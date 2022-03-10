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
 * $RCSfile: mmp_common.h,v $
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
 
#ifndef _MMP_COMMON_H_
#define _MMP_COMMON_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "a_mmp.h"
#include "u_common.h"
#include "u_img_tfx.h"
#ifdef LINUX_TURNKEY_SOLUTION
#include "app_util/a_common.h"
#endif
#include "u_mm_common.h"

#include "res/mmp/mmp_common_rc.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*-----Return Value-----*/
#define MMPR_NO_ACTION              ((INT32)   15)
#define MMPR_IS_SLOW_REWINDED       ((INT32)   14)
#define MMPR_IS_SLOW_FORWARDED      ((INT32)   13)
#define MMPR_IS_FAST_REWINDED       ((INT32)   12)
#define MMPR_IS_FAST_FORWARDED      ((INT32)   11)
#define MMPR_ALREADY_INIT   ((INT32)   10)
#define MMPR_IS_LOADING     ((INT32)   9)              /* Requested items are loading now. */
#define MMPR_IS_ZOOMED      ((INT32)   8)
#define MMPR_IS_ROTATED     ((INT32)   7)
#define MMPR_IS_SAVED       ((INT32)   6)
#define MMPR_IS_PRELOADED   ((INT32)   5)
#define MMPR_IS_PLAYED      ((INT32)   4)
#define MMPR_IS_PAUSED      ((INT32)   3)
#define MMPR_IS_STOPPED     ((INT32)   2)
#define MMPR_IS_OPENED      (MMPR_IS_STOPPED)
#define MMPR_IS_CLOSED      ((INT32)   1)
#define MMPR_OK             ((INT32)   0)
#define MMPR_FAIL           ((INT32)  -1)
#define MMPR_INV_ARG        ((INT32)  -2)
#define MMPR_OUT_OF_MEM     ((INT32)  -3)
#define MMPR_NOT_SUPPORT    ((INT32)  -4)
#define MMPR_INTERNAL_ERROR ((INT32)  -5)
#define MMPR_QUEUE_FULL     ((INT32)  -6)
#define MMPR_OUT_OF_LIMIT   ((INT32)  -7)
#define MMPR_NO_DATA        ((INT32)  -8)
#define MMPR_RES_NOT_READY  ((INT32)  -9)
#define MMPR_BUF_NOT_ENOUGH ((INT32) -10)
#define MMPR_DIR_FAIL_VISIT ((INT32)  -11)
#define MMPR_DIR_AUTH_FAIL  ((INT32)  -12)
#define MMPR_SPACE_NOT_ENOUGH ((INT32) -13)
#define MMPR_DLNA_SERVER_OFF	((INT32) -14)
#define MMPR_TRICK_CHANGE	((INT32) -15)
#define MMPR_WRONG_STATE    ((INT32) -16)
#define MMPR_NOT_IMPLEMENT  ((INT32) -17)
#define MMPR_NOT_SUPPORT_ZOOM       ((INT32)  -18)
#define MMPR_NOT_SUPPORT_ROTATE     ((INT32)  -19)

/*-----Media type-----*/
typedef enum _MMP_MEDIA_TYPE_T
{
    MMP_MEDIA_TYPE_UNKNOWN      = 0x00000000,
    MMP_MEDIA_TYPE_PHOTO        = 0x00000001,
    MMP_MEDIA_TYPE_AUDIO        = 0x00000002,
    MMP_MEDIA_TYPE_VIDEO        = 0x00000004,
    MMP_MEDIA_TYPE_TEXT         = 0x00000008,
    MMP_MEDIA_TYPE_LIST_PHOTO   = 0x00000010,
    MMP_MEDIA_TYPE_LIST_AUDIO   = 0x00000020,
    MMP_MEDIA_TYPE_LIST_VIDEO   = 0x00000040,
    MMP_MEDIA_TYPE_LIST_MIX     = 0x00000080,
    MMP_MEDIA_TYPE_ALL          = 0x00000100
} MMP_MEDIA_TYPE_T;

typedef struct _MMP_STAT_XNG_INFO_T
{
    MMP_MAIN_AP_STATUS_T e_mmp_stat_old;
    MMP_MAIN_AP_STATUS_T e_mmp_stat_new;
} MMP_STAT_XNG_INFO_T;

