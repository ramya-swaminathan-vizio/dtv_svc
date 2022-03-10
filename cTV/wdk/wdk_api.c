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
* $RCSfile: c_wdk_common.c,v $
* $Revision: #1 $
* $Date: 2015/05/29 $
* $Author: brianpc.huang $
* $CCRevision: /main/DTV_X_ATSC/13 $
* $SWAuthor: CS Kuo $
* $MD5HEX: 0dc5e5894593d8bd6b2c6ecc9869c8fa $
*
* Description:
*         This file contains function prototypes to support view commands of
*         the Menu application.
*---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_sets.h"

#include "c_os.h"
#include "c_handle.h"
#include "c_gl.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_wgl_rect.h"
#include "c_uc_str.h"

#include "wdk_api.h"

/*-----------------------------------------------------------------------------
macros, defines, typedefs, enums
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
data declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
function declarations
----------------------------------------------------------------------------*/
/*
* Internal Functions
*/
VOID _wdk_get_clr_info(WGL_COLOR_INFO_T *pt_clr_info,
                       WDK_COLOR_INFO_T *pt_clr_info_src)
{
    c_memset(pt_clr_info, 0, sizeof(WGL_COLOR_INFO_T));

    pt_clr_info->e_type = pt_clr_info_src->e_type;
    WDK_CLR_COPY (& pt_clr_info->u_color_data.t_extend.t_enable,
                    pt_clr_info_src->t_color_set.h_enable);
    WDK_CLR_COPY (& pt_clr_info->u_color_data.t_extend.t_disable,
                    pt_clr_info_src->t_color_set.h_disable);
    WDK_CLR_COPY (& pt_clr_info->u_color_data.t_extend.t_highlight,
                    pt_clr_info_src->t_color_set.h_highlight);
    WDK_CLR_COPY (& pt_clr_info->u_color_data.t_extend.t_highlight_inactive,
                    pt_clr_info_src->t_color_set.h_highlight_inactive);
    WDK_CLR_COPY (& pt_clr_info->u_color_data.t_extend.t_push,
                    pt_clr_info_src->t_color_set.h_push);
    WDK_CLR_COPY (& pt_clr_info->u_color_data.t_extend.t_push_unhighlight,
                    pt_clr_info_src->t_color_set.h_push_unhighlight);

    return;
}

VOID _wdk_get_img_info(WGL_IMG_INFO_T *pt_img_info,
                       WDK_IMG_INFO_T *pt_img_info_src)
{
    c_memset(pt_img_info, 0, sizeof(WGL_IMG_INFO_T));

    pt_img_info->e_type = pt_img_info_src->e_type;
    WDK_IMG_COPY(pt_img_info->u_img_data.t_extend.t_enable,
                 pt_img_info_src->t_img_set.h_enable);
    WDK_IMG_COPY(pt_img_info->u_img_data.t_extend.t_disable,
                 pt_img_info_src->t_img_set.h_disable);
    WDK_IMG_COPY(pt_img_info->u_img_data.t_extend.t_highlight,
                 pt_img_info_src->t_img_set.h_highlight);
    WDK_IMG_COPY(pt_img_info->u_img_data.t_extend.t_highlight_inactive,
                 pt_img_info_src->t_img_set.h_highlight_inactive);
    WDK_IMG_COPY(pt_img_info->u_img_data.t_extend.t_push,
                 pt_img_info_src->t_img_set.h_push);
    WDK_IMG_COPY(pt_img_info->u_img_data.t_extend.t_push_unhighlight,
                 pt_img_info_src->t_img_set.h_push_unhighlight);

    return;
}

VOID _wdk_get_lb_font_set(WGL_LB_FONT_INFO_EX_T *pt_font_set,
                          WDK_LB_FONT_SET_T *pt_font_set_src)
{
    c_memset(pt_font_set, 0, sizeof(WGL_LB_FONT_INFO_EX_T));

    WDK_COPY (& pt_font_set->t_normal,
              pt_font_set_src->pt_normal,
              sizeof(WGL_FONT_INFO_T));
    WDK_COPY (& pt_font_set->t_highlight,
              pt_font_set_src->pt_highlight,
              sizeof(WGL_FONT_INFO_T));
    WDK_COPY (& pt_font_set->t_highlight_unfocused,
              pt_font_set_src->pt_highlight_unfocused,
              sizeof(WGL_FONT_INFO_T));
    WDK_COPY (& pt_font_set->t_selected,
              pt_font_set_src->pt_selected,
              sizeof(WGL_FONT_INFO_T));

    return;
}

VOID _wdk_get_lb_clr_set(WGL_LB_COLOR_ELEM_SET_T *pt_clr_set,
                         WDK_LB_COLOR_SET_T *pt_clr_set_src)
{
    c_memset(pt_clr_set, 0, sizeof(WGL_LB_COLOR_ELEM_SET_T));

    WDK_CLR_COPY (& pt_clr_set->t_normal,
                    pt_clr_set_src->h_normal);
    WDK_CLR_COPY (& pt_clr_set->t_disable,
                    pt_clr_set_src->h_disable);
    WDK_CLR_COPY (& pt_clr_set->t_highlight,
                    pt_clr_set_src->h_highlight);
    WDK_CLR_COPY (& pt_clr_set->t_highlight_unfocus,
                    pt_clr_set_src->h_highlight_unfocus);
    WDK_CLR_COPY (& pt_clr_set->t_pushed,
                    pt_clr_set_src->h_pushed);
    WDK_CLR_COPY (& pt_clr_set->t_selected,
                    pt_clr_set_src->h_selected);
    WDK_CLR_COPY (& pt_clr_set->t_selected_disable,
                    pt_clr_set_src->h_selected_disable);

    return;
}

