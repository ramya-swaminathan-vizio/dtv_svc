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
 * $RCSfile: menu_clr.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 164f107778d40dc636d1d0f28124de3c $
 *
 * Description:
 *      This file contains the color used by the MENU application.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_sets.h"

#include "app_util/a_common.h"

#include "res/menu2/menu_config.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
#if defined(APP_COLOR_MODE_PALLET)
GL_COLOR_T t_g_menu_color_transp            = { 0,   {   0 }, {   0 }, {   0 }};

/* Menu Background */
GL_COLOR_T t_g_menu_color_bk0               = { 0,   {   0 }, {   0 }, {   0 }};
GL_COLOR_T t_g_menu_color_tb                = { 0  , {   0 }, {   0 }, {   0 }};
GL_COLOR_T t_g_menu_color_ib                = { 0  , {   0 }, {   0 }, {   0 }};

/* The background is h_g_img_bk0 */
GL_COLOR_T t_g_menu_color_bk0_txt           = { 255, {   0 }, {   0 }, { 196 }}; /* { 255, {  30 }, {  30 }, {  30 }}; */
GL_COLOR_T t_g_menu_color_bk0_txt_hlt       = { 255, {   0 }, {   0 }, {   1 }};
GL_COLOR_T t_g_menu_color_bk0_txt_disable   = { 255, {   0 }, {   0 }, {  208 }};

/* The background is h_g_img_bk1, or t_g_menu_color_bk1 when no APP_MENU_IMG_UI */
GL_COLOR_T t_g_menu_color_bk1_txt           = { 255, {   0 }, {   0 }, { 220 }}; /* { 255, { 200 }, { 200 }, { 200 }}; */
GL_COLOR_T t_g_menu_color_bk1_txt_hlt       = { 255, {   0 }, {   0 }, { 244 }}; /* { 255, { 232 }, { 186 }, {   2 }}; */
GL_COLOR_T t_g_menu_color_bk1_txt_disable   = { 255, {   0 }, {   0 }, { 227 }}; /* { 255, { 127 }, { 127 }, { 127 }}; */
/*GL_COLOR_T t_g_menu_color_bk1_txt_disable   = { 255, {  96 }, { 143 }, {  48 }};*/

/* The background is h_g_img_bk2 */
GL_COLOR_T t_g_menu_color_bk2_txt           = { 255, {   0 }, {   0 }, { 220 }}; /*{ 255, { 200 }, { 200 }, { 200 }}; */
GL_COLOR_T t_g_menu_color_bk2_txt_hlt       = { 255, {   0 }, {   0 }, {  37 }}; /*{ 255, { 232 }, { 186 }, {   2 }};*/
GL_COLOR_T t_g_menu_color_bk2_txt_disable   = { 255, {   0 }, {   0 }, { 227 }}; /*{ 255, { 127 }, { 127 }, { 127 }};*/
/*GL_COLOR_T t_g_menu_color_bk2_txt_disable   = { 255, {  96 }, { 143 }, {  48 }};*/

/* The background is t_g_menu_color_bk1 */
GL_COLOR_T t_g_menu_color_bk3_txt           = { 255, {   0 }, {   0 }, {  196 }};
GL_COLOR_T t_g_menu_color_bk3_txt_hlt       = { 255, {   0 }, {   0 }, {   0 }};
GL_COLOR_T t_g_menu_color_bk3_txt_disable   = { 255, {   0 }, {   0 }, {  208 }};

/* Title text color */
GL_COLOR_T t_g_menu_color_title_txt         = { 255, {   0 }, {   0 }, { 177 }}; /*{ 255, { 128 }, { 174 }, { 210 }}; */
GL_COLOR_T t_g_menu_color_title_bk          = {   0, {   0 }, {   0 }, {   0 }};

/* Title text color */
GL_COLOR_T t_g_menu_color_input_ind_txt     = {   0, {   0 }, {   0 }, {   0 }};
GL_COLOR_T t_g_menu_color_input_ind_bk      = {   0, {   0 }, {   0 }, {   0 }};

