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
 * $RCSfile: tuner_setup_view.c,v $
 * $Revision: #1 $
 * $Date: 2016/02/03 $
 * $Author: sin_fangyuan $
 * $CCRevision:  $
 * $SWAuthor: $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_common.h"
#include "u_sys_name.h"
#include "u_sm_audio_hdlr.h"
#include "u_svl.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_bdr_common.h"
#include "u_wgl_bdr_uniform.h"
#include "u_wgl_bdr_raised.h"
#include "u_wgl_tools.h"
#include "u_dbg.h"
#include "u_pcl.h"
#include "u_gl.h"
#include "u_net_wlan.h"
#include "u_wgl_text.h"
#include "u_sb_atsc_eng.h"
#include "u_sb_ntsc_eng.h"
#include "u_sb_cqam_eng.h"
#include "u_time_msrt_name.h"
#include "u_btn_map.h"
#include "u_sb.h"

#include "c_time_msrt.h"
#include "c_svl.h"
#include "c_sb.h"
#include "c_common.h"
#include "c_os.h"
#include "c_gl.h"
#include "c_uc_str.h"
#include "c_wgl_image.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_dbg.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_tsl.h"
#include "c_wgl.h"
#include "c_pcl.h"
#include "c_httpc_api.h"

#include "menu2/a_menu.h"

#include "agent/a_agent.h"
#include "app_util/a_common.h"
#include "app_util/a_key_seq.h"
#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "app_util/a_network.h"
#include "wizard/wzd_util.h"
#include "mmp/a_mmp.h"

#include "nav/nav_common.h"
#include "nav/dialog/nav_dialog.h"
#include "nav/tuner_setup/tuner_setup.h"
#include "nav/tuner_setup/tuner_setup_view.h"
#include "nav/tuner_setup/tuner_setup_cli.h"
#include "nav/input_src/input_src.h"
#include "nav/pop/a_pop.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "wdk/widget/wdk_widget.h"

#include "res/revolt/revolt_settings_mlm.h"
#include "res/revolt/revolt_warnings_mlm.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_colors.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/network/network_custom.h"
#include "wizard_anim/a_wzd.h"
#include "res/nav/one_channel_list/ocl.h"

#include "rest/a_rest_event.h"
#include "rest/rest.h"

#include "res/app_util/icl/a_icl_custom.h"

#include "c_httpc_api.h"
#include "am/a_am.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "res/nav/nav_dbg.h"
#include "res/nav/one_channel_list/ocl.h"
#include "menu2/menu.h"
#include "res/msgconvert/msgconvert_custom.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#define RET_ON_ERR(_expr)  \
{ \
    INT32 expr = _expr; \
    if(expr != 0)\
    {\
        DBG_LOG_PRINT(("<TUNER_SETUP_VIEW> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__)); \
        return expr;\
    } \
}

#ifdef APP_TTS_SUPPORT
#define TUNER_TTS_SETTINGS_TEXT(key)   MLM_SETTINGS_TEXT(ui2_g_tuner_curr_lang, (key))  /* 0:english   */
#define TUNER_TTS_WARNINGS_TEXT(key)   MLM_WARNINGS_TEXT(ui2_g_tuner_curr_lang, (key))  /* 0:english   */
#endif

typedef struct _OSD_CONTENT_T
{
    GL_HSCREEN_T    h_screen;
    GL_HPLANE_T     h_plane;
    HANDLE_T        h_canvas;
    UINT32          ui4_canvas_width;
    UINT32          ui4_canvas_height;

    /* widget */
    HANDLE_T        h_frm;   /* Main frame */
    HANDLE_T        h_bar;
    HANDLE_T        h_icon;
    HANDLE_T        h_cd_text;
    HANDLE_T        h_da_text;
    HANDLE_T        h_per_text;

    //for warning msg
    HANDLE_T        h_warning_msg_dialog_frame;
    HANDLE_T        h_warning_msg_text;
    HANDLE_T        h_warning_msg_msgbox;
    HANDLE_T        h_warning_msg_icon;

    WGL_HIMG_TPL_T  h_bg_img_tpl;
    WGL_HIMG_TPL_T  h_pb_img_tpl;
    WGL_HIMG_TPL_T  h_pb_level_img_tpl;
} OSD_CONTENT_T;

typedef struct _AS_SCAN_NFY_T {
    HANDLE_T    h_builder;
    UINT32      ui4_nfy_reason;
    INT32       i4_nfy_data;
    VOID*       pv_nfy_tag;
} AS_SCAN_NFY_T;

typedef struct _AS_SCAN_INFO_T {
    HANDLE_T    h_builder;
    HANDLE_T    h_pb;
    INT32       i4_vir_ch_num;
    INT32       i4_phy_ch_num;
    INT32       i4_phy_ch_ttl;
    BOOL        b_done;         /* if b_done is TRUE, it means that the builder has
                                   sent a SB_REASON_COMPLETE, SB_REASON_CANCEL,
                                   SB_REASON_ABORT message */
} AS_SCAN_INFO_T;

typedef enum{
    TUNER_SCAN_TYPE_FULL_MODE,
    TUNER_SCAN_TYPE_UNKNOWN

}TUNER_SCAN_TYPE_T;

typedef struct _TUNER_SETUP_CHANNEL_INFO_T {
    CHAR    s_ch_num[CH_NUMBER_MAX_LENGTH+1];
    CHAR    s_ch_name[CH_NAME_MAX_LENGTH+1];
    BOOL    b_is_skip;
    BOOL    b_is_locked;
} TUNER_SETUP_CHANNEL_INFO_T;

#define TUNER_FRAME_X       (0)
#define TUNER_FRAME_Y       (0)
#define TUNER_FRAME_WIDTH   (1920)
#define TUNER_FRAME_HEIGHT  (1080)

#define TUNER_ICON_X          (0)
#define TUNER_ICON_Y          (512)
#define TUNER_ICON_WIDTH      (1920)
#define TUNER_ICON_HEIGHT     (40)

#define TUNER_PB_X          (960)
#define TUNER_PB_Y          (508)
#define TUNER_PB_WIDTH      (0)
#define TUNER_PB_HEIGHT     (4)

#define TUNER_CD_X          (710)
#define TUNER_CD_Y          (460)
#define TUNER_CD_WIDTH      (500)
#define TUNER_CD_HEIGHT     (32)

#define TUNER_DA_X          (460)
#define TUNER_DA_Y          (560)
#define TUNER_DA_WIDTH      (1000)
#define TUNER_DA_HEIGHT     (64)

#define TUNER_PER_X          (860)
#define TUNER_PER_Y          (660)
#define TUNER_PER_WIDTH      (200)
#define TUNER_PER_HEIGHT     (32)


#define WARNING_MSG_VIEW_BASE_FRAME_X             (0)
#define WARNING_MSG_VIEW_BASE_FRAME_Y             (-2)
#define WARNING_MSG_VIEW_BASE_FRAME_W             (1920)
#define WARNING_MSG_VIEW_BASE_FRAME_H             (415)


#define WARNING_MSG_VIEW_TXT_MSG_X                ((WARNING_MSG_VIEW_BASE_FRAME_W-WARNING_MSG_VIEW_TXT_MSG_W)/2)
#define WARNING_MSG_VIEW_TXT_MSG_Y                (33)
#define WARNING_MSG_VIEW_TXT_MSG_W                (1400)
#define WARNING_MSG_VIEW_TXT_MSG_H                (78)


#define WARNING_MSG_VIEW_ICON_WARNING_X           (0)
#define WARNING_MSG_VIEW_ICON_WARNING_Y           (160+60)
#define WARNING_MSG_VIEW_ICON_WARNING_W           (WARNING_MSG_VIEW_BASE_FRAME_W)
#define WARNING_MSG_VIEW_ICON_WARNING_H           (28)

#define WARNING_MSG_VIEW_ICON_MSGBOX_X            (0)
#define WARNING_MSG_VIEW_ICON_MSGBOX_Y            (0)
#define WARNING_MSG_VIEW_ICON_MSGBOX_W            (WARNING_MSG_VIEW_BASE_FRAME_W)
#define WARNING_MSG_VIEW_ICON_MSGBOX_H            (162)



#define atsc_scan_file  "/tmp/autotest/test_atsc_auto_scan_with_signal_ok"
#define cable_scan_file  "/tmp/autotest/test_cable_auto_scan_with_signal_ok"

#define _GET_PHY_CH_NUM(v) (((v)>>16) & 0xFFFF)
#define _GET_VIR_CH_NUM(v) ( (v)      & 0xFFFF)
#define TUNER_TEXT   _tuner_text

#define TUNER_WARNINGS_TEXT     _tuner_warning_text

#define _SB_VNET_CUST_CH_TOUCHED    (SB_VNET_USER_INDEX_BGN+1)    /* FIXME_MIN */
#define TUNER_MAKE_MOD_BIT_MASK(m)     MAKE_BIT_MASK_32((UINT32)((TUNER_MODULATION_T)(m)))
#define TUNER_SB_CQAM_DEF_MOD_MASK    (TUNER_MAKE_MOD_BIT_MASK(MOD_QAM_64) | TUNER_MAKE_MOD_BIT_MASK(MOD_QAM_256))
#define TUNER_SB_CQAM_QAM_MOD_MASK    (TUNER_MAKE_MOD_BIT_MASK(MOD_QAM_64) | TUNER_MAKE_MOD_BIT_MASK(MOD_QAM_256))


#define MAX_CH_NUM          (512)
#define OOBE_SCAN           (5)
#define OOBE_END            (7)

/*
from spec 3.4
Find Channels: scan only over the air channels, do not scan cable channels.
*/
 #define FIND_CHANNEL_SCAN_CABLE_ENABLE FALSE

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static OSD_CONTENT_T    tg_scan_view = {0};
GL_COLOR_T              t_g_tuner_setup_color_white = { 255, { 255 }, { 255 }, { 255 }};
static GL_COLOR_T       t_g_tuner_setup_color_white_line = { 127, { 133 }, { 133 }, { 133 }};
static GL_COLOR_T       t_g_tuner_setup_color_black = { 127, { 102 }, { 102 }, { 102 }};


static BOOL             b_scan                  = FALSE;
static BOOL             b_clean_lists           = FALSE; /* clean the SVL, TSL lists before scanning */
static BOOL             b_is_cancel             = FALSE; /* channel scan status */
static BOOL             b_repaint               = FALSE;
static BOOL             b_scan_cable            = FALSE;

static HANDLE_T         h_timer_ani = NULL_HANDLE;
static HANDLE_T         h_timer_show = NULL_HANDLE;
static HANDLE_T         h_timer_show_no_signal = NULL_HANDLE;

static UINT16           ui2_crnt_svl_id;
static UINT32           aui4_bk_ch_lst[MAX_CH_NUM];
static UINT32           ui4_bk_ch_lst_top = 0;

static UINT16           ui2_g_tuner_curr_lang;

static AS_SCAN_INFO_T   t_scan_antenna_atv;
static AS_SCAN_INFO_T   t_scan_antenna_dtv;
static AS_SCAN_INFO_T   t_scan_cable_atv;
static AS_SCAN_INFO_T   t_scan_cable_dtv;

static TUNER_COMMON_T          t_g_tuner_common;
static TUNER_ATSC_T            t_g_tuner_atsc;

static WDK_TOAST_PARAM_T       tg_toast_param;
static WDK_OSD_TOAST_T          t_g_wdk_view={0} ;

//static AS_SCAN_NFY_T   t_scan_nfy;
static UINT32          ui4_g_last_strm_mode = ST_MASK_AUDIO|ST_MASK_VIDEO;
static INT32           i4_toast_flag = 0;

static UINT32          ui4_g_tv_capability = 0;
static INT32          i4_g_scan_progress = 0;
static TSL_REC_T*      pt_g_tsl_rec_list   = NULL;
static TSL_REC_T*      pt_g_tsl_rec_list_cable   = NULL;

static UINT16          ui2_g_tsl_num       = 0;
static UINT16          ui2_g_tsl_num_cable       = 0;


static BOOL             b_menu_scan_channel = FALSE;

static BOOL             b_need_rest_scan_after_menu_scan = FALSE;

static BOOL             b_menu_scan_new_channel = FALSE;

#define ANTENTA_CH_START    2
#define ANTENTA_CH_MAX      69
#define CABLE_CH_START      1
#define CABLE_CH_MAX        135

static INT32 ant_ana_start = ANTENTA_CH_START;
static INT32 ant_dig_start = ANTENTA_CH_START;
static INT32 cab_ana_start = CABLE_CH_START;
static INT32 cab_dig_start = CABLE_CH_START;

static INT32 ant_ana_end = ANTENTA_CH_MAX;
static INT32 ant_dig_end = ANTENTA_CH_MAX;
static INT32 cab_ana_end = CABLE_CH_MAX;
static INT32 cab_dig_end = CABLE_CH_MAX;

static UINT16  ant_dtv_list_num    =   0;
static UINT16  ant_atv_list_num    =   0;
static UINT16  cab_dtv_list_num    =   0;
static UINT16  cab_atv_list_num    =   0;
static UINT8   ant_dtv_list[ANTENTA_CH_MAX]   =   {0};
static UINT8   ant_atv_list[ANTENTA_CH_MAX]   =   {0};
static UINT8   cab_dtv_list[CABLE_CH_MAX]   =   {0};
static UINT8   cab_atv_list[CABLE_CH_MAX]   =   {0};


#define             TOAST_VIEW_HEADLINE_2_FONT_SIZE                 (27)

static GL_COLOR_T   t_g_msg_txt_clr                 = { 255, { 255}, { 255}, { 255}};
static GL_COLOR_T   t_g_msg_txt_clr_oled            = { 255, { 191 }, { 191 }, { 191 }};

extern WGL_IMG_T t_g_wdk_warning;
extern WGL_IMG_T t_g_wdk_toast_box_settings;
extern WGL_IMG_T t_g_wdk_gradient_top;


WGL_HIMG_TPL_T              t_g_h_g_wdk_warning;
WGL_HIMG_TPL_T              t_g_h_g_wdk_toast_box_settings;
WGL_HIMG_TPL_T              t_g_h_g_wdk_gradient_top;

extern VOID a_reset_err_msg_id(VOID);

INT32 tuner_setup_warning_show(UTF16_T* w2s_str);
INT32 tuner_setup_warning_hide(VOID);

static VOID  _tuner_setup_clear_scan_table_list(VOID);


static INT32 _tuner_setup_warning_widget_init(VOID);

static VOID _tuner_setup_view_show_scan (VOID* pv_data1,
                                                   VOID* pv_data2,
                                                   VOID* pv_data3);

static VOID _timer_animation_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag);


static VOID _tuner_setup_scan_nfy_fct(HANDLE_T          h_builder,
                          UINT32            ui4_nfy_reason,
                          INT32             i4_nfy_data,
                          VOID*             pv_nfy_tag);
static VOID _sb_nfy_fct (HANDLE_T          h_builder,
                         SB_COND_T         e_builder_cond,
                         VOID*             pv_nfy_tag);
static INT32 _cancel_scan(BOOL b_is_select_ch);

static INT32 _on_scan_stop(VOID);


static VOID _timer_show_toast_view_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag);


static INT32 _tuner_setup_string_toast_view(HANDLE_T h_canvas,
                                                    UTF16_T* w2s_txt);


static INT32 _tuner_setup_warning_toast_view(HANDLE_T h_canvas,
                                                    UTF16_T* w2s_txt);

static INT32 _tuner_setup_get_wzd_state(VOID);


static INT32 _tuner_setup_get_crnt_isl(ISL_REC_T* pt_isl_rec);

static INT32 _tuner_setup_select_crnt_or_first_channel(BOOL b_skip_fake);

static VOID _tuner_setup_get_dig_and_ana_num(HANDLE_T h_svl,
                                            UINT16* pui2_num_recs_digital,
                                            UINT16* pui2_num_recs_analog);
static INT32 _tuner_setup_clean_channel_table(VOID);

static INT32 _tuner_setup_get_gui_lang(VOID);

static VOID _tuner_setup_url_put_response(VOID* pv_data1,
                                              VOID* pv_data2,
                                              VOID* pv_data3);

static VOID _tuner_setup_url_put_update_channel(VOID);

static INT32 _tuner_setup_start_scan_before(VOID);
static INT32 _tuner_setup_start_scan_new_antenna(VOID);
static INT32 _tuner_setup_start_scan_new_cable(VOID);
static VOID _tuner_setup_do_scan_new_nfy(VOID* pv_data,
                         SIZE_T  z_data_size);
static VOID _tuner_setup_scan_new_nfy_fct(HANDLE_T          h_builder,
                          UINT32            ui4_nfy_reason,
                          INT32             i4_nfy_data,
                          VOID*             pv_nfy_tag);
static INT32 _tuner_setup_scan_antenna_atv(UINT16 idx);
static INT32 _tuner_setup_scan_antenna_dtv(UINT16 idx);
static INT32 _tuner_setup_scan_cable_atv(UINT16 idx);
static INT32 _tuner_setup_scan_cable_dtv(UINT16 idx);
INT32 _tuner_setup_sort_channels(VOID);
BOOL _tuner_check_phy_CH(HANDLE_T builder,UINT16 CH_num);


/*----------------------------------------------------------------------------
 * Name: _itoa
 *
 * Description: Interger to string utility function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _itoa(UTF16_T* w2s_dst,
                  INT32 i4_src,
                  UINT32 ui4_dst_len)
{
    CHAR    s_buf[32];
    c_sprintf(s_buf, "%d",  i4_src);
    c_uc_ps_to_w2s(s_buf, w2s_dst, ui4_dst_len);
}

/*----------------------------------------------------------------------------
 * Name: _tuner_text
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
static UTF16_T* _tuner_text(INT32 ui4_key)
{
    do{
        _tuner_setup_get_gui_lang();
        return MLM_SETTINGS_TEXT(ui2_g_tuner_curr_lang, (ui4_key));                                                       \
    }while(FALSE);
}

/*----------------------------------------------------------------------------
 * Name: _tuner_warning_text
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
static UTF16_T* _tuner_warning_text(INT32 ui4_key)
{
    do{
        _tuner_setup_get_gui_lang();
        return MLM_WARNINGS_TEXT(ui2_g_tuner_curr_lang, (ui4_key));                                                       \
    }while(FALSE);
}
/*----------------------------------------------------------------------------
 * Name: _ch_num_to_str
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
static VOID _ch_num_to_str(UINT16      ui2_major,
                           UINT16      ui2_minor,
                           BOOL        b_one_part_ch,
                           UTF16_T*    w2s_str)
{
    CHAR    s_str[64];
    c_memset(s_str, 0, sizeof(s_str));
    if (b_one_part_ch)
    {   /* One part channel number */
        c_sprintf(s_str,
                  "%d",
                  ui2_major);
    }
    else
    {   /* Two part channel number */
        c_sprintf(s_str,
                  CHANNEL_NUMBER_FORMAT,   /* Defined in a_common.h */
                  ui2_major,
                  ui2_minor);
    }
    c_uc_ps_to_w2s(s_str ,w2s_str, 8);
}


/*-----------------------------------------------------------------------------
 * Name: _tuner_get_crnt_svctx
 *
 * Description: -
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
HANDLE_T _tuner_get_crnt_svctx(VOID)
{
    TV_WIN_ID_T     t_win_id = TV_WIN_ID_MAIN;
    HANDLE_T        h_crnt_svctx = NULL_HANDLE;
    INT32           i4_ret = 0;

    i4_ret = a_tv_get_focus_win(&t_win_id);

    if(i4_ret == TVR_OK )
    {
        nav_get_svctx_handle(t_win_id,&h_crnt_svctx);
        return h_crnt_svctx;
    }
    else
    {
        TUNER_LOG_E("a_tv_get_focus_win fail i4_ret:%d. \n",i4_ret);
    }

    return NULL_HANDLE;

}

/*--------------------------------------------------------------------------
 * Name
 *      _revolt_misc_get_gui_lang
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/

static INT32 _tuner_setup_get_gui_lang(VOID)
{
    INT32 i4_ret;
    ISO_639_LANG_T s639_lang;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    RET_ON_ERR(i4_ret);

    ui2_g_tuner_curr_lang = mlm_settings_s639_to_langidx(s639_lang);

    return TSP_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _tuner_atsc_update_sb_snk_name
 *
 * Description:
 *  Update the sink name to svl builder NTSC engine.
 *
 * Inputs:
 *      h_lb - paraent widget
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _tuner_atsc_update_sb_snk_name(
    HANDLE_T    h_sb,
    HANDLE_T    h_svctx)
{
    INT32   i4_ret;
    CHAR    s_snk_name[SVCTX_SNK_NAME_MAX_SIZE + 1];
    SIZE_T  z_size = SVCTX_SNK_NAME_MAX_SIZE;

    /* get sync name from svctx */
    i4_ret = c_svctx_get(h_svctx,
                         SVCTX_COMMON_GET_TYPE_SNK_NAME,
                         (VOID*)s_snk_name,
                         &z_size);
    RET_ON_ERR(i4_ret);

    /* set sync name to sb */
    i4_ret = c_sb_set(h_sb,
                      SB_KEY_TYPE_SET_TVD_SNK_NAME,
                      NULL,
                      z_size,
                      s_snk_name);
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _tuner_setup_get_input_src
 *
 * Description:
 *  Update the sink name to svl builder NTSC engine.
 *
 * Inputs:
 *      h_lb - paraent widget
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL _tuner_setup_get_input_src(VOID)
{
    INT32           i4_ret;
    TV_WIN_ID_T     e_tv_win_id;
    ISL_REC_T       pt_isl_rec;

    i4_ret = nav_get_focus_id (&e_tv_win_id);
    RET_ON_ERR(i4_ret);

    i4_ret = nav_get_isl_rec(e_tv_win_id,&pt_isl_rec);
    RET_ON_ERR(i4_ret);

    if(pt_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        TUNER_LOG_I("INP_SRC_TYPE_TV\n\r");
        return TRUE;
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: _tuner_setup_get_wzd_state
 *
 * Description:
 *  get oobe state
 *
 * Inputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _tuner_setup_get_wzd_state(VOID)
{
    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;

    RET_ON_ERR(a_cfg_get_wzd_status(&ui2_status));
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

    TUNER_LOG_I("tuner_setup_scan_oobe_state,state=%d\r\n",(int)ui1_state);
    if(WZD_STATE_RESUME_C4TV == ui1_state)
    {
        return OOBE_SCAN;
    }
    else if(WZD_STATE_RESUME_C4TV_END == ui1_state)
    {
        return OOBE_END;
    }
    return TSP_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _tuner_setup_get_crnt_isl
 *
 * Description:
 *  get oobe state
 *
 * Inputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _tuner_setup_get_crnt_isl(ISL_REC_T* pt_isl_rec)
{
    INT32           i4_ret;
    TV_WIN_ID_T     t_win_id;

    i4_ret = a_tv_get_focus_win(&t_win_id);
    RET_ON_ERR(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id,
                                        pt_isl_rec);
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _tuner_setup_select_crnt_or_first_channel
 *
 * Description:
 *
 * Inputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _tuner_setup_select_crnt_or_first_channel(BOOL b_skip_fake)
{
    INT32                      i4_ret;
    SVL_REC_T                  t_svl_rec          = {0};
    UINT32                     ui4_channel_id     = 0;
    //UINT16                     ui2_crnt_svl_id    = ATSC_TRSTRL_SVL_ID;
    //CHAR*                      ps_crnt_tuner_name = ATSC_TRSTRL_TUNER_NAME;
    //HANDLE_T                   h_crnt_svl         = t_g_tuner_common.h_svl_air;
    ISL_REC_T                  t_isl_rec;
    TV_MODE_T                  t_tv_mode;
    TV_WIN_ID_T                t_win_id;
    INT32                      i4_scanned_analog_ch_num  = 0;
    INT32                      i4_scanned_dig_ch_num     = 0;
    UINT16                      ui2_ocl_idx=0;
    OCL_SVL_REC_T               t_ocl_svl_rec = {0};

    /* Get current working TV Mode */
    a_tv_get_mode(&t_tv_mode);

    tuner_setup_scan_analog_get_val(&i4_scanned_analog_ch_num);

    tuner_setup_scan_digital_get_val(&i4_scanned_dig_ch_num);

    TUNER_LOG_I(" i4_scanned_ch_num = %d\n\r", i4_scanned_analog_ch_num + i4_scanned_dig_ch_num);

    if ((i4_scanned_analog_ch_num + i4_scanned_dig_ch_num) <= 0 && !a_nav_tuner_setup_get_scan_new_channel())
    {
        return -1;
    }
    /* Check the input source on FOCUSED WIN */
    _tuner_setup_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
    {
        if(t_tv_mode == TV_MODE_TYPE_NORMAL)
        {
            /* TV_MODE = NORMAL */
            /* Input Src != TV, so, change it to TV */

            a_tv_get_focus_win(&t_win_id);

            i4_ret = a_isl_get_rec_by_type(
                        INP_SRC_TYPE_TV,
                        0,
                        &t_isl_rec
                        );
            if (i4_ret != ISLR_OK) {
                return TSP_FAIL;
            }

            i4_ret = a_tv_set_input_src_id(t_win_id, t_isl_rec.ui1_id);

            if (i4_ret != TVR_OK) {
                return TSP_FAIL;
            }

        }
        else if(t_tv_mode == TV_MODE_TYPE_PIP ||
                t_tv_mode == TV_MODE_TYPE_POP)
        {
            /* TV_MODE = PIP/POP */
            /* Focus Win Input Src != TV, don't change anything, return directly */
            return TSP_OK;
        }
     }
    #if 0
    /* set tuner type to Antenna,
    * because should select first antenna channel after scan complete.
    */
    a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_AIR);

    /* The focus win's input src == INP_SRC_TYPE_TV now */
    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, &ps_crnt_tuner_name);
    if (i4_ret != APP_CFGR_OK)
    {
        return TSP_FAIL;
    }
    h_crnt_svl = tuner_get_crnt_svl();

    if (h_crnt_svl == NULL_HANDLE)
    {
        TUNER_LOG_E("Can't ntuner_get_crnt_svl\r\n");
        return TSP_OK;
    }

    i4_ret = a_cfg_set_tuner_sync_src(ui2_crnt_svl_id, ps_crnt_tuner_name);
    if (i4_ret != APP_CFGR_OK)
    {
        TUNER_LOG_E("Can't notify DT to sync source,i4_ret:%d\r\n",i4_ret);
        return TSP_FAIL;
    }
    #endif
    i4_ret = ocl_get_ocl_svl_by_index(ui2_ocl_idx, &t_svl_rec, &t_ocl_svl_rec);
    if (OCLR_OK != i4_ret)
    {
        a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_AIR);
        i4_ret = a_cfg_set_tuner_sync_src(ATSC_TRSTRL_SVL_ID, ATSC_TRSTRL_TUNER_NAME);
        if (i4_ret != APP_CFGR_OK)
        {
            TUNER_LOG_E("Can't notify DT to sync source,i4_ret:%d\r\n",i4_ret);
        }
        DBG_LOG_PRINT(("[tuner scan] ATSC_TRSTRL_SVL_ID :%d\n",i4_ret));
    }
    else
    {
        if (t_ocl_svl_rec.ui2_svl_id == ANTENNA_SVL_ID)
        {
            a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_AIR);
            i4_ret = a_cfg_set_tuner_sync_src(ATSC_TRSTRL_SVL_ID, ATSC_TRSTRL_TUNER_NAME);
            if (i4_ret != APP_CFGR_OK)
            {
                TUNER_LOG_E("ANTENNA_SVL_ID i4_ret:%d\r\n",i4_ret);
            }
        }
        else
        {
            a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_CABLE);
            i4_ret = a_cfg_set_tuner_sync_src(ATSC_CABLE_SVL_ID, ATSC_CABLE_TUNER_NAME);
            if (i4_ret != APP_CFGR_OK)
            {
                TUNER_LOG_E("ATSC_CABLE_SVL_ID i4_ret:%d\r\n",i4_ret);
            }
        }
    }
    #if 0
    /* Try to get a proper playable svl_rec */
    /* b_skip_fake argument is taking from outside */
    OCL_SVL_REC_T t_ocl_svl_rec = {0};
    i4_ret =  ocl_get_first_ch_by_svl_id(ANTENNA_SVL_ID, &t_svl_rec, &t_ocl_svl_rec);

    //i4_ret = a_tv_get_crnt_or_first_svl_rec(h_crnt_svl, b_skip_fake, &t_svl_rec);
    /* cannot find first antenna channel, get the cable first channel */
    if (i4_ret != OCLR_OK)
    {
        i4_ret =  ocl_get_first_ch_by_svl_id(CABLE_SVL_ID, &t_svl_rec, &t_ocl_svl_rec);
        TUNER_LOG_E("cannot find first antenna channel, get the cable first channel t_svl_rec.uheader.t_rec_hdr.ui4_channel_id= %d\n\r", t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);

        a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_CABLE);

        i4_ret = a_cfg_set_tuner_sync_src(ATSC_CABLE_SVL_ID, ATSC_CABLE_TUNER_NAME);
        if (i4_ret != APP_CFGR_OK)
        {
            TUNER_LOG_E("Can't notify DT to sync source,i4_ret:%d\r\n",i4_ret);
            return TSP_FAIL;
        }
    }
    #endif

    UINT8 ui1_brdcst_src = 0;
    a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, &ui1_brdcst_src);
    TUNER_LOG_I("a_tv_get_crnt_or_first_svl_rec ui4_channel_id:0x%x e_brdcst_type= %d,ui1_brdcst_src= %d i4_ret= %d\n\r",\
        t_svl_rec.uheader.t_rec_hdr.ui4_channel_id,t_svl_rec.uheader.t_rec_hdr.e_brdcst_type,ui1_brdcst_src,i4_ret);

    if(i4_ret != OCLR_OK)
    {
        i4_ret = a_tv_stop(_tuner_get_crnt_svctx());

        if (i4_ret != OCLR_OK)
        {
            TUNER_LOG_E("Stop service failed = %d\n\r", i4_ret);
        }

        return TSP_OK;
    }
    else
    {
        ui4_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;
    }

    TUNER_LOG_I("t_svl_rec.uheader.t_rec_hdr.ui4_channel_id = %d\n\r", t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);

    TUNER_LOG_I("t_tv_mode = %d\n\r", t_tv_mode);
    if(nav_is_svl_empty(TV_WIN_ID_MAIN))
    {
        nav_update_tv_win_status(TV_WIN_ID_MAIN, &t_isl_rec);
    }
    /* Successfully get a playable svl_rec, so play it */
    if(t_tv_mode != TV_MODE_TYPE_NORMAL)
    {
        SIZE_T  z_size = sizeof(UINT32);

        i4_ret = c_svctx_get (_tuner_get_crnt_svctx(),
                          SVCTX_COMMON_GET_STREAM_MODE,
                          &ui4_g_last_strm_mode,
                          &z_size
                          );
        /* If PIP/POP mode, use the last stream mode. */
        i4_ret = a_tv_change_channel(_tuner_get_crnt_svctx(),
                                     ui4_g_last_strm_mode,
                                     ui4_channel_id,
                                     NULL);
    }
    else
    {
        /* If normal mode, always play video and audio */
        i4_ret = a_tv_change_channel(_tuner_get_crnt_svctx(),
                                     ST_MASK_VIDEO | ST_MASK_AUDIO,
                                     ui4_channel_id,
                                     NULL);
    }
    /* sync */
    a_cfg_update_dt_sync_mode();

    nav_hide_component(NAV_COMP_ID_TUNER_SETUP);

    nav_return_activation(NAV_COMP_ID_TUNER_SETUP);

    return TSP_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _tuner_setup_enable_ch_chg
 *
 * Description:
 *
 * Inputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _tuner_setup_enable_ch_chg( BOOL b_enable )
{
    if (b_enable)
    {
        /* Check APP_TV's capability */
        a_tv_get_capability (&ui4_g_tv_capability);
        a_tv_unset_capability (TV_CAPABILITY_MASK_ALLOW_CHANNEL_CHANGE,
                             TV_CAPABILITY_MASK_ALLOW_CHANNEL_CHANGE);
        TUNER_LOG_I("reset APP_TV capability \r\n");
    }
    else
    {
        if ((ui4_g_tv_capability & TV_CAPABILITY_MASK_ALLOW_CHANNEL_CHANGE)
            == TV_CAPABILITY_MASK_ALLOW_CHANNEL_CHANGE)
      /*it don't need to judge the condition, if use this condition, it will lead to don't change
      channel when scan complete or scan cancle or scan abort*/
        {
            TUNER_LOG_I("set APP_TV capability\r\n");
            a_tv_set_capability (TV_CAPABILITY_MASK_ALLOW_CHANNEL_CHANGE,
                                   TV_CAPABILITY_MASK_ALLOW_CHANNEL_CHANGE);
        }
    }
}