VOID _wdk_get_lb_img_set(WGL_LB_ITEM_IMG_SUIT_T *pt_img_set,
                         WDK_LB_IMG_SET_T *pt_img_set_src)
{
    c_memset(pt_img_set, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    /* WGL_LB_IMG_SUIT_T */
    WDK_IMG_COPY(pt_img_set->h_normal,
                 pt_img_set_src->h_normal);
    WDK_IMG_COPY(pt_img_set->h_disable,
                 pt_img_set_src->h_disable);
    WDK_IMG_COPY(pt_img_set->h_highlight,
                 pt_img_set_src->h_highlight);
    WDK_IMG_COPY(pt_img_set->h_highlight_unfocus,
                 pt_img_set_src->h_highlight_unfocus);
    WDK_IMG_COPY(pt_img_set->h_pushed,
                 pt_img_set_src->h_pushed);
    WDK_IMG_COPY(pt_img_set->h_selected,
                 pt_img_set_src->h_selected);
    WDK_IMG_COPY(pt_img_set->h_selected_disable,
                 pt_img_set_src->h_selected_disable);

    /* WGL_LB_ITEM_IMG_SUIT_T */
    WDK_IMG_COPY(pt_img_set->h_selected_highlight,
                 pt_img_set_src->h_selected_highlight);
    WDK_IMG_COPY(pt_img_set->h_selected_highlight_unfocus,
                 pt_img_set_src->h_selected_highlight_unfocus);
    WDK_IMG_COPY(pt_img_set->h_selected_pushed,
                 pt_img_set_src->h_selected_pushed);

    return;
}


VOID _wdk_get_fnt_info(WGL_FONT_INFO_EX_T *pt_fnt_info,
                       WDK_FONT_INFO_T    *pt_fnt_info_src)
{
    c_memset(pt_fnt_info, 0, sizeof(WGL_FONT_INFO_EX_T));

    pt_fnt_info->e_type = pt_fnt_info_src->e_type;
    WDK_COPY (& pt_fnt_info->u_font_data.t_basic.t_focused,
              pt_fnt_info_src->t_fnt_set.pt_focused,
              sizeof(WGL_FONT_INFO_T));

    WDK_COPY (& pt_fnt_info->u_font_data.t_basic.t_unfocused,
              pt_fnt_info_src->t_fnt_set.pt_unfocused,
              sizeof(WGL_FONT_INFO_T));

    return;
}

VOID _wdk_set_background(WDK_FRM_WGT_T *pt_wgt_param,
                         HANDLE_T      *ph_widget)
{
    return;
}

INT32 _wdk_set_border(HANDLE_T h_widget, UINT32 ui4_bdr_type, WDK_BORDER_INFO_T *pt_bdr_info)
{
    INT32 i4_ret;
    WGL_COLOR_INFO_T t_clr_info;
    WGL_IMG_INFO_T   t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    if (NULL_HANDLE == h_widget)
    {
        return (WDKR_FAILED);
    }

    if (WGL_BORDER_NULL == ui4_bdr_type
        || WGL_BORDER_DEPRESSED == ui4_bdr_type
        || WGL_BORDER_DROP_SHADOW_LEFT == ui4_bdr_type
        || WGL_BORDER_DROP_SHADOW_RIGHT == ui4_bdr_type)
    {
        /* do nothing */
        return (WDKR_OK);
    }

    if (NULL == pt_bdr_info)
    {
        return (WDKR_FAILED);
    }

    /* Inset */
    if (WGL_BORDER_TRANSP == ui4_bdr_type
        || WGL_BORDER_UNIFORM == ui4_bdr_type
        || WGL_BORDER_RAISED == ui4_bdr_type
        || WGL_BORDER_TIMG == ui4_bdr_type)
    {
        i4_ret = c_wgl_do_cmd(h_widget,
            WGL_CMD_GL_SET_INSET,
            WGL_PACK(&(pt_bdr_info->t_cnt_inset)),
            NULL);
        WDK_CHK_FAIL(i4_ret);
    }

    /* Background Color */
    if (WGL_BORDER_UNIFORM == ui4_bdr_type
        || WGL_BORDER_RAISED == ui4_bdr_type)
    {
        _wdk_get_clr_info(&t_clr_info, pt_bdr_info->pt_bk_clr);

        i4_ret = c_wgl_do_cmd(h_widget,
            WGL_CMD_GL_SET_BDR_COLOR,
            WGL_PACK(WGL_CLR_BDR_BK),
            WGL_PACK(&t_clr_info));
        WDK_CHK_FAIL(i4_ret);

    }

    /* Foreground Color */
    if (WGL_BORDER_UNIFORM == ui4_bdr_type
        || WGL_BORDER_RAISED == ui4_bdr_type)
    {
        _wdk_get_clr_info(&t_clr_info, pt_bdr_info->pt_fg_clr);

        i4_ret = c_wgl_do_cmd(h_widget,
            WGL_CMD_GL_SET_BDR_COLOR,
            WGL_PACK(WGL_CLR_BDR_FG),
            WGL_PACK(&t_clr_info));
        WDK_CHK_FAIL(i4_ret);

    }

    /* WGL_BORDER_UNIFORM - Thickness */
    if (WGL_BORDER_UNIFORM == ui4_bdr_type)
    {
        i4_ret = c_wgl_do_cmd(h_widget,
            WGL_CMD_BDR_UNFM_SET_THICKNESS,
            WGL_PACK(pt_bdr_info->ui4_thickness),
            NULL);
        WDK_CHK_FAIL(i4_ret);
    }

    /* WGL_BORDER_RAISED - Height */
    if (WGL_BORDER_RAISED == ui4_bdr_type)
    {
        i4_ret = c_wgl_do_cmd(h_widget,
            WGL_CMD_BDR_RS_SET_HEIGHT,
            WGL_PACK(pt_bdr_info->ui4_height),
            NULL);
        WDK_CHK_FAIL(i4_ret);
    }

    /* WGL_BORDER_TIMG - Background Image */
    if (WGL_BORDER_TIMG == ui4_bdr_type)
    {
        _wdk_get_clr_info(&t_clr_info, pt_bdr_info->pt_title_clr);
        i4_ret = c_wgl_do_cmd(h_widget,
              WGL_CMD_GL_SET_BDR_COLOR,
              WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
              WGL_PACK(&t_clr_info));
        WDK_CHK_FAIL(i4_ret);

        _wdk_get_img_info(&t_img_info, pt_bdr_info->pt_bk_img);
        i4_ret = c_wgl_do_cmd(h_widget,
            WGL_CMD_BDR_TIMG_SET_BK_IMG,
            WGL_PACK(&t_img_info),
            NULL);
        WDK_CHK_FAIL(i4_ret);

        c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
        t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
        WDK_COPY (&(t_title_info.t_font), pt_bdr_info->pt_fnt, sizeof(WGL_FONT_INFO_T));
        WDK_COPY (&(t_title_info.t_rc_ref), &(pt_bdr_info->t_rc_ref), sizeof(GL_RECT_T));
        t_title_info.ui1_align = pt_bdr_info->ui1_align;
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                              &t_title_info,
                              NULL);
        WDK_CHK_FAIL(i4_ret);
    }

    return (WDKR_OK);
}

/*
* External APIs
*/

/*----------------------------------------------------------------------------
* Name: a_wdk_create_frame
*
* Description: This function creates a frame widget according to the parameters.
*
* Inputs:  -
*
* Outputs: -
*
* Returns: 0                  Successful.
*          Any other values   Failed.
----------------------------------------------------------------------------*/

INT32 a_wdk_create_frame(WDK_FRM_WGT_T *pt_wgt_param,
                         UINT32         ui4_opt_mask,
                         HANDLE_T      *ph_widget)
{
    INT32 i4_ret;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;

    /* create widget */
    i4_ret = c_wgl_create_widget (pt_wgt_param->h_parent,
        HT_WGL_WIDGET_FRAME,
        WGL_CONTENT_FRAME_DEF,
        pt_wgt_param->ui4_border,
        &(pt_wgt_param->t_rect),
        pt_wgt_param->pf_wdgt_proc,
        pt_wgt_param->ui1_alpha,
        (VOID*) pt_wgt_param->ui4_style,
        0,
        ph_widget);
    WDK_CHK_FAIL(i4_ret);

    /* set border */
    _wdk_set_border(*ph_widget, pt_wgt_param->ui4_border, pt_wgt_param->pt_border);

    /* set background */
    if( (pt_wgt_param->ui4_style & WGL_STL_GL_NO_IMG_UI) == WGL_STL_GL_NO_IMG_UI)
    {
        _wdk_get_clr_info(&t_color_info, pt_wgt_param->t_bk_set.pt_clr_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_COLOR,
            WGL_PACK (WGL_CLR_BK), /* background color */
            WGL_PACK (& t_color_info));
        WDK_CHK_FAIL(i4_ret);
    }
    else
    {
        _wdk_get_img_info(&t_img_info, pt_wgt_param->t_bk_set.pt_img_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_IMAGE,
            WGL_PACK (WGL_IMG_BK), /* background image */
            WGL_PACK (& t_img_info));
        WDK_CHK_FAIL(i4_ret);
    }

    /* set visibility */
    WDK_CHK_FAIL (c_wgl_set_visibility (*ph_widget, WGL_SW_HIDE));

    return  i4_ret;
}

