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
 * $RCSfile: menu_page_inp_edit.c,v $
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

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svctx.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_rating.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"

#include "res/app_util/config/a_cfg_custom.h"

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/* Customizable part */
#define INP_EDIT_STL_SCROLL     0
#define INP_EDIT_STL_WRAP_OVER  1
#define INP_EDIT_BACK_ON_LEFT   0
#define INP_EDIT_X              (0 * GRID_W)
#define INP_EDIT_Y              (0 * GRID_H)
#define INP_EDIT_W              (16 * GRID_W)
#define INP_EDIT_H              (10 * GRID_H)
#define INP_EDIT_COL0_W         1
#define INP_EDIT_COL1_W         200
#define INP_EDIT_COL2_W         CONTENT_W - INP_EDIT_COL0_W - INP_EDIT_COL1_W - \
                                10 - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R

/* layout */
/*
  +----------------------------------------------------+
  |   Icon  |    Disp Name          | User Name        |
  +----------------------------------------------------+
   COL0     COL1                            COL2
*/


#define INP_EDIT_ELEM_N         16
#define INP_EDIT_ELEM_H         GRID_H
#define INP_EDIT_COL0_ALIGN     WGL_AS_CENTER_CENTER
#define INP_EDIT_COL1_ALIGN     WGL_AS_LEFT_CENTER
#define INP_EDIT_COL2_ALIGN     WGL_AS_LEFT_CENTER

#define MAX_INP_NAME_LEN        APP_CFG_CUSTOM_INP_NAME_LEN

typedef enum _HELP_LST_STATE{
    HELP_LST_NORMAL,
    HELP_LST_EDITING
} HELP_LST_STATE;

typedef struct _INPUT_EDIT_INIT_T{
    UINT16              ui2_msg_title;
    UINT32              ui4_sel_mask;
    UINT16              ui2_max_rec_num;
    BOOL                b_scroll;       /* TRUE, then turns off the listbox
                                           WGL_STL_LB_NO_SCROLL style */
    BOOL                b_wrap_over;    /* TRUE, then turns off the listbox
                                           WGL_STL_LB_NO_WRAP_OVER */
    BOOL                b_back_on_left; /* Back to previous page by
                                           BTN_CURSOR_LEFT */
}   INPUT_EDIT_INIT_T;

typedef struct _INPUT_EDIT_T
{
    UINT32                  ui4_page_id;
    INPUT_EDIT_INIT_T       t_inp_edit_init;
    HANDLE_T                h_lb_inp;
    BOOL                    b_editing;
    BOOL                    b_is_refreshing;

    /* For eb_user_name */
    HANDLE_T                h_eb_user_name;
    CHAR                    ac_name[MAX_INP_NAME_LEN];
    UINT8                   ui1_cursor;
}   INPUT_EDIT_T;


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T     t_g_menu_page_inp_edit;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _lb_input_proc_fct(
    HANDLE_T   h_widget,
    UINT32     ui4_msg,
    VOID*      pv_param1,
    VOID*      pv_param2
);