static VOID _tuner_setup_set_enable_change_ch(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    _tuner_setup_enable_ch_chg(FALSE);
}


static INT32 _tuner_setup_set_cfg_first_channel_id(VOID)
{
    INT32           i4_ret = 0;
    OCL_SVL_REC_T   t_ocl_svl_rec = {0};
    SVL_REC_T       t_svl_rec  = {0};
    TV_WIN_ID_T     e_tv_win_id;
    UINT16          ui2_ocl_idx=0;

    c_memset(&t_svl_rec, 0, sizeof(t_svl_rec));
    c_memset(&t_ocl_svl_rec, 0, sizeof(t_ocl_svl_rec));

    i4_ret = ocl_get_ocl_svl_by_index(ui2_ocl_idx, &t_svl_rec, &t_ocl_svl_rec);
    if (OCLR_OK != i4_ret)
    {
        a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_AIR);
        i4_ret = a_cfg_set_tuner_sync_src(ATSC_TRSTRL_SVL_ID, ATSC_TRSTRL_TUNER_NAME);
        if (i4_ret != APP_CFGR_OK)
        {
            TUNER_LOG_E("Can't notify DT to sync source,i4_ret:%d\r\n",i4_ret);
        }
        DBG_LOG_PRINT(("ATSC_TRSTRL_SVL_ID i4_ret:%d\n",i4_ret));
    }
    else
    {
        if (t_ocl_svl_rec.ui2_svl_id == ANTENNA_SVL_ID)
        {
            a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_AIR);
            i4_ret = a_cfg_set_tuner_sync_src(ATSC_TRSTRL_SVL_ID, ATSC_TRSTRL_TUNER_NAME);
            if (i4_ret != APP_CFGR_OK)
            {
                TUNER_LOG_E("ATSC_TRSTRL_SVL_ID,i4_ret:%d\r\n",i4_ret);
            }
        }
        else
        {
            a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_CABLE);
            i4_ret = a_cfg_set_tuner_sync_src(ATSC_CABLE_SVL_ID, ATSC_CABLE_TUNER_NAME);
            if (i4_ret != APP_CFGR_OK)
            {
                TUNER_LOG_E("ATSC_CABLE_SVL_ID,i4_ret:%d\r\n",i4_ret);
            }
        }
    }
    TUNER_LOG_I("t_svl_rec.uheader.t_rec_hdr.ui4_channel_id = %d \n\r", t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);
    /* fix DTV00870987 */
    if (i4_ret == OCLR_OK)
    {
        a_cfg_set_crnt_channel_id(t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);

        DBG_LOG_PRINT(("[tuner scan] ui4_channel_id:0x%x\n",t_svl_rec.uheader.t_rec_hdr.ui4_channel_id));

        /*update current channel's SVL record of the window. */
        nav_get_focus_id(&e_tv_win_id);
        //nav_update_svl_rec (e_tv_win_id);
        nav_update_src_info(e_tv_win_id);
    }

    nav_request_context_switch(
                        _tuner_setup_set_enable_change_ch,
                        NULL,
                        NULL,
                        NULL);


    return TSP_OK;
}


/*----------------------------------------------------------------------------
 * Name: _calc_progress
 *
 * Description:
 *  Calculate the progress.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _calc_progress(VOID)
{
    /*
    from spec 3.4
    Find Channels: scan only over the air channels, do not scan cable channels.
    Find More Channels: adds channels not found for over the air without deleting channels previously scanned and also scans all cable channels.
    */
    if(!a_nav_tuner_setup_get_scan_new_channel())
        #if FIND_CHANNEL_SCAN_CABLE_ENABLE
        return (t_scan_antenna_atv.i4_phy_ch_num + t_scan_antenna_dtv.i4_phy_ch_num +
            t_scan_cable_atv.i4_phy_ch_num + t_scan_cable_dtv.i4_phy_ch_num) * 100 /
           (t_scan_antenna_atv.i4_phy_ch_ttl + t_scan_antenna_dtv.i4_phy_ch_ttl +
           t_scan_cable_atv.i4_phy_ch_ttl + t_scan_cable_dtv.i4_phy_ch_ttl);
        #else
        return (t_scan_antenna_atv.i4_phy_ch_num + t_scan_antenna_dtv.i4_phy_ch_num) * 100 /
           (t_scan_antenna_atv.i4_phy_ch_ttl + t_scan_antenna_dtv.i4_phy_ch_ttl);
        #endif
    else
        return (t_scan_antenna_atv.i4_phy_ch_num + t_scan_antenna_dtv.i4_phy_ch_num +
                t_scan_cable_atv.i4_phy_ch_num + t_scan_cable_dtv.i4_phy_ch_num) * 100 /
                (t_scan_antenna_atv.i4_phy_ch_ttl-1 + t_scan_antenna_dtv.i4_phy_ch_ttl-1 +
                t_scan_cable_atv.i4_phy_ch_ttl + t_scan_cable_dtv.i4_phy_ch_ttl);

}

/*-----------------------------------------------------------------------------
 * Name: _get_freq_plan
 *
 * Description: Get the frequency plan setting and return correct parameter
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_freq_plan(UINT8*  pui1_freq,
                            UINT32* pui4_mod)
{
    INT32  i4_ret;
    UINT8  ui1_idx;

    i4_ret = a_cfg_get_tuner_type(APP_CFG_RECID_BS_PLN, &ui1_idx);
    if (i4_ret == APP_CFGR_OK)
    {
        switch (ui1_idx)
        {
        case APP_CFG_BS_PLN_AUTO:
            (*pui1_freq) = SB_CQAM_FREQ_PLAN_AUTO;
            i4_ret = a_cfg_get_tuner_type(APP_CFG_RECID_BS_VSB, &ui1_idx);
            if (i4_ret == APP_CFGR_OK)
            {
                switch (ui1_idx)
                {
                case APP_CFG_BS_VSB_DETECT:
                    TUNER_LOG_I("APP_CFG_BS_VSB_DETECT\r\n");
                    (*pui4_mod)  = TUNER_SB_CQAM_DEF_MOD_MASK;
                    break;
                case APP_CFG_BS_VSB_IGNORE:
                    TUNER_LOG_I("TUNER_SB_CQAM_QAM_MOD_MASK\r\n");
                    (*pui4_mod)  = TUNER_SB_CQAM_QAM_MOD_MASK;
                    break;
                default:
                    TUNER_LOG_I("Wrong 8vsb mode: %d\r\n", ui1_idx);
                    return TSP_FAIL;
                }
            }
            else
            {
                TUNER_LOG_I("Cannot get 8vsb mode\r\n");
                return TSP_FAIL;
            }
            break;
        case APP_CFG_BS_PLN_STD:
            (*pui1_freq) = SB_CQAM_FREQ_PLAN_STD;
            (*pui4_mod)  = TUNER_SB_CQAM_QAM_MOD_MASK;
            break;
        case APP_CFG_BS_PLN_IRC:
            (*pui1_freq) = SB_CQAM_FREQ_PLAN_IRC;
            (*pui4_mod)  = TUNER_SB_CQAM_QAM_MOD_MASK;
            break;
        case APP_CFG_BS_PLN_HRC:
            (*pui1_freq) = SB_CQAM_FREQ_PLAN_HRC;
            (*pui4_mod)  = TUNER_SB_CQAM_QAM_MOD_MASK;
            break;
        default:
            return TSP_FAIL;
        }
    }
    else
    {
        TUNER_LOG_E("Cannot get frequency plan mode\r\n");
        return TSP_FAIL;
    }
    TUNER_LOG_I("pui4_mod :0x%x\r\n", *pui4_mod);
    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: tuner_get_crnt_svl
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
HANDLE_T tuner_get_crnt_svl(VOID)
{
    INT32  i4_ret;
    UINT16 ui2_crnt_svl_id;

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    if (i4_ret != APP_CFGR_OK)
    {
        return NULL_HANDLE;
    }

    return ((ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID) ?
            t_g_tuner_common.h_svl_air :
            t_g_tuner_common.h_svl_cable);
}

/*----------------------------------------------------------------------------
 * Name: tuner_get_crnt_tsl
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
HANDLE_T tuner_get_crnt_tsl(VOID)
{
    INT32  i4_ret;
    UINT16 ui2_crnt_svl_id;

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    if (i4_ret != APP_CFGR_OK)
    {
        return NULL_HANDLE;
    }

    return ((ui2_crnt_svl_id == ATSC_TRSTRL_TSL_ID) ?
            t_g_tuner_common.h_tsl_air :
            t_g_tuner_common.h_tsl_cable);
}

/*----------------------------------------------------------------------------
 * Name: _bk_ch_preserve
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
INT32 _bk_ch_preserve(HANDLE_T  h_svl)
{
    INT32       i4_ret;
    SVL_REC_T   t_svl_rec;
    UINT32      ui4_lst_mask    = SB_VNET_ALL;
    UINT32      ui4_bk_mask     = SB_VNET_BLOCKED;
    UINT16      ui2_idx;
    UINT16      ui2_rec_num = 0;
    UINT32      ui4_ver_id = SVL_NULL_VER_ID;
    BOOL        b_again;

    /* This loop is used for redo the iteration when somebody modify the SVL
       during our iteration. */
    do
    {
        b_again = FALSE;

        /* reset the top index of aui4_bk_ch_lst */
        ui4_bk_ch_lst_top = 0;

        /* get record number */
        i4_ret = c_svl_get_num_rec_by_brdcst_type(h_svl,
                                                  BRDCST_TYPE_UNKNOWN,
                                                  ui4_lst_mask,
                                                  &ui2_rec_num,
                                                  &ui4_ver_id);
        if(i4_ret != SVLR_OK)
        {
            TUNER_LOG_E("Can't get record number.i4_ret:%d\r\n",i4_ret);
            return TSP_FAIL;
        }

        /* Boundary check */
        if(ui2_rec_num > MAX_CH_NUM)
        {
            ui2_rec_num = MAX_CH_NUM;
        }

        /* iterate */
        for(ui2_idx=0; ui2_idx<ui2_rec_num; ui2_idx++)
        {
            i4_ret = c_svl_get_rec_by_brdcst_type(h_svl,
                                                  BRDCST_TYPE_UNKNOWN,
                                                  ui4_lst_mask,
                                                  ui2_idx,
                                                  &t_svl_rec,
                                                  &ui4_ver_id);
            if (i4_ret == SVLR_MODIFIED)
            {
                TUNER_LOG_E("Somebody modifed the SVL.\r\n");
                b_again = TRUE;
                break;
            }
            else if(i4_ret != SVLR_OK)
            {
                TUNER_LOG_E("Can't iterate service list at idx=%d.\r\n",
                           ui2_idx);
                return TSP_FAIL;
            }

            if(t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & ui4_bk_mask)
            {
                aui4_bk_ch_lst[ui4_bk_ch_lst_top++] =
                    t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;
                TUNER_LOG_E("Block channel found=0x%08X\n",
                           t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);
            }
        }   /* end of Iteration */
    }while(b_again);

    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: _bk_ch_back
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
INT32 _bk_ch_back(HANDLE_T h_svl)
{
    INT32       i4_ret          = TSP_OK;
    UINT32      ui4_lst_mask    = SB_VNET_ALL;
    UINT32      ui4_bk_mask     = SB_VNET_BLOCKED;
    UINT16      ui2_i;
    UINT32      ui4_ver_id      = SVL_NULL_VER_ID;
    SVL_REC_T   t_svl_rec;

    if (h_svl == NULL_HANDLE)
    {
        return TSP_FAIL;
    }

    /* lock SVL */
    c_svl_lock(h_svl);

    do
    {
        /* Boundary check */
        if(ui4_bk_ch_lst_top > MAX_CH_NUM)
        {
            ui4_bk_ch_lst_top = MAX_CH_NUM;
        }

        for (ui2_i=0;
             ui2_i < (UINT16)ui4_bk_ch_lst_top;
             ui2_i++)
        {
            i4_ret = c_svl_get_rec_by_channel(h_svl,
                                              aui4_bk_ch_lst[ui2_i],
                                              ui4_lst_mask,
                                              0,            /* index = 0 */
                                              &t_svl_rec,
                                              &ui4_ver_id);
            if(i4_ret != SVLR_OK)
            {
                TUNER_LOG_E("Block channel not found=0x%08X\n", aui4_bk_ch_lst[ui2_i]);
                continue;
            }

            /* Turn on the block mask */
            t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask |= ui4_bk_mask;

            TUNER_LOG_I("Block channel puback=0x%08X\n", aui4_bk_ch_lst[ui2_i]);

            c_svl_lock(h_svl);

            i4_ret = c_svl_update_rec(h_svl, &t_svl_rec, TRUE);

            c_svl_unlock(h_svl);

            if (i4_ret != SVLR_OK)
            {
                TUNER_LOG_E("Can't update record. i4_ret:%d\n",i4_ret);
            }
        }
    } while(0);

    ui4_bk_ch_lst_top = 0;

    /* Unlock SVL */
    c_svl_unlock(h_svl);

    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: _percent_set_text
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
static INT32 _percent_set_text(INT32       i4_progress)
{
    INT32       i4_ret;
    UTF16_T     w2s_tmp_str[128] = {0};
    UTF16_T     w2s_str[128] = {0};
    //char*       s_str;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    //s_str = "0";
     _itoa(w2s_tmp_str, i4_progress, 4);
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_uc_w2s_strcpy(w2s_tmp_str,TUNER_TEXT(MLM_SETTINGS_KEY_CHANNEL_PERCENT_COMPLETE));
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_per_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_str)));
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}


/*----------------------------------------------------------------------------
 * Name: _txt_info_set_text
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
static INT32 _txt_info_set_text(UTF16_T* w2s_digital_str,UTF16_T* w2s_analgo_str)
{
    INT32       i4_ret;
    UTF16_T     w2s_tmp_str[128] = {0};
    UTF16_T     w2s_str[128] = {0};
    char*       s_str = " ";

    c_uc_w2s_strncat(w2s_str,w2s_digital_str,c_uc_w2s_strlen(w2s_digital_str));

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));

    c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));
    /* add backspeace */
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));

    c_uc_w2s_strncpy(w2s_tmp_str, TUNER_TEXT(MLM_SETTINGS_KEY_AND),
                         128);
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));

    c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));
    /* add backspeace */
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    c_uc_w2s_strncat(w2s_str,w2s_analgo_str,c_uc_w2s_strlen(w2s_analgo_str));

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_da_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_str)));
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: _update_scan_ch_title
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
static INT32 _update_scan_ch_title()
{
    INT32       i4_ret;
    UTF16_T     w2s_tmp_str[128] = {0};

    c_uc_w2s_strcpy(w2s_tmp_str, TUNER_TEXT(MLM_SETTINGS_KEY_CHANNELS_FOUND));

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_cd_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_tmp_str),
                          WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));

    RET_ON_ERR(i4_ret);

    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: _txt_info_animate_update
 *
 * Description:
 *
 * Inputs:
 *      b_step - if go to the next animation step
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _txt_info_animate_update(BOOL b_clear)
{
    //static UINT8 ui1_step=0;
    UTF16_T w2s_str_digital[50];
    UTF16_T w2s_num_digital[5];
    UTF16_T w2s_str_analog[50];
    UTF16_T w2s_num_analog[5];

    UINT32  ui4_len = 50;
    INT32   i4_num_analog = 0;
    INT32   i4_num_digital = 0;

    c_memset(w2s_str_digital, 0, sizeof(w2s_str_digital));
    c_memset(w2s_str_analog,  0, sizeof(w2s_str_analog));
    c_memset(w2s_num_digital, 0, sizeof(w2s_num_digital));
    c_memset(w2s_num_analog,  0, sizeof(w2s_num_analog));

    if (b_scan || b_clear)
    {
        /* Append Analog Channels */
        if(b_clear)
            i4_num_analog = 0;
        else
            i4_num_analog = t_scan_antenna_atv.i4_vir_ch_num + t_scan_cable_atv.i4_vir_ch_num;

        _itoa(w2s_num_analog, i4_num_analog, 4);

        c_uc_w2s_strncpy(w2s_str_analog, TUNER_TEXT(MLM_SETTINGS_KEY_CHANNEL_ANALOG),
                         ui4_len - c_uc_w2s_strlen(w2s_str_analog));
        c_uc_w2s_strncat(w2s_str_analog, w2s_num_analog,
                         ui4_len - c_uc_w2s_strlen(w2s_str_analog));

        /* Append Digital Channels */
        if(b_clear)
            i4_num_analog = 0;
        else
            i4_num_digital = t_scan_antenna_dtv.i4_vir_ch_num + t_scan_cable_dtv.i4_vir_ch_num;

        _itoa(w2s_num_digital, i4_num_digital, 4);

        c_uc_w2s_strncpy(w2s_str_digital, TUNER_TEXT(MLM_SETTINGS_KEY_CHANNEL_DIGITAL),
                         ui4_len - c_uc_w2s_strlen(w2s_str_digital));
        c_uc_w2s_strncat(w2s_str_digital, w2s_num_digital,
                         ui4_len - c_uc_w2s_strlen(w2s_str_digital));

        /*
        if(b_step)
        {
            ui1_step = (UINT8)((ui1_step + 1)%3);
        }
        */

        _txt_info_set_text(w2s_str_digital,w2s_str_analog);
    }

    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_start_scan_fail
 *
 * Description:
 *  if start to scan unsuccessfully, it will show "scan error" message, and
 * callback the notify to CLI (if any).
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_start_scan_fail(VOID)
{
    INT32 i4_ret;

    i4_ret = c_wgl_show(tg_scan_view.h_frm, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: _crnt_is_tv_src
 *
 * Description:
 *    This API judge current source is TV or not.
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static BOOL _crnt_is_tv_src(VOID)
{
    INT32  i4_ret           = 0;
    TV_WIN_ID_T  e_focus_id = {0};
    ISL_REC_T  t_isl_rec    = {0};

    i4_ret = a_tv_get_focus_win(&e_focus_id);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_isl_rec);
    NAV_LOG_ON_FAIL(i4_ret);

    if (INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
    {
        TUNER_LOG_I("Current src is INP_SRC_TYPE_TV\n");
        return TRUE;
    }
    else
    {
        TUNER_LOG_I("Current src is Not INP_SRC_TYPE_TV\n");
        return FALSE;
    }

}
/*----------------------------------------------------------------------------
 * Name: _cancel_scan
 *
 * Description:
 *    This API is called when the user cancel the process by remote controller,
 * or the menu is paused somewhere.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _cancel_scan(BOOL b_is_select_ch)
{
    INT32  i4_ret;
    INT32  i4_scanned_analog_ch_num  = 0;
    INT32  i4_scanned_dig_ch_num     = 0;

    if(b_scan)
    {
        b_scan = FALSE;
        b_is_cancel = TRUE;
        /* cancel the antenna part */
        if(t_scan_antenna_atv.b_done == FALSE)
        {
            i4_ret = c_sb_cancel_scan(t_g_tuner_atsc.h_sb_anlg_air);
            if (i4_ret < 0)
            {
                TUNER_LOG_E("Can't cancel antenna analog scan,%d\r\n",i4_ret);
                return TSP_FAIL;
            }
        }
        if(t_scan_antenna_dtv.b_done == FALSE )
        {
            i4_ret = c_sb_cancel_scan(t_g_tuner_atsc.h_sb_dig_air);
            if (i4_ret < 0)
            {
                TUNER_LOG_E("Can't cancel  antenna digital scan,%d\r\n",i4_ret);
                return TSP_FAIL;
            }
        }
        /* cancel the cable part */
        if(b_scan_cable)
        {
            b_scan_cable = FALSE;
            if(t_scan_cable_atv.b_done == FALSE)
            {
                i4_ret = c_sb_cancel_scan(t_g_tuner_atsc.h_sb_anlg_cable);
                if (i4_ret < 0)
                {
                    TUNER_LOG_E("Can't cancel cable analog scan,%d\r\n",i4_ret);
                    return TSP_FAIL;
                }
            }
            if(t_scan_cable_dtv.b_done == FALSE)
            {
                i4_ret = c_sb_cancel_scan(t_g_tuner_atsc.h_sb_dig_cable);

                if (i4_ret < 0)
                {
                    TUNER_LOG_E("Can't cancel cable digital scan,%d\r\n",i4_ret);
                    return TSP_FAIL;
                }
            }
        }

        tuner_setup_scan_analog_get_val(&i4_scanned_analog_ch_num);

        tuner_setup_scan_digital_get_val(&i4_scanned_dig_ch_num);

        TUNER_LOG_I("i4_scanned_ch_num = %d\n\r", i4_scanned_analog_ch_num + i4_scanned_dig_ch_num);

        if ((i4_scanned_analog_ch_num + i4_scanned_dig_ch_num) <= 0 && !a_nav_tuner_setup_get_scan_new_channel())
        {
            /* if cannot scan the channels,should clear SVL/TSL. */
            /* clean antenna/cable channel table */
            i4_ret = _tuner_setup_clean_channel_table();

            a_cfg_set_crnt_channel_id(INVALID_CHANNEL_ID);
            a_cfg_set_last_channel_id(INVALID_CHANNEL_ID);
        }

        _on_scan_stop();
        a_cfg_ch_lst_store();

         //cli_parser("mw.svl.dump 1");

         if (TRUE == b_is_select_ch
            && TRUE == _crnt_is_tv_src()&&
            (_tuner_setup_get_wzd_state()!= OOBE_SCAN)&&
            (TRUE == a_am_is_power_on()))
         {
            /* select channel when current source is TV */
             _tuner_setup_select_crnt_or_first_channel(TRUE);
         }

        if((_tuner_setup_get_wzd_state()== OOBE_SCAN)||(FALSE == a_am_is_power_on()))
        {
             a_tv_unset_capability (TV_CAPABILITY_MASK_ALLOW_CHANNEL_CHANGE,
                     TV_CAPABILITY_MASK_ALLOW_CHANNEL_CHANGE);
            _tuner_setup_set_cfg_first_channel_id();
        }

    }

    return TSP_OK;
}


/*----------------------------------------------------------------------------
 * Name: _on_scan_stop
 *
 * Description:
 *      _on_scan_stop function is always invoked by the first message processing
 *  procedure when the scan completes. It could be the scan completion event from
 *  svl builder, abort event from user, or cancel event from user. It will set
 *  the b_scan variable to FALSE so that the following message processing procedure
 *  could realize the scan session is finished. However, it doesn't guarantee that
 *  the svl builder is in the AVAILABLE state. It should wait for both builder send
 *  one of the SB_REASON_COMPLETE, SB_REASON_ABORT, SB_REASON_CANCEL message.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_scan_stop()
{

    UTF16_T w2s_str_digital[50];
    UTF16_T w2s_num_digital[5];
    UTF16_T w2s_str_analog[50];
    UTF16_T w2s_num_analog[5];
    UINT32  ui4_len = 50;
    UINT32  i4_ret = TSP_OK;
    INT32   i4_num_analog = 0;
    INT32   i4_num_digital = 0;

    b_scan = FALSE;
    b_scan_cable = FALSE;

    c_memset(w2s_str_digital, 0, sizeof(w2s_str_digital));
    c_memset(w2s_str_analog,  0, sizeof(w2s_str_analog));
    c_memset(w2s_num_digital, 0, sizeof(w2s_num_digital));
    c_memset(w2s_num_analog,  0, sizeof(w2s_num_analog));

    /* show the message */
    /* Copy message */
    /* Append Analog Channels */
    i4_num_analog = t_scan_antenna_atv.i4_vir_ch_num + t_scan_cable_atv.i4_vir_ch_num;
    _itoa(w2s_num_analog, i4_num_analog, 4);
    c_uc_w2s_strncpy(w2s_str_analog, TUNER_TEXT(MLM_SETTINGS_KEY_CHANNEL_ANALOG),
                     ui4_len - c_uc_w2s_strlen(w2s_str_analog));
    c_uc_w2s_strncat(w2s_str_analog, w2s_num_analog,
                     ui4_len - c_uc_w2s_strlen(w2s_str_analog));

    /* Append Digital Channels */
    i4_num_digital = t_scan_antenna_dtv.i4_vir_ch_num + t_scan_cable_dtv.i4_vir_ch_num;
    _itoa(w2s_num_digital, i4_num_digital, 4);
    c_uc_w2s_strncpy(w2s_str_digital, TUNER_TEXT(MLM_SETTINGS_KEY_CHANNEL_DIGITAL),
                     ui4_len - c_uc_w2s_strlen(w2s_str_digital));
    c_uc_w2s_strncat(w2s_str_digital, w2s_num_digital,
                     ui4_len - c_uc_w2s_strlen(w2s_str_digital));

    i4_ret = _txt_info_set_text(w2s_str_digital,w2s_str_analog);
    RET_ON_ERR(i4_ret);

    /* disable the animation timer */
    c_timer_stop(h_timer_ani);

    if(0)
    {
        _bk_ch_back(tuner_get_crnt_svl());
    }

    nav_set_channel_scan_active(FALSE);

    nav_hide_component(NAV_COMP_ID_TUNER_SETUP);

    nav_return_activation(NAV_COMP_ID_TUNER_SETUP);


    TUNER_LOG_I("Finish to scan\r\n");

    /* channel scan status */
    if (b_is_cancel)
    {
        TUNER_LOG_I("[tuner set scan_status] ACFG_CUST_PARTIAL_SCAN\n");
        a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_PARTIAL_SCAN);
        b_is_cancel = FALSE;
    }
    else
    {
        TUNER_LOG_I("[tuner set scan_status] ACFG_CUST_COMPLETED_SCAN\n");
        a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_COMPLETED_SCAN);
    }
    return TSP_OK;
}