/*-----Play state-----*/
typedef enum _MMP_PLAY_STATE_T
{
    MMP_PLAY_STATE_CLOSED = 0,
    MMP_PLAY_STATE_OPENING,
    MMP_PLAY_STATE_PLAYING,
    MMP_PLAY_STATE_PLAYED,
    MMP_PLAY_STATE_PAUSING,
    MMP_PLAY_STATE_PAUSED,
    MMP_PLAY_STATE_FAST_FORWARDING,
    MMP_PLAY_STATE_FAST_FORWARDED,
    MMP_PLAY_STATE_FAST_REWINDING,
    MMP_PLAY_STATE_FAST_REWINDED,
    MMP_PLAY_STATE_SLOW_FORWARDING,
    MMP_PLAY_STATE_SLOW_FORWARDED,
    MMP_PLAY_STATE_SLOW_REWINDING,
    MMP_PLAY_STATE_SLOW_REWINDED,
    MMP_PLAY_STATE_STOPPING,
    MMP_PLAY_STATE_STOPPED,
    MMP_PLAY_STATE_CLOSING,
    MMP_PLAY_STATE_PLAY_NEXTING,
    MMP_PLAY_STATE_VIEW_NEXTING,
    MMP_PLAY_STATE_NO_FILE
} MMP_PLAY_STATE_T;

typedef enum _MMP_FB_MODE
{
    MMP_FB_MODE_THUMB = 0,
    MMP_FB_MODE_LIST
} MMP_FB_MODE;

#define _MMP_PLAY_IS_STATE_PLAY(_e_state)                       \
(                                                               \
    (MMP_PLAY_STATE_PLAYING == (_e_state) ||                    \
     MMP_PLAY_STATE_PLAYED == (_e_state) ||                     \
     MMP_PLAY_STATE_PLAY_NEXTING == (_e_state)) ? TRUE : FALSE  \
)

/*----------*/
#define MMP_PLAY_IDX_CURRENT            ((UINT32) 0xFFFFFFFF)
#define MMP_NULL_FILE_IDX               ((UINT32) 0xFFFFFFFF)
#define MMP_NULL_FILE_COUNT             ((UINT32) 0xFFFFFFFF)
#define MMP_BROWSE_ID_LAST              ((UINT8)  0xFF)
#define MMP_BROWSE_FOCUS_IDX_LAST       ((UINT32) 0xFFFFFFFF)
#define MMP_PLAYER_IDX_NULL             ((UINT8)  255)

/*-----Ground mode-----*/
typedef enum _MMP_GROUND_MODE_T
{
    MMP_GROUND_MODE_BACK = 0,
    MMP_GROUND_MODE_FORE,
    MMP_GROUND_MODE_ALL,
    MMP_GROUND_MODE_AUTO
} MMP_GROUND_MODE_T;

/*-----Repeat mode-----*/
typedef enum _MMP_REPEAT_MODE_T
{
    MMP_REPEAT_MODE_NONE = 0,           /*whole folder will be played once.*/
    MMP_REPEAT_MODE_ONE,                /*current file will be played repeatedly.*/
    MMP_REPEAT_MODE_ALL,                /*whole folder will be played repeatedly.*/
    MMP_REPEAT_MODE_ONE_ONCE            /*current file will be played once.*/
} MMP_REPEAT_MODE_T;

/*-----Shuffle mode-----*/
typedef enum _MMP_SHUFFLE_MODE_T
{
    MMP_SHUFFLE_MODE_SEQUENTIAL = 0,
    MMP_SHUFFLE_MODE_SHUFFLE
} MMP_SHUFFLE_MODE_T;


typedef enum
{ 
	MMP_SPEED_TYPE_NONE = 0,           /*Play normal when start play*/
    MMP_SPEED_TYPE_ONCE,                /*Play with speed settings on current file*/
    MMP_SPEED_TYPE_ALL                /*All file will play with speed settings*/
}MMP_SPEED_TYPE_T;

