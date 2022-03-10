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
 * $RCSfile: menu_page_cap_stl.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/10 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: def1c94290023494fa73e23229d19fd3 $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_cc.h"
#include "u_wgl_bdr_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "u_sb_atsc_eng.h"

#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_dbg.h"
#include "rest/a_rest_event.h"

#ifdef ATSC_CAP_STL_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

typedef struct _MENU_PAGE_CAP_STL_DATA_T
{
    WGL_CC_INFO_T     t_cc_info;
    HANDLE_T            h_cc_preview;
    UINT32              ui4_page_id;
    UINT16              ui2_cap_stl_idx;
	UINT16 			    ui2_idx_fs_idx;
    UINT16              ui2_font_size_idx;
    UINT16              ui2_font_color_idx;
	UINT16				ui2_text_edges_idx;
	UINT16				ui2_text_edges_color_idx;
    UINT16              ui2_font_opac_idx;
    UINT16              ui2_bg_color_idx;
    UINT16              ui2_bg_opac_idx;
    UINT16              ui2_win_color_idx;
    UINT16              ui2_win_opac_idx;
    BOOL                b_page_is_show;
} MENU_PAGE_CAP_STL_DATA_T;

#define MENU_PAGE_CAP_STL_MAX_ITEM_NUM      (10)
#define MENU_PAGE_CAP_STL_PREVIEW_W         (200)
#define MENU_PAGE_CAP_STL_PREVIEW_H         (100)
#define MENU_PAGE_CAP_STL_PREVIEW_X         ((1920 - MENU_PAGE_CAP_STL_PREVIEW_W)/2 )
#define MENU_PAGE_CAP_STL_PREVIEW_Y         (1080 - 200)

# ifdef    CS_CC_PV_H
# undef    CS_CC_PV_H

# define   CS_CC_PV_H              1241*4/3

# endif



#define     CS_CPY_COLOR(dest, src)         \
                    dest.a    = src.a;      \
                    dest.u1.r = src.u1.r;   \
                    dest.u2.g = src.u2.g;   \
                    dest.u3.b = src.u3.b

#define     CS_CPY_RGB(dest, src)           \
                    dest.u1.r = src.u1.r;   \
                    dest.u2.g = src.u2.g;   \
                    dest.u3.b = src.u3.b


#define     CS_CPY_ALPHA(dest, src)         \
                    dest.a = src.a


#define     CS_CPY_FS(dest, src)            \
                    c_strcpy(dest, src)

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T                 t_g_menu_atsc_page_cap_stl;

static MENU_PAGE_CAP_STL_DATA_T    t_g_menu_page_cap_stl_data;
static BOOL         					  b_fs_support = TRUE; //default support the font style [DTV00544379]


static GL_COLOR_T t_g_color_black       = {255, {  0}, {  0}, {  0}};
static GL_COLOR_T t_g_color_white       = {255, {255}, {255}, {255}};
static GL_COLOR_T t_g_color_green       = {255, {  0}, {255}, {  0}};
static GL_COLOR_T t_g_color_blue        = {255, {  0}, {  0}, {255}};
static GL_COLOR_T t_g_color_red         = {255, {255}, {  0}, {  0}};
static GL_COLOR_T t_g_color_cyan        = {255, {  0}, {255}, {255}};
static GL_COLOR_T t_g_color_yellow      = {255, {255}, {255}, {  0}};
static GL_COLOR_T t_g_color_magenta     = {255, {255}, {  0}, {255}};
static GL_COLOR_T t_g_color_broadcast   = {255, {  0}, {  0}, {  0}};
static GL_COLOR_T t_g_opac_solid        = {255, {  0}, {  0}, {  0}};
static GL_COLOR_T t_g_opac_transp       = {0  , {  0}, {  0}, {  0}};
static GL_COLOR_T t_g_opac_transl       = {127, {  0}, {  0}, {  0}};


/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _cap_stl_preview_init
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
static INT32 _cap_stl_preview_init(VOID)
{
    INT32       i4_ret = MENUR_OK;
    GL_RECT_T   t_rect;
    HANDLE_T    h_root_frame = NULL_HANDLE;
    WGL_CC_INIT_INFO_T          t_cc_init;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    /* Get root frame */
    i4_ret = menu_pm_get_root_frm(&h_root_frame);
    MENU_CHK_FAIL(i4_ret);

    /* Init CC */
    c_memset(&t_cc_init, 0, sizeof(WGL_CC_INIT_INFO_T));
    t_cc_init.t_override_attr.ui2_flag          = 0;
    t_cc_init.ui2_max_width                     = (UINT16)menu_canvas_width();
    t_cc_init.ui2_max_height                    = (UINT16)menu_canvas_height();
    t_cc_init.ui4_flashing_interval             = 0;
    t_cc_init.ui4_smooth_scroll_time_bound      = 0;
    t_cc_init.ui4_typewriter_effect_time_bound  = 0;
    t_cc_init.ui2_tab_size                      = (UINT16)8;

    /* CC Info */
    c_memset(&pt_this->t_cc_info, 0, sizeof(WGL_CC_INFO_T));
    pt_this->t_cc_info.ui2_cc_info_flags = WGL_CC_INFO_VISIBLE |
                                           WGL_CC_INFO_IS_VALID_WIN_ATTR |
                                           WGL_CC_INFO_IS_VALID_PEN_FONT |
                                           WGL_CC_INFO_IS_VALID_PEN_COLOR;
    pt_this->t_cc_info.ui1_anchor        = (UINT8)CS_CC_PV_A;
    pt_this->t_cc_info.ui2_anchor_h      = MENU_PAGE_CAP_STL_PREVIEW_X;//(UINT16)CS_CC_PV_H;
    pt_this->t_cc_info.ui2_anchor_v      = MENU_PAGE_CAP_STL_PREVIEW_Y;//(UINT16)CS_CC_PV_V;
    pt_this->t_cc_info.ui2_col_count     = 5;
    pt_this->t_cc_info.ui2_row_count     = 1;

    /* Win Attr */
    pt_this->t_cc_info.t_win_attr.ui2_win_attr =
                                            WGL_CC_WIN_ATTR_WORD_WRAP |
                                            WGL_CC_WIN_ATTR_AUTO_SCROLL;
    pt_this->t_cc_info.t_win_attr.ui1_justify =
                                            WGL_CC_JUSTIFY_CENTER;
    pt_this->t_cc_info.t_win_attr.ui1_print_dir =
                                            WGL_CC_PRINT_DIR_LEFT_TO_RIGHT;
    pt_this->t_cc_info.t_win_attr.ui1_scroll_dir =
                                            WGL_CC_SCROLL_DIR_BOTTOM_TO_TOP;
    pt_this->t_cc_info.t_win_attr.ui1_display_effect =
                                            WGL_CC_DISPLAY_EFFECT_SNAP;
    pt_this->t_cc_info.t_win_attr.ui1_display_effect_dir =
                                            WGL_CC_DISPLAY_EFFECT_DIR_LEFT_TO_RIGHT;
    pt_this->t_cc_info.t_win_attr.ui4_display_effect_duration = 0;
    pt_this->t_cc_info.t_win_attr.ui1_border_type =
                                            WGL_CC_BORDER_TYPE_NONE;
    CS_CPY_COLOR(pt_this->t_cc_info.t_win_attr.t_color_bk,      t_g_color_black);
    CS_CPY_COLOR(pt_this->t_cc_info.t_win_attr.t_color_border,  t_g_color_black);

    /* Pen Font */
    CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name, CS_FS_STYLE1);
    pt_this->t_cc_info.t_pen_font.t_font.e_size         = FE_FNT_SIZE_SMALL;
    pt_this->t_cc_info.t_pen_font.t_font.e_style        = WGL_CC_FNT_STYLE_REGULAR;
    pt_this->t_cc_info.t_pen_font.t_font.e_cmap         = FE_CMAP_ENC_UNICODE;
    pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type  = WGL_CC_EDGE_TYPE_NONE;
    pt_this->t_cc_info.t_pen_font.ui1_offset            = WGL_CC_TEXT_OFFSET_NORMAL;

    /* Pen Color */
    CS_CPY_COLOR(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_white);
    CS_CPY_COLOR(pt_this->t_cc_info.t_pen_color.t_color_bk,   t_g_color_black);
    CS_CPY_COLOR(pt_this->t_cc_info.t_pen_color.t_color_edge, t_g_color_black);
    pt_this->t_cc_info.t_pen_color.b_is_flash_fg = FALSE;
    pt_this->t_cc_info.t_pen_color.b_is_flash_bk = FALSE;

    c_memcpy(&t_cc_init.t_cc_info, &pt_this->t_cc_info, sizeof(WGL_CC_INFO_T));

    /* Init Caption Preview CC Widget */
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_PAGE_CAP_STL_PREVIEW_X,
                     MENU_PAGE_CAP_STL_PREVIEW_Y,
                     MENU_PAGE_CAP_STL_PREVIEW_W,
                     MENU_PAGE_CAP_STL_PREVIEW_H);
    i4_ret = c_wgl_create_widget(h_root_frame,
                                 HT_WGL_WIDGET_CC,
                                 WGL_CONTENT_CC_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 &t_cc_init,
                                 0,
                                 &pt_this->h_cc_preview);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_insert(pt_this->h_cc_preview,
                          NULL_HANDLE,
                          WGL_INSERT_BEFORE,
                          FALSE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_cc_preview,
                          WGL_CMD_CC_WRITE_TEXT,
                          WGL_PACK(L"ABC"),
                          WGL_PACK(3));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(
                          pt_this->h_cc_preview,
                          WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _cap_stl_update_info
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
static INT32 _cap_stl_update_info(VOID)
{
    INT32 i4_ret    = MENUR_OK;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    i4_ret = c_wgl_do_cmd(pt_this->h_cc_preview,
                          WGL_CMD_CC_UPDATE_ATTR,
                          &pt_this->t_cc_info,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_cc_preview,
                          WGL_CMD_CC_CLEAR_TEXT,
                          NULL,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_cc_preview,
                          WGL_CMD_CC_WRITE_TEXT,
                          WGL_PACK(L"ABC"),
                          WGL_PACK(3));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_cc_preview,
                          WGL_CMD_CC_UPDATE,
                          NULL,
                          NULL);
    MENU_CHK_FAIL(i4_ret);
    a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);
    a_cfg_update_dcs();
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _set_cap_stl_custom
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
static INT32 _set_cap_stl_custom(
                    BOOL        b_custom)
{
    INT32   i4_ret = MENUR_OK;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;


	if(b_fs_support)
	{
		menu_page_tree_enable_item(
	 							  pt_this->ui4_page_id,
	 							  pt_this->ui2_idx_fs_idx,
	 							  b_custom);
	}

    i4_ret = menu_page_tree_enable_item(
                                pt_this->ui4_page_id,
                                pt_this->ui2_font_size_idx,
                                b_custom);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_enable_item(
                                pt_this->ui4_page_id,
                                pt_this->ui2_font_color_idx,
                                b_custom);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_enable_item(
                                pt_this->ui4_page_id,
                                pt_this->ui2_font_opac_idx,
                                b_custom);
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = menu_page_tree_enable_item(
								pt_this->ui4_page_id,
								pt_this->ui2_text_edges_idx,
								b_custom);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = menu_page_tree_enable_item(
								pt_this->ui4_page_id,
								pt_this->ui2_text_edges_color_idx,
								b_custom);
	MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_enable_item(
                                pt_this->ui4_page_id,
                                pt_this->ui2_bg_color_idx,
                                b_custom);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_enable_item(
                                pt_this->ui4_page_id,
                                pt_this->ui2_bg_opac_idx,
                                b_custom);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_enable_item(
                                pt_this->ui4_page_id,
                                pt_this->ui2_win_color_idx,
                                b_custom);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_enable_item(
                                pt_this->ui4_page_id,
                                pt_this->ui2_win_opac_idx,
                                b_custom);
    MENU_LOG_ON_FAIL(i4_ret);

    if (pt_this->b_page_is_show)
     {
         if (b_custom)
         {
             /* Show the caption preview */
             i4_ret = c_wgl_set_visibility(pt_this->h_cc_preview,
                                           WGL_SW_NORMAL);
             MENU_LOG_ON_FAIL(i4_ret);
         }
         else
         {
             /* Hide the caption preview */
             i4_ret = c_wgl_set_visibility(pt_this->h_cc_preview,
                                           WGL_SW_HIDE);
             MENU_LOG_ON_FAIL(i4_ret);
         }
     }

    return MENUR_OK;
}

