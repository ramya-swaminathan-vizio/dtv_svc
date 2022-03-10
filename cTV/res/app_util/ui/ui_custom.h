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
 * $RCSfile: ui_custom.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the custom layer header file for UI
 *---------------------------------------------------------------------------*/


#ifndef _UI_CUSTOM_H_
#define _UI_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
#include "app_util/a_ui.h"

#ifndef APP_UI_IMG_UI
    #ifdef  APP_IMG_UI
        #define APP_UI_IMG_UI
    #endif
#endif

#ifndef IMG_960X540_8888_UI
#define IMG_960X540_8888_UI
#endif


#define UI_WIDTH(__w)                           (__w*4/3) /* for 1280 width  */
#define UI_HEIGHT(__h)                          (__h*4/3) /* for 720 height */

#ifdef IMG_960X540_8888_UI
/*
* Because IMG_960X540_8888_UI already defined, undifined it may casuse some unknown bugs,
* so change UI_WIDTH and UI_HEIGHT from 960*540 to 1440*810, 1440*4/3=1920 810*4/3=1080
*/
#define UI_DISPLAY_WIDTH                            UI_WIDTH(1440)
#define UI_DISPLAY_HEIGHT                           UI_HEIGHT(810)

#define UI_THICK_GRID_W                             (UI_DISPLAY_WIDTH/64)   /* Unit is 15 pixels */
#define UI_THICK_GRID_H                             (UI_DISPLAY_HEIGHT/36)  /* Unit is 15 pixels */

#define UI_THIN_GRID_W                              (UI_DISPLAY_WIDTH/96)   /* Unit is 10 pixels */
#define UI_THIN_GRID_H                              (UI_DISPLAY_HEIGHT/54)  /* Unit is 10 pixels */


#define UI_SLIDER_BAR_DEF_CONTENT_FRAME_X           ((UI_THIN_GRID_H)* 34)/* ((UI_THIN_GRID_H)* 36) */
#define UI_SLIDER_BAR_DEF_CONTENT_FRAME_Y           ((UI_THIN_GRID_H)* 36)
#define UI_SLIDER_BAR_DEF_CONTENT_FRAME_W           ((UI_THIN_GRID_W)* 81)
#define UI_SLIDER_BAR_DEF_CONTENT_FRAME_H           ((UI_THICK_GRID_H)* 7)
#define UI_SLIDER_BAR_STYLE_BAR_CONTENT_FRAME_W     UI_WIDTH(332)
#define UI_SLIDER_BAR_STYLE_BAR_CONTENT_FRAME_H     UI_WIDTH(82)

#define UI_SLIDER_BAR_ICON_X                        ((UI_THIN_GRID_W)* 1)
#define UI_SLIDER_BAR_ICON_Y                        ((UI_HEIGHT(76) - UI_HEIGHT(30))/2)
#define UI_SLIDER_BAR_ICON_W                        ((UI_THIN_GRID_W)* 5)
#define UI_SLIDER_BAR_ICON_H                        ((UI_THIN_GRID_H)* 4)


#define UI_SLIDER_BAR_TEXT_INFO_X                   UI_WIDTH(16)
#define UI_SLIDER_BAR_TEXT_INFO_Y                   UI_HEIGHT(10)
#define UI_SLIDER_BAR_TEXT_INFO_W                   UI_WIDTH(200)
#define UI_SLIDER_BAR_TEXT_INFO_H                   ((UI_THICK_GRID_H)* 2)


#define UI_SLIDER_BAR_ARROW_LEFT_X                  ((UI_THIN_GRID_W)* 22)
#define UI_SLIDER_BAR_ARROW_LEFT_Y                  ((UI_HEIGHT(76) - UI_HEIGHT(16))/2)
#define UI_SLIDER_BAR_ARROW_LEFT_W                  ((UI_THIN_GRID_W)* 2)
#define UI_SLIDER_BAR_ARROW_LEFT_H                  ((UI_THIN_GRID_H)* 2)

