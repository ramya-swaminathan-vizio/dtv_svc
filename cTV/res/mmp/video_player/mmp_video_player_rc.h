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
 * $RCSfile: mmp_video_player_rc.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *         This header file contains public interfaces, constant and type
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/

#ifndef _MMP_VIDEO_PLAYER_RC_H_
#define _MMP_VIDEO_PLAYER_RC_H_

#include "u_irrc_btn_def.h"
#include "u_img_tfx.h"

#include "mmp/mmp_common.h"

#include MMP_MLM_HEADER_FILE
#include "res/mmp/common_ui/mmp_common_ui_rc.h"
#include "res/mmp/img/mmp_img.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*******************************************************************************
********************************************************************************
                          Video Player
*******************************************************************************
*******************************************************************************/

#define MMP_VP_RC_MAIN_X                    (0)
#define MMP_VP_RC_MAIN_Y                    (0)
#define MMP_VP_RC_MAIN_W                    (1920)//(FRM_TOOLBAR_W)
#define MMP_VP_RC_MAIN_H                    (1080)//(FRM_TOOLBAR_Y + FRM_TOOLBAR_H)

#define _MMP_VP_RC_DP_GET_CONFIG()      {                                      \
    { MLM_MMP_KEY_DP_TITLE,                 MMP_VE_INFO_ID_TITLE      },       \
    { MLM_MMP_KEY_DP_DIRECTOR,              MMP_VE_INFO_ID_DIRECTOR   },       \
    { MLM_MMP_KEY_DP_COPYRIGHT,             MMP_VE_INFO_ID_COPYRIGHT  },       \
    { MLM_MMP_KEY_DP_DT,                    MMP_VE_INFO_ID_DATE       },       \
    { MLM_MMP_KEY_DP_GENRE,                 MMP_VE_INFO_ID_GENRE      },       \
    { MLM_MMP_KEY_DP_DURATION,              MMP_VE_INFO_ID_DURATION   },       \
    { MLM_MMP_KEY_DP_NEXT,                  MMP_VE_INFO_ID_INVAL      }        \
}

/*TEXT AUDIO*/
#define MMP_VP_RC_TXT_AUDIO_X               ((MMP_VP_RC_MAIN_W-MMP_VP_RC_TXT_AUDIO_W)/2)
#define MMP_VP_RC_TXT_AUDIO_Y               ((MMP_VP_RC_MAIN_H-MMP_VP_RC_TXT_AUDIO_H)/2)
#define MMP_VP_RC_TXT_AUDIO_W               (500*4/3)
#define MMP_VP_RC_TXT_AUDIO_H               (40 * 5*4/3)

/*TEXT LOADING*/
#define MMP_VP_RC_TXT_LOADING_X             ((MMP_VP_RC_MAIN_W-MMP_VP_RC_TXT_LOADING_W)/2)
#define MMP_VP_RC_TXT_LOADING_Y             ((MMP_VP_RC_MAIN_H-MMP_VP_RC_TXT_LOADING_H)/2)
#define MMP_VP_RC_TXT_LOADING_W             (MMP_VP_RC_MAIN_W)
#define MMP_VP_RC_TXT_LOADING_H             (40*4/3)

#ifdef APP_COLOR_MODE_PALLET
#define MMP_VP_GET_CLR_BK() { 255, { 0 }, { 0 }, { MMP_CLR_IDX_GET_WHITE() }}
#else
#define MMP_VP_GET_CLR_BK() { 255, { 17 }, {92 }, { 156 }}
#endif

/*-----Key definition-----*/
#define VIDEO_PLAYER_BTN_REPEAT             BTN_REPEAT
#define VIDEO_PLAYER_BTN_ZOOM               BTN_ZOOM
#define VIDEO_PLAYER_BTN_INFO               BTN_BLUE
#define VIDEO_PLAYER_BTN_PIC_MODE           BTN_GREEN
#define VIDEO_PLAYER_BTN_EXIT               BTN_EXIT
#define VIDEO_PLAYER_BTN_NEXT               BTN_PRG_UP
#define VIDEO_PLAYER_BTN_PREV               BTN_PRG_DOWN
#define VIDEO_PLAYER_BTN_PLAY               BTN_PLAY
#define VIDEO_PLAYER_BTN_PAUSE              BTN_PAUSE
#define VIDEO_PLAYER_BTN_PLAY_PAUSE         BTN_SELECT
#define VIDEO_PLAYER_BTN_PLAY_PAUSE_2       BTN_FAVORITE
#define VIDEO_PLAYER_BTN_STOP               BTN_FAV_CH
#define VIDEO_PLAYER_BTN_STOP_2             BTN_STOP
#define VIDEO_PLAYER_BTN_STOP_3             BTN_RETURN
#define VIDEO_PLAYER_BTN_MTS                BTN_MTS
#define VIDEO_PLAYER_BTN_SUB                BTN_CC
#define VIDEO_PLAYER_BTN_FF                 BTN_FF
#define VIDEO_PLAYER_BTN_FR                 BTN_FR
#define VIDEO_PLAYER_BTN_HIDE               BTN_PRG_INFO
#define VIDEO_PLAYER_BTN_REG_CODE           BTN_YELLOW
#define VIDEO_PLAYER_BTN_SET_TIME           BTN_TIMER
#define VIDEO_PLAYER_BTN_OPTION             BTN_MENU

#define VIDEO_PLAYER_BTN_SLOW_FF            BTN_CUSTOM_110
#define VIDEO_PLAYER_BTN_SLOW_FR            BTN_CUSTOM_111
#define MMP_VP_RC_TEXT_MULTILINE_STYLE      (WGL_STL_TEXT_MULTILINE|WGL_STL_TEXT_MAX_128)

#define MMP_VP_RC_FILE_MAX_LEN              ((UINT32) 63)
#define MMP_VP_RC_FILE_PATH_DIV_CHAR        ((CHAR)'/')
#define MMP_VP_INFO_MAX_STR_LEN             (256)


/*-----Time delay definition-----*/
#define MMP_VP_TIMER_PIC_MODE               (3000)
#define MMP_VP_TIMER_HIDE_MSG_DELAY         (3000)
#define MMP_VP_TIMER_TIMEOUT_DELAY          (500)
#define MMP_VP_TIMER_VIERER_HIDE            (10000)
#define MMP_VP_TIMER_BTN_FILTER             (200)
#define MMP_VP_TIMER_RESET_ICON             (2000)
#define MMP_VP_TIMER_CEC_SAC_VOL            (5000)

#define MMP_VP_RC_GET_FILTED_BTN()                                             \
{                                                                              \
    VIDEO_PLAYER_BTN_SUB,                                                      \
    VIDEO_PLAYER_BTN_MTS,                                                      \
    VIDEO_PLAYER_BTN_FF,                                                       \
    VIDEO_PLAYER_BTN_FR,                                                       \
    VIDEO_PLAYER_BTN_PLAY_PAUSE,                                               \
    BTN_CURSOR_LEFT,                                                           \
    BTN_CURSOR_RIGHT,                                                          \
    0                                                                          \
}

#define MMP_VP_RC_FILTED_BTN_NUM            ((UINT16) 10)

/*******************************************************************************
Video Player End
*******************************************************************************/

#endif /*_MMP_VIDEO_PLAYER_RC_H_*/

