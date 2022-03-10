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
 * $RCSfile: menu_clr.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/4 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 8c6737221831cf41cafd4a196b4fd4a3 $
 *
 * Description:
 *      This file contains the color used by the MENU application.
 *---------------------------------------------------------------------------*/
#ifndef _menu_clr_h_
#define _menu_clr_h_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_sets.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/

/* Transparant */
extern GL_COLOR_T t_g_menu_color_transp;
extern GL_COLOR_T t_g_menu_color_white;
extern GL_COLOR_T t_g_menu_color_black;
extern GL_COLOR_T t_g_menu_font_color_oled;

/* Menu Background */
extern GL_COLOR_T t_g_menu_color_bk0;
extern GL_COLOR_T t_g_menu_color_tb;
extern GL_COLOR_T t_g_menu_color_ib;

/* The background is h_g_img_bk0 */
extern GL_COLOR_T t_g_menu_color_bk0_txt;
extern GL_COLOR_T t_g_menu_color_bk0_txt_hlt;
extern GL_COLOR_T t_g_menu_color_bk0_txt_disable;

/* The background is h_g_img_bk0_ex */
extern GL_COLOR_T t_g_menu_color_bk0_ex_txt;

/* The background is h_g_img_bk1, or t_g_menu_color_bk1 when no APP_MENU_IMG_UI */
extern GL_COLOR_T t_g_menu_color_bk1_txt;
extern GL_COLOR_T t_g_menu_color_bk1_txt_hlt;
extern GL_COLOR_T t_g_menu_color_bk1_txt_disable;

/* The background is h_g_img_bk2 */
extern GL_COLOR_T t_g_menu_color_bk2_txt;
extern GL_COLOR_T t_g_menu_color_bk2_txt_hlt;
extern GL_COLOR_T t_g_menu_color_bk2_txt_disable;

/* The background is t_g_menu_color_bk1 */
extern GL_COLOR_T t_g_menu_color_bk3_txt;
extern GL_COLOR_T t_g_menu_color_bk3_txt_hlt;
extern GL_COLOR_T t_g_menu_color_bk3_txt_disable;

/* Title text color */
extern GL_COLOR_T t_g_menu_color_title_txt;
extern GL_COLOR_T t_g_menu_color_title_bk;

/* Input indicator text color */
extern GL_COLOR_T t_g_menu_color_input_ind_txt;
extern GL_COLOR_T t_g_menu_color_input_ind_bk;

/* Title text color */
extern GL_COLOR_T t_g_menu_color_version_txt;

/* Help list text color */
extern GL_COLOR_T t_g_menu_color_help_txt;

/* Alarm color */
extern GL_COLOR_T t_g_menu_color_alarm_txt;
extern GL_COLOR_T t_g_menu_color_alarm_bk;

/* Scan text color */
extern GL_COLOR_T t_g_menu_color_scan_txt;

/* used to substitude for bk1 when APP_MENU_IMG_UI is turned off*/
extern GL_COLOR_T t_g_menu_color_bk1;
extern GL_COLOR_T t_g_menu_color_bk2;

extern GL_COLOR_T t_g_menu_color_bdr;
extern GL_COLOR_T t_g_menu_color_bdr_hlt;

/* Highlight Cursor Color */
extern GL_COLOR_T t_g_menu_color_highlight_cursor;
#ifdef APP_MJC_SUPPORT
/* MJC text color */
extern GL_COLOR_T t_g_menu_color_mjc_txt;
#endif

extern GL_COLOR_T t_g_menu_color_gray;


/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
extern INT32 menu_init_color(VOID);

#endif /* _menu_clr_h_ */