static INT32 _tuner_setup_clean_channel_table(VOID)
{
    INT32 i4_ret = SBR_OK;
    /* clean antenna */
    if(t_g_tuner_common.h_svl_air != NULL_HANDLE)
    {
        _bk_ch_preserve(t_g_tuner_common.h_svl_air);

        i4_ret = c_svl_clean(t_g_tuner_common.h_svl_air);
        if (i4_ret != SBR_OK)
        {
           TUNER_LOG_E("Can't clean AIR SVL. %d\r\n",i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }
        t_g_tuner_common.b_svl_air_dirty = TRUE;
    }

    if(t_g_tuner_common.h_tsl_air != NULL_HANDLE)
    {
        i4_ret = c_tsl_clean(t_g_tuner_common.h_tsl_air);
        if (i4_ret != SBR_OK)
        {
            TUNER_LOG_E("Can't clean AIR TSL. %d\r\n",i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }
        t_g_tuner_common.b_tsl_air_dirty = TRUE;
    }

    /* clean cable */
    if(t_g_tuner_common.h_svl_cable != NULL_HANDLE)
    {
        _bk_ch_preserve(t_g_tuner_common.h_svl_cable);

        i4_ret = c_svl_clean(t_g_tuner_common.h_svl_cable);
        if (i4_ret != SBR_OK)
        {
            TUNER_LOG_E("Can't clean CQAM SVL. %d\r\n",i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }
        t_g_tuner_common.b_svl_cable_dirty = TRUE;
    }

    if(t_g_tuner_common.h_tsl_cable != NULL_HANDLE)
    {
        i4_ret = c_tsl_clean(t_g_tuner_common.h_tsl_cable);
        if (i4_ret != SBR_OK)
        {
            TUNER_LOG_E("Can't clean cable TSL. %d\r\n",i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }
        t_g_tuner_common.b_tsl_cable_dirty = TRUE;
    }

    return SBR_OK;
}
/*----------------------------------------------------------------------------
 * Name:_tuner_setup_start_scan_cable
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
static INT32 _tuner_setup_start_scan_cable(VOID)
{
    INT32               i4_ret;
    SB_COND_T           e_cond;

    if (b_scan)
    {
        b_scan_cable = TRUE;

        /* Start scan the ATV channels*/
        SB_NTSC_SCAN_DATA_T t_ntsc_scan_data;

        TUNER_LOG_I("Scan Mode: NTSC/CABLE\r\n");

        /* udpate the sink name to builder */
        _tuner_atsc_update_sb_snk_name(t_g_tuner_atsc.h_sb_anlg_cable,
                                         _tuner_get_crnt_svctx());

        /* start scan */
        c_memset(&t_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));

#ifdef  APP_FUSION_TV_SUPPORT
        t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_CAB_FREQ_PLAN_STD|SB_NTSC_CAB_FREQ_PLAN_IRC;
#else
        t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_CAB_FREQ_PLAN_AUTO;
#endif
        t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_FULL_MODE;
        t_ntsc_scan_data.ui2_start_idx = 0;
        t_ntsc_scan_data.ui2_end_idx   = 0;

        t_scan_cable_atv.h_builder = t_g_tuner_atsc.h_sb_anlg_cable;

        i4_ret = c_sb_start_scan(t_g_tuner_atsc.h_sb_anlg_cable,
                                     &t_ntsc_scan_data,
                                     &t_scan_cable_atv,
                                     _tuner_setup_scan_nfy_fct,
                                     &e_cond);

        if (i4_ret != SBR_OK)
        {
            TUNER_LOG_E("Can't start scan,i4_ret:%d\r\n",i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }

        /* Start scan the DTV */
        SB_CQAM_SCAN_DATA_T t_cqam_scan_data;
        UINT8               ui1_freq;
        UINT32              ui4_mod;

        TUNER_LOG_I("Scan Mode: ATSC/CABLE\r\n");

        i4_ret = _get_freq_plan(&ui1_freq, &ui4_mod);
        if (i4_ret != TSP_OK)
        {
            TUNER_LOG_E("Wrong frequency plan mode,i4_ret:%d\r\n",i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }

        TUNER_LOG_I("Use CQAM mode to start scan\r\n");
        c_memset(&t_cqam_scan_data, 0, sizeof(SB_CQAM_SCAN_DATA_T));
        t_cqam_scan_data.e_scan_type   = SB_CQAM_SCAN_TYPE_FULL_MODE;
        t_cqam_scan_data.ui4_scan_info = 0;
        t_cqam_scan_data.ui1_freq_plan = ui1_freq;
        t_cqam_scan_data.ui4_mod_mask  = ui4_mod;

        t_scan_cable_dtv.h_builder = t_g_tuner_atsc.h_sb_dig_cable;
        _tuner_setup_url_put_update_channel();
        rest_event_notify("tv_settings/channels/channel_scan_state", 0, "");//scan start

        i4_ret = c_sb_start_scan(t_g_tuner_atsc.h_sb_dig_cable,
                                     &t_cqam_scan_data,
                                     &t_scan_cable_dtv,
                                     _tuner_setup_scan_nfy_fct,
                                     &e_cond);

        if (i4_ret != SBR_OK)
        {
            TUNER_LOG_E("Can't start scan,i4_ret:%d\r\n",i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }

        /* set up the dirty flags for storing SVL and TSL */
        t_g_tuner_common.b_svl_cable_dirty = TRUE;
        t_g_tuner_common.b_tsl_cable_dirty = TRUE;

        /* set the corresponding widget */
        i4_ret = _txt_info_animate_update(FALSE);
        if(i4_ret < 0)
        {
           TUNER_LOG_E("Can't change scan text,i4_ret:%d\r\n",i4_ret);
        }
        TUNER_LOG_I("Start to scan cable\r\n");
    }

    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name:_tuner_setup_start_scan_antenna
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
 static INT32 _tuner_setup_start_scan_antenna(VOID)
{
    INT32               i4_ret;
    SB_COND_T           e_cond;

    DBG_LOG_PRINT(("[tuner setup] _tuner_setup_start_scan_antenna=%d b_scan=%d\n",__LINE__,b_scan));
    if (!b_scan)
    {
        VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(FALSE);
        VIZIO_CTRL_ENABLE_SPI_HW_MODE(FALSE);
        _tuner_setup_enable_ch_chg(TRUE);
        a_cfg_cust_set_ch_scan_progress(0);    //Need clear scan progress before start scan
        /* close service context */
        i4_ret = c_svctx_sync_stop_svc(_tuner_get_crnt_svctx(),
                                       DEFAULT_STOP_SVC_TIMEOUT);
        if (i4_ret == SVCTXR_TIMEOUT)
        {
            TUNER_LOG_E("Cannot close service context timeout. i4_ret:%d\r\n",i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }
        else if (i4_ret != SVCTXR_OK && i4_ret != SVCTXR_ALREADY_STOPPED)
        {
            TUNER_LOG_E("Cannot close service context. %d\r\n", i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }

        TUNER_LOG_I("_tuner_setup_start_scan_antenna. b_clean_lists=%d\r\n",b_clean_lists);

        /* clean the service list */
        if(b_clean_lists && !a_nav_tuner_setup_get_scan_new_channel())
        {
            TUNER_LOG_I("clean AIR SVL.\r\n");

            /* clean antenna/cable channel table */
            i4_ret = _tuner_setup_clean_channel_table();
            if(i4_ret < 0)
            {
                TUNER_LOG_E("_tuner_setup_clean_channel_table fail\r\n");
            }
            a_cfg_ch_lst_store();

            a_cfg_set_crnt_channel_id(INVALID_CHANNEL_ID);
            a_cfg_set_last_channel_id(INVALID_CHANNEL_ID);
        }

        /* reset the status of update list */

        /* Start scan the ATV channels*/
        SB_NTSC_SCAN_DATA_T t_ntsc_scan_data;

        TUNER_LOG_I("Scan Mode: NTSC/AIR,\r\n");

        /* udpate the sink name to builder */
        _tuner_atsc_update_sb_snk_name(t_g_tuner_atsc.h_sb_anlg_air,
                                         _tuner_get_crnt_svctx());

        /* start scan */
        c_memset(&t_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));

        t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_TER_FREQ_PLAN;
        t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_FULL_MODE;
        t_ntsc_scan_data.ui2_start_idx = 0;
        t_ntsc_scan_data.ui2_end_idx   = 0;

        t_scan_antenna_atv.h_builder = t_g_tuner_atsc.h_sb_anlg_air;

        i4_ret = c_sb_start_scan(t_g_tuner_atsc.h_sb_anlg_air,
                                     &t_ntsc_scan_data,
                                     &t_scan_antenna_atv,
                                     _tuner_setup_scan_nfy_fct,
                                     &e_cond);
        if (i4_ret != SBR_OK)
        {
            TUNER_LOG_E("Can't start scan,i4_ret:%d\r\n",i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }

        /* Start scan the DTV */

        SB_ATSC_SCAN_DATA_T t_atsc_scan_data;

        TUNER_LOG_I("Scan Mode: ATSC/AIR\r\n");
        c_memset(&t_atsc_scan_data, 0, sizeof(SB_ATSC_SCAN_DATA_T));
        t_atsc_scan_data.e_scan_type   = SB_ATSC_SCAN_TYPE_FULL_MODE;
        t_atsc_scan_data.ui4_scan_info = 0;

        t_scan_antenna_dtv.h_builder = t_g_tuner_atsc.h_sb_dig_air;
        _tuner_setup_url_put_update_channel();
        rest_event_notify("tv_settings/channels/channel_scan_state", 0, "");//scan start

        i4_ret = c_sb_start_scan(t_g_tuner_atsc.h_sb_dig_air,
                                     &t_atsc_scan_data,
                                     &t_scan_antenna_dtv,
                                     _tuner_setup_scan_nfy_fct,
                                     &e_cond);

        if (i4_ret != SBR_OK)
        {
            TUNER_LOG_E("Can't start scan,i4_ret:%d\r\n",i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }


        /* set up the dirty flags for storing SVL and TSL */
        t_g_tuner_common.b_svl_air_dirty = TRUE;
        t_g_tuner_common.b_tsl_air_dirty = TRUE;

        /* Init the antenna scan relative data */
        b_scan = TRUE;
        t_scan_antenna_atv.i4_vir_ch_num = 0;
        t_scan_antenna_atv.i4_phy_ch_num = 0;
        t_scan_antenna_atv.i4_phy_ch_ttl = 68;  /* assign a big enough value */
        t_scan_antenna_atv.b_done = FALSE;
        t_scan_antenna_dtv.i4_vir_ch_num = 0;
        t_scan_antenna_dtv.i4_phy_ch_num = 0;
        t_scan_antenna_dtv.i4_phy_ch_ttl = 68;  /* assign a big enough value */
        t_scan_antenna_dtv.b_done = FALSE;

                /* set up the dirty flags for storing SVL and TSL */
        t_g_tuner_common.b_svl_cable_dirty = TRUE;
        t_g_tuner_common.b_tsl_cable_dirty = TRUE;

        /* Init the cable scan relative data */
        t_scan_cable_atv.i4_vir_ch_num = 0;
        t_scan_cable_atv.i4_phy_ch_num = 0;
        t_scan_cable_atv.i4_phy_ch_ttl = 135;  /* assign a big enough value */
        t_scan_cable_atv.b_done = FALSE;
        t_scan_cable_dtv.i4_vir_ch_num = 0;
        t_scan_cable_dtv.i4_phy_ch_num = 0;
        t_scan_cable_dtv.i4_phy_ch_ttl = 135;  /* assign a big enough value */
        t_scan_cable_dtv.b_done = FALSE;

        /* set the corresponding widget */
        i4_ret = _txt_info_animate_update(FALSE);
        if(i4_ret < 0)
        {
           TUNER_LOG_E("Can't change scan text,i4_ret:%d\r\n",i4_ret);
        }

        /* enable the animation timer */
        i4_ret = c_timer_start(h_timer_ani,
                               1000,
                               X_TIMER_FLAG_REPEAT,
                               _timer_animation_fct,
                               NULL);
        if(i4_ret < 0)
        {
            TUNER_LOG_E("Can't start animation timer ,i4_ret=%d\r\n",i4_ret);
        }

        TUNER_LOG_I("Start to scan antenna\r\n");
    }

    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: _touch_svl_record
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
static INT32 _touch_svl_record (
    HANDLE_T                    h_svl ,
    SVL_REC_T*                  pt_svl_rec
    )
{
    if (!pt_svl_rec)
    {
        return TSP_FAIL;
    }
    INT32 i4_ret = 0;

    pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask |= SB_MAKE_VNET_USER(_SB_VNET_CUST_CH_TOUCHED) ;

    c_svl_lock(h_svl);

    i4_ret = c_svl_update_rec(h_svl,pt_svl_rec,TRUE);

    c_svl_unlock(h_svl);

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: _do_animation_timer
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
static VOID _do_animation_timer(VOID* pv_data1,
                                VOID* pv_data2,
                                VOID* pv_data3)
{
    _txt_info_animate_update(FALSE);
    c_wgl_repaint(tg_scan_view.h_frm, NULL, FALSE);
}

/*----------------------------------------------------------------------------
 * Name: _timer_animation_fct
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
static VOID _timer_animation_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    nav_request_context_switch(_do_animation_timer,NULL, NULL,NULL);
}


/*----------------------------------------------------------------------------
 * Name: _do_show_toast_view_timer
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
static VOID _do_show_toast_view_timer(VOID* pv_data1,
                                VOID* pv_data2,
                                VOID* pv_data3)
{
    //a_wdk_toast_hide(FALSE,&tg_toast_param,&t_g_wdk_view);
    tuner_setup_warning_hide();

    if(*(INT32*)pv_data1 == 0)
    {
        _tuner_setup_enable_ch_chg(FALSE);
        nav_hide_component(NAV_COMP_ID_TUNER_SETUP);

        nav_return_activation(NAV_COMP_ID_TUNER_SETUP);

        if(b_repaint)
        {
            _tuner_setup_select_crnt_or_first_channel(TRUE);
        }
    }
    else if(*(INT32*)pv_data1 == 1)
    {
        if (FALSE == nav_is_channel_scan_active())
        {
            TUNER_LOG_I("\n nav_return_activation(NAV_COMP_ID_TUNER_SETUP)\n");
            /* not at scanning state, we should exit tuner setup component. */
            nav_hide_component(NAV_COMP_ID_TUNER_SETUP);

            nav_return_activation(NAV_COMP_ID_TUNER_SETUP);

        }
    }

}


/*----------------------------------------------------------------------------
 * Name: _do_show_toast_no_signal_view_timer
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
static VOID _do_show_toast_no_signal_view_timer(VOID* pv_data1,
                                VOID* pv_data2,
                                VOID* pv_data3)
{

    TV_WIN_ID_T      e_tv_win_id;
    nav_get_focus_id(&e_tv_win_id);
    if(nav_is_signal_loss(e_tv_win_id))
    {
        nav_dispatch_msg_to_component(NAV_COMP_ID_SCREEN_SAVER,
                          NAV_UI_MSG_NO_SIGNAL,
                          NULL
                          );
    }
}


/*----------------------------------------------------------------------------
 * Name: _timer_show_toast_view_fct
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
static VOID _timer_show_toast_view_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    nav_request_context_switch(_do_show_toast_view_timer,pv_tag, NULL,NULL);
}

/*----------------------------------------------------------------------------
 * Name: _timer_show_toast_no_signal_fct
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
static VOID _timer_show_toast_no_signal_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    nav_request_context_switch(_do_show_toast_no_signal_view_timer,pv_tag, NULL,NULL);
}


/*----------------------------------------------------------------------------
 * Name: _update_ch_lst
 *
 * Description:
 *   1) This function will be called when scan started (Must later than svl clean)
 *   2) This function will be called when mesage "SB_REASON_PROGRESS" received
 *   3) Static varialbe ui4_ch_id_ana & ui4_ch_id_dig will be used for
 *      remembering the latest updated channel, then when next "SB_REASON_PROGRESS"
 *      received, we can use it to differ who is the latest updated channel.
 *   4) need reset ui4_ch_id_ana & ui4_ch_id_dig each time scan start
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _update_ch_lst (
    BOOL                        b_update_atv ,
    UINT16                      ui2_update_num
    )
{
    UINT32                      ui4_ch_id = 0 ;
    UINT16                      ui2_idx = 0 ;
    BOOL                        b_found = FALSE;
    SVL_REC_T                   t_svl_rec ;
    HANDLE_T                    h_svl = tuner_get_crnt_svl () ;
    INT32                       i4_ret = 0;

    c_svl_lock(h_svl);

    /* find out the latest updated channels */
    ui2_idx = 0 ;

    do
    {
        /* get next svl record */
         b_found = a_tv_get_svl_rec_by_logic_and_nw_masks (
                                    h_svl,
                                    SB_VNET_ACTIVE|SB_VNET_FAKE|SB_MAKE_VNET_USER(_SB_VNET_CUST_CH_TOUCHED),
                                    SB_VNET_ACTIVE,
                                    TV_ITERATE_DIR_NEXT_NO_LOOP,
                                    &ui4_ch_id ,
                                    &t_svl_rec);
        if (!b_found)
        {
            break ;
        }

        if ((b_update_atv && BRDCST_TYPE_ANALOG != t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
             ||
            (!b_update_atv && BRDCST_TYPE_ANALOG == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type) )
        {
             /* continue to get the next svl record if broadcast not matched */
            continue ;
        }
            /* set touch flag for this recoed ,this means the record has touched
                 * it will skip this record for next loop
                 */
        i4_ret = _touch_svl_record (h_svl ,&t_svl_rec);
        if(i4_ret < 0)
        {
            TUNER_LOG_E("_touch_svl_record fail,i4_ret:%d\r\n",i4_ret);
        }

        ui2_idx ++ ;
        if (ui2_idx >= ui2_update_num)
        {
            break ;
        }
    }while (1) ;

    c_svl_unlock(h_svl);

    return TSP_OK ;
}


/*----------------------------------------------------------------------------
 * Name: _do_show_warning_nfy
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
static VOID _do_show_warning_nfy(VOID* pv_data1,
                                VOID* pv_data2,
                                VOID* pv_data3)
{

    INT32       i4_ret;
    UTF16_T     w2s_tmp_str[128] = {0};

    //
    if(!b_repaint)
    {
        c_uc_w2s_strcpy(w2s_tmp_str,TUNER_WARNINGS_TEXT(MLM_WARNINGS_KEY_WARNING_15));

        i4_ret = _tuner_setup_warning_toast_view(tg_scan_view.h_canvas,w2s_tmp_str);
        if (i4_ret != TSP_OK)
        {
            TUNER_LOG_E("_tuner_setup_warning_toast_view fail ,i4_ret:%d\r\n",i4_ret);
        }

        i4_ret = c_timer_start(h_timer_show_no_signal,
                        5000,
                        X_TIMER_FLAG_ONCE,
                        _timer_show_toast_no_signal_fct,
                        NULL);
    }
    else
    {
        c_uc_w2s_strcpy(w2s_tmp_str,TUNER_WARNINGS_TEXT(MLM_WARNINGS_KEY_WARNING_39));
        i4_ret = _tuner_setup_warning_toast_view(tg_scan_view.h_canvas,w2s_tmp_str);
        if (i4_ret != TSP_OK)
        {
           TUNER_LOG_E("_tuner_setup_warning_toast_view fail,i4_ret:%d\r\n",i4_ret);
        }
    }

}


static VOID  _tuner_setup_clear_scan_table_list(VOID)
{
    if (NULL != pt_g_tsl_rec_list)
    {
        OCL_MEM_FREE(pt_g_tsl_rec_list);

        pt_g_tsl_rec_list = NULL;
    }

    if (NULL != pt_g_tsl_rec_list_cable)
    {
        OCL_MEM_FREE(pt_g_tsl_rec_list_cable);

        pt_g_tsl_rec_list_cable = NULL;
    }

}

/*----------------------------------------------------------------------------
 * Name:_tuner_setup_create_air_tsl_table
 *
 * Description: The function of create air tsl record table.
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_create_air_tsl_table()
{
    INT32       i4_ret         = 0;
    UINT32      ui4_ver_id     = SVL_NULL_VER_ID;

    /* if one channel list exsit then recreate */
    if (NULL != pt_g_tsl_rec_list)
    {
        OCL_MEM_FREE(pt_g_tsl_rec_list);

        pt_g_tsl_rec_list = NULL;
    }

    ui2_g_tsl_num  = 0;

    i4_ret = c_tsl_get_num_recs(t_g_tuner_common.h_tsl_air,
                                &ui2_g_tsl_num,
                                &ui4_ver_id
                                );
    if (TSLR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("[tuner setup view]Error: c_tsl_get_num_recs ret=[%d], line=[%d]", i4_ret, __LINE__));
        return -1;
    }

    TUNER_LOG_I("function=%s, ui2_tsl_num=%d \r\n",  __FUNCTION__, ui2_g_tsl_num);

    if (ui2_g_tsl_num > 0)
    {
        pt_g_tsl_rec_list = (TSL_REC_T *)c_mem_alloc(ui2_g_tsl_num * sizeof(TSL_REC_T));
        if (NULL == pt_g_tsl_rec_list)
        {
            DBG_LOG_PRINT(("[tuner setup view]Error:c_mem_alloc(ui2_tsl_num) \n"));
            return -2;
        }
    }

    c_memset(pt_g_tsl_rec_list, 0x0, ui2_g_tsl_num * sizeof(TSL_REC_T));

    for (UINT16 ui2_i = 0; ui2_i < ui2_g_tsl_num; ui2_i ++)
    {
        i4_ret = c_tsl_get_rec_by_rec_idx(t_g_tuner_common.h_tsl_air,
                                ui2_i,
                                (pt_g_tsl_rec_list + ui2_i),
                                &ui4_ver_id);

        if (TSLR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[tuner setup view]Error: c_tsl_get_rec_by_rec_idx ret=[%d], ui2_i=[%d]", i4_ret, ui2_i));
            return -1;
        }

        //TUNER_LOG_I(("[tuner setup view]c_tsl_get_rec_by_rec_idx ui2_tsl_rec_id=[%d], ui4_freq=[%d] \n",
        //                                        pt_g_tsl_rec_list[ui2_i].ui2_tsl_rec_id ,
        //                                        pt_g_tsl_rec_list[ui2_i].udata.t_ter_ana.ui4_freq));

    }

    return 0;
}


/*----------------------------------------------------------------------------
 * Name:_tuner_setup_create_air_tsl_table
 *
 * Description: The function of create air tsl record table.
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_create_cable_tsl_table()
{
    INT32       i4_ret         = 0;
    UINT32      ui4_ver_id     = SVL_NULL_VER_ID;

    /* if one channel list exsit then recreate */
    if (NULL != pt_g_tsl_rec_list_cable)
    {
        OCL_MEM_FREE(pt_g_tsl_rec_list_cable);

        pt_g_tsl_rec_list_cable = NULL;
    }

    ui2_g_tsl_num_cable  = 0;

    i4_ret = c_tsl_get_num_recs(t_g_tuner_common.h_tsl_cable,
                                &ui2_g_tsl_num_cable,
                                &ui4_ver_id
                                );
    if (TSLR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("[tuner setup view]Error: c_tsl_get_num_recs ret=[%d], line=[%d]", i4_ret, __LINE__));
        return -1;
    }

    TUNER_LOG_I("function=%s, ui2_tsl_num=%d \r\n",  __FUNCTION__, ui2_g_tsl_num_cable);

    if (ui2_g_tsl_num_cable > 0)
    {
        pt_g_tsl_rec_list_cable = (TSL_REC_T *)c_mem_alloc(ui2_g_tsl_num_cable * sizeof(TSL_REC_T));
        if (NULL == pt_g_tsl_rec_list_cable)
        {
            DBG_LOG_PRINT(("[tuner setup view]Error:c_mem_alloc(ui2_tsl_num) \n"));
            return -2;
        }
    }

    c_memset(pt_g_tsl_rec_list_cable, 0x0, ui2_g_tsl_num_cable * sizeof(TSL_REC_T));

    for (UINT16 ui2_i = 0; ui2_i < ui2_g_tsl_num_cable; ui2_i ++)
    {
        i4_ret = c_tsl_get_rec_by_rec_idx(t_g_tuner_common.h_tsl_cable,
                                ui2_i,
                                (pt_g_tsl_rec_list_cable + ui2_i),
                                &ui4_ver_id);

        if (TSLR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[tuner setup view]Error: c_tsl_get_rec_by_rec_idx ret=[%d], ui2_i=[%d]", i4_ret, ui2_i));
            return -1;
        }

        //TUNER_LOG_I(("[tuner setup view]c_tsl_get_rec_by_rec_idx ui2_tsl_rec_id=[%d], ui4_freq=[%d] \n",
        //                                        pt_g_tsl_rec_list[ui2_i].ui2_tsl_rec_id ,
        //                                        pt_g_tsl_rec_list[ui2_i].udata.t_ter_ana.ui4_freq));

    }

    return 0;
}


/*----------------------------------------------------------------------------
 * Name:_tuner_setup_create_air_tsl_table
 *
 * Description: The function of get svl by tsl record id.
 *
 *
 * Inputs:
 *
 * Outputs:pt_svl_rec
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_get_tsl_rec_by_freq(UINT32      ui4_freq,
                                              TSL_REC_T   *pt_tsl_rec)
{
    if (NULL == pt_tsl_rec)
    {
        return -1;
    }

    TUNER_LOG_I("function=%s, ui4_freq=%d \r\n",  __FUNCTION__, ui4_freq);

    if (ui2_g_tsl_num > 0)
    {
        for (UINT16 ui2_i = 0; ui2_i < ui2_g_tsl_num; ui2_i ++)
        {
            /* regard as the same channel when frequence +/-100kHZ */
            if (ABS((INT32)ui4_freq - (INT32)pt_g_tsl_rec_list[ui2_i].udata.t_ter_ana.ui4_freq) < 100001)
            {
                DBG_LOG_PRINT(("[tuner setup view]Matched the freq, src freq=[%d], target ui2_i=[%d], target freq=[%d]\n",
                                                                ui4_freq,
                                                                ui2_i,
                                                                pt_g_tsl_rec_list[ui2_i].udata.t_ter_ana.ui4_freq));
                c_memcpy(pt_tsl_rec, (pt_g_tsl_rec_list + ui2_i), sizeof(TSL_REC_T));

                return SVLR_OK;
            }
        }
    }

    return -2;
}


/*----------------------------------------------------------------------------
 * Name:_tuner_setup_create_air_tsl_table
 *
 * Description: The function of get svl by tsl record id.
 *
 *
 * Inputs:
 *
 * Outputs:pt_svl_rec
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_get_tsl_rec_by_freq_cable(UINT32      ui4_freq,
                                              TSL_REC_T   *pt_tsl_rec)
{
    if (NULL == pt_tsl_rec)
    {
        return -1;
    }

    TUNER_LOG_I("function=%s, ui4_freq=%d \r\n",  __FUNCTION__, ui4_freq);

    if (ui2_g_tsl_num_cable > 0)
    {
        for (UINT16 ui2_i = 0; ui2_i < ui2_g_tsl_num_cable; ui2_i ++)
        {
            /* regard as the same channel when frequence +/-100kHZ */
            if (ABS((INT32)ui4_freq - (INT32)pt_g_tsl_rec_list_cable[ui2_i].udata.t_ter_ana.ui4_freq) < 100001)
            {
                DBG_LOG_PRINT(("[tuner setup view]Matched the freq, src freq=[%d], target ui2_i=[%d], target freq=[%d]\n",
                                                                ui4_freq,
                                                                ui2_i,
                                                                pt_g_tsl_rec_list_cable[ui2_i].udata.t_ter_ana.ui4_freq));
                c_memcpy(pt_tsl_rec, (pt_g_tsl_rec_list_cable + ui2_i), sizeof(TSL_REC_T));

                return SVLR_OK;
            }
        }
    }

    return -2;
}


/*----------------------------------------------------------------------------
 * Name:_tuner_setup_get_svl_rec_by_rf_index
 *
 * Description: The function of get svl by rf index.
 *
 *
 * Inputs:
 *
 * Outputs:pt_svl_rec
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_get_svl_rec_by_rf_index(HANDLE_T     h_svl,
                                                 UINT16 ui2_tuner_type,
                                                 UINT16      ui2_rf_ch,
                                                 SVL_REC_T   *pt_svl_rec)
{
    if (NULL == pt_svl_rec)
    {
        return -1;
    }

    UINT32      ui4_ver_id = SVL_NULL_VER_ID;
    INT32       i4_ret     = 0;
    BOOL        b_is_fake    = FALSE;

    c_memset(pt_svl_rec, 0x0, sizeof(SVL_REC_T));
    ui4_ver_id = 0;
    /* Try to get analog SVL record */
    i4_ret = c_svl_get_rec_by_ts(h_svl,
                      ui2_tuner_type,
                      SB_MAKE_ANA_TSL_REC_ID(ui2_rf_ch),
                      SB_VNET_ACTIVE,
                      0,
                      pt_svl_rec,
                      &ui4_ver_id);
    /* can get the record
     * && is not the FAKE channel
    */
    if(i4_ret == SVLR_OK)
    {
        b_is_fake = (pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE) > 0 ? TRUE : FALSE;
        TUNER_LOG_I("function=%s, ui4_nw_mask=0x%x, b_is_fake:%d \r\n",  __FUNCTION__, pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask, b_is_fake);
        if (TRUE == b_is_fake)
        {
            TUNER_LOG_I("function=%s,FAKE channel, ignore it.\r\n", __FUNCTION__);
            c_memset(pt_svl_rec, 0x0, sizeof(SVL_REC_T));

            return -2;
        }
        else
        {
            TUNER_LOG_I("function=%s,not FAKE channel,get channel success.\r\n", __FUNCTION__);
            return SVLR_OK;
        }
    }

    return -3;
}

