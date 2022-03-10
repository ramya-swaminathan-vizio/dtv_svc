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
 * $RCSfile: divx_cert_dlg.c,v $
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

#include "c_handle.h"
#include "c_wgl_image.h"
#include "c_wgl_sets.h"
#include "c_wgl.h"

#include "mmp_divx_dlg.h"
#include "res/mmp/img/mmp_img.h"
#include MMP_MLM_HEADER_FILE

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define DLG_FRAME_ALPHA          (255)

#define DLG_DFLT_HLT_BTN_IDX     (0)
#define DLG_DFLT_MAX_BTN_NUM     (3)

#define DLG_TITLE_TXT_MAX        (32)
#define DLG_TEXT_TXT_MAX         (512)
#define DLG_BTN_TXT_MAX          (10)

typedef struct _DLG_BTN_CONTROL_T {

    HANDLE_T                     h_dlg_btn;                         /* the handle of button*/
    dlg_action_fct               pf_dlg_btn_act_cb_fct;             /* Button action callback */
    VOID*                        pv_tag;

}DLG_BTN_CONTROL_T;

typedef struct _DLG_CONTROL_T {

    /* Widgets */
    HANDLE_T                     h_dlg_frm;                         /* the main frame of the DLG */
    HANDLE_T                     h_dlg_title;                       /* the title */
    HANDLE_T                     h_dlg_text;                        /* the text */

    /* Template Images */
    WGL_HIMG_TPL_T               h_dlg_frame_bk;                     /* Dialog BK */
    WGL_HIMG_TPL_T               h_dlg_title_bk;                     /* Dialog BK */
    WGL_HIMG_TPL_T               h_dlg_btn_selected_bk;              /* Dialog selected button BK */
    WGL_HIMG_TPL_T               h_dlg_btn_unselected_bk;            /* Dialog unselected button BK */

    /* Init information */
    HANDLE_T                     h_parent;                           /* Your root widget */
    DLG_ALIGN_T                  e_align;
    UINT32                       ui4_style_mask;
    dlg_data_change_nfy_fct      pf_fct;
    VOID*                        pv_tag;

    DLG_BTN_CONTROL_T            at_button[DLG_DFLT_MAX_BTN_NUM];    /* the buttons */

    UINT8                        ui1_hlt_btn_idx;                    /* the index of hightlight button */

} DLG_CONTROL_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    color
-----------------------------------------------------------------------------*/
#ifdef APP_COLOR_MODE_PALLET
	const GL_COLOR_T t_g_dlg_title_bk_color =       /* Trans */
	{
	      0, {  0}, {  0}, {  1}
	};
	const GL_COLOR_T t_g_dlg_title_txt_color =      /* White */
	{
	    255, {  0}, {  0}, {241}
	};

	const GL_COLOR_T t_g_dlg_text_txt_color =       /* White */
	{
	    255, {  0}, {  0}, {241}
	};

	const GL_COLOR_T t_g_dlg_text_txt_hl_color =     /* Black */
	{
	    255, {  0}, {  0}, { 16}
	};

	const GL_COLOR_T t_g_dlg_btn_txt_color =        /* White */
	{
	    255, {  0}, {  0}, {241}
	};

	const GL_COLOR_T t_g_dlg_trans_color =          /* Trans */
	{
	      0, {  0}, {  0}, {  1}
	};
#else
	const GL_COLOR_T t_g_dlg_title_bk_color =       /* Trans */
	{
	      0, {148}, {  0}, {255}
	};
	const GL_COLOR_T t_g_dlg_title_txt_color =      /* White */
	{
	    255, {255}, {255}, {255}
	};

	const GL_COLOR_T t_g_dlg_text_txt_color =       /* White */
	{
	    255, {255}, {255}, {255}
	};

	const GL_COLOR_T t_g_dlg_text_txt_hl_color =     /* Black */
	{
	    255, {  0}, {  0}, {  0}
	};

	const GL_COLOR_T t_g_dlg_btn_txt_color =        /* White */
	{
	    255, {255}, {255}, {255}
	};

	const GL_COLOR_T t_g_dlg_trans_color =          /* Trans */
	{
	      0, {148}, {  0}, {255}
	};
