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
 * $RCSfile: nav_fac_dialog.c,v $
 * $Revision: #3 $
 * $Date: 2015/07/23 $
 * $Author: lin.xu $
 * $CCRevision$
 * $SWAuthor$
 * $MD5HEX$
 * Description:
 *---------------------------------------------------------------------------*/
#include <stdlib.h>		//mind 20160913
#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "u_pcl.h"//jeff 20090121 add
#include "u_gl.h"
#include "u_device_type.h"

//#include "c_os.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_pcl.h"
#include "c_scc.h"
#include "c_common.h"
#include "c_handle_grp.h"
#include "c_version.h"


#include "nav/a_navigator.h"
#include "nav/banner2/banner_common.h"//jeff 20090122 add
#include "../../../nav/burning_mode/burning_mode.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "res/app_util/config/a_cfg_custom.h" //APP_FAC_MENU
#include "app_util/config/acfg_cust_factory_vizio.h"


//#include "app_util/config/_acfg.h"    //Soar 20080924
#include "app_util/a_isl.h"
#include "app_util/a_ui.h"
//#include "app_util/a_network.h"	// Ben 20151223

//#include "wizard/a_wzd.h" //jeff 20090209 add
#include "wizard_anim/wzd.h"		//mind 20160512
#include "wizard_anim/a_wzd.h"

#include "INX_fac_urc.h"
//#include "res/nav/factory/a_factory.h"
#include "INX_factory/a_INX_factory.h"
#include "INX_factory/INX_d_factory.h"

#include "INX_factory/INX_fac_menu/INX_fac.h"
//#include "res/nav/factory/fac_mlm.h"
#include "INX_factory/INX_fac_mlm.h"
#include "INX_factory/INX_fac_ch_table/INX_fac_load_ch.h"


#if defined(APP_NAV_COMP_ID_CSM)
#include "res/nav/psm/_psm.h" //Denny 2009/10/29 unmark  //jeff 20080106 add  //ke_test_fac
#endif

#include "mmp/a_mmp.h" //Denny 2011/03/17 add
#include "app_util/rmv_dev/a_rmv_dev.h" //Denny 2011/03/17 add
#include "app_util/a_cfg.h"	//kyo_20120202
#include "res/app_util/app_tv/a_tv_custom.h"
#include "menu2/menu_page.h"

#include "app_util/a_network.h"
#include "res/app_util/network/network_custom.h"

#include "c_rm.h"  //ke_vizio_20131218 add
#include "res/app_util/config/acfg_custom.h"
#ifdef APP_C4TV_SUPPORT
#include "res/app_util/config/acfg_cust_misc.h"		//mind 20160825
#endif

#include "menu2/menu_common/menu_common.h"  // Ben 10280130
#include "INX_factory/INX_fac_img.h"

#ifdef APP_BLUETOOTH_SUPPORT
// test, zl #include "mtk_bt_service_gap_wrapper.h"
#endif

extern VOID burning_mode_under_ext_rc_control(
                    UINT16                       ui2_idx
                    );
extern BOOL cvt_fac_is_burning_mode_runing();
extern INT32 cvt_fac_burnning_mode_run(INT32 cmd_value);
extern BOOL cvt_fac_is_AT_mode(void);
extern INT32 cvt_fac_keypad_test(
                    UINT32      ui4_keystatus,
                    UINT32*     pt_ui4_keycode
                    );

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
//#define     SUPPORT_AUTO_COLOR_KEY  //ke_vizio_20170517 cancel

#ifdef SUPPORT_AUTO_COLOR_KEY
static HANDLE_T     h_g_fac_dialog_svctx = NULL_HANDLE;
#endif

#ifndef APP_CFG_RECID_DCR
#define APP_CFG_RECID_DCR                   (APP_CFG_RECID_VID_CUSTOM_BASE + 26)
#endif

#ifndef ACFG_AUD_VOL_DEF
#define ACFG_AUD_VOL_DEF                    ( 25)
#define ACFG_AUD_VOL_MIN                    (  0)
#define ACFG_AUD_VOL_MAX                    (100)
#endif

typedef enum
{
    NAV_FAC_DIALOG_ID_NULL = 0,
    NAV_FAC_DIALOG_ID_TEST_MODE_ON,
    NAV_FAC_DIALOG_ID_ENTER_FM,
    NAV_FAC_DIALOG_ID_LEAVE_FM,
    NAV_FAC_DIALOG_ID_SET_ALL_PM,
    NAV_FAC_DIALOG_ID_SET_TO_FM,
    NAV_FAC_DIALOG_ID_BACKLIGHT_50P,
    NAV_FAC_DIALOG_ID_BACKLIGHT_100P,
    NAV_FAC_DIALOG_ID_BRIGHTNESS_50P,
    NAV_FAC_DIALOG_ID_BRIGHTNESS_100P,
    NAV_FAC_DIALOG_ID_CONTRAST_50P,
    NAV_FAC_DIALOG_ID_CONTRAST_100P,
    NAV_FAC_DIALOG_ID_PIC_MODE_USER,
    NAV_FAC_DIALOG_ID_PIC_MODE_SPORT,
    NAV_FAC_DIALOG_ID_PIC_MODE_CINEMA,
    NAV_FAC_DIALOG_ID_WB_NORMAL,
    NAV_FAC_DIALOG_ID_WB_WARM,
    NAV_FAC_DIALOG_ID_WB_COOL,
    NAV_FAC_DIALOG_ID_VIRGIN_MODE,
    NAV_FAC_DIALOG_ID_ORT_ON,
    NAV_FAC_DIALOG_ID_ORT_OFF,
    NAV_FAC_DIALOG_ID_SM_STEREO,
    NAV_FAC_DIALOG_ID_AVL_OFF,
    NAV_FAC_DIALOG_ID_BALANCE_RIGHT,
    NAV_FAC_DIALOG_ID_BALANCE_LEFT,
    NAV_FAC_DIALOG_ID_VOLUME_50P,
    NAV_FAC_DIALOG_ID_VOLUME_100P,
    NAV_FAC_DIALOG_ID_AUTO_DONE,
    NAV_FAC_DIALOG_ID_AUTO_FAIL,
    NAV_FAC_DIALOG_ID_EDID_WRITE_EN,
    NAV_FAC_DIALOG_ID_EDID_WRITE_DIS,
    NAV_FAC_DIALOG_ID_VGA_SWITCH,
    NAV_FAC_DIALOG_ID_AV_RESET,
    NAV_FAC_DIALOG_ID_SPDIF_OFF,
    NAV_FAC_DIALOG_ID_SPDIF_DOLBY,
    NAV_FAC_DIALOG_ID_SPDIF_PCM,
    NAV_FAC_DIALOG_ID_DCR_ON,
    NAV_FAC_DIALOG_ID_DCR_OFF,
    NAV_FAC_DIALOG_ID_TV,//jeff 20090119 add
    NAV_FAC_DIALOG_ID_EDID_ON,
    NAV_FAC_DIALOG_ID_PATTEN_ON,
    NAV_FAC_DIALOG_ID_AUTO_COFIG,
    NAV_FAC_DIALOG_ID_USB,
    NAV_FAC_DIALOG_ID_LOGO_LED,
    //Denny 2011/03/17 add -start
    NAV_FAC_DIALOG_ID_VOL_BUZ,
    NAV_FAC_DIALOG_ID_PIC_STANDARD,
    NAV_FAC_DIALOG_ID_PIC_MOVIE,
    NAV_FAC_DIALOG_ID_PIC_GAME,
    NAV_FAC_DIALOG_ID_PIC_VIVID,
    NAV_FAC_DIALOG_ID_PIC_FOOTBALL,
    NAV_FAC_DIALOG_ID_PIC_GOLF,
    NAV_FAC_DIALOG_ID_PIC_BASKETBALL,
    NAV_FAC_DIALOG_ID_PIC_BASEBALL,
    NAV_FAC_DIALOG_ID_PIC_CUSTOM,
#if 1	//kyo_20120202
	NAV_FAC_DIALOG_ID_ARC_ON,
	NAV_FAC_DIALOG_ID_ARC_OFF,
	NAV_FAC_DIALOG_ID_LSR_ON,
	NAV_FAC_DIALOG_ID_LSR_OFF,
	NAV_FAC_DIALOG_ID_3D2D_ON,
	NAV_FAC_DIALOG_ID_3D2D_OFF,
	NAV_FAC_DIALOG_ID_NO_SUPPORT,
#endif

    /* For keypad test */
    NAV_FAC_DIALOG_ID_CH_UP,
    NAV_FAC_DIALOG_ID_CH_DOWN,
    NAV_FAC_DIALOG_ID_POWER,
    NAV_FAC_DIALOG_ID_VOL_UP,
    NAV_FAC_DIALOG_ID_VOL_DOWN,
    NAV_FAC_DIALOG_ID_SRC,
    NAV_FAC_DIALOG_ID_MENU,

    #ifdef APP_TTS_SUPPORT
    NAV_FAC_DIALOG_ID_TTS,
    #endif
	//Denny 2011/03/17 add -end

    #ifdef APP_INX_DFT_WIFI_AUTO_DETECTION //ke_vizio_20170523
    NAV_FAC_DIALOG_ID_WIFI_SSID,
    NAV_FAC_DIALOG_ID_WIFI_STATUS,
    #endif
}   NAV_FAC_DIALOG_ID_T;

typedef struct
{
    /* Widgets */
    HANDLE_T        h_canvas;
    HANDLE_T        h_dialog;
    HANDLE_T        h_hide_timer;
    HANDLE_T        h_auto_color_timer;
    UINT32             ui4_timer_delay;
    NAV_FAC_DIALOG_ID_T e_dialog_id;

    #ifdef APP_DFT_LSR_TEST  //ke_vizio_20131220 add
    HANDLE_T        h_LSR_timer;
    BOOL            b_LSR_time_start;
    #endif
}NAV_FAC_DIALOG_T;

typedef struct _NAV_FAC_DIALOG_VIEW_T
{
    /* Widgets */
    HANDLE_T        h_frm_simple_dialog;   /* the main frame of the S-DLG */
    HANDLE_T        h_txt_txtinfo;         /* the text box */
    HANDLE_T        h_txt_txtinfo_2;         /* the text box *///jeff 20080119 add
    /* Properties */
    UTF16_T*     pw2s_txtinfo;         /* the pointer of UTF16 txtinfo */
    BOOL         b_answer;
    /* Template Images */
    WGL_HIMG_TPL_T  h_ui_simple_dialog_bk0;             /* Simple Dialog BK */
} NAV_FAC_DIALOG_VIEW_T;

typedef struct  _NAV_FAC_DIALOG_SHOW_INIT_T
{
    HANDLE_T                     h_parent;
    wgl_widget_proc_fct          pf_wdgt_proc;
    UINT16                       ui2_txt_align_type;
    GL_RECT_T*                   pt_rect;            /* For Information style only */
    GL_POINT_T*                  pt_begin_offset;    /* For Small/Medium/Big style only */
    BOOL                         b_default_answer;   /* For Small/Medium/Big style only */
    ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct; /* For Small/Medium/Big style only */
    ui_simple_dialog_no_cb_fct   pf_ui_simple_dialog_no_cb_fct;  /* For Small/Medium/Big style only */
}  NAV_FAC_DIALOG_SHOW_INIT_T;

#define _TEXT(_txt)    ((UTF16_T*)L##_txt)

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_FAC_DIALOG_T t_g_nav_fac_dialog   = {0};

static NAV_FAC_DIALOG_VIEW_T   t_g_nav_fac_dialog_view     = {0};  //ke_vizio_20141118 add
static NAV_FAC_DIALOG_SHOW_INIT_T     t_g_nav_fac_dialog_init = {0};  //ke_vizio_20141118 add


#ifdef SUPPORT_AUTO_COLOR_KEY
static UINT32  ui4_auto_start_time  = 0;
#endif
BOOL b_nav_fac_edid_write_en = FALSE;
//#if 1 //jeff 20080106 add
BOOL b_nav_fac_blk = FALSE;
BOOL b_nav_fac_spdif_on = FALSE;
BOOL B_nav_fac_buzz_flag = FALSE;
BOOL B_nav_fac_BI_flag = FALSE;//jeff 20090407 add
//#endif
/* Transparant */
GL_COLOR_T t_g_nav_fac_color_transp            = { 0,   {   0 }, {   0 }, {   0 }};
/* txt fg */
GL_COLOR_T t_g_nav_fac_dialog_color_fg1_txt           = { 255, { 255 }, { 255 }, { 255 }};

#ifdef APP_INX_DFT_WIFI_AUTO_DETECTION
static BOOL b_INX_wifi_connect_status = FALSE;
#endif

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_hide_timer_start(
    UINT32    ui4_time);

static INT32 _nav_fac_dialog_hide_timer_stop(
    VOID);

static VOID _nav_fac_dialog_hide_timer_nfy (
    HANDLE_T  h_timer,
    VOID*     pv_tag);

static VOID _nav_fac_dialog_timeout_to_hide(
    VOID*     pv_tag,
    VOID*     pv_tag2,
    VOID*     pv_tag3);

#ifdef SUPPORT_AUTO_COLOR_KEY
static INT32 _nav_fac_dialog_default_msg_proc(
    HANDLE_T            h_widget,
    UINT32              ui4_msg,
    VOID*               pv_param1,
    VOID*               pv_param2);
#endif


static VOID _nav_fac_volume_setting(INT32 i4_val);

static VOID _nav_fac_agc_setting(BOOL b_enable);

static VOID _nav_fac_blacklight_setting(INT32 i4_val);//jeff 20080106 modify

static VOID _nav_fac_picmode_setting(UINT16 ui2_idx);

static VOID _nav_fac_color_temp_setting(UINT16 ui2_idx);

#if 0
static VOID _nav_fac_dcr_setting(UINT16 ui2_idx);//jeff 20080106 add
#endif

static VOID _nav_fac_aud_mts_setting(UINT16 ui2_idx);
#ifdef SUPPORT_AUTO_COLOR_KEY
static VOID _nav_fac_dialog_auto_color_timeout(
    HANDLE_T                    h_timer,
    VOID*                       pv_tag         );
#endif

INT32 _nav_fac_dialog_prompt_msg_dialog(
                                            NAV_FAC_DIALOG_ID_T     e_dialog_id,
                                            UTF16_T*            pw2s_msg,
                                      wgl_widget_proc_fct pf_wdgt_proc);




static INT32 _nav_fac_dialog_prompt_msg_dialog_2(
    NAV_FAC_DIALOG_ID_T     e_dialog_id,
    UTF16_T*            pw2s_msg_1,
    UTF16_T*            pw2s_msg_2,
    wgl_widget_proc_fct pf_wdgt_proc
    );

extern INT32 menu_adjust_vplane(VOID);  //ke_20090123_add for clean warning

extern INT32 menu_select_crnt_or_first_channel(BOOL b_skip_fake); //Denny 2010/01/12 add

//extern CHAR* sys_cust_get_usb_upg_version(VOID);
extern CHAR* sys_cust_get_cust_serial(VOID);		//mind 20160811

extern INT32 a_sleep_timer_start(UINT32 ui4_time);	//<INX>James 20120321:Add auto shut-down at URC RST key

#ifdef APP_INX_DFT_URC_WIFI
extern INT32 nav_fac_urc_set_wifi(VOID);  //ke_vizio_20130912 add
#endif

#ifdef APP_DFT_LSR_TEST //ke_vizio_20131220 add
static INT32 _nav_fac_dialog_LSR_timer_start(VOID);
static INT32 _nav_fac_dialog_LSR_timer_stop(VOID);
static VOID _nav_fac_dialog_LSR_timer_nfy(HANDLE_T h_timer,VOID * pv_tag);
#endif

