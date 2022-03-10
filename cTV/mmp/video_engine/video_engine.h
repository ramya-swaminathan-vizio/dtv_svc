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
 * $RCSfile: video_engine.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This is the header file for video engine.
 *---------------------------------------------------------------------------*/

#ifndef _VIDEO_ENGINE_H_
#define _VIDEO_ENGINE_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_os.h"
#include "c_handle.h"
#include "c_dbg.h"
#include "c_cli.h"
#include "c_aee.h"
#include "c_appman.h"
#include "c_wgl.h"
#include "c_fe.h"
#include "c_gl.h"
#include "c_pcl.h"

#include "u_midxbuld.h"
#include "u_common.h"

#include "u_svctx.h"
#include "c_svctx.h"
#include "u_cli.h"
#include "u_uc.h"
#include "u_wgl.h"
#include "u_wgl_sets.h"
#include "u_pcl.h"
#include "u_handle.h"
#include "u_mm_common.h"
#include "u_mm_hdlr.h"
#include "amb/a_amb.h"
#include "am/a_am.h"

#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp/mmp_intf_file_player.h"

#include "res/mmp/video_engine/mmp_video_engine_rc.h"

#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
#include "nav/teletext/a_nav_teletext.h"
#endif
#include "app_util/splayer/splayer.h"



/*-----------------------------------------------------------------------------
                    macros, typedefs, enums
-----------------------------------------------------------------------------*/
#define MMP_VE_IS_MONO(channel)            (channel == ASH_CHANNELS_MONO                \
                                                || channel == ASH_CHANNELS_MONO_SUB      \
                                                || channel == ASH_CHANNELS_MONO_LFE)
#define MMP_VE_IS_STEREO(channel)          (channel == ASH_CHANNELS_STEREO                          \
                                                || channel == ASH_CHANNELS_STEREO_SUB                \
                                                || channel == ASH_CHANNELS_STEREO_LFE                \
                                                || channel == ASH_CHANNELS_STEREO_DOLBY_SURROUND)
#define MMP_VE_IS_DUALMONO(channel)        (channel == ASH_CHANNELS_DUAL_MONO            \
                                                || channel == ASH_CHANNELS_DUAL_MONO_LFE)

#define VIDEO_ENGINE_INFO_VER_INVALID             ((UINT32)0)
#define VIDEO_ENGINE_LOAD_VER_INVALID             ((UINT32)0)

/* flag for information instance */
#define VIDEO_ENGINE_INFO_FLAG_LOADING            ((UINT8)0x01)
#define VIDEO_ENGINE_INFO_FLAG_STOPING            ((UINT8)0x02)
#define VIDEO_ENGINE_INFO_FLAG_SUCCESS            ((UINT8)0x04)

/* flag for video engine */
#define VIDEO_ENGINE_FLAG_PLAY_DISP_RESUMED       ((UINT32)0x00000001)
#define VIDEO_ENGINE_FLAG_THUMB_DISP_RESUMED      ((UINT32)0x00000002)

#define VIDEO_ENGINE_THUMB_BUF_ID_T               UINT8
#define VIDEO_ENGINE_THUMB_BUF_ID_SHOW            ((VIDEO_ENGINE_THUMB_BUF_ID_T)0)
#define VIDEO_ENGINE_THUMB_BUF_ID_LOAD            ((VIDEO_ENGINE_THUMB_BUF_ID_T)1)


#define VIDEO_ENGINE_ELMT_RESET(_t_elmt)                                       \
do                                                                             \
{                                                                              \
    c_memset(&(_t_elmt), 0, sizeof(_MMP_VE_ELMT_INFO_T));                      \
    (_t_elmt).t_elmt_fid = MMP_FID_NULL_REC_IDX;                               \
}while(0)

#define VIDEO_ENGINE_INFO_RESET(_t_info)                                       \
do                                                                             \
{                                                                              \
    c_memset(&(_t_info), 0, sizeof(_MMP_VE_INFO_INST_T));                      \
    (_t_info).t_elmt_fid = MMP_FID_NULL_REC_IDX;                               \
}while(0)


/*flag for notify*/
#define MMP_VE_PLAY_FLAG_VIDEO_FMT_UPDATE             	((uint32_t) (1))         ///< indicating that video engine receive video fmt update notify
#define MMP_VE_PLAY_FLAG_AUDIO_FMT_UPDATE             	((uint32_t) (1 << 1))    ///< indicating that video engine receive audio fmt update notify
#define MMP_VE_PLAY_FLAG_AUDIO_ONLY            			((uint32_t) (1 << 2))   ///< indicating that video engine receive audio only  notify
#define MMP_VE_PLAY_FLAG_VIDEO_SCRAMBLE        			((uint32_t) (1 << 3))   ///< indicating that video engine receive video scramble notify
#define MMP_VE_PLAY_FLAG_MEDIA_HD_NOT_SUPPORT  			((uint32_t) (1 << 4))
#define MMP_VE_PLAY_FLAG_MEDIA_DRM_NOT_SUPPORT 			((uint32_t) (1 << 5))
#define MMP_VE_PLAY_FLAG_MEDIA_RESOLUTION_NOT_SUPPORT 	((uint32_t) (1 << 6))
#define MMP_VE_PLAY_FLAG_MEDIA_FRAMERATE_NOT_SUPPORT    ((uint32_t) (1 << 7))
#define MMP_VE_PLAY_FLAG_VIDEO_NOT_SUPPORT				((uint32_t) (1 << 8))
#define MMP_VE_PLAY_FLAG_SUBTITLE             			((uint32_t) (1 << 9))   ///< indicating that the content contains subtitle and subtitle is to be played
#define MMP_VE_PLAY_FLAG_UNKNOWN              			((uint32_t) (1 << 31))   ///< indicating that App doesn't know the play flag.  If this bit is 1, all other bits are ignored.