/*----------------------------------------------------------------------------
 * Name: _tuner_setup_is_freq_nearer_prev
 *
 * Description: the abs(frequence - center_frequence) is nearer previous ?
 *
 *
 * Inputs:
 *
 * Outputs:pt_svl_rec
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _tuner_setup_is_freq_nearer_prev(TSL_REC_T   t_tsl_rec_antenna,
                                        TSL_REC_T   t_tsl_rec_cable)
{
    if (ABS((INT32)t_tsl_rec_antenna.udata.t_ter_ana.ui4_freq - (INT32)t_tsl_rec_antenna.udata.t_ter_ana.ui4_central_freq) < ABS((INT32)t_tsl_rec_cable.udata.t_ter_ana.ui4_freq - (INT32)t_tsl_rec_cable.udata.t_ter_ana.ui4_central_freq))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

/*----------------------------------------------------------------------------

 * Name: _tuner_setup_rm_duplicate_ch
 *
 * Description: The function will set the SVL to FAKE which frequence is farther when them has the same frequence.
 *
 *
 * Inputs:
 *
 * Outputs:pt_svl_rec
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_rm_farther_ch(UINT16      ui2_rf_ch,
                                          HANDLE_T    h_svl_air,
                                          HANDLE_T    h_svl_cable)
{
    INT32       i4_ret            = 0;
    SVL_REC_T   t_svl_rec_antenna = {0};
    SVL_REC_T   t_svl_rec_cable   = {0};
    TSL_REC_T   t_tsl_rec_antenna = {0};
    TSL_REC_T   t_tsl_rec_cable   = {0};
    UINT32      ui4_ver_id = SVL_NULL_VER_ID;

    c_memset(&t_svl_rec_antenna, 0x0, sizeof(SVL_REC_T));
    c_memset(&t_svl_rec_cable, 0x0, sizeof(SVL_REC_T));
    c_memset(&t_tsl_rec_antenna, 0x0, sizeof(TSL_REC_T));
    c_memset(&t_tsl_rec_cable, 0x0, sizeof(TSL_REC_T));

    TUNER_LOG_I("Enter _tuner_setup_rm_farther_ch ui2_rf_ch=%d line:%d\n", ui2_rf_ch,__LINE__);

    /* Try to get cable SVL record */
    i4_ret = _tuner_setup_get_svl_rec_by_rf_index(h_svl_cable,
                                                  CABLE_SVL_ID,
                                                  ui2_rf_ch,
                                                  &t_svl_rec_cable);
    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("i4_ret=%d,_tuner_setup_get_svl_rec_by_rf_index(CABLE_SVL_ID), ui2_rf_ch=%d \r\n", i4_ret, ui2_rf_ch);
        return -2;
    }

    /* get the tsl record by tsl record id */
    i4_ret =  c_tsl_get_rec(t_g_tuner_common.h_tsl_cable,
                            t_svl_rec_cable.uheader.t_rec_hdr.ui2_tsl_rec_id,
                            &t_tsl_rec_cable,
                            &ui4_ver_id);

    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("i4_ret=%d,c_tsl_get_rec(ui2_tsl_rec_id), ui2_tsl_rec_id=%d \r\n", i4_ret, t_svl_rec_cable.uheader.t_rec_hdr.ui2_tsl_rec_id);
        return -3;
    }

    /* get the air TSL record by the cable same frequency */
    i4_ret = _tuner_setup_get_tsl_rec_by_freq(t_tsl_rec_cable.udata.t_ter_ana.ui4_freq, &t_tsl_rec_antenna);

    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("i4_ret=%d,_tuner_setup_get_tsl_rec_by_freq(ui4_freq), ui4_freq=%d \r\n", i4_ret, t_tsl_rec_cable.udata.t_ter_ana.ui4_freq);
        return -4;
    }

    TUNER_LOG_I("line=%d,_tuner_setup_get_tsl_rec_by_freq(ui4_freq), ui4_freq=%d, tsl_rec_id=[%d]\r\n",
                                                             __LINE__,
                                                             t_tsl_rec_cable.udata.t_ter_ana.ui4_freq,
                                                             t_tsl_rec_antenna.ui2_tsl_rec_id);
    i4_ret =  c_svl_get_rec_by_ts(h_svl_air,
                                  ANTENNA_SVL_ID,
                                  t_tsl_rec_antenna.ui2_tsl_rec_id,
                                  SB_VNET_ACTIVE,
                                  0,/* first */
                                  &t_svl_rec_antenna,
                                  &ui4_ver_id);

    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("i4_ret=%d,c_svl_get_rec_by_ts(ui2_tsl_rec_id), ui2_tsl_rec_id=%d \r\n", i4_ret, t_tsl_rec_antenna.ui2_tsl_rec_id);
        return -7;
    }

    if (_tuner_setup_is_freq_nearer_prev(t_tsl_rec_antenna, t_tsl_rec_cable))
    {
        /* rm the cable channel due to nearer frequence of air */
        /* rm == set the SVL to FAKE channel */
        t_svl_rec_cable.uheader.t_rec_hdr.ui4_nw_mask |= SB_VNET_FAKE;

        TUNER_LOG_I("set the SVL to FAKE channel, ch_id=[%d], line=%d\n", t_svl_rec_cable.uheader.t_rec_hdr.ui4_channel_id, __LINE__);

        /* Update SVL */
        c_svl_lock(h_svl_cable);

        i4_ret = c_svl_update_rec(h_svl_cable, &t_svl_rec_cable, TRUE);

        c_svl_unlock(h_svl_cable);

        if (i4_ret != SVLR_OK)
        {
            TUNER_LOG_E("Can't update record. i4_ret:%d\n",i4_ret);
            return -5;
        }
    }
    else
    {
        /* rm the air channel due to nearer frequence of cable */
        /* rm == set the SVL to FAKE channel */
        t_svl_rec_antenna.uheader.t_rec_hdr.ui4_nw_mask |= SB_VNET_FAKE;

        TUNER_LOG_I("set the SVL to FAKE channel, ch_id=[%d], line=%d\n", t_svl_rec_antenna.uheader.t_rec_hdr.ui4_channel_id, __LINE__);

        /* Update SVL */
        c_svl_lock(h_svl_air);

        i4_ret = c_svl_update_rec(h_svl_air, &t_svl_rec_antenna, TRUE);

        c_svl_unlock(h_svl_air);

        if (i4_ret != SVLR_OK)
        {
            TUNER_LOG_E("Can't update record. i4_ret:%d\n",i4_ret);
            return -6;
        }

    }

    return SVLR_OK;
}


/*----------------------------------------------------------------------------

 * Name: _tuner_setup_rm_duplicate_ch
 *
 * Description: The function will set the SVL to FAKE which frequence is farther when them has the same frequence.
 *
 *
 * Inputs:
 *
 * Outputs:pt_svl_rec
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_rm_farther_ch_cable(UINT16      ui2_rf_ch,
                                          HANDLE_T    h_svl_air,
                                          HANDLE_T    h_svl_cable)
{
    INT32       i4_ret            = 0;
    SVL_REC_T   t_svl_rec_antenna = {0};
    SVL_REC_T   t_svl_rec_cable   = {0};
    TSL_REC_T   t_tsl_rec_antenna = {0};
    TSL_REC_T   t_tsl_rec_cable   = {0};
    UINT32      ui4_ver_id = SVL_NULL_VER_ID;

    c_memset(&t_svl_rec_antenna, 0x0, sizeof(SVL_REC_T));
    c_memset(&t_svl_rec_cable, 0x0, sizeof(SVL_REC_T));
    c_memset(&t_tsl_rec_antenna, 0x0, sizeof(TSL_REC_T));
    c_memset(&t_tsl_rec_cable, 0x0, sizeof(TSL_REC_T));

    TUNER_LOG_I("Enter _tuner_setup_rm_farther_ch_for_pre ui2_rf_ch=%d line:%d\n", ui2_rf_ch,__LINE__);

    /* Try to get cable SVL record */
    i4_ret = _tuner_setup_get_svl_rec_by_rf_index(h_svl_air,
                                                  ANTENNA_SVL_ID,
                                                  ui2_rf_ch,
                                                  &t_svl_rec_antenna);
    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("i4_ret=%d,_tuner_setup_get_svl_rec_by_rf_index(ANTENNA_SVL_ID), ui2_rf_ch=%d \r\n", i4_ret, ui2_rf_ch);
        return -2;
    }

    /* get the tsl record by tsl record id */
    i4_ret =  c_tsl_get_rec(t_g_tuner_common.h_tsl_air,
                            t_svl_rec_antenna.uheader.t_rec_hdr.ui2_tsl_rec_id,
                            &t_tsl_rec_antenna,
                            &ui4_ver_id);

    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("i4_ret=%d,c_tsl_get_rec(ui2_tsl_rec_id), ui2_tsl_rec_id=%d \r\n", i4_ret, t_svl_rec_antenna.uheader.t_rec_hdr.ui2_tsl_rec_id);
        return -3;
    }

    /* get the cable TSL record by the air same frequency */
    i4_ret = _tuner_setup_get_tsl_rec_by_freq_cable(t_tsl_rec_antenna.udata.t_ter_ana.ui4_freq, &t_tsl_rec_cable);

    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("i4_ret=%d,_tuner_setup_get_tsl_rec_by_freq(ui4_freq), ui4_freq=%d \r\n", i4_ret, t_tsl_rec_antenna.udata.t_ter_ana.ui4_freq);
        return -4;
    }

    TUNER_LOG_I("line=%d,_tuner_setup_get_tsl_rec_by_freq(ui4_freq), ui4_freq=%d, tsl_rec_id=[%d]\r\n",
                                                             __LINE__,
                                                             t_tsl_rec_antenna.udata.t_ter_ana.ui4_freq,
                                                             t_tsl_rec_cable.ui2_tsl_rec_id);
    i4_ret =  c_svl_get_rec_by_ts(h_svl_cable,
                                  CABLE_SVL_ID,
                                  t_tsl_rec_cable.ui2_tsl_rec_id,
                                  SB_VNET_ACTIVE,
                                  0,/* first */
                                  &t_svl_rec_cable,
                                  &ui4_ver_id);

    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("i4_ret=%d,c_svl_get_rec_by_ts(ui2_tsl_rec_id), ui2_tsl_rec_id=%d \r\n", i4_ret, t_tsl_rec_cable.ui2_tsl_rec_id);
        return -7;
    }

    if (_tuner_setup_is_freq_nearer_prev(t_tsl_rec_antenna, t_tsl_rec_cable))
    {
        /* rm the cable channel due to nearer frequence of air */
        /* rm == set the SVL to FAKE channel */
        t_svl_rec_cable.uheader.t_rec_hdr.ui4_nw_mask |= SB_VNET_FAKE;

        TUNER_LOG_I("set the SVL to FAKE channel, ch_id=[%d], line=%d\n", t_svl_rec_cable.uheader.t_rec_hdr.ui4_channel_id, __LINE__);

        /* Update SVL */
        c_svl_lock(h_svl_cable);

        i4_ret = c_svl_update_rec(h_svl_cable, &t_svl_rec_cable, TRUE);

        c_svl_unlock(h_svl_cable);

        if (i4_ret != SVLR_OK)
        {
            TUNER_LOG_E("Can't update record. i4_ret:%d\n",i4_ret);
            return -5;
        }
    }
    else
    {
        /* rm the air channel due to nearer frequence of cable */
        /* rm == set the SVL to FAKE channel */
        t_svl_rec_antenna.uheader.t_rec_hdr.ui4_nw_mask |= SB_VNET_FAKE;

        TUNER_LOG_I("set the SVL to FAKE channel, ch_id=[%d], line=%d\n", t_svl_rec_antenna.uheader.t_rec_hdr.ui4_channel_id, __LINE__);

        /* Update SVL */
        c_svl_lock(h_svl_air);

        i4_ret = c_svl_update_rec(h_svl_air, &t_svl_rec_antenna, TRUE);

        c_svl_unlock(h_svl_air);

        if (i4_ret != SVLR_OK)
        {
            TUNER_LOG_E("Can't update record. i4_ret:%d\n",i4_ret);
            return -6;
        }

    }

    return SVLR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _tuner_setup_rm_duplicate_ch
 *
 * Description: The function will remove the cable SVL when antenna has the same frequence channel.
 *              rm == set the svl to FAKE.
 *
 * Inputs:
 *
 * Outputs:pt_svl_rec
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_rm_duplicate_ch(UINT16      ui2_rf_ch,
                                          HANDLE_T    h_svl_air,
                                          HANDLE_T    h_svl_cable)
{
    INT32       i4_ret            = 0;
    SVL_REC_T   t_svl_rec_antenna = {0};
    SVL_REC_T   t_svl_rec_cable   = {0};

    c_memset(&t_svl_rec_antenna, 0x0, sizeof(SVL_REC_T));
    c_memset(&t_svl_rec_cable, 0x0, sizeof(SVL_REC_T));

    TUNER_LOG_I("Enter _tuner_setup_rm_duplicate_ch ui2_rf_ch=%d\n", ui2_rf_ch);

    /* Try to get antenna SVL record */
    i4_ret = _tuner_setup_get_svl_rec_by_rf_index(h_svl_air,
                                                  ANTENNA_SVL_ID,
                                                  ui2_rf_ch,
                                                  &t_svl_rec_antenna);
    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("line=%d,_tuner_setup_get_svl_rec_by_rf_index(ANTENNA_SVL_ID), ui2_rf_ch=%d \r\n", __LINE__, ui2_rf_ch);
        return -1;
    }

    TUNER_LOG_I("ANTENNA ch_id=[%d], line=%d\n", t_svl_rec_antenna.uheader.t_rec_hdr.ui4_channel_id, __LINE__);

    /* Try to get cable SVL record */
    i4_ret = _tuner_setup_get_svl_rec_by_rf_index(h_svl_cable,
                                                  CABLE_SVL_ID,
                                                  ui2_rf_ch,
                                                  &t_svl_rec_cable);
    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("line=%d,_tuner_setup_get_svl_rec_by_rf_index(CABLE_SVL_ID), ui2_rf_ch=%d \r\n", __LINE__, ui2_rf_ch);
        return -2;
    }

    /* rm the cable channel that same frequence of air */
    /* rm == set the SVL to FAKE channel */
    t_svl_rec_cable.uheader.t_rec_hdr.ui4_nw_mask |= SB_VNET_FAKE;

    TUNER_LOG_I("set the SVL to FAKE channel, ch_id=[%d], line=%d\n", t_svl_rec_cable.uheader.t_rec_hdr.ui4_channel_id, __LINE__);

    /* Update SVL */
    c_svl_lock(h_svl_cable);

    i4_ret = c_svl_update_rec(h_svl_cable, &t_svl_rec_cable, TRUE);

    c_svl_unlock(h_svl_cable);

    if (i4_ret != SVLR_OK)
    {
        TUNER_LOG_E("Can't update record. i4_ret:%d\n",i4_ret);
        return -3;
    }

    return SVLR_OK;
}

static VOID _tuner_setup_ocl_reinstall(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    ocl_reinstall();
}
/*----------------------------------------------------------------------------
 * Name:_tuner_seetup_do_scan_nfy
 *
 * Description: The callback function of SVL Builder.
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static VOID _tuner_setup_do_scan_nfy(VOID* pv_data,
                         SIZE_T  z_data_size)
{
    INT32       i4_ret;
    GL_RECT_T   t_rect;
    AS_SCAN_NFY_T* pt_scan_nfy      = (AS_SCAN_NFY_T*)pv_data;
    AS_SCAN_INFO_T* pt_scan_info    = (AS_SCAN_INFO_T*)pt_scan_nfy->pv_nfy_tag;
    INT32       i4_progress;

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_PROGRESS)
    {
        if (b_scan)
        {
            BOOL    b_paint_info = (_GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data) > 0);
            pt_scan_info->i4_phy_ch_num += 1;
            pt_scan_info->i4_phy_ch_ttl  = _GET_PHY_CH_NUM(pt_scan_nfy->i4_nfy_data);

            TUNER_LOG_I("[Tuner scan]Scan %d/%d: total =[%d] vir channels found, current freq find [%d] channels.\r\n",
                      pt_scan_info->i4_phy_ch_num,
                      pt_scan_info->i4_phy_ch_ttl,
                      pt_scan_info->i4_vir_ch_num,
                      _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data));

            if (TRUE == b_scan_cable
                && _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data) > 0)
            {
                TUNER_LOG_I("<TUNER SETUP>Current scan cable. frequence=[%d], total=[%d]\n",
                           pt_scan_info->i4_phy_ch_num,
                           pt_scan_info->i4_phy_ch_ttl);

                i4_ret = -1;

                /* we shuold check antenna SVL fr index between 2 and 13 */
                if ((pt_scan_info->i4_phy_ch_num > 1) && (pt_scan_info->i4_phy_ch_num < 14))
                {
                     i4_ret = _tuner_setup_rm_duplicate_ch(pt_scan_info->i4_phy_ch_num,
                                                                 t_g_tuner_common.h_svl_air,
                                                                 t_g_tuner_common.h_svl_cable);
                }
                else if (pt_scan_info->i4_phy_ch_num > 13)
                {
                    /* we shuold check antenna and cable SVL freq */
                    //DBG_LOG_PRINT(("[Tunner scan] %s %d %d num:%d \n",__FILE__,__FUNCTION__,__LINE__,pt_scan_info->i4_phy_ch_num+1));
                    i4_ret = _tuner_setup_rm_farther_ch(pt_scan_info->i4_phy_ch_num,
                                                 t_g_tuner_common.h_svl_air,
                                                 t_g_tuner_common.h_svl_cable);
                }

                if (SVLR_OK == i4_ret)
                {
                    TUNER_LOG_I("<TUNER SETUP>Do not show update scan info when set channel to fake.\n");

                    /* do not show update scan info when set channel to fake */
                    return;
                }
            }

            pt_scan_info->i4_vir_ch_num += _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data);

            if(pt_scan_info->i4_phy_ch_num > pt_scan_info->i4_phy_ch_ttl)
            {
                 TUNER_LOG_I("<TUNER SETUP>ph_ch_num > ph_ch_ttl!:%d,%d\n",
                           pt_scan_info->i4_phy_ch_num,
                           pt_scan_info->i4_phy_ch_ttl);
                pt_scan_info->i4_phy_ch_num = pt_scan_info->i4_phy_ch_ttl;
            }

            i4_progress = _calc_progress();

            if(_tuner_setup_get_wzd_state()!= OOBE_SCAN)
            {
                if((i4_progress != 0)
                    && (i4_progress % 10 == 0)
                    && b_paint_info)
                {
                    _tuner_setup_url_put_update_channel(); //reload channel
                }
            }

            /* if progress no update & no channel scanned from current PTC, don't need to update UI. */
            if ((i4_g_scan_progress == i4_progress) && (b_paint_info == FALSE))
            {
                return;
            }

            i4_g_scan_progress = i4_progress;

            if(i4_progress!=100)
            {
                a_cfg_cust_set_ch_scan_progress((UINT8)i4_progress);
            }

            // notify REST AP to send event to customer's module
            rest_event_notify("tv_settings/channels/percent_complete", i4_progress, "");

            i4_ret=c_wgl_do_cmd(tg_scan_view.h_bar,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK((INT32) i4_progress),
                         NULL);
            if (i4_ret != TSP_OK)
            {
                TUNER_LOG_E("c_wgl_do_cmd fail i4_ret:%d\r\n",i4_ret);
            }

            SET_RECT_BY_SIZE(&t_rect,
                     960 - i4_progress * 9.6,
                     TUNER_PB_Y,
                     1920,
                     TUNER_PB_HEIGHT);
            i4_ret = c_wgl_move(tg_scan_view.h_bar,&t_rect,WGL_ASYNC_AUTO_REPAINT);
            if (i4_ret != TSP_OK)
            {
               TUNER_LOG_E("c_wgl_move fail i4_ret:%d\r\n",i4_ret);
            }

            i4_ret =  _percent_set_text(i4_progress);
            if (i4_ret != TSP_OK)
            {
                TUNER_LOG_E("_percent_set_text fail ,i4_ret:%d\r\n",i4_ret);
            }
            /* get gui lang */
            i4_ret = _tuner_setup_get_gui_lang();
            TUNER_LOG_I("_tuner_setup_view_lang_notify_cb_handler, update GUI language, i4_ret=[%d].\n", i4_ret);
            /* update title */
            i4_ret = _update_scan_ch_title();

            i4_ret = c_wgl_repaint(tg_scan_view.h_frm, NULL, TRUE);

            if (i4_ret != TSP_OK)
            {
                TUNER_LOG_E("c_wgl_repaint fail ,i4_ret:%d\r\n",i4_ret);
            }

            if (b_paint_info)
            {
                b_repaint = TRUE;
                _txt_info_animate_update(FALSE);

                //a_cfg_ch_lst_store();

                _update_ch_lst(((pt_scan_info == &t_scan_antenna_atv)||(pt_scan_info == &t_scan_cable_atv)) ? TRUE : FALSE ,
                                _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data));

                // notify REST AP to send event to customer's module
                rest_event_notify("tv_settings/channels/analog", t_scan_antenna_atv.i4_vir_ch_num + t_scan_cable_atv.i4_vir_ch_num, "");
                rest_event_notify("tv_settings/channels/digital", t_scan_antenna_dtv.i4_vir_ch_num + t_scan_cable_dtv.i4_vir_ch_num, "");
            }

            a_icl_custom_set_tuner_setup_status(ICL_RECID_TUNER_SETUP_STATUS_PROGRESS);

            TUNER_LOG_I("Scan %d/%d: %d channels found.\r\n",
                      pt_scan_info->i4_phy_ch_num, pt_scan_info->i4_phy_ch_ttl, pt_scan_info->i4_vir_ch_num);

        }
    }

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_CANCEL)
    {
        TUNER_LOG_I("SB_REASON_CANCEL\r\n");
        a_icl_custom_set_tuner_setup_status(ICL_RECID_TUNER_SETUP_STATUS_CANCEL);
        nav_set_channel_scan_active(FALSE);
        a_cfg_ch_lst_store();

        rest_event_notify("tv_settings/channels/channel_scan_state", 2, "");//scan cancel

        _tuner_setup_clear_scan_table_list();
        VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(TRUE);
        VIZIO_CTRL_ENABLE_SPI_HW_MODE(TRUE);
    }

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_ABORT)
    {
        if(b_scan)
        {
            a_icl_custom_set_tuner_setup_status(ICL_RECID_TUNER_SETUP_STATUS_ABORT);

            /* Abort is always triggered by svl-builder internal */
            _tuner_setup_enable_ch_chg(FALSE);

            _on_scan_stop();

            if(pt_scan_info == &t_scan_antenna_atv)
            {
                /* cancel the DTV one */
                c_sb_cancel_scan(t_scan_antenna_dtv.h_builder);
            }
            else if(pt_scan_info == &t_scan_antenna_dtv)
            {
                /* cancel the ATV one */
                c_sb_cancel_scan(t_scan_antenna_atv.h_builder);
            }

            #if FIND_CHANNEL_SCAN_CABLE_ENABLE
            if(pt_scan_info == &t_scan_cable_atv)
            {
                /* cancel the DTV one */
                c_sb_cancel_scan(t_scan_cable_dtv.h_builder);
            }
            else if(pt_scan_info == &t_scan_cable_dtv)
            {
                /* cancel the ATV one */
                c_sb_cancel_scan(t_scan_cable_atv.h_builder);
            }
            #endif

            i4_ret = c_wgl_repaint(tg_scan_view.h_frm, NULL, TRUE);
            if (i4_ret != TSP_OK)
            {
                TUNER_LOG_E("c_wgl_repaint fail i4_ret:%d\r\n");
            }
            _tuner_setup_clear_scan_table_list();
            VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(TRUE);
            VIZIO_CTRL_ENABLE_SPI_HW_MODE(TRUE);
        }
    }

    /* Check if the builder reach "AVAILABLE" condition */
    if(pt_scan_nfy->ui4_nfy_reason & SB_REASON_COMPLETE)
    {
        TUNER_LOG_I("SB_REASON_COMPLETE\r\n");

        pt_scan_info->i4_phy_ch_num = pt_scan_info->i4_phy_ch_ttl;
        pt_scan_info->b_done = TRUE;

        #if FIND_CHANNEL_SCAN_CABLE_ENABLE
        if(t_scan_antenna_atv.b_done && t_scan_antenna_dtv.b_done
            && !t_scan_cable_atv.b_done && !t_scan_cable_dtv.b_done)
        {
            /* set antenna scan completed first */
            a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_COMPLETED_SCAN);
            /* create the air tsl table. */
            _tuner_setup_create_air_tsl_table();
            //_tuner_setup_create_cable_tsl_table();

            TUNER_LOG_I("_tuner_setup_start_scan_cable\r\n");
            _tuner_setup_start_scan_cable();

        }
        #else
        if(t_scan_antenna_atv.b_done && t_scan_antenna_dtv.b_done)
        {

            TUNER_LOG_I("don't do _tuner_setup_start_scan_cable\r\n");
            /* set antenna scan completed first */
            a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_COMPLETED_SCAN);
            /* create the air tsl table. */
            _tuner_setup_create_air_tsl_table();
        }
        #endif

        #if 0
        if((t_scan_cable_atv.i4_vir_ch_num + t_scan_cable_dtv.i4_vir_ch_num)>=1)
        {
            a_cfg_set_tuner_type(APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_CABLE);
        }
        #endif
        /* make sure that both ATV/DTV scan complete */
        if(t_scan_antenna_atv.b_done && t_scan_antenna_dtv.b_done
        #if FIND_CHANNEL_SCAN_CABLE_ENABLE
            && t_scan_cable_atv.b_done && t_scan_cable_dtv.b_done
        #endif
        )
        {
            if(b_scan && !b_menu_scan_channel)
            {
                _on_scan_stop();

                i4_ret=c_wgl_do_cmd(tg_scan_view.h_bar,
                             WGL_CMD_PG_SET_POS,
                             WGL_PACK((INT32) 100),
                             NULL);
                if (i4_ret != TSP_OK)
                {
                    TUNER_LOG_E("c_wgl_do_cmd fail i4_ret:%d\r\n",i4_ret);
                }

                c_wgl_repaint(tg_scan_view.h_frm, NULL, TRUE);
            }
            else
            {
                b_scan = FALSE;
                b_scan_cable = FALSE;
                nav_set_channel_scan_active(FALSE);
                /* channel scan status */
                if (b_is_cancel)
                {
                    TUNER_LOG_I("[tuner set scan_status] set ACFG_CUST_PARTIAL_SCAN\n");
                    a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_PARTIAL_SCAN);
                    b_is_cancel = FALSE;
                }
                else
                {
                    TUNER_LOG_I("[tuner set scan_status] set ACFG_CUST_COMPLETED_SCAN\n");
                    a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_COMPLETED_SCAN);
                }
            }

            a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
            /* Re-open SVL */
            if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID &&
                t_g_tuner_common.h_svl_air == NULL_HANDLE)
            {
                i4_ret = c_svl_open(ATSC_TRSTRL_SVL_ID,
                                    NULL,
                                    NULL,
                                    &t_g_tuner_common.h_svl_air);
                if (i4_ret != SVLR_OK)
                {
                    TUNER_LOG_E("Can't open SVL,%d\r\n",i4_ret);
                    t_g_tuner_common.h_svl_air = NULL_HANDLE;
                }
            }
            else if (ui2_crnt_svl_id == ATSC_CABLE_SVL_ID &&
                     t_g_tuner_common.h_svl_cable == NULL_HANDLE)
            {
                i4_ret = c_svl_open(ATSC_CABLE_SVL_ID,
                                    NULL,
                                    NULL,
                                    &t_g_tuner_common.h_svl_cable);
                if (i4_ret != SVLR_OK)
                {
                    TUNER_LOG_E("Can't open SVL,%d\r\n",i4_ret);
                    t_g_tuner_common.h_svl_cable = NULL_HANDLE;
                }
            }

            if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_COMPLETE)
            {
                _tuner_setup_url_put_update_channel();//reload channel

                if(!b_menu_scan_channel)
                    c_wgl_show(tg_scan_view.h_frm, WGL_SW_HIDE);

                if(_tuner_setup_get_wzd_state()!= OOBE_SCAN &&
                    !b_menu_scan_channel)
                {

                    TUNER_LOG_I("do_scan_nfy");
                    nav_request_context_switch(_do_show_warning_nfy,NULL, NULL,NULL);
                }

                a_icl_custom_set_tuner_setup_status(ICL_RECID_TUNER_SETUP_STATUS_COMPLETE);
                if(b_menu_scan_channel)
                {
                    _tuner_setup_enable_ch_chg(FALSE);
                    _tuner_setup_select_crnt_or_first_channel(TRUE);
                }

                if(_tuner_setup_get_wzd_state()== OOBE_SCAN)
                {
                    _tuner_setup_set_cfg_first_channel_id();
                }

                _tuner_setup_clear_scan_table_list();
                a_cfg_ch_lst_store();
                VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(TRUE);
                VIZIO_CTRL_ENABLE_SPI_HW_MODE(TRUE);

            }
            rest_event_notify("tv_settings/channels/channel_scan_state", 1, "");  //scan complete

            DBG_LOG_PRINT(("[OCL] ocl enter! finish scan0\n"));
            /*nav_request_context_switch(
                        _tuner_setup_ocl_reinstall,
                        NULL,
                        NULL,
                        NULL);*/
            nav_request_context_switch_in_sync(_tuner_setup_ocl_reinstall,
                                                    NULL,
                                                    NULL,
                                                    NULL,
                                                    5000);
            i4_progress =100;
            a_cfg_cust_set_ch_scan_progress((UINT8)i4_progress);
        }


    }

}

