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
 * $RCSfile: thumbnailmode.h,v $
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

#ifndef _MMP_THUMBNAIL_MODE_H_
#define _MMP_THUMBNAIL_MODE_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "c_os.h"
#include "u_irrc_btn_def.h"
#include "c_uc_str.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#include "mmp/common_ui2/mmp_info_bar.h"
#include "res/mmp/thumbnailmode/mmp_thumbnailmode_rc.h"
#include "res/mmp/gen/mmp_mmp_layout.h"
#include "res/mmp/gen/mmp_tm_focus_layout.h"
#include "app_util/option_list/a_optl.h"
#ifdef APP_NET_NEIGHBOR_SUPPORT
#include "app_util/pwd_dlg_util/a_pwd_dlg_util.h"
#endif
#include "res/nav/nav_variant.h"
#include "wdk/util/wdk_wgl_util.h"
#include "mmp/disp_res_ctrler/mmp_drc.h"
#include MMP_COM_UI_HEADER_FILE
#include MMP_MLM_HEADER_FILE
#include "res/mmp/gen/mmp_tm_focus_layout.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MMP_TM_VIEW_INFO_STR_MAX_LEN            MMP_RC_PATH_MAX_LEN
#define MMP_TM_MAX_USB_DEV_NUM                  ((UINT32)6)
#define MMP_TM_MAX_NAV_WIG__NUM                 (7)
#define MMP_TM_UI_OPTL_SHUFFLE_TYPE_NUM     (2)
#define MMP_TM_UI_OPTL_SPEED_TYPE_NUM       (6)
#define MMP_TM_UI_OPTL_EFFECT_TYPE_NUM      (8)
#define MMP_THUMBNAILMODE_TEXT(key)   \
            MLM_MMP_TEXT(ui2_g_menu_curr_lang, (key))


#define MMP_PHOTO_POP_UP_LEFT               (560*2)///(560*4/3)      
#define MMP_PHOTO_POP_UP_TOP                (50*2)//(50*4/3)
#define MMP_PHOTO_POP_UP_WIDTH              (282*2)//(282*4/3)
#define MMP_PHOTO_POP_UP_HIGHT              (376*2)//(376*4/3)
#define MMP_PHOTO_POP_UP_OFFICE             (300*2)//(300*4/3)

#define MMP_THMBNAILMODE_MAX_THUMBS         (9)

#ifdef APP_TTS_SUPPORT
#define MMP_TM_VIEW_OPTL_SORT              (0)
#define MMP_TM_VIEW_OPTL_VIEW              (1)
#define MMP_TM_VIEW_OPTL_SETTINGS          (2)
#endif



/* sort  options, view options ,settings options     */
typedef enum _OPTION_KINDS
{
    MMP_THUB_OPTL_SORT = 0,
    MMP_THUB_OPTL_VIEW,
    MMP_THUB_OPTL_SETTINGS,
    MMP_THUB_OPTL_DEV_LIST
}OPTION_KINDS;


typedef enum _MMP_TM_UPDATE_REASON_T
{
    MMP_TM_UPDATE_REASON_HIDE_RIGHT_FRAM           	= 0x00000001,
    MMP_TM_UPDATE_REASON_UPD_TOOL_BAR_HINT      	= 0x00000002,
    MMP_TM_UPDATE_REASON_HIDE_FILE_INFO         	= 0x00000004,
    MMP_TM_UPDATE_REASON_CLEAN_PAGE_INFO        	= 0x00000008,
    MMP_TM_UDPATE_REASON_DEV_NUM_CHG            	= 0x00000010,
    MMP_TM_UDPATE_REASON_BK_PLAYER_STOP         	= 0x00000020,
    MMP_TM_UPDATE_REASON_ACT_MEDIA_RMV          	= 0x00000040,
    MMP_TM_UPDATE_REASON_HIDE_ALL_THUMB         	= 0x00000080,
    MMP_TM_UPDATE_REASON_FDLR_NAME              	= 0x00000100,
    MMP_TN_UPDATE_REASON_THUMB_NAME             	= 0x00000200,
    MMP_TM_UPDATE_RESAON_LEFT_UI					= 0x00000400,
    MMP_TM_UPDATE_RESAON_PAGE						= 0x00000800,
    MP_TM_UPDATE_RESAON_SET_PAGE_NUM				= 0x00001000
    
} MMP_TM_UPDATE_REASON_T;