#define _VIDEO_ENGINE_IS_PLAY_NORMAL(_pt_elmt)															\
(((_pt_elmt)->ui4_notify_flag & MMP_VE_PLAY_FLAG_VIDEO_FMT_UPDATE)|| 										\
   (((_pt_elmt)->ui4_notify_flag & MMP_VE_PLAY_FLAG_AUDIO_FMT_UPDATE) && 										\
    (((_pt_elmt)->ui4_notify_flag & MMP_VE_PLAY_FLAG_AUDIO_ONLY) || 									\
     ((_pt_elmt)->ui4_notify_flag & MMP_VE_PLAY_FLAG_MEDIA_HD_NOT_SUPPORT) ||							\
     ((_pt_elmt)->ui4_notify_flag & MMP_VE_PLAY_FLAG_MEDIA_DRM_NOT_SUPPORT) ||							\
     ((_pt_elmt)->ui4_notify_flag & MMP_VE_PLAY_FLAG_MEDIA_RESOLUTION_NOT_SUPPORT) ||					\
     ((_pt_elmt)->ui4_notify_flag & MMP_VE_PLAY_FLAG_MEDIA_FRAMERATE_NOT_SUPPORT) ||					\
     ((_pt_elmt)->ui4_notify_flag & MMP_VE_PLAY_FLAG_VIDEO_NOT_SUPPORT))))

#define _VIDEO_ENGINE_NEW_LOAD_VER(_pt_this)                                   \
{                                                                              \
    (_pt_this)->ui4_load_ver++;                                                \
    if(VIDEO_ENGINE_LOAD_VER_INVALID == (_pt_this)->ui4_load_ver)              \
    {                                                                          \
        (_pt_this)->ui4_load_ver++;                                            \
    }                                                                          \
}

#define _VIDEO_ENGINE_SET_LOAD_VER_INVALID(_ui4_ver)                           \
{                                                                              \
    (_ui4_ver) = VIDEO_ENGINE_LOAD_VER_INVALID;                                \
}

/*-----------------------------------------------------------------------------
 * define setting types for audio lyrics
 *---------------------------------------------------------------------------*/
#ifndef APP_MMP_SUBTITLE_CUSTOMER_SUPPORT
typedef struct {} *MMP_VE_PLAY_INST_PTR_T;
typedef struct {} *MMP_VE_INFO_INST_PTR_T;

typedef enum /* VIDEO FILE TYPE */
{
    MMP_VE_FILE_TYPE_UNKNOWN = 0,   /* Unknown Type */
    MMP_VE_FILE_TYPE_DIVX           /* Divx Type*/
} MMP_VE_FILE_TYPE_T;
#endif

typedef enum
{
    SCC_AUD_MODE_TYPE_MATRIX = 0,
    SCC_AUD_MODE_TYPE_DOWNMIX
}SCC_AUD_MODE_TYPE_T;

typedef enum /* CONTENT REPEAT */
{
    MMP_VE_CTNT_RPT_TYPE_NONE = 0,
    MMP_VE_CTNT_RPT_TYPE_PT_A,  /* Set Point A */
    MMP_VE_CTNT_RPT_TYPE_PT_B   /* Set Point B */
} MMP_VE_CTNT_RPT_TYPE_T;

typedef enum /* FAST FORWARD */
{
    MMP_VE_FAST_FWD_TYPE_2X    = MM_SPEED_TYPE_FORWARD_2X,
    MMP_VE_FAST_FWD_TYPE_4X    = MM_SPEED_TYPE_FORWARD_4X,
    MMP_VE_FAST_FWD_TYPE_8X    = MM_SPEED_TYPE_FORWARD_8X,
    MMP_VE_FAST_FWD_TYPE_16X   = MM_SPEED_TYPE_FORWARD_16X,
    MMP_VE_FAST_FWD_TYPE_32X   = MM_SPEED_TYPE_FORWARD_32X,
    MMP_VE_FAST_FWD_TYPE_64X   = MM_SPEED_TYPE_FORWARD_64X,
    MMP_VE_FAST_FWD_TYPE_128X  = MM_SPEED_TYPE_FORWARD_128X,
    MMP_VE_FAST_FWD_TYPE_256X  = MM_SPEED_TYPE_FORWARD_256X,
    MMP_VE_FAST_FWD_TYPE_512X  = MM_SPEED_TYPE_FORWARD_512X,
    MMP_VE_FAST_FWD_TYPE_1024X = MM_SPEED_TYPE_FORWARD_1024X
} MMP_VE_FAST_FWD_TYPE_T;

typedef enum /* FAST REWIND  */
{
    MMP_VE_FAST_RWD_TYPE_1X    = MM_SPEED_TYPE_REWIND_1X,
    MMP_VE_FAST_RWD_TYPE_2X    = MM_SPEED_TYPE_REWIND_2X,
    MMP_VE_FAST_RWD_TYPE_4X    = MM_SPEED_TYPE_REWIND_4X,
    MMP_VE_FAST_RWD_TYPE_8X    = MM_SPEED_TYPE_REWIND_8X,
    MMP_VE_FAST_RWD_TYPE_16X   = MM_SPEED_TYPE_REWIND_16X,
    MMP_VE_FAST_RWD_TYPE_32X   = MM_SPEED_TYPE_REWIND_32X,
    MMP_VE_FAST_RWD_TYPE_64X   = MM_SPEED_TYPE_REWIND_64X,
    MMP_VE_FAST_RWD_TYPE_128X  = MM_SPEED_TYPE_REWIND_128X,
    MMP_VE_FAST_RWD_TYPE_256X  = MM_SPEED_TYPE_REWIND_256X,
    MMP_VE_FAST_RWD_TYPE_512X  = MM_SPEED_TYPE_REWIND_512X,
    MMP_VE_FAST_RWD_TYPE_1024X = MM_SPEED_TYPE_REWIND_1024X
} MMP_VE_FAST_RWD_TYPE_T;

typedef enum /* SLOW FORWARD */
{
    MMP_VE_SLOW_FWD_TYPE_2X    = MM_SPEED_TYPE_FORWARD_1_DIV_2X,  /* 1/2  */
    MMP_VE_SLOW_FWD_TYPE_4X    = MM_SPEED_TYPE_FORWARD_1_DIV_4X,  /* 1/4  */
    MMP_VE_SLOW_FWD_TYPE_8X    = MM_SPEED_TYPE_FORWARD_1_DIV_8X,  /* 1/8  */
    MMP_VE_SLOW_FWD_TYPE_16X   = MM_SPEED_TYPE_FORWARD_1_DIV_16X, /* 1/16 */
    MMP_VE_SLOW_FWD_TYPE_32X   = MM_SPEED_TYPE_FORWARD_1_DIV_32X  /* 1/32 */
} MMP_VE_SLOW_FWD_TYPE_T;

