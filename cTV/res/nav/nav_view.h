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
 * $RCSfile: nav_view.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/11 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e4fca22a35d115b284d4931487730df1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_VIEW_H_
#define _NAV_VIEW_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_iom.h"
#include "u_sys_name.h"
#include "u_wgl_lb.h"

#include "amb/a_amb.h"

#include "res/nav/nav_colors.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/* when output OSD resolution is not the same as 960 * 540
 * 1. modify the NAV_WIDTH()'s factor to the proper one
 * 2. modify the NAV_HEIGHT()'s factor to the proper one
 * 3. modify all background images and icon images to the proper one
 */
#define NAV_WIDTH(__w)                  (__w*4/3) /* for 960 width  */
#define NAV_HEIGHT(__h)                 (__h*4/3) /* for 540 height */

#define DISPLAY_WIDTH                   NAV_WIDTH(960)
#define DISPLAY_HEIGHT                  NAV_HEIGHT(540)

/* DTV00000570 - change the safe area to be the same as ClosedCaption */
#define SAFE_DISPLAY_LEFT               (DISPLAY_WIDTH/10 - NAV_WIDTH(20))  /* add aditional 40 pixels for "Scrambled Video"*/
#define SAFE_DISPLAY_TOP                (DISPLAY_HEIGHT/10)
#define SAFE_DISPLAY_WIDTH              (DISPLAY_WIDTH - SAFE_DISPLAY_LEFT * 2)
#define SAFE_DISPLAY_HEIGHT             (DISPLAY_HEIGHT - SAFE_DISPLAY_TOP * 2)

#ifdef APP_CLRQAM_SUPPORT
#define CHNO_WIDTH                      NAV_WIDTH(300)
#define CHNO_HEIGHT                     NAV_HEIGHT(50)
#define CHNO_LEFT                       NAV_WIDTH(0)
#define CHNO_TOP                        NAV_HEIGHT(0)

#define CH_NAME_WIDTH                   CHNO_WIDTH
#define CH_NAME_HEIGHT                  NAV_HEIGHT(40)
#define CH_NAME_LEFT                    CHNO_LEFT
#define CH_NAME_TOP                     CHNO_HEIGHT

#define IN_SRC_NAME_WIDTH               CHNO_WIDTH
#define IN_SRC_NAME_HEIGHT              NAV_HEIGHT(30)
#define IN_SRC_NAME_LEFT                CHNO_LEFT
#define IN_SRC_NAME_TOP                 (CHNO_HEIGHT + CH_NAME_HEIGHT)

#define CH_FRAME_WIDTH                  CHNO_WIDTH
#define CH_FRAME_HEIGHT                 (CHNO_HEIGHT + CH_NAME_HEIGHT + IN_SRC_NAME_HEIGHT)
#define CH_FRAME_LEFT                   (SAFE_DISPLAY_WIDTH - CH_FRAME_WIDTH)
#define CH_FRAME_TOP                    NAV_WIDTH(0)

#else /* ATSC Only, DVBT */
#define CHNO_WIDTH                      NAV_WIDTH(300)
#define CHNO_LEFT                       NAV_WIDTH(0)
#define CHNO_TOP                        NAV_HEIGHT(0)

#ifdef APP_NAV_BNR_NEXT_EVENT_SUPPORT
    #define CHNO_HEIGHT                     NAV_HEIGHT(63)
    #define CH_NAME_HEIGHT                  NAV_HEIGHT(63)
#else
    #define CHNO_HEIGHT                     NAV_HEIGHT(60)
    #define CH_NAME_HEIGHT                  NAV_HEIGHT(60)
#endif

#define CH_NAME_WIDTH                   CHNO_WIDTH
#define CH_NAME_LEFT                    CHNO_LEFT
#define CH_NAME_TOP                     CHNO_HEIGHT

#define CH_FRAME_WIDTH                  CHNO_WIDTH
#define CH_FRAME_HEIGHT                 (CHNO_HEIGHT + CH_NAME_HEIGHT)
#define CH_FRAME_LEFT                   (SAFE_DISPLAY_WIDTH - CH_FRAME_WIDTH)
#define CH_FRAME_TOP                    NAV_HEIGHT(0)
#endif

#define INFO_BANNER_WIDTH               (SAFE_DISPLAY_WIDTH - CH_FRAME_WIDTH)

#ifdef APP_DCR_SUPPORT
    #define PROG_ATTR_REC_ICON_WIDTH    NAV_WIDTH(60)
    #define PROG_ATTR_REC_ICON_HEIGHT   NAV_HEIGHT(50)
    #define PROG_ATTR_REC_ICON_LEFT     (INFO_BANNER_WIDTH - PROG_ATTR_REC_ICON_WIDTH)
    #define PROG_ATTR_REC_ICON_TOP      NAV_HEIGHT(0)

    #define PROG_TITLE_WIDTH            (SAFE_DISPLAY_WIDTH - CH_FRAME_WIDTH - PROG_ATTR_REC_ICON_WIDTH)

#else
    #define PROG_TITLE_WIDTH            (SAFE_DISPLAY_WIDTH - CH_FRAME_WIDTH)
#endif


    #define PROG_TITLE_LEFT             NAV_WIDTH(0)
    #define PROG_TITLE_TOP              NAV_HEIGHT(0)

#ifdef APP_NAV_BNR_NEXT_EVENT_SUPPORT
    #define PROG_TITLE_HEIGHT           NAV_HEIGHT(42)
    #define PROG_TIME_HEIGHT            NAV_HEIGHT(28)
#else
    #define PROG_TITLE_HEIGHT           NAV_HEIGHT(50)
    #define PROG_TIME_HEIGHT            NAV_HEIGHT(35)
#endif

#define PROG_TIME_WIDTH                 (INFO_BANNER_WIDTH/2 + NAV_WIDTH(10))
#define PROG_TIME_LEFT                  NAV_WIDTH(0)
#define PROG_TIME_TOP                   (PROG_TITLE_TOP + PROG_TITLE_HEIGHT)

#define PROG_TITLE_LEFT_INSET           NAV_WIDTH(12)
#define PROG_TITLE_RIGHT_INSET          NAV_WIDTH(4)
#define PROG_TITLE_TOP_INSET            NAV_HEIGHT(0)
#define PROG_TITLE_BOTTOM_INSET         NAV_HEIGHT(0)

#define PROG_TIME_LEFT_INSET            NAV_WIDTH(12)
#define PROG_TIME_RIGHT_INSET           NAV_WIDTH(4)
#define PROG_TIME_TOP_INSET             NAV_HEIGHT(0)
#define PROG_TIME_BOTTOM_INSET          NAV_HEIGHT(0)

#define PROG_ATTR_WIDTH                 (INFO_BANNER_WIDTH/2)
#define PROG_ATTR_HEIGHT                PROG_TIME_HEIGHT
#define PROG_ATTR_LEFT                  PROG_TIME_LEFT
#define PROG_ATTR_TOP                   (PROG_TIME_TOP + PROG_TIME_HEIGHT)

#define PROG_ATTR_LEFT_INSET            NAV_WIDTH(12)
#define PROG_ATTR_RIGHT_INSET           NAV_WIDTH(4)
#define PROG_ATTR_TOP_INSET             NAV_HEIGHT(0)
#define PROG_ATTR_BOTTOM_INSET          NAV_HEIGHT(0)

#define PROG_ATTR_RATING_WIDTH          NAV_WIDTH(200)
#define PROG_ATTR_RATING_HEIGHT         PROG_TIME_HEIGHT
#define PROG_ATTR_RATING_LEFT           NAV_WIDTH(0)
#define PROG_ATTR_RATING_TOP            (PROG_TIME_TOP + PROG_TIME_HEIGHT)

#define PROG_ATTR_RATING_LEFT_INSET     NAV_WIDTH(12)
#define PROG_ATTR_RATING_RIGHT_INSET    NAV_WIDTH(0)
#define PROG_ATTR_RATING_TOP_INSET      NAV_HEIGHT(0)
#define PROG_ATTR_RATING_BOTTOM_INSET   NAV_HEIGHT(0)