#if 0
/*----------------------------------------------------------------------------
 * Name: _set_cap_stl_idx
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
static VOID _set_cap_stl_idx(
					UINT16		ui2_idx)
{
	INT32		i4_ret = MENUR_OK;
	UINT8		ui1_cc_stl = APP_CFG_DCS_BROADCAST;

	switch (ui2_idx)
	{
		case 0:
			_set_cap_stl_custom(TRUE);
			ui1_cc_stl = APP_CFG_DCS_BROADCAST;
			break;
		case 1:
			_set_cap_stl_custom(TRUE);
			ui1_cc_stl = APP_CFG_DCS_CUSTOM;
			break;
		default:
			_set_cap_stl_custom(FALSE);
			ui1_cc_stl = APP_CFG_DCS_BROADCAST;
			break;
	}

	i4_ret = a_cfg_set_dcs(APP_CFG_RECID_DCS, ui1_cc_stl);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = a_cfg_update_dcs();
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = menu_pm_refresh();
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = menu_pm_repaint();
	MENU_LOG_ON_FAIL(i4_ret);

	return;
}
#endif
/*----------------------------------------------------------------------------
 * Name: _get_cap_stl_idx
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
static UINT16 _get_cap_stl_idx(VOID)
{
	INT32		i4_ret = MENUR_OK;
	UINT16		ui2_idx = 0;
	UINT8		ui1_cc_stl = APP_CFG_DCS_BROADCAST;

	i4_ret = a_cfg_get_dcs(APP_CFG_RECID_DCS, &ui1_cc_stl);
	MENU_LOG_ON_FAIL(i4_ret);

	switch(ui1_cc_stl)
	{
		case APP_CFG_DCS_BROADCAST:
			ui2_idx = 0;
			break;
		case APP_CFG_DCS_CUSTOM:
			ui2_idx = 1;
			break;
		default:
			ui2_idx = 0;
			break;
	}
	ui2_idx = 1;
	return ui2_idx;
}

/*----------------------------------------------------------------------------
 * Name: set_font_style_idx
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
static VOID _set_font_style_idx(
						UINT16		ui2_idx)
{
	MENU_PAGE_CAP_STL_DATA_T*	pt_this = &t_g_menu_page_cap_stl_data;
	UINT8		ui1_font_style = APP_CFG_DCS_FS_BROADCAST;

    switch (ui2_idx)
    {
	    case 0:
			CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  SN_FONT_MONO_SP_WO_SERF);
			ui1_font_style = APP_CFG_DCS_FS_BROADCAST;
	        break;
	    case 1:
			CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE1);
			ui1_font_style = APP_CFG_DCS_FS_STYLE1;
	        break;
	    case 2:
			CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE2);
			ui1_font_style = APP_CFG_DCS_FS_STYLE2;
	        break;
	    case 3:
			CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE3);
			ui1_font_style = APP_CFG_DCS_FS_STYLE3;
	        break;
	    case 4:
			CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE4);
			ui1_font_style = APP_CFG_DCS_FS_STYLE4;
	        break;
	    case 5:
			CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE5);
			ui1_font_style = APP_CFG_DCS_FS_STYLE5;
	        break;
	    case 6:
			CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE6);
			ui1_font_style = APP_CFG_DCS_FS_STYLE6;
	        break;
		case 7:
			CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE7);
			ui1_font_style = APP_CFG_DCS_FS_STYLE7;
	        break;
	    default:
			CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  SN_FONT_MONO_SP_WO_SERF);
			ui1_font_style = APP_CFG_DCS_FS_BROADCAST;
	        break;
    }

    MENU_LOG_ON_FAIL(a_cfg_set_dcs(APP_CFG_RECID_DCS_FONT_STYLE, ui1_font_style));
    MENU_LOG_ON_FAIL(_cap_stl_update_info());

    rest_event_notify("tv_settings/closed_captions/digital_style", 0, ""); //dolphin 20200505n add restap notify
}


/*----------------------------------------------------------------------------
 * Name: _get_font_style_idx
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
static UINT16 _get_font_style_idx(VOID)
{
    UINT8 ui1_value = 0;
	MENU_PAGE_CAP_STL_DATA_T*	pt_this = &t_g_menu_page_cap_stl_data;
	UINT16      ui2_idx = 0;


    a_cfg_get_dcs(APP_CFG_RECID_DCS_FONT_STYLE, &ui1_value);

    switch (ui1_value)
    {
   	case APP_CFG_DCS_FS_BROADCAST:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  SN_FONT_MONO_SP_WO_SERF);
        ui2_idx = 0;
		break;
    case APP_CFG_DCS_FS_STYLE1:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE1);
        ui2_idx = 1;
        break;
    case APP_CFG_DCS_FS_STYLE2:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE2);
        ui2_idx = 2;
        break;
    case APP_CFG_DCS_FS_STYLE3:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE3);
        ui2_idx = 3;
        break;
    case APP_CFG_DCS_FS_STYLE4:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE4);
        ui2_idx = 4;
        break;
    case APP_CFG_DCS_FS_STYLE5:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE5);
        ui2_idx = 5;
        break;
    case APP_CFG_DCS_FS_STYLE6:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE6);
        ui2_idx = 6;
        break;
    case APP_CFG_DCS_FS_STYLE7:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE7);
        ui2_idx = 7;
        break;
    default:
        break;
    }
    return ui2_idx;
}

UINT16 menu_get_font_style_idx(VOID)
{
    return _get_font_style_idx();
}

/*----------------------------------------------------------------------------
 * Name: _get_font_size_text
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
static VOID _get_font_style_text(
                    UINT16      ui2_idx,   /* in */
                    UTF16_T*    w2s_str,   /* out */
                    SIZE_T      z_len)     /* in, len of w2s_str */
{
    if (ui2_idx > CS_FS_STYLE_NUM)
    {
        ui2_idx = 0;
    }

    if (1 == _get_cap_stl_idx())
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_AS_BROADCAST + ui2_idx),
                         (UINT32)z_len);
    }
    else
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_STL_1),
                         (UINT32)z_len);

    }

    w2s_str[z_len - 1] = '\0';

    return;
}


