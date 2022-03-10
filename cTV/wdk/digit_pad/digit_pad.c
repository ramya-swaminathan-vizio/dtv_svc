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
 * $RCSfile: digit_pad.c $
 * $Revision: #1 $
 * $Date: 2020/03/20 $
 * $Author: yuwen.han $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: yuwen.han $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: GUI composite component -- Time Entry
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "digit_pad.h"
#include "res/app_util/tts/a_tts_custom.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#ifndef COLOR_COPY
#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))
#endif
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static CHAR digit_pad_digit_text[DIGIT_PAD_DIGIT_ROW_NUM][DIGIT_PAD_DIGIT_COL_NUM] =
{
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'-', '0', ' '}
};

static UTF16_T* w2s_digit_pad_digit_text[DIGIT_PAD_DIGIT_ROW_NUM][DIGIT_PAD_DIGIT_COL_NUM] =
{
    {L"1", L"2", L"3"},
    {L"4", L"5", L"6"},
    {L"7", L"8", L"9"},
    {L"-", L"0", L" "}
};

static UTF16_T* w2s_digit_tts_text[DIGIT_PAD_DIGIT_ROW_NUM][DIGIT_PAD_DIGIT_COL_NUM] =
{
    {L"1", L"2", L"3"},
    {L"4", L"5", L"6"},
    {L"7", L"8", L"9"},
    {L"dash", L"0", L"delete"}
};


static INT32 _digit_create_main_frame(DIGIT_PAD* pt_this);
static INT32 _digit_create_digit_keys(DIGIT_PAD* pt_this);
static INT32 _digit_create_info_ok_buttons(DIGIT_PAD* pt_this);
static INT32 _digit_create_buttons(DIGIT_PAD* pt_this);
static INT32 _digit_key_wdgt_proc_fct(HANDLE_T h_widget,
                                      UINT32 ui4_msg,
                                      VOID* pv_param1,
                                      VOID* pv_param2);
static INT32 _digit_key_set_text_keymap(HANDLE_T h_txt_handle);
static INT32 _digit_pad_set_attach_data(HANDLE_T h_digit_handle, DIGIT_PAD* pdigit_pad);
static INT32 _digit_pad_get_attach_data(HANDLE_T h_digit_handle, DIGIT_PAD** ppdigit_pad);
static INT32 _digit_button_wdgt_proc_fct(HANDLE_T h_widget,
                                         UINT32 ui4_msg,
                                         VOID* pv_param1,
                                         VOID* pv_param2);
static INT32 _digit_change_language(DIGIT_PAD* pt_this);

/*-----------------------------------------------------------------------------
 * methods implementations
 *---------------------------------------------------------------------------*/
VOID a_digit_pad_init_config(DIGIT_PAD_CONFIG* pdigit_cfg)
{
    pdigit_cfg->parent_frame = NULL_HANDLE;
    pdigit_cfg->position.ui4_left = 0;
    pdigit_cfg->position.ui4_top = 0;
    pdigit_cfg->digit_key_event_nfy = NULL;
    pdigit_cfg->btn_ok.b_enable = FALSE;
    pdigit_cfg->btn_cancel.b_enable = FALSE;
    pdigit_cfg->b_dash_key_enable = FALSE;
    pdigit_cfg->b_dash_key_grayout= FALSE;
    pdigit_cfg->b_del_key_grayout = FALSE;
    pdigit_cfg->pf_rc_event_default_handle = NULL;
    pdigit_cfg->b_info_ok_key_enable = FALSE;
}

INT32 a_digit_pad_create(DIGIT_PAD_CONFIG digit_cfg,
                         HANDLE_T* ph_digit_handle)
{
    INT32 i4_ret = WDKR_OK;
    DIGIT_PAD* pt_this;
    pt_this =  (DIGIT_PAD*)c_mem_alloc(sizeof(DIGIT_PAD));
    if (NULL == pt_this)
    {
        return WDKR_OUT_OF_MEMORY;
    }
    pt_this->cfg = digit_cfg;

    i4_ret = _digit_create_main_frame(pt_this);
    WDK_CHK_FAIL(i4_ret);
    *ph_digit_handle = pt_this->main_frame;
    i4_ret = _digit_pad_set_attach_data(pt_this->main_frame, pt_this);
    WDK_CHK_FAIL(i4_ret);
    i4_ret = _digit_create_digit_keys(pt_this);
    WDK_CHK_FAIL(i4_ret);
    i4_ret = _digit_create_info_ok_buttons(pt_this);
    WDK_CHK_FAIL(i4_ret);
    i4_ret = _digit_create_buttons(pt_this);
    WDK_CHK_FAIL(i4_ret);
    return i4_ret;
}