#define PROG_ATTR_LOCK_ICON_WIDTH       NAV_WIDTH(40)
#define PROG_ATTR_LOCK_ICON_HEIGHT      PROG_ATTR_RATING_HEIGHT
#define PROG_ATTR_LOCK_ICON_LEFT        (PROG_ATTR_RATING_LEFT + PROG_ATTR_RATING_WIDTH)
#define PROG_ATTR_LOCK_ICON_TOP         PROG_ATTR_RATING_TOP

#define PROG_ATTR_FAV_ICON_WIDTH        NAV_WIDTH(40)
#define PROG_ATTR_FAV_ICON_HEIGHT       PROG_ATTR_RATING_HEIGHT
#define PROG_ATTR_FAV_ICON_LEFT         (PROG_ATTR_LOCK_ICON_LEFT + PROG_ATTR_LOCK_ICON_WIDTH)
#define PROG_ATTR_FAV_ICON_TOP          PROG_ATTR_RATING_TOP

#define PROG_ATTR_TTX_ICON_WIDTH        NAV_WIDTH(40)
#define PROG_ATTR_TTX_ICON_HEIGHT       PROG_ATTR_RATING_HEIGHT
#define PROG_ATTR_TTX_ICON_LEFT         (PROG_ATTR_FAV_ICON_LEFT + PROG_ATTR_FAV_ICON_WIDTH)
#define PROG_ATTR_TTX_ICON_TOP          PROG_ATTR_RATING_TOP

#define PROG_ATTR_CC_ICON_WIDTH         NAV_WIDTH(60)
#define PROG_ATTR_CC_ICON_HEIGHT        PROG_ATTR_RATING_HEIGHT
#define PROG_ATTR_CC_ICON_TOP           PROG_ATTR_RATING_TOP
#ifdef APP_DVBT_SUPPORT
    #define PROG_ATTR_CC_ICON_LEFT      (PROG_ATTR_TTX_ICON_LEFT + PROG_ATTR_TTX_ICON_WIDTH)
#else
    #define PROG_ATTR_CC_ICON_LEFT      (PROG_ATTR_FAV_ICON_LEFT + PROG_ATTR_FAV_ICON_WIDTH)
#endif

#define PROG_ATTR_CC_DESC_WIDTH         NAV_WIDTH(210)
#define PROG_ATTR_CC_DESC_HEIGHT        PROG_ATTR_RATING_HEIGHT
#define PROG_ATTR_CC_DESC_LEFT          (PROG_ATTR_CC_ICON_LEFT + PROG_ATTR_CC_ICON_WIDTH)
#define PROG_ATTR_CC_DESC_TOP           PROG_ATTR_RATING_TOP

#define PROG_ATTR_CC_DESC_LEFT_INSET    NAV_WIDTH(0)
#define PROG_ATTR_CC_DESC_RIGHT_INSET   NAV_WIDTH(4)
#define PROG_ATTR_CC_DESC_TOP_INSET     NAV_HEIGHT(0)
#define PROG_ATTR_CC_DESC_BOTTOM_INSET  NAV_HEIGHT(0)

#define AUDIO_INFO_WIDTH                (INFO_BANNER_WIDTH - PROG_TIME_WIDTH)
#define AUDIO_INFO_HEIGHT               PROG_TIME_HEIGHT
#define AUDIO_INFO_LEFT                 (PROG_TIME_LEFT + PROG_TIME_WIDTH)
#define AUDIO_INFO_TOP                  (PROG_TIME_TOP)

#define AUDIO_INFO_LEFT_INSET           NAV_WIDTH(4)
#define AUDIO_INFO_RIGHT_INSET          NAV_WIDTH(8)
#define AUDIO_INFO_TOP_INSET            NAV_HEIGHT(0)
#define AUDIO_INFO_BOTTOM_INSET         NAV_HEIGHT(0)

#ifndef APP_DCR_SUPPORT
    #define VIDEO_INFO_WIDTH            (INFO_BANNER_WIDTH - (PROG_ATTR_CC_DESC_LEFT - PROG_ATTR_RATING_LEFT + PROG_ATTR_CC_DESC_WIDTH))
    #define VIDEO_INFO_HEIGHT           PROG_ATTR_RATING_HEIGHT
    #define VIDEO_INFO_LEFT             (PROG_ATTR_CC_DESC_LEFT + PROG_ATTR_CC_DESC_WIDTH)
    #define VIDEO_INFO_TOP              (PROG_ATTR_RATING_TOP)
#else
    #define VIDEO_INFO_LEFT             (PROG_ATTR_CC_DESC_LEFT + PROG_ATTR_CC_DESC_WIDTH)
    #define VIDEO_INFO_TOP              (PROG_ATTR_RATING_TOP)
    #define VIDEO_INFO_WIDTH            (INFO_BANNER_WIDTH - VIDEO_INFO_LEFT)
    #define VIDEO_INFO_HEIGHT           PROG_ATTR_RATING_HEIGHT
#endif

#define VIDEO_INFO_LEFT_INSET           NAV_WIDTH(4)
#define VIDEO_INFO_RIGHT_INSET          NAV_WIDTH(8)
#define VIDEO_INFO_TOP_INSET            NAV_HEIGHT(0)
#define VIDEO_INFO_BOTTOM_INSET         NAV_HEIGHT(0)

#ifdef APP_NAV_BNR_NEXT_EVENT_SUPPORT
    #define NEXT_PROG_TIME_HEIGHT           NAV_HEIGHT(28)
    #define NEXT_PROG_TIME_WIDTH            NAV_WIDTH(250)
    #define NEXT_PROG_TIME_LEFT             NAV_WIDTH(0)
    #define NEXT_PROG_TIME_TOP              (PROG_ATTR_TOP + PROG_ATTR_HEIGHT)

    #define NEXT_PROG_TIME_LEFT_INSET       NAV_WIDTH(12)
    #define NEXT_PROG_TIME_RIGHT_INSET      NAV_WIDTH(4)
    #define NEXT_PROG_TIME_TOP_INSET        NAV_HEIGHT(0)
    #define NEXT_PROG_TIME_BOTTOM_INSET     NAV_HEIGHT(0)

    #define NEXT_PROG_TITLE_WIDTH           (INFO_BANNER_WIDTH - NEXT_PROG_TIME_WIDTH)
    #define NEXT_PROG_TITLE_HEIGHT          NEXT_PROG_TIME_HEIGHT
    #define NEXT_PROG_TITLE_LEFT            NEXT_PROG_TIME_WIDTH
    #define NEXT_PROG_TITLE_TOP             NEXT_PROG_TIME_TOP

    #define NEXT_PROG_TITLE_LEFT_INSET      NAV_WIDTH(12)
    #define NEXT_PROG_TITLE_RIGHT_INSET     NAV_WIDTH(4)
    #define NEXT_PROG_TITLE_TOP_INSET       NAV_HEIGHT(0)
    #define NEXT_PROG_TITLE_BOTTOM_INSET    NAV_HEIGHT(0)
#endif
#define PLS_SCAN_TITLE_WIDTH            (INFO_BANNER_WIDTH - CHNO_WIDTH)
#define PLS_SCAN_TITLE_HEIGHT           CH_FRAME_HEIGHT
#define PLS_SCAN_TITLE_LEFT             CHNO_WIDTH
#define PLS_SCAN_TITLE_TOP              NAV_HEIGHT(0)

#define INFO_FRAME_WIDTH                (INFO_BANNER_WIDTH)
#define INFO_FRAME_HEIGHT               CH_FRAME_HEIGHT
#define INFO_FRAME_LEFT                 NAV_WIDTH(0)
#define INFO_FRAME_TOP                  NAV_HEIGHT(0)

