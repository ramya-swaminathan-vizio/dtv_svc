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
 * $RCSfile: nav_fac_urc_dialog.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/06 $
 * $Author: heyi.wang $
 * $CCRevision$
 * $SWAuthor$
 * $MD5HEX$
 * Description:
 *---------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_pcl.h"
#include "u_pcl.h"//jeff 20090121 add

#include "nav/a_navigator.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"


//#include "res/nav/factory/fac_mlm.h"
#include "INX_factory/INX_fac_mlm.h"

#include "app_util/config/acfg_cust_factory_vizio.h"


#include "nav/burning_mode/burning_mode.h"

#include "app_util/config/_acfg.h"    //Soar 20080924

/* view */
#include "app_util/a_ui.h"
//#include "nav/banner/banner_common.h"//jeff 20090122 add
#include "wizard/a_wzd.h" //jeff 20090209 add

#include "INX_fac_urc.h"
#include "INX_factory/a_INX_factory.h"
#include "INX_factory/INX_d_factory.h"
#include "INX_factory/INX_fac_menu/INX_fac.h"

//#include "res/nav/factory/nav_fac_img.h"
#include "INX_factory/INX_fac_img.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

typedef enum
{
    NAV_FAC_DIALOG_ID_NULL = 0,
    NAV_FAC_DIALOG_ID_TEST_MODE_ON,
}   NAV_FAC_URC_DIALOG_ID_T;

typedef struct
{
    /* Widgets */
    HANDLE_T        h_canvas;
    HANDLE_T        h_dialog;
    HANDLE_T        h_hide_timer;
    UINT32             ui4_timer_delay;
    NAV_FAC_URC_DIALOG_ID_T e_dialog_id;
}NAV_FAC_URC_DIALOG_T;

typedef struct _NAV_FAC_URC_DIALOG_VIEW_T
{
    /* Widgets */
    HANDLE_T        h_frm_simple_dialog;   /* the main frame of the S-DLG */
    HANDLE_T        h_txt_txtinfo;         /* the text box */
    /* Properties */
    UTF16_T*     pw2s_txtinfo;         /* the pointer of UTF16 txtinfo */
    BOOL         b_answer;
    /* Template Images */
    WGL_HIMG_TPL_T  h_ui_simple_dialog_bk0;             /* Simple Dialog BK */
} NAV_FAC_URC_DIALOG_VIEW_T;

typedef struct  _NAV_FAC_URC_DIALOG_SHOW_INIT_T
{
    HANDLE_T                     h_parent;
    wgl_widget_proc_fct          pf_wdgt_proc;
    UINT16                       ui2_txt_align_type;
    GL_RECT_T*                   pt_rect;            /* For Information style only */
    GL_POINT_T*                  pt_begin_offset;    /* For Small/Medium/Big style only */
    BOOL                         b_default_answer;   /* For Small/Medium/Big style only */
    ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct; /* For Small/Medium/Big style only */
    ui_simple_dialog_no_cb_fct   pf_ui_simple_dialog_no_cb_fct;  /* For Small/Medium/Big style only */
}  NAV_FAC_URC_DIALOG_SHOW_INIT_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_FAC_URC_DIALOG_T t_g_nav_fac_urc_dialog   = {0};

