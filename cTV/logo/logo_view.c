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
 * $RCSfile: logo_view.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/13 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 0dc5e5894593d8bd6b2c6ecc9869c8fa $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "logo/logo_view.h"


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

static GL_COLOR_T    t_logo_bk_color = { 0, { 0 }, { 0 }, { 0 }};


/*
   View structure.
*/
typedef struct
{
    HANDLE_T      h_frm_main;               /* Main frame */
    HANDLE_T      h_icon_logo;              /* Logo icon */

}   LOGO_VIEW_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static LOGO_VIEW_T    t_g_view;

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _logo_view_create_main_frm
 *
 * Description: This function creates the main (root) frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _logo_view_create_main_frm (HANDLE_T    h_canvas)
{
    INT32               i4_ret;
    UINT32              ui4_canvas_width;
    UINT32              ui4_canvas_height;
    INT32               i4_osd_offset_x;
    INT32               i4_osd_offset_y;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;

    /* Get canvas size. */
    i4_ret = c_wgl_get_canvas_size (h_canvas,
                                    & ui4_canvas_width,
                                    & ui4_canvas_height);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Calculate OSD offsets. */
    i4_osd_offset_x = (INT32)((ui4_canvas_width  - MAIN_FRM_W) / 2);
    i4_osd_offset_y = (INT32)((ui4_canvas_height - MAIN_FRM_H) / 2);

    SET_RECT_BY_SIZE (& t_rect,
                      MAIN_FRM_X + i4_osd_offset_x,
                      MAIN_FRM_Y + i4_osd_offset_y,
                      MAIN_FRM_W,
                      MAIN_FRM_H);

    /* Create widget. */
    i4_ret = c_wgl_create_widget (h_canvas,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  NULL,
                                  LOGO_DEFAULT_ALPHA,
                                  (VOID*) WGL_STL_GL_NO_IMG_UI,
                                  0,
                                  & t_g_view.h_frm_main);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Set background color. */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_logo_bk_color;
    t_clr_info.u_color_data.t_standard.t_disable   = t_logo_bk_color;
    t_clr_info.u_color_data.t_standard.t_highlight = t_logo_bk_color;

    i4_ret = c_wgl_do_cmd (t_g_view.h_frm_main,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK (WGL_CLR_BK),
                           WGL_PACK (& t_clr_info));
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    return LOGOR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _logo_view_create_logo_icon
 *
 * Description: This function creates the logo icon.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _logo_view_create_logo_icon (VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      LOGO_ICON_X,
                      LOGO_ICON_Y,
                      LOGO_ICON_W,
                      LOGO_ICON_H);

    /* Create widget. */
    i4_ret = c_wgl_create_widget (t_g_view.h_frm_main,
                                  HT_WGL_WIDGET_ICON,
                                  WGL_CONTENT_ICON_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  NULL,
                                  LOGO_DEFAULT_ALPHA,
                                  NULL,
                                  NULL,
                                  & t_g_view.h_icon_logo);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Set alignment. */
    i4_ret = c_wgl_do_cmd (t_g_view.h_icon_logo,
                           WGL_CMD_ICON_SET_ALIGN,
                           WGL_PACK (LOGO_ICON_ALIGN),
                           NULL);
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Set image. */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = LOGO_ICON_IMAGE;
    t_img_info.u_img_data.t_standard.t_disable   = LOGO_ICON_IMAGE;
    t_img_info.u_img_data.t_standard.t_highlight = LOGO_ICON_IMAGE;

    i4_ret = c_wgl_do_cmd (t_g_view.h_icon_logo,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK (WGL_IMG_FG),
                           WGL_PACK (& t_img_info));
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    return  LOGOR_OK;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: logo_view_show
 *
 * Description: This API shows view.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 logo_view_show (VOID)
{
    return  c_wgl_show (t_g_view.h_frm_main, WGL_SW_RECURSIVE);
}

/*-----------------------------------------------------------------------------
 * Name: menu_view_hide
 *
 * Description: This API hides view.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 logo_view_hide (VOID)
{
    return  c_wgl_show (t_g_view.h_frm_main, WGL_SW_HIDE);
}

/*-----------------------------------------------------------------------------
 * Name: logo_view_init
 *
 * Description: This API inits view.
 *
 * Inputs:  h_canvas            Canvas handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 logo_view_init (HANDLE_T    h_canvas)
{
    INT32            i4_ret;

    /* Reset view data. */
    c_memset (& t_g_view, 0, sizeof (LOGO_VIEW_T));

    /* Init images. */
    i4_ret = logo_image_init ();
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    /* Create widgets. */
    i4_ret = _logo_view_create_main_frm (h_canvas);  /* Main frame */
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    i4_ret = _logo_view_create_logo_icon ();         /* Logo icon */
    LOGO_CHK_FAIL (i4_ret, i4_ret);

    return LOGOR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: logo_view_destory
 *
 * Description: This API destroys view.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 logo_view_destroy (VOID)
{
    /* Destroy image templates. */
    logo_image_destroy ();

    /* Destory widgets. */
    c_wgl_destroy_widget (t_g_view.h_icon_logo);
    c_wgl_destroy_widget (t_g_view.h_frm_main);

    return LOGOR_OK;
}
