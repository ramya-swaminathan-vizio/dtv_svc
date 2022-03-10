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
 * $RCSfile: vkb.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: GUI composite component -- Time Entry
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "u_common.h"

#include "c_handle.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_wgl_sets.h"

#include "c_fe.h"
#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "wdk/vkb/vkb.h"
#include "res/wdk/vkb/vkb_rc.h"
#include "res/wdk/a_vkb_custom.h"
#include "res/wdk/wdk_img.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#define VKB_LANGUAGE_ENG                    "eng"
#define VKB_LANGUAGE_FRE                    "fre"
#define VKB_LANGUAGE_SPA                    "spa"

#define _ENABLE_EB_CLR_ICON                 1
#define _ENABLE_NEW_KEY_PAD                 1
//#define _PRINT_PROC_MAPS

#define VKB_RC_CHG_DFT                      ((UINT8)0)
#define VKB_RC_CHG_PHASE2                   ((UINT8)1)
#define VKB_RC_CHG_UI3X                     ((UINT8)2)

#define COPY_RECT(dst_rect, src_rect)   \
do{\
    (dst_rect)->i4_left = (src_rect)->i4_left;  \
    (dst_rect)->i4_top = (src_rect)->i4_top;    \
    (dst_rect)->i4_right = (src_rect)->i4_right;    \
    (dst_rect)->i4_bottom = (src_rect)->i4_bottom;  \
}while(0)

#define COPY_ATTACH_DATA(dst_data, src_data)   \
do{\
    if (NULL == (dst_data) || NULL == (src_data))   \
    {   \
        break;  \
    }\
    \
    (dst_data)->h_edit_box = (src_data)->h_edit_box;    \
    COPY_RECT(&((dst_data)->t_rect_eb), &((src_data)->t_rect_eb));  \
    \
    (dst_data)->b_need_eb_clr = (src_data)->b_need_eb_clr;  \
    (dst_data)->h_eb_clr = (src_data)->h_eb_clr;  \
    COPY_RECT(&((dst_data)->t_rect_eb_clr), &((src_data)->t_rect_eb_clr));  \
    \
    (dst_data)->pf_eb_proc = (src_data)->pf_eb_proc;  \
    (dst_data)->pf_eb_clr_proc = (src_data)->pf_eb_clr_proc;  \
}while(0)

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static GL_RECT_T t_rect_main_frm = {0};
static GL_RECT_T t_rect_eb = {0};
static GL_RECT_T t_rect_label = {0};
static GL_RECT_T t_rect_btn_ok = {0};
static GL_RECT_T t_rect_btn_cancel = {0};

static HANDLE_T  h_cur_vkb = NULL_HANDLE;

static UINT16 g_ui2_lang_id = 0;

static UTF16_T  w2s_ok_txt[3][10] = {L"OK",L"OK",L"Aceptar"};
static UTF16_T  w2s_cncl_txt[3][10] = {L"Cancel",L"Annuler",L"Cancelar"};

static UINT8    aui1_latin_offset[VKB_KEYPAD_LATIN_KEY_TEXT_NUM][2] =
                                {
                                    {0, 0}, {0, 2}, {0, 3}, {0, 4},{0, 8},
                                    {1, 4}, {1, 5},
                                    {2, 2}, {2, 6}
                                };

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _vkb_view_create_main_frm(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    HANDLE_T                h_parent,
                    VKB_GUI_RC_T            t_gui_rc);

static INT32 _vkb_view_create_label_txt(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    HANDLE_T                h_parent);

static INT32 _vkb_view_create_keypad_normal_key_txt(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    HANDLE_T                h_parent);

static INT32 _vkb_view_create_keypad_ctrl_key_txt(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    HANDLE_T                h_parent);

static INT32 _vkb_view_create_button_txt(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    HANDLE_T                h_parent);

static INT32 _vkb_view_create_editbox(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    HANDLE_T                h_parent);

static INT32 _vkb_view_set_text_keymap(
                    HANDLE_T                h_txt_handle);

static INT32 _vkb_view_txt_wdgt_proc_fct(
                    HANDLE_T    h_widget,
                    UINT32      ui4_msg,
                    VOID*       pv_param1,
                    VOID*       pv_param2);

static INT32 _vkb_get_attach_data(
                    HANDLE_T                h_vkb_handle,
                    VKB_CONTROL_LOGIC_T**   ppt_vkb_ctrl);

static INT32 _vkb_set_attach_data(
                    HANDLE_T                h_vkb_handle,
                    VKB_CONTROL_LOGIC_T*    pt_vkb_ctrl);

static INT32 _vkb_init_internal_ctrl_data(
                    VKB_INIT_T*             pt_init_data,
                    VKB_CONTROL_LOGIC_T*    pt_this);

static INT32 _vkb_set_focus_item(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    VKB_FOCUS_CHG_TYPE_T    e_chg_type,
                    BOOL                    b_repaint);

static INT32 _vkb_view_select_key_proc(
                    VKB_CONTROL_LOGIC_T*    pt_this);

static INT32 _vkb_view_editbox_set_text(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    UTF16_T*                pw2s_txt,
                    BOOL                    b_repaint);

static INT32 _vkb_view_editbox_get_text(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    UTF16_T*                pw2s_txt,
                    SIZE_T                  sz_len);

static INT32 _vkb_view_keypad_set_key_text(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    BOOL                    b_repaint);

static INT32 _vkb_view_keypad_get_key_value(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    VKB_KEYPAD_KEY_ITEM_T*  pt_keypad_key,
                    CHAR*                   ps_value);

static INT32 _vkb_view_keypad_get_key_caption(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    VKB_KEYPAD_KEY_ITEM_T*  pt_keypad_key,
                    CHAR*                   ps_caption);

static INT32 _vkb_view_ctrl_key_backspace_proc_fct(
                    VOID* pv_tag,
                    VOID* pv_vkb_ctrl);

static INT32 _vkb_full_scrn_pad_set_focus_item(
                    VKB_CONTROL_LOGIC_T*    pt_this,    /* IN, OUT */
                    VKB_FOCUS_CHG_TYPE_T    e_chg_type, /* IN */
                    BOOL                    b_repaint);

static BOOL _vkb_is_eb_clr_hide(
                    HANDLE_T h_vkb_handle
                    );

static VOID _set_cur_attached_vkb_handle(HANDLE_T h_vkb);

static HANDLE_T _get_cur_attached_vkb_handle(VOID);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*
* This method only used for support fre/spa issues that occured on acfg buffer is low.
*/

static INT32 _vkb_view_play_tts(VKB_CONTROL_LOGIC_T *pt_this, VKB_FOCUS_WIDGET_T e_focus_type)
{
    INT32 i4_ret = NAVR_OK;

#ifdef APP_TTS_SUPPORT
    BOOL                    b_play = TRUE;
    BOOL                    b_symbol_page = FALSE;
    UTF16_T                 w2s_str[64] = {0};

    switch (e_focus_type)
    {
        case VKB_FOCUS_WIDGET_EDIT_BOX:
        {
            c_uc_w2s_strcpy(w2s_str, L"EDIT BOX");
            break;
        }
        case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
        {

            c_wgl_do_cmd (pt_this->aah_normal_key_txt[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row][pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col],
                          WGL_CMD_TEXT_GET_TEXT,
                          WGL_PACK (w2s_str),
                          WGL_PACK (63));

            if (pt_this->b_symbol_page)
            {
                b_symbol_page = TRUE;
            }
            break;
        }
        case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
        {
            switch (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx)
            {
                case VKB_KEYPAD_CTRL_SYMBOL_KEY_IDX:
                    if (pt_this->b_symbol_page)
                    {
                        c_uc_w2s_strcpy(w2s_str, L"ABC");
                    }
                    else
                    {
                        c_uc_w2s_strcpy(w2s_str, L"SYMBOL");
                    }
                    break;
                case VKB_KEYPAD_CTRL_CAPS_KEY_IDX:
                    c_uc_w2s_strcpy(w2s_str, L"CAP");
                    break;
                case VKB_KEYPAD_CTRL_LATIN_KEY_IDX:
                    c_uc_w2s_strcpy(w2s_str, L"LATIN");
                    break;
                case VKB_KEYPAD_CTRL_SPACE_KEY_IDX:
                    c_uc_w2s_strcpy(w2s_str, L"SPACE");
                    break;
                case VKB_KEYPAD_CTRL_DEL_KEY_IDX:
                    c_uc_w2s_strcpy(w2s_str, L"DELETE");
                    break;
                default:
                    break;
            }
            break;
        }
        case VKB_FOCUS_WIDGET_BTN_OK:
        {
            c_uc_w2s_strcpy(w2s_str, L"OK");
            break;
        }
        case VKB_FOCUS_WIDGET_BTN_CANCEL:
        {
            c_uc_w2s_strcpy(w2s_str, L"Cancel");
            break;
        }
        case VKB_FOCUS_WIDGET_EB_CLR:
        {
            c_uc_w2s_strcpy(w2s_str, L"Clear All");
            break;
        }
        default:
        {
            b_play = FALSE;
            break;
        }
    }

    if (b_play)
    {
        if (b_symbol_page)
        {
            a_app_tts_play_symbol(w2s_str[0]);
        }
        else
        {
            i4_ret = a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
        }
    }
#endif
    return i4_ret;
}

static BOOL _vkb_view_eb_chk_buffer_full(VKB_CONTROL_LOGIC_T* pt_this, UTF16_T *pw2s_append)
{
#ifdef APP_VKB_SUPPORT_LATIN_CHAR
#define VKB_EB_APPEND_LEN   8

    BOOL        b_full = FALSE;
    UINT16      ui2_len = 0;
    UINT16      ui2_append_len = 0;
    CHAR        ac_txt[VKB_INPUT_TEXT_MAX_LEN+1];
    CHAR        ac_append[VKB_EB_APPEND_LEN];

    c_memset(ac_txt, 0, sizeof(ac_txt));
    c_memset(ac_append, 0, sizeof(ac_append));

    if (pw2s_append != NULL && c_uc_w2s_strlen(pw2s_append) > 0)
    {
        c_uc_w2s_to_ps(pw2s_append, ac_append, sizeof(ac_append)-1);
        ui2_append_len = c_strlen(ac_append);
    }

    c_uc_w2s_to_ps(pt_this->aw2s_txt, ac_txt, VKB_INPUT_TEXT_MAX_LEN);

    ui2_len = c_strlen(ac_txt);

    /* ui4_max_char_num indicator the CHAR buffer size when vkb not support fre/spa */
    b_full = ((ui2_len >= pt_this->ui4_max_char_num)
             || (ui2_len + ui2_append_len > pt_this->ui4_max_char_num)) ? TRUE : FALSE;

    DBG_INFO(("[VKB]: Limit length = %d, curent length = %d, append length = %d\n",
                                                            pt_this->ui4_max_char_num,
                                                            ui2_len,
                                                            ui2_append_len));
    return b_full;
#else
    return FALSE;
#endif
}

static BOOL _vkb_view_eb_cursor_at_end(HANDLE_T h_eb_input)
{
    BOOL b_end = FALSE;

    return b_end;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_create_kb_frm(VKB_CONTROL_LOGIC_T*    pt_this,
                                       HANDLE_T                h_parent,
                                       VKB_GUI_RC_T            t_gui_rc)
{
    WDK_FRM_WIDGET_PARAM_T t_frm_param;

    /* Create root frame */
    c_memset(&t_frm_param, 0, sizeof(WDK_FRM_WIDGET_PARAM_T));

    t_frm_param.h_parent             = h_parent;
    t_frm_param.ui1_alpha            = VKB_MAIN_FRAME_ALPHA;
    t_frm_param.b_visibility         = TRUE;
    t_frm_param.i4_x                 = 0;
    t_frm_param.i4_y                 = VKB_3X_KB_FRAME_Y;
    t_frm_param.i4_w                 = VKB_3X_KB_FRAME_W;
    t_frm_param.i4_h                 = VKB_3X_KB_FRAME_H;

    t_frm_param.ui4_style            = 0;
    t_frm_param.t_img_bk.h_enable    = pt_this->pt_rc_config->h_kb_frm_bk_img;
    t_frm_param.t_img_bk.h_highlight = pt_this->pt_rc_config->h_kb_frm_bk_img;
    t_frm_param.t_img_bk.h_disable   = pt_this->pt_rc_config->h_kb_frm_bk_img;

    t_frm_param.pf_wdgt_proc         = NULL;
    t_frm_param.ph_created_frm       = & pt_this->h_kb_frm;

    c_wgl_set_visibility(pt_this->h_kb_frm, WGL_SW_NORMAL);

    return a_wdk_create_frm_widget (t_frm_param);
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_create_main_frm(VKB_CONTROL_LOGIC_T*    pt_this,
                                       HANDLE_T                h_parent,
                                       VKB_GUI_RC_T            t_gui_rc)
{
    WDK_FRM_WIDGET_PARAM_T t_frm_param;

    /* Create main frame */
    c_memset(&t_frm_param, 0, sizeof(WDK_FRM_WIDGET_PARAM_T));

    t_frm_param.h_parent             = h_parent;
    t_frm_param.ui1_alpha            = VKB_MAIN_FRAME_ALPHA;
    t_frm_param.b_visibility         = TRUE;
    t_frm_param.i4_x                 = t_gui_rc.i4_left;
    t_frm_param.i4_y                 = t_gui_rc.i4_top;
    t_frm_param.i4_w                 = VKB_MAIN_FRAME_W;

    /*if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD )
        || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID))
    {
        t_frm_param.i4_h             = VKB_BTN_OK_TEXT_Y;
    }
    else*/
    {
        t_frm_param.i4_h             = VKB_MAIN_FRAME_H;
    }

    t_frm_param.ui4_style            = 0;
    t_frm_param.t_img_bk.h_enable    = pt_this->pt_rc_config->h_main_frm_bk_img;
    t_frm_param.t_img_bk.h_highlight = pt_this->pt_rc_config->h_main_frm_bk_img;
    t_frm_param.t_img_bk.h_disable   = pt_this->pt_rc_config->h_main_frm_bk_img;

    t_frm_param.pf_wdgt_proc         = NULL;
    t_frm_param.ph_created_frm       = & pt_this->h_main_frm;

    return a_wdk_create_frm_widget (t_frm_param);
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_create_label_txt(VKB_CONTROL_LOGIC_T*    pt_this,
                                        HANDLE_T                h_parent)
{
    WDK_TXT_WIDGET_PARAM_T  t_txt_param;

    /* Create label text */
    c_memset(&t_txt_param, 0, sizeof(WDK_TXT_WIDGET_PARAM_T));

    t_txt_param.h_parent      = h_parent;
    t_txt_param.ui1_alpha     = VKB_LABEL_TEXT_ALPHA;
    t_txt_param.b_visibility  = TRUE;
    t_txt_param.i4_x          = VKB_LABEL_TEXT_X;
    t_txt_param.i4_y          = VKB_LABEL_TEXT_Y;
    t_txt_param.i4_w          = VKB_LABEL_TEXT_W;
    t_txt_param.i4_h          = VKB_LABEL_TEXT_H;
    t_txt_param.ui4_style     = WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_END_AS_NEWLINE | WGL_STL_TEXT_SMART_CUT;
    t_txt_param.ps_font_name  = VKB_LABEL_TEXT_FONT_NAME;
    t_txt_param.e_font_size   = VKB_LABEL_TEXT_FONT_SIZE;
    t_txt_param.e_font_style  = VKB_LABEL_TEXT_FONT_STYLE;
    t_txt_param.ui1_align     = VKB_LABEL_TEXT_ALIGNMENT;
    t_txt_param.b_img_bk      = TRUE;
    t_txt_param.pt_clr_txt    = & (pt_this->pt_rc_config->t_label_txt_clr);
    t_txt_param.pt_hlt_clr_txt    = & (pt_this->pt_rc_config->t_label_txt_clr);
    t_txt_param.pt_dis_clr_txt= & (pt_this->pt_rc_config->t_label_txt_dis_clr);

    t_txt_param.pf_wdgt_proc  = NULL;
    t_txt_param.ph_created_txt= & pt_this->h_label_txt;

    return a_wdk_create_txt_widget (t_txt_param);
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_create_keypad_normal_key_txt(VKB_CONTROL_LOGIC_T*    pt_this,
                                                    HANDLE_T                h_parent)

{
    INT32                   i4_ret;
    UINT8                   ui1_idx_row;
    UINT8                   ui1_idx_col;
    WDK_TXT_WIDGET_PARAM_T  t_txt_param;

    for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM; ui1_idx_row++)
    {
        for (ui1_idx_col=0; ui1_idx_col<VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM; ui1_idx_col++)
        {
            /* Create keypad normal key text */
            c_memset(&t_txt_param, 0, sizeof(WDK_TXT_WIDGET_PARAM_T));

            t_txt_param.h_parent      = h_parent;
            t_txt_param.ui1_alpha     = VKB_KEYPAD_KEY_TEXT_ALPHA;
            t_txt_param.b_visibility  = TRUE;
            t_txt_param.i4_x          = VKB_KEYPAD_NORMAL_KEY_TEXT_X + ui1_idx_col*(VKB_KEYPAD_NORMAL_KEY_TEXT_W + VKB_KEYPAD_KEY_TEXT_INTERVAL_X);
            t_txt_param.i4_y          = VKB_KEYPAD_NORMAL_KEY_TEXT_Y + ui1_idx_row*(VKB_KEYPAD_NORMAL_KEY_TEXT_H + VKB_KEYPAD_KEY_TEXT_INTERVAL_Y);
            t_txt_param.i4_w          = VKB_KEYPAD_NORMAL_KEY_TEXT_W;
            t_txt_param.i4_h          = VKB_KEYPAD_NORMAL_KEY_TEXT_H;
            t_txt_param.ui4_style     = WGL_STL_TEXT_MAX_32 | WGL_STL_TEXT_END_AS_NEWLINE | WGL_STL_TEXT_SMART_CUT;
            t_txt_param.ps_font_name  = VKB_KEYPAD_KEY_TEXT_FONT_NAME;
            t_txt_param.e_font_size   = VKB_KEYPAD_KEY_TEXT_FONT_SIZE;
            t_txt_param.e_font_style  = VKB_KEYPAD_KEY_TEXT_FONT_STYLE;
            t_txt_param.ui1_align     = VKB_KEYPAD_KEY_TEXT_ALIGNMENT;
            t_txt_param.b_img_bk      = TRUE;
            t_txt_param.pt_clr_txt    = & (pt_this->pt_rc_config->t_keypad_key_txt_clr);
            t_txt_param.pt_hlt_clr_txt= & (pt_this->pt_rc_config->t_keypad_key_txt_hlt_clr);
            t_txt_param.pt_dis_clr_txt= & (pt_this->pt_rc_config->t_keypad_key_txt_dis_clr);

            t_txt_param.t_img_bk.h_enable    = pt_this->pt_rc_config->h_keypad_bk_img;
            t_txt_param.t_img_bk.h_highlight = pt_this->pt_rc_config->h_keypad_bk_hlt_img;
            t_txt_param.t_img_bk.h_disable   = NULL_HANDLE;

            t_txt_param.pf_wdgt_proc  = _vkb_view_txt_wdgt_proc_fct;
            t_txt_param.ph_created_txt= & (pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col]);

            i4_ret = a_wdk_create_txt_widget (t_txt_param);
            WDK_CHK_FAIL(i4_ret);

            /* Clear key map to make sure text widget will notify CURSOR key to its parent frame. */
            i4_ret = _vkb_view_set_text_keymap(*(t_txt_param.ph_created_txt));
            WDK_CHK_FAIL(i4_ret);
        }
    }

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_create_keypad_ctrl_key_txt(VKB_CONTROL_LOGIC_T*    pt_this,
                                                  HANDLE_T                h_parent)

{
    INT32                   i4_ret;
    UINT8                   ui1_idx_row;
    WDK_TXT_WIDGET_PARAM_T  t_txt_param;

    INT32                   ai4_ctrl_key_width[VKB_KEYPAD_CTRL_KEY_TEXT_NUM] =
        {
            VKB_KEYPAD_BIG_KEY_TEXT_W - 1,
            VKB_KEYPAD_BIG_KEY_TEXT_W - 1,
            VKB_KEYPAD_BIG_KEY_TEXT_W,
            VKB_KEYPAD_SPACE_KEY_TEXT_W,
            VKB_KEYPAD_BIG_KEY_TEXT_W
        };

    INT32                   ai4_ctrl_key_height[VKB_KEYPAD_CTRL_KEY_TEXT_NUM] =
        {
            VKB_KEYPAD_BIG_KEY_TEXT_H,
            VKB_KEYPAD_BIG_KEY_TEXT_H,
            VKB_KEYPAD_BIG_KEY_TEXT_H,
            VKB_KEYPAD_SPACE_KEY_TEXT_H,
            VKB_KEYPAD_BIG_KEY_TEXT_H
        };

    INT32                   i4_ctrl_key_x = VKB_KEYPAD_CTRL_KEY_TEXT_X;

    WGL_HIMG_TPL_T          ah_txt_bk_img[] =
    {
        pt_this->pt_rc_config->h_keypad_big_bk_img,
        pt_this->pt_rc_config->h_keypad_capslock_bk_img,
        pt_this->pt_rc_config->h_keypad_big_bk_img,
        pt_this->pt_rc_config->h_keypad_space_bk_img,
        pt_this->pt_rc_config->h_keypad_delete_bk_img
    };

    WGL_HIMG_TPL_T          ah_txt_bk_hlt_img[] =
    {
        pt_this->pt_rc_config->h_keypad_big_bk_hlt_img,
        pt_this->pt_rc_config->h_keypad_capslock_bk_hlt_img,
        pt_this->pt_rc_config->h_keypad_big_bk_hlt_img,
        pt_this->pt_rc_config->h_keypad_space_bk_hlt_img,
        pt_this->pt_rc_config->h_keypad_delete_bk_hlt_img
    };

    WGL_HIMG_TPL_T          ah_txt_bk_dis_img[] =
    {
        NULL_HANDLE,
        pt_this->pt_rc_config->h_keypad_capslock_bk_dis_img,
        NULL_HANDLE,
        NULL_HANDLE,
        pt_this->pt_rc_config->h_keypad_delete_bk_dis_img
    };


    for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_CTRL_KEY_TEXT_NUM; ui1_idx_row++)
    {
        /* Create keypad ctrl key text */
        c_memset(&t_txt_param, 0, sizeof(WDK_TXT_WIDGET_PARAM_T));

        t_txt_param.h_parent      = h_parent;
        t_txt_param.ui1_alpha     = VKB_KEYPAD_KEY_TEXT_ALPHA;
        t_txt_param.b_visibility  = TRUE;
        t_txt_param.i4_x          = i4_ctrl_key_x;
        t_txt_param.i4_y          = VKB_KEYPAD_CTRL_KEY_TEXT_Y;
        t_txt_param.i4_w          = ai4_ctrl_key_width[ui1_idx_row];
        t_txt_param.i4_h          = ai4_ctrl_key_height[ui1_idx_row];
        i4_ctrl_key_x             += ai4_ctrl_key_width[ui1_idx_row] + VKB_KEYPAD_KEY_TEXT_INTERVAL_X;

        t_txt_param.ui4_style     = WGL_STL_TEXT_MAX_32 | WGL_STL_TEXT_END_AS_NEWLINE | WGL_STL_TEXT_SMART_CUT;
        t_txt_param.ps_font_name  = VKB_KEYPAD_KEY_TEXT_FONT_NAME;
        t_txt_param.e_font_size   = VKB_KEYPAD_KEY_TEXT_FONT_SIZE;
        t_txt_param.e_font_style  = VKB_KEYPAD_KEY_TEXT_FONT_STYLE;
        t_txt_param.ui1_align     = VKB_KEYPAD_KEY_TEXT_ALIGNMENT;
        t_txt_param.b_img_bk      = TRUE;
        t_txt_param.pt_clr_txt    = & (pt_this->pt_rc_config->t_keypad_key_txt_clr);
        t_txt_param.pt_hlt_clr_txt= & (pt_this->pt_rc_config->t_keypad_key_txt_hlt_clr);
        t_txt_param.pt_dis_clr_txt= & (pt_this->pt_rc_config->t_keypad_key_txt_dis_clr);

        t_txt_param.t_img_bk.h_enable    = ah_txt_bk_img[ui1_idx_row];
        t_txt_param.t_img_bk.h_highlight = ah_txt_bk_hlt_img[ui1_idx_row];
        t_txt_param.t_img_bk.h_disable   = ah_txt_bk_dis_img[ui1_idx_row];

        t_txt_param.pf_wdgt_proc  = _vkb_view_txt_wdgt_proc_fct;
        t_txt_param.ph_created_txt= & (pt_this->ah_ctrl_key_txt[ui1_idx_row]);

        i4_ret = a_wdk_create_txt_widget (t_txt_param);
        WDK_CHK_FAIL(i4_ret);

        /* Clear key map to make sure text widget will notify CURSOR key to its parent frame. */
        i4_ret = _vkb_view_set_text_keymap(*(t_txt_param.ph_created_txt));
        WDK_CHK_FAIL(i4_ret);
    }

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_create_button_txt(VKB_CONTROL_LOGIC_T*    pt_this,
                                         HANDLE_T                h_parent)
{
    INT32                   i4_ret;
    WDK_TXT_WIDGET_PARAM_T  t_txt_param;

    /* Create button OK, it is a text widget */
    c_memset(&t_txt_param, 0, sizeof(WDK_TXT_WIDGET_PARAM_T));

    t_txt_param.h_parent      = h_parent;
    t_txt_param.ui1_alpha     = VKB_BTN_OK_TEXT_ALPHA;
    t_txt_param.b_visibility  = TRUE;
    t_txt_param.i4_x          = VKB_BTN_OK_TEXT_X;
    t_txt_param.i4_y          = VKB_BTN_OK_TEXT_Y;
    t_txt_param.i4_w          = VKB_BTN_OK_TEXT_W;
    t_txt_param.i4_h          = VKB_BTN_OK_TEXT_H;
    t_txt_param.ui4_style     = WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_END_AS_NEWLINE | WGL_STL_TEXT_SMART_CUT;
    t_txt_param.ps_font_name  = VKB_BTN_FONT_NAME;
    t_txt_param.e_font_size   = VKB_BTN_FONT_SIZE;
    t_txt_param.e_font_style  = VKB_BTN_FONT_STYLE;
    t_txt_param.ui1_align     = VKB_BTN_OK_TEXT_ALIGNMENT;
    t_txt_param.b_img_bk      = TRUE;
    t_txt_param.pt_clr_txt    = & (pt_this->pt_rc_config->t_btn_txt_clr);
    t_txt_param.pt_hlt_clr_txt= & (pt_this->pt_rc_config->t_btn_txt_hlt_clr);
    t_txt_param.pt_dis_clr_txt= & (pt_this->pt_rc_config->t_btn_txt_dis_clr);

    t_txt_param.t_img_bk.h_enable    = pt_this->pt_rc_config->h_keypad_bar_bk_img;
    t_txt_param.t_img_bk.h_highlight = pt_this->pt_rc_config->h_keypad_bar_bk_hlt_img;
    t_txt_param.t_img_bk.h_disable   = pt_this->pt_rc_config->h_keypad_bar_bk_img;

    /* content insert setting */
    t_txt_param.t_inset.i4_left      = VKB_BTN_CNT_INSET_L;
    t_txt_param.t_inset.i4_right     = VKB_BTN_CNT_INSET_R;
    t_txt_param.t_inset.i4_top       = VKB_BTN_CNT_INSET_T;
    t_txt_param.t_inset.i4_bottom    = VKB_BTN_CNT_INSET_B;

    t_txt_param.pf_wdgt_proc  = _vkb_view_txt_wdgt_proc_fct;
    t_txt_param.ph_created_txt= & pt_this->h_ok_txt;

    i4_ret = a_wdk_create_txt_widget (t_txt_param);
    WDK_CHK_FAIL(i4_ret);

    /* Clear key map to make sure text widget will notify CURSOR key to its parent frame. */
    i4_ret = _vkb_view_set_text_keymap(*(t_txt_param.ph_created_txt));
    WDK_CHK_FAIL(i4_ret);

    /* Set OK Button default name */
    i4_ret = a_wdk_text_set_text(*(t_txt_param.ph_created_txt), L"OK");
    WDK_CHK_FAIL(i4_ret);
    c_memset(pt_this->aw2s_ok_txt, 0, 32);
    pt_this->aw2s_ok_txt[0] = 0xFFFF;

    /* Create button Cancel, it is a text widget */
    c_memset(&t_txt_param, 0, sizeof(WDK_TXT_WIDGET_PARAM_T));

    t_txt_param.h_parent      = h_parent;
    t_txt_param.ui1_alpha     = VKB_BTN_CANCEL_TEXT_ALPHA;
    t_txt_param.b_visibility  = TRUE;

    t_txt_param.i4_x          = VKB_BTN_CANCEL_TEXT_X;
    t_txt_param.i4_y          = VKB_BTN_CANCEL_TEXT_Y;
    t_txt_param.i4_w          = VKB_BTN_CANCEL_TEXT_W;
    t_txt_param.i4_h          = VKB_BTN_CANCEL_TEXT_H;
    t_txt_param.ui4_style     = WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_END_AS_NEWLINE | WGL_STL_TEXT_SMART_CUT;
    t_txt_param.ps_font_name  = VKB_BTN_FONT_NAME;
    t_txt_param.e_font_size   = VKB_BTN_FONT_SIZE;
    t_txt_param.e_font_style  = VKB_BTN_FONT_STYLE;
    t_txt_param.ui1_align     = VKB_BTN_CANCEL_TEXT_ALIGNMENT;
    t_txt_param.b_img_bk      = TRUE;
    t_txt_param.pt_clr_txt    = & (pt_this->pt_rc_config->t_btn_txt_clr);
    t_txt_param.pt_hlt_clr_txt= & (pt_this->pt_rc_config->t_btn_txt_hlt_clr);
    t_txt_param.pt_dis_clr_txt= & (pt_this->pt_rc_config->t_btn_txt_dis_clr);

    t_txt_param.t_img_bk.h_enable    = pt_this->pt_rc_config->h_keypad_bar_bk_img;
    t_txt_param.t_img_bk.h_highlight = pt_this->pt_rc_config->h_keypad_bar_bk_hlt_img;
    t_txt_param.t_img_bk.h_disable   = NULL_HANDLE;

    /* content insert setting */
    t_txt_param.t_inset.i4_left      = VKB_BTN_CNT_INSET_L;
    t_txt_param.t_inset.i4_right     = VKB_BTN_CNT_INSET_R;
    t_txt_param.t_inset.i4_top       = VKB_BTN_CNT_INSET_T;
    t_txt_param.t_inset.i4_bottom    = VKB_BTN_CNT_INSET_B;

    t_txt_param.pf_wdgt_proc  = _vkb_view_txt_wdgt_proc_fct;
    t_txt_param.ph_created_txt= & pt_this->h_cancel_txt;

    i4_ret = a_wdk_create_txt_widget (t_txt_param);
    WDK_CHK_FAIL(i4_ret);

    /* Clear key map to make sure text widget will notify CURSOR key to its parent frame. */
    i4_ret = _vkb_view_set_text_keymap(*(t_txt_param.ph_created_txt));
    WDK_CHK_FAIL(i4_ret);

    /* Set Cancel Button default name */
    i4_ret = a_wdk_text_set_text(*(t_txt_param.ph_created_txt), L"Cancel");
    WDK_CHK_FAIL(i4_ret);

    c_memset(pt_this->aw2s_cncl_txt, 0, 32);
    pt_this->aw2s_cncl_txt[0] = 0xFFFF;

    return WDKR_OK;
}

static INT32 _vkb_view_eb_proc_fct(HANDLE_T    h_widget,
                                      UINT32      ui4_msg,
                                      VOID*       pv_param1,
                                      VOID*       pv_param2)
{
    INT32                 i4_ret;
    UINT32                ui4_key_code;
    HANDLE_T              h_vkb_frm;
    VKB_CONTROL_LOGIC_T*  pt_this = NULL;

    i4_ret = c_wgl_get_parent(h_widget, & h_vkb_frm);
    if(i4_ret != WGLR_OK)
    {
       return i4_ret;
    }

    /* 1. Get attach data */
    i4_ret = _vkb_get_attach_data(h_vkb_frm, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if ((WGL_MSG_KEY_DOWN != ui4_msg)&&
        (WGL_MSG_KEY_REPEAT != ui4_msg))
    {
        return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
    }

    /* get key code */
    ui4_key_code = (UINT32)pv_param1;

    switch (ui4_key_code)
    {
        case BTN_CURSOR_RIGHT:
        {
            /* Change focus via Right key */
            i4_ret = _vkb_set_focus_item(pt_this, VKB_FOCUS_CHG_RIGHT_KEY, TRUE);
            WDK_CHK_FAIL(i4_ret);
            return WDKR_OK;
        }
        default:
            break;
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

}

/*----------------------------------------------------------------------------
 * Name: _eb_pwd_proc_fct
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
static INT32 _vkb_view_eb_proc_fct_ex(HANDLE_T    h_widget,
                                      UINT32      ui4_msg,
                                      VOID*       pv_param1,
                                      VOID*       pv_param2)
{
    INT32                 i4_ret;
    UINT32                ui4_key_code;
    HANDLE_T              h_vkb_frm;
    VKB_CONTROL_LOGIC_T*  pt_this = NULL;
    UINT32                ui4_len = 0;

    if ((h_vkb_frm = _get_cur_attached_vkb_handle()) == NULL_HANDLE)
    {
        i4_ret = c_wgl_get_parent(h_widget, & h_vkb_frm);
        if(i4_ret != WGLR_OK)
        {
           return i4_ret;
        }
    }

    /* 1. Get attach data */
    i4_ret = _vkb_get_attach_data(h_vkb_frm, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if ((WGL_MSG_KEY_DOWN != ui4_msg)&&
        (WGL_MSG_KEY_REPEAT != ui4_msg))
    {
        if (WGL_MSG_LOSE_FOCUS == ui4_msg)
        {
            c_memset(pt_this->aw2s_txt, 0, sizeof(UTF16_T)*(VKB_INPUT_TEXT_MAX_LEN+1));

            i4_ret = c_wgl_do_cmd (h_widget,
                                   WGL_CMD_EB_GET_TEXT,
                                   WGL_PACK (pt_this->aw2s_txt),
                                   WGL_PACK (VKB_INPUT_TEXT_MAX_LEN));
            if(i4_ret != WGLR_OK)
            {
                c_memset(pt_this->aw2s_txt, 0, sizeof(UTF16_T)*(VKB_INPUT_TEXT_MAX_LEN+1));
            }

            /* update buffer content to editbox widget */
            i4_ret = _vkb_view_editbox_set_text(pt_this, pt_this->aw2s_txt, !pt_this->b_eb_attached);
            WDK_CHK_FAIL(i4_ret);
        }
        else if (WGL_MSG_KEY_UP == ui4_msg)
        {
            UINT32 ui4_key_code = (UINT32)pv_param1;
            if (BTN_DIGIT_0 <= ui4_key_code && ui4_key_code <= BTN_DIGIT_9)
            {
                UTF16_T w2s_str[2] = {0};
                w2s_str[0] = '0' + ui4_key_code - BTN_DIGIT_0;
                a_app_tts_play(w2s_str, 2);
            }
        }

        return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
    }

    /* get key code */
    ui4_key_code = (UINT32)pv_param1;

    if (BTN_DIGIT_0 <= ui4_key_code && ui4_key_code <= BTN_DIGIT_9)
    {
        UTF16_T w2s_str[2] = {0};
        w2s_str[0] = '0' + ui4_key_code - BTN_DIGIT_0;
        a_app_tts_play(w2s_str, 2);
    }

    if (NULL != pt_this->pf_fct)
    {
        /* notify VKB_MSG_DLG_KEY_INPUT message to caller */
        i4_ret = pt_this->pf_fct(
                            pt_this->pv_tag,
                            VKB_MSG_DLG_KEY_INPUT,
                            (VOID*)(&ui4_key_code),
                            NULL);

        if (WDK_NO_ACTION == i4_ret)
        {
            return WDKR_OK;
        }
    }

    if (((BTN_DIGIT_0 <= ui4_key_code) && (BTN_DIGIT_9 >= ui4_key_code)) ||
        ((BTN_KB_NULL <= ui4_key_code) && (BTN_KB_HYPER >= ui4_key_code)))
    {
        if (TRUE == pt_this->b_eb_attached)
        {
            c_memset(pt_this->aw2s_txt, 0, sizeof(UTF16_T)*(VKB_INPUT_TEXT_MAX_LEN+1));

            i4_ret = c_wgl_do_cmd (h_widget,
                                   WGL_CMD_EB_GET_TEXT,
                                   WGL_PACK (pt_this->aw2s_txt),
                                   WGL_PACK (VKB_INPUT_TEXT_MAX_LEN));

            /* check total char number */
            ui4_len = c_uc_w2s_strlen(pt_this->aw2s_txt);

            if (ui4_len >= (pt_this->ui4_max_char_num)
                || _vkb_view_eb_cursor_at_end(h_widget))
            {
                return WDKR_OK;
            }

            if (_vkb_view_eb_chk_buffer_full(pt_this, NULL))
            {
                return WDKR_OK;
            }

            c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

            if (NULL != pt_this->pf_fct)
            {
               i4_ret = pt_this->pf_fct(
                            pt_this->pv_tag,
                            VKB_MSG_DLG_KEY_INPUT,
                            (VOID*)(&ui4_key_code),
                            NULL);
            }

            return WDKR_OK;
        }
    }

    switch (ui4_key_code)
    {
        case BTN_CURSOR_UP:
        {
            /* Change focus via UP key */
            i4_ret = _vkb_set_focus_item(pt_this, VKB_FOCUS_CHG_UP_KEY, TRUE);
            WDK_CHK_FAIL(i4_ret);
        }
        return WDKR_OK;

        case BTN_CURSOR_DOWN:
        {
            /* Change focus via Down key */
            i4_ret = _vkb_set_focus_item(pt_this, VKB_FOCUS_CHG_DOWN_KEY, TRUE);
            WDK_CHK_FAIL(i4_ret);
        }
        return WDKR_OK;

        case BTN_KB_BACKSPACE:
        case BTN_CURSOR_LEFT:
        {
            c_memset(pt_this->aw2s_txt, 0, sizeof(UTF16_T)*(VKB_INPUT_TEXT_MAX_LEN+1));

            i4_ret = c_wgl_do_cmd (h_widget,
                                    WGL_CMD_EB_GET_TEXT,
                                    WGL_PACK (pt_this->aw2s_txt),
                                    WGL_PACK (VKB_INPUT_TEXT_MAX_LEN));
            if(i4_ret != WGLR_OK)
            {
                c_memset(pt_this->aw2s_txt, 0, sizeof(UTF16_T)*(VKB_INPUT_TEXT_MAX_LEN+1));
            }

            /* update buffer content to editbox widget */
            i4_ret = _vkb_view_editbox_set_text(pt_this, pt_this->aw2s_txt, TRUE);
            WDK_CHK_FAIL(i4_ret);

            _vkb_view_ctrl_key_backspace_proc_fct(NULL, pt_this);
        }
        return WDKR_OK;

        case BTN_KB_ENTER:
        {
            c_memset(pt_this->aw2s_txt, 0, sizeof(UTF16_T)*(VKB_INPUT_TEXT_MAX_LEN+1));

            i4_ret = c_wgl_do_cmd (h_widget,
                                   WGL_CMD_EB_GET_TEXT,
                                   WGL_PACK (pt_this->aw2s_txt),
                                   WGL_PACK (VKB_INPUT_TEXT_MAX_LEN));
            if(i4_ret != WGLR_OK)
            {
                c_memset(pt_this->aw2s_txt, 0, sizeof(UTF16_T)*(VKB_INPUT_TEXT_MAX_LEN+1));
            }

            /* notify VKB_MSG_DLG_FINISHED message to caller */
            if (NULL != pt_this->pf_fct)
            {
                pt_this->pf_fct(
                        pt_this->pv_tag,
                        VKB_MSG_DLG_FINISHED,
                        NULL,
                        NULL);
            }
        }
            return WDKR_OK;
        case BTN_CURSOR_RIGHT:
        {
            /* Change focus via Right key */
            i4_ret = _vkb_set_focus_item(pt_this, VKB_FOCUS_CHG_RIGHT_KEY, TRUE);
            WDK_CHK_FAIL(i4_ret);
            return WDKR_OK;
        }
        default:
        {
            c_memset(pt_this->aw2s_txt, 0, sizeof(UTF16_T)*(VKB_INPUT_TEXT_MAX_LEN+1));

            i4_ret = c_wgl_do_cmd (h_widget,
                                   WGL_CMD_EB_GET_TEXT,
                                   WGL_PACK (pt_this->aw2s_txt),
                                   WGL_PACK (VKB_INPUT_TEXT_MAX_LEN));

            /* check total char number */
            ui4_len = c_uc_w2s_strlen(pt_this->aw2s_txt);

            if (ui4_len >= (pt_this->ui4_max_char_num)
                || _vkb_view_eb_cursor_at_end(h_widget))
            {
                return WDKR_OK;
            }

            if (_vkb_view_eb_chk_buffer_full(pt_this, NULL))
            {
                return WDKR_OK;
            }
        }
            break;
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

}


static VOID _vkb_view_eb_clr_get_rect(VKB_CONTROL_LOGIC_T *pt_this, GL_RECT_T *pt_rect)
{
    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD )
        || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID)
        || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD)
        || (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU)
        || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_PWD)
        || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WITH_EB_CLEAR)
        || (pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN))
    {
        SET_RECT_BY_SIZE(pt_rect,
                 VKB_WIDTH(VKB_MAIN_FRAME_W-47-39),
                 VKB_HEIGHT(44+17-16),
                 VKB_WIDTH(77),
                 VKB_HEIGHT(61));
    }
    else
    {
        SET_RECT_BY_SIZE(pt_rect,
                 (VKB_EDIT_BOX_X+VKB_EDIT_BOX_W-VKB_WIDTH(47)),
                 VKB_EDIT_BOX_Y,
                 VKB_WIDTH(77),
                 VKB_HEIGHT(61));
    }
}