INT32 a_wdk_create_button(WDK_BTN_WGT_T *pt_wgt_param,
                          UINT32         ui4_opt_mask,
                          HANDLE_T      *ph_widget)
{
    INT32               i4_ret;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_EX_T  t_fnt_info;

    /* create widget */
    i4_ret = c_wgl_create_widget (pt_wgt_param->h_parent,
        HT_WGL_WIDGET_BUTTON,
        WGL_CONTENT_BUTTON_DEF,
        pt_wgt_param->ui4_border,
        &(pt_wgt_param->t_rect),
        pt_wgt_param->pf_wdgt_proc,
        pt_wgt_param->ui1_alpha,
        (VOID*) pt_wgt_param->ui4_style,
        0,
        ph_widget);
    WDK_CHK_FAIL(i4_ret);

    /* set border */
    _wdk_set_border(*ph_widget, pt_wgt_param->ui4_border, pt_wgt_param->pt_border);

    /* set background */
    if( (pt_wgt_param->ui4_style & WGL_STL_GL_NO_IMG_UI) == WGL_STL_GL_NO_IMG_UI)
    {
        _wdk_get_clr_info(&t_color_info, pt_wgt_param->t_bk_set.pt_clr_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_COLOR,
            WGL_PACK (WGL_CLR_BK), /* background color */
            WGL_PACK (& t_color_info));
        WDK_CHK_FAIL(i4_ret);
    }
    else
    {
        _wdk_get_img_info(&t_img_info, pt_wgt_param->t_bk_set.pt_img_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_IMAGE,
            WGL_PACK (WGL_IMG_BK), /* background image */
            WGL_PACK (& t_img_info));
        WDK_CHK_FAIL(i4_ret);
    }

    /* Special Part */
    /* Set Content Inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_BTN_SET_CNT_INSET,
        WGL_PACK(&pt_wgt_param->t_cnt_inset),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_BTN_SET_ALIGN,
        WGL_PACK(pt_wgt_param->ui1_align),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Foreground Image */
    if (NULL != pt_wgt_param->pt_fg_img)
    {
        _wdk_get_img_info(&t_img_info, pt_wgt_param->pt_fg_img);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_IMAGE,
            WGL_PACK (WGL_IMG_FG),
            WGL_PACK (& t_img_info));
        WDK_CHK_FAIL(i4_ret);
    }

    /* Set Text Color */
    _wdk_get_clr_info(&t_color_info, pt_wgt_param->pt_clr_text);

    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_GL_SET_COLOR,
        WGL_PACK(WGL_CLR_TEXT),
        WGL_PACK(&t_color_info));
    WDK_CHK_FAIL(i4_ret);

    /* Set Text */
    if (NULL != pt_wgt_param->pv_data
        && 0 != pt_wgt_param->ui2_text_id)
    {
        /* TODO */
    }

    /* Set Distance */
    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_BTN_SET_DISTANCE,
        WGL_PACK(pt_wgt_param->i4_distance),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Order */
    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_BTN_SET_ORDER,
        WGL_PACK(pt_wgt_param->ui1_order),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Font */
    _wdk_get_fnt_info(&t_fnt_info, pt_wgt_param->pt_fnt);
    c_wgl_do_cmd (*ph_widget,
        WGL_CMD_GL_SET_FONT_EX,
        WGL_PACK(&t_fnt_info),
        NULL);
    /* WDK_CHK_FAIL(i4_ret); */

    /* set visibility */
    WDK_CHK_FAIL (c_wgl_set_visibility (*ph_widget, WGL_SW_NORMAL));

    return  i4_ret;
}


/*----------------------------------------------------------------------------
* Name: a_wdk_create_txt
*
* Description: This function creates a text widget according to the parameters.
*
* Inputs:  -
*
* Outputs: -
*
* Returns: 0                  Successful.
*          Any other values   Failed.
----------------------------------------------------------------------------*/
INT32 a_wdk_create_text (WDK_TXT_WGT_T *pt_wgt_param,
                         UINT32         ui4_opt_mask,
                         HANDLE_T      *ph_widget)
{
    INT32               i4_ret;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_EX_T  t_fnt_info;

    /* create widget */
    i4_ret = c_wgl_create_widget ( pt_wgt_param->h_parent,
        HT_WGL_WIDGET_TEXT,
        WGL_CONTENT_TEXT_DEF,
        pt_wgt_param->ui4_border,
        &(pt_wgt_param->t_rect),
        pt_wgt_param->pf_wdgt_proc,
        pt_wgt_param->ui1_alpha,
        (VOID*) pt_wgt_param->ui4_style,
        0,
        ph_widget);
    WDK_CHK_FAIL(i4_ret);

    /* set border */
    _wdk_set_border(*ph_widget, pt_wgt_param->ui4_border, pt_wgt_param->pt_border);

    /* set background */
    if( (pt_wgt_param->ui4_style & WGL_STL_GL_NO_IMG_UI) == WGL_STL_GL_NO_IMG_UI)
    {
        _wdk_get_clr_info(&t_color_info, pt_wgt_param->t_bk_set.pt_clr_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_COLOR,
            WGL_PACK (WGL_CLR_BK), /* background color */
            WGL_PACK (& t_color_info));
        WDK_CHK_FAIL(i4_ret);
    }
    else
    {
        _wdk_get_img_info(&t_img_info, pt_wgt_param->t_bk_set.pt_img_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_IMAGE,
            WGL_PACK (WGL_IMG_BK), /* background image */
            WGL_PACK (& t_img_info));
        WDK_CHK_FAIL(i4_ret);
    }

    /* Special Part */
    /* Set Content Inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_TEXT_SET_CNT_INSET,
        WGL_PACK(&pt_wgt_param->t_cnt_inset),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_TEXT_SET_ALIGN,
        WGL_PACK(pt_wgt_param->ui1_align),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Font */
    _wdk_get_fnt_info(&t_fnt_info, pt_wgt_param->pt_fnt);
    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_GL_SET_FONT_EX,
        WGL_PACK(&t_fnt_info),
        NULL);
    /* WDK_CHK_FAIL(i4_ret); */

    /* Set Text Color */
    _wdk_get_clr_info(&t_color_info, pt_wgt_param->pt_clr_text);

    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_GL_SET_COLOR,
        WGL_PACK(WGL_CLR_TEXT),
        WGL_PACK(&t_color_info));
    WDK_CHK_FAIL(i4_ret);

    /* Set Line Gap */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_TEXT_SET_LINE_GAP,
        WGL_PACK(pt_wgt_param->i4_line_gap),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Max Line */
    if((pt_wgt_param->ui4_style & WGL_STL_TEXT_MULTILINE)
        && (pt_wgt_param->ui4_style & WGL_STL_TEXT_MAX_DIS_USER_DEF))
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
            WGL_CMD_TEXT_SET_MAX_DIS_LINE,
            WGL_PACK(pt_wgt_param->ui2_max_line),
            NULL);
        WDK_CHK_FAIL(i4_ret);
    }

    /* set visibility */
    WDK_CHK_FAIL (c_wgl_set_visibility (*ph_widget, WGL_SW_NORMAL));

    return  i4_ret;
}