#ifdef APP_INX_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
static VOID _auto_detect_nw_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param);
#endif
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _nav_fac_dialog_image_init
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_image_init(NAV_FAC_DIALOG_VIEW_T*    pt_nav_fac_dialog)
{
    INT32 i4_ret;

    /* Background of simple_dialog */  //ke_vizio_20160912 modify
    i4_ret = INX_fac_img_create_urc_bk_img_tpl(&pt_nav_fac_dialog->h_ui_simple_dialog_bk0);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _nav_fac_dialog_create_frm
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32  _nav_fac_dialog_create_frm(NAV_FAC_DIALOG_VIEW_T*    pt_nav_fac_dialog_show,
                                          wgl_widget_proc_fct pf_wdgt_proc,
                                          HANDLE_T            h_parent,
                                          GL_RECT_T*          pt_rect,
                                          GL_POINT_T*         pt_begin_offset)
{

    INT32             i4_ret;
    GL_RECT_T         t_rect;
    UINT32            ui4_style;
    WGL_IMG_INFO_T    t_img_info;
    GL_POINT_T        t_begin_offset;

    ui4_style = 0;

    if(pt_begin_offset == NULL)
    {
        t_begin_offset.i4_x = 0;
        t_begin_offset.i4_y = 0;
    }
    else
    {
        t_begin_offset = *pt_begin_offset;
    }
    /* If the pt_rect is specified, use this parameter */
    if(pt_rect == NULL)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         NAV_FAC_DIALOG_DEF_CONTENT_FRAME_X + t_begin_offset.i4_x - NAV_FAC_DIALOG_CONTENT_X_FRAME,
                         NAV_FAC_DIALOG_DEF_CONTENT_FRAME_Y + t_begin_offset.i4_y,
                         NAV_FAC_DIALOG_DEF_CONTENT_FRAME_W + NAV_FAC_DIALOG_INFO_TEXT_LEN,
                         NAV_FAC_DIALOG_DEF_CONTENT_FRAME_H);
    }
    else
    {
        t_rect = *pt_rect;
    }
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_nav_fac_dialog_show->h_frm_simple_dialog);
    if (i4_ret < 0)
    {
        return APP_UIR_WIDGET_CREATE_FAIL;
    }
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_nav_fac_dialog_show->h_ui_simple_dialog_bk0;
    t_img_info.u_img_data.t_standard.t_highlight = pt_nav_fac_dialog_show->h_ui_simple_dialog_bk0;
    t_img_info.u_img_data.t_standard.t_disable   = pt_nav_fac_dialog_show->h_ui_simple_dialog_bk0;
    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog_show->h_frm_simple_dialog,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_fac_dialog_create_txtinfo
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32  _nav_fac_dialog_create_txtinfo(NAV_FAC_DIALOG_VIEW_T*      pt_nav_fac_dialog,
                                              GL_RECT_T*               pt_rect,
                                              UINT16                   ui2_align_type)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    UINT16              ui2_align;

    ui4_style =  WGL_STL_GL_NO_IMG_UI
                |WGL_STL_TEXT_MULTILINE
                |WGL_STL_TEXT_MAX_512
                |WGL_STL_TEXT_MAX_DIS_10_LINE;

    /* Default alignment */
    if(ui2_align_type == 0)
    {
        ui2_align = WGL_AS_LEFT_TOP;
    }
    else
    {
        ui2_align = ui2_align_type;
    }

    /* If the pt_rect is specified, use this parameter */
    if(pt_rect == NULL)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SIMPLE_DIALOG_INFO_TEXT_INFO_X,
                         UI_SIMPLE_DIALOG_INFO_TEXT_INFO_Y,
                         UI_SIMPLE_DIALOG_INFO_TEXT_INFO_W+NAV_FAC_DIALOG_INFO_TEXT_LEN,
                         UI_SIMPLE_DIALOG_INFO_TEXT_INFO_H);
    }
    else
    {
        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         0,
                         pt_rect->i4_right - pt_rect->i4_left,
                         pt_rect->i4_bottom - pt_rect->i4_top);

    }

    i4_ret = c_wgl_create_widget(pt_nav_fac_dialog->h_frm_simple_dialog,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_nav_fac_dialog->h_txt_txtinfo);

    SET_RECT_BY_SIZE(&t_rect,
                        UI_SIMPLE_DIALOG_INFO_TEXT_INFO_X,
                        UI_SIMPLE_DIALOG_INFO_TEXT_INFO_Y+35,
                        UI_SIMPLE_DIALOG_INFO_TEXT_INFO_W,
                        UI_SIMPLE_DIALOG_INFO_TEXT_INFO_H);

    i4_ret = c_wgl_create_widget(pt_nav_fac_dialog->h_frm_simple_dialog,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_nav_fac_dialog->h_txt_txtinfo_2);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_BIG);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
	t_fnt_info.ui1_custom_size = NAV_FAC_DIALOG_CUSTOM_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog->h_txt_txtinfo,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);

    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog->h_txt_txtinfo_2,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_nav_fac_dialog_color_fg1_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_nav_fac_dialog_color_fg1_txt;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_nav_fac_dialog_color_fg1_txt;
    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog->h_txt_txtinfo_2,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_nav_fac_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_nav_fac_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_nav_fac_color_transp;
    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }
//#if 1 //jeff 20080119
    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog->h_txt_txtinfo_2,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }
//#endif
    if(ui2_align == 0)
    {
       ui2_align = WGL_AS_LEFT_TOP;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog->h_txt_txtinfo,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(ui2_align),
                          NULL);
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog->h_txt_txtinfo_2,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(ui2_align),
                          NULL);
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32  _nav_fac_dialog_set_attach_data(
    HANDLE_T       h_simple_dialog,
    NAV_FAC_DIALOG_VIEW_T*  pt_nav_fac_dialog)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_simple_dialog,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_nav_fac_dialog),
                          NULL);
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }
    return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_get_attach_data(
    HANDLE_T         h_simple_dialog,
    NAV_FAC_DIALOG_VIEW_T**    ppt_ui_simple_dialog)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_simple_dialog,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_ui_simple_dialog),
                          NULL);
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_set_text(HANDLE_T            h_simple_dialog,
                                  UTF16_T*            w2s_text)
{
      INT32   i4_ret;
      NAV_FAC_DIALOG_VIEW_T*  pt_nav_fac_dialog_show;

      /* Get simple dialog structure */

      i4_ret = _nav_fac_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_nav_fac_dialog_show);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      pt_nav_fac_dialog_show->pw2s_txtinfo = w2s_text;

      i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog_show->h_txt_txtinfo,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(w2s_text),
                            WGL_PACK(c_uc_w2s_strlen(w2s_text)));

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      return APP_UIR_OK;
}
//#if 1 //jeff 20080119
static INT32 _nav_fac_dialog_set_text_2(HANDLE_T            h_simple_dialog,
                                  UTF16_T*            w2s_text)
{
      INT32   i4_ret;
      NAV_FAC_DIALOG_VIEW_T*  pt_nav_fac_dialog_show;

      /* Get simple dialog structure */

      i4_ret = _nav_fac_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_nav_fac_dialog_show);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      pt_nav_fac_dialog_show->pw2s_txtinfo = w2s_text;

      i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog_show->h_txt_txtinfo_2,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(w2s_text),
                            WGL_PACK(c_uc_w2s_strlen(w2s_text)));

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      return APP_UIR_OK;
}
//#endif
/*----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32  _nav_fac_dialog_create(NAV_FAC_DIALOG_SHOW_INIT_T*    pt_nav_fac_dialog_init,   /* In  */
                                HANDLE_T*                nav_fac_dialog)              /* Out */
{
    INT32 i4_ret;
    INT32 i4_result;
    NAV_FAC_DIALOG_VIEW_T* pt_nav_fac_dialog_show= &t_g_nav_fac_dialog_view;  //ke_vizio_20141118 modify

    pt_nav_fac_dialog_show = (NAV_FAC_DIALOG_VIEW_T *) c_mem_alloc(sizeof(NAV_FAC_DIALOG_VIEW_T));

    if(pt_nav_fac_dialog_show == NULL)
    {
        return APP_UIR_OUT_OF_MEMORY;
    }
    //c_memset(pt_nav_fac_dialog_show,0 , sizeof(NAV_FAC_DIALOG_VIEW_T));  //ke_vizio_20141118 mark

    /* dialog background image */
    i4_ret = _nav_fac_dialog_image_init(pt_nav_fac_dialog_show);
    if(WGLR_OK != i4_ret)
    {
        c_mem_free(pt_nav_fac_dialog_show);  //ke_vizio_20110330 for clean warning.
        return NAVR_FAIL;
    }

    /* Create content frame widget */
    do
    {
        /* Content Frame */
        i4_result =  _nav_fac_dialog_create_frm(pt_nav_fac_dialog_show,
                                                 pt_nav_fac_dialog_init->pf_wdgt_proc,       /* App assigns the pf_wdgt_proc */
                                                 pt_nav_fac_dialog_init->h_parent,
                                                 pt_nav_fac_dialog_init->pt_rect,
                                                 pt_nav_fac_dialog_init->pt_begin_offset);

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* txtinfo */
        i4_result =  _nav_fac_dialog_create_txtinfo(pt_nav_fac_dialog_show,
                                                     pt_nav_fac_dialog_init->pt_rect,
                                                     pt_nav_fac_dialog_init->ui2_txt_align_type);

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /*set all non-visible */
        c_wgl_set_visibility(pt_nav_fac_dialog_show->h_frm_simple_dialog, WGL_SW_HIDE_RECURSIVE);  //ke_vizio_20141118 modify

        /* Return the h_simple_dialog handle */
        *nav_fac_dialog = pt_nav_fac_dialog_show->h_frm_simple_dialog;

        /* Done */
         _nav_fac_dialog_set_attach_data(pt_nav_fac_dialog_show->h_frm_simple_dialog,
                                          pt_nav_fac_dialog_show);
        i4_ret = APP_UIR_OK;

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

    } while(0);

    if(i4_ret != APP_UIR_OK)
    {
        /* Release childs*/

        if(pt_nav_fac_dialog_show->h_txt_txtinfo != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_nav_fac_dialog_show->h_txt_txtinfo);
        }

        /* Release childs*/
        if(pt_nav_fac_dialog_show->h_txt_txtinfo_2 != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_nav_fac_dialog_show->h_txt_txtinfo_2);
        }

        /* Release parent */
        if(pt_nav_fac_dialog_show->h_frm_simple_dialog != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_nav_fac_dialog_show->h_frm_simple_dialog);
        }

        /* Release template images */

        if(pt_nav_fac_dialog_show->h_ui_simple_dialog_bk0 != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_nav_fac_dialog_show->h_ui_simple_dialog_bk0);
        }
        /* Release the structure */
        c_mem_free(pt_nav_fac_dialog_show);

    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_destory(HANDLE_T            h_simple_dialog)

{
      INT32   i4_ret;
      NAV_FAC_DIALOG_VIEW_T*        pt_nav_fac_dialog;

      /* Get simple dialog structure */

      i4_ret = _nav_fac_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_nav_fac_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

        if(pt_nav_fac_dialog->h_txt_txtinfo != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_nav_fac_dialog->h_txt_txtinfo);
        }

        if(pt_nav_fac_dialog->h_txt_txtinfo_2 != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_nav_fac_dialog->h_txt_txtinfo_2);
        }

        /* Release parent */
        if(pt_nav_fac_dialog->h_frm_simple_dialog != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_nav_fac_dialog->h_frm_simple_dialog);
        }

        /* Release template images */

        if(pt_nav_fac_dialog->h_ui_simple_dialog_bk0 != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_nav_fac_dialog->h_ui_simple_dialog_bk0);
        }
        /* Release the structure */
        c_mem_free(pt_nav_fac_dialog);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_set_focus(HANDLE_T  h_simple_dialog, BOOL b_repaint)
{
     c_wgl_set_focus(h_simple_dialog, b_repaint);

     return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_show(HANDLE_T            h_simple_dialog)
{
      INT32   i4_ret;
      NAV_FAC_DIALOG_VIEW_T*        pt_nav_fac_dialog_show;

      /* Get simple dialog structure */

      i4_ret = _nav_fac_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_nav_fac_dialog_show);
      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      /* i4_ret = c_wgl_show(pt_ui_simple_dialog->h_frm_simple_dialog, WGL_SW_NORMAL); */
      //i4_ret = c_wgl_set_visibility(pt_nav_fac_dialog_show->h_frm_simple_dialog, WGL_SW_NORMAL);
      i4_ret = c_wgl_set_visibility(pt_nav_fac_dialog_show->h_frm_simple_dialog, WGL_SW_RECURSIVE);  //ke_vizio_20141118 modify
      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

    return APP_UIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    INT32 i4_ret = 0;  //ke_vizio_20141118 add

    NAV_FAC_DIALOG_SHOW_INIT_T *    t_nav_fac_dialog_init = &t_g_nav_fac_dialog_init;  //ke_vizio_20141118 add

	//DBG_LOG_PRINT(("!!!!@djh %s :\n", __func__));

    c_memset(&t_g_nav_fac_dialog, 0, sizeof(NAV_FAC_DIALOG_T));

    t_g_nav_fac_dialog.h_canvas = pt_ctx->t_gui_res.h_canvas;
    t_g_nav_fac_dialog.ui4_timer_delay = NAV_FAC_DIALOG_DEFAULT_TIMER_DELAY;

    c_timer_create(&t_g_nav_fac_dialog.h_hide_timer);

    #ifdef APP_DFT_LSR_TEST //ke_vizio_20131220 add
    c_timer_create(&t_g_nav_fac_dialog.h_LSR_timer);
    #endif

    #if 1  //ke_vizio_20141118 add
    c_memset(t_nav_fac_dialog_init, 0, sizeof(NAV_FAC_DIALOG_SHOW_INIT_T));

    t_nav_fac_dialog_init->h_parent                       = t_g_nav_fac_dialog.h_canvas;
    t_nav_fac_dialog_init->pf_wdgt_proc                   = NULL;
    t_nav_fac_dialog_init->ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_nav_fac_dialog_init->pt_rect                        = NULL;

    i4_ret = _nav_fac_dialog_create(t_nav_fac_dialog_init,
                              &t_g_nav_fac_dialog.h_dialog);
    if(i4_ret != APP_UIR_OK)
    {
        return NAVR_FAIL;
    }
    #endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_deinit(VOID)
{
    NAV_FAC_DIALOG_T*  pt_this = &t_g_nav_fac_dialog;

    _nav_fac_dialog_destory(pt_this->h_dialog);  //ke_vizio_20141118 add

	//DBG_LOG_PRINT(("!!!!@djh %s :\n", __func__));

    if (c_handle_valid(pt_this->h_hide_timer)) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    pt_this->h_canvas   = NULL_HANDLE;
    pt_this->h_dialog= NULL_HANDLE;
    pt_this->h_hide_timer   = NULL_HANDLE;

    #ifdef APP_DFT_LSR_TEST //ke_vizio_20131220 add
    if (c_handle_valid(pt_this->h_LSR_timer)) {
        c_timer_delete(pt_this->h_LSR_timer);
    }
    pt_this->h_LSR_timer   = NULL_HANDLE;
    #endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern INT32 acfg_get_crnt_isl_rec(
    ISL_REC_T* pt_svl_rec
);
static VOID _nav_urc_src_hotkey(UINT32 ui4_key_code)
{
    INT32 i4_ret;
    UINT8 ui1_rec_num;
    UINT8 ui1_idx = 0;
    ISL_REC_T   t_isl_rec;

    UINT8 ui1_serach_id = 0;
    //UINT8 ui1_next_id = 0;
    BOOL b_found = FALSE;
    DEVICE_TYPE_T e_hotkey_src[255]={0};  //ke_vizio_20110330 for clean warning.

    i4_ret = a_isl_get_num_rec(&ui1_rec_num);
    if(i4_ret != 0){
        DBG_LOG_PRINT((" a_isl_get_num_rec fail\n"));
    }

    for(ui1_idx = 0; ui1_idx < ui1_rec_num; ui1_idx++)
    {
        a_isl_get_rec_by_id(ui1_idx, &t_isl_rec);

        e_hotkey_src[ui1_idx] = t_isl_rec.t_avc_info.e_video_type;
    }

    acfg_get_crnt_isl_rec(&t_isl_rec);

    ui1_serach_id = t_isl_rec.ui1_id + 1;
    if(ui1_serach_id > ui1_rec_num){
        ui1_serach_id = 0;
    }

    switch(ui4_key_code)
    {
        case BTN_FAC_AV:
		case BTN_FAC_YPBPR:		//mind 20160803
        {
            for(ui1_idx = 0; ui1_idx < ui1_rec_num; ui1_idx++)
            {
                if(e_hotkey_src[ui1_serach_id]== DEV_AVC_COMP_VIDEO ||
                   e_hotkey_src[ui1_serach_id]== DEV_AVC_COMBI ||
                   e_hotkey_src[ui1_serach_id]== DEV_AVC_S_VIDEO)
                {
                    b_found = TRUE;
                    break;
                }
                ui1_serach_id = ui1_serach_id + 1;
                if(ui1_serach_id > ui1_rec_num){
                    ui1_serach_id = 0;
                }
            }
        }
            break;

        case BTN_FAC_HDMI:
        {
            for(ui1_idx = 0; ui1_idx < ui1_rec_num; ui1_idx++)
            {
                if(e_hotkey_src[ui1_serach_id] == DEV_AVC_HDMI)
                {
                    b_found = TRUE;
                    break;
                }
                ui1_serach_id = ui1_serach_id + 1;
                if(ui1_serach_id > ui1_rec_num){
                    ui1_serach_id = 0;
                }
            }
        }
            break;

        /*case BTN_FAC_YPBPR:		//mind 20160803
        {
            for(ui1_idx = 0; ui1_idx < ui1_rec_num; ui1_idx++)
            {
                if(e_hotkey_src[ui1_serach_id] == DEV_AVC_Y_PB_PR ||
                   e_hotkey_src[ui1_serach_id] == DEV_AVC_SCART)
                {
                    b_found = TRUE;
                    break;
                }
                ui1_serach_id = ui1_serach_id + 1;
                if(ui1_serach_id > ui1_rec_num){
                    ui1_serach_id = 0;
                }
            }
        }
            break;*/

        case BTN_FAC_VGA:
        {
            for(ui1_idx = 0; ui1_idx < ui1_rec_num; ui1_idx++)
            {
                if(e_hotkey_src[ui1_serach_id] == DEV_AVC_VGA)
                {
                    b_found = TRUE;
                    break;
                }
                ui1_serach_id = ui1_serach_id + 1;
                if(ui1_serach_id > ui1_rec_num){
                    ui1_serach_id = 0;
                }
            }
        }
            break;
        default:
            break;
    }

    if(b_found == TRUE){
        DBG_LOG_PRINT(("Change src id : %d", ui1_serach_id));
        nav_change_av_inp_by_id(TV_WIN_ID_MAIN, ui1_serach_id, NULL);
    }
    else
    {
        #ifndef APP_NAV_BNR_ENHANCE
        a_nav_show_banner();
        #else
        nav_send_msg_to_component(
                                NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER),
                                NAV_UI_MSG_SHOW_BANNER ,
                                NULL) ;
        #endif
    }

}