static INT32 _vkb_view_eb_clear_icon_proc_fct(HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{
    INT32                 i4_ret;
    UINT32                ui4_key_code;
    HANDLE_T              h_vkb_frm;
    VKB_CONTROL_LOGIC_T*  pt_this = NULL;

    if ((h_vkb_frm = _get_cur_attached_vkb_handle()) == NULL_HANDLE)
    {
        i4_ret = c_wgl_get_parent(h_widget, & h_vkb_frm);
        if(i4_ret != WGLR_OK)
        {
           return i4_ret;
        }
    }

    /* 1. Get attach data */
    i4_ret = _vkb_get_attach_data(h_vkb_frm, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if ((WGL_MSG_KEY_DOWN != ui4_msg)&&
        (WGL_MSG_KEY_REPEAT != ui4_msg))
    {
        if (WGL_MSG_GET_FOCUS == ui4_msg)
        {
            //c_wgl_set_alpha(h_widget, 128);
        }
        else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
        {
            //c_wgl_set_alpha(h_widget, 32);
        }

        return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
    }

    /* get key code */
    ui4_key_code = (UINT32)pv_param1;

    if (NULL != pt_this->pf_fct)
    {
        /* notify VKB_MSG_DLG_KEY_INPUT message to caller */
        i4_ret = pt_this->pf_fct(
                            pt_this->pv_tag,
                            VKB_MSG_DLG_KEY_EB_CLEAR,
                            (VOID*)(&ui4_key_code),
                            NULL);

        if (WDK_NO_ACTION == i4_ret)
        {
            return WDKR_OK;
        }
    }

    switch (ui4_key_code)
    {
        case BTN_CURSOR_DOWN:
        {
            /* Change focus via Down key */
            i4_ret = _vkb_set_focus_item(pt_this, VKB_FOCUS_CHG_DOWN_KEY, TRUE);
            WDK_CHK_FAIL(i4_ret);
            return WDKR_OK;
        }

        case BTN_CURSOR_LEFT:
        {
            i4_ret = _vkb_set_focus_item(pt_this, VKB_FOCUS_CHG_LEFT_KEY, TRUE);
            WDK_CHK_FAIL(i4_ret);
            return WDKR_OK;
        }

        case BTN_SELECT:
        case BTN_KB_ENTER:
        {
            c_memset(pt_this->aw2s_txt, 0, sizeof(UTF16_T)*(VKB_INPUT_TEXT_MAX_LEN+1));

            /* update buffer content to editbox widget */
            i4_ret = _vkb_view_editbox_set_text(pt_this, pt_this->aw2s_txt, TRUE);
            WDK_CHK_FAIL(i4_ret);

            /* set focus on edit box */
            pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EDIT_BOX;
            i4_ret = c_wgl_set_focus (pt_this->h_input_editbox, TRUE);
            WDK_CHK_FAIL(i4_ret);

            return WDKR_OK;
        }

        case BTN_CURSOR_UP:
        case BTN_EXIT:
        case BTN_RETURN:
        {
            if (NULL != pt_this->pf_fct)
            {
                /* notify VKB_MSG_DLG_KEY_INPUT message to caller */
                pt_this->pf_fct(
                                pt_this->pv_tag,
                                VKB_MSG_DLG_KEY_INPUT,
                                (VOID*)(&ui4_key_code),
                                NULL);
            }

            return WDKR_OK;
        }

        default:
            break;
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

}

static INT32 _vkb_view_create_eb_clear_icon(VKB_CONTROL_LOGIC_T*    pt_this,
                                         HANDLE_T                h_parent)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect;
    //WGL_INSET_T         t_inset;
    WGL_IMG_INFO_T      t_img_info;

    _vkb_view_eb_clr_get_rect(pt_this, &t_rect);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 _vkb_view_eb_clear_icon_proc_fct,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &(pt_this->t_eb_clear_icon.h_eb_clear_icon));
    WDK_CHK_FAIL(i4_ret);

    /* Set Insets
    t_inset.i4_left     = VKB_WIDTH(0);
    t_inset.i4_right    = VKB_WIDTH(0);
    t_inset.i4_top      = VKB_HEIGHT(0);
    t_inset.i4_bottom   = VKB_HEIGHT(0);
    i4_ret = c_wgl_do_cmd(pt_this->t_eb_clear_icon.h_eb_clear_icon,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    WDK_CHK_FAIL(i4_ret);
*/
    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(pt_this->t_eb_clear_icon.h_eb_clear_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_this->pt_rc_config->h_keypad_eb_clear_img;
    t_img_info.u_img_data.t_standard.t_highlight = pt_this->pt_rc_config->h_keypad_eb_clear_img_hlt;
    t_img_info.u_img_data.t_standard.t_disable   = pt_this->pt_rc_config->h_keypad_eb_clear_img;
    i4_ret = c_wgl_do_cmd(pt_this->t_eb_clear_icon.h_eb_clear_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    WDK_CHK_FAIL(i4_ret);

    /* Set Border images
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_wdk_vkb_big_keypad_hlt_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wdk_vkb_big_keypad_hlt_img;
    t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(pt_this->t_eb_clear_icon.h_eb_clear_icon,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    WDK_CHK_FAIL(i4_ret);*/

    pt_this->t_eb_clear_icon.h_eb_clear_icon_self = pt_this->t_eb_clear_icon.h_eb_clear_icon;

    WDK_CHK_FAIL(c_wgl_set_visibility(pt_this->t_eb_clear_icon.h_eb_clear_icon, WGL_SW_HIDE));

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_create_editbox_ex(VKB_CONTROL_LOGIC_T*    pt_this,
                                         HANDLE_T                h_parent)
{
    INT32               i4_ret = 0;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_EB_KEY_MAP_T    t_eb_key_map;
    UTF16_T             w2s_cursor =(UTF16_T) 0x005F; /* underline */

    ui4_style = WGL_STL_EB_MAX_CHAR_64;

    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD ) ||
        (pt_this->ui4_style_mask & VKB_STYLE_MASK_PASSWORD) ||
        (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_PWD))
    {
        ui4_style |= WGL_STL_EB_PASSWORD_ESC_LAST;
        ui4_style |= WGL_STL_EB_SHOW_LAST_CHARACTERS;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     VKB_WIDTH(0),
                     VKB_HEIGHT(44),
                     VKB_MAIN_FRAME_W,
                     VKB_HEIGHT(33));
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 _vkb_view_eb_proc_fct_ex,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 & pt_this->h_input_editbox);
    WDK_CHK_FAIL(i4_ret);

    /* Set Insets */
    t_inset.i4_left     = VKB_WIDTH(8);
    t_inset.i4_right    = VKB_WIDTH(8);
    t_inset.i4_top      = VKB_HEIGHT(5);
    t_inset.i4_bottom   = VKB_HEIGHT(0);
    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Cnt Insets */
    t_inset.i4_left     = VKB_WIDTH(2);
    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD)
        || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_PWD)
        || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID))
    {
        t_inset.i4_right    = VKB_WIDTH(12);
    }
    else
    {
        t_inset.i4_right    = VKB_WIDTH(0);
    }
    t_inset.i4_right    += 47;
    t_inset.i4_top      = VKB_HEIGHT(0);
    t_inset.i4_bottom   = VKB_HEIGHT(6);
    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_EB_SET_ALIGN,
                          WGL_PACK(VKB_EDIT_BOX_ALIGNMENT),
                          NULL);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_this->h_input_editbox,
                           WGL_CMD_EB_SET_FOCUS_STATUS,
                           WGL_PACK (TRUE),
                           NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, VKB_EDIT_BOX_FONT_NAME);
    t_fnt_info.e_font_size  = VKB_EDIT_BOX_FONT_SIZE;
    t_fnt_info.e_font_style = VKB_EDIT_BOX_FONT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.i2_width     = VKB_EDIT_BOX_FONT_WIDTH;

    i4_ret = c_wgl_do_cmd (pt_this->h_input_editbox,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set the cursor highlight */
    i4_ret = c_wgl_do_cmd (pt_this->h_input_editbox,
                            WGL_CMD_EB_ENABLE_CURSOR_HT,
                            WGL_PACK (TRUE),
                            NULL);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_this->h_input_editbox,
                             WGL_CMD_EB_SET_CURSOR_CHAR,
                             (VOID*) (&w2s_cursor),/* underline */
                             NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set the text color highlighted by cursor */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = pt_this->pt_rc_config->t_editbox_cursor_clr;
    t_clr_info.u_color_data.t_standard.t_disable   = pt_this->pt_rc_config->t_editbox_cursor_clr;
    t_clr_info.u_color_data.t_standard.t_highlight = pt_this->pt_rc_config->t_editbox_cursor_clr;

    i4_ret = c_wgl_do_cmd (pt_this->h_input_editbox,
                             WGL_CMD_GL_SET_COLOR,
                             WGL_PACK(WGL_CLR_EB_CURSOR),   /* text color highlighted by cursor */
                             WGL_PACK(& t_clr_info));
    WDK_CHK_FAIL(i4_ret);

    /* Set always highlight: this will display cursor even if focus not on editbox. */
    i4_ret = c_wgl_do_cmd (pt_this->h_input_editbox,
                                  WGL_CMD_EB_SET_EXT_ATTR,
                                  WGL_PACK (WGL_EB_ALWAYS_HT),
                                  WGL_PACK (WGL_EB_ALWAYS_HT));
    WDK_CHK_FAIL(i4_ret);

    /* Set txt color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = pt_this->pt_rc_config->t_editbox_txt_clr;
    t_clr_info.u_color_data.t_standard.t_highlight    = pt_this->pt_rc_config->t_editbox_txt_dis_clr;
    t_clr_info.u_color_data.t_standard.t_disable      = pt_this->pt_rc_config->t_editbox_txt_hlt_clr;
    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       =h_g_wdk_vkb_edit_img;
    t_img_info.u_img_data.t_standard.t_highlight    =h_g_wdk_vkb_edit_img;
    t_img_info.u_img_data.t_standard.t_disable      =h_g_wdk_vkb_edit_img;
    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    WDK_CHK_FAIL(i4_ret);

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)64),
                          NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING | WGL_EB_CHAR_SUPPORT | WGL_EB_KEEP_CURSOR_POS),  /*Attr mask*/
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING | WGL_EB_CHAR_SUPPORT | WGL_EB_KEEP_CURSOR_POS)); /*Attr value*/
    WDK_CHK_FAIL(i4_ret);

    /* Set Border images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE;//h_g_wdk_vkb_edit_bk;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;//h_g_wdk_vkb_keypad_bar_hlt_img;
    t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE;//h_g_wdk_vkb_edit_bk;
    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    WDK_CHK_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_backsapce = BTN_CURSOR_LEFT;

    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_create_editbox(VKB_CONTROL_LOGIC_T*    pt_this,
                                      HANDLE_T                h_parent)
{
    INT32                       i4_ret;
    WDK_EDIT_BOX_WIDGET_PARAM_T t_eb_param;

    c_memset (& t_eb_param, 0, sizeof (WDK_EDIT_BOX_WIDGET_PARAM_T));

    t_eb_param.h_parent               = h_parent;
    t_eb_param.ui1_alpha              = VKB_EDIT_BOX_ALPHA;
    t_eb_param.b_visibility           = TRUE;
    t_eb_param.i4_x                   = VKB_EDIT_BOX_X;
    t_eb_param.i4_y                   = VKB_EDIT_BOX_Y;
    t_eb_param.i4_w                   = VKB_EDIT_BOX_W;
    t_eb_param.i4_h                   = VKB_EDIT_BOX_H;
    t_eb_param.ui4_style              = VKB_EDIT_BOX_STYLE;

    t_eb_param.ps_font_name           = VKB_EDIT_BOX_FONT_NAME;
    t_eb_param.e_font_size            = VKB_EDIT_BOX_FONT_SIZE;
    t_eb_param.e_font_style           = VKB_EDIT_BOX_FONT_STYLE;
    t_eb_param.i2_width               = VKB_EDIT_BOX_FONT_WIDTH;

    t_eb_param.ui2_input_limit        = VKB_INPUT_TEXT_MAX_LEN;
    t_eb_param.ui1_align              = VKB_EDIT_BOX_ALIGNMENT;
    t_eb_param.w2s_cursor_char        = 0x005F; /* underline */
    t_eb_param.pt_clr_cur             = & (pt_this->pt_rc_config->t_editbox_cursor_clr);
    t_eb_param.t_clr_txt.pt_enable    = & (pt_this->pt_rc_config->t_editbox_txt_clr);
    t_eb_param.t_clr_txt.pt_disable   = & (pt_this->pt_rc_config->t_editbox_txt_dis_clr);
    t_eb_param.t_clr_txt.pt_highlight = & (pt_this->pt_rc_config->t_editbox_txt_hlt_clr);

    /* insert setting */
    t_eb_param.t_inset_info.i4_left   = VKB_EDIT_BOX_BDR_INSET_L;
    t_eb_param.t_inset_info.i4_right  = VKB_EDIT_BOX_BDR_INSET_R;
    t_eb_param.t_inset_info.i4_top    = VKB_EDIT_BOX_BDR_INSET_T;
    t_eb_param.t_inset_info.i4_bottom = VKB_EDIT_BOX_BDR_INSET_B;

    /* content insert setting */
    t_eb_param.t_cnt_inset.i4_left    = VKB_EDIT_BOX_CNT_INSET_L;
    t_eb_param.t_cnt_inset.i4_right   = VKB_EDIT_BOX_CNT_INSET_R;
    t_eb_param.t_cnt_inset.i4_top     = VKB_EDIT_BOX_CNT_INSET_T;
    t_eb_param.t_cnt_inset.i4_bottom  = VKB_EDIT_BOX_CNT_INSET_B;

    t_eb_param.b_cursor_nav           = TRUE;
    t_eb_param.b_auto_edit            = TRUE;
    t_eb_param.b_img_bk               = TRUE;
    t_eb_param.b_always_hlt_cursor    = TRUE;   /* always display cursor even if focus not on editbox. */

    t_eb_param.t_bk_img.h_enable      = pt_this->pt_rc_config->h_editbox_bk_img;
    t_eb_param.t_bk_img.h_disable     = pt_this->pt_rc_config->h_editbox_bk_dis_img;
    t_eb_param.t_bk_img.h_highlight   = pt_this->pt_rc_config->h_editbox_bk_hlt_img;

    t_eb_param.pf_wdgt_proc           = _vkb_view_eb_proc_fct;
    t_eb_param.ph_created_eb          = & pt_this->h_input_editbox;

    i4_ret = a_wdk_create_editbox_widget (t_eb_param);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_set_text_keymap(HANDLE_T                h_txt_handle)
{
    INT32                 i4_ret;
    WGL_TEXT_KEY_MAP_T    t_key_map;

    /* Clear key map to make sure text widget will notify CURSOR key to its parent frame. */
    t_key_map.ui4_line_up   = 0;
    t_key_map.ui4_line_down = 0;
    t_key_map.ui4_page_up   = 0;
    t_key_map.ui4_page_down = 0;

    i4_ret = c_wgl_do_cmd (h_txt_handle,
                   WGL_CMD_TEXT_SET_KEY_MAP,
                   WGL_PACK (& t_key_map),
                   NULL);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_keypad_set_key_text(VKB_CONTROL_LOGIC_T*    pt_this,
                                           BOOL                    b_repaint)
{
    INT32                   i4_ret;
    UINT8                   ui1_idx_row;
    UINT8                   ui1_idx_col;
    CHAR                    ach_temp[VKB_KEY_CAPTION_MAX_LEN + 1];
    UTF16_T                 w2s_str[VKB_KEY_CAPTION_MAX_LEN + 1];
    VKB_KEYPAD_KEY_ITEM_T*  pt_keypad_key;

    /* Set caption for keypad key text widget -- normal key */
    for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM; ui1_idx_row++)
    {
        for (ui1_idx_col=0; ui1_idx_col<VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM; ui1_idx_col++)
        {
            c_memset(ach_temp, 0, sizeof(ach_temp));
            c_memset(w2s_str, 0, sizeof(w2s_str));

            pt_keypad_key = & (pt_this->aat_keypad_normal_key[ui1_idx_row][ui1_idx_col]);

            i4_ret = _vkb_view_keypad_get_key_caption(pt_this, pt_keypad_key, ach_temp);
            WDK_CHK_FAIL(i4_ret);

            if(ach_temp[0] == (CHAR)0xF7)
            {
                w2s_str[0] = 0x00F7;
            }
            else if(ach_temp[0] == (CHAR)0xB7)
            {
                w2s_str[0] = 0x00B7;
            }
            else if(ach_temp[0] == (CHAR)0xB0)
            {
                w2s_str[0] = 0x00B0;
            }
            else
            {
                c_uc_ps_to_w2s (ach_temp, w2s_str, VKB_KEY_CAPTION_MAX_LEN);
            }

            i4_ret = a_wdk_text_set_text(
                            pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col],
                            w2s_str);
            WDK_CHK_FAIL(i4_ret);
        }
    }

    /* Set caption for keypad key text widget -- ctrl key */
    for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_CTRL_KEY_TEXT_NUM; ui1_idx_row++)
    {
        c_memset(ach_temp, 0, sizeof(ach_temp));
        c_memset(w2s_str, 0, sizeof(w2s_str));

        pt_keypad_key = & (pt_this->at_keypad_ctrl_key[ui1_idx_row]);

        i4_ret = _vkb_view_keypad_get_key_caption(pt_this, pt_keypad_key, ach_temp);
        WDK_CHK_FAIL(i4_ret);

        c_uc_ps_to_w2s (ach_temp, w2s_str, VKB_KEY_CAPTION_MAX_LEN);
    #ifdef APP_VKB_SUPPORT_LATIN_CHAR
        if (VKB_KEYPAD_CTRL_COM_KEY_IDX == ui1_idx_row)
        {
            UTF16_T w2s_tmp[4] = {0x00E4,0x00EA,0x00ED,0x0000};
            //UTF16_T w2s_tmp_cap[4] = {0x00C4,0x00CA,0x00CD,0x0000};

            /*if (pt_this->b_caps_lock)
            {
                c_uc_w2s_strcpy(w2s_str, w2s_tmp_cap);
            }
            else*/
            {
                c_uc_w2s_strcpy(w2s_str, w2s_tmp);
            }
        }
    #else
        /*HIDE .com key by request of customer */
        if((VKB_KEYPAD_CTRL_COM_KEY_IDX == ui1_idx_row) && (pt_this->ui4_style_mask & VKB_STYLE_MASK_NO_COM_KEY))
        {
            c_uc_ps_to_w2s ("", w2s_str, VKB_KEY_CAPTION_MAX_LEN);
        }
    #endif
        i4_ret = a_wdk_text_set_text(
                    pt_this->ah_ctrl_key_txt[ui1_idx_row],
                    w2s_str);
        WDK_CHK_FAIL(i4_ret);
    }

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_main_frm, NULL, TRUE);
        WDK_CHK_FAIL(i4_ret);
    }

    return WDKR_OK;
}


