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
 * $RCSfile: wdk_wgl_util.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_sets.h"

#include "c_handle.h"
#include "c_gl.h"
#include "c_wgl.h"
#include "c_wgl_image.h"

#include "app_util/a_common.h"
#include "app_util/a_lbw.h"

#include "wdk/a_wdk.h"
#include "wdk/util/wdk_wgl_util.h"

/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/

#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    private function implementations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    public function implementations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    export function implementations
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_create_frm_widget (WDK_FRM_WIDGET_PARAM_T t_frm_param)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      t_frm_param.i4_x,
                      t_frm_param.i4_y,
                      t_frm_param.i4_w,
                      t_frm_param.i4_h);

    /* create widget */
    WDK_CHK_FAIL (c_wgl_create_widget (t_frm_param.h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     t_frm_param.pf_wdgt_proc,
                                     t_frm_param.ui1_alpha,
                                     (VOID*) t_frm_param.ui4_style,
                                     0,
                                     t_frm_param.ph_created_frm));

    /* set theme */
    if( (t_frm_param.ui4_style & WGL_STL_GL_NO_IMG_UI) == WGL_STL_GL_NO_IMG_UI ||
        t_frm_param.t_img_bk.h_enable == NULL_HANDLE )
    {
        t_color_info.e_type = WGL_COLOR_SET_STANDARD;
        if (NULL != t_frm_param.pt_clr_bk)
        {
            COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    t_frm_param.pt_clr_bk);
            COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   t_frm_param.pt_clr_bk);
            COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, t_frm_param.pt_clr_bk);
        }

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_frm_param.ph_created_frm,
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK (WGL_CLR_BK), /* background color */
                                  WGL_PACK (& t_color_info)));
    }
    else
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = t_frm_param.t_img_bk.h_enable;
        t_img_info.u_img_data.t_standard.t_disable   = t_frm_param.t_img_bk.h_disable;
        t_img_info.u_img_data.t_standard.t_highlight = t_frm_param.t_img_bk.h_highlight;

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_frm_param.ph_created_frm,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK (WGL_IMG_BK), /* background image */
                                  WGL_PACK (& t_img_info)));
    }

    /* set visibility */
    if (t_frm_param.b_visibility)
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_frm_param.ph_created_frm, WGL_SW_NORMAL));
    }
    else
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_frm_param.ph_created_frm, WGL_SW_HIDE));
    }

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: mus_view_create_txt_widget
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
INT32 a_wdk_create_txt_widget (WDK_TXT_WIDGET_PARAM_T t_txt_param)
{
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;
    WGL_COLOR_INFO_T            t_color_info;

    SET_RECT_BY_SIZE (& t_rect,
                      t_txt_param.i4_x,
                      t_txt_param.i4_y,
                      t_txt_param.i4_w,
                      t_txt_param.i4_h);

    /* create widget */
    WDK_CHK_FAIL (c_wgl_create_widget (t_txt_param.h_parent,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     t_txt_param.pf_wdgt_proc,
                                     t_txt_param.ui1_alpha,
                                     (VOID*)(t_txt_param.ui4_style),
                                     NULL,
                                     t_txt_param.ph_created_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));

    if (t_txt_param.ps_font_name)
    {
        c_strcpy (t_fnt_info.a_c_font_name, t_txt_param.ps_font_name);
    }
    else
    {
        c_strcpy (t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    }
    t_fnt_info.e_font_size  = t_txt_param.e_font_size;
    t_fnt_info.e_font_style = t_txt_param.e_font_style;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = t_txt_param.ui1_font_custom_size;

    WDK_CHK_FAIL (c_wgl_do_cmd (*t_txt_param.ph_created_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    WDK_CHK_FAIL (c_wgl_do_cmd (*t_txt_param.ph_created_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_txt_param.t_inset),
                              NULL));

    /* set alignment */
    WDK_CHK_FAIL (c_wgl_do_cmd (*t_txt_param.ph_created_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (t_txt_param.ui1_align),
                              NULL));

    /* set theme */
    if (t_txt_param.b_img_bk == TRUE)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = t_txt_param.t_img_bk.h_enable;
        t_img_info.u_img_data.t_standard.t_disable   = t_txt_param.t_img_bk.h_disable;
        t_img_info.u_img_data.t_standard.t_highlight = t_txt_param.t_img_bk.h_highlight;

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_txt_param.ph_created_txt,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK (WGL_IMG_BK), /* background image */
                                  WGL_PACK (& t_img_info)));
    }
    else
    {
        t_color_info.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    t_txt_param.pt_clr_bk);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   t_txt_param.pt_clr_bk);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, t_txt_param.pt_clr_bk);

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_txt_param.ph_created_txt,
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK (WGL_CLR_BK), /* background color */
                                  WGL_PACK (& t_color_info)));
    }

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    t_txt_param.pt_clr_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   t_txt_param.pt_dis_clr_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, t_txt_param.pt_hlt_clr_txt);

    WDK_CHK_FAIL (c_wgl_do_cmd (*t_txt_param.ph_created_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    if (t_txt_param.b_visibility)
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_txt_param.ph_created_txt, WGL_SW_NORMAL));
    }
    else
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_txt_param.ph_created_txt, WGL_SW_HIDE));
    }

    return  0;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_create_icon_widget (WDK_ICON_WIDGET_PARAM_T t_icon_param)
{
    WGL_COLOR_INFO_T            t_color_info;
    WGL_IMG_INFO_T              t_img_info;
    GL_RECT_T                   t_rect;

    SET_RECT_BY_SIZE (& t_rect,
                      t_icon_param.i4_x,
                      t_icon_param.i4_y,
                      t_icon_param.i4_w,
                      t_icon_param.i4_h);

    /* create widget */
    WDK_CHK_FAIL (c_wgl_create_widget (t_icon_param.h_parent,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     t_icon_param.pf_wdgt_proc,
                                     t_icon_param.ui1_alpha,
                                     (VOID*)(t_icon_param.ui4_style),
                                     NULL,
                                     t_icon_param.ph_created_icon));

    if (t_icon_param.ui4_style & WGL_STL_GL_NO_IMG_UI)
    {
        t_color_info.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    t_icon_param.pt_clr_bk);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   t_icon_param.pt_clr_bk);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, t_icon_param.pt_clr_bk);

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_icon_param.ph_created_icon,
                                    WGL_CMD_GL_SET_COLOR,
                                    WGL_PACK (WGL_CLR_BK), /* background color */
                                    WGL_PACK (& t_color_info)));
    }
    else
    {
        /* set icon image buffer */
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = t_icon_param.t_img_param.h_enable;
        t_img_info.u_img_data.t_standard.t_disable   = t_icon_param.t_img_param.h_disable;
        t_img_info.u_img_data.t_standard.t_highlight = t_icon_param.t_img_param.h_highlight;

        if( t_icon_param.b_img_bk == TRUE )
        {
            WDK_CHK_FAIL (c_wgl_do_cmd (*t_icon_param.ph_created_icon,
                                        WGL_CMD_GL_SET_IMAGE,
                                        WGL_PACK (WGL_IMG_BK),
                                        WGL_PACK(&t_img_info)));
        }
        else
        {
            WDK_CHK_FAIL (c_wgl_do_cmd (*t_icon_param.ph_created_icon,
                                        WGL_CMD_GL_SET_IMAGE,
                                        WGL_PACK (WGL_IMG_FG),  /* foreground image */
                                        WGL_PACK(&t_img_info)));
        }

        /* set icon alignment */
        WDK_CHK_FAIL (c_wgl_do_cmd (*t_icon_param.ph_created_icon,
                                    WGL_CMD_ICON_SET_ALIGN,
                                    WGL_PACK (t_icon_param.ui1_img_align_style),
                                    NULL));

    }

    /* set visibility */
    if (t_icon_param.b_visibility)
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_icon_param.ph_created_icon, WGL_SW_NORMAL));
    }
    else
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_icon_param.ph_created_icon, WGL_SW_HIDE));
    }


    return 0;
}


