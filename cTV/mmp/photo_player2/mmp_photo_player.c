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
 * $RCSfile: mmp_photo_player.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
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
#include "c_os.h"
#include "c_fe.h"
#include "u_wgl_common.h"
#include "u_wgl_obj_type.h"
#include "u_wgl_text.h"
#include "u_wgl_lb.h"
#include "c_uc_str.h"
#include "c_dt.h"
#include "c_fm.h"
#include "c_dbg.h"
#include "app_util/a_common.h"
#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp/mmp_intf_file_player.h"
#include "mmp/mmp_mmc_basic.h"
#include "mmp/mmp_mmc_list.h"
#include "mmp/app/mmp_main.h"
#include "mmp/disp_res_ctrler/mmp_drc.h"
#include "mmp/photo_eng/mmp_photo_eng.h"
#include MMP_COM_UI_HEADER_FILE
#include "res/mmp/photo_player/mmp_photo_player_rc.h"
#include "mmp/file_browser/file_browser.h"
#include "res/mmp/img/mmp_img.h"
#include "app_util/a_cfg.h"
#include "app_util/option_list/a_optl.h"
#include "app_util/capture_logo/a_capture_logo.h"
#include "mmp/common_ui2/mmp_common_ui_toolbar.h"
#include "mmp/photoframe/mmp_photo_frame.h"
#include "mmp/common_ui2/mmp_com_ui_info_handler.h"
#include "mmp/common_ui2/mmp_info_bar.h"
#include "res/mmp/gen/mmp_pop_up_photo_layout.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#include "mmp/thumbnailmode2/thumbnailmode.h"
//#include "res/mmp/gen/mmp_pp_hide_layout.h"
#include "menu2/menu_common/menu_common.h"



#ifdef MMP_GUI_AUTHORING_DP
#include "mmp/common_ui2/mmp_common_ui_detail_page.h"
#endif

#include "wdk/util/wdk_wgl_util.h"

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
#include "mmp/dmr/mmp_dmr.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DBG_INFO_DIRECT(fmt, args...) \
	do{																		\
		if(0)																\
		{																	\
			fprintf(stderr,fmt,##args );									\
			fflush(stderr);													\
		}																	\
		else																\
		{																	\
			MMP_DBG_INFO((fmt, args));										\
		}																	\
	}while(0)																\


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef enum _MMP_PP_MSGBOX_TYPE_T
{
    MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT,
    MMP_PP_MSGBOX_TYPE_RESOLUTION_NOT_SUPPORT,
    MMP_PP_MSGBOX_TYPE_DECODE_FAIL,
    MMP_PP_MSGBOX_TYPE_NOT_EXIST,
    MMP_PP_MSGBOX_TYPE_LAST_ITEM
}MMP_PP_MSGBOX_TYPE_T;

typedef struct _MMP_PP_STATUSBAR_T
{
    HANDLE_T                    h_bar;
    HANDLE_T                    h_status_icon;
    HANDLE_T                    h_read_only_icon;
    HANDLE_T                    ah_label[MMP_PP_RC_STATUSBAR_LABEL_COUNT];
} MMP_PP_STATUSBAR_T;

typedef struct __MMP_PP_DETAIL_PAGE_T
{
    HANDLE_T                    h_page;
#ifdef MMP_GUI_AUTHORING_DP
    MMP_PP_DP_CONFIG_T          at_config[MMP_PP_RC_DP_LBL_COUNT];
#else
    HANDLE_T                    ah_label[MMP_PP_RC_DP_LBL_LAST_ENTRT];
#endif
} _MMP_PP_DETAIL_PAGE_T;

typedef struct __MMP_PP_INFO_HANDLE_T
{
    BOOL                          b_inited;
    MMP_COM_FP_INFO_UI_TYPE_T     e_thum_mode;
}_MMP_PP_INFO_HANDLE_T;

#ifndef MMP_GUI_AUTHORING_DP
typedef enum __MMP_PP_INFO_DATA_TYPE_T
{
    _MMP_PP_INFO_DATA_TYPE_CHAR = 0,
    _MMP_PP_INFO_DATA_TYPE_GL_SIZE,
    _MMP_PP_INFO_DATA_TYPE_DTG,
    _MMP_PP_INFO_DATA_TYPE_ROTATION,
    _MMP_PP_INFO_DATA_TYPE_EXPOSURE_TIME,
    _MMP_PP_INFO_DATA_TYPE_F_NUMBER,
    _MMP_PP_INFO_DATA_TYPE_FILENAME,
    _MMP_PP_INFO_DATA_TYPE_EXPOSURE_PROGRAM,
    _MMP_PP_INFO_DATA_TYPE_COLOR_SPACE,
    _MMP_PP_INFO_DATA_TYPE_CUR_OF_TOAL
} _MMP_PP_INFO_DATA_TYPE_T;
#endif

typedef struct __MMP_PP_INFO_UPDATE_REC_T
{
    MMP_FP_INFO_TYPE_T          e_type;
    SIZE_T                      z_size;
    UINT8*                      pui1_buf;
    _MMP_PP_INFO_DATA_TYPE_T    e_data_type;
    HANDLE_T                    h_update;
} _MMP_PP_INFO_UPDATE_REC_T;

typedef struct __MMP_PP_VIEW_T
{
    MMP_PP_STATUSBAR_T      t_statusbar;
    _MMP_PP_DETAIL_PAGE_T       t_detailpage;
    _MMP_PP_INFO_HANDLE_T       t_info_hdlr;
    /*MMP_COM_UI_LISTBOX_T        t_tfx_lb;*/
    /*MMP_COM_UI_LISTBOX_T        t_dur_lb;*/
    /*MMP_COM_UI_LISTBOX_T        t_zoom_lb;*/
    HANDLE_T                    h_frame;
    HANDLE_T                    h_optl;
    HANDLE_T                    h_skip_icon;
    HANDLE_T                     h_play_icon;
    HANDLE_T                     h_pause_icon;
    HANDLE_T                     h_not_show_file_title;

} _MMP_PP_VIEW_T;

typedef enum _MMP_INFO_STATE_T
{
    _MMP_INFO_STATE_NONE = 0,
    _MMP_INFO_STATE_SIMPLE,
    _MMP_INFO_STATE_DETAIL,
    _MMP_INFO_STATE_POP_UP,
    _MMP_INFO_STATE_POP_UP_THEN_DETAIL,
    _MMP_INFO_STATE_DETAIL_THEN_POP_UP,
    _MMP_INFO_STATE_NEXT
} _MMP_INFO_STATE_T;

typedef enum __MMP_PLAY_STATE_T
{
    _MMP_PLAY_STATE_NONE    = 0,
    _MMP_PLAY_STATE_PAUSE,
    _MMP_PLAY_STATE_PLAY
} _MMP_PLAY_STATE_T;

typedef enum _MMP_INFO_STATE_CHANGE
{
    _MMP_INFO_UNCHANGE =0,
    _MMP_INFO_CHANGE
}_MMP_INFO_STATE_CHANGE;


typedef enum __MMP_LABEL_STATE_T
{
    _MMP_LABEL_STATE_PLAY = 0,
    _MMP_LABEL_STATE_PAUSE
}_MMP_LABEL_STATE_T;

#define _MMP_PP_FLAG_PLAY                   ((UINT32) 0x00000001)
#define _MMP_PP_FLAG_TFX_LB_SHOW            ((UINT32) 0x00000002)
#define _MMP_PP_FLAG_ZOOM_LB_SHOW           ((UINT32) 0x00000004)
#define _MMP_PP_FLAG_DUR_LB_SHOW            ((UINT32) 0x00000008)

#ifndef MMP_PP_RC_REPEAT_ALL
#define MMP_PP_RC_REPEAT_ALL()     (FALSE)
#endif


#define MMP_PP_MAX_NAV_WIG__NUM             (7)
typedef struct __MMP_PP_DATA_MEMBER_T
{
    _MMP_PP_VIEW_T              t_view;
    HANDLE_T                    h_hide_timer;
    mmp_fp_show_nfy_fct         pf_nfy;
    VOID*                       pv_nfy_tag;
    _MMP_INFO_STATE_T           e_info_state;
    _MMP_PLAY_STATE_T             e_play_state;
    MMP_REPEAT_MODE_T           e_repeat_mode;
    MMP_SHUFFLE_MODE_T          e_shuffle_mode;
    UINT32                      ui4_flag;
    UINT32                      ui4_tfx_idx;          /* The index of current tfx */
    UINT32                      ui4_dur_idx;          /* The index of current dur */
    UINT32                      ui4_zoom_idx;         /* The index of current zoom */
    _MMP_LABEL_STATE_T          e_label_state;        /* The state for label display */
    UINT32                      ui4_current_fileidx;  /* Current file index */
    UINT32                      ui4_total_fileidx;    /* Total file index */
    BOOL                        b_is_notsupport_show;
    BOOL                        b_pp_view_active;
    BOOL                        b_pause_by_cap;
    BOOL                        b_cap_ui_active;
    VOID*                       pv_cap;
    _MMP_INFO_STATE_CHANGE      e_state_change_flag;
    UINT8                         ui1_gui_lang_id;
    BOOL                        b_crnt_file_skip;
    UINT32                      ui4_mlm_id;
} _MMP_PP_DATA_MEMBER_T;


/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _MMP_PP_DATA_MEMBER_T    t_g_pp;
static UINT32 ui4_msg_type;
#ifdef MMP_GUI_AUTHORING_DP
static MMP_COM_UI_DP_VIEW_PTR_T pt_pdp_inst;
#endif

#if 1//def MMP_GUI_AUTHORING_TB
//static VOID*                    pt_ptb_inst;
#endif

/*-----------------------------------------------------------------------------
 * customization default value
 *---------------------------------------------------------------------------*/
#ifndef MMP_PP_RC_IS_NO_THUMB_FROM_MAIN
    #define MMP_PP_RC_IS_NO_THUMB_FROM_MAIN()       (FALSE)
#endif

 /*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _mmp_pp_init(VOID);

static INT32 _mmp_pp_deinit(VOID);

static INT32 _mmp_pp_handle_msg(
        MMP_MSG_ID_T                        e_msg_id,
        VOID*                               pv_msg_param);

static INT32 _mmp_pp_show_open(
        const CHAR*                         ps_filename,
        mmp_fp_show_nfy_fct                 pf_nfy,
        VOID*                               pv_tag,
        UINT32                              ui4_ver);

static INT32 _mmp_pp_show_close(VOID);

static INT32 _mmp_pp_show_attr_set(
        UINT32                              ui4_attr_count,
        const MMP_FP_SHOW_ATTR_T*           at_show_attr);

static INT32 _mmp_pp_show_next_preload(
        const CHAR*                         ps_filename);

static INT32 _mmp_pp_show_next_attr_set(
        UINT32                              ui4_attr_count,
        const MMP_FP_SHOW_ATTR_T*           at_show_attr);

static INT32 _mmp_pp_show_cmd_do(
        MMP_FP_SHOW_CMD_ID_T                e_cmd_id,
        VOID*                               pv_cmd_param);

static VOID _mmp_pp_play_nfy_cb(
        VOID*                               pv_tag,
        UINT32                              ui4_ver,
        MMP_PE_PLAY_NFY_ID_T                e_nfy_id,
        VOID*                               pv_nfy_param);

static INT32 _mmp_pp_view_init(
        _MMP_PP_DATA_MEMBER_T*              pt_this);

static VOID _mmp_pp_view_deinit(
        _MMP_PP_DATA_MEMBER_T*              pt_this);

static VOID _mmp_pp_view_update_info(
        _MMP_PP_DATA_MEMBER_T*              pt_this);

static INT32 _mmp_pp_opt_set_item (
        _MMP_LABEL_STATE_T                  t_label_state);

static VOID _mmp_pp_view_update_play_status(
        _MMP_PP_DATA_MEMBER_T*              pt_this,
        MMP_PLAY_STATE_T                    e_status);

static INT32 _mmp_pp_view_activate(
        _MMP_PP_DATA_MEMBER_T*              pt_this);

static INT32 _mmp_pp_view_switch_info(
        _MMP_PP_DATA_MEMBER_T*              pt_this,
        _MMP_INFO_STATE_T                   e_new_state);

static INT32 _mmp_pp_view_reset_info_hdlr(VOID*    pv_info_hdlr_inst);

static INT32 _mmp_pp_view_rotate_left(
        _MMP_PP_DATA_MEMBER_T*              pt_this);
static INT32 _mmp_pp_view_rotate_right(
        _MMP_PP_DATA_MEMBER_T*              pt_this);


static INT32 _mmp_pp_view_do_zoom(
        _MMP_PP_DATA_MEMBER_T*              pt_this,
        UINT32                              ui4_idx);

static INT32 _mmp_pp_set_do_picture_frame_photo(VOID*  pv_tag);

static INT32 _mmp_pp_view_do_effect(
        _MMP_PP_DATA_MEMBER_T*              pt_this,
        UINT32                              ui4_idx);

static INT32 _mmp_pp_view_do_duration(
        _MMP_PP_DATA_MEMBER_T*              pt_this,
        UINT32                              ui4_idx);

static VOID _mmp_pp_view_reset_hide_timer(
        _MMP_PP_DATA_MEMBER_T*              pt_this,
        MMP_TIMER_OP_TYPE_T                 e_op);

static VOID _mmp_pp_view_hide_timer_cb(
        HANDLE_T                            h_timer,
        VOID*                               pv_unused);

static VOID _mmp_pp_view_hide_timer_event_handler(
        VOID*                               pv_unused1,
        VOID*                               pv_unused2,
        VOID*                               pv_unused3,
        VOID*                               pv_unused4);

static INT32 _mmp_pp_view_main_frm_proc_fct(
        HANDLE_T                            h_frm_main,
        UINT32                              ui4_msg,
        VOID*                               pv_param1,
        VOID*                               pv_param2);
#if 0

static INT32 _mmp_pp_view_update_tfx(
   _MMP_PP_DATA_MEMBER_T*      pt_this);


static INT32 _mmp_pp_view_update_zoom(
   _MMP_PP_DATA_MEMBER_T*      pt_this);
#endif
static VOID _mmp_pp_view_update_repeat_label(
    _MMP_PP_DATA_MEMBER_T*      pt_this);

static VOID _mmp_pp_view_update_shuffle_label(
    _MMP_PP_DATA_MEMBER_T*      pt_this);

static VOID _mmp_pp_view_update_label(
    _MMP_PP_DATA_MEMBER_T*      pt_this);

static INT32 _mmp_pp_view_create_optl(
    HANDLE_T                    h_parent,
    HANDLE_T*                   ph_optl);

static VOID _mmp_pp_view_broadcast_file_msg(
    VOID*                       pv_unused1,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3,
    VOID*                       pv_unused4);

static UINT16 _mmp_pp_get_mlm_lang_id(VOID);
static INT32 _mmp_pp_view_update_fileidx(
    _MMP_PP_DATA_MEMBER_T*       pt_this,
    MMP_PL_IDX_TYPE_T            e_idx_type,
    BOOL                         b_repaint);


static INT32 _mmp_pp_view_open_msgbox(MMP_PP_MSGBOX_TYPE_T   e_msg_type);

static INT32 _mmp_pp_view_close_msgbox(VOID);

static INT32 _mmp_pp_random_effect (_MMP_PP_DATA_MEMBER_T* pt_this);

static UINT32 _mmp_pp_rand(VOID);

static INT32 _mmp_pp_info_hdlr_init(
    MMP_FP_INFO_HDLR_INIT_PARAM_T*  pt_param,
    VOID**                          ppv_info_hdlr_inst);

static INT32 _mmp_pp_info_hdlr_deinit(VOID*    pv_info_hdlr_inst);

static INT32 _mmp_pp_info_hdlr_cmd_do(
    VOID*                           pv_info_hdlr_inst,
    MMP_FP_INFO_HDLR_CMD_ID_T       e_cmd,
    VOID*                           pv_cmd_param);
static INT32 _mmp_pp_view_update_file_name(_MMP_PP_DATA_MEMBER_T*   pt_this,
                                           VOID*                    pv_cmd_param,
                                           VOID*                    pv_info_hdlr_inst,
                                           BOOL                     b_info_hdlr);
static INT32 _mmp_pp_pop_up_page_show(_MMP_PP_DATA_MEMBER_T*  pt_this);

static INT32 _mmp_pp_view_update_file_info_solution(_MMP_PP_DATA_MEMBER_T*   pt_this,
                                                    VOID*                    pv_cmd_param,
                                                    VOID*                    pv_info_hdlr_inst);

static INT32 _mmp_pp_view_update_file_info_size(_MMP_PP_DATA_MEMBER_T*       pt_this,
                                                    VOID*                    pv_cmd_param,
                                                    VOID*                    pv_info_hdlr_inst);

static INT32 _mmp_pp_view_update_file_info_protect(_MMP_PP_DATA_MEMBER_T*   pt_this,
                                              VOID*                    pv_cmd_param,
                                              VOID*                    pv_info_hdlr_inst);

static INT32 _mmp_pp_get_force_rotate_op(const CHAR* ps_filename, MMP_FP_LOAD_IMG_ROTATE_OP_T* pe_force_rotate_op);
static INT32 _mmp_pp_rotate_image(_MMP_PP_DATA_MEMBER_T* pt_this, BOOL b_clockwise);
static VOID _mmp_pp_hide_pop_up_page(_MMP_PP_DATA_MEMBER_T* pt_this);
static INT32 _mmp_pp_ch_lang_text(UINT8 ui1_gui_lang_id);


/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
* Name: _mmp_pp_view_red_key_handler
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _mmp_pp_view_red_key_handler(UINT32 ui4_key_code, UINT32 ui4_keystatus)
{
    INT32   i4_ret=MMPR_OK;

    switch(ui4_key_code)
    {
        case BTN_EXIT:
        case BTN_RED:
        {
            i4_ret = mmp_be_pause_mmp();
            return i4_ret;
        }
            break;

        default:
            break;
    }
    return i4_ret;
}

/*-----------------------------------------------------------------------------
* Name: _mmp_pp_pop_up_page_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

INT32 _mmp_pp_pop_up_page_show(_MMP_PP_DATA_MEMBER_T*  pt_this)
{
    HANDLE_T            h_view_item=NULL_HANDLE;
    ISO_639_LANG_T  s639_lang;
    UINT8               ui1_gui_lang_id;
    INT32               i4_ret=MMPR_OK;

    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_STARTSLIDESHOW_BTN);
    c_wgl_set_focus(h_view_item,WGL_SYNC_AUTO_REPAINT);
    a_cfg_get_gui_lang(s639_lang);
    ui1_gui_lang_id  = mlm_mmp_s639_to_langidx(s639_lang);
    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_TXT_MODIFY_BTN_TEXT);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_TITLE_MODIFY_PHOTO)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_TITLE_MODIFY_PHOTO))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);

    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_TXT_EXCLUDE_STATUS_TEXT);
    i4_ret = c_wgl_do_cmd (h_view_item,
                   WGL_CMD_TEXT_SET_TEXT,
                   WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SATSLSHOW)),
                   WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SATSLSHOW))));

    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_pop_up_info_cb
     *
     * Description:
     *
     * Inputs:
     *
     * Outputs:
     *
     * Returns:
     ----------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_info_cb (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;
    UINT32                        ui4_key_code = (UINT32) pv_param1;
    INT32                          i4_ret=MMPR_OK;
    HANDLE_T                      h_view_item=NULL_HANDLE;
    GL_RECT_T                     t_rect ={0};
    //BOOL                            b_reset_timer,b_wake_ui;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
       {
           case  MMP_TM_RC_KEY_DETAIL:
           case MMP_TM_BTN_SELECT:
           if(pt_this->e_info_state == _MMP_INFO_STATE_POP_UP)
           {

              h_view_item      = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
              t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT-MMP_PHOTO_POP_UP_OFFICE;
              t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
              t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
              t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
              IS_MMPR_OK(c_wgl_move(h_view_item,
                           &t_rect,
                           FALSE));
              pt_this->e_info_state = _MMP_INFO_STATE_POP_UP;
              h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
              c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
              i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
              mmp_com_ui_dp_view_active(pt_pdp_inst);
               pt_this->e_info_state = _MMP_INFO_STATE_POP_UP_THEN_DETAIL;
           }

           else if((pt_this->e_info_state == _MMP_INFO_STATE_POP_UP_THEN_DETAIL)||
                    (pt_this->e_info_state == _MMP_INFO_STATE_DETAIL_THEN_POP_UP))
           {
               i4_ret = mmp_com_ui_dp_view_inactive(pt_pdp_inst);
               pt_this->e_info_state = _MMP_INFO_STATE_POP_UP;
               h_view_item      = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);

               c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
               i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);

               t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT;
               t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
               t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
               t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
               IS_MMPR_OK(c_wgl_move(h_view_item,
                            &t_rect,
                            FALSE));
               h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
               c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
               i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);

           }

               break;

           case BTN_RETURN:
                pt_this->e_play_state = _MMP_PLAY_STATE_NONE;
                c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
               h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
               c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
               i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
               mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
               break;
           case BTN_INPUT_SRC:
               _mmp_pp_hide_pop_up_page(pt_this);
                break;

            case MMP_PP_RC_KEY_PHO_PAUSE:
                if(pt_this->e_play_state == _MMP_PLAY_STATE_PAUSE)
                {
                    break;
                }

                else
                {
                    pt_this->e_play_state = _MMP_PLAY_STATE_PAUSE;
                    c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                    c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_NORMAL);
                    //b_reset_timer = TRUE;
                #ifdef APP_TTS_SUPPORT
                    UTF16_T         w2s_str[128] = {0};
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif
                    mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                    //b_wake_ui = TRUE;
                    break;
                }
            case BTN_STOP:
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
               c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
               i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                break;

           default:
           {
               i4_ret = _mmp_pp_view_red_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
               IS_MMPR_OK(i4_ret);
               i4_ret = c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
               IS_MMPR_OK(i4_ret);
           }
       }
         return i4_ret;

    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_EXCLU_INFO));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_TXT_EXCLUDE_STATUS_TEXT);
        i4_ret = c_wgl_do_cmd (h_view_item,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_INFO)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_INFO))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
        return c_wgl_repaint(h_view_item ,NULL,TRUE);

    }


    else return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_pop_up_skip_cb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_skip_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2)
{
    HANDLE_T                      h_view_item=NULL_HANDLE;
    INT32                          i4_ret=MMPR_OK;
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;
    UINT32                        ui4_key_code = (UINT32) pv_param1;
    GL_RECT_T                     t_rect ={0};
    //BOOL                            b_reset_timer,b_wake_ui;
#ifdef APP_NET_DLNA_SUPPORT
    CHAR                        s_buf[MMP_PP_RC_STR_MAX_LEN + 1];
    SIZE_T                      z_buf_size = MMP_PP_RC_STR_MAX_LEN + 1;
    RMV_DEV_DEVICE_STATUS_T     e_dev_status = RMV_DEV_DEVICE_STATUS_UNSUPT_DEV;
#endif

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
        {
            case MMP_TM_BTN_SELECT:
#ifdef APP_NET_DLNA_SUPPORT
                i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                             MMP_PE_EXTRA_INFO_ID_PATH,
                                             &z_buf_size,
                                             (VOID*)s_buf);
                IS_MMPR_OK(i4_ret);

                i4_ret = a_rmv_dev_get_mnt_point_status_by_path(s_buf, &e_dev_status);
                IS_MMPR_OK(i4_ret);

                if (RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
                {
                }
                else if(RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))
                {
                }
                else
#endif
                {
                pt_this->b_crnt_file_skip = !pt_this->b_crnt_file_skip;

                if (pt_this->b_crnt_file_skip)
                {
                    mmp_be_update_list_item(ITEM_TYPE_FILE,
                                            pt_this->ui4_current_fileidx,
                                            MMP_FF_ITEM_LIST_TYPE_SKIP_LIST,
                                            MMP_FF_ITEM_LIST_OP_TYPE_ADD);
                    c_wgl_show(pt_this->t_view.h_skip_icon, WGL_SW_NORMAL);
                }
                else
                {
                    mmp_be_update_list_item(ITEM_TYPE_FILE,
                                            pt_this->ui4_current_fileidx,
                                            MMP_FF_ITEM_LIST_TYPE_SKIP_LIST,
                                            MMP_FF_ITEM_LIST_OP_TYPE_RMV);
                    c_wgl_show(pt_this->t_view.h_skip_icon, WGL_SW_HIDE);
                }
                }

                break;

            case  MMP_TM_RC_KEY_DETAIL:
                if(pt_this->e_info_state == _MMP_INFO_STATE_POP_UP)
                {

                    h_view_item      = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                    t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT-MMP_PHOTO_POP_UP_OFFICE;
                    t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
                    t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
                    t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
                    IS_MMPR_OK(c_wgl_move(h_view_item,
                                 &t_rect,
                                 FALSE));
                    pt_this->e_info_state = _MMP_INFO_STATE_POP_UP_THEN_DETAIL;
                    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
                    i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                    mmp_com_ui_dp_view_active(pt_pdp_inst);

                }

                else if((pt_this->e_info_state == _MMP_INFO_STATE_POP_UP_THEN_DETAIL) ||
                    (pt_this->e_info_state == _MMP_INFO_STATE_DETAIL_THEN_POP_UP))
                {
                    i4_ret = mmp_com_ui_dp_view_inactive(pt_pdp_inst);
                    pt_this->e_info_state = _MMP_INFO_STATE_POP_UP;
                    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);

                    c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                    i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);

                    t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT;
                    t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
                    t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
                    t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
                    IS_MMPR_OK(c_wgl_move(h_view_item,
                                 &t_rect,
                                 FALSE));
                    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
                    i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                }
                break;

            case BTN_RETURN:
                pt_this->e_play_state = _MMP_PLAY_STATE_NONE;
                c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                break;
            case BTN_INPUT_SRC:
                _mmp_pp_hide_pop_up_page(pt_this);
                 break;

            case MMP_PP_RC_KEY_PHO_PAUSE:
                if(pt_this->e_play_state == _MMP_PLAY_STATE_PAUSE)
                {
                    break;
                }

                else
                {
                    pt_this->e_play_state = _MMP_PLAY_STATE_PAUSE;
                    c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                    c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_NORMAL);
                    //b_reset_timer = TRUE;
                #ifdef APP_TTS_SUPPORT
                    UTF16_T         w2s_str[128] = {0};
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif
                    mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                    //b_wake_ui = TRUE;
                    break;
                }
            case BTN_STOP:
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
               c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
               i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                break;

            default:
            {
                i4_ret = _mmp_pp_view_red_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
                IS_MMPR_OK(i4_ret);
                i4_ret = c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);//mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
                IS_MMPR_OK(i4_ret);
            }

            break;
        }
        return i4_ret;
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_EXCLU_SKIP));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_TXT_EXCLUDE_STATUS_TEXT);
        i4_ret = c_wgl_do_cmd (h_view_item,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SKIP)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SKIP))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
        return c_wgl_repaint(h_view_item ,NULL,TRUE);

    }
   else return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_pop_up_start_slideshow_cb
     *
     * Description:
     *
     * Inputs:
     *
     * Outputs:
     *
     * Returns:
----------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_pop_up_start_slideshow_cb (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{
    _MMP_PP_DATA_MEMBER_T*          pt_this = &t_g_pp;
    UINT32                          ui4_key_code = (UINT32) pv_param1;
    INT32                           i4_ret=MMPR_OK;
    HANDLE_T                        h_view_item=NULL_HANDLE;
    GL_RECT_T                       t_rect ={0};
    UINT32                          ui4_slideshow_idx;
    //BOOL                            b_reset_timer,b_wake_ui;
#ifdef APP_TTS_SUPPORT
    UTF16_T         w2s_str[128] = {0};
#endif

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
       {
           case  MMP_TM_RC_KEY_DETAIL:
           if(pt_this->e_info_state == _MMP_INFO_STATE_POP_UP)
           {

              h_view_item      = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
              t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT-MMP_PHOTO_POP_UP_OFFICE;
              t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
              t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
              t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
              IS_MMPR_OK(c_wgl_move(h_view_item,
                           &t_rect,
                           FALSE));
              pt_this->e_info_state = _MMP_INFO_STATE_POP_UP;
              h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
              c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
              i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
              mmp_com_ui_dp_view_active(pt_pdp_inst);
              pt_this->e_info_state = _MMP_INFO_STATE_POP_UP_THEN_DETAIL;
           }

           else if((pt_this->e_info_state == _MMP_INFO_STATE_POP_UP_THEN_DETAIL)||
                    (pt_this->e_info_state == _MMP_INFO_STATE_DETAIL_THEN_POP_UP))
           {
               i4_ret = mmp_com_ui_dp_view_inactive(pt_pdp_inst);
               pt_this->e_info_state = _MMP_INFO_STATE_POP_UP;
               h_view_item      = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);

               c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
               i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);

               t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT;
               t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
               t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
               t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
               IS_MMPR_OK(c_wgl_move(h_view_item,
                            &t_rect,
                            FALSE));
               h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
               c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
               i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);

           }
               break;

           case MMP_TM_BTN_SELECT:
                c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                i4_ret = mmp_info_bar_hide();
                pt_this->e_play_state = _MMP_PLAY_STATE_NONE;

                if((pt_this->e_info_state == _MMP_INFO_STATE_DETAIL_THEN_POP_UP)||
                    (pt_this->e_info_state == _MMP_INFO_STATE_POP_UP_THEN_DETAIL))
                {
                    pt_this->e_info_state = _MMP_INFO_STATE_DETAIL;
                }
                else if(pt_this->e_info_state == _MMP_INFO_STATE_POP_UP)
                {
                    pt_this->e_info_state = _MMP_INFO_STATE_SIMPLE;
                }
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                IS_MMPR_OK (c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE));
                IS_MMPR_OK(c_wgl_repaint(h_view_item,NULL,TRUE));

                c_wgl_set_focus(pt_this->t_view.h_frame,WGL_SYNC_AUTO_REPAINT);

                i4_ret = mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX_CRT,
                                                        pt_this->ui4_current_fileidx + 1,
                                                        &ui4_slideshow_idx);
                if (MMPR_OK == i4_ret)
                {
                    mmp_mc_list_play(MMP_GROUND_MODE_FORE, ui4_slideshow_idx);
                }
                break;

           case BTN_RETURN:
                pt_this->e_play_state = _MMP_PLAY_STATE_NONE;
                c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
               h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
               c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
               i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
               mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
               break;
           case BTN_INPUT_SRC:
               _mmp_pp_hide_pop_up_page(pt_this);
                break;
            case MMP_PP_RC_KEY_PHO_PLAY:
                if(pt_this->e_play_state == _MMP_PLAY_STATE_PLAY)
                {
                    break;
                }

                else
                {
                    pt_this->e_play_state = _MMP_PLAY_STATE_PLAY;
                    c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                    c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_NORMAL);
                #ifdef APP_TTS_SUPPORT
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif
                    mmp_mc_list_play(MMP_GROUND_MODE_FORE, MMP_PLAY_IDX_CURRENT);
                    _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                    i4_ret = mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX_CRT,
                                            pt_this->ui4_current_fileidx + 1,
                                            &ui4_slideshow_idx);
                    if (MMPR_OK == i4_ret)
                    {
                    #ifdef APP_TTS_SUPPORT
                        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    #endif
                        mmp_mc_list_play(MMP_GROUND_MODE_FORE, ui4_slideshow_idx);
                    }
                    break;
                }
                case MMP_PP_RC_KEY_PHO_PAUSE:
                    if(pt_this->e_play_state == _MMP_PLAY_STATE_PAUSE)
                    {
                        break;
                    }

                    else
                    {
                        pt_this->e_play_state = _MMP_PLAY_STATE_PAUSE;
                        c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                        c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_NORMAL);
                        //b_reset_timer = TRUE;
                    #ifdef APP_TTS_SUPPORT
                        c_memset(w2s_str, 0, sizeof(w2s_str));
                        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    #endif
                        mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                        //b_wake_ui = TRUE;
                        break;
                    }
                case BTN_STOP:
                    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                    c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                    i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                    mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                    break;

           default:
           {
                i4_ret = _mmp_pp_view_red_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
                IS_MMPR_OK(i4_ret);
                i4_ret = c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
                IS_MMPR_OK(i4_ret);
           }
       }
         return i4_ret;

    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_BTN_START_SLIDESHOW));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_TXT_EXCLUDE_STATUS_TEXT);
        i4_ret = c_wgl_do_cmd (h_view_item,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SATSLSHOW)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SATSLSHOW))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
        c_wgl_repaint(h_view_item,NULL,TRUE);
    if(pt_this->e_info_state == _MMP_INFO_STATE_DETAIL_THEN_POP_UP)
    {
        if(pt_this->e_state_change_flag ==_MMP_INFO_CHANGE)
        {
           h_view_item      = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
           t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT-MMP_PHOTO_POP_UP_OFFICE;
           t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
           t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH - MMP_PHOTO_POP_UP_OFFICE;
           t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
           IS_MMPR_OK(c_wgl_move(h_view_item,&t_rect,FALSE));
           h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
           c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
           i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
        }
       else return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

    }
    else if(pt_this->e_info_state == _MMP_INFO_STATE_POP_UP)
        {

        if(pt_this->e_state_change_flag ==_MMP_INFO_CHANGE)
        {
            h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);

            t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT;
            t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
            t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
            t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
            IS_MMPR_OK(c_wgl_move(h_view_item,&t_rect,FALSE));
            c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
           i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);

        }
       else return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
    }
    return i4_ret;

}

else return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_pop_up_done_cb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pp_hide_pop_up_page(_MMP_PP_DATA_MEMBER_T*  pt_this)
{
    HANDLE_T        h_view_item=NULL_HANDLE;

    if((pt_this->e_info_state == _MMP_INFO_STATE_DETAIL_THEN_POP_UP)||
        (pt_this->e_info_state == _MMP_INFO_STATE_POP_UP_THEN_DETAIL))
    {
        mmp_mc_list_play(MMP_GROUND_MODE_FORE, MMP_PLAY_IDX_CURRENT);
        pt_this->e_info_state = _MMP_INFO_STATE_DETAIL;
    }
    else if(pt_this->e_info_state == _MMP_INFO_STATE_POP_UP)
    {
        pt_this->e_info_state = _MMP_INFO_STATE_SIMPLE;
    }
    mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
    c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
    c_wgl_repaint(h_view_item,NULL,TRUE);
    c_wgl_set_focus(pt_this->t_view.h_frame,WGL_SYNC_AUTO_REPAINT);

}

/*-----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_pop_up_done_cb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_done_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2)
{
    HANDLE_T                        h_view_item=NULL_HANDLE;
    INT32                           i4_ret=MMPR_OK;
    _MMP_PP_DATA_MEMBER_T*          pt_this = &t_g_pp;
    UINT32                          ui4_key_code = (UINT32) pv_param1;
    GL_RECT_T                       t_rect ={0};
    //BOOL                            b_reset_timer,b_wake_ui;
    UINT32                          ui4_slideshow_idx;
    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {

        switch (ui4_key_code)
        {
            case MMP_TM_BTN_SELECT:
            case BTN_INPUT_SRC:
                _mmp_pp_hide_pop_up_page(pt_this);
                break;

            case  MMP_TM_RC_KEY_DETAIL:
            if(pt_this->e_info_state == _MMP_INFO_STATE_POP_UP)
            {

                h_view_item      = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT-MMP_PHOTO_POP_UP_OFFICE;
                t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
                t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
                t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
                IS_MMPR_OK(c_wgl_move(h_view_item,&t_rect,FALSE));

                pt_this->e_info_state = _MMP_INFO_STATE_POP_UP_THEN_DETAIL;
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                mmp_com_ui_dp_view_active(pt_pdp_inst);

            }

            else if((pt_this->e_info_state == _MMP_INFO_STATE_POP_UP_THEN_DETAIL) ||
                (pt_this->e_info_state == _MMP_INFO_STATE_DETAIL_THEN_POP_UP))
            {
                i4_ret = mmp_com_ui_dp_view_inactive(pt_pdp_inst);
                pt_this->e_info_state = _MMP_INFO_STATE_POP_UP;
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);

                c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);

                t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT;
                t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
                t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
                t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
                IS_MMPR_OK(c_wgl_move(h_view_item,
                             &t_rect,
                             FALSE));
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);

            }
            break;

            case BTN_RETURN:
                pt_this->e_play_state = _MMP_PLAY_STATE_NONE;
                c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                break;
            case MMP_PP_RC_KEY_PHO_PLAY:
                if(pt_this->e_play_state == _MMP_PLAY_STATE_PLAY)
                {
                    break;
                }

                else
                {
                    pt_this->e_play_state = _MMP_PLAY_STATE_PLAY;
                    c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                    c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_NORMAL);
                #ifdef APP_TTS_SUPPORT
                    UTF16_T         w2s_str[128] = {0};
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif
                    mmp_mc_list_play(MMP_GROUND_MODE_FORE, MMP_PLAY_IDX_CURRENT);
                    _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                    i4_ret = mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX_CRT,
                                            pt_this->ui4_current_fileidx + 1,
                                            &ui4_slideshow_idx);
                    if (MMPR_OK == i4_ret)
                    {
                    #ifdef APP_TTS_SUPPORT
                        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    #endif
                        mmp_mc_list_play(MMP_GROUND_MODE_FORE, ui4_slideshow_idx);
                    }
                    break;
                }
                case MMP_PP_RC_KEY_PHO_PAUSE:
                    if(pt_this->e_play_state == _MMP_PLAY_STATE_PAUSE)
                    {
                        break;
                    }

                    else
                    {
                        pt_this->e_play_state = _MMP_PLAY_STATE_PAUSE;
                        c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                        c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_NORMAL);
                        //b_reset_timer = TRUE;
                    #ifdef APP_TTS_SUPPORT
                        UTF16_T         w2s_str[128] = {0};
                        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif
                        mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                        //b_wake_ui = TRUE;
                        break;
                    }
                case BTN_STOP:
                        h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                        c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                        i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                        mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                        break;

            default:
            {
                i4_ret = _mmp_pp_view_red_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
                IS_MMPR_OK(i4_ret);
                i4_ret = c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
                IS_MMPR_OK(i4_ret);
            }

            break;
        }
        return i4_ret;
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_BTN_DONE));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_TXT_EXCLUDE_STATUS_TEXT);
        i4_ret = c_wgl_do_cmd (h_view_item,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_DONE)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_DONE))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
        return c_wgl_repaint(h_view_item ,NULL,TRUE);

    }

     else if(ui4_msg == WGL_MSG_LOSE_FOCUS)
    {
        pt_this->e_state_change_flag = _MMP_INFO_UNCHANGE;
        return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

    }
        else return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_pop_up_browse_cb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_browse_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2)
{
    HANDLE_T                        h_view_item=NULL_HANDLE;
    INT32                           i4_ret=MMPR_OK;
    _MMP_PP_DATA_MEMBER_T*       pt_this = &t_g_pp;
    UINT32                          ui4_key_code = (UINT32) pv_param1;
    //BOOL                            b_reset_timer,b_wake_ui;
    UINT32                          ui4_slideshow_idx;
    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
        {
            case MMP_TM_BTN_SELECT:
                pt_this->e_play_state = _MMP_PLAY_STATE_NONE;
                c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                 mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                break;

            case BTN_RETURN:

                pt_this->e_play_state = _MMP_PLAY_STATE_NONE;
                c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                break;

            case BTN_INPUT_SRC:
               _mmp_pp_hide_pop_up_page(pt_this);
                break;

            case MMP_PP_RC_KEY_PHO_PLAY:
                if(pt_this->e_play_state == _MMP_PLAY_STATE_PLAY)
                {
                    break;
                }

                else
                {
                    pt_this->e_play_state = _MMP_PLAY_STATE_PLAY;
                    c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                    c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_NORMAL);
                #ifdef APP_TTS_SUPPORT
                    UTF16_T         w2s_str[128] = {0};
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif
                    mmp_mc_list_play(MMP_GROUND_MODE_FORE, MMP_PLAY_IDX_CURRENT);
                    _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                    i4_ret = mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX_CRT,
                                            pt_this->ui4_current_fileidx + 1,
                                            &ui4_slideshow_idx);
                    if (MMPR_OK == i4_ret)
                    {
                #ifdef APP_TTS_SUPPORT
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif
                        mmp_mc_list_play(MMP_GROUND_MODE_FORE, ui4_slideshow_idx);
                    }
                    break;
                }
                case MMP_PP_RC_KEY_PHO_PAUSE:
                    if(pt_this->e_play_state == _MMP_PLAY_STATE_PAUSE)
                    {
                        break;
                    }

                    else
                    {
                        pt_this->e_play_state = _MMP_PLAY_STATE_PAUSE;
                        c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                        c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_NORMAL);
                        //b_reset_timer = TRUE;
                    #ifdef APP_TTS_SUPPORT
                        UTF16_T         w2s_str[128] = {0};
                        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    #endif
                        mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                        //b_wake_ui = TRUE;
                        break;
                    }
                case BTN_STOP:
                    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                    c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                    i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                    mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                    break;

                default:
                {
                    i4_ret = _mmp_pp_view_red_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
                    IS_MMPR_OK(i4_ret);
                    c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

                }
                break;
        }
        return i4_ret;
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_BROWSE));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_TXT_EXCLUDE_STATUS_TEXT);
        i4_ret = c_wgl_do_cmd (h_view_item,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_BROWSE)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_BROWSE))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
        return c_wgl_repaint(h_view_item ,NULL,TRUE);

    }
   else return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_pop_up_rotate_left_cb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_rotate_left_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2)
{
    HANDLE_T                      h_view_item=NULL_HANDLE;
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;
    UINT32                        ui4_key_code = (UINT32) pv_param1;
    GL_RECT_T                     t_rect ={0};
    INT32                          i4_ret=MMPR_OK;
    //BOOL                            b_reset_timer,b_wake_ui;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {

        switch (ui4_key_code)
        {
            case MMP_TM_BTN_SELECT:
                if( FALSE == pt_this->b_is_notsupport_show )  /* If not support, don't apply rotate */
                {
                    _mmp_pp_view_rotate_left(pt_this);
                }
                break;

            case  MMP_TM_RC_KEY_DETAIL:
                if(pt_this->e_info_state == _MMP_INFO_STATE_POP_UP)
                {

                    h_view_item      = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                    t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT-MMP_PHOTO_POP_UP_OFFICE;
                    t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
                    t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
                    t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
                    IS_MMPR_OK(c_wgl_move(h_view_item,
                                 &t_rect,
                                 FALSE));
                    pt_this->e_info_state = _MMP_INFO_STATE_POP_UP_THEN_DETAIL;
                    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
                    i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                    mmp_com_ui_dp_view_active(pt_pdp_inst);

                }

                else if((pt_this->e_info_state == _MMP_INFO_STATE_POP_UP_THEN_DETAIL) ||
                    (pt_this->e_info_state == _MMP_INFO_STATE_DETAIL_THEN_POP_UP))
                {
                    i4_ret = mmp_com_ui_dp_view_inactive(pt_pdp_inst);
                    pt_this->e_info_state = _MMP_INFO_STATE_POP_UP;
                    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);

                    c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                    i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);

                    t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT;
                    t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
                    t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
                    t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
                    IS_MMPR_OK(c_wgl_move(h_view_item,&t_rect,FALSE));

                    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
                    i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                }
                break;

            case BTN_RETURN:
                pt_this->e_play_state = _MMP_PLAY_STATE_NONE;
                c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                break;

            case BTN_INPUT_SRC:
               _mmp_pp_hide_pop_up_page(pt_this);
                break;

            case MMP_PP_RC_KEY_PHO_PAUSE:
                if(pt_this->e_play_state == _MMP_PLAY_STATE_PAUSE)
                {
                    break;
                }

                else
                {
                    pt_this->e_play_state = _MMP_PLAY_STATE_PAUSE;
                    c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                    c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_NORMAL);
                    //b_reset_timer = TRUE;
                #ifdef APP_TTS_SUPPORT
                    UTF16_T         w2s_str[128] = {0};
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif
                    mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                    //b_wake_ui = TRUE;
                    break;
                }
            case BTN_STOP:
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
            break;
            default:
            {
                i4_ret = _mmp_pp_view_red_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
                IS_MMPR_OK(i4_ret);
                i4_ret = c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);//mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
                IS_MMPR_OK(i4_ret);
            }

            break;
        }
        return i4_ret;
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_LEFT));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_TXT_EXCLUDE_STATUS_TEXT);
        i4_ret = c_wgl_do_cmd (h_view_item,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_LEFT)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_LEFT))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
        return c_wgl_repaint(h_view_item ,NULL,TRUE);
    }
   else return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_pop_up_rotate_right_cb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_rotate_right_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2)
{
    HANDLE_T                      h_view_item;
    INT32                          i4_ret=MMPR_OK;
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;
    UINT32                        ui4_key_code = (UINT32) pv_param1;
    GL_RECT_T                     t_rect ={0};
    //BOOL                            b_reset_timer,b_wake_ui;
#ifdef APP_NET_DLNA_SUPPORT
    CHAR                        s_buf[MMP_PP_RC_STR_MAX_LEN + 1];
    SIZE_T                      z_buf_size = MMP_PP_RC_STR_MAX_LEN + 1;
    RMV_DEV_DEVICE_STATUS_T     e_dev_status = RMV_DEV_DEVICE_STATUS_UNSUPT_DEV;
#endif

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {

        switch (ui4_key_code)
        {
            case MMP_TM_BTN_SELECT:
                if( FALSE == pt_this->b_is_notsupport_show )  /* If not support, don't apply rotate */
                {
                    _mmp_pp_view_rotate_right(pt_this);
                }
                break;

            case MMP_TM_BTN_CURSOR_RIGHT:

#ifdef APP_NET_DLNA_SUPPORT

                i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                             MMP_PE_EXTRA_INFO_ID_PATH,
                                             &z_buf_size,
                                             (VOID*)s_buf);
                IS_MMPR_OK(i4_ret);

                i4_ret = a_rmv_dev_get_mnt_point_status_by_path(s_buf, &e_dev_status);
                IS_MMPR_OK(i4_ret);

                if ((RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)) ||
                    (RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status)))
                {
                    DBG_LOG_PRINT(("\n==========DLNA/NEIGHBOR==========%d\n",__LINE__));
                }
                else