/* Version text color */
GL_COLOR_T t_g_menu_color_version_txt       = {   0, {   0 }, {   0 }, {   0 }};

/* Help list text color */
GL_COLOR_T t_g_menu_color_help_txt          = { 255, {   0 }, {   0 }, { 177 }}; /*{ 255, { 128 }, { 174 }, { 210 }};*/

/* Alarm color */
GL_COLOR_T t_g_menu_color_alarm_txt         = { 255, {   0 }, {   0 }, {  230 }};
GL_COLOR_T t_g_menu_color_alarm_bk          = {   0, {   0 }, {   0 }, {   0 }};

/* Scan text color */
GL_COLOR_T t_g_menu_color_scan_txt          = { 255, {   0 }, {   0 }, {  230 }};/* { 255, { 255 }, { 255 }, { 255 }}; */

/* used to substitude for bk1 when APP_MENU_IMG_UI is turned off*/
GL_COLOR_T t_g_menu_color_bk1               = { 255, {   0 }, {   0 }, {  63 }};
GL_COLOR_T t_g_menu_color_bk2               = { 255, {   0 }, {   0 }, {  190 }};

/* Border color */
GL_COLOR_T t_g_menu_color_bdr               = { 255, {   0 }, {  0 },  {  196  }}; /* { 255, {  30 }, {  30 }, {  30 }}; */
GL_COLOR_T t_g_menu_color_bdr_hlt           = { 255, {   0 }, {  0 },  {  0 }};

/* Highlight Cursor Color */
GL_COLOR_T t_g_menu_color_highlight_cursor  = { 255, {   0 }, {  0 }, {  230 }}; /* { 255  , { 255 }, { 255 }, { 255 }}; */

#ifdef APP_MJC_SUPPORT
/* MJC text color */
GL_COLOR_T t_g_menu_color_mjc_txt           = { 255, {   0 }, {  0 }, {  220 }};
#endif /* APP_MJC_SUPPORT0 */

GL_COLOR_T t_g_menu_color_gray  = {0xff, {0x2c}, {0x2c}, {0x2c}};


#else
/* Transparant */
GL_COLOR_T t_g_menu_color_transp            = { 0,   {   0 }, {   0 }, {   0 }};
GL_COLOR_T t_g_menu_color_white             = { 255, { 255 }, { 255 }, { 255 }};
GL_COLOR_T t_g_menu_color_black             = { 255, {   0 }, {   0 }, {   0 }};

GL_COLOR_T t_g_menu_font_color_oled         = { 255, { 191 }, { 191 }, { 191 }};

/* Menu Background */
GL_COLOR_T t_g_menu_color_bk0               = { 255, {   1 }, {   1 }, {   1 }};
GL_COLOR_T t_g_menu_color_tb                = { 0  , {   0 }, {   0 }, {   0 }};
GL_COLOR_T t_g_menu_color_ib                = { 0  , {   0 }, {   0 }, {   0 }};

/* The background is h_g_img_bk0 */
GL_COLOR_T t_g_menu_color_bk0_txt           = { 255, {  30 }, {  30 }, {  30 }};
GL_COLOR_T t_g_menu_color_bk0_txt_hlt       = { 255, {   0 }, {   0 }, {   0 }};
GL_COLOR_T t_g_menu_color_bk0_txt_disable   = { 255, {  96 }, { 143 }, {  48 }};

/* The background is h_g_img_bk0_ex */
GL_COLOR_T t_g_menu_color_bk0_ex_txt        = { 255, { 118 }, { 161 }, { 235 }};

/* The background is h_g_img_bk1, or t_g_menu_color_bk1 when no APP_MENU_IMG_UI */
GL_COLOR_T t_g_menu_color_bk1_txt           = { 255, { 255 }, { 255 }, { 255 }};
GL_COLOR_T t_g_menu_color_bk1_txt_hlt       = { 255, { 255 }, { 255 }, {   0 }};
GL_COLOR_T t_g_menu_color_bk1_txt_disable   = { 255, { 127 }, { 127 }, { 127 }};
/*GL_COLOR_T t_g_menu_color_bk1_txt_disable   = { 255, {  96 }, { 143 }, {  48 }};*/