static INT32 _eb_user_name_proc_fct(
    HANDLE_T   h_widget,
    UINT32     ui4_msg,
    VOID*      pv_param1,
    VOID*      pv_param2
);

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _inp_edit_set_attach_data
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
static INT32 _inp_edit_set_attach_data(HANDLE_T         h_lb_inp,
                                      INPUT_EDIT_T*     pt_inp_edit)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_inp_edit),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _inp_edit_get_attach_data
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
static INT32 _inp_edit_get_attach_data(HANDLE_T         h_lb_inp,
                                      INPUT_EDIT_T**    ppt_inp_edit)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_inp_edit),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _help_lst_update
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
static INT32 _help_lst_update(HELP_LST_STATE e_help_lst_state,
                              BOOL           b_repaint)
{
/* use help tip instead of menu's help list */
#if 0
    if(e_help_lst_state == HELP_LST_NORMAL)
    {
        MENU_HELP_LST_BUCKET_T at_help_lst[] =
        {
            {h_g_menu_img_btn_ok,    MLM_MENU_KEY_HELP_EDIT},
            {h_g_menu_img_btn_select,   MLM_MENU_KEY_HELP_SELECT},
            {h_g_menu_img_btn_enter,     MLM_MENU_KEY_HELP_BACK}
        };

        menu_main_set_help(at_help_lst,
                           sizeof(at_help_lst)/ sizeof(at_help_lst[0]));
    }
    else
    {
        MENU_HELP_LST_BUCKET_T at_help_lst[] =
        {
            {h_g_menu_img_btn_ok,    MLM_MENU_KEY_OK},
            {h_g_menu_img_btn_select,   MLM_MENU_KEY_HELP_SELECT},
            {h_g_menu_img_btn_enter,     MLM_MENU_KEY_HELP_CNCL}
        };

        menu_main_set_help(at_help_lst,
                           sizeof(at_help_lst)/ sizeof(at_help_lst[0]));
    }
#endif
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _eb_user_name_create
 *
 * Description:  Create widgets.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _eb_user_name_create (
    HANDLE_T          h_parent,
    INPUT_EDIT_T*     pt_input_edit,
    HANDLE_T*         ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    UINT32          ui4_style = WGL_STL_GL_NO_IMG_UI |
                                WGL_STL_EB_MAX_CHAR_16;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    /* Set the editbox location and size */
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_BAR_CNT_INSET_L + INP_EDIT_COL0_W + INP_EDIT_COL1_W + 10,
                     0,
                     INP_EDIT_COL2_W,
                     GRID_H);

    /* Create Editbox */
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _eb_user_name_proc_fct,/* window procedure */
                                 255,                /* alpha */
                                 (void*)ui4_style,
                                 NULL,               /* tag */
                                 ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.i2_width     = 18;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_menu_color_bk1_txt;
    c_wgl_do_cmd(*ph_widget,
                 WGL_CMD_GL_SET_COLOR,
                 WGL_PACK(WGL_CLR_TEXT),
                 WGL_PACK(&t_clr_info));

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable      = t_g_menu_color_bk0_ex_txt;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_g_menu_color_bk0_ex_txt;
    t_clr_info.u_color_data.t_standard.t_disable     = t_g_menu_color_bk0_ex_txt;
    c_wgl_do_cmd(*ph_widget,
                 WGL_CMD_GL_SET_COLOR,
                 WGL_PACK(WGL_CLR_BK),
                 WGL_PACK(&t_clr_info));

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable      = t_g_menu_color_bk1_txt_hlt;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_g_menu_color_bk1_txt_hlt;
    t_clr_info.u_color_data.t_standard.t_disable     = t_g_menu_color_bk1_txt_hlt;
    c_wgl_do_cmd(*ph_widget,
                 WGL_CMD_GL_SET_COLOR,
                 WGL_PACK(WGL_CLR_EB_CURSOR),
                 WGL_PACK(&t_clr_info));

    /* Input Limit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK(MAX_INP_NAME_LEN + 2),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Attr */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Cursor Highlight */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_ENABLE_CURSOR_HT,
                          WGL_PACK(TRUE),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    pt_input_edit->ui1_cursor = 0;
    c_memset(pt_input_edit->ac_name, (UINT8)' ', MAX_INP_NAME_LEN);

    /* attach data */
    i4_ret = _inp_edit_set_attach_data(*ph_widget, pt_input_edit);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _eb_user_name_update_text (
    INPUT_EDIT_T*       pt_inp_edit)
{
    UINT8       ui1_i;
    UINT8       ui1_ptr = 0;
    UTF16_T     w2s_str[MAX_INP_NAME_LEN + 3];  /* [ , ], \0 */

    w2s_str[ui1_ptr++] = (UTF16_T)'[';

    for(ui1_i=0; ui1_i<MAX_INP_NAME_LEN; ui1_i++)
    {
        if(pt_inp_edit->ac_name[ui1_i] == ' ')
        {
            w2s_str[ui1_ptr++] = (UTF16_T)'_';
        }
        else
        {
            w2s_str[ui1_ptr++] = (UTF16_T)pt_inp_edit->ac_name[ui1_i];
        }
    }

    w2s_str[ui1_ptr++] = (UTF16_T)']';
    w2s_str[ui1_ptr++] = 0;

    /* Append with the whole string */
    c_wgl_do_cmd(pt_inp_edit->h_eb_user_name,
                 WGL_CMD_EB_SET_TEXT,
                 WGL_PACK(w2s_str),
                 WGL_PACK(0xFFFF));

    /* Update the position */
    c_wgl_do_cmd(pt_inp_edit->h_eb_user_name,
                 WGL_CMD_EB_SET_CURSOR_POS,
                 WGL_PACK(pt_inp_edit->ui1_cursor + 1),
                 WGL_PACK(NULL));

    return MENUR_OK;
}

static INT32 _eb_user_name_edit_start(
    INPUT_EDIT_T*       pt_inp_edit)
{
    UINT16      ui2_idx;
    GL_RECT_T   t_rect;

    c_wgl_do_cmd(pt_inp_edit->h_lb_inp,
                 WGL_CMD_LB_GET_HLT_INDEX,
                 WGL_PACK(&ui2_idx),
                 WGL_PACK(NULL));

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_BAR_CNT_INSET_L + INP_EDIT_COL0_W + INP_EDIT_COL1_W + 10,
                     GRID_H * ui2_idx,
                     INP_EDIT_COL2_W,
                     GRID_H);

    a_cfg_custom_get_inp_name(ui2_idx+1,
                              pt_inp_edit->ac_name);

    c_wgl_move(pt_inp_edit->h_eb_user_name, &t_rect, WGL_NO_AUTO_REPAINT);

    c_wgl_set_visibility(pt_inp_edit->h_eb_user_name, WGL_SW_NORMAL);

    c_wgl_set_focus(pt_inp_edit->h_eb_user_name, WGL_NO_AUTO_REPAINT);

    pt_inp_edit->ui1_cursor = 0;

    _eb_user_name_update_text(pt_inp_edit);

    _help_lst_update(HELP_LST_EDITING, FALSE);

    menu_pm_repaint();

    pt_inp_edit->b_editing = TRUE;

    return MENUR_OK;
}

