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
 * $RCSfile: menu_page_mjc_demo.c,v $
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
#include "c_wgl_image.h"

#include "app_util/a_cfg.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "res/menu2/menu_img.h"
#include "res/menu2/menu_clr.h"
#include "menu2/menu_dbg.h"


#ifdef COMMON_MJC_DEMO_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

typedef struct
{
    HANDLE_T            h_parent;
    INT32               i4_x;
    INT32               i4_y;
    INT32               i4_w;
    INT32               i4_h;
    UINT32              ui4_style;
    FE_FNT_SIZE         e_font_size;
    UINT8               ui1_align;

    WGL_HIMG_TPL_T      h_img_bk;

    GL_COLOR_T*         pt_clr_txt;

    wgl_widget_proc_fct pf_wdgt_proc;
    HANDLE_T*           ph_created_txt;

}  MJC_TXT_WIDGET_PARAM_T;


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T t_g_menu_common_page_mjc_demo;
static HANDLE_T     h_frm_mjc;
static HANDLE_T     h_line;
static HANDLE_T     h_txt_left;
static HANDLE_T     h_txt_right;
static HANDLE_T     h_txt_center;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _on_page_hide(UINT32 ui4_page_id);

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _mjc_demo_wdgt_proc_fct
 *
 * Description:   Main widget process function of the mjc demo UI.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static INT32 _mjc_demo_wdgt_proc_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;

            if (BTN_INVALID != ui4_keycode)
            {
                menu_nav_back();
            }
            break;
        }
        default:
            break;
    }

   return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}