#define PROG_DETAIL_LEFT                NAV_WIDTH(0)
#define PROG_DETAIL_TOP                 NAV_HEIGHT(0)
#define PROG_DETAIL_WIDTH               (SAFE_DISPLAY_WIDTH - NAV_WIDTH(80))
#define PROG_DETAIL_HEIGHT              NAV_HEIGHT(120)

#define PROG_DETAIL_INDEX_WIDTH         NAV_WIDTH(80)
#define PROG_DETAIL_INDEX_HEIGHT        PROG_DETAIL_HEIGHT
#define PROG_DETAIL_INDEX_LEFT          (PROG_DETAIL_LEFT+PROG_DETAIL_WIDTH)
#define PROG_DETAIL_INDEX_TOP           PROG_DETAIL_TOP

#define PROG_DETAIL_UP_ICON_WIDTH       NAV_WIDTH(28)
#define PROG_DETAIL_UP_ICON_HEIGHT      NAV_HEIGHT(28)
#define PROG_DETAIL_UP_ICON_LEFT        (PROG_DETAIL_LEFT + PROG_DETAIL_WIDTH + PROG_DETAIL_INDEX_WIDTH/2 - PROG_DETAIL_UP_ICON_WIDTH/2)
#define PROG_DETAIL_UP_ICON_TOP         (PROG_DETAIL_TOP + NAV_HEIGHT(2))

#define PROG_DETAIL_DN_ICON_WIDTH       NAV_WIDTH(28)
#define PROG_DETAIL_DN_ICON_HEIGHT      NAV_HEIGHT(28)
#define PROG_DETAIL_DN_ICON_LEFT        PROG_DETAIL_UP_ICON_LEFT
#define PROG_DETAIL_DN_ICON_TOP         (PROG_DETAIL_TOP + PROG_DETAIL_HEIGHT - NAV_HEIGHT(2) - PROG_DETAIL_DN_ICON_HEIGHT)

#define PROG_DETAIL_FRAME_LEFT          INFO_FRAME_LEFT
#define PROG_DETAIL_FRAME_TOP           (INFO_FRAME_TOP + INFO_FRAME_HEIGHT + NAV_HEIGHT(4))
#define PROG_DETAIL_FRAME_WIDTH         SAFE_DISPLAY_WIDTH
#define PROG_DETAIL_FRAME_HEIGHT        PROG_DETAIL_HEIGHT
#define PROG_DETAIL_WGL_CUT_STYLE       WGL_STL_TEXT_SMART_CUT_OVER_MAX
#define PROG_DETAIL_WGL_TEXT_LEN        WGL_STL_TEXT_MAX_4096
#define PROG_DETAIL_MAX_TEXT_LEN        4096

#ifdef APP_NAV_BNR_NEXT_EVENT_SUPPORT
    #define BANNER_FRAME_TOP            (SAFE_DISPLAY_TOP / 2)
#else
    #define BANNER_FRAME_TOP            SAFE_DISPLAY_TOP
#endif

#define BANNER_FRAME_LEFT               SAFE_DISPLAY_LEFT
#define BANNER_FRAME_WIDTH              SAFE_DISPLAY_WIDTH
#define BANNER_FRAME_HEIGHT             (PROG_DETAIL_FRAME_TOP - INFO_FRAME_TOP + PROG_DETAIL_FRAME_HEIGHT)

#define PROG_DETAIL_LEFT_INSET          NAV_WIDTH(12)
#define PROG_DETAIL_RIGHT_INSET         NAV_WIDTH(12)
#define PROG_DETAIL_TOP_INSET           NAV_HEIGHT(4)
#define PROG_DETAIL_BOTTOM_INSET        NAV_HEIGHT(4)

#define VOLUME_TITLE_WIDTH              NAV_WIDTH(450)
#define VOLUME_TITLE_HEIGHT             NAV_HEIGHT(70)
#define VOLUME_TITLE_LEFT               NAV_WIDTH(10)
#define VOLUME_TITLE_TOP                NAV_HEIGHT(0)

#define VOLUME_WIDTH                    NAV_WIDTH(400)
#define VOLUME_HEIGHT                   NAV_HEIGHT(40)
#define VOLUME_LEFT                     (VOLUME_TITLE_LEFT + VOLUME_TITLE_WIDTH)
#define VOLUME_TOP                      ((VOLUME_TITLE_HEIGHT - VOLUME_HEIGHT)/2)

#define VOLUME_FRAME_WIDTH              (VOLUME_TITLE_WIDTH + VOLUME_WIDTH + NAV_WIDTH(20))
#define VOLUME_FRAME_HEIGHT             VOLUME_TITLE_HEIGHT
#define VOLUME_FRAME_LEFT               (SAFE_DISPLAY_LEFT + (SAFE_DISPLAY_WIDTH - VOLUME_FRAME_WIDTH) / 2)
#define VOLUME_FRAME_TOP                (SAFE_DISPLAY_TOP + SAFE_DISPLAY_HEIGHT - VOLUME_FRAME_HEIGHT)

#ifdef APP_MUTE_DISP_AS_TEXT
    #define MUTE_FRAME_WIDTH            NAV_WIDTH(120)
    #define MUTE_FRAME_HEIGHT           NAV_HEIGHT(50)
    #define MUTE_FRAME_LEFT             (SAFE_DISPLAY_LEFT - MUTE_FRAME_WIDTH)
    #define MUTE_FRAME_TOP              (SAFE_DISPLAY_TOP  + SAFE_DISPLAY_HEIGHT - MUTE_FRAME_HEIGHT)

    #define MUTE_TEXT_WIDTH             MUTE_FRAME_WIDTH
    #define MUTE_TEXT_HEIGHT            MUTE_FRAME_HEIGHT
    #define MUTE_TEXT_LEFT              NAV_WIDTH(0)
    #define MUTE_TEXT_TOP               NAV_HEIGHT(0)

    #define MUTE_MSG_LEFT_INSET         NAV_WIDTH(6)
    #define MUTE_MSG_RIGHT_INSET        NAV_WIDTH(6)
    #define MUTE_MSG_TOP_INSET          NAV_WIDTH(0)
    #define MUTE_MSG_BOTTOM_INSET       NAV_WIDTH(0)

    #define MUTE_MSG_ALIGNMENT          WGL_AS_RIGHT_CENTER
#else
    #define MUTE_ICON_WIDTH             VOLUME_TITLE_HEIGHT
    #define MUTE_ICON_HEIGHT            VOLUME_TITLE_HEIGHT
    #define MUTE_ICON_LEFT              NAV_WIDTH(0)
    #define MUTE_ICON_TOP               NAV_HEIGHT(7)

    #define MUTE_FRAME_WIDTH            MUTE_ICON_WIDTH
    #define MUTE_FRAME_HEIGHT           MUTE_ICON_HEIGHT
    #define MUTE_FRAME_LEFT             (SAFE_DISPLAY_LEFT + SAFE_DISPLAY_WIDTH  - MUTE_FRAME_WIDTH)
    #define MUTE_FRAME_TOP              (SAFE_DISPLAY_TOP  + SAFE_DISPLAY_HEIGHT - MUTE_FRAME_HEIGHT)
#endif

#define PWD_TITLE_WIDTH                 (PWD_FRAME_WIDTH - PWD_TITLE_LEFT )
#define PWD_TITLE_HEIGHT                NAV_HEIGHT(26)
#define PWD_TITLE_LEFT                  NAV_WIDTH(5)
#define PWD_TITLE_TOP                   NAV_HEIGHT(7)

#define PWD_BOX_WIDTH                   NAV_WIDTH(46)
#define PWD_BOX_HEIGHT                  NAV_HEIGHT(53)
#define PWD_BOX_LEFT                    NAV_WIDTH(6*4/3)
#define PWD_BOX_TOP                     NAV_HEIGHT(84)
#define PWD_BOX_DIS                     NAV_WIDTH(4)