#ifdef SUPPORT_AUTO_COLOR_KEY
/*-----------------------------------------------------------------------------
 * Name: _fac_dialog_svctx_notify_fct
 * Description: Get the Auto-Color procedure status
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _fac_dialog_svctx_notify_fct(
    HANDLE_T            h_g_fac_dialog_svctx,
    SVCTX_COND_T        e_nfy_cond,
    SVCTX_NTFY_CODE_T   e_code,
    STREAM_TYPE_T       e_stream_type,
    VOID*               pv_nfy_tag)
{
    if(e_code == SVCTX_NTFY_CODE_SIGNAL_LOSS ||
       e_code == SVCTX_NTFY_CODE_INTERRUPTED)
    {
         a_amb_enable_system_key(TRUE);
         nav_send_sim_rc_key_event(BTN_PSUDO_AUTO_FAIL);
    }

    if(e_code == SVCTX_NTFY_CODE_VIDEO_AUTO_COLOR_DONE)
    {
         a_amb_enable_system_key(TRUE);
         nav_send_sim_rc_key_event(BTN_PSUDO_AUTO_DONE);
    }
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_fac_dialog_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    UTF16_T*        pw2s_string;
    INT32           i4_ret = NAVR_OK;

    ISL_REC_T       t_isl_rec;
	UINT32          ui4_fac_val;//jeff 20090107 add
	UINT32          ui4_key_code_for_switch = ui4_key_code & 0x00ffffff;

	//DBG_LOG_PRINT(("!!!!@djh %s, 0x%X(%d) :\n", __func__,ui4_key_code,ui4_key_code));

    a_cfg_cust_fac_get(&ui4_fac_val);//jeff 20090107 add

	//DBG_LOG_PRINT(("!!!!@djh %s, ui4_fac_val=0x%X :\n", __func__,ui4_fac_val));

    if (!(ui4_fac_val & APP_CFG_CUST_FAC_RC_ON))
    {
        DBG_LOG_PRINT(("\n--------NO OPEN FAC RC MODE-------- =%d \n",ui4_fac_val));
		return FALSE;
    }

    switch (ui4_key_code_for_switch)
    {
		/*	//mind 20160509
		case BTN_FAC_LIGHT_SENSOR:
            {
                DBG_LOG_PRINT(("!!!!@djh %s, BTN_FAC_LIGHT_SENSOR, NO-API TODO :\n", __func__));
            }
            break;*/
		case BTN_FAC_FAC:
             DBG_LOG_PRINT(("\n--------Enter Factory MODE--------\n"));
             nav_grab_activation(NAV_COMP_ID_FAC_INX);//joe.zy
			 nav_set_component_visible(NAV_COMP_ID_CSM);
             break;
        case BTN_FAC_CSM:
            DBG_LOG_PRINT(("\n--------Enter CSM MODE--------\n"));
            #if defined(APP_NAV_COMP_ID_CSM)
            nav_send_sim_rc_key_event(PSEUDO_BTN_CSM_MENU);
            #else
            {
                const CHAR*   s_tmp_str;
                CHAR    s_ver[40]={0};

                //s_tmp_str = c_sys_get_version();
                //s_tmp_str = sys_cust_get_usb_upg_version();
                s_tmp_str = sys_cust_get_cust_serial();  //ke_vizio_20160831
                c_sprintf(s_ver,"SW ver : %s", s_tmp_str);
                DBG_LOG_PRINT(("%s\n", s_ver));
                pw2s_string = (UTF16_T*) c_mem_alloc(40 * sizeof(UTF16_T));
                c_uc_ps_to_w2s(s_ver, pw2s_string, sizeof(s_ver));
                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_DCR_ON,
                                                         pw2s_string,
                                                         NULL);
            }
            #endif
            break;
        case BTN_FAC_VOL_MAX:
             DBG_LOG_PRINT(("\n--------Get 100 Vol--------\n"));
			 #if 1 //jeff 20090327 add for URC
             a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), 0);
			 a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
			 #endif
			_nav_fac_volume_setting(ACFG_AUD_VOL_MAX);
				  pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_VOLUME_100P);
				  _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_VOLUME_100P,
																			   pw2s_string,
																			  NULL);
			break;
        case BTN_FAC_VOL_R: // Denny 2008/12/09 add
            DBG_LOG_PRINT(("\n--------Sound Right--------\n"));
            #if 0  //ke_vizio_20160902 modify
            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), 50);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
            pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_BALANCE_RIGHT);
            _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_BALANCE_RIGHT,
                                                pw2s_string,
                                                NULL);
            break;
            #else
            {
                static UINT8 ui1_trigger = 0;
                INT32 i4_vol = 0;
                UINT16 ui2_mlm = 0;
                if(ui1_trigger == 0)
                {
                    //Vol : 25
                    i4_vol = 25;
                    ui2_mlm = MLM_FAC_KEY_MSG_VOLUME_25P;
                }
                else if(ui1_trigger == 1)
                {
                    //Vol : 50
                    i4_vol = 50;
                    ui2_mlm = MLM_FAC_KEY_MSG_VOLUME_50P;
                }
                else
                {
                    //Vol : 75
                    i4_vol = 75;
                    ui2_mlm = MLM_FAC_KEY_MSG_VOLUME_75P;

                }


                _nav_fac_volume_setting(i4_vol);

                pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), ui2_mlm);
                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_BALANCE_RIGHT,
                                                pw2s_string,
                                                NULL);

                ui1_trigger++;
                if(ui1_trigger > 2)
                {
                    ui1_trigger = 0;
                }
                break;
            }
            #endif

        case BTN_FAC_VOL_L: // Denny 2008/12/09 add
          {
            DBG_LOG_PRINT(("\n--------Sound Left--------\n"));
            //const CHAR*   s_tmp_str;
            CHAR    s_info[200]={0};
            NW_IP_INFO_T t_net_ip_info;
            CHAR    s_ip_str[40];
            CHAR    s_rj45_mac_str[64];
            CHAR    s_wlan_mac_str[64];
            UTF16_T w2s_tmp_str[200];
        #ifdef APP_BLUETOOTH_SUPPORT
        #ifdef FAC_BLUETOOTH_SUPPORT // Ben 20180126
            BT_LOCAL_DEV local_dev_info;		//mind 20160805
        #endif
        #endif
            //UTF16_T w2s_str[128];

            c_memset(&t_net_ip_info, 0, sizeof(t_net_ip_info));
            c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
            //c_memset(w2s_str, 0, sizeof(w2s_str));
            c_memset(s_ip_str,0,sizeof(CHAR)*16);
            c_memset(s_rj45_mac_str,0,sizeof(CHAR)*64);
            c_memset(s_wlan_mac_str,0,sizeof(CHAR)*64);

            /*IP Address*/
            i4_ret = a_nw_get_crnt_ip_info(&t_net_ip_info);
            MENU_LOG_ON_FAIL(i4_ret);
            a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_address);

            /*RJ45 MAC*/
            a_nw_get_mac_addr_string(NI_ETHERNET_0,s_rj45_mac_str);

            /*WLAN MAC*/
            a_nw_get_mac_addr_string(NI_WIRELESS_0,s_wlan_mac_str);

            /*BT MAC  */
        #ifdef APP_BLUETOOTH_SUPPORT
        #ifdef FAC_BLUETOOTH_SUPPORT // Ben 20180126
            c_memset(&local_dev_info, 0, sizeof(BT_LOCAL_DEV));		//mind 20160805
            a_mtkapi_bt_gap_get_local_dev_info(&local_dev_info);
        #endif
        #endif

            /*Combine*/
    #ifdef FAC_BLUETOOTH_SUPPORT // Ben 20180126
        #ifdef APP_BLUETOOTH_SUPPORT
            c_sprintf(s_info,"IP: %s \n RJ45 MAC: %s \n WiFi MAC: %s \n BT MAC: %s", s_ip_str,s_rj45_mac_str,s_wlan_mac_str,local_dev_info.bdAddr);		//mind 20160805

        #else
            c_sprintf(s_info,"IP: %s \n RJ45 MAC: %s \n WiFi MAC: %s ", s_ip_str,s_rj45_mac_str,s_wlan_mac_str);
        #endif
    #else
            c_sprintf(s_info,"IP: %s \n RJ45 MAC: %s \n WiFi MAC: %s ", s_ip_str,s_rj45_mac_str,s_wlan_mac_str);
    #endif
            //c_sprintf(s_info, " ");
            //c_sprintf(s_info,"RJ45 MAC:%s", s_rj45_mac_str);
            //c_sprintf(s_info, "    ");
            //c_sprintf(s_info,"WLAN MAC:%s", s_wlan_mac_str);

            c_uc_ps_to_w2s(s_info,w2s_tmp_str,c_strlen(s_info));
            _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_DCR_ON,w2s_tmp_str, NULL);

            _nav_fac_dialog_hide_timer_stop();
	        _nav_fac_dialog_hide_timer_start(3000);	// Ben 20180125

           
         }
		 break;

        case BTN_FAC_BLK:
            if(b_nav_fac_blk)
            {
                DBG_LOG_PRINT(("\n--------Backlight set to 50--------\n"));
                b_nav_fac_blk = FALSE;
                _nav_fac_blacklight_setting(50);
                pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_BLK_50P);	//kyo_20091202
                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_BACKLIGHT_50P,
                                                    pw2s_string,
                                                    NULL);
            }
            else
            {
                DBG_LOG_PRINT(("\n--------Backlight set to 100--------\n"));
                b_nav_fac_blk = TRUE;
                _nav_fac_blacklight_setting(100);
                pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_BLK_100P); //kyo_20091202
                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_BACKLIGHT_100P,
                                                    pw2s_string,
                                                    NULL);
            }
    		break;
		case BTN_FAC_VOL_BUZZ:
            {
                //Denny 2011/03/17 modify
                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), 0);
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
                _nav_fac_volume_setting(25);
                pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_VOLUME_25P);
                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_VOLUME_100P, pw2s_string, NULL);
            }
			break;
        case BTN_FAC_DCR:
			{
                #if 1
                UINT16   ui2_idx = 0;
                a_cfg_custom_get_dimming_idx(&ui2_idx);

                if(ui2_idx > 0)
                {
                    DBG_LOG_PRINT(("\n--------DCR OFF--------\n"));
                    //_nav_fac_dcr_setting(0);
                    a_cfg_custom_set_dimming_idx(FALSE); //Denny 2011/03/17 modify
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_DCR_OFF);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_DCR_OFF,
                                                        pw2s_string,
                                                        NULL);
                }
                else
                {
                    DBG_LOG_PRINT(("\n--------DCR ON--------\n"));
                    //_nav_fac_dcr_setting(1);
                    a_cfg_custom_set_dimming_idx(TRUE); //Denny 2011/03/17 modify
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_DCR_ON);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_DCR_ON,
                                                         pw2s_string,
                                                         NULL);
                }
                //a_cfg_custom_update_dimming_idx();
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));//sam 121029
                #else
                DBG_LOG_PRINT(("\n--------DCR Not Support--------\n"));
                pw2s_string = L"DCR Not Support";
                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_DCR_ON,
                                                         pw2s_string,
                                                         NULL);
                #endif
            }
			break;
#if 0 //todo
        case BTN_FAC_EDID_WP:
            {
                //DBG_LOG_PRINT(("!!!!@djh %s, BTN_FAC_EDID_WP :\n", __func__));
                BOOL bWP;  //Denny 2009/11/06 modify for EDID Write Protect
                a_cfg_cust_fac_get_edid_write_enable(&bWP);  //Denny 2009/11/06 modify for EDID Write Protect
                if (bWP == TRUE) //Denny 2009/11/06 modify for EDID Write Protect
                {
                    a_cfg_cust_fac_edid_write_enable(FALSE); //Denny 2009/11/06 modify for EDID Write Protect
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_EDID_WP_EN);	//kyo_20091202 modify message
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_EDID_ON,
                                                      pw2s_string,
                                                      NULL);
                }
                else
                {
                    a_cfg_cust_fac_edid_write_enable(TRUE); //Denny 2009/11/06 modify for EDID Write Protect
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_EDID_WP_DIS);	//kyo_20091202 modify message
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_EDID_ON,
                                                      pw2s_string,
                                                      NULL);
                }
            }
            break;
#endif
        case BTN_FAC_BI:
			{
			    UINT8   ui_temp_val = 0;

			    a_cfg_get_factory_mode(&ui_temp_val);
                DBG_LOG_PRINT(("\n--------Factory Aging Mode(0x%X)--------\n", ui_temp_val));

                if((ui_temp_val & APP_CFG_FAC_MODE_BURNING_MASK) != 0)
                {
                    nav_fac_set_setup_value(NAV_FAC_MENU_BURN_IN, FALSE);
                }
                else
                {
                    nav_fac_set_setup_value(NAV_FAC_MENU_BURN_IN, TRUE);
                }
        	}
			break;
        case BTN_FAC_RST:
			{
				int cmd_result = 0;
			    DBG_LOG_PRINT(("\n--------Set to final mode , turn off the power--------\n"));
    		    a_cfg_fac_reset();
                menu_clear_memory_ex(FALSE);    // Ben 20180129
#ifdef APP_C4TV_SUPPORT
				a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));	//mind 20160511
				a_cfg_custom_reset_power_mode();		//mind 20160825
				cmd_result = system("sync;sync;sync");		//mind 20160913
				if(cmd_result!=0){
					printf("%s(),%d, cmd_result=%d\n", __func__, __LINE__, cmd_result);
				}
#endif
    			pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_SET_TO_FM);
    			_nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_SET_TO_FM,
    																	   pw2s_string,
    																	  NULL);

    			a_sleep_timer_start(3);	//<INX>James 20120321:Add auto shut-down at URC RST key
        	}
            break;

        case BTN_FAC_CTC:
		{
			INT16   i2_val = 0;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);
			i2_val+=1;
			if(i2_val>3){
			    i2_val=0;
			}
			_nav_fac_color_temp_setting(i2_val);

			if(i2_val == 0)
			{
			    DBG_LOG_PRINT(("\n--------Color Temp to Cool--------\n"));
				pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_COOL);
			  	_nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_WB_COOL,
												  pw2s_string,
												  NULL);
			}
			else if (i2_val == 1)
			{
			    DBG_LOG_PRINT(("\n--------Color Temp to Normal--------\n"));
		 		pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_WARM);
			  	_nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_WB_WARM,
												  pw2s_string,
												  NULL);
			}
			else if (i2_val == 2)
			{
			    DBG_LOG_PRINT(("\n--------Color Temp to Computer--------\n"));
				pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_STANDARD);
				_nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_WB_NORMAL,
                                                  pw2s_string,
                                                  NULL);
			}
			else
			{
			    DBG_LOG_PRINT(("\n--------Color Temp to Custom--------\n"));
				pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_USER);
				_nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_WB_WARM,
                                                  pw2s_string,
                                                  NULL);
			}
        }
			break;
		case BTN_FAC_POWER:
			  a_amb_power_on(FALSE);
			break;
		case BTN_FAC_ANTENNA:
        {
			INT16   i2_val = 0;
            a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
            if (t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
            {
                menu_adjust_vplane();
			}
			else
			{
			    UINT8   ui1_value = 0;
			    UINT16  ui2_svl_id = ATSC_TRSTRL_SVL_ID;

			    a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, &ui1_value);
                if(ui1_value == 0)
                {
                    ui2_svl_id = ATSC_CABLE_SVL_ID;
                }
                else
                {
                    ui2_svl_id = ATSC_TRSTRL_SVL_ID;
                }

                i4_ret = a_cfg_set_tuner_sync_src(ui2_svl_id, NULL);
                if(i4_ret!=APP_CFGR_OK) {
                    DBG_LOG_PRINT(("a_cfg_set_tuner_sync_src() failed. i4_ret = %d at line of Nav_fac_dialog.c\r\n", i4_ret, __LINE__));
                    return FALSE;
                }

#ifdef APP_MENU_DONT_SKIP_FAKE_CHANNEL_WHEN_TOGGLE_TUNER_MODE
                /* Reselect the current channel. Don't skip fake channel. */
                i4_ret = menu_select_crnt_or_first_channel(FALSE);
                if(i4_ret!=0) {
                    DBG_LOG_PRINT(("menu_select_crnt_or_first_channel() failed. i4_ret = %d at line of Nav_fac_dialog.c\r\n", i4_ret, __LINE__));
                    return FALSE;
                }
#else
                /* Reselect the current channel. Skip the fake channel. */
                menu_select_crnt_or_first_channel(TRUE);
                if(i4_ret!=0) {
                    DBG_LOG_PRINT(("menu_select_crnt_or_first_channel() failed. i4_ret = %d at line of Nav_fac_dialog.c\r\n", i4_ret, __LINE__));
                    return FALSE;
                }
#endif
			}


            UINT32      ui4_len = 128;
            UTF16_T     ws2_append_txt[128+1];
            UTF16_T     ws2_append_txt2[128+1];

            c_memset(ws2_append_txt, 0, sizeof(ws2_append_txt));
            c_uc_w2s_strncat( ws2_append_txt, _TEXT("    CT Mode : "),
                              ui4_len);

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);
            if(i2_val == 1)
            {
                c_uc_w2s_strncat( ws2_append_txt, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_COOL), //Cool
                                  ui4_len - c_uc_w2s_strlen(ws2_append_txt));

            }
            else if (i2_val == 2)
            {
                c_uc_w2s_strncat( ws2_append_txt, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_STANDARD), //PC
                                  ui4_len - c_uc_w2s_strlen(ws2_append_txt));
            }
            else if (i2_val == 3)
            {
                c_uc_w2s_strncat( ws2_append_txt, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_WARM), //Normal
                                  ui4_len - c_uc_w2s_strlen(ws2_append_txt));
            }
            else
            {
                c_uc_w2s_strncat( ws2_append_txt, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_USER), //User
                                  ui4_len - c_uc_w2s_strlen(ws2_append_txt));
            }

            c_memset(ws2_append_txt2, 0, sizeof(ws2_append_txt2));
            c_uc_w2s_strncat( ws2_append_txt2, _TEXT("    Pic Mode : "),
                              ui4_len);

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_val);

            if(i2_val == 0)
            {
                c_uc_w2s_strncat( ws2_append_txt2, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PIC_MODE_HOME),
                                  ui4_len - c_uc_w2s_strlen(ws2_append_txt2));
            }
            else if (i2_val == 1)
            {
                c_uc_w2s_strncat( ws2_append_txt2, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PIC_MODE_GAME),
                                  ui4_len - c_uc_w2s_strlen(ws2_append_txt2));
            }
            else if (i2_val == 2)
            {
                c_uc_w2s_strncat( ws2_append_txt2, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PIC_MODE_MOVIE),
                                  ui4_len - c_uc_w2s_strlen(ws2_append_txt2));
            }
            else if (i2_val == 3)
            {
                c_uc_w2s_strncat( ws2_append_txt2, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PIC_MODE_RETAIL),
                                  ui4_len - c_uc_w2s_strlen(ws2_append_txt2));
            }
            else if (i2_val == 4)
            {
                c_uc_w2s_strncat( ws2_append_txt2, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PIC_MODE_PHOTO),
                                  ui4_len - c_uc_w2s_strlen(ws2_append_txt2));
            }
            else  //(i2_val == 5)
            {
                c_uc_w2s_strncat( ws2_append_txt2, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PIC_MODE_CUSTOM),
                                  ui4_len - c_uc_w2s_strlen(ws2_append_txt2));
            }

            _nav_fac_dialog_prompt_msg_dialog_2(NAV_FAC_DIALOG_ID_TV,
                                                ws2_append_txt,
                                                ws2_append_txt2,
                                                NULL);
        }
        break;
		case BTN_FAC_PATTEN:
            {

                UINT32 ui4_fac_val_new;

                //DBG_LOG_PRINT(("!!!!@djh %s, BTN_FAC_PATTEN :\n", __func__));

                a_cfg_cust_fac_get(&ui4_fac_val);
                ui4_fac_val_new = ui4_fac_val>>5;

                if (ui4_fac_val_new ==0)
                {
                    #if 0//def APP_C4TV_SUPPORT
					a_bluetooth_gattc_rssi_meter_dialog_enable(FALSE);	//mind 20160728
					a_bluetooth_gattc_rssi_meter_hide();
                    #endif
                    ui4_fac_val = ui4_fac_val | APP_CFG_CUST_FAC_PATTEN_RED;
                    i4_ret = a_cfg_cust_fac_set(ui4_fac_val);
                    if(i4_ret != APP_CFGR_OK){
                        DBG_LOG_PRINT(("Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
                    }
                    burning_mode_under_ext_rc_control(NAV_FAC_INTERNAL_PATTERN_RED);
                }
                else if (ui4_fac_val_new ==1)
                {
                    ui4_fac_val = ui4_fac_val & ~APP_CFG_CUST_FAC_PATTEN_RED;
                    ui4_fac_val = ui4_fac_val | APP_CFG_CUST_FAC_PATTEN_GREEN;
                    a_cfg_cust_fac_set(ui4_fac_val);
                    burning_mode_under_ext_rc_control(NAV_FAC_INTERNAL_PATTERN_GREEN);
                }
                else if (ui4_fac_val_new ==2)
                {
                    ui4_fac_val = ui4_fac_val & ~APP_CFG_CUST_FAC_PATTEN_GREEN;
                    ui4_fac_val = ui4_fac_val | APP_CFG_CUST_FAC_PATTEN_BLUE;
                    a_cfg_cust_fac_set(ui4_fac_val);
                    burning_mode_under_ext_rc_control(NAV_FAC_INTERNAL_PATTERN_BLUE);
                }
                else if (ui4_fac_val_new ==4)
                {
                    ui4_fac_val = ui4_fac_val & ~APP_CFG_CUST_FAC_PATTEN_BLUE;
                    ui4_fac_val = ui4_fac_val | APP_CFG_CUST_FAC_PATTEN_WHITE;
                    a_cfg_cust_fac_set(ui4_fac_val);
                    burning_mode_under_ext_rc_control(NAV_FAC_INTERNAL_PATTERN_White);
                }
                else if (ui4_fac_val_new ==8)
                {
                    ui4_fac_val = ui4_fac_val & ~APP_CFG_CUST_FAC_PATTEN_WHITE;
                    ui4_fac_val = ui4_fac_val | APP_CFG_CUST_FAC_PATTEN_BLACK;
                    a_cfg_cust_fac_set(ui4_fac_val);
                    burning_mode_under_ext_rc_control(NAV_FAC_INTERNAL_PATTERN_BLACK);
                }
                else
                {
                    ui4_fac_val = ui4_fac_val & ~APP_CFG_CUST_FAC_PATTEN_BLACK;
                    a_cfg_cust_fac_set(ui4_fac_val);
                    nav_hide_component (NAV_COMP_ID_BURNING_MODE);
                    #if 0//def APP_C4TV_SUPPORT
					a_bluetooth_gattc_rssi_meter_dialog_enable(TRUE);	//mind 20160728
                    #endif
                }
            }
            break;
        case BTN_FAC_PREV_PRG:
            acfg_INX_load_default_channel("FQ");
            a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
            if (t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
            {
                menu_adjust_vplane();
            }
			break;

        case BTN_FAC_TV:

            i4_ret = a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, (ui4_key_code -BTN_FAC_TV));
            if (i4_ret != APP_CFGR_OK) {
                return FALSE;
            }
            i4_ret = nav_change_av_inp_by_id(TV_WIN_ID_MAIN,(ui4_key_code -BTN_FAC_TV),NULL);
            if(NAVR_OK != i4_ret)
            {
                return FALSE;
            }
            return FALSE;

        case BTN_FAC_VGA:
        case BTN_FAC_AV:
        case BTN_FAC_HDMI:
        case BTN_FAC_YPBPR:
            _nav_urc_src_hotkey(ui4_key_code);
            return FALSE;

	case BTN_FAC_PM_TO_STANDARDS:
	    DBG_LOG_PRINT(("\n--------Pic to Standard--------\n"));
		//_nav_fac_picmode_setting(FAC_PIC_MODE_STANDARD);
		_nav_fac_picmode_setting(ACFG_CUST_PIC_MODE_STANDARD);
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PIC_MODE_STANDARD);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_MODE_CINEMA,
                                                                           pw2s_string,
                                                                          NULL);
		break;

