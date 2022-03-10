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
 * $RCSfile: mmp_ff.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *          This is the header file for display resource controller.
 *---------------------------------------------------------------------------*/
#ifndef _MMP_BROWSE_ENG_H_
#define _MMP_BROWSE_ENG_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "mmp/mmp_common.h"
#include "mmp/mmp_mmc_basic.h"
#include "mmp/mmp_mmc_device.h"
#include "mmp/mmp_mmc_list.h"
#include "mmp/mmp_mmc_file.h"
#include "mmp/mmp_mmc_browse.h"
#include "mmp/mmp_intf_file_browser.h"
#include "mmp/app/mmp_main.h"
#include "mmp/file_filter/mmp_ff.h"
#include "mmp/file_filter/mmp_fid.h"
#include "mmp/file_filter/mmp_mem_pool.h"
#include "mmp/util/mmp_util.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "app_util/a_cfg.h"
#include "res/mmp/browse_eng/mmp_browse_eng_rc.h"
#include "res/mmp/audio_player/mmp_audio_player_rc.h"
#include "res/mmp/mmc/mmp_mmc_rc.h"
#include "res/mmp/mmp_common_rc.h"

#ifdef APP_NETWORK_SUPPORT
#include "c_fm_dlnafs.h"
#include "c_dm_dlna.h"
#endif

#include "c_fm.h"
#include "u_irrc_btn_def.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define MMP_MC_BWR_ID_NULL          ((UINT8) 255)
#define MMP_BE_MAX_PATH_LEN         (MMP_RC_PATH_MAX_LEN)
#define MMP_BE_PATH_SEPRATE_LEN     (1)

#define MMP_BE_INVALID_FILE_IDX     ((UINT32) 0xFFFFFFFF)
#define MMP_BE_EMPTY_PATH           "@@EMPTY_PATH@@"
#define MMP_BE_IS_EMPTY_PATH(_path)                             \
(                                                               \
    (0 == c_strcmp(MMP_BE_EMPTY_PATH, _path)) ? TRUE : FALSE    \
)

#define MMP_BE_IS_LEGAL_SORT_TYPE(_e_media_type, _e_sort_type)  TRUE

#define MMP_BE_GET_FULL_ITEM_PATH(_t_item_info, _s_full_path)                   \
{                                                                               \
    if (NULL != (_t_item_info).s_parent_name && NULL != (_t_item_info).s_name)  \
    {                                                                           \
        c_strcpy((_s_full_path), (_t_item_info).s_parent_name);                 \
        c_strcat((_s_full_path), "/");                                          \
        c_strcat((_s_full_path), (_t_item_info).s_name);                        \
    }                                                                           \
}

/*-----Browser Engine command-----*/
typedef enum _MMP_VIDEO_PLAY_MODE_T
{
    MMP_PLAY_REPEAT_MODE_NONE = 0,           /*whole folder will be played once.*/
    MMP_PLAY_REPEAT_MODE_ONE,                /*current file will be played repeatedly.*/
    MMP_PLAY_REPEAT_MODE_ALL,                /*whole folder will be played repeatedly.*/
    MMP_PLAY_REPEAT_MODE_ONE_ONCE            /*current file will be played once.*/
} MMP_VIDEO_PLAY_MODE_T;

/* File Browser status */
typedef enum _MMP_BE_STATUS_T
{
    MMP_BE_STATUS_NONE = 0,
    MMP_BE_STATUS_NORMAL,
    MMP_BE_STATUS_PLAYER_ACT,
    MMP_BE_STATUS_BACKGROUND,
    MMP_BE_STATUS_CHOOSE_FF,
    MMP_BE_STATUS_CHOOSE_MNT,
    MMP_BE_STATUS_CUSTOM_0,
    MMP_BE_STATUS_CUSTOM_1,
} MMP_BE_STATUS_T;

/*File filter index*/
typedef enum _MMP_BE_FF_IDX
{
    MMP_BE_FF_IDX_CRT = 0,
    MMP_BE_FF_IDX_CHILD,
    MMP_BE_FF_IDX_TOTAL,
} MMP_BE_FF_IDX;

/* File source type*/
typedef enum _MMP_BE_FILE_SRC_TYPE_T
{
    MMP_BE_FILE_SRC_UNKNOWN,
    MMP_BE_FILE_SRC_MASS_STRG,
    MMP_BE_FILE_SRC_DLNA,
    MMP_BE_FILE_SRC_NET_NEIGHBOR

} MMP_BE_FILE_SRC_TYPE_T;