/*----------------------------------------------------------------------------
 * Name: _set_font_size_idx
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
static VOID _set_font_size_idx(
                    UINT16      ui2_idx)
{
    UINT8       ui1_font_size = APP_CFG_DCS_FZ_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    switch (ui2_idx)
    {
        case 0:
            ui1_font_size = APP_CFG_DCS_FZ_BROADCAST;
            pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
            break;
        case 1:
            ui1_font_size = APP_CFG_DCS_FZ_SMALL;
            pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_SMALL;
            break;
        case 2:
            ui1_font_size = APP_CFG_DCS_FZ_MEDIUN;
            pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
            break;
        case 3:
            ui1_font_size = APP_CFG_DCS_FZ_LARGE;
            pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_LARGE;
            break;
        default:
            ui1_font_size = APP_CFG_DCS_FZ_BROADCAST;
            pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
            break;
    }

    MENU_LOG_ON_FAIL(a_cfg_set_dcs(APP_CFG_RECID_DCS_FONT_SIZE, ui1_font_size));
    MENU_LOG_ON_FAIL(_cap_stl_update_info());

    rest_event_notify("tv_settings/closed_captions/digital_style", 0, ""); //dolphin 20200505n add restap notify

    return;
}

/*----------------------------------------------------------------------------
 * Name: _get_font_size_idx
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
static UINT16 _get_font_size_idx(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_idx = 0;
    UINT8       ui1_font_size = APP_CFG_DCS_FZ_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    i4_ret = a_cfg_get_dcs(APP_CFG_RECID_DCS_FONT_SIZE, &ui1_font_size);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (ui1_font_size)
    {
        case APP_CFG_DCS_FZ_BROADCAST:
            pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_FZ_SMALL:
            pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_SMALL;
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_FZ_MEDIUN:
            pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_FZ_LARGE:
            pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_LARGE;
            ui2_idx = 3;
            break;
        default:
            pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
            ui2_idx = 0;
            break;
    }

    return  ui2_idx;
}

UINT16 menu_get_font_size_idx(VOID)
{
    return _get_font_size_idx();
}

/*----------------------------------------------------------------------------
 * Name: _get_font_size_text
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
static VOID _get_font_size_text(
                    UINT16      ui2_idx,   /* in */
                    UTF16_T*    w2s_str,   /* out */
                    SIZE_T      z_len)     /* in, len of w2s_str */
{
    if (ui2_idx > 3)
    {
        ui2_idx = 0;
    }

    if (1 == _get_cap_stl_idx())
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_FZ_0 + ui2_idx),
                         (UINT32)z_len);
    }
    else
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_STL_1),
                         (UINT32)z_len);

    }

    w2s_str[z_len - 1] = '\0';

    return;
}

/*----------------------------------------------------------------------------
 * Name: _set_font_color_idx
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
static VOID _set_font_color_idx(
                    UINT16      ui2_idx)
{
    UINT8       ui1_font_color = APP_CFG_DCS_CLR_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    switch (ui2_idx)
    {
        case 0:
            ui1_font_color = APP_CFG_DCS_CLR_BROADCAST;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_white);
            break;
        case 1:
            ui1_font_color = APP_CFG_DCS_CLR_BLACK;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_black);
            break;
        case 2:
            ui1_font_color = APP_CFG_DCS_CLR_WHITE;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_white);
            break;
        case 3:
            ui1_font_color = APP_CFG_DCS_CLR_GREEN;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_green);
            break;
        case 4:
            ui1_font_color = APP_CFG_DCS_CLR_BLUE;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_blue);
            break;
        case 5:
            ui1_font_color = APP_CFG_DCS_CLR_RED;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_red);
            break;
        case 6:
            ui1_font_color = APP_CFG_DCS_CLR_CYAN;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_cyan);
            break;
        case 7:
            ui1_font_color = APP_CFG_DCS_CLR_YELLOW;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_yellow);
            break;
        case 8:
            ui1_font_color = APP_CFG_DCS_CLR_MAGENTA;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_magenta);
            break;
        default:
            ui1_font_color = APP_CFG_DCS_CLR_BROADCAST;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_broadcast);
            break;
    }

    MENU_LOG_ON_FAIL(a_cfg_set_dcs(APP_CFG_RECID_DCS_FONT_COLOR, ui1_font_color));
    MENU_LOG_ON_FAIL(_cap_stl_update_info());

    rest_event_notify("tv_settings/closed_captions/digital_style", 0, ""); //dolphin 20200505n add restap notify

    return;
}

/*----------------------------------------------------------------------------
 * Name: _get_font_color_idx
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
static UINT16 _get_font_color_idx(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_idx = 0;
    UINT8       ui1_font_color = APP_CFG_DCS_CLR_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    i4_ret = a_cfg_get_dcs(APP_CFG_RECID_DCS_FONT_COLOR, &ui1_font_color);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (ui1_font_color)
    {
        case APP_CFG_DCS_CLR_BROADCAST:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_white);
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_CLR_BLACK:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_black);
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_CLR_WHITE:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_white);
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_CLR_GREEN:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_green);
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_CLR_BLUE:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_blue);
            ui2_idx = 4;
            break;
        case APP_CFG_DCS_CLR_RED:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_red);
            ui2_idx = 5;
            break;
        case APP_CFG_DCS_CLR_CYAN:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_cyan);
            ui2_idx = 6;
            break;
        case APP_CFG_DCS_CLR_YELLOW:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_yellow);
            ui2_idx = 7;
            break;
        case APP_CFG_DCS_CLR_MAGENTA:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_magenta);
            ui2_idx = 8;
            break;
        default:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_broadcast);
            ui2_idx = 0;
            break;
    }

    return  ui2_idx;
}


UINT16 menu_get_font_color_idx(VOID)
{
    return _get_font_color_idx();
}

/*----------------------------------------------------------------------------
 * Name: _get_font_color_text
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
static VOID _get_font_color_text(
                    UINT16      ui2_idx,   /* in */
                    UTF16_T*    w2s_str,   /* out */
                    SIZE_T      z_len)     /* in, len of w2s_str */
{
    if (ui2_idx > 8)
    {
        ui2_idx = 0;
    }

    if (1 == _get_cap_stl_idx())
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_COL_0 + ui2_idx),
                         (UINT32)z_len);
    }
    else
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_STL_1),
                         (UINT32)z_len);

    }

    w2s_str[z_len - 1] = '\0';

    return;
}