#if 0
	case BTN_FAC_WB_TO_NORMAL:
		_nav_fac_color_temp_setting(NAV_FAC_MENU_COLOR_TEMP_STANDARD);
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_WB_NORMAL);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_WB_NORMAL,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Color Temp to Standard--------\n"));
		break;
	case BTN_FAC_WB_TO_WARM:
		_nav_fac_color_temp_setting(NAV_FAC_MENU_COLOR_TEMP_WARM);
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_WB_WARM);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_WB_WARM,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Color Temp to Warm--------\n"));
		break;
	case BTN_FAC_WB_TO_COOL:
		_nav_fac_color_temp_setting(NAV_FAC_MENU_COLOR_TEMP_COOL);
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_WB_COOL);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_WB_COOL,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Color Temp to Cool--------\n"));
		break;
#endif

	case BTN_FAC_SM_TO_STEREO:
	    DBG_LOG_PRINT(("\n--------Sound Mode to Stereo--------\n"));
		_nav_fac_aud_mts_setting(1);
        pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_SOUND_MODE_STEREO);
        _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_SM_STEREO,
                                          pw2s_string,
                                          NULL);
		break;
	case BTN_FAC_AVL_OFF:
	    DBG_LOG_PRINT(("\n--------Set AGC Off--------\n"));
		_nav_fac_agc_setting(FALSE);
        pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_AVL_OFF);
        _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_AVL_OFF,
                                          pw2s_string,
                                          NULL);
		break;

#ifdef SUPPORT_AUTO_COLOR_KEY
		case BTN_FAC_AUTO_COLOR:
        //case BTN_FAC_AUTO_COLOR_FUNCTION:

            {
                i4_ret = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
                if (i4_ret != ISLR_OK) {
                   return FALSE;
                }
                if (((t_isl_rec.e_src_type == INP_SRC_TYPE_AV)&&
                    ((t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR)||(t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)||
                    (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_SCART)))&&
                    !nav_fac_is_video_block()&&
                    !nav_fac_is_signal_loss())
                {
    		    DBG_LOG_PRINT(("\n--------Auto-Color processing--------\n"));
                ui4_auto_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();
                i4_ret = c_svctx_open(SVCTX_NAME_MAIN, &h_g_fac_dialog_svctx);
                if (i4_ret != NAVR_OK) {
                    return FALSE;
                }
                a_amb_enable_system_key(FALSE);
                pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_AUTO_COLOR_PROCESS);
                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_TEST_MODE_ON,
                                                                           pw2s_string,
                                                                          _nav_fac_dialog_default_msg_proc);
                _nav_fac_dialog_hide_timer_stop();
                i4_ret = c_svctx_set_listener(h_g_fac_dialog_svctx,
                                                               _fac_dialog_svctx_notify_fct,
                                                              NULL);
                if (i4_ret != SMR_OK)
                {
                    return FALSE;
                }
                i4_ret = c_svctx_set_stream_attr(h_g_fac_dialog_svctx,
                                                                    ST_VIDEO,
                                                                    SM_VSH_SET_TYPE_AUTO_COLOR,
                                                                    NULL,
                                                                    0);
                if (i4_ret != SMR_OK)
                {
                    return FALSE;
                }
                i4_ret = c_timer_create(&t_g_nav_fac_dialog.h_auto_color_timer);

                i4_ret = c_timer_start(t_g_nav_fac_dialog.h_auto_color_timer,
                	                      1000,
                	                      X_TIMER_FLAG_REPEAT,
                	                      _nav_fac_dialog_auto_color_timeout,
                	                      NULL);
                }
                else
                {
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_AUTO_DONE,
                                                        MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_AUTO_COLOR_FAIL),
                                                        NULL);
                }
            }
            break;
#endif
#if 0
        case BTN_FAC_VGA_SWITCH://Set to Uart Mode
            {
                UINT32  ui4_fac_val;

                a_cfg_cust_fac_get(&ui4_fac_val);
                ui4_fac_val = ui4_fac_val | APP_CFG_CUST_FAC_VGA_SWITCH;
                //GPIO_SetOut(TOP_EU_IO_VGA_SWITCH_CONTROL ,(INT32)TRUE);
                DBG_LOG_PRINT(("\n--------Uart Mode --------\n"));
                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_VGA_SWITCH,
                                                                               MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_URC_VGA_SWITCH),
                                                                               NULL);
                i4_ret =  a_cfg_cust_fac_set(ui4_fac_val);
                if (i4_ret != APP_CFGR_OK)
                    return FALSE;
            }
            break;
#endif
       case BTN_FAC_SET_TO_FM:
              DBG_LOG_PRINT(("\n--------Set to final mode , turn off the power--------\n"));
              a_cfg_fac_reset();
              a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT);
              a_cfg_store();//save to eeprom
              menu_clear_memory_ex(FALSE);    // Ben 20180129
              a_amb_resume_app (WZD_NAME);
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_SET_TO_FM);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_SET_TO_FM,
                                                                           pw2s_string,
                                                                          NULL);
		break;
		#if 0
		case BTN_FAC_VGA_AUTO:
			{
			i4_ret = a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
            if (i4_ret != ISLR_OK) {
               return FALSE;
            	}
            if ((t_isl_rec.e_src_type == INP_SRC_TYPE_AV)&&
                (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA))
            	{
			    a_cfg_vga_auto_clk_phs_pos();
                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_AUTO_COFIG,
                                                                               MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_AUTO_CONFIG),
                                                                               NULL);
            	}
		        DBG_LOG_PRINT(("\n--------VGA AUTO DONE--------\n"));
			}
			break;
        #endif
        case BTN_FAC_LOGO_LED:
            #if 1 //Denny 2011/03/17 mark
            {
				UINT16 ui2_idx = 0;

    			ui2_idx = a_cfg_custom_get_led_logo_ctrl();
				if(ui2_idx == 0)// if LOGO == Off
			    {
			        DBG_LOG_PRINT(("\n--------LOGO LED ON--------\n"));
			    	ui2_idx = 1;
					//DRVCUST_VIZIO_LOGO_CTRL(ui2_idx);
			        //c_pcl_set_gpio(211, ui2_idx);	//POWER_LED_GPIO	//sam 130807
			        //c_pcl_set_gpio(210, 0);	//BACKUP_LED_GPIO
			        //b_logo_LED_standby = FALSE;  // Reset
			        //ui4_LED_LOGO_counter = 1; // Reset counter
			        pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_LED_ON);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_LOGO_LED,
                                                      pw2s_string,
                                                      NULL);
			    }
				else
			    {
			        DBG_LOG_PRINT(("\n--------LOGO LED OFF--------\n"));
			    	ui2_idx = 0;
					//DRVCUST_VIZIO_LOGO_CTRL(ui2_idx);
			        //c_pcl_set_gpio(211, ui2_idx);
			        //c_pcl_set_gpio(210, 0);
					pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_LED_OFF);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_LOGO_LED,
                                                      pw2s_string,
                                                      NULL);
			    }
					a_cfg_custom_set_led_logo_ctrl((UINT8)ui2_idx);
					{
				        menu_pm_refresh();
				        menu_pm_repaint();
				    }
				    //VIZIO_LOGO_D_SET(ui2_idx);
	            }
			#else
            {
                PCL_GPIO_STATUS_T   e_val1 = PCL_GPIO_STATUS_LOW;
                //PCL_GPIO_STATUS_T   e_val2 = PCL_GPIO_STATUS_LOW;

                c_pcl_get_gpio( 205, PCL_GPIO_MODE_OUTPUT, &e_val1);
                //c_pcl_get_gpio( 4,   PCL_GPIO_MODE_OUTPUT, &e_val2);

                if(e_val1==PCL_GPIO_STATUS_LOW)
                {
                    //GPIO_SetOut(205 ,(INT32)TRUE);
                    c_pcl_set_gpio(205, PCL_GPIO_STATUS_HIGH);
                    //GPIO_SetOut(4 ,(INT32)TRUE);
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_LED_HIGH);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_LOGO_LED,
                                                      pw2s_string,
                                                      NULL);
                }
                else
                {
                    //GPIO_SetOut(205 ,(INT32)FALSE);
                    //GPIO_SetOut(4 ,(INT32)FALSE);
                    c_pcl_set_gpio(205, PCL_GPIO_STATUS_LOW);
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_LED_LOW);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_LOGO_LED,
                                                      pw2s_string,
                                                      NULL);
                }
            }
            #endif
            break;
#ifndef APP_C4TV_SUPPORT
        case BTN_FAC_USB: //Denny 2011/03/17 add
            {
                UINT32 ui4_mnt_count = 0;
                INT32  i4_ret = 0;

                i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
                if ((i4_ret != 0)||(ui4_mnt_count==0))
                {
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_NO_USB);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_USB, pw2s_string, NULL);
                    return FALSE;
                }
                else
                    a_mmp_request_operation(MMP_REQ_OP_ENTER_PHOTO_BWR);
            }
            break;
#endif
        case BTN_FAC_P_EFFECT: //ke_vizio_20130603 modify //Denny 2011/03/17 add
            {
                INT16   i2_idx = 0;

                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_idx);
                i2_idx+=1;
                if(i2_idx>5)
                    i2_idx=0;

                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), i2_idx);
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));

                switch((UINT16)i2_idx)
                {
                case 0:
                    DBG_LOG_PRINT(("\n--------Picture Mode to Standard--------\n"));
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_ITEM_STD);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_STANDARD, pw2s_string, NULL);
                    break;
                case 1:
                    DBG_LOG_PRINT(("\n--------Picture Mode to Calibrated--------\n"));
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_ITEM_BRIGHT_ROOM);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_MOVIE, pw2s_string, NULL);
                    break;
                case 2:
                    DBG_LOG_PRINT(("\n--------Picture Mode to Calibrated Dark--------\n"));
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_ITEM_DARK_ROOM);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_GAME, pw2s_string, NULL);
                    break;
                case 3:
                    DBG_LOG_PRINT(("\n--------Picture Mode to Vivid--------\n"));
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_ITEM_RETAIL);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_VIVID, pw2s_string, NULL);
                    break;
                case 4:
                    DBG_LOG_PRINT(("\n--------Picture Mode to Game--------\n"));
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_ITEM_GAME);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_FOOTBALL, pw2s_string, NULL);
                    break;
                case 5:
                    DBG_LOG_PRINT(("\n--------Picture Mode to Computer--------\n"));
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_ITEM_COMPURER);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_FOOTBALL, pw2s_string, NULL);
                    break;
                default:
                    DBG_LOG_PRINT(("\n--------Picture Mode to Custom--------\n"));
                    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PIC_CUSTOM);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_CUSTOM, pw2s_string, NULL);
                    break;
                }
            }
            break;
	    case BTN_FAC_ARC:
           	{
        		UINT8 ui1_cec_func;

        		a_cfg_get_cec_func (&ui1_cec_func);

        		if (ui1_cec_func == APP_CFG_CEC_OFF)
        		{
        		    DBG_LOG_PRINT(("\n--------ARC ON--------\n"));
        		    a_cfg_set_cec_func (APP_CFG_CEC_ON);
        	        a_cfg_set_cec_auto_on(APP_CFG_CEC_ON);
        	        a_cfg_set_cec_auto_off(APP_CFG_CEC_ON);
        	        a_cfg_set_cec_sac_func(APP_CFG_CEC_ON);
        			pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_ARC_ON);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_ARC_ON,
                                                        pw2s_string,
                                                        NULL);
        		}
        		else
        		{
        		    DBG_LOG_PRINT(("\n--------ARC OFF--------\n"));
        		    a_cfg_set_cec_func (APP_CFG_CEC_OFF);
        	        a_cfg_set_cec_auto_on(APP_CFG_CEC_OFF);
        	        a_cfg_set_cec_auto_off(APP_CFG_CEC_OFF);
        			a_cfg_set_cec_sac_func(APP_CFG_CEC_OFF);
        			pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_ARC_OFF);
                    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_ARC_OFF,
                                                        pw2s_string,
                                                        NULL);
        		}

        		menu_pm_refresh();
        		menu_pm_repaint();
           	}
			break;

		case BTN_FAC_LSR:
		{
				INT16   i2_light_sensor = 0;

                #ifdef FAC_PHASE2_UI_SETTING  //ke_vizio_20140619 add
                BOOL b_pic_mode_usage = 0;
                // Get custom 1's usage, custom 1 = "6".
                a_cfg_cust_get_cust_pic_mode_exist_status(6, &b_pic_mode_usage);
				if(b_pic_mode_usage == FALSE)
				{
                    a_cfg_cust_create_pic_mode();
                    a_cfg_cust_set_cust_pic_mode_name(6,"Factory");
                }
                else
                {
                    //Change to "custom 1"
                    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),6);
                }
                #endif

				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), &i2_light_sensor);
				if(i2_light_sensor == 0)	//Off
				{

	                #ifdef APP_DFT_LSR_TEST  //ke_vizio_20131220 add
                    _nav_fac_dialog_LSR_timer_start();
	                #endif

				    DBG_LOG_PRINT(("\n--------Light sensor On--------\n"));
					a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR),3);	//High
					pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_LSR_ON);
	                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_LSR_ON,
	                                                    pw2s_string,
	                                                    NULL);

	                #ifdef APP_DFT_LSR_TEST //ke_vizio_20131220 add
                    _nav_fac_dialog_hide_timer_stop();
	                _nav_fac_dialog_hide_timer_start(6000);	// Ben 20161125, for TF1016VIZUSMTK03-665
	                #endif
				}
				else
				{
				    DBG_LOG_PRINT(("\n--------Light sensor Off--------\n"));
					a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR),0);	//Off
					pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_LSR_OFF);
	                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_LSR_OFF,
	                                                    pw2s_string,
	                                                    NULL);
				}

				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));
			}
			break;