/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_editbox_set_text(VKB_CONTROL_LOGIC_T*    pt_this,
                                        UTF16_T*                pw2s_txt,
                                        BOOL                    b_repaint)
{
    INT32        i4_ret = 0;
    UINT32       ui4_len;

    i4_ret = a_wdk_editbox_set_text(pt_this->h_input_editbox, pw2s_txt);
    WDK_CHK_FAIL(i4_ret);

    /* set cursor position */
    ui4_len = c_uc_w2s_strlen(pt_this->aw2s_txt);
    i4_ret = a_wdk_editbox_set_cursor_pos(pt_this->h_input_editbox, ui4_len);
    WDK_CHK_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_input_editbox, NULL, TRUE);
        WDK_CHK_FAIL(i4_ret);
    }

    return   WDKR_OK;
}

static INT32 _vkb_view_editbox_get_text(VKB_CONTROL_LOGIC_T*    pt_this,
                                        UTF16_T*                pw2s_txt,
                                        SIZE_T                  sz_len)
{
    INT32        i4_ret = 0;

    if (NULL == pt_this || NULL == pw2s_txt || 0 == sz_len)
    {
        return WDKR_INV_ARG;
    }

    i4_ret = c_wgl_do_cmd (pt_this->h_input_editbox,
                           WGL_CMD_EB_GET_TEXT,
                           WGL_PACK (pw2s_txt),
                           WGL_PACK (sz_len));
    WDK_CHK_FAIL(i4_ret);

    return   WDKR_OK;
}


/*-----------------------------------------------------------------------------
* Name:
* Description:
* Inputs: -
* Outputs: -
* Returns:
----------------------------------------------------------------------------*/
static INT32 _vkb_view_ctrl_key_symbol_proc_fct(VOID* pv_tag,
                                                VOID* pv_vkb_ctrl)
{
    INT32                   i4_ret;
    VKB_CONTROL_LOGIC_T*    pt_this = (VKB_CONTROL_LOGIC_T*)pv_vkb_ctrl;

    /* check valid of argument */
    if (NULL_HANDLE == pt_this)
    {
        return WDKR_INV_ARG;
    }

    /* update internal caps_lock status */

    pt_this->b_symbol_page = !pt_this->b_symbol_page;

    i4_ret = c_wgl_enable(pt_this->ah_ctrl_key_txt[VKB_KEYPAD_CTRL_CAPS_KEY_IDX], !pt_this->b_symbol_page);
    WDK_CHK_FAIL(i4_ret);
#ifdef APP_VKB_SUPPORT_LATIN_CHAR
    i4_ret = c_wgl_enable(pt_this->ah_ctrl_key_txt[VKB_KEYPAD_CTRL_LATIN_KEY_IDX], !pt_this->b_symbol_page);
    WDK_CHK_FAIL(i4_ret);
#endif
    /* update text widget */
    i4_ret = _vkb_view_keypad_set_key_text(pt_this, TRUE);
    WDK_CHK_FAIL(i4_ret);

    _vkb_view_play_tts(pt_this,VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY);

    return   WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_reset_ctrl_key_capslock(VKB_CONTROL_LOGIC_T *pt_this, BOOL b_repaint)
{
    INT32                   i4_ret;

    /* check valid of argument */
    if (NULL_HANDLE == pt_this)
    {
        return WDKR_INV_ARG;
    }

    if (VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY == pt_this->t_focus_item.e_type
        || !pt_this->b_caps_lock)
    {
        return WDKR_OK;
    }

    /* update internal caps_lock status */
    pt_this->b_caps_lock = FALSE;

    /* update text widget */
    i4_ret = _vkb_view_keypad_set_key_text(pt_this, b_repaint);
    WDK_CHK_FAIL(i4_ret);

    return   WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_reset_ctrl_key_latinlock(VKB_CONTROL_LOGIC_T *pt_this, BOOL b_repaint)
{
    INT32                   i4_ret = WDKR_OK;
    UINT8                   ui1_i = 0;
    UINT8                   ui1_idx_row;
    UINT8                   ui1_idx_col;

    /* check valid of argument */
    if (NULL_HANDLE == pt_this)
    {
        return WDKR_INV_ARG;
    }

    if (VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY == pt_this->t_focus_item.e_type
        || (!pt_this->b_latin_lock && !pt_this->b_latin_expand))
    {
        return WDKR_OK;
    }

    /* update internal caps_lock status */
    pt_this->b_latin_lock= FALSE;
    pt_this->b_latin_expand = FALSE;

    for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM; ui1_idx_row++)
    {
        for (ui1_idx_col=0; ui1_idx_col<VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM; ui1_idx_col++)
        {
            i4_ret = c_wgl_enable(pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col], TRUE);
            WDK_CHK_FAIL(i4_ret);
        }
    }

    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = aui1_latin_offset[pt_this->ui1_cur_latin_key_idx][1];

    if ((pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row < VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM)&&
        (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col < VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM))
    {
        i4_ret = c_wgl_set_focus (pt_this->aah_normal_key_txt[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row][pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col],
                                  FALSE);
        WDK_CHK_FAIL(i4_ret);
    }

    /* Enable ctrl keys */
    for (ui1_i = 0; ui1_i < VKB_KEYPAD_CTRL_KEY_TEXT_NUM; ui1_i++)
    {
        i4_ret = c_wgl_enable(pt_this->ah_ctrl_key_txt[ui1_i], TRUE);
        WDK_CHK_FAIL(i4_ret);
    }

    /* update text widget */
    i4_ret = _vkb_view_keypad_set_key_text(pt_this, b_repaint);
    WDK_CHK_FAIL(i4_ret);

    return   WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_ctrl_key_capslock_proc_fct(VOID* pv_tag,
                                                  VOID* pv_vkb_ctrl)
{
    INT32                   i4_ret;
    VKB_CONTROL_LOGIC_T*    pt_this = (VKB_CONTROL_LOGIC_T*)pv_vkb_ctrl;

    /* check valid of argument */
    if (NULL_HANDLE == pt_this)
    {
        return WDKR_INV_ARG;
    }

    /* update internal caps_lock status */
    pt_this->b_caps_lock = !pt_this->b_caps_lock;

    /* update text widget */
    i4_ret = _vkb_view_keypad_set_key_text(pt_this, TRUE);
    WDK_CHK_FAIL(i4_ret);

    return   WDKR_OK;
}

#ifdef APP_VKB_SUPPORT_LATIN_CHAR
static BOOL _vkb_view_normal_key_is_latin(UINT8 ui1_idx_row, UINT8 ui1_idx_col)
{
    BOOL                    b_ret = FALSE;
    UINT8                   ui1_i = 0;

    for (ui1_i = 0; ui1_i < VKB_KEYPAD_LATIN_KEY_TEXT_NUM; ui1_i++)
    {
        if (ui1_idx_row == aui1_latin_offset[ui1_i][0]
            && ui1_idx_col == aui1_latin_offset[ui1_i][1])
        {
            b_ret = TRUE;
            break;
        }
    }

    return b_ret;
}

/*-----------------------------------------------------------------------------
* Name:
* Description:
* Inputs: -
* Outputs: -
* Returns:
----------------------------------------------------------------------------*/
static INT32 _vkb_view_ctrl_key_latin_proc_fct(VOID* pv_tag, VOID* pv_vkb_ctrl)
{
    INT32                   i4_ret;
    UINT8                   ui1_idx_row = 0;
    UINT8                   ui1_idx_col = 0;
    BOOL                    b_latin = FALSE;
    VKB_CONTROL_LOGIC_T*    pt_this = (VKB_CONTROL_LOGIC_T*)pv_vkb_ctrl;

    /* check valid of argument */
    if (NULL_HANDLE == pt_this)
    {
        return WDKR_INV_ARG;
    }

    /* update internal latin lock status */

    pt_this->b_latin_lock = !pt_this->b_latin_lock;

    if (!pt_this->b_latin_lock)
    {
        pt_this->b_latin_expand = FALSE;
    }

    for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM; ui1_idx_row++)
    {
        for (ui1_idx_col=0; ui1_idx_col<VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM; ui1_idx_col++)
        {
            b_latin = _vkb_view_normal_key_is_latin(ui1_idx_row, ui1_idx_col);
            if (pt_this->b_latin_lock)
            {
                i4_ret = c_wgl_enable(pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col], b_latin);
                WDK_CHK_FAIL(i4_ret);
            }
            else
            {
                i4_ret = c_wgl_enable(pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col], TRUE);
                WDK_CHK_FAIL(i4_ret);
            }
        }
    }

    i4_ret = c_wgl_enable(pt_this->ah_ctrl_key_txt[VKB_KEYPAD_CTRL_SYMBOL_KEY_IDX], !pt_this->b_latin_lock);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_this->h_main_frm, NULL, TRUE);
    WDK_CHK_FAIL(i4_ret);

    return   WDKR_OK;
}
#endif