/*----------------------------------------------------------------------------
 * Name: _set_font_opac_idx
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
static VOID _set_font_opac_idx(
                    UINT16      ui2_idx)
{
    UINT8       ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;
    BOOL        b_is_font_flash = FALSE;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    switch (ui2_idx)
    {
        case 0:
            ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
            b_is_font_flash = FALSE;
            break;
        case 1:
            ui1_font_opac = APP_CFG_DCS_OP_SOLID;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
            b_is_font_flash = FALSE;
            break;
        case 2:
            ui1_font_opac = APP_CFG_DCS_OP_TRANSLUCENT;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_transl);
            b_is_font_flash = FALSE;
            break;
        case 3:
            ui1_font_opac = APP_CFG_DCS_OP_TRANSPARENT;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_transp);
            b_is_font_flash = FALSE;
            break;
        case 4:
			ui1_font_opac = APP_CFG_DCS_OP_FLASH;
			CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
			b_is_font_flash = TRUE;
			break;
        default:
            ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
            b_is_font_flash = FALSE;
            break;
    }

    pt_this->t_cc_info.t_pen_color.b_is_flash_fg = b_is_font_flash;
    MENU_LOG_ON_FAIL(a_cfg_set_dcs(APP_CFG_RECID_DCS_FONT_OPACITY, ui1_font_opac));
    MENU_LOG_ON_FAIL(_cap_stl_update_info());

    rest_event_notify("tv_settings/closed_captions/digital_style", 0, ""); //dolphin 20200505n add restap notify

    return;
}

/*----------------------------------------------------------------------------
 * Name: _get_font_opac_idx
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
static UINT16 _get_font_opac_idx(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_idx = 0;
    UINT8       ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;
    BOOL        b_is_font_flash = FALSE;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    i4_ret = a_cfg_get_dcs(APP_CFG_RECID_DCS_FONT_OPACITY, &ui1_font_opac);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (ui1_font_opac)
    {
        case APP_CFG_DCS_OP_BROADCAST:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
            b_is_font_flash = FALSE;
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_OP_SOLID:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
            b_is_font_flash = FALSE;
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_OP_TRANSLUCENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_transl);
            b_is_font_flash = FALSE;
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_OP_TRANSPARENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_transp);
            b_is_font_flash = FALSE;
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_OP_FLASH:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
            b_is_font_flash = TRUE;
            ui2_idx = 4;
			break;
        default:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
            b_is_font_flash = FALSE;
            ui2_idx = 0;
            break;
    }

    pt_this->t_cc_info.t_pen_color.b_is_flash_fg = b_is_font_flash;

    return  ui2_idx;
}

UINT16 menu_get_font_opac_idx(VOID)
{
    return _get_font_opac_idx();
}

/*----------------------------------------------------------------------------
 * Name: _get_font_opac_text
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
static VOID _get_font_opac_text(
                    UINT16      ui2_idx,   /* in */
                    UTF16_T*    w2s_str,   /* out */
                    SIZE_T      z_len)     /* in, len of w2s_str */
{
    if (ui2_idx > 4)
    {
        ui2_idx = 0;
    }

    if (1 == _get_cap_stl_idx())
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_OP_0 + ui2_idx),
                         (UINT32)z_len);
    }
    else
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_STL_1),
                         (UINT32)z_len);

    }

    w2s_str[z_len - 1] = '\0';

    return;
}


/*----------------------------------------------------------------------------
 * Name: _set_bg_color_idx
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
static VOID _set_bg_color_idx(
                    UINT16      ui2_idx)
{
    UINT8       ui1_bg_color = APP_CFG_DCS_CLR_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    switch (ui2_idx)
    {
        case 0:
            ui1_bg_color = APP_CFG_DCS_CLR_BROADCAST;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_broadcast);
            break;
        case 1:
            ui1_bg_color = APP_CFG_DCS_CLR_BLACK;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_black);
            break;
        case 2:
            ui1_bg_color = APP_CFG_DCS_CLR_WHITE;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_white);
            break;
        case 3:
            ui1_bg_color = APP_CFG_DCS_CLR_GREEN;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_green);
            break;
        case 4:
            ui1_bg_color = APP_CFG_DCS_CLR_BLUE;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_blue);
            break;
        case 5:
            ui1_bg_color = APP_CFG_DCS_CLR_RED;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_red);
            break;
        case 6:
            ui1_bg_color = APP_CFG_DCS_CLR_CYAN;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_cyan);
            break;
        case 7:
            ui1_bg_color = APP_CFG_DCS_CLR_YELLOW;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_yellow);
            break;
        case 8:
            ui1_bg_color = APP_CFG_DCS_CLR_MAGENTA;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_magenta);
            break;
        default:
            ui1_bg_color = APP_CFG_DCS_CLR_BROADCAST;
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_broadcast);
            break;
    }

    MENU_LOG_ON_FAIL(a_cfg_set_dcs(APP_CFG_RECID_DCS_BK_COLOR, ui1_bg_color));
    MENU_LOG_ON_FAIL(_cap_stl_update_info());

    rest_event_notify("tv_settings/closed_captions/digital_style", 0, ""); //dolphin 20200505n add restap notify

    return;
}

/*----------------------------------------------------------------------------
 * Name: _get_bg_color_idx
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
static UINT16 _get_bg_color_idx(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_idx = 0;
    UINT8       ui1_bg_color = APP_CFG_DCS_CLR_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    i4_ret = a_cfg_get_dcs(APP_CFG_RECID_DCS_BK_COLOR, &ui1_bg_color);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (ui1_bg_color)
    {
        case APP_CFG_DCS_CLR_BROADCAST:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_broadcast);
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_CLR_BLACK:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_black);
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_CLR_WHITE:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_white);
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_CLR_GREEN:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_green);
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_CLR_BLUE:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_blue);
            ui2_idx = 4;
            break;
        case APP_CFG_DCS_CLR_RED:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_red);
            ui2_idx = 5;
            break;
        case APP_CFG_DCS_CLR_CYAN:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_cyan);
            ui2_idx = 6;
            break;
        case APP_CFG_DCS_CLR_YELLOW:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_yellow);
            ui2_idx = 7;
            break;
        case APP_CFG_DCS_CLR_MAGENTA:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_magenta);
            ui2_idx = 8;
            break;
        default:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_broadcast);
            ui2_idx = 0;
            break;
    }

    return  ui2_idx;
}

UINT16 menu_get_bg_color_idx(VOID)
{
    return _get_bg_color_idx();
}

/*----------------------------------------------------------------------------
 * Name: _get_bg_color_text
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
static VOID _get_bg_color_text(
                    UINT16      ui2_idx,   /* in */
                    UTF16_T*    w2s_str,   /* out */
                    SIZE_T      z_len)     /* in, len of w2s_str */
{
    if (ui2_idx > 8)
    {
        ui2_idx = 0;
    }

    if (1 == _get_cap_stl_idx())
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_COL_0 + ui2_idx),
                         (UINT32)z_len);
    }
    else
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_STL_1),
                         (UINT32)z_len);

    }

    w2s_str[z_len - 1] = '\0';

    return;
}