/*----------------------------------------------------------------------------
* Name: a_wdk_create_icon
*
* Description: This function creates a icon widget according to the parameters.
*
* Inputs:  -
*
* Outputs: -
*
* Returns: 0                  Successful.
*          Any other values   Failed.
----------------------------------------------------------------------------*/

INT32 a_wdk_create_icon(WDK_ICON_WGT_T *pt_wgt_param,
                        UINT32         ui4_opt_mask,
                        HANDLE_T      *ph_widget)
{
    INT32               i4_ret;
    INT32               i4_idx;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_ICON_MULTIPLE_INFO_T t_multi_img_info = {0};

    /* create widget */
    i4_ret = c_wgl_create_widget (pt_wgt_param->h_parent,
        HT_WGL_WIDGET_ICON,
        WGL_CONTENT_ICON_DEF,
        pt_wgt_param->ui4_border,
        &(pt_wgt_param->t_rect),
        pt_wgt_param->pf_wdgt_proc,
        pt_wgt_param->ui1_alpha,
        (VOID*) pt_wgt_param->ui4_style,
        0,
        ph_widget);
    WDK_CHK_FAIL(i4_ret);

    /* set border */
    _wdk_set_border(*ph_widget, pt_wgt_param->ui4_border, pt_wgt_param->pt_border);

    /* set background */
    if( (pt_wgt_param->ui4_style & WGL_STL_GL_NO_IMG_UI) == WGL_STL_GL_NO_IMG_UI)
    {
        _wdk_get_clr_info(&t_color_info, pt_wgt_param->t_bk_set.pt_clr_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_COLOR,
            WGL_PACK (WGL_CLR_BK), /* background color */
            WGL_PACK (& t_color_info));
        WDK_CHK_FAIL(i4_ret);
    }
    else
    {
        _wdk_get_img_info(&t_img_info, pt_wgt_param->t_bk_set.pt_img_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_IMAGE,
            WGL_PACK (WGL_IMG_BK), /* background image */
            WGL_PACK (& t_img_info));
        WDK_CHK_FAIL(i4_ret);
    }

    /* Special Part */
    /* Set Content Inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_ICON_SET_CNT_INSET,
        WGL_PACK(&pt_wgt_param->t_cnt_inset),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_ICON_SET_ALIGN,
        WGL_PACK(pt_wgt_param->ui1_align),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Foreground Image */
    if (WGL_STL_ICON_MULTI_IMG & pt_wgt_param->ui4_style)
    {
        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_ICON_SET_MAX_FG_IMG_NUM,
            WGL_PACK (pt_wgt_param->u4_multi_image_max),
            NULL);
        WDK_CHK_FAIL(i4_ret);

        t_multi_img_info.ui4_node_num = pt_wgt_param->u4_multi_image_num;
        t_multi_img_info.at_nodes = c_mem_alloc(sizeof(WGL_ICON_FG_IMG_NODE_T)*t_multi_img_info.ui4_node_num);

        if (NULL == t_multi_img_info.at_nodes)
        {
            return (WDKR_FAILED);
        }
        c_memset(t_multi_img_info.at_nodes, 0, sizeof(WGL_ICON_FG_IMG_NODE_T)*t_multi_img_info.ui4_node_num);

        for(i4_idx=0; i4_idx<(INT32)(pt_wgt_param->u4_multi_image_num); i4_idx++)
        {
            t_multi_img_info.at_nodes[i4_idx].i4_ahead_gap = pt_wgt_param->pt_img_node[i4_idx].i4_ahead_gap;
            _wdk_get_img_info(&(t_multi_img_info.at_nodes[i4_idx].t_img_info),
                pt_wgt_param->pt_img_node[i4_idx].pt_img_info);
        }

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_IMAGE,
            WGL_PACK(WGL_IMG_ICON_MULTIPLE),
            WGL_PACK(& t_multi_img_info));
        WDK_CHK_FAIL(i4_ret);

        c_mem_free(t_multi_img_info.at_nodes);
        t_multi_img_info.at_nodes = NULL;
    }
    else if (NULL != pt_wgt_param->pt_fg_img)
    {
        _wdk_get_img_info(&t_img_info, pt_wgt_param->pt_fg_img);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_IMAGE,
            WGL_PACK (WGL_IMG_FG),
            WGL_PACK (& t_img_info));
        WDK_CHK_FAIL(i4_ret);
    }

    /* set visibility */
    WDK_CHK_FAIL (c_wgl_set_visibility (*ph_widget, WGL_SW_NORMAL));

    return  i4_ret;
}


/*----------------------------------------------------------------------------
* Name: a_wdk_create_pb
*
* Description: This function creates a progress bar widget according to the parameters.
*
* Inputs:  -
*
* Outputs: -
*
* Returns: 0                  Successful.
*          Any other values   Failed.
----------------------------------------------------------------------------*/