typedef struct _MMP_BE_VP_RANGE_INFO_T
{
    UINT8           ui1_row_num;
    UINT8           ui1_col_num;
} MMP_BE_VP_RANGE_INFO_T;

/*-----Get-Info ID-----*/
typedef enum _MMP_BE_INFO_GET_INFO_ID_T
{
    MMP_BE_INFO_GET_INFO_ID_STATUS = 0,         /*pv_param: a pointer to MMP_BE_STATUS_T value*/
    MMP_BE_INFO_GET_INFO_ID_SORT_TYPE,          /*pv_param: a pointer to MMP_SORT_TYPE_T value*/
    MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,        /*pv_param: a pointer to MMP_MEDIA_TYPE_T value*/
    MMP_BE_INFO_GET_INFO_ID_FB_MODE,            /*pv_param: a pointer to MMP_FB_MODE value*/
    MMP_BE_INFO_GET_INFO_ID_FOCUS_ITEM_IDX,     /*pv_param: a pointer to UINT32 value*/
    MMP_BE_INFO_GET_INFO_ID_FOCUS_FILE_IDX,     /*pv_param: a pointer to UINT32 value*/
    MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE,       /*pv_param: a pointer to BOOL value*/
    MMP_BE_INFO_GET_INFO_ID_IS_ADD_PARENT,      /*pv_param: a pointer to BOOL value*/
    MMP_BE_INFO_SET_INFO_ID_GET_PATH_FLAG,
    MMP_BE_INFO_GET_INFO_ID_GET_VIDEO_PLAY_MODE /* pv_param: a a pointer to UINT8  value*/
} MMP_BE_INFO_GET_INFO_ID_T;

/*-----Set-Info ID-----*/
typedef enum _MMP_BE_INFO_SET_INFO_ID_T
{
    MMP_BE_INFO_SET_INFO_ID_STATUS = 0,         /*pv_param: a MMP_BE_STATUS_T value*/
    MMP_BE_INFO_SET_INFO_ID_SORT_TYPE,          /*pv_param: a MMP_SORT_TYPE_T value*/
    MMP_BE_INFO_SET_INFO_ID_FILTER_TYPE,        /*pv_param: a MMP_MEDIA_TYPE_T value*/
    MMP_BE_INFO_SET_INFO_ID_FB_MODE,            /*pv_param: a MMP_FB_MODE value*/
    MMP_BE_INFO_SET_INFO_ID_FOCUS_ITEM_IDX,     /*pv_param: a UINT32 value*/
    MMP_BE_INFO_SET_INFO_ID_FOCUS_FILE_IDX,     /*pv_param: a UINT32 value*/
    MMP_BE_INFO_SET_INFO_ID_IS_RECURSIVE,       /*pv_param: a BOOL value*/
    MMP_BE_INFO_SET_INFO_ID_SHOW_PLAYLIST_ONLY, /*pv_param: a BOOL value*/
    MMP_BE_INFO_SET_INFO_ID_SORT_STATUS_NFY,    /*pv_param: a mmp_sort_status_nfy*/
    MMP_BE_INFO_SET_INFO_ID_VP_RANGE_INFO,      /*pv_param: a pointer to MMP_BE_VP_RANGE_INFO struct*/
    MMP_BE_INFO_SET_INFO_ID_PREVIEW_INFO,       /*pv_param: a pointer to MMP_FP_PREVIEW_INFO_T struct*/
    MMP_BE_INFO_SET_INFO_ID_SET_PATH_FLAG,      /*pv_param: a MMP_FF_SET_PATH_FLAG_T value*/
    MMP_BE_INFO_SET_INFO_ID_SET_ACT_MNT_POINT,  /*pv_param: a UINT32 value*/
    MMP_BE_INFO_SET_INFO_ID_SET_VIDEO_PLAY_MODE /* pv_param: a UINT8 */
} MMP_BE_INFO_SET_INFO_ID_T;

/*-----Browser Engine command-----*/
typedef enum _MMP_BE_BROWSER_CMD_ID_T
{
    MMP_BE_BROWSER_CMD_ID_EXIT_BG_MODE      = 0,
} MMP_BE_BROWSER_CMD_ID_T;

