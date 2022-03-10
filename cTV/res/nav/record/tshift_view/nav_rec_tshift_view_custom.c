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
 * $RCSfile: nav_misc_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 164f107778d40dc636d1d0f28124de3c $
 *
 * Description:
 *      This file contains the color used by the MENU application.
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_NAV_REC_TSHIFT_SUPPORT

#include "c_wgl_image.h"
#include "u_irrc_btn_def.h"

#include "nav/nav_common.h"
#include "nav/record/nav_rec.h"
#include "nav/record/tshift_view/nav_rec_tshift_view.h"
#include "nav/record/tshift_view/nav_rec_tshift_view_wzd.h"

#include "res/nav/nav_img.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_colors.h"
#include "res/nav/record/tshift_view/nav_rec_tshift_view_custom.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define __DESTROY_IMG(__img)            \
if((__img) != NULL)                     \
{                                       \
    c_wgl_img_tpl_destroy (__img);      \
    (__img) = NULL;                     \
}

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
static WGL_FONT_INFO_T  t_g_font_info = {
    FE_FNT_SIZE_MEDIUM, 
    FE_FNT_STYLE_REGULAR, 
    FE_CMAP_ENC_UNICODE, 
    SN_FONT_DEFAULT_SMALL,
    0
};

static WGL_FONT_INFO_T  t_g_font_info_scale = {
    FE_FNT_SIZE_MEDIUM, 
    FE_FNT_STYLE_REGULAR, 
    FE_CMAP_ENC_UNICODE, 
    SN_FONT_DEFAULT_SMALL,
    0
};

static WGL_FONT_INFO_T  t_g_wzd_font_info = {
    FE_FNT_SIZE_SMALL, 
    FE_FNT_STYLE_REGULAR, 
    FE_CMAP_ENC_UNICODE, 
    SN_FONT_DEFAULT,
    0
};

static WGL_FONT_INFO_T  t_g_wzd_font_info_title = {
    FE_FNT_SIZE_MEDIUM, 
    FE_FNT_STYLE_REGULAR, 
    FE_CMAP_ENC_UNICODE, 
    SN_FONT_DEFAULT,
    0
};

static WGL_FONT_INFO_T  t_g_wzd_font_info_help = {
    FE_FNT_SIZE_MEDIUM, 
    FE_FNT_STYLE_REGULAR, 
    FE_CMAP_ENC_UNICODE, 
    SN_FONT_DEFAULT_SMALL,
    0
};

static WGL_FONT_INFO_T  t_g_msg_font_info = {
    FE_FNT_SIZE_MEDIUM, 
    FE_FNT_STYLE_REGULAR, 
    FE_CMAP_ENC_UNICODE, 
    SN_FONT_DEFAULT,
    0
};

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
INT32 _nav_rec_tshift_view_init_image_rc(
    NAV_REC_TSHIFT_VIEW_RC_T*         pt_rc)
{
    INT32   i4_ret;

    /* Images */
    i4_ret = nav_img_create_default_bk_img_tpl(&pt_rc->h_img_bk);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Images, playback status */
    i4_ret = nav_img_cec_create_play_img(&pt_rc->h_img_play);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_cec_create_pause_img(&pt_rc->h_img_pause);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_cec_create_stop_img(&pt_rc->h_img_stop);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_cec_create_fast_forward_img(&pt_rc->h_img_ff);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_cec_create_fast_reverse_img(&pt_rc->h_img_fr);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_cec_create_skip_forward_img(&pt_rc->h_img_next);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_cec_create_skip_reverse_img(&pt_rc->h_img_prev);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Images, playback speed */
    i4_ret = nav_img_create_1x_img_tpl(&pt_rc->h_img_1x);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_2x_img_tpl(&pt_rc->h_img_2x);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_4x_img_tpl(&pt_rc->h_img_4x);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_8x_img_tpl(&pt_rc->h_img_8x);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_16x_img_tpl(&pt_rc->h_img_16x);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_32x_img_tpl(&pt_rc->h_img_32x);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Images, timer bar */
    i4_ret = nav_img_create_upg_scan_bar_bk_img_tpl(&pt_rc->h_img_bar_bg);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_upg_scan_bar_level_img_tpl(&pt_rc->h_img_bar_fg);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_upg_scan_bar_level_img_tpl(&pt_rc->h_img_bar_fg);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_tshift_scale_img_tpl(&pt_rc->h_img_ind_time);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_tshift_crnt_img_tpl(&pt_rc->h_img_ind_crnt);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    pt_rc->h_img_record     = NULL_HANDLE;
    pt_rc->h_img_not_record = NULL_HANDLE;
    pt_rc->h_img_live       = NULL_HANDLE;

    return NAVR_OK;
}

