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
 * $RCSfile: theme_img.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/4 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 6995d119ffe2091e31d2bc97171ebd19 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl_common.h"
#include "c_wgl_image.h"
#include "res/theme/theme_img.h"
#include "app_util/a_common.h"
#include "c_handle.h"

#if defined(APP_COLOR_MODE_PALLET)
    #if !defined(APP_OSD_640x360)
        #include "res/theme/images_p.i"
    #else
        #error Not implemented
    #endif
#else /* 444 mode */
#include "res/theme/images_2013.i"
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef struct _THEME_SHARE_RC_T
{
    WGL_HIMG_TPL_T              h_time_zone_map_0;      /* Eastern Time */
    WGL_HIMG_TPL_T              h_time_zone_map_1;      /* Indiana */
    WGL_HIMG_TPL_T              h_time_zone_map_2;      /* Central Time */
    WGL_HIMG_TPL_T              h_time_zone_map_3;      /* Mountain Time */
    WGL_HIMG_TPL_T              h_time_zone_map_4;      /* Arizona */
    WGL_HIMG_TPL_T              h_time_zone_map_5;      /* Pacific Time */
    WGL_HIMG_TPL_T              h_time_zone_map_6;      /* Alaska */
    WGL_HIMG_TPL_T              h_time_zone_map_7;      /* Hawaii */


} THEME_SHARE_RC_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static THEME_SHARE_RC_T          t_g_share_rc;
static BOOL                      b_g_init = FALSE;

static INT32 _theme_create_icon_widget(GL_RECT_T* pt_rect,
                                              HANDLE_T h_parent,
                                              WGL_HIMG_TPL_T  h_img,
                                              HANDLE_T* ph_icon);

static INT32 _theme_load_icon(HANDLE_T  h_icon,
                                     WGL_HIMG_TPL_T t_img_tpl,
                                     BOOL b_repaint);

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: theme_img_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 theme_img_init(VOID)
{
    THEME_SHARE_RC_T*            pt_this = &t_g_share_rc;
    //INT32                        i4_ret;
    if( b_g_init == FALSE)
    {
        pt_this->h_time_zone_map_0 = NULL_HANDLE;
        pt_this->h_time_zone_map_1 = NULL_HANDLE;
        pt_this->h_time_zone_map_2 = NULL_HANDLE;
        pt_this->h_time_zone_map_3 = NULL_HANDLE;
        pt_this->h_time_zone_map_4 = NULL_HANDLE;
        pt_this->h_time_zone_map_5 = NULL_HANDLE;
        pt_this->h_time_zone_map_6 = NULL_HANDLE;
        pt_this->h_time_zone_map_7 = NULL_HANDLE;
        b_g_init = TRUE;
    }

    return THEME_OK;
}

/*-----------------------------------------------------------------------------
 * Name: theme_img_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 theme_img_deinit(VOID)
{
    THEME_SHARE_RC_T*            pt_this = &t_g_share_rc;
    INT32                        i4_ret;

    /*Time zone icon.  0---> Eastern Time */
    if(NULL_HANDLE != pt_this->h_time_zone_map_0)
    {
        i4_ret = c_wgl_img_tpl_destroy(pt_this->h_time_zone_map_0);
        THEME_ASSERT(WGLR_OK == i4_ret);

        pt_this->h_time_zone_map_0 = NULL_HANDLE;
    }

    /*Time zone icon.  1---> Indiana */
    if(NULL_HANDLE != pt_this->h_time_zone_map_1)
    {
        i4_ret = c_wgl_img_tpl_destroy(pt_this->h_time_zone_map_1);
        THEME_ASSERT(WGLR_OK == i4_ret);

        pt_this->h_time_zone_map_1 = NULL_HANDLE;
    }

    /*Time zone icon.  2---> Central Time */
    if(NULL_HANDLE != pt_this->h_time_zone_map_2)
    {
        i4_ret = c_wgl_img_tpl_destroy(pt_this->h_time_zone_map_2);
        THEME_ASSERT(WGLR_OK == i4_ret);

        pt_this->h_time_zone_map_2 = NULL_HANDLE;
    }

    /*Time zone icon.  3---> Mountain Time */
    if(NULL_HANDLE != pt_this->h_time_zone_map_3)
    {
        i4_ret = c_wgl_img_tpl_destroy(pt_this->h_time_zone_map_3);
        THEME_ASSERT(WGLR_OK == i4_ret);

        pt_this->h_time_zone_map_3 = NULL_HANDLE;
    }

    /*Time zone icon.  4---> Arizona */
    if(NULL_HANDLE != pt_this->h_time_zone_map_4)
    {
        i4_ret = c_wgl_img_tpl_destroy(pt_this->h_time_zone_map_4);
        THEME_ASSERT(WGLR_OK == i4_ret);

        pt_this->h_time_zone_map_4 = NULL_HANDLE;
    }

    /*Time zone icon.  5---> Pacific Time */
    if(NULL_HANDLE != pt_this->h_time_zone_map_5)
    {
        i4_ret = c_wgl_img_tpl_destroy(pt_this->h_time_zone_map_5);
        THEME_ASSERT(WGLR_OK == i4_ret);

        pt_this->h_time_zone_map_5 = NULL_HANDLE;
    }

    /*Time zone icon.  6---> Alaska */
    if(NULL_HANDLE != pt_this->h_time_zone_map_6)
    {
        i4_ret = c_wgl_img_tpl_destroy(pt_this->h_time_zone_map_6);
        THEME_ASSERT(WGLR_OK == i4_ret);

        pt_this->h_time_zone_map_6 = NULL_HANDLE;
    }

    /*Time zone icon.  7---> Hawaii */
    if(NULL_HANDLE != pt_this->h_time_zone_map_7)
    {
        i4_ret = c_wgl_img_tpl_destroy(pt_this->h_time_zone_map_7);
        THEME_ASSERT(WGLR_OK == i4_ret);

        pt_this->h_time_zone_map_7 = NULL_HANDLE;
    }

    b_g_init = FALSE;

    return THEME_OK;
}