typedef enum _MMP_TM_VIEW_WARN_MSG_ID_T
{
    MMP_TM_VIEW_WARN_MSG_EMPTY          = 0,
    MMP_TM_VIEW_WARN_MSG_WAITING,
    MMP_TM_VIEW_WARN_MSG_NO_DEVICE,
    MMP_TM_VIEW_WARN_MSG_LIMITED_FLDR,
    MMP_TM_VIEW_WARN_MSG_OPEN_FLDR_FAIL,
    MMP_TM_VIEW_WARN_MSG_PWD_ERROR,
    MMP_TM_VIEW_WARN_MSG_LOCK_INP,
} MMP_TM_VIEW_WARN_MSG_ID_T;


typedef enum _MMP_TM_WIDGET_TYPE
{
    WIDGET_TEXT        = 0,
    WIDGET_BTN,
    WIDGET_EDB,
    WIDGET_LB

} MMP_TM_WIDGET_TYPE;

/*-------Speed  type-----------*/
typedef enum _MMP_SPEED_SEC_TYPE_T
{
    MMP_SPEED_TYPE_5SECONDS =0,
    MMP_SPEED_TYPE_10SECONDS,
    MMP_SPEED_TYPE_15SECONDS,
    MMP_SPEED_TYPE_20SECONDS,
    MMP_SPEED_TYPE_25SECONDS,
    MMP_SPEED_TYPE_30SECONDS
    
} MMP_SPEED_SEC_TYPE_T;

#define	MMP_EFCT_TYPE_TOTAL_NUM 	(8)

#define MMP_PP_RC_DLB_GET_SPEED(_ui4_idx, _ui4_dur) /*ms*/      \
{                                                               \
    switch(_ui4_idx)                                           \
    {                                                           \
    case 1:                                                     \
        (_ui4_dur) = 10000;                                    \
        break;                                                  \
    case 2:                                                     \
        (_ui4_dur) = 15000;                                    \
        break;                                                  \
    case 3:                                                     \
        (_ui4_dur) = 20000;                                    \
        break;                                                  \
    case 4:                                                     \
        (_ui4_dur) = 25000;                                    \
        break;                                                  \
    case 5:                                                     \
        (_ui4_dur) = 30000;                                    \
        break;                                                  \
    case 0:                                                     \
        (_ui4_dur) = 5000;                                     \
    default:                                                    \
           break;                                               \
    }                                                           \
}

/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/
typedef struct _MMP_TM_TRANSPARENT_T
{
    GL_RECT_T    at_rect[TM_THUMB_ITEM_FRAME_H_NUM * TM_THUMB_ITEM_FRAME_V_NUM];
    BOOL         ab_is_enable[TM_THUMB_ITEM_FRAME_H_NUM * TM_THUMB_ITEM_FRAME_V_NUM];
}MMP_TM_TRANSPARENT_T;

typedef enum _MMP_TM_WAIT_TIMER_STATUS
{
    MMP_TM_WAIT_TIMER_STATUS_NONE = 0,
    MMP_TM_WAIT_TIMER_STATUS_LISTEN,
    MMP_TM_WAIT_TIMER_STATUS_EXPIRED
} MMP_TM_WAIT_TIMER_STATUS;

typedef enum _MMP_TM_POPUP_STATUS_T
{
    MMP_TM_POPUP_STATUS_OFF,
    MMP_TM_POPUP_STATUS_ON,
    MMP_TM_POPUP_STATUS_PREVIEW
}MMP_TM_POPUP_STATUS_T;

typedef enum _MMP_TM_PHOTO_EFFECT
{
	MMP_TM_EFFECT_RANDOM	= 0,
	MMP_TM_EFFECT_DISSOLVE,
	MMP_TM_EFFECT_WIPE_RIG,
	MMP_TM_EFFECT_WIPE_LEF,
	MMP_TM_EFFECT_WIPE_UP,
	MMP_TM_EFFECT_WIPE_DONE,
	MMP_TM_EFFECT_BOX_IN,
	MMP_TM_EFFECT_BOX_OUT
}MMP_TM_PHOTO_EFFECT;