INT32 a_wdk_create_pb(WDK_PB_WGT_T *pt_wgt_param,
                      UINT32         ui4_opt_mask,
                      HANDLE_T      *ph_widget)
{
    INT32               i4_ret;
    INT32               i4_idx;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_EX_T  t_fnt_info;
    WGL_PG_IDR_LOC_T    *pt_min_idr = NULL;
    WGL_PG_IDR_LOC_T    *pt_pos_idr = NULL;
    WGL_PG_IDR_LOC_T    *pt_max_idr = NULL;

    /* create widget */
    i4_ret = c_wgl_create_widget (pt_wgt_param->h_parent,
        HT_WGL_WIDGET_PROGRESS_BAR,
        WGL_CONTENT_PROGRESS_BAR_DEF,
        pt_wgt_param->ui4_border,
        &(pt_wgt_param->t_rect),
        pt_wgt_param->pf_wdgt_proc,
        pt_wgt_param->ui1_alpha,
        (VOID*) pt_wgt_param->ui4_style,
        0,
        ph_widget);
    WDK_CHK_FAIL(i4_ret);

    /* set border */
    _wdk_set_border(*ph_widget, pt_wgt_param->ui4_border, pt_wgt_param->pt_border);

    /* set background */
    if( (pt_wgt_param->ui4_style & WGL_STL_GL_NO_IMG_UI) == WGL_STL_GL_NO_IMG_UI)
    {
        _wdk_get_clr_info(&t_color_info, pt_wgt_param->t_bk_set.pt_clr_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_COLOR,
            WGL_PACK (WGL_CLR_BK), /* background color */
            WGL_PACK (& t_color_info));
        WDK_CHK_FAIL(i4_ret);
    }
    else
    {
        _wdk_get_img_info(&t_img_info, pt_wgt_param->t_bk_set.pt_img_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_IMAGE,
            WGL_PACK (WGL_IMG_BK), /* background image */
            WGL_PACK (&t_img_info));
        WDK_CHK_FAIL(i4_ret);
    }

    /* Special Part */
    /* Set Content Inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_PG_SET_CNT_INSET,
        WGL_PACK(&pt_wgt_param->t_cnt_inset),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Bar Inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_PG_SET_BAR_INSET,
        WGL_PACK(& pt_wgt_param->t_bar_inset),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Display Mode */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_PG_SET_DISPLAY_MODE,
        WGL_PACK(pt_wgt_param->ui4_display_mode),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Range */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_PG_SET_RANGE,
        WGL_PACK(pt_wgt_param->i4_range_min),
        WGL_PACK(pt_wgt_param->i4_range_max));
    WDK_CHK_FAIL(i4_ret);

    /* Set Position */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_PG_SET_POS,
        WGL_PACK(pt_wgt_param->i4_position),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Indicator */
    if (!WGL_RECT_IS_EMPTY(&(pt_wgt_param->t_min_idr.t_loc_rect)))
    {
        pt_min_idr = &(pt_wgt_param->t_min_idr);
    }
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_PG_SET_IDR_LOC,
        WGL_PACK(WGL_PG_CNT_ILT_MIN),
        WGL_PACK(pt_min_idr));
    WDK_CHK_FAIL(i4_ret);

    if (!WGL_RECT_IS_EMPTY(&(pt_wgt_param->t_pos_idr.t_loc_rect)))
    {
        pt_pos_idr = &(pt_wgt_param->t_pos_idr);
    }
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_PG_SET_IDR_LOC,
        WGL_PACK(WGL_PG_CNT_ILT_POS),
        WGL_PACK(pt_pos_idr));
    WDK_CHK_FAIL(i4_ret);

    if (!WGL_RECT_IS_EMPTY(&(pt_wgt_param->t_max_idr.t_loc_rect)))
    {
        pt_max_idr = &(pt_wgt_param->t_max_idr);
    }
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_PG_SET_IDR_LOC,
        WGL_PACK(WGL_PG_CNT_ILT_MAX),
        WGL_PACK(pt_max_idr));
    WDK_CHK_FAIL(i4_ret);

    /* Set Block Size */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_PG_SET_BLK_PT_SIZE,
        WGL_PACK(pt_wgt_param->u2_block_w),
        WGL_PACK(pt_wgt_param->u2_block_h));
    WDK_CHK_FAIL(i4_ret);


    /* set body background */
    if( (pt_wgt_param->ui4_style & WGL_STL_GL_NO_IMG_UI) == WGL_STL_GL_NO_IMG_UI)
    {
        _wdk_get_clr_info(&t_color_info, pt_wgt_param->t_body_set.pt_clr_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_COLOR,
            WGL_PACK (WGL_CLR_PG_BODY), /* background color */
            WGL_PACK (& t_color_info));
        WDK_CHK_FAIL(i4_ret);
    }
    else
    {
        _wdk_get_img_info(&t_img_info, pt_wgt_param->t_body_set.pt_img_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_IMAGE,
            WGL_PACK (WGL_IMG_PG_BODY), /* background image */
            WGL_PACK (& t_img_info));
        WDK_CHK_FAIL(i4_ret);
    }

    /* Levels */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_PG_SET_LEVELS,
        WGL_PACK(& pt_wgt_param->t_levels),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    for (i4_idx=0; i4_idx<(INT32)(pt_wgt_param->t_levels.ui1_level_number); i4_idx++)
    {
        if (i4_idx >= WGL_PG_LEVEL_MAX)
        {
            break;
        }

        if( (pt_wgt_param->ui4_style & WGL_STL_GL_NO_IMG_UI) == WGL_STL_GL_NO_IMG_UI)
        {
            _wdk_get_clr_info(&t_color_info, pt_wgt_param->at_level_set[i4_idx].pt_clr_info);

            i4_ret = c_wgl_do_cmd (*ph_widget,
                WGL_CMD_GL_SET_COLOR,
                WGL_PACK (WGL_CLR_PG_LEVEL_1+i4_idx), /* background color */
                WGL_PACK (&t_color_info));
            WDK_CHK_FAIL(i4_ret);
        }
        else
        {
            _wdk_get_img_info(&t_img_info, pt_wgt_param->at_level_set[i4_idx].pt_img_info);

            i4_ret = c_wgl_do_cmd (*ph_widget,
                WGL_CMD_GL_SET_IMAGE,
                WGL_PACK (WGL_IMG_PG_LEVEL_1+i4_idx), /* background image */
                WGL_PACK (&t_img_info));
            WDK_CHK_FAIL(i4_ret);
        }
    }

    /* Set Text Color */
    _wdk_get_clr_info(&t_color_info, pt_wgt_param->pt_clr_text);

    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_GL_SET_COLOR,
        WGL_PACK(WGL_CLR_TEXT),
        WGL_PACK(&t_color_info));
    WDK_CHK_FAIL(i4_ret);

    /* Set Font */
    _wdk_get_fnt_info(&t_fnt_info, pt_wgt_param->pt_fnt);
    c_wgl_do_cmd (*ph_widget,
        WGL_CMD_GL_SET_FONT_EX,
        WGL_PACK(&t_fnt_info),
        NULL);
    /* WDK_CHK_FAIL(i4_ret); */

    /* set visibility */
    WDK_CHK_FAIL (c_wgl_set_visibility (*ph_widget, pt_wgt_param->ui1_visibility));

    return  i4_ret;
}


/*----------------------------------------------------------------------------
* Name: a_wdk_create_eb
*
* Description: This function creates a edit box widget according to the parameters.
*
* Inputs:  -
*
* Outputs: -
*
* Returns: 0                  Successful.
*          Any other values   Failed.
----------------------------------------------------------------------------*/

INT32 a_wdk_create_eb(WDK_EB_WGT_T *pt_wgt_param,
                      UINT32         ui4_opt_mask,
                      HANDLE_T      *ph_widget)
{
    INT32 i4_ret;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_EX_T  t_fnt_info;

    /* create widget */
    i4_ret = c_wgl_create_widget (pt_wgt_param->h_parent,
        HT_WGL_WIDGET_EDIT_BOX,
        WGL_CONTENT_EDIT_BOX_DEF,
        pt_wgt_param->ui4_border,
        &(pt_wgt_param->t_rect),
        pt_wgt_param->pf_wdgt_proc,
        pt_wgt_param->ui1_alpha,
        (VOID*) pt_wgt_param->ui4_style,
        0,
        ph_widget);
    WDK_CHK_FAIL (i4_ret);

    /* set border */
    _wdk_set_border(*ph_widget, pt_wgt_param->ui4_border, pt_wgt_param->pt_border);

    /* set background */
    if( (pt_wgt_param->ui4_style & WGL_STL_GL_NO_IMG_UI) == WGL_STL_GL_NO_IMG_UI)
    {
        _wdk_get_clr_info(&t_color_info, pt_wgt_param->t_bk_set.pt_clr_info);

        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_COLOR,
            WGL_PACK (WGL_CLR_BK), /* background color */
            WGL_PACK (& t_color_info));
        WDK_CHK_FAIL (i4_ret);
    }
    else
    {
        _wdk_get_img_info(&t_img_info, pt_wgt_param->t_bk_set.pt_img_info);
        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_IMAGE,
            WGL_PACK (WGL_IMG_BK), /* background image */
            WGL_PACK (&t_img_info));
        WDK_CHK_FAIL (i4_ret);
    }

    /* Special Part */
    /* Set Content Inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_EB_SET_CNT_INSET,
        WGL_PACK(&pt_wgt_param->t_cnt_inset),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_EB_SET_ALIGN,
        WGL_PACK(pt_wgt_param->ui1_align),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Font */
    _wdk_get_fnt_info(&t_fnt_info, pt_wgt_param->pt_fnt);
    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_GL_SET_FONT_EX,
        WGL_PACK(&t_fnt_info),
        NULL);
    /* WDK_CHK_FAIL(i4_ret); */

    /* Set Text Color */
    _wdk_get_clr_info(&t_color_info, pt_wgt_param->pt_clr_text);

    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_GL_SET_COLOR,
        WGL_PACK(WGL_CLR_TEXT),
        WGL_PACK(&t_color_info));
    WDK_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_EB_SET_INPUT_LIMIT,
        WGL_PACK((UINT16)pt_wgt_param->ui4_input_limit),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_EB_SET_INSERT_MODE,
        WGL_PACK (pt_wgt_param->t_insert_mode),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* set visibility */
    WDK_CHK_FAIL (c_wgl_set_visibility (*ph_widget, WGL_SW_NORMAL));

    return  i4_ret;
}