#define UI_SLIDER_BAR_PROGRESS_BAR_X                UI_WIDTH(12)
#define UI_SLIDER_BAR_PROGRESS_BAR_Y                UI_HEIGHT(29)
#define UI_SLIDER_BAR_PROGRESS_BAR_W                UI_WIDTH(220)
#define UI_SLIDER_BAR_PROGRESS_BAR_H                ((UI_THICK_GRID_H)* 2)


#define UI_SLIDER_CONTENT_W                         (1920)
#define UI_SLIDER_CONTENT_H                         (1080)

#define UI_SLIDER_BAR_PROGRESS_BAR_LINE_X           (UI_SLIDER_CONTENT_W/2)
#define UI_SLIDER_BAR_PROGRESS_BAR_LINE_Y           (253)
#define UI_SLIDER_BAR_PROGRESS_BAR_LINE_W           UI_SLIDER_CONTENT_W
#define UI_SLIDER_BAR_PROGRESS_BAR_LINE_H           (4)

#define UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X    (0)
#define UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_Y    (665)
#define UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_W    UI_SLIDER_CONTENT_W
#define UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_H    (415)

#define UI_SLIDER_BAR_DEF_CONTENT_TOAST_X           UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X
#define UI_SLIDER_BAR_DEF_CONTENT_TOAST_Y           UI_SLIDER_BAR_PROGRESS_BAR_LINE_Y
#define UI_SLIDER_BAR_DEF_CONTENT_TOAST_W           UI_SLIDER_CONTENT_W
#define UI_SLIDER_BAR_DEF_CONTENT_TOAST_H           (162)

#define UI_SLIDER_BAR_DEF_CONTENT_AUDIO_X           (UI_SLIDER_CONTENT_W/2-13)
#define UI_SLIDER_BAR_DEF_CONTENT_AUDIO_Y           UI_SLIDER_BAR_DEF_CONTENT_TOAST_H
#define UI_SLIDER_BAR_DEF_CONTENT_AUDIO_W           (36)
#define UI_SLIDER_BAR_DEF_CONTENT_AUDIO_H           (36)

#define UI_SLIDER_BAR_DEF_CONTENT_BT_HEADSET_AUDIO_X (UI_SLIDER_CONTENT_W/2-13)
#define UI_SLIDER_BAR_DEF_CONTENT_BT_HEADSET_AUDIO_Y UI_SLIDER_BAR_DEF_CONTENT_TOAST_H
#define UI_SLIDER_BAR_DEF_CONTENT_BT_HEADSET_AUDIO_W (36)
#define UI_SLIDER_BAR_DEF_CONTENT_BT_HEADSET_AUDIO_H (36)

#define UI_SLIDER_BAR_DEF_CONTENT_OFF_AUDIO_X       (UI_SLIDER_CONTENT_W/2-13)
#define UI_SLIDER_BAR_DEF_CONTENT_OFF_AUDIO_Y       UI_SLIDER_BAR_DEF_CONTENT_TOAST_H
#define UI_SLIDER_BAR_DEF_CONTENT_OFF_AUDIO_W       UI_SLIDER_BAR_DEF_CONTENT_AUDIO_W
#define UI_SLIDER_BAR_DEF_CONTENT_OFF_AUDIO_H       UI_SLIDER_BAR_DEF_CONTENT_AUDIO_H

#define UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_X      (UI_SLIDER_CONTENT_W/2-13)
#define UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_Y      UI_SLIDER_BAR_DEF_CONTENT_TOAST_H
#define UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_W      UI_SLIDER_BAR_DEF_CONTENT_AUDIO_W
#define UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_H      UI_SLIDER_BAR_DEF_CONTENT_AUDIO_H

#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_X      (UI_SLIDER_CONTENT_W/2-30)
#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_Y      (147)
#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_W      (60)
#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_H      (60)