#if 0
			case BTN_FAC_3D_2D:
			{
				INT16          ui2_mode_idx = 0;
    			INT16          ui2_3d_to_2d_mode = 0;

	     		if (a_tv_custom_is_3D_mode_playing() == FALSE)
	     		{
	     		    DBG_LOG_PRINT(("\n--------3D Mode--------\n"));
		        	ui2_3d_to_2d_mode = APP_CFG_3D_TO_2D_OFF; //sam 120502
					ui2_mode_idx = APP_CFG_3D_MODE_SBS;
					pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_3D2D_3D);
	                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_3D2D_ON,
	                                                    pw2s_string,
	                                                    NULL);
	     		}
				else
				{
				    DBG_LOG_PRINT(("\n--------2D Mode--------\n"));
            		ui2_3d_to_2d_mode = APP_CFG_3D_TO_2D_LEFT;	//sam 120502
					ui2_mode_idx = APP_CFG_3D_MODE_OFF;
					pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_3D2D_2D);
	                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_3D2D_OFF,
	                                                    pw2s_string,
	                                                    NULL);
				}
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                 (INT16)ui2_mode_idx);
		        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

		        /* 3D to 2D*/
		        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
		                 (INT16 )ui2_3d_to_2d_mode);
		        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));
				#if 0	//sam 120502
				a_cfg_set_3d_display (a_tv_custom_is_3D_mode_playing ());
		        a_cfg_update_viewport ();
				#endif
			}
			break;
#endif
#if 1
			case BTN_FAC_VIRGIN_MODE_OFF:
			{
              //a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT+2);
#ifdef APP_C4TV_SUPPORT
              a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));	//mind 20160512
              a_cfg_store();//save to eeprom
              a_amb_resume_app (WZD_NAME);
#endif
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_VIRGIN_MODE_OFF);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_VIRGIN_MODE,
                                                                           pw2s_string,
                                                                          NULL);
			  DBG_LOG_PRINT(("\n--------Virgin Mode off--------\n"));

			  i4_ret = a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, (ui4_key_code -BTN_FAC_VIRGIN_MODE_OFF));	//mind 20160512
			  if (i4_ret != APP_CFGR_OK) {
				  return FALSE;
			  }
			  i4_ret = nav_change_av_inp_by_id(TV_WIN_ID_MAIN,(ui4_key_code -BTN_FAC_VIRGIN_MODE_OFF),NULL);
			  if(NAVR_OK != i4_ret)
			  {
				  return FALSE;
			  }
			  return FALSE;
			}
              //break;
#endif
			case BTN_FAC_PREV_SCAN:		//mind 20160511
			case BTN_FAC_3D_2D:
			//case BTN_FAC_VIRGIN_MODE_OFF:
			case BTN_FAC_CI_PLUS:
			case BTN_FAC_REGIN:
			//case BTN_FAC_CLONE:
			case BTN_FAC_EDID_WP:
            #ifdef APP_C4TV_SUPPORT
			case BTN_FAC_USB:
            #endif
			case BTN_FAC_RJ45:
			case BTN_FAC_RS232:
			case BTN_FAC_RESERVE:  //ke_vizio_20130912 mark
			    DBG_LOG_PRINT(("\n--------Not Support--------\n"));
				pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_NOT_SUPPORT);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_NO_SUPPORT,
                                                                           pw2s_string,
                                                                          NULL);
			break;
#if 0
			case BTN_FAC_RESERVE:  //ke_vizio_20130912 add
            {
                DBG_LOG_PRINT(("\n--------BTN_FAC_RESERVE--------\n"));
                #ifdef APP_INX_DFT_URC_WIFI
                nav_fac_urc_set_wifi();
                #endif
			    break;
			}
#endif
#if 1//0	// Factory change to disable it   Ben 20140725
			//case BTN_FAC_CLK:	// Ben 20140714
			case BTN_FAC_S_EFFECT:	//mind 20160510
			{
				INT16   i2_idx = 0;

                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_SURROUND), &i2_idx);

                if(i2_idx == 0)
					i2_idx = 1;
				else
					i2_idx = 0;

                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_SURROUND), i2_idx);
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_SURROUND));

				if (i2_idx == 1)
				{
	                DBG_LOG_PRINT(("\n--------Surround On--------\n"));
	                pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_SURROUND_ON);
	                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_STANDARD, pw2s_string, NULL);

				}

				if (i2_idx == 0)
				{
	                DBG_LOG_PRINT(("\n--------Surround Off--------\n"));
	                pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_SURROUND_OFF);
	                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_STANDARD, pw2s_string, NULL);

				}

				break;
			}
#endif
#if 0
       case BTN_FAC_ENTER_FM:
            UART_SetDebugPortFactory(TRUE);
            DBG_LOG_PRINT(("\n--------Enter Factory RS-232--------\n"));
            pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_ENTER_FAC);
            _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_ENTER_FM,
                                                                         pw2s_string,
                                                                         NULL);
            break;
       case BTN_FAC_EXIT_FM:
            UART_SetDebugPortFactory(FALSE);
            SerStart();
            DBG_LOG_PRINT(("\n--------Leave Factory RS-232--------\n"));
            pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_LEAVE_FAC);
            _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_LEAVE_FM,
                                                                         pw2s_string,
                                                                         NULL);
            break;
       case BTN_FAC_SET_ALL_PM:
              i4_ret = a_isl_get_num_rec(&ui1_src_number);
              for(ui2_src_idx = 0;ui2_src_idx < ui1_src_number;ui2_src_idx++)
              {
                  a_cfg_cust_fac_psm_set(ui2_src_idx,CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),FAC_PIC_MODE_DYNAMIC);
              }
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_SET_ALL_PM);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_SET_ALL_PM,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Set all the picture mode to Dynamic--------\n"));
		break;
       case BTN_FAC_SET_TO_FM:
              a_cfg_fac_reset();
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_SET_TO_FM);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_SET_TO_FM,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Set to final mode , turn off the power--------\n"));
		break;
	case BTN_FAC_PM_TO_PERSONAL:
		_nav_fac_picmode_setting(FAC_PIC_MODE_USER);
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PIC_MODE_PERSONAL);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_MODE_USER,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Pic to User--------\n"));
		break;
	case BTN_FAC_PM_TO_SPORTS:
		_nav_fac_picmode_setting(FAC_PIC_MODE_DYNAMIC);
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PIC_MODE_SPORTS);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_PIC_MODE_SPORT,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Pic to Dynamic--------\n"));
		break;
       case BTN_FAC_BALANCE_R: // Denny 2008/12/09 add
		i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), 50);
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_BALANCE_RIGHT);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_BALANCE_RIGHT,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Sound Right--------\n"));
       	break;
       case BTN_FAC_BALANCE_L: // Denny 2008/12/09 add
		i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), -50);
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_BALANCE_LEFT);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_BALANCE_LEFT,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Sound Left--------\n"));
              break;
       case BTN_FAC_SV_TO_50P: // Denny 2008/12/09 add
		_nav_fac_volume_setting(50);
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_VOLUME_50P);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_VOLUME_50P,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Get 50 Vol--------\n"));
       	break;
       case BTN_FAC_SV_TO_100P:
		_nav_fac_volume_setting(100);
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_VOLUME_100P);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_VOLUME_100P,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Get 100 Vol--------\n"));
              break;
        case BTN_FAC_POWER_OFF:
              a_amb_power_on(FALSE);
              break;
        case BTN_FAC_TEST_MODE_ON:
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_TEST_MODE_ON);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_TEST_MODE_ON,
                                                                           pw2s_string,
                                                                          NULL);
              break
	    case BTN_FAC_IPAT_RED:
        case BTN_FAC_IPAT_GREEN:
        case BTN_FAC_IPAT_BLUE:
        case BTN_FAC_IPAT_WHITE:
        case BTN_FAC_IPAT_BLACK:
            DBG_LOG_PRINT(("\n--------Set to Internal Pattern --------\n"));
            burning_mode_under_ext_rc_control(NAV_FAC_INTERNAL_PATTERN_RED+(ui4_key_code-BTN_FAC_IPAT_RED));
            break;
        case BTN_FAC_EDIDWP_EN:
            if(b_nav_fac_edid_write_en)
            {
                //Emerson Add 2008-1127 for prevent MW reset the EDID WP in factory mode.
                c_pcl_get_misc_ctrl(&ui4_misc_ctrl);
                ui4_misc_ctrl &= ~PCL_MISC_CTRL_FACTORY_MODE;
                c_pcl_set_misc_ctrl(ui4_misc_ctrl);
                a_cfg_cust_fac_edid_write_enable(FALSE);
                b_nav_fac_edid_write_en = FALSE;
                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_EDID_WRITE_DIS,
                                                                               MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_EDID_WP_EN),
                                                                               NULL);
            }
            else
            {
                //Emerson Add 2008-1127 for prevent MW reset the EDID WP in factory mode.
                c_pcl_get_misc_ctrl(&ui4_misc_ctrl);
                ui4_misc_ctrl |= PCL_MISC_CTRL_FACTORY_MODE;
                c_pcl_set_misc_ctrl(ui4_misc_ctrl);
                a_cfg_cust_fac_edid_write_enable(TRUE);
                b_nav_fac_edid_write_en = TRUE;
                _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_EDID_WRITE_EN,
                                                                               MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_EDID_WP_DIS),
                                                                               NULL);
            }
            break;
        case BTN_FAC_VIRGIN_MODE_ON:
              a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT);
              a_cfg_store();//save to eeprom
              pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_VIRGIN_MODE);
              _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_VIRGIN_MODE,
                                                                           pw2s_string,
                                                                          NULL);
		DBG_LOG_PRINT(("\n--------Virgin mode on--------\n"));
              break;
#endif

    case BTN_FAC_CLONE:
    {
        DBG_LOG_PRINT(("\n--------BTN_FAC_CLONE--------\n"));
        #ifdef APP_TTS_SUPPORT
        UINT8 ui1_idx;
        a_cfg_get_tts_switch_status(&ui1_idx);
        ui1_idx =! ui1_idx;
        a_cfg_set_tts_switch_status(ui1_idx);
        a_cfg_update_tts_switch_status();

        pw2s_string = (ui1_idx == 0 ? L"TTS Off": L"TTS On");
        _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_TTS,
                                            pw2s_string,
                                            NULL);
        #else
        DBG_LOG_PRINT(("\n--------Not Support--------\n"));
        pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_NOT_SUPPORT);
        _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_NO_SUPPORT,
                                            pw2s_string,
                                            NULL);
        #endif
        break;
    }

#ifdef APP_INX_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
    case BTN_FAC_WIFI_SSID:  //ke_vizio_20170523
    {
        DBG_LOG_PRINT(("\n--------BTN_FAC_WIFI_SSID--------\n"));
        #ifdef APP_INX_DFT_WIFI_AUTO_DETECTION
        UINT8 ui1_status = 0xAA; // 0XAA :WIFI status ON
        UINT32 ui4_wirtten;

        a_cfg_eep_raw_write(EEP_WIFI_SSID_ON, &ui1_status, 1, &ui4_wirtten);

        i4_ret = INX_FACTORY_WIFI_AUTODETECT();
        if (i4_ret != NWR_OK)
        {
            DBG_INFO(("[Fac] a_nw_wlan_associate() Fail. Return %d.\n", i4_ret));
        }

        pw2s_string = L"WIFI SSID : iptvwifi_test";
        _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_WIFI_SSID,
                                            pw2s_string,
                                            NULL);
        #endif
        break;
    }

    case BTN_FAC_RESERVE1:  //ke_vizio_20170523
    {
        DBG_LOG_PRINT(("\n--------BTN_FAC_RESERVE1--------\n"));
        #ifdef APP_INX_DFT_WIFI_AUTO_DETECTION
        UINT8 ui1_status = 0;
        UINT32 ui4_read;
        //BOOL b_connect = FALSE;

        a_cfg_eep_raw_read(EEP_WIFI_SSID_ON, &ui1_status, 1, &ui4_read);

        DBG_LOG_PRINT(("%s EEP_WIFI_SSID_ON: %d\n", __FUNCTION__, ui1_status));


        DBG_LOG_PRINT(("%s EEP_WIFI_status: %d\n", __FUNCTION__, INX_fac_get_WIFI_status()));

        pw2s_string = (TRUE == INX_fac_get_WIFI_status() ? L"WIFI status : 01": L"WIFI Status : 00");
        _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_WIFI_STATUS,
                                            pw2s_string,
                                            NULL);
        #endif
        break;
    }