static INT32 _vkb_view_show_latin_chars(VOID* pv_vkb_ctrl, BOOL b_repaint)
{
    INT32                   i4_ret;
    UINT8                   ui1_i = 0;
    UINT8                   ui1_idx_row = 0;
    UINT8                   ui1_idx_col = 0;
    UINT8                   ui1_offset = 0;
    UINT8                   ui1_latin_char_num = 0;
    UTF16_T                 w2s_str[10] = {0};
    VKB_CONTROL_LOGIC_T*    pt_this = (VKB_CONTROL_LOGIC_T*)pv_vkb_ctrl;

    UINT8                   aui1_offset[VKB_KEYPAD_LATIN_KEY_TEXT_NUM] = {0,2,3,3,3,4,0,2,5};

    if (NULL == pv_vkb_ctrl)
    {
        return WDKR_FAIL;
    }

    if (!pt_this->b_latin_lock)
    {
        return WDKR_OK;
    }

    /* Disable/Enable Ctrl keys */
    for (ui1_idx_col = 0; ui1_idx_col < VKB_KEYPAD_CTRL_KEY_TEXT_NUM; ui1_idx_col++)
    {
        i4_ret = c_wgl_enable(pt_this->ah_ctrl_key_txt[ui1_idx_col], FALSE);
        WDK_CHK_FAIL(i4_ret);
    }

    ui1_idx_row = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row;
    ui1_idx_col = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col;

    for (ui1_i = 0; ui1_i < VKB_KEYPAD_LATIN_KEY_TEXT_NUM; ui1_i++)
    {
        if (aui1_latin_offset[ui1_i][0] == ui1_idx_row
            && aui1_latin_offset[ui1_i][1] == ui1_idx_col)
        {
            break;
        }
    }

    if (ui1_i >= VKB_KEYPAD_LATIN_KEY_TEXT_NUM)
    {
        DBG_INFO(("%s() Line %d: VKB intenal error!\n", __FUNCTION__, __LINE__));
    }

    ui1_offset = aui1_offset[ui1_i];
    ui1_latin_char_num = c_uc_w2s_strlen(pt_this->at_keypad_latin_key[ui1_i].w2s_latin_char);

    pt_this->ui1_cur_latin_key_idx = ui1_i;
    pt_this->at_keypad_latin_key[ui1_i].ui1_col_offset = ui1_offset;

    for (ui1_idx_row = 0; ui1_idx_row < VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM; ui1_idx_row++)
    {
        for (ui1_idx_col = 0; ui1_idx_col < VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM; ui1_idx_col++)
        {
            if (aui1_latin_offset[ui1_i][0] == ui1_idx_row
                && ui1_offset <= ui1_idx_col
                && ui1_offset + ui1_latin_char_num >= ui1_idx_col)
            {
                c_memset(w2s_str, 0, sizeof(w2s_str));

                i4_ret = c_wgl_enable(pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col], TRUE);
                WDK_CHK_FAIL(i4_ret);

                if (ui1_offset + ui1_latin_char_num == ui1_idx_col)
                {
                    c_uc_w2s_strcpy(w2s_str, L"<<");
                    a_wdk_text_set_text(pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col],
                                        w2s_str);
                }
                else
                {
                    if (pt_this->b_caps_lock)
                    {
                        w2s_str[0] = pt_this->at_keypad_latin_key[ui1_i].w2s_latin_char_in_capslock[ui1_idx_col-ui1_offset];
                        a_wdk_text_set_text(pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col], w2s_str);
                    }
                    else
                    {
                        w2s_str[0] = pt_this->at_keypad_latin_key[ui1_i].w2s_latin_char[ui1_idx_col-ui1_offset];
                        a_wdk_text_set_text(pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col], w2s_str);
                    }
                }

            }
            else
            {
                i4_ret = c_wgl_enable(pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col], FALSE);
                WDK_CHK_FAIL(i4_ret);
            }
        }
    }

    pt_this->b_latin_expand = TRUE;

    c_wgl_set_focus(pt_this->aah_normal_key_txt[aui1_latin_offset[ui1_i][0]][ui1_offset],
                    WGL_NO_AUTO_REPAINT);

    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = ui1_offset;

    /* Disable ctrl keys */
    for (ui1_i = 0; ui1_i < VKB_KEYPAD_CTRL_KEY_TEXT_NUM; ui1_i++)
    {
        i4_ret = c_wgl_enable(pt_this->ah_ctrl_key_txt[ui1_i], FALSE);
        WDK_CHK_FAIL(i4_ret);
    }

    if (b_repaint)
    {
        c_wgl_repaint(pt_this->h_main_frm, NULL, TRUE);
    }

    return WDKR_OK;

}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_ctrl_key_backspace_proc_fct(VOID* pv_tag,
                                                   VOID* pv_vkb_ctrl)
{
    INT32                   i4_ret;
    UINT32                  ui4_len;
    VKB_CONTROL_LOGIC_T*    pt_this = (VKB_CONTROL_LOGIC_T*)pv_vkb_ctrl;

    /* check valid of argument */
    if (NULL_HANDLE == pt_this)
    {
        return WDKR_INV_ARG;
    }

    /* check total char number */
    ui4_len = c_uc_w2s_strlen(pt_this->aw2s_txt);
    if ((ui4_len > 0)&& (ui4_len < sizeof(pt_this->aw2s_txt)/sizeof(UTF16_T)))
    {
        /* delete last character from internal buffer */
        c_uc_w2s_set (pt_this->aw2s_txt, ui4_len-1, (UTF16_T) 0);

        /* update buffer content to editbox widget */
        i4_ret = _vkb_view_editbox_set_text(pt_this, pt_this->aw2s_txt, TRUE);
        WDK_CHK_FAIL(i4_ret);
    }

    return   WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_keypad_get_key_value(VKB_CONTROL_LOGIC_T*    pt_this,
                                            VKB_KEYPAD_KEY_ITEM_T*  pt_keypad_key,
                                            CHAR*                   ps_value)
{
    VKB_KEY_TYPE_T          e_key_type;

    /* check valid of argument */
    if ((NULL_HANDLE == pt_this)||
        (NULL_HANDLE == pt_keypad_key)||
        (NULL_HANDLE == ps_value))
    {
        return WDKR_INV_ARG;
    }

    e_key_type = pt_keypad_key->e_type;

    switch (e_key_type)
    {
        case VKB_KEY_TYPE_SINGLE_INPUT_KEY:
        {
            if(pt_this->b_symbol_page)
            {
                c_sprintf(ps_value, "%c", pt_keypad_key->u.t_single_input_key.ch_value_symbol_page);

            }
            else
            {
                if (pt_this->b_caps_lock)
                {
                    c_sprintf(ps_value, "%c", pt_keypad_key->u.t_single_input_key.ch_value_in_caps_lock);
                }
                else
                {
                    c_sprintf(ps_value, "%c", pt_keypad_key->u.t_single_input_key.ch_value_no_caps_lock);
                }
            }
        }
            break;

        case VKB_KEY_TYPE_COMPOSITE_INPUT_KEY:
        {
            if (pt_this->b_caps_lock)
            {
                c_strcpy(ps_value,
                    pt_keypad_key->u.t_composite_input_key.ach_values_no_caps_lock);
            }
            else
            {
                c_strcpy(ps_value,
                    pt_keypad_key->u.t_composite_input_key.ach_values_in_caps_lock);
            }
        }
            break;

        case VKB_KEY_TYPE_CTRL_KEY:
        {

            if(pt_this->b_symbol_page)
            {
                c_strcpy(ps_value,
                        pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_symbol_page);

            }
            else
            {
                if (pt_this->b_caps_lock)
                {
                    c_strcpy(ps_value,
                        pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_in_caps_lock);
                }
                else
                {
                    c_strcpy(ps_value,
                        pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_no_caps_lock);
                }
            }
        }
            break;
        default:
            break;
    }

    return   WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_keypad_get_key_caption(
                    VKB_CONTROL_LOGIC_T*    pt_this,
                    VKB_KEYPAD_KEY_ITEM_T*  pt_keypad_key,
                    CHAR*                   ps_caption)
{
    VKB_KEY_TYPE_T          e_key_type;

    /* check valid of argument */
    if ((NULL_HANDLE == pt_this)||
        (NULL_HANDLE == pt_keypad_key)||
        (NULL_HANDLE == ps_caption))
    {
        return WDKR_INV_ARG;
    }

    e_key_type = pt_keypad_key->e_type;

    switch (e_key_type)
    {
        case VKB_KEY_TYPE_SINGLE_INPUT_KEY:
        {
            if(pt_this->b_symbol_page)
            {
                c_sprintf(ps_caption, "%c", pt_keypad_key->u.t_single_input_key.ch_value_symbol_page);
            }
            else
            {
                if (pt_this->b_caps_lock)
                {
                    c_sprintf(ps_caption, "%c", pt_keypad_key->u.t_single_input_key.ch_value_in_caps_lock);
                }
                else
                {
                    c_sprintf(ps_caption, "%c", pt_keypad_key->u.t_single_input_key.ch_value_no_caps_lock);
                }
            }
        }
            break;

        case VKB_KEY_TYPE_COMPOSITE_INPUT_KEY:
        {
            if (pt_this->b_caps_lock)
            {
                c_strcpy(ps_caption,
                    pt_keypad_key->u.t_composite_input_key.t_key_ui_descr.ach_captions_in_caps_lock);
            }
            else
            {
                c_strcpy(ps_caption,
                    pt_keypad_key->u.t_composite_input_key.t_key_ui_descr.ach_captions_no_caps_lock);
            }
        }
            break;

        case VKB_KEY_TYPE_CTRL_KEY:
        {

            if(pt_this->b_symbol_page)
            {
                c_strcpy(ps_caption,
                    pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_symbol_page);

            }
            else
            {
                if (pt_this->b_caps_lock)
                {
                    c_strcpy(ps_caption,
                        pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_in_caps_lock);
                }
                else
                {
                    c_strcpy(ps_caption,
                        pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_no_caps_lock);
                }
            }
        }
            break;
        default:
            break;
    }

    return   WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_append_key_value(VKB_CONTROL_LOGIC_T*    pt_this,
                                        VKB_KEYPAD_KEY_ITEM_T*  pt_keypad_key,
                                        BOOL                    b_repaint)
{
    INT32                   i4_ret;
    CHAR                    ach_temp[VKB_KEY_CAPTION_MAX_LEN + 1];
    UTF16_T                 w2s_str_temp[VKB_KEY_CAPTION_MAX_LEN + 1];
    UINT32                  ui4_len;
    UINT32                  ui4_len_temp;
    UINT8                   ui1_key_idx;
    UINT8                   ui1_elem_idx;

    c_memset(ach_temp, 0, sizeof(ach_temp));
    c_memset(w2s_str_temp, 0, sizeof(w2s_str_temp));

    /* check total char number */
    ui4_len = c_uc_w2s_strlen(pt_this->aw2s_txt);
    if (ui4_len >= pt_this->ui4_max_char_num)
    {
        return WDKR_OK;
    }

    if (pt_this->b_latin_lock
        && pt_this->b_latin_expand)
    {
        ui1_key_idx = pt_this->ui1_cur_latin_key_idx;
        ui1_elem_idx = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col - pt_this->at_keypad_latin_key[ui1_key_idx].ui1_col_offset;

        if (ui1_elem_idx >= pt_this->at_keypad_latin_key[ui1_key_idx].ui1_elem_num)
        {
            return WDKR_OK;
        }

        if (FALSE == pt_this->b_caps_lock)
        {
            w2s_str_temp[0] = pt_this->at_keypad_latin_key[ui1_key_idx].w2s_latin_char[ui1_elem_idx];
        }
        else
        {
            w2s_str_temp[0] = pt_this->at_keypad_latin_key[ui1_key_idx].w2s_latin_char_in_capslock[ui1_elem_idx];
        }
    }
    else
    {
        /* get key value */
        i4_ret = _vkb_view_keypad_get_key_value(pt_this, pt_keypad_key, ach_temp);
        WDK_CHK_FAIL(i4_ret);

        if(ach_temp[0] == (CHAR)0xF7)
        {
            w2s_str_temp[0] = 0x00F7;
        }
        else if(ach_temp[0] == (CHAR)0xB7)
        {
            w2s_str_temp[0] = 0x00B7;
        }
        else if(ach_temp[0] == (CHAR)0xB0)
        {
            w2s_str_temp[0] = 0x00B0;
        }
        else
        {
            c_uc_ps_to_w2s (ach_temp, w2s_str_temp, VKB_KEY_CAPTION_MAX_LEN);
        }
    }

    ui4_len_temp = c_uc_w2s_strlen(w2s_str_temp);
    if ((ui4_len + ui4_len_temp) > pt_this->ui4_max_char_num)
    {
        return WDKR_OK;
    }

    if (_vkb_view_eb_chk_buffer_full(pt_this, w2s_str_temp))
    {
        return WDKR_OK;
    }

    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_DIGITAL_ONLY)
        && (ach_temp[0] < 0x30 || ach_temp[0] > 0x39))
    {
        return WDKR_OK;
    }

    /* append key to internal buffer */
    c_uc_w2s_strcat (pt_this->aw2s_txt, w2s_str_temp);

    /* update buffer content to editbox widget */
    i4_ret = _vkb_view_editbox_set_text(pt_this, pt_this->aw2s_txt, b_repaint);
    WDK_CHK_FAIL(i4_ret);

    return   WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_select_key_proc(VKB_CONTROL_LOGIC_T*    pt_this)
{
    INT32                   i4_ret;
    UINT32                  ui4_len;
    UINT8                   ui1_idx_row;
    UINT8                   ui1_idx_col;
    VKB_KEYPAD_KEY_ITEM_T*  pt_keypad_key;

    switch (pt_this->t_focus_item.e_type)
    {
        case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
        {
            /* check total char number */
            ui4_len = c_uc_w2s_strlen(pt_this->aw2s_txt);
            if (ui4_len >= pt_this->ui4_max_char_num)
            {
                return WDKR_OK;
            }

            /* get focus index */
            ui1_idx_row = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row;
            ui1_idx_col = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col;

            if ((ui1_idx_row < VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM) &&
                (ui1_idx_col < VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM))
            {
                if (pt_this->b_latin_lock)
                {
                    if (!pt_this->b_latin_expand)
                    {
                        _vkb_view_show_latin_chars(pt_this, TRUE);
                        break;
                    }
                    else
                    {
                        pt_keypad_key = & (pt_this->aat_keypad_normal_key[ui1_idx_row][ui1_idx_col]);

                        /* update internal buffer and flush editbox widget */
                        i4_ret = _vkb_view_append_key_value(pt_this, pt_keypad_key, TRUE);
                        WDK_CHK_FAIL(i4_ret);

                        _vkb_view_reset_ctrl_key_latinlock(pt_this, TRUE);
                    }
                }
                else
                {
                    pt_keypad_key = & (pt_this->aat_keypad_normal_key[ui1_idx_row][ui1_idx_col]);

                    /* update internal buffer and flush editbox widget */
                    i4_ret = _vkb_view_append_key_value(pt_this, pt_keypad_key, TRUE);
                    WDK_CHK_FAIL(i4_ret);
                }
            }

            _vkb_view_reset_ctrl_key_capslock(pt_this, TRUE);
        }
            break;

        case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
        {
            /* focus on ctrl key */
            ui1_idx_row = pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx;
            if (ui1_idx_row < VKB_KEYPAD_CTRL_KEY_TEXT_NUM)
            {
                pt_keypad_key = & (pt_this->at_keypad_ctrl_key[ui1_idx_row]);

                switch (pt_keypad_key->e_type)
                {
                    case VKB_KEY_TYPE_SINGLE_INPUT_KEY:
                    case VKB_KEY_TYPE_COMPOSITE_INPUT_KEY:
                    {
                        /* update internal buffer and flush editbox widget */
                        i4_ret = _vkb_view_append_key_value(pt_this, pt_keypad_key, TRUE);
                        WDK_CHK_FAIL(i4_ret);
                    }
                        break;

                    case VKB_KEY_TYPE_CTRL_KEY:
                    {
                        if (pt_keypad_key->u.t_ctrl_key.pf_fct != NULL)
                        {
                            pt_keypad_key->u.t_ctrl_key.pf_fct(
                                    pt_keypad_key->u.t_ctrl_key.pv_tag,
                                    pt_this);
                        }
                    }
                        break;

                    default:
                        break;
                }
            }
        #ifdef APP_VKB_SUPPORT_LATIN_CHAR
            if (VKB_KEYPAD_CTRL_LATIN_KEY_IDX != ui1_idx_row)
            {
                _vkb_view_reset_ctrl_key_capslock(pt_this, TRUE);
            }
        #endif
        }
            break;

        case VKB_FOCUS_WIDGET_BTN_OK:
        {
            /* notify VKB_MSG_DLG_FINISHED message to caller */
            if (NULL != pt_this->pf_fct)
            {
                pt_this->pf_fct(
                        pt_this->pv_tag,
                        VKB_MSG_DLG_FINISHED,
                        NULL,
                        NULL);
            }

            _vkb_view_reset_ctrl_key_capslock(pt_this, TRUE);
        }
            break;

        case VKB_FOCUS_WIDGET_BTN_CANCEL:
        {
            /* notify VKB_MSG_DLG_CANCEL message to caller */
            if (NULL != pt_this->pf_fct)
            {
                pt_this->pf_fct(
                        pt_this->pv_tag,
                        VKB_MSG_DLG_CANCEL,
                        NULL,
                        NULL);
            }
            _vkb_view_reset_ctrl_key_capslock(pt_this, TRUE);
        }
            break;

        default:
            break;

    }

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_view_txt_wdgt_proc_fct(HANDLE_T    h_widget,
                                         UINT32      ui4_msg,
                                         VOID*       pv_param1,
                                         VOID*       pv_param2)
{
    INT32                 i4_ret;
    UINT32                ui4_key_code;
    HANDLE_T              h_vkb_frm;
    VKB_CONTROL_LOGIC_T*  pt_this;
    wgl_widget_proc_fct   pf_wgl_proc = NULL;


    if ((h_vkb_frm = _get_cur_attached_vkb_handle()) == NULL_HANDLE)
    {
        i4_ret = c_wgl_get_parent(h_widget, & h_vkb_frm);
        if(i4_ret != WGLR_OK)
        {
           return i4_ret;
        }
    }

    /* 1. Get attach data */
    i4_ret = _vkb_get_attach_data(h_vkb_frm, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if ((WGL_MSG_KEY_DOWN != ui4_msg) &&
        (WGL_MSG_KEY_REPEAT != ui4_msg))
    {
       /*DTV02170271:
        [Step 3] Enter ,then move cursor down to OK 
        [Step 4] Then back,find DUT will read Number(ex:1)(NG2) 
       */
       if(pt_this != NULL)
       {
        if (WGL_MSG_GET_FOCUS == ui4_msg)
        {
            //_vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY);
            _vkb_view_play_tts(pt_this, pt_this->t_focus_item.e_type);
        }

        if (WGL_MSG_LOSE_FOCUS == ui4_msg)
        {
            //_vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY);
            _vkb_view_play_tts(pt_this, pt_this->t_focus_item.e_type);
        }
       }

        return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
    }

    /* get key code */
    ui4_key_code = (UINT32)pv_param1;

    if (NULL != pt_this->pf_fct)
    {
        if ((pt_this->ui4_style_mask != VKB_STYLE_MASK_WZD_DROP_DOWN) ||
            (ui4_key_code != CUSTOM_BTN_VKB_SELECT))
        {
            /* notify VKB_MSG_DLG_KEY_INPUT message to caller */
            i4_ret = pt_this->pf_fct(
                                pt_this->pv_tag,
                                VKB_MSG_DLG_KEY_INPUT,
                                (VOID*)(&ui4_key_code),
                                NULL);

            if (WDK_NO_ACTION == i4_ret)
            {
                return WDKR_OK;
            }
        }
    }

    if (((BTN_DIGIT_0 <= ui4_key_code) && (BTN_DIGIT_9 >= ui4_key_code)) ||
        ((BTN_KB_NULL <= ui4_key_code) && (BTN_KB_HYPER >= ui4_key_code)))
    {
        i4_ret = c_wgl_set_focus (pt_this->h_input_editbox, TRUE);
        WDK_CHK_FAIL(i4_ret);

        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EDIT_BOX;

        /* when cursor down, foucs on 'e' */
        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row = 0;
        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = 4;

        if (c_uc_w2s_strlen(pt_this->aw2s_txt) >= pt_this->ui4_max_char_num)
        {
            return WDKR_OK;
        }

        if (_vkb_view_eb_chk_buffer_full(pt_this, NULL))
        {
            return WDKR_OK;
        }

        c_wgl_get_widget_proc(pt_this->h_input_editbox, &pf_wgl_proc);
        if (pf_wgl_proc != NULL
            && pt_this->b_eb_attached)
        {
            return pf_wgl_proc(pt_this->h_input_editbox, ui4_msg, pv_param1, pv_param2);
        }
        else
        {
            return c_wgl_default_msg_proc (pt_this->h_input_editbox, ui4_msg, pv_param1, pv_param2);
        }
    }

    switch (ui4_key_code)
    {
        case BTN_CURSOR_UP:
        {
            /* Change focus via UP key */
            i4_ret = _vkb_set_focus_item(pt_this, VKB_FOCUS_CHG_UP_KEY, TRUE);
            WDK_CHK_FAIL(i4_ret);
        }
        break;

        case BTN_CURSOR_DOWN:
        {
            /* Change focus via Down key */
            i4_ret = _vkb_set_focus_item(pt_this, VKB_FOCUS_CHG_DOWN_KEY, TRUE);
            WDK_CHK_FAIL(i4_ret);
        }
        break;

        case BTN_CURSOR_LEFT:
        {
            /* Change focus via Left key */
            i4_ret = _vkb_set_focus_item(pt_this, VKB_FOCUS_CHG_LEFT_KEY, TRUE);
            WDK_CHK_FAIL(i4_ret);
        }
        break;

        case BTN_CURSOR_RIGHT:
        {
            /* Change focus via Right key */
            i4_ret = _vkb_set_focus_item(pt_this, VKB_FOCUS_CHG_RIGHT_KEY, TRUE);
            WDK_CHK_FAIL(i4_ret);
        }
        break;

        case CUSTOM_BTN_VKB_SELECT:
        {
            /* VKB_SELECT key process */
            i4_ret = _vkb_view_select_key_proc(pt_this);
            WDK_CHK_FAIL(i4_ret);
            if (((pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_OK) ||
                (pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_CANCEL)) &&
                (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_DROP_DOWN))
            {
                return WDKR_OK;
            }

            if (NULL != pt_this->pf_fct)
            {
                if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_DROP_DOWN)
                    || (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN))
                {
                    /* notify VKB_MSG_DLG_KEY_INPUT message to caller */
                    i4_ret = pt_this->pf_fct(
                                        pt_this->pv_tag,
                                        VKB_MSG_DLG_KEY_INPUT,
                                        (VOID*)(&ui4_key_code),
                                        NULL);

                    if (WDK_NO_ACTION == i4_ret)
                    {
                        return WDKR_OK;
                    }
                }
            }
        }
        break;
    }

    return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}


/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_set_attach_data(
                    HANDLE_T                h_vkb_handle,
                    VKB_CONTROL_LOGIC_T*    pt_vkb_ctrl)
{
    INT32 i4_ret = WDKR_OK;

    i4_ret = c_wgl_do_cmd(h_vkb_handle,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_vkb_ctrl),
                          NULL);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_get_attach_data(
                    HANDLE_T                h_vkb_handle,
                    VKB_CONTROL_LOGIC_T**   ppt_vkb_ctrl)
{
    INT32 i4_ret;

    /* set a initial value */
    *ppt_vkb_ctrl = NULL;

    i4_ret = c_wgl_do_cmd(h_vkb_handle,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_vkb_ctrl),
                          NULL);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_init_internal_ctrl_data(
                    VKB_INIT_T*             pt_init_data,
                    VKB_CONTROL_LOGIC_T*    pt_this)
{
    UINT8                   ui1_idx_row;
    UINT8                   ui1_idx_col;
    CHAR                    ch_temp;
    VKB_KEY_TYPE_T          e_key_type;
    VKB_KEYPAD_KEY_ITEM_T*  pt_keypad_key;

    /* Customization part: caption table of normal key in keypad */
    CHAR        aach_nor_key_cus_caption[VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM][VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM] =
        {
            {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'},
            {'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r'},
            {'s', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0'},
            {'1', '2', '3', '4', '5', '6', '7', '8', '9'}
        };

    CHAR        aach_nor_key_symbol_page[VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM][VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM] =
        {
            {'$', '^', '(', ')', '{', '}', '~', '`', '|'},
            {',', '&', '[', ']', '^', '%', 247, '#', 183},
            {'!', '?', '<', '>', ':', ';', '+', '*', 176},
            {'.', '@',  92, '/',  39, '"', '-', '=', '_'}
        };

    UTF16_T     w2s_latin_key_values[VKB_KEYPAD_LATIN_KEY_TEXT_NUM][VKB_LATIN_KEY_MAX_ELEM_NUM] =
        {
            {0x0061,0x00E0,0x00E1,0x00E2,0x00E3,0x00E4,0x00E5,0x00E6,0x0000},
            {0x0063,0x00E7,0x0000},
            {0x0064,0x00F0,0x00FE,0x0000},
            {0x0065,0x00E8,0x00E9,0x00EA,0x00EB,0x0000},
            {0x0069,0x00EC,0x00ED,0x00EE,0x00EF,0x0000},
            {0x006E,0x00F1,0x0000},
            {0x006F,0x00F2,0x00F3,0x00F4,0x00F5,0x00F6,0x00F8,0x0153,0x0000},
            {0x0075,0x00F9,0x00FA,0x00FB,0x00FC,0x0000},
            {0x0079,0x00FD,0x00FF,0x0000}
        };

    UTF16_T     w2s_latin_key_values_in_capslock[VKB_KEYPAD_LATIN_KEY_TEXT_NUM][VKB_LATIN_KEY_MAX_ELEM_NUM] =
        {
            {0x0041,0x00C0,0x00C1,0x00C2,0x00C3,0x00C4,0x00C5,0x00C6,0x0000},
            {0x0043,0x00C7,0x0000},
            {0x0044,0x00D0,0x00DE,0x0000},
            {0x0045,0x00C8,0x00C9,0x00CA,0x00CB,0x0000},
            {0x0049,0x00CC,0x00CD,0x00CE,0x00CF,0x0000},
            {0x004E,0x00D1,0x0000},
            {0x004F,0x00D2,0x00D3,0x00D4,0x00D5,0x00D6,0x00D8,0x0152,0x0000},
            {0x0055,0x00D9,0x00DA,0x00DB,0x00DC,0x0000},
            {0x0059,0x00DD,0x00DF,0x0000}
        };


    /* Customization part: caption table of ctrl key in keypad */
    CHAR        aach_ctrl_key_cus_caption[VKB_KEYPAD_CTRL_KEY_TEXT_NUM][VKB_KEY_CAPTION_MAX_LEN] =
        {
            ".@#",
            " ",
            ".com",
            "Space",
            " "
        };
    CHAR        aach_ctrl_key_cus_caption_in_capslock[VKB_KEYPAD_CTRL_KEY_TEXT_NUM][VKB_KEY_CAPTION_MAX_LEN] =
        {
            ".@#",
            " ",
            ".com",
            "Space",
            " "
        };
    CHAR        aach_ctrl_key_cus_caption_symbol_page[VKB_KEYPAD_CTRL_KEY_TEXT_NUM][VKB_KEY_CAPTION_MAX_LEN] =
        {
            "abc",
            " ",
            ".com",
            "Space",
            " "
        };

    CHAR        aach_ctrl_key_cus_values[VKB_KEYPAD_CTRL_KEY_TEXT_NUM][VKB_KEY_CAPTION_MAX_LEN] =
        {
            "NULL",
            "NULL",
            ".COM",
            " ",
            "NULL"
        };
    CHAR        aach_ctrl_key_cus_values_in_capslock[VKB_KEYPAD_CTRL_KEY_TEXT_NUM][VKB_KEY_CAPTION_MAX_LEN] =
        {
            "NULL",
            "NULL",
            ".com",
            " ",
            "NULL"
        };
    VKB_KEY_TYPE_T   ae_ctrl_key_cus_type[VKB_KEYPAD_CTRL_KEY_TEXT_NUM] =
        {
            VKB_KEY_TYPE_CTRL_KEY,
            VKB_KEY_TYPE_CTRL_KEY,
        #ifdef APP_VKB_SUPPORT_LATIN_CHAR
            VKB_KEY_TYPE_CTRL_KEY,              /* CapsLock key */
        #else
            VKB_KEY_TYPE_COMPOSITE_INPUT_KEY,   /* CapsLock key */
        #endif
            VKB_KEY_TYPE_COMPOSITE_INPUT_KEY,   /* Space key */
            VKB_KEY_TYPE_CTRL_KEY               /* Backspace key */
        };

    /* Set the style mask */
    pt_this->ui4_style_mask = pt_init_data->ui4_style_mask;

    /* Init internal control variable */
    pt_this->ui4_max_char_num  = VKB_INPUT_TEXT_MAX_LEN;
    pt_this->b_caps_lock       = FALSE;          /* Default Caps_Lock = off */
    pt_this->b_symbol_page     = FALSE;

    /* Init keypad normal key */
    for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM; ui1_idx_row++)
    {
        for (ui1_idx_col=0; ui1_idx_col<VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM; ui1_idx_col++)
        {
            ch_temp = aach_nor_key_cus_caption[ui1_idx_row][ui1_idx_col];
            pt_keypad_key = & (pt_this->aat_keypad_normal_key[ui1_idx_row][ui1_idx_col]);

            pt_keypad_key->e_type = VKB_KEY_TYPE_SINGLE_INPUT_KEY;
            pt_keypad_key->u.t_single_input_key.ch_value_no_caps_lock = ch_temp;
            pt_keypad_key->u.t_single_input_key.ch_value_symbol_page = aach_nor_key_symbol_page[ui1_idx_row][ui1_idx_col];
            if ((ch_temp >= 'a') && (ch_temp <= 'z'))
            {
                /* convert to upper alpha */
                pt_keypad_key->u.t_single_input_key.ch_value_in_caps_lock = ch_temp - 32;
            }
            else
            {
                /* digital key */
                pt_keypad_key->u.t_single_input_key.ch_value_in_caps_lock = ch_temp;
            }

        }
    }

    /* Init keypad ctrl key caption */
    for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_CTRL_KEY_TEXT_NUM; ui1_idx_row++)
    {
        e_key_type = ae_ctrl_key_cus_type[ui1_idx_row];
        pt_keypad_key = & (pt_this->at_keypad_ctrl_key[ui1_idx_row]);

        switch (e_key_type)
        {
            case VKB_KEY_TYPE_SINGLE_INPUT_KEY:
            {
                pt_keypad_key->e_type = VKB_KEY_TYPE_SINGLE_INPUT_KEY;
                pt_keypad_key->u.t_single_input_key.ch_value_no_caps_lock = aach_ctrl_key_cus_caption[ui1_idx_row][0];
                pt_keypad_key->u.t_single_input_key.ch_value_in_caps_lock = aach_ctrl_key_cus_caption_in_capslock[ui1_idx_row][0];
            }
                break;

            case VKB_KEY_TYPE_COMPOSITE_INPUT_KEY:
            {
                pt_keypad_key->e_type = VKB_KEY_TYPE_COMPOSITE_INPUT_KEY;
                /* value */
                c_strcpy(pt_keypad_key->u.t_composite_input_key.ach_values_no_caps_lock,
                            aach_ctrl_key_cus_values[ui1_idx_row]);
                c_strcpy(pt_keypad_key->u.t_composite_input_key.ach_values_in_caps_lock,
                            aach_ctrl_key_cus_values_in_capslock[ui1_idx_row]);

                /* caption */
                c_strcpy(pt_keypad_key->u.t_composite_input_key.t_key_ui_descr.ach_captions_no_caps_lock,
                            aach_ctrl_key_cus_caption[ui1_idx_row]);
                c_strcpy(pt_keypad_key->u.t_composite_input_key.t_key_ui_descr.ach_captions_in_caps_lock,
                            aach_ctrl_key_cus_caption_in_capslock[ui1_idx_row]);
            }
                break;

            case VKB_KEY_TYPE_CTRL_KEY:
            {
                pt_keypad_key->e_type = VKB_KEY_TYPE_CTRL_KEY;
                /* caption */
                c_strcpy(pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_no_caps_lock,
                            aach_ctrl_key_cus_caption[ui1_idx_row]);
                c_strcpy(pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_in_caps_lock,
                            aach_ctrl_key_cus_caption_in_capslock[ui1_idx_row]);
                c_strcpy(pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_symbol_page,
                            aach_ctrl_key_cus_caption_symbol_page[ui1_idx_row]);
            }
                break;

            default:
                break;
        }
    }

    /* Init Latin Keys */
    VKB_KEYPAD_LATIN_KEY_ITEM *pt_latin_item = NULL;

    pt_this->b_latin_lock = FALSE;
    pt_this->b_latin_expand = FALSE;

    for (ui1_idx_row=0; ui1_idx_row < VKB_KEYPAD_LATIN_KEY_TEXT_NUM; ui1_idx_row++)
    {
        pt_latin_item = &pt_this->at_keypad_latin_key[ui1_idx_row];

        pt_latin_item->ui1_row_offset = aui1_latin_offset[ui1_idx_row][0];
        pt_latin_item->ui1_col_offset = aui1_latin_offset[ui1_idx_row][1];
        pt_latin_item->ui1_elem_num = c_uc_w2s_strlen(w2s_latin_key_values[ui1_idx_row]);

        c_memcpy(pt_latin_item->w2s_latin_char,
                &w2s_latin_key_values[ui1_idx_row][0],
                sizeof(pt_latin_item->w2s_latin_char));

        c_memcpy(pt_latin_item->w2s_latin_char_in_capslock,
                &w2s_latin_key_values_in_capslock[ui1_idx_row][0],
                sizeof(pt_latin_item->w2s_latin_char_in_capslock));
    }

    /* Init keypad ctrl key callback: Symbol/Character page key */
    pt_keypad_key = & (pt_this->at_keypad_ctrl_key[VKB_KEYPAD_CTRL_SYMBOL_KEY_IDX]);
    pt_keypad_key->u.t_ctrl_key.pf_fct = _vkb_view_ctrl_key_symbol_proc_fct;
    pt_keypad_key->u.t_ctrl_key.pv_tag = NULL;


    /* Init keypad ctrl key callback: CapsLock key */
    pt_keypad_key = & (pt_this->at_keypad_ctrl_key[VKB_KEYPAD_CTRL_CAPS_KEY_IDX]);
    pt_keypad_key->u.t_ctrl_key.pf_fct = _vkb_view_ctrl_key_capslock_proc_fct;
    pt_keypad_key->u.t_ctrl_key.pv_tag = NULL;

#ifdef APP_VKB_SUPPORT_LATIN_CHAR
    /* Init keypad ctrl key callback: Latin key */
    pt_keypad_key = & (pt_this->at_keypad_ctrl_key[VKB_KEYPAD_CTRL_LATIN_KEY_IDX]);
    pt_keypad_key->u.t_ctrl_key.pf_fct = _vkb_view_ctrl_key_latin_proc_fct;
    pt_keypad_key->u.t_ctrl_key.pv_tag = NULL;
#endif

    /* Init keypad ctrl key callback: Backspace key */
    pt_keypad_key = & (pt_this->at_keypad_ctrl_key[VKB_KEYPAD_CTRL_DELETE_KEY_IDX]);
    pt_keypad_key->u.t_ctrl_key.pf_fct = _vkb_view_ctrl_key_backspace_proc_fct;
    pt_keypad_key->u.t_ctrl_key.pv_tag = NULL;

    /* Init the callback information */
    pt_this->pf_fct = pt_init_data->pf_data_change_fct;
    pt_this->pv_tag = pt_init_data->pv_tag;

    return WDKR_OK;
}

#ifdef APP_VKB_SUPPORT_LATIN_CHAR
static UINT8 _vkb_get_latin_key_idx(UINT8 ui1_row, UINT8 ui1_col)
{
    UINT8 ui1_i = 0;

    for (ui1_i = 0; ui1_i < VKB_KEYPAD_LATIN_KEY_TEXT_NUM; ui1_i++)
    {
        if (ui1_row == aui1_latin_offset[ui1_i][0]
            && ui1_col == aui1_latin_offset[ui1_i][1])
        {
            break;
        }
    }

    if (ui1_i >= VKB_KEYPAD_LATIN_KEY_TEXT_NUM)
    {
        ui1_i = 0;
        DBG_INFO(("<VKB> Get latin key index fail! Return 0.\n"));
    }

    return ui1_i;
}

static INT32 _vkb_set_focus_item_in_latin_expand(VKB_CONTROL_LOGIC_T* pt_this,
                                                   VKB_FOCUS_CHG_TYPE_T e_chg_type,
                                                   BOOL                 b_repaint)
{
    INT32 i4_ret = WDKR_OK;
    VKB_FOCUS_WIDGET_T e_key_type = pt_this->t_focus_item.e_type;
    //UINT8 ui1_row;
    UINT8 ui1_col;
    UINT8 ui1_cur_latin_key_idx = 0;

    if (FALSE == pt_this->b_latin_expand)
    {
        return WDK_NO_ACTION;
    }

    switch (e_key_type)
    {
        case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
        {
            //ui1_row = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row;
            ui1_col = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col;
            //ui1_cur_latin_key_idx = _vkb_get_latin_key_idx(ui1_row, ui1_col);
            break;
        }
        default:
        {
            //ui1_row = 0;
            ui1_col = 0;
            break;
        }
    }

    ui1_cur_latin_key_idx = pt_this->ui1_cur_latin_key_idx;

    if (VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY == e_key_type)
    {
        switch (e_chg_type)
        {
            case VKB_FOCUS_CHG_UP_KEY:
            {
                if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD)||
                    (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD)||
                    (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID)||
                    (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU)||
                    (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_PWD)||
                    (pt_this->b_eb_attached))
                {
                    /* in first row: highlight on Edit box */
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EDIT_BOX;
                }
                else if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_DROP_DOWN)
                    || (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN))
                {
                    return WDKR_OK;
                }
                else
                {
                    /* in first row: highlight on BTN_CANCEL */
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_CANCEL;
                }
                break;
            }
            case VKB_FOCUS_CHG_DOWN_KEY:
            {
                if (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN)
                {
                    return WDKR_OK;
                }
                /* focus on OK button */
                pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_OK;
                break;
            }
            case VKB_FOCUS_CHG_LEFT_KEY:
            {
                UINT8 ui1_coll_offset = pt_this->at_keypad_latin_key[ui1_cur_latin_key_idx].ui1_col_offset;
                UINT8 ui1_elem_num = pt_this->at_keypad_latin_key[ui1_cur_latin_key_idx].ui1_elem_num;

                if (ui1_col == ui1_coll_offset)
                {
                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = ui1_coll_offset + ui1_elem_num;
                }
                else
                {
                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col--;
                }

                break;
            }
            case VKB_FOCUS_CHG_RIGHT_KEY:
            {
                UINT8 ui1_coll_offset = pt_this->at_keypad_latin_key[ui1_cur_latin_key_idx].ui1_col_offset;
                UINT8 ui1_elem_num = pt_this->at_keypad_latin_key[ui1_cur_latin_key_idx].ui1_elem_num;

                if (ui1_col == ui1_coll_offset + ui1_elem_num)
                {
                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = ui1_coll_offset;
                }
                else
                {
                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col++;
                }

                break;
            }
            default:
                i4_ret = WDK_NO_ACTION;
                break;
        }

    }
    else if (VKB_FOCUS_WIDGET_EDIT_BOX == e_key_type)
    {
        switch (e_chg_type)
        {
            case VKB_FOCUS_CHG_DOWN_KEY:
            {
                /* focus on first normal key: key-a */
                pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                break;
            }
            case VKB_FOCUS_CHG_RIGHT_KEY:
            {
                if (_vkb_is_eb_clr_hide(pt_this->h_main_frm))
                {
                    //Do Nothing
                }
                else
                {
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EB_CLR;
                }

                break;
            }
            default:
                break;
        }
    }

    else if (VKB_FOCUS_WIDGET_EB_CLR == e_key_type)
    {
        switch (e_chg_type)
        {
            case VKB_FOCUS_CHG_DOWN_KEY:
            {
                pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                break;
            }
            case VKB_FOCUS_CHG_LEFT_KEY:
            {
                if (_vkb_is_eb_clr_hide(pt_this->h_main_frm))
                {
                    //Do Nothing
                }
                else
                {
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EDIT_BOX;
                }

                break;
            }
            default:
                break;
        }
    }

    else if (VKB_FOCUS_WIDGET_BTN_OK == e_key_type)
    {
        switch (e_chg_type)
        {
            case VKB_FOCUS_CHG_DOWN_KEY:
            {
                pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_CANCEL;
                break;
            }
            case VKB_FOCUS_CHG_UP_KEY:
            {
                pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                break;
            }
            default:
                break;
        }
    }
    else if (VKB_FOCUS_WIDGET_BTN_CANCEL == e_key_type)
    {
        switch (e_chg_type)
        {
            case VKB_FOCUS_CHG_UP_KEY:
            {
                pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_OK;
                break;
            }

            default:
                break;
        }
    }
    else
    {
        DBG_INFO(("<VKB> Focus key type incorrect!\n"));
        return WDKR_OK;
    }

    if (i4_ret == WDK_NO_ACTION)
    {
        return WDKR_OK;
    }

    /* set focus depend on internal focus data */
    switch (pt_this->t_focus_item.e_type)
    {
        case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
        {
            /* set focus on keypad normal key */
            if ((pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row < VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM)&&
                (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col < VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM))
            {
                i4_ret = c_wgl_set_focus (pt_this->aah_normal_key_txt[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row][pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col],
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);

                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY);
            }
            break;
        }
        case VKB_FOCUS_WIDGET_BTN_OK:
        {
            if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD)
                || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID))
            {
                break;
            }
            else
            {
                /* set focus on OK button */
                i4_ret = c_wgl_set_focus (pt_this->h_ok_txt,
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);

                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_BTN_OK);
            }
            break;
        }
        case VKB_FOCUS_WIDGET_BTN_CANCEL:
        {
            if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD)||
                (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID))
            {
                return WDKR_OK;
            }
            else
            {
                /* set focus on Cancel button */
                i4_ret = c_wgl_set_focus (pt_this->h_cancel_txt,
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);

                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_BTN_CANCEL);
            }

            break;
        }
        case VKB_FOCUS_WIDGET_EDIT_BOX:
        {
            /* set focus on edit box */
            i4_ret = c_wgl_set_focus (pt_this->h_input_editbox,
                                      b_repaint);
            WDK_CHK_FAIL(i4_ret);

            _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_EDIT_BOX);
            break;
        }

        case VKB_FOCUS_WIDGET_EB_CLR:
        {
            if (FALSE == _vkb_is_eb_clr_hide(pt_this->h_main_frm))
            {
                /* set focus on edit box */
                i4_ret = c_wgl_set_focus (pt_this->t_eb_clear_icon.h_eb_clear_icon,
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);

                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_EB_CLR);
            }
        }
            break;
        default:
            break;
    }

    return i4_ret;
}