typedef enum /* SLOW REWIND  */
{
    MMP_VE_SLOW_RWD_TYPE_2X    = MM_SPEED_TYPE_REWIND_1_DIV_2X,   /* 1/2  */
    MMP_VE_SLOW_RWD_TYPE_4X    = MM_SPEED_TYPE_REWIND_1_DIV_4X,   /* 1/4  */
    MMP_VE_SLOW_RWD_TYPE_8X    = MM_SPEED_TYPE_REWIND_1_DIV_8X,   /* 1/8  */
    MMP_VE_SLOW_RWD_TYPE_16X   = MM_SPEED_TYPE_REWIND_1_DIV_16X,  /* 1/16 */
    MMP_VE_SLOW_RWD_TYPE_32X   = MM_SPEED_TYPE_REWIND_1_DIV_32X   /* 1/32 */
} MMP_VE_SLOW_RWD_TYPE_T;

typedef enum
{
    MMP_VE_ZOOM_TYPE_1X = 0,
    MMP_VE_ZOOM_TYPE_2X,
    MMP_VE_ZOOM_TYPE_4X,
    MMP_VE_ZOOM_TYPE_8X,
    MMP_VE_ZOOM_TYPE_16X,
    MMP_VE_ZOOM_TYPE_32X,
    MMP_VE_ZOOM_TYPE_64X,
    MMP_VE_ZOOM_TYPE_128X,
    MMP_VE_ZOOM_TYPE_256X,
    MMP_VE_ZOOM_TYPE_512X
} MMP_VE_ZOOM_TYPE_T,
* MMP_VE_ZOOM_TYPE_PTR_T;

/* PLAYER status */
typedef enum
{
    MMP_VE_PLAY_STAT_OPEN = 0,
    MMP_VE_PLAY_STAT_PLAY,
    MMP_VE_PLAY_STAT_NEXT,
    MMP_VE_PLAY_STAT_UNSUP,
    MMP_VE_PLAY_STAT_PAUSE,
    MMP_VE_PLAY_STAT_BLANK,
    MMP_VE_PLAY_STAT_FAST_FWD,
    MMP_VE_PLAY_STAT_FAST_RWD,
    MMP_VE_PLAY_STAT_SLOW_FWD,
    MMP_VE_PLAY_STAT_SLOW_RWD,
    MMP_VE_PLAY_STAT_STOP,
    MMP_VE_PLAY_STAT_CLOSE
} MMP_VE_PLAY_STAT_T,
* MMP_VE_PLAY_STAT_PTR_T;

typedef struct
{
    SCDB_REC_TYPE_T            e_rec_type;
    BOOL                       b_is_progressive;
    UINT32                     ui4_frame_rate;
    VID_ENC_T                  t_enc_fmt;
    UINT32                     ui4_width;
    UINT32                     ui4_height;
    VSH_SRC_ASPECT_RATIO_T     e_asp_ratio;
    MMP_VE_ZOOM_TYPE_T         t_max_zoom;
    MMP_VE_ZOOM_TYPE_T         t_idx_zoom;
} MMP_VE_VID_INFO_T,
* MMP_VE_VID_INFO_PTR_T;

#ifndef APP_MMP_PVR_AUDIO_SWITCH_CUST_RULE
typedef enum
{
    MMP_VE_ALT_AUDIO_NULL= 0,
    MMP_VE_ALT_AUDIO_VISUAL_IMPAIRED,
    MMP_VE_ALT_AUDIO_HEARING_IMPAIRED,
} MMP_VE_ALT_AUDIO_T;

typedef enum
{
    MMP_VE_AUD_SUB_TYPE_UNKNOWN = 0,
    MMP_VE_AUD_SUB_TYPE_MONO,
    MMP_VE_AUD_SUB_TYPE_STEREO,
    MMP_VE_AUD_SUB_TYPE_DUALMONO,
    MMP_VE_AUD_SUB_TYPE_SURROUND
} MMP_VE_AUD_SUB_TYPE_T;
typedef struct
 {
    SCDB_REC_TYPE_T             e_rec_type;
    AUD_ENC_T                   t_enc_fmt;
    ASH_DECODE_TYPE_T           e_dec_type;
    ASH_AUDIO_FMT_T             e_aud_fmt;
    ASH_CHANNELS_T              e_channels;
    SCC_AUD_DOWNMIX_MODE_T      e_aud_mode;
    MMP_VE_AUD_SUB_TYPE_T       e_aud_mime_type;
    UINT16                      ui2_aud_num;
    UINT16                      ui2_sel_idx;
    UINT32                      ui4_strm_id;
    UINT32                      ui4_strm_sub_id;
    STREAM_COMP_ID_T            at_comp_id[_MMP_VERC_AUD_MAX_NUM];
    ISO_639_LANG_T              as_lang[_MMP_VERC_AUD_MAX_NUM];
	MMP_VE_ALT_AUDIO_T	        t_alt_audio[_MMP_VERC_AUD_MAX_NUM];
} MMP_VE_AUD_INFO_T,
* MMP_VE_AUD_INFO_PTR_T;
#endif

typedef struct
{
    ASH_CHANNELS_T              e_chn_type;
} MMP_VE_CHN_INFO_T,
* MMP_VE_CHN_INFO_PTR_T;

#ifndef APP_MMP_SUBTITLE_CUSTOMER_SUPPORT
typedef enum
{
    MMP_VE_SBTL_ENCODE_UNKNOW = 0,
    MMP_VE_SBTL_ENCODE_ISO8859_2,
    MMP_VE_SBTL_ENCODE_ISO8859_5,
    MMP_VE_SBTL_ENCODE_ISO8859_7,
    MMP_VE_SBTL_ENCODE_ISO8859_9,
    MMP_VE_SBTL_ENCODE_NUM
} MMP_VE_SBTL_ENCODING_T;

typedef UINT8 MMP_VE_SBTL_STYLE;
#define MMP_VE_SBTL_STYLE_NONE  ((MMP_VE_SBTL_STYLE)(0))
#define MMP_VE_SBTL_STYLE_TXT   ((MMP_VE_SBTL_STYLE)(1))
#define MMP_VE_SBTL_STYLE_IMG   ((MMP_VE_SBTL_STYLE)(2))
#define MMP_VE_SBTL_STYLE_EXT   ((MMP_VE_SBTL_STYLE)(4))

