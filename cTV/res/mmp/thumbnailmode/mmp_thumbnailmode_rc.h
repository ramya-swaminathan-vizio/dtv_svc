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
 * $RCSfile: mmp_file_browser_rc.h,v $
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

#ifndef _MMP_THUMBNAILMODE_RC_H_
#define _MMP_THUMBNAILMODE_RC_H_

#define  MAIN_FRM_W                 (960*4/3)
#define  MAIN_FRM_H                 (540*4/3)
#define  TOP_FRM_H                  (0)
#define  BTM_FRM_H                  (0)

//#define  TOP_FRM_H                  (60)
//#define  BTM_FRM_H                  (41)


/* thumbnail fram number */
#define TM_THUMB_SMALL_ITEM_FRAME_H_NUM            ((UINT8)3)
#define TM_THUMB_SMALL_ITEM_FRAME_V_NUM            ((UINT8)3)
#define TM_THUMB_MEDIUM_ITEM_FRAME_H_NUM           ((INT32)3)
#define TM_THUMB_MEDIUM_ITEM_FRAME_V_NUM            ((INT32)3)
#define TM_THUMB_LARGE_ITEM_FRAME_H_NUM            ((INT32)5)
#define TM_THUMB_LARGE_ITEM_FRAME_V_NUM            ((INT32)3)

#define  THUMB_FRM_X                         (0)
#define  THUMB_FRM_Y                         (TOP_FRM_H)
#define  THUMB_FRM_W                         (MAIN_FRM_W)
#define  THUMB_FRM_H                         (MAIN_FRM_H - TOP_FRM_H - BTM_FRM_H)

#define  SCROLL_BAR_W                       (11*4/3)
#define TM_THUMB_SCROLL_BAR_RANGE_MAX        (381)

#define TM_THUMB_ITEM_SIZE_CONT                    ((INT32)3)


#define TM_THUMB_ITEM_FRAME_H_NUM            ((INT32)3)
#define TM_THUMB_ITEM_FRAME_V_NUM            ((INT32)3)

#define TM_FOLDER_ITEM_FRAME_H_NUM                 ((INT32)3)
#define TM_FOLDER_ITEM_FRAME_V_NUM                 ((INT32)3)


#define TM_THUMB_SMALL_ITEM_FRAME_H_NUM            ((UINT8)3)
#define TM_THUMB_SMALL_ITEM_FRAME_V_NUM            ((UINT8)3)

#define    TM_MENU_MEDIA_ICON_X   (198*2)//(198*4/3)
#define    TM_MENU_MEDIA_ICON_Y   (203*2)//(203*4/3)
#define    TM_MENU_MEDIA_ICON_W   (74*2)//(74*4/3)
#define    TM_MENU_MEDIA_ICON_H   (32*2)//(32*4/3)
#define    TM_MENU_MEDIA_ICON_INSET   (70*2)//(70*4/3)

#define    TM_THUMB_NAIL_HL_INSET1                 (3*2)//(3*4/3)
#define    TM_THUMB_NALL_HL_INSET2                 (10*2)//(10*4/3)
#define    TM_FOLDER_MALL_HL_INSERT1               (7*2)//(7*4/3)
#define    TM_FOLDER_MALL_HL_INSERT2               (15*2)//(15*4/3)
#define    TM_THUMB_NAIL_OP_FRM_OFFSET  (3*2)//(3*4/3)

#define    TM_THUMB_SKIP_OFFSET_X       (90*2)//(90*4/3)
#define    TM_THUMB_SKIP_OFFSET_Y       (70*2)//(70*4/3)


/*skip btn  */
#define    TM_THUMB_SKIP_INSERT_LEFT         (102*2)//(102*4/3)
#define    TM_THUMB_SKIP_INSERT_RTGHT        (2*2)//(2*4/3)
#define    TM_THUMB_SKIP_INSERT_TOP          (4*2)//(4*4/3)
#define    TM_THUMB_SKIP_INSERT_BOTTOM       (72*2)//(72*4/3)
#define    TM_THUMB_SKIP_INSERT_WIDTH        (38*2)//(38*4/3)



/*middle*/
#define TM_THUMB_ITEM_FRAME_X                ((INT32)127)//((INT32)85)
#define TM_THUMB_ITEM_FRAME_Y                ((INT32)7)//((INT32)5)
#define TM_THUMB_ITEM_FRAME_W                ((INT32)292)//((INT32)195)
#define TM_THUMB_ITEM_FRAME_H                ((INT32)232)//((INT32)155)