/*-----Browser Engine UI notification-----*/
typedef enum _MMP_BE_UI_UPD_FIELD_T
{
    MMP_BE_UI_UPD_FIELD_EMPTY              = 0,
    MMP_BE_UI_UPD_FIELD_NO_DEVICE          = 0x00000001,
    MMP_BE_UI_UPD_FIELD_MNT_LST            = 0x00000002,
    MMP_BE_UI_UPD_FIELD_ITEM_LIST          = 0x00000004,
    MMP_BE_UI_UPD_FIELD_FOLDER_XNG         = 0x00000008,
    MMP_BE_UI_UPD_FIELD_BK_PLAYER_STOP     = 0x00000010,
    MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_XNG     = 0x00000020,
    MMP_BE_UI_UPD_FIELD_PARSE_STATUS_UPD   = 0x00000040,
    MMP_BE_UI_UPD_FIELD_FOCUS_ITEM_NAME    = 0x00000080,
    MMP_BE_UI_UPD_FIELD_FOCUS_ITEM_INFO    = 0x00000100,
    MMP_BE_UI_UPD_FIELD_CRT_FDLR_NAME      = 0x00000200,
    MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_LST     = 0x00000400,
    MMP_BE_UI_UPD_FIELD_PLAY_ITEM_INFO     = 0x00000800,
    MMP_BE_UI_UPD_FIELD_PARSING_TIMEOUT    = 0x00001000,
    MMP_BE_UI_UPD_FIELD_DEV_NUM_CHG        = 0x00002000,
    MMP_BE_UI_UPD_FIELD_LIMITED_FLDR       = 0x00004000,
    MMP_BE_UI_UPD_FIELD_OPEN_FLDR_FAIL     = 0x00008000,
    MMP_BE_UI_UPD_FIELD_MNT_DEV_XNG        = 0x00010000,
    MMP_BE_UI_UPD_FIELD_ACT_DEV_INVALID    = 0x00020000,
    MMP_BE_UI_UPD_FIELD_ITEM_SORTED        = 0x00040000,
    MMP_BE_UI_UPD_FIELD_CRNT_PATH_CHANGE   = 0x00080000
} MMP_BE_UI_UPD_FIELD_T;

typedef enum _MMP_BE_UI_VALID_FIELD_T
{
    MMP_BE_UI_VALID_FIELD_ITEM_LIST,
    MMP_BE_UI_VALID_FIELD_PARSE_STATUS,
    MMP_BE_UI_VALID_FIELD_MEDIA_TYPE,
    MMP_BE_UI_VALID_FIELD_MNT_LST
} MMP_BE_UI_VALID_FIELD_T;

typedef enum _MMP_BE_ITEM_TYPE_T
{
    MMP_BE_ITEM_TYPE_DIR   = 0,
    MMP_BE_ITEM_TYPE_IMAGE,
    MMP_BE_ITEM_TYPE_AUDIO,
    MMP_BE_ITEM_TYPE_VIDEO,
    MMP_BE_ITEM_TYPE_TEXT,
    MMP_BE_ITEM_TYPE_UNKNOWN
} MMP_BE_ITEM_TYPE_T;

typedef struct _MMP_BE_ADV_DIR_INFO_T
{
    UINT32 ui4_dir_num;
    UINT32 ui4_file_num;
} MMP_BE_ADV_DIR_INFO_T;

typedef struct _MMP_BE_ADV_FILE_INFO_PHOTO_T
{
    GL_SIZE_T   t_gl_size;
} MMP_BE_ADV_FILE_INFO_PHOTO_T;

typedef struct _MMP_BE_ADV_FILE_INFO_AUDIO_T
{
    UTF16_T     w2s_info[MMP_BE_MAX_PATH_LEN];
} MMP_BE_ADV_FILE_INFO_AUDIO_T;

typedef struct _MMP_BE_ADV_FILE_INFO_VIDEO_T
{
    UTF16_T     w2s_info[MMP_BE_MAX_PATH_LEN];
} MMP_BE_ADV_FILE_INFO_VIDEO_T;

typedef struct _MMP_BE_ADV_ITEM_INFO
{
    MMP_BE_ITEM_TYPE_T                  e_type;
    union
    {
        MMP_BE_ADV_DIR_INFO_T           t_dir;
        MMP_BE_ADV_FILE_INFO_PHOTO_T    t_photo;
        MMP_BE_ADV_FILE_INFO_AUDIO_T    t_audio;
        MMP_BE_ADV_FILE_INFO_VIDEO_T    t_video;
    } u;
} MMP_BE_ADV_ITEM_INFO;

