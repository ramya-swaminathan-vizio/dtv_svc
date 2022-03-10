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
 * $RCSfile: record.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: 
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_NAV_REC_PVR_SCH_SUPPORT

#ifndef _NAV_REMINDER_RC_H_
#define _NAV_REMINDER_RC_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_gl.h"
#include "u_wgl.h"
#include "u_wgl_image.h"
#include "u_fe.h"

#include "wdk/a_wdk_help_lst.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/* Base Frame*/
#define  REMINDER_ROOT_FRM_W          788
#define  REMINDER_ROOT_FRM_H          483
#define  REMINDER_ROOT_FRM_X          ((DISPLAY_WIDTH  - REMINDER_ROOT_FRM_W)/2)
#define  REMINDER_ROOT_FRM_Y          ((DISPLAY_HEIGHT - REMINDER_ROOT_FRM_H)/2)

/* Title. inside the base frame.*/
#define  REMINDER_TITLE_X                 (0)
#define  REMINDER_TITLE_Y                 (0)
#define  REMINDER_TITLE_W                 (500)
#define  REMINDER_TITLE_H                 (45)
#define  REMINDER_TITLE_INSET_L           (40)
#define  REMINDER_TITLE_INSET_R           (40)
#define  REMINDER_TITLE_INSET_T           4
#define  REMINDER_TITLE_INSET_B           0
#define  REMINDER_TITLE_ALIGN             WGL_AS_LEFT_CENTER
#define  REMINDER_TITLE_FONT_SIZE         FE_FNT_SIZE_LARGE

/*   Help list. inside the base frame.*/
#define  REMINDER_HELP_X                  (10)
#define  REMINDER_HELP_Y                  (REMINDER_ROOT_FRM_H - REMINDER_HELP_H )
#define  REMINDER_HELP_W                  (REMINDER_ROOT_FRM_W - 2 * REMINDER_HELP_X)
#define  REMINDER_HELP_H                  (38)

/* Infobar help */
#define REMINDER_INFOBAR_HELP_X          (200)
#define REMINDER_INFOBAR_HELP_Y          0
#define REMINDER_INFOBAR_HELP_W          (580)
#define REMINDER_INFOBAR_HELP_H          (32)
#define REMINDER_INFOBAR_HELP_INSET_L    (20)
#define REMINDER_INFOBAR_HELP_INSET_R    (20)
#define REMINDER_INFOBAR_HELP_INSET_T    0
#define REMINDER_INFOBAR_HELP_INSET_B    0
#define REMINDER_INFOBAR_HELP_IN_GAP     (5)
#define REMINDER_INFOBAR_HELP_OUT_GAP    (10)
#define REMINDER_INFOBAR_HELP_AS         WDK_HELP_LST_AS_RIGHT
#define REMINDER_INFOBAR_HELP_LS         WDK_HELP_LST_LS_IMG_FIRST
#define REMINDER_INFOBAR_HELP_FONT_SIZE  FE_FNT_SIZE_SMALL

/* For layout*/
#define  REMINDER_LAYOUT_X                         (5)
#define  REMINDER_LAYOUT_Y                         (REMINDER_TITLE_Y +REMINDER_TITLE_H + 5)
#define  REMINDER_LAYOUT_W                         (REMINDER_ROOT_FRM_W - 2 * REMINDER_LAYOUT_X)
#define  REMINDER_LAYOUT_H                         (REMINDER_HELP_Y - REMINDER_LAYOUT_Y -5)

/*Display txt*/
#define  REMINDER_SUG_TXT_X                          (0)
#define  REMINDER_SUG_TXT_Y                          (0)
#define  REMINDER_SUG_TXT_W                          (REMINDER_LAYOUT_W)
#define  REMINDER_SUG_TXT_H                          (REMINDER_LAYOUT_H)
#define  REMINDER_SUG_TXT_INSET_L                    (80)
#define  REMINDER_SUG_TXT_INSET_R                    (80)
#define  REMINDER_SUG_TXT_INSET_T                     0
#define  REMINDER_SUG_TXT_INSET_B                     0
#define  REMINDER_SUG_TXT_ALIGN                       WGL_AS_LEFT_CENTER
#define  REMINDER_SUG_TXT_FONT_SIZE                   FE_FNT_SIZE_SMALL

/* Schedule list */
#define  REMINDER_LST_ELEM_NUM                   (128)
#define  REMINDER_LST_PAGE_ELEM_NUM              (10)

