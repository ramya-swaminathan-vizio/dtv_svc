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
#ifdef APP_NAV_REC_PVR_SUPPORT

#include "c_wgl_image.h"
#include "u_irrc_btn_def.h"

#include "nav/nav_common.h"
#include "nav/record/nav_rec.h"
#include "nav/record/pvr_view/nav_rec_pvr_view.h"

#include "res/nav/nav_img.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_colors.h"
#include "res/nav/record/pvr_view/nav_rec_pvr_view_custom.h"

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

static WGL_FONT_INFO_T  t_g_font_info_ch_txt = {
    FE_FNT_SIZE_MEDIUM, 
    FE_FNT_STYLE_REGULAR, 
    FE_CMAP_ENC_UNICODE, 
    SN_FONT_DEFAULT_SMALL,
    0
};

static WGL_FONT_INFO_T  t_g_font_info_pro_title = {
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
INT32 _nav_rec_pvr_view_init_image_rc(
    NAV_REC_PVR_VIEW_RC_T*         pt_rc)
{
    INT32   i4_ret;

    /* Images */
    i4_ret = nav_img_create_default_bk_img_tpl(&pt_rc->h_img_bk);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Images, playback status */
    i4_ret = nav_img_create_record_icon_img_tpl(&pt_rc->h_img_record);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Images, PVR line */
    i4_ret = nav_img_create_pvr_line_img_tpl(&pt_rc->h_img_pvr_line);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Images, PVR Line litter */
    i4_ret = nav_img_create_pvr_line_littel_img_tpl(&pt_rc->h_img_pvr_line_little);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

INT32 _nav_rec_pvr_view_deinit_image_rc(
    NAV_REC_PVR_VIEW_RC_T*         pt_rc)
{
    __DESTROY_IMG(pt_rc->h_img_bk);
    __DESTROY_IMG(pt_rc->h_img_record);
    __DESTROY_IMG(pt_rc->h_img_pvr_line);
    __DESTROY_IMG(pt_rc->h_img_pvr_line_little);

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
INT32 nav_rec_pvr_view_init_rc(
    NAV_REC_PVR_VIEW_RC_T*         pt_rc)
{
    INT32       i4_ret;

    GL_COLOR_T  t_color_mini_bg = {0, {0}, {0}, {0}};

    /* Root frme*/
    SET_RECT_BY_SIZE(&pt_rc->t_frm_rect,
                     PVR_FRM_X,
                     PVR_FRM_Y,
                     PVR_FRM_W,
                     PVR_FRM_H);

    /* Broadcast Time */
    SET_RECT_BY_SIZE(&pt_rc->t_brdcst_time_rect,
                     PVR_BRDCST_TIME_X,
                     PVR_BRDCST_TIME_Y,
                     PVR_BRDCST_TIME_W,
                     PVR_BRDCST_TIME_H);
    pt_rc->ui1_brdcst_time_align    = PVR_BRDCST_TIME_ALIGN;
    c_memcpy(&pt_rc->t_brdcst_time_fnt_info,
             &t_g_font_info,
             sizeof(WGL_FONT_INFO_T));

    /* Record status */
    SET_RECT_BY_SIZE(&pt_rc->t_pvr_line_rect,
                     PVR_LINE_X,
                     PVR_LINE_Y,
                     PVR_LINE_W,
                     PVR_LINE_H);
	
    /* Record durning */
    SET_RECT_BY_SIZE(&pt_rc->t_main_rec_dur_txt_rect,
					PVR_MINI_TXT_X,
					PVR_MINI_TXT_Y,
					PVR_MINI_TXT_W*2,
					PVR_MINI_TXT_H);

    /* Channel Info */
    SET_RECT_BY_SIZE(&pt_rc->t_ch_info_rect,
                     PVR_CH_INFO_X,
                     PVR_CH_INFO_Y,
                     PVR_CH_INFO_W,
                     PVR_CH_INFO_H);
    pt_rc->ui1_ch_info_align = PVR_CH_INFO_ALIGN;
    c_memcpy(&pt_rc->t_ch_info_fnt_info,
             &t_g_font_info_ch_txt,
             sizeof(WGL_FONT_INFO_T));

    /* pro title */
    SET_RECT_BY_SIZE(&pt_rc->t_pro_title_rect,
                     PVR_PRO_TITLE_X,
                     PVR_PRO_TITLE_Y,
                     PVR_PRO_TITLE_W,
                     PVR_PRO_TITLE_H);
    pt_rc->ui1_pro_title_align = PVR_PRO_TITLE_ALIGN;
    c_memcpy(&pt_rc->t_pro_title_fnt_info,
             &t_g_font_info_pro_title,
             sizeof(WGL_FONT_INFO_T));


    /* Mini */
    SET_RECT_BY_SIZE(&pt_rc->t_mini_frm_rect,
                     PVR_MINI_FRM_X,
                     PVR_MINI_FRM_Y,
                     PVR_MINI_FRM_W,
                     PVR_MINI_FRM_H);
	
    /* Record status */
    SET_RECT_BY_SIZE(&pt_rc->t_rec_status_rect,
                     PVR_REC_STATUS_X,
                     PVR_REC_STATUS_Y,
                     PVR_REC_STATUS_W,
                     PVR_REC_STATUS_H);
	
    SET_RECT_BY_SIZE(&pt_rc->t_mini_txt_rect,
                     PVR_MINI_TXT_X,
                     PVR_MINI_TXT_Y,
                     PVR_MINI_TXT_W,
                     PVR_MINI_TXT_H);
	
    pt_rc->ui1_mini_pb_time_align   = PVR_MINI_TXT_ALIGN;
    c_memcpy(&pt_rc->t_mini_fnt_info,
             &t_g_font_info,
             sizeof(WGL_FONT_INFO_T));

    /* Message */
    SET_RECT_BY_SIZE(&pt_rc->t_msg_frm_rect,
                     PVR_MSG_FRM_X,
                     PVR_MSG_FRM_Y,
                     PVR_MSG_FRM_W,
                     PVR_MSG_FRM_H);

    SET_RECT_BY_SIZE(&pt_rc->t_msg_txt_rect,
                     PVR_MSG_TXT_X,
                     PVR_MSG_TXT_Y,
                     PVR_MSG_TXT_W,
                     PVR_MSG_TXT_H);

    pt_rc->t_msg_txt_inset.i4_left   = PVR_MSG_TXT_INSET_L;
    pt_rc->t_msg_txt_inset.i4_right  = PVR_MSG_TXT_INSET_R;
    pt_rc->t_msg_txt_inset.i4_top    = PVR_MSG_TXT_INSET_T;
    pt_rc->t_msg_txt_inset.i4_bottom = PVR_MSG_TXT_INSET_B;

    c_memcpy(&pt_rc->t_msg_fnt_info,
             &t_g_msg_font_info,
             sizeof(WGL_FONT_INFO_T));

    /* Images */
    i4_ret = _nav_rec_pvr_view_init_image_rc(pt_rc);
    NAV_REC_CHK_FAIL(i4_ret, i4_ret);

    /* Colors */
    pt_rc->t_clr_txt            = NAV_COLOR(NAV_COLOR_ID_TEXT);
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
INT32 nav_rec_pvr_view_deinit_rc(
    NAV_REC_PVR_VIEW_RC_T*         pt_rc)
{
    _nav_rec_pvr_view_deinit_image_rc(pt_rc);

    return NAVR_OK;
}

#endif /* APP_NAV_REC_PVR_SUPPORT */


