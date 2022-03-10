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
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_REC_TSHIFT_VIEW_CUSTOM_H_
#define _NAV_REC_TSHIFT_VIEW_CUSTOM_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#include "app_util/a_common.h"
#include "nav/record/a_nav_rec.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/* Timer */
#define TSHIFT_REFRESH_DELAY        500
#define TSHIFT_HIDE_DELAY           5000
#define TSHIFT_PAUSE_HIDE_DELAY     5000
#define TSHIFT_MSG_HIDE_DELAY       5000

/* How many seconds the BTN_NEXT and BTN_PREV would jump over*/
#define TSHIFT_STEP_SECS            10

/* Fast foward loop */
#define TSHIFT_FF_LOOP          \
{                               \
    MM_SPEED_TYPE_FORWARD_1X,   \
    MM_SPEED_TYPE_FORWARD_2X,   \
    MM_SPEED_TYPE_FORWARD_4X,   \
    MM_SPEED_TYPE_FORWARD_8X,   \
    MM_SPEED_TYPE_FORWARD_16X,  \
    MM_SPEED_TYPE_FORWARD_32X,  \
}

/* Fast Rewind loop */
#define TSHIFT_FR_LOOP          \
{                               \
    MM_SPEED_TYPE_FORWARD_1X,   \
    MM_SPEED_TYPE_REWIND_2X,    \
    MM_SPEED_TYPE_REWIND_4X,    \
    MM_SPEED_TYPE_REWIND_8X,    \
    MM_SPEED_TYPE_REWIND_16X,   \
    MM_SPEED_TYPE_REWIND_32X,   \
}

#define TSHIFT_OSD_W                (1280)
#define TSHIFT_OSD_H                (720)
#define TSHIFT_OSD(_x)              ((_x)*0.75)

/* Root frame */
#define TSHIFT_FRM_X                (TSHIFT_OSD( TSHIFT_OSD_W ) - TSHIFT_FRM_W) / 2
#define TSHIFT_FRM_Y                (DISPLAY_HEIGHT - TSHIFT_FRM_H - TSHIFT_OSD( 60 ))
#define TSHIFT_FRM_W                TSHIFT_OSD( 540 )
#define TSHIFT_FRM_H                TSHIFT_OSD( 80 )

/* Record status */
#define TSHIFT_REC_STATUS_X         TSHIFT_OSD( 10 )
#define TSHIFT_REC_STATUS_Y         TSHIFT_OSD( 10 )
#define TSHIFT_REC_STATUS_W         TSHIFT_OSD( 40 )
#define TSHIFT_REC_STATUS_H         TSHIFT_OSD( 15 )

/* Playback status */
#define TSHIFT_PB_STATUS_X          TSHIFT_OSD( 10 )
#define TSHIFT_PB_STATUS_Y          TSHIFT_OSD( 30 )
#define TSHIFT_PB_STATUS_W          TSHIFT_OSD( 40 )
#define TSHIFT_PB_STATUS_H          TSHIFT_OSD( 45 )

/* Playback speed */
#define TSHIFT_PB_SPEED_X           TSHIFT_OSD( 60 )
#define TSHIFT_PB_SPEED_Y           TSHIFT_OSD( 30 )
#define TSHIFT_PB_SPEED_W           TSHIFT_OSD( 40 )
#define TSHIFT_PB_SPEED_H           TSHIFT_OSD( 45 )

/* Timer bar */
#define TSHIFT_TIME_BAR_X           TSHIFT_OSD( 105 )
#define TSHIFT_TIME_BAR_Y           TSHIFT_OSD( 0 )
#define TSHIFT_TIME_BAR_W           (TSHIFT_FRM_W - TSHIFT_TIME_BAR_X - TSHIFT_OSD( 10 ))
#define TSHIFT_TIME_BAR_H           TSHIFT_FRM_H
#define TSHIFT_TIME_BAR_TIME_Y      TSHIFT_OSD( 10 )
#define TSHIFT_TIME_BAR_TIME_H      TSHIFT_OSD( 30 )
#define TSHIFT_TIME_BAR_BAR_Y       TSHIFT_OSD( 40 )
#define TSHIFT_TIME_BAR_BAR_H       TSHIFT_OSD( 30 )
#define TSHIFT_TIME_BAR_INSET_L     TSHIFT_OSD( 2 )
#define TSHIFT_TIME_BAR_INSET_R     TSHIFT_OSD( 2 )
#define TSHIFT_TIME_BAR_INSET_T     TSHIFT_OSD( 2 )
#define TSHIFT_TIME_BAR_INSET_B     TSHIFT_OSD( 2 )