#endif
                {
                    h_view_item  = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_STOP_BTN);
                    c_wgl_set_focus(h_view_item,WGL_SYNC_AUTO_REPAINT);
                }
                break;

            case  MMP_TM_RC_KEY_DETAIL:
                if(pt_this->e_info_state == _MMP_INFO_STATE_POP_UP)
                {

                    h_view_item      = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                    t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT-MMP_PHOTO_POP_UP_OFFICE;
                    t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
                    t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
                    t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
                    IS_MMPR_OK(c_wgl_move(h_view_item,&t_rect,FALSE));
                    pt_this->e_info_state = _MMP_INFO_STATE_POP_UP_THEN_DETAIL;
                    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
                    i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                    mmp_com_ui_dp_view_active(pt_pdp_inst);

                }

                else if((pt_this->e_info_state == _MMP_INFO_STATE_POP_UP_THEN_DETAIL) ||
                    (pt_this->e_info_state == _MMP_INFO_STATE_DETAIL_THEN_POP_UP))
                {
                    i4_ret = mmp_com_ui_dp_view_inactive(pt_pdp_inst);
                    pt_this->e_info_state = _MMP_INFO_STATE_POP_UP;
                    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);

                    c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                    i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);

                    t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT;
                    t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
                    t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
                    t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
                    IS_MMPR_OK(c_wgl_move(h_view_item,
                                 &t_rect,
                                 FALSE));
                    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
                    i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                }
                break;

            case BTN_RETURN:
                pt_this->e_play_state = _MMP_PLAY_STATE_NONE;
                c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                break;
            case BTN_INPUT_SRC:
                _mmp_pp_hide_pop_up_page(pt_this);
                break;

            case MMP_PP_RC_KEY_PHO_PAUSE:
                if(pt_this->e_play_state == _MMP_PLAY_STATE_PAUSE)
                {
                    break;
                }

                else
                {
                    pt_this->e_play_state = _MMP_PLAY_STATE_PAUSE;
                    c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                    c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_NORMAL);
                    //b_reset_timer = TRUE;
#ifdef APP_TTS_SUPPORT
                    UTF16_T         w2s_str[128] = {0};
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif
                    mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                    //b_wake_ui = TRUE;
                    break;
                }
            case BTN_STOP:
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
            default:
            {
                i4_ret = _mmp_pp_view_red_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
                IS_MMPR_OK(i4_ret);
                i4_ret = c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);//mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
                IS_MMPR_OK(i4_ret);
            }

            break;
        }
        return i4_ret;
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_RIGHT));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_TXT_EXCLUDE_STATUS_TEXT);
        i4_ret = c_wgl_do_cmd (h_view_item,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_RIGHT)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_RIGHT))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
        return c_wgl_repaint(h_view_item ,NULL,TRUE);

    }
   else return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}






/*----------------------------------------------------------------------------
 * Name: a_mmp_reg_photo_player
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_mmp_reg_photo_player(VOID)
{
    MMP_FILE_PLAYER_INTF_T          t_intf;
    MMP_MC_FILE_PLAYER_PROPERTY_T   t_prop;
    INT32                           i4_ret;

    /**/
    MMP_FILE_PLAYER_INTF_ZERO(t_intf);
    /*media interface*/
    t_intf.t_media_intf.pf_init = _mmp_pp_init;
    t_intf.t_media_intf.pf_deinit = _mmp_pp_deinit;
    t_intf.t_media_intf.pf_handle_msg = _mmp_pp_handle_msg;
    t_intf.t_media_intf.pf_is_type_of = mmp_pe_is_type_of;

    /*file info interface*/
    t_intf.t_info_intf.pf_open = mmp_pe_info_open;
    t_intf.t_info_intf.pf_close = mmp_pe_info_close;
    t_intf.t_info_intf.pf_get = mmp_pe_info_get;
    t_intf.t_info_intf.pf_set = mmp_pe_info_set;
    t_intf.t_info_intf.pf_cmd_do = mmp_pe_info_cmd_do;
    t_intf.t_info_intf.pf_cmd_res_init = mmp_pe_info_cmd_res_init;
    t_intf.t_info_intf.pf_cmd_res_reset = mmp_pe_info_cmd_res_reset;
    t_intf.t_info_intf.pf_cmd_res_deinit = mmp_pe_info_cmd_res_deinit;

    /*file show interface*/
    t_intf.t_show_intf.pf_open = _mmp_pp_show_open;
    t_intf.t_show_intf.pf_close = _mmp_pp_show_close;
    t_intf.t_show_intf.pf_attr_set = _mmp_pp_show_attr_set;
    t_intf.t_show_intf.pf_next_preload = _mmp_pp_show_next_preload;
    t_intf.t_show_intf.pf_next_attr_set = _mmp_pp_show_next_attr_set;
    t_intf.t_show_intf.pf_cmd_do = _mmp_pp_show_cmd_do;

    t_intf.t_info_hdlr_intf.pf_init      = _mmp_pp_info_hdlr_init;
    t_intf.t_info_hdlr_intf.pf_deinit    = _mmp_pp_info_hdlr_deinit;
    t_intf.t_info_hdlr_intf.pf_cmd_do    = _mmp_pp_info_hdlr_cmd_do;

    /**/
    t_prop.e_type = MMP_MEDIA_TYPE_PHOTO;
    t_prop.e_excl_type = MMP_MEDIA_TYPE_VIDEO;

    i4_ret = mmp_mc_reg_file_player(&t_intf, &t_prop);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_mc_reg_file_player() failed. i4_ret = %d.\r\n", i4_ret));
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * private VIEW methods implementations
 *---------------------------------------------------------------------------*/