#define PWD_ALARM_WIDTH                 (PWD_FRAME_WIDTH-(PWD_ALARM_LEFT*2))
#define PWD_ALARM_HEIGHT                NAV_HEIGHT(45)
#define PWD_ALARM_LEFT                  NAV_WIDTH(5)
#define PWD_ALARM_TOP                   NAV_HEIGHT(30)


#define PWD_FRAME_WIDTH                 NAV_WIDTH(206)
#define PWD_FRAME_HEIGHT                NAV_HEIGHT(142)
#define PWD_FRAME_LEFT                  (SAFE_DISPLAY_LEFT + (SAFE_DISPLAY_WIDTH-PWD_FRAME_WIDTH) / 2)
#define PWD_FRAME_TOP                   (SAFE_DISPLAY_TOP + SAFE_DISPLAY_HEIGHT-PWD_FRAME_HEIGHT-NAV_HEIGHT(120))

#define ELEM_HEIGHT_OF_CH_LIST          NAV_HEIGHT(33)
#define ELEM_DTANCE_OF_CH_LIST          NAV_HEIGHT(2)

#ifdef APP_DVBT_SUPPORT
#define CH_LST_0_COL_ALIGN              WGL_AS_CENTER_CENTER     /* Icon1 */
#define CH_LST_0_COL_WIDTH              NAV_WIDTH(20)
#define CH_LST_1_COL_ALIGN              WGL_AS_CENTER_CENTER     /* Icon2 */
#define CH_LST_1_COL_WIDTH              NAV_WIDTH(20)
#define CH_LST_2_COL_ALIGN              WGL_AS_CENTER_CENTER     /* Icon3 */
#define CH_LST_2_COL_WIDTH              NAV_WIDTH(20)

#define CH_LST_3_MAX_TEXT_LEN           5
#define CH_LST_4_MAX_TEXT_LEN           32      /*channel name*/

#define CH_LST_3_COL_ALIGNMENT          WGL_AS_RIGHT_CENTER
#define CH_LST_4_COL_ALIGNMENT          WGL_AS_LEFT_CENTER
#define CH_LST_3_COL_LEFT_INSET         NAV_WIDTH(4)
#define CH_LST_3_COL_RIGHT_INSET        NAV_WIDTH(4)
#define CH_LST_4_COL_LEFT_INSET         NAV_WIDTH(4)
#define CH_LST_4_COL_RIGHT_INSET        NAV_WIDTH(4)
#define CH_LST_3_COL_WIDHT              (NAV_WIDTH(100) + CH_LST_3_COL_LEFT_INSET + CH_LST_3_COL_RIGHT_INSET)
#define CH_LST_4_COL_WIDHT              (NAV_WIDTH(350) + CH_LST_4_COL_LEFT_INSET + CH_LST_4_COL_RIGHT_INSET)
#else
#define CH_LST_0_COL_ALIGN              WGL_AS_CENTER_CENTER     /* Icon1 */
#define CH_LST_0_COL_WIDTH              NAV_WIDTH(0)
#define CH_LST_1_COL_ALIGN              WGL_AS_CENTER_CENTER     /* Icon2 */
#define CH_LST_1_COL_WIDTH              NAV_WIDTH(0)
#define CH_LST_2_COL_ALIGN              WGL_AS_CENTER_CENTER     /* Icon3 */
#define CH_LST_2_COL_WIDTH              NAV_WIDTH(0)

#define CH_LST_3_MAX_TEXT_LEN           10
#define CH_LST_4_MAX_TEXT_LEN           16      /*channel name*/

#define CH_LST_3_COL_ALIGNMENT          WGL_AS_RIGHT_CENTER
#define CH_LST_4_COL_ALIGNMENT          WGL_AS_LEFT_CENTER
#define CH_LST_3_COL_LEFT_INSET         NAV_WIDTH(4)
#define CH_LST_3_COL_RIGHT_INSET        NAV_WIDTH(4)
#define CH_LST_4_COL_LEFT_INSET         NAV_WIDTH(4)
#define CH_LST_4_COL_RIGHT_INSET        NAV_WIDTH(4)
#define CH_LST_3_COL_WIDHT              NAV_WIDTH(100)
#define CH_LST_4_COL_WIDHT              NAV_WIDTH(200)
#endif

#define CH_LST_LEFT_INSET               NAV_WIDTH(4)
#define CH_LST_RIGHT_INSET              NAV_WIDTH(2)
#define CH_LST_TOP_INSET                NAV_HEIGHT(44)
#define CH_LST_BOTTOM_INSET             NAV_HEIGHT(0)


#define CH_LST_WIDTH                    NAV_WIDTH(298)
#define CH_LST_HEIGHT                   NAV_HEIGHT(295)
#define CH_LST_LEFT                     NAV_WIDTH(0)
#define CH_LST_TOP                      NAV_HEIGHT(0)

#define CH_LST_TITLE_WIDTH              NAV_WIDTH(278)
#define CH_LST_TITLE_HEIGHT             NAV_HEIGHT(23)
#define CH_LST_TITLE_LEFT               NAV_WIDTH(15)
#define CH_LST_TITLE_TOP                NAV_HEIGHT(12)

#define CH_LST_PG_UP_ICON_LEFT          NAV_WIDTH(14)
#define CH_LST_PG_UP_ICON_TOP           (CH_LST_HEIGHT - CH_LST_BOTTOM_INSET + 12)
#define CH_LST_PG_UP_ICON_WIDTH         NAV_WIDTH(42)
#define CH_LST_PG_UP_ICON_HEIGHT        NAV_HEIGHT(13)

#define CH_LST_PG_UP_HELP_MSG_LEFT      (CH_LST_PG_UP_ICON_LEFT + CH_LST_PG_UP_ICON_WIDTH + NAV_WIDTH(2))
#define CH_LST_PG_UP_HELP_MSG_TOP       (CH_LST_HEIGHT - CH_LST_BOTTOM_INSET)
#define CH_LST_PG_UP_HELP_MSG_WIDTH     ((CH_LST_WIDTH - CH_LST_PG_UP_HELP_MSG_LEFT * 2)/2)
#define CH_LST_PG_UP_HELP_MSG_HEIGHT    CH_LST_BOTTOM_INSET

#define CH_LST_PG_DN_ICON_LEFT          (CH_LST_WIDTH/2 + NAV_WIDTH(6))
#define CH_LST_PG_DN_ICON_TOP           CH_LST_PG_UP_ICON_TOP
#define CH_LST_PG_DN_ICON_WIDTH         CH_LST_PG_UP_ICON_WIDTH
#define CH_LST_PG_DN_ICON_HEIGHT        CH_LST_PG_UP_ICON_HEIGHT

#define CH_LST_PG_DN_HELP_MSG_LEFT      (CH_LST_PG_DN_ICON_LEFT + CH_LST_PG_DN_ICON_WIDTH + NAV_WIDTH(2))
#define CH_LST_PG_DN_HELP_MSG_TOP       (CH_LST_HEIGHT - CH_LST_BOTTOM_INSET)
#define CH_LST_PG_DN_HELP_MSG_WIDTH     CH_LST_PG_UP_HELP_MSG_WIDTH
#define CH_LST_PG_DN_HELP_MSG_HEIGHT    CH_LST_PG_UP_HELP_MSG_HEIGHT

#define CH_LST_FRAME_WIDTH              NAV_WIDTH(298)
#define CH_LST_FRAME_HEIGHT             NAV_HEIGHT(295)
#define CH_LST_FRAME_LEFT               NAV_WIDTH(335)
#define CH_LST_FRAME_TOP                NAV_HEIGHT(145)   /*(128)*/

#define CH_LST_INDCTR_LEFT              NAV_WIDTH(0)
#define CH_LST_INDCTR_TOP               NAV_HEIGHT(43)
#define CH_LST_INDCTR_WIDTH             NAV_WIDTH(298)
#define CH_LST_INDCTR_HEIGHT            NAV_HEIGHT(244)