typedef struct
 {
    UINT16                      ui2_sub_num;
    UINT16                      ui2_sel_idx;
    UINT32                      ui4_strm_id;
    STREAM_COMP_ID_T            at_comp_id[_MMP_VERC_SUB_MAX_NUM];
    ISO_639_LANG_T              as_lang[_MMP_VERC_SUB_MAX_NUM];
	MMP_VE_SBTL_STYLE           e_style[_MMP_VERC_SUB_MAX_NUM];
    BOOL                        b_extra_sub;
    MMP_VE_SBTL_ENCODING_T      t_sub_font;
} MMP_VE_SUB_INFO_T,
* MMP_VE_SUB_INFO_PTR_T;
#endif

typedef enum
{
    MMP_VE_SBTL_SET_HILT_STL  = SVCTX_MM_SBTL_SET_TYPE_HILT_STL,
    MMP_VE_SBTL_SET_DISP_MODE = SVCTX_MM_SBTL_SET_TYPE_DISP_MODE,
    MMP_VE_SBTL_SET_HILT_ATTR = SVCTX_MM_SBTL_SET_TYPE_HILT_ATTR,
    MMP_VE_SBTL_SET_NRML_ATTR = SVCTX_MM_SBTL_SET_TYPE_NRML_ATTR,
    MMP_VE_SBTL_SET_TIME_OFST = SVCTX_MM_SBTL_SET_TYPE_TIME_OFST,
    MMP_VE_SBTL_SET_FONT_ENC  = SVCTX_MM_SBTL_SET_TYPE_FONT_ENC
} MMP_VE_SBTL_ATTR_SET_T;

typedef struct
{
    MMP_VE_SBTL_ATTR_SET_T          t_attr_type;

    union
    {
        MM_SVC_SBTL_HILT_STL_T      t_hilt_stl;
        MM_SVC_SBTL_DISP_MODE_T     t_disp_mode;
        MM_SVC_SBTL_DISP_ATTR_T     t_hilt_attr;
        MM_SVC_SBTL_DISP_ATTR_T     t_nrml_attr;
        MM_SVC_SBTL_TIME_OFST_T     t_time_ofst;
        MM_SVC_SBTL_FONT_ENC_T      t_font_enc;
    }u;

} MMP_VE_SBTL_ATTR_T,
* MMP_VE_SBTL_ATTR_PTR_T;

typedef enum
{
    MMP_VE_POS_TYPE_TIME,
    MMP_VE_POS_TYPE_BYTE
} MMP_VE_POS_TYPE_T;

typedef enum
{
    MMP_VE_DUR_TYPE_TIME,
    MMP_VE_DUR_TYPE_BYTE
} MMP_VE_DUR_TYPE_T;

typedef MINFO_DISP_INFO_T  MMP_VE_CHAP_META_DATA_T;
typedef MINFO_DISP_INFO_T* MMP_VE_CHAP_META_DATA_PTR_T;

#ifndef APP_MMP_SUBTITLE_CUSTOMER_SUPPORT
typedef enum
{
    MMP_VE_DRM_TYPE_NORMAL = 0,          /* non-divx type media file    */
    MMP_VE_DRM_TYPE_UNAUTH,              /* unauthorized divx file      */
    MMP_VE_DRM_TYPE_EXPIRE,              /* rental-expired divx file    */
    MMP_VE_DRM_TYPE_RENTAL,              /* rental-confirmed divx file  */
} MMP_VE_DRM_TYPE_T;
#endif

/* This structure enumerates all info type of video. */
typedef enum
{
    MMP_VE_INFO_ID_INVAL = 0,
    MMP_VE_INFO_ID_NAME,
    MMP_VE_INFO_ID_TITLE,
    MMP_VE_INFO_ID_DIRECTOR,
    MMP_VE_INFO_ID_COPYRIGHT,
    MMP_VE_INFO_ID_YEAR,
    MMP_VE_INFO_ID_DATE,
    MMP_VE_INFO_ID_GENRE,
    MMP_VE_INFO_ID_DURATION,
    MMP_VE_INFO_ID_SIZE,
    MMP_VE_INFO_ID_ARTIST,
    MMP_VE_INFO_ID_ALBUM,
    MMP_VE_INFO_ID_BITRATE,
    MMP_VE_INFO_ID_PROTECT,
    MMP_VE_INFO_ID_CREATE_TIME,
    MMP_VE_INFO_ID_ACCESS_TIME,
    MMP_VE_INFO_ID_MODIFY_TIME,
    MMP_VE_INFO_ID_RESOLUTION,
    MMP_VE_INFO_ID_NEXT_TITLE,
    MMP_VE_INFO_ID_NEXT_ARTIST,
    MMP_VE_INFO_ID_IS_SEEK_SUPPORTED
} MMP_VE_INFO_ID_T,
* MMP_VE_INFO_ID_PTR_T;

#ifndef APP_MMP_SUBTITLE_CUSTOMER_SUPPORT
typedef struct
{
    MMP_VE_DRM_TYPE_T           t_drm_type;
    MMP_VE_FILE_TYPE_T          t_file_type;
    UINT32                      ui4_use_limit;
    UINT32                      ui4_use_count;
    UINT32                      ui4_use_left;
    UINT32                      ui4_title_id;
    BOOL                        b_user_yes;
} MMP_VE_DIVX_CERT_T,
* MMP_VE_DIVX_CERT_PTR_T;
#endif