static INT32 _vkb_set_focus_item_in_latin_state(VKB_CONTROL_LOGIC_T* pt_this,
                                           VKB_FOCUS_CHG_TYPE_T e_chg_type,
                                           BOOL                 b_repaint)
{
    INT32 i4_ret = WDKR_OK;
    VKB_FOCUS_WIDGET_T e_key_type = pt_this->t_focus_item.e_type;
    UINT8 ui1_row;
    UINT8 ui1_col;
    UINT8 ui1_cur_latin_key_idx = 0;
    UINT8 ui1_next_latin_key_idx = 0;
#define FOCUS_CHG_UP    0
#define FOCUS_CHG_DN    1
#define FOCUS_CHG_LF    2
#define FOCUS_CHG_RT    3

    UINT8 aui1_normal_key_nav_idx[9][4] ={/* up,    down,   left,   right*/
                                            {0,     5,      4,      1},
                                            {0,     5,      0,      2},
                                            {0,     5,      1,      3},
                                            {0,     5,      2,      4},
                                            {0,     6,      3,      0},
                                            {3,     7,      6,      6},
                                            {3,     8,      5,      5},
                                            {5,     0,      8,      8},
                                            {6,     0,      7,      7}
                                         };

    if (pt_this->b_latin_expand)
    {
        i4_ret = _vkb_set_focus_item_in_latin_expand(pt_this, e_chg_type, b_repaint);
        if (WDK_NO_ACTION != i4_ret)
        {
            return i4_ret;
        }
    }

    switch (e_key_type)
    {
        case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
        {
            ui1_row = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row;
            ui1_col = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col;

            ui1_cur_latin_key_idx = _vkb_get_latin_key_idx(ui1_row,ui1_col);
            break;
        }
        case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
        {
            ui1_col = pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx;
            break;
        }
        default:
        {
            ui1_row = 0;
            ui1_col = 0;
            break;
        }
    }

    if (VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY == e_key_type)
    {
        switch (e_chg_type)
        {
            case VKB_FOCUS_CHG_UP_KEY:
            {
                if (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row == 0)
                {
                    i4_ret = WDK_NO_ACTION;
                }
                else
                {
                    ui1_next_latin_key_idx = aui1_normal_key_nav_idx[ui1_cur_latin_key_idx][FOCUS_CHG_UP];

                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row =
                                    aui1_latin_offset[ui1_next_latin_key_idx][0];
                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col =
                                    aui1_latin_offset[ui1_next_latin_key_idx][1];

                    pt_this->ui1_cur_latin_key_idx = ui1_next_latin_key_idx;

                }
                break;
            }
            case VKB_FOCUS_CHG_DOWN_KEY:
            {
                if (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row == 2)
                {
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                    pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx = (ui1_cur_latin_key_idx == 7) ?
                                                                        VKB_KEYPAD_CTRL_CAPS_KEY_IDX :
                                                                        VKB_KEYPAD_CTRL_LATIN_KEY_IDX;
                }
                else
                {
                    ui1_next_latin_key_idx = aui1_normal_key_nav_idx[ui1_cur_latin_key_idx][FOCUS_CHG_DN];

                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row =
                                    aui1_latin_offset[ui1_next_latin_key_idx][0];
                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col =
                                    aui1_latin_offset[ui1_next_latin_key_idx][1];

                    pt_this->ui1_cur_latin_key_idx = ui1_next_latin_key_idx;
                }
                break;
            }
            case VKB_FOCUS_CHG_LEFT_KEY:
            {
                ui1_next_latin_key_idx = aui1_normal_key_nav_idx[ui1_cur_latin_key_idx][FOCUS_CHG_LF];
                pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row =
                                aui1_latin_offset[ui1_next_latin_key_idx][0];
                pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col =
                                aui1_latin_offset[ui1_next_latin_key_idx][1];

                pt_this->ui1_cur_latin_key_idx = ui1_next_latin_key_idx;
                break;
            }
            case VKB_FOCUS_CHG_RIGHT_KEY:
            {
                ui1_next_latin_key_idx = aui1_normal_key_nav_idx[ui1_cur_latin_key_idx][FOCUS_CHG_RT];
                pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row =
                                aui1_latin_offset[ui1_next_latin_key_idx][0];
                pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col =
                                aui1_latin_offset[ui1_next_latin_key_idx][1];

                pt_this->ui1_cur_latin_key_idx = ui1_next_latin_key_idx;
                break;
            }
            default:
                i4_ret = WDK_NO_ACTION;
                break;
        }

    }
    else if (VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY == e_key_type)
    {
        switch (e_chg_type)
        {
            case VKB_FOCUS_CHG_UP_KEY:
            {
                pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row = 2;

                if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx <= 2)
                {
                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = 2;
                }
                else
                {
                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = 6;
                }

                pt_this->ui1_cur_latin_key_idx =
                    _vkb_get_latin_key_idx(
                                            pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row,
                                            pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col
                                          );

                break;
            }
            case VKB_FOCUS_CHG_DOWN_KEY:
            {
                i4_ret = WDK_NO_ACTION;
                break;
            }
            case VKB_FOCUS_CHG_LEFT_KEY:
            {
                if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx == 1)
                {
                    pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx = 4;
                }
                else
                {
                    pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx--;
                }
                break;
            }
            case VKB_FOCUS_CHG_RIGHT_KEY:
            {
                if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx == 4)
                {
                    pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx = 1;
                }
                else
                {
                    pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx++;
                }
                break;
            }
            default:
                break;
        }
    }
    else
    {
        i4_ret = WDK_NO_ACTION;
    }

    if (i4_ret == WDK_NO_ACTION)
    {
        return i4_ret;
    }

    /* set focus depend on internal focus data */
    switch (pt_this->t_focus_item.e_type)
    {
        case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
        {
            /* set focus on keypad normal key */
            if ((pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row < VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM)&&
                (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col < VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM))
            {
                i4_ret = c_wgl_set_focus (pt_this->aah_normal_key_txt[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row][pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col],
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);

                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY);
            }
            break;
        }

        case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
        {
            /* set focus on keypad ctrl key */
            if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx < VKB_KEYPAD_CTRL_KEY_TEXT_NUM)
            {
                i4_ret = c_wgl_set_focus (pt_this->ah_ctrl_key_txt[pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx],
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);

                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY);
            }
            break;
        }

        default:
            break;
    }

    return i4_ret;
}
#endif

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_set_focus_item(VKB_CONTROL_LOGIC_T*    pt_this,    /* IN, OUT */
                                 VKB_FOCUS_CHG_TYPE_T    e_chg_type, /* IN */
                                 BOOL                    b_repaint)
{
    UINT8   ui1_idx = 0;
    INT32   i4_ret;

    i4_ret = _vkb_full_scrn_pad_set_focus_item(pt_this, e_chg_type, b_repaint);
    if (WDK_NO_ACTION != i4_ret)
    {
        return i4_ret;
    }

#ifdef APP_VKB_SUPPORT_LATIN_CHAR
    if (pt_this->b_latin_lock)
    {
        i4_ret = _vkb_set_focus_item_in_latin_state(pt_this, e_chg_type, b_repaint);
        if (WDK_NO_ACTION != i4_ret)
        {
            return i4_ret;
        }
    }
#endif
    /* aui1_ctrl_key_up_nav_idx[2]=3: means when press up on ctrl_key[2], focus change to normal_key[last_row][3] */
    UINT8   aui1_ctrl_key_up_nav_idx[] = {0, 1, 3, 5, 8};

    /* aui1_normal_key_dn_nav_idx[2]=1: means when press dn on normal_key[last_row][2], focus change to ctrl_key[1] */
    UINT8   aui1_normal_key_dn_nav_idx[] = {0, 1, 1, 2, 3, 3, 3, 3, 4};
    UINT8   aui1_normal_key_dn_nav_idx_disable_shift[] = {0, 0, 2, 2, 3, 3, 3, 3, 4};

    switch (e_chg_type)
    {
        case VKB_FOCUS_CHG_INITIAL:
        {
            /* update internal focus data */
            pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
            pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row = 0;
            pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = 0;
        }
            break;

        case VKB_FOCUS_CHG_UP_KEY:
        {
            /* update internal focus data */
            switch (pt_this->t_focus_item.e_type)
            {
                case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
                {
                    /* update internal focus data */
                    if (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row == 0)
                    {
                        if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD)||
                            (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD)||
                            (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID)||
                            (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU)||
                            (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_PWD)||
                            (pt_this->b_eb_attached))
                        {
                            /* in first row: highlight on Edit box */
                            pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EDIT_BOX;
                        }
                        else if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_DROP_DOWN)
                            || (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN))
                        {
                            return WDKR_OK;
                        }
                        else
                        {
                            /* in first row: highlight on BTN_CANCEL */
                            pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_CANCEL;
                        }
                    }
                    else
                    {
                        /* not in first row: highlight on previous row */
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row--;
                    }
                }
                    break;

                case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
                {
                    /* focus on normal key last row */
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row = VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM - 1;

                    if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx < sizeof(aui1_ctrl_key_up_nav_idx)/sizeof(UINT8))
                    {
                        ui1_idx = aui1_ctrl_key_up_nav_idx[pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx];
                        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = ui1_idx;
                    }
                }
                    break;

                case VKB_FOCUS_WIDGET_BTN_OK:
                {
                    /* focus on original ctrl key, do not need update focus index  */
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                }
                    break;

                case VKB_FOCUS_WIDGET_BTN_CANCEL:
                {
                    /* update internal focus data */
                    /* focus on OK button */
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_OK;
                }
                    break;
                case VKB_FOCUS_WIDGET_EDIT_BOX:
                case VKB_FOCUS_WIDGET_EB_CLR:
                {
                    /* highlight on BTN_CANCEL */
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_CANCEL;
                }
                    break;

                default:
                    break;
            }
        }
            break;

        case VKB_FOCUS_CHG_DOWN_KEY:
        {
            /* update internal focus data */
            switch (pt_this->t_focus_item.e_type)
            {
                case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
                {
                    /* update internal focus data */
                    if (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row == VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM - 1)
                    {
                        /* in last row: highlight on ctrl key */
                        if (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col < sizeof (aui1_normal_key_dn_nav_idx))
                        {
                            ui1_idx = aui1_normal_key_dn_nav_idx[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col];
                        }
                        if(pt_this->b_symbol_page)
                        {
                            if (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col < sizeof (aui1_normal_key_dn_nav_idx_disable_shift))
                            {
                                ui1_idx = aui1_normal_key_dn_nav_idx_disable_shift[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col];
                            }
                        #ifdef APP_VKB_SUPPORT_LATIN_CHAR
                            if (ui1_idx == VKB_KEYPAD_CTRL_LATIN_KEY_IDX)
                            {
                                ui1_idx++;
                            }
                        #endif
                        }
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                        pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx = ui1_idx;

                        if((pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx == VKB_KEYPAD_CTRL_COM_KEY_IDX) &&
                           (pt_this->ui4_style_mask & VKB_STYLE_MASK_NO_COM_KEY))
                        {
                            if(pt_this->b_symbol_page)
                            {
                                if(pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col == 2)
                                    pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx = 0;//focus 1st control key
                                else if(pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col == 3)
                                    pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx = 3;//focus to 4th control key
                            }
                            else
                            {
                                pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx --;
                            }
                        }
                    }
                    else
                    {
                        /* not in last row: highlight on next row */
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row++;
                    }
                }
                    break;

                case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
                {
                    if (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN)
                    {
                        return WDKR_OK;
                    }
                    /* focus on OK button */
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_OK;
                }
                    break;

                case VKB_FOCUS_WIDGET_BTN_OK:
                {
                    /* focus on Cancel button */
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_CANCEL;
                }
                    break;

                case VKB_FOCUS_WIDGET_BTN_CANCEL:
                {
                    if (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_DROP_DOWN)
                    {
                        return WDKR_OK;
                    }
                    /* focus on first normal key: key-a */
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row = 0;
                    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = 0;
                }
                    break;

                case VKB_FOCUS_WIDGET_EDIT_BOX:
                case VKB_FOCUS_WIDGET_EB_CLR:
                {
                    /* focus on first normal key: key-a */
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                }
                    break;

                default:
                    break;
            }
        }
            break;

        case VKB_FOCUS_CHG_LEFT_KEY:
        {
            /* update internal focus data */
            switch (pt_this->t_focus_item.e_type)
            {
                case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
                {
                    /* update internal focus data */
                    if (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col == 0)
                    {
                        /* in first col: highlight on last col */
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM - 1;
                    }
                    else
                    {
                        /* not in first col: highlight on previous col */
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col--;
                    }
                }
                    break;

                case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
                {
                    /* update internal focus data */
                    if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx == 0)
                    {
                        /* in first col: highlight on last col */
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                        pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx = VKB_KEYPAD_CTRL_KEY_TEXT_NUM - 1;
                    }
                    else
                    {
                        /* not in first col: highlight on previous col */
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                        pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx--;

                        if((pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx == VKB_KEYPAD_CTRL_COM_KEY_IDX) &&
                           (pt_this->ui4_style_mask & VKB_STYLE_MASK_NO_COM_KEY))
                        {
                            pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx--;
                        }

                        if((pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx == VKB_KEYPAD_CTRL_LATIN_KEY_IDX) &&
                           (pt_this->b_symbol_page))
                        {
                            pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx--;
                        }

                        if((pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx == VKB_KEYPAD_CTRL_CAPS_KEY_IDX) &&
                                (pt_this->b_symbol_page))
                        {
                            pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx--;
                        }
                    }
                }
                    break;
                case VKB_FOCUS_WIDGET_EB_CLR:
                {
                    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EDIT_BOX;
                    break;
                }
                case VKB_FOCUS_WIDGET_BTN_OK:
                    break;
                case VKB_FOCUS_WIDGET_BTN_CANCEL:
                    break;
                default:
                    break;
            }
        }
            break;

        case VKB_FOCUS_CHG_RIGHT_KEY:
        {
            /* update internal focus data */
            switch (pt_this->t_focus_item.e_type)
            {
                case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
                {
                    /* update internal focus data */
                    if (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col == VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM - 1)
                    {
                        /* in last col: highlight on first col */
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = 0;
                    }
                    else
                    {
                        /* not in last col: highlight on next col */
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col++;
                    }
                }
                    break;

                case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
                {
                    /* update internal focus data */
                    if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx == VKB_KEYPAD_CTRL_KEY_TEXT_NUM - 1)
                    {
                        /* in last col: highlight on first col */
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                        pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx = 0;
                    }
                    else
                    {
                        /* not in last col: highlight on next col */
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                        pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx++;

                        if((pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx == VKB_KEYPAD_CTRL_CAPS_KEY_IDX) &&
                           (pt_this->b_symbol_page))
                        {
                            pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx++;
                        }

                        if((pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx == VKB_KEYPAD_CTRL_COM_KEY_IDX) &&
                           (pt_this->ui4_style_mask & VKB_STYLE_MASK_NO_COM_KEY))
                        {
                            pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx++;
                        }

                        if((pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx == VKB_KEYPAD_CTRL_LATIN_KEY_IDX) &&
                           (pt_this->b_symbol_page))
                        {
                            pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx++;
                        }

                    }
                }
                    break;

                case VKB_FOCUS_WIDGET_BTN_OK:
                {
                }
                    break;
                case VKB_FOCUS_WIDGET_BTN_CANCEL:
                {
                }
                    break;
                case VKB_FOCUS_WIDGET_EDIT_BOX:
                {
                    if (_vkb_is_eb_clr_hide(pt_this->h_main_frm))
                    {
                        //Do Nothing
                    }
                    else
                    {
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EB_CLR;
                    }
                    break;
                }
                default:
                    break;
            }
        }
            break;

        default:
            break;
    }

    /* set focus depend on internal focus data */
    switch (pt_this->t_focus_item.e_type)
    {
        case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
        {
            /* set focus on keypad normal key */
            if ((pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row < VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM)&&
                (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col < VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM))
            {
                i4_ret = c_wgl_set_focus (pt_this->aah_normal_key_txt[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row][pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col],
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);
                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY);
            }
        }
            break;

        case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
        {
            /* set focus on keypad ctrl key */
            if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx < VKB_KEYPAD_CTRL_KEY_TEXT_NUM)
            {
                i4_ret = c_wgl_set_focus (pt_this->ah_ctrl_key_txt[pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx],
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);
                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY);
            }
        }
            break;

        case VKB_FOCUS_WIDGET_BTN_OK:
        {
            if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD)
                || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID))
            {
                break;
            }
            else
            {
                /* set focus on OK button */
                i4_ret = c_wgl_set_focus (pt_this->h_ok_txt,
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);
                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_BTN_OK);
            }
        }
            break;

        case VKB_FOCUS_WIDGET_BTN_CANCEL:
        {
            if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD)||
                (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID))
            {
                break;
            }
            else
            {
                /* set focus on Cancel button */
                i4_ret = c_wgl_set_focus (pt_this->h_cancel_txt,
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);
                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_BTN_CANCEL);
            }
        }
            break;

        case VKB_FOCUS_WIDGET_EDIT_BOX:
        {
            if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD)||
                (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD)||
                (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID)||
                (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU)||
                (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_PWD))
            {
                /* set focus on edit box */
                i4_ret = c_wgl_set_focus (pt_this->h_input_editbox,
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);

                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_EDIT_BOX);
            }
        }
            break;
        case VKB_FOCUS_WIDGET_EB_CLR:
        {
            if (FALSE == _vkb_is_eb_clr_hide(pt_this->h_main_frm))
            {
                /* set focus on edit box */
                i4_ret = c_wgl_set_focus (pt_this->t_eb_clear_icon.h_eb_clear_icon,
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);
                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_EB_CLR);

            }
        }
            break;
        default:
            break;
    }

    return WDKR_OK;
}


static BOOL _vkb_is_full_screen_style(HANDLE_T h_vkb_handle)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T *pt_this = NULL;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    if (i4_ret != WDKR_OK)
    {
        DBG_INFO(("File:%s, Line:%d VKB GET Atach data Error!!\n", __FILE__, __LINE__));
    }

    return ((pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN)
            || (pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_EB)
            || (pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_OK)
            || (pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_CANCLE));
}

static BOOL _vkb_is_eb_clr_hide(HANDLE_T h_vkb_handle)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T *pt_this = NULL;
    BOOL b_visiable = FALSE;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    if (i4_ret != WDKR_OK)
    {
        DBG_INFO(("File:%s, Line:%d VKB GET Atach data Error!!\n", __FILE__, __LINE__));
    }

    /* hide delete all icon for editbox not created or attached */
    if (NULL_HANDLE == pt_this->h_input_editbox
        || NULL_HANDLE == pt_this->t_eb_clear_icon.h_eb_clear_icon)
    {
        return TRUE;
    }

    /* hide delete all icon for editbox hided or not indicating the style */
    i4_ret = c_wgl_get_visibility(pt_this->h_input_editbox, &b_visiable);
    if (i4_ret != WDKR_OK)
    {
        DBG_INFO(("File:%s, Line:%d VKB GET Atach data Error!!\n", __FILE__, __LINE__));
    }

    if (!b_visiable || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WITH_EB_CLEAR) == 0)
    {
        return TRUE;
    }

    return FALSE;
}

static INT32 _vkb_full_scrn_pad_set_focus_item(VKB_CONTROL_LOGIC_T*    pt_this,    /* IN, OUT */
                                                 VKB_FOCUS_CHG_TYPE_T    e_chg_type, /* IN */
                                                 BOOL                    b_repaint)
{
    INT32   i4_ret = WDK_NO_ACTION;
    BOOL    b_continue = FALSE;
    BOOL b_is_eb_attach = FALSE;
    BOOL b_is_eb_clr_attach = FALSE;
    /* aui1_ctrl_key_up_nav_idx[2]=3: means when press up on ctrl_key[2], focus change to normal_key[last_row][3] */
    //UINT8   aui1_ctrl_key_up_nav_idx[] = {0, 1, 3, 5, 8};

    /* aui1_normal_key_dn_nav_idx[2]=1: means when press dn on normal_key[last_row][2], focus change to ctrl_key[1] */
    //UINT8   aui1_normal_key_dn_nav_idx[] = {0, 1, 1, 2, 3, 3, 3, 3, 4};
    //UINT8   aui1_normal_key_dn_nav_idx_disable_shift[] = {0, 0, 2, 2, 3, 3, 3, 3, 4};

    a_vkb_is_eb_attach(pt_this->h_main_frm, &b_is_eb_attach, &b_is_eb_clr_attach);
    if (b_is_eb_attach)
    {
        _set_cur_attached_vkb_handle(pt_this->h_main_frm);
    }
    else
    {
        _set_cur_attached_vkb_handle(NULL_HANDLE);
    }

    if (FALSE == _vkb_is_full_screen_style(pt_this->h_main_frm))
    {
        return WDK_NO_ACTION;
    }
#ifdef APP_VKB_SUPPORT_LATIN_CHAR
    if (pt_this->b_latin_lock)
    {
        i4_ret = _vkb_set_focus_item_in_latin_state(pt_this, e_chg_type, b_repaint);
        if (WDK_NO_ACTION != i4_ret)
        {
            return i4_ret;
        }
    }
#endif
    switch (e_chg_type)
    {
        case VKB_FOCUS_CHG_UP_KEY:
        {
            /* update internal focus data */
            switch (pt_this->t_focus_item.e_type)
            {
                case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
                {
                    /* update internal focus data */
                    if (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row == 0)
                    {
                        if (b_is_eb_attach)
                        {
                            b_continue = TRUE;
                            pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EDIT_BOX;
                        }

                        i4_ret = WDKR_OK;
                    }
                    else
                    {
                        i4_ret = WDK_NO_ACTION;
                    }
                    break;
                }

                case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
                {
                    i4_ret = WDK_NO_ACTION;
                    break;
                }

                case VKB_FOCUS_WIDGET_BTN_OK:
                case VKB_FOCUS_WIDGET_BTN_CANCEL:
                {
                    return WDKR_OK;
                }

                case VKB_FOCUS_WIDGET_EDIT_BOX:
                case VKB_FOCUS_WIDGET_EB_CLR:
                {
                    i4_ret = WDK_NO_ACTION;
                    break;
                }

                default:
                    i4_ret = WDK_NO_ACTION;
                    break;
            }
        }
            break;

        case VKB_FOCUS_CHG_DOWN_KEY:
        {
            /* update internal focus data */
            switch (pt_this->t_focus_item.e_type)
            {
                case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
                {
                    i4_ret = WDK_NO_ACTION;
                    break;
                }

                case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
                case VKB_FOCUS_WIDGET_BTN_OK:
                case VKB_FOCUS_WIDGET_BTN_CANCEL:
                {
                    return WDKR_OK;
                }

                case VKB_FOCUS_WIDGET_EDIT_BOX:
                case VKB_FOCUS_WIDGET_EB_CLR:
                {
                    if (b_is_eb_attach)
                    {
                        b_continue = TRUE;
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                    }
                    i4_ret = WDKR_OK;
                    break;
                }

                default:
                    i4_ret = WDK_NO_ACTION;
                    break;
            }
        }
            break;

        case VKB_FOCUS_CHG_LEFT_KEY:
        {
            /* update internal focus data */
            switch (pt_this->t_focus_item.e_type)
            {
                case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
                case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
                {
                    i4_ret = WDK_NO_ACTION;
                    break;
                }

                case VKB_FOCUS_WIDGET_EB_CLR:
                {
                    if (b_is_eb_attach)
                    {
                        b_continue = TRUE;
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EDIT_BOX;
                    }
                    i4_ret = WDKR_OK;
                    break;
                }

                case VKB_FOCUS_WIDGET_BTN_OK:
                case VKB_FOCUS_WIDGET_BTN_CANCEL:
                    return WDKR_OK;
                default:
                    i4_ret = WDK_NO_ACTION;
                    break;
            }
        }
            break;

        case VKB_FOCUS_CHG_RIGHT_KEY:
        {
            /* update internal focus data */
            switch (pt_this->t_focus_item.e_type)
            {
                case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
                {
                    i4_ret = WDK_NO_ACTION;
                    break;
                }

                case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
                {
                    i4_ret = WDK_NO_ACTION;
                    break;
                }

                case VKB_FOCUS_WIDGET_BTN_OK:
                case VKB_FOCUS_WIDGET_BTN_CANCEL:
                {
                    return WDKR_OK;
                }

                case VKB_FOCUS_WIDGET_EDIT_BOX:
                {
                    if (b_is_eb_attach && b_is_eb_clr_attach)
                    {
                        b_continue = TRUE;
                        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EB_CLR;
                    }

                    i4_ret = WDKR_OK;

                    break;
                }

                default:
                    i4_ret = WDK_NO_ACTION;
                    break;
            }
        }
            break;

        default:
            i4_ret = WDK_NO_ACTION;
            break;
    }

    /* Processed by _vkb_set_focus_item */
    if (WDK_NO_ACTION == i4_ret || (!b_continue))
    {
        return i4_ret;
    }

    /* set focus depend on internal focus data */
    switch (pt_this->t_focus_item.e_type)
    {
        case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
        {
            /* set focus on keypad normal key */
            if ((pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row < VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM)&&
                (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col < VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM))
            {
                i4_ret = c_wgl_set_focus (pt_this->aah_normal_key_txt[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row][pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col],
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);

                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY);
            }
        }
            break;

        case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
        {
            /* set focus on keypad ctrl key */
            if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx < VKB_KEYPAD_CTRL_KEY_TEXT_NUM)
            {
                i4_ret = c_wgl_set_focus (pt_this->ah_ctrl_key_txt[pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx],
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);

                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY);
            }
        }
            break;

        case VKB_FOCUS_WIDGET_BTN_OK:
        {
            if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD)
                || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID))
            {
                break;
            }
            else
            {
                /* set focus on OK button */
                i4_ret = c_wgl_set_focus (pt_this->h_ok_txt,
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);

                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_BTN_OK);
            }
        }
            break;

        case VKB_FOCUS_WIDGET_BTN_CANCEL:
        {
            if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD)||
                (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID))
            {
                break;
            }
            else
            {
                /* set focus on Cancel button */
                i4_ret = c_wgl_set_focus (pt_this->h_cancel_txt,
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);

                _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_BTN_CANCEL);
            }
        }
            break;

        case VKB_FOCUS_WIDGET_EDIT_BOX:
        {
            /* set focus on edit box */
            i4_ret = c_wgl_set_focus (pt_this->h_input_editbox,
                                      b_repaint);
            WDK_CHK_FAIL(i4_ret);

            _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_EDIT_BOX);
        }
            break;
        case VKB_FOCUS_WIDGET_EB_CLR:
        {
            /* set focus on edit box */
            i4_ret = c_wgl_set_focus (pt_this->t_eb_clear_icon.h_eb_clear_icon,
                                      b_repaint);
            WDK_CHK_FAIL(i4_ret);

            _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_EB_CLR);
        }
            break;

        default:
            break;
    }

    return WDKR_OK;
}