#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_OFF_AUDIO_X       UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_X
#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_OFF_AUDIO_Y       UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_Y
#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_OFF_AUDIO_W       UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_W
#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_OFF_AUDIO_H       UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_H

#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_X           UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_X
#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_Y           UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_Y
#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_W           UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_W
#define UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_H           UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_H

#define UI_SLIDER_BAR_DEF_CONTENT_TEXT_X            (900)
#define UI_SLIDER_BAR_DEF_CONTENT_TEXT_Y            (290)
#define UI_SLIDER_BAR_DEF_CONTENT_TEXT_W            (120)
#define UI_SLIDER_BAR_DEF_CONTENT_TEXT_H            (64)

#define UI_SLIDER_BAR_DEF_CONTENT_TEXT_INFO_X       UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X
#define UI_SLIDER_BAR_DEF_CONTENT_TEXT_INFO_Y       UI_SLIDER_BAR_PROGRESS_BAR_LINE_Y
#define UI_SLIDER_BAR_DEF_CONTENT_TEXT_INFO_W       UI_SLIDER_CONTENT_W
#define UI_SLIDER_BAR_DEF_CONTENT_TEXT_INFO_H       UI_SLIDER_BAR_PROGRESS_BAR_LINE_H

#define UI_SLIDER_BAR_DEF_CONTENT_OFF_TEXT_X        (700)
#define UI_SLIDER_BAR_DEF_CONTENT_OFF_TEXT_Y        (290)
#define UI_SLIDER_BAR_DEF_CONTENT_OFF_TEXT_W        (520)
#define UI_SLIDER_BAR_DEF_CONTENT_OFF_TEXT_H        (70)

#define UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_X        (760)
#define UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_Y        (355)
#define UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_W        (400)
#define UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_H        (55)

#define UI_SLIDER_BAR_ARROW_RIGHT_X                 ((UI_THICK_GRID_W)* 45)
#define UI_SLIDER_BAR_ARROW_RIGHT_Y                 ((UI_HEIGHT(76) - UI_HEIGHT(16))/2)
#define UI_SLIDER_BAR_ARROW_RIGHT_W                 ((UI_THIN_GRID_W)* 2)
#define UI_SLIDER_BAR_ARROW_RIGHT_H                 ((UI_THIN_GRID_H)* 2)


#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_X           (UI_SLIDER_BAR_PROGRESS_BAR_W+UI_SLIDER_BAR_PROGRESS_BAR_X-UI_WIDTH(30))
#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_Y           UI_HEIGHT(6) //(UI_SLIDER_BAR_PROGRESS_BAR_Y-UI_HEIGHT(9))
#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_W           UI_WIDTH(30)
#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_H           ((UI_THICK_GRID_H)* 2)

#define UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_L      UI_WIDTH(0)
#define UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_R      UI_WIDTH(0)
#define UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_T      UI_HEIGHT(0)
#define UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_B      UI_HEIGHT(0)

#define UI_SLIDER_BAR_PROGRESS_BAR_BLOCK_W          ((UI_THICK_GRID_H)* 2)
#define UI_SLIDER_BAR_PROGRESS_BAR_BLOCK_H          ((UI_THICK_GRID_H)* 2)

#define UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_W   (UI_THIN_GRID_W * 44)
#define UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_H   (UI_THIN_GRID_H * 15)
#define UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_X   ((UI_DISPLAY_WIDTH - UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_W)/2)
#define UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_Y   ((UI_DISPLAY_HEIGHT - UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_H)/2)

/*BIG INFO*/
#define UI_SIMPLE_DIALOG_BIG_TEXT_INFO_X           (UI_THIN_GRID_W * 5)
#define UI_SIMPLE_DIALOG_BIG_TEXT_INFO_Y           (UI_THIN_GRID_H * 1)
#define UI_SIMPLE_DIALOG_BIG_TEXT_INFO_W           (UI_THIN_GRID_W * 34)
#define UI_SIMPLE_DIALOG_BIG_TEXT_INFO_H           (UI_THIN_GRID_H * 9)