typedef enum
{
    MMP_VE_NFY_CODE_MEDIA_OPEN_BGN,
    MMP_VE_NFY_CODE_MEDIA_OPEN_ERR,
    MMP_VE_NFY_CODE_MEDIA_PLAY_ERR,
    MMP_VE_NFY_CODE_MEDIA_NEXT_OPEN_ERR,
    MMP_VE_NFY_CODE_MEDIA_NO_RESOURCES, /*For file miss case*/
    MMP_VE_NFY_CODE_MEDIA_FILE_ERR, /*For file miss case*/
    MMP_VE_NFY_CODE_MEDIA_OPER_ERROR,/*server file not found*/
    MMP_VE_NFY_CODE_MEDIA_OPEN_END,
    MMP_VE_NFY_CODE_MEDIA_NEXT_OPEN_END,
    MMP_VE_NFY_CODE_MEDIA_PLAY_PROGRAM_INFO_READY,
    MMP_VE_NFY_CODE_MEDIA_PLAY_HD_NOT_SUPPORT,
    MMP_VE_NFY_CODE_MEDIA_PLAY_DRM_NOT_SUPPORT,
    MMP_VE_NFY_CODE_MEDIA_PLAY_HAS_NO_CONTENT,
    MMP_VE_NFY_CODE_MEDIA_PLAY_RESOLUTION_NOT_SUPPORT,
    MMP_VE_NFY_CODE_MEDIA_PLAY_FRAMERATE_NOT_SUPPORT,
    MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_ONLY_SVC,
    MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_ONLY_SVC,
    MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_ONLY_STRM,
    MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_ONLY_STRM,
    MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_VIDEO_SVC,
    MMP_VE_NFY_CODE_MEDIA_PLAY_NO_AUDIO_VIDEO_SVC,
    MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_NOT_SUPPORT,
    MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_NOT_SUPPORT,
    MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_FMT_UPDATE,
    MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_DOLBY_ATMOS,
    MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_DOLBY_NO_ATMOS,
#ifdef APP_MMP_SCDB_SEPARATE
    MMP_VE_NFY_CODE_MEDIA_PLAY_SCDB_CHANGE,
#endif
    MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_FMT_UPDATE,
    MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL,
    MMP_VE_NFY_CODE_MEDIA_PLAY_REPLAY,
    MMP_VE_NFY_CODE_MEDIA_PLAY_CHAPTER_CHANGE,
    MMP_VE_NFY_CODE_MEDIA_PLAY_DURATION_UPDATE,
    MMP_VE_NFY_CODE_MEDIA_PLAY_SUBTITLE_UPDATE,
    MMP_VE_NFY_CODE_MEDIA_PLAY_SPEED_UPDATE,
    MMP_VE_NFY_CODE_MEDIA_PLAY_AB_REPEAT_DONE,
    MMP_VE_NFY_CODE_MEDIA_PLAY_SEEK_READY,
    MMP_VE_NFY_CODE_MEDIA_PLAY_SEEK_ERROR,
    MMP_VE_NFY_CODE_MEDIA_PLAY_INTRRPTD,
#ifdef APP_MMP_PVR_SUPPORT
    MMP_VE_NFY_CODE_STREAM_OPENED,
	MMP_VE_NFY_CODE_MEDIA_PVR_THUMBNAIL_PIN_VALID_PARENT_RATING,
	MMP_VE_NFY_CODE_MEDIA_PVR_PLAYING_PIN_VALID_PARENT_RATING,
	//<<<modify_by_weijia_20130924_for_pvr_guidance_description_blocked
	MMP_VE_NFY_CODE_MEDIA_PVR_GUIDANCE_BLOCKED_DUR_THUMB,
	MMP_VE_NFY_CODE_MEDIA_PVR_GUIDANCE_BLOCKED_AFTER_THUMB,
    MMP_VE_NFY_CODE_MEDIA_SERVICE_PIN_BLOCKED,
	//>>>
	MMP_VE_NFY_CODE_MEDIA_PVR_PIN_VALID_PROG_BLOCKED,
	MMP_VE_NFY_CODE_MEDIA_PVR_PLAYING_PIN_VALID_PROG_BLOCKED,
#endif
#ifdef SUPPORT_CIPLUS_RECORD
        MMP_VE_NFY_CODE_MEDIA_PLAY_CAM_CARD_REMOVE,
#endif
    MMP_VE_NFY_CODE_MEDIA_STOP_BGN,
    MMP_VE_NFY_CODE_MEDIA_STOP_EOS,
    MMP_VE_NFY_CODE_MEDIA_THUMBNAIL_CANCEL_STOP,
    MMP_VE_NFY_CODE_MEDIA_SCRAMBLE_VID,
    MMP_VE_NFY_CODE_MEDIA_SCRAMBLE_AUD,
    MMP_VE_NFY_CODE_MEDIA_SCRAMBLE_VID_AUD,
    MMP_VE_NFY_CODE_MEDIA_SCRAMBLE_VID_ONLY,
    MMP_VE_NFY_CODE_MEDIA_SCRAMBLE_AUD_ONLY,
	MMP_VE_NFY_CODE_MEDIA_NEED_PSW,
    MMP_VE_NFY_CODE_MEDIA_STOP_END,
    MMP_VE_NFY_CODE_SUBTITLE_INFO_UPDATE,
    MMP_VE_NFY_CODE_AUDIO_INFO_UPDATE,
    MMP_VE_NFY_CODE_MEDIA_SPEED_UPDATE,
    MMP_VE_NFY_CODE_MEDIA_CAM_RATING_LOWER_EVENT_RATING,
    MMP_VE_NFY_CODE_MEDIA_MEDIA_LOST,

    MMP_VE_NFY_CODE_MEDIA_PLAYING_INIT_OK,

    MMP_VE_NFY_CODE_MEDIA_PVR_TRICK_REACH_VALID_RANGE_END
} MMP_VE_NFY_CODE_T;

typedef VOID (*mmp_ve_play_nfy_fct) (
                    MMP_VE_NFY_CODE_T               e_nfy_code,       /* out  */
                    VOID*                           pv_param          /* out  */
                    );
typedef struct
{
    UINT8   ui1_program_num;
    UINT8   ui1_cur_idx;
} MMP_VE_PROGRAM_INFO_T,
* MMP_VE_PROGRAM_INFO_PTR_T;

#ifndef _MMP_VERC_GET_ELMT_EFFECT
#define _MMP_VERC_GET_ELMT_EFFECT()               (_MMP_VE_ELMT_EFCT_DEF)
#endif


#ifdef DIVX_PLUS_CER
typedef enum
{
    MMP_VE_CHAP_CMD_GET_NUM = 0,
    MMP_VE_CHAP_CMD_GET_META_DATA,
    MMP_VE_CHAP_CMD_SET_TITLE,
    MMP_VE_CHAP_CMD_SET_CHAP,
    MMP_VE_CHAP_CMD_SET_SGMT
} MMP_VE_CHAP_CMD_T;

typedef enum
{
    MMP_VE_SGMT_TYPE_DIGIT = 0,
    MMP_VE_SGMT_TYPE_NEXT,
    MMP_VE_SGMT_TYPE_PREV
} MMP_VE_SGMT_TYPE_T;

typedef struct
{
    UINT64                      ui8_title_hide;
    UINT64                      ui8_list_hide;
    UINT64                      ui8_chap_hide;
} MMP_VE_CHAP_NUM_EX_T,
* MMP_VE_CHAP_NUM_EX_PTR_T;