static INT32 _vkb_show_eb_clr(HANDLE_T h_vkb_handle, BOOL b_repain)
{
    INT32 i4_ret = WDKR_OK;
    BOOL b_visible = TRUE;
    VKB_CONTROL_LOGIC_T* pt_this = NULL;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if (NULL_HANDLE == pt_this->t_eb_clear_icon.h_eb_clear_icon)
    {
        return i4_ret;
    }

    i4_ret = c_wgl_get_visibility(pt_this->h_input_editbox, &b_visible);
    WDK_CHK_FAIL(i4_ret);

    if (b_visible)
    {
        if (TRUE == _vkb_is_eb_clr_hide(h_vkb_handle))
        {
            return WDKR_OK;
        }

        i4_ret = c_wgl_set_visibility(pt_this->t_eb_clear_icon.h_eb_clear_icon, WGL_SW_NORMAL);
        WDK_CHK_FAIL(i4_ret);
        i4_ret = c_wgl_float(pt_this->t_eb_clear_icon.h_eb_clear_icon, TRUE, b_repain);
        WDK_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_set_visibility(pt_this->t_eb_clear_icon.h_eb_clear_icon, WGL_SW_HIDE);
        WDK_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_float(pt_this->t_eb_clear_icon.h_eb_clear_icon, FALSE, b_repain);
        WDK_CHK_FAIL(i4_ret);
    }

    return i4_ret;
}

static INT32 _vkb_hide_eb_clr(HANDLE_T h_vkb_handle, BOOL b_repain)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T* pt_this = NULL;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if (NULL_HANDLE == pt_this->t_eb_clear_icon.h_eb_clear_icon)
    {
        return i4_ret;
    }

    i4_ret = c_wgl_set_visibility(pt_this->t_eb_clear_icon.h_eb_clear_icon, WGL_SW_HIDE);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_float(pt_this->t_eb_clear_icon.h_eb_clear_icon, FALSE, b_repain);
    WDK_CHK_FAIL(i4_ret);

    return i4_ret;
}

static VOID _vkb_widget_rect_chg(VKB_CONTROL_LOGIC_T* pt_this, VKB_INIT_T* pt_init_data)
{
    if (_vkb_is_full_screen_style(pt_this->h_main_frm))
    {
        /* change main frame rect */
        SET_RECT_BY_SIZE(&t_rect_main_frm,
                            pt_init_data->t_gui_rc.i4_left,
                            pt_init_data->t_gui_rc.i4_top,
                            VKB_MAIN_FRAME_W_PHA2,
                            VKB_MAIN_FRAME_H_PHA2);

        SET_RECT_BY_SIZE(&t_rect_eb,
                         VKB_BTN_OK_TEXT_X_PHA2,
                         VKB_HEIGHT(0),
                         VKB_MAIN_FRAME_W_PHA2,
                         VKB_HEIGHT(33));

        SET_RECT_BY_SIZE(&t_rect_label,
                         VKB_LABEL_TEXT_X_PHA2,
                         VKB_LABEL_TEXT_Y_PHA2,
                         VKB_LABEL_TEXT_W_PHA2,
                         VKB_LABEL_TEXT_H_PHA2);

        SET_RECT_BY_SIZE(&t_rect_btn_ok,
                         VKB_BTN_OK_TEXT_X_PHA2,
                         VKB_BTN_OK_TEXT_Y_PHA2,
                         VKB_BTN_OK_TEXT_W_PHA2,
                         VKB_BTN_OK_TEXT_H_PHA2);

        SET_RECT_BY_SIZE(&t_rect_btn_cancel,
                         VKB_BTN_CANCEL_TEXT_X_PHA2,
                         VKB_BTN_CANCEL_TEXT_Y_PHA2,
                         VKB_BTN_CANCEL_TEXT_W_PHA2,
                         VKB_BTN_CANCEL_TEXT_H_PHA2);
    }
    else
    {
        /* change main frame rect */
        SET_RECT_BY_SIZE(&t_rect_main_frm,
                            pt_init_data->t_gui_rc.i4_left,
                            pt_init_data->t_gui_rc.i4_top,
                            VKB_3X_MAIN_FRAME_W,
                            VKB_3X_MAIN_FRAME_H);

        SET_RECT_BY_SIZE(&t_rect_eb,
                         VKB_3X_EB_X,
                         VKB_3X_EB_Y,
                         VKB_3X_EB_W,
                         VKB_3X_EB_H);

        SET_RECT_BY_SIZE(&t_rect_label,
                         VKB_3X_LABLE_X,
                         VKB_3X_LABLE_Y,
                         VKB_3X_LABLE_W,
                         VKB_3X_LABLE_H);

        SET_RECT_BY_SIZE(&t_rect_btn_ok,
                         VKB_3X_BTN_OK_X,
                         VKB_3X_BTN_OK_Y,
                         VKB_3X_BTN_OK_W,
                         VKB_3X_BTN_OK_H);

        SET_RECT_BY_SIZE(&t_rect_btn_cancel,
                         VKB_3X_BTN_CL_X,
                         VKB_3X_BTN_CL_Y,
                         VKB_3X_BTN_CL_W,
                         VKB_3X_BTN_CL_H);
    }
}
static INT32 _vkb_rc_change(UINT8 ui1_rc_config, VKB_CONTROL_LOGIC_T* pt_this)
{
    return vkb_rc_chg(ui1_rc_config, &pt_this->pt_rc_config);
}

static INT32 _vkb_change_main_frm(VKB_CONTROL_LOGIC_T*    pt_this,
                                   HANDLE_T                h_parent,
                                   VKB_GUI_RC_T            t_gui_rc)
{
    INT32 i4_ret = WDKR_OK;
    WGL_IMG_INFO_T      t_img_info;

    if (NULL == pt_this
        || NULL_HANDLE == h_parent
        || NULL_HANDLE == pt_this->h_main_frm)
    {
        DBG_INFO(("%s(): return WDKR_INV_ARG\n", __FUNCTION__));
        return WDKR_INV_ARG;
    }

    /* change rect */
    i4_ret = c_wgl_move(pt_this->h_main_frm, &t_rect_main_frm, FALSE);
    WDK_CHK_FAIL(i4_ret);

    /* change background image */
    c_memset(&t_img_info, 0, sizeof(t_img_info));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_this->pt_rc_config->h_main_frm_bk_img;
    t_img_info.u_img_data.t_standard.t_disable   = pt_this->pt_rc_config->h_main_frm_bk_img;
    t_img_info.u_img_data.t_standard.t_highlight = pt_this->pt_rc_config->h_main_frm_bk_img;

    WDK_CHK_FAIL (c_wgl_do_cmd (pt_this->h_main_frm,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK (WGL_IMG_BK),
                                  WGL_PACK (&t_img_info)));

    return i4_ret;

}

static INT32 _vkb_view_change_kb_frm(VKB_CONTROL_LOGIC_T*    pt_this)
{
    INT32   i4_ret = WDKR_OK;
    WGL_IMG_INFO_T      t_img_info = {0};

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       =pt_this->pt_rc_config->h_kb_frm_bk_img;
    t_img_info.u_img_data.t_standard.t_highlight    =pt_this->pt_rc_config->h_kb_frm_bk_img;
    t_img_info.u_img_data.t_standard.t_disable      =pt_this->pt_rc_config->h_kb_frm_bk_img;
    i4_ret = c_wgl_do_cmd(pt_this->h_kb_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    WDK_CHK_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _vkb_change_eb_ex(VKB_CONTROL_LOGIC_T* pt_this)
{
    INT32               i4_ret = 0;

    if (NULL == pt_this
        || NULL_HANDLE == pt_this->h_main_frm)
    {
        return WDKR_INV_ARG;
    }

    if (NULL_HANDLE == pt_this->h_input_editbox)
    {
        return WDKR_OK;
    }

    i4_ret = c_wgl_move(pt_this->h_input_editbox, &t_rect_eb, FALSE);
    WDK_CHK_FAIL(i4_ret);

    WGL_INSET_T         t_inset;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;

    /* Set Insets */
    t_inset.i4_left     = (0);
    t_inset.i4_right    = (0);
    t_inset.i4_top      = (0);
    t_inset.i4_bottom   = (0);
    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Cnt Insets */
    t_inset.i4_left     = 8;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    WDK_CHK_FAIL(i4_ret);
    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       =h_g_vkb_text_entry_v2;
    t_img_info.u_img_data.t_standard.t_highlight    =h_g_vkb_text_entry_highlight;
    t_img_info.u_img_data.t_standard.t_disable      =h_g_vkb_text_entry_v2;
    i4_ret = c_wgl_do_cmd(pt_this->h_input_editbox,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    WDK_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_BIG);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.i2_width     = VKB_EDIT_BOX_FONT_WIDTH;

    i4_ret = c_wgl_do_cmd (pt_this->h_input_editbox,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    WDK_CHK_FAIL(i4_ret);
    return WDKR_OK;
}

static INT32 _vkb_chg_label_txt(VKB_CONTROL_LOGIC_T* pt_this)
{
    INT32 i4_ret = WDKR_OK;

    if (NULL == pt_this
        || NULL_HANDLE == pt_this->h_main_frm)
    {
        return WDKR_INV_ARG;
    }

    if (pt_this->h_label_txt != NULL_HANDLE)
    {
        i4_ret = c_wgl_move(pt_this->h_label_txt, &t_rect_eb, FALSE);
        WDK_CHK_FAIL(i4_ret);
    }

    return i4_ret;
}



static INT32 _vkb_change_eb_clear_icon(VKB_CONTROL_LOGIC_T* pt_this)
{
    INT32 i4_ret = WDKR_OK;
    GL_RECT_T           t_rect = {0};
    WGL_IMG_INFO_T      t_img_info = {0};

    if (_vkb_is_full_screen_style(pt_this->h_main_frm))
    {
        return WDKR_OK;
    }

    if (NULL_HANDLE == pt_this->t_eb_clear_icon.h_eb_clear_icon)
    {
        return WDKR_OK;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     VKB_3X_CLEAR_EB_X,
                     VKB_3X_CLEAR_EB_Y,
                     VKB_3X_CLEAR_EB_W,
                     VKB_3X_CLEAR_EB_H);
    i4_ret = c_wgl_move(pt_this->t_eb_clear_icon.h_eb_clear_icon, &t_rect, FALSE);
    WDK_CHK_FAIL(i4_ret);

    /* Set images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_this->pt_rc_config->h_keypad_eb_clear_img;
    t_img_info.u_img_data.t_standard.t_highlight = pt_this->pt_rc_config->h_keypad_eb_clear_img_hlt;
    t_img_info.u_img_data.t_standard.t_disable   = pt_this->pt_rc_config->h_keypad_eb_clear_img;
    i4_ret = c_wgl_do_cmd(pt_this->t_eb_clear_icon.h_eb_clear_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    WDK_CHK_FAIL(i4_ret);
    return i4_ret;
}

static INT32 _vkb_chg_keypad_normal_key(VKB_CONTROL_LOGIC_T* pt_this)
{
    HANDLE_T                h_txt;
    UINT8                   ui1_idx_row;
    UINT8                   ui1_idx_col;
    GL_RECT_T               t_rect;
    WGL_IMG_INFO_T          t_img_info;
    WGL_COLOR_INFO_T        t_color_info;
    WGL_FONT_INFO_T         t_fnt_info;

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    c_memcpy(&t_color_info.u_color_data.t_standard.t_enable,
             &pt_this->pt_rc_config->t_keypad_key_txt_clr,
             sizeof(GL_COLOR_T));
    c_memcpy(&t_color_info.u_color_data.t_standard.t_disable,
             &pt_this->pt_rc_config->t_keypad_key_txt_dis_clr,
             sizeof(GL_COLOR_T));
    c_memcpy(&t_color_info.u_color_data.t_standard.t_highlight,
             &pt_this->pt_rc_config->t_keypad_key_txt_hlt_clr,
             sizeof(GL_COLOR_T));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_this->pt_rc_config->h_keypad_bk_img;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = pt_this->pt_rc_config->h_keypad_bk_hlt_img;

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_BIG);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.i2_width     = VKB_EDIT_BOX_FONT_WIDTH;

    for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM; ui1_idx_row++)
    {
        for (ui1_idx_col=0; ui1_idx_col<VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM; ui1_idx_col++)
        {
            h_txt = pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col];

            SET_RECT_BY_SIZE(&t_rect,
                        VKB_3X_KEYPAD_NORMAL_KEY_TEXT_X + ui1_idx_col*(VKB_3X_KEYPAD_NORMAL_KEY_TEXT_W + VKB_3X_KEYPAD_NORMAL_KEY_TEXT_OFFSET),
                        VKB_3X_KEYPAD_NORMAL_KEY_TEXT_Y + ui1_idx_row*(VKB_3X_KEYPAD_NORMAL_KEY_TEXT_H + VKB_3X_KEYPAD_NORMAL_KEY_TEXT_OFFSET),
                        VKB_3X_KEYPAD_NORMAL_KEY_TEXT_W,
                        VKB_3X_KEYPAD_NORMAL_KEY_TEXT_H);
            WDK_CHK_FAIL (c_wgl_move(h_txt, &t_rect, FALSE));

            WDK_CHK_FAIL (c_wgl_do_cmd (h_txt,
                                          WGL_CMD_GL_SET_IMAGE,
                                          WGL_PACK (WGL_IMG_BK),
                                          WGL_PACK (&t_img_info)));


            WDK_CHK_FAIL (c_wgl_do_cmd (h_txt,
                                          WGL_CMD_GL_SET_COLOR,
                                          WGL_PACK (WGL_CLR_TEXT), /* text color */
                                          WGL_PACK (& t_color_info)));

            WDK_CHK_FAIL (c_wgl_do_cmd (h_txt,
                                           WGL_CMD_GL_SET_FONT,
                                           WGL_PACK(&t_fnt_info),
                                           NULL));
        }
    }

    return WDKR_OK;
}

static INT32 _vkb_chg_keypad_ctrl_key_txt(VKB_CONTROL_LOGIC_T *pt_this)

{
    INT32                   i4_ret = WDKR_OK;
    UINT8                   ui1_idx_row;
    HANDLE_T                h_ctrl_txt;
    GL_RECT_T               t_rect;
    WGL_INSET_T             t_inset;
    WGL_IMG_INFO_T          t_img_info;
    WGL_COLOR_INFO_T        t_color_info;
    WGL_FONT_INFO_T         t_fnt_info;
    INT32                   i4_ctrl_key_x;
    INT32                   i4_ctrl_key_y;

    INT32 ai4_ctrl_key_width[VKB_KEYPAD_CTRL_KEY_TEXT_NUM] =
        {
            VKB_3X_KEYPAD_CTRL_KEY_BIG_W,
            VKB_3X_KEYPAD_CTRL_KEY_BIG_W,
            VKB_3X_KEYPAD_CTRL_KEY_BIG_W,
            VKB_3X_KEYPAD_CTRL_KEY_SPACE_W,
            VKB_3X_KEYPAD_CTRL_KEY_BIG_W
        };

    INT32 ai4_ctrl_key_height[VKB_KEYPAD_CTRL_KEY_TEXT_NUM] =
        {
            VKB_3X_KEYPAD_CTRL_KEY_BIG_H,
            VKB_3X_KEYPAD_CTRL_KEY_BIG_H,
            VKB_3X_KEYPAD_CTRL_KEY_BIG_H,
            VKB_3X_KEYPAD_CTRL_KEY_BIG_H,
            VKB_3X_KEYPAD_CTRL_KEY_BIG_H
        };

    i4_ctrl_key_x = VKB_3X_KEYPAD_CTRL_KEY_BIG_X;
    i4_ctrl_key_y = VKB_3X_KEYPAD_CTRL_KEY_BIG_Y;

    WGL_HIMG_TPL_T ah_txt_bk_img[] =
    {
        pt_this->pt_rc_config->h_keypad_big_bk_img,
        pt_this->pt_rc_config->h_keypad_capslock_bk_img,
        pt_this->pt_rc_config->h_keypad_big_bk_img,
        pt_this->pt_rc_config->h_keypad_space_bk_img,
        pt_this->pt_rc_config->h_keypad_delete_bk_img
    };

    WGL_HIMG_TPL_T ah_txt_bk_hlt_img[] =
    {
        pt_this->pt_rc_config->h_keypad_big_bk_hlt_img,
        pt_this->pt_rc_config->h_keypad_capslock_bk_hlt_img,
        pt_this->pt_rc_config->h_keypad_big_bk_hlt_img,
        pt_this->pt_rc_config->h_keypad_space_bk_hlt_img,
        pt_this->pt_rc_config->h_keypad_delete_bk_hlt_img
    };

    WGL_HIMG_TPL_T ah_txt_bk_dis_img[] =
    {
        NULL_HANDLE,
        pt_this->pt_rc_config->h_keypad_capslock_bk_dis_img,
        NULL_HANDLE,
        NULL_HANDLE,
        NULL_HANDLE
    };

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    c_memcpy (& t_color_info.u_color_data.t_standard.t_enable,
                & (pt_this->pt_rc_config->t_keypad_key_txt_clr),
                sizeof(GL_COLOR_T));
    c_memcpy (& t_color_info.u_color_data.t_standard.t_disable,
                & (pt_this->pt_rc_config->t_keypad_key_txt_dis_clr),
                sizeof(GL_COLOR_T));
    c_memcpy (& t_color_info.u_color_data.t_standard.t_highlight,
                & (pt_this->pt_rc_config->t_keypad_key_txt_hlt_clr),
                sizeof(GL_COLOR_T));

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_BIG);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.i2_width     = VKB_EDIT_BOX_FONT_WIDTH;

    for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_CTRL_KEY_TEXT_NUM; ui1_idx_row++)
    {
        h_ctrl_txt = pt_this->ah_ctrl_key_txt[ui1_idx_row];

        SET_RECT_BY_SIZE(&t_rect,
                        i4_ctrl_key_x,
                        i4_ctrl_key_y,
                        ai4_ctrl_key_width[ui1_idx_row],
                        ai4_ctrl_key_height[ui1_idx_row]);

        i4_ctrl_key_x += ai4_ctrl_key_width[ui1_idx_row] + VKB_3X_KEYPAD_NORMAL_KEY_TEXT_OFFSET;
        c_wgl_move(h_ctrl_txt, &t_rect, FALSE);

        WDK_CHK_FAIL (c_wgl_do_cmd (h_ctrl_txt,
                                      WGL_CMD_GL_SET_COLOR,
                                      WGL_PACK (WGL_CLR_TEXT), /* text color */
                                      WGL_PACK (& t_color_info)));

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = ah_txt_bk_img[ui1_idx_row];
        t_img_info.u_img_data.t_standard.t_disable   = ah_txt_bk_dis_img[ui1_idx_row];
        t_img_info.u_img_data.t_standard.t_highlight = ah_txt_bk_hlt_img[ui1_idx_row];

        WDK_CHK_FAIL (c_wgl_do_cmd (h_ctrl_txt,
                                      WGL_CMD_GL_SET_IMAGE,
                                      WGL_PACK (WGL_IMG_BK), /* background image */
                                      WGL_PACK (& t_img_info)));
        WDK_CHK_FAIL (c_wgl_do_cmd (h_ctrl_txt,
                                      WGL_CMD_GL_SET_FONT,
                                      WGL_PACK (&t_fnt_info), /* background image */
                                      NULL));
        #if 1
        /* change content insert for Shift/Back */
        if (ui1_idx_row == 1 || ui1_idx_row == 4)
        {
            t_inset.i4_left = 0;
            t_inset.i4_right = VKB_KEYPAD_BIG_KEY_TEXT_W_PHA2/3+5;
            t_inset.i4_top = 0;
            t_inset.i4_bottom = 0;
            WDK_CHK_FAIL (c_wgl_do_cmd (h_ctrl_txt,
                                        WGL_CMD_TEXT_SET_CNT_INSET,
                                        WGL_PACK (&t_inset),
                                        NULL));

            WDK_CHK_FAIL (c_wgl_do_cmd (h_ctrl_txt,
                                        WGL_CMD_TEXT_SET_ALIGN,
                                        WGL_PACK (WGL_AS_RIGHT_CENTER),
                                        NULL));
        }
        #endif
    }

    return i4_ret;
}

static INT32 _vkb_keypad_set_changed_ctrl_text(VKB_CONTROL_LOGIC_T *pt_this,
                                            BOOL *pab_ctrl_key_is_chg,
                                            BOOL b_repaint)
{
    INT32 i4_ret = WDKR_OK;
    UINT8 ui1_i;
    CHAR                    ach_temp[VKB_KEY_CAPTION_MAX_LEN + 1];
    UTF16_T                 w2s_str[VKB_KEY_CAPTION_MAX_LEN + 1];
    VKB_KEYPAD_KEY_ITEM_T*  pt_keypad_key;

    if (NULL == pt_this || NULL == pab_ctrl_key_is_chg)
    {
        return WDKR_INV_ARG;
    }

    /* Set caption for keypad key text widget -- ctrl key */
    for (ui1_i=0; ui1_i<VKB_KEYPAD_CTRL_KEY_TEXT_NUM; ui1_i++)
    {
        if (FALSE == pab_ctrl_key_is_chg[ui1_i])
        {
            continue;
        }

        c_memset(ach_temp, 0, sizeof(ach_temp));
        c_memset(w2s_str, 0, sizeof(w2s_str));

        pt_keypad_key = & (pt_this->at_keypad_ctrl_key[ui1_i]);

        i4_ret = _vkb_view_keypad_get_key_caption(pt_this, pt_keypad_key, ach_temp);
        WDK_CHK_FAIL(i4_ret);

        c_uc_ps_to_w2s (ach_temp, w2s_str, VKB_KEY_CAPTION_MAX_LEN);

        /*HIDE .com key by request of customer*/
        if((VKB_KEYPAD_CTRL_COM_KEY_IDX == ui1_i) && (pt_this->ui4_style_mask & VKB_STYLE_MASK_NO_COM_KEY))
        {
            c_uc_ps_to_w2s ("", w2s_str, VKB_KEY_CAPTION_MAX_LEN);
        }
        i4_ret = a_wdk_text_set_text(
                    pt_this->ah_ctrl_key_txt[ui1_i],
                    w2s_str);
        WDK_CHK_FAIL(i4_ret);
    }

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_main_frm, NULL, TRUE);
        WDK_CHK_FAIL(i4_ret);
    }

    return i4_ret;

}