#define UI_SIMPLE_DIALOG_BIG_BUTTON_YES_X          (UI_THIN_GRID_W * 7)
#define UI_SIMPLE_DIALOG_BIG_BUTTON_YES_Y          (UI_THIN_GRID_H * 11)
#define UI_SIMPLE_DIALOG_BIG_BUTTON_YES_W          (UI_THIN_GRID_W * 12)
#define UI_SIMPLE_DIALOG_BIG_BUTTON_YES_H          (UI_THIN_GRID_H * 4)

#define UI_SIMPLE_DIALOG_BIG_BUTTON_NO_X           (UI_THIN_GRID_W * 25)
#define UI_SIMPLE_DIALOG_BIG_BUTTON_NO_Y           (UI_THIN_GRID_H * 11)
#define UI_SIMPLE_DIALOG_BIG_BUTTON_NO_W           (UI_THIN_GRID_W * 12)
#define UI_SIMPLE_DIALOG_BIG_BUTTON_NO_H           (UI_THIN_GRID_H * 4)


/*MEDIUM DEFAULT INFO*/
#define UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_W     827//(UI_THIN_GRID_W * 44)
#define UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_H     280//(UI_THIN_GRID_H * 13)
#define UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_X     ((UI_DISPLAY_WIDTH - UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_W)/2)
#define UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_Y     ((UI_DISPLAY_HEIGHT - UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_H)/2)

#define UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_X             (UI_THIN_GRID_W * 5)
#define UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_Y             (UI_THIN_GRID_H * 1)
#define UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_W             727//(UI_THIN_GRID_W * 34)
#define UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_H             213//(UI_THIN_GRID_H * 7)

#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_X            214//(UI_THIN_GRID_W * 18)
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_Y            233//(UI_THIN_GRID_H * 9)
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_W            (133+35)//(UI_THIN_GRID_W * 12)
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_H            37//(UI_THIN_GRID_H * 4)

#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_X             480//(UI_THIN_GRID_W * 25)
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_Y             UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_Y//(UI_THIN_GRID_H * 9)
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_W             UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_W//(UI_THIN_GRID_W * 12)
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_H             UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_H//(UI_THIN_GRID_H * 4)

/*SMALL DEFAULT INFO*/
#define UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_Y      ((UI_DISPLAY_HEIGHT - UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_H)/2)
#define UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_X      ((UI_DISPLAY_WIDTH - UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W)/2)
#define UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W      (412+90)   /*412*/
#define UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_H      (179+35)   /* 179(117) */

#define UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_X              (UI_THIN_GRID_W * 1+45)
#define UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_Y              (UI_THIN_GRID_W * 1)
#define UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_W              392//(UI_THIN_GRID_W * 36)   /* (UI_THIN_GRID_W * 34) */
#define UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_H              118//(UI_THIN_GRID_W * 9)    /* (UI_THIN_GRID_W * 6) */

#define UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_W             (133+35)//(UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W/2 - UI_WIDTH(10))
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_H             (37)
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_X             (UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_X)
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_Y             (UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_H - UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_H-(4))

#define UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_W              (UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_W)
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_H              (UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_H)
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_X              (UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_X+UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_W+(50))
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_Y              (UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_Y)

#define UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_X       ((UI_DISPLAY_WIDTH - UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_W)/2)
#define UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_Y       ((UI_DISPLAY_HEIGHT - UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_H)/2)
#define UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_W       (UI_THICK_GRID_W * 22)
#define UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_H       (UI_THIN_GRID_H * 8)

