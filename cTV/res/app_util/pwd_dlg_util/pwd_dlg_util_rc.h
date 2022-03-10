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
 * $RCSfile: optl_rc.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/54 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e2d2b1a79d31b7290e162f409db02988 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _PWD_DLG_UTIL_RC_H
#define _PWD_DLG_UTIL_RC_H

#include "res/nav/nav_view.h"


#define PWD_DLG_VKB_MAX_LEN   255
#define PWD_DLG_BK_ALPHA      255
#define PWD_DLG_FG_ALPHA      255

/*Text Color*/
#define PWD_DLG_HELP_TEXT_COLOR       NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)
#define PWD_DLG_TITLE_TEXT_COLOR      NAV_COLOR(NAV_COLOR_ID_TEXT)

/* Edit Box color */
#define PWD_DLG_EB_BDR_WIDTH          NAV_WIDTH(3)
#define PWD_DLG_EB_TEXT_COLOR_NML     NAV_COLOR(NAV_COLOR_ID_TEXT)
#define PWD_DLG_EB_TEXT_COLOR_HLT     (GL_COLOR_T){ 255, { 197}, { 167}, { 00}}
#define PWD_DLG_EB_BDR_COLOR_NML      NAV_COLOR(NAV_COLOR_ID_TEXT)
#define PWD_DLG_EB_BDR_COLOR_HLT      (GL_COLOR_T){ 255, { 197}, { 167}, { 00}}
#define PWD_DLG_EB_BK_COLOR_NML       NAV_COLOR(NAV_COLOR_ID_MAIN)
#define PWD_DLG_EB_BK_COLOR_HLT       NAV_COLOR(NAV_COLOR_ID_MAIN)

/* Edit Box INSET*/
#define PWD_EB_INPUT_INSET_L          NAV_WIDTH(8)
#define PWD_EB_INPUT_INSET_R          NAV_WIDTH(8)

/* pwd only layout */

#define PWD_ONLY_DLG_WIDTH       NAV_WIDTH(390)
#define PWD_ONLY_DLG_HEIGHT      NAV_HEIGHT(90)


#define PWD_ONLY_TITLE_LEFT      NAV_WIDTH(0)
#define PWD_ONLY_TITLE_TOP       NAV_HEIGHT(27)
#define PWD_ONLY_TITLE_WIDTH     NAV_WIDTH(180)
#define PWD_ONLY_TITLE_HEIGHT    NAV_HEIGHT(38)


#define PWD_ONLY_BOX_LEFT        (PWD_ONLY_TITLE_LEFT + PWD_ONLY_TITLE_WIDTH)
#define PWD_ONLY_BOX_TOP         PWD_ONLY_TITLE_TOP
#define PWD_ONLY_BOX_WIDTH       NAV_WIDTH(188)
#define PWD_ONLY_BOX_HEIGHT      NAV_HEIGHT(38)

/* usr pwd layout */
#define USR_PWD_DLG_WIDTH        NAV_WIDTH(390)
#define USR_PWD_DLG_HEIGHT       NAV_HEIGHT(188)

#define USR_NAME_TITLE_LEFT      NAV_WIDTH(0)
#define USR_NAME_TITLE_TOP       NAV_HEIGHT(27)
#define USR_NAME_TITLE_WIDTH     NAV_WIDTH(180)
#define USR_NAME_TITLE_HEIGHT    NAV_HEIGHT(38)

#define USR_PWD_TITLE_LEFT      USR_NAME_TITLE_LEFT
#define USR_PWD_TITLE_TOP       (NAV_HEIGHT(22) +USR_NAME_TITLE_TOP + USR_NAME_TITLE_HEIGHT)
#define USR_PWD_TITLE_WIDTH     USR_NAME_TITLE_WIDTH
#define USR_PWD_TITLE_HEIGHT    USR_NAME_TITLE_HEIGHT


#define USR_NAME_BOX_LEFT      (USR_NAME_TITLE_LEFT + USR_NAME_TITLE_WIDTH)
#define USR_NAME_BOX_TOP       (USR_NAME_TITLE_TOP)
#define USR_NAME_BOX_WIDTH     NAV_WIDTH(180)
#define USR_NAME_BOX_HEIGHT    NAV_HEIGHT(38)


#define USR_PWD_BOX_LEFT      USR_NAME_BOX_LEFT
#define USR_PWD_BOX_TOP       USR_PWD_TITLE_TOP
#define USR_PWD_BOX_WIDTH     NAV_WIDTH(180)
#define USR_PWD_BOX_HEIGHT    NAV_HEIGHT(38)


#define DLG_VKB_STARTX        NAV_WIDTH((960 - 300) >> 1)
#define DLG_VKB_STARTY        NAV_HEIGHT((540 - 274) >> 1)

/* HELP MASSAGE LAYOUT */
#define HELP_INFO_BAR_HEIGHT      NAV_HEIGHT(38)

#define ENTER_ICON_LEFT           (USR_PWD_DLG_WIDTH >>1) + NAV_WIDTH(4) 
#define ENTER_ICON_TOP            (USR_PWD_DLG_HEIGHT - HELP_INFO_BAR_HEIGHT) + NAV_HEIGHT(13)
#define ENTER_ICON_WIDTH          NAV_WIDTH(33)
#define ENTER_ICON_HEIGHT         NAV_HEIGHT(16)

#define ENTER_ICON_MSG_LEFT       (ENTER_ICON_LEFT +  ENTER_ICON_WIDTH + NAV_WIDTH(5)) 
#define ENTER_ICON_MSG_TOP        (ENTER_ICON_TOP - 4)
#define ENTER_ICON_MSG_WIDTH      NAV_WIDTH(68)
#define ENTER_ICON_MSG_HEIGHT     NAV_HEIGHT(16)

#define ARROW_ICON_LEFT           (ENTER_ICON_MSG_LEFT+ ENTER_ICON_MSG_WIDTH +NAV_WIDTH(10))  
#define ARROW_ICON_TOP            ENTER_ICON_MSG_TOP
#define ARROW_ICON_WIDTH          NAV_WIDTH(25)
#define ARROW_ICON_HEIGHT         NAV_HEIGHT(25)

#define ARROW_ICON_MSG_LEFT       (ARROW_ICON_LEFT + ARROW_ICON_WIDTH +NAV_WIDTH(5))  
#define ARROW_ICON_MSG_TOP        ARROW_ICON_TOP
#define ARROW_ICON_MSG_WIDTH      NAV_WIDTH(45)
#define ARROW_ICON_MSG_HEIGHT     NAV_HEIGHT(25)



#endif