#define TM_THUMB_ITEM_FRAME_OFFSET_X         ((INT32)90)//((INT32)60)
#define TM_THUMB_ITEM_FRAME_OFFSET_Y         ((INT32)67) //((INT32)45)
#define TM_THUMB_NAME_ITEM_FRAME_X                (TM_THUMB_ITEM_FRAME_X)
#define TM_THUMB_NAME_ITEM_FRAME_Y                (TM_THUMB_ITEM_FRAME_Y+TM_THUMB_ITEM_FRAME_H+15)//(TM_THUMB_ITEM_FRAME_Y+TM_THUMB_ITEM_FRAME_H+10)
#define TM_THUMB_NAME_ITEM_FRAME_W                ((INT32)(141*2))//((INT32)(141*4/3))
#define TM_THUMB_NAME_ITEM_FRAME_H                ((INT32)(25*2))//((INT32)(25*4/3))
#define TM_THUMB_NAME_ITEM_FRAME_OFFSET_X         (TM_THUMB_ITEM_FRAME_OFFSET_X)
#define TM_THUMB_NAME_ITEM_FRAME_OFFSET_Y         (TM_THUMB_ITEM_FRAME_OFFSET_Y)


/* middle  folder ui frame size */
#define TM_FOLDER_ITEM_FRAME_X                    ((INT32)163)//((INT32)109)
#define TM_FOLDER_ITEM_FRAME_Y                    ((INT32)66)//((INT32)44)
#define TM_FOLDER_ITEM_FRAME_W                    ((INT32)228)//((INT32)152)
#define TM_FOLDER_ITEM_FRAME_H                    ((INT32)196)//((INT32)131)

#define TM_FOLDER_ITEM_FRAMEOFFSET_X              ((INT32)157)//((INT32)105)
#define TM_FOLDER_ITEM_FRAMEOFFSET_Y              ((INT32)75)//((INT32)50)

#define TM_FOLDER_NAME_ITEM_FRAME_X               (TM_FOLDER_ITEM_FRAME_X)
#define TM_FOLDER_NAME_ITEM_FRAME_Y               (TM_FOLDER_ITEM_FRAME_Y+TM_FOLDER_ITEM_FRAME_H+7)//(TM_FOLDER_ITEM_FRAME_Y+TM_FOLDER_ITEM_FRAME_H+5)
#define TM_FOLDER_NAME_ITEM_FRAME_W               ((INT32)(228))//((INT32)(152))
#define TM_FOLDER_NAME_ITEM_FRAME_H               ((INT32)(37))//((INT32)(25))

#define TM_FOLDER_NAME_ITEM_FRAME_OFFSET_X         (TM_FOLDER_ITEM_FRAMEOFFSET_X)
#define TM_FOLDER_NAME_ITEM_FRAME_OFFSET_Y         (TM_FOLDER_ITEM_FRAMEOFFSET_Y)



/* large */
#define TM_THUMB_LARGE_ITEM_FRAME_X                ((INT32)222*2)//((INT32)222*4/3)
#define TM_THUMB_LARGE_ITEM_FRAME_Y                ((INT32)24*2)//((INT32)24*4/3)
#define TM_THUMB_LARGE_ITEM_FRAME_W                ((INT32)118*2)//((INT32)118*4/3)
#define TM_THUMB_LARGE_ITEM_FRAME_H                ((INT32)116*2)//((INT32)116*4/3)
#define TM_THUMB_LARGE_ITEM_FRAME_OFFSET_X         ((INT32)21*2)//(INT32)21*4/3)
#define TM_THUMB_LARGE_ITEM_FRAME_OFFSET_Y         ((INT32)21*2)//((INT32)21*4/3)

#define TM_THUMB_LARGE_NAME_ITEM_FRAME_X                ((INT32)(0))
#define TM_THUMB_LARGE_NAME_ITEM_FRAME_Y                ((INT32)TM_THUMB_LARGE_ITEM_FRAME_H - 40*2)//((INT32)TM_THUMB_LARGE_ITEM_FRAME_H - 40*4/3)
#define TM_THUMB_LARGE_NAME_ITEM_FRAME_W                ((INT32)118*2)//((INT32)118*4/3)
#define TM_THUMB_LARGE_NAME_ITEM_FRAME_H                ((INT32)40*2)//((INT32)40*4/3)
#define TM_THUMB_LARGE_NAME_ITEM_FRAME_OFFSET_X         ((INT32)71*2)//((INT32)71*4/3)
#define TM_THUMB_LARGE_NAME_ITEM_FRAME_OFFSET_Y         ((INT32)261*2)//((INT32)261*4/3)