#define UI_SIMPLE_DIALOG_INFO_TEXT_INFO_X               (UI_THIN_GRID_W * 6)
#define UI_SIMPLE_DIALOG_INFO_TEXT_INFO_Y               (UI_THIN_GRID_H * 1)
#define UI_SIMPLE_DIALOG_INFO_TEXT_INFO_W               (UI_THIN_GRID_W * 20)
#define UI_SIMPLE_DIALOG_INFO_TEXT_INFO_H               (UI_THIN_GRID_H * 5)

#define UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_X   ((UI_DISPLAY_WIDTH - UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W)/2)
#define UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_Y   (UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_Y)
#define UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_W   (UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W)
#define UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_H   (UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_H)

#define UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_X           (UI_THIN_GRID_W * 1)
#define UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_Y           (UI_THIN_GRID_W * 1)
#define UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_W           (UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_W)
#define UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_H           (150)

#define UI_VOL_BAR_BASE_FRM_X                           ((UI_DISPLAY_WIDTH - UI_VOL_BAR_BASE_FRM_W) /2)
#define UI_VOL_BAR_BASE_FRM_Y                           ((UI_THIN_GRID_H)* 41)  /* ((UI_THIN_GRID_H)* 37) */
#define UI_VOL_BAR_BASE_FRM_W                           UI_WIDTH(308)
#define UI_VOL_BAR_BASE_FRM_H                           UI_HEIGHT(35)

#define UI_VOL_BAR_PG_BAR_X                             UI_WIDTH(50)    /*(48)*/
#define UI_VOL_BAR_PG_BAR_Y                             UI_HEIGHT(19)    /*(10)*/
#define UI_VOL_BAR_PG_BAR_W                             UI_WIDTH(213)
#define UI_VOL_BAR_PG_BAR_H                             UI_HEIGHT(20)

#define UI_VOL_PG_BAR_TEXT_X                            (UI_VOL_BAR_BASE_FRM_W - UI_VOL_PG_BAR_TEXT_W - UI_WIDTH(24))  /* (UI_VOL_BAR_BASE_FRM_W - UI_VOL_PG_BAR_TEXT_W) */
#define UI_VOL_PG_BAR_TEXT_Y                            (UI_VOL_BAR_PG_BAR_H)
#define UI_VOL_PG_BAR_TEXT_W                            ((UI_THIN_GRID_W)* 3)
#define UI_VOL_PG_BAR_TEXT_H                            ((UI_THICK_GRID_H)* 1)



#else
#define UI_DISPLAY_WIDTH                                UI_WIDTH(1280)
#define UI_DISPLAY_HEIGHT                               UI_HEIGHT(720)

#define UI_THICK_GRID_W                                 (UI_DISPLAY_WIDTH/40)   /* Unit is 32 pixels */
#define UI_THICK_GRID_H                                 (UI_DISPLAY_HEIGHT/24)  /* Unit is 30 pixels */

#define UI_THIN_GRID_W                                  (UI_DISPLAY_WIDTH/80)
#define UI_THIN_GRID_H                                  (UI_DISPLAY_HEIGHT/48)

#define UI_SLIDER_BAR_DEF_CONTENT_FRAME_X               (UI_THIN_GRID_W)* 16
#define UI_SLIDER_BAR_DEF_CONTENT_FRAME_Y               (UI_THIN_GRID_H)* 41
#define UI_SLIDER_BAR_DEF_CONTENT_FRAME_W               (UI_THICK_GRID_W)* 24
#define UI_SLIDER_BAR_DEF_CONTENT_FRAME_H               (UI_THICK_GRID_H)* 2
#define UI_SLIDER_BAR_STYLE_BAR_CONTENT_FRAME_W         UI_WIDTH(332)
#define UI_SLIDER_BAR_STYLE_BAR_CONTENT_FRAME_H         UI_WIDTH(82)