#endif /*APP_COLOR_MODE_PALLET*/

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
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
static BOOL _dlg_is_fixed_image_size(
                    DLG_CONTROL_T*      pt_dlg_dialog
                    )
{
    if (pt_dlg_dialog->ui4_style_mask & DLG_STYLE_MASK_FIXED_IMAGE_SIZE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
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
static INT32 _dlg_set_attach_data(
                    HANDLE_T            h_dlg_handle,
                    DLG_CONTROL_T*      pt_dlg_dialog
                    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(h_dlg_handle,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_dlg_dialog),
                          NULL);
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
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
static INT32 _dlg_get_attach_data(
                    HANDLE_T            h_dlg_handle,
                    DLG_CONTROL_T**     ppt_dlg_dialog
                    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(h_dlg_handle,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_dlg_dialog),
                          NULL);
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
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
static UINT8 _dlg_validate_style_mask(
                    UINT32              ui4_style_mask
                    )
{
    if (ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON3)
    {
        if (ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON1 &&
            ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON2)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    if (ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON2)
    {
        if (ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON1)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    return TRUE;
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
static UINT8 _dlg_get_num_of_btn(
                    UINT32              ui4_style_mask
                    )
{
    UINT8 ui1_num_of_btn;

    if (ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON3)
    {
        ui1_num_of_btn = 3;
    }
    else if (ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON2)
    {
        ui1_num_of_btn = 2;
    }
    else if (ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON1)
    {
        ui1_num_of_btn = 1;
    }
    else
    {
        ui1_num_of_btn = 0;
    }

    return ui1_num_of_btn;
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
INT32 _dlg_select_hlt_btn(
                    DLG_CONTROL_T*      pt_dlg_dialog
                    )
{
    UINT8     ui1_hlt_idx;

    ui1_hlt_idx = pt_dlg_dialog->ui1_hlt_btn_idx;

    if(DLG_DFLT_MAX_BTN_NUM <= ui1_hlt_idx)
    {
        return DLGR_FAIL;
    }

    if(pt_dlg_dialog->at_button[ui1_hlt_idx].pf_dlg_btn_act_cb_fct != NULL)
    {
		pt_dlg_dialog->at_button[ui1_hlt_idx].pf_dlg_btn_act_cb_fct(pt_dlg_dialog->at_button[ui1_hlt_idx].pv_tag);
    }

    return DLGR_OK;
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

static BOOL _dlg_key_handler(
                    DLG_CONTROL_T*      pt_dlg_dialog,
                    UINT32              ui4_key
                    )
{
    switch (ui4_key)
    {
        /* When there is no mask related to button, send all key message out. */
        case BTN_CURSOR_RIGHT:
            if (pt_dlg_dialog->ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON1 )
            {
                if (pt_dlg_dialog->ui1_hlt_btn_idx == _dlg_get_num_of_btn(pt_dlg_dialog->ui4_style_mask) - (UINT8)1)
                {
                    pt_dlg_dialog->ui1_hlt_btn_idx = (UINT8)0;
                }
                else
                {
                    pt_dlg_dialog->ui1_hlt_btn_idx++;
                }

                a_dlg_set_highlight_button(pt_dlg_dialog->h_dlg_frm,
                                           pt_dlg_dialog->ui1_hlt_btn_idx);
                c_wgl_repaint(pt_dlg_dialog->h_dlg_frm, NULL, TRUE);

                if (pt_dlg_dialog->pf_fct != NULL)
                {
                    pt_dlg_dialog->pf_fct(pt_dlg_dialog->pv_tag,
                                          DLG_MSG_BUTTON_HIGHLIGHT,
                                          (VOID*)(UINT32)pt_dlg_dialog->ui1_hlt_btn_idx,
                                          (VOID*)NULL);
                }
                break;
            }

        case BTN_CURSOR_LEFT:
            if (pt_dlg_dialog->ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON1 )
            {
                if (pt_dlg_dialog->ui1_hlt_btn_idx == (UINT8)0)
                {
                    pt_dlg_dialog->ui1_hlt_btn_idx = _dlg_get_num_of_btn(pt_dlg_dialog->ui4_style_mask) - (UINT8)1;
                }
                else
                {
                    pt_dlg_dialog->ui1_hlt_btn_idx--;
                }

                a_dlg_set_highlight_button(pt_dlg_dialog->h_dlg_frm,
                                           pt_dlg_dialog->ui1_hlt_btn_idx);
                c_wgl_repaint(pt_dlg_dialog->h_dlg_frm, NULL, TRUE);

                if (pt_dlg_dialog->pf_fct!=NULL)
                {
                    pt_dlg_dialog->pf_fct(pt_dlg_dialog->pv_tag,
                                          DLG_MSG_BUTTON_HIGHLIGHT,
                                          (VOID*)(UINT32)pt_dlg_dialog->ui1_hlt_btn_idx,
                                          (VOID*)NULL);
                }
                break;
            }

        case BTN_SELECT:
            if (pt_dlg_dialog->ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON1 )
            {
                _dlg_select_hlt_btn(pt_dlg_dialog);
                break;
            }

        default:
            /* For other key event, send "DLG_MSG_KEY_INPUT" */
            /* to indicator other keys are pressed.          */
            if (pt_dlg_dialog->pf_fct!=NULL)
            {
                pt_dlg_dialog->pf_fct(pt_dlg_dialog->pv_tag,
                              DLG_MSG_KEY_INPUT ,
                              (VOID*)ui4_key,
                              (VOID*)NULL);
            }
            break;
    }

    return TRUE;
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
static INT32 _dlg_frame_nfy_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2
                    )
{
    if (ui4_msg == WGL_MSG_KEY_DOWN || ui4_msg == WGL_MSG_KEY_UP)
    {
        DLG_CONTROL_T*      pt_dlg_dialog;
        INT32               i4_ret;

        /* Get epb structure */
        i4_ret = _dlg_get_attach_data(h_widget, &pt_dlg_dialog);
        if(i4_ret != DLGR_OK)
        {
           return i4_ret;
        }

        /* Special case: */
        if(pt_dlg_dialog->ui4_style_mask & DLG_STYLE_MASK_MANUAL_KEY_PROCESSING)
        {
            if (pt_dlg_dialog->pf_fct != NULL)
            {
                pt_dlg_dialog->pf_fct(pt_dlg_dialog->pv_tag, ui4_msg, pv_param1, pv_param2);
            }
            return WGLR_OK;
        }
    }

    switch(ui4_msg)
    {
	    case WGL_MSG_KEY_DOWN:
        {
            DLG_CONTROL_T*      pt_dlg_dialog;
            INT32               i4_ret;

            /* Get dialog structure */
            i4_ret = _dlg_get_attach_data(h_widget, &pt_dlg_dialog);
            if(i4_ret != DLGR_OK)
            {
               return i4_ret;
            }

            _dlg_key_handler(pt_dlg_dialog, (UINT32)pv_param1);

            return WGLR_OK;
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
static INT32 _dlg_create_frm(
                    DLG_CONTROL_T*             pt_dlg_dialog,
                    HANDLE_T                   h_parent,
                    DLG_STYLE_T                e_style
                    )

{
    INT32             i4_ret;
    GL_RECT_T         t_rect;
    UINT32            ui4_style;
    WGL_IMG_INFO_T    t_img_info;

    ui4_style = 0;

    if(e_style == DLG_STYLE_DIALOG)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         DLG_FRAME_LEFT,
                         DLG_FRAME_TOP,
                         DLG_FRAME_WIDTH,
                         DLG_FRAME_HEIGHT);
    }
    else
    {
        return DLGR_INV_ARG;
    }

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _dlg_frame_nfy_fct,
                                 DLG_FRAME_ALPHA,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_dlg_dialog->h_dlg_frm);
    DLG_WC_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_dlg_dialog->h_dlg_frame_bk;
    t_img_info.u_img_data.t_standard.t_highlight = pt_dlg_dialog->h_dlg_frame_bk;
    t_img_info.u_img_data.t_standard.t_disable   = pt_dlg_dialog->h_dlg_frame_bk;

    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    if (i4_ret != WGLR_OK)
    {
        return DLGR_WIDGET_CREATE_FAIL;
    }

    return DLGR_OK;
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
static INT32 _dlg_create_title(
                    DLG_CONTROL_T*      pt_dlg_dialog
                    )
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

    ui4_style = WGL_STL_GL_NO_IMG_UI |
                WGL_STL_TEXT_MAX_32;

    /* Default alignment */

    SET_RECT_BY_SIZE(&t_rect,
                     DLG_TITLE_TXT_LEFT,
                     DLG_TITLE_TXT_TOP,
                     DLG_TITLE_TXT_WIDTH,
                     DLG_TITLE_TXT_HEIGHT);

    i4_ret = c_wgl_create_widget(pt_dlg_dialog->h_dlg_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_dlg_dialog->h_dlg_title);
    DLG_WC_CHK_FAIL(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));

    t_inset.i4_left     = DLG_TITLE_TXT_INSET_L;
    t_inset.i4_right    = DLG_TITLE_TXT_INSET_R;
    t_inset.i4_top      = DLG_TITLE_TXT_INSET_T;
    t_inset.i4_bottom   = DLG_TITLE_TXT_INSET_B;

    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_title,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    DLG_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_title,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    DLG_CHK_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_dlg_title_txt_color;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_dlg_title_txt_color;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_dlg_title_txt_color;
    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_title,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    DLG_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_dlg_title_bk_color;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_dlg_title_bk_color;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_dlg_title_bk_color;
    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_title,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    DLG_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_title,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(DLG_TITLE_TXT_ALIGNMENT),
                          NULL);
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
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

static INT32 _dlg_create_text(
                    DLG_CONTROL_T*      pt_dlg_dialog
                    )
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

    ui4_style = WGL_STL_GL_NO_IMG_UI   |
                WGL_STL_TEXT_MULTILINE |
                WGL_STL_TEXT_MAX_512   |
                WGL_STL_TEXT_MAX_DIS_5_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                     DLG_TEXT_TXT_LEFT,
                     DLG_TEXT_TXT_TOP,
                     DLG_TEXT_TXT_WIDTH,
                     DLG_TEXT_TXT_HEIGHT);

    i4_ret = c_wgl_create_widget(pt_dlg_dialog->h_dlg_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_dlg_dialog->h_dlg_text);
    DLG_WC_CHK_FAIL(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));

    t_inset.i4_left     = DLG_TEXT_TXT_INSET_L;
    t_inset.i4_right    = DLG_TEXT_TXT_INSET_R;
    t_inset.i4_top      = DLG_TEXT_TXT_INSET_T;
    t_inset.i4_bottom   = DLG_TEXT_TXT_INSET_B;

    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_text,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    DLG_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_text,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    DLG_CHK_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_dlg_text_txt_color;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_dlg_text_txt_color;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_dlg_text_txt_color;
    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    DLG_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_text,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(DLG_TEXT_TXT_ALIGNMENT),
                          NULL);
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
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
static INT32 _dlg_create_btn(
                     DLG_CONTROL_T*     pt_dlg_dialog
                     )
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT8                       ui1_idx;
    UINT8                       ui4_val;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_IMG_INFO_T              t_img_info;
    WGL_FONT_INFO_T             t_fnt_info;
    /*
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    */

    ui4_val = (DLG_FRAME_WIDTH - DLG_DFLT_MAX_BTN_NUM * DLG_BTN_TXT_WIDTH) / (DLG_DFLT_MAX_BTN_NUM + 1);

    for (ui1_idx = 0; ui1_idx < DLG_DFLT_MAX_BTN_NUM; ui1_idx++)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         ui4_val + (DLG_BTN_TXT_WIDTH * ui1_idx),
                         DLG_BTN_TXT_TOP,
                         DLG_BTN_TXT_WIDTH,
                         DLG_BTN_TXT_HEIGHT);

        i4_ret = c_wgl_create_widget(pt_dlg_dialog->h_dlg_frm,
                                     HT_WGL_WIDGET_BUTTON,
                                     WGL_CONTENT_BUTTON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)WGL_STL_BTN_CHECKBOX,
                                     NULL,
                                     &(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn));
        DLG_WC_CHK_FAIL(i4_ret);

#if 0
        /* set theme */
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_dlg_trans_color;
        t_clr_info.u_color_data.t_standard.t_disable   = t_g_dlg_trans_color;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_dlg_trans_color;

        i4_ret = c_wgl_do_cmd (pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                               WGL_CMD_GL_SET_COLOR,
                               WGL_PACK (WGL_CLR_BK),
                               WGL_PACK (& t_clr_info));
        DLG_WC_CHK_FAIL(i4_ret);

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable       = NULL_HANDLE;
        t_img_info.u_img_data.t_standard.t_disable      = NULL_HANDLE;
        t_img_info.u_img_data.t_standard.t_highlight    = NULL_HANDLE;

        i4_ret = c_wgl_do_cmd (pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK (WGL_IMG_BK),
                               WGL_PACK (& t_img_info));
        DLG_WC_CHK_FAIL(i4_ret);

        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_dlg_trans_color;
        t_clr_info.u_color_data.t_standard.t_disable   = t_g_dlg_trans_color;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_dlg_trans_color;

        i4_ret = c_wgl_do_cmd (pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                               WGL_CMD_GL_SET_COLOR,
                               WGL_PACK (WGL_CLR_LB_VP_BK),
                               WGL_PACK (& t_img_info));
        DLG_WC_CHK_FAIL(i4_ret);

        t_color_elem.t_normal            = t_g_dlg_trans_color;
        t_color_elem.t_disable           = t_g_dlg_trans_color;
        t_color_elem.t_highlight         = t_g_dlg_trans_color;
        t_color_elem.t_highlight_unfocus = t_g_dlg_trans_color;
        t_color_elem.t_pushed            = t_g_dlg_trans_color;
        t_color_elem.t_selected          = t_g_dlg_trans_color;
        t_color_elem.t_selected_disable  = t_g_dlg_trans_color;

        i4_ret = c_wgl_do_cmd (pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                               WGL_CMD_LB_SET_ELEM_COLOR,
                               WGL_PACK (WGL_CLR_BK),
                               WGL_PACK (& t_color_elem));
        DLG_WC_CHK_FAIL(i4_ret);

        t_img_elem.h_normal             = NULL;
        t_img_elem.h_disable            = NULL;
        t_img_elem.h_highlight          = pt_dlg_dialog->h_dlg_btn_selected_bk;
        t_img_elem.h_highlight_unfocus  = pt_dlg_dialog->h_dlg_btn_selected_bk;
        t_img_elem.h_pushed             = pt_dlg_dialog->h_dlg_btn_selected_bk;
        t_img_elem.h_selected           = NULL;
        t_img_elem.h_selected_disable   = NULL;

        i4_ret = c_wgl_do_cmd (pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                               WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                               WGL_PACK(& t_img_elem),
                               NULL);
        DLG_WC_CHK_FAIL(i4_ret);

        t_color_elem.t_normal            = t_g_dlg_trans_color;
        t_color_elem.t_disable           = t_g_dlg_trans_color;
        t_color_elem.t_highlight         = t_g_dlg_trans_color;
        t_color_elem.t_highlight_unfocus = t_g_dlg_trans_color;
        t_color_elem.t_pushed            = t_g_dlg_trans_color;
        t_color_elem.t_selected          = t_g_dlg_trans_color;
        t_color_elem.t_selected_disable  = t_g_dlg_trans_color;

        i4_ret = c_wgl_do_cmd (pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2 (0, WGL_CLR_BK),
                                  WGL_PACK (& t_color_elem));
        DLG_WC_CHK_FAIL(i4_ret);

        t_color_elem.t_normal            = t_g_dlg_text_txt_color;
        t_color_elem.t_disable           = t_g_dlg_text_txt_color;
        t_color_elem.t_highlight         = t_g_dlg_text_txt_hl_color;
        t_color_elem.t_highlight_unfocus = t_g_dlg_text_txt_hl_color;
        t_color_elem.t_pushed            = t_g_dlg_text_txt_hl_color;
        t_color_elem.t_selected          = t_g_dlg_text_txt_color;
        t_color_elem.t_selected_disable  = t_g_dlg_text_txt_color;

        i4_ret = c_wgl_do_cmd (pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                               WGL_CMD_LB_SET_COL_COLOR,
                               WGL_PACK_2 (0, WGL_CLR_TEXT),
                               WGL_PACK (& t_color_elem));
        DLG_WC_CHK_FAIL(i4_ret);
#endif

#if 1
        /* Set Color */
        t_clr_info.e_type = WGL_COLOR_SET_EXTEND;

        t_clr_info.u_color_data.t_extend.t_enable             = t_g_dlg_btn_txt_color;
        t_clr_info.u_color_data.t_extend.t_disable            = t_g_dlg_btn_txt_color;
        t_clr_info.u_color_data.t_extend.t_highlight          = t_g_dlg_btn_txt_color;
        t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_dlg_btn_txt_color;
        t_clr_info.u_color_data.t_extend.t_push               = t_g_dlg_btn_txt_color;
        t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_dlg_btn_txt_color;

        i4_ret = c_wgl_do_cmd(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_TEXT),
                              WGL_PACK(&t_clr_info ));
        DLG_CHK_FAIL(i4_ret);

        /* Set Image */
        t_img_info.e_type = WGL_IMG_SET_EXTEND;
        t_img_info.u_img_data.t_extend.t_disable            = NULL_HANDLE;
        t_img_info.u_img_data.t_extend.t_enable             = pt_dlg_dialog->h_dlg_btn_unselected_bk;
        t_img_info.u_img_data.t_extend.t_highlight          = NULL_HANDLE;
        t_img_info.u_img_data.t_extend.t_highlight_inactive = NULL_HANDLE;
        t_img_info.u_img_data.t_extend.t_push               = NULL_HANDLE;
        t_img_info.u_img_data.t_extend.t_push_unhighlight   = pt_dlg_dialog->h_dlg_btn_selected_bk;

        i4_ret = c_wgl_do_cmd(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        DLG_CHK_FAIL(i4_ret);

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
        t_fnt_info.e_font_size  = DLG_BTN_DFLT_FONT_SIZE;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = c_wgl_do_cmd(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK(&t_fnt_info),
                              NULL);
        DLG_CHK_FAIL(i4_ret);
#endif

        /* Set Alignment */
        i4_ret = c_wgl_do_cmd(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                              WGL_CMD_BTN_SET_ALIGN,
                              WGL_PACK(WGL_AS_CENTER_CENTER),
                              NULL);
        DLG_CHK_FAIL(i4_ret);
    }

    return DLGR_OK;
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
static INT32 _dlg_destroy(
                    HANDLE_T            h_dlg_handle
                    )