#ifdef APP_CAPTURE_LOGO_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_do_nfy_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pp_do_nfy_fct(VOID*      pv_host,
                              VOID*      pv_msg,
                              VOID*      pv_param1,
                              VOID*      pv_param2)
{
    UINT32                   ui4_msg, ui4_param1, ui4_param2;
    _MMP_PP_DATA_MEMBER_T*   pt_this = (_MMP_PP_DATA_MEMBER_T*)pv_host;
    CAP_PARAM_T              t_param;
    HANDLE_T                 h_sur = NULL_HANDLE;
    HANDLE_T                 h_work_sur = NULL_HANDLE;

    ui4_msg    = (UINT32)pv_msg;
    ui4_param1 = (UINT32)pv_param1;
    ui4_param2 = (UINT32)pv_param2;

    switch(ui4_msg)
    {
        case CAP_MSG_PRE_ACTIVATE:
            /*hide photo player UI*/
            _mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_NONE);

           // _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_STOP);

            pt_this->b_cap_ui_active = TRUE;

            /*set photo source and the surface handle*/
            t_param.e_param_type = CAP_PARAM_PHOTO_SOURCE;

            mmp_pe_get_curnt_surf(&h_sur, &h_work_sur);
            t_param.u.t_photo.h_src_surf = h_sur;
            t_param.u.t_photo.h_working_surf = h_work_sur;

            a_cap_set_capture_param(pt_this->pv_cap, (VOID *)&t_param);
            break;
        case CAP_MSG_POST_INACTIVATE:
            if(pt_this->b_pause_by_cap)
            {
                mmp_mc_list_play(MMP_GROUND_MODE_FORE, MMP_PLAY_IDX_CURRENT);
            }

            pt_this->b_cap_ui_active = FALSE;

            //_mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);

            mmp_pe_restart_preload();
            break;
        case CAP_MSG_FAIL:
            a_cap_abort(pt_this->pv_cap);
            break;
        default:
            break;
    }

    a_cap_def_msg_process(pt_this->pv_cap, ui4_msg, ui4_param1, ui4_param2);
}
/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_cap_logo_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pp_cap_logo_proc_fct(VOID*      pv_tag,
                                    UINT32     ui4_msg,
                                    UINT32     ui4_param1,
                                    UINT32     ui4_param2)
{
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_pp_do_nfy_fct,
                                pv_tag,
                                (VOID*)ui4_msg,
                                (VOID*)ui4_param1,
                                (VOID*)ui4_param2);
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_init(VOID)
{
    MMP_PE_INIT_SETTING_T       t_setting;
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;
    HANDLE_T                      h_view_item;
    ISO_639_LANG_T               s639_lang;
    UINT8                         ui1_gui_lang_id;
    INT32                          i4_ret;
    WGL_KEY_LINK_T               at_key_lnk[3];
    HANDLE_T                      ah_items[MMP_PP_MAX_NAV_WIG__NUM];
#ifdef APP_CAPTURE_LOGO_SUPPORT
    CAP_INIT_T                   t_cap_init;
#endif

    /**/
    c_memset(pt_this, 0, sizeof(_MMP_PP_DATA_MEMBER_T));

    /*init photo engine*/
    c_memset(&t_setting, 0, sizeof(MMP_PE_INIT_SETTING_T));
    t_setting.b_quick_rotate = MMP_PP_RC_IS_QUICK_ROTATE();
    t_setting.b_no_thumb_from_main = MMP_PP_RC_IS_NO_THUMB_FROM_MAIN();
    i4_ret = mmp_pe_init(&t_setting);
    pt_this->e_state_change_flag = _MMP_INFO_UNCHANGE;
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_pe_init() fail. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }

    /*init view*/
    i4_ret = _mmp_pp_view_init(pt_this);
    if(MMPR_OK != i4_ret)
    {
        _mmp_pp_deinit();
    }

    i4_ret = c_wgl_set_widget_proc(mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_INFO_BTN),
                                           _mmp_thumbnailmode_pop_up_info_cb);
    IS_MMPR_OK(i4_ret);

    i4_ret = c_wgl_set_widget_proc(mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_STARTSLIDESHOW_BTN),
                                          _mmp_thumbnailmode_pop_up_start_slideshow_cb);
    IS_MMPR_OK(i4_ret);

    i4_ret = c_wgl_set_widget_proc(mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_DONE_BTN),
                            _mmp_thumbnailmode_pop_up_done_cb);
    IS_MMPR_OK(i4_ret);

    i4_ret = c_wgl_set_widget_proc(mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_FULL_SCREEN_BTN),
                            _mmp_thumbnailmode_pop_up_browse_cb);
    IS_MMPR_OK(i4_ret);

    i4_ret = c_wgl_set_widget_proc(mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_ROTATE_LEFT_BTN),
                            _mmp_thumbnailmode_pop_up_rotate_left_cb);
    IS_MMPR_OK(i4_ret);

    i4_ret = c_wgl_set_widget_proc(mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_ROTATE_RIGHT_BTN),
                            _mmp_thumbnailmode_pop_up_rotate_right_cb);
    IS_MMPR_OK(i4_ret);

    i4_ret = c_wgl_set_widget_proc(mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_STOP_BTN),
                            _mmp_thumbnailmode_pop_up_skip_cb);
    IS_MMPR_OK(i4_ret);

    a_cfg_get_gui_lang(s639_lang);
    ui1_gui_lang_id  = mlm_mmp_s639_to_langidx(s639_lang);
    pt_this->ui1_gui_lang_id = ui1_gui_lang_id;

    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_TXT_MODIFY_BTN_TEXT);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_TITLE_MODIFY_PHOTO)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_TITLE_MODIFY_PHOTO))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);

    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_STARTSLIDESHOW_BTN);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_START_SLIDESHOW)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_START_SLIDESHOW))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);

    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_DONE_BTN);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_DONE)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_DONE))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_FULL_SCREEN_BTN);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BROWSE)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BROWSE))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);


    ah_items[0] = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_INFO_BTN);
    ah_items[1] = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_ROTATE_LEFT_BTN);
    ah_items[2] = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_ROTATE_RIGHT_BTN);
    ah_items[3] = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_STOP_BTN);
    ah_items[4] = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_FULL_SCREEN_BTN);
    ah_items[5] = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_STARTSLIDESHOW_BTN);
    ah_items[6] = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_DONE_BTN);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[0].h_widget = ah_items[5] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_RIGHT;
    at_key_lnk[1].h_widget = ah_items[1];
    i4_ret = c_wgl_set_navigation(ah_items[0], 2, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_LEFT;
    at_key_lnk[0].h_widget = ah_items[0] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_RIGHT;
    at_key_lnk[1].h_widget = ah_items[2];
    at_key_lnk[2].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[2].h_widget = ah_items[5] ;
    i4_ret = c_wgl_set_navigation(ah_items[1], 3, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_LEFT;
    at_key_lnk[0].h_widget = ah_items[1] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = ah_items[5];
    i4_ret = c_wgl_set_navigation(ah_items[2], 3, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_LEFT;
    at_key_lnk[0].h_widget = ah_items[2] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = ah_items[5];
    i4_ret = c_wgl_set_navigation(ah_items[3], 2, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = ah_items[0] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = ah_items[4];
    i4_ret = c_wgl_set_navigation(ah_items[5], 2, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = ah_items[5] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = ah_items[6];
    i4_ret = c_wgl_set_navigation(ah_items[4], 2, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = ah_items[4] ;
    i4_ret = c_wgl_set_navigation(ah_items[6], 1, at_key_lnk);


#ifdef APP_CAPTURE_LOGO_SUPPORT
    /*capture logo lib create*/
    c_memset(&t_cap_init, 0, sizeof(CAP_INIT_T));
    t_cap_init.h_parent = pt_this->t_view.h_frame;
    t_cap_init.pv_tag   = pt_this;
    t_cap_init.pf_fct   = _mmp_pp_cap_logo_proc_fct;
    t_cap_init.e_source = CAP_SRC_TYPE_MM_IMAGE;

    i4_ret = a_cap_create(&t_cap_init, &pt_this->pv_cap);
    if(MMPR_OK != i4_ret)
    {
        a_cap_destroy(pt_this->pv_cap);
    }
#endif

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_deinit(VOID)
{
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;

    pt_this->pf_nfy = NULL;
    pt_this->pv_nfy_tag = NULL;


    /*free view*/
    _mmp_pp_view_deinit(pt_this);

#ifdef APP_CAPTURE_LOGO_SUPPORT
    a_cap_destroy(pt_this->pv_cap);
#endif

    /*deinit photo engine*/
    return mmp_pe_deinit();
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_ch_lang_text
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_ch_lang_text(UINT8 ui1_gui_lang_id)
{
    HANDLE_T        h_view_item = NULL_HANDLE;
    INT32           i4_ret = MMPR_OK, i4_ret2 = MMPR_OK;
    CHAR            s_result[MMP_PP_RC_STR_MAX_LEN + 1] = {0};
    CHAR            s_dest_result[MMP_PP_RC_STR_MAX_LEN + 1] = {0};
    UTF16_T         w2s_info[MMP_PP_RC_STR_MAX_LEN + 1] = {0};
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;

    /* Set pop up page text */
    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_TXT_MODIFY_BTN_TEXT);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_TITLE_MODIFY_PHOTO)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_TITLE_MODIFY_PHOTO))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_STARTSLIDESHOW_BTN);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_START_SLIDESHOW)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_START_SLIDESHOW))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_DONE_BTN);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_DONE)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_DONE))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_BTN_FULL_SCREEN_BTN);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BROWSE)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BROWSE))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
    c_wgl_repaint(h_view_item,NULL,TRUE);

    /*Set detail page info text */
    i4_ret2 = mmp_mc_list_get_item_count(MMP_GROUND_MODE_FORE, &pt_this->ui4_total_fileidx );
    mmp_mc_list_get_idx(MMP_GROUND_MODE_FORE, MMP_PL_IDX_TYPE_CRNT_PLAY,  &pt_this->ui4_current_fileidx );
    if(MMPR_OK != i4_ret || MMPR_OK != i4_ret2)
    {
        MMP_DBG_ERROR(("mmp_mc_list_get_item_count(MMP_GROUND_MODE_FORE) (ret = %d) or mmp_mc_list_get_idx(%d) (i4_ret = %d) fail.\r\n", i4_ret2, MMP_PL_IDX_TYPE_CRNT_PLAY, i4_ret));
        w2s_info[0] = 0;
    }
    else
    {
        i4_ret = c_uc_w2s_to_ps(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_MMP_DP_INFO_TEMP),
                                s_result,
                                sizeof(s_result));
        MMPR_LOG_ON_FAIL(i4_ret);
        i4_ret = c_snprintf(s_dest_result,(SIZE_T)(MMP_PP_RC_STR_MAX_LEN + 1), s_result, (pt_this->ui4_current_fileidx + 1), pt_this->ui4_total_fileidx);
        c_uc_ps_to_w2s(s_dest_result, w2s_info, sizeof(w2s_info));
    }

    h_view_item = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE0);
    i4_ret = c_wgl_do_cmd (h_view_item,
                           WGL_CMD_TEXT_SET_TEXT,
                           WGL_PACK (w2s_info),
                           WGL_PACK (c_uc_w2s_strlen (w2s_info)));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL1);
    i4_ret = c_wgl_do_cmd (h_view_item,
                    WGL_CMD_TEXT_SET_TEXT,
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_DP_DT)),
                    WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_DP_DT))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL2);
    i4_ret = c_wgl_do_cmd (h_view_item,
                    WGL_CMD_TEXT_SET_TEXT,
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_DP_NM)),
                    WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_DP_NM))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL3);
    i4_ret = c_wgl_do_cmd (h_view_item,
                    WGL_CMD_TEXT_SET_TEXT,
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_CAMERA)),
                    WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_CAMERA))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL4);
    i4_ret = c_wgl_do_cmd (h_view_item,
                    WGL_CMD_TEXT_SET_TEXT,
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_RESOLUTION)),
                    WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_RESOLUTION))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL5);
    i4_ret = c_wgl_do_cmd (h_view_item,
                    WGL_CMD_TEXT_SET_TEXT,
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_DP_SZ)),
                    WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_DP_SZ))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL6);
    i4_ret = c_wgl_do_cmd (h_view_item,
                    WGL_CMD_TEXT_SET_TEXT,
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_SPEED)),
                    WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_SPEED))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL7);
    i4_ret = c_wgl_do_cmd (h_view_item,
                    WGL_CMD_TEXT_SET_TEXT,
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_ISO)),
                    WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_ISO))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL8);
    i4_ret = c_wgl_do_cmd (h_view_item,
                    WGL_CMD_TEXT_SET_TEXT,
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_FLASH)),
                    WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_FLASH))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL9);
    i4_ret = c_wgl_do_cmd (h_view_item,
                    WGL_CMD_TEXT_SET_TEXT,
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_EXP_PROGRAM)),
                    WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_EXP_PROGRAM))));
    IS_MMPR_OK(i4_ret);

    h_view_item = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL10);
    i4_ret = c_wgl_do_cmd (h_view_item,
                    WGL_CMD_TEXT_SET_TEXT,
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_BAIS)),
                    WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_BUTX_PHOTO_BAIS))));
    IS_MMPR_OK(i4_ret);
    c_wgl_repaint(pt_this->t_view.h_frame,NULL,TRUE);
    return MMPR_OK;

}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_handle_msg
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_handle_msg(
    MMP_MSG_ID_T                e_msg_id,
    VOID*                       pv_msg_param)
{

    _MMP_PP_DATA_MEMBER_T*          pt_this = &t_g_pp;
#ifdef APP_MENU_MMP_COEXIST
    INT32                           i4_ret=MMPR_OK;
    HANDLE_T                        h_view_item=NULL_HANDLE;
#endif
    ISO_639_LANG_T                  s639_lang;
    UINT16                      ui2_lang_id = 0;

    switch(e_msg_id)
    {
    case MMP_MSG_ID_APP_RESUMED:
        {
            MMP_EXEC_WITH_ASSERT(mmp_pe_alloc_common_res(), MMPR_OK);
        }
        break;

    case MMP_MSG_ID_APP_PAUSED:
        {
            t_g_pp.b_pp_view_active = FALSE;

            mmp_pe_free_common_res();
        }
        break;

#ifdef APP_MENU_MMP_COEXIST
    case MMP_MSG_ID_APP_STAT_XNG:
    {
        MMP_STAT_XNG_INFO_T*    pt_mmp_stat_info = (MMP_STAT_XNG_INFO_T*)pv_msg_param;

        if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == pt_mmp_stat_info->e_mmp_stat_new)
        {
            if(pt_this->b_pp_view_active == TRUE)
            {
                switch(pt_this->e_info_state)
                {
                    case _MMP_INFO_STATE_POP_UP_THEN_DETAIL:
                    case _MMP_INFO_STATE_DETAIL_THEN_POP_UP:
                    case _MMP_INFO_STATE_DETAIL:
                        pt_this->e_info_state = _MMP_INFO_STATE_DETAIL;
                        break;
                    case _MMP_INFO_STATE_SIMPLE:
                    case _MMP_INFO_STATE_POP_UP:
                        pt_this->e_info_state = _MMP_INFO_STATE_SIMPLE;
                        break;
                    default:
                        break;
                }
                h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
                c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
                i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
                c_wgl_set_focus(pt_this->t_view.h_frame,WGL_SYNC_AUTO_REPAINT);
            }
        }
        else if (MMP_MAIN_AP_STATUS_RESUMED == pt_mmp_stat_info->e_mmp_stat_new)
        {

        }
    }
    break;
#endif
    case MMP_MSG_ID_GUI_LANG_XNG:

        i4_ret = a_cfg_get_gui_lang(s639_lang);
        if(i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("MMP photo player get language fail \r\n"));
            pt_this->ui1_gui_lang_id =0;
        }
        else
        {
            pt_this->ui1_gui_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
        }

        _mmp_pp_ch_lang_text(pt_this->ui1_gui_lang_id);

        ui2_lang_id = _mmp_pp_get_mlm_lang_id();

        a_mmp_info_bar_refresh_msg(MLM_MMP_TEXT(ui2_lang_id, pt_this->ui4_mlm_id),pt_this->b_is_notsupport_show);
        break;

    default:
        break;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_show_open
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_show_open(
    const CHAR*                 ps_filename,
    mmp_fp_show_nfy_fct         pf_nfy,
    VOID*                       pv_tag,
    UINT32                      ui4_ver)
{
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;
    INT32                       i4_ret;
    MMP_PE_EXTRA_ATTR_T         t_extra_attr;
    MMP_FP_LOAD_IMG_ROTATE_OP_T e_force_rotate_op = MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE;

    i4_ret = _mmp_pp_get_force_rotate_op(ps_filename, &e_force_rotate_op);
    if (MMPR_OK == i4_ret && MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE != e_force_rotate_op)
    {
        t_extra_attr.e_extra_id = MMP_PE_EXTRA_ATTR_ID_FORCE_ROTATE_OP;
        t_extra_attr.pv_extra_param = (VOID*)e_force_rotate_op;
        mmp_pe_play_extra_attr_set(1, &t_extra_attr);
    }

    DBG_INFO_DIRECT("[mmp pp] %s %d e_force_rotate_op:%d \r\n",__FUNCTION__,__LINE__,e_force_rotate_op);

    i4_ret = mmp_pe_play_open(ps_filename, _mmp_pp_play_nfy_cb, NULL, ui4_ver);
    if(MMPR_OK != i4_ret && MMPR_IS_OPENED != i4_ret)
    {
        pt_this->pf_nfy = NULL;
        pt_this->pv_nfy_tag = NULL;
    }
    else
    {
        pt_this->pf_nfy = pf_nfy;
        pt_this->pv_nfy_tag = pv_tag;

        /*update file information*/
        _mmp_pp_view_update_info(pt_this);
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_show_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_show_close(VOID)
{
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;
    INT32                       i4_ret;

    i4_ret = mmp_pe_play_close();

    pt_this->pf_nfy = NULL;
    pt_this->pv_nfy_tag = NULL;

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_show_attr_set
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_show_attr_set(
    UINT32                      ui4_attr_count,
    const MMP_FP_SHOW_ATTR_T*   at_show_attr)
{
    return mmp_pe_play_attr_set(ui4_attr_count, at_show_attr);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_show_next_preload
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_show_next_preload(
    const CHAR*                 ps_filename)
{
    INT32                       i4_ret = 0;
    MMP_PE_EXTRA_ATTR_T         t_extra_attr;
    MMP_FP_LOAD_IMG_ROTATE_OP_T e_force_rotate_op = MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE;

    i4_ret = _mmp_pp_get_force_rotate_op(ps_filename, &e_force_rotate_op);
    if (MMPR_OK == i4_ret && MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE != e_force_rotate_op)
    {
        t_extra_attr.e_extra_id = MMP_PE_EXTRA_ATTR_ID_FORCE_ROTATE_OP;
        t_extra_attr.pv_extra_param = (VOID*)e_force_rotate_op;
        mmp_pe_play_next_extra_attr_set(1, &t_extra_attr);
    }

    i4_ret = mmp_pe_play_next_preload(ps_filename);
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_show_next_attr_set
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_show_next_attr_set(
    UINT32                      ui4_attr_count,
    const MMP_FP_SHOW_ATTR_T*   at_show_attr)
{
    return mmp_pe_play_next_attr_set(ui4_attr_count, at_show_attr);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_show_cmd_do
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_show_cmd_do(
    MMP_FP_SHOW_CMD_ID_T        e_cmd_id,
    VOID*                       pv_cmd_param)
{
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;
    INT32                       i4_ret;
    MMP_PLAY_STATE_T            e_state;
    //IMG_TFX_EFFECT_T            e_effect_mode;
    UINT32                      ui4_effect_mode;

    DBG_LOG_PRINT(("[MMP][%s %d] show cmd <=%s=> \n",__FUNCTION__,__LINE__,SHOW_CMD(e_cmd_id)));

    switch(e_cmd_id)
    {
    case MMP_FP_SHOW_CMD_ID_START:          /*pv_param: NULL. Not used*/
        {
            i4_ret = mmp_pe_play_start();

            if(MMPR_OK == i4_ret || MMPR_IS_PLAYED == i4_ret)
            {
                e_state = MMP_PLAY_STATE_PLAYED;

                /* Update file index */
               _mmp_pp_view_update_fileidx(pt_this, MMP_PL_IDX_TYPE_CRNT_PLAY, FALSE);
            }
            else
            {
                e_state = MMP_PLAY_STATE_STOPPED;
            }
        }
        break;

    case MMP_FP_SHOW_CMD_ID_PAUSE:          /*pv_param: NULL. Not used*/
        {
            i4_ret = mmp_pe_play_pause();
            if(MMPR_OK == i4_ret || MMPR_IS_PAUSED == i4_ret)
            {
                e_state = MMP_PLAY_STATE_PAUSED;
            }
            else
            {
                e_state = MMP_PLAY_STATE_STOPPED;
            }
        }
        break;

    case MMP_FP_SHOW_CMD_ID_STOP:           /*pv_param: NULL. Not used*/
        {
            i4_ret = mmp_pe_play_stop();
            e_state = MMP_PLAY_STATE_STOPPED;
        }
        break;

    case MMP_FP_SHOW_CMD_ID_ACTIVATE:       /*pv_param: NULL. Not used*/
        {
            pt_this->ui4_zoom_idx = 0;
            pt_this->e_label_state  = _MMP_LABEL_STATE_PLAY;

            pt_this->b_pp_view_active = TRUE;
            pt_this->b_pause_by_cap   = FALSE;
            pt_this->b_cap_ui_active  = FALSE;

            //_mmp_pp_random_effect(pt_this);
            return _mmp_pp_view_activate(pt_this);
        }

    case MMP_FP_SHOW_CMD_ID_INACTIVATE:     /*pv_param: a BOOL value. TRUE: stop the play too. FALSE: don't stop the play*/
        {
            pt_this->b_pp_view_active = FALSE;

            /* Hide not support text */
            _mmp_pp_view_close_msgbox();
            a_optl_hide(pt_this->t_view.h_optl);
            c_wgl_show(pt_this->t_view.h_not_show_file_title,WGL_SW_HIDE);

            if(TRUE == (BOOL)(UINT32)pv_cmd_param)
            {
                mmp_pe_play_stop();
                mmp_pe_play_clean();
            }

            pt_this->e_label_state = _MMP_LABEL_STATE_PLAY;
            _mmp_pp_view_update_label(pt_this);

            /* Clear file name when leaving photo player to prevent dislaying last file name when entering photo player. */
            #if 0
            i4_ret = mmp_common_ui_toolbar_cmd_do(pt_ptb_inst,
                                                  MMP_PP_TB_CMD_SET_FILENAME,
                                                  (VOID*)(L""),
                                                  MMP_TB_NON_REPAINT);

            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_TEXT_SET_TEXT) fail. i4_ret = %d.\r\n", i4_ret));
            }
            #endif
            i4_ret = c_wgl_show(pt_this->t_view.h_frame, WGL_SW_HIDE);
            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_show(WGL_SW_HIDE) fail. i4_ret = %d.\r\n", i4_ret));
                return MMPR_FAIL;
            }

#ifdef APP_CAPTURE_LOGO_SUPPORT
            if(pt_this->b_cap_ui_active)
            {
                a_cap_abort(pt_this->pv_cap);
            }
#endif
            _mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_NONE);
            pt_this->e_info_state = _MMP_INFO_STATE_NONE;
        }
        return MMPR_OK;
    case MMP_FP_SHOW_CMD_ID_NEXT_EX:
    case MMP_FP_SHOW_CMD_ID_NEXT:           /*pv_param: an UINT32 value. This is a version id that file player has to send back to the client with notification*/
        {
            i4_ret = mmp_pe_play_next(e_cmd_id == MMP_FP_SHOW_CMD_ID_NEXT_EX ?  ((MMP_FP_SHOW_NEXT_PARAM_T*)pv_cmd_param)->ui4_ver : (UINT32)pv_cmd_param);

            /* Recover zoom to 1X while play next picture */
            pt_this->ui4_zoom_idx = 0;

            /* Update file index */
            _mmp_pp_view_update_fileidx(pt_this, MMP_PL_IDX_TYPE_CRNT_PLAY, FALSE);
            /*update file information*/
            _mmp_pp_view_update_info(pt_this);

            mmp_tm_get_photo_effect(&ui4_effect_mode);
            //e_effect_mode = (IMG_TFX_EFFECT_T)ui4_effect_mode;
            if(ui4_effect_mode == MMP_TM_EFFECT_RANDOM)
            {
                _mmp_pp_random_effect(pt_this);
            }

            return i4_ret;
        }

    case MMP_FP_SHOW_CMD_ID_PREVIEW_ACTIVATE:
        {
            GL_RECT_T      t_pre_rect = {0};

            t_pre_rect.i4_left = ((MMP_FP_PREVIEW_INFO_T*)pv_cmd_param)->t_preview_rect.i4_left;
            t_pre_rect.i4_right= ((MMP_FP_PREVIEW_INFO_T*)pv_cmd_param)->t_preview_rect.i4_right;
            t_pre_rect.i4_top= ((MMP_FP_PREVIEW_INFO_T*)pv_cmd_param)->t_preview_rect.i4_top;
            t_pre_rect.i4_bottom= ((MMP_FP_PREVIEW_INFO_T*)pv_cmd_param)->t_preview_rect.i4_bottom;

            mmp_drc_convert_rect_coord(((MMP_FP_PREVIEW_INFO_T*)pv_cmd_param)->e_coords, &t_pre_rect);
            mmp_pe_preview_start(&t_pre_rect);
            mmp_drc_switch_mode(MMP_DRC_MODE_FREE);
            return MMPR_OK;
        }

    case MMP_FP_SHOW_CMD_ID_PREVIEW_INACTIVATE:
        mmp_pe_preview_exit();
        return MMPR_OK;

    default:
        return MMPR_NOT_SUPPORT;
    }

    /*update status icon*/
    _mmp_pp_view_update_play_status(pt_this, e_state);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_pp_info_hdlr_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_info_hdlr_init(MMP_FP_INFO_HDLR_INIT_PARAM_T*  pt_param,
                                 VOID**                          ppv_info_hdlr_inst)
{
    INT32                       i4_ret = -1;
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;

    if(pt_this->t_view.t_info_hdlr.b_inited)
    {
        return MMPR_OK;
    }

    if(MMP_FP_INFO_HDLR_UI_TYPE_TM_FOCUS == pt_param->e_ui_type || MMP_FP_INFO_HDLR_UI_TYPE_TM_ACT_BK == pt_param->e_ui_type)
    {
        pt_this->t_view.t_info_hdlr.e_thum_mode = MMP_COM_FP_INFO_UI_TYPE_TM;
    }
    else
    {
        pt_this->t_view.t_info_hdlr.e_thum_mode = MMP_COM_FP_INFO_UI_TYPE_LM;
    }

    i4_ret = mmp_com_ui_focus_info_frm_create(pt_param->h_parent,
                                              pt_this->t_view.t_info_hdlr.e_thum_mode,
                                              MMP_COM_INFO_FP_TYPE_PP,
                                              ppv_info_hdlr_inst);
    IS_MMPR_OK(i4_ret);

    i4_ret = mmp_com_ui_fp_focus_set_elem_num(*ppv_info_hdlr_inst,
                                              MMP_COM_FP_TYPE_PP,
                                              FALSE);
    IS_MMPR_OK(i4_ret);

    pt_this->t_view.t_info_hdlr.b_inited = TRUE;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_pp_info_hdlr_deinit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_info_hdlr_deinit(VOID*  pv_info_hdlr_inst)
{
    INT32                       i4_ret = -1;
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;

    if(FALSE == pt_this->t_view.t_info_hdlr.b_inited)
    {
        return MMPR_OK;
    }

    i4_ret = mmp_com_ui_focus_info_frm_destroy(pt_this->t_view.t_info_hdlr.e_thum_mode,
                                                   MMP_COM_INFO_FP_TYPE_PP,
                                                        pv_info_hdlr_inst);
    IS_MMPR_OK(i4_ret);

    pt_this->t_view.t_info_hdlr.b_inited = FALSE;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_pp_info_hdlr_cmd_do
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_info_hdlr_cmd_do(VOID*                      pv_info_hdlr_inst,
                                     MMP_FP_INFO_HDLR_CMD_ID_T  e_cmd,
                                     VOID*                      pv_cmd_param)
{
    INT32                       i4_ret = -1;
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;

    switch(e_cmd)
    {
        case MMP_FP_INFO_HDLR_CMD_ID_SHOW:
            i4_ret = mmp_com_ui_focus_info_frm_active(pv_info_hdlr_inst,
                                                      MMP_COM_FP_TYPE_PP,
                                                      TRUE);
            IS_MMPR_OK(i4_ret);
            break;
        case MMP_FP_INFO_HDLR_CMD_ID_HIDE:
            i4_ret = mmp_com_ui_focus_info_frm_inactive(pv_info_hdlr_inst, (BOOL)(UINT32)pv_cmd_param);
            IS_MMPR_OK(i4_ret);
            break;
        case MMP_FP_INFO_HDLR_CMD_ID_UPDATE_FOCUS_ITEM:
        {
            i4_ret = _mmp_pp_view_update_file_name(pt_this, pv_cmd_param, pv_info_hdlr_inst, TRUE);
            IS_MMPR_OK(i4_ret);

            i4_ret = _mmp_pp_view_update_file_info_solution(pt_this, pv_cmd_param, pv_info_hdlr_inst);
            IS_MMPR_OK(i4_ret);

            i4_ret = _mmp_pp_view_update_file_info_size(pt_this, pv_cmd_param, pv_info_hdlr_inst);
            IS_MMPR_OK(i4_ret);

            i4_ret = _mmp_pp_view_update_file_info_protect(pt_this, pv_cmd_param, pv_info_hdlr_inst);
            IS_MMPR_OK(i4_ret);
        }
            break;
        case MMP_FP_INFO_HDLR_CMD_ID_RESET:
            i4_ret = _mmp_pp_view_reset_info_hdlr(pv_info_hdlr_inst);
            IS_MMPR_OK(i4_ret);
            break;
        default:
            break;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pp_optl_cb_fac
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static VOID _pp_optl_cb_fac(VOID*    pv_tag,
                          UINT32   ui4_msg,
                          VOID*    pv_param1,
                          VOID*    pv_param2)
{
    UINT32                   ui4_key_code = 0;
    INT32                    i4_ret  = -1;
    _MMP_PP_DATA_MEMBER_T*   pt_this = &t_g_pp;

    switch(ui4_msg)
    {
        case OPTL_MSG_KEY_INPUT:
            _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);

            ui4_key_code = (UINT32)pv_param1;

            if(MMP_PP_RC_KEY_BROWSE == ui4_key_code)
            {
                i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
                if(WGLR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("c_wgl_set_focus() fail. i4_ret = %d.\r\n", i4_ret));
                    return;
                }
            }

            if(MMP_PP_RC_KEY_OPTION == ui4_key_code)
            {
                i4_ret = a_optl_hide(pt_this->t_view.h_optl);
                if(WGLR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("a_optl_hide() fail. i4_ret = %d.\r\n", i4_ret));
                    return;
                }

                i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
                if(WGLR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("c_wgl_set_focus() fail. i4_ret = %d.\r\n", i4_ret));
                    return;
                }
            }
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
            else
            {
                i4_ret = mmp_mc_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
          if(MMPR_OK == i4_ret)
          {
              a_optl_hide(pt_this->t_view.h_optl);
          }
            }
#endif
            break;
        case OPTL_MSG_ITEM_HIGHLIGHT:
            break;
        case OPTL_MSG_HIDE_TIMEOUT:
            break;
        case OPTL_MSG_CANCELLED:
            break;
        default:
            break;
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_pp_play_pause
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_play_pause(VOID* pv_tag)
{
    INT32                       i4_ret               = -1;
    UINT16                      ui2_main_lst_hlt_idx = 0;
    UINT16                      ui2_sub_lst_hlt_idx  = 0;
    _MMP_PP_DATA_MEMBER_T*      pt_this              = &t_g_pp;
    _MMP_LABEL_STATE_T          e_label_state = _MMP_LABEL_STATE_PLAY;

#ifdef MMP_PP_ACTION_SELECT_EXIT
    i4_ret = a_optl_hide(pt_this->t_view.h_optl);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_optl_hide fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_focus fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
#else
    if(_MMP_LABEL_STATE_PLAY == pt_this->e_label_state)
    {
        e_label_state = _MMP_LABEL_STATE_PAUSE;
    }

    i4_ret = a_optl_get_hlt_index(pt_this->t_view.h_optl,
                                  &ui2_main_lst_hlt_idx,
                                  &ui2_sub_lst_hlt_idx);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_optl_get_hlt_index fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = _mmp_pp_opt_set_item(e_label_state);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("_mmp_pp_opt_set_item fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = a_optl_set_hlt_index(pt_this->t_view.h_optl,
                                  ui2_main_lst_hlt_idx,
                                  ui2_sub_lst_hlt_idx);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_optl_set_hlt_index fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

#endif

    if(_MMP_LABEL_STATE_PLAY != pt_this->e_label_state)
    {
        mmp_mc_list_play(MMP_GROUND_MODE_FORE, MMP_PLAY_IDX_CURRENT);
    }
    else
    {
        mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_pp_show_hide_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_show_hide_info(VOID* pv_tag)
{
    INT32                       i4_ret               = -1;
    _MMP_PP_DATA_MEMBER_T*      pt_this              = &t_g_pp;

    if(_MMP_INFO_STATE_SIMPLE == pt_this->e_info_state)
    {
#ifdef MMP_GUI_AUTHORING_DP
        mmp_com_ui_dp_view_active(pt_pdp_inst);
#else
        i4_ret = c_wgl_set_visibility(pt_this->t_view.t_detailpage.h_page, WGL_SW_RECURSIVE);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_set_visibility fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }
#endif

        i4_ret = c_wgl_set_visibility(pt_this->t_view.h_optl, WGL_SW_HIDE);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_set_visibility fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }

        i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_set_focus fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }

        i4_ret = c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_repaint fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }

        pt_this->e_info_state = _MMP_INFO_STATE_DETAIL;

    }
    else
    {
#ifdef MMP_GUI_AUTHORING_DP
        mmp_com_ui_dp_view_inactive(pt_pdp_inst);
#else
        i4_ret = c_wgl_show(pt_this->t_view.t_detailpage.h_page, WGL_SW_HIDE);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_show fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }
#endif
        pt_this->e_info_state = _MMP_INFO_STATE_SIMPLE;
    }

    return MMPR_OK;
}

static VOID _mmp_pp_fm_copy_nfy(HANDLE_T           h_req,
                               VOID*               pv_tag,
                               FM_COPY_NFY_COND_T  e_copy_cond,
                               UINT32              ui4_data)
{
    FM_CONFIRM_FILE_REPLACE_T*    pt_confm = (FM_CONFIRM_FILE_REPLACE_T* )ui4_data;

    if(FM_COPY_NFY_COND_CONFIRM_FILE_REPLACE == e_copy_cond)
    {
        pt_confm->b_replace_existing_file = TRUE;
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_pp_do_ratate
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_set_do_picture_frame_photo(VOID*  pv_tag)
{
    INT32                       i4_ret = -1;
#ifdef MMP_PP_ACTION_SELECT_EXIT
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;
#endif
    CHAR                        s_buf[MMP_PP_RC_STR_MAX_LEN + 1];
    SIZE_T                      z_buf_size = MMP_PP_RC_STR_MAX_LEN + 1;
    HANDLE_T                    h_handle = NULL_HANDLE;

#ifdef MMP_PP_ACTION_SELECT_EXIT
    i4_ret = a_optl_hide(pt_this->t_view.h_optl);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_optl_hide fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_focus fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
#endif

    i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                             MMP_PE_EXTRA_INFO_ID_PATH,
                                             &z_buf_size,
                                             (VOID*)s_buf);
    IS_MMPR_OK(i4_ret);

    if(MMP_PF_HAS_INTERNAL_FALSH())
    {
        i4_ret = c_fm_async_copy_file(NULL_HANDLE,
                                      s_buf,
                                      NULL_HANDLE,
                                      MMP_USER_PHOTO_FRAME_NAME,
                                      _mmp_pp_fm_copy_nfy,
                                      NULL,
                                      &h_handle);
        IS_MMPR_OK(i4_ret);
    }
    else
    {
       // mmp_ph_set_user_frame(s_buf, z_buf_size);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_pp_do_ratate
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_do_ratate(VOID* pv_tag)
{
    INT32                       i4_ret  = -1;
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;

#ifdef MMP_PP_ACTION_SELECT_EXIT
    i4_ret = a_optl_hide(pt_this->t_view.h_optl);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_optl_hide fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_focus fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
#endif

    if( FALSE == pt_this->b_is_notsupport_show )  /* If not support, don't apply rotate */
    {
        i4_ret = _mmp_pp_view_rotate_right(pt_this);
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_get_duration
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_get_duration(VOID* pv_tag, UINT16* pui2_dur_idx)
{
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;

    *pui2_dur_idx = (UINT16)pt_this->ui4_dur_idx;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_do_duration
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_do_duration(VOID* pv_tag)
{
    INT32                    i4_ret      = -1;
    UINT32                   ui4_dua_idx = (UINT32)pv_tag;
    _MMP_PP_DATA_MEMBER_T*   pt_this = &t_g_pp;

    if(ui4_dua_idx >= MMP_PP_RC_DLB_ELEM_COUNT)
    {
        return MMPR_INV_ARG;
    }

    pt_this->ui4_dur_idx = ui4_dua_idx;

    _mmp_pp_view_do_duration( pt_this, pt_this->ui4_dur_idx );

#ifdef MMP_PP_ACTION_SELECT_EXIT
    i4_ret = a_optl_hide(pt_this->t_view.h_optl);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_optl_hide fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_focus fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
#endif

    i4_ret = c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_repaint fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_get_effect
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_get_effect(VOID* pv_tag, UINT16* pui2_eft_idx)
{
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;

    *pui2_eft_idx = (UINT16)pt_this->ui4_tfx_idx;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_do_effect
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_do_effect(VOID* pv_tag)
{
    INT32                    i4_ret      = -1;
    UINT32                   ui4_eft_idx = (UINT32)pv_tag;
    _MMP_PP_DATA_MEMBER_T*   pt_this     = &t_g_pp;

    if(ui4_eft_idx >= MMP_PP_RC_TLB_ELEM_COUNT)
    {
        return MMPR_INV_ARG;
    }

    pt_this->ui4_tfx_idx = ui4_eft_idx;

    _mmp_pp_view_do_effect( pt_this, pt_this->ui4_tfx_idx );

#ifdef MMP_PP_ACTION_SELECT_EXIT
    i4_ret = a_optl_hide(pt_this->t_view.h_optl);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_optl_hide fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_focus fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
#endif

    i4_ret = c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_repaint fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_get_zoom
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_get_zoom(VOID* pv_tag, UINT16* pui2_zom_idx)
{
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;

    *pui2_zom_idx = (UINT16)pt_this->ui4_zoom_idx;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_do_zoom
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_do_zoom(VOID* pv_tag)
{
    INT32                    i4_ret      = -1;
    UINT32                   ui4_zom_idx = (UINT32)pv_tag;
    UINT32                   ui4_old_zom = 0;
    _MMP_PP_DATA_MEMBER_T*   pt_this     = &t_g_pp;

#ifdef MMP_PP_ACTION_SELECT_EXIT
    i4_ret = a_optl_hide(pt_this->t_view.h_optl);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_optl_hide fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_focus fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
#endif

    if(pt_this->b_is_notsupport_show)
    {
        return MMPR_OK;
    }

    ui4_old_zom = pt_this->ui4_zoom_idx;

    if(MMP_PP_RC_IS_QUICK_ROTATE())
    {
        if(ui4_zom_idx >= MMP_PP_RC_ZLB_ELEM_COUNT)
        {
            return MMPR_INV_ARG;
        }

        pt_this->ui4_zoom_idx = ui4_zom_idx;

        i4_ret = _mmp_pp_view_do_zoom( pt_this, pt_this->ui4_zoom_idx );

        if( i4_ret >= 0 )  /* Zoom Successfully */
        {
            c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
        }
        else
        {
            /* Zoom fail, we should roll back the increment of zoom index */
            pt_this->ui4_zoom_idx = ui4_old_zom;

            MMP_DBG_ERROR(("_mmp_pp_view_do_zoom fail. i4_ret = %d.\r\n", i4_ret));
        }
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_get_repeat
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_get_repeat(VOID* pv_tag, UINT16* pui2_repeat_idx)
{
    SIZE_T                      z_size;
    MMP_REPEAT_MODE_T           e_repeat_mode;

    z_size = sizeof(MMP_REPEAT_MODE_T);
    mmp_mc_list_get_attr(MMP_PL_ATTR_ID_FG_REPEAT, &z_size, &e_repeat_mode);

    switch(e_repeat_mode)
    {
        case MMP_REPEAT_MODE_NONE:
            *pui2_repeat_idx = 0;
            break;
        case MMP_REPEAT_MODE_ONE:
            *pui2_repeat_idx = 1;
            break;
        case MMP_REPEAT_MODE_ALL:
            *pui2_repeat_idx = 2;
            break;
        default:
            return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_do_repeat
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_do_repeat(VOID* pv_tag)
{
    INT32                    i4_ret      = -1;
    UINT32                   ui4_rp_idx  = (UINT32)pv_tag;
    _MMP_PP_DATA_MEMBER_T*   pt_this     = &t_g_pp;
    MMP_PL_ATTR_T            at_attr[2] ;
    MMP_REPEAT_MODE_T        e_repeat_mode;

    if(ui4_rp_idx >= MMP_PP_RC_RP_LB_ELEM_COUNT)
    {
        return MMPR_INV_ARG;
    }

    switch(ui4_rp_idx)
    {
        case 0:
            e_repeat_mode = MMP_REPEAT_MODE_NONE;
            break;
        case 1:
            e_repeat_mode = MMP_REPEAT_MODE_ONE;
            break;
        case 2:
            e_repeat_mode = MMP_REPEAT_MODE_ALL;
            break;
        default:
            return MMPR_INV_ARG;
    }

#ifdef MMP_PP_ACTION_SELECT_EXIT
    i4_ret = a_optl_hide(pt_this->t_view.h_optl);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_optl_hide fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_focus fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
#endif

    at_attr[0].e_id = MMP_PL_ATTR_ID_FG_REPEAT;
    at_attr[0].pv_param = (VOID*)e_repeat_mode;
    at_attr[1].e_id = MMP_PL_ATTR_ID_FG_SHUFFLE;
    at_attr[1].pv_param = (VOID*)(pt_this->e_shuffle_mode);

    i4_ret = mmp_mc_list_set_attr(2,at_attr);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_mc_list_set_attr fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    pt_this->e_repeat_mode = e_repeat_mode;

    _mmp_pp_view_update_repeat_label(pt_this);

    i4_ret = c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_repaint fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_get_shuffle
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_get_shuffle(VOID* pv_tag, UINT16* pui2_shuffle_idx)
{
    SIZE_T                      z_size;
    MMP_SHUFFLE_MODE_T          e_shuffle_mode;

    z_size = sizeof(MMP_SHUFFLE_MODE_T);
    mmp_mc_list_get_attr(MMP_PL_ATTR_ID_FG_SHUFFLE, &z_size, &e_shuffle_mode);

    switch(e_shuffle_mode)
    {
        case MMP_SHUFFLE_MODE_SEQUENTIAL:
            *pui2_shuffle_idx = 0;
            break;
        case MMP_SHUFFLE_MODE_SHUFFLE:
            *pui2_shuffle_idx = 1;
            break;
        default:
            return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_do_shuffle
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_do_shuffle(VOID* pv_tag)
{
    INT32                    i4_ret      = -1;
    UINT32                   ui4_sf_idx  = (UINT32)pv_tag;
    _MMP_PP_DATA_MEMBER_T*   pt_this     = &t_g_pp;
    MMP_PL_ATTR_T            at_attr[2] ;
    MMP_SHUFFLE_MODE_T       e_shuffle_mode;

    if(ui4_sf_idx >= MMP_PP_RC_SF_LB_ELEM_COUNT)
    {
        return MMPR_INV_ARG;
    }

    switch(ui4_sf_idx)
    {
        case 0:
            e_shuffle_mode = MMP_SHUFFLE_MODE_SEQUENTIAL;
            break;
        case 1:
            e_shuffle_mode = MMP_SHUFFLE_MODE_SHUFFLE;
            break;
        default:
            return MMPR_INV_ARG;
    }

#ifdef MMP_PP_ACTION_SELECT_EXIT
    i4_ret = a_optl_hide(pt_this->t_view.h_optl);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_optl_hide fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_focus fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
#endif

    at_attr[0].e_id = MMP_PL_ATTR_ID_FG_REPEAT;
    at_attr[0].pv_param = (VOID*)(pt_this->e_repeat_mode);
    at_attr[1].e_id = MMP_PL_ATTR_ID_FG_SHUFFLE;
    at_attr[1].pv_param = (VOID*)e_shuffle_mode;

    i4_ret = mmp_mc_list_set_attr(2,at_attr);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_mc_list_set_attr fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    pt_this->e_shuffle_mode = e_shuffle_mode;

    _mmp_pp_view_update_shuffle_label(pt_this);

    i4_ret = c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_repaint fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

static INT32 _mmp_pp_opt_set_item (_MMP_LABEL_STATE_T t_label_state)
{
    OPTL_ITEM_DEF_T             t_optl_item_def = {0};
    OPTL_ITEM_T                 t_optl_item[7];
    OPTL_SUBITEM_T              t_sub_item_repeat[3];
    OPTL_SUBITEM_T              t_sub_item_shuffle[2];
    OPTL_SUBITEM_T              t_sub_item_duration[3];
    OPTL_SUBITEM_T              t_sub_item_zoom[3];
    OPTL_SUBITEM_T              t_sub_item_effect[MMP_PP_RC_TLB_ELEM_COUNT];
    UINT16                      ui4_index;
    UINT8                       ui1_cnt = 0;
    INT32                       i4_ret = -1;
    CHAR                        s_buf[MMP_PP_RC_STR_MAX_LEN + 1];
    SIZE_T                      z_buf_size = MMP_PP_RC_STR_MAX_LEN + 1;
    RMV_DEV_DEVICE_STATUS_T     e_dev_status = RMV_DEV_DEVICE_STATUS_UNSUPT_DEV;
    UINT16                      aui4_repeat_mlm[3] = {MLM_MMP_KEY_TLB_NONE,
                                                      MLM_MMP_KEY_VP_REPEAT_ONCE,
                                                      MLM_MMP_KEY_TB_REPEAT};
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;

    /*sub item repeat mode*/
    for(ui4_index = 0; ui4_index < 3; ui4_index++)
    {
        t_sub_item_repeat[ui4_index].pf_fct = _mmp_pp_do_repeat;
        t_sub_item_repeat[ui4_index].pv_tag = (VOID*)(UINT32)ui4_index;
        t_sub_item_repeat[ui4_index].pw2s_text =
                MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), aui4_repeat_mlm[ui4_index]);
    }

    /*sub item shuffle mode*/
    for(ui4_index = 0; ui4_index < 2; ui4_index++)
    {
        t_sub_item_shuffle[ui4_index].pf_fct = _mmp_pp_do_shuffle;
        t_sub_item_shuffle[ui4_index].pv_tag = (VOID*)(UINT32)ui4_index;
        if(0 == ui4_index)
        {
            t_sub_item_shuffle[ui4_index].pw2s_text =
                MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_AUD_OPT_SHUFF_OFF);
        }
        else
        {
            t_sub_item_shuffle[ui4_index].pw2s_text =
                MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_AUD_OPT_SHUFF_ON);
        }
    }

    /*sub item duration*/
    for(ui4_index = 0; ui4_index < 3; ui4_index++)
    {
        t_sub_item_duration[ui4_index].pf_fct    = _mmp_pp_do_duration;
        t_sub_item_duration[ui4_index].pv_tag    = (VOID*)(UINT32)ui4_index;
        t_sub_item_duration[ui4_index].pw2s_text =
                MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), (UINT16)MLM_MMP_KEY_DLB_S + ui4_index);
    }

    if(MMP_PP_RC_IS_QUICK_ROTATE())
    {
        /*sub item zoom*/
        for(ui4_index = 0; ui4_index < 3; ui4_index++)
        {
            t_sub_item_zoom[ui4_index].pf_fct    = _mmp_pp_do_zoom;
            t_sub_item_zoom[ui4_index].pv_tag    = (VOID*)(UINT32)ui4_index;
            t_sub_item_zoom[ui4_index].pw2s_text =
                    MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), (UINT16)MLM_MMP_KEY_ZLB_1 + ui4_index);

        }
    }

    /*sub item effect*/
    for(ui4_index = 0; ui4_index < (UINT16)MMP_PP_RC_TLB_ELEM_COUNT; ui4_index++)
    {
        t_sub_item_effect[ui4_index].pf_fct    = _mmp_pp_do_effect;
        t_sub_item_effect[ui4_index].pv_tag    = (VOID*)(UINT32)ui4_index;
        t_sub_item_effect[ui4_index].pw2s_text =
                MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), (UINT16)MLM_MMP_KEY_TLB_NONE + ui4_index);

    }

    /*item play pause*/
    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
    if(_MMP_LABEL_STATE_PLAY != t_label_state)
    {
        t_optl_item[ui1_cnt].pw2s_text =
            MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_TB_PLAY);
    }
    else
    {
        t_optl_item[ui1_cnt].pw2s_text =
            MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_TB_PAUSE);
    }

    t_optl_item[ui1_cnt].u.t_action.pv_tag = NULL;
    t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_pp_play_pause;
    t_optl_item[ui1_cnt].b_is_disable = FALSE;
    ui1_cnt++;

    /*item repeat mode*/
    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
    t_optl_item[ui1_cnt].pw2s_text =
        MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_TB_REPEAT);
    t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = 3;
    t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_repeat;
    t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_pp_get_repeat;
    t_optl_item[ui1_cnt].b_is_disable = FALSE;
    ui1_cnt++;

    /*item shuffle mode*/
    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
    t_optl_item[ui1_cnt].pw2s_text =
        MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_TB_SHUFFLE);
    t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = 2;
    t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_shuffle;
    t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_pp_get_shuffle;
    t_optl_item[ui1_cnt].b_is_disable = FALSE;
    ui1_cnt++;

    /*item duration/rotate*/
    if(_MMP_LABEL_STATE_PLAY != t_label_state)
    {
        t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
        t_optl_item[ui1_cnt].pw2s_text =
            MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_TB_ROT);
        t_optl_item[ui1_cnt].u.t_action.pv_tag = NULL;
        t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_pp_do_ratate;
    }
    else
    {
        t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
        t_optl_item[ui1_cnt].pw2s_text =
            MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_TB_DURATION);
        t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = 3;
        t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_duration;
        t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_pp_get_duration;
    }
    t_optl_item[ui1_cnt].b_is_disable = FALSE;
    ui1_cnt++;

    /*item zoom/effect*/
    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
    if(_MMP_LABEL_STATE_PLAY != t_label_state)
    {
        if(MMP_PP_RC_IS_QUICK_ROTATE())
        {
            t_optl_item[ui1_cnt].pw2s_text =
                MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_TB_ZOM);
            t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = 3;
            t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_zoom;
            t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_pp_get_zoom;
            t_optl_item[ui1_cnt].b_is_disable = FALSE;
            ui1_cnt++;
        }
    }
    else
    {
        t_optl_item[ui1_cnt].pw2s_text =
            MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_TB_EFFECT);
        t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = (UINT16)MMP_PP_RC_TLB_ELEM_COUNT;
        t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_effect;
        t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_pp_get_effect;
        t_optl_item[ui1_cnt].b_is_disable = FALSE;
        ui1_cnt++;
    }

    /*item show/hide info*/
    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
    if(_MMP_INFO_STATE_SIMPLE == pt_this->e_info_state)
    {
        t_optl_item[ui1_cnt].pw2s_text =
            MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_AUD_OPT_SHOW_INFO);
    }
    else
    {
        t_optl_item[ui1_cnt].pw2s_text =
            MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_AUD_OPT_HIDE_INFO);
    }

    t_optl_item[ui1_cnt].u.t_action.pv_tag = NULL;
    t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_pp_show_hide_info;
    t_optl_item[ui1_cnt].b_is_disable = FALSE;
    ui1_cnt++;

    i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                             MMP_PE_EXTRA_INFO_ID_PATH,
                                             &z_buf_size,
                                             (VOID*)s_buf);
    IS_MMPR_OK(i4_ret);

    i4_ret = a_rmv_dev_get_mnt_point_status_by_path(s_buf, &e_dev_status);
    IS_MMPR_OK(i4_ret);

    if (RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
    {
    }
    else if(RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))
    {
    }
    else
    {
        /**/
        t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
        t_optl_item[ui1_cnt].pw2s_text =
            MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PP_PHOTO_FRAME);
        t_optl_item[ui1_cnt].u.t_action.pv_tag = NULL;
        t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_pp_set_do_picture_frame_photo;
        t_optl_item[ui1_cnt].b_is_disable = FALSE;
        ui1_cnt++;
    }

    /*main item 7*/
    t_optl_item_def.pt_opt_item = t_optl_item;
    t_optl_item_def.ui2_num_of_opt_items = ui1_cnt;

    a_optl_set_option_items(pt_this->t_view.h_optl,
                 &t_optl_item_def);
    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_play_nfy_cb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pp_play_nfy_cb(
    VOID*                       pv_tag,
    UINT32                      ui4_ver,
    MMP_PE_PLAY_NFY_ID_T        e_nfy_id,
    VOID*                       pv_nfy_param)
{
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;
    MMP_FP_SHOW_NFY_ID_T        e_id = MMP_FP_SHOW_NFY_ID_LAST_ENTRY;
    VOID*                       pv_param = NULL;
    BOOL                        b_nfy = TRUE;
    INT32                       i4_ret;
    SIZE_T                      z_buf_size;
    SIZE_T                      z_size = MMP_PP_RC_STR_MAX_LEN + 1;
    BOOL                        b_can_decoded = FALSE;
    BOOL                        b_is_bad_head = TRUE;
    BOOL                        b_file_not_exist = FALSE;
    BOOL                        b_is_removed = FALSE;
    MMP_PP_MSGBOX_TYPE_T        t_msg_type    = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;

    DBG_LOG_PRINT(("[MMP][%s %d] show cmd <=%s=> \n",__FUNCTION__,__LINE__,PE_FILE_STATE(e_nfy_id)));
    switch(e_nfy_id)
    {
    case MMP_PE_PLAY_NFY_ID_OPEN_RESULT:        /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
        e_id = MMP_FP_SHOW_NFY_ID_OPEN_RESULT;
        pv_param = pv_nfy_param;
        break;

    case MMP_PE_PLAY_NFY_ID_CLOSE_RESULT:       /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
        e_id = MMP_FP_SHOW_NFY_ID_CLOSE_RESULT;
        pv_param = pv_nfy_param;
        break;

    case MMP_PE_PLAY_NFY_ID_START_RESULT:       /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
        {
            CHAR     s_buf[MMP_PP_RC_STR_MAX_LEN + 1];
            UTF16_T  ws_buf[MMP_PP_RC_STR_MAX_LEN + 12];

            e_id = MMP_FP_SHOW_NFY_ID_START_RESULT;
            pv_param = pv_nfy_param;

            /* [DTV00208322] */
            /* Some files can be opened but can't be deocded */
            /* check current file can be decode or not here */
            z_buf_size = sizeof(BOOL);
            i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                     MMP_PE_EXTRA_INFO_ID_IS_SUPPORTED,
                                                     &z_buf_size,
                                                     &b_can_decoded);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_READY) fail. i4_ret = %d.\r\n", i4_ret));

                b_can_decoded = TRUE;
            }

        #if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
            if (a_mmp_dmr_is_active())
            {
                if (b_can_decoded)
                {
                    c_dmr_submit_player_status(
                                PLAYER_MEDIATYPE_PHOTO,
                                PLAYER_NFYCODE_PHOTO_PLAYED
                                );
                }
                else
                {
                    c_dmr_submit_player_status(
                                PLAYER_MEDIATYPE_PHOTO,
                                PLAYER_NFYCODE_FILE_NOT_SUPPORT
                                );
                }
            }
        #endif

            /* If not support, show not support text */
            if( FALSE == b_can_decoded )
            {
                 /*check if the device is removed. If yes, don't show message*/
        z_buf_size = sizeof(BOOL);
                i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                         MMP_PE_EXTRA_INFO_ID_IS_REMOVED,
                                                         &z_buf_size,
                                                         &b_is_removed);
                if(MMPR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_REMOVED) fail. i4_ret = %d.\r\n", i4_ret));

                    b_is_removed = FALSE;
                }

                if(FALSE == b_is_removed) /*not caused by unplugging devices*/
                {

                    /* Reset hide timer to show the notify */
                   // _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                    if(_MMP_INFO_STATE_NONE == pt_this->e_info_state)
                    {
                        _mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_SIMPLE);
                    }

                    z_buf_size = sizeof(BOOL);
                    i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                             MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST,
                                                             &z_buf_size,
                                                             &b_file_not_exist);
                    if(MMPR_OK != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST) fail. i4_ret = %d.\r\n", i4_ret));

                        b_file_not_exist = TRUE;
                    }

                    if(b_file_not_exist)
                    {
                        t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_EXIST;
                    }
                    else
                    {

                    z_buf_size = sizeof(BOOL);
                        i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                                 MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER,
                                                                 &z_buf_size,
                                                                 &b_is_bad_head);
                        if(MMPR_OK != i4_ret)
                        {
                            MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER) fail. i4_ret = %d.\r\n", i4_ret));

                            b_is_bad_head = FALSE;
                        }


                        if(b_is_bad_head)
                        {
                            BOOL    b_meet_all = FALSE;

                            z_buf_size = sizeof(BOOL);
                            i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                                         MMP_PE_EXTRA_INFO_ID_IS_MEET_LIMITATION,
                                                                         &z_buf_size,
                                                                         &b_meet_all);

                            if(IMGR_OK != i4_ret)
                            {
                                MMP_DBG_ERROR(("c_img_get_info(IMG_INFO_THUMBNAIL_MEET_ALL_LIMITATION) failed. i4_ret = %d.\r\n", i4_ret));
                            t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;

                            }


                            if(FALSE == b_meet_all)
                            {
                                t_msg_type = MMP_PP_MSGBOX_TYPE_RESOLUTION_NOT_SUPPORT;
                            }

                            else
                            {
                                t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;
                            }

                        }
                        else
                        {
                            t_msg_type = MMP_PP_MSGBOX_TYPE_DECODE_FAIL;
                        }
                    }


                    if(pt_this->b_pp_view_active)
                    {
                        i4_ret = _mmp_pp_view_open_msgbox(t_msg_type);
                        if(WGLR_OK != i4_ret)
                        {
                                MMP_DBG_ERROR(("_mmp_pp_view_open_msgbox fail. i4_ret = %d.\r\n", i4_ret));
                                return;
                        }
                        i4_ret = mmp_pe_play_get_file_info(MMP_PE_FILE_IDX_CURRENT,
                                   MMP_FP_INFO_TYPE_TITLE,
                                   &z_size,
                                   (UINT8*)s_buf);

                        if(MMPR_OK != i4_ret)
                        {
                            if(MMPR_NO_DATA != i4_ret)
                            {
                                MMP_DBG_ERROR(("mmp_pe_play_get_file_info() fail. i4_ret = %d.\r\n", i4_ret));
                            }
                        }

                        z_buf_size = c_strlen(s_buf);
                        s_buf[z_buf_size] = 0;
                        c_uc_ps_to_w2s(s_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);

                        i4_ret = c_wgl_do_cmd (pt_this->t_view.h_not_show_file_title,
                                                WGL_CMD_TEXT_SET_TEXT,
                                                WGL_PACK(ws_buf),
                                                WGL_PACK(c_uc_w2s_strlen(ws_buf)));
                        MMPR_LOG_ON_FAIL(i4_ret);
                        c_wgl_show(pt_this->t_view.h_not_show_file_title,WGL_SW_RECURSIVE);
                    }
                    else
                    {
                        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                                    _mmp_pp_view_broadcast_file_msg,
                                                    NULL,
                                                    NULL,
                                                    NULL,
                                                    NULL);
                    }
                }
            }

            /*update status icon*/
            if(pv_nfy_param && FALSE == ((MMP_FP_SHOW_NFY_COMMON_PARAM_T*)pv_nfy_param)->b_result)
            {
                _mmp_pp_view_update_play_status(pt_this, MMP_PLAY_STATE_STOPPED);
            }


        }
        break;

    case MMP_PE_PLAY_NFY_ID_RES_BUSY:
        {
            CHAR     s_buf[MMP_PP_RC_STR_MAX_LEN + 1];

            z_buf_size = MMP_PP_RC_STR_MAX_LEN + 1;
            i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_NEXT,
                                                         MMP_PE_EXTRA_INFO_ID_PATH,
                                                         &z_buf_size,
                                                         (VOID*)s_buf);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info() failed. i4_ret = %d.\r\n", i4_ret));
            }

            i4_ret = mmp_pe_play_next_preload(s_buf);
            if(MMPR_OK != i4_ret && MMPR_IS_PRELOADED != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_pe_play_next_preload() failed. i4_ret = %d.\r\n", i4_ret));
            }
        }
        return;

    case MMP_PE_PLAY_NFY_ID_PAUSE_RESULT:       /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
        e_id = MMP_FP_SHOW_NFY_ID_PAUSE_RESULT;
        pv_param = pv_nfy_param;
        break;

    case MMP_PE_PLAY_NFY_ID_STOP_RESULT:        /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
        e_id = MMP_FP_SHOW_NFY_ID_STOP_RESULT;
        pv_param = pv_nfy_param;
        break;

    case MMP_PE_PLAY_NFY_ID_PRELOAD_RESULT:     /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/
        e_id = MMP_FP_SHOW_NFY_ID_PRELOAD_RESULT;
        pv_param = pv_nfy_param;
        break;

    case MMP_PE_PLAY_NFY_ID_NEXT_RESULT:        /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
        e_id = MMP_FP_SHOW_NFY_ID_NEXT_RESULT;
        pv_param = pv_nfy_param;

        /* [DTV00208322] */
        /* Some files can be opened but can't be deocded */
        /* check current file can be decode or not here */
        z_buf_size = sizeof(BOOL);
        i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                 MMP_PE_EXTRA_INFO_ID_IS_SUPPORTED,
                                                 &z_buf_size,
                                                 &b_can_decoded);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_READY) fail. i4_ret = %d.\r\n", i4_ret));

            b_can_decoded = TRUE;
        }

        /* If not support, show not support text */
        if( FALSE == b_can_decoded )
        {
            CHAR     s_buf[MMP_PP_RC_STR_MAX_LEN + 1];
            UTF16_T  ws_buf[MMP_PP_RC_STR_MAX_LEN + 12];
            /*check if the device is removed. If yes, don't show message*/
            i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                     MMP_PE_EXTRA_INFO_ID_IS_REMOVED,
                                                     &z_buf_size,
                                                     &b_is_removed);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_REMOVED) fail. i4_ret = %d.\r\n", i4_ret));

                b_is_removed = FALSE;
            }

            if(FALSE == b_is_removed) /*not caused by unplugging devices*/
            {
                /* Reset hide timer to show the notify */
                //_mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                if(_MMP_INFO_STATE_NONE == pt_this->e_info_state)
                {
                    _mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_SIMPLE);
                }

                z_buf_size = sizeof(BOOL);
                i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                         MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST,
                                                         &z_buf_size,
                                                         &b_file_not_exist);
                if(MMPR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST) fail. i4_ret = %d.\r\n", i4_ret));

                    b_file_not_exist = TRUE;
                }

                if(b_file_not_exist)
                {
                    t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_EXIST;
                }
                else
            {
                    i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                             MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER,
                                                             &z_buf_size,
                                                             &b_is_bad_head);
                    if(MMPR_OK != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER) fail. i4_ret = %d.\r\n", i4_ret));

                        b_is_bad_head = FALSE;
                    }

                    if(b_is_bad_head)
                    {
                        BOOL    b_meet_all = FALSE;

                        z_buf_size = sizeof(BOOL);
                        i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                                     MMP_PE_EXTRA_INFO_ID_IS_MEET_LIMITATION,
                                                                     &z_buf_size,
                                                                     &b_meet_all);

                        if(IMGR_OK != i4_ret)
                        {
                            MMP_DBG_ERROR(("c_img_get_info(IMG_INFO_THUMBNAIL_MEET_ALL_LIMITATION) failed. i4_ret = %d.\r\n", i4_ret));
                            t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;

                        }

                        if(FALSE == b_meet_all)
                        {
                            t_msg_type = MMP_PP_MSGBOX_TYPE_RESOLUTION_NOT_SUPPORT;
                        }

                        else
                        {
                        t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;
                    }
                    }
                    else
                    {
                        t_msg_type = MMP_PP_MSGBOX_TYPE_DECODE_FAIL;
                    }
            }

                i4_ret = _mmp_pp_view_open_msgbox(t_msg_type);
                if(WGLR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("_mmp_pp_view_open_msgbox fail. i4_ret = %d.\r\n", i4_ret));
                    return;
                }

                i4_ret = mmp_pe_play_get_file_info(MMP_PE_FILE_IDX_CURRENT,
                                                   MMP_FP_INFO_TYPE_TITLE,
                                                   &z_size,
                                                   (UINT8*)s_buf);
                if(MMPR_OK != i4_ret)
                {
                    if(MMPR_NO_DATA != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_pe_play_get_file_info() fail. i4_ret = %d.\r\n", i4_ret));
                    }
            }

                z_buf_size = c_strlen(s_buf);
                s_buf[z_buf_size] = 0;
                c_uc_ps_to_w2s(s_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);

                i4_ret = c_wgl_do_cmd (pt_this->t_view.h_not_show_file_title,
                                        WGL_CMD_TEXT_SET_TEXT,
                                        WGL_PACK(ws_buf),
                                        WGL_PACK(c_uc_w2s_strlen(ws_buf)));
                MMPR_LOG_ON_FAIL(i4_ret);
                c_wgl_show(pt_this->t_view.h_not_show_file_title,WGL_SW_RECURSIVE);
            }
            }
        else
        {
            _mmp_pp_view_close_msgbox();
            c_wgl_show(pt_this->t_view.h_not_show_file_title,WGL_SW_HIDE_RECURSIVE);
        }
        break;

    case MMP_PE_PLAY_NFY_ID_PLAY_END:           /*pv_nfy_param: NULL. Play is completed.*/
        e_id = MMP_FP_SHOW_NFY_ID_PLAY_END;
        pv_param = pv_nfy_param;

        /* Hide not support text */
        _mmp_pp_view_close_msgbox();
        c_wgl_show(pt_this->t_view.h_not_show_file_title,WGL_SW_HIDE);
        {
           mmp_mc_list_next(MMP_GROUND_MODE_FORE);
        }
    #if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
        if (a_mmp_dmr_is_active())
        {
            c_dmr_submit_player_status(
                        PLAYER_MEDIATYPE_PHOTO,
                        PLAYER_NFYCODE_END_OF_MEDIA
                        );
        }
    #endif
        break;

    case MMP_PE_PLAY_NFY_ID_ROTATE_RESULT:      /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/
        b_nfy = FALSE;
        break;

    case MMP_PE_PLAY_NFY_ID_ZOOM_RESULT:        /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/
        b_nfy = FALSE;
        break;

    case MMP_PE_PLAY_NFY_ID_LOAD_RESULT:        /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/

            e_id = MMP_FP_SHOW_NFY_ID_START_RESULT;
            pv_param = pv_nfy_param;

            /* [DTV00208322] */
            /* Some files can be opened but can't be deocded */
            /* check current file can be decode or not here */
            z_buf_size = sizeof(BOOL);
            i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                     MMP_PE_EXTRA_INFO_ID_IS_SUPPORTED,
                                                     &z_buf_size,
                                                     &b_can_decoded);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_READY) fail. i4_ret = %d.\r\n", i4_ret));

                b_can_decoded = TRUE;
            }

            /* If not support, show not support text */
            if( FALSE == b_can_decoded)
            {
                 /*check if the device is removed. If yes, don't show message*/
                z_buf_size = sizeof(BOOL);
                i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                         MMP_PE_EXTRA_INFO_ID_IS_REMOVED,
                                                         &z_buf_size,
                                                         &b_is_removed);
                if(MMPR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_REMOVED) fail. i4_ret = %d.\r\n", i4_ret));

                    b_is_removed = FALSE;
                }

                if(FALSE == b_is_removed) /*not caused by unplugging devices*/
                {

                    /* Reset hide timer to show the notify */
                   // _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                    if(_MMP_INFO_STATE_NONE == pt_this->e_info_state)
                    {
                        _mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_SIMPLE);
                    }

                    z_buf_size = sizeof(BOOL);
                    i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                             MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST,
                                                             &z_buf_size,
                                                             &b_file_not_exist);
                    if(MMPR_OK != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST) fail. i4_ret = %d.\r\n", i4_ret));

                        b_file_not_exist = TRUE;
                    }

                    if(b_file_not_exist)
                    {
                        t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_EXIST;
                    }
                    else
                    {

                    z_buf_size = sizeof(BOOL);
                        i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                                 MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER,
                                                                 &z_buf_size,
                                                                 &b_is_bad_head);
                        if(MMPR_OK != i4_ret)
                        {
                            MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER) fail. i4_ret = %d.\r\n", i4_ret));

                            b_is_bad_head = FALSE;
                        }

                        if(b_is_bad_head)
                        {
                            BOOL    b_meet_all = FALSE;

                            z_buf_size = sizeof(BOOL);
                            i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                                         MMP_PE_EXTRA_INFO_ID_IS_MEET_LIMITATION,
                                                                         &z_buf_size,
                                                                         &b_meet_all);

                            if(IMGR_OK != i4_ret)
                            {
                                MMP_DBG_ERROR(("c_img_get_info(IMG_INFO_THUMBNAIL_MEET_ALL_LIMITATION) failed. i4_ret = %d.\r\n", i4_ret));
                            t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;

                            }

                            if(FALSE == b_meet_all)
                            {
                                t_msg_type = MMP_PP_MSGBOX_TYPE_RESOLUTION_NOT_SUPPORT;
                            }

                            else
                            {
                                t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;
                            }
                        }
                        else
                        {
                            t_msg_type = MMP_PP_MSGBOX_TYPE_DECODE_FAIL;
                        }
                    }

                    if(pt_this->b_pp_view_active)
                    {
                        i4_ret = _mmp_pp_view_open_msgbox(t_msg_type);
                        if(WGLR_OK != i4_ret)
                        {
                                MMP_DBG_ERROR(("_mmp_pp_view_open_msgbox fail. i4_ret = %d.\r\n", i4_ret));
                                return;
                        }
                    }
                    else
                    {
                        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                                    _mmp_pp_view_broadcast_file_msg,
                                                    NULL,
                                                    NULL,
                                                    NULL,
                                                    NULL);
                    }
                }
            }

            /*update status icon*/
            /*
            if(pv_nfy_param && FALSE == ((MMP_FP_SHOW_NFY_COMMON_PARAM_T*)pv_nfy_param)->b_result)
            {
                _mmp_pp_view_update_play_status(pt_this, MMP_PLAY_STATE_STOPPED);
            }
            */


            //************************************************

        /* Some files can be opened but can't be deocded */
        /* check current file can be decode or not here */
        z_buf_size = sizeof(BOOL);
        i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                 MMP_PE_EXTRA_INFO_ID_IS_SUPPORTED,
                                                 &z_buf_size,
                                                 &b_can_decoded);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_READY) fail. i4_ret = %d.\r\n", i4_ret));

            b_can_decoded = TRUE;
        }

        /* If not support, show not support text */
        if( FALSE == b_can_decoded )
        {
            CHAR     s_buf[MMP_PP_RC_STR_MAX_LEN + 1];
            UTF16_T  ws_buf[MMP_PP_RC_STR_MAX_LEN + 12];
            /*check if the device is removed. If yes, don't show message*/
            i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                     MMP_PE_EXTRA_INFO_ID_IS_REMOVED,
                                                     &z_buf_size,
                                                     &b_is_removed);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_REMOVED) fail. i4_ret = %d.\r\n", i4_ret));

                b_is_removed = FALSE;
            }

            if(FALSE == b_is_removed) /*not caused by unplugging devices*/
            {
                /* Reset hide timer to show the notify */
                //_mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                if(_MMP_INFO_STATE_NONE == pt_this->e_info_state)
                {
                    _mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_SIMPLE);
                }

                z_buf_size = sizeof(BOOL);
                i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                         MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST,
                                                         &z_buf_size,
                                                         &b_file_not_exist);
                if(MMPR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST) fail. i4_ret = %d.\r\n", i4_ret));

                    b_file_not_exist = TRUE;
                }

                if(b_file_not_exist)
                {
                    t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_EXIST;
                }
                else
                {
                    i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                             MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER,
                                                             &z_buf_size,
                                                             &b_is_bad_head);
                    if(MMPR_OK != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER) fail. i4_ret = %d.\r\n", i4_ret));

                        b_is_bad_head = FALSE;
                    }

                    if(b_is_bad_head)
                    {
                        t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;
                    }
                    else
                    {
                        t_msg_type = MMP_PP_MSGBOX_TYPE_DECODE_FAIL;
                    }
                }

                i4_ret = _mmp_pp_view_open_msgbox(t_msg_type);
                if(WGLR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("_mmp_pp_view_open_msgbox fail. i4_ret = %d.\r\n", i4_ret));
                    return;
                }

                i4_ret = mmp_pe_play_get_file_info(MMP_PE_FILE_IDX_CURRENT,
                                                   MMP_FP_INFO_TYPE_TITLE,
                                                   &z_size,
                                                   (UINT8*)s_buf);
                if(MMPR_OK != i4_ret)
                {
                    if(MMPR_NO_DATA != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_pe_play_get_file_info() fail. i4_ret = %d.\r\n", i4_ret));
                    }
                }
                MMPR_LOG_ON_FAIL(i4_ret);
                z_buf_size = c_strlen(s_buf);
                s_buf[z_buf_size] = 0;
                c_uc_ps_to_w2s(s_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
                i4_ret = c_wgl_do_cmd (pt_this->t_view.h_not_show_file_title,
                                        WGL_CMD_TEXT_SET_TEXT,
                                        WGL_PACK(ws_buf),
                                        WGL_PACK(c_uc_w2s_strlen(ws_buf)));
                MMPR_LOG_ON_FAIL(i4_ret);

                c_wgl_show(pt_this->t_view.h_not_show_file_title,WGL_SW_RECURSIVE);
            }
        }
        b_nfy = FALSE;
        break;

    default:
        MMP_ASSERT(0);
    }

    if(b_nfy && pt_this->pf_nfy)
    {
        MMP_ASSERT(MMP_FP_SHOW_NFY_ID_LAST_ENTRY != e_id);

        pt_this->pf_nfy(pt_this->pv_nfy_tag, ui4_ver, e_id, pv_param);
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_init(
    _MMP_PP_DATA_MEMBER_T*      pt_this)
{
#ifndef MMP_GUI_AUTHORING_DP
    MMP_COM_UI_DETAIL_ELEM_PARAM_T  at_elem_param[MMP_PP_RC_DP_LBL_COUNT];
    GL_RECT_T                       t_detail_pg_rect = {FRM_PP_DETAIL_X, FRM_PP_DETAIL_Y, FRM_PP_DETAIL_X + FRM_PP_DETAIL_W, FRM_PP_DETAIL_Y + FRM_PP_DETAIL_H};
    INT32                           i;
#endif
    GL_RECT_T                       t_rect = {MMP_PP_RC_MAIN_X, MMP_PP_RC_MAIN_Y, MMP_PP_RC_MAIN_X + MMP_PP_RC_MAIN_W, MMP_PP_RC_MAIN_Y + MMP_PP_RC_MAIN_H};
    HANDLE_T                        h_canvas;
    INT32                           i4_ret;

#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
    MMP_MC_PLAYER_SETTING_T  t_play_setting;
#endif
    WDK_ICON_WIDGET_PARAM_T          t_icon_param;
    WDK_ICON_WIDGET_PARAM_T             t_play_icon_param;
    WDK_ICON_WIDGET_PARAM_T             t_pause_icon_param;
    GL_COLOR_T                          at_color[]= {{255, {0}, {0}, {0}}};
    GL_COLOR_T                          at_color_txt[] = {{255, {128}, {128}, {128}}};
    WDK_TXT_WIDGET_PARAM_T              t_txt_param;
     HANDLE_T                           h_font = NULL_HANDLE;

    /*create timer for autohide*/
    i4_ret = c_timer_create(&pt_this->h_hide_timer);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_create() failed. i4_ret = %d.\r\n", i4_ret));
        pt_this->h_hide_timer = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*get canvas*/
    h_canvas = mmp_main_get_canvas();

    /*init image*/
    i4_ret = mmp_img_init();
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /*create main frame*/
    i4_ret = c_wgl_create_widget(h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _mmp_pp_view_main_frm_proc_fct,          /*default proc*/
                                 0,
                                 (VOID*)WGL_STL_GL_NO_BK,
                                 0,
                                 &pt_this->t_view.h_frame);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));

        pt_this->t_view.h_frame = NULL_HANDLE;
        return MMPR_FAIL;
    }

    do
    {
        /* skip icon */
        t_icon_param.h_parent             = pt_this->t_view.h_frame;
        t_icon_param.ui1_alpha            = 255;
        t_icon_param.b_visibility         = TRUE;
        t_icon_param.i4_x                 = MMP_PP_SKIP_ICON_X;
        t_icon_param.i4_y                 = MMP_PP_SKIP_ICON_Y;
        t_icon_param.i4_w                 = MMP_PP_SKIP_ICON_W;
        t_icon_param.i4_h                 = MMP_PP_SKIP_ICON_H;
        t_icon_param.ui4_style            = 0;
        t_icon_param.b_img_bk             = FALSE;
        t_icon_param.ui1_img_align_style  = WGL_AS_CENTER_CENTER;
        t_icon_param.t_img_param.h_disable= h_g_mmp_pop_up_exculde_htl_icon;
        t_icon_param.t_img_param.h_enable = h_g_mmp_pop_up_exculde_htl_icon;
        t_icon_param.t_img_param.h_highlight= h_g_mmp_pop_up_exculde_htl_icon;
        t_icon_param.pt_clr_bk            = NULL;
        t_icon_param.pf_wdgt_proc         = NULL;
        t_icon_param.ph_created_icon      = &pt_this->t_view.h_skip_icon;
        i4_ret = a_wdk_create_icon_widget (t_icon_param);
        if (i4_ret < WDKR_OK)
        {
           break;
        }

        /* play  icon */
        t_play_icon_param.h_parent             = pt_this->t_view.h_frame;
        t_play_icon_param.ui1_alpha            = 255;
        t_play_icon_param.b_visibility         = TRUE;
        t_play_icon_param.i4_x                 = MMP_PP_PLAY_ICON_X;
        t_play_icon_param.i4_y                 = MMP_PP_PLAY_ICON_Y;
        t_play_icon_param.i4_w                 = MMP_PP_PLAY_ICON_W;
        t_play_icon_param.i4_h                 = MMP_PP_PLAY_ICON_H;
        t_play_icon_param.ui4_style            = 0;
        t_play_icon_param.b_img_bk             = FALSE;
        t_play_icon_param.ui1_img_align_style  = WGL_AS_CENTER_CENTER;
        t_play_icon_param.t_img_param.h_disable= h_g_mmp_video_player_play_icon;
        t_play_icon_param.t_img_param.h_enable = h_g_mmp_video_player_play_icon;
        t_play_icon_param.t_img_param.h_highlight= h_g_mmp_video_player_play_icon;
        t_play_icon_param.pt_clr_bk            = at_color;
        t_play_icon_param.pf_wdgt_proc         = NULL;
        t_play_icon_param.ph_created_icon      = &pt_this->t_view.h_play_icon;
        i4_ret = a_wdk_create_icon_widget (t_play_icon_param);
        if (i4_ret < WDKR_OK)
        {
           break;
        }
        c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);


        /* pause  icon */
        t_pause_icon_param.h_parent             = pt_this->t_view.h_frame;
        t_pause_icon_param.ui1_alpha            = 255;
        t_pause_icon_param.b_visibility         = TRUE;
        t_pause_icon_param.i4_x                 = MMP_PP_PLAY_ICON_X;
        t_pause_icon_param.i4_y                 = MMP_PP_PLAY_ICON_Y;
        t_pause_icon_param.i4_w                 = MMP_PP_PLAY_ICON_W;
        t_pause_icon_param.i4_h                 = MMP_PP_PLAY_ICON_H;
        t_pause_icon_param.ui4_style            = 0;
        t_pause_icon_param.b_img_bk             = FALSE;
        t_pause_icon_param.ui1_img_align_style  = WGL_AS_CENTER_CENTER;
        t_pause_icon_param.t_img_param.h_disable= h_g_mmp_video_player_pause_icon;
        t_pause_icon_param.t_img_param.h_enable = h_g_mmp_video_player_pause_icon;
        t_pause_icon_param.t_img_param.h_highlight= h_g_mmp_video_player_pause_icon;
        t_pause_icon_param.pt_clr_bk            = at_color;
        t_pause_icon_param.pf_wdgt_proc         = NULL;
        t_pause_icon_param.ph_created_icon      = &pt_this->t_view.h_pause_icon;
        i4_ret = a_wdk_create_icon_widget (t_pause_icon_param);
        if (i4_ret < WDKR_OK)
        {
           break;
        }
        c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);

        i4_ret =  mmp_pop_up_photo_create_ui(pt_this->t_view.h_frame);
        IS_MMPR_OK(i4_ret);

        pt_this->e_play_state = _MMP_PLAY_STATE_NONE;



         /* Status text */

        t_txt_param.h_parent                    = pt_this->t_view.h_frame;
        t_txt_param.ui1_alpha                   = 255;
        t_txt_param.b_visibility                = TRUE;
        t_txt_param.i4_x                        = MMP_PP_INFO_BAR_STATUS_TXT_X;
        t_txt_param.i4_y                        = MMP_PP_INFO_BAR_STATUS_TXT_Y;
        t_txt_param.i4_w                        = MMP_PP_INFO_BAR_STATUS_TXT_W;
        t_txt_param.i4_h                        = MMP_PP_INFO_BAR_STATUS_TXT_H;
        t_txt_param.ui4_style                   = MMP_PP_INFO_BAR_STATUS_TXT_STYLE;
        t_txt_param.ps_font_name                = MMP_PP_INFO_BAR_STATUS_FONT_NAME;
        t_txt_param.e_font_size                 = MMP_PP_INFO_BAR_STATUS_FONT_SIZE;
        t_txt_param.e_font_style                = MMP_PP_INFO_BAR_STATUS_FONT_STYLE;
        t_txt_param.t_inset.i4_left             = MMP_PP_INFO_BAR_STATUS_TXT_INSET_LEFT;
        t_txt_param.t_inset.i4_right            = MMP_PP_INFO_BAR_STATUS_TXT_INSET_RIGHT;
        t_txt_param.t_inset.i4_top              = MMP_PP_INFO_BAR_STATUS_TXT_INSET_TOP;
        t_txt_param.t_inset.i4_bottom           = MMP_PP_INFO_BAR_STATUS_TXT_INSET_BOTTOM;
        t_txt_param.ui1_align                   = MMP_PP_INFO_BAR_STATUS_TXT_ALIGN;
        t_txt_param.b_img_bk                    = TRUE;
        t_txt_param.t_img_bk.h_disable          = NULL_HANDLE;
        t_txt_param.t_img_bk.h_enable           = NULL_HANDLE;
        t_txt_param.t_img_bk.h_highlight        = NULL_HANDLE;
        t_txt_param.pt_clr_txt                  = at_color_txt;
        t_txt_param.pt_hlt_clr_txt              = at_color_txt;
        t_txt_param.pt_dis_clr_txt              = at_color_txt;
        t_txt_param.pf_wdgt_proc                = NULL;
        t_txt_param.ph_created_txt              = &pt_this->t_view.h_not_show_file_title;

        i4_ret = a_wdk_create_txt_widget (t_txt_param);
        if (i4_ret < WDKR_OK)
        {
            return MMPR_FAIL;
        }

        /* set line gap */

        IS_MMPR_OK (c_wgl_do_cmd (pt_this->t_view.h_not_show_file_title,
                                  WGL_CMD_TEXT_SET_LINE_GAP,
                                  WGL_PACK ((INT32) MMP_PP_INFO_BAR_STATUS_TXT_LINE_GAP),
                                  NULL));


        /* font handle */

        i4_ret = c_fe_create_font(MMP_PP_INFO_BAR_STATUS_FONT_NAME,
                   MMP_PP_INFO_BAR_STATUS_FONT_SIZE,
                   MMP_PP_INFO_BAR_STATUS_FONT_STYLE,
                   FE_CMAP_ENC_UNICODE,
                   &h_font);
        if (i4_ret < FER_OK)
        {
            return MMPR_FAIL;
        }


        /*
        i4_ret = mmp_common_ui_toolbar_init(MMP_TB_PHOTO_PLAYER, pt_this->t_view.h_frame, &pt_ptb_inst);
        if (MMPR_OK != i4_ret)
        {
            pt_ptb_inst = NULL;
            break;
        }
        */

