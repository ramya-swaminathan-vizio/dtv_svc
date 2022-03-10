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
 * $RCSfile: menu_page_divx_info.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_svctx.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "app_util/a_cfg.h"
#include "menu2/menu_dbg.h"

#ifdef COMMON_DIVX_INFO_ENABLE
/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#ifndef  COMMON_DIVX_INFO_X
    #define COMMON_DIVX_INFO_X                  (0)
    #define COMMON_DIVX_INFO_Y                  (0)
    #define COMMON_DIVX_INFO_W                  (CONTENT_W)
    #define COMMON_DIVX_INFO_H                  (CONTENT_H)

    #define COMMON_DIVX_INFO_CNT_INSET_L        (16)
    #define COMMON_DIVX_INFO_CNT_INSET_R        (16)
    #define COMMON_DIVX_INFO_CNT_INSET_T        ( 0)
    #define COMMON_DIVX_INFO_CNT_INSET_B        ( 0)

    #define COMMON_DIVX_INFO_ALIGN              (WGL_AS_CENTER_TOP)
    #define COMMON_DIVX_INFO_FONT_SIZE          (FE_FNT_SIZE_MEDIUM)

    #define DIVX_BTN_DONE_X    (220)
    #define DIVX_BTN_DONE_Y    (300)
    #define DIVX_BTN_DONE_W    (90)
    #define DIVX_BTN_DONE_H    (31)
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_divx_info;

static HANDLE_T     h_cnt_frm;
static HANDLE_T     h_txt_divx_info;
static HANDLE_T     h_btn_divx_done;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _txt_divx_info_create
 *
 * Description:
 *      The version component show the version information.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _txt_divx_info_create(
    HANDLE_T    h_parent,
    HANDLE_T*   ph_widget
){
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    WGL_COLOR_INFO_T            t_clr_info;

    SET_RECT_BY_SIZE (& t_rect,
                      COMMON_DIVX_INFO_X,
                      COMMON_DIVX_INFO_Y,
                      COMMON_DIVX_INFO_W,
                      COMMON_DIVX_INFO_H);

    /* create widget */
    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  NULL,
                                  255,
                                  (VOID*)(WGL_STL_GL_NO_IMG_UI | WGL_STL_TEXT_MAX_512 |
                                          WGL_STL_TEXT_MULTILINE | WGL_STL_TEXT_MAX_DIS_10_LINE),
                                  NULL,
                                  ph_widget);
    MENU_CHK_FAIL(i4_ret);

    /* set font size */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = COMMON_DIVX_INFO_FONT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK (& t_fnt_info),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set content inset */
    t_inset.i4_left     = COMMON_DIVX_INFO_CNT_INSET_L;
    t_inset.i4_right    = COMMON_DIVX_INFO_CNT_INSET_R;
    t_inset.i4_top      = COMMON_DIVX_INFO_CNT_INSET_T;
    t_inset.i4_bottom   = COMMON_DIVX_INFO_CNT_INSET_B;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_TEXT_SET_CNT_INSET,
                           WGL_PACK (& t_inset),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set alignment */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK (COMMON_DIVX_INFO_ALIGN),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set theme */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_transp;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK (WGL_CLR_BK),   /* background color */
                           WGL_PACK (& t_clr_info));
    MENU_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_bk1_txt_hlt;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_bk1_txt_disable;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK (WGL_CLR_TEXT), /* text color */
                           WGL_PACK (& t_clr_info));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _btn_divx_info_create
 *
 * Description:
 *
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _btn_divx_info_create(
    HANDLE_T    h_parent,
    INT32       i4_x,
    INT32       i4_y,
    INT32       i4_w,
    INT32       i4_h,
    UTF16_T*    w2s_name,
    HANDLE_T*   ph_widget
)
{
    GL_RECT_T                       t_rect;
    WGL_FONT_INFO_T                 t_fnt_info;
    WGL_COLOR_INFO_T                t_clr_info;
    WGL_INSET_T                     t_inset;
    INT32                           i4_ret;

#ifdef APP_MENU_IMG_UI
    WGL_IMG_INFO_T                  t_img_info;
#endif /* APP_MENU_IMG_UI */

    /* create icon */
    SET_RECT_BY_SIZE(&t_rect,
                     i4_x,
                     i4_y,
                     i4_w,
                     i4_h);

    i4_ret = c_wgl_create_widget( h_parent,
                                  HT_WGL_WIDGET_BUTTON,
                                  WGL_CONTENT_BUTTON_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)NULL,
                                  NULL,
                                  ph_widget);
    if (i4_ret != WGLR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

     /* set background */
#ifdef APP_MENU_IMG_UI
    t_img_info.e_type                                   = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_menu_img_divx_btn_nor;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_menu_img_divx_btn_nor;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_menu_img_divx_btn_hlt;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_divx_btn_hlt;
    t_img_info.u_img_data.t_extend.t_push               = h_g_menu_img_divx_btn_hlt;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_menu_img_divx_btn_hlt;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);
#else
	t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
	t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_bk0;
	t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_bk0;
	t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_bk0;

	i4_ret = c_wgl_do_cmd(*ph_widget,
	                      WGL_CMD_GL_SET_COLOR,
	                      WGL_PACK(WGL_CLR_BK),
	                      WGL_PACK(&t_clr_info));
	MENU_CHK_FAIL(i4_ret);