#endif

	 default:
	    return FALSE;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{

    NAV_FAC_DIALOG_T*  pt_this = &t_g_nav_fac_dialog;
    INT32   i4_ret = NAVR_FAIL;

	//DBG_LOG_PRINT(("!!!!@djh %s :\n", __func__));

    do
    {
        i4_ret = _nav_fac_dialog_set_focus(pt_this->h_dialog, FALSE);
        if(i4_ret != APP_UIR_OK){ break;}

        i4_ret = _nav_fac_dialog_show(pt_this->h_dialog);
        if(i4_ret != APP_UIR_OK){ break;}

        i4_ret = c_wgl_repaint(pt_this->h_dialog, NULL, IS_SYNC_REPAINT);
        if(i4_ret != APP_UIR_OK){ break;}

        i4_ret = nav_set_component_visible(NAV_COMP_ID_FAC_DIALOG);
        if(i4_ret != APP_UIR_OK){ break;}

        i4_ret = NAVR_OK;
    }while(0);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{

	//DBG_LOG_PRINT(("!!!!@djh %s :\n", __func__));

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
#ifdef APP_INX_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
    switch (pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_POWER_ON:
        {
            #ifdef APP_INX_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
            UINT8 ui1_status = 0;
            UINT32 ui4_read;
            INT32 i4_ret = 0;

            a_cfg_eep_raw_read(EEP_WIFI_SSID_ON, &ui1_status, 1, &ui4_read);

            if(ui1_status == 0xAA)
            {
                static UINT32       ui4_nw_nfy_id = 0;

                i4_ret = a_nw_register(_auto_detect_nw_notify_callback, NULL, &ui4_nw_nfy_id );
                if (i4_ret != NWR_OK)
                {
                    DBG_INFO(("[Fac] a_nw_register() Fail. Return %d.\n", i4_ret));
                    return INX_FACTORY_COND_FAIL;
                }
            }
            #endif

            break;
        }

        default:
            break;
    }
#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_hide(
                    VOID
                    )
{
    NAV_FAC_DIALOG_T*  pt_this = &t_g_nav_fac_dialog;

	//DBG_LOG_PRINT(("!!!!@djh %s :\n", __func__));

    /* Hide the widgets */
    if(pt_this->e_dialog_id != NAV_FAC_DIALOG_ID_NULL)
    {
        //ke_vizio_20141118 modify
        //_nav_fac_dialog_destory(pt_this->h_dialog);
        c_wgl_set_visibility(pt_this->h_dialog, WGL_SW_HIDE);
        c_wgl_repaint(pt_this->h_dialog, NULL, TRUE);

        //pt_this->h_dialog = NULL_HANDLE;
        pt_this->e_dialog_id = NAV_FAC_DIALOG_ID_NULL;
    }

    /* Return activation */
    nav_return_activation(NAV_COMP_ID_FAC_DIALOG);

    /* stop the timer */
    _nav_fac_dialog_hide_timer_stop();

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_hide_timer_start(
    UINT32    ui4_time)
{
    c_timer_start(t_g_nav_fac_dialog.h_hide_timer,
                  ui4_time,
                  X_TIMER_FLAG_ONCE,
                  _nav_fac_dialog_hide_timer_nfy,
                  NULL);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_hide_timer_stop(VOID)
{
    c_timer_stop(t_g_nav_fac_dialog.h_hide_timer);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_fac_dialog_hide_timer_nfy (
    HANDLE_T  h_timer,
    VOID*     pv_tag)
{
    nav_request_context_switch(_nav_fac_dialog_timeout_to_hide,
                               NULL,
                               NULL,
                               NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_fac_dialog_timeout_to_hide(
    VOID*                       pv_tag,
    VOID*                       pv_tag2,
    VOID*                       pv_tag3)
{
    NAV_FAC_DIALOG_T*  pt_this = &t_g_nav_fac_dialog;

    #ifdef APP_DFT_LSR_TEST //ke_vizio_20131220 add
    if(pt_this->b_LSR_time_start == TRUE)
    {
        UTF16_T w2s_buf[10];
        c_memset(w2s_buf, 0, 10);
        _nav_fac_dialog_LSR_timer_stop();
        _nav_fac_dialog_set_text_2(pt_this->h_dialog, w2s_buf);
        pt_this->b_LSR_time_start = FALSE;
    }
    #endif
	#if 0  // Don't hide when timeout
    if(pt_this->e_dialog_id != NAV_FAC_DIALOG_ID_NULL)
    {
        _nav_fac_dialog_hide();
    }
	#endif
}

#ifdef SUPPORT_AUTO_COLOR_KEY
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_fac_dialog_auto_color_timeout(
    HANDLE_T                    h_timer,
    VOID*                       pv_tag
    )
{
    UINT32  ui4_curr_time;
    ui4_curr_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

    if(ui4_curr_time - ui4_auto_start_time > NAV_FAC_DIALOG_AUTO_COLOR_TIMEOUT)
    {
        if(h_g_fac_dialog_svctx != NULL_HANDLE)
        {
            c_svctx_close(h_g_fac_dialog_svctx);
            h_g_fac_dialog_svctx = NULL_HANDLE;
        }
        a_amb_enable_system_key(TRUE);
        nav_send_sim_rc_key_event(BTN_PSUDO_AUTO_FAIL);
        c_timer_stop(t_g_nav_fac_dialog.h_auto_color_timer);
        c_timer_delete(t_g_nav_fac_dialog.h_auto_color_timer);
    }
}
#endif

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_T     e_dialog_id,
                                                UTF16_T*            pw2s_msg,
                                                wgl_widget_proc_fct pf_wdgt_proc)
{
    INT32                       i4_ret =  NAVR_OK;
    NAV_FAC_DIALOG_T*  pt_this = &t_g_nav_fac_dialog;
    //NAV_FAC_DIALOG_SHOW_INIT_T     t_nav_fac_dialog_init;  //ke_vizio_20141118 mark

    #if 0  //ke_vizio_20141119 mark
    /* Hide the previous */
    if(pt_this->e_dialog_id != NAV_FAC_DIALOG_ID_NULL)
    {
        _nav_fac_dialog_destory(pt_this->h_dialog);
        pt_this->e_dialog_id = NAV_FAC_DIALOG_ID_NULL;
        //pt_this->h_dialog    = NULL_HANDLE;  //ke_vizio_20141118 mark
    }
    #endif
	DBG_LOG_PRINT(("[INX-AT] %s,%d h_dialog = %d \r\n",__FUNCTION__,__LINE__,pt_this->h_dialog));
    /* Create the dialog */
    if(pt_this->e_dialog_id != e_dialog_id)
    {
        #if 0  //ke_vizio_20141118 modify
        c_memset(&t_nav_fac_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

        t_nav_fac_dialog_init.h_parent                       = pt_this->h_canvas;
        t_nav_fac_dialog_init.pf_wdgt_proc                   = pf_wdgt_proc;
        t_nav_fac_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
        t_nav_fac_dialog_init.pt_rect                        = NULL;

        i4_ret = _nav_fac_dialog_create(&t_nav_fac_dialog_init,
                                  &pt_this->h_dialog);
        if(i4_ret != APP_UIR_OK)
        {
            return NAVR_FAIL;
        }
        #endif
        pt_this->e_dialog_id = e_dialog_id;
    }

    /* Modify the attribute */
    i4_ret = _nav_fac_dialog_set_text(pt_this->h_dialog, pw2s_msg);
    if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}

    /* If the Dialog component is not active componet, Grab activation.
       Otherwise, set focus to current dialog*/
    if(nav_get_active_component() != NAV_COMP_ID_FAC_DIALOG)
    {
        i4_ret = nav_grab_activation(NAV_COMP_ID_FAC_DIALOG);
    }
    else
    {
        _nav_fac_dialog_set_focus(pt_this->h_dialog, FALSE);
        _nav_fac_dialog_show(pt_this->h_dialog);
        c_wgl_repaint(pt_this->h_dialog, NULL, TRUE);
    }


    /* restart the timer */
    t_g_nav_fac_dialog.ui4_timer_delay = BKLIGHT_TIMER_DELAY_1MIN;
    _nav_fac_dialog_hide_timer_start(t_g_nav_fac_dialog.ui4_timer_delay);

    return 0;
}
//#if 1
static INT32 _nav_fac_dialog_prompt_msg_dialog_ex_2(
                                            NAV_FAC_DIALOG_ID_T     e_dialog_id,
                                            UTF16_T*            pw2s_msg_1,
                                            UTF16_T*            pw2s_msg_2,
                                            GL_RECT_T*          pt_rect,
                                            wgl_widget_proc_fct pf_wdgt_proc)
{
    INT32                       i4_ret;
    NAV_FAC_DIALOG_T*  pt_this = &t_g_nav_fac_dialog;
    NAV_FAC_DIALOG_SHOW_INIT_T     t_nav_fac_dialog_init;

    /* Hide the previous */
    if(pt_this->e_dialog_id != NAV_FAC_DIALOG_ID_NULL)
    {
        _nav_fac_dialog_destory(pt_this->h_dialog);
        pt_this->e_dialog_id = NAV_FAC_DIALOG_ID_NULL;
        //pt_this->h_dialog    = NULL_HANDLE;    //ke_vizio_20141118 mark
    }

    /* Create the dialog */
    if(pt_this->e_dialog_id != e_dialog_id)
    {
        #if 0  //ke_vizio_20141118 modify
        c_memset(&t_nav_fac_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

        t_nav_fac_dialog_init.h_parent                       = pt_this->h_canvas;
        t_nav_fac_dialog_init.pf_wdgt_proc                   = pf_wdgt_proc;
        t_nav_fac_dialog_init.ui2_txt_align_type             = WGL_AS_LEFT_TOP; //WGL_AS_CENTER_TOP;
        t_nav_fac_dialog_init.pt_rect                        = pt_rect;
        i4_ret = _nav_fac_dialog_create(&t_nav_fac_dialog_init,
                                  &pt_this->h_dialog);
        if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}
        #endif
        pt_this->e_dialog_id = e_dialog_id;
    }

    /* Modify the attribute */
    i4_ret = _nav_fac_dialog_set_text(pt_this->h_dialog, pw2s_msg_1);
    if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}
    /* Create the dialog */
    if(pt_this->e_dialog_id != e_dialog_id)
    {
        c_memset(&t_nav_fac_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

        t_nav_fac_dialog_init.h_parent                       = pt_this->h_canvas;
        t_nav_fac_dialog_init.pf_wdgt_proc                   = pf_wdgt_proc;
        t_nav_fac_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_BOTTOM;
        t_nav_fac_dialog_init.pt_rect                        = pt_rect;
        i4_ret = _nav_fac_dialog_create(&t_nav_fac_dialog_init,
                                  &pt_this->h_dialog);
        if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}
        pt_this->e_dialog_id = e_dialog_id;
    }
    i4_ret = _nav_fac_dialog_set_text_2(pt_this->h_dialog, pw2s_msg_2);
    if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}
    /* If the Dialog component is not active componet, Grab activation.
       Otherwise, set focus to current dialog*/
    if(nav_get_active_component() != NAV_COMP_ID_FAC_DIALOG)
    {
        i4_ret = nav_grab_activation(NAV_COMP_ID_FAC_DIALOG);
    }
    else
    {
        _nav_fac_dialog_set_focus(pt_this->h_dialog, FALSE);
        _nav_fac_dialog_show(pt_this->h_dialog);
        c_wgl_repaint(pt_this->h_dialog, NULL, TRUE);
    }

    /* restart the timer */
    t_g_nav_fac_dialog.ui4_timer_delay = NAV_FAC_DIALOG_DEFAULT_TIMER_DELAY;
    _nav_fac_dialog_hide_timer_start(t_g_nav_fac_dialog.ui4_timer_delay);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_prompt_msg_dialog_2(
    NAV_FAC_DIALOG_ID_T     e_dialog_id,
    UTF16_T*            pw2s_msg_1,
    UTF16_T*            pw2s_msg_2,
    wgl_widget_proc_fct pf_wdgt_proc
    )
{
    return _nav_fac_dialog_prompt_msg_dialog_ex_2(e_dialog_id,
                                           pw2s_msg_1,
                                           pw2s_msg_2,
                                           NULL,
                                           pf_wdgt_proc);
}

#ifdef SUPPORT_AUTO_COLOR_KEY
/*-----------------------------------------------------------------------------
 * Name _nav_fac_dialog_default_msg_proc
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_default_msg_proc(
    HANDLE_T            h_widget,
    UINT32              ui4_msg,
    VOID*               pv_param1,
    VOID*               pv_param2)
{
    switch(ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;

            _nav_fac_dialog_hide_timer_start(t_g_nav_fac_dialog.ui4_timer_delay);

            switch(ui4_keycode)
            {
                case BTN_PSUDO_AUTO_DONE:
                   if(h_g_fac_dialog_svctx != NULL_HANDLE)
                   {
                       c_svctx_close(h_g_fac_dialog_svctx);
                       h_g_fac_dialog_svctx = NULL_HANDLE;
                   }
                   _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_AUTO_DONE,
                                                                                MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_AUTO_COLOR_DONE),
                                                                                NULL);
                return WGLR_OK;
                case BTN_PSUDO_AUTO_FAIL:
                   if(h_g_fac_dialog_svctx != NULL_HANDLE)
                   {
                       c_svctx_close(h_g_fac_dialog_svctx);
                       h_g_fac_dialog_svctx = NULL_HANDLE;
                   }
                   _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_AUTO_FAIL,
                                                                                MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_AUTO_COLOR_FAIL),
                                                                                NULL);
                return WGLR_OK;
            default:
                nav_rcu_key_handler(ui4_keycode);
                return WGLR_OK;
            }
        }

        default:
            break;
    }

    return a_ui_simple_dialog_default_msg_proc(h_widget,
                                               ui4_msg,
                                               pv_param1,
                                               pv_param2);
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern NAV_FAC_DIALOG_ID_T nav_fac_dialog_get_crnt_id(VOID)
{
    NAV_FAC_DIALOG_T*  pt_this = &t_g_nav_fac_dialog;

    return pt_this->e_dialog_id;
}

/*----------------------------------------------------------------------------
* Name: _nav_fac_volume_setting
* Description: Setting Audio Volume value.
* Returns:
----------------------------------------------------------------------------*/
static VOID _nav_fac_volume_setting(INT32 i4_val)    //Soar Add 20081015
{
    INT16 i2_aud_volume;

    i2_aud_volume = (INT16)i4_val;

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
    		   i2_aud_volume);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));

}

/*----------------------------------------------------------------------------
* Name: _nav_fac_acg_setting
* Description: Setting Audio auto gain control.
* Returns:
----------------------------------------------------------------------------*/
static VOID _nav_fac_agc_setting(BOOL b_enable)
{
    a_cfg_set_agc(b_enable);
    a_cfg_update_agc();
}

/*----------------------------------------------------------------------------
* Name: _nav_fac_blacklight_setting
* Description: Setting Video blacklight value.
* Returns:
----------------------------------------------------------------------------*/
static VOID _nav_fac_blacklight_setting(INT32 i4_val)    //jeff 20090107 modify
{
    INT32 i4_ret;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT);
    i4_ret = a_cfg_av_set(ui2_id, (INT16)i4_val);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<ACFG> a_cfg_av_set fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
    }

    a_cfg_av_update(ui2_id);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<ACFG> a_cfg_av_set fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
    }

}
//#if 1
/*----------------------------------------------------------------------------
* Name: _nav_fac_picmode_setting
* Description: Setting Video Picture Mode.
* Returns:
----------------------------------------------------------------------------*/
static VOID _nav_fac_picmode_setting(UINT16 ui2_idx)    //Soar Add 20081015
{
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 ui2_idx);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
}
//#endif
/*----------------------------------------------------------------------------
* Name: _nav_fac_colortemp_setting
* Description: Setting Video Color Temp.
* Returns:
----------------------------------------------------------------------------*/
static VOID _nav_fac_color_temp_setting(UINT16 ui2_idx)    //Soar Add 20081015
{
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), ui2_idx);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
}
#if 0
/*----------------------------------------------------------------------------
* Name: _nav_fac_dcr_setting
* Description: Setting dcr.
* Returns:
----------------------------------------------------------------------------*/
static VOID _nav_fac_dcr_setting(UINT16 ui2_idx)    //Jeff 20090107 add
{
	INT16 i2_adp_back_light;
#if 0
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_CUSTOM_DCR);
    INT16   i2_val = ui2_idx;

    a_cfg_av_set(ui2_id, i2_val);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_CUSTOM_DCR));

#else	//kyo_20091202 modify
	if(ui2_idx == 0)
	{
		i2_adp_back_light = 0;
	}
	else
	{
		i2_adp_back_light = 2;
	}
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_DCR), (INT16)ui2_idx);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT), i2_adp_back_light);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_DCR));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
#endif
}
#endif
//#if 1
/*----------------------------------------------------------------------------
* Name: _nav_fac_aud_mts_setting
* Description: Setting Audio MTS mode.
* Returns:
----------------------------------------------------------------------------*/
static VOID _nav_fac_aud_mts_setting(UINT16 ui2_idx)
{
    SCC_AUD_MTS_T   e_aud_ch;
    UINT16          ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS);
    switch(ui2_idx)
    {
        case 0: /* MONO */
            e_aud_ch = SCC_AUD_MTS_MONO;
            break;
        case 1: /* STEREO */
            e_aud_ch = SCC_AUD_MTS_NICAM_STEREO;
            break;
        case 2: /* DUAL1 */
            e_aud_ch = SCC_AUD_MTS_NICAM_DUAL1;
            break;
        case 3: /* DUAL2 */
            e_aud_ch = SCC_AUD_MTS_NICAM_DUAL2;
            break;
        default:
            e_aud_ch = SCC_AUD_MTS_NICAM_STEREO;
            break;
    }
    a_cfg_av_set(ui2_id, (INT16)e_aud_ch);
    a_cfg_av_update(ui2_id);
}
//#endif
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name : a_INX_fac_dialog_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_INX_fac_dialog_register(VOID)
{
    NAV_COMP_T      t_comp;
    INT32           i4_ret;

    //DBG_LOG_PRINT(("!!!!@djh %s :\n", __func__));

    c_memset(&t_comp,0,sizeof(NAV_COMP_T));
    /* NAV_COMP_ID_DIALOG */
    t_comp.pf_init           = _nav_fac_dialog_init;
    t_comp.pf_deinit         = _nav_fac_dialog_deinit;
    t_comp.pf_is_key_handler = _nav_fac_dialog_is_key_handler;
    t_comp.pf_activate       = _nav_fac_dialog_activate;
    t_comp.pf_inactivate     = _nav_fac_dialog_inactivate;
    t_comp.pf_hide           = _nav_fac_dialog_hide;
    t_comp.pf_handle_msg     = _nav_fac_dialog_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_FAC_DIALOG, &t_comp, COMP_EXC_SET_FAC_DIALOG);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name : nav_fac_urc_key_pre_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern VOID nav_fac_urc_key_pre_handler(UINT32 ui4_keystatus, UINT32* pt_ui4_keycode)
{
    UINT32          ui4_fac_val;
    INT32   i4_ret;
    UINT32 ui4_keycode = *pt_ui4_keycode;


	//DBG_LOG_PRINT(("!!!!@djh %s, 0x%X :\n", __func__, ui4_keycode));

    a_cfg_cust_fac_get(&ui4_fac_val);//jeff 20090107 add

	//DBG_LOG_PRINT(("!!!!@djh: ui4_keycode=0x%X,ui4_fac_val=0x%X:\n",ui4_keycode,ui4_fac_val));

    if(ui4_keystatus == WGL_MSG_KEY_DOWN)
    {
        if((ui4_keycode == BTN_FAC_TEST)&&
            (ui4_keystatus == WGL_MSG_KEY_DOWN)&&
            (ui4_fac_val & APP_CFG_CUST_FAC_RC_CHECK))
        {
            ui4_fac_val = ui4_fac_val | APP_CFG_CUST_FAC_RC_ON;
            i4_ret = a_cfg_cust_fac_set(ui4_fac_val);
            if(i4_ret !=0)
            {
               DBG_LOG_PRINT(("!!!!%s : a_cfg_cust_fac_set fail\n", __func__));
            }

            a_tv_net_disable_keyroute(TRUE);  //ke_vizio_20121018 add for keypad test

            //ke_vizio_20130320 disable POWER key watchdog for keypad test.
            // coz audio no output sound.
            a_tv_net_send_cmd(":dtv_app_mtk,am,:disable_PKWD\n");
        }
        else
        {
            ui4_fac_val = ui4_fac_val & ~APP_CFG_CUST_FAC_RC_CHECK;
            i4_ret = a_cfg_cust_fac_set(ui4_fac_val);
            if(i4_ret !=0)
            {
               DBG_LOG_PRINT(("!!!!%s : a_cfg_cust_fac_set fail\n", __func__));
            }
        }

    }

	//DBG_LOG_PRINT(("!!!!@djh: ui4_keycode=0x%X,ui4_fac_val=0x%X:\n",ui4_keycode,ui4_fac_val));

    if (ui4_fac_val & APP_CFG_CUST_FAC_RC_ON)
    {
        if(ui4_keycode == BTN_FAC_DIGIT_0)
            ui4_keycode = BTN_DIGIT_0;
        if(ui4_keycode == BTN_FAC_DIGIT_1)
            ui4_keycode = BTN_DIGIT_1;
        if(ui4_keycode == BTN_FAC_DIGIT_2)
            ui4_keycode = BTN_DIGIT_2;
        if(ui4_keycode == BTN_FAC_DIGIT_3)
            ui4_keycode = BTN_DIGIT_3;
        if(ui4_keycode == BTN_FAC_DIGIT_4)
            ui4_keycode = BTN_DIGIT_4;
        if(ui4_keycode == BTN_FAC_DIGIT_5)
            ui4_keycode = BTN_DIGIT_5;
        if(ui4_keycode == BTN_FAC_DIGIT_6)
            ui4_keycode = BTN_DIGIT_6;
        if(ui4_keycode == BTN_FAC_DIGIT_7)
            ui4_keycode = BTN_DIGIT_7;
        if(ui4_keycode == BTN_FAC_DIGIT_8)
            ui4_keycode = BTN_DIGIT_8;
        if(ui4_keycode == BTN_FAC_DIGIT_9)
            ui4_keycode = BTN_DIGIT_9;
        //if(ui4_keycode == BTN_FAC_S_EFFECT)	//mind 20160510
        //    ui4_keycode = BTN_S_EFFECT;
//        if(ui4_keycode == BTN_FAC_P_EFFECT) //Denny 2011/03/17 mark
//            ui4_keycode = BTN_P_EFFECT;
        if(ui4_keycode == BTN_FAC_FR)
        #ifndef APP_DVBT_SUPPORT
            ui4_keycode=BTN_CC;
        #else
            ui4_keycode = BTN_FR;
        #endif
        if(ui4_keycode == BTN_FAC_SELECT)
            ui4_keycode = BTN_SELECT;//BTN_CURSOR_RIGHT;//BTN_SELECT;	//mind 20160511
        if(ui4_keycode == BTN_FAC_MUTE)
            ui4_keycode = BTN_MUTE;
        if(ui4_keycode == BTN_FAC_PRG_DOWN)
            ui4_keycode = BTN_PRG_DOWN;
        if(ui4_keycode == BTN_FAC_PRG_UP)
            ui4_keycode = BTN_PRG_UP;
		if(ui4_keycode == BTN_FAC_UP)	//kyo_20120207
            ui4_keycode = BTN_CURSOR_UP;
		if(ui4_keycode == BTN_FAC_DOWN)
            ui4_keycode = BTN_CURSOR_DOWN;
    }
    else
    {
        #if 0  //ke_test_fac
        if((ui4_keycode == BTN_FAC_YPBPR)||
            (ui4_keycode == BTN_FAC_HDMI)||
            (ui4_keycode == BTN_FAC_AV)||
            (ui4_keycode == BTN_FAC_VGA)||
            (ui4_keycode == BTN_FAC_USB))
        {
            ui4_keycode = BTN_INVALID;
        }
        #endif
	}
    #ifndef APP_DVBT_SUPPORT  //jeff 20090319 add
	if((ui4_keycode == BTN_CC) &&
		(ui4_fac_val & APP_CFG_CUST_FAC_RC_ON))
		{
		nav_fac_urc_dialog_hide();
		}
	#else
	if((ui4_keycode == BTN_FR) &&
		(ui4_fac_val & APP_CFG_CUST_FAC_RC_ON) &&
		a_nav_ttx_is_show_ttx())
		{
		nav_fac_urc_dialog_hide();
		}
    #endif

    *pt_ui4_keycode = ui4_keycode;

}

