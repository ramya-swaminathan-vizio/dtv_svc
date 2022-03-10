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
 * $RCSfile: epg_cfg.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/20 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 3f88970aa8d53b2a36871c1bf4926cd8 $
 *
 * Description:
 *      The file defines the configurable macros for the EPG application.
 *
 *---------------------------------------------------------------------------*/
#ifndef _EPG_CONFIG_H_
#define _EPG_CONFIG_H_

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/*
   OSD resolution.
*/

#define EPG_UI_RATIO_W                       (1)
#define EPG_UI_RATIO_H                       (1)

/*
   Main frame.
*/
#define  MAIN_FRM_W                              (1280 * EPG_UI_RATIO_W)
#define  MAIN_FRM_H                              (720 * EPG_UI_RATIO_H)

#define  EPG_MAIN_FRM_BK_COLOR_BLACK             (APP_COLOR (APP_COLOR_TYPE_BLUE, APP_COLOR_ITEM_BLACK))

/*
   Base map frame.
*/
#define  BASE_FRM_X                          ((MAIN_FRM_W - BASE_FRM_W) / 2)
#define  BASE_FRM_Y                          ((MAIN_FRM_H - BASE_FRM_H) / 2)
#define  BASE_FRM_W                          (955)
#define  BASE_FRM_H                          (538)

#ifdef APP_IMG_UI
    #define  BASE_FRM_IMG_BK                 h_g_epg_img_base_map
#else /* #ifndef APP_IMG_UI */
    #define  BASE_FRM_IMG_BK                 h_g_epg_img_trans
#endif /* APP_IMG_UI */


/*
   Description background frame.
*/
#ifdef APP_EPG_FULL_VIDEO
   /* Because we do not support scale in these modes when DRAM sizw is 32MB */
    #define  DESC_BK_FRM_X                    (PRG_LB_X)
    #define  DESC_BK_FRM_W                    ( PRG_LB_W)
#else
       #define  DESC_BK_FRM_X                    (450 * EPG_UI_RATIO_W)
       #define  DESC_BK_FRM_W                    (700 * EPG_UI_RATIO_W)
#endif
#define  DESC_BK_FRM_Y                       (BASE_FRM_Y + 272*4/3)
#define  DESC_BK_FRM_H                       (100*4/3)
#define  DESC_BK_FRM_IMG_BK                  h_g_epg_img_trans




#ifdef APP_DVBT_SUPPORT

/*
   Type list.
*/
#define  TYPE_LB_X                               (200 * EPG_UI_RATIO_W)
#define  TYPE_LB_Y                               (200 * EPG_UI_RATIO_H)
#define  TYPE_LB_W                               (750 * EPG_UI_RATIO_W)
#define  TYPE_LB_H                               (40 * EPG_UI_RATIO_H)
#define  TYPE_LB_ELEM_H                          (40 * EPG_UI_RATIO_H)
#define  TYPE_LB_COL_W                           (400 * EPG_UI_RATIO_W)
#define  TYPE_LB_COL_FNT_SIZE                    FE_FNT_SIZE_MEDIUM
#define  TYPE_LB_COL_ALIGN                       WGL_AS_CENTER_CENTER
#define  TYPE_LB_TITLE_X                         (0)
#define  TYPE_LB_TITLE_Y                         (0)
#define  TYPE_LB_TITLE_W                         (200 * EPG_UI_RATIO_W)
#define  TYPE_LB_TITLE_H                         (40 * EPG_UI_RATIO_H)
#define  TYPE_LB_TITLE_FNT_SIZE                  FE_FNT_SIZE_MEDIUM
#define  TYPE_LB_TITLE_ALIGN                     WGL_AS_RIGHT_CENTER
#define  TYPE_LB_IMG_SCROLL_UP_X                 (270 * EPG_UI_RATIO_W)
#define  TYPE_LB_IMG_SCROLL_UP_Y                 (10 * EPG_UI_RATIO_H)
#define  TYPE_LB_IMG_SCROLL_DOWN_X               (710 *EPG_UI_RATIO_W)
#define  TYPE_LB_IMG_SCROLL_DOWN_Y               (10 * EPG_UI_RATIO_H)
#define  TYPE_LB_CNT_INSET_L                     (300 * EPG_UI_RATIO_W)
#define  TYPE_LB_CNT_INSET_R                     (50 * EPG_UI_RATIO_W)
#define  TYPE_LB_CNT_INSET_T                     (0)
#define  TYPE_LB_CNT_INSET_B                     (0)
#define  TYPE_LB_ELEM_INSET_L                    (2 * EPG_UI_RATIO_W)
#define  TYPE_LB_ELEM_INSET_R                    (2 * EPG_UI_RATIO_W)
#define  TYPE_LB_ELEM_INSET_T                    (2 * EPG_UI_RATIO_H)
#define  TYPE_LB_ELEM_INSET_B                    (2 * EPG_UI_RATIO_H)
#define  TYPE_LB_COL_INSET_L                     (0)
#define  TYPE_LB_COL_INSET_R                     (0)
#define  TYPE_LB_COL_INSET_T                     (0)
#define  TYPE_LB_COL_INSET_B                     (0)
#define  TYPE_LB_IMG_BK                          h_g_epg_img_trans
#define  TYPE_LB_ELEM_NUM_MAX                    (12)

/*
   Subtype list.
*/
#define  SUBTYPE_LB_X                            (200 * EPG_UI_RATIO_W)
#define  SUBTYPE_LB_Y                            (280 * EPG_UI_RATIO_H)
#define  SUBTYPE_LB_W                            (750 * EPG_UI_RATIO_W)
#define  SUBTYPE_LB_H                            (40 * EPG_UI_RATIO_H)
#define  SUBTYPE_LB_ELEM_H                       (40 * EPG_UI_RATIO_H)
#define  SUBTYPE_LB_COL_W                        (400 * EPG_UI_RATIO_W)
#define  SUBTYPE_LB_COL_FNT_SIZE                 FE_FNT_SIZE_MEDIUM
#define  SUBTYPE_LB_COL_ALIGN                    WGL_AS_CENTER_CENTER
#define  SUBTYPE_LB_TITLE_X                      (0)
#define  SUBTYPE_LB_TITLE_Y                      (0)
#define  SUBTYPE_LB_TITLE_W                      (200 * EPG_UI_RATIO_W)
#define  SUBTYPE_LB_TITLE_H                      (40 * EPG_UI_RATIO_H)
#define  SUBTYPE_LB_TITLE_FNT_SIZE               FE_FNT_SIZE_MEDIUM
#define  SUBTYPE_LB_TITLE_ALIGN                  WGL_AS_RIGHT_CENTER
#define  SUBTYPE_LB_IMG_SCROLL_UP_X              (270 * EPG_UI_RATIO_W)
#define  SUBTYPE_LB_IMG_SCROLL_UP_Y              (10 * EPG_UI_RATIO_H)
#define  SUBTYPE_LB_IMG_SCROLL_DOWN_X            (710 *EPG_UI_RATIO_W)
#define  SUBTYPE_LB_IMG_SCROLL_DOWN_Y            (10 * EPG_UI_RATIO_H)
#define  SUBTYPE_LB_CNT_INSET_L                  (300 * EPG_UI_RATIO_W)
#define  SUBTYPE_LB_CNT_INSET_R                  (50 * EPG_UI_RATIO_W)
#define  SUBTYPE_LB_CNT_INSET_T                  (0)
#define  SUBTYPE_LB_CNT_INSET_B                  (0)
#define  SUBTYPE_LB_ELEM_INSET_L                 (2 * EPG_UI_RATIO_W)
#define  SUBTYPE_LB_ELEM_INSET_R                 (2 * EPG_UI_RATIO_W)
#define  SUBTYPE_LB_ELEM_INSET_T                 (2 * EPG_UI_RATIO_H)
#define  SUBTYPE_LB_ELEM_INSET_B                 (2 * EPG_UI_RATIO_H)
#define  SUBTYPE_LB_COL_INSET_L                  (0)
#define  SUBTYPE_LB_COL_INSET_R                  (0)
#define  SUBTYPE_LB_COL_INSET_T                  (0)
#define  SUBTYPE_LB_COL_INSET_B                  (0)
#define  SUBTYPE_LB_IMG_BK                       h_g_epg_img_trans
#define  SUBTYPE_LB_ELEM_NUM_MAX                 (16)