static INT32 _vkb_keypad_chg_ctrl_key_text(VKB_CONTROL_LOGIC_T* pt_this)
{
    UINT8                   ui1_idx_row;
    VKB_KEY_TYPE_T          e_key_type;
    VKB_KEYPAD_KEY_ITEM_T*  pt_keypad_key;

    BOOL       ab_ctrl_key_is_chg[VKB_KEYPAD_CTRL_KEY_TEXT_NUM] =
        {
            FALSE,
            TRUE,
            FALSE,
            FALSE,
            TRUE
        };

    /* Customization part: caption table of ctrl key in keypad */
    CHAR        aach_ctrl_key_cus_caption[VKB_KEYPAD_CTRL_KEY_TEXT_NUM][VKB_KEY_CAPTION_MAX_LEN] =
        {
            ".@#",
            "Shift",
            ".com",
            "Space",
            "Back"
        };
    CHAR        aach_ctrl_key_cus_caption_in_capslock[VKB_KEYPAD_CTRL_KEY_TEXT_NUM][VKB_KEY_CAPTION_MAX_LEN] =
        {
            ".@#",
            "Shift",
            ".com",
            "Space",
            "Back"
        };
    CHAR        aach_ctrl_key_cus_caption_symbol_page[VKB_KEYPAD_CTRL_KEY_TEXT_NUM][VKB_KEY_CAPTION_MAX_LEN] =
        {
            "abc",
            "Shift",
            ".com",
            "Space",
            "Back"
        };
    CHAR        aach_ctrl_key_cus_values[VKB_KEYPAD_CTRL_KEY_TEXT_NUM][VKB_KEY_CAPTION_MAX_LEN] =
        {
            "NULL",
            "NULL",
            ".COM",
            " ",
            "NULL"
        };
    CHAR        aach_ctrl_key_cus_values_in_capslock[VKB_KEYPAD_CTRL_KEY_TEXT_NUM][VKB_KEY_CAPTION_MAX_LEN] =
        {
            "NULL",
            "NULL",
            ".com",
            " ",
            "NULL"
        };
    VKB_KEY_TYPE_T   ae_ctrl_key_cus_type[VKB_KEYPAD_CTRL_KEY_TEXT_NUM] =
        {
            VKB_KEY_TYPE_CTRL_KEY,
            VKB_KEY_TYPE_CTRL_KEY,
            VKB_KEY_TYPE_COMPOSITE_INPUT_KEY,              /* CapsLock key */
            VKB_KEY_TYPE_COMPOSITE_INPUT_KEY,   /* Space key */
            VKB_KEY_TYPE_CTRL_KEY               /* Backspace key */
        };

    /* change keypad ctrl key caption */
    for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_CTRL_KEY_TEXT_NUM; ui1_idx_row++)
    {
        if (FALSE == ab_ctrl_key_is_chg[ui1_idx_row])
        {
            continue;
        }

        e_key_type = ae_ctrl_key_cus_type[ui1_idx_row];
        pt_keypad_key = & (pt_this->at_keypad_ctrl_key[ui1_idx_row]);

        switch (e_key_type)
        {
            case VKB_KEY_TYPE_SINGLE_INPUT_KEY:
            {
                pt_keypad_key->e_type = VKB_KEY_TYPE_SINGLE_INPUT_KEY;
                pt_keypad_key->u.t_single_input_key.ch_value_no_caps_lock = aach_ctrl_key_cus_caption[ui1_idx_row][0];
                pt_keypad_key->u.t_single_input_key.ch_value_in_caps_lock = aach_ctrl_key_cus_caption_in_capslock[ui1_idx_row][0];
            }
                break;

            case VKB_KEY_TYPE_COMPOSITE_INPUT_KEY:
            {
                pt_keypad_key->e_type = VKB_KEY_TYPE_COMPOSITE_INPUT_KEY;
                /* value */
                c_strcpy(pt_keypad_key->u.t_composite_input_key.ach_values_no_caps_lock,
                            aach_ctrl_key_cus_values[ui1_idx_row]);
                c_strcpy(pt_keypad_key->u.t_composite_input_key.ach_values_in_caps_lock,
                            aach_ctrl_key_cus_values_in_capslock[ui1_idx_row]);

                /* caption */
                c_strcpy(pt_keypad_key->u.t_composite_input_key.t_key_ui_descr.ach_captions_no_caps_lock,
                            aach_ctrl_key_cus_caption[ui1_idx_row]);
                c_strcpy(pt_keypad_key->u.t_composite_input_key.t_key_ui_descr.ach_captions_in_caps_lock,
                            aach_ctrl_key_cus_caption_in_capslock[ui1_idx_row]);
            }
                break;

            case VKB_KEY_TYPE_CTRL_KEY:
            {
                pt_keypad_key->e_type = VKB_KEY_TYPE_CTRL_KEY;
                /* caption */
                c_strcpy(pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_no_caps_lock,
                            aach_ctrl_key_cus_caption[ui1_idx_row]);
                c_strcpy(pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_in_caps_lock,
                            aach_ctrl_key_cus_caption_in_capslock[ui1_idx_row]);
                c_strcpy(pt_keypad_key->u.t_ctrl_key.t_key_ui_descr.ach_captions_symbol_page,
                            aach_ctrl_key_cus_caption_symbol_page[ui1_idx_row]);
            }
                break;

            default:
                break;
        }
    }

    _vkb_keypad_set_changed_ctrl_text(pt_this, ab_ctrl_key_is_chg, FALSE);
    return WDKR_OK;
}

static INT32 _vkb_chg_button_txt(VKB_CONTROL_LOGIC_T* pt_this)
{
    INT32                   i4_ret;
    WGL_SW_CMD_T            e_sw_cmd_bt_ok = WGL_SW_HIDE;
    WGL_SW_CMD_T            e_sw_cmd_bt_cancel = WGL_SW_HIDE;
    WGL_FONT_INFO_T         t_fnt_info = {0};
    WGL_IMG_INFO_T          t_img_info = {0};
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = pt_this->pt_rc_config->h_keypad_bk_hlt_img;

    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_OK) != 0)
    {
        e_sw_cmd_bt_ok = WGL_SW_NORMAL;
    }

    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_CANCLE) != 0)
    {
        e_sw_cmd_bt_cancel = WGL_SW_NORMAL;
    }

    if (pt_this->h_ok_txt != NULL_HANDLE)
    {
        c_wgl_do_cmd (pt_this->h_ok_txt,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK (WGL_IMG_BK), /* background image */
                                  WGL_PACK (& t_img_info));

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_BIG);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_fnt_info.i2_width     = VKB_EDIT_BOX_FONT_WIDTH;

         c_wgl_do_cmd (pt_this->h_ok_txt,
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);

        i4_ret = c_wgl_move(pt_this->h_ok_txt, &t_rect_btn_ok, FALSE);
        WDK_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_this->h_ok_txt, e_sw_cmd_bt_ok);
        WDK_CHK_FAIL(i4_ret);
    }

    if (pt_this->h_cancel_txt != NULL_HANDLE)
    {
        c_wgl_do_cmd (pt_this->h_cancel_txt,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK (WGL_IMG_BK), /* background image */
                                  WGL_PACK (& t_img_info));

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_BIG);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_fnt_info.i2_width     = VKB_EDIT_BOX_FONT_WIDTH;

         c_wgl_do_cmd (pt_this->h_cancel_txt,
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);

        i4_ret = c_wgl_move(pt_this->h_cancel_txt, &t_rect_btn_cancel, FALSE);
        WDK_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_this->h_cancel_txt, e_sw_cmd_bt_cancel);
        WDK_CHK_FAIL(i4_ret);
    }


    return WDKR_OK;
}

static INT32 _vkb_set_visiable_full_screen_style(VKB_CONTROL_LOGIC_T* pt_this)
{
    if (_vkb_is_full_screen_style(pt_this->h_main_frm) == FALSE)
    {
        return WDKR_OK;
    }

    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_EB) == 0)
    {
        c_wgl_set_visibility(pt_this->h_input_eb_self, WGL_SW_HIDE);
        c_wgl_set_visibility(pt_this->t_eb_clear_icon.h_eb_clear_icon_self, WGL_SW_HIDE);
    }

    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_OK) == 0)
    {
        c_wgl_set_visibility(pt_this->h_ok_txt, WGL_SW_HIDE);
    }

    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_CANCLE) == 0)
    {
        c_wgl_set_visibility(pt_this->h_cancel_txt, WGL_SW_HIDE);
    }

    return WDKR_OK;
}

static INT32 _vkb_change_skin(HANDLE_T h_vkb_handle, VKB_INIT_T* pt_init_data)
{
    INT32       i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T*    pt_this = NULL;

    if (NULL_HANDLE == h_vkb_handle || NULL == pt_init_data)
    {
        return WDKR_INV_ARG;
    }

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if ((pt_init_data->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN) == 0
        && (pt_init_data->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_EB) == 0
        && (pt_init_data->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_OK) == 0
        && (pt_init_data->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_CANCLE) == 0)
    {
        i4_ret = _vkb_rc_change(VKB_RC_CHG_UI3X, pt_this);
        WDK_CHK_FAIL(i4_ret);
    }
    else    //full screen vkb
    {
        //Clear other style for full screen style, beacuse it has keypad only(no editbox and buttons)
        pt_this->ui4_style_mask = ((pt_init_data->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN) | VKB_STYLE_MASK_WZD_DROP_DOWN);
        pt_this->ui4_style_mask = pt_this->ui4_style_mask|pt_init_data->ui4_style_mask;
        i4_ret = _vkb_rc_change(VKB_RC_CHG_PHASE2, pt_this);
        WDK_CHK_FAIL(i4_ret);

        /* Set keypad caption */
        i4_ret = _vkb_keypad_chg_ctrl_key_text(pt_this);
        if (i4_ret != WGLR_OK)
        {
            DBG_INFO(("%s(): _vkb_keypad_chg_ctrl_key_text return %d\n", __FUNCTION__, i4_ret));
        }
    }

    _vkb_widget_rect_chg(pt_this, pt_init_data);

    do
    {
        /* change Content Frame theme */
        i4_ret = _vkb_change_main_frm(
                                pt_this,
                                pt_init_data->h_parent,
                                pt_init_data->t_gui_rc);

        if (i4_ret != WGLR_OK)
        {
            DBG_INFO(("%s(): %d return %d\n", __FUNCTION__,__LINE__, i4_ret));
            break;
        }

        _vkb_view_change_kb_frm(pt_this);

        /* change Input Editbox theme */
        i4_ret = _vkb_change_eb_ex(pt_this);
        if (i4_ret != WGLR_OK)
        {
            DBG_INFO(("%s(): %d return %d\n", __FUNCTION__,__LINE__, i4_ret));
            break;
        }

        /* change Label text theme*/
        i4_ret = _vkb_chg_label_txt(pt_this);
        if (i4_ret != WGLR_OK)
        {
            DBG_INFO(("%s(): %d return %d\n", __FUNCTION__,__LINE__, i4_ret));
            break;
        }

        /* change edit box clear icon */
        _vkb_change_eb_clear_icon(pt_this);

        /* change Keypad normal key theme */
        i4_ret = _vkb_chg_keypad_normal_key(pt_this);
        if (i4_ret != WGLR_OK)
        {
            DBG_INFO(("%s(): %d return %d\n", __FUNCTION__,__LINE__, i4_ret));
            break;
        }
        /* change Keypad ctrl key theme */
        i4_ret = _vkb_chg_keypad_ctrl_key_txt(pt_this);
        if (i4_ret != WGLR_OK)
        {
            DBG_INFO(("%s(): %d return %d\n", __FUNCTION__,__LINE__, i4_ret));
            break;
        }

        //i4_ret = _vkb_view_keypad_set_key_text(pt_this, FALSE);
        //if(i4_ret != WDKR_OK)
        //{
        //    break;
        //}

        i4_ret = _vkb_chg_button_txt(pt_this);
        if (i4_ret != WGLR_OK)
        {
            DBG_INFO(("%s(): %d return %d\n", __FUNCTION__,__LINE__, i4_ret));
            break;
        }

        /* Hide the frame at initial time */
        c_wgl_set_visibility(pt_this->h_main_frm, WGL_SW_HIDE);
        c_wgl_repaint(pt_this->h_main_frm, NULL, TRUE);

        i4_ret = WDKR_OK;

    } while(0);

    DBG_INFO(("%s(): %d return %d\n", __FUNCTION__,__LINE__, i4_ret));
    return i4_ret;
}

static BOOL _is_valid_attach_data(VKB_EB_ATTACH_DATE *pt_attach_data)
{
    if (NULL == pt_attach_data)
    {
        DBG_INFO(("%s(): NULL attach data\n"));
        return FALSE;
    }

    if (NULL_HANDLE == pt_attach_data->h_edit_box)
    {
        DBG_INFO(("%s(): NULL editbox handle\n"));
        return FALSE;
    }

    if (pt_attach_data->b_need_eb_clr
        && NULL_HANDLE == pt_attach_data->h_eb_clr)
    {
        DBG_INFO(("%s(): NULL Delete All handle\n"));
        return FALSE;
    }

    return TRUE;
}

static VOID _set_cur_attached_vkb_handle(HANDLE_T h_vkb)
{
    h_cur_vkb = h_vkb;
}

static HANDLE_T _get_cur_attached_vkb_handle(VOID)
{
    return h_cur_vkb;
}

static INT32 _vkb_full_screen_is_top_row(VKB_CONTROL_LOGIC_T* pt_this, BOOL *pb_is_top_row)
{
    BOOL b_is_top_row = FALSE;
    INT32 i4_ret = WDK_NO_ACTION;

    do {
        if (!_vkb_is_full_screen_style(pt_this->h_main_frm))
        {
            b_is_top_row = FALSE;
            i4_ret = WDK_NO_ACTION;
            break;
        }

        i4_ret = WDKR_OK;

        if (pt_this->b_eb_attached
            || (pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_EB))
        {
            b_is_top_row = (pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_EDIT_BOX
                            || pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_EB_CLR);
            break;
        }
        else
        {
            b_is_top_row = ((pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY)
                            && (0 == pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row));

            if (pt_this->b_latin_expand)
            {
                if (pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY)
                {
                    b_is_top_row = TRUE;
                }
                else
                {
                    b_is_top_row = FALSE;
                }
            }
           break;
        }
    }while(0);

    *pb_is_top_row = b_is_top_row;

    return i4_ret;
}

static INT32 _vkb_full_screen_is_bootom_row(VKB_CONTROL_LOGIC_T* pt_this, BOOL *pb_is_bottom_row)
{
    BOOL b_is_bottom_row = FALSE;
    INT32 i4_ret = WDK_NO_ACTION;
    UINT32 ui4_mask = 0;

    do {
        if (!_vkb_is_full_screen_style(pt_this->h_main_frm))
        {
            b_is_bottom_row = FALSE;
            i4_ret = WDK_NO_ACTION;
            break;
        }

        i4_ret = WDKR_OK;

        ui4_mask = (pt_this->ui4_style_mask
                    & (VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_OK
                        | VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_CANCLE));

        if ( 0 == ui4_mask)
        {
            b_is_bottom_row = (pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY);

            if (pt_this->b_latin_expand)
            {
                if (pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY)
                {
                    b_is_bottom_row = TRUE;
                }
                else
                {
                    b_is_bottom_row = FALSE;
                }
            }
           break;
        }
        else if (ui4_mask == (VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_OK | VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_OK))
        {
           b_is_bottom_row = (pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_CANCEL);
           break;
        }
        else
        {
            b_is_bottom_row = ((pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_OK)
                                || (pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_CANCEL));
           break;
        }
    }while(0);

    *pb_is_bottom_row = b_is_bottom_row;

    return i4_ret;
}

static INT32 _vkb_chg_lang(VKB_CONTROL_LOGIC_T* pt_this)
{
    UTF16_T         *p_w2s_ok = NULL_HANDLE;
    UTF16_T         *p_w2s_cncl = NULL_HANDLE;

    if (pt_this->aw2s_ok_txt[0] == 0xFFFF)
    {
        p_w2s_ok = w2s_ok_txt[g_ui2_lang_id];
    }
    else
    {
        p_w2s_ok = pt_this->aw2s_ok_txt;
    }

    if (pt_this->aw2s_cncl_txt[0] == 0xFFFF)
    {
        p_w2s_cncl = w2s_cncl_txt[g_ui2_lang_id];
    }
    else
    {
        p_w2s_cncl = pt_this->aw2s_cncl_txt;
    }

    a_wdk_text_set_text(pt_this->h_ok_txt, p_w2s_ok);
    a_wdk_text_set_text(pt_this->h_cancel_txt, p_w2s_cncl);

    return WDKR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vkb_destroy(HANDLE_T                 h_vkb_handle)
{
    INT32                   i4_ret;
    UINT8                   ui1_idx_row;
    UINT8                   ui1_idx_col;
    VKB_CONTROL_LOGIC_T*    pt_this = NULL;

    if (NULL_HANDLE == h_vkb_handle)
    {
        return WDKR_INV_ARG;
    }

    /* 1. Get attach data */
    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    do
    {
        /* Destroy Label text handle */
        if (NULL_HANDLE != pt_this->h_label_txt)
        {
            i4_ret = c_wgl_destroy_widget_ex(pt_this->h_label_txt, FALSE);
            if(i4_ret != WGLR_OK)
            {
                break;
            }
        }

        /* Destroy Input editbox handle */
        if (NULL_HANDLE != pt_this->h_input_eb_self)
        {
            i4_ret = c_wgl_destroy_widget_ex(pt_this->h_input_eb_self, FALSE);
            if(i4_ret != WGLR_OK)
            {
                break;
            }
        }

        /* Destroy Keypad normal key text */
        for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM; ui1_idx_row++)
        {
            for (ui1_idx_col=0; ui1_idx_col<VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM; ui1_idx_col++)
            {
                if (NULL_HANDLE != pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col])
                {
                    i4_ret = c_wgl_destroy_widget_ex(pt_this->aah_normal_key_txt[ui1_idx_row][ui1_idx_col], FALSE);
                    if(i4_ret != WGLR_OK)
                    {
                        break;
                    }
                }
            }
        }

        /* Destroy Keypad ctrl key text */
        for (ui1_idx_row=0; ui1_idx_row<VKB_KEYPAD_CTRL_KEY_TEXT_NUM; ui1_idx_row++)
        {
            if (NULL_HANDLE != pt_this->ah_ctrl_key_txt[ui1_idx_row])
            {
                i4_ret = c_wgl_destroy_widget_ex(pt_this->ah_ctrl_key_txt[ui1_idx_row], FALSE);
                if(i4_ret != WGLR_OK)
                {
                    break;
                }
            }
        }

        /* Destroy button OK, Cancel: they are text widget */
        if (NULL_HANDLE != pt_this->h_ok_txt)
        {
            i4_ret = c_wgl_destroy_widget_ex(pt_this->h_ok_txt, FALSE);
            if(i4_ret != WGLR_OK)
            {
                break;
            }
        }
        if (NULL_HANDLE != pt_this->h_cancel_txt)
        {
            i4_ret = c_wgl_destroy_widget_ex(pt_this->h_cancel_txt, FALSE);
            if(i4_ret != WGLR_OK)
            {
                break;
            }
        }

        if (NULL_HANDLE != pt_this->t_eb_clear_icon.h_eb_clear_icon_self)
        {
            i4_ret = c_wgl_destroy_widget_ex(pt_this->t_eb_clear_icon.h_eb_clear_icon_self, FALSE);
            if(i4_ret != WGLR_OK)
            {
                break;
            }
        }

        /* Destroy VKB handle */
        if (NULL_HANDLE != pt_this->h_main_frm)
        {
            i4_ret = c_wgl_destroy_widget_ex(pt_this->h_main_frm, FALSE);
            if(i4_ret != WGLR_OK)
            {
                break;
            }
        }

    } while (0);

    /* 3. Free attach data memory */
    c_mem_free(pt_this);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_vkb_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_vkb_create_v2(VKB_INIT_T*              pt_init_data,       /* IN */
                   HANDLE_T*                ph_handle_out       /* OUT */)
{
    INT32       i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T*    pt_this = NULL;

    /* check valid of argument */
    if (pt_init_data->t_gui_rc.i4_left < 0)
    {
        return WDKR_INV_ARG;
    }

    /* Alloc memory for internal control logic data */
    pt_this = (VKB_CONTROL_LOGIC_T*)c_mem_alloc(sizeof(VKB_CONTROL_LOGIC_T));
    if (NULL == pt_this)
    {
        return WDKR_OUT_OF_MEMORY;
    }

    c_memset(pt_this, 0, sizeof(VKB_CONTROL_LOGIC_T));

    /* Init general resource shared by all VKB instance */
    i4_ret = vkb_rc_init(&(pt_this->pt_rc_config));
    WDK_CHK_FAIL(i4_ret);

    /* Initilize internal control data */
    i4_ret = _vkb_init_internal_ctrl_data(pt_init_data, pt_this);
    WDK_CHK_FAIL(i4_ret);

    /* Initilize widgets */
    do
    {
    #ifdef APP_VKB_SUPPORT_LATIN_CHAR
        pt_this->ui4_style_mask = (pt_this->ui4_style_mask & (~VKB_STYLE_MASK_NO_COM_KEY));
    #endif

        /* Create Content Frame for Keyboard area */
        i4_ret = _vkb_view_create_main_frm(
                                pt_this,
                                pt_init_data->h_parent,
                                pt_init_data->t_gui_rc);
        if(i4_ret != WDKR_OK)
        {
            break;
        }

        if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD )||
            (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID))
        {
            /* Create Input Editbox */
            _vkb_view_create_editbox_ex(
                                    pt_this,
                                    pt_this->h_main_frm);
            if(i4_ret != WDKR_OK)
            {
                break;
            }
        }
        else
        {
            /* Create Label text */
            i4_ret = _vkb_view_create_label_txt(
                                    pt_this,
                                    pt_this->h_main_frm);
            if(i4_ret != WDKR_OK)
            {
                break;
            }

            if((pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD)||
               (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU)||
               (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_PWD)||
               (pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN))
            {
                /* Create Input Editbox */
                _vkb_view_create_editbox_ex(
                                        pt_this,
                                        pt_this->h_main_frm);
                if(i4_ret != WDKR_OK)
                {
                    break;
                }
            }
            else if (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN)
            {
                /* Do not create editbox */
            }
            else
            {
                /* Create Input Editbox */
                i4_ret = _vkb_view_create_editbox(
                                        pt_this,
                                        pt_this->h_main_frm);
                if(i4_ret != WDKR_OK)
                {
                    break;
                }
            }

            if (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN)
            {
                /* Do not create buttons */
            }
            else
            {
                /* Create button OK, Cancel: they are text widget */
                i4_ret = _vkb_view_create_button_txt(
                                        pt_this,
                                        pt_this->h_main_frm);
                if(i4_ret != WDKR_OK)
                {
                    break;
                }
            }
        }

        if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN) == 0)
        {
            _vkb_view_create_eb_clear_icon(pt_this, pt_this->h_input_editbox);
        }

        if(i4_ret != WDKR_OK)
        {
            break;
        }

        /* Create Keypad normal key text */
        i4_ret = _vkb_view_create_keypad_normal_key_txt(
                                pt_this,
                                pt_this->h_main_frm);
        if(i4_ret != WDKR_OK)
        {
            break;
        }

        /* Create Keypad ctrl key text */
        i4_ret = _vkb_view_create_keypad_ctrl_key_txt(
                                pt_this,
                                pt_this->h_main_frm);
        if(i4_ret != WDKR_OK)
        {
            break;
        }

        /* Create vkb keyboard frame for UI3.X */
        i4_ret = _vkb_view_create_kb_frm(
                                pt_this,
                                pt_this->h_main_frm,
                                pt_init_data->t_gui_rc);
        if(i4_ret != WDKR_OK)
        {
            break;
        }

        if(pt_this->ui4_style_mask & VKB_STYLE_MASK_NO_COM_KEY)
        {
            i4_ret = c_wgl_enable(pt_this->ah_ctrl_key_txt[VKB_KEYPAD_CTRL_COM_KEY_IDX], FALSE);
            if(i4_ret != WDKR_OK)
            {
                break;
            }
        }

        /* Set keypad caption */
        i4_ret = _vkb_view_keypad_set_key_text(pt_this, FALSE);
        if(i4_ret != WDKR_OK)
        {
            break;
        }

        /* Hide the frame at initial time */
        c_wgl_set_visibility(pt_this->h_main_frm, WGL_SW_HIDE);

        /* Return the main frame handle */
        *ph_handle_out = pt_this->h_main_frm;

        /* Set attach data */
        i4_ret = _vkb_set_attach_data(pt_this->h_main_frm, pt_this);
        if(i4_ret != WDKR_OK)
        {
            break;
        }
        i4_ret = _vkb_set_attach_data(pt_this->h_input_editbox, pt_this);
        if(i4_ret != WDKR_OK)
        {
            break;
        }
        i4_ret = WDKR_OK;

    } while(0);

    pt_this->h_input_eb_self = pt_this->h_input_editbox;

    i4_ret = _vkb_change_skin(pt_this->h_main_frm, pt_init_data);
    if (i4_ret != WDKR_OK)
    {
        DBG_INFO(("%s(): _vkb_change_skin return %d\n", __FUNCTION__, i4_ret));
    }

    /* set initial foucs data */
    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row = 0;
    pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = 0;

    if(i4_ret != WDKR_OK)
    {
        if (pt_this->h_main_frm != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_this->h_main_frm);
        }
        c_mem_free(pt_this);
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_vkb_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_vkb_create(VKB_INIT_T*              pt_init_data,       /* IN */
                   HANDLE_T*                ph_handle_out       /* OUT */)
{
    return a_vkb_create_v2(pt_init_data, ph_handle_out);;
}

INT32 a_vkb_destroy(HANDLE_T      h_vkb_handle)
{
    return _vkb_destroy(h_vkb_handle);;
}

INT32 a_vkb_repaint(HANDLE_T      h_vkb_handle)
{
    INT32 i4_ret = WDKR_OK;

    i4_ret = c_wgl_repaint(h_vkb_handle, NULL, TRUE);
    WDK_CHK_FAIL (i4_ret);

    VKB_CONTROL_LOGIC_T* pt_this = NULL;

    i4_ret = c_wgl_do_cmd(h_vkb_handle,
                           WGL_CMD_GL_GET_ATTACH_DATA,
                           WGL_PACK(&pt_this),
                           NULL);
    WDK_CHK_FAIL (i4_ret);

    if (NULL == pt_this)
    {
        return WDKR_INV_ARG;
    }
    c_wgl_repaint(pt_this->h_input_editbox, NULL, TRUE);
    c_wgl_repaint(pt_this->t_eb_clear_icon.h_eb_clear_icon, NULL, TRUE);

    return WDKR_OK;
}

INT32 a_vkb_set_visibility(HANDLE_T       h_vkb_handle,
                             BOOL           b_visible)
{
    INT32 i4_ret = WDKR_OK;
    BOOL b_is_eb_attach = FALSE;
    BOOL b_is_eb_clr_attach = FALSE;
    BOOL b_old_visible = FALSE;
    VKB_CONTROL_LOGIC_T* pt_this = NULL;

    /* 1. Get attach data */
    i4_ret = c_wgl_do_cmd(h_vkb_handle,
                       WGL_CMD_GL_GET_ATTACH_DATA,
                       WGL_PACK(&pt_this),
                       NULL);
    WDK_CHK_FAIL (i4_ret);

    if (NULL == pt_this)
    {
        return WDKR_INV_ARG;
    }

    c_wgl_get_visibility(h_vkb_handle, &b_old_visible);
    if (FALSE == b_old_visible
        && TRUE == b_visible)
    {
    #ifdef APP_VKB_SUPPORT_LATIN_CHAR
        _vkb_view_reset_ctrl_key_latinlock(pt_this, FALSE);
    #endif
        /* update internal focus data */
        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row = 0;
        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = 0;
    }

    if (!b_visible)
    {
    #ifdef APP_VKB_SUPPORT_LATIN_CHAR
        _vkb_view_reset_ctrl_key_latinlock(pt_this, FALSE);
    #endif

        /* update internal focus data */
        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row = 0;
        pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = 0;
    }

    WGL_SW_CMD_T t_sw_sta = (b_visible ? WGL_SW_RECURSIVE: WGL_SW_HIDE);

    i4_ret = c_wgl_set_visibility (h_vkb_handle, t_sw_sta);
    WDK_CHK_FAIL(i4_ret);

    DBG_INFO(("%s(): ui4_style_mask = %x\n", __FUNCTION__, pt_this->ui4_style_mask));

    if (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_DROP_DOWN)
    {
        c_wgl_set_visibility(pt_this->h_input_eb_self, WGL_SW_HIDE);
    }

    _vkb_set_visiable_full_screen_style(pt_this);
    a_vkb_is_eb_attach(h_vkb_handle, &b_is_eb_attach, &b_is_eb_clr_attach);

    _set_cur_attached_vkb_handle(h_vkb_handle);

    if (b_is_eb_attach)
    {
        c_wgl_set_visibility(pt_this->h_input_eb_self, WGL_SW_HIDE);
        c_wgl_set_visibility(pt_this->t_eb_clear_icon.h_eb_clear_icon_self, WGL_SW_HIDE);
        c_wgl_set_visibility(pt_this->h_input_editbox, (b_visible ? WGL_SW_NORMAL : WGL_SW_HIDE));
    }
#if _ENABLE_EB_CLR_ICON
    if (b_visible)
    {
        _vkb_show_eb_clr(h_vkb_handle, FALSE);
    }
    else
    {
        _vkb_hide_eb_clr(h_vkb_handle, FALSE);
    }
#endif

    _vkb_chg_lang(pt_this);

    return WDKR_OK;
}