/*----------------------------------------------------------------------------
* Name: a_wdk_create_lb
*
* Description: This function creates a list box widget according to the parameters.
*
* Inputs:  -
*
* Outputs: -
*
* Returns: 0                  Successful.
*          Any other values   Failed.
----------------------------------------------------------------------------*/

INT32 a_wdk_create_lb(WDK_LB_WGT_T *pt_wgt_param,
                      UINT32         ui4_opt_mask,
                      HANDLE_T      *ph_widget)
{
    INT32               i4_col;
    INT32               i4_elem;
    INT32               i4_idx;
    INT32               i4_ret;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_EX_T  t_fnt_info;
    WGL_LB_INIT_T       t_lb_init = {0};

    WGL_LB_FONT_INFO_EX_T   t_lb_fnt_set;
    WGL_LB_COLOR_ELEM_SET_T t_lb_clr_set;
    WGL_LB_ITEM_IMG_SUIT_T  t_lb_img_set; /* WGL_LB_IMG_ELEM_SET_T; */

    t_lb_init.ui4_style = pt_wgt_param->ui4_style;
    t_lb_init.ui2_max_elem_num = pt_wgt_param->ui2_max_elem_num;
    t_lb_init.ui2_elem_size = pt_wgt_param->ui2_elem_height;
    t_lb_init.ui2_elem_distance = pt_wgt_param->ui2_elem_distance;
    t_lb_init.ui1_col_num = pt_wgt_param->ui1_col_num;
    t_lb_init.at_cols = pt_wgt_param->at_col;

    /* create widget */
    i4_ret = c_wgl_create_widget (pt_wgt_param->h_parent,
        HT_WGL_WIDGET_LIST_BOX,
        WGL_CONTENT_LIST_BOX_DEF,
        pt_wgt_param->ui4_border,
        &(pt_wgt_param->t_rect),
        pt_wgt_param->pf_wdgt_proc,
        pt_wgt_param->ui1_alpha,
        (VOID*) &t_lb_init,
        0,
        ph_widget);
    WDK_CHK_FAIL(i4_ret);

    /* set border */
    _wdk_set_border(*ph_widget, pt_wgt_param->ui4_border, pt_wgt_param->pt_border);

    /* set background */
    if( (pt_wgt_param->ui4_style & WGL_STL_GL_NO_IMG_UI) == WGL_STL_GL_NO_IMG_UI)
    {
        _wdk_get_clr_info(&t_clr_info, pt_wgt_param->t_bk_set.pt_clr_info);
        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_COLOR,
            WGL_PACK (WGL_CLR_BK), /* background color */
            WGL_PACK (& t_clr_info));
        WDK_CHK_FAIL(i4_ret);
    }
    else
    {
        _wdk_get_img_info(&t_img_info, pt_wgt_param->t_bk_set.pt_img_info);
        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_GL_SET_IMAGE,
            WGL_PACK (WGL_IMG_BK), /* background image */
            WGL_PACK (& t_img_info));
        WDK_CHK_FAIL(i4_ret);
    }

    /* Special Part */
    /* Set Content Inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_LB_SET_CNT_INSET,
        WGL_PACK(&pt_wgt_param->t_cnt_inset),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Element Inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
        WGL_CMD_LB_SET_ELEM_INSET,
        WGL_PACK(&pt_wgt_param->t_elem_inset),
        NULL);
    WDK_CHK_FAIL(i4_ret);


    /* Set Element Background Color */
    _wdk_get_lb_clr_set(&t_lb_clr_set, pt_wgt_param->t_elem_bk_set.pt_clr_set);
    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_ELEM_COLOR,
        WGL_PACK (WGL_CLR_BK),
        WGL_PACK (& t_lb_clr_set));
    WDK_CHK_FAIL(i4_ret);

    /* Set Element Background Image */
    _wdk_get_lb_img_set(&t_lb_img_set, pt_wgt_param->t_elem_bk_set.pt_img_set);
    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
        WGL_PACK (& t_lb_img_set),
        NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Column Inset/Background Color/Text Color */
    for (i4_col = 0; i4_col < (INT32)(pt_wgt_param->ui1_col_num); i4_col++)
    {
        /* Inset */
        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_LB_SET_COL_INSET,
            WGL_PACK (i4_col),
            WGL_PACK (& pt_wgt_param->at_col_inset[i4_col]));
        WDK_CHK_FAIL (i4_ret);

        if (LB_COL_TYPE_TEXT == pt_wgt_param->at_col[i4_col].e_col_type)
        {
            /* FontEx*/
            _wdk_get_lb_font_set(&t_lb_fnt_set, &(pt_wgt_param->at_col_font_ex[i4_col]));
            i4_ret = c_wgl_do_cmd (*ph_widget,
                WGL_CMD_LB_SET_COL_FONT_EX,
                WGL_PACK(i4_col),
                WGL_PACK (&t_lb_fnt_set));
            /* WDK_CHK_FAIL(i4_ret); */

            /* Text Color */
            _wdk_get_lb_clr_set(&t_lb_clr_set, &(pt_wgt_param->at_col_txt_clr[i4_col]));
            i4_ret = c_wgl_do_cmd (*ph_widget,
                WGL_CMD_LB_SET_COL_COLOR,
                WGL_PACK_2 (i4_col, WGL_CLR_TEXT),
                WGL_PACK (& t_lb_clr_set));
            WDK_CHK_FAIL (i4_ret);
        }

        /* Background Color */
        _wdk_get_lb_clr_set(&t_lb_clr_set, &(pt_wgt_param->at_col_bk_clr[i4_col]));
        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_LB_SET_COL_COLOR,
            WGL_PACK_2 (i4_col, WGL_CLR_BK),
            WGL_PACK (& t_lb_clr_set));
        WDK_CHK_FAIL (i4_ret);
    }

    /* set element enum*/
    if(!(t_lb_init.ui4_style & WGL_STL_LB_FIXED_ELEM_NUM))
    {
        i4_ret = c_wgl_do_cmd (*ph_widget,
            WGL_CMD_LB_SET_ELEM_NUM,
            WGL_PACK (0),
            NULL);
        WDK_CHK_FAIL(i4_ret);

        pt_wgt_param->ui2_elem_num = 0;
    }

    /* Set Items */
    for (i4_col = 0; i4_col < (INT32)(pt_wgt_param->ui1_col_num); i4_col++)
    {
        for (i4_elem = 0; i4_elem < (INT32)(pt_wgt_param->ui2_elem_num); i4_elem++)
        {
            i4_idx = (pt_wgt_param->ui1_col_num) * i4_elem + i4_col;

            if (!(pt_wgt_param->at_items[i4_idx].ui1_flag))
            {
                /* Set Align */
                i4_ret = c_wgl_do_cmd (*ph_widget,
                    WGL_CMD_LB_SET_ITEM_ALIGN,
                    WGL_PACK_2 (i4_elem, i4_col),
                    WGL_PACK (pt_wgt_param->at_items[i4_idx].ui1_align));
                WDK_CHK_FAIL (i4_ret);

                /* Set Background Color */
                _wdk_get_lb_clr_set(&t_lb_clr_set, &(pt_wgt_param->at_bk_clr[i4_idx]));
                i4_ret = c_wgl_do_cmd (*ph_widget,
                    WGL_CMD_LB_SET_ITEM_COLOR,
                    WGL_PACK_3 (i4_elem, i4_col, WGL_CLR_BK),
                    WGL_PACK (& t_lb_clr_set));
                WDK_CHK_FAIL (i4_ret);
            }

            switch (pt_wgt_param->at_items[i4_idx].e_col_type)
            {
            case LB_COL_TYPE_TEXT:
                /* LEM@TODO  set text string & color */
                break;



            case LB_COL_TYPE_IMG:
            {
                if(NULL != pt_wgt_param->at_items[i4_idx].h_img)
                {
                    i4_ret = c_wgl_do_cmd (*ph_widget,
                                            WGL_CMD_LB_SET_ITEM_IMAGE,
                                            WGL_PACK_2 (i4_elem, i4_col),
                                            WGL_PACK (*(pt_wgt_param->at_items[i4_idx].h_img)));
                }
                else
                {
                    i4_ret = c_wgl_do_cmd (*ph_widget,
                                            WGL_CMD_LB_SET_ITEM_IMAGE,
                                            WGL_PACK_2 (i4_elem, i4_col),
                                            WGL_PACK (NULL));
                }
                WDK_CHK_FAIL (i4_ret);
            }
            break;

            case LB_COL_TYPE_IMG_SUIT:
            {
                _wdk_get_lb_img_set(&t_lb_img_set, &(pt_wgt_param->at_img_set[i4_idx]));
                i4_ret = c_wgl_do_cmd (*ph_widget,
                                        WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
                                        WGL_PACK_2 (i4_elem, i4_col),
                                        WGL_PACK (& t_lb_img_set));
                                        WDK_CHK_FAIL (i4_ret);
            }
            break;

            default:
                break;
            }
        }
    }

    /* Set Highlight Effect */
    /* LEM@TODO */

    /* Set Font */
    _wdk_get_fnt_info(&t_fnt_info, pt_wgt_param->pt_fnt);
    c_wgl_do_cmd (*ph_widget,
        WGL_CMD_GL_SET_FONT_EX,
        WGL_PACK(&t_fnt_info),
        NULL);
    /* WDK_CHK_FAIL(i4_ret); */

    /* set visibility */
    WDK_CHK_FAIL (c_wgl_set_visibility (*ph_widget, WGL_SW_NORMAL));

    return  i4_ret;
}