typedef struct _MMP_BE_UI_INFO_T
{
    MMP_BE_UI_UPD_FIELD_T           e_upd_field;
    MMP_BE_UI_VALID_FIELD_T         e_valid_field;
    MMP_FF_PARSE_STATUS_T           e_parse_status;
    UINT32                          ui4_dir_num;        /* Number of sub dirs in current dir */
    UINT32                          ui4_file_num;       /* Number of files in current dir */
    UINT32                          ui4_focus_idx;      /* Focus item in current dir */
    MMP_ITEM_INFO_T                 t_focus_item;
    MMP_BE_ADV_ITEM_INFO            t_focus_adv_info;
} MMP_BE_UI_INFO_T;

typedef INT32 (*mmp_be_browser_cmd_do)(MMP_BE_BROWSER_CMD_ID_T e_cmd_id, VOID* pv_cmd_param);
typedef INT32 (*mmp_be_browser_data_change_fct)(const MMP_BE_UI_INFO_T* pt_upd_data);

typedef struct _MMP_BE_BROWSER_HDLR_T
{
    mmp_be_browser_cmd_do           pf_cmd_do;
    mmp_be_browser_data_change_fct  pf_data_change;
} MMP_BE_BROWSER_HDLR_T;

#define MMP_BE_BROWSER_HDLR_IS_LEGAL(_t_hdlr)                       \
(                                                           \
    (((_t_hdlr).pf_cmd_do) &&                               \
    ((_t_hdlr).pf_data_change)) ? TRUE : FALSE              \
)

#define MMP_BE_BWR_FLAG_SKIP_MNT_PNT_SEL       ((UINT16) 0x01)
#define MMP_BE_BWR_FLAG_SKIP_MEDIA_TYPE_SEL    ((UINT16) 0x02)
#define MMP_BE_BWR_FLAG_ADD_PARENT_ITEM        ((UINT16) 0x04)
#define MMP_BE_BWR_FLAG_ENABLE_FILE_PREVIEW    ((UINT16) 0x08)

typedef struct _MMP_BE_BROWSER_PROPERTY_T
{
    UINT16                      ui2_flag;
    MMP_BE_VP_RANGE_INFO_T      t_range_info;
    MMP_FP_PREVIEW_INFO_T       t_preview_info;
} MMP_BE_BROWSER_PROPERTY_T;
//MMP_BE_INIT_BWR_PROP()

typedef enum _MMP_BE_REFRESH_REASON_T
{
    MMP_BE_REFRESH_TYPE_MNT_LST = 0,
    MMP_BE_REFRESH_TYPE_ITEM_LST,
} MMP_BE_REFRESH_REASON_T;

typedef enum
{
    MMP_PASTE_STATUS_NO_FILE,
    MMP_PASTE_STATUS_AVAILABLE,
    MMP_PASTE_STATUS_UNAVAILABLE
}   MMP_PASTE_STATUS_T;

#ifdef APP_MENU_MMP_COEXIST
typedef enum _MMP_BE_BROWSER_MEDIA_TYPE
{
    MMP_BE_BROWSER_MEDIA_TYPE_NONE = 0,
    MMP_BE_BROWSER_MEDIA_TYPE_AUDIO,
    MMP_BE_BROWSER_MEDIA_TYPE_VIDEO,
    MMP_BE_BROWSER_MEDIA_TYPE_PHOTO
}MMP_BE_BROWSER_MEDIA_TYPE;