#define CH_DETAIL_TITLE_LEFT            NAV_WIDTH(0)
#define CH_DETAIL_TITLE_TOP             NAV_HEIGHT(0)
#define CH_DETAIL_TITLE_WIDTH           (SAFE_DISPLAY_WIDTH - CH_LST_WIDTH - NAV_WIDTH(10))
#define CH_DETAIL_TITLE_HEIGHT          NAV_HEIGHT(40)

#define CH_DETAIL_LEFT                  NAV_WIDTH(0)
#define CH_DETAIL_TOP                   (CH_DETAIL_TITLE_HEIGHT + CH_DETAIL_TITLE_TOP)
#define CH_DETAIL_WIDTH                 (CH_DETAIL_TITLE_WIDTH)
#define CH_DETAIL_HEIGHT                (CH_LST_HEIGHT - (CH_DETAIL_TITLE_HEIGHT + CH_DETAIL_LF_ICON_HEIGHT))

#define CH_DETAIL_INDEX_WIDTH           NAV_WIDTH(80)
#define CH_DETAIL_INDEX_HEIGHT          NAV_HEIGHT(40)
#define CH_DETAIL_INDEX_LEFT            (CH_DETAIL_LEFT+ CH_DETAIL_WIDTH/2 - CH_DETAIL_INDEX_WIDTH/2)
#define CH_DETAIL_INDEX_TOP             (CH_DETAIL_TOP + CH_DETAIL_HEIGHT)
/* DTV00000565 - change UP_ICON to LF_ICON */
#define CH_DETAIL_LF_ICON_WIDTH         NAV_WIDTH(40)
#define CH_DETAIL_LF_ICON_HEIGHT        NAV_HEIGHT(40)
#define CH_DETAIL_LF_ICON_LEFT          (CH_DETAIL_LEFT)
#define CH_DETAIL_LF_ICON_TOP           (CH_DETAIL_INDEX_TOP)
/* DTV00000565 - change DN_ICON to RT_ICON */
#define CH_DETAIL_RT_ICON_WIDTH         NAV_WIDTH(40)
#define CH_DETAIL_RT_ICON_HEIGHT        NAV_HEIGHT(40)
#define CH_DETAIL_RT_ICON_LEFT          (CH_DETAIL_LEFT + CH_DETAIL_WIDTH - CH_DETAIL_RT_ICON_WIDTH)
#define CH_DETAIL_RT_ICON_TOP           (CH_DETAIL_INDEX_TOP)

#define CH_DETAIL_FRAME_LEFT            (CH_LST_FRAME_LEFT + CH_LST_FRAME_WIDTH + NAV_WIDTH(0))
#define CH_DETAIL_FRAME_TOP             CH_LST_FRAME_TOP
#define CH_DETAIL_FRAME_WIDTH           (CH_DETAIL_WIDTH)
#define CH_DETAIL_FRAME_HEIGHT          (CH_DETAIL_TITLE_HEIGHT + CH_DETAIL_HEIGHT + CH_DETAIL_LF_ICON_HEIGHT)
#define CH_DETAIL_WGL_CUT_STYLE         WGL_STL_TEXT_SMART_CUT_OVER_MAX
#define CH_DETAIL_WGL_TEXT_LEN          WGL_STL_TEXT_MAX_4096
#define CH_DETAIL_MAX_TEXT_LEN          4096

#define CH_DETAIL_LEFT_INSET            NAV_WIDTH(12)
#define CH_DETAIL_RIGHT_INSET           NAV_WIDTH(12)
#define CH_DETAIL_TOP_INSET             NAV_HEIGHT(4)
#define CH_DETAIL_BOTTOM_INSET          NAV_HEIGHT(4)

#define ELEM_HEIGHT_OF_FAV_CH_LIST      NAV_HEIGHT(34)
#define ELEM_DTANCE_OF_FAV_CH_LIST      NAV_HEIGHT(0) /* NAV_HEIGHT(2)*/

#ifdef APP_DVBT_SUPPORT
#define FAV_LST_0_MAX_TEXT_LEN          5
#define FAV_LST_1_MAX_TEXT_LEN          (MAX_PROG_NAME_LEN)      /*channel name*/

#define FAV_LST_0_COL_ALIGNMENT         WGL_AS_RIGHT_CENTER
#define FAV_LST_1_COL_ALIGNMENT         WGL_AS_LEFT_CENTER
#define FAV_LST_0_COL_LEFT_INSET        NAV_WIDTH(4)
#define FAV_LST_0_COL_RIGHT_INSET       NAV_WIDTH(4)
#define FAV_LST_1_COL_LEFT_INSET        NAV_WIDTH(4)
#define FAV_LST_1_COL_RIGHT_INSET       NAV_WIDTH(4)
#define FAV_LST_0_COL_WIDHT             (NAV_WIDTH(100) + FAV_LST_0_COL_LEFT_INSET + FAV_LST_0_COL_RIGHT_INSET)
#define FAV_LST_1_COL_WIDHT             (NAV_WIDTH(330) + FAV_LST_1_COL_LEFT_INSET + FAV_LST_1_COL_RIGHT_INSET)
#else
#define FAV_LST_0_MAX_TEXT_LEN          10
#define FAV_LST_1_MAX_TEXT_LEN          48      /*channel name*/

#define FAV_LST_0_COL_ALIGNMENT         WGL_AS_RIGHT_CENTER
#define FAV_LST_1_COL_ALIGNMENT         WGL_AS_LEFT_CENTER
#define FAV_LST_0_COL_LEFT_INSET        NAV_WIDTH(4)
#define FAV_LST_0_COL_RIGHT_INSET       NAV_WIDTH(4)
#define FAV_LST_1_COL_LEFT_INSET        NAV_WIDTH(4)
#define FAV_LST_1_COL_RIGHT_INSET       NAV_WIDTH(4)
#define FAV_LST_0_COL_WIDHT             (NAV_WIDTH(200) + FAV_LST_0_COL_LEFT_INSET + FAV_LST_0_COL_RIGHT_INSET)
#define FAV_LST_1_COL_WIDHT             (NAV_WIDTH(230) + FAV_LST_1_COL_LEFT_INSET + FAV_LST_1_COL_RIGHT_INSET)
#endif

#define FAV_LST_LEFT_INSET              NAV_WIDTH(4)
#define FAV_LST_RIGHT_INSET             NAV_WIDTH(4)
#define FAV_LST_TOP_INSET               NAV_HEIGHT(40)
#define FAV_LST_HELP_AREA_INSET         NAV_HEIGHT(34)  /* If this is defined, indicate there is an HINT icon available. */
#define FAV_LST_BOTTOM_INSET            (NAV_HEIGHT(16)+FAV_LST_HELP_AREA_INSET)

#define FAV_LST_WIDTH                   (FAV_LST_LEFT_INSET + FAV_LST_RIGHT_INSET + FAV_LST_0_COL_WIDHT + FAV_LST_1_COL_WIDHT)
#define FAV_LST_HEIGHT                  (FAV_LST_BOTTOM_INSET + FAV_LST_TOP_INSET + MAX_ELEM_OF_FAV_LIST * (ELEM_HEIGHT_OF_FAV_CH_LIST + ELEM_DTANCE_OF_FAV_CH_LIST) - ELEM_DTANCE_OF_FAV_CH_LIST)
#define FAV_LST_LEFT                    NAV_WIDTH(0)
#define FAV_LST_TOP                     NAV_HEIGHT(0)

#define FAV_LST_TITLE_WIDTH             FAV_LST_WIDTH
#define FAV_LST_TITLE_HEIGHT            FAV_LST_TOP_INSET
#define FAV_LST_TITLE_LEFT              NAV_WIDTH(0)
#define FAV_LST_TITLE_TOP               NAV_HEIGHT(0)

/* Only available if FAV_LST_HELP_AREA_INSET is defined */