#ifdef MMP_GUI_AUTHORING_DP
        /*create detail page by xiangdong_ding 100318*/
        i4_ret = mmp_com_ui_create_detail_page_new(pt_this->t_view.h_frame, COM_UI_DTL_PG_PHOTO, (VOID*)&pt_pdp_inst);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_com_ui_create_detail_page_new() fail. i4_ret = %d.\r\n", i4_ret));
            pt_this->t_view.t_detailpage.h_page= NULL_HANDLE;
            break;
        }
#else

        /*create detail page*/
        c_memset(at_elem_param, 0, sizeof(at_elem_param));

        for(i = 0; i < MMP_PP_RC_DP_LBL_COUNT; i++)
        {
            MMP_PP_RC_DP_LBL_GET_SETTING((MMP_PP_RC_DP_LBL_ID_T)i, at_elem_param[i].t_rect, at_elem_param[i].ws_desc);
        }

        i4_ret = mmp_com_ui_create_detail_page(pt_this->t_view.h_frame,
                                               MMP_PP_RC_DP_LBL_COUNT,
                                               &t_detail_pg_rect,
                                               MMP_PP_RC_TEXT_STYLE,
                                               TRUE,
                                               at_elem_param,
                                               pt_this->t_view.t_detailpage.ah_label,
                                               &pt_this->t_view.t_detailpage.h_page);
        if(MMPR_OK != i4_ret)
        {
            pt_this->t_view.t_detailpage.h_page = NULL_HANDLE;
            break;
        }