/* small  */
#define TM_THUMB_SMALL_ITEM_FRAME_X                ((INT32)222*2)//((INT32)222*4/3)
#define TM_THUMB_SMALL_ITEM_FRAME_Y                ((INT32)33*2)//((INT32)33*4/3)
#define TM_THUMB_SMALL_ITEM_FRAME_W                ((INT32)86*2)//((INT32)86*4/3)
#define TM_THUMB_SMALL_ITEM_FRAME_H                ((INT32)66*2)//((INT32)66*4/3)
#define TM_THUMB_SMALL_ITEM_FRAME_OFFSET_X         ((INT32)15*2)//((INT32)15*4/3)
#define TM_THUMB_SMALL_ITEM_FRAME_OFFSET_Y         ((INT32)14*2)//((INT32)14*4/3)

#define TM_THUMB_SMALL_NAME_ITEM_FRAME_X           ((INT32)(0))
#define TM_THUMB_SMALL_NAME_ITEM_FRAME_Y           ((INT32)TM_THUMB_SMALL_ITEM_FRAME_H - 20*2)//((INT32)TM_THUMB_SMALL_ITEM_FRAME_H - 20*4/3)
#define TM_THUMB_SMALL_NAME_ITEM_FRAME_W           ((INT32)TM_THUMB_SMALL_ITEM_FRAME_W)
#define TM_THUMB_SMALL_NAME_ITEM_FRAME_H           ((INT32)20*2)//((INT32)20*4/3)
#define TM_THUMB_SMALL_NAME_ITEM_FRAME_OFFSET_X    ((INT32)17*2)//((INT32)17*4/3)
#define TM_THUMB_SMALL_NAME_ITEM_FRAME_OFFSET_Y    ((INT32)105*2)//((INT32)105*4/3)

/* Info handle rect */
#define     TM_FILE_INFO_HANDLE_X       (10*2)//(10*4/3)
#define     TM_FILE_INFO_HANDLE_Y       (380*2)//(380*4/3)
#define     TM_FILE_INFO_HANDLE_W       (270*2)//(270*4/3)
#define     TM_FILE_INFO_HANDLE_H       (100*2)//(100*4/3)


#define TM_THUMB_SKIP_INSERT_WIDTH      (38*2)//(38*4/3)


/* Playing file rect */
#define     TM_FILE_PLAY_HANDLE_X       (0)
#define     TM_FILE_PLAY_HANDLE_Y       (TM_FILE_INFO_HANDLE_Y + TM_FILE_INFO_HANDLE_H)
#define     TM_FILE_PLAY_HANDLE_W       (THUMB_FRM_W/5)
#define     TM_FILE_PLAY_HANDLE_H       (THUMB_FRM_H/5)

#define OPTION_MENU_LEFT    (100*4/3);
#define OPTION_MENU_TOP     (100*4/3);
#define MMP_TM_UI_OPTL_MAIN_ITEM_MAX_NUM    (8)
#define MMP_TM_UI_OPTL_SIZE_TYPE_NUM        (3)
#ifdef MMP_TM_UI_OPTL_PH_SORT_NUM
#undef MMP_TM_UI_OPTL_PH_SORT_NUM
#endif
#define MMP_TM_UI_OPTL_PH_SORT_NUM          (4)
#define MMP_TM_UI_OPTL_AU_SORT_NUM          (4)
#define MMP_TM_UI_OPTL_PH_VIEW_NUM          (2)
#define MMP_TM_UI_OPTL_PH_SETTINGS_NUM      (4)
#define MMP_TM_UI_OPTL_VD_SORT_NUM          (3)