#define FAV_LST_BOTTOM_HELP_AREA_LINE_1_INSET    NAV_HEIGHT(25)
#define FAV_LST_BOTTOM_HELP_AREA_LINE_2_INSET    NAV_HEIGHT(25)

/* Buttons in Help line 1 */
#define FAV_LST_GRP_UP_ICON_LEFT          NAV_WIDTH(14)
#define FAV_LST_GRP_UP_ICON_TOP           (FAV_LST_HEIGHT - FAV_LST_BOTTOM_HELP_AREA_LINE_1_INSET - FAV_LST_BOTTOM_HELP_AREA_LINE_2_INSET + 5)
#define FAV_LST_GRP_UP_ICON_WIDTH         NAV_WIDTH(31)
#define FAV_LST_GRP_UP_ICON_HEIGHT        NAV_HEIGHT(15)

#define FAV_LST_GRP_UP_HELP_MSG_LEFT      (FAV_LST_GRP_UP_ICON_LEFT + FAV_LST_GRP_UP_ICON_WIDTH + NAV_WIDTH(2))
#define FAV_LST_GRP_UP_HELP_MSG_TOP       (FAV_LST_HEIGHT - FAV_LST_BOTTOM_HELP_AREA_LINE_1_INSET - FAV_LST_BOTTOM_HELP_AREA_LINE_2_INSET)
#define FAV_LST_GRP_UP_HELP_MSG_WIDTH     ((FAV_LST_WIDTH - FAV_LST_GRP_UP_HELP_MSG_LEFT * 2)/2)
#define FAV_LST_GRP_UP_HELP_MSG_HEIGHT    FAV_LST_BOTTOM_HELP_AREA_LINE_1_INSET

#define FAV_LST_GRP_DN_ICON_LEFT          (FAV_LST_WIDTH/2 + NAV_WIDTH(14))
#define FAV_LST_GRP_DN_ICON_TOP           FAV_LST_GRP_UP_ICON_TOP
#define FAV_LST_GRP_DN_ICON_WIDTH         FAV_LST_GRP_UP_ICON_WIDTH
#define FAV_LST_GRP_DN_ICON_HEIGHT        FAV_LST_GRP_UP_ICON_HEIGHT

#define FAV_LST_GRP_DN_HELP_MSG_LEFT      (FAV_LST_GRP_DN_ICON_LEFT + FAV_LST_GRP_DN_ICON_WIDTH + NAV_WIDTH(2))
#define FAV_LST_GRP_DN_HELP_MSG_TOP       (FAV_LST_HEIGHT - FAV_LST_BOTTOM_HELP_AREA_LINE_1_INSET - FAV_LST_BOTTOM_HELP_AREA_LINE_2_INSET)
#define FAV_LST_GRP_DN_HELP_MSG_WIDTH     FAV_LST_GRP_UP_HELP_MSG_WIDTH
#define FAV_LST_GRP_DN_HELP_MSG_HEIGHT    FAV_LST_GRP_UP_HELP_MSG_HEIGHT

/* Buttons in Help line 2 */
#define FAV_LST_SELECT_ICON_LEFT          NAV_WIDTH(14)
#define FAV_LST_SELECT_ICON_TOP           (FAV_LST_HEIGHT - FAV_LST_BOTTOM_HELP_AREA_LINE_2_INSET + 2)
#define FAV_LST_SELECT_ICON_WIDTH         FAV_LST_GRP_UP_ICON_WIDTH
#define FAV_LST_SELECT_ICON_HEIGHT        FAV_LST_BOTTOM_HELP_AREA_LINE_2_INSET

#define FAV_LST_SELECT_HELP_MSG_LEFT      (FAV_LST_SELECT_ICON_LEFT + FAV_LST_SELECT_ICON_WIDTH + NAV_WIDTH(2))
#define FAV_LST_SELECT_HELP_MSG_TOP       (FAV_LST_HEIGHT - FAV_LST_BOTTOM_HELP_AREA_LINE_2_INSET)
#define FAV_LST_SELECT_HELP_MSG_WIDTH     ((FAV_LST_WIDTH - FAV_LST_GRP_UP_HELP_MSG_LEFT * 2)/2)
#define FAV_LST_SELECT_HELP_MSG_HEIGHT    FAV_LST_SELECT_ICON_HEIGHT

#define FAV_LST_EXIT_ICON_LEFT          (FAV_LST_WIDTH/2 + NAV_WIDTH(14))
#define FAV_LST_EXIT_ICON_TOP           (FAV_LST_SEL_LIST_ICON_TOP)
#define FAV_LST_EXIT_ICON_WIDTH         FAV_LST_GRP_UP_ICON_WIDTH
#define FAV_LST_EXIT_ICON_HEIGHT        FAV_LST_BOTTOM_HELP_AREA_LINE_2_INSET

#define FAV_LST_EXIT_HELP_MSG_LEFT      (FAV_LST_EXIT_ICON_LEFT + FAV_LST_EXIT_ICON_WIDTH + NAV_WIDTH(2))
#define FAV_LST_EXIT_HELP_MSG_TOP       FAV_LST_SEL_LIST_HELP_MSG_TOP
#define FAV_LST_EXIT_HELP_MSG_WIDTH     ((FAV_LST_WIDTH - FAV_LST_GRP_UP_HELP_MSG_LEFT * 2)/2)

/* ---------------------------------------------------- */

#define FAV_LST_FRAME_WIDTH             FAV_LST_WIDTH
#define FAV_LST_FRAME_HEIGHT            FAV_LST_HEIGHT
#define FAV_LST_FRAME_LEFT              BANNER_FRAME_LEFT
#define FAV_LST_FRAME_TOP               (BANNER_FRAME_TOP + BANNER_FRAME_HEIGHT - 100)

/* screen saver message */
#define TWINKLE_MSG_FRAME_LEFT          ((DISPLAY_WIDTH - TWINKLE_MSG_FRAME_WIDTH)/2)
#define TWINKLE_MSG_FRAME_TOP           ((DISPLAY_HEIGHT - TWINKLE_MSG_FRAME_HEIGHT)/2)
#define TWINKLE_MSG_FRAME_WIDTH         NAV_WIDTH(312)
#define TWINKLE_MSG_FRAME_HEIGHT        NAV_HEIGHT(77)

#define TWINKLE_MSG_TITLE_LEFT          NAV_WIDTH(0)
#define TWINKLE_MSG_TITLE_TOP           NAV_HEIGHT(0)
#define TWINKLE_MSG_TITLE_WIDTH         TWINKLE_MSG_FRAME_WIDTH
#define TWINKLE_MSG_TITLE_HEIGHT        TWINKLE_MSG_FRAME_HEIGHT

#ifdef APP_MOVABLE_SCREEN_SAVER
  #define MSG_X_MOVEMENT                NAV_WIDTH(13)
  #define MSG_Y_MOVEMENT                NAV_HEIGHT(13)
  #define MOVABLE_RECT_TOP              NAV_HEIGHT(200)
  #define MOVABLE_RECT_BOTTOM           NAV_HEIGHT(450)
#endif /* APP_MOVABLE_SCREEN_SAVER */

/* multi-video selection */
#define VIDEO_SEL_0_COL_ALIGNMENT       WGL_AS_CENTER_CENTER
#define VIDEO_SEL_0_COL_LEFT_INSET      NAV_WIDTH(4)
#define VIDEO_SEL_0_COL_RIGHT_INSET     NAV_WIDTH(4)
#define VIDEO_SEL_0_COL_WIDHT           (NAV_WIDTH(48) + VIDEO_SEL_0_COL_LEFT_INSET + VIDEO_SEL_0_COL_RIGHT_INSET)

#define VIDEO_SEL_1_COL_ALIGNMENT       WGL_AS_LEFT_CENTER
#define VIDEO_SEL_1_COL_LEFT_INSET      NAV_WIDTH(4)
#define VIDEO_SEL_1_COL_RIGHT_INSET     NAV_WIDTH(4)
#define VIDEO_SEL_1_COL_WIDHT           (NAV_WIDTH(176) + VIDEO_SEL_1_COL_LEFT_INSET + VIDEO_SEL_1_COL_RIGHT_INSET)