#endif

        /* Initial file index */
        pt_this->ui4_current_fileidx = 0;
        pt_this->ui4_total_fileidx = 0;

        /* Initial tfx */
        pt_this->ui4_tfx_idx = 0;
        //_mmp_pp_view_do_effect( pt_this, pt_this->ui4_tfx_idx );

        /* Initial dur */
        pt_this->ui4_dur_idx = 0;
        _mmp_pp_view_do_duration( pt_this, pt_this->ui4_dur_idx );

        /* Initial zoom */
        pt_this->ui4_zoom_idx = 0;
        pt_this->e_label_state = _MMP_LABEL_STATE_PLAY;
        _mmp_pp_view_update_label( pt_this );

        i4_ret = _mmp_pp_view_create_optl(pt_this->t_view.h_frame,
                                          &(pt_this->t_view.h_optl));
        if(MMPR_OK != i4_ret)
        {
            break;
        }
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
        t_play_setting.ui4_mask = MMP_MC_PLYR_SETTING_MSK_DEF_FCS_WGT;
        t_play_setting.h_def_focus_widget = pt_this->t_view.h_frame;
        i4_ret = mmp_mc_set_player_setting(MMP_MEDIA_TYPE_PHOTO,
                                       &t_play_setting);
        if(MMPR_OK != i4_ret)
        {
            break;
        }