#endif /* APP_DVBT_SUPPORT */


/*
   Description frame.
*/
#define  DESC_FRM_X                              DESC_BK_FRM_X
#define  DESC_FRM_Y                              DESC_BK_FRM_Y
#define  DESC_FRM_W                              DESC_BK_FRM_W
#define  DESC_FRM_H                              DESC_BK_FRM_H
#define  DESC_FRM_IMG_BK                         h_g_epg_img_trans


/*
   Video frame.
*/


#ifdef APP_EPG_FULL_VIDEO
    #define  VIDEO_FRM_X                     (140 * EPG_UI_RATIO_W)
    #define  VIDEO_FRM_Y                     (550 * EPG_UI_RATIO_H)
    #define  VIDEO_FRM_W                     (500 * EPG_UI_RATIO_W)
    #define  VIDEO_FRM_H                     (50 * EPG_UI_RATIO_H)
#else
    #define  VIDEO_FRM_X                     (130 * EPG_UI_RATIO_W)
    #define  VIDEO_FRM_Y                     (420 * EPG_UI_RATIO_H)
    #define  VIDEO_FRM_W                     (266 * EPG_UI_RATIO_W)
    #define  VIDEO_FRM_H                     (150 * EPG_UI_RATIO_H)
#endif

#ifdef APP_IMG_UI
    #define  VIDEO_FRM_IMG_BK                h_g_epg_img_trans
#else /* #ifndef APP_IMG_UI */
    #define  VIDEO_FRM_IMG_BK                h_g_epg_img_trans
#endif /* APP_IMG_UI */


/*
   Password frame.
*/
#ifdef APP_EPG_FULL_VIDEO
    #define  PASSWD_FRM_X                    (400 * EPG_UI_RATIO_W)
    #define  PASSWD_FRM_Y                    (505 * EPG_UI_RATIO_H)
    #define  PASSWD_FRM_W                    (400 * EPG_UI_RATIO_W)
    #define  PASSWD_FRM_H                    (40 * EPG_UI_RATIO_H)
    #define  PASSWD_FRM_IMG_BK               h_g_epg_img_trans
#else
    #define  PASSWD_FRM_X                    (550 * EPG_UI_RATIO_W)
    #define  PASSWD_FRM_Y                    (505 * EPG_UI_RATIO_H)
    #define  PASSWD_FRM_W                    (400 * EPG_UI_RATIO_W)
    #define  PASSWD_FRM_H                    (40 * EPG_UI_RATIO_H)
    #define  PASSWD_FRM_IMG_BK               h_g_epg_img_trans
#endif

/*
   Channel list.
*/
#define  CHN_LB_X                                (PRG_LB_X)
#define  CHN_LB_Y                                (BASE_FRM_Y + 45)
#define  CHN_LB_W                                (PRG_LB_W)
#define  CHN_LB_H                                (40*4/3)

#define  CHN_LB_ELEM_H                           (40*4/3)
#define  CHN_LB_COL_PREV_W                       (60*4/3)
#define  CHN_LB_COL_LEFT_W                       (10*4/3)
#define  CHN_LB_COL_CRNT_W                       (CHN_LB_W - 2*CHN_LB_COL_PREV_W - 2* CHN_LB_COL_LEFT_W)
#define  CHN_LB_COL_RIGHT_W                      (10*4/3)
#define  CHN_LB_COL_NEXT_W                       (60*4/3)

#define  CHN_LB_COL_PREV_FNT_SIZE                FE_FNT_SIZE_MEDIUM
#define  CHN_LB_COL_CRNT_FNT_SIZE                FE_FNT_SIZE_MEDIUM 
#define  CHN_LB_COL_NEXT_FNT_SIZE                FE_FNT_SIZE_MEDIUM
#define  CHN_LB_COL_PREV_ALIGN                   WGL_AS_LEFT_CENTER
#define  CHN_LB_COL_LEFT_ALIGN                   WGL_AS_CENTER_CENTER
#define  CHN_LB_COL_CRNT_ALIGN                   WGL_AS_CENTER_CENTER
#define  CHN_LB_COL_RIGHT_ALIGN                  WGL_AS_CENTER_CENTER
#define  CHN_LB_COL_NEXT_ALIGN                   WGL_AS_RIGHT_CENTER

#define  CHN_LB_CNT_INSET_L                      (0)
#define  CHN_LB_CNT_INSET_R                      (0)
#define  CHN_LB_CNT_INSET_T                      (0)
#define  CHN_LB_CNT_INSET_B                      (0)
#define  CHN_LB_ELEM_INSET_L                     (0)
#define  CHN_LB_ELEM_INSET_R                     (0)
#define  CHN_LB_ELEM_INSET_T                     (0)
#define  CHN_LB_ELEM_INSET_B                     (0)
#define  CHN_LB_COL_PREV_INSET_L                 (0)
#define  CHN_LB_COL_PREV_INSET_R                 (0)
#define  CHN_LB_COL_PREV_INSET_T                 (0)
#define  CHN_LB_COL_PREV_INSET_B                 (0)
#define  CHN_LB_COL_LEFT_INSET_L                 (0)
#define  CHN_LB_COL_LEFT_INSET_R                 (0)
#define  CHN_LB_COL_LEFT_INSET_T                 (0)
#define  CHN_LB_COL_LEFT_INSET_B                 (0)
#define  CHN_LB_COL_CRNT_INSET_L                 (0)
#define  CHN_LB_COL_CRNT_INSET_R                 (0)
#define  CHN_LB_COL_CRNT_INSET_T                 (0)
#define  CHN_LB_COL_CRNT_INSET_B                 (0)
#define  CHN_LB_COL_RIGHT_INSET_L                (0)
#define  CHN_LB_COL_RIGHT_INSET_R                (0)
#define  CHN_LB_COL_RIGHT_INSET_T                (0)
#define  CHN_LB_COL_RIGHT_INSET_B                (0)
#define  CHN_LB_COL_NEXT_INSET_L                 (0)
#define  CHN_LB_COL_NEXT_INSET_R                 (0)
#define  CHN_LB_COL_NEXT_INSET_T                 (0)
#define  CHN_LB_COL_NEXT_INSET_B                 (0)
#define  CHN_LB_IMG_BK                           h_g_epg_img_trans


/*
   Program list.
*/