INT32 _nav_rec_tshift_view_deinit_image_rc(
    NAV_REC_TSHIFT_VIEW_RC_T*         pt_rc)
{
    __DESTROY_IMG(pt_rc->h_img_bk);
    __DESTROY_IMG(pt_rc->h_img_play);
    __DESTROY_IMG(pt_rc->h_img_pause);
    __DESTROY_IMG(pt_rc->h_img_stop);
    __DESTROY_IMG(pt_rc->h_img_ff);
    __DESTROY_IMG(pt_rc->h_img_fr);
    __DESTROY_IMG(pt_rc->h_img_next);
    __DESTROY_IMG(pt_rc->h_img_prev);
    __DESTROY_IMG(pt_rc->h_img_1x);
    __DESTROY_IMG(pt_rc->h_img_2x);
    __DESTROY_IMG(pt_rc->h_img_4x);
    __DESTROY_IMG(pt_rc->h_img_8x);
    __DESTROY_IMG(pt_rc->h_img_16x);
    __DESTROY_IMG(pt_rc->h_img_32x);
    __DESTROY_IMG(pt_rc->h_img_bar_bg);
    __DESTROY_IMG(pt_rc->h_img_bar_fg);
    __DESTROY_IMG(pt_rc->h_img_ind_time);
    __DESTROY_IMG(pt_rc->h_img_ind_crnt);
    __DESTROY_IMG(pt_rc->h_img_ind_seek);
    __DESTROY_IMG(pt_rc->h_img_record);
    __DESTROY_IMG(pt_rc->h_img_not_record);
    __DESTROY_IMG(pt_rc->h_img_live);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_rec_tshit_view_init_rc
 *
 * Description:
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_rec_tshift_view_init_rc(
    NAV_REC_TSHIFT_VIEW_RC_T*         pt_rc)
{
    INT32       i4_ret;
    GL_COLOR_T  t_color_mini_bg = {255, {0}, {0}, {0}};

    /* Root frme*/
    SET_RECT_BY_SIZE(&pt_rc->t_frm_rect,
                     TSHIFT_FRM_X,
                     TSHIFT_FRM_Y,
                     TSHIFT_FRM_W,
                     TSHIFT_FRM_H);

    /* Playback status */
    SET_RECT_BY_SIZE(&pt_rc->t_pb_status_rect,
                     TSHIFT_PB_STATUS_X,
                     TSHIFT_PB_STATUS_Y,
                     TSHIFT_PB_STATUS_W,
                     TSHIFT_PB_STATUS_H);

    /* Playback speed */
    SET_RECT_BY_SIZE(&pt_rc->t_pb_speed_rect,
                     TSHIFT_PB_SPEED_X,
                     TSHIFT_PB_SPEED_Y,
                     TSHIFT_PB_SPEED_W,
                     TSHIFT_PB_SPEED_H);

    /* Record status */
    SET_RECT_BY_SIZE(&pt_rc->t_rec_status_rect,
                     TSHIFT_REC_STATUS_X,
                     TSHIFT_REC_STATUS_Y,
                     TSHIFT_REC_STATUS_W,
                     TSHIFT_REC_STATUS_H);

    /* Timer bar */
    SET_RECT_BY_SIZE(&pt_rc->t_time_bar_rect,
                     TSHIFT_TIME_BAR_X,
                     TSHIFT_TIME_BAR_Y,
                     TSHIFT_TIME_BAR_W,
                     TSHIFT_TIME_BAR_H);

    SET_RECT_BY_SIZE(&pt_rc->t_time_bar_time_rect,
                     0,
                     TSHIFT_TIME_BAR_TIME_Y,
                     TSHIFT_TIME_BAR_W,
                     TSHIFT_TIME_BAR_TIME_H);

    SET_RECT_BY_SIZE(&pt_rc->t_time_bar_bar_rect,
                     0,
                     TSHIFT_TIME_BAR_BAR_Y,
                     TSHIFT_TIME_BAR_W,
                     TSHIFT_TIME_BAR_BAR_H);

    pt_rc->t_time_bar_bar_inset.i4_left     = TSHIFT_TIME_BAR_INSET_L;
    pt_rc->t_time_bar_bar_inset.i4_right    = TSHIFT_TIME_BAR_INSET_R;
    pt_rc->t_time_bar_bar_inset.i4_top      = TSHIFT_TIME_BAR_INSET_T;
    pt_rc->t_time_bar_bar_inset.i4_bottom   = TSHIFT_TIME_BAR_INSET_B;

    c_memcpy(&pt_rc->t_scale_fnt_info,
             &t_g_font_info_scale,
             sizeof(WGL_FONT_INFO_T));

    /* Broadcast Time */
    SET_RECT_BY_SIZE(&pt_rc->t_brdcst_time_rect,
                     TSHIFT_BRDCST_TIME_X,
                     TSHIFT_BRDCST_TIME_Y,
                     TSHIFT_BRDCST_TIME_W,
                     TSHIFT_BRDCST_TIME_H);
    pt_rc->ui1_brdcst_time_align    = TSHIFT_BRDCST_TIME_ALIGN;
    c_memcpy(&pt_rc->t_brdcst_time_fnt_info,
             &t_g_font_info,
             sizeof(WGL_FONT_INFO_T));

    /* Playback Time */
    SET_RECT_BY_SIZE(&pt_rc->t_pb_time_rect,
                     TSHIFT_PB_TIME_X,
                     TSHIFT_PB_TIME_Y,
                     TSHIFT_PB_TIME_W,
                     TSHIFT_PB_TIME_H);
    pt_rc->ui1_pb_time_align        = TSHIFT_PB_TIME_ALIGN;
    c_memcpy(&pt_rc->t_pb_time_fnt_info,
             &t_g_font_info,
             sizeof(WGL_FONT_INFO_T));

    /* Mini */
    SET_RECT_BY_SIZE(&pt_rc->t_mini_frm_rect,
                     TSHIFT_MINI_FRM_X,
                     TSHIFT_MINI_FRM_Y,
                     TSHIFT_MINI_FRM_W,
                     TSHIFT_MINI_FRM_H);
    SET_RECT_BY_SIZE(&pt_rc->t_mini_txt_rect,
                     TSHIFT_MINI_TXT_X,
                     TSHIFT_MINI_TXT_Y,
                     TSHIFT_MINI_TXT_W,
                     TSHIFT_MINI_TXT_H);
    pt_rc->ui1_mini_pb_time_align   = TSHIFT_MINI_TXT_ALIGN;

    /* Message */
    SET_RECT_BY_SIZE(&pt_rc->t_msg_frm_rect,
                     TSHIFT_MSG_FRM_X,
                     TSHIFT_MSG_FRM_Y,
                     TSHIFT_MSG_FRM_W,
                     TSHIFT_MSG_FRM_H);

    SET_RECT_BY_SIZE(&pt_rc->t_msg_txt_rect,
                     TSHIFT_MSG_TXT_X,
                     TSHIFT_MSG_TXT_Y,
                     TSHIFT_MSG_TXT_W,
                     TSHIFT_MSG_TXT_H);

    pt_rc->t_msg_txt_inset.i4_left   = TSHIFT_MSG_TXT_INSET_L;
    pt_rc->t_msg_txt_inset.i4_right  = TSHIFT_MSG_TXT_INSET_R;
    pt_rc->t_msg_txt_inset.i4_top    = TSHIFT_MSG_TXT_INSET_T;
    pt_rc->t_msg_txt_inset.i4_bottom = TSHIFT_MSG_TXT_INSET_B;

    c_memcpy(&pt_rc->t_msg_fnt_info,
             &t_g_msg_font_info,
             sizeof(WGL_FONT_INFO_T));

    /* Images */
    i4_ret = _nav_rec_tshift_view_init_image_rc(pt_rc);
    NAV_REC_CHK_FAIL(i4_ret, i4_ret);

    /* Colors */
    pt_rc->t_clr_txt            = NAV_COLOR(NAV_COLOR_ID_TEXT);
    pt_rc->t_clr_txt_time_scale = NAV_COLOR(NAV_COLOR_ID_TEXT);
    pt_rc->t_clr_mini_bg        = t_color_mini_bg;
    pt_rc->t_clr_mini_txt       = NAV_COLOR(NAV_COLOR_ID_TEXT);

    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name: nav_rec_tshit_view_deinit_rc
 *
 * Description:
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_rec_tshift_view_deinit_rc(
    NAV_REC_TSHIFT_VIEW_RC_T*         pt_rc)
{
    _nav_rec_tshift_view_deinit_image_rc(pt_rc);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_rec_tshift_view_wzd_init_rc
 *
 * Description:
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_rec_tshift_view_wzd_init_rc(
    NAV_REC_TSHIFT_VIEW_WZD_RC_T* pt_rc)
{
    INT32   i4_ret;

    /* Root frame*/
    SET_RECT_BY_SIZE(&pt_rc->t_frm_rect,
                     TSHIFT_WZD_FRM_MAIN_X,
                     TSHIFT_WZD_FRM_MAIN_Y,
                     TSHIFT_WZD_FRM_MAIN_W,
                     TSHIFT_WZD_FRM_MAIN_H);

    /* Message text */
    SET_RECT_BY_SIZE(&pt_rc->t_txt_msg_rect,
                     TSHIFT_WZD_TXT_MSG_X,
                     TSHIFT_WZD_TXT_MSG_Y,
                     TSHIFT_WZD_TXT_MSG_W,
                     TSHIFT_WZD_TXT_MSG_H);
    SET_RECT_BY_SIZE(&pt_rc->t_txt_msg_rect_2,
                     TSHIFT_WZD_TXT_MSG_X,
                     TSHIFT_WZD_TXT_MSG_Y,
                     TSHIFT_WZD_TXT_MSG_W_2,
                     TSHIFT_WZD_TXT_MSG_H);

    /* Title text */
    SET_RECT_BY_SIZE(&pt_rc->t_txt_title_rect,
                     TSHIFT_WZD_TXT_TITLE_X,
                     TSHIFT_WZD_TXT_TITLE_Y,
                     TSHIFT_WZD_TXT_TITLE_W,
                     TSHIFT_WZD_TXT_TITLE_H);

    /* Option listbox */
    SET_RECT_BY_SIZE(&pt_rc->t_lb_opt_rect,
                     TSHIFT_WZD_LB_OPT_X,
                     TSHIFT_WZD_LB_OPT_Y,
                     TSHIFT_WZD_LB_OPT_W,
                     TSHIFT_WZD_LB_OPT_H);
    pt_rc->ui2_lb_opt_elem_h = TSHIFT_WZD_LB_OPT_ELEM_H;

    /* Size listbox */
    SET_RECT_BY_SIZE(&pt_rc->t_lb_size_rect,
                     TSHIFT_WZD_LB_SIZE_X,
                     TSHIFT_WZD_LB_SIZE_Y,
                     TSHIFT_WZD_LB_SIZE_W,
                     TSHIFT_WZD_LB_SIZE_H);
    pt_rc->ui2_lb_size_elem_h = TSHIFT_WZD_LB_SIZE_ELEM_H;

    /* Progress bar */
    SET_RECT_BY_SIZE(&pt_rc->t_pb_prog_rect,
                     TSHIFT_WZD_PB_PROG_X,
                     TSHIFT_WZD_PB_PROG_Y,
                     TSHIFT_WZD_PB_PROG_W,
                     TSHIFT_WZD_PB_PROG_H);
    pt_rc->t_pb_prog_inset.i4_top    = TSHIFT_WZD_PB_PROG_INSET_T;
    pt_rc->t_pb_prog_inset.i4_bottom = TSHIFT_WZD_PB_PROG_INSET_B;
    pt_rc->t_pb_prog_inset.i4_left   = TSHIFT_WZD_PB_PROG_INSET_L;
    pt_rc->t_pb_prog_inset.i4_right  = TSHIFT_WZD_PB_PROG_INSET_R;

    /* Status listbox */
    SET_RECT_BY_SIZE(&pt_rc->t_lb_status_rect,
                     TSHIFT_WZD_LB_STATUS_X,
                     TSHIFT_WZD_LB_STATUS_Y,
                     TSHIFT_WZD_LB_STATUS_W,
                     TSHIFT_WZD_LB_STATUS_H);
    pt_rc->ui2_lb_status_elem_h = TSHIFT_WZD_LB_STATUS_ELEM_H;

    /* Images */
    i4_ret = nav_img_create_upg_bk_img_tpl(&pt_rc->h_img_bk);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_upg_hl_bk_img_tpl(&pt_rc->h_img_hl_bk);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_upg_hl_bk_img_tpl(&pt_rc->h_img_hl_bk);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_upg_scan_bar_bk_img_tpl(&pt_rc->h_img_bar_bg);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_upg_scan_bar_level_img_tpl(&pt_rc->h_img_bar_fg);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_upg_back_icon_tpl(&pt_rc->h_img_help_back);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_upg_arrow_up_down_icon_tpl(&pt_rc->h_img_help_select);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_upg_enter_icon_tpl(&pt_rc->h_img_help_next);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_upg_exit_icon_tpl(&pt_rc->h_img_help_exit);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Color */
    pt_rc->t_clr_txt    = NAV_COLOR(NAV_COLOR_ID_TEXT); 
    pt_rc->t_clr_txt_hlt= NAV_COLOR(NAV_COLOR_ID_TEXT_HLT); 
    pt_rc->t_clr_transp = NAV_COLOR(NAV_COLOR_ID_TRANS); 

    /* Font */
    pt_rc->t_fnt_inf_title   = t_g_wzd_font_info_title;
    pt_rc->t_fnt_inf_pb      = t_g_wzd_font_info;
    pt_rc->t_fnt_inf         = t_g_wzd_font_info;
    pt_rc->t_fnt_inf_help    = t_g_wzd_font_info_help;

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_rec_tshift_view_wzd_deinit_rc
 *
 * Description:
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_rec_tshift_view_wzd_deinit_rc(
    NAV_REC_TSHIFT_VIEW_WZD_RC_T* pt_rc)
{
    __DESTROY_IMG(pt_rc->h_img_bk);
    __DESTROY_IMG(pt_rc->h_img_hl_bk);
    __DESTROY_IMG(pt_rc->h_img_bar_bg);
    __DESTROY_IMG(pt_rc->h_img_bar_fg);
    __DESTROY_IMG(pt_rc->h_img_help_back);
    __DESTROY_IMG(pt_rc->h_img_help_select);
    __DESTROY_IMG(pt_rc->h_img_help_next);
    __DESTROY_IMG(pt_rc->h_img_help_exit);

    return NAVR_OK;
}

#endif /* APP_NAV_REC_TSHIFT_SUPPORT */