#endif
        return MMPR_OK;
    } while(0);

    _mmp_pp_view_deinit(pt_this);
    return MMPR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pp_view_deinit(
    _MMP_PP_DATA_MEMBER_T*      pt_this)
{

    /*free timer*/
    if(NULL_HANDLE != pt_this->h_hide_timer)
    {
        MMP_EXEC_WITH_ASSERT(c_timer_delete(pt_this->h_hide_timer), OSR_OK);

        pt_this->h_hide_timer = NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->t_view.h_optl)
    {
        MMP_EXEC_WITH_ASSERT(a_optl_destroy(pt_this->t_view.h_optl), WGLR_OK);

        pt_this->t_view.h_optl = NULL_HANDLE;;
    }

#ifdef MMP_GUI_AUTHORING_DP
        mmp_com_ui_dp_destroy(pt_pdp_inst);
#endif

#if 0
        mmp_common_ui_toolbar_deinit(pt_ptb_inst);
#endif

    if(NULL_HANDLE != pt_this->t_view.h_frame)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_destroy_widget(pt_this->t_view.h_frame), WGLR_OK);

        pt_this->t_view.h_frame = NULL_HANDLE;
    }

    mmp_pop_up_photo_destroy_ui();
    MMP_EXEC_WITH_ASSERT(mmp_img_deinit(), MMPR_OK);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_reset_info_hdlr
 *
 * Description: Update the file information in the info page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_reset_info_hdlr(VOID*    pv_info_hdlr_inst)
{
    INT32    i4_ret = -1;

    i4_ret = mmp_com_ui_fp_set_focus_info(pv_info_hdlr_inst,
                                          MMP_PP_FOCUS_INFO_ID_NAME,
                                          MMP_COM_UI_FP_DATA_W2S,
                                          (VOID*)NULL,
                                          FALSE);
    IS_MMPR_OK(i4_ret);
#if 0
    i4_ret = mmp_com_ui_fp_set_focus_info(pv_info_hdlr_inst,
                                          MMP_PP_FOCUS_INFO_ID_TIME,
                                          MMP_COM_UI_FP_DATA_W2S,
                                          (VOID*)NULL,
                                          FALSE);
    IS_MMPR_OK(i4_ret);
#endif

    i4_ret = mmp_com_ui_fp_set_focus_info(pv_info_hdlr_inst,
                                          MMP_PP_FOCUS_INFO_ID_RESLUTION,
                                          MMP_COM_UI_FP_DATA_W2S,
                                          (VOID*)NULL,
                                          FALSE);
    IS_MMPR_OK(i4_ret);

    i4_ret = mmp_com_ui_fp_set_focus_info(pv_info_hdlr_inst,
                                          MMP_PP_FOCUS_INFO_ID_SIZE,
                                          MMP_COM_UI_FP_DATA_W2S,
                                          (VOID*)NULL,
                                          FALSE);
    IS_MMPR_OK(i4_ret);

    i4_ret = mmp_com_ui_fp_set_focus_info(pv_info_hdlr_inst,
                                          MMP_PP_FOCUS_INFO_ID_READ_ONLY,
                                          MMP_COM_UI_FP_DATA_BOOL,
                                          (VOID*)FALSE,
                                          FALSE);
    IS_MMPR_OK(i4_ret);

    i4_ret = mmp_com_ui_focus_info_frm_repaint(pv_info_hdlr_inst,
                                               MMP_INFO_SYNC_REPAINT);
    IS_MMPR_OK(i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_update_file_name
 *
 * Description: Update the file information in the info page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_update_file_name(_MMP_PP_DATA_MEMBER_T*   pt_this,
                                         VOID*                    pv_cmd_param,
                                         VOID*                    pv_info_hdlr_inst,
                                         BOOL                     b_info_hdlr)
{
    INT32    i4_ret = -1;
    SIZE_T   z_buf_size;
    CHAR     s_buf[MMP_PP_RC_STR_MAX_LEN + 1], *ps_buf,s_error[MMP_PP_RC_STR_MAX_LEN + 1];
    UTF16_T  ws_buf[MMP_PP_RC_STR_MAX_LEN + 12], *ws_display = NULL, ws_error[MMP_PP_RC_STR_MAX_LEN + 1];
    MMP_COM_FP_FOCUS_INFO_VIEW_T       *pt_temp;
    UINT8                 ui1_gui_lang_id;
    ISO_639_LANG_T        s639_lang;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    IS_MMPR_OK(i4_ret);
    if(b_info_hdlr && (NULL == pv_cmd_param || NULL == pv_info_hdlr_inst))
    {
        return MMPR_INV_ARG;
    }

    c_sprintf(s_error, "%s", "-");
    c_uc_ps_to_w2s(s_error, ws_error, MMP_PP_RC_STR_MAX_LEN);

    z_buf_size = MMP_PP_RC_STR_MAX_LEN + 1;

    if(b_info_hdlr)
    {
        i4_ret = mmp_pe_info_get(pv_cmd_param,
                                 MMP_FP_INFO_TYPE_TITLE,
                                 &z_buf_size,
                                 (UINT8*)s_buf);
    }
    else
    {
        i4_ret = mmp_pe_play_get_file_info(MMP_PE_FILE_IDX_CURRENT,
                                           MMP_FP_INFO_TYPE_TITLE,
                                           &z_buf_size,
                                           (UINT8*)s_buf);
    }
    if(MMPR_OK != i4_ret)
    {
        if(MMPR_NO_DATA != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_pe_play_get_file_info() fail. i4_ret = %d.\r\n", i4_ret));
        }

        c_sprintf(s_buf,"%s","-");
    }

    z_buf_size = c_strlen(s_buf);
    /*
    while('.' != s_buf[z_buf_size -1])
    {
        s_buf[z_buf_size -1] = 0;
        z_buf_size--;
        MMP_ASSERT(z_buf_size > 1);
    }
    */
    s_buf[z_buf_size] = 0;
    ps_buf = s_buf;
    i4_ret = c_uc_ps_to_w2s(ps_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
    if(UCR_OK != i4_ret)
    {
        ws_display = ws_error;
    }
    else
    {
        z_buf_size = c_strlen(ps_buf);
        ws_buf[z_buf_size] = '\0';
        ws_display = ws_buf;
    }

    if(b_info_hdlr)
    {
        pt_temp = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_info_hdlr_inst;
        ui1_gui_lang_id  = mlm_mmp_s639_to_langidx(s639_lang);
        if(i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("<MMP photo player > get lanugage fail\r\n"));
        }

        i4_ret = c_wgl_do_cmd (pt_temp->h_info_list,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(0,0),
                        WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_THU_MODE_FILE_INFO_NAME)));


        if(i4_ret != WGLR_OK)
        {
             c_wgl_set_visibility(pt_temp->h_info_list, WGL_SW_HIDE_RECURSIVE);
        }
        else
             c_wgl_set_visibility(pt_temp->h_info_list, WGL_SW_RECURSIVE);


        i4_ret = mmp_com_ui_fp_set_focus_info(pv_info_hdlr_inst,
                                              MMP_PP_FOCUS_INFO_ID_NAME,
                                              MMP_COM_UI_FP_DATA_W2S,
                                              (VOID*)ws_display,
                                              FALSE);

    //IS_MMPR_OK (c_wgl_repaint(pt_temp->h_main_frm, NULL,TRUE));

    }
    else
    {
        #if 0
        i4_ret = mmp_common_ui_toolbar_cmd_do(pt_ptb_inst,
                                              MMP_PP_TB_CMD_SET_FILENAME,
                                              (VOID*)(ws_display),
                                            MMP_TB_NON_REPAINT);
        #endif

    }
    IS_MMPR_OK(i4_ret);
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_update_file_info_solution
 *
 * Description: Update the file information in the info page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_update_file_info_solution(_MMP_PP_DATA_MEMBER_T*   pt_this,
                                               VOID*                    pv_cmd_param,
                                               VOID*                    pv_info_hdlr_inst)
{
    INT32      i4_ret = -1;
    SIZE_T     z_buf_size;
    GL_SIZE_T  t_size;
    CHAR     s_buf[MMP_PP_RC_STR_MAX_LEN + 1], *ps_buf, s_error[MMP_PP_RC_STR_MAX_LEN + 1];
    UTF16_T  ws_buf[MMP_PP_RC_STR_MAX_LEN + 1], *ws_display =NULL, ws_error[MMP_PP_RC_STR_MAX_LEN + 1];
    MMP_COM_FP_FOCUS_INFO_VIEW_T       *pt_temp;
    UINT8                 ui1_gui_lang_id;
    ISO_639_LANG_T        s639_lang;

    c_sprintf(s_error, "%s", "-");
    c_uc_ps_to_w2s(s_error, ws_error, MMP_PP_RC_STR_MAX_LEN);

    z_buf_size = sizeof(GL_SIZE_T);

    i4_ret = mmp_pe_info_get(pv_cmd_param,
                             MMP_FP_INFO_TYPE_RESOLUTION,
                             &z_buf_size,
                             (UINT8*)(&t_size));
    if(MMPR_OK != i4_ret)
    {
        if(MMPR_NO_DATA != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_pe_play_get_file_info() fail. i4_ret = %d.\r\n", i4_ret));
        }
        c_sprintf(s_buf,"%s","-");
    }

    c_sprintf(s_buf, "%dx%d", t_size.ui4_width, t_size.ui4_height);

    ps_buf = s_buf;

    i4_ret = c_uc_ps_to_w2s(ps_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
    if(UCR_OK != i4_ret)
    {
        ws_display = ws_error;
    }
    else
    {
        z_buf_size = c_strlen(ps_buf);
        ws_buf[z_buf_size] = '\0';
        ws_display = ws_buf;
    }

    MMP_ASSERT(c_strlen(s_buf) < MMP_PP_RC_STR_MAX_LEN);

    pt_temp = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_info_hdlr_inst;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<MMP photo player > get lanugage fail\r\n"));
    }

    ui1_gui_lang_id  = mlm_mmp_s639_to_langidx(s639_lang);

    i4_ret = c_wgl_do_cmd (pt_temp->h_info_list,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(1,0),
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_THU_MODE_FILE_INFO_RESOLUTION)));



    if(i4_ret != WGLR_OK)
    {
         c_wgl_set_visibility(pt_temp->h_info_list, WGL_SW_HIDE_RECURSIVE);
    }
    else
         c_wgl_set_visibility(pt_temp->h_info_list, WGL_SW_RECURSIVE);

    i4_ret = mmp_com_ui_fp_set_focus_info(pv_info_hdlr_inst,
                                          MMP_PP_FOCUS_INFO_ID_RESLUTION,
                                          MMP_COM_UI_FP_DATA_W2S,
                                          (VOID*)ws_display,
                                          FALSE);
    IS_MMPR_OK(i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_update_file_info_size
 *
 * Description: Update the file information in the info page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_update_file_info_size(_MMP_PP_DATA_MEMBER_T*   pt_this,
                                            VOID*                    pv_cmd_param,
                                            VOID*                    pv_info_hdlr_inst)
{
    INT32    i4_ret = -1;
    SIZE_T   z_buf_size;
    UINT64   ui8_size;//ui8_size2;
    CHAR     s_buf[MMP_PP_RC_STR_MAX_LEN + 1],*ps_buf, s_error[MMP_PP_RC_STR_MAX_LEN + 1];
    UTF16_T  ws_buf[MMP_PP_RC_STR_MAX_LEN + 1], *ws_display = NULL, ws_error[MMP_PP_RC_STR_MAX_LEN + 1];
    MMP_COM_FP_FOCUS_INFO_VIEW_T       *pt_temp;
    UINT8                 ui1_gui_lang_id;
    ISO_639_LANG_T        s639_lang;

    c_sprintf(s_error, "%s", "-");
    c_uc_ps_to_w2s(s_error, ws_error, MMP_PP_RC_STR_MAX_LEN);

    z_buf_size = sizeof(UINT64);

    i4_ret = mmp_pe_info_get(pv_cmd_param,
                             MMP_FP_INFO_TYPE_SIZE,
                             &z_buf_size,
                             (UINT8*)(&ui8_size));
    if(MMPR_OK != i4_ret)
    {
        if(MMPR_NO_DATA != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_pe_play_get_file_info() fail. i4_ret = %d.\r\n", i4_ret));
        }
        c_sprintf(s_buf,"%s","-");
    }
    //ui8_size2 = ui8_size%1024;
    if(0xFFFFFFFFFFFFFFF != ui8_size)
    {
    ui8_size = ui8_size/1024;


   // c_sprintf(s_buf, "%d.%d KB", ui8_size,ui8_size2);
   c_sprintf(s_buf, "%d KB", ui8_size);

    ps_buf = s_buf;

    i4_ret = c_uc_ps_to_w2s(ps_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
    if(UCR_OK != i4_ret)
    {
        ws_display = ws_error;
    }
    else
    {
        z_buf_size = c_strlen(ps_buf);
        ws_buf[z_buf_size] = '\0';
        ws_display = ws_buf;
    }
    }
    else
    {
        ws_display = ws_error;
    }

    MMP_ASSERT(c_strlen(s_buf) < MMP_PP_RC_STR_MAX_LEN);

    pt_temp = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_info_hdlr_inst;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<MMP photo player > get lanugage fail\r\n"));
    }
    ui1_gui_lang_id  = mlm_mmp_s639_to_langidx(s639_lang);

    i4_ret = c_wgl_do_cmd (pt_temp->h_info_list,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(2,0),
                    WGL_PACK(MLM_MMP_TEXT(ui1_gui_lang_id,MLM_MMP_KEY_THU_MODE_FILE_SIZE)));


    if(i4_ret != WGLR_OK)
    {
         c_wgl_set_visibility(pt_temp->h_info_list, WGL_SW_HIDE_RECURSIVE);
    }
    else
         c_wgl_set_visibility(pt_temp->h_info_list, WGL_SW_RECURSIVE);

    i4_ret = mmp_com_ui_fp_set_focus_info(pv_info_hdlr_inst,
                                          MMP_PP_FOCUS_INFO_ID_SIZE,
                                          MMP_COM_UI_FP_DATA_W2S,
                                          (VOID*)ws_display,
                                          FALSE);
    IS_MMPR_OK(i4_ret);
    IS_MMPR_OK (c_wgl_repaint(pt_temp->h_main_frm, NULL,TRUE));

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_update_file_info_protect
 *
 * Description: Update the file information in the info page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_update_file_info_protect(_MMP_PP_DATA_MEMBER_T*   pt_this,
                                              VOID*                    pv_cmd_param,
                                              VOID*                    pv_info_hdlr_inst)
{
    INT32           i4_ret = -1;
    SIZE_T          z_buf_size;
    BOOL            b_protect;

    z_buf_size = sizeof(BOOL);

    i4_ret = mmp_pe_info_get(pv_cmd_param,
                             MMP_FP_INFO_TYPE_PROTECT,
                             &z_buf_size,
                             (UINT8*)(&b_protect));
    IS_MMPR_OK(i4_ret);

    i4_ret = mmp_com_ui_fp_set_focus_info(pv_info_hdlr_inst,
                                          MMP_PP_FOCUS_INFO_ID_READ_ONLY,
                                          MMP_COM_UI_FP_DATA_BOOL,
                                          (VOID*)(UINT32)b_protect,
                                          FALSE);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_pp_view_broadcast_file_msg
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _mmp_pp_view_broadcast_file_msg(
    VOID*                       pv_unused1,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3,
    VOID*                       pv_unused4)
{
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ACTIVE, MMP_MSG_ID_PF_PALY_FAIL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_update_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
#ifdef MMP_GUI_AUTHORING_DP
static VOID _mmp_pp_view_update_info(
    _MMP_PP_DATA_MEMBER_T*      pt_this)

{
    GL_SIZE_T                       t_size = {0};
    DTG_T                           t_dtg = {0};
    SIZE_T                          z_buf_size;
    IMG_ROTATE_OP_TYPE_T            t_rotation = IMG_ROTATE_CLOCKWS_0_OP_TYPE;
    float                           t_exposure_time = 0.000;
    UINT16                          iso = 0;
    EXIF_FLASH_MODE_TYPE_T          flash = EXIF_FLASH_OFF;
    EXIF_SRATIONAL_DATA             speed = {0,1};
    float                           bias  = 0.000;
    INT32                           expro = 0;
    UINT64                          ui8_file_size1=0;
    INT32                           i4_ret, i;
    UTF16_T                         ws_buf[MMP_PP_RC_STR_MAX_LEN + 1]={0}, *ws_display = NULL;
    CHAR                            s_camera[MMP_PP_RC_STR_MAX_LEN + 1],s_buf[MMP_PP_RC_STR_MAX_LEN + 1]={0}, *ps_buf;
    BOOL                            b_is_supported;
    BOOL                            b_is_bad_head = TRUE;
    BOOL                            b_is_removed = FALSE;
    BOOL                            b_file_not_exist = TRUE;
    BOOL                            b_failed      = FALSE;
    MMP_PP_MSGBOX_TYPE_T            t_msg_type    = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;
    MMP_PP_DP_CONFIG_T              at_config[MMP_PP_RC_DP_LBL_COUNT] = _MMP_PP_RC_DP_GET_CONFIG();

    #if 1

    for(i = 0; i < MMP_PP_RC_DP_LBL_COUNT; i++)
    {
        b_failed = FALSE;
        z_buf_size = MMP_PP_RC_STR_MAX_LEN + 1;

        if(MMP_FP_INFO_TYPE_ALBUM == at_config[i].e_type ||
           _MMP_PP_IFNO_DATA_TYPE_CAMERA == at_config[i].e_data_type )
        {
            memset(s_buf,0,sizeof(s_buf));
            z_buf_size = MMP_PP_RC_STR_MAX_LEN + 1;
            at_config[i].pui1_buf = (UINT8*)s_buf;
        }
        else if(_MMP_PP_INFO_DATA_TYPE_GL_SIZE == at_config[i].e_data_type)//x y resolution
        {
            z_buf_size = sizeof(GL_SIZE_T);
            at_config[i].pui1_buf = (UINT8*)&t_size;
        }
        else if(_MMP_PP_INFO_DATA_TYPE_DTG == at_config[i].e_data_type)
        {
            z_buf_size = sizeof(DTG_T);
            at_config[i].pui1_buf = (UINT8*)&t_dtg;
        }
        else if(_MMP_PP_INFO_DATA_TYPE_FILE_SIZE == at_config[i].e_data_type)
        {
            z_buf_size = sizeof(ui8_file_size1);
            at_config[i].pui1_buf = (UINT8*) &ui8_file_size1;
        }
        else if(MMP_FP_INFO_TYPE_TITLE == at_config[i].e_type)
        {
            z_buf_size = MMP_PP_RC_STR_MAX_LEN + 1;
            at_config[i].pui1_buf = (UINT8*)s_buf;
        }


        //--------------------------------jpeg exif info-----------------------------------
        else if(_MMP_PP_INFO_DATA_TYPE_EXPOSURE_PROGRAM == at_config[i].e_data_type)
        {
            z_buf_size = sizeof(expro);
            at_config[i].pui1_buf = (UINT8*) &expro;
        }
        else if(_MMP_PP_INFO_DATA_TYPE_EXPOSURE_TIME == at_config[i].e_data_type)
        {
            z_buf_size = sizeof(t_exposure_time);
            at_config[i].pui1_buf = (UINT8*) &t_exposure_time;
        }
        else if(_MMP_PP_INFO_DATE_TYPE_ISO == at_config[i].e_data_type)
        {
            z_buf_size = sizeof(iso);
            at_config[i].pui1_buf = (UINT8*) &iso;
        }
        else if(_MMP_PP_IFNO_DATA_TYPE_FLASH == at_config[i].e_data_type)
        {
            z_buf_size = sizeof(flash);
            at_config[i].pui1_buf = (UINT8*) &flash;
        }
        else if(_MMP_PP_INFO_DATA_TYPE_BIAS == at_config[i].e_data_type)
        {
            z_buf_size = sizeof(bias);
            at_config[i].pui1_buf = (UINT8*) &bias;
        }
        //---------------------------------------------------------------------------------

        if(z_buf_size)
        {
            i4_ret = mmp_pe_play_get_file_info(MMP_PE_FILE_IDX_CURRENT,
                                               at_config[i].e_type,
                                               &z_buf_size,
                                               at_config[i].pui1_buf);
            if(MMPR_OK != i4_ret)
            {
                if(MMPR_NO_DATA != i4_ret)
                {
                    MMP_DBG_ERROR(("mmp_pe_play_get_file_info() fail. i4_ret = %d.\r\n", i4_ret));
                }

                b_failed = TRUE;
                at_config[i].pui1_buf = NULL;
            }
        }
        ws_display = NULL;

        //TITLE:...........................................................................................
        if(MMP_FP_INFO_TYPE_ALBUM == at_config[i].e_type)
        {
            UINT32  z_buf_size;
            CHAR    s_buf[MMP_PP_RC_STR_MAX_LEN + 1], *ps_buf;
            INT32   i4_ret, i4_ret2;

            // Fix coverity-4491958: Pointer to local outside scope
            //UTF16_T ws_buf[MMP_PP_RC_STR_MAX_LEN + 1];

            i4_ret2 = mmp_mc_list_get_item_count(MMP_GROUND_MODE_FORE, &pt_this->ui4_total_fileidx );
            i4_ret = mmp_mc_list_get_idx(MMP_GROUND_MODE_FORE, MMP_PL_IDX_TYPE_CRNT_PLAY,  &pt_this->ui4_current_fileidx );
            if(MMPR_OK != i4_ret || MMPR_OK != i4_ret2)
            {
                MMP_DBG_ERROR(("mmp_mc_list_get_item_count(MMP_GROUND_MODE_FORE) (ret = %d) or mmp_mc_list_get_idx(%d) (i4_ret = %d) fail.\r\n", i4_ret2, MMP_PL_IDX_TYPE_CRNT_PLAY, i4_ret));
                ws_display = NULL;
            }
            else
            {
                CHAR    s_result[MMP_PP_RC_STR_MAX_LEN + 1] = {0};
                i4_ret = c_uc_w2s_to_ps(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_MMP_DP_INFO_TEMP),
                                s_result,
                                sizeof(s_result));

                MMPR_LOG_ON_FAIL(i4_ret);
                c_snprintf(s_buf,(SIZE_T)(MMP_PP_RC_STR_MAX_LEN + 1), s_result, (pt_this->ui4_current_fileidx + 1), pt_this->ui4_total_fileidx);

                ps_buf = s_buf;
                i4_ret = c_uc_ps_to_w2s(ps_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
                if(UCR_OK != i4_ret)
                {
                    ws_display = NULL;
                }
                else
                {
                    z_buf_size = c_strlen(ps_buf);
                    ws_buf[z_buf_size] = (UTF16_T)0;
                    ws_display = ws_buf;
                }
            }
        }
        //DATA:...........................................................................................
        else if(_MMP_PP_INFO_DATA_TYPE_DTG == at_config[i].e_data_type)
        {
            if(b_failed)
            {
                ws_display = NULL;
            }
            else
            {
                c_sprintf(s_buf, MMP_PP_RC_DATE_FMT, t_dtg.ui1_mo, t_dtg.ui1_day, t_dtg.ui2_yr);
                MMP_ASSERT(c_strlen(s_buf) < MMP_PP_RC_STR_MAX_LEN);
                c_uc_ps_to_w2s(s_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
                ws_display = ws_buf;
            }
        }
        //NAME:...........................................................................................
        else if(MMP_FP_INFO_TYPE_TITLE == at_config[i].e_type)
        {
            memset(s_buf,0,sizeof(s_buf));
            z_buf_size = MMP_PP_RC_STR_MAX_LEN + 1;
            i4_ret = mmp_pe_play_get_file_info(MMP_PE_FILE_IDX_CURRENT,
                                               MMP_FP_INFO_TYPE_TITLE,
                                               &z_buf_size,
                                               (UINT8*)s_buf);
            if(i4_ret != MMPR_OK)
            {
                ws_display = NULL;
            }
            else
            {
                c_uc_ps_to_w2s(s_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
                ws_display = ws_buf;
            }
        }
        //RESOLUTION:...........................................................................................
        else if(_MMP_PP_INFO_DATA_TYPE_GL_SIZE == at_config[i].e_data_type)
        {
            if(b_failed)
            {
                ws_display = NULL;
            }
            else
            {
                c_sprintf(s_buf, "%d X %d", t_size.ui4_width, t_size.ui4_height);
                MMP_ASSERT(c_strlen(s_buf) < MMP_PP_RC_STR_MAX_LEN);
                c_uc_ps_to_w2s(s_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
                ws_display = ws_buf;
            }
        }

        //SIZE:...........................................................................................
        else if(_MMP_PP_INFO_DATA_TYPE_FILE_SIZE == at_config[i].e_data_type)
        {
            if(b_failed || 0xFFFFFFFFFFFFFFF == ui8_file_size1)
            {
                ws_display = NULL;
            }
            else
            {
                ui8_file_size1 = ui8_file_size1/1024;
                c_sprintf(s_buf, "%d KB",ui8_file_size1);
                c_uc_ps_to_w2s(s_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
                ws_display = ws_buf;
            }
        }


        //--------------------------------jpeg exif info-----------------------------------

        //...........................................................................................
        else if(_MMP_PP_IFNO_DATA_TYPE_CAMERA == at_config[i].e_data_type)
        {
            //DBG_LOG_PRINT(("[%s]  CameraModel:%s. \r\n", __FUNCTION__, s_camera));
            if(b_failed)
            {
                ws_display = NULL;
            }
            else
            {
                c_uc_ps_to_w2s(s_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
                ws_display = ws_buf;
            }
        }
        else if(_MMP_PP_INFO_DATA_TYPE_EXPOSURE_TIME == at_config[i].e_data_type)
        {
            DBG_LOG_PRINT(("[%s]  CameraModel:%lf. \r\n", __FUNCTION__, t_exposure_time));
            if(b_failed || (-0.000001 <= t_exposure_time && t_exposure_time <= 0.000001))
            {
                ws_display = NULL;
            }
            else
            {
                if(t_exposure_time >= 1.000 && t_exposure_time < 4.000)
                    c_sprintf(s_buf, "%d",(int)t_exposure_time);
                else
                    c_sprintf(s_buf, "1/%d\"",(int)((float)1.0000/t_exposure_time));

                c_uc_ps_to_w2s(s_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
                ws_display = ws_buf;
            }
        }
        //...........................................................................................
        else if(_MMP_PP_IFNO_DATA_TYPE_FLASH == at_config[i].e_data_type)
        {
            //DBG_LOG_PRINT(("[%s]  FlashUsed:%d.\r\n", __FUNCTION__, flash));
            if(b_failed)
            {
                ws_display = NULL;
            }
            else
            {
                if(flash == 0)
                    ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_FLASH_OFF);
                else if(flash == 1)
                    ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_FLASH_ON);
                else if(flash == 9)
                    ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_FLASH_FORCE_ON);
                else if(flash == 16)
                    ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_FLASH_FORCE_OFF);
                else if(flash == 24)
                    ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_FLASH_AUTO_OFF);
                else if(flash == 25)
                    ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_FLASH_AUTO_ON);
            }
        }
        //...........................................................................................
        else if(_MMP_PP_INFO_DATA_TYPE_EXPOSURE_PROGRAM == at_config[i].e_data_type)
        {
            //DBG_LOG_PRINT(("[%s]  ExposureProgram:%d.\r\n", __FUNCTION__, expro));
            ws_display = NULL;
            if(b_failed)
            {
                ws_display = NULL;
            }
            else
            {
                ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_EP_NOT_DEFINE + (UINT32)expro);
            }
        }
        //...........................................................................................
        else if(_MMP_PP_INFO_DATE_TYPE_ISO == at_config[i].e_data_type)
        {
            //DBG_LOG_PRINT(("[%s]  ISOequivalent:%d.\r\n", __FUNCTION__, iso));
            ws_display = NULL;
            if(b_failed || iso == 0)
            {
                ws_display = NULL;
            }
            else
            {
                c_sprintf(s_buf, MMP_PP_RC_ISO_FMT,iso);
                c_uc_ps_to_w2s(s_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
                ws_display = ws_buf;
            }
        }
        //...........................................................................................
        else if(_MMP_PP_INFO_DATA_TYPE_BIAS == at_config[i].e_data_type)
        {
            //DBG_LOG_PRINT(("[%s]  ExposureBias:%f.\r\n", __FUNCTION__, bias));
            if(b_failed || (-0.000001 <= bias && bias <= 0.000001))
            {
                ws_display = NULL;
            }
            else
            {
                if(bias < 0.000)
                {
                    c_sprintf(s_buf,"-%lf EV",bias);
                }
                else
                {
                    c_sprintf(s_buf,"+%lf EV",bias);
                }
                c_uc_ps_to_w2s(s_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
                ws_display = ws_buf;
            }
        }

        if(NULL == ws_display)
        {
            ws_buf[0] = (UTF16_T)0;
            ws_display = ws_buf;
        }

        pt_pdp_inst->e_repaint = COM_UI_NON_REPAINT;
        mmp_com_ui_dp_set_text(pt_pdp_inst, (MMP_DP_LBL_ID_T)(i + MMP_PP_RC_DP_LBL_ID_ALBM), ws_display);
    }


    /*check current file supported or not*/
    z_buf_size = sizeof(BOOL);
    i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                             MMP_PE_EXTRA_INFO_ID_IS_SUPPORTED,
                                             &z_buf_size,
                                             (VOID *)&b_is_supported);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_READY) fail. i4_ret = %d.\r\n", i4_ret));

        b_is_supported = TRUE;
    }

    /* If not support, show not support text */
    if( FALSE == b_is_supported )
    {
        /*check if the device is removed. If yes, don't show message*/
        i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                 MMP_PE_EXTRA_INFO_ID_IS_REMOVED,
                                                 &z_buf_size,
                                                 (VOID *)&b_is_removed);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_REMOVED) fail. i4_ret = %d.\r\n", i4_ret));
            b_is_removed = FALSE;
        }

        if(FALSE == b_is_removed) /*not caused by unplugging devices*/
        {
            /* Reset hide timer to show the notify */
            // _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
            if(_MMP_INFO_STATE_NONE == pt_this->e_info_state)
            {
                _mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_SIMPLE);
            }

            z_buf_size = sizeof(BOOL);
            i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                     MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST,
                                                     &z_buf_size,
                                                     &b_file_not_exist);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST) fail. i4_ret = %d.\r\n", i4_ret));
                b_file_not_exist = TRUE;
            }

            if(b_file_not_exist)
            {
                t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_EXIST;
            }
            else
            {
                i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                         MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER,
                                                         &z_buf_size,
                                                         &b_is_bad_head);
                if(MMPR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER) fail. i4_ret = %d.\r\n", i4_ret));
                    b_is_bad_head = FALSE;
                }

                if(b_is_bad_head)
                {
                    BOOL    b_meet_all = FALSE;
                    z_buf_size = sizeof(BOOL);
                    i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                                 MMP_PE_EXTRA_INFO_ID_IS_MEET_LIMITATION,
                                                                 &z_buf_size,
                                                                 &b_meet_all);

                    if(IMGR_OK != i4_ret)
                    {
                        MMP_DBG_ERROR(("c_img_get_info(IMG_INFO_THUMBNAIL_MEET_ALL_LIMITATION) failed. i4_ret = %d.\r\n", i4_ret));
                        t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;
                    }

                    if(FALSE == b_meet_all)
                    {
                        t_msg_type = MMP_PP_MSGBOX_TYPE_RESOLUTION_NOT_SUPPORT;
                    }
                    else
                    {
                        t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;
                    }
                }
                else
                {
                    t_msg_type = MMP_PP_MSGBOX_TYPE_DECODE_FAIL;
                }
            }

            if(pt_this->b_pp_view_active)
            {
                SIZE_T      z_size = MMP_PP_RC_STR_MAX_LEN + 1;
                CHAR        s_buff[MMP_PP_RC_STR_MAX_LEN + 1];
                UTF16_T     ws_buff[MMP_PP_RC_STR_MAX_LEN + 12];

                i4_ret = _mmp_pp_view_open_msgbox(t_msg_type);
                if(WGLR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("_mmp_pp_view_open_msgbox fail. i4_ret = %d.\r\n", i4_ret));
                }
                i4_ret = mmp_pe_play_get_file_info(MMP_PE_FILE_IDX_CURRENT,
                                                   MMP_FP_INFO_TYPE_TITLE,
                                                   &z_size,
                                                   (UINT8*)s_buff);
                if(MMPR_OK != i4_ret)
                {
                    if(MMPR_NO_DATA != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_pe_play_get_file_info() fail. i4_ret = %d.\r\n", i4_ret));
                    }
                }

                z_buf_size = c_strlen(s_buff);
                s_buff[z_buf_size] = 0;
                c_uc_ps_to_w2s(s_buff, ws_buff, MMP_PP_RC_STR_MAX_LEN);
                i4_ret = c_wgl_do_cmd (pt_this->t_view.h_not_show_file_title,
                                        WGL_CMD_TEXT_SET_TEXT,
                                        WGL_PACK(ws_buff),
                                        WGL_PACK(c_uc_w2s_strlen(ws_buff)));
                MMPR_LOG_ON_FAIL(i4_ret);
                c_wgl_show(pt_this->t_view.h_not_show_file_title,WGL_SW_RECURSIVE);
            }
            else
            {
                mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                            _mmp_pp_view_broadcast_file_msg,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL);
            }
        }
    }

    #endif

    //fix menu network ip setting page lose focus when photo going slider show
    MMP_DBG_INFO(("[mmp] %s %d e_info_state:%d \r\n",__FUNCTION__,__LINE__,pt_this->e_info_state));
    if(pt_this->e_info_state == _MMP_INFO_STATE_DETAIL || pt_this->e_info_state == _MMP_INFO_STATE_DETAIL_THEN_POP_UP)
    {
        c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
        menu_pm_refresh();
        menu_pm_repaint();
    }


}

#else