typedef struct
{
    UINT32                      ui4_title_num;
    UINT32                      ui4_title_idx;

    UINT32                      ui4_list_num;
    UINT32                      ui4_list_idx;

    UINT32                      ui4_chap_num;
    UINT32                      ui4_chap_idx;

    MMP_VE_CHAP_NUM_EX_T        t_chap_ext;
} MMP_VE_CHAP_NUM_T,
* MMP_VE_CHAP_NUM_PTR_T;

typedef struct
{
    MMP_VE_DIVX_CERT_T          e_divx_cert;
} MMP_VE_TITLE_ID_T,
* MMP_VE_TITLE_ID_PTR_T;

typedef struct
{
    UINT32                      ui4_list_id;
    UINT32                      ui4_chap_id;
} MMP_VE_CHAP_ID_T,
* MMP_VE_CHAP_ID_PTR_T;

typedef struct
{
    MMP_VE_SGMT_TYPE_T          e_sgmt_type;
    UINT32                      ui4_sgmt_id;
} MMP_VE_SGMT_ID_T,
* MMP_VE_SGMT_ID_PTR_T;

typedef struct
{
    MMP_VE_CHAP_CMD_T           e_chap_cmd;
    union
    {
        MMP_VE_CHAP_NUM_T       t_chap_num;
        MMP_VE_TITLE_ID_T       t_title_id;
        MMP_VE_CHAP_ID_T        t_chap_id;
        MMP_VE_SGMT_ID_T        t_sgmt_id;
        MMP_VE_CHAP_META_DATA_T t_meta_data;
    } u;
} MMP_VE_CHAP_DATA_T,
* MMP_VE_CHAP_DATA_PTR_T;

extern INT32 video_engine_chap_get(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_CHAP_DATA_PTR_T          pt_chap_data      /* out */
                    );

extern INT32 video_engine_chap_set(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_CHAP_DATA_PTR_T          pt_chap_data      /* out */
                    );
#endif

#ifdef LINUX_AUTO_TEST
#include <stdlib.h>
#define mmp_seek_done_file   LINUX_TMP_PATH"/autotest/mmp_seek_done"
#define mmp_trick_done_file  LINUX_TMP_PATH"/autotest/mmp_trick_done"
#define mmp_stop_done_file   LINUX_TMP_PATH"/autotest/mmp_sync_stop_done"
#define mmp_stop_fail_file   LINUX_TMP_PATH"/autotest/mmp_sync_stop_fail"
#define mmp_audio_fmt_file   LINUX_TMP_PATH"/autotest/mmp_audio_fmt_update"
#define mmp_video_fmt_file   LINUX_TMP_PATH"/autotest/mmp_video_fmt_update"

#define CREATE_MMP_TMP_FILE(_file)          \
	{                                       \
		system("touch "_file);              \
	}
#endif



/*-----------------------------------------------------------------------------
 * video engine export methods declarations
 *---------------------------------------------------------------------------*/
extern INT32 video_engine_create(
                    mmp_ve_play_nfy_fct             pf_play_nfy,      /* in  */
                    MMP_VE_PLAY_INST_PTR_T*         ppt_play_inst     /* out */
                    );