typedef struct _MMP_SPEED_MODE_T
{
	MMP_SPEED_TYPE_T     e_speed_type;       
    MM_SPEED_TYPE_T      e_speed;
} MMP_SPEED_SET_T;

/*-----Sort type-----*/
typedef enum _MMP_SORT_TYPE_T
{
    MMP_SORT_TYPE_NONE = 0,
    MMP_SORT_TYPE_NAME,
    MMP_SORT_TYPE_INV_NAME,
    MMP_SORT_TYPE_DATE,
    MMP_SORT_TYPE_INV_DATE,
    MMP_SORT_TYPE_AUD_NAME,
    MMP_SORT_TYPE_AUD_GENRE,
    MMP_SORT_TYPE_AUD_ARTIST,
    MMP_SORT_TYPE_AUD_INV_ARTIST,
    MMP_SORT_TYPE_AUD_ALBUM,
    MMP_SORT_TYPE_AUD_INV_ALBUM,
    MMP_SORT_TYPE_AUD_TITLE,
    MMP_SORT_TYPE_AUD_INV_TITLE,
    MMP_SORT_TYPE_AUDIO_DATE,
    MMP_SORT_TYPE_AUDIO_INV_DATE,
    MMP_SORT_TYPE_AUDIO_INV_NAME,
    MMP_SORT_TYPE_PHOTO_DATE,
    MMP_SORT_TYPE_PHOTO_FILE_DATE,
    MMP_SORT_TYPE_PHOTO_NAME,
    MMP_SORT_TYPE_PHOTO_INV_DATE,
    MMP_SORT_TYPE_PHOTO_INV_NAME,   
    MMP_SORT_TYPE_VIDEO_TYPE,
    MMP_SORT_TYPE_VIDEO_DATE,
    MMP_SORT_TYPE_VIDEO_NAME,
    MMP_SORT_TYPE_VIDEO_INV_DATE,
    MMP_SORT_TYPE_VIDEO_INV_NAME,
    MMP_SORT_TYPE_TEXT_DATE,
    MMP_SORT_TYPE_TEXT_NAME,
    MMP_SORT_TYPE_TEXT_INV_DATE,
    MMP_SORT_TYPE_TEXT_INV_NAME
} MMP_SORT_TYPE_T;

/*-----*/
typedef enum
{
    ITEM_TYPE_FILE = 0,
    ITEM_TYPE_DIR,
    ITEM_TYPE_NONE,
    ITEM_TYPE_LAST_ENTRY
} MMP_ITEM_TYPE_T;

/*-----Folder type-----*/
typedef enum _MMP_FDLR_PSR_TYPE_T
{
    MMP_FDLR_PSR_TYPE_SINGLE,
    MMP_FDLR_PSR_TYPE_RECUR_FDLR_FISRT,
    MMP_FDLR_PSR_TYPE_RECUR_FILE_FISRT,
    MMP_FDLR_PSR_TYPE_RECUR_FAT_FIRST
} MMP_FLDR_PSR_TYPE_T;

/*-----Filter prototype-----*/
/* For each file to determine whether to filter the file or not. */
typedef INT32 (*mmp_func_filter_fct)(const CHAR* ps_path,
                                     UINT16 ui2_path_len, 
                                     const CHAR* ps_filename, 
                                     UINT16 ui2_name_len, 
                                     BOOL* pb_match,
                                     VOID* pv_tag);

/*-----Open Method-----*/
typedef enum _MMP_OPEN_METHOD_T
{
    MMP_OPEN_METHOD_OPEN = 0,
    MMP_OPEN_METHOD_NEW
} MMP_OPEN_METHOD_T;

typedef enum _MMP_APP_RESUME_INFO_T
{
    MMP_APP_RESUME_INFO_NONE,
    MMP_APP_RESUME_INFO_PHOTO_FRM,
    MMP_APP_RESUME_INFO_PHOTO_BWR,
    MMP_APP_RESUME_INFO_AUDIO_BWR,
    MMP_APP_RESUME_INFO_VIDEO_BWR,
    MMP_APP_RESUME_INFO_TEXT_BWR,
    MMP_APP_RESUME_INFO_DMR,
    MMP_APP_RESUME_INFO_PVR,    
	MMP_APP_RESUME_INFO_PHOTO_SHARE,
	MMP_APP_RESUME_INFO_FAC_PHOTO_PATTERN,
	MMP_APP_RESUME_INFO_VIEW_SAMPLE_IMAGE
} MMP_APP_RESUME_INFO_T;