#define MMP_TM_RC_FOLDER_GET_SIZE_SETTINTG(_ui1_id, _ui2_x_f, _ui2_y_f, _ui2_w_f, _ui2_h_f, _ui2_offset_x_f, _ui2_offset_y_f,          \
                                   _ui2_name_x_f, _ui2_name_y_f, _ui2_name_w_f, _ui2_name_h_f, _ui1_max_h_num, _ui1_max_v_num,        \
                                   _e_img_id_folder, _e_img_id_photo, _e_img_id_audio, _e_img_id_video, _e_img_id_text,         \
                                   _e_img_id_hlt_thumb, _e_img_id_thumb_fail)                                                 \
{                                                                                                                             \
    switch (_ui1_id)                                                                                                          \
    {                                                                                                                          \
        case 1:                                                                                                               \
        default: /* middle(defualt) folder */                                                                                      \
            (_ui2_x_f)             = TM_FOLDER_ITEM_FRAME_X;                                                                   \
            (_ui2_y_f)             = TM_FOLDER_ITEM_FRAME_Y;                                                                      \
            (_ui2_w_f)             = TM_FOLDER_ITEM_FRAME_W;                                                                      \
            (_ui2_h_f)             = TM_FOLDER_ITEM_FRAME_H;                                                                      \
            (_ui2_offset_x_f)     = TM_FOLDER_ITEM_FRAMEOFFSET_X;                                                               \
            (_ui2_offset_y_f)     = TM_FOLDER_ITEM_FRAMEOFFSET_Y;                                                               \
            (_ui2_name_x_f)       = TM_FOLDER_NAME_ITEM_FRAME_X;                                                                 \
            (_ui2_name_y_f)       = TM_FOLDER_NAME_ITEM_FRAME_Y;                                                                 \
            (_ui2_name_w_f)       = TM_FOLDER_NAME_ITEM_FRAME_W;                                                                 \
            (_ui2_name_h_f)       = TM_FOLDER_NAME_ITEM_FRAME_H;                                                                 \
            (_ui1_max_h_num)    = TM_THUMB_MEDIUM_ITEM_FRAME_H_NUM;                                                           \
            (_ui1_max_v_num)    = TM_THUMB_MEDIUM_ITEM_FRAME_V_NUM;                                                           \
            (_e_img_id_folder)  = MMP_IMG_IMAGE_ID_FOLDER_M;                                                                  \
            (_e_img_id_photo)   = MMP_IMG_IMAGE_ID_PHOTO_ICON_M;                                                              \
            (_e_img_id_audio)   = MMP_IMG_IMAGE_ID_AUDIO_ICON_M;                                                              \
            (_e_img_id_video)   = MMP_IMG_IMAGE_ID_VIDEO_ICON_M;                                                              \
            (_e_img_id_text)     = MMP_IMG_IMAGE_ID_TEXT_ICON_M;                                                               \
            (_e_img_id_hlt_thumb)   = MMP_IMG_IMAGE_ID_HIGHLIGHT_THUMBNAIL_M;                                                 \
            (_e_img_id_thumb_fail)  = MMP_IMG_IMAGE_ID_THUMB_LOAD_FAIL_M;                                                     \
            break;                                                                                                              \
    }                                                                                                                            \
}