/* Playback Time */
#define TSHIFT_PB_TIME_X            TSHIFT_OSD( 10 )
#define TSHIFT_PB_TIME_Y            TSHIFT_OSD( 10 )
#define TSHIFT_PB_TIME_W            TSHIFT_OSD( 90 )
#define TSHIFT_PB_TIME_H            TSHIFT_OSD( 30 )
#define TSHIFT_PB_TIME_ALIGN        (WGL_AS_RIGHT_TOP)

/* Broadcast Time */
#define TSHIFT_BRDCST_TIME_X        TSHIFT_OSD( 0 )
#define TSHIFT_BRDCST_TIME_Y        TSHIFT_OSD( 0 )
#define TSHIFT_BRDCST_TIME_W        TSHIFT_OSD( 1 )
#define TSHIFT_BRDCST_TIME_H        TSHIFT_OSD( 1 )
#define TSHIFT_BRDCST_TIME_ALIGN    (WGL_AS_RIGHT_TOP)

/*-----------------------------------------------------------------------------
    Mini
-----------------------------------------------------------------------------*/
#define TSHIFT_MINI_FRM_X                TSHIFT_OSD( 0 )
#define TSHIFT_MINI_FRM_Y                TSHIFT_OSD( (TSHIFT_OSD_H - 45) )
#define TSHIFT_MINI_FRM_W                TSHIFT_OSD( 150 )
#define TSHIFT_MINI_FRM_H                TSHIFT_OSD( 45 )

#define TSHIFT_MINI_TXT_X                TSHIFT_OSD( 0 )
#define TSHIFT_MINI_TXT_Y                TSHIFT_OSD( 0 )
#define TSHIFT_MINI_TXT_W                TSHIFT_MINI_FRM_W
#define TSHIFT_MINI_TXT_H                TSHIFT_MINI_FRM_H
#define TSHIFT_MINI_TXT_ALIGN            WGL_AS_CENTER_CENTER

/*-----------------------------------------------------------------------------
    Msg
-----------------------------------------------------------------------------*/
#define TSHIFT_MSG_FRM_X                ((DISPLAY_WIDTH - TSHIFT_FRM_W ) / 2)
#define TSHIFT_MSG_FRM_Y                (TSHIFT_FRM_Y - TSHIFT_MSG_FRM_H)
#define TSHIFT_MSG_FRM_W                (TSHIFT_FRM_W)
#define TSHIFT_MSG_FRM_H                TSHIFT_OSD( 80 )

#define TSHIFT_MSG_TXT_X                TSHIFT_OSD( 0 )
#define TSHIFT_MSG_TXT_Y                TSHIFT_OSD( 0 )
#define TSHIFT_MSG_TXT_W                TSHIFT_MSG_FRM_W
#define TSHIFT_MSG_TXT_H                TSHIFT_MSG_FRM_H
#define TSHIFT_MSG_TXT_INSET_L          TSHIFT_OSD( 10 )
#define TSHIFT_MSG_TXT_INSET_R          TSHIFT_OSD( 10 )
#define TSHIFT_MSG_TXT_INSET_T          TSHIFT_OSD( 0 )
#define TSHIFT_MSG_TXT_INSET_B          TSHIFT_OSD( 0 )

/*-----------------------------------------------------------------------------
    Wizard
-----------------------------------------------------------------------------*/
/* Wizard */
#define  TSHIFT_WZD_FRM_MAIN_W          TSHIFT_OSD( 788 )
#define  TSHIFT_WZD_FRM_MAIN_H          TSHIFT_OSD( 440 )
#define  TSHIFT_WZD_FRM_MAIN_X          ((TSHIFT_OSD( TSHIFT_OSD_W ) - TSHIFT_WZD_FRM_MAIN_W)/2)
#define  TSHIFT_WZD_FRM_MAIN_Y          ((TSHIFT_OSD( TSHIFT_OSD_H ) - TSHIFT_WZD_FRM_MAIN_H)/2)

#define  TSHIFT_WZD_TXT_TITLE_X         TSHIFT_OSD( 34 )
#define  TSHIFT_WZD_TXT_TITLE_Y         TSHIFT_OSD( 0 )
#define  TSHIFT_WZD_TXT_TITLE_W         TSHIFT_OSD( 400 )
#define  TSHIFT_WZD_TXT_TITLE_H         TSHIFT_OSD( 60 )
#define  TSHIFT_WZD_TXT_TITLE_STYLE     WGL_STL_TEXT_MAX_128

#define  TSHIFT_WZD_TXT_MSG_X           TSHIFT_OSD( 34 )
#define  TSHIFT_WZD_TXT_MSG_Y           TSHIFT_OSD( 80 )
#define  TSHIFT_WZD_TXT_MSG_W           TSHIFT_OSD( 720 )
#define  TSHIFT_WZD_TXT_MSG_W_2         TSHIFT_OSD( 534 )     /*only for size selection page */
#define  TSHIFT_WZD_TXT_MSG_H           TSHIFT_OSD( 300 )
#define  TSHIFT_WZD_TXT_MSG_STYLE       WGL_STL_TEXT_MAX_512 | WGL_STL_TEXT_MULTILINE | WGL_STL_TEXT_MAX_DIS_10_LINE