#ifdef APP_IMG_UI
    #define  PRG_LB_X                        (BASE_FRM_X + 39)
    #define  PRG_LB_Y                        (BASE_FRM_Y + 93)
    #define  PRG_LB_W                        (877)
    #define  PRG_LB_H                        (265)

    #define  PRG_LB_TITLE_X                  (0)
    #define  PRG_LB_TITLE_Y                  (0)
    #define  PRG_LB_TITLE_W                  (0)
    #define  PRG_LB_TITLE_H                  (0)
    #define  PRG_LB_TITLE_ALIGN              WGL_AS_CENTER_TOP
    #define  PRG_LB_TITLE_FNT_SIZE           FE_FNT_SIZE_LARGE
    #define  PRG_LB_ELEM_H                   (49)
    #define  PRG_LB_COL_DATE_W               (115*4/3)
    #define  PRG_LB_COL_TIME_W               (100*4/3)

    #ifndef APP_EPG_ICON_SEP

        #define  PRG_LB_COL_NUM              (5)
        #define  PRG_LB_COL_TITLE_W          (400*4/3)
        #define  PRG_LB_COL_LOCK_W           (5*4/3)
        #define  PRG_LB_COL_CC_W             (30*4/3)

        #define  PRG_LB_COL_LOCK_ALIGN       WGL_AS_CENTER_CENTER
        #define  PRG_LB_COL_CC_ALIGN         WGL_AS_CENTER_CENTER
        #define  PRG_LB_COL_LOCK_INSET_L     (0)
        #define  PRG_LB_COL_LOCK_INSET_R     (0)
        #define  PRG_LB_COL_LOCK_INSET_T     (0)
        #define  PRG_LB_COL_LOCK_INSET_B     (0)
        #define  PRG_LB_COL_CC_INSET_L       (0)
        #define  PRG_LB_COL_CC_INSET_R       (0)
        #define  PRG_LB_COL_CC_INSET_T       (0)
        #define  PRG_LB_COL_CC_INSET_B       (0)

    #else /* #ifdef APP_EPG_ICON_SEP */

        #define  PRG_LB_COL_NUM              (3)
        #define  PRG_LB_COL_TITLE_W          (660 * EPG_UI_RATIO_W)

    #endif /* APP_EPG_ICON_SEP */

    #define  PRG_LB_COL_DATE_FNT_SIZE        FE_FNT_SIZE_SMALL
    #define  PRG_LB_COL_TIME_FNT_SIZE        FE_FNT_SIZE_SMALL
    #define  PRG_LB_COL_TITLE_FNT_SIZE       FE_FNT_SIZE_SMALL
    #define  PRG_LB_COL_DATE_ALIGN           WGL_AS_LEFT_CENTER
    #define  PRG_LB_COL_TIME_ALIGN           WGL_AS_LEFT_CENTER
    #define  PRG_LB_COL_TITLE_ALIGN          WGL_AS_LEFT_CENTER
    #define  PRG_LB_BDR_INSET_L              (0)
    #define  PRG_LB_BDR_INSET_R              (0)
    #define  PRG_LB_BDR_INSET_T              (0)
    #define  PRG_LB_BDR_INSET_B              (0)
    #define  PRG_LB_CNT_INSET_L              (0)
    #define  PRG_LB_CNT_INSET_R              (0)
    #define  PRG_LB_CNT_INSET_T              (0)
    #define  PRG_LB_CNT_INSET_B              (0)

    #define  PRG_LB_ELEM_INSET_L             (0)
    #define  PRG_LB_ELEM_INSET_R             (0)
    #define  PRG_LB_ELEM_INSET_T             (0)
    #define  PRG_LB_ELEM_INSET_B             (0)
    #define  PRG_LB_COL_DATE_INSET_L         (10*4/3)
    #define  PRG_LB_COL_TIME_ALIGN           WGL_AS_LEFT_CENTER
    #define  PRG_LB_COL_DATE_INSET_R         (0)
    #define  PRG_LB_COL_DATE_INSET_T         (0)
    #define  PRG_LB_COL_DATE_INSET_B         (0)
    #define  PRG_LB_COL_TIME_INSET_L         (10*4/3)
    #define  PRG_LB_COL_TIME_INSET_R         (0)
    #define  PRG_LB_COL_TIME_INSET_T         (0)
    #define  PRG_LB_COL_TIME_INSET_B         (0)
    #define  PRG_LB_COL_TITLE_INSET_L        (10*4/3)
    #define  PRG_LB_COL_TITLE_INSET_R        (0)
    #define  PRG_LB_COL_TITLE_INSET_T        (0)
    #define  PRG_LB_COL_TITLE_INSET_B        (0)
    #define  PRG_LB_IMG_BK                   h_g_epg_img_program_frm
    #define  PRG_LB_IMG_SCROLL_BAR           h_g_epg_img_scroll_bar
    #define  PRG_LB_IMG_SCROLL_UP_X          ((PRG_LB_W / 2) - 5 * EPG_UI_RATIO_W)
    #define  PRG_LB_IMG_SCROLL_UP_Y          (0 * EPG_UI_RATIO_H)
    #define  PRG_LB_IMG_SCROLL_DOWN_X        ((PRG_LB_W / 2) - 5 * EPG_UI_RATIO_W)
    #define  PRG_LB_IMG_SCROLL_DOWN_Y        (PRG_LB_H - 13*4/3)
    #define  PRG_LB_IMG_SCROLL_UP_ENABLE     h_g_epg_img_arrow_up_enable
    #define  PRG_LB_IMG_SCROLL_UP_DISABLE    NULL_HANDLE
    #define  PRG_LB_IMG_SCROLL_DOWN_ENABLE   h_g_epg_img_arrow_down_enable
    #define  PRG_LB_IMG_SCROLL_DOWN_DISABLE  NULL_HANDLE

#else /* #ifndef APP_IMG_UI */

    #define  PRG_LB_X                        (0)
    #define  PRG_LB_Y                        (160 * EPG_UI_RATIO_H)
    #define  PRG_LB_W                        MAIN_FRM_W
    #define  PRG_LB_H                        (260 * EPG_UI_RATIO_H)
    #define  PRG_LB_TITLE_X                  (0)
    #define  PRG_LB_TITLE_Y                  (0)
    #define  PRG_LB_TITLE_W                  (0)
    #define  PRG_LB_TITLE_H                  (0)
    #define  PRG_LB_TITLE_ALIGN              WGL_AS_CENTER_TOP
    #define  PRG_LB_TITLE_FNT_SIZE           FE_FNT_SIZE_LARGE
    #define  PRG_LB_ELEM_H                   (40 * EPG_UI_RATIO_H)
    #define  PRG_LB_COL_DATE_W               (300 * EPG_UI_RATIO_W)
    #define  PRG_LB_COL_TIME_W               (180 * EPG_UI_RATIO_W)

    #ifndef APP_EPG_ICON_SEP

        #define  PRG_LB_COL_NUM              (5)
        #define  PRG_LB_COL_TITLE_W          (570 * EPG_UI_RATIO_W)
        #define  PRG_LB_COL_LOCK_W           (40 * EPG_UI_RATIO_W)
        #define  PRG_LB_COL_CC_W             (50 * EPG_UI_RATIO_W)
        #define  PRG_LB_COL_LOCK_ALIGN       WGL_AS_CENTER_CENTER
        #define  PRG_LB_COL_CC_ALIGN         WGL_AS_CENTER_CENTER
        #define  PRG_LB_COL_LOCK_INSET_L     (0)
        #define  PRG_LB_COL_LOCK_INSET_R     (0)
        #define  PRG_LB_COL_LOCK_INSET_T     (0)
        #define  PRG_LB_COL_LOCK_INSET_B     (0)
        #define  PRG_LB_COL_CC_INSET_L       (0)
        #define  PRG_LB_COL_CC_INSET_R       (0)
        #define  PRG_LB_COL_CC_INSET_T       (0)
        #define  PRG_LB_COL_CC_INSET_B       (0)

    #else /* #ifdef APP_EPG_ICON_SEP */

        #define  PRG_LB_COL_NUM              (3)
        #define  PRG_LB_COL_TITLE_W          (660 * EPG_UI_RATIO_W)

    #endif /* APP_EPG_ICON_SEP */

    #define  PRG_LB_COL_DATE_FNT_SIZE        FE_FNT_SIZE_MEDIUM
    #define  PRG_LB_COL_TIME_FNT_SIZE        FE_FNT_SIZE_MEDIUM
    #define  PRG_LB_COL_TITLE_FNT_SIZE       FE_FNT_SIZE_MEDIUM
    #define  PRG_LB_COL_DATE_ALIGN           WGL_AS_LEFT_CENTER
    #define  PRG_LB_COL_TIME_ALIGN           WGL_AS_RIGHT_CENTER
    #define  PRG_LB_COL_TITLE_ALIGN          WGL_AS_LEFT_CENTER
    #define  PRG_LB_BDR_INSET_L              (0)
    #define  PRG_LB_BDR_INSET_R              (0)
    #define  PRG_LB_BDR_INSET_T              (0)
    #define  PRG_LB_BDR_INSET_B              (0)
    #define  PRG_LB_CNT_INSET_L              (0)
    #define  PRG_LB_CNT_INSET_R              (0)
    #define  PRG_LB_CNT_INSET_T              (10 * EPG_UI_RATIO_H)
    #define  PRG_LB_CNT_INSET_B              (10 * EPG_UI_RATIO_H)
    #define  PRG_LB_ELEM_INSET_L             (0)
    #define  PRG_LB_ELEM_INSET_R             (0)
    #define  PRG_LB_ELEM_INSET_T             (0)
    #define  PRG_LB_ELEM_INSET_B             (2 * EPG_UI_RATIO_H)
    #define  PRG_LB_COL_DATE_INSET_L         (140 * EPG_UI_RATIO_W)
    #define  PRG_LB_COL_DATE_INSET_R         (0)
    #define  PRG_LB_COL_DATE_INSET_T         (0)
    #define  PRG_LB_COL_DATE_INSET_B         (0)
    #define  PRG_LB_COL_TIME_INSET_L         (0)
    #define  PRG_LB_COL_TIME_INSET_R         (25 * EPG_UI_RATIO_W)
    #define  PRG_LB_COL_TIME_INSET_T         (0)
    #define  PRG_LB_COL_TIME_INSET_B         (0)
    #define  PRG_LB_COL_TITLE_INSET_L        (0)
    #define  PRG_LB_COL_TITLE_INSET_R        (0)
    #define  PRG_LB_COL_TITLE_INSET_T        (0)
    #define  PRG_LB_COL_TITLE_INSET_B        (0)
    #define  PRG_LB_IMG_BK                   h_g_epg_img_trans
    #define  PRG_LB_IMG_SCROLL_BAR           h_g_epg_img_trans
    #define  PRG_LB_IMG_SCROLL_UP_X          ((PRG_LB_W / 2) - 5 * EPG_UI_RATIO_W)
    #define  PRG_LB_IMG_SCROLL_UP_Y          (2 * EPG_UI_RATIO_H)
    #define  PRG_LB_IMG_SCROLL_DOWN_X        ((PRG_LB_W / 2) - 5 * EPG_UI_RATIO_W)
    #define  PRG_LB_IMG_SCROLL_DOWN_Y        (PRG_LB_H - 8 * EPG_UI_RATIO_H)
    #define  PRG_LB_IMG_SCROLL_UP_ENABLE     h_g_epg_img_arrow_up_enable
    #define  PRG_LB_IMG_SCROLL_UP_DISABLE    NULL_HANDLE
    #define  PRG_LB_IMG_SCROLL_DOWN_ENABLE   h_g_epg_img_arrow_down_enable
    #define  PRG_LB_IMG_SCROLL_DOWN_DISABLE  NULL_HANDLE