/*----------------------------------------------------------------------------
 * Name: _set_text_edges_color_idx
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
static VOID _set_text_edges_color_idx(
                    UINT16      ui2_idx)
{
    UINT8       ui1_text_edges_color = APP_CFG_DCS_TYPE_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    switch (ui2_idx)
    {
        case 0:
            ui1_text_edges_color = APP_CFG_DCS_CLR_BROADCAST;
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_broadcast;
            break;
        case 1:
            ui1_text_edges_color = APP_CFG_DCS_CLR_BLACK;
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_black;
            break;
		case 2:
			ui1_text_edges_color = APP_CFG_DCS_CLR_WHITE;
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_white;
			break;
        case 3:
            ui1_text_edges_color = APP_CFG_DCS_CLR_GREEN;
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_green;
            break;
        case 4:
            ui1_text_edges_color = APP_CFG_DCS_CLR_BLUE;
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_blue;
            break;
		 case 5:
		 	ui1_text_edges_color = APP_CFG_DCS_CLR_RED;
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_red;
		  	break;
         case 6:
            ui1_text_edges_color = APP_CFG_DCS_CLR_CYAN;
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_cyan;
            break;
		 case 7:
            ui1_text_edges_color = APP_CFG_DCS_CLR_YELLOW;
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_yellow;
            break;
		 case 8:
            ui1_text_edges_color = APP_CFG_DCS_CLR_MAGENTA;
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_magenta;
            break;
		 default:
			ui1_text_edges_color = APP_CFG_DCS_CLR_BROADCAST;
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_broadcast;
		 	break;
    }


    MENU_LOG_ON_FAIL(a_cfg_set_dcs(APP_CFG_RECID_DCS_EDGE_COLOR, ui1_text_edges_color));

	/*If the text edge color is not set as as broadcast then set the edge opac as solid*/
	if(ui1_text_edges_color != APP_CFG_DCS_CLR_BROADCAST)
	{
		MENU_LOG_ON_FAIL(a_cfg_set_dcs(APP_CFG_RECID_DCS_EDGE_OPACITY, APP_CFG_DCS_OP_SOLID));
	}
    MENU_LOG_ON_FAIL(_cap_stl_update_info());

    rest_event_notify("tv_settings/closed_captions/digital_style", 0, ""); //dolphin 20200505n add restap notify

    return;

}

/*----------------------------------------------------------------------------
 * Name: _get_text_edges_color_idx
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
static UINT16 _get_text_edges_color_idx(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_idx = 0;
    UINT8       ui1_edge_color = APP_CFG_DCS_TYPE_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    i4_ret = a_cfg_get_dcs(APP_CFG_RECID_DCS_EDGE_COLOR, &ui1_edge_color);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (ui1_edge_color)
    {
        case APP_CFG_DCS_CLR_BROADCAST:
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_white;
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_CLR_BLACK:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_black;
            ui2_idx = 1;
            break;
	    case APP_CFG_DCS_CLR_WHITE:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_white;
            ui2_idx = 2;
			break;
        case APP_CFG_DCS_CLR_GREEN:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_green;
            ui2_idx = 3;
            break;
	  	case APP_CFG_DCS_CLR_BLUE:
	        pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_blue;
	        ui2_idx = 4;
	        break;
        case APP_CFG_DCS_CLR_RED:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_red;
            ui2_idx = 5;
            break;
		case APP_CFG_DCS_CLR_CYAN:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_cyan;
            ui2_idx = 6;
            break;
		case APP_CFG_DCS_CLR_YELLOW:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_yellow;
            ui2_idx = 7;
            break;
		case APP_CFG_DCS_CLR_MAGENTA:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_magenta;
            ui2_idx = 8;
            break;
        default:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_broadcast;
            ui2_idx = 0;
            break;
    }

    return  ui2_idx;

}

UINT16 menu_get_text_edges_color_idx(VOID)
{
    return _get_text_edges_color_idx();
}

/*----------------------------------------------------------------------------
 * Name: _get_text_edges_color_text
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
static VOID _get_text_edges_color_text(
                    UINT16      ui2_idx,   /* in */
                    UTF16_T*    w2s_str,   /* out */
                    SIZE_T      z_len)     /* in, len of w2s_str */
{
    if (ui2_idx > 8)
    {
        ui2_idx = 0;
    }

    if (1 == _get_cap_stl_idx())
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_COL_0 + ui2_idx),
                         (UINT32)z_len);
    }
    else
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_STL_1),
                         (UINT32)z_len);

    }

    w2s_str[z_len - 1] = '\0';
    return;
}


/*----------------------------------------------------------------------------
 * Name: _set_text_edges_idx
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
static VOID _set_text_edges_idx(
                    UINT16      ui2_idx)
{
    UINT8       ui1_text_edges = APP_CFG_DCS_TYPE_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    switch (ui2_idx)
    {
        case 0:
            ui1_text_edges = APP_CFG_DCS_TYPE_BROADCAST;
			pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
            break;
        case 1:
            ui1_text_edges = APP_CFG_DCS_TYPE_NONE;
			pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
            break;
		case 2:
			ui1_text_edges = APP_CFG_DCS_TYPE_RAISED;
			pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_RAISED;
			break;
        case 3:
            ui1_text_edges = APP_CFG_DCS_TYPE_DEPRESSED;
			pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_DEPRESSED;
            break;
        case 4:
            ui1_text_edges = APP_CFG_DCS_TYPE_UNIFORM;
			pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_UNIFORM;
            break;
		 case 5:
		 	ui1_text_edges = APP_CFG_DCS_TYPE_RIGHT_DROP_SHADOW;
			pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_RIGHT_DROP_SHADOW;
		  	break;
        default:
            ui1_text_edges = APP_CFG_DCS_TYPE_BROADCAST;
			pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
            break;
    }

    MENU_LOG_ON_FAIL(a_cfg_set_dcs(APP_CFG_RECID_DCS_EDGE_TYPE, ui1_text_edges));
    MENU_LOG_ON_FAIL(_cap_stl_update_info());

    rest_event_notify("tv_settings/closed_captions/digital_style", 0, ""); //dolphin 20200505n add restap notify

    return;

}

/*----------------------------------------------------------------------------
 * Name: _get_text_edges_idx
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
static UINT16 _get_text_edges_idx(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_idx = 0;
    UINT8       ui1_edge_type = APP_CFG_DCS_TYPE_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    i4_ret = a_cfg_get_dcs(APP_CFG_RECID_DCS_EDGE_TYPE, &ui1_edge_type);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (ui1_edge_type)
    {
        case APP_CFG_DCS_TYPE_BROADCAST:
			pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_TYPE_NONE:
            pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
            ui2_idx = 1;
            break;
	    case APP_CFG_DCS_TYPE_RAISED:
            pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_RAISED;
            ui2_idx = 2;
			break;
        case APP_CFG_DCS_TYPE_DEPRESSED:
            pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_DEPRESSED;
            ui2_idx = 3;
            break;
	  case APP_CFG_DCS_TYPE_UNIFORM:
	        pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_UNIFORM;
	        ui2_idx = 4;
	        break;
        case APP_CFG_DCS_TYPE_RIGHT_DROP_SHADOW:
            pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_RIGHT_DROP_SHADOW;
            ui2_idx = 5;
            break;
        default:
            pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
            ui2_idx = 0;
            break;
    }

    return  ui2_idx;

}

UINT16 menu_get_text_edges_idx(VOID)
{
	return _get_text_edges_idx();
}

/*----------------------------------------------------------------------------
 * Name: _get_text_edges_text
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
static VOID _get_text_edges_text(
                    UINT16      ui2_idx,   /* in */
                    UTF16_T*    w2s_str,   /* out */
                    SIZE_T      z_len)     /* in, len of w2s_str */
{
    if (ui2_idx > 5)
    {
        ui2_idx = 0;
    }

    if (1 == _get_cap_stl_idx())
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_TEXT_EDGES_AS_BROADCAST + ui2_idx),
                         (UINT32)z_len);
    }
    else
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_TEXT_EDGES_AS_BROADCAST),
                         (UINT32)z_len);

    }

    w2s_str[z_len - 1] = '\0';
    return;
}