/*----------------------------------------------------------------------------
 * Name: _create_frame
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _create_frame(
                    HANDLE_T            h_parent,
                    HANDLE_T*           ph_frm
                    )
{
    GL_RECT_T           t_rect;
    INT32               i4_ret;

    /* create channel frame */
    SET_RECT_BY_SIZE(&t_rect,
                     MJC_DEMO_CHASSIS_X,
                     MJC_DEMO_CHASSIS_Y,
                     MJC_DEMO_CHASSIS_W,
                     MJC_DEMO_CHASSIS_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _mjc_demo_wdgt_proc_fct,
                                 255,
                                 (VOID *)(WGL_STL_GL_NO_IMG_UI | WGL_STL_GL_NO_BK),
                                 NULL,
                                 ph_frm);
    MENU_CHK_FAIL (i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _create_frame
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _create_split_line(
                    HANDLE_T            h_parent,
                    HANDLE_T*           ph_frm
                    )
{
    GL_RECT_T           t_rect;
    INT32               i4_ret;
    WGL_IMG_INFO_T      t_img_info;

    /* create channel frame */
    SET_RECT_BY_SIZE(&t_rect,
                     MJC_DEMO_LINE_X,
                     MJC_DEMO_LINE_Y,
                     MJC_DEMO_LINE_W,
                     MJC_DEMO_LINE_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID *)0,
                                 NULL,
                                 ph_frm);
    MENU_CHK_FAIL (i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_mjc_line_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_mjc_line_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_mjc_line_bk;
    i4_ret = c_wgl_do_cmd(*ph_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _create_frame
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _create_txt(
                    MJC_TXT_WIDGET_PARAM_T  t_txt_param
                    )
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;
    WGL_COLOR_INFO_T            t_color_info;

    SET_RECT_BY_SIZE (& t_rect,
                      t_txt_param.i4_x,
                      t_txt_param.i4_y,
                      t_txt_param.i4_w,
                      t_txt_param.i4_h);

    /* create widget */
    MENU_CHK_FAIL (c_wgl_create_widget (t_txt_param.h_parent,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     t_txt_param.pf_wdgt_proc,
                                     255,
                                     (VOID*)(t_txt_param.ui4_style),
                                     NULL,
                                     t_txt_param.ph_created_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));

    c_strcpy (t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = t_txt_param.e_font_size;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    MENU_CHK_FAIL (c_wgl_do_cmd (*t_txt_param.ph_created_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    c_memset (& t_inset, 0, sizeof (WGL_INSET_T));

    MENU_CHK_FAIL (c_wgl_do_cmd (*t_txt_param.ph_created_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    MENU_CHK_FAIL (c_wgl_do_cmd (*t_txt_param.ph_created_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (t_txt_param.ui1_align),
                              NULL));

    /* set theme */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_txt_param.h_img_bk;
    t_img_info.u_img_data.t_standard.t_disable   = t_txt_param.h_img_bk;
    t_img_info.u_img_data.t_standard.t_highlight = t_txt_param.h_img_bk;

    MENU_CHK_FAIL (c_wgl_do_cmd (*t_txt_param.ph_created_txt,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    t_txt_param.pt_clr_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   t_txt_param.pt_clr_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, t_txt_param.pt_clr_txt);

    MENU_CHK_FAIL (c_wgl_do_cmd (*t_txt_param.ph_created_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    MENU_CHK_FAIL (c_wgl_set_visibility (*t_txt_param.ph_created_txt, WGL_SW_HIDE));

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _create_frame
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _create_txt_left(
                    HANDLE_T            h_parent,
                    HANDLE_T*           ph_widget
                    )
{
    MJC_TXT_WIDGET_PARAM_T     t_txt_param;

    c_memset (& t_txt_param, 0, sizeof (MJC_TXT_WIDGET_PARAM_T));

    t_txt_param.h_parent        = h_parent;
    t_txt_param.i4_x            = MJC_DEMO_L_TXT_X;
    t_txt_param.i4_y            = MJC_DEMO_LR_TXT_Y;
    t_txt_param.i4_w            = MJC_DEMO_LR_TXT_W;
    t_txt_param.i4_h            = MJC_DEMO_LR_TXT_H;
    t_txt_param.ui4_style       = WGL_STL_TEXT_MAX_32;
    t_txt_param.e_font_size     = FE_FNT_SIZE_SMALL;
    t_txt_param.ui1_align       = WGL_AS_CENTER_CENTER;
    t_txt_param.h_img_bk        = h_g_menu_img_mjc_txt_bk;
    t_txt_param.pt_clr_txt      = &t_g_menu_color_mjc_txt;

    t_txt_param.pf_wdgt_proc    = NULL;
    t_txt_param.ph_created_txt  = ph_widget;

    return _create_txt(t_txt_param);
}


/*----------------------------------------------------------------------------
 * Name: _create_frame
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _create_txt_right(
                    HANDLE_T            h_parent,
                    HANDLE_T*           ph_widget
                    )
{
    MJC_TXT_WIDGET_PARAM_T     t_txt_param;

    c_memset (& t_txt_param, 0, sizeof (MJC_TXT_WIDGET_PARAM_T));

    t_txt_param.h_parent        = h_parent;
    t_txt_param.i4_x            = MJC_DEMO_R_TXT_X;
    t_txt_param.i4_y            = MJC_DEMO_LR_TXT_Y;
    t_txt_param.i4_w            = MJC_DEMO_LR_TXT_W;
    t_txt_param.i4_h            = MJC_DEMO_LR_TXT_H;
    t_txt_param.ui4_style       = WGL_STL_TEXT_MAX_32;
    t_txt_param.e_font_size     = FE_FNT_SIZE_SMALL;
    t_txt_param.ui1_align       = WGL_AS_CENTER_CENTER;
    t_txt_param.h_img_bk        = h_g_menu_img_mjc_txt_bk;
    t_txt_param.pt_clr_txt      = &t_g_menu_color_mjc_txt;

    t_txt_param.pf_wdgt_proc    = NULL;
    t_txt_param.ph_created_txt  = ph_widget;

    return _create_txt(t_txt_param);
}


/*----------------------------------------------------------------------------
 * Name: _create_frame
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _create_txt_center(
                    HANDLE_T            h_parent,
                    HANDLE_T*           ph_widget
                    )
{
    MJC_TXT_WIDGET_PARAM_T     t_txt_param;

    c_memset (& t_txt_param, 0, sizeof (MJC_TXT_WIDGET_PARAM_T));

    t_txt_param.h_parent        = h_parent;
    t_txt_param.i4_x            = MJC_DEMO_C_TXT_X;
    t_txt_param.i4_y            = MJC_DEMO_C_TXT_Y;
    t_txt_param.i4_w            = MJC_DEMO_C_TXT_W;
    t_txt_param.i4_h            = MJC_DEMO_C_TXT_H;
    t_txt_param.ui4_style       = WGL_STL_TEXT_MAX_32;
/*  t_txt_param.ui4_style       = WGL_STL_GL_NO_IMG_UI | WGL_STL_TEXT_MAX_512 |
                                  WGL_STL_TEXT_MULTILINE | WGL_STL_TEXT_MAX_DIS_10_LINE;
*/
    t_txt_param.e_font_size     = FE_FNT_SIZE_MEDIUM;
    t_txt_param.ui1_align       = WGL_AS_CENTER_CENTER;
    t_txt_param.h_img_bk        = h_g_menu_img_mjc_txt_bk;
    t_txt_param.pt_clr_txt      = &t_g_menu_color_mjc_txt;

    t_txt_param.pf_wdgt_proc    = NULL;
    t_txt_param.ph_created_txt  = ph_widget;

    return _create_txt(t_txt_param);
}


/*----------------------------------------------------------------------------
 * Name: _create_frame
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _set_txt(
            HANDLE_T        h_txt,
            UTF16_T*        pw2s_text)
{
    return  c_wgl_do_cmd (h_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/


static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    HANDLE_T                           h_frm_root;

    /* Get root frame */
    MENU_CHK_FAIL(menu_pm_get_root_frm(&h_frm_root));

    /* Creae demo frame */
    MENU_CHK_FAIL(_create_frame(h_frm_root, &h_frm_mjc));

    /* Create center text */
    MENU_CHK_FAIL(_create_txt_center(h_frm_mjc, &h_txt_center));
    MENU_CHK_FAIL(_set_txt(h_txt_center, MENU_TEXT(MLM_MENU_KEY_VID_MJC_DEMO_PAGE)));

    /* create split line */
    MENU_CHK_FAIL(_create_split_line(h_frm_mjc, &h_line));

    /* create left text */
    MENU_CHK_FAIL(_create_txt_left(h_frm_mjc, &h_txt_left));
    MENU_CHK_FAIL(_set_txt(h_txt_left, MENU_TEXT(MLM_MENU_KEY_OFF)));

    /* create right text */
    MENU_CHK_FAIL(_create_txt_right(h_frm_mjc, &h_txt_right));
    MENU_CHK_FAIL(_set_txt(h_txt_right, MENU_TEXT(MLM_MENU_KEY_ON)));

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    c_wgl_destroy_widget(h_frm_mjc);
    h_frm_mjc = NULL_HANDLE;

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT16   i2_val;
    INT32   i4_ret;
    UINT32  ui4_demo_status;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT), &i2_val);

    /* MJC effect is off */
    if (0 == i2_val)
    {
        return MENUR_OK;
    }

    /* Show MJC demo info widget */
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_DEMO), &i2_val);

    /* Show all */
    i4_ret = c_wgl_set_visibility(h_frm_mjc, WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    switch (i2_val)
    {
        case 1:
        {
            /* Update LR text */
            MENU_CHK_FAIL(_set_txt(h_txt_left, MENU_TEXT(MLM_MENU_KEY_OFF)));
            MENU_CHK_FAIL(_set_txt(h_txt_right, MENU_TEXT(MLM_MENU_KEY_ON)));
            break;
        }
        case 2:
        {
            /* Update LR text */
            MENU_CHK_FAIL(_set_txt(h_txt_left, MENU_TEXT(MLM_MENU_KEY_ON)));
            MENU_CHK_FAIL(_set_txt(h_txt_right, MENU_TEXT(MLM_MENU_KEY_OFF)));
            break;
        }
        case 0:
        default:
        {
            /* Hide */
            i4_ret = c_wgl_set_visibility(h_line, WGL_SW_HIDE);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = c_wgl_set_visibility(h_txt_left, WGL_SW_HIDE);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = c_wgl_set_visibility(h_txt_right, WGL_SW_HIDE);
            MENU_CHK_FAIL(i4_ret);
            break;
        }
    }

    /* Hide the main menu */
    menu_main_set_visibility(FALSE);

    /* disable the menu timer */
    menu_timer_enable(FALSE);
    menu_timer_stop();

    /* set MJC mode status on */
    a_cfg_get_demo_status(&ui4_demo_status);
    a_cfg_set_demo_status(ui4_demo_status|APP_CFG_DEMO_MODE_MJC);

    /* enable demo effect */
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_DEMO));

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32       i4_ret;
    UINT32      ui4_demo_status;

    /* Hide mjc demo indicate frame */
    i4_ret = c_wgl_set_visibility(h_frm_mjc, WGL_SW_HIDE_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    /* Let the menu show */
    menu_main_set_visibility(TRUE);

    /* enable the menu timer */
    menu_timer_enable(TRUE);
    menu_timer_start();

    /* set MJC mode status on */
    a_cfg_get_demo_status(&ui4_demo_status);
    a_cfg_set_demo_status(ui4_demo_status&(~APP_CFG_DEMO_MODE_MJC));

    /* Disable demo effect to user setting */
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_DEMO));

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32       i4_ret;

    i4_ret = c_wgl_set_focus(h_frm_mjc, WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);

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


INT32 menu_common_page_mjc_demo_init(VOID)
{

    t_g_menu_common_page_mjc_demo.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_mjc_demo.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_mjc_demo.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_mjc_demo.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_mjc_demo.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_mjc_demo.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_mjc_demo.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
#endif /* COMMON_MJC_DEMO_ENABLE */