/*-----------------------------------------------------------------------------
 * Name : nav_fac_keypad_test
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern INT32 nav_fac_keypad_test(UINT32 ui4_keystatus,UINT32 * pt_ui4_keycode)
{
    UINT32 ui4_keycode = *pt_ui4_keycode;

    if (a_cfg_cust_fac_get_urc_flag() == 1)   // fac keypad test,joe.zy fix 0830
    {
        if(ui4_keystatus == WGL_MSG_KEY_DOWN)
        {
        	DBG_LOG_PRINT(("%s%d [INX_AT]a_cfg_cust_fac_get_urc_flag = 1 \n",__FUNCTION__,__LINE__));
            switch(ui4_keycode)
            {
                case BTN_PRG_UP:     /* Ch + */
					a_cfg_cust_fac_set_keypad_status_read(ACFG_FAC_KEYPAD_CH_INC);
                    break;
                case BTN_PRG_DOWN:   /* Ch - */
					a_cfg_cust_fac_set_keypad_status_read(ACFG_FAC_KEYPAD_CH_DEC);
                    break;
                case BTN_VOL_UP:     /* Vol + */
					a_cfg_cust_fac_set_keypad_status_read(ACFG_FAC_KEYPAD_VOL_INC);
                    break;
                case BTN_VOL_DOWN:   /* Vol - */
					a_cfg_cust_fac_set_keypad_status_read(ACFG_FAC_KEYPAD_VOL_DEC);
                    break;
                case BTN_INPUT_SRC:       /* Input Source */
					a_cfg_cust_fac_set_keypad_status_read(ACFG_FAC_KEYPAD_INPUT);
                    break;
                case BTN_FAC_KEYPAD_POWER:  //BTN_CUSTOM_10:        /* Power */
					a_cfg_cust_fac_set_keypad_status_read(ACFG_FAC_KEYPAD_POWER);
                    break;
                case BTN_FAC_KEYPAD_MENU: //BTN_CUSTOM_11:     /* Menu*/
					a_cfg_cust_fac_set_keypad_status_read(ACFG_FAC_KEYPAD_MENU);
                    break;
                default:
                    break;
            }
        }
        *pt_ui4_keycode = BTN_INVALID;
    }
	if (inx_cfg_cust_fac_get_ir_key_flag() == 1)   // fac ir test
    {
    	DBG_LOG_PRINT(("%s%d [INX_AT] inx_cfg_cust_fac_get_ir_key_flag = 1 \n",__FUNCTION__,__LINE__));
        if(ui4_keystatus == WGL_MSG_KEY_DOWN)
        {
        	DBG_LOG_PRINT(("%s%d ui4_keystatus = %d \n",__FUNCTION__,__LINE__,ui4_keystatus));
            switch(ui4_keycode)
            {
            		case BTN_CURSOR_UP: //up
            			inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_UP);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_UP = %d",ACFG_FAC_IR_KEY_UP));
						DBG_LOG_PRINT(("INX_BTN_CURSOR_UP = %d",BTN_CURSOR_UP));
						break;
					case BTN_CURSOR_DOWN: //down
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_DOWN);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_DOWN = %d",ACFG_FAC_IR_KEY_DOWN));
						DBG_LOG_PRINT(("INX_BTN_CURSOR_DOWN = %d",BTN_CURSOR_DOWN));
						break;
					case BTN_CURSOR_LEFT: //LEFT
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_LEFT);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_LEFT = %d",ACFG_FAC_IR_KEY_LEFT));
						DBG_LOG_PRINT(("INX_BTN_CURSOR_LEFT = %d",BTN_CURSOR_LEFT));
						break;
					case BTN_CURSOR_RIGHT: //RIGHT
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_RIGHT);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_RIGHT = %d",ACFG_FAC_IR_KEY_RIGHT));
						DBG_LOG_PRINT(("INX_BTN_CURSOR_RIGHT = %d",BTN_CURSOR_RIGHT));
						break;
					case BTN_PRG_UP: //PRG UP
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_PRG_UP);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_PRG_UP = %d",ACFG_FAC_IR_KEY_PRG_UP));
						DBG_LOG_PRINT(("INX_BTN_PRG_UP = %d",BTN_PRG_UP));
						break;
					case BTN_PRG_DOWN: //PRG DOWN
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_PRG_DOWN);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_PRG_DOWN = %d",ACFG_FAC_IR_KEY_PRG_DOWN));
						DBG_LOG_PRINT(("INX_BTN_PRG_DOWN = %d",BTN_PRG_DOWN));
						break;
					case BTN_MTS: //MTS
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_MTS);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_MTS = %d",ACFG_FAC_IR_KEY_MTS));
						DBG_LOG_PRINT(("INX_BTN_MTS = %d",BTN_MTS));
						break;
					case BTN_CC: //CC
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_CC);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_CC = %d",ACFG_FAC_IR_KEY_CC));
						DBG_LOG_PRINT(("INX_BTN_CC = %d",BTN_CC));
						break;
					case BTN_WIDE_MODE: //WIDE MODE
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_WIDE_MODE);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_CC = %d",ACFG_FAC_IR_KEY_WIDE_MODE));
						DBG_LOG_PRINT(("INX_BTN_CC = %d",BTN_WIDE_MODE));
						break;
#if 0  /* NOT FIND IR EVT KEY */

					case 0x0A: //TOOLS
						break;
#endif
					case BTN_DIGIT_0: //KEY 0
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_NUM_0);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_NUM_0 = %d",ACFG_FAC_IR_KEY_NUM_0));
						DBG_LOG_PRINT(("INX_BTN_DIGIT_0 = %d",BTN_DIGIT_0));
						break;
					case BTN_DIGIT_1: //KEY 1
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_NUM_1);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_NUM_1 = %d",ACFG_FAC_IR_KEY_NUM_1));
						DBG_LOG_PRINT(("INX_BTN_DIGIT_1 = %d",BTN_DIGIT_1));
						break;
					case BTN_DIGIT_2: //KEY 2
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_NUM_2);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_NUM_2 = %d",ACFG_FAC_IR_KEY_NUM_2));
						DBG_LOG_PRINT(("INX_BTN_DIGIT_2 = %d",BTN_DIGIT_2));
						break;
					case BTN_DIGIT_3: // KEY 3
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_NUM_3);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_NUM_3 = %d",ACFG_FAC_IR_KEY_NUM_3));
						DBG_LOG_PRINT(("INX_BTN_DIGIT_3 = %d",BTN_DIGIT_3));
						break;
					case BTN_DIGIT_4: // KEY 4
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_NUM_4);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_NUM_4 = %d",ACFG_FAC_IR_KEY_NUM_4));
						DBG_LOG_PRINT(("INX_BTN_DIGIT_4 = %d",BTN_DIGIT_4));
						break;
					case BTN_DIGIT_5: //KEY 5
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_NUM_5);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_NUM_5 = %d",ACFG_FAC_IR_KEY_NUM_5));
						DBG_LOG_PRINT(("INX_BTN_DIGIT_5 = %d",BTN_DIGIT_5));
						break;
					case BTN_DIGIT_6: //KEY 6
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_NUM_6);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_NUM_6 = %d",ACFG_FAC_IR_KEY_NUM_6));
						DBG_LOG_PRINT(("INX_BTN_DIGIT_6 = %d",BTN_DIGIT_6));
						break;
					case BTN_DIGIT_7: //KEY 7
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_NUM_7);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_NUM_7 = %d",ACFG_FAC_IR_KEY_NUM_7));
						DBG_LOG_PRINT(("INX_BTN_DIGIT_7 = %d",BTN_DIGIT_7));
						break;
					case BTN_DIGIT_8: //KEY 8
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_NUM_8);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_NUM_8 = %d",ACFG_FAC_IR_KEY_NUM_8));
						DBG_LOG_PRINT(("INX_BTN_DIGIT_8 = %d",BTN_DIGIT_8));
						break;
					case BTN_DIGIT_9: //KEY 9
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_NUM_9);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_NUM_9 = %d",ACFG_FAC_IR_KEY_NUM_9));
						DBG_LOG_PRINT(("INX_BTN_DIGIT_9 = %d",BTN_DIGIT_9));
						break;
#if 0  /* NOT FIND IR EVT KEY */
					case 0x15: //dash
						break;
					case 0x16: //ENT
						break;
#endif
					case BTN_FAC_IR_KEY_POWER: //POWER
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_POWER);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_POWER = %d",ACFG_FAC_IR_KEY_POWER));
						DBG_LOG_PRINT(("INX_BTN_POWER = %d",BTN_POWER));
						break;
					case BTN_VOL_UP: //volume up
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_VOL_UP);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_VOL_UP = %d",ACFG_FAC_IR_KEY_VOL_UP));
						DBG_LOG_PRINT(("INX_BTN_VOL_UP = %d",BTN_VOL_UP));
						break;
					case BTN_VOL_DOWN: //volume down
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_VOL_DOWN);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_VOL_DOWN = %d",ACFG_FAC_IR_KEY_VOL_DOWN));
						DBG_LOG_PRINT(("INX_BTN_VOL_DOWN = %d",BTN_VOL_DOWN));
						break;
					case BTN_FAC_IR_KEY_MENU: //menu
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_MENU);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_MENU = %d",ACFG_FAC_IR_KEY_MENU));
						DBG_LOG_PRINT(("INX_BTN_MENU = %d",BTN_MENU));
						break;
					case BTN_EXIT: //EXIT
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_EXIT);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_EXIT = %d",ACFG_FAC_IR_KEY_EXIT));
						DBG_LOG_PRINT(("INX_BTN_EXIT = %d",BTN_EXIT));
						break;
					case BTN_RETURN: //BACK
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_BACK);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_BACK = %d",ACFG_FAC_IR_KEY_BACK));
						DBG_LOG_PRINT(("INX_BTN_RETURN = %d",BTN_RETURN));
						break;
					case BTN_PRG_INFO: //INFO
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_INFO);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_INFO = %d",ACFG_FAC_IR_KEY_INFO));
						DBG_LOG_PRINT(("INX_BTN_PRG_INFO = %d",BTN_PRG_INFO));
						break;
					case BTN_INPUT_SRC: //INPUT
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_INPUT);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_INPUT = %d",ACFG_FAC_IR_KEY_INPUT));
						DBG_LOG_PRINT(("INX_BTN_INPUT_SRC = %d",BTN_INPUT_SRC));
						break;
					case BTN_MUTE: //MUTE
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_MUTE);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_MUTE = %d",ACFG_FAC_IR_KEY_MUTE));
						DBG_LOG_PRINT(("INX_BTN_MUTE = %d",BTN_MUTE));
						break;
					case BTN_SELECT: //OK
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_OK);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_OK = %d",ACFG_FAC_IR_KEY_OK));
						DBG_LOG_PRINT(("INX_BTN_SELECT = %d",BTN_SELECT));
						break;
					case BTN_PLAY: //PLAY
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_PLAY);
						DBG_LOG_PRINT(("ACFG_FAC_IR_KEY_OK = %d",ACFG_FAC_IR_PLAY));
						DBG_LOG_PRINT(("INX_BTN_SELECT = %d",BTN_PLAY));
						break;
					default:
						inx_cfg_cust_fac_set_ir_key_status_read(ACFG_FAC_IR_KEY_NONE);
						break;
            }
        }
        *pt_ui4_keycode = BTN_INVALID;
    }
    return 0;
}

//ke_vizio_20130912 add
#ifdef APP_INX_DFT_URC_WIFI
/*-----------------------------------------------------------------------------
 * Name : nav_fac_urc_set_wifi
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_fac_urc_set_wifi(VOID)
{
    INT32 i4_ret;
    UINT8 ui1_i;

    CHAR a_ssid[NET_802_11_MAX_LEN_SSID] = "corega";
    CHAR a_password[128+1]= "0000000000";

    DBG_LOG_PRINT(("SSID: %s\n", a_ssid));

    /* Set Terms of Service*/
    a_tv_custom_set_tos(TRUE);
    a_tv_custom_set_privacy(TRUE);

    /* Switch to Wifi mode */
    i4_ret = nw_custom_get_network_interface(&ui1_i);
    if (i4_ret != NWR_OK)
    {
        DBG_LOG_PRINT(("[Fac] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
        return NAVR_FAIL;
    }
    if(ui1_i!=APP_CFG_NET_INTERFACE_WIFI)
    {
        i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_WIFI);
        if (i4_ret != NWR_OK)
        {
            DBG_LOG_PRINT(("[Fac] a_nw_chg_network_interface(wifi) Fail. Return %d.\n", i4_ret));
            return NAVR_FAIL;
        }
    }


    /* Associate */
    {
        CHAR              s_input_buf[128+1] = {0}; //s_input_buf[WLAN_VKB_MAX_LEN+1]
        NET_802_11_ASSOCIATE_T* pt_associate = NULL;

        pt_associate = (NET_802_11_ASSOCIATE_T*)c_mem_alloc(sizeof(NET_802_11_ASSOCIATE_T));
        c_memset(pt_associate, 0x00, sizeof(NET_802_11_ASSOCIATE_T));
        pt_associate->e_AssocCase = IEEE_802_11_MANUAL_ASSOC;

        pt_associate->t_Ssid.ui4_SsidLen = (UINT32)c_strlen(a_ssid);
        c_memcpy(pt_associate->t_Ssid.ui1_aSsid, a_ssid,(SIZE_T)pt_associate->t_Ssid.ui4_SsidLen);
        c_memset(pt_associate->t_Bssid, 0xff,sizeof(NET_802_11_BSSID_T));

    #if 0
        pt_associate->e_AuthMode  = IEEE_802_11_AUTH_MODE_NONE;
        pt_associate->e_AuthCipher= IEEE_802_11_AUTH_MODE_OPEN;
    #else
        pt_associate->e_AuthMode  = IEEE_802_11_AUTH_MODE_WPA2_PSK;
        pt_associate->e_AuthCipher= IEEE_802_11_AUTH_CIPHER_AES_OR_TKIP;
    #endif

        /* Password phrase */
        c_strcpy(s_input_buf,a_password);
        pt_associate->t_Key.pui1_PassPhrase = s_input_buf;
        pt_associate->t_Key.b_IsAscii = FALSE;

        i4_ret = a_nw_wlan_associate(pt_associate);
        if (i4_ret != NWR_OK)
        {
            DBG_LOG_PRINT(("[Fac] a_nw_wlan_associate() Fail. Return %d.\n", i4_ret));
            return FACTORY_COND_FAIL;
        }
    }

    return NAVR_OK;
}
#endif

