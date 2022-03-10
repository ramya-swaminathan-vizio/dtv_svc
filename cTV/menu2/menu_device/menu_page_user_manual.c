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
 * $RCSfile: menu_page_adv_scan_rng.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/22 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 223730d1bdc36ed27cb26dea5de9232d $
 *
 * Description:
 *      This scan includes both ATV channel scan and DTV channel scan.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_cli.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu_page_user_manual.h"

#include "res/menu2/menu_custom.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/config/acfg_cust_plf_opt.h"
#include "res/app_util/config/acfg_cust_factory.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/model/model.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#ifdef LINUX_TURNKEY_SOLUTION
#include <stdio.h>
#endif

#include "menu2/menu_dbg.h"
#include "rest/a_rest_api.h"

/*-----------------------------------------------------------------------------
                    defines, typedefs, enums
 ----------------------------------------------------------------------------*/

typedef struct _MENU_USER_MANUAL_PAGE_DATA_T
{
    HANDLE_T     h_cnt_frm;
//    UINT32  ui4_user_manual_page_id;

    HANDLE_T    h_text_widget;
    UINT16      ui2_msg_idx;
    UINT16      ui2_url_idx;
}MENU_USER_MANUAL_PAGE_DATA_T;

#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

GL_COLOR_T           t_g_menu_color_user_manual_bk = { 255, {200}, {200 }, {200 }};
GL_COLOR_T           t_g_menu_color_user_manual_txt_nor = { 255, {200}, {200 }, {200 }}; /* Gray color */
GL_COLOR_T           t_g_menu_color_user_manual_txt_hlt = { 255, {255 }, {255 }, {255}}; /* white color */

#define MENU_USER_MANUAL_SIZE_NOT_MATCH     (UINT16)1
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_user_manual;
static MENU_USER_MANUAL_PAGE_DATA_T t_g_user_manual_page_data;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementations
 ----------------------------------------------------------------------------*/
static INT32 _user_manual_page_get_url(void)
{
    CHAR    s_model_name[16+1] = {0};
    MENU_USER_MANUAL_PAGE_DATA_T* pt_this = &t_g_user_manual_page_data;

    a_cfg_custom_get_model_name(s_model_name);

    if(c_strstr(s_model_name, "E24") != NULL)
    {
        pt_this->ui2_url_idx = MLM_MENU_KEY_SCREEN_SIZE_24_INCHES;
        return MENUR_OK;
    }

    if(c_strstr(s_model_name, "E32") != NULL)
    {
        pt_this->ui2_url_idx = MLM_MENU_KEY_SCREEN_SIZE_32_INCHES;
        return MENUR_OK;
    }

    if(c_strstr(s_model_name, "E35") != NULL)
    {
        pt_this->ui2_url_idx = MLM_MENU_KEY_SCREEN_SIZE_35_INCHES;
        return MENUR_OK;
    }

    if(c_strstr(s_model_name, "E50") != NULL)
    {
        pt_this->ui2_url_idx = MLM_MENU_KEY_SCREEN_SIZE_50_INCHES;
        return MENUR_OK;
    }

    return MENUR_FAIL;
}