#endif /* APP_IMG_UI */


/*
   Surfing list.
*/
#ifdef APP_IMG_UI

    #define  SURF_LB_X                           (130 * EPG_UI_RATIO_W - SURF_LB_BDR_INSET_L)
    #define  SURF_LB_Y                           (105 * EPG_UI_RATIO_H - SURF_LB_BDR_INSET_T)
    #define  SURF_LB_W                           (375 * EPG_UI_RATIO_W + 2 * SURF_LB_BDR_INSET_L)
    #define  SURF_LB_H                           (505 * EPG_UI_RATIO_H + 2 * SURF_LB_BDR_INSET_T)
    #define  SURF_LB_ELEM_H                      (40 * EPG_UI_RATIO_H)
    #define  SURF_LB_TITLE_X                     (0)
    #define  SURF_LB_TITLE_Y                     (15 * EPG_UI_RATIO_H)
    #define  SURF_LB_TITLE_W                     SURF_LB_W
    #define  SURF_LB_TITLE_H                     (45 * EPG_UI_RATIO_H)
    #define  SURF_LB_TITLE_ALIGN                 WGL_AS_CENTER_BOTTOM
    #define  SURF_LB_TITLE_FNT_SIZE              FE_FNT_SIZE_LARGE
    #define  SURF_LB_COL_NO_W                    (160 * EPG_UI_RATIO_W)
    #define  SURF_LB_COL_NAME_W                  (195 * EPG_UI_RATIO_W)
    #define  SURF_LB_COL_NO_FNT_SIZE             FE_FNT_SIZE_MEDIUM
    #define  SURF_LB_COL_NAME_FNT_SIZE           FE_FNT_SIZE_MEDIUM
    #define  SURF_LB_COL_NO_ALIGN                WGL_AS_CENTER_CENTER
    #define  SURF_LB_COL_NAME_ALIGN              WGL_AS_LEFT_CENTER
    #define  SURF_LB_BDR_INSET_L                 (4 * EPG_UI_RATIO_W)
    #define  SURF_LB_BDR_INSET_R                 (4 * EPG_UI_RATIO_W)
    #define  SURF_LB_BDR_INSET_T                 (4 * EPG_UI_RATIO_H)
    #define  SURF_LB_BDR_INSET_B                 (4 * EPG_UI_RATIO_H)
    #define  SURF_LB_CNT_INSET_L                 (10 * EPG_UI_RATIO_W)
    #define  SURF_LB_CNT_INSET_R                 (10 * EPG_UI_RATIO_W)
    #define  SURF_LB_CNT_INSET_T                 (70 * EPG_UI_RATIO_H)
    #define  SURF_LB_CNT_INSET_B                 (230 * EPG_UI_RATIO_H)
    #define  SURF_LB_ELEM_INSET_L                (0)
    #define  SURF_LB_ELEM_INSET_R                (0)
    #define  SURF_LB_ELEM_INSET_T                (0)
    #define  SURF_LB_ELEM_INSET_B                (2 * EPG_UI_RATIO_H)
    #define  SURF_LB_COL_NO_INSET_L              (10 * EPG_UI_RATIO_W)
    #define  SURF_LB_COL_NO_INSET_R              (0)
    #define  SURF_LB_COL_NO_INSET_T              (0)
    #define  SURF_LB_COL_NO_INSET_B              (0)
    #define  SURF_LB_COL_NAME_INSET_L            (0)
    #define  SURF_LB_COL_NAME_INSET_R            (0)
    #define  SURF_LB_COL_NAME_INSET_T            (0)
    #define  SURF_LB_COL_NAME_INSET_B            (0)
    #define  SURF_LB_IMG_BK                      h_g_epg_img_program_frm
    #define  SURF_LB_IMG_SCROLL_BAR              NULL_HANDLE
    #define  SURF_LB_IMG_SCROLL_UP_X             ((SURF_LB_W / 2) - 9 * EPG_UI_RATIO_W)
    #define  SURF_LB_IMG_SCROLL_UP_Y             (51 * EPG_UI_RATIO_H + SURF_LB_BDR_INSET_T)
    #define  SURF_LB_IMG_SCROLL_DOWN_X           ((SURF_LB_W / 2) - 9 * EPG_UI_RATIO_W)
    #define  SURF_LB_IMG_SCROLL_DOWN_Y           (270 * EPG_UI_RATIO_H + SURF_LB_BDR_INSET_T)
    #define  SURF_LB_IMG_SCROLL_UP_ENABLE        h_g_epg_img_arrow_up_enable
    #define  SURF_LB_IMG_SCROLL_UP_DISABLE       NULL_HANDLE
    #define  SURF_LB_IMG_SCROLL_DOWN_ENABLE      h_g_epg_img_arrow_down_enable
    #define  SURF_LB_IMG_SCROLL_DOWN_DISABLE     NULL_HANDLE