static VOID _tuner_setup_do_scan_by_rest_after_menu(VOID* pv_data,
                         SIZE_T  z_data_size)
{
    INT32       i4_ret              = TSP_OK;


    /* step 1: cancel scan */
    a_amb_pause_app("menu");
    a_amb_resume_app(NAV_NAME);

    nav_grab_activation(NAV_COMP_ID_TUNER_SETUP);
    i4_ret = tuner_setup_rest_view_show();
    if (i4_ret != TSP_OK)
    {
        TUNER_LOG_E("tuner_setup_rest_view_show,i4_ret=[%d] \r\n",i4_ret);
    }

}
BOOL tuner_setup_during_scan(VOID)
{
    return b_scan;
}
/*----------------------------------------------------------------------------
 * Name:_tuner_setup_do_cancel_scan_nfy
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
static VOID _tuner_setup_do_cancel_scan_nfy(VOID* pv_data,
                         SIZE_T  z_data_size)
{
    INT32   i4_ret = 0;

    i4_ret = _cancel_scan(TRUE);
    if (i4_ret != TSP_OK)
    {
        TUNER_LOG_E("_cancel_scan fail i4_ret:%d\r\n",i4_ret);
    }
    if(b_need_rest_scan_after_menu_scan)
    {
        _tuner_setup_do_scan_by_rest_after_menu(NULL,0);
    }
}

/*----------------------------------------------------------------------------
 * Name: _sb_nfy_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *----------------------------------------------------------------------------*/
static VOID _sb_nfy_fct (HANDLE_T          h_builder,
                         SB_COND_T         e_builder_cond,
                         VOID*             pv_nfy_tag)
{
}

/*----------------------------------------------------------------------------
 * Name: _tuner_setup_scan_nfy_fct
 *
 * Description: The callback function of SVL Builder.
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _tuner_setup_scan_nfy_fct(HANDLE_T          h_builder,
                          UINT32            ui4_nfy_reason,
                          INT32             i4_nfy_data,
                          VOID*             pv_nfy_tag)
{
    AS_SCAN_NFY_T   t_scan_nfy;

    t_scan_nfy.h_builder        = h_builder;
    t_scan_nfy.ui4_nfy_reason   = ui4_nfy_reason;
    t_scan_nfy.i4_nfy_data      = i4_nfy_data;
    t_scan_nfy.pv_nfy_tag       = pv_nfy_tag;

    a_agent_async_invoke(_tuner_setup_do_scan_nfy,&t_scan_nfy,sizeof(AS_SCAN_NFY_T));
    //menu_async_invoke(_tuner_setup_do_scan_nfy,&t_scan_nfy,sizeof(AS_SCAN_NFY_T),TRUE);
}

/*---------------------------------------------------------------------------
 * Name
 *      _tuner_setup_string_toast_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32  _tuner_setup_string_toast_nfy_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2
                    )
{
    INT32     i4_ret;
    UINT32    ui4_keycode = (UINT32)pv_param1;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            switch (ui4_keycode)
            {
                case BTN_P_EFFECT:
                {
                    TUNER_LOG_I("BTN_P_EFFECT\n\r");

                    nav_grab_activation(NAV_COMP_ID_TUNER_SETUP);
                    _tuner_setup_view_show_scan(NULL,NULL,NULL);
                }
                    break;

                default:
                    break;
                }
        }
        default:
            break;
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}


/*---------------------------------------------------------------------------
 * Name
 *      _tuner_setup_main_frame_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32  _tuner_setup_main_frame_nfy_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2
                    )
{

    INT32     i4_ret;
    UINT32    ui4_keycode = (UINT32)pv_param1;
    UTF16_T   w2s_tmp_str[128] = {0};
    UINT32    ui4_crnt_channel_id = INVALID_CHANNEL_ID;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            if (b_scan)
            {
                switch (ui4_keycode)
                {
                #if 0
                case BTN_INPUT_SRC:
                    {
                        TUNER_LOG_E("BTN_INPUT_SRC\n\r");
                        i4_ret = tuner_setup_view_hide();
                        RET_ON_ERR(i4_ret);

                        nav_set_channel_scan_active(FALSE);

                        nav_hide_component(NAV_COMP_ID_TUNER_SETUP);

                        nav_return_activation(NAV_COMP_ID_TUNER_SETUP);
                        nav_rcu_key_handler(ui4_keycode);
                    }
                   break;
                   #endif
                case BTN_PAUSE:
                case BTN_PLAY:
                    break;

                 default:
                    break;
                }
            }
            else
            {
                switch (ui4_keycode)
                {
                case BTN_SELECT:
                //case BTN_PAUSE:
                //case BTN_PLAY:
                    {
                        a_cfg_get_crnt_channel_id(&ui4_crnt_channel_id);
                        if (ui4_crnt_channel_id != INVALID_CHANNEL_ID)
                        {
                            c_uc_w2s_strcpy(w2s_tmp_str,TUNER_WARNINGS_TEXT(MLM_WARNINGS_KEY_WARNING_42));
                            _tuner_setup_string_toast_view(tg_scan_view.h_canvas,w2s_tmp_str);
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        }
        default:
            break;
    }
    if(ui4_msg == WGL_MSG_KEY_DOWN)
    {
        i4_ret = c_wgl_default_msg_proc(
                        h_widget,
                        ui4_msg,
                        pv_param1,
                        pv_param2
                        );
        RET_ON_ERR(i4_ret);
    }
    return TSP_OK;
}


/*----------------------------------------------------------------------------
 * Name: _tuner_setup_warning_toast_view
 * Description:
 *  show warning toast
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_warning_toast_view(HANDLE_T h_canvas,UTF16_T* w2s_txt)
{
    INT32   i4_ret;

    nav_grab_activation(NAV_COMP_ID_TUNER_SETUP);
    /*
    c_memset(&tg_toast_param,0,sizeof(WDK_TOAST_PARAM_T));
    tg_toast_param.e_toast_style = WDK_WARNING_TOAST;
    tg_toast_param.w2s_str       = (VOID*)w2s_txt;
    tg_toast_param.pf_cb         = NULL;

    i4_ret = a_wdk_toast_init(h_canvas,&tg_toast_param,&t_g_wdk_view);
    RET_ON_ERR(i4_ret);

    i4_ret = a_wdk_toast_activate(FALSE,&tg_toast_param,&t_g_wdk_view);
    RET_ON_ERR(i4_ret);
    */
    DBG_LOG_PRINT(("[tuner warning] %s %d start\n",__FUNCTION__,__LINE__));
    tuner_setup_warning_show(w2s_txt);
    DBG_LOG_PRINT(("[tuner warning] %s %d end\n",__FUNCTION__,__LINE__));

#ifdef  APP_TTS_SUPPORT
    a_app_tts_play(w2s_txt, 128);
#endif

    i4_toast_flag = 0;
    /* enable the show timer */
    i4_ret = c_timer_start(h_timer_show,
                            2000,
                            X_TIMER_FLAG_ONCE,
                            _timer_show_toast_view_fct,
                            (VOID*)&i4_toast_flag);
    if(i4_ret < 0)
    {
        TUNER_LOG_E("Can't start show timer,i4_ret=%d\r\n",i4_ret);
    }

    return TSP_OK;
}


/*----------------------------------------------------------------------------
 * Name: _tuner_setup_string_toast_view
 * Description:
 *  show warning toast
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_string_toast_view(HANDLE_T h_canvas,UTF16_T* w2s_txt)
{
    INT32   i4_ret;

    nav_grab_activation(NAV_COMP_ID_TUNER_SETUP);

    c_memset(&tg_toast_param,0,sizeof(WDK_TOAST_PARAM_T));
    tg_toast_param.e_toast_style = WDK_STRING_TOAST;
    tg_toast_param.w2s_str       = (VOID*)w2s_txt;
    tg_toast_param.pf_cb         = _tuner_setup_string_toast_nfy_fct;

    i4_ret = a_wdk_toast_init(h_canvas,&tg_toast_param,&t_g_wdk_view);
    RET_ON_ERR(i4_ret);

    tg_toast_param.h_t_focus_handle = t_g_wdk_view.h_base_frm;

    i4_ret = a_wdk_toast_activate(FALSE,&tg_toast_param,&t_g_wdk_view);
    RET_ON_ERR(i4_ret);

    i4_toast_flag = 1;
    /* enable the show timer */
    i4_ret = c_timer_start(h_timer_show,
                            2000,
                            X_TIMER_FLAG_ONCE,
                            _timer_show_toast_view_fct,
                            (VOID*)&i4_toast_flag);
    if(i4_ret < 0)
    {
        TUNER_LOG_E("Can't start show timer,i4_ret=%d\r\n",i4_ret);
    }

    return TSP_OK;
}


/*----------------------------------------------------------------------------
 * Name: _tuner_setup_cd_text_init
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_cd_text_init(VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    UTF16_T                     w2s_tmp_str[128] = {0};

    SET_RECT_BY_SIZE(&t_rect,
                     TUNER_CD_X,
                     TUNER_CD_Y,
                     TUNER_CD_WIDTH,
                     TUNER_CD_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_scan_view.h_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_128),
                                 &tg_scan_view,
                                 &(tg_scan_view.h_cd_text));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_scan_view.h_cd_text,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_CENTER_CENTER),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = 28;

    i4_ret = c_wgl_do_cmd (tg_scan_view.h_cd_text,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Color
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_tuner_setup_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_tuner_setup_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_tuner_setup_color_white;
    i4_ret = c_wgl_do_cmd(tg_scan_view.h_cd_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strcpy(w2s_tmp_str,TUNER_TEXT(MLM_SETTINGS_KEY_CHANNELS_FOUND));

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_cd_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_tmp_str),
                          WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_cd_text, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return TSP_OK;

}


/*----------------------------------------------------------------------------
 * Name: _tuner_setup_da_text_init
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_da_text_init(VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    UTF16_T                     w2s_tmp_str[128] = {0};
    UTF16_T                     w2s_str[128] = {0};
    char*                       w2s_num_str;
    char*                       s_str;

    SET_RECT_BY_SIZE(&t_rect,
                     TUNER_DA_X,
                     TUNER_DA_Y,
                     TUNER_DA_WIDTH,
                     TUNER_DA_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_scan_view.h_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_128),
                                 &tg_scan_view,
                                 &(tg_scan_view.h_da_text));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_scan_view.h_da_text,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_CENTER_CENTER),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = 32;

    i4_ret = c_wgl_do_cmd (tg_scan_view.h_da_text,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Color
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_tuner_setup_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_tuner_setup_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_tuner_setup_color_white;
    i4_ret = c_wgl_do_cmd(tg_scan_view.h_da_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strcpy(w2s_tmp_str,TUNER_TEXT(MLM_SETTINGS_KEY_CHANNEL_DIGITAL));

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    w2s_num_str = " 0 ";
    c_uc_ps_to_w2s(w2s_num_str,w2s_tmp_str,c_strlen(w2s_num_str));
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    s_str = " and ";
    c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_uc_w2s_strcpy(w2s_tmp_str,TUNER_TEXT(MLM_SETTINGS_KEY_CHANNEL_ANALOG));

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    w2s_num_str = " 0 ";
    c_uc_ps_to_w2s(w2s_num_str,w2s_tmp_str,c_strlen(w2s_num_str));
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_da_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_str)));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_da_text, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: _tuner_setup_per_text_init
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _tuner_setup_per_text_init(VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    UTF16_T                     w2s_tmp_str[128] = {0};
    UTF16_T                     w2s_str[128] = {0};
    char*                       s_str;

    SET_RECT_BY_SIZE(&t_rect,
                     TUNER_PER_X,
                     TUNER_PER_Y,
                     TUNER_PER_WIDTH,
                     TUNER_PER_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_scan_view.h_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_128),
                                 &tg_scan_view,
                                 &(tg_scan_view.h_per_text));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_scan_view.h_per_text,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_CENTER_CENTER),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = 21;

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_per_text,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Color
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_tuner_setup_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_tuner_setup_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_tuner_setup_color_white;
    i4_ret = c_wgl_do_cmd(tg_scan_view.h_per_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    s_str = "0";
    c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_uc_w2s_strcpy(w2s_tmp_str,TUNER_TEXT(MLM_SETTINGS_KEY_CHANNEL_PERCENT_COMPLETE));
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_per_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_str)));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_per_text, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return TSP_OK;

}

/*--------------------------------------------------------------------------
 * Name
 *     _tuner_setup_scan_pb_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _tuner_setup_scan_pb_init(VOID)
{
    INT32                 i4_ret;
    GL_RECT_T             t_rect;
    WGL_PG_LEVELS_INFO_T  t_pg_levels;
    WGL_COLOR_INFO_T      t_clr_info;
    WGL_IMG_INFO_T        t_img_info;
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     TUNER_ICON_X,
                     TUNER_PB_Y+1,
                     TUNER_ICON_WIDTH,
                     TUNER_PB_HEIGHT-2);

    i4_ret = c_wgl_create_widget(tg_scan_view.h_frm,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)(WGL_STL_GL_NO_IMG_UI),
                                NULL,
                                &tg_scan_view.h_icon);

    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_tuner_setup_color_white_line;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_tuner_setup_color_white_line;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_tuner_setup_color_white_line;

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_icon,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_insert(tg_scan_view.h_icon,
                          NULL_HANDLE,
                          WGL_INSERT_TOPMOST,
                          WGL_NO_AUTO_REPAINT);
    RET_ON_ERR(i4_ret);
     /*Create Bar*/
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     TUNER_PB_X,
                     TUNER_PB_Y,
                     TUNER_PB_WIDTH,
                     TUNER_PB_HEIGHT);
    i4_ret = c_wgl_create_widget(tg_scan_view.h_frm,
                                 HT_WGL_WIDGET_PROGRESS_BAR,
                                 WGL_CONTENT_PROGRESS_BAR_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(NULL),
                                 NULL,
                                 &(tg_scan_view.h_bar));
    RET_ON_ERR(i4_ret);

    /* Set Range */
    i4_ret = c_wgl_do_cmd (tg_scan_view.h_bar,
                           WGL_CMD_PG_SET_RANGE,
                           WGL_PACK((INT32)0),
                           WGL_PACK((INT32)100));
    RET_ON_ERR(i4_ret);

    i4_ret=c_wgl_do_cmd(tg_scan_view.h_bar,
                        WGL_CMD_PG_SET_POS,
                        WGL_PACK((INT32) 0),
                        NULL);
    RET_ON_ERR(i4_ret);

    /* Set Levels */
    t_pg_levels.a_boundary[0] = 100;
    t_pg_levels.ui1_level_number = 1;
    i4_ret = c_wgl_do_cmd (tg_scan_view.h_bar,
                           WGL_CMD_PG_SET_LEVELS,
                           WGL_PACK(&t_pg_levels),
                           NULL);
    RET_ON_ERR(i4_ret);

    /* Set Display Modes */
    i4_ret = c_wgl_do_cmd (tg_scan_view.h_bar,
                           WGL_CMD_PG_SET_DISPLAY_MODE,
                           WGL_PACK(WGL_PG_DM_HIDE_IDR),
                           NULL);
    RET_ON_ERR(i4_ret);

    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_tuner_setup_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_tuner_setup_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_tuner_setup_color_white;
    i4_ret = c_wgl_do_cmd(tg_scan_view.h_bar,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_bar,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_BK),
                              WGL_PACK(&t_clr_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_bar,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_PG_BODY),
                              WGL_PACK(&t_clr_info));
    RET_ON_ERR(i4_ret);
#if 0
    i4_ret = nav_img_create_tuner_track_mute_fill(&(tg_scan_view.h_pb_img_tpl));
    RET_ON_ERR(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = tg_scan_view.h_pb_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight    = tg_scan_view.h_pb_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable      = tg_scan_view.h_pb_img_tpl;
    i4_ret = c_wgl_do_cmd(tg_scan_view.h_bar,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_BODY),
                          WGL_PACK(&t_img_info ));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_bar,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);
#endif
    i4_ret = nav_img_create_tuner_track_mute_fill(&(tg_scan_view.h_pb_level_img_tpl));
    RET_ON_ERR(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = tg_scan_view.h_pb_level_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight    = tg_scan_view.h_pb_level_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable      = tg_scan_view.h_pb_level_img_tpl;
    i4_ret = c_wgl_do_cmd(tg_scan_view.h_bar,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_LEVEL_1),
                          WGL_PACK(&t_img_info ));
    RET_ON_ERR(i4_ret);
    i4_ret = c_wgl_insert(tg_scan_view.h_bar,
                          tg_scan_view.h_icon,
                          WGL_INSERT_BEFORE,
                          WGL_NO_AUTO_REPAINT);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_icon, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_bar, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}

/*--------------------------------------------------------------------------
 * Name
 *     _tuner_setup_main_frm_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _tuner_setup_main_frm_init(VOID)
{
    INT32             i4_ret;
    GL_RECT_T         t_rect;
    //WGL_IMG_INFO_T    t_img_info;
    WGL_COLOR_INFO_T  t_clr_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

    /*create bg*/
    SET_RECT_BY_SIZE(&t_rect,
                     TUNER_FRAME_X,
                     TUNER_FRAME_Y,
                     TUNER_FRAME_WIDTH,
                     TUNER_FRAME_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_scan_view.h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _tuner_setup_main_frame_nfy_fct,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI),
                                 &(tg_scan_view),
                                 &(tg_scan_view.h_frm));
    RET_ON_ERR(i4_ret);

    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_tuner_setup_color_black;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_tuner_setup_color_black;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_tuner_setup_color_black;

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_frm,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);
    #if 0
    //get background img
    i4_ret = nav_img_create_tuner_setup_bg(&(tg_scan_view.h_bg_img_tpl));
    //i4_ret = nav_img_create_tuner_bk(&(tg_scan_view.h_bg_img_tpl));
    RET_ON_ERR(i4_ret);

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = tg_scan_view.h_bg_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = tg_scan_view.h_bg_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = tg_scan_view.h_bg_img_tpl;
    i4_ret = c_wgl_do_cmd(tg_scan_view.h_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);
    #endif

    i4_ret = c_wgl_insert(tg_scan_view.h_frm,
                              NULL_HANDLE,
                              WGL_INSERT_BOTTOMMOST,
                              WGL_NO_AUTO_REPAINT);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_frm, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}


static VOID _tuner_setup_url_put_response(VOID* pv_data1,
                                              VOID* pv_data2,
                                              VOID* pv_data3)
{
    a_tuner_setup_url_put_channels_changed();
}

/*--------------------------------------------------------------------------
 * Name
 *      _tuner_setup_url_put_update_channel
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/

static VOID _tuner_setup_url_put_update_channel(VOID)
{
    if(b_scan)  //For scan status will be clear after rge url update,so do not need update after the scan status clear
    {
        nav_request_context_switch(_tuner_setup_url_put_response,NULL, NULL,NULL);
    }
}

/*--------------------------------------------------------------------------
 * Name
 *      _tuner_setup_open_svl_builder
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _tuner_setup_open_svl_builder(VOID)
{
    INT32               i4_ret;
    SB_COND_T           e_atsc_cond;
    SB_COND_T           e_ntsc_cond;
    SB_COND_T           e_cqam_cond;
    SB_COND_T           e_antsc_cond;
    SB_ATSC_OPEN_DATA_T t_sb_atsc_open_data;
    SB_NTSC_OPEN_DATA_T t_sb_ntsc_open_data;
    SB_CQAM_OPEN_DATA_T t_sb_cqam_open_data;
    SB_NTSC_OPEN_DATA_T t_sb_antsc_open_data;

    #define NTSC_TRSTRL_SVL_ID              ATSC_TRSTRL_SVL_ID
    #define NTSC_TRSTRL_SVL_NAME            ATSC_TRSTRL_SVL_NAME
    #define NTSC_TRSTRL_SVL_FILE            ATSC_TRSTRL_SVL_FILE
    #define NTSC_TRSTRL_TUNER_NAME          SN_TUNER_GRP_0

    #define NTSC_CABLE_SVL_ID               ATSC_CABLE_SVL_ID
    #define NTSC_CABLE_SVL_NAME             ATSC_CABLE_SVL_NAME
    #define NTSC_CABLE_SVL_FILE             ATSC_CABLE_SVL_FILE
    #define NTSC_CABLE_TUNER_NAME           SN_TUNER_GRP_0

    c_memset(&t_sb_atsc_open_data, 0, sizeof(SB_ATSC_OPEN_DATA_T));
    t_sb_atsc_open_data.ui2_svl_id    = ATSC_TRSTRL_SVL_ID;
    t_sb_atsc_open_data.ps_svl_name   = ATSC_TRSTRL_SVL_NAME;
    t_sb_atsc_open_data.ps_file_name  = ATSC_TRSTRL_SVL_FILE;
    t_sb_atsc_open_data.ps_tuner_name = ATSC_TRSTRL_TUNER_NAME;
    t_sb_atsc_open_data.b_use_orig    =TRUE;
    i4_ret = c_sb_open_builder(SB_TRSTRL_ENG_NAME,
                               &t_sb_atsc_open_data,
                               NULL,
                               _sb_nfy_fct,
                               &t_g_tuner_atsc.h_sb_dig_air ,
                               &e_atsc_cond);
    RET_ON_ERR(i4_ret);

    c_memset(&t_sb_ntsc_open_data, 0, sizeof(SB_NTSC_OPEN_DATA_T));
    t_sb_ntsc_open_data.ui2_svl_id    = NTSC_TRSTRL_SVL_ID;
    t_sb_ntsc_open_data.ps_svl_name   = NTSC_TRSTRL_SVL_NAME;
    t_sb_ntsc_open_data.ps_file_name  = NTSC_TRSTRL_SVL_FILE;
    t_sb_ntsc_open_data.ps_tuner_name = NTSC_TRSTRL_TUNER_NAME;
    t_sb_ntsc_open_data.b_use_orig =TRUE;
    i4_ret = c_sb_open_builder(SB_NTSC_TER_ENG_NAME,
                               &t_sb_ntsc_open_data,
                               NULL,
                               _sb_nfy_fct,
                               &t_g_tuner_atsc.h_sb_anlg_air,
                               &e_ntsc_cond);
    RET_ON_ERR(i4_ret);

    c_memset(&t_sb_cqam_open_data, 0, sizeof(SB_CQAM_OPEN_DATA_T));

    t_sb_cqam_open_data.ui2_svl_id    = ATSC_CABLE_SVL_ID;
    t_sb_cqam_open_data.ps_svl_name   = ATSC_CABLE_SVL_NAME;
    t_sb_cqam_open_data.ps_file_name  = ATSC_CABLE_SVL_FILE;
    t_sb_cqam_open_data.ps_tuner_name = ATSC_CABLE_TUNER_NAME;
    t_sb_cqam_open_data.b_use_orig =TRUE;
    i4_ret = c_sb_open_builder(SB_CABLE_ENG_NAME,
                               &t_sb_cqam_open_data,
                               NULL,
                               _sb_nfy_fct,
                               &t_g_tuner_atsc.h_sb_dig_cable,
                               &e_cqam_cond);
    RET_ON_ERR(i4_ret);


    c_memset(&t_sb_antsc_open_data, 0, sizeof(SB_NTSC_OPEN_DATA_T));
    t_sb_antsc_open_data.ui2_svl_id    = NTSC_CABLE_SVL_ID;
    t_sb_antsc_open_data.ps_svl_name   = NTSC_CABLE_SVL_NAME;
    t_sb_antsc_open_data.ps_file_name  = NTSC_CABLE_SVL_FILE;
    t_sb_antsc_open_data.ps_tuner_name = NTSC_CABLE_TUNER_NAME;
    t_sb_antsc_open_data.b_use_orig =TRUE;
    i4_ret = c_sb_open_builder(SB_NTSC_CAB_ENG_NAME,
                               &t_sb_antsc_open_data,
                               NULL,
                               _sb_nfy_fct,
                               &t_g_tuner_atsc.h_sb_anlg_cable,
                               &e_antsc_cond);
    RET_ON_ERR(i4_ret);

    /* Open SVL */
    i4_ret = c_svl_open(ATSC_TRSTRL_SVL_ID, /* defined in a_common.h*/
                        NULL,
                        NULL,//_tuner_setup_trstrl_svl_update_nfy_callback,
                        &t_g_tuner_common.h_svl_air);
    if (i4_ret != SVLR_OK)
    {
        TUNER_LOG_E("Can't open AIR SVL,%d\r\n",i4_ret);
        t_g_tuner_common.h_svl_air = NULL_HANDLE;
    }

    i4_ret = c_svl_open(ATSC_CABLE_SVL_ID, /* defined in a_common.h*/
                        NULL,
                        NULL,//_tuner_setup_cable_svl_update_nfy_callback,
                        &t_g_tuner_common.h_svl_cable);
    if (i4_ret != SVLR_OK)
    {
        TUNER_LOG_E("<TUNER SETUP>Can't open CABLE SVL,%d\r\n",i4_ret);
        t_g_tuner_common.h_svl_cable = NULL_HANDLE;
    }

    /* Open TSL */
    i4_ret = c_tsl_open(ATSC_TRSTRL_TSL_ID, /* defined in a_common.h*/
                        NULL,
                        NULL,
                        &t_g_tuner_common.h_tsl_air);
    if (i4_ret != TSLR_OK)
    {
        TUNER_LOG_E("<TUNER SETUP>Can't open AIR TSL,%d\r\n",i4_ret);
        t_g_tuner_common.h_tsl_air = NULL_HANDLE;
    }

    i4_ret = c_tsl_open(ATSC_CABLE_TSL_ID, /* defined in a_common.h*/
                        NULL,
                        NULL,
                        &t_g_tuner_common.h_tsl_cable);
    if (i4_ret != TSLR_OK)
    {
        TUNER_LOG_E("<TUNER SETUP>Can't open CABLE TSL,%d\r\n",i4_ret);
        t_g_tuner_common.h_tsl_cable = NULL_HANDLE;
    }

    return TSP_OK;
}

/*--------------------------------------------------------------------------
 * Name
 *      _tuner_setup_close_svl_builder
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _tuner_setup_close_svl_builder(VOID)
{
    INT32               i4_ret;

    i4_ret = c_sb_close_builder(t_g_tuner_atsc.h_sb_dig_air);
    RET_ON_ERR(i4_ret);

    i4_ret = c_sb_close_builder(t_g_tuner_atsc.h_sb_anlg_air);
    RET_ON_ERR(i4_ret);

    i4_ret = c_sb_close_builder(t_g_tuner_atsc.h_sb_dig_cable);
    RET_ON_ERR(i4_ret);

    i4_ret = c_sb_close_builder(t_g_tuner_atsc.h_sb_anlg_cable);
    RET_ON_ERR(i4_ret);

    i4_ret = c_tsl_close(t_g_tuner_common.h_svl_air);
    RET_ON_ERR(i4_ret);

    i4_ret = c_tsl_close(t_g_tuner_common.h_svl_cable);
    RET_ON_ERR(i4_ret);

    i4_ret = c_tsl_close(t_g_tuner_common.h_tsl_air);
    RET_ON_ERR(i4_ret);

    i4_ret = c_tsl_close(t_g_tuner_common.h_tsl_cable);
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}



/*--------------------------------------------------------------------------
 * Name
 *      _tuner_setup_view_init_widgets
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _tuner_setup_view_init_widgets(VOID)
{
    INT32               i4_ret;

    /* get gui lang */
    i4_ret = _tuner_setup_get_gui_lang();
    RET_ON_ERR(i4_ret);

    /* init mian frame widgets */
    i4_ret = _tuner_setup_main_frm_init();
    RET_ON_ERR(i4_ret);

    /* init pb widgets */
    i4_ret = _tuner_setup_scan_pb_init();
    RET_ON_ERR(i4_ret);

     /*init channels detected */
    i4_ret = _tuner_setup_cd_text_init();
    RET_ON_ERR(i4_ret);

     /*init digital and analog */
    i4_ret = _tuner_setup_da_text_init();
    RET_ON_ERR(i4_ret);

    /*init percent */
    i4_ret = _tuner_setup_per_text_init();
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}

static VOID _drrt_change_proc(VOID* pv_data1,
                              VOID* pv_data2,
                              VOID* pv_data3)
{
    HANDLE_T     h_handle = NULL_HANDLE;
    INT32        i4_ret = 0;
    HTTPC_DATA_T t_data;
    char         ut_url[256] = "http://127.0.0.1:7346/state/tuner/drrt_changed";
    char s_c_session_token[24] = {0};
    char session_header[64] = {0};

    DBG_LOG_PRINT(("%s,%d\n", __FUNCTION__, __LINE__));

    c_httpc_data_init(&t_data);
    i4_ret = c_httpc_new_session(&h_handle);
    if (i4_ret == HTTPR_OK)
    {
        TUNER_LOG_I("new session PASS\n");
    }
    else
    {
        TUNER_LOG_E("new session FAIL,i4_ret:%d\n",i4_ret);
    }

    c_httpc_append_header(h_handle, "Expect: ");
    c_httpc_append_header(h_handle, "content-type: application/json");

    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
        if(h_handle != NULL_HANDLE)
            c_httpc_free_session(h_handle);
        return;
    }
    sprintf(session_header, "SESSION: %s", s_c_session_token);
    session_header[63] = '\0';
    c_httpc_append_header(h_handle, session_header);


    i4_ret = c_httpc_put(h_handle, ut_url, NULL, 0, &t_data);

    if (i4_ret != HTTPR_OK)
    {
        TUNER_LOG_E("c_httpc_put FAIL.%i4_ret:%d.!!!\n",i4_ret);
    }

    c_httpc_free_session(h_handle);
    c_httpc_data_free(&t_data);

}