#define UI_SLIDER_BAR_TEXT_INFO_X                       (UI_THIN_GRID_W)* 3
#define UI_SLIDER_BAR_TEXT_INFO_Y                       (UI_THIN_GRID_H)* 1
#define UI_SLIDER_BAR_TEXT_INFO_W                       (UI_THICK_GRID_W)* 9
#define UI_SLIDER_BAR_TEXT_INFO_H                       (UI_THICK_GRID_H)* 1

#define UI_SLIDER_BAR_PROGRESS_BAR_X                    (UI_THIN_GRID_W)* 25
#define UI_SLIDER_BAR_PROGRESS_BAR_Y                    (UI_THIN_GRID_H)* 1
#define UI_SLIDER_BAR_PROGRESS_BAR_W                    (UI_THICK_GRID_W)* 9
#define UI_SLIDER_BAR_PROGRESS_BAR_H                    (UI_THICK_GRID_H)* 1

#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_X               (UI_THIN_GRID_W)* 43
#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_Y               (UI_THIN_GRID_H)* 1
#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_W               (UI_THIN_GRID_W)* 5
#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_H               (UI_THICK_GRID_H)* 1

#define UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_L          2
#define UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_R          2
#define UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_T          2
#define UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_B          2

#define UI_SLIDER_BAR_PROGRESS_BAR_BLOCK_W              26
#define UI_SLIDER_BAR_PROGRESS_BAR_BLOCK_H              26


#define UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_X        (UI_THICK_GRID_W) * 10
#define UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_Y        (UI_THICK_GRID_H) * 7
#define UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_W        (UI_THICK_GRID_W) * 20
#define UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_H        (UI_THICK_GRID_H) * 10

#define UI_SIMPLE_DIALOG_BIG_TEXT_INFO_X                (UI_THIN_GRID_W)* 3
#define UI_SIMPLE_DIALOG_BIG_TEXT_INFO_Y                (UI_THIN_GRID_H)* 1
#define UI_SIMPLE_DIALOG_BIG_TEXT_INFO_W                (UI_THICK_GRID_W)* 17
#define UI_SIMPLE_DIALOG_BIG_TEXT_INFO_H                (UI_THICK_GRID_H)* 7

#define UI_SIMPLE_DIALOG_BIG_BUTTON_YES_X               (UI_THIN_GRID_W) * 7
#define UI_SIMPLE_DIALOG_BIG_BUTTON_YES_Y               (UI_THIN_GRID_H) * 16
#define UI_SIMPLE_DIALOG_BIG_BUTTON_YES_W               (UI_THIN_GRID_W) * 10
#define UI_SIMPLE_DIALOG_BIG_BUTTON_YES_H               (UI_THIN_GRID_H) * 3

#define UI_SIMPLE_DIALOG_BIG_BUTTON_NO_X                (UI_THIN_GRID_W) * 23
#define UI_SIMPLE_DIALOG_BIG_BUTTON_NO_Y                (UI_THIN_GRID_H) * 16
#define UI_SIMPLE_DIALOG_BIG_BUTTON_NO_W                (UI_THIN_GRID_W) * 10
#define UI_SIMPLE_DIALOG_BIG_BUTTON_NO_H                (UI_THIN_GRID_H) * 3




#define UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_X     (UI_THICK_GRID_W) * 10
#define UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_Y     (UI_THIN_GRID_H) * 17
#define UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_W     (UI_THICK_GRID_W) * 20
#define UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_H     (UI_THIN_GRID_H) * 13

#define UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_X             (UI_THIN_GRID_W)* 3
#define UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_Y             (UI_THIN_GRID_H)* 1
#define UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_W             (UI_THICK_GRID_W)* 17
#define UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_H             (UI_THIN_GRID_H)* 7

#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_X            (UI_THIN_GRID_W) * 7
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_Y            (UI_THIN_GRID_H) * 9
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_W            (UI_THIN_GRID_W) * 10
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_H            (UI_THIN_GRID_H) * 3

