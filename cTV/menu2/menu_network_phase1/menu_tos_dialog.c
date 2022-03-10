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
 *                                                                             *
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
 * $RCSfile: ui.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *
 *
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_NETWORK_SUPPORT
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
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_dt.h"

#include "menu2/menu_util2.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_common/menu_page_animation.h"
#include "menu_tos_dialog.h"

#include "res/menu2/menu_custom.h"
#include "res/menu2/menu_img.h"

#include "app_util/a_cfg.h"
#include "app_util/a_network.h"

#include "c_time_msrt.h"
#include "u_time_msrt_name.h"
#include <sys/time.h>

#include "res/wdk/wdk_img.h"
#include "res/app_util/network/network_custom.h"

#ifdef LINUX_TURNKEY_SOLUTION
#include <stdlib.h>
#include <stdio.h>
#endif
#include "menu2/menu_dbg.h"

#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct _MENU_TOS_DIALOG_T
{
    HANDLE_T h_root_frm;
    HANDLE_T h_tos_dialog_frm;
    HANDLE_T h_tos_dialog_title;
    HANDLE_T h_tos_dialog_text;
    HANDLE_T h_tos_dialog_btn;
    HANDLE_T h_pb;
    HANDLE_T h_eb;
}MENU_TOS_DIALOG_T;

//static BOOL            b_g_default_eb_init = FALSE;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static MENU_TOS_DIALOG_T t_g_tos_dialog_data;

/*-----------------------------------------------------------------------------
                    function implementation
----------------------------------------------------------------------------*/