#define MAX_COL_OF_VIDEO_SEL            3
#define VIDEO_SEL_COL_HEIGHT            NAV_HEIGHT(36)
#define VIDEO_SEL_COL_DTANCE            NAV_HEIGHT(2)
#define VIDEO_SEL_COL_NUM               2

#define VIDEO_SEL_1_COL_MAX_TEXT_LEN    12

#define VIDEO_SEL_LEFT_INSET            NAV_WIDTH(4)
#define VIDEO_SEL_RIGHT_INSET           NAV_WIDTH(4)
#define VIDEO_SEL_TOP_INSET             NAV_HEIGHT(40)
#define VIDEO_SEL_BOTTOM_INSET          NAV_HEIGHT(12)

#define VIDEO_SEL_TITLE_WIDTH           VIDEO_SEL_WIDTH
#define VIDEO_SEL_TITLE_HEIGHT          VIDEO_SEL_TOP_INSET
#define VIDEO_SEL_TITLE_LEFT            NAV_WIDTH(0)
#define VIDEO_SEL_TITLE_TOP             NAV_HEIGHT(0)

#define VIDEO_SEL_LEFT                  NAV_WIDTH(0)
#define VIDEO_SEL_TOP                   NAV_HEIGHT(0)
#define VIDEO_SEL_WIDTH                 (VIDEO_SEL_LEFT_INSET + VIDEO_SEL_RIGHT_INSET + VIDEO_SEL_0_COL_WIDHT + VIDEO_SEL_1_COL_WIDHT)
#define VIDEO_SEL_HEIGHT                (VIDEO_SEL_BOTTOM_INSET + VIDEO_SEL_TOP_INSET + MAX_COL_OF_VIDEO_SEL * (VIDEO_SEL_COL_HEIGHT + VIDEO_SEL_COL_DTANCE) - VIDEO_SEL_COL_DTANCE)

#define VIDEO_SEL_FRAME_WIDTH           VIDEO_SEL_WIDTH
#define VIDEO_SEL_FRAME_HEIGHT          VIDEO_SEL_HEIGHT
#define VIDEO_SEL_FRAME_LEFT            (BANNER_FRAME_LEFT)
#define VIDEO_SEL_FRAME_TOP             (BANNER_FRAME_TOP + CH_FRAME_HEIGHT + NAV_HEIGHT(4))

#define VIDEO_SEL_BK_ALPHA              DEFAULT_BK_ALPHA
#define VIDEO_SEL_ELM_BK_ALPHA          LST_BOX_ELM_BK_ALPHA
#define VIDEO_SEL_TITLE_FG_ALPHA        LST_BOX_TITLE_FG_ALPHA
#define VIDEO_SEL_TITLE_BK_ALPHA        LST_BOX_TITLE_BK_ALPHA

/* Lower left message OSD */
#define LOWER_LEFT_MSG_WIDTH            NAV_WIDTH(300)
#define LOWER_LEFT_MSG_HEIGHT           NAV_HEIGHT(56)
#define LOWER_LEFT_MSG_LEFT             (SAFE_DISPLAY_LEFT)
#define LOWER_LEFT_MSG_TOP              (SAFE_DISPLAY_TOP  + SAFE_DISPLAY_HEIGHT - SCRN_MODE_FRAME_HEIGHT)

/* screen mode */
#define SCRN_MODE_FG_COLOR(__clr_type)  NAV_COLOR(NAV_COLOR_ID_TEXT)

#define SCRN_MODE_FRAME_WIDTH           LOWER_LEFT_MSG_WIDTH
#define SCRN_MODE_FRAME_HEIGHT          LOWER_LEFT_MSG_HEIGHT
#define SCRN_MODE_FRAME_LEFT            LOWER_LEFT_MSG_LEFT
#define SCRN_MODE_FRAME_TOP             LOWER_LEFT_MSG_TOP

#define SCRN_MODE_MSG_LEFT              NAV_WIDTH(0)
#define SCRN_MODE_MSG_TOP               NAV_HEIGHT(0)
#define SCRN_MODE_MSG_WIDTH             SCRN_MODE_FRAME_WIDTH
#define SCRN_MODE_MSG_HEIGHT            SCRN_MODE_FRAME_HEIGHT

/* spperated cc info */
#define CC_INFO_FRAME_WIDTH             NAV_WIDTH(300)
#define CC_INFO_FRAME_HEIGHT            NAV_HEIGHT(30)
#define CC_INFO_FRAME_LEFT              (SAFE_DISPLAY_LEFT + (SAFE_DISPLAY_WIDTH - CC_INFO_FRAME_WIDTH)/2 - NAV_WIDTH(18))
#define CC_INFO_FRAME_TOP               (SAFE_DISPLAY_TOP  + NAV_HEIGHT(310))

#define CC_INFO_MSG_LEFT                NAV_WIDTH(52)
#define CC_INFO_MSG_TOP                 NAV_HEIGHT(0)
#define CC_INFO_MSG_WIDTH               (CC_INFO_FRAME_WIDTH - CC_INFO_MSG_LEFT)
#define CC_INFO_MSG_HEIGHT              CC_INFO_FRAME_HEIGHT

#define CC_INFO_ICON_LEFT               NAV_WIDTH(0)
#define CC_INFO_ICON_TOP                NAV_HEIGHT(0)
#define CC_INFO_ICON_WIDTH              NAV_WIDTH(52)
#define CC_INFO_ICON_HEIGHT             CC_INFO_FRAME_HEIGHT

#define CC_INFO_BK_ALPHA                100
#define CC_INFO_FG_ALPHA                255
#define CC_INFO_FG_COLOR                NAV_COLOR_TEXT

/* spperated audio info */
/*
#define AUDIO_INFO_FRAME_WIDTH          NAV_WIDTH(600)
#define AUDIO_INFO_FRAME_HEIGHT         NAV_HEIGHT(60)
#define AUDIO_INFO_FRAME_LEFT           (SAFE_DISPLAY_LEFT)
#define AUDIO_INFO_FRAME_TOP            (SAFE_DISPLAY_TOP  + NAV_HEIGHT(45))

#define AUDIO_INFO_MSG_LEFT             NAV_WIDTH(0)
#define AUDIO_INFO_MSG_TOP              NAV_HEIGHT(0)
#define AUDIO_INFO_MSG_WIDTH            AUDIO_INFO_FRAME_WIDTH
#define AUDIO_INFO_MSG_HEIGHT           AUDIO_INFO_FRAME_HEIGHT
*/

#define AUDIO_INFO_FG_COLOR             NAV_COLOR_TEXT

/* macors for video hight algorithm */
#define VID_VGA_RESLOUTION_FMT          "%dx%d@%dHz"
#define VID_DETAIL_RESLOUTION_FMT       "%dx%d%s"
#define VID_RESLOUTION_FMT              "%d%s %s"
#define VID_PROGRESSIVE                 "p"
#define VID_INTERLACE                   "i"
#define VID_UHD                         "UHD"
#define VID_HD                          "HD"
#define VID_SD                          "SD"
#define VID_STRING_MAX_LEN              ((UINT32)32)

#define AUD_ORDER_FMT_LONG              "%d/%d"
#define AUD_ORDER_FMT_SHORT             "%d."
#define AUD_ORDER_MAX_LEN               ((UINT32)11)
#define AUD_STRING_MAX_LEN              ((UINT32)64)

/* font family */
#define NAV_FONT_BIG                    SN_FONT_DEFAULT_BIG
#define NAV_FONT_NORMAL                 SN_FONT_DEFAULT
#ifdef APP_NAV_BNR_NEXT_EVENT_SUPPORT
    #define NAV_FONT_SMALL                  "nav_small_font"
#endif

