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
 * $RCSfile: mmp_photo_eng.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "c_gl.h"
#include "c_img.h"
#include "c_img_tfx.h"
#include "c_fm.h"
#include "c_dt.h"
#include "c_handle.h"
#include "u_wgl_rect.h"
#include "c_wgl.h"

#include "app_util/a_common.h"
#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp/util/mmp_util.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "mmp/mmp_mmc_device.h"
#include "mmp/file_filter/mmp_fid.h"
#include "mmp/photo_eng/mmp_photo_eng.h"
#include "res/mmp/photo_eng/mmp_photo_eng_rc.h"
#include "mmp/disp_res_ctrler/mmp_drc.h"
#include "res/app_util/config/a_cfg_custom.h"

#ifdef APP_3D_PHOTO_SUPPORT
#include "mmp/app/mmp_main.h"
#ifdef APP_MENU_MMP_COEXIST
#include "menu2/a_menu.h"
#endif
#endif

#include "mi_common.h"
#include "mi_mm.h"
#include "mi_aout.h"
#include "mi_disp.h"
#include "mi_osd.h"
#include "mi_os.h"
#include "mi_sys.h"
#include <sys/stat.h>
#include <dirent.h>
#include "mi_fs.h"

#include "../../res/mmp/gen/mmp_mmp_layout.h"
#include "../../res/mmp/thumbnailmode/mmp_thumbnailmode_rc.h"
#include "../browse_eng/mmp_browse_eng.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define DBG_INFO_DIRECT(fmt, args...) \
    do{                                                                     \
        if(0)                                                               \
        {                                                                   \
            fprintf(stderr,fmt,##args );                                    \
            fflush(stderr);                                                 \
        }                                                                   \
        else                                                                \
        {                                                                   \
            MMP_DBG_INFO((fmt, args));                                      \
        }                                                                   \
    }while(0)                                                               \




#define MMP_THMBNAILMODE_MAX_THUMBS  (9)
#define ALIGN_N(x,n)        ((x+(n-1)) & ~(n-1))


#define MMP_THUMBNAIL_DATA_MAX_SIZE     (640000)  //align 16


#undef DBG_ERROR
#define DBG_ERROR(_stmt)                DBG_LOG_PRINT(_stmt)

#undef DBG_TRACE
#define DBG_TRACE(_stmt)                DBG_LOG_PRINT(_stmt)



#define CHECK_MI_OSD_RET(RET,BEGIN)  \
    {   \
        if( RET != MI_OK)  \
        {   \
            if( BEGIN==TRUE )   \
            {   \
                MI_OSD_EndDraw();   \
            }   \
            DBG_LOG_PRINT(("\033[35m%s %d[ Check Ret Fail !! ]\033[m\n", __FUNCTION__, __LINE__));  \
            return FALSE;   \
        }   \
    }   \

static MI_BOOL _bIsMMModuleInit = FALSE;


//
#define MMP_PHOTO_USE_MI_MM_MODULE

////
////
////
////



typedef enum
{
    E_MI_OSD_COLOR_ALPHA_RED   = 0,    //R:255 G: 0   B:0   Alpha:128
    E_MI_OSD_COLOR_ALPHA_GREEN = 1,    //R:0   G: 255 B:0   Alpha:128
    E_MI_OSD_COLOR_ALPHA_BLUE  = 2,    //R:0   G: 0   B:255 Alpha:128
    E_MI_OSD_COLOR_YUV_WHITE   = 3,    //R:128 G: 0   B:128 Alpha:255
    E_MI_OSD_COLOR_YUV_BLACK   = 4,    //R:128 G: 255 B:128 Alpha:255
    E_MI_OSD_COLOR_ALPHA_WHITE = 5,    //R:255 G: 255 B:255 Alpha:128
    E_MI_OSD_COLOR_ZERO        = 0xFF  //R:0   G: 0   B:0   Alpha:0
} _MI_OSD_ColorIndex_e;


//thumbnail
#define MI_MM_THUMBNAIL_WIDTH    288
#define MI_MM_THUMBNAIL_HEIGHT   228
#define MI_MM_THUMBNAIL_DATA_COLOR_FMT   E_MI_MM_THUMBNAIL_COLOR_FMT_ARGB8888 //MI MM enum
static MI_S32 _s32NonCachedPoolId = -1;




/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define _MMP_PE_EXIF_DATE_SIZE              ((UINT32) 20) /*EXIF2.0 spec: including null character*/
#define _MMP_PE_EXIF_DATE_FMT               "YYYY:MM:DD hh:mm:ss"   /*EXIF2.0 spec: YYYY:MM:DD HH:MM:SS*/
#define _MMP_PE_PHOTO_PLAY_ATTR_COUNT       ((UINT32) 2)

#define _MMP_PE_DISPLAY_RES_MAX_COUNT       ((UINT8) 4)
#define _MMP_PE_IMAGE_FILE_MAX_COUNT        ((UINT8) 2)
#define _MMP_PE_THUMB_DISP_RES_COUNT        ((UINT8) 2)
#define _MMP_PE_DISPLAY_RES_IDX_NULL        ((UINT8) 0xFF)
#define _MMP_PE_IMG_IDX_NULL                ((UINT8) 0xFF)
#define _MMP_PE_ACCURACY_CONST              ((UINT32)10000)
#define _MMP_PE_ZOOM_SQRT_ACCURACY          ((UINT64)1000000)
#define _MMP_PE_ZOOM_ACCURACY               ((UINT32)1000)
#define _MMP_PE_INFO_VER_INVALID            ((UINT32)0)
#define _MMP_PE_LOAD_VER_INVALID            ((UINT32)0)

#ifndef APP_SUPPORT_FULL_3D_PHOTO
#ifndef APP_PHOTO_FHD_SCALE_4K2K
#ifndef APP_PHOTO_FHD_AS_4K2K
#define APP_PHOTO_FHD_AS_4K2K
#endif
#endif
#endif
typedef enum __MMP_PE_ROTATE_GROUP_T
{
    _MMP_PE_ROTATE_GROUP_0 = 0,             /*0, 180 without flip*/
    _MMP_PE_ROTATE_GROUP_1,                 /*90, 270 without flip*/
    _MMP_PE_ROTATE_GROUP_2,                 /*0, 180 with flip*/
    _MMP_PE_ROTATE_GROUP_3,                 /*90, 270 with flip*/
} _MMP_PE_ROTATE_GROUP_T;

#define _MMP_PE_DISP_RES_RESET(_t_disp)                         \
{                                                               \
    (_t_disp).e_rotate = IMG_ROTATE_CLOCKWS_0_OP_TYPE;          \
    (_t_disp).t_center_offset.i4_x = 0;                         \
    (_t_disp).t_center_offset.i4_y = 0;                         \
    (_t_disp).ui4_scale = 1;                                    \
    (_t_disp).ui4_x = 0;                                        \
    (_t_disp).ui4_y = 0;                                        \
    (_t_disp).ui4_w = 0;                                        \
    (_t_disp).ui4_h = 0;                                        \
    (_t_disp).ui1_flag = 0;                                     \
}

#define _MMP_PE_ZERO_COLOR(_t_clr, _ui1_aplha)                  \
{                                                               \
    (_t_clr).a = (_ui1_aplha);                                  \
    (_t_clr).u1.y = MMP_PE_RC_DEF_BK_Y;                         \
    (_t_clr).u2.u = MMP_PE_RC_DEF_BK_U;                         \
    (_t_clr).u3.v = MMP_PE_RC_DEF_BK_V;                         \
}

#define _MMP_PE_WORKING_BUF_ID_T            UINT8
#define _MMP_PE_WORKING_BUF_ID_SRC          ((_MMP_PE_WORKING_BUF_ID_T) 0)
#define _MMP_PE_WORKING_BUF_ID_WORK_1       ((_MMP_PE_WORKING_BUF_ID_T) 1)
#define _MMP_PE_WORKING_BUF_ID_WORK_2       ((_MMP_PE_WORKING_BUF_ID_T) 2)
#if 0 //#ifdef APP_SUPPORT_4K2K
#define _MMP_PE_WORKING_BUF_ID_WORK_3       ((_MMP_PE_WORKING_BUF_ID_T) 3)
#define _MMP_PE_WORKING_BUF_ID_TOTAL        ((_MMP_PE_WORKING_BUF_ID_T) 4)
#else
#define _MMP_PE_WORKING_BUF_ID_TOTAL        ((_MMP_PE_WORKING_BUF_ID_T) 3)
#endif
#define _MMP_PE_WORKING_BUF_ID_NULL         ((_MMP_PE_WORKING_BUF_ID_T) 0xFF)

typedef struct __MMP_PE_WORKING_BUF_T
{
    _MMP_PE_WORKING_BUF_ID_T    e_match_id;
    MMP_DRC_BUF_T*              at_buf[_MMP_PE_WORKING_BUF_ID_TOTAL];
} _MMP_PE_WORKING_BUF_T;

#if 0 //#ifdef APP_SUPPORT_4K2K
#define _MMP_PE_WORKING_BUF_RESET(_t_buf)                                           \
{                                                                                   \
    (_t_buf).e_match_id = _MMP_PE_WORKING_BUF_ID_NULL;                              \
    (_t_buf).at_buf[_MMP_PE_WORKING_BUF_ID_SRC]    = NULL;                          \
    (_t_buf).at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1] = NULL;                          \
    (_t_buf).at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = NULL;                          \
    (_t_buf).at_buf[_MMP_PE_WORKING_BUF_ID_WORK_3] = NULL;                          \
}
#else
#define _MMP_PE_WORKING_BUF_RESET(_t_buf)                                           \
{                                                                                   \
    (_t_buf).e_match_id = _MMP_PE_WORKING_BUF_ID_NULL;                              \
    (_t_buf).at_buf[_MMP_PE_WORKING_BUF_ID_SRC]    = NULL;                          \
    (_t_buf).at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1] = NULL;                          \
    (_t_buf).at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = NULL;                          \
}
#endif

/*flag for information instance*/
#define _MMP_PE_INFO_FLAG_LOADING           ((UINT8) 0x01)
#define _MMP_PE_INFO_FLAG_CORRUPT           ((UINT8) 0x02)
#define _MMP_PE_INFO_FLAG_FROM_MAIN         ((UINT8) 0x04)

#define _MMP_PE_THUMB_BUF_ID_T              UINT8
#define _MMP_PE_THUMB_BUF_ID_SHOW           ((_MMP_PE_THUMB_BUF_ID_T) 0)
#define _MMP_PE_THUMB_BUF_ID_LOAD           ((_MMP_PE_THUMB_BUF_ID_T) 1)


#define _MMP_PE_INFO_INST_RESET(_t_info)                        \
{                                                               \
    c_memset(&(_t_info), 0, sizeof(_MMP_PE_INFO_INST_T));       \
    (_t_info).t_path = MMP_FID_NULL_REC_IDX;                    \
}

#define _MMP_PE_IS_JPG_PROGRESSIVE(ui2_flag)     (((ui2_flag) & _MMP_PE_IMG_FLAG_PROGRESSIVE_FILE) ? TRUE : FALSE)
#define _MMP_PE_INFO_FILE_INFO_FIELD            UINT16
#define _MMP_PE_INFO_FILE_INFO_FIELD_EMPTY      ((_MMP_PE_INFO_FILE_INFO_FIELD) 0x0000)
#define _MMP_PE_INFO_FILE_INFO_FIELD_CREATE     ((_MMP_PE_INFO_FILE_INFO_FIELD) 0x0001)
#define _MMP_PE_INFO_FILE_INFO_FIELD_MODIFY     ((_MMP_PE_INFO_FILE_INFO_FIELD) 0x0002)
#define _MMP_PE_INFO_FILE_INFO_FIELD_PROTECT    ((_MMP_PE_INFO_FILE_INFO_FIELD) 0x0004)
#define _MMP_PE_INFO_FILE_INFO_FIELD_SIZE       ((_MMP_PE_INFO_FILE_INFO_FIELD) 0x0008)

#define  _PE_OFFSET_X                           ((UINT32) 200)
#define  _PE_OFFSET_Y                           ((UINT32) 0)

typedef struct __MMP_PE_INFO_FILE_INFO_T
{
    TIME_T                      ui8_create_time;
    TIME_T                      ui8_modify_time;
    UINT64                      ui8_size;
    BOOL                        b_protect;

    _MMP_PE_INFO_FILE_INFO_FIELD ui2_field;
} _MMP_PE_INFO_FILE_INFO_T;

typedef struct __MMP_PE_INFO_INST_T
{
    _MMP_PE_INFO_FILE_INFO_T    t_file_info;
    GL_RECT_T                   t_thumb_rect;
    GL_RECT_T                   t_boundary_rect;
    HANDLE_T                    h_img;                          /*image handle*/
    mmp_fp_info_nfy_fct         pf_info_nfy;
    VOID*                       pv_info_nfy_tag;
    SIZE_T                      z_img_w;
    SIZE_T                      z_img_h;
    UINT32                      ui4_ver;
    UINT32                      ui4_crnt_load_ver;
    FID_T                       t_path;
    UINT8                       ui1_flag;
    IMG_ROTATE_OP_TYPE_T        e_rotate;
    MMP_FP_LOAD_IMG_ROTATE_OP_T e_rotate_op;
    IMG_TYPE_T                  e_img_type;
} _MMP_PE_INFO_INST_T;

/*flag for image file*/
#define _MMP_PE_IMG_FLAG_ROTATE_FROM_FILE   ((UINT32) 0x00000001)
#define _MMP_PE_IMG_FLAG_IMG_CORRUPT        ((UINT32) 0x00000002)
#define _MMP_PE_IMG_FLAG_IMG_LOADING        ((UINT32) 0x00000004)
#define _MMP_PE_IMG_FLAG_IMG_DURING_EFFECT  ((UINT32) 0x00000008)
#define _MMP_PE_IMG_FLAG_IMG_SCALED         ((UINT32) 0x00000010)
#define _MMP_PE_IMG_FLAG_IMG_LOADING_SUSPEND    ((UINT32) 0x00000020)
#define _MMP_PE_IMG_FLAG_IMG_ROTATING       ((UINT32) 0x00000040)
#define _MMP_PE_IMG_FLAG_IMG_ZOOMING        ((UINT32) 0x00000080)
#define _MMP_PE_IMG_FLAG_MEM_FILE           ((UINT32) 0x00000100)
#define _MMP_PE_IMG_FLAG_BAD_FILE           ((UINT32) 0x00000200)
#define _MMP_PE_IMG_FLAG_NOT_SUPPORT_FILE   ((UINT32) 0x00000400)
#define _MMP_PE_IMG_FLAG_THUMB_LOADING      ((UINT32) 0x00000800)
#define _MMP_PE_IMG_FLAG_WITH_THUMB         ((UINT32) 0x00001000)
#define _MMP_PE_IMG_FLAG_PROGRESSIVE_FILE   ((UINT32) 0x00002000)
#define _MMP_PE_IMG_FLAG_FILE_REMOVED       ((UINT32) 0x00004000)
#define _MMP_PE_IMG_FLAG_INFO_THUM_DCDING   ((UINT32) 0x00008000)/*decoding file info page thumbnail*/
#define _MMP_PE_IMG_FLAG_FILE_NOT_EXIST     ((UINT32) 0x00010000)
#define _MMP_PE_IMG_FLAG_DLNA_SERVER_OFF    ((UINT32) 0x00020000)
#define _MMP_PE_IMG_FLAG_PER_DENY           ((UINT32) 0x00040000)
#define _MMP_PE_IMG_FLAG_ANIMATION_GIF_PREVIEW_BUF  ((UINT32) 0x00080000)
#define _MMP_PE_IMG_FLAG_MPO_3D_OFF         ((UINT32) 0x00100000)
#define _MMP_PE_IMG_FLAG_MPO_3D_ON         ((UINT32) 0x00200000)



#ifdef _MMP_DEBUG_FILENAME
    #define _MMP_DECLARE_FILENAME()         CHAR    ac_name_buf[MMP_RC_PATH_MAX_LEN];

    #define _MMP_DECLARE_STORE_NAME(_pt_this, _ps_name)         \
    {                                                           \
        c_strcpy((_pt_this)->ac_name_buf, _ps_name);            \
    }
#else
    #define _MMP_DECLARE_FILENAME()
    #define _MMP_DECLARE_STORE_NAME(_pt_this, _ps_name)         \
    {                                                           \
    }
#endif

typedef enum __MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_T
{
    _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_CORRUPT = 0,
    _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_BAD,
    _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_NOT_EXIST,
    _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_DLNA_SERVER_OFF,
    _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_PER_DENY
} _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_T;

#ifdef APP_3D_PHOTO_SUPPORT
typedef struct _CROP_RECT_T
{
    UINT32  ui4_left_offset;
    UINT32  ui4_right_offset;
    UINT32  ui4_top_offset;
    UINT32  ui4_bottom_offset;
}CROP_RECT_T;
#endif

typedef struct __MMP_PE_IMG_FILE_T
{
    _MMP_PE_INFO_FILE_INFO_T    t_file_info;
    GL_RECT_T                   t_thumb_rect;                   /*rectangle for disaply thumbnail*/
    HANDLE_T                    h_img;                          /*image handle*/
    HANDLE_T                    h_tfx;                          /*effect handle*/
    SIZE_T                      z_img_w;
    SIZE_T                      z_img_h;
    SIZE_T                      z_thumb_rect_w;
    SIZE_T                      z_thumb_rect_h;
    INT32                       i4_info_thumb_left;
    INT32                       i4_info_thumb_top;
    IMG_ROTATE_OP_TYPE_T        e_rotate;                       /*rotation of this image*/
    MMP_FP_LOAD_IMG_ROTATE_OP_T e_force_rotate_op;
    GL_POINT_T                  t_center_offset;
    UINT32                      ui4_crnt_load_ver;
    UINT32                      ui4_zoom;                       /*zoom of this image*/
    UINT32                      ui4_duration;                   /*duration of this image*/
    MMP_EFFECT_T                t_effect;                       /*effect of this image*/
    _MMP_PE_WORKING_BUF_T       t_working_buf;
    FID_T                       t_path;
    UINT32                      ui2_flag;
    IMG_TYPE_T                  e_img_type;
    GL_RECT_T                   t_file_page_thumb_rect;         /*rectangle for disaply thumbnail in file info page*/
    MMP_DRC_BUF_T*              pt_buf_file_thumb;
    BOOL                        b_animation_gif;
    MMP_DRC_BUF_T*              pt_buf_animation_gif;
#ifdef APP_3D_PHOTO_SUPPORT
    CROP_RECT_T                 t_surface_crop_rect;
    CROP_RECT_T                 t_surface_crop_rect_mpo;
    _MMP_PE_WORKING_BUF_ID_T    e_slideshow_id;
#endif
#ifdef APP_MENU_MMP_COEXIST
    BOOL                        b_3d_disable;
#endif
#ifdef APP_SUPPORT_4K2K
    BOOL                        b_is_4k2k_photo;
#endif

    BOOL                        b_first_photo;
    _MMP_DECLARE_FILENAME()
    GL_RECT_T                   t_disp_rect;
    MMP_DRC_BUF_T*              pt_buf_effect;
} _MMP_PE_IMG_FILE_T;

#define MI_MM_PHOTO_HANDLE              "MI_MM_HANDLE_IDX_0"
#define MI_MM_PHOTO_THUMBNAIL_HANDLE    "MI_MM_HANDLE_IDX_1"




typedef struct __MMP_PE_REQ_PARAM_MEM_OPEN_T
{
    const UINT8*                pui1_buf;
    SIZE_T                      z_buf_size;
    mmp_pe_play_nfy_fct         pf_nfy;
    VOID*                       pv_tag;
    UINT32                      ui4_ver;
} _MMP_PE_REQ_PARAM_MEM_OPEN_T;

typedef enum __MMP_PE_REQ_ID_T
{
    _MMP_PE_REQ_ID_OPEN = 0,
    _MMP_PE_REQ_ID_MEM_OPEN,
    _MMP_PE_REQ_ID_CLOSE,
    _MMP_PE_REQ_ID_ATTR_SET,
    _MMP_PE_REQ_ID_NEXT_PRELOAD,
    _MMP_PE_REQ_ID_NEXT_MEM_PRELOAD,
    _MMP_PE_REQ_ID_NEXT_ATTR_SET,
    _MMP_PE_REQ_ID_SHOW,
    _MMP_PE_REQ_ID_PLAY,
    _MMP_PE_REQ_ID_CLEAN,
    _MMP_PE_REQ_ID_NEXT,
    _MMP_PE_REQ_ID_GET_FILE,
    _MMP_PE_REQ_ID_GET_SURF,
    _MMP_PE_REQ_ID_ROTATE,
    _MMP_PE_REQ_ID_INFO_THUM,
    _MMP_PE_REQ_ID_STOP,
    _MMP_PE_REQ_ID_PAUSE,
    _MMP_PE_REQ_ID_LAST_ENTRY      /*NOT USED*/
} _MMP_PE_REQ_ID_T;

typedef struct __MMP_PE_REQ_WINDOW_T
{
    HANDLE_T                    h_ready_signal;
    VOID*                       apv_param[5];
    _MMP_PE_REQ_ID_T            e_id;
    INT32                       i4_ret;
} _MMP_PE_REQ_WINDOW_T;

/*flag for photo engine*/
#define _MMP_PE_FLAG_QUICK_ROTATE           ((UINT32) 0x00000001)
#define _MMP_PE_FLAG_INIT_READY             ((UINT32) 0x00000002)
#define _MMP_PE_FLAG_PLAY_DISP_RESUMED      ((UINT32) 0x00000004)
#define _MMP_PE_FLAG_FILE_NEXTING           ((UINT32) 0x00000008)
#define _MMP_PE_FLAG_NEXT_IS_PLAY           ((UINT32) 0x00000010)
#define _MMP_PE_FLAG_THUMB_DISP_RESUMED     ((UINT32) 0x00000020)
#define _MMP_PE_FLAG_SCREEN_LINKED          ((UINT32) 0x00000040)
#define _MMP_PE_FLAG_NO_MAIN_THUMB          ((UINT32) 0x00000080)
#define _MMP_PE_FLAG_SHOW_THUMB_AS_NEXT     ((UINT32) 0x00000100)
#define _MMP_PE_FLAG_LIMIT_INFO_READY       ((UINT32) 0x00000200)
#define _MMP_PE_FLAG_FULL_DECODING          ((UINT32) 0x00000400)
#define _MMP_PE_FLAG_PREVIEW_MODE           ((UINT32) 0x00000800)
#define _MMP_PE_FLAG_ANIMATION_GIF_NEED_CLEAN   ((UINT32) 0x00001000)
#define _MMP_PE_FLAG_OSD_PLANE_3_SET_BLACK      ((UINT32) 0x00002000)
#define _MMP_PE_FLAG_IS_PLAYING_ZOOM_ROTATE     ((UINT32) 0x00004000)



#define _MMP_PE_NEW_LOAD_VER(_pt_this)                          \
{                                                               \
    (_pt_this)->ui4_load_ver++;                                 \
    if(_MMP_PE_LOAD_VER_INVALID == (_pt_this)->ui4_load_ver)    \
    {                                                           \
        (_pt_this)->ui4_load_ver++;                             \
    }                                                           \
}

#define _MMP_PE_SET_LOAD_VER_INVALID(_ui4_ver)                  \
{                                                               \
    (_ui4_ver) = _MMP_PE_LOAD_VER_INVALID;                      \
}

#define _MMP_PE_IS_LIMIT_INFO_READY(_pt_this)                   \
(                                                               \
    (_MMP_PE_FLAG_LIMIT_INFO_READY & (_pt_this)->ui4_flag) ? TRUE : FALSE    \
)

#define _MMP_PE_SET_LIMIT_INFO_READY(_pt_this)                  \
{                                                               \
    (_pt_this)->ui4_flag |= _MMP_PE_FLAG_LIMIT_INFO_READY;      \
}

#define _MMP_PE_GET_ROTATE_TYPE_FROM_OP(_e_rotate_op, _e_rotate)     \
{                                                                    \
    switch (_e_rotate_op)                                            \
    {                                                                \
        case MMP_FP_LOAD_IMG_ROTATE_OP_CLOCKWS_0:                    \
            (_e_rotate) = IMG_ROTATE_CLOCKWS_0_OP_TYPE;              \
            break;                                                   \
        case MMP_FP_LOAD_IMG_ROTATE_OP_CLOCKWS_90:                   \
            (_e_rotate) = IMG_ROTATE_CLOCKWS_90_OP_TYPE;             \
            break;                                                   \
        case MMP_FP_LOAD_IMG_ROTATE_OP_CLOCKWS_180:                  \
            (_e_rotate) = IMG_ROTATE_CLOCKWS_180_OP_TYPE;            \
            break;                                                   \
        case MMP_FP_LOAD_IMG_ROTATE_OP_CLOCKWS_270:                  \
            (_e_rotate) = IMG_ROTATE_CLOCKWS_270_OP_TYPE;            \
            break;                                                   \
        default:                                                     \
            break;                                                   \
    }                                                                \
}

typedef enum __MMP_PE_STATE_UPDATE_TYPE_T
{
    _MMP_PE_STATE_UPDATE_TYPE_VIEW = 0
} _MMP_PE_STATE_UPDATE_TYPE_T;

typedef struct __MMP_PHOTO_LIMIT_T
{
    UINT32  ui4_scale_max_width;
    UINT32  ui4_scale_min_width;
    UINT32  ui4_scale_max_height;
    UINT32  ui4_scale_min_height;

    BOOL    b_is_progressive_support;
} _MMP_PHOTO_LIMIT_T;






#define MI_MM_NAME_LENGTH  32
//#define MAX_FILE_PATH_LEN 255 ---> CID:4632295, incompatible redefinition in "app_util/splayer/splayer.h"

#undef CHECK_RET
#define CHECK_RET(RET, API)  \
    {   \
        if( RET != MI_OK)  \
        {   \
            DBG_LOG_PRINT(("[mmp] %s %d [Check Fun:<%s> Ret Fail! Ret=%d]\r\n", __FUNCTION__, __LINE__,API,RET));  \
        }   \
    }

typedef struct _MMP_SUR_SNAPSHOT_T
{
    GL_HSURFACE_T               h_surf;
    UINT32                      ui4_w;
    UINT32                      ui4_h;
} MMP_SUR_SNAPSHOT_T;



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#ifndef STATIC
#define STATIC      static
#endif
#ifndef ULONG
#define ULONG       unsigned long
#endif
#ifndef UCHAR
#define UCHAR       unsigned char
#endif
#ifndef DWORD
#define DWORD       unsigned int
#endif
#ifndef LPCTSTR
#define LPCTSTR     unsigned char *
#endif
#ifndef HFILE
#define HFILE       HANDLE
#endif


#define NUM_FORMATS     12

#define FMT_BYTE        1           //Format Byte
#define FMT_STRING      2
#define FMT_USHORT      3
#define FMT_ULONG       4
#define FMT_URATIONAL   5
#define FMT_SBYTE       6
#define FMT_UNDEFINED   7
#define FMT_SSHORT      8
#define FMT_SLONG       9
#define FMT_SRATIONAL  10
#define FMT_SINGLE     11
#define FMT_DOUBLE     12
//////////////////////////////////////////////////////////////////////////
#define MAX_SECTIONS   20       //JPG file max SECTION number

#ifndef M_SOI
#define M_SOF0  0xC0            // Start Of Frame N
#define M_SOF1  0xC1            // N indicates which compression process
#define M_SOF2  0xC2            // Only SOF0-SOF2 are now in common use
#define M_SOF3  0xC3
#define M_SOF5  0xC5            // NB: codes C4 and CC are NOT SOF markers
#define M_SOF6  0xC6
#define M_SOF7  0xC7
#define M_SOF9  0xC9
#define M_SOF10 0xCA
#define M_SOF11 0xCB
#define M_SOF13 0xCD
#define M_SOF14 0xCE
#define M_SOF15 0xCF
#define M_SOI   0xD8            // Start Of Image (beginning of datastream)
#define M_EOI   0xD9            // End Of Image (end of datastream)
#define M_SOS   0xDA            // Start Of Scan (begins compressed data)
#define M_JFIF  0xE0            // Jfif marker
#define M_EXIF  0xE1            // Exif marker
#define M_COM   0xFE            // COMment

//define APP simbol (SECTION)
#define M_APP0  0xE0
#define M_APP1  0xE1
#define M_APP2  0xE2
#define M_APP3  0xE3
#define M_APP4  0xE4
#define M_APP5  0xE5
#define M_APP6  0xE6
//...
#endif

// Describes tag values
//NOTE: the following define is Intel CPU (Little-Endian)  eg,  TAG_MAKE  addr0 == 0x0f  add1 == 0x01
#define TAG_MAKE              0x010F    //camera manufacturers
#define TAG_MODEL             0x0110    //DC module
#define TAG_ORIENTATION       0x0112    //shoot angle
#define TAG_XRESOLUTION       0x011A    //X resolution
#define TAG_YRESOLUTION       0x011B    //Y resolution
#define TAG_RESOLUTIONUNIT    0x0128    //resolution uint inch, cm
#define TAG_DATATIME          0x0132    //data
#define TAG_YBCR_POSITION     0x0213    //YCbCr position control£¬e.g  right
#define TAG_COPYRIGHT         0x8298    //lisent
#define TAG_EXIF_OFFSET       0x8769    //EXIF offset£¬== handle a new EXIF info

//
#define TAG_IMAGEWIDTH        0x0001    //image height
#define TAG_IMAGEHEIGHT       0x0101    //image width
//BOOKMARK
#define TAG_EXPOSURETIME      0x829A    //exposure time£¬e.g 1/30 second
#define TAG_FNUMBER           0x829D    //aperture  e.g F2.8
#define TAG_EXIF_VERSION      0x9000    //EXIF version info
#define TAG_DATETIME_ORIGINAL 0x9003    //photo shooting time e.g  2005-10-13 11:09:35
#define TAG_DATATIME_DIGITIZED 0x9004   //the time of photo by app modeifed , e.g 2005-10-13 11:36:35
#define TAG_COMPONCONFIG      0x9101    //ComponentsConfiguration color space config
#define TAG_COMPRESS_BIT      0x9202    //
#define TAG_SHUTTERSPEED      0x9201    //shutter speed£¬e.g 1/30 second
#define TAG_APERTURE          0x9202    //sperture value£¬e.g F2.8
#define TAG_BRIGHTNESS        0x9203    //brightness
#define TAG_EXPOSURE_BIAS     0x9204    //exposure compensation£¬e.gEV0.0
#define TAG_MAXAPERTURE       0x9205    //max aperture  e.g F2.8
#define TAG_SUBJECT_DISTANCE  0x9206    //
#define TAG_METERING_MODE     0x9207    //
#define TAG_WHITEBALANCE      0x9208    //LightSource white balance
#define TAG_FLASH             0x9209    //use flash light ?
#define TAG_FOCALLENGTH       0x920A    //f-number e.g 7.09mm
#define TAG_USERCOMMENT       0x9286    //user commont
#define TAG_MAKE_COMMENT      0x927C    //
#define TAG_SUBSECTIME        0x9290    //SubSecTime
#define TAG_SUBTIME_ORIGINAL  0x9291    //SubSecTimeOriginal
#define TAG_SUBTIME_DIGITIZED 0x9292    //SubSecTimeDigitized
#define TAG_FLASHPIXVERSION   0x00A0    //Flash Pix version
#define TAG_COLORSPACE        0x01A0    //color sapce£¬e.g sRGB

#define TAG_PIXEL_XDIMENSION  0x02A0    //
#define TAG_PIXEL_YDIMENSION  0x03A0    //
//EXIFR98

#define TAG_INTEROP_OFFSET    0xa005   //offset

#define TAG_FOCALPLANEXRES    0xA20E   //
#define TAG_FOCALPLANEYRES    0xA20F   //
#define TAG_FOCALPLANEUNITS   0xA210   //
#define TAG_EXIF_IMAGEWIDTH   0xA002   //EXIF width
#define TAG_EXIF_IMAGELENGTH  0xA003   //EXIF height

#define TAG_EXPOSURE_PROGRAM  0x8822   //
#define TAG_ISO_EQUIVALENT    0x8827   //
#define TAG_COMPRESSION_LEVEL 0x9102   //

#define TAG_THUMBNAIL_OFFSET  0x0201   //thumbnail offset
#define TAG_THUMBNAIL_LENGTH  0x0202   //thumbnail size


#define TAG_GPS_VERSIONID       0x0000 //
#define TAG_GPS_LATITUDEREF     0x0001 //
#define TAG_GPS_LATITUDE        0x0002 //
#define TAG_GPS_LONGITUDEREF    0x0003 //
#define TAG_GPS_LONGITUDE       0x0004 //
#define TAG_GPS_ALTITUDEREF     0x0005 //
#define TAG_GPS_ALTITUDE        0x0006 //
#define TAG_GPS_TIMESTAMP       0x0007 //
#define TAG_GPS_SATELLITES      0x0008 //
#define TAG_GPS_STATUS          0x0009 //
#define TAG_GPS_MEASUREMODE     0x000A //
#define TAG_GPS_DOP             0x000B //
#define TAG_GPS_SPEEDREF        0x000C //
#define TAG_GPS_SPEED           0x000D //
#define TAG_GPS_TRACKREF        0x000E //
#define TAG_GPS_TRACK           0x000F //
#define TAG_GPS_IMGDIRECTIONREF 0x0010 //
#define TAG_GPS_IMGDIRECTION    0x0011 //
#define TAG_GPS_MAPDATUM        0x0012 //
#define TAG_GPS_DESTLATITUDEREF 0x0013 //
#define TAG_GPS_DESTLATITUDE    0x0014 //
#define TAG_GPS_DESTLONGITUDEREF 0x0015//
#define TAG_GPS_DESTLONGITUDE   0x0016 //
#define TAG_GPS_DESTBEARINGREF  0x0017 //
#define TAG_GPS_DESTBEARING     0x0018 //
#define TAG_GPS_DESTDISTANCEREF 0x0019 //
#define TAG_GPS_DESTDISTANCE    0x001A //

// ASCII, UNICODE ....
typedef enum ECT{
    CT_ASCII = 0,
    CT_UNICODE,
    CT_JIS,
    CT_UNDEFINE
}COMMENT_TYPE;




//////////////////////////////////////////////////////////////////////////
typedef struct tag_Section_t{
    UCHAR    *Data;
    int      Type;
    unsigned int Size;
} Section_t;

//////////////////////////////////////////////////////////////////////////

STATIC _MMP_IMAGE_INFO* g_pImageInfo = 0; //
STATIC int m_MotorolaOrder   = 0; //
STATIC int m_ExifImageWidth  = 0; //

//////////////////////////////////////////////////////////////////////////

/* Describes format descriptor */
static const int m_BytesPerFormat[] = {0,1,1,2,4,8,1,1,2,4,8,4,8};

#if 0
//Get 16 bits motorola order (always) for jpeg header stuff.
#define EXIF_Get16m(Short)          ((((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1])

//Convert a 16 bit unsigned value from file's native unsigned char order
#define EXIF_Get16u(Short)          ((m_MotorolaOrder==0)?((((unsigned char *)(Short))[1] << 8) | ((unsigned char *)(Short))[0]):((((unsigned char *)(Short))[0] << 8) | ((unsigned char *)(Short))[1]))


//Convert a 32 bit signed value from file's native unsigned char order
#define EXIF_Get32s(Long)           ((m_MotorolaOrder==0)?\
                                    (((( char *)(Long))[0] << 24) | (((unsigned char *)(Long))[1] << 16) | (((unsigned char *)(Long))[2] << 8 ) | (((unsigned char *)(Long))[3] << 0 )):\
                                    (((( char *)(Long))[3] << 24) | (((unsigned char *)(Long))[2] << 16) | (((unsigned char *)(Long))[1] << 8 ) | (((unsigned char *)(Long))[0] << 0 )))

//Convert a 32 bit unsigned value from file's native unsigned char order
#define EXIF_Get32u(Long)           ((unsigned long)EXIF_Get32s(Long) & 0XFFFFFFFF)
#endif
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


typedef struct __MMP_PE_DATA_MEMBER_T
{
    _MMP_PE_INFO_INST_T         at_info_inst[MMP_PE_RC_INFO_INST_MAX_COUNT];
    MMP_DRC_BUF_T*              pt_buf_thumb_show;
    MMP_DRC_BUF_T*              pt_buf_thumb_load;
    _MMP_PE_IMG_FILE_T          at_img[_MMP_PE_IMAGE_FILE_MAX_COUNT];
    GL_POINT_T                  t_screen_offset;
    GL_RECT_T                   t_thumb_rect;                   /*rectangle for disaply thumbnail*/
    GL_RECT_T                   t_prew_rect;
    _MMP_PHOTO_LIMIT_T          t_limit;
    GL_HSCREEN_T                h_screen;
    GL_HPLANE_T                 h_plane;
    //X++
    HANDLE_T                    h_plane_canvas; //thumbnail/vdp(video player) osd /plane

    HANDLE_T                    h_play_timer;
    MMP_PLAY_STATE_T            e_state;
    mmp_pe_play_nfy_fct         pf_play_nfy;
    VOID*                       pv_play_nfy_tag;
    UINT32                      ui4_disp_count;
    UINT32                      ui4_play_ver;
    UINT32                      ui4_info_ver;
    UINT32                      ui4_load_ver;
    UINT32                      ui4_flag;
    UINT16                      ui2_screen_w;
    UINT16                      ui2_screen_h;
    UINT16                      ui2_canvas_w;
    UINT16                      ui2_canvas_h;
    UINT8                       ui1_crnt_img;
    MMP_DRC_BUF_T*              pt_buf_crnt_disp;
    MMP_DRC_BUF_T*              pt_buf_crnt_disp_bkp;
    INT8                        i1_img_z_order;
    INT8                        i1_thumb_z_order;
#ifdef APP_SUPPORT_4K2K
    UINT8                       ui1_prev_photo_is_4k2k;
#endif
    UINT16                      ui2_icl_id_3d;
    GL_RECT_T                   t_nexting_thumb_rect;
    //
    _MMP_IMAGE_INFO             t_image_info;

#ifdef MMP_PHOTO_USE_MI_MM_MODULE
    //mi_mm ++
    MI_HANDLE                   h_MI_MM_Hdl;
    MI_HANDLE                   h_Disp_Hdl;
#endif
    GL_HPLANE_T                 h_thumbnail_plane;
    GL_HVIEW_T                  h_thumbnail_view;    /*view handle*/
    GL_HSURFACE_T               h_thumbnail_surf;
    UINT32                      ui4_thumbanil_viewport;
    UINT32                      ui4_thumbanil_canvas_w;
    UINT32                      ui4_thumbanil_canvas_h;
    MMP_SUR_SNAPSHOT_T          st_snapshot;

    UINT8*                      p_thumbnail_data;
    UINT8*                      p_thumbnail_rotate_data;

} _MMP_PE_DATA_MEMBER_T;

/*-----------------------------------------------------------------------------
 * customization declarations
 *---------------------------------------------------------------------------*/
#ifndef MMP_PE_RC_Z_ORDER_COUNT
    #define MMP_PE_RC_Z_ORDER_COUNT             2
    #define MMP_PE_RC_Z_ORDER_GET(_ui4_idx, _i4_img_odr, _i4_thumb_odr)             \
    {                                                                               \
        switch(_ui4_idx)                                                            \
        {                                                                           \
        case 0:                                                                     \
            (_i4_img_odr) = 3;                                                      \
            (_i4_thumb_odr) = 2;                                                    \
            break;                                                                  \
        case 1:                                                                     \
            (_i4_img_odr) = 2;                                                      \
            (_i4_thumb_odr) = 1;                                                    \
            break;                                                                  \
        default:                                                                    \
            MMP_ASSERT(0);                                                          \
            (_i4_img_odr) = 0;                                                      \
            (_i4_thumb_odr) = 0;                                                    \
            break;                                                                  \
        }                                                                           \
    }
#endif

#ifndef MMP_PE_RC_IS_PROGRESSIVE_SUPT
    #define MMP_PE_RC_IS_PROGRESSIVE_SUPT()                                         \
    (                                                                               \
        mmp_pe_is_progressive_support()                                             \
    )
#endif

#ifdef APP_MMP_PE_SAVE_ROTATE
    #define MMP_PE_RC_IS_SAVE_ROTATE()          (TRUE)
#endif

#ifndef MMP_PE_RC_IS_SAVE_ROTATE
    #define MMP_PE_RC_IS_SAVE_ROTATE()          (FALSE)
#endif

#ifndef MMP_PE_RC_IS_FULL_SCREEN
    #define MMP_PE_RC_IS_FULL_SCREEN()              (FALSE)
#endif

#ifndef MMP_PE_RC_SUPPORT_FULL_DECODING
    #define MMP_PE_RC_SUPPORT_FULL_DECODING()  (((_MMP_PE_FLAG_FULL_DECODING & t_g_photo_eng.ui4_flag)&&(_MMP_PE_FLAG_QUICK_ROTATE & pt_this->ui4_flag)) ? TRUE: FALSE)
#endif

#ifndef MMP_PE_RC_IS_SLOW_LOADING
    #define MMP_PE_RC_IS_SLOW_LOADING(_h_img, e_img_type, _b_progressive, _z_w, _z_h, _b_slow)      \
    {                                                                                   \
        if(IMG_JPG == e_img_type)                                          \
        {                                                                               \
            if(_b_progressive)                                                          \
            {                                                                           \
                (_b_slow) = TRUE;                                                       \
            }                                                                           \
            else                                                                        \
            {                                                                           \
                if(((_z_w) * (_z_h)) >= 4000000)                                       \
                {                                                                       \
                    (_b_slow) = TRUE;                                                   \
                }                                                                       \
                else                                                                    \
                {                                                                       \
                    (_b_slow) = FALSE;                                                  \
                }                                                                       \
            }                                                                           \
        }                                                                               \
        else                                                                            \
        {                                                                               \
            if(((_z_w) * (_z_h)) >= 4000000)                                           \
                {                                                                       \
                    (_b_slow) = TRUE;                                                   \
                }                                                                       \
                else                                                                    \
                {                                                                       \
                    (_b_slow) = FALSE;                                                  \
                }                                                                       \
        }                                                                               \
    }
#endif

//These two Macro have been defined in mmp_photo_eng_rc.h.
#if 0
#ifndef MMP_PE_INFO_THUMB_DECODE_X
#define MMP_PE_INFO_THUMB_DECODE_X              (800)
#endif

#ifndef MMP_PE_INFO_THUMB_DECODE_Y
#define MMP_PE_INFO_THUMB_DECODE_Y              (0)
#endif
#endif

/*-----Setting for OSD Blending Effect-----*/
#ifndef MMP_PE_RC_OB_ALPAH_BEGIN
    #define MMP_PE_RC_OB_ALPAH_BEGIN                ((UINT8) 255)
#endif
#ifndef MMP_PE_RC_OB_ALPHA_MIDDLE
    #define MMP_PE_RC_OB_ALPHA_MIDDLE               ((UINT8) 0)
#endif
#ifndef MMP_PE_RC_OB_ALPHA_END
    #define MMP_PE_RC_OB_ALPHA_END                  ((UINT8) 255)
#endif

#ifndef MMP_PE_RC_DO_BAD_PHOTO_EFFECT
    #define MMP_PE_RC_DO_BAD_PHOTO_EFFECT           ((BOOL) FALSE)
#endif

/*-----default color of background-----*/
#ifndef MMP_PE_RC_DEF_BK_Y
    #define MMP_PE_RC_DEF_BK_Y                      ((UINT8) 0)
#endif

#ifndef MMP_PE_RC_DEF_BK_U
    #define MMP_PE_RC_DEF_BK_U                      ((UINT8) 128)
#endif

#ifndef MMP_PE_RC_DEF_BK_V
    #define MMP_PE_RC_DEF_BK_V                      ((UINT8) 128)
#endif

/*-----compensate for thumbnail-----*/
#ifndef MMP_PE_RC_CONVERT_COMPENSATE
    #define MMP_PE_RC_THUMB_COMPENSATE              ((UINT32)  7)
#endif
#ifndef MMP_PE_RC_CONVERT_BASE
    #define MMP_PE_RC_CONVERT_BASE                  ((UINT32) 10)
#endif
#ifndef MMP_PE_RC_ASPECT_RATIO_TOLERANCE
    #define MMP_PE_RC_ASPECT_RATIO_TOLERANCE        ((UINT32)  1)
#endif

/*-----default setting for corrupt files-----*/
#ifndef MMP_PE_RC_IS_CLEAN_LOAD_FAIL
    #define MMP_PE_RC_IS_CLEAN_LOAD_FAIL()          (TRUE)
#endif

/*-----compensate for zoom-----*/
#ifndef MMP_PE_RC_ZOOM_GET_W_COMPENSATE
    #define MMP_PE_RC_ZOOM_GET_W_COMPENSATE(_ui4_zoom, _ui4_dst_w, _ui4_src_w)          \
    {                                                                                   \
        switch(_ui4_zoom)                                                               \
        {                                                                               \
        case 2:                                                                         \
            (_ui4_src_w) = ((_ui4_dst_w) * 3) / 4;                                        \
            break;                                                                      \
        case 4:                                                                         \
            (_ui4_src_w) = ((_ui4_dst_w) * 3) / 5;                                        \
            break;                                                                      \
        default:                                                                        \
            (_ui4_src_w) = 0;                                                           \
            break;                                                                      \
        }                                                                               \
    }
#endif

#ifndef MMP_PE_RC_ZOOM_GET_H_COMPENSATE
    #define MMP_PE_RC_ZOOM_GET_H_COMPENSATE(_ui4_zoom, _ui4_src_h, _ui4_dst_h)          \
    {                                                                                   \
        switch(_ui4_zoom)                                                               \
        {                                                                               \
        case 2:                                                                         \
            (_ui4_dst_h) = ((_ui4_src_h) * 3) / 2;                                        \
            break;                                                                      \
        case 4:                                                                         \
            (_ui4_dst_h) = ((_ui4_src_h) * 2);                                            \
            break;                                                                      \
        default:                                                                        \
            (_ui4_dst_h) = (_ui4_zoom) * (_ui4_src_h);                                  \
            break;                                                                      \
        }                                                                               \
    }

#endif

#ifndef MMP_PHOTO_ENG_CUSTOM_LOGIC
    #define mmp_pe_custom_get(p1, p2, p3, p4) MMPR_NOT_IMPLEMENT
    #define mmp_pe_custom_set(p1, p2, p3, p4) MMPR_NOT_IMPLEMENT
#endif

#ifndef MMP_PHOTO_ENG_CUSTOM_LOGIC
    #define mmp_pe_is_pf_part_mode() FALSE
#endif

#ifndef MMP_PHOTO_ENG_CUSTOM_LOGIC
    #define mmp_pp_is_photo_share() FALSE
#endif


#ifndef MMP_PHOTO_ENG_JUST_SUPPORT_JPG
    #define MMP_PHOTO_ENG_JUST_SUPPORT_JPG() (FALSE)
#endif

#ifdef LINUX_AUTO_TEST
#include <stdlib.h>
#define PNG_HW_CHKSUM   0x8907715
#define PNG_SW_CHKSUM   0x8907943
#define JPG_CHKSUM      0x527df14
#define BMP_CHKSUM      0x3aac661
#define GIF_CHKSUM      0xbb8fa75
#define WEBP_CHKSUM     0x3248e9
#define MMP_PHOTO_DECODE_DONE_FILE      LINUX_TMP_PATH"/autotest/mmp_photo_dec_ok"
#define MMP_PHOTO_ZOOM_DONE_FILE        LINUX_TMP_PATH"/autotest/mmp_photo_zoom_ok"
#define MMP_PHOTO_ROTATE_DONE_FILE      LINUX_TMP_PATH"/autotest/mmp_photo_rotate_ok"
#define MMP_PHOTO_EFFECT_DONE_FILE      LINUX_TMP_PATH"/autotest/mmp_photo_effect_ok"
#define MMP_PHOTO_4K2K_DONE_FILE        LINUX_TMP_PATH"/autotest/mmp_photo_4k2k_ok"

#define CREATE_MMP_TMP_FILE(_file)          \
    {                                       \
        system("touch "_file);              \
    }
#endif

typedef enum _MMP_PP_PHOTO_PLAY_STATE_T
{
    PP_PHOTO_PLAY_NONE = 0,
    PP_PHOTO_OPENING,
    PP_PHOTO_PLAYING,
    PP_PHOTO_STOP
}MMP_PP_PHOTO_PLAY_STATE_T;










/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _MMP_PE_DATA_MEMBER_T    t_g_photo_eng;
static _MMP_PE_REQ_WINDOW_T     t_g_req_window;

static P_APPL_SPLAYER_T             gp_p_splayer = NULL;
static MMP_PP_PHOTO_PLAY_STATE_T t_g_p_play_state = PP_PHOTO_PLAY_NONE;

 /*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _mmp_pe_reset_img_file(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file);
#if 0
static VOID _mmp_pe_convert_rect_coord(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        MMP_FP_THUMB_COORDS_T               e_coord,
        GL_RECT_T*                          pt_rect);
#endif

static INT32 _mmp_pe_clean_surface(GL_HSURFACE_T h_surf);

static INT32 _mmp_pe_print_get_id(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file,
        MMP_DRC_BUF_T*                      pt_buf);

static VOID _mmp_pe_print_buffer_addr(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file);

static INT32 _mmp_pe_init_plane(
        _MMP_PE_DATA_MEMBER_T*              pt_this);

static INT32 _mmp_pe_init_view(
        _MMP_PE_DATA_MEMBER_T*              pt_this);

static INT32 _mmp_pe_init_req_window(
        _MMP_PE_REQ_WINDOW_T*               pt_req_window);

static INT32 _mmp_pe_suspend_disp_res(
        _MMP_PE_DATA_MEMBER_T*              pt_this);

static INT32 _mmp_pe_resume_disp_res(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        BOOL                                b_is_thumb);

static MMP_DRC_BUF_T* _mmp_pe_get_unused_disp_res(
        _MMP_PE_DATA_MEMBER_T*              pt_this);

static MI_BOOL _mmp_pe_get_thumbnail_data(MI_HANDLE hMm, MI_U8 **pu8ThumbnailData, MI_U16 u32Width, MI_U16 u32Height);
static VOID _mmp_pe_get_img_limitation_info(const CHAR* ps_filename, MMP_FS_PHOTO_Format_e *pFsPhotoType, VOID*  pv_info);

static BOOL _mmp_pe_is_disp_res_used_by_crnt_img(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        MMP_DRC_BUF_T*                      pt_buf);

static INT32 _mmp_pe_get_output_disp_res(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file,
        MMP_DRC_BUF_T**                     ppt_buf);

static INT32 _mmp_pe_check_working_disp_res(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file,
        MMP_DRC_BUF_T*                      pt_buf_res,
        MMP_DRC_BUF_T**                     ppt_buf_output);       /*OUT*/

static INT32 _mmp_pe_load_image(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        UINT32                              ui4_img_idx);

static INT32 _mmp_pe_load_thumbnail(
        _MMP_PE_DATA_MEMBER_T*              pt_this,                /*IN*/
        _MMP_PE_INFO_INST_T*                pt_this_obj,            /*IN*/
        IMG_TYPE_T                          e_img_type,             /*IN*/
        HANDLE_T                            h_load_surf,            /*IN*/
        HANDLE_T                            h_show_surf,            /*IN*/
        const GL_RECT_T*                    pt_boundary_rect,       /*IN*/
        BOOL                                b_no_main_thumb,        /*IN*/
        BOOL                                b_empty_show,           /*IN*/
        BOOL                                b_empty_if_err,         /*IN*/
        BOOL                                b_info_page_thum,       /*IN*/
        MMP_FP_LOAD_IMG_ROTATE_OP_T         e_rotate_op,            /*IN*/
        IMG_INTRA_TYPE_T*                   pe_thumb_type,          /*OUT*/
        GL_RECT_T*                          pt_show_rect,           /*OUT*/
        UINT32*                             pui4_load_ver);         /*OUT*/
static INT32 _mmp_pe_play_do_open(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        const CHAR*                         ps_filename,
        const UINT8*                        pui1_buf,
        SIZE_T                              z_buf_size,
        mmp_pe_play_nfy_fct                 pf_nfy,
        VOID*                               pv_tag,
        UINT32                              ui4_ver);

static INT32 mmp_pe_play_do_next_preload(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        const CHAR*                         ps_filename,
        const UINT8*                        pui1_buf,
        SIZE_T                              z_buf_size);

static INT32 _mmp_pe_open_image(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file,
        const CHAR*                         ps_filename,
        const UINT8*                        pui1_buf,
        SIZE_T                              z_buf_size);

static INT32 _mmp_pe_close_image(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file,
        BOOL                                b_send_effect_event);

static VOID _mmp_pe_update_state(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_STATE_UPDATE_TYPE_T         e_type,
        INT32                               i4_result,
        BOOL                                b_is_play);

static INT32 _mmp_pe_play_image(
        _MMP_PE_DATA_MEMBER_T*      pt_this,
        _MMP_PE_IMG_FILE_T*         pt_file,
        BOOL                        b_is_play);


static INT32 _mmp_pe_show_thumbnail(
        _MMP_PE_DATA_MEMBER_T*      pt_this,
        const GL_RECT_T*            pt_boundary_rect,
        GL_RECT_T*                  pt_show_rect);


static INT32 _mmp_pe_load_preview(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        UINT32                              ui4_img_idx);

static INT32 _mmp_pe_stop_effect(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file,
        BOOL                                b_send_effect_event);

static INT32 _mmp_pe_pause_image(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file);

static BOOL _mmp_pe_stop_next_image_preload(VOID);


static INT32 _mmp_pe_normal_scale_image(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file);

static INT32 _mmp_pe_save_rotation(
        _MMP_PE_IMG_FILE_T*                 pt_file);

static INT32 _mmp_pe_get_surf(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        MMP_PE_FILE_IDX_T                   e_idx,
        HANDLE_T*                           ph_surf);

static INT32 _mmp_pe_update_display(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file,
        BOOL                                b_flip);

static INT32 _mmp_pe_detach_display(
        _MMP_PE_DATA_MEMBER_T*              pt_this);

static _MMP_PE_ROTATE_GROUP_T _mmp_pe_get_angle_group(
        IMG_ROTATE_OP_TYPE_T                e_rotate);

static VOID _mmp_pe_get_angle_diff(
        IMG_ROTATE_OP_TYPE_T                e_crnt_rotate,
        IMG_ROTATE_OP_TYPE_T                e_new_rotate,
        UINT32*                             pui4_angle,
        UINT32*                             pui4_flip);

static INT32 _mmp_pe_get_info_title(
        FID_T                               t_fid,
        SIZE_T*                             pz_size,
        UINT8*                              pui1_buf);

static INT32 _mmp_pe_get_info_file_info(
        FID_T                               t_fid,
        _MMP_PE_INFO_FILE_INFO_T*           pt_file_info,
        MMP_FP_INFO_TYPE_T                  e_type,
        SIZE_T*                             pz_size,
        UINT8*                              pui1_buf);

static INT32 _mmp_pe_get_parent(
        FID_T                               t_fid,
        SIZE_T*                             pz_size,
        UINT8*                              pui1_buf);

static VOID _mmp_pe_reset_play_timer(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        UINT32                              ui4_img_idx,
        MMP_TIMER_OP_TYPE_T                 e_op);

static VOID _mmp_pe_play_timer_cb(
        HANDLE_T                            h_timer,
        VOID*                               pv_ui4_play_ver);

static VOID _mmp_pe_play_timer_event_handler(
        VOID*                               pv_ui4_play_ver,
        VOID*                               pv_unused1,
        VOID*                               pv_unused2,
        VOID*                               pv_unused3);

static INT32 _mmp_pe_get_file_have_thumb(
        _MMP_PE_IMG_FILE_T*                 pt_file,
        BOOL*                               pb_hav_thum);

static INT32 _mmp_pe_get_unused_info_inst(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_INFO_INST_T**               ppt_info_inst);

static INT32 _mmp_pe_info_load_thumbnail(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_INFO_INST_T*                pt_this_obj,
        MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T* pt_param);

static VOID _mmp_pe_info_ready_event_handler(
        VOID*                               pv_pt_info_obj,
        VOID*                               pv_ui4_ver,
        VOID*                               pv_nfy_tag,
        VOID*                               pv_unused3);

static VOID _mmp_pe_thumb_load_next_file(
    VOID*                       pv_pt_info_obj,
    VOID*                       pv_h_img,
    VOID*                       pv_i4_ret,
    VOID*                       pv_ver);

static INT32 _mmp_pe_show_preview(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file,
        BOOL                                b_detach_disp);

static INT32 _mmp_pe_do_xtrn_req(
        _MMP_PE_REQ_WINDOW_T*               pt_req_window);

static VOID _mmp_pe_xtrn_req_handler(
        VOID*                               pv_unused1,
        VOID*                               pv_unused2,
        VOID*                               pv_unused3,
        VOID*                               pv_unused4);

static BOOL _mmp_pe_is_valid_datetime(
    CHAR*                                   ps_exif_time);

static INT32 _mmp_pe_init_limit_info(
    _MMP_PE_DATA_MEMBER_T*              pt_this);                /*IN*/

static INT32 _mmp_pe_get_file_path(
    _MMP_PE_IMG_FILE_T*         pt_file,
    SIZE_T*                     pz_size,
    UINT8*                      pui1_buf);

#ifdef MMP_TWO_BUFF_SUPPORT_PROGRESSIVE
static INT32 _mmp_pe_progressive_rotate(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file,
    BOOL                        b_detach_disp);

static INT32 _mmp_pe_clean_next_image_preload(VOID);
#endif

static INT32 _mmp_pe_copy_attr(
    _MMP_PE_IMG_FILE_T*         pt_file,            /*in*/
    UINT32*                     pui4_attr_count,    /*in/out*/
    MMP_FP_SHOW_ATTR_T*         at_show_attr);      /*out*/
static INT32 _mmp_pe_lock_thumbnail_buf(BOOL b_lock);

static BOOL _mmp_pe_is_buf_used_by_img(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file,
    MMP_DRC_BUF_T*              pt_buf,
    UINT8*                      pui1_idx);

static VOID _mmp_pe_set_img_bad_or_corrupt(
    _MMP_PE_DATA_MEMBER_T*              pt_this,
    _MMP_PE_IMG_FILE_T*                 pt_file,
    _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_T  e_type);

static VOID _mmp_pe_rect_print(GL_RECT_T rect);

#ifdef APP_3D_PHOTO_SUPPORT
static VOID _mmp_pe_rect_even(GL_RECT_T* rect);  // make the rectangle even to fit YC422 color mode...
#endif

#ifdef APP_3D_PHOTO_SUPPORT
#ifdef APP_MENU_MMP_COEXIST
static INT32    _mmp_pe_set_3D_mode_disable(BOOL b_disable);
#endif
#endif
static INT32 _mmp_pp_photo_play(const CHAR* p_path);
static INT32 _mmp_pp_photo_stop(VOID);

static BOOL _mmp_pe_mi_module_init(VOID);
static BOOL _mmp_pe_mi_module_deinit(VOID);

static MI_U8 _mmp_pe_mi_osd_get_pixel_byte(MI_OSD_ColorFormat_e eColorFmt, MI_U8 *pu8Bpp);
static INT32 _mmp_pe_gl_dfb_snapshot_create(UINT32 ui4_w, UINT32 ui4_h);
static INT32 _mmp_pe_gl_dfb_snapshot_free(VOID);





/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_open
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_open(
    const CHAR*                 ps_filename,
    mmp_pe_play_nfy_fct         pf_nfy,
    VOID*                       pv_tag,
    UINT32                      ui4_ver)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*set data*/
    pt_req_window->apv_param[0] = (VOID*)ps_filename;
    pt_req_window->apv_param[1] = (VOID*)pf_nfy;
    pt_req_window->apv_param[2] = pv_tag;
    pt_req_window->apv_param[3] = (VOID*)ui4_ver;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_OPEN;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_mopen
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_mopen(
    const UINT8*                pui1_buf,
    SIZE_T                      z_buf_size,
    mmp_pe_play_nfy_fct         pf_nfy,
    VOID*                       pv_tag,
    UINT32                      ui4_ver)
{
    _MMP_PE_REQ_PARAM_MEM_OPEN_T    t_param;
    _MMP_PE_REQ_WINDOW_T*           pt_req_window = &t_g_req_window;

    /*set data*/
    t_param.pui1_buf = pui1_buf;
    t_param.z_buf_size = z_buf_size;
    t_param.pf_nfy = pf_nfy;
    t_param.pv_tag = pv_tag;
    t_param.ui4_ver = ui4_ver;

    pt_req_window->apv_param[0] = (VOID*)&t_param;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_MEM_OPEN;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_close(VOID)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_CLOSE;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_attr_set
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_attr_set(
    UINT32                      ui4_attr_count,
    const MMP_FP_SHOW_ATTR_T*   at_show_attr)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*set data*/
    pt_req_window->apv_param[0] = (VOID*)ui4_attr_count;
    pt_req_window->apv_param[1] = (VOID*)at_show_attr;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_ATTR_SET;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_next_preload
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_next_preload(
    const CHAR*                 ps_filename)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*set data*/
    pt_req_window->apv_param[0] = (VOID*)ps_filename;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_NEXT_PRELOAD;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_next_mpreload
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_next_mpreload(
    const UINT8*                pui1_buf,
    SIZE_T                      z_buf_size)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*set data*/
    pt_req_window->apv_param[0] = (VOID*)pui1_buf;
    pt_req_window->apv_param[1] = (VOID*)(UINT32)z_buf_size;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_NEXT_MEM_PRELOAD;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_next_attr_set
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_next_attr_set(
    UINT32                      ui4_attr_count,
    const MMP_FP_SHOW_ATTR_T*   at_show_attr)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*set data*/
    pt_req_window->apv_param[0] = (VOID*)ui4_attr_count;
    pt_req_window->apv_param[1] = (VOID*)at_show_attr;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_NEXT_ATTR_SET;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_show(VOID)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_SHOW;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_start
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_start(VOID)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_PLAY;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_stop
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_stop(VOID)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_STOP;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_pause
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_pause(VOID)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_PAUSE;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_clean
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_clean(VOID)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_CLEAN;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_next
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_next(
    UINT32                      ui4_ver)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*set data*/
    pt_req_window->apv_param[0] = (VOID*)ui4_ver;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_NEXT;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_get_file
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_get_file(
    MMP_PE_FILE_IDX_T           e_idx,
    CHAR**                      pps_name)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*set data*/
    pt_req_window->apv_param[0] = (VOID*)e_idx;
    pt_req_window->apv_param[1] = (VOID*)pps_name;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_GET_FILE;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name: a_mmp_pe_play_get_surf
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_get_surf(
    MMP_PE_FILE_IDX_T           e_idx,
    HANDLE_T*                   ph_surf)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*set data*/
    pt_req_window->apv_param[0] = (VOID*)e_idx;
    pt_req_window->apv_param[1] = (VOID*)ph_surf;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_GET_SURF;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_pe_play_rotate(IMG_ROTATE_OP_TYPE_T        e_degree)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_ROTATE;

    /*set data*/
    pt_req_window->apv_param[0] = (VOID*)e_degree;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 a_mmp_play_show_info_thum(BOOL                  b_show_thumb,
                               GL_RECT_T*            pt_rect,
                               MMP_FP_THUMB_COORDS_T e_coord)
{
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    /*post req message*/
    pt_req_window->e_id = _MMP_PE_REQ_ID_INFO_THUM;

    /*set data*/
    pt_req_window->apv_param[0] = (VOID*)(UINT32)b_show_thumb;
    pt_req_window->apv_param[1] = (VOID*)pt_rect;
    pt_req_window->apv_param[2] = (VOID*)e_coord;

    return _mmp_pe_do_xtrn_req(pt_req_window);
}



/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: mmp_pe_is_progressive_support
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL mmp_pe_is_progressive_support(VOID)
{
    return t_g_photo_eng.t_limit.b_is_progressive_support;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

#ifdef APP_SUPPORT_4K2K
#ifndef APP_SUPPORT_FULL_3D_PHOTO
static VOID _mmp_pe_update_disp_by_3dmode(UINT8 i1_3d_mode)
{

}

static VOID _mmp_pe_icl_nfy_func_handler (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3,
                    VOID*                       pv_tag4)
{
    UINT8                       ui1_val = 0;
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;

    pt_file = &pt_this->at_img[pt_this->ui1_crnt_img];
    ui1_val = (UINT8) (((UINT32) pv_tag1) & 0x000000FF);

    MMP_DBG_INFO(("[Photo/callback] ui1_val=%d.\n", ui1_val));

    if (ICL_3D_MODE_OFF == ui1_val)
    {
        if(pt_file->ui2_flag & _MMP_PE_IMG_FLAG_MPO_3D_OFF)
        {
            pt_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_MPO_3D_OFF);
            MMP_DBG_INFO(("=== [%s-->%d]3D_MODE_OFF callback come from mmp,skip===\n",__FUNCTION__, __LINE__));
            return;
        }
    }
    else if (ICL_3D_MODE_AUTO == ui1_val)
    {
        if(pt_file->ui2_flag & _MMP_PE_IMG_FLAG_MPO_3D_ON)
        {
            pt_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_MPO_3D_ON);
            MMP_DBG_INFO(("=== [%s-->%d]3D_MODE_AUTO callback come from mmp,skip===\n",__FUNCTION__, __LINE__));
            return;
        }
    }
    #if 0
    if(IMG_MPO == pt_file->e_img_type)
    {
        if(ICL_3D_MODE_OFF == ui1_val)
        {
            MMP_DBG_INFO(("[Photo/callback] This is MPO file, and just show fhd buffer(first enter callback).\n"));
            return;
        }
        else if(_mmp_pe_is_disp_res_used_by_crnt_img(pt_this, pt_this->pt_buf_crnt_disp))
        {
            MMP_DBG_INFO(("[Photo/callback] This is MPO file, and just stay fhd buffer(second...enter callback).\n"));
            return;
        }
    }
    #endif
    _mmp_pe_update_disp_by_3dmode(ui1_val);
}

static INT32 _mmp_pe_icl_nfy_func(
    UINT16              ui2_nfy_id,
    VOID*               pv_tag,
    ICL_NOTIFY_DATA_T*  pt_notify_data)
{
    ICL_GRPID_TYPE  e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    ICL_RECID_TYPE  e_rec_id = ICL_GET_REC (pt_notify_data->pe_id[0]);
    UINT8           ui1_val = 0;
    INT32               i4_ret;
    SIZE_T          z_size = sizeof (UINT8);

    if ( e_grp_id != ICL_GRPID_3D )
    {
        return MMPR_OK;
    }

    if( e_grp_id == ICL_GRPID_3D )
    {
        switch( e_rec_id )
        {
        case ICL_RECID_3D_MODE:
            i4_ret = a_icl_get (ICL_MAKE_ID (ICL_GRPID_3D, ICL_RECID_3D_MODE), (VOID *) &ui1_val, &z_size);
            if (ICLR_OK != i4_ret)
            {
                MMP_DBG_INFO(("\n a_icl_get Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            }
            mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_CRITICAL,
                                _mmp_pe_icl_nfy_func_handler,
                                (void*)(UINT32)ui1_val,
                                NULL,
                                NULL,
                                NULL);
            break;
        default:
            break;
        }
    }

    return MMPR_OK;
}
#endif
#endif

INT32 mmp_pe_init(
    const MMP_PE_INIT_SETTING_T*            pt_setting)
{
    _MMP_PE_DATA_MEMBER_T*                  pt_this = &t_g_photo_eng;
    _MMP_PE_REQ_WINDOW_T*                   pt_req_window = &t_g_req_window;
    INT32                                   i4_ret;
    UINT32                                  i;

    if(NULL == pt_setting)
    {
        MMP_DBG_ERROR(("pt_setting cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }

    if(_MMP_PE_FLAG_INIT_READY & pt_this->ui4_flag)
    {
        MMP_DBG_ERROR(("Already Init.\r\n"));
        return MMPR_FAIL;
    }

    /*init members*/
    c_memset(pt_this, 0, sizeof(_MMP_PE_DATA_MEMBER_T));
    pt_this->ui1_crnt_img = _MMP_PE_IMG_IDX_NULL;
    pt_this->pt_buf_crnt_disp = NULL;
    pt_this->e_state = MMP_PLAY_STATE_CLOSED;
#ifdef APP_SUPPORT_4K2K
    pt_this->ui1_prev_photo_is_4k2k = 0xFF;
#endif

    for(i = 0; i < _MMP_PE_IMAGE_FILE_MAX_COUNT; i++)
    {
        _MMP_PE_WORKING_BUF_RESET(pt_this->at_img[i].t_working_buf);
        _mmp_pe_reset_img_file(pt_this, &pt_this->at_img[i]);
    }

    for(i = 0; i < MMP_PE_RC_INFO_INST_MAX_COUNT; i++)
    {
        _MMP_PE_INFO_INST_RESET(pt_this->at_info_inst[i]);
    }

    /*create timer*/
    i4_ret = c_timer_create(&pt_this->h_play_timer);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_create() failed. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    do
    {
        /*init member*/
        if(pt_setting->b_quick_rotate)
        {
            pt_this->ui4_flag |= _MMP_PE_FLAG_QUICK_ROTATE;
            pt_this->ui4_disp_count = _MMP_PE_DISPLAY_RES_MAX_COUNT;
        }
        else
        {
            pt_this->ui4_disp_count = _MMP_PE_IMAGE_FILE_MAX_COUNT;
        }

        if(pt_setting->b_no_thumb_from_main)
        {
            pt_this->ui4_flag |= _MMP_PE_FLAG_NO_MAIN_THUMB;
        }

        if(pt_setting->b_show_thumb_as_next)
        {
            pt_this->ui4_flag |= _MMP_PE_FLAG_SHOW_THUMB_AS_NEXT;
        }

        /*get full mode support capability*/
        //t_caps.ui4_type = IMG_HW_JPG_CAP_FULL_MODE;
        //i4_ret = c_img_get_capability(&t_caps);
        if(1)//IMGR_OK == i4_ret && t_caps.u.b_full_mode_support)
        {
            pt_this->ui4_flag |= _MMP_PE_FLAG_FULL_DECODING;
        }

        //init mi module
        _mmp_pe_mi_module_init();

        /*init plane*/
        i4_ret = _mmp_pe_init_plane(pt_this);
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /*init view*/
        i4_ret = _mmp_pe_init_view(pt_this);
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /*init request window*/
        i4_ret = _mmp_pe_init_req_window(pt_req_window);
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /*convert and keep thumbnail rect*/
        pt_this->t_thumb_rect = pt_setting->t_thumb_rect;
        mmp_drc_convert_rect_coord(pt_setting->e_thumb_rect_coord, &pt_this->t_thumb_rect);
        #ifdef APP_3D_PHOTO_SUPPORT
        pt_this->t_nexting_thumb_rect = pt_setting->t_thumb_rect;
        mmp_drc_convert_rect_coord(MMP_FP_THUMB_COORDS_VIRTUAL_SCREEN, &pt_this->t_nexting_thumb_rect);
        #endif

        /*keep setting*/
        pt_this->ui4_flag |= _MMP_PE_FLAG_INIT_READY;

        #ifdef APP_SUPPORT_4K2K
        #ifndef APP_SUPPORT_FULL_3D_PHOTO
        i4_ret = a_icl_notify_reg(ICL_GRPID_3D,
                        128,
                        NULL,
                        NULL,
                        _mmp_pe_icl_nfy_func,
                        &pt_this->ui2_icl_id_3d);
        if(0 != i4_ret)
        {
            MMP_DBG_ERROR(("%s:%d notify reg icl fail!!!\n", __FUNCTION__, __LINE__));
        }
        #endif
        #endif
        return MMPR_OK;

    } while(0);

    /**/
    pt_this->ui4_flag = _MMP_PE_FLAG_INIT_READY;

    mmp_pe_deinit();

    return MMPR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_deinit(VOID)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;
    INT32                       i4_ret;
    UINT32                      i;

    if(0 == (_MMP_PE_FLAG_INIT_READY & pt_this->ui4_flag))
    {
        return MMPR_OK;
    }

    /*close info instance*/
    for(i = 0; i < MMP_PE_RC_INFO_INST_MAX_COUNT; i++)
    {
        i4_ret = mmp_pe_info_close(&pt_this->at_info_inst[i]);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_pe_info_close(%d) failed. i4_ret = %d.\r\n", i, i4_ret));
            MMP_ASSERT(0);
        }
    }

    /*close play instance*/
    mmp_pe_play_close();

    //
    _mmp_pe_mi_module_deinit();


    /*delete timer*/
    if(NULL_HANDLE != pt_this->h_play_timer)
    {
        i4_ret = c_timer_delete(pt_this->h_play_timer);
        if(OSR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_timer_delete(h_timer = %d) failed. i4_ret = %d.\r\n", pt_this->h_play_timer, i4_ret));
            MMP_ASSERT(0);
        }

        pt_this->h_play_timer = NULL_HANDLE;
    }

    for(i = 0; i < _MMP_PE_IMAGE_FILE_MAX_COUNT; i++)
    {
        _mmp_pe_close_image(pt_this, &pt_this->at_img[i], FALSE);
    }

    //
    _mmp_pe_gl_dfb_snapshot_free();


    //
    if(pt_this->ui4_thumbanil_viewport != 0)
    {
        c_gl_view_delete_viewport(pt_this->h_thumbnail_view,pt_this->ui4_thumbanil_viewport);
        pt_this->ui4_thumbanil_viewport = 0;
    }
    //
    if(pt_this->h_thumbnail_surf != NULL_HANDLE)
    {
        c_gl_obj_free(pt_this->h_thumbnail_surf);
        pt_this->h_thumbnail_surf = NULL_HANDLE;
    }
    //
    if(pt_this->h_thumbnail_view != NULL_HANDLE)
    {
        c_gl_obj_free(pt_this->h_thumbnail_view);
        pt_this->h_thumbnail_view = NULL_HANDLE;
    }
    /*free plane*/
    if(pt_this->h_thumbnail_plane != NULL_HANDLE)
    {
        c_gl_obj_free(pt_this->h_thumbnail_plane);
        pt_this->h_thumbnail_plane = NULL_HANDLE;
    }
    //
    if(NULL_HANDLE != pt_this->h_screen)
    {
        i4_ret = c_gl_obj_free(pt_this->h_screen);
        MMP_ASSERT(GLR_OK == i4_ret);

        pt_this->h_screen = NULL_HANDLE;
    }

    pt_this->ui4_flag = 0;

    /*free semaphore for protection*/
    if(NULL_HANDLE != pt_req_window->h_ready_signal)
    {
        i4_ret = c_sema_delete(pt_req_window->h_ready_signal);
        MMP_ASSERT(OSR_OK == i4_ret);

        pt_req_window->h_ready_signal = NULL_HANDLE;
    }

#ifdef APP_SUPPORT_4K2K
#ifndef APP_SUPPORT_FULL_3D_PHOTO
        a_icl_notify_unreg(pt_this->ui2_icl_id_3d);
#endif
#endif

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_is_type_of
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_is_type_of(
    const CHAR*                 ps_filename,
    MMP_MEDIA_TYPE_T*           pe_type)
{
    if(NULL == ps_filename || NULL == pe_type)
    {
        return MMPR_INV_ARG;
    }

    if(mmp_util_filter_fct_by_ext(ps_filename, (CHAR*) as_g_image_ext, ui2_g_image_ext_count))
    {
        *pe_type = MMP_MEDIA_TYPE_PHOTO;
    }
    else
    {
        *pe_type = MMP_MEDIA_TYPE_UNKNOWN;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_alloc_common_res
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_alloc_common_res(VOID)
{
#if 0
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    INT32                       i4_ret;

    if(0 == (_MMP_PE_FLAG_SCREEN_LINKED & pt_this->ui4_flag))
    {
        i4_ret = c_gl_plane_link(pt_this->h_plane, pt_this->h_screen, TRUE);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_gl_plane_link() failed. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }

        pt_this->ui4_flag |= _MMP_PE_FLAG_SCREEN_LINKED;
    }
#endif
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_free_common_res
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_free_common_res(VOID)
{
#if 0
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    INT32                       i4_ret, i4_order;

    if(0 != (_MMP_PE_FLAG_SCREEN_LINKED & pt_this->ui4_flag))
    {
        i4_order = pt_this->i1_img_z_order/*MMP_PE_RC_IMG_Z_ORDER*/;
        i4_order--;

        /*set the plane order*/
        i4_ret = c_gl_plane_reorder(pt_this->h_plane, GL_REORDER_ABSOLUTE, i4_order);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_gl_plane_reorder(%d) failed. i4_ret = %d.\r\n", i4_order, i4_ret));
        }

        i4_ret = c_gl_plane_link(pt_this->h_plane, NULL, TRUE);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_gl_plane_link(NULL) failed. i4_ret = %d.\r\n", i4_ret));
            MMP_ASSERT(0);
        }

        pt_this->ui4_flag &= ~(_MMP_PE_FLAG_SCREEN_LINKED);
    }
#endif

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_info_open
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/



 static INT32 _mmp_pe_get_photo_type_strcmp_nocase(
    const CHAR* ps_s1,
    const CHAR* ps_s2
                    )
{
    INT32 i4_ret;

    if (ps_s1 == NULL)
    {
        return (ps_s2 == NULL) ? 0 : -1;
    }
    else if (ps_s2 == NULL)
    {
        return 1;
    }

    do
    {
        CHAR pc1 = *ps_s1;
        CHAR pc2 = *ps_s2;

        if ((pc1 >= 'a') && (pc1 <= 'z'))
        {
            pc1 += ('A' - 'a');
        }
        if ((pc2 >= 'a') && (pc2 <= 'z'))
        {
            pc2 += ('A' - 'a');
        }
        i4_ret = pc1 - pc2;
        if (i4_ret != 0)
        {
            return (i4_ret > 0) ? 1 : -1;
        }
    } while ((*ps_s1++ != '\0') && (*ps_s2++ != '\0'));

    return 0;
}
static BOOL _mmp_pe_get_photo_filter_fct_by_ext (
                    const CHAR*                     ps_filename,
                    CHAR*                           as_ext_name,
                    const UINT16                    ui2_as_ext_name_num
                    )
{
    UINT16 ui2_i;
    BOOL b_ret = FALSE;
    CHAR* s_ext_name = c_strrchr (ps_filename, '.');

    if (NULL == s_ext_name)
    {
        return FALSE;
    }

    /* Skip ".". */
    s_ext_name++;

    for (ui2_i = 0;ui2_i < ui2_as_ext_name_num;ui2_i++)
    {
        if (_mmp_pe_get_photo_type_strcmp_nocase (s_ext_name, as_ext_name + (ui2_i * 5)) == 0)
        {
            b_ret = TRUE;
            break;
        }
    }

    return b_ret;
}


/*
i4_ret = pt_this->at_player[ui1_file_idx].t_intf.t_info_intf.pf_open(pt_info_inst->t_file.ps_filename,
                                                                     _mmp_mc_browse_info_file_nfy_cb,
                                                                     (VOID*)_MMP_MC_BROWSE_MAKE_INFO_TAG_VER(e_id, pt_info_inst->ui2_info_ver),
                                                                     &pt_info_inst->pv_inst);
*/
INT32 mmp_pe_info_open(
    const CHAR*                 ps_filename,
    mmp_fp_info_nfy_fct         pf_nfy,
    VOID*                       pv_tag,
    VOID**                      ppv_info_inst)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_INFO_INST_T*        pt_this_obj = NULL;
    INT32                       i4_ret = MMPR_OK;
    _MMP_IMAGE_INFO             imageInfo = {0};
    BOOL b_meet_all             = FALSE;


    /**/
    if(NULL == ps_filename || NULL == pf_nfy || NULL == ppv_info_inst)
    {
        MMP_DBG_ERROR(("[mmp] %s %d  ps_filename, pf_nfy, and ppv_info_inst cannot be NULL.\r\n", __FUNCTION__,__LINE__));
        return MMPR_INV_ARG;
    }

    DBG_INFO_DIRECT("[mmp pe] %s %d ps_filename:%s \r\n",__FUNCTION__,__LINE__,ps_filename);

    /**/
    i4_ret = _mmp_pe_get_unused_info_inst(pt_this, &pt_this_obj);
    if(MMPR_OK != i4_ret)
    {
        DBG_INFO_DIRECT("[mmp pe] %s %d _mmp_pe_get_unused_info_inst() failed. i4_ret = %d.\r\n",__FUNCTION__,__LINE__, i4_ret);
        return i4_ret;
    }

    #if 0
    /**/
    if(FALSE == _MMP_PE_IS_LIMIT_INFO_READY(pt_this))
    {
        i4_ret = _mmp_pe_init_limit_info(pt_this);
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }
    #endif

    /*keep setting*/
    pt_this_obj->pf_info_nfy = pf_nfy;
    pt_this_obj->pv_info_nfy_tag = pv_tag;
    pt_this_obj->ui4_ver = (_MMP_PE_INFO_VER_INVALID == (++pt_this->ui4_info_ver)) ? (++pt_this->ui4_info_ver) : pt_this->ui4_info_ver;

    do
    {
        /*keep file name for load_thumbnial*/
        i4_ret = mmp_fid_add(ps_filename, &pt_this_obj->t_path);
        if(MMPR_OK != i4_ret)
        {
            DBG_INFO_DIRECT("[mmp pe] %s %d  mmp_fid_add(%s) failed. i4_ret = %d.\r\n", __FUNCTION__,__LINE__, ps_filename, i4_ret);
            pt_this_obj->t_path = MMP_FID_NULL_REC_IDX;
            break;
        }

        // 1. get image info and
        i4_ret = mmp_pe_get_image_info(ps_filename,&imageInfo);
        if(i4_ret != 0)
        {
            DBG_INFO_DIRECT("[mmp pe] %s %d File is over limitation.\r\n", __FUNCTION__,__LINE__);
            i4_ret = MMPR_OK;
            break;
        }
        MMP_DBG_INFO(("[mmp] %s %d  PhotoType:%x \r\n", __FUNCTION__,__LINE__, imageInfo.PhotoType));
        MMP_DBG_INFO(("[mmp] %s %d  Ori_Width:%d  Ori_Height:%d \r\n", __FUNCTION__,__LINE__,imageInfo.Width,imageInfo.Height));
        MMP_DBG_INFO(("[mmp] %s %d  IsExif:%d \r\n", __FUNCTION__,__LINE__, imageInfo.IsExif));
        MMP_DBG_INFO(("[mmp] %s %d  FlashUsed:%d \r\n", __FUNCTION__,__LINE__, imageInfo.FlashUsed));
        MMP_DBG_INFO(("[mmp] %s %d  ExposureBias:%lf \r\n", __FUNCTION__,__LINE__, imageInfo.ExposureBias));
        MMP_DBG_INFO(("[mmp] %s %d  ExposureProgram:%d \r\n", __FUNCTION__,__LINE__, imageInfo.ExposureProgram));
        MMP_DBG_INFO(("[mmp] %s %d  ISOequivalent:%d \r\n", __FUNCTION__,__LINE__, imageInfo.ISOequivalent));
        MMP_DBG_INFO(("[mmp] %s %d  Orientation:%d \r\n", __FUNCTION__,__LINE__, imageInfo.Orientation));

        // 2. set image dimension
        pt_this_obj->z_img_w = imageInfo.Width;
        pt_this_obj->z_img_h = imageInfo.Height;

        // 3. set image type [mapping type]
        switch(imageInfo.PhotoType)
        {
            case E_FS_FORMAT_PNG:
                pt_this_obj->e_img_type = IMG_PNG;
                break;
            case E_FS_FORMAT_GIF:
                pt_this_obj->e_img_type = IMG_GIF;
                break;
            case E_FS_FORMAT_BMP:
                pt_this_obj->e_img_type = IMG_BMP;
                break;
            case E_FS_FORMAT_JPEG:
                pt_this_obj->e_img_type = IMG_JPG;
                break;
            default:
                pt_this_obj->e_img_type = IMG_UNKNOWN;
        }

        // 4. get hw/decode limit info
        _mmp_pe_get_img_limitation_info(ps_filename,&imageInfo.PhotoType,(VOID *)&b_meet_all);
        if(!b_meet_all)
        {
            MMP_DBG_ERROR(("[mmp] %s %d File is over limitation.\r\n", __FUNCTION__,__LINE__));
            i4_ret = MMPR_OK;
            break;
        }
    } while(0);



    /*post a message for sending a info ready message*/
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                _mmp_pe_info_ready_event_handler,
                                (VOID*)pt_this_obj,
                                (VOID*)pt_this_obj->ui4_ver,
                                (VOID*)(UINT32)(i4_ret == MMPR_OK ? TRUE:FALSE),
                                NULL);

    *ppv_info_inst = pt_this_obj;
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_info_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_info_close(
    VOID*                       pv_info_inst)
{
    _MMP_PE_INFO_INST_T*        pt_this_obj;
    INT32                       i4_ret;

    if(NULL == pv_info_inst)
    {
        return MMPR_OK;
    }
    pt_this_obj = (_MMP_PE_INFO_INST_T*)pv_info_inst;

    DBG_INFO_DIRECT("[mmp pe] %s %d mmp_fid_del(%d)\r\n",__FUNCTION__,__LINE__,pt_this_obj->t_path);

    /*free path*/
    if(MMP_FID_NULL_REC_IDX != pt_this_obj->t_path)
    {
        i4_ret = mmp_fid_del(pt_this_obj->t_path);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_fid_del(%d) failed. i4_ret = %d.\r\n", pt_this_obj->t_path, i4_ret));
            MMP_ASSERT(0);
        }
    }


    /**/
    _MMP_PE_INFO_INST_RESET(*pt_this_obj);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_info_get
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_info_get(
    VOID*                       pv_info_inst,
    MMP_FP_INFO_TYPE_T          e_type,
    SIZE_T*                     pz_size,
    UINT8*                      pui1_buf)
{
    EXIF_INFO_T                 t_exif_info;
    _MMP_PE_INFO_INST_T*        pt_this_obj;
    INT32                       i4_ret = MMPR_OK;
    BOOL                        b_try_next = FALSE;

    /*check param*/
    if(NULL == pv_info_inst || NULL == pz_size)
    {
        MMP_DBG_ERROR(("pv_info_inst and pz_size cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }
    pt_this_obj = (_MMP_PE_INFO_INST_T*)pv_info_inst;

    c_memset(&t_exif_info, 0, sizeof(EXIF_INFO_T));

    switch (e_type)
    {
    case MMP_FP_INFO_TYPE_ARTIST:
        {
            t_exif_info.e_exif_id = EXIF_ARTIST;
        }
        break;

    case MMP_FP_INFO_TYPE_DATE:
        {
            t_exif_info.e_exif_id = EXIF_DATE_TIME_ORIGINAL;
        }
        break;

    case MMP_FP_INFO_TYPE_TYPE:
        {
            if(0 == *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(IMG_TYPE_T);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *((IMG_TYPE_T*)pui1_buf) = pt_this_obj->e_img_type;
        }
        return MMPR_OK;

    case MMP_FP_INFO_TYPE_ALBUM:
        return _mmp_pe_get_parent(pt_this_obj->t_path, pz_size, pui1_buf);

    case MMP_FP_INFO_TYPE_CREATE_TIME:
    case MMP_FP_INFO_TYPE_LAST_WRITE_TIME:
    case MMP_FP_INFO_TYPE_PROTECT:
    case MMP_FP_INFO_TYPE_SIZE:
        return _mmp_pe_get_info_file_info(pt_this_obj->t_path, &pt_this_obj->t_file_info, e_type, pz_size, pui1_buf);

    case MMP_FP_INFO_TYPE_PRODUCER:
        {
            t_exif_info.e_exif_id = EXIF_MAKE;
        }
        break;

    case MMP_FP_INFO_TYPE_TITLE:
        return _mmp_pe_get_info_title(pt_this_obj->t_path, pz_size, pui1_buf);

    case MMP_FP_INFO_TYPE_ROTATION:
        {
            t_exif_info.e_exif_id = EXIF_ORIENTATION;
        }
        break;

    case MMP_FP_INFO_TYPE_RESOLUTION:
        {
            if(0 == *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(GL_SIZE_T);
                return MMPR_BUF_NOT_ENOUGH;
            }

            ((GL_SIZE_T*)pui1_buf)->ui4_width = pt_this_obj->z_img_w;
            ((GL_SIZE_T*)pui1_buf)->ui4_height = pt_this_obj->z_img_h;
        }
        return MMPR_OK;

    default:
        return MMPR_NO_DATA;
    }

    if(0 == *pz_size || NULL == pui1_buf)
    {
        #if 0
        /*query info*/
        i4_ret = c_img_get_exif_info_len(pt_this_obj->h_img, INTRA_IMG_PRIMARY_IMG_TYPE, &t_exif_info, 1);
        if(IMGR_OK != i4_ret && IMGR_NO_EXIF_DATA != i4_ret)
        {
            MMP_DBG_ERROR(("c_img_get_exif_info_len(id = %d) failed. i4_ret = %d.\r\n", t_exif_info.e_exif_id, i4_ret));
            return MMPR_FAIL;
        }

        if(IMGR_NO_EXIF_DATA == i4_ret || EXIF_AVAILABLE != t_exif_info.e_property)
        {
            *pz_size = 0;
            return MMPR_NO_DATA;
        }

        *pz_size = t_exif_info.z_size;
        return MMPR_BUF_NOT_ENOUGH;
        #endif
    }

    /**/
    t_exif_info.z_size = *pz_size;
    t_exif_info.pv_data = pui1_buf;

    #if 0
    i4_ret = c_img_get_exif_info(pt_this_obj->h_img, INTRA_IMG_PRIMARY_IMG_TYPE, &t_exif_info, 1);
    if(IMGR_OK != i4_ret && IMGR_NO_EXIF_DATA != i4_ret && IMGR_INSUFFICIENT_BUFFER != i4_ret)
    {
        MMP_DBG_ERROR(("c_img_get_exif_info(id = %d) failed. i4_ret = %d.\r\n", t_exif_info.e_exif_id, i4_ret));
        return MMPR_FAIL;
    }

    /*check date*/
    if(IMGR_NO_EXIF_DATA == i4_ret || EXIF_AVAILABLE != t_exif_info.e_property)
    {
        b_try_next = TRUE;
    }
    else if(MMP_FP_INFO_TYPE_DATE == e_type) /*IMGR_OK*/
    {
        if(FALSE == _mmp_pe_is_valid_datetime((CHAR*)pui1_buf))
        {
            b_try_next = TRUE;
        }
        else
        {
            pui1_buf[4] = '/';
            pui1_buf[7] = '/';
        }
    }

    if(b_try_next)
    {
        if(MMP_FP_INFO_TYPE_DATE == e_type)
        {
            /*no EXIF_DATE_TIME_ORIGINAL, try EXIF_DATE_TIME*/
            t_exif_info.e_exif_id = EXIF_DATE_TIME;
            i4_ret = c_img_get_exif_info(pt_this_obj->h_img, INTRA_IMG_PRIMARY_IMG_TYPE, &t_exif_info, 1);
            if(IMGR_OK != i4_ret && IMGR_NO_EXIF_DATA != i4_ret && IMGR_INSUFFICIENT_BUFFER != i4_ret)
            {
                MMP_DBG_ERROR(("c_img_get_exif_info(EXIF_DATE_TIME) failed. i4_ret = %d.\r\n", i4_ret));
                return MMPR_FAIL;
            }

            /*check date*/
            if(IMGR_NO_EXIF_DATA == i4_ret || EXIF_AVAILABLE != t_exif_info.e_property)
            {
                *pz_size = 0;
                return MMPR_NO_DATA;
            }
            else
            {
                if(FALSE == _mmp_pe_is_valid_datetime((CHAR*)pui1_buf))
                {
                    *pz_size = 0;
                    return MMPR_NO_DATA;
                }
                else
                {
                    pui1_buf[4] = '/';
                    pui1_buf[7] = '/';
                }
            }
        }
        else
        {
            *pz_size = 0;
            return MMPR_NO_DATA;
        }
    }
    #endif
    *pz_size = t_exif_info.z_size;
    //return (IMGR_INSUFFICIENT_BUFFER == i4_ret) ? MMPR_BUF_NOT_ENOUGH : MMPR_OK;
    //CID:4641492, "i4_ret" must be equal "MMPR_OK"
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_info_set
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_info_set(
    VOID*                       pv_info_inst,
    MMP_FP_INFO_TYPE_T          e_type,
    SIZE_T*                     pz_size,
    UINT8*                      pui1_buf)
{
    EXIF_INFO_T                 t_exif_info;
    _MMP_PE_INFO_INST_T*        pt_this_obj;
    //INT32                       i4_ret;

    /*check param*/
    if(NULL == pv_info_inst || NULL == pz_size || 0 == *pz_size || NULL == pui1_buf)
    {
        MMP_DBG_ERROR(("pv_info_inst, pz_size, and pui1_buf cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }

    c_memset( &t_exif_info, 0, sizeof(t_exif_info) );

    pt_this_obj = (_MMP_PE_INFO_INST_T*)pv_info_inst;

    switch(e_type)
    {
    case MMP_FP_INFO_TYPE_ARTIST:
        {
            t_exif_info.e_exif_id = EXIF_ARTIST;
        }
        break;

    case MMP_FP_INFO_TYPE_DATE:
        {
            t_exif_info.e_exif_id = EXIF_DATE_TIME;
        }
        break;

    case MMP_FP_INFO_TYPE_PRODUCER:
        {
            t_exif_info.e_exif_id = EXIF_MAKE;
        }
        break;

    case MMP_FP_INFO_TYPE_ROTATION:
        {
            t_exif_info.e_exif_id = EXIF_ORIENTATION;
        }
        break;

    default:
        return MMPR_NOT_SUPPORT;
    }

    /**/
    t_exif_info.z_size = *pz_size;
    t_exif_info.pv_data = pui1_buf;
    t_exif_info.e_property = EXIF_AVAILABLE;

    //i4_ret = c_img_set_exif_info(pt_this_obj->h_img, INTRA_IMG_PRIMARY_IMG_TYPE, &t_exif_info, 1);
    //if(IMGR_OK != i4_ret && IMGR_NO_EXIF_DATA != i4_ret)
    //{
    //    MMP_DBG_ERROR(("c_img_set_exif_info(id = %d) failed. i4_ret = %d.\r\n", t_exif_info.e_exif_id, i4_ret));
    //    return MMPR_FAIL;
    //}

    // Fix coverity-4490146: Uninitialized scalar variable.
    /*check date*/
    if( /*IMGR_NO_EXIF_DATA == i4_ret ||*/ EXIF_AVAILABLE != t_exif_info.e_property)
    {
        *pz_size = 0;
        return MMPR_NO_DATA;
    }

    *pz_size = t_exif_info.z_size;
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_info_cmd_do
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_info_cmd_do(
    VOID*                       pv_info_inst,
    MMP_FP_INFO_CMD_ID_T        e_cmd,
    VOID*                       pv_cmd_param)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_INFO_INST_T*        pt_this_obj;
    INT32                       i4_ret;

    /*check param*/
    if(NULL == pv_info_inst)
    {
        MMP_DBG_ERROR(("pv_info_inst cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }
    pt_this_obj = (_MMP_PE_INFO_INST_T*)pv_info_inst;

    /**/
    switch(e_cmd)
    {
    case MMP_FP_INFO_CMD_ID_LOAD_THUMB:     /*argument: a pointer to MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T variable*/
        {
            if(NULL == pv_cmd_param)
            {
                MMP_DBG_ERROR(("pv_cmd_param cannot be NULL.\r\n"));
                return MMPR_INV_ARG;
            }

            return _mmp_pe_info_load_thumbnail(pt_this, pt_this_obj, (MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T*)pv_cmd_param);
        }

    case MMP_FP_INFO_CMD_ID_STOP_THUMB:     /*argument: NULL.*/
        {
            if(_MMP_PE_INFO_FLAG_LOADING & pt_this_obj->ui1_flag)
            {
                pt_this_obj->ui1_flag &= ~(_MMP_PE_INFO_FLAG_LOADING);
            }
        }
        break;

    default:
        return MMPR_NOT_SUPPORT;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_info_cmd_res_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_info_cmd_res_init(VOID)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    INT32                       i4_ret;

    if(_MMP_PE_FLAG_THUMB_DISP_RESUMED & pt_this->ui4_flag)
    {
        return MMPR_OK;
    }

    if(_MMP_PE_FLAG_PLAY_DISP_RESUMED & pt_this->ui4_flag)
    {
        MMP_ASSERT(0);
        return MMPR_INTERNAL_ERROR;
    }

    i4_ret = _mmp_pe_resume_disp_res(pt_this, TRUE);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /*_mmp_pe_lock_thumbnail_buf(TRUE);*/

#if 0
    /**/
    i4_ret = c_gl_plane_flip(pt_this->h_plane, pt_this->pt_buf_thumb_show->h_view, TRUE);
    if(GLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_gl_plane_flip() failed. i4_ret = %d\r\n", i4_ret));

        mmp_pe_info_cmd_res_deinit();
        return MMPR_FAIL;
    }
#endif

    MMP_ASSERT(NULL == pt_this->pt_buf_crnt_disp);
    pt_this->pt_buf_crnt_disp = pt_this->pt_buf_thumb_show;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_info_cmd_res_reset
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_info_cmd_res_reset(VOID)
{
    /*GL_COLOR_T                  t_empty_clr;*/
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    INT32                       i4_ret;

    MMP_DBG_INFO(("[mmp] %s %d .\r\n",__FUNCTION__,__LINE__));

    //
    if(0 == (_MMP_PE_FLAG_THUMB_DISP_RESUMED & pt_this->ui4_flag))
    {
        return MMPR_OK;
    }


    //Clean thumbnail screen // NOTE set translte
    if(pt_this->h_thumbnail_surf)
    {

        GL_COLOR_T  t_empty_clr = {0, {0}, {0}, {0}};
        GL_RECT_T   st_rect;
        st_rect.i4_left = 0;
        st_rect.i4_top  = 0;
        st_rect.i4_bottom = pt_this->ui4_thumbanil_canvas_h;
        st_rect.i4_right  = pt_this->ui4_thumbanil_canvas_w;
        c_gl_surface_draw_rect(pt_this->h_thumbnail_surf,
                                &st_rect,
                                &t_empty_clr,
                                1,
                                GL_STYLE_FILLED,
                                GL_SYNC);

        // Flip Surface/View Data to Screen
        //c_gl_plane_flip(pt_this->h_thumbnail_plane, pt_this->h_thumbnail_view, TRUE);
    }



#ifdef MMP_PHOTO_USE_MI_MM_MODULE

    //clean XC screen
    if (MI_HANDLE_NULL != pt_this->h_MI_MM_Hdl)
    {
        //note: much mute disp, as xc is open
        MI_HANDLE hDisp = MI_HANDLE_NULL;
        MI_DISP_QueryHandleParams_t stDispHandleParam;
        memset(&stDispHandleParam, 0, sizeof(MI_DISP_QueryHandleParams_t));
        char szName[MI_MM_NAME_LENGTH] = {0};
        c_snprintf(szName, sizeof(szName), "MI_DISP_HD%d", 0);//0 1 2 3
        stDispHandleParam.pszName = (MI_U8*)szName;
        CHECK_RET(MI_DISP_GetHandle(&stDispHandleParam, &hDisp), MI_OK);
        CHECK_RET(MI_DISP_SetMute(hDisp, E_MI_DISP_MUTE_FLAG_VIDEO), MI_OK);
        //noto end

        CHECK_RET(MI_MM_ClearPhoto(pt_this->h_MI_MM_Hdl),"MI_MM_ClearPhoto");
        CHECK_RET(MI_MM_Stop(pt_this->h_MI_MM_Hdl),"MI_MM_Stop");
    }
#endif




    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_info_cmd_res_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_info_cmd_res_deinit(VOID)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    UINT32                      i;

    if(0 == (_MMP_PE_FLAG_THUMB_DISP_RESUMED & pt_this->ui4_flag))
    {
        return MMPR_OK;
    }

    if(_MMP_PE_FLAG_PLAY_DISP_RESUMED & pt_this->ui4_flag)
    {
        MMP_ASSERT(0);
        return MMPR_INTERNAL_ERROR;
    }

    /*stop loading thumbnail*/
    for(i = 0; i < MMP_PE_RC_INFO_INST_MAX_COUNT; i++)
    {
        if(0 != pt_this->at_info_inst[i].ui4_ver)
        {
            MMP_EXEC_WITH_ASSERT(mmp_pe_info_cmd_do(&pt_this->at_info_inst[i], MMP_FP_INFO_CMD_ID_STOP_THUMB, NULL), MMPR_OK);
        }
    }

    /*clean thumbnail and unlock buffer*/
    mmp_pe_info_cmd_res_reset();

    _mmp_pe_detach_display(pt_this);

    return _mmp_pe_suspend_disp_res(pt_this);
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_preview_start
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID mmp_pe_preview_start(GL_RECT_T*     pt_pre_rect)
{
    _MMP_PE_DATA_MEMBER_T*                  pt_this = &t_g_photo_eng;
#ifdef APP_3D_PHOTO_SUPPORT
    INT32   i4_w, i4_h;
#endif


    pt_this->ui4_flag |= _MMP_PE_FLAG_PREVIEW_MODE;

    pt_this->t_prew_rect.i4_left   = pt_pre_rect->i4_left;
    pt_this->t_prew_rect.i4_right  = pt_pre_rect->i4_right;
    pt_this->t_prew_rect.i4_top    = pt_pre_rect->i4_top;
    pt_this->t_prew_rect.i4_bottom = pt_pre_rect->i4_bottom;

    MMP_DBG_INFO(("[PhotoEng][mmp_pe_preview_start] Print preview rect.\r\n"));
    _mmp_pe_rect_print(pt_this->t_prew_rect);

#ifdef APP_3D_PHOTO_SUPPORT
    i4_w = pt_this->t_prew_rect.i4_right - pt_this->t_prew_rect.i4_left;
    i4_h = pt_this->t_prew_rect.i4_bottom - pt_this->t_prew_rect.i4_top;
    pt_this->t_prew_rect.i4_right -= (i4_w % 8) / 2;
    pt_this->t_prew_rect.i4_left += (i4_w % 8) - (i4_w % 8) / 2;
    pt_this->t_prew_rect.i4_bottom -= (i4_h % 8) / 2;
    pt_this->t_prew_rect.i4_top += (i4_h % 8) - (i4_h % 8) / 2;

    MMP_DBG_INFO(("[PhotoEng][mmp_pe_preview_start] Print preview rect after processing.\r\n"));
    _mmp_pe_rect_print(pt_this->t_prew_rect);
#endif

    return;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_preview_exit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID mmp_pe_preview_exit(VOID)
{
    _MMP_PE_DATA_MEMBER_T*                  pt_this = &t_g_photo_eng;

    mmp_pe_play_close();

    pt_this->ui4_flag &= ~(_MMP_PE_FLAG_PREVIEW_MODE);

    return;
}

static MI_BOOL __MI_MM_2k20_PlayPhoto(const CHAR* ps_filename);


/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_open
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_open(
    const CHAR*                 ps_filename,
    mmp_pe_play_nfy_fct         pf_nfy,
    VOID*                       pv_tag,
    UINT32                      ui4_ver)
{
    if(NULL == ps_filename)
    {
        MMP_DBG_ERROR(("ps_filename cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }

    MMP_ASSERT(NULL == t_g_photo_eng.pt_buf_crnt_disp);
    MMP_ASSERT(NULL == t_g_photo_eng.at_img[0].t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC]);
    MMP_ASSERT(NULL == t_g_photo_eng.at_img[1].t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC]);

    return _mmp_pe_play_do_open(&t_g_photo_eng, ps_filename, NULL, 0, pf_nfy, pv_tag, ui4_ver);
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_mopen
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_mopen(
    const UINT8*                pui1_buf,
    SIZE_T                      z_buf_size,
    mmp_pe_play_nfy_fct         pf_nfy,
    VOID*                       pv_tag,
    UINT32                      ui4_ver)
{
    if(NULL == pui1_buf || 0 == z_buf_size)
    {
        MMP_DBG_ERROR(("pui1_buf and z_buf_size cannot be 0.\r\n"));
        return MMPR_INV_ARG;
    }

    return _mmp_pe_play_do_open(&t_g_photo_eng, NULL, pui1_buf, z_buf_size, pf_nfy, pv_tag, ui4_ver);
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_close(VOID)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    INT32                       i;

    DBG_INFO_DIRECT("[mmp pe] %s %d h_MI_MM_Hdl:%d  ui1_crnt_img:%d \r\n",__FUNCTION__, __LINE__,pt_this->h_MI_MM_Hdl,pt_this->ui1_crnt_img);


    /**/
    if(_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
    {
        return MMPR_IS_CLOSED;
    }

    /*stop timer*/
    _mmp_pe_reset_play_timer(pt_this, 0, MMP_TIMER_OP_TYPE_STOP);


    //clean screen
    if (MI_HANDLE_NULL != pt_this->h_MI_MM_Hdl)
    {
        //note: much mute disp, as xc is open
        MI_HANDLE hDisp = MI_HANDLE_NULL;
        MI_DISP_QueryHandleParams_t stDispHandleParam;
        memset(&stDispHandleParam, 0, sizeof(MI_DISP_QueryHandleParams_t));
        char szName[MI_MM_NAME_LENGTH] = {0};
        c_snprintf(szName, sizeof(szName), "MI_DISP_HD%d", 0);//0 1 2 3
        stDispHandleParam.pszName = (MI_U8*)szName;
        CHECK_RET(MI_DISP_GetHandle(&stDispHandleParam, &hDisp), MI_OK);
        CHECK_RET(MI_DISP_SetMute(hDisp, E_MI_DISP_MUTE_FLAG_VIDEO), MI_OK);
        //noto end

        CHECK_RET(MI_MM_ClearPhoto(pt_this->h_MI_MM_Hdl),"MI_MM_ClearPhoto");
        CHECK_RET(MI_MM_Stop(pt_this->h_MI_MM_Hdl),"MI_MM_Stop");
        CHECK_RET(MI_MM_Close(pt_this->h_MI_MM_Hdl),"MI_MM_Close");
        pt_this->h_MI_MM_Hdl = MI_HANDLE_NULL;
    }


    /**/
    for(i = 0; i < _MMP_PE_IMAGE_FILE_MAX_COUNT; i++)
    {
        _mmp_pe_close_image(pt_this, &pt_this->at_img[i], FALSE);
    }

    /*detach current diaplay*/
    //_mmp_pe_detach_display(pt_this);

    /*viewport and surface*/
    _mmp_pe_suspend_disp_res(pt_this);

    pt_this->e_state = MMP_PLAY_STATE_CLOSED;
    pt_this->ui1_crnt_img = _MMP_PE_IMG_IDX_NULL;
    pt_this->ui4_flag &= ~(_MMP_PE_FLAG_NEXT_IS_PLAY | _MMP_PE_FLAG_FILE_NEXTING);

    return MMPR_IS_CLOSED;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_attr_set
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_attr_set(
    UINT32                      ui4_attr_count,
    const MMP_FP_SHOW_ATTR_T*   at_show_attr)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    UINT32                      i;

    pt_file = (_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img || 0 == pt_this->ui1_crnt_img) ? &pt_this->at_img[0] : &pt_this->at_img[1];

    DBG_INFO_DIRECT("[mmp pe] %s %d ui1_crnt_img:%d \r\n",__FUNCTION__,__LINE__,pt_this->ui1_crnt_img);

    for(i = 0; i < ui4_attr_count; i++)
    {
        switch(at_show_attr[i].e_id)
        {
        case MMP_FP_SHOW_ATTR_ID_DURATION:          /*pv_param: a UINT32 value in ms. ex: 5000 for 5 sec*/
            {
                pt_file->ui4_duration = (UINT32)at_show_attr[i].pv_param;

                if(MMP_PLAY_STATE_PLAYED == pt_this->e_state && 0 == (_MMP_PE_IMG_FLAG_IMG_DURING_EFFECT & pt_file->ui2_flag))
                {
                    _mmp_pe_reset_play_timer(pt_this, pt_this->ui1_crnt_img, MMP_TIMER_OP_TYPE_RESET);
                }
            }
            break;

        case MMP_FP_SHOW_ATTR_ID_EFFECT:            /*pv_param: a pointer to MMP_EFFECT_T struct*/
            {
                pt_file->t_effect = *((MMP_EFFECT_T*)at_show_attr[i].pv_param);
            }
            break;

        case MMP_FP_SHOW_ATTR_ID_SPEED:             /*pv_param: a INT32 value. 0: Normal speed, -1: 1/2, 1: 2*/
        default:
            return MMPR_NOT_SUPPORT;
        }
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_extra_attr_set
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_extra_attr_set(
    UINT32                      ui4_attr_count,
    const MMP_PE_EXTRA_ATTR_T*  at_extra_attr)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    UINT32                      i;

    pt_file = (_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img) ? &pt_this->at_img[0] : &pt_this->at_img[1];

    for(i = 0; i < ui4_attr_count; i++)
    {
        switch(at_extra_attr[i].e_extra_id)
        {
        case MMP_PE_EXTRA_ATTR_ID_ROTATION:          /*pv_extra_param: a pointer to MMP_PE_EXTRA_ATTR_ROTATE_T struct*/
            {
                MMP_PE_EXTRA_ATTR_ROTATE_T*     pt_rotate_attr = (MMP_PE_EXTRA_ATTR_ROTATE_T*)at_extra_attr[i].pv_extra_param;

                if(MMP_PE_EXTRA_ATTR_SRC_TYPE_FILE == pt_rotate_attr->e_src_type)
                {
                    pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_ROTATE_FROM_FILE;
                }
                else
                {
                    pt_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_ROTATE_FROM_FILE);
                    pt_file->e_rotate = pt_rotate_attr->e_assign_degree;
                }
            }
            break;

        case MMP_PE_EXTRA_ATTR_ID_FORCE_ROTATE_OP:
            {
                pt_file->e_force_rotate_op = (MMP_FP_LOAD_IMG_ROTATE_OP_T)(UINT32)at_extra_attr[i].pv_extra_param;
            }
            break;

        default:
            return MMPR_NOT_SUPPORT;
        }
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_next_preload
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_next_preload(
    const CHAR*                 ps_filename)
{
    return mmp_pe_play_do_next_preload(&t_g_photo_eng, ps_filename, NULL, 0);
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_next_mpreload
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_next_mpreload(
    const UINT8*                pui1_buf,
    SIZE_T                      z_buf_size)
{
    return mmp_pe_play_do_next_preload(&t_g_photo_eng, NULL, pui1_buf, z_buf_size);
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_next_attr_set
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_next_attr_set(
    UINT32                      ui4_attr_count,
    const MMP_FP_SHOW_ATTR_T*   at_show_attr)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    UINT32                      i;

    MMP_DBG_INFO(("[mmp] %s %d  \r\n",__FUNCTION__,__LINE__));

    pt_file = (_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img || 1 == pt_this->ui1_crnt_img) ? &pt_this->at_img[0] : &pt_this->at_img[1];

    for(i = 0; i < ui4_attr_count; i++)
    {
        switch(at_show_attr[i].e_id)
        {
        case MMP_FP_SHOW_ATTR_ID_DURATION:          /*pv_param: a UINT32 value in ms. ex: 5000 for 5 sec*/
            {
                pt_file->ui4_duration = (UINT32)at_show_attr[i].pv_param;
            }
            break;

        case MMP_FP_SHOW_ATTR_ID_EFFECT:            /*pv_param: a pointer to MMP_EFFECT_T struct*/
            {
                pt_file->t_effect = *((MMP_EFFECT_T*)at_show_attr[i].pv_param);
            }
            break;

        case MMP_FP_SHOW_ATTR_ID_SPEED:             /*pv_param: a INT32 value. 0: Normal speed, -1: 1/2, 1: 2*/
        default:
            return MMPR_NOT_SUPPORT;
        }
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_next_extra_attr_set
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_next_extra_attr_set(
    UINT32                      ui4_attr_count,
    const MMP_PE_EXTRA_ATTR_T*  at_extra_attr)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    UINT32                      i;

    pt_file = (_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img || 1 == pt_this->ui1_crnt_img) ? &pt_this->at_img[0] : &pt_this->at_img[1];

    for(i = 0; i < ui4_attr_count; i++)
    {
        switch(at_extra_attr[i].e_extra_id)
        {
        case MMP_PE_EXTRA_ATTR_ID_ROTATION:          /*pv_extra_param: a pointer to MMP_PE_EXTRA_ATTR_ROTATE_T struct*/
            {
                MMP_PE_EXTRA_ATTR_ROTATE_T*     pt_rotate_attr = (MMP_PE_EXTRA_ATTR_ROTATE_T*)at_extra_attr[i].pv_extra_param;

                if(MMP_PE_EXTRA_ATTR_SRC_TYPE_FILE == pt_rotate_attr->e_src_type)
                {
                    pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_ROTATE_FROM_FILE;
                }
                else
                {
                    pt_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_ROTATE_FROM_FILE);
                    pt_file->e_rotate = pt_rotate_attr->e_assign_degree;
                }
            }
            break;

        case MMP_PE_EXTRA_ATTR_ID_FORCE_ROTATE_OP:
            {
                pt_file->e_force_rotate_op = (MMP_FP_LOAD_IMG_ROTATE_OP_T)(UINT32)at_extra_attr[i].pv_extra_param;
            }
            break;

        default:
            return MMPR_NOT_SUPPORT;
        }
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_start
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_start(VOID)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;

    /*check status*/
    if(MMP_PLAY_STATE_PLAYED == pt_this->e_state)
    {
        return MMPR_IS_PLAYED;
    }
    else if(MMP_PLAY_STATE_PLAYING == pt_this->e_state)
    {
        return MMPR_OK;
    }

    MMP_DBG_INFO(("[Photo/PlayStart] mmp_pe_play_start.\r\n"));


                        //if((_MMP_PE_IMG_FLAG_IMG_LOADING | _MMP_PE_IMG_FLAG_THUMB_LOADING) & pt_file->ui2_flag)
                        //{
                        //  MMP_DBG_INFO(("Photo is loading..........\r\n"));
                        //  return MMPR_OK;
                        //}
    /*reset timer*/
    _mmp_pe_reset_play_timer(pt_this, 0, MMP_TIMER_OP_TYPE_RESET);

    _mmp_pe_update_state(pt_this, _MMP_PE_STATE_UPDATE_TYPE_VIEW, MMPR_OK, TRUE);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_pause
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_pause(VOID)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    INT32                       i4_ret;

    MMP_DBG_INFO(("[Photo/PlayPause] mmp_pe_play_pause.  pt_this->ui1_crnt_img = %d. \r\n",pt_this->ui1_crnt_img));

    /*check file*/
    if(_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
    {
        MMP_DBG_ERROR(("No photo is opened.\r\n"));
        return MMPR_NO_DATA;
    }

    if(pt_this->ui1_crnt_img >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        return MMPR_FAIL;
    }
    pt_file = &pt_this->at_img[pt_this->ui1_crnt_img];

    MMP_DBG_INFO(("[Photo/PlayPause] pt_file->ui2_flag = 0x%x.\r\n", pt_file->ui2_flag));

    /*clean next is play or not flag*/
    pt_this->ui4_flag &= ~(_MMP_PE_FLAG_NEXT_IS_PLAY);

    i4_ret = _mmp_pe_pause_image(pt_this, pt_file);
    if(MMPR_IS_PAUSED == i4_ret)
    {
        pt_this->e_state = MMP_PLAY_STATE_PAUSED;
    }
    else if(MMPR_OK == i4_ret)
    {
        pt_this->e_state = MMP_PLAY_STATE_PAUSING;
    }
    else /*error*/
    {
        pt_this->e_state = MMP_PLAY_STATE_STOPPED;
    }

    MMP_DBG_INFO(("[Photo/PlayPause] pt_this->e_state = %d. pt_this->ui4_flag = 0x%x.\r\n", pt_this->e_state, pt_this->ui4_flag));
    MMP_DBG_INFO(("[Photo/PlayPause] pt_file->ui2_flag = 0x%x.\r\n", pt_file->ui2_flag));

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_stop
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_stop(VOID)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    INT32                       i4_ret;

    DBG_INFO_DIRECT("[mmp pe] %s %d .\r\n",__FUNCTION__, __LINE__);

    /*check file*/
    if(_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
    {
        MMP_DBG_ERROR(("[mmp] %s %d No photo is opened.\r\n",__FUNCTION__, __LINE__));
        return MMPR_NO_DATA;
    }

    if(pt_this->ui1_crnt_img >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        return MMPR_FAIL;
    }
    pt_file = &pt_this->at_img[pt_this->ui1_crnt_img];


    /*clean next is play or not flag*/
    pt_this->ui4_flag &= ~(_MMP_PE_FLAG_NEXT_IS_PLAY);

    i4_ret = _mmp_pe_pause_image(pt_this, pt_file);
    if(MMPR_IS_PAUSED == i4_ret)
    {
        pt_this->e_state = MMP_PLAY_STATE_STOPPED;
        i4_ret = MMPR_IS_STOPPED;
    }
    else if(MMPR_OK == i4_ret)
    {
        pt_this->e_state = MMP_PLAY_STATE_STOPPING;
    }
    else /*error*/
    {
        pt_this->e_state = MMP_PLAY_STATE_STOPPED;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_clean
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_clean(VOID)
{
    /*GL_COLOR_T                  t_empty_clr;*/
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    INT32                       i4_ret;

    MMP_DBG_INFO(("[Photo/PlayClean] mmp_pe_play_clean.\r\n"));

    /**/
    if(0 == (_MMP_PE_FLAG_PLAY_DISP_RESUMED & pt_this->ui4_flag) || NULL == pt_this->pt_buf_crnt_disp)
    {
        return MMPR_OK;
    }



#if 0
    /*clean surface*/
    _MMP_PE_ZERO_COLOR(t_empty_clr, 0);
    i4_ret = c_gl_surface_fill(pt_this->at_disp_pool[pt_this->ui1_crnt_disp].h_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d.\r\n", i4_ret));
        return MMPR_INTERNAL_ERROR;
    }
#endif

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_next
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_next(UINT32 ui4_ver)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    INT32                       i4_ret;
    UINT32                      ui4_next_img,ui4_old_ver;
    BOOL                        b_is_play, b_show_thumb, b_reload = FALSE;

    ui4_next_img = (UINT32)((_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img || 1 == pt_this->ui1_crnt_img) ? 0 : 1);
    pt_file = &pt_this->at_img[ui4_next_img];



    // close current play
    if(MMP_PLAY_STATE_PLAYING == pt_this->e_state || MMP_PLAY_STATE_PLAYED == pt_this->e_state)
    {
        b_is_play = TRUE;
        i4_ret = mmp_pe_play_stop();
        if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
        {
            MMP_DBG_ERROR(("[mmp] %s %d mmp_pe_play_stop() failed. i4_ret = %d\r\n",__FUNCTION__, __LINE__, i4_ret));
        }
    }
    else
    {
        b_is_play = (_MMP_PE_FLAG_NEXT_IS_PLAY & pt_this->ui4_flag) ? TRUE : FALSE;
    }

    DBG_INFO_DIRECT("[mmp pe] %s %d ui1_crnt_img = %d. ui4_next_img = %d . b_is_play : %d \r\n",__FUNCTION__, __LINE__, pt_this->ui1_crnt_img, 0, b_is_play);



    /*switch to next file*/
    pt_this->ui1_crnt_img = (UINT8)ui4_next_img;

    /*update play version*/
    ui4_old_ver = pt_this->ui4_play_ver;
    pt_this->ui4_play_ver = ui4_ver;


    if(b_is_play)
    {
        // reset timer ---- slider show play
        _mmp_pe_reset_play_timer(pt_this, ui4_next_img, MMP_TIMER_OP_TYPE_RESET);

        _mmp_pe_update_state(pt_this, _MMP_PE_STATE_UPDATE_TYPE_VIEW, MMPR_OK, TRUE);
    }


    if(MMP_PLAY_STATE_STOPPED == pt_this->e_state || MMP_PLAY_STATE_PAUSED == pt_this->e_state)
    {
        MMP_ASSERT(_MMP_PE_IMG_IDX_NULL != pt_this->ui1_crnt_img);

        if(pt_this->ui1_crnt_img >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
        {
            return MMPR_FAIL;
        }
        //_mmp_pe_close_image(pt_this, &pt_this->at_img[pt_this->ui1_crnt_img], TRUE);
        /*pt_this->e_state = MMP_PLAY_STATE_NO_FILE;*/
    }
    else /*MMP_PLAY_STATE_PAUSING or MMP_PLAY_STATE_STOPPING*/
    {
        pt_this->ui4_flag |= _MMP_PE_FLAG_FILE_NEXTING;

        if(b_is_play)
        {
            pt_this->ui4_flag |= _MMP_PE_FLAG_NEXT_IS_PLAY;
        }

        /*update play version*/
        pt_this->ui4_play_ver = ui4_ver;

        return MMPR_OK;
    }

    i4_ret = (b_is_play) ? MMPR_IS_PLAYED : MMPR_IS_STOPPED;
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_rotate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_rotate(
    IMG_ROTATE_OP_TYPE_T        e_degree)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    INT32                       i4_ret = MMPR_OK, i4_save_ret = MMPR_OK;

    DBG_INFO_DIRECT("[mmp pe] %s %d e_degree:%d ui1_crnt_img:%d\r\n",__FUNCTION__,__LINE__, e_degree, pt_this->ui1_crnt_img);

    /*check file*/
    if(_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
    {
        MMP_DBG_ERROR(("mmp] %s %d No photo is opened.\r\n"));
        return MMPR_NO_DATA;
    }

    if(pt_this->ui1_crnt_img >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        return MMPR_FAIL;
    }

    pt_file = &pt_this->at_img[pt_this->ui1_crnt_img];

    //not support 2 buf mpo file rotation, because driver not support YUV422 decoding with rotation
    if (pt_file->e_img_type == IMG_MPO && (_MMP_PE_FLAG_QUICK_ROTATE & pt_this->ui4_flag) == 0)
    {
        return MMPR_NOT_SUPPORT_ROTATE;
    }


    /*check file content*/
    if((_MMP_PE_IMG_FLAG_NOT_SUPPORT_FILE | _MMP_PE_IMG_FLAG_BAD_FILE)  & pt_file->ui2_flag)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Photo is bad or not supported.\r\n",__FUNCTION__,__LINE__));
        return MMPR_NOT_SUPPORT;
    }

    /*check image ready*/
    if(_MMP_PE_IMG_FLAG_IMG_LOADING & pt_file->ui2_flag)
    {
        MMP_DBG_ERROR(("[mmp] %s %d During loading, rotation is disabled.\r\n",__FUNCTION__,__LINE__));
        return MMPR_RES_NOT_READY;
    }

    /*check status*/
    if(MMP_PLAY_STATE_STOPPED != pt_this->e_state && MMP_PLAY_STATE_PAUSED != pt_this->e_state)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Not stopped or paused, rotation is disabled.\r\n",__FUNCTION__,__LINE__));
        return MMPR_RES_NOT_READY;
    }


    //NOTE : save ====> no surport
#if 0
    if(IMG_JPG == pt_file->e_img_type)
    {
        i4_ret = _mmp_pe_save_rotation(pt_file);
        if(MMPR_OK != i4_ret && MMPR_NO_DATA != i4_ret)
        {
            return i4_ret;
        }
        i4_save_ret = i4_ret;
    }
    else
    {
        i4_save_ret = MMPR_NO_DATA;
    }
#endif

    /**/
    if(_MMP_PE_FLAG_QUICK_ROTATE & pt_this->ui4_flag)
    {
        pt_this->ui4_flag |= _MMP_PE_FLAG_IS_PLAYING_ZOOM_ROTATE;

#ifdef MMP_PHOTO_USE_MI_MM_MODULE
        if(pt_this->h_MI_MM_Hdl == MI_HANDLE_NULL)
        {
            MMP_DBG_INFO(("[mmp] %s %d [pt_this.h_MI_MM_Hdl == MI_HANDLE_NULL]  need MI_MM_GetHandle!!\r\n",__FUNCTION__,__LINE__));
            // open MI_MM
            char szMmName[32] = {0};
            MI_MM_QueryHandleParams_t stQueryHandleParams;
            memset(&stQueryHandleParams, 0, sizeof(stQueryHandleParams));
            memset(&szMmName, 0, sizeof(szMmName));
            c_snprintf(szMmName, sizeof(szMmName), MI_MM_PHOTO_HANDLE);
            stQueryHandleParams.pszName = (MI_U8 *)szMmName;
            stQueryHandleParams.eMediaType = E_MI_MM_MEDIA_PHOTO;
            i4_ret = MI_MM_GetHandle(&stQueryHandleParams, &(pt_this->h_MI_MM_Hdl));\
            if(i4_ret != MI_OK || pt_this->h_MI_MM_Hdl == MI_HANDLE_NULL)
            {
                MMP_DBG_INFO(("[mmp] %s %d MI_MM_GetHandle Error!!\r\n",__FUNCTION__,__LINE__));
                return MMPR_FAIL;
            }

        }
        // left rotate    0 - 7 - 5 - 2 - 0
        DBG_INFO_DIRECT("[mmp pe] %s %d pt_file->e_img_type = %d.\r\n",__FUNCTION__,__LINE__, IMG_GIF);
        //Set Strecth Mode and Image play rotate angle
        MI_MM_RotateAngle_e eAngle = MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE;
        MI_MM_PhotoStretchMode_e AttrParams = E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN;

		//set/save rotate
		pt_file->e_rotate = e_degree;

        switch(pt_file->e_rotate)
        {
            case IMG_ROTATE_CLOCKWS_0_OP_TYPE:
            case IMG_ROTATE_CLOCKWS_0_OP_TYPE_WITH_FLIP:
                eAngle = E_MI_MM_ROTATE_0;
                break;
            case IMG_ROTATE_CLOCKWS_90_OP_TYPE:
            case IMG_ROTATE_CLOCKWS_90_OP_TYPE_WITH_FLIP:
                eAngle = E_MI_MM_ROTATE_90;
                break;
            case IMG_ROTATE_CLOCKWS_180_OP_TYPE:
            case IMG_ROTATE_CLOCKWS_180_OP_TYPE_WITH_FLIP:
                eAngle = E_MI_MM_ROTATE_180;
                break;
            case IMG_ROTATE_CLOCKWS_270_OP_TYPE:
            case IMG_ROTATE_CLOCKWS_270_OP_TYPE_WITH_FLIP:
                eAngle = E_MI_MM_ROTATE_270;
                break;
            default:
                eAngle = E_MI_MM_ROTATE_0;
                break;
        }

        //note: 3840*2160 / 1920*1080 image if strecth is E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN will cannot full screen, because data will be align 16
        if(eAngle != E_MI_MM_ROTATE_90 && eAngle !=E_MI_MM_ROTATE_270 && pt_file->z_img_w%1920 == 0 && pt_file->z_img_h%1080 == 0)
            AttrParams = E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN_STRETCH;
        else
            AttrParams = E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN;
        CHECK_RET(MI_MM_SetAttr(pt_this->h_MI_MM_Hdl,E_MI_MM_ATTR_TYPE_SET_PHOTO_DISPALY_STRECTH_MODE, (void *)AttrParams),"MI_MM_SetAttr");

        //
        if(IMG_GIF != pt_file->e_img_type)
        {
            i4_ret= MI_MM_RotatePhoto(pt_this->h_MI_MM_Hdl, eAngle);
            if(i4_ret>=MI_ERR_FAILED)
            {
                return MMPR_FAIL;
            }
        }
        else
        {
            //if gif rotate, need decode /draw play again
            i4_ret=_mmp_pe_load_image(pt_this, pt_this->ui1_crnt_img);
            if(i4_ret != MMPR_OK)
            {
                MMP_DBG_INFO(("[mmp] %s %d _mmp_pe_load_image Error!!\r\n",__FUNCTION__,__LINE__));
                return i4_ret;
            }
        }
#endif
        pt_this->ui4_flag &= ~(_MMP_PE_FLAG_IS_PLAYING_ZOOM_ROTATE);
        if(MMPR_OK == i4_ret)
        {
            //return (MMPR_NO_DATA == i4_save_ret) ? i4_save_ret : MMPR_IS_ROTATED;
            //CID:4632700, "i4_save_ret" must be equal to "MMPR_OK"
            return MMPR_IS_ROTATED;
        }
    }
    return i4_ret;
}


/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_zoom
 *
 * Description: i4_ratio: (screen : zoom). 1250: 1: 1.25
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_zoom(
    const GL_POINT_T*           pt_center_offset,
    UINT32                      ui4_ratio)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;

    // Fix coverity CID-4632706: Uninitialized scalar variable
    INT32                       i4_ret = MMPR_OK;

#ifdef APP_3D_MODE_SUPPORT
#ifdef APP_3D_PHOTO_SUPPORT
    INT16                       i2_idx = 0;
#endif
#endif

    MMP_DBG_INFO(("[Photo/Zoom] mmp_pe_play_zoom. ui4_ratio = %d\r\n", ui4_ratio));

    /*check param*/
    if(NULL == pt_center_offset)
    {
        MMP_DBG_ERROR(("pt_center_offset cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }
    if(0 != pt_center_offset->i4_x || 0 != pt_center_offset->i4_y)
    {
        MMP_DBG_ERROR(("Not support Center Offset now.\r\n"));
        return MMPR_NOT_SUPPORT;
    }

    /*check file*/
    if(_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
    {
        MMP_DBG_ERROR(("No photo is opened.\r\n"));
        return MMPR_NO_DATA;
    }

    if(pt_this->ui1_crnt_img >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        return MMPR_FAIL;
    }

    pt_file = &pt_this->at_img[pt_this->ui1_crnt_img];

#ifdef APP_3D_MODE_SUPPORT
#ifdef APP_3D_PHOTO_SUPPORT
    /*if the mode is not off, disable zoom function*/
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                 &i2_idx);
    if (i2_idx != 0) //SCC_3D_MODE_OFF == 0
    {
        MMP_DBG_INFO(("\n3D mode is %d, not support zoom.\n", i2_idx));
        return MMPR_NOT_SUPPORT_ZOOM;
    }
#endif
#endif
    /*check file content*/
    if((_MMP_PE_IMG_FLAG_NOT_SUPPORT_FILE | _MMP_PE_IMG_FLAG_BAD_FILE)  & pt_file->ui2_flag)
    {
        MMP_DBG_ERROR(("Photo is bad or not supported.\r\n"));
        return MMPR_NOT_SUPPORT;
    }

    /*check image ready*/
    if(_MMP_PE_IMG_FLAG_IMG_LOADING & pt_file->ui2_flag)
    {
        MMP_DBG_ERROR(("During loading, zooming is disabled.\r\n"));
        return MMPR_RES_NOT_READY;
    }

    /*check status*/
    if(MMP_PLAY_STATE_STOPPED != pt_this->e_state && MMP_PLAY_STATE_PAUSED != pt_this->e_state)
    {
        MMP_DBG_ERROR(("Not stopped or paused, zooming is disabled.\r\n"));
        return MMPR_RES_NOT_READY;
    }

    /*check effect*/
    if(_MMP_PE_IMG_FLAG_IMG_DURING_EFFECT & pt_file->ui2_flag)
    {
        //i4_ret = c_img_tfx_stop(pt_file->h_tfx);
        //if(IMGR_OK != i4_ret && IMGR_ALREADY_STOP != i4_ret)
        //{
        //    MMP_DBG_ERROR(("c_img_tfx_stop() failed. i4_ret = %d\r\n", i4_ret));
        //    MMP_ASSERT(0);
//
        //    return MMPR_RES_NOT_READY;
        //}

        pt_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_IMG_DURING_EFFECT);
    }

    pt_file->ui4_zoom = ui4_ratio;
    pt_file->t_center_offset = *pt_center_offset;

    /**/
    if(_MMP_PE_FLAG_QUICK_ROTATE & pt_this->ui4_flag)
    {
        pt_this->ui4_flag |= _MMP_PE_FLAG_ANIMATION_GIF_NEED_CLEAN;
        pt_this->ui4_flag |= _MMP_PE_FLAG_IS_PLAYING_ZOOM_ROTATE;
        pt_this->ui4_flag &= ~(_MMP_PE_FLAG_ANIMATION_GIF_NEED_CLEAN);
        pt_this->ui4_flag &= ~(_MMP_PE_FLAG_IS_PLAYING_ZOOM_ROTATE);

        if(pt_file->b_animation_gif)
        {



            // set zoom flag
            pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_IMG_ZOOMING;

            // clean buffer
            ///
            ///
            ///
            ///
            ///
        }

#ifdef LINUX_AUTO_TEST
        if (i4_ret == MMPR_OK)
        {
            CREATE_MMP_TMP_FILE(MMP_PHOTO_ZOOM_DONE_FILE);
        }
#endif
        return (MMPR_OK != i4_ret) ? i4_ret : MMPR_IS_ZOOMED;
    }
    else
    {
        i4_ret = _mmp_pe_normal_scale_image(pt_this, pt_file);
        if(MMPR_OK == i4_ret)
        {
            pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_IMG_ZOOMING;
        }
        else
        {
            pt_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_IMG_ZOOMING);
        }

        return i4_ret;
    }
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_get_file
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_get_file(
    MMP_PE_FILE_IDX_T           e_idx,
    CHAR**                      pps_name)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    UINT32                      ui4_img;
    INT32                       i4_ret;

    /*check param*/
    if(MMP_PE_FILE_IDX_TOTAL == e_idx || NULL == pps_name)
    {
        MMP_DBG_ERROR(("e_idx cannot be MMP_PE_FILE_IDX_TOTAL and pps_name cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }

    /*get target file*/
    if(MMP_PE_FILE_IDX_CURRENT == e_idx)
    {
        if(_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
        {
            MMP_DBG_ERROR(("No file is active.\r\n"));
            return MMPR_NO_DATA;
        }

        ui4_img = pt_this->ui1_crnt_img;
    }
    else /*MMP_PE_FILE_IDX_NEXT*/
    {
        ui4_img = (UINT32)((_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img || 1 == pt_this->ui1_crnt_img) ? 0 : 1);
    }

    if(ui4_img >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        return MMPR_FAIL;
    }
    pt_file = &pt_this->at_img[ui4_img];

    /*check id*/
    if(MMP_FID_NULL_REC_IDX == pt_file->t_path)
    {
        MMP_ASSERT(pt_this->ui1_crnt_img != ui4_img || 0 != (_MMP_PE_IMG_FLAG_MEM_FILE & pt_file->ui2_flag));

        MMP_DBG_ERROR(("There's no file for image-%d.\r\n", ui4_img));
        return MMPR_NO_DATA;
    }

    /*get path*/
    i4_ret = mmp_fid_get(pt_file->t_path, pps_name);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_fid_get(%d) failed. i4_ret = %d.\r\n", pt_file->t_path, i4_ret));
        MMP_ASSERT(0);
        return i4_ret;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_get_file_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_get_file_info(
    MMP_PE_FILE_IDX_T           e_idx,
    MMP_FP_INFO_TYPE_T          e_type,
    SIZE_T*                     pz_size,
    UINT8*                      pui1_buf)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    UINT32                      ui4_img;
    INT32                       i4_ret;
    BOOL                        b_try_next = FALSE;
    _MMP_IMAGE_INFO             ExifInfo = {0};
    CHAR *ps_path;

    MMP_DBG_INFO(("[%s %d] e_idx:%d  e_type:%d\r\n", __FUNCTION__,__LINE__,e_idx,e_type));


    /*check param*/
    if(MMP_PE_FILE_IDX_TOTAL == e_idx || NULL == pz_size || NULL == pui1_buf)
    {
        MMP_DBG_ERROR(("e_idx cannot be MMP_PE_FILE_IDX_TOTAL and pz_size cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }

    /*get target file*/
    if(MMP_PE_FILE_IDX_CURRENT == e_idx)
    {
        if(_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
        {
            MMP_DBG_ERROR(("No file is active.\r\n"));
            return MMPR_NO_DATA;
        }
        ui4_img = pt_this->ui1_crnt_img;
    }
    else /*MMP_PE_FILE_IDX_NEXT*/
    {
        ui4_img = (UINT32)((_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img || 1 == pt_this->ui1_crnt_img) ? 0 : 1);
    }

    if(ui4_img >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        return MMPR_FAIL;
    }
    pt_file = &pt_this->at_img[ui4_img];


    if(MMP_FP_INFO_TYPE_TITLE == e_type)
    {
        if(MMP_FID_NULL_REC_IDX == pt_file->t_path)
        {
            return MMPR_NO_DATA;
        }
        else
        {
            return _mmp_pe_get_info_title(pt_file->t_path, pz_size, pui1_buf);
        }
    }
    else if(MMP_FP_INFO_TYPE_FLODER == e_type)
    {
        if(MMP_FID_NULL_REC_IDX == pt_file->t_path)
        {
            return MMPR_NO_DATA;
        }
        else
        {
            return _mmp_pe_get_parent(pt_file->t_path, pz_size, pui1_buf);
        }
    }

    /**/
    if(_MMP_PE_IMG_FLAG_BAD_FILE & pt_file->ui2_flag)
    {
        return MMPR_NO_DATA;
    }

    switch(e_type)
    {
        case MMP_FP_IFNO_TYPE_CAMERA:
            if(0 == *pz_size || NULL == pui1_buf)
            {
                *pz_size = 0;
                return MMPR_BUF_NOT_ENOUGH;
            }
            if(pt_this->t_image_info.CameraModel[0] != 0)
            {
                *pz_size = sizeof(pt_this->t_image_info.CameraModel);
                memcpy((void *)pui1_buf,(const void *)(pt_this->t_image_info.CameraModel),*pz_size);
            }
            return MMPR_OK;
        case MMP_FP_INFO_TYPE_EXPOSURE_TIME:
            if(0 == *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(float);
                return MMPR_BUF_NOT_ENOUGH;
            }
            *pz_size = sizeof(float);
            *((float*)pui1_buf) = pt_this->t_image_info.ExposureTime;
            return MMPR_OK;
        case MP_FP_INFO_TYPE_ISO_SENSITIVITY:
            if(0 == *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(int);
                return MMPR_BUF_NOT_ENOUGH;
            }
            *pz_size = sizeof(int);
            *((int*)pui1_buf) = pt_this->t_image_info.ISOequivalent;
            return MMPR_OK;
        case MP_FP_INFO_TYPE_FLASH_MODE:
            if(0 == *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(int);
                return MMPR_BUF_NOT_ENOUGH;
            }
            *pz_size = sizeof(int);
            *((int*)pui1_buf) = pt_this->t_image_info.FlashUsed;
            return MMPR_OK;
        case MMP_FP_INFO_TYPE_EXPOSURE_PROGRAM:
            if(0 == *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(int);
                return MMPR_BUF_NOT_ENOUGH;
            }
            *pz_size = sizeof(int);
            *((int*)pui1_buf) = pt_this->t_image_info.ExposureProgram;
            return MMPR_OK;
        case MP_FP_INFO_TYPE_EXPOSURE_BIAS:
            if(0 == *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(float);
                return MMPR_BUF_NOT_ENOUGH;
            }
            *pz_size = sizeof(float);
            *((float*)pui1_buf) = pt_this->t_image_info.ExposureBias;
            return MMPR_OK;

        case MMP_FP_INFO_TYPE_ALBUM:
            if(MMP_FID_NULL_REC_IDX == pt_file->t_path)
            {
                return MMPR_NO_DATA;
            }
            else
            {
                return _mmp_pe_get_parent(pt_file->t_path, pz_size, pui1_buf);
            }

        case MMP_FP_INFO_TYPE_CREATE_TIME:
        case MMP_FP_INFO_TYPE_LAST_WRITE_TIME:
        case MMP_FP_INFO_TYPE_PROTECT:
        case MMP_FP_INFO_TYPE_SIZE:
            return _mmp_pe_get_info_file_info(pt_file->t_path, &pt_file->t_file_info, e_type, pz_size, pui1_buf);

        case MMP_FP_INFO_TYPE_ROTATION:
            if(0 == *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(IMG_ROTATE_OP_TYPE_T);
                return MMPR_BUF_NOT_ENOUGH;
            }
            *((IMG_ROTATE_OP_TYPE_T*)pui1_buf) = pt_file->e_rotate;
            return MMPR_OK;

        case MMP_FP_INFO_TYPE_TYPE:
            if(0 == *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(IMG_TYPE_T);
                return MMPR_BUF_NOT_ENOUGH;
            }
            *((IMG_TYPE_T*)pui1_buf) = pt_file->e_img_type;
            return MMPR_OK;

        case MMP_FP_INFO_TYPE_RESOLUTION:
            if(0 == *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(GL_SIZE_T);
                return MMPR_BUF_NOT_ENOUGH;
            }
            if(pt_file->z_img_w != 0 && pt_file->z_img_h != 0)
            {
                ((GL_SIZE_T*)pui1_buf)->ui4_width  = pt_file->z_img_w;
                ((GL_SIZE_T*)pui1_buf)->ui4_height = pt_file->z_img_h;
            }
            else
            {
                ((GL_SIZE_T*)pui1_buf)->ui4_width  = pt_this->t_image_info.Width;
                ((GL_SIZE_T*)pui1_buf)->ui4_height = pt_this->t_image_info.Height;
            }

            return MMPR_OK;

        default:
            return MMPR_NO_DATA;
    }

    // Coverity-4490563: Structurally dead code
    //return (IMGR_INSUFFICIENT_BUFFER == i4_ret) ? MMPR_BUF_NOT_ENOUGH : MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_get_curnt_surf
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_get_curnt_surf(HANDLE_T*   ph_curt_surf,
                          HANDLE_T*   ph_next_surf)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    UINT32                      ui4_img;


    if(NULL == ph_curt_surf)
    {
        return MMPR_INV_ARG;
    }

    if(NULL_HANDLE == t_g_photo_eng.pt_buf_crnt_disp->h_surf)
    {
        return MMPR_FAIL;
    }

    *ph_curt_surf = t_g_photo_eng.pt_buf_crnt_disp->h_surf;

    ui4_img = (UINT32)((_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img || 1 == pt_this->ui1_crnt_img) ? 0 : 1);
    pt_file = &pt_this->at_img[ui4_img];

    //i4_ret = c_img_stop(pt_file->h_img, IMG_STOP_PRIMARY_OP_TYPE);
    //if(IMGR_OK != i4_ret && IMGR_ALREADY_STOP != i4_ret)
    //{
    //    return MMPR_FAIL;
    //}

    //mmp_drc_unlock_buf(pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC]);

    *ph_next_surf = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC]->h_surf;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_get_curnt_surf
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_restart_preload(VOID)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    //UINT32                      ui4_img;

    MMP_DBG_INFO(("[Photo/RestartPreload] mmp_pe_restart_preload.\r\n"));

    //ui4_img = (UINT32)((_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img || 1 == pt_this->ui1_crnt_img) ? 0 : 1);

    /*reloading next image again*/
    pt_this->pf_play_nfy(pt_this->pv_play_nfy_tag, pt_this->ui4_play_ver, MMP_PE_PLAY_NFY_ID_RES_BUSY, (VOID*)NULL);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_get_file_extra_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_pe_play_get_file_extra_info(
    MMP_PE_FILE_IDX_T           e_idx,
    MMP_PE_EXTRA_INFO_ID_T      e_id,
    SIZE_T*                     pz_size,
    VOID*                       pv_param)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file;
    UINT32                      ui4_img;
    INT32                       i4_ret;

    /*check param*/
    if(MMP_PE_FILE_IDX_TOTAL == e_idx || NULL == pz_size)
    {
        MMP_DBG_ERROR(("e_idx cannot be MMP_PE_FILE_IDX_TOTAL and pz_size cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }

    /*get target file*/
    if(MMP_PE_FILE_IDX_CURRENT == e_idx)
    {
        if(_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
        {
            MMP_DBG_ERROR(("No file is active.\r\n"));
            return MMPR_NO_DATA;
        }
        ui4_img = pt_this->ui1_crnt_img;
    }
    else /*MMP_PE_FILE_IDX_NEXT*/
    {
        ui4_img = (UINT32)((_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img || 1 == pt_this->ui1_crnt_img) ? 0 : 1);
    }

    if(ui4_img >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        return MMPR_FAIL;
    }

    pt_file = &pt_this->at_img[ui4_img];

    switch(e_id)
    {
    case MMP_PE_EXTRA_INFO_ID_PATH:
        {
            if(MMP_FID_NULL_REC_IDX == pt_file->t_path)
            {
                return MMPR_NO_DATA;
            }
            else if(NULL == pv_param)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }
            else
            {
                _mmp_pe_get_file_path(pt_file, pz_size, (UINT8*)pv_param);
            }
        }
        return MMPR_OK;

    case MMP_PE_EXTRA_INFO_ID_HAVE_THUMB:
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(BOOL);
            i4_ret = _mmp_pe_get_file_have_thumb(pt_file, (BOOL*)pv_param);
            if(MMPR_OK != i4_ret)
            {
                return MMPR_FAIL;
            }
        }
        return MMPR_OK;
    case MMP_PE_EXTRA_INFO_ID_IS_READY:
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }
            MMP_DBG_INFO(("[mmp] %s %d <MMP_PE_EXTRA_INFO_ID_IS_READY>  ui2_flag = 0x%x\r\n",__FUNCTION__,__LINE__,pt_file->ui2_flag));
            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = (0 != ((_MMP_PE_IMG_FLAG_IMG_LOADING | _MMP_PE_IMG_FLAG_IMG_LOADING_SUSPEND | _MMP_PE_IMG_FLAG_THUMB_LOADING) & pt_file->ui2_flag)) ? FALSE : TRUE;
        }
        return MMPR_OK;

    case MMP_PE_EXTRA_INFO_ID_IS_SUPPORTED:
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = (0 != ((_MMP_PE_IMG_FLAG_IMG_CORRUPT | _MMP_PE_IMG_FLAG_BAD_FILE |
                _MMP_PE_IMG_FLAG_NOT_SUPPORT_FILE | _MMP_PE_IMG_FLAG_FILE_REMOVED |
                _MMP_PE_IMG_FLAG_FILE_NOT_EXIST | _MMP_PE_IMG_FLAG_PER_DENY) & pt_file->ui2_flag)) ? FALSE : TRUE;
        }
        return MMPR_OK;

    case MMP_PE_EXTRA_INFO_ID_IS_ANIMATION_GIF:
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = pt_file->b_animation_gif;
        }
        return MMPR_OK;

    case MMP_PE_EXTRA_INFO_ID_IS_MPO_FILE:
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = (pt_file->e_img_type == IMG_MPO) ? TRUE : FALSE;
         }
         return MMPR_OK;
    case MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST:
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = (0 != ((_MMP_PE_IMG_FLAG_FILE_NOT_EXIST) & pt_file->ui2_flag)) ? TRUE : FALSE;
        }
        return MMPR_OK;

    case MMP_PE_EXTRA_INFO_ID_DLNA_SERVER_OFF:
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = (0 != ((_MMP_PE_IMG_FLAG_DLNA_SERVER_OFF) & pt_file->ui2_flag)) ? TRUE : FALSE;
        }
        return MMPR_OK;
    case MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER:
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = (0 != ((_MMP_PE_IMG_FLAG_BAD_FILE) & pt_file->ui2_flag)) ? TRUE : FALSE;
        }
        return MMPR_OK;

    case MMP_PE_EXTRA_INFO_ID_IS_PER_DENY:
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = (0 != ((_MMP_PE_IMG_FLAG_PER_DENY) & pt_file->ui2_flag)) ? TRUE : FALSE;
        }
        return MMPR_OK;

    case MMP_PE_EXTRA_INFO_ID_IS_REMOVED:
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }
            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = (0 != (_MMP_PE_IMG_FLAG_FILE_REMOVED & pt_file->ui2_flag)) ? TRUE : FALSE;
        }

        return MMPR_OK;

    case MMP_PE_EXTRA_INFO_ID_IS_DURING_EFFECT: /*pv_param: a pointer to BOOL variable. TRUE: during effect, FALSE: not in effect*/
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = (_MMP_PE_IMG_FLAG_IMG_DURING_EFFECT & pt_file->ui2_flag) ? TRUE : FALSE;
        }
        return MMPR_OK;

    case MMP_PE_EXTRA_INFO_ID_IS_DECODE_THUMB: /*pv_param: a pointer to BOOL variable. TRUE: it has been requested to decode its thumbnail. Otherwise: FALSE*/
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = (_MMP_PE_IMG_FLAG_WITH_THUMB & pt_file->ui2_flag) ? TRUE : FALSE;
        }
        return MMPR_OK;

    case MMP_PE_EXTRA_INFO_ID_IS_NEXTING:
        {
            if(sizeof(BOOL) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(BOOL);
            *((BOOL*)pv_param) = (_MMP_PE_FLAG_FILE_NEXTING & pt_this->ui4_flag) ? TRUE : FALSE;
        }
        return MMPR_OK;

    case MMP_PE_EXTRA_INFO_ID_GET_LOAD_PROG:          /*pv_param: a pointer to UINT32 valiable*/
        {
            UINT32   ui4_progress =0;// ui4_size = sizeof(UINT32);

            *pz_size = sizeof(UINT32);
            *((UINT32*)pv_param) = ui4_progress;
        }
        return MMPR_OK;
    case MMP_PE_EXTRA_INFO_ID_ZOOM:
        {
            if((0 != (_MMP_PE_IMG_FLAG_BAD_FILE & pt_file->ui2_flag)))// || NULL_HANDLE == pt_file->h_img))
            {
                MMP_DBG_ERROR(("No image file to get information.\r\n"));
                return MMPR_NO_DATA;
            }
            if(sizeof(UINT32) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(UINT32);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(UINT32);
            *((UINT32*)pv_param) = pt_file->ui4_zoom;
        }
        return MMPR_OK;
    case MMP_PE_EXTRA_INFO_ID_ROTATE:
        {
            if((0 != (_MMP_PE_IMG_FLAG_BAD_FILE & pt_file->ui2_flag)))// || NULL_HANDLE == pt_file->h_img))
            {
                MMP_DBG_ERROR(("No image file to get information.\r\n"));
                return MMPR_NO_DATA;
            }
            if(sizeof(IMG_ROTATE_OP_TYPE_T) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(IMG_ROTATE_OP_TYPE_T);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(IMG_ROTATE_OP_TYPE_T);
            *((UINT32*)pv_param) = pt_file->e_rotate;
        }
        return MMPR_OK;
    case MMP_PE_EXTRA_INFO_ID_CENTER_OFFSET:
        {
            if((0 != (_MMP_PE_IMG_FLAG_BAD_FILE & pt_file->ui2_flag)))// || NULL_HANDLE == pt_file->h_img))
            {
                MMP_DBG_ERROR(("No image file to get information.\r\n"));
                return MMPR_NO_DATA;
            }
            if(sizeof(GL_POINT_T) > *pz_size || NULL == pv_param)
            {
                *pz_size = sizeof(GL_POINT_T);
                return MMPR_BUF_NOT_ENOUGH;
            }

            *pz_size = sizeof(GL_POINT_T);
            *((GL_POINT_T*)pv_param) = pt_file->t_center_offset;
        }
        return MMPR_OK;
    case MMP_PE_EXTRA_INFO_ID_IS_MEET_LIMITATION:
        {
            BOOL b_meet_all = FALSE;
            if(MMP_FID_NULL_REC_IDX != pt_file->t_path)
            {
                CHAR* p_file_name;
                /*get file name path by fid*/
                i4_ret = mmp_fid_get(pt_file->t_path, &p_file_name);
                if(MMPR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("[mmp pe] %s %d mmp_fid_get(%d) failed. i4_ret = %d.\r\n",__FUNCTION__,__LINE__, pt_file->t_path, i4_ret));
                    MMP_ASSERT(0);
                    return MMPR_NO_DATA;
                }
                //get image info and judeg image limit
                _MMP_IMAGE_INFO imageInfo;
                BOOL    b_meet_all = TRUE;
                i4_ret = mmp_pe_get_image_info(p_file_name, &imageInfo);
                _mmp_pe_get_img_limitation_info(p_file_name, &imageInfo.PhotoType,(VOID *)&b_meet_all);

                *pz_size =  sizeof(BOOL);
                *((BOOL*)pv_param) = b_meet_all;
            }
            *pz_size =  sizeof(BOOL);
            *((BOOL*)pv_param) = b_meet_all;

        }
        return MMPR_OK;
    default:
        return MMPR_NO_DATA;
    }
}





/*-----------------------------------------------------------------------------
 * private VIEW methods implementations
 *---------------------------------------------------------------------------*/
static VOID _mmp_pp_mmp_ctx_fct(VOID* pv_nfy_code, VOID* pv_tag, VOID* pv_data,VOID* pv_param4)
{
    #if 0
   APPL_SPLAYER_PLAY_EVENT e_nfy_code = (APPL_SPLAYER_PLAY_EVENT) pv_nfy_code;   //sac modify   TF516PHIEUMTK00-2455
    switch (e_nfy_code)
    {
        case APPL_SPLAYER_PLAY_EVENT_EOS:
            if((t_g_p_play_state == PP_PHOTO_PLAY_NONE) || (t_g_p_play_state == PP_PHOTO_STOP) )
            {
                break;
            }
            t_g_p_play_state = PP_PHOTO_PLAYING;

            //_mmp_pp_photo_play(XX);
            break;
        case APPL_SPLAYER_PLAY_EVENT_FAIL:
            break;
        case APPL_SPLAYER_PLAY_EVENT_DONE:
            t_g_p_play_state = PP_PHOTO_PLAYING;
            break;
        case APPL_SPLAYER_PLAY_EVENT_PREPARE_DONE:
            DBG_LOG_PRINT(("**  appl_splayer_start_play *** %s,%d\r\n",__FUNCTION__,__LINE__));
#ifdef NEVER
            appl_splayer_start_play((IMTK_PB_CTRL_EVENT_T)pv_nfy_code, pv_tag, (UINT32) pv_data);
#endif /* NEVER */
            break;
        default:
            break;
    }
    #endif
}
static VOID _mmp_pp_splayer_eventCallback(APPL_SPLAYER_PLAY_EVENT e_nfy_code, VOID *pvTag, UINT32 u4Data)
{
    mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _mmp_pp_mmp_ctx_fct,
                    (VOID*)(UINT32)e_nfy_code,
                    (VOID*)pvTag,
                    (VOID*)(UINT32)u4Data,
                    (VOID*)NULL);
}

static INT32 _mmp_pp_photo_play(const CHAR* p_path)
{
    INT32 i4_ret;
    if(gp_p_splayer != NULL)
        appl_splayer_close(&gp_p_splayer);

    i4_ret = appl_splayer_open_async(p_path,(appl_splayer_eventCallback)_mmp_pp_splayer_eventCallback,NULL, 0/*APPL_SPLAYER_PLAY_MODE_LAST_FREEZE*/, &gp_p_splayer,NULL);

    if(APPL_SPLAYER_SUCCESS == i4_ret)
    {
        t_g_p_play_state = PP_PHOTO_OPENING;
    }
    else
    {
        DBG_LOG_PRINT(("(x) HD Demo (x) appl_splayer_open() returns %d.\n", i4_ret));
        t_g_p_play_state = PP_PHOTO_PLAY_NONE;
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

static INT32 _mmp_pp_photo_stop(VOID)
{

    t_g_p_play_state = PP_PHOTO_PLAY_NONE;
    if(gp_p_splayer != NULL)
    {
        appl_splayer_close(&gp_p_splayer);
    }


    return MMPR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_reset_img_file
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pe_reset_img_file(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file)
{
    UINT32                      i;
    MMP_DRC_BUF_T*              pt_match_buf = NULL;
    INT32                       i4_ret = 0;
    UINT8                       ui1_zoom = 1;

    i4_ret = mmp_pe_custom_get(MMP_PE_CUSTOM_GET_RESET_IMG_FILE_WITH_ZOOM_FACTOR,
        &ui1_zoom,
        NULL,
        NULL);
    if (MMPR_NOT_IMPLEMENT == i4_ret)
    {
        ui1_zoom = 1; /* custom part is not implemented */
    }

    pt_file->z_img_w = 0;
    pt_file->z_img_h = 0;
    pt_file->ui4_duration = 0;
    pt_file->e_rotate = IMG_ROTATE_CLOCKWS_0_OP_TYPE;
    pt_file->e_force_rotate_op = MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE;
    pt_file->ui4_zoom = MMP_PE_ZOOM_CONST * ui1_zoom;
    pt_file->t_center_offset.i4_x = 0;
    pt_file->t_center_offset.i4_y = 0;
    pt_file->t_effect.b_is_enabled = FALSE;
    //pt_file->t_effect.b_first_photo = FALSE;
    pt_file->t_path = MMP_FID_NULL_REC_IDX;
    pt_file->ui2_flag = _MMP_PE_IMG_FLAG_ROTATE_FROM_FILE;
    pt_file->t_file_info.ui2_field = _MMP_PE_INFO_FILE_INFO_FIELD_EMPTY;
    pt_file->e_img_type = IMG_UNKNOWN;
#ifdef APP_SUPPORT_4K2K
    pt_file->b_is_4k2k_photo = FALSE;
#endif
    pt_file->b_first_photo = FALSE;


    _MMP_PE_SET_LOAD_VER_INVALID(pt_file->ui4_crnt_load_ver);

    if(pt_file->b_animation_gif && pt_file->pt_buf_animation_gif != NULL)
    {
        pt_file->pt_buf_animation_gif = NULL;
    }

    return;

}
#if 0
/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_convert_rect_coord
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pe_convert_rect_coord(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    MMP_FP_THUMB_COORDS_T       e_coord,
    GL_RECT_T*                  pt_rect)
{
    UINT32                      ui4_width, ui4_height;

    MMP_ASSERT(pt_this->ui2_screen_w && pt_this->ui2_canvas_w && pt_this->ui2_screen_h && pt_this->ui2_canvas_h)
    if(MMP_FP_THUMB_COORDS_CANVAS == e_coord)
    {
        pt_rect->i4_left = (pt_rect->i4_left * pt_this->ui2_screen_w +
                            pt_this->ui2_canvas_w * MMP_PE_RC_THUMB_COMPENSATE / MMP_PE_RC_CONVERT_BASE) / pt_this->ui2_canvas_w;
        pt_rect->i4_right = pt_rect->i4_right * pt_this->ui2_screen_w / pt_this->ui2_canvas_w;

        /*check width*/
        ui4_width = WGL_RECT_GET_WIDTH(pt_rect);
        if(0x00000001 & ui4_width) /*not multiple of 2*/
        {
            pt_rect->i4_right++;
        }

        pt_rect->i4_top = (pt_rect->i4_top * pt_this->ui2_screen_h +
                           pt_this->ui2_canvas_h * MMP_PE_RC_THUMB_COMPENSATE / MMP_PE_RC_CONVERT_BASE) / pt_this->ui2_canvas_h;
        pt_rect->i4_bottom = pt_rect->i4_bottom * pt_this->ui2_screen_h / pt_this->ui2_canvas_h;

        ui4_height = WGL_RECT_GET_HEIGHT(pt_rect);
        if(0x00000001 & ui4_height) /*not multiple of 2*/
        {
            pt_rect->i4_bottom++;
        }
    }
}
#endif

static INT32 _mmp_pe_clean_surface(GL_HSURFACE_T h_surf)
{
    INT32           i4_ret;
    GL_COLOR_T      t_empty_clr;

    /*clean surface*/
    _MMP_PE_ZERO_COLOR(t_empty_clr, 255);
    i4_ret = c_gl_surface_fill(h_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d.\r\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_pe_print_get_id(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file,
        MMP_DRC_BUF_T*                      pt_buf)
{
    INT32   i4_id;
    _MMP_PE_IMG_FILE_T*         pt_another_file;    /* next image file. */

    MMP_ASSERT(pt_this != NULL && pt_file != NULL);


    if(!pt_buf)
    {
        MMP_DBG_INFO(("[Photo/Buffer] pt_buf is NULL.\r\n"));
        return -1;
    }

    if(pt_buf == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC])
    {
        i4_id = 0;
    }
    else if(pt_buf == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1])
    {
        i4_id = 1;
    }
    else if(pt_buf == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2])
    {
        i4_id = 2;
    }
    else
    {
        pt_another_file = (pt_file == &pt_this->at_img[0]) ? &pt_this->at_img[1] : &pt_this->at_img[0];

        if(pt_buf == pt_another_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC])
        {
            i4_id = 3;
        }
        else
        {
            MMP_DBG_INFO(("[Photo/Buffer] pt_buf didn't be found.\r\n"));
            return -2;
        }
    }

    return i4_id;
}

static VOID _mmp_pe_print_buffer_addr(
        _MMP_PE_DATA_MEMBER_T*              pt_this,
        _MMP_PE_IMG_FILE_T*                 pt_file)
{
    _MMP_PE_IMG_FILE_T*         pt_another_file;    /* next image file. */

    MMP_ASSERT((pt_this != NULL && pt_file != NULL));

    pt_another_file = (pt_file == &pt_this->at_img[0]) ? &pt_this->at_img[1] : &pt_this->at_img[0];

    MMP_DBG_INFO(("[Photo/Buffer] Buffer\t\t 0 is 0x%x\r\n", pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC]));
    MMP_DBG_INFO(("[Photo/Buffer] Buffer\t\t 1 is 0x%x\r\n", pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1]));
    MMP_DBG_INFO(("[Photo/Buffer] Buffer\t\t 2 is 0x%x\r\n", pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2]));
    MMP_DBG_INFO(("[Photo/Buffer] Preload Buffer\t   is 0x%x\r\n", pt_another_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC]));

    MMP_DBG_INFO(("[Photo/Buffer] Current Display\t   is 0x%x\r\n", pt_this->pt_buf_crnt_disp));
}





/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_init_plane
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_init_plane(
    _MMP_PE_DATA_MEMBER_T*       pt_this)
{
    UINT32              ui4_screen_width, ui4_screen_height;
    GL_HSCREEN_T                h_screen;
    HANDLE_T                    h_canvas;
    INT32                       i4_ret;
    UINT32                      ui4_w, ui4_h;
    UINT16                      ui2_plane_count;
    UINT32                      ui4_thum_idx = 0;
    UINT32                      i = 0,j = 0;
    HANDLE_T                    h_thum_canvas;
    GL_PLANE_CAPS_T             t_plane_caps;
    GL_DISPLAY_OPT_T            t_dsp_opt = {0};

    if(pt_this == NULL)
    {
        return -1;
    }
    /*open screen*/
    i4_ret = c_gl_screen_open(MMP_RC_DISPLAY_NAME, NULL, NULL, &h_screen);
    if(GLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_gl_screen_open(%s) failed. i4_ret = %d.\r\n", MMP_RC_DISPLAY_NAME, i4_ret));
        return MMPR_FAIL;
    }

    do
    {
        /*get screen capability*/
        i4_ret = c_gl_screen_get_panel_size(h_screen, &ui4_screen_width, &ui4_screen_height);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_gl_screen_get_panel_size() failed. i4_ret = %d.\r\n", i4_ret));
            i4_ret = MMPR_FAIL;
            break;
        }
        pt_this->ui2_screen_w = (UINT16)ui4_screen_width;
        pt_this->ui2_screen_h = (UINT16)ui4_screen_height;

        /* Find a suit plane for image*/
        i4_ret = c_gl_plane_num(&ui2_plane_count);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("%s, c_gl_plane_num() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            i4_ret = MMPR_FAIL;
            break;
        }

        ui4_thum_idx = 1;

        #if 1
        for(i = 0; i < ui2_plane_count; i++)
        {
            /* Skip OSD plane. */
            if(i == ui4_thum_idx)
            {
                continue;
            }

            /* Get plane capability. */
            i4_ret = c_gl_plane_enum(h_screen, i, &t_plane_caps);
            if(GLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("%s, c_gl_plane_enum(%d) failed. i4_ret = %d.\r\n", __FUNCTION__, i, i4_ret));
                i4_ret = MMPR_FAIL;
                break;
            }

            /* Check capability. */
            if(((0x00000001 << GL_COLORMODE_ARGB_D8888) & t_plane_caps.ui4_cm_caps) &&
                ((0x00000001 << 1) & t_plane_caps.ui4_z_mask))
            {
                /*found*/
                i4_ret = MMPR_OK;
                break;
            }
        }

        if(i >= ui2_plane_count || MMPR_OK != i4_ret)   /*not found or error*/
        {
            MMP_DBG_ERROR(("%s, Not found suit plane or error.\r\n", __FUNCTION__));
            i4_ret = MMPR_FAIL;
            break;
        }
        #endif

        ui4_thum_idx = 0;

        /*init thumbnail plane*/
        i4_ret = c_gl_plane_open(h_screen, (UINT16)ui4_thum_idx, &pt_this->h_thumbnail_plane);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_gl_plane_open(%d) failed. i4_ret = %d.\r\n", ui4_thum_idx, i4_ret));
            pt_this->h_thumbnail_plane = NULL_HANDLE;
            i4_ret = MMPR_FAIL;
            break;
        }

        //
        i4_ret = c_gl_plane_link(pt_this->h_thumbnail_plane, h_screen, TRUE);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("x_gl_plane_link() failed. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        /*get thumbnail canvas*/
        i4_ret = c_wgl_get_canvas(pt_this->h_thumbnail_plane, &h_thum_canvas);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_get_canvas() failed. i4_ret = %d.\r\n", i4_ret));
            i4_ret = MMPR_FAIL;
            break;
        }


        /*get thumbnail canvas size*/
        i4_ret = c_wgl_get_canvas_size(h_thum_canvas, &ui4_w, &ui4_h);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_get_canvas_size() failed. i4_ret = %d.\r\n", i4_ret));
            i4_ret = MMPR_FAIL;
            break;
        }
        pt_this->ui4_thumbanil_canvas_w = (UINT16)1920;
        pt_this->ui4_thumbanil_canvas_h = (UINT16)1080;

        //
        i4_ret = c_gl_view_create(ui4_w,
                                  ui4_h,
                                  TRUE/*FALSE*/,
                                  &pt_this->h_thumbnail_view);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_gl_view_create() failed. i4_ret = %d.\r\n", i4_ret));
            pt_this->h_thumbnail_view = NULL_HANDLE;
            i4_ret = MMPR_FAIL;
            break;
        }



        // Create Surface
        GL_SURFACE_DESC_T       t_surf_descr = {0};
        t_surf_descr.e_clrmode  = GL_COLORMODE_ARGB_D8888;
        t_surf_descr.ui4_width  = 1920;
        t_surf_descr.ui4_height = 1080;
        i4_ret = c_gl_surface_create(&t_surf_descr, &pt_this->h_thumbnail_surf);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_gl_surface_create() failed. i4_ret = %d.\r\n", i4_ret));
            pt_this->h_thumbnail_surf = NULL_HANDLE;
            break;
        }


        // Create Viewport
        t_dsp_opt.e_flag             = GL_DISP_OPT_POSITION | GL_DISP_OPT_BLEND_OPTION | GL_DISP_OPT_ALPHA;
        t_dsp_opt.e_blend_option     = GL_BLEND_OPT_PIXEL;
        t_dsp_opt.ui1_alpha          = 255;
        t_dsp_opt.t_pos.i4_x         = 0;
        t_dsp_opt.t_pos.i4_y         = 0;
        i4_ret = c_gl_view_create_viewport(pt_this->h_thumbnail_view, pt_this->h_thumbnail_surf, &t_dsp_opt, &pt_this->ui4_thumbanil_viewport);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_gl_view_create_viewport() failed. i4_ret = %d.\r\n", i4_ret));
            pt_this->ui4_thumbanil_viewport = 0;
            break;
        }




        #if 0
        c_gl_plane_set_alpha(pt_this->h_thumbnail_plane,0xFF);
        i4_ret = c_gl_plane_flip(pt_this->h_thumbnail_plane, pt_this->h_thumbnail_view, TRUE);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_gl_plane_flip() failed. i4_ret = %d.\r\n", i4_ret));
            break;
        }
        #endif



        /* Get image plane from DRC */
        //NOTE : this is image plane/osd , may is 0 /2
        //i4_ret = mmp_drc_get_plane(&pt_this->h_plane);
        //if (i4_ret != MMPR_OK)
        //{
        //    break;
        //}

        pt_this->h_screen = h_screen;
        h_screen = NULL_HANDLE;
        pt_this->ui4_flag |= _MMP_PE_FLAG_SCREEN_LINKED;
        i4_ret = MMPR_OK;

        return i4_ret;
    } while(0);

    //
    if(pt_this->ui4_thumbanil_viewport != 0)
    {
        c_gl_view_delete_viewport(pt_this->h_thumbnail_view,pt_this->ui4_thumbanil_viewport);
        pt_this->ui4_thumbanil_viewport = 0;
    }
    //
    if(pt_this->h_thumbnail_surf != NULL_HANDLE)
    {
        c_gl_obj_free(pt_this->h_thumbnail_surf);
        pt_this->h_thumbnail_surf = NULL_HANDLE;
    }
    //
    if(pt_this->h_thumbnail_view != NULL_HANDLE)
    {
        MMP_EXEC_WITH_ASSERT(c_gl_obj_free(pt_this->h_thumbnail_view), GLR_OK);
        pt_this->h_thumbnail_view = NULL_HANDLE;
    }
    /*free plane*/
    if(pt_this->h_thumbnail_plane != NULL_HANDLE)
    {
        MMP_EXEC_WITH_ASSERT(c_gl_obj_free(pt_this->h_thumbnail_plane), GLR_OK);
        pt_this->h_thumbnail_plane = NULL_HANDLE;
    }
    //
    if(pt_this->h_screen != NULL_HANDLE)
    {
        MMP_EXEC_WITH_ASSERT(c_gl_obj_free(pt_this->h_screen), GLR_OK);
        pt_this->h_screen = NULL_HANDLE;
    }

    return i4_ret;
}

static INT32 _mmp_pe_preview_wgl_frm_main_proc(
HANDLE_T h_frm_main,
UINT32 ui4_msg,
VOID* pv_param1,
VOID* pv_param2)
{
    /* delivers the message to the default message procedure of main_frame */
    return c_wgl_default_msg_proc(h_frm_main,
                                    ui4_msg,
                                    pv_param1,
                                    pv_param2);
}

const GL_COLOR_T _COLOR_LIGHT_BLUE_NORMAL =
{
    255, {163}, {189}, {203}
};

const GL_COLOR_T _COLOR_LIGHT_BLUE_HLT =
{
    255, {204}, {236}, {254}
};

const GL_COLOR_T _COLOR_GRAY_128 =
{
    255, {128}, {128}, {128}
};

/* color definitions */
#define FRM_MN_CLR_BK_EN        _COLOR_LIGHT_BLUE_NORMAL
#define FRM_MN_CLR_BK_DIS       _COLOR_GRAY_128
#define FRM_MN_CLR_BK_HLT       _COLOR_LIGHT_BLUE_HLT

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_init_view
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_init_view(
    _MMP_PE_DATA_MEMBER_T*      pt_this)
{
    GL_RECT_T t_rect;
    if(pt_this == NULL)
    {
        return -1;
    }

#if 0
    INT32                       i4_ret, i;

    for(i = 0; i < pt_this->ui4_disp_count; i++)
    {
        /*create view*/
        i4_ret = c_gl_view_create(pt_this->ui2_screen_w, pt_this->ui2_screen_h, TRUE/*FALSE*/, &pt_this->at_disp_pool[i].h_view);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_gl_view_create() failed. i4_ret = %d.\r\n", i4_ret));

            pt_this->at_disp_pool[i].h_view = NULL_HANDLE;
            return MMPR_FAIL;
        }
    }
#endif
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_init_req_window
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_init_req_window(
    _MMP_PE_REQ_WINDOW_T*       pt_req_window)
{
    INT32                       i4_ret;

    /*clean request window*/
    c_memset(pt_req_window, 0, sizeof(_MMP_PE_REQ_WINDOW_T));
    pt_req_window->e_id = _MMP_PE_REQ_ID_LAST_ENTRY;

    /*create a semaphore for protection*/
    i4_ret = c_sema_create(&pt_req_window->h_ready_signal, X_SEMA_TYPE_BINARY, X_SEMA_STATE_LOCK);
    if(OSR_OK != i4_ret)
    {
        pt_req_window->h_ready_signal = NULL_HANDLE;
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_suspend_disp_res
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_suspend_disp_res(
    _MMP_PE_DATA_MEMBER_T*      pt_this)
{
    INT32                       i4_ret = MMPR_OK;
    pt_this->ui4_flag &= ~(_MMP_PE_FLAG_PLAY_DISP_RESUMED | _MMP_PE_FLAG_THUMB_DISP_RESUMED);
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_resume_disp_res
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_resume_disp_res(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    BOOL                        b_is_thumb)
{
    if(b_is_thumb)
    {
        pt_this->ui4_flag |= _MMP_PE_FLAG_THUMB_DISP_RESUMED;
    }
    else
    {
        pt_this->ui4_flag |= _MMP_PE_FLAG_PLAY_DISP_RESUMED;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_get_unused_disp_res
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static MMP_DRC_BUF_T* _mmp_pe_get_unused_disp_res(
    _MMP_PE_DATA_MEMBER_T*      pt_this)
{
    INT32                       i4_ret;
    MMP_DRC_BUF_T*              pt_buf;

    return NULL;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_is_disp_res_used_by_crnt_img
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static BOOL _mmp_pe_is_disp_res_used_by_crnt_img(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    MMP_DRC_BUF_T*              pt_buf)
{
    _MMP_PE_IMG_FILE_T*         pt_file;
    UINT32                      i;

    if(_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
    {
        return FALSE;
    }

    //MMP_ASSERT(NULL != pt_buf);
    if(NULL == pt_buf)
    {
        return FALSE;
    }

    if(pt_this->ui1_crnt_img < _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        pt_file = &pt_this->at_img[pt_this->ui1_crnt_img];

        for(i = 0; i < _MMP_PE_WORKING_BUF_ID_TOTAL; i++)
        {
            if(pt_buf == pt_file->t_working_buf.at_buf[i])
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_get_output_disp_res
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_get_output_disp_res(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file,
    MMP_DRC_BUF_T**             ppt_buf)
{
    /*UINT8*                      pui1_null_idx;*/
    MMP_DRC_BUF_T**             ppt_null_buf;
    UINT32                      i;
    MMP_DRC_BUF_T*              pt_buf_dest;

    /* for the situation: the three buffer is not enough, so it is need to occupy preload buffer. */
    _MMP_PE_IMG_FILE_T*         pt_another_file;    /* next image file. */

    /*find working surface index*/
    ppt_null_buf = NULL;
    for(i = 1; i < _MMP_PE_WORKING_BUF_ID_TOTAL; i++)
    {
        if(NULL == pt_file->t_working_buf.at_buf[i])
        {
            ppt_null_buf = &(pt_file->t_working_buf.at_buf[i]);
            pt_file->t_working_buf.e_match_id = (UINT8)i;

            MMP_DBG_INFO(("[Photo/Buffer] Find buffer %d.\r\n", i));
            break;
        }
    }

    /* prepare working surface.
    */
    /* find surface, so just get one buffer.*/
    if(NULL != ppt_null_buf)
    {
        /*get a free one*/
        pt_buf_dest = _mmp_pe_get_unused_disp_res(pt_this);
        if(NULL == pt_buf_dest)
        {
            MMP_DBG_ERROR(("No free Display Resource.\r\n"));
            return MMPR_INTERNAL_ERROR;
        }

        pt_file->t_working_buf.at_buf[i] = pt_buf_dest;

        *ppt_buf = pt_buf_dest;
        return MMPR_OK;
    }

    /* gif, cannot use preload buffer. */
    if(pt_file->b_animation_gif)
    {
        MMP_ASSERT(pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] != pt_this->pt_buf_crnt_disp);

        pt_buf_dest = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2];
        pt_file->t_working_buf.e_match_id = _MMP_PE_WORKING_BUF_ID_WORK_2;

        if(pt_this->ui4_flag & _MMP_PE_FLAG_ANIMATION_GIF_NEED_CLEAN)
        {
            /*clean surface*/
            _mmp_pe_clean_surface(pt_buf_dest->h_surf);
        }

        *ppt_buf = pt_buf_dest;
        return MMPR_OK;
    }

    /* the preload buffer is located in the another image file object. */
    pt_another_file = (pt_file == &pt_this->at_img[0]) ? &pt_this->at_img[1] : &pt_this->at_img[0];

    /* Current display is Preload buffer, so regard buffer 2 as dest buffer. */
    if(pt_another_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC] == pt_this->pt_buf_crnt_disp)
    {
        MMP_DBG_INFO(("[Photo/Buffer] Current display is Preload buffer, so regard buffer 2 as dest buffer.\r\n"));
        pt_buf_dest = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2];
        pt_file->t_working_buf.e_match_id = _MMP_PE_WORKING_BUF_ID_WORK_2;

        /*clean surface*/
        _mmp_pe_clean_surface(pt_buf_dest->h_surf);

        *ppt_buf = pt_buf_dest;
        return MMPR_OK;
    }

    /* The follow will occupy preload buffer................ */
    /* There are preload buffer....*/
    if(pt_another_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC] != NULL)
    {
        if(_mmp_pe_stop_next_image_preload())
        {
            MMP_DBG_INFO(("[Photo/Buffer] Get Preload buffer.(Stop Preload).\r\n"));

            /* get a free one as preload buffer.  */
            pt_buf_dest = _mmp_pe_get_unused_disp_res(pt_this);
            if(NULL == pt_buf_dest)
            {
                MMP_DBG_INFO(("[Photo/Buffer] No free Display Resource.\r\n"));
                return MMPR_INTERNAL_ERROR;
            }
        }
        else
        {
            MMP_DBG_INFO(("[Photo/Buffer] Get Preload buffer.(Have Preload).\r\n"));
            pt_buf_dest = pt_another_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC];

            /* suspend preload, to make sure next photo playing is OK! */
            pt_another_file->ui2_flag |= _MMP_PE_IMG_FLAG_IMG_LOADING_SUSPEND;
        }

        MMP_DBG_INFO(("[Photo/Buffer] Swap buffer between work 2 and preload.\r\n"));

        pt_another_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC] =
            pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2];
        pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = pt_buf_dest;

        pt_file->t_working_buf.e_match_id = _MMP_PE_WORKING_BUF_ID_WORK_2;

        /*clean surface*/
        _mmp_pe_clean_surface(pt_buf_dest->h_surf);

        *ppt_buf = pt_buf_dest;
        return MMPR_OK;
    }

    MMP_DBG_INFO(("[Photo/Buffer] Get Preload buffer.(No Preload).\r\n"));

    /* current display buffer is not included in at_buf[src/work1/work2/preload],
        which will maybe lead to out of memory. (CR:621343)
       That case will happen when playing next photo, which has rotate,stretch and tfx.
    */
    if(pt_this->pt_buf_crnt_disp != pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC]       &&
        pt_this->pt_buf_crnt_disp != pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1]   &&
        pt_this->pt_buf_crnt_disp != pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2])
    {
        MMP_DBG_INFO(("[Photo/Buffer] Current photo has rotate, stretch and tfx.\r\n"));
        pt_another_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC] = pt_this->pt_buf_crnt_disp;
        pt_buf_dest = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2];
    }
    else
    {
        /* get a free one as preload buffer.  */
        pt_buf_dest = _mmp_pe_get_unused_disp_res(pt_this);
        if(NULL == pt_buf_dest)
        {
            MMP_DBG_INFO(("[Photo/Buffer] No free Display Resource.\r\n"));
            return MMPR_INTERNAL_ERROR;
        }

        MMP_DBG_INFO(("[Photo/Buffer] Swap buffer between work 2 and preload.\r\n"));
        pt_another_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC] =
            pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2];
        pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = pt_buf_dest;
    }

    pt_file->t_working_buf.e_match_id = _MMP_PE_WORKING_BUF_ID_WORK_2;

    /*clean surface*/
    _mmp_pe_clean_surface(pt_buf_dest->h_surf);

    *ppt_buf = pt_buf_dest;
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_check_working_disp_res
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_check_working_disp_res(
    _MMP_PE_DATA_MEMBER_T*              pt_this,
    _MMP_PE_IMG_FILE_T*                 pt_file,
    MMP_DRC_BUF_T*                      pt_buf_ref,
    MMP_DRC_BUF_T**                     ppt_buf_output)
{
    INT32                               i4_ret;
    MMP_DRC_BUF_T*                      pt_temp_buf;
#if 0
    /* for the situation: the three buffer is not enough, so it is need to occupy preload buffer. */
    _MMP_PE_IMG_FILE_T*         pt_another_file;    /* next image file. */

    pt_another_file = (pt_file == &pt_this->at_img[0]) ? &pt_this->at_img[1] : &pt_this->at_img[0];
#endif
#if 0 //#ifdef APP_SUPPORT_4K2K
    /*ref surface is work[1], swap work[0] and work[1]*/
    if (pt_buf_ref == pt_this->pt_buf_crnt_disp)
    {
        if(pt_buf_ref == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2])
        {
            pt_temp_buf = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1];
            pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1] = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2];
            pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = pt_temp_buf;
            pt_file->t_working_buf.e_match_id = _MMP_PE_WORKING_BUF_ID_WORK_2;
        }
    }
    else
    {
        if(pt_buf_ref == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2])
        {
            if (pt_this->pt_buf_crnt_disp == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_3])
            {
                pt_temp_buf = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1];
                pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1] = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2];
                pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = pt_temp_buf;
            }
            else
            {
                pt_temp_buf = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_3];
                pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_3] = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2];
                pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = pt_temp_buf;
            }

            pt_file->t_working_buf.e_match_id = _MMP_PE_WORKING_BUF_ID_WORK_2;
        }
        else if(pt_this->pt_buf_crnt_disp == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2])
        {
            if (pt_buf_ref == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_3])
            {
                pt_temp_buf = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1];
                pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1] = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2];
                pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = pt_temp_buf;
            }
            else
            {
                pt_temp_buf = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_3];
                pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_3] = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2];
                pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = pt_temp_buf;
            }

            pt_file->t_working_buf.e_match_id = _MMP_PE_WORKING_BUF_ID_WORK_2;
        }
    }
#else
    /*ref surface is work[1], swap work[0] and work[1]*/
    if(pt_buf_ref == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2])
    {
        MMP_DBG_INFO(("[Photo/Buffer] ref_buf is work 2, so swap buffer between 1 and 2.\r\n"));

        pt_temp_buf = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1];
        pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1] = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2];
        pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = pt_temp_buf;

        pt_file->t_working_buf.e_match_id = _MMP_PE_WORKING_BUF_ID_WORK_2;
    }

    if(pt_file->b_animation_gif && (pt_this->pt_buf_crnt_disp == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2]))
    {
        MMP_DBG_INFO(("[Photo/Buffer] Gif: crnt_disp is work2, so exchange 'work 2' and 'work 1 or src'.\r\n"));

        if(pt_buf_ref == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC]) // ref buffer is src..
        {
            pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1];
            pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_1] = pt_this->pt_buf_crnt_disp;
        }
        else // ref buffer is work 1..
        {
            pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_WORK_2] = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC];
            pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC] = pt_this->pt_buf_crnt_disp;
        }
    }
#endif

    /*find working surface index*/
    i4_ret = _mmp_pe_get_output_disp_res(pt_this, pt_file, ppt_buf_output);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    return MMPR_OK;
}

#if defined(APP_SUPPORT_4K2K) || defined(APP_3D_PHOTO_SUPPORT)
_MMP_PE_WORKING_BUF_ID_T _mmp_pe_get_working_id(
    _MMP_PE_IMG_FILE_T*         pt_file,
    MMP_DRC_BUF_T*              pt_buf)
{
    INT32 i;

    for (i = 0; i < _MMP_PE_WORKING_BUF_ID_TOTAL; i++)
    {
        if (pt_buf == pt_file->t_working_buf.at_buf[i])
        {
            return i;
        }
    }

    return _MMP_PE_WORKING_BUF_ID_NULL;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_load_preview
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_load_preview(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    UINT32                      ui4_img_idx)
{
    IMG_TYPE_DATA_T             t_type_data;
    _MMP_PE_IMG_FILE_T*         pt_file;
    MMP_DRC_BUF_T*              pt_disp;
    IMG_ROTATE_OP_TYPE_T        e_best_rotate;
    _MMP_PE_ROTATE_GROUP_T      e_group;
    UINT32                      ui4_src_w, ui4_src_h, ui4_ratio_w, ui4_ratio_h;
    UINT32                      ui4_rect_w, ui4_rect_h;
    UINT32                      ui4_dst_x, ui4_dst_y, ui4_dst_w, ui4_dst_h;
    INT32                       i4_ret/*, i4_ratio_scrn, i4_diff_w_h, i4_diff_h_w*/;
    MMP_DRC_BUF_T*              pt_buf_unused = NULL;
    //EXIF_INFO_T                 t_rotate_info;
    BOOL                        b_need_rotate = FALSE;
    BOOL                        b_use_full_decode = TRUE;

    _mmp_pe_suspend_disp_res(pt_this);

    c_memset(&t_type_data, 0, sizeof(IMG_TYPE_DATA_T));

    if(ui4_img_idx >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        return MMPR_INV_ARG;
    }

    pt_file = &pt_this->at_img[ui4_img_idx];

    if(_MMP_PE_IMG_FLAG_WITH_THUMB & pt_file->ui2_flag)
    {
        /*notify client main image begin*/
        pt_this->pf_play_nfy(pt_this->pv_play_nfy_tag, pt_this->ui4_play_ver, MMP_PE_PLAY_NFY_ID_DEC_IMG_BEGIN, NULL);
    }

    do
    {
        /**/
        if(NULL == pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC])
        {
            pt_buf_unused = _mmp_pe_get_unused_disp_res(pt_this);

            if(NULL == pt_buf_unused)
            {
                MMP_DBG_ERROR(("No free Display Resource.\r\n"));
                i4_ret = MMPR_FAIL;
                break; /*break do-while(0)*/
            }
            pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC] = pt_buf_unused;
            /*pt_this->at_disp_pool[ui4_unused].ui1_flag |= _MMP_PE_DR_FLAG_USED;*/

            /**/
            if(_MMP_PE_IMG_FLAG_BAD_FILE & pt_file->ui2_flag)
            {
                i4_ret = MMPR_FAIL;
                break; /*break do-while(0)*/
            }

            /*disable progressive*/
            if( IMG_JPG == pt_file->e_img_type && FALSE == MMP_PE_RC_IS_PROGRESSIVE_SUPT() && _MMP_PE_IS_JPG_PROGRESSIVE(pt_file->ui2_flag))
            {
                pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_NOT_SUPPORT_FILE;
                MMP_DBG_INFO(("Progressive Photo Type not support.\r\n"));
                i4_ret = MMPR_NOT_SUPPORT;
                break; /*break do-while(0)*/
            }
        }
        else if( IMG_JPG == pt_file->e_img_type && FALSE == MMP_PE_RC_IS_PROGRESSIVE_SUPT() && _MMP_PE_IS_JPG_PROGRESSIVE(pt_file->ui2_flag)) /*disable progressive*/
        {
            MMP_DBG_INFO(("Progressive Photo Type not support.\r\n"));
            i4_ret = MMPR_NOT_SUPPORT;
            break; /*break do-while(0)*/
        }
        else if(pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC] != NULL)
        {
            /**/
            if(_MMP_PE_IMG_FLAG_BAD_FILE & pt_file->ui2_flag)
            {
                //mmp_drc_clean_buf(pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC]);
                //_MMP_PE_NEW_LOAD_VER(pt_this);

                i4_ret = MMPR_FAIL;
                break; /*break do-while(0)*/
            }
        }

        pt_disp = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC];

        //mmp_drc_clean_buf(pt_disp);

        if(IMG_JPG == pt_file->e_img_type)
        {
            #if 0
            i4_ret = c_img_reparse_exif(&(pt_file->h_img));
            if(IMGR_OK != i4_ret)
            {
                MMP_DBG_INFO(("c_img_reparse_exif failed.\r\n"));
                i4_ret = MMPR_FAIL;
                break; /*break do-while(0)*/
            }

            t_rotate_info.e_exif_id = EXIF_ORIENTATION;
            t_rotate_info.z_size = sizeof(IMG_ROTATE_OP_TYPE_T);
            t_rotate_info.pv_data = &(pt_file->e_rotate);

            i4_ret = c_img_get_exif_info(pt_file->h_img, INTRA_IMG_PRIMARY_IMG_TYPE, &t_rotate_info, 1);
            if(IMGR_OK != i4_ret && IMGR_NO_EXIF_DATA != i4_ret)
            {
                MMP_DBG_INFO(("c_img_get_exif_info failed.\r\n"));
                i4_ret = MMPR_FAIL;
                break; /*break do-while(0)*/
            }
            #endif
        }

        e_best_rotate = pt_file->e_rotate;

        e_group = _mmp_pe_get_angle_group(e_best_rotate);

        if(_MMP_PE_ROTATE_GROUP_1 == e_group || _MMP_PE_ROTATE_GROUP_3 == e_group)
        {
            b_need_rotate = TRUE;
            #ifndef APP_3D_PHOTO_SUPPORT
            b_use_full_decode = FALSE;
            #endif
        }

        if(_MMP_PE_IS_JPG_PROGRESSIVE(pt_file->ui2_flag))
        {
            b_use_full_decode = TRUE;
        }

        if(TRUE == mmp_pe_is_pf_part_mode())
        {
            if(b_need_rotate && FALSE == _MMP_PE_IS_JPG_PROGRESSIVE(pt_file->ui2_flag))
            {
//              i4_ret = mmp_photo_frm_photo_get_rect(pt_file->z_img_h, pt_file->z_img_w, &pt_this->t_prew_rect);
                i4_ret = mmp_pe_custom_get(MMP_PE_CUSTOM_GET_PHOTO_FRM_PREW_RECT, &pt_file->z_img_h, &pt_file->z_img_w, &pt_this->t_prew_rect);
            }
            else
            {
//                i4_ret = mmp_photo_frm_photo_get_rect(pt_file->z_img_w, pt_file->z_img_h, &pt_this->t_prew_rect);
                i4_ret = mmp_pe_custom_get(MMP_PE_CUSTOM_GET_PHOTO_FRM_PREW_RECT, &pt_file->z_img_w, &pt_file->z_img_h, &pt_this->t_prew_rect);
            }
            if(MMPR_OK == i4_ret)
            {
                #ifdef APP_3D_PHOTO_SUPPORT
                mmp_drc_convert_rect_coord(MMP_FP_THUMB_COORDS_VIRTUAL_SCREEN, &pt_this->t_prew_rect);
                #else
                mmp_drc_convert_rect_coord(MMP_FP_THUMB_COORDS_CANVAS, &pt_this->t_prew_rect);
                #endif
            }
        }

        if(MMP_PE_RC_SUPPORT_FULL_DECODING()&& b_use_full_decode)
        {
            e_best_rotate = IMG_ROTATE_CLOCKWS_0_OP_TYPE;
        }

        /**/
        e_group = _mmp_pe_get_angle_group(e_best_rotate);
        if(_MMP_PE_ROTATE_GROUP_1 == e_group || _MMP_PE_ROTATE_GROUP_3 == e_group) /*90, 270 without flip / 90, 270 with flip*/
        {
            ui4_src_w = pt_file->z_img_h;
            ui4_src_h = pt_file->z_img_w;
        }
        else
        {
            ui4_src_w = pt_file->z_img_w;
            ui4_src_h = pt_file->z_img_h;
        }

        if(MMP_PE_RC_SUPPORT_FULL_DECODING()&& b_need_rotate && b_use_full_decode)
        {
            /*get destination width and height*/
            ui4_rect_h = (UINT32)WGL_RECT_GET_WIDTH(&(pt_this->t_prew_rect));
            ui4_rect_w = (UINT32)WGL_RECT_GET_HEIGHT(&(pt_this->t_prew_rect));
        }
        else
        {
            /*get destination width and height*/
            ui4_rect_w = (UINT32)WGL_RECT_GET_WIDTH(&(pt_this->t_prew_rect));
            ui4_rect_h = (UINT32)WGL_RECT_GET_HEIGHT(&(pt_this->t_prew_rect));
        }

        MMP_DBG_INFO(("[PhotoEng][_mmp_pe_load_preview] Print preview rect.\r\n"));
        _mmp_pe_rect_print(pt_this->t_prew_rect);

        /*calc rectangle...keep aspect ratio*/
        ui4_ratio_w = ui4_rect_w * _MMP_PE_ACCURACY_CONST / ui4_src_w;
        ui4_ratio_h = ui4_rect_h * _MMP_PE_ACCURACY_CONST / ui4_src_h;

        if(ui4_ratio_w > ui4_ratio_h) /*keep height*/
        {
            ui4_dst_w = ui4_rect_h * ui4_src_w / ui4_src_h;

            MMP_DBG_INFO(("[PhotoEng][_mmp_pe_load_preview] ui4_dst_w=%d.\r\n", ui4_dst_w));

            if(0 == ui4_dst_w)
            {
                ui4_dst_w = 1; /*for special width*/
            }
            if (ui4_dst_w < 4 && (pt_file->e_img_type == IMG_WEBP || pt_file->e_img_type == IMG_JPG))
            {
                ui4_dst_w = 4;
            }

#ifdef APP_3D_PHOTO_SUPPORT
            if (ui4_dst_w < 8)
            {
                ui4_dst_w = 8;
            }
            ui4_dst_w = ((ui4_dst_w + 7) >> 3) << 3;
            if (ui4_dst_w > ui4_rect_w)
            {
                ui4_dst_w -= 8;
            }
#endif
            MMP_DBG_INFO(("[PhotoEng][_mmp_pe_load_preview] ui4_dst_w=%d.\r\n", ui4_dst_w));

            if((ui4_rect_w - ui4_dst_w) > MMP_PE_RC_ASPECT_RATIO_TOLERANCE)
            {
                ui4_dst_x = ((ui4_rect_w - ui4_dst_w) >> 1);

                if(MMP_PE_RC_SUPPORT_FULL_DECODING() && b_need_rotate && b_use_full_decode)
                {
                    pt_file->t_thumb_rect.i4_top    = pt_this->t_prew_rect.i4_top + ((ui4_rect_w - ui4_dst_w) >> 1);
                    pt_file->t_thumb_rect.i4_bottom = pt_file->t_thumb_rect.i4_top + ui4_dst_w;
                    pt_file->t_thumb_rect.i4_left   = pt_this->t_prew_rect.i4_left;
                    pt_file->t_thumb_rect.i4_right  = pt_this->t_prew_rect.i4_right;
                }
                else
                {
                    pt_file->t_thumb_rect.i4_top    = pt_this->t_prew_rect.i4_top;
                    pt_file->t_thumb_rect.i4_bottom = pt_this->t_prew_rect.i4_bottom;
                    pt_file->t_thumb_rect.i4_left   = pt_this->t_prew_rect.i4_left + ui4_dst_x;
                    pt_file->t_thumb_rect.i4_right  = pt_file->t_thumb_rect.i4_left + ui4_dst_w;
                }
            }
            else /*near the original apsect ratio*/
            {
                pt_file->t_thumb_rect.i4_top    = pt_this->t_prew_rect.i4_top;
                pt_file->t_thumb_rect.i4_bottom = pt_this->t_prew_rect.i4_bottom;
                pt_file->t_thumb_rect.i4_left   = pt_this->t_prew_rect.i4_left;
                pt_file->t_thumb_rect.i4_right  = pt_this->t_prew_rect.i4_right;
            }
        }
        else /*keep width*/
        {
            ui4_dst_h = ui4_rect_w * ui4_src_h / ui4_src_w;

            MMP_DBG_INFO(("[PhotoEng][_mmp_pe_load_preview] ui4_dst_h=%d.\r\n", ui4_dst_h));

            if(0 == ui4_dst_h)
            {
                ui4_dst_h = 1; /*for special height*/
            }
            if (ui4_dst_h < 4 && (pt_file->e_img_type == IMG_WEBP || pt_file->e_img_type == IMG_JPG))
            {
                ui4_dst_h = 4;
            }

#ifdef APP_3D_PHOTO_SUPPORT
            if (ui4_dst_h < 8)
            {
                ui4_dst_h = 8;
            }
            ui4_dst_h = ((ui4_dst_h + 7) >> 3) << 3;
            if (ui4_dst_h > ui4_rect_h)
            {
                ui4_dst_h -= 8;
            }
#endif

            ui4_dst_y = ((ui4_rect_h - ui4_dst_h) >> 1);

            MMP_DBG_INFO(("[PhotoEng][_mmp_pe_load_preview] ui4_dst_h=%d.\r\n", ui4_dst_h));

            if((ui4_rect_h - ui4_dst_h) > MMP_PE_RC_ASPECT_RATIO_TOLERANCE)
            {
                if(MMP_PE_RC_SUPPORT_FULL_DECODING() && b_need_rotate && b_use_full_decode)
                {
                    pt_file->t_thumb_rect.i4_left   = pt_this->t_prew_rect.i4_left + ((ui4_rect_h - ui4_dst_h) >> 1);
                    pt_file->t_thumb_rect.i4_right  = pt_file->t_thumb_rect.i4_left + ui4_dst_h;
                    pt_file->t_thumb_rect.i4_top    = pt_this->t_prew_rect.i4_top;
                    pt_file->t_thumb_rect.i4_bottom = pt_this->t_prew_rect.i4_bottom;
                }
                else
                {
                    pt_file->t_thumb_rect.i4_left   = pt_this->t_prew_rect.i4_left;
                    pt_file->t_thumb_rect.i4_right  = pt_this->t_prew_rect.i4_right;
                    pt_file->t_thumb_rect.i4_top    = pt_this->t_prew_rect.i4_top + ui4_dst_y;
                    pt_file->t_thumb_rect.i4_bottom = pt_file->t_thumb_rect.i4_top + ui4_dst_h;
                }
            }
            else /*near the original apsect ratio*/
            {
                pt_file->t_thumb_rect.i4_top    = pt_this->t_prew_rect.i4_top;
                pt_file->t_thumb_rect.i4_bottom = pt_this->t_prew_rect.i4_bottom;
                pt_file->t_thumb_rect.i4_left   = pt_this->t_prew_rect.i4_left;
                pt_file->t_thumb_rect.i4_right  = pt_this->t_prew_rect.i4_right;
            }
        }

        ui4_dst_x = 0;
        ui4_dst_y = 0;

        if(MMP_PE_RC_SUPPORT_FULL_DECODING() && b_need_rotate && b_use_full_decode)
        {
            ui4_dst_h = (UINT32)WGL_RECT_GET_WIDTH(&(pt_file->t_thumb_rect));
            ui4_dst_w = (UINT32)WGL_RECT_GET_HEIGHT(&(pt_file->t_thumb_rect));
            if (pt_disp->ui4_buf_width > pt_disp->ui4_buf_height)
            {
                //mmp_drc_rotate_buf(pt_disp);
            }
        }
        else
        {
            ui4_dst_w = (UINT32)WGL_RECT_GET_WIDTH(&(pt_file->t_thumb_rect));
            ui4_dst_h = (UINT32)WGL_RECT_GET_HEIGHT(&(pt_file->t_thumb_rect));
        }

        MMP_DBG_INFO(("[PhotoEng][_mmp_pe_load_preview] Print thumbnail rect.\r\n"));
        _mmp_pe_rect_print(pt_file->t_thumb_rect);

        _MMP_PE_NEW_LOAD_VER(pt_this);

        /*load image*/
        t_type_data.pv_tag = (VOID*)pt_this->ui4_load_ver;
        t_type_data.ui4_data_flag = IMG_TYPE_DATA_TAG;
        t_type_data.t_animated.b_animated = FALSE;
        t_type_data.t_animated.ui4_frame_index = 0;
        t_type_data.b_load_more_frame = FALSE;

        if(!(_MMP_PE_FLAG_QUICK_ROTATE & pt_this->ui4_flag))
        {
            ui4_dst_x = (UINT32)pt_file->t_thumb_rect.i4_left;
            ui4_dst_y = (UINT32)pt_file->t_thumb_rect.i4_top;
        }
#ifdef APP_3D_PHOTO_SUPPORT
        ui4_dst_w = (ui4_dst_w >> 1) << 1;
        ui4_dst_x = ui4_dst_x / 2 * 2;//to be even
#endif

        MMP_DBG_INFO(("[PhotoEng][_mmp_pe_load_preview] \
            ui4_dst_x=%d;\
            ui4_dst_y=%d;\
            ui4_dst_w=%d;\
            ui4_dst_h=%d.\r\n",
            ui4_dst_x, ui4_dst_y, ui4_dst_w, ui4_dst_h));

        pt_disp->ui4_x = ui4_dst_x;
        pt_disp->ui4_y = ui4_dst_y;
        pt_disp->ui4_w = ui4_dst_w;
        pt_disp->ui4_h = ui4_dst_h;
        pt_disp->ui4_scale = _MMP_PE_ACCURACY_CONST;

        #if 0
        i4_ret = c_img_async_load(pt_file->h_img,
                                  INTRA_IMG_PRIMARY_IMG_TYPE,
                                  &t_type_data,
                                  e_best_rotate,
                                  0,
                                  0,
                                  pt_file->z_img_w,
                                  pt_file->z_img_h,
                                  ui4_dst_x,
                                  ui4_dst_y,
                                  ui4_dst_w,
                                  ui4_dst_h,
                                  pt_disp->h_surf);

        if (pt_disp == pt_this->pt_buf_crnt_disp)
        {
            MMP_DBG_ERROR(("c_img_async_load using the current disp\r\n"));
            MMP_ASSERT(0);
        }

        if(i4_ret!=IMGR_OK)
        {
            _MMP_PE_SET_LOAD_VER_INVALID(pt_file->ui4_crnt_load_ver);
            MMP_DBG_ERROR(("c_img_async_load() failed. i4_ret = %d.\r\n", i4_ret));
            i4_ret = MMPR_FAIL;
            break; /*break do-while(0)*/
        }
        #endif

        i4_ret = MMPR_OK;

    } while (0);

    if(i4_ret!=MMPR_OK && (_MMP_PE_IMG_FLAG_WITH_THUMB & pt_file->ui2_flag))
    {
        /*notify client main image end*/
        pt_this->pf_play_nfy(pt_this->pv_play_nfy_tag, pt_this->ui4_play_ver, MMP_PE_PLAY_NFY_ID_DEC_IMG_END,FALSE);
    }

    if(i4_ret==MMPR_OK)
    {
        /*update state*/
        pt_file->ui4_crnt_load_ver = pt_this->ui4_load_ver;
        pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_IMG_LOADING;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: xxxxxxxxxxxxxxxxxxx
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
#define MMP_EVENT_PHOTO_NOTIFY_BIT_SHIFT        (16)
#define MMP_EVENT_PHOTO_N_NOTIFY(N)             (MI_BIT(MMP_EVENT_PHOTO_NOTIFY_BIT_SHIFT+N))//0x00XX0000
static MI_S32  gs32PlayEventGroupId;

static INT32 _mmp_pe_gif_format_image_decode_callback(MI_HANDLE hMm, MI_U32 u32Event, void *pNotifyParams, void *pUserParams)
{
    MI_MM_Event_e eEvent = (MI_MM_Event_e)u32Event;

    switch (eEvent)
    {
        case E_MI_MM_EVENT_PHOTO_DECODE_DONE:
            MMP_DBG_INFO(("[mmp mi] %s %d  Photo decode ok!\n",__FUNCTION__,__LINE__));
            MI_OS_SetEvent(gs32PlayEventGroupId, MMP_EVENT_PHOTO_N_NOTIFY(1)); // 1 :success
            break;
        case E_MI_MM_EVENT_PHOTO_DECODE_FAILED:
            MMP_DBG_INFO(("[mmp mi] %s %d  Photo decode fail!\n",__FUNCTION__,__LINE__));
            MI_OS_SetEvent(gs32PlayEventGroupId, MMP_EVENT_PHOTO_N_NOTIFY(2));  // 2 :fail
            break;
        case E_MI_MM_EVENT_PHOTO_DECODE_ONE_FRAME_DONE :
            MMP_DBG_INFO(("[mmp mi] %s %d  Decode one frame ok!\n",__FUNCTION__,__LINE__));
            break;
        case E_MI_MM_EVENT_PHOTO_DISPLAYED:
            MMP_DBG_INFO(("[mmp mi] %s %d  GIF is playing \n",__FUNCTION__,__LINE__));
            MI_OS_SetEvent(gs32PlayEventGroupId, MMP_EVENT_PHOTO_N_NOTIFY(3));  // 3 : playing
            break;
        default:
            break;
    }
    return MI_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_load_image
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_load_image(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    UINT32                      ui4_img_idx)
{
    MI_RESULT eRet = MI_ERR_FAILED;
    _MMP_PE_IMG_FILE_T*         pt_file;
    INT32                       i4_ret;
    IMG_ROTATE_OP_TYPE_T        e_best_rotate;
    SIZE_T                      z_src_w, z_src_h;
    //BOOL                      b_rotate = FALSE;
    SIZE_T                      z_temp;
    UINT32                      ui4_ratio_w, ui4_ratio_h, ui4_dest_x,ui4_dest_y,ui4_dest_w, ui4_dest_h;
    UINT32                      ui4_display_region_w, ui4_display_region_h;
    CHAR*                       ps_file_name;

    ui4_display_region_w = 3820;
    ui4_display_region_h = 2160;

    if(ui4_img_idx >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        return MMPR_INV_ARG;
    }

    pt_file = &pt_this->at_img[ui4_img_idx];

    if(MMP_FID_NULL_REC_IDX == pt_file->t_path)
    {
        return MMPR_INV_ARG;
    }

    /*get file name path by fid*/
    i4_ret = mmp_fid_get(pt_file->t_path, &ps_file_name);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("[mmp pe] %s %d mmp_fid_get(%d) failed. i4_ret = %d.\r\n",__FUNCTION__,__LINE__, pt_file->t_path, i4_ret));
        MMP_ASSERT(0);
        return i4_ret;
    }
    DBG_INFO_DIRECT("[mmp pe] %s %d mmp_fid_get(%d)  ps_file_name:%s  ui4_img_idx:%d  img[x].e_rotate:%d \r\n",__FUNCTION__,__LINE__,pt_file->t_path,ps_file_name,ui4_img_idx,pt_file->e_rotate);

    do
    {
        //0. Check mm module init
        _mmp_pe_mi_module_init();

        //1. Clean screen
        if (MI_HANDLE_NULL != pt_this->h_MI_MM_Hdl)
        {
            //note: much mute disp, as xc is open
            MI_HANDLE hDisp = MI_HANDLE_NULL;
            MI_DISP_QueryHandleParams_t stDispHandleParam;
            memset(&stDispHandleParam, 0, sizeof(MI_DISP_QueryHandleParams_t));
            char szName[MI_MM_NAME_LENGTH] = {0};
            c_snprintf(szName, sizeof(szName), "MI_DISP_HD%d", 0);//0 1 2 3
            stDispHandleParam.pszName = (MI_U8*)szName;
            CHECK_RET(MI_DISP_GetHandle(&stDispHandleParam, &hDisp), MI_OK);
            CHECK_RET(MI_DISP_SetMute(hDisp, E_MI_DISP_MUTE_FLAG_VIDEO), MI_OK);
            //
            CHECK_RET(MI_MM_ClearPhoto(pt_this->h_MI_MM_Hdl),"MI_MM_ClearPhoto");
            CHECK_RET(MI_MM_Stop(pt_this->h_MI_MM_Hdl),"MI_MM_Stop");
            CHECK_RET(MI_MM_Close(pt_this->h_MI_MM_Hdl),"MI_MM_Close");
            pt_this->h_MI_MM_Hdl = MI_HANDLE_NULL;
        }

        //2. Open/Get MI_MM handle
        MI_RESULT eRet = MI_ERR_FAILED;
        char szMmName[32] = {0};
        MI_MM_QueryHandleParams_t stQueryHandleParams;
        memset(&stQueryHandleParams, 0, sizeof(stQueryHandleParams));
        memset(&szMmName, 0, sizeof(szMmName));
        pt_this->h_MI_MM_Hdl = MI_HANDLE_NULL;
        c_snprintf(szMmName, sizeof(szMmName), MI_MM_PHOTO_HANDLE);//0 1 //MI_MM_HANDLE_IDX_0 this name id Fix
        stQueryHandleParams.pszName = (MI_U8 *)szMmName;
        stQueryHandleParams.eMediaType = E_MI_MM_MEDIA_PHOTO;
        eRet = MI_MM_GetHandle(&stQueryHandleParams, &(pt_this->h_MI_MM_Hdl));
        if(eRet != MI_OK || pt_this->h_MI_MM_Hdl == MI_HANDLE_NULL)
        {
            MI_MM_OpenParams_t stOpenParams;
            c_memset(&stOpenParams, 0 ,sizeof(stOpenParams));
            stOpenParams.pszName = (MI_U8 *)szMmName;//need to note: can throuth this pszName and eMediaType find MI_MM_Open() return handle.   use interface is MI_MM_GetHandle()
            stOpenParams.eMediaType = E_MI_MM_MEDIA_PHOTO;
            //1.1 open MM player and get img handle
            eRet = MI_MM_Open(&stOpenParams, &(pt_this->h_MI_MM_Hdl));
            if(eRet != MI_OK || pt_this->h_MI_MM_Hdl == MI_HANDLE_NULL)
            {
                DBG_INFO_DIRECT("[mmp pe] %s %d MI_MM_Open fail!!!!! eRet :%d \r\n",__FUNCTION__,__LINE__,eRet);
                return MMPR_FAIL;
            }

            //1.2 Set AP mode   [note]: effece memery alloc
            MI_MM_ApTypeParams_t stApParams;
            memset(&stApParams, 0, sizeof(stApParams));
            stApParams.eApType = E_MI_MM_AP_TYPE_NORMAL;
            CHECK_RET(MI_MM_SetAttr(pt_this->h_MI_MM_Hdl, E_MI_MM_ATTR_TYPE_SET_AP_TYPE, (void *)&stApParams),"Set AP mode MI_MM_SetAttr");
        }


        //3. Get display handle
        char szWinName[32] = {0};
        MI_DISP_QueryHandleParams_t stDispQueryHandleParams = {0};
        MI_DISP_OpenParams_t stDispOpenParams = {E_MI_DISP_VIDWIN_HD, 0};
        c_memset(&szWinName, 0 ,sizeof(szWinName));
        c_snprintf(szWinName, sizeof(szWinName), "MI_DISP_HD%d", 0);//note : string "MI_DISP_HD" can't be modefied
        stDispQueryHandleParams.pszName = (MI_U8*)szWinName;
        if(MI_DISP_GetHandle(&stDispQueryHandleParams, &(pt_this->h_Disp_Hdl)) != MI_OK)
        {
            stDispOpenParams.pszName = (MI_U8*)szWinName;
            //3.1 if dont't , open display window, get a handle
            if(MI_DISP_Open(&stDispOpenParams, &(pt_this->h_Disp_Hdl)) != MI_OK)
            {
                DBG_INFO_DIRECT("[mmp pe] %s %d  MI_DISP_Open error\n",__FUNCTION__,__LINE__);
                return MMPR_FAIL;
            }
        }

        //4. Gif format Image need Register Decode Callback for waiting for decode
        if(IMG_GIF == pt_file->e_img_type)
        {
            //4.0
            MI_MM_CallbackInputParams_t stInputParams;
            MI_MM_CallbackOutputParams_t stOutputParams;
            memset(&stInputParams, 0, sizeof(stInputParams));
            memset(&stOutputParams, 0, sizeof(stOutputParams));
            stInputParams.pfEventCallback   = _mmp_pe_gif_format_image_decode_callback;
            stInputParams.u32EventFlags     = E_MI_MM_EVENT_ALL;
            eRet = MI_MM_RegisterCallback(pt_this->h_MI_MM_Hdl, &stInputParams, &stOutputParams);
            if ((eRet == MI_OK) && (stOutputParams.u64CallbackId != 0))
            {
                MMP_DBG_ERROR(("[mmp] %s %d Set Callback function Success!!\n",__FUNCTION__,__LINE__));
            }
            else
            {
                DBG_INFO_DIRECT("[mmp pe] %s %d Set Callback function failure!!\n",__FUNCTION__,__LINE__);
                return MMPR_FAIL;
            }

            //4.2 Clear GIF event. before playing
            MI_OS_ClearEvent(gs32PlayEventGroupId, MMP_EVENT_PHOTO_N_NOTIFY(1) | MMP_EVENT_PHOTO_N_NOTIFY(2) | MMP_EVENT_PHOTO_N_NOTIFY(3));
        }


        // Update state
        pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_IMG_LOADING;
        MMP_DBG_INFO(("[mmp] %s %d MI_MM_Start Decode Start......\r\n\r\n\r\n",__FUNCTION__,__LINE__));


        //5. Start decode file
        MI_MM_StartParams_t stStartParams;
        memset(&stStartParams, 0, sizeof(stStartParams));
        stStartParams.bInitOnly                         = FALSE;
        stStartParams.bIsLowLatencyMode                 = FALSE;
        stStartParams.bPreviewEnable                    = FALSE;
        stStartParams.pu8DirMemInputBuf                 = (MI_U8 *)0;  //from dram display
        stStartParams.u32DirMemInputBufLen              = 0;
        stStartParams.stPreviewSetting.eMode            = E_MI_MM_PREVIEW_NORMAL_MODE ;
        stStartParams.stPreviewSetting.u32VideoPauseTime= 0;
        stStartParams.eFileOption                       = E_MI_MM_FILE_MODE;
        stStartParams.pszFileName                       = (MI_U8*)ps_file_name;
        stStartParams.hDisplay                          = pt_this->h_Disp_Hdl;
        eRet= MI_MM_Start(pt_this->h_MI_MM_Hdl, &stStartParams);
        if(eRet != MI_OK)
        {
            _mmp_pe_set_img_bad_or_corrupt(pt_this, pt_file, _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_BAD);
            DBG_INFO_DIRECT("[mmp pe] %s %d MI_MM_Start Decode Error!!!! eRet = %d\r\n",__FUNCTION__,__LINE__,eRet);
            //Clean screen
            if (MI_HANDLE_NULL != pt_this->h_MI_MM_Hdl)
            {
                //note: much mute disp, as xc is open
                MI_HANDLE hDisp = MI_HANDLE_NULL;
                MI_DISP_QueryHandleParams_t stDispHandleParam;
                memset(&stDispHandleParam, 0, sizeof(MI_DISP_QueryHandleParams_t));
                char szName[MI_MM_NAME_LENGTH] = {0};
                c_snprintf(szName, sizeof(szName), "MI_DISP_HD%d", 0);//0 1 2 3
                stDispHandleParam.pszName = (MI_U8*)szName;
                CHECK_RET(MI_DISP_GetHandle(&stDispHandleParam, &hDisp), MI_OK);
                CHECK_RET(MI_DISP_SetMute(hDisp, E_MI_DISP_MUTE_FLAG_VIDEO), MI_OK);
                //noto end
                CHECK_RET(MI_MM_ClearPhoto(pt_this->h_MI_MM_Hdl),"MI_MM_ClearPhoto");
                CHECK_RET(MI_MM_Stop(pt_this->h_MI_MM_Hdl),"MI_MM_Stop");
                CHECK_RET(MI_MM_Close(pt_this->h_MI_MM_Hdl),"MI_MM_Close");
                pt_this->h_MI_MM_Hdl = MI_HANDLE_NULL;
            }
            //Update flag
            pt_file->ui2_flag &= ~_MMP_PE_IMG_FLAG_IMG_LOADING;
            DBG_INFO_DIRECT("[mmp pe] %s %d File is over limitation.\r\n",__FUNCTION__,__LINE__);
            return MMPR_OK;
        }
        // Block decode image when imgae is no gif format
        if(IMG_GIF != pt_file->e_img_type)
        {
            MMP_DBG_INFO(("[mmp] %s %d MI_MM_Start Decode OK!!\r\n",__FUNCTION__,__LINE__));
        }
        else
        {
            //5.1
            DBG_INFO_DIRECT("[mmp pe] %s %d GIF e_fp_rotate:%d \r\n",__FUNCTION__,__LINE__,pt_file->e_rotate);

            //Set Strecth Mode and Image play rotate angle
            MI_MM_RotateAngle_e eAngle = MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE;
            MI_MM_PhotoStretchMode_e AttrParams = E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN;
            DBG_INFO_DIRECT("[mmp pe] %s %d e_fp_rotate:%d \r\n",__FUNCTION__,__LINE__,pt_file->e_rotate);
            switch(pt_file->e_rotate)
            {
                case IMG_ROTATE_CLOCKWS_0_OP_TYPE:
                case IMG_ROTATE_CLOCKWS_0_OP_TYPE_WITH_FLIP:
                    eAngle = E_MI_MM_ROTATE_0;
                    break;
                case IMG_ROTATE_CLOCKWS_90_OP_TYPE:
                case IMG_ROTATE_CLOCKWS_90_OP_TYPE_WITH_FLIP:
                    eAngle = E_MI_MM_ROTATE_90;
                    break;
                case IMG_ROTATE_CLOCKWS_180_OP_TYPE:
                case IMG_ROTATE_CLOCKWS_180_OP_TYPE_WITH_FLIP:
                    eAngle = E_MI_MM_ROTATE_180;
                    break;
                case IMG_ROTATE_CLOCKWS_270_OP_TYPE:
                case IMG_ROTATE_CLOCKWS_270_OP_TYPE_WITH_FLIP:
                    eAngle = E_MI_MM_ROTATE_270;
                    break;
                default:
                    eAngle = E_MI_MM_ROTATE_0;
                    break;
            }

            //note: 3840*2160 / 1920*1080 image if strecth is E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN will cannot full screen, because data will be align 16
            if(eAngle != E_MI_MM_ROTATE_90 && eAngle !=E_MI_MM_ROTATE_270 && pt_file->z_img_w%1920 == 0 && pt_file->z_img_h%1080 == 0)
                AttrParams = E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN_STRETCH;
            else
                AttrParams = E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN;

            CHECK_RET(MI_MM_SetAttr(pt_this->h_MI_MM_Hdl,E_MI_MM_ATTR_TYPE_SET_PHOTO_DISPALY_STRECTH_MODE, (void *)AttrParams),"MI_MM_SetAttr");
            CHECK_RET(MI_MM_SetAttr(pt_this->h_MI_MM_Hdl,E_MI_MM_ATTR_TYPE_SET_PHOTO_ROTATE, (void *)eAngle),"MI_MM_SetAttr");




            #if 0
            //5.1 Waiting Gif format image Decode ok!!! and  UnRegister Decode Callback
            // wait event E_MI_MM_EVENT_PLAYING_INIT_OK from MI_MM_Start
            MI_OS_WaitEventParams_t stWaitEventParams;
            MI_U32  u32RetrievedEventFlag = 0;
            memset(&stWaitEventParams, 0, sizeof(stWaitEventParams));
            stWaitEventParams.s32EventGroupId   = gs32PlayEventGroupId;
            stWaitEventParams.eWaitMode         = E_MI_OS_EVENT_WAIT_MODE_OR_CLEAR;
            stWaitEventParams.u32WaitMs         = 10000;
            stWaitEventParams.u32WaitEventFlag  = MMP_EVENT_PHOTO_N_NOTIFY(1) | MMP_EVENT_PHOTO_N_NOTIFY(2); // 1 : decode OK, 2: decode failed.
            MMP_DBG_ERROR(("[mmp] %s %d Wait event!!\n", __FUNCTION__, __LINE__));
            //MI_OS_ClearEvent(stWaitEventParams.s32EventGroupId, USBMMPLAYER_EVENT_PHOTO_N_NOTIFY(1) | USBMMPLAYER_EVENT_PHOTO_N_NOTIFY(2));
            MI_OS_WaitEvent(&stWaitEventParams, &u32RetrievedEventFlag);
            if(u32RetrievedEventFlag == MMP_EVENT_PHOTO_N_NOTIFY(2) || u32RetrievedEventFlag == 0)
            {
                MMP_DBG_ERROR(("[mmp] %s %d GIF decode failed!!flag = %u\n",  __FUNCTION__,__LINE__, (unsigned int)u32RetrievedEventFlag));
                //Update flag
                pt_file->ui2_flag &= ~_MMP_PE_IMG_FLAG_IMG_LOADING;
                _mmp_pe_set_img_bad_or_corrupt(pt_this, pt_file, _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_BAD);
                return MMPR_OK;
            }
            //5.2 Clear GIF event. before playing
            MI_OS_ClearEvent(gs32PlayEventGroupId, MMP_EVENT_PHOTO_N_NOTIFY(1) | MMP_EVENT_PHOTO_N_NOTIFY(2) | MMP_EVENT_PHOTO_N_NOTIFY(3));
            #endif
        }

        _MMP_PE_NEW_LOAD_VER(pt_this);


        //6. Play image
#ifdef MMP_PHOTO_USE_MI_MM_MODULE
        // Get image decode statue
        MI_MM_PhotoDecoderStatus_e ePhotoDecoderStatus;
        eRet= MI_MM_GetPhotoDecoderStatus(pt_this->h_MI_MM_Hdl, &ePhotoDecoderStatus);
        if(eRet != MI_OK || ePhotoDecoderStatus != E_MI_MM_PHOTO_DECODE_OK)
        {
            MMP_DBG_INFO(("[mmp] %s %d MI_MM_GetPhotoDecoderStatus Error!!!\r\n",__FUNCTION__,__LINE__));
        }
        MMP_DBG_INFO(("[mmp] %s %d MI_MM_GetPhotoDecoderStatus End!!!\r\n",__FUNCTION__,__LINE__));
#endif

        // Update state
        pt_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_IMG_LOADING);

        //
        //7. Draw image  ---------------------------------------
        MMP_DBG_INFO(("[mmp] %s %d Play_Image_e_state:::%d !!!\r\n",__FUNCTION__,__LINE__,pt_this->e_state));
        switch(pt_this->e_state)
        {
            case MMP_PLAY_STATE_PLAYING:
                {
                    i4_ret = _mmp_pe_play_image(pt_this, pt_file, TRUE);
                    _mmp_pe_update_state(pt_this, _MMP_PE_STATE_UPDATE_TYPE_VIEW, i4_ret, TRUE);
                }
                break;
            case MMP_PLAY_STATE_STOPPED:
            case MMP_PLAY_STATE_PAUSED:
                {
                    //Claen flag
                    if(_MMP_PE_FLAG_FILE_NEXTING & pt_this->ui4_flag)
                    {
                        pt_file->ui2_flag &= ~(_MMP_PE_FLAG_FILE_NEXTING);
                        pt_this->ui4_flag &= ~(_MMP_PE_FLAG_NEXT_IS_PLAY);
                    }
                    else if(_MMP_PE_IMG_FLAG_IMG_ZOOMING & pt_file->ui2_flag)
                    {
                        pt_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_IMG_ZOOMING);
                    }
                    else if(_MMP_PE_IMG_FLAG_IMG_ROTATING & pt_file->ui2_flag)
                    {
                        pt_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_IMG_ROTATING);
                    }

                    i4_ret = _mmp_pe_play_image(pt_this, pt_file, FALSE);
                    _mmp_pe_update_state(pt_this, _MMP_PE_STATE_UPDATE_TYPE_VIEW, i4_ret, FALSE);
                }
                break;
            default:
                return MMPR_INTERNAL_ERROR;
        }

        i4_ret = MMPR_OK;

    } while (0);

    return i4_ret;
}


//bug
INT32 mmp_thumbnailmode_for_pe_get_hlt_idx(VOID);
INT32 mmp_thumbnailmode_for_pe_get_item_idx(VOID);


typedef unsigned char  U1;
typedef unsigned short U2;
typedef unsigned long  U4;


typedef struct {
    U4 u4_image_width;
    U4 u4_image_height;
    U4 u4_widthbyte;
    U4 u4_image_size;
    U2 u2_bitcount;
    U2 u2_palette_size;
    U1* u1_p_image_data;
} ST_BITMAP;


void vd_SerializeLittleEndianU2(U1 * u1_ap_serial, U2 u2_a_value)
{
    do
    {
        if(u1_ap_serial == NULL)
            break;
        u1_ap_serial[0] = (U1)u2_a_value;
        u1_ap_serial[1] = (U1)(u2_a_value >> 8);
    } while(FALSE);
}

void vd_SerializeLittleEndianU3(U1 * u1_ap_serial, U4 u4_a_value)
{
    do
    {
        if(u1_ap_serial == NULL)
            break;

        u1_ap_serial[0] = (U1)u4_a_value;
        u1_ap_serial[1] = (U1)(u4_a_value >> 8);
        u1_ap_serial[2] = (U1)(u4_a_value >> 16);
    } while(FALSE);
}

void vd_SerializeLittleEndianU4(U1 * u1_ap_serial, U4 u4_a_value)
{
    do
    {
        if(u1_ap_serial == NULL)
            break;
        u1_ap_serial[0] = (U1)u4_a_value;
        u1_ap_serial[1] = (U1)(u4_a_value >> 8);
        u1_ap_serial[2] = (U1)(u4_a_value >> 16);
        u1_ap_serial[3] = (U1)(u4_a_value >> 24);
    } while(FALSE);
}


static INT32 _usb_get_root_path(CHAR*  s_path, SIZE_T  z_size)
{
    INT32   i4_ret= -1;
    UINT32  ui4_mnt_count = 0;
    UINT32  ui4_mnt_point_idx = 0;
    RMV_DEV_DEVICE_STATUS_T         t_rmv_dev_status;

    a_rmv_dev_lock();

    i4_ret = a_rmv_dev_get_mnt_count (& ui4_mnt_count);
    if (i4_ret != RMVR_OK)
    {
        DBG_LOG_PRINT(("No usb disk found.\n"));
        a_rmv_dev_unlock();
        return -1;
    }

    if (ui4_mnt_count == 0)
    {
        DBG_LOG_PRINT(("No usb disk found.\n"));
        a_rmv_dev_unlock();
        return -1;
    }

    for(ui4_mnt_point_idx = 0;
        ui4_mnt_point_idx < ui4_mnt_count;
        ui4_mnt_point_idx ++)
    {
        /* Get the mount point status */
        i4_ret= a_rmv_dev_get_mnt_point_status_by_idx(ui4_mnt_point_idx,
                                                          &t_rmv_dev_status);

        if (i4_ret != RMVR_OK)
        {
            continue;
        }

        /* Check the mount point status */
        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(t_rmv_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(t_rmv_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(t_rmv_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(t_rmv_dev_status)))
        {
            continue;
        }

        i4_ret = a_rmv_dev_get_mnt_point(ui4_mnt_point_idx,
                                 &z_size,
                                 s_path);
        break;

    }

    a_rmv_dev_unlock();

    return 0;
}



void vd_g_SaveBitmap(const ST_BITMAP * st_ap_bitmap, const char *p_file_name)
{
    BOOL b_t_success = FALSE;

    U1 u1_tp_bitmap_header[] =
    {
        0x42, 0x4D, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, //  2 AA->FileSize
        0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0x28, 0x00, // 10 BB->OffBits
        0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xDD, 0xDD, // 18 CC->Width
        0xDD, 0xDD, 0x01, 0x00, 0xEE, 0xEE, 0x00, 0x00, // 22 DD->Height
        0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, // 28 EE->BitCount
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34 FF->ImageSize
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    HANDLE_T h_file = NULL_HANDLE;
    UINT32 ui4_write = 0;
    UINT32 i4_ret = 0;

    U4 u4_t_y;
    U4 u4_t_pixel_offset = 0;

    char usb_root_path[128] = {0};
    char file_full_path[255] = {0};
    static int num = 1;
    num++;


    /* get the usb root path */
    i4_ret = _usb_get_root_path(usb_root_path, sizeof(usb_root_path));
    if (0 != i4_ret)
    {
        return i4_ret;
    }

    do
    {
        if(st_ap_bitmap == NULL)
            break;

        if((st_ap_bitmap->u2_bitcount != 16) && (st_ap_bitmap->u2_bitcount != 24) && (st_ap_bitmap->u2_bitcount != 32))
            break;

        sprintf(file_full_path,"%s/%s",usb_root_path,p_file_name);
        i4_ret = c_fm_open(FM_ROOT_HANDLE, file_full_path, FM_OPEN_CREATE|FM_READ_WRITE, 0777, FALSE, &h_file);
        DBG_INFO_DIRECT("c_fm_open %s!!\r\n",file_full_path);
        if(i4_ret != 0)
        {
            break;
        }

        // set bitmap head info
        vd_SerializeLittleEndianU4(&u1_tp_bitmap_header[2], sizeof(u1_tp_bitmap_header) + st_ap_bitmap->u4_image_size);
        vd_SerializeLittleEndianU4(&u1_tp_bitmap_header[10], sizeof(u1_tp_bitmap_header));
        vd_SerializeLittleEndianU4(&u1_tp_bitmap_header[18], st_ap_bitmap->u4_image_width);
        vd_SerializeLittleEndianU4(&u1_tp_bitmap_header[22], st_ap_bitmap->u4_image_height);
        vd_SerializeLittleEndianU2(&u1_tp_bitmap_header[28], st_ap_bitmap->u2_bitcount);
        vd_SerializeLittleEndianU4(&u1_tp_bitmap_header[34], st_ap_bitmap->u4_image_size);

        // write bitmap file head
        i4_ret = c_fm_write(h_file, u1_tp_bitmap_header, sizeof(u1_tp_bitmap_header) , &ui4_write);
        if(i4_ret != 0)
        {
            MMP_DBG_ERROR(("c_fm_write failed!!\r\n"));
            break;
        }

        // write bitmap image data, bottom to top
        u4_t_pixel_offset = st_ap_bitmap->u4_image_height * st_ap_bitmap->u4_widthbyte;
        for(u4_t_y = 0; u4_t_y < st_ap_bitmap->u4_image_height; u4_t_y++)
        {
            u4_t_pixel_offset -= st_ap_bitmap->u4_widthbyte;
            c_fm_write(h_file, (VOID *)(st_ap_bitmap->u1_p_image_data+u4_t_pixel_offset), st_ap_bitmap->u4_widthbyte , &ui4_write);
        }
    } while(0);


    i4_ret = c_fm_close(h_file);
    if(i4_ret != 0)
    {
        MMP_DBG_INFO(("c_fm_write failed!!\r\n"));
    }

    MMP_DBG_INFO(("c_fm comp!!\r\n"));

}

static MI_U8 _mmp_pe_mi_osd_get_pixel_byte(MI_OSD_ColorFormat_e eColorFmt, MI_U8 *pu8Bpp)
{
    switch(eColorFmt)
    {
        case E_MI_OSD_COLOR_FORMAT_ARGB8888:
        case E_MI_OSD_COLOR_FORMAT_ABGR8888:
        case E_MI_OSD_COLOR_FORMAT_RGBA8888:
        case E_MI_OSD_COLOR_FORMAT_BGRA8888:
            *pu8Bpp = 4;
            break;
        case E_MI_OSD_COLOR_FORMAT_RGB565:
        case E_MI_OSD_COLOR_FORMAT_BGR565:
        case E_MI_OSD_COLOR_FORMAT_ARGB4444:
        case E_MI_OSD_COLOR_FORMAT_ARGB1555:
        case E_MI_OSD_COLOR_FORMAT_YUV422_YVYU:
        case E_MI_OSD_COLOR_FORMAT_YUV422_UYVY:
        case E_MI_OSD_COLOR_FORMAT_YUV422_YUYV:
        case E_MI_OSD_COLOR_FORMAT_1ABFGBG12355:
        case E_MI_OSD_COLOR_FORMAT_FABAFGBG2266:
            *pu8Bpp = 2;
            break;
        case E_MI_OSD_COLOR_FORMAT_I1:
        case E_MI_OSD_COLOR_FORMAT_I2:
        case E_MI_OSD_COLOR_FORMAT_I4:
        case E_MI_OSD_COLOR_FORMAT_I8:
            *pu8Bpp = 1;
            break;
        default:
            DBG_ERROR(("not defined format!\n"));
            *pu8Bpp = 0;
    }
    if(*pu8Bpp == 0)
        return MI_ERR_FAILED;

    return MI_OK;
}


static MI_RESULT _MI_MM_CreateSrcDstSurface(
    MI_HANDLE *phSrcSurf, MI_HANDLE *phDstSurf,
    MI_OSD_Rect_t *pstSrcRect, MI_OSD_Rect_t *pstDstRect,
    MI_VIRT virtSrc, MI_VIRT virtDst
)
{
    MI_OSD_SurfaceInfo_t stSurfInfo;
    MI_HANDLE hSrcSurf = MI_HANDLE_NULL;
    MI_HANDLE hDstSurf = MI_HANDLE_NULL;
    MI_OSD_ColorFormat_e eSrcFmt = E_MI_OSD_COLOR_FORMAT_ARGB8888;
    MI_OSD_ColorFormat_e eDstFmt = E_MI_OSD_COLOR_FORMAT_ARGB8888;
    MI_U8 u8Bpp = 1;

    if(phSrcSurf == NULL || phDstSurf == NULL || pstSrcRect == NULL || pstDstRect == NULL)
        return MI_ERR_INVALID_PARAMETER;

    if(virtDst == NULL || virtSrc == NULL)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Error: phy is NULL phySrc=0x%llx, phyDst=0x%llx",__FUNCTION__,__LINE__, virtSrc, virtDst));
        return MI_ERR_FAILED;
    }

    //create src surface
    memset(&stSurfInfo,0x00, sizeof(MI_OSD_SurfaceInfo_t));
    stSurfInfo.eColorFormat = eSrcFmt;
    CHECK_RET(_mmp_pe_mi_osd_get_pixel_byte(eSrcFmt, &u8Bpp), "mi_osd_GetPixelByte");
    stSurfInfo.u32Pitch = pstSrcRect->u32Width*u8Bpp;   // byte = pixel*bpp
    stSurfInfo.u32Width = pstSrcRect->u32Width;
    stSurfInfo.u32Height = pstSrcRect->u32Height;
    MMP_DBG_INFO(("[mmp] %s %d Src surface(inter buf): (w, h, p, f)=(%u, %u, %u, %u)\n",__FUNCTION__,__LINE__, stSurfInfo.u32Width, stSurfInfo.u32Height, stSurfInfo.u32Pitch, stSurfInfo.eColorFormat));

    stSurfInfo.virtAddr = virtSrc;
    stSurfInfo.eMemoryType = E_MI_OSD_MEMORY_OS;
    stSurfInfo.eOwner = E_MI_OSD_SURFACE_OWNER_AP;
    CHECK_RET(MI_OSD_SurfaceCreate(&stSurfInfo, &hSrcSurf), "MI_OSD_SurfaceCreate");
    *phSrcSurf = hSrcSurf;

    //create dst surface
    memset(&stSurfInfo,0x00, sizeof(MI_OSD_SurfaceInfo_t));
    stSurfInfo.eColorFormat = eDstFmt;
    CHECK_RET(_mmp_pe_mi_osd_get_pixel_byte(eDstFmt, &u8Bpp), "mi_osd_GetPixelByte");
    stSurfInfo.u32Pitch = pstDstRect->u32Width*u8Bpp;   // byte = pixel*bpp
    stSurfInfo.u32Width = pstDstRect->u32Width;
    stSurfInfo.u32Height = pstDstRect->u32Height;
    MMP_DBG_INFO(("[mmp] %s %d Dst surface(display buf): (w, h, p, f)=(%u, %u, %u, %u)\n",__FUNCTION__,__LINE__, stSurfInfo.u32Width, stSurfInfo.u32Height, stSurfInfo.u32Pitch, stSurfInfo.eColorFormat));
    stSurfInfo.virtAddr= virtDst;
    stSurfInfo.eMemoryType = E_MI_OSD_MEMORY_OS;
    stSurfInfo.eOwner = E_MI_OSD_SURFACE_OWNER_AP;
    CHECK_RET(MI_OSD_SurfaceCreate(&stSurfInfo, &hDstSurf), "MI_OSD_SurfaceCreate");
    *phDstSurf = hDstSurf;
    return MI_OK;
}



static int _mmp_pe_mi_image_rotate(
    MI_OSD_Rect_t *pstSrcRect,
    MI_OSD_Rect_t *pstDstRect,
    MI_VIRT virtSrcAddr,
    MI_VIRT virtDstAddr,
    MI_MM_RotateAngle_e rotate
)
{
    MI_HANDLE hSrcSurface = MI_HANDLE_NULL;
    MI_HANDLE hDstSurface = MI_HANDLE_NULL;
    MI_RESULT u32Ret = MI_ERR_FAILED;

    if(rotate<E_MI_MM_ROTATE_INVALID || rotate>E_MI_MM_ROTATE_270)
        return u32Ret;

    _MI_MM_CreateSrcDstSurface(&hSrcSurface, &hDstSurface,
                                pstSrcRect, pstDstRect,
                                virtSrcAddr, virtDstAddr);

    //MMP_DBG_INFO(("_MI_MM_CreateSrcDstSurface Out\r\n"));

    // bitblit from SrcBuf to DstBuf
    MI_OSD_BlitOpt_t stBlitOpt = {0};
    u32Ret = MI_OSD_GetDefaultBlitOpt(&stBlitOpt);
    if(u32Ret != MI_OK)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Error 0x%x: failed to MI_OSD_GetDefaultBlitOpt()!\n",__FUNCTION__,__LINE__, u32Ret));
        goto END;
    }
    stBlitOpt.eRotate = (MI_OSD_Rotate_e)rotate;
    stBlitOpt.eSrcYuvFormat = E_MI_OSD_YUV422_YUYV;
    stBlitOpt.eDstYuvFormat = E_MI_OSD_YUV422_YUYV;
    stBlitOpt.stClipRect.u32X = 0;
    stBlitOpt.stClipRect.u32Y = 0;
    stBlitOpt.stClipRect.u32Width   = pstDstRect->u32Width;
    stBlitOpt.stClipRect.u32Height  = pstDstRect->u32Height;

    MI_OSD_RenderJob_t stRenderJob;
    memset(&stRenderJob, 0, sizeof(MI_OSD_RenderJob_t));

    MI_OSD_BeginDraw();
    u32Ret = MI_OSD_Bitblit(hSrcSurface, pstSrcRect, hDstSurface, pstDstRect, &stBlitOpt, NULL);
    if(u32Ret != MI_OK)
    {
       MMP_DBG_ERROR(("[mmp] %s %d Error 0x%x: failed to MI_OSD_Bitblit()!\n",__FUNCTION__,__LINE__, u32Ret));
    }
    u32Ret = MI_OSD_WaitRenderDone(&stRenderJob);
    if(u32Ret != MI_OK)
    {
       MMP_DBG_ERROR(("[mmp] %s %d Error 0x%x: failed to MI_OSD_WaitRenderDone()!\n",__FUNCTION__,__LINE__, u32Ret));
    }
    MI_OSD_EndDraw();


END:

    if(hSrcSurface != MI_HANDLE_NULL)
    {
        CHECK_RET(MI_OSD_SurfaceDestroy(hSrcSurface), "MI_OSD_SurfaceDestroy");
    }
    if(hDstSurface != MI_HANDLE_NULL)
    {
        CHECK_RET(MI_OSD_SurfaceDestroy(hDstSurface), "MI_OSD_SurfaceDestroy");
    }

    return u32Ret;
}




/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_load_thumbnail
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_load_thumbnail(
    _MMP_PE_DATA_MEMBER_T*      pt_this,                /*IN*/
    _MMP_PE_INFO_INST_T*        pt_this_obj,            /*IN*/
    IMG_TYPE_T                  e_img_type,             /*IN*/
    HANDLE_T                    h_load_surf,            /*IN*/
    HANDLE_T                    h_show_surf,            /*IN*/
    const GL_RECT_T*            pt_boundary_rect,       /*IN*/
    BOOL                        b_no_main_thumb,        /*IN*/
    BOOL                        b_empty_show,           /*IN*/
    BOOL                        b_empty_if_err,         /*IN*/
    BOOL                        b_info_page_thum,       /*IN*/
    MMP_FP_LOAD_IMG_ROTATE_OP_T e_rotate_op,            /*IN*/
    IMG_INTRA_TYPE_T*           pe_thumb_type,          /*OUT*/
    GL_RECT_T*                  pt_show_rect,           /*OUT*/
    UINT32*                     pui4_load_ver)          /*OUT*/
{
    _MMP_PE_ROTATE_GROUP_T      e_group;
    SIZE_T                      z_width = 0, z_height = 0;
    UINT32                      ui4_src_w = 0, ui4_src_h = 0, ui4_ratio_w, ui4_ratio_h;
    UINT32                      ui4_rect_w, ui4_rect_h;
    UINT32                      ui4_dst_w = 0, ui4_dst_h = 0, ui4_dst_x = 0, ui4_dst_y = 0;
    INT32                       i4_ret;
    BOOL                        b_need_rotate = FALSE;
    EXIF_INFO_T                 t_rotate_info;
    IMG_ROTATE_OP_TYPE_T        e_rotate = IMG_ROTATE_CLOCKWS_0_OP_TYPE;

    MI_RESULT eRet              = MI_ERR_FAILED;
    char szMmName[32]           = {0};
    MI_MM_QueryHandleParams_t   stQueryHandleParams;
    MI_MM_OpenParams_t          stOpenParams;
    char szWinName[32]          = {0};
    MI_DISP_QueryHandleParams_t stDispQueryHandleParams = {0};
    MI_DISP_OpenParams_t        stDispOpenParams = {E_MI_DISP_VIDWIN_HD, 0};
    MI_MM_StartParams_t         stStartParams;
    MI_MM_PhotoInfo_t           stPhotoInfo;
    CHAR*                       ps_file_name;

    if(pt_this == NULL || pt_show_rect == NULL || pt_boundary_rect == NULL|| pt_this_obj == NULL || MMP_FID_NULL_REC_IDX == pt_this_obj->t_path)
    {
        return MMPR_FAIL;
    }

    /*get file name by fid*/
    i4_ret = mmp_fid_get(pt_this_obj->t_path, &ps_file_name);
    if(MMPR_OK != i4_ret)
    {
        DBG_INFO_DIRECT("[mmp pe] %s %d  mmp_fid_get(%d) failed. i4_ret = %d.\r\n", __FUNCTION__,__LINE__, pt_this_obj->t_path, i4_ret);
        pt_this_obj->t_path = MMP_FID_NULL_REC_IDX;
        return MMPR_FAIL;
    }
    DBG_INFO_DIRECT("[mmp pe] %s %d mmp_fid_add(%d) e_rotate_op:%d!  ps_file_name:%s !!!!! \r\n",__FUNCTION__,__LINE__,pt_this_obj->t_path,e_rotate_op, ps_file_name);

#ifdef MMP_PHOTO_USE_MI_MM_MODULE

    // Get image info and flie_size/resolution limit
    _MMP_IMAGE_INFO imageInfo = {0};
    BOOL b_meet_all = FALSE;
    i4_ret = mmp_pe_get_image_info(ps_file_name,&imageInfo);
    if(i4_ret != 0)
    {
        DBG_INFO_DIRECT("[mmp pe] %s %d File is error.\r\n",__FUNCTION__,__LINE__);
        return MMPR_FAIL;
    }
    _mmp_pe_get_img_limitation_info(ps_file_name,&imageInfo.PhotoType,(VOID *)&b_meet_all);
    if(!b_meet_all)
    {
        DBG_INFO_DIRECT("[mmp pe] %s %d File is over limitation.\r\n",__FUNCTION__,__LINE__);
       return MMPR_FAIL;;
    }

    if(E_FS_FORMAT_PNG == imageInfo.PhotoType || E_FS_FORMAT_BMP == imageInfo.PhotoType || E_FS_FORMAT_GIF == imageInfo.PhotoType || E_FS_FORMAT_JPEG == imageInfo.PhotoType)
    {
        //Check force rotate op
        _MMP_PE_GET_ROTATE_TYPE_FROM_OP(e_rotate_op, e_rotate);
    }
    else
    {
        DBG_INFO_DIRECT("[mmp pe] %s %d unknown photo type!\r\n",__FUNCTION__,__LINE__);
        return MMPR_FAIL;
    }

#ifdef MMP_PHOTO_USE_MI_MM_MODULE

    do
    {
        //0. Check mi module init
        _mmp_pe_mi_module_init();

        //1. Check/Close Thumbnial handle /readly
        if (pt_this->h_MI_MM_Hdl != MI_HANDLE_NULL)
        {
            CHECK_RET(MI_MM_Stop(pt_this->h_MI_MM_Hdl), MI_OK);
            CHECK_RET(MI_MM_Close(pt_this->h_MI_MM_Hdl), MI_OK);
            pt_this->h_MI_MM_Hdl = MI_HANDLE_NULL;
        }

        //2. Open MM player and get Thumbnial handle
        c_memset(&szMmName, 0, sizeof(szMmName));
        c_snprintf(szMmName, sizeof(szMmName), MI_MM_PHOTO_THUMBNAIL_HANDLE);//0 1 //MI_MM_HANDLE_IDX_0 this name id Fix
        c_memset(&stOpenParams, 0 ,sizeof(stOpenParams));
        stOpenParams.pszName    = (MI_U8 *)szMmName;
        stOpenParams.eMediaType = E_MI_MM_MEDIA_PHOTO;
        eRet = MI_MM_Open(&stOpenParams, &(pt_this->h_MI_MM_Hdl));
        if(eRet != MI_OK || pt_this->h_MI_MM_Hdl == MI_HANDLE_NULL)
        {
            DBG_INFO_DIRECT("[mmp pe] %s %d re MI_MM_Open fail:  ret:%d!!!!!\r\n",__FUNCTION__,__LINE__,eRet);
            return MMPR_FAIL;
        }

        //3. Set AP mode
        MI_MM_ApTypeParams_t stApParams;
        memset(&stApParams, 0, sizeof(stApParams));
        stApParams.eApType = E_MI_MM_AP_TYPE_NORMAL;
        eRet = MI_MM_SetAttr(pt_this->h_MI_MM_Hdl, E_MI_MM_ATTR_TYPE_SET_AP_TYPE, (void *)&stApParams);
        if (eRet !=  MI_OK)
        {
            MMP_DBG_ERROR(("[mmp] %s %d Set AP mode Failure!!\r\n",__FUNCTION__,__LINE__));
        }

        //4. Get/Open MI Display handle (??? need ???)
        c_memset(&szWinName, 0 ,sizeof(szWinName));
        c_snprintf(szWinName, sizeof(szWinName), "MI_DISP_HD%d", 0);//0 1
        stDispQueryHandleParams.pszName = (MI_U8*)szWinName;
        if(MI_DISP_GetHandle(&stDispQueryHandleParams, &(pt_this->h_Disp_Hdl)) != MI_OK)
        {
            stDispOpenParams.pszName = (MI_U8*)szWinName;
            //4.1 If don't , open display window, get a handle
            if(MI_DISP_Open(&stDispOpenParams, &(pt_this->h_Disp_Hdl)) != MI_OK)
            {
                DBG_INFO_DIRECT("[mmp pe] %s %d MI_DISP_Open error\n",__FUNCTION__,__LINE__);
                return MMPR_FAIL;
            }
        }
        MMP_DBG_INFO(("[mmp] %s %d MI_MM_Start Decode/InitOnly Start  FileName:%s\r\n",__FUNCTION__,__LINE__,ps_file_name));

        //5. Gif format Image need Register Decode Callback for waiting for decode
        MI_MM_CallbackInputParams_t stInputParams;
        MI_MM_CallbackOutputParams_t stOutputParams;
        if(E_FS_FORMAT_GIF == imageInfo.PhotoType)
        {
            memset(&stInputParams, 0, sizeof(stInputParams));
            memset(&stOutputParams, 0, sizeof(stOutputParams));
            stInputParams.pfEventCallback   = _mmp_pe_gif_format_image_decode_callback;
            stInputParams.u32EventFlags     = E_MI_MM_EVENT_ALL;
            eRet = MI_MM_RegisterCallback(pt_this->h_MI_MM_Hdl, &stInputParams, &stOutputParams);
            if ((eRet == MI_OK) && (stOutputParams.u64CallbackId != 0))
            {
                DBG_INFO_DIRECT("[mmp pe] %s %d Set Callback function Success!!\n",__FUNCTION__,__LINE__);
            }
            else
            {
                DBG_INFO_DIRECT("[mmp pe] %s %d Set Callback function failure!!\n",__FUNCTION__,__LINE__);
                return MMPR_FAIL;
            }

            //5.1 Clear GIF event. before playing
            MI_OS_ClearEvent(gs32PlayEventGroupId, MMP_EVENT_PHOTO_N_NOTIFY(1) | MMP_EVENT_PHOTO_N_NOTIFY(2) | MMP_EVENT_PHOTO_N_NOTIFY(3));
        }

        //6. Start Decode Image for get Thumbnail data
        memset(&stStartParams, 0, sizeof(stStartParams));
        ////////////////////////////////////////////////////////////////////////////////////////////////
        stStartParams.bInitOnly                         = TRUE;     ///////note.. thumbnail much be true.....................
        stStartParams.bIsLowLatencyMode                 = FALSE;
        stStartParams.bPreviewEnable                    = FALSE;
        stStartParams.pu8DirMemInputBuf                 = (MI_U8 *)0;  //from dram display
        stStartParams.u32DirMemInputBufLen              = 0;
        stStartParams.stPreviewSetting.eMode            = E_MI_MM_PREVIEW_NORMAL_MODE ;
        stStartParams.stPreviewSetting.u32VideoPauseTime= 0;
        stStartParams.eFileOption                       = E_MI_MM_FILE_MODE;
        stStartParams.pszFileName                       = (MI_U8*)ps_file_name;
        stStartParams.hDisplay                          = pt_this->h_Disp_Hdl;
        eRet= MI_MM_Start(pt_this->h_MI_MM_Hdl, &stStartParams);/// block open imgic
        if(eRet != MI_OK)
        {
            DBG_INFO_DIRECT("[mmp pe] %s %d MI_MM_Start Decode Error!!!!eRet = %d\r\n",__FUNCTION__,__LINE__,eRet);
            return MMPR_FAIL;
        }
        DBG_INFO_DIRECT("[mmp pe] %s %d MI_MM_Start Decode OK!!\r\n",__FUNCTION__,__LINE__);


        //7. Waiting Gif format image Decode ok!!!  and  UnRegister Decode Callback
        if(E_FS_FORMAT_GIF == imageInfo.PhotoType)
        {
            // wait event E_MI_MM_EVENT_PLAYING_INIT_OK from MI_MM_Start
            MI_OS_WaitEventParams_t stWaitEventParams;
            MI_U32  u32RetrievedEventFlag = 0;
            memset(&stWaitEventParams, 0, sizeof(stWaitEventParams));
            stWaitEventParams.s32EventGroupId   = gs32PlayEventGroupId;
            stWaitEventParams.eWaitMode         = E_MI_OS_EVENT_WAIT_MODE_OR_CLEAR;
            stWaitEventParams.u32WaitMs         = 10000;
            stWaitEventParams.u32WaitEventFlag  = MMP_EVENT_PHOTO_N_NOTIFY(1) | MMP_EVENT_PHOTO_N_NOTIFY(2); // 1 : decode OK, 2: decode failed.
            MMP_DBG_ERROR(("[mmp] %s %d Wait event!!\n", __FUNCTION__, __LINE__));
            //MI_OS_ClearEvent(stWaitEventParams.s32EventGroupId, USBMMPLAYER_EVENT_PHOTO_N_NOTIFY(1) | USBMMPLAYER_EVENT_PHOTO_N_NOTIFY(2));
            MI_OS_WaitEvent(&stWaitEventParams, &u32RetrievedEventFlag);
            if(u32RetrievedEventFlag == MMP_EVENT_PHOTO_N_NOTIFY(2) || u32RetrievedEventFlag == 0)
            {
                MMP_DBG_ERROR(("[mmp] %s %d GIF decode failed!!flag = %u\n",  __FUNCTION__,__LINE__, (unsigned int)u32RetrievedEventFlag));
                break;
            }

            //6.1 UnRegister Gif image Decode Callback
            MI_MM_CallbackInputParams_t stInputParams;
            memset(&stInputParams, 0, sizeof(stInputParams));
            stInputParams.u64CallbackId = stOutputParams.u64CallbackId;
            if (stInputParams.u64CallbackId != 0)
            {
                eRet = MI_MM_UnRegisterCallback(pt_this->h_MI_MM_Hdl, &stInputParams);
                if (eRet != MI_OK)
                {
                    MMP_DBG_ERROR(("[mmp] %s %d Error: 0x%x, u64CallbackId(0x%llx) fail to MI_MM_UnRegisterCallback()\n", __FUNCTION__, __LINE__,eRet, stInputParams.u64CallbackId));
                    break;
                }
            }
        }

        //8. Fix bug: reopen image again
        memset(&stPhotoInfo,0,sizeof(MI_MM_PhotoInfo_t));
        CHECK_RET(MI_MM_GetPhotoInfo(pt_this->h_MI_MM_Hdl, &stPhotoInfo),"MI_MM_GetPhotoInfo");
        if(stPhotoInfo.u32PhotoOutputWidth == 0 || stPhotoInfo.u32PhotoOutputHeight == 0)
        {
            continue;//will run again do--while(1)
        }
        #if 0
        MMP_DBG_INFO(("[mmp] %s %d output w:%d. h:%d\r\n", __FUNCTION__, __LINE__, stPhotoInfo.u32PhotoOutputWidth, stPhotoInfo.u32PhotoOutputHeight));
        MMP_DBG_INFO(("[mmp] %s %d output pitch:%d. progress:%d\r\n", __FUNCTION__, __LINE__, stPhotoInfo.u32PhotoOutputPitch, stPhotoInfo.u32PhotoDecodeProgress));
        MMP_DBG_INFO(("[mmp] %s %d source w:%d. h:%d\r\n", __FUNCTION__, __LINE__, stPhotoInfo.u32PhotoSourceWidth, stPhotoInfo.u32PhotoSourceHeight));
        MMP_DBG_INFO(("[mmp] %s %d ERR:%d. photo_type:%d\r\n", __FUNCTION__, __LINE__, stPhotoInfo.u32PhotoErrCode, stPhotoInfo.ePhotoType));
        MMP_DBG_INFO(("[mmp] %s %d Has Thumbnail: %d \r\n", __FUNCTION__, __LINE__, stPhotoInfo.bThumbnailExist));
        MMP_DBG_INFO(("[mmp] %s %d Has Date: %d \r\n", __FUNCTION__, __LINE__, stPhotoInfo.bDateExist));
        MMP_DBG_INFO(("[mmp] %s %d Year: %d Month: %d\r\n", __FUNCTION__, __LINE__, stPhotoInfo.stDateTime.u32Year, stPhotoInfo.stDateTime.u32Month));
        MMP_DBG_INFO(("[mmp] %s %d Day: %d Hour: %d\r\n", __FUNCTION__, __LINE__, stPhotoInfo.stDateTime.u32Day, stPhotoInfo.stDateTime.u32Hour));
        MMP_DBG_INFO(("[mmp] %s %d Minute: %d second: %d\r\n", __FUNCTION__, __LINE__, stPhotoInfo.stDateTime.u32Minute, stPhotoInfo.stDateTime.u32Second));
        #endif
#endif
        //9. Calculate Get Thumbnial width/height By rotate and decoede get width/height info
        z_height = stPhotoInfo.u32PhotoSourceHeight;
        z_width  = stPhotoInfo.u32PhotoSourceWidth;
        if(z_width == 0 || z_height == 0)//eg. rotate::::90 z_width:1024  z_height:574
        {
            return -1;
        }
        break;
    }while(1);


    // Calcalete ,,,,,,,,
    do
    {
        //
        if(MMP_PE_RC_SUPPORT_FULL_DECODING())
        {
            e_group = _mmp_pe_get_angle_group(e_rotate);
            if(_MMP_PE_ROTATE_GROUP_1 == e_group || _MMP_PE_ROTATE_GROUP_3 == e_group)
            {
                b_need_rotate = TRUE;
            }
            e_rotate = IMG_ROTATE_CLOCKWS_0_OP_TYPE;
        }
        e_group = _mmp_pe_get_angle_group(e_rotate);
        if(_MMP_PE_ROTATE_GROUP_1 == e_group || _MMP_PE_ROTATE_GROUP_3 == e_group) /*90, 270 without flip / 90, 270 with flip*/
        {
            ui4_src_w = z_height;
            ui4_src_h = z_width;
        }
        else
        {
            ui4_src_w = z_width;//1024  574
            ui4_src_h = z_height;
        }

        // Get destination width and height
        if(MMP_PE_RC_SUPPORT_FULL_DECODING()&& b_need_rotate)
        {
            ui4_rect_h = (UINT32)WGL_RECT_GET_WIDTH(pt_boundary_rect);//eg. rotate::::90 ui4_rect_h:296  ui4_rect_w:216
            ui4_rect_w = (UINT32)WGL_RECT_GET_HEIGHT(pt_boundary_rect);
        }
        else
        {
            ui4_rect_w = (UINT32)WGL_RECT_GET_WIDTH(pt_boundary_rect);
            ui4_rect_h = (UINT32)WGL_RECT_GET_HEIGHT(pt_boundary_rect);
        }
        MMP_DBG_INFO(("[mmp pe] %s %d b_need_rotate:%d boundary_rect:::::: ui4_rect_h:%d  ui4_rect_w:%d \r\n", __FUNCTION__,__LINE__,b_need_rotate,ui4_rect_h,ui4_rect_w));

        //Consider mi mm fet_thumbnail need align 16, so need add/sub some num for boundary w/h
        UINT32 boundary_rect_w          = (UINT32)WGL_RECT_GET_WIDTH(pt_boundary_rect);
        UINT32 boundary_rect_h          = (UINT32)WGL_RECT_GET_HEIGHT(pt_boundary_rect);
        UINT32 boundary_rect_add_w      = 0;
        UINT32 boundary_rect_add_h      = 0;
        if(boundary_rect_w%16 != 0)  //note: only preview will come in
        {
            UINT32 boundary_rect_align16_w  = 0;
            boundary_rect_align16_w = ((int)(boundary_rect_w/16))*16;//288
            boundary_rect_add_w     = ((boundary_rect_w - boundary_rect_align16_w)/2); //eg.  preview(296, 216)  296 -288 = 8/2 = 4
        }
        if(boundary_rect_h%16 != 0)
        {
            UINT32 boundary_rect_align16_h  = 0;
            boundary_rect_align16_h = ((int)(boundary_rect_h/16))*16;                        //eg.  3X3 thumbnail(288,228)  224
            boundary_rect_add_h     = (boundary_rect_h - boundary_rect_align16_h)/2; //eg.  3X3 thumbnail(288,228)  (228-224)/2 = 2
        }
        //------------------------------------------------------------------------------------------

        // calc rectangle...keep aspect ratio
        // eg. rotate::::90
        // ui4_ratio_w = 216 * _MMP_PE_ACCURACY_CONST / 574  = 3763
        // ui4_ratio_h = 296 * _MMP_PE_ACCURACY_CONST / 1024 = 2890
        ui4_ratio_w = ui4_rect_w * _MMP_PE_ACCURACY_CONST / ui4_src_w; //288*10000/1024 = 2812.5
        ui4_ratio_h = ui4_rect_h * _MMP_PE_ACCURACY_CONST / ui4_src_h; //228*10000/574  = 3972.1
        if(ui4_ratio_w > ui4_ratio_h) /*keep height*/
        {
            ui4_dst_w = ui4_rect_h * ui4_src_w / ui4_src_h; //eg. rotate::::90    ui4_dst_w = 296 * 574 / 1024 = 165
            if(0 == ui4_dst_w)
            {
                ui4_dst_w = 1; /*for special width*/
            }
            if (ui4_dst_w < 4 && (E_MI_MM_INFO_SUB_TYPE_JPEG == stPhotoInfo.ePhotoType))
            {
                ui4_dst_w = 4;
            }
            ui4_dst_w = ALIGN_N(ui4_dst_w,16);
            if(ui4_dst_w > WGL_RECT_GET_HEIGHT(pt_boundary_rect))
                ui4_dst_w = ui4_dst_w - 16;
            if((ui4_rect_w - ui4_dst_w) > MMP_PE_RC_ASPECT_RATIO_TOLERANCE)//eg. rotate::::90  216-165 = 51
            {
                ui4_dst_x = ((ui4_rect_w - ui4_dst_w) >> 1); //eg. rotate::::90  (216-165)/2 = 25
                if(MMP_PE_RC_SUPPORT_FULL_DECODING() && b_need_rotate)//
                {
                    pt_show_rect->i4_top    = pt_boundary_rect->i4_top + ((ui4_rect_w - ui4_dst_w) >> 1); // +25
                    pt_show_rect->i4_bottom = pt_show_rect->i4_top + ui4_dst_w; // + 165
                    pt_show_rect->i4_left   = pt_boundary_rect->i4_left;
                    pt_show_rect->i4_right  = pt_boundary_rect->i4_right;
                }
                else
                {
                    pt_show_rect->i4_top    = pt_boundary_rect->i4_top + boundary_rect_add_h;
                    pt_show_rect->i4_bottom = pt_boundary_rect->i4_bottom - (boundary_rect_add_h+boundary_rect_add_h);
                    pt_show_rect->i4_left   = pt_boundary_rect->i4_left + ui4_dst_x;// +25
                    pt_show_rect->i4_right  = pt_show_rect->i4_left + ui4_dst_w; // + 165
                }
            }
            else /*near the original apsect ratio*/
            {
                *pt_show_rect = *pt_boundary_rect;
            }
            DBG_INFO_DIRECT("[mmp pe] %s %d %s ui4_ratio_w:%d ui4_ratio_h:%d ui4_dst_w:%d ui4_rect_w-ui4_dst_w =%d  add_w:%d add_h:%d\r\n",__FUNCTION__, __LINE__,(b_need_rotate?"<keep height>":"<keep width >"),ui4_ratio_w,ui4_ratio_h,ui4_dst_w,(ui4_rect_w-ui4_dst_w),boundary_rect_add_w,boundary_rect_add_h);
        }
        else /*keep width*/
        {
            ui4_dst_h = ui4_rect_w * ui4_src_h / ui4_src_w;//288*574/1024  = 161.4       1200/1600
            if(0 == ui4_dst_h)
            {
                ui4_dst_h = 1; /*for special height*/
            }
            if (ui4_dst_h < 4 && (E_MI_MM_INFO_SUB_TYPE_JPEG == stPhotoInfo.ePhotoType))
            {
                ui4_dst_h = 4;
            }
            ui4_dst_h = ALIGN_N(ui4_dst_h,16);
            if(ui4_dst_h > WGL_RECT_GET_HEIGHT(pt_boundary_rect))
                ui4_dst_h = ui4_dst_h - 16;
            ui4_dst_y = ((ui4_rect_h - ui4_dst_h) >> 1);//(228 - 161.4)/2 = 33.5
            if((ui4_rect_h - ui4_dst_h) > MMP_PE_RC_ASPECT_RATIO_TOLERANCE)//228  > 161.4
            {
                if(MMP_PE_RC_SUPPORT_FULL_DECODING() && b_need_rotate)
                {
                    pt_show_rect->i4_left   = pt_boundary_rect->i4_left + ((ui4_rect_h - ui4_dst_h) >> 1);
                    pt_show_rect->i4_right  = pt_show_rect->i4_left + ui4_dst_h;
                    pt_show_rect->i4_top    = pt_boundary_rect->i4_top + boundary_rect_add_h;     //3X3 thumbnail(288,228) align 228 == 240,   240 -228 = 12
                    pt_show_rect->i4_bottom = pt_boundary_rect->i4_bottom - (boundary_rect_add_h + (boundary_rect_add_h*2));  //preview(296, 216)
                }
                else
                {
                    pt_show_rect->i4_left   = pt_boundary_rect->i4_left + boundary_rect_add_w * 2;  //703
                    pt_show_rect->i4_right  = pt_boundary_rect->i4_right;                           //703+288
                    pt_show_rect->i4_top    = pt_boundary_rect->i4_top + ui4_dst_y; //133 + 33.5 = 167
                    pt_show_rect->i4_bottom = pt_show_rect->i4_top + ui4_dst_h;     //133 + 33.5 + 161.4 = 328
                }
            }
            else /*near the original apsect ratio*/
            {
                *pt_show_rect = *pt_boundary_rect;
            }
            DBG_INFO_DIRECT("[mmp pe] %s %d %s ui4_ratio_w:%d ui4_ratio_h:%d ui4_dst_h:%d ui4_rect_h-ui4_dst_h =%d  add_w:%d add_h:%d\r\n",__FUNCTION__, __LINE__,(b_need_rotate?"<keep height>":"<keep width >"),ui4_ratio_w,ui4_ratio_h,ui4_dst_h,(ui4_rect_h-ui4_dst_h),boundary_rect_add_w,boundary_rect_add_h);
        }

        DBG_INFO_DIRECT("[mmp pe] %s %d Show_Rect: x=%d, y=%d, w=%d, h=%d, b_need_rotate:%d, e_rotate_op:%d\n\r", __FUNCTION__, __LINE__,
            pt_show_rect->i4_left,
            pt_show_rect->i4_top,
            WGL_RECT_GET_WIDTH(pt_show_rect),
            WGL_RECT_GET_HEIGHT(pt_show_rect),b_need_rotate,e_rotate_op);

    }while(0);

    //Get/Rotate Thumbnail/Rreview
#if 1
    do
    {
        UINT32 ui4_show_dst_w = 0;
        UINT32 ui4_show_dst_h = 0;
        UINT32 ui4_thumbnail_src_h = 0;
        UINT32 ui4_thumbnail_src_w = 0;

        if(!b_need_rotate)//0 and 180 degree
        {
            ui4_thumbnail_src_h = ALIGN_N(WGL_RECT_GET_HEIGHT(pt_show_rect),16);
            ui4_thumbnail_src_w = ALIGN_N(WGL_RECT_GET_WIDTH(pt_show_rect),16);//ALIGN_N(WGL_RECT_GET_WIDTH(pt_show_rect),16);
        }
        else             //90 and 270 degree, get no rotate w/h
        {
            ui4_src_w  = z_width;
            ui4_src_h  = z_height;
            ui4_rect_w = WGL_RECT_GET_WIDTH(pt_boundary_rect);
            ui4_rect_h = WGL_RECT_GET_HEIGHT(pt_boundary_rect);

            ui4_ratio_w = ui4_rect_w * _MMP_PE_ACCURACY_CONST / ui4_src_w;
            ui4_ratio_h = ui4_rect_h * _MMP_PE_ACCURACY_CONST / ui4_src_h;
            if(ui4_ratio_w > ui4_ratio_h) /*keep height*/
            {
                ui4_dst_w = ui4_rect_h * ui4_src_w / ui4_src_h;
                if(0 == ui4_dst_w)
                {
                    ui4_dst_w = 1; /*for special width*/
                }
                if (ui4_dst_w < 4 && (E_MI_MM_INFO_SUB_TYPE_JPEG == stPhotoInfo.ePhotoType))
                {
                    ui4_dst_w = 4;
                }
                if((ui4_rect_w - ui4_dst_w) > MMP_PE_RC_ASPECT_RATIO_TOLERANCE)
                {
                    ui4_dst_x = ((ui4_rect_w - ui4_dst_w) >> 1);
                    ui4_thumbnail_src_h = ALIGN_N(WGL_RECT_GET_HEIGHT(pt_boundary_rect),16);
                    ui4_thumbnail_src_w = ALIGN_N(ui4_dst_w,16);
                }
            }
            else /*keep width*/
            {
                ui4_dst_h = ui4_rect_w * ui4_src_h / ui4_src_w;
                if(0 == ui4_dst_h)
                {
                    ui4_dst_h = 1; /*for special height*/
                }
                if (ui4_dst_h < 4 && (E_MI_MM_INFO_SUB_TYPE_JPEG == stPhotoInfo.ePhotoType))
                {
                    ui4_dst_h = 4;
                }
                ui4_dst_y = ((ui4_rect_h - ui4_dst_h) >> 1);//(228 - 161.4)/2 = 33.5
                if((ui4_rect_h - ui4_dst_h) > MMP_PE_RC_ASPECT_RATIO_TOLERANCE)
                {
                    ui4_thumbnail_src_h = ALIGN_N(ui4_dst_h,16);
                    ui4_thumbnail_src_w = ALIGN_N(WGL_RECT_GET_WIDTH(pt_boundary_rect),16);
                }
            }
        }
        DBG_INFO_DIRECT("[mmp pe] %s %d Get origan thumbnail file ---- w:%d h:%d \r\n",__FUNCTION__,__LINE__,ui4_thumbnail_src_w,ui4_thumbnail_src_h);

        if(ui4_thumbnail_src_h>WGL_RECT_GET_HEIGHT(pt_boundary_rect))
            ui4_thumbnail_src_h = ui4_thumbnail_src_h-16;
        if(ui4_thumbnail_src_w>WGL_RECT_GET_WIDTH(pt_boundary_rect))
            ui4_thumbnail_src_w = ui4_thumbnail_src_w-16;

        ui4_show_dst_h      = ALIGN_N(WGL_RECT_GET_HEIGHT(pt_show_rect),16);
        ui4_show_dst_w      = ALIGN_N(WGL_RECT_GET_WIDTH(pt_show_rect),16);//ALIGN_N(WGL_RECT_GET_WIDTH(pt_show_rect),16);

        #if 1
        // Get image origan thumbnail file
        if(_mmp_pe_get_thumbnail_data(pt_this->h_MI_MM_Hdl, (MI_U8 **)&pt_this->p_thumbnail_data ,ui4_thumbnail_src_w,ui4_thumbnail_src_h) != TRUE)
        {
            DBG_INFO_DIRECT("[mmp pe] %s %d _GetThumbnailData failed!!\n",__FUNCTION__,__LINE__);
            i4_ret = MMPR_FAIL;
            break;
        }
        #if 0
        if(pt_show_rect->i4_left == 804)
        {
            ST_BITMAP st_ap_bitmap;
            st_ap_bitmap.u4_image_height = ui4_thumbnail_src_h;
            st_ap_bitmap.u4_image_width  = ui4_thumbnail_src_w;
            st_ap_bitmap.u4_widthbyte    = ui4_thumbnail_src_w*4;
            st_ap_bitmap.u4_image_size   = ui4_thumbnail_src_w * ui4_thumbnail_src_h * 4;
            st_ap_bitmap.u2_palette_size = 0;
            st_ap_bitmap.u2_bitcount     = 32;
            st_ap_bitmap.u1_p_image_data = pt_this->p_thumbnail_data;

            vd_g_SaveBitmap(&st_ap_bitmap, "origan_thumbnail_file.bmp");
        }
        #endif
        //
        if(e_rotate_op != MMP_FP_LOAD_IMG_ROTATE_OP_CLOCKWS_0 && e_rotate_op != MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE)
        {
            MI_OSD_Rect_t stSrcRect;
            MI_OSD_Rect_t stDstRect;
            stSrcRect.u32X = 0;
            stSrcRect.u32Y = 0;
            stSrcRect.u32Height = ui4_thumbnail_src_h;
            stSrcRect.u32Width  = ui4_thumbnail_src_w;

            stDstRect.u32X = 0;
            stDstRect.u32Y = 0;
            stDstRect.u32Height = ui4_show_dst_h;
            stDstRect.u32Width  = ui4_show_dst_w;

            DBG_INFO_DIRECT("[mmp pe] %s %d Rotate Thumbnail Data     ---- w:%d h:%d   show: w:%d h:%d\r\n",__FUNCTION__,__LINE__,ui4_thumbnail_src_w,ui4_thumbnail_src_h,ui4_show_dst_w,ui4_show_dst_h);

            memset((void *)pt_this->p_thumbnail_rotate_data,0,MMP_THUMBNAIL_DATA_MAX_SIZE);
            i4_ret = _mmp_pe_mi_image_rotate(&stSrcRect,
                                             &stDstRect,
                                             MI_ADDR_CAST(MI_VIRT)pt_this->p_thumbnail_data,
                                             MI_ADDR_CAST(MI_VIRT)pt_this->p_thumbnail_rotate_data,
                                             (MI_MM_RotateAngle_e)(e_rotate_op-1));
            if(i4_ret != MI_OK)
            {
                MMP_DBG_ERROR(("[mmp] %s %d Allocate _mmp_pe_mi_image_rotate Memory Fail! %d\r\n", __FUNCTION__, __LINE__,i4_ret));
                i4_ret = MMPR_FAIL;
                break;
            }

            #if 0
            ST_BITMAP st_ap_bitmap;
            st_ap_bitmap.u4_image_height = ui4_show_dst_h;
            st_ap_bitmap.u4_image_width  = ui4_show_dst_w;
            st_ap_bitmap.u4_widthbyte    = ui4_show_dst_w *4;
            st_ap_bitmap.u4_image_size   = ui4_show_dst_w * ui4_show_dst_h * 4;
            st_ap_bitmap.u2_palette_size = 0;
            st_ap_bitmap.u2_bitcount     = 32;
            st_ap_bitmap.u1_p_image_data = pt_this->p_thumbnail_rotate_data;
            vd_g_SaveBitmap(&st_ap_bitmap, "rotate_thumbnail_file.bmp");
            #endif

            MI_OS_DelayTask(10);

            //copy data to p_thumbnail_data buff
            memset((void *)pt_this->p_thumbnail_data,0,MMP_THUMBNAIL_DATA_MAX_SIZE);
            memcpy((void *)pt_this->p_thumbnail_data,(void *)pt_this->p_thumbnail_rotate_data,MMP_THUMBNAIL_DATA_MAX_SIZE);
        }

        //Show thumbnial data to surface
        GL_RECT_T t_show_rect;
        t_show_rect.i4_left     = pt_show_rect->i4_left;
        t_show_rect.i4_top      = pt_show_rect->i4_top;
        t_show_rect.i4_right    = pt_show_rect->i4_left + ui4_show_dst_w;
        t_show_rect.i4_bottom   = pt_show_rect->i4_top + ui4_show_dst_h;
        i4_ret =_mmp_pe_show_thumbnail(pt_this,pt_boundary_rect,&t_show_rect);


        #endif

    }while(0);

#endif

    if (pt_this->h_MI_MM_Hdl != MI_HANDLE_NULL)
    {
        //CHECK_RET(MI_MM_ClearPhoto(pt_this->h_MI_MM_Hdl),"MI_MM_ClearPhoto");
        CHECK_RET(MI_MM_Stop(pt_this->h_MI_MM_Hdl), MI_OK);
        CHECK_RET(MI_MM_Close(pt_this->h_MI_MM_Hdl), MI_OK);
        pt_this->h_MI_MM_Hdl = MI_HANDLE_NULL;
    }



#endif


    //8. if load 3x3 thumbnail ,will send msg to load/show next thumbnial
    #if 0
    _mmp_pe_thumb_load_next_file((VOID*)pt_this_obj,(VOID*)NULL,(VOID*)i4_ret,(VOID*)NULL);

    #else

    //-----
    _MMP_PE_NEW_LOAD_VER(pt_this);

    /*post a message to itself*/
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_CRITICAL,
                                _mmp_pe_thumb_load_next_file,
                                (VOID*)pt_this_obj,
                                (VOID*)NULL,
                                (VOID*)i4_ret,
                                (VOID*)NULL);
    #endif

    *pui4_load_ver = pt_this->ui4_load_ver;
    return MMPR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_play_do_open
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_play_do_open(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    const CHAR*                 ps_filename,
    const UINT8*                pui1_buf,
    SIZE_T                      z_buf_size,
    mmp_pe_play_nfy_fct         pf_nfy,
    VOID*                       pv_tag,
    UINT32                      ui4_ver)
{
    INT32                       i4_ret;

    DBG_INFO_DIRECT("[mmp pe] %s %d ps_filename = %s. ui4_ver = %d.\r\n",__FUNCTION__,__LINE__, ps_filename, ui4_ver);

    if(NULL == pf_nfy)
    {
        MMP_DBG_ERROR(("[mmp] %s %d pf_nfy cannot be NULL.\r\n",__FUNCTION__,__LINE__));
        return MMPR_INV_ARG;
    }

    /**/
    if(_MMP_PE_IMG_IDX_NULL != pt_this->ui1_crnt_img)
    {
        MMP_DBG_ERROR(("[mmp] %s %d A photos is opened.\r\n",__FUNCTION__,__LINE__));
        //return MMPR_FAIL;
    }

    /**/
    if(FALSE == _MMP_PE_IS_LIMIT_INFO_READY(pt_this))
    {
        i4_ret = _mmp_pe_init_limit_info(pt_this);
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }

    //
    MMP_ASSERT(MMP_FID_NULL_REC_IDX == pt_this->at_img[0].t_path && 0 == (_MMP_PE_IMG_FLAG_MEM_FILE & pt_this->at_img[0].ui2_flag));
    pt_this->at_img[0].b_first_photo = TRUE;    // tfx effect will do special handling if the current photo is the first...
    // Keep setting
    pt_this->pf_play_nfy    = pf_nfy;
    pt_this->pv_play_nfy_tag= pv_tag;
    pt_this->ui4_play_ver   = ui4_ver;


    // Open file and get some image info, use img[0]
    i4_ret = _mmp_pe_open_image(pt_this, &pt_this->at_img[0], ps_filename, pui1_buf, z_buf_size);//0
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    do
    {
        /*prepare display resource*/
        if(0 == (_MMP_PE_FLAG_PLAY_DISP_RESUMED & pt_this->ui4_flag))
        {
            i4_ret = _mmp_pe_resume_disp_res(pt_this, FALSE);
            if(MMPR_OK != i4_ret)
            {
                break;
            }
        }

        /*load image*/
        //place here, because  image open block _mmp_pe_load_image
        pt_this->ui1_crnt_img = 0;
        pt_this->e_state = MMP_PLAY_STATE_STOPPED;
        //load image:  0 ----- only use pt_this->at_img[0]
        i4_ret = _mmp_pe_load_image(pt_this, 0);
        if(MMPR_OK != i4_ret)
        {
            _mmp_pe_set_img_bad_or_corrupt(pt_this, &pt_this->at_img[0], _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_CORRUPT);
        }

        return MMPR_IS_OPENED;

    } while(0);

    /*free file*/
    _mmp_pe_close_image(pt_this, &pt_this->at_img[0], TRUE);

    return i4_ret;
}



/*-----------------------------------------------------------------------------
 * Name: mmp_pe_play_do_next_preload
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 mmp_pe_play_do_next_preload(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    const CHAR*                 ps_filename,
    const UINT8*                pui1_buf,
    SIZE_T                      z_buf_size)
{
    MMP_FP_SHOW_ATTR_T          at_play_attr[_MMP_PE_PHOTO_PLAY_ATTR_COUNT];
    MMP_EFFECT_T                t_effect;
    _MMP_PE_IMG_FILE_T          *pt_file, *pt_next_file;
    UINT32                      ui4_next_img,ui4_attr_count;
    INT32                       i4_ret;

    ui4_next_img = (UINT32)((_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img || 1 == pt_this->ui1_crnt_img) ? 0 : 1);
    pt_next_file = &pt_this->at_img[ui4_next_img];

    DBG_INFO_DIRECT("[mmp pe] %s %d ps_filename:%s ui4_next_img:%d\r\n",__FUNCTION__,__LINE__, ps_filename, ui4_next_img);

    /*copy the attribute first*/
    ui4_attr_count = _MMP_PE_PHOTO_PLAY_ATTR_COUNT;
    at_play_attr[0].e_id = MMP_FP_SHOW_ATTR_ID_DURATION;
    at_play_attr[1].e_id = MMP_FP_SHOW_ATTR_ID_EFFECT;
    at_play_attr[1].pv_param = &t_effect;
    i4_ret = _mmp_pe_copy_attr(pt_next_file, &ui4_attr_count, at_play_attr);
    if(MMPR_OK != i4_ret || _MMP_PE_PHOTO_PLAY_ATTR_COUNT != ui4_attr_count)
    {
        MMP_DBG_ERROR(("[mmp] %s %d _mmp_pe_copy_attr() failed, i4_ret = %d, count = %d.\n\r",__FUNCTION__,__LINE__, i4_ret, ui4_attr_count));
        MMP_ASSERT(0);
        return MMPR_INTERNAL_ERROR;
    }

    if(MMP_FID_NULL_REC_IDX != pt_next_file->t_path || 0 != (_MMP_PE_IMG_FLAG_MEM_FILE & pt_next_file->ui2_flag))   /*next file is used.*/
    {
        _mmp_pe_close_image(pt_this, pt_next_file, TRUE);
    }

    /**/
    if(NULL == ps_filename && NULL == pui1_buf)
    {
        return MMPR_OK;
    }


    /*restore the backup play attribute*/
    i4_ret = mmp_pe_play_next_attr_set(_MMP_PE_PHOTO_PLAY_ATTR_COUNT, at_play_attr);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Restore play attribute failed, i4_ret = %d.\n\r",__FUNCTION__,__LINE__, i4_ret));
        return i4_ret;
    }

    /*open file*/
    i4_ret = _mmp_pe_open_image(pt_this, pt_next_file, ps_filename, pui1_buf, z_buf_size);/// inclue loading
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("[mmp] %s %d _mmp_pe_open_image failed, i4_ret = %d.\n\r",__FUNCTION__,__LINE__, i4_ret));
        return i4_ret;
    }


    if(_MMP_PE_IMG_IDX_NULL != pt_this->ui1_crnt_img)
    {
        if(pt_this->ui1_crnt_img >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
        {
            return MMPR_FAIL;
        }

        pt_file = &pt_this->at_img[pt_this->ui1_crnt_img];

        MMP_DBG_INFO(("[mmp] %s %d \
            \r\n ui2_flag = 0x%x \
            \r\n pt_file->b_animation_gif = %d \
            \r\n pt_next_file->b_animation_gif = %d \
            \r\n",__FUNCTION__,__LINE__,\
            pt_file->ui2_flag,\
            pt_file->b_animation_gif,\
            pt_next_file->b_animation_gif));
    }


    /*load image*/
    i4_ret = _mmp_pe_load_image(pt_this, ui4_next_img);  //check loading and cal pe_play_image
    if(MMPR_OK != i4_ret)
    {
        _mmp_pe_set_img_bad_or_corrupt(pt_this, &pt_this->at_img[ui4_next_img], _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_CORRUPT);
    }

    return MMPR_IS_PRELOADED;
}


#if  0
static MI_RESULT _MMP_PE_ConvertColorFmtToRGBA8888(MI_U8 *pu8ThumbnailData)
{
    for(int i = 0; i < MI_MM_THUMBNAIL_WIDTH*MI_MM_THUMBNAIL_HEIGHT; i ++)
    {
        MI_U8 u8RedData;
        u8RedData = pu8ThumbnailData[4*i+2];
        pu8ThumbnailData[4*i+2] = pu8ThumbnailData[4*i+0];
        pu8ThumbnailData[4*i+0] = u8RedData;
    }
    return MI_OK;
}
#endif

static MI_BOOL _mmp_pe_get_thumbnail_data(MI_HANDLE hMm, MI_U8 **pu8ThumbnailData, MI_U16 u32Width, MI_U16 u32Height)
{
    MI_RESULT eRet = MI_ERR_FAILED;
    MI_MM_ThumbnailParams_t stThumbnailParam;
    MI_MM_ThumbnailColorFmt_e eColorFmt = E_MI_MM_THUMBNAIL_COLOR_FMT_ARGB8888;
    MI_U16 u16Pitch = 0;
    MI_BOOL bRet = FALSE;

    if(u32Width <= 0 || u32Height <= 0 || pu8ThumbnailData == NULL)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Thumbnail width or height less 0!!\r\n",__FUNCTION__,__LINE__));
        return FALSE;
    }
#if NEVER    //CID:4515818, "eColorFmt" must be equal to "E_MI_MM_THUMBNAIL_COLOR_FMT_ARGB8888"
    if(eColorFmt >= E_MI_MM_THUMBNAIL_COLOR_FMT_MAX)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Unsupport Thumbnail color format!!\r\n",__FUNCTION__,__LINE__));
        return FALSE;
    }
#endif
    memset(&stThumbnailParam, 0, sizeof(MI_MM_ThumbnailParams_t));
    stThumbnailParam.u32Width  = u32Width;
    stThumbnailParam.u32Height = u32Height;
#if 0    //CID:4515818 ,"eColorFmt" must be equal to "E_MI_MM_THUMBNAIL_COLOR_FMT_ARGB8888"
    if(eColorFmt == E_MI_MM_THUMBNAIL_COLOR_FMT_YUV422)
    {
        u16Pitch = 2;
    }
    else if(eColorFmt == E_MI_MM_THUMBNAIL_COLOR_FMT_RGB565)
    {
        u16Pitch = 2;
    }
    else if(eColorFmt == E_MI_MM_THUMBNAIL_COLOR_FMT_ARGB8888)
    {
        u16Pitch = 4;
    }
    else if(eColorFmt == E_MI_MM_THUMBNAIL_COLOR_FMT_ARGB4444)
    {
        u16Pitch = 2;
    }
    else if(eColorFmt == E_MI_MM_THUMBNAIL_COLOR_FMT_ARGB1555)
    {
        u16Pitch = 2;
    }
    else
    {
        MMP_DBG_ERROR(("[mmp] %s %d Unsupport Thumbnail color format!!\r\n",__FUNCTION__,__LINE__));
        return FALSE;
    }
#endif
    u16Pitch = 4;
    stThumbnailParam.eColorFmt = eColorFmt;
    stThumbnailParam.u32AddrSize = stThumbnailParam.u32Width * stThumbnailParam.u32Height * u16Pitch;

    memset(*pu8ThumbnailData, 0, stThumbnailParam.u32AddrSize);
    stThumbnailParam.pu8Addr = *pu8ThumbnailData;
    MMP_DBG_INFO(("[mmp] %s %d Get Thumbnail Address = %p, Size = 0x%x, color fmt = %d, width = %d, height = %d\r\n",__FUNCTION__, __LINE__ ,
        stThumbnailParam.pu8Addr, stThumbnailParam.u32AddrSize, stThumbnailParam.eColorFmt, stThumbnailParam.u32Width, stThumbnailParam.u32Height));

    eRet = MI_MM_GetThumbnail(hMm, &stThumbnailParam);
    if(eRet != MI_OK)
    {
        MMP_DBG_ERROR(("[mmp] %s %d MI_MM_GetThumbnail failed : %d \r\n",__FUNCTION__,__LINE__,eRet));
        bRet = FALSE;
    }
    else
    {
        MMP_DBG_ERROR(("[mmp] %s %d MI_MM_GetThumbnail successfully \r\n",__FUNCTION__,__LINE__));
        bRet = TRUE;
    }

    return bRet;
}

//
//
//
static VOID _mmp_pe_get_img_limitation_info(const CHAR* ps_filename, MMP_FS_PHOTO_Format_e *pFsPhotoType, VOID*  pv_info)
{
    INT32  i4_ret;
    FM_FILE_INFO_T  t_info;
    BOOL b_ret;


    if(!pv_info || !ps_filename || pFsPhotoType == NULL)
    {
        return;
    }

    //MMAP_MI.h  define
    // |       Format      |   Decode Method   |      Buff Type       |      Buff Size Requirement       |
    // |     BMP/GIF/PNG   |     SW Decode     |    MI_JPD_OUT_ADR    | Output Width*Output Height*4 byte|
    // |        JPEG       | JPBuffD HW Decode |  MI_JPD_READ_BUF_ADR |             fix  0x50000         |
    // |                   |                   |    MI_JPD_OUT_ADR    | Output Width*Output Height*2 byte|
    // |                   |                   |                      | Algne: Width 32byte,Height 16byte|

    *(BOOL*)pv_info = FALSE;

    // Get file info and file photo type
    i4_ret = c_fm_get_info_by_name(NULL_HANDLE, ps_filename, &t_info);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("[mmp] %s %d c_fm_get_info_by_name(%s) failed. i4_ret = %d.\r\n",__FUNCTION__,__LINE__, ps_filename, i4_ret));
        return;
    }
    MMP_DBG_INFO(("[mmp] %s %d c_fm_get_info_by_name  i4_ret:%d   size%d k byte !!!!!!!!\r\n",__FUNCTION__,__LINE__,i4_ret,   ((MI_U32)t_info.ui8_size)/1024));

    //note:
    // if jpeg/jpg  progressive max 1026 * 768
    //              baseline   max  15360 * 8640
    //4M size   MI_JPD_OUT_LEN  0x0000400000
    //if( (pFsPhotoType != E_FS_FORMAT_JPEG && t_info.ui8_size < 0x0000400000))// ||
       // (pFsPhotoType == E_FS_FORMAT_JPEG && t_info.ui8_size < 0x0000500000))
    {
        *(BOOL*)pv_info = (BOOL)TRUE;
    }

}




/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_open_image
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_open_image(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file,
    const CHAR*                 ps_filename,
    const UINT8*                pui1_buf,
    SIZE_T                      z_buf_size)
{
    INT32                       i4_ret = 0;
    BOOL                        b_meet_all  = FALSE;
    _MMP_IMAGE_INFO             imageInfo = {0};

    DBG_INFO_DIRECT("[mmp pe] %s %d filename:%s. ui1_crnt_img = %d. \r\n",__FUNCTION__,__LINE__, ps_filename, pt_this->ui1_crnt_img);

    if(pt_this != NULL && ps_filename != NULL)
    {
        /*keep file name*/
        i4_ret = mmp_fid_add(ps_filename, &pt_file->t_path);
        //DBG_INFO_DIRECT("[mmp pe] %s %d mmp_fid_add(%d) --------------- \r\n",__FUNCTION__,__LINE__, pt_file->t_path);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("[mmp pe] %s %d mmp_fid_add(%d) failed. i4_ret = %d.\r\n",__FUNCTION__,__LINE__, pt_file->t_path, i4_ret));
            MMP_ASSERT(0);
            return i4_ret;
        }
    }
    else
    {
        MMP_DBG_ERROR(("[mmp] %s %d File name/pt_this NULL.\r\n",__FUNCTION__,__LINE__));
        return MMPR_OK;
    }

    // Get image info and judeg image filetype and limit
    memset((void *)&imageInfo,0,sizeof(_MMP_IMAGE_INFO));
    i4_ret = mmp_pe_get_image_info(ps_filename, &imageInfo);
    if(i4_ret != 0)
    {
        DBG_INFO_DIRECT("[mmp pe] %s %d mmp_pe_get_image_info: File is error.\r\n",__FUNCTION__,__LINE__);
    }
    memcpy((void *)(&pt_this->t_image_info),(const void *)&imageInfo,sizeof(_MMP_IMAGE_INFO));
    _mmp_pe_get_img_limitation_info(ps_filename, &imageInfo.PhotoType,(VOID *)&b_meet_all);

    if(!b_meet_all)
    {
        _mmp_pe_set_img_bad_or_corrupt(pt_this, pt_file, _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_BAD);
        DBG_INFO_DIRECT("[mmp pe] %s %d File is over limitation!!!\r\n",__FUNCTION__,__LINE__);
        return MMPR_OK;
    }

    if(pt_this->ui1_crnt_img >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        MMP_DBG_ERROR(("[mmp] %s %d ui1_crnt_img == _MMP_PE_IMG_IDX_NULL \r\n",__FUNCTION__,__LINE__));
        pt_this->ui1_crnt_img = 0;
    }

    // Check type
    switch(imageInfo.PhotoType)
    {
        case E_FS_FORMAT_PNG:
            pt_file->e_img_type = IMG_PNG;
            pt_file->b_animation_gif = FALSE;
            break;
        case E_FS_FORMAT_GIF:
            pt_file->e_img_type = IMG_GIF;
            pt_file->b_animation_gif = TRUE;
            break;
        case E_FS_FORMAT_BMP:
            pt_file->e_img_type = IMG_BMP;
            pt_file->b_animation_gif = FALSE;
            break;
        case E_FS_FORMAT_JPEG:
            pt_file->e_img_type = IMG_JPG;
            pt_file->b_animation_gif = FALSE;
            break;
        default:
            pt_file->e_img_type = IMG_UNKNOWN;
            MMP_DBG_ERROR(("[%s %d] File is over limitation !!!!!\r\n",__FUNCTION__,__LINE__));
            _mmp_pe_set_img_bad_or_corrupt(pt_this, pt_file, _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_BAD);
            break;
    }


    // ....
    // Get image rotation from memory , here no consider jpg format exit
    /*Check force rotate op*/
    _MMP_PE_GET_ROTATE_TYPE_FROM_OP(pt_file->e_force_rotate_op, pt_file->e_rotate);


#ifdef MMP_PHOTO_USE_MI_MM_MODULE
    // Get image dimension
    pt_file->z_img_w = imageInfo.Width;
    pt_file->z_img_h = imageInfo.Height;
#endif

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_close_image
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_close_image(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file,
    BOOL                        b_send_effect_event)
{
    INT32                       i4_ret;

    DBG_INFO_DIRECT("[mmp pe] %s %d \r\n",__FUNCTION__, __LINE__);
    /*free path*/
    if(MMP_FID_NULL_REC_IDX != pt_file->t_path)
    {
        i4_ret = mmp_fid_del(pt_file->t_path);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_fid_del(%d) failed. i4_ret = %d.\r\n", pt_file->t_path, i4_ret));
            MMP_ASSERT(0);
        }
        pt_file->t_path = MMP_FID_NULL_REC_IDX;
    }
    else
    {
        i4_ret = MMPR_OK;
    }

    _mmp_pe_reset_img_file(pt_this, pt_file);

    return i4_ret;
}


/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_update_state
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pe_update_state(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_STATE_UPDATE_TYPE_T e_type,
    INT32                       i4_result,
    BOOL                        b_is_play)
{
    switch(e_type)
    {
        case _MMP_PE_STATE_UPDATE_TYPE_VIEW:
        {
            if(MMPR_IS_PLAYED == i4_result)
            {
                if(b_is_play)
                {
                    pt_this->e_state = MMP_PLAY_STATE_PLAYED;
                }
                else
                {
                    pt_this->e_state = MMP_PLAY_STATE_STOPPED;
                }
            }
            else if(MMPR_OK == i4_result)
            {
                if(b_is_play)
                {
                    pt_this->e_state = MMP_PLAY_STATE_PLAYING;
                }
                else
                {
                    pt_this->e_state = MMP_PLAY_STATE_STOPPED;
                }
            }
            else /*error*/
            {
                pt_this->e_state = MMP_PLAY_STATE_STOPPED;
            }
        }
        break;

        default:
        break;
    }
}


static UINT32 _mmp_pe_rand(VOID)
{
    static UINT32 ui4_mul = 97;
    static UINT32 ui4_add = 33;
    static UINT32 ui4_seed = 12345;

    ui4_seed = ui4_seed * ui4_mul + ui4_add;

    return ui4_seed;
}


/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_play_image
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_play_image(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file,
    BOOL                        b_is_play)
{
    INT32                       i4_ret = 0 ;

    DBG_INFO_DIRECT("[mmp pe] %s %d ui1_crnt_img = %d. b_is_play = %d. \n",__FUNCTION__,__LINE__, pt_this->ui1_crnt_img,b_is_play);

    // check file
    if(_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
    {
        MMP_DBG_ERROR(("[mmp] %s %d No photo is opened.\r\n",__FUNCTION__,__LINE__));
        return MMPR_NO_DATA;
    }

    DBG_INFO_DIRECT("[mmp pe] %s %d MI MM Start Draw Photo ..........................!!!!!!! \r\n",__FUNCTION__,__LINE__);

#ifdef MMP_PHOTO_USE_MI_MM_MODULE


    MI_RESULT eRet;
    if(pt_this->h_MI_MM_Hdl == MI_HANDLE_NULL)
    {
        MMP_DBG_INFO(("[mmp] %s %d Need To MI_MM_GetHandle Error !!\r\n",__FUNCTION__,__LINE__));
        // open MI_MM
        char szMmName[32] = {0};
        MI_MM_QueryHandleParams_t stQueryHandleParams;
        memset(&stQueryHandleParams, 0, sizeof(stQueryHandleParams));
        memset(&szMmName, 0, sizeof(szMmName));
        c_snprintf(szMmName, sizeof(szMmName), MI_MM_PHOTO_HANDLE);
        stQueryHandleParams.pszName = (MI_U8 *)szMmName;
        stQueryHandleParams.eMediaType = E_MI_MM_MEDIA_PHOTO;
        eRet = MI_MM_GetHandle(&stQueryHandleParams, &(pt_this->h_MI_MM_Hdl));
        if(eRet != MI_OK || pt_this->h_MI_MM_Hdl == MI_HANDLE_NULL)
        {
            DBG_INFO_DIRECT("[mmp pe] %s %d MI_MM_GetHandle Error !!\r\n",__FUNCTION__,__LINE__);
            return MMPR_FAIL;
        }

    }

    if (IMG_GIF != pt_file->e_img_type)
    {
        //6. display related setting  mi_mm had modified, can not call
        //CHECK_RET(MI_MM_SetupPhotoDisplay(pt_this->h_MI_MM_Hdl),"MI_MM_SetupPhotoDisplay");

        //Set Strecth Mode and Image play rotate angle
        MI_MM_RotateAngle_e eAngle = MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE;
        MI_MM_PhotoStretchMode_e AttrParams = E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN;
        DBG_INFO_DIRECT("[mmp pe] %s %d e_fp_rotate:%d \r\n",__FUNCTION__,__LINE__,pt_file->e_rotate);
        switch(pt_file->e_rotate)
        {
            case IMG_ROTATE_CLOCKWS_0_OP_TYPE:
            case IMG_ROTATE_CLOCKWS_0_OP_TYPE_WITH_FLIP:
                eAngle = E_MI_MM_ROTATE_0;
                break;
            case IMG_ROTATE_CLOCKWS_90_OP_TYPE:
            case IMG_ROTATE_CLOCKWS_90_OP_TYPE_WITH_FLIP:
                eAngle = E_MI_MM_ROTATE_90;
                break;
            case IMG_ROTATE_CLOCKWS_180_OP_TYPE:
            case IMG_ROTATE_CLOCKWS_180_OP_TYPE_WITH_FLIP:
                eAngle = E_MI_MM_ROTATE_180;
                break;
            case IMG_ROTATE_CLOCKWS_270_OP_TYPE:
            case IMG_ROTATE_CLOCKWS_270_OP_TYPE_WITH_FLIP:
                eAngle = E_MI_MM_ROTATE_270;
                break;
            default:
                eAngle = E_MI_MM_ROTATE_0;
                break;
        }

        //note: 3840*2160 / 1920*1080 image if strecth is E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN will cannot full screen, because data will be align 16
        if(eAngle != E_MI_MM_ROTATE_90 && eAngle !=E_MI_MM_ROTATE_270 && pt_file->z_img_w%1920 == 0 && pt_file->z_img_h%1080 == 0)
            AttrParams = E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN_STRETCH;
        else
            AttrParams = E_MI_MM_PHOTO_STRETCH_MODE_FULL_SCREEN;

        CHECK_RET(MI_MM_SetAttr(pt_this->h_MI_MM_Hdl,E_MI_MM_ATTR_TYPE_SET_PHOTO_DISPALY_STRECTH_MODE, (void *)AttrParams),"MI_MM_SetAttr");
        CHECK_RET(MI_MM_SetAttr(pt_this->h_MI_MM_Hdl,E_MI_MM_ATTR_TYPE_SET_PHOTO_ROTATE, (void *)eAngle),"MI_MM_SetAttr");


        MI_MM_PhotoSlideShowEffect_e pu32Effect;
        MI_MM_PhotoSlideShowEffect_e bu32Effect[7];
        bu32Effect[0] = E_MI_MM_SLIDE_SHOW_EFFECT_BLOCKS_RANDOM;
        bu32Effect[1] = E_MI_MM_SLIDE_SHOW_EFFECT_BAR_WIPE_LEFT_TO_RIGHT;
        bu32Effect[2] = E_MI_MM_SLIDE_SHOW_EFFECT_BAR_WIPE_RIGHT_TO_LEFT;
        bu32Effect[3] = E_MI_MM_SLIDE_SHOW_EFFECT_BOX_WIPE_BOTTOM_LEFT;
        bu32Effect[4] = E_MI_MM_SLIDE_SHOW_EFFECT_BOX_WIPE_TOP_LEFT;
        bu32Effect[5] = E_MI_MM_SLIDE_SHOW_EFFECT_IRIS_WIPE_OUTER;
        bu32Effect[6] = E_MI_MM_SLIDE_SHOW_EFFECT_IRIS_WIPE_CENTER;
        switch(pt_file->t_effect.e_effect)
        {
            case TFX_DISSOLVE:
                pu32Effect = E_MI_MM_SLIDE_SHOW_EFFECT_BLOCKS_RANDOM;
                break;
            case TFX_WIPE_RIGHT:
                pu32Effect = E_MI_MM_SLIDE_SHOW_EFFECT_BAR_WIPE_LEFT_TO_RIGHT;
                break;
            case TFX_WIPE_LEFT:
                pu32Effect = E_MI_MM_SLIDE_SHOW_EFFECT_BAR_WIPE_RIGHT_TO_LEFT;
                break;
            case TFX_WIPE_UP:
                pu32Effect = E_MI_MM_SLIDE_SHOW_EFFECT_BAR_WIPE_BOTTOM_TO_TOP;
                break;
            case TFX_WIPE_DOWN:
                pu32Effect = E_MI_MM_SLIDE_SHOW_EFFECT_BAR_WIPE_TOP_TO_BOTTOM;
                break;
            case TFX_BOX_IN:
                pu32Effect = E_MI_MM_SLIDE_SHOW_EFFECT_IRIS_WIPE_OUTER;
                break;
            case TFX_BOX_OUT:
                pu32Effect = E_MI_MM_SLIDE_SHOW_EFFECT_IRIS_WIPE_CENTER;
                break;
            default: //mmp_tm_rand()%7+1;
                pu32Effect = bu32Effect[_mmp_pe_rand()%6];
                break;
        }

        //7. draws the photo to display buffer
        i4_ret = MI_MM_DrawPhoto(pt_this->h_MI_MM_Hdl,pu32Effect);


#if 0
        MI_MM_PhotoAddr_t stPhotoAddr = {0};
        MI_MM_GetPhotoAddr(pt_this->h_MI_MM_Hdl,&stPhotoAddr);
#if 1//test raw data

            ST_BITMAP st_ap_bitmap;
            st_ap_bitmap.u4_image_height = pt_file->z_img_h;
            st_ap_bitmap.u4_image_width  = pt_file->z_img_w;
            st_ap_bitmap.u4_widthbyte    = pt_file->z_img_w*4;
            st_ap_bitmap.u4_image_size   = pt_file->z_img_w * pt_file->z_img_h * 4;
            st_ap_bitmap.u2_palette_size = 0;
            st_ap_bitmap.u2_bitcount     = 32;
            st_ap_bitmap.u1_p_image_data = (MI_U8 *)stPhotoAddr.virtOutputBufAddr;

            vd_g_SaveBitmap(&st_ap_bitmap);

#endif /* NEVER */

#endif
#endif



    }
    else
    {
        MI_BOOL bIsPlayOk = FALSE;

        // Wait event E_MI_MM_EVENT_PLAYING_INIT_OK from MI_MM_Start
        MI_OS_WaitEventParams_t stWaitEventParams;
        MI_U32  u32RetrievedEventFlag = 0;
        memset(&stWaitEventParams, 0, sizeof(stWaitEventParams));
        stWaitEventParams.s32EventGroupId   = gs32PlayEventGroupId;
        stWaitEventParams.eWaitMode         = E_MI_OS_EVENT_WAIT_MODE_OR_CLEAR;
        stWaitEventParams.u32WaitMs         = 10000;
        stWaitEventParams.u32WaitEventFlag  =MMP_EVENT_PHOTO_N_NOTIFY(1) | MMP_EVENT_PHOTO_N_NOTIFY(2); // 1 : Play OK, 2: Play failed.
        MMP_DBG_INFO(("[mmp] %s %d Wait GIF event!!\r\n",__FUNCTION__,__LINE__));
        MI_OS_WaitEvent(&stWaitEventParams, &u32RetrievedEventFlag);
        if(u32RetrievedEventFlag == MMP_EVENT_PHOTO_N_NOTIFY(2)) //fail
        {
            DBG_INFO_DIRECT("[mmp pe] %s %d GIF plays or decodes failed!!!\r\n",__FUNCTION__,__LINE__);
            return MMPR_IS_PLAYED;
        }
        else if(u32RetrievedEventFlag == MMP_EVENT_PHOTO_N_NOTIFY(1))
        {
            bIsPlayOk = TRUE;
        }

        // Wait until GIF plays done.
        while(bIsPlayOk == FALSE)
        {
            stWaitEventParams.u32WaitEventFlag=MMP_EVENT_PHOTO_N_NOTIFY(1) | MMP_EVENT_PHOTO_N_NOTIFY(2) | MMP_EVENT_PHOTO_N_NOTIFY(3);
            stWaitEventParams.u32WaitMs = 1000;
            MI_OS_WaitEvent(&stWaitEventParams, &u32RetrievedEventFlag);
            if(u32RetrievedEventFlag == MMP_EVENT_PHOTO_N_NOTIFY(1)) //play ok
            {
                bIsPlayOk = TRUE;
            }
            else if(u32RetrievedEventFlag == MMP_EVENT_PHOTO_N_NOTIFY(2)) //play failed.
            {
                MMP_DBG_ERROR(("[mmp] %s %d GIF plays or decodes failed!!\r\n",__FUNCTION__,__LINE__));
                return MMPR_IS_PLAYED;
            }
            else if(u32RetrievedEventFlag == MMP_EVENT_PHOTO_N_NOTIFY(3)) //playing
            {
                MMP_DBG_ERROR(("[mmp] %s %d GIF is still playing!!\r\n",__FUNCTION__,__LINE__));
                continue;
            }
        }

        if(bIsPlayOk == TRUE)
        {
            MMP_DBG_INFO(("[mmp] %s %d GIF plays done!!\r\n",__FUNCTION__,__LINE__));
        }
    }


    //
    if(MI_OK != i4_ret)
    {
        MMP_DBG_ERROR(("[mmp] %s %d MI_MM_DrawPhoto() failed. i4_ret = %d.\r\n",__FUNCTION__,__LINE__, i4_ret));
    }
    else
    {
        pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_IMG_DURING_EFFECT;
        _mmp_pe_update_state(&t_g_photo_eng, _MMP_PE_STATE_UPDATE_TYPE_VIEW, MMPR_IS_PLAYED, b_is_play);
        return MMPR_IS_PLAYED;
    }


    //
    pt_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_IMG_DURING_EFFECT);
    pt_file->b_first_photo = FALSE; // tfx effect will do special handling if it is the first photo..

    // xxxxxxx
    i4_ret = _mmp_pe_update_display(pt_this, pt_file, TRUE);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    // Reset timer and do slider show
    _mmp_pe_reset_play_timer(pt_this, pt_this->ui1_crnt_img, (b_is_play) ? MMP_TIMER_OP_TYPE_RESET : MMP_TIMER_OP_TYPE_STOP);

    return MMPR_IS_PLAYED;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_show_thumbnail
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_show_thumbnail(
    _MMP_PE_DATA_MEMBER_T*      pt_this,                /*IN*/
    const GL_RECT_T*            pt_boundary_rect,       /*IN*/
    GL_RECT_T*                  pt_show_rect)           /*IN*/

{
    INT32  i4_ret = 0;
    UINT32 ui4_x, ui4_y, ui4_w, ui4_h;
    UINT8* pui1_src = NULL, *pui1_dst = NULL;

    if(pt_this->h_thumbnail_plane == NULL_HANDLE || pt_this->h_thumbnail_view == NULL_HANDLE || pt_this->h_thumbnail_surf == NULL_HANDLE || pt_this->p_thumbnail_data == NULL)
    {
        return MMPR_FAIL;
    }

    DBG_INFO_DIRECT("[mmp pe] %s %d  \r\n",__FUNCTION__,__LINE__);

    //Clean Rect
    GL_COLOR_T  t_empty_clr = {255, {0}, {0}, {0}};
    GL_RECT_T  t_clean_rect;
    t_clean_rect.i4_left    = pt_boundary_rect->i4_left;
    t_clean_rect.i4_top     = pt_boundary_rect->i4_top;
    t_clean_rect.i4_right   = pt_boundary_rect->i4_right + 15;
    t_clean_rect.i4_bottom  = pt_boundary_rect->i4_bottom + 15;
    i4_ret = c_gl_surface_draw_rect(pt_this->h_thumbnail_surf,
                                    &t_clean_rect,
                                    &t_empty_clr,
                                    1,
                                    GL_STYLE_FILLED,
                                    GL_SYNC);

    ui4_x = pt_show_rect->i4_left;
    ui4_y = pt_show_rect->i4_top;
    ui4_w = WGL_RECT_GET_WIDTH(pt_show_rect);
    ui4_h = WGL_RECT_GET_HEIGHT(pt_show_rect);

    do
    {

        // Copy Data to Surface
        GL_LOCK_INFO_T  t_lock_info;
        i4_ret = c_gl_surface_lock(pt_this->h_thumbnail_surf, NULL, 0, &t_lock_info);
        if (i4_ret != IMGR_OK)
        {
            MMP_DBG_ERROR(("[mmp] %s %d c_gl_surface_lock() failed. i4_ret = %d.\r\n",__FUNCTION__,__LINE__, i4_ret));
            break;
        }
        UINT32 ui4_pitch = 0;
        ui4_pitch = ui4_w * 4;
        pui1_dst = (UINT8*)t_lock_info.at_subplane[0].pv_bits+ (ui4_y * t_lock_info.at_subplane[0].ui4_pitch + ui4_x*4);
        pui1_src = (UINT8*)pt_this->p_thumbnail_data;
        for (int i =0 ; i < ui4_h; i++)
        {
            x_memcpy(pui1_dst, pui1_src, ui4_pitch);
            pui1_dst += t_lock_info.at_subplane[0].ui4_pitch;
            pui1_src += ui4_pitch;
        }
        i4_ret = c_gl_surface_unlock(pt_this->h_thumbnail_surf, NULL);

        // Flip Surface/View Data to Screen
#ifdef MT5583_MODEL
        i4_ret  = c_gl_plane_flip(pt_this->h_thumbnail_plane, pt_this->h_thumbnail_view, FALSE);
#else
        i4_ret  = c_gl_plane_flip(pt_this->h_thumbnail_plane, pt_this->h_thumbnail_view, TRUE);
#endif
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("[mmp] %s %d c_gl_plane_flip() failed. i4_ret = %d.\r\n",__FUNCTION__,__LINE__, i4_ret));
            break;
        }

        //c_thread_delay(34);
        i4_ret = c_gl_plane_enable(pt_this->h_thumbnail_plane, TRUE);


        i4_ret = MMPR_OK;
    }while(0);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_stop_effect
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_stop_effect(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file,
    BOOL                        b_send_effect_event)
{
    INT32                       i4_ret;

    if(_MMP_PE_IMG_FLAG_IMG_DURING_EFFECT & pt_file->ui2_flag)
    {
        i4_ret = IMGR_OK;

        pt_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_IMG_DURING_EFFECT);

        return MMPR_OK;
    }
    else
    {
        return MMPR_IS_PAUSED;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_pause_image
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_pause_image(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file)
{
    // Fix coverity CID-4641508: Uninitialized scalar variable
    INT32                       i4_ret = MMPR_OK;

    //i4_ret = _mmp_pe_stop_effect(pt_this, pt_file, TRUE);s
    if(MMPR_OK == i4_ret)
    {
        /*When in photo frm, don't show next image when pause current image*/
        if ((MMP_MAIN_AP_STATUS_RESUMED_PHOTO_FRM != a_mmp_get_ap_status())&&(MMP_MAIN_AP_STATUS_RESUMED_PHOTO_SHARE!= a_mmp_get_ap_status()))
        {
            i4_ret = _mmp_pe_update_display(pt_this, pt_file, TRUE);
        }
    }

    if(MMPR_OK != i4_ret && MMPR_IS_PAUSED != i4_ret)
    {
        return i4_ret;
    }

    /*stop timer*/
    _mmp_pe_reset_play_timer(pt_this, pt_this->ui1_crnt_img, MMP_TIMER_OP_TYPE_STOP);

    return MMPR_IS_PAUSED;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_stop_next_image_preload
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: TRUE -- next image is during loading
 ----------------------------------------------------------------------------*/
static BOOL _mmp_pe_stop_next_image_preload(VOID)
{
    _MMP_PE_IMG_FILE_T*         pt_next_file;
    UINT32                      ui4_next_img;
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    //INT32                       i4_ret = -1;

    ui4_next_img = (UINT32)((1 == pt_this->ui1_crnt_img) ? 0 : 1);
    pt_next_file = &pt_this->at_img[ui4_next_img];

    if(_MMP_PE_IMG_FLAG_IMG_LOADING & pt_next_file->ui2_flag)
    {
        /*cancel next loading*/
        //i4_ret = c_img_stop(pt_next_file->h_img, IMG_STOP_PRIMARY_OP_TYPE);
        //if(MMPR_OK != i4_ret && IMGR_FILE_ERR != i4_ret && IMGR_ALREADY_STOP != i4_ret)
        //{
        //    MMP_ASSERT(0);
        //}

        pt_next_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_IMG_LOADING);
        pt_next_file->ui2_flag |= _MMP_PE_IMG_FLAG_IMG_LOADING_SUSPEND;

        //mmp_drc_unlock_buf(pt_next_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC]);

        return TRUE;
    }

    return FALSE;
}

#ifdef MMP_TWO_BUFF_SUPPORT_PROGRESSIVE
/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_clean_next_image_preload
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: TRUE -- next image is during loading
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_clean_next_image_preload(VOID)
{
    _MMP_PE_IMG_FILE_T*         pt_next_file;
    UINT32                      ui4_next_img;
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;

    ui4_next_img = (UINT32)((1 == pt_this->ui1_crnt_img) ? 0 : 1);
    pt_next_file = &pt_this->at_img[ui4_next_img];

    /*cancel next loading*/
    //c_img_stop(pt_next_file->h_img, IMG_STOP_PRIMARY_OP_TYPE);

    pt_next_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_IMG_LOADING);
    pt_next_file->ui2_flag |= _MMP_PE_IMG_FLAG_IMG_LOADING_SUSPEND;

    //mmp_drc_unlock_buf(pt_next_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC]);

    return MMPR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_show_preview
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_show_preview(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file,
    BOOL                        b_detach_disp)
{
    return MMPR_OK;
}

#ifdef MMP_TWO_BUFF_SUPPORT_PROGRESSIVE
static INT32 _mmp_pe_progressive_rotate(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file,
    BOOL                        b_detach_disp)
{

    return MMPR_OK;
}
#endif


/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_normal_scale_image
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_normal_scale_image(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file)
{
    _MMP_PE_IMG_FILE_T*         pt_next_file;
    UINT32                      ui4_next_img;
    INT32                       i4_ret, i4_next_ret;
    MMP_DRC_BUF_T*              pt_buf;

    ui4_next_img = (UINT32)((1 == pt_this->ui1_crnt_img) ? 0 : 1);
    pt_next_file = &pt_this->at_img[ui4_next_img];


    if(_MMP_PE_IMG_FLAG_BAD_FILE & pt_file->ui2_flag)
    {
        return MMPR_FAIL;
    }

    if(_MMP_PE_IMG_FLAG_IMG_LOADING & pt_next_file->ui2_flag)
    {
        /*cancel next loading*/
        //i4_ret = c_img_stop(pt_next_file->h_img, IMG_STOP_PRIMARY_OP_TYPE);
       // MMP_ASSERT(MMPR_OK == i4_ret || IMGR_FILE_ERR == i4_ret || IMGR_ALREADY_STOP == i4_ret);

        pt_next_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_IMG_LOADING);
        pt_next_file->ui2_flag |= _MMP_PE_IMG_FLAG_IMG_LOADING_SUSPEND;
    }

    /*blank screen first*/
    i4_ret = _mmp_pe_detach_display(pt_this);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /*clean surface if buffer is ready*/
    pt_buf = pt_file->t_working_buf.at_buf[_MMP_PE_WORKING_BUF_ID_SRC];
    if(NULL != pt_buf)
    {
        //_MMP_PE_ZERO_COLOR(t_empty_clr, 255);
        //i4_ret = c_gl_surface_fill(pt_buf->h_surf, &t_empty_clr, GL_SYNC);
        //if(GLR_OK != i4_ret)
        //{
        //    MMP_DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d.\r\n", i4_ret));
        //}
    }

    /*apply rotation and zoom*/
    i4_ret = _mmp_pe_load_image(pt_this, pt_this->ui1_crnt_img);
    if(MMPR_OK != i4_ret)
    {
        /**/
        _mmp_pe_set_img_bad_or_corrupt(pt_this, &pt_this->at_img[ui4_next_img], _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_CORRUPT);

        /**/
        if(_MMP_PE_IMG_FLAG_IMG_LOADING_SUSPEND & pt_next_file->ui2_flag)
        {
            pt_next_file->ui2_flag &= ~(_MMP_PE_IMG_FLAG_IMG_LOADING_SUSPEND);

            i4_next_ret = _mmp_pe_load_image(pt_this, 0);
            if(MMPR_OK != i4_next_ret)
            {
                _mmp_pe_set_img_bad_or_corrupt(pt_this, &pt_this->at_img[ui4_next_img], _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_CORRUPT);
            }
        }

        return i4_ret;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_save_rotation
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_save_rotation(
    _MMP_PE_IMG_FILE_T*         pt_file)
{
    EXIF_INFO_T                 t_rotate_info;
    //INT32                       i4_ret;
    IMG_ROTATE_OP_TYPE_T        e_save_rotate;

    if(MMP_PE_RC_IS_SAVE_ROTATE())
    {
        if(_MMP_PE_IMG_FLAG_BAD_FILE & pt_file->ui2_flag)
        {
            return MMPR_FAIL;
        }


        /**/
        e_save_rotate = pt_file->e_rotate;
        t_rotate_info.e_exif_id = EXIF_ORIENTATION;
        t_rotate_info.z_size = sizeof(IMG_ROTATE_OP_TYPE_T);
        t_rotate_info.pv_data = &e_save_rotate;
        t_rotate_info.e_property = EXIF_AVAILABLE;

        //i4_ret = c_img_set_exif_info(pt_file->h_img, INTRA_IMG_PRIMARY_IMG_TYPE, &t_rotate_info, 1);
       // if(IMGR_OK != i4_ret && IMGR_NO_EXIF_DATA != i4_ret)
        //{
        //    MMP_DBG_ERROR(("c_img_set_info() failed, i4_ret = %d.\r\n", i4_ret));
        //    return MMPR_FAIL;
        //}

        //if((IMGR_NO_EXIF_DATA == i4_ret) || (EXIF_AVAILABLE != t_rotate_info.e_property))
        if (EXIF_AVAILABLE != t_rotate_info.e_property)
        {
            MMP_DBG_INFO(("No Rotation field to save.\r\n"));
            return MMPR_NO_DATA;
        }

        //save rotation in thumbnail at same time
        //i4_ret = c_img_set_exif_info(pt_file->h_img, INTRA_IMG_THUMBNAIL_TYPE, &t_rotate_info, 1);
        //if(IMGR_OK != i4_ret && IMGR_NO_EXIF_DATA != i4_ret)
        //{
        //    MMP_DBG_ERROR(("c_img_set_info() failed, i4_ret = %d.\r\n", i4_ret));
        //}

        //if((IMGR_NO_EXIF_DATA == i4_ret) || (EXIF_AVAILABLE != t_rotate_info.e_property))
        if (EXIF_AVAILABLE != t_rotate_info.e_property)
        {
            MMP_DBG_INFO(("No Rotation field to save.\r\n"));
        }
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_get_surf
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_get_surf(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    MMP_PE_FILE_IDX_T           e_idx,
    HANDLE_T*                   ph_surf)
{
    _MMP_PE_IMG_FILE_T*         pt_file;
    UINT32                      ui4_img;
    INT32                       i;
    MMP_DRC_BUF_T*              pt_buf = NULL;

    /*check param*/
    if(MMP_PE_FILE_IDX_TOTAL == e_idx || NULL == ph_surf)
    {
        MMP_DBG_ERROR(("e_idx cannot be MMP_PE_FILE_IDX_TOTAL and ph_surf cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }

    /*get target file*/
    if(MMP_PE_FILE_IDX_CURRENT == e_idx)
    {
        if(_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
        {
            MMP_DBG_ERROR(("No file is active.\r\n"));
            return MMPR_NO_DATA;
        }

        ui4_img = pt_this->ui1_crnt_img;
    }
    else /*MMP_PE_FILE_IDX_NEXT*/
    {
        ui4_img = (UINT32)((_MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img || 1 == pt_this->ui1_crnt_img) ? 0 : 1);
    }

    if(ui4_img >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        return MMPR_FAIL;
    }

    pt_file = &pt_this->at_img[ui4_img];

    /*get working buf*/
    if(_MMP_PE_WORKING_BUF_ID_NULL == pt_file->t_working_buf.e_match_id)
    {
        for(i = _MMP_PE_WORKING_BUF_ID_TOTAL; i > 0; i--)
        {
            if(NULL != pt_file->t_working_buf.at_buf[i - 1])
            {
                pt_buf = pt_file->t_working_buf.at_buf[i - 1];
                break;
            }
        }
    }
    else
    {
        if(pt_file->t_working_buf.e_match_id >= _MMP_PE_WORKING_BUF_ID_TOTAL)
        {
            return MMPR_FAIL;
        }

        pt_buf = pt_file->t_working_buf.at_buf[pt_file->t_working_buf.e_match_id];
    }

    /*check valid*/
    if(NULL == pt_buf)
    {
        MMP_DBG_ERROR(("Source display buffer shouldn't be NULL.\r\n"));
        MMP_ASSERT(0);
        return MMPR_INTERNAL_ERROR;
    }

    *ph_surf = pt_buf->h_surf;
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_update_display
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_update_display(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file,
    BOOL                        b_flip)
{

    //INT32                       i4_ret, i, j;
    //MMP_DRC_BUF_T               *pt_buf_old = NULL, *pt_buf_slot = NULL;
    //BOOL                        b_swap;
    //UINT8                       ui1_own_buf_slot_idx = 0;
    //_MMP_PE_IMG_FILE_T*         pt_another_file;
    //INT16                       i2_idx = 0;

    if(b_flip)
    {
        //Set cropping rectangle to graphic
        if (pt_file->e_img_type == IMG_MPO &&
            pt_file->e_rotate == IMG_ROTATE_CLOCKWS_0_OP_TYPE &&
            pt_file->ui4_zoom == MMP_PE_ZOOM_CONST &&
            (!(pt_this->ui4_flag & _MMP_PE_FLAG_IS_PLAYING_ZOOM_ROTATE)) &&
            !(_MMP_PE_FLAG_PREVIEW_MODE & pt_this->ui4_flag))
        {

        }
        else
        {

        }

        /*change image*/
        if(1)
        {

            c_thread_delay(34);

        }
    }
    return MMPR_OK;

}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_detach_display
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_detach_display(
    _MMP_PE_DATA_MEMBER_T*      pt_this)
{
    //INT32                       i4_ret;
    _MMP_PE_IMG_FILE_T*         pt_another_file;
    UINT8                       ui1_idx;
    if(NULL == pt_this->pt_buf_crnt_disp)
    {
        return MMPR_OK;
    }

    /*show image*/
    //
    ////
    ///
    ///
    ////


    if(FALSE == _mmp_pe_is_disp_res_used_by_crnt_img(pt_this, pt_this->pt_buf_crnt_disp))
    {
        if(NULL != pt_this->pt_buf_crnt_disp)
        {
            //mmp_drc_unlock_buf(pt_this->pt_buf_crnt_disp);

            pt_another_file = (1 == pt_this->ui1_crnt_img) ? &pt_this->at_img[0] : &pt_this->at_img[1];

            if (TRUE == _mmp_pe_is_buf_used_by_img(pt_this, pt_another_file, pt_this->pt_buf_crnt_disp, &ui1_idx))
            {
                if(ui1_idx >= _MMP_PE_WORKING_BUF_ID_TOTAL)
                {
                    return MMPR_FAIL;
                }

                pt_another_file->t_working_buf.at_buf[ui1_idx] = NULL;
            }
            /*pt_this->at_disp_pool[pt_this->ui1_crnt_disp].ui1_flag &= ~(_MMP_PE_DR_FLAG_USED);*/
        }
    }

    pt_this->pt_buf_crnt_disp = NULL;
    pt_this->pt_buf_crnt_disp_bkp = NULL;
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_get_angle_group
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static _MMP_PE_ROTATE_GROUP_T _mmp_pe_get_angle_group(
    IMG_ROTATE_OP_TYPE_T                e_rotate)
{
    switch(e_rotate)
    {
    case IMG_ROTATE_CLOCKWS_0_OP_TYPE:
    case IMG_ROTATE_CLOCKWS_180_OP_TYPE:
        return _MMP_PE_ROTATE_GROUP_0;

    case IMG_ROTATE_CLOCKWS_90_OP_TYPE:
    case IMG_ROTATE_CLOCKWS_270_OP_TYPE:
        return _MMP_PE_ROTATE_GROUP_1;

    case IMG_ROTATE_CLOCKWS_0_OP_TYPE_WITH_FLIP:
    case IMG_ROTATE_CLOCKWS_180_OP_TYPE_WITH_FLIP:
        return _MMP_PE_ROTATE_GROUP_2;

    case IMG_ROTATE_CLOCKWS_90_OP_TYPE_WITH_FLIP:
    case IMG_ROTATE_CLOCKWS_270_OP_TYPE_WITH_FLIP:
        return _MMP_PE_ROTATE_GROUP_3;


    default:
        MMP_ASSERT(0);
        return _MMP_PE_ROTATE_GROUP_0;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_get_angle_diff
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pe_get_angle_diff(
    IMG_ROTATE_OP_TYPE_T        e_crnt_rotate,
    IMG_ROTATE_OP_TYPE_T        e_new_rotate,
    UINT32*                     pui4_angle,
    UINT32*                     pui4_flip)
{
    IMG_ROTATE_OP_TYPE_T        ae_rotate[2] = {e_crnt_rotate, e_new_rotate};
    INT32                       ai4_angle[2], i, i4_angle_diff;
    BOOL                        ab_flip[2], b_flip_diff;

    for(i = 0; i < 2; i++)
    {
        switch(ae_rotate[i])
        {
        case IMG_ROTATE_CLOCKWS_0_OP_TYPE:
            ai4_angle[i] = 0;
            ab_flip[i] = FALSE;
            break;

        case IMG_ROTATE_CLOCKWS_90_OP_TYPE:
            ai4_angle[i] = 90;
            ab_flip[i] = FALSE;
            break;

        case IMG_ROTATE_CLOCKWS_180_OP_TYPE:
            ai4_angle[i] = 180;
            ab_flip[i] = FALSE;
            break;

        case IMG_ROTATE_CLOCKWS_270_OP_TYPE:
            ai4_angle[i] = 270;
            ab_flip[i] = FALSE;
            break;

        case IMG_ROTATE_CLOCKWS_0_OP_TYPE_WITH_FLIP:
            ai4_angle[i] = 0;
            ab_flip[i] = TRUE;
            break;

        case IMG_ROTATE_CLOCKWS_90_OP_TYPE_WITH_FLIP:
            ai4_angle[i] = 90;
            ab_flip[i] = TRUE;
            break;

        case IMG_ROTATE_CLOCKWS_180_OP_TYPE_WITH_FLIP:
            ai4_angle[i] = 180;
            ab_flip[i] = TRUE;
            break;

        case IMG_ROTATE_CLOCKWS_270_OP_TYPE_WITH_FLIP:
            ai4_angle[i] = 270;
            ab_flip[i] = TRUE;
            break;

        default:
            MMP_ASSERT(0);
            ai4_angle[i] = 0;
            ab_flip[i] = FALSE;
            break;
        }
    }

    b_flip_diff = (ab_flip[0] != ab_flip[1]) ? TRUE : FALSE;
    i4_angle_diff = ai4_angle[1] - ai4_angle[0];
    i4_angle_diff = (i4_angle_diff + 360) % 360;

    switch(i4_angle_diff)
    {
    case 0:
        *pui4_angle = GL_BLT_ROTATE_NONE;
        break;

    case 90:
        *pui4_angle = GL_BLT_ROTATE_CW90;
        break;

    case 180:
        *pui4_angle = GL_BLT_ROTATE_CW180;
        break;

    case 270:
        *pui4_angle = GL_BLT_ROTATE_CW270;
        break;

    default:
        MMP_ASSERT(0);
        *pui4_angle = GL_BLT_ROTATE_NONE;
        break;
    }

    *pui4_flip = (b_flip_diff) ? GL_BLT_FLIP : 0;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_get_file_path
 *
 * Description:
 *
 * Inputs:  pz_size cannot be NULL.
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_get_file_path(
    _MMP_PE_IMG_FILE_T*         pt_file,
    SIZE_T*                     pz_size,
    UINT8*                      pui1_buf)
{
    CHAR                        *ps_path;
    INT32                       i4_ret;
    SIZE_T                      z_need;

    /*check id*/
    if(MMP_FID_NULL_REC_IDX == pt_file->t_path)
    {
        return MMPR_NO_DATA;
    }

    /*get path*/
    i4_ret = mmp_fid_get(pt_file->t_path, &ps_path);
    if(MMPR_OK != i4_ret)
    {
        MMP_ASSERT(0);
        return MMPR_NO_DATA;
    }

    z_need = c_strlen(ps_path) + 1; /*+1 for null-char*/
    if(1 >= z_need)
    {
        return MMPR_NO_DATA;
    }

    if(0 == *pz_size || NULL == pui1_buf)
    {
        *pz_size = z_need;
        return MMPR_BUF_NOT_ENOUGH;
    }

    /*copy str*/
    *pz_size = (z_need > *pz_size) ? *pz_size : z_need;
    c_strncpy((CHAR*)pui1_buf, ps_path, *pz_size - 1);
    pui1_buf[*pz_size - 1] = (UINT8)'\0';

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_get_file_have_thumb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_get_file_have_thumb(
    _MMP_PE_IMG_FILE_T*         pt_file,
    BOOL*                       pb_hav_thum)
{
    INT32   i4_ret = -1;
    SIZE_T  z_width = 0, z_height = 0;
    UINT32  ui4_type_size;
    BOOL    b_meet_all;

    if(IMG_JPG != pt_file->e_img_type && IMG_MPO != pt_file->e_img_type)
    {
        *pb_hav_thum = FALSE;
    }
    else
    {
        /*get thumb dimension*/
        i4_ret = c_img_get_dimension(pt_file->h_img, INTRA_IMG_THUMBNAIL_TYPE, &z_width, &z_height);
        if(IMGR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_img_get_dimension(INTRA_IMG_THUMBNAIL_TYPE) failed. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }

        if(0 == z_width || 0 == z_height)
        {
            *pb_hav_thum = FALSE;
        }
        else
        {
            /*check type*/
            ui4_type_size = sizeof(BOOL);

            i4_ret = c_img_get_info(pt_file->h_img,
                                IMG_INFO_THUMBNAIL_MEET_ALL_LIMITATION,
                                NULL,
                                (VOID*)&b_meet_all,
                                &ui4_type_size);
            if(IMGR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_img_get_info(IMG_INFO_THUMBNAIL_MEET_ALL_LIMITATION) failed. i4_ret = %d.\r\n", i4_ret));
                return MMPR_FAIL;
            }

            *pb_hav_thum = b_meet_all;
        }
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_get_info_title
 *
 * Description:
 *
 * Inputs:  pz_size cannot be NULL.
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_get_info_title(
    FID_T                       t_fid,
    SIZE_T*                     pz_size,
    UINT8*                      pui1_buf)
{
    CHAR                        *ps_path, *ps_name;
    INT32                       i4_ret;
    SIZE_T                      z_need;

    /*check id*/
    if(MMP_FID_NULL_REC_IDX == t_fid)
    {
        return MMPR_NO_DATA;
    }

    /*get path*/
    i4_ret = mmp_fid_get(t_fid, &ps_path);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_fid_get(%d) failed. i4_ret = %d.\r\n", t_fid, i4_ret));
        MMP_ASSERT(0);
        return MMPR_NO_DATA;
    }

    /*find parent*/
    ps_name = c_strrchr(ps_path, MMP_RC_FOLDER_TOKEN);
    if(NULL == ps_name)
    {
        MMP_DBG_ERROR(("Cannot find parent of %s.\r\n", ps_path));
        return MMPR_NO_DATA;
    }

    /*remove prefix*/
    ps_name = mmp_util_trim_path_prefix(ps_path, ps_name + 1);

    z_need = c_strlen(ps_name) + 1; /*+1 for null-char*/
    if(1 >= z_need)
    {
        return MMPR_NO_DATA;
    }

    if(0 == *pz_size || NULL == pui1_buf)
    {
        *pz_size = z_need;
        return MMPR_BUF_NOT_ENOUGH;
    }

    /*copy str*/
    *pz_size = (z_need > *pz_size) ? *pz_size : z_need;
    c_strncpy((CHAR*)pui1_buf, ps_name, *pz_size - 1);
    pui1_buf[*pz_size - 1] = (UINT8)'\0';

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_get_info_file_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_get_info_file_info(
   FID_T                        t_fid,
   _MMP_PE_INFO_FILE_INFO_T*    pt_file_info,
   MMP_FP_INFO_TYPE_T           e_type,
   SIZE_T*                      pz_size,
   UINT8*                       pui1_buf)
{
    FM_FILE_INFO_T              t_info;
    TIME_T*                     pt_time = NULL;
    CHAR*                       ps_path;
    INT32                       i4_ret;
    _MMP_PE_INFO_FILE_INFO_FIELD ui2_field = 0;

    /*check id*/
    if(MMP_FID_NULL_REC_IDX == t_fid)
    {
        return MMPR_NO_DATA;
    }

    switch(e_type)
    {
    case MMP_FP_INFO_TYPE_CREATE_TIME:
    case MMP_FP_INFO_TYPE_LAST_WRITE_TIME:
        {
            if(sizeof(DTG_T) != *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(DTG_T);
                return MMPR_BUF_NOT_ENOUGH;
            }

            if(MMP_FP_INFO_TYPE_CREATE_TIME == e_type)
            {
                ui2_field |= _MMP_PE_INFO_FILE_INFO_FIELD_CREATE;
                pt_time = &pt_file_info->ui8_create_time;
            }
            else /*MMP_FP_INFO_TYPE_LAST_WRITE_TIME*/
            {
                ui2_field |= _MMP_PE_INFO_FILE_INFO_FIELD_MODIFY;
                pt_time = &pt_file_info->ui8_modify_time;
            }
        }
        break;

    case MMP_FP_INFO_TYPE_PROTECT:
        {
            if(sizeof(BOOL) != *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(BOOL);
                return MMPR_BUF_NOT_ENOUGH;
            }

            ui2_field |= _MMP_PE_INFO_FILE_INFO_FIELD_PROTECT;
        }
        break;

    case MMP_FP_INFO_TYPE_SIZE:
        {
            if(sizeof(UINT64) != *pz_size || NULL == pui1_buf)
            {
                *pz_size = sizeof(UINT64);
                return MMPR_BUF_NOT_ENOUGH;
            }

            ui2_field |= _MMP_PE_INFO_FILE_INFO_FIELD_SIZE;
        }
        break;

    default:
        MMP_ASSERT(0);
        break;
        //return MMPR_INTERNAL_ERROR;
    }

    if((ui2_field & pt_file_info->ui2_field) != ui2_field) /*data not ready*/
    {
        /*get path*/
        i4_ret = mmp_fid_get(t_fid, &ps_path);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_fid_get(%d) failed. i4_ret = %d.\r\n", t_fid, i4_ret));
            MMP_ASSERT(0);
            return MMPR_NO_DATA;
        }

        /*get file info*/
        i4_ret = c_fm_get_info_by_name(NULL_HANDLE, ps_path, &t_info);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_fm_get_info_by_name(%s) failed. i4_ret = %d.\r\n", ps_path, i4_ret));
            return MMPR_FAIL;
        }

        pt_file_info->ui8_create_time = t_info.ui8_create_time;
        pt_file_info->ui8_modify_time = t_info.ui8_modify_time;
        pt_file_info->b_protect = (FM_MODE_USR_WRITE & t_info.ui4_mode) ? FALSE : TRUE;
        pt_file_info->ui8_size  = t_info.ui8_size;

        pt_file_info->ui2_field |= (_MMP_PE_INFO_FILE_INFO_FIELD_CREATE | _MMP_PE_INFO_FILE_INFO_FIELD_MODIFY | _MMP_PE_INFO_FILE_INFO_FIELD_PROTECT | _MMP_PE_INFO_FILE_INFO_FIELD_SIZE);
    }

    switch(e_type)
    {
    case MMP_FP_INFO_TYPE_CREATE_TIME:
    case MMP_FP_INFO_TYPE_LAST_WRITE_TIME:
        {
            MMP_ASSERT(pt_time);

            /**/
            i4_ret = c_dt_utc_sec_to_loc_dtg(*pt_time, (DTG_T*)pui1_buf);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_dt_utc_sec_to_loc_dtg(%d) failed. i4_ret = %d.\r\n", *pt_time, i4_ret));
                return MMPR_FAIL;
            }
        }
        break;

    case MMP_FP_INFO_TYPE_PROTECT:
        {
            *((BOOL*)pui1_buf) = pt_file_info->b_protect;
        }
        break;

    case MMP_FP_INFO_TYPE_SIZE:
        {
            *((UINT64*)pui1_buf) = pt_file_info->ui8_size;
        }
        break;
        default:
        return MMPR_INTERNAL_ERROR;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_get_parent
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_get_parent(
    FID_T                       t_fid,
    SIZE_T*                     pz_size,
    UINT8*                      pui1_buf)
{
    CHAR                        *ps_path, *ps_token_one, *ps_token_two, *ps_crnt;
    CHAR                        *ps_buf1,  as_buf[MMP_RC_PATH_MAX_LEN+1];
    INT32                       i4_ret;
    SIZE_T                      z_need_len;

    /*get path*/
    i4_ret = mmp_fid_get(t_fid, &ps_path);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_fid_get(%d) failed. i4_ret = %d.\r\n", t_fid, i4_ret));
        MMP_ASSERT(0);
        return MMPR_NO_DATA;
    }

    /**/
    ps_token_one = ps_token_two = NULL;
    ps_crnt = ps_path;
    while(ps_crnt && '\0' != *ps_crnt)
    {
        if(MMP_RC_FOLDER_TOKEN == *ps_crnt)
        {
            ps_token_one = ps_token_two;
            ps_token_two = ps_crnt;
        }

        ps_crnt++;
    }

    if(NULL == ps_token_one || NULL == ps_token_two)
    {
        MMP_DBG_ERROR(("Token not found, string = %s.\r\n", ps_path));
        return MMPR_NO_DATA;
    }

    /**/
    z_need_len = (SIZE_T)(ps_token_two - ps_token_one + 1); /*include null character, include the '/'*/
    if(0 == z_need_len)
    {
        MMP_DBG_ERROR(("Copy length is 0, string = %s.\r\n", ps_path));
        return MMPR_NO_DATA;
    }

    /*check buffer*/
    if(0 == *pz_size || NULL == pui1_buf)
    {
        *pz_size = z_need_len;
        return MMPR_BUF_NOT_ENOUGH;
    }

    /**/
    if(*pz_size < z_need_len)
    {
        z_need_len = *pz_size;
    }

    /*copy result*/
    c_strncpy(as_buf, ps_token_one , z_need_len - 1);
    as_buf[z_need_len - 1] = '\0';

    ps_buf1 = as_buf;
    ps_buf1 = mmp_util_trim_path_prefix(ps_path, ps_buf1 + 1);


    z_need_len = c_strlen(ps_buf1) + 1;

    c_strncpy((CHAR*)pui1_buf, ps_buf1 , z_need_len - 1);
    pui1_buf[z_need_len - 1] = (UINT8)'\0';

    *pz_size = z_need_len;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_reset_play_timer
 *

 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pe_reset_play_timer(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    UINT32                      ui4_img_idx,
    MMP_TIMER_OP_TYPE_T         e_op)
{
    INT32                       i4_ret = 0;


    // Fix coverity CID-4632702: Out-of-bounds access ...
    MMP_DBG_INFO(("[mmp] %s %d ui4_img_idx = %d. \r\n",__FUNCTION__, __LINE__, ui4_img_idx ));

    if( pt_this == NULL )
    {
        return;
    }
    if(ui4_img_idx >= _MMP_PE_IMAGE_FILE_MAX_COUNT)
    {
        return;
    }

    MMP_DBG_INFO(("[mmp] ui4_duration = %d \r\n",  pt_this->at_img[ui4_img_idx].ui4_duration));


    i4_ret = c_timer_stop(pt_this->h_play_timer);
    if(OSR_OK != i4_ret)
    {
        ABORT_APPL(DBG_MOD_PHOTO, ("stop Error-Timer failed!"));
    }

    if(MMP_TIMER_OP_TYPE_STOP == e_op)
    {
        return;
    }

    if(0 != pt_this->at_img[ui4_img_idx].ui4_duration)
    {
        i4_ret = c_timer_start(pt_this->h_play_timer,
                               pt_this->at_img[ui4_img_idx].ui4_duration,
                               X_TIMER_FLAG_ONCE,
                               _mmp_pe_play_timer_cb,
                               (VOID*)pt_this->ui4_play_ver);
        if(OSR_OK != i4_ret)
        {
            ABORT_APPL(DBG_MOD_PHOTO, ("start Error-Timer failed!"));
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_pe_play_timer_cb
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _mmp_pe_play_timer_cb(
    HANDLE_T                    h_timer,
    VOID*                       pv_ui4_play_ver)
{
    /*post a message to itself*/
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_IMPORTANT,
                                _mmp_pe_play_timer_event_handler,
                                pv_ui4_play_ver,
                                NULL,
                                NULL,
                                NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_pe_play_timer_event_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _mmp_pe_play_timer_event_handler(
    VOID*                       pv_ui4_play_ver,
    VOID*                       pv_unused1,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    UINT32                      ui4_play_ver;

    ui4_play_ver = (UINT32)pv_ui4_play_ver;

    MMP_DBG_INFO(("[Photo/ResetTimer] _mmp_pe_play_timer_event_handler. ui4_play_ver = %d. pt_this->ui4_play_ver = %d.\r\n", ui4_play_ver, pt_this->ui4_play_ver));

    if(ui4_play_ver != pt_this->ui4_play_ver)
    {
        /*timer is out of date*/
        return;
    }

    if(NULL == pt_this->pf_play_nfy || _MMP_PE_IMG_IDX_NULL == pt_this->ui1_crnt_img)
    {
        MMP_ASSERT(0);
        return;
    }

    /*pt_this->e_state = MMP_PLAY_STATE_STOPPED;*/

    /*notify client*/
    pt_this->pf_play_nfy(pt_this->pv_play_nfy_tag, pt_this->ui4_play_ver, MMP_PE_PLAY_NFY_ID_PLAY_END, (VOID*)TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_get_unused_info_inst
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_get_unused_info_inst(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_INFO_INST_T**       ppt_info_inst)
{
    UINT32                      i;

    for(i = 0; i < MMP_PE_RC_INFO_INST_MAX_COUNT; i++)
    {
        if(0 == pt_this->at_info_inst[i].ui4_ver)
        {
            *ppt_info_inst = &pt_this->at_info_inst[i];
            return MMPR_OK;
        }
    }

    return MMPR_OUT_OF_LIMIT;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_info_ready_event_handler
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pe_info_ready_event_handler(
    VOID*                       pv_pt_info_obj,
    VOID*                       pv_ui4_ver,
    VOID*                       pv_nfy_tag,
    VOID*                       pv_unused3)
{
    _MMP_PE_INFO_INST_T*        pt_this_obj;

    if(NULL == pv_pt_info_obj)
    {
        MMP_ASSERT(0);
        return;
    }
    pt_this_obj = (_MMP_PE_INFO_INST_T*)pv_pt_info_obj;

    /**/
    if(pt_this_obj->ui4_ver != (UINT32)(pv_ui4_ver))
    {
        /*notification is out of date*/
        return;
    }
    MMP_ASSERT(pt_this_obj->pf_info_nfy);

    DBG_INFO_DIRECT("[mmp pe] %s %d <MMP_FP_INFO_NFY_ID_INFO_READY> \r\n",__FUNCTION__,__LINE__);

    /*notify client*/
    pt_this_obj->pf_info_nfy(pt_this_obj->pv_info_nfy_tag, pt_this_obj, MMP_FP_INFO_NFY_ID_INFO_READY, (VOID*)pv_nfy_tag);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_info_load_thumbnail
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_info_load_thumbnail(
    _MMP_PE_DATA_MEMBER_T*                  pt_this,
    _MMP_PE_INFO_INST_T*                    pt_this_obj,
    MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T*     pt_param)
{
    GL_RECT_T                               t_boundary_rect;
    GL_RECT_T                               t_show_rect;
    IMG_INTRA_TYPE_T                        e_thumb_type;
    INT32                                   i4_ret;
    UINT32                                  ui4_load_ver;

    if(NULL == pt_param->pt_rect || WGL_RECT_IS_EMPTY(pt_param->pt_rect))
    {
        return MMPR_INV_ARG;
    }

    DBG_INFO_DIRECT("[mmp pe] %s %d  \r\n",__FUNCTION__,__LINE__);


    /**/
    if(0 == (_MMP_PE_FLAG_THUMB_DISP_RESUMED & pt_this->ui4_flag))
    {
        return MMPR_RES_NOT_READY;
    }

    /*stop current loading*/
    if(_MMP_PE_INFO_FLAG_LOADING & pt_this_obj->ui1_flag)
    {
        pt_this_obj->ui1_flag &= ~(_MMP_PE_INFO_FLAG_LOADING);
        //return MMPR_OK;
    }

    t_boundary_rect = *pt_param->pt_rect;
    mmp_drc_convert_rect_coord(pt_param->e_coords, &t_boundary_rect);
    DBG_INFO_DIRECT("[mmp pe] %s %d UI:  x=%d, y=%d, w=%d, h=%d    IMG: x=%d, y=%d, w=%d, h=%d.\r\n",
                  __FUNCTION__,
                  __LINE__,
                  pt_param->pt_rect->i4_left,
                  pt_param->pt_rect->i4_top,
                  WGL_RECT_GET_WIDTH(pt_param->pt_rect),
                  WGL_RECT_GET_HEIGHT(pt_param->pt_rect),
                  t_boundary_rect.i4_left,
                  t_boundary_rect.i4_top,
                  WGL_RECT_GET_WIDTH(&t_boundary_rect),
                  WGL_RECT_GET_HEIGHT(&t_boundary_rect));

    pt_this_obj->e_rotate_op = pt_param->e_rotate_op;
    i4_ret = _mmp_pe_load_thumbnail(pt_this,
                                    pt_this_obj,
                                    pt_this_obj->e_img_type,
                                    NULL,
                                    NULL,
                                    &t_boundary_rect,
                                    (_MMP_PE_FLAG_NO_MAIN_THUMB & pt_this->ui4_flag) ? TRUE : FALSE,
                                    FALSE,
                                    FALSE,
                                    FALSE,
                                    pt_param->e_rotate_op,
                                    &e_thumb_type,
                                    &t_show_rect,
                                    &ui4_load_ver);


    if(MMPR_OK != i4_ret)
    {
        _MMP_PE_SET_LOAD_VER_INVALID(pt_this_obj->ui4_crnt_load_ver);
        return i4_ret;
    }


    /*update status*/
    pt_this_obj->t_boundary_rect    = t_boundary_rect;
    pt_this_obj->t_thumb_rect       = t_show_rect;
    pt_this_obj->ui4_crnt_load_ver  = ui4_load_ver;
    if(INTRA_IMG_PRIMARY_IMG_TYPE == e_thumb_type)
    {
        pt_this_obj->ui1_flag |= _MMP_PE_INFO_FLAG_FROM_MAIN;
    }
    pt_this_obj->ui1_flag |= _MMP_PE_INFO_FLAG_LOADING;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_thumb_load_event_handler
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pe_thumb_load_next_file(
    VOID*                       pv_pt_info_obj,
    VOID*                       pv_h_img,
    VOID*                       pv_i4_ret,
    VOID*                       pv_ver)
{
    _MMP_PE_INFO_INST_T*        pt_this_obj = (_MMP_PE_INFO_INST_T*)pv_pt_info_obj;
    BOOL                        b_is_success = pv_i4_ret;

    DBG_INFO_DIRECT("[mmp pe] %s %d\n",__FUNCTION__,__LINE__);

    /*stop loading next thumbnail*/
    if(!(_MMP_PE_INFO_FLAG_LOADING & pt_this_obj->ui1_flag))
    {
        return MMPR_OK;
    }

    b_is_success = (IMGR_OK == ((INT32)pv_i4_ret)) ? TRUE : FALSE;

    /*notify client*/
    pt_this_obj->pf_info_nfy(pt_this_obj->pv_info_nfy_tag, pt_this_obj, MMP_FP_INFO_NFY_ID_THUMBNAIL, (VOID*)(UINT32)TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_do_xtrn_req
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_do_xtrn_req(
    _MMP_PE_REQ_WINDOW_T*       pt_req_window)
{
    INT32                       i4_ret;

    i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_CRITICAL,
                                         _mmp_pe_xtrn_req_handler,
                                         NULL,
                                         NULL,
                                         NULL,
                                         NULL);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /*wait result*/
    i4_ret = c_sema_lock(pt_req_window->h_ready_signal, X_SEMA_OPTION_WAIT);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_sema_lock() failed. i4_ret = %d.\r\n", i4_ret));
        return MMPR_INTERNAL_ERROR;
    }

    pt_req_window->e_id = _MMP_PE_REQ_ID_LAST_ENTRY;
    return pt_req_window->i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_xtrn_req_handler
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pe_xtrn_req_handler(
    VOID*                       pv_unused1,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3,
    VOID*                       pv_unused4)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this;
    _MMP_PE_REQ_WINDOW_T*       pt_req_window = &t_g_req_window;

    switch(pt_req_window->e_id)
    {
    case _MMP_PE_REQ_ID_OPEN:
        pt_req_window->i4_ret = mmp_pe_play_open((const CHAR*)pt_req_window->apv_param[0],
                                                 (mmp_pe_play_nfy_fct)pt_req_window->apv_param[1],
                                                 pt_req_window->apv_param[2],
                                                 (UINT32)pt_req_window->apv_param[3]);
        break;
    case _MMP_PE_REQ_ID_MEM_OPEN:
        {
            _MMP_PE_REQ_PARAM_MEM_OPEN_T*    pt_param = (_MMP_PE_REQ_PARAM_MEM_OPEN_T*)pt_req_window->apv_param[0];

            pt_req_window->i4_ret = mmp_pe_play_mopen(pt_param->pui1_buf, pt_param->z_buf_size, pt_param->pf_nfy, pt_param->pv_tag, pt_param->ui4_ver);
        }
        break;

    case _MMP_PE_REQ_ID_CLOSE:
        pt_req_window->i4_ret = mmp_pe_play_close();
        break;
    case _MMP_PE_REQ_ID_ATTR_SET:
        pt_req_window->i4_ret = mmp_pe_play_attr_set((UINT32)pt_req_window->apv_param[0],
                                                     (const MMP_FP_SHOW_ATTR_T*)pt_req_window->apv_param[1]);
        break;
    case _MMP_PE_REQ_ID_NEXT_PRELOAD:
        pt_req_window->i4_ret = mmp_pe_play_next_preload((const CHAR*)pt_req_window->apv_param[0]);
        break;
    case _MMP_PE_REQ_ID_NEXT_MEM_PRELOAD:
        pt_req_window->i4_ret = mmp_pe_play_next_mpreload((const UINT8*)pt_req_window->apv_param[0],
                                                          (SIZE_T)pt_req_window->apv_param[1]);
        break;
    case _MMP_PE_REQ_ID_NEXT_ATTR_SET:
        pt_req_window->i4_ret = mmp_pe_play_next_attr_set((UINT32)pt_req_window->apv_param[0],
                                                          (const MMP_FP_SHOW_ATTR_T*)pt_req_window->apv_param[1]);
        break;
    case _MMP_PE_REQ_ID_SHOW:
        {
            pt_this = &t_g_photo_eng;

            //pt_req_window->i4_ret = _mmp_pe_view_image(pt_this, FALSE);
            if(MMPR_IS_PLAYED == pt_req_window->i4_ret)
            {
                pt_req_window->i4_ret = MMPR_IS_STOPPED;
            }
        }
        break;
    case _MMP_PE_REQ_ID_ROTATE:
        pt_req_window->i4_ret = mmp_pe_play_rotate((IMG_ROTATE_OP_TYPE_T)(UINT32)pt_req_window->apv_param[0]);
        break;

    case _MMP_PE_REQ_ID_INFO_THUM:

        break;

    case _MMP_PE_REQ_ID_PLAY:
        {
            pt_this = &t_g_photo_eng;

            //pt_req_window->i4_ret = _mmp_pe_view_image(pt_this, TRUE);
            if(MMPR_IS_PLAYED == pt_req_window->i4_ret)
            {
                pt_req_window->i4_ret = MMPR_IS_PLAYED;
            }
        }
        break;

    case _MMP_PE_REQ_ID_STOP:
        pt_req_window->i4_ret = mmp_pe_play_stop();
        break;

    case _MMP_PE_REQ_ID_PAUSE:
        pt_req_window->i4_ret = mmp_pe_play_pause();
        break;

    case _MMP_PE_REQ_ID_CLEAN:
        pt_req_window->i4_ret = mmp_pe_play_clean();
        break;
    case _MMP_PE_REQ_ID_NEXT:
        pt_req_window->i4_ret = mmp_pe_play_next((UINT32)pt_req_window->apv_param[0]);
        break;
    case _MMP_PE_REQ_ID_GET_FILE:
        pt_req_window->i4_ret = mmp_pe_play_get_file((MMP_PE_FILE_IDX_T)(UINT32)pt_req_window->apv_param[0],
                                                     (CHAR**)pt_req_window->apv_param[1]);
        break;
    case _MMP_PE_REQ_ID_GET_SURF:
        {
            pt_this = &t_g_photo_eng;

            pt_req_window->i4_ret = _mmp_pe_get_surf(pt_this,
                                                     (MMP_PE_FILE_IDX_T)(UINT32)pt_req_window->apv_param[0],
                                                     (HANDLE_T*)pt_req_window->apv_param[1]);
        }
        break;
    case _MMP_PE_REQ_ID_LAST_ENTRY:
    default:
        MMP_ASSERT(0);
        return; /*ignore*/
    }

    /*raise the signal*/
    if(OSR_OK != c_sema_unlock(pt_req_window->h_ready_signal))
    {
        MMP_ASSERT(0);
        pt_req_window->i4_ret = MMPR_INTERNAL_ERROR;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_is_valid_datetime
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static BOOL _mmp_pe_is_valid_datetime(
    CHAR*                       ps_exif_time)
{
    CHAR*                       ps_pattern = _MMP_PE_EXIF_DATE_FMT;
    INT32                       i4_update_field = 0;
    CHAR                        c_data = '\0';
    BOOL                        b_legal = FALSE, b_continue = TRUE, b_update = FALSE;

    /**/
    do
    {
        switch(*ps_pattern)
        {
        case ':':
        case ' ':
            {
                if(*ps_pattern != *ps_exif_time)
                {
                    b_continue = FALSE;
                }
                else
                {
                    b_update = TRUE;
                }
            }
            break;

        case '\0':
            {
                b_legal = ('\0' == *ps_exif_time) ? TRUE : FALSE;
                b_continue = FALSE;
                b_update = TRUE;
            }
            break;

        case 'Y':
        case 'M':
        case 'D':
        case 'h':
        case 'm':
        case 's':
            {
                c_data = *ps_pattern;
                if(*ps_exif_time > '9' || *ps_exif_time < '0')
                {
                    b_continue = FALSE;
                }

            }
            break;
        default:
            MMP_ASSERT(0);
            return FALSE;
        }

        if(b_update)
        {
            /**/
            switch(c_data)
            {
            case 'Y':
            case 'M':
            case 'D':
            case 'h':
            case 'm':
            case 's':
                i4_update_field++;
                break;
            default:
                MMP_ASSERT(0);
                return FALSE;
            }
            b_update = FALSE;
            b_legal = (b_legal && 6 == i4_update_field) ? TRUE : FALSE; /*all field is upated*/
        }

        ps_pattern++;
        ps_exif_time++;

    } while(b_continue);

    if(b_legal)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_init_limit_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_init_limit_info(
    _MMP_PE_DATA_MEMBER_T*      pt_this)                 /*IN*/
{
    //IMG_CAPS_T                  t_caps;
    //GL_GPU_CAPS_T               t_gpu_caps;
    //INT32                       i4_ret;
#if 0
    /*get progressive jpg support*/
    t_caps.ui4_type = IMG_HW_JPG_CAP_PROGRESSIVE;
    i4_ret = c_img_get_capability(&t_caps);
    if(IMGR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_img_get_capability(IMG_HW_JPG_CAP_PROGRESSIVE) failed, i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
    pt_this->t_limit.b_is_progressive_support = t_caps.u.b_progressive_support;

    /*get GPU limitation*/
    t_gpu_caps.ui4_type = GL_GPU_SCALING_LIMIT;
    i4_ret = c_gl_get_gpu_capability(&t_gpu_caps);
    if(GLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_gl_get_gpu_capability(GL_GPU_SCALING_LIMIT) failed, i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
    pt_this->t_limit.ui4_scale_max_width = t_gpu_caps.u.t_scaling_limit.ui4_max_width;
    pt_this->t_limit.ui4_scale_min_width = t_gpu_caps.u.t_scaling_limit.ui4_min_width;
    pt_this->t_limit.ui4_scale_max_height = t_gpu_caps.u.t_scaling_limit.ui4_max_height;
    pt_this->t_limit.ui4_scale_min_height = t_gpu_caps.u.t_scaling_limit.ui4_min_height;
#endif

    pt_this->t_limit.ui4_scale_max_width  = 0;
    pt_this->t_limit.ui4_scale_min_width  = 0;
    pt_this->t_limit.ui4_scale_max_height = 0;
    pt_this->t_limit.ui4_scale_min_height = 0;


    _MMP_PE_SET_LIMIT_INFO_READY(pt_this);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_copy_attr
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_copy_attr(
    _MMP_PE_IMG_FILE_T*         pt_file,            /*in*/
    UINT32*                     pui4_attr_count,    /*in/out*/
    MMP_FP_SHOW_ATTR_T*         at_show_attr)       /*out*/
{
    UINT32                      i;

    for(i = 0; i < *pui4_attr_count; i++)
    {
        switch(at_show_attr[i].e_id)
        {
        case MMP_FP_SHOW_ATTR_ID_DURATION:          /*pv_param: a UINT32 value in ms. ex: 5000 for 5 sec*/
            {
                at_show_attr[i].pv_param = (VOID*)pt_file->ui4_duration;
            }
            break;

        case MMP_FP_SHOW_ATTR_ID_EFFECT:            /*pv_param: a pointer to MMP_EFFECT_T struct*/
            {
                *((MMP_EFFECT_T*)at_show_attr[i].pv_param) = pt_file->t_effect;
            }
            break;

        case MMP_FP_SHOW_ATTR_ID_SPEED:             /*pv_param: a INT32 value. 0: Normal speed, -1: 1/2, 1: 2*/
        default:
            *pui4_attr_count = i;
            return MMPR_NOT_SUPPORT;
        }
    }

    *pui4_attr_count = i;
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_lock_thumbnail_buf
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pe_lock_thumbnail_buf(BOOL b_lock)
{

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_is_buf_used_by_img
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static BOOL _mmp_pe_is_buf_used_by_img(
    _MMP_PE_DATA_MEMBER_T*      pt_this,
    _MMP_PE_IMG_FILE_T*         pt_file,
    MMP_DRC_BUF_T*              pt_buf,
    UINT8*                      pui1_idx)
{
    UINT8       i;

    if (pt_buf == NULL)
    {
        return FALSE;
    }

    for(i = 0; i < _MMP_PE_WORKING_BUF_ID_TOTAL; i++)
    {
        if(pt_buf == pt_file->t_working_buf.at_buf[i])
        {
            *pui1_idx = i;
            return TRUE;
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pe_set_img_bad_or_corrupt
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pe_set_img_bad_or_corrupt(
    _MMP_PE_DATA_MEMBER_T*              pt_this,
    _MMP_PE_IMG_FILE_T*                 pt_file,
    _MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_T  e_type)
{
    CHAR*                       ps_path;
    INT32                       i4_ret;
    BOOL                        b_removed = FALSE, b_valid = TRUE;

    i4_ret = mmp_mc_device_is_dev_removed(&b_removed);

    if(MMPR_OK == i4_ret && b_removed)
    {
        /*get path*/
        i4_ret = mmp_fid_get(pt_file->t_path, &ps_path);
        if(MMPR_OK == i4_ret)
        {
            i4_ret = mmp_mc_device_is_path_valid(ps_path, &b_valid);
            if(RMVR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_mc_device_is_path_valid(%s) failed. i4_ret = %d.\r\n", ps_path, i4_ret));
                b_valid = TRUE;
            }
        }
        else
        {
            MMP_DBG_ERROR(("mmp_fid_get(%d) failed. i4_ret = %d.\r\n", pt_file->t_path, i4_ret));
            MMP_ASSERT(0);
        }
    }

    if(FALSE == b_valid) /*device is removed*/
    {
        pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_FILE_REMOVED;
    }

    if(_MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_CORRUPT == e_type)
    {
        pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_IMG_CORRUPT;
    }
    else if(_MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_NOT_EXIST == e_type)
    {
        pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_FILE_NOT_EXIST;
    }
    else if(_MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_PER_DENY == e_type)
    {
        pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_PER_DENY;
    }
    else if(_MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_DLNA_SERVER_OFF == e_type)
    {
        pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_DLNA_SERVER_OFF;
        pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_BAD_FILE;
    }
    else /*_MMP_PE_IMG_SET_BAD_CORRUPT_TYPE_BAD*/
    {
       pt_file->ui2_flag |= _MMP_PE_IMG_FLAG_BAD_FILE;
    }
}

/*-----------------------------------------------------------------------------
 * Name: mmp_pe_get_play_ver
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
UINT32 mmp_pe_get_play_ver(VOID)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;

    return pt_this->ui4_play_ver;
}

static VOID _mmp_pe_rect_print(GL_RECT_T rect)
{
    MMP_DBG_INFO(("[PhotoEng/Print] left=%d, top=%d, width=%d, height=%d.\r\n",
        rect.i4_left,
        rect.i4_top,
        rect.i4_right - rect.i4_left,
        rect.i4_bottom - rect.i4_top));
}

#ifdef APP_3D_PHOTO_SUPPORT
static VOID _mmp_pe_rect_even(GL_RECT_T* rect)  // make the rectangle even to fit YC422 color mode...
{
    INT32   i4_left, i4_right;

    MMP_ASSERT(rect != NULL);

    i4_left     = ((rect->i4_left >> 1) << 1);  // left pixel is 2x
    i4_right    = i4_left + (rect->i4_right - rect->i4_left);
    i4_right   -= ((rect->i4_right - rect->i4_left) % 4);   // width pixel is 4x

    rect->i4_left   = i4_left;
    rect->i4_right  = i4_right;
}
#endif

#ifdef APP_3D_PHOTO_SUPPORT
#ifdef APP_MENU_MMP_COEXIST
static INT32    _mmp_pe_set_3D_mode_disable(BOOL b_disable)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file = &(pt_this->at_img[pt_this->ui1_crnt_img]);

    pt_file->b_3d_disable = b_disable;

    return MMPR_OK;
}

BOOL    _mmp_pe_get_3D_mode_disable(VOID)
{
    _MMP_PE_DATA_MEMBER_T*      pt_this = &t_g_photo_eng;
    _MMP_PE_IMG_FILE_T*         pt_file = &(pt_this->at_img[pt_this->ui1_crnt_img]);

    return pt_file->b_3d_disable;
}
#endif
#endif







//
//
//
//
//
static BOOL _mmp_pe_mi_module_init(VOID)
{
    _MMP_PE_DATA_MEMBER_T*  pt_this = &t_g_photo_eng;
    MI_RESULT eRet = MI_ERR_FAILED;

    if(_bIsMMModuleInit)
    {
        return TRUE;
    }
    MMP_DBG_INFO(("[mmp] %s %d mmp mi module init ..\n",__FUNCTION__, __LINE__));


    // Activate MI modules when process first uses MI API.
    eRet = MI_SYS_Init(NULL);
    if (eRet >= MI_ERR_FAILED)
    {
        MMP_DBG_ERROR(("[mmp] %s %d DISP init fail!!\n",__FUNCTION__, __LINE__));
        return FALSE;
    }
    MMP_DBG_INFO(("[mmp] %s %d DISP init OK\n",__FUNCTION__, __LINE__));


    //
    MI_FS_InitParams_t stFsInitParam = {0};
    eRet = MI_FS_Init(&stFsInitParam);
    if (eRet >= MI_ERR_FAILED)
    {
        MMP_DBG_ERROR(("[mmp] %s %d MI_FS_Init init fail!!\n",__FUNCTION__, __LINE__));
        return FALSE;
    }
    MMP_DBG_INFO(("[mmp] %s %d MI_FS_Init init OK\n",__FUNCTION__, __LINE__));


    // Init MI_DISP
    eRet = MI_DISP_Init(NULL);
    if(eRet >= MI_ERR_FAILED)
    {
        MMP_DBG_ERROR(("[mmp] %s %d DISP init fail!!\n",__FUNCTION__, __LINE__));
        return FALSE;
    }
    MMP_DBG_INFO(("[mmp] %s %d DISP init OK\n",__FUNCTION__, __LINE__));


#ifdef MMP_PHOTO_USE_MI_MM_MODULE
    // Init MI_MM
    eRet = MI_MM_Init(NULL);
    if(eRet >= MI_ERR_FAILED)
    {
        MMP_DBG_ERROR(("[mmp] %s %d MM init fail!!\n",__FUNCTION__, __LINE__));
        return FALSE;
    }
    MMP_DBG_INFO(("[mmp] %s %d MM init OK\n",__FUNCTION__, __LINE__));
#endif

    // Create event group
    MI_U8* psEvtGrpName = (MI_U8*)"MMPEvnGrp";
    if (MI_OS_CreateEventGroup(psEvtGrpName, &gs32PlayEventGroupId)!=MI_OK)
    {
        MMP_DBG_ERROR(("[mmp] %s %d MI_OS_CreateEventGroup fail!!\n",__FUNCTION__, __LINE__));
        return FALSE;
    }
    MMP_DBG_INFO(("[mmp] %s %d I_OS_CreateEventGroup OK\n",__FUNCTION__, __LINE__));




    // Init MI_OSD
    MI_OSD_InitParams_t stInitPar;
    memset(&stInitPar,0,sizeof(MI_OSD_InitParams_t));
    stInitPar.eCanvasBufMode         = E_MI_OSD_WINDOW_CANVAS_AUTO_SWITCH;
    stInitPar.u16SupportSurfaceCount = 64;
    eRet = MI_OSD_Init(&stInitPar);
    if((eRet != MI_OK) && (eRet != MI_HAS_INITED))
    {
        MMP_DBG_ERROR(("[mmp] %s %d OSD module init failed ret: %d\n",__FUNCTION__, __LINE__, eRet));
        return FALSE;
    }
    MMP_DBG_INFO(("[mmp] %s %d OSD init OK\n",__FUNCTION__, __LINE__));


    // Get Disp OutputTiming 1920*1080
    MI_HANDLE hDispController = MI_HANDLE_NULL;
    MI_DISP_Timing_e eTiming = E_MI_DISP_TIMING_1920X1080_60I;
    MI_DISP_GetControllerParams_t stGetControllerParams;
    MI_DISP_OpenControllerParams_t stOpenControllerParams;
    MI_BOOL bIsDispControllerOpened = FALSE;

    memset(&stOpenControllerParams, 0x0, sizeof(MI_DISP_OpenControllerParams_t));
    memset(&stGetControllerParams, 0x00, sizeof(MI_DISP_GetControllerParams_t));
    if(MI_DISP_OpenController(&stOpenControllerParams, &hDispController) != MI_OK)
    {
        CHECK_RET(MI_DISP_GetController(&stGetControllerParams, &hDispController), "MI_DISP_GetController");
    }
    if(hDispController != MI_HANDLE_NULL)
    {
        CHECK_RET(MI_DISP_GetOutputTiming(hDispController, &eTiming), "MI_DISP_GetOutputTiming");
        MMP_DBG_INFO(("[mmp] %s %d eTiming = %d\r\n\r\n\r\n",__FUNCTION__,__LINE__,eTiming));
        CHECK_RET(MI_DISP_CloseController(hDispController),"MI_DISP_CloseController");
    }

#ifdef MMP_PHOTO_USE_MI_MM_MODULE
    // Alloc thumbnail memery
    MI_U32 u32AddrSize;
    if(MI_SYS_GetMemPoolId(NULL, &_s32NonCachedPoolId) != MI_OK)
    {
        MMP_DBG_INFO(("[mmp] %s %d  MI_SYS_GetMemPoolId fail\r\n",__FUNCTION__,__LINE__));
        MMP_ASSERT(0);
    }

    //Alloac Thumbnial/Preview memory
    pt_this->p_thumbnail_data = MI_OS_AllocateMemory(MMP_THUMBNAIL_DATA_MAX_SIZE, _s32NonCachedPoolId);
    if (pt_this->p_thumbnail_data == NULL)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Allocate p_thumbnail_data Memory Fail!\r\n", __FUNCTION__, __LINE__));
        MMP_ASSERT(0);
    }
    pt_this->p_thumbnail_rotate_data = MI_OS_AllocateMemory(MMP_THUMBNAIL_DATA_MAX_SIZE, _s32NonCachedPoolId);
    if (pt_this->p_thumbnail_rotate_data == NULL)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Allocate p_thumbnail_rotate_data Memory Fail!\r\n", __FUNCTION__, __LINE__));
        MMP_ASSERT(0);
    }

#endif

    _bIsMMModuleInit = TRUE;

    //CHECK_RET(MI_MM_SetDebugLevel(MI_DBG_NONE),"MI_MM_SetDebugLevel");
    //CHECK_RET(MI_DISP_SetDebugLevel(MI_DBG_NONE),"MI_DISP_SetDebugLevel");
    //CHECK_RET(MI_OSD_SetDebugLevel(MI_DBG_NONE),"MI_OSD_SetDebugLevel");



    return TRUE;
}

static BOOL _mmp_pe_mi_module_deinit(VOID)
{

    _MMP_PE_DATA_MEMBER_T* pt_this = &t_g_photo_eng;
    MI_RESULT eRet = MI_ERR_FAILED;


    _bIsMMModuleInit = FALSE;

#ifdef MMP_PHOTO_USE_MI_MM_MODULE
    //Free memroy
    if(pt_this->p_thumbnail_rotate_data != NULL)
    {
        MI_OS_FreeMemory(pt_this->p_thumbnail_rotate_data, _s32NonCachedPoolId);
        pt_this->p_thumbnail_rotate_data = NULL;
    }
    if(pt_this->p_thumbnail_data != NULL)
    {
        MI_OS_FreeMemory(pt_this->p_thumbnail_data, _s32NonCachedPoolId);
        pt_this->p_thumbnail_data = NULL;
    }
    // close mm handle
    if (MI_HANDLE_NULL != pt_this->h_MI_MM_Hdl)
    {
        MI_MM_ClearPhoto(pt_this->h_MI_MM_Hdl);
        MI_MM_Stop(pt_this->h_MI_MM_Hdl);
        MI_MM_Close(pt_this->h_MI_MM_Hdl);
        pt_this->h_MI_MM_Hdl = NULL_HANDLE;
    }
#endif

    DBG_INFO_DIRECT("[mmp pe] %s %d done!!\r\n",__FUNCTION__, __LINE__);

    //other
    return TRUE;


}




//
//
//
//
//
static INT32 _mmp_pe_gl_dfb_snapshot_create(UINT32 ui4_w, UINT32 ui4_h)
{
    GL_SURFACE_DESC_T       t_surf_descr;
    INT32                   i4_ret;
    _MMP_PE_DATA_MEMBER_T*  pt_this = &t_g_photo_eng;

    MMP_DBG_INFO(("[mmp] %s %d st_snapshot.ui4_w:%d   st_snapshot.ui4_h:%d!!\r\n",__FUNCTION__,__LINE__,ui4_w,ui4_h));

    if (ui4_w == 0 || ui4_h == 0)
    {
        return MMPR_INV_ARG;
    }
    do {
        /*create surface*/
        c_memset(&t_surf_descr, 0, sizeof(GL_SURFACE_DESC_T));
        t_surf_descr.ui4_width  = ui4_w;
        t_surf_descr.ui4_height = ui4_h;
        t_surf_descr.e_clrmode  = GL_COLORMODE_ARGB_D8888;
        i4_ret = c_gl_surface_create(&t_surf_descr, &pt_this->st_snapshot.h_surf);
        if (GLR_OK != i4_ret)
        {
            break;
        }
        pt_this->st_snapshot.ui4_w = ui4_w;
        pt_this->st_snapshot.ui4_h = ui4_h;

        return MMPR_OK;
    } while (0);

    return MMPR_FAIL;
}

//
//
//
//
//
static INT32 _mmp_pe_gl_dfb_snapshot_free(VOID)
{
    _MMP_PE_DATA_MEMBER_T*  pt_this = &t_g_photo_eng;
    if (pt_this->st_snapshot.h_surf != NULL_HANDLE)
    {
        c_gl_obj_free(pt_this->st_snapshot.h_surf);
        pt_this->st_snapshot.h_surf = NULL_HANDLE;
    }
    return MMPR_OK;
}

//
//
//
//
//
INT32 mmp_pe_gl_dfb_snapshot_save(GL_RECT_T* pt_rect, BOOL b_clean_after_save)
{
    GL_COLOR_T              t_empty_clr = {255, {0}, {0}, {0}};
    INT32                   i4_ret;
    _MMP_PE_DATA_MEMBER_T*  pt_this = &t_g_photo_eng;

    MMP_DBG_INFO(("[mmp] %s %d st_snapshot.ui4_w:%d  st_snapshot.ui4_h:%d!!\r\n",__FUNCTION__,__LINE__,pt_this->st_snapshot.ui4_w,pt_this->st_snapshot.ui4_h));

    //
    if(pt_this->st_snapshot.ui4_w == 0  && pt_this->st_snapshot.ui4_h == 0 && pt_this->st_snapshot.h_surf == NULL_HANDLE)
    {
        pt_this->st_snapshot.ui4_w = (UINT32)RECT_W(pt_rect)+15;
        pt_this->st_snapshot.ui4_h = (UINT32)RECT_H(pt_rect)+15;
        i4_ret = _mmp_pe_gl_dfb_snapshot_create(pt_this->st_snapshot.ui4_w, pt_this->st_snapshot.ui4_h);
        if (MMPR_OK != i4_ret)
        {
            return MMPR_INV_ARG;
        }
    }


    if (pt_this->st_snapshot.ui4_w == 0 ||
        pt_this->st_snapshot.ui4_h == 0 ||
        pt_this->h_thumbnail_surf == NULL_HANDLE                ||
        pt_this->st_snapshot.h_surf == NULL_HANDLE
        )
    {
        return MMPR_INV_ARG;
    }


    i4_ret = c_gl_surface_blt(pt_this->st_snapshot.h_surf,
                              pt_this->h_thumbnail_surf,
                              0,
                              0,
                              pt_rect->i4_left,
                              pt_rect->i4_top,
                              pt_this->st_snapshot.ui4_w,
                              pt_this->st_snapshot.ui4_h,
                              255,
                              GL_SYNC);
    if (GLR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    if (b_clean_after_save)
    {
        i4_ret = c_gl_surface_draw_rect(pt_this->h_thumbnail_surf,
                                        pt_rect,
                                        &t_empty_clr,
                                        1,
                                        GL_STYLE_FILLED,
                                        GL_SYNC);
        if (GLR_OK != i4_ret)
        {
            return MMPR_FAIL;
        }
    }
    return MMPR_OK;
}

//
//
//
//
//
INT32 mmp_pe_gl_dfb_snapshot_load(GL_RECT_T* pt_rect, BOOL b_need_reflash)
{
    INT32                   i4_ret;
    _MMP_PE_DATA_MEMBER_T*  pt_this = &t_g_photo_eng;

    MMP_DBG_INFO(("[mmp] %s %d st_snapshot.ui4_w:%d   st_snapshot.ui4_h:%d!!\r\n",__FUNCTION__,__LINE__,pt_this->st_snapshot.ui4_w,pt_this->st_snapshot.ui4_h));

    if (pt_this->st_snapshot.ui4_w == 0 ||
        pt_this->st_snapshot.ui4_h == 0 ||
        pt_this->h_thumbnail_surf == NULL_HANDLE                ||
        pt_this->st_snapshot.h_surf == NULL_HANDLE
        )
    {
        return MMPR_INV_ARG;
    }

    i4_ret = c_gl_surface_blt(pt_this->h_thumbnail_surf,
                              pt_this->st_snapshot.h_surf,
                              pt_rect->i4_left,
                              pt_rect->i4_top,
                              0,
                              0,
                              pt_this->st_snapshot.ui4_w,
                              pt_this->st_snapshot.ui4_h,
                              255,
                              GL_SYNC);
    if (GLR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    if(b_need_reflash)
    {
        // Flip Surface/View Data to Screen
#ifdef MT5583_MODEL
        i4_ret  = c_gl_plane_flip(pt_this->h_thumbnail_plane, pt_this->h_thumbnail_view, FALSE);
#else
        i4_ret  = c_gl_plane_flip(pt_this->h_thumbnail_plane, pt_this->h_thumbnail_view, TRUE);
#endif
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("[mmp] %s %d c_gl_plane_flip() failed. i4_ret = %d.\r\n",__FUNCTION__,__LINE__, i4_ret));
            return MMPR_FAIL;
        }

    }

    return MMPR_OK;
}


#if 1

#undef MI_IMGDEC_FEATURE_ENABLE
#define MI_IMGDEC_FEATURE_ENABLE 1

#include "mi_imgdec.h"




#define _CONVERT_COLOR_FORMAT_MI_IMGDEC_TO_MI_OSD(pteOSDColorFmt, eIMGDECColorFmt)      \
{                                                               \
    switch(eIMGDECColorFmt)                                     \
    {                                                           \
        case E_MI_IMGDEC_COLOR_FMT_I1:                          \
        case E_MI_IMGDEC_COLOR_FMT_I2:                          \
        case E_MI_IMGDEC_COLOR_FMT_I4:                          \
        case E_MI_IMGDEC_COLOR_FMT_I8:                          \
        case E_MI_IMGDEC_COLOR_FMT_RGB565:                      \
        case E_MI_IMGDEC_COLOR_FMT_ARGB1555:                    \
        case E_MI_IMGDEC_COLOR_FMT_ARGB4444:                    \
            *pteOSDColorFmt = eIMGDECColorFmt;                  \
            break;                                              \
        case E_MI_IMGDEC_COLOR_FMT_YUV422:                      \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_YUV422_YUYV;   \
            break;                                              \
        case E_MI_IMGDEC_COLOR_FMT_ARGB8888:                    \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_ARGB8888;  \
            break;                                              \
        case E_MI_IMGDEC_COLOR_FMT_GENERIC:                     \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_GENERIC;   \
            break;                                              \
        default:                                                \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_YUV422_YUYV;   \
    }                                                           \
}                                                               \


#define _CONVERT_COLOR_FORMAT_MI_MM_TO_MI_OSD(pteOSDColorFmt, eMMColorFmt)      \
{                                                               \
    switch(eMMColorFmt)                                         \
    {                                                           \
        case E_MI_MM_PHOTO_COLOR_FORMAT_ARGB8888:               \
            *pteOSDColorFmt = E_MI_OSD_COLOR_FORMAT_ARGB8888;   \
            break;                                              \
        case E_MI_MM_PHOTO_COLOR_FORMAT_ARGB1555:               \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_ARGB1555;  \
            break;                                              \
        case E_MI_MM_PHOTO_COLOR_FORMAT_ARGB4444:               \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_ARGB4444;  \
            break;                                              \
        case E_MI_MM_PHOTO_COLOR_FORMAT_YUV422_YUYV:            \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_YUV422_YUYV;\
            break;                                              \
        default:                                                \
            *pteOSDColorFmt  = E_MI_OSD_COLOR_FORMAT_YUV422_YUYV;   \
    }                                                           \
}                                                               \


#define _GET_MI_OSD_COLOR_FORMAT_BPP(eOSDColorFmt, pu8Bpp)      \
{                                                               \
    switch(eOSDColorFmt)                                        \
    {                                                           \
        case E_MI_OSD_COLOR_FORMAT_ARGB8888:                    \
        case E_MI_OSD_COLOR_FORMAT_ABGR8888:                    \
        case E_MI_OSD_COLOR_FORMAT_RGBA8888:                    \
        case E_MI_OSD_COLOR_FORMAT_BGRA8888:                    \
            *pu8Bpp = 4;                                        \
            break;                                              \
        case E_MI_OSD_COLOR_FORMAT_RGB565:                      \
        case E_MI_OSD_COLOR_FORMAT_BGR565:                      \
        case E_MI_OSD_COLOR_FORMAT_ARGB4444:                    \
        case E_MI_OSD_COLOR_FORMAT_ARGB1555:                    \
        case E_MI_OSD_COLOR_FORMAT_YUV422_YVYU:                 \
        case E_MI_OSD_COLOR_FORMAT_YUV422_UYVY:                 \
        case E_MI_OSD_COLOR_FORMAT_YUV422_YUYV:                 \
        case E_MI_OSD_COLOR_FORMAT_1ABFGBG12355:                \
        case E_MI_OSD_COLOR_FORMAT_FABAFGBG2266:                \
            *pu8Bpp = 2;                                        \
            break;                                              \
        case E_MI_OSD_COLOR_FORMAT_I1:                          \
        case E_MI_OSD_COLOR_FORMAT_I2:                          \
        case E_MI_OSD_COLOR_FORMAT_I4:                          \
        case E_MI_OSD_COLOR_FORMAT_I8:                          \
            *pu8Bpp = 1;                                        \
            break;                                              \
        default:                                                \
            *pu8Bpp = 0;                                        \
    }                                                           \
}                                                               \


#define _GET_IMAGE_FORMAT(u32ReadSign, ptIMG_Format)            \
{                                                               \
    UINT32 u32_temp = 0x0;                                      \
    u32_temp = u32ReadSign;                                     \
    switch(u32_temp & 0x0FFF0)                                  \
    {                                                           \
        case (E_MI_IMGDEC_FORMAT_JPEG & 0x0FFF0):               \
            u32_temp &= 0x0000FFFF;                             \
            break;                                              \
        case (E_MI_IMGDEC_FORMAT_PNG & 0x0FFF0):                \
            u32_temp &= 0x00FFFF00;                             \
            break;                                              \
        case (E_MI_IMGDEC_FORMAT_GIF & 0x0FFF0):                \
            u32_temp &= 0x00FFFFFF;                             \
            break;                                              \
        case (E_MI_IMGDEC_FORMAT_BMP & 0x0FFF0):                \
            u32_temp &= 0x0000FFFF;                             \
            break;                                              \
        case (E_MI_IMGDEC_FORMAT_MPO & 0xFFF0):                 \
            u32_temp &= 0x00FFFFFF;                             \
            break;                                              \
        default:                                                \
            u32_temp = 0x00FFFFFF;                              \
            break;                                              \
    }                                                           \
    *ptIMG_Format = u32_temp;                                   \
}                                                               \

#ifndef MI_MEM_ALIGN
#define MI_MEM_ALIGN(align, address)                    ((((address)+(align)-1)/(align))*(align))
#endif



typedef struct __MmapLayout_Info_T
{
    MI_SYS_MmapId_e eMmapId;
    MI_VIRT         virtBuffVirAddr;
    MI_U32          u32BufLen;
} _MmapLayout_Info_T;






static INT32 _mmp_pe_get_mmap_layout(_MmapLayout_Info_T * pst_layoutinfo)
{
    INT32   i4_ret = MMPR_OK;
    MI_SYS_MmapLayout_t stMmapLayout;

    if(pst_layoutinfo == NULL)
        return MMPR_FAIL;

    pst_layoutinfo->u32BufLen = 0;
    pst_layoutinfo->virtBuffVirAddr = 0x0;

    do
    {
        memset(&stMmapLayout,0,sizeof(MI_SYS_MmapLayout_t));
        MI_SYS_GetMmapLayout(pst_layoutinfo->eMmapId, &stMmapLayout);
        pst_layoutinfo->u32BufLen = stMmapLayout.u32MemLen;
        if(stMmapLayout.eMemType == E_MI_SYS_MEM_TYPE_UNCACHED)
        {
            stMmapLayout.eMemType = E_MI_SYS_MEM_TYPE_WRITE_BACK;
            i4_ret = MI_SYS_MappingMmapLayout(pst_layoutinfo->eMmapId, &stMmapLayout);
            if(i4_ret != MI_OK)
            {
                stMmapLayout.eMemType = E_MI_SYS_MEM_TYPE_UNCACHED;
                MMP_DBG_ERROR(("[mmp] %s %d ReMapping cache VA fail  mmap_id:%d  i4_ret:%d\n", __FUNCTION__,__LINE__,pst_layoutinfo->eMmapId,i4_ret));
            }
        }
        if(stMmapLayout.eMemType == E_MI_SYS_MEM_TYPE_UNCACHED)
            i4_ret = MI_OS_Pa2NonCachedVa(stMmapLayout.phyMemAddr, &pst_layoutinfo->virtBuffVirAddr);
        else
            i4_ret = MI_OS_Pa2CachedVa(stMmapLayout.phyMemAddr, &pst_layoutinfo->virtBuffVirAddr);
        if((i4_ret != MI_OK) || (pst_layoutinfo->virtBuffVirAddr == 0))
        {
            MMP_DBG_ERROR(("[mmp] %s %d Memory allocate error  mmap_id:%d   i4_ret:%d\n", __FUNCTION__,__LINE__,pst_layoutinfo->eMmapId,i4_ret));
            i4_ret = MMPR_FAIL;
            break;
        }

    }while(0);

    //memset(MI_ADDR_CAST(void*)pst_layoutinfo->virtBuffVirAddr, 0 ,pst_layoutinfo->u32BufLen);
    MMP_DBG_ERROR(("[mmp] %s %d mmap_id:%d   phyMemAddr:0x%x\n", __FUNCTION__,__LINE__,pst_layoutinfo->eMmapId,stMmapLayout.phyMemAddr));
    //
    //Fix Coverity ID : 4597662 Unchecked return value
    if (MI_SYS_FreeMmapLayout(pst_layoutinfo->eMmapId) != MI_OK)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Memory allocate error  mmap_id:%d   MI_SYS_FreeMmapLayout fail\n", __FUNCTION__,__LINE__,pst_layoutinfo->eMmapId));
    }

    return i4_ret;
}


static INT32 _mmp_pe_convert_color_format_data( MI_OSD_Rect_t *pstSrcRect,
                                                                MI_OSD_ColorFormat_e *pteOSDSrcFmt,
                                                                UINT8 * ui2_SrcDataAddr,
                                                                MI_OSD_Rect_t *pstDstRect,
                                                                MI_OSD_ColorFormat_e *pteOSDDstFmt,
                                                                UINT8 * ui2_DstDataAddr)
{
    INT32   i4_ret = MMPR_OK;

    MI_HANDLE hSrcSurface = MI_HANDLE_NULL;
    MI_HANDLE hDstSurface = MI_HANDLE_NULL;
    MI_OSD_SurfaceInfo_t stSurfInfo;
    MI_OSD_BlitOpt_t stBlitOpt = {0};
    MI_U8 u8SrcSurBpp = 1;
    MI_U8 u8DstSurBpp = 1;

    if(pstSrcRect == NULL || pteOSDSrcFmt == NULL || ui2_SrcDataAddr == NULL
|| pstDstRect == NULL || pteOSDDstFmt == NULL || ui2_DstDataAddr == NULL)
        return MMPR_FAIL;

    // Get Bpp by OSD color format
    _GET_MI_OSD_COLOR_FORMAT_BPP(*pteOSDSrcFmt, &u8SrcSurBpp); //
    _GET_MI_OSD_COLOR_FORMAT_BPP(*pteOSDDstFmt, &u8DstSurBpp); //
    MMP_DBG_INFO(("[%s] [%d] eOSDSrcFmt %d  eOSDDstFmt:%d  u8SrcSurBpp:%d  u8DstSurBpp:%d\r\n", __FUNCTION__,__LINE__, *pteOSDSrcFmt,*pteOSDDstFmt,u8SrcSurBpp,u8DstSurBpp));

    pstSrcRect->u32Width = ALIGN_N(pstSrcRect->u32Width,16);

    do
    {
        // Create src surface
        memset(&stSurfInfo,0x00, sizeof(MI_OSD_SurfaceInfo_t));
        stSurfInfo.eColorFormat = *pteOSDSrcFmt;
        stSurfInfo.u32Pitch     = pstSrcRect->u32Width * u8SrcSurBpp; // byte = pixel*bpp
        stSurfInfo.u32Width     = pstSrcRect->u32Width;
        stSurfInfo.u32Height    = pstSrcRect->u32Height;
        stSurfInfo.virtAddr     = (MI_VIRT)ui2_SrcDataAddr;
        stSurfInfo.eMemoryType  = E_MI_OSD_MEMORY_OS;
        stSurfInfo.eOwner       = E_MI_OSD_SURFACE_OWNER_AP;
        MMP_DBG_INFO(("[%s] [%d] Src surface(inter buf): (w, h, p, f)=(%u, %u, %u, %u)\n", __FUNCTION__,__LINE__, stSurfInfo.u32Width, stSurfInfo.u32Height, stSurfInfo.u32Pitch, stSurfInfo.eColorFormat));
        i4_ret = MI_OSD_SurfaceCreate(&stSurfInfo, &hSrcSurface);
        if(i4_ret != MI_OK)
        {
            MMP_DBG_ERROR(("[%s] [%d] MI_OSD_SurfaceCreate  Src failed!! i4_ret = %d.\r\n", __FUNCTION__,__LINE__, i4_ret));
            i4_ret = MMPR_FAIL;
            break;
        }


        // Create dst surface
        memset(&stSurfInfo,0x00, sizeof(MI_OSD_SurfaceInfo_t));
        stSurfInfo.eColorFormat = *pteOSDDstFmt;
        stSurfInfo.u32Pitch     = pstDstRect->u32Width * u8DstSurBpp; // byte = pixel*bpp
        stSurfInfo.u32Width     = pstDstRect->u32Width;
        stSurfInfo.u32Height    = pstDstRect->u32Height;
        stSurfInfo.virtAddr     = (MI_VIRT)ui2_DstDataAddr;
        stSurfInfo.eMemoryType  = E_MI_OSD_MEMORY_OS;
        stSurfInfo.eOwner       = E_MI_OSD_SURFACE_OWNER_AP;
        MMP_DBG_INFO(("[%s] [%d] Dst surface(display buf): (w, h, p, f)=(%u, %u, %u, %u)\n", __FUNCTION__,__LINE__, stSurfInfo.u32Width, stSurfInfo.u32Height, stSurfInfo.u32Pitch, stSurfInfo.eColorFormat));
        i4_ret = MI_OSD_SurfaceCreate(&stSurfInfo, &hDstSurface);
        if(i4_ret != MI_OK)
        {
            MMP_DBG_ERROR(("[%s] [%d] MI_OSD_SurfaceCreate Dst failed!! i4_ret = %d.\r\n", __FUNCTION__,__LINE__, i4_ret));
            i4_ret = MMPR_FAIL;
            break;

        }

        // Bitblit from SrcBuf to DstBuf
        i4_ret = MI_OSD_GetDefaultBlitOpt(&stBlitOpt);
        if(i4_ret != MI_OK)
        {
            MMP_DBG_ERROR(("[%s] [%d] MI_OSD_GetDefaultBlitOpt failed!! i4_ret = %d.\r\n", __FUNCTION__,__LINE__, i4_ret));
            i4_ret = MMPR_FAIL;
            break;

        }
        stBlitOpt.eRotate               = E_MI_OSD_ROTATE_NONE;
        stBlitOpt.eSrcYuvFormat         = E_MI_OSD_YUV422_YUYV;//noto ,imgdec decode default color format is YuYv
        stBlitOpt.eDstYuvFormat         = E_MI_OSD_YUV422_YUYV;
        stBlitOpt.stClipRect.u32X       = 0;
        stBlitOpt.stClipRect.u32Y       = 0;
        stBlitOpt.stClipRect.u32Width   = pstDstRect->u32Width;
        stBlitOpt.stClipRect.u32Height  = pstDstRect->u32Height;
        MI_OSD_BeginDraw();
        i4_ret = MI_OSD_Bitblit(hSrcSurface, pstSrcRect, hDstSurface, pstDstRect, &stBlitOpt, NULL);
        if(i4_ret != MI_OK)
        {
            MMP_DBG_ERROR(("[%s] [%d] MI_OSD_Bitblit failed!! i4_ret = %d.\r\n", __FUNCTION__,__LINE__, i4_ret));
            i4_ret = MMPR_FAIL;
            break;

        }
        MI_OSD_EndDraw();

    }while(0);

    if(hSrcSurface != MI_HANDLE_NULL)
    {
        CHECK_RET(MI_OSD_SurfaceDestroy(hSrcSurface), "MI_OSD_SurfaceDestroy");
    }
    if(hDstSurface != MI_HANDLE_NULL)
    {
        CHECK_RET(MI_OSD_SurfaceDestroy(hDstSurface), "MI_OSD_SurfaceDestroy");
    }



    return i4_ret;
}


//
//
//
//
static INT32 _mmp_pe_dump_image_data_to_bmp_file(MI_MM_PhotoInfo_t *pstPhotoInfo)
{
    INT32   i4_ret = 0;
    MI_U32  u32_vir_addr_temp = 0;

    MI_U32 u32AddrSize;
    MI_S32 s32NonCachedPoolId;
    UINT8*  ps_image_data = NULL;
    MI_OSD_ColorFormat_e eOSDSrcFmt = E_MI_OSD_COLOR_FORMAT_YUV422_YUYV;
    MI_OSD_ColorFormat_e eOSDDstFmt = E_MI_OSD_COLOR_FORMAT_ARGB8888;
    MI_OSD_Rect_t stSrcRect = {0,0,1920,1080};
    MI_OSD_Rect_t stDstRect = {0,0,1920,1080};

    _MmapLayout_Info_T stLayout_Info[4] = { {E_MI_SYS_MMAP_ID_JPD_READ_BUF  , 0, 0},
                                            {E_MI_SYS_MMAP_ID_JPD_INTER_BUF , 0, 0},
                                            {E_MI_SYS_MMAP_ID_JPD_OUT       , 0, 0},
                                            {E_MI_SYS_MMAP_ID_DISP_PHOTO_BUF, 0, 0} };
    if(pstPhotoInfo == NULL)
        return MMPR_FAIL;

    stSrcRect.u32Width  = pstPhotoInfo->u32PhotoSourceWidth;
    stSrcRect.u32Height = pstPhotoInfo->u32PhotoSourceHeight;

    stDstRect.u32Width  = pstPhotoInfo->u32PhotoSourceWidth;
    stDstRect.u32Height = pstPhotoInfo->u32PhotoSourceHeight;


    // 0
    i4_ret = MI_SYS_GetMemPoolId(NULL, &s32NonCachedPoolId);
    if(i4_ret != MI_OK)
    {
        MMP_DBG_ERROR(("[%s] [%d] MI_SYS_GetMemPoolId init fail!! i4_ret:%d\n", __FUNCTION__,__LINE__,i4_ret));
        return MMPR_FAIL;
    }

    // Alloc memory for Dst image surface
    ps_image_data = (UINT8 *)MI_OS_AllocateMemory(stDstRect.u32Width * stDstRect.u32Height * 4 + 500, s32NonCachedPoolId);//1080*1920*4+100 byte
    if(ps_image_data == NULL)
    {
        MMP_DBG_ERROR(("[%s] [%d] MI_OS_AllocateMemory() fail!! i4_ret = %d.\r\n", __FUNCTION__,__LINE__, i4_ret));
        return MMPR_FAIL;
    }

    //
    for(UINT8 i=0; i<4 ; i++)
    {
        _mmp_pe_get_mmap_layout(&stLayout_Info[i]);
    }


    // Convert/Mapping Mi MM color format to MI OSD color format
    _CONVERT_COLOR_FORMAT_MI_MM_TO_MI_OSD(&eOSDSrcFmt, pstPhotoInfo->ePhotoColorFormat);

    for(UINT8 i=0; i<4 ; i++)
    {
        u32_vir_addr_temp = (MI_U32)stLayout_Info[i].virtBuffVirAddr;    //CID:4597684
        memset(ps_image_data,0,stDstRect.u32Width * stDstRect.u32Height * 4 + 500);
        i4_ret = _mmp_pe_convert_color_format_data( &stSrcRect, &eOSDSrcFmt, (UINT8 *)u32_vir_addr_temp,
                                                    &stDstRect, &eOSDDstFmt, ps_image_data);
        if(i4_ret == MMPR_OK)
        {
            ST_BITMAP st_ap_bitmap;
            st_ap_bitmap.u4_image_height = stDstRect.u32Height;
            st_ap_bitmap.u4_image_width  = stDstRect.u32Width;
            st_ap_bitmap.u4_widthbyte    = stDstRect.u32Width * 4;
            st_ap_bitmap.u4_image_size   = stDstRect.u32Width * stDstRect.u32Height * 4;
            st_ap_bitmap.u2_palette_size = 0;
            st_ap_bitmap.u2_bitcount     = 32;
            st_ap_bitmap.u1_p_image_data = (UINT8*)ps_image_data;

            vd_g_SaveBitmap(&st_ap_bitmap,"test");
        }
        u32_vir_addr_temp = 0;
    }



    //
    if(ps_image_data != NULL)
    {
        MI_OS_FreeMemory(ps_image_data, s32NonCachedPoolId);
    }

    return i4_ret;
}
#endif


//////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
Get 16 bits motorola order (always) for jpeg header stuff.
--------------------------------------------------------------------------*/
STATIC int EXIF_Get16m(void * Short)
{
    return (((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1];
}

/*--------------------------------------------------------------------------
Convert a 16 bit unsigned value from file's native unsigned char order
--------------------------------------------------------------------------*/
STATIC int EXIF_Get16u(void * Short)
{
    if (m_MotorolaOrder)
    {
       return (((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1];
    }
    else
    {
       return (((unsigned char *)Short)[1] << 8) | ((unsigned char *)Short)[0];
    }
}

/*--------------------------------------------------------------------------
Convert a 32 bit signed value from file's native unsigned char order
--------------------------------------------------------------------------*/
STATIC long EXIF_Get32s(void * Long)
{
    if (m_MotorolaOrder)
    {
       return ((( char *)Long)[0] << 24) | (((unsigned char *)Long)[1] << 16)
         | (((unsigned char *)Long)[2] << 8 ) | (((unsigned char *)Long)[3] << 0 );
    }
    else
    {
       return ((( char *)Long)[3] << 24) | (((unsigned char *)Long)[2] << 16)
         | (((unsigned char *)Long)[1] << 8 ) | (((unsigned char *)Long)[0] << 0 );
    }
}

/*--------------------------------------------------------------------------
Convert a 32 bit unsigned value from file's native unsigned char order
--------------------------------------------------------------------------*/
STATIC ULONG EXIF_Get32u(void * Long)
{
    return (unsigned long)EXIF_Get32s(Long) & 0XFFFFFFFF;
}




//
//Evaluate number, be it int, rational, or float from directory.
//
STATIC double _mmp_pe_exif_convert_format(void * ValuePtr, int Format)
{
    double Value = 0;

    switch(Format)
    {
        case FMT_SBYTE:     Value = *(signed char *)ValuePtr;
            break;
        case FMT_BYTE:      Value = *(unsigned char *)ValuePtr;
            break;
        case FMT_USHORT:    Value = EXIF_Get16u(ValuePtr);
            break;
        case FMT_ULONG:     Value = EXIF_Get32u(ValuePtr);
            break;
        case FMT_URATIONAL:
        case FMT_SRATIONAL:
        {
            int Num,Den;
            Num = EXIF_Get32s(ValuePtr);
            Den = EXIF_Get32s(4+(char *)ValuePtr);
            if (Den == 0)
            {
              Value = 0;
            }
            else
            {
              Value = (double)Num/Den;
            }
            break;
        }
        case FMT_SSHORT:    Value = (signed short)EXIF_Get16u(ValuePtr);
            break;
        case FMT_SLONG:     Value = EXIF_Get32s(ValuePtr);
            break;
        /* Not sure if this is correct (never seen float used in Exif format) */
        case FMT_SINGLE:    Value = (double)*(float *)ValuePtr;
            break;
        case FMT_DOUBLE:    Value = *(double *)ValuePtr;
            break;
    }
    return Value;
}


//
//
//
STATIC BOOL _mmp_pe_process_exif_info(const UCHAR* DataStart, const DWORD dwFilePointerBeforeReadData,
                                UCHAR *DirStart, UCHAR *OffsetBase, const UINT32 ExifLength,
                                _MMP_IMAGE_INFO * const m_exifinfo, UCHAR **const LastExifRefdP)
{
    int de = 0;                 //
    int a = 0;                  //
    int NumTagEntries = 0;      //TAG number
    int BytesCount = 0;         //
    UCHAR * TagEntry = 0;       //TAG entry
    int Tag, Format, Components;
    UCHAR * ValuePtr = 0;       //offset after position
    DWORD OffsetVal = 0;        //offset value

    MMP_DBG_INFO(("[mmp] %s %d _mmp_pe_process_exif_info.\r\n", __FUNCTION__,__LINE__));


    //get TAG number
    NumTagEntries = EXIF_Get16u(DirStart);

    //judeg EXIF info length is correct
    //follow DirStart+2 is beside NumTagEntries  2 byte
    if ((DirStart+2+NumTagEntries*12) > (OffsetBase+ExifLength))
    {
        MMP_DBG_ERROR(("[mmp] %s %d Illegally sized directory\r\n",__FUNCTION__,__LINE__));
        return 0;
    }

    for (de=0;de<NumTagEntries;de++)
    {
        TagEntry = DirStart+2+12*de;    //TagEntry entry
        Tag = EXIF_Get16u(TagEntry);
        Format = EXIF_Get16u(TagEntry+2);
        Components = EXIF_Get32u(TagEntry+4);

        if ((Format-1) >= NUM_FORMATS)
        {
            //(-1) catches illegal zero case as unsigned underflows to positive large
            MMP_DBG_ERROR(("[mmp] %s %d Illegal format code in EXIF dir\r\n",__FUNCTION__,__LINE__));
            return 0;
        }
        BytesCount = Components * m_BytesPerFormat[Format];
        if (BytesCount > 4)
        {
            OffsetVal = EXIF_Get32u(TagEntry+8);
            //If its bigger than 4 unsigned chars, the dir entry contains an offset.
            if (OffsetVal+BytesCount > ExifLength)
            {
                //JPG file is destorry
                MMP_DBG_ERROR(("[mmp] %s %d Illegal pointer offset value in EXIF.\r\n",__FUNCTION__,__LINE__));
                return 0;
            }
            ValuePtr = OffsetBase+OffsetVal;
        }
        else
        {
            //4. unsigned chars or less and value is in the dir entry itself
            ValuePtr = TagEntry+8;
        }
        if (*LastExifRefdP < ValuePtr+BytesCount)
        {
            //check agian JPG file in correct
            *LastExifRefdP = ValuePtr+BytesCount;
        }

        // Extract useful components of tag
        switch(Tag)
        {
            case TAG_MAKE:
                break;
            case TAG_MODEL:
                strncpy(m_exifinfo->CameraModel, (char*)ValuePtr, 39);
                break;

            case TAG_EXIF_VERSION:
                break;
            //photo shooting time e.g  2005-10-13 11:09:35
            case TAG_DATETIME_ORIGINAL:
                strncpy(m_exifinfo->DateTime, (char*)ValuePtr, 19);
                break;
            case TAG_DATATIME_DIGITIZED:
                strncpy(m_exifinfo->DateTimeDigitized, (char*)ValuePtr, 19);
                break;
            //user commont
            case TAG_USERCOMMENT:
                break;
            //
            case TAG_MAKE_COMMENT:
                break;
            //aperture  e.g F2.8
            case TAG_FNUMBER:
                break;
            //sperture value£¬e.g F2.8
            //max aperture  e.g F2.8
            case TAG_APERTURE:
            case TAG_MAXAPERTURE:
                break;
            //Brightness
            case TAG_BRIGHTNESS:
                break;
            //f-number e.g 7.09mm
            case TAG_FOCALLENGTH:
                break;
            //
            case TAG_SUBJECT_DISTANCE:
                break;
            //exposure time£¬e.g 1/30 second
            case TAG_EXPOSURETIME:
                m_exifinfo->ExposureTime = (float)_mmp_pe_exif_convert_format(ValuePtr, Format);
                break;
            //
            case TAG_SHUTTERSPEED:
                break;
            //FLASH
            case TAG_FLASH:
                m_exifinfo->FlashUsed = (int)_mmp_pe_exif_convert_format(ValuePtr, Format);
                break;
            case TAG_ORIENTATION:
                m_exifinfo->Orientation = (int)_mmp_pe_exif_convert_format(ValuePtr, Format);
                if (m_exifinfo->Orientation < 1 || m_exifinfo->Orientation > 8)
                {
                    MMP_DBG_ERROR(("[mmp] %s %d Undefined rotation value\r\n",__FUNCTION__,__LINE__));
                    m_exifinfo->Orientation = 0;
                }
                break;
            //EXIF height and width
            case TAG_EXIF_IMAGELENGTH:
            case TAG_EXIF_IMAGEWIDTH:
                a = (int)_mmp_pe_exif_convert_format(ValuePtr, Format);
                if (m_ExifImageWidth < a) m_ExifImageWidth = a;
                break;
            case TAG_FOCALPLANEXRES:
            case TAG_FOCALPLANEYRES:
                break;
            case TAG_RESOLUTIONUNIT:
                break;
            //
            case TAG_FOCALPLANEUNITS:
                break;
            //exposure compensation£¬e.gEV0.0
            case TAG_EXPOSURE_BIAS:
                m_exifinfo->ExposureBias = (float) _mmp_pe_exif_convert_format(ValuePtr, Format);
                break;
            //LightSource white balance
            case TAG_WHITEBALANCE:
                break;
            case TAG_METERING_MODE:
                break;
            case TAG_EXPOSURE_PROGRAM:
                m_exifinfo->ExposureProgram = (int)_mmp_pe_exif_convert_format(ValuePtr, Format);
                break;
            case TAG_ISO_EQUIVALENT:
                m_exifinfo->ISOequivalent = (int)_mmp_pe_exif_convert_format(ValuePtr, Format);
                if ( m_exifinfo->ISOequivalent < 50 ) m_exifinfo->ISOequivalent *= 200;
                break;
            case TAG_COMPRESSION_LEVEL:
                break;
            //X resolution
            case TAG_XRESOLUTION:
                break;
            //Y resolution
            case TAG_YRESOLUTION:
                break;
            //thumbnail data offset
            case TAG_THUMBNAIL_OFFSET:
                break;
            //thumbnial data len
            case TAG_THUMBNAIL_LENGTH:
                break;
        } //end switch(Tag)
        //EXIF info offset
        if (Tag == TAG_EXIF_OFFSET || Tag == TAG_INTEROP_OFFSET)
        {
            UCHAR * SubdirStart;
            SubdirStart = OffsetBase + EXIF_Get32u(ValuePtr);
            if (SubdirStart < OffsetBase ||
              SubdirStart > OffsetBase+ExifLength)
            {
                MMP_DBG_ERROR(("[mmp] %s %d Illegal subdirectory link\r\n",__FUNCTION__,__LINE__));
                return 0;
            }
            _mmp_pe_process_exif_info(DataStart, dwFilePointerBeforeReadData, SubdirStart, OffsetBase, ExifLength, m_exifinfo, LastExifRefdP);
            continue;
        }
    } //end for {for (de=0;de<NumTagEntries;de++)}

    //In addition to linking to subdirectories via exif tags,
    //there's also a potential link to another directory at the end
    //of each directory. This has got to be the result of a
    //committee!

    UCHAR * SubdirStart;
    unsigned Offset;
    Offset = EXIF_Get16u(DirStart+2+12*NumTagEntries);
    if (Offset)
    {
        SubdirStart = OffsetBase + Offset;
        if (SubdirStart < OffsetBase
          || SubdirStart > OffsetBase+ExifLength)
        {
            MMP_DBG_ERROR(("[mmp] %s %d Illegal subdirectory link\r\n",__FUNCTION__,__LINE__));
            return 0;
        }
        _mmp_pe_process_exif_info(DataStart, dwFilePointerBeforeReadData, SubdirStart, OffsetBase, ExifLength, m_exifinfo, LastExifRefdP);
    }

    return TRUE;
}

//
//
//
STATIC BOOL _mmp_pe_process_exif_info_tag(const UCHAR *DataStart, const DWORD dwFilePointerBeforeReadData,
                              UCHAR *CharBuf, const UINT32 length)
{
    int FirstOffset = 0;
    UCHAR *LastExifRefd = 0;
    g_pImageInfo->FlashUsed = 0;

    m_ExifImageWidth = 0;

    //MMP_DBG_INFO(("[%s %d] _mmp_pe_process_exif_info_tag.\r\n", __FUNCTION__,__LINE__));
    //check EXIF head
    //static const unsigned char ExifHeader[] = "Exif/0/0";
    //if (memcmp(CharBuf+0, ExifHeader,6) != 0)
    //{
    //  MMP_DBG_ERROR(("Incorrect Exif header\r\n"));
    //  return 0;
    //}

    //judeg memory data is Intel or Motorola CPU
    if (memcmp(CharBuf+6,"II",2) == 0)
    {
        m_MotorolaOrder = 0;    //
    }
    else if (memcmp(CharBuf+6,"MM",2) == 0)
    {
        m_MotorolaOrder = 1; //
    }
    else
    {
        MMP_DBG_ERROR(("[mmp] %s %d Invalid Exif alignment marker.\r\n",__FUNCTION__,__LINE__));
        return 0;
    }

    //check follow 2 byte is 0x2A00 ???
    if (EXIF_Get16u(CharBuf+8) != 0x2A)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Invalid Exif start (1)\r\n",__FUNCTION__,__LINE__));
        return 0;
    }

    //judge 0th IFD Offset is 0x08000000 ???
    FirstOffset = EXIF_Get32u(CharBuf+10);
    if (FirstOffset < 8 || FirstOffset > 16)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Suspicious offset of first IFD value\r\n",__FUNCTION__,__LINE__));
        return 0;
    }

    LastExifRefd = CharBuf;

    //start parse EXIF info
    if (!_mmp_pe_process_exif_info(DataStart, dwFilePointerBeforeReadData,
       CharBuf+14, CharBuf+6, length-6, g_pImageInfo, &LastExifRefd))
    {
        return 0;
    }

    return 1;
}

//
//
//
STATIC VOID _mmp_pe_process_sofn_tag (const UCHAR * Data, int marker)
{
    int IsColor; //
    int Process; //
    int data_precision, num_components;
    //MMP_DBG_INFO(("[%s %d] !!\r\n",__FUNCTION__,__LINE__));

    data_precision = Data[2];
    g_pImageInfo->Height = EXIF_Get16m((Data+3));
    g_pImageInfo->Width = EXIF_Get16m((Data+5));
    num_components = Data[7];

    if (num_components == 3)
    {
        IsColor = 1;
    }
    else
    {
        IsColor = 0;
    }

    Process = marker;
}

//
//
//
STATIC int _mmp_pe_parse_jpeg_image_data(FILE *pFile)
{
    int a=0, b=0;
    int nSectionsRead = 0;        //had read SECTION number
    DWORD dwFileRead = 0;         //Read stream File byte size
    DWORD dwFilePointerBeforeReadData = 0;  //Read stream file before , file position
    Section_t Sections[MAX_SECTIONS];       //JPG file SECTIONS

    int   nSectionLength=0;     //SECTION(APP) len
    int   marker = 0;           //
    int   ll=0,lh=0, got=0;     //
    UCHAR *Data = 0;            //

    //MMP_DBG_INFO(("[%s %d] _mmp_pe_parse_jpeg_image_data.\r\n", __FUNCTION__,__LINE__));

    //read JPG 1th, 2th byte£¬judge == 0xFF,M_SOI ??
    dwFileRead = MI_FS_Fread((void *)&a, 1, 1, pFile);
    if(dwFileRead != 1)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Unexpect File End\r\\n",__FUNCTION__,__LINE__));
        return -1;
    }
    dwFileRead = MI_FS_Fread((void *)&b, 1, 1, pFile);
    if(dwFileRead != 1)
    {
        MMP_DBG_ERROR(("Unexpect File End\r\n",__FUNCTION__,__LINE__));
        return -1;
    }
    //judge is EXIF flie???
    //EXIF file much be  FF D8
    if (a != 0xFF || b != M_SOI)
    {
        MMP_DBG_ERROR(("[mmp] %s %d File Format Error\r\n",__FUNCTION__,__LINE__));
        return -1;
    }
    //loop£¬read stream JPG file SECTION
    //first SECTION much be APP1£¬and APP1 start Marker much be FFE1
    for(;;)
    {
        if (nSectionsRead >= MAX_SECTIONS)
        {
            MMP_DBG_ERROR(("[mmp] %s %d Too many sections in this jpg file\r\n",__FUNCTION__,__LINE__));
            return -1;
        }
        //find JPG file fill byte£¬7 byte much had 1 byte is 0xFF
        for (a=0;a<7;a++)
        {
            dwFileRead = MI_FS_Fread((void *)&marker, 1, 1, pFile);
            if(dwFileRead != 1)
            {
                MMP_DBG_ERROR(("[mmp] %s %d Unexpect File End\r\n",__FUNCTION__,__LINE__));
                return -1;
            }
            if (marker != 0xFF) break;

            if (a >= 6)
            {
                MMP_DBG_ERROR(("[mmp] %s %d Too many padding unsigned chars\r\n",__FUNCTION__,__LINE__));
                return -1;
            }
        }
#if 0
        if(nSectionsRead==0) //APP 1
        {
            ASSERT(marker == M_APP1);
        }
#endif
        Sections[nSectionsRead].Type = marker;
        //recode read starem file before file point position
        dwFilePointerBeforeReadData = MI_FS_Ftell(pFile);
        //read this SECTION lenght
        //Fix Cverity ID : 4597645 Unused value
        dwFileRead = MI_FS_Fread((void *)&lh, 1, 1, pFile);
        if(dwFileRead != 1)
        {
            MMP_DBG_ERROR(("[mmp] %s %d Unexpect File End\r\n",__FUNCTION__,__LINE__));
        }
        dwFileRead = MI_FS_Fread((void *)&ll, 1, 1, pFile);
        if(dwFileRead != 1)
        {
            MMP_DBG_ERROR(("[mmp] %s %d Unexpect File End\r\n",__FUNCTION__,__LINE__));
        }
        //EXIF file high byte is first£¬low byte is after£¬can;t read a WORD type
        nSectionLength = (int)((lh << 8) | ll);  //CID:4597612

        if (nSectionLength < 2)
        {
            MMP_DBG_ERROR(("[mmp] %s %d Invalid Marker\r\n",__FUNCTION__,__LINE__));
            return -1;
        }
        Data = (UCHAR *)malloc(nSectionLength);
        if (Data == NULL)
        {
            MMP_DBG_ERROR(("[mmp] %s %d Could not allocate memory!\r\n",__FUNCTION__,__LINE__));
            return -1;
        }
        Sections[nSectionsRead].Data = Data;

        // Store first two pre-read unsigned chars.
        Data[0] = (UCHAR)lh;
        Data[1] = (UCHAR)ll;
        dwFileRead = MI_FS_Fread((void *)(Data+2), 1, nSectionLength-2, pFile);
        if(dwFileRead !=(DWORD)(nSectionLength-2))
        {
            free(Data);
            MMP_DBG_ERROR(("[mmp] %s %d Premature end of file\r\n",__FUNCTION__,__LINE__));
            return -1;
        }
        //get starem file current point position
        dwFileRead = MI_FS_Ftell(pFile);

        nSectionsRead += 1;
        switch(marker)
        {
            case M_SOS:   //had get data
                free(Sections[--nSectionsRead].Data);
                Sections[nSectionsRead].Data=0;
                //MMP_DBG_INFO(("[%s %d] return M_SOS !!\r\n",__FUNCTION__,__LINE__));
                return 0;
            case M_EOI:   //End Of Image
                free(Sections[--nSectionsRead].Data);
                Sections[nSectionsRead].Data=0;
                //MMP_DBG_INFO(("[%s %d] return M_EOI   No image in this jpeg file !!\r\n",__FUNCTION__,__LINE__));
                return -1;
            case M_COM:   //comment info
                break;
            case M_JFIF:
                break;
            case M_EXIF:
                //EXIF info TAG
                if (memcmp(Data+2, "Exif", 4) == 0)
                {
                    g_pImageInfo->IsExif = _mmp_pe_process_exif_info_tag(Data, dwFilePointerBeforeReadData, (unsigned char *)Data+2, nSectionLength);
                }
                break;
            case M_SOF0:
            case M_SOF1:
            case M_SOF2:
            case M_SOF3:
            case M_SOF5:
            case M_SOF6:
            case M_SOF7:
            case M_SOF9:
            case M_SOF10:
            case M_SOF11:
            case M_SOF13:
            case M_SOF14:
            case M_SOF15:
                _mmp_pe_process_sofn_tag(Data, marker);
                break;
            default:
                // Skip any other sections.
                //if (ShowTags) printf("Jpeg section marker 0x%02x size %d/n",marker, nSectionLength);
                break;
        }
        free(Sections[--nSectionsRead].Data);
        Sections[nSectionsRead].Data=0;

    }
    return 0;
}

//
//
//
INT32 mmp_pe_get_image_info(const char* pszFileName, _MMP_IMAGE_INFO* pImageInfo)
{
    int nReturn = 0;
    FILE *pFile = NULL;
    int u32ReadSign = 0;

    if(pImageInfo == NULL || pszFileName == NULL)
    {
        MMP_DBG_ERROR(("[mmp] %s %d Parameter incorreted! photo Info must not be NULL!\r\n",__FUNCTION__,__LINE__));
        return -1;
    }
    //MMP_DBG_INFO(("[%s %d] MI_FS_Fopen: %s.\r\n", __FUNCTION__,__LINE__, pszFileName));

    //Open image file
    pFile = MI_FS_Fopen((const MI_U8 *)pszFileName,(const MI_U8 *)"rb");
    if(pFile == NULL)
    {
        MMP_DBG_ERROR(("[mmp] %s %d JPG File Not Found!\r\n",__FUNCTION__,__LINE__));
        return -1;
    }

    //Get/judge photo type
    nReturn = MI_FS_Fread(&u32ReadSign, 1, sizeof(int), pFile);
    if(nReturn != sizeof(int))    //CID:4632278
    {
        MMP_DBG_ERROR(("[mmp] %s %d image info read error!\r\n",__FUNCTION__,__LINE__));
        goto ERR;
    }
    nReturn = 0;

    switch(u32ReadSign & 0x0FF00)
    {
        case (E_FS_FORMAT_JPEG & 0x0FF00):
            u32ReadSign &= 0x0000FFFF;
            break;
        case (E_FS_FORMAT_PNG & 0x0FF00):
            u32ReadSign &= 0x00FFFF00;
            break;
        case (E_FS_FORMAT_GIF & 0x0FF00):
            u32ReadSign &= 0x00FFFFFF;
            break;
        case (E_FS_FORMAT_BMP & 0x0FF00):
            u32ReadSign &= 0x0000FFFF;
            break;
        default:
            u32ReadSign = 0;
            break;
    }
    switch(u32ReadSign)
    {
        case E_FS_FORMAT_JPEG:
            pImageInfo->PhotoType = E_FS_FORMAT_JPEG;
            break;
        case E_FS_FORMAT_PNG:
            pImageInfo->PhotoType = E_FS_FORMAT_PNG;
            break;
        case E_FS_FORMAT_GIF:
            pImageInfo->PhotoType = E_FS_FORMAT_GIF;
            break;
        case E_FS_FORMAT_BMP:
            pImageInfo->PhotoType = E_FS_FORMAT_BMP;
            break;
        default:
            pImageInfo->PhotoType = E_FS_FORMAT_UNSUPPORT;
            goto ERR;
    }

    //init
    pImageInfo->IsExif = FALSE;
    pImageInfo->Height = 0;
    pImageInfo->Width  = 0;

    //only jpeg format image had exif info
    if(u32ReadSign == E_FS_FORMAT_JPEG)
    {
        //Set stream filr point to start
        MI_FS_Fseek(pFile,0L,SEEK_SET);

        g_pImageInfo = pImageInfo;
        nReturn = _mmp_pe_parse_jpeg_image_data(pFile);
    }
    //if bmp/gif/png format image, continu get image w/h
    else
    {
        UINT8 height_data[4] = {0};
        UINT8 width_data[4]  = {0};

        if(u32ReadSign == E_FS_FORMAT_BMP)
        {
            MI_FS_Fseek(pFile,0x10,SEEK_SET);
            MI_FS_Fread(width_data, 1, 4, pFile);
            MI_FS_Fread(height_data,1, 4, pFile);
            pImageInfo->Height = (int)(height_data[3] << 8) + height_data[2];
            pImageInfo->Width  = (int)(width_data[3] << 8)  + width_data[2];
        }
        else if(u32ReadSign == E_FS_FORMAT_PNG)
        {
            MI_FS_Fseek(pFile,0x10,SEEK_SET);
            MI_FS_Fread(width_data, 1, 4, pFile);
            MI_FS_Fread(height_data,1, 4, pFile);
            pImageInfo->Height = height_data[3] + (int)(height_data[2] << 8);
            pImageInfo->Width  = width_data[3]  + (int)(width_data[2] << 8);
        }
        else if(u32ReadSign == E_FS_FORMAT_GIF)
        {
            MI_FS_Fseek(pFile,0x6,SEEK_SET);
            MI_FS_Fread(&pImageInfo->Width,  1, 2, pFile);
            MI_FS_Fread(&pImageInfo->Height, 1, 2, pFile);
        }
#if NEVER    //CID:4632255
        else
        {
            nReturn = -1;
        }
#endif
    }


ERR:
    //
    MI_FS_Fclose(pFile);

    return nReturn;
}