/*----------------------------------------------------------------------------
 * Name: _set_bg_opac_idx
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
static VOID _set_bg_opac_idx(
                    UINT16  ui2_idx)
{
    UINT8       ui1_bg_opac = APP_CFG_DCS_OP_BROADCAST;
    BOOL        b_is_bk_flash = FALSE;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    switch (ui2_idx)
    {
        case 0:
            ui1_bg_opac = APP_CFG_DCS_OP_BROADCAST;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            break;
        case 1:
            ui1_bg_opac = APP_CFG_DCS_OP_SOLID;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            break;
        case 2:
            ui1_bg_opac = APP_CFG_DCS_OP_TRANSLUCENT;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_transl);
            b_is_bk_flash = FALSE;
            break;
        case 3:
            ui1_bg_opac = APP_CFG_DCS_OP_TRANSPARENT;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_transp);
            b_is_bk_flash = FALSE;
            break;
        case 4:
			ui1_bg_opac = APP_CFG_DCS_OP_FLASH;
			CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
			b_is_bk_flash = TRUE;
			break;
        default:
            ui1_bg_opac = APP_CFG_DCS_OP_BROADCAST;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            break;
    }

    pt_this->t_cc_info.t_pen_color.b_is_flash_bk = b_is_bk_flash;
    MENU_LOG_ON_FAIL(a_cfg_set_dcs(APP_CFG_RECID_DCS_BK_OPACITY, ui1_bg_opac));
    MENU_LOG_ON_FAIL(_cap_stl_update_info());

    rest_event_notify("tv_settings/closed_captions/digital_style", 0, ""); //dolphin 20200505n add restap notify

    return;
}


/*----------------------------------------------------------------------------
 * Name: _get_bg_opac_idx
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
static UINT16 _get_bg_opac_idx(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_idx = 0;
    UINT8       ui1_bk_opac = APP_CFG_DCS_OP_BROADCAST;
    BOOL        b_is_bk_flash = FALSE;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    i4_ret = a_cfg_get_dcs(APP_CFG_RECID_DCS_BK_OPACITY, &ui1_bk_opac);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (ui1_bk_opac)
    {
        case APP_CFG_DCS_OP_BROADCAST:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_OP_SOLID:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_OP_TRANSLUCENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_transl);
            b_is_bk_flash = FALSE;
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_OP_TRANSPARENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_transp);
            b_is_bk_flash = FALSE;
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_OP_FLASH:
			CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
			b_is_bk_flash = TRUE;
			ui2_idx = 4;
			break;
        default:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx = 0;
            break;
    }

    pt_this->t_cc_info.t_pen_color.b_is_flash_bk = b_is_bk_flash;

    return  ui2_idx;
}

UINT16 menu_get_bg_opac_idx(VOID)
{
	return _get_bg_opac_idx();
}

/*----------------------------------------------------------------------------
 * Name: _get_bg_opac_text
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
static VOID _get_bg_opac_text(
                    UINT16      ui2_idx,   /* in */
                    UTF16_T*    w2s_str,   /* out */
                    SIZE_T      z_len)     /* in, len of w2s_str */
{
    if(ui2_idx > 4)
    {
        ui2_idx = 0;
    }

    if (1 == _get_cap_stl_idx())
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_OP_0 + ui2_idx),
                         (UINT32)z_len);
    }
    else
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_STL_1),
                         (UINT32)z_len);

    }

    w2s_str[z_len - 1] = '\0';

    return;
}


/*----------------------------------------------------------------------------
 * Name: _set_win_color_idx
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
static VOID _set_win_color_idx(
                    UINT16      ui2_idx)
{
    UINT8       ui1_win_color = APP_CFG_DCS_CLR_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    switch (ui2_idx)
    {
        case 0:
            ui1_win_color = APP_CFG_DCS_CLR_BROADCAST;
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_broadcast);
            break;
        case 1:
            ui1_win_color = APP_CFG_DCS_CLR_BLACK;
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_black);
            break;
        case 2:
            ui1_win_color = APP_CFG_DCS_CLR_WHITE;
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_white);
            break;
        case 3:
            ui1_win_color = APP_CFG_DCS_CLR_GREEN;
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_green);
            break;
        case 4:
            ui1_win_color = APP_CFG_DCS_CLR_BLUE;
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_blue);
            break;
        case 5:
            ui1_win_color = APP_CFG_DCS_CLR_RED;
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_red);
            break;
        case 6:
            ui1_win_color = APP_CFG_DCS_CLR_CYAN;
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_cyan);
            break;
        case 7:
            ui1_win_color = APP_CFG_DCS_CLR_YELLOW;
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_yellow);
            break;
        case 8:
            ui1_win_color = APP_CFG_DCS_CLR_MAGENTA;
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_magenta);
            break;
        default:
            ui1_win_color = APP_CFG_DCS_CLR_BROADCAST;
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_broadcast);
            break;
    }

    MENU_LOG_ON_FAIL(a_cfg_set_dcs(APP_CFG_RECID_DCS_WIN_COLOR, ui1_win_color));
    MENU_LOG_ON_FAIL(_cap_stl_update_info());

    rest_event_notify("tv_settings/closed_captions/digital_style", 0, ""); //dolphin 20200505n add restap notify

    return;
}

/*----------------------------------------------------------------------------
 * Name: _get_win_color_idx
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
static UINT16 _get_win_color_idx(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_idx = 0;
    UINT8       ui1_win_color = APP_CFG_DCS_CLR_BROADCAST;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    i4_ret = a_cfg_get_dcs(APP_CFG_RECID_DCS_WIN_COLOR, &ui1_win_color);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (ui1_win_color)
    {
        case APP_CFG_DCS_CLR_BROADCAST:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_broadcast);
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_CLR_BLACK:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_black);
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_CLR_WHITE:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_white);
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_CLR_GREEN:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_green);
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_CLR_BLUE:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_blue);
            ui2_idx = 4;
            break;
        case APP_CFG_DCS_CLR_RED:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_red);
            ui2_idx = 5;
            break;
        case APP_CFG_DCS_CLR_CYAN:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_cyan);
            ui2_idx = 6;
            break;
        case APP_CFG_DCS_CLR_YELLOW:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_yellow);
            ui2_idx = 7;
            break;
        case APP_CFG_DCS_CLR_MAGENTA:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_magenta);
            ui2_idx = 8;
            break;
        default:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_broadcast);
            ui2_idx = 0;
            break;
    }

    return  ui2_idx;
}

UINT16 menu_get_win_color_idx(VOID)
{
    return _get_win_color_idx();
}

/*----------------------------------------------------------------------------
 * Name: _get_win_color_text
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
static VOID _get_win_color_text(
                    UINT16      ui2_idx,   /* in */
                    UTF16_T*    w2s_str,   /* out */
                    SIZE_T      z_len)     /* in, len of w2s_str */
{
    if(ui2_idx > 8)
    {
        ui2_idx = 0;
    }

    if (1 == _get_cap_stl_idx())
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_COL_0 + ui2_idx),
                         (UINT32)z_len);
    }
    else
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_STL_1),
                         (UINT32)z_len);

    }

    w2s_str[z_len - 1] = '\0';

    return;
}


/*----------------------------------------------------------------------------
 * Name: _set_win_opac_idx
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
static VOID _set_win_opac_idx(
                    UINT16      ui2_idx)
{
    UINT8       ui1_win_opac = APP_CFG_DCS_OP_BROADCAST;
    BOOL        b_is_bk_flash = FALSE;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    switch (ui2_idx)
    {
        case 0:
            ui1_win_opac = APP_CFG_DCS_OP_BROADCAST;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            break;
        case 1:
            ui1_win_opac = APP_CFG_DCS_OP_SOLID;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            break;
        case 2:
            ui1_win_opac = APP_CFG_DCS_OP_TRANSLUCENT;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_transl);
            b_is_bk_flash = FALSE;
            break;
        case 3:
            ui1_win_opac = APP_CFG_DCS_OP_TRANSPARENT;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_transp);
            b_is_bk_flash = FALSE;
            break;
        case 4:
            ui1_win_opac = APP_CFG_DCS_OP_FLASH;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = TRUE;
            break;
        default:
            ui1_win_opac = APP_CFG_DCS_OP_BROADCAST;
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            break;
    }

    pt_this->t_cc_info.t_win_attr.b_is_flash_bk = b_is_bk_flash;

    MENU_LOG_ON_FAIL(a_cfg_set_dcs(APP_CFG_RECID_DCS_WIN_OPACITY, ui1_win_opac));
    MENU_LOG_ON_FAIL(_cap_stl_update_info());

    rest_event_notify("tv_settings/closed_captions/digital_style", 0, ""); //dolphin 20200505n add restap notify

    return;
}

/*----------------------------------------------------------------------------
 * Name: _get_win_opac_idx
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
static UINT16 _get_win_opac_idx(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_idx = 0;
    UINT8       ui1_win_opac = APP_CFG_DCS_OP_BROADCAST;
    BOOL        b_is_bk_flash = FALSE;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    i4_ret = a_cfg_get_dcs(APP_CFG_RECID_DCS_WIN_OPACITY, &ui1_win_opac);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (ui1_win_opac)
    {
        case APP_CFG_DCS_OP_BROADCAST:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx= 0;
            break;
        case APP_CFG_DCS_OP_SOLID:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_OP_TRANSLUCENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_transl);
            b_is_bk_flash = FALSE;
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_OP_TRANSPARENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_transp);
            b_is_bk_flash = FALSE;
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_OP_FLASH:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = TRUE;
            ui2_idx = 4;
            break;
        default:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx = 0;
            break;
    }

    pt_this->t_cc_info.t_win_attr.b_is_flash_bk = b_is_bk_flash;

    return  ui2_idx;
}

UINT16 menu_get_win_opac_idx(VOID)
{
	return _get_win_opac_idx();
}

/*----------------------------------------------------------------------------
 * Name: _get_win_opac_text
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
static VOID _get_win_opac_text(
                    UINT16      ui2_idx,   /* in */
                    UTF16_T*    w2s_str,   /* out */
                    SIZE_T      z_len)     /* in, len of w2s_str */
{
    if (ui2_idx > 4)
    {
        ui2_idx = 0;
    }

    if (1 == _get_cap_stl_idx())
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_OP_0 + ui2_idx),
                         (UINT32)z_len);
    }
    else
    {
        c_uc_w2s_strncpy(w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_CC_STL_STL_1),
                         (UINT32)z_len);

    }

    w2s_str[z_len - 1] = '\0';

    return;
}