#define  REMINDER_LST_COL_NUM                    (5)
#define  REMINDER_LST_LONG_TXT_SCRL_DELAY        (180)
#define  REMINDER_LST_ELEM_H                     (REMINDER_LAYOUT_H /10)
#define  REMINDER_LST_COL_TEXT_FNT_SIZE          FE_FNT_SIZE_SMALL

#define  REMINDER_LST_X                          ((REMINDER_LAYOUT_W - REMINDER_LST_W)/2)
#define  REMINDER_LST_Y                          (0)
#define  REMINDER_LST_W                          (REMINDER_LAYOUT_W)
#define  REMINDER_LST_H                          (REMINDER_LST_ELEM_H * REMINDER_LST_PAGE_ELEM_NUM)
#define  REMINDER_LST_CNT_INSET_L                (0)
#define  REMINDER_LST_CNT_INSET_R                (0)
#define  REMINDER_LST_CNT_INSET_T                (0)
#define  REMINDER_LST_CNT_INSET_B                (0)
#define  REMINDER_LST_ELEM_INSET_L               (15)
#define  REMINDER_LST_ELEM_INSET_R               (15)
#define  REMINDER_LST_ELEM_INSET_T               (0)
#define  REMINDER_LST_ELEM_INSET_B               (0)
#define  REMINDER_LST_COL_TEXT_INSET_L           (0)
#define  REMINDER_LST_COL_TEXT_INSET_R           (0)
#define  REMINDER_LST_COL_TEXT_INSET_T           (0)
#define  REMINDER_LST_COL_TEXT_INSET_B           (0)

#define  REMINDER_LST_COL_W                 (REMINDER_LST_W-REMINDER_LST_CNT_INSET_L- REMINDER_LST_CNT_INSET_R \
                                            -REMINDER_LST_ELEM_INSET_L-REMINDER_LST_ELEM_INSET_R)/8
                                            
#define  REMINDER_LST_COL0_W                 (REMINDER_LST_COL_W)
#define  REMINDER_LST_COL0_ALIGN             WGL_AS_LEFT_CENTER
#define  REMINDER_LST_COL1_W                 (REMINDER_LST_COL_W*3 + 10)
#define  REMINDER_LST_COL1_ALIGN             WGL_AS_LEFT_CENTER
#define  REMINDER_LST_COL2_W                 (REMINDER_LST_COL_W*3/2)
#define  REMINDER_LST_COL2_ALIGN             WGL_AS_LEFT_CENTER
#define  REMINDER_LST_COL3_W                 (REMINDER_LST_COL_W*5/4 - 10)
#define  REMINDER_LST_COL3_ALIGN             WGL_AS_CENTER_CENTER
#define  REMINDER_LST_COL4_W                 (REMINDER_LST_COL_W*5/4)
#define  REMINDER_LST_COL4_ALIGN             WGL_AS_CENTER_CENTER



#define  REMINDER_VIEW_HIDE_DELAY           (15000)/*15 sec*/
#define  REMINDER_DIALOG_HIDE_DELAY         (60000)/*60 sec*/
/*-----------------------------------------------------------------------------
 *  data declarations
 *---------------------------------------------------------------------------*/
/* Transparant */
extern GL_COLOR_T t_g_nav_reminder_color_transp;

/* Title text color */
extern GL_COLOR_T t_g_nav_reminder_color_title_txt;

/* Help list text color */
extern GL_COLOR_T t_g_nav_reminder_color_help_txt;

/*text color*/
extern GL_COLOR_T t_g_nav_reminder_color_normal_fg_clr;
extern GL_COLOR_T t_g_nav_reminder_color_hlt_fg_clr;
extern GL_COLOR_T t_g_nav_reminder_color_dis_fg_clr;

/*List element bk color*/
extern GL_COLOR_T t_g_nav_reminder_color_lst_elm_bk_clr;

extern GL_COLOR_T t_g_nav_reminder_color_highlight_cursor;

extern WGL_HIMG_TPL_T  h_g_nav_reminder_img_bk;
extern WGL_HIMG_TPL_T  h_g_nav_reminder_img_lst_elem_hlt_bk;

extern WGL_HIMG_TPL_T  h_g_nav_reminder_img_exit;
extern WGL_HIMG_TPL_T  h_g_nav_reminder_img_select;
extern WGL_HIMG_TPL_T  h_g_nav_reminder_img_add;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 nav_reminder_rc_init(VOID);

#endif /* _NAV_REMINDER_RC_H_ */

#endif /*APP_NAV_REC_PVR_SCH_SUPPORT*/