INT32 a_digit_pad_destroy(HANDLE_T h_digit_handle)
{
    INT32 i4_ret = WDKR_OK;
    DIGIT_PAD* pt_this;
    i4_ret = _digit_pad_get_attach_data(h_digit_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    for (UINT8 ui1_row_idx = 0; ui1_row_idx < DIGIT_PAD_DIGIT_ROW_NUM; ui1_row_idx++)
    {
        for (UINT8 ui1_col_idx = 0; ui1_col_idx < DIGIT_PAD_DIGIT_COL_NUM; ui1_col_idx++)
        {
            if (pt_this->digit_key_handles[ui1_row_idx][ui1_col_idx] != NULL_HANDLE)
            {
                i4_ret = c_wgl_destroy_widget(pt_this->digit_key_handles[ui1_row_idx][ui1_col_idx]);
                WDK_CHK_FAIL(i4_ret);
            }
        }
    }
    if (pt_this->btn_ok != NULL_HANDLE)
    {
        i4_ret = c_wgl_destroy_widget(pt_this->btn_ok);
        WDK_CHK_FAIL(i4_ret);
    }
    if (pt_this->btn_cancel != NULL_HANDLE)
    {
        i4_ret = c_wgl_destroy_widget(pt_this->btn_cancel);
        WDK_CHK_FAIL(i4_ret);
    }
    if (pt_this->btn_go != NULL_HANDLE)
    {
        i4_ret = c_wgl_destroy_widget(pt_this->btn_go);
        WDK_CHK_FAIL(i4_ret);
    }
    if (pt_this->btn_info!= NULL_HANDLE)
    {
        i4_ret = c_wgl_destroy_widget(pt_this->btn_info);
        WDK_CHK_FAIL(i4_ret);
    }
    if (pt_this->main_frame != NULL_HANDLE)
    {
        i4_ret = c_wgl_destroy_widget(pt_this->main_frame);
        WDK_CHK_FAIL(i4_ret);
    }

    c_mem_free(pt_this);
    return i4_ret;
}

INT32 a_digit_pad_show(HANDLE_T h_digit_pad_handle)
{
    INT32   i4_ret = WDKR_OK;
    DIGIT_PAD* pt_this;

    i4_ret = a_digit_pad_set_visibility(h_digit_pad_handle, TRUE);
    WDK_CHK_FAIL(i4_ret);


    i4_ret = _digit_pad_get_attach_data(h_digit_pad_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);
    i4_ret = _digit_change_language(pt_this);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = a_digit_pad_repaint(h_digit_pad_handle);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

INT32 a_digit_pad_hide(HANDLE_T h_digit_pad_handle)
{
    INT32   i4_ret = WDKR_OK;

    i4_ret = a_digit_pad_set_visibility(h_digit_pad_handle, FALSE);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = a_digit_pad_repaint(h_digit_pad_handle);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

INT32 a_digit_pad_focus(HANDLE_T h_digit_pad_handle)
{
    INT32   i4_ret = WDKR_OK;
    DIGIT_PAD* pt_this;
    i4_ret = _digit_pad_get_attach_data(h_digit_pad_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);

    pt_this->aui8_current_digit_focus[0] = 1;
    pt_this->aui8_current_digit_focus[1] = 1;

    i4_ret = c_wgl_set_focus(pt_this->digit_key_handles[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]],
                              WGL_ASYNC_AUTO_REPAINT);
    WDK_CHK_FAIL(i4_ret);
    return WDKR_OK;
}

INT32 a_digit_pad_focus_btn_ok(HANDLE_T h_digit_pad_handle)
{
    INT32   i4_ret = WDKR_OK;
    DIGIT_PAD* pt_this;
    i4_ret = _digit_pad_get_attach_data(h_digit_pad_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);
    if (pt_this->cfg.btn_ok.b_enable == TRUE)
    {
        i4_ret = c_wgl_set_focus(pt_this->btn_ok,
                                    WGL_ASYNC_AUTO_REPAINT);
        WDK_CHK_FAIL(i4_ret);
    }
    return i4_ret;
}

INT32 a_digit_pad_repaint(HANDLE_T      h_digit_pad_handle)
{
    INT32 i4_ret = WDKR_OK;

    i4_ret = c_wgl_repaint(h_digit_pad_handle, NULL, TRUE);
    WDK_CHK_FAIL (i4_ret);

    return WDKR_OK;
}

INT32 a_digit_pad_set_visibility(HANDLE_T       h_digit_pad_handle,
                             BOOL           b_visible)
{
    INT32 i4_ret = WDKR_OK;
    WGL_SW_CMD_T t_sw_sta = (b_visible ? WGL_SW_RECURSIVE: WGL_SW_HIDE);
    i4_ret = c_wgl_set_visibility (h_digit_pad_handle, t_sw_sta);
    WDK_CHK_FAIL(i4_ret);
    return WDKR_OK;
}

INT32 a_digit_pad_grayout_dash(HANDLE_T h_digit_pad_handle, BOOL b_gray)
{
    INT32 i4_ret = WDKR_OK;
    DIGIT_PAD* pt_this;
    WGL_IMG_INFO_T t_img_info;
    i4_ret = _digit_pad_get_attach_data(h_digit_pad_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);
    if (pt_this->cfg.b_dash_key_grayout == b_gray)
    {
        return i4_ret;
    }
    pt_this->cfg.b_dash_key_grayout = b_gray;
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    if (b_gray == TRUE)
    {
        t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
        t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
        t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
        if (pt_this->aui8_current_digit_focus[0] == DIGIT_PAD_DIGIT_ROW_NUM - 1
            && pt_this->aui8_current_digit_focus[1] == 0)
        {
            pt_this->aui8_current_digit_focus[1]++;
            i4_ret = c_wgl_set_focus(pt_this->digit_key_handles[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]],
                                     WGL_ASYNC_AUTO_REPAINT);
            WDK_CHK_FAIL(i4_ret);
        }
    }
    else
    {
        t_img_info.u_img_data.t_standard.t_enable    = h_g_digit_pad_digit_key_unfocus_bkg;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_digit_pad_digit_key_unfocus_bkg;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_digit_pad_digit_key_focus_bkg;
    }
    WDK_CHK_FAIL (c_wgl_do_cmd (pt_this->digit_key_handles[DIGIT_PAD_DIGIT_ROW_NUM - 1][0],
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK (WGL_IMG_BK), /* background image */
                                WGL_PACK (& t_img_info)));
    WDK_CHK_FAIL(c_wgl_repaint(pt_this->digit_key_handles[DIGIT_PAD_DIGIT_ROW_NUM - 1][0]
                 , NULL, TRUE));
    return i4_ret;
}


INT32 a_digit_pad_grayout_del(HANDLE_T h_digit_pad_handle, BOOL b_gray)
{
    INT32 i4_ret = WDKR_OK;
    DIGIT_PAD* pt_this;
    WGL_IMG_INFO_T t_img_info;
    i4_ret = _digit_pad_get_attach_data(h_digit_pad_handle, &pt_this);
    WDK_CHK_FAIL(i4_ret);
    if (pt_this->cfg.b_del_key_grayout == b_gray)
    {
        return i4_ret;
    }
    pt_this->cfg.b_del_key_grayout = b_gray;
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    if (b_gray == TRUE)
    {
        t_img_info.u_img_data.t_standard.t_enable    = h_g_digit_pad_del_grayout_bkg;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_digit_pad_del_grayout_bkg;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_digit_pad_del_grayout_bkg;
        if (pt_this->aui8_current_digit_focus[0] == DIGIT_PAD_DIGIT_ROW_NUM - 1
            && pt_this->aui8_current_digit_focus[1] == DIGIT_PAD_DIGIT_COL_NUM - 1)
        {
            pt_this->aui8_current_digit_focus[1]--;
            i4_ret = c_wgl_set_focus(pt_this->digit_key_handles[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]],
                                     WGL_ASYNC_AUTO_REPAINT);
            WDK_CHK_FAIL(i4_ret);
        }
    }
    else
    {
        t_img_info.u_img_data.t_standard.t_enable    = h_g_digit_pad_del_unfocus_bkg;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_digit_pad_del_unfocus_bkg;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_digit_pad_del_focus_bkg;
    }
    WDK_CHK_FAIL (c_wgl_do_cmd (pt_this->digit_key_handles[DIGIT_PAD_DIGIT_ROW_NUM - 1][DIGIT_PAD_DIGIT_COL_NUM - 1],
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK (WGL_IMG_BK), /* background image */
                                WGL_PACK (& t_img_info)));
    WDK_CHK_FAIL(c_wgl_repaint(pt_this->digit_key_handles[DIGIT_PAD_DIGIT_ROW_NUM - 1][DIGIT_PAD_DIGIT_COL_NUM - 1]
                 , NULL, TRUE));
    return i4_ret;
}

