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

#ifdef APP_2K12_RETAIL_DEMO_MODE

#include "wizard_anim/wzd.h"
#include "app_util/config/_acfg.h"
#include "app_util/a_ui.h"
#include "wizard_anim/page/wzd_page_choose_mode.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "res/app_util/icl/a_icl_custom.h"

typedef struct _WZD_CHO_MODE_MEMBER_T
{
    HANDLE_T                    h_welcome_frm;
    HANDLE_T                    h_dlg;
    HANDLE_T                    h_dialog_frm;
	HANDLE_T                    h_enegry_icon;
    HANDLE_T                    h_store_button;
    HANDLE_T                    h_home_button;
    HANDLE_T                    h_eng_text;
    HANDLE_T                    h_fre_text;
    HANDLE_T                    h_spa_text;
    HANDLE_T                    h_timer;
}WZD_CHO_MODE_MEMBER_T;


WZD_CHO_MODE_MEMBER_T   gt_cho_mode;

#define WZD_CHO_MODE_DLG_FRM_X           ((MAIN_FRM_W - WZD_CHO_MODE_DLG_FRM_W)/2)
#define WZD_CHO_MODE_DLG_FRM_Y           ((MAIN_FRM_H - WZD_CHO_MODE_DLG_FRM_H)/2 - 30 * WZD_UI_RATIO_W)
#define WZD_CHO_MODE_DLG_FRM_W           (580 * WZD_UI_RATIO_W)
#define WZD_CHO_MODE_DLG_FRM_H           (240 * WZD_UI_RATIO_W)

#define WZD_DLG_ENG_TXT_X       (100 * WZD_UI_RATIO_W)
#define WZD_DLG_ENG_TXT_Y       (25 * WZD_UI_RATIO_W)
#define WZD_DLG_ENG_TXT_W       (WZD_CHO_MODE_DLG_FRM_W - 2*WZD_DLG_ENG_TXT_X)
#define WZD_DLG_ENG_TXT_H       (75 * WZD_UI_RATIO_W)

#define WZD_DLG_SPA_TXT_X     	(0)
#define WZD_DLG_SPA_TXT_Y     	(WZD_DLG_ENG_TXT_H + 25 * WZD_UI_RATIO_W)
#define WZD_DLG_SPA_TXT_W     	(WZD_CHO_MODE_DLG_FRM_W)
#define WZD_DLG_SPA_TXT_H     	(22 * WZD_UI_RATIO_W)

#define WZD_DLG_FRE_TXT_X     	(0)
#define WZD_DLG_FRE_TXT_Y     	(WZD_DLG_SPA_TXT_Y + WZD_DLG_FRE_TXT_H)
#define WZD_DLG_FRE_TXT_W     	(WZD_CHO_MODE_DLG_FRM_W)
#define WZD_DLG_FRE_TXT_H     	(22 * WZD_UI_RATIO_W)

#define WZD_BTN01_X             (17 * WZD_UI_RATIO_W)
#define WZD_BTN01_Y             (WZD_DLG_FRE_TXT_Y + WZD_DLG_FRE_TXT_H + 12 * WZD_UI_RATIO_W)
#define WZD_BTN01_W             (270 * WZD_UI_RATIO_W)
#define WZD_BTN01_H             (78 * WZD_UI_RATIO_W)

#define WZD_BTN02_X             (WZD_BTN01_X + WZD_BTN01_W + 6 * WZD_UI_RATIO_W)
#define WZD_BTN02_Y             (WZD_BTN01_Y)
#define WZD_BTN02_W             (WZD_BTN01_W)
#define WZD_BTN02_H             (WZD_BTN01_H)

#define WZD_ENEGRY_ICON_COUNTRY_CODE_X         (WZD_CHO_MODE_DLG_FRM_W - 48 * WZD_UI_RATIO_W)
#define WZD_ENEGRY_ICON_COUNTRY_CODE_Y         (10 * WZD_UI_RATIO_W)
#define WZD_ENEGRY_ICON_COUNTRY_CODE_W         (44 * WZD_UI_RATIO_W)
#define WZD_ENEGRY_ICON_COUNTRY_CODE_H         (44 * WZD_UI_RATIO_W)