/*-----------------------------------------------------------------------------
 * Name: theme_time_zone_get_img
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 theme_time_zone_get_img(UINT16 ui2_idx, WGL_HIMG_TPL_T* ph_img_tpl)
{
    return THEME_OK;
}

/*-----------------------------------------------------------------------------
 * Name: theme_time_zone_create_icon_widget
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 theme_time_zone_create_icon_widget(HANDLE_T          h_parent,
                                      WGL_HIMG_TPL_T    h_img,
                                      GL_RECT_T         t_icon_rect,
                                      HANDLE_T*         ph_icon)
{
    GL_RECT_T t_rect;
  INT32     i4_ret = -1;

  t_rect.i4_bottom = t_icon_rect.i4_bottom;
  t_rect.i4_left   = t_icon_rect.i4_left;
  t_rect.i4_right  = t_icon_rect.i4_right;
  t_rect.i4_top    = t_icon_rect.i4_top;

    i4_ret = _theme_create_icon_widget(&t_rect, h_parent, h_img, ph_icon);
  IS_THEME_OK (i4_ret);

    return THEME_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: theme_time_zone_load_icon
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 theme_time_zone_load_icon(HANDLE_T  h_icon, UINT16 ui2_idx, BOOL b_repaint)
{
    WGL_HIMG_TPL_T              t_img_tpl = NULL_HANDLE;
    INT32                       i4_ret    = -1;

    i4_ret = theme_time_zone_get_img(ui2_idx,&t_img_tpl);
    IS_THEME_OK (i4_ret);

    i4_ret = _theme_load_icon(h_icon, t_img_tpl, b_repaint);
    IS_THEME_OK (i4_ret);

    return THEME_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _theme_create_icon_widget
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _theme_create_icon_widget(GL_RECT_T* pt_rect,
                                              HANDLE_T h_parent,
                                              WGL_HIMG_TPL_T  h_img,
                                              HANDLE_T* ph_icon)
{
    INT32 i4_ret;
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 ph_icon
                                 );
    IS_THEME_OK (i4_ret);

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(*ph_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    IS_THEME_OK (i4_ret);

    if (h_img != NULL_HANDLE)
    {
        i4_ret = _theme_load_icon(*ph_icon,h_img,TRUE);
    IS_THEME_OK (i4_ret);
    }

    return THEME_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _theme_load_icon
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _theme_load_icon(HANDLE_T  h_icon,
                                     WGL_HIMG_TPL_T t_img_tpl,
                                     BOOL b_repaint)
{
    INT32 i4_ret;
    WGL_IMG_INFO_T t_img_info;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = t_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = t_img_tpl;
    i4_ret = c_wgl_do_cmd(h_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info)
                          );
    IS_THEME_OK (i4_ret);

    if (b_repaint == TRUE)
    {
        c_wgl_repaint(h_icon,NULL,TRUE);
    }

    return i4_ret ;
}