#else /* #ifndef APP_IMG_UI */

    #define  SURF_LB_X                           (130 * EPG_UI_RATIO_W - SURF_LB_BDR_INSET_L)
    #define  SURF_LB_Y                           (120 * EPG_UI_RATIO_H - SURF_LB_BDR_INSET_T)
    #define  SURF_LB_W                           (375 * EPG_UI_RATIO_W + 2 * SURF_LB_BDR_INSET_L)
    #define  SURF_LB_H                           (485 * EPG_UI_RATIO_H + 2 * SURF_LB_BDR_INSET_T)
    #define  SURF_LB_ELEM_H                      (40 * EPG_UI_RATIO_H)
    #define  SURF_LB_TITLE_X                     (0)
    #define  SURF_LB_TITLE_Y                     (0)
    #define  SURF_LB_TITLE_W                     SURF_LB_W
    #define  SURF_LB_TITLE_H                     (35 * EPG_UI_RATIO_H)
    #define  SURF_LB_TITLE_ALIGN                 WGL_AS_CENTER_TOP
    #define  SURF_LB_TITLE_FNT_SIZE              FE_FNT_SIZE_LARGE
    #define  SURF_LB_COL_NO_W                    (160 * EPG_UI_RATIO_W)
    #define  SURF_LB_COL_NAME_W                  (195 * EPG_UI_RATIO_W)
    #define  SURF_LB_COL_NO_FNT_SIZE             FE_FNT_SIZE_MEDIUM
    #define  SURF_LB_COL_NAME_FNT_SIZE           FE_FNT_SIZE_MEDIUM
    #define  SURF_LB_COL_NO_ALIGN                WGL_AS_CENTER_CENTER
    #define  SURF_LB_COL_NAME_ALIGN              WGL_AS_LEFT_CENTER
    #define  SURF_LB_BDR_INSET_L                 (4 * EPG_UI_RATIO_W)
    #define  SURF_LB_BDR_INSET_R                 (4 * EPG_UI_RATIO_W)
    #define  SURF_LB_BDR_INSET_T                 (4 * EPG_UI_RATIO_H)
    #define  SURF_LB_BDR_INSET_B                 (4 * EPG_UI_RATIO_H)
    #define  SURF_LB_CNT_INSET_L                 (10 * EPG_UI_RATIO_W)
    #define  SURF_LB_CNT_INSET_R                 (10 * EPG_UI_RATIO_W)
    #define  SURF_LB_CNT_INSET_T                 (55 * EPG_UI_RATIO_H)
    #define  SURF_LB_CNT_INSET_B                 (230 * EPG_UI_RATIO_H)
    #define  SURF_LB_ELEM_INSET_L                (0)
    #define  SURF_LB_ELEM_INSET_R                (0)
    #define  SURF_LB_ELEM_INSET_T                (0)
    #define  SURF_LB_ELEM_INSET_B                (2 * EPG_UI_RATIO_H)
    #define  SURF_LB_COL_NO_INSET_L              (10 * EPG_UI_RATIO_W)
    #define  SURF_LB_COL_NO_INSET_R              (0)
    #define  SURF_LB_COL_NO_INSET_T              (0)
    #define  SURF_LB_COL_NO_INSET_B              (0)
    #define  SURF_LB_COL_NAME_INSET_L            (0)
    #define  SURF_LB_COL_NAME_INSET_R            (0)
    #define  SURF_LB_COL_NAME_INSET_T            (0)
    #define  SURF_LB_COL_NAME_INSET_B            (0)
    #define  SURF_LB_IMG_BK                      h_g_epg_img_trans
    #define  SURF_LB_IMG_SCROLL_BAR              h_g_epg_img_trans
    #define  SURF_LB_IMG_SCROLL_UP_X             ((SURF_LB_W / 2) - 9 * EPG_UI_RATIO_W)
    #define  SURF_LB_IMG_SCROLL_UP_Y             (36 * EPG_UI_RATIO_H + SURF_LB_BDR_INSET_T)
    #define  SURF_LB_IMG_SCROLL_DOWN_X           ((SURF_LB_W / 2) - 9 * EPG_UI_RATIO_W)
    #define  SURF_LB_IMG_SCROLL_DOWN_Y           (255 * EPG_UI_RATIO_H + SURF_LB_BDR_INSET_T)
    #define  SURF_LB_IMG_SCROLL_UP_ENABLE        h_g_epg_img_arrow_up_enable
    #define  SURF_LB_IMG_SCROLL_UP_DISABLE       NULL_HANDLE
    #define  SURF_LB_IMG_SCROLL_DOWN_ENABLE      h_g_epg_img_arrow_down_enable
    #define  SURF_LB_IMG_SCROLL_DOWN_DISABLE     NULL_HANDLE

#endif /* APP_IMG_UI */


/*
   Icon list.
*/


#define  ICON_LB_X                           (DESC_FRM_W-ICON_LB_W)
#define  ICON_LB_Y                           (DESC_FRM_H-ICON_LB_H)
#define  ICON_LB_W                           (90 * EPG_UI_RATIO_W)
#define  ICON_LB_H                           (40 * EPG_UI_RATIO_H)
#define  ICON_LB_ELEM_H                      (40 * EPG_UI_RATIO_H)
#define  ICON_LB_COL_LOCK_W                  (40 * EPG_UI_RATIO_W)
#define  ICON_LB_COL_CC_W                    (50 * EPG_UI_RATIO_W)
#define  ICON_LB_COL_LOCK_ALIGN              WGL_AS_CENTER_CENTER
#define  ICON_LB_COL_CC_ALIGN                WGL_AS_CENTER_CENTER
#define  ICON_LB_CNT_INSET_L                 (0)
#define  ICON_LB_CNT_INSET_R                 (0)
#define  ICON_LB_CNT_INSET_T                 (0)
#define  ICON_LB_CNT_INSET_B                 (0)
#define  ICON_LB_ELEM_INSET_L                (0)
#define  ICON_LB_ELEM_INSET_R                (0)
#define  ICON_LB_ELEM_INSET_T                (0)
#define  ICON_LB_ELEM_INSET_B                (0)
#define  ICON_LB_COL_LOCK_INSET_L            (0)
#define  ICON_LB_COL_LOCK_INSET_R            (0)
#define  ICON_LB_COL_LOCK_INSET_T            (0)
#define  ICON_LB_COL_LOCK_INSET_B            (0)
#define  ICON_LB_COL_CC_INSET_L              (0)
#define  ICON_LB_COL_CC_INSET_R              (0)
#define  ICON_LB_COL_CC_INSET_T              (0)
#define  ICON_LB_COL_CC_INSET_B              (0)
#define  ICON_LB_IMG_BK                      h_g_epg_img_trans




/*
   Description list.
*/


#define  DESC_LB_X                           (80*4/3)
#define  DESC_LB_Y                           (0)
#define  DESC_LB_W                           (480 * EPG_UI_RATIO_W)
#define  DESC_LB_H                           (40 * EPG_UI_RATIO_H)
#define  DESC_LB_ELEM_H                      (40 * EPG_UI_RATIO_H)
#ifdef APP_EPG_FULL_VIDEO
    #define  DESC_LB_COL_TIME_W              (300 * EPG_UI_RATIO_W)
#else
#ifdef APP_EPG_MODIFY_DISPLAY_TIME
    #define  DESC_LB_COL_TIME_W              (108 * EPG_UI_RATIO_W)
#else
    #define  DESC_LB_COL_TIME_W              (120 * EPG_UI_RATIO_W)
#endif
    #endif
#define  DESC_LB_COL_CA_W                    (DESC_LB_W - DESC_LB_COL_TIME_W)
#define  DESC_LB_COL_TIME_FNT_SIZE           FE_FNT_SIZE_SMALL 
#define  DESC_LB_COL_CA_FNT_SIZE             FE_FNT_SIZE_SMALL 
#define  DESC_LB_COL_TIME_ALIGN              WGL_AS_LEFT_CENTER
#define  DESC_LB_COL_CA_ALIGN                WGL_AS_LEFT_CENTER
#define  DESC_LB_CNT_INSET_L                 (0)
#define  DESC_LB_CNT_INSET_R                 (0)
#define  DESC_LB_CNT_INSET_T                 (0)
    #define  DESC_LB_CNT_INSET_B                 (3 * EPG_UI_RATIO_H)