static INT32 _wzd_cho_mode_show_energy_logo(BOOL b_show);
static INT32 _wzd_choose_mode_energy_logo_create(VOID);

#ifndef APP_ADD_COUNTRY_CODE_SUPPORT
static INT32 _wzd_choose_mode_dialog_wdgt_proc(HANDLE_T    h_widget,
                                               UINT32      ui4_msg,
                                               VOID*       pv_param1,
                                               VOID*       pv_param2);
#endif

/*----------------------------------------------------------------------------
 * Name: _wzd_store_btn_nfy
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

static VOID _wzd_store_btn_nfy(VOID)
{
    WZD_CHO_MODE_MEMBER_T*      pt_this = &gt_cho_mode;
	UINT8                       ui1_wzd_sts = ICL_WIZARD_STATUS_PAUSE;

	a_icl_set(
            ICL_MAKE_ID(ICL_GRPID_WIZARD_STATUS, ICL_RECID_WIZARD_STATUS),
            (VOID *) &ui1_wzd_sts,
            ICL_RECID_WIZARD_STATUS_SIZE);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));

	c_timer_stop(pt_this->h_timer);

    RETAIL_MODE_PARAM_T t_param;
    c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));

    t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_WZD;
    t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
    t_param.t_launch_info.ui2_count = 15;

    a_nav_retail_mode_start(&t_param);
}

static VOID _wzd_home_btn_nfy(VOID)
{
    WZD_CHO_MODE_MEMBER_T*      pt_this = &gt_cho_mode;
    UINT8                       ui1_wzd_sts = ICL_WIZARD_STATUS_RESUME;

    a_icl_set(
            ICL_MAKE_ID(ICL_GRPID_WIZARD_STATUS, ICL_RECID_WIZARD_STATUS),
            (VOID *) &ui1_wzd_sts,
            ICL_RECID_WIZARD_STATUS_SIZE);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));

    c_timer_stop(pt_this->h_timer);
    wzd_page_goto( WZD_PAGE_NAVI_NEXT_PAGE );
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_cho_mode_timer_nfy
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
static VOID _wzd_cho_mode_timer_nfy(VOID*   pv_data,
                                    SIZE_T  z_data_size)
{
    RETAIL_MODE_PARAM_T t_param;
    c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));

    t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_WZD;
    t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
    t_param.t_launch_info.ui2_count = 15;

    a_nav_retail_mode_start(&t_param);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_cho_mode_timer_cb_fct
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
static VOID _wzd_cho_mode_timer_cb_fct(HANDLE_T  pt_tm_handle,
                                       VOID*     pv_tag)
{
	UINT16  ui2_status;
    UINT8   ui2_page_idx;
    //UINT8   ui2_state;

    a_cfg_get_wzd_status (&ui2_status);

    //ui2_state   = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui2_page_idx = WZD_UTIL_GET_STATUS_IDX(ui2_status);

    if(ui2_page_idx == WZD_PAGE_INDEX_CHO_MODE)
    {
        wzd_async_invoke(_wzd_cho_mode_timer_nfy, NULL, 0, TRUE);
    }
}

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
static INT32 _wzd_store_btn_wgl_nfy_fct(HANDLE_T            h_widget,
                               UINT32              ui4_msg,
                               VOID*               pv_param1,
                               VOID*               pv_param2)
{
	WZD_CHO_MODE_MEMBER_T*      pt_this = &gt_cho_mode;

    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            switch( (UINT32)pv_param1 )
            {
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
					c_timer_start(pt_this->h_timer,
								WZD_CHOOSE_HOME_MODE_TIMER,
								X_TIMER_FLAG_ONCE,
								_wzd_cho_mode_timer_cb_fct,
								NULL);
					_wzd_cho_mode_show_energy_logo(TRUE);
                    c_wgl_set_focus(pt_this->h_home_button, FALSE);
					c_wgl_repaint(pt_this->h_welcome_frm, NULL, TRUE);
                    break;

                case BTN_SELECT:
                    _wzd_store_btn_nfy();
                    break;
                default:
                    break;
            }
        }
        break;

    default:
        break;
    }

    c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );

    return WZDR_OK;
}

static INT32 _wzd_home_btn_wgl_nfy_fct(HANDLE_T            h_widget,
                               UINT32              ui4_msg,
                               VOID*               pv_param1,
                               VOID*               pv_param2)
{
	WZD_CHO_MODE_MEMBER_T*      pt_this = &gt_cho_mode;

    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            switch( (UINT32)pv_param1 )
            {
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
					c_timer_start(pt_this->h_timer,
								WZD_CHOOSE_STORE_MODE_TIMER,
								X_TIMER_FLAG_ONCE,
								_wzd_cho_mode_timer_cb_fct,
								NULL);
					_wzd_cho_mode_show_energy_logo(FALSE);
                    c_wgl_set_focus(pt_this->h_store_button, FALSE);
					c_wgl_repaint(pt_this->h_welcome_frm, NULL, TRUE);
                    break;

                case BTN_SELECT:
                    _wzd_home_btn_nfy();
                    break;
                default:
                    break;
            }
        }
        break;

    default:
        break;
    }

    c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );

    return WZDR_OK;
}

static INT32 _wzd_page_cho_mode_create_txt (
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

    return  0;
}

static INT32 _wzd_page_cho_mode_create_btn(HANDLE_T  h_parent,
                                          GL_RECT_T*  pt_rect,
                                          UTF16_T*    pw2s_btn_text,
                                          wgl_widget_proc_fct     pf_wdgt_proc,
                                          HANDLE_T* ph_widget)
{
    INT32               i4_ret;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_font_info;

    i4_ret = c_wgl_create_widget(h_parent,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                pt_rect,
                                pf_wdgt_proc,
                                255,
                                NULL,
                                NULL,
                                ph_widget);
    RET_ON_ERR(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    RET_ON_ERR(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_wzd_img_button;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_wzd_img_button;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_button_highlight;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_wzd_img_button;
    t_img_info.u_img_data.t_extend.t_push               = h_g_wzd_img_button_highlight;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_wzd_img_button;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(& t_img_info));
    RET_ON_ERR(i4_ret);

    c_memset(&t_color_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_color_info.e_type = WGL_COLOR_SET_EXTEND;
    t_color_info.u_color_data.t_extend.t_enable             = WZD_MODE_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_disable            = WZD_MODE_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_highlight          = WZD_MODE_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_highlight_inactive = WZD_MODE_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_push               = WZD_MODE_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_push_unhighlight   = WZD_MODE_DLG_BTN_TEXT_CLR;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(& t_color_info));
    RET_ON_ERR(i4_ret);

    c_memset(&t_font_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_font_info.a_c_font_name, WZD_FONT_NAME, WGL_MAX_FONT_NAME-1);
    t_font_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_font_info.e_font_size  = WZD_DLG_BTN_FNT_SIZE;
    t_font_info.e_font_style = FE_FNT_STYLE_REGULAR;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_font_info),
                          NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(pw2s_btn_text),
                          WGL_PACK(c_uc_w2s_strlen(pw2s_btn_text)));
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}
#endif

static INT32 _wzd_cho_mode_show_energy_logo(BOOL b_show)
{
	WZD_CHO_MODE_MEMBER_T*	pt_this = &gt_cho_mode;
	WGL_IMG_INFO_T      	t_img_info;

	/* make icon visible */
	if(b_show)
	{
	    t_img_info.e_type = WGL_IMG_SET_STANDARD;
	    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_energystar_logo;
	    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_energystar_logo;
	    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_energystar_logo;

	    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_enegry_icon,
	                              WGL_CMD_GL_SET_IMAGE,
	                              WGL_PACK (WGL_IMG_FG),
	                              WGL_PACK (&t_img_info)));

		RET_ON_ERR (c_wgl_set_visibility(pt_this->h_enegry_icon, WGL_SW_NORMAL));
		RET_ON_ERR (c_wgl_float(pt_this->h_enegry_icon, TRUE, WGL_NO_AUTO_REPAINT));
	}
	else
	{
	    t_img_info.e_type = WGL_IMG_SET_STANDARD;
	    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
	    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
	    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;

	    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_enegry_icon,
	                              WGL_CMD_GL_SET_IMAGE,
	                              WGL_PACK (WGL_IMG_FG),
	                              WGL_PACK (&t_img_info)));

		RET_ON_ERR (c_wgl_set_visibility (pt_this->h_enegry_icon, WGL_SW_HIDE));
		RET_ON_ERR (c_wgl_float(pt_this->h_enegry_icon, TRUE, WGL_NO_AUTO_REPAINT));
	}

	return WZDR_OK;
}