static VOID _mmp_pp_view_update_info(
    _MMP_PP_DATA_MEMBER_T*      pt_this)
{
    GL_SIZE_T                   t_size;
    DTG_T                       t_dtg;
    SIZE_T                      z_buf_size;
    IMG_ROTATE_OP_TYPE_T        t_rotation;
    EXIF_RATIONAL_DATA          t_exposure_time,t_f_number;
    EXIF_CONTEXT_DATA           t_context_data;
    INT32                       i4_ret, i, i4_count;
    UTF16_T                     ws_buf[MMP_PP_RC_STR_MAX_LEN + 1], *ws_display = NULL;
    CHAR                        s_buf[MMP_PP_RC_STR_MAX_LEN + 1], *ps_buf;
    BOOL                        b_is_supported;
    BOOL                        b_is_bad_head = TRUE;
    BOOL                        b_is_removed = FALSE;
    BOOL                        b_failed      = FALSE;
    MMP_PP_MSGBOX_TYPE_T        t_msg_type    = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;
    _MMP_PP_INFO_UPDATE_REC_T   at_info_rec[] = {
                                                 {
                                                    MMP_FP_INFO_TYPE_TITLE,
                                                    MMP_PP_RC_STR_MAX_LEN + 1,
                                                    (UINT8*)s_buf,
                                                    _MMP_PP_INFO_DATA_TYPE_CHAR,
                                                    pt_this->t_view.t_statusbar.ah_label[MMP_PP_RC_SB_LBL_ID_FILE_NAME]
                                                 },
                                                 {
                                                    MMP_FP_INFO_TYPE_TITLE,
                                                    MMP_PP_RC_STR_MAX_LEN + 1,
                                                    (UINT8*)s_buf,
                                                    _MMP_PP_INFO_DATA_TYPE_CHAR,
                                                    pt_this->t_view.t_detailpage.ah_label[MMP_PP_RC_DP_LBL_ID_VALUE_NAME]
                                                 },
                                                 {
                                                    MMP_FP_INFO_TYPE_ARTIST,
                                                    MMP_PP_RC_STR_MAX_LEN + 1,
                                                    (UINT8*)s_buf,
                                                    _MMP_PP_INFO_DATA_TYPE_CHAR,
                                                    pt_this->t_view.t_detailpage.ah_label[MMP_PP_RC_DP_LBL_ID_VALUE_ARTIST]
                                                 },
                                                 {
                                                    MMP_FP_INFO_TYPE_ALBUM,
                                                    MMP_PP_RC_STR_MAX_LEN + 1,
                                                    (UINT8*)s_buf,
                                                    _MMP_PP_INFO_DATA_TYPE_CHAR,
                                                    pt_this->t_view.t_detailpage.ah_label[MMP_PP_RC_DP_LBL_ID_VALUE_ALBM]
                                                 },
                                                 {
                                                    MMP_FP_INFO_TYPE_ROTATION,
                                                    sizeof(t_rotation),
                                                    (UINT8*)&t_rotation,
                                                    _MMP_PP_INFO_DATA_TYPE_ROTATION,
                                                    pt_this->t_view.t_detailpage.ah_label[MMP_PP_RC_DP_LBL_ID_VALUE_ROTATION]
                                                 },
                                                 {
                                                    MMP_FP_INFO_TYPE_EXPOSURE_TIME,
                                                    sizeof(t_exposure_time),
                                                    (UINT8*) &t_exposure_time,
                                                    _MMP_PP_INFO_DATA_TYPE_EXPOSURE_TIME,
                                                    pt_this->t_view.t_detailpage.ah_label[MMP_PP_RC_DP_LBL_ID_VALUE_EXPOSURE_TIME]
                                                 },
                                                 {
                                                    MMP_FP_INFO_TYPE_F_NUMBER,
                                                    sizeof(t_f_number),
                                                    (UINT8*) &t_f_number,
                                                    _MMP_PP_INFO_DATA_TYPE_F_NUMBER,
                                                    pt_this->t_view.t_detailpage.ah_label[MMP_PP_RC_DP_LBL_ID_VALUE_F_NUMBER]
                                                 },
                                                 {
                                                    MMP_FP_INFO_TYPE_EXPOSURE_PROGRAM,
                                                    sizeof(t_context_data),
                                                    (UINT8*) &t_context_data,
                                                    _MMP_PP_INFO_DATA_TYPE_EXPOSURE_PROGRAM,
                                                    pt_this->t_view.t_detailpage.ah_label[MMP_PP_RC_DP_LBL_ID_VALUE_EXPOSURE_PROGRAM]
                                                 },
                                                 {
                                                    MMP_FP_INFO_TYPE_COLOR_SPACE,
                                                    sizeof(t_context_data),
                                                    (UINT8*) &t_context_data,
                                                    _MMP_PP_INFO_DATA_TYPE_COLOR_SPACE,
                                                    pt_this->t_view.t_detailpage.ah_label[MMP_PP_RC_DP_LBL_ID_VALUE_COLOR_SPACE]
                                                 },
                                                 {
                                                    MMP_FP_INFO_TYPE_CREATE_TIME,
                                                    sizeof(DTG_T),
                                                    (UINT8*)&t_dtg,
                                                    _MMP_PP_INFO_DATA_TYPE_DTG,
                                                    pt_this->t_view.t_detailpage.ah_label[MMP_PP_RC_DP_LBL_ID_VALUE_DATE]
                                                 },
                                                 {
                                                    MMP_FP_INFO_TYPE_RESOLUTION,
                                                    sizeof(GL_SIZE_T),
                                                    (UINT8*)&t_size,
                                                    _MMP_PP_INFO_DATA_TYPE_GL_SIZE,
                                                    pt_this->t_view.t_detailpage.ah_label[MMP_PP_RC_DP_LBL_ID_VALUE_SIZE]
                                                 },
                                                 {
                                                    MMP_FP_INFO_TYPE_TITLE,
                                                    0,
                                                    NULL,
                                                    _MMP_PP_INFO_DATA_TYPE_CHAR,
                                                    pt_this->t_view.t_detailpage.ah_label[MMP_PP_RC_DP_LBL_ID_VALUE_NEXT]
                                                 }};


    i4_count = (INT32)(sizeof(at_info_rec) / sizeof(_MMP_PP_INFO_UPDATE_REC_T));
    for(i = 0; i < i4_count; i++)
    {
        b_failed = FALSE;

        z_buf_size = at_info_rec[i].z_size;
        if(z_buf_size)
        {
            i4_ret = mmp_pe_play_get_file_info(MMP_PE_FILE_IDX_CURRENT,
                                               at_info_rec[i].e_type,
                                               &z_buf_size,
                                               at_info_rec[i].pui1_buf);
            if(MMPR_OK != i4_ret)
            {
                if(MMPR_NO_DATA != i4_ret)
                {
                    MMP_DBG_ERROR(("mmp_pe_play_get_file_info() fail. i4_ret = %d.\r\n", i4_ret));
                }

                b_failed = TRUE;
                at_info_rec[i].pui1_buf = NULL;
            }
        }

        if(at_info_rec[i].pui1_buf == NULL)
        {
            s_buf[0] = 0;
            at_info_rec[i].pui1_buf = (UINT8*)s_buf;
        }
        else
        {
            if(_MMP_PP_INFO_DATA_TYPE_GL_SIZE == at_info_rec[i].e_data_type)
            {
                if(at_info_rec[i].pui1_buf)
                {
                    c_sprintf(s_buf, MMP_PP_RC_RES_FMT, t_size.ui4_width, t_size.ui4_height);
                    MMP_ASSERT(c_strlen(s_buf) < MMP_PP_RC_STR_MAX_LEN);

                    at_info_rec[i].pui1_buf = (UINT8*)s_buf;
                }
            }
            else if(_MMP_PP_INFO_DATA_TYPE_DTG == at_info_rec[i].e_data_type)
            {
                if(at_info_rec[i].pui1_buf)
                {
                    c_sprintf(s_buf, MMP_PP_RC_DATE_FMT, t_dtg.ui2_yr, t_dtg.ui1_mo, t_dtg.ui1_day, t_dtg.ui1_hr, t_dtg.ui1_min, t_dtg.ui1_sec);
                    MMP_ASSERT(c_strlen(s_buf) < MMP_PP_RC_STR_MAX_LEN);

                    at_info_rec[i].pui1_buf = (UINT8*)s_buf;
                }
            }
            else if(_MMP_PP_INFO_DATA_TYPE_EXPOSURE_TIME == at_info_rec[i].e_data_type)
            {
                if(at_info_rec[i].pui1_buf)
                {
                    c_sprintf(s_buf, MMP_PP_RC_EXPOSURE_FMT, t_exposure_time.ui4_numerator, t_exposure_time.ui4_denominator);
                    MMP_ASSERT(c_strlen(s_buf) < MMP_PP_RC_STR_MAX_LEN);

                    at_info_rec[i].pui1_buf = (UINT8*)s_buf;
                }
            }
            else if(_MMP_PP_INFO_DATA_TYPE_F_NUMBER == at_info_rec[i].e_data_type)
            {
                if(at_info_rec[i].pui1_buf)
                {
                    FLOAT    f_result;
                    FLOAT    f_denominator = (FLOAT)t_f_number.ui4_denominator;
                    FLOAT    f_numerator   = (FLOAT)t_f_number.ui4_numerator;

                    if(0 == t_f_number.ui4_denominator)
                    {
                        s_buf[0] = 0;
                    }
                    else
                    {
                        f_result = f_numerator/f_denominator;
                        c_sprintf(s_buf, "%.1fF", f_result);
                    }

                    MMP_ASSERT(c_strlen(s_buf) < MMP_PP_RC_STR_MAX_LEN);

                    at_info_rec[i].pui1_buf = (UINT8*)s_buf;
                }
            }
        }

        if(at_info_rec[i].pui1_buf)
        {
            if(MMP_FP_INFO_TYPE_EXPOSURE_PROGRAM == at_info_rec[i].e_type)
            {
                if(b_failed)
                {
                    ws_display = NULL;
                }
                else
                {
                    ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_EP_NOT_DEFINE + (UINT32)t_context_data.u.e_exposure_program);
                }

            }
            else if(MMP_FP_INFO_TYPE_COLOR_SPACE == at_info_rec[i].e_type)
            {
                if(b_failed)
                {
                    ws_display = NULL;
                }
                else
                {
                    switch(t_context_data.u.e_color_space)
                    {
                        case EXIF_COLOR_SPACE_RESERVED:
                            ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_CS_RSV);
                            break;
                        case EXIF_COLOR_SPACE_SRGB:
                            ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_CS_SRGB);
                            break;
                        case EXIF_COLOR_SPACE_UNCALIBRATED:
                            ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_CS_UNCBR);
                            break;
                        default:
                            ws_display = NULL;
                            MMP_ASSERT(0);
                    }
                }
            }
            else if(MMP_FP_INFO_TYPE_ROTATION == at_info_rec[i].e_type)
            {
                if(b_failed)
                {
                    ws_display = NULL;
                }
                else
                {
                    ws_display = MLM_MMP_TEXT(_mmp_pp_get_mlm_lang_id(), MLM_MMP_KEY_PHOTO_ANGLE_0 + ((UINT32)t_rotation%4));
                }
            }
            else
            {
                ps_buf = s_buf;
                while('\0' != *ps_buf) /*remove space*/
                {
                    if(*ps_buf != ' ')
                    {
                        break;
                    }
                    ps_buf++;
                }
                /*convert to UTF16*/
                i4_ret = c_uc_ps_to_w2s(ps_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
                if(UCR_OK != i4_ret)
                {
                    ws_display = NULL;
                }
                else
                {
                    z_buf_size = c_strlen(ps_buf);
                    ws_buf[z_buf_size] = (UTF16_T)0;
                    ws_display = ws_buf;
                }
            }
        }
        else
        {
            ws_display = NULL;
        }

        if(NULL == ws_display)
        {
            ws_buf[0] = (UTF16_T)0;
            ws_display = ws_buf;
        }

        i4_ret = c_wgl_do_cmd(at_info_rec[i].h_update, WGL_CMD_TEXT_SET_TEXT, WGL_PACK(ws_display), WGL_PACK((UINT16)0xFFFF));
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_TEXT_SET_TEXT) fail. i4_ret = %d.\r\n", i4_ret));
        }
    }

    /*check current file supported or not*/
    z_buf_size = sizeof(BOOL);
    i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                             MMP_PE_EXTRA_INFO_ID_IS_SUPPORTED,
                                             &z_buf_size,
                                             &b_is_supported);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_READY) fail. i4_ret = %d.\r\n", i4_ret));

        b_is_supported = TRUE;
    }

    /* If not support, show not support text */
    if( FALSE == b_is_supported )
    {
        /*check if the device is removed. If yes, don't show message*/
        i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                 MMP_PE_EXTRA_INFO_ID_IS_REMOVED,
                                                 &z_buf_size,
                                                 &b_is_removed);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_REMOVED) fail. i4_ret = %d.\r\n", i4_ret));

            b_is_removed = FALSE;
        }

        if(FALSE == b_is_removed) /*not caused by unplugging devices*/
        {
            /* Reset hide timer to show the notify */
            //_mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
            if(_MMP_INFO_STATE_NONE == pt_this->e_info_state)
            {
                _mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_SIMPLE);
            }

            i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                     MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER,
                                                     &z_buf_size,
                                                     &b_is_bad_head);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER) fail. i4_ret = %d.\r\n", i4_ret));

                b_is_bad_head = FALSE;
            }

            if(b_is_bad_head)
            {
                t_msg_type = MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT;
            }
            else
            {
                t_msg_type = MMP_PP_MSGBOX_TYPE_DECODE_FAIL;
            }

            if(pt_this->b_pp_view_active)
            {
            i4_ret = _mmp_pp_view_open_msgbox(t_msg_type);
            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("_mmp_pp_view_open_msgbox fail. i4_ret = %d.\r\n", i4_ret));
            }
        }
            else
            {
                mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                            _mmp_pp_view_broadcast_file_msg,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL);
            }
        }
    }

    c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
}
#endif

/*----------------------------------------------------------------------------
 * Name: _mmp_pp_view_update_play_status
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pp_view_update_play_status(
    _MMP_PP_DATA_MEMBER_T*      pt_this,
    MMP_PLAY_STATE_T            e_status)
{
    MMP_IMG_IMAGE_ID_T          e_img_id;
    //INT32                       i4_ret;

    switch(e_status)
    {
    case MMP_PLAY_STATE_STOPPED:
        e_img_id = MMP_IMG_IMAGE_ID_STATUS_BAR_PAUSE;
        pt_this->e_label_state = _MMP_LABEL_STATE_PAUSE;
        _mmp_pp_view_update_label(pt_this);
        break;
    case MMP_PLAY_STATE_PAUSED:
        e_img_id = MMP_IMG_IMAGE_ID_STATUS_BAR_PAUSE;
        pt_this->e_label_state = _MMP_LABEL_STATE_PAUSE;
        _mmp_pp_view_update_label(pt_this);
        break;
    case MMP_PLAY_STATE_PLAYED:
        e_img_id = MMP_IMG_IMAGE_ID_STATUS_BAR_PLAY;
        pt_this->e_label_state = _MMP_LABEL_STATE_PLAY;
        _mmp_pp_view_update_label(pt_this);
        break;
    default:
        MMP_ASSERT(0);
        return;
    }

    DBG_INFO(("e_img_id=%d\n", (int)e_img_id));

#if 0//def MMP_GUI_AUTHORING_TB
    i4_ret = mmp_common_ui_toolbar_cmd_do(pt_ptb_inst,
                                          MMP_PP_TB_CMD_SET_PLAY_STATUS,
                                          (VOID*)(e_img_id == MMP_IMG_IMAGE_ID_STATUS_BAR_PLAY?MMP_PP_TB_STATUS_PLAY:MMP_PP_TB_STATUS_PAUSE),
                                          MMP_TB_SYNC_REPAINT);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_common_ui_toolbar_cmd_do(MMP_PP_TB_CMD_SET_PLAY_STATUS) fail. i4_ret = %d.\r\n", i4_ret));
        return;
    }
#else
#if 0
    /*get image*/
    i4_ret = mmp_img_get_img(e_img_id, &t_img_info.u_img_data.t_standard.t_enable);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_img_get_img(%d) fail. i4_ret = %d.\r\n", i4_ret, e_img_id));
        return;
    }

    /*set image*/
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = t_img_info.u_img_data.t_standard.t_enable;
    i4_ret = c_wgl_do_cmd(pt_this->t_view.t_statusbar.h_status_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));

    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_GL_SET_IMAGE) fail. i4_ret = %d.\r\n", i4_ret));
        return;
    }
    c_wgl_repaint(pt_this->t_view.t_statusbar.h_status_icon, NULL, TRUE);
    #endif
#endif

    /**/
    if(MMP_PLAY_STATE_PLAYED == e_status)
    {
        pt_this->ui4_flag |= _MMP_PP_FLAG_PLAY;
    }
    else
    {
        pt_this->ui4_flag &= ~(_MMP_PP_FLAG_PLAY);
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_activate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_activate(
    _MMP_PP_DATA_MEMBER_T*      pt_this)
{
    INT32                       i4_ret;
    /*MMP_PL_ATTR_T             at_attr[1];*/
    SIZE_T                      z_size;
    MMP_REPEAT_MODE_T           e_repeat_mode;
    MMP_PL_ATTR_T               at_attr[1];

    z_size = sizeof(MMP_REPEAT_MODE_T);
    mmp_mc_list_get_attr(MMP_PL_ATTR_ID_FG_REPEAT, &z_size, &e_repeat_mode);


    pt_this->e_repeat_mode = MMP_REPEAT_MODE_ALL;
    at_attr[0].e_id = MMP_PL_ATTR_ID_FG_REPEAT;
    at_attr[0].pv_param = (VOID*)(pt_this->e_repeat_mode);
    mmp_mc_list_set_attr(1, at_attr);


    /*show status bar*/
#if 1//def MMP_GUI_AUTHORING_TB

    //mmp_common_ui_toolbar_view_active(pt_ptb_inst, MMP_TB_NON_REPAINT);
#else
    c_wgl_set_visibility(pt_this->t_view.t_statusbar.h_bar, WGL_SW_RECURSIVE);

    /* hide the read only icon*/
    c_wgl_set_visibility(pt_this->t_view.t_statusbar.h_read_only_icon, WGL_SW_HIDE);
#endif
    if(_MMP_LABEL_STATE_PLAY == pt_this->e_label_state)
    {
    _mmp_pp_view_update_play_status(pt_this, MMP_PLAY_STATE_PLAYED);
    }
    else if(_MMP_LABEL_STATE_PAUSE== pt_this->e_label_state)
    {
        _mmp_pp_view_update_play_status(pt_this, MMP_PLAY_STATE_PAUSED);
    }
    else
    {
        MMP_ASSERT(0);
    }

    /* Update file index */
    _mmp_pp_view_update_fileidx(pt_this, MMP_PL_IDX_TYPE_CRNT_PLAY, FALSE);

    /*hide detail page*/
#ifdef MMP_GUI_AUTHORING_DP
    mmp_com_ui_dp_view_inactive(pt_pdp_inst);
#else
    c_wgl_set_visibility(pt_this->t_view.t_detailpage.h_page, WGL_SW_HIDE);
#endif

    /**/
    i4_ret = c_wgl_show(pt_this->t_view.h_frame, WGL_SW_NORMAL);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_show() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_focus() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    pt_this->e_info_state   = _MMP_INFO_STATE_SIMPLE;
   // _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_switch_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_switch_info(
    _MMP_PP_DATA_MEMBER_T*      pt_this,
    _MMP_INFO_STATE_T           e_new_state)
{
    HANDLE_T                    h_widget = NULL_HANDLE;
    HANDLE_T                    h_view_item;
    INT32                        i4_ret;
    GL_RECT_T                   t_rect ={0};

    if(e_new_state == pt_this->e_info_state)
    {
        return MMPR_OK;
    }

    if(FALSE == pt_this->b_pp_view_active)
    {
        return MMPR_OK;
    }

    if(_MMP_INFO_STATE_NEXT == e_new_state)
    {
        switch(pt_this->e_info_state)
        {
        case _MMP_INFO_STATE_SIMPLE:
            e_new_state = _MMP_INFO_STATE_DETAIL;
            break;
        case _MMP_INFO_STATE_DETAIL:
            break;
        case _MMP_INFO_STATE_NONE:
             e_new_state = _MMP_INFO_STATE_SIMPLE;
            break;
        case _MMP_INFO_STATE_POP_UP:
            h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
            IS_MMPR_OK (c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE));

            t_rect.i4_left   = MMP_PHOTO_POP_UP_LEFT-MMP_PHOTO_POP_UP_OFFICE;
            t_rect.i4_top    = MMP_PHOTO_POP_UP_TOP;
            t_rect.i4_right  = MMP_PHOTO_POP_UP_LEFT + MMP_PHOTO_POP_UP_WIDTH;
            t_rect.i4_bottom = MMP_PHOTO_POP_UP_TOP + MMP_PHOTO_POP_UP_HIGHT;
            IS_MMPR_OK(c_wgl_move(h_view_item,
                         &t_rect,
                         FALSE));
            c_wgl_repaint(h_view_item,NULL,TRUE);
            e_new_state =_MMP_INFO_STATE_DETAIL;
            break;
        default:
            e_new_state =_MMP_INFO_STATE_DETAIL;// _MMP_INFO_STATE_SIMPLE;
            break;
        }
    }

    switch(e_new_state)
    {
    case _MMP_INFO_STATE_SIMPLE:

        mmp_com_ui_dp_view_active(pt_pdp_inst);
        return _mmp_pp_view_activate(pt_this);
        break;
    case _MMP_INFO_STATE_DETAIL:
        {

            e_new_state = _MMP_INFO_STATE_DETAIL;

            mmp_com_ui_dp_view_active(pt_pdp_inst);
        }
        break;
    case _MMP_INFO_STATE_POP_UP:

        break;

    case _MMP_INFO_STATE_NONE:
    default:
        {
            //mmp_common_ui_toolbar_view_inactive(pt_ptb_inst, MMP_TB_NON_REPAINT);

            mmp_com_ui_dp_view_inactive(pt_pdp_inst);

            c_wgl_set_visibility(pt_this->t_view.h_optl, WGL_SW_HIDE);

            e_new_state = _MMP_INFO_STATE_NONE;
            h_widget = pt_this->t_view.h_frame;
            i4_ret = c_wgl_repaint(h_widget, NULL, TRUE);
            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_show() fail. i4_ret = %d.\r\n", i4_ret));
                return MMPR_FAIL;
            }
            c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
        }
        break;
    }

    pt_this->e_info_state    = e_new_state;
    if(_MMP_INFO_STATE_NONE != e_new_state)
    {
        //_mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
    }
    else
    {
        i4_ret = c_wgl_set_focus(pt_this->t_view.h_frame, FALSE);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_set_focus() fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }

        pt_this->ui4_flag &= ~(_MMP_PP_FLAG_TFX_LB_SHOW | _MMP_PP_FLAG_ZOOM_LB_SHOW | _MMP_PP_FLAG_DUR_LB_SHOW);
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_rotate_left
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_rotate_left(
    _MMP_PP_DATA_MEMBER_T*      pt_this)
{
    return _mmp_pp_rotate_image(pt_this, FALSE);
}