/*-----Remove Device Info-----*/
typedef enum _MMP_REMOVE_DEVICE_INFO_T
{
    MMP_REMOVE_DEVICE_INFO_ACTIVE = 0,
    MMP_REMOVE_DEVICE_INFO_OTHER
} MMP_REMOVE_DEVICE_INFO_T;

/*---- Volume Update Info-----------*/
typedef struct _MMP_VOL_UPD_INFO_T
{
    BOOL        b_volume_up;
    BOOL        b_volume_down;
    BOOL        b_mute_dirty;
    BOOL        b_cec_sac;
} MMP_VOL_UPD_INFO_T;


/*-----Audio Lyrics Display Mode-----*/
typedef enum _MMP_LYRIC_DISP_MODE
{
    MMP_LYRIC_DISP_OFF = 0,
    MMP_LYRIC_DISP_SINGLE,
    MMP_LYRIC_DISP_MUTIL
}MMP_LYRIC_DISP_MODE;

/*-----Audio Lyrics Time Offset Mode-----*/
typedef enum _MMP_LYRIC_TIME_MODE
{
    MMP_LYRIC_TIME_OFF = 0,
    MMP_LYRIC_TIME_AUTO,
    MMP_LYRIC_TIME_USER
}MMP_LYRIC_TIME_MODE;

/*-----Audio Lyrics Encode Mode-----*/
typedef enum _MMP_LYRIC_ENCODE_MODE
{
    MMP_LYRIC_ENCODE_AUTO = 0,
    MMP_LYRIC_ENCODE_GB,
    MMP_LYRIC_ENCODE_BIG5,
    MMP_LYRIC_ENCODE_UTF8,
    MMP_LYRIC_ENCODE_UTF16
}MMP_LYRIC_ENCODE_MODE;

/*-----Common Key Info-----*/
#define MMP_NULL_KEYCODE                    ((UINT32) 0xFFFFFFFF)
typedef struct _MMP_KEY_INFO
{
    UINT32          ui4_keycode;
    UINT32          ui4_keystatus;
} MMP_KEY_INFO;

/*-----File Source Type*/
typedef enum _MMP_FILE_SRC_TYPE_T
{
    MMP_FILE_SRC_UNKNOWN,
    MMP_FILE_SRC_MASS_STRG,
    MMP_FILE_SRC_DLNA,
    MMP_FILE_SRC_NET_NEIGHBOR
} MMP_FILE_SRC_TYPE_T;

typedef struct _MMP_MSG_XNG_PARAM_T
{
    MMP_GROUND_MODE_T           e_mode;
} MMP_MSG_XNG_PARAM_T;

typedef struct _MMP_END_OF_PLAYLIST_INFO_T
{
    MMP_GROUND_MODE_T           e_mode;
    BOOL                        b_is_next;
} MMP_END_OF_PLAYLIST_INFO_T;