/* The background is h_g_img_bk2 */
GL_COLOR_T t_g_menu_color_bk2_txt           = { 255, { 255 }, { 255 }, { 255 }};
GL_COLOR_T t_g_menu_color_bk2_txt_hlt       = { 255, { 255 }, { 255 }, {   0 }};
GL_COLOR_T t_g_menu_color_bk2_txt_disable   = { 255, { 127 }, { 127 }, { 127 }};
/*GL_COLOR_T t_g_menu_color_bk2_txt_disable   = { 255, {  96 }, { 143 }, {  48 }};*/

/* The background is t_g_menu_color_bk1 */
GL_COLOR_T t_g_menu_color_bk3_txt           = { 255, {  30 }, {  30 }, {  30 }};
GL_COLOR_T t_g_menu_color_bk3_txt_hlt       = { 255, {   0 }, {   0 }, {   0 }};
GL_COLOR_T t_g_menu_color_bk3_txt_disable   = { 255, {  96 }, { 143 }, {  48 }};

/* Title text color */
GL_COLOR_T t_g_menu_color_title_txt         = { 255, { 114 }, { 114 }, { 114 }};
GL_COLOR_T t_g_menu_color_title_bk          = {   0, {   0 }, {   0 }, {   0 }};

/* Title text color */
GL_COLOR_T t_g_menu_color_input_ind_txt     = { 255, { 255 }, {  63 }, {   0 }};
GL_COLOR_T t_g_menu_color_input_ind_bk      = {   0, {   0 }, {   0 }, {   0 }};

/* Version text color */
GL_COLOR_T t_g_menu_color_version_txt       = {   0, {   0 }, {   0 }, {   0 }};

/* Help list text color */
GL_COLOR_T t_g_menu_color_help_txt          = { 255, {   0 }, {   0 }, {   0 }};

/* Alarm color */
GL_COLOR_T t_g_menu_color_alarm_txt         = { 255, { 255 }, { 255 }, { 255 }};
GL_COLOR_T t_g_menu_color_alarm_bk          = {   0, {   0 }, {   0 }, {   0 }};

/* Scan text color */
GL_COLOR_T t_g_menu_color_scan_txt          = { 255, { 255 }, { 255 }, { 255 }};

/* used to substitude for bk1 when APP_MENU_IMG_UI is turned off*/
GL_COLOR_T t_g_menu_color_bk1               = { 255, { 240 }, { 240 }, {  90 }};
GL_COLOR_T t_g_menu_color_bk2               = { 255, {  80 }, { 110 }, { 150 }};

/* Border color */
GL_COLOR_T t_g_menu_color_bdr               = { 255, {  30 }, {  30 }, {  30 }};
GL_COLOR_T t_g_menu_color_bdr_hlt           = { 255, {   0 }, {   0 }, {   0 }};

/* Highlight Cursor Color */
GL_COLOR_T t_g_menu_color_highlight_cursor  = { 255  , { 175 }, { 16 }, { 50 }};
#ifdef APP_MJC_SUPPORT
/* MJC text color */
GL_COLOR_T t_g_menu_color_mjc_txt           = { 255, { 255 }, { 255 }, { 255 }};
#endif /* APP_MJC_SUPPORT0 */

GL_COLOR_T t_g_menu_color_gray  = {0xff, {0x2c}, {0x2c}, {0x2c}};


#endif
static BOOL b_oled = FALSE;
extern BOOL a_is_oled_compensation_support();
/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: menu_init_color
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
INT32 menu_init_color(VOID)
{
    b_oled = a_is_oled_compensation_support();
    if (b_oled)
    {
        t_g_menu_color_white = t_g_menu_font_color_oled;
    }
    return 0;
}

