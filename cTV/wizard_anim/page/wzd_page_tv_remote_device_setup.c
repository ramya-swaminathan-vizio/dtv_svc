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
#include "c_scc.h"
#include "wizard_anim/wzd.h"
#include "wizard_anim/page/wzd_page_tv_remote_device_setup.h"
#include "wdk/a_vkb.h"
#include "wdk/vkb/vkb.h"
#include "res/wdk/a_vkb_custom.h"
#include "res/wizard_anim/wzd_img.h"
#include "res/wdk/wdk_img.h"
#include "app_util/config/_acfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/isl/a_isl_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/dev_db/a_dev_db_custom.h"
#include "menu2/a_menu.h"
#include "wfrrc_interface.h"
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT 
#include "c_cecm.h"
#include "nav/cec2/nav_cec.h"
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT
#include "wizard_anim/page/wzd_page_tv_setup.h"
#include "wizard/wzd_dbg.h"

#define WZD_DEVICE_BRAND_IDS_MAX_NUM               (255)
#define WZD_DEVICE_SETUP_SHOW_MIG_MAX_NUM          (128)
#define WZD_DEVICE_SETUP_PIC_FLAG                  ("%p")
#define WZD_DEVICE_SETUP_PIC_FLAG_LEN              (3)
#define WZD_DEVICE_SETUP_TYPE_NAME_SUFFIX_LEN      (3)
#define WZD_DEVICE_SETUP_INPUT_SRC_NUM             (16)
#define WZD_DEVICE_SETUP_INPUT_NUM                 (8)
#define DEV_SETUP_DB_NAME_LEN_MAX                  (32)
#define DEV_SETUP_DB_CODESET_LEN_MAX               (5)
#define WZD_DEV_SETUP_TRY_CODESET_MIN_NUM          (2)
#define WZD_DEV_SETUP_DEVICE_CODESET_MAX_NUM       (60)

typedef enum DEVICE_TYPE_SELECT_STATE
{
   DEVICE_TYPE_SELECT_BLURAY_PLAYER = 0,
   DEVICE_TYPE_SELECT_CABLE_BOX,
   DEVICE_TYPE_SELECT_COMPUTER,
   DEVICE_TYPE_SELECT_DVD_PLAYER,
   DEVICE_TYPE_SELECT_DVR,
   DEVICE_TYPE_SELECT_GAME,
   DEVICE_TYPE_SELECT_SATELLITE,
   DEVICE_TYPE_SELECT_VCR,
   DEVICE_TYPE_SELECT_AUDIO_RECIEVER,
   DEVICE_TYPE_SELECT_SOUND_BAR
}DEVICE_TYPE_SELECT_STATE;

/* Enum the box of the select box */
typedef enum _WZD_CHOOSE_BOX_BTN_INDEX_T
{
    WZD_CB_BTN_01 = 0,
    WZD_CB_BTN_02,
    WZD_CB_BTN_03,
    WZD_CB_BTN_04,
    WZD_CB_BTN_05,
    WZD_CB_BTN_06,
    WZD_CB_BTN_07,
    WZD_CB_BTN_08,
    WZD_CB_BTN_09,
    WZD_CB_BTN_10, 
    WZD_CB_BTN_COUNT  /* 10 */
}WZD_CHOOSE_BOX_BTN_INDEX_T;

typedef struct _WZD_CHOOSE_BOX_T
{
    HANDLE_T            h_cb_btn_frm;
    HANDLE_T            h_cb_icon_1;
    HANDLE_T            h_cb_icon_2;
    HANDLE_T            h_cb_text;  
}WZD_CHOOSE_BTN_T;

typedef struct _WZD_SELECT_PAGE_T
{
    HANDLE_T            h_select_frm; 
    HANDLE_T            h_select_desc_txt;
    WZD_CHOOSE_BTN_T    t_sel_box_btn[WZD_CB_BTN_COUNT];
}WZD_SELECT_PAGE_T;

typedef struct _WZD_DLG_PAGE_T
{
    HANDLE_T            h_dlg_frm;
    HANDLE_T            h_dlg_icon;
    HANDLE_T            h_dlg_text; 
    HANDLE_T            h_dlg_timer;
	HANDLE_T			h_amp_plug_dlg_timer;
}WZD_DLG_PAGE_T;

typedef struct _WZD_INPUT_PAGE_T
{
    HANDLE_T            h_input_desc_txt;
    BOOL				b_is_finished_dlg_show;
    BOOL				b_is_full_screen_dlg_show;
	/* Select box */
	HANDLE_T      			h_sb_frm;			/* Select box frame */
	HANDLE_T      			ah_sb_btn[DEV_SETUP_SEL_BOX_BTN_COUNT];
	HANDLE_T      			ah_sb_txt[DEV_SETUP_SEL_BOX_BTN_COUNT];
	HANDLE_T      			ah_sb_icon_1[DEV_SETUP_SEL_BOX_BTN_COUNT];
	HANDLE_T      			ah_sb_icon_2[DEV_SETUP_SEL_BOX_BTN_COUNT];
	HANDLE_T      			h_sb_icon_plus;
}WZD_INPUT_PAGE_T;

typedef struct _WZD_BRAND_PAGE_T
{
    HANDLE_T            h_brand_desc_txt;
    HANDLE_T            h_brand_msg_txt;
    HANDLE_T            h_brand_eb_frm;
    HANDLE_T            h_brand_eb;
    HANDLE_T            h_brand_lb_frm;
    HANDLE_T            h_brand_lb;  
    HANDLE_T            h_brand_lb_hlt_icon;  
    HANDLE_T            h_brand_vkb;
    HANDLE_T            h_brand_eb_clr; /* editbox clear all icon */
}WZD_BRAND_PAGE_T;

typedef struct _WZD_MODEL_PAGE_T
{
    HANDLE_T            h_model_desc_txt;
    HANDLE_T            h_model_msg_txt;
    HANDLE_T            h_model_eb_frm;
    HANDLE_T            h_model_eb;
    HANDLE_T            h_model_lb_frm;
    HANDLE_T            h_model_lb;
    HANDLE_T            h_model_lb_hlt_icon;  
    HANDLE_T            h_model_vkb;
    HANDLE_T            h_model_eb_clr; /* editbox clear all icon */
}WZD_MODEL_PAGE_T;

typedef struct _WZD_CONFIRM_PAGE_T
{
    HANDLE_T            h_code_frm;
    HANDLE_T            h_code_desc_txt;
    HANDLE_T            h_code_htxt;
    HANDLE_T            h_code_htxt_prefix;
    HANDLE_T            h_code_msg_txt;
    HANDLE_T            h_btn_worked;
    HANDLE_T            h_btn_retry;
    HANDLE_T            h_btn_manually;
    HANDLE_T            h_btn_back;
    HANDLE_T            h_btn_skip;
    HANDLE_T            h_manually_dlg;
    HANDLE_T            h_manually_dlg_eb;
}WZD_CONFIRM_PAGE_T;

typedef struct _WZD_DEVICE_PAIR_DLG_PAGE_T
{
    HANDLE_T      h_device_pair_dlg_timer;;
}WZD_DEVICE_PAIR_DLG_PAGE_T;

typedef struct _WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T
{
    DEVICE_SETUP_STATE          e_state;
    DEVICE_SETUP_STATE          e_pre_state;
    ISL_REC_T                   t_isl_rec;
    UINT32                      ui4_sel_box_idx; /* the current focused device type index */
    BOOL                        b_is_db_locked;
    BOOL                        b_is_device_setup_worked;
    BOOL                        b_is_codeset_query_fail;
    BOOL                        b_is_i_do_not_know_mdl_sel;
    BOOL                        b_is_paired[WZD_DEVICE_SETUP_INPUT_NUM][WZD_CB_BTN_COUNT]; /* persist */
    BOOL                        b_is_aduio_paired;                       /* persist */
    BOOL                        b_is_soundbar_paired;                    /* persist */
    UINT32                      ui4_type_paired_count[WZD_CB_BTN_COUNT]; /* persist */ 
	BOOL                        b_is_type_sel[WZD_CB_BTN_COUNT]; /* temp */
	BOOL                        b_is_input_sel[WZD_CB_BTN_COUNT]; /* temp */

    /* here will define the data info for the dev db*/   
    /* dev type info */
    DEV_DB_TYPE_T               t_dev_type[DEV_DB_MAX_DEV_TYPE_CONT];
    UINT32                      ui4_type_sel_idx;
    UINT32                      ui4_type_num;
    
    /* input src info */
    UINT8                       ui1_sel_src_idx;      /* Select source idx */
    UINT8                       aui1_input_src_id[WZD_DEVICE_SETUP_INPUT_SRC_NUM]; /* clean next setup */
    
    /* brand info of this view */  
    DEV_DB_BRMD_T               t_brd_info[DEV_DB_DUL_OP_MAX];
    CHAR                        c_brd_pfx[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    UINT32                      ui4_brd_notify_count;
    UINT32                      ui4_brd_num;
    UINT32                      ui4_brd_sel_idx;

    /* model info of this view */  
    DEV_DB_BRMD_T               t_mdl_info[DEV_DB_DUL_OP_MAX];
    CHAR                        c_mdl_pfx[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    UINT32                      ui4_mdl_notify_count;
    UINT32                      ui4_mdl_num;
    UINT32                      ui4_mdl_sel_idx; 
    
    /* codeset info*/
    DEV_DB_CODESET_T*           pt_codeset;
    DEV_DB_CODESET_LIST_T*      pt_codeset_list;
    UINT8                       ui1_codeset_num;
    UINT8                       ui1_cur_code_pos;  
    BOOL                        b_is_codeset_querying;

    /* device setup info */
    CHAR                        s_type_name[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    CHAR                        s_inp_name[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    CHAR                        s_brd_name[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    CHAR                        s_mdl_name[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    CHAR                        s_codeset[DEV_SETUP_DB_CODESET_LEN_MAX + 1];
    
    /* store Audio Receiver/Amplifier as device type when select Audio Receiver/Amplifier*/
    CHAR                        s_aud_amp_type[DEV_SETUP_DB_NAME_LEN_MAX+1];
    
    /* the glob init info*/
    UINT32                      ui4_nfy_id;
    BOOL                        b_is_notify_reg;
          
    DEVICE_SETUP_ENTER_REASON   e_dev_setup_enter_reason;

    ISO_639_LANG_T 				pre_s639_lang;/*record the pre language*/
    ISO_639_LANG_T 				crn_s639_lang;/*record the current language*/
    SCC_AUD_SPDIF_FMT_T 		e_g_spdif_value;

    BOOL                        b_type_show_checkbox; /* for device type */
    BOOL                        b_input_show_checkbox; /* for device input */
    UINT8                       ui1_input_sel_box_idx; /* the current focused device input index */
    
#ifdef APP_UEI_SPINNER_SUPPORT
	/*on line query spinner*/
	HANDLE_T					h_animation;
	BOOL         				b_animation;
	BOOL						b_is_brd_online_query_start;
	BOOL						b_is_brd_online_query_complete;
	HANDLE_T					h_brd_online_timer;
 	UINT8               		ui1_icon_step;
	HANDLE_T					h_timer;
#endif
    
}WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T;

/*add animation*/
typedef struct _WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T
{
    HANDLE_T            h_anim_handle;                  /* the animation handle which callback to AP */
    WZD_CALLBACK_PARAM  e_param;                        /* private tag data */
    UINT32              ui4_index;
    BOOL                b_used;
} WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T;

/* for move anim of icon2 and txt on the sel box */
typedef enum {
    WZD_DEVICE_SETUP_CALLBACK_PARAM_NOTHING = 0,
    WZD_DEVICE_SETUP_CALLBACK_PARAM_FIRST,
    WZD_DEVICE_SETUP_CALLBACK_PARAM_SECOND,
} WZD_DEVICE_SETUP_CALLBACK_PARAM;



/* device setup diloge frame size */
#define WZD_SCREEN_DLG_FRM_X                 ((BASE_FRM_W - WZD_SCREEN_DLG_FRM_W) / 2)
#define WZD_SCREEN_DLG_FRM_Y                 (((BASE_FRM_H - WZD_SCREEN_DLG_FRM_H ) / 2) - (110 * WZD_UI_RATIO_W))
#define WZD_SCREEN_DLG_FRM_W                 (580 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_FRM_H                 (240 * WZD_UI_RATIO_W)

/* device setup diloge icon size */
#define WZD_SCREEN_DLG_ICON_X                ((WZD_SCREEN_DLG_FRM_W / 2) - (20 * WZD_UI_RATIO_W))
#define WZD_SCREEN_DLG_ICON_Y                (75 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_ICON_W                (40 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_ICON_H                (40 * WZD_UI_RATIO_W)

/* device setup diloge text size */
#define WZD_SCREEN_DLG_TEXT_X                (0)
#define WZD_SCREEN_DLG_TEXT_Y                (WZD_SCREEN_DLG_ICON_Y + WZD_SCREEN_DLG_ICON_H + 10 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_TEXT_W                (WZD_SCREEN_DLG_FRM_W)
#define WZD_SCREEN_DLG_TEXT_H                (100 * WZD_UI_RATIO_W)

/* device setup editbox frame size */
#define WZD_DEVICE_SETUP_EB_FOM_X            (0)
#define WZD_DEVICE_SETUP_EB_FOM_Y            (80 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_EB_FOM_W            (LAYOUT_FRM_W - WZD_VKB_FRAME_X)
#define WZD_DEVICE_SETUP_EB_FOM_H            (120 * WZD_UI_RATIO_W)

/* device setup editbox size */
#define WZD_DEVICE_SETUP_EB_X                (90 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_EB_Y                (10 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_EB_W                (440 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_EB_H                (110 * WZD_UI_RATIO_W)

/* device setup manually dlg editbox size */
#define  WZD_MANUALLY_DLG_EB_X                          ((LAYOUT_FRM_W - WZD_MANUALLY_DLG_EB_W)/2)
#define  WZD_MANUALLY_DLG_EB_Y                          ((LAYOUT_FRM_H - WZD_MANUALLY_DLG_EB_H)/2-90* WZD_UI_RATIO_W)
#define  WZD_MANUALLY_DLG_EB_W                          (368 * WZD_UI_RATIO_W)
#define  WZD_MANUALLY_DLG_EB_H                          (85 * WZD_UI_RATIO_W)

/* device setup listbox frame size */
#define WZD_DEVICE_SETUP_LB_FOM_X            (0)
#define WZD_DEVICE_SETUP_LB_FOM_Y            (200 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_LB_FOM_W            (320 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_LB_FOM_H            (220 * WZD_UI_RATIO_W)

/* device setup listbox size */
#define WZD_DEVICE_SETUP_LB_X                (WZD_DEVICE_SETUP_EB_X + 28 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_LB_Y                (WZD_DEVICE_SETUP_EB_Y + WZD_DEVICE_SETUP_EB_H + 20 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_LB_W                (400 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_LB_H                (303 * WZD_UI_RATIO_W)

/* device setup listbox hlt icon size */
#define WZD_DEVICE_SETUP_LB_HT_ICON_X        (22 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_LB_HT_ICON_Y        (26 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_LB_HT_ICON_W        (354 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_LB_HT_ICON_H        (60 * WZD_UI_RATIO_W)
                                                              
/* editbox inset position */
#define WZD_DEVICE_SETUP_EDIT_BOX_LEFT_INSET       (50 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_EDIT_BOX_RIGHT_INSET      (20 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_EDIT_BOX_TOP_INSET        (8)
#define WZD_DEVICE_SETUP_EDIT_BOX_BOTTOM_INSET     (8)

/* editbox hightlight icon */
#define WZD_DEVICE_SETUP_EDIT_BOX_HL_ICON_X        (50 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_EDIT_BOX_HL_ICON_Y        (40 * WZD_UI_RATIO_H)
#define WZD_DEVICE_SETUP_EDIT_BOX_HL_ICON_W        (8 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_EDIT_BOX_HL_ICON_H        (20 * WZD_UI_RATIO_H)

/* vkb position */
#define WZD_VKB_FRAME_X                    (435 * WZD_UI_RATIO_W)
#define WZD_VKB_FRAME_Y                    (60 * WZD_UI_RATIO_W)

/* select box frame. inside the layout frame */
#define WZD_CB_FRM_X                       (0)
#define WZD_CB_FRM_Y                       (10 * WZD_UI_RATIO_W)
#define WZD_CB_FRM_W                       (BASE_FRM_W - 2 * WZD_CB_FRM_X)
#define WZD_CB_FRM_H                       (640 * WZD_UI_RATIO_W)

#define WZD_CB_BTN_GAP                     (-268 * WZD_UI_RATIO_W)

#define WZD_CB_BTN_Y                       (0)
#define WZD_CB_BTN_W                       (410 * WZD_UI_RATIO_W)
#define WZD_CB_BTN_H                       (386 * WZD_UI_RATIO_W)

/*add animation*/
#define WZD_CB_BTN_SCALE_UP_W              (463 * WZD_UI_RATIO_W)
#define WZD_CB_BTN_SCALE_UP_H              (436 * WZD_UI_RATIO_W)

#define WZD_CB_BTN_SCALE_DOWN_W            (295 * WZD_UI_RATIO_W)
#define WZD_CB_BTN_SCALE_DOWN_H            (278 * WZD_UI_RATIO_W)


/* select box buttons */
#define WZD_CB_BTN_MARGINS                 ((WZD_CB_FRM_W - 5 * WZD_CB_BTN_W - 4 * WZD_CB_BTN_GAP)/2) /* (35 * WZD_UI_RATIO_W) */

#define WZD_CB_BTN_01_X                    (WZD_CB_BTN_MARGINS)
#define WZD_CB_BTN_02_X                    (WZD_CB_BTN_01_X + WZD_CB_BTN_W + WZD_CB_BTN_GAP)
#define WZD_CB_BTN_03_X                    (WZD_CB_BTN_02_X + WZD_CB_BTN_W + WZD_CB_BTN_GAP)
#define WZD_CB_BTN_04_X                    (WZD_CB_BTN_03_X + WZD_CB_BTN_W + WZD_CB_BTN_GAP)
#define WZD_CB_BTN_05_X                    (WZD_CB_BTN_04_X + WZD_CB_BTN_W + WZD_CB_BTN_GAP)
#define WZD_CB_BTN_06_X                    (WZD_CB_BTN_MARGINS)
#define WZD_CB_BTN_07_X                    (WZD_CB_BTN_01_X + WZD_CB_BTN_W + WZD_CB_BTN_GAP)
#define WZD_CB_BTN_08_X                    (WZD_CB_BTN_02_X + WZD_CB_BTN_W + WZD_CB_BTN_GAP)
#define WZD_CB_BTN_09_X                    (WZD_CB_BTN_03_X + WZD_CB_BTN_W + WZD_CB_BTN_GAP)
#define WZD_CB_BTN_10_X                    (WZD_CB_BTN_04_X + WZD_CB_BTN_W + WZD_CB_BTN_GAP)

#define WZD_CB_BTN_LINE1_Y                 WZD_CB_BTN_Y - 20 * WZD_UI_RATIO_W
#define WZD_CB_BTN_LINE2_Y                 WZD_CB_BTN_Y + WZD_CB_BTN_H - 265 * WZD_UI_RATIO_W

#ifdef APP_UEI_SPINNER_SUPPORT
/* animation icon position */
#define WZD_DEVICE_SETUP_SPINNER_ICON_X          ((1280-44)/2 * WZD_UI_RATIO_W)/*578*/
#define WZD_DEVICE_SETUP_SPINNER_ICON_Y          (150 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_SPINNER_ICON_W          (44 * WZD_UI_RATIO_W)
#define WZD_DEVICE_SETUP_SPINNER_ICON_H          (44 * WZD_UI_RATIO_W)
#endif

/* select box buttons layout */
#define  WZD_CB_BTN_GET_RECTS()                                                                                                     \
{                                                                                                                                           \
    {WZD_CB_BTN_01_X, WZD_CB_BTN_LINE1_Y, WZD_CB_BTN_01_X + WZD_CB_BTN_W, WZD_CB_BTN_LINE1_Y + WZD_CB_BTN_H}, \
    {WZD_CB_BTN_02_X, WZD_CB_BTN_LINE1_Y, WZD_CB_BTN_02_X + WZD_CB_BTN_W, WZD_CB_BTN_LINE1_Y + WZD_CB_BTN_H}, \
    {WZD_CB_BTN_03_X, WZD_CB_BTN_LINE1_Y, WZD_CB_BTN_03_X + WZD_CB_BTN_W, WZD_CB_BTN_LINE1_Y + WZD_CB_BTN_H}, \
    {WZD_CB_BTN_04_X, WZD_CB_BTN_LINE1_Y, WZD_CB_BTN_04_X + WZD_CB_BTN_W, WZD_CB_BTN_LINE1_Y + WZD_CB_BTN_H}, \
    {WZD_CB_BTN_05_X, WZD_CB_BTN_LINE1_Y, WZD_CB_BTN_05_X + WZD_CB_BTN_W, WZD_CB_BTN_LINE1_Y + WZD_CB_BTN_H}, \
    {WZD_CB_BTN_06_X, WZD_CB_BTN_LINE2_Y, WZD_CB_BTN_06_X + WZD_CB_BTN_W, WZD_CB_BTN_LINE2_Y + WZD_CB_BTN_H}, \
    {WZD_CB_BTN_07_X, WZD_CB_BTN_LINE2_Y, WZD_CB_BTN_07_X + WZD_CB_BTN_W, WZD_CB_BTN_LINE2_Y + WZD_CB_BTN_H}, \
    {WZD_CB_BTN_08_X, WZD_CB_BTN_LINE2_Y, WZD_CB_BTN_08_X + WZD_CB_BTN_W, WZD_CB_BTN_LINE2_Y + WZD_CB_BTN_H}, \
    {WZD_CB_BTN_09_X, WZD_CB_BTN_LINE2_Y, WZD_CB_BTN_09_X + WZD_CB_BTN_W, WZD_CB_BTN_LINE2_Y + WZD_CB_BTN_H}, \
    {WZD_CB_BTN_10_X, WZD_CB_BTN_LINE2_Y, WZD_CB_BTN_10_X + WZD_CB_BTN_W, WZD_CB_BTN_LINE2_Y + WZD_CB_BTN_H}, \
}

/* for move animation -- input page */
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_X     WZD_SEL_BOX_BTN_ICON_1_X
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_Y     WZD_SEL_BOX_BTN_ICON_1_Y + 40 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_W     WZD_SEL_BOX_BTN_ICON_1_W + 20 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_H     WZD_SEL_BOX_BTN_ICON_1_H

#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_X     WZD_SEL_BOX_BTN_ICON_2_X - 5 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_Y     WZD_SEL_BOX_BTN_ICON_2_Y
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_W     WZD_SEL_BOX_BTN_ICON_2_W + 20 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_H     WZD_SEL_BOX_BTN_ICON_2_H

#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_X        WZD_SEL_BOX_BTN_TXT_X
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_Y        WZD_SEL_BOX_BTN_TXT_Y - 40 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_W        WZD_SEL_BOX_BTN_TXT_W
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_H        WZD_SEL_BOX_BTN_TXT_H

#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_MOVE_DOWN_X        WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_X
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_MOVE_DOWN_Y        WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_Y + 20 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_MOVE_DOWN_X           WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_X
#define WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_MOVE_DOWN_Y            WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_Y + 20 * WZD_UI_RATIO_W

/* for move animation -- select device type page */
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_X     -32 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_Y     135 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_W     WZD_CB_BTN_W + 78 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_H     40 * WZD_UI_RATIO_W

#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_X     -32 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_Y     170 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_W     WZD_CB_BTN_W + 70 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_H     40 * WZD_UI_RATIO_W

#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_X        33 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_Y        190 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_W        343 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_H        80 * WZD_UI_RATIO_W

#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_MOVE_DOWN_X        WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_X
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_MOVE_DOWN_Y        WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_Y + 10 * WZD_UI_RATIO_W
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_MOVE_DOWN_X           WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_X
#define WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_MOVE_DOWN_Y           WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_Y + 10 * WZD_UI_RATIO_W

#define WZD_DEVICE_SETUP_TYPE_MOVE_ANIM_TOTAL_STEPS         4
#define WZD_DEVICE_SETUP_TYPE_MOVE_ANIM_FRAME_INTERVAL      50

#define WZD_DEVICE_SETUP_INPUT_MOVE_ANIM_TOTAL_STEPS        6
#define WZD_DEVICE_SETUP_INPUT_MOVE_ANIM_FRAME_INTERVAL     50

static WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T    t_g_tv_remote_device_setup;
static WZD_DLG_PAGE_T                         t_g_device_setup_finished_dlg_page;
static WZD_SELECT_PAGE_T                      t_g_device_setup_select_page;
static WZD_INPUT_PAGE_T                       t_g_device_setup_input_page;
static WZD_BRAND_PAGE_T                       t_g_device_setup_brand_page;
static WZD_MODEL_PAGE_T                       t_g_device_setup_model_page;
static WZD_CONFIRM_PAGE_T                     t_g_device_setup_confirm_page;
static WZD_DEVICE_PAIR_DLG_PAGE_T             t_g_device_setup_device_pair_dlg_page;

static TV_DEV_SETUP_SEL_BOX_BTN_INDEX_T	e_sb_pre_focused_box = DEV_SETUP_SEL_BOX_BTN_01;
static WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T at_anim_cb_get_focus_data_type;
static WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T at_anim_cb_lose_focus_data_type;

static WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T      at_anim_cb_icon_data;
static WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T      at_anim_cb_txt_data;


static INT32 _wzd_page_tv_remote_device_setup_type_sel_box_reset_img(VOID);
 
/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_select_show(BOOL b_repaint);
static INT32 _wzd_page_tv_remote_device_setup_input_show(BOOL b_repaint);
static INT32 _wzd_page_tv_remote_device_setup_brand_show(BOOL b_repaint);
static INT32 _wzd_page_tv_remote_device_setup_model_show(BOOL b_repaint);
static INT32 _wzd_page_tv_remote_device_setup_update_by_state(BOOL b_repaint);
static INT32 _wzd_page_tv_remote_device_setup_code_text_connect (UTF16_T* code_w2s_prefix, UTF16_T* code_w2s);
static INT32 _wzd_page_tv_remote_device_setup_set_page_text(HANDLE_T h_parent, UTF16_T* pw2s_text);
static INT32 _wzd_page_tv_remote_device_setup_text_it_work_btn (const UTF16_T*  suffix_w2s, UTF16_T* ps_w2s,UINT32 ui4_len);
static INT32 _wzd_page_tv_remote_device_setup_init(VOID);
static INT32 _wzd_page_tv_remote_device_setup_set_sel_box_theme (UINT8 ui1_rec_num);
static INT32 _wzd_page_tv_remote_device_setup_get_device_paired_info (VOID);
static UINT8 _wzd_page_tv_remote_device_setup_input_src_id_map (UINT8 ui1_input_id);
static INT32 _wzd_page_tv_remote_device_setup_full_dlg_set_content(VOID);
static VOID  _wzd_page_tv_remote_device_setup_finished_btn_dlg_show_nfy_fct(HANDLE_T h_timer, VOID* pv_tag);
static VOID  _wzd_page_tv_remote_device_setup_timer_paired_show_dialog_nfy_fct(HANDLE_T h_timer, VOID* pv_tag);
static INT32 _wzd_page_tv_remote_device_setup_set_codeset(CHAR* c_codeset);
static INT32 _wzd_page_tv_remote_device_setup_manual_enter_code(VOID);
static INT32 _wzd_page_tv_remote_device_setup_confirm_manually_dlg_create (VOID);
static INT32 _wzd_page_tv_remote_device_setup_set_device_info(VOID);
static INT32 _wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_initial(UINT32 ui4_sel_box_idx);

#ifdef APP_UEI_SPINNER_SUPPORT
static INT32 _wzd_page_tv_remote_timer_icon_update(HANDLE_T   h_widget);
static VOID _wzd_page_tv_remote_animation_timer_notify_fct(HANDLE_T  pt_tm_handle,
                                     VOID*     pv_tag);
#endif

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_device_setup_sel_box_move_cond_cb_handler
 *
 * Description: update the state after the animiation is end
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_device_setup_sel_box_move_cond_cb_handler(
    VOID*               pv_data,
    SIZE_T              z_data_size)
{
    WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T*    pt_anim_cb_data = NULL;
    WZD_DEVICE_SETUP_CALLBACK_PARAM          param = WZD_DEVICE_SETUP_CALLBACK_PARAM_NOTHING;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*     pt_this = &t_g_tv_remote_device_setup;
	UINT8								     ui1_rec_num = 0;
    UINT8                                    status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;
    WZD_DEVICE_PAIR_DLG_PAGE_T*              pt_paired_dlg_page = &t_g_device_setup_device_pair_dlg_page;

    do
    {
        /* Check input arguments */
        if ((NULL == pv_data) ||
            (z_data_size != sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T)))
        {
            break;
        }

        pt_anim_cb_data = (WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T*)pv_data;

        if (NULL_HANDLE == pt_anim_cb_data->h_anim_handle)
        {
            break;
        }

        param = pt_anim_cb_data->e_param;
        
        c_wgl_set_alpha(pt_anim_cb_data->h_anim_handle, 255);

        /* Stop animation */
        if (WZD_DEVICE_SETUP_CALLBACK_PARAM_SECOND == param)
        {
            c_thread_delay(200);

            if (DEVICE_SETUP_CHOOSE_DEVICE == pt_this->e_state)
            {
                if (pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_AUDIO_RECIEVER || pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_SOUND_BAR)
                {
                    pt_this->e_pre_state = DEVICE_SETUP_CHOOSE_DEVICE;
                    pt_this->e_state = DEVICE_SETUP_SELECT_BRAND;
                }
                else
                {
                    pt_this->e_pre_state = DEVICE_SETUP_CHOOSE_DEVICE;
                    pt_this->e_state = DEVICE_SETUP_SELECT_INPUT;
                }

                _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
            }
            else if (DEVICE_SETUP_SELECT_INPUT== pt_this->e_state)
            {
                a_cfg_custom_get_wifi_remote_pair_status(&status);
                a_isl_get_num_rec(&ui1_rec_num);
                if (((DEVICE_TYPE_SELECT_CABLE_BOX== pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SATELLITE== pt_this->ui4_type_sel_idx)) &&
                     (pt_this->ui1_sel_src_idx == (ui1_rec_num-1)))
            	{
    				wzd_page_tv_setup_enter_from_tv_remote_device_setup_rf(pt_this->ui4_type_sel_idx);
            	}
    			else
    			{
                    if (pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP && status != WIFI_REMOTE_PAIR_STATUS_PAIRED)
                    {    
                        /* lose focus when the full dialog display */
                        wzd_view_sel_box_lose_focus(pt_this->ui1_input_sel_box_idx, FALSE);
                        
                        /* Set dialog */    
                        _wzd_page_tv_remote_device_setup_full_dlg_set_content();
                        wzd_view_full_screen_dlg_show(FALSE);
                        t_g_device_setup_input_page.b_is_full_screen_dlg_show = TRUE;
        				
        				/* set device info */
        				_wzd_page_tv_remote_device_setup_set_device_info();  
        				DBG_INFO( ("[Ln: %d] set device info!!! \n", __LINE__)); 

                        c_timer_start(pt_paired_dlg_page->h_device_pair_dlg_timer, 
                                      5000,
                                      X_TIMER_FLAG_ONCE,
                                      _wzd_page_tv_remote_device_setup_timer_paired_show_dialog_nfy_fct,
                                      NULL);
        				
                    }
                    else 
                    {
                        pt_this->e_pre_state = DEVICE_SETUP_SELECT_INPUT;
                        pt_this->e_state = DEVICE_SETUP_SELECT_BRAND;
                        _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
                    }
                }
            }
            
        }
        else
        {
            /* do nothing */
        }

        a_wzd_anim_end(pt_anim_cb_data->h_anim_handle);
        
        /* clean data */
        if (pt_anim_cb_data->h_anim_handle == at_anim_cb_icon_data.h_anim_handle)
        {
            at_anim_cb_icon_data.h_anim_handle = NULL_HANDLE;
            at_anim_cb_icon_data.e_param = WZD_DEVICE_SETUP_CALLBACK_PARAM_NOTHING;
        }
        else if (pt_anim_cb_data->h_anim_handle == at_anim_cb_txt_data.h_anim_handle)
        {
            at_anim_cb_txt_data.h_anim_handle = NULL_HANDLE;
            at_anim_cb_txt_data.e_param = WZD_DEVICE_SETUP_CALLBACK_PARAM_NOTHING;
        }
        
    } while(0);
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_device_setup_sel_box_move_cb_fct
 *
 * Description: for select signal type and cable device type
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_device_setup_sel_box_move_cb_fct(
    HANDLE_T            h_widget,
    UINT16              ui2_anim_type,
    WGL_ANIM_COND_INF_T t_anim_cond_inf,
    VOID*               pv_tag)
{
    if (h_widget == NULL_HANDLE)
    {
        return WZDR_OK;
    }
    
    if (_ANIM_TOTAL_END(&t_anim_cond_inf))
    {
        DBG_INFO( ("[WZD_DEVICE_SETUP] ANIM_TOTAL_END Line@%d.\n", __LINE__));

        /* Async invoke callback handler function */        
        wzd_async_invoke(
                _wzd_page_tv_device_setup_sel_box_move_cond_cb_handler, 
                pv_tag, 
                sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T), 
                FALSE);
    }

    return WZDR_OK;   
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_device_setup_type_set_checkmark
 *
 * Description: set checkmark(icon1) and move icon2 and text when select the box.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_device_setup_type_set_checkmark (VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;
    WZD_SELECT_PAGE_T*                      pt_select_page = &t_g_device_setup_select_page;
    WGL_IMG_INFO_T 					        t_img_info = {0};
    GL_RECT_T      					        t_rect = {0};
	WGL_HIMG_TPL_T 					        h_checkmark_icon = NULL_HANDLE;
    ANIM_DATA_MOVE_T                        t_anim_data_icon;
    ANIM_DATA_MOVE_T                        t_anim_data_txt;
    HANDLE_T       					        h_icon1 = NULL_HANDLE;
    HANDLE_T       					        h_icon2 = NULL_HANDLE;
	HANDLE_T    					        h_text = NULL_HANDLE;

    c_memset(&t_anim_data_icon, 0, sizeof(ANIM_DATA_MOVE_T));
    c_memset(&t_anim_data_txt, 0, sizeof(ANIM_DATA_MOVE_T));

    h_checkmark_icon = h_g_wzd_img_checkmark_green_small;
    h_icon1 = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_icon_1;
    /* move icon1(checkmark) position */
    RET_ON_ERR (c_wgl_do_cmd(h_icon1,
                      WGL_CMD_ICON_SET_ALIGN,
                      WGL_PACK(WGL_AS_CENTER_CENTER),
                      NULL));

	SET_RECT_BY_SIZE (&t_rect,
                      WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_X,
                      WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_Y,
                      WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_W,
                      WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_H);

    RET_ON_ERR (c_wgl_move(h_icon1,
                      &t_rect,
                      WGL_NO_AUTO_REPAINT));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_enable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;

    RET_ON_ERR (c_wgl_do_cmd(h_icon1,
                      WGL_CMD_GL_SET_IMAGE,
                      WGL_PACK(WGL_IMG_FG),
                      WGL_PACK(&t_img_info)));
    
    RET_ON_ERR (c_wgl_set_visibility (h_icon1, WGL_SW_NORMAL));
    RET_ON_ERR (c_wgl_repaint (h_icon1, NULL, TRUE));

    /* start icon2 move animation */
    h_icon2 = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_icon_2;

    t_anim_data_icon.ui2_total_steps = WZD_DEVICE_SETUP_TYPE_MOVE_ANIM_TOTAL_STEPS;
    t_anim_data_icon.ui2_frame_interval = WZD_DEVICE_SETUP_TYPE_MOVE_ANIM_FRAME_INTERVAL;

    t_anim_data_icon.i2_start_x = WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_X;
    t_anim_data_icon.i2_start_y = WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_Y;
    t_anim_data_icon.i2_end_x   = WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_MOVE_DOWN_X;
    t_anim_data_icon.i2_end_y   = WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_MOVE_DOWN_Y;

    
    /* set h_icon2 move down callback data */
    c_memset(&at_anim_cb_icon_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
    at_anim_cb_icon_data.h_anim_handle = h_icon2;
    at_anim_cb_icon_data.e_param = WZD_DEVICE_SETUP_CALLBACK_PARAM_FIRST;

    a_wzd_anim_set_cb(
               h_icon2,
               _wzd_page_tv_device_setup_sel_box_move_cb_fct,
               (void *)&at_anim_cb_icon_data);

    a_wzd_anim_move_ex(h_icon2, &t_anim_data_icon, TRUE);

    /* start text move animation */
    h_text = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_text;

    t_anim_data_txt.ui2_total_steps = WZD_DEVICE_SETUP_TYPE_MOVE_ANIM_TOTAL_STEPS;
    t_anim_data_txt.ui2_frame_interval = WZD_DEVICE_SETUP_TYPE_MOVE_ANIM_FRAME_INTERVAL;

    t_anim_data_txt.i2_start_x = WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_X;
    t_anim_data_txt.i2_start_y = WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_Y;
    t_anim_data_txt.i2_end_x   = WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_MOVE_DOWN_X;
    t_anim_data_txt.i2_end_y   = WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_MOVE_DOWN_Y;

    /* set h_text move down callback data */
    c_memset(&at_anim_cb_txt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
    at_anim_cb_txt_data.h_anim_handle = h_text;
    at_anim_cb_txt_data.e_param = WZD_DEVICE_SETUP_CALLBACK_PARAM_SECOND;

    /* set h_text move down callback */
    a_wzd_anim_set_cb(
               h_text,
               _wzd_page_tv_device_setup_sel_box_move_cb_fct,
               (void *)&at_anim_cb_txt_data);

    a_wzd_anim_move_ex(h_text, &t_anim_data_txt, TRUE);

    return WZDR_OK;;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_device_setup_type_update_checkmark
 *
 * Description: update the position of checkmark(icon1)/icon2/txt on the select box
 *              when get the focus.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_device_setup_type_update_checkmark(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;
    WZD_SELECT_PAGE_T*                      pt_select_page = &t_g_device_setup_select_page;
    WGL_IMG_INFO_T 					        t_img_info = {0};
    GL_RECT_T      					        t_rect_icon = {0};
    GL_RECT_T      					        t_rect_txt = {0};
	WGL_HIMG_TPL_T 					        h_checkmark_icon = NULL_HANDLE;
    HANDLE_T       					        h_icon1 = NULL_HANDLE;
    HANDLE_T       					        h_icon2 = NULL_HANDLE;
	HANDLE_T    					        h_text = NULL_HANDLE;
    BOOL         					        b_sel_status = FALSE;
    BOOL         					        b_sel_curr_same = FALSE;
    UINT8                                   ui1_sel_box_idx = 0;
    INT32                                   i4_ret = WZDR_OK;
    
    if (!pt_this->b_type_show_checkbox)
    {
        return 0;
    }

    for (ui1_sel_box_idx = 0; ui1_sel_box_idx < WZD_CB_BTN_COUNT; ui1_sel_box_idx++)
    {
        h_icon1 = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_icon_1;
        
        if (pt_this->b_is_type_sel[ui1_sel_box_idx])
        {
            b_sel_status = TRUE;
            if (pt_this->ui4_sel_box_idx == ui1_sel_box_idx)
            {
                b_sel_curr_same = TRUE;
                break;
            }
        }
        if(b_sel_curr_same)
        {
            break;
        }
    }

    if (b_sel_status)
    {
        if (b_sel_curr_same)
        {  
            h_checkmark_icon = h_g_wzd_img_checkmark_green_small;
        }
        else
        {
            pt_this->b_type_show_checkbox = FALSE;
            h_checkmark_icon = NULL_HANDLE;
        }
    }
    else
    {
        pt_this->b_type_show_checkbox = FALSE;
        pt_this->ui4_sel_box_idx = 0;
        h_checkmark_icon = NULL_HANDLE;
    }

    /*update sel box icon2 and text position */
    if (b_sel_status)
    {
        if (pt_this->b_type_show_checkbox)
        {
            /* move icon2 position */
            h_icon2 = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_icon_2;
            SET_RECT_BY_SIZE(&t_rect_icon,
                                WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_MOVE_DOWN_X,
                                WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_MOVE_DOWN_Y,
                                WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_W,
                                WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_H);
            RET_ON_ERR (c_wgl_move(h_icon2,
                                   &t_rect_icon,
                                   WGL_NO_AUTO_REPAINT));
            
            /* move txt position */
            h_text = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_text;
            SET_RECT_BY_SIZE(&t_rect_txt,
                             WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_MOVE_DOWN_X,
                             WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_MOVE_DOWN_Y,
                             WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_W,
                             WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_H);
            
            RET_ON_ERR (c_wgl_move(h_text,
                                   &t_rect_txt,
                                   WGL_NO_AUTO_REPAINT));
        }
        else
        {
            /* move icon2 position */
            h_icon2 = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_icon_2;
            SET_RECT_BY_SIZE(&t_rect_icon,
                            WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_X,
                            WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_Y,
                            WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_W,
                            WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_H);
            RET_ON_ERR (c_wgl_move(h_icon2,
                                   &t_rect_icon,
                                   WGL_NO_AUTO_REPAINT));
            
            /* move txt position */
            h_text = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_text;
            SET_RECT_BY_SIZE(&t_rect_txt,
                             WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_X,
                             WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_Y,
                             WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_W,
                             WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_H);
            
            RET_ON_ERR (c_wgl_move(h_text,
                                   &t_rect_txt,
                                   WGL_NO_AUTO_REPAINT));
        }
        
    }

    /* update checkmark icon position*/ 
    if (pt_this->b_type_show_checkbox)
    {
        h_icon1 = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_icon_1;
        SET_RECT_BY_SIZE(&t_rect_icon,
                        WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_X,
                        WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_Y,
                        WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_W,
                        WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_1_H);
    
        RET_ON_ERR (c_wgl_move(h_icon1,
                           &t_rect_icon,
                           WGL_NO_AUTO_REPAINT));
    
    }
    
    RET_ON_ERR (c_wgl_do_cmd(h_icon1,
                  WGL_CMD_ICON_SET_ALIGN,
                  WGL_PACK(WGL_AS_CENTER_CENTER),
                  NULL));
    
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_disable   = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;

    i4_ret = c_wgl_do_cmd(h_icon1,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_FG),
                           WGL_PACK(&t_img_info));                 
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_device_setup_input_set_checkmark
 *
 * Description: set checkmark(icon1) and move icon2 and text when select the box.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_device_setup_input_set_checkmark (VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;
    WGL_IMG_INFO_T 					        t_img_info = {0};
    GL_RECT_T      					        t_rect = {0};
	WGL_HIMG_TPL_T 					        h_checkmark_icon = NULL_HANDLE;
    ANIM_DATA_MOVE_T                        t_anim_data_icon;
    ANIM_DATA_MOVE_T                        t_anim_data_txt;
    HANDLE_T       					        h_icon1 = NULL_HANDLE;
    HANDLE_T       					        h_icon2 = NULL_HANDLE;
	HANDLE_T    					        h_text = NULL_HANDLE;

    c_memset(&t_anim_data_icon, 0, sizeof(ANIM_DATA_MOVE_T));
    c_memset(&t_anim_data_txt, 0, sizeof(ANIM_DATA_MOVE_T));

    h_checkmark_icon = h_g_wzd_img_checkmark_green_large;

    /* move icon1(checkmark) position */
    h_icon1 = wzd_view_sel_box_get_icon_1_handle(pt_this->ui1_input_sel_box_idx);

    RET_ON_ERR (c_wgl_do_cmd(h_icon1,
                      WGL_CMD_ICON_SET_ALIGN,
                      WGL_PACK(WGL_AS_CENTER_CENTER),
                      NULL));

	SET_RECT_BY_SIZE (&t_rect,
                      WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_X,
                      WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_Y,
                      WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_W,
                      WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_H);

    RET_ON_ERR (c_wgl_move(h_icon1,
                      &t_rect,
                      WGL_NO_AUTO_REPAINT));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_enable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;

    RET_ON_ERR (c_wgl_do_cmd(h_icon1,
                      WGL_CMD_GL_SET_IMAGE,
                      WGL_PACK(WGL_IMG_FG),
                      WGL_PACK(&t_img_info)));
    
    RET_ON_ERR (c_wgl_set_visibility (h_icon1, WGL_SW_NORMAL));
    RET_ON_ERR (c_wgl_repaint (h_icon1, NULL, TRUE));

    /* start icon2 move animation */
    h_icon2 = wzd_view_sel_box_get_icon_2_handle(pt_this->ui1_input_sel_box_idx);

    t_anim_data_icon.ui2_total_steps = WZD_DEVICE_SETUP_INPUT_MOVE_ANIM_TOTAL_STEPS;
    t_anim_data_icon.ui2_frame_interval = WZD_DEVICE_SETUP_INPUT_MOVE_ANIM_FRAME_INTERVAL;

    t_anim_data_icon.i2_start_x = WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_X;
    t_anim_data_icon.i2_start_y = WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_Y;
    t_anim_data_icon.i2_end_x   = WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_MOVE_DOWN_X;
    t_anim_data_icon.i2_end_y   = WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_MOVE_DOWN_Y;

    
    /* set h_icon2 move down callback data */
    c_memset(&at_anim_cb_icon_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
    at_anim_cb_icon_data.h_anim_handle = h_icon2;
    at_anim_cb_icon_data.e_param = WZD_DEVICE_SETUP_CALLBACK_PARAM_FIRST;

    a_wzd_anim_set_cb(
               h_icon2,
               _wzd_page_tv_device_setup_sel_box_move_cb_fct,
               (void *)&at_anim_cb_icon_data);

    a_wzd_anim_move_ex(h_icon2, &t_anim_data_icon, TRUE);

    /* start text move animation */
    h_text = wzd_view_sel_box_get_txt_handle(pt_this->ui1_input_sel_box_idx);

    t_anim_data_txt.ui2_total_steps = WZD_DEVICE_SETUP_INPUT_MOVE_ANIM_TOTAL_STEPS;
    t_anim_data_txt.ui2_frame_interval = WZD_DEVICE_SETUP_INPUT_MOVE_ANIM_FRAME_INTERVAL;

    t_anim_data_txt.i2_start_x = WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_X;
    t_anim_data_txt.i2_start_y = WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_Y;
    t_anim_data_txt.i2_end_x   = WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_MOVE_DOWN_X;
    t_anim_data_txt.i2_end_y   = WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_MOVE_DOWN_Y;

    /* set h_text move down callback data */
    c_memset(&at_anim_cb_txt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
    at_anim_cb_txt_data.h_anim_handle = h_text;
    at_anim_cb_txt_data.e_param = WZD_DEVICE_SETUP_CALLBACK_PARAM_SECOND;

    /* set h_text move down callback */
    a_wzd_anim_set_cb(
               h_text,
               _wzd_page_tv_device_setup_sel_box_move_cb_fct,
               (void *)&at_anim_cb_txt_data);

    a_wzd_anim_move_ex(h_text, &t_anim_data_txt, TRUE);

    return WZDR_OK;;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_device_setup_input_update_checkmark
 *
 * Description: update the position of checkmark(icon1)/icon2/txt on the select box
 *              when get the focus.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_device_setup_input_update_checkmark(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;
    WGL_IMG_INFO_T 					        t_img_info = {0};
    GL_RECT_T      					        t_rect_icon = {0};
    GL_RECT_T      					        t_rect_txt = {0};
	WGL_HIMG_TPL_T 					        h_checkmark_icon = NULL_HANDLE;
    HANDLE_T       					        h_icon1 = NULL_HANDLE;
    HANDLE_T       					        h_icon2 = NULL_HANDLE;
	HANDLE_T    					        h_text = NULL_HANDLE;
    BOOL         					        b_sel_status = FALSE;
    BOOL         					        b_sel_curr_same = FALSE;
    UINT8                                   ui1_sel_box_idx = 0;
    INT32                                   i4_ret = WZDR_OK;
    
    if (!pt_this->b_input_show_checkbox)
    {
        return 0;
    }

    for (ui1_sel_box_idx = 0; ui1_sel_box_idx < WZD_CB_BTN_COUNT; ui1_sel_box_idx++)
    {
        h_icon1 = wzd_view_sel_box_get_icon_1_handle(ui1_sel_box_idx);
        
        if (pt_this->b_is_input_sel[ui1_sel_box_idx])
        {
            b_sel_status = TRUE;
            if (pt_this->ui1_input_sel_box_idx == ui1_sel_box_idx)
            {
                b_sel_curr_same = TRUE;
                break;
            }
        }
        if(b_sel_curr_same)
        {
            break;
        }
    }

    if (b_sel_status)
    {
        if (b_sel_curr_same)
        {  
            h_checkmark_icon = h_g_wzd_img_checkmark_green_large;
        }
        else
        {
            pt_this->b_input_show_checkbox = FALSE;
            h_checkmark_icon = NULL_HANDLE;
        }
    }
    else
    {
        pt_this->b_input_show_checkbox = FALSE;
        pt_this->ui1_input_sel_box_idx = 0;
        h_checkmark_icon = NULL_HANDLE;
    }

    /*update sel box icon2 and text position */
    if (b_sel_status)
    {
        if (pt_this->b_input_show_checkbox)
        {
            /* move icon2 position */
            h_icon2 = wzd_view_sel_box_get_icon_2_handle(pt_this->ui1_input_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_icon,
                                WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_MOVE_DOWN_X,
                                WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_MOVE_DOWN_Y,
                                WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_W,
                                WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_H);
            RET_ON_ERR (c_wgl_move(h_icon2,
                                   &t_rect_icon,
                                   WGL_NO_AUTO_REPAINT));
            
            /* move txt position */
            h_text = wzd_view_sel_box_get_txt_handle(pt_this->ui1_input_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_txt,
                             WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_MOVE_DOWN_X,
                             WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_MOVE_DOWN_Y,
                             WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_W,
                             WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_H);
            
            RET_ON_ERR (c_wgl_move(h_text,
                                   &t_rect_txt,
                                   WGL_NO_AUTO_REPAINT));
        }
        else
        {
            /* move icon2 position */
            h_icon2 = wzd_view_sel_box_get_icon_2_handle(pt_this->ui1_input_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_icon,
                            WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_X,
                            WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_Y,
                            WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_W,
                            WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_H);
            RET_ON_ERR (c_wgl_move(h_icon2,
                                   &t_rect_icon,
                                   WGL_NO_AUTO_REPAINT));
            
            /* move txt position */
            h_text = wzd_view_sel_box_get_txt_handle(pt_this->ui1_input_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_txt,
                             WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_X,
                             WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_Y,
                             WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_W,
                             WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_H);
            
            RET_ON_ERR (c_wgl_move(h_text,
                                   &t_rect_txt,
                                   WGL_NO_AUTO_REPAINT));
        }
        
    }

    /* update checkmark icon position*/ 
    if (pt_this->b_input_show_checkbox)
    {
        h_icon1 = wzd_view_sel_box_get_icon_1_handle(pt_this->ui1_input_sel_box_idx);
        SET_RECT_BY_SIZE(&t_rect_icon,
                        WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_X,
                        WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_Y,
                        WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_W,
                        WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_1_H);
    
        RET_ON_ERR (c_wgl_move(h_icon1,
                           &t_rect_icon,
                           WGL_NO_AUTO_REPAINT));
    
    }
    
    RET_ON_ERR (c_wgl_do_cmd(h_icon1,
                  WGL_CMD_ICON_SET_ALIGN,
                  WGL_PACK(WGL_AS_CENTER_CENTER),
                  NULL));
    
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_disable   = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;

    i4_ret = c_wgl_do_cmd(h_icon1,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_FG),
                           WGL_PACK(&t_img_info));                 
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_set_frm_bg_img
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_set_frm_bg_img(
    HANDLE_T            h_widget,
    WGL_HIMG_TPL_T      h_bg_img)
{
    WGL_IMG_INFO_T      		t_img_info;
    INT32               		i4_ret = WZDR_OK;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_bg_img;
    t_img_info.u_img_data.t_standard.t_disable   = h_bg_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_bg_img;

    i4_ret = c_wgl_do_cmd (h_widget,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK (WGL_IMG_BK), /* background image */
                           WGL_PACK (&t_img_info));
                           
    RET_ON_ERR (i4_ret);

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_scale_cond_cb_handler
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_scale_cond_cb_handler(
    VOID*               pv_data,
    SIZE_T              z_data_size)
{
    WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T*   pt_anim_cb_data = NULL;
    WZD_CALLBACK_PARAM                      param = WZD_CALLBACK_PARAM_NOTHING;

    do
    {
        /* Check input arguments */
        if ((NULL == pv_data) ||
            (z_data_size != sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T)))
        {
            break;
        }

        pt_anim_cb_data = (WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T*)pv_data;

        if (NULL_HANDLE == pt_anim_cb_data->h_anim_handle)
        {
            break;
        }

        param = pt_anim_cb_data->e_param;

        DBG_INFO( ("[WZD][DEVICE SETUP]ANIM end:0x%x, param:%d, index:%d\n",
                    pt_anim_cb_data->h_anim_handle, 
                    param, 
                    pt_anim_cb_data->ui4_index));

        /* Stop animation */
        if (WZD_CALLBACK_PARAM_SCALE_DOWN == param)
        {
            /*change image for the lose focus box*/
            if((pt_anim_cb_data->ui4_index >= WZD_CB_BTN_01)&&(pt_anim_cb_data->ui4_index<=WZD_CB_BTN_05))
            {
                _wzd_page_tv_remote_device_setup_set_frm_bg_img(pt_anim_cb_data->h_anim_handle, h_g_wzd_img_selectbox_small);
            }
            else if((pt_anim_cb_data->ui4_index >= WZD_CB_BTN_06)&&(pt_anim_cb_data->ui4_index<=WZD_CB_BTN_10))
            {
                _wzd_page_tv_remote_device_setup_set_frm_bg_img(pt_anim_cb_data->h_anim_handle, h_g_wzd_img_selectbox_small_1);
            }
            else
            {
                DBG_ERROR(("[WZD][DEVICE SETUP] pt_anim_cb_data->ui4_index (%d) overflow\n", pt_anim_cb_data->ui4_index));
                break;
            }
            _wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_initial(pt_anim_cb_data->ui4_index);
            c_wgl_float(pt_anim_cb_data->h_anim_handle, FALSE, WGL_NO_AUTO_REPAINT);
        }
        else if (WZD_CALLBACK_PARAM_SCALE_UP == param)
        {
            /*change image for the get focus box*/
            _wzd_page_tv_remote_device_setup_set_frm_bg_img(pt_anim_cb_data->h_anim_handle, h_g_wzd_img_selectbox_small_hlt);
            c_wgl_float(pt_anim_cb_data->h_anim_handle, TRUE, WGL_NO_AUTO_REPAINT);
            c_wgl_set_focus(pt_anim_cb_data->h_anim_handle, WGL_NO_AUTO_REPAINT);
        }
        else
        {
            /* do nothing */
        }

        a_wzd_anim_end(pt_anim_cb_data->h_anim_handle);

        /* clean data */
        if (pt_anim_cb_data->h_anim_handle == at_anim_cb_get_focus_data_type.h_anim_handle)
        {
            at_anim_cb_get_focus_data_type.h_anim_handle = NULL_HANDLE;
            at_anim_cb_get_focus_data_type.e_param = WZD_CALLBACK_PARAM_NOTHING;
            at_anim_cb_get_focus_data_type.ui4_index = 0;
            at_anim_cb_get_focus_data_type.b_used = FALSE;
        }
        else if(pt_anim_cb_data->h_anim_handle == at_anim_cb_lose_focus_data_type.h_anim_handle)
        {
            at_anim_cb_lose_focus_data_type.h_anim_handle = NULL_HANDLE;
            at_anim_cb_lose_focus_data_type.e_param = WZD_CALLBACK_PARAM_NOTHING;
            at_anim_cb_lose_focus_data_type.ui4_index = 0;
            at_anim_cb_lose_focus_data_type.b_used = FALSE;
        }
        
    } while(0);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct(
    HANDLE_T            h_widget,
    UINT16              ui2_anim_type,
    WGL_ANIM_COND_INF_T t_anim_cond_inf,
    VOID*               pv_tag)
{
    if (h_widget == NULL_HANDLE)
    {
        return WZDR_OK;
    }
    
    if (_ANIM_TOTAL_END(&t_anim_cond_inf))
    {
        DBG_INFO( ("[WZD][DEVICE SETUP] ANIM_TOTAL_END Line@%d.\n", __LINE__));

        /* Async invoke callback handler function */        
        wzd_async_invoke(
                _wzd_page_tv_remote_device_setup_scale_cond_cb_handler, 
                pv_tag, 
                sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T), 
                FALSE);
    }

    return WZDR_OK;   
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_sel_box_get_focus_scale_up
 *
 * Description: scale up the get foucs box.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/

static INT32 _wzd_page_tv_remote_device_setup_sel_box_get_focus_scale_up(HANDLE_T h_widget)
{
	ANIM_DATA_SCALE_T*                        pt_anim_data_scale = NULL;
    
    DBG_API( ("\n####%s(%d)\n",__FUNCTION__,__LINE__));
    pt_anim_data_scale = c_mem_alloc(sizeof (ANIM_DATA_SCALE_T));
    
    if(NULL == pt_anim_data_scale)
    {
        return WZDR_OK;
    }
    /* Clear animation data */
    c_memset (pt_anim_data_scale, 0, sizeof (ANIM_DATA_SCALE_T));

    do
    {   
        pt_anim_data_scale->ui2_total_steps = WZD_ANIM_SCALE_TOTAL_STEPS;
        pt_anim_data_scale->ui2_frame_interval = 50;
        pt_anim_data_scale->ui4_start_tick = 0;

        pt_anim_data_scale->ui8_start_w = WZD_CB_BTN_W;
        pt_anim_data_scale->ui8_start_h = WZD_CB_BTN_H;
        pt_anim_data_scale->ui8_end_w = WZD_CB_BTN_SCALE_UP_W;
        pt_anim_data_scale->ui8_end_h = WZD_CB_BTN_SCALE_UP_H;

    } while(0);

    a_wzd_anim_scale(h_widget, pt_anim_data_scale, TRUE);

    if(NULL != pt_anim_data_scale)
    {
        c_mem_free(pt_anim_data_scale);
        pt_anim_data_scale = NULL;
    }

    return WZDR_OK;    
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_sel_box_lose_focus_scale_down
 *
 * Description: scale down the lose focus box.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/

static INT32 _wzd_page_tv_remote_device_setup_sel_box_lose_focus_scale_down(HANDLE_T h_widget)
{
    
	ANIM_DATA_SCALE_T*                        pt_anim_data_scale = NULL;

    DBG_API( ("\n####%s(%d)\n",__FUNCTION__,__LINE__));
    pt_anim_data_scale = c_mem_alloc(sizeof (ANIM_DATA_SCALE_T));
    
    if(NULL == pt_anim_data_scale)
    {
        return WZDR_OK;
    }

    /* Clear animation data */
    c_memset (pt_anim_data_scale, 0, sizeof (ANIM_DATA_SCALE_T));

    do
    {   
        pt_anim_data_scale->ui2_total_steps = WZD_ANIM_SCALE_TOTAL_STEPS;
        pt_anim_data_scale->ui2_frame_interval = 50;
        pt_anim_data_scale->ui4_start_tick = 1;

        pt_anim_data_scale->ui8_start_w = WZD_CB_BTN_W;
        pt_anim_data_scale->ui8_start_h = WZD_CB_BTN_H;
        pt_anim_data_scale->ui8_end_w = WZD_CB_BTN_SCALE_DOWN_W;
        pt_anim_data_scale->ui8_end_h = WZD_CB_BTN_SCALE_DOWN_H;

    } while(0);
    
    a_wzd_anim_scale(h_widget, pt_anim_data_scale, TRUE);

    if(NULL != pt_anim_data_scale)
    {
        c_mem_free(pt_anim_data_scale);
        pt_anim_data_scale = NULL;
    }

    return WZDR_OK;    
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_finished_dlg_icon_create
 *
 * Description: This function creates the dialog icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_finished_dlg_icon_create (VOID)
{
    GL_RECT_T           t_rect  = {0};
    WGL_INSET_T         t_inset = {0};
    WZD_DLG_PAGE_T*     pt_finished_dlg_page = &t_g_device_setup_finished_dlg_page;
    
    SET_RECT_BY_SIZE (&t_rect,
                      WZD_SCREEN_DLG_ICON_X,
                      WZD_SCREEN_DLG_ICON_Y,
                      WZD_SCREEN_DLG_ICON_W,
                      WZD_SCREEN_DLG_ICON_H);

    RET_ON_ERR (c_wgl_create_widget(pt_finished_dlg_page->h_dlg_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &pt_finished_dlg_page->h_dlg_icon));

    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_icon,
                              WGL_CMD_ICON_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set icon alignment */
    RET_ON_ERR (c_wgl_do_cmd(pt_finished_dlg_page->h_dlg_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_BOTTOM,
                          NULL));

    /* set visibility, default hidden */
    RET_ON_ERR (c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_icon, WGL_SW_HIDE));
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_finished_dlg_text_create
 *
 * Description: This function creates the full screen dialog text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_finished_dlg_text_create(VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    CHAR*                       s_font_name = wzd_view_get_font_name();
    WZD_DLG_PAGE_T*             pt_finished_dlg_page = &t_g_device_setup_finished_dlg_page;

    SET_RECT_BY_SIZE (& t_rect,
                      WZD_SCREEN_DLG_TEXT_X,
                      WZD_SCREEN_DLG_TEXT_Y,
                      WZD_SCREEN_DLG_TEXT_W,
                      WZD_SCREEN_DLG_TEXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (pt_finished_dlg_page->h_dlg_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MULTILINE |
                                             WGL_STL_TEXT_MAX_512  |
                                             WGL_STL_TEXT_MAX_DIS_5_LINE |
                                             WZD_WIDGET_STYLE),
                                     NULL,
                                     &pt_finished_dlg_page->h_dlg_text));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_text,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_text,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_text,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_CENTER_TOP),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_text,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) 0),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt);

    RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_text,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_text, WGL_SW_HIDE));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name:  _wzd_page_tv_remote_device_setup_dlg_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_dlg_create (HANDLE_T parent)
{
    WZD_DLG_PAGE_T*     pt_finished_dlg_page = &t_g_device_setup_finished_dlg_page;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_color_info;
    
    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      WZD_SCREEN_DLG_FRM_X,
                      WZD_SCREEN_DLG_FRM_Y,
                      WZD_SCREEN_DLG_FRM_W,
                      WZD_SCREEN_DLG_FRM_H);
  
    /* create widget */
    RET_ON_ERR(c_wgl_create_widget (parent,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  NULL,
                                  240,
                                  (VOID*) WZD_WIDGET_STYLE,
                                  0,
                                  &pt_finished_dlg_page->h_dlg_frm));
    
    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_dialog;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_dialog;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_dialog;

    RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK),
                              WGL_PACK (& t_img_info)));

    /* create icon */
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_finished_dlg_icon_create());

    /* create text */
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_finished_dlg_text_create());

    /* create dlg show timer */
    RET_ON_ERR (c_timer_create(&pt_finished_dlg_page->h_dlg_timer));
	
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
	/* create amp plug dlg hide timer */
    RET_ON_ERR (c_timer_create (&pt_finished_dlg_page->h_amp_plug_dlg_timer));
#endif
#endif
#endif

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_frm, WGL_SW_HIDE));
    
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_finished_dlg_set_icon
 *
 * Description: The function set image template to the finished dialog icon.
 *
 *
 *
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_finished_dlg_set_icon (WGL_HIMG_TPL_T h_dlg_icon)
{
    WGL_IMG_INFO_T      t_img_info;
    WZD_DLG_PAGE_T*     pt_finished_dlg_page = &t_g_device_setup_finished_dlg_page;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_dlg_icon;
    t_img_info.u_img_data.t_standard.t_disable = h_dlg_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_dlg_icon;

    RET_ON_ERR (c_wgl_do_cmd(pt_finished_dlg_page->h_dlg_icon,
                            WGL_CMD_GL_SET_IMAGE,
                            (VOID*)WGL_IMG_FG,
                            (VOID*)&t_img_info));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_finished_dlg_set_text
 *
 * Description: The function set the full screen dialog text.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_finished_dlg_set_text (UTF16_T* pw2s_text)
{
    WZD_DLG_PAGE_T*     pt_finished_dlg_page = &t_g_device_setup_finished_dlg_page;

    RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_text,
                              WGL_CMD_TEXT_SET_TEXT,
                              WGL_PACK (pw2s_text),
                              WGL_PACK ((UINT16)0xFFFF)));
    return  WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_set_dlg_visibility
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_set_dlg_visibility (VOID)
{
    WZD_DLG_PAGE_T* pt_finished_dlg_page = &t_g_device_setup_finished_dlg_page;
    
    RET_ON_ERR (c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_icon, WGL_SW_NORMAL));

    RET_ON_ERR (c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_text, WGL_SW_NORMAL));

    RET_ON_ERR (c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_frm, WGL_SW_NORMAL));

    RET_ON_ERR (c_wgl_insert (pt_finished_dlg_page->h_dlg_frm,
                              NULL_HANDLE,
                              WGL_INSERT_TOPMOST,
                              WGL_NO_AUTO_REPAINT));
                              
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_init());                       

    RET_ON_ERR (c_wgl_set_focus(pt_finished_dlg_page->h_dlg_frm, FALSE));
    
    return  WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_finished_dlg_hide
 *
 * Description: The function hide the full screen dialog.
 *
 * Inputs: 
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_finished_dlg_hide (VOID)
{
    WZD_DLG_PAGE_T*     pt_finished_dlg_page = &t_g_device_setup_finished_dlg_page;

    t_g_device_setup_input_page.b_is_finished_dlg_show = FALSE;
    return c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_frm, WGL_SW_HIDE);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_device_type_page_back_resume
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_select_device_page_back_resume(VOID)
{   
    if (!a_wzd_is_resume_from_menu_setup())
    {
        wzd_page_goto(WZD_PAGE_NAVI_PREV_PAGE);
    }
	else
	{
		a_wzd_exit();
	}

    return  WZDR_OK; 
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_input_src_page_back_resume
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_input_page_back_resume(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;

    c_memset(pt_this->aui1_input_src_id, 0, sizeof(pt_this->aui1_input_src_id));                       
                     
    /* back prev page */
    if (pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP) 
    {
        pt_this->e_dev_setup_enter_reason = DEVICE_SETUP_ENTER_REASON_NONE;
        wzd_page_tv_setup_enter_from_tv_remote_device_setup_input();
    }
    else
    {   
        pt_this->e_pre_state = DEVICE_SETUP_SELECT_INPUT;
        pt_this->e_state = DEVICE_SETUP_CHOOSE_DEVICE;
        _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
    } 

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_brand_page_back_resume
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_brand_page_back_resume(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this       = &t_g_tv_remote_device_setup;
    WZD_BRAND_PAGE_T*                    pt_brand_page = &t_g_device_setup_brand_page;
    BOOL                                 b_is_visible  = FALSE;
    
    /* resume origin input src */
    if (pt_this->ui4_type_sel_idx != DEVICE_TYPE_SELECT_AUDIO_RECIEVER 
        || pt_this->ui4_type_sel_idx != DEVICE_TYPE_SELECT_SOUND_BAR)
    {
        a_tv_change_input_src_by_rec(wzd_get_crnt_svctx(), 
                                     SVCTX_STRM_MODE_AS_LAST,
                                     &pt_this->t_isl_rec, 
                                     NULL);
    }  

    /* clean brand editbox info */
    RET_ON_ERR(a_vkb_do_cmd(pt_brand_page->h_brand_vkb,
                            VKB_CMD_CLEAR_TEXT,
                            (VOID*)NULL,
                            (VOID*)NULL));                        

    /* clean brand listbox info */     
    RET_ON_ERR(c_wgl_do_cmd(pt_brand_page->h_brand_lb, 
                            WGL_CMD_LB_DEL_ALL, 
                            NULL, 
                            NULL));  
                            
    RET_ON_ERR(c_wgl_get_visibility(pt_brand_page->h_brand_lb_frm, &b_is_visible)); 
    if ( b_is_visible == TRUE )
    {
        RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
    } 
    
    /* set brand page next button disable */
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));

    /* hide vkb */
    a_vkb_set_visibility(pt_brand_page->h_brand_vkb, FALSE);

    /* back prev page */
    if ((DEVICE_TYPE_SELECT_AUDIO_RECIEVER == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SOUND_BAR == pt_this->ui4_type_sel_idx))
    {
        pt_this->e_pre_state = DEVICE_SETUP_SELECT_BRAND;
        pt_this->e_state = DEVICE_SETUP_CHOOSE_DEVICE;
    }
    else
    {   
        pt_this->e_pre_state = DEVICE_SETUP_SELECT_BRAND;
        pt_this->e_state = DEVICE_SETUP_SELECT_INPUT;
    }
    _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
    
    return  WZDR_OK;    
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_model_page_back_resume
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_model_page_back_resume(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this       = &t_g_tv_remote_device_setup;
    WZD_MODEL_PAGE_T*                    pt_model_page = &t_g_device_setup_model_page;
    BOOL                                 b_is_visible  = FALSE;

    /* clean model editbox info */
    RET_ON_ERR(a_vkb_do_cmd(pt_model_page->h_model_vkb,
                            VKB_CMD_CLEAR_TEXT,
                            (VOID*)NULL,
                            (VOID*)NULL));

    /* clean model listbox info */
    RET_ON_ERR(c_wgl_do_cmd(pt_model_page->h_model_lb, 
                            WGL_CMD_LB_DEL_ALL, 
                            NULL, 
                            NULL));  
                        
    RET_ON_ERR(c_wgl_get_visibility(pt_model_page->h_model_lb_frm, &b_is_visible)); 
    if ( b_is_visible == TRUE )
    {
        RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));
    } 

    /* hide vkb */
    a_vkb_set_visibility(pt_model_page->h_model_vkb, FALSE);

    /* back prev page */
    pt_this->e_pre_state = DEVICE_SETUP_SELECT_MODEL;
    pt_this->e_state = DEVICE_SETUP_SELECT_BRAND;
    _wzd_page_tv_remote_device_setup_update_by_state(FALSE);

    /* set brand page next button enable */
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
    RET_ON_ERR (wzd_view_main_frm_repaint());
    
    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_page_back_resume
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_page_back_resume(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;

	if (wzd_view_full_screen_dlg_is_show())
	{
		return WZDR_OK;
	}

    /* back prev page */
    if ((pt_this->b_is_db_locked)||((pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_SOUND_BAR)&&(c_strcmp(pt_this->s_brd_name, "VIZIO")==0)))
    {
        pt_this->e_pre_state = DEVICE_SETUP_CODE_CONFIRM;
        pt_this->e_state = DEVICE_SETUP_SELECT_BRAND;
    }
    else
    {
        pt_this->e_pre_state = DEVICE_SETUP_CODE_CONFIRM;
        pt_this->e_state = DEVICE_SETUP_SELECT_MODEL;
    }
    _wzd_page_tv_remote_device_setup_update_by_state(FALSE);
    
    /* set model page next button */
    if (pt_this->b_is_i_do_not_know_mdl_sel == TRUE)
    {
        pt_this->b_is_i_do_not_know_mdl_sel = FALSE;
    }
    else
    {
        RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
    }
    RET_ON_ERR (wzd_view_main_frm_repaint());
     
    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_reset_type_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_reset_type_info(VOID)
{
    UINT32  ui4_idx   = 0;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    
    for (ui4_idx = 0; ui4_idx < DEV_DB_MAX_DEV_TYPE_CONT; ui4_idx++)
    {
        c_memset(&(pt_this->t_dev_type[ui4_idx]), 0, sizeof (DEV_DB_TYPE_T));
        
        pt_this->t_dev_type[ui4_idx].i4_deva_src_idx  = -1; /* invaild value*/
        pt_this->t_dev_type[ui4_idx].i4_devb_src_idx  = -1;
    }

    pt_this->ui4_type_num = 0;
    
    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_reset_device_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_reset_device_info(VOID)
{
    WZD_BRAND_PAGE_T*                     pt_brand_page = &t_g_device_setup_brand_page;
    WZD_MODEL_PAGE_T*                     pt_model_page = &t_g_device_setup_model_page;
    BOOL                                  b_is_visible;

    /* clean brand info */
    RET_ON_ERR (a_vkb_do_cmd(pt_brand_page->h_brand_vkb,
                          VKB_CMD_CLEAR_TEXT,
                          (VOID*)NULL,
                          (VOID*)NULL));

    c_wgl_repaint (pt_brand_page->h_brand_eb_frm, NULL, TRUE);

    RET_ON_ERR (c_wgl_get_visibility(pt_brand_page->h_brand_lb_frm, &b_is_visible)); 
    if ( b_is_visible == TRUE )
    {
        RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
        c_wgl_repaint (pt_brand_page->h_brand_lb_frm, NULL, TRUE);
    } 

    /* clean model info */
    RET_ON_ERR (a_vkb_do_cmd(pt_model_page->h_model_vkb,
                          VKB_CMD_CLEAR_TEXT,
                          (VOID*)NULL,
                          (VOID*)NULL));

    c_wgl_repaint (pt_model_page->h_model_eb_frm, NULL, TRUE);

    RET_ON_ERR (c_wgl_get_visibility(pt_model_page->h_model_lb_frm, &b_is_visible)); 
    if ( b_is_visible == TRUE )
    {
        RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));
        c_wgl_repaint (pt_model_page->h_model_lb_frm, NULL, TRUE);
    } 

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_reset_brand_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_reset_brand_info(VOID)
{
    UINT32          ui4_idx   = 0;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;

    for (ui4_idx = 0; ui4_idx < DEV_DB_DUL_OP_MAX; ui4_idx ++)
    {
        /* init the brand info */
        c_memset(&(pt_this->t_brd_info[ui4_idx]),0,sizeof (DEV_DB_BRMD_T));
        pt_this->t_brd_info[ui4_idx].i4_local1_idx  = -1;
        pt_this->t_brd_info[ui4_idx].i4_online1_idx = -1;
        pt_this->t_brd_info[ui4_idx].i4_local2_idx  = -1;
        pt_this->t_brd_info[ui4_idx].i4_online2_idx = -1;
    }

    for (ui4_idx = 0; ui4_idx < DEV_SETUP_DB_NAME_LEN_MAX + 1; ui4_idx ++)
    {
        pt_this->c_brd_pfx[ui4_idx] = '\0';
    }
    
    /* init the brand num */    
    pt_this->ui4_brd_notify_count       = 0;
    pt_this->ui4_brd_num                = 0;

    c_memset(pt_this->s_brd_name, 0, sizeof(pt_this->s_brd_name));
    
#ifdef APP_UEI_SPINNER_SUPPORT
	pt_this->b_is_brd_online_query_start = FALSE;
	pt_this->b_is_brd_online_query_complete = FALSE;
#endif

    return  WZDR_OK; 
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_reset_model_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_reset_model_info(VOID)
{
    UINT32                               ui4_idx = 0;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    
    for (ui4_idx = 0; ui4_idx < DEV_DB_DUL_OP_MAX; ui4_idx ++)
    {
        /* init the model info*/
        c_memset(&(pt_this->t_mdl_info[ui4_idx]),0,sizeof (DEV_DB_BRMD_T));
        pt_this->t_mdl_info[ui4_idx].i4_local1_idx  = -1;
        pt_this->t_mdl_info[ui4_idx].i4_online1_idx = -1;
        pt_this->t_mdl_info[ui4_idx].i4_local2_idx  = -1;
        pt_this->t_mdl_info[ui4_idx].i4_online2_idx = -1;
    }

    for (ui4_idx = 0; ui4_idx < DEV_SETUP_DB_NAME_LEN_MAX + 1; ui4_idx ++)
    {
        pt_this->c_mdl_pfx[ui4_idx] = '\0';
    }

    /* init the model num*/
    pt_this->ui4_mdl_notify_count       = 0;
    pt_this->ui4_mdl_num                = 0;
    pt_this->ui4_mdl_sel_idx            = 0;

    c_memset(pt_this->s_mdl_name, 0, sizeof(pt_this->s_mdl_name));
    
    return  WZDR_OK;   
}

/*-----------------------------------------------------------------------------
 * Name:_wzd_page_tv_remote_device_setup_codeset_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_codeset_info(VOID)
{
    UINT32                                  ui4_idx = 0;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;

    for (ui4_idx = 0; ui4_idx < 6; ui4_idx ++)
    {
        pt_this->s_codeset[ui4_idx] = '\0';
    }

    pt_this->ui1_cur_code_pos = 0;
    pt_this->ui1_codeset_num = 0;

    return  WZDR_OK;   
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_init
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_init(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this = &t_g_tv_remote_device_setup;

    pt_this->b_is_codeset_query_fail = FALSE;
    pt_this->b_is_i_do_not_know_mdl_sel = FALSE;

    c_memset(pt_this->aui1_input_src_id, 0, sizeof(pt_this->aui1_input_src_id));
    c_memset(pt_this->s_type_name, 0, DEV_SETUP_DB_NAME_LEN_MAX + 1);
    c_memset(pt_this->s_inp_name, 0, DEV_SETUP_DB_NAME_LEN_MAX + 1);
    c_memset(pt_this->s_brd_name, 0, DEV_SETUP_DB_NAME_LEN_MAX + 1);
    c_memset(pt_this->s_mdl_name, 0, DEV_SETUP_DB_NAME_LEN_MAX + 1);
    c_memset(pt_this->s_codeset, 0, DEV_SETUP_DB_CODESET_LEN_MAX + 1);
    c_memset(pt_this->s_aud_amp_type, 0, DEV_SETUP_DB_NAME_LEN_MAX + 1);

    RET_ON_ERR( _wzd_page_tv_remote_device_setup_reset_type_info() );
    RET_ON_ERR( _wzd_page_tv_remote_device_setup_reset_brand_info() );
    RET_ON_ERR( _wzd_page_tv_remote_device_setup_reset_model_info() );
    RET_ON_ERR( _wzd_page_tv_remote_device_setup_codeset_info() );

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
* Name: _wzd_page_tv_remote_device_setup_codeset_update
*
* Description:
*
* Inputs:
*
* Outputs:
*
* Returns:
*
----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_codeset_update(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    BOOL  b_db_status = FALSE;
    
    pt_this->ui1_codeset_num = 0;
    pt_this->ui1_cur_code_pos = 0;
    c_strncpy(pt_this->s_codeset, "", 5);

    /* here only deal with the dev setup*/
    DEV_DB_LOCK_CHECK_COND_T e_check_cond = DEV_DB_LOCK_CHECK_COND_CODESET;
    
    RET_ON_ERR(a_dev_db_check_lock_info( e_check_cond, &b_db_status ));
                              
    RET_ON_ERR(a_dev_db_update_codeset(pt_this->ui4_type_sel_idx,
                            pt_this->t_dev_type[pt_this->ui4_type_sel_idx],
                            pt_this->t_brd_info[pt_this->ui4_brd_sel_idx],
                            pt_this->t_mdl_info[pt_this->ui4_mdl_sel_idx],
                            pt_this->s_brd_name,
                            pt_this->s_mdl_name));

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_change_input
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_change_input(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    UINT8  ui1_idx = 0;
	UINT8								 ui1_rec_num 		= 0;
    
    if (pt_this->ui1_sel_src_idx > (WZD_DEVICE_SETUP_INPUT_SRC_NUM - 1) ) /*Klocwork*/
    {
        return WZDR_OK;
    }

    ui1_idx = pt_this->aui1_input_src_id[pt_this->ui1_sel_src_idx];

    if (ui1_idx == (UINT8) - 1 || ui1_idx >= 16)
    {
        return WZDR_FAIL;
    }    
    
    /* stop 3rd process */
    a_tv_net_send_cmd("\n:dtv_app_mtk,dtv_app_mtk,:resume=wizard\n");

	a_isl_get_num_rec(&ui1_rec_num);
	if (((DEVICE_TYPE_SELECT_CABLE_BOX == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SATELLITE == pt_this->ui4_type_sel_idx)) &&
		(pt_this->ui1_sel_src_idx == (ui1_rec_num-1)))
	{
		/*change to tv source*/
		DBG_INFO( ("\n####%s(%d)before change to tv\n",__FUNCTION__,__LINE__));
		a_tv_change_input_src(wzd_get_crnt_svctx(),
	                                   SVCTX_STRM_MODE_AS_LAST,
	                                   0,
	                                   NULL);

		DBG_INFO( ("\n####%s(%d)after change to tv\n",__FUNCTION__,__LINE__));
	}
	else
	{
	    a_tv_change_input_src(wzd_get_crnt_svctx(),
	                                   SVCTX_STRM_MODE_AS_LAST,
	                                   ui1_idx,
	                                   NULL);
	}
                                   
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
* Name: _wzd_page_tv_remote_device_setup_update_codeset
*
* Description: 
*
* Inputs:
*
* Outputs:
*
* Returns:
*
----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_update_codeset(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*      pt_this = &t_g_tv_remote_device_setup;
    INT32 i4_ret = WZDR_OK;

    if (( pt_this->ui1_sel_src_idx > (WZD_DEVICE_SETUP_INPUT_SRC_NUM - 1))
         && (pt_this->ui1_sel_src_idx != 0xFF))  /*Klocwork*/
    {
        return WZDR_OK;
    }

    if (pt_this->b_is_codeset_querying)
    {
        DBG_INFO( ("[Ln: %d] pt_this->b_is_codeset_querying = %d\n", __LINE__, pt_this->b_is_codeset_querying));
        return WZDR_OK;
    }
    else
    {       
        _wzd_page_tv_remote_device_setup_codeset_info();
        i4_ret = _wzd_page_tv_remote_device_setup_codeset_update();
        if  (WZDR_OK != i4_ret)
        {           
            pt_this->b_is_codeset_querying = FALSE; 
            DBG_INFO( ("[Ln: %d] _wzd_page_tv_remote_device_setup_codeset_update(), i4_ret = %d\n", __LINE__, i4_ret));
            return i4_ret;
        }
        else
        {
            pt_this->b_is_codeset_querying = TRUE;
        }
     }   
     
     return WZDR_OK;
}

/*----------------------------------------------------------------------------
* Name: _wzd_page_tv_remote_device_setup_update_codeset_with_brand(VOID)
*
* Description:
*
* Inputs:
*
* Outputs:
*
* Returns:
*
----------------------------------------------------------------------------*/

static INT32 _wzd_page_tv_remote_device_setup_update_codeset_with_brand (VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*      pt_this = &t_g_tv_remote_device_setup;
    INT32 i4_ret = WZDR_OK;
    
    if (c_strcmp(pt_this->s_brd_name, "") == 0)
    {
        DBG_ERROR( ("[Ln: %d] brand info have not select, please select it first! pt_this->s_brd_name = %s\n", __LINE__, pt_this->s_brd_name));
        return WZDR_FAIL;
    }

    DBG_INFO( ("[Ln: %d] ui4_type_sel_idx = %d, dev_type = %s, brd_name = %s, s_brd_name = %s\n", __LINE__, 
                              pt_this->ui4_type_sel_idx, 
                              pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, 
                              pt_this->t_brd_info[pt_this->ui4_brd_sel_idx].s_src_name,
                              pt_this->s_brd_name));
                              
    pt_this->e_pre_state = DEVICE_SETUP_SELECT_BRAND;                          
    pt_this->e_state = DEVICE_SETUP_CODE_CONFIRM;                         
    i4_ret = a_dev_db_update_codeset_with_brand(pt_this->ui4_type_sel_idx,
                                                pt_this->t_dev_type[pt_this->ui4_type_sel_idx],
                                                pt_this->t_brd_info[pt_this->ui4_brd_sel_idx],
                                                pt_this->s_brd_name);
    if (i4_ret != WZDR_OK)
    {
        DBG_ERROR( ("[Ln: %d] a_dev_db_update_codeset_with_brand(), i4_ret = %d\n", __LINE__, i4_ret));
        return WZDR_FAIL;
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_brand_drop_down_lb_update
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_brand_drop_down_lb_update(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    WZD_BRAND_PAGE_T*                    pt_brand_page = &t_g_device_setup_brand_page;
    BOOL                                 b_is_visible;
    UTF16_T                              str_prefix[DEV_SETUP_DB_NAME_LEN_MAX + 1]= L"";
    INT32                                i4_ret = WZDR_OK;

    RET_ON_ERR (_wzd_page_tv_remote_device_setup_reset_brand_info());
    
#ifdef APP_UEI_SPINNER_SUPPORT
	/*hide the spinner before update brand info(insert new query task) if the spinner is show*/
	c_wgl_set_visibility(pt_this->h_animation, WGL_SW_HIDE);
	DBG_INFO( ("\n####%s(%d)HIDE animation lb update\n",__FUNCTION__,__LINE__));
#endif		
       
    RET_ON_ERR (c_wgl_do_cmd(pt_brand_page->h_brand_lb, 
                             WGL_CMD_LB_DEL_ALL, 
                             NULL, 
                             NULL));
    
    RET_ON_ERR (a_vkb_do_cmd (pt_brand_page->h_brand_vkb,
                           VKB_CMD_GET_EB_CONTENT,
                          (VOID*) str_prefix,
                          (VOID*) (UINT32) DEV_SETUP_DB_NAME_LEN_MAX));                       

    c_uc_w2s_to_ps(str_prefix, pt_this->c_brd_pfx, DEV_SETUP_DB_NAME_LEN_MAX);

    if (c_strcmp(pt_this->c_brd_pfx, "") == 0)
    {
        pt_this->ui4_brd_sel_idx = 0xFFFFFFFF;
        c_memset(pt_this->s_brd_name, 0, DEV_SETUP_DB_NAME_LEN_MAX + 1);
        RET_ON_ERR(c_wgl_get_visibility(pt_brand_page->h_brand_lb_frm, &b_is_visible)); 
        if ( b_is_visible == TRUE )
        {
           RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
           RET_ON_ERR (c_wgl_repaint (pt_brand_page->h_brand_lb_frm, NULL, TRUE));
        } 
        return WZDR_OK;
    }
    
    DBG_INFO( ("[Ln: %d][BRAND UPDATE] ui4_type_sel_idx = %d, dev_type = %s, str_prefix = %s\n", __LINE__, 
                              pt_this->ui4_type_sel_idx, 
                              pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, 
                              pt_this->c_brd_pfx));

    i4_ret = a_dev_db_update_brand_info(pt_this->ui4_type_sel_idx, 
                                        pt_this->t_dev_type[pt_this->ui4_type_sel_idx], 
                                        pt_this->c_brd_pfx);
    if (i4_ret != 0)
    {
        DBG_ERROR( ("[Ln: %d] a_dev_db_update_brand_info fail! i4_ret = %d\n", __LINE__, i4_ret));
        return WZDR_FAIL;
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_brand_drop_down_lb_set_text_update
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_brand_drop_down_lb_set_text_update(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    WZD_BRAND_PAGE_T*                    pt_brand_page = &t_g_device_setup_brand_page;
    UINT16                               ui2_idx = 0;
    INT32                                i4_ret = WZDR_OK;
    UTF16_T                              s_src_name[DEV_SETUP_DB_NAME_LEN_MAX + 1]= L"";
    
    RET_ON_ERR (c_wgl_do_cmd(pt_brand_page->h_brand_lb, 
                          WGL_CMD_LB_DEL_ALL, 
                          NULL, 
                          NULL));
    
    i4_ret = a_dev_db_get_brand_list(pt_this->t_brd_info,
                                     &pt_this->ui4_brd_num,
                                     pt_this->c_brd_pfx);
    if (i4_ret != 0)
    {
        DBG_ERROR( ("[Ln: %d] a_dev_db_get_brand_list()fail!!! i4_ret = %d\n", __LINE__, i4_ret));   
        return WZDR_FAIL;
    }

    if ((pt_this->ui4_brd_num == 0) || (pt_this->ui4_brd_num >= DEV_DB_DUL_OP_MAX))
    {
        DBG_INFO(  ("[Ln: %d] the brand num value is invalid! get_brand_number = %d\n", __LINE__, pt_this->ui4_brd_num));
        return WZDR_OK;
    }
    
    i4_ret = a_dev_db_resort_bm_list_with_str(pt_this->t_brd_info,
                                              pt_this->ui4_brd_num,
                                              "Vizio");    
    if (i4_ret != 0)
    {
        DBG_INFO( ("[Ln: %d] a_dev_db_resort_bm_list_with_str() fail!!! i4_ret = %d\n", __LINE__, i4_ret));   
        return WZDR_FAIL;
    }
    
    /* set listbox item number */
    RET_ON_ERR (c_wgl_do_cmd(pt_brand_page->h_brand_lb,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK(pt_this->ui4_brd_num),
                          NULL));

    /* Iterate all the brands */
    while (ui2_idx < pt_this->ui4_brd_num)
    {
        DBG_INFO( ("[Ln: %d]ui4_brd_num = %d  s_src_name[%d]= [%s]\n", __LINE__, pt_this->ui4_brd_num, ui2_idx, pt_this->t_brd_info[ui2_idx].s_src_name));
        c_uc_ps_to_w2s(pt_this->t_brd_info[ui2_idx].s_src_name, s_src_name, DEV_SETUP_DB_NAME_LEN_MAX);
        /* set element text */
        c_wgl_do_cmd(pt_brand_page->h_brand_lb,
                     WGL_CMD_LB_SET_ITEM_TEXT,
                     WGL_PACK_2((ui2_idx), 0),
                     WGL_PACK(s_src_name));
        ui2_idx++;
    }

    RET_ON_ERR (c_wgl_do_cmd(pt_brand_page->h_brand_lb,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(0),
                          NULL));

    RET_ON_ERR (c_wgl_do_cmd(pt_brand_page->h_brand_lb,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(0),
                          WGL_PACK(0)));
  
    RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_NORMAL));
    RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb, WGL_SW_NORMAL));
    RET_ON_ERR (c_wgl_repaint (pt_brand_page->h_brand_lb_frm, NULL, TRUE));
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setupselect_brd_eb_set_text
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setupselect_brd_eb_set_text(UINT32 ui4_brd_sel_idx)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    WZD_BRAND_PAGE_T* pt_brand_page = &t_g_device_setup_brand_page;
    UTF16_T w2s_brand_name[DEV_SETUP_DB_NAME_LEN_MAX + 1] = {0};
    
    if (ui4_brd_sel_idx > (WZD_DEVICE_BRAND_IDS_MAX_NUM - 1))  
    {  
        DBG_ERROR( ("[Ln: %d]  brd_sel_idx = %d\n", __LINE__, ui4_brd_sel_idx));
        return WZDR_FAIL;
    }

    RET_ON_ERR (a_vkb_do_cmd(pt_brand_page->h_brand_vkb,
                          VKB_CMD_CLEAR_TEXT,
                          (VOID*)NULL,
                          (VOID*)NULL));                    

    c_uc_ps_to_w2s(pt_this->t_brd_info[ui4_brd_sel_idx].s_src_name, w2s_brand_name, DEV_SETUP_DB_NAME_LEN_MAX);
    RET_ON_ERR (a_vkb_do_cmd (pt_brand_page->h_brand_vkb,
                           VKB_CMD_SET_INITIAL_TEXT,
                           (VOID*)w2s_brand_name,
                           (VOID*)0XFF));                              
                              
    RET_ON_ERR (c_wgl_repaint (pt_brand_page->h_brand_eb_frm, NULL, TRUE));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_model_drop_down_lb_update
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_model_drop_down_lb_update( VOID )
{

    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;
    WZD_MODEL_PAGE_T*                       pt_model_page = &t_g_device_setup_model_page;
    BOOL                                    b_is_visible;
    INT32                                   i4_ret = WZDR_OK;
    UTF16_T                                 str_prefix[DEV_SETUP_DB_NAME_LEN_MAX + 1]= L"";

    RET_ON_ERR ( _wzd_page_tv_remote_device_setup_reset_model_info());
    
    RET_ON_ERR ( c_wgl_do_cmd(pt_model_page->h_model_lb, 
                              WGL_CMD_LB_DEL_ALL, 
                              NULL, 
                              NULL));
                        
    RET_ON_ERR ( a_vkb_do_cmd (pt_model_page->h_model_vkb,
                               VKB_CMD_GET_EB_CONTENT,
                              (VOID*) str_prefix,
                              (VOID*) (UINT32) DEV_SETUP_DB_NAME_LEN_MAX));
                          
    c_uc_w2s_to_ps(str_prefix, pt_this->c_mdl_pfx, DEV_SETUP_DB_NAME_LEN_MAX);

    if ( c_strcmp(pt_this->c_mdl_pfx, "") == 0 )
    {
        pt_this->ui4_mdl_sel_idx = 0xFFFFFFFF;
        c_memset(pt_this->s_mdl_name, 0, DEV_SETUP_DB_NAME_LEN_MAX + 1);
        RET_ON_ERR(c_wgl_get_visibility(pt_model_page->h_model_lb_frm, &b_is_visible)); 
        if ( b_is_visible == TRUE )
        {
            RET_ON_ERR (c_wgl_set_visibility(pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));
            RET_ON_ERR (c_wgl_repaint (pt_model_page->h_model_lb_frm, NULL, TRUE));
        } 

        return WZDR_OK;
    }
    
    i4_ret = a_dev_db_update_model_info(pt_this->ui4_type_sel_idx, 
                                        pt_this->t_dev_type[pt_this->ui4_type_sel_idx], 
                                        pt_this->t_brd_info[pt_this->ui4_brd_sel_idx], 
                                        pt_this->s_brd_name, 
                                        pt_this->c_mdl_pfx);
    if (i4_ret != WZDR_OK)
    {
        DBG_INFO( ("[Ln: %d] a_dev_db_update_model_info fail! i4_ret = %d\n", __LINE__, i4_ret));
        return WZDR_FAIL;
    }     
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_model_drop_down_lb_set_text_update
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_model_drop_down_lb_set_text_update(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;
    WZD_MODEL_PAGE_T*                       pt_model_page = &t_g_device_setup_model_page;
    UINT16                                  ui2_idx = 0;
    INT32                                   i4_ret = WZDR_OK;
    UTF16_T                                 s_src_name[DEV_SETUP_DB_NAME_LEN_MAX + 1]= L"";

    RET_ON_ERR(c_wgl_do_cmd(pt_model_page->h_model_lb, 
                             WGL_CMD_LB_DEL_ALL, 
                             NULL, 
                             NULL));
    
    i4_ret = a_dev_db_get_model_list(pt_this->t_mdl_info,
                                     &pt_this->ui4_mdl_num,
                                     pt_this->c_mdl_pfx);
    if (i4_ret != 0)
    {
        DBG_ERROR( ("[Ln: %d] a_dev_db_get_model_list()fail!!! i4_ret = %d\n", __LINE__, i4_ret));   
        return WZDR_FAIL;
    }

    if ((pt_this->ui4_mdl_num == 0) || (pt_this->ui4_mdl_num >= DEV_DB_DUL_OP_MAX))
    {
        DBG_INFO(  ("[Ln: %d] the model number value is invalid! get_modle_number = %d\n", __LINE__, pt_this->ui4_mdl_num));
        return WZDR_OK;
    }
    
    i4_ret = a_dev_db_resort_bm_list_with_str(pt_this->t_mdl_info,
                                              pt_this->ui4_mdl_num,
                                              "Vizio");  
    if (i4_ret != 0)
    {
        DBG_ERROR( ("[Ln: %d] a_dev_db_resort_bm_list_with_str()fail!!! i4_ret = %d\n", __LINE__, i4_ret));   
        return WZDR_FAIL;
    }  
    
    /* set listbox item number */
    i4_ret = c_wgl_do_cmd(pt_model_page->h_model_lb,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK(pt_this->ui4_mdl_num),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Iterate all the input sources */
    while (ui2_idx < pt_this->ui4_mdl_num)
    {
        c_uc_ps_to_w2s(pt_this->t_mdl_info[ui2_idx].s_src_name, s_src_name, DEV_SETUP_DB_NAME_LEN_MAX);
        /* set element text */
        RET_ON_ERR (c_wgl_do_cmd(pt_model_page->h_model_lb,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2((ui2_idx), 0),
                              WGL_PACK(s_src_name)));
        ui2_idx++;
    }

    RET_ON_ERR (c_wgl_do_cmd(pt_model_page->h_model_lb,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(0),
                          NULL));

    RET_ON_ERR (c_wgl_do_cmd(pt_model_page->h_model_lb,
                 WGL_CMD_LB_HLT_ELEM_VISIBLE,
                 WGL_PACK(0),
                 WGL_PACK(0)));

    RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_NORMAL));
    RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb, WGL_SW_NORMAL));
    RET_ON_ERR (c_wgl_repaint (pt_model_page->h_model_lb_frm, NULL, TRUE));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_select_mdl_eb_set_text
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_select_mdl_eb_set_text(UINT32 ui4_mdl_sel_idx)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    WZD_MODEL_PAGE_T* pt_model_page = &t_g_device_setup_model_page;
    UTF16_T w2s_model_name[DEV_SETUP_DB_NAME_LEN_MAX + 1] = {0};
    
    if (ui4_mdl_sel_idx > (WZD_DEVICE_BRAND_IDS_MAX_NUM - 1))  
    {  
        DBG_ERROR( ("[Ln: %d]  mdl_sel_idx = %d\n", __LINE__, ui4_mdl_sel_idx));
        return WZDR_FAIL;
    }

    RET_ON_ERR (a_vkb_do_cmd(pt_model_page->h_model_vkb,
                          VKB_CMD_CLEAR_TEXT,
                         (VOID*)NULL,
                         (VOID*)NULL));                    

    c_uc_ps_to_w2s(pt_this->t_mdl_info[ui4_mdl_sel_idx].s_src_name, w2s_model_name, DEV_SETUP_DB_NAME_LEN_MAX);
    RET_ON_ERR (a_vkb_do_cmd (pt_model_page->h_model_vkb,
                           VKB_CMD_SET_INITIAL_TEXT,
                          (VOID*)w2s_model_name,
                          (VOID*)0XFF));                         
                              
    RET_ON_ERR (c_wgl_repaint (pt_model_page->h_model_eb_frm, NULL, TRUE));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_set_button_text
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_set_button_text(VOID)
{
    WZD_CONFIRM_PAGE_T* pt_confirm_page = &t_g_device_setup_confirm_page;
    UTF16_T  ps_w2s[256] = {0};

    _wzd_page_tv_remote_device_setup_text_it_work_btn(WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_BTN_IT_WORKED), ps_w2s, 255);
    
    RET_ON_ERR ( c_wgl_do_cmd(pt_confirm_page->h_btn_worked,
                     WGL_CMD_BTN_SET_TEXT,
                     WGL_PACK (ps_w2s),
                     WGL_PACK (c_uc_w2s_strlen(ps_w2s))));

    RET_ON_ERR ( c_wgl_do_cmd(pt_confirm_page->h_btn_retry,
                     WGL_CMD_BTN_SET_TEXT,
                     WGL_PACK (WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_BTN_TRY_THE_NEXT_CODE)),
                     WGL_PACK (c_uc_w2s_strlen (WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_BTN_TRY_THE_NEXT_CODE)))));

    RET_ON_ERR ( c_wgl_do_cmd(pt_confirm_page->h_btn_manually,
                     WGL_CMD_BTN_SET_TEXT,
                     WGL_PACK (WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_BTN_MANU_ENTER_CODE)),
                     WGL_PACK (c_uc_w2s_strlen (WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_BTN_MANU_ENTER_CODE)))));

    RET_ON_ERR ( c_wgl_do_cmd(pt_confirm_page->h_btn_back,
                     WGL_CMD_BTN_SET_TEXT,
                     WGL_PACK (WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_BTN_BACK)),
                     WGL_PACK (c_uc_w2s_strlen (WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_BTN_BACK)))));

    RET_ON_ERR ( c_wgl_do_cmd(pt_confirm_page->h_btn_skip,
                     WGL_CMD_BTN_SET_TEXT,
                     WGL_PACK (WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_BTN_SKIP)),
                     WGL_PACK (c_uc_w2s_strlen (WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_BTN_SKIP)))));
    
    return  WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_code_chang_lang
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_code_chang_lang(UINT8   ui1_code_index,
                                                                      BOOL    b_repaint)
{
    UTF16_T     w2s_str[128] = {0};
    CHAR        s_codeset[16] = {0};
    UTF16_T     w2s_codeset[16] = {0};
    INT32       i4_ret = WZDR_OK;
    UTF16_T     code_w2s[WZD_DEVICE_SETUP_SHOW_MIG_MAX_NUM] = {0};
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*      pt_this = &t_g_tv_remote_device_setup;
    WZD_CONFIRM_PAGE_T*                       pt_confirm_page = &t_g_device_setup_confirm_page;
    ISO_639_LANG_T s639_lang = {0};


    if (pt_this->ui1_codeset_num == 0 && pt_this->b_is_codeset_query_fail == FALSE) 
    {
        DBG_INFO( ("[Ln: %d] device setup codeset not found!\n", __LINE__));
        RET_ON_ERR ( c_wgl_do_cmd(pt_confirm_page->h_code_msg_txt,
                     WGL_CMD_TEXT_SET_TEXT,
                     WGL_PACK (WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_CODESET_NOT_FOUND)),
                     WGL_PACK (c_uc_w2s_strlen (WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_CODESET_NOT_FOUND)))));
    }
    else
    {
        if (pt_this->ui1_codeset_num == 0)
        {
            ui1_code_index = 0;
        }
        
	    i4_ret = a_cfg_get_gui_lang(s639_lang);
	    if ((i4_ret == WZDR_OK) && (c_strncmp(s639_lang, s639_app_cfg_lang_eng, ISO_639_LANG_LEN) == 0))
    	{
    		c_sprintf(s_codeset, "%d of %d:    ", ui1_code_index, pt_this->ui1_codeset_num);
    	}
		else
		{
			c_sprintf(s_codeset, "%d de %d:    ", ui1_code_index, pt_this->ui1_codeset_num);
		}
        c_uc_ps_to_w2s(s_codeset, w2s_codeset, 16);
        c_uc_w2s_strcpy(w2s_str, WZD_TEXT (MLM_WZD_KEY_DEVICE_SETUP_CONFIRM_CODE_MSG));
        c_uc_w2s_strcat(w2s_str, w2s_codeset);

        i4_ret = _wzd_page_tv_remote_device_setup_code_text_connect (w2s_str, code_w2s);
        if (i4_ret != 0)
        {
            DBG_ERROR( ("[Ln: %d] _wzd_page_tv_remote_device_setup_code_text_connect error! i4_ret =  %d\n", __LINE__, i4_ret));
            return i4_ret;     
        }
        RET_ON_ERR ( c_wgl_do_cmd(pt_confirm_page->h_code_msg_txt,
                     WGL_CMD_TEXT_SET_TEXT,
                     WGL_PACK (code_w2s),
                     WGL_PACK (c_uc_w2s_strlen (code_w2s))));
    }      
    
    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_set_device_info
 *
 * Description: 
 *
 * Inputs:  - b_is_src_id_valid
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_set_device_info(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    ISL_REC_T  t_isl_rec = {0};
    UINT8      ui1_src_idx = 0; 

    DBG_INFO( ("[Ln: %d] [SET DEVICE INFO] type_sel_idx = %d, dev_type = %s, sel_src_idx = %d, s_brd_name = %s, s_mdl_name = %s, s_codeset1 = %s\n", __LINE__, 
                pt_this->ui4_type_sel_idx, 
                pt_this->s_type_name, 
                pt_this->ui1_sel_src_idx,
                pt_this->s_brd_name, 
                pt_this->s_mdl_name,
                pt_this->s_codeset));

    if (pt_this->b_is_device_setup_worked == FALSE) 
    {
       c_memset(pt_this->s_codeset, 0, sizeof(pt_this->s_codeset));
    }

    if (pt_this->ui1_sel_src_idx != 0xFF && DEVICE_TYPE_SELECT_AUDIO_RECIEVER != pt_this->ui4_type_sel_idx && DEVICE_TYPE_SELECT_SOUND_BAR != pt_this->ui4_type_sel_idx)
    {
        ui1_src_idx = pt_this->aui1_input_src_id[pt_this->ui1_sel_src_idx];
        a_isl_get_rec_by_idx(ui1_src_idx, &t_isl_rec);

        a_cfg_custom_set_device_info(t_isl_rec.ui1_id,
                                     pt_this->s_type_name,
                                     pt_this->s_brd_name, 
                                     pt_this->s_mdl_name, 
                                     pt_this->s_codeset);
    }


    if ((DEVICE_TYPE_SELECT_AUDIO_RECIEVER == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SOUND_BAR == pt_this->ui4_type_sel_idx))
    {
    	if(DEVICE_TYPE_SELECT_AUDIO_RECIEVER == pt_this->ui4_type_sel_idx)
    	{
	    	a_cfg_custom_set_device_info(0,
                                     pt_this->s_aud_amp_type,
                                     pt_this->s_brd_name, 
                                     pt_this->s_mdl_name, 
                                     pt_this->s_codeset);
    	}
    	else
    	{
	    	a_cfg_custom_set_device_info(0,
                                     pt_this->s_type_name,
                                     pt_this->s_brd_name, 
                                     pt_this->s_mdl_name, 
                                     pt_this->s_codeset);
    	}
        
    }
    else 
    {
        DBG_INFO( ("[Ln: %d] [SET DEVICE INFO] sel_src_idx is error!!! pt_this->ui1_sel_src_idx = %d\n", __LINE__, pt_this->ui1_sel_src_idx));                                  
    }

    _wzd_page_tv_remote_device_setup_get_device_paired_info();

    return WZDR_OK; 
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_turn_off_tv_speaker
 *
 * Description: 
 *
 * Inputs:  - b_is_src_id_valid
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_turn_off_tv_speaker(VOID)
{
    INT16     i2_val = 0;
    UINT16    ui2_aud_out_mask = 0;  
    UINT16    ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);

    /*turn off TV speaker*/
    a_cfg_av_get(ui2_id, &i2_val);
    ui2_aud_out_mask = (UINT16)i2_val;

    if (ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER)
    {
        /* Off */
        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);

        a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
        a_cfg_av_update(ui2_id);
    }
    
    /* set audio ctrl flag to AUD_CONTROL_EXTERNAL */
    a_cfg_custom_set_vol_control(1);

    /* set soundbar_enable and soundbar codeset */
    a_tv_net_custom_set_soundbar_flag(TRUE);

    return WZDR_OK;        
 } 

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_turn_on_tv_speaker
 *
 * Description: 
 *
 * Inputs:  - b_is_src_id_valid
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_turn_on_tv_speaker(VOID)
{
    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16  ui2_aud_out_mask = 0;  
    INT16   i2_val = 0;

    /*turn off TV speaker*/
    a_cfg_av_get(ui2_id, &i2_val);
    ui2_aud_out_mask = (UINT16)i2_val;

    /* On */
    ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask | SCC_AUD_OUT_PORT_SPEAKER);

    a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
    a_cfg_av_update(ui2_id);

    a_cfg_custom_set_vol_control(0);                                    
    a_tv_net_custom_set_soundbar_flag(FALSE);
    
    return WZDR_OK;   
}
 
/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_get_codeset_from_list
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_get_codeset_from_list (UINT32 ui4_index)
{
    UINT32   ui4_idx = 0;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    
    DBG_INFO( ("[Ln: %d] codesetlist1_num = %d, codesetlist2_num = %d\n", __LINE__,
                pt_this->pt_codeset_list->t_codeset_list1.i4_length,
                pt_this->pt_codeset_list->t_codeset_list2.i4_length));

    /* for codeset list1 */
    for (ui4_idx = 0; ui4_idx < pt_this->pt_codeset_list->t_codeset_list1.i4_length; ui4_idx ++)
    {
        if (NULL != pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx])
        {
            DBG_INFO( ("[Ln: %d] codeset_idx[%-3d]---> codeset[%-20s]\n", __LINE__,
                        ui4_idx, pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx]));
            if(ui4_index == ui4_idx)
            {
                c_memcpy(pt_this->s_codeset, pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx], 6);
            }
        }
    }

    /* for codeset list2 */
    for (ui4_idx = 0; ui4_idx < pt_this->pt_codeset_list->t_codeset_list2.i4_length; ui4_idx ++)
    {
        if (NULL != pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx])
        {
            DBG_INFO( ("[Ln: %d] codeset_idx[%-3d]---> codeset[%-20s]\n", __LINE__,
                        ui4_idx + pt_this->pt_codeset_list->t_codeset_list1.i4_length,
                        pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx]));

            if(ui4_index == (ui4_idx + pt_this->pt_codeset_list->t_codeset_list1.i4_length))
            {
                c_memcpy(pt_this->s_codeset, pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx], 6);
            }
        }
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_save_and_upload_codeset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_save_and_upload_codeset(UINT32 ui4_idx)
{
    INT32 i4_ret = WZDR_OK;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;

    if (ui4_idx >= (pt_this->pt_codeset_list->t_codeset_list1.i4_length + pt_this->pt_codeset_list->t_codeset_list2.i4_length))
    {
        DBG_INFO( ("[Ln: %d] the index for codeset should not more then [%d]\n", __LINE__,
                   pt_this->pt_codeset_list->t_codeset_list1.i4_length + pt_this->pt_codeset_list->t_codeset_list2.i4_length));    }
    else
    {        
        DBG_INFO( ("[Ln: %d] the codeset select ui4_idx = %d\n", __LINE__, ui4_idx));

        if (ui4_idx >= pt_this->pt_codeset_list->t_codeset_list1.i4_length)
        {
            if (NULL != pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx - pt_this->pt_codeset_list->t_codeset_list1.i4_length])
            {
                i4_ret = a_dev_db_save_codeset(pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx - pt_this->pt_codeset_list->t_codeset_list1.i4_length]);

                i4_ret = a_dev_db_upload_codeset_ex(pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx - pt_this->pt_codeset_list->t_codeset_list1.i4_length]);
                if (i4_ret == WZDR_OK)
                {
                    DBG_INFO( ("[Ln: %d] a_dev_db_upload_codeset_ex() list2.p_list success!!! codeset =[%s]\n", __LINE__, pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx - pt_this->pt_codeset_list->t_codeset_list1.i4_length]));
                }
                else
                {
                    DBG_INFO( ("[Ln: %d] a_dev_db_upload_codeset_ex() list2.p_list fail!!! i4_ret = %d\n", __LINE__, i4_ret));
                }

                /* set codeset */
                _wzd_page_tv_remote_device_setup_set_codeset(pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx - pt_this->pt_codeset_list->t_codeset_list1.i4_length]); 

            }
        }
        else
        {
            if (NULL != pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx])
            {
                i4_ret = a_dev_db_save_codeset(pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx]);
                
                i4_ret = a_dev_db_upload_codeset_ex(pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx]);
                if (i4_ret == WZDR_OK)
                {
                    DBG_INFO( ("[Ln: %d] a_dev_db_upload_codeset_ex()list1.p_list success!!! codeset =[%s]\n", __LINE__, pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx]));
                }
                else
                {
                    DBG_INFO( ("[Ln: %d] a_dev_db_upload_codeset_ex()list1.p_list fail!!! i4_ret = %d\n", __LINE__, i4_ret));
                }
                /* set codeset */
                _wzd_page_tv_remote_device_setup_set_codeset(pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx]);
            }
        }
    }

    return CLIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:_wzd_page_tv_remote_device_setup_do_retry_next_code
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_do_retry_next_code(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this         = &t_g_tv_remote_device_setup;
    WZD_CONFIRM_PAGE_T*                  pt_confirm_page = &t_g_device_setup_confirm_page;
    INT32                                i4_ret          = WZDR_OK;
    
    DBG_INFO( ("[Ln: %d] [do try next code] type_sel_idx = %d, dev_type = %s, s_brd_name = %s, s_mdl_name = %s\n", __LINE__, 
               pt_this->ui4_type_sel_idx, 
               pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, 
               pt_this->s_brd_name, 
               pt_this->s_mdl_name));
                                         
    if (pt_this->ui1_cur_code_pos < pt_this->ui1_codeset_num)
    {
        /* current only support two max codeset*/
        if (pt_this->ui1_codeset_num == WZD_DEV_SETUP_TRY_CODESET_MIN_NUM)
        {
            /* upload codest2 */
            i4_ret = a_dev_db_upload_codeset_ex(pt_this->pt_codeset->c_codeset2);
            c_strncpy(pt_this->s_codeset, pt_this->pt_codeset->c_codeset2, 5);
            DBG_INFO( ("[Ln: %d] a_dev_db_upload_codeset_2(), i4_ret = %d, pt_this->s_codeset2 = %s\n", __LINE__, i4_ret, pt_this->s_codeset));       

            /* set codeset */
            _wzd_page_tv_remote_device_setup_set_codeset(pt_this->s_codeset);

            pt_this->ui1_cur_code_pos ++;
            DBG_INFO( ("[Ln: %d] pt_this->ui1_cur_code_pos = %d, pt_this->ui1_codeset_num = %d\n", __LINE__, pt_this->ui1_cur_code_pos, pt_this->ui1_codeset_num));
            _wzd_page_tv_remote_device_setup_confirm_code_chang_lang(pt_this->ui1_cur_code_pos, TRUE);
            pt_this->b_is_codeset_querying = FALSE;   

            c_wgl_enable(pt_confirm_page->h_btn_retry, FALSE);
            DBG_INFO( ("[Ln: %d] codeset retry is over! i4_ret = %d\n", __LINE__, i4_ret));
            c_wgl_repaint(pt_confirm_page->h_btn_retry, NULL, TRUE);
            
            c_wgl_set_focus(pt_confirm_page->h_btn_worked, WGL_SYNC_AUTO_REPAINT);

            if(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_AUDIO_RECIEVER )
	        {
	            c_memset(pt_this->s_aud_amp_type, 0, DEV_SETUP_DB_NAME_LEN_MAX);
	            c_strncpy(pt_this->s_aud_amp_type, DEV_DB_TYPE_AMPLIFIER_NAME, DEV_SETUP_DB_NAME_LEN_MAX);
	        }

        }  
        else
        {
            DBG_INFO( ("[Ln: %d] pt_this->ui1_codeset_num = %d is error!!!\n", __LINE__, pt_this->ui1_codeset_num));
        }
    }
    else
    {
        DBG_INFO( ("[Ln: %d] pt_this->ui1_cur_code_pos = %d is error!!!\n", __LINE__, pt_this->ui1_cur_code_pos));
    }
}

/*----------------------------------------------------------------------------
 * Name:_wzd_page_tv_remote_device_setup_do_retry_next_code_without_sel_mdl
 *
 * Description:call this function if the end user select the button of I Don't Know the Model button.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_do_retry_next_code_without_sel_mdl(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this         = &t_g_tv_remote_device_setup;
    WZD_CONFIRM_PAGE_T*                  pt_confirm_page = &t_g_device_setup_confirm_page;
    INT32                                i4_ret          = WZDR_OK;

    DBG_INFO( ("[Ln: %d] [do try next code with brand] type_sel_idx = %d, dev_type = %s, s_brd_name = %s\n", __LINE__, 
                pt_this->ui4_type_sel_idx, 
                pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, 
                pt_this->s_brd_name));
                
    DBG_INFO( ("[Ln: %d] pt_this->ui1_cur_code_pos = %d, pt_this->ui1_codeset_num = %d\n", __LINE__, pt_this->ui1_cur_code_pos, pt_this->ui1_codeset_num));

    if (pt_this->ui1_cur_code_pos < pt_this->ui1_codeset_num)
    {
        /* get next codeset from list */
        i4_ret = _wzd_page_tv_remote_device_setup_get_codeset_from_list(pt_this->ui1_cur_code_pos);
        DBG_INFO( ("[Ln: %d] _wzd_page_tv_remote_device_setup_get_codeset_from_list(), i4_ret = %d, pt_this->ui1_cur_code_pos = %d, pt_this->s_codeset = %s\n", __LINE__,i4_ret, pt_this->ui1_cur_code_pos, pt_this->s_codeset)); 

        /* upload codeset with brand */
        i4_ret = _wzd_page_tv_remote_device_setup_save_and_upload_codeset(pt_this->ui1_cur_code_pos);
        DBG_INFO( ("[Ln: %d] _wzd_page_tv_remote_device_setup_save_and_upload_codeset(), i4_ret = %d, pt_this->ui1_cur_code_pos = %d\n", __LINE__, i4_ret, pt_this->ui1_cur_code_pos)); 
        
        pt_this->ui1_cur_code_pos ++;
        DBG_INFO( ("[Ln: %d] pt_this->ui1_cur_code_pos = %d, pt_this->ui1_codeset_num = %d\n", __LINE__, pt_this->ui1_cur_code_pos, pt_this->ui1_codeset_num));
        _wzd_page_tv_remote_device_setup_confirm_code_chang_lang(pt_this->ui1_cur_code_pos, TRUE);

        pt_this->b_is_codeset_querying = FALSE; 

        c_wgl_set_focus(pt_confirm_page->h_btn_worked, WGL_SYNC_AUTO_REPAINT);

        if(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_AUDIO_RECIEVER )
        {
            c_memset(pt_this->s_aud_amp_type, 0, DEV_SETUP_DB_NAME_LEN_MAX);
            if(pt_this->ui1_cur_code_pos < pt_this->pt_codeset_list->t_codeset_list1.i4_length)
            {
	            c_strncpy(pt_this->s_aud_amp_type, DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME, DEV_SETUP_DB_NAME_LEN_MAX);
            }
            else
            {
	            c_strncpy(pt_this->s_aud_amp_type, DEV_DB_TYPE_AMPLIFIER_NAME, DEV_SETUP_DB_NAME_LEN_MAX);
            }
        }

        if (pt_this->ui1_cur_code_pos == pt_this->ui1_codeset_num)
        {
            i4_ret = c_wgl_enable(pt_confirm_page->h_btn_retry, FALSE);
            DBG_INFO( ("[Ln: %d] codeset retry is over! i4_ret = %d\n", __LINE__, i4_ret));
        }      
    }
    else
    {
        DBG_INFO( ("[Ln: %d] pt_this->ui1_cur_code_pos = %d is error!!!\n", __LINE__, pt_this->ui1_cur_code_pos));
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_set_codeset
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_set_codeset(CHAR* c_codeset)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this = &t_g_tv_remote_device_setup;
    INT32								  i4_ret = WZDR_OK;

    if ((DEVICE_TYPE_SELECT_AUDIO_RECIEVER == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SOUND_BAR == pt_this->ui4_type_sel_idx))
    {
        a_tv_net_custom_set_soundbar_codeset(c_codeset);

        /* according to device type setup turn off tv speaker */
        if ((DEVICE_TYPE_SELECT_AUDIO_RECIEVER == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SOUND_BAR == pt_this->ui4_type_sel_idx))
        {
            i4_ret =_wzd_page_tv_remote_device_setup_turn_off_tv_speaker();  
            DBG_INFO( ("[Ln: %d] _wzd_page_tv_remote_device_setup_turn_off_tv_speaker(), i4_ret = %d\n", __LINE__, i4_ret));            
        }
    }
    else
    {
        a_tv_net_custom_set_codeset(c_codeset);   
    }

    return WZDR_OK;
}
#ifdef APP_UEI_SPINNER_SUPPORT
/*----------------------------------------------------------------------------
* Name: _add_device_animation_do_timer_nfy
*
* Description: 
*
* Inputs:
*
* Outputs:
*
* Returns: 
----------------------------------------------------------------------------*/
static VOID _add_device_animation_do_timer_nfy(
														VOID* pv_data,
														SIZE_T	z_data_size)
{  
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this                 = &t_g_tv_remote_device_setup;
	
	c_wgl_set_visibility(pt_this->h_animation, WGL_SW_HIDE);
	wzd_view_main_frm_repaint();
	DBG_INFO( ("\n####%s(%d)HIDE animation for timeout\n",__FUNCTION__,__LINE__));
   
}

/*----------------------------------------------------------------------------
* Name: _add_device_animation_timer_cb_fct
*
* Description: 
*
* Inputs:
*
* Outputs:
*
* Returns: 
----------------------------------------------------------------------------*/
static VOID _add_device_animation_timer_cb_fct(HANDLE_T  pt_tm_handle,
                                    VOID*     pv_tag)
{  
	
    INT32 i4_ret = WZDR_OK;
    
    i4_ret = wzd_async_invoke(_add_device_animation_do_timer_nfy, 
                               NULL, 0, TRUE);

}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_animation_do_timer_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_animation_do_timer_nfy(VOID* pv_data,
                                 SIZE_T  z_data_size)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this                 = &t_g_tv_remote_device_setup;

    if ((DEVICE_SETUP_SELECT_BRAND == pt_this->e_state)||(DEVICE_SETUP_CODE_CONFIRM== pt_this->e_state))
    {
	    _wzd_page_tv_remote_timer_icon_update(pt_this->h_animation);
	    
	    c_timer_start(pt_this->h_timer,
	                            1000,
	                            X_TIMER_FLAG_ONCE,
	                            _wzd_page_tv_remote_animation_timer_notify_fct,
	                            NULL);
    }
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_animation_timer_notify_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_animation_timer_notify_fct(HANDLE_T  pt_tm_handle,
                                     VOID*     pv_tag)
{
    wzd_async_invoke(_wzd_page_tv_remote_animation_do_timer_nfy, pv_tag, (0), TRUE);
    return;
}
#endif
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_dev_db_online_query_hdlr
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_dev_db_online_query_hdlr(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3)
{
    DEV_DB_BMC_QUERY_T*                   pt_tag_query_info       = (DEV_DB_BMC_QUERY_T*)((UINT32)(pv_tag2));
    WZD_CONFIRM_PAGE_T*                   pt_confirm_page         = &t_g_device_setup_confirm_page;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this                 = &t_g_tv_remote_device_setup;
    CHAR                                  s_active_app[APP_NAME_MAX_LEN + 1] = {0} ;
    BOOL                                  b_need_to_update_brd_ui = FALSE;
    BOOL                                  b_need_to_update_mdl_ui = FALSE;  
    INT32                                 i4_ret = WZDR_OK;
    
#ifdef APP_UEI_SPINNER_SUPPORT
    GL_RECT_T                   		  t_rect = {0};
#endif
    
    a_am_get_active_app (s_active_app) ;

    /* if the page is not show or the current active app is not wizard should discard the notify info*/
    if (c_strcmp(s_active_app, WZD_NAME) != 0)
    {
        return;
    }
    
    if ((DEV_DB_THREAD_QUERY_BRAND != pt_tag_query_info->e_query_type)
        && (DEV_DB_THREAD_QUERY_MODEL != pt_tag_query_info->e_query_type)
        && (DEV_DB_THREAD_QUERY_CODESET != pt_tag_query_info->e_query_type)
        && (DEV_DB_THREAD_QUERY_CODESET_WITH_BRD != pt_tag_query_info->e_query_type))
    {
        return;
    }

    if (DEV_DB_THREAD_QUERY_BRAND == pt_tag_query_info->e_query_type)
    {
        DBG_INFO( ("[Ln: %d] c_brd_pfx = %s, s_brd_prefix = %s, ui4_notify_count = %d, ui4_brd_notify_count = %d\n", __LINE__, 
            pt_this->c_brd_pfx, pt_tag_query_info->s_brd_prefix, pt_tag_query_info->ui4_notify_count, pt_this->ui4_brd_notify_count));     

        if ((0 == c_strcmp(pt_this->c_brd_pfx, pt_tag_query_info->s_brd_prefix))
                && (DEVICE_SETUP_SELECT_BRAND == pt_this->e_state)
                && (pt_tag_query_info->ui4_notify_count != pt_this->ui4_brd_notify_count))
        {
            DBG_INFO( ("[Ln: %d] [call get brand]type_sel_idx = %d, dev_type = %s, brd_pfx = %s, s_brd_name = %s\n", __LINE__, 
                       pt_this->ui4_type_sel_idx, pt_this->s_type_name, pt_this->c_brd_pfx, pt_this->s_brd_name));
            
#ifdef APP_UEI_SPINNER_SUPPORT
			DBG_INFO( ("\n####%s(%d)DEV_DB_THREAD_QUERY_BRAND start=%d,complete=%d,notify_cnt=%d,this_cnt=%d\n",__FUNCTION__,__LINE__,pt_tag_query_info->b_is_brd_online_query_start,pt_tag_query_info->b_is_brd_online_query_complete,pt_tag_query_info->ui4_notify_count,pt_this->ui4_brd_notify_count));

			if(pt_tag_query_info->b_is_brd_online_query_start)
			{
				if(!pt_this->b_is_brd_online_query_start)
				{
					pt_this->b_is_brd_online_query_start = TRUE;

					SET_RECT_BY_SIZE (& t_rect,
									  WZD_DEVICE_SETUP_LB_X+WZD_DEVICE_SETUP_LB_W/2,
									  WZD_DEVICE_SETUP_LB_Y+30,
									  WZD_DEVICE_SETUP_SPINNER_ICON_W,
									  WZD_DEVICE_SETUP_SPINNER_ICON_H);

					c_wgl_move( pt_this->h_animation, &t_rect,WGL_NO_AUTO_REPAINT);
						
					c_wgl_insert(pt_this->h_animation,
								  NULL_HANDLE,
								  WGL_INSERT_TOPMOST,
								  FALSE);
					
					c_wgl_set_visibility(pt_this->h_animation, WGL_SW_NORMAL);

					/* enable the animation scan timer */
					c_timer_start(pt_this->h_timer,
											1000,
											X_TIMER_FLAG_ONCE,
											_wzd_page_tv_remote_animation_timer_notify_fct,
											NULL);

					c_timer_start(pt_this->h_brd_online_timer,
								60000,
								X_TIMER_FLAG_ONCE,
								_add_device_animation_timer_cb_fct,
								NULL);
				}
			}
			
			if(pt_tag_query_info->b_is_brd_online_query_complete)
			{
				pt_this->b_is_brd_online_query_complete = TRUE;

				c_wgl_set_visibility(pt_this->h_animation, WGL_SW_HIDE);
				DBG_INFO( ("\n####%s(%d)HIDE animation for complete\n",__FUNCTION__,__LINE__));
			}
#endif		
            i4_ret = a_dev_db_get_brand_list(pt_this->t_brd_info,
                                             &pt_this->ui4_brd_num,
                                             pt_this->c_brd_pfx);

            DBG_INFO( ("[Ln: %d] [get brand]i4_ret[%d], brd_num = %d, brd_pfx = %s!\n", __LINE__, i4_ret, pt_this->ui4_brd_num, pt_this->c_brd_pfx));
            pt_this->ui4_brd_notify_count = pt_tag_query_info->ui4_notify_count;
            
            if ( DEV_DBR_OK != i4_ret)
            {
                if (pt_tag_query_info->b_is_to_clean)
                {
                
#ifdef APP_UEI_SPINNER_SUPPORT
	        		c_wgl_set_visibility(pt_this->h_animation, WGL_SW_HIDE);
					DBG_INFO( ("\n####%s(%d)HIDE animation for b_is_to_clean FAIL\n",__FUNCTION__,__LINE__));
#endif
	                DBG_INFO( ("[Ln: %d] query model error clean slot[%d]!is_to_clean = %d\n", __LINE__, pt_tag_query_info->ui4_task_idx, pt_tag_query_info->b_is_to_clean));
                    a_dev_db_reset_bmc_query_info(pt_tag_query_info);
                    pt_this->ui4_brd_notify_count = 0;
                }
                b_need_to_update_brd_ui = FALSE;
                return;
            }
            else
            {
                b_need_to_update_brd_ui = TRUE;
            }
        }
#ifdef APP_UEI_SPINNER_SUPPORT
        if ((DEVICE_SETUP_SELECT_BRAND == pt_this->e_state)&&(pt_tag_query_info->b_is_to_clean))
        {    
        	c_wgl_set_visibility(pt_this->h_animation, WGL_SW_HIDE);
			DBG_INFO( ("\n####%s(%d)HIDE animation for b_is_to_clean FAIL\n",__FUNCTION__,__LINE__));
			
            DBG_INFO( ("[Ln: %d] query brand clean slot[%d]! is_to_clean = %d\n", __LINE__, pt_tag_query_info->ui4_task_idx, pt_tag_query_info->b_is_to_clean));
            a_dev_db_reset_bmc_query_info(pt_tag_query_info);
            pt_this->ui4_brd_notify_count = 0;
        }
#else
        if (pt_tag_query_info->b_is_to_clean)
        {    
            DBG_INFO( ("[Ln: %d] query brand clean slot[%d]! is_to_clean = %d\n", __LINE__, pt_tag_query_info->ui4_task_idx, pt_tag_query_info->b_is_to_clean));
            a_dev_db_reset_bmc_query_info(pt_tag_query_info);
            pt_this->ui4_brd_notify_count = 0;
        }

#endif
    }

    if (DEV_DB_THREAD_QUERY_MODEL == pt_tag_query_info->e_query_type)
    {
        DBG_INFO( ("[Ln: %d] pt_mdl_pfx = %s, s_mdl_prefix = %s, ui4_notify_count = %d, ui4_mdl_notify_count = %d\n", __LINE__, 
            pt_this->c_mdl_pfx, pt_tag_query_info->s_mdl_prefix, pt_tag_query_info->ui4_notify_count, pt_this->ui4_mdl_notify_count));     

        if ((0 == c_strcmp(pt_this->c_mdl_pfx, pt_tag_query_info->s_mdl_prefix))
                && (DEVICE_SETUP_SELECT_MODEL == pt_this->e_state)
                && (pt_tag_query_info->ui4_notify_count != pt_this->ui4_mdl_notify_count))
        {
            i4_ret = a_dev_db_get_model_list(pt_this->t_mdl_info,
                                             &pt_this->ui4_mdl_num,
                                             pt_this->c_mdl_pfx);
            DBG_INFO( ("[Ln: %d] i4_ret[%d], mdl_num = %d, mdl_pfx = %s!\n", __LINE__, i4_ret, pt_this->ui4_mdl_num, pt_this->c_mdl_pfx));
            
            pt_this->ui4_mdl_notify_count = pt_tag_query_info->ui4_notify_count;
            
            if (DEV_DBR_OK != i4_ret)
            {            
                if (pt_tag_query_info->b_is_to_clean)
                {
                    DBG_INFO( ("[Ln: %d] query model error clean slot[%d]!is_to_clean = %d\n", __LINE__, pt_tag_query_info->ui4_task_idx, pt_tag_query_info->b_is_to_clean));
                    a_dev_db_reset_bmc_query_info(pt_tag_query_info);
                    pt_this->ui4_mdl_notify_count = 0;
                }
                b_need_to_update_mdl_ui = FALSE;
                return;
            }
            else
            {
                b_need_to_update_mdl_ui = TRUE;
            }
        }

        if (pt_tag_query_info->b_is_to_clean)
        {
            DBG_INFO( ("[Ln: %d] query model error clean slot[%d]!is_to_clean = %d\n", __LINE__, pt_tag_query_info->ui4_task_idx, pt_tag_query_info->b_is_to_clean));
            a_dev_db_reset_bmc_query_info(pt_tag_query_info);
            pt_this->ui4_mdl_notify_count = 0;
        }
    }

    if (DEV_DB_THREAD_QUERY_CODESET == pt_tag_query_info->e_query_type)
    {
        DBG_INFO( ("[Ln: %d] [call get codeset] type_sel_idx = %d, dev_type = %s, s_brd_name = %s, s_mdl_name = %s\n", __LINE__, 
                   pt_this->ui4_type_sel_idx, 
                   pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, 
                   pt_this->s_brd_name, 
                   pt_this->s_mdl_name));

        /* get codest */
        i4_ret = a_dev_db_get_codeset(&pt_this->pt_codeset);
        if (i4_ret != WZDR_OK)
        {
            DBG_INFO( ("[Ln: %d] a_dev_db_get_codeset()fail!!! i4_ret = %d\n", __LINE__, i4_ret));      
            return;
        }

        if (NULL != pt_this->pt_codeset->c_codeset1)
        {
            /* upload codest1 */
            i4_ret = a_dev_db_upload_codeset_ex(pt_this->pt_codeset->c_codeset1);
            c_strncpy(pt_this->s_codeset, pt_this->pt_codeset->c_codeset1, 5);
            DBG_INFO( ("[Ln: %d] a_dev_db_upload_codeset_1(), i4_ret = %d, pt_this->s_codeset1 = %s\n", __LINE__, i4_ret, pt_this->s_codeset));    
            _wzd_page_tv_remote_device_setup_set_codeset(pt_this->s_codeset);

            if(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_AUDIO_RECIEVER )
            {
	            c_memset(pt_this->s_aud_amp_type, 0, DEV_SETUP_DB_NAME_LEN_MAX);
	            c_strncpy(pt_this->s_aud_amp_type, DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME, DEV_SETUP_DB_NAME_LEN_MAX);
            }

        }
        else if (NULL != pt_this->pt_codeset->c_codeset2)
        {   
            /* upload codest2 */
            i4_ret = a_dev_db_upload_codeset_ex(pt_this->pt_codeset->c_codeset2);
            c_strncpy(pt_this->s_codeset, pt_this->pt_codeset->c_codeset2, 5);
            DBG_INFO( ("[Ln: %d] a_dev_db_upload_codeset_2(), i4_ret = %d, pt_this->s_codeset2 = %s\n", __LINE__, i4_ret, pt_this->s_codeset));       
            _wzd_page_tv_remote_device_setup_set_codeset(pt_this->s_codeset); 

            if(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_AUDIO_RECIEVER )
            {
	            c_memset(pt_this->s_aud_amp_type, 0, DEV_SETUP_DB_NAME_LEN_MAX);
	            c_strncpy(pt_this->s_aud_amp_type, DEV_DB_TYPE_AMPLIFIER_NAME, DEV_SETUP_DB_NAME_LEN_MAX);
            }

        }
        else
        {
            /* do nothing */
        }
       
        if (NULL != pt_this->pt_codeset->c_codeset1)
        {
            pt_this->ui1_codeset_num ++;
        }

        if (NULL != pt_this->pt_codeset->c_codeset2)
        {
            pt_this->ui1_codeset_num ++;
        }
        
        if (pt_tag_query_info->b_is_to_clean)
        {
            a_dev_db_reset_bmc_query_info(pt_tag_query_info);
        }

        if (pt_this->ui1_codeset_num < WZD_DEV_SETUP_TRY_CODESET_MIN_NUM)
        {
            c_wgl_enable(pt_confirm_page->h_btn_retry, FALSE);
        }
        else
        {
            c_wgl_enable(pt_confirm_page->h_btn_retry, TRUE);
        }

        pt_this->ui1_cur_code_pos ++;
        DBG_INFO( ("[Ln: %d] pt_this->ui1_cur_code_pos = %d, pt_this->ui1_codeset_num = %d\n", __LINE__, pt_this->ui1_cur_code_pos, pt_this->ui1_codeset_num));

        _wzd_page_tv_remote_device_setup_confirm_code_chang_lang(pt_this->ui1_cur_code_pos, TRUE);
        
        pt_this->e_pre_state = DEVICE_SETUP_SELECT_MODEL;
        pt_this->e_state = DEVICE_SETUP_CODE_CONFIRM;
        _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
        pt_this->b_is_codeset_querying = FALSE;
        
#ifdef APP_UEI_SPINNER_SUPPORT
		/*hide spinner after get codeset for confirm remote conection page*/
		c_wgl_set_visibility(pt_this->h_animation, WGL_SW_HIDE);
		DBG_INFO( ("\n####%s(%d)get codese sucess\n",__FUNCTION__,__LINE__));
#endif

    }
    if (DEV_DB_THREAD_QUERY_CODESET_WITH_BRD == pt_tag_query_info->e_query_type)
    {
        DBG_INFO( ("[Ln: %d] [call get codeset] type_sel_idx = %d, dev_type = %s, s_brd_name = %s\n", __LINE__, 
                   pt_this->ui4_type_sel_idx, 
                   pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, 
                   pt_this->s_brd_name));
		
		if(DEVICE_SETUP_CODE_CONFIRM == pt_this->e_state)
		{
	        /* get codeset list */
	        i4_ret = a_dev_db_get_codeset_list(&pt_this->pt_codeset_list);
	        pt_this->ui1_codeset_num = pt_this->pt_codeset_list->t_codeset_list1.i4_length + pt_this->pt_codeset_list->t_codeset_list2.i4_length;  
	        DBG_INFO( ("[Ln: %d] a_dev_db_get_codeset_list(), i4_ret = %d, pt_this->ui1_codeset_num = %d\n", __LINE__, i4_ret, pt_this->ui1_codeset_num));   

	        /* get index is 0 codeset from list */
	        pt_this->ui1_cur_code_pos = 0;
	        i4_ret = _wzd_page_tv_remote_device_setup_get_codeset_from_list(pt_this->ui1_cur_code_pos);
	        DBG_INFO( ("[Ln: %d] _wzd_page_tv_remote_device_setup_get_codeset_from_list(), i4_ret = %d, pt_this->ui1_cur_code_pos = %d, pt_this->s_codeset = %s\n", __LINE__,i4_ret, pt_this->ui1_cur_code_pos, pt_this->s_codeset));

	        /* upload codeset with brand */
	        i4_ret = _wzd_page_tv_remote_device_setup_save_and_upload_codeset(pt_this->ui1_cur_code_pos);
	        DBG_INFO( ("[Ln: %d] _wzd_page_tv_remote_device_setup_save_and_upload_codeset(), i4_ret = %d, pt_this->ui1_cur_code_pos = %d\n", __LINE__, i4_ret, pt_this->ui1_cur_code_pos));  

	        if(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_AUDIO_RECIEVER )
	        {
	            c_memset(pt_this->s_aud_amp_type, 0, DEV_SETUP_DB_NAME_LEN_MAX);
	            if(pt_this->ui1_cur_code_pos < pt_this->pt_codeset_list->t_codeset_list1.i4_length)
	            {
		            c_strncpy(pt_this->s_aud_amp_type, DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME, DEV_SETUP_DB_NAME_LEN_MAX);
	            }
	            else
	            {
		            c_strncpy(pt_this->s_aud_amp_type, DEV_DB_TYPE_AMPLIFIER_NAME, DEV_SETUP_DB_NAME_LEN_MAX);
	            }
	        }

	        if (pt_tag_query_info->b_is_to_clean)
	        {
	            a_dev_db_reset_bmc_query_info(pt_tag_query_info);
				
				/*free the codeset list*/
				a_dev_db_clean_codeset_list();
	        }

	        if (pt_this->ui1_codeset_num < WZD_DEV_SETUP_TRY_CODESET_MIN_NUM)
	        {
	            c_wgl_enable(pt_confirm_page->h_btn_retry, FALSE);
	        }
	        else
	        {
	            c_wgl_enable(pt_confirm_page->h_btn_retry, TRUE);
	        }
	       
	        pt_this->ui1_cur_code_pos ++;
	        DBG_INFO( ("[Ln: %d] pt_this->ui1_cur_code_pos = %d, pt_this->ui1_codeset_num = %d\n", __LINE__, pt_this->ui1_cur_code_pos, pt_this->ui1_codeset_num));

	        _wzd_page_tv_remote_device_setup_confirm_code_chang_lang(pt_this->ui1_cur_code_pos, TRUE);
	        
	        pt_this->e_pre_state = DEVICE_SETUP_SELECT_BRAND;
	        pt_this->e_state = DEVICE_SETUP_CODE_CONFIRM;
	        _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
	        pt_this->b_is_codeset_querying = FALSE;
            
#ifdef APP_UEI_SPINNER_SUPPORT
			/*hide spinner after get codeset for confirm remote conection page*/
			c_wgl_set_visibility(pt_this->h_animation, WGL_SW_HIDE);
			DBG_INFO( ("\n####%s(%d)get codese sucess\n",__FUNCTION__,__LINE__));
#endif
        }
    }
  
    if (b_need_to_update_brd_ui == TRUE)    
    {
        /* updater the brd info to the drop down list*/
        i4_ret = _wzd_page_tv_remote_device_setup_brand_drop_down_lb_set_text_update();
        if (i4_ret != WZDR_OK)
        {
            DBG_INFO( ("[Ln: %d] update brand listbox fail!!! i4_ret = %d\n", __LINE__, i4_ret));
            return;
        }
    }

    if(b_need_to_update_mdl_ui == TRUE)
    {
         /* updater the mdl info to the drop down list*/
        i4_ret = _wzd_page_tv_remote_device_setup_model_drop_down_lb_set_text_update();
        if (i4_ret != WZDR_OK)
        {
            DBG_INFO( ("[Ln: %d] update model listbox fail!!! i4_ret = %d\n", __LINE__, i4_ret));
            return;
        }
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_dev_db_online_query
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_dev_db_online_query(VOID* pv_tag, VOID* pv_nfy_param)
{    /* will use the retry notify if send msg fail*/
     wzd_request_context_switch(_wzd_page_tv_remote_device_setup_dev_db_online_query_hdlr, 
                                pv_tag,                    
                                pv_nfy_param,                    
                                NULL);    
     return;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_choose_box_btns_set_all_unfloat
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_choose_box_btns_set_all_unfloat(VOID)
{
    INT32 index = 0;
    WZD_SELECT_PAGE_T* pt_select_page = &t_g_device_setup_select_page;
   
    for (index = 0; index < WZD_CB_BTN_COUNT; index++)
    {
        RET_ON_ERR (c_wgl_float(pt_select_page->t_sel_box_btn[index].h_cb_btn_frm, FALSE, FALSE)); 
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_initial
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_initial(UINT32 ui4_sel_box_idx)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    WZD_SELECT_PAGE_T*                   pt_select_page = &t_g_device_setup_select_page;
    HANDLE_T                             h_txt_handle = NULL_HANDLE; 
    WGL_COLOR_INFO_T                     t_color_txt;
    WGL_FONT_INFO_T                      t_fnt_info;
    GL_RECT_T                    		 t_rect = {0};
    HANDLE_T                             h_sb_icon1 = NULL_HANDLE; 
    HANDLE_T                             h_sb_icon2 = NULL_HANDLE;
    WGL_IMG_INFO_T                       t_img_info;
    HANDLE_T                             h_checkmark_icon = NULL_HANDLE; 

    h_txt_handle = pt_select_page->t_sel_box_btn[ui4_sel_box_idx].h_cb_text;

    /* update color */
    c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
    t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (&t_color_txt)));

    /* update font size */
    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (&t_fnt_info),
                              NULL));

    /* update txt position */
    SET_RECT_BY_SIZE(&t_rect,
                     WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_X,
                     WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_Y,
                     WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_W,
                     WZD_DEVICE_SETUP_TYPE_BOX_BTN_TXT_H);
    
    RET_ON_ERR (c_wgl_move(h_txt_handle,
                           &t_rect,
                           WGL_NO_AUTO_REPAINT));
                   
    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                    WGL_CMD_TEXT_SET_ALIGN,
                    WGL_PACK(WGL_AS_CENTER_CENTER),
                    NULL));                            

    /* update icon 1 */
    h_sb_icon1 = pt_select_page->t_sel_box_btn[ui4_sel_box_idx].h_cb_icon_1;

    /* h_checkmark_icon = NULL_HANDLE */
	pt_this->b_type_show_checkbox = FALSE;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_enable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;

    c_wgl_do_cmd(h_sb_icon1,
                 WGL_CMD_GL_SET_IMAGE,
                 WGL_PACK(WGL_IMG_FG),
                 WGL_PACK(&t_img_info));                                
                              
    /* update icon2 */
    h_sb_icon2 = pt_select_page->t_sel_box_btn[ui4_sel_box_idx].h_cb_icon_2;
    
    /* icon2 move position */
    SET_RECT_BY_SIZE (& t_rect,
                  WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_X,
                  WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_Y,
                  WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_W,
                  WZD_DEVICE_SETUP_TYPE_BOX_BTN_ICON_2_H);
                  
    RET_ON_ERR (c_wgl_move(h_sb_icon2,
                           &t_rect,
                           WGL_NO_AUTO_REPAINT));
    
    RET_ON_ERR (c_wgl_do_cmd(h_sb_icon2,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL));
    
                         

    RET_ON_ERR (c_wgl_enable(pt_select_page->t_sel_box_btn[ui4_sel_box_idx].h_cb_icon_2, FALSE));
                                              
    return WZDR_OK;                      
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_hlt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_hlt(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    WZD_SELECT_PAGE_T*                   pt_select_page = &t_g_device_setup_select_page;
    HANDLE_T                             h_txt_handle = NULL_HANDLE; 
    WGL_COLOR_INFO_T                     t_color_txt; 

    h_txt_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_text;

    /* update color */
    c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
    t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_hlt_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_hlt_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_hlt_txt);
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (&t_color_txt)));
                              
    RET_ON_ERR (c_wgl_enable(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_icon_2, TRUE));

    return WZDR_OK;   
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_inp_page_set_losed_foucs_box_txt_initial
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_inp_page_set_losed_foucs_box_txt_initial(UINT32 ui4_idx)
{
    HANDLE_T                             h_txt_handle = NULL_HANDLE; 
    HANDLE_T                             h_sb_icon1 = NULL_HANDLE; 
    HANDLE_T                             h_sb_icon2   = NULL_HANDLE; 
    WGL_COLOR_INFO_T                     t_color_txt;
    WGL_FONT_INFO_T                      t_fnt_info;
    WGL_IMG_INFO_T                       t_img_info;
    HANDLE_T                             h_checkmark_icon = NULL_HANDLE; 
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    GL_RECT_T                    		 t_rect = {0};

    h_txt_handle = wzd_view_sel_box_get_txt_handle(ui4_idx);

    /* update color */
    c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
    t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (&t_color_txt)));

    /* update font size */
    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (&t_fnt_info),
                              NULL));

    /* update txt position */
    SET_RECT_BY_SIZE(&t_rect,
                     WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_X,
                     WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_Y,
                     WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_W,
                     WZD_DEVICE_SETUP_INPUT_BOX_BTN_TXT_H);
    
    RET_ON_ERR (c_wgl_move(h_txt_handle,
                           &t_rect,
                           WGL_NO_AUTO_REPAINT));
                   
    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                    WGL_CMD_TEXT_SET_ALIGN,
                    WGL_PACK(WGL_AS_CENTER_CENTER),
                    NULL));                            

    /* update icon 1 */
    h_sb_icon1 = wzd_view_sel_box_get_icon_1_handle(ui4_idx);

    /* h_checkmark_icon = NULL_HANDLE */
	pt_this->b_input_show_checkbox = FALSE;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_enable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;

    c_wgl_do_cmd(h_sb_icon1,
                 WGL_CMD_GL_SET_IMAGE,
                 WGL_PACK(WGL_IMG_FG),
                 WGL_PACK(&t_img_info));                                
                              
    /* update icon2 */
    h_sb_icon2 = wzd_view_sel_box_get_icon_2_handle(ui4_idx);
    
    /* icon2 move position */
    SET_RECT_BY_SIZE (& t_rect,
                  WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_X,
                  WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_Y,
                  WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_W,
                  WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_H);
                  
    RET_ON_ERR (c_wgl_move(h_sb_icon2,
                           &t_rect,
                           WGL_NO_AUTO_REPAINT));
    
    RET_ON_ERR (c_wgl_do_cmd(h_sb_icon2,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL));
    
    RET_ON_ERR (c_wgl_enable(h_sb_icon2, FALSE));                          
                    
    return WZDR_OK;                      
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_inp_page_set_foucsed_box_txt_hlt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_inp_page_set_foucsed_box_txt_hlt(UINT32 ui4_idx)
{
    HANDLE_T                             h_txt_handle = NULL_HANDLE;
    HANDLE_T                             h_sb_icon2 = NULL_HANDLE; 
    WGL_COLOR_INFO_T                     t_color_txt;
    WGL_FONT_INFO_T                      t_fnt_info;

    h_txt_handle = wzd_view_sel_box_get_txt_handle(ui4_idx);
    
    /* update color */
    c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
    t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_hlt_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_hlt_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_hlt_txt);
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (&t_color_txt)));

    /* update font size */
    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (&t_fnt_info),
                              NULL));
                              
    /* update icon2 */
    h_sb_icon2 = wzd_view_sel_box_get_icon_2_handle(ui4_idx);                          
    RET_ON_ERR (c_wgl_enable(h_sb_icon2, TRUE));                          
                    
    return WZDR_OK;                     
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_all_widget_anim_finish
 *
 * Description: check all widget's anim are finish or not.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE                  all widget's anim are finish.
 *          FALSE                 at least one widget's anim is not finish.
 ----------------------------------------------------------------------------*/
static BOOL _wzd_page_tv_remote_device_setup_all_widget_anim_finish (VOID)
{
    /* check get focus widget and lose focus widget */
    if ((at_anim_cb_get_focus_data_type.b_used) || (at_anim_cb_lose_focus_data_type.b_used))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_choose_box_btn_nfy_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_choose_box_btn_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;
    WZD_SELECT_PAGE_T*                      pt_select_page = &t_g_device_setup_select_page;
    /*add animation*/
    WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T*   pt_data = NULL;
    BOOL                                    b_set_checkmark = FALSE;
    
    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            /* if sel box scale animation is NOT finish, just return */
            if (!_wzd_page_tv_remote_device_setup_all_widget_anim_finish())
            {
                DBG_INFO( ("[WZD][DEVICE SETUP] anim not finish retun@LINE: %d.\n", __LINE__));
                return WZDR_OK;
            }

            switch( (UINT32)pv_param1 )
            {
            case BTN_SELECT:
                /* reset the flag */
			    b_set_checkmark = FALSE;

                c_memset(pt_this->s_type_name, 0, DEV_SETUP_DB_NAME_LEN_MAX + 1);
                pt_this->ui4_type_sel_idx = pt_this->ui4_sel_box_idx;
                c_strncpy(pt_this->s_type_name, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, DEV_SETUP_DB_NAME_LEN_MAX);

				/*temporary show check mark*/
				c_memset(pt_this->b_is_type_sel, 0, WZD_CB_BTN_COUNT);
				pt_this->b_is_type_sel[pt_this->ui4_type_sel_idx] = TRUE;

                /* need move icon2/text widget animation */
                if (!pt_this->b_type_show_checkbox)
                {
                    pt_this->b_type_show_checkbox = TRUE;
                    _wzd_page_tv_device_setup_type_set_checkmark();
                    b_set_checkmark = TRUE;
                }
                /* if the checkmark exist already, update state directly, else, update state after the anim is end*/
                if (!b_set_checkmark)
                {
                    if (pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_AUDIO_RECIEVER || pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_SOUND_BAR)
                    {
                        pt_this->e_pre_state = DEVICE_SETUP_CHOOSE_DEVICE;
                        pt_this->e_state = DEVICE_SETUP_SELECT_BRAND;
                    }
                    else
                    {
                        pt_this->e_pre_state = DEVICE_SETUP_CHOOSE_DEVICE;
                        pt_this->e_state = DEVICE_SETUP_SELECT_INPUT;
                    }

                    _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
                }
               
                
                break;

            case BTN_CURSOR_UP:
                if (pt_this->ui4_sel_box_idx >= WZD_CB_BTN_06 && pt_this->ui4_sel_box_idx <= WZD_CB_BTN_10) 
                {   
                
                    /* change image for the get focus box */
                    _wzd_page_tv_remote_device_setup_set_frm_bg_img(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx - WZD_CB_BTN_06].h_cb_btn_frm, h_g_wzd_img_selectbox_small_hlt_small);
                    
                    /* set scale down animation callback data */
                    pt_data = &at_anim_cb_lose_focus_data_type;
                    if (NULL == pt_data)
                    {
                        return WZDR_OK;
                    }
                    c_memset(pt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
                    pt_data->b_used = TRUE;
                    pt_data->h_anim_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm;
                    pt_data->ui4_index = pt_this->ui4_sel_box_idx;
                    pt_data->e_param = WZD_CALLBACK_PARAM_SCALE_DOWN;
                    
                    /* set scale down callback */
                    a_wzd_anim_set_cb(
                               pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm,
                               _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct,
                               (void *)pt_data);
                    
                    /* set scale up animation callback data */
                    pt_data = &at_anim_cb_get_focus_data_type;
                    if (NULL == pt_data)
                    {
                        return WZDR_OK;
                    }
                    c_memset(pt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
                    pt_data->b_used = TRUE;
                    pt_data->h_anim_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx - WZD_CB_BTN_06].h_cb_btn_frm;
                    pt_data->ui4_index = pt_this->ui4_sel_box_idx - WZD_CB_BTN_06;
                    pt_data->e_param = WZD_CALLBACK_PARAM_SCALE_UP;
                    
                    /* set scale up callback */
                    a_wzd_anim_set_cb(
                               pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx - WZD_CB_BTN_06].h_cb_btn_frm,
                               _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct,
                               (void *)pt_data);
                    
                    /* start scale down anim for lose focus box*/
                    _wzd_page_tv_remote_device_setup_sel_box_lose_focus_scale_down(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm);
                    
                    /* start scale up anim for get focus box*/
                    _wzd_page_tv_remote_device_setup_sel_box_get_focus_scale_up(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx - WZD_CB_BTN_06].h_cb_btn_frm);
                    
                    pt_this->ui4_sel_box_idx = pt_this->ui4_sel_box_idx - WZD_CB_BTN_06;
                    _wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_hlt();
                    RET_ON_ERR (c_wgl_float(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, TRUE, FALSE)); 

                    _wzd_page_tv_device_setup_type_update_checkmark();
                } 
                wzd_view_main_frm_repaint();
                
                break;

            case BTN_CURSOR_DOWN:
                if (pt_this->ui4_sel_box_idx >= WZD_CB_BTN_01 && pt_this->ui4_sel_box_idx <= WZD_CB_BTN_05) 
                {
                    /* change image for the get focus box */
                    _wzd_page_tv_remote_device_setup_set_frm_bg_img(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx + WZD_CB_BTN_06].h_cb_btn_frm, h_g_wzd_img_selectbox_small_hlt_small);
                    
                    /* set scale down animation callback data */
                    pt_data = &at_anim_cb_lose_focus_data_type;
                    if (NULL == pt_data)
                    {
                        return WZDR_OK;
                    }
                    c_memset(pt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
                    pt_data->b_used = TRUE;
                    pt_data->h_anim_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm;
                    pt_data->ui4_index = pt_this->ui4_sel_box_idx;
                    pt_data->e_param = WZD_CALLBACK_PARAM_SCALE_DOWN;
                    
                    /* set scale down callback */
                    a_wzd_anim_set_cb(
                               pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm,
                               _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct,
                               (void *)pt_data);
                    
                    /* set scale up animation callback data */
                    pt_data = &at_anim_cb_get_focus_data_type;
                    if (NULL == pt_data)
                    {
                        return WZDR_OK;
                    }
                    c_memset(pt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
                    pt_data->b_used = TRUE;
                    pt_data->h_anim_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx + WZD_CB_BTN_06].h_cb_btn_frm;
                    pt_data->ui4_index = pt_this->ui4_sel_box_idx + WZD_CB_BTN_06;
                    pt_data->e_param = WZD_CALLBACK_PARAM_SCALE_UP;
                    
                    /* set scale up callback */
                    a_wzd_anim_set_cb(
                               pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx + WZD_CB_BTN_06].h_cb_btn_frm,
                               _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct,
                               (void *)pt_data);
                    
                    /* start scale down anim for lose focus box*/
                    _wzd_page_tv_remote_device_setup_sel_box_lose_focus_scale_down(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm);
                    
                    /* start scale up anim for get focus box*/
                    _wzd_page_tv_remote_device_setup_sel_box_get_focus_scale_up(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx + WZD_CB_BTN_06].h_cb_btn_frm);
                    
                    pt_this->ui4_sel_box_idx = pt_this->ui4_sel_box_idx + WZD_CB_BTN_06;
                    _wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_hlt();

                } 
                else if (pt_this->ui4_sel_box_idx >= WZD_CB_BTN_05 && pt_this->ui4_sel_box_idx <= WZD_CB_BTN_10)
                {
                    /* change image for the lose focus box */
                    _wzd_page_tv_remote_device_setup_set_frm_bg_img(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, h_g_wzd_img_selectbox_small_hlt);

                    /* set scale down animation callback data */
                    pt_data = &at_anim_cb_lose_focus_data_type;
                    if (NULL == pt_data)
                    {
                        return WZDR_OK;
                    }
                    c_memset(pt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
                    pt_data->b_used = TRUE;
                    pt_data->h_anim_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm;
                    pt_data->ui4_index = pt_this->ui4_sel_box_idx;
                    pt_data->e_param = WZD_CALLBACK_PARAM_SCALE_DOWN;
                    
                    /* set scale down callback */
                    a_wzd_anim_set_cb(
                               pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm,
                               _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct,
                               (void *)pt_data);
                    
                    /* start scale down anim for lose focus box*/
                    _wzd_page_tv_remote_device_setup_sel_box_lose_focus_scale_down(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm);
                    
                    RET_ON_ERR (wzd_view_footer_set_focus (WZD_FOOTER_BTN_01, TRUE));
                }
                RET_ON_ERR (c_wgl_float(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, TRUE, FALSE));

                _wzd_page_tv_device_setup_type_update_checkmark();
                wzd_view_main_frm_repaint();
                
                break;
                
            case BTN_CURSOR_RIGHT:
                if (pt_this->ui4_sel_box_idx >= WZD_CB_BTN_01 && pt_this->ui4_sel_box_idx <= WZD_CB_BTN_09) 
                {
                    /* change image for the get focus box */
                    _wzd_page_tv_remote_device_setup_set_frm_bg_img(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx+1].h_cb_btn_frm, h_g_wzd_img_selectbox_small_hlt_small);
                    
                    /* set scale down animation callback data */
                    pt_data = &at_anim_cb_lose_focus_data_type;
                    if (NULL == pt_data)
                    {
                        return WZDR_OK;
                    }
                    c_memset(pt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
                    pt_data->b_used = TRUE;
                    pt_data->h_anim_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm;
                    pt_data->ui4_index = pt_this->ui4_sel_box_idx;
                    pt_data->e_param = WZD_CALLBACK_PARAM_SCALE_DOWN;
                    
                    /* set scale down callback */
                    a_wzd_anim_set_cb(
                               pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm,
                               _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct,
                               (void *)pt_data);
                    
                    /* set scale up animation callback data */
                    pt_data = &at_anim_cb_get_focus_data_type;
                    if (NULL == pt_data)
                    {
                        return WZDR_OK;
                    }
                    c_memset(pt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
                    pt_data->b_used = TRUE;
                    pt_data->h_anim_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx+1].h_cb_btn_frm;
                    pt_data->ui4_index = pt_this->ui4_sel_box_idx+1;
                    pt_data->e_param = WZD_CALLBACK_PARAM_SCALE_UP;
                    
                    /* set scale up callback */
                    a_wzd_anim_set_cb(
                               pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx+1].h_cb_btn_frm,
                               _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct,
                               (void *)pt_data);
                    
                    /* start scale down anim for lose focus box*/
                    _wzd_page_tv_remote_device_setup_sel_box_lose_focus_scale_down(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm);
                    
                    /* start scale up anim for get focus box*/
                    _wzd_page_tv_remote_device_setup_sel_box_get_focus_scale_up(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx+1].h_cb_btn_frm);
                    
                    pt_this->ui4_sel_box_idx = pt_this->ui4_sel_box_idx + 1;
                    _wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_hlt();                    
                }
                RET_ON_ERR (c_wgl_float(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, TRUE, FALSE));

                _wzd_page_tv_device_setup_type_update_checkmark();
                wzd_view_main_frm_repaint();

                break;
                
            case BTN_CURSOR_LEFT:
                if (pt_this->ui4_sel_box_idx >= WZD_CB_BTN_02 && pt_this->ui4_sel_box_idx <= WZD_CB_BTN_10) 
                {
                    
                    /* change image for the get focus box */
                    _wzd_page_tv_remote_device_setup_set_frm_bg_img(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx-1].h_cb_btn_frm, h_g_wzd_img_selectbox_small_hlt_small);
                    
                    /* set scale down animation callback data */
                    pt_data = &at_anim_cb_lose_focus_data_type;
                    if (NULL == pt_data)
                    {
                        return WZDR_OK;
                    }
                    c_memset(pt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
                    pt_data->b_used = TRUE;
                    pt_data->h_anim_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm;
                    pt_data->ui4_index = pt_this->ui4_sel_box_idx;
                    pt_data->e_param = WZD_CALLBACK_PARAM_SCALE_DOWN;
                    
                    /* set scale down callback */
                    a_wzd_anim_set_cb(
                               pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm,
                               _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct,
                               (void *)pt_data);
                    
                    /* set scale up animation callback data */
                    pt_data = &at_anim_cb_get_focus_data_type;
                    if (NULL == pt_data)
                    {
                        return WZDR_OK;
                    }
                    c_memset(pt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
                    pt_data->b_used = TRUE;
                    pt_data->h_anim_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx-1].h_cb_btn_frm;
                    pt_data->ui4_index = pt_this->ui4_sel_box_idx-1;
                    pt_data->e_param = WZD_CALLBACK_PARAM_SCALE_UP;
                    
                    /* set scale up callback */
                    a_wzd_anim_set_cb(
                               pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx-1].h_cb_btn_frm,
                               _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct,
                               (void *)pt_data);
                    
                    /* start scale down anim for lose focus box*/
                    _wzd_page_tv_remote_device_setup_sel_box_lose_focus_scale_down(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm);
                    
                    /* start scale up anim for get focus box*/
                    _wzd_page_tv_remote_device_setup_sel_box_get_focus_scale_up(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx-1].h_cb_btn_frm);
                    
                    pt_this->ui4_sel_box_idx = pt_this->ui4_sel_box_idx - 1;
                    _wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_hlt();
                }
                else if (pt_this->ui4_sel_box_idx >= WZD_CB_BTN_COUNT)
                {
                    DBG_ERROR(("%s(%d) pt_this->ui4_sel_box_idx(%d) overflow\n",
					__func__, __LINE__, pt_this->ui4_sel_box_idx));
                    return WZDR_FAIL;
                }
                RET_ON_ERR (c_wgl_float(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, TRUE, FALSE));

                _wzd_page_tv_device_setup_type_update_checkmark();
                wzd_view_main_frm_repaint();
                
                break;
                
            default:
                break;
            }
        }
        break;
    default:
        break;
    }
   
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_create_choose_box_frm
 *
 * Description: This function creates a choose box frame to display background
 *              image.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_create_choose_box_frm (HANDLE_T  h_parent)
                                              
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    WZD_SELECT_PAGE_T*  pt_select_page = &t_g_device_setup_select_page;
 

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      WZD_CB_FRM_X,
                      WZD_CB_FRM_Y,
                      WZD_CB_FRM_W,
                      WZD_CB_FRM_H);

    RET_ON_ERR (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     NULL,
                                     &pt_select_page->h_select_frm));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (pt_select_page->h_select_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (pt_select_page->h_select_frm, WGL_SW_HIDE));

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_create_text
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_create_text(
                           GL_RECT_T*               pt_rect,
                           HANDLE_T                 h_parent,
                           wgl_widget_proc_fct      pf_wdgt_proc,
                           UINT32                   ui4_style,
                           HANDLE_T*                ph_txt,
                           WGL_FONT_INFO_T*         pt_fnt_info,
                           UINT8                    ui1_align,
                           WGL_COLOR_INFO_T*        pt_color_bk,
                           WGL_COLOR_INFO_T*        pt_color_fg,
                           WGL_INSET_T*             pt_inset)
{
    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     pt_rect,
                                     pf_wdgt_proc,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     ph_txt));

    /* set font size */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (pt_fnt_info),
                              NULL));

    /* set content inset */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (pt_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (ui1_align),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) 0),
                              NULL));

    /* set theme */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (pt_color_bk)));

    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (pt_color_fg)));    

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (*ph_txt, WGL_SW_HIDE));

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_choose_box_create_icon
 *
 * Description: 
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_choose_box_create_icon(HANDLE_T     h_parent,
                                                                     HANDLE_T*    ph_widget,
                                                                     GL_RECT_T*   pt_rect)
{   
    RET_ON_ERR (c_wgl_create_widget(h_parent,
                              HT_WGL_WIDGET_ICON,
                              WGL_CONTENT_ICON_DEF,
                              WGL_BORDER_NULL,
                              pt_rect,
                              NULL,
                              255,
                              (VOID*)WGL_STL_GL_NO_BK,
                              NULL,
                              ph_widget));

    RET_ON_ERR (c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_ICON_SET_ALIGN,
                              WGL_PACK(WGL_AS_CENTER_CENTER),
                              NULL));

    RET_ON_ERR (c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE));
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_create_choose_box_button_widget
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_create_choose_box_button_widget(
                               HANDLE_T                h_parent,
                               const GL_RECT_T*        pt_rect,
                               wgl_widget_proc_fct     pf_wdgt_proc,
                               HANDLE_T*               ph_btn)
{
    INT32               i4_ret = WZDR_OK;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_color_info;

    /* create widget */
    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  pt_rect,
                                  pf_wdgt_proc,
                                  255,
                                  (VOID*) WZD_WIDGET_STYLE,
                                  NULL,
                                  ph_btn);
    RET_ON_ERR (i4_ret);                               

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_enable,    &t_g_wzd_color_base_frm_bk);
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_disable,   &t_g_wzd_color_base_frm_bk);
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_highlight, &t_g_wzd_color_base_frm_bk);

    i4_ret = c_wgl_do_cmd (h_parent,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK (WGL_CLR_BK), /* background color */
                           WGL_PACK(&t_color_info));
                           
    RET_ON_ERR (i4_ret);
    
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_selectbox_small;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_selectbox_small;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_selectbox_small_hlt;

    i4_ret = c_wgl_do_cmd (*ph_btn,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK (WGL_IMG_BK), /* background image */
                           WGL_PACK (&t_img_info));
                           
    RET_ON_ERR (i4_ret);
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_create_choose_box_buttons
 *
 * Description: This function creates the select box buttons.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_create_choose_box_buttons(VOID)
{
    GL_RECT_T           at_btn_rect[WZD_CB_BTN_COUNT] = WZD_CB_BTN_GET_RECTS();
    UINT8               ui1_i = 0;
    UINT8               ui1_align = 0; 
    UINT32              ui4_style;
    INT32               i4_ret = WZDR_OK;
    WGL_INSET_T         t_inset;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_IMG_INFO_T      t_img_info;
    GL_RECT_T           t_rect_icon_1, t_rect_icon_2, t_rect_text;
    WGL_COLOR_INFO_T    t_color_info_bg, t_color_info_fg;
    CHAR*               s_font_name = wzd_view_get_font_name();
    WZD_SELECT_PAGE_T*  pt_select_page = &t_g_device_setup_select_page;
                                                                       
    /* icon_1 rect */
    SET_RECT_BY_SIZE (& t_rect_icon_1,
                      -32 * WZD_UI_RATIO_W,
                      135 * WZD_UI_RATIO_W,
                      WZD_CB_BTN_W + 78 * WZD_UI_RATIO_W,
                      40 * WZD_UI_RATIO_W);

    /* icon_2 rect */
    SET_RECT_BY_SIZE (& t_rect_icon_2,
                      -32 * WZD_UI_RATIO_W,
                      170 * WZD_UI_RATIO_W,
                      WZD_CB_BTN_W + 70 * WZD_UI_RATIO_W,
                      40 * WZD_UI_RATIO_W);                    
    
    /* set text theme */
    SET_RECT_BY_SIZE (&t_rect_text,
                      33 * WZD_UI_RATIO_W,
                      190 * WZD_UI_RATIO_W,
                      343 * WZD_UI_RATIO_W,
                      80 * WZD_UI_RATIO_W);

    ui4_style = WGL_STL_TEXT_MULTILINE |
                WGL_STL_TEXT_MAX_128  |
                WGL_STL_TEXT_MAX_DIS_5_LINE |
                WZD_WIDGET_STYLE;
    
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_CENTER_CENTER;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);

    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    /* create buttons */
    for( ui1_i = 0; ui1_i < WZD_CB_BTN_COUNT ; ui1_i++ )
    { 
        i4_ret = _wzd_page_tv_remote_device_setup_create_choose_box_button_widget (pt_select_page->h_select_frm,
                                                                                   &at_btn_rect[ui1_i],
                                                                                   _wzd_page_tv_remote_device_setup_choose_box_btn_nfy_fct,
                                                                                   &((pt_select_page->t_sel_box_btn[ui1_i]).h_cb_btn_frm));
        RET_ON_ERR (i4_ret);

        i4_ret = _wzd_page_tv_remote_device_setup_create_text(&t_rect_text,
                                                              (pt_select_page->t_sel_box_btn[ui1_i]).h_cb_btn_frm,
                                                              NULL,
                                                              ui4_style,
                                                              &(pt_select_page->t_sel_box_btn[ui1_i]).h_cb_text,
                                                              &t_fnt_info,
                                                              ui1_align,
                                                              &t_color_info_bg,
                                                              &t_color_info_fg,
                                                              &t_inset);
        RET_ON_ERR (i4_ret);

        /* icon_1 create */
        i4_ret = _wzd_page_tv_remote_device_setup_choose_box_create_icon((pt_select_page->t_sel_box_btn[ui1_i]).h_cb_btn_frm,
                                                                          &(pt_select_page->t_sel_box_btn[ui1_i]).h_cb_icon_1,
                                                                          &t_rect_icon_1);   
        RET_ON_ERR (i4_ret);
                
        /* icon_2 create */
        i4_ret = _wzd_page_tv_remote_device_setup_choose_box_create_icon((pt_select_page->t_sel_box_btn[ui1_i]).h_cb_btn_frm,
                                                                          &(pt_select_page->t_sel_box_btn[ui1_i]).h_cb_icon_2,
                                                                          &t_rect_icon_2);   
        RET_ON_ERR (i4_ret);
    }

    /* update background image */
    for ( ui1_i = WZD_CB_BTN_06; ui1_i <= WZD_CB_BTN_10 ; ui1_i++ )
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_selectbox_small_1;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_selectbox_small_1;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_selectbox_small_hlt;

        i4_ret = c_wgl_do_cmd ((pt_select_page->t_sel_box_btn[ui1_i]).h_cb_btn_frm,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK (WGL_IMG_BK), /* background image */
                               WGL_PACK (&t_img_info));
                               
        RET_ON_ERR (i4_ret);
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_set_choose_box_buttons_content
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_set_choose_box_buttons_content (VOID)
{
    INT32               i4_ret = 0;
    UINT8               ui1_idx = 0;   
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_color_txt;
    WGL_FONT_INFO_T     t_fnt_info;
    WZD_SELECT_PAGE_T*  pt_select_page = &t_g_device_setup_select_page;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    DEV_DB_DEV_TYPE_CTGY_T  				e_dev_type_category = DEV_DB_DEV_TYPE_CTGY_NONE;

    WGL_HIMG_TPL_T wzd_tv_device_setup_img_choose[WZD_CB_BTN_COUNT] =
                    {h_g_wzd_img_device_bluray,
                     h_g_wzd_img_device_cable,
                     h_g_wzd_img_device_computer,
                     h_g_wzd_img_device_dvd,
                     h_g_wzd_img_device_dvr,
                     h_g_wzd_img_device_game,
                     h_g_wzd_img_device_sat,
                     h_g_wzd_img_device_vcr,
                     h_g_wzd_img_device_avr,
                     h_g_wzd_img_device_soundbar,
                    };
                    
    WGL_HIMG_TPL_T wzd_tv_device_setup_img_hlt_choose[WZD_CB_BTN_COUNT] =
                    {h_g_wzd_img_device_bluray_hlt,
                     h_g_wzd_img_device_cable_hlt,
                     h_g_wzd_img_device_computer_hlt,
                     h_g_wzd_img_device_dvd_hlt,
                     h_g_wzd_img_device_dvr_hlt,
                     h_g_wzd_img_device_game_hlt,
                     h_g_wzd_img_device_sat_hlt,
                     h_g_wzd_img_device_vcr_hlt,
                     h_g_wzd_img_device_avr_hlt,
                     h_g_wzd_img_device_soundbar_hlt,
                    };

    HANDLE_T        h_checkmark_icon = NULL_HANDLE;

    RET_ON_ERR( _wzd_page_tv_remote_device_setup_reset_type_info ());
    RET_ON_ERR( i4_ret );

	i4_ret = a_dev_db_get_dev_type_category(&e_dev_type_category);
	DBG_INFO( ("\n####%s(%d)a_dev_db_get_dev_type_category [return %d]\n",__FUNCTION__,__LINE__,i4_ret));
	
	i4_ret = a_cfg_get_gui_lang(pt_this->crn_s639_lang);
	DBG_INFO( ("\n####%s(%d)a_cfg_get_gui_lang [return %d]pt_this->crn_s639_lang=%s\n",__FUNCTION__,__LINE__,i4_ret,pt_this->crn_s639_lang));

	if((e_dev_type_category != DEV_DB_DEV_TYPE_CTGY_ALL_DEV)||(c_strncmp(pt_this->crn_s639_lang, pt_this->pre_s639_lang, ISO_639_LANG_LEN) != 0))
	{
        i4_ret = a_dev_db_update_dev_type(DEV_DB_DEV_TYPE_CTGY_ALL_DEV);
	    if (i4_ret != 0)
	    {
	        DBG_INFO( ("[Ln: %d] a_dev_db_update_dev_type fail! i4_ret = %d\n", __LINE__, i4_ret));
	        return WZDR_FAIL;
	    }
	    c_strncpy(pt_this->pre_s639_lang, pt_this->crn_s639_lang, ISO_639_LANG_LEN);
		DBG_INFO( ("\n####%s(%d)a_cfg_get_gui_lang [return %d]pt_this->pre_s639_lang=%s,pt_this->crn_s639_lang=%s\n",__FUNCTION__,__LINE__,i4_ret,pt_this->pre_s639_lang,pt_this->crn_s639_lang));
    }
    i4_ret = a_dev_db_get_dev_type_ex(pt_this->t_dev_type, &pt_this->ui4_type_num); 
    if (i4_ret != 0)
    {
        DBG_INFO( ("[Ln: %d] a_dev_db_get_dev_type_ex fail! i4_ret = %d\n", __LINE__, i4_ret));
        return WZDR_FAIL;
    }       
    
    if (pt_this->ui4_type_num < WZD_CB_BTN_COUNT) 
    {
        DBG_INFO( ("[Ln: %d]  pui4_dev_type_num = %d\n",  __LINE__, pt_this->ui4_type_num)); 
        return WZDR_FAIL;
    }
   
    for( ui1_idx = 0 ; ui1_idx < WZD_CB_BTN_COUNT ; ui1_idx ++ )
    {
        if (pt_this->b_is_type_sel[ui1_idx])
        {
           if (pt_this->ui4_sel_box_idx == ui1_idx)
           {
               h_checkmark_icon = h_g_wzd_img_checkmark_green_small;
           }
           else
           {
               h_checkmark_icon = NULL_HANDLE;
           }
        }
        else
        {
            h_checkmark_icon = NULL_HANDLE;
        }
    
        /* set select box icon_1 */
        c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_checkmark_icon;
        t_img_info.u_img_data.t_standard.t_disable   = h_checkmark_icon;
        t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;

        i4_ret = c_wgl_do_cmd((pt_select_page->t_sel_box_btn[ui1_idx]).h_cb_icon_1,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK(WGL_IMG_FG),
                               WGL_PACK(&t_img_info));                 
        RET_ON_ERR(i4_ret);
        
        /* set select box icon_2 */
        c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
        t_img_info.e_type = WGL_IMG_SET_BASIC;
        t_img_info.u_img_data.t_standard.t_enable    = wzd_tv_device_setup_img_hlt_choose[ui1_idx];
        t_img_info.u_img_data.t_standard.t_disable   = wzd_tv_device_setup_img_choose[ui1_idx];

        i4_ret = c_wgl_do_cmd((pt_select_page->t_sel_box_btn[ui1_idx]).h_cb_icon_2,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK(WGL_IMG_FG),
                               WGL_PACK(&t_img_info));                 
        RET_ON_ERR(i4_ret);

        /* set select box text */                           
        i4_ret =  c_wgl_do_cmd (pt_select_page->t_sel_box_btn[ui1_idx].h_cb_text,
                                WGL_CMD_TEXT_SET_TEXT,
                                WGL_PACK (pt_this->t_dev_type[ui1_idx].pw2s_txt_msg),
                                WGL_PACK (c_uc_w2s_strlen (pt_this->t_dev_type[ui1_idx].pw2s_txt_msg)));
        RET_ON_ERR (i4_ret);

        c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
        t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
        RET_ON_ERR (c_wgl_do_cmd (pt_select_page->t_sel_box_btn[ui1_idx].h_cb_text,
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK (WGL_CLR_TEXT),
                                  WGL_PACK (&t_color_txt)));

        c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
        c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

        t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        
        RET_ON_ERR (c_wgl_do_cmd (pt_select_page->t_sel_box_btn[ui1_idx].h_cb_text,
                                  WGL_CMD_GL_SET_FONT,
                                  WGL_PACK (&t_fnt_info),
                                  NULL));  

        c_wgl_enable((pt_select_page->t_sel_box_btn[ui1_idx]).h_cb_icon_2, FALSE);
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_input_src_id_map
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static UINT8 _wzd_page_tv_remote_device_setup_input_src_id_map (UINT8 ui1_input_id)
{ 
    UINT8        ui1_rec_num = 0;
    ISL_REC_T    t_isl_rec = {0};
    UINT8        ui1_show_idx = 0xFF;

    a_isl_get_num_rec(&ui1_rec_num);
	
    if (ui1_rec_num == 2)
    {
        DBG_INFO( ("[Ln: %d] ui1_rec_num = 2.\n", __LINE__));
        ui1_show_idx = ui1_input_id - 1;
    }   
    
    if (ui1_rec_num >= 3)
    {
        a_isl_get_rec_by_idx(ui1_input_id, &t_isl_rec); 
    
        if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type && ui1_input_id >= 2) /* HDMI */
        {
            ui1_show_idx = ui1_input_id - 2;
        }
        else if (DEV_AVC_COMP_VIDEO == t_isl_rec.t_avc_info.e_video_type || DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type) /* COMP */
        {
            ui1_show_idx = ui1_rec_num - 2;
        }
        else
        {
           DBG_INFO( ("[Ln: %d] ui1_input_id[%d] get show idx error!!!\n", __LINE__, ui1_input_id, ui1_show_idx));
        }
    }

	/*for RF TV source*/
    if (ui1_input_id == 0)
    {
        ui1_show_idx = ui1_rec_num - 1;
		DBG_INFO( ("[%s(%d)] ui1_show_idx=%d\n", __FUNCTION__,__LINE__,ui1_show_idx));
    }   

    return ui1_show_idx;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_get_device_paired_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_get_device_paired_info (VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    CHAR                                 s_type_name[DEV_SETUP_DB_NAME_LEN_MAX] = {0};
	CHAR                                 s_set_type_name[DEV_SETUP_DB_NAME_LEN_MAX] = {0};
    UINT8                                ui1_rec_num = 0;
    INT32                                i4_ret = WZDR_OK; 
    UINT8                                ui1_input_id;  
    UINT8                                ui1_show_idx = 0xFF;

    c_memset(pt_this->b_is_paired, 0, sizeof(pt_this->b_is_paired));  
    c_memset(pt_this->ui4_type_paired_count, 0, sizeof(pt_this->ui4_type_paired_count));  

    i4_ret = a_cfg_custom_get_device_type(0, s_type_name);
    DBG_INFO( ("[Ln: %d] [DEVICE LIST] i4_ret = %d, ui1_input_id = [0], s_type_name = [%s]!!!!\n", __LINE__, i4_ret, s_type_name));

	if ((c_strncmp(s_type_name,DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME,c_strlen(DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME) ) == 0)||
	    (c_strncmp(s_type_name,DEV_DB_TYPE_AMPLIFIER_NAME,c_strlen(DEV_DB_TYPE_AMPLIFIER_NAME) ) == 0))
	    
    {
        pt_this->b_is_aduio_paired    = TRUE;
        pt_this->b_is_soundbar_paired = FALSE;
        pt_this->ui4_type_paired_count[DEVICE_TYPE_SELECT_AUDIO_RECIEVER] ++;
        DBG_INFO( ("[Ln: %d] [DEVICE LIST] [Audio Reciever/Amplifer paired] count = %d\n", __LINE__, pt_this->ui4_type_paired_count[DEVICE_TYPE_SELECT_AUDIO_RECIEVER]));
    }
    else if (c_strncmp(s_type_name, pt_this->t_dev_type[DEVICE_TYPE_SELECT_SOUND_BAR].s_dev_view_name, c_strlen(pt_this->t_dev_type[DEVICE_TYPE_SELECT_SOUND_BAR].s_dev_view_name)) == 0)
	{
        pt_this->b_is_soundbar_paired = TRUE;
        pt_this->b_is_aduio_paired    = FALSE;
        pt_this->ui4_type_paired_count[DEVICE_TYPE_SELECT_SOUND_BAR] ++;
        DBG_INFO( ("[Ln: %d] [DEVICE LIST] [Sound bar paired] count = %d\n", __LINE__, pt_this->ui4_type_paired_count[DEVICE_TYPE_SELECT_SOUND_BAR]));
    }
    else
    {
        pt_this->b_is_aduio_paired    = FALSE;
        pt_this->b_is_soundbar_paired = FALSE;
        pt_this->ui4_type_paired_count[DEVICE_TYPE_SELECT_AUDIO_RECIEVER] = 0;
        pt_this->ui4_type_paired_count[DEVICE_TYPE_SELECT_SOUND_BAR] = 0;
    }

    a_isl_get_num_rec(&ui1_rec_num);
    
    for (ui1_input_id = 0; ui1_input_id < ui1_rec_num; ui1_input_id++)
    {
        i4_ret = a_cfg_custom_get_device_type(ui1_input_id, s_type_name);
		DBG_INFO( ("\n####%s(%d) s_type_name=%s\n",__FUNCTION__,__LINE__,s_type_name));
		
        if (i4_ret != WZDR_OK || c_strlen(s_type_name) == 0)
        {
            DBG_INFO( ("[Ln: %d] [DEVICE LIST] Continue!!!! i4_ret = %d, ui1_input_id = [%d], s_type_name = [%s].\n", __LINE__, i4_ret, ui1_input_id, s_type_name));
            continue;
        }

        ui1_show_idx = _wzd_page_tv_remote_device_setup_input_src_id_map(ui1_input_id);
        if (ui1_show_idx == 0XFF)
        {
            continue;
            DBG_INFO( ("[Ln: %d] [DEVICE LIST] ui1_input_id = [%d]<==========>ui1_show_idx = [%d].\n", __LINE__, ui1_input_id, ui1_show_idx));
        }

		for(UINT16 ui2_dev_type_mlm_idx = MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY;ui2_dev_type_mlm_idx<=MLM_WZD_KEY_DEVICE_SETUP_TYPE_SOUND_BAR;ui2_dev_type_mlm_idx++)
		{
			c_uc_w2s_to_ps(WZD_TEXT(ui2_dev_type_mlm_idx),s_set_type_name,DEV_SETUP_DB_NAME_LEN_MAX);
			DBG_INFO( ("\n####%s(%d) s_set_type_name=%s\n",__FUNCTION__,__LINE__,s_set_type_name));
			if (c_strncmp(s_type_name, s_set_type_name, c_strlen(s_set_type_name)) == 0)
			{
				pt_this->b_is_paired[ui1_show_idx][ui2_dev_type_mlm_idx-MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY] = TRUE;
	            pt_this->ui4_type_paired_count[ui2_dev_type_mlm_idx-MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY]++;
			}
			else
			{
				pt_this->b_is_paired[ui1_show_idx][ui2_dev_type_mlm_idx-MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY] = FALSE;
			}

		}
    }
    
    return WZDR_OK;                             
}                                
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_desc_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/ 
static INT32 _wzd_page_tv_remote_device_setup_desc_create(HANDLE_T     h_parent,
                                                          GL_RECT_T*   t_rect,
                                                          HANDLE_T*    ph_widget)
{
    UINT32              ui4_style = 0;
    UINT8               ui1_align = 0;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_COLOR_INFO_T    t_color_info_bg, t_color_info_fg;
    WGL_INSET_T         t_inset;
    CHAR*               s_font_name = wzd_view_get_font_name();
    
    /* set font theme */   
    ui4_style = WGL_STL_TEXT_MULTILINE |
                WGL_STL_TEXT_MAX_512  |
                WGL_STL_TEXT_MAX_DIS_5_LINE |
                WZD_WIDGET_STYLE;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_begin_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_begin_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_begin_txt);

    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_CENTER_CENTER;
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (_wzd_page_tv_remote_device_setup_create_text(
                t_rect,
                h_parent,
                NULL,
                ui4_style,
                ph_widget,
                &t_fnt_info,
                ui1_align,
                &t_color_info_bg,
                &t_color_info_fg,
                &t_inset));           

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_page_desc_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_page_desc_create(HANDLE_T   h_parent,
                                                                       GL_RECT_T* t_rect,
                                                                       HANDLE_T*  ph_widget)
{
    UINT32              ui4_style = 0;
    WGL_FONT_INFO_T     t_fnt_info;
    UINT8               ui1_align = 0;
    WGL_COLOR_INFO_T    t_color_info_bg, t_color_info_fg;
    WGL_INSET_T         t_inset;
    CHAR*               s_font_name = wzd_view_get_font_name();
    
    /* set font theme */   
    ui4_style = WGL_STL_TEXT_MULTILINE |
                WGL_STL_TEXT_MAX_512  |
                WGL_STL_TEXT_MAX_DIS_5_LINE |
                WZD_WIDGET_STYLE;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_cho_mode_txt_gray);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_cho_mode_txt_gray);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_cho_mode_txt_gray);

    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_CENTER_CENTER;
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (_wzd_page_tv_remote_device_setup_create_text(
                t_rect,
                h_parent,
                NULL,
                ui4_style,
                ph_widget,
                &t_fnt_info,
                ui1_align,
                &t_color_info_bg,
                &t_color_info_fg,
                &t_inset));           

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_reset_device_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_set_page_text(HANDLE_T h_parent, UTF16_T* pw2s_text)
{    
    /* set text */
    RET_ON_ERR (c_wgl_do_cmd(h_parent,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen(pw2s_text))));
          
    
    return WZDR_OK;        
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_set_page_text_size
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_set_page_text_size(HANDLE_T h_parent)
{ 
    WGL_FONT_INFO_T     t_fnt_info;
    CHAR*               s_font_name = wzd_view_get_font_name();

    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    /* set font size */
    RET_ON_ERR (c_wgl_do_cmd (h_parent,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (&t_fnt_info),
                              NULL));
    return WZDR_OK;  
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_sel_box_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_sel_box_nfy(
                    UINT32           ui4_msg,
                    VOID*            pv_param1,
                    VOID*            pv_param2)
{   
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this            = &t_g_tv_remote_device_setup;
    WZD_DEVICE_PAIR_DLG_PAGE_T*          pt_paired_dlg_page = &t_g_device_setup_device_pair_dlg_page;
    UINT8                                status             = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;
	UINT8								 ui1_rec_num 		= 0;
	BOOL                                 b_is_set_checkmark = FALSE;
    
    switch (ui4_msg)
    {
        case WZD_SEL_BOX_MSG_ITEM_FOCUSED:
            DBG_INFO( ( "[Ln: %d][WZD][SB] --- %d select box button is focused.\n", __LINE__, (UINT32)pv_param1));
            pt_this->ui1_input_sel_box_idx = (UINT8)(UINT32)pv_param1;
            _wzd_page_tv_remote_device_setup_inp_page_set_foucsed_box_txt_hlt((UINT32)pv_param1); 
            _wzd_page_tv_device_setup_input_update_checkmark();
            break;

        case WZD_SEL_BOX_MSG_ITEM_LOSE_FOCUSED:
            DBG_INFO( ( "[Ln: %d][WZD][SB] --- %d select box button is lose focused.\n", __LINE__, (UINT32)pv_param1));
			e_sb_pre_focused_box = wzd_view_sel_box_get_btn_idx((UINT32)pv_param1);
			_wzd_page_tv_remote_device_setup_inp_page_set_losed_foucs_box_txt_initial((UINT32)pv_param1);
            break;

        case WZD_SEL_BOX_MSG_KEY_INPUT:
            switch((UINT32)pv_param1)
            {
                case BTN_SELECT: 
                    b_is_set_checkmark = FALSE;
                    /* get origin input src */
                    c_memset(&pt_this->t_isl_rec, 0, sizeof(ISL_REC_T));
                    a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &pt_this->t_isl_rec);
                    pt_this->ui1_sel_src_idx = (UINT8)(UINT32)pv_param2;
                    pt_this->ui1_input_sel_box_idx = pt_this->ui1_sel_src_idx;
                    a_cfg_custom_get_wifi_remote_pair_status(&status);
					
					/*temporary show check mark*/
					c_memset(pt_this->b_is_input_sel, 0, WZD_CB_BTN_COUNT);
					pt_this->b_is_input_sel[pt_this->ui1_sel_src_idx] = TRUE;

					/* need move icon2/text widget animation */
                    if (!pt_this->b_input_show_checkbox)
                    {
                        b_is_set_checkmark = TRUE;
                        pt_this->b_input_show_checkbox = TRUE;
                        _wzd_page_tv_device_setup_input_set_checkmark();
                    }
					
					/* switch src */
                    if ((DEVICE_TYPE_SELECT_AUDIO_RECIEVER != pt_this->ui4_type_sel_idx) && (DEVICE_TYPE_SELECT_SOUND_BAR != pt_this->ui4_type_sel_idx))
                    {
                        _wzd_page_tv_remote_device_setup_change_input();
                    } 

					if (!b_is_set_checkmark)
					{
                        if ((DEVICE_TYPE_SELECT_CABLE_BOX== pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SATELLITE== pt_this->ui4_type_sel_idx))
                    	{
    						a_isl_get_num_rec(&ui1_rec_num);
    						if(pt_this->ui1_sel_src_idx == (ui1_rec_num-1))
                			{	
                				wzd_page_tv_setup_enter_from_tv_remote_device_setup_rf(pt_this->ui4_type_sel_idx);
    							return;
                			}
                    	}
								
                        if (pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP && status != WIFI_REMOTE_PAIR_STATUS_PAIRED)
                        {   
                            /* lose focus when the full dialog display */
                            wzd_view_sel_box_lose_focus(pt_this->ui1_input_sel_box_idx, FALSE);

                            /* Set dialog */    
                            _wzd_page_tv_remote_device_setup_full_dlg_set_content();
                            wzd_view_full_screen_dlg_show(FALSE);
                            t_g_device_setup_input_page.b_is_full_screen_dlg_show = TRUE;
    						
    						/* set device info */
    						_wzd_page_tv_remote_device_setup_set_device_info();  
    						DBG_INFO( ("[Ln: %d] set device info!!! \n", __LINE__)); 

                            c_timer_start(pt_paired_dlg_page->h_device_pair_dlg_timer, 
                                          5000,
                                          X_TIMER_FLAG_ONCE,
                                          _wzd_page_tv_remote_device_setup_timer_paired_show_dialog_nfy_fct,
                                          NULL);
    						
                        }
                        else 
                        {
                            pt_this->e_pre_state = DEVICE_SETUP_SELECT_INPUT;
                            pt_this->e_state = DEVICE_SETUP_SELECT_BRAND;
                            _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
                        }
                    }
     
                    break;

                case BTN_CURSOR_DOWN:
                {
                    /* save the lasted focus */
                    e_sb_pre_focused_box = (UINT32)pv_param2;
                    wzd_view_sel_box_lose_focus(e_sb_pre_focused_box, FALSE);

                    wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, TRUE);
                    
                    break;     
                }
                                 

                default:
                    break;
            }
            break;
        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_set_sel_box_theme
 *
 * Description:
 *
 * Inputs:  ui4_btn_idx        Select box button index
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_set_sel_box_theme (UINT8 ui1_rec_num)
{
    UINT32                       ui4_i = 0;
    HANDLE_T                     h_sb_txt = NULL_HANDLE;
    HANDLE_T                     h_sb_icon_1st = NULL_HANDLE;
    HANDLE_T                     h_sb_icon_2nd = NULL_HANDLE;
    WGL_COLOR_INFO_T             t_color_txt;
    WGL_FONT_INFO_T              t_fnt_info;
    GL_RECT_T                    t_rect = {0};

    for( ui4_i = 0; ui4_i < ui1_rec_num - 1; ui4_i++ )
    {       
        /* update text theme */
        h_sb_txt = wzd_view_sel_box_get_txt_handle(ui4_i);

        /* move position */
        SET_RECT_BY_SIZE(&t_rect,
                         WZD_SEL_BOX_BTN_TXT_X,
                         WZD_SEL_BOX_BTN_TXT_Y - (40 * WZD_UI_RATIO_W),
                         WZD_SEL_BOX_BTN_TXT_W,
                         WZD_SEL_BOX_BTN_TXT_H);

        RET_ON_ERR (c_wgl_move(h_sb_txt,
                               &t_rect,
                               WGL_NO_AUTO_REPAINT));
                       
        /* set alignment */
        RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
                                  WGL_CMD_TEXT_SET_ALIGN,
                                  WGL_PACK(WGL_AS_CENTER_CENTER),
                                  NULL));             

        /* set color */
        c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
        t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
        RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK (WGL_CLR_TEXT),
                                  WGL_PACK (&t_color_txt)));

        /* set font size */
        c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
        c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

        t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        
        RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
                                  WGL_CMD_GL_SET_FONT,
                                  WGL_PACK (&t_fnt_info),
                                  NULL));   

        /* update icon 1 theme */
        h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(ui4_i);
        
        /* move position */
        SET_RECT_BY_SIZE(&t_rect,
                         WZD_SEL_BOX_BTN_ICON_1_X,
                         WZD_SEL_BOX_BTN_ICON_1_Y  + 40 * WZD_UI_RATIO_W,
                         WZD_SEL_BOX_BTN_ICON_1_W  + 20 * WZD_UI_RATIO_W,
                         WZD_SEL_BOX_BTN_ICON_1_H);

        RET_ON_ERR (c_wgl_move(h_sb_icon_1st,
                               &t_rect,
                               WGL_NO_AUTO_REPAINT));
        
        RET_ON_ERR (c_wgl_do_cmd(h_sb_icon_1st,
                                 WGL_CMD_ICON_SET_ALIGN,
                                 WGL_PACK(WGL_AS_CENTER_CENTER),
                                 NULL));


        /* update icon 2 theme */
        h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(ui4_i);

        /* move position */
        SET_RECT_BY_SIZE (& t_rect,
                          WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_X,
                          WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_Y,
                          WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_W,
                          WZD_DEVICE_SETUP_INPUT_BOX_BTN_ICON_2_H);
                      
        RET_ON_ERR (c_wgl_move(h_sb_icon_2nd,
                               &t_rect,
                               WGL_NO_AUTO_REPAINT));

        RET_ON_ERR (c_wgl_do_cmd(h_sb_icon_2nd,
                                 WGL_CMD_ICON_SET_ALIGN,
                                 WGL_PACK(WGL_AS_CENTER_CENTER),
                                 NULL));                         
    }
                         
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_update_sel_box_txt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_set_sel_box_content(VOID)
{
    INT32               i4_ret = WZDR_OK;
    UINT16              ui2_src_idx = 0;
    UINT8               ui2_idx = 0;
    UINT8               ui1_show_idx = 0xFF;
    UINT8               ui1_rec_num = 0;
    WGL_IMG_INFO_T      t_img_info;
    WGL_HIMG_TPL_T      h_inp_src_img;
    WGL_HIMG_TPL_T      h_inp_src_hlt_img;
    ISL_REC_T           t_isl_rec;
    HANDLE_T            h_sb_text = NULL_HANDLE;
    HANDLE_T            h_sb_icon = NULL_HANDLE;
    CHAR                s_src_name[DEV_SETUP_DB_NAME_LEN_MAX + 1] = {0};
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
	CHAR           		s_rf_name[DEV_SETUP_DB_NAME_LEN_MAX + 1] = "Coaxial";//RF->Coaxial
	UTF16_T           	w2s_rf_name[DEV_SETUP_DB_NAME_LEN_MAX + 1] = {0};
	HANDLE_T            h_checkmark_icon = NULL_HANDLE;

    c_memset(pt_this->aui1_input_src_id, 0, sizeof(pt_this->aui1_input_src_id));

    a_isl_get_num_rec(&ui1_rec_num);
	
	if ((DEVICE_TYPE_SELECT_CABLE_BOX == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SATELLITE == pt_this->ui4_type_sel_idx))
    {
	    RET_ON_ERR (_wzd_page_tv_remote_device_setup_set_sel_box_theme(ui1_rec_num+1));
	}
	else
	{
	    RET_ON_ERR (_wzd_page_tv_remote_device_setup_set_sel_box_theme(ui1_rec_num));
	}

    /* Iterate all the input sources */
    for (ui2_src_idx = 1; ui2_src_idx < ui1_rec_num; ui2_src_idx++)
    { 
        c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
        i4_ret = a_isl_get_rec_by_idx(ui2_src_idx, &t_isl_rec); 
        if (i4_ret != ISLR_OK) {
            DBG_INFO( ("[Ln: %d]  ui2_idx = %d, ui1_rec_num = %d, i4_ret = %d!!!!\n",  __LINE__, ui2_src_idx, ui1_rec_num, i4_ret)); 
            return WZDR_FAIL;
        }
        c_uc_w2s_to_ps(a_isl_get_display_name(&t_isl_rec), s_src_name, DEV_SETUP_DB_NAME_LEN_MAX);

        if (t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
        {
            /* ISL first is AV src, then should remove it */
            continue;
        }
        else if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
        {
            if ( DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type )            /* HDMI */
            {
                h_inp_src_img = h_g_wzd_img_icon_hdmi_gray;
                h_inp_src_hlt_img = h_g_wzd_img_icon_hdmi_white;
            }
            else if ( DEV_AVC_COMP_VIDEO == t_isl_rec.t_avc_info.e_video_type 
                || DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type)          /* COMP */
            {   
                h_inp_src_img = h_g_wzd_img_icon_comp_gray;
                h_inp_src_hlt_img = h_g_wzd_img_icon_comp_white;
            }
            else
            {
                  /* do nothing*/
            }
        }
        else
        {
              /* do nothing*/
        }
        
        ui1_show_idx = _wzd_page_tv_remote_device_setup_input_src_id_map((UINT8)ui2_src_idx);
        if (ui1_show_idx == 0XFF)
        {
            continue;
        }        

        pt_this->aui1_input_src_id[ui1_show_idx] = t_isl_rec.ui1_id;
        
        /* set sel box text */
        h_sb_text = wzd_view_sel_box_get_txt_handle(ui1_show_idx);
        c_wgl_do_cmd(h_sb_text,
                     WGL_CMD_TEXT_SET_TEXT,
                     WGL_PACK (a_isl_get_display_name(&t_isl_rec)),                             
                     WGL_PACK ((UINT16)0xFFFF)); 
        
        /* set sel box icon 2 */
        c_memset(&t_img_info, 0, sizeof(t_img_info));
        t_img_info.e_type = WGL_IMG_SET_BASIC;
        t_img_info.u_img_data.t_standard.t_enable  = h_inp_src_hlt_img;
        t_img_info.u_img_data.t_standard.t_disable = h_inp_src_img;
                
        h_sb_icon = wzd_view_sel_box_get_icon_2_handle((INT32)ui1_show_idx);
        RET_ON_ERR ( c_wgl_do_cmd(h_sb_icon,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK(WGL_IMG_FG),
                                  WGL_PACK(&t_img_info))); 
        c_wgl_enable(h_sb_icon, FALSE);                          
    }
	
	/*ADD RF BOX*/
	if ((DEVICE_TYPE_SELECT_CABLE_BOX == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SATELLITE == pt_this->ui4_type_sel_idx))
	{
		DBG_INFO( ("\n####%s(%d)ui1_rec_num=%d\n",__FUNCTION__,__LINE__,ui1_rec_num));
		c_uc_ps_to_w2s(s_rf_name,w2s_rf_name,DEV_SETUP_DB_NAME_LEN_MAX);
		/* set sel box text for the RF*/
	    h_sb_text = wzd_view_sel_box_get_txt_handle(ui1_rec_num-1);
	    c_wgl_do_cmd(h_sb_text,
	                 WGL_CMD_TEXT_SET_TEXT,
	                 WGL_PACK (w2s_rf_name),                             
	                 WGL_PACK ((UINT16)0xFFFF)); 
	    
	    /* set sel box icon 2 for the RF*/
	    c_memset(&t_img_info, 0, sizeof(t_img_info));
	    t_img_info.e_type = WGL_IMG_SET_BASIC;
	    t_img_info.u_img_data.t_standard.t_enable  = h_g_wzd_input_icon_rf_white;
	    t_img_info.u_img_data.t_standard.t_disable = h_g_wzd_input_icon_RF;
	            
	    h_sb_icon = wzd_view_sel_box_get_icon_2_handle((INT32)ui1_rec_num-1);
	    RET_ON_ERR ( c_wgl_do_cmd(h_sb_icon,
	                              WGL_CMD_GL_SET_IMAGE,
	                              WGL_PACK(WGL_IMG_FG),
	                              WGL_PACK(&t_img_info))); 
	    c_wgl_enable(h_sb_icon, FALSE); 

		pt_this->aui1_input_src_id[ui1_rec_num-1] = 0;
	}

    /* set sel box icon 1 */
    for (ui2_idx = 0; ui2_idx < ui1_rec_num; ui2_idx++)
    {
        h_sb_icon = wzd_view_sel_box_get_icon_1_handle(ui2_idx);

        if (pt_this->b_is_input_sel[ui2_idx])
        {
            if (pt_this->ui1_input_sel_box_idx == ui2_idx)
            {
                h_checkmark_icon = h_g_wzd_img_checkmark_green_large;
                pt_this->b_input_show_checkbox = TRUE;
            }
            else
            {
                h_checkmark_icon = NULL_HANDLE;
            }
        }
        else
        {
            h_checkmark_icon = NULL_HANDLE;
        }
        
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_disable = h_checkmark_icon;
        t_img_info.u_img_data.t_standard.t_enable = h_checkmark_icon;
        t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;
        
        c_wgl_do_cmd(h_sb_icon,
                     WGL_CMD_GL_SET_IMAGE,
                     WGL_PACK(WGL_IMG_FG),
                     WGL_PACK(&t_img_info));  
        
    }

    return WZDR_OK;   
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_create_sel_box
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_create_sel_box (VOID)
{
    UINT8                                ui1_rec_num = 0;
    WZD_VIEW_SEL_BOX_INFO_T              t_sel_box_info;
	WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    
    c_memset(&t_sel_box_info, 0 , sizeof(WZD_VIEW_SEL_BOX_INFO_T));

	
	/* reset previous focused select box button */
	e_sb_pre_focused_box = DEV_SETUP_SEL_BOX_BTN_01;
 
    RET_ON_ERR (a_isl_get_num_rec(&ui1_rec_num));

	/*add RF BOX*/
	if ((DEVICE_TYPE_SELECT_CABLE_BOX == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SATELLITE == pt_this->ui4_type_sel_idx))
    {
	    t_sel_box_info.ui4_index_total = ui1_rec_num;
    }
    else
	{
	    t_sel_box_info.ui4_index_total = ui1_rec_num - 1;
	}

    t_sel_box_info.pf_data_chg_nfy = _wzd_page_tv_remote_device_setup_sel_box_nfy;

    wzd_view_sel_box_set_info_data (&t_sel_box_info);

    if (pt_this->ui1_input_sel_box_idx >= t_sel_box_info.ui4_index_total)
    {
        pt_this->ui1_input_sel_box_idx = 0;
    }

    /* initial select box content */
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_set_sel_box_content());

    return WZDR_OK;       
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_text_it_work_btn
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_text_it_work_btn (const UTF16_T*  suffix_w2s, UTF16_T* ps_w2s,UINT32 ui4_len)
{    
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup; 
        
    switch (pt_this->ui4_type_sel_idx)
    {
    case DEVICE_TYPE_SELECT_BLURAY_PLAYER:        
    case DEVICE_TYPE_SELECT_CABLE_BOX:
    case DEVICE_TYPE_SELECT_COMPUTER:
    case DEVICE_TYPE_SELECT_DVD_PLAYER:
    case DEVICE_TYPE_SELECT_DVR:
    case DEVICE_TYPE_SELECT_GAME:
    case DEVICE_TYPE_SELECT_SATELLITE:
    case DEVICE_TYPE_SELECT_VCR:
        //c_uc_ps_to_w2s(pt_this->t_dev_type[pt_this->ui4_type_sel_idx]., w2s_dev_view_name, DEV_DB_NAME_LEN_MAX);
        c_uc_w2s_strncpy(ps_w2s, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].pw2s_txt_msg, ui4_len);
        c_uc_w2s_strncat(ps_w2s, suffix_w2s, ui4_len);
        break;
    case DEVICE_TYPE_SELECT_AUDIO_RECIEVER:
    case DEVICE_TYPE_SELECT_SOUND_BAR:
        c_uc_w2s_strncpy(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_BTN_AVR_IT_WORKED), ui4_len);
        break;         
    default:
        break;
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_text_connect
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_text_connect (const UTF16_T* prifix_w2s, UTF16_T* ps_w2s)
{    
    UINT32 ui4_len;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    
    c_uc_w2s_strcpy(ps_w2s, prifix_w2s);
        
    switch (pt_this->ui4_type_sel_idx)
    {
    case DEVICE_TYPE_SELECT_BLURAY_PLAYER:   
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY_MSG), ui4_len);
        break;
        
    case DEVICE_TYPE_SELECT_CABLE_BOX:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_CABLE_BOX_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_CABLE_BOX_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_COMPUTER:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_COMPUTER_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_COMPUTER_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_DVD_PLAYER:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_DVD_PLAYER_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_DVD_PLAYER_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_DVR:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_DVR_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_DVR_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_GAME:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_GAME_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_GAME_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_SATELLITE:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_SATELLITE_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_SATELLITE_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_VCR:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_VCR_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_VCR_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_AUDIO_RECIEVER:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_AUDIO_RECIEVER_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_AUDIO_RECIEVER_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_SOUND_BAR:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_SOUND_BAR_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_SOUND_BAR_MSG), ui4_len);
        break; 
        
    default:
        break;
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_msg_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_msg_create(HANDLE_T     h_parent,
                                          GL_RECT_T*   t_rect,
                                          HANDLE_T*    ph_widget)
{
    UINT32              ui4_style = 0;
    WGL_FONT_INFO_T     t_fnt_info;
    UINT8               ui1_align = 0;
    WGL_COLOR_INFO_T    t_color_info_bg, t_color_info_fg;
    WGL_INSET_T         t_inset;
    CHAR*               s_font_name = wzd_view_get_font_name();

    /* set font theme */   
    ui4_style = WGL_STL_TEXT_MULTILINE |
                WGL_STL_TEXT_MAX_512  |
                WGL_STL_TEXT_MAX_DIS_5_LINE |
                WZD_WIDGET_STYLE;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_cho_mode_txt_gray);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_cho_mode_txt_gray);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_cho_mode_txt_gray);

    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_CENTER_CENTER;
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (_wzd_page_tv_remote_device_setup_create_text(t_rect,
                                                          h_parent,
                                                          NULL,
                                                          ui4_style,
                                                          ph_widget,
                                                          &t_fnt_info,
                                                          ui1_align,
                                                          &t_color_info_bg,
                                                          &t_color_info_fg,
                                                          &t_inset));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_page_msg_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_page_msg_create(HANDLE_T     h_parent,
                                                                      GL_RECT_T*   t_rect,
                                                                      HANDLE_T*    ph_widget)
{
    UINT32              ui4_style = 0;
    WGL_FONT_INFO_T     t_fnt_info;
    UINT8               ui1_align = 0;
    WGL_COLOR_INFO_T    t_color_info_bg, t_color_info_fg;
    WGL_INSET_T         t_inset;
    CHAR*               s_font_name = wzd_view_get_font_name();

    /* set font theme */   
    ui4_style = WGL_STL_TEXT_MULTILINE |
                WGL_STL_TEXT_MAX_512  |
                WGL_STL_TEXT_MAX_DIS_5_LINE |
                WZD_WIDGET_STYLE;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_cho_mode_txt_wihte);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_cho_mode_txt_wihte);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_cho_mode_txt_wihte);

    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_CENTER_CENTER;
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (_wzd_page_tv_remote_device_setup_create_text(t_rect,
                                           h_parent,
                                           NULL,
                                           ui4_style,
                                           ph_widget,
                                           &t_fnt_info,
                                           ui1_align,
                                           &t_color_info_bg,
                                           &t_color_info_fg,
                                           &t_inset));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_box_frm_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_box_frm_create(HANDLE_T              h_parent,
                                                             GL_RECT_T             t_rect,
                                                             wgl_widget_proc_fct   pf_wgl_nfy_fct,
                                                             HANDLE_T*             ph_frame)
{
    RET_ON_ERR ( c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wgl_nfy_fct,
                                 255,
                                 NULL,
                                 0,
                                 ph_frame));

    RET_ON_ERR ( c_wgl_set_visibility (*ph_frame, WGL_SW_HIDE));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_manually_edit_box_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_manually_edit_box_create (HANDLE_T             h_parent,
                                                               GL_RECT_T            t_rect,
                                                               wgl_widget_proc_fct  pf_wdgt_proc,
                                                               HANDLE_T*            ph_widget)
{
    INT32                       i4_ret = WZDR_OK;
    UINT32                      ui4_style;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_IMG_INFO_T              t_img_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_EB_KEY_MAP_T            t_eb_key_map;

    ui4_style = WGL_STL_EB_MAX_CHAR_256;
    
    /* create editbox */
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 240,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Font */
    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    /* Set txt color */
    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_wzd_color_seti_lst_col_dis_txt;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_wzd_color_seti_lst_col_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_wzd_color_seti_lst_col_dis_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set the cursor highlight */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_EB_ENABLE_CURSOR_HT,
                           WGL_PACK (TRUE),
                           NULL);
    RET_ON_ERR(i4_ret);

    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_wzd_color_seti_lst_col_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_wzd_color_seti_lst_col_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_wzd_color_seti_lst_col_txt;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_EB_CURSOR),
                           WGL_PACK(& t_clr_info));
    RET_ON_ERR(i4_ret);

    /* Set background images */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable     = h_g_wzd_img_textBox_register;
    t_img_info.u_img_data.t_standard.t_highlight  = h_g_wzd_img_textBox_register_highlight;
    t_img_info.u_img_data.t_standard.t_disable    = h_g_wzd_img_textBox_register;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);
    
    /* Set pos style */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CURSOR_CHAR,
                          (VOID*)WZD_CUSTOM_TEXT("|"),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS),
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS));
    RET_ON_ERR(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_backsapce = BTN_KB_BACKSPACE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    RET_ON_ERR(i4_ret);
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_edit_box_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_edit_box_create (HANDLE_T             h_parent,
                                                               GL_RECT_T            t_rect,
                                                               wgl_widget_proc_fct  pf_wdgt_proc,
                                                               HANDLE_T*            ph_widget)
{
    INT32                       i4_ret = WZDR_OK;
    UINT32                      ui4_style;
    WGL_INSET_T                 t_inset;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_IMG_INFO_T              t_img_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_EB_KEY_MAP_T            t_eb_key_map;
    WGL_BDR_TIMG_ICON_INFO_T    t_title_icon_info;  

    /* underline */
    UTF16_T                     w2s_cursor =(UTF16_T) 0x005F;

    ui4_style = WGL_STL_EB_MAX_CHAR_256;
    
    /* create editbox */
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = WZD_DEVICE_SETUP_EDIT_BOX_LEFT_INSET;
    t_inset.i4_right    = WZD_DEVICE_SETUP_EDIT_BOX_RIGHT_INSET;
    t_inset.i4_top      = WZD_DEVICE_SETUP_EDIT_BOX_TOP_INSET;
    t_inset.i4_bottom   = WZD_DEVICE_SETUP_EDIT_BOX_BOTTOM_INSET + 8;
   
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Cnt Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left = 25 * WZD_UI_RATIO_W;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Font */
    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    /* Set txt color */
    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_wzd_color_seti_lst_col_dis_txt;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_wzd_color_seti_lst_col_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_wzd_color_seti_lst_col_dis_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set the cursor highlight */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_EB_ENABLE_CURSOR_HT,
                           WGL_PACK (TRUE),
                           NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_EB_SET_CURSOR_CHAR,
                           (VOID*)(&w2s_cursor),
                           NULL);
    RET_ON_ERR(i4_ret);

    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_wzd_color_seti_lst_col_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_wzd_color_seti_lst_col_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_wzd_color_seti_lst_col_txt;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_EB_CURSOR),
                           WGL_PACK(& t_clr_info));
    RET_ON_ERR(i4_ret);

    /* Set background images */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable     = h_g_wzd_img_textBox_register;
    t_img_info.u_img_data.t_standard.t_highlight  = h_g_wzd_img_textBox_register_highlight;
    t_img_info.u_img_data.t_standard.t_disable    = h_g_wzd_img_textBox_register;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     WZD_DEVICE_SETUP_EDIT_BOX_HL_ICON_X,
                     WZD_DEVICE_SETUP_EDIT_BOX_HL_ICON_Y,
                     WZD_DEVICE_SETUP_EDIT_BOX_HL_ICON_W,
                     WZD_DEVICE_SETUP_EDIT_BOX_HL_ICON_H);
                     
    c_memset(&t_title_icon_info, 0, sizeof(WGL_BDR_TIMG_ICON_INFO_T));
    t_title_icon_info.t_rc_ref  = t_rect;
    t_title_icon_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_ICON_INFO,
                          WGL_PACK(&t_title_icon_info),
                          WGL_PACK(NULL));
    RET_ON_ERR(i4_ret);
    
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_wzd_img_text_focus;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_text_focus;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_wzd_img_text_focus;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push               = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_ICON,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL) );
    RET_ON_ERR(i4_ret);

    /* Set pos style */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CURSOR_CHAR,
                          (VOID*)WZD_CUSTOM_TEXT("|"),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS),
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS));
    RET_ON_ERR(i4_ret);

    /* Set Char support */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_CHAR_SUPPORT),
                          WGL_PACK(WGL_EB_CHAR_SUPPORT));
    RET_ON_ERR(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_backsapce = BTN_KB_BACKSPACE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Border Title */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_wzd_color_seti_lst_col_txt;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_wzd_color_seti_lst_col_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_wzd_color_seti_lst_col_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_brand_eb_clear_icon_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_brand_eb_clear_icon_create (HANDLE_T h_parent)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WZD_BRAND_PAGE_T*   pt_brand_page = &t_g_device_setup_brand_page;


    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     WZD_DEVICE_SETUP_EB_X + WZD_DEVICE_SETUP_EB_W - 103 * WZD_UI_RATIO_W,
                     WZD_DEVICE_SETUP_EB_Y + 77 * WZD_UI_RATIO_W, 
                     80 * WZD_UI_RATIO_W,
                     WZD_DEVICE_SETUP_EB_H);
        
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &pt_brand_page->h_brand_eb_clr);
    RET_ON_ERR(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(pt_brand_page->h_brand_eb_clr,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wdk_vkb_eb_clear;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wdk_vkb_eb_clear_hlt;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wdk_vkb_eb_clear;
    i4_ret = c_wgl_do_cmd(pt_brand_page->h_brand_eb_clr,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));    
    RET_ON_ERR(i4_ret);

    RET_ON_ERR(c_wgl_set_visibility(pt_brand_page->h_brand_eb_clr, WGL_SW_HIDE));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_model_eb_clear_icon_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_model_eb_clear_icon_create (HANDLE_T h_parent)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WZD_MODEL_PAGE_T*   pt_model_page = &t_g_device_setup_model_page;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     WZD_DEVICE_SETUP_EB_X + WZD_DEVICE_SETUP_EB_W - 103 * WZD_UI_RATIO_W,
                     WZD_DEVICE_SETUP_EB_Y + 77 * WZD_UI_RATIO_W,
                     80 * WZD_UI_RATIO_W,
                     WZD_DEVICE_SETUP_EB_H);
        
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &pt_model_page->h_model_eb_clr);
    RET_ON_ERR(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(pt_model_page->h_model_eb_clr,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wdk_vkb_eb_clear;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wdk_vkb_eb_clear_hlt;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wdk_vkb_eb_clear;
    i4_ret = c_wgl_do_cmd(pt_model_page->h_model_eb_clr,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));    
    RET_ON_ERR(i4_ret);

    RET_ON_ERR(c_wgl_set_visibility(pt_model_page->h_model_eb_clr, WGL_SW_HIDE));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_model_drop_down_lb_proc
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_model_drop_down_lb_proc(
                 HANDLE_T            h_widget,
                 UINT32              ui4_msg,
                 VOID*               pv_param1,
                 VOID*               pv_param2)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this = &t_g_tv_remote_device_setup;
    WZD_MODEL_PAGE_T*                     pt_model_page = &t_g_device_setup_model_page;
    UINT32                                ui4_mdl_lb_hlt_index = 0;
    UINT32                                ui4_elem_num = 0;
    UINT32                                ui4_first_vsb_idx = 0;
    UINT32                                ui4_last_vsb_idx = 0;
    INT32                                 i4_ret = WZDR_OK;
    GL_RECT_T                             t_rect;
    
    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            switch( (UINT32)pv_param1 )
            {
            case BTN_SELECT:
                i4_ret = c_wgl_do_cmd(pt_model_page->h_model_lb,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui4_mdl_lb_hlt_index),
                              NULL);
                RET_ON_ERR(i4_ret);

                pt_this->ui4_mdl_sel_idx = (UINT32)ui4_mdl_lb_hlt_index;
                DBG_INFO( ("[Ln: %d] [MODEL_BTN_SELECT] ui4_mdl_lb_hlt_index = %d ui1_model_idx=%d.\n", __LINE__, ui4_mdl_lb_hlt_index, pt_this->ui4_mdl_sel_idx));

                RET_ON_ERR (_wzd_page_tv_remote_device_setup_select_mdl_eb_set_text(pt_this->ui4_mdl_sel_idx));
                RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
                RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, FALSE));    /* Set focus to next button. */
                RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_hlt_icon, WGL_SW_HIDE)); 
                RET_ON_ERR (wzd_view_main_frm_repaint());

                return WZDR_OK;
 
            case BTN_CURSOR_UP:
            
                i4_ret = c_wgl_do_cmd (pt_model_page->h_model_lb,
                                       WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                                       WGL_PACK(&ui4_first_vsb_idx),
                                       NULL) ;
                RET_ON_ERR(i4_ret);
                
                i4_ret = c_wgl_do_cmd(pt_model_page->h_model_lb,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui4_mdl_lb_hlt_index),
                                      NULL);
                RET_ON_ERR(i4_ret);
                
                i4_ret = c_wgl_do_cmd(pt_model_page->h_model_lb,
                                      WGL_CMD_LB_GET_ELEM_NUM,
                                      WGL_PACK(&ui4_elem_num),
                                      NULL);
                RET_ON_ERR(i4_ret);
                
                if (ui4_mdl_lb_hlt_index == 0)
                {
                    DBG_INFO( ("[Ln: %d] [MODEL_BTN_CURSOR_UP] ui4_mdl_lb_hlt_index = %d, ui4_first_vsb_idx = %d\n", __LINE__, ui4_mdl_lb_hlt_index, ui4_first_vsb_idx)); 
                    RET_ON_ERR (a_vkb_set_focus_ex(pt_model_page->h_model_vkb)); /* set focus to editbox */
                    RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_hlt_icon, WGL_SW_HIDE)); 
                    RET_ON_ERR (wzd_view_main_frm_repaint());
                    return WZDR_OK;
                }
                if (ui4_mdl_lb_hlt_index == ui4_first_vsb_idx)
                {
                    DBG_INFO( ("[Ln: %d] [MODEL_BTN_CURSOR_UP] ui4_mdl_lb_hlt_index = %d, ui4_first_vsb_idx = %d\n", __LINE__, ui4_mdl_lb_hlt_index, ui4_first_vsb_idx)); 
                    RET_ON_ERR (wzd_view_main_frm_repaint());
                    break;
                }
                else
                {
                    DBG_INFO( ("[Ln: %d] [MODEL_BTN_CURSOR_UP] ui4_mdl_lb_hlt_index = %d, ui4_first_vsb_idx = %d\n", __LINE__, ui4_mdl_lb_hlt_index, ui4_first_vsb_idx)); 
                    SET_RECT_BY_SIZE(&t_rect,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_X,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_Y + (ui4_mdl_lb_hlt_index - ui4_first_vsb_idx - 1) * 37 * WZD_UI_RATIO_W + (ui4_mdl_lb_hlt_index - ui4_first_vsb_idx  - 1) * 1,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_H);
                }
                RET_ON_ERR (c_wgl_move(pt_model_page->h_model_lb_hlt_icon,
                                       &t_rect,
                                       WGL_NO_AUTO_REPAINT)); 
                RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_hlt_icon, WGL_SW_RECURSIVE)); 
                RET_ON_ERR (c_wgl_float(pt_model_page->h_model_lb_hlt_icon, TRUE, FALSE));
                RET_ON_ERR (wzd_view_main_frm_repaint());                

                break;                

            case BTN_CURSOR_DOWN:
                i4_ret = c_wgl_do_cmd (pt_model_page->h_model_lb,
                                       WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                                       WGL_PACK(&ui4_first_vsb_idx),
                                       NULL) ;
                RET_ON_ERR(i4_ret);
            
                i4_ret = c_wgl_do_cmd (pt_model_page->h_model_lb,
                                       WGL_CMD_LB_GET_LAST_VISIBLE_INDEX,
                                       WGL_PACK(&ui4_last_vsb_idx),
                                       NULL) ;
                RET_ON_ERR(i4_ret);   
                
                i4_ret = c_wgl_do_cmd(pt_model_page->h_model_lb,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui4_mdl_lb_hlt_index),
                                      NULL);
                RET_ON_ERR(i4_ret);
                
                i4_ret = c_wgl_do_cmd(pt_model_page->h_model_lb,
                                      WGL_CMD_LB_GET_ELEM_NUM,
                                      WGL_PACK(&ui4_elem_num),
                                      NULL);
                RET_ON_ERR(i4_ret);
                
                DBG_INFO( ("[Ln: %d] [MODEL_BTN_CURSOR_DOWN] ui4_mdl_lb_hlt_index = %d, ui4_first_vsb_idx = %d, ui4_last_vsb_idx = %d\n", __LINE__, ui4_mdl_lb_hlt_index, ui4_first_vsb_idx, ui4_last_vsb_idx)); 
                if (ui4_mdl_lb_hlt_index == (ui4_elem_num - 1))
                {
                    DBG_INFO( ("[Ln: %d] [MODEL_BTN_CURSOR_DOWN] ui4_mdl_lb_hlt_index = %d, ui4_first_vsb_idx = %d, ui4_last_vsb_idx = %d\n", __LINE__, ui4_mdl_lb_hlt_index, ui4_first_vsb_idx, ui4_last_vsb_idx)); 
                    return WZDR_OK;
                }
                else if (ui4_mdl_lb_hlt_index == ui4_last_vsb_idx)
                {
                    DBG_INFO( ("[Ln: %d] [MODEL_BTN_CURSOR_DOWN] ui4_mdl_lb_hlt_index = %d, ui4_first_vsb_idx = %d, ui4_last_vsb_idx = %d\n", __LINE__, ui4_mdl_lb_hlt_index, ui4_first_vsb_idx, ui4_last_vsb_idx)); 
                    SET_RECT_BY_SIZE(&t_rect,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_X,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_Y + 5 * 37 * WZD_UI_RATIO_W + 8 * WZD_UI_RATIO_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_H );
                }
                else if (ui4_last_vsb_idx < 6)
                {
                    DBG_INFO( ("[Ln: %d] [MODEL_BTN_CURSOR_DOWN] ui4_mdl_lb_hlt_index = %d, ui4_first_vsb_idx = %d, ui4_last_vsb_idx = %d\n", __LINE__, ui4_mdl_lb_hlt_index, ui4_first_vsb_idx, ui4_last_vsb_idx)); 
                    SET_RECT_BY_SIZE(&t_rect,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_X,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_Y + (ui4_mdl_lb_hlt_index + 1) * 37 * WZD_UI_RATIO_W + 2 * WZD_UI_RATIO_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_H );
                }
                else
                {
                    DBG_INFO( ("[Ln: %d] [MODEL_BTN_CURSOR_DOWN] ui4_mdl_lb_hlt_index = %d, ui4_first_vsb_idx = %d, ui4_last_vsb_idx = %d\n", __LINE__, ui4_mdl_lb_hlt_index, ui4_first_vsb_idx, ui4_last_vsb_idx)); 
                    SET_RECT_BY_SIZE(&t_rect,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_X,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_Y + (ui4_mdl_lb_hlt_index - ui4_first_vsb_idx + 1) * 37 * WZD_UI_RATIO_W + 2 * WZD_UI_RATIO_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_H );
                }
                
                RET_ON_ERR (c_wgl_move(pt_model_page->h_model_lb_hlt_icon,
                                       &t_rect,
                                       WGL_NO_AUTO_REPAINT)); 
                RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_hlt_icon, WGL_SW_RECURSIVE)); 
                RET_ON_ERR (c_wgl_float(pt_model_page->h_model_lb_hlt_icon, TRUE, FALSE));
                RET_ON_ERR(wzd_view_main_frm_repaint());

                break;

            default:
                break;
            }
        }
        break;
    default:
        break;
    }

    c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
                                       
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_model_vkb_nfy_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_model_vkb_nfy_fct (VOID*   pv_tag,
                                                                 UINT32  ui4_msg,
                                                                 VOID*   pv_param1,
                                                                 VOID*   pv_param2)
{
    WZD_MODEL_PAGE_T* pt_model_page = &t_g_device_setup_model_page;
    UINT32*           pui4_key_code = (UINT32*) pv_param1;
    UTF16_T           str_prefix[DEV_SETUP_DB_NAME_LEN_MAX + 1]= L"";
    CHAR              mdl_prefix[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    INT32             i4_ret = WZDR_OK;
    HANDLE_T          h_focus = NULL_HANDLE;
    HANDLE_T          h_cancel_btn = 0;
    UINT8             i_top_row = 0;
    UINT32            ui4_elem_num = 0;
    BOOL              b_is_bottom_row = FALSE;
    BOOL              b_is_visible = FALSE;
    GL_RECT_T         t_rect = {0}; 
    UINT32            ui4_mdl_lb_hlt_index = 0;
    UINT32            ui4_first_vsb_idx = 0;
    UINT32            ui4_last_vsb_idx = 0;
                                                
    if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        DBG_INFO( ("[Ln: %d]  ============ enter VKB_MSG_DLG_KEY_INPUT!!!\n",  __LINE__));

        if( BTN_SELECT == *pui4_key_code )
        { 
            RET_ON_ERR(c_wgl_get_focus(&h_focus));
            if (h_focus == pt_model_page->h_model_eb)
            {
                return WDK_NO_ACTION;
            } 
            else
            {
                i4_ret = _wzd_page_tv_remote_device_setup_model_drop_down_lb_update();
                if (i4_ret != WZDR_OK)
                {
                    DBG_INFO( ("[Ln: %d] Model_drop_down_lb_update FAIL! i4_ret = %d\n", __LINE__, i4_ret)); 
                    RET_ON_ERR(c_wgl_get_visibility(pt_model_page->h_model_lb_frm, &b_is_visible)); 
                    if ( b_is_visible == TRUE )
                    {
                        RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));
                    }
                }
                RET_ON_ERR (wzd_view_main_frm_repaint());

                return WDKR_OK;
            }  
        }        
        else if( BTN_CURSOR_DOWN == *pui4_key_code )
        {           
            RET_ON_ERR(c_wgl_get_visibility(pt_model_page->h_model_lb, &b_is_visible)); 
            RET_ON_ERR(c_wgl_get_focus(&h_focus));
            RET_ON_ERR((c_wgl_do_cmd(pt_model_page->h_model_lb,
                        WGL_CMD_LB_GET_ELEM_NUM,
                        WGL_PACK(&ui4_elem_num),
                        NULL)));

            i4_ret = c_wgl_do_cmd (pt_model_page->h_model_lb,
                                       WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                                       WGL_PACK(&ui4_first_vsb_idx),
                                       NULL) ;
            RET_ON_ERR(i4_ret);

            i4_ret = c_wgl_do_cmd (pt_model_page->h_model_lb,
                                       WGL_CMD_LB_GET_LAST_VISIBLE_INDEX,
                                       WGL_PACK(&ui4_last_vsb_idx),
                                       NULL) ;
            RET_ON_ERR(i4_ret);  

            i4_ret = c_wgl_do_cmd(pt_model_page->h_model_lb,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui4_mdl_lb_hlt_index),
                                      NULL);
            RET_ON_ERR(i4_ret);

            DBG_INFO( ("[%s(Ln: %d)] BTN_CURSOR_DOWN focus to LB! i4_ret = %d,ui4_mdl_lb_hlt_index=%d,ui4_first_vsb_idx=%d,ui4_last_vsb_idx=%d\n", __FUNCTION__,__LINE__, i4_ret,ui4_mdl_lb_hlt_index,ui4_first_vsb_idx,ui4_last_vsb_idx)); 

            if ((h_focus == pt_model_page->h_model_eb) && (b_is_visible == TRUE) && (ui4_elem_num != 0))
            {
				if(ui4_elem_num < 6)
				{
	                SET_RECT_BY_SIZE(&t_rect,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_X,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_Y + (ui4_mdl_lb_hlt_index) * 37 * WZD_UI_RATIO_W + 2 * WZD_UI_RATIO_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_H );

				}
				else
				{
					if(ui4_mdl_lb_hlt_index == ui4_first_vsb_idx)
					{
		                SET_RECT_BY_SIZE(&t_rect,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_X,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_Y,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_H );
					}
					else if(ui4_mdl_lb_hlt_index == ui4_last_vsb_idx)
					{
		                SET_RECT_BY_SIZE(&t_rect,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_X,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_Y + 5 * 37 * WZD_UI_RATIO_W + 2 * WZD_UI_RATIO_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_H );

					}
					else
					{
		                SET_RECT_BY_SIZE(&t_rect,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_X,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_Y + (ui4_mdl_lb_hlt_index - ui4_first_vsb_idx) * 37 * WZD_UI_RATIO_W + (ui4_mdl_lb_hlt_index - ui4_first_vsb_idx) * 2,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_H );

					}
				}
                RET_ON_ERR (c_wgl_move(pt_model_page->h_model_lb_hlt_icon,
                                       &t_rect,
                                       WGL_NO_AUTO_REPAINT)); 

                c_wgl_set_focus(pt_model_page->h_model_lb, WGL_NO_AUTO_REPAINT);
                RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_hlt_icon, WGL_SW_NORMAL)); 
                RET_ON_ERR (c_wgl_float(pt_model_page->h_model_lb_hlt_icon, TRUE, FALSE));
                RET_ON_ERR (wzd_view_main_frm_repaint());
                return WDK_NO_ACTION;
            } 
            else if ((h_focus == pt_model_page->h_model_eb) && (b_is_visible == FALSE))
            {
                RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_02, FALSE));    /* Set focus to back button. */
                RET_ON_ERR (wzd_view_main_frm_repaint());
                return WDK_NO_ACTION;
            }
            else 
            {
                i4_ret = a_vkb_current_is_bottom_row(pt_model_page->h_model_vkb, &h_cancel_btn, &b_is_bottom_row);
                DBG_INFO( ("[Ln: %d]: [MODEL_BTN_CURSOR_DOWN] b_is_bottom_row = %d\n", __LINE__, b_is_bottom_row));
                if ((TRUE == b_is_bottom_row) && (WDKR_OK == i4_ret))
                {
                    RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_02, FALSE));    /* Set focus to back button. */
                    RET_ON_ERR (wzd_view_main_frm_repaint());
                    return WDK_NO_ACTION;
                }  
                return WDKR_OK;
            }
        } 
        else if (BTN_CURSOR_UP == *pui4_key_code )
        { 
            RET_ON_ERR(c_wgl_get_focus(&h_focus));

            if (h_focus == pt_model_page->h_model_eb)
            {
                return WDK_NO_ACTION;  
            }
            else
            {
                i_top_row = a_vkb_current_get_row_index(pt_model_page->h_model_vkb);
                if (i_top_row == 0)
                {
                    DBG_INFO( ("[Ln: %d]: [MODEL_BTN_CURSOR_UP] i_top_row = %d\n", __LINE__, i_top_row));
                    return WDK_NO_ACTION;
                }
                return WDKR_OK;  
            }
            
        }        
        else if (BTN_CURSOR_LEFT == *pui4_key_code )
        {   
            RET_ON_ERR(c_wgl_get_focus(&h_focus));
           
            if (h_focus == pt_model_page->h_model_eb)
            {
                i4_ret = a_vkb_do_cmd (pt_model_page->h_model_vkb,
                                      VKB_CMD_GET_EB_CONTENT,
                                      (VOID*) str_prefix,
                                      (VOID*) (UINT32) DEV_SETUP_DB_NAME_LEN_MAX);
                RET_ON_ERR(i4_ret);    

                c_memset(mdl_prefix, 0, sizeof(mdl_prefix));
                c_uc_w2s_to_ps(str_prefix, mdl_prefix, DEV_SETUP_DB_NAME_LEN_MAX);

                if ( c_uc_w2s_strlen(str_prefix) == 1 )
                {
                    str_prefix[c_uc_w2s_strlen(str_prefix) - 1] = '\0';

                    i4_ret = a_vkb_do_cmd (pt_model_page->h_model_vkb,
                                           VKB_CMD_SET_INITIAL_TEXT,
                                          (VOID*)str_prefix,
                                          (VOID*)0XFF);
                    RET_ON_ERR(i4_ret); 

                    RET_ON_ERR(c_wgl_get_visibility(pt_model_page->h_model_lb_frm, &b_is_visible)); 
                    if ( b_is_visible == TRUE )
                    {
                       RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));
                    }
                    RET_ON_ERR (wzd_view_main_frm_repaint());                    
                }
                else if ( c_uc_w2s_strlen(str_prefix) == 0 )
                {
                    RET_ON_ERR(c_wgl_get_visibility(pt_model_page->h_model_lb_frm, &b_is_visible)); 
                    if ( b_is_visible == TRUE )
                    {
                       RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));
                    }
                    RET_ON_ERR (wzd_view_main_frm_repaint());
                    
                    return WDK_NO_ACTION;
                }
                else 
                {
                    str_prefix[c_uc_w2s_strlen(str_prefix) - 1] = '\0';

                    i4_ret = a_vkb_do_cmd (pt_model_page->h_model_vkb,
                                           VKB_CMD_SET_INITIAL_TEXT,
                                          (VOID*)str_prefix,
                                          (VOID*)0XFF);
                    RET_ON_ERR(i4_ret);  
                    
                    i4_ret = _wzd_page_tv_remote_device_setup_model_drop_down_lb_update();
                    if (i4_ret != WZDR_OK)
                    {
                        DBG_INFO( ("[Ln: %d] [MODEL_BTN_CURSOR_LEFT] Model_drop_down_lb_update FAIL! i4_ret = %d\n", __LINE__, i4_ret)); 
                        RET_ON_ERR(c_wgl_get_visibility(pt_model_page->h_model_lb_frm, &b_is_visible)); 
                        if ( b_is_visible == TRUE )
                        {
                           RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));
                        }
                        RET_ON_ERR (wzd_view_main_frm_repaint());
                    }
                    else
                    {
                        SET_RECT_BY_SIZE(&t_rect,
                                         WZD_DEVICE_SETUP_LB_HT_ICON_X,
                                         WZD_DEVICE_SETUP_LB_HT_ICON_Y,
                                         WZD_DEVICE_SETUP_LB_HT_ICON_W,
                                         WZD_DEVICE_SETUP_LB_HT_ICON_H );

                        RET_ON_ERR (c_wgl_move(pt_model_page->h_model_lb_hlt_icon,
                                               &t_rect,
                                               WGL_NO_AUTO_REPAINT)); 
                    
                        RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_NORMAL));
                        RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb, WGL_SW_NORMAL));
                        RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_hlt_icon, WGL_SW_HIDE)); 
                        RET_ON_ERR (wzd_view_main_frm_repaint());
                    } 
                }
                
                return WDK_NO_ACTION;
            }
            else if (a_vkb_current_get_col_index(pt_model_page->h_model_vkb) == 0)
            {
                RET_ON_ERR (a_vkb_set_focus_ex(pt_model_page->h_model_vkb));
                RET_ON_ERR (a_vkb_repaint(pt_model_page->h_model_vkb));
                RET_ON_ERR (wzd_view_main_frm_repaint());
                return WDK_NO_ACTION;
            } 
            else 
            {
                return WZDR_OK; 
            }  
        }       
        else if (BTN_CURSOR_RIGHT == *pui4_key_code )
        {
            return WZDR_OK;
        }  
        else if (((BTN_DIGIT_0 <= *pui4_key_code) && (BTN_DIGIT_9 >= *pui4_key_code)) 
            ||((BTN_KB_NULL <= *pui4_key_code) && (BTN_KB_HYPER >= *pui4_key_code)))
        {
            RET_ON_ERR(c_wgl_get_focus(&h_focus));
            if (h_focus == pt_model_page->h_model_eb)
            {                
                i4_ret = _wzd_page_tv_remote_device_setup_model_drop_down_lb_update();
                if (i4_ret != WZDR_OK)
                {
                    DBG_INFO( ("[Ln: %d] Model_drop_down_lb_update FAIL! i4_ret = %d\n", __LINE__, i4_ret)); 
                    RET_ON_ERR(c_wgl_get_visibility(pt_model_page->h_model_lb_frm, &b_is_visible)); 
                    if ( b_is_visible == TRUE )
                    {
                        RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));
                    }
                }
                RET_ON_ERR (wzd_view_main_frm_repaint());
            }

            return WDKR_OK;
        }
        else
        {
            return WZDR_OK;
        }
    }
    else if (ui4_msg == VKB_MSG_DLG_KEY_EB_CLEAR)
    {        
        if (BTN_CURSOR_RIGHT == *pui4_key_code )
        {
            c_wgl_get_focus(&h_focus);

            if (h_focus == pt_model_page->h_model_eb_clr)
            {
                RET_ON_ERR (a_vkb_set_focus(pt_model_page->h_model_vkb));
                RET_ON_ERR (wzd_view_main_frm_repaint());
                return WDK_NO_ACTION;
            }

            return WZDR_OK;  
        }
        else if (BTN_CURSOR_DOWN == *pui4_key_code )
        {
            return WDK_NO_ACTION;
        }
        else if (BTN_SELECT == *pui4_key_code )
        {
            i4_ret = a_vkb_do_cmd (pt_model_page->h_model_vkb,
                                   VKB_CMD_CLEAR_TEXT,
                                  (VOID*)NULL,
                                  (VOID*)NULL);
            RET_ON_ERR(i4_ret);    

            RET_ON_ERR(c_wgl_get_visibility(pt_model_page->h_model_lb_frm, &b_is_visible)); 
            if ( b_is_visible == TRUE )
            {
                RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));     
            }
            RET_ON_ERR (wzd_view_main_frm_repaint());

            return WDK_NO_ACTION;
        }
        else 
        {
            return WZDR_OK;
        }
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_brand_lb_hlt_icon_create
 *
 * Description: This function creates a icon widget to display images while
 *              listbox item select.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_brand_lb_hlt_icon_create (VOID)
{
    WGL_INSET_T                 t_inset;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_IMG_INFO_T              t_img_info;
    WZD_BRAND_PAGE_T*           pt_brand_page = &t_g_device_setup_brand_page;

    SET_RECT_BY_SIZE (&t_rect,
                      (INT32)WZD_DEVICE_SETUP_LB_HT_ICON_X,
                      (INT32)WZD_DEVICE_SETUP_LB_HT_ICON_Y,
                      (INT32)WZD_DEVICE_SETUP_LB_HT_ICON_W,
                      (INT32)WZD_DEVICE_SETUP_LB_HT_ICON_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (pt_brand_page->h_brand_lb_frm,
                                  HT_WGL_WIDGET_ICON,
                                  WGL_CONTENT_ICON_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  NULL,
                                  255,
                                 (VOID*)(0),
                                  NULL,
                                  &pt_brand_page->h_brand_lb_hlt_icon));
                                  
    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (c_wgl_do_cmd (pt_brand_page->h_brand_lb_hlt_icon,
                              WGL_CMD_ICON_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set icon alignment */
    RET_ON_ERR (c_wgl_do_cmd(pt_brand_page->h_brand_lb_hlt_icon,
                             WGL_CMD_ICON_SET_ALIGN,
                             (VOID*)WGL_AS_LEFT_CENTER,
                             NULL));
                             
    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (pt_brand_page->h_brand_lb_hlt_icon,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),   /* background */
                              WGL_PACK (& t_color_info)));
    /* set image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_dropdown_brand_hlt;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_dropdown_brand_hlt;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_dropdown_brand_hlt;

    RET_ON_ERR (c_wgl_do_cmd (pt_brand_page->h_brand_lb_hlt_icon,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK), /* Background image */
                              WGL_PACK(& t_img_info)));
                              
    /* set visibility, default hidden */
    RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_hlt_icon, WGL_SW_HIDE));                          

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_model_lb_hlt_icon_create
 *
 * Description: This function creates a icon widget to display images while
 *              listbox item select.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_model_lb_hlt_icon_create (VOID)
{
    WGL_INSET_T                 t_inset;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_IMG_INFO_T              t_img_info;
    WZD_MODEL_PAGE_T*           pt_model_page = &t_g_device_setup_model_page;

    SET_RECT_BY_SIZE (&t_rect,
                      (INT32)WZD_DEVICE_SETUP_LB_HT_ICON_X,
                      (INT32)WZD_DEVICE_SETUP_LB_HT_ICON_Y,
                      (INT32)WZD_DEVICE_SETUP_LB_HT_ICON_W,
                      (INT32)WZD_DEVICE_SETUP_LB_HT_ICON_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (pt_model_page->h_model_lb_frm,
                                  HT_WGL_WIDGET_ICON,
                                  WGL_CONTENT_ICON_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  NULL,
                                  255,
                                 (VOID*)(0),
                                  NULL,
                                  &pt_model_page->h_model_lb_hlt_icon));
                                  
    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (c_wgl_do_cmd (pt_model_page->h_model_lb_hlt_icon,
                              WGL_CMD_ICON_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set icon alignment */
    RET_ON_ERR (c_wgl_do_cmd(pt_model_page->h_model_lb_hlt_icon,
                             WGL_CMD_ICON_SET_ALIGN,
                             (VOID*)WGL_AS_LEFT_CENTER,
                             NULL));
                             
    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (pt_model_page->h_model_lb_hlt_icon,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),   /* background */
                              WGL_PACK (& t_color_info)));
    /* set image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_dropdown_brand_hlt;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_dropdown_brand_hlt;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_dropdown_brand_hlt;

    RET_ON_ERR (c_wgl_do_cmd (pt_model_page->h_model_lb_hlt_icon,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK), /* Background image */
                              WGL_PACK(& t_img_info)));
                              
    /* set visibility, default hidden */
    RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_hlt_icon, WGL_SW_HIDE));                          

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_brand_drop_down_lb_proc
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_brand_drop_down_lb_proc(HANDLE_T h_widget,
                                                                      UINT32   ui4_msg,
                                                                      VOID*    pv_param1,
                                                                      VOID*    pv_param2)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this = &t_g_tv_remote_device_setup;
    WZD_BRAND_PAGE_T*                     pt_brand_page = &t_g_device_setup_brand_page;
    UINT32                                ui4_brd_lb_hlt_index = 0;
    UINT32                                ui4_first_vsb_idx = 0;
    UINT32                                ui4_last_vsb_idx = 0;
    UINT32                                ui4_elem_num = 0;
    INT32                                 i4_ret = WZDR_OK;
    GL_RECT_T                             t_rect = {0};
    
    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            switch( (UINT32)pv_param1 )
            {
            case BTN_SELECT:
                
#ifdef APP_UEI_SPINNER_SUPPORT
				/*hide the spinner when select the item from the dropdown list when the spinner is show*/
				c_wgl_set_visibility(pt_this->h_animation, WGL_SW_HIDE);
				DBG_INFO( ("\n####%s(%d)HIDE animation lb proc sel\n",__FUNCTION__,__LINE__));
#endif
				
                i4_ret = c_wgl_do_cmd(pt_brand_page->h_brand_lb,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui4_brd_lb_hlt_index),
                                      NULL);
                RET_ON_ERR(i4_ret);

                pt_this->ui4_brd_sel_idx = (UINT32)ui4_brd_lb_hlt_index;
                DBG_INFO( ("[Ln: %d][BRAND_BTN_SELECT]ui4_brd_lb_hlt_index = %d ui4_brd_sel_idx=%d.\n", __LINE__, ui4_brd_lb_hlt_index, pt_this->ui4_brd_sel_idx));
                RET_ON_ERR (_wzd_page_tv_remote_device_setupselect_brd_eb_set_text(pt_this->ui4_brd_sel_idx));
                RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
                RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, FALSE));    /* Set focus to next button. */
                RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_hlt_icon, WGL_SW_HIDE)); 
                RET_ON_ERR (wzd_view_main_frm_repaint());

                return WZDR_OK;

            case BTN_CURSOR_UP:
                i4_ret = c_wgl_do_cmd (pt_brand_page->h_brand_lb,
                                       WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                                       WGL_PACK(&ui4_first_vsb_idx),
                                       NULL) ;
                RET_ON_ERR(i4_ret);
                
                i4_ret = c_wgl_do_cmd(pt_brand_page->h_brand_lb,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui4_brd_lb_hlt_index),
                                      NULL);
                RET_ON_ERR(i4_ret);

                i4_ret = c_wgl_do_cmd(pt_brand_page->h_brand_lb,
                                      WGL_CMD_LB_GET_ELEM_NUM,
                                      WGL_PACK(&ui4_elem_num),
                                      NULL);
                RET_ON_ERR(i4_ret);

                DBG_INFO( ("[Ln: %d][BRAND_BTN_CURSOR_UP] ui4_brd_lb_hlt_index = %d, ui4_first_vsb_idx = %d\n", __LINE__, ui4_brd_lb_hlt_index, ui4_first_vsb_idx)); 
                if (ui4_brd_lb_hlt_index == 0)
                {
                    DBG_INFO( ("[Ln: %d][BRAND_BTN_CURSOR_UP] ui4_brd_lb_hlt_index = %d, ui4_first_vsb_idx = %d\n", __LINE__, ui4_brd_lb_hlt_index, ui4_first_vsb_idx)); 
                    RET_ON_ERR (a_vkb_set_focus_ex(pt_brand_page->h_brand_vkb)); /* set focus to editbox */
                    RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_hlt_icon, WGL_SW_HIDE)); 
                    RET_ON_ERR (wzd_view_main_frm_repaint());
                    return WZDR_OK;
                }
                if (ui4_brd_lb_hlt_index == ui4_first_vsb_idx)
                {
                    DBG_INFO( ("[Ln: %d][BRAND_BTN_CURSOR_UP] ui4_brd_lb_hlt_index = %d, ui4_first_vsb_idx = %d\n", __LINE__, ui4_brd_lb_hlt_index, ui4_first_vsb_idx)); 
                    RET_ON_ERR (wzd_view_main_frm_repaint());
                    break;
                }
                else
                {
                    DBG_INFO( ("[Ln: %d][BRAND_BTN_CURSOR_UP] ui4_brd_lb_hlt_index = %d, ui4_first_vsb_idx = %d\n", __LINE__, ui4_brd_lb_hlt_index, ui4_first_vsb_idx)); 
                    SET_RECT_BY_SIZE(&t_rect,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_X,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_Y + (ui4_brd_lb_hlt_index - ui4_first_vsb_idx - 1) * 37 * WZD_UI_RATIO_W + (ui4_brd_lb_hlt_index - ui4_first_vsb_idx  - 1) * 2,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_H);
                }
                RET_ON_ERR (c_wgl_move(pt_brand_page->h_brand_lb_hlt_icon,
                                       &t_rect,
                                       WGL_NO_AUTO_REPAINT)); 
                RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_hlt_icon, WGL_SW_RECURSIVE)); 
                RET_ON_ERR (c_wgl_float(pt_brand_page->h_brand_lb_hlt_icon, TRUE, FALSE));
                RET_ON_ERR (wzd_view_main_frm_repaint());                

                break;

            case BTN_CURSOR_DOWN:
                i4_ret = c_wgl_do_cmd (pt_brand_page->h_brand_lb,
                                       WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                                       WGL_PACK(&ui4_first_vsb_idx),
                                       NULL) ;
                RET_ON_ERR(i4_ret);
                
                i4_ret = c_wgl_do_cmd (pt_brand_page->h_brand_lb,
                                       WGL_CMD_LB_GET_LAST_VISIBLE_INDEX,
                                       WGL_PACK(&ui4_last_vsb_idx),
                                       NULL) ;
                RET_ON_ERR(i4_ret);   
                
                i4_ret = c_wgl_do_cmd(pt_brand_page->h_brand_lb,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui4_brd_lb_hlt_index),
                                      NULL);
                RET_ON_ERR(i4_ret);
                
                i4_ret = c_wgl_do_cmd(pt_brand_page->h_brand_lb,
                                      WGL_CMD_LB_GET_ELEM_NUM,
                                      WGL_PACK(&ui4_elem_num),
                                      NULL);
                RET_ON_ERR(i4_ret);
                
                DBG_INFO( ("[Ln: %d] [BRAND_BTN_CURSOR_DOWN] ui4_brd_lb_hlt_index = %d, ui4_first_vsb_idx = %d, ui4_last_vsb_idx = %d\n", __LINE__, ui4_brd_lb_hlt_index, ui4_first_vsb_idx, ui4_last_vsb_idx)); 
                if (ui4_brd_lb_hlt_index == (ui4_elem_num - 1))
                {
                    DBG_INFO( ("[Ln: %d] [BRAND_BTN_CURSOR_DOWN] ui4_brd_lb_hlt_index = %d, ui4_first_vsb_idx = %d, ui4_last_vsb_idx = %d\n", __LINE__, ui4_brd_lb_hlt_index, ui4_first_vsb_idx, ui4_last_vsb_idx)); 
                    return WZDR_OK;
                }
                else if(ui4_brd_lb_hlt_index == ui4_last_vsb_idx)
                {
                    DBG_INFO( ("[Ln: %d] [BRAND_BTN_CURSOR_DOWN] ui4_brd_lb_hlt_index = %d, ui4_first_vsb_idx = %d, ui4_last_vsb_idx = %d\n", __LINE__, ui4_brd_lb_hlt_index, ui4_first_vsb_idx, ui4_last_vsb_idx)); 
                    SET_RECT_BY_SIZE(&t_rect,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_X,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_Y + 5 * 37 * WZD_UI_RATIO_W + 8 * WZD_UI_RATIO_W ,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_H );
                }
                else if (ui4_last_vsb_idx < 6)
                {
                    DBG_INFO( ("[Ln: %d] [BRAND_BTN_CURSOR_DOWN] ui4_brd_lb_hlt_index = %d, ui4_first_vsb_idx = %d, ui4_last_vsb_idx = %d\n", __LINE__, ui4_brd_lb_hlt_index, ui4_first_vsb_idx, ui4_last_vsb_idx)); 
                    SET_RECT_BY_SIZE(&t_rect,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_X,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_Y + (ui4_brd_lb_hlt_index + 1) * 37 * WZD_UI_RATIO_W + 2 * WZD_UI_RATIO_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_H );
                }
                else
                {
                    DBG_INFO( ("[Ln: %d] [BRAND_BTN_CURSOR_DOWN] ui4_brd_lb_hlt_index = %d, ui4_first_vsb_idx = %d, ui4_last_vsb_idx = %d\n", __LINE__, ui4_brd_lb_hlt_index, ui4_first_vsb_idx, ui4_last_vsb_idx)); 
                    SET_RECT_BY_SIZE(&t_rect,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_X,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_Y + (ui4_brd_lb_hlt_index - ui4_first_vsb_idx + 1) * 37 * WZD_UI_RATIO_W + 2 * WZD_UI_RATIO_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_W,
                                     WZD_DEVICE_SETUP_LB_HT_ICON_H );
                }
                
                RET_ON_ERR (c_wgl_move(pt_brand_page->h_brand_lb_hlt_icon,
                                       &t_rect,
                                       WGL_NO_AUTO_REPAINT)); 
                RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_hlt_icon, WGL_SW_RECURSIVE)); 
                RET_ON_ERR (c_wgl_float(pt_brand_page->h_brand_lb_hlt_icon, TRUE, FALSE));
                RET_ON_ERR(wzd_view_main_frm_repaint());

                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }

    c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
                                                                         
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_brand_vkb_nfy_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_brand_vkb_nfy_fct (VOID*                   pv_tag,
                                          UINT32                  ui4_msg,
                                          VOID*                   pv_param1,
                                          VOID*                   pv_param2)
{
    WZD_BRAND_PAGE_T* pt_brand_page = &t_g_device_setup_brand_page;
    GL_RECT_T         t_rect = {0};    
    UINT32*           pui4_key_code = (UINT32*) pv_param1;
    UTF16_T           str_prefix[DEV_SETUP_DB_NAME_LEN_MAX + 1]= L"";
    INT32             i4_ret = WZDR_OK;
    HANDLE_T          h_focus = NULL_HANDLE;
    HANDLE_T          h_cancel_btn = 0;
    UINT8             i_top_row = 0;
    UINT32            ui4_elem_num = 0;
    BOOL              b_is_bottom_row = FALSE;
    BOOL              b_is_visible = FALSE;
    UINT32            ui4_brd_lb_hlt_index = 0;
    UINT32            ui4_first_vsb_idx = 0;
    UINT32            ui4_last_vsb_idx = 0;
    
    if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        if( BTN_SELECT == *pui4_key_code )
        {  
            RET_ON_ERR(c_wgl_get_focus(&h_focus));
            if ( h_focus == pt_brand_page->h_brand_eb )
            {
                DBG_INFO( ("[Ln: %d]  focus in editbox!!!\n",  __LINE__));
                return WDK_NO_ACTION;
            }
            else
            {
                i4_ret = _wzd_page_tv_remote_device_setup_brand_drop_down_lb_update();
                if (i4_ret != WZDR_OK)
                {
                    DBG_INFO( ("[Ln: %d] Brand_drop_down_lb_update FAIL! i4_ret = %d\n", __LINE__, i4_ret)); 
                    RET_ON_ERR(c_wgl_get_visibility(pt_brand_page->h_brand_lb_frm, &b_is_visible)); 
                    if ( b_is_visible == TRUE )
                    {
                        RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
                    }
                }
                RET_ON_ERR (wzd_view_main_frm_repaint());
                
                return WDKR_OK;  
            }
        }
        else if( BTN_CURSOR_DOWN == *pui4_key_code )
        {           
            RET_ON_ERR(c_wgl_get_visibility(pt_brand_page->h_brand_lb, &b_is_visible)); 
            RET_ON_ERR(c_wgl_get_focus(&h_focus));
            RET_ON_ERR((c_wgl_do_cmd(pt_brand_page->h_brand_lb,
                        WGL_CMD_LB_GET_ELEM_NUM,
                        WGL_PACK(&ui4_elem_num),
                        NULL)));

            i4_ret = c_wgl_do_cmd (pt_brand_page->h_brand_lb,
                                       WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                                       WGL_PACK(&ui4_first_vsb_idx),
                                       NULL) ;
            RET_ON_ERR(i4_ret);

            i4_ret = c_wgl_do_cmd (pt_brand_page->h_brand_lb,
                                       WGL_CMD_LB_GET_LAST_VISIBLE_INDEX,
                                       WGL_PACK(&ui4_last_vsb_idx),
                                       NULL) ;
            RET_ON_ERR(i4_ret);  

            i4_ret = c_wgl_do_cmd(pt_brand_page->h_brand_lb,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui4_brd_lb_hlt_index),
                                      NULL);
            RET_ON_ERR(i4_ret);

            DBG_INFO( ("[%s(Ln: %d)] BTN_CURSOR_DOWN focus to LB! i4_ret = %d,ui4_brd_lb_hlt_index=%d,ui4_first_vsb_idx=%d,ui4_last_vsb_idx=%d\n", __FUNCTION__,__LINE__, i4_ret,ui4_brd_lb_hlt_index,ui4_first_vsb_idx,ui4_last_vsb_idx)); 

            if ((h_focus == pt_brand_page->h_brand_eb) && (b_is_visible == TRUE) && (ui4_elem_num != 0))
            {
				if(ui4_elem_num < 6)
				{
	                SET_RECT_BY_SIZE(&t_rect,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_X,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_Y + (ui4_brd_lb_hlt_index) * 37 * WZD_UI_RATIO_W + 2 * WZD_UI_RATIO_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_H );

				}
				else
				{
					if(ui4_brd_lb_hlt_index == ui4_first_vsb_idx)
					{
		                SET_RECT_BY_SIZE(&t_rect,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_X,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_Y,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_H );
					}
					else if(ui4_brd_lb_hlt_index == ui4_last_vsb_idx)
					{
		                SET_RECT_BY_SIZE(&t_rect,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_X,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_Y + 5 * 37 * WZD_UI_RATIO_W + 2 * WZD_UI_RATIO_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_H );

					}
					else
					{
		                SET_RECT_BY_SIZE(&t_rect,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_X,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_Y + (ui4_brd_lb_hlt_index - ui4_first_vsb_idx) * 37 * WZD_UI_RATIO_W + (ui4_brd_lb_hlt_index - ui4_first_vsb_idx) * 2,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_W,
		                                 WZD_DEVICE_SETUP_LB_HT_ICON_H );

					}
				}
                RET_ON_ERR (c_wgl_move(pt_brand_page->h_brand_lb_hlt_icon,
                                       &t_rect,
                                       WGL_NO_AUTO_REPAINT)); 

                RET_ON_ERR (c_wgl_set_focus(pt_brand_page->h_brand_lb, WGL_NO_AUTO_REPAINT));
                RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_hlt_icon, WGL_SW_NORMAL)); 
                RET_ON_ERR (c_wgl_float(pt_brand_page->h_brand_lb_hlt_icon, TRUE, FALSE));
                RET_ON_ERR (wzd_view_main_frm_repaint());
                return WDK_NO_ACTION;
            } 
            else if ((h_focus == pt_brand_page->h_brand_eb) && (b_is_visible == FALSE))
            {
                RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_02, FALSE));    /* Set focus to back button. */
                RET_ON_ERR (wzd_view_main_frm_repaint());
                return WDK_NO_ACTION;
            }
            else 
            {
                i4_ret = a_vkb_current_is_bottom_row(pt_brand_page->h_brand_vkb, &h_cancel_btn, &b_is_bottom_row);
                if ((TRUE == b_is_bottom_row) && (WDKR_OK == i4_ret))
                {
                    RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_02, FALSE));    /* Set focus to back button. */
                    RET_ON_ERR (wzd_view_main_frm_repaint());
                    return WDK_NO_ACTION;
                }  
                return WDKR_OK;
            }
        } 
        else if (BTN_CURSOR_UP == *pui4_key_code )
        { 
            RET_ON_ERR(c_wgl_get_focus(&h_focus));

            if (h_focus == pt_brand_page->h_brand_eb)
            {
                return WDK_NO_ACTION;  
            }
            else
            {
                i_top_row = a_vkb_current_get_row_index(pt_brand_page->h_brand_vkb);
                if (i_top_row == 0)
                {
                    DBG_INFO( ("[Ln: %d]: [BRAND_BTN_CURSOR_UP] i_top_row = %d\n", __LINE__, i_top_row));
                    return WDK_NO_ACTION;
                }
                return WDKR_OK;  
            }
        }        
        else if (BTN_CURSOR_LEFT == *pui4_key_code )
        {   
            RET_ON_ERR(c_wgl_get_focus(&h_focus));
                       
            if (h_focus == pt_brand_page->h_brand_eb)
            {
                i4_ret = a_vkb_do_cmd (pt_brand_page->h_brand_vkb,
                                      VKB_CMD_GET_EB_CONTENT,
                                      (VOID*) str_prefix,
                                      (VOID*) (UINT32) DEV_SETUP_DB_NAME_LEN_MAX);
                RET_ON_ERR(i4_ret);        

                if ( c_uc_w2s_strlen(str_prefix) == 1 )
                {
                    str_prefix[c_uc_w2s_strlen(str_prefix) - 1] = '\0';

                    i4_ret = a_vkb_do_cmd (pt_brand_page->h_brand_vkb,
                                           VKB_CMD_SET_INITIAL_TEXT,
                                          (VOID*)str_prefix,
                                          (VOID*)0XFF);
                    RET_ON_ERR(i4_ret);

                    RET_ON_ERR(c_wgl_get_visibility(pt_brand_page->h_brand_lb_frm, &b_is_visible)); 
                    if ( b_is_visible == TRUE )
                    {
                       RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
                    }
                    RET_ON_ERR (wzd_view_main_frm_repaint());                    
                }
                else if ( c_uc_w2s_strlen(str_prefix) == 0 )
                {                    
                    RET_ON_ERR(c_wgl_get_visibility(pt_brand_page->h_brand_lb_frm, &b_is_visible)); 
                    if ( b_is_visible == TRUE )
                    {
                       RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
                    }
                    RET_ON_ERR (wzd_view_main_frm_repaint());
                    return WDK_NO_ACTION;
                }
                else 
                {                   
                    str_prefix[c_uc_w2s_strlen(str_prefix) - 1] = '\0';

                    i4_ret = a_vkb_do_cmd (pt_brand_page->h_brand_vkb,
                                           VKB_CMD_SET_INITIAL_TEXT,
                                          (VOID*)str_prefix,
                                          (VOID*)0XFF);
                    RET_ON_ERR(i4_ret);  
                    
                    i4_ret = _wzd_page_tv_remote_device_setup_brand_drop_down_lb_update();
                    if (i4_ret != WZDR_OK)
                    {
                        RET_ON_ERR(c_wgl_get_visibility(pt_brand_page->h_brand_lb_frm, &b_is_visible)); 
                        if ( b_is_visible == TRUE )
                        {
                           RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
                        }                       
                    }
                    else
                    {
                        SET_RECT_BY_SIZE(&t_rect,
                                         WZD_DEVICE_SETUP_LB_HT_ICON_X,
                                         WZD_DEVICE_SETUP_LB_HT_ICON_Y,
                                         WZD_DEVICE_SETUP_LB_HT_ICON_W,
                                         WZD_DEVICE_SETUP_LB_HT_ICON_H );

                        RET_ON_ERR (c_wgl_move(pt_brand_page->h_brand_lb_hlt_icon,
                                               &t_rect,
                                               WGL_NO_AUTO_REPAINT)); 
                    
                        RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_NORMAL));
                        RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb, WGL_SW_NORMAL));
                        RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_hlt_icon, WGL_SW_HIDE)); 
                    }                    
                    RET_ON_ERR (wzd_view_main_frm_repaint());
                }
                
                return WDK_NO_ACTION;
            }
            else if (a_vkb_current_get_col_index(pt_brand_page->h_brand_vkb) == 0)
            {
                RET_ON_ERR (a_vkb_set_focus_ex(pt_brand_page->h_brand_vkb));
                RET_ON_ERR (a_vkb_repaint(pt_brand_page->h_brand_vkb));
                RET_ON_ERR (wzd_view_main_frm_repaint()); 

                return WDK_NO_ACTION;
            }
            else 
            {
                return WZDR_OK; 
            } 
        }       
        else if (BTN_CURSOR_RIGHT == *pui4_key_code )
        {
            return WZDR_OK;  
        }    
        else if (((BTN_DIGIT_0 <= *pui4_key_code) && (BTN_DIGIT_9 >= *pui4_key_code)) ||
                ((BTN_KB_NULL <= *pui4_key_code) && (BTN_KB_HYPER >= *pui4_key_code)))
        {
            RET_ON_ERR(c_wgl_get_focus(&h_focus));
            if (h_focus == pt_brand_page->h_brand_eb)
            {                
                i4_ret = _wzd_page_tv_remote_device_setup_brand_drop_down_lb_update();
                if (i4_ret != WZDR_OK)
                {
                    DBG_INFO( ("[Ln: %d] Brand_drop_down_lb_update FAIL! i4_ret = %d\n", __LINE__, i4_ret)); 
                    RET_ON_ERR(c_wgl_get_visibility(pt_brand_page->h_brand_lb_frm, &b_is_visible)); 
                    if ( b_is_visible == TRUE )
                    {
                        RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
                    }
                }
                RET_ON_ERR (wzd_view_main_frm_repaint());
            }

            return WDKR_OK;
        }
        else
        {
            /* do not respond other key */
            return WZDR_OK;
        }
    }
    else if (ui4_msg == VKB_MSG_DLG_KEY_EB_CLEAR)
    {
        if (BTN_CURSOR_RIGHT == *pui4_key_code )
        {
            c_wgl_get_focus(&h_focus);

            if (h_focus == pt_brand_page->h_brand_eb_clr)
            {
                RET_ON_ERR (a_vkb_set_focus(pt_brand_page->h_brand_vkb));
                RET_ON_ERR (wzd_view_main_frm_repaint());
                return WDK_NO_ACTION;
            }

            return WZDR_OK;  
        }
        else if (BTN_CURSOR_DOWN == *pui4_key_code )
        {
            return WDK_NO_ACTION;
        }
        else if (BTN_SELECT == *pui4_key_code )
        {
            i4_ret = a_vkb_do_cmd (pt_brand_page->h_brand_vkb,
                                   VKB_CMD_CLEAR_TEXT,
                                  (VOID*)NULL,
                                  (VOID*)NULL);
            RET_ON_ERR(i4_ret);    

            RET_ON_ERR(c_wgl_get_visibility(pt_brand_page->h_brand_lb_frm, &b_is_visible)); 
            if ( b_is_visible == TRUE )
            {
                RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
            }   
            RET_ON_ERR (wzd_view_main_frm_repaint());
            return WDK_NO_ACTION; 
        }
        else 
        {
            return WZDR_OK;
        }
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_create_brand_vkb
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_create_brand_vkb(HANDLE_T h_parent)
{
    VKB_INIT_T          t_init_data;
    WZD_BRAND_PAGE_T*   pt_brand_page = &t_g_device_setup_brand_page;

    /* Create Virtual key board */
    t_init_data.h_parent            = h_parent;
    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_FULL_SCREEN;
    t_init_data.t_gui_rc.i4_left    = WZD_VKB_FRAME_X;
    t_init_data.t_gui_rc.i4_top     = WZD_VKB_FRAME_Y;
    t_init_data.pf_data_change_fct  = _wzd_page_tv_remote_device_setup_brand_vkb_nfy_fct;
    t_init_data.pv_tag              = NULL;

    a_vkb_create(&t_init_data, &pt_brand_page->h_brand_vkb);                
    a_vkb_set_visibility(pt_brand_page->h_brand_vkb, FALSE);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_create_model_vkb
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_create_model_vkb(HANDLE_T h_parent)
{
    VKB_INIT_T          t_init_data;
    WZD_MODEL_PAGE_T*   pt_model_page = &t_g_device_setup_model_page;

    /* Create Virtual key board */
    t_init_data.h_parent            = h_parent;
    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_FULL_SCREEN;
    t_init_data.t_gui_rc.i4_left    = WZD_VKB_FRAME_X;
    t_init_data.t_gui_rc.i4_top     = WZD_VKB_FRAME_Y;
    t_init_data.pf_data_change_fct  = _wzd_page_tv_remote_device_setup_model_vkb_nfy_fct;
    t_init_data.pv_tag              = NULL;

    a_vkb_create(&t_init_data, &pt_model_page->h_model_vkb);               
    a_vkb_set_visibility(pt_model_page->h_model_vkb, FALSE);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_brand_vkb_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_brand_vkb_show(VOID)
{
    WZD_BRAND_PAGE_T*   pt_brand_page = &t_g_device_setup_brand_page;
    
    a_vkb_set_visibility(pt_brand_page->h_brand_vkb, TRUE);
    a_vkb_set_focus(pt_brand_page->h_brand_vkb);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_model_vkb_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_model_vkb_show(VOID)
{
    WZD_MODEL_PAGE_T*   pt_model_page = &t_g_device_setup_model_page;
    
    a_vkb_set_visibility(pt_model_page->h_model_vkb, TRUE);
    a_vkb_set_focus(pt_model_page->h_model_vkb);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_reset_device_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_drop_down_lb_create(
                                HANDLE_T            h_parent,
                                GL_RECT_T*          pt_rect,
                                wgl_widget_proc_fct pf_wdgt_proc,
                                HANDLE_T*           ph_widget)                                
{
    INT32                       i4_ret = 0 ;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_LB_SCRL_BAR_T           t_scrl_bar_info;
    CHAR*                       s_font_name = wzd_view_get_font_name();

    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_ITEM_T               at_items[1];
    UTF16_T                     w2s_empty[] = {0};

    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = TV_SETUP_SIG_TYPE_LB_TEXT_LENGTH;
    at_cols[0].ui2_width        = 228;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH | WGL_STL_LB_NO_WRAP_OVER;
    t_lb_init.ui2_max_elem_num  = 256;
    t_lb_init.ui2_elem_size     = 38;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    i4_ret = c_wgl_create_widget (h_parent,
                        HT_WGL_WIDGET_LIST_BOX,
                        WGL_CONTENT_LIST_BOX_DEF,
                        WGL_BORDER_TIMG,
                        pt_rect,
                        pf_wdgt_proc,
                        255,
                        & t_lb_init,
                        NULL,
                        ph_widget);
    RET_ON_ERR (i4_ret);

    /* Set Font */
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);
    t_fnt_info.e_font_size  = DESC_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK((UINT16)0),
                           WGL_PACK(&t_fnt_info));
    RET_ON_ERR (i4_ret);

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    RET_ON_ERR (c_wgl_do_cmd(*ph_widget,
                             WGL_CMD_GL_SET_INSET,
                             &t_inset,
                             NULL));
    RET_ON_ERR (i4_ret);                   

    /* Set CNT Inset */
    t_inset.i4_left   = 36 * WZD_UI_RATIO_W;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 36 * WZD_UI_RATIO_W;
    t_inset.i4_bottom = 27 * WZD_UI_RATIO_W;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    RET_ON_ERR (i4_ret);

    /* Set ELEM Inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_ELEM_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    RET_ON_ERR (i4_ret);

    /* Set COL Inset */
    t_inset.i4_left   = 25 * WZD_UI_RATIO_W;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)0),
                           WGL_PACK(&t_inset));
    RET_ON_ERR (i4_ret);
    
    /* Set column color: channel number, text color . */
    t_color_elem.t_normal            = t_g_wzd_color_tv_setup_lb_nor;
    t_color_elem.t_disable           = t_g_wzd_color_tv_setup_lb_nor;
    t_color_elem.t_highlight         = t_g_wzd_color_tv_setup_lb_hlt;
    t_color_elem.t_highlight_unfocus = t_g_wzd_color_tv_setup_lb_nor;
    t_color_elem.t_pushed            = t_g_wzd_color_tv_setup_lb_nor;
    t_color_elem.t_selected          = t_g_wzd_color_tv_setup_lb_nor;
    t_color_elem.t_selected_disable  = t_g_wzd_color_tv_setup_lb_nor;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2 (0, WGL_CLR_TEXT), /* text color */
                           WGL_PACK (& t_color_elem));
    RET_ON_ERR (i4_ret);

    /* Set column color: channel number, bk color . */
    t_color_elem.t_normal            = t_g_wzd_color_cho_sig_txt_bk;
    t_color_elem.t_disable           = t_g_wzd_color_cho_sig_txt_bk;
    t_color_elem.t_highlight         = t_g_wzd_color_cho_sig_txt_bk;
    t_color_elem.t_highlight_unfocus = t_g_wzd_color_cho_sig_txt_bk;
    t_color_elem.t_pushed            = t_g_wzd_color_cho_sig_txt_bk;
    t_color_elem.t_selected          = t_g_wzd_color_cho_sig_txt_bk;
    t_color_elem.t_selected_disable  = t_g_wzd_color_cho_sig_txt_bk;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_ELEM_COLOR,
                           WGL_PACK(WGL_CLR_BK),
                           WGL_PACK (& t_color_elem));
    RET_ON_ERR (i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2 (0, WGL_CLR_BK), 
                           WGL_PACK (& t_color_elem));
    RET_ON_ERR (i4_ret);

    /* Set LB elements */
    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_empty;

    i4_ret = c_wgl_do_cmd(*ph_widget, 
                          WGL_CMD_LB_APPEND_ELEM, 
                          at_items, 
                          NULL );
    RET_ON_ERR (i4_ret);

    t_img_elem.h_normal             = NULL_HANDLE;
    t_img_elem.h_disable            = NULL_HANDLE;
    t_img_elem.h_highlight          = NULL_HANDLE;
    t_img_elem.h_highlight_unfocus  = NULL_HANDLE;
    t_img_elem.h_pushed             = NULL_HANDLE;
    t_img_elem.h_selected           = NULL_HANDLE;
    t_img_elem.h_selected_disable   = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd (*ph_widget, 
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE, 
                           WGL_PACK(&t_img_elem),
                           NULL);      
    RET_ON_ERR (i4_ret);

    /* Set scrollbar image.  */   
    c_memset (& t_scrl_bar_info, 0, sizeof (WGL_LB_SCRL_BAR_T));    
    SET_RECT_BY_SIZE(& t_scrl_bar_info.t_rc_body,                     
                     WZD_DEVICE_SETUP_LB_W - 45 * WZD_UI_RATIO_W,                    
                     25 * WZD_UI_RATIO_W,                      
                     36 * WZD_UI_RATIO_W,                     
                     WZD_DEVICE_SETUP_LB_H - 64 * WZD_UI_RATIO_W);                        
    t_scrl_bar_info.ui4_sz_thumb_min         = WZD_DEVICE_SETUP_LB_H / 5;/*it is size of thumb ;*/      
    
    t_scrl_bar_info.t_imgs_body.t_enable     = NULL_HANDLE;    
    t_scrl_bar_info.t_imgs_body.t_disable    = NULL_HANDLE;    
    t_scrl_bar_info.t_imgs_body.t_highlight  = NULL_HANDLE;  
    
    t_scrl_bar_info.t_imgs_thumb.t_enable    = h_g_wzd_img_dropdown_brand_scrollbar;    
    t_scrl_bar_info.t_imgs_thumb.t_disable   = h_g_wzd_img_dropdown_brand_scrollbar;    
    t_scrl_bar_info.t_imgs_thumb.t_highlight = h_g_wzd_img_dropdown_brand_scrollbar;                      

    i4_ret = c_wgl_do_cmd (*ph_widget,                          
                           WGL_CMD_LB_EXT_SET_SCRL_BAR,                         
                           WGL_PACK (& t_scrl_bar_info),                          
                           NULL);  
    RET_ON_ERR(i4_ret);
                      
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_reset_device_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_code_text_connect (UTF16_T* code_w2s_prefix, UTF16_T* code_w2s)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this = &t_g_tv_remote_device_setup;
    UTF16_T        w2s_brand[DEV_SETUP_DB_NAME_LEN_MAX + 1] = {0};
    UTF16_T        w2s_model[DEV_SETUP_DB_NAME_LEN_MAX + 1] = {0};
    CHAR           ps_brand_name[DEV_SETUP_DB_NAME_LEN_MAX + 1] = {0};
    UINT32         ui4_brand_len;
    UINT32         ui4_model_len;

    c_uc_w2s_strcpy(code_w2s, code_w2s_prefix);

    c_memset(ps_brand_name, 0, DEV_SETUP_DB_NAME_LEN_MAX + 1);
    c_memcpy(ps_brand_name, pt_this->s_brd_name, DEV_SETUP_DB_NAME_LEN_MAX + 1);

    if ((c_strcmp(pt_this->s_brd_name, "") != 0) && (c_strcmp(pt_this->s_mdl_name, "") == 0))
    {
        c_uc_ps_to_w2s (ps_brand_name, w2s_brand, DEV_SETUP_DB_NAME_LEN_MAX);
        ui4_brand_len = c_uc_w2s_strlen(w2s_brand);
        c_uc_w2s_strncat(code_w2s, w2s_brand, ui4_brand_len);
    }
    else if ((c_strcmp(pt_this->s_brd_name, "") != 0) && (c_strcmp(pt_this->s_mdl_name, "") != 0))
    {
        c_strncat(ps_brand_name, " ", 1);
        c_uc_ps_to_w2s (ps_brand_name, w2s_brand, DEV_SETUP_DB_NAME_LEN_MAX);
        ui4_brand_len = c_uc_w2s_strlen(w2s_brand);
        c_uc_w2s_strncat(code_w2s, w2s_brand, ui4_brand_len);
        
        c_uc_ps_to_w2s (pt_this->s_mdl_name, w2s_model, DEV_SETUP_DB_NAME_LEN_MAX);
        ui4_model_len = c_uc_w2s_strlen(w2s_model);
        c_uc_w2s_strncat(code_w2s, w2s_model, ui4_model_len);
    }
    else
    {
       DBG_INFO( ("[Ln: %d] brand is null or brand and model are all null!\n", __LINE__));
    }
  
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_skip_full_dlg_text_connect
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_skip_full_dlg_text_connect (UTF16_T* dlg_w2s)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    UTF16_T        str_w2s[DEV_SETUP_DB_NAME_LEN_MAX + 1] = {0};
    CHAR           s_src_name[DEV_SETUP_DB_NAME_LEN_MAX + 1] = {0};
    ISO_639_LANG_T s639_lang = {0};
    ISL_REC_T      t_isl_rec = {0};
    INT32          i4_ret = WZDR_OK;
	CHAR           s_rf_name[DEV_SETUP_DB_NAME_LEN_MAX + 1] = "Coaxial";//RF->Coaxial
	UINT8		   ui1_rec_num = 0;

	a_isl_get_num_rec(&ui1_rec_num);
	if(pt_this->ui1_sel_src_idx == (ui1_rec_num-1))
	{
		c_uc_ps_to_w2s(s_rf_name,str_w2s,DEV_SETUP_DB_NAME_LEN_MAX);
	}
	else
	{
	    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
	    i4_ret = a_isl_get_rec_by_id(pt_this->aui1_input_src_id[pt_this->ui1_sel_src_idx], &t_isl_rec); 
	    if (i4_ret != ISLR_OK) {
	        DBG_INFO( ("[Ln: %d] pt_this->ui1_sel_src_idx = %d, i4_ret = %d!!!!\n",  __LINE__, pt_this->ui1_sel_src_idx, i4_ret)); 
	        return WZDR_FAIL;
	    }
	    c_uc_w2s_to_ps(a_isl_get_display_name(&t_isl_rec), s_src_name, DEV_SETUP_DB_NAME_LEN_MAX);

	    i4_ret = a_cfg_get_gui_lang(s639_lang);
	    if ((i4_ret == WZDR_OK) && (c_strncmp(s639_lang, s639_app_cfg_lang_spa, ISO_639_LANG_LEN) == 0))
	    {
	        c_uc_w2s_strncpy(str_w2s, WZD_TEXT(MLM_WZD_KEY_TV_DEVICE_NAME_INPUT_DLG_MSG_1), DEV_SETUP_DB_NAME_LEN_MAX);
	        c_uc_w2s_strncat(str_w2s, a_isl_get_display_name(&t_isl_rec), DEV_SETUP_DB_NAME_LEN_MAX);
	    }
	    else
	    {
	        c_uc_w2s_strcpy(str_w2s, a_isl_get_display_name(&t_isl_rec));
	    }
	}

    c_uc_w2s_strncat(str_w2s, WZD_TEXT(MLM_WZD_KEY_TV_DEVICE_NAME_INPUT_DLG_MSG_2), DEV_SETUP_DB_NAME_LEN_MAX);
    
    _wzd_page_tv_remote_device_setup_text_connect (str_w2s, dlg_w2s);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_worked_full_dlg_text_connect
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_worked_full_dlg_text_connect (UTF16_T* code_w2s)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this = &t_g_tv_remote_device_setup;
    UTF16_T        w2s_type_suffix[WZD_DEVICE_SETUP_TYPE_NAME_SUFFIX_LEN + 1] = {0};
    CHAR           type_suffix[WZD_DEVICE_SETUP_TYPE_NAME_SUFFIX_LEN + 1] = {0};
    UINT32         ui4_type_len;
    UINT32         ui4_string_len;
    UINT16         lang_id;

    c_uc_w2s_strcpy(code_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_COMPLETE_TIP));

    ui4_string_len = c_uc_w2s_strlen(pt_this->t_dev_type[pt_this->ui4_type_sel_idx].pw2s_txt_msg);
    
    lang_id = wzd_get_lang_id ();
    DBG_INFO( ("[Ln: %d] wzd_get_lang_id = %d\n", __LINE__, lang_id));

    c_uc_w2s_strncat(code_w2s, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].pw2s_txt_msg, ui4_string_len);

    if (pt_this->ui4_type_paired_count[pt_this->ui4_type_sel_idx] == 1 || pt_this->ui4_type_paired_count[pt_this->ui4_type_sel_idx] == 0)
    {
       c_uc_w2s_strncat(code_w2s, L" ", 1);
    }
    else
    {
       type_suffix[0] = 0x30 + pt_this->ui4_type_paired_count[pt_this->ui4_type_sel_idx];
       c_uc_ps_to_w2s (type_suffix, w2s_type_suffix, WZD_DEVICE_SETUP_TYPE_NAME_SUFFIX_LEN);
       c_uc_w2s_strncat(w2s_type_suffix, L" ", 1); 
       ui4_type_len = c_uc_w2s_strlen(w2s_type_suffix);
       c_uc_w2s_strncat(code_w2s, w2s_type_suffix, ui4_type_len);
    }
    c_uc_w2s_strncat(code_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_COMPLETE_MIG), c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_COMPLETE_MIG)));
    
    if ((DEVICE_TYPE_SELECT_AUDIO_RECIEVER == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SOUND_BAR == pt_this->ui4_type_sel_idx))
    {
	    c_uc_w2s_strncat(code_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_COMPLETE_MIG_AUD), c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_COMPLETE_MIG_AUD)));
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_msg_w2s_sch
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static UTF16_T* _wzd_page_tv_remote_device_setup_confirm_msg_w2s_sch(UTF16_T* pw2s_text,UTF16_T* pw2s_sub_text)
{                                              

    UTF16_T*   pw2s_start = NULL;
    SIZE_T     t_cmp_offset = 0;
    SIZE_T     t_txt_size = 0;
    SIZE_T     t_sub_txt_size = 0;

    if (!pw2s_text ||!pw2s_sub_text)
    {
        return (pw2s_start);
    }

    t_txt_size = c_uc_w2s_strlen(pw2s_text);
    t_sub_txt_size = c_uc_w2s_strlen(pw2s_sub_text);

    if (t_txt_size < t_sub_txt_size)
    {
        return (pw2s_start);
    }

    pw2s_start = pw2s_text;

    while (pw2s_start <= pw2s_text + t_txt_size - t_sub_txt_size)
    {
        t_cmp_offset = 0;
        while (t_cmp_offset < t_sub_txt_size)
        {
            if (*(pw2s_start + t_cmp_offset) == *(pw2s_sub_text + t_cmp_offset))
            {
                t_cmp_offset++;
            }
            else
            {
                break;
            }
        }
        if (t_cmp_offset == t_sub_txt_size)
        {
            return (pw2s_start);
        }
        pw2s_start++;
    }
    
    return (NULL);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_page_desc_htxt_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_page_desc_htxt_create(HANDLE_T h_parent, GL_RECT_T* t_rect, HANDLE_T *ph_widget)
{
    WGL_INSET_T                 t_inset;
    WGL_HTS_INIT_T              t_init;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_HTS_PARAG_ATTR_T        t_parag;
    CHAR*                       s_font_name = wzd_view_get_font_name();

    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, s_font_name);
    t_init.t_font_info_dft.e_font_size  = DESC_TXT_FNT_SIZE;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;

    /* create hyper text widget */
    RET_ON_ERR (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     ph_widget));

    /* set content inset */
    t_inset.i4_left   = WIFI_REMOTE_HPR_TXT_L;
    t_inset.i4_right  = WIFI_REMOTE_HPR_TXT_R;
    t_inset.i4_top    = WIFI_REMOTE_HPR_TXT_T;
    t_inset.i4_bottom = WIFI_REMOTE_HPR_TXT_B;

    RET_ON_ERR (c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_HTS_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set justification */
    RET_ON_ERR (c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_CENTER),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt_bk);
    
    RET_ON_ERR (c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    RET_ON_ERR (c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_HTS_VP_BK), /* viewport color */
                              WGL_PACK (& t_color_info)));



    c_memset (&t_parag, 0, sizeof(WGL_HTS_PARAG_ATTR_T));
    t_parag.e_justif = WGL_HTS_JUSTIF_LEFT;
    t_parag.ui2_indent = 0;
    t_parag.i4_line_gap_bottom = 2;
    t_parag.i4_line_gap_top = 0;
    t_parag.ui2_parag_gap_bottom = 0;
    t_parag.ui2_parag_gap_top = 0;
    RET_ON_ERR (c_wgl_do_cmd(*ph_widget,
                             WGL_CMD_HTS_CUR_PARAG_SET,
                             WGL_PACK(&t_parag),
                             NULL));
    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_page_set_desc_htxt
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_page_set_desc_htxt(HANDLE_T h_parent, 
                                                                         UTF16_T* pw2s_text, 
                                                                         WGL_HIMG_TPL_T h_img)
{
    INT32                  i4_ret = WZDR_OK;
    UINT16                 ui2_sec_id = 0;
    WGL_HTS_TEXT_INFO_T    t_hts_txt_info;
    WGL_HTS_IMG_INFO_T     t_hts_img_info;
    UTF16_T                w2s_pic_flag[WZD_DEVICE_SETUP_PIC_FLAG_LEN + 1];
    UTF16_T*               pw2s_next = NULL;
    UTF16_T*               pw2s_temp = pw2s_text;
    
    c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
    c_memset (&t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
    c_memset (w2s_pic_flag, 0, sizeof(w2s_pic_flag));

    i4_ret = c_wgl_do_cmd (h_parent,
                           WGL_CMD_HTS_CLEAR_ALL,
                           WGL_PACK (FALSE),
                           NULL);
    RET_ON_ERR(i4_ret);

    /* Set font data. */
    c_strcpy (t_hts_txt_info.t_font.a_c_font_name, wzd_view_get_font_name());

    t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_LARGE;
    t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
    t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

    /* Set text background color. */
    COLOR_COPY (&t_hts_txt_info.t_clr_text, &t_g_wzd_color_cho_mode_txt_gray);
    COLOR_COPY (&t_hts_txt_info.t_clr_text_bk, &t_g_wzd_color_desc_txt_bk);
    
    c_uc_ps_to_w2s("%p", w2s_pic_flag, sizeof(w2s_pic_flag));

    pw2s_next = _wzd_page_tv_remote_device_setup_confirm_msg_w2s_sch(pw2s_temp, w2s_pic_flag);

    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
    t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * (pw2s_next - pw2s_temp);

    i4_ret = c_wgl_do_cmd(h_parent,
                          WGL_CMD_HTS_APPEND_TEXT_SEC,
                          WGL_PACK (&t_hts_txt_info),
                          WGL_PACK (&ui2_sec_id));
    RET_ON_ERR(i4_ret);   

    t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
    t_hts_img_info.h_img = h_img;

    i4_ret = c_wgl_do_cmd(h_parent,
                          WGL_CMD_HTS_APPEND_IMG_SEC,
                          WGL_PACK(&t_hts_img_info),
                          WGL_PACK(&ui2_sec_id));
    RET_ON_ERR(i4_ret);   

    pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
    t_hts_txt_info.t_string.w2s_str = pw2s_temp;
    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

    i4_ret = c_wgl_do_cmd(h_parent,
                          WGL_CMD_HTS_APPEND_TEXT_SEC,
                          WGL_PACK (&t_hts_txt_info),
                          WGL_PACK (&ui2_sec_id));
    RET_ON_ERR(i4_ret); 

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_reset_device_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_select_device_type_page_create(HANDLE_T  h_parent) 
{
    GL_RECT_T   t_rect;
    WZD_SELECT_PAGE_T* pt_select_page = &t_g_device_setup_select_page;

    /* description text create */
    c_memset (&t_rect, 0, sizeof (GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      BASE_FRM_W,
                      80 * WZD_UI_RATIO_W);

    RET_ON_ERR( _wzd_page_tv_remote_device_setup_desc_create(h_parent,
                                                             &t_rect,
                                                             &pt_select_page->h_select_desc_txt));

    /* select box buttons create */
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_create_choose_box_frm(h_parent));
    RET_ON_ERR ( _wzd_page_tv_remote_device_setup_create_choose_box_buttons());

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_reset_device_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_select_input_page_create(HANDLE_T  h_parent)
{
    GL_RECT_T   t_rect;
    INT32       i4_ret;
    WZD_INPUT_PAGE_T* pt_input_page = &t_g_device_setup_input_page;

    /* description text create */
    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      BASE_FRM_W,
                      80 * WZD_UI_RATIO_W);

    i4_ret = _wzd_page_tv_remote_device_setup_desc_create(h_parent,
                                                          &t_rect,
                                                          &pt_input_page->h_input_desc_txt);
    RET_ON_ERR(i4_ret);
    
    return WZDR_OK;
}
#ifdef APP_UEI_SPINNER_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_timer_icon_update
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_timer_icon_update(HANDLE_T   h_widget)
{
    INT32                i4_ret;
    WGL_IMG_INFO_T       t_img_info;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this       = &t_g_tv_remote_device_setup;
    WGL_HIMG_TPL_T       ah_g_searching_icon[12] =
    {
        h_g_wdk_img_loading_icon_1,
        h_g_wdk_img_loading_icon_2,
        h_g_wdk_img_loading_icon_3,
        h_g_wdk_img_loading_icon_4,
        h_g_wdk_img_loading_icon_5,
        h_g_wdk_img_loading_icon_6,
        h_g_wdk_img_loading_icon_7,
        h_g_wdk_img_loading_icon_8,
        h_g_wdk_img_loading_icon_9,
        h_g_wdk_img_loading_icon_10,
        h_g_wdk_img_loading_icon_11,
        h_g_wdk_img_loading_icon_12
    };

    if(pt_this->ui1_icon_step >= ((sizeof(ah_g_searching_icon) / sizeof(WGL_HIMG_TPL_T)) -1))
    {
        pt_this->ui1_icon_step = 0;
    }
    else
    {
        pt_this->ui1_icon_step++;
    }

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = ah_g_searching_icon[pt_this->ui1_icon_step];
    t_img_info.u_img_data.t_standard.t_disable   = ah_g_searching_icon[pt_this->ui1_icon_step];
    t_img_info.u_img_data.t_standard.t_highlight = ah_g_searching_icon[pt_this->ui1_icon_step];

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(h_widget, NULL, TRUE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;

}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_paring_create_animation_icon
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_wifi_remote_paring_create_animation_icon(HANDLE_T  h_parent,
                                           HANDLE_T* ph_widget)
{
	INT32			i4_ret;
	GL_RECT_T		t_rect;
	WGL_IMG_INFO_T		 t_img_info;

	c_memset(&t_rect, 0, sizeof(GL_RECT_T));
	SET_RECT_BY_SIZE(&t_rect,
					 WZD_DEVICE_SETUP_SPINNER_ICON_X,
					 WZD_DEVICE_SETUP_SPINNER_ICON_Y,
					 WZD_DEVICE_SETUP_SPINNER_ICON_W,
					 WZD_DEVICE_SETUP_SPINNER_ICON_H);

	i4_ret = c_wgl_create_widget(h_parent,
								HT_WGL_WIDGET_ICON,
								WGL_CONTENT_ICON_DEF,
								WGL_BORDER_TIMG,
								&t_rect,
								NULL,
								255,
								(VOID *)0,
								NULL,
								ph_widget);
	RET_ON_ERR(i4_ret);

	/* set icon alignment */
	i4_ret = c_wgl_do_cmd(*ph_widget,
						  WGL_CMD_ICON_SET_ALIGN,
						  (VOID*)WGL_AS_CENTER_CENTER,
						  NULL);
	RET_ON_ERR(i4_ret);

	c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
	t_img_info.e_type							 = WGL_IMG_SET_STANDARD;
	t_img_info.u_img_data.t_standard.t_enable	 = h_g_wdk_img_loading_icon_1;
	t_img_info.u_img_data.t_standard.t_disable	 = h_g_wdk_img_loading_icon_1;
	t_img_info.u_img_data.t_standard.t_highlight = h_g_wdk_img_loading_icon_1;

	i4_ret = c_wgl_do_cmd(*ph_widget,
						  WGL_CMD_GL_SET_IMAGE,
						  WGL_PACK(WGL_IMG_FG),
						  WGL_PACK(&t_img_info));
	RET_ON_ERR(i4_ret);

	/* make icon invisible */
	i4_ret = c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE);
	RET_ON_ERR(i4_ret);

	return WZDR_OK;
}
#endif
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_reset_device_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_select_brand_page_create(HANDLE_T  h_parent)
{
    INT32                   i4_ret;
    GL_RECT_T               t_rect;
    WGL_COLOR_INFO_T        t_color_info;
    WGL_IMG_INFO_T          t_img_info;
    VKB_EB_ATTACH_DATE      t_attach_data;
    WZD_BRAND_PAGE_T*       pt_brand_page = &t_g_device_setup_brand_page;

    /* description text create */
    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      25 * WZD_UI_RATIO_W,
                      LAYOUT_FRM_W,
                      30 * WZD_UI_RATIO_W);

    i4_ret = _wzd_page_tv_remote_device_setup_desc_create(h_parent,
                                                          &t_rect,
                                                          &pt_brand_page->h_brand_desc_txt);
    RET_ON_ERR(i4_ret);                 

    /* message text create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      50 * WZD_UI_RATIO_W,
                      LAYOUT_FRM_W,
                      30 * WZD_UI_RATIO_H);
    i4_ret = _wzd_page_tv_remote_device_setup_msg_create(h_parent,
                                                         &t_rect,
                                                         &pt_brand_page->h_brand_msg_txt);
    RET_ON_ERR(i4_ret);                 

    /* create vkb */
    i4_ret = _wzd_page_tv_remote_device_setup_create_brand_vkb(h_parent);
    RET_ON_ERR(i4_ret); 

    /* editebox frame create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      WZD_DEVICE_SETUP_EB_FOM_X,
                      WZD_DEVICE_SETUP_EB_FOM_Y,
                      WZD_DEVICE_SETUP_EB_FOM_W,
                      WZD_DEVICE_SETUP_EB_FOM_H);
                      
    i4_ret = _wzd_page_tv_remote_device_setup_box_frm_create(h_parent,
                                                             t_rect,
                                                             NULL,
                                                             &pt_brand_page->h_brand_eb_frm);
    RET_ON_ERR(i4_ret);

    c_memset(&t_color_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_network_frame_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_network_frame_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_network_frame_bk);
    i4_ret= c_wgl_do_cmd(pt_brand_page->h_brand_eb_frm,
                         WGL_CMD_GL_SET_COLOR,
                         WGL_PACK (WGL_CLR_BK),     /* background color */
                         WGL_PACK (&t_color_info));
    RET_ON_ERR(i4_ret);

    /* editbox create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      WZD_DEVICE_SETUP_EB_X,
                      WZD_DEVICE_SETUP_EB_Y,
                      WZD_DEVICE_SETUP_EB_W,
                      WZD_DEVICE_SETUP_EB_H);
                      
    i4_ret = _wzd_page_tv_remote_device_setup_edit_box_create(pt_brand_page->h_brand_eb_frm,
                                                              t_rect,
                                                              NULL,
                                                              &pt_brand_page->h_brand_eb);
    RET_ON_ERR(i4_ret);  

    /* editbox clean icon create */
    i4_ret = _wzd_page_tv_remote_device_setup_brand_eb_clear_icon_create (h_parent);
    RET_ON_ERR(i4_ret); 
    
    /* attach editbox to vkb */
    c_memset(&t_attach_data, 0 , sizeof(VKB_EB_ATTACH_DATE));
    t_attach_data.h_edit_box = pt_brand_page->h_brand_eb;
    t_attach_data.h_eb_clr = pt_brand_page->h_brand_eb_clr;
    t_attach_data.b_need_eb_clr = TRUE;
    
    i4_ret = a_vkb_attach_eb (pt_brand_page->h_brand_vkb, &t_attach_data);
    RET_ON_ERR(i4_ret);

    /* listbox frame create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      WZD_DEVICE_SETUP_LB_X,
                      WZD_DEVICE_SETUP_LB_Y,
                      WZD_DEVICE_SETUP_LB_W,
                      WZD_DEVICE_SETUP_LB_H);

    i4_ret = _wzd_page_tv_remote_device_setup_box_frm_create(h_parent,
                                                             t_rect,
                                                             NULL,
                                                             &pt_brand_page->h_brand_lb_frm);
    RET_ON_ERR(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_dropdown_brand;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_dropdown_brand;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_dropdown_brand;

    RET_ON_ERR (c_wgl_do_cmd (pt_brand_page->h_brand_lb_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));
                              
    /* listbox create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (& t_rect,
                      0,
                      0,
                      WZD_DEVICE_SETUP_LB_W,
                      WZD_DEVICE_SETUP_LB_H);
    i4_ret = _wzd_page_tv_remote_device_setup_drop_down_lb_create(pt_brand_page->h_brand_lb_frm,
                                                   &t_rect,
                                                   _wzd_page_tv_remote_device_setup_brand_drop_down_lb_proc,
                                                   &pt_brand_page->h_brand_lb);
    RET_ON_ERR(i4_ret);

    /* listbox highlight icon create */
    i4_ret = _wzd_page_tv_remote_device_setup_brand_lb_hlt_icon_create();
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_select_model_page_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_select_model_page_create(HANDLE_T  h_parent)
{
    INT32                   i4_ret;
    GL_RECT_T               t_rect;
    WGL_COLOR_INFO_T        t_color_info;
    WGL_IMG_INFO_T          t_img_info;
    VKB_EB_ATTACH_DATE      t_attach_data;
    WZD_MODEL_PAGE_T*       pt_model_page = &t_g_device_setup_model_page;

    /* description text create */
    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      25 * WZD_UI_RATIO_W,
                      LAYOUT_FRM_W,
                      30 * WZD_UI_RATIO_W);

    i4_ret = _wzd_page_tv_remote_device_setup_desc_create(h_parent,
                                                          &t_rect,
                                                          &pt_model_page->h_model_desc_txt);
    RET_ON_ERR(i4_ret);                 

    /* message text create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      50 * WZD_UI_RATIO_W,
                      LAYOUT_FRM_W,
                      50 * WZD_UI_RATIO_H);
    i4_ret = _wzd_page_tv_remote_device_setup_msg_create(h_parent,
                                                         &t_rect,
                                                         &pt_model_page->h_model_msg_txt);
    RET_ON_ERR(i4_ret);                 

    /* create vkb */
    i4_ret = _wzd_page_tv_remote_device_setup_create_model_vkb(h_parent);
    RET_ON_ERR(i4_ret); 

    /* editebox frame create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      WZD_DEVICE_SETUP_EB_FOM_X,
                      WZD_DEVICE_SETUP_EB_FOM_Y,
                      WZD_DEVICE_SETUP_EB_FOM_W,
                      WZD_DEVICE_SETUP_EB_FOM_H);
                      
    i4_ret = _wzd_page_tv_remote_device_setup_box_frm_create(h_parent,
                                                             t_rect,
                                                             NULL,
                                                             &pt_model_page->h_model_eb_frm);
    RET_ON_ERR(i4_ret);


    c_memset(&t_color_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_network_frame_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_network_frame_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_network_frame_bk);
    i4_ret= c_wgl_do_cmd(pt_model_page->h_model_eb_frm,
                         WGL_CMD_GL_SET_COLOR,
                         WGL_PACK (WGL_CLR_BK),     /* background color */
                         WGL_PACK (&t_color_info));
    RET_ON_ERR(i4_ret);

    /* editbox create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      WZD_DEVICE_SETUP_EB_X,
                      WZD_DEVICE_SETUP_EB_Y,
                      WZD_DEVICE_SETUP_EB_W,
                      WZD_DEVICE_SETUP_EB_H);
                      
    i4_ret = _wzd_page_tv_remote_device_setup_edit_box_create(pt_model_page->h_model_eb_frm,
                                                              t_rect,
                                                              NULL,
                                                              &pt_model_page->h_model_eb);
                                        
    RET_ON_ERR(i4_ret);  

    /* editbox clean icon create */
    i4_ret = _wzd_page_tv_remote_device_setup_model_eb_clear_icon_create (h_parent);
    RET_ON_ERR(i4_ret); 
    

    /* attach editbox to vkb */
    c_memset(&t_attach_data, 0 , sizeof(VKB_EB_ATTACH_DATE));
    t_attach_data.h_edit_box = pt_model_page->h_model_eb;
    t_attach_data.h_eb_clr = pt_model_page->h_model_eb_clr;
    t_attach_data.b_need_eb_clr = TRUE;
    
    i4_ret = a_vkb_attach_eb (pt_model_page->h_model_vkb, &t_attach_data);   
    RET_ON_ERR(i4_ret);

    /* listbox frame create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      WZD_DEVICE_SETUP_LB_X,
                      WZD_DEVICE_SETUP_LB_Y,
                      WZD_DEVICE_SETUP_LB_W,
                      WZD_DEVICE_SETUP_LB_H);

    i4_ret = _wzd_page_tv_remote_device_setup_box_frm_create(h_parent,
                                                             t_rect,
                                                             NULL,
                                                             &pt_model_page->h_model_lb_frm);
    RET_ON_ERR(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_dropdown_brand;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_dropdown_brand;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_dropdown_brand;

    RET_ON_ERR (c_wgl_do_cmd (pt_model_page->h_model_lb_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));
                              
    /* listbox create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (& t_rect,
                      0,
                      0,
                      WZD_DEVICE_SETUP_LB_W,
                      WZD_DEVICE_SETUP_LB_H);
    i4_ret = _wzd_page_tv_remote_device_setup_drop_down_lb_create(pt_model_page->h_model_lb_frm,
                                                                  &t_rect,
                                                                  _wzd_page_tv_remote_device_setup_model_drop_down_lb_proc,
                                                                  &pt_model_page->h_model_lb);

    RET_ON_ERR(i4_ret);

    /* listbox highlight icon create */
    i4_ret = _wzd_page_tv_remote_device_setup_model_lb_hlt_icon_create();
    RET_ON_ERR(i4_ret);
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_create_btn_widget
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_create_btn_widget(
                            HANDLE_T                    h_parent,
                            GL_RECT_T*                  pt_rect,
                            WGL_COLOR_INFO_T*           pt_color_info_fg,
                            WGL_FONT_INFO_T*            pt_font,
                            WGL_HIMG_TPL_T              t_img_tpl_ht,
                            WGL_HIMG_TPL_T              t_img_tpl_un_ht,
                            UINT8                       ui1_align,
                            wgl_widget_proc_fct         pf_wdgt_proc,
                            HANDLE_T*                   ph_btn,
                            WGL_INSET_T*                pt_inset)
{
    WGL_IMG_INFO_T  t_img_info;
    INT32           i4_ret = WZDR_OK;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 ph_btn);
                                                                           
    RET_ON_ERR(i4_ret);                                    
                                 
    /*foreground color*/
    RET_ON_ERR (c_wgl_do_cmd(*ph_btn, 
                             WGL_CMD_GL_SET_COLOR, 
                             WGL_PACK(WGL_CLR_TEXT), 
                             WGL_PACK(pt_color_info_fg)));

    RET_ON_ERR (c_wgl_do_cmd(*ph_btn,
                             WGL_CMD_BTN_SET_ALIGN,
                             WGL_PACK(ui1_align),
                             NULL));

    /*content inset*/
    RET_ON_ERR (c_wgl_do_cmd(*ph_btn,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(pt_inset),
                           NULL));
                           
    /*font*/
    RET_ON_ERR (c_wgl_do_cmd(*ph_btn, WGL_CMD_GL_SET_FONT, (VOID*)pt_font, NULL));

    /*set image*/
    t_img_info.e_type                                   = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable            = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_enable             = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_highlight          = t_img_tpl_ht;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_push               = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = t_img_tpl_un_ht;

    RET_ON_ERR (c_wgl_do_cmd(*ph_btn, WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_BK), WGL_PACK(&t_img_info)));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_page_worked_button_resume_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_page_worked_button_resume_info (VOID)
{
    WZD_BRAND_PAGE_T*                    pt_brand_page = &t_g_device_setup_brand_page;
    WZD_MODEL_PAGE_T*                    pt_model_page = &t_g_device_setup_model_page;
    BOOL                                 b_is_visible  = FALSE;
         
    /* clean brand editbox and listbox */
    RET_ON_ERR (a_vkb_do_cmd (pt_brand_page->h_brand_vkb,
                              VKB_CMD_CLEAR_TEXT,
                             (VOID*)NULL,
                             (VOID*)NULL));  

    RET_ON_ERR (c_wgl_do_cmd(pt_brand_page->h_brand_lb, 
                             WGL_CMD_LB_DEL_ALL, 
                             NULL, 
                             NULL));
                 
    RET_ON_ERR (c_wgl_get_visibility(pt_brand_page->h_brand_lb_frm, &b_is_visible)); 
    if ( b_is_visible == TRUE )
    {
        RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
    }   
    
    /* clean brand editbox and listbox */
    RET_ON_ERR (a_vkb_do_cmd (pt_model_page->h_model_vkb,
                              VKB_CMD_CLEAR_TEXT,
                             (VOID*)NULL,
                             (VOID*)NULL));  

    RET_ON_ERR ( c_wgl_do_cmd(pt_model_page->h_model_lb, 
                              WGL_CMD_LB_DEL_ALL, 
                              NULL, 
                              NULL));

    RET_ON_ERR (c_wgl_get_visibility(pt_model_page->h_model_lb_frm, &b_is_visible)); 
    if ( b_is_visible == TRUE )
    {
        RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));
    }                               
    
    return WZDR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_page_skip_button_resume_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_page_skip_button_resume_info (VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this       = &t_g_tv_remote_device_setup;
    WZD_BRAND_PAGE_T*                    pt_brand_page = &t_g_device_setup_brand_page;
    WZD_MODEL_PAGE_T*                    pt_model_page = &t_g_device_setup_model_page;
    BOOL                                 b_is_visible  = FALSE;

    /* Unpair hander */
    if ((DEVICE_TYPE_SELECT_AUDIO_RECIEVER == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SOUND_BAR == pt_this->ui4_type_sel_idx))
    {
        RET_ON_ERR (_wzd_page_tv_remote_device_setup_turn_on_tv_speaker()); 
    }
    
    /* clean brand editbox and listbox */
    RET_ON_ERR (a_vkb_do_cmd (pt_brand_page->h_brand_vkb,
                              VKB_CMD_CLEAR_TEXT,
                             (VOID*)NULL,
                             (VOID*)NULL));  

    RET_ON_ERR (c_wgl_do_cmd(pt_brand_page->h_brand_lb, 
                             WGL_CMD_LB_DEL_ALL, 
                             NULL, 
                             NULL));
                 
    RET_ON_ERR (c_wgl_get_visibility(pt_brand_page->h_brand_lb_frm, &b_is_visible)); 
    if ( b_is_visible == TRUE )
    {
        RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
    }   
    
    /* clean brand editbox and listbox */
    RET_ON_ERR (a_vkb_do_cmd (pt_model_page->h_model_vkb,
                              VKB_CMD_CLEAR_TEXT,
                             (VOID*)NULL,
                             (VOID*)NULL));  

    RET_ON_ERR ( c_wgl_do_cmd(pt_model_page->h_model_lb, 
                              WGL_CMD_LB_DEL_ALL, 
                              NULL, 
                              NULL));

    RET_ON_ERR (c_wgl_get_visibility(pt_model_page->h_model_lb_frm, &b_is_visible)); 
    if ( b_is_visible == TRUE )
    {
        RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));
    }                               

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_do_show_dialog_timer
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_do_show_dialog_timer(VOID* pv_data, SIZE_T  z_data_size)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    UINT8 status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;

    wzd_view_full_screen_dlg_hide();
    t_g_device_setup_input_page.b_is_full_screen_dlg_show = FALSE;

    a_cfg_custom_get_wifi_remote_pair_status(&status);
    if ((pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP||pt_this->e_dev_setup_enter_reason ==DEVICE_SETUP_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE) && status != WIFI_REMOTE_PAIR_STATUS_PAIRED)
    {
        pt_this->e_dev_setup_enter_reason = DEVICE_SETUP_ENTER_REASON_NONE;
        
        /* hide selbox */
        wzd_view_sel_box_show (WZD_SEL_BOX_SHOW_TYPE_HIDE);

		if (a_wzd_is_resume_from_menu_setup())
        {
           a_wzd_exit(); /*Exit Wizard*/
        }
        else
		{
		    pt_this->e_pre_state = DEVICE_SETUP_CODE_CONFIRM;
	        pt_this->e_state = DEVICE_SETUP_FINISHED;
	        _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
		}
    }
    else 
    {
        /* resume info */   
        if (pt_this->b_is_device_setup_worked == FALSE)
        {
            _wzd_page_tv_remote_device_setup_confirm_page_skip_button_resume_info();
        }
        else
        {
            _wzd_page_tv_remote_device_setup_confirm_page_worked_button_resume_info();
        }

        if (pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP||pt_this->e_dev_setup_enter_reason ==DEVICE_SETUP_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE)
        {
            pt_this->e_dev_setup_enter_reason = DEVICE_SETUP_ENTER_REASON_NONE;
        }
        
        if (a_wzd_is_resume_from_menu_setup())
        {
           a_wzd_exit(); /*Exit Wizard*/
        }
        else
        {
            pt_this->e_pre_state = DEVICE_SETUP_CODE_CONFIRM;
            pt_this->e_state = DEVICE_SETUP_CHOOSE_DEVICE;
            _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
        }
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_timer_paired_show_dialog_nfy_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_timer_paired_show_dialog_nfy_fct(HANDLE_T  h_timer,
                                                                              VOID*     pv_tag)
{
    wzd_async_invoke(_wzd_page_tv_remote_device_setup_do_show_dialog_timer, NULL, 0, FALSE); 
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_full_dlg_set_content
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32  _wzd_page_tv_remote_device_setup_full_dlg_set_content(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    UTF16_T code_w2s[WZD_DEVICE_SETUP_SHOW_MIG_MAX_NUM] = {0};

    wzd_view_full_screen_dlg_set_icon(h_g_wzd_img_checkmark_green_small, FALSE);

    if (pt_this->b_is_device_setup_worked == TRUE)
    {
        _wzd_page_tv_remote_device_setup_confirm_worked_full_dlg_text_connect(code_w2s);
    }
    else 
    {
        _wzd_page_tv_remote_device_setup_confirm_skip_full_dlg_text_connect(code_w2s);
    }

    wzd_view_full_screen_dlg_set_text(code_w2s, FALSE);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_worked_btn_proc_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_worked_btn_proc_fct (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this            = &t_g_tv_remote_device_setup;
    WZD_CONFIRM_PAGE_T*                  pt_confirm_page    = &t_g_device_setup_confirm_page;
    WZD_DEVICE_PAIR_DLG_PAGE_T*          pt_paired_dlg_page = &t_g_device_setup_device_pair_dlg_page;
    //HANDLE_T             h_cb_widget;
    //WGL_NOTIFY_DATA_T*   pt_wgl_nfy_data;
    INT32                i4_ret = WZDR_OK;
    UINT32               pui4_state = 0;

    //h_cb_widget     = (HANDLE_T) pv_param1;
    //pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;
    
    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_DOWN == (UINT32)pv_param1 ) 
        {
            c_wgl_get_state(pt_confirm_page->h_btn_retry, &pui4_state);
            
            if(pui4_state & WGL_STATE_ENABLED)
            {
                RET_ON_ERR (c_wgl_set_focus(pt_confirm_page->h_btn_retry, FALSE));   
            }
            else
            {
                RET_ON_ERR (c_wgl_set_focus(pt_confirm_page->h_btn_manually, FALSE));   
            }
            RET_ON_ERR (wzd_view_main_frm_repaint());
            
            return WZDR_OK;
        }
        if( BTN_SELECT == (UINT32)pv_param1 ) 
        {           
            pt_this->b_is_device_setup_worked = TRUE;
            
            /* set device info */
            i4_ret =_wzd_page_tv_remote_device_setup_set_device_info();  
            DBG_INFO( ("[Ln: %d] set device info!!! i4_ret = %d\n", __LINE__, i4_ret));  
            
            /* Paired successful */
            if (DEVICE_TYPE_SELECT_AUDIO_RECIEVER == pt_this->ui4_type_sel_idx)
            {
                pt_this->b_is_aduio_paired = TRUE;
                pt_this->ui4_type_paired_count[DEVICE_TYPE_SELECT_AUDIO_RECIEVER] = 1;
            } else if (DEVICE_TYPE_SELECT_SOUND_BAR == pt_this->ui4_type_sel_idx)
            {
                pt_this->b_is_soundbar_paired = TRUE;
                pt_this->ui4_type_paired_count[DEVICE_TYPE_SELECT_SOUND_BAR] = 1;  
            }
            else
            {
                pt_this->b_is_paired[pt_this->ui1_sel_src_idx][pt_this->ui4_type_sel_idx] = TRUE;
                pt_this->ui4_type_paired_count[pt_this->ui4_type_sel_idx]++;
            }

            DBG_INFO( ("[Ln: %d] type_paired_idx[%d], src_paired_idx[%d], type_paired_count[%d], is successful!!!\n", __LINE__, 
                        pt_this->ui4_type_sel_idx,
                        pt_this->ui1_sel_src_idx,
                        pt_this->ui4_type_paired_count[pt_this->ui4_type_sel_idx]));   
            
            /* Set dialog */    
            RET_ON_ERR (_wzd_page_tv_remote_device_setup_full_dlg_set_content());
            RET_ON_ERR (wzd_view_full_screen_dlg_show(FALSE));
            t_g_device_setup_input_page.b_is_full_screen_dlg_show = TRUE;
            
            i4_ret = c_timer_start(pt_paired_dlg_page->h_device_pair_dlg_timer, 
                                   5000,
                                   X_TIMER_FLAG_ONCE,
                                   _wzd_page_tv_remote_device_setup_timer_paired_show_dialog_nfy_fct,
                                   NULL);
            RET_ON_ERR (i4_ret);

            wzd_set_power_off_flag(FALSE);
            RET_ON_ERR (_wzd_page_tv_remote_device_setup_init());
            
            return WZDR_OK;
        }
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_retry_btn_proc_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_retry_btn_proc_fct (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    WZD_CONFIRM_PAGE_T*         pt_confirm_page = &t_g_device_setup_confirm_page;
    //HANDLE_T                    h_cb_widget;
    //WGL_NOTIFY_DATA_T*          pt_wgl_nfy_data;
    
    //h_cb_widget     = (HANDLE_T) pv_param1;
    //pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_DOWN == (UINT32)pv_param1 )  
        {
            RET_ON_ERR (c_wgl_set_focus(pt_confirm_page->h_btn_manually, FALSE)); 
            RET_ON_ERR (wzd_view_main_frm_repaint());
            return WZDR_OK;
        }
        
        if( BTN_CURSOR_UP == (UINT32)pv_param1 )  
        {
            RET_ON_ERR (c_wgl_set_focus(pt_confirm_page->h_btn_worked, FALSE));    
            RET_ON_ERR (wzd_view_main_frm_repaint());

            return WZDR_OK;
        }
        
        if( BTN_SELECT == (UINT32)pv_param1 ) 
        {
            DBG_INFO( ("[Ln: %d] pt_this->b_is_i_do_not_know_mdl_sel= %d\n", __LINE__, pt_this->b_is_i_do_not_know_mdl_sel));

            if (pt_this->b_is_i_do_not_know_mdl_sel)
            {
                _wzd_page_tv_remote_device_setup_do_retry_next_code_without_sel_mdl();
            }
            else
            {
                _wzd_page_tv_remote_device_setup_do_retry_next_code();
            }
            RET_ON_ERR (wzd_view_main_frm_repaint());
            return WZDR_OK;
        }
    }
    
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_manually_dlg_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
 static INT32 _wzd_page_tv_remote_device_setup_confirm_manually_dlg_show (VOID)
 {
 	INT32			i4_ret = WZDR_OK;

 	RET_ON_ERR (_wzd_page_tv_remote_device_setup_confirm_manually_dlg_create());
 	
	i4_ret = wzd_dlg_show( t_g_device_setup_confirm_page.h_manually_dlg , FALSE );
	DBG_INFO( ("\n####%s(%d)wzd_dlg_show(h_manually_dlg) return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
	
	/* Set to topmost */
    i4_ret = c_wgl_insert (t_g_device_setup_confirm_page.h_manually_dlg_eb,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    RET_ON_ERR(i4_ret);
    
	i4_ret = c_wgl_set_visibility(t_g_device_setup_confirm_page.h_manually_dlg_eb, WGL_SW_NORMAL);
	RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_focus(t_g_device_setup_confirm_page.h_manually_dlg_eb, WGL_NO_AUTO_REPAINT);
	RET_ON_ERR(i4_ret);
	 
	return WZDR_OK;
 }
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_manually_dlg_hide
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
 static INT32 _wzd_page_tv_remote_device_setup_confirm_manually_dlg_hide (VOID)
 {
	 INT32			i4_ret = WZDR_OK;
	 
	 i4_ret = c_wgl_set_visibility(t_g_device_setup_confirm_page.h_manually_dlg_eb, WGL_SW_HIDE);
	 DBG_INFO( ("\n####%s(%d)c_wgl_set_visibility return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
	 wzd_dlg_hide( t_g_device_setup_confirm_page.h_manually_dlg );
	 
	 return WZDR_OK;
 }

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_manually_dlg_ok_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
 static VOID _wzd_page_tv_remote_device_setup_manually_dlg_ok_fct(
									  VOID*      pv_tag,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
 {
    WZD_CONFIRM_PAGE_T*         pt_confirm_page = &t_g_device_setup_confirm_page;
    INT32 						i4_ret = WZDR_OK;
    
	if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        
        if( BTN_CURSOR_UP == (UINT32)param1 )  
        {
            c_wgl_set_focus(pt_confirm_page->h_manually_dlg_eb, WGL_SYNC_AUTO_REPAINT);    
            wzd_view_main_frm_repaint();
            return;

        }
        
        if( BTN_SELECT == (UINT32)param1 ) 
        {
			_wzd_page_tv_remote_device_setup_confirm_manually_dlg_hide();
			i4_ret = _wzd_page_tv_remote_device_setup_manual_enter_code();
            DBG_INFO( ("\n[%s(Ln: %d)] = %d\n", __FUNCTION__,__LINE__, i4_ret));

		    c_wgl_set_focus(pt_confirm_page->h_btn_manually, WGL_SYNC_AUTO_REPAINT); 

		    return;
        }
    }
    return;
	 
 }
 /*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_manually_dlg_cancel_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
 static VOID _wzd_page_tv_remote_device_setup_manually_dlg_cancel_fct(
									  VOID*      pv_tag,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
 {
    WZD_CONFIRM_PAGE_T*         pt_confirm_page = &t_g_device_setup_confirm_page;
    INT32 						i4_ret = WZDR_OK;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        
        if( BTN_CURSOR_UP == (UINT32)param1 )  
        {
            c_wgl_set_focus(pt_confirm_page->h_manually_dlg_eb, WGL_SYNC_AUTO_REPAINT);    
            return;

        }
        
        if( BTN_SELECT == (UINT32)param1 ) 
        {
			i4_ret = _wzd_page_tv_remote_device_setup_confirm_manually_dlg_hide();
            DBG_INFO( ("\n[%s(Ln: %d)] = %d\n", __FUNCTION__,__LINE__, i4_ret));

		    c_wgl_set_focus(pt_confirm_page->h_btn_manually, WGL_SYNC_AUTO_REPAINT); 
		    
            return;
        }
    }
 }
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_manually_dlg_proc_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
 static VOID _wzd_page_tv_remote_device_setup_manually_dlg_proc_fct(
									  VOID*      pv_tag,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
 {
 

    static wzd_dlg_data_change_nfy_fct  pf_fct = NULL;

    if(WZD_DLG_MSG_BTN_FOCUSED == ui4_msg)
    {
        WZD_DLG_BTN_TYPE_T  t_btn_id = (WZD_DLG_BTN_TYPE_T)(UINT32)param1;

        
        if(WZD_DLG_BTN_TYPE_01 == t_btn_id)
        {
            pf_fct = _wzd_page_tv_remote_device_setup_manually_dlg_ok_fct;
        }
        else
        {
            pf_fct = _wzd_page_tv_remote_device_setup_manually_dlg_cancel_fct;
        }
    }
    else if(pf_fct && WZD_DLG_MSG_KEY_INPUT == ui4_msg)
    {
        pf_fct(pv_tag, WGL_MSG_KEY_DOWN, param1, param2);
    }
    
    return;

 }
 
/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_manual_enter_code
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_manual_enter_code (VOID)
{
    WZD_CONFIRM_PAGE_T*                   pt_confirm_page = &t_g_device_setup_confirm_page;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this = &t_g_tv_remote_device_setup;
    
	INT32       		i4_ret = WZDR_OK;
    UTF16_T             w2s_text[DEV_DB_NAME_LEN_MAX + 1] = {0};

	pt_this->b_is_device_setup_worked = FALSE;
	i4_ret = c_wgl_do_cmd(pt_confirm_page->h_manually_dlg_eb,
				          WGL_CMD_EB_GET_TEXT,
				          WGL_PACK(w2s_text),
				          WGL_PACK(DEV_DB_NAME_LEN_MAX));
    RET_ON_ERR(i4_ret);

    c_uc_w2s_to_ps(w2s_text,pt_this->s_codeset, 32);
    DBG_INFO( ("\n####%s(%d)pt_this->s_codeset=%s\n",__FUNCTION__,__LINE__,pt_this->s_codeset));
    
	i4_ret = a_dev_db_manual_upload_codeset(pt_this->ui4_type_sel_idx, pt_this->s_codeset, (DEV_SETUP_DB_CODESET_LEN_MAX+1));
	
    DBG_INFO( ("\n[####%s(%d)]------a_dev_db_manual_upload_codeset() return:%d -------\n", __FUNCTION__,__LINE__,i4_ret));

	if(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_AUDIO_RECIEVER)
	{	
		c_memset(pt_this->s_aud_amp_type, 0, DEV_SETUP_DB_NAME_LEN_MAX);
		/* set the device type Audio Receiver */
		if((c_strncmp(pt_this->s_codeset,"M",1)==0)||(c_strncmp(pt_this->s_codeset,"R",1)==0))
		{
			c_strncpy(pt_this->s_aud_amp_type, DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME, DEV_SETUP_DB_NAME_LEN_MAX);
		}
		/* set the device type Amplifier */
		else if(c_strncmp(pt_this->s_codeset,"A",1)==0)
		{
			c_strncpy(pt_this->s_aud_amp_type, DEV_DB_TYPE_AMPLIFIER_NAME, DEV_SETUP_DB_NAME_LEN_MAX);
		}
	}

	/* set codeset */
    _wzd_page_tv_remote_device_setup_set_codeset(pt_this->s_codeset);

    return 0;
}

 /*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_manually_dlg_eb_create
 *
 * Description: create edit box on the manually dlg for enter codeset
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
 static INT32 _wzd_page_tv_remote_device_setup_confirm_manually_dlg_eb_fct(
							    HANDLE_T                    h_widget,
							    UINT32                      ui4_msg,
							    VOID*                       param1,
							    VOID*                       param2)
 {
	WZD_CONFIRM_PAGE_T*                   pt_confirm_page = &t_g_device_setup_confirm_page;

	DBG_INFO( ("\n####%s(%d)ui4_msg=%d(%x) param1=%d(%x) \n",__FUNCTION__,__LINE__,ui4_msg,ui4_msg,param1,param1));

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32  				i4_ret = WZDR_OK;
        UTF16_T				w2s_text[32+1] = {0};
	    INT32 				ui4_keycode = (UINT32)param1;
        
        if ((ui4_keycode >= BTN_DIGIT_0) && (ui4_keycode <= BTN_DIGIT_9))
        {
			DBG_INFO( ("\n####%s(%d)BTN_DIGIT_0-9 \n",__FUNCTION__,__LINE__));
	        i4_ret = c_wgl_do_cmd(pt_confirm_page->h_manually_dlg_eb,
							              WGL_CMD_EB_GET_TEXT,
							              (VOID *) w2s_text,
							              (VOID *)32);
			DBG_INFO( ("\n####%s(%d)WGL_CMD_EB_GET_TEXT return[%d] \n",__FUNCTION__,__LINE__,i4_ret));	
			
			RET_ON_ERR(i4_ret); 

			if ( c_uc_w2s_strlen(w2s_text) >= 4 )
			{
				i4_ret = wzd_dlg_set_focus_to_btn(pt_confirm_page->h_manually_dlg, WZD_DLG_BTN_TYPE_01, WGL_SYNC_AUTO_REPAINT);
                DBG_INFO( ("\n####%s(%d)wzd_dlg_set_focus_to_btn return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
				return WZDR_OK;
			}
        }
        switch (ui4_keycode)
        {
            case BTN_CURSOR_DOWN:
            {
                DBG_INFO( ("\n####%s(%d)BTN_CURSOR_DOWN \n",__FUNCTION__,__LINE__));
				i4_ret = wzd_dlg_set_focus_to_btn(pt_confirm_page->h_manually_dlg, WZD_DLG_BTN_TYPE_01, WGL_SYNC_AUTO_REPAINT);
                DBG_INFO( ("\n####%s(%d)wzd_dlg_set_focus_to_btn return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
            }
                break;
            case BTN_CURSOR_LEFT:
            {
            	DBG_INFO( ("\n####%s(%d)BTN_CURSOR_LEFT \n",__FUNCTION__,__LINE__));
                i4_ret = c_wgl_do_cmd(pt_confirm_page->h_manually_dlg_eb,
						              WGL_CMD_EB_GET_TEXT,
						              (VOID *) w2s_text,
						              (VOID *)32);
				RET_ON_ERR(i4_ret);  

                if ( c_uc_w2s_strlen(w2s_text) > 0 )
                {
                    w2s_text[c_uc_w2s_strlen(w2s_text) - 1] = '\0';

                    i4_ret = c_wgl_do_cmd (pt_confirm_page->h_manually_dlg_eb,
                                           WGL_CMD_EB_SET_TEXT,
                                           WGL_PACK (w2s_text),
				                           WGL_PACK (0xFFFF));
                    RET_ON_ERR(i4_ret);

                    RET_ON_ERR (wzd_view_main_frm_repaint());  
                    return WDK_NO_ACTION;
                }
                else
                {
                	return WZDR_OK;
                }
            }
            	break;
            default:
                break ;
        }
    }
	DBG_INFO( ("\n####%s(%d)c_wgl_default_msg_proc \n",__FUNCTION__,__LINE__));
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);  
 }
 /*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_manually_dlg_eb_create
 *
 * Description: create edit box on the manually dlg for enter codeset
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
 static INT32 _wzd_page_tv_remote_device_setup_confirm_manually_dlg_eb_create (HANDLE_T parent)
 {
 	WZD_CONFIRM_PAGE_T*                  pt_confirm_page    = &t_g_device_setup_confirm_page;
 	GL_RECT_T           				 t_rect;
 	INT32								 i4_ret = WZDR_OK;
 	
	/* get rectangle size */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    
	SET_RECT_BY_SIZE (& t_rect,
				WZD_MANUALLY_DLG_EB_X,
				WZD_MANUALLY_DLG_EB_Y,
				WZD_MANUALLY_DLG_EB_W,
				WZD_MANUALLY_DLG_EB_H);
				  
    /* create widget */
    i4_ret = _wzd_page_tv_remote_device_setup_manually_edit_box_create(parent,
                                                              t_rect,
                                                              _wzd_page_tv_remote_device_setup_confirm_manually_dlg_eb_fct,
                                                              &pt_confirm_page->h_manually_dlg_eb);
                                                              
	DBG_INFO( ("\n####%s(%d)_wzd_page_tv_remote_device_setup_edit_box_create()return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
    RET_ON_ERR(i4_ret);  
    return i4_ret;
 }
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_manually_dlg_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
 static INT32 _wzd_page_tv_remote_device_setup_confirm_manually_dlg_create (VOID)
 {
 	WZD_DLG_INIT_T      t_dlg_init;
 	HANDLE_T            h_layout_frm = NULL_HANDLE;
    UTF16_T*            pw2s_dlg_text = NULL;
    UTF16_T*            pw2s_dlg_btn1_text = NULL;
    UTF16_T*            pw2s_dlg_btn2_text = NULL;
    //WZD_CONFIRM_PAGE_T*                  pt_confirm_page    = &t_g_device_setup_confirm_page;
 	
 	c_memset(&t_dlg_init, 0 , sizeof(WZD_DLG_INIT_T));
    wzd_view_get_layout_frm(&h_layout_frm);
    t_dlg_init.h_parent = h_layout_frm;
    t_dlg_init.e_default_focus_btn = WZD_DLG_BTN_TYPE_01;
    t_dlg_init.pf_fct = _wzd_page_tv_remote_device_setup_manually_dlg_proc_fct;

    t_dlg_init.ui4_style_mask = WZD_DLG_STYLE_MASK_2_BTN | WZD_DLG_STYLE_MASK_WITH_DESC;
	pw2s_dlg_text = WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_DLG_MANU_ENTER_CODE_TITLE);

	/* Set Font */
    c_strcpy (t_dlg_init.t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_dlg_init.t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_dlg_init.t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_dlg_init.t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_dlg_init.t_fnt_info.ui1_custom_size = 20;

	pw2s_dlg_btn1_text = WZD_TEXT(MLM_WZD_KEY_DLG_OK);
    pw2s_dlg_btn2_text = WZD_TEXT(MLM_WZD_KEY_HELP_CANCEL);

    wzd_dlg_create( &t_dlg_init, &t_g_device_setup_confirm_page.h_manually_dlg);

    wzd_dlg_set_text( t_g_device_setup_confirm_page.h_manually_dlg, pw2s_dlg_text, FALSE );
    
    wzd_dlg_set_btn_text( t_g_device_setup_confirm_page.h_manually_dlg, WZD_DLG_BTN_TYPE_01,
                          pw2s_dlg_btn1_text, FALSE );
                          
    wzd_dlg_set_btn_text( t_g_device_setup_confirm_page.h_manually_dlg, WZD_DLG_BTN_TYPE_02,
                          pw2s_dlg_btn2_text, FALSE );

    _wzd_page_tv_remote_device_setup_confirm_manually_dlg_eb_create (h_layout_frm);

    return WZDR_OK;

 }
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_manually_btn_proc_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_manually_btn_proc_fct (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    WZD_CONFIRM_PAGE_T*         pt_confirm_page = &t_g_device_setup_confirm_page;
    //HANDLE_T                    h_cb_widget;
    //WGL_NOTIFY_DATA_T*          pt_wgl_nfy_data;
    UINT32                      pui4_state = 0;
    INT32						i4_ret = WZDR_OK;

    //h_cb_widget     = (HANDLE_T) pv_param1;
    //pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_DOWN == (UINT32)pv_param1 )  
        {
            RET_ON_ERR (c_wgl_set_focus(pt_confirm_page->h_btn_back, FALSE)); 
            RET_ON_ERR (wzd_view_main_frm_repaint());
            return WZDR_OK;
        }
        if( BTN_CURSOR_UP == (UINT32)pv_param1 )  
        {
            c_wgl_get_state(pt_confirm_page->h_btn_retry, &pui4_state);
            if(pui4_state & WGL_STATE_ENABLED)
            {
                RET_ON_ERR (c_wgl_set_focus(pt_confirm_page->h_btn_retry, FALSE));   
            }
            else
            {
                RET_ON_ERR (c_wgl_set_focus(pt_confirm_page->h_btn_worked, FALSE));   
            }   
            RET_ON_ERR (wzd_view_main_frm_repaint());

            return WZDR_OK;
        }
        if( BTN_SELECT == (UINT32)pv_param1 ) 
        {
            i4_ret = _wzd_page_tv_remote_device_setup_confirm_manually_dlg_show();
            DBG_INFO( ("\n####%s(%d)_wzd_page_tv_remote_device_setup_manual_enter_code()return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
            RET_ON_ERR (wzd_view_main_frm_repaint());
            
            return WZDR_OK;
        }
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_back_btn_proc_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_back_btn_proc_fct (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this         = &t_g_tv_remote_device_setup;
    WZD_CONFIRM_PAGE_T*                  pt_confirm_page = &t_g_device_setup_confirm_page;
    //HANDLE_T                             h_cb_widget;
    //WGL_NOTIFY_DATA_T*                   pt_wgl_nfy_data;

    //h_cb_widget     = (HANDLE_T) pv_param1;
    //pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_DOWN == (UINT32)pv_param1 )  
        {
            RET_ON_ERR (c_wgl_set_focus(pt_confirm_page->h_btn_skip, FALSE));  
            RET_ON_ERR (wzd_view_main_frm_repaint());
            return WZDR_OK;
        }
        if( BTN_CURSOR_UP == (UINT32)pv_param1 )  
        {
            RET_ON_ERR (c_wgl_set_focus(pt_confirm_page->h_btn_manually, FALSE));    
            RET_ON_ERR (wzd_view_main_frm_repaint());
            return WZDR_OK;
        }
        if( BTN_SELECT == (UINT32)pv_param1 ) 
        {
            wzd_set_power_off_flag(FALSE);
            if (pt_this->b_is_db_locked)
            {
                pt_this->e_pre_state = DEVICE_SETUP_CODE_CONFIRM;
                pt_this->e_state = DEVICE_SETUP_SELECT_BRAND;
            }
            else 
            {
                pt_this->e_pre_state = DEVICE_SETUP_CODE_CONFIRM;
                pt_this->e_state = DEVICE_SETUP_SELECT_MODEL;
            }
            RET_ON_ERR (_wzd_page_tv_remote_device_setup_update_by_state(FALSE));

            RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
            RET_ON_ERR (wzd_view_main_frm_repaint());

            return WZDR_OK;
        }
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_skip_btn_proc_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_page_skip_btn_proc_fct (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this            = &t_g_tv_remote_device_setup;
    WZD_CONFIRM_PAGE_T*                  pt_confirm_page    = &t_g_device_setup_confirm_page;
    WZD_DEVICE_PAIR_DLG_PAGE_T*          pt_paired_dlg_page = &t_g_device_setup_device_pair_dlg_page;
    //HANDLE_T              h_cb_widget;
    //WGL_NOTIFY_DATA_T*    pt_wgl_nfy_data;
    INT32                 i4_ret = WZDR_OK;

    //h_cb_widget     = (HANDLE_T) pv_param1;
    //pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_UP == (UINT32)pv_param1 )  /* Press ok to open signal type list */
        {
            RET_ON_ERR (c_wgl_set_focus(pt_confirm_page->h_btn_back, FALSE));   
            RET_ON_ERR (wzd_view_main_frm_repaint());

            return WZDR_OK;

        }
        if( BTN_SELECT == (UINT32)pv_param1 )  /* Press ok to open signal type list */
        {
            pt_this->b_is_device_setup_worked = FALSE;
            
            /* Set dialog */    
            RET_ON_ERR (_wzd_page_tv_remote_device_setup_full_dlg_set_content());
            RET_ON_ERR (wzd_view_full_screen_dlg_show(FALSE));
            t_g_device_setup_input_page.b_is_full_screen_dlg_show = TRUE;
            RET_ON_ERR (wzd_view_main_frm_repaint());
            
            i4_ret = c_timer_start(pt_paired_dlg_page->h_device_pair_dlg_timer, 
                                   5000,
                                   X_TIMER_FLAG_ONCE,
                                   _wzd_page_tv_remote_device_setup_timer_paired_show_dialog_nfy_fct,
                                   NULL);
            RET_ON_ERR (i4_ret);
            
            wzd_set_power_off_flag(FALSE);
            RET_ON_ERR (_wzd_page_tv_remote_device_setup_init());
            
            return WZDR_OK;
        }
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_paired_dlg_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_paired_dlg_create(VOID)
{
    WZD_DEVICE_PAIR_DLG_PAGE_T* pt_paired_dlg_page = &t_g_device_setup_device_pair_dlg_page;
    
    /* Create show dialog timer */
    c_timer_create(&pt_paired_dlg_page->h_device_pair_dlg_timer);

    return WZDR_OK;
}    

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_code_confirm_page_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_code_confirm_page_create(HANDLE_T  h_parent)
{
    INT32                   i4_ret = WZDR_OK;
    GL_RECT_T               t_rect;
    WGL_INSET_T             t_inset;
    WGL_FONT_INFO_T         t_fnt_info;
    WGL_COLOR_INFO_T        t_color_info_fg;
    WZD_CONFIRM_PAGE_T*     pt_confirm_page = &t_g_device_setup_confirm_page;

    /* description text create */
    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      30 * WZD_UI_RATIO_W,
                      LAYOUT_FRM_W,
                      30 * WZD_UI_RATIO_W);

    i4_ret = _wzd_page_tv_remote_device_setup_confirm_page_desc_create(h_parent,
                                                                       &t_rect,
                                                                       &pt_confirm_page->h_code_desc_txt);                                    
    RET_ON_ERR(i4_ret);     

    /* htxt message append text create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      0 * WZD_UI_RATIO_W,
                      48 * WZD_UI_RATIO_W,
                      LAYOUT_FRM_W,
                      60 * WZD_UI_RATIO_H);
    i4_ret = _wzd_page_tv_remote_device_setup_msg_create(h_parent,
                                                         &t_rect,
                                                         &pt_confirm_page->h_code_htxt_prefix);
                                          
    RET_ON_ERR(i4_ret);
    
    /* htxt message text create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      380 * WZD_UI_RATIO_W,
                      85 * WZD_UI_RATIO_W,
                      LAYOUT_FRM_W,
                      50 * WZD_UI_RATIO_H);
    i4_ret = _wzd_page_tv_remote_device_setup_confirm_page_desc_htxt_create(h_parent,
                                                                            &t_rect,
                                                                            &pt_confirm_page->h_code_htxt);
                                                

    RET_ON_ERR(i4_ret);  
    
    /* code text create */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      150 * WZD_UI_RATIO_W,
                      LAYOUT_FRM_W,
                      45 * WZD_UI_RATIO_H);
    i4_ret = _wzd_page_tv_remote_device_setup_confirm_page_msg_create(h_parent,
                                                                      &t_rect,
                                                                      &pt_confirm_page->h_code_msg_txt);
    RET_ON_ERR(i4_ret);  
  
    /*=================== For create button ===================================*/
    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, WZD_FONT_NAME);

    t_fnt_info.e_font_size  = WZD_FOOTER_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_footer_enable_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_footer_disable_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_footer_hlt_txt);

    /* Create it_worked button */
    SET_RECT_BY_SIZE (& t_rect,
                      250 * WZD_UI_RATIO_W,
                      260 * WZD_UI_RATIO_W,
                      270 * WZD_UI_RATIO_W,
                       78 * WZD_UI_RATIO_W);

    RET_ON_ERR (_wzd_page_tv_remote_device_setup_confirm_create_btn_widget(
                        h_parent,
                        &t_rect,
                        &t_color_info_fg,
                        &t_fnt_info,
                        h_g_wzd_img_button_highlight,
                        h_g_wzd_img_button,                       
                        WGL_AS_CENTER_CENTER,
                        _wzd_page_tv_remote_device_setup_confirm_worked_btn_proc_fct,
                        &pt_confirm_page->h_btn_worked,
                        &t_inset));

    /* Create retry button */
    SET_RECT_BY_SIZE (& t_rect,
                      250 * WZD_UI_RATIO_W,
                      313 * WZD_UI_RATIO_W,
                      270 * WZD_UI_RATIO_W,
                       78 * WZD_UI_RATIO_W);
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_confirm_create_btn_widget(
                        h_parent,
                        &t_rect,
                        &t_color_info_fg,
                        &t_fnt_info,
                        h_g_wzd_img_button_highlight,
                        h_g_wzd_img_button,
                        WGL_AS_CENTER_CENTER,
                        _wzd_page_tv_remote_device_setup_confirm_retry_btn_proc_fct,
                        &pt_confirm_page->h_btn_retry,
                        &t_inset));
                        
    /* Create manually button */
    SET_RECT_BY_SIZE (& t_rect,
                      250 * WZD_UI_RATIO_W,
                      367 * WZD_UI_RATIO_W,
                      270 * WZD_UI_RATIO_W,
                       78 * WZD_UI_RATIO_W);
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_confirm_create_btn_widget(
                        h_parent,
                        &t_rect,
                        &t_color_info_fg,
                        &t_fnt_info,
                        h_g_wzd_img_button_highlight,
                        h_g_wzd_img_button,
                        WGL_AS_CENTER_CENTER,
                        _wzd_page_tv_remote_device_setup_confirm_manually_btn_proc_fct,
                        &pt_confirm_page->h_btn_manually,
                        &t_inset));
                        
    /* Create back button */
    SET_RECT_BY_SIZE (& t_rect,
                      250 * WZD_UI_RATIO_W,
                      431 * WZD_UI_RATIO_W,
                      270 * WZD_UI_RATIO_W,
                       78 * WZD_UI_RATIO_W);
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_confirm_create_btn_widget(
                        h_parent,
                        &t_rect,
                        &t_color_info_fg,
                        &t_fnt_info,
                        h_g_wzd_img_button_highlight,
                        h_g_wzd_img_button,
                        WGL_AS_CENTER_CENTER,
                        _wzd_page_tv_remote_device_setup_confirm_back_btn_proc_fct,
                        &pt_confirm_page->h_btn_back,
                        &t_inset));
                       
    /* Create skip button */
    SET_RECT_BY_SIZE (& t_rect,
                      250 * WZD_UI_RATIO_W,
                      485 * WZD_UI_RATIO_W,
                      270 * WZD_UI_RATIO_W,
                       78 * WZD_UI_RATIO_W);
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_confirm_create_btn_widget(
                        h_parent,
                        &t_rect,
                        &t_color_info_fg,
                        &t_fnt_info,
                        h_g_wzd_img_button_highlight,
                        h_g_wzd_img_button,
                        WGL_AS_CENTER_CENTER,
                        _wzd_page_tv_remote_device_setup_confirm_page_skip_btn_proc_fct,
                        &pt_confirm_page->h_btn_skip,
                        &t_inset));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/                        
static INT32 _wzd_page_tv_remote_device_setup_create (VOID)
{
    HANDLE_T h_layout_frm = NULL_HANDLE;
    
#ifdef APP_UEI_SPINNER_SUPPORT
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
#endif

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    c_memset( &t_g_tv_remote_device_setup, 0, sizeof(WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T) );
    c_memset( &t_g_device_setup_finished_dlg_page, 0, sizeof(WZD_DLG_PAGE_T) );
    c_memset( &t_g_device_setup_select_page, 0, sizeof(WZD_SELECT_PAGE_T) );
    c_memset( &t_g_device_setup_input_page, 0, sizeof(WZD_INPUT_PAGE_T) );
    c_memset( &t_g_device_setup_brand_page, 0, sizeof(WZD_BRAND_PAGE_T) );
    c_memset( &t_g_device_setup_model_page, 0, sizeof(WZD_MODEL_PAGE_T) );
    c_memset( &t_g_device_setup_confirm_page, 0, sizeof(WZD_CONFIRM_PAGE_T) );
    c_memset( &t_g_device_setup_device_pair_dlg_page, 0, sizeof(WZD_DEVICE_PAIR_DLG_PAGE_T) );
        
    RET_ON_ERR ( _wzd_page_tv_remote_device_setup_dlg_create(h_layout_frm) );
    
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_select_device_type_page_create(h_layout_frm) );
    
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_select_input_page_create(h_layout_frm) );

    RET_ON_ERR (_wzd_page_tv_remote_device_setup_select_brand_page_create(h_layout_frm) );

    RET_ON_ERR (_wzd_page_tv_remote_device_setup_select_model_page_create(h_layout_frm) );

    RET_ON_ERR (_wzd_page_tv_remote_device_setup_code_confirm_page_create(h_layout_frm) );

    RET_ON_ERR (_wzd_page_tv_remote_device_setup_paired_dlg_create() );

#ifdef APP_UEI_SPINNER_SUPPORT
    RET_ON_ERR (_wzd_page_wifi_remote_paring_create_animation_icon(h_layout_frm, &pt_this->h_animation));

	RET_ON_ERR (c_timer_create(&pt_this->h_brd_online_timer));
#endif
           
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_finished_dlg_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_finished_dlg_show(BOOL b_repaint)
{
    INT32               i4_ret = WZDR_OK;
    HANDLE_T            h_layout_frm = NULL_HANDLE;
    WZD_DLG_PAGE_T*     pt_finished_dlg_page = &t_g_device_setup_finished_dlg_page;
   
    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));  
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE)); 
    
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
    RET_ON_ERR (wzd_view_title_txt_set_visibility (FALSE));
    RET_ON_ERR (wzd_view_footer_set_visibility (FALSE));

    /* Set main frame no background */
    RET_ON_ERR (wzd_view_set_main_frm_bg(NULL_HANDLE, FALSE)); 
    RET_ON_ERR (wzd_set_stream_play_region(FALSE, FALSE));
     
    i4_ret = _wzd_page_tv_remote_device_setup_finished_dlg_set_icon (h_g_wzd_img_checkmark_green_small);
    RET_ON_ERR (i4_ret);
    
    i4_ret = _wzd_page_tv_remote_device_setup_finished_dlg_set_text (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_FINISHED_IMG));
    RET_ON_ERR (i4_ret);
    
    i4_ret = _wzd_page_tv_remote_device_setup_set_dlg_visibility();
    RET_ON_ERR (i4_ret);
    t_g_device_setup_input_page.b_is_finished_dlg_show = TRUE;
    
    if (b_repaint)
    {
        RET_ON_ERR (wzd_view_main_frm_repaint());
    }

	c_timer_start(pt_finished_dlg_page->h_dlg_timer, 
				  5000,
				  X_TIMER_FLAG_ONCE,
				  _wzd_page_tv_remote_device_setup_finished_btn_dlg_show_nfy_fct,
				  NULL);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_select_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_select_show(BOOL b_repaint)
{
    HANDLE_T h_layout_frm = NULL_HANDLE;
    WZD_SELECT_PAGE_T* pt_select_page = &t_g_device_setup_select_page;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    INT32					   i4_ret = WZDR_OK;
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT 
    CECM_ARC_CTRL_T             t_arc_ctrl;  
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT

    _wzd_page_tv_remote_device_setup_type_sel_box_reset_img();
    
	/* not show power off dlg */
    wzd_set_power_off_flag(FALSE);
    
    /* update vol state */
    a_tv_set_mute(TRUE);
    wzd_enable_vol_key(FALSE);
    
	/*disable ARC*/
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT 
    c_memset(&t_arc_ctrl, 0, sizeof(CECM_ARC_CTRL_T));
    t_arc_ctrl.b_enable = FALSE;
    i4_ret = c_cecm_arc_ctrl(nav_cec_get_mw_handle(), &t_arc_ctrl);
    DBG_INFO( ("\n####%s(%d)c_cecm_arc_ctrl return[%d]\n",__FUNCTION__,__LINE__,i4_ret)); 
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT
    
    i4_ret = a_cfg_get_spdif_type(&(pt_this->e_g_spdif_value));
	DBG_INFO( ("\n####%s(%d)a_cfg_get_spdif_type return[%d],e_g_spdif_value=%d\n",__FUNCTION__,__LINE__,i4_ret,pt_this->e_g_spdif_value)); 

    i4_ret = c_scc_aud_set_spdif_fmt(h_g_acfg_scc_main_aud, SCC_AUD_SPDIF_FMT_OFF);
	DBG_INFO( ("\n####%s(%d)c_scc_aud_set_spdif_fmt return[%d]\n",__FUNCTION__,__LINE__,i4_ret)); 

	// analog audio off temporarily if resume from MENU.
    wzd_turn_on_off_analog_audio_by_mute(0);
    
    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));

    /* Hide select box first */
    RET_ON_ERR (wzd_view_sel_box_show (WZD_SEL_BOX_SHOW_TYPE_HIDE));
	
    /* Set main frame color */
    RET_ON_ERR (wzd_view_set_main_frm_bg(h_g_wzd_img_background, FALSE)); 

    /* Set footer */
    RET_ON_ERR (wzd_view_footer_set_btn_num(1));
    RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_01, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_BTN_FINISHED)));
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_02, FALSE));
    RET_ON_ERR (wzd_view_footer_update_btn_navigation());

    /* Set title */
    if (pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP)
    {
        RET_ON_ERR(wzd_view_title_set_htxt (WZD_TEXT(MLM_WZD_KEY_TV_SETUP_TV_SIGNAL), NULL_HANDLE));
    }
    else
    {	
        RET_ON_ERR(wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_SETUP_TITLE), NULL_HANDLE));
    }

    /* Set description */
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_set_page_text(pt_select_page->h_select_desc_txt, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_SEL_TYPE_MSG)));
	
    /* Set select buttons */
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_set_choose_box_buttons_content());
    
    /* Show page */  
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
	
    RET_ON_ERR (c_wgl_set_visibility (pt_select_page->h_select_desc_txt, WGL_SW_RECURSIVE)); 
    RET_ON_ERR (c_wgl_set_visibility (pt_select_page->h_select_frm, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_focus(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, WGL_NO_AUTO_REPAINT));
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_hlt());
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_choose_box_btns_set_all_unfloat());
    RET_ON_ERR (c_wgl_float(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, TRUE, WGL_NO_AUTO_REPAINT));
    _wzd_page_tv_device_setup_type_update_checkmark();
    RET_ON_ERR (wzd_view_footer_set_visibility(TRUE));
	RET_ON_ERR (wzd_view_title_txt_set_visibility(TRUE));

    if(b_repaint)
    {
        RET_ON_ERR (wzd_view_main_frm_repaint());
    }
    
    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_type_sel_box_reset_img
 *
 * Description: reset background image for the choose device type box (the image was exchanged when animation)
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_type_sel_box_reset_img(VOID)
{
    UINT8                                       ui1_i = 0;
    WGL_IMG_INFO_T      		                t_img_info;
    WZD_SELECT_PAGE_T*                          pt_select_page = &t_g_device_setup_select_page;
    
    /* reset background image for the first row (the image was exchanged when animation)*/
    for (ui1_i = WZD_CB_BTN_01; ui1_i <= WZD_CB_BTN_05; ui1_i++)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_selectbox_small;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_selectbox_small;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_selectbox_small_hlt;

        RET_ON_ERR (c_wgl_do_cmd (pt_select_page->t_sel_box_btn[ui1_i].h_cb_btn_frm,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK (WGL_IMG_BK), /* background image */
                               WGL_PACK (&t_img_info)));
    }

    /* reset background image for the second row (the image was exchanged when animation)*/
    for (ui1_i = WZD_CB_BTN_06; ui1_i <= WZD_CB_BTN_10; ui1_i++)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_selectbox_small_1;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_selectbox_small_1;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_selectbox_small_hlt;

        RET_ON_ERR (c_wgl_do_cmd (pt_select_page->t_sel_box_btn[ui1_i].h_cb_btn_frm,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK (WGL_IMG_BK), /* background image */
                               WGL_PACK (&t_img_info)));
    }

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_input_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_input_show(BOOL b_repaint)
{
    HANDLE_T h_layout_frm = NULL_HANDLE;
    UTF16_T  ps_w2s[WZD_DEVICE_SETUP_SHOW_MIG_MAX_NUM] = {0};
    UINT32   i4_ret = WZDR_OK;  
    WZD_INPUT_PAGE_T*  pt_input_page = &t_g_device_setup_input_page;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT 
    CECM_ARC_CTRL_T             t_arc_ctrl;  
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT

	/* not show power off dlg */
    wzd_set_power_off_flag(FALSE);
    
    /* update vol state */
    a_tv_set_mute(TRUE);
    wzd_enable_vol_key(FALSE);

	/*disable ARC*/
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT 
    c_memset(&t_arc_ctrl, 0, sizeof(CECM_ARC_CTRL_T));
    t_arc_ctrl.b_enable = FALSE;
    i4_ret = c_cecm_arc_ctrl(nav_cec_get_mw_handle(), &t_arc_ctrl);
    DBG_INFO( ("\n####%s(%d)c_cecm_arc_ctrl return[%d]\n",__FUNCTION__,__LINE__,i4_ret)); 
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT

	if(pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP)
	{
	    i4_ret = a_cfg_get_spdif_type(&(pt_this->e_g_spdif_value));
		DBG_INFO( ("\n####%s(%d)a_cfg_get_spdif_type return[%d],e_g_spdif_value=%d\n",__FUNCTION__,__LINE__,i4_ret,pt_this->e_g_spdif_value)); 
	}
		
    i4_ret = c_scc_aud_set_spdif_fmt(h_g_acfg_scc_main_aud, SCC_AUD_SPDIF_FMT_OFF);
    DBG_INFO( ("\n####%s(%d)c_scc_aud_set_spdif_fmt return[%d]\n",__FUNCTION__,__LINE__,i4_ret)); 

    // analog audio off temporarily if resume from MENU.
    wzd_turn_on_off_analog_audio_by_mute(0);
 
    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));

    /* Set main frame color */
    RET_ON_ERR (wzd_view_set_main_frm_bg(h_g_wzd_img_background, FALSE)); 

    /* Set footer */
    RET_ON_ERR (wzd_view_footer_set_btn_num(1));
    RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_01, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_BTN_BACK)));
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_02, FALSE));
    RET_ON_ERR (wzd_view_footer_update_btn_navigation());
    
    /* Set title */
    if (pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP)
    {
        RET_ON_ERR(wzd_view_title_set_htxt (WZD_TEXT(MLM_WZD_KEY_TV_SETUP_TV_SIGNAL), NULL_HANDLE));
    }
    else
    {
        RET_ON_ERR(wzd_view_title_set_htxt (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_INPUT_TITLE), NULL_HANDLE));
    }
    
    /* Set description */
    i4_ret = _wzd_page_tv_remote_device_setup_text_connect (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_SEL_INPUT_MSG), ps_w2s);
    RET_ON_ERR (i4_ret);
    
    i4_ret = _wzd_page_tv_remote_device_setup_set_page_text (pt_input_page->h_input_desc_txt, ps_w2s);
    RET_ON_ERR (i4_ret);

    /* Set select box */
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_create_sel_box ());

    /* Show page */  
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));

    RET_ON_ERR (c_wgl_set_visibility (pt_input_page->h_input_desc_txt, WGL_SW_RECURSIVE));
    RET_ON_ERR (wzd_view_sel_box_set_focus (pt_this->ui1_input_sel_box_idx, FALSE));
    RET_ON_ERR (wzd_view_sel_box_show (WZD_SEL_BOX_SHOW_TYPE_NORMAL));
    _wzd_page_tv_device_setup_input_update_checkmark();
    RET_ON_ERR (wzd_view_footer_set_visibility (TRUE));
	RET_ON_ERR (wzd_view_title_txt_set_visibility(TRUE));

    if(b_repaint)
    {
        RET_ON_ERR (wzd_view_main_frm_repaint());
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_brand_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_brand_show(BOOL b_repaint)
{
    UINT32   i4_ret = WZDR_OK;      
    UTF16_T  ps_w2s[WZD_DEVICE_SETUP_SHOW_MIG_MAX_NUM] = {0};
    HANDLE_T h_layout_frm = NULL_HANDLE;
    GL_RECT_T t_rect;
    WZD_BRAND_PAGE_T* pt_brand_page = &t_g_device_setup_brand_page; 
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT 
    CECM_ARC_CTRL_T             t_arc_ctrl;  
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));   
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));

	/* not show power off dlg */
    wzd_set_power_off_flag(FALSE);

    /* update vol state */
    a_tv_set_mute(TRUE);
    wzd_enable_vol_key(FALSE);

    /*disable ARC*/
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT 
    c_memset(&t_arc_ctrl, 0, sizeof(CECM_ARC_CTRL_T));
    t_arc_ctrl.b_enable = FALSE;
    i4_ret = c_cecm_arc_ctrl(nav_cec_get_mw_handle(), &t_arc_ctrl);
    DBG_INFO( ("\n####%s(%d)c_cecm_arc_ctrl return[%d]\n",__FUNCTION__,__LINE__,i4_ret)); 
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT

	i4_ret = c_scc_aud_set_spdif_fmt(h_g_acfg_scc_main_aud, SCC_AUD_SPDIF_FMT_OFF);
    DBG_INFO( ("\n####%s(%d)c_scc_aud_set_spdif_fmt return[%d]\n",__FUNCTION__,__LINE__,i4_ret));  

    // analog audio off temporarily if resume from MENU.
    wzd_turn_on_off_analog_audio_by_mute(0);
    
    /* Hide select box first */
    RET_ON_ERR (wzd_view_sel_box_show (WZD_SEL_BOX_SHOW_TYPE_HIDE));

    /* Set main frame color */   
    RET_ON_ERR (wzd_view_set_main_frm_bg(h_g_wzd_img_background, FALSE)); /* Change background for close display small video */

    /* Set footer */
    RET_ON_ERR (wzd_view_footer_set_btn_num(2));
    RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_01, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_BTN_NEXT)));
    RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_02, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_BTN_BACK))); 
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_02, TRUE));
    RET_ON_ERR (wzd_view_footer_update_btn_navigation());
    
    /* Set title */
    RET_ON_ERR(wzd_view_title_set_htxt (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_BRAND_TITLE), NULL_HANDLE));

    /* Set description */
    i4_ret = _wzd_page_tv_remote_device_setup_text_connect (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_ENTER_BRAND_MSG), ps_w2s);
    RET_ON_ERR (i4_ret);
    
    i4_ret = _wzd_page_tv_remote_device_setup_set_page_text (pt_brand_page->h_brand_desc_txt, ps_w2s);
    RET_ON_ERR (i4_ret);

    i4_ret = _wzd_page_tv_remote_device_setup_set_page_text_size(pt_brand_page->h_brand_desc_txt);
    RET_ON_ERR (i4_ret);
    
    /* Set message */
    i4_ret = _wzd_page_tv_remote_device_setup_set_page_text (pt_brand_page->h_brand_msg_txt, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_ENTER_BRAND_TIP));
    RET_ON_ERR (i4_ret);

    /*Set list hlt icon */
    SET_RECT_BY_SIZE(&t_rect,
                     WZD_DEVICE_SETUP_LB_HT_ICON_X,
                     WZD_DEVICE_SETUP_LB_HT_ICON_Y,
                     WZD_DEVICE_SETUP_LB_HT_ICON_W,
                     WZD_DEVICE_SETUP_LB_HT_ICON_H );

    RET_ON_ERR (c_wgl_move(pt_brand_page->h_brand_lb_hlt_icon,
                           &t_rect,
                           WGL_NO_AUTO_REPAINT)); 
                           
    /* Show page */
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
	
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_brand_vkb_show ());
    RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_desc_txt, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_msg_txt, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_eb_frm, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_eb_clr, WGL_SW_NORMAL));
    RET_ON_ERR (c_wgl_float (pt_brand_page->h_brand_eb_clr, TRUE, FALSE));
    RET_ON_ERR (c_wgl_set_visibility (pt_brand_page->h_brand_lb_frm, WGL_SW_HIDE_RECURSIVE));
    RET_ON_ERR (wzd_view_footer_set_visibility (TRUE));
	RET_ON_ERR (wzd_view_title_txt_set_visibility(TRUE));

    if(b_repaint)
    {
        RET_ON_ERR (wzd_view_main_frm_repaint());
    }
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_model_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_model_show(BOOL b_repaint)
{
    UINT32   i4_ret = WZDR_OK;       
    UTF16_T  ps_w2s[WZD_DEVICE_SETUP_SHOW_MIG_MAX_NUM] = {0};
    HANDLE_T h_layout_frm = NULL_HANDLE;
    GL_RECT_T t_rect;
    WZD_MODEL_PAGE_T* pt_model_page = &t_g_device_setup_model_page;
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT 
    CECM_ARC_CTRL_T             t_arc_ctrl;  
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT
    
    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));  
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE)); 

	/* not show power off dlg */
    wzd_set_power_off_flag(FALSE);

    /* update vol state */
    a_tv_set_mute(TRUE);
    wzd_enable_vol_key(FALSE);

	/*disable ARC*/
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT 
    c_memset(&t_arc_ctrl, 0, sizeof(CECM_ARC_CTRL_T));
    t_arc_ctrl.b_enable = FALSE;
    i4_ret = c_cecm_arc_ctrl(nav_cec_get_mw_handle(), &t_arc_ctrl);
    DBG_INFO( ("\n####%s(%d)c_cecm_arc_ctrl return[%d]\n",__FUNCTION__,__LINE__,i4_ret)); 
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT

    i4_ret = c_scc_aud_set_spdif_fmt(h_g_acfg_scc_main_aud, SCC_AUD_SPDIF_FMT_OFF);
    DBG_INFO( ("\n####%s(%d)c_scc_aud_set_spdif_fmt return[%d]\n",__FUNCTION__,__LINE__,i4_ret)); 

    // analog audio off temporarily if resume from MENU.
    wzd_turn_on_off_analog_audio_by_mute(0);

    /* Hide select box first */
    RET_ON_ERR (wzd_view_sel_box_show (WZD_SEL_BOX_SHOW_TYPE_HIDE));
    
    /* Set main frame color */
    RET_ON_ERR (wzd_view_set_main_frm_bg(h_g_wzd_img_background, FALSE)); /* Change background for close display small video */

    /* Set footer */
    RET_ON_ERR (wzd_view_footer_set_btn_num(2));
    RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_01, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_BTN_NEXT)));
    RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_02, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_BTN_UNKNOWN_MODEL))); 
    
    /* Set title */
    RET_ON_ERR(wzd_view_title_set_htxt (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_MODEL_TITLE), NULL_HANDLE));

    /* Set description */
    i4_ret = _wzd_page_tv_remote_device_setup_text_connect (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_ENTER_MODEL_MSG), ps_w2s);
    RET_ON_ERR (i4_ret);
    
    i4_ret = _wzd_page_tv_remote_device_setup_set_page_text (pt_model_page->h_model_desc_txt, ps_w2s);
    RET_ON_ERR (i4_ret);

    i4_ret = _wzd_page_tv_remote_device_setup_set_page_text_size(pt_model_page->h_model_desc_txt);
    RET_ON_ERR (i4_ret);
    
    /* Set message */
    i4_ret = _wzd_page_tv_remote_device_setup_set_page_text (pt_model_page->h_model_msg_txt, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_ENTER_MODEL_TIP));
    RET_ON_ERR (i4_ret);

    /*Set list hlt icon */
    SET_RECT_BY_SIZE(&t_rect,
                     WZD_DEVICE_SETUP_LB_HT_ICON_X,
                     WZD_DEVICE_SETUP_LB_HT_ICON_Y,
                     WZD_DEVICE_SETUP_LB_HT_ICON_W,
                     WZD_DEVICE_SETUP_LB_HT_ICON_H );

    RET_ON_ERR (c_wgl_move(pt_model_page->h_model_lb_hlt_icon,
                           &t_rect,
                           WGL_NO_AUTO_REPAINT)); 
    
    /* Show page */
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
	
    RET_ON_ERR (wzd_view_footer_set_visibility (TRUE));
    RET_ON_ERR (_wzd_page_tv_remote_device_setup_model_vkb_show ());
    RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_desc_txt, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_msg_txt, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_eb_frm, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_eb_clr, WGL_SW_NORMAL));
    RET_ON_ERR (c_wgl_float (pt_model_page->h_model_eb_clr, TRUE, FALSE));
    RET_ON_ERR (c_wgl_set_visibility (pt_model_page->h_model_lb_frm, WGL_SW_HIDE_RECURSIVE));
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_02, TRUE));
    RET_ON_ERR (wzd_view_footer_update_btn_navigation());
	RET_ON_ERR (wzd_view_title_txt_set_visibility(TRUE));

    if(b_repaint)
    {
        RET_ON_ERR (wzd_view_main_frm_repaint());
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_htxt_show_update
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_htxt_show_update(VOID)
{
    WZD_CONFIRM_PAGE_T* pt_confirm_page = &t_g_device_setup_confirm_page;
    ISO_639_LANG_T s639_lang = {0};
    GL_RECT_T      t_rect    = {0};
    INT32          i4_ret    = WZDR_OK;

    /* move line3 hlep text position */
    SET_RECT_BY_SIZE(&t_rect,
                     0 * WZD_UI_RATIO_W,
                     48 * WZD_UI_RATIO_W,
                     LAYOUT_FRM_W,
                     60 * WZD_UI_RATIO_H);                           
    RET_ON_ERR (c_wgl_move(pt_confirm_page->h_code_htxt_prefix,
                           &t_rect,
                           WGL_NO_AUTO_REPAINT));
    
    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret == WZDR_OK)
    {
        if (c_strncmp(s639_lang, s639_app_cfg_lang_spa, ISO_639_LANG_LEN) == 0 ||
             c_strncmp (s639_lang, s639_app_cfg_lang_esl, ISO_639_LANG_LEN) == 0)
        {
            /* move line4 hlep text position */
            SET_RECT_BY_SIZE(&t_rect,
                             265 * WZD_UI_RATIO_W,
                             85 * WZD_UI_RATIO_W,
                             LAYOUT_FRM_W,
                             50 * WZD_UI_RATIO_H);
                             
            RET_ON_ERR (c_wgl_move(pt_confirm_page->h_code_htxt,
                                   &t_rect,
                                   WGL_NO_AUTO_REPAINT));
         }
         else if (c_strncmp (s639_lang, s639_app_cfg_lang_fre, ISO_639_LANG_LEN) == 0 ||
             c_strncmp(s639_lang, s639_app_cfg_lang_fra, ISO_639_LANG_LEN) == 0)
         {
            /* move line4 hlep text position */
            SET_RECT_BY_SIZE(&t_rect,
                             315 * WZD_UI_RATIO_W,
                             85 * WZD_UI_RATIO_W,
                             LAYOUT_FRM_W,
                             50 * WZD_UI_RATIO_H);
                             
            RET_ON_ERR (c_wgl_move(pt_confirm_page->h_code_htxt,
                                   &t_rect,
                                   WGL_NO_AUTO_REPAINT));
         }
         else 
         {
            /* move line4 hlep text position */
            SET_RECT_BY_SIZE(&t_rect,
                             380 * WZD_UI_RATIO_W,
                             85 * WZD_UI_RATIO_W,
                             LAYOUT_FRM_W,
                             50 * WZD_UI_RATIO_H);
                             
            RET_ON_ERR (c_wgl_move(pt_confirm_page->h_code_htxt,
                                   &t_rect,
                                   WGL_NO_AUTO_REPAINT));
         }
         
     }
         
     return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_soundbar_help_text_show_update
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_soundbar_help_text_show_update(VOID)
{
    WZD_CONFIRM_PAGE_T* pt_confirm_page = &t_g_device_setup_confirm_page;
    GL_RECT_T      t_rect    = {0};
    
    /* move htxt message append text */
    SET_RECT_BY_SIZE(&t_rect,
                     0 * WZD_UI_RATIO_W,
                     60 * WZD_UI_RATIO_W,
                     LAYOUT_FRM_W,
                     60 * WZD_UI_RATIO_H);
                       
    RET_ON_ERR (c_wgl_move(pt_confirm_page->h_code_htxt_prefix,
                           &t_rect,
                           WGL_NO_AUTO_REPAINT));                    

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_confirm_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_confirm_show(BOOL b_repaint)
{
    UINT32  i4_ret;
    UTF16_T ps_w2s[WZD_DEVICE_SETUP_SHOW_MIG_MAX_NUM] = {0};
    HANDLE_T h_layout_frm = NULL_HANDLE;
    WZD_CONFIRM_PAGE_T* pt_confirm_page = &t_g_device_setup_confirm_page;
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this = &t_g_tv_remote_device_setup;
    BOOL						 b_is_mute = 0;
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT 
    CECM_ARC_CTRL_T             t_arc_ctrl;  
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT

    RET_ON_ERR (wzd_view_get_layout_frm (&h_layout_frm));  
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE)); 

    /* update vol state  */
    wzd_enable_vol_key(TRUE);

	/*enable ARC*/
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT 
    c_memset(&t_arc_ctrl, 0, sizeof(CECM_ARC_CTRL_T));
    t_arc_ctrl.b_enable = TRUE;
    i4_ret = c_cecm_arc_ctrl(nav_cec_get_mw_handle(), &t_arc_ctrl);
    DBG_INFO( ("\n####%s(%d)c_cecm_arc_ctrl return[%d]\n",__FUNCTION__,__LINE__,i4_ret)); 
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT
    
    b_is_mute = wzd_get_mute_status();
    DBG_INFO( ("\n####%s(%d)b_is_mute=%d\n",__FUNCTION__,__LINE__,b_is_mute));
    
    a_tv_set_mute(wzd_get_mute_status());

    i4_ret = a_cfg_set_spdif_type(pt_this->e_g_spdif_value);
    DBG_INFO( ("\n####%s(%d)i4_ret=%d,pt_this->e_g_spdif_value=%d\n",__FUNCTION__,__LINE__,i4_ret,pt_this->e_g_spdif_value));
    
    i4_ret = a_cfg_update_spdif_type();
    DBG_INFO( ("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));

    // analog audio on.
    wzd_turn_on_off_analog_audio_by_mute(1);

    /* power key press*/  
    wzd_set_power_off_flag(TRUE);

    /* Hide select box first */
    RET_ON_ERR (wzd_view_sel_box_show (WZD_SEL_BOX_SHOW_TYPE_HIDE));
    
    /* Set main frame color */
    RET_ON_ERR (wzd_view_set_main_frm_bg (h_g_wzd_img_background_with_box, FALSE)); /* Change background for close display small video */
    
    /* Set title */
    RET_ON_ERR(wzd_view_title_set_htxt (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_CONFIRM_TITLE), NULL_HANDLE));

    /* Set description */
    i4_ret = _wzd_page_tv_remote_device_setup_text_connect (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_CONFIRM_CONNECT), ps_w2s);
    RET_ON_ERR (i4_ret);
    
    i4_ret = _wzd_page_tv_remote_device_setup_set_page_text (pt_confirm_page->h_code_desc_txt, ps_w2s);
    RET_ON_ERR (i4_ret);

    i4_ret = _wzd_page_tv_remote_device_setup_set_page_text_size(pt_confirm_page->h_code_desc_txt);
    RET_ON_ERR (i4_ret);

    if (pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_AUDIO_RECIEVER || pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_SOUND_BAR)
    {
        /* Set htxt message */
        i4_ret = _wzd_page_tv_remote_device_setup_set_page_text (pt_confirm_page->h_code_htxt_prefix, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_CONFIRM_AUDIO_DEV_MIG));
        RET_ON_ERR (i4_ret);

        i4_ret = _wzd_page_tv_remote_device_setup_set_page_text_size(pt_confirm_page->h_code_htxt_prefix);
        RET_ON_ERR (i4_ret);

        i4_ret = _wzd_page_tv_remote_device_setup_confirm_soundbar_help_text_show_update();
        DBG_INFO( ("[Ln: %d] _wzd_page_tv_remote_device_setup_confirm_soundbar_help_text_show_update()!!!! i4_ret = %d\n", __LINE__, i4_ret)); 
        RET_ON_ERR (i4_ret);
        
        RET_ON_ERR (c_wgl_set_visibility (pt_confirm_page->h_code_htxt_prefix, WGL_SW_RECURSIVE));
        RET_ON_ERR (c_wgl_set_visibility (pt_confirm_page->h_code_htxt, WGL_SW_HIDE));
    }
    else 
    {
        /* Set htxt prefix message */
        i4_ret = _wzd_page_tv_remote_device_setup_set_page_text (pt_confirm_page->h_code_htxt_prefix, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_CONFIRM_HTXT_MIG));
        RET_ON_ERR (i4_ret);

        i4_ret = _wzd_page_tv_remote_device_setup_set_page_text_size(pt_confirm_page->h_code_htxt_prefix);
        RET_ON_ERR (i4_ret);

        /* Set htxt message */
        i4_ret = _wzd_page_tv_remote_device_setup_confirm_page_set_desc_htxt (pt_confirm_page->h_code_htxt, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_CONFIRM_HTXT_MIG_APPEND), h_g_wzd_img_Remote_Key_Device_Power);
        RET_ON_ERR (i4_ret);

        i4_ret = _wzd_page_tv_remote_device_setup_confirm_htxt_show_update();
        DBG_INFO( ("[Ln: %d] _wzd_page_tv_remote_device_setup_confirm_htxt_show_update()!!!! i4_ret = %d\n", __LINE__, i4_ret)); 
        RET_ON_ERR (i4_ret);

        RET_ON_ERR (c_wgl_set_visibility (pt_confirm_page->h_code_htxt_prefix, WGL_SW_RECURSIVE));
        RET_ON_ERR (c_wgl_set_visibility (pt_confirm_page->h_code_htxt, WGL_SW_RECURSIVE));
    }
   
    /* Set code message */
    i4_ret = _wzd_page_tv_remote_device_setup_set_page_text_size(pt_confirm_page->h_code_msg_txt);
    RET_ON_ERR (i4_ret);
    
    /* Set button text */
    i4_ret = _wzd_page_tv_remote_device_setup_confirm_set_button_text();
    RET_ON_ERR (i4_ret);
    
    /* Show page */
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));

    RET_ON_ERR (wzd_view_footer_set_visibility(FALSE));
	RET_ON_ERR (wzd_view_title_txt_set_visibility(TRUE));
    RET_ON_ERR (c_wgl_set_visibility (pt_confirm_page->h_code_desc_txt, WGL_SW_RECURSIVE));
 
    RET_ON_ERR (c_wgl_set_visibility (pt_confirm_page->h_code_msg_txt, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (pt_confirm_page->h_btn_worked, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (pt_confirm_page->h_btn_retry, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (pt_confirm_page->h_btn_manually, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (pt_confirm_page->h_btn_back, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (pt_confirm_page->h_btn_skip, WGL_SW_RECURSIVE));
    RET_ON_ERR (c_wgl_set_focus (pt_confirm_page->h_btn_worked, FALSE));

    if(b_repaint)
    {
        RET_ON_ERR (wzd_view_main_frm_repaint());
    }
    
    return WZDR_OK;
}
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_amp_plug_dlg_show_do_timer
 *
 * Description: 
 *
 * Inputs:	-
 *
 * Outputs: -
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_amp_plug_dlg_show_do_timer(VOID* pv_data,
																			SIZE_T	z_data_size)
{
    WZD_DLG_PAGE_T*     pt_finished_dlg_page = &t_g_device_setup_finished_dlg_page;
	
	c_timer_stop(pt_finished_dlg_page->h_amp_plug_dlg_timer);
	
	_wzd_page_tv_remote_device_setup_finished_dlg_show (TRUE); 
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_amp_plug_dlg_show_nfy_fct
 *
 * Description: 
 *
 * Inputs:	-
 *
 * Outputs: -
 *
 * Returns: 0				   Successful.
 * Any other values 		   Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_amp_plug_dlg_show_nfy_fct(HANDLE_T	h_timer,
																		   VOID*	 pv_tag)
{
	wzd_async_invoke(_wzd_page_tv_remote_device_setup_amp_plug_dlg_show_do_timer, NULL, 0, FALSE); 
}
#endif
#endif
#endif

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_update_by_state
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_update_by_state(BOOL b_repaint)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*   pt_this = &t_g_tv_remote_device_setup;
    WZD_ANIM_MOVE_PAGE_TYPE_T              e_move_hide_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;
    WZD_ANIM_MOVE_PAGE_TYPE_T              e_move_show_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;


    if (DEVICE_SETUP_CHOOSE_DEVICE == pt_this->e_state)
    {
        if ((DEVICE_SETUP_SELECT_INPUT == pt_this->e_pre_state) ||
            (DEVICE_SETUP_SELECT_BRAND == pt_this->e_pre_state) ||
            (DEVICE_SETUP_CODE_CONFIRM == pt_this->e_pre_state))
        {
            e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_RIGHT;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_LEFT_TO_CENTER;
        }
        
        /* start hide move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_hide_type));

        pt_this->ui4_type_sel_idx = 0XFFFFFFFF;
        RET_ON_ERR (_wzd_page_tv_remote_device_setup_select_show (b_repaint)); 
        
        /* start show move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_show_type));

    }
    else if (DEVICE_SETUP_SELECT_INPUT == pt_this->e_state)
    {
        if (DEVICE_SETUP_SELECT_BRAND == pt_this->e_pre_state)
        {
            e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_RIGHT;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_LEFT_TO_CENTER;
        }
        else if (DEVICE_SETUP_CHOOSE_DEVICE == pt_this->e_pre_state)
        {
            e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER;
        }
        
        /* start hide move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_hide_type));

        pt_this->ui1_sel_src_idx = 0XFF;
        RET_ON_ERR (_wzd_page_tv_remote_device_setup_input_show (b_repaint));
        
        /* start show move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_show_type));

    }
    else if (DEVICE_SETUP_SELECT_BRAND == pt_this->e_state)
    {
        if ((DEVICE_SETUP_SELECT_MODEL == pt_this->e_pre_state) ||
            (DEVICE_SETUP_CODE_CONFIRM == pt_this->e_pre_state))
        {
            e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_RIGHT;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_LEFT_TO_CENTER;
        }
        else if ((DEVICE_SETUP_CHOOSE_DEVICE == pt_this->e_pre_state) ||
                 (DEVICE_SETUP_SELECT_INPUT == pt_this->e_pre_state))
        {
            e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER;
        }

        /* start hide move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_hide_type));

        RET_ON_ERR (_wzd_page_tv_remote_device_setup_brand_show (b_repaint));
        
        /* start show move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_show_type));

    }
    else if (DEVICE_SETUP_SELECT_MODEL == pt_this->e_state)
    {
        if (DEVICE_SETUP_CODE_CONFIRM == pt_this->e_pre_state)
        {
            e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_RIGHT;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_LEFT_TO_CENTER;
        }
        else if (DEVICE_SETUP_SELECT_BRAND == pt_this->e_pre_state)
        {
            e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER;
        }

        /* start hide move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_hide_type));

        RET_ON_ERR (_wzd_page_tv_remote_device_setup_model_show (b_repaint));
        
        /* start show move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_show_type));

    }
    else if (DEVICE_SETUP_CODE_CONFIRM == pt_this->e_state)
    {
#ifndef APP_UEI_SPINNER_SUPPORT

        e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT;
        e_move_show_type = WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER;

        /* start hide move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_hide_type));

        RET_ON_ERR (_wzd_page_tv_remote_device_setup_confirm_show (b_repaint));
        
        /* start show move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_show_type));

#else
        RET_ON_ERR (_wzd_page_tv_remote_device_setup_confirm_show (b_repaint));
#endif
    }
    else if (DEVICE_SETUP_FINISHED == pt_this->e_state)
    {
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY

		WZD_DLG_PAGE_T* 	pt_finished_dlg_page = &t_g_device_setup_finished_dlg_page;

		if(b_g_is_amp_plug_dlg_show == FALSE)
		{
			nav_cec_custom_amp_plug_dlg_show();
			
			c_timer_start(pt_finished_dlg_page->h_amp_plug_dlg_timer, 
						  5000,
						  X_TIMER_FLAG_ONCE,
						  _wzd_page_tv_remote_device_setup_amp_plug_dlg_show_nfy_fct,
						  NULL); 
			
		}
		else
#endif
#endif
#endif
        RET_ON_ERR (_wzd_page_tv_remote_device_setup_finished_dlg_show (b_repaint)); 
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_dsty
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_dsty(VOID)
{
#ifdef APP_UEI_SPINNER_SUPPORT
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this              = &t_g_tv_remote_device_setup;
	
	if (pt_this->h_timer != NULL_HANDLE)
    {
        RET_ON_ERR (c_timer_delete(pt_this->h_timer));
        pt_this->h_timer = NULL_HANDLE;
    }

    if (pt_this->h_brd_online_timer != NULL_HANDLE)
    {
        RET_ON_ERR (c_timer_delete(pt_this->h_brd_online_timer));
        pt_this->h_brd_online_timer = NULL_HANDLE;
    }
#endif	
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_on_show
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_on_show (UINT32  ui4_page_id)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*  pt_this              = &t_g_tv_remote_device_setup;

    BOOL    b_db_status = FALSE;
    INT32   i4_ret = WZDR_OK;
    DEV_DB_LOCK_CHECK_COND_T e_check_cond = DEV_DB_LOCK_CHECK_COND_NONE;
    DEV_DB_DEV_TYPE_CTGY_T  				e_dev_type_category = DEV_DB_DEV_TYPE_CTGY_NONE;
	UINT8                               	status             = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;

    c_wgl_img_cache_flush();

    i4_ret = a_dev_db_check_lock_info( e_check_cond, &b_db_status );
    if (WZDR_OK != i4_ret) 
    {
        DBG_INFO( ("\n[Ln:%d] a_dev_db_check_lock_info() i4_ret = %d , check_cond = %d, b_db_status = %d\n", __LINE__, i4_ret, e_check_cond, b_db_status));
    }

    if ((WZDR_OK == i4_ret) && (b_db_status)) /* should check the return value and the lock status*/
    {
        pt_this->b_is_db_locked = TRUE;
        pt_this->ui4_mdl_sel_idx = 0xFFFFFFFF;
    }
    else
    {
        pt_this->b_is_db_locked = FALSE;
    }

    if (FALSE == pt_this->b_is_notify_reg)
    {
        i4_ret = a_dev_db_register(_wzd_page_tv_remote_device_setup_dev_db_online_query, (VOID*) pt_this, &(pt_this->ui4_nfy_id) );
        if (WZDR_OK != i4_ret)
        {
            DBG_INFO( ("[Ln: %d][nav_dev_db] a_dev_db_register() i4_ret = %d\n", __LINE__, i4_ret));
            return i4_ret;
        }
    }

    DBG_INFO( ("[Ln: %d] [PAIRED] e_dev_setup_enter_reason = %d\n", __LINE__, pt_this->e_dev_setup_enter_reason));

    pt_this->b_is_notify_reg = TRUE;

	if(pt_this->e_dev_setup_enter_reason != DEVICE_SETUP_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE)
	{
	    RET_ON_ERR( _wzd_page_tv_remote_device_setup_reset_type_info() );
	    RET_ON_ERR( _wzd_page_tv_remote_device_setup_reset_brand_info() );
	    RET_ON_ERR( _wzd_page_tv_remote_device_setup_reset_model_info() );
	    RET_ON_ERR( _wzd_page_tv_remote_device_setup_codeset_info() );

	    /* get origin input src */
	    c_memset(&pt_this->t_isl_rec, 0, sizeof(ISL_REC_T));
	    RET_ON_ERR (a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &pt_this->t_isl_rec));
	}
    if (pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP_ANTENNA_NOT_PAIR)/* not pair*/
    {
        DBG_INFO( ("[Ln: %d] [NOT PAIR] e_dev_setup_enter_reason = %d\n", __LINE__, pt_this->e_dev_setup_enter_reason));
        pt_this->e_dev_setup_enter_reason = DEVICE_SETUP_ENTER_REASON_NONE;

        pt_this->e_pre_state = DEVICE_SETUP_STATE_HIDE;
        pt_this->e_state = DEVICE_SETUP_FINISHED;
        _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
    }
    else if (pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP) /* pair*/
    {       
        DBG_INFO( ("[Ln: %d] [PAIRED] e_dev_setup_enter_reason = %d\n", __LINE__, pt_this->e_dev_setup_enter_reason));

		i4_ret = a_dev_db_get_dev_type_category(&e_dev_type_category);
		DBG_INFO( ("\n####%s(%d)a_dev_db_get_dev_type_category [return %d]\n",__FUNCTION__,__LINE__,i4_ret));
		
		i4_ret = a_cfg_get_gui_lang(pt_this->crn_s639_lang);
		DBG_INFO( ("\n####%s(%d)a_cfg_get_gui_lang [return %d]pt_this->crn_s639_lang=%s\n",__FUNCTION__,__LINE__,i4_ret,pt_this->crn_s639_lang));
	
		if((e_dev_type_category != DEV_DB_DEV_TYPE_CTGY_ALL_DEV)||(c_strncmp(pt_this->crn_s639_lang, pt_this->pre_s639_lang, ISO_639_LANG_LEN) != 0))
		{
	        RET_ON_ERR( a_dev_db_update_dev_type(DEV_DB_DEV_TYPE_CTGY_ALL_DEV));  
	        c_strncpy(pt_this->pre_s639_lang, pt_this->crn_s639_lang, ISO_639_LANG_LEN);
			DBG_INFO( ("\n####%s(%d)a_cfg_get_gui_lang [return %d]pt_this->pre_s639_lang=%s,pt_this->crn_s639_lang=%s\n",__FUNCTION__,__LINE__,i4_ret,pt_this->pre_s639_lang,pt_this->crn_s639_lang));
        }
        RET_ON_ERR( a_dev_db_get_dev_type_ex(pt_this->t_dev_type, &pt_this->ui4_type_num));     
        c_strncpy( pt_this->s_type_name, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, DEV_SETUP_DB_NAME_LEN_MAX);   
        pt_this->e_pre_state = DEVICE_SETUP_STATE_HIDE;
        pt_this->e_state = DEVICE_SETUP_SELECT_INPUT;
        _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
    }
	else if(pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE)
	{
		a_cfg_custom_get_wifi_remote_pair_status(&status);
		if(status == WIFI_REMOTE_PAIR_STATUS_PAIRED)
		{
		    DBG_INFO( ("[Ln: %d] [PAIRED] e_dev_setup_enter_reason = %d\n", __LINE__, pt_this->e_dev_setup_enter_reason));
		    pt_this->ui4_sel_box_idx = 0;
		    pt_this->e_pre_state = DEVICE_SETUP_STATE_HIDE;
		    pt_this->e_state = DEVICE_SETUP_SELECT_BRAND;
		    _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
			pt_this->e_dev_setup_enter_reason = DEVICE_SETUP_ENTER_REASON_NONE;
		}
		else
		{
		    /* show the full dialg after the page anim is finish */

            pt_this->e_pre_state = DEVICE_SETUP_STATE_HIDE;
    		pt_this->e_state = DEVICE_SETUP_SELECT_INPUT;
    	    _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
		}
	}
    else 
    {
        DBG_INFO( ("[Ln: %d] [PAIRED] e_dev_setup_enter_reason = %d\n", __LINE__, pt_this->e_dev_setup_enter_reason));
        pt_this->ui4_sel_box_idx = 0;
        pt_this->ui1_input_sel_box_idx = 0;
        pt_this->e_pre_state = DEVICE_SETUP_STATE_HIDE;
        pt_this->e_state = DEVICE_SETUP_CHOOSE_DEVICE;
        _wzd_page_tv_remote_device_setup_update_by_state(FALSE);
    }
#ifdef APP_UEI_SPINNER_SUPPORT
    RET_ON_ERR (c_timer_create(&pt_this->h_timer)); /*Create timer*/
#endif

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_on_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_on_hide(UINT32 ui4_page_id)
{
    HANDLE_T h_layout_frm = NULL_HANDLE;
	
    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
    RET_ON_ERR (a_dev_db_clean_codeset_list());

    wzd_page_tv_remote_device_reset_page_show_flag();

    c_wgl_img_cache_flush();
	
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_finished_btn_do_show_dlg_timer
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_finished_btn_do_show_dlg_timer(VOID* pv_data,
                                                                            SIZE_T  z_data_size)
{
    _wzd_page_tv_remote_device_setup_finished_dlg_hide();
    _wzd_page_tv_remote_device_setup_reset_device_info();
    wzd_page_goto( WZD_PAGE_NAVI_LAST_VALID_ITEM );
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_finished_btn_dlg_show_nfy_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_finished_btn_dlg_show_nfy_fct(HANDLE_T  h_timer,
                                                                           VOID*     pv_tag)
{
    wzd_async_invoke(_wzd_page_tv_remote_device_setup_finished_btn_do_show_dlg_timer, NULL, 0, FALSE); 
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_update_codeset_exciption_handle
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_remote_device_setup_update_codeset_exciption_handle(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T* pt_this         = &t_g_tv_remote_device_setup;
    WZD_CONFIRM_PAGE_T*                  pt_confirm_page = &t_g_device_setup_confirm_page;

    c_wgl_enable(pt_confirm_page->h_btn_retry, FALSE);
    c_wgl_repaint(pt_confirm_page->h_btn_retry, NULL, TRUE);

    pt_this->b_is_codeset_query_fail = TRUE;
    _wzd_page_tv_remote_device_setup_confirm_code_chang_lang(0, TRUE);
    DBG_INFO( ("[Ln: %d] pt_this->b_is_codeset_query_fail = %d, pt_this->ui1_cur_code_pos = %d\n", __LINE__, pt_this->b_is_codeset_query_fail, pt_this->ui1_cur_code_pos));

    pt_this->e_pre_state = DEVICE_SETUP_SELECT_BRAND;
    pt_this->e_state = DEVICE_SETUP_CODE_CONFIRM;
    _wzd_page_tv_remote_device_setup_update_by_state(TRUE);

    return WZDR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_return_nfy_cb
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *          
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_return_nfy_cb(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*      pt_this = &t_g_tv_remote_device_setup;

    switch (pt_this->e_state)
    {
        case DEVICE_SETUP_CHOOSE_DEVICE:
        {
            _wzd_page_tv_remote_device_setup_select_device_page_back_resume();
        }
            break;
        case DEVICE_SETUP_SELECT_INPUT:
        {
			if((!t_g_device_setup_input_page.b_is_full_screen_dlg_show)&&(!t_g_device_setup_input_page.b_is_finished_dlg_show))
			{
                _wzd_page_tv_remote_device_setup_input_page_back_resume();
            }
        }
            break;
        case DEVICE_SETUP_SELECT_BRAND:
        {
            _wzd_page_tv_remote_device_setup_brand_page_back_resume();
        }
            break;
        case DEVICE_SETUP_SELECT_MODEL:
        {
            _wzd_page_tv_remote_device_setup_model_page_back_resume();
        }
            break;            
        case DEVICE_SETUP_CODE_CONFIRM: 
        {
            _wzd_page_tv_remote_device_setup_confirm_page_back_resume();
        }
            break;
        default:
            break;
    }
    
    return;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_on_footer_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_on_footer_nfy(
                                         UINT32   ui4_msg,
                                         VOID*    pv_param1,
                                         VOID*    pv_param2)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*      pt_this              = &t_g_tv_remote_device_setup;
    WZD_SELECT_PAGE_T*                        pt_select_page       = &t_g_device_setup_select_page;
    WZD_BRAND_PAGE_T*                         pt_brand_page        = &t_g_device_setup_brand_page;
    WZD_MODEL_PAGE_T*                         pt_model_page        = &t_g_device_setup_model_page;
    ISL_REC_T                                 t_isl_rec            = {0};
    UTF16_T                                   s_brd_name[DEV_SETUP_DB_NAME_LEN_MAX + 1] = {0};
    UTF16_T                                   s_mdl_name[DEV_SETUP_DB_NAME_LEN_MAX + 1] = {0};
    INT32                                     i4_ret = WZDR_OK;
	BOOL 									  b_visible = FALSE;
	HANDLE_T 								  h_sel_box = NULL_HANDLE;
    
#ifdef APP_UEI_SPINNER_SUPPORT
    GL_RECT_T                   		  	  t_rect = {0};
    /* set comfirm page move not put update by state function,
    because the confirm page will show two times in this case(#ifdef APP_UEI_SPINNER_SUPPORT) */
    WZD_ANIM_MOVE_PAGE_TYPE_T                 e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT;
    WZD_ANIM_MOVE_PAGE_TYPE_T                 e_move_show_type = WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER;
#endif
    /*add animation*/
    WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T*    pt_data = NULL;
    
    switch( ui4_msg )
    {
        case WZD_FOOTER_MSG_ITEM_FOCUSED:
            DBG_INFO( ( "[Ln: %d] footer button is focused.\n", __LINE__, (UINT32)pv_param1 ));

            break;
        case WZD_FOOTER_MSG_KEY_INPUT:
            DBG_INFO( ( "[Ln: %d] Receive key input, keycode = %d\n", __LINE__, (UINT32)pv_param1 ));
            
            switch((UINT32)pv_param1)
            {
                case BTN_SELECT:
                    {
                        if( DEVICE_SETUP_CHOOSE_DEVICE == pt_this->e_state )     /* finished button okey */ 
                        {
                            /* clean used info */
                            c_memset(pt_this->aui1_input_src_id, 0, sizeof(pt_this->aui1_input_src_id));    

                            if (!a_wzd_is_resume_from_menu_setup())
                            {
                                pt_this->e_pre_state = DEVICE_SETUP_CHOOSE_DEVICE;
                                pt_this->e_state = DEVICE_SETUP_FINISHED;
                                _wzd_page_tv_remote_device_setup_update_by_state(TRUE);
                            }
                            else
                            {
                                a_wzd_exit(); /*Exit Wizard*/
                            }
                        }
                        else if( DEVICE_SETUP_SELECT_INPUT == pt_this->e_state ) /* back button okey */ 
                        {
                             DBG_INFO( ("[Ln: %d] DEVICE_SETUP_SELECT_INPUT!\n", __LINE__));
                            _wzd_page_tv_remote_device_setup_input_page_back_resume();
                        }
                        else if( DEVICE_SETUP_SELECT_BRAND == pt_this->e_state)
                        {
                            if (WZD_FOOTER_BTN_01 == (WZD_FOOTER_BTN_INDEX_T)pv_param2) /* next button okey */ 
                            {
                                a_vkb_do_cmd (pt_brand_page->h_brand_vkb,
                                              VKB_CMD_GET_EB_CONTENT,
                                             (VOID*) s_brd_name,
                                             (VOID*) (UINT32) DEV_SETUP_DB_NAME_LEN_MAX);
                                c_uc_w2s_to_ps(s_brd_name, pt_this->s_brd_name, DEV_SETUP_DB_NAME_LEN_MAX);

                                if (pt_this->b_is_db_locked)
                                {
                                    /* Play first channel and resize the video to small area. */
                                    if ((DEVICE_TYPE_SELECT_AUDIO_RECIEVER == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SOUND_BAR == pt_this->ui4_type_sel_idx))
                                    {
                                        wzd_set_stream_play_region( TRUE, TRUE );  
                                        DBG_INFO( ("[Ln: %d] wzd_set_stream_play_region() sound bar!\n", __LINE__));
                                    }
                                    else
                                    {
                                        wzd_set_stream_play_region( TRUE, FALSE );  
                                    }
                                    
                                    /* uplode codeset info */
                                    _wzd_page_tv_remote_device_setup_codeset_info();
                                    i4_ret = _wzd_page_tv_remote_device_setup_update_codeset(); 
                                    if (i4_ret != WZDR_OK)
                                    {
                                        DBG_INFO( ("[Ln: %d] [BRAND_BTN_NEXT]_wzd_page_tv_remote_device_setup_update_codeset() is Fail!. i4_ret = %d\n", __LINE__, i4_ret));
                                        _wzd_page_tv_remote_device_setup_update_codeset_exciption_handle();
                                    }

                                }
                                else
                                {
                                	if((pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_SOUND_BAR)&&(c_strcmp(pt_this->s_brd_name, "VIZIO")==0))
                            		{
                            		
#ifdef APP_UEI_SPINNER_SUPPORT
										/*anyway,show confirm page first*/
                                        /* start hide move animation */
                                        wzd_anim_start_move_page(e_move_hide_type);

										_wzd_page_tv_remote_device_setup_update_codeset_exciption_handle();
                                        
                                        /* start show move animation */
                                        wzd_anim_start_move_page(e_move_show_type);
										
										SET_RECT_BY_SIZE (& t_rect,
											  WZD_DEVICE_SETUP_SPINNER_ICON_X,
											  WZD_DEVICE_SETUP_SPINNER_ICON_Y,
											  WZD_DEVICE_SETUP_SPINNER_ICON_W,
											  WZD_DEVICE_SETUP_SPINNER_ICON_H);
										
										c_wgl_move( pt_this->h_animation, &t_rect,WGL_NO_AUTO_REPAINT);
										
										c_wgl_insert(pt_this->h_animation,
													  NULL_HANDLE,
													  WGL_INSERT_TOPMOST,
													  FALSE);
										
										c_wgl_set_visibility(pt_this->h_animation, WGL_SW_RECURSIVE);
										c_wgl_repaint(pt_this->h_animation, NULL, TRUE);
										
										DBG_INFO( ("\n####%s(%d)show animation for vizio soundbar\n",__FUNCTION__,__LINE__));
										
										/* enable the animation scan timer */
										c_timer_start(pt_this->h_timer,
																1000,
																X_TIMER_FLAG_ONCE,
																_wzd_page_tv_remote_animation_timer_notify_fct,
																NULL);
#endif
										
										/* update codeset info with brand */
		                                pt_this->b_is_i_do_not_know_mdl_sel = TRUE;
		                                a_dev_db_clean_codeset_list();
		                                c_memset(pt_this->s_mdl_name, 0, sizeof(pt_this->s_mdl_name));
		                                i4_ret = _wzd_page_tv_remote_device_setup_update_codeset_with_brand();  
		                                if (i4_ret != WZDR_OK)
		                                {
		                                    DBG_INFO( ("[Ln: %d] _wzd_page_tv_remote_device_setup_update_codeset_with_brand() is Fail!, i4_ret = %d\n", __LINE__, i4_ret));
		                                    pt_this->b_is_codeset_querying = FALSE;
		                                    _wzd_page_tv_remote_device_setup_update_codeset_exciption_handle();
											
#ifdef APP_UEI_SPINNER_SUPPORT
											/*hide spinner after get codeset for confirm remote conection page*/
											c_wgl_set_visibility(pt_this->h_animation, WGL_SW_HIDE);
											DBG_INFO( ("\n####%s(%d)confirm page show\n",__FUNCTION__,__LINE__));
#endif
		                                }
		                                else
		                                {
		                                    pt_this->b_is_codeset_querying = TRUE;
		                                }
                            		}
									else
									{
									    pt_this->e_pre_state = DEVICE_SETUP_SELECT_BRAND;
										pt_this->e_state = DEVICE_SETUP_SELECT_MODEL;
										_wzd_page_tv_remote_device_setup_update_by_state(TRUE);
									}
                                }
                            }
                            else if (WZD_FOOTER_BTN_02 == (WZD_FOOTER_BTN_INDEX_T)pv_param2) /* back button okey */ 
                            {                             
                                _wzd_page_tv_remote_device_setup_brand_page_back_resume();
                            }
                        }
                        else if( DEVICE_SETUP_SELECT_MODEL == pt_this->e_state )
                        {
                            /* get current input src */
                            c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
                            a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);

                            /* Play first channel and resize the video to small area. */
                            if ((DEVICE_TYPE_SELECT_AUDIO_RECIEVER == pt_this->ui4_type_sel_idx || DEVICE_TYPE_SELECT_SOUND_BAR == pt_this->ui4_type_sel_idx) && (t_isl_rec.e_src_type == INP_SRC_TYPE_TV))
                            {
                                wzd_set_stream_play_region( TRUE, TRUE );  
                            }
                            else
                            {
                                wzd_set_stream_play_region( TRUE, FALSE );  
                            }
                        
                            if (WZD_FOOTER_BTN_01 == (WZD_FOOTER_BTN_INDEX_T)pv_param2)     /* next button okey */
                            { 
                            
#ifdef APP_UEI_SPINNER_SUPPORT
                            	/*anyway,show confirm page first*/
                                /* start hide move animation */
                                wzd_anim_start_move_page(e_move_hide_type);

								_wzd_page_tv_remote_device_setup_update_codeset_exciption_handle();
                                
                                /* start show move animation */
                                wzd_anim_start_move_page(e_move_show_type);

								SET_RECT_BY_SIZE (& t_rect,
									  WZD_DEVICE_SETUP_SPINNER_ICON_X,
									  WZD_DEVICE_SETUP_SPINNER_ICON_Y,
									  WZD_DEVICE_SETUP_SPINNER_ICON_W,
									  WZD_DEVICE_SETUP_SPINNER_ICON_H);

								c_wgl_move( pt_this->h_animation, &t_rect,WGL_NO_AUTO_REPAINT);
								
								c_wgl_insert(pt_this->h_animation,
											  NULL_HANDLE,
											  WGL_INSERT_TOPMOST,
											  FALSE);
								
								c_wgl_set_visibility(pt_this->h_animation, WGL_SW_RECURSIVE);
								c_wgl_repaint(pt_this->h_animation, NULL, TRUE);
								
								DBG_INFO( ("\n####%s(%d)show animation for next\n",__FUNCTION__,__LINE__));
								
								/* enable the animation scan timer */
								c_timer_start(pt_this->h_timer,
														1000,
														X_TIMER_FLAG_ONCE,
														_wzd_page_tv_remote_animation_timer_notify_fct,
														NULL);
#endif
								
                                a_vkb_do_cmd (pt_model_page->h_model_vkb,
                                              VKB_CMD_GET_EB_CONTENT,
                                             (VOID*) s_mdl_name,
                                             (VOID*) (UINT32) DEV_SETUP_DB_NAME_LEN_MAX);
                                c_uc_w2s_to_ps(s_mdl_name, pt_this->s_mdl_name, DEV_SETUP_DB_NAME_LEN_MAX);
                                
                                /* update codeset info */
                                _wzd_page_tv_remote_device_setup_codeset_info();
                                i4_ret = _wzd_page_tv_remote_device_setup_update_codeset();     
                                if (i4_ret != WZDR_OK)
                                {
                                    DBG_INFO( ("[Ln: %d] _wzd_page_tv_remote_device_setup_update_codeset()is Fail!, i4_ret = %d\n", __LINE__, i4_ret));
                                    _wzd_page_tv_remote_device_setup_update_codeset_exciption_handle();
                                }
                            }
                            else if (WZD_FOOTER_BTN_02 == (WZD_FOOTER_BTN_INDEX_T)pv_param2) /* I don't know model button okey */
                            {   
                            
#ifdef APP_UEI_SPINNER_SUPPORT
								/*anyway,show confirm page first*/
                                /* start hide move animation */
                                wzd_anim_start_move_page(e_move_hide_type);

								_wzd_page_tv_remote_device_setup_update_codeset_exciption_handle();
                                
                                /* start show move animation */
                                wzd_anim_start_move_page(e_move_show_type);
								
								SET_RECT_BY_SIZE (& t_rect,
									  WZD_DEVICE_SETUP_SPINNER_ICON_X,
									  WZD_DEVICE_SETUP_SPINNER_ICON_Y,
									  WZD_DEVICE_SETUP_SPINNER_ICON_W,
									  WZD_DEVICE_SETUP_SPINNER_ICON_H);

								c_wgl_move( pt_this->h_animation, &t_rect,WGL_NO_AUTO_REPAINT);
								
								c_wgl_insert(pt_this->h_animation,
											  NULL_HANDLE,
											  WGL_INSERT_TOPMOST,
											  FALSE);
								
								c_wgl_set_visibility(pt_this->h_animation, WGL_SW_RECURSIVE);
								c_wgl_repaint(pt_this->h_animation, NULL, TRUE);

								DBG_INFO( ("\n####%s(%d)show animation for i dont model\n",__FUNCTION__,__LINE__));
								
								/* enable the animation scan timer */
								c_timer_start(pt_this->h_timer,
														1000,
														X_TIMER_FLAG_ONCE,
														_wzd_page_tv_remote_animation_timer_notify_fct,
														NULL);
#endif
								
                                /* update codeset info with brand */
                                pt_this->b_is_i_do_not_know_mdl_sel = TRUE;
                                a_dev_db_clean_codeset_list();
                                c_memset(pt_this->s_mdl_name, 0, sizeof(pt_this->s_mdl_name));
                                i4_ret = _wzd_page_tv_remote_device_setup_update_codeset_with_brand();  
                                if (i4_ret != WZDR_OK)
                                {
                                    DBG_INFO( ("[Ln: %d] _wzd_page_tv_remote_device_setup_update_codeset_with_brand() is Fail!, i4_ret = %d\n", __LINE__, i4_ret));
                                    pt_this->b_is_codeset_querying = FALSE;
                                    _wzd_page_tv_remote_device_setup_update_codeset_exciption_handle();
									
#ifdef APP_UEI_SPINNER_SUPPORT
									/*hide spinner after get codeset for confirm remote conection page*/
									c_wgl_set_visibility(pt_this->h_animation, WGL_SW_HIDE);
									DBG_INFO( ("\n####%s(%d)confirm page show\n",__FUNCTION__,__LINE__));
#endif
                                }
                                else
                                {
                                    pt_this->b_is_codeset_querying = TRUE;
                                }
                            }
                        }
                    }
                    break;
                    
                case BTN_CURSOR_UP:
                    {
                        if( DEVICE_SETUP_CHOOSE_DEVICE == pt_this->e_state )
                        {
                            if (!_wzd_page_tv_remote_device_setup_all_widget_anim_finish())
                            {
                                DBG_INFO( ("[WZD][DEVICE SETUP] anim not finish retun@LINE: %d.\n", __LINE__));
                                return;
                            }

                            /* change image for the get focus box */
                            _wzd_page_tv_remote_device_setup_set_frm_bg_img(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, h_g_wzd_img_selectbox_small_hlt_small);
                            
                            /* set scale up animation callback data */
                            pt_data = &at_anim_cb_get_focus_data_type;
                            if (NULL == pt_data)
                            {
                                return;
                            }
                            c_memset(pt_data, 0, sizeof(WZD_DEVICE_SETUP_ANIM_COND_CB_DATA_T));
                            pt_data->b_used = TRUE;
                            pt_data->h_anim_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm;
                            pt_data->ui4_index = pt_this->ui4_sel_box_idx;
                            pt_data->e_param = WZD_CALLBACK_PARAM_SCALE_UP;
                            
                            /* set scale up callback */
                            a_wzd_anim_set_cb(
                                       pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm,
                                       _wzd_page_tv_remote_device_setup_sel_box_scale_cb_fct,
                                       (void *)pt_data);
                            
                            /* start scale up anim for get focus box*/
                            _wzd_page_tv_remote_device_setup_sel_box_get_focus_scale_up(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm);
                            
                            _wzd_page_tv_remote_device_setup_sel_page_set_losed_foucs_box_txt_hlt();
                            c_wgl_set_focus(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, WGL_NO_AUTO_REPAINT);
                            c_wgl_float(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, TRUE, WGL_NO_AUTO_REPAINT); 

                            _wzd_page_tv_device_setup_type_update_checkmark();
                        }
                        else if( DEVICE_SETUP_SELECT_INPUT == pt_this->e_state )
                        {
							/* focus to pre select box */
							h_sel_box = wzd_view_sel_box_get_btn_handle (e_sb_pre_focused_box);

							c_wgl_get_visibility(h_sel_box, &b_visible);
					        if (b_visible)
					        {
					            SHOW_ON_ERR (wzd_view_sel_box_set_focus(e_sb_pre_focused_box, FALSE));
					        }

							wzd_view_main_frm_repaint();
                        }
                        else if( DEVICE_SETUP_SELECT_BRAND == pt_this->e_state)
                        {
                            a_vkb_set_focus(pt_brand_page->h_brand_vkb);
                        }
                        else if( DEVICE_SETUP_SELECT_MODEL == pt_this->e_state )
                        {
                            a_vkb_set_focus(pt_model_page->h_model_vkb);
                        }
                                              
                        wzd_view_main_frm_repaint();
                    }
                default:
                    break;
            }
            break;
            
        default:
            break;
            
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_anim_finish_nfy
 *
 * Description: the notify callback function of the page animation is finish.
 *              only for RF scan is complete(tv setup page->tv name input page).
 *              display the full screen dialog after the page animation is finish.
 *              
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_remote_device_setup_anim_finish_nfy()
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;
	WZD_DEVICE_PAIR_DLG_PAGE_T*             pt_paired_dlg_page = &t_g_device_setup_device_pair_dlg_page;
	UINT8                               	status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;

    a_cfg_custom_get_wifi_remote_pair_status(&status);
    
    if((pt_this->e_dev_setup_enter_reason == DEVICE_SETUP_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE) && 
        (status != WIFI_REMOTE_PAIR_STATUS_PAIRED))
    {
        /* lose focus for the sel box when display the dialog */
        wzd_view_sel_box_lose_focus(pt_this->ui1_input_sel_box_idx, FALSE);
        
		/* Set dialog */    
        _wzd_page_tv_remote_device_setup_full_dlg_set_content();
        wzd_view_full_screen_dlg_show(FALSE);
        t_g_device_setup_input_page.b_is_full_screen_dlg_show = TRUE;
		
        c_timer_start(pt_paired_dlg_page->h_device_pair_dlg_timer, 
                      5000,
                      X_TIMER_FLAG_ONCE,
                      _wzd_page_tv_remote_device_setup_timer_paired_show_dialog_nfy_fct,
                      NULL);	
    }
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_remote_device_setup_get_page_info_data
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_remote_device_setup_get_page_info_data( WZD_PAGE_INFO_DATA_T* pt_info_data)
{    
    c_memset( pt_info_data, 0, sizeof(WZD_PAGE_INFO_DATA_T) );

    pt_info_data->t_page_type              = WZD_PAGE_TYPE_CUST_PAGE;
    pt_info_data->ui2_title_key            = MLM_WZD_KEY_TITLE_DEVICE;
    pt_info_data->ui2_desc_text_key        = MLM_WZD_KEY_DESC_DEVICE;
    pt_info_data->ui1_elem_num             = 0;
    pt_info_data->pf_get_text              = NULL;
    pt_info_data->pf_footer_data_change    = _wzd_page_tv_remote_device_setup_on_footer_nfy;
    pt_info_data->pf_return_nfy_fct        = _wzd_page_tv_remote_device_setup_return_nfy_cb;
    pt_info_data->pf_anim_finish_nfy_fct   = _wzd_page_tv_remote_device_setup_anim_finish_nfy;
   
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_create = _wzd_page_tv_remote_device_setup_create;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_destory = _wzd_page_tv_remote_device_setup_dsty;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_show = _wzd_page_tv_remote_device_setup_on_show;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_hide = _wzd_page_tv_remote_device_setup_on_hide;

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_remote_device_setup_nfy_sel
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_remote_device_setup_nfy_sel(UINT16               ui2_sel_idx,
                                  VOID*                 pv_data,
                                  WZD_MSG_CUSTOM_T*     pt_ret_msg)
{
    (*pt_ret_msg)  = WZD_MSG_CUSTOM_NAV_NEXT_PAGE;

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_remote_device_reset_page_show_flag
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_remote_device_reset_page_show_flag(VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;
    INT32      i4_ret = WZDR_OK;;

    /* should unregister the callback*/
    if (pt_this->b_is_notify_reg)
    {
        i4_ret = a_dev_db_unregister(pt_this->ui4_nfy_id);
        DBG_INFO(  ("\n[Ln:][wzd_dev_setup] a_dev_db_unregister() return i4_ret[%d]\n", __LINE__, i4_ret));
        pt_this->b_is_notify_reg = FALSE;
    }
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_remote_device_setup_enter_from_tuner_setup
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_remote_device_setup_enter_from_tuner_setup(UINT32  ui4_dev_type_sel_idx)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;

    /* here should updater the dev type by enter reason*/
    pt_this->e_dev_setup_enter_reason = DEVICE_SETUP_ENTER_REASON_TV_SETUP;
    pt_this->ui4_type_sel_idx = ui4_dev_type_sel_idx;
    
    wzd_page_goto( WZD_PAGE_NAVI_NEXT_PAGE );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_remote_device_setup_enter_from_tuner_not_pair_antenna
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_remote_device_setup_enter_from_tuner_not_pair_antenna (VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;

    /* here should updater the dev type by enter reason*/
    pt_this->e_dev_setup_enter_reason = DEVICE_SETUP_ENTER_REASON_TV_SETUP_ANTENNA_NOT_PAIR;
    
    wzd_page_goto( WZD_PAGE_NAVI_NEXT_PAGE );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_remote_device_setup_enter_from_tuner_pair_antenna
 *
 * Description: paired wifi remote && antenna scan enter
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_remote_device_setup_enter_from_tuner_pair_antenna (VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;

    /* here should updater the dev type by enter reason*/
    pt_this->e_dev_setup_enter_reason = DEVICE_SETUP_ENTER_REASON_TV_SETUP_ANTENNA_PAIR;
    
    wzd_page_goto( WZD_PAGE_NAVI_NEXT_PAGE );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_remote_device_setup_enter_from_tuner_pair_direct_from_wall
 *
 * Description: paired wifi remote && direct from wall scan enter
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_remote_device_setup_enter_from_tuner_pair_direct_from_wall (VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;

    /* here should updater the dev type by enter reason*/
    pt_this->e_dev_setup_enter_reason = DEVICE_SETUP_ENTER_REASON_TV_SETUP_DIRECT_FROM_WALL_PAIR;
    
    wzd_page_goto( WZD_PAGE_NAVI_NEXT_PAGE );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_remote_device_setup_enter_from_tuner_setup_rf_scan
 *
 * Description: From tv turn setup RF channel scan complete: cable box->rf->scan complete->brand
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_remote_device_setup_enter_from_tuner_setup_rf_scan (VOID)
{
    WZD_TV_REMOTE_DEVICE_SETUP_MEMBER_T*    pt_this = &t_g_tv_remote_device_setup;

    /* here should updater the dev type by enter reason*/
    pt_this->e_dev_setup_enter_reason = DEVICE_SETUP_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE;
    
    wzd_page_goto( WZD_PAGE_NAVI_NEXT_PAGE );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_remote_device_setup_back_to_tuner_setup
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_remote_device_setup_back_to_tuner_setup(VOID)
{
    wzd_page_goto( WZD_PAGE_NAVI_PREV_PAGE );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_remote_device_setup_unfocus_footer
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_remote_device_setup_unfocus_footer(VOID)
{
    return WZDR_OK;
}