static INT32 _eb_user_name_edit_done(
    INPUT_EDIT_T*       pt_inp_edit)
{
    UINT16      ui2_idx;
    UTF16_T     w2s_str[MAX_INP_NAME_LEN+1];

    c_wgl_do_cmd(pt_inp_edit->h_lb_inp,
                 WGL_CMD_LB_GET_HLT_INDEX,
                 WGL_PACK(&ui2_idx),
                 WGL_PACK(NULL));

    c_wgl_set_focus(pt_inp_edit->h_lb_inp, WGL_NO_AUTO_REPAINT);
    c_wgl_set_visibility(pt_inp_edit->h_eb_user_name, WGL_SW_HIDE);

    /* Set the result to config */
    a_cfg_custom_set_inp_name(ui2_idx+1,
                              pt_inp_edit->ac_name);

    /* Set the result to listbox */
    c_uc_ps_to_w2s(pt_inp_edit->ac_name, w2s_str, MAX_INP_NAME_LEN);
    w2s_str[MAX_INP_NAME_LEN] = 0;
    c_wgl_do_cmd(pt_inp_edit->h_lb_inp,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(ui2_idx, 2),
                 WGL_PACK(w2s_str));

    _help_lst_update(HELP_LST_NORMAL, FALSE);

    /* Repaint */
    menu_pm_repaint();

    pt_inp_edit->b_editing = FALSE;

    return MENUR_OK;
}

static INT32 _eb_user_name_edit_cancel(
    INPUT_EDIT_T*       pt_inp_edit)
{
    c_wgl_set_focus(pt_inp_edit->h_lb_inp, WGL_NO_AUTO_REPAINT);
    c_wgl_set_visibility(pt_inp_edit->h_eb_user_name, WGL_SW_HIDE);

    _help_lst_update(HELP_LST_NORMAL, FALSE);

    menu_pm_repaint();

    pt_inp_edit->b_editing = FALSE;

    return MENUR_OK;
}