static INT32 _wzd_choose_mode_energy_logo_create(VOID)
{
    WZD_CHO_MODE_MEMBER_T*  pt_this = &gt_cho_mode;
    GL_RECT_T           	t_rect;
    WGL_IMG_INFO_T      	t_img_info;

	/* create dialog frame */
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    SET_RECT_BY_SIZE (& t_rect,
                        WZD_ENEGRY_ICON_COUNTRY_CODE_X,
                        WZD_ENEGRY_ICON_COUNTRY_CODE_Y,
                        WZD_ENEGRY_ICON_COUNTRY_CODE_W,
                        WZD_ENEGRY_ICON_COUNTRY_CODE_H);

    RET_ON_ERR (c_wgl_create_widget (pt_this->h_dialog_frm,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     0,
                                     &pt_this->h_enegry_icon));


    /* set theme */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_energystar_logo;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_energystar_logo;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_energystar_logo;
#else
    SET_RECT_BY_SIZE (& t_rect,
                        WZD_ENEGRY_ICON_X,
                        WZD_ENEGRY_ICON_Y,
                        WZD_ENEGRY_ICON_W,
                        WZD_ENEGRY_ICON_H);

	RET_ON_ERR (c_wgl_create_widget (pt_this->h_welcome_frm,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     0,
                                     &pt_this->h_enegry_icon));

    /* set theme */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_energy_star;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_energy_star;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_energy_star;
#endif


    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_enegry_icon,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_FG), /* foreground image */
                              WGL_PACK (&t_img_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility(pt_this->h_enegry_icon, WGL_SW_HIDE));

	return WZDR_OK;
}

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
static INT32 _wzd_choose_mode_dialog_create(VOID)
{
    GL_RECT_T               t_rect;
    /**
    WGL_COLOR_INFO_T        t_color_info;
    */
    WGL_FONT_INFO_T         t_fnt_info;
    /**
    WGL_IMG_INFO_T          t_img_info;
     */
    UINT32                  ui4_style = 0;
    UINT8                   ui1_align = 0;
    WGL_COLOR_INFO_T        t_color_info_bg, t_color_info_fg;
    WGL_INSET_T             t_inset;
    UTF16_T                 w2s_dlg_store[32] = {0};
    UTF16_T                 w2s_dlg_home[32] = {0};

    c_uc_w2s_strncpy(w2s_dlg_store, L"Store Demo", (UINT32)31);
    c_uc_w2s_strncpy(w2s_dlg_home, L"Home Use", (UINT32)31);

	/* create dialog frame */
    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                        WZD_CHO_MODE_DLG_FRM_X,
                        WZD_CHO_MODE_DLG_FRM_Y,
                        WZD_CHO_MODE_DLG_FRM_W,
                        WZD_CHO_MODE_DLG_FRM_H);

    /* create widget */
	RET_ON_ERR (c_wgl_create_widget (gt_cho_mode.h_welcome_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     0,
                                     & gt_cho_mode.h_dialog_frm));