#define  DESC_LB_ELEM_INSET_L                (0)
#define  DESC_LB_ELEM_INSET_R                (0)
#define  DESC_LB_ELEM_INSET_T                (0)
#define  DESC_LB_ELEM_INSET_B                (0)
#define  DESC_LB_COL_TIME_INSET_L            (10 * EPG_UI_RATIO_W)
#define  DESC_LB_COL_TIME_INSET_R            (0)
#define  DESC_LB_COL_TIME_INSET_T            (0)
#define  DESC_LB_COL_TIME_INSET_B            (0)
#define  DESC_LB_COL_CA_INSET_L              (0)
#define  DESC_LB_COL_CA_INSET_R              (10 * EPG_UI_RATIO_W)
#define  DESC_LB_COL_CA_INSET_T              (0)
#define  DESC_LB_COL_CA_INSET_B              (0)
#define  DESC_LB_IMG_BK                      h_g_epg_img_trans




/*
   Help list.
*/
#define APP_NO_COLOR_KEY
#define  HELP_LB_X                           (BASE_FRM_X + 8)
#define  HELP_LB_Y                           (BASE_FRM_Y + BASE_FRM_H - 75)
#define  HELP_LB_W                           (BASE_FRM_W - 80)
#define  HELP_LB_H                           (50 * EPG_UI_RATIO_H)
#define  HELP_LB_ELEM_H                      (50 * EPG_UI_RATIO_H)
#define  HELP_LB_COL_IMG_W                   (50 * EPG_UI_RATIO_W)
#define  HELP_LB_COL_TEXT_W                  (170 * EPG_UI_RATIO_W)
#define  HELP_LB_COL_TEXT_FNT_SIZE           FE_FNT_SIZE_SMALL
#define  HELP_LB_COL_IMG_ALIGN               WGL_AS_CENTER_CENTER
#define  HELP_LB_CNT_INSET_L                 (0)
#define  HELP_LB_CNT_INSET_R                 (0)
#define  HELP_LB_CNT_INSET_T                 (0)
#define  HELP_LB_CNT_INSET_B                 (0)
#define  HELP_LB_ELEM_INSET_L                (0)
#define  HELP_LB_ELEM_INSET_R                (0)
#define  HELP_LB_ELEM_INSET_T                (0)
#define  HELP_LB_ELEM_INSET_B                (0)
#define  HELP_LB_COL_IMG_INSET_L             (0)
#define  HELP_LB_COL_IMG_INSET_R             (0)
#define  HELP_LB_COL_IMG_INSET_T             (0)
#define  HELP_LB_COL_IMG_INSET_B             (0)
#define  HELP_LB_COL_TEXT_INSET_L            (0)
#define  HELP_LB_COL_TEXT_INSET_R            (0)
#define  HELP_LB_COL_TEXT_INSET_T            (0)
#define  HELP_LB_COL_TEXT_INSET_B            (0)
#define  HELP_LB_IMG_BK                      h_g_epg_img_trans
#define  HELP_LB_IMG_BTN_RED_ENABLE          h_g_epg_img_btn_red
#define  HELP_LB_IMG_BTN_RED_DISABLE         h_g_epg_img_btn_red
#define  HELP_LB_IMG_BTN_GREEN_ENABLE        h_g_epg_img_btn_green
#define  HELP_LB_IMG_BTN_GREEN_DISABLE       h_g_epg_img_btn_green
#define  HELP_LB_IMG_BTN_YELLOW_ENABLE       h_g_epg_img_btn_yellow
#define  HELP_LB_IMG_BTN_YELLOW_DISABLE      h_g_epg_img_btn_yellow
#define  HELP_LB_IMG_BTN_BLUE_ENABLE         h_g_epg_img_btn_blue
#define  HELP_LB_IMG_BTN_BLUE_DISABLE        h_g_epg_img_btn_blue

#ifdef APP_EPG_HELP_LST_REVERSE

    #define  HELP_LB_COL_TEXT_ALIGN          WGL_AS_RIGHT_CENTER
    #define  HELP_LB_TXT_START_IDX           (0)
    #define  HELP_LB_IMG_START_IDX           (1)
    #define  HELP_LB_BTN_RED_TXT_IDX         (0)
    #define  HELP_LB_BTN_RED_IMG_IDX         (1)
    #define  HELP_LB_BTN_GREEN_TXT_IDX       (2)
    #define  HELP_LB_BTN_GREEN_IMG_IDX       (3)
    #define  HELP_LB_BTN_YELLOW_TXT_IDX      (4)
    #define  HELP_LB_BTN_YELLOW_IMG_IDX      (5)
    #define  HELP_LB_BTN_BLUE_TXT_IDX        (6)
    #define  HELP_LB_BTN_BLUE_IMG_IDX        (7)

#else /* #ifndef APP_EPG_HELP_LST_REVERSE    */

    #define  HELP_LB_COL_TEXT_ALIGN          WGL_AS_LEFT_CENTER
    #define  HELP_LB_IMG_START_IDX           (0)
    #define  HELP_LB_TXT_START_IDX           (1)
    #define  HELP_LB_BTN_RED_IMG_IDX         (0)
    #define  HELP_LB_BTN_RED_TXT_IDX         (1)
    #define  HELP_LB_BTN_GREEN_IMG_IDX       (2)
    #define  HELP_LB_BTN_GREEN_TXT_IDX       (3)
    #define  HELP_LB_BTN_YELLOW_IMG_IDX      (4)
    #define  HELP_LB_BTN_YELLOW_TXT_IDX      (5)
    #define  HELP_LB_BTN_BLUE_IMG_IDX        (6)
    #define  HELP_LB_BTN_BLUE_TXT_IDX        (7)

#endif /* APP_EPG_HELP_LST_REVERSE */




/*
    Page index text.
*/


#ifdef APP_EPG_ICON_SEP

    #define  PAGE_TXT_X                      (DESC_FRM_W / 2 - PAGE_TXT_W / 2)
    #define  PAGE_TXT_Y                      (DESC_FRM_H - PAGE_TXT_H)
    #define  PAGE_TXT_W                      (100 * EPG_UI_RATIO_W)
    #define  PAGE_TXT_H                      (30 * EPG_UI_RATIO_H)
    #define  PAGE_TXT_FNT_SIZE               FE_FNT_SIZE_SMALL
    #define  PAGE_TXT_ALIGN                  WGL_AS_CENTER_BOTTOM
    #define  PAGE_TXT_INSET_L                (0)
    #define  PAGE_TXT_INSET_R                (0)
    #define  PAGE_TXT_INSET_T                (0)
    #define  PAGE_TXT_INSET_B                (0)
    #define  PAGE_TXT_IMG_BK                 h_g_epg_img_trans

#else /* #ifndef APP_EPG_ICON_SEP */

    #define  PAGE_TXT_X                      (DESC_FRM_W - PAGE_TXT_W)
    #define  PAGE_TXT_Y                      (DESC_FRM_H - PAGE_TXT_H)
    #define  PAGE_TXT_W                      (100 * EPG_UI_RATIO_W)
    #define  PAGE_TXT_H                      (30 * EPG_UI_RATIO_H)
    #define  PAGE_TXT_FNT_SIZE               FE_FNT_SIZE_SMALL
    #define  PAGE_TXT_ALIGN                  WGL_AS_RIGHT_BOTTOM
    #define  PAGE_TXT_INSET_L                (0)
    #define  PAGE_TXT_INSET_R                (10 * EPG_UI_RATIO_W)
    #define  PAGE_TXT_INSET_T                (0)
    #define  PAGE_TXT_INSET_B                (0)
    #define  PAGE_TXT_IMG_BK                 h_g_epg_img_trans

