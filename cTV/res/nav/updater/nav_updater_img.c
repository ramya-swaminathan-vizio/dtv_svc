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
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "res/nav/updater/nav_updater_img.h"
#include "res/nav/updater/nav_updater_res.h"

/* image definitions */
#include "res/nav/nav_img.h"
#include "res/nav/updater/nav_updater_img.i"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define RET_ON_ERR(_expr) if (_expr != 0) { return -1; }

/*-----------------------------------------------------------------------------
                    function implementations
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: nav_updater_image_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_updater_image_init (
    VOID
)
{
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_updater_back_bar_bk,
               &t_g_nav_updater_res.h_g_img_back_bar_bk));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_updater_back_bar_bk_hlt,
               &t_g_nav_updater_res.h_g_img_back_bar_bk_hlt));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_updater_bk_plain,
               &t_g_nav_updater_res.h_g_img_bk_plain));


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_updater_home_bar,
               &t_g_nav_updater_res.h_g_img_home_bar));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_updater_home_bar_hlt,
               &t_g_nav_updater_res.h_g_img_home_bar_hlt));

   RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY,
               &t_g_nav_updater_banner_bk,
               &t_g_nav_updater_res.h_g_img_banner_bk));

   RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY,
               &t_g_nav_updater_progress_bar_bk,
               &t_g_nav_updater_res.h_g_img_progress_bar_bk));

   RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_HV,
               &t_g_nav_updater_progress_bar_level,
               &t_g_nav_updater_res.h_g_img_progress_bar_level));
   
   RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                  &t_g_nav_updater_progress_bar_bk_rightshadow,
                  &t_g_nav_updater_res.h_g_nav_updater_progress_bar_bk_rightshadow));
   
   RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_updater_progress_bar_bk_leftshadow,
               &t_g_nav_updater_res.h_g_nav_updater_progress_bar_bk_leftshadow));
   
   RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_updater_bk_plain_exit,
               &t_g_nav_updater_res.h_g_nav_updater_bk_plain_exit));
   
   RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_updater_warning_toast,
               &t_g_nav_updater_res.h_g_nav_updater_warning_toast));

   RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
				&t_g_nav_updater_track_fill_toast,
				&t_g_nav_updater_res.h_g_nav_updater_track_fill_toast));
	
   RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
				&t_g_nav_updater_track_cap_left_toast,
				&t_g_nav_updater_res.h_g_nav_updater_track_cap_left_toast));
   
   RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
				&t_g_nav_updater_track_cap_right_toast,
				&t_g_nav_updater_res.h_g_nav_updater_track_cap_right_toast));

    return 0;
}

/*----------------------------------------------------------------------------
 * Name: wzd_image_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_updater_image_deinit (
    VOID
)
{
    c_wgl_img_tpl_destroy(t_g_nav_updater_res.h_g_img_back_bar_bk);
    c_wgl_img_tpl_destroy(t_g_nav_updater_res.h_g_img_back_bar_bk_hlt);
    c_wgl_img_tpl_destroy(t_g_nav_updater_res.h_g_img_bk_plain);
    c_wgl_img_tpl_destroy(t_g_nav_updater_res.h_g_img_home_bar);
    c_wgl_img_tpl_destroy(t_g_nav_updater_res.h_g_img_home_bar_hlt);
    c_wgl_img_tpl_destroy(t_g_nav_updater_res.h_g_img_banner_bk);
    c_wgl_img_tpl_destroy(t_g_nav_updater_res.h_g_nav_updater_progress_bar_bk_rightshadow);
    c_wgl_img_tpl_destroy(t_g_nav_updater_res.h_g_nav_updater_progress_bar_bk_leftshadow);
    c_wgl_img_tpl_destroy(t_g_nav_updater_res.h_g_nav_updater_bk_plain_exit);

    return 0;
}