/** as the bk pic provided by custom is put the bg glob and the dialog bg together
*     so here just do not set the dialog bg, and only use it position reference
*/
#if 0
    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (gt_cho_mode.h_dialog_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_simple_dialog_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_simple_dialog_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_simple_dialog_bk;

    RET_ON_ERR (c_wgl_do_cmd (gt_cho_mode.h_dialog_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));



#endif


    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (gt_cho_mode.h_dialog_frm, WGL_SW_HIDE));

	/* create dialog text */
    SET_RECT_BY_SIZE (& t_rect,
                      WZD_DLG_ENG_TXT_X,
                      WZD_DLG_ENG_TXT_Y,
                      WZD_DLG_ENG_TXT_W,
                      WZD_DLG_ENG_TXT_H);

    ui4_style = WGL_STL_TEXT_MULTILINE |
                 WGL_STL_TEXT_MAX_128  |
                 WGL_STL_TEXT_MAX_DIS_5_LINE |
                 WZD_WIDGET_STYLE;

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strncpy (t_fnt_info.a_c_font_name, WZD_FONT_NAME, WGL_MAX_FONT_NAME-1);

	t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_BOLD;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_fnt_info.ui1_custom_size = 16;

    ui1_align = WGL_AS_CENTER_CENTER;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_cho_mode_txt_bg);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_cho_mode_txt_bg);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_cho_mode_txt_bg);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_cho_mode_txt_wihte);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_cho_mode_txt_wihte);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_cho_mode_txt_wihte);

    t_inset.i4_left   = 8 * WZD_UI_RATIO_W;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (_wzd_page_cho_mode_create_txt(
                            &t_rect,
                            gt_cho_mode.h_dialog_frm,
                            NULL,
                            ui4_style,
                            &gt_cho_mode.h_eng_text,
                            &t_fnt_info,
                            ui1_align,
                            &t_color_info_bg,
                            &t_color_info_fg,
                            &t_inset));

     RET_ON_ERR (c_wgl_do_cmd (gt_cho_mode.h_eng_text,
                              WGL_CMD_TEXT_SET_TEXT,
                              WGL_PACK (MLM_WZD_TEXT(0, wzd_get_validate_key ((MLM_WZD_KEY_CHO_MODE)))),
                              WGL_PACK (c_uc_w2s_strlen (MLM_WZD_TEXT(0, wzd_get_validate_key (MLM_WZD_KEY_CHO_MODE))))));

     RET_ON_ERR (c_wgl_do_cmd(gt_cho_mode.h_eng_text,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          WGL_PACK(5),
                          NULL));

   SET_RECT_BY_SIZE (& t_rect,
                      WZD_DLG_FRE_TXT_X,
                      WZD_DLG_FRE_TXT_Y,
                      WZD_DLG_FRE_TXT_W,
                      WZD_DLG_FRE_TXT_H);

    ui4_style = WGL_STL_TEXT_MULTILINE |
                 WGL_STL_TEXT_MAX_128  |
                 WGL_STL_TEXT_MAX_DIS_5_LINE |
                 WZD_WIDGET_STYLE;

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strncpy (t_fnt_info.a_c_font_name, WZD_FONT_NAME, WGL_MAX_FONT_NAME-1);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_fnt_info.ui1_custom_size = 13;

    ui1_align = WGL_AS_CENTER_CENTER;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_cho_mode_txt_bg);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_cho_mode_txt_bg);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_cho_mode_txt_bg);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_cho_mode_txt_gray);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_cho_mode_txt_gray);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_cho_mode_txt_gray);

    t_inset.i4_left   = 8 * WZD_UI_RATIO_W;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (_wzd_page_cho_mode_create_txt(
                            &t_rect,
                            gt_cho_mode.h_dialog_frm,
                            NULL,
                            ui4_style,
                            &gt_cho_mode.h_fre_text,
                            &t_fnt_info,
                            ui1_align,
                            &t_color_info_bg,
                            &t_color_info_fg,
                            &t_inset));

    RET_ON_ERR (c_wgl_do_cmd (gt_cho_mode.h_fre_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (MLM_WZD_TEXT(1, wzd_get_validate_key (MLM_WZD_KEY_CHO_MODE))),
                          WGL_PACK (c_uc_w2s_strlen (MLM_WZD_TEXT(1, wzd_get_validate_key (MLM_WZD_KEY_CHO_MODE))))));

      SET_RECT_BY_SIZE (& t_rect,
                      WZD_DLG_SPA_TXT_X,
                      WZD_DLG_SPA_TXT_Y,
                      WZD_DLG_SPA_TXT_W,
                      WZD_DLG_SPA_TXT_H);

      RET_ON_ERR (_wzd_page_cho_mode_create_txt(
                        &t_rect,
                        gt_cho_mode.h_dialog_frm,
                        NULL,
                        ui4_style,
                        &gt_cho_mode.h_spa_text,
                        &t_fnt_info,
                        ui1_align,
                        &t_color_info_bg,
                        &t_color_info_fg,
                        &t_inset));

    RET_ON_ERR (c_wgl_do_cmd (gt_cho_mode.h_spa_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (MLM_WZD_TEXT(2, wzd_get_validate_key ((MLM_WZD_KEY_CHO_MODE)))),
                          WGL_PACK (c_uc_w2s_strlen (MLM_WZD_TEXT(2, wzd_get_validate_key (MLM_WZD_KEY_CHO_MODE))))));

	/* create dialog buttons */
    SET_RECT_BY_SIZE (& t_rect,
                  WZD_BTN01_X,
                  WZD_BTN01_Y,
                  WZD_BTN01_W,
                  WZD_BTN01_H);

    _wzd_page_cho_mode_create_btn(gt_cho_mode.h_dialog_frm,
                                    &t_rect,
                                    w2s_dlg_store,
                                    _wzd_store_btn_wgl_nfy_fct,
                                    &gt_cho_mode.h_store_button
                                    );

    SET_RECT_BY_SIZE (& t_rect,
              WZD_BTN02_X,
              WZD_BTN02_Y,
              WZD_BTN02_W,
              WZD_BTN02_H);

    _wzd_page_cho_mode_create_btn(gt_cho_mode.h_dialog_frm,
                                &t_rect,
                                w2s_dlg_home,
                                _wzd_home_btn_wgl_nfy_fct,
                                &gt_cho_mode.h_home_button
                                );


    return  0;
}
#else
static INT32 _wzd_choose_mode_dialog_create(VOID)
{
    WZD_CHO_MODE_MEMBER_T*      pt_this = &gt_cho_mode;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    INT32                       i4_ret = WZDR_OK;
    UTF16_T                     w2s_dlg_text[512+1]       = {0};
    UTF16_T                     w2s_dlg_store[512+1]       = {0};
    UTF16_T                     w2s_dlg_home[512+1]       = {0};

    c_uc_w2s_strcpy(w2s_dlg_text, L"  Choose your mode. \n Select Store Demo for in-store display. \n Select Home Use for in-home use.");
    c_uc_w2s_strcpy(w2s_dlg_store, L"Store Mode");
    c_uc_w2s_strcpy(w2s_dlg_home, L"Home Use");

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_MEDIUM;
    t_simple_dialog_init.h_parent                       = pt_this->h_welcome_frm;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = _wzd_home_btn_nfy;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _wzd_store_btn_nfy;
    t_simple_dialog_init.pf_wdgt_proc                   = _wzd_choose_mode_dialog_wdgt_proc;
    t_simple_dialog_init.pt_begin_offset                = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = FALSE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init, &pt_this->h_dlg);
    if(i4_ret != APP_UIR_OK){
        return WZDR_FAIL;
    }

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_dlg, w2s_dlg_text);
    if(i4_ret != APP_UIR_OK){
        return WZDR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_dlg, w2s_dlg_store);
    if(i4_ret != APP_UIR_OK){
        return WZDR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_set_no_text(pt_this->h_dlg, w2s_dlg_home);
    if(i4_ret != APP_UIR_OK){
        return WZDR_FAIL;
    }

    return WZDR_FAIL;
}

