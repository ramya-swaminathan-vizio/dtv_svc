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

#ifndef _MMP_AUDIO_PLAYER_RC_H_
#define _MMP_AUDIO_PLAYER_RC_H_

#include "u_irrc_btn_def.h"


#include "res/mmp/common_ui/mmp_common_ui_rc.h"
#include "mmp/mmp_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*Cover pic*/
#define MMP_AP_RC_COV_PIC_X             (240)
#define MMP_AP_RC_COV_PIC_Y             (118)
#define MMP_AP_RC_COV_PIC_W             (170)
#define MMP_AP_RC_COV_PIC_H             (182)

#define MMP_AP_RC_LYRIC_X             (400)
#define MMP_AP_RC_LYRIC_Y             (0)
#define MMP_AP_RC_LYRIC_W             (500)
#define MMP_AP_RC_LYRIC_H             (400)

/*-----Key definition-----*/
#define AUDIO_PLAYER_BTN_REPEAT      BTN_REPEAT
#define AUDIO_PLAYER_BTN_DINFO       BTN_BLUE
#define AUDIO_PLAYER_BTN_EXIT        BTN_EXIT
#define AUDIO_PLAYER_BTN_NEXT        BTN_PRG_UP
#define AUDIO_PLAYER_BTN_PREV        BTN_PRG_DOWN
#define AUDIO_PLAYER_BTN_PLAY_PAUSE  BTN_SELECT
#define AUDIO_PLAYER_BTN_STOP        BTN_FAV_CH
#define AUDIO_PLAYER_BTN_FF          BTN_FF
#define AUDIO_PLAYER_BTN_FR          BTN_FR
#define AUDIO_PLAYER_BTN_INFO        BTN_PRG_INFO
#define AUDIO_PLAYER_BTN_AB_REPEAT   BTN_SWAP

#define AUDIO_PLAYER_BTN_FSEEK       BTN_CURSOR_RIGHT
#define AUDIO_PLAYER_BTN_BSEEK       BTN_CURSOR_LEFT

#define AUDIO_PLAYER_BTN_SHUFFLE     BTN_GREEN
#define AUDIO_PLAYER_BTN_AUD_ONLY    BTN_YELLOW

#define AUDIO_PLAYER_BTN_REPEAT_2      BTN_RED
#define AUDIO_PLAYER_BTN_PLAY_PAUSE_2  BTN_FAVORITE
#define AUDIO_PLAYER_BTN_NEXT_2      BTN_NEXT
#define AUDIO_PLAYER_BTN_PREV_2      BTN_PREV
#define AUDIO_PLAYER_BTN_STOP_2      BTN_STOP
#define AUDIO_PLAYER_BTN_PLAY        BTN_PLAY
#define AUDIO_PLAYER_BTN_PAUSE       BTN_PAUSE

#define AUDIO_PLAYER_BTN_OPTION      BTN_MENU
#define AUDIO_LYRIC_BTN_OPTION       BTN_DIGIT_9

#define MMP_AP_RC_FILE_MAX_LEN               ((UINT32) 63)

#define MMP_AP_INFO_MAX_STR_LEN              (128)

#define MMP_AP_RC_FILE_PATH_DIV_CHAR            ((CHAR)'/')

/*-----Time delay definition-----*/
#define MMP_AP_TIMER_INVALID_FILE_MSG_DELAY       (3*1000)
#define MMP_AP_TIMER_TIMEOUT_DELAY                (1000)
#define MMP_AP_TIMER_HIDE_MSG                    (3*1000)

#define MMP_AP_TIMER_OPTION_LIST                  (10*1000)
#define MMP_AP_TIMER_CEC_SAC_VOL                  (5*1000)


#define IOM_HOTKEY_RPT_EVT_ITVL_FST    (40)
#define IOM_HOTKEY_RPT_EVT_ITVL_OTHER  (7)

#define MMP_AP_SEEK_DUR                (3)/*3 sec*/

#define MMP_AP_RC_GET_FILTED_BTN()                              \
{                                                               \
    AUDIO_PLAYER_BTN_FF,                                        \
    AUDIO_PLAYER_BTN_FR,                                        \
    AUDIO_PLAYER_BTN_PLAY_PAUSE,                                \
    AUDIO_PLAYER_BTN_PLAY_PAUSE_2,                                \
    BTN_CURSOR_LEFT,                                            \
    BTN_CURSOR_RIGHT,                                           \
    0                                                           \
}
#endif /*_MMP_AUDIO_PLAYER_RC_H_*/