#define MMP_TM_RC_GET_SIZE_SETTING(_ui1_id, _ui2_x, _ui2_y, _ui2_w, _ui2_h, _ui2_offset_x, _ui2_offset_y,                     \
                                   _ui2_name_x, _ui2_name_y, _ui2_name_w, _ui2_name_h, _ui1_max_h_num, _ui1_max_v_num,        \
                                   _e_img_id_folder, _e_img_id_photo, _e_img_id_audio, _e_img_id_video, _e_img_id_text,       \
                                   _e_img_id_hlt_thumb, _e_img_id_thumb_fail)                                                 \
{                                                                                                                             \
    switch (_ui1_id)                                                                                                          \
    {                                                                                                                         \
        case 2: /* large thumb */                                                                                             \
            (_ui2_x)            = TM_THUMB_LARGE_ITEM_FRAME_X;                                                                \
            (_ui2_y)            = TM_THUMB_LARGE_ITEM_FRAME_Y;                                                                \
            (_ui2_w)            = TM_THUMB_LARGE_ITEM_FRAME_W;                                                                \
            (_ui2_h)            = TM_THUMB_LARGE_ITEM_FRAME_H;                                                                \
            (_ui2_offset_x)     = TM_THUMB_LARGE_ITEM_FRAME_OFFSET_X;                                                         \
            (_ui2_offset_y)     = TM_THUMB_LARGE_ITEM_FRAME_OFFSET_Y;                                                         \
            (_ui2_name_x)       = TM_THUMB_LARGE_NAME_ITEM_FRAME_X;                                                           \
            (_ui2_name_y)       = TM_THUMB_LARGE_NAME_ITEM_FRAME_Y;                                                           \
            (_ui2_name_w)       = TM_THUMB_LARGE_NAME_ITEM_FRAME_W;                                                           \
            (_ui2_name_h)       = TM_THUMB_LARGE_NAME_ITEM_FRAME_H;                                                           \
            (_ui1_max_h_num)    = TM_THUMB_LARGE_ITEM_FRAME_H_NUM;                                                            \
            (_ui1_max_v_num)    = TM_THUMB_LARGE_ITEM_FRAME_V_NUM;                                                            \
            (_e_img_id_folder)  = MMP_IMG_IMAGE_ID_FOLDER_L;                                                                  \
            (_e_img_id_photo)   = MMP_IMG_IMAGE_ID_PHOTO_ICON_L;                                                              \
            (_e_img_id_audio)   = MMP_IMG_IMAGE_ID_AUDIO_ICON_L;                                                              \
            (_e_img_id_video)   = MMP_IMG_IMAGE_ID_VIDEO_ICON_L;                                                              \
            (_e_img_id_text)        = MMP_IMG_IMAGE_ID_TEXT_ICON_L;                                                           \
            (_e_img_id_hlt_thumb)   = MMP_IMG_IMAGE_ID_HIGHLIGHT_THUMBNAIL_L;                                                 \
            (_e_img_id_thumb_fail)  = MMP_IMG_IMAGE_ID_THUMB_LOAD_FAIL_L;                                                     \
            break;                                                                                                            \
        case 0: /* small  thumb */                                                                                            \
            (_ui2_x)            = TM_THUMB_SMALL_ITEM_FRAME_X;                                                                \
            (_ui2_y)            = TM_THUMB_SMALL_ITEM_FRAME_Y;                                                                \
            (_ui2_w)            = TM_THUMB_SMALL_ITEM_FRAME_W;                                                                \
            (_ui2_h)            = TM_THUMB_SMALL_ITEM_FRAME_H;                                                                \
            (_ui2_offset_x)     = TM_THUMB_SMALL_ITEM_FRAME_OFFSET_X;                                                         \
            (_ui2_offset_y)     = TM_THUMB_SMALL_ITEM_FRAME_OFFSET_Y;                                                         \
            (_ui2_name_x)       = TM_THUMB_SMALL_NAME_ITEM_FRAME_X;                                                           \
            (_ui2_name_y)       = TM_THUMB_SMALL_NAME_ITEM_FRAME_Y;                                                           \
            (_ui2_name_w)       = TM_THUMB_SMALL_NAME_ITEM_FRAME_W;                                                           \
            (_ui2_name_h)       = TM_THUMB_SMALL_NAME_ITEM_FRAME_H;                                                           \
            (_ui1_max_h_num)    = TM_THUMB_SMALL_ITEM_FRAME_H_NUM;                                                            \
            (_ui1_max_v_num)    = TM_THUMB_SMALL_ITEM_FRAME_V_NUM;                                                            \
            (_e_img_id_folder)  = MMP_IMG_IMAGE_ID_FOLDER_S;                                                                  \
            (_e_img_id_photo)   = MMP_IMG_IMAGE_ID_PHOTO_ICON_S;                                                              \
            (_e_img_id_audio)   = MMP_IMG_IMAGE_ID_AUDIO_ICON_S;                                                              \
            (_e_img_id_video)   = MMP_IMG_IMAGE_ID_VIDEO_ICON_S;                                                              \
            (_e_img_id_text)    = MMP_IMG_IMAGE_ID_TEXT_ICON_S;                                                               \
            (_e_img_id_hlt_thumb)   = MMP_IMG_IMAGE_ID_HIGHLIGHT_THUMBNAIL;                                                   \
            (_e_img_id_thumb_fail)  = MMP_IMG_IMAGE_ID_THUMB_LOAD_FAIL_S;                                                     \
            break;                                                                                                            \
        case 1:                                                                                                               \
        default: /* middle(defualt) thumb */                                                                                  \
            (_ui2_x)            = TM_THUMB_ITEM_FRAME_X;                                                                      \
            (_ui2_y)            = TM_THUMB_ITEM_FRAME_Y;                                                                      \
            (_ui2_w)            = TM_THUMB_ITEM_FRAME_W;                                                                      \
            (_ui2_h)            = TM_THUMB_ITEM_FRAME_H;                                                                      \
            (_ui2_offset_x)     = TM_THUMB_ITEM_FRAME_OFFSET_X;                                                               \
            (_ui2_offset_y)     = TM_THUMB_ITEM_FRAME_OFFSET_Y;                                                               \
            (_ui2_name_x)       = TM_THUMB_NAME_ITEM_FRAME_X;                                                                 \
            (_ui2_name_y)       = TM_THUMB_NAME_ITEM_FRAME_Y;                                                                 \
            (_ui2_name_w)       = TM_THUMB_NAME_ITEM_FRAME_W;                                                                 \
            (_ui2_name_h)       = TM_THUMB_NAME_ITEM_FRAME_H;                                                                 \
            (_ui1_max_h_num)    = TM_THUMB_MEDIUM_ITEM_FRAME_H_NUM;                                                           \
            (_ui1_max_v_num)    = TM_THUMB_MEDIUM_ITEM_FRAME_V_NUM;                                                           \
            (_e_img_id_folder)  = MMP_IMG_IMAGE_ID_FOLDER_M;                                                                  \
            (_e_img_id_photo)   = MMP_IMG_IMAGE_ID_PHOTO_ICON_M;                                                              \
            (_e_img_id_audio)   = MMP_IMG_IMAGE_ID_AUDIO_ICON_M;                                                              \
            (_e_img_id_video)   = MMP_IMG_IMAGE_ID_VIDEO_ICON_M;                                                              \
            (_e_img_id_text)    = MMP_IMG_IMAGE_ID_TEXT_ICON_M;                                                               \
            (_e_img_id_hlt_thumb)   = MMP_IMG_IMAGE_ID_HIGHLIGHT_THUMBNAIL_M;                                                 \
            (_e_img_id_thumb_fail)  = MMP_IMG_IMAGE_ID_THUMB_LOAD_FAIL_M;                                                     \
            break;                                                                                                            \
    }                                                                                                                         \
}
#define MMP_TM_RC_GET_MSG_SETTING(_e_warning_id, _ui2_mlm_idx, _e_msg_class)                                                  \
{                                                                                                                             \
    switch(_e_warning_id)                                                                                                     \
    {                                                                                                                         \
        /* 1. Empty */                                                                                                        \
        case MMP_TM_VIEW_WARN_MSG_EMPTY :                                                                                     \
            (_ui2_mlm_idx) = MLM_MMP_KEY_THUMB_FOLDER_IS_EMPTY;                                                               \
            (_e_msg_class) = MMP_IB_MSG_CLASS_INFO;                                                                           \
            break;                                                                                                            \
        /* 2. Waiting */                                                                                                      \
        case MMP_TM_VIEW_WARN_MSG_WAITING :                                                                                   \
            (_ui2_mlm_idx) = MLM_MMP_KEY_PARSING_FOLDER_WARTING;                                                              \
            (_e_msg_class) = MMP_IB_MSG_CLASS_INFO;                                                                           \
            break;                                                                                                            \
        /* 3. No device */                                                                                                    \
        case MMP_TM_VIEW_WARN_MSG_NO_DEVICE :                                                                                 \
            (_ui2_mlm_idx) = MLM_MMP_KEY_THUMB_IS_NO_DEVICE;                                                                  \
            (_e_msg_class) = MMP_IB_MSG_CLASS_INFO;                                                                           \
            break;                                                                                                            \
        /* 4. limited folder */                                                                                               \
        case MMP_TM_VIEW_WARN_MSG_LIMITED_FLDR:                                                                               \
            (_ui2_mlm_idx) = MLM_MMP_KEY_LIMITED_FOLDER;                                                                      \
            (_e_msg_class) = MMP_IB_MSG_CLASS_WARNING;                                                                        \
            break;                                                                                                            \
        /* 5. open folder fail */                                                                                             \
        case MMP_TM_VIEW_WARN_MSG_OPEN_FLDR_FAIL:                                                                             \
            (_ui2_mlm_idx) = MLM_MMP_KEY_ACCESS_FLDR_FAIL;                                                                    \
            (_e_msg_class) = MMP_IB_MSG_CLASS_URGENT;                                                                         \
            break;                                                                                                            \
        /* 6. pwd error  */                                                                                                   \
        case MMP_TM_VIEW_WARN_MSG_PWD_ERROR:                                                                                  \
            (_ui2_mlm_idx) = MLM_MMP_KEY_NET_NEIGHBOR_NAME_PWD_ERROR;                                                         \
            (_e_msg_class) = MMP_IB_MSG_CLASS_WARNING;                                                                        \
            break;                                                                                                            \
        /* 7. Lock inp */                                                                                                     \
        case MMP_TM_VIEW_WARN_MSG_LOCK_INP:                                                                                   \
            (_ui2_mlm_idx) = MLM_MMP_KEY_LOCKED_INP;                                                                          \
            (_e_msg_class) = MMP_IB_MSG_CLASS_WARNING;                                                                        \
            break;                                                                                                            \
        /*  Empty */                                                                                                          \
        default:                                                                                                              \
            (_ui2_mlm_idx) = MLM_MMP_KEY_THUMB_FOLDER_IS_EMPTY;                                                               \
            (_e_msg_class) = MMP_IB_MSG_CLASS_INFO;                                                                           \
            break;                                                                                                            \
    }                                                                                                                         \
}