static VOID _tuner_setup_scan_in_menu(VOID* pv_data1,
                              VOID* pv_data2,
                              VOID* pv_data3)
{
    INT32 i4_ret=TSP_OK;
    b_clean_lists = TRUE;
    nav_set_channel_scan_active(TRUE);
    if(!a_nav_tuner_setup_get_scan_new_channel())
    {
        i4_ret=_tuner_setup_start_scan_antenna();
    }
    else
    {
        i4_ret=_tuner_setup_start_scan_new_antenna();
    }
    if(i4_ret != TSP_OK)
    {
        nav_set_channel_scan_active(FALSE);
    }
}

static VOID _tuner_setup_cancel_scan_in_menu(VOID* pv_data,
                         SIZE_T  z_data_size)
{
    a_tuner_setup_stop_scan(NULL, 0);
    nav_set_channel_scan_active(FALSE);
}

/*-----------------------------------------------------------------------------
 * Name
 *       tuner_setup_view_init
 * Description:
 *
 * Input arguments:
 *      pt_ctrl         pointer to struct REVOLT_MISC_SYSTEM_INFO_VIEW_T
 *      h_canvas        canvas handle
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
INT32 tuner_setup_view_init( HANDLE_T  h_canvas)
{
    INT32 i4_ret;

    tg_scan_view.h_canvas = h_canvas;

    i4_ret = _tuner_setup_view_init_widgets();
    RET_ON_ERR(i4_ret);

    _tuner_setup_warning_widget_init();

    i4_ret = c_timer_create(&h_timer_ani);
    RET_ON_ERR(i4_ret);

    i4_ret = c_timer_create(&h_timer_show);
    RET_ON_ERR(i4_ret);

    i4_ret = c_timer_create(&h_timer_show_no_signal);
    RET_ON_ERR(i4_ret);
    httpc_client_init();

    /* open svl builder */
    i4_ret = _tuner_setup_open_svl_builder();
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *     tuner_setup_view_deinit
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 tuner_setup_view_deinit (VOID)
{

    INT32 i4_ret;

    if (h_timer_ani)
    {
        i4_ret = c_timer_delete(h_timer_ani);
        RET_ON_ERR(i4_ret);
        h_timer_ani = NULL_HANDLE;
    }
    if (h_timer_show)
    {
        i4_ret = c_timer_delete(h_timer_show);
        RET_ON_ERR(i4_ret);
        h_timer_show = NULL_HANDLE;
    }

    if (h_timer_show_no_signal)
    {
        i4_ret = c_timer_delete(h_timer_show_no_signal);
        RET_ON_ERR(i4_ret);
        h_timer_show_no_signal = NULL_HANDLE;
    }

    /* close svl builder */
    i4_ret = _tuner_setup_close_svl_builder();
    RET_ON_ERR(i4_ret);

     /*view deinit*/
    i4_ret = c_wgl_destroy_widget(tg_scan_view.h_frm);
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *     tuner_setup_view_hide
 * Description:
 *      hide UI.
 * Input arguments:
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32  tuner_setup_view_hide (VOID)
{
    INT32 i4_ret = 0;

    _tuner_setup_url_put_update_channel();//reload channel
    /*when hide tuner setup, it must enable change channel ,
    if this function is in if b_scan condition, it maybe can't enter this condition if find channel again*/
    if((_tuner_setup_get_wzd_state()!= OOBE_SCAN)&&
      (!(t_scan_antenna_atv.b_done && t_scan_antenna_dtv.b_done
            && t_scan_cable_atv.b_done && t_scan_cable_dtv.b_done)))
    {
        _tuner_setup_enable_ch_chg(FALSE);
    }
    a_amb_enable_system_key (TRUE);
    if(b_scan)
    {
        i4_ret = c_wgl_show(tg_scan_view.h_frm, WGL_SW_HIDE);
        if (i4_ret != TSP_OK)
        {
            TUNER_LOG_E("c_wgl-show fail i4_ret=%d\r\n",i4_ret);
        }
        a_agent_async_invoke(_tuner_setup_do_cancel_scan_nfy,NULL,0);
        a_cfg_ch_lst_store();
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name:
 *     a_tuner_setup_stop_scan
 * Description:
 *      hide UI.
 * Input arguments:
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
VOID  a_tuner_setup_stop_scan (VOID*      pv_data,
                               SIZE_T     z_data_size)
{
    _tuner_setup_url_put_update_channel();//reload channel

    TUNER_LOG_I("a_tuner_setup_stop_scan ,b_scan=%d\r\n", b_scan);

    if(b_scan)
    {
        c_wgl_show(tg_scan_view.h_frm, WGL_SW_HIDE);
        nav_hide_component(NAV_COMP_ID_TUNER_SETUP);
        nav_return_activation(NAV_COMP_ID_TUNER_SETUP);
        _tuner_setup_enable_ch_chg(FALSE);

        a_agent_async_invoke(_tuner_setup_do_cancel_scan_nfy,NULL,0);
    }

}

INT32  tuner_setup_view_hide_ex (VOID)
{
    INT32 i4_ret = 0;

    if(b_scan)
    {

        i4_ret = c_wgl_show(tg_scan_view.h_frm, WGL_SW_HIDE);
        if (i4_ret != TSP_OK)
        {
            TUNER_LOG_E("c_wgl_show fail ,i4_ret=%d\r\n",i4_ret);
        }
    }

    return i4_ret;
}

INT32 tuner_setup_view_show_ex (VOID)
{

    INT32 i4_ret = 0;

    if(b_scan)
    {
        if (a_menu_is_resume() == FALSE)
        {
            i4_ret = c_wgl_show(tg_scan_view.h_frm, WGL_SW_NORMAL);
        }
        if (i4_ret != TSP_OK)
        {
            TUNER_LOG_E("c_wgl_show fail ,i4_ret=%d\r\n",i4_ret);
        }
    }

    return i4_ret;
}



/*-----------------------------------------------------------------------------
 * Name:
 *     _tuner_setup_view_show_scan_widgets
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
VOID _tuner_setup_view_show_scan (VOID* pv_data1,
                                            VOID* pv_data2,
                                            VOID* pv_data3)
{
    INT32                       i4_ret;
    UTF16_T                     w2s_tmp_str[128] = {0};
    UTF16_T                     w2s_str[128]     = {0};
    UTF16_T                     i4_progress      = 0;

    b_clean_lists         = TRUE;
    b_repaint             = FALSE;

    c_wgl_set_visibility(tg_scan_view.h_frm, WGL_SW_NORMAL);

    //adjust h_per_text text for this may stay English first show but changed to French/... already,so set it first to make sure
    {
        c_uc_w2s_strcpy(w2s_tmp_str,TUNER_TEXT(MLM_SETTINGS_KEY_CHANNELS_FOUND));
        i4_ret = c_wgl_do_cmd(tg_scan_view.h_cd_text,
                              WGL_CMD_TEXT_SET_TEXT,
                              WGL_PACK(w2s_tmp_str),
                              WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
        //char tmp[128] = {0};
        //c_uc_w2s_to_ps(w2s_str,tmp,sizeof(tmp));
        //DBG_LOG_PRINT(("[test] %d tmp:%s\n",__LINE__,tmp));
    }
    c_wgl_set_visibility(tg_scan_view.h_cd_text, WGL_SW_NORMAL);
    c_wgl_set_visibility(tg_scan_view.h_icon, WGL_SW_NORMAL);

    c_wgl_set_visibility(tg_scan_view.h_bar, WGL_SW_NORMAL);


    //update dig&nan number text,because if have been scaned imcompleted before,the text will show the last info
    _txt_info_animate_update(TRUE);
    c_wgl_set_visibility(tg_scan_view.h_da_text, WGL_SW_NORMAL);

    //adjust h_per_text text for this may stay English first show but changed to French/... already,so set it first to make sure
    {
        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        _itoa(w2s_tmp_str, i4_progress, 4);
        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_uc_w2s_strcpy(w2s_tmp_str,TUNER_TEXT(MLM_SETTINGS_KEY_CHANNEL_PERCENT_COMPLETE));
        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(tg_scan_view.h_per_text,
                              WGL_CMD_TEXT_SET_TEXT,
                              WGL_PACK(w2s_str),
                              WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_str)));

        //char tmp[128] = {0};
        //c_uc_w2s_to_ps(w2s_str,tmp,sizeof(tmp));
        //DBG_LOG_PRINT(("[test] %d tmp:%s\n",__LINE__,tmp));

    }

    c_wgl_set_visibility(tg_scan_view.h_per_text, WGL_SW_NORMAL);

    c_wgl_set_focus(tg_scan_view.h_frm,WGL_NO_AUTO_REPAINT);

    i4_ret = nav_set_channel_scan_active(TRUE);
    if(i4_ret < 0)
    {
        TUNER_LOG_E("nav_set_channel_scan_active fail ,i4_ret=%d\n\r",i4_ret);
    }

    if(!b_scan)
    {
        //clear warning msg
        a_reset_err_msg_id();
        VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(FALSE);
        VIZIO_CTRL_ENABLE_SPI_HW_MODE(FALSE);

        if(!a_nav_tuner_setup_get_scan_new_channel())
        {
            DBG_LOG_PRINT(("[tuner cx] %s %d old\n",__FUNCTION__,__LINE__));
            i4_ret = _tuner_setup_start_scan_antenna();
        }
        else
        {
            DBG_LOG_PRINT(("[tuner cx] %s %d new\n",__FUNCTION__,__LINE__));
            i4_ret = _tuner_setup_start_scan_new_antenna();
        }
        if(i4_ret < 0)
        {
             TUNER_LOG_E("_tuner_setup_start_scan_antenna fail ,i4_ret=%d\n\r",i4_ret);
             nav_set_channel_scan_active(FALSE);
        }
        a_amb_enable_system_key (FALSE);
    }
}
/*-----------------------------------------------------------------------------
 * Name:
 *     tuner_setup_view_prepare_for_rest_scan
 * Description:
 *      This api due to different app before scan,menu,mmp,wo need post menu or mmp before scan.
 *       For MMP we need change channel first.will start scan after receive nav resume message
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
 INT32 tuner_setup_view_prepare_for_rest_scan (VOID)
{
    CHAR  s_name [APP_NAME_MAX_LEN + 1]     = { 0 };

    a_am_get_active_app (s_name);
    if(b_menu_scan_channel)
    {
        b_need_rest_scan_after_menu_scan = TRUE;
        a_icl_custom_set_tuner_setup_status(ICL_RECID_TUNER_SETUP_STATUS_CANCEL);
        return TSP_OK;
    }
    else if(c_strcmp(s_name, "menu") == 0)
    {

        /* step 1: cancel scan */
        b_need_rest_scan_after_menu_scan = TRUE;
        a_amb_pause_app("menu");
        a_amb_resume_app(NAV_NAME);
     }
     else if(c_strcmp(s_name, "mmp") == 0)
     {

        ISL_REC_T                   t_next_isl, t_isl_rec;
        INT32                       i4_ret;
        b_need_rest_scan_after_menu_scan = TRUE;
        /*get next input source*/
        i4_ret = a_isl_iterate_rec(0, ISL_ITERATE_DIR_THIS, &t_next_isl);
        if(TSP_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(), Fail to get specific isl rec, i4_ret=%d\r\n", __FUNCTION__, i4_ret));

        }
        i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
        if(TSP_OK != i4_ret)
        {
           DBG_ERROR((_ERROR_HEADER"%s(): a_tv_get_isl_rec_by_win_id failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        }

        i4_ret = a_tv_set_last_input_src_id (TV_WIN_ID_MAIN, t_isl_rec.ui1_id);
        if(TSP_OK != i4_ret)
        {
           DBG_ERROR((_ERROR_HEADER"%s(): a_tv_set_last_input_src_id failed. i4_ret = %d\r\n", __FUNCTION__,i4_ret));
        }
        {
            a_amb_resume_app(NAV_NAME);
        }

        return a_tv_set_input_src_id (TV_WIN_ID_MAIN, 0);
     }
    return TSP_OK;
}
BOOL tuner_setup_view_get_need_scan_after_resume(VOID)
{
    return b_need_rest_scan_after_menu_scan;
}
VOID tuner_setup_view_set_need_scan_after_resume(BOOL b_statue)
{
    b_need_rest_scan_after_menu_scan = b_statue;
}

/*-----------------------------------------------------------------------------
 * Name:
 *     tuner_setup_view_reset_scan
 * Description:
 *      restart to scan.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
INT32 tuner_setup_view_reset_scan (VOID)
{
    INT32       i4_ret              = TSP_OK;

    /* step 1: cancel scan */
    i4_ret = _cancel_scan(FALSE);
    if (i4_ret != TSP_OK)
    {
        TUNER_LOG_E("_cancel_scna fail i4_ret=[%d] \r\n", i4_ret);
    }

    /* step 2: reset variable data */

    /* reset dtv channel number */
    t_scan_antenna_dtv.i4_vir_ch_num = 0;
    t_scan_cable_dtv.i4_vir_ch_num   = 0;

    /* reset atv channel number */
    t_scan_antenna_atv.i4_phy_ch_num = 0;
    t_scan_cable_atv.i4_phy_ch_num   = 0;

    /*********in order to implement continuous scan:**********************
    1. stop scan; 2. clean svl and tsl; 3 active component
    NOTE: delay 450ms. if don't delay the timer,reset scan will be cancle
    **********************************************************************/
    i4_ret = _tuner_setup_clean_channel_table();
    if (i4_ret != TSP_OK)
    {
        TUNER_LOG_E("_tuner_setup_clean_channel_table error,i4_ret=[%d] \r\n",i4_ret);
    }
    a_cfg_set_crnt_channel_id(INVALID_CHANNEL_ID);
    a_cfg_set_last_channel_id(INVALID_CHANNEL_ID);

    /* step 3: start scan. */
    c_thread_delay(450);//if timer is too long, it will lead to show channel banner
    if(_tuner_setup_get_wzd_state() != OOBE_SCAN)
    {
        nav_grab_activation(NAV_COMP_ID_TUNER_SETUP);
    }
    i4_ret = tuner_setup_rest_view_show();
    if (i4_ret != TSP_OK)
    {
        TUNER_LOG_E("tuner_setup_rest_view_show,i4_ret=[%d] \r\n",i4_ret);
    }

    return TSP_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *     tuner_setup_view_show
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
INT32 tuner_setup_view_show (VOID)
{
    UTF16_T     w2s_tmp_str[128] = {0};
    UINT32      ui4_crnt_channel_id = INVALID_CHANNEL_ID;
    INT32       i4_ret;
    TV_WIN_ID_T      e_tv_win_id;

    nav_grab_activation(NAV_COMP_ID_TUNER_SETUP);

     if(_tuner_setup_get_input_src())
     {
         a_cfg_get_crnt_channel_id(&ui4_crnt_channel_id);
         if (ui4_crnt_channel_id != INVALID_CHANNEL_ID)
         {
            i4_ret = nav_get_focus_id(&e_tv_win_id);

            if(nav_is_signal_loss(e_tv_win_id))
            {
                c_uc_w2s_strcpy(w2s_tmp_str,TUNER_WARNINGS_TEXT(MLM_WARNINGS_KEY_WARNING_42));
                _tuner_setup_string_toast_view(tg_scan_view.h_canvas,w2s_tmp_str);
            }
         }
         else
         {
             _tuner_setup_view_show_scan(NULL,NULL,NULL);
         }
     }

    return i4_ret;
}

VOID _tuner_setup_c4tv_apron_custom_nfy(
        VOID*                    pv_param1, /*BOOL,connect or not; True,connect;FALSE,not connect*/
        VOID*                    pv_param2, /*UINT8,for ForcedUpdate,it is C4TV_APRON_UPDATE_STATE_T*/
        VOID*                    pv_param3
        )
{
    a_nav_ipts_src_c4tv_apron_custom_nfy(NULL, NULL, NULL);
    nav_request_context_switch(_tuner_setup_view_show_scan,NULL,NULL,NULL);
}

/*-----------------------------------------------------------------------------
 * Name:
 *     tuner_setup_rest_view_show
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
INT32 tuner_setup_rest_view_show(VOID)
{
    INT32       i4_ret;
    b_need_rest_scan_after_menu_scan = FALSE;

    if(_tuner_setup_get_wzd_state() == OOBE_SCAN)
    {
        b_clean_lists         = TRUE;
        b_repaint             = FALSE;

        i4_ret = nav_set_channel_scan_active(TRUE);
        RET_ON_ERR(i4_ret);

        if(!b_scan)
        {
            i4_ret = _tuner_setup_start_scan_antenna();
            RET_ON_ERR(i4_ret);
        }
    }
    else
    {
        UINT8  ui1_index = 0;
        UINT8  ui1_src_num = 0;
        ISL_REC_T  t_isl_rec_i = {0};

        a_isl_get_num_rec(&ui1_src_num);
        for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
        {
            c_memset(&t_isl_rec_i, 0, sizeof(ISL_REC_T));
            a_isl_get_rec_by_idx(ui1_index, &t_isl_rec_i);
            if ( t_isl_rec_i.e_src_type == INP_SRC_TYPE_TV )
            {
                break;
            }
        }

        if(!_tuner_setup_get_input_src())
        {
            CHAR       s_disp_name[SYS_NAME_LEN+1] = {0};
            UINT8      ui1_input_id = 0;
            ISL_REC_T  t_isl_rec = {0};

            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            RET_ON_ERR(i4_ret);
            i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
            RET_ON_ERR(i4_ret);
            i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
            RET_ON_ERR(i4_ret);

            if ( t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST )
            {
                a_cfg_av_set_input_src(s_disp_name, t_isl_rec_i.ui1_id);
                a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
                i4_ret = a_c4tv_apron_revoke_exit_cast(_tuner_setup_c4tv_apron_custom_nfy);
                TUNER_LOG_I("a_c4tv_apron_revoke_exit_cast i4_ret=%d",i4_ret);
            }
            else
            {
                //i4_ret = nav_ipts_switch_src(NAV_IPTS_SMS_BY_ID,TV_WIN_ID_MAIN,0);
                i4_ret = nav_change_av_inp_by_id(TV_WIN_ID_MAIN, t_isl_rec_i.ui1_id, NULL);
                if(i4_ret < 0)
                {
                    TUNER_LOG_E("nav_ipts_switch_src,i4_ret=%d\n\r",i4_ret);
                }
                nav_request_context_switch(_tuner_setup_view_show_scan,NULL,NULL,NULL);
            }
        }
        else
        {
            /* TV src should scan direct */
            nav_request_context_switch(_tuner_setup_view_show_scan,NULL,NULL,NULL);
        }
    }

    return TSP_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *    _tuner_setup_view_is_lock_state
 * Description:
 *      Is lock state or not.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      TRUE         LOCK state.
 *      Others       Unlock state.
 *---------------------------------------------------------------------------*/
static BOOL _tuner_setup_view_is_lock_state (NAV_CONTEXT_T*  pt_ctx)
{
    switch(nav_get_locked_status(pt_ctx->t_svc_res.e_focus_tv_win_id))
    {
        case LOCKED_STATUS_PROGRAM_RATING:
        case LOCKED_STATUS_CHANNEL_LOCKED:
        case LOCKED_STATUS_INP_SRC_LOCKED:
            return TRUE;
        default:
            return FALSE;
    }

    return FALSE;
}


/*-----------------------------------------------------------------------------
 * Name:
 *    tuner_setup_view_is_key_handler_fct
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
BOOL tuner_setup_view_is_key_handler_fct (NAV_CONTEXT_T*  pt_ctx, INT32 ui4_key_code)
{
    UINT32    ui4_crnt_channel_id = INVALID_CHANNEL_ID;

    a_cfg_get_crnt_channel_id(&ui4_crnt_channel_id);

    if(_tuner_setup_get_input_src()
      && FALSE == _tuner_setup_view_is_lock_state(pt_ctx)
      &&(ui4_crnt_channel_id == INVALID_CHANNEL_ID))//Do nothing if channels previously scanned
    {
        if(BTN_SELECT == ui4_key_code)
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T         w2s_str[128] = {0};
            
            c_uc_w2s_strcpy(w2s_str,TUNER_TTS_SETTINGS_TEXT(MLM_SETTINGS_KEY_TTS_SCAN));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif
            return TRUE;
        }
    }

    return FALSE;
}

/*----------------------------------------------------------------------------
 * Name: tuner_setup_range_get_val
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
INT32 tuner_setup_range_get_val(INT32*      pi4_val)
{
    //INT32  i4_ret;
    UINT8 ui1_val;

#if 0
    i4_ret = c_wgl_do_cmd(tg_scan_view.h_bar,
                          WGL_CMD_PG_GET_POS,
                          WGL_PACK(&i4_val),
                          NULL);
    RET_ON_ERR(i4_ret);
#endif

    a_cfg_cust_get_ch_scan_progress(&ui1_val);
    *pi4_val = (INT32)ui1_val;

    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: _tuner_setup_get_dig_and_ana_num
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
static VOID _tuner_setup_get_dig_and_ana_num(HANDLE_T h_svl,
                                            UINT16* pui2_num_recs_digital,
                                            UINT16* pui2_num_recs_analog)
{
    INT32      i4_ret;
    UINT32     ui4_ver_id = 0;
    UINT16     ui2_num_recs = 0;
    UINT16     ui2_i=0;
    UINT16     ui2_num_recs_digital = 0;
    UINT16     ui2_num_recs_analog = 0;
    SVL_REC_T  t_svl_rec;

    c_svl_lock(h_svl);

    /* get digital number */
    c_memset(&t_svl_rec,0,sizeof(t_svl_rec));
    i4_ret = c_svl_get_num_rec_by_brdcst_type(h_svl,
                                    BRDCST_TYPE_UNKNOWN,
                                    SB_VNET_ALL,
                                    &ui2_num_recs,
                                    &ui4_ver_id);
    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("func:%s line=%d fail !!!\r\n",__FUNCTION__,__LINE__);
        return -1;
    }

    for(ui2_i = 0; ui2_i < ui2_num_recs; ui2_i++)
    {
        c_svl_get_rec_by_brdcst_type(h_svl,
                                     BRDCST_TYPE_UNKNOWN,
                                     SB_VNET_ALL,
                                     ui2_i,
                                     &t_svl_rec,
                                     &ui4_ver_id);

        if(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG)
        {
            continue;
        }
#if 0
        if(t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE)
      {
          continue;
      }
#endif
         ui2_num_recs_digital++;
    }

    /* get analog number */
    c_memset(&t_svl_rec,0,sizeof(t_svl_rec));
    i4_ret = c_svl_get_num_rec_by_brdcst_type(h_svl,
                                     BRDCST_TYPE_ANALOG,
                                     SB_VNET_ALL,
                                     &ui2_num_recs,
                                     &ui4_ver_id);
    if(i4_ret != SVLR_OK)
    {
        TUNER_LOG_I("func:%s line=%d fail !!!\r\n",__FUNCTION__,__LINE__);
        return -1;
    }

    for(ui2_i = 0; ui2_i < ui2_num_recs; ui2_i++)
    {
      c_svl_get_rec_by_brdcst_type(h_svl,
                                   BRDCST_TYPE_ANALOG,
                                   SB_VNET_ALL,
                                   ui2_i,
                                   &t_svl_rec,
                                   &ui4_ver_id);

      if(t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE)
      {
          continue;
      }

      ui2_num_recs_analog++;
    }

    *pui2_num_recs_digital = ui2_num_recs_digital;
    *pui2_num_recs_analog  = ui2_num_recs_analog;

    c_svl_unlock(h_svl);

    return TSP_OK;
 }

/*----------------------------------------------------------------------------
 * Name: tuner_setup_scan_digital_get_val
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
INT32 tuner_setup_scan_digital_get_val(INT32*      pi4_val)
{
    if(b_scan || a_nav_tuner_setup_get_scan_new_channel())
    {
        *pi4_val = t_scan_antenna_dtv.i4_vir_ch_num + t_scan_cable_dtv.i4_vir_ch_num;
    }
    else
    {
        UINT16      ui2_air_dig_num = 0;
        UINT16      ui2_air_ana_num = 0;
        UINT16      ui2_cab_dig_num = 0;
        UINT16      ui2_cab_ana_num = 0;

        _tuner_setup_get_dig_and_ana_num(t_g_tuner_common.h_svl_air,&ui2_air_dig_num,&ui2_air_ana_num);

        _tuner_setup_get_dig_and_ana_num(t_g_tuner_common.h_svl_cable,&ui2_cab_dig_num,&ui2_cab_ana_num);


        *pi4_val = ui2_air_dig_num + ui2_cab_dig_num;
    }
    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: tuner_setup_scan_analog_get_val
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
INT32 tuner_setup_scan_analog_get_val(INT32*      pi4_val)
{
    if(b_scan || a_nav_tuner_setup_get_scan_new_channel())
    {
        *pi4_val = t_scan_antenna_atv.i4_vir_ch_num + t_scan_cable_atv.i4_vir_ch_num;
    }
    else
    {
        UINT16      ui2_air_dig_num = 0;
        UINT16      ui2_air_ana_num = 0;
        UINT16      ui2_cab_dig_num = 0;
        UINT16      ui2_cab_ana_num = 0;

        _tuner_setup_get_dig_and_ana_num(t_g_tuner_common.h_svl_air,&ui2_air_dig_num,&ui2_air_ana_num);

        _tuner_setup_get_dig_and_ana_num(t_g_tuner_common.h_svl_cable,&ui2_cab_dig_num,&ui2_cab_ana_num);

        *pi4_val = ui2_air_ana_num + ui2_cab_ana_num;
    }
    return TSP_OK;
}

/*----------------------------------------------------------------------------
 * Name: tuner_setup_get_scan_channel_info_
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
INT32 tuner_setup_get_scan_channel_info_(INT32 idx, CHAR* ps_num, CHAR* ps_name, BOOL* pb_is_dig)
{
    UINT16     ui2_ch_num_recs = 0;
    INT32      i4_ret          = 0;

    SVL_REC_T     t_svl_rec     = {0};
    OCL_SVL_REC_T t_ocl_svl_rec = {0};

    c_memset(&t_svl_rec, 0, sizeof(t_svl_rec));
    c_memset(&t_ocl_svl_rec, 0, sizeof(t_ocl_svl_rec));

    TUNER_LOG_I("tuner_setup_get_scan_channel_info_ idx=[%d]\n\r",idx);

    ui2_ch_num_recs = ocl_get_ocl_num();

    if (idx < 0 ||
        idx > (ui2_ch_num_recs - 1))
    {
        TUNER_LOG_E("the idx=[%d] has exceed ocl total num=[%d]\n\r",idx, ui2_ch_num_recs);
    }

    /* get the one channel list channel by the channel index */
    i4_ret = ocl_get_ocl_svl_by_index(idx, &t_svl_rec, &t_ocl_svl_rec);

    if (OCLR_OK != i4_ret)
    {
        TUNER_LOG_E("ocl_get_ocl_svl_by_index idx=[%d] ret=[%d]\n\r",idx, i4_ret);
        return i4_ret;
    }

    /* get the channel number and channel name. */
    nav_set_ch_num_and_name(&t_svl_rec, ps_num, ps_name);

    /* the svl record is digital or analog ? */
    if (BRDCST_TYPE_ATSC == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
    {
        *pb_is_dig = TRUE;
    }
    else
    {
        *pb_is_dig = FALSE;
    }

    return i4_ret;
 }

/*----------------------------------------------------------------------------
 * Name: tuner_setup_get_channel_name_by_channel_id
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

INT32 tuner_setup_get_channel_name_by_channel_id(UINT16 ui2_crnt_svl_id,UINT32 ui4_channel_id,CHAR* ps_src)
{
    UINT32      ui4_ver_id = SVL_NULL_VER_ID;
    UTF16_T     w2s_digits[8+1];
    BOOL        b_one_part_ch;
    UINT16      ui2_major;
    UINT16      ui2_minor;
    SVL_REC_T   t_svl_rec;
    INT32       i4_len = 0;
    INT32       i4_ret = 0;

    i4_ret = c_svl_get_rec_by_channel(ui2_crnt_svl_id,
                            ui4_channel_id,
                            SB_VNET_ALL,
                            0,
                            &t_svl_rec,
                            &ui4_ver_id);
    TUNER_LOG_E("get channel name,i4_ret=%d",i4_ret);

    b_one_part_ch = SB_ATSC_IS_ONE_PART_CHANNEL_ID(ui4_channel_id);
    ui2_major     = SB_ATSC_GET_MAJOR_CHANNEL_NUM(ui4_channel_id);
    ui2_minor     = SB_ATSC_GET_MINOR_CHANNEL_NUM(ui4_channel_id);

    /* Get the channel number */
    c_memset(w2s_digits, 0, sizeof(w2s_digits));
    _ch_num_to_str(ui2_major, ui2_minor, b_one_part_ch, w2s_digits);

    /* Get the channel name */
    i4_len = (INT32)c_strlen(t_svl_rec.uheader.t_rec_hdr.ac_name);
    if(i4_len > 48)
    {
        i4_len = 48;
    }

    TUNER_LOG_E("get channel name,name=%s",t_svl_rec.uheader.t_rec_hdr.ac_name);
    c_strcpy(ps_src,t_svl_rec.uheader.t_rec_hdr.ac_name);

    return TSP_OK;
}