#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_X             (UI_THIN_GRID_W) * 23
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_Y             (UI_THIN_GRID_H) * 9
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_W             (UI_THIN_GRID_W) * 10
#define UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_H             (UI_THIN_GRID_H) * 3




#define UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_X      (UI_THICK_GRID_W) * 10
#define UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_Y      (UI_THICK_GRID_H) * 9
#define UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W      (UI_THICK_GRID_W) * 20
#define UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_H      (UI_THIN_GRID_H) * 11

#define UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_X              (UI_THIN_GRID_W)* 3
#define UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_Y              (UI_THIN_GRID_H)* 1
#define UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_W              (UI_THICK_GRID_W)* 17
#define UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_H              (UI_THIN_GRID_H)* 5

#define UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_X             (UI_THIN_GRID_W) * 7
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_Y             (UI_THIN_GRID_H) * 7
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_W             (UI_THIN_GRID_W) * 10
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_H             (UI_THIN_GRID_H) * 3

#define UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_X              (UI_THIN_GRID_W) * 23
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_Y              (UI_THIN_GRID_H) * 7
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_W              (UI_THIN_GRID_W) * 10
#define UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_H              (UI_THIN_GRID_H) * 3

#define UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_X       (UI_THICK_GRID_W) * 10
#define UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_Y       (UI_THICK_GRID_H) * 10
#define UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_W       (UI_THICK_GRID_W) * 20
#define UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_H       (UI_THIN_GRID_H) * 7

#define UI_SIMPLE_DIALOG_INFO_TEXT_INFO_X               (UI_THIN_GRID_W)* 3
#define UI_SIMPLE_DIALOG_INFO_TEXT_INFO_Y               (UI_THIN_GRID_H)* 1
#define UI_SIMPLE_DIALOG_INFO_TEXT_INFO_W               (UI_THICK_GRID_W)* 17
#define UI_SIMPLE_DIALOG_INFO_TEXT_INFO_H               (UI_THIN_GRID_H)* 5

#define UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_X   (UI_THICK_GRID_W) * 14 + 16
#define UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_Y   (UI_THICK_GRID_H) * 9
#define UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_W   384
#define UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_H   89

#define UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_X           10
#define UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_Y           (UI_THIN_GRID_H)* 1
#define UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_W           375
#define UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_H           UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_H

#endif


/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/

/* Transparant */
extern GL_COLOR_T t_g_ui_color_transp;

/* No APP_IMG_UI, txt fg */
extern GL_COLOR_T t_g_ui_color_fg0_txt;
extern GL_COLOR_T t_g_ui_color_fg1_txt;
extern GL_COLOR_T t_g_ui_color_fg2_txt;

extern GL_COLOR_T t_g_ui_color_fg1_oled_txt;


/* No APP_IMG_UI, txt bk */
extern GL_COLOR_T t_g_ui_color_bk0_txt;
extern GL_COLOR_T t_g_ui_color_bk9_txt;

/* No APP_IMG_UI, frm bk */
extern GL_COLOR_T t_g_ui_color_bk0;

/* No APP_IMG_UI, pg bk */
extern GL_COLOR_T t_g_ui_color_pg_bk0;
extern GL_COLOR_T t_g_ui_color_pg_bk1;

/* No APP_IMG_UI, pg bar */
extern GL_COLOR_T t_g_ui_color_pg_bar;



/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
extern INT32 a_ui_vol_ctrl_view_create(UI_SLIDER_BAR_INIT_T*    pt_ui_slider_bar_init,   /* In  */
                                       HANDLE_T*                ph_slider);

extern INT32 a_ui_show_slider_bar_by_mute(HANDLE_T  h_frm_slider,
                                          BOOL      b_mute,
                                          BOOL      is_headphone_vol);

extern INT32 a_ui_vol_ctrl_view_destroy(HANDLE_T    h_frm_slider);

#endif /* _UI_CUSTOM_H_ */

