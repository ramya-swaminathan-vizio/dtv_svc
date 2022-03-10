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
 * $RCSfile: menu_page_pwd.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/9 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 9cd3c20f32467f383f0d47c1431bb92b $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"

#include "app_util/a_cfg.h"

#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"

#include "res/menu2/menu_custom.h"
#include "menu2/menu_dbg.h"

#ifdef COMMON_PWD_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define PWD_ALARM_DELAY     2000

#define PWD_GUIDE_TEXT1_X   0
#define PWD_GUIDE_TEXT1_Y   0
#define PWD_GUIDE_TEXT1_W   CONTENT_W
#define PWD_GUIDE_TEXT1_H   28 * 5

#define PWD_EB_X            0
#define PWD_EB_Y            PWD_GUIDE_TEXT1_Y + PWD_GUIDE_TEXT1_H
#define PWD_EB_W            CONTENT_W - CONTENT_DIS
#define PWD_EB_H            44

#define PWD_EB_INSET_T      4
#define PWD_EB_INSET_B      0
#define PWD_EB_INSET_R      (CONTENT_W - CONTENT_DIS)/3
#define PWD_EB_INSET_L      PWD_EB_INSET_R

#define PWD_EB_CNT_INSET_T      0
#define PWD_EB_CNT_INSET_B      0
#define PWD_EB_CNT_INSET_R      2
#define PWD_EB_CNT_INSET_L      2

typedef struct _PWD_FORM
{
   UINT32   ui4_page_id;
   UINT32   ui4_page_id_pass;
   HANDLE_T h_cnt_frm;
   HANDLE_T h_eb_pwd;
   HANDLE_T h_bk_frm_top;
   HANDLE_T h_guide_text1;
   HANDLE_T h_txt_alarm;
}PWD_FORM_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_pwd;


/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _init_txt_alarm
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
static INT32 _init_txt_alarm(HANDLE_T    h_parent,
                             HANDLE_T*   ph_widget,
                             INT32       i4_index,
                             FE_FNT_SIZE e_font_size,
                             UINT8       ui1_align
                             )
{
    INT32           i4_ret;
    UINT32          ui4_style;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_IMG_INFO_T    t_img_info;

    if( 0 == i4_index)
    {
        ui4_style = WGL_STL_GL_NO_IMG_UI
                        | WGL_STL_GL_BDR_FILL_CNT_BK
                    |WGL_STL_TEXT_MAX_128
                    | WGL_STL_TEXT_MULTILINE
                    | WGL_STL_TEXT_MAX_DIS_5_LINE;

        SET_RECT_BY_SIZE(&t_rect,
                         PWD_ALARM_X,
                             PWD_ALARM_Y+MENU_ITEM_V_HEIGHT*i4_index,
                         PWD_ALARM_W,
                         PWD_ALARM_H);

        i4_ret = c_wgl_create_widget(h_parent,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                         WGL_BORDER_TIMG,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     ph_widget);
        if (i4_ret < 0)
        {
            return MENUR_CANT_CREATE_WIDGET;
        }
    }
    else
    {
        ui4_style = WGL_STL_GL_NO_IMG_UI
                    |WGL_STL_TEXT_MAX_128
                    | WGL_STL_TEXT_MULTILINE
                    | WGL_STL_TEXT_MAX_DIS_5_LINE;

        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         PWD_ALARM_Y+MENU_ITEM_V_HEIGHT*i4_index,
                         16*GRID_W+8,
                         PWD_ALARM_H);

        i4_ret = c_wgl_create_widget(h_parent,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     ph_widget);
        if (i4_ret < 0)
        {
            return MENUR_CANT_CREATE_WIDGET;
        }
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = e_font_size;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set content inset */

    WGL_INSET_T         t_inset;
    t_inset.i4_left   = 3;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 8;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL);
    MENU_CHK_FAIL(i4_ret);


    /* set alignment */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (ui1_align),
                              NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_alarm_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_alarm_txt;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_alarm_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_alarm_bk;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_alarm_bk;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_alarm_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);


    if( 0 == i4_index)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
        t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_BDR_TIMG_SET_BK_IMG,
                              WGL_PACK(&t_img_info),
                              WGL_PACK(NULL));
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32           i4_ret;
        PWD_FORM_T*     pt_pwd_form = NULL;
        UINT32          ui4_page_id = 0;
        UINT32          ui4_keycode = (UINT32)pv_param1;

        i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_pwd_form);
        MENU_LOG_ON_FAIL(i4_ret);

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return MENUR_OK;
        #endif
        case BTN_SELECT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_CURSOR_RIGHT:
        case BTN_CURSOR_DOWN:
            /* set highlight of quick_operation & focus on it */
            c_wgl_do_cmd (pt_pwd_form->h_eb_pwd,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(0),
                          NULL);

            c_wgl_set_focus (pt_pwd_form->h_eb_pwd, WGL_SYNC_AUTO_REPAINT);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_PARENT_PIN));
            break;

        case BTN_CURSOR_UP:
            menu_set_focus_on_homebar(TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
            break;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}