static INT32 _wzd_choose_mode_dialog_wdgt_proc(HANDLE_T    h_widget,
                                               UINT32      ui4_msg,
                                               VOID*       pv_param1,
                                               VOID*       pv_param2)
{
    UINT32          ui4_key_code;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        ui4_key_code = (UINT32)pv_param1;
        switch (ui4_key_code)
        {
            case BTN_CURSOR_RIGHT:
				_wzd_cho_mode_show_energy_logo(TRUE);
				c_wgl_repaint(pt_this->h_welcome_frm, NULL, TRUE);
            	break;
			case BTN_CURSOR_LEFT:
				_wzd_cho_mode_show_energy_logo(FALSE);
				c_wgl_repaint(pt_this->h_welcome_frm, NULL, TRUE);
            	break;
            default:
                break;
        }
    }
    return a_ui_simple_dialog_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

#endif

 /*----------------------------------------------------------------------------
 * Name: wzd_page_dvbs_create
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
static INT32 _wzd_page_choose_mode_create (VOID)
{
    HANDLE_T                    h_main_frm = NULL_HANDLE;
    WZD_CHO_MODE_MEMBER_T*        pt_this = &gt_cho_mode;
    GL_RECT_T           t_rect;
    /**
    WGL_COLOR_INFO_T    t_color_info;
    */
    WGL_IMG_INFO_T      t_img_info;

    RET_ON_ERR (wzd_view_get_main_frm(&h_main_frm));

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      MAIN_FRM_X,
                      MAIN_FRM_Y,
                      MAIN_FRM_W,
                      MAIN_FRM_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (h_main_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) (WZD_WIDGET_STYLE | WGL_STL_GL_ANIM_AFFECT_CHILD),
                                     0,
                                     &pt_this->h_welcome_frm));