/*----------------------------------------------------------------------------
* Name: a_wdk_create_widgets
*
* Description: This function creates widgets according to the parameters.
*
* Inputs:  -
*
* Outputs: -
*
* Returns: 0                  Successful.
*          Any other values   Failed.
----------------------------------------------------------------------------*/
INT32 a_wdk_create_widgets(HANDLE_T h_container, WDK_ITEM_LIST_T *pt_wdk_list,
                           HANDLE_T *ph_handle, wgl_widget_proc_fct *pf_cb)
{
    INT32 i;
    INT32 i4_ret = WDKR_FAILED;
    WDK_ITEM_LIST_T *p_child;
    VOID *pv_param;
    UINT32 ui4_opt_mask;
    UINT16 u2_id;
    #define  WDK_CHK    1
    for (i=0; i<(INT32)(pt_wdk_list->ui4_num); i++)
    {
        pv_param = pt_wdk_list->p_item_list[i].p_param;
        ui4_opt_mask = pt_wdk_list->p_item_list[i].ui4_opt_mask;
        u2_id = pt_wdk_list->p_item_list[i].u2_id;

        switch (pt_wdk_list->p_item_list[i].e_type)
        {
        case HT_WGL_WIDGET_FRAME:
#if    WDK_CHK
            ((WDK_FRM_WGT_T *)pv_param)->h_parent = h_container;
            if (NULL != pf_cb)
            {
                ((WDK_FRM_WGT_T *)pv_param)->pf_wdgt_proc = pf_cb[u2_id];
            }
#endif
            i4_ret = a_wdk_create_frame((WDK_FRM_WGT_T *)pv_param,
                ui4_opt_mask,
                &(ph_handle[u2_id]));

            if (pt_wdk_list->p_item_list[i].p_child != NULL)
            {
                p_child = pt_wdk_list->p_item_list[i].p_child;
                i4_ret = a_wdk_create_widgets((ph_handle[u2_id]),
                    p_child,
                    ph_handle,
                    pf_cb);
            }
            break;

        case HT_WGL_WIDGET_ICON:
#if WDK_CHK
            ((WDK_ICON_WGT_T *)pv_param)->h_parent = h_container;
            if (NULL != pf_cb)
            {
                ((WDK_ICON_WGT_T *)pv_param)->pf_wdgt_proc = pf_cb[u2_id];
            }
#endif
            i4_ret = a_wdk_create_icon((WDK_ICON_WGT_T *)pv_param,
                ui4_opt_mask,
                &(ph_handle[u2_id]));
            break;

        case HT_WGL_WIDGET_TEXT:
#if WDK_CHK
            ((WDK_TXT_WGT_T *)pv_param)->h_parent = h_container;
            if (NULL != pf_cb)
            {
                ((WDK_TXT_WGT_T *)pv_param)->pf_wdgt_proc = pf_cb[u2_id];
            }
#endif
            i4_ret = a_wdk_create_text((WDK_TXT_WGT_T *)pv_param,
                ui4_opt_mask,
                &(ph_handle[u2_id]));
            break;

        case HT_WGL_WIDGET_BUTTON:
#if WDK_CHK
            ((WDK_BTN_WGT_T *)pv_param)->h_parent = h_container;
            if (NULL != pf_cb)
            {
                ((WDK_BTN_WGT_T *)pv_param)->pf_wdgt_proc = pf_cb[u2_id];
            }
#endif
            i4_ret = a_wdk_create_button((WDK_BTN_WGT_T *)pv_param,
                ui4_opt_mask,
                &(ph_handle[u2_id]));
            break;

        case HT_WGL_WIDGET_PROGRESS_BAR:
#if WDK_CHK
            ((WDK_PB_WGT_T *)pv_param)->h_parent = h_container;
            if (NULL != pf_cb)
            {
                ((WDK_PB_WGT_T *)pv_param)->pf_wdgt_proc = pf_cb[u2_id];
            }
#endif
            i4_ret = a_wdk_create_pb((WDK_PB_WGT_T *)pv_param,
                ui4_opt_mask,
                &(ph_handle[u2_id]));
            break;

        case HT_WGL_WIDGET_EDIT_BOX:
#if WDK_CHK
            ((WDK_EB_WGT_T *)pv_param)->h_parent = h_container;
            if (NULL != pf_cb)
            {
                ((WDK_EB_WGT_T *)pv_param)->pf_wdgt_proc = pf_cb[u2_id];
            }
#endif
            i4_ret = a_wdk_create_eb((WDK_EB_WGT_T *)pv_param,
                ui4_opt_mask,
                &(ph_handle[u2_id]));
            break;

        case HT_WGL_WIDGET_LIST_BOX:
#if WDK_CHK
            ((WDK_LB_WGT_T *)pv_param)->h_parent = h_container;
            if (NULL != pf_cb)
            {
                ((WDK_LB_WGT_T *)pv_param)->pf_wdgt_proc = pf_cb[u2_id];
            }
#endif
            i4_ret = a_wdk_create_lb((WDK_LB_WGT_T *)pv_param,
                ui4_opt_mask,
                &(ph_handle[u2_id]));
            break;

        case HT_WGL_WIDGET_ANIM:
            /* TODO */
        default:
            break;
        }
    }

    return i4_ret;
}