/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _on_page_create
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
static INT32 _on_page_create(
                UINT32      ui4_page_id,
                VOID*       pv_create_data)
{
    INT32   i4_ret = MENUR_OK;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;
    MENU_ITEM_T                 t_menu_item;
    MENU_PAGE_TREE_INIT_T       t_tree_init;

    c_memset(&t_g_menu_page_cap_stl_data, 0, sizeof(MENU_PAGE_TREE_INIT_T));
    pt_this->ui4_page_id = ui4_page_id;

    c_memset(&t_tree_init, 0, sizeof(MENU_PAGE_TREE_INIT_T));
    t_tree_init.ui2_max_item_num = MENU_PAGE_CAP_STL_MAX_ITEM_NUM;
    t_tree_init.ui2_msgid_title =  MLM_MENU_KEY_CC_STL;

#ifdef APP_MENU_DCS_NO_FONT_STYLE
    b_fs_support = FALSE;
#endif
#if CS_FS_STYLE_NUM == 1
    b_fs_support = FALSE;
#endif

    /* menu tree page */
    i4_ret = t_g_menu_page_tree.pf_menu_page_create(pt_this->ui4_page_id,
                                                    &t_tree_init);
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_menu_item, 0, sizeof(MENU_PAGE_TREE_INIT_T));
	#if 0
    /* caption style */
    i4_ret = menu_page_tree_list_item(&t_menu_item,
                                      MLM_MENU_KEY_CC_STL_FS,
                                      MLM_MENU_KEY_TAB_HELP_CAP_STL,
                                      MLM_MENU_KEY_CC_STL_STL_1,
                                      MLM_MENU_KEY_CC_STL_STL_2,
                                      _set_cap_stl_idx,
                                      _get_cap_stl_idx);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(pt_this->ui4_page_id,
                                &t_menu_item,
                                &pt_this->ui2_cap_stl_idx);
    MENU_CHK_FAIL(i4_ret);

