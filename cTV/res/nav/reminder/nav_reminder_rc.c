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
 * $RCSfile: rec_model.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *  This file is to implement the logic of pvring.
 *
 *  All the function implemented here assume that it is run at the navigator
 *  thread context. Please guarantee the thread safe if you need to call these
 *  API in non-navigator thread.
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_NAV_REC_PVR_SCH_SUPPORT

#include "u_common.h"

#include "c_handle.h"
#include "c_os.h"

#include "nav/reminder/nav_reminder.h"

#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_colors.h"
#include "res/nav/reminder/nav_reminder_rc.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constanpvr, macro definitions
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 *  data declarations
 *---------------------------------------------------------------------------*/

GL_COLOR_T t_g_nav_reminder_color_transp;

/* Title text color */
GL_COLOR_T t_g_nav_reminder_color_title_txt;

/* Help list text color */
GL_COLOR_T t_g_nav_reminder_color_help_txt;

/*text color*/
GL_COLOR_T t_g_nav_reminder_color_normal_fg_clr;
GL_COLOR_T t_g_nav_reminder_color_hlt_fg_clr;
GL_COLOR_T t_g_nav_reminder_color_dis_fg_clr;

/*List element bk color*/
GL_COLOR_T t_g_nav_reminder_color_lst_elm_bk_clr;

/* Highlight Cursor Color */
GL_COLOR_T t_g_nav_reminder_color_highlight_cursor;



WGL_HIMG_TPL_T  h_g_nav_reminder_img_bk;
WGL_HIMG_TPL_T  h_g_nav_reminder_img_lst_elem_hlt_bk;

WGL_HIMG_TPL_T  h_g_nav_reminder_img_exit;
WGL_HIMG_TPL_T  h_g_nav_reminder_img_select;
WGL_HIMG_TPL_T  h_g_nav_reminder_img_add;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
INT32 nav_reminder_rc_init(VOID)
{
	INT32 i4_ret = NAVR_OK;

    /* Images */
    i4_ret = nav_img_create_reminder_bk_img_tpl(&h_g_nav_reminder_img_bk);
    REMINDER_CHK_FAIL(i4_ret);

	i4_ret = nav_img_create_reminder_exit_icon_tpl(&h_g_nav_reminder_img_exit);
	REMINDER_CHK_FAIL(i4_ret);

    i4_ret = nav_img_create_reminder_arrow_up_down_icon_tpl(&h_g_nav_reminder_img_select);
	REMINDER_CHK_FAIL(i4_ret);

    i4_ret = nav_img_create_hlt_bar_bk_img_tpl (&h_g_nav_reminder_img_lst_elem_hlt_bk);
	REMINDER_CHK_FAIL(i4_ret);

    i4_ret = nav_img_create_reminder_add_icon_tpl (&h_g_nav_reminder_img_add);
	REMINDER_CHK_FAIL(i4_ret);

	t_g_nav_reminder_color_transp 	=  NAV_COLOR(NAV_COLOR_ID_TRANS);
	t_g_nav_reminder_color_title_txt	=  NAV_COLOR(NAV_COLOR_ID_TEXT);
	t_g_nav_reminder_color_help_txt	= NAV_COLOR(NAV_COLOR_ID_TEXT);

	t_g_nav_reminder_color_normal_fg_clr = NAV_COLOR(NAV_COLOR_ID_TEXT);
	t_g_nav_reminder_color_hlt_fg_clr = NAV_COLOR(NAV_COLOR_ID_TEXT_HLT);
	t_g_nav_reminder_color_dis_fg_clr = NAV_COLOR(NAV_COLOR_ID_POP_BLUR);

	t_g_nav_reminder_color_lst_elm_bk_clr = t_g_nav_reminder_color_transp;

	t_g_nav_reminder_color_highlight_cursor = NAV_COLOR(NAV_COLOR_ID_TEXT_HLT);

	return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

#endif /*APP_NAV_REC_PVR_SCH_SUPPORT*/