/*-----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _homebar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32           i4_ret;
        PWD_FORM_T*     pt_pwd_form = NULL;
        UINT32          ui4_page_id = 0;
        UINT32          ui4_keycode = (UINT32)pv_param1;

        i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_pwd_form);
        MENU_LOG_ON_FAIL(i4_ret);

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return MENUR_OK;
        #endif
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_SELECT :
            menu_nav_go_home_menu();
            return WGLR_OK;

        case BTN_CURSOR_DOWN :
            menu_set_focus_on_backbar (TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _init_guide_text
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

static INT32 _init_guide_text(HANDLE_T h_parent,
                             HANDLE_T* ph_widget,
                             GL_RECT_T* pt_rect)
{
    INT32           i4_ret;
    UINT32          ui4_style;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = WGL_STL_GL_NO_IMG_UI
                |WGL_STL_TEXT_MAX_128
                | WGL_STL_TEXT_MULTILINE
                | WGL_STL_TEXT_MAX_DIS_5_LINE;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_alarm_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_alarm_txt;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_alarm_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_alarm_bk;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_alarm_bk;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_alarm_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ed_pwd_set_attach_data(HANDLE_T h_ed_pwd,
                                     PWD_FORM_T*  pt_pwd_from)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_ed_pwd,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_pwd_from),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ed_pwd_get_attach_data(HANDLE_T h_ed_pwd,
                                     PWD_FORM_T**  ppt_pwd_from)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_ed_pwd,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_pwd_from),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _chg_lang
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
static INT32 _chg_lang(UINT32 ui4_page_id)
{
    INT32   i4_ret = 0;
    PWD_FORM_T* pt_pwd_form = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_pwd_form);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Guide*/
    i4_ret = c_wgl_do_cmd(pt_pwd_form->h_guide_text1,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_PASSWORD_DESCRIPTION)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Edibox password */
    i4_ret = menu_edit_chg_lang(pt_pwd_form->h_eb_pwd, 0);
    MENU_CHK_FAIL(i4_ret);

    /* Alarm */
    i4_ret = c_wgl_do_cmd(pt_pwd_form->h_txt_alarm,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CLRMEM_PWD_HELP_INFO)),
                          WGL_PACK(0xFF));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_pwd_notify
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
static INT32 _on_pwd_notify(HANDLE_T h_eb_pwd, WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    INT32 i4_ret;
    PWD_FORM_T *pt_pwd_form = NULL;

    /* get the pwd form content */
    i4_ret = _ed_pwd_get_attach_data(h_eb_pwd,  &pt_pwd_form);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_EB_CHANGED:
        {
            char s_str[5];
            UTF16_T w2s_str[5];
            c_memset(w2s_str, 0, 5 * sizeof(UTF16_T));
            c_wgl_do_cmd(pt_pwd_form->h_eb_pwd,
                         WGL_CMD_EB_GET_TEXT,
                         (VOID*)w2s_str,
                         (VOID*)5);
            c_uc_w2s_to_ps(w2s_str, s_str, 4);
            if (c_uc_w2s_strlen(w2s_str) == 4)
            {
                BOOL b_pass;

                /* check pwd */
                a_cfg_chk_password(w2s_str, &b_pass);

                /* if valid show parental settting frame */
                if (b_pass)
                {
                    /* delay to waiting for completion of repainting editbox. */
                    c_thread_delay(300);

                    /* clean pwd */
                    c_wgl_do_cmd(pt_pwd_form->h_eb_pwd,
                                 WGL_CMD_EB_SET_TEXT,
                                 NULL,
                                 NULL);

                    /* change page */
                    menu_nav_back_and_go(pt_pwd_form->ui4_page_id_pass, NULL);
                }
                else
                {
                    c_wgl_show(pt_pwd_form->h_txt_alarm,
                               WGL_SW_NORMAL);

                    /* wait for a while */
                    c_thread_delay(PWD_ALARM_DELAY);

                    /* clean pwd */
                    c_wgl_do_cmd(pt_pwd_form->h_eb_pwd,
                                 WGL_CMD_EB_SET_TEXT,
                                 NULL,
                                 NULL);

                    c_wgl_set_visibility(pt_pwd_form->h_txt_alarm,
                                         WGL_SW_HIDE);

                    c_wgl_repaint(pt_pwd_form->h_cnt_frm,
                                  NULL,
                                  TRUE);
                }
            }
            break;
        }
    case WGL_NC_GL_KEY_DOWN:
        {
            switch (pt_nfy_data->u.t_key.ui4_key_code)
            {
            case BTN_PREV_PRG:
            case BTN_RETURN:
                menu_nav_back();
                return WMPR_DONE;

            case BTN_CURSOR_UP:
            case BTN_EXIT:
                /* clean password */
                c_wgl_do_cmd(pt_pwd_form->h_eb_pwd,
                             WGL_CMD_EB_SET_TEXT,
                             NULL,
                             NULL);

                menu_set_focus_on_backbar(TRUE);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                return WMPR_DONE;

            case BTN_CURSOR_DOWN:
                /* clean password */
                c_wgl_do_cmd(pt_pwd_form->h_eb_pwd,
                             WGL_CMD_EB_SET_TEXT,
                             NULL,
                             NULL);
                menu_help_tip_keytip_set_focus(pt_pwd_form->h_eb_pwd,0,FALSE);
                menu_pm_repaint();
                return WMPR_DONE;

            default:
                break;
            }
        }
    default:
        break;
    }
    return WMPR_DONE;
}