/*----------------------------------------------------------------------------
* Name: a_wdk_destory_widgets
*
* Description: This function creates widgets according to the parameters.
*
* Inputs:  -
*
* Outputs: -
*
* Returns: 0                  Successful.
*          Any other values   Failed.
----------------------------------------------------------------------------*/
INT32 a_wdk_destory_widgets(WDK_ITEM_LIST_T *pt_wdk_list,
                            HANDLE_T *ph_handle)
{
    INT32 i;
    INT32 i4_ret;
    UINT16 u2_id;

    for (i=0; i<(INT32)(pt_wdk_list->ui4_num); i++)
    {
        u2_id = pt_wdk_list->p_item_list[i].u2_id;

        i4_ret = c_wgl_destroy_widget_ex(ph_handle[u2_id], TRUE);
        if (WGLR_OK != i4_ret)
        {
            return (WDKR_FAILED);
        }
    }

    return (WDKR_OK);
}


/*----------------------------------------------------------------------------
* Name: a_wdk_widgets_update_text
*
* Description: This function update the text of widgets according to the parameters.
*
* Inputs:  -
*
* Outputs: -
*
* Returns: 0                  Successful.
*          Any other values   Failed.
----------------------------------------------------------------------------*/
INT32 a_wdk_widgets_update_text(WDK_ITEM_LIST_T *pt_wdk_list,
                                HANDLE_T *ph_handle,
                                wdk_mlm_get_text pf_get_text,
                                UINT16 ui2_lang)
{
    INT32 i;
    INT32 i4_ret = WDKR_FAILED;
    WDK_ITEM_LIST_T *p_child;
    VOID *pv_param;
    UINT16 u2_id;
    UINT16 ui2_msg_id;

    for (i=0; i<(INT32)(pt_wdk_list->ui4_num); i++)
    {
        pv_param = pt_wdk_list->p_item_list[i].p_param;
        u2_id = pt_wdk_list->p_item_list[i].u2_id;

        switch (pt_wdk_list->p_item_list[i].e_type)
        {
        case HT_WGL_WIDGET_FRAME:

            if (pt_wdk_list->p_item_list[i].p_child != NULL)
            {
                p_child = pt_wdk_list->p_item_list[i].p_child;
                i4_ret = a_wdk_widgets_update_text(p_child,
                                                   ph_handle,
                                                   pf_get_text,
                                                   ui2_lang);
            }
            break;

        case HT_WGL_WIDGET_ICON:
            break;

        case HT_WGL_WIDGET_TEXT:
            ui2_msg_id = ((WDK_TXT_WGT_T *)pv_param)->ui2_text_id;

            i4_ret = c_wgl_do_cmd(ph_handle[u2_id],
                                 WGL_CMD_TEXT_SET_TEXT,
                                 WGL_PACK(pf_get_text(ui2_lang, ui2_msg_id)),
                                 WGL_PACK((UINT16)c_uc_w2s_strlen(pf_get_text(ui2_lang, ui2_msg_id))));
            break;

        case HT_WGL_WIDGET_BUTTON:
            ui2_msg_id = ((WDK_BTN_WGT_T *)pv_param)->ui2_text_id;

            i4_ret = c_wgl_do_cmd(ph_handle[u2_id],
                                  WGL_CMD_BTN_SET_TEXT,
                                  WGL_PACK(pf_get_text(ui2_lang, ui2_msg_id)),
                                  WGL_PACK((UINT16)c_uc_w2s_strlen(pf_get_text(ui2_lang, ui2_msg_id))));
            break;

        case HT_WGL_WIDGET_PROGRESS_BAR:
            break;

        case HT_WGL_WIDGET_EDIT_BOX:
            break;

        case HT_WGL_WIDGET_LIST_BOX:
            break;

        case HT_WGL_WIDGET_ANIM:
            /* TODO */
        default:
            break;
        }
    }

    return i4_ret;
}


/*----------------------------------------------------------------------------
* Name: a_wdk_widgets_get_param
*
* Description: This function return the param of widget according to the widget id.
*
* Inputs:  -
*
* Outputs: -
*
* Returns: 0                  Successful.
*          Any other values   Failed.
----------------------------------------------------------------------------*/
extern INT32 a_wdk_widgets_get_param(WDK_ITEM_LIST_T *pt_wdk_list,
                                     UINT16 ui2_wgt_id,
                                     WDK_WGT_T **ppt_wgt_param)
{
    INT32 i;
    INT32 i4_ret = WDKR_FAILED;
    WDK_ITEM_LIST_T *p_child;
    VOID *pv_param;
    UINT16 u2_id;

    for (i=0; i<(INT32)(pt_wdk_list->ui4_num); i++)
    {
        pv_param = pt_wdk_list->p_item_list[i].p_param;
        u2_id = pt_wdk_list->p_item_list[i].u2_id;

        if (u2_id == ui2_wgt_id)
        {
            *ppt_wgt_param = (WDK_WGT_T *)pv_param;
            return (WDKR_OK);
        }

        switch (pt_wdk_list->p_item_list[i].e_type)
        {
        case HT_WGL_WIDGET_FRAME:

            if (pt_wdk_list->p_item_list[i].p_child != NULL)
            {
                p_child = pt_wdk_list->p_item_list[i].p_child;
                i4_ret = a_wdk_widgets_get_param(p_child,
                                                 ui2_wgt_id,
                                                 ppt_wgt_param);

                if (WDKR_OK == i4_ret)
                {
                    return (WDKR_OK);
                }
            }
            break;

        default:
            break;
        }
    }

    return i4_ret;
}