typedef struct _MMP_TM_MEMBER_T
{
    MMP_TM_WAIT_TIMER_STATUS        e_wt_status;
    BOOL                            b_load_first_page;
    HANDLE_T                        h_frm_base_frm;
    HANDLE_T                        h_frm_left_base_frm;
    HANDLE_T                        h_frm_left_ui_frm1;
    HANDLE_T                        h_frm_right_base_frm;
    HANDLE_T                        h_frm_thumbnailmode_ui_frm;
    HANDLE_T                        h_frm_htl_thumbnail_mov_frm;
    HANDLE_T                        h_frm_htl_folder_mov_frm;
    HANDLE_T                        h_btn_right_to_left_btn;
    HANDLE_T                        h_thumb_frm;
    HANDLE_T                        h_folder_frm;
    HANDLE_T                        h_folder_text;
    HANDLE_T                        h_transparent_rect;
    HANDLE_T                        h_option_list;
    HANDLE_T                        h_pwd_dlg;
    HANDLE_T                        h_pop_up_exculde_help_text;
	HANDLE_T						h_last_focus_wigt;
	HANDLE_T						h_last_left_focus_wigt;
    WGL_HIMG_TPL_T                  h_thumbnail_load_fail_img;
    HANDLE_T                        h_info_frm;
    HANDLE_T                        h_play_frm;
    WGL_HIMG_TPL_T                  h_thumbnail_photo_img;
    WGL_HIMG_TPL_T                  h_thumbnail_folder_img;
    WGL_HIMG_TPL_T                  h_thumbnail_music_img;
    WGL_HIMG_TPL_T                  h_thumbnail_na_img;
    MMP_FF_SET_PATH_FLAG_T          changed_view_mode;
    MMP_SHUFFLE_MODE_T              shuffle_type;
    UINT32                             speed_type;//MMP_SPEED_TYPE_T                speed_type;
    MMP_TM_PHOTO_EFFECT              effect_type;
	UINT32								sort_type;
#ifdef APP_NET_DLNA_SUPPORT
    /* DLNA related resource */
    WGL_HIMG_TPL_T                  h_thumbnail_dlna_folder_img;
#endif
    BOOL                            b_is_loaded_first_page;

#ifdef APP_NET_NEIGHBOR_SUPPORT
    WGL_HIMG_TPL_T                  h_thumbnail_mnp_folder_img;
#endif

    UINT32                          ui4_focus_idx;              /* Focus item idex in current dir*/
    //UINT32          ui4_folder_focus_idx;
    UINT8                           ui1_hlt_idx;                /* Highlight idx, 0 <= ui1_hlt_idx < H_NUM * V_NUM */
    //UINT8           ui1_folder_hlt_idx;

    UINT32                          ui4_dir_num;                /* Number of sub dirs in current dir*/
    UINT32                          ui4_file_num;               /* Number of files in current dir*/

    UINT32                          ui4_thumb_idx_start;        /* Index of start item for loading thumbnail(inclusive)*/
    UINT32                          ui4_thumb_idx_end;          /* Index of end item for loading thumbnail(exclusive)*/
    UINT32                          ui4_thumb_idx_next;         /* Index of current item for loading thumbnail(exclusive)*/
    UINT16                          ui2_thumb_item_idx;         /* Index of last shown thumbnail, 0 <= ui1_hlt_idx < H_NUM * V_NUM*/
    UINT32                          ui4_thumb_idx_curr;         /* Index of current file for loading thumbnail */
    BOOL                            b_is_nofile_show;

    UINT8                           ui1_gui_lang_id;

    BOOL                            b_is_parsing_folder;
    //BOOL            b_is_pwd_err_show;

    UINT8                           ui1_max_h_num;
    UINT8                           ui1_max_v_num;
    MMP_TM_TRANSPARENT_T            at_transp;
    UINT8                           ui1_thumb_size_id;

    HANDLE_T                        h_preview_trans_list;
    VOID*                           pv_drc_snapshot_thumb;
    GL_RECT_T                       t_rect_preview;
    BOOL                            b_loading_thumb;
    MMP_TM_POPUP_STATUS_T           e_popup_status;
    BOOL                            b_preview_rotate;
    BOOL                            b_skip_flag[MMP_THMBNAILMODE_MAX_THUMBS];
	BOOL							b_recursive;
	BOOL 							b_thumb_active;
	BOOL							b_is_dev_list_show;
    HANDLE_T                        h_pop_up_skip_icon;
	BOOL							b_refersh_data_ready;
    BOOL                            b_optl_show;

#ifdef APP_TTS_SUPPORT
    UINT16                          ui2_optl_item;
#endif
}   MMP_TM_MEMBER_T;