#endif /* APP_EPG_ICON_SEP */


/*
   Channel text.
*/
#ifndef APP_NO_COLOR_KEY

    #define  CHN_TXT_X                           (0)
    #define  CHN_TXT_Y                           (600 * EPG_UI_RATIO_H)
    #define  CHN_TXT_W                           (450 * EPG_UI_RATIO_W)
    #define  CHN_TXT_H                           (50 * EPG_UI_RATIO_H)
    #define  CHN_TXT_FNT_SIZE                    FE_FNT_SIZE_MEDIUM
    #define  CHN_TXT_ALIGN                       WGL_AS_CENTER_CENTER
    #define  CHN_TXT_INSET_L                     (110 * EPG_UI_RATIO_W)
    #define  CHN_TXT_INSET_R                     (0)
    #define  CHN_TXT_INSET_T                     (0)
    #define  CHN_TXT_INSET_B                     (0)
    #define  CHN_TXT_IMG_BK                      h_g_epg_img_trans

#else /* #ifdef APP_NO_COLOR_KEY */

    #define  CHN_TXT_X                           (0)
    #define  CHN_TXT_Y                           (600 * EPG_UI_RATIO_H)
    #define  CHN_TXT_W                           MAIN_FRM_W
    #define  CHN_TXT_H                           (50 * EPG_UI_RATIO_H)
    #define  CHN_TXT_FNT_SIZE                    FE_FNT_SIZE_MEDIUM
    #define  CHN_TXT_ALIGN                       WGL_AS_CENTER_CENTER
    #define  CHN_TXT_INSET_L                     (110 * EPG_UI_RATIO_W)
    #define  CHN_TXT_INSET_R                     (830 * EPG_UI_RATIO_W)
    #define  CHN_TXT_INSET_T                     (0)
    #define  CHN_TXT_INSET_B                     (0)
    #define  CHN_TXT_IMG_BK                      h_g_epg_img_trans

#endif /* APP_NO_COLOR_KEY */


/*
   Program text.
*/

#define  PRG_TXT_X                           (0)
#define  PRG_TXT_Y                           (PRG_LB_Y + PRG_LB_CNT_INSET_T)
#define  PRG_TXT_W                           MAIN_FRM_W
#define  PRG_TXT_H                           PRG_LB_ELEM_H
#define  PRG_TXT_FNT_SIZE                    FE_FNT_SIZE_SMALL
#define  PRG_TXT_ALIGN                       WGL_AS_CENTER_CENTER
#define  PRG_TXT_INSET_L                     (0)
#define  PRG_TXT_INSET_R                     (0)
#define  PRG_TXT_INSET_T                     (0)
#define  PRG_TXT_INSET_B                     (0)


/*
   Direct channel input (DCI) hyper text.
*/
#define  DCI_HTS_X                               (CHN_LB_COL_PREV_W + CHN_LB_COL_LEFT_W)
#if defined(APP_SLIM_RGB_IMG)
    #define  DCI_HTS_Y                           (CHN_LB_Y - 1)
#else
    #define  DCI_HTS_Y                           CHN_LB_Y
#endif
#define  DCI_HTS_W                               CHN_LB_COL_CRNT_W
#define  DCI_HTS_H                               CHN_LB_ELEM_H
#define  DCI_HTS_FNT_SIZE                        FE_FNT_SIZE_LARGE
#define  DCI_HTS_ALIGN                           WGL_AS_CENTER_CENTER
#define  DCI_HTS_INSET_L                         (0)
#define  DCI_HTS_INSET_R                         (0)
#define  DCI_HTS_INSET_T                         (0)
#define  DCI_HTS_INSET_B                         (0)


/*
   Time text.
*/
#define  TIME_TXT_X                          (BASE_FRM_X + 45*4/3)
#define  TIME_TXT_Y                          (BASE_FRM_Y + 10)
#define  TIME_TXT_W                          (BASE_FRM_W - 45*4/3)
#define  TIME_TXT_H                          (32)
#define  TIME_TXT_FNT_SIZE                   FE_FNT_SIZE_SMALL
#define  TIME_TXT_ALIGN                      WGL_AS_RIGHT_CENTER
#define  TIME_TXT_INSET_L                    (0)
#define  TIME_TXT_INSET_R                    (40 * EPG_UI_RATIO_W)
#define  TIME_TXT_INSET_T                    (10 * EPG_UI_RATIO_H)
#define  TIME_TXT_INSET_B                    (0)
#define  TIME_TXT_IMG_BK                     h_g_epg_img_trans



/*
   Description text.
*/
#define  DESC_TXT_X                          (DESC_LB_X)
#define  DESC_TXT_Y                          (30*4/3)
#define  DESC_TXT_W                          (DESC_FRM_W - DESC_TXT_X)
#define  DESC_TXT_H                          (80 * EPG_UI_RATIO_H)
#define  DESC_TXT_FNT_SIZE                   FE_FNT_SIZE_SMALL
#define  DESC_TXT_ALIGN                      WGL_AS_LEFT_TOP
#define  DESC_TXT_INSET_L                    (10 * EPG_UI_RATIO_W)
#define  DESC_TXT_INSET_R                    (20 * EPG_UI_RATIO_W)
#define  DESC_TXT_INSET_T                    (0)
#define  DESC_TXT_INSET_B                    (0)
#define  DESC_TXT_IMG_BK                     h_g_epg_img_trans
#define  DESC_TXT_LINE_GAPS                  (-3 * EPG_UI_RATIO_H)
#define  DESC_TXT_LINES_PER_PAGE             (4)

#define  DESC_RATE_TXT_X                      (80*4/3)
#define  DESC_RATE_TXT_Y                      (0)
#define  DESC_RATE_TXT_W                      (DESC_FRM_W - 2*DESC_RATE_TXT_X)
#define  DESC_RATE_TXT_H                      (20*4/3)




/*
   Video text.
*/


#ifdef APP_IMG_UI

    #define  VIDEO_TXT_X                     (0)
    #define  VIDEO_TXT_Y                     (0)
    #define  VIDEO_TXT_W                     VIDEO_FRM_W
    #define  VIDEO_TXT_H                     VIDEO_FRM_H
    #ifdef APP_EPG_FULL_VIDEO
        #define  VIDEO_TXT_FNT_SIZE          FE_FNT_SIZE_MEDIUM
        #define  VIDEO_TXT_ALIGN             WGL_AS_LEFT_CENTER
    #else
        #define  VIDEO_TXT_FNT_SIZE          FE_FNT_SIZE_LARGE
        #define  VIDEO_TXT_ALIGN             WGL_AS_CENTER_CENTER
    #endif
    #define  VIDEO_TXT_INSET_L               (0)
    #define  VIDEO_TXT_INSET_R               (0)
    #define  VIDEO_TXT_INSET_T               (0)
    #define  VIDEO_TXT_INSET_B               (0)

#else /* #ifndef APP_IMG_UI */

    #define  VIDEO_TXT_X                     (0)
    #define  VIDEO_TXT_Y                     (0)
    #define  VIDEO_TXT_W                     VIDEO_FRM_W
    #define  VIDEO_TXT_H                     VIDEO_FRM_H
    #define  VIDEO_TXT_FNT_SIZE              FE_FNT_SIZE_LARGE
    #define  VIDEO_TXT_ALIGN                 WGL_AS_CENTER_CENTER
    #define  VIDEO_TXT_INSET_L               (0)
    #define  VIDEO_TXT_INSET_R               (0)
    #define  VIDEO_TXT_INSET_T               (0)
    #define  VIDEO_TXT_INSET_B               (0)

#endif /* APP_IMG_UI */