/*-----Message ID-----*/
#define MMP_MSG_ID_T                        UINT16
#define MMP_MSG_ID_POWER_OFF                ((MMP_MSG_ID_T)0)           /*pv_msg_param:*/
#define MMP_MSG_ID_POWER_ON                 ((MMP_MSG_ID_T)1)           /*pv_msg_param:*/
#define MMP_MSG_ID_APP_PAUSED               ((MMP_MSG_ID_T)2)           /*pv_msg_param:*/
#define MMP_MSG_ID_APP_RESUMED              ((MMP_MSG_ID_T)3)           /*pv_msg_param: a MMP_APP_RESUME_INFO_T value*/
#define MMP_MSG_ID_MEDIA_INSERTED           ((MMP_MSG_ID_T)4)           /*pv_msg_param: a DM_DEV_TYPE_T value*/
#define MMP_MSG_ID_MEDIA_REMOVED            ((MMP_MSG_ID_T)5)           /*pv_msg_param: a MMP_REMOVE_DEVICE_INFO_T value*/
#define MMP_MSG_ID_MEDIA_UNSUPPORT          ((MMP_MSG_ID_T)6)           /*pv_msg_param: NULL*/
#define MMP_MSG_ID_ACTIVE_PLAYLIST_XNG      ((MMP_MSG_ID_T)7)           /*pv_msg_param:*/
#define MMP_MSG_ID_BROWSE_FILE_XNG          ((MMP_MSG_ID_T)8)           /*pv_msg_param:*/
#define MMP_MSG_ID_BROWSE_FILE_INFO_READY   ((MMP_MSG_ID_T)9)           /*pv_nfy_param: a BOOL value. TRUE: info ready, FALSE: fail to load info.*/
#define MMP_MSG_ID_BROWSE_FILE_THUMBNAIL    ((MMP_MSG_ID_T)10)          /*pv_msg_param: a BOOL value. TRUE: thumbnail ready, FALSE: fail to load.*/
#define MMP_MSG_ID_GUI_LANG_XNG             ((MMP_MSG_ID_T)11)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_BROWSE_FOLDER_XNG        ((MMP_MSG_ID_T)12)
#define MMP_MSG_ID_KEY                      ((MMP_MSG_ID_T)13)          /*pv_msg_param: Key code*/
#define MMP_MSG_ID_END_OF_PLAYLIST          ((MMP_MSG_ID_T)14)          /*pv_msg_param: a pointer to MMP_END_OF_PLAYLIST_INFO_T structure*/
#define MMP_MSG_ID_VOL_INFO_UPD             ((MMP_MSG_ID_T)15)          /*pv_msg_param: a pointer to MMP_VOL_UPD_INFO_T structure*/
#define MMP_MSG_ID_APP_PRE_RESUMED          ((MMP_MSG_ID_T)16)          /*pv_msg_param: a MMP_APP_RESUME_INFO_T value*/
#define MMP_MSG_ID_APP_PRE_PAUSED           ((MMP_MSG_ID_T)17)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_PLAY_FILE_XNG            ((MMP_MSG_ID_T)18)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_PF_PALY_FAIL             ((MMP_MSG_ID_T)19)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_PSR_CNT_ORDER_XNG        ((MMP_MSG_ID_T)20)          /*pv_msg_param: a pointer to MMP_MSG_XNG_PARAM_T structure*/
#define MMP_MSD_ID_LOCKED_INP               ((MMP_MSG_ID_T)21)
#define MMP_MSG_ID_APP_STAT_XNG             ((MMP_MSG_ID_T)22)          /*pv_msg_param: a pointer to MMP_AP_STAT_XNG_INFO_T structure*/
#define MMP_MSG_ID_DMR_SHOW_CMD             ((MMP_MSG_ID_T)23)          /*pv_msg_param: a MMP_FP_SHOW_CMD_ID_T value*/
#define MMP_MSG_ID_PLAY_STOPPED             ((MMP_MSG_ID_T)24)          /*pv_msg_param: MMP_GROUND_MODE_T value*/
#define MMP_MSG_ID_MEDIA_REMOVED_EX         ((MMP_MSG_ID_T)25)          /*pv_msg_param: a pointer to RMV_REMOVE_DEVICE_INFO_T structure*/
#define MMP_MSG_ID_NW_PLAY_FILE_MISSING     ((MMP_MSG_ID_T)26)          /*pv_msg_param: MMP_GROUND_MODE_T value*/
#define MMP_MSG_ID_DMR_PALY_MEDIA_FAIL      ((MMP_MSG_ID_T)27)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_PRE_POWER_OFF            ((MMP_MSG_ID_T)28)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_NW_PLUGIN                ((MMP_MSG_ID_T)29)          /*pv_msg_param: NW_NFY_ID_T value*/
#define MMP_MSG_ID_ACT_NW_UNPLUG            ((MMP_MSG_ID_T)30)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_INPUT_DEV_INSERTED       ((MMP_MSG_ID_T)31)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_INPUT_DEV_REMOVED        ((MMP_MSG_ID_T)32)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_EXTERN_MSG               ((MMP_MSG_ID_T)33)          /*pv_msg_param: MMP_EXT_MSG_T value*/
#define MMP_MSG_ID_NEXT_FILE_READY          ((MMP_MSG_ID_T)34)          /*pv_msg_param: MMP_GROUND_MODE_T value*/
#define MMP_MSG_ID_IP_ADDR_CHANGED          ((MMP_MSG_ID_T)35)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_RMK_RETURN               ((MMP_MSG_ID_T)36)          /*pv_msg_param: NULL*/