#define MMP_TM_BTN_CURSOR_UP     BTN_CURSOR_UP
#define MMP_TM_BTN_CURSOR_DOWN   BTN_CURSOR_DOWN
#define MMP_TM_BTN_CURSOR_LEFT   BTN_CURSOR_LEFT
#define MMP_TM_BTN_CURSOR_RIGHT  BTN_CURSOR_RIGHT
#define MMP_TM_BTN_PAGE_UP       BTN_PRG_UP
#define MMP_TM_BTN_PAGE_DOWN     BTN_PRG_DOWN
#define MMP_TM_BTN_SELECT        BTN_SELECT
#define MMP_TM_RC_KEY_DETAIL     BTN_PRG_INFO

#define MMP_TM_POP_UP_BASE_FRM_X (336*2)//(336*4/3)
#define MMP_TM_POP_UP_BASE_FRM_Y (100*2)//(100*4/3)
#define MMP_TM_POP_UP_BASE_FRM_W (617*2 - MMP_TM_POP_UP_BASE_FRM_X)//(617*4/3 - MMP_TM_POP_UP_BASE_FRM_X)
#define MMP_TM_POP_UP_BASE_FRM_H (460*2 - MMP_TM_POP_UP_BASE_FRM_Y)//(460*4/3 - MMP_TM_POP_UP_BASE_FRM_Y)