extern INT32 video_engine_destroy(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_open(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const CHAR*                     ps_file_name      /* in  */
                    );

extern INT32 video_engine_next_preload(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const CHAR*                     ps_file_name      /* in  */
                    );

#if defined(_MMP_VERC_PLAY_THUMB_SUPPORT)
extern INT32 video_engine_thumb_load(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_FP_THUMB_COORDS_T           e_thumb_coord,    /* in  */
                    const GL_RECT_T*                pt_thumb_rect     /* in  */
                    );

extern INT32 video_engine_thumb_load_ex(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_FP_THUMB_COORDS_T           e_thumb_coord,    /* in  */
                    const GL_RECT_T*                pt_thumb_rect,    /* in  */
                    MMP_VE_DIVX_CERT_PTR_T          pt_divx_cert      /* out */
                    );

extern INT32 video_engine_thumb_next(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_FP_THUMB_COORDS_T           e_thumb_coord,    /* in  */
                    const GL_RECT_T*                pt_thumb_rect     /* in  */
                    );

extern INT32 video_engine_thumb_next_ex(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_FP_THUMB_COORDS_T           e_thumb_coord,    /* in  */
                    const GL_RECT_T*                pt_thumb_rect,    /* in  */
                    MMP_VE_DIVX_CERT_PTR_T          pt_divx_cert      /* out */
                    );

extern INT32 video_engine_thumb_stop(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_thumb_show(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_thumb_hide(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );
#endif

#if defined(_MMP_VERC_PLAY_COVER_SUPPORT)
extern INT32 video_engine_cover_load(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const GL_RECT_T*                pt_rect,          /* in  */
                    MMP_FP_THUMB_COORDS_T           e_coord           /* in  */
                    );

extern INT32 video_engine_cover_stop(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_has_cover_pic(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
                    BOOL*                           pb_value
                    );

extern INT32 video_engine_cover_load_image_template(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const GL_RECT_T*                pt_rect,          /* in  */
                    MMP_FP_THUMB_COORDS_T           e_coord,           /* in  */
                    MMP_UTIL_IMG_TPL_INFO_T         * pt_info
                    );

extern  INT32 video_engine_get_cover_pic_size(MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
                                   UINT32                          *pui4_w,
                                   UINT32                          *pui4_h);
extern INT32 video_engine_file_cover_load(
                    CHAR*                           ps_elmt_name,     /* in  */
                    const GL_RECT_T*                pt_rect,          /* in  */
                    MMP_FP_THUMB_COORDS_T           e_coord           /* in  */
                    );
extern  INT32 video_engine_file_has_cover_pic(CHAR*         ps_elmt_name,
                                                    BOOL         *pb_value);

#endif
extern INT32 video_engine_preview_activate(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const MMP_FP_PREVIEW_INFO_T*    pt_preview_info   /* in  */
                    );

extern INT32 video_engine_preview_inactivate(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_close(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_attr_set(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    UINT32                          ui4_attr_size,    /* in  */
                    const MMP_FP_SHOW_ATTR_T        at_show_attr[]    /* in  */
                    );

extern INT32 video_engine_next_attr_set(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    UINT32                          ui4_attr_size,    /* in  */
                    const MMP_FP_SHOW_ATTR_T        at_show_attr[]    /* in  */
                    );

extern INT32 video_engine_play(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_DIVX_CERT_PTR_T          pt_divx_cert      /* out */
                    );

extern INT32 video_engine_next(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_DIVX_CERT_PTR_T          pt_divx_cert      /* out */
                    );

extern INT32 video_engine_pause(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_blank(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_fast_forward(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_FAST_FWD_TYPE_T          e_fast_fwd_type   /* in  */
                    );

extern INT32 video_engine_fast_rewind(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_FAST_RWD_TYPE_T          e_fast_rwd_type   /* in  */
                    );

extern INT32 video_engine_slow_forward(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_SLOW_FWD_TYPE_T          e_slow_fwd_type   /* in  */
                    );

extern INT32 video_engine_slow_rewind(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_SLOW_RWD_TYPE_T          e_slow_rwd_type   /* in  */
                    );

extern INT32 video_engine_step(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_stop(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_stop_lyric(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern BOOL  video_engine_trick_enable(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );
extern BOOL video_engine_trick_enable_ex(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
                    MM_SPEED_TYPE_T*                pe_speed
                    );

extern BOOL  video_engine_seek_enable(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_seek(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    UINT32                          ui4_time_ofs      /* in  */
                    );

extern INT32 video_engine_seek_ex(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_POS_TYPE_T               t_pos_type,       /* in  */
                    UINT32                          ui4_time_ofs      /* in  */
                    );

extern INT32 video_engine_get_progress(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    UINT8*                          pui1_prog_pct     /* out */
                    );

extern INT32 video_engine_get_position(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_POS_TYPE_T               t_pos_type,       /* in  */
                    UINT64*                         pui8_pos_val      /* out */
                    );

extern INT32 video_engine_get_duration(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_DUR_TYPE_T               t_dur_type,       /* in  */
                    UINT64*                         pui8_dur_val      /* out */
                    );

extern INT32 video_engine_get_lyric_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    SVC_MM_SBTL_LYRIC_INFO_T*       pt_lyric_info      /* out */
                    );


extern INT32 video_engine_get_vid_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_VID_INFO_PTR_T           pt_vid_info       /* out */
                    );

extern INT32 video_engine_get_drm_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_DIVX_CERT_PTR_T          pt_drm_info       /* out */
                    );

extern INT32 video_engine_get_aud_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_AUD_INFO_PTR_T           pt_aud_info       /* out */
                    );

extern INT32 video_engine_get_chn_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_CHN_INFO_PTR_T           pt_chn_info       /* out */
                    );

#ifdef APP_MMP_PVR_AUDIO_SWITCH_CUST_RULE
extern INT32 video_engine_get_aud_mode(
					SCC_AUD_MODE_TYPE_T 			e_aud_type, 	  /*in */
					UINT32*							pui4_aud_mode	  /* out */
                    );

extern INT32 video_engine_set_aud_mode(
					SCC_AUD_MODE_TYPE_T 			e_aud_type, 	  /*in */
					UINT32							ui4_aud_mode	  /* in */
                    );
#else
extern INT32 video_engine_get_aud_mode(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    SCC_AUD_DOWNMIX_MODE_T*         pe_aud_mode       /* out */
                    );

extern INT32 video_engine_set_aud_mode(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    SCC_AUD_DOWNMIX_MODE_T          e_aud_mode        /* out */
                    );
#endif

#ifndef APP_MMP_SUBTITLE_CUSTOMER_SUPPORT
extern INT32 video_engine_get_sub_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_SUB_INFO_PTR_T           pt_sub_info       /* out */
                    );
#endif

extern INT32 video_engine_set_sub_attr(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_SBTL_ATTR_PTR_T          pt_sbtl_attr      /* in  */
                    );

extern INT32 video_engine_get_dtl_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_INFO_ID_T                e_info_id,        /* in  */
                    VOID*                           pv_buf,           /* in/out */
                    SIZE_T*                         pz_buf_len        /* in/out */
                    );

extern INT32 video_engine_get_next_dtl_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_INFO_ID_T                e_info_id,        /* in  */
                    VOID*                           pv_buf,           /* in/out */
                    SIZE_T*                         pz_buf_len        /* in/out */
                    );

extern INT32 video_engine_get_src_type(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    UINT8                           ui1_idx,          /* in  */
                    MMP_FILE_SRC_TYPE_T*            pt_file_src       /* out*/
                    );

extern INT32 video_engine_zoom(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_ZOOM_TYPE_T              e_zoom_type       /* in  */
                    );

extern INT32 video_engine_zoom_4sm(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_VID_INFO_PTR_T           pt_vid_info       /* in  */
                    );

extern INT32 video_engine_zoom_reset(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_zoom_reset_4sm(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_square_pixel(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 video_engine_square_pixel_4sm(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const GL_SIZE_T*                pt_video_size     /* in  */
                    );

extern INT32 video_engine_square_pixel_by_overscan_ratio(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const GL_SIZE_T*                pt_video_size,    /* in  */
                    UINT32                          ui4_ratio_x,      /* in  */ /* ex. 25 = 0.025% */
                    UINT32                          ui4_ratio_y,      /* in  */ /* ex. 25 = 0.025% */
                    BOOL*                           pb_adjusted       /* out */
                    );

extern INT32 video_engine_mts(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_AUD_INFO_PTR_T           pt_aud_info       /* in  */
                    );

#ifndef APP_MMP_SUBTITLE_CUSTOMER_SUPPORT
extern INT32 video_engine_sub(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_SUB_INFO_PTR_T           pt_sub_info       /* out */
                    );
#endif

extern INT32 video_engine_repeat(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MM_SVC_REPEAT_TYPE_T            e_rpt_type        /* in  */
                    );

extern MMP_VE_PLAY_STAT_T video_engine_get_state(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern VOID video_engine_set_state(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_PLAY_STAT_T              e_stat            /* in  */
                    );
#ifdef APP_TWN_SUPPORT
extern INT32 video_engine_get_sbtl_state(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );
#endif
extern INT32 video_engine_set_ctnt_repeat(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_CTNT_RPT_TYPE_T          e_ctnt_rpt        /* in  */
                    );

extern INT32 video_engine_get_ctnt_repeat(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_CTNT_RPT_TYPE_T*         pe_ctnt_rpt       /* out */
                    );

extern INT32 video_engine_set_screen_mode(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    SCC_VID_SCREEN_MODE_T           e_scr_mode        /* in  */
                    );

extern INT32 video_engine_get_screen_mode(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    SCC_VID_SCREEN_MODE_T*          pe_scr_mode       /* out */
                    );

extern INT32 video_engine_set_sub_plane(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    HANDLE_T                        h_sub_plane       /* in  */
                    );
extern INT32 video_engine_get_program_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,      /* in  */
                    MMP_VE_PROGRAM_INFO_PTR_T       pt_prog_info);    /* out*/

extern INT32 video_engine_set_language(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    ISO_639_LANG_T                  e_language        /* in */
                    );
#ifdef APP_MMP_ID3_SUPPORT
extern INT32 video_engine_set_id3_encode(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MM_SBTL_ID3_ENC_T               e_type        /* in */
                    );
#endif
extern INT32 mmp_ve_info_open(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const CHAR*                     ps_inf_name,      /* in  */
                    mmp_fp_info_nfy_fct             pf_inf_nfy,       /* in  */
                    VOID*                           pv_nfy_tag,       /* in  */
                    MMP_VE_INFO_INST_PTR_T*         ppt_info_inst     /* out */
                    );

extern INT32 mmp_ve_info_close(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_INFO_INST_PTR_T          pt_info_inst      /* in  */
                    );

extern INT32 mmp_ve_info_get(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_INFO_INST_PTR_T          pt_info_inst,     /* in  */
                    MMP_FP_INFO_TYPE_T              e_inf_type,       /* in  */
                    SIZE_T*                         pz_size,          /* out */
                    UTF16_T *                           pv_buf            /* out */
                    );

extern INT32 mmp_ve_info_set(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_INFO_INST_PTR_T          pt_info_inst,     /* in  */
                    MMP_FP_INFO_TYPE_T              e_inf_type,       /* in  */
                    SIZE_T*                         pz_size,          /* in  */
                    UINT8*                          pui1_buf          /* in  */
                    );

extern INT32 mmp_ve_info_cmd_do(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_INFO_INST_PTR_T          pt_info_inst,     /* in  */
                    MMP_FP_INFO_CMD_ID_T            e_inf_cmd,
                    VOID*                           pv_cmd_para
                    );

extern INT32 mmp_ve_info_cmd_res_init(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 mmp_ve_info_cmd_res_reset(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );

extern INT32 mmp_ve_info_cmd_res_deinit(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    );
extern INT32 video_engine_program_select(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,      /* in  */
                    UINT32                          ui4_prog_idx);     /*  in  */

extern VOID video_engine_sbtl_show_hide(
					MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
					BOOL 							b_is_show);

extern INT32 video_engine_get_resolution(
					MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
					UINT32* 						pt_u4_width,
					UINT32*						    pt_u4_height);

extern INT32 video_engine_unblock_svc(
					MMP_VE_PLAY_INST_PTR_T          pt_play_inst);

extern INT32 video_engine_set_speed(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
                    SPLAYER_TrickSpeed_e                 e_speed);

extern INT32 video_engine_get_speed(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
                    SPLAYER_TrickSpeed_e*                pe_speed);

extern INT32 video_engine_start2play_cust(
  					MMP_VE_PLAY_INST_PTR_T          pt_play_inst,          /* in  */
                    MMP_VE_DIVX_CERT_PTR_T         pt_divx_cert      /* out */
                    );

#ifdef APP_LAST_MEMORY_SUPPORT
extern INT32 video_engine_save_video_playback_last_momory(
					MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
					);
#ifdef APP_MMP_PVR_LAST_MEMORY_SUPPORT
extern INT32 video_engine_before_pvr_play_get_lst_mem(CHAR*	ac_filepath);
extern INT32 video_engine_get_video_last_mem(
					MMP_VE_PLAY_INST_PTR_T			pt_play_inst,
					CHAR*							ac_filepath,
					APP_CFG_MM_STOP_INFO_T*         pt_stop_info
					);
extern INT32 video_engine_set_video_last_mem(
					MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
					CHAR* 							ac_filepath,
					BOOL							b_eos
					);
extern INT32 video_engine_get_video_path(
					CHAR*							ac_filepath
					);
#endif

#endif

extern INT32 video_engine_divx_cert_cust(
                     MMP_VE_PLAY_INST_PTR_T         pt_play_inst,          /* in  */
                     MMP_VE_DIVX_CERT_PTR_T         pt_divx_cert      /* out */
                    );
extern INT32 video_engine_full_stop_cust(
                    MMP_VE_PLAY_INST_PTR_T         pt_play_inst           /* in  */
                    );
extern INT32 video_engine_elmt_open_cust(
                    MMP_VE_PLAY_INST_PTR_T         pt_play_inst       /* in/out */
                    );
extern INT32 video_engine_elmt_close_cust(
                    MMP_VE_PLAY_INST_PTR_T         pt_play_inst
                    );
extern BOOL video_engine_strm_comp_filter(
                    UINT16                          ui2_num_recs,     /* in  */
                    UINT16                          ui2_idx,          /* in  */
                    const STREAM_COMP_ID_T*         pt_comp_id,       /* in  */
                    const SCDB_REC_T*               pt_scdb_rec,      /* in  */
                    VOID*                           pv_fltr_tag       /* in  */
                    );
extern VOID svctx_media_play_nfy_fct(
                    HANDLE_T                        h_ctx_hdl,        /* in  */
                    SVCTX_COND_T                    e_ctx_cond,       /* in  */
                    SVCTX_NTFY_CODE_T               e_nfy_code,       /* in  */
                    STREAM_TYPE_T                   e_stm_type,       /* in  */
                    VOID*                           pv_nfy_tag        /* in  */
                    );

extern MMP_VE_PLAY_INST_PTR_T video_engine_get_inst_by_idx(UINT32    ui4_inst_id);
extern INT32 video_engine_get_movie_info(APPL_SPLAYER_MOVIE_INFO_T *ptMovieInfo);
extern INT32 video_engine_get_music_info(APPL_SPLAYER_MUSIC_INFO_T *ptInfo);

#ifdef APP_LAST_MEMORY_SUPPORT
extern VOID video_engine_set_last_mem_audio_play_id(UINT16 ui2_audio_id);
extern UINT16 video_engine_get_last_mem_audio_play_id(VOID);
extern VOID video_engine_set_last_mem_subtitle_play_id(UINT16 ui2_sub_play_id);
extern UINT16 video_engine_get_last_mem_subtitle_play_id(VOID);
extern VOID video_engine_set_last_mem_audio_num(UINT16 ui2_num);
extern VOID video_engine_set_last_mem_sbtl_num(UINT16 ui2_num);

#endif




#endif /* _VIDEO_ENGINE_H_ */