/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
extern INT32 a_mmp_thumbnailmode_register(VOID);
extern INT32 mmp_thumbnailmode_update_ui(MMP_TM_MEMBER_T* pt_this, MMP_TM_UPDATE_REASON_T e_upd_reason, BOOL b_repaint);
extern INT32 mmp_thumbnailmode_show_warning_msg(MMP_TM_MEMBER_T* pt_this,
                                                MMP_TM_VIEW_WARN_MSG_ID_T e_warning_id,
                                                BOOL b_is_show,
                                                BOOL b_is_repaint);


extern INT32 mmp_thumbnailmode_optl_create(MMP_TM_MEMBER_T* pt_this);
extern INT32 mmp_thumbnailmode_optl_destroy(MMP_TM_MEMBER_T* pt_this);
extern INT32 mmp_thumbnailmode_optl_show(MMP_TM_MEMBER_T* pt_this,void* pv_param);
extern INT32 mmp_thumbnailmode_optl_hide_ui(MMP_TM_MEMBER_T* pt_this, BOOL b_repaint);
extern INT32 mmp_thumbnailmode_change_size(MMP_TM_MEMBER_T* pt_this);
extern VOID mmp_thumbnailmode_set_page_num(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx);
extern INT32 mmp_thumbnailmode_view_updatet_widget_text(MMP_TM_MEMBER_T* pt_this);
extern INT32 mmp_thumbnailmode_show_img_preview(MMP_TM_MEMBER_T* pt_this, BOOL b_show);
extern INT32 mmp_thumbnailmode_set_navigation(MMP_TM_MEMBER_T* pt_this);
extern INT32 mmp_thumbnailmode_get_folder_img(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_dev_idx, WGL_HIMG_TPL_T* ph_img_tpl);

extern INT32 mmp_thumbnail_display_file_info(MMP_TM_MEMBER_T* pt_this);

extern INT32 mmp_thumbnailmode_view_set_path(BOOL b_repaint);
extern INT32 mmp_thumbnailmode_empty_folders_and_files(MMP_TM_MEMBER_T*  pt_this,BOOL b_repaint);
extern INT32 mmp_thumbnailmode_view_update_driver_name(BOOL  b_repaint,BOOL *pb_is_usb);
extern INT32 mmp_thumbnailmode_upd_preview_trans_list(MMP_TM_MEMBER_T* pt_this, UINT8 ui1_idx);
extern INT32 mmp_thumbnailmode_view_dev_num_xng_proc(MMP_TM_MEMBER_T* pt_this);
extern INT32 mmp_thumbnailmode_view_dev_remove_proc(MMP_TM_MEMBER_T* pt_this);
extern INT32 mmp_thumbnailmode_view_dev_mnt_xng_proc(MMP_TM_MEMBER_T* pt_this);
extern INT32 mmp_thumbnailmode_hide_file_info(VOID);
extern VOID  mmp_tm_get_photo_effect(UINT32 *pui4_effect_mode); 
extern UINT32 mmp_tm_rand(VOID); 

#ifdef APP_NET_NEIGHBOR_SUPPORT
extern INT32 mmp_thumbnailmode_pwd_dlg_create(MMP_TM_MEMBER_T* pt_this);
extern INT32 mmp_thumbnailmode_pwd_dlg_destroy(MMP_TM_MEMBER_T* pt_this);
extern BOOL mmp_thumbnailmode_is_need_show_pwd_dlg(MMP_TM_MEMBER_T* pt_this);
#endif
#endif /*_MMP_THUMBNAIL_MODE_H_*/