#define MMP_TM_IMG_PREVIEW_X     (402*2)  //(402*4/3)
#define MMP_TM_IMG_PREVIEW_Y     (139*2) //(139*4/3)
#define MMP_TM_IMG_PREVIEW_W     (148*2)//(148*4/3)
#define MMP_TM_IMG_PREVIEW_H     (108*2) //(110*4/3)

#define MMP_TM_POP_UP_SKIP_ICON_W   (40*2)//(40*4/3)
#define MMP_TM_POP_UP_SKIP_ICON_H   (40*2)//(40*4/3)

#define MMP_TM_RC_GET_SORT_TYPE(_e_media_type, _ui4_id, _e_sort)        \
{                                                                       \
    if (MMP_MEDIA_TYPE_PHOTO == (_e_media_type))                        \
    {                                                                   \
        switch ((_ui4_id))                                              \
        {                                                               \
            case 0:                                                     \
                (_e_sort) = MMP_SORT_TYPE_PHOTO_NAME;                   \
                break;                                                  \
            case 1:                                                     \
                (_e_sort) = MMP_SORT_TYPE_PHOTO_INV_NAME;               \
                break;                                                  \
            case 2:                                                     \
                (_e_sort) = MMP_SORT_TYPE_PHOTO_DATE;                   \
                break;                                                  \
            case 3:                                                     \
                (_e_sort) = MMP_SORT_TYPE_PHOTO_INV_DATE;               \
                break;                                                  \
            default:                                                    \
                (_e_sort) = MMP_SORT_TYPE_NONE;                         \
                break;                                                  \
        }                                                               \
    }                                                                   \
    else                                                                \
    {                                                                   \
        (_e_sort) = MMP_SORT_TYPE_NONE;                                 \
    }                                                                   \
}

#endif /*_MMP_THUMBNAILMODE_RC_H_*/