#ifdef APP_DFT_LSR_TEST  //ke_vizio_20131220 add
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_fac_dialog_LSR_count(
    VOID*                       pv_tag,
    VOID*                       pv_tag2,
    VOID*                       pv_tag3)
{
    NAV_FAC_DIALOG_T*  pt_this = &t_g_nav_fac_dialog;
    CHAR s_string[10] = {0};
    UTF16_T w2s_buf[10];
    UINT32 ui4_LSR_value = 0;
    DRV_CUST_OPERATION_INFO_T       t_op_info;
    SIZE_T                          z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                          z_size = sizeof(ui4_LSR_value);
    //INT32                           i4_ret = APP_CFGR_OK;

    if((UINT32)pv_tag == 0)
    {
        //DBG_LOG_PRINT("%s Line: %d, pv_tag == 0\n", __FUNCTION__, __LINE__);

        pt_this->b_LSR_time_start = TRUE;

        /* set operation type */
        c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_LIGHT_SENSOR_VALUE;
        t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui4_LSR_value;
        t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

         /*get driver value */
        /*i4_ret =*/ c_rm_get_comp( DRVT_CUST_DRV,
                                DRV_CUST_COMP_ID,
                                FALSE,
                                ANY_PORT_NUM,
                                0,
                                &t_op_info,
                                &z_size_drv
                                );

        c_sprintf(s_string, "%d", ui4_LSR_value);

        c_memset(w2s_buf, 0, 10);
        c_uc_ps_to_w2s(s_string, w2s_buf, c_strlen(s_string));
        _nav_fac_dialog_set_text_2(pt_this->h_dialog, w2s_buf);

        c_wgl_repaint(pt_this->h_dialog, NULL, TRUE);
    }
    else if((UINT32)pv_tag == 1)
    {
        //DBG_LOG_PRINT("%s Line: %d, pv_tag == 1\n", __FUNCTION__, __LINE__);
        pt_this->b_LSR_time_start = FALSE;
        c_memset(w2s_buf, 0, 10);
        _nav_fac_dialog_LSR_timer_stop();
        _nav_fac_dialog_set_text_2(pt_this->h_dialog, w2s_buf);
    }

}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_fac_dialog_LSR_timer_nfy (
    HANDLE_T  h_timer,
    VOID*     pv_tag)
{
    nav_request_context_switch(_nav_fac_dialog_LSR_count,
                               (VOID *)0,
                               NULL,
                               NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_LSR_timer_start(VOID)
{
    INT32 i4_ret = 0;
    i4_ret = c_timer_start(t_g_nav_fac_dialog.h_LSR_timer,
                            100,
                            X_TIMER_FLAG_REPEAT,
                            _nav_fac_dialog_LSR_timer_nfy,
                            NULL);
    if(i4_ret != OSR_OK)
    {
        DBG_LOG_PRINT(("%s Line: %d; c_timer_stop fail\n", __FUNCTION__, __LINE__));
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_dialog_LSR_timer_stop(VOID)
{

    INT32 i4_ret = 0;
    i4_ret = c_timer_stop(t_g_nav_fac_dialog.h_LSR_timer);
    if(i4_ret != OSR_OK)
    {
        DBG_LOG_PRINT(("%s Line: %d; c_timer_stop fail\n", __FUNCTION__, __LINE__));
    }

    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: joe.zy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 INX_fac_burning_off(void)
{
	// if 0x1a022 = 1 then close aging mode
	if(_nav_fac_get_eeprom_flag(INX_EEP_INX_AGING_MODE))
	{
		//return NAVR_FAIL when keypad locked
		if(inx_cfg_cust_fac_get_ir_key_flag() == FALSE)
        {
        	// close aging mode flag
			_nav_fac_set_eeprom_flag(INX_EEP_INX_AGING_MODE,INX_EEP_ADDRESS_NO_WORK);
			// auto poweron off 
			if((_nav_fac_get_eeprom_flag(INX_EEP_WHITE_BALANCE_MODE)) == INX_CHECK_WHITE_BALANCE) // Set 0x1a05e to 0 when 0x1a022=0 and 0x11000 = 0xAA
				_nav_fac_set_eeprom_flag(INX_EEP_AUTO_POWERON,INX_EEP_ADDRESS_NO_WORK);
			nav_fac_set_setup_value(NAV_FAC_MENU_BURN_IN, FALSE);
        }
		else
			return NAVR_FAIL;

	}

    return NAVR_OK;
}

//ke_vizio_20160429 add
VOID INX_custom_rcu_key_pre_handler(
                    NAV_MODEL_T*                pt_this,
                    NAV_EVN_T*                  pt_event
                    )
{

	nav_fac_urc_key_pre_handler(pt_event->ui4_data1, &pt_event->ui4_data2);
	nav_fac_keypad_test(pt_event->ui4_data1, &pt_event->ui4_data2);

#if 0 // test, zl
    if(TRUE == cvt_fac_is_AT_mode())
    {
        DBG_LOG_PRINT(("\033[1;31;40mCVTE debug : %s %s %d	\033[0m\r\n",__FILE__,__FUNCTION__,__LINE__));
        cvt_fac_keypad_test(pt_event->ui4_data1, &pt_event->ui4_data2);
    }
#endif
	return;
}

BOOL INX_custom_system_key_cb(UINT32     ui4_evt_code)
{
    BOOL               b_process = TRUE;

    NAV_EVN_T t_event;

	//DBG_LOG_PRINT(("[INX_AT] APP_CFG_CUST_FAC_RC_ON = %d \n ",APP_CFG_CUST_FAC_RC_ON));
	//DBG_LOG_PRINT(("[INX_AT] IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_POWER) = %d \n ",IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_POWER)));
	//INX_AckString("[INX_AT] ui4_evt_code = %d \n ",ui4_evt_code);
	//INX_AckString("[INX_AT] IOM_GEN_EVT_CODE(KEY_SRC_FRONT_POWER, BTN_POWER) = %d \n ",IOM_GEN_EVT_CODE(KEY_SRC_FRONT_POWER, BTN_POWER));
	//INX_AckString("[INX_AT] IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_MENU) = %d \n ",IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_POWER));
    if( /*test, zl TRUE == cvt_fac_is_AT_mode() ||*/ (a_cfg_cust_fac_get_urc_flag() == 1))
    {
    	DBG_LOG_PRINT(("[INX_AT] a_cfg_cust_fac_get_urc_flag = 1\n"));
        if(ui4_evt_code == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_MENU))
        {
            t_event.ui4_msg_id = NAV_KEY_EVENT;
            t_event.ui4_data1  = WGL_MSG_KEY_DOWN;
            t_event.ui4_data2  = ((UINT32)BTN_FAC_KEYPAD_MENU);
            t_event.ui4_data3  = (UINT32)NULL;
            t_event.ui4_data4  = IOM_GET_EVT_SRC(ui4_evt_code);

            nav_send_msg(&t_event);
            return FALSE;
        }

        if(ui4_evt_code == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_POWER))//joe.zy fix
        {
            t_event.ui4_msg_id = NAV_KEY_EVENT;
            t_event.ui4_data1  = WGL_MSG_KEY_DOWN;
            t_event.ui4_data2  = ((UINT32)BTN_FAC_KEYPAD_POWER);
            t_event.ui4_data3  = (UINT32)NULL;
            t_event.ui4_data4  = IOM_GET_EVT_SRC(ui4_evt_code);

            nav_send_msg(&t_event);
            return FALSE;
        }
    }
	if((inx_cfg_cust_fac_get_ir_key_flag() == 1))
	{
		DBG_LOG_PRINT(("[INX_AT] inx_cfg_cust_fac_get_ir_key_flag = 1\n"));
		if(ui4_evt_code == IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_MENU))
        {
        	DBG_LOG_PRINT(("\n%s,%d KEY_SRC_REMOTE_CTRL BTN_MENU",__FUNCTION__,__LINE__));
            t_event.ui4_msg_id = NAV_KEY_EVENT;
            t_event.ui4_data1  = WGL_MSG_KEY_DOWN;
            t_event.ui4_data2  = ((UINT32)BTN_FAC_IR_KEY_MENU);
            t_event.ui4_data3  = (UINT32)NULL;
            t_event.ui4_data4  = IOM_GET_EVT_SRC(ui4_evt_code);

            nav_send_msg(&t_event);
            return FALSE;
        }

        if(ui4_evt_code == IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_POWER))
        {
        	DBG_LOG_PRINT(("\n%s,%d KEY_SRC_REMOTE_CTRL BTN_POWER",__FUNCTION__,__LINE__));
            t_event.ui4_msg_id = NAV_KEY_EVENT;
            t_event.ui4_data1  = WGL_MSG_KEY_DOWN;
            t_event.ui4_data2  = ((UINT32)BTN_FAC_IR_KEY_POWER);
            t_event.ui4_data3  = (UINT32)NULL;
            t_event.ui4_data4  = IOM_GET_EVT_SRC(ui4_evt_code);

            nav_send_msg(&t_event);
            return FALSE;
        }
	}

    if(cvt_fac_is_burning_mode_runing())
    {
        if(IOM_GET_EVT_GRP_ID(ui4_evt_code) == BTN_MENU)
        {
            return FALSE;
        }

        if(IOM_GET_EVT_GRP_ID(ui4_evt_code) == BTN_POWER)
        {
            if(IOM_GET_EVT_SRC(ui4_evt_code) == KEY_SRC_REMOTE_CTRL) //IR
            {
                return FALSE;
            }
            else if(IOM_GET_EVT_SRC(ui4_evt_code) == KEY_SRC_FRONT_PANEL)  // KEYPAD
            {
                cvt_fac_burnning_mode_run(0);
                a_amb_power_on(FALSE);
                return TRUE;
            }
        }
    }
    
    return b_process;

}

#ifdef APP_INX_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
INT32 INX_FACTORY_WIFI_AUTODETECT(VOID)
{
    INT32 i4_ret = 0;
    CHAR  s_input_buf[128+1] = {0};
    NET_802_11_ASSOCIATE_T* pt_associate = NULL;
    UINT8 ui1_i;

    CHAR a_ssid[NET_802_11_MAX_LEN_SSID] = "Pixel_fish";
    CHAR a_password[128+1]= "00000000";

#if 0 //joe.zy modify
    UINT8 ui1_odm_index = 0;

    INX_fac_set_WIFI_status(FALSE);  // Reset the connect status

    a_cfg_custom_get_odm_index(&ui1_odm_index);
    if(ui1_odm_index != 2){
        DBG_LOG_PRINT(("INX_FACTORY_WIFI_AUTODETECT ODM ID : %d\n", ui1_odm_index));
        return INX_FACTORY_COND_INV_ARG;
    }
#endif
    /* Set Terms of Service*/
    a_tv_custom_set_tos(TRUE);
    a_tv_custom_set_privacy(TRUE);

    /* Switch to Wifi mode */
    i4_ret = nw_custom_get_network_interface(&ui1_i);
    if (i4_ret != NWR_OK)
    {
        DBG_LOG_PRINT(("[Fac] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
        return NAVR_FAIL;
    }
    if(ui1_i!=APP_CFG_NET_INTERFACE_WIFI)
    {
        i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_WIFI);
        if (i4_ret != NWR_OK)
        {
            DBG_LOG_PRINT(("[Fac] a_nw_chg_network_interface(wifi) Fail. Return %d.\n", i4_ret));
            return NAVR_FAIL;
        }
    }

    pt_associate = (NET_802_11_ASSOCIATE_T*)c_mem_alloc(sizeof(NET_802_11_ASSOCIATE_T));
	if(pt_associate == NULL)
	{
		DBG_INFO(("[Fac] a_nw_wlan_associate() pt_associate is NULL\n"));
		return INX_FACTORY_COND_FAIL;
	}
    c_memset(pt_associate, 0x00, sizeof(NET_802_11_ASSOCIATE_T));
    pt_associate->e_AssocCase = IEEE_802_11_MANUAL_ASSOC;

    pt_associate->t_Ssid.ui4_SsidLen = (UINT32)c_strlen(a_ssid);
    c_memcpy(pt_associate->t_Ssid.ui1_aSsid, a_ssid,(SIZE_T)pt_associate->t_Ssid.ui4_SsidLen);
    c_memset(pt_associate->t_Bssid, 0xff,sizeof(NET_802_11_BSSID_T));

    pt_associate->e_AuthMode  = IEEE_802_11_AUTH_MODE_NONE;
    pt_associate->e_AuthCipher= IEEE_802_11_AUTH_CIPHER_NONE;

    /* Password phrase => Ignored */
    c_strcpy(s_input_buf, a_password);
    pt_associate->t_Key.pui1_PassPhrase = s_input_buf;
    pt_associate->t_Key.b_IsAscii = FALSE;

    i4_ret = a_nw_wlan_associate(pt_associate);

	if(pt_associate != NULL)
	{
		c_mem_free(pt_associate);
		pt_associate = NULL;
	}

	if (i4_ret != NWR_OK)
    {
        DBG_INFO(("[Fac] a_nw_wlan_associate() Fail. Return %d.\n", i4_ret));
        return INX_FACTORY_COND_FAIL;
    }

    return INX_FACTORY_COND_OK;
}

static VOID _auto_detect_nw_notify_handler(
    VOID*          pv_tag1,
    VOID*          pv_tag2,
    VOID*          pv_tag3
)
{
    NW_NFY_ID_T         e_nfy_id = (NW_NFY_ID_T)((UINT32)pv_tag2);

    switch (e_nfy_id)
    {
        case NW_NFY_ID_DHCP_SUCCESS_DHCPv4:
        {
            NET_802_11_SSID_T       t_Ssid;
            UINT8 ui1_status = 0;
            UINT32 ui4_read;

            a_cfg_eep_raw_read(EEP_WIFI_SSID_ON, &ui1_status, 1, &ui4_read);

            if(ui1_status == 0xAA)
            {
                c_memset (&t_Ssid, 0, sizeof(t_Ssid));

                a_nw_get_wlan_ssid(&t_Ssid);
                DBG_LOG_PRINT(("SSID: %s\n", t_Ssid.ui1_aSsid));
                if(c_strcmp(t_Ssid.ui1_aSsid, "iptvwifi_test") != 0)
                {
                    DBG_LOG_PRINT(("%s Line: %d, INX_FACTORY_WIFI_AUTODETECT\n", __FUNCTION__, __LINE__));
                    INX_FACTORY_WIFI_AUTODETECT();
                }
                else
                {
                    INX_fac_set_WIFI_status(TRUE);
                }
            }
            break;
        }
        case NW_NFY_ID_WLAN_SCAN:
        {
            INX_fac_set_WIFI_status(FALSE);
            break;
        }

        default:
            break;
    }
}


/*----------------------------------------------------------------------------
 * Name: _auto_detect_notify_callback
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
static VOID _auto_detect_nw_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    nav_request_context_switch(_auto_detect_nw_notify_handler,
                              (VOID*)pv_tag,
                              (VOID*)e_nfy_id,
                              (VOID*)pv_nfy_param);
}
/*----------------------------------------------------------------------------
 * Name: _auto_detect_notify_callback
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
VOID INX_fac_set_WIFI_status(BOOL b_connect)
{
    b_INX_wifi_connect_status = b_connect;
}
/*----------------------------------------------------------------------------
 * Name: _auto_detect_notify_callback
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

BOOL INX_fac_get_WIFI_status(VOID)
{
    return b_INX_wifi_connect_status;
}

#endif /* end of APP_INX_DFT_WIFI_AUTO_DETECTION */
#if 1

INT32 inx_connect_wifi(CHAR* a_ssid,CHAR* a_password)
{
	INT32 i4_ret = 0;
    CHAR  s_input_buf[128+1] = {0};
    NET_802_11_ASSOCIATE_T* pt_associate = NULL;
    UINT8 ui1_i;
    //CHAR a_ssid[NET_802_11_MAX_LEN_SSID] = "NETGEAR38";
    //CHAR a_password[128+1]= "55016680";

#if 0 //joe.zy modify
    UINT8 ui1_odm_index = 0;

    INX_fac_set_WIFI_status(FALSE);  // Reset the connect status

    a_cfg_custom_get_odm_index(&ui1_odm_index);
    if(ui1_odm_index != 2){
        DBG_LOG_PRINT(("INX_FACTORY_WIFI_AUTODETECT ODM ID : %d\n", ui1_odm_index));
        return INX_FACTORY_COND_INV_ARG;
    }
#endif
    /* Set Terms of Service*/
    a_tv_custom_set_tos(TRUE);
    a_tv_custom_set_privacy(TRUE);

    if( a_password ){
        /* Switch to Wifi mode */
        i4_ret = nw_custom_get_network_interface(&ui1_i);
        if (i4_ret != NWR_OK)
        {
            DBG_LOG_PRINT(("[Fac] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
            return NAVR_FAIL;
        }
        if(ui1_i!=APP_CFG_NET_INTERFACE_WIFI)
        {
            i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_WIFI);
            if (i4_ret != NWR_OK)
            {
                DBG_LOG_PRINT(("[Fac] a_nw_chg_network_interface(wifi) Fail. Return %d.\n", i4_ret));
                return NAVR_FAIL;
            }
        }
    }

    pt_associate = (NET_802_11_ASSOCIATE_T*)c_mem_alloc(sizeof(NET_802_11_ASSOCIATE_T));
	if(pt_associate == NULL)
	{
		DBG_INFO(("[Fac] a_nw_wlan_associate() pt_associate is NULL\n"));
		return INX_FACTORY_COND_FAIL;
	}

    c_memset(pt_associate, 0x00, sizeof(NET_802_11_ASSOCIATE_T));
    pt_associate->e_AssocCase = IEEE_802_11_MANUAL_ASSOC;

    pt_associate->t_Ssid.ui4_SsidLen = (UINT32)c_strlen(a_ssid);
    c_memcpy(pt_associate->t_Ssid.ui1_aSsid, a_ssid,(SIZE_T)pt_associate->t_Ssid.ui4_SsidLen);
    c_memset(pt_associate->t_Bssid, 0xff,sizeof(NET_802_11_BSSID_T));

    if( a_password == NULL ){//No password
        pt_associate->e_AuthMode  = IEEE_802_11_AUTH_MODE_NONE;
        pt_associate->e_AuthCipher= IEEE_802_11_AUTH_CIPHER_NONE;
    }else{
        pt_associate->e_AuthMode  = IEEE_802_11_AUTH_MODE_WPA2_PSK;
        pt_associate->e_AuthCipher= IEEE_802_11_AUTH_CIPHER_AES_OR_TKIP;
    }
    /* Password phrase => Ignored */
    if( a_password ){
        c_strcpy(s_input_buf, a_password);
        pt_associate->t_Key.pui1_PassPhrase = s_input_buf;
        pt_associate->t_Key.b_IsAscii = FALSE;
    }
    i4_ret = a_nw_wlan_associate(pt_associate);

	//yshu Free memory
	if(pt_associate != NULL)
	{
		c_mem_free(pt_associate);
		pt_associate = NULL;
	}
    if (i4_ret != NWR_OK)
    {
        DBG_INFO(("[Fac] a_nw_wlan_associate() Fail. Return %d.\n", i4_ret));
        return INX_FACTORY_COND_FAIL;
    }

    return INX_FACTORY_COND_OK;
}


#endif
/*----------------------------------------------------------------------------
 * Name: INX_nav_fac_urc_dialog_show
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


INT32 INX_nav_fac_urc_dialog_show(UINT16 str_msg)
{
	
    _nav_fac_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_TEST_MODE_ON,
                                            MLM_FAC_TEXT(nav_get_mlm_lang_id(), str_msg),
                                            NULL);
	

	return NAVR_OK;
}


