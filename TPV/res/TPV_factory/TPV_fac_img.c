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
 * $RCSfile: nav_img.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/06 $
 * $Author: heyi.wang $
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
#include "u_common.h"
#include "u_wgl_common.h"
#include "c_wgl_image.h"

#include "nav/navigator.h"

//#include "nav/nav_common.h"
#include "TPV_fac_img.h"

//#include "nav_fac_image_8888.i"
#include "TPV_fac_image_8888.i"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
WGL_HIMG_TPL_T  h_g_app_fac_bk_img;
WGL_HIMG_TPL_T  h_g_app_fac_bar_img;
WGL_HIMG_TPL_T  h_g_app_fac_bar_Highlight_img;
WGL_HIMG_TPL_T  h_g_app_fac_pb_bk_img;
WGL_HIMG_TPL_T  h_g_app_fac_pb_bar_img;
WGL_HIMG_TPL_T  h_g_app_fac_sidebar_highlight_arrow_left;
WGL_HIMG_TPL_T  h_g_app_fac_sidebar_highlight_arrow_right;


/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      TPV_fac_img_create_T_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 TPV_fac_img_create_T_img_tpl(WGL_HIMG_TPL_T* ph_img_tpl)
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_app_fac_T_icon_img,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      TPV_fac_img_create_menu_bk_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 INT32 TPV_fac_img_create_menu_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    )
 {
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_app_fac_urc_bk_img, //&t_g_app_fac_frame_bmp,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
* Name
*      TPV_img_create_pwd_bk_img_tpl
* Description
* Input arguments
* Output arguments
* Returns
*---------------------------------------------------------------------------*/
INT32 TPV_fac_img_create_menu_hilight_img_tpl(
                WGL_HIMG_TPL_T*             ph_img_tpl
                )
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_H_ONLY,
                    &t_g_app_fac_bar_Highlight_img, //&t_g_app_fac_highlight_bar_img,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
//ke_vizio_20160912 add
/*-----------------------------------------------------------------------------
 * Name
 *      TPV_fac_img_create_T_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 TPV_fac_img_create_urc_bk_img_tpl(WGL_HIMG_TPL_T* ph_img_tpl)
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_app_fac_urc_bk_img,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      TPV_fac_img_color_tuner_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 TPV_fac_img_color_tuner_tpl(VOID)
{
    INT32 i4_ret;
    static BOOL b_init = FALSE;

    if(b_init == TRUE){
        return NAVR_OK;
    }
    
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_HV,
                    &t_g_app_fac_urc_bk_img,
                    &h_g_app_fac_bk_img
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_H_ONLY,
                    &t_g_app_fac_bar_img,
                    &h_g_app_fac_bar_img
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_H_ONLY,
                    &t_g_app_fac_bar_Highlight_img,
                    &h_g_app_fac_bar_Highlight_img
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_H_ONLY,
                    &t_g_app_fac_pb_bar_img,
                    &h_g_app_fac_pb_bar_img
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_H_ONLY,
                    &t_g_app_fac_pb_bk_img,
                    &h_g_app_fac_pb_bk_img
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_app_fac_sidebar_highlight_arrow_left,
                    &h_g_app_fac_sidebar_highlight_arrow_left
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_app_fac_sidebar_highlight_arrow_right,
                        &h_g_app_fac_sidebar_highlight_arrow_right
                        );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    b_init = TRUE;
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      TPV_fac_img_create_F_img_tpl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 TPV_fac_img_create_F_img_tpl(WGL_HIMG_TPL_T* ph_img_tpl)
{
    INT32 i4_ret;

    if (ph_img_tpl == NULL) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_app_fac_F_icon_img,
                    ph_img_tpl
                    );

    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