#if 0 /* just deal with according to the  new ui custom spec*/
    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_welcome_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));
#endif

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = MAIN_FRM_IMG_BK_FULL_DLG;
    t_img_info.u_img_data.t_standard.t_disable   = MAIN_FRM_IMG_BK_FULL_DLG;
    t_img_info.u_img_data.t_standard.t_highlight = MAIN_FRM_IMG_BK_FULL_DLG;

    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_welcome_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (pt_this->h_welcome_frm, WGL_SW_HIDE));


    _wzd_choose_mode_dialog_create();
	_wzd_choose_mode_energy_logo_create();

    c_timer_create(&pt_this->h_timer);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_dvbs_dsty
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
static INT32 _wzd_page_choose_mode_dsty(VOID)
{
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_on_show
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
static INT32 _wzd_page_choose_mode_on_show (
                                    UINT32  ui4_page_id )
{
    WZD_CHO_MODE_MEMBER_T*      pt_this = &gt_cho_mode;
    HANDLE_T                    h_base_frm = NULL_HANDLE;
    UINT32                      ui4_choose_timer_delay = WZD_CHOOSE_STORE_MODE_TIMER;
    BOOL                        b_is_wzd_startup_first_time;
#if 0
    ANIM_DATA_ALPHA_T           t_anim_data;
#endif

    b_is_wzd_startup_first_time = wzd_get_startup_first_time();

    RET_ON_ERR (wzd_view_get_base_frm(&h_base_frm));
    RET_ON_ERR (c_wgl_set_visibility (h_base_frm, WGL_SW_HIDE_RECURSIVE));
    RET_ON_ERR (c_wgl_set_alpha (pt_this->h_welcome_frm, 255));
    RET_ON_ERR (c_wgl_set_visibility (pt_this->h_welcome_frm, WGL_SW_RECURSIVE));

#ifndef APP_ADD_COUNTRY_CODE_SUPPORT
    a_ui_simple_dialog_show(pt_this->h_dlg);
    a_ui_simple_dialog_set_answer(pt_this->h_dlg, b_is_wzd_startup_first_time);
    a_ui_simple_dialog_set_focus(pt_this->h_dlg, FALSE);
	_wzd_cho_mode_show_energy_logo(!b_is_wzd_startup_first_time);
	wzd_set_startup_first_time(FALSE);
#else
    c_wgl_set_visibility(pt_this->h_dialog_frm, WGL_SW_RECURSIVE);
    c_wgl_float(pt_this->h_dialog_frm, TRUE, WGL_NO_AUTO_REPAINT);
    if (b_is_wzd_startup_first_time)
    {
        ui4_choose_timer_delay = WZD_CHOOSE_STORE_MODE_TIMER;
        c_wgl_set_focus(pt_this->h_store_button, FALSE);
		_wzd_cho_mode_show_energy_logo(FALSE);
		wzd_set_startup_first_time(FALSE);
    }
    else
    {
        ui4_choose_timer_delay = WZD_CHOOSE_HOME_MODE_TIMER;
        c_wgl_set_focus(pt_this->h_home_button, FALSE);
		_wzd_cho_mode_show_energy_logo(TRUE);
    }
    RET_ON_ERR (c_wgl_repaint(pt_this->h_welcome_frm, NULL, TRUE));
#endif

#if 0
    c_memset(&t_anim_data, 0, sizeof(ANIM_DATA_ALPHA_T));
    t_anim_data.ui2_total_steps = 10;
    t_anim_data.ui2_frame_interval = 50;
    t_anim_data.ui1_start_alpha = 0;
    t_anim_data.ui1_end_alpha = 255;

    a_wzd_anim_alpha(pt_this->h_welcome_frm, &t_anim_data, TRUE);
    a_wzd_anim_end(pt_this->h_welcome_frm);
#endif

    c_timer_start(pt_this->h_timer,
                ui4_choose_timer_delay,
                X_TIMER_FLAG_ONCE,
                _wzd_cho_mode_timer_cb_fct,
                NULL);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_on_hide
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
static INT32 _wzd_page_choose_mode_on_hide(UINT32 ui4_page_id)
{
    return WZDR_OK;
}

INT32 wzd_page_choose_mode_on_hide(BOOL b_fade_out_anim)
{
    WZD_CHO_MODE_MEMBER_T*        pt_this = &gt_cho_mode;
    ANIM_DATA_ALPHA_T             t_anim_data;

    if (b_fade_out_anim)
    {
        c_memset(&t_anim_data, 0, sizeof(ANIM_DATA_ALPHA_T));

        t_anim_data.ui2_total_steps = 5;
        t_anim_data.ui2_frame_interval = 50;

        t_anim_data.ui1_start_alpha = 255;
        t_anim_data.ui1_end_alpha = 0;

        a_wzd_anim_alpha(pt_this->h_welcome_frm, &t_anim_data, TRUE);
        a_wzd_anim_end(pt_this->h_welcome_frm);

        c_thread_delay(200);
    }
    else
    {
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_welcome_frm, WGL_SW_HIDE_RECURSIVE));
    }

    return WZDR_OK;
}