static INT32 _user_manual_page_backbar_proc_fct(
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32  i4_ret = MENUR_OK;
        MENU_USER_MANUAL_PAGE_DATA_T* pt_this = &t_g_user_manual_page_data;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
            #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
            #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                menu_nav_back();

                return MENUR_OK;
            }

            case BTN_CURSOR_DOWN:
            {
                i4_ret = c_wgl_set_focus(pt_this->h_text_widget,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break ;

            case BTN_CURSOR_UP:
            {
                i4_ret = menu_set_focus_on_homebar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;

            default:
                break ;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _user_manual_page_homebar_proc_fct(
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HOME_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32  i4_ret = MENUR_OK;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
            #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
            #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                UINT32 aui4_pages[1] = {ui4_g_menu_page_main_menu};
                i4_ret = menu_nav_go_direct(0,
                                            aui4_pages,
                                            sizeof(aui4_pages)/sizeof(aui4_pages[0]),
                                            NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }

            case BTN_CURSOR_DOWN:
            {
                i4_ret = menu_set_focus_on_backbar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;

            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

static INT32 _text_proc_fct (HANDLE_T   h_widget,
                                    UINT32     ui4_msg,
                                    VOID*      param1,
                                    VOID*      param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
                menu_set_focus_on_backbar(TRUE);
                return MENUR_OK;
            case BTN_SELECT:
                return MENUR_OK;
            case BTN_RETURN:
                menu_nav_go_home_menu();
                return MENUR_OK;
            case BTN_EXIT:
                return MENUR_OK;
        default:
            break;
        }

        break;
    }

    case WGL_MSG_KEY_UP:
    {
		break;
    }

    case WGL_MSG_GET_FOCUS:
    {
 //       menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TERMS_OF_SERVICE_HELP));
         UINT32 i4_ret = MENUR_OK;
        MENU_USER_MANUAL_PAGE_DATA_T* pt_this = &t_g_user_manual_page_data;
 #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_name_str[256] = {0};
        i4_ret = c_wgl_do_cmd (pt_this->h_text_widget,
                          WGL_CMD_TEXT_GET_TEXT,
                          WGL_PACK (w2s_name_str),
                          WGL_PACK (256));
        MENU_CHK_FAIL(i4_ret);
        if (i4_ret >= 0)
        {
            a_app_tts_play(w2s_name_str, 256);
        }
#endif
		break;
    }

    case WGL_MSG_LOSE_FOCUS:
        break;

    default:
        break;
    }


    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _menu_user_manual_text_create(HANDLE_T     h_parent,
                                     INT32        i4_left,
                                     INT32        i4_top,
                                     INT32        i4_width,
                                     INT32        i4_height,
                                     FE_FNT_STYLE e_font_style,
                                     HANDLE_T     h_normal_bk,
                                     HANDLE_T     h_highlight_bk,
                                     HANDLE_T*    ph_widget)
{

    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      i4_left,
                      i4_top,
                      i4_width,
                      i4_height
                       );

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _text_proc_fct,
                                 255,
                                 (VOID*)( WGL_STL_TEXT_MAX_2048 |
                                          WGL_STL_TEXT_MULTILINE |
                                          WGL_STL_TEXT_MAX_DIS_40_LINE),
                                 NULL,
                                 ph_widget);
    MENU_CHK_FAIL(i4_ret);

    /* set alignment */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_LEFT_TOP),//WGL_AS_LEFT_CENTER
                              NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left     = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_right    = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          WGL_PACK((INT32)0),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* txt info */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_user_manual_bk);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_user_manual_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_user_manual_txt_nor);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_highlight_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_normal_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _user_manual_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32       i4_ret = MENUR_OK;
    MENU_USER_MANUAL_PAGE_DATA_T* pt_this = &t_g_user_manual_page_data;

    c_memset(pt_this, 0, sizeof(MENU_USER_MANUAL_PAGE_DATA_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_this->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_user_manual_text_create(
                         pt_this->h_cnt_frm,
                         USER_MANUAL_MSG_TEXT_X,
                         USER_MANUAL_MSG_TEXT_Y,
                         USER_MANUAL_MSG_TEXT_W,
                         USER_MANUAL_MSG_TEXT_H,
                         FE_FNT_SIZE_LARGE,
                         NULL_HANDLE,
                         NULL_HANDLE,
                         &pt_this->h_text_widget);
    MENU_CHK_FAIL(i4_ret);

    pt_this->ui2_msg_idx = MLM_MENU_KEY_USER_MANUAL_MSG;

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _user_manual_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _menu_user_manual_text_set_text(HANDLE_T  h_widget,
                                            UINT16    ui2_msg_id,
                                            UINT16    ui2_url_id)
{
    INT32 i4_ret = 0;

    UTF16_T    aw2s_text[256] = {0};

    c_uc_w2s_strcpy(aw2s_text, MENU_TEXT(ui2_msg_id));
    c_uc_w2s_strcat(aw2s_text, L"\n");
    c_uc_w2s_strcat(aw2s_text, MENU_TEXT(ui2_url_id));

    i4_ret = c_wgl_do_cmd (h_widget,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (aw2s_text),
                      WGL_PACK (c_uc_w2s_strlen (aw2s_text)));
    MENU_CHK_FAIL(i4_ret);


    return MENUR_OK;
}

static INT32 _user_manual_page_show(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    GL_RECT_T       t_rect = {0};
    HANDLE_T		h_last_shadow_item = NULL_HANDLE;
    MENU_USER_MANUAL_PAGE_DATA_T* pt_this = &t_g_user_manual_page_data;

    menu_set_start_user_manual_flag(TRUE);
    menu_show_backbar(FALSE, FALSE);
    /* pause menu */
    a_amb_pause_app(MENU_NAME);
    /* launch User Manual html. */
    a_rest_app_launch_user_manual();

    return i4_ret;

    i4_ret = menu_main_set_title(MLM_MENU_KEY_HELP_MANUAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _user_manual_page_get_url();
    MENU_CHK_FAIL(i4_ret);

    _menu_user_manual_text_set_text(pt_this->h_text_widget,
                              pt_this->ui2_msg_idx,
                              pt_this->ui2_url_idx);

    i4_ret = menu_set_backbar_proc(_user_manual_page_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(_user_manual_page_homebar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_visibility(pt_this->h_cnt_frm,WGL_SW_RECURSIVE);


    /* adjust last shadow position */
    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;
	t_rect.i4_top = USER_MANUAL_SHADOW_HEIGHT;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;

	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _user_manual_page_hide(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _user_manual_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32       i4_ret = MENUR_OK;

    MENU_USER_MANUAL_PAGE_DATA_T* pt_this = &t_g_user_manual_page_data;

    i4_ret = c_wgl_set_focus(pt_this->h_text_widget, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _user_manual_page_lose_focus(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

static INT32 _user_manual_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

extern INT32 menu_user_manual_page_init(VOID)
{
    t_g_menu_user_manual.pf_menu_page_create =    _user_manual_page_create;
    t_g_menu_user_manual.pf_menu_page_destroy=    _user_manual_page_destroy;
    t_g_menu_user_manual.pf_menu_page_show=       _user_manual_page_show;
    t_g_menu_user_manual.pf_menu_page_hide=       _user_manual_page_hide;
    t_g_menu_user_manual.pf_menu_page_get_focus=  _user_manual_page_get_focus;
    t_g_menu_user_manual.pf_menu_page_lose_focus= _user_manual_page_lose_focus;
    t_g_menu_user_manual.pf_menu_page_update=     _user_manual_page_update;

    return MENUR_OK;
}