static INT32 _eb_user_name_proc_fct(
    HANDLE_T   h_widget,
    UINT32     ui4_msg,
    VOID*      pv_param1,
    VOID*      pv_param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        INPUT_EDIT_T* pt_inp_lst;
        UINT32 ui4_keycode = (UINT32)pv_param1;

        /* get the channel list data */
        _inp_edit_get_attach_data(h_widget, &pt_inp_lst);

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
            /* Cursor */
            if(ui4_keycode ==  BTN_CURSOR_RIGHT &&
               pt_inp_lst->ui1_cursor != MAX_INP_NAME_LEN - 1)
            {
                pt_inp_lst->ui1_cursor++;
            }
            else if(ui4_keycode == BTN_CURSOR_LEFT &&
                    pt_inp_lst->ui1_cursor != 0)
            {
                pt_inp_lst->ui1_cursor--;
            }
            _eb_user_name_update_text(pt_inp_lst);
            c_wgl_repaint(pt_inp_lst->h_eb_user_name, NULL, TRUE);
            return WMPR_DONE;
        case BTN_CURSOR_UP:
        {
            CHAR    c_char;

            if (pt_inp_lst->ui1_cursor >= MAX_INP_NAME_LEN)
            {
                break;
            }

            c_char = pt_inp_lst->ac_name[pt_inp_lst->ui1_cursor];
            if(c_char == ' ')
            {
                c_char = 'A';
            }
            else if(c_char >= 'A' && c_char <= 'Y')
            {
                c_char++;
            }
            else if(c_char == 'Z')
            {
                c_char = '0';
            }
            else if(c_char >= '0' && c_char <= '8')
            {
                c_char++;
            }
            else if(c_char == '9')
            {
                c_char = ' ';
            }
            else
            {
                c_char = ' ';
            }
            pt_inp_lst->ac_name[pt_inp_lst->ui1_cursor] = c_char;
            _eb_user_name_update_text(pt_inp_lst);
            c_wgl_repaint(pt_inp_lst->h_eb_user_name, NULL, TRUE);
            return WMPR_DONE;
        }
        case BTN_CURSOR_DOWN:
        {
            CHAR    c_char;

            if (pt_inp_lst->ui1_cursor >= MAX_INP_NAME_LEN)
            {
                break;
            }

            c_char = pt_inp_lst->ac_name[pt_inp_lst->ui1_cursor];
            if(c_char == ' ')
            {
                c_char = '9';
            }
            else if(c_char >= '1' && c_char <= '9')
            {
                c_char--;
            }
            else if(c_char == '0')
            {
                c_char = 'Z';
            }
            else if(c_char >= 'B' && c_char <= 'Z')
            {
                c_char--;
            }
            else if(c_char == 'A')
            {
                c_char = ' ';
            }
            else
            {
                c_char = ' ';
            }
            pt_inp_lst->ac_name[pt_inp_lst->ui1_cursor] = c_char;
            _eb_user_name_update_text(pt_inp_lst);
            c_wgl_repaint(pt_inp_lst->h_eb_user_name, NULL, TRUE);
            return WMPR_DONE;
        }
        case BTN_SELECT:
            /* OK */
            _eb_user_name_edit_done(pt_inp_lst);
            break;
        case BTN_EXIT:
            /* Cancel */
            _eb_user_name_edit_cancel(pt_inp_lst);
            break;
        default:
            break;
        }

        return WMPR_DONE;
    }
    case WGL_MSG_KEY_UP:
    {
        return WMPR_DONE;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _lb_input_proc_fct(
    HANDLE_T            h_widget,
    UINT32              ui4_msg,
    VOID*               pv_param1,
    VOID*               pv_param2)
{
    INT32 i4_ret;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        INPUT_EDIT_T* pt_inp_lst;
        UINT32 ui4_keycode = (UINT32)pv_param1;

        /* get the channel list data */
        i4_ret = _inp_edit_get_attach_data(h_widget, &pt_inp_lst);
        if(i4_ret != MENUR_OK)
        {
            return WGLR_OK;
        }

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
            if(pt_inp_lst->t_inp_edit_init.b_back_on_left)
            {
                menu_nav_back();
                return WGLR_OK;
            }
            else
            {
                /* simulate the page up */
                pv_param1 = WGL_PACK(BTN_RED);
            }
            break;
        case BTN_CURSOR_RIGHT:
            if(pt_inp_lst->t_inp_edit_init.b_back_on_left)
            {
                /* do nothing */
                return WGLR_OK;
            }
            else
            {
                /* simulate the page up */
                pv_param1 = WGL_PACK(BTN_GREEN);
            }
            break;
        case BTN_SELECT:
            _eb_user_name_edit_start(pt_inp_lst);
            break;
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;
        default:
            break;
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _ch_lst2_add_ch
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
static INT32 _lb_input_add_inp(HANDLE_T           h_lb_inp,
                              INPUT_EDIT_T*       pt_inp_lst,
                              ISL_REC_T*          pt_isl_rec)
{
    INT32       i4_ret;
    HANDLE_T    h_img;
    UTF16_T     w2s_disp_name[MAX_INP_NAME_LEN+1];
    UTF16_T     w2s_user_name[MAX_INP_NAME_LEN+1];
    CHAR        ac_user_name[MAX_INP_NAME_LEN];
    WGL_LB_ITEM_T at_items[3];


    /* Get the input icon */
    h_img = NULL_HANDLE;

    /* Get the display name */
    c_memset(w2s_disp_name, 0, sizeof(w2s_disp_name));
    c_uc_w2s_strncpy(w2s_disp_name, a_isl_get_display_name(pt_isl_rec), MAX_INP_NAME_LEN);

    /* Get the user name */
    c_memset(w2s_user_name, 0, sizeof(w2s_user_name));
    a_cfg_custom_get_inp_name(pt_isl_rec->ui1_id, ac_user_name);
    c_uc_ps_to_w2s(ac_user_name, w2s_user_name, MAX_INP_NAME_LEN);

    /* Append the data */
    at_items[0].e_col_type      = LB_COL_TYPE_IMG;
    at_items[0].data.h_img      = h_img;
    at_items[1].e_col_type      = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text  = w2s_disp_name;
    at_items[2].e_col_type      = LB_COL_TYPE_TEXT;
    at_items[2].data.pw2s_text  = w2s_user_name;

     /* append item */
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(at_items),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_create_channel_list
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
static INT32 _lb_input_create(
    HANDLE_T          h_parent,
    INT32             i4_x,
    INT32             i4_y,
    INT32             i4_w,
    INT32             i4_h,
    INPUT_EDIT_T*     pt_inp_lst,
    HANDLE_T*         ph_lb_inp)
{
    INT32               i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[3];
    GL_RECT_T           t_rect;
    WGL_LB_KEY_MAP_T    t_lb_key_map;
    WGL_FONT_INFO_T     t_fnt_info;

    /* Icon */
    at_cols[0].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[0].ui1_align        = INP_EDIT_COL0_ALIGN;
    at_cols[0].ui2_width        = INP_EDIT_COL0_W;

    /* Display Name */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = INP_EDIT_COL1_ALIGN;
    at_cols[1].ui2_max_text_len = MAX_INP_NAME_LEN + 1;
    at_cols[1].ui2_width        = INP_EDIT_COL1_W;

    /* User Name */
    at_cols[2].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[2].ui1_align        = INP_EDIT_COL2_ALIGN;
    at_cols[2].ui2_max_text_len = MAX_INP_NAME_LEN + 1;
    at_cols[2].ui2_width        = INP_EDIT_COL2_W;


    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_MULTI_SEL;

    if(!pt_inp_lst->t_inp_edit_init.b_scroll)
    {
        t_lb_init.ui4_style    |= WGL_STL_LB_NO_SCROLL;
    }

    if(!pt_inp_lst->t_inp_edit_init.b_wrap_over)
    {
        t_lb_init.ui4_style    |= WGL_STL_LB_NO_WRAP_OVER;
    }

    t_lb_init.ui2_max_elem_num  = pt_inp_lst->t_inp_edit_init.ui2_max_rec_num;
    t_lb_init.ui2_elem_size     = INP_EDIT_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 3;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      i4_x,
                      i4_y,
                      i4_w,
                      i4_h);

    i4_ret = menu_list2_create (h_parent,
                                &t_rect,
                                _lb_input_proc_fct,
                                & t_lb_init,
                                NULL,
                                ph_lb_inp);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for input source list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next       = BTN_CURSOR_DOWN;
    t_lb_key_map.ui4_key_prev       = BTN_CURSOR_UP;
    t_lb_key_map.ui4_key_select     = BTN_SELECT;
    t_lb_key_map.ui4_key_page_up    = BTN_RED;
    t_lb_key_map.ui4_key_page_down  = BTN_GREEN;
    i4_ret = c_wgl_do_cmd(*ph_lb_inp, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.i2_width     = 30;

    i4_ret = c_wgl_do_cmd (*ph_lb_inp,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK((UINT16)2),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* attach data */
    i4_ret = _inp_edit_set_attach_data(*ph_lb_inp, pt_inp_lst);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _lb_input_refresh
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
static INT32   _lb_input_refresh(HANDLE_T   h_lb_inp)
{
    INT32         i4_ret      = MENUR_OK;
    INT32         i4_result;
    INPUT_EDIT_T* pt_inp_lst;
    UINT8         ui1_rec_num;
    UINT8         ui1_idx;
    ISL_REC_T     t_isl_rec;

    /* get the channel list data */
    _inp_edit_get_attach_data(h_lb_inp, &pt_inp_lst);
    if (pt_inp_lst == NULL)
    {
        return MENUR_FAIL;
    }

    /* Set the refreshing flag */
    pt_inp_lst->b_is_refreshing = TRUE;

    /* clear the list */
    i4_result = c_wgl_do_cmd(h_lb_inp,
                             WGL_CMD_LB_DEL_ALL,
                             NULL, NULL);
    MENU_LOG_ON_FAIL(i4_result);

    /* get record number */
    a_isl_get_num_rec(&ui1_rec_num);

    /* check if the record number exceeds the max channel number */
    if(ui1_rec_num > pt_inp_lst->t_inp_edit_init.ui2_max_rec_num)
    {
        DBG_ERROR(("<MENU> Record number exceeds max sec number: %d < %d.\r\n",
                  ui1_rec_num, pt_inp_lst->t_inp_edit_init.ui2_max_rec_num));

       ui1_rec_num = pt_inp_lst->t_inp_edit_init.ui2_max_rec_num;
    }

    /* iterate */
    for(ui1_idx = 0 ; ui1_idx < ui1_rec_num ; ui1_idx++)
    {
        a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);

        /* ignore TV inp src */
        if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
        {
            continue;
        }

        i4_result = _lb_input_add_inp(h_lb_inp,
                                     pt_inp_lst,
                                     &t_isl_rec);
        if (i4_result < 0)
        {
            i4_ret = i4_result;
            DBG_ERROR(("<MENU> Can't add input source to input source list.\r\n"));
            break;
        }
    }

    /* Set the refreshing flag */
    pt_inp_lst->b_is_refreshing = FALSE;

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _lb_input_hlt_curent_src
 *
 * Description:
 *  Highlight current playing channel
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _lb_input_hlt_curent_src(HANDLE_T h_lb_inp)
{
    INT32           i4_ret;
    INPUT_EDIT_T*   pt_inp_lst;
    ISL_REC_T       t_isl_rec;
    ISL_REC_T       t_isl_rec_crnt;
    UINT8           ui1_rec_num;
    UINT8           ui1_idx;

    /* get the channel list data */
    _inp_edit_get_attach_data(h_lb_inp, &pt_inp_lst);
    if (pt_inp_lst == NULL)
    {
        return MENUR_FAIL;
    }

    /* Get Input Source number */
    i4_ret = a_isl_get_num_rec(&ui1_rec_num);
    MENU_LOG_ON_FAIL(i4_ret);

    /* get the current svl record */
    i4_ret = menu_get_crnt_isl(&t_isl_rec_crnt);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Iterate the ISL */
    for(ui1_idx = 0 ; ui1_idx < ui1_rec_num ; ui1_idx++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);
        MENU_LOG_ON_FAIL(i4_ret);

        if(t_isl_rec.ui1_id == t_isl_rec_crnt.ui1_id)
        {
            break;
        }
    }
    if(ui1_idx == ui1_rec_num ||
       ui1_idx == 0)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = ui1_idx - 1;
    }

    /* Highlight Element */
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui1_idx),                            /* hlt elem */
                          WGL_PACK(ui1_idx % (CONTENT_H / GRID_H)));    /* hlt pos */
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32                i4_ret       = MENUR_FAIL;
    INPUT_EDIT_T*        pt_inp_lst   = NULL;
    INPUT_EDIT_INIT_T*   pt_inp_edit_init = (INPUT_EDIT_INIT_T*)pv_create_data;
    HANDLE_T             h_cnt_frm;

    if(pt_inp_edit_init == NULL)
    {
        return MENUR_INV_ARG;
    }

    /* Attach data */
    do
    {
        i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        pt_inp_lst = c_mem_alloc(sizeof(INPUT_EDIT_T));

        if(pt_inp_lst == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        c_memset(pt_inp_lst, 0, sizeof(INPUT_EDIT_T));

        c_memcpy(&pt_inp_lst->t_inp_edit_init,
                 pt_inp_edit_init,
                 sizeof(INPUT_EDIT_INIT_T));

        pt_inp_lst->ui4_page_id = ui4_page_id;

        i4_ret = menu_page_set_data(ui4_page_id, pt_inp_lst);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /* Create editbox */
        i4_ret = _eb_user_name_create(h_cnt_frm,
                                      pt_inp_lst,
                                      &pt_inp_lst->h_eb_user_name);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /* Create input list box */
        i4_ret = _lb_input_create(h_cnt_frm,
                    INP_EDIT_X,
                    INP_EDIT_Y,
                    INP_EDIT_W,
                    INP_EDIT_H,
                    pt_inp_lst,
                    &pt_inp_lst->h_lb_inp);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /* Set visibility */
        i4_ret = c_wgl_set_visibility(pt_inp_lst->h_lb_inp,
                                      WGL_SW_NORMAL);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = c_wgl_set_visibility(pt_inp_lst->h_eb_user_name,
                                      WGL_SW_HIDE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                      WGL_SW_HIDE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }
    } while(0);

    if(i4_ret != MENUR_OK)
    {
        if(pt_inp_lst != NULL)
        {
            if(pt_inp_lst->h_lb_inp != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_inp_lst->h_lb_inp);
            }
            c_mem_free(pt_inp_lst);
        }
    }

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{

    /* Pending */

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32 i4_ret;
    INPUT_EDIT_T* pt_inp_lst = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_inp_lst);
    MENU_LOG_ON_FAIL(i4_ret);

    _lb_input_refresh(pt_inp_lst->h_lb_inp);

    _lb_input_hlt_curent_src(pt_inp_lst->h_lb_inp);

    menu_main_set_title(pt_inp_lst->t_inp_edit_init.ui2_msg_title);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32 i4_ret;
    INPUT_EDIT_T* pt_inp_edit = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_inp_edit);
    MENU_LOG_ON_FAIL(i4_ret);

    if(pt_inp_edit->b_editing)
    {
        _eb_user_name_edit_cancel(pt_inp_edit);
    }

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32 i4_ret;
    INPUT_EDIT_T* pt_inp_lst = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_inp_lst);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_focus(pt_inp_lst->h_lb_inp, WGL_NO_AUTO_REPAINT);

    /* Initially, only Page Down button is shown */
    _help_lst_update(HELP_LST_NORMAL, FALSE);

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
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        /* do_nothing */
    }
    return MENUR_OK;
}

extern INT32 menu_custom_create_page_inp_edit(UINT32 *pui4_page_id)
{
    INPUT_EDIT_INIT_T    t_inp_edit_init;

    c_memset(&t_inp_edit_init, 0, sizeof(INPUT_EDIT_INIT_T));

    t_inp_edit_init.ui2_msg_title            = MLM_MENU_KEY_INPUT_EDIT;
    t_inp_edit_init.ui2_max_rec_num          = INP_EDIT_ELEM_N;
    t_inp_edit_init.ui4_sel_mask             = ISL_ATTR_BIT_BLOCKED;
    t_inp_edit_init.b_scroll                 = INP_EDIT_STL_SCROLL;
    t_inp_edit_init.b_wrap_over              = INP_EDIT_STL_WRAP_OVER;
    t_inp_edit_init.b_back_on_left           = INP_EDIT_BACK_ON_LEFT;

    return menu_pm_page_create(&t_g_menu_page_inp_edit,
                               (VOID*)&t_inp_edit_init,
                               pui4_page_id);

}

extern INT32 menu_page_inp_edit_init(VOID)
{
    t_g_menu_page_inp_edit.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_inp_edit.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_inp_edit.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_inp_edit.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_inp_edit.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_inp_edit.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_inp_edit.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