/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_rotate_right
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_rotate_right(
    _MMP_PP_DATA_MEMBER_T*      pt_this)
{
    return _mmp_pp_rotate_image(pt_this, TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_pp_random_effect
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_random_effect (_MMP_PP_DATA_MEMBER_T* pt_this)
{
    INT32   i4_ret = -1;

    if(MMP_PP_RC_TLB_ELEM_COUNT - 1 == pt_this->ui4_tfx_idx ||  MMP_PP_RC_TLB_NONE_MODE == pt_this->ui4_tfx_idx)
    {
        i4_ret = _mmp_pp_view_do_effect (pt_this, MMP_PP_RC_TLB_ELEM_COUNT - 1);
        return i4_ret;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_do_zoom
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_do_zoom(
    _MMP_PP_DATA_MEMBER_T*      pt_this,
    UINT32                      ui4_idx)
{
    UINT32                      ui4_zoom;
    GL_POINT_T                  t_center = {0, 0};

    /**/
    MMP_PP_RC_ZLB_GET_ZOOM(ui4_idx, ui4_zoom);

    return mmp_pe_play_zoom(&t_center, ui4_zoom);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_rand
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static UINT32 _mmp_pp_rand(VOID)
{
    static UINT32 ui4_mul = 97;
    static UINT32 ui4_add = 33;
    static UINT32 ui4_seed = 12345;

    ui4_seed = ui4_seed * ui4_mul + ui4_add;

    return ui4_seed;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_do_effect
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_do_effect(
    _MMP_PP_DATA_MEMBER_T*      pt_this,
    UINT32                      ui4_idx)
{
    IMG_TFX_EFFECT_T            e_effect;
    MMP_PL_ATTR_T               t_attr;
    MMP_EFFECT_T                t_effect;

    /**/
    t_attr.e_id = MMP_PL_ATTR_ID_EFFECT;
    t_attr.pv_param = &t_effect;

    /*effect none*/
    if(0 == ui4_idx)
    {
        MMP_PP_RC_TLB_GET_EFFECT((_mmp_pp_rand()%7) + 1, e_effect);

        t_effect.b_is_enabled = TRUE;
        t_effect.e_effect = e_effect;
        //t_effect.b_is_enabled = FALSE;
        //t_effect.e_effect = TFX_WIPE_LEFT;

    }
    /*effect random*/
    else if(MMP_PP_RC_TLB_ELEM_COUNT - 1 == ui4_idx)
    {
        MMP_PP_RC_TLB_GET_EFFECT((_mmp_pp_rand()%7) + 1, e_effect);

        t_effect.b_is_enabled = TRUE;
        t_effect.e_effect = e_effect;
    }
    else
    {
        MMP_PP_RC_TLB_GET_EFFECT(ui4_idx, e_effect);

        t_effect.b_is_enabled = TRUE;
        t_effect.e_effect = e_effect;
    }

    return mmp_mc_list_set_attr(1, &t_attr);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_do_duration
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_do_duration(
    _MMP_PP_DATA_MEMBER_T*      pt_this,
    UINT32                      ui4_idx)
{
    MMP_PL_ATTR_T               t_attr;
    UINT32                      ui4_dur;

    /**/
    MMP_PP_RC_DLB_GET_DUR(ui4_idx, ui4_dur);

    /**/
    t_attr.e_id = MMP_PL_ATTR_ID_DURATION;
    t_attr.pv_param = (VOID*)ui4_dur;

    return mmp_mc_list_set_attr(1, &t_attr);
}


/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_reset_hide_timer
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pp_view_reset_hide_timer(
    _MMP_PP_DATA_MEMBER_T*      pt_this,
    MMP_TIMER_OP_TYPE_T         e_op)
{
    INT32                       i4_ret;

    if(_MMP_PLAY_STATE_NONE == pt_this->e_play_state)
    {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if(OSR_OK != i4_ret)
    {
        ABORT_APPL(DBG_MOD_PHOTO, ("stop Hide-Timer failed!"));
    }

    if(MMP_TIMER_OP_TYPE_STOP == e_op)
    {
        return;
    }

    i4_ret = c_timer_start(pt_this->h_hide_timer,
                           MMP_PP_RC_AUTOHIDE_DUR,
                           X_TIMER_FLAG_ONCE,
                           _mmp_pp_view_hide_timer_cb,
                           NULL);
    if(OSR_OK != i4_ret)
    {
        ABORT_APPL(DBG_MOD_PHOTO, ("start Hide-Timer failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_pp_view_hide_timer_cb
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _mmp_pp_view_hide_timer_cb(
    HANDLE_T                    h_timer,
    VOID*                       pv_unused)
{
    /*post a message to itself*/
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                _mmp_pp_view_hide_timer_event_handler,
                                NULL,
                                NULL,
                                NULL,
                                NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_pp_view_hide_timer_event_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _mmp_pp_view_hide_timer_event_handler(
    VOID*                       pv_unused1,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3,
    VOID*                       pv_unused4)
{
    _MMP_PP_DATA_MEMBER_T*      pt_this = &t_g_pp;

    pt_this->e_play_state = _MMP_PLAY_STATE_NONE;
    c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);

    //_mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_NONE);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_main_frm_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_main_frm_proc_fct(
    HANDLE_T                    h_frm_main,
    UINT32                      ui4_msg,
    VOID*                       pv_param1,
    VOID*                       pv_param2)
{
    _MMP_PP_DATA_MEMBER_T*      pt_this;
    UINT32                      ui4_key_code;
    BOOL                        b_reset_timer = FALSE;
    BOOL                        b_wake_ui = FALSE;
    INT32                       i4_ret=MMPR_OK;
    HANDLE_T                    h_view_item;
    UINT32                      ui4_slideshow_idx = MMP_NULL_FILE_IDX;

    if(WGL_MSG_KEY_DOWN == ui4_msg)
    {
        pt_this = &t_g_pp;
        ui4_key_code = (UINT32)pv_param1;

        DBG_INFO_DIRECT("[mmp pp] %s %d ui4_key_code:%d \r\n",__FUNCTION__,__LINE__,ui4_key_code);

        switch(ui4_key_code)
        {

        case MMP_PP_RC_KEY_PHO_PLAY:
            if(pt_this->e_play_state == _MMP_PLAY_STATE_PLAY)
            {
                break;
            }

            else
            {
                pt_this->e_play_state = _MMP_PLAY_STATE_PLAY;
                c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
                c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_NORMAL);
                //mmp_mc_list_play(MMP_GROUND_MODE_FORE, MMP_PLAY_IDX_CURRENT);
                _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                i4_ret = mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX_CRT,
                                        pt_this->ui4_current_fileidx + 1,
                                        &ui4_slideshow_idx);

                if ((MMPR_OK == i4_ret) && (MMP_NULL_FILE_IDX != ui4_slideshow_idx))
                {
                #ifdef APP_TTS_SUPPORT
                    UTF16_T         w2s_str[128] = {0};
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif
                    mmp_mc_list_play(MMP_GROUND_MODE_FORE, ui4_slideshow_idx);
                }
                break;
            }
        case MMP_PP_RC_KEY_PHO_PAUSE:
            if(pt_this->e_play_state == _MMP_PLAY_STATE_PAUSE)
            {
                break;
            }

            else
            {
                pt_this->e_play_state = _MMP_PLAY_STATE_PAUSE;
                c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
                c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_NORMAL);
                b_reset_timer = TRUE;
            #ifdef APP_TTS_SUPPORT
                UTF16_T         w2s_str[128] = {0};
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
            #endif
                mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                b_wake_ui = TRUE;
                break;
            }
        // case MMP_PP_RC_KEY_BROWSE://BTN_EXIT
        case BTN_RETURN:
        case BTN_STOP:
            pt_this->e_play_state = _MMP_PLAY_STATE_NONE;
            c_wgl_show(pt_this->t_view.h_pause_icon, WGL_SW_HIDE);
            c_wgl_show(pt_this->t_view.h_play_icon, WGL_SW_HIDE);
            h_view_item = mmp_pop_up_photo_get_wgt_hdl(WID_MMP_POP_UP_PHOTO_FRM_POP_UP_BASE_FRM);
           c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
           i4_ret = c_wgl_repaint(h_view_item,NULL,TRUE);
            mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
            break;

        case MMP_PP_RC_KEY_NEXT://BTN_PRG_UP
        case MMP_PP_RC_KEY_PREV://BTN_PRG_DOWN
        case MMP_PP_RC_KEY_PLAY_NEXT:
        case MMP_PP_RC_KEY_PLAY_PREV:
        case BTN_PREV:
        case BTN_NEXT:
            {
                INT32                       i4_ret;
                SIZE_T                      z_size;
                BOOL                        b_is_ready;

                //_mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);

                if(_MMP_INFO_STATE_NONE == pt_this->e_info_state)
                {
                    _mmp_pp_view_switch_info(pt_this,_MMP_INFO_STATE_SIMPLE/*_MMP_INFO_STATE_NEXT*/);
                }

                /* Hide not support text */
                _mmp_pp_view_close_msgbox();
                c_wgl_show(pt_this->t_view.h_not_show_file_title,WGL_SW_HIDE);

                /*get file status*/
                z_size = sizeof(BOOL);
                i4_ret = mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_CURRENT,
                                                         MMP_PE_EXTRA_INFO_ID_IS_READY,
                                                         &z_size,
                                                         &b_is_ready);

                MMP_DBG_INFO(("[mmp] %s %d\
                            \r\n z_size = %d.\
                            \r\n b_is_ready = %d. \
                            \r\n i4_ret = %d. \
                            \r\n ui4_key_code = %d. \
                            \r\n",\
                            __FUNCTION__,\
                            __LINE__,\
                            z_size,\
                            b_is_ready,\
                            i4_ret,\
                            ui4_key_code));

                if(MMPR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("mmp_pe_play_get_file_extra_info(MMP_PE_EXTRA_INFO_ID_IS_READY) fail. i4_ret = %d.\r\n", i4_ret));
                    return i4_ret;
                }

                if(b_is_ready)
                {
                    if((MMP_PP_RC_KEY_NEXT == ui4_key_code)||(MMP_PP_RC_KEY_PLAY_NEXT == ui4_key_code) ||( BTN_NEXT == ui4_key_code ))
                    {
                        i4_ret = mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX_CRT,
                                        pt_this->ui4_current_fileidx,
                                        &ui4_slideshow_idx);
                        MMP_DBG_INFO(("[mmp] %s %d\
                                    \r\n ui4_slideshow_idx = %d.\
                                    \r\n i4_ret = %d. \
                                    \r\n",\
                                    __FUNCTION__,\
                                    __LINE__,\
                                    ui4_slideshow_idx,\
                                    i4_ret));
                        if ((MMPR_OK == i4_ret) && (MMP_NULL_FILE_IDX != ui4_slideshow_idx))
                        {
                             mmp_mc_list_next(MMP_GROUND_MODE_FORE);
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        i4_ret = mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX_CRT,
                                        pt_this->ui4_current_fileidx,
                                        &ui4_slideshow_idx);

                        if ((MMPR_OK == i4_ret) && (MMP_NULL_FILE_IDX != ui4_slideshow_idx))
                        {
                             mmp_mc_list_previous(MMP_GROUND_MODE_FORE);
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                /* Recover zoom to 1X while play next picture */
                pt_this->ui4_zoom_idx = 0;
            }
            break;

        case MMP_PP_RC_KEY_DETAIL://BTN_PRG_INFO
            if(pt_this->e_info_state == _MMP_INFO_STATE_POP_UP)
            {
                pt_this->e_info_state =_MMP_INFO_STATE_POP_UP_THEN_DETAIL;
                _mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_NEXT);

            }

            else if(pt_this->e_info_state ==_MMP_INFO_STATE_DETAIL)
            {
                mmp_com_ui_dp_view_inactive(pt_pdp_inst);
                pt_this->e_info_state = _MMP_INFO_STATE_SIMPLE;
            }

            else
            {
                 mmp_com_ui_dp_view_active(pt_pdp_inst);//_mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_NEXT);
                 pt_this->e_info_state = _MMP_INFO_STATE_DETAIL;
            }

            break;

        case MMP_PP_RC_KEY_OPTION://BTN_MENU
            if(_MMP_INFO_STATE_NONE == pt_this->e_info_state)
            {
                _mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_SIMPLE);
            }
            {
                //_mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);

                if(_MMP_INFO_STATE_DETAIL == pt_this->e_info_state)
                {
#ifdef MMP_GUI_AUTHORING_DP
                    mmp_com_ui_dp_view_inactive(pt_pdp_inst);
#else
                    c_wgl_set_visibility(pt_this->t_view.t_detailpage.h_page,
                                         WGL_SW_HIDE);
#endif
                    pt_this->e_info_state = _MMP_INFO_STATE_SIMPLE;

                    a_optl_set_visibility(pt_this->t_view.h_optl, TRUE);

                    a_optl_set_focus(pt_this->t_view.h_optl);

                    _mmp_pp_opt_set_item(pt_this->e_label_state);

                    a_optl_repaint(pt_this->t_view.h_optl);

                    c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
                }
                else
                {
                    _mmp_pp_opt_set_item(pt_this->e_label_state);
                    a_optl_show(pt_this->t_view.h_optl);
                }
            }
            break;

        case BTN_INPUT_SRC:
            break;

        case BTN_EXIT:
        case BTN_RED:
            {
               i4_ret = mmp_be_pause_mmp();
               return i4_ret;
            }
            break;

        default:
            {
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
                INT32 i4_ret;
#endif
                b_reset_timer = FALSE;
                if(_MMP_PP_FLAG_PLAY & pt_this->ui4_flag)
                {
                    switch(ui4_key_code)
                    {

                    case MMP_PP_RC_KEY_PAUSE:
                        b_reset_timer = FALSE;//b_reset_timer = TRUE;
                        if(pt_this->e_info_state == _MMP_INFO_STATE_DETAIL)
                        {
                            pt_this->e_info_state = _MMP_INFO_STATE_DETAIL_THEN_POP_UP;

                        }
                        else if(pt_this->e_info_state == _MMP_INFO_STATE_SIMPLE)
                        {
                            pt_this->e_info_state = _MMP_INFO_STATE_POP_UP;
                        }

                        pt_this->e_state_change_flag = _MMP_INFO_CHANGE;
                    #ifdef APP_TTS_SUPPORT
                        UTF16_T         w2s_str[128] = {0};
                        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    #endif
                        mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                        _mmp_pp_pop_up_page_show(pt_this);
                        b_wake_ui = TRUE;
                        break;
                    case MMP_PP_RC_KEY_TFX://BTN_YELLOW
                        #if 0
                        _mmp_pp_view_update_tfx(pt_this);
                        //_mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                        b_wake_ui = TRUE;
                        #endif

                        break;
                    case MMP_PP_RC_KEY_TIME://BTN_GREEN
                        #if 0
                        _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                        b_wake_ui = TRUE;
                        #endif
                        break;
#ifdef APP_CAPTURE_LOGO_SUPPORT
                    case MMP_PP_RC_KEY_CAPTURE://BTN_RECORD
                        if(FALSE == pt_this->b_is_notsupport_show )
                        {
                            b_reset_timer           = TRUE;
                            pt_this->b_pause_by_cap = TRUE;

                            mmp_mc_list_pause(MMP_GROUND_MODE_FORE);

                            a_cap_capture(pt_this->pv_cap);
                        }
                        break;
#endif
                    default:
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
                        {
                            i4_ret = mmp_mc_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
                            if(i4_ret == MMPR_NO_DATA)
                            {
                                break;
                            }
                            else
                            {
                                return i4_ret;
                            }
                        }
#else
                        break;
#endif
                    }
                }
                else
                {
                    switch(ui4_key_code)
                    {

                     case MMP_PP_RC_KEY_PLAY://BTN_SELECT
                        //b_reset_timer = TRUE;
                        //mmp_mc_list_play(MMP_GROUND_MODE_FORE, MMP_PLAY_IDX_CURRENT);
                        //_mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                        if(pt_this->e_info_state == _MMP_INFO_STATE_DETAIL)
                        {
                            pt_this->e_info_state = _MMP_INFO_STATE_DETAIL_THEN_POP_UP;

                        }
                        else if(pt_this->e_info_state == _MMP_INFO_STATE_SIMPLE)
                        {
                            pt_this->e_info_state = _MMP_INFO_STATE_POP_UP;
                        }

                        pt_this->e_state_change_flag = _MMP_INFO_CHANGE;
                    #ifdef APP_TTS_SUPPORT
                        UTF16_T         w2s_str[128] = {0};
                        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    #endif
                        mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                        _mmp_pp_pop_up_page_show(pt_this);
                        b_wake_ui = TRUE;
                        break;
                    case MMP_PP_RC_KEY_ZOOM://BTN_YELLOW
                        #if 0
                        if(FALSE == pt_this->b_is_notsupport_show )  /* If not support, don't apply zoom */
                        {
                            _mmp_pp_view_update_zoom(pt_this);
                        }
                        //_mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                        b_wake_ui = TRUE;
                        #endif
                        break;
                    case MMP_PP_RC_KEY_ROTATE://BTN_GREEN
                    #if 0
                        b_reset_timer = TRUE;
                        if( FALSE == pt_this->b_is_notsupport_show )  /* If not support, don't apply rotate */
                        {
                            _mmp_pp_view_rotate_right(pt_this);
                        }
                        b_wake_ui = TRUE;
                    #endif
                        break;
#ifdef APP_CAPTURE_LOGO_SUPPORT
                    case MMP_PP_RC_KEY_CAPTURE://BTN_RECORD
                        if(FALSE == pt_this->b_is_notsupport_show )
                        {
                            b_reset_timer           = TRUE;
                            a_cap_capture(pt_this->pv_cap);
                        }
                        break;
#endif
                    default:
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
                    {
                        i4_ret = mmp_mc_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
                        if(i4_ret == MMPR_NO_DATA)
                        {
                            break;
                        }
                        else
                        {
                            return i4_ret;
                        }
                    }
#else
                        break;
#endif
                    }
                }

                if(b_wake_ui)
                {
                    if(_MMP_INFO_STATE_NONE == pt_this->e_info_state)
                    {
                        _mmp_pp_view_switch_info(pt_this, _MMP_INFO_STATE_SIMPLE);
                    }
                }

                if(b_reset_timer)
                {
                   // _mmp_pp_view_reset_hide_timer(pt_this, MMP_TIMER_OP_TYPE_RESET);
                }
            }
            break;
        }
    }
    else if(WGL_MSG_NOTIFY == ui4_msg)
    {
        /*HANDLE_T                h_source;*/
        WGL_NOTIFY_DATA_T*      pt_nfy_data = (WGL_NOTIFY_DATA_T*)pv_param2;

        do
        {
            pt_this = &t_g_pp;

            /*check if selection notification*/
            if(WGL_NC_LB_ELEM_PUSH != pt_nfy_data->ui4_nc_code)
            {
                break;
            }

            /*check if selected notification*/
            if(FALSE == pt_nfy_data->u.t_lb_elem_push.b_is_pushed)
            {
                break;
            }
        } while(0);

    }

    return c_wgl_default_msg_proc(h_frm_main, ui4_msg, pv_param1, pv_param2);
}
#if 0

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_update_tfx
 *
 * Description: update the tfx, along with the label and index
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_update_tfx(
   _MMP_PP_DATA_MEMBER_T*      pt_this)
{
    pt_this->ui4_tfx_idx++;
    if(  pt_this->ui4_tfx_idx >= MMP_PP_RC_TLB_ELEM_COUNT )
    {
        pt_this->ui4_tfx_idx = 0;
    }
    _mmp_pp_view_do_effect( pt_this, pt_this->ui4_tfx_idx );
    c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
    return MMPR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_update_zoom
 *
 * Description: update the zoom, along with the label and index
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_update_zoom(
   _MMP_PP_DATA_MEMBER_T*      pt_this)
{
    INT32   i4_ret;
    if(MMP_PP_RC_IS_QUICK_ROTATE())
    {
        pt_this->ui4_zoom_idx++;
        if(  pt_this->ui4_zoom_idx >= MMP_PP_RC_ZLB_ELEM_COUNT )
        {
            pt_this->ui4_zoom_idx = 0;
        }

        i4_ret = _mmp_pp_view_do_zoom( pt_this, pt_this->ui4_zoom_idx );

        if( i4_ret >= 0 )  /* Zoom Successfully */
        {
           // c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
        }
        else
        {
            /* Zoom fail, we should roll back the increment of zoom index */
            if( pt_this->ui4_zoom_idx > 0 )
            {
                pt_this->ui4_zoom_idx--;
            }
            else
            {
                pt_this->ui4_zoom_idx = MMP_PP_RC_ZLB_ELEM_COUNT-1;
            }

            MMP_DBG_ERROR(("_mmp_pp_view_do_zoom fail. i4_ret = %d.\r\n", i4_ret));
        }
    }

    return MMPR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_update_repeat_label
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pp_view_update_repeat_label(
    _MMP_PP_DATA_MEMBER_T*      pt_this)
{
    INT32                       i4_ret = -1;
    UINT32                      ui4_repeat_idx = 0;

    switch(pt_this->e_repeat_mode)
    {
        case MMP_REPEAT_MODE_NONE:
            ui4_repeat_idx = 0;
            break;
        case MMP_REPEAT_MODE_ONE:
            ui4_repeat_idx = 1;
            break;
        case MMP_REPEAT_MODE_ALL:
            ui4_repeat_idx = 2;
            break;
        default:
            ui4_repeat_idx = 0;
    }

    DBG_INFO(("ui4_repeat_idx=%d\n", ui4_repeat_idx));

    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_TEXT_SET_TEXT) fail. i4_ret = %d.\r\n", i4_ret));
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_update_shuffle_label
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pp_view_update_shuffle_label(
    _MMP_PP_DATA_MEMBER_T*      pt_this)
{
    INT32                       i4_ret = -1;
    UINT32                      ui4_shuffle_idx = 0;

    switch(pt_this->e_shuffle_mode)
    {
        case MMP_SHUFFLE_MODE_SEQUENTIAL:
            ui4_shuffle_idx = 0;
            break;
        case MMP_SHUFFLE_MODE_SHUFFLE:
            ui4_shuffle_idx = 1;
            break;
        default:
            ui4_shuffle_idx = 0;
            break;
    }

    DBG_INFO(("ui4_shuffle_idx=%d\n", ui4_shuffle_idx));

    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_TEXT_SET_TEXT) fail. i4_ret = %d.\r\n", i4_ret));
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_update_label
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_pp_view_update_label(
    _MMP_PP_DATA_MEMBER_T*      pt_this)
{
    GL_RECT_T                   t_rect;

    switch(pt_this->e_label_state)
    {
        case _MMP_LABEL_STATE_PLAY:
            SET_RECT_BY_SIZE( &t_rect, TXT_PP_SB_3_X, TXT_PP_SB_Y, TXT_PP_SB_L_VAL_W, TXT_PP_SB_H );
            _mmp_pp_view_update_repeat_label(pt_this);
            _mmp_pp_view_update_shuffle_label(pt_this);
            c_wgl_set_visibility(pt_this->t_view.t_statusbar.ah_label[MMP_PP_RC_SB_LBL_ID_DUR], WGL_SW_NORMAL);
            c_wgl_set_visibility(pt_this->t_view.t_statusbar.ah_label[MMP_PP_RC_SB_LBL_ID_ZOOM], WGL_SW_HIDE);
            c_wgl_set_visibility(pt_this->t_view.t_statusbar.ah_label[MMP_PP_RC_SB_LBL_ID_TFX], WGL_SW_NORMAL);
            c_wgl_move(pt_this->t_view.t_statusbar.ah_label[MMP_PP_RC_SB_LBL_ID_FILE_NAME], &t_rect, WGL_NO_AUTO_REPAINT );
            break;
        case _MMP_LABEL_STATE_PAUSE:
            SET_RECT_BY_SIZE( &t_rect, TXT_PP_SB_2_X, TXT_PP_SB_Y, TXT_PP_SB_L_VAL_W, TXT_PP_SB_H );
            //mmp_pp_view_update_tfx_label(pt_this);
            _mmp_pp_view_update_repeat_label(pt_this);
            _mmp_pp_view_update_shuffle_label(pt_this);
            c_wgl_set_visibility(pt_this->t_view.t_statusbar.ah_label[MMP_PP_RC_SB_LBL_ID_DUR], WGL_SW_HIDE);
            c_wgl_set_visibility(pt_this->t_view.t_statusbar.ah_label[MMP_PP_RC_SB_LBL_ID_ZOOM], WGL_SW_NORMAL);
            c_wgl_set_visibility(pt_this->t_view.t_statusbar.ah_label[MMP_PP_RC_SB_LBL_ID_TFX], WGL_SW_HIDE);
            c_wgl_move(pt_this->t_view.t_statusbar.ah_label[MMP_PP_RC_SB_LBL_ID_FILE_NAME], &t_rect, WGL_NO_AUTO_REPAINT );
            break;
        default:
            break;
    }
    /*c_wgl_repaint(pt_this->t_view.t_statusbar.h_bar, NULL, TRUE);*/
    c_wgl_repaint(pt_this->t_view.h_frame, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_create_optl
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_create_optl(HANDLE_T    h_parent,
                                    HANDLE_T*   ph_optl)
{
    INT32                i4_ret = -1;
    OPTL_INIT_T          t_pp_optl_init;

    c_memset(&t_pp_optl_init, 0, sizeof(OPTL_INIT_T));

    t_pp_optl_init.h_parent = h_parent;
    t_pp_optl_init.t_gui_rc.i4_left = OPTION_LIST_LEFT;
    t_pp_optl_init.t_gui_rc.i4_top  = OPTION_LIST_TOP;
    t_pp_optl_init.ui4_style_mask   = 0;
    t_pp_optl_init.pv_tag = NULL;
    t_pp_optl_init.pf_fct = _pp_optl_cb_fac;
    t_pp_optl_init.ui4_custom_flag = 0;
    t_pp_optl_init.ui4_sleep_time = 0000;

    i4_ret = a_optl_create(&t_pp_optl_init, ph_optl);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_create_detail_page
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static UINT16 _mmp_pp_get_mlm_lang_id(VOID)
{
    INT32                       i4_ret;
    ISO_639_LANG_T              s639_lang;
    UINT16                      ui2_lang_id;

    i4_ret = a_cfg_get_gui_lang(s639_lang);

    if(i4_ret != APP_CFGR_OK)
    {
        MMP_DBG_ERROR(("a_cfg_get_gui_lang() fail. i4_ret = %d.\r\n", i4_ret));
        ui2_lang_id =0;
    }
    else
    {
        ui2_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
    }

    return ui2_lang_id;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_sb_update_fileidx
 *
 * Description: update the file index on the status bar.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_update_fileidx(
    _MMP_PP_DATA_MEMBER_T*       pt_this,
    MMP_PL_IDX_TYPE_T            e_idx_type,
    BOOL                         b_repaint)
{
    UINT32                         z_buf_size;
    //UTF16_T                     *ws_display = NULL;

    CHAR                        s_buf[MMP_PP_RC_STR_MAX_LEN + 1], *ps_buf;
    INT32                       i4_ret, i4_ret2;
    UTF16_T                       ws_buf[MMP_PP_RC_STR_MAX_LEN + 1];

    i4_ret2 = mmp_mc_list_get_item_count(MMP_GROUND_MODE_FORE, &pt_this->ui4_total_fileidx );
    i4_ret = mmp_mc_list_get_idx(MMP_GROUND_MODE_FORE, e_idx_type,  &pt_this->ui4_current_fileidx );
    if(MMPR_OK != i4_ret || MMPR_OK != i4_ret2)
    {
        MMP_DBG_ERROR(("mmp_mc_list_get_item_count(MMP_GROUND_MODE_FORE) (ret = %d) or mmp_mc_list_get_idx(%d) (i4_ret = %d) fail.\r\n", i4_ret2, e_idx_type, i4_ret));
        //ws_display = NULL;
    }
    else
    {
        /* change info page : %d of %d text fix DTV00811927 case3 */
        //c_sprintf( s_buf, MMP_PP_RC_FILEIDX_FMT, (pt_this->ui4_current_fileidx + 1), pt_this->ui4_total_fileidx );

        CHAR            s_result[MMP_PP_RC_STR_MAX_LEN + 1] = {0};
        i4_ret = c_uc_w2s_to_ps(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_MMP_DP_INFO_TEMP),
                        s_result,
                        sizeof(s_result));

        MMPR_LOG_ON_FAIL(i4_ret);
        c_snprintf(s_buf,(SIZE_T)(MMP_PP_RC_STR_MAX_LEN + 1), s_result, (pt_this->ui4_current_fileidx + 1), pt_this->ui4_total_fileidx);

        ps_buf = s_buf;
        i4_ret = c_uc_ps_to_w2s(ps_buf, ws_buf, MMP_PP_RC_STR_MAX_LEN);
        if(UCR_OK != i4_ret)
        {
            //ws_display = NULL;
        }
        else
        {
            z_buf_size = c_strlen(ps_buf);
            ws_buf[z_buf_size] = (UTF16_T)0;
            //ws_display = ws_buf;
        }

        /*Check slideshow skip setting*/
        pt_this->b_crnt_file_skip = mmp_be_is_item_in_list(MMP_BE_FF_IDX_CRT,
                                                           ITEM_TYPE_FILE,
                                                           pt_this->ui4_current_fileidx,
                                                           MMP_FF_ITEM_LIST_TYPE_SKIP_LIST);
        if (pt_this->b_crnt_file_skip)
        {
            c_wgl_show(pt_this->t_view.h_skip_icon, WGL_SW_NORMAL);
        }
        else
        {
            c_wgl_show(pt_this->t_view.h_skip_icon, WGL_SW_HIDE);
        }


    }
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_open_msgbox
 *
 * Description: Open the message box.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_open_msgbox(MMP_PP_MSGBOX_TYPE_T   e_msg_type)
{
    INT32    i4_ret = -1;
    UINT16   ui2_lang_id = 0;
    UINT32   ui4_mlm_id = 0;

    if( e_msg_type >= MMP_PP_MSGBOX_TYPE_LAST_ITEM )
    {
        MMP_DBG_ERROR(("Wrong message box type = %d\r\n", e_msg_type));
        return MMPR_FAIL;
    }

    ui2_lang_id = _mmp_pp_get_mlm_lang_id();

    if( MMP_PP_MSGBOX_TYPE_NOT_SUPPPORT == e_msg_type )
    {
        ui4_mlm_id = MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT;
    }
    else if( MMP_PP_MSGBOX_TYPE_DECODE_FAIL == e_msg_type )
    {
        ui4_mlm_id = MLM_MMP_KEY_NFY_DECODE_FAIL;
    }
    else if( MMP_PP_MSGBOX_TYPE_NOT_EXIST == e_msg_type )
    {
        ui4_mlm_id = MLM_MMP_KEY_FILE_NOT_FOUND;
    }
    else if(MMP_PP_MSGBOX_TYPE_RESOLUTION_NOT_SUPPORT)
    {
        ui4_mlm_id = MLM_MMP_KEY_RES_NOT_SUPPORT;
    }

    else
    {
        MMP_DBG_ERROR(("Wrong message box type = %d\r\n", e_msg_type));
        return MMPR_FAIL;
    }

    t_g_pp.ui4_mlm_id = ui4_mlm_id;

    t_g_pp.b_is_notsupport_show = TRUE;
    ui4_msg_type = e_msg_type;

    i4_ret = mmp_info_bar_set_status_msg(MMP_IB_MSG_CLASS_INFO,
                                         MMP_IB_STATUS_MSG_TYPE_FILE_STATUS,
                                         MMP_IB_STATUS_MSG_ID_FILE_STATUS,
                                         MLM_MMP_TEXT(ui2_lang_id, ui4_mlm_id));

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_view_close_msgbox
 *
 * Description: Close the message box.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_view_close_msgbox(VOID)
{
    t_g_pp.b_is_notsupport_show = FALSE;

    return mmp_info_bar_hide();
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_get_force_rotate_op
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_get_force_rotate_op(const CHAR* ps_filename, MMP_FP_LOAD_IMG_ROTATE_OP_T* pe_force_rotate_op)
{
    CHAR                            s_full_path[MMP_BE_MAX_PATH_LEN] = {0};
    MMP_ITEM_INFO_T                 t_item_info = {0};
    MMP_FF_ITEM_FLAG_T              e_item_flag = MMP_FF_ITEM_FLAG_EMPTY;
    INT32                           i4_ret;
    UINT32                          ui4_i, ui4_cnt = 1, ui4_dir_num, ui4_file_num;

    if (NULL == ps_filename)
    {
        return MMPR_NO_DATA;
    }

    *pe_force_rotate_op = MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE;

    i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT, &ui4_dir_num, &ui4_file_num);
    if (MMPR_OK != i4_ret)
    {
        return MMPR_OK;
    }

    for (ui4_i = 0; ui4_i < ui4_file_num; ui4_i++)
    {
        i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                      ITEM_TYPE_FILE,
                                      ui4_i,
                                      &ui4_cnt,
                                      &t_item_info);
        if (MMPR_OK != i4_ret)
        {
            break;
        }
        MMP_BE_GET_FULL_ITEM_PATH(t_item_info, s_full_path);
        if (c_strcmp(s_full_path, ps_filename) == 0)
        {
            e_item_flag = t_item_info.e_flag;
            break;
        }
    }

    MMP_BE_RC_GET_MMP_ROTATE_FROM_ITEM_FLAG(e_item_flag, *pe_force_rotate_op);
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_pp_rotate_image
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_pp_rotate_image(_MMP_PP_DATA_MEMBER_T* pt_this, BOOL b_clockwise)
{
    UINT32                          ui4_cnt = 1;
    MMP_ITEM_INFO_T                 t_item_info = {0};
    MMP_FF_ITEM_FLAG_T              e_item_flag, e_rotate_flag = MMP_FF_ITEM_FLAG_EMPTY;
    SIZE_T                          z_size = sizeof(IMG_ROTATE_OP_TYPE_T);
    IMG_ROTATE_OP_TYPE_T            e_img_rotate = IMG_ROTATE_CLOCKWS_0_OP_TYPE;
    INT32                           i4_ret;

    i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                  ITEM_TYPE_FILE,
                                  pt_this->ui4_current_fileidx,
                                  &ui4_cnt,
                                  &t_item_info);
    if (MMPR_OK != i4_ret)
    {
        return MMPR_NOT_SUPPORT;
    }
    e_item_flag = t_item_info.e_flag;

    DBG_INFO_DIRECT("[mmp pp] %s %d e_item_flag:0x%x \r\n",__FUNCTION__,__LINE__,e_item_flag);

    if (0 == (MMP_BE_ITEM_FLAG_ROTATE & e_item_flag))
    {
        /*Apply file rotate info first*/
        i4_ret = mmp_pe_play_get_file_info(MMP_PE_FILE_IDX_CURRENT, MMP_FP_INFO_TYPE_ROTATION, &z_size, (UINT8*)&e_img_rotate);
        if(MMPR_OK != i4_ret)
        {
            e_img_rotate = IMG_ROTATE_CLOCKWS_0_OP_TYPE;
        }

        MMP_BE_RC_GET_ITEM_FLAG_FROM_ROTATE(e_img_rotate, e_rotate_flag)
        e_rotate_flag |= MMP_BE_ITEM_FLAG_ROTATE;

        e_item_flag |= e_rotate_flag;
    }

    /*Get current rotate from item flag*/
    MMP_BE_RC_GET_IMG_ROTATE_FROM_ITEM_FLAG(e_item_flag, e_img_rotate);

    /*Get next rotate type*/
    MMP_BE_RC_GET_NEXT_ROTATE(e_img_rotate, b_clockwise);

    DBG_INFO_DIRECT("[mmp pp] %s %d e_img_rotate:%d e_item_flag:0x%x \r\n",__FUNCTION__,__LINE__,e_img_rotate,e_item_flag);

    /*Perform rotate*/
    mmp_pe_play_rotate(e_img_rotate);

    /*Get new rotate flag*/
    e_rotate_flag = MMP_FF_ITEM_FLAG_EMPTY;
    MMP_BE_RC_GET_ITEM_FLAG_FROM_ROTATE(e_img_rotate, e_rotate_flag)

    /*Save back item flag*/
    MMP_BE_RC_APPLY_ROTATE_FLAG(e_item_flag, e_rotate_flag);
    mmp_be_set_item_status(ITEM_TYPE_FILE, pt_this->ui4_current_fileidx, e_item_flag);

    return MMPR_OK;
}