#define  TSHIFT_WZD_LB_OPT_X            TSHIFT_OSD( 568 )
#define  TSHIFT_WZD_LB_OPT_Y            TSHIFT_OSD( 278 )
#define  TSHIFT_WZD_LB_OPT_W            TSHIFT_OSD( 160 )
#define  TSHIFT_WZD_LB_OPT_H            TSHIFT_OSD( 88 )
#define  TSHIFT_WZD_LB_OPT_ELEM_H       33

#define  TSHIFT_WZD_LB_SIZE_X           TSHIFT_OSD( 568 )
#define  TSHIFT_WZD_LB_SIZE_Y           TSHIFT_OSD( 80 )
#define  TSHIFT_WZD_LB_SIZE_W           TSHIFT_OSD( 160 )
#define  TSHIFT_WZD_LB_SIZE_H           TSHIFT_OSD( 264 )
#define  TSHIFT_WZD_LB_SIZE_ELEM_H      33

#define  TSHIFT_WZD_LB_HELP_X           TSHIFT_OSD( 10 )
#define  TSHIFT_WZD_LB_HELP_Y           TSHIFT_OSD( 405 )
#define  TSHIFT_WZD_LB_HELP_W           TSHIFT_OSD( 768 )
#define  TSHIFT_WZD_LB_HELP_H           TSHIFT_OSD( 30 )
#define  TSHIFT_WZD_LB_HELP_IMG_W       TSHIFT_OSD( 50 )
#define  TSHIFT_WZD_LB_HELP_TXT_W       TSHIFT_OSD( 142 )

#define  TSHIFT_WZD_PB_PROG_X           TSHIFT_OSD( 34 )
#define  TSHIFT_WZD_PB_PROG_Y           TSHIFT_OSD( 140 )
#define  TSHIFT_WZD_PB_PROG_W           TSHIFT_OSD( 600 )
#define  TSHIFT_WZD_PB_PROG_H           TSHIFT_OSD( 30 )
#define  TSHIFT_WZD_PB_PROG_INSET_T     TSHIFT_OSD( 2 )
#define  TSHIFT_WZD_PB_PROG_INSET_B     TSHIFT_OSD( 2 )
#define  TSHIFT_WZD_PB_PROG_INSET_L     TSHIFT_OSD( 2 )
#define  TSHIFT_WZD_PB_PROG_INSET_R     TSHIFT_OSD( 2 )

#define  TSHIFT_WZD_LB_STATUS_X         TSHIFT_OSD( 34 )
#define  TSHIFT_WZD_LB_STATUS_Y         TSHIFT_OSD( 80 )
#define  TSHIFT_WZD_LB_STATUS_W         (TSHIFT_WZD_FRM_MAIN_W - TSHIFT_OSD( 68 ))
#define  TSHIFT_WZD_LB_STATUS_H         (TSHIFT_WZD_FRM_MAIN_H - TSHIFT_OSD( 100 ))
#define  TSHIFT_WZD_LB_STATUS_ELEM_H    TSHIFT_OSD( 45 )

/* The available file size. Size in MB */

#define TSHIFT_WZD_FILE_SIZE_ARRAY  \
{                                   \
    512,                            \
    1024,                           \
    1024 + 512,                     \
    1024 * 2,                       \
    1024 * 2 + 512,                 \
    1024 * 3,                       \
    1024 * 3 + 512,                 \
    1024 * 4,                       \
    1024 * 5,                       \
    1024 * 6,                       \
    1024 * 7,                       \
    1024 * 8,                       \
    1024 * 9,                       \
    1024 * 10,                      \
    1024 * 11,                      \
    1024 * 12,                      \
    1024 * 13,                      \
    1024 * 14,                      \
    1024 * 15,                      \
    1024 * 16,                      \
    1024 * 17,                      \
    1024 * 18,                      \
    1024 * 19,                      \
    1024 * 20,                      \
    1024 * 21,                      \
    1024 * 22,                      \
    1024 * 23,                      \
    1024 * 24,                      \
    1024 * 25,                      \
    1024 * 26,                      \
    1024 * 27,                      \
    1024 * 28,                      \
    1024 * 29,                      \
    1024 * 30,                      \
    1024 * 31,                      \
}

#define TSHIFT_WZD_FILE_SIZE_DFT_IDX    0

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

#endif /* _NAV_REC_TSHIFT_VIEW_CUSTOM_H_ */