typedef enum _MMP_BE_BROWSER_STATUS_T
{
    MMP_BE_BROWSER_STATUS_NONE = 0,
	MMP_BE_BROWSER_STATUS_PHOTO,
    MMP_BE_BROWSER_STATUS_PHOTO_THUMBNAIL_PLAYING,
    MMP_BE_BROWSER_STATUS_PHOTO_THUMBNAIL_NOT_PLAYING,
    MMP_BE_BROWSER_STATUS_PHOTO_LIST_PLAYING,
    MMP_BE_BROWSER_STATUS_PHOTO_LIST_NOT_PLAYING,
    MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_BACK_NORMAL_PLAYING,
    MMP_BE_BROWSER_STATUS_AUDIO_LIST_BACK_NORMAL_PLAYING,
    MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_BACK_FF_PLAYING,
    MMP_BE_BROWSER_STATUS_AUDIO_LIST_BACK_FF_PLAYING,
    MMP_BE_BROWSER_STATUS_AUDIO_FORE_FF_PLAYING,
    MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_BACK_FR_PLAYING,
    MMP_BE_BROWSER_STATUS_AUDIO_LIST_BACK_FR_PLAYING,
    MMP_BE_BROWSER_STATUS_AUDIO_FORE_FR_PLAYING,
    MMP_BE_BROWSER_STATUS_AUDIO_FORE_NORMAL_PLAYING,
    MMP_BE_BROWSER_STATUS_AUDIO_THUMBNAIL_NOT_PLAYING,
    MMP_BE_BROWSER_STATUS_AUDIO_LIST_NOT_PLAYING,
    MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_NORMAL_PREVIEW,
    MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_FF_PREVIEW,
    MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_FR_PREVIEW,
    MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING,
    MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING,
    MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING,
    MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING,
    MMP_BE_BROWSER_STATUS_VIDEO_THUMBNAIL_NOT_PLAYING,
    MMP_BE_BROWSER_STATUS_VIDEO_LIST_NORMAL_PREVIEW,
    MMP_BE_BROWSER_STATUS_VIDEO_LIST_FF_PREVIEW,
    MMP_BE_BROWSER_STATUS_VIDEO_LIST_FR_PREVIEW,
    MMP_BE_BROWSER_STATUS_VIDEO_LIST_NOT_PLAYING,
    MMP_BE_BROWSER_STATUS_ERROR,
    MMP_BE_BROWSER_STATUS_END
}MMP_BE_BROWSER_STATUS_T;
#endif

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 mmp_be_init(VOID);
extern INT32 mmp_be_deinit(VOID);
extern INT32 mmp_be_reg_brower(const MMP_FILE_BROWSER_INTF_T* pt_intf,
                               const MMP_MC_FILE_BROWSER_PROPERTY_T* pt_property,
                               const MMP_BE_BROWSER_HDLR_T* pt_bwr_hdlr,
                               const MMP_BE_BROWSER_PROPERTY_T* pt_bwr_prop);
extern INT32 mmp_be_activate(UINT8 ui1_bwr_id, UINT32 ui4_file_idx);
extern INT32 mmp_be_inactivate(VOID);
extern INT32 mmp_be_default_msg_hdlr(MMP_MSG_ID_T e_msg_id, VOID* pv_msg_param);
extern INT32 mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_T e_info_id, VOID* pv_param);
extern INT32 mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_T e_info_id, VOID* pv_param);
extern BOOL mmp_be_is_root_path(VOID);
extern INT32 mmp_be_get_file_src_type(const CHAR* ps_pname, MMP_BE_FILE_SRC_TYPE_T* pe_type);
extern INT32 mmp_be_get_curr_path(CHAR* ps_pname, SIZE_T* pz_size);
extern INT32 mmp_be_set_curr_path(CHAR* ps_pname);

extern INT32 mmp_be_get_curr_path_display(UTF16_T* pw2s_text, UTF16_T** ppw2s_final_path, SIZE_T* pz_size);
extern INT32 mmp_be_get_focus_path(CHAR* ps_pname, SIZE_T* pz_size);
extern BOOL mmp_be_is_traverse_down(MMP_BE_FF_IDX e_ff_idx);
extern INT32 mmp_be_is_empty_folder(MMP_BE_FF_IDX e_ff_idx, BOOL* pb_is_empty);
extern INT32 mmp_be_get_ff_path_name(MMP_BE_FF_IDX e_ff_idx, CHAR** pps_pname);
extern INT32 mmp_be_get_item_num(MMP_BE_FF_IDX e_ff_idx, UINT32* pui4_dir_num, UINT32* pui4_file_num);
extern INT32 mmp_be_get_item_info(MMP_BE_FF_IDX e_ff_idx,
                                  MMP_ITEM_TYPE_T e_filter_type,
                                  UINT32 ui4_idx_start,
                                  UINT32* pui4_cnt,
                                  MMP_ITEM_INFO_T* pt_item_info);
extern INT32 mmp_be_refresh(MMP_BE_FF_IDX e_ff_idx, MMP_BE_REFRESH_REASON_T e_reason);
extern INT32 mmp_be_switch_browser(UINT8 ui1_bwr_id, BOOL b_reset);
extern INT32 mmp_be_cd_child(UINT32 ui4_focus_idx);
extern INT32 mmp_be_cd_parent(VOID);
extern MMP_ITEM_TYPE_T mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX e_ff_idx,
                                                   UINT32 ui4_item_idx);
