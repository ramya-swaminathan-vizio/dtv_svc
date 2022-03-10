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
 * $RCSfile: mmp_img.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/8 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: fad6e0fd4edaccd0084a192f40b2c916 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _MMP_IMG_API_H_
#define _MMP_IMG_API_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_common.h"

#include "mmp/mmp_common.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/*-----Image-----*/

#define MMP_SCANNING_ANI_IMG_NUM    4
extern  WGL_HIMG_TPL_T            ah_g_mmp_scanning_img [MMP_SCANNING_ANI_IMG_NUM];
#define MMP_SCANNING_ANI_ICON_IMG(_idx) ah_g_mmp_scanning_img[_idx]
 
typedef enum _MMP_IMG_IMAGE_ID_T
{
    MMP_IMG_IMAGE_ID_RED_ICON = 0,
    MMP_IMG_IMAGE_ID_GREEN_ICON,
    MMP_IMG_IMAGE_ID_YELLOW_ICON,
    MMP_IMG_IMAGE_ID_BLUE_ICON,
    MMP_IMG_IMAGE_ID_PLAY_ICON,
    MMP_IMG_IMAGE_ID_PAUSE_ICON,
    MMP_IMG_IMAGE_ID_STOP_ICON,
    MMP_IMG_IMAGE_ID_PREV_ICON,
    MMP_IMG_IMAGE_ID_NEXT_ICON,
    MMP_IMG_IMAGE_ID_VOL_ICON,
    MMP_IMG_IMAGE_ID_VOL_MUTE_ICON,
    MMP_IMG_IMAGE_ID_VOL_BAR,
    MMP_IMG_IMAGE_ID_VOL_BAR_BG,
    MMP_IMG_IMAGE_ID_STATUS_BAR,
    MMP_IMG_IMAGE_ID_PLAYBACK_PG_BAR,
    MMP_IMG_IMAGE_ID_AUDIO_MAIN_FRM,
    MMP_IMG_IMAGE_ID_TOOL_BAR,
    MMP_IMG_IMAGE_ID_DETAIL_PAGE,
    MMP_IMG_IMAGE_ID_REPEAT_ONCE,
    MMP_IMG_IMAGE_ID_REPEAT_ALL,
    MMP_IMG_IMAGE_ID_REPEAT_A,
    MMP_IMG_IMAGE_ID_REPEAT_AB,
    MMP_IMG_IMAGE_ID_REPEAT_ABX,
    MMP_IMG_IMAGE_ID_SHUFFLE,
    MMP_IMG_IMAGE_ID_FAST_FORWARD,
    MMP_IMG_IMAGE_ID_FAST_REWIND,
    MMP_IMG_IMAGE_ID_THUMBNAIL_PHOTO,
    MMP_IMG_IMAGE_ID_THUMBNAIL_FOLDER,
    MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER,
    MMP_IMG_IMAGE_ID_THUMBNAIL_MUSIC,
    MMP_IMG_IMAGE_ID_DETAIL_AUDIO,
    MMP_IMG_IMAGE_ID_HIGHLIGHT_THUMBNAIL,
    MMP_IMG_IMAGE_ID_HIGHLIGHT_THUMBNAIL_M,
    MMP_IMG_IMAGE_ID_HIGHLIGHT_THUMBNAIL_L,
    MMP_IMG_IMAGE_ID_SELECT_THUMBNAIL,
    MMP_IMG_IMAGE_ID_COPY_THUMBNAIL,
    MMP_IMG_IMAGE_ID_THUMBNAIL_TOP_BG,
    MMP_IMG_IMAGE_ID_THUMBNAIL_BTM_BG,
    MMP_IMG_IMAGE_ID_FOLDER_ICON,
    MMP_IMG_IMAGE_ID_MUSIC_ICON,
    MMP_IMG_IMAGE_ID_PHOTO_ICON,
    MMP_IMG_IMAGE_ID_VIDEO_ICON,
    MMP_IMG_IMAGE_ID_TXT_ICON,    
    MMP_IMG_IMAGE_ID_PAGE_ICON,
    MMP_IMG_IMAGE_ID_SIZE_ICON,
    MMP_IMG_IMAGE_ID_DURATION_ICON,
    MMP_IMG_IMAGE_ID_SCROLL_BAR_BK,
    MMP_IMG_IMAGE_ID_SCROLL_BAR,
    MMP_IMG_IMAGE_ID_STATUS_BAR_PLAY,
    MMP_IMG_IMAGE_ID_STATUS_BAR_PAUSE,
    MMP_IMG_IMAGE_ID_MUSIC_PLAY_ICON,
    MMP_IMG_IMAGE_ID_READ_ONLY_ICON,
    /*Added for video player*/
	MMP_IMG_IMAGE_ID_DIVX_BTN_NOR,
    MMP_IMG_IMAGE_ID_DIVX_BTN_HLT,
    MMP_IMG_IMAGE_ID_DIVX_FRM,
    MMP_IMG_IMAGE_ID_DIVX_TOP,
    MMP_IMG_IMAGE_ID_VP_REPEAT_ALL,
    MMP_IMG_IMAGE_ID_VP_REPEAT_ONCE,
    MMP_IMG_IMAGE_ID_VP_REPEAT_SINGLE,
    MMP_IMG_IMAGE_ID_VP_STOP,
    MMP_IMG_IMAGE_ID_VP_FAST_FORWARD,
    MMP_IMG_IMAGE_ID_VP_FAST_REVERSE,
    MMP_IMG_IMAGE_ID_VP_NO_FAST_FORWARD,
    MMP_IMG_IMAGE_ID_VP_NO_FAST_REVERSE,
    MMP_IMG_IMAGE_ID_VP_NOT_SUPPORT,
    MMP_IMG_IMAGE_ID_VP_ZOOM,
    MMP_IMG_IMAGE_ID_VP_NO_ZOOM,
    MMP_IMG_IMAGE_ID_VP_NO_AUDIO,
    MMP_IMG_IMAGE_ID_VP_SUBTITLE,
    MMP_IMG_IMAGE_ID_VP_NO_SUBTITLE,
    MMP_IMG_IMAGE_ID_STATUS_BAR_NO_PAUSE,
    MMP_IMG_IMAGE_ID_LIST_MODE_SCROLL_BODY,
    MMP_IMG_IMAGE_ID_LIST_MODE_SCROLL_THUMB,
    MMP_IMG_IMAGE_ID_LIST_MODE_HL_BAR,        
    MMP_IMG_IMAGE_ID_MUSIC_FILE_LIST_BK,
    MMP_IMG_IMAGE_ID_VP_MUSIC_1_BK,
    MMP_IMG_IMAGE_ID_LIST_MODE_MUSIC_2_BK,
    MMP_IMG_IMAGE_ID_LSTMODE_RIGHT_LB_TITLE,
    MMP_IMG_IMAGE_ID_LSTMODE_RIGHT_LB_BK,
    MMP_IMG_IMAGE_ID_LSTMODE_BAR_DOWN_CURSOR,
    MMP_IMG_IMAGE_ID_LSTMODE_BAR_TOP_CURSOR,
    MMP_IMG_IMAGE_ID_LSTMODE_BEXCLAMATION_MARK,
    MMP_IMG_IMAGE_ID_LSTMODE_ICON_FOLDER,    
    MMP_IMG_IMAGE_ID_SELECT_LISTMODE,
    MMP_IMG_IMAGE_ID_COPY_LISTMODE,

    /* music list toolbar icon */
    MMP_IMG_IMAGE_ID_ENTER,
    MMP_IMG_IMAGE_ID_EXIT,
    MMP_IMG_IMAGE_ID_MENU,
    MMP_IMG_IMAGE_ID_SELECT,
    MMP_IMG_IMAGE_ID_MUSIC_PLAYER_BK,
    MMP_IMG_IMAGE_ID_MUSIC_PLAYER_COVER_PIC_BK,
    
    MMP_IMG_IMAGE_ID_SELECT_THUBNAIL,
    MMP_IMG_IMAGE_ID_SELECT_FILTER,
    MMP_IMG_IMAGE_ID_BTM_EXIT,

    MMP_IMG_IMAGE_ID_PLAYING_REPEAT_ONE,
    MMP_IMG_IMAGE_ID_PLAYING_REPEAT_ALL,
    MMP_IMG_IMAGE_ID_PLAYING_A,
    MMP_IMG_IMAGE_ID_PLAYING_AB,
    MMP_IMG_IMAGE_ID_PLAYING_SHUFFLE,
    MMP_IMG_IMAGE_ID_PLAYING_PLAY,
    MMP_IMG_IMAGE_ID_PLAYING_PAUSE,
    MMP_IMG_IMAGE_ID_PLAYING_STOP,
    MMP_IMG_IMAGE_ID_PLAYING_FF,
    MMP_IMG_IMAGE_ID_PLAYING_FR,
    MMP_IMG_IMAGE_ID_PLAYING_VOL_NOR,
    MMP_IMG_IMAGE_ID_PLAYING_VOL_MUTE,
    MMP_IMG_IMAGE_ID_THUMB_LOAD_FAIL_S,
    MMP_IMG_IMAGE_ID_THUMB_LOAD_FAIL_M,
    MMP_IMG_IMAGE_ID_THUMB_LOAD_FAIL_L,
    
    /* THUMB SIZE */
    MMP_IMG_IMAGE_ID_FOLDER_L,
    MMP_IMG_IMAGE_ID_FOLDER_M,
    MMP_IMG_IMAGE_ID_FOLDER_S,
    MMP_IMG_IMAGE_ID_AUDIO_ICON_L,
    MMP_IMG_IMAGE_ID_AUDIO_ICON_M,
    MMP_IMG_IMAGE_ID_AUDIO_ICON_S,
    MMP_IMG_IMAGE_ID_VIDEO_ICON_L,
    MMP_IMG_IMAGE_ID_VIDEO_ICON_M,
    MMP_IMG_IMAGE_ID_VIDEO_ICON_S,
    MMP_IMG_IMAGE_ID_PHOTO_ICON_L,
    MMP_IMG_IMAGE_ID_PHOTO_ICON_M,
    MMP_IMG_IMAGE_ID_PHOTO_ICON_S,
    MMP_IMG_IMAGE_ID_TEXT_ICON_L,
    MMP_IMG_IMAGE_ID_TEXT_ICON_M,
    MMP_IMG_IMAGE_ID_TEXT_ICON_S,
    MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER_L,
    MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER_M,
    MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER_S,
    MMP_IMG_IMAGE_ID_THUMBNAIL_MNP_FOLDER_L,
    MMP_IMG_IMAGE_ID_THUMBNAIL_MNP_FOLDER_M,
    MMP_IMG_IMAGE_ID_THUMBNAIL_MNP_FOLDER_S,
    MMP_IMG_IMAGE_ID_PASTE_AVA,
    MMP_IMG_IMAGE_ID_PASTE_UNAVA,
    MMP_IMG_IMAGE_ID_FRM_BK,
    MMP_IMG_IMAGE_ID_BTN_NR_BK,
    MMP_IMG_IMAGE_ID_BTN_HLT_BK,
    MMP_IMG_IMAGE_ID_LM_PLAY,
    MMP_IMG_IMAGE_ID_LM_PAUSE
} MMP_IMG_IMAGE_ID_T;

extern INT32 mmp_img_init(VOID);
extern INT32 mmp_img_deinit(VOID);
extern INT32 mmp_img_get_img(MMP_IMG_IMAGE_ID_T e_id, WGL_HIMG_TPL_T* ph_img_tpl);

/*-----Color-----*/
#ifdef APP_COLOR_MODE_PALLET
    #define MMP_CLR_IDX_GET_GARY()      (240)
    #define MMP_CLR_IDX_GET_WHITE()     (241)
    #define MMP_CLR_IDX_GET_BLUE()      (242)
    #define MMP_CLR_IDX_GET_DEEP_BLUE() (243)
    #define MMP_CLR_IDX_GET_YELLOW()    (244)
    #define MMP_CLR_IDX_GET_ORANGE()    (245)

    #define MMP_CLR_IDX_GET_TXT()       (246)
    #define MMP_CLR_IDX_GET_HITL()      (247)
    #define MMP_CLR_IDX_GET_TRANSP()    (248)
    #define MMP_CLR_IDX_GET_TITLE()     (249)

#endif

#endif /* _MMP_IMG_API_H_ */
