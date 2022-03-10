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
#include "wizard/wzd.h"
#include "wizard/page/wzd_page_nw_setup.h"
#include "wizard/page/wzd_page_complete.h"
#include "wdk/a_vkb.h"
#include "res/wdk/a_vkb_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "wizard/wzd_dbg.h"

 /* compl diloge frame size */
#define WZD_SCREEN_DLG_FRM_X                 ((BASE_FRM_W - WZD_SCREEN_DLG_FRM_W) / 2)
#define WZD_SCREEN_DLG_FRM_Y                 (((BASE_FRM_H - WZD_SCREEN_DLG_FRM_H ) / 2) - (110 * WZD_UI_RATIO_W))
#define WZD_SCREEN_DLG_FRM_W                 (580 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_FRM_H                 (240 * WZD_UI_RATIO_W)
 
 /* compl diloge icon size */
#define WZD_SCREEN_DLG_ICON_X                ((WZD_SCREEN_DLG_FRM_W / 2) - (20 * WZD_UI_RATIO_W))
#define WZD_SCREEN_DLG_ICON_Y                (75 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_ICON_W                (40 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_ICON_H                (40 * WZD_UI_RATIO_W)
 
 /* compl diloge text size */
#define WZD_SCREEN_DLG_TEXT_X                (0)
#define WZD_SCREEN_DLG_TEXT_Y                (WZD_SCREEN_DLG_ICON_Y + WZD_SCREEN_DLG_ICON_H + 10 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_TEXT_W                (WZD_SCREEN_DLG_FRM_W)
#define WZD_SCREEN_DLG_TEXT_H                (100 * WZD_UI_RATIO_W)


 typedef struct _WZD_DLG_PAGE_T
 {
	 HANDLE_T			 h_dlg_frm;
	 HANDLE_T			 h_dlg_icon;
	 HANDLE_T			 h_dlg_text; 
	 HANDLE_T			 h_dlg_timer;
 }WZD_DLG_PAGE_T;

 static WZD_DLG_PAGE_T					 t_g_compl_finished_dlg_page;


 static INT32 _wzd_page_compl_finished_dlg_hide (VOID);
 static INT32 _wzd_page_compl_set_dlg_visibility (VOID);

 /*----------------------------------------------------------------------------
  * Name: _wzd_page_compl_finished_btn_do_show_dlg_timer
  *
  * Description: 
  *
  * Inputs:  -
  *
  * Outputs: -
  *
  * Returns: 
  ----------------------------------------------------------------------------*/
 static VOID _wzd_page_compl_finished_btn_do_show_dlg_timer(VOID* pv_data,
																			 SIZE_T  z_data_size)
 {
	 _wzd_page_compl_finished_dlg_hide();
 }
 
 /*----------------------------------------------------------------------------
  * Name: _wzd_page_compl_finished_btn_dlg_show_nfy_fct
  *
  * Description: 
  *
  * Inputs:  -
  *
  * Outputs: -
  *
  * Returns: 0					Successful.
  * Any other values			Failed.
  ----------------------------------------------------------------------------*/
 static VOID _wzd_page_compl_finished_btn_dlg_show_nfy_fct(HANDLE_T  h_timer,
																			VOID*	  pv_tag)
 {
	 wzd_async_invoke(_wzd_page_compl_finished_btn_do_show_dlg_timer, NULL, 0, FALSE); 
 }
 
 /*-----------------------------------------------------------------------------
  * Name: _wzd_page_compl_finished_dlg_hide
  *
  * Description: The function hide the full screen dialog.
  *
  * Inputs: 
  *
  * Outputs: -
  *
  * Returns: 0						Successful.
  * 		 Any other values		Failed.
  ----------------------------------------------------------------------------*/
 static INT32 _wzd_page_compl_finished_dlg_hide (VOID)
 {
	 WZD_DLG_PAGE_T*	 pt_finished_dlg_page = &t_g_compl_finished_dlg_page;
 
	 c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_frm, WGL_SW_HIDE);
	 RET_ON_ERR (a_wzd_exit());    /* Exit wizard. */
	 return WZDR_OK;
 }
 
 /*-----------------------------------------------------------------------------
  * Name: _wzd_page_compl_set_dlg_visibility
  *
  * Description: 
  *
  * Inputs:  
  *
  * Outputs: -
  *
  * Returns: 0						Successful.
  * 		 Any other values		Failed.
  ----------------------------------------------------------------------------*/
 static INT32 _wzd_page_compl_set_dlg_visibility (VOID)
 {
	 WZD_DLG_PAGE_T* pt_finished_dlg_page = &t_g_compl_finished_dlg_page;
	 
	 RET_ON_ERR (c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_icon, WGL_SW_NORMAL));
 
	 RET_ON_ERR (c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_text, WGL_SW_NORMAL));
 
	 RET_ON_ERR (c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_frm, WGL_SW_NORMAL));
 
	 RET_ON_ERR (c_wgl_insert (pt_finished_dlg_page->h_dlg_frm,
							   NULL_HANDLE,
							   WGL_INSERT_TOPMOST,
							   WGL_NO_AUTO_REPAINT));
							   
	 RET_ON_ERR (c_wgl_set_focus(pt_finished_dlg_page->h_dlg_frm, FALSE));
	 
	 return  WZDR_OK;
 }
 
 /*-----------------------------------------------------------------------------
  * Name: _wzd_page_compl_finished_dlg_set_text
  *
  * Description: The function set the full screen dialog text.
  *
  * Inputs:
  *
  * Outputs: -
  *
  * Returns: 0						Successful.
  * 		 Any other values		Failed.
  ----------------------------------------------------------------------------*/
 static INT32 _wzd_page_compl_finished_dlg_set_text (UTF16_T* pw2s_text)
 {
	 WZD_DLG_PAGE_T*	 pt_finished_dlg_page = &t_g_compl_finished_dlg_page;
 
	 RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_text,
							   WGL_CMD_TEXT_SET_TEXT,
							   WGL_PACK (pw2s_text),
							   WGL_PACK ((UINT16)0xFFFF)));
	 return  WZDR_OK;
 }
 
 /*-----------------------------------------------------------------------------
  * Name: _wzd_page_compl_finished_dlg_set_icon
  *
  * Description: The function set image template to the finished dialog icon.
  *
  *
  *
  *
  * Outputs: -
  *
  * Returns: 0						Successful.
  * 		 Any other values		Failed.
  ----------------------------------------------------------------------------*/
 static INT32 _wzd_page_compl_finished_dlg_set_icon (WGL_HIMG_TPL_T h_dlg_icon)
 {
	 WGL_IMG_INFO_T 	 t_img_info;
	 WZD_DLG_PAGE_T*	 pt_finished_dlg_page = &t_g_compl_finished_dlg_page;
 
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
 
 
 /*----------------------------------------------------------------------------
  * Name: _wzd_page_compl_finished_dlg_icon_create
  *
  * Description: This function creates the dialog icon widget.
  *
  * Inputs:  -
  *
  * Outputs: -
  *
  * Returns: 0					Successful.
  * 		 Any other values	Failed.
  ----------------------------------------------------------------------------*/
 static INT32 _wzd_page_compl_finished_dlg_icon_create (VOID)
 {
	 GL_RECT_T			 t_rect = {0};
	 INT32				 i4_ret;
	 WGL_INSET_T		 t_inset;
	 WZD_DLG_PAGE_T*	 pt_finished_dlg_page = &t_g_compl_finished_dlg_page;
	 
	 SET_RECT_BY_SIZE (&t_rect,
					   WZD_SCREEN_DLG_ICON_X,
					   WZD_SCREEN_DLG_ICON_Y,
					   WZD_SCREEN_DLG_ICON_W,
					   WZD_SCREEN_DLG_ICON_H);
 
	 i4_ret = c_wgl_create_widget(pt_finished_dlg_page->h_dlg_frm,
								  HT_WGL_WIDGET_ICON,
								  WGL_CONTENT_ICON_DEF,
								  WGL_BORDER_NULL,
								  &t_rect,
								  NULL,
								  255,
								  (VOID*)0,
								  NULL,
								  &pt_finished_dlg_page->h_dlg_icon);
 
	 RET_ON_ERR (i4_ret);
 
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
	 i4_ret = c_wgl_do_cmd(pt_finished_dlg_page->h_dlg_icon,
						   WGL_CMD_ICON_SET_ALIGN,
						   (VOID*)WGL_AS_CENTER_BOTTOM,
						   NULL);
	 RET_ON_ERR (i4_ret);
 
	 /* set visibility, default hidden */
	 RET_ON_ERR (c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_icon, WGL_SW_HIDE));
	 
	 return WZDR_OK;
 }
 
 
 /*----------------------------------------------------------------------------
  * Name: _wzd_page_compl_finished_dlg_text_create
  *
  * Description: This function creates the full screen dialog text widget.
  *
  * Inputs:  -
  *
  * Outputs: -
  *
  * Returns: 0					Successful.
  * 		 Any other values	Failed.
  ----------------------------------------------------------------------------*/
 static INT32 _wzd_page_compl_finished_dlg_text_create(VOID)
 {
	 WGL_INSET_T				 t_inset;
	 WGL_FONT_INFO_T			 t_fnt_info;
	 GL_RECT_T						 t_rect;
	 WGL_COLOR_INFO_T			 t_color_info;
	 CHAR*							 s_font_name = wzd_view_get_font_name();
	 WZD_DLG_PAGE_T*			 pt_finished_dlg_page = &t_g_compl_finished_dlg_page;
 
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
											  WGL_STL_TEXT_MAX_512	|
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
	 COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,	 & t_g_wzd_color_desc_txt);
	 COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,	 & t_g_wzd_color_desc_txt);
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
  * Name:  _wzd_page_compl_dlg_create
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
 static INT32 _wzd_page_compl_dlg_create (HANDLE_T parent)
 {
	 WZD_DLG_PAGE_T*	 pt_finished_dlg_page = &t_g_compl_finished_dlg_page;
	 GL_RECT_T			 t_rect;
	 WGL_IMG_INFO_T 	 t_img_info;
	 WGL_COLOR_INFO_T	 t_color_info;
	 INT32				 i4_ret = WZDR_OK;
	 
	 /* get rectangle size */
	 SET_RECT_BY_SIZE (& t_rect,
					   WZD_SCREEN_DLG_FRM_X,
					   WZD_SCREEN_DLG_FRM_Y,
					   WZD_SCREEN_DLG_FRM_W,
					   WZD_SCREEN_DLG_FRM_H);
   
	 /* create widget */
	 i4_ret = c_wgl_create_widget (parent,
								   HT_WGL_WIDGET_FRAME,
								   WGL_CONTENT_FRAME_DEF,
								   WGL_BORDER_NULL,
								   & t_rect,
								   NULL,
								   240,
								   (VOID*) WZD_WIDGET_STYLE,
								   0,
								   &pt_finished_dlg_page->h_dlg_frm);
	 RET_ON_ERR(i4_ret);
	 
	 /* set theme */
	 t_color_info.e_type = WGL_COLOR_SET_STANDARD;
	 COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,	 & t_g_wzd_color_base_frm_bk);
	 COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,	 & t_g_wzd_color_base_frm_bk);
	 COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);
 
	 RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_frm,
							   WGL_CMD_GL_SET_COLOR,
							   WGL_PACK (WGL_CLR_BK),
							   WGL_PACK (& t_color_info)));
 
	 t_img_info.e_type = WGL_IMG_SET_STANDARD;
	 t_img_info.u_img_data.t_standard.t_enable	  = h_g_wzd_img_dialog;
	 t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_dialog;
	 t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_dialog;
 
	 RET_ON_ERR (c_wgl_do_cmd (pt_finished_dlg_page->h_dlg_frm,
							   WGL_CMD_GL_SET_IMAGE,
							   WGL_PACK (WGL_IMG_BK),
							   WGL_PACK (& t_img_info)));
 
	 /* create icon */
	 RET_ON_ERR (_wzd_page_compl_finished_dlg_icon_create());
 
	 /* create text */
	 RET_ON_ERR (_wzd_page_compl_finished_dlg_text_create());
 
	 /* create dlg show timer */
	 RET_ON_ERR (c_timer_create(&pt_finished_dlg_page->h_dlg_timer));
 
	 /* set visibility */
	 RET_ON_ERR (c_wgl_set_visibility (pt_finished_dlg_page->h_dlg_frm, WGL_SW_HIDE));
	 
	 return WZDR_OK;
 }
 
 

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
static INT32 _wzd_page_comp_create (VOID)
{
    HANDLE_T                        h_layout_frm = NULL_HANDLE;

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    _wzd_page_compl_dlg_create(h_layout_frm);
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
static INT32 _wzd_page_comp_dsty(VOID)
{
	c_wgl_destroy_widget(t_g_compl_finished_dlg_page.h_dlg_frm);
	c_wgl_destroy_widget(t_g_compl_finished_dlg_page.h_dlg_icon);
	c_wgl_destroy_widget(t_g_compl_finished_dlg_page.h_dlg_text);
	c_wgl_destroy_widget(t_g_compl_finished_dlg_page.h_dlg_timer);
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_comp_on_show
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
static INT32 _wzd_page_comp_on_show (
    UINT32                      ui4_page_id
    )
{
	WZD_DLG_PAGE_T*	 pt_finished_dlg_page = &t_g_compl_finished_dlg_page;

    /* Update footer */
	RET_ON_ERR (wzd_view_footer_set_btn_num(0));
	RET_ON_ERR (wzd_view_set_main_frm_bg(NULL_HANDLE, FALSE)); /* Change background for close display small video */
    RET_ON_ERR (wzd_view_demo_pic_show(FALSE));  /* Close right side picture. */
	RET_ON_ERR (wzd_view_title_txt_set_visibility(FALSE));
	RET_ON_ERR(_wzd_page_compl_set_dlg_visibility());
	_wzd_page_compl_finished_dlg_set_text (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_FINISHED_IMG));
	_wzd_page_compl_finished_dlg_set_icon(h_g_wzd_img_checkmark_green_small);

    /* Update display */
	DBG_LOG_PRINT(("\n[WZD][complete dlg show] [line= %d] \n", __LINE__));
	c_timer_start(pt_finished_dlg_page->h_dlg_timer, 
				  5000,
				  X_TIMER_FLAG_ONCE,
				  _wzd_page_compl_finished_btn_dlg_show_nfy_fct,
				  NULL); 

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_comp_on_hide
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
static INT32 _wzd_page_comp_on_hide(UINT32 ui4_page_id)
{
	_wzd_page_compl_finished_dlg_hide();

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_comp_on_footer_nfy
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
static VOID _wzd_page_comp_on_footer_nfy(
                                         UINT32   ui4_msg,
                                         VOID*    pv_param1,
                                         VOID*    pv_param2)
{
}


/*----------------------------------------------------------------------------
 * Name: _wzd_page_comp_on_hide
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
INT32 wzd_page_comp_get_page_info_data( WZD_PAGE_INFO_DATA_T* pt_info_data)
{
    c_memset( pt_info_data, 0, sizeof(WZD_PAGE_INFO_DATA_T) );

    pt_info_data->t_page_type              = WZD_PAGE_TYPE_CUST_PAGE;
    pt_info_data->ui2_title_key            = MLM_WZD_KEY_TITLE_CMPL_VIZIO;
    pt_info_data->ui2_desc_text_key        = MLM_WZD_KEY_LOC_DESC_TITLE;
    pt_info_data->ui1_elem_num             = 0;
    pt_info_data->pf_get_text              = NULL;
    pt_info_data->pf_footer_data_change    = _wzd_page_comp_on_footer_nfy;
	pt_info_data->pf_return_nfy_fct        = NULL;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_create = _wzd_page_comp_create;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_destory = _wzd_page_comp_dsty;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_show = _wzd_page_comp_on_show;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_hide = _wzd_page_comp_on_hide;


    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_comp_nfy_sel
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
INT32 wzd_page_comp_nfy_sel(UINT16               ui2_sel_idx,
                                  VOID*                 pv_data,
                                  WZD_MSG_CUSTOM_T*     pt_ret_msg)
{
    (*pt_ret_msg)  = WZD_MSG_CUSTOM_NAV_NEXT_PAGE;

    return WZDR_OK;
}