//<<<modify_by_weijia_20130909
#define MMP_MSG_ID_FAC_PHOTO_PATTERN_CMD	((MMP_MSG_ID_T)37)			/*pv_msg_param: a MMP_FP_SHOW_CMD_ID_T value*/
//<<<modify_by_weijia_20130915_for_use_mmp_implement_view_sample_image
#define MMP_MSG_ID_VIEW_SAMPLE_IMAGE_CMD	((MMP_MSG_ID_T)38)			/*pv_msg_param: a MMP_FP_SHOW_CMD_ID_T value*/
#define MMP_MSG_ID_PIC_XNG                  ((MMP_MSG_ID_T)39)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_BROWSE_FILE_THUMBNAIL_EX ((MMP_MSG_ID_T)40)          /*pv_msg_param: GL_RECT_T*/
#define MMP_MSG_ID_USB_NET_DEVICE_INSERT    ((MMP_MSG_ID_T)41)          /*pv_msg_param: NULL*/
#define MMP_MSG_ID_USB_NET_DEVICE_REMOVED   ((MMP_MSG_ID_T)42)          /*pv_msg_param: NULL*/

//>>>
#define MMP_MSG_ID_CUSTOM_START             ((MMP_MSG_ID_T)1000)

#define MMP_MEDIA_INTF_IS_LEGAL(_t_intf)        \
(                                               \
    (((_t_intf).pf_init) &&                     \
    ((_t_intf).pf_deinit) &&                    \
    ((_t_intf).pf_handle_msg) &&                \
    ((_t_intf).pf_is_type_of)) ? TRUE : FALSE   \
)

/*-----File Parser Special Token-----*/
#define MMP_FF_FILE_PSR_TOKEN                   "PARSER_FF:"
#define MMP_FF_FILE_PSR_TOKEN_LEN               ((UINT32) 10)   /*not include null character*/

#define MMP_FF_IS_FILE_PSR_PATH(_ps_path)                                                       \
(                                                                                               \
    (0 == c_strncmp(_ps_path, MMP_FF_FILE_PSR_TOKEN, MMP_FF_FILE_PSR_TOKEN_LEN)) ? TRUE : FALSE \
)

/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/
/*-----Playlist Attribute: For MMP_PL_ATTR_ID_EFFECT-----*/
typedef struct _MMP_EFFECT_T
{
    IMG_TFX_EFFECT_T        e_effect;
    BOOL                    b_is_enabled;       /*FALSE: No effect is enabled, e_effect is invalid. TRUE: e_effect is enabled.*/
    BOOL					b_first_photo;
} MMP_EFFECT_T;

/*-----Media Interface-----*/
typedef INT32 (*mmp_comp_init)(VOID);
typedef INT32 (*mmp_comp_deinit)(VOID);
typedef INT32 (*mmp_comp_handle_msg)(MMP_MSG_ID_T e_msg_id, VOID* pv_msg_param);
typedef INT32 (*mmp_mda_is_type_of)(const CHAR* ps_filename, MMP_MEDIA_TYPE_T* pe_type);

typedef struct _MMP_MEDIA_T
{
    mmp_comp_init               pf_init;
    mmp_comp_deinit             pf_deinit;
    mmp_comp_handle_msg         pf_handle_msg;
    mmp_mda_is_type_of          pf_is_type_of;
} MMP_MEDIA_T;

/*-----FID-----------------*/
typedef UINT16 FID_T;

#ifndef MMP_COM_UI_HEADER_FILE
#define MMP_COM_UI_HEADER_FILE "mmp/common_ui/mmp_common_ui.h"
#endif

#ifndef MMP_MLM_HEADER_FILE
#define MMP_MLM_HEADER_FILE "res/mmp/gen/mmp_mlm.h"
#endif


/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/

#endif /*_MMP_COMMON_H_*/