INT32 a_vkb_set_focus(HANDLE_T                h_vkb_handle)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T* pt_this = NULL;

    /* 1. Get attach data */
    i4_ret = c_wgl_do_cmd(h_vkb_handle,
                       WGL_CMD_GL_GET_ATTACH_DATA,
                       WGL_PACK(&pt_this),
                       NULL);
    WDK_CHK_FAIL (i4_ret);

    if (NULL == pt_this)
    {
        return WDKR_INV_ARG;
    }

    /* set initial foucs */
    i4_ret = a_vkb_set_focus_to_current_btn(h_vkb_handle, FALSE);
    WDK_CHK_FAIL(i4_ret);

    /* set main frame to topmost */
    /* Inset arrow to TOPMOST */
    i4_ret = c_wgl_insert (pt_this->h_main_frm,
                       NULL_HANDLE,
                       WGL_INSERT_TOPMOST,
                       WGL_NO_AUTO_REPAINT);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

INT32 a_vkb_set_focus_sync(HANDLE_T                h_vkb_handle)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T* pt_this = NULL;

    /* 1. Get attach data */
    i4_ret = c_wgl_do_cmd(h_vkb_handle,
                       WGL_CMD_GL_GET_ATTACH_DATA,
                       WGL_PACK(&pt_this),
                       NULL);
    WDK_CHK_FAIL (i4_ret);

    if (NULL == pt_this)
    {
        return WDKR_INV_ARG;
    }

    /* set initial foucs */
    i4_ret = _vkb_set_focus_item(pt_this, VKB_FOCUS_CHG_INITIAL, TRUE);
    WDK_CHK_FAIL(i4_ret);

    /* set main frame to topmost */
    /* Inset arrow to TOPMOST */
    i4_ret = c_wgl_insert (pt_this->h_main_frm,
                       NULL_HANDLE,
                       WGL_INSERT_TOPMOST,
                       WGL_NO_AUTO_REPAINT);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

INT32 a_vkb_show(HANDLE_T                h_vkb_handle)
{
    INT32   i4_ret = WDKR_OK;

    i4_ret = a_vkb_set_visibility(h_vkb_handle, TRUE);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = a_vkb_set_focus(h_vkb_handle);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = a_vkb_repaint(h_vkb_handle);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

INT32 a_vkb_hide(HANDLE_T                h_vkb_handle)
{
    INT32   i4_ret = WDKR_OK;

    i4_ret = a_vkb_set_visibility(h_vkb_handle, FALSE);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = a_vkb_repaint(h_vkb_handle);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

INT32 a_vkb_do_cmd(HANDLE_T                h_vkb_handle,   /* IN */
                   VKB_CMD_TYPE_T          e_cmd,          /* IN */
                   VOID*                   pv_param1,
                   VOID*                   pv_param2)
{
    INT32                   i4_ret = WDKR_OK;
    UINT32                  ui4_len;
    UTF16_T*                pw2s_text;
    VKB_CONTROL_LOGIC_T*    pt_this;

    /* check valid of argument */
    if (NULL_HANDLE == h_vkb_handle)
    {
        return WDKR_INV_ARG;
    }

    /* 1. Get attach data */
    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    /* 2. Dispatch cmd type */
    switch (e_cmd)
    {
        case VKB_CMD_SET_INITIAL_TEXT:
        {
            /* pv_param1 is pointer to UTF16_T */
            pw2s_text = (UTF16_T*)pv_param1;

            /* store initial text to internal buffer */
            c_memset(pt_this->aw2s_txt, 0, sizeof(pt_this->aw2s_txt));
            c_uc_w2s_strncpy(pt_this->aw2s_txt, pw2s_text, VKB_INPUT_TEXT_MAX_LEN);

            /* update buffer content to editbox widget */
            i4_ret = _vkb_view_editbox_set_text(pt_this, pt_this->aw2s_txt, FALSE);
            WDK_CHK_FAIL(i4_ret);
        }
        break;

        case VKB_CMD_SET_STYLE_MASK:
        {
            /* param1: UINT32 ui4_style_mask */
            ui4_len = (UINT32)pv_param1;

            /* check style validation */

            /* set style to control data */
            pt_this->ui4_style_mask = ui4_len;

            if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN) != 0)
            {
                pt_this->ui4_style_mask = (pt_this->ui4_style_mask | VKB_STYLE_MASK_WZD_DROP_DOWN);
            }

        }
        case VKB_CMD_GET_STYLE_MASK:
        {
            if (NULL == pv_param1
                || (SIZE_T)pv_param2 < sizeof(UINT32))
            {
                break;
            }
            *((UINT32*)pv_param1) = pt_this->ui4_style_mask;
            break;
        }

        case VKB_CMD_SET_LABEL_TEXT:
        {
            /* pv_param1 is pointer to UTF16_T */
            pw2s_text   = (UTF16_T*)pv_param1;
            i4_ret = a_wdk_text_set_text(pt_this->h_label_txt, pw2s_text);
            WDK_CHK_FAIL(i4_ret);
        }
        break;

        case VKB_CMD_SET_OK_BTN_TEXT:
        {
            /* pv_param1 is pointer to UTF16_T */
            pw2s_text   = (UTF16_T*)pv_param1;

            c_memset(pt_this->aw2s_ok_txt, 0, 32);
            c_uc_w2s_strncpy(pt_this->aw2s_ok_txt, pw2s_text, 32);

            i4_ret = a_wdk_text_set_text(pt_this->h_ok_txt, pw2s_text);
            WDK_CHK_FAIL(i4_ret);
        }
        break;

        case VKB_CMD_SET_CANCEL_BTN_TEXT:
        {
            /* pv_param1 is pointer to UTF16_T */
            /* pv_param2 is length of text */
            pw2s_text   = (UTF16_T*)pv_param1;

            c_memset(pt_this->aw2s_cncl_txt, 0, 32);
            c_uc_w2s_strncpy(pt_this->aw2s_cncl_txt, pw2s_text, 32);

            i4_ret = a_wdk_text_set_text(pt_this->h_cancel_txt, pw2s_text);
            WDK_CHK_FAIL(i4_ret);
        }
        break;

        case VKB_CMD_SET_MAX_CHAR_NUM:
        {
            /* pv_param1 is max length */
            ui4_len = (UINT32)pv_param1;
            if (ui4_len > VKB_INPUT_TEXT_MAX_LEN)
            {
                WDK_CHK_FAIL(WDKR_INV_ARG);
            }
            pt_this->ui4_max_char_num = (ui4_len - 1 );
        }
        break;

        case VKB_CMD_CLEAR_TEXT:
        {
            /* reset internal buffer */
            c_memset(pt_this->aw2s_txt, 0, sizeof(pt_this->aw2s_txt));

            /* update buffer content to editbox widget */
            i4_ret = _vkb_view_editbox_set_text(pt_this, pt_this->aw2s_txt, FALSE);
            WDK_CHK_FAIL(i4_ret);
        }
        break;

        case VKB_CMD_GET_TEXT:
        {
            /* pv_param1 is pointer to UTF16_T */
            /* pv_param2 is length of text */
            pw2s_text = (UTF16_T*)pv_param1;
            ui4_len = (UINT32)pv_param2;

            c_uc_w2s_strncpy(pw2s_text, pt_this->aw2s_txt, ui4_len);
        }
        break;

        case VKB_CMD_GET_EB_CONTENT:
        {
            pw2s_text = (UTF16_T*)pv_param1;
            ui4_len = (UINT32)pv_param2;

            _vkb_view_editbox_get_text(pt_this, pw2s_text, ui4_len);
        }
        break;

        case VKB_CMD_GET_ATTACH_DATA:
        {
            VKB_EB_ATTACH_DATE *pt_attach_data = NULL;
            pt_attach_data = (VKB_EB_ATTACH_DATE*)pv_param1;

            COPY_ATTACH_DATA(pt_attach_data, &pt_this->t_eb_attach_data);
        }
        break;

        case VKB_CMD_GET_CTRL_BTN_IDX:
        {
            if (NULL == pv_param1)
            {
                i4_ret = WDKR_INV_ARG;
                break;
            }
            *(UINT16 *)pv_param1 = pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx;
            break;
        }
        case VKB_CMD_GET_NORMAL_BTN_IDX:
        {
            if (NULL == pv_param1 || NULL == pv_param2)
            {
                i4_ret = WDKR_INV_ARG;
                break;
            }
            *(UINT16 *)pv_param1 = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row;
            *(UINT16 *)pv_param2 = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col;
            break;
        }
        case VKB_CMD_GET_LATIN_BTN_IDX:
        {
            UINT8   ui1_key_idx = 0;

            if (NULL == pv_param1)
            {
                i4_ret = WDKR_INV_ARG;
                break;
            }

            ui1_key_idx = pt_this->ui1_cur_latin_key_idx;
            *(UINT16 *)pv_param1 = pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col - pt_this->at_keypad_latin_key[ui1_key_idx].ui1_col_offset;

            break;
        }
        case VKB_CMD_GET_CUR_LATIN_NUM:
        {
            UINT8   ui1_key_idx = 0;

            if (NULL == pv_param1)
            {
                i4_ret = WDKR_INV_ARG;
                break;
            }

            ui1_key_idx = pt_this->ui1_cur_latin_key_idx;
            *(UINT16 *)pv_param1 = (UINT16)pt_this->at_keypad_latin_key[ui1_key_idx].ui1_elem_num;
            break;
        }

        default:
            break;
    }

    return i4_ret;
}

INT32 a_vkb_current_is_top_row(HANDLE_T     h_vkb_handle,
                               BOOL*        pb_is_top_row)
{
    INT32                 i4_ret;
    VKB_CONTROL_LOGIC_T*  pt_this;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if (WDK_NO_ACTION != _vkb_full_screen_is_top_row(pt_this, pb_is_top_row))
    {
        return WDKR_OK;
    }

    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD) ||
        (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD) ||
        (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID)||
        (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU)||
        (pt_this->ui4_style_mask & VKB_STYLE_MASK_WZD_PWD) ||
        (pt_this->b_eb_attached))
    {
        if(pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_EDIT_BOX
            || pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_EB_CLR)
        {
            *pb_is_top_row = TRUE;
        }
        else
        {
            *pb_is_top_row = FALSE;
        }
    }
    else
    {
        if((pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY) &&
           (0 == pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row))
        {
           *pb_is_top_row = TRUE;
        }
        else
        {
            *pb_is_top_row = FALSE;

            if (pt_this->b_latin_expand
                && (pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY))
            {
                *pb_is_top_row = TRUE;
            }
        }
    }

    return WDKR_OK;
}

INT32 a_vkb_current_is_bottom_row(HANDLE_T      h_vkb_handle,
                                  HANDLE_T*     ph_cancel_handle,
                                  BOOL*         pb_is_bottom_row)
{
    INT32                 i4_ret;
    VKB_CONTROL_LOGIC_T*  pt_this;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if (WDK_NO_ACTION != _vkb_full_screen_is_bootom_row(pt_this, pb_is_bottom_row))
    {
        return WDKR_OK;
    }

    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_PWD)
        || (pt_this->ui4_style_mask & VKB_STYLE_MASK_WIFI_SSID)
        || (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN))
    {
        if(pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY)
        {
           *pb_is_bottom_row = TRUE;
           if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx < VKB_KEYPAD_CTRL_KEY_TEXT_NUM)
           {
              *ph_cancel_handle = pt_this->ah_ctrl_key_txt[pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx];
           }
        }
        else
        {
            *pb_is_bottom_row = FALSE;
        }

        if (pt_this->b_latin_expand
            && (pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY))
        {
            *pb_is_bottom_row = TRUE;
            *ph_cancel_handle = pt_this->aah_normal_key_txt[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row][pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col];
        }
    }
    else
    {
        if(pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_CANCEL)
        {
           *pb_is_bottom_row = TRUE;
           *ph_cancel_handle = pt_this->h_cancel_txt;
        }
        else
        {
            *pb_is_bottom_row = FALSE;
        }
    }
    return i4_ret;
}

INT32 a_vkb_set_focus_to_current_btn(HANDLE_T h_vkb_handle, BOOL b_repaint)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T* pt_this = NULL;

    /* 1. Get attach data */
    i4_ret = c_wgl_do_cmd(h_vkb_handle,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_this),
                          NULL);
    WDK_CHK_FAIL (i4_ret);

    if (NULL == pt_this)
    {
        return WDKR_INV_ARG;
    }

    /* set focus depend on internal focus data */
    switch (pt_this->t_focus_item.e_type)
    {
        case VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY:
        {
            /* set focus on keypad normal key */
            if ((pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row < VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM)&&
                (pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col < VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM))
            {
                i4_ret = c_wgl_set_focus (pt_this->aah_normal_key_txt[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row][pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col],
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);
            }
        }
            break;

        case VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY:
        {
            /* set focus on keypad ctrl key */
            if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx < VKB_KEYPAD_CTRL_KEY_TEXT_NUM)
            {
                i4_ret = c_wgl_set_focus (pt_this->ah_ctrl_key_txt[pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx],
                                          b_repaint);
                WDK_CHK_FAIL(i4_ret);
            }
        }
            break;

        case VKB_FOCUS_WIDGET_BTN_OK:
        case VKB_FOCUS_WIDGET_BTN_CANCEL:
        {
            /* update internal focus data */
            if (pt_this->b_latin_expand)
            {
                pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                i4_ret = c_wgl_set_focus (pt_this->aah_normal_key_txt[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row][pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col],
                                              b_repaint);
            }
            else
            {
                pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                i4_ret = c_wgl_set_focus (pt_this->ah_ctrl_key_txt[pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx],
                                              b_repaint);
            }
            WDK_CHK_FAIL(i4_ret);
        }
            break;

        case VKB_FOCUS_WIDGET_EDIT_BOX:
        {
            /* update internal focus data */
            pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
            i4_ret = c_wgl_set_focus (pt_this->aah_normal_key_txt[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row][pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col],
                                      b_repaint);
            WDK_CHK_FAIL(i4_ret);
        }
            break;
        case VKB_FOCUS_WIDGET_EB_CLR:
        {
            /* update internal focus data */
            pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
            i4_ret = c_wgl_set_focus (pt_this->aah_normal_key_txt[pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row][pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col],
                                      b_repaint);
            WDK_CHK_FAIL(i4_ret);
        }
            break;
        default:
            break;
    }
    c_wgl_repaint(h_vkb_handle,NULL,FALSE);
    return WDKR_OK;
}

INT32 a_vkb_set_focus_to_ok(HANDLE_T        h_vkb_handle)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T* pt_this = NULL;

    /* 1. Get attach data */
    i4_ret = c_wgl_do_cmd(h_vkb_handle,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_this),
                          NULL);
    WDK_CHK_FAIL (i4_ret);

    if (NULL == pt_this)
    {
        return WDKR_INV_ARG;
    }

    if (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN)
    {
        return WDKR_OK;
    }

    if (_vkb_is_full_screen_style(h_vkb_handle)
        && 0 == (pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_OK))
    {
        if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx < VKB_KEYPAD_CTRL_KEY_TEXT_NUM)
        {
            i4_ret = c_wgl_set_focus (pt_this->ah_ctrl_key_txt[pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx],
                                      FALSE);
            WDK_CHK_FAIL(i4_ret);
        }

        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
    }
    else
    {/* set foucs to ok text */
        i4_ret = c_wgl_set_focus (pt_this->h_ok_txt, WGL_SYNC_AUTO_REPAINT);
        WDK_CHK_FAIL(i4_ret);

        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_OK;

        _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_BTN_OK);
    }

    /* set main frame to topmost */
    /* Inset arrow to TOPMOST */
    i4_ret = c_wgl_insert (pt_this->h_main_frm,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

INT32 a_vkb_set_focus_to_cancel(HANDLE_T        h_vkb_handle)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T* pt_this = NULL;

    /* 1. Get attach data */
    i4_ret = c_wgl_do_cmd(h_vkb_handle,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_this),
                          NULL);
    WDK_CHK_FAIL (i4_ret);
    if (NULL == pt_this)
    {
        return WDKR_INV_ARG;
    }

    if (pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN)
    {
        return WDKR_OK;
    }

    if (_vkb_is_full_screen_style(h_vkb_handle)
        && 0 == (pt_this->ui4_style_mask & VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_CANCLE))
    {
        if (pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx < VKB_KEYPAD_CTRL_KEY_TEXT_NUM)
        {
            i4_ret = c_wgl_set_focus (pt_this->ah_ctrl_key_txt[pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx],
                                      FALSE);
            WDK_CHK_FAIL(i4_ret);
        }

        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
    }
    else
    {
        /* set foucs to cancel text */
        i4_ret = c_wgl_set_focus (pt_this->h_cancel_txt, WGL_SYNC_AUTO_REPAINT);
        WDK_CHK_FAIL(i4_ret);

        pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_CANCEL;

        _vkb_view_play_tts(pt_this, VKB_FOCUS_WIDGET_BTN_CANCEL);
    }

    /* set main frame to topmost */
    /* Inset arrow to TOPMOST */
    i4_ret = c_wgl_insert (pt_this->h_main_frm,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

INT32 a_vkb_current_is_ok_btn(HANDLE_T  h_vkb_handle,
                              BOOL*     pb_is_ok_btn)
{
    INT32                 i4_ret;
    VKB_CONTROL_LOGIC_T*  pt_this;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if(pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_OK)
    {
       *pb_is_ok_btn = TRUE;
    }
    else
    {
        *pb_is_ok_btn = FALSE;
    }

    return i4_ret;
}

INT32 a_vkb_current_is_cancel_btn(HANDLE_T  h_vkb_handle,
                              BOOL*     pb_is_cancel_btn)
{
    INT32                 i4_ret;
    VKB_CONTROL_LOGIC_T*  pt_this;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if(pt_this->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_CANCEL)
    {
       *pb_is_cancel_btn = TRUE;
    }
    else
    {
        *pb_is_cancel_btn = FALSE;
    }

    return i4_ret;
}

/* disable cancel button and you must manually adjust the navgation */
INT32 a_vkb_enable_cancel_btn (HANDLE_T     h_vkb_handle,
                               BOOL         b_enable)
{
    INT32                 i4_ret;
    VKB_CONTROL_LOGIC_T*  pt_this;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_enable(pt_this->h_cancel_txt, b_enable);
    WDK_CHK_FAIL(i4_ret);
    c_wgl_repaint(pt_this->h_cancel_txt,NULL,TRUE);
    return i4_ret;
}

/* disable OK button and you must manually adjust the navgation */
INT32 a_vkb_enable_ok_btn (HANDLE_T     h_vkb_handle,
                           BOOL         b_enable)
{
    INT32                 i4_ret;
    VKB_CONTROL_LOGIC_T*  pt_this;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_enable(pt_this->h_ok_txt, b_enable);
    WDK_CHK_FAIL(i4_ret);
    c_wgl_repaint(pt_this->h_ok_txt,NULL,TRUE);
    return i4_ret;
}

UINT8 a_vkb_current_get_row_index(HANDLE_T  h_vkb_handle)
{
    INT32                 i4_ret;
    VKB_CONTROL_LOGIC_T*  pt_this;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    return pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row;
}

UINT8 a_vkb_current_get_col_index(HANDLE_T  h_vkb_handle)
{
    INT32                 i4_ret;
    VKB_CONTROL_LOGIC_T*  pt_this;

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if (VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY == pt_this->t_focus_item.e_type)
    {
        return pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col;
    }
    else
    {
        return pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx;
    }

}

INT32 a_vkb_set_focus_ex(HANDLE_T       h_vkb_handle)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T* pt_this = NULL;

    /* 1. Get attach data */
    i4_ret = c_wgl_do_cmd(h_vkb_handle,
                       WGL_CMD_GL_GET_ATTACH_DATA,
                       WGL_PACK(&pt_this),
                       NULL);
    WDK_CHK_FAIL (i4_ret);

    if (NULL == pt_this)
    {
        return WDKR_INV_ARG;
    }

    if ((pt_this->ui4_style_mask & VKB_STYLE_MASK_MENU_NO_EB_NO_BTN)
        && pt_this->b_eb_attached == FALSE)
    {
        return WDKR_OK;
    }
    /* set foucs to edit box*/
    i4_ret = c_wgl_set_focus (pt_this->h_input_editbox, WGL_SYNC_AUTO_REPAINT);
    WDK_CHK_FAIL(i4_ret);
    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_EDIT_BOX;

    /* set main frame to topmost */
    /* Inset arrow to TOPMOST */
    i4_ret = c_wgl_insert (pt_this->h_main_frm,
                       NULL_HANDLE,
                       WGL_INSERT_TOPMOST,
                       WGL_NO_AUTO_REPAINT);
    WDK_CHK_FAIL(i4_ret);
    c_wgl_repaint(h_vkb_handle,NULL,TRUE);
    return WDKR_OK;
}

INT32 a_vkb_reset_eb_handle(HANDLE_T h_vkb_handle)
{
    INT32 i4_ret = WDKR_OK;
    BOOL b_visible = TRUE;
    VKB_CONTROL_LOGIC_T *pt_this = NULL;

    if (NULL_HANDLE == h_vkb_handle)
    {
        DBG_INFO(("%s(): NULL HANDLE ERROR!!\n", __FUNCTION__));
        return WDKR_INV_ARG;
    }

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    pt_this->b_eb_attached = FALSE;
    pt_this->h_input_editbox = pt_this->h_input_eb_self;

    if (TRUE == pt_this->t_eb_clear_icon.b_eb_clr_attached)
    {
        pt_this->t_eb_clear_icon.b_eb_clr_attached = FALSE;
        pt_this->t_eb_clear_icon.h_eb_clear_icon = pt_this->t_eb_clear_icon.h_eb_clear_icon_self;
    }

    /* Refresh */
    c_wgl_get_visibility(h_vkb_handle, &b_visible);
    a_vkb_set_visibility(h_vkb_handle, b_visible);

    return i4_ret;
}

INT32 a_vkb_attach_eb(HANDLE_T h_vkb_handle, VKB_EB_ATTACH_DATE *pt_attach_data)
{
    INT32 i4_ret = WDKR_OK;
    BOOL  b_visible = TRUE;
    VKB_CONTROL_LOGIC_T *pt_this = NULL;

    if (!_is_valid_attach_data(pt_attach_data)
        || NULL_HANDLE == h_vkb_handle)
    {
        DBG_INFO(("%s(): ARG error!\n"));
        return WDKR_INV_ARG;
    }

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    COPY_ATTACH_DATA(&pt_this->t_eb_attach_data, pt_attach_data);

    pt_this->b_eb_attached = TRUE;
    pt_this->h_input_eb_self = pt_this->h_input_editbox;
    pt_this->h_input_editbox = pt_this->t_eb_attach_data.h_edit_box;

    pt_this->t_eb_clear_icon.h_eb_clear_icon_self = pt_this->t_eb_clear_icon.h_eb_clear_icon;
    pt_this->t_eb_clear_icon.h_eb_clear_icon = pt_attach_data->h_eb_clr;
    pt_this->t_eb_clear_icon.b_eb_clr_attached = pt_attach_data->b_need_eb_clr;

    c_wgl_set_widget_proc(pt_this->t_eb_clear_icon.h_eb_clear_icon, _vkb_view_eb_clear_icon_proc_fct);
    c_wgl_set_widget_proc(pt_this->h_input_editbox, _vkb_view_eb_proc_fct_ex);

    /* Refresh */
    c_wgl_get_visibility(h_vkb_handle, &b_visible);
    a_vkb_set_visibility(h_vkb_handle, b_visible);

    return i4_ret;
}

INT32 a_vkb_is_eb_attach(HANDLE_T h_vkb_handle, BOOL *pb_is_eb_attach, BOOL *pb_is_eb_clr_attach)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T *pt_this = NULL;

    if (NULL_HANDLE == h_vkb_handle
        || NULL == pb_is_eb_attach
        || NULL == pb_is_eb_clr_attach)
    {
        return WDKR_INV_ARG;
    }

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    *pb_is_eb_attach = pt_this->b_eb_attached;
    *pb_is_eb_clr_attach = pt_this->t_eb_clear_icon.b_eb_clr_attached;

    return i4_ret;
}

VOID a_vkb_set_lang(CHAR *ps_lang)
{
    if (NULL == ps_lang)
    {
        g_ui2_lang_id = 0;
    }
    else if (c_strncmp(ps_lang, VKB_LANGUAGE_ENG, 3) == 0)
    {
        g_ui2_lang_id = 0;
    }
    else if (c_strncmp(ps_lang, VKB_LANGUAGE_FRE, 3) == 0)
    {
        g_ui2_lang_id = 1;
    }
    else if (c_strncmp(ps_lang, VKB_LANGUAGE_SPA, 3) == 0)
    {
        g_ui2_lang_id = 2;
    }
    else
    {
        g_ui2_lang_id = 0;
    }


}

INT32 a_vkb_is_latin_stat(HANDLE_T h_vkb_handle, BOOL *pb_latin)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T *pt_this = NULL;

    *pb_latin = FALSE;

    if (NULL_HANDLE == h_vkb_handle)
    {
        return WDKR_INV_ARG;
    }

    i4_ret = _vkb_get_attach_data(h_vkb_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    if (pt_this->b_latin_lock || pt_this->b_latin_expand)
    {
        *pb_latin = TRUE;
    }

    return i4_ret;
}

INT32 a_vkb_set_focus_ctrl_del(HANDLE_T h_vkb_handle, BOOL b_repaint)
{
    INT32 i4_ret = WDKR_OK;
    VKB_CONTROL_LOGIC_T* pt_this = NULL;

    i4_ret = c_wgl_do_cmd(h_vkb_handle,
                       WGL_CMD_GL_GET_ATTACH_DATA,
                       WGL_PACK(&pt_this),
                       NULL);
    WDK_CHK_FAIL (i4_ret);

    if (NULL == pt_this)
    {
        return WDKR_INV_ARG;
    }

    pt_this->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
    //pt_this->t_focus_item.t_normal_key.ui1_focus_idx_row = 0;
    //pt_this->t_focus_item.t_normal_key.ui1_focus_idx_col = 0;
    pt_this->t_focus_item.t_ctrl_key.ui1_focus_idx = VKB_KEYPAD_CTRL_DEL_KEY_IDX;

    i4_ret = c_wgl_set_focus (pt_this->ah_ctrl_key_txt[VKB_KEYPAD_CTRL_DEL_KEY_IDX],
                              (b_repaint ? WGL_SYNC_AUTO_REPAINT : WGL_NO_AUTO_REPAINT));
    WDK_CHK_FAIL(i4_ret);

    /* set main frame to topmost */
    /* Inset arrow to TOPMOST */
    i4_ret = c_wgl_insert (pt_this->h_main_frm,
                       NULL_HANDLE,
                       WGL_INSERT_TOPMOST,
                       WGL_NO_AUTO_REPAINT);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}
