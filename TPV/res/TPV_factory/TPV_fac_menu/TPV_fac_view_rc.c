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
 * $RCSfile: nav_fac_view_rc.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/06 $
 * $Author: heyi.wang $
 * $CCRevision$
 * $SWAuthor$
 * $MD5HEX$
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
//#include "u_wgl_common.h"
#include "u_wgl.h"
#include "c_wgl_image.h"

#include "nav/nav_common.h"
//#include "res/nav/nav_img.h"
//#include "res/nav/nav_colors.h"
//#include "res/nav/factory/fac_mlm.h"
#include "TPV_factory/TPV_fac_mlm.h"

//#include "nav_fac_view_rc.h"
#include "TPV_fac_view_rc.h"

//#include "res/nav/factory/nav_fac_img.h"
#include "TPV_factory/TPV_fac_img.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
GL_COLOR_T t_g_fac_menu_color_white    = { 255, { 255 }, { 255 }, { 255 }};
GL_COLOR_T t_g_fac_menu_color_gray     = { 255, {  88 }, {  88 }, {  88 }};
GL_COLOR_T t_g_fa_cmenu_color_orange   = { 255, { 255 }, {  69 }, {   0 }};

WGL_FONT_INFO_T  t_title_font_info    = {FE_FNT_SIZE_SMALL,  FE_FNT_STYLE_REGULAR,
                                                FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
#ifndef APP_C4TV_SUPPORT
WGL_FONT_INFO_T  t_elem_font_info     = {FE_FNT_SIZE_MEDIUM, FE_FNT_STYLE_REGULAR,
                                                FE_CMAP_ENC_UNICODE, SN_FONT_DEFAULT_SMALL};
#else
WGL_FONT_INFO_T  t_elem_font_info     = {FE_FNT_SIZE_SMALL, FE_FNT_STYLE_REGULAR,			//FE_FNT_SIZE_MEDIUM		//mind 20160810
                                                FE_CMAP_ENC_UNICODE, SN_FONT_DEFAULT};		//SN_FONT_DEFAULT_SMALL
#endif
/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: nav_fac_view_init_rc
 *
 * Description:
 *      Initiate the colors for menu.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *  0 - Successful
 *  -1- Failed
 ----------------------------------------------------------------------------*/
INT32 nav_fac_view_init_rc(
                    NAV_FAC_VIEW_RC_T*            pt_rc
                    )
{
    INT32 i4_ret;

    i4_ret = TPV_fac_img_create_menu_bk_img_tpl(&pt_rc->h_fac_menu_img_bk);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = TPV_fac_img_create_menu_hilight_img_tpl(&pt_rc->h_fac_hlt_img_bk);
    if(NAVR_OK != i4_ret){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name: nav_fac_view_deinit_rc
 *
 * Description:
 *      Initiate the colors for menu.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *  0 - Successful
 *  -1- Failed
 ----------------------------------------------------------------------------*/
INT32 nav_fac_view_deinit_rc(
                    NAV_FAC_VIEW_RC_T*            pt_rc
                    )
{
    c_wgl_img_tpl_destroy (pt_rc->h_fac_menu_img_bk);
    c_wgl_img_tpl_destroy (pt_rc->h_fac_hlt_img_bk);
    c_wgl_img_tpl_destroy (pt_rc->h_fac_hlt_unfocus_img_bk);
    pt_rc->h_fac_menu_img_bk            = NULL_HANDLE;
    pt_rc->h_fac_hlt_img_bk             = NULL_HANDLE;
    pt_rc->h_fac_hlt_unfocus_img_bk     = NULL_HANDLE;

    return NAVR_OK;
}