extern INT32 mmp_be_set_focus_item(UINT32 ui4_focus_idx);

extern CHAR* mmp_be_get_filtered_item_name(CHAR* s_item_name);

extern INT32 mmp_be_preview_crnt_file(UINT32 ui4_focus_idx);
extern INT32 mmp_be_stop_preview(VOID);

extern INT32 mmp_be_auth_touch_folder(UINT32 ui4_focus_idx);

extern INT32 mmp_be_default_key_handle(UINT32 ui4_key_code,UINT32 ui4_keystatus);

extern INT32 mmp_be_pause_mmp(VOID);

extern INT32 mmp_be_paste(VOID);
extern INT32 mmp_be_delete(VOID);
extern INT32 mmp_be_press_select(UINT32 ui4_idx);
extern INT32 mmp_be_file_in_list(MMP_FF_ITEM_LIST_TYPE_T e_list_type, UINT32 ui4_idx, BOOL* pb_exists);
extern INT32 mmp_be_add_to_sel_list(UINT32 ui4_idx);
extern INT32 mmp_be_clone_to_copy_list(UINT32 ui4_idx);
extern INT32 mmp_be_clone_to_del_list(UINT32 ui4_idx);
extern INT32 mmp_be_empty_crt_folder_list(MMP_FF_ITEM_LIST_TYPE_T e_list_type);
extern INT32 mmp_be_get_paste_status(MMP_PASTE_STATUS_T* pe_paste_status);
extern BOOL  mmp_be_is_copy_available(VOID);
extern BOOL  mmp_be_is_delete_available(VOID);
extern INT32 mmp_be_stop_bg_player(VOID);

extern BOOL mmp_be_is_item_in_list(MMP_BE_FF_IDX e_ff_idx,
                                   MMP_ITEM_TYPE_T e_filter_type,
                                   UINT32 ui4_idx,
                                   MMP_FF_ITEM_LIST_TYPE_T e_list_type);
extern INT32 mmp_be_update_list_item(MMP_ITEM_TYPE_T e_filter_type,
                                     UINT32 ui4_idx,
                                     MMP_FF_ITEM_LIST_TYPE_T e_list_type,
                                     MMP_FF_ITEM_LIST_OP_TYPE_T e_op_type);
extern INT32 mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX e_ff_idx, UINT32 ui4_start_idx, UINT32* pui4_target_idx);

extern INT32 mmp_be_set_item_status(MMP_ITEM_TYPE_T e_filter_type, 
                                    UINT32 ui4_idx,
                                    MMP_FF_ITEM_FLAG_T e_flag);
extern INT32 mmp_be_start_play_crnt_folder(UINT32 ui4_focus_idx, BOOL b_view_only);

extern INT32 mmp_be_get_device_info(UINT32                   ui4_idx,
                                       UTF16_T*                 pw2s_dev_info,
                                       RMV_DEV_DEVICE_STATUS_T* pe_dev_status,
                                       BOOL*                    pb_next);

extern INT32 mmp_be_get_dlna_serial_name(UINT32     ui4_idx,
                                              UTF16_T*   pw2s_dev_hint);

extern INT32 mmp_be_get_usb_serial_name(UINT32     ui4_idx,
                                             UTF16_T*   pw2s_dev_hint);

extern INT32 mmp_be_get_activate_device_info(UTF16_T* pw2s_dev_info,
                                                  UTF16_T* pw2s_dev_hint,
                                                  UINT32*  pui4_active_idx);

#ifdef APP_NET_DLNA_SUPPORT
extern BOOL mmp_be_current_is_dlna_device(VOID);
#endif

#ifdef APP_MENU_MMP_COEXIST
extern MMP_BE_BROWSER_STATUS_T a_mmp_be_get_browser_status(VOID);
extern BOOL a_mmp_is_video_playing(VOID);
extern MMP_BE_BROWSER_STATUS_T a_mmp_get_av_stat(VOID);
extern MMP_BE_BROWSER_MEDIA_TYPE a_mmp_be_get_media_type(VOID);

#endif

extern BOOL a_mmp_is_video_full_screen(VOID);

#ifdef APP_NET_DLNA_SUPPORT
extern BOOL mmp_be_dlna_is_seek_supported(CHAR* s_name);
#endif

#ifdef APP_CAST_TV_MMP_FG
extern INT32 mmp_be_reset(VOID);
#endif


#endif /* _MMP_BROWSE_ENG_H_ */