/*----------------------------------------------------------------------------
 * Name: tuner_setup_get_current_channel
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
VOID tuner_setup_get_current_channel(CHAR* ps_num,CHAR* ps_name)
{
    INT32   i4_ret = 0;
    SVL_REC_T       t_svl_rec = {0};
    TV_WIN_ID_T     e_tv_win_id;
    if(b_scan)
    {
        c_strcpy(ps_num,"0-0");
    }
    else
    {
        i4_ret = nav_get_focus_id (&e_tv_win_id);
        if(i4_ret < 0)
        {
            e_tv_win_id = TV_WIN_ID_MAIN;
            TUNER_LOG_E("nav_get_focus_id fail: %d\n\r", e_tv_win_id);
        }
        i4_ret = nav_get_svl_rec (e_tv_win_id, &t_svl_rec);
        if (i4_ret < NAVR_OK)
        {
            TUNER_LOG_E("nav_get_svl_rec fail: \n\r");
        }

        nav_set_ch_num_and_name (&t_svl_rec, ps_num, ps_name);
        if(c_strcmp(ps_num,"") == 0)
        {
            c_strcpy(ps_num,"0-0");
        }
    }
}


/*----------------------------------------------------------------------------
 * Name: a_tuner_setup_url_put_channels_changed
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *----------------------------------------------------------------------------*/
VOID a_tuner_setup_url_put_channels_changed()
{
    HANDLE_T     h_handle = NULL_HANDLE;
    INT32        i4_ret = 0;
    HTTPC_DATA_T t_data;
    char         ut_url[256] = "http://127.0.0.1:7346/state/tuner/channels_changed";
    char s_c_session_token[24] = {0};
    char session_header[64] = {0};

    DBG_LOG_PRINT(("%s,%d\n", __FUNCTION__, __LINE__));

    c_httpc_data_init(&t_data);
    i4_ret = c_httpc_new_session(&h_handle);
    if (i4_ret == HTTPR_OK)
    {
        TUNER_LOG_I("new session PASS\n");
    }
    else
    {
        TUNER_LOG_E("new session FAIL,i4_ret:%d\n",i4_ret);
    }

    c_httpc_append_header(h_handle, "Expect: ");
    c_httpc_append_header(h_handle, "content-type: application/json");

    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
        if(h_handle != NULL_HANDLE)
            c_httpc_free_session(h_handle);
        return;
    }
    sprintf(session_header, "SESSION: %s", s_c_session_token);
    session_header[63] = '\0';
    c_httpc_append_header(h_handle, session_header);

    i4_ret = c_httpc_put(h_handle, ut_url, NULL, 0, &t_data);

    if (i4_ret == HTTPR_OK)
    {
        if(_tuner_setup_get_wzd_state() == OOBE_SCAN)
        {
            c_thread_delay(100);
        }
        TUNER_LOG_I("c_httpc_put get PASS\n");
    }
    else
    {
        TUNER_LOG_E("c_httpc_put FAIL.i4_ret:%d.!!!\n",i4_ret);
        c_httpc_free_session(h_handle);
        c_httpc_data_free(&t_data);
        return ;
    }

    c_httpc_free_session(h_handle);
    c_httpc_data_free(&t_data);

}
/*----------------------------------------------------------------------------
 * Name: a_tuner_setup_is_key_to_discard
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *----------------------------------------------------------------------------*/
BOOL a_tuner_setup_is_key_to_discard(UINT32 ui4_key_code)
{
    if (TRUE == nav_is_channel_scan_active())
    {
        switch (ui4_key_code)
        {
           // case BTN_INPUT_SRC:
            case BTN_POWER:
                return FALSE;
            case BTN_VOL_DOWN:
            case BTN_VOL_UP:
            case BTN_MUTE:
                if (a_wzd_is_oobe_mode())
                {
                    return FALSE;
                }
            default:
                return TRUE;
        }
    }

    return FALSE;
}

VOID a_tuner_setup_scab_stop(VOID)
{
    TUNER_LOG_I("STOP_SCAN_TUNER \n\r");

    tuner_setup_view_hide();

    nav_set_channel_scan_active(FALSE);

    nav_hide_component(NAV_COMP_ID_TUNER_SETUP);

    nav_return_activation(NAV_COMP_ID_TUNER_SETUP);
}

VOID a_tuner_setup_url_put_drrt_changed(VOID)
{
    nav_request_context_switch(_drrt_change_proc,NULL, NULL,NULL);
}

VOID a_nav_tuner_setup_start_scan_channel (VOID)
{
    b_menu_scan_channel = TRUE;
    nav_request_context_switch(_tuner_setup_scan_in_menu,NULL, NULL,NULL);
}

VOID a_nav_tuner_setup_cancel_scan_channel (VOID)
{
    b_menu_scan_channel = FALSE;
    //nav_request_context_switch(_tuner_setup_cancel_scan_in_menu,NULL, NULL,NULL);
    menu_async_invoke(_tuner_setup_cancel_scan_in_menu,NULL,0,TRUE);
}
BOOL a_get_current_menu_scan_statue(VOID)
{
    return b_menu_scan_channel;
}

VOID a_nav_tuner_setup_set_scan_new_channel (BOOL val)
{
    b_menu_scan_new_channel = val;
}

BOOL a_nav_tuner_setup_get_scan_new_channel(VOID)
{
    return b_menu_scan_new_channel;
}

static INT32 _tuner_setup_start_scan_before(VOID)
{
    INT32               i4_ret;

    DBG_LOG_PRINT(("[tuner setup] _tuner_setup_start_scan_before=%d b_scan=%d\n",__LINE__,b_scan));
    if (!b_scan)
    {
        VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(FALSE);
        VIZIO_CTRL_ENABLE_SPI_HW_MODE(FALSE);

        _tuner_setup_enable_ch_chg(TRUE);
        a_cfg_cust_set_ch_scan_progress(0);    //Need clear scan progress before start scan
        /* close service context */
        i4_ret = c_svctx_sync_stop_svc(_tuner_get_crnt_svctx(),
                                       DEFAULT_STOP_SVC_TIMEOUT);
        if (i4_ret == SVCTXR_TIMEOUT)
        {
            TUNER_LOG_E("Cannot close service context timeout. i4_ret:%d\r\n",i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }
        else if (i4_ret != SVCTXR_OK && i4_ret != SVCTXR_ALREADY_STOPPED)
        {
            TUNER_LOG_E("Cannot close service context. %d\r\n", i4_ret);
            _on_start_scan_fail();
            return TSP_FAIL;
        }

        TUNER_LOG_I("_tuner_setup_start_scan_antenna. b_clean_lists=%d\r\n",b_clean_lists);

        /* clean the service list */
        if(b_clean_lists && !a_nav_tuner_setup_get_scan_new_channel())
        {
            TUNER_LOG_I("clean AIR SVL.\r\n");

            /* clean antenna/cable channel table */
            i4_ret = _tuner_setup_clean_channel_table();

            a_cfg_set_crnt_channel_id(INVALID_CHANNEL_ID);
            a_cfg_set_last_channel_id(INVALID_CHANNEL_ID);
        }

        b_scan = TRUE;

        ant_ana_start = ANTENTA_CH_START;
        ant_dig_start = ANTENTA_CH_START;
        cab_ana_start = CABLE_CH_START;
        cab_dig_start = CABLE_CH_START;

        ant_ana_end = ANTENTA_CH_MAX;
        ant_dig_end = ANTENTA_CH_MAX;
        cab_ana_end = CABLE_CH_MAX;
        cab_dig_end = CABLE_CH_MAX;

        while(_tuner_check_phy_CH(t_g_tuner_atsc.h_sb_dig_air,ant_dig_start) && ant_dig_start < ANTENTA_CH_MAX)
            ant_dig_start++;
        while(_tuner_check_phy_CH(t_g_tuner_atsc.h_sb_dig_cable,cab_dig_start) && cab_dig_start < CABLE_CH_MAX)
            cab_dig_start++;
        while(_tuner_check_phy_CH(t_g_tuner_atsc.h_sb_anlg_air,ant_ana_start) && ant_ana_start < ANTENTA_CH_MAX)
            ant_ana_start++;
        while(_tuner_check_phy_CH(t_g_tuner_atsc.h_sb_anlg_cable,cab_ana_start) && cab_ana_start < CABLE_CH_MAX)
            cab_ana_start++;

        while(_tuner_check_phy_CH(t_g_tuner_atsc.h_sb_dig_air,ant_dig_end) && ant_dig_end > ANTENTA_CH_START)
            ant_dig_end--;
        while(_tuner_check_phy_CH(t_g_tuner_atsc.h_sb_dig_cable,cab_dig_end) && cab_dig_end > CABLE_CH_START)
            cab_dig_end--;
        while(_tuner_check_phy_CH(t_g_tuner_atsc.h_sb_anlg_air,ant_ana_end) && ant_ana_end > ANTENTA_CH_START)
            ant_ana_end--;
        while(_tuner_check_phy_CH(t_g_tuner_atsc.h_sb_anlg_cable,cab_ana_end) && cab_ana_end > CABLE_CH_START)
            cab_ana_end--;

        TUNER_LOG_I("[tuner scan] ant_dig(%d,%d),ant_ana(%d,%d),cab_dig(%d,%d),cab_ana(%d,%d)\n",
            ant_dig_start,ant_dig_end,ant_ana_start,ant_ana_end,cab_dig_start,cab_dig_end,cab_ana_start,cab_ana_end);

        /* set up the dirty flags for storing SVL and TSL */
        t_g_tuner_common.b_svl_air_dirty = TRUE;
        t_g_tuner_common.b_tsl_air_dirty = TRUE;

        /* Init the antenna scan relative data */
        t_scan_antenna_atv.i4_vir_ch_num = 0;
        t_scan_antenna_atv.i4_phy_ch_num = ant_ana_start;
        t_scan_antenna_atv.i4_phy_ch_ttl = ant_ana_end;  /* assign a big enough value */
        t_scan_antenna_atv.b_done = FALSE;
        t_scan_antenna_dtv.i4_vir_ch_num = 0;
        t_scan_antenna_dtv.i4_phy_ch_num = ant_dig_start;
        t_scan_antenna_dtv.i4_phy_ch_ttl = ant_dig_end;  /* assign a big enough value */
        t_scan_antenna_dtv.b_done = FALSE;

                /* set up the dirty flags for storing SVL and TSL */
        t_g_tuner_common.b_svl_cable_dirty = TRUE;
        t_g_tuner_common.b_tsl_cable_dirty = TRUE;

        /* Init the cable scan relative data */
        t_scan_cable_atv.i4_vir_ch_num = 0;
        t_scan_cable_atv.i4_phy_ch_num = cab_ana_start;
        t_scan_cable_atv.i4_phy_ch_ttl = cab_ana_end;  /* assign a big enough value */
        t_scan_cable_atv.b_done = FALSE;
        t_scan_cable_dtv.i4_vir_ch_num = 0;
        t_scan_cable_dtv.i4_phy_ch_num = cab_dig_start;
        t_scan_cable_dtv.i4_phy_ch_ttl = cab_dig_end;  /* assign a big enough value */
        t_scan_cable_dtv.b_done = FALSE;

     }
    return 0;
}

static INT32 _tuner_setup_start_scan_new_antenna(VOID)
{
    //for pre cable tsl list
    _tuner_setup_create_cable_tsl_table();

    _tuner_setup_sort_channels();
    _tuner_setup_start_scan_before();

    //_tuner_setup_url_put_update_channel();
    rest_event_notify("tv_settings/channels/channel_scan_state", 0, "");//scan start

    _tuner_setup_scan_antenna_atv(ant_ana_start);
    _tuner_setup_scan_antenna_dtv(ant_dig_start);

    return TSP_OK;
}

static INT32 _tuner_setup_start_scan_new_cable(VOID)
{
    if(b_scan)
        b_scan_cable = TRUE;

    rest_event_notify("tv_settings/channels/channel_scan_state", 0, "");//scan start

    _tuner_setup_scan_cable_atv(cab_ana_start);
    _tuner_setup_scan_cable_dtv(cab_dig_start);

    return TSP_OK;
}

static VOID _tuner_setup_do_scan_new_nfy(VOID* pv_data,
                         SIZE_T  z_data_size)
{
    INT32       i4_ret;
    GL_RECT_T   t_rect;
    AS_SCAN_NFY_T* pt_scan_nfy      = (AS_SCAN_NFY_T*)pv_data;
    AS_SCAN_INFO_T* pt_scan_info    = (AS_SCAN_INFO_T*)pt_scan_nfy->pv_nfy_tag;
    INT32       i4_progress;
    UINT16      ui2_air_dig_num = 0;
    UINT16      ui2_air_ana_num = 0;
    UINT16      ui2_cab_dig_num = 0;
    UINT16      ui2_cab_ana_num = 0;
    UINT32      ui4_dig_num = 0;
    UINT32      ui4_ana_num = 0;

    TUNER_LOG_I("[tuner scan] ui4_nfy_reason:%x\n",pt_scan_nfy->ui4_nfy_reason);

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_PROGRESS)
    {
        TUNER_LOG_I("[tuner scan] SB_REASON_PROGRESS \n");
        if (b_scan)
        {
            BOOL    b_paint_info = (_GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data) > 0);

            if(pt_scan_info->h_builder == t_g_tuner_atsc.h_sb_dig_air)
            {
                TUNER_LOG_I("[tuner scan] ant_dig scan\n");
            }
            else if(pt_scan_info->h_builder == t_g_tuner_atsc.h_sb_dig_cable)
            {
                TUNER_LOG_I("[tuner scan] cab_dig scan \n");
            }
            else if(pt_scan_info->h_builder == t_g_tuner_atsc.h_sb_anlg_air)
            {
                TUNER_LOG_I("[tuner scan] ant_ana scan\n");
            }
            else if(pt_scan_info->h_builder == t_g_tuner_atsc.h_sb_anlg_cable)
            {
                TUNER_LOG_I("[tuner scan] cab_ana scan\n");
            }

            TUNER_LOG_I("[Tuner scan]Scan %d/%d: total =[%d] vir channels found, current freq find [%d] channels.\r\n",
                      pt_scan_info->i4_phy_ch_num,
                      pt_scan_info->i4_phy_ch_ttl,
                      pt_scan_info->i4_vir_ch_num,
                      _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data));
            if (TRUE != b_scan_cable
                && _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data) > 0)
            {
                TUNER_LOG_I("<TUNER SETUP>Current scan air. frequence=[%d], total=[%d]\n",
                           pt_scan_info->i4_phy_ch_num,
                           pt_scan_info->i4_phy_ch_ttl);

                i4_ret = -1;

                //should compare this antenna channel frequency to cable channel frequency,because cable channel maybe already existed
                //otherwise this antenna channel may would be showed,and then be repleased by cable channel
                if (pt_scan_info->i4_phy_ch_num > 13)
                {
                    /* we shuold check antenna and cable SVL freq */
                    i4_ret = _tuner_setup_rm_farther_ch_cable(pt_scan_info->i4_phy_ch_num,
                                                 t_g_tuner_common.h_svl_air,
                                                 t_g_tuner_common.h_svl_cable);

                    if (SVLR_OK == i4_ret)
                    {
                        TUNER_LOG_I("<TUNER SETUP>Do not show update scan info when set channel to fake.\n");

                        /* do not show update scan info when set channel to fake */
                        return;
                    }
                }
            }

            if (TRUE == b_scan_cable
                && _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data) > 0)
            {
                TUNER_LOG_I("<TUNER SETUP>Current scan cable. frequence=[%d], total=[%d]\n",
                           pt_scan_info->i4_phy_ch_num,
                           pt_scan_info->i4_phy_ch_ttl);

                i4_ret = -1;

                /* we shuold check antenna SVL fr index between 2 and 13 */
                if ((pt_scan_info->i4_phy_ch_num > 1) && (pt_scan_info->i4_phy_ch_num < 14))
                {
                     i4_ret = _tuner_setup_rm_duplicate_ch(pt_scan_info->i4_phy_ch_num,
                                                                 t_g_tuner_common.h_svl_air,
                                                                 t_g_tuner_common.h_svl_cable);
                }
                else if (pt_scan_info->i4_phy_ch_num > 13)
                {
                    /* we shuold check antenna and cable SVL freq */
                    i4_ret = _tuner_setup_rm_farther_ch(pt_scan_info->i4_phy_ch_num,
                                                 t_g_tuner_common.h_svl_air,
                                                 t_g_tuner_common.h_svl_cable);
                }

                if (SVLR_OK == i4_ret)
                {
                    TUNER_LOG_I("<TUNER SETUP>Do not show update scan info when set channel to fake.\n");

                    /* do not show update scan info when set channel to fake */
                    return;
                }
            }

            pt_scan_info->i4_vir_ch_num += _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data);

            if(pt_scan_info->i4_phy_ch_num > pt_scan_info->i4_phy_ch_ttl)
            {
                 TUNER_LOG_I("<TUNER SETUP>ph_ch_num > ph_ch_ttl!:%d,%d\n",
                           pt_scan_info->i4_phy_ch_num,
                           pt_scan_info->i4_phy_ch_ttl);
                 pt_scan_info->i4_phy_ch_num = pt_scan_info->i4_phy_ch_ttl;
            }

            i4_progress = _calc_progress();

            /* if progress no update & no channel scanned from current PTC, don't need to update UI. */
            if ((i4_g_scan_progress == i4_progress) && (b_paint_info == FALSE))
            {
                return;
            }

            i4_g_scan_progress = i4_progress;

            if(i4_progress!=100)
            {
                a_cfg_cust_set_ch_scan_progress((UINT8)i4_progress);
            }

            // notify REST AP to send event to customer's module
            rest_event_notify("tv_settings/channels/percent_complete", i4_progress, "");

            i4_ret=c_wgl_do_cmd(tg_scan_view.h_bar,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK((INT32) i4_progress),
                         NULL);
            if (i4_ret != TSP_OK)
            {
                TUNER_LOG_E("c_wgl_do_cmd fail i4_ret:%d\r\n",i4_ret);
            }

            SET_RECT_BY_SIZE(&t_rect,
                     960 - i4_progress * 9.6,
                     TUNER_PB_Y,
                     1920,
                     TUNER_PB_HEIGHT);
            i4_ret = c_wgl_move(tg_scan_view.h_bar,&t_rect,WGL_ASYNC_AUTO_REPAINT);
            if (i4_ret != TSP_OK)
            {
               TUNER_LOG_E("c_wgl_move fail i4_ret:%d\r\n",i4_ret);
            }

            i4_ret =  _percent_set_text(i4_progress);
            if (i4_ret != TSP_OK)
            {
                TUNER_LOG_E("_percent_set_text fail ,i4_ret:%d\r\n",i4_ret);
            }
            /* get gui lang */
            i4_ret = _tuner_setup_get_gui_lang();
            TUNER_LOG_I("_tuner_setup_view_lang_notify_cb_handler, update GUI language, i4_ret=[%d].\n", i4_ret);
            /* update title */
            i4_ret = _update_scan_ch_title();

            i4_ret = c_wgl_repaint(tg_scan_view.h_frm, NULL, TRUE);

            if (i4_ret != TSP_OK)
            {
                TUNER_LOG_E("c_wgl_repaint fail ,i4_ret:%d\r\n",i4_ret);
            }

            if (b_paint_info)
            {
                b_repaint = TRUE;
                _txt_info_animate_update(FALSE);

                //a_cfg_ch_lst_store();

                _update_ch_lst(((pt_scan_info == &t_scan_antenna_atv)||(pt_scan_info == &t_scan_cable_atv)) ? TRUE : FALSE ,
                                _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data));

                // notify REST AP to send event to customer's module
                rest_event_notify("tv_settings/channels/analog", t_scan_antenna_atv.i4_vir_ch_num + t_scan_cable_atv.i4_vir_ch_num, "");
                rest_event_notify("tv_settings/channels/digital", t_scan_antenna_dtv.i4_vir_ch_num + t_scan_cable_dtv.i4_vir_ch_num, "");
            }


            a_icl_custom_set_tuner_setup_status(ICL_RECID_TUNER_SETUP_STATUS_PROGRESS);


            TUNER_LOG_I("Scan %d/%d: %d channels found.\r\n",
                      pt_scan_info->i4_phy_ch_num, pt_scan_info->i4_phy_ch_ttl, pt_scan_info->i4_vir_ch_num);

        }

    }

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_CANCEL)
    {
        TUNER_LOG_I("[tuner scan] SB_REASON_ABORT \n");
        a_cfg_ch_lst_store();

        a_icl_custom_set_tuner_setup_status(ICL_RECID_TUNER_SETUP_STATUS_CANCEL);

        rest_event_notify("tv_settings/channels/channel_scan_state", 2, "");//scan cancel

        _tuner_setup_clear_scan_table_list();
        VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(TRUE);
        VIZIO_CTRL_ENABLE_SPI_HW_MODE(TRUE);

    }
    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_ABORT)
    {
        TUNER_LOG_I("[tuner scan] SB_REASON_CANCEL \n");

        if(b_scan)
        {

            a_icl_custom_set_tuner_setup_status(ICL_RECID_TUNER_SETUP_STATUS_ABORT);


            /* Abort is always triggered by svl-builder internal */
            _tuner_setup_enable_ch_chg(FALSE);

            _on_scan_stop();

            if(pt_scan_info == &t_scan_antenna_atv)
            {
                /* cancel the DTV one */
                c_sb_cancel_scan(t_scan_antenna_dtv.h_builder);
            }
            else if(pt_scan_info == &t_scan_antenna_dtv)
            {
                /* cancel the ATV one */
                c_sb_cancel_scan(t_scan_antenna_atv.h_builder);
            }

            if(pt_scan_info == &t_scan_cable_atv)
            {
                /* cancel the DTV one */
                c_sb_cancel_scan(t_scan_cable_dtv.h_builder);
            }
            else if(pt_scan_info == &t_scan_cable_dtv)
            {
                /* cancel the ATV one */
                c_sb_cancel_scan(t_scan_cable_atv.h_builder);
            }

            i4_ret = c_wgl_repaint(tg_scan_view.h_frm, NULL, TRUE);
            if (i4_ret != TSP_OK)
            {
                TUNER_LOG_E("c_wgl_repaint fail i4_ret:%d\r\n");
            }

            _tuner_setup_clear_scan_table_list();
            VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(TRUE);
            VIZIO_CTRL_ENABLE_SPI_HW_MODE(TRUE);

        }
    }
    /* Check if the builder reach "AVAILABLE" condition */
    if(pt_scan_nfy->ui4_nfy_reason & SB_REASON_COMPLETE)
    {
        TUNER_LOG_I("[tuner scan] SB_REASON_COMPLETE\n");

        if(pt_scan_info->i4_phy_ch_num >= pt_scan_info->i4_phy_ch_ttl)
        {
            pt_scan_info->b_done = TRUE;
        }
        if(pt_scan_info->i4_phy_ch_num < pt_scan_info->i4_phy_ch_ttl)
        {
            pt_scan_info->i4_phy_ch_num += 1;
            while(_tuner_check_phy_CH(pt_scan_info->h_builder,pt_scan_info->i4_phy_ch_num))
            {
                pt_scan_info->i4_phy_ch_num += 1;
            }
            if(pt_scan_info->i4_phy_ch_num > pt_scan_info->i4_phy_ch_ttl)
            {
                pt_scan_info->b_done = TRUE;
            }
        }

        if(pt_scan_info->h_builder == t_g_tuner_atsc.h_sb_dig_air && !pt_scan_info->b_done)
        {
            TUNER_LOG_I("[tuner scan] next scan ant_dtv_CH:%d\n",pt_scan_info->i4_phy_ch_num);
            if(b_scan)
            {
                _tuner_setup_scan_antenna_dtv(pt_scan_info->i4_phy_ch_num);
            }
        }
        else if(pt_scan_info->h_builder == t_g_tuner_atsc.h_sb_dig_cable && !pt_scan_info->b_done)
        {
            TUNER_LOG_I("[tuner scan] next scan cab_dtv_CH:%d\n",pt_scan_info->i4_phy_ch_num);
            if(b_scan_cable)
            {
                _tuner_setup_scan_cable_dtv(pt_scan_info->i4_phy_ch_num);
            }
        }
        else if(pt_scan_info->h_builder == t_g_tuner_atsc.h_sb_anlg_air && !pt_scan_info->b_done)
        {
            TUNER_LOG_I("[tuner scan] next scan ant_atv_CH:%d\n",pt_scan_info->i4_phy_ch_num);
            if(b_scan)
            {
                _tuner_setup_scan_antenna_atv(pt_scan_info->i4_phy_ch_num);
            }
        }
        else if(pt_scan_info->h_builder == t_g_tuner_atsc.h_sb_anlg_cable && !pt_scan_info->b_done)
        {
            TUNER_LOG_I("[tuner scan] next scan cab_atv_CH:%d\n",pt_scan_info->i4_phy_ch_num);
            if(b_scan_cable)
            {
                _tuner_setup_scan_cable_atv(pt_scan_info->i4_phy_ch_num);
            }
        }

            if(t_scan_antenna_atv.b_done && t_scan_antenna_dtv.b_done &&
                !t_scan_cable_atv.b_done && !t_scan_cable_dtv.b_done && !b_scan_cable)
            {
                TUNER_LOG_I("[tuner scan] antenna scan done,next to cable scan %d\n",__LINE__);
                /* set antenna scan completed first */
                a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_COMPLETED_SCAN);
                /* create the air tsl table. */
                _tuner_setup_create_air_tsl_table();
                _tuner_setup_start_scan_new_cable();
            }
            #if 0
            if((t_scan_cable_atv.i4_vir_ch_num + t_scan_cable_dtv.i4_vir_ch_num)>=1)
            {
                a_cfg_set_tuner_type(APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_CABLE);
            }
            #endif
            /* make sure that both ATV/DTV scan complete */
            if(t_scan_antenna_atv.b_done && t_scan_antenna_dtv.b_done
                && t_scan_cable_atv.b_done && t_scan_cable_dtv.b_done)
            {
                if(b_scan && !b_menu_scan_channel)
                {
                    _on_scan_stop();
                    i4_ret=c_wgl_do_cmd(tg_scan_view.h_bar,
                                WGL_CMD_PG_SET_POS,
                                WGL_PACK((INT32) 100),
                                NULL);
                    if (i4_ret != TSP_OK)
                    {
                        TUNER_LOG_E("c_wgl_do_cmd fail i4_ret:%d\r\n",i4_ret);
                    }

                    c_wgl_repaint(tg_scan_view.h_frm, NULL, TRUE);
                }
                else
                {
                    b_scan = FALSE;
                    b_scan_cable = FALSE;
                    nav_set_channel_scan_active(FALSE);
                    /* channel scan status */
                    if (b_is_cancel)
                    {
                        TUNER_LOG_I("[tuner set scan_status] set ACFG_CUST_PARTIAL_SCAN\n");
                        a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_PARTIAL_SCAN);
                        b_is_cancel = FALSE;
                    }
                    else
                    {
                        TUNER_LOG_I("[tuner set scan_status] set ACFG_CUST_PARTIAL_SCAN\n");
                        a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_COMPLETED_SCAN);
                    }
                }
                a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
                /* Re-open SVL */
                if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID &&
                    t_g_tuner_common.h_svl_air == NULL_HANDLE)
                {
                    i4_ret = c_svl_open(ATSC_TRSTRL_SVL_ID,
                                        NULL,
                                        NULL,
                                        &t_g_tuner_common.h_svl_air);
                    if (i4_ret != SVLR_OK)
                    {
                        TUNER_LOG_E("Can't open SVL,%d\r\n",i4_ret);
                        t_g_tuner_common.h_svl_air = NULL_HANDLE;
                    }
                }
                else if (ui2_crnt_svl_id == ATSC_CABLE_SVL_ID &&
                         t_g_tuner_common.h_svl_cable == NULL_HANDLE)
                {
                    i4_ret = c_svl_open(ATSC_CABLE_SVL_ID,
                                        NULL,
                                        NULL,
                                        &t_g_tuner_common.h_svl_cable);
                    if (i4_ret != SVLR_OK)
                    {
                        TUNER_LOG_E("Can't open SVL,%d\r\n",i4_ret);
                        t_g_tuner_common.h_svl_cable = NULL_HANDLE;
                    }
                }

                if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_COMPLETE)
                {
                    _tuner_setup_url_put_update_channel();//reload channel

                    if(!b_menu_scan_channel)
                        c_wgl_show(tg_scan_view.h_frm, WGL_SW_HIDE);

                    if(_tuner_setup_get_wzd_state()!= OOBE_SCAN &&
                        !b_menu_scan_channel)
                    {
                        _tuner_setup_enable_ch_chg(FALSE);
                        TUNER_LOG_I("do_scan_nfy");
                        nav_request_context_switch(_do_show_warning_nfy,NULL, NULL,NULL);
                    }


                    a_icl_custom_set_tuner_setup_status(ICL_RECID_TUNER_SETUP_STATUS_COMPLETE);
                    if(b_menu_scan_channel)
                    {
                        _tuner_setup_enable_ch_chg(FALSE);
                        _tuner_setup_select_crnt_or_first_channel(TRUE);
                    }


                    if(_tuner_setup_get_wzd_state()== OOBE_SCAN)
                    {
                        _tuner_setup_set_cfg_first_channel_id();
                    }

                    _tuner_setup_clear_scan_table_list();
                    a_cfg_ch_lst_store();

                    VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(TRUE);
                    VIZIO_CTRL_ENABLE_SPI_HW_MODE(TRUE);

                }
                rest_event_notify("tv_settings/channels/channel_scan_state", 1, "");  //scan complete

                TUNER_LOG_I("[OCL] ocl enter!\n");
                /*nav_request_context_switch(
                            _tuner_setup_ocl_reinstall,
                            NULL,
                            NULL,
                            NULL);*/
                nav_request_context_switch_in_sync(_tuner_setup_ocl_reinstall,
                                                    NULL,
                                                    NULL,
                                                    NULL,
                                                    5000);
                i4_progress =100;
                a_cfg_cust_set_ch_scan_progress((UINT8)i4_progress);

                _tuner_setup_get_dig_and_ana_num(t_g_tuner_common.h_svl_air,&ui2_air_dig_num,&ui2_air_ana_num);
                _tuner_setup_get_dig_and_ana_num(t_g_tuner_common.h_svl_cable,&ui2_cab_dig_num,&ui2_cab_ana_num);

                ui4_dig_num = ui2_air_dig_num + ui2_cab_dig_num;
                ui4_ana_num = ui2_air_ana_num + ui2_cab_ana_num;

                // notify REST AP to send event to customer's module
                rest_event_notify("tv_settings/channels/analog", ui4_ana_num, "");
                rest_event_notify("tv_settings/channels/digital", ui4_dig_num, "");
            }

    }


}