#endif

    /* Set text color */
    t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_menu_color_bk1_txt_hlt;
    t_clr_info.u_color_data.t_extend.t_enable             = t_g_menu_color_bk1_txt_hlt;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_menu_color_bk1_txt_hlt;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_bk1_txt_hlt;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_menu_color_bk1_txt_hlt;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_menu_color_bk1_txt_hlt;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    /* Set alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set content insert */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(w2s_name),
                          WGL_PACK(c_uc_w2s_strlen(w2s_name)));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _widgets_proc_fct
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
static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
        case BTN_RETURN:
            menu_nav_back();
            return WMPR_DONE;
        default:
            break;
        }
    }

    case WGL_MSG_NOTIFY:
    {
        HANDLE_T h_source = (HANDLE_T)param1;
        WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)param2;

        if(WGL_NC_BTN_PUSHED == pt_nfy_data->ui4_nc_code)
        {
            if(h_source == h_btn_divx_done)
            {
                menu_nav_back();
                return WMPR_DONE;
            }
        }
        else if(WGL_NC_GL_KEY_DOWN == pt_nfy_data->ui4_nc_code)
        {
            if(BTN_RETURN == pt_nfy_data->u.t_key.ui4_key_code)
            {
                menu_nav_back();
                return WMPR_DONE;
            }
        }

        break;
    }

    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret;
    UTF16_T     w2s_btn_name[8] = {0};

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _txt_divx_info_create(h_cnt_frm, &h_txt_divx_info);
    MENU_CHK_FAIL(i4_ret);

    c_uc_ps_to_w2s("Done", w2s_btn_name, 8);
    i4_ret = _btn_divx_info_create(
                        h_cnt_frm,
                        DIVX_BTN_DONE_X,
                        DIVX_BTN_DONE_Y,
                        DIVX_BTN_DONE_W,
                        DIVX_BTN_DONE_H,
                        w2s_btn_name,
                        &h_btn_divx_done);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id, _widgets_proc_fct);
    MENU_CHK_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility(h_cnt_frm, WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32                           i4_ret;
    UTF16_T                         w2s_tmp_str [16] = { 0 };
    UTF16_T                         w2s_str [376]    = { 0 };
    DIVX_DRM_UNION_GENERIC_INFO_T   t_divx_drm_generic_info;

    c_memset(w2s_tmp_str,              0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,                  0, sizeof(w2s_str));
    c_memset(&t_divx_drm_generic_info, 0, sizeof(DIVX_DRM_UNION_GENERIC_INFO_T));

    c_uc_ps_to_w2s("\n\n", w2s_tmp_str, 16);
    c_uc_w2s_strcpy (w2s_str, w2s_tmp_str);
    c_uc_w2s_strcat (w2s_str, MENU_TEXT(MLM_MENU_KEY_DIVX_CODE_1));
    c_uc_w2s_strcat (w2s_str, w2s_tmp_str);
    c_uc_w2s_strcat (w2s_str, MENU_TEXT(MLM_MENU_KEY_DIVX_CODE_2));

    /* get DivX registration code */
    {
#ifdef ENABLE_MULTIMEDIA
        c_svctx_generic_get_info (menu_get_crnt_svctx(),
                                  NULL_HANDLE,
                                  SVCTX_GENGRIC_GET_TYPE_DIVX_DRM_REGISTRATION_CODE,
                                  &(t_divx_drm_generic_info.t_divx_drm_registration_info.s_registration_code),
                                  sizeof(DIVX_DRM_UNION_GENERIC_INFO_T));
#endif

        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_uc_ps_to_w2s (t_divx_drm_generic_info.t_divx_drm_registration_info.s_registration_code,
                        w2s_tmp_str,
                        c_strlen (t_divx_drm_generic_info.t_divx_drm_registration_info.s_registration_code));
        c_uc_w2s_strcat (w2s_str, w2s_tmp_str);

        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_uc_ps_to_w2s("\n", w2s_tmp_str, 16);
        c_uc_w2s_strcat (w2s_str, w2s_tmp_str);
    }

    c_uc_w2s_strcat (w2s_str, MENU_TEXT(MLM_MENU_KEY_DIVX_CODE_3));

    i4_ret = c_wgl_do_cmd (h_txt_divx_info,
                           WGL_CMD_TEXT_SET_TEXT,
                           WGL_PACK (w2s_str),
                           WGL_PACK (c_uc_w2s_strlen (w2s_str)));
    MENU_CHK_FAIL(i4_ret);

    /* Change the menu title */
    menu_main_set_title(MLM_MENU_KEY_DIVX_INFO);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    c_wgl_set_focus(h_btn_divx_done, WGL_NO_AUTO_REPAINT);

    menu_common_help_show_back();

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

extern INT32 menu_common_page_divx_info_init(VOID)
{
    t_g_menu_common_page_divx_info.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_divx_info.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_divx_info.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_divx_info.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_divx_info.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_divx_info.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_divx_info.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

#ifdef DIVX_DRM_51
extern BOOL menu_common_page_divx_info_need_hide(VOID)
{
#ifdef ENABLE_MULTIMEDIA
    DIVX_DRM_UNION_GENERIC_INFO_T t_divx_drm_generic_info;

    c_memset(&t_divx_drm_generic_info, 0, sizeof(DIVX_DRM_UNION_GENERIC_INFO_T));

    c_svctx_generic_get_info (
              menu_get_crnt_svctx(),
              NULL_HANDLE,
              SVCTX_GENGRIC_GET_TYPE_DIVX_DRM_UI_HELP_INFO,
              &(t_divx_drm_generic_info.t_divx_drm_ui_help_info.ui4_divx_drm_ui_help_info),
              sizeof(DIVX_DRM_UNION_GENERIC_INFO_T));

    return (DIVX_DRM_REGISTRATION_CODE_HIDE & t_divx_drm_generic_info.t_divx_drm_ui_help_info.ui4_divx_drm_ui_help_info);
#else
    return TRUE;
#endif /* ENABLE_MULTIMEDIA */
}
#endif /* DIVX_DRM_51 */

#endif /* COMMON_DIVX_INFO_ENABLE */

