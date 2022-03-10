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
 * $RCSfile: ch_dtl_view.c,v $
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
#include "res/nav/nav_variant.h"

#include "u_common.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_gl.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_svctx.h"

#include "nav/nav_common.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"

#include "nav/ch_lst/ch_lst.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)

#ifdef APP_IMG_UI
#define FRAME_STYLE                             (NULL)
#else
#define FRAME_STYLE                             ((VOID*)(WGL_STL_GL_NO_IMG_UI))
#endif
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static UTF16_T*        pw2s_g_title       = NULL;
static UTF16_T*        pw2s_g_no_dtl      = NULL;
static WGL_FONT_INFO_T t_title_font_info  = {FE_FNT_SIZE_LARGE,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
static WGL_FONT_INFO_T t_detail_font_info = {FE_FNT_SIZE_SMALL,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
#ifndef APP_CH_DETAIL_NO_SCROLL
static WGL_FONT_INFO_T t_index_font_info  = {FE_FNT_SIZE_SMALL,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
#endif
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_dtl_view_set_skin(
                    NAV_CH_DTL_VIEW_T*          pt_view,
                    APP_COLOR_TYPE_T            e_color_type
                    );
static INT32 _nav_ch_dtl_view_set_msgs(
                    NAV_CH_DTL_VIEW_T*          pt_view
                    );
static VOID _nav_ch_dtl_view_load_msgs(
                    UINT8                       ui1_lang_id
                    );
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_dtl_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_dtl_view_init(
                    NAV_CH_LST_T*               pt_this,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    INT32              i4_ret;
    GL_RECT_T          t_rect;
    NAV_CH_DTL_VIEW_T* pt_view = &(pt_this->t_dtl_view);

    /* create channel detail frame */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    CH_DETAIL_FRAME_LEFT + i4_frame_x_offset,
                    CH_DETAIL_FRAME_TOP  + i4_frame_y_offset,
                    CH_DETAIL_FRAME_WIDTH,
                    CH_DETAIL_FRAME_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    h_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    FRAME_STYLE,
                    NULL,
                    &pt_view->h_frame
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* create channel detail */
    SET_RECT_BY_SIZE(&t_rect,
                    CH_DETAIL_TITLE_LEFT,
                    CH_DETAIL_TITLE_TOP,
                    CH_DETAIL_TITLE_WIDTH,
                    CH_DETAIL_TITLE_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frame,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(VOID*)(WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_title
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* create channel detail */
    SET_RECT_BY_SIZE(&t_rect,
                    CH_DETAIL_LEFT,
                    CH_DETAIL_TOP,
                    CH_DETAIL_WIDTH,
                    CH_DETAIL_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frame,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MULTILINE
                          | WGL_STL_TEXT_MAX_DIS_10_LINE
                          | CH_DETAIL_WGL_TEXT_LEN
                          | CH_DETAIL_WGL_CUT_STYLE
                          | WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_detail
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
#ifndef APP_CH_DETAIL_NO_SCROLL

    /* create channel detail lf icon */
    SET_RECT_BY_SIZE(&t_rect,
                    CH_DETAIL_LF_ICON_LEFT,
                    CH_DETAIL_LF_ICON_TOP,
                    CH_DETAIL_LF_ICON_WIDTH,
                    CH_DETAIL_LF_ICON_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frame,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_lf_icon
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* create channel detail right icon */
    SET_RECT_BY_SIZE(&t_rect,
                    CH_DETAIL_RT_ICON_LEFT,
                    CH_DETAIL_RT_ICON_TOP,
                    CH_DETAIL_RT_ICON_WIDTH,
                    CH_DETAIL_RT_ICON_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frame,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_rt_icon
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* create channel detail index */
    SET_RECT_BY_SIZE(&t_rect,
                    CH_DETAIL_INDEX_LEFT,
                    CH_DETAIL_INDEX_TOP,
                    CH_DETAIL_INDEX_WIDTH,
                    CH_DETAIL_INDEX_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frame,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_32
                          | WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_index
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
#endif

    /* hide the frame */
    i4_ret = c_wgl_show(
                    pt_view->h_frame,
                    WGL_SW_HIDE
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_dtl_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_dtl_view_deinit(
                    NAV_CH_DTL_VIEW_T*          pt_view
                    )
{
#ifdef APP_IMG_UI
    c_wgl_img_tpl_destroy(pt_view->h_img_bk);
#endif

#ifndef APP_CH_DETAIL_NO_SCROLL
    c_wgl_img_tpl_destroy(pt_view->h_img_arrow_lf);
    c_wgl_img_tpl_destroy(pt_view->h_img_arrow_rt);
    c_wgl_destroy_widget(pt_view->h_lf_icon);
    c_wgl_destroy_widget(pt_view->h_rt_icon);
    c_wgl_destroy_widget(pt_view->h_index);
#endif

    c_wgl_destroy_widget(pt_view->h_title);
    c_wgl_destroy_widget(pt_view->h_detail);
    c_wgl_destroy_widget(pt_view->h_frame);
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_dtl_view_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_dtl_view_show(
                    NAV_CH_DTL_VIEW_T*          pt_view
                    )
{
    INT32 i4_ret;

    if (pt_view->b_lazy_init == FALSE)
    {
#ifdef APP_IMG_UI
        i4_ret = nav_img_create_ch_detail_bk_img_tpl(
                        &pt_view->h_img_bk
                        );
        if(NAVR_OK != i4_ret){
            return NAVR_FAIL;
        }
#endif    
#ifndef APP_CH_DETAIL_NO_SCROLL    
        i4_ret = c_wgl_img_tpl_create(
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_app_arrow_left_enable_img,
                        &pt_view->h_img_arrow_lf
                        );
        if(WGLR_OK != i4_ret){
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_img_tpl_create(
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_app_arrow_right_enable_img,
                        &pt_view->h_img_arrow_rt
                        );
        if(WGLR_OK != i4_ret){
            return NAVR_FAIL;
        } 
#endif 
        /* load prog detail frame */
        i4_ret = _nav_ch_dtl_view_set_skin(
                        pt_view,
                        APP_COLOR_TYPE_BLUE
                        );
        if(NAVR_OK != i4_ret) {
            return NAVR_FAIL;
        }
        pt_view->b_lazy_init = TRUE;
    }

    i4_ret = _nav_ch_dtl_view_set_msgs(pt_view);
    if(i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_title,
                    WGL_SW_NORMAL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = nav_ch_dtl_view_updn_page(
                    pt_view,
                    CH_DTL_FIRST_PAGE,
                    FALSE
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_frame,
                    WGL_SW_NORMAL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(
                    pt_view->h_frame,
                    NULL,
                    IS_SYNC_REPAINT
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_dtl_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_dtl_view_hide(
                    NAV_CH_DTL_VIEW_T*          pt_view
                    )
{
        INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_frame,
                    WGL_SW_HIDE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(
                    pt_view->h_frame,
                    NULL,
                    IS_SYNC_REPAINT
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_dtl_view_update
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_dtl_view_update(
                    NAV_CH_DTL_VIEW_T*          pt_view,
                    UTF16_T*                    pw2s_detail,
                    CHAR*                       ps_ch_name
                    )
{
    SIZE_T z_len  = c_uc_w2s_strlen(pw2s_detail);
    INT32  i4_ret = 0;
    SIZE_T z_len_name = 0;
#if 0
    UTF16_T w2s_ch_name_string[CH_NAME_MAX_LENGTH+2] = {0};     /*1 for null-char, 1 for '\n'*/

    if(ps_ch_name)
    {
        z_len_name = c_strlen(ps_ch_name);

        if (z_len_name > 0) {
            /* channel name */
            i4_ret = c_uc_ps_to_w2s(
                            ps_ch_name,
                            w2s_ch_name_string,
                            z_len_name
                            );
            if (i4_ret != UCR_OK) {
                return NAVR_FAIL;
            }
            
            NAV_ASSERT(z_len_name <= CH_NAME_MAX_LENGTH);
            w2s_ch_name_string[z_len_name] = '\n';
            
            i4_ret = c_wgl_do_cmd(
                            pt_view->h_detail,
                            WGL_CMD_TEXT_SET_TEXT,
                            (VOID*)w2s_ch_name_string,
                            (VOID*)(z_len_name + 1)
                            );
            if (i4_ret != WGLR_OK) {
                return NAVR_FAIL;
            }
        }
    }
#endif

    if (z_len > 0) {
        i4_ret = c_wgl_do_cmd(
                        pt_view->h_detail,
                        (z_len_name > 0) ? WGL_CMD_TEXT_APPEND_TEXT : WGL_CMD_TEXT_SET_TEXT,
                        (VOID*)pw2s_detail,
                        (VOID*)(z_len)
                        );

        if(WGLR_OK != i4_ret){
            return NAVR_FAIL;
        }
    } else {
        _nav_ch_dtl_view_load_msgs(nav_get_mlm_lang_id());

        i4_ret = c_wgl_do_cmd(
                        pt_view->h_detail,
                        (z_len_name > 0) ? WGL_CMD_TEXT_APPEND_TEXT : WGL_CMD_TEXT_SET_TEXT,
                        (VOID*)pw2s_g_no_dtl,
                        (VOID*)(c_uc_w2s_strlen(pw2s_g_no_dtl))
                        );
        if(WGLR_OK != i4_ret){
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_dtl_view_updn_page
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_dtl_view_updn_page(
                    NAV_CH_DTL_VIEW_T*          pt_view,
                    UINT8                       ui1_page_dir,
                    BOOL                        b_repaint
                    )
{
#ifdef APP_CH_DETAIL_NO_SCROLL
    INT32   i4_ret;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_TEXT_SET_DISPLAY_START,
                    (VOID*)0,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_detail,
                    WGL_SW_NORMAL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    if (b_repaint == TRUE) {
        i4_ret = c_wgl_repaint(
                    pt_view->h_frame,
                    NULL,
                    IS_SYNC_REPAINT
                    );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }
#else
    INT32   i4_ret;
    UINT16  ui2_total_lines         = 0;
    UINT16  ui2_start_lines         = 0;
    UINT16  ui2_total_pages         = 0;
    UINT16  ui2_crnt_page_index     = 0;
    CHAR    s_page_detail_index[10] = {0};
    UTF16_T w2s_string[10+1]        = {0};

    if (pt_view->ui2_page_lines == 0) {
        return NAVR_FAIL;
    }

    if (ui1_page_dir == CH_DTL_NEXT_PAGE) {
        /* page down */
        i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_TEXT_PAGE_SCROL,
                    WGL_PACK(FALSE),
                    WGL_PACK(TRUE)
                    );
        if(WGLR_OK != i4_ret) {
            return NAVR_FAIL;
        }
    } else if (ui1_page_dir == CH_DTL_PREV_PAGE){
        /* page up */
        i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_TEXT_PAGE_SCROL,
                    WGL_PACK(TRUE),
                    WGL_PACK(TRUE)
                    );
        if(WGLR_OK != i4_ret) {
            return NAVR_FAIL;
        }
    } else if (ui1_page_dir == CH_DTL_FIRST_PAGE) {
        i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_TEXT_SET_DISPLAY_START,
                    (VOID*)0,
                    NULL
                    );
        if(WGLR_OK != i4_ret) {
            return NAVR_FAIL;
        }
    }

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_detail,
                    WGL_SW_NORMAL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* get total lines */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_TEXT_GET_TOTAL_LINES,
                    WGL_PACK(&ui2_total_lines),
                    NULL
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    /* get current lines */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_TEXT_GET_DISPLAY_START,
                    WGL_PACK(&ui2_start_lines),
                    NULL
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    ui2_total_pages     = (UINT16)(ui2_total_lines/pt_view->ui2_page_lines
                        + ((ui2_total_lines % pt_view->ui2_page_lines) > 0 ? 1 : 0));
    ui2_crnt_page_index = (UINT16)(ui2_start_lines/pt_view->ui2_page_lines
                        + ((ui2_start_lines % pt_view->ui2_page_lines) > 0 ? 1 : 0) + 1);

    c_sprintf(s_page_detail_index,
                    "%d/%d",
                    ui2_crnt_page_index,
                    ui2_total_pages
                    );

    /* event detail index */
    i4_ret = c_uc_ps_to_w2s(
                    s_page_detail_index,
                    w2s_string,
                    10
                    );
    if (i4_ret != UCR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_index,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)w2s_string,
                    (VOID*)(c_uc_w2s_strlen(w2s_string))
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_index,
                    (ui2_total_pages <= 1) ? WGL_SW_HIDE : WGL_SW_NORMAL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_lf_icon,
                    (ui2_total_pages == 0 || ui2_crnt_page_index == 1) ? WGL_SW_HIDE : WGL_SW_NORMAL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_rt_icon,
                    (ui2_total_pages == 0 || ui2_crnt_page_index == ui2_total_pages) ? WGL_SW_HIDE : WGL_SW_NORMAL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    if (b_repaint == TRUE) {
        i4_ret = c_wgl_repaint(
                    pt_view->h_frame,
                    NULL,
                    IS_SYNC_REPAINT
                    );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_dtl_view_reset_detail
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_dtl_view_reset_detail(
                    NAV_CH_DTL_VIEW_T*          pt_view,
                    BOOL                        b_repaint
                    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)NULL,
                    (VOID*)(0)
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    i4_ret = nav_ch_dtl_view_updn_page(
                    pt_view,
                    CH_DTL_FIRST_PAGE,
                    b_repaint
                    );
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_dtl_view_load_msgs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_ch_dtl_view_load_msgs(
                    UINT8                       ui1_lang_id
                    )
{
    pw2s_g_title  = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_TITLE_CH_DETAIL);
    pw2s_g_no_dtl = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_MSG_NO_CH_DTIL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_dtl_view_set_msgs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_dtl_view_set_msgs(
                    NAV_CH_DTL_VIEW_T*          pt_view
                    )
{
    INT32 i4_ret;

    _nav_ch_dtl_view_load_msgs(nav_get_mlm_lang_id());

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_title,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)pw2s_g_title,
                    (VOID*)(c_uc_w2s_strlen(pw2s_g_title))
                    );

    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_dtl_view_set_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_dtl_view_set_skin(
                    NAV_CH_DTL_VIEW_T*          pt_view,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    WGL_COLOR_INFO_T t_clr_info;
    WGL_INSET_T      t_inset;
    INT32            i4_ret;

#ifdef APP_IMG_UI
    i4_ret = nav_set_bk_img(
                    pt_view->h_frame,
                    WGL_IMG_SET_STANDARD,
                    pt_view->h_img_bk,
                    pt_view->h_img_bk,
                    pt_view->h_img_bk
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#else
    /* set event detail frame bgcolor */
    t_clr_info.e_type                                = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = APP_COLOR(e_color_type, APP_COLOR_ITEM_MAIN);
    t_clr_info.u_color_data.t_standard.t_enable      = APP_COLOR(e_color_type, APP_COLOR_ITEM_MAIN);
    t_clr_info.u_color_data.t_standard.t_highlight   = APP_COLOR(e_color_type, APP_COLOR_ITEM_MAIN);
    t_clr_info.u_color_data.t_standard.t_disable.a   = DEFAULT_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = DEFAULT_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = DEFAULT_BK_ALPHA;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frame,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
#endif
    /* set channel detail title fgcolor */
    t_clr_info.e_type                                = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = CH_DETAIL_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = CH_DETAIL_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = CH_DETAIL_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = DEFAULT_FG_ALPHA;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_title,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set ch detail title alignment */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_title,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set ch detail font */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_title,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_title_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set channel detail fgcolor */
    t_clr_info.e_type                                = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = CH_DETAIL_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = CH_DETAIL_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = CH_DETAIL_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = DEFAULT_FG_ALPHA;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set ch detail font */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_detail_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set ch detail inset */
    t_inset.i4_left   = CH_DETAIL_LEFT_INSET;
    t_inset.i4_right  = CH_DETAIL_RIGHT_INSET;
    t_inset.i4_top    = CH_DETAIL_TOP_INSET;
    t_inset.i4_bottom = CH_DETAIL_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_TEXT_SET_CNT_INSET,
                    (VOID*)&t_inset,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set scroll style */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_TEXT_SET_PAGE_SCROL,
                    (VOID*)WGL_TEXT_PS_TYPE_REPLACE_ALL,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* get ch detail per page lines */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_detail,
                    WGL_CMD_TEXT_GET_PAGE_LINES,
                    (VOID*)&pt_view->ui2_page_lines,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
#ifndef APP_CH_DETAIL_NO_SCROLL
    /* set lf icon bgcolor */
    t_clr_info.u_color_data.t_standard.t_disable.a   = 0;
    t_clr_info.u_color_data.t_standard.t_enable.a    = 0;
    t_clr_info.u_color_data.t_standard.t_highlight.a = 0;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_lf_icon,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set lf icon image buffer*/
    i4_ret = nav_set_icon(
                    pt_view->h_lf_icon,
                    WGL_IMG_SET_STANDARD,
                    pt_view->h_img_arrow_lf,
                    pt_view->h_img_arrow_lf,
                    pt_view->h_img_arrow_lf,
                    WGL_AS_CENTER_CENTER
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* set right icon bgcolor */
    t_clr_info.u_color_data.t_standard.t_disable.a   = 0;
    t_clr_info.u_color_data.t_standard.t_enable.a    = 0;
    t_clr_info.u_color_data.t_standard.t_highlight.a = 0;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_rt_icon,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );

    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set right icon image buffer*/
    i4_ret = nav_set_icon(
                    pt_view->h_rt_icon,
                    WGL_IMG_SET_STANDARD,
                    pt_view->h_img_arrow_rt,
                    pt_view->h_img_arrow_rt,
                    pt_view->h_img_arrow_rt,
                    WGL_AS_CENTER_CENTER
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* set ch detail index fgcolor */
    t_clr_info.e_type                                = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = CH_DETAIL_IDX_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = CH_DETAIL_IDX_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = CH_DETAIL_IDX_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = DEFAULT_FG_ALPHA;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_index,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set ch detail index font */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_index,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_index_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set ch detail index alignment */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_index,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
#endif
    return NAVR_OK;
}