#endif

	/* font style */
	if(b_fs_support)
	{
		c_memset(&t_menu_item, 0, sizeof(MENU_PAGE_TREE_INIT_T));
		i4_ret = menu_page_tree_list_item(&t_menu_item,
										  MLM_MENU_KEY_CC_STL_FONT_STYLE,
										  MLM_MENU_KEY_HELP_TIP_CAPTION_DCC_FNT_STYLE,
										  MLM_MENU_KEY_CC_STL_AS_BROADCAST,
										  MLM_MENU_KEY_CC_STL_FONT_STYLE_CAPITALS,
										  _set_font_style_idx,
										  _get_font_style_idx);
		MENU_CHK_FAIL(i4_ret);

		t_menu_item.u.t_list.pf_get_text = _get_font_style_text;

		i4_ret = menu_page_tree_add(pt_this->ui4_page_id,
									&t_menu_item,
									&pt_this->ui2_idx_fs_idx);
		MENU_CHK_FAIL(i4_ret);

	}

    c_memset(&t_menu_item, 0, sizeof(MENU_PAGE_TREE_INIT_T));
    /* font size */
    i4_ret = menu_page_tree_list_item(&t_menu_item,
                                       MLM_MENU_KEY_CC_STL_FZ,
                                       MLM_MENU_KEY_HELP_TIP_CAPTION_DCC_FNT_SIZE,
                                       MLM_MENU_KEY_CC_STL_FZ_0,
                                       MLM_MENU_KEY_CC_STL_FZ_3,
                                       _set_font_size_idx,
                                       _get_font_size_idx);
    MENU_CHK_FAIL(i4_ret);

    t_menu_item.u.t_list.pf_get_text = _get_font_size_text;

    i4_ret = menu_page_tree_add(pt_this->ui4_page_id,
                                &t_menu_item,
                                &pt_this->ui2_font_size_idx);
    MENU_CHK_FAIL(i4_ret);


    c_memset(&t_menu_item, 0, sizeof(MENU_PAGE_TREE_INIT_T));
    /* font color */
    i4_ret = menu_page_tree_list_item(&t_menu_item,
                                      MLM_MENU_KEY_CC_STL_FC,
                                      MLM_MENU_KEY_HELP_TIP_CAPTION_DCC_FNT_CLR,
                                      MLM_MENU_KEY_CC_STL_COL_0,
                                      MLM_MENU_KEY_CC_STL_COL_8,
                                      _set_font_color_idx,
                                      _get_font_color_idx);
    MENU_CHK_FAIL(i4_ret);

    t_menu_item.u.t_list.pf_get_text = _get_font_color_text;

    i4_ret = menu_page_tree_add(pt_this->ui4_page_id,
                                &t_menu_item,
                                &pt_this->ui2_font_color_idx);
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_menu_item, 0, sizeof(MENU_PAGE_TREE_INIT_T));
    /* font opacity */
    i4_ret = menu_page_tree_list_item(&t_menu_item,
                                      MLM_MENU_KEY_CC_STL_FO,
                                      MLM_MENU_KEY_HELP_TIP_CAPTION_DCC_FNT_OP,
                                      MLM_MENU_KEY_CC_STL_OP_0,
                                      MLM_MENU_KEY_CC_STL_OP_4,
                                      _set_font_opac_idx,
                                      _get_font_opac_idx);
    MENU_CHK_FAIL(i4_ret);

    t_menu_item.u.t_list.pf_get_text = _get_font_opac_text;

    i4_ret = menu_page_tree_add(pt_this->ui4_page_id,
                                &t_menu_item,
                                &pt_this->ui2_font_opac_idx);
    MENU_CHK_FAIL(i4_ret);

	 c_memset(&t_menu_item, 0, sizeof(MENU_PAGE_TREE_INIT_T));
	 /*Text Edges*/
	  i4_ret = menu_page_tree_list_item(&t_menu_item,
                                      MLM_MENU_KEY_CC_STL_TEXT_EDGES,
                                      MLM_MENU_KEY_CC_STL_TEXT_EDGES_HELP,
                                      MLM_MENU_KEY_CC_STL_TEXT_EDGES_AS_BROADCAST,
                                      MLM_MENU_KEY_CC_STL_TEXT_EDGES_DROP_SHADOW,
                                      _set_text_edges_idx,
                                      _get_text_edges_idx);
    MENU_CHK_FAIL(i4_ret);

    t_menu_item.u.t_list.pf_get_text = _get_text_edges_text;

    i4_ret = menu_page_tree_add(pt_this->ui4_page_id,
		                                &t_menu_item,
		                                &pt_this->ui2_text_edges_idx);
    MENU_CHK_FAIL(i4_ret);

	 /*Text Edges Color*/
	 c_memset(&t_menu_item, 0, sizeof(MENU_PAGE_TREE_INIT_T));

	 i4_ret = menu_page_tree_list_item(&t_menu_item,
                                      MLM_MENU_KEY_CC_STL_TEXT_EDGES_COLOR,
                                      MLM_MENU_KEY_CC_STL_TEXT_EDGES_COLOR_HELP,
                                      MLM_MENU_KEY_CC_STL_COL_0,
                                      MLM_MENU_KEY_CC_STL_COL_8,
                                      _set_text_edges_color_idx,
                                      _get_text_edges_color_idx);
    MENU_CHK_FAIL(i4_ret);

    t_menu_item.u.t_list.pf_get_text = _get_text_edges_color_text;

    i4_ret = menu_page_tree_add(pt_this->ui4_page_id,
		                                &t_menu_item,
		                                &pt_this->ui2_text_edges_color_idx);
    MENU_CHK_FAIL(i4_ret);


    c_memset(&t_menu_item, 0, sizeof(MENU_PAGE_TREE_INIT_T));
    /* BG color */
    i4_ret = menu_page_tree_list_item(&t_menu_item,
                                      MLM_MENU_KEY_CC_STL_BC,
                                      MLM_MENU_KEY_HELP_TIP_CAPTION_DCC_BK_CLR,
                                      MLM_MENU_KEY_CC_STL_COL_0,
                                      MLM_MENU_KEY_CC_STL_COL_8,
                                      _set_bg_color_idx,
                                      _get_bg_color_idx);
    MENU_CHK_FAIL(i4_ret);

    t_menu_item.u.t_list.pf_get_text = _get_bg_color_text;

    i4_ret = menu_page_tree_add(pt_this->ui4_page_id,
                                &t_menu_item,
                                &pt_this->ui2_bg_color_idx);
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_menu_item, 0, sizeof(MENU_PAGE_TREE_INIT_T));
    /* BG opacity */
    i4_ret = menu_page_tree_list_item(&t_menu_item,
                                      MLM_MENU_KEY_CC_STL_BO,
                                      MLM_MENU_KEY_HELP_TIP_CAPTION_DCC_BK_OP,
                                      MLM_MENU_KEY_CC_STL_OP_0,
                                      MLM_MENU_KEY_CC_STL_OP_4,
                                      _set_bg_opac_idx,
                                      _get_bg_opac_idx);
    MENU_CHK_FAIL(i4_ret);

    t_menu_item.u.t_list.pf_get_text = _get_bg_opac_text;

    i4_ret = menu_page_tree_add(pt_this->ui4_page_id,
                                &t_menu_item,
                                &pt_this->ui2_bg_opac_idx);
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_menu_item, 0, sizeof(MENU_PAGE_TREE_INIT_T));
    /* win color */
    i4_ret = menu_page_tree_list_item(&t_menu_item,
                                      MLM_MENU_KEY_CC_STL_WC,
                                      MLM_MENU_KEY_HELP_TIP_CAPTION_DCC_WIN_CLR,
                                      MLM_MENU_KEY_CC_STL_COL_0,
                                      MLM_MENU_KEY_CC_STL_COL_8,
                                      _set_win_color_idx,
                                      _get_win_color_idx);
    MENU_CHK_FAIL(i4_ret);

    t_menu_item.u.t_list.pf_get_text = _get_win_color_text;

    i4_ret = menu_page_tree_add(pt_this->ui4_page_id,
                                &t_menu_item,
                                &pt_this->ui2_win_color_idx);
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_menu_item, 0, sizeof(MENU_PAGE_TREE_INIT_T));
    /* win opaicty */
    i4_ret = menu_page_tree_list_item(&t_menu_item,
                                      MLM_MENU_KEY_CC_STL_WO,
                                      MLM_MENU_KEY_HELP_TIP_CAPTION_DCC_WIN_OP,
                                      MLM_MENU_KEY_CC_STL_OP_0,
                                      MLM_MENU_KEY_CC_STL_OP_4,
                                      _set_win_opac_idx,
                                      _get_win_opac_idx);
    MENU_CHK_FAIL(i4_ret);

    t_menu_item.u.t_list.pf_get_text = _get_win_opac_text;

    i4_ret = menu_page_tree_add(pt_this->ui4_page_id,
                                &t_menu_item,
                                &pt_this->ui2_win_opac_idx);
    MENU_CHK_FAIL(i4_ret);

    /* init preview */
    i4_ret = _cap_stl_preview_init();
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_destroy
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
static INT32 _on_page_destroy(
                    UINT32      ui4_page_id)
{
    INT32   i4_ret = MENUR_OK;

    i4_ret = t_g_menu_page_tree.pf_menu_page_destroy(ui4_page_id);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_show
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
static INT32 _on_page_show(
                    UINT32      ui4_page_id)
{
    INT32   i4_ret = MENUR_OK;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    i4_ret = t_g_menu_page_tree.pf_menu_page_show(ui4_page_id);
    MENU_CHK_FAIL(i4_ret);

    if (1 == _get_cap_stl_idx())
    {
        _set_cap_stl_custom(TRUE);

        /* Show the caption preview */
        i4_ret = c_wgl_set_visibility(pt_this->h_cc_preview,
                                      WGL_SW_NORMAL);
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        _set_cap_stl_custom(TRUE);

        /* Show the caption preview */
        i4_ret = c_wgl_set_visibility(pt_this->h_cc_preview,
                                      WGL_SW_HIDE);
        MENU_CHK_FAIL(i4_ret);
    }


    pt_this->b_page_is_show = TRUE;

    i4_ret = _cap_stl_update_info();
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_hide
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
static INT32 _on_page_hide(
                    UINT32      ui4_page_id)
{
    INT32   i4_ret = MENUR_OK;
    MENU_PAGE_CAP_STL_DATA_T*   pt_this = &t_g_menu_page_cap_stl_data;

    pt_this->b_page_is_show = FALSE;

    i4_ret = t_g_menu_page_tree.pf_menu_page_hide(ui4_page_id);
    MENU_CHK_FAIL(i4_ret);

    /* Hide the caption preview */
    i4_ret = c_wgl_set_visibility(pt_this->h_cc_preview,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);
	
    i4_ret = _cap_stl_update_info();
    MENU_CHK_FAIL(i4_ret);

    /* Update the CC Handler */
    i4_ret = a_cfg_update_dcs();
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_get_focus
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
static INT32 _on_page_get_focus(
                    UINT32              ui4_page_id,
                    MENU_PAGE_HINT_T*   pt_hint)
{
    INT32   i4_ret = MENUR_OK;

    i4_ret = t_g_menu_page_tree.pf_menu_page_get_focus(ui4_page_id,
                                                       pt_hint);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_lose_focus
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
static INT32 _on_page_lose_focus(
                    UINT32      ui4_page_id)
{
    INT32   i4_ret = MENUR_OK;

    i4_ret = t_g_menu_page_tree.pf_menu_page_lose_focus(ui4_page_id);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_update
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
static INT32 _on_page_update(
                    UINT32      ui4_page_id,
                    UINT32      ui4_update_mask)
{
    INT32   i4_ret = MENUR_OK;

    i4_ret = t_g_menu_page_tree.pf_menu_page_update(ui4_page_id,
                                                    ui4_update_mask);
    MENU_CHK_FAIL(i4_ret);
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_atsc_page_cap_stl_init
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
extern INT32 menu_atsc_page_cap_stl_init(VOID)
{
    t_g_menu_atsc_page_cap_stl.pf_menu_page_create      = _on_page_create;
    t_g_menu_atsc_page_cap_stl.pf_menu_page_destroy     = _on_page_destroy;
    t_g_menu_atsc_page_cap_stl.pf_menu_page_show        = _on_page_show;
    t_g_menu_atsc_page_cap_stl.pf_menu_page_hide        = _on_page_hide;
    t_g_menu_atsc_page_cap_stl.pf_menu_page_get_focus   = _on_page_get_focus;
    t_g_menu_atsc_page_cap_stl.pf_menu_page_lose_focus  = _on_page_lose_focus;
    t_g_menu_atsc_page_cap_stl.pf_menu_page_update      = _on_page_update;

    return MENUR_OK;
}

void a_mtktvapi_cap_set_attr(INT32 i4_attr_type,INT32 i4_type_value)
{
    return;
}

BOOL a_menu_get_cc_preview_visiable(VOID)
{
    return t_g_menu_page_cap_stl_data.b_page_is_show;
}

#endif /* ATSC_CAP_STL_ENABLE */