/* Transparant */
GL_COLOR_T t_g_nav_fac_urc_color_transp            = { 0,   {   0 }, {   0 }, {   0 }};
/* txt fg */
GL_COLOR_T t_g_nav_fac_urc_dialog_color_fg1_txt     = { 255, {  255 }, { 255 }, { 255 }};
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_urc_dialog_prompt_msg_dialog(
    NAV_FAC_URC_DIALOG_ID_T     e_dialog_id,
    UTF16_T*            pw2s_msg,
    wgl_widget_proc_fct pf_wdgt_proc
    );

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
static INT32 _nav_fac_urc_dialog_image_init(NAV_FAC_URC_DIALOG_VIEW_T*    pt_nav_fac_dialog)
{
    INT32 i4_ret;


    i4_ret = INX_fac_img_create_T_img_tpl(&pt_nav_fac_dialog->h_ui_simple_dialog_bk0);
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
static INT32  _nav_fac_urc_dialog_create_frm(NAV_FAC_URC_DIALOG_VIEW_T*    pt_nav_fac_dialog_show,
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
                         NAV_FAC_DIALOG_URC_FRAME_X + t_begin_offset.i4_x,
                         NAV_FAC_DIALOG_URC_FRAME_Y + t_begin_offset.i4_y,
                         NAV_FAC_DIALOG_URC_FRAME_W,
                         NAV_FAC_DIALOG_URC_FRAME_H);
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
static INT32  _nav_fac_urc_dialog_create_txtinfo(NAV_FAC_URC_DIALOG_VIEW_T*      pt_nav_fac_dialog,
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
                         UI_SIMPLE_DIALOG_INFO_TEXT_INFO_W,
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
    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog->h_txt_txtinfo,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_nav_fac_urc_dialog_color_fg1_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_nav_fac_urc_dialog_color_fg1_txt;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_nav_fac_urc_dialog_color_fg1_txt;
    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_nav_fac_urc_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_nav_fac_urc_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_nav_fac_urc_color_transp;
    i4_ret = c_wgl_do_cmd(pt_nav_fac_dialog->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
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
    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32  _nav_fac_urc_dialog_set_attach_data(
    HANDLE_T       h_simple_dialog,
    NAV_FAC_URC_DIALOG_VIEW_T*  pt_nav_fac_dialog)
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
static INT32 _nav_fac_urc_dialog_get_attach_data(
    HANDLE_T         h_simple_dialog,
    NAV_FAC_URC_DIALOG_VIEW_T**    ppt_ui_simple_dialog)
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
static INT32 _nav_fac_urc_dialog_set_text(HANDLE_T            h_simple_dialog,
                                  UTF16_T*            w2s_text)
{
      INT32   i4_ret;
      NAV_FAC_URC_DIALOG_VIEW_T*  pt_nav_fac_dialog_show;

      /* Get simple dialog structure */

      i4_ret = _nav_fac_urc_dialog_get_attach_data(h_simple_dialog,
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
/*----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32  _nav_fac_urc_dialog_create(NAV_FAC_URC_DIALOG_SHOW_INIT_T*    pt_nav_fac_dialog_init,   /* In  */
                                HANDLE_T*                nav_fac_dialog)              /* Out */
{
    INT32 i4_ret;
    //INT32 i4_result;
    NAV_FAC_URC_DIALOG_VIEW_T* pt_nav_fac_dialog_show;

    pt_nav_fac_dialog_show = (NAV_FAC_URC_DIALOG_VIEW_T *) c_mem_alloc(sizeof(NAV_FAC_URC_DIALOG_VIEW_T));

    if(pt_nav_fac_dialog_show == NULL)
    {
        return APP_UIR_OUT_OF_MEMORY;
    }
    c_memset(pt_nav_fac_dialog_show,0 , sizeof(NAV_FAC_URC_DIALOG_VIEW_T));

    /* dialog background image */
    i4_ret = _nav_fac_urc_dialog_image_init(pt_nav_fac_dialog_show);
    if(WGLR_OK != i4_ret)
    {
        c_mem_free(pt_nav_fac_dialog_show);  //ke_vizio_20110330 for clean warning.
        return NAVR_FAIL;
    }

    /* Create content frame widget */
    do
    {
        /* Content Frame */
        i4_ret =  _nav_fac_urc_dialog_create_frm(pt_nav_fac_dialog_show,
                                                 pt_nav_fac_dialog_init->pf_wdgt_proc,       /* App assigns the pf_wdgt_proc */
                                                 pt_nav_fac_dialog_init->h_parent,
                                                 pt_nav_fac_dialog_init->pt_rect,
                                                 pt_nav_fac_dialog_init->pt_begin_offset);

        if(i4_ret != APP_UIR_OK)
        {
            break;
        }

        /* txtinfo */
        i4_ret =  _nav_fac_urc_dialog_create_txtinfo(pt_nav_fac_dialog_show,
                                                     pt_nav_fac_dialog_init->pt_rect,
                                                     pt_nav_fac_dialog_init->ui2_txt_align_type);

        if(i4_ret != APP_UIR_OK)
        {
            break;
        }

        /*set all visible */
        c_wgl_set_visibility(pt_nav_fac_dialog_show->h_frm_simple_dialog, WGL_SW_RECURSIVE);

        /* Return the h_simple_dialog handle */
        *nav_fac_dialog = pt_nav_fac_dialog_show->h_frm_simple_dialog;

        /* Done */
        i4_ret = _nav_fac_urc_dialog_set_attach_data(pt_nav_fac_dialog_show->h_frm_simple_dialog,
                                          pt_nav_fac_dialog_show);


    } while(0);

    if(i4_ret != APP_UIR_OK)
    {
        /* Release childs*/

        if(pt_nav_fac_dialog_show->h_txt_txtinfo != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_nav_fac_dialog_show->h_txt_txtinfo);
        }
        /* Release childs*/

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
static INT32 _nav_fac_urc_dialog_destory(HANDLE_T            h_simple_dialog)

{
      INT32   i4_ret;
      NAV_FAC_URC_DIALOG_VIEW_T*        pt_nav_fac_dialog;

      /* Get simple dialog structure */

      i4_ret = _nav_fac_urc_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_nav_fac_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

        if(pt_nav_fac_dialog->h_txt_txtinfo != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_nav_fac_dialog->h_txt_txtinfo);
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
static INT32 _nav_fac_urc_dialog_set_focus(HANDLE_T  h_simple_dialog, BOOL b_repaint)
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
static INT32 _nav_fac_urc_dialog_show(HANDLE_T            h_simple_dialog)
{
      INT32   i4_ret;
      NAV_FAC_URC_DIALOG_VIEW_T*        pt_nav_fac_dialog_show;

      /* Get simple dialog structure */

      i4_ret = _nav_fac_urc_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_nav_fac_dialog_show);
      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      /* i4_ret = c_wgl_show(pt_ui_simple_dialog->h_frm_simple_dialog, WGL_SW_NORMAL); */
      i4_ret = c_wgl_set_visibility(pt_nav_fac_dialog_show->h_frm_simple_dialog, WGL_SW_NORMAL);
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
static INT32 _nav_fac_urc_dialog_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    //NAV_FAC_DIALOG_T*  pt_this = &t_g_nav_fac_dialog;   //ke_20090123_mark : Never referenced

	//DBG_LOG_PRINT(("!!!!@djh %s :\n", __func__));


    c_memset(&t_g_nav_fac_urc_dialog, 0, sizeof(NAV_FAC_URC_DIALOG_T));

    t_g_nav_fac_urc_dialog.h_canvas = pt_ctx->t_gui_res.h_canvas;
//    t_g_nav_fac_urc_dialog.ui4_timer_delay = NAV_FAC_DIALOG_DEFAULT_TIMER_DELAY;

//    c_timer_create(&t_g_nav_fac_urc_dialog.h_hide_timer);

    {  //ke_vizio_20130401 : TF1013VIZUSMTKO0-734
    UINT32         ui4_fac_rc_val;
    //Turn off URC when power on.
    a_cfg_cust_fac_get(&ui4_fac_rc_val);
    //ui4_fac_rc_val = ui4_fac_rc_val & 0x0f;
    ui4_fac_rc_val = ui4_fac_rc_val & (~APP_CFG_CUST_FAC_RC_ON);  //ke_vizio_20130911 modify
    a_cfg_cust_fac_set(ui4_fac_rc_val);
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
static INT32 _nav_fac_urc_dialog_deinit(VOID)
{
    NAV_FAC_URC_DIALOG_T*  pt_this = &t_g_nav_fac_urc_dialog;

//    if (c_handle_valid(pt_this->h_hide_timer)) {
//        c_timer_delete(pt_this->h_hide_timer);
//    }

    pt_this->h_canvas   = NULL_HANDLE;
    pt_this->h_dialog= NULL_HANDLE;
    pt_this->h_hide_timer   = NULL_HANDLE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_fac_urc_dialog_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    UTF16_T*         pw2s_string;
	UINT32         ui4_fac_val;//jeff 20090107 add

    a_cfg_cust_fac_get(&ui4_fac_val);//jeff 20090107 add
    //Printf("*******Test key PPs********************\n");
    switch(ui4_key_code)
	{
	    case BTN_FAC_TEST:
            pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_TEST_MODE_ON);
            _nav_fac_urc_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_TEST_MODE_ON,
                                                                                 pw2s_string,
                                                                                 NULL);
			//c_dbg_secure_stmt("*******Test key On********************\n");
			break;
        case BTN_FAC_TEST_0:
            ui4_fac_val = ui4_fac_val | APP_CFG_CUST_FAC_RC_CHECK;
            a_cfg_cust_fac_set(ui4_fac_val);
			//c_dbg_secure_stmt("&&&&&&&&&&&&&&&&&&&&Test key 00000000&&&&&&&&&&&\n");
            break;
        default :
            break;
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
static INT32 _nav_fac_urc_dialog_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    //NAV_FAC_URC_DIALOG_T*  pt_this = &t_g_nav_fac_urc_dialog;
    UINT8   ui_temp_val = 0;

    a_cfg_get_factory_mode(&ui_temp_val);

    _nav_fac_urc_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_TEST_MODE_ON,
																 NULL,
																NULL);

    if((ui_temp_val & APP_CFG_FAC_MODE_BURNING_MASK) != 0)
    {
        nav_grab_activation(NAV_COMP_ID_BURNING_MODE);
    }
    else
    {
        nav_return_activation(NAV_COMP_ID_LAST_VALID_ENTRY);
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
static INT32 _nav_fac_urc_dialog_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_urc_dialog_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    INT32   i4_ret = 0;
    
    switch (pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_POWER_OFF:
        {
            //ke_vizio_20161109 add
            // Due to MG162 power off will not run the initial and hide function.
            // Turn off the URC function at here.
            UINT32         ui4_fac_val;

            a_cfg_cust_fac_get(&ui4_fac_val);
            if((ui4_fac_val & APP_CFG_CUST_FAC_RC_ON)>>4)
            {
                NAV_FAC_URC_DIALOG_T*  pt_this = &t_g_nav_fac_urc_dialog;
                
                ui4_fac_val = ui4_fac_val & (~APP_CFG_CUST_FAC_RC_ON);
                a_cfg_cust_fac_set(ui4_fac_val);

                i4_ret = c_wgl_set_visibility(pt_this->h_dialog, WGL_SW_HIDE);
                if(i4_ret != APP_UIR_OK)
                {
                    return i4_ret;
                }
                i4_ret = c_wgl_repaint(pt_this->h_dialog, NULL, TRUE);
                if(i4_ret != APP_UIR_OK)
                {
                    return i4_ret;
                }
            }
            break;
        }
        
        default:
            break;
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
static INT32 _nav_fac_urc_dialog_hide(
                    VOID
                    )
{
    NAV_FAC_URC_DIALOG_T*  pt_this = &t_g_nav_fac_urc_dialog;

    /* Hide the widgets */
    if(pt_this->e_dialog_id != NAV_FAC_DIALOG_ID_NULL)
    {
        _nav_fac_urc_dialog_destory(pt_this->h_dialog);
        pt_this->h_dialog = NULL_HANDLE;
        pt_this->e_dialog_id = NAV_FAC_DIALOG_ID_NULL;
    }

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_dialog_prompt_msg_dialog_ex
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_fac_urc_dialog_prompt_msg_dialog_ex(
    NAV_FAC_URC_DIALOG_ID_T     e_dialog_id,
    UTF16_T*            pw2s_msg,
    UINT16              ui2_txt_align_type,
    GL_RECT_T*          pt_rect,
    wgl_widget_proc_fct pf_wdgt_proc)
{
    INT32                       i4_ret;
    NAV_FAC_URC_DIALOG_T*  pt_this = &t_g_nav_fac_urc_dialog;
    NAV_FAC_URC_DIALOG_SHOW_INIT_T     t_nav_fac_dialog_init;

    /* Hide the previous */
    if(pt_this->e_dialog_id != NAV_FAC_DIALOG_ID_NULL)
    {
        _nav_fac_urc_dialog_destory(pt_this->h_dialog);
        pt_this->e_dialog_id = NAV_FAC_DIALOG_ID_NULL;
        pt_this->h_dialog    = NULL_HANDLE;
    }

    /* Create the dialog */
    if(pt_this->e_dialog_id != e_dialog_id)
    {
        c_memset(&t_nav_fac_dialog_init, 0, sizeof(NAV_FAC_URC_DIALOG_SHOW_INIT_T));

        t_nav_fac_dialog_init.h_parent                       = pt_this->h_canvas;
        t_nav_fac_dialog_init.pf_wdgt_proc                   = pf_wdgt_proc;
        t_nav_fac_dialog_init.ui2_txt_align_type             = ui2_txt_align_type;
        t_nav_fac_dialog_init.pt_rect                        = pt_rect;
        i4_ret = _nav_fac_urc_dialog_create(&t_nav_fac_dialog_init,
                                  &pt_this->h_dialog);
        if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}
        pt_this->e_dialog_id = e_dialog_id;
    }

    /* Modify the attribute */
    i4_ret = _nav_fac_urc_dialog_set_text(pt_this->h_dialog, pw2s_msg);
    if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}
    /* If the Dialog component is not active componet, Grab activation.
       Otherwise, set focus to current dialog*/
    if(nav_get_active_component() != NAV_COMP_ID_FAC_URC_DIALOG)
    {
        i4_ret = nav_grab_activation(NAV_COMP_ID_FAC_URC_DIALOG);
    }
    else
    {
        _nav_fac_urc_dialog_set_focus(pt_this->h_dialog, FALSE);
        _nav_fac_urc_dialog_show(pt_this->h_dialog);
        c_wgl_repaint(pt_this->h_dialog, NULL, TRUE);
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
static INT32 _nav_fac_urc_dialog_prompt_msg_dialog(
    NAV_FAC_URC_DIALOG_ID_T     e_dialog_id,
    UTF16_T*            pw2s_msg,
    wgl_widget_proc_fct pf_wdgt_proc
    )
{
    return _nav_fac_urc_dialog_prompt_msg_dialog_ex(e_dialog_id,
                                           pw2s_msg,
                                           WGL_AS_CENTER_CENTER,
                                           NULL,
                                           pf_wdgt_proc);
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_INX_fac_urc_dialog_register(VOID)
{
    NAV_COMP_T      t_comp;
    INT32           i4_ret;

	//DBG_LOG_PRINT(("!!!!@djh %s :\n", __func__));

    c_memset(&t_comp,0,sizeof(NAV_COMP_T));
    /* NAV_COMP_ID_DIALOG */
    t_comp.pf_init           = _nav_fac_urc_dialog_init;
    t_comp.pf_deinit         = _nav_fac_urc_dialog_deinit;
    t_comp.pf_is_key_handler = _nav_fac_urc_dialog_is_key_handler;
    t_comp.pf_activate       = _nav_fac_urc_dialog_activate;
    t_comp.pf_inactivate     = _nav_fac_urc_dialog_inactivate;
    t_comp.pf_hide           = _nav_fac_urc_dialog_hide;
    t_comp.pf_handle_msg     = _nav_fac_urc_dialog_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_FAC_URC_DIALOG, &t_comp, COMP_EXC_SET_FAC_URC_DIALOG);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
//jeff 20090319 add
INT32 nav_fac_urc_dialog_hide(VOID)
{
    return _nav_fac_urc_dialog_hide();
}

INT32 nav_fac_urc_dialog_show(VOID)
{
    UTF16_T*         pw2s_string;
    pw2s_string = MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_TEST_MODE_ON);
    _nav_fac_urc_dialog_prompt_msg_dialog(NAV_FAC_DIALOG_ID_TEST_MODE_ON,
                                            pw2s_string,
                                            NULL);
	return NAVR_OK;
}