/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_create_anim_widget (WDK_ANIM_WIDGET_PARAM_T t_anim_param)
{
    WGL_IMG_INFO_T              t_img_info;
    GL_RECT_T                   t_rect;

    SET_RECT_BY_SIZE (& t_rect,
                      t_anim_param.i4_x,
                      t_anim_param.i4_y,
                      t_anim_param.i4_w,
                      t_anim_param.i4_h);

    /* create widget */
    WDK_CHK_FAIL (c_wgl_create_widget (t_anim_param.h_parent,
                                     HT_WGL_WIDGET_ANIM,
                                     WGL_CONTENT_ANIM_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     t_anim_param.pf_wdgt_proc,
                                     t_anim_param.ui1_alpha,
                                     (VOID*)& t_anim_param.t_anim_init,
                                     NULL,
                                     t_anim_param.ph_created_anim));

    if (t_anim_param.t_anim_init.ui4_style & WGL_STL_GL_NO_IMG_UI)
    {
        return WDKR_INV_ARG;
    }
    else
    {
        /* set icon image buffer */
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = t_anim_param.t_img_param.h_enable;
        t_img_info.u_img_data.t_standard.t_disable   = t_anim_param.t_img_param.h_disable;
        t_img_info.u_img_data.t_standard.t_highlight = t_anim_param.t_img_param.h_highlight;

        if( t_anim_param.b_img_bk == TRUE )
        {
            WDK_CHK_FAIL (c_wgl_do_cmd (*t_anim_param.ph_created_anim,
                                        WGL_CMD_GL_SET_IMAGE,
                                        WGL_PACK (WGL_IMG_BK),
                                        WGL_PACK(&t_img_info)));
        }
        else
        {
            WDK_CHK_FAIL (c_wgl_do_cmd (*t_anim_param.ph_created_anim,
                                        WGL_CMD_GL_SET_IMAGE,
                                        WGL_PACK (WGL_IMG_FG),  /* foreground image */
                                        WGL_PACK(&t_img_info)));
        }

        /* set icon alignment */
        WDK_CHK_FAIL (c_wgl_do_cmd (*t_anim_param.ph_created_anim,
                                    WGL_CMD_ANIM_SET_ALIGN,
                                    WGL_PACK (t_anim_param.ui1_img_align_style),
                                    NULL));

    }

    /* condition callback */
    if (t_anim_param.t_cond_cb.pf_anim_callback != NULL)
    {
        WDK_CHK_FAIL (c_wgl_do_cmd (*t_anim_param.ph_created_anim,
                               WGL_CMD_ANIM_SET_COND_CB,
                               WGL_PACK (& t_anim_param.t_cond_cb),
                               NULL));
    }

    /* set visibility */
    if (t_anim_param.b_visibility)
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_anim_param.ph_created_anim, WGL_SW_NORMAL));
    }
    else
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_anim_param.ph_created_anim, WGL_SW_HIDE));
    }

    return 0;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_create_lb_widget   (WDK_LB_WIDGET_PARAM_T t_lb_param)
{
    WGL_LB_INIT_T               t_lb_init = {0};
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_FONT_INFO_T             t_hlt_fnt_info;
    WGL_LB_FONT_INFO_EX_T       t_lb_fnt_info_ex;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    UINT8                       ui1_column_index;
    WGL_IMG_INFO_T              t_img_info;
    WGL_LB_SCRL_BAR_T           t_scrl_bar;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;

    t_lb_init.ui4_style          = t_lb_param.ui4_style;

    t_lb_init.ui2_max_elem_num   = t_lb_param.ui2_max_elem_num;
    t_lb_init.ui2_elem_size      = t_lb_param.ui2_elem_size;
    t_lb_init.ui2_elem_distance  = t_lb_param.ui2_elem_distance;
    t_lb_init.ui1_col_num        = t_lb_param.ui1_col_num;
    t_lb_init.at_cols            = t_lb_param.at_cols;

    SET_RECT_BY_SIZE (& t_rect,
                      t_lb_param.i4_x,
                      t_lb_param.i4_y,
                      t_lb_param.i4_w,
                      t_lb_param.i4_h);

    /* create widget */
    WDK_CHK_FAIL (c_wgl_create_widget (t_lb_param.h_parent,
                                     HT_WGL_WIDGET_LIST_BOX,
                                     WGL_CONTENT_LIST_BOX_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     t_lb_param.pf_wdgt_proc,
                                     t_lb_param.ui1_alpha,
                                     & t_lb_init,
                                     NULL,
                                     t_lb_param.ph_created_lb));

    /* set font size */
    {
        c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));

        if (t_lb_param.ps_font_name)
        {
            c_strcpy (t_fnt_info.a_c_font_name, t_lb_param.ps_font_name);
        }
        else
        {
            c_strcpy (t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
        }

        t_fnt_info.e_font_size  = t_lb_param.e_font_size;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        c_memset (& t_hlt_fnt_info, 0, sizeof (WGL_FONT_INFO_T));

        if (t_lb_param.ps_font_name_hlt)
        {
            c_strcpy (t_hlt_fnt_info.a_c_font_name, t_lb_param.ps_font_name_hlt);
        }
        else
        {
            c_strcpy (t_hlt_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
        }

        t_hlt_fnt_info.e_font_size  = t_lb_param.e_font_size;
        t_hlt_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_hlt_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        c_memcpy(&t_lb_fnt_info_ex.t_normal,              & t_fnt_info,     sizeof(WGL_FONT_INFO_T));
        c_memcpy(&t_lb_fnt_info_ex.t_highlight,           & t_hlt_fnt_info, sizeof(WGL_FONT_INFO_T));
        c_memcpy(&t_lb_fnt_info_ex.t_highlight_unfocused, & t_fnt_info,     sizeof(WGL_FONT_INFO_T));
        c_memcpy(&t_lb_fnt_info_ex.t_selected,            & t_fnt_info,     sizeof(WGL_FONT_INFO_T));

        for( ui1_column_index = 0;
             ui1_column_index < t_lb_param.ui1_col_num;
             ui1_column_index++ )
        {
            if (ui1_column_index >= 3)
            {
                continue;
            }
            if(t_lb_param.at_cols[ui1_column_index].e_col_type != LB_COL_TYPE_TEXT)
            {
                continue;
            }

            WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                        WGL_CMD_LB_SET_COL_FONT_EX,
                                        WGL_PACK (ui1_column_index),
                                        WGL_PACK (& t_lb_fnt_info_ex)));
        }
    }

    /* set content inset */
    WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                              WGL_CMD_LB_SET_CNT_INSET,
                              WGL_PACK (& t_lb_param.t_cnt_inset),
                              NULL));

    /* set element inset */
    c_memset (& t_inset, 0, sizeof (WGL_INSET_T));

    WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                              WGL_CMD_LB_SET_ELEM_INSET,
                              WGL_PACK (& t_lb_param.t_elem_inset),
                              NULL));

    /* set highlighted element effect inset */
    c_memset (& t_hlt_elem_effect, 0, sizeof (WGL_LB_HLT_ELEM_EFFECT_T));

    if (t_lb_param.ui2_hef_up_shadow > 0 || t_lb_param.ui2_hef_down_shadow > 0)
    {
        t_hlt_elem_effect.ui4_style              = WGL_LB_HEF_STL_ENLARGE_SIZE;
        t_hlt_elem_effect.t_ex_margin.ui2_top    = t_lb_param.ui2_hef_up_shadow;
        t_hlt_elem_effect.t_ex_margin.ui2_bottom = t_lb_param.ui2_hef_down_shadow;
    }

    /* set text scrolling styles */
    if (t_lb_param.b_scroll_effect)
    {
        t_hlt_elem_effect.ui4_style                  |= WGL_LB_HEF_STL_SCRL_LONG_TEXT;
        t_hlt_elem_effect.t_text_scrl.ui4_style       = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR;

        if (t_lb_param.b_scroll_when_unfocus)
        {
            t_hlt_elem_effect.t_text_scrl.ui4_style  |= WGL_LB_TEXT_SCRL_STL_FORCE_SCRL_UNFOCUS;
        }

        t_hlt_elem_effect.t_text_scrl.ui4_scrl_count  = 1;
        t_hlt_elem_effect.t_text_scrl.ui4_ms_delay    = 180;

        if (t_lb_param.b_async_scrolling)
        {
            t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;
        }
        else
        {
            t_hlt_elem_effect.t_text_scrl.b_sync         = TRUE;
        }
    }

    WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                              WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                              WGL_PACK (& t_hlt_elem_effect),
                              NULL));

    /* set column inset */
    for( ui1_column_index = 0;
         ui1_column_index < t_lb_param.ui1_col_num;
         ui1_column_index++ )
    {
        if (ui1_column_index >= 3)
        {
            continue;
        }
        WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                  WGL_CMD_LB_SET_COL_INSET,
                                  WGL_PACK (ui1_column_index),
                                  WGL_PACK (& t_lb_param.at_col_inset[ui1_column_index])));
    }

    /* set element number */
    WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                              WGL_CMD_LB_SET_ELEM_NUM,
                              WGL_PACK (t_lb_param.ui2_max_elem_num),
                              NULL));

    /* set the scroll bar */
    if (t_lb_param.b_scrl_bar)
    {
        c_memset (& t_scrl_bar, 0, sizeof (WGL_LB_SCRL_BAR_T));

        /* X, Y, W, H */
        SET_RECT_BY_SIZE (& t_scrl_bar.t_rc_body,
                          t_lb_param.i4_scrl_bar_x,
                          t_lb_param.i4_scrl_bar_y,
                          t_lb_param.i4_scrl_bar_w,
                          t_lb_param.i4_scrl_bar_h);

        t_scrl_bar.ui4_sz_thumb_min = t_lb_param.ui4_sz_thumb_min;

        t_scrl_bar.t_imgs_body.t_enable     = t_lb_param.h_scrollbar_bk;
        t_scrl_bar.t_imgs_body.t_disable    = t_lb_param.h_scrollbar_bk;
        t_scrl_bar.t_imgs_body.t_highlight  = t_lb_param.h_scrollbar_bk;

        t_scrl_bar.t_imgs_thumb.t_enable    = t_lb_param.h_scrollbar_pt;
        t_scrl_bar.t_imgs_thumb.t_disable   = t_lb_param.h_scrollbar_pt;
        t_scrl_bar.t_imgs_thumb.t_highlight = t_lb_param.h_scrollbar_pt;

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                  WGL_CMD_LB_EXT_SET_SCRL_BAR,
                                  WGL_PACK (& t_scrl_bar),
                                  NULL));
    }

    /* set the scroll hlt margin */
    if (t_lb_param.ui2_hlt_margin > 0)
    {
        WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                  WGL_CMD_LB_SET_HLT_MARGIN,
                                  WGL_PACK (t_lb_param.ui2_hlt_margin),
                                  NULL));
    }

    /* Widget level */
    if (t_lb_param.b_img_bk == FALSE)
    {
        /* set theme */
        t_color_info.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    t_lb_param.t_clr_bk.pt_enable);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   t_lb_param.t_clr_bk.pt_disable);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, t_lb_param.t_clr_bk.pt_highlight);

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK (WGL_CLR_BK), /* background color */
                                  WGL_PACK (& t_color_info)));
    }
    else
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = t_lb_param.t_img_bk.h_enable;
        t_img_info.u_img_data.t_standard.t_disable   = t_lb_param.t_img_bk.h_disable;
        t_img_info.u_img_data.t_standard.t_highlight = t_lb_param.t_img_bk.h_highlight;

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK (WGL_IMG_BK), /* background image */
                                  WGL_PACK (& t_img_info)));
    }

    /* View port */

    if (t_lb_param.b_vp_img_bk == FALSE)
    {
        /* set theme */
        t_color_info.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    t_lb_param.t_vp_clr_bk.pt_enable);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   t_lb_param.t_vp_clr_bk.pt_disable);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, t_lb_param.t_vp_clr_bk.pt_highlight);

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK (WGL_CLR_LB_VP_BK), /* background color */
                                  WGL_PACK (& t_color_info)));
    }
    else
    {
        /* set theme */
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = t_lb_param.t_vp_img_bk.h_enable;
        t_img_info.u_img_data.t_standard.t_disable   = t_lb_param.t_vp_img_bk.h_disable;
        t_img_info.u_img_data.t_standard.t_highlight = t_lb_param.t_vp_img_bk.h_highlight;

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK (WGL_IMG_LB_VP_BK), /* background color */
                                  WGL_PACK (& t_img_info)));
    }

    /* element layer */
    if( t_lb_param.b_elem_img_bk == FALSE )
    {
        /* transparent element background color */
        COLOR_COPY (& t_color_elem.t_normal,            t_lb_param.t_elem_clr_bk.pt_normal);
        COLOR_COPY (& t_color_elem.t_disable,           t_lb_param.t_elem_clr_bk.pt_disable);
        COLOR_COPY (& t_color_elem.t_highlight,         t_lb_param.t_elem_clr_bk.pt_highlight);
        COLOR_COPY (& t_color_elem.t_highlight_unfocus, t_lb_param.t_elem_clr_bk.pt_highlight_unfocus);
        COLOR_COPY (& t_color_elem.t_pushed,            t_lb_param.t_elem_clr_bk.pt_normal);
        COLOR_COPY (& t_color_elem.t_selected,          t_lb_param.t_elem_clr_bk.pt_selected);
        COLOR_COPY (& t_color_elem.t_selected_disable,  t_lb_param.t_elem_clr_bk.pt_selected);

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                  WGL_CMD_LB_SET_ELEM_COLOR,
                                  WGL_PACK (WGL_CLR_BK),        /* element background color */
                                  WGL_PACK (& t_color_elem)));
    }
    else
    {
        t_img_elem.h_normal             = t_lb_param.t_elem_img_bk.h_normal;
        t_img_elem.h_disable            = t_lb_param.t_elem_img_bk.h_normal;
        t_img_elem.h_highlight          = t_lb_param.t_elem_img_bk.h_highlight;
        t_img_elem.h_highlight_unfocus  = t_lb_param.t_elem_img_bk.h_highlight_unfocus;
        t_img_elem.h_pushed             = t_lb_param.t_elem_img_bk.h_pushed;
        t_img_elem.h_selected           = t_lb_param.t_elem_img_bk.h_selected;
        t_img_elem.h_selected_disable   = t_lb_param.t_elem_img_bk.h_selected;

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                  WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                                  WGL_PACK(& t_img_elem),  /* element background image */
                                  NULL));
    }

    /* column background color */
    COLOR_COPY (& t_color_elem.t_normal,            t_lb_param.t_col_clr_bk.pt_normal);
    COLOR_COPY (& t_color_elem.t_disable,           t_lb_param.t_col_clr_bk.pt_disable);
    COLOR_COPY (& t_color_elem.t_highlight,         t_lb_param.t_col_clr_bk.pt_highlight);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, t_lb_param.t_col_clr_bk.pt_highlight_unfocus);
    COLOR_COPY (& t_color_elem.t_pushed,            t_lb_param.t_col_clr_bk.pt_normal);
    COLOR_COPY (& t_color_elem.t_selected,          t_lb_param.t_col_clr_bk.pt_selected);
    COLOR_COPY (& t_color_elem.t_selected_disable,  t_lb_param.t_col_clr_bk.pt_normal);

    for( ui1_column_index = 0;
            ui1_column_index < t_lb_param.ui1_col_num;
            ui1_column_index++ )
    {
        WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2 (ui1_column_index, WGL_CLR_BK), /* columns background color */
                                  WGL_PACK (& t_color_elem)));
    }

    COLOR_COPY (& t_color_elem.t_normal,            t_lb_param.t_col_clr_txt.pt_normal);
    COLOR_COPY (& t_color_elem.t_disable,           t_lb_param.t_col_clr_txt.pt_disable);
    COLOR_COPY (& t_color_elem.t_highlight,         t_lb_param.t_col_clr_txt.pt_highlight);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, t_lb_param.t_col_clr_txt.pt_highlight_unfocus);
    COLOR_COPY (& t_color_elem.t_pushed,            t_lb_param.t_col_clr_txt.pt_normal);
    COLOR_COPY (& t_color_elem.t_selected,          t_lb_param.t_col_clr_txt.pt_selected);
    COLOR_COPY (& t_color_elem.t_selected_disable,  t_lb_param.t_col_clr_txt.pt_normal);

    for( ui1_column_index = 0;
            ui1_column_index < t_lb_param.ui1_col_num;
            ui1_column_index++ )
    {
        if (ui1_column_index >= 3)
        {
            continue;
        }
        if(t_lb_param.at_cols[ui1_column_index].e_col_type != LB_COL_TYPE_TEXT)
        {
            continue;
        }

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_lb_param.ph_created_lb,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2 (ui1_column_index, WGL_CLR_TEXT), /* text color */
                                  WGL_PACK (& t_color_elem)));
    }

    /* set visibility */
    if (t_lb_param.b_visibility)
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_lb_param.ph_created_lb, WGL_SW_NORMAL));
    }
    else
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_lb_param.ph_created_lb, WGL_SW_HIDE));
    }

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_create_editbox_widget   (WDK_EDIT_BOX_WIDGET_PARAM_T t_eb_param)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_EB_KEY_MAP_T            t_eb_key_map;
    WGL_IMG_INFO_T              t_img_info;
    UTF16_T                     w2s_cursor;

    SET_RECT_BY_SIZE (& t_rect,
                      t_eb_param.i4_x,
                      t_eb_param.i4_y,
                      t_eb_param.i4_w,
                      t_eb_param.i4_h);

    /* create widget */
    WDK_CHK_FAIL (c_wgl_create_widget (t_eb_param.h_parent,
                                     HT_WGL_WIDGET_EDIT_BOX,
                                     WGL_CONTENT_EDIT_BOX_DEF,
                                     WGL_BORDER_UNIFORM,
                                     & t_rect,
                                     t_eb_param.pf_wdgt_proc,
                                     t_eb_param.ui1_alpha,
                                     (VOID*)(t_eb_param.ui4_style),
                                     NULL,
                                     t_eb_param.ph_created_eb));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));

    if (t_eb_param.ps_font_name)
    {
        c_strcpy (t_fnt_info.a_c_font_name, t_eb_param.ps_font_name);
    }
    else
    {
        c_strcpy (t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    }
    t_fnt_info.e_font_size  = t_eb_param.e_font_size;
    t_fnt_info.e_font_style = t_eb_param.e_font_style;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.i2_width     = t_eb_param.i2_width;

    WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set inset */
    t_inset.i4_left   = t_eb_param.t_cnt_inset.i4_left;
    t_inset.i4_right  = t_eb_param.t_cnt_inset.i4_right;
    t_inset.i4_top    = t_eb_param.t_cnt_inset.i4_top;
    t_inset.i4_bottom = t_eb_param.t_cnt_inset.i4_bottom;

    WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                              WGL_CMD_GL_SET_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = t_eb_param.t_inset_info.i4_left;
    t_inset.i4_right  = t_eb_param.t_inset_info.i4_right;
    t_inset.i4_top    = t_eb_param.t_inset_info.i4_top;
    t_inset.i4_bottom = t_eb_param.t_inset_info.i4_bottom;

    WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                              WGL_CMD_EB_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* Set EB Input Limit */
    WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                              WGL_CMD_EB_SET_INPUT_LIMIT,
                              WGL_PACK (t_eb_param.ui2_input_limit),
                              NULL));

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));

    if (t_eb_param.b_cursor_nav)
    {
        t_eb_key_map.ui4_cursor_left   = BTN_CURSOR_LEFT;
        t_eb_key_map.ui4_cursor_right  = BTN_CURSOR_RIGHT;
        t_eb_key_map.ui4_enter_editing = BTN_SELECT;
    }

    WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                              WGL_CMD_EB_SET_KEY_MAP,
                              WGL_PACK (&t_eb_key_map),
                              NULL));

    /* set alignment */
    WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                              WGL_CMD_EB_SET_ALIGN,
                              WGL_PACK (t_eb_param.ui1_align),
                              NULL));

    /* Set as the replace mode */
    WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                              WGL_CMD_EB_SET_INSERT_MODE,
                              WGL_PACK (WGL_EB_MODE_REPLACE),
                              NULL));

    /* Set the cursor highlight */
    WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                              WGL_CMD_EB_ENABLE_CURSOR_HT,
                              WGL_PACK (TRUE),
                              NULL));

    /* Set the cursor character */
    if (t_eb_param.w2s_cursor_char == ((UTF16_T) 0x0000))
    {
        w2s_cursor = (UTF16_T) 0x002D;  /* default */
    }
    else
    {
        w2s_cursor = t_eb_param.w2s_cursor_char;
    }
    WDK_CHK_FAIL (c_wgl_do_cmd(*t_eb_param.ph_created_eb,
                             WGL_CMD_EB_SET_CURSOR_CHAR,
                             (VOID*) (& w2s_cursor),
                             NULL));

    /* Set the text color highlighted by cursor */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_clr_info.u_color_data.t_standard.t_enable,    t_eb_param.pt_clr_cur);
    COLOR_COPY (& t_clr_info.u_color_data.t_standard.t_disable,   t_eb_param.pt_clr_cur);
    COLOR_COPY (& t_clr_info.u_color_data.t_standard.t_highlight, t_eb_param.pt_clr_cur);

    WDK_CHK_FAIL (c_wgl_do_cmd(*t_eb_param.ph_created_eb,
                             WGL_CMD_GL_SET_COLOR,
                             WGL_PACK(WGL_CLR_EB_CURSOR),   /* text color highlighted by cursor */
                             WGL_PACK(& t_clr_info)));

    /* Set auto-edit mode. */
    if (t_eb_param.b_auto_edit)
    {
        WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                                  WGL_CMD_EB_SET_EXT_ATTR,
                                  WGL_PACK (WGL_EB_EA_AUTO_EDITING),
                                  WGL_PACK (WGL_EB_EA_AUTO_EDITING)));
    }

    /* Set always highlight: this will display cursor even if focus not on editbox. */
    if (t_eb_param.b_always_hlt_cursor)
    {
        WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                                  WGL_CMD_EB_SET_EXT_ATTR,
                                  WGL_PACK (WGL_EB_ALWAYS_HT),
                                  WGL_PACK (WGL_EB_ALWAYS_HT)));
    }

    /*set char image*/
    if (TRUE == t_eb_param.b_char_img)
    {
        WDK_CHK_FAIL (c_wgl_do_cmd(*t_eb_param.ph_created_eb,
                                   WGL_CMD_EB_SET_CHAR_IMG,
                                   WGL_PACK(&t_eb_param.t_char_img),
                                   NULL));
    }

    /* set theme */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_clr_info.u_color_data.t_standard.t_enable,    t_eb_param.t_clr_txt.pt_enable);
    COLOR_COPY (& t_clr_info.u_color_data.t_standard.t_disable,   t_eb_param.t_clr_txt.pt_disable);
    COLOR_COPY (& t_clr_info.u_color_data.t_standard.t_highlight, t_eb_param.t_clr_txt.pt_highlight);

    WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),  /* text color */
                              WGL_PACK (& t_clr_info)));

    if(t_eb_param.b_img_bk == TRUE)
    {
        /* set background image */
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable       = t_eb_param.t_bk_img.h_enable;
        t_img_info.u_img_data.t_standard.t_disable      = t_eb_param.t_bk_img.h_disable;
        t_img_info.u_img_data.t_standard.t_highlight    = t_eb_param.t_bk_img.h_highlight;

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK (WGL_IMG_BK),
                                  WGL_PACK (& t_img_info)));
    }
    else
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_clr_info.u_color_data.t_standard.t_enable,    t_eb_param.t_clr_bk.pt_enable);
        COLOR_COPY (& t_clr_info.u_color_data.t_standard.t_highlight, t_eb_param.t_clr_bk.pt_highlight);
        COLOR_COPY (& t_clr_info.u_color_data.t_standard.t_disable,   t_eb_param.t_clr_bk.pt_disable);

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK (WGL_CLR_BK),    /* background color */
                                  WGL_PACK (& t_clr_info)));

        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   , t_eb_param.t_clr_brd.pt_enable);
        COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight, t_eb_param.t_clr_brd.pt_highlight);
        COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  , t_eb_param.t_clr_brd.pt_disable);

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                                  WGL_CMD_GL_SET_BDR_COLOR,
                                  WGL_PACK (WGL_CLR_BDR_FG),    /* border forground color */
                                  WGL_PACK (& t_clr_info)));

        WDK_CHK_FAIL (c_wgl_do_cmd (*t_eb_param.ph_created_eb,
                                  WGL_CMD_GL_SET_BDR_COLOR,
                                  WGL_PACK (WGL_CLR_BK),        /* border color */
                                  WGL_PACK (& t_clr_info)));
    }

    /* set visibility */
    if (t_eb_param.b_visibility)
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_eb_param.ph_created_eb, WGL_SW_NORMAL));
    }
    else
    {
        WDK_CHK_FAIL (c_wgl_set_visibility (*t_eb_param.ph_created_eb, WGL_SW_HIDE));
    }

    return  0;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_set_clr_bk (HANDLE_T    h_widget,
                         GL_COLOR_T* pt_enable_clr,
                         GL_COLOR_T* pt_disable_clr,
                         GL_COLOR_T* pt_highlight_clr)
{
    WGL_COLOR_INFO_T     t_color_info;

    if (h_widget == NULL_HANDLE)
    {
        return WDKR_FAIL;
    }

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    pt_enable_clr);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   pt_disable_clr);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, pt_highlight_clr);

    WDK_CHK_FAIL (c_wgl_do_cmd (h_widget,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_set_text_clr (HANDLE_T    h_widget,
                         GL_COLOR_T* pt_enable_clr,
                         GL_COLOR_T* pt_disable_clr,
                         GL_COLOR_T* pt_highlight_clr)
{
    WGL_COLOR_INFO_T     t_color_info;

    if (h_widget == NULL_HANDLE)
    {
        return WDKR_FAIL;
    }

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    pt_enable_clr);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   pt_disable_clr);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, pt_highlight_clr);

    WDK_CHK_FAIL (c_wgl_do_cmd (h_widget,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_set_img_bk (HANDLE_T    h_widget,
                         WGL_HIMG_TPL_T                  h_enable_img,
                         WGL_HIMG_TPL_T                  h_disable_img,
                         WGL_HIMG_TPL_T                  h_highlight_img)
{
    INT32          i4_ret;
    WGL_IMG_INFO_T t_img_info;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_enable_img;
    t_img_info.u_img_data.t_standard.t_disable   = h_disable_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_highlight_img;

    i4_ret = c_wgl_do_cmd(
                    h_widget,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_set_img_fg (HANDLE_T    h_widget,
                         WGL_HIMG_TPL_T                  h_enable_img,
                         WGL_HIMG_TPL_T                  h_disable_img,
                         WGL_HIMG_TPL_T                  h_highlight_img)
{
    INT32          i4_ret;
    WGL_IMG_INFO_T t_img_info;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_enable_img;
    t_img_info.u_img_data.t_standard.t_disable   = h_disable_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_highlight_img;

    i4_ret = c_wgl_do_cmd(
                    h_widget,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_FG),
                    WGL_PACK(&t_img_info)
                    );
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_set_font_info(HANDLE_T    h_handle,
                           FE_FNT_SIZE                     e_font_size,
                           FE_FNT_STYLE                    e_font_style,
                           FE_CMAP_ENCODING                e_font_cmap,
                           CHAR*                           ps_font_name,
                           INT16                           i2_width)

{
    WGL_FONT_INFO_T   t_font_info;

    c_memset(&t_font_info, 0, sizeof(WGL_FONT_INFO_T));

    t_font_info.e_font_size   = e_font_size;
    t_font_info.e_font_style  = e_font_style;
    t_font_info.e_font_cmap   = FE_CMAP_ENC_UNICODE;
    c_strncpy(t_font_info.a_c_font_name, ps_font_name, WGL_MAX_FONT_NAME);
    t_font_info.i2_width      = i2_width;

    return  c_wgl_do_cmd (h_handle,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK (&t_font_info),
                          NULL);
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_text_set_text(HANDLE_T    h_handle,
                           UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (h_handle,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (0xFFFF));
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_text_set_text_by_number(HANDLE_T    h_handle,
                                     UINT32      ui4_number)
{
    UTF16_T   w2s_buf[16];
    CHAR      s_buf[16];

    c_memset(w2s_buf, 0, sizeof(w2s_buf));
    c_memset(s_buf, 0, sizeof(s_buf));

    c_sprintf(s_buf, "%d", ui4_number);

    c_uc_ps_to_w2s(s_buf, w2s_buf, c_strlen(s_buf));

    return  c_wgl_do_cmd (h_handle,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (w2s_buf),
                          WGL_PACK (0xFFFF));
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_text_start_scroll_attr(HANDLE_T     h_handle,
                                    WDK_TEXT_WIDGET_SCROLL_PARAM_T*  pt_text_scroll)
{
    WGL_TEXT_SCRL_T    t_text_scr;

    if (h_handle == NULL_HANDLE ||
        pt_text_scroll == NULL)
    {
        return WDKR_INV_ARG;
    }

    c_memset (&t_text_scr, 0, sizeof(WGL_TEXT_SCRL_T));

    /* parameter alignment */

    /* default */
    t_text_scr.ui2_style     |= WGL_TEXT_SCRL_SMART;

    if (pt_text_scroll->b_from_first_char)
    {
        t_text_scr.ui2_style |= WGL_TEXT_SCRL_FROM_FIRST_CHAR;
    }
    if (pt_text_scroll->b_till_last_char)
    {
        t_text_scr.ui2_style |= WGL_TEXT_SCRL_TILL_LAST_CHAR;
    }
    if (pt_text_scroll->b_repeat)
    {
        t_text_scr.ui2_style |= WGL_TEXT_SCRL_REPEAT;
    }

    t_text_scr.ui4_ms_delay   = pt_text_scroll->ui4_ms_delay;
    t_text_scr.ui2_scrl_count = pt_text_scroll->ui2_scrl_count;
    t_text_scr.b_sync         = TRUE;

    return  c_wgl_do_cmd (h_handle,
                          WGL_CMD_TEXT_BEGIN_SCRL,
                          WGL_PACK (& t_text_scr),
                          NULL);

}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_text_stop_scroll_attr (HANDLE_T     h_handle)
{
    if (h_handle == NULL_HANDLE)
    {
        return WDKR_INV_ARG;
    }

    return  c_wgl_do_cmd (h_handle,
                          WGL_CMD_TEXT_END_SCRL,
                          NULL,
                          NULL);
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_lb_set_elem_text (HANDLE_T       h_widget,
                               UINT16         ui2_elem_idx,
                               UINT16         ui2_col_idx,
                               UTF16_T*       pw2s_text)
{
    return  c_wgl_do_cmd (h_widget,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2 (ui2_elem_idx, ui2_col_idx),
                          WGL_PACK (pw2s_text));

}
/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_lb_set_elem_img_suit (HANDLE_T                   h_widget,
                                   UINT16                     ui2_elem_idx,
                                   UINT16                     ui2_col_idx,
                                   WGL_LB_ITEM_IMG_SUIT_T*    pt_img_suit)
{
    return  c_wgl_do_cmd (h_widget,
                          WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
                          WGL_PACK_2 (ui2_elem_idx, ui2_col_idx),
                          WGL_PACK (pt_img_suit));
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_lb_set_elem_char_text (HANDLE_T       h_widget,
                                    UINT16         ui2_elem_idx,
                                    UINT16         ui2_col_idx,
                                    CHAR*          ps_str)
{
    UTF16_T     w2s_title[256];

    c_memset(w2s_title, 0, sizeof(w2s_title));

    /* to UTF16 */
    c_uc_ps_to_w2s (ps_str,
                       w2s_title,
                       255);

    return a_wdk_lb_set_elem_text(h_widget,
                               ui2_elem_idx,
                               ui2_col_idx,
                               w2s_title);
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_editbox_set_text(HANDLE_T    h_handle,
                           UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (h_handle,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (0xFFFF));
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_wdk_editbox_set_cursor_pos (HANDLE_T    h_handle,
                                  UINT16                ui2_pos)
{
    return  c_wgl_do_cmd (h_handle,
                          WGL_CMD_EB_SET_CURSOR_POS,
                          WGL_PACK (ui2_pos),
                          NULL);
}