static INT32 _tos_dialog_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    MENU_TOS_DIALOG_T*              pt_this = &t_g_tos_dialog_data;
    BOOL 		                    b_visible = FALSE;
    INT32                           i4_ret = MENUR_OK;
    nw_dialog_cb_fct                pf_back = NULL;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;

            switch (ui4_keycode)
            {
                case BTN_CURSOR_UP:
                {
                    c_wgl_get_visibility(pt_this->h_eb, &b_visible);

                    if (b_visible)
                    {
                        c_wgl_set_focus(pt_this->h_eb, WGL_SYNC_AUTO_REPAINT);
                        return MENUR_OK;
                    }
                }
                    break;

                case BTN_SELECT:
                case BTN_EXIT:
                case BTN_PREV_PRG:
                case BTN_RETURN:
                {
                    i4_ret = c_wgl_do_cmd(h_widget,
                                          WGL_CMD_GL_GET_ATTACH_DATA,
                                          WGL_PACK(&pf_back),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    menu_tos_dialog_hide(TRUE);
                    if(pf_back != NULL)
                    {
                        pf_back(ui4_keycode);
                    }

                    return WGLR_OK;
                }

                default:
                    break;
            }

            break;
        }
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _menu_tos_dialog_create(VOID)
{
    INT32                         i4_ret = MENUR_OK;
    MENU_TOS_DIALOG_T* pt_this = &t_g_tos_dialog_data;
    GL_RECT_T                     t_rect;
    WGL_COLOR_INFO_T              t_clr_info;
    WGL_FONT_INFO_T               t_fnt_info;
    WGL_IMG_INFO_T                t_img_info;
    WGL_INSET_T t_inset = {
                            8*4/3,
                            8*4/3,
                            3*4/3,
                            0};

    i4_ret = menu_pm_get_root_frm(&pt_this->h_root_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE (& t_rect,
                      SIMPLE_DIALOG_FRAM_X,
                      SIMPLE_DIALOG_FRAM_Y,
                      SIMPLE_DIALOG_FRAM_W,
                      SIMPLE_DIALOG_FRAM_H);

    /* create widget */
    i4_ret = c_wgl_create_widget (pt_this->h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 & t_rect,
                                 NULL,
                                 255,
                                 NULL,
                                 0,
                                 &pt_this->h_tos_dialog_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_dialog_box_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_box_v2;
    t_img_info.u_img_data.t_standard.t_disable = h_g_dialog_box_v2;
    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_frm,
                       WGL_CMD_GL_SET_IMAGE,
                       WGL_PACK(WGL_IMG_BK),
                       WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
              SIMPLE_DIALOG_TITLE_X,
              SIMPLE_DIALOG_TITLE_Y,
              SIMPLE_DIALOG_TITLE_W,
              SIMPLE_DIALOG_TITLE_H);

    i4_ret = c_wgl_create_widget(pt_this->h_tos_dialog_frm,
                          HT_WGL_WIDGET_TEXT,
                          WGL_CONTENT_TEXT_DEF,
                          WGL_BORDER_TRANSP,
                          &t_rect,
                          NULL,
                          255,
                          (VOID*)(WGL_STL_TEXT_MAX_128 |WGL_STL_TEXT_MULTILINE),
                          NULL,
                          &pt_this->h_tos_dialog_title);
    if (i4_ret < 0)
    {
    return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_title,
                       WGL_CMD_TEXT_SET_CNT_INSET,
                       &t_inset,
                       NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_title,
                       WGL_CMD_TEXT_SET_ALIGN,
                       (VOID*)WGL_AS_CENTER_CENTER,
                       NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_this->h_tos_dialog_title,
                        WGL_CMD_GL_SET_FONT,
                        (void*)&t_fnt_info,
                        NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_title,
                       WGL_CMD_GL_SET_COLOR,
                       WGL_PACK(WGL_CLR_TEXT),
                       WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    /* create text  */
    SET_RECT_BY_SIZE(&t_rect,
              SIMPLE_DIALOG_TEXT_X,
              SIMPLE_DIALOG_TEXT_Y,
              SIMPLE_DIALOG_TEXT_W,
              SIMPLE_DIALOG_TEXT_H);

    i4_ret = c_wgl_create_widget(pt_this->h_tos_dialog_frm,
                              HT_WGL_WIDGET_TEXT,
                              WGL_CONTENT_TEXT_DEF,
                              WGL_BORDER_TRANSP,
                              &t_rect,
                              NULL,
                              255,
                              (VOID*)(WGL_STL_TEXT_MAX_128 |WGL_STL_TEXT_MULTILINE),
                              NULL,
                              &pt_this->h_tos_dialog_text);
    if (i4_ret < 0)
    {
     return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_text,
                       WGL_CMD_TEXT_SET_CNT_INSET,
                       &t_inset,
                       NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_text,
                       WGL_CMD_TEXT_SET_ALIGN,
                       (VOID*)WGL_AS_CENTER_CENTER,
                       NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_this->h_tos_dialog_text,
                        WGL_CMD_GL_SET_FONT,
                        (void*)&t_fnt_info,
                        NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_text,
                       WGL_CMD_GL_SET_COLOR,
                       WGL_PACK(WGL_CLR_TEXT),
                       WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     SIMPLE_DIALOG_BTN_X,
                     SIMPLE_DIALOG_BTN_Y,
                     SIMPLE_DIALOG_BTN_W,
                     SIMPLE_DIALOG_BTN_H);

    i4_ret = c_wgl_create_widget(pt_this->h_tos_dialog_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _tos_dialog_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &pt_this->h_tos_dialog_btn);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_btn,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_this->h_tos_dialog_btn,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_btn,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_dialog_button_gray_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_button_highlight_v2;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_dialog_button_gray_v2;
    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_btn,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

#if 0
    /* Create progressbar */
    i4_ret = _menu_network_pb_create(pt_this->h_tos_dialog_frm,
                                     NULL, &pt_this->h_pb);
    MENU_LOG_ON_FAIL(i4_ret);



    /* Create editbox */
    i4_ret = _menu_network_eb_create(pt_this->h_tos_dialog_frm,
                                     _eb_iperf_port_fct,
                                     &pt_this->h_eb);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /* set visibility */
    i4_ret = c_wgl_set_visibility(pt_this->h_tos_dialog_frm, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT32 menu_tos_dialog_init(VOID)
{
    INT32                         i4_ret = MENUR_OK;
    MENU_TOS_DIALOG_T* pt_this = &t_g_tos_dialog_data;

    c_memset(pt_this, 0, sizeof(MENU_TOS_DIALOG_T));

    i4_ret = _menu_tos_dialog_create();
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT32 menu_tos_dialog_show(UINT16      ui2_msgid_title,
                                    UINT16      ui2_msgid_text,
                                    UINT16      ui2_msgid_btn,
                                    menu_tos_dialog_cb_fct  pf_back,
                                    BOOL         b_repaint)
{
    MENU_TOS_DIALOG_T* pt_this = &t_g_tos_dialog_data;
    INT32 i4_ret = MENUR_OK;
    WGL_FONT_INFO_T  t_fnt_info;
    GL_RECT_T        t_rect;
    #ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
    #endif
    SET_RECT_BY_SIZE(
                    &t_rect,
                    0,
                    0,
                    SIMPLE_DIALOG_TITLE_W,
                    SIMPLE_DIALOG_TITLE_H * 4 / 3
                    );

     i4_ret = c_wgl_move(pt_this->h_tos_dialog_title,
                         &t_rect, WGL_NO_AUTO_REPAINT);
     MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_focus(pt_this->h_tos_dialog_btn, WGL_SYNC_AUTO_REPAINT);

    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_this->h_tos_dialog_title,
                            WGL_CMD_GL_SET_FONT,
                            (void*)&t_fnt_info,
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

     /* Set Alignment */
     i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_title,
                           WGL_CMD_TEXT_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_CENTER,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_btn,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_text)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_btn,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_btn)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = c_wgl_set_focus(pt_this->h_tos_dialog_btn,
                             WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_tos_dialog_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_pb,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_eb,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_tos_dialog_frm,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[256] = {0};

    c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(ui2_msgid_title));
    c_uc_w2s_strcat(w2s_str, _TEXT("."));
    c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(ui2_msgid_text));
    c_uc_w2s_strcat(w2s_str, _TEXT("."));
    c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(ui2_msgid_btn));

    a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif

    return i4_ret;
}

INT32 menu_tos_dialog_hide(BOOL  b_repaint)
{
    MENU_TOS_DIALOG_T* pt_this = &t_g_tos_dialog_data;
    INT32 i4_ret = MENUR_OK;
    #ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
    #endif

#ifdef APP_TTS_SUPPORT
    a_menu_tts_stop();
#endif

    i4_ret = c_wgl_do_cmd(pt_this->h_tos_dialog_btn,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          NULL,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_tos_dialog_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_tos_dialog_frm,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}


#endif /* APP_NETWORK_SUPPORT */