#define EVENT_START_END_TIME_FORMAT     "%d:%02d %s - %d:%02d %s"
#define EVENT_START_END_EX_TIME_FORMAT  "%d:%02d %s - %d:%02d %s (%d:%02d)"
#define ANTE_MERIDIEM                   "AM"
#define POST_MERIDIEM                   "PM"
#define NOON_HOUR                       (12)
#define MIDNIGHT_HOUR                   (0)
#define NOON_DISPLAY_HOUR               (12)
#define MIDNIGHT_DISPLAY_HOUR           (12)

#ifdef APP_IMG_UI
#define DEFAULT_BK_ALPHA                255
#else
#define DEFAULT_BK_ALPHA                220
#endif
#define DEFAULT_FG_ALPHA                255
#define LST_BOX_BK_ALPHA                180
#define LST_BOX_ELM_BK_ALPHA            0
#define LST_BOX_TITLE_FG_ALPHA          255
#define LST_BOX_TITLE_BK_ALPHA          0

/* ch bar */
#define CH_NAME_FG_COLOR(__color_type)          NAV_COLOR(NAV_COLOR_ID_TEXT)
#define CH_NUMBER_FG_COLOR(__color_type)        NAV_COLOR(NAV_COLOR_ID_TEXT)
#ifdef APP_CLRQAM_SUPPORT

#define INPUT_SRC_NAME_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)
#endif
#define CH_FRAME_BK_ALPHA                       DEFAULT_BK_ALPHA
/* prog */
#define PROG_TITLE_FG_COLOR(__color_type)       NAV_COLOR(NAV_COLOR_ID_TEXT)

    #define PROG_TIME_FG_COLOR(__color_type)        NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)
    #define PROG_RATING_FG_COLOR(__color_type)      NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)
    #define PROG_AUDIO_INFO_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)
    #define PROG_VIDEO_INFO_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)
    #define PROG_CC_DESC_FG_COLOR(__color_type)     NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)
#define INFO_FRAME_BK_ALPHA                     DEFAULT_BK_ALPHA

#ifdef APP_NAV_BNR_NEXT_EVENT_SUPPORT
    #define NEXT_PROG_TIME_FG_COLOR(__color_type)        NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)
    #define NEXT_PROG_TITLE_FG_COLOR(__color_type)       NAV_COLOR(NAV_COLOR_ID_TEXT)
#endif

/* prog detail */

#define PROG_DETAIL_FG_COLOR(__color_type)      NAV_COLOR(NAV_COLOR_ID_TEXT)

#define PROG_DETAIL_IDX_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)
#define PROG_DETAIL_FRAME_BK_ALPHA              DEFAULT_BK_ALPHA

/* ch detail*/
#define CH_DETAIL_TITLE_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)
#define CH_DETAIL_FG_COLOR(__color_type)        NAV_COLOR(NAV_COLOR_ID_TEXT)
#define CH_DETAIL_IDX_FG_COLOR(__color_type)    NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)

/* ch list color */
#define CH_LIST_TITLE_FG_COLOR(__color_type)    NAV_COLOR(NAV_COLOR_ID_TEXT)
#define CH_LIST_HELP_MSG_FG_COLOR(__color_type) NAV_COLOR(NAV_COLOR_ID_TEXT)
#define CH_LIST_TITLE_BK_COLOR(__color_type)    NAV_COLOR(NAV_COLOR_ID_CONTENT)

#define CH_LIST_COL_N_FG_COLOR(__color_type)    NAV_COLOR(NAV_COLOR_ID_TEXT)
#define CH_LIST_COL_D_FG_COLOR(__color_type)    NAV_COLOR(NAV_COLOR_ID_TEXT)
#define CH_LIST_COL_H_FG_COLOR(__color_type)    NAV_COLOR(NAV_COLOR_ID_TEXT)
#define CH_LIST_COL_HU_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)
#define CH_LIST_COL_P_FG_COLOR(__color_type)    NAV_COLOR(NAV_COLOR_ID_TEXT)
#define CH_LIST_COL_S_FG_COLOR(__color_type)    NAV_COLOR(NAV_COLOR_ID_TEXT)
#define CH_LIST_COL_SD_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)


/* fav list color */
#define FAV_LIST_COL_N_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)
#define FAV_LIST_COL_D_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)
#define FAV_LIST_COL_H_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)
#define FAV_LIST_COL_HU_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT)
#define FAV_LIST_COL_P_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)
#define FAV_LIST_COL_S_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)
#define FAV_LIST_COL_SD_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT)
#define FAV_LIST_TITLE_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)
#define FAV_LIST_TITLE_BK_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_CONTENT)

/* pwd color */
#define PWD_TITLE_FG_COLOR(__color_type)        NAV_COLOR(NAV_COLOR_ID_TEXT)
#define PWD_BOX_FG_D_FG_COLOR(__color_type)     NAV_COLOR(NAV_COLOR_ID_TEXT)
#define PWD_BOX_FG_E_FG_COLOR(__color_type)     NAV_COLOR(NAV_COLOR_ID_TEXT)
#define PWD_BOX_FG_H_FG_COLOR(__color_type)     NAV_COLOR(NAV_COLOR_ID_TEXT_COMP)
#define PWD_BOX_FG_D_BK_COLOR(__color_type)     NAV_COLOR(NAV_COLOR_ID_MAIN)
#define PWD_BOX_FG_E_BK_COLOR(__color_type)     NAV_COLOR(NAV_COLOR_ID_MAIN)
#define PWD_BOX_FG_H_BK_COLOR(__color_type)     NAV_COLOR(NAV_COLOR_ID_HLT)
#define PWD_BDR_FG_D_BK_COLOR(__color_type)     NAV_COLOR(NAV_COLOR_ID_TEXT)
#define PWD_BDR_FG_E_BK_COLOR(__color_type)     NAV_COLOR(NAV_COLOR_ID_TEXT)
#define PWD_BDR_FG_H_BK_COLOR(__color_type)     NAV_COLOR(NAV_COLOR_ID_TEXT)

/* volume color */
#define VOLUME_TITLE_D_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)
#define VOLUME_TITLE_E_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)
#define VOLUME_TITLE_H_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)

#define VOLUME_D_FG_COLOR(__color_type)         NAV_COLOR(NAV_COLOR_ID_TEXT_COMP)
#define VOLUME_E_FG_COLOR(__color_type)         NAV_COLOR(NAV_COLOR_ID_TEXT_COMP)
#define VOLUME_H_FG_COLOR(__color_type)         NAV_COLOR(NAV_COLOR_ID_TEXT_COMP)

/* twinkle msg color */
#define TWINKLE_TITLE_FG_COLOR(__color_type)    NAV_COLOR(NAV_COLOR_ID_TEXT)

/* multiple video selection */
#define VIDEO_SEL_COL_N_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT)
#define VIDEO_SEL_COL_D_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT)
#define VIDEO_SEL_COL_H_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT_COMP)
#define VIDEO_SEL_COL_HU_FG_COLOR(__color_type) NAV_COLOR(NAV_COLOR_ID_TEXT_COMP)
#define VIDEO_SEL_COL_P_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT)
#define VIDEO_SEL_COL_S_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT)
#define VIDEO_SEL_COL_SD_FG_COLOR(__color_type) NAV_COLOR(NAV_COLOR_ID_TEXT)
#define VIDEO_SEL_TITLE_FG_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_TEXT_HLT)
#define VIDEO_SEL_TITLE_BK_COLOR(__color_type)  NAV_COLOR(NAV_COLOR_ID_CONTENT)

/* others */
#define PLS_SCAN_TITLE_FG_COLOR(__color_type)   NAV_COLOR(NAV_COLOR_ID_TEXT)

/* zoom */
#define  ARROW_SIZE                      NAV_WIDTH(25)
#define  CROSS_SIZE                      NAV_WIDTH(50)

#define PWD_DLG_FONT_INSET               (0)

#endif /* _NAV_VIEW_H_ */