static INT32 _digit_create_main_frame(DIGIT_PAD* pt_this)
{
    INT32 i4_ret = WDKR_OK;
    GL_RECT_T t_rect;
    WGL_IMG_INFO_T t_img_info;
    UINT32 ui4_main_frame_h = DIGIT_PAD_MAIN_FRAME_H_NO_BTN;
    WGL_HIMG_TPL_T h_main_frame_bkg = h_g_digit_pad_normal_bkg;

    if(pt_this->cfg.b_info_ok_key_enable == TRUE)
    {
        DBG_LOG_PRINT(("[WDK]{%s %d} b_info_ok_key_enable -> change btn_ok & btn_cancel to FLASE\n", __FUNCTION__, __LINE__));
        pt_this->cfg.btn_ok.b_enable = FALSE;
        pt_this->cfg.btn_cancel.b_enable = FALSE;
    }
    if (pt_this->cfg.btn_ok.b_enable == TRUE && pt_this->cfg.btn_cancel.b_enable == TRUE)
    {
        ui4_main_frame_h = DIGIT_PAD_MAIN_FRAME_H_TWO_BTN;
        h_main_frame_bkg = h_g_digit_pad_two_button_bkg;
    }
    else if (pt_this->cfg.btn_ok.b_enable == TRUE || pt_this->cfg.btn_cancel.b_enable == TRUE || pt_this->cfg.b_info_ok_key_enable == TRUE)
    {
        ui4_main_frame_h = DIGIT_PAD_MAIN_FRAME_H_ONE_BTN;
        h_main_frame_bkg = h_g_digit_pad_one_button_bkg;
    }


    /* get rectangle size */
    SET_RECT_BY_SIZE (&t_rect,
                      pt_this->cfg.position.ui4_left,
                      pt_this->cfg.position.ui4_top,
                      DIGIT_PAD_MAIN_FRAME_W,
                      ui4_main_frame_h);
    /* create widget */
    WDK_CHK_FAIL (c_wgl_create_widget (pt_this->cfg.parent_frame,
                                    HT_WGL_WIDGET_FRAME,
                                    WGL_CONTENT_FRAME_DEF,
                                    WGL_BORDER_NULL,
                                    & t_rect,
                                    NULL,
                                    DIGIT_PAD_MAIN_FRAME_ALPHA,
                                    (VOID*)(0),
                                    0,
                                    &pt_this->main_frame));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_main_frame_bkg;
    t_img_info.u_img_data.t_standard.t_highlight = h_main_frame_bkg;
    t_img_info.u_img_data.t_standard.t_disable   = h_main_frame_bkg;
    i4_ret = c_wgl_do_cmd(pt_this->main_frame,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    WDK_CHK_FAIL(i4_ret);
    WDK_CHK_FAIL (c_wgl_set_visibility (pt_this->main_frame, WGL_SW_NORMAL));

    return  i4_ret;
}

static INT32 _digit_create_info_ok_buttons(DIGIT_PAD* pt_this)
{
    INT32                   i4_ret = WDKR_OK;
    WDK_TXT_WIDGET_PARAM_T  t_txt_param;

    if (pt_this->cfg.b_info_ok_key_enable == FALSE)
    {
        return i4_ret;
    }

    // create info button
    c_memset(&t_txt_param, 0, sizeof(WDK_TXT_WIDGET_PARAM_T));
    t_txt_param.h_parent      = pt_this->main_frame;
    t_txt_param.ui1_alpha     = DIGIT_PAD_KEY_TEXT_ALPHA;
    t_txt_param.b_visibility  = TRUE;
    t_txt_param.i4_x          = DIGIT_PAD_BTN_INTERVAL_X;
    t_txt_param.i4_y          = DIGIT_PAD_BTN_INTERVAL_Y
                                + DIGIT_PAD_DIGIT_ROW_NUM * (DIGIT_PAD_NORMAL_KEY_TEXT_H + DIGIT_PAD_KEY_TEXT_INTERVAL_Y);
    t_txt_param.i4_w          = DIGIT_PAD_TWO_COL_BTN_W;
    t_txt_param.i4_h          = DIGIT_PAD_NORMAL_KEY_TEXT_H;
    t_txt_param.ui4_style     = WGL_STL_TEXT_MAX_32 | WGL_STL_TEXT_END_AS_NEWLINE | WGL_STL_TEXT_SMART_CUT;
    t_txt_param.ps_font_name  = DIGIT_PAD_FONT_NAME;
    t_txt_param.e_font_size   = DIGIT_PAD_KEY_TEXT_FONT_SIZE;
    t_txt_param.ui1_font_custom_size = DIGIT_PAD_KEY_TEXT_FONT_CUSTOM_SIZE;
    t_txt_param.e_font_style  = DIGIT_PAD_KEY_TEXT_FONT_STYLE;
    t_txt_param.ui1_align     = DIGIT_PAD_KEY_TEXT_ALIGNMENT;
    t_txt_param.b_img_bk      = TRUE;
    t_txt_param.pt_clr_txt    = & (NAV_COLOR(NAV_COLOR_ID_TEXT));
    t_txt_param.pt_hlt_clr_txt= & (NAV_COLOR(NAV_COLOR_ID_TEXT));
    t_txt_param.pt_dis_clr_txt= & (t_g_menu_color_bk2_txt_disable);

    t_txt_param.t_img_bk.h_enable    = h_g_digit_pad_info_unfocus_bkg;
    t_txt_param.t_img_bk.h_highlight = h_g_digit_pad_info_focus_bkg;
    t_txt_param.t_img_bk.h_disable   = h_g_digit_pad_info_unfocus_bkg;

    t_txt_param.pf_wdgt_proc = _digit_button_wdgt_proc_fct;
    t_txt_param.ph_created_txt= &(pt_this->btn_info);

    i4_ret = a_wdk_create_txt_widget (t_txt_param);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = a_wdk_text_set_text(*t_txt_param.ph_created_txt, L"");
    WDK_CHK_FAIL(i4_ret);

    /* Clear key map to make sure text widget will notify CURSOR key to its parent frame. */
    i4_ret = _digit_key_set_text_keymap(*(t_txt_param.ph_created_txt));
    WDK_CHK_FAIL(i4_ret);


    // create go button
    t_txt_param.i4_x          = DIGIT_PAD_BTN_INTERVAL_X + DIGIT_PAD_NORMAL_KEY_TEXT_W*1.5 + DIGIT_PAD_KEY_TEXT_INTERVAL_X;
    t_txt_param.t_img_bk.h_enable    = h_g_digit_pad_go_unfocus_bkg;
    t_txt_param.t_img_bk.h_highlight = h_g_digit_pad_go_focus_bkg;
    t_txt_param.t_img_bk.h_disable   = h_g_digit_pad_go_unfocus_bkg;

    t_txt_param.pf_wdgt_proc = _digit_button_wdgt_proc_fct;
    t_txt_param.ph_created_txt= &(pt_this->btn_go);

    i4_ret = a_wdk_create_txt_widget (t_txt_param);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = a_wdk_text_set_text(*t_txt_param.ph_created_txt, L"");
    WDK_CHK_FAIL(i4_ret);

    /* Clear key map to make sure text widget will notify CURSOR key to its parent frame. */
    i4_ret = _digit_key_set_text_keymap(*(t_txt_param.ph_created_txt));
    WDK_CHK_FAIL(i4_ret);
    return i4_ret;
}



static INT32 _digit_create_buttons(DIGIT_PAD* pt_this)
{
    INT32                   i4_ret = WDKR_OK;
    WDK_TXT_WIDGET_PARAM_T  t_txt_param;
    if (pt_this->cfg.btn_ok.b_enable == FALSE && pt_this->cfg.btn_cancel.b_enable == FALSE)
    {
        return i4_ret;
    }

    c_memset(&t_txt_param, 0, sizeof(WDK_TXT_WIDGET_PARAM_T));
    t_txt_param.h_parent      = pt_this->main_frame;
    t_txt_param.ui1_alpha     = DIGIT_PAD_KEY_TEXT_ALPHA;
    t_txt_param.b_visibility  = TRUE;
    t_txt_param.i4_x          = DIGIT_PAD_BTN_INTERVAL_X;
    t_txt_param.i4_y          = DIGIT_PAD_BTN_INTERVAL_Y
                                + DIGIT_PAD_DIGIT_ROW_NUM * (DIGIT_PAD_NORMAL_KEY_TEXT_H + DIGIT_PAD_KEY_TEXT_INTERVAL_Y);
    t_txt_param.i4_w          = DIGIT_PAD_BTN_TEXT_W;
    t_txt_param.i4_h          = DIGIT_PAD_BTN_TEXT_H;
    t_txt_param.ui4_style     = WGL_STL_TEXT_MAX_32 | WGL_STL_TEXT_END_AS_NEWLINE | WGL_STL_TEXT_SMART_CUT;
    t_txt_param.ps_font_name  = DIGIT_PAD_FONT_NAME;
    t_txt_param.e_font_size   = DIGIT_PAD_KEY_TEXT_FONT_SIZE;
    t_txt_param.ui1_font_custom_size = DIGIT_PAD_KEY_TEXT_FONT_CUSTOM_SIZE;
    t_txt_param.e_font_style  = DIGIT_PAD_KEY_TEXT_FONT_STYLE;
    t_txt_param.ui1_align     = DIGIT_PAD_KEY_TEXT_ALIGNMENT;
    t_txt_param.b_img_bk      = TRUE;
    t_txt_param.pt_clr_txt    = & (NAV_COLOR(NAV_COLOR_ID_TEXT));
    t_txt_param.pt_hlt_clr_txt= & (NAV_COLOR(NAV_COLOR_ID_TEXT));
    t_txt_param.pt_dis_clr_txt= & (t_g_menu_color_bk2_txt_disable);

    t_txt_param.t_img_bk.h_enable    = h_g_digit_pad_button_unfocus_bkg;
    t_txt_param.t_img_bk.h_highlight = h_g_digit_pad_button_focus_bkg;
    t_txt_param.t_img_bk.h_disable   = h_g_digit_pad_button_unfocus_bkg;

    t_txt_param.pf_wdgt_proc = _digit_button_wdgt_proc_fct;
    if (pt_this->cfg.btn_ok.b_enable == TRUE)
    {
        t_txt_param.ph_created_txt= &(pt_this->btn_ok);

        i4_ret = a_wdk_create_txt_widget (t_txt_param);
        WDK_CHK_FAIL(i4_ret);

        i4_ret = a_wdk_text_set_text(*t_txt_param.ph_created_txt, MENU_TEXT(pt_this->cfg.btn_ok.ui2_text_key));
        WDK_CHK_FAIL(i4_ret);

        /* Clear key map to make sure text widget will notify CURSOR key to its parent frame. */
        i4_ret = _digit_key_set_text_keymap(*(t_txt_param.ph_created_txt));
        WDK_CHK_FAIL(i4_ret);

        t_txt_param.i4_y += DIGIT_PAD_BTN_TEXT_H + DIGIT_PAD_BTN_INTERVAL_Y;
    }
    else
    {
        pt_this->btn_ok = NULL_HANDLE;
    }
    if (pt_this->cfg.btn_cancel.b_enable == TRUE)
    {
        t_txt_param.ph_created_txt= &(pt_this->btn_cancel);

        i4_ret = a_wdk_create_txt_widget (t_txt_param);
        WDK_CHK_FAIL(i4_ret);

        i4_ret = a_wdk_text_set_text(*t_txt_param.ph_created_txt, MENU_TEXT(pt_this->cfg.btn_cancel.ui2_text_key));
        WDK_CHK_FAIL(i4_ret);

        /* Clear key map to make sure text widget will notify CURSOR key to its parent frame. */
        i4_ret = _digit_key_set_text_keymap(*(t_txt_param.ph_created_txt));
        WDK_CHK_FAIL(i4_ret);
    }
    else
    {
        pt_this->btn_cancel = NULL_HANDLE;
    }
    return i4_ret;
}

static INT32 _digit_create_digit_keys(DIGIT_PAD* pt_this)
{
    INT32                   i4_ret = WDKR_OK;
    UINT8                   ui1_idx_row;
    UINT8                   ui1_idx_col;
    WDK_TXT_WIDGET_PARAM_T  t_txt_param;

    for (ui1_idx_row = 0; ui1_idx_row < DIGIT_PAD_DIGIT_ROW_NUM; ui1_idx_row++)
    {
        for (ui1_idx_col = 0; ui1_idx_col < DIGIT_PAD_DIGIT_COL_NUM; ui1_idx_col++)
        {
            if (pt_this->cfg.b_dash_key_enable == FALSE
                    && (ui1_idx_row == DIGIT_PAD_DIGIT_ROW_NUM - 1 && ui1_idx_col == 0))
            {
                pt_this->digit_key_handles[ui1_idx_row][ui1_idx_col] = NULL_HANDLE;
                continue;
            }
            /* Create keypad normal key text */
            c_memset(&t_txt_param, 0, sizeof(WDK_TXT_WIDGET_PARAM_T));

            t_txt_param.h_parent      = pt_this->main_frame;
            t_txt_param.ui1_alpha     = DIGIT_PAD_KEY_TEXT_ALPHA;
            t_txt_param.b_visibility  = TRUE;
            t_txt_param.i4_x          = DIGIT_PAD_NORMAL_KEY_TEXT_X + ui1_idx_col * (DIGIT_PAD_NORMAL_KEY_TEXT_W + DIGIT_PAD_KEY_TEXT_INTERVAL_X);
            t_txt_param.i4_y          = DIGIT_PAD_NORMAL_KEY_TEXT_Y + ui1_idx_row * (DIGIT_PAD_NORMAL_KEY_TEXT_H + DIGIT_PAD_KEY_TEXT_INTERVAL_Y);
            t_txt_param.i4_w          = DIGIT_PAD_NORMAL_KEY_TEXT_W;
            t_txt_param.i4_h          = DIGIT_PAD_NORMAL_KEY_TEXT_H;
            t_txt_param.ui4_style     = WGL_STL_TEXT_MAX_32 | WGL_STL_TEXT_END_AS_NEWLINE | WGL_STL_TEXT_SMART_CUT;
            t_txt_param.ps_font_name  = DIGIT_PAD_FONT_NAME;
            t_txt_param.e_font_size   = DIGIT_PAD_KEY_TEXT_FONT_SIZE;
            t_txt_param.ui1_font_custom_size = DIGIT_PAD_KEY_TEXT_FONT_CUSTOM_SIZE;
            t_txt_param.e_font_style  = DIGIT_PAD_KEY_TEXT_FONT_STYLE;
            t_txt_param.ui1_align     = DIGIT_PAD_KEY_TEXT_ALIGNMENT;
            t_txt_param.b_img_bk      = TRUE;
            t_txt_param.pt_clr_txt    = & (NAV_COLOR(NAV_COLOR_ID_TEXT));
            t_txt_param.pt_hlt_clr_txt= & (NAV_COLOR(NAV_COLOR_ID_TEXT));
            t_txt_param.pt_dis_clr_txt= & (t_g_menu_color_bk2_txt_disable);

            if (ui1_idx_row == DIGIT_PAD_DIGIT_ROW_NUM - 1 && ui1_idx_col == DIGIT_PAD_DIGIT_COL_NUM - 1)
            {
                if (pt_this->cfg.b_del_key_grayout == TRUE)
                {
                    t_txt_param.t_img_bk.h_enable    = h_g_digit_pad_del_grayout_bkg;
                    t_txt_param.t_img_bk.h_highlight = h_g_digit_pad_del_grayout_bkg;
                    t_txt_param.t_img_bk.h_disable   = h_g_digit_pad_del_grayout_bkg;
                }
                else
                {
                    t_txt_param.t_img_bk.h_enable    = h_g_digit_pad_del_unfocus_bkg;
                    t_txt_param.t_img_bk.h_highlight = h_g_digit_pad_del_focus_bkg;
                    t_txt_param.t_img_bk.h_disable   = h_g_digit_pad_del_unfocus_bkg;
                }
            }
            else if (ui1_idx_row == DIGIT_PAD_DIGIT_ROW_NUM - 1 && ui1_idx_col == 0 && pt_this->cfg.b_dash_key_grayout== TRUE)
            {
                t_txt_param.t_img_bk.h_enable    = NULL_HANDLE;
                t_txt_param.t_img_bk.h_highlight = NULL_HANDLE;
                t_txt_param.t_img_bk.h_disable   = NULL_HANDLE;
            }
            else
            {
                t_txt_param.t_img_bk.h_enable    = h_g_digit_pad_digit_key_unfocus_bkg;
                t_txt_param.t_img_bk.h_highlight = h_g_digit_pad_digit_key_focus_bkg;
                t_txt_param.t_img_bk.h_disable   = h_g_digit_pad_digit_key_unfocus_bkg;
            }
            t_txt_param.pf_wdgt_proc = _digit_key_wdgt_proc_fct;
            t_txt_param.ph_created_txt= &(pt_this->digit_key_handles[ui1_idx_row][ui1_idx_col]);

            i4_ret = a_wdk_create_txt_widget (t_txt_param);
            WDK_CHK_FAIL(i4_ret);

            i4_ret = a_wdk_text_set_text(*t_txt_param.ph_created_txt, w2s_digit_pad_digit_text[ui1_idx_row][ui1_idx_col]);
            WDK_CHK_FAIL(i4_ret);

            /* Clear key map to make sure text widget will notify CURSOR key to its parent frame. */
            i4_ret = _digit_key_set_text_keymap(*(t_txt_param.ph_created_txt));
            WDK_CHK_FAIL(i4_ret);
        }
    }

    return i4_ret;
}

static INT32 _digit_pad_notify_digit_key_event(DIGIT_PAD* pt_this)
{
    INT32 i4_ret = WDKR_OK;
    UINT8 ui1_idx_row;
    UINT8 ui1_idx_col;
    if (pt_this->cfg.digit_key_event_nfy == NULL)
    {
        return i4_ret;
    }
    ui1_idx_row = pt_this->aui8_current_digit_focus[0];
    ui1_idx_col = pt_this->aui8_current_digit_focus[1];
    if (ui1_idx_row == DIGIT_PAD_DIGIT_ROW_NUM - 1 && ui1_idx_col == DIGIT_PAD_DIGIT_COL_NUM - 1)
    {
        pt_this->cfg.digit_key_event_nfy(DIGIT_PAD_DEL_KEY, NULL);
    }
    else
    {
        pt_this->cfg.digit_key_event_nfy(DIGIT_PAD_DIGIT_KEY, (VOID*)&digit_pad_digit_text[ui1_idx_row][ui1_idx_col]);
    }
    return i4_ret;
}

static INT32 _digit_button_wdgt_proc_fct(HANDLE_T h_widget,
                                         UINT32 ui4_msg,
                                         VOID* pv_param1,
                                         VOID* pv_param2)
{
    UINT32 ui4_keycode = (UINT32)pv_param1;
    INT32 i4_ret = WDKR_OK;
    HANDLE_T hmain_frame;
    DIGIT_PAD* pt_this;

    i4_ret = c_wgl_get_parent(h_widget, &hmain_frame);
    WDK_CHK_FAIL(i4_ret);
    i4_ret = _digit_pad_get_attach_data(hmain_frame, &pt_this);
    WDK_CHK_FAIL(i4_ret);
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            switch (ui4_keycode)
            {
                case BTN_CURSOR_UP:
                {
                    if (h_widget == pt_this->btn_cancel && pt_this->cfg.btn_ok.b_enable == TRUE)
                    {
                        c_wgl_set_focus(pt_this->btn_ok,
                                        WGL_ASYNC_AUTO_REPAINT);
                        WDK_CHK_FAIL(i4_ret);
                        TTS_PLAY(MENU_TEXT(pt_this->cfg.btn_ok.ui2_text_key));
                    }
                    else
                    {
                        pt_this->aui8_current_digit_focus[0] = DIGIT_PAD_DIGIT_ROW_NUM - 1;
                        pt_this->aui8_current_digit_focus[1] = DIGIT_PAD_DIGIT_COL_NUM - 2;
                        i4_ret = c_wgl_set_focus(pt_this->digit_key_handles[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]],
                                                 WGL_ASYNC_AUTO_REPAINT);
                        WDK_CHK_FAIL(i4_ret);
                        TTS_PLAY(w2s_digit_tts_text[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]]);
                    }

                    break;
                }
                case BTN_CURSOR_DOWN:
                {
                    if (h_widget == pt_this->btn_ok && pt_this->cfg.btn_cancel.b_enable == TRUE)
                    {
                        c_wgl_set_focus(pt_this->btn_cancel,
                                        WGL_ASYNC_AUTO_REPAINT);
                        WDK_CHK_FAIL(i4_ret);

                        TTS_PLAY(MENU_TEXT(pt_this->cfg.btn_cancel.ui2_text_key));
                    }
                    else
                    {
                        if (pt_this->cfg.digit_key_event_nfy != NULL)
                        {
                            pt_this->cfg.digit_key_event_nfy(DIGIT_PAD_FOCUS_TO_BELOW_WGL, NULL);
                        }
                    }
                    break;
                }
                case BTN_CURSOR_RIGHT:
                {
                    if (h_widget == pt_this->btn_info && pt_this->cfg.b_info_ok_key_enable == TRUE)
                    {
                        c_wgl_set_focus(pt_this->btn_go,
                                        WGL_ASYNC_AUTO_REPAINT);
                        WDK_CHK_FAIL(i4_ret);

                        TTS_PLAY(L"go");
                    }
                    break;
                }
                case BTN_CURSOR_LEFT:
                {
                    if (h_widget == pt_this->btn_go && pt_this->cfg.b_info_ok_key_enable == TRUE)
                    {
                        c_wgl_set_focus(pt_this->btn_info,
                                        WGL_ASYNC_AUTO_REPAINT);
                        WDK_CHK_FAIL(i4_ret);

                        TTS_PLAY(L"info");
                    }
                    break;
                }
                case BTN_SELECT:
                {
                    if (pt_this->cfg.digit_key_event_nfy != NULL)
                    {
                        if(h_widget == pt_this->btn_ok || h_widget == pt_this->btn_go)
                        {
                            pt_this->cfg.digit_key_event_nfy(DIGIT_PAD_BUTTON_OK, NULL);
                        }
                        else if(h_widget == pt_this->btn_cancel)
                        {
                            pt_this->cfg.digit_key_event_nfy(DIGIT_PAD_BUTTON_CANCEL, NULL);
                        }
                        else if(h_widget == pt_this->btn_info)
                        {
                            pt_this->cfg.digit_key_event_nfy(DIGIT_PAD_BUTTON_INFO, NULL);
                        }
                    }
                    break;
                }
                case BTN_RETURN:
                {
                    if (pt_this->cfg.digit_key_event_nfy != NULL)
                    {
                        pt_this->cfg.digit_key_event_nfy(DIGIT_PAD_NAV_BACK, NULL);
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }

    if (pt_this->cfg.pf_rc_event_default_handle != NULL)
    {
        pt_this->cfg.pf_rc_event_default_handle(ui4_msg, pv_param1, pv_param2);

    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);;
}

static INT32 _digit_key_wdgt_proc_fct(HANDLE_T h_widget,
                                      UINT32 ui4_msg,
                                      VOID* pv_param1,
                                      VOID* pv_param2)
{
    UINT32 ui4_keycode = (UINT32)pv_param1;
    INT32 i4_ret = WDKR_OK;
    HANDLE_T hmain_frame;    DIGIT_PAD* pt_this;

    UTF16_T w2s_text[32];

    i4_ret = c_wgl_get_parent(h_widget, &hmain_frame);
    WDK_CHK_FAIL(i4_ret);
    i4_ret = _digit_pad_get_attach_data(hmain_frame, &pt_this);
    WDK_CHK_FAIL(i4_ret);
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    i4_ret = _digit_pad_notify_digit_key_event(pt_this);
                    WDK_CHK_FAIL(i4_ret);
                    break;
                }
                case BTN_CURSOR_UP:
                {
                    if (pt_this->aui8_current_digit_focus[0] > 0)
                    {
                        pt_this->aui8_current_digit_focus[0]--;
                     
                    }
                    else if(pt_this->aui8_current_digit_focus[0] == 0 && pt_this->aui8_current_digit_focus[1] == 1)
                    {
                        pt_this->aui8_current_digit_focus[0] += (DIGIT_PAD_DIGIT_ROW_NUM-1);
                    }
                    else
                    {
                        if (pt_this->cfg.digit_key_event_nfy != NULL)
                        {
                            pt_this->cfg.digit_key_event_nfy(DIGIT_PAD_FOCUS_TO_ABOVE_WGL, NULL);
                        }
                    }

                    i4_ret = c_wgl_set_focus(pt_this->digit_key_handles[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]],
                                                 WGL_ASYNC_AUTO_REPAINT);
                    WDK_CHK_FAIL(i4_ret);
                    TTS_PLAY(w2s_digit_tts_text[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]]);

                    break;
                }
                case BTN_CURSOR_DOWN:
                {
                    if (pt_this->aui8_current_digit_focus[0] + 1 < DIGIT_PAD_DIGIT_ROW_NUM)
                    {
                        pt_this->aui8_current_digit_focus[0]++;
                        // if dash key is disable and will focus to dash key
                        if (pt_this->aui8_current_digit_focus[0] == DIGIT_PAD_DIGIT_ROW_NUM - 1
                                && pt_this->aui8_current_digit_focus[1] == 0
                                && (pt_this->cfg.b_dash_key_enable == FALSE || pt_this->cfg.b_dash_key_grayout == TRUE))
                        {
                            // do nothing
                            pt_this->aui8_current_digit_focus[0]--;

                        }
                        else if (pt_this->aui8_current_digit_focus[0] == DIGIT_PAD_DIGIT_ROW_NUM - 1
                                 && pt_this->aui8_current_digit_focus[1] == DIGIT_PAD_DIGIT_COL_NUM - 1
                                 && pt_this->cfg.b_del_key_grayout == TRUE)
                        {
                            // do nothing
                            pt_this->aui8_current_digit_focus[0]--;
                        }
                        else
                        {
                            i4_ret = c_wgl_set_focus(pt_this->digit_key_handles[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]],
                                                    WGL_ASYNC_AUTO_REPAINT);
                            WDK_CHK_FAIL(i4_ret);
                            TTS_PLAY(w2s_digit_tts_text[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]]);
                            break;
                        }
                    }
                    if (pt_this->cfg.btn_ok.b_enable == TRUE)
                    {
                        i4_ret = c_wgl_set_focus(pt_this->btn_ok,
                                                 WGL_ASYNC_AUTO_REPAINT);
                        WDK_CHK_FAIL(i4_ret);

                        TTS_PLAY(MENU_TEXT(pt_this->cfg.btn_ok.ui2_text_key));
                    }
                    else if (pt_this->cfg.btn_cancel.b_enable == TRUE)
                    {
                        i4_ret = c_wgl_set_focus(pt_this->btn_cancel,
                                                 WGL_ASYNC_AUTO_REPAINT);
                        WDK_CHK_FAIL(i4_ret);

                        TTS_PLAY(MENU_TEXT(pt_this->cfg.btn_cancel.ui2_text_key));
                    }
                    else if(pt_this->cfg.b_info_ok_key_enable == TRUE)
                    {
                        i4_ret = c_wgl_set_focus(pt_this->btn_go,
                                                 WGL_ASYNC_AUTO_REPAINT);
                        WDK_CHK_FAIL(i4_ret);

                        TTS_PLAY(L"go");
                    }
                    else
                    {
                        if (pt_this->cfg.digit_key_event_nfy != NULL)
                        {
                            pt_this->cfg.digit_key_event_nfy(DIGIT_PAD_FOCUS_TO_BELOW_WGL, NULL);
                        }
                    }
                    break;
                }
                case BTN_CURSOR_LEFT:
                {
                    pt_this->aui8_current_digit_focus[1] = (pt_this->aui8_current_digit_focus[1] + DIGIT_PAD_DIGIT_COL_NUM - 1)
                                                        % DIGIT_PAD_DIGIT_COL_NUM;
                    // if dash key is disable and will focus to dash key
                    if (pt_this->aui8_current_digit_focus[0] == DIGIT_PAD_DIGIT_ROW_NUM - 1
                            && pt_this->aui8_current_digit_focus[1] == 0
                            && (pt_this->cfg.b_dash_key_enable == FALSE || pt_this->cfg.b_dash_key_grayout == TRUE))
                    {
                        pt_this->aui8_current_digit_focus[1] = (pt_this->aui8_current_digit_focus[1] + DIGIT_PAD_DIGIT_COL_NUM - 1)
                                    % DIGIT_PAD_DIGIT_COL_NUM;
                    }
                    // if del key is grayout
                    if (pt_this->aui8_current_digit_focus[0] == DIGIT_PAD_DIGIT_ROW_NUM - 1
                        && pt_this->aui8_current_digit_focus[1] == DIGIT_PAD_DIGIT_COL_NUM - 1
                        && pt_this->cfg.b_del_key_grayout == TRUE)
                    {
                        pt_this->aui8_current_digit_focus[1] = (pt_this->aui8_current_digit_focus[1] + DIGIT_PAD_DIGIT_COL_NUM - 1)
                                    % DIGIT_PAD_DIGIT_COL_NUM;

                    }
                    i4_ret = c_wgl_set_focus(pt_this->digit_key_handles[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]],
                                             WGL_ASYNC_AUTO_REPAINT);
                    WDK_CHK_FAIL(i4_ret);
                    TTS_PLAY(w2s_digit_tts_text[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]]);
                    break;
                }
                case BTN_CURSOR_RIGHT:
                {
                    pt_this->aui8_current_digit_focus[1] = (pt_this->aui8_current_digit_focus[1] + 1)
                                                        % DIGIT_PAD_DIGIT_COL_NUM;
                    // if del key is grayout
                    if (pt_this->aui8_current_digit_focus[0] == DIGIT_PAD_DIGIT_ROW_NUM - 1
                        && pt_this->aui8_current_digit_focus[1] == DIGIT_PAD_DIGIT_COL_NUM - 1
                        && pt_this->cfg.b_del_key_grayout == TRUE)
                    {
                        pt_this->aui8_current_digit_focus[1] = (pt_this->aui8_current_digit_focus[1] + 1)
                                    % DIGIT_PAD_DIGIT_COL_NUM;

                    }
                    if (pt_this->aui8_current_digit_focus[0] == DIGIT_PAD_DIGIT_ROW_NUM - 1
                            && pt_this->aui8_current_digit_focus[1] == 0
                            && (pt_this->cfg.b_dash_key_enable == FALSE || pt_this->cfg.b_dash_key_grayout == TRUE))
                    {
                        pt_this->aui8_current_digit_focus[1] = (pt_this->aui8_current_digit_focus[1] + 1)
                                    % DIGIT_PAD_DIGIT_COL_NUM;
                    }
                    i4_ret = c_wgl_set_focus(pt_this->digit_key_handles[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]],
                                             WGL_ASYNC_AUTO_REPAINT);
                    WDK_CHK_FAIL(i4_ret);

                    TTS_PLAY(w2s_digit_tts_text[pt_this->aui8_current_digit_focus[0]][pt_this->aui8_current_digit_focus[1]]);
                    break;
                }
                case BTN_RETURN:
                {
                    if (pt_this->cfg.digit_key_event_nfy != NULL)
                    {
                        pt_this->cfg.digit_key_event_nfy(DIGIT_PAD_NAV_BACK, NULL);
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
    if (pt_this->cfg.pf_rc_event_default_handle != NULL)
    {
        pt_this->cfg.pf_rc_event_default_handle(ui4_msg, pv_param1, pv_param2);

    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _digit_key_set_text_keymap(HANDLE_T h_txt_handle)
{
    INT32 i4_ret = WDKR_OK;
    WGL_TEXT_KEY_MAP_T t_key_map;

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

    return i4_ret;
}

static INT32 _digit_pad_set_attach_data(HANDLE_T    h_digit_handle,
                                        DIGIT_PAD*  pdigit_pad)
{
    INT32 i4_ret = WDKR_OK;

    i4_ret = c_wgl_do_cmd(h_digit_handle,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pdigit_pad),
                          NULL);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

static INT32 _digit_pad_get_attach_data(HANDLE_T h_digit_handle,
                                        DIGIT_PAD** ppdigit_pad)
{
   INT32 i4_ret = WDKR_OK;

    /* set a initial value */
    *ppdigit_pad = NULL;

    i4_ret = c_wgl_do_cmd(h_digit_handle,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppdigit_pad),
                          NULL);
    WDK_CHK_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _digit_change_language(DIGIT_PAD* pt_this)
{
    INT32 i4_ret = WDKR_OK;
    if (pt_this->cfg.btn_ok.b_enable == TRUE)
    {
        i4_ret = a_wdk_text_set_text(pt_this->btn_ok, MENU_TEXT(pt_this->cfg.btn_ok.ui2_text_key));
        WDK_CHK_FAIL(i4_ret);
    }
    if (pt_this->cfg.btn_cancel.b_enable == TRUE)
    {
        i4_ret = a_wdk_text_set_text(pt_this->btn_cancel, MENU_TEXT(pt_this->cfg.btn_cancel.ui2_text_key));
        WDK_CHK_FAIL(i4_ret);
    }
    return i4_ret;
}