INT32 wzd_page_choose_mode_stop_timer(VOID)
{
    WZD_CHO_MODE_MEMBER_T*        pt_this = &gt_cho_mode;

    c_timer_stop(pt_this->h_timer);

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_on_hide
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
INT32 wzd_page_choose_mode_get_page_info_data( WZD_PAGE_INFO_DATA_T* pt_info_data)
{
    c_memset( pt_info_data, 0, sizeof(WZD_PAGE_INFO_DATA_T) );

    pt_info_data->t_page_type              = WZD_PAGE_TYPE_CUST_PAGE;
    pt_info_data->ui2_title_key            = MLM_WZD_KEY_TITLE_VIZIO;
    pt_info_data->ui2_desc_text_key        = MLM_WZD_KEY_LOC_DESC_TITLE;
    pt_info_data->ui1_elem_num             = 0;
    pt_info_data->pf_get_text              = NULL;
    pt_info_data->pf_footer_data_change    = NULL;
	pt_info_data->pf_return_nfy_fct        = NULL;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_create = _wzd_page_choose_mode_create;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_destory = _wzd_page_choose_mode_dsty;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_show = _wzd_page_choose_mode_on_show;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_hide = _wzd_page_choose_mode_on_hide;


    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_con_tv_nfy_sel
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
INT32 wzd_page_choose_mode_nfy_sel(UINT16               ui2_sel_idx,
                                  VOID*                 pv_data,
                                  WZD_MSG_CUSTOM_T*     pt_ret_msg)
{
    (*pt_ret_msg)  = WZD_MSG_CUSTOM_NAV_NEXT_PAGE;

    return WZDR_OK;
}

#endif  /*APP_2K12_RETAIL_DEMO_MODE*/