/*----------------------------------------------------------------------------
 * Name: _proc_fct
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
static INT32 _proc_fct(HANDLE_T    h_widget,
                       UINT32      ui4_msg,
                       VOID*       param1,
                       VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
            HANDLE_T h_source = (HANDLE_T)param1;
            WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)param2;

            return _on_pwd_notify(h_source, pt_nfy_data);
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _init_edit_box(HANDLE_T h_parent,HANDLE_T* ph_widget,GL_RECT_T* pt_rect)
{
    INT32               i4_ret;
    UINT32              ui4_style;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_EB_KEY_MAP_T    t_eb_key_map;

    ui4_style = WGL_STL_EB_PASSWORD;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 pt_rect,
                                 _proc_fct,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),  /*Attr mask*/
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING)); /*Attr value*/
    MENU_CHK_FAIL(i4_ret);

    /*-------Config UI-------*/

    /* Set Insets */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = PWD_EB_INSET_L;
    t_inset.i4_right    = PWD_EB_INSET_R;
    t_inset.i4_top      = PWD_EB_INSET_T;
    t_inset.i4_bottom   = PWD_EB_INSET_B;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = PWD_EB_CNT_INSET_L;
    t_inset.i4_right    = PWD_EB_CNT_INSET_R;
    t_inset.i4_top      = PWD_EB_CNT_INSET_T;
    t_inset.i4_bottom   = PWD_EB_CNT_INSET_B;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set txt color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_text_entry_small;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_text_entry_small;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_text_entry_small;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set cursor character */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CURSOR_CHAR,
                          (VOID*)_TEXT("_"),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)4),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Enable Cursor Highlight */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_ENABLE_CURSOR_HT,
                          WGL_PACK(TRUE),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_EB_CURSOR),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_enter_editing = BTN_SELECT;
    t_eb_key_map.ui4_backsapce= BTN_CURSOR_LEFT;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    PWD_FORM_T*         pt_pwd_form = NULL;

    do
    {
        /* new password form */
        pt_pwd_form = c_mem_alloc(sizeof(PWD_FORM_T));
        if( pt_pwd_form  == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }
        c_memset(pt_pwd_form, 0, sizeof(PWD_FORM_T));

        /*record the current page id*/
        pt_pwd_form->ui4_page_id = ui4_page_id;

        /*copy the re-direct page information*/
        pt_pwd_form->ui4_page_id_pass = (UINT32)pv_create_data;

       /*get current form*/
        i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_pwd_form->h_cnt_frm);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /*init guide text */
        SET_RECT_BY_SIZE(&t_rect,
                            PWD_GUIDE_TEXT1_X,
                            PWD_GUIDE_TEXT1_Y,
                            PWD_GUIDE_TEXT1_W,
                            PWD_GUIDE_TEXT1_H);
        i4_ret = _init_guide_text(pt_pwd_form->h_cnt_frm, &pt_pwd_form->h_guide_text1,&t_rect);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /*init txt alarm*/
        i4_ret = _init_txt_alarm(pt_pwd_form->h_cnt_frm, &pt_pwd_form->h_txt_alarm, 4, PWD_ALARM_FONT_SIZE, WGL_AS_CENTER_CENTER);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /*init editor*/
        SET_RECT_BY_SIZE(&t_rect,
                            PWD_EB_X,
                            PWD_EB_Y,
                            PWD_EB_W,
                            PWD_EB_H);
        i4_ret = _init_edit_box(pt_pwd_form->h_cnt_frm, &pt_pwd_form->h_eb_pwd,&t_rect);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /* Attach data */
        i4_ret = menu_page_set_data(ui4_page_id, pt_pwd_form);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = _ed_pwd_set_attach_data(pt_pwd_form->h_eb_pwd, pt_pwd_form);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = _chg_lang(ui4_page_id);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = c_wgl_set_visibility(pt_pwd_form->h_cnt_frm, WGL_SW_RECURSIVE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = c_wgl_set_visibility(pt_pwd_form->h_txt_alarm, WGL_SW_HIDE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = c_wgl_set_visibility(pt_pwd_form->h_cnt_frm, WGL_SW_HIDE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = menu_page_set_proc_func(ui4_page_id,
                                     _proc_fct);
        if(i4_ret != MENUR_OK)
        {
            break;
        }
    }while (0);

    /* destory allocated data when some error on creating process*/
    if(i4_ret != MENUR_OK)
    {
        if(pt_pwd_form != NULL)
        {
             c_mem_free(pt_pwd_form);
        }
    }

    return i4_ret;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    INT32 i4_ret;
    PWD_FORM_T* pt_pwd_form = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_pwd_form);

    if(i4_ret == MENUR_OK)
    {
        if(pt_pwd_form != NULL)
        {
            c_mem_free(pt_pwd_form);
        }
    }

    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32 i4_ret;
    PWD_FORM_T* pt_pwd_form = NULL;
    UINT16      ui2_msgid_txt;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_pwd_form);
    MENU_LOG_ON_FAIL(i4_ret);

    if (ui4_page_id == ui4_g_menu_page_pwd)
    {
        ui2_msgid_txt = MLM_MENU_KEY_CLR_MEM_TITLE;
    }
    else if (ui4_page_id == ui4_g_menu_page_setup_wizard_pwd)
    {
        ui2_msgid_txt = MLM_MENU_KEY_START_WZD;
    }
    else if (ui4_page_id == ui4_g_menu_page_ch_scan2_pwd)
    {
        ui2_msgid_txt = MLM_MENU_KEY_SCAN_CHANNELS;
    }
    else
    {
        ui2_msgid_txt = MLM_MENU_KEY_EMPTY;
    }

    menu_main_set_title(ui2_msgid_txt);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_PARENT_PIN));

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32 i4_ret;
    PWD_FORM_T* pt_pwd_form = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_pwd_form);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_focus(pt_pwd_form->h_eb_pwd, WGL_NO_AUTO_REPAINT);

    menu_common_help_show_back();

    menu_set_backbar_proc (_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    INT32 i4_ret;
    PWD_FORM_T* pt_pwd_form = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_pwd_form);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_do_cmd(pt_pwd_form->h_eb_pwd,
                 WGL_CMD_EB_SET_TEXT,
                 NULL,
                 NULL);

    MENU_LOG_ON_FAIL (menu_set_backbar_proc (NULL)) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    INT32 i4_ret;
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        i4_ret = _chg_lang(ui4_page_id);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

extern INT32 menu_common_page_pwd_init(VOID)
{
    t_g_menu_common_page_pwd.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_pwd.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_pwd.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_pwd.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_pwd.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_pwd.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_pwd.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

#endif /* COMMON_PWD_ENABLE */