static VOID _tuner_setup_scan_new_nfy_fct(HANDLE_T          h_builder,
                          UINT32            ui4_nfy_reason,
                          INT32             i4_nfy_data,
                          VOID*             pv_nfy_tag)
{
    AS_SCAN_NFY_T   t_scan_nfy;

    t_scan_nfy.h_builder        = h_builder;
    t_scan_nfy.ui4_nfy_reason   = ui4_nfy_reason;
    t_scan_nfy.i4_nfy_data      = i4_nfy_data;
    t_scan_nfy.pv_nfy_tag       = pv_nfy_tag;

    a_agent_async_invoke(_tuner_setup_do_scan_new_nfy,&t_scan_nfy,sizeof(AS_SCAN_NFY_T));

}

static INT32 _tuner_setup_scan_antenna_atv(UINT16 idx)
{
    SB_COND_T           e_cond      = 0;
    UINT32              i4_ret      = 0;

    /* Start scan the ATV channels*/
    SB_NTSC_SCAN_DATA_T t_ntsc_scan_data;

    TUNER_LOG_I("Scan Mode: NTSC/AIR,\r\n");

    /* udpate the sink name to builder */
    _tuner_atsc_update_sb_snk_name(t_g_tuner_atsc.h_sb_anlg_air,
                                         _tuner_get_crnt_svctx());

    /* start scan */
    c_memset(&t_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));
    t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_TER_FREQ_PLAN;
    t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_SINGLE_RF_CHANNEL;
    t_ntsc_scan_data.ui2_start_idx = idx;
    t_ntsc_scan_data.ui2_end_idx   = idx;

    t_scan_antenna_atv.h_builder = t_g_tuner_atsc.h_sb_anlg_air;

    i4_ret = c_sb_start_scan(t_g_tuner_atsc.h_sb_anlg_air,
                                 &t_ntsc_scan_data,
                                 &t_scan_antenna_atv,
                                 _tuner_setup_scan_new_nfy_fct,
                                 &e_cond);
    if (i4_ret != SBR_OK)
    {
        TUNER_LOG_E("Can't start scan,i4_ret:%d e_cond:%d\r\n",i4_ret,e_cond);
        _on_start_scan_fail();
        return TSP_FAIL;
    }


    return 0;
}


static INT32 _tuner_setup_scan_antenna_dtv(UINT16 idx)
{
    SB_COND_T           e_cond      = {0};
    //UINT16              idx         = 0;
    UINT32              i4_ret      = 0;

    SB_ATSC_SCAN_DATA_T t_atsc_scan_data;

    TUNER_LOG_I("Scan Mode: ATSC/AIR\r\n");

    c_memset(&t_atsc_scan_data, 0, sizeof(SB_ATSC_SCAN_DATA_T));
    t_atsc_scan_data.e_scan_type   = SB_ATSC_SCAN_TYPE_SINGLE_RF_CHANNEL;
    t_atsc_scan_data.ui4_scan_info = ((idx  << 16) | idx);

    t_scan_antenna_dtv.h_builder = t_g_tuner_atsc.h_sb_dig_air;
    //_tuner_setup_url_put_update_channel();
    //rest_event_notify("tv_settings/channels/channel_scan_state", 0, "");//scan start

    i4_ret = c_sb_start_scan(t_g_tuner_atsc.h_sb_dig_air,
                                 &t_atsc_scan_data,
                                 &t_scan_antenna_dtv,
                                 _tuner_setup_scan_new_nfy_fct,
                                 &e_cond);

    if (i4_ret != SBR_OK)
    {
        TUNER_LOG_E("Can't start scan,i4_ret:%d e_cond:%d\r\n",i4_ret,e_cond);
        _on_start_scan_fail();
        return TSP_FAIL;
    }

    return 0;
}



static INT32 _tuner_setup_scan_cable_atv(UINT16 idx)
{
    SB_COND_T           e_cond      = {0};
    //UINT16              idx         = 0;
    UINT32              i4_ret      = 0;

    /* Start scan the ATV channels*/
    SB_NTSC_SCAN_DATA_T t_ntsc_scan_data;

    TUNER_LOG_I("Scan Mode: NTSC/CABLE\r\n");

    /* udpate the sink name to builder */
    _tuner_atsc_update_sb_snk_name(t_g_tuner_atsc.h_sb_anlg_cable,
                                         _tuner_get_crnt_svctx());


    /* start scan */
    c_memset(&t_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));

#ifdef  APP_FUSION_TV_SUPPORT
    t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_CAB_FREQ_PLAN_STD|SB_NTSC_CAB_FREQ_PLAN_IRC;
#else
    t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_CAB_FREQ_PLAN_AUTO;
#endif

    t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_SINGLE_RF_CHANNEL;
    t_ntsc_scan_data.ui2_start_idx = idx;
    t_ntsc_scan_data.ui2_end_idx   = idx;

    t_scan_cable_atv.h_builder = t_g_tuner_atsc.h_sb_anlg_cable;

    i4_ret = c_sb_start_scan(t_g_tuner_atsc.h_sb_anlg_cable,
                                 &t_ntsc_scan_data,
                                 &t_scan_cable_atv,
                                 _tuner_setup_scan_new_nfy_fct,
                                 &e_cond);

    if (i4_ret != SBR_OK)
    {
        TUNER_LOG_E("Can't start scan,i4_ret:%d e_cond:%d\r\n",i4_ret,e_cond);
        _on_start_scan_fail();
        return TSP_FAIL;
    }

    return 0;
}



static INT32 _tuner_setup_scan_cable_dtv(UINT16 idx)
{
    SB_COND_T           e_cond      = {0};
    //UINT16              idx         = 0;
    UINT32              i4_ret      = 0;

    /* Start scan the DTV */
    SB_CQAM_SCAN_DATA_T t_cqam_scan_data;
    UINT8               ui1_freq;
    UINT32              ui4_mod;

    TUNER_LOG_I("Scan Mode: ATSC/CABLE\r\n");

    i4_ret = _get_freq_plan(&ui1_freq, &ui4_mod);
    if (i4_ret != TSP_OK)
    {
        TUNER_LOG_E("Wrong frequency plan mode,i4_ret:%d\r\n",i4_ret);
        _on_start_scan_fail();
        return TSP_FAIL;
    }

    TUNER_LOG_I("Use CQAM mode to start scan\r\n");
    c_memset(&t_cqam_scan_data, 0, sizeof(SB_CQAM_SCAN_DATA_T));
    t_cqam_scan_data.e_scan_type   = SB_ATSC_SCAN_TYPE_SINGLE_RF_CHANNEL;
    t_cqam_scan_data.ui4_scan_info = ((idx  << 16) | idx);
    t_cqam_scan_data.ui1_freq_plan = ui1_freq;
    t_cqam_scan_data.ui4_mod_mask  = ui4_mod;

    t_scan_cable_dtv.h_builder = t_g_tuner_atsc.h_sb_dig_cable;
    //_tuner_setup_url_put_update_channel();
    //rest_event_notify("tv_settings/channels/channel_scan_state", 0, "");//scan start

    i4_ret = c_sb_start_scan(t_g_tuner_atsc.h_sb_dig_cable,
                                 &t_cqam_scan_data,
                                 &t_scan_cable_dtv,
                                 _tuner_setup_scan_new_nfy_fct,
                                 &e_cond);

    if (i4_ret != SBR_OK)
    {
        TUNER_LOG_E("Can't start scan,i4_ret:%d,e_cond:%d\r\n",i4_ret,e_cond);
        _on_start_scan_fail();
        return TSP_FAIL;
    }


    return 0;
}


INT32 _tuner_setup_sort_channels(VOID)
{

    INT16       ocl_num = 0;
    INT32       i4_idx = 0,i4_ret = 0;
    //INT32       i4_result = SVLR_FAIL;
    SVL_REC_T   t_svl_rec;
    OCL_SVL_REC_T   t_ocl_svl_rec;
    HANDLE_T    h_tsl     = NULL_HANDLE;
    TSL_REC_T   t_tsl_rec = {0};
    UINT32      ui4_ver_id = SVL_NULL_VER_ID;

    ant_dtv_list_num    =   0;
    ant_atv_list_num    =   0;
    cab_dtv_list_num    =   0;
    cab_atv_list_num    =   0;

    ocl_num = ocl_get_ocl_num();
    TUNER_LOG_I("[tuner scan] %d ocl_num=%d \n",__LINE__,ocl_num);
    for(;i4_idx<ocl_num;i4_idx++)
    {
        c_memset(&t_svl_rec, 0, sizeof(t_svl_rec));
        c_memset(&t_ocl_svl_rec, 0, sizeof(t_ocl_svl_rec));
        i4_ret = ocl_get_ocl_svl_by_index(i4_idx,&t_svl_rec,&t_ocl_svl_rec);
        if (OCLR_OK != i4_ret)
        {
            TUNER_LOG_I("[tuner scan] %s:%d get ocl fail,i4_idx=%d\n",__FUNCTION__,__LINE__,i4_idx);
            return OCLR_FAIL;
        }

        //DBG_LOG_PRINT(("%s ocl_idx[%d] ui2_svl_rec_id:%d,e_brdcst_type:%d\n",__FUNCTION__,i4_idx,t_svl_rec.ui2_svl_rec_id,t_svl_rec.uheader.t_rec_hdr.e_brdcst_type));

        if(t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id == ATSC_TRSTRL_TSL_ID)
        {
            h_tsl = t_g_tuner_common.h_tsl_air;
        }
        else if(t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id == ATSC_CABLE_TSL_ID)
        {
            h_tsl = t_g_tuner_common.h_tsl_cable;
        }
        else
        {
            TUNER_LOG_E("[tuner scan] Err\n");
        }

        /* get the tsl record by tsl record id */
        i4_ret =  c_tsl_get_rec(h_tsl,
                            t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                            &t_tsl_rec,
                            &ui4_ver_id);

        TUNER_LOG_I("[tuner scan] %s ocl_idx[%d] ui2_svl_rec_id:%d,e_brdcst_type:%d e_bcst_medium:%d\n",__FUNCTION__,i4_idx,\
            t_svl_rec.ui2_svl_rec_id,t_svl_rec.uheader.t_rec_hdr.e_brdcst_type,t_tsl_rec.uheader.t_desc.e_bcst_medium);

        if(BRDCST_MEDIUM_DIG_TERRESTRIAL == t_tsl_rec.uheader.t_desc.e_bcst_medium)
        {
            UINT32 tmp_val = ((t_svl_rec.ui2_svl_rec_id >= 1) && (t_svl_rec.ui2_svl_rec_id <=68)) ? t_svl_rec.ui2_svl_rec_id : t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id;
            TUNER_LOG_I("   [tuner scan] air_dig_id=%d\n",tmp_val);
            ant_dtv_list[ant_dtv_list_num] = tmp_val;
            ant_dtv_list_num++;
        }
        else if(BRDCST_MEDIUM_ANA_TERRESTRIAL == t_tsl_rec.uheader.t_desc.e_bcst_medium)
        {
            UINT32 tmp_val = ((t_svl_rec.ui2_svl_rec_id >= 1) && (t_svl_rec.ui2_svl_rec_id <=68)) ? t_svl_rec.ui2_svl_rec_id : t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id;
            TUNER_LOG_I("   [tuner scan] air_ana_id=%d\n",tmp_val);
            ant_atv_list[ant_atv_list_num] = tmp_val;
            ant_atv_list_num++;
        }
        else if(BRDCST_MEDIUM_DIG_CABLE == t_tsl_rec.uheader.t_desc.e_bcst_medium)
        {
            UINT32 tmp_val = ((t_svl_rec.ui2_svl_rec_id >= 1) && (t_svl_rec.ui2_svl_rec_id <=135)) ? t_svl_rec.ui2_svl_rec_id : t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id;
            TUNER_LOG_I("   [tuner scan] cable_dig_id=%d\n",tmp_val);
            cab_dtv_list[cab_dtv_list_num] = tmp_val;
            cab_dtv_list_num++;
        }
        else if(BRDCST_MEDIUM_ANA_CABLE == t_tsl_rec.uheader.t_desc.e_bcst_medium)
        {
            UINT32 tmp_val = ((t_svl_rec.ui2_svl_rec_id >= 1) && (t_svl_rec.ui2_svl_rec_id <=135)) ? t_svl_rec.ui2_svl_rec_id : t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id;
            TUNER_LOG_I("   [tuner scan] cable_ana_id=%d\n",tmp_val);
            cab_atv_list[cab_atv_list_num] = tmp_val;
            cab_atv_list_num++;
        }


    }
    /*
    int j = 0;
    DBG_LOG_PRINT(("ant_dtv_list:\n"));
    for(j=0;j<ant_dtv_list_num;j++)
    {
        DBG_LOG_PRINT(("        %d\n",ant_dtv_list[j]));
    }

    DBG_LOG_PRINT(("ant_atv_list:\n"));
    for(j=0;j<ant_atv_list_num;j++)
    {
        DBG_LOG_PRINT(("        %d\n",ant_atv_list[j]));
    }

    DBG_LOG_PRINT(("cab_dtv_list:\n"));
    for(j=0;j<cab_dtv_list_num;j++)
    {
        DBG_LOG_PRINT(("        %d\n",cab_dtv_list[j]));
    }

    DBG_LOG_PRINT(("cab_atv_list:\n"));
    for(j=0;j<cab_atv_list_num;j++)
    {
        DBG_LOG_PRINT(("        %d\n",cab_atv_list[j]));
    }
    */
    return i4_ret;

}


/*
    check the CH wether in ch+list or not

    return: TRUE    in
            FALSE   out

*/
BOOL _tuner_check_phy_CH(HANDLE_T builder,UINT16 CH_num)
{
    UINT16 count = 0;
    if(builder == t_g_tuner_atsc.h_sb_dig_air)
    {
        //DBG_LOG_PRINT(("ant_dtv_list:\n"));
        for(count=0;count<ant_dtv_list_num;count++)
        {
            //DBG_LOG_PRINT(("        %d\n",ant_dtv_list[count]+1));
            if(CH_num == (ant_dtv_list[count]))
                return TRUE;
        }
    }
    else if(builder == t_g_tuner_atsc.h_sb_dig_cable)
    {
        //DBG_LOG_PRINT(("cab_dtv_list:\n"));
        for(count=0;count<cab_dtv_list_num;count++)
        {
            //DBG_LOG_PRINT(("        %d\n",cab_dtv_list[count]));
            if(CH_num == (cab_dtv_list[count]))
                return TRUE;
        }
    }
    else if(builder == t_g_tuner_atsc.h_sb_anlg_air)
    {
        //DBG_LOG_PRINT(("ant_atv_list:\n"));
        for(count=0;count<ant_atv_list_num;count++)
        {
            //DBG_LOG_PRINT(("        %d\n",ant_atv_list[count]+1));
            if(CH_num == (ant_atv_list[count]+1))
                return TRUE;
        }
    }
    else if(builder == t_g_tuner_atsc.h_sb_anlg_cable)
    {
        //DBG_LOG_PRINT(("cab_atv_list:\n"));
        for(count=0;count<cab_atv_list_num;count++)
        {
            //DBG_LOG_PRINT(("        %d\n",cab_atv_list[count]));
            if(CH_num == (cab_atv_list[count]))
                return TRUE;
        }
    }

    return FALSE;
}


static INT32 _tuner_setup_warning_msg_tg_init(VOID)
{

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
           &t_g_wdk_warning,
           &t_g_h_g_wdk_warning));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
           &t_g_wdk_toast_box_settings,
           &t_g_h_g_wdk_toast_box_settings));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
           &t_g_wdk_gradient_top,
           &t_g_h_g_wdk_gradient_top));
    return TSP_OK;
}


static INT32 _tuner_setup_warning_msg_dialog_frame_init(VOID)
{
    //h_warning_msg_dialog_frame
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;

    SET_RECT_BY_SIZE(&t_rect,
                     WARNING_MSG_VIEW_BASE_FRAME_X,
                     WARNING_MSG_VIEW_BASE_FRAME_Y,
                     WARNING_MSG_VIEW_BASE_FRAME_W,
                     WARNING_MSG_VIEW_BASE_FRAME_H);

    i4_ret = c_wgl_create_widget(tg_scan_view.h_frm,
                             HT_WGL_WIDGET_FRAME,
                             WGL_CONTENT_FRAME_DEF,
                             WGL_BORDER_NULL,
                             &t_rect,
                             NULL,
                             255,
                             (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK),
                             NULL,
                             &(tg_scan_view.h_warning_msg_dialog_frame));
    RET_ON_ERR(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type                   = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_g_h_g_wdk_gradient_top;
    t_img_info.u_img_data.t_standard.t_disable   = t_g_h_g_wdk_gradient_top;
    t_img_info.u_img_data.t_standard.t_highlight = t_g_h_g_wdk_gradient_top;
    i4_ret = c_wgl_do_cmd(
                    tg_scan_view.h_warning_msg_dialog_frame,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_FG),
                    WGL_PACK(&t_img_info));
    RET_ON_ERR (i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_dialog_frame, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return TSP_OK;


}



static INT32 _tuner_setup_warning_msg_text_init(VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    //UTF16_T                     w2s_tmp_str[128] = {0};
    //UTF16_T                     w2s_str[128] = {0};
    //char*                       w2s_num_str;
    //char*                       s_str;

    SET_RECT_BY_SIZE(&t_rect,
                     WARNING_MSG_VIEW_TXT_MSG_X,
                     WARNING_MSG_VIEW_TXT_MSG_Y,
                     WARNING_MSG_VIEW_TXT_MSG_W,
                     WARNING_MSG_VIEW_TXT_MSG_H);

    i4_ret = c_wgl_create_widget(tg_scan_view.h_warning_msg_dialog_frame,
    //i4_ret = c_wgl_create_widget(tg_scan_view.h_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_WGT_SPF_START |
                                         WGL_STL_TEXT_MAX_128 |
                                         WGL_STL_TEXT_SMART_CUT |
                                         WGL_STL_GL_NO_IMG_UI |
                                         WGL_STL_GL_NO_BK),
                                 &tg_scan_view,
                                 &(tg_scan_view.h_warning_msg_text));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_scan_view.h_warning_msg_text,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_CENTER_CENTER),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = TOAST_VIEW_HEADLINE_2_FONT_SIZE;

    i4_ret = c_wgl_do_cmd (tg_scan_view.h_warning_msg_text,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Color
    if (a_is_oled_compensation_support())
    {
        t_g_msg_txt_clr = t_g_msg_txt_clr_oled;
    }
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type                           = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_msg_txt_clr;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_msg_txt_clr;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_msg_txt_clr;

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_warning_msg_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);


    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(tg_scan_view.h_warning_msg_text,
        WGL_CMD_TEXT_SET_ALIGN,
        WGL_PACK(WGL_AS_CENTER_CENTER),
        NULL);
    RET_ON_ERR(i4_ret);


    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_text, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return TSP_OK;
}



static INT32 _tuner_setup_warning_icon_init(VOID)
{

    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;


    SET_RECT_BY_SIZE(&t_rect,
                     WARNING_MSG_VIEW_ICON_WARNING_X,
                     WARNING_MSG_VIEW_ICON_WARNING_Y,
                     WARNING_MSG_VIEW_ICON_WARNING_W,
                     WARNING_MSG_VIEW_ICON_WARNING_H);

    i4_ret = c_wgl_create_widget(tg_scan_view.h_warning_msg_dialog_frame,
        //i4_ret = c_wgl_create_widget(tg_scan_view.h_frm,
                                    HT_WGL_WIDGET_ICON,
                                    WGL_CONTENT_ICON_DEF,
                                    WGL_BORDER_NULL,
                                    &t_rect,
                                    NULL,
                                    255,
                                    (VOID*)(WGL_STL_GL_NO_BK),
                                    &tg_scan_view,
                                    &tg_scan_view.h_warning_msg_icon);
    RET_ON_ERR (i4_ret);


    /* set icon  buffer */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_g_h_g_wdk_warning;
    t_img_info.u_img_data.t_standard.t_disable   = t_g_h_g_wdk_warning;
    t_img_info.u_img_data.t_standard.t_highlight = t_g_h_g_wdk_warning;
    i4_ret = c_wgl_do_cmd(
                    tg_scan_view.h_warning_msg_icon,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_FG),
                    WGL_PACK(&t_img_info));
    RET_ON_ERR (i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(
                     tg_scan_view.h_warning_msg_icon,
                     WGL_CMD_ICON_SET_ALIGN,
                     WGL_PACK(WGL_AS_CENTER_CENTER),
                     NULL);
    RET_ON_ERR (i4_ret);


     /* make icon visible */
    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_icon, WGL_SW_HIDE);
    RET_ON_ERR (i4_ret);

    return TSP_OK;
}


static INT32 _tuner_setup_warning_msgbox_init(VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;


    SET_RECT_BY_SIZE(&t_rect,
                     WARNING_MSG_VIEW_ICON_MSGBOX_X,
                     WARNING_MSG_VIEW_ICON_MSGBOX_Y,
                     WARNING_MSG_VIEW_ICON_MSGBOX_W,
                     WARNING_MSG_VIEW_ICON_MSGBOX_H);

    i4_ret = c_wgl_create_widget(tg_scan_view.h_warning_msg_dialog_frame,
        //i4_ret = c_wgl_create_widget(tg_scan_view.h_frm,
                                    HT_WGL_WIDGET_ICON,
                                    WGL_CONTENT_ICON_DEF,
                                    WGL_BORDER_NULL,
                                    &t_rect,
                                    NULL,
                                    255,
                                    (VOID*)(WGL_STL_GL_NO_BK),
                                    &tg_scan_view,
                                    &tg_scan_view.h_warning_msg_msgbox);
    RET_ON_ERR (i4_ret);


    /* set icon  buffer */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_g_h_g_wdk_toast_box_settings;
    t_img_info.u_img_data.t_standard.t_disable   = t_g_h_g_wdk_toast_box_settings;
    t_img_info.u_img_data.t_standard.t_highlight = t_g_h_g_wdk_toast_box_settings;
    i4_ret = c_wgl_do_cmd(
                    tg_scan_view.h_warning_msg_msgbox,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_FG),
                    WGL_PACK(&t_img_info));
    RET_ON_ERR (i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(
                     tg_scan_view.h_warning_msg_msgbox,
                     WGL_CMD_ICON_SET_ALIGN,
                     WGL_PACK(WGL_AS_CENTER_CENTER),
                     NULL);
    RET_ON_ERR (i4_ret);


     /* make icon visible */
    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_msgbox, WGL_SW_HIDE);
    RET_ON_ERR (i4_ret);

    return TSP_OK;
}

static INT32 _tuner_setup_warning_widget_init(VOID)
{
    DBG_LOG_PRINT(("[tuner_setup init] _tuner_setup_warning_widget_init AAAAAAAAAAAAAAAAAAAAAAAAA\n"));
    _tuner_setup_warning_msg_tg_init();

    _tuner_setup_warning_msg_dialog_frame_init();

    _tuner_setup_warning_msg_text_init();
    _tuner_setup_warning_msgbox_init();
    _tuner_setup_warning_icon_init();

    return 0;
}


VOID _tuner_setup_view_set_process_visibility (WGL_SW_CMD_T val)
{

    c_wgl_set_visibility(tg_scan_view.h_cd_text, val);

    c_wgl_set_visibility(tg_scan_view.h_bar, val);

    c_wgl_set_visibility(tg_scan_view.h_da_text, val);

    c_wgl_set_visibility(tg_scan_view.h_per_text, val);

    c_wgl_set_visibility(tg_scan_view.h_icon, val);

}

INT32 tuner_setup_warning_show(UTF16_T* w2s_str)
{
    DBG_LOG_PRINT(("[tuner] %s %d show?:%d\n",__FUNCTION__,__LINE__,a_tuner_setup_enable_get()));

    if(!a_tuner_setup_enable_get())
        return NAVR_NO_ACTION;

    INT32                       i4_ret;

    i4_ret = c_wgl_do_cmd(tg_scan_view.h_warning_msg_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_str)));
    RET_ON_ERR(i4_ret);

    //otehr widgets should be hide
    _tuner_setup_view_set_process_visibility(WGL_SW_HIDE);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_text, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_msgbox, WGL_SW_NORMAL);
    RET_ON_ERR (i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_icon, WGL_SW_NORMAL);
    RET_ON_ERR (i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_frm, WGL_SW_NORMAL);
    RET_ON_ERR (i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_dialog_frame, WGL_SW_NORMAL);
    RET_ON_ERR (i4_ret);

    c_wgl_repaint(tg_scan_view.h_warning_msg_dialog_frame,NULL,TRUE);

    return TSP_OK;
}

INT32 tuner_setup_warning_hide(VOID)
{
    DBG_LOG_PRINT(("[tuner] %s %d \n",__FUNCTION__,__LINE__));

    INT32                       i4_ret;

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_text, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_msgbox, WGL_SW_HIDE);
    RET_ON_ERR (i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_icon, WGL_SW_HIDE);
    RET_ON_ERR (i4_ret);


    i4_ret = c_wgl_set_visibility(tg_scan_view.h_warning_msg_dialog_frame, WGL_SW_HIDE);
    RET_ON_ERR (i4_ret);

    i4_ret = c_wgl_set_visibility(tg_scan_view.h_frm, WGL_SW_HIDE);
    RET_ON_ERR (i4_ret);

    c_wgl_repaint(tg_scan_view.h_frm,NULL,TRUE);
    return TSP_OK;
}


VOID tuner_setup_view_auto_test(VOID)
{
    DBG_LOG_PRINT(("[tuner_setup] start\n"));
    nav_grab_activation(NAV_COMP_ID_TUNER_SETUP);
    nav_request_context_switch(_tuner_setup_view_show_scan,NULL,NULL,NULL);

}

static VOID _tuner_setup_view_change_source_to_tv(
    VOID*                              pv_this,
    VOID*                              pv_unused2,
    VOID*                              pv_unused3)
{
    nav_ipts_switch_src(NAV_IPTS_SMS_TO_TV, TV_WIN_ID_MAIN, 0);
}

INT32 a_tuner_setup_view_change_source_to_tv(VOID)
{
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    //CHAR            s_active_app[32] = {0};
    UINT8           ui1_input_id = 0;
    ISL_REC_T       t_isl_rec;
    INT32           i4_ret = MENUR_OK;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);
    if((INP_SRC_TYPE_TV == t_isl_rec.e_src_type))
    {
        DBG_LOG_PRINT(("%s_%d current source is tv \n ",__FUNCTION__,__LINE__));
        return MENUR_OK;
    }

    /* if scan next,may not change to TV completely in nav thread and scan already starts,so change to TV first
    nav_request_context_switch(_tuner_setup_view_change_source_to_tv,
                               NULL,
                               NULL,
                               NULL);*/

    if (msg_convert_custom_netflix_active() || msg_convert_custom_cobalt_alive())
    {
        DBG_LOG_PRINT(("[tuner scan][%s %d] - stop native app\n",__FUNCTION__,__LINE__));
        msg_convert_custom_resume_nav();
        int nCount = 0;
        //wait netflix exit. netflix will be exit in 8s, otherwise it will be killed.
        while ((msg_convert_custom_netflix_active() || msg_convert_custom_cobalt_alive()) && nCount <= 50)
        {
            DBG_LOG_PRINT(("[tuner scan][%s %d] - delay 0.1s, nCount: %d\n",__FUNCTION__,__LINE__, nCount));
            c_thread_delay(100);
            nCount++;
        }
    }

    nav_ipts_switch_src(NAV_IPTS_SMS_TO_TV, TV_WIN_ID_MAIN, 0);

    rest_event_notify_current_input("tuner");

    return i4_ret;
}