/*
   Retrieving icon.
*/
#define  RETRIEVE_ICON_X                         (BASE_FRM_X + 10)
#define  RETRIEVE_ICON_Y                         (BASE_FRM_Y + 10)
#define  RETRIEVE_ICON_W                         (53*4/3)
#define  RETRIEVE_ICON_H                         (48*4/3)
#define  RETRIEVE_ICON_ALIGN                     WGL_AS_CENTER_CENTER
#define  RETRIEVE_ICON_INSET_L                   (0)
#define  RETRIEVE_ICON_INSET_R                   (0)
#define  RETRIEVE_ICON_INSET_T                   (0)
#define  RETRIEVE_ICON_INSET_B                   (0)
#define  RETRIEVE_ICON_IMG_1                     h_g_epg_img_retrieve_1
#define  RETRIEVE_ICON_IMG_2                     h_g_epg_img_retrieve_2
#define  RETRIEVE_ICON_IMG_3                     NULL_HANDLE


#define  RETRIEVE_ICON_IMG_TBL          \
{                                       \
    h_g_epg_img_retrieve_1,             \
    h_g_epg_img_retrieve_2,             \
    h_g_epg_img_retrieve_3,             \
    h_g_epg_img_retrieve_4,             \
    h_g_epg_img_retrieve_5,             \
    h_g_epg_img_retrieve_6,             \
    h_g_epg_img_retrieve_7,             \
    h_g_epg_img_retrieve_8             \
}


/*
   Retrieving text.
*/
#define  RETRIEVE_TXT_X                          (0)
#define  RETRIEVE_TXT_Y                          (0 * EPG_UI_RATIO_H)
#define  RETRIEVE_TXT_W                          (700 * EPG_UI_RATIO_W)
#define  RETRIEVE_TXT_H                          (50 * EPG_UI_RATIO_H)
#define  RETRIEVE_TXT_FNT_SIZE                   FE_FNT_SIZE_SMALL
#define  RETRIEVE_TXT_ALIGN                      WGL_AS_LEFT_CENTER
#define  RETRIEVE_TXT_INSET_L                    (140 * EPG_UI_RATIO_W)
#define  RETRIEVE_TXT_INSET_R                    (0)
#define  RETRIEVE_TXT_INSET_T                    (10 * EPG_UI_RATIO_H)
#define  RETRIEVE_TXT_INSET_B                    (0)


/*
   Password text.
*/
#define  PASSWD_TXT_X                            (0)
#define  PASSWD_TXT_Y                            (0)
#define  PASSWD_TXT_W                            (200 * EPG_UI_RATIO_W)
#define  PASSWD_TXT_H                            PASSWD_FRM_H
#define  PASSWD_TXT_FNT_SIZE                     FE_FNT_SIZE_MEDIUM
#define  PASSWD_TXT_ALIGN                        WGL_AS_RIGHT_CENTER
#define  PASSWD_TXT_INSET_L                      (0)
#define  PASSWD_TXT_INSET_R                      (0)
#define  PASSWD_TXT_INSET_T                      (0)
#define  PASSWD_TXT_INSET_B                      (0)

#ifdef APP_EPG_FULL_VIDEO
#define  PASSWD_TXT_ALARM_X                            ((DESC_BK_FRM_W - PASSWD_TXT_ALARM_W)/2)
#define  PASSWD_TXT_ALARM_Y                            (DESC_BK_FRM_H - PASSWD_TXT_ALARM_H)
#define  PASSWD_TXT_ALARM_W                            (500 * EPG_UI_RATIO_W)
#define  PASSWD_TXT_ALARM_H                            (48 * EPG_UI_RATIO_H)
#define  PASSWD_TXT_ALARM_FNT_SIZE                     FE_FNT_SIZE_MEDIUM
#define  PASSWD_TXT_ALARM_ALIGN                        WGL_AS_CENTER_CENTER
#define  PASSWD_TXT_ALARM_INSET_L                      (0)
#define  PASSWD_TXT_ALARM_INSET_R                      (0)
#define  PASSWD_TXT_ALARM_INSET_T                      (0)
#define  PASSWD_TXT_ALARM_INSET_B                      (0)
#endif

/*
   Password edit.
*/
#ifdef APP_IMG_UI

    #define  PASSWD_EDIT_X                       (210 * EPG_UI_RATIO_W)
    #define  PASSWD_EDIT_Y                       (0)
    #define  PASSWD_EDIT_W                       (190 * EPG_UI_RATIO_W)
    #define  PASSWD_EDIT_H                       (PASSWD_FRM_H)
    #define  PASSWD_EDIT_MAX_WORD_LEN            (4)
    #define  PASSWD_EDIT_COMPLETE_DELAY          (200)
    #define  PASSWD_EDIT_FNT_SIZE                FE_FNT_SIZE_LARGE
    #define  PASSWD_EDIT_ALIGN                   WGL_AS_LEFT_CENTER
    #define  PASSWD_EDIT_BDR_INSET_L             (0)
    #define  PASSWD_EDIT_BDR_INSET_R             (0)
    #define  PASSWD_EDIT_BDR_INSET_T             (0)
    #define  PASSWD_EDIT_BDR_INSET_B             (0)
    #define  PASSWD_EDIT_CNT_INSET_L             (65 * EPG_UI_RATIO_W)
    #define  PASSWD_EDIT_CNT_INSET_R             (0)
    #define  PASSWD_EDIT_CNT_INSET_T             (6 * EPG_UI_RATIO_H)
    #define  PASSWD_EDIT_CNT_INSET_B             (0)
    #define  PASSWD_EDIT_IMG_BK                  NULL_HANDLE

#else /* #ifndef APP_IMG_UI */

    #define  PASSWD_EDIT_X                       (210 * EPG_UI_RATIO_W)
    #define  PASSWD_EDIT_Y                       (0)
    #define  PASSWD_EDIT_W                       (190 * EPG_UI_RATIO_W)
    #define  PASSWD_EDIT_H                       (PASSWD_FRM_H)
    #define  PASSWD_EDIT_MAX_WORD_LEN            (4)
    #define  PASSWD_EDIT_COMPLETE_DELAY          (200)
    #define  PASSWD_EDIT_FNT_SIZE                FE_FNT_SIZE_LARGE
    #define  PASSWD_EDIT_ALIGN                   WGL_AS_LEFT_CENTER
    #define  PASSWD_EDIT_BDR_INSET_L             (2 * EPG_UI_RATIO_W)
    #define  PASSWD_EDIT_BDR_INSET_R             (2 * EPG_UI_RATIO_W)
    #define  PASSWD_EDIT_BDR_INSET_T             (2 * EPG_UI_RATIO_H)
    #define  PASSWD_EDIT_BDR_INSET_B             (2 * EPG_UI_RATIO_H)
    #define  PASSWD_EDIT_CNT_INSET_L             (65 * EPG_UI_RATIO_W)
    #define  PASSWD_EDIT_CNT_INSET_R             (0)
    #define  PASSWD_EDIT_CNT_INSET_T             (6 * EPG_UI_RATIO_H)
    #define  PASSWD_EDIT_CNT_INSET_B             (0)
    #define  PASSWD_EDIT_IMG_BK                  h_g_epg_img_trans

#endif /* APP_IMG_UI */

/*
   The number of elements that the surfing/program list can display per page.
*/

#define  ELEM_VIEW_SIZE                      (5)


/*
   EPG font name.
*/
#define  EPG_FONT_NAME                           SN_FONT_DEFAULT

/*
   Retrieving states.
*/
#define  EPG_RETRIEVE_STATE                      (2)

/*
   Auto-pause timer delay.
*/
#ifdef APP_EPG_NO_AUTO_PAUSE

    #define  TIMER_DELAY_PAUSE                   (0)

#else /* #ifndef APP_EPG_NO_AUTO_PAUSE */

    #define  TIMER_DELAY_PAUSE                   (10000)/*(3*60000) */ /* 3 minutes */ 

#endif /* APP_EPG_NO_AUTO_PAUSE */


#endif /* _EPG_CONFIG_H_ */