{
	INT32             i4_ret;
	UINT8 ui1_idx;
	DLG_CONTROL_T*    pt_dlg_dialog;

	/* Get dialog structure */
	i4_ret = _dlg_get_attach_data(h_dlg_handle,
	                           &pt_dlg_dialog);
	if(i4_ret != DLGR_OK)
	{
	  return i4_ret;
	}

	/* Release childs*/
	if(pt_dlg_dialog->h_dlg_title != NULL_HANDLE)
	{
	    c_wgl_destroy_widget(pt_dlg_dialog->h_dlg_title);
	}

	if(pt_dlg_dialog->h_dlg_text != NULL_HANDLE)
	{
	    c_wgl_destroy_widget(pt_dlg_dialog->h_dlg_text);
	}

	for (ui1_idx = 0; ui1_idx < _dlg_get_num_of_btn(pt_dlg_dialog->ui4_style_mask); ui1_idx++)
	{
	    if(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn != NULL_HANDLE)
	    {
	        c_wgl_destroy_widget(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn);
	    }
	}

	/* Release parent */
	if(pt_dlg_dialog->h_dlg_frm != NULL_HANDLE)
	{
	    c_wgl_destroy_widget(pt_dlg_dialog->h_dlg_frm);
	}

    /* Release the structure */
    c_mem_free(pt_dlg_dialog);

    return DLGR_OK;
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
static INT32 _dlg_get_text_line(
                    DLG_CONTROL_T*     pt_dlg_dialog,
                    UINT16*            pui1_total_lines
                    )
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;

    /* In order to calculate the really line, we should set the maximum      */
    /* height to the text area                                               */
    SET_RECT_BY_SIZE(&t_rect,
                 DLG_TEXT_TXT_LEFT,
                 DLG_TEXT_TXT_TOP,
                 DLG_TEXT_TXT_WIDTH,
                 DLG_TEXT_TXT_HEIGHT);

    i4_ret = c_wgl_move(pt_dlg_dialog->h_dlg_text, &t_rect, FALSE);
    DLG_CHK_FAIL(i4_ret);

    /* get total lines */
    i4_ret = c_wgl_do_cmd(
                    pt_dlg_dialog->h_dlg_text,
                    WGL_CMD_TEXT_GET_TOTAL_LINES,
                    WGL_PACK(pui1_total_lines),
                    NULL
                    );
    DLG_CHK_FAIL(i4_ret);

    /* If the total number of lines is bigger than the maximum number,       */
    /* Set it as the maximum number.                                         */
    if (_dlg_is_fixed_image_size(pt_dlg_dialog))
    {
        *pui1_total_lines = DLG_FIXED_IMAGE_DFLT_MAX_LINE_NUM;
    }
    else
    {
        if (*pui1_total_lines > DLG_DFLT_MAX_LINE_NUM)
        {
            *pui1_total_lines = DLG_DFLT_MAX_LINE_NUM;
        }
    }

    return DLGR_OK;
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
static INT32 _dlg_allocate_layout(
                     DLG_CONTROL_T*     pt_dlg_dialog
                     )
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UINT8               ui1_mum_of_btn;
    UINT32              ui4_val;
    UINT32              ui4_btn_left;
    UINT8               ui1_idx;
    UINT16              ui1_total_lines = 1;
    UINT16              ui2_frm_height = 0;

    /* Add the height of title */
    if (_dlg_is_fixed_image_size(pt_dlg_dialog))
    {
        ui2_frm_height = DLG_TITLE_TXT_HEIGHT + DLG_CNT_SPACE_HEIGHT_T;
    }
    else
    {
        if (pt_dlg_dialog->ui4_style_mask & DLG_STYLE_MASK_WITH_TITLE)
        {
            ui2_frm_height = DLG_TITLE_TXT_HEIGHT + DLG_CNT_SPACE_HEIGHT_T;
        }
        else
        {
            ui2_frm_height = DLG_CNT_SPACE_HEIGHT_T;
        }
    }

    /* Set the loaction of text*/
    i4_ret = _dlg_get_text_line(pt_dlg_dialog, &ui1_total_lines);
    if (i4_ret != DLGR_OK || ui1_total_lines <= 0)
    {
        /* error correct */
        ui1_total_lines = 1;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     (INT32)DLG_TEXT_TXT_LEFT,
                     (INT32)ui2_frm_height,
                     (INT32)DLG_TEXT_TXT_WIDTH,
                     (INT32)(ui1_total_lines * DLG_TEXT_TXT_PER_LINE));

    i4_ret = c_wgl_move(pt_dlg_dialog->h_dlg_text, &t_rect, FALSE);
    DLG_CHK_FAIL(i4_ret);

    /* Add the hight of text */
    if (_dlg_is_fixed_image_size(pt_dlg_dialog))
    {
        ui2_frm_height = DLG_BTN_TXT_TOP;
    }
    else
    {
        ui2_frm_height = ui2_frm_height +
                         ui1_total_lines * (UINT16)DLG_TEXT_TXT_PER_LINE + (UINT16)DLG_CNT_SPACE_HEIGHT_T;
    }

    if (pt_dlg_dialog->ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON1)
    {
        /* Set the location of buttons*/
        ui1_mum_of_btn = _dlg_get_num_of_btn(pt_dlg_dialog->ui4_style_mask);
        ui4_val = ((UINT32)DLG_FRAME_WIDTH - ui1_mum_of_btn * (UINT32)DLG_BTN_TXT_WIDTH) / (ui1_mum_of_btn + (UINT32)1);
        ui4_btn_left = DLG_BTN_TXT_LEFT + ui4_val;
        for (ui1_idx = 0; ui1_idx < ui1_mum_of_btn; ui1_idx++)
        {
            /* Set the loaction of button*/
            SET_RECT_BY_SIZE(&t_rect,
                             (INT32)ui4_btn_left,
                             (INT32)ui2_frm_height,
                             (INT32)DLG_BTN_TXT_WIDTH,
                             (INT32)DLG_BTN_TXT_HEIGHT);
            ui4_btn_left = (ui4_btn_left + DLG_BTN_TXT_WIDTH) + ui4_val;
            c_wgl_move(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn, &t_rect, FALSE);
        }

        /* Add the hight of button */
        ui2_frm_height = ui2_frm_height + (UINT16)DLG_BTN_TXT_HEIGHT + (UINT16)DLG_CNT_SPACE_HEIGHT_T + (UINT16)DLG_CNT_SPACE_HEIGHT_B;
    }
    else
    {
        /* no button layout for fixed bg size */
        if (_dlg_is_fixed_image_size(pt_dlg_dialog))
        {
            ui2_frm_height = ui2_frm_height + (UINT16)DLG_BTN_TXT_HEIGHT + (UINT16)DLG_CNT_SPACE_HEIGHT_T + (UINT16)DLG_CNT_SPACE_HEIGHT_B;
        }
    }

    /* Set the location of dialog frame*/
    if (pt_dlg_dialog->e_align == DLG_ALIGN_CENTER)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         DLG_FRAME_LEFT,
                         ((DLG_SCREEN_HEIGHT-ui2_frm_height)/2),
                         DLG_FRAME_WIDTH,
                         ui2_frm_height);
    }
    else if (pt_dlg_dialog->e_align == DLG_ALIGN_BOTTOM)
    {
        SET_RECT_BY_SIZE(&t_rect,
                     DLG_FRAME_LEFT,
                     (DLG_SCREEN_HEIGHT - DLG_FRAME_BOTTOM_DIST - ui2_frm_height),
                     DLG_FRAME_WIDTH,
                     ui2_frm_height);
    }

    i4_ret = c_wgl_move(pt_dlg_dialog->h_dlg_frm, &t_rect, FALSE);
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
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
static INT32 _dlg_set_visibility_by_style(
                    DLG_CONTROL_T*      pt_dlg_dialog
                    )
{
    c_wgl_set_visibility(pt_dlg_dialog->h_dlg_text, WGL_SW_NORMAL);

    if (pt_dlg_dialog->ui4_style_mask & DLG_STYLE_MASK_WITH_TITLE)
    {
        c_wgl_set_visibility(pt_dlg_dialog->h_dlg_title, WGL_SW_NORMAL);
    }
    else
    {
        c_wgl_set_visibility(pt_dlg_dialog->h_dlg_title, WGL_SW_HIDE);
    }

    if (pt_dlg_dialog->ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON1)
    {
        c_wgl_set_visibility(pt_dlg_dialog->at_button[0].h_dlg_btn, WGL_SW_NORMAL);
    }
    else
    {
        c_wgl_set_visibility(pt_dlg_dialog->at_button[0].h_dlg_btn, WGL_SW_HIDE);
    }

    if (pt_dlg_dialog->ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON2)
    {
        c_wgl_set_visibility(pt_dlg_dialog->at_button[1].h_dlg_btn, WGL_SW_NORMAL);
    }
    else
    {
        c_wgl_set_visibility(pt_dlg_dialog->at_button[1].h_dlg_btn, WGL_SW_HIDE);
    }

    if (pt_dlg_dialog->ui4_style_mask & DLG_STYLE_MASK_WITH_BUTTON3)
    {
        c_wgl_set_visibility(pt_dlg_dialog->at_button[2].h_dlg_btn, WGL_SW_NORMAL);
    }
    else
    {
        c_wgl_set_visibility(pt_dlg_dialog->at_button[2].h_dlg_btn, WGL_SW_HIDE);
    }

    return DLGR_OK;
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
static INT32 _dlg_image_init(
                    DLG_VIEW_INIT_T*    pt_dlg_view_init,
                    DLG_CONTROL_T*      pt_dlg_dialog
                    )
{
    /* INT32 i4_ret = 0; */

#if 0
    /* Background of dialog */
    if (h_g_d_gcc_dlg_btn_selected_bk_img != NULL_HANDLE)
    {
        pt_dlg_dialog->h_dlg_frame_bk = h_g_d_gcc_dlg_frame_bk_img;
    } else
    {
        return DLGR_FAIL;
    }
    /* Background of selected button */
    if (h_g_d_gcc_dlg_btn_selected_bk_img != NULL_HANDLE)
    {
        pt_dlg_dialog->h_dlg_btn_selected_bk = h_g_d_gcc_dlg_btn_selected_bk_img;
    } else
    {
        return DLGR_FAIL;
    }

    /* Background of unselected button */
    if (h_g_d_gcc_dlg_btn_selected_bk_img != NULL_HANDLE)
    {
        pt_dlg_dialog->h_dlg_btn_unselected_bk = h_g_d_gcc_dlg_btn_unselected_bk_img;
    } else
    {
        return DLGR_FAIL;
    }
#endif

    if (pt_dlg_view_init->h_dlg_img_bg)
    {
        pt_dlg_dialog->h_dlg_frame_bk = pt_dlg_view_init->h_dlg_img_bg;
    }
    else
    {
        return DLGR_FAIL;
    }

    if (pt_dlg_view_init->h_dlg_img_btn_nor)
    {
        pt_dlg_dialog->h_dlg_btn_unselected_bk = pt_dlg_view_init->h_dlg_img_btn_nor;
    }
    else
    {
        return DLGR_FAIL;
    }

    if (pt_dlg_view_init->h_dlg_img_btn_hlt)
    {
        pt_dlg_dialog->h_dlg_btn_selected_bk = pt_dlg_view_init->h_dlg_img_btn_hlt;
    }
    else
    {
        return DLGR_FAIL;
    }

    /*
    nav_img_create_upg_bk_img_tpl(&pt_dlg_dialog->h_dlg_frame_bk);

    nav_img_create_upg_hl_bk_img_tpl(&pt_dlg_dialog->h_dlg_btn_selected_bk);

    pt_dlg_dialog->h_dlg_btn_unselected_bk = pt_dlg_dialog->h_dlg_btn_selected_bk;
    */

    return DLGR_OK;
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
INT32 a_dlg_create(
                    DLG_INIT_T*         pt_dlg_init,                  /* in  */
                    HANDLE_T*           ph_dlg_handle                 /* out */
                    )
{
    INT32           i4_ret;
    INT32           i4_result;
    DLG_CONTROL_T*  pt_dlg_dialog;

    if(!_dlg_validate_style_mask(pt_dlg_init->ui4_style_mask))
    {
        return DLGR_INV_ARG;
    }

    pt_dlg_dialog = (DLG_CONTROL_T*)c_mem_alloc(sizeof(DLG_CONTROL_T));
    if(pt_dlg_dialog == NULL)
    {
        return DLGR_OUT_OF_MEMORY;
    }
    c_memset(pt_dlg_dialog, 0 , sizeof(DLG_CONTROL_T));

    /* Image initial*/
    _dlg_image_init(&pt_dlg_init->t_view_init, pt_dlg_dialog);

    /* Create content frame widget */
    do
    {
        /* Content Frame */
        i4_result = _dlg_create_frm(pt_dlg_dialog,
                                    pt_dlg_init->h_parent,
                                    pt_dlg_init->e_style
                                    );
        if(i4_result != DLGR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* Title Area */
        i4_result = _dlg_create_title(pt_dlg_dialog);
        if(i4_result != DLGR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* Text Area */
        i4_result = _dlg_create_text(pt_dlg_dialog);
        if(i4_result != DLGR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* Button Area */
        i4_result = _dlg_create_btn(pt_dlg_dialog);
        if(i4_result != DLGR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* Save the initial information */
        pt_dlg_dialog->h_parent       = pt_dlg_init->h_parent;
        pt_dlg_dialog->e_align        = pt_dlg_init->e_align;
        pt_dlg_dialog->pf_fct         = pt_dlg_init->pf_fct;
        pt_dlg_dialog->pv_tag         = pt_dlg_init->pv_tag;
        pt_dlg_dialog->ui4_style_mask = pt_dlg_init->ui4_style_mask;

        /* Hide the main frame at initial time */
        c_wgl_set_visibility(pt_dlg_dialog->h_dlg_frm, WGL_SW_HIDE);

        /* Return the ph_dlg_handle handle */
        *ph_dlg_handle = pt_dlg_dialog->h_dlg_frm;

        /* Done */
        _dlg_set_attach_data(pt_dlg_dialog->h_dlg_frm,
                             pt_dlg_dialog);

        /* check answer and set the button status */
        pt_dlg_dialog->ui1_hlt_btn_idx = DLG_DFLT_HLT_BTN_IDX;

        a_dlg_set_highlight_button(pt_dlg_dialog->h_dlg_frm,
                                   pt_dlg_dialog->ui1_hlt_btn_idx);

        i4_ret = DLGR_OK;

    } while(0);

    if(i4_ret != DLGR_OK)
    {
        i4_ret = _dlg_destroy(pt_dlg_dialog->h_dlg_frm);
        if (NULL != pt_dlg_dialog)
        {
            c_mem_free(pt_dlg_dialog);
            pt_dlg_dialog = NULL;
        }
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
INT32 a_dlg_destroy(
                    HANDLE_T            h_dlg_handle
                    )

{
    INT32   i4_ret;

    i4_ret = _dlg_destroy(h_dlg_handle);

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
INT32 a_dlg_set_style_mask(
                    HANDLE_T            h_dlg_handle,
                    UINT32              ui4_style_mask
                    )
{
    INT32           i4_ret;
    DLG_CONTROL_T*  pt_dlg_dialog;

    /* get dialog structure */
    i4_ret = _dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    pt_dlg_dialog->ui4_style_mask = ui4_style_mask;

    return DLGR_OK;
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
INT32 a_dlg_set_align(
                    HANDLE_T            h_dlg_handle,
                    DLG_ALIGN_T         e_align
                    )
{
    INT32           i4_ret;
    DLG_CONTROL_T*  pt_dlg_dialog;

    /* get dialog structure */
    i4_ret = _dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    /* set algin */
    pt_dlg_dialog->e_align = e_align;

    return DLGR_OK;
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
INT32 a_dlg_set_title(
                    HANDLE_T            h_dlg_handle,
                    UTF16_T*            w2s_str
                    )
{
    INT32           i4_ret;
    DLG_CONTROL_T*  pt_dlg_dialog;

    /* get dialog structure */
    i4_ret = _dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK(c_uc_w2s_strlen(w2s_str)));
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
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
INT32 a_dlg_set_text(
                    HANDLE_T            h_dlg_handle,
                    UTF16_T*            w2s_str
                    )
{
    INT32           i4_ret;
    DLG_CONTROL_T*  pt_dlg_dialog;

    /* get dialog structure */
    i4_ret = _dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_dlg_dialog->h_dlg_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK(c_uc_w2s_strlen(w2s_str)));
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
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
INT32 a_dlg_set_buttons(
                    HANDLE_T            h_dlg_handle,
                    UINT16              ui2_button_num,
                    DLG_BUTTON_DEF_T*   pt_button_def
                    )
{
    INT32           i4_ret;
    DLG_CONTROL_T*  pt_dlg_dialog;
    UINT16          ui2_idx;

    if (ui2_button_num > DLG_DFLT_MAX_BTN_NUM)
    {
      return DLGR_INV_ARG;
    }

    /* Get dialog structure */
    i4_ret = _dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    for (ui2_idx = 0; ui2_idx < ui2_button_num; ui2_idx++)
    {
        pt_dlg_dialog->at_button[ui2_idx].pf_dlg_btn_act_cb_fct = pt_button_def[ui2_idx].pf_dlg_btn_act_cb_fct;
        pt_dlg_dialog->at_button[ui2_idx].pv_tag = pt_button_def[ui2_idx].pv_tag;

        i4_ret = c_wgl_do_cmd(pt_dlg_dialog->at_button[ui2_idx].h_dlg_btn,
                              WGL_CMD_BTN_SET_TEXT,
                              WGL_PACK(pt_button_def[ui2_idx].pw2s_dlg_btn_txt),
                              WGL_PACK(c_uc_w2s_strlen(pt_button_def[ui2_idx].pw2s_dlg_btn_txt)));
        DLG_CHK_FAIL(i4_ret);
    }

    return DLGR_OK;
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
INT32 a_dlg_set_highlight_button(
                    HANDLE_T            h_dlg_handle,
                    UINT8               ui8_btn_idx
                    )
{
    INT32               i4_ret;
    DLG_CONTROL_T*      pt_dlg_dialog;
    UINT8               ui1_idx;
    WGL_FONT_INFO_T     t_fnt_info;

    if (ui8_btn_idx >= DLG_DFLT_MAX_BTN_NUM)
    {
        return DLGR_INV_ARG;
    }

    /* get dialog structure */
    i4_ret = _dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    /* save the hightlight index */
    pt_dlg_dialog->ui1_hlt_btn_idx = ui8_btn_idx;

    /* set the appearance of buttons */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    for (ui1_idx = 0; ui1_idx < DLG_DFLT_MAX_BTN_NUM; ui1_idx++)
    {
        if (ui1_idx == ui8_btn_idx)
        {
            t_fnt_info.e_font_size = DLG_BTN_HLT_FONT_SIZE;
            i4_ret = c_wgl_do_cmd(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
            DLG_CHK_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                                WGL_CMD_BTN_SET_PUSHED,
                                WGL_PACK(TRUE),
                                NULL);
        }
        else
        {
            t_fnt_info.e_font_size = DLG_BTN_DFLT_FONT_SIZE;
            i4_ret = c_wgl_do_cmd(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
            DLG_CHK_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(pt_dlg_dialog->at_button[ui1_idx].h_dlg_btn,
                                WGL_CMD_BTN_SET_PUSHED,
                                WGL_PACK(FALSE),
                                NULL);
        }
	}

	DLG_CHK_FAIL(i4_ret);

	return DLGR_OK;
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
INT32 a_dlg_repaint(
                    HANDLE_T            h_dlg_handle
                    )
{
    INT32           i4_ret;
    DLG_CONTROL_T*  pt_dlg_dialog;

    /* get dialog structure */
    i4_ret = _dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    /* 1. reallocate layout */
    i4_ret = _dlg_allocate_layout(pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    /* 2. set visibility by style */
    i4_ret = _dlg_set_visibility_by_style(pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    /* 3. set to topmost. */
    i4_ret = c_wgl_insert (h_dlg_handle,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    DLG_CHK_FAIL (i4_ret);

    /* 4. repaint it */
    i4_ret = c_wgl_repaint(h_dlg_handle, NULL, TRUE);
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
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
INT32 a_dlg_set_visibility(
                    HANDLE_T            h_dlg_handle,                 /* in  */
                    BOOL                b_visible                     /* in  */
                    )
{
    INT32           i4_ret;
    DLG_CONTROL_T*  pt_dlg_dialog;

    /* Get dialog structure */
    i4_ret = _dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    /* 1. Reallocate layout */
    i4_ret = _dlg_allocate_layout(pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    if (b_visible)
    {
        /* 2 et visibility by style */
        i4_ret = _dlg_set_visibility_by_style(pt_dlg_dialog);
        DLG_CHK_FAIL(i4_ret);

        /* 3. Set frame visibility*/
        c_wgl_set_visibility(h_dlg_handle, WGL_SW_NORMAL);


    }
    else
    {
        c_wgl_set_visibility(h_dlg_handle, WGL_SW_HIDE);
    }

    return DLGR_OK;
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
INT32 a_dlg_set_focus(
                    HANDLE_T            h_dlg_handle
                    )
{
    INT32           i4_ret;
    DLG_CONTROL_T*  pt_dlg_dialog;

    /* Get dialog structure */
    i4_ret = _dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    /* 1. Reallocate layout */
    i4_ret = _dlg_allocate_layout(pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    /* 2. Set focus */
    c_wgl_set_focus(h_dlg_handle, FALSE);

    return DLGR_OK;
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
INT32 a_dlg_show(
                    HANDLE_T            h_dlg_handle
                    )
{
    INT32           i4_ret;
    DLG_CONTROL_T*  pt_dlg_dialog;

    /* Get dialog structure */
    i4_ret = _dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    /* 1. Reallocate layout */
    i4_ret = _dlg_allocate_layout(pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    /* 2. Set visibility by style */
    i4_ret = _dlg_set_visibility_by_style(pt_dlg_dialog);
    DLG_CHK_FAIL(i4_ret);

    /* 3. Set frame visibility*/
    c_wgl_set_visibility(h_dlg_handle, WGL_SW_NORMAL);

    /* 4. Set focus */
    c_wgl_set_focus(h_dlg_handle, FALSE);

    /* 5. Set to topmost. */
    i4_ret = c_wgl_insert (h_dlg_handle,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    DLG_CHK_FAIL (i4_ret);

    /* 6. Repaint the frame */
    i4_ret = c_wgl_repaint(h_dlg_handle, NULL, TRUE);
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
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
INT32 a_dlg_hide(
                    HANDLE_T            h_dlg_handle)
{
    INT32           i4_ret;

    /* Hide the dialog frame */
    i4_ret = c_wgl_set_visibility(h_dlg_handle, WGL_SW_HIDE);
    DLG_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_dlg_handle, NULL, TRUE);
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
}

/* ------------------------------------------------------------------------- */

static HANDLE_T h_frm_divx = NULL_HANDLE;
MMP_DC_DLG_TYPE_T e_divx_dlg_type = MMP_DC_DLG_TYPE_NONE;

/*----------------------------------------------------------------------------
 * Name: _mmp_dc_dlg_show_1
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: DLGR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 _mmp_dc_dlg_show_1(
                    HANDLE_T                        h_frm_main,
                    MMP_DC_DLG_TYPE_T               e_dlg_type,
                    UINT32                          ui4_use_count,
                    mmp_dc_btn_act_cb_fct           pt_cb_fct
                    )
{
#define _MMP_DC_DLG_SHOW1_TTL_MAX_LEN        (64)    /* title */
#define _MMP_DC_DLG_SHOW1_TXT_MAX_LEN        (128)   /* text  */

    HANDLE_T            h_dc_btn_nor;
    HANDLE_T            h_dc_btn_hlt;
    HANDLE_T            h_dc_frm_bg;
    DLG_INIT_T          t_init;
    DLG_BUTTON_DEF_T    at_btn_def[1];
    CHAR                sz_dlg_ttl[_MMP_DC_DLG_SHOW1_TTL_MAX_LEN] = {0};
    CHAR                sz_dlg_txt [_MMP_DC_DLG_SHOW1_TXT_MAX_LEN] = {0};
    UTF16_T             ws_dlg_ttl[_MMP_DC_DLG_SHOW1_TTL_MAX_LEN] = {0};
    UTF16_T             ws_dlg_txt[_MMP_DC_DLG_SHOW1_TXT_MAX_LEN] = {0};
    INT32               i4_ret = 0;

    if((MMP_DC_DLG_TYPE_UNAUTH   != e_dlg_type) &&
       (MMP_DC_DLG_TYPE_EXPIRED != e_dlg_type))
    {
        return DLGR_INV_ARG;
    }

    if(NULL_HANDLE != h_frm_divx)
    {
        return DLGR_OK;
    }

    if((DLGR_OK != mmp_img_get_img(MMP_IMG_IMAGE_ID_BTN_NR_BK,  &h_dc_btn_nor)) ||
       (DLGR_OK != mmp_img_get_img(MMP_IMG_IMAGE_ID_BTN_HLT_BK, &h_dc_btn_hlt)) ||
       (DLGR_OK != mmp_img_get_img(MMP_IMG_IMAGE_ID_FRM_BK,     &h_dc_frm_bg )))
    {
        return DLGR_FAIL;
    }

    c_memset(at_btn_def, 0, sizeof(at_btn_def));

    t_init.h_parent         = h_frm_main;
    t_init.e_style          = DLG_STYLE_DIALOG;
    t_init.e_align          = DLG_ALIGN_CENTER;
    t_init.ui4_style_mask   = DLG_STYLE_MASK_FIXED_IMAGE_SIZE |
                              DLG_STYLE_MASK_WITH_TITLE       |
                              DLG_STYLE_MASK_WITH_BUTTON1;
    t_init.pf_fct           = NULL;
    t_init.pv_tag           = NULL;

    t_init.t_view_init.h_dlg_img_bg      = h_dc_frm_bg;
    t_init.t_view_init.h_dlg_img_btn_nor = h_dc_btn_nor;
    t_init.t_view_init.h_dlg_img_btn_hlt = h_dc_btn_hlt;

    i4_ret = a_dlg_create(&t_init, &h_frm_divx);
    DLG_CHK_FAIL(i4_ret);

    i4_ret = a_dlg_set_focus(h_frm_divx);
    DLG_CHK_FAIL(i4_ret);

    switch(e_dlg_type)
    {
        case MMP_DC_DLG_TYPE_UNAUTH:
#ifdef DIVX_DRM_60
            c_sprintf(sz_dlg_ttl, "");
            c_sprintf(sz_dlg_txt, "Your device is not authorized\n"
                                  "to play this DivX protected video.");
#else
            c_sprintf(sz_dlg_ttl, "Authorization Error");
            c_sprintf(sz_dlg_txt, "This player is not authorized\n"
                                  "to play this video.");
#endif
            break;

        case MMP_DC_DLG_TYPE_EXPIRED:
#ifdef DIVX_DRM_60
            c_sprintf(sz_dlg_ttl, "");
            c_sprintf(sz_dlg_txt, "This DivX rental has used %d of %d views.\n\n"
                                  "This DivX rental has expired.");
#else
            c_sprintf(sz_dlg_ttl, "Rental Expired");
            c_sprintf(sz_dlg_txt, "");
#endif
            break;

        default:
            break;
    }

    c_uc_ps_to_w2s(sz_dlg_ttl, ws_dlg_ttl, _MMP_DC_DLG_SHOW1_TTL_MAX_LEN);
    c_uc_ps_to_w2s(sz_dlg_txt, ws_dlg_txt, _MMP_DC_DLG_SHOW1_TXT_MAX_LEN);

    i4_ret = a_dlg_set_title(h_frm_divx, ws_dlg_ttl);
    DLG_CHK_FAIL(i4_ret);

    i4_ret = a_dlg_set_text(h_frm_divx, ws_dlg_txt);
    DLG_CHK_FAIL(i4_ret);

#ifdef DIVX_DRM_60
    at_btn_def[0].pw2s_dlg_btn_txt      = (UTF16_T*)L"OK";
#else
    at_btn_def[0].pw2s_dlg_btn_txt      = MLM_MMP_TEXT(0, MLM_MMP_KEY_DC_BTN_TXT_DONE);
#endif
    at_btn_def[0].pf_dlg_btn_act_cb_fct = pt_cb_fct;
    at_btn_def[0].pv_tag                = (VOID*)(UINT32)TRUE;

    i4_ret = a_dlg_set_buttons(h_frm_divx, 1, at_btn_def);
    DLG_CHK_FAIL(i4_ret);

    i4_ret = a_dlg_show(h_frm_divx);
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_dc_dlg_show_2
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: DLGR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 _mmp_dc_dlg_show_2(
                    HANDLE_T                        h_frm_main,
                    MMP_DC_DLG_TYPE_T               e_dlg_type,
                    UINT32                          ui4_use_limit,
                    UINT32                          ui4_use_count,
                    mmp_dc_btn_act_cb_fct           pt_cb_fct
                    )
{
#define _MMP_DC_DLG_SHOW2_TTL_MAX_LEN        (64)
#define _MMP_DC_DLG_SHOW2_TXT_MAX_LEN        (128)

    HANDLE_T            h_dc_btn_nor;
    HANDLE_T            h_dc_btn_hlt;
    HANDLE_T            h_dc_frm_bg;
    DLG_INIT_T          t_init;
    DLG_BUTTON_DEF_T    at_btn_def[2];
    CHAR                sz_dlg_ttl[_MMP_DC_DLG_SHOW2_TTL_MAX_LEN] = {0};
    CHAR                sz_dlg_txt [_MMP_DC_DLG_SHOW2_TXT_MAX_LEN] = {0};
    UTF16_T             ws_dlg_ttl[_MMP_DC_DLG_SHOW2_TTL_MAX_LEN] = {0};
    UTF16_T             ws_dlg_txt[_MMP_DC_DLG_SHOW2_TXT_MAX_LEN] = {0};
    INT32               i4_ret = 0;

    if(MMP_DC_DLG_TYPE_RENTAL != e_dlg_type)
    {
        return DLGR_INV_ARG;
    }

    if(NULL_HANDLE != h_frm_divx)
    {
        return DLGR_OK;
    }

    c_memset(at_btn_def, 0, sizeof(at_btn_def));

#ifdef DIVX_DRM_60
    c_sprintf(sz_dlg_ttl, "");
    c_sprintf(sz_dlg_txt, "This DivX rental has used %d of %d views.\n\n"
                          "Continue?",
              ui4_use_count,
              ui4_use_limit);
#else
    c_sprintf(sz_dlg_ttl, "View DivX(R) VOD Rental");
    c_sprintf(sz_dlg_txt, "This rental has %u views left.\n"
                          "Do you want to use one\n"
                           "of your %u views now?",
              ui4_use_limit - ui4_use_count,
              ui4_use_limit - ui4_use_count);
#endif

    c_uc_ps_to_w2s(sz_dlg_ttl, ws_dlg_ttl, _MMP_DC_DLG_SHOW2_TXT_MAX_LEN);
    c_uc_ps_to_w2s(sz_dlg_txt, ws_dlg_txt, _MMP_DC_DLG_SHOW2_TXT_MAX_LEN);

    if((DLGR_OK != mmp_img_get_img(MMP_IMG_IMAGE_ID_BTN_NR_BK,  &h_dc_btn_nor)) ||
       (DLGR_OK != mmp_img_get_img(MMP_IMG_IMAGE_ID_BTN_HLT_BK, &h_dc_btn_hlt)) ||
       (DLGR_OK != mmp_img_get_img(MMP_IMG_IMAGE_ID_FRM_BK,     &h_dc_frm_bg )))
    {
        return DLGR_FAIL;
    }

    t_init.h_parent         = h_frm_main;
    t_init.e_style          = DLG_STYLE_DIALOG;
    t_init.e_align          = DLG_ALIGN_CENTER;
    t_init.ui4_style_mask   = DLG_STYLE_MASK_FIXED_IMAGE_SIZE |
                              DLG_STYLE_MASK_WITH_TITLE       |
                              DLG_STYLE_MASK_WITH_BUTTON1     |
                              DLG_STYLE_MASK_WITH_BUTTON2;
    t_init.pf_fct           = NULL;
    t_init.pv_tag           = NULL;

    t_init.t_view_init.h_dlg_img_bg      = h_dc_frm_bg;
    t_init.t_view_init.h_dlg_img_btn_nor = h_dc_btn_nor;
    t_init.t_view_init.h_dlg_img_btn_hlt = h_dc_btn_hlt;

    i4_ret = a_dlg_create(&t_init, &h_frm_divx);
    DLG_CHK_FAIL(i4_ret);

    i4_ret = a_dlg_set_focus(h_frm_divx);
    DLG_CHK_FAIL(i4_ret);

    i4_ret = a_dlg_set_title(h_frm_divx, ws_dlg_ttl);
    DLG_CHK_FAIL(i4_ret);

    i4_ret = a_dlg_set_text(h_frm_divx, ws_dlg_txt);
    DLG_CHK_FAIL(i4_ret);

    /* pv_tag is used to judge the button which user pushed */
#ifdef DIVX_DRM_60
    at_btn_def[0].pw2s_dlg_btn_txt      = (UTF16_T*)L"OK";
#else
    at_btn_def[0].pw2s_dlg_btn_txt      = MLM_MMP_TEXT(0, MLM_MMP_KEY_DC_BTN_TXT_YES);
#endif
    at_btn_def[0].pf_dlg_btn_act_cb_fct = pt_cb_fct;
    at_btn_def[0].pv_tag                = (VOID*)(UINT32)TRUE;

#ifdef DIVX_DRM_60
    at_btn_def[1].pw2s_dlg_btn_txt      = (UTF16_T*)L"Cancel";
#else
    at_btn_def[1].pw2s_dlg_btn_txt      = MLM_MMP_TEXT(0, MLM_MMP_KEY_DC_BTN_TXT_NO);
#endif
    at_btn_def[1].pf_dlg_btn_act_cb_fct = pt_cb_fct;
    at_btn_def[1].pv_tag                = (VOID*)(UINT32)FALSE;

    i4_ret = a_dlg_set_buttons(h_frm_divx, 2, at_btn_def);
    DLG_CHK_FAIL(i4_ret);

    i4_ret = a_dlg_show(h_frm_divx);
    DLG_CHK_FAIL(i4_ret);

    return DLGR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_dc_dlg_show
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: DLGR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_dc_dlg_show(
                    HANDLE_T                        h_frm_main,
                    MMP_VE_DIVX_CERT_PTR_T          pt_divx_cert,
                    mmp_dc_btn_act_cb_fct           pt_cb_fct
                    )
{
    if(MMP_VE_DRM_TYPE_UNAUTH == pt_divx_cert->t_drm_type)
    {
        /* show unauthorization error message */
        _mmp_dc_dlg_show_1(h_frm_main, MMP_DC_DLG_TYPE_UNAUTH, 0, pt_cb_fct);
        e_divx_dlg_type = MMP_DC_DLG_TYPE_UNAUTH;
    }
    else if(MMP_VE_DRM_TYPE_EXPIRE == pt_divx_cert->t_drm_type)
    {
        UINT32 ui4_use_left = pt_divx_cert->ui4_use_limit -
                              pt_divx_cert->ui4_use_count;

        /* show rental expired message */
        _mmp_dc_dlg_show_1(h_frm_main, MMP_DC_DLG_TYPE_EXPIRED, ui4_use_left, pt_cb_fct);
        e_divx_dlg_type = MMP_DC_DLG_TYPE_EXPIRED;
    }
    else if(MMP_VE_DRM_TYPE_RENTAL == pt_divx_cert->t_drm_type)
    {
        /* show rental confirmation choice */
        _mmp_dc_dlg_show_2(
                    h_frm_main,
                    MMP_DC_DLG_TYPE_RENTAL,
                    pt_divx_cert->ui4_use_limit,
                    pt_divx_cert->ui4_use_count,
                    pt_cb_fct
                    );
        e_divx_dlg_type = MMP_DC_DLG_TYPE_RENTAL;
    }
    else
    {
        return DLGR_INV_ARG;
    }

    return DLGR_OK;
}

INT32 mmp_dc_dlg_delete(VOID)
{
    if(NULL_HANDLE != h_frm_divx)
    {
        a_dlg_hide(h_frm_divx);
        a_dlg_destroy(h_frm_divx);
        h_frm_divx = NULL_HANDLE;
    }

    return DLGR_OK;
}

