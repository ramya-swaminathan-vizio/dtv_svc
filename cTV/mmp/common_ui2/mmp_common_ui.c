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
 * $RCSfile: mmp_common_ui.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                     include files
 ----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_common.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_obj_type.h"
#include "u_wgl_text.h"
#include "u_wgl_icon.h"
#include "u_wgl_lb.h"
#include "c_wgl.h"
#include "app_util/a_common.h"
#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp_common_ui.h"
#include "res/mmp/common_ui/mmp_common_ui_rc.h"
#include "res/mmp/video_engine/mmp_video_engine_rc.h"
#ifdef MMP_GUI_AUTHORING
#include "res/mmp/img/mmp_img.h"
#include "res/mmp/common_ui/gen/mmp_common_ui_diag_2_option_layout.h"
#ifdef MMP_GUI_AUTHORING_DP
#include "res/mmp/gen/mmp_vdp_layout.h"
#include "res/mmp/gen/mmp_pdp_layout.h"
#endif
#endif
#ifdef MMP_GUI_AUTHORING_DP
#include "res/mmp/gen/mmp_vdp_layout.h"
#include "res/mmp/gen/mmp_pdp_layout.h"
#endif
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
#ifdef MMP_GUI_AUTHORING 
static com_ui_msg_box_user_sel_nfy g_pf_msg_box_nfy;
static VOID* g_pv_msg_box_tag;
#endif
 /*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _mmp_com_ui_running_box_timer_cb(
        HANDLE_T                h_timer,
        VOID*                   pv_pt_running_box);

static VOID _mmp_com_ui_running_box_timer_handler(
        VOID*                   pv_pt_running_box,
        VOID*                   pv_unused1, 
        VOID*                   pv_unused2, 
        VOID*                   pv_unused3);

static INT32 _mmp_com_ui_update_running_box(
        MMP_COM_UI_RUNNING_BOX_T*           pt_running_box);
#ifdef MMP_GUI_AUTHORING
static INT32 _mmp_com_ui_msg_box_frm_nfy(HANDLE_T            h_widget,
                                         UINT32              ui4_msg,
                                         VOID*               pv_param1,
                                         VOID*               pv_param2);
static INT32 _mmp_com_ui_msg_box_build_nav(VOID);
#endif
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/ 

/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_create_toolbar
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
extern INT32 mmp_com_ui_create_toolbar(
    HANDLE_T                                h_parent,
    const MMP_COM_UI_TOOLBAR_PARAM_T*       pt_param,
    MMP_COM_UI_TOOLBAR_T*                   pt_toolbar)
{
    GL_RECT_T                               t_rect = {FRM_TOOLBAR_X, FRM_TOOLBAR_Y, FRM_TOOLBAR_X + FRM_TOOLBAR_W, FRM_TOOLBAR_Y + FRM_TOOLBAR_H};
    WGL_FONT_INFO_T                         t_font_info = MMP_COM_UI_RC_GET_TOOLBAR_HINT_FONT();
    GL_COLOR_T                              t_color = MMP_COM_UI_RC_GET_TOOLBAR_HINT_COLOR();
    WGL_IMG_INFO_T                          t_img_info;
    INT32                                   i4_ret;
    UINT8                                   ui1_num,ui1_i;
    UINT32                                  ui4_text_style = MMP_COM_UI_RC_DETAILPAGE_STYLE;
    UINT32                                  ui4_style = MMP_COM_UI_RC_ICON_STYLE;
    
    /*check param*/
    if(NULL == pt_param || NULL == pt_toolbar)
    {
        return MMPR_INV_ARG;
    }

    /*create toolbar*/
    pt_toolbar->h_bar = NULL_HANDLE;
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 MMP_COM_UI_DEFAULT_ALPHA,
                                 (VOID*)MMP_COM_UI_RC_TOOLBAR_STYLE,
                                 0,
                                 &pt_toolbar->h_bar);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));

        pt_toolbar->h_bar = NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    do 
    {    
        /*get image*/
        i4_ret = mmp_img_get_img(MMP_IMG_IMAGE_ID_TOOL_BAR, &t_img_info.u_img_data.t_standard.t_enable);
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /*set background image*/
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_disable   = t_img_info.u_img_data.t_standard.t_enable;
        t_img_info.u_img_data.t_standard.t_highlight = t_img_info.u_img_data.t_standard.t_enable;
        i4_ret = c_wgl_do_cmd(pt_toolbar->h_bar, WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_BK), WGL_PACK(&t_img_info));
        if(WGLR_OK != i4_ret)
        {
            break;
        }
        
        /*create label*/
        i4_ret = MMPR_OK;
        ui1_num = pt_param->ui1_hint_num;
        if(ui1_num > MMP_COM_UI_RC_TOOLBAR_MAX_TXT)
        {
            i4_ret = MMPR_INV_ARG;
            break;
        }
        for(ui1_i = 0; ui1_i < ui1_num; ui1_i++)
        {
            i4_ret = mmp_com_ui_create_txt_widget(pt_toolbar->h_bar, 
                                                   ui4_text_style,
                                                   pt_param->aws_hint[ui1_i], 
                                                   &pt_param->at_rect_hint[ui1_i], 
                                                   &t_color, 
                                                   &t_font_info, 
                                                   &pt_toolbar->ah_hint[ui1_i]);
            if(MMPR_OK != i4_ret)
            {
                break;
            }
        }
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /*create icons*/
        i4_ret = MMPR_OK;
        ui1_num = pt_param->ui1_icon_num;
        if(ui1_num > MMP_COM_UI_RC_TOOLBAR_MAX_ICON)
        {
            i4_ret = MMPR_INV_ARG;
            break;
        }
        for(ui1_i = 0; ui1_i < ui1_num; ui1_i++)
        {
            i4_ret = mmp_com_ui_create_icon_widget(pt_toolbar->h_bar, 
                                                    ui4_style,
                                                    &pt_param->at_rect_icon[ui1_i],
                                                    pt_param->ah_img[ui1_i],
                                                    &pt_toolbar->ah_icon[ui1_i]);
            if(MMPR_OK != i4_ret)
            {
                break;
            }
        }
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /*vol bar*/
        i4_ret = mmp_com_ui_create_pg_bar(pt_toolbar->h_bar,
                                          (GL_RECT_T*)&(pt_param->t_rect_vol_bar),
                                          &pt_toolbar->h_vol_bar);
        if (MMPR_OK != i4_ret)
        {
            break;
        }
        return MMPR_OK;
    }
    while(0);

    /*free toolbar*/
    i4_ret = c_wgl_destroy_widget_ex(pt_toolbar->h_bar,FALSE);
    MMP_ASSERT(WGLR_OK == i4_ret);
    
    pt_toolbar->h_bar = NULL_HANDLE;
    return MMPR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_create_statusbar_2
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
extern INT32 mmp_com_ui_create_statusbar(
    HANDLE_T                                h_parent,
    const MMP_COM_UI_STATUSBAR_PARAM_T*     pt_param,
    MMP_COM_UI_STATUSBAR_T*                 pt_statusbar)
{
    GL_RECT_T                               t_rect = {STATUS_FRM_X, STATUS_FRM_Y, STATUS_FRM_X + STATUS_FRM_W, STATUS_FRM_Y + STATUS_FRM_H};
    WGL_FONT_INFO_T                         t_font_info = MMP_COM_UI_RC_GET_STATUSBAR_LABEL_FONT();
    GL_COLOR_T                              t_color = MMP_COM_UI_RC_GET_STATUS_LABEL_COLOR();
    WGL_IMG_INFO_T                          t_img_info;
    INT32                                   i4_ret;
    UINT8                                   ui1_num,ui1_i;
    UINT32                                  ui4_text_style = MMP_COM_UI_RC_SBAR_TXT_STYLE;
    UINT32                                  ui4_style = MMP_COM_UI_RC_ICON_STYLE;
        
    /*check param*/
    if(NULL == pt_param || NULL == pt_statusbar)
    {
        return MMPR_INV_ARG;
    }

    /*create status bar*/
    pt_statusbar->h_bar = NULL_HANDLE;
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 MMP_COM_UI_DEFAULT_ALPHA,
                                 (VOID*)MMP_COM_UI_RC_STATUSBAR_STYLE,
                                 0,
                                 &pt_statusbar->h_bar);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));
        
        pt_statusbar->h_bar = NULL_HANDLE;
        return MMPR_FAIL;
    }

    do 
    {
        /*get image*/
        i4_ret = mmp_img_get_img(MMP_IMG_IMAGE_ID_STATUS_BAR, &t_img_info.u_img_data.t_standard.t_enable);
        if(MMPR_OK != i4_ret)
        {
            break;
        }
        
        /*set background image*/
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_disable   = t_img_info.u_img_data.t_standard.t_enable;
        t_img_info.u_img_data.t_standard.t_highlight = t_img_info.u_img_data.t_standard.t_enable;
        i4_ret = c_wgl_do_cmd(pt_statusbar->h_bar, WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_BK), WGL_PACK(&t_img_info));
        if(WGLR_OK != i4_ret)
        {
            break;
        }
        
        /*create txt*/
        i4_ret = MMPR_OK;
        ui1_num = pt_param->ui1_label_num;
        if(ui1_num > MMP_COM_UI_RC_STATUSBAR_MAX_TXT)
        {
            i4_ret = MMPR_INV_ARG;
            break;
        }
        for(ui1_i = 0; ui1_i < ui1_num; ui1_i++)
        {
            i4_ret = mmp_com_ui_create_txt_widget(pt_statusbar->h_bar,
                                                   ui4_text_style,
                                                   pt_param->aw2s_label[ui1_i], 
                                                   &pt_param->at_rect_label[ui1_i], 
                                                   &t_color, 
                                                   &t_font_info, 
                                                   &pt_statusbar->ah_label[ui1_i]);
            if(MMPR_OK != i4_ret)
            {
                break;
            }
        }
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /*progress bar*/
        i4_ret = mmp_com_ui_create_pg_bar(pt_statusbar->h_bar,
                                          (GL_RECT_T*)&pt_param->t_rect_pb,
                                          &pt_statusbar->h_pb_playback);
        if (MMPR_OK != i4_ret)
        {
            break;
        }
        
        /*create status icon*/
        i4_ret = MMPR_OK;
        ui1_num = pt_param->ui1_icon_num;
        if(ui1_num > MMP_COM_UI_RC_STATUSBAR_MAX_TXT)
        {
            i4_ret = MMPR_INV_ARG;
            break;
        }
        for(ui1_i = 0; ui1_i < ui1_num; ui1_i++)
        {
            i4_ret = mmp_com_ui_create_icon_widget(pt_statusbar->h_bar, 
                                                    ui4_style,
                                                    &pt_param->at_rect_icon[ui1_i],
                                                    pt_param->ah_img[ui1_i],
                                                    &pt_statusbar->ah_icon[ui1_i]);

            if(MMPR_OK != i4_ret)
            {
                break;
            }
        }
        
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        return MMPR_OK;

    } while(0);

    /*free statusbar*/
    i4_ret = c_wgl_destroy_widget_ex(pt_statusbar->h_bar,FALSE);
    MMP_ASSERT(WGLR_OK == i4_ret);
    
    pt_statusbar->h_bar = NULL_HANDLE;
    return MMPR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_create_detail_page
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
/*mmp enhance for detail page by xiangdong_ding 100318*/
#ifndef MMP_GUI_AUTHORING_DP  
extern INT32 mmp_com_ui_create_detail_page(
    HANDLE_T                                h_parent,
    UINT32                                  ui4_elem_count,
    GL_RECT_T*                              pt_rect,
    UINT32                                  ui4_text_style,
    BOOL                                    b_custom_rect,
    const MMP_COM_UI_DETAIL_ELEM_PARAM_T*   at_elem_param,
    HANDLE_T*                               ah_elem,
    HANDLE_T*                               ph_detail_page)
{
    GL_RECT_T                               t_rect = {FRM_DETAIL_X, FRM_DETAIL_Y, FRM_DETAIL_X + FRM_DETAIL_W, FRM_DETAIL_Y + FRM_DETAIL_H};
    WGL_FONT_INFO_T                         t_font_info = MMP_COM_UI_RC_GET_DETAILPGAE_TEXT_FONT();
    GL_COLOR_T                              t_color = MMP_COM_UI_RC_GET_DETAILPGAE_TEXT_COLOR();
    WGL_IMG_INFO_T                          t_img_info;
    INT32                                   i4_ret;
    UINT32                                  i;

    /*check param*/
    if(NULL == ph_detail_page)
    {
        return MMPR_INV_ARG;
    }

    if(ui4_elem_count > 0 && (NULL == at_elem_param || NULL == ah_elem))
    {
        return MMPR_INV_ARG;
    }

    if(TRUE == b_custom_rect && NULL == pt_rect)
    {
        return MMPR_INV_ARG;
    }

    if(b_custom_rect)
    {
        t_rect.i4_left   = pt_rect->i4_left;
        t_rect.i4_right  = pt_rect->i4_right;
        t_rect.i4_top    = pt_rect->i4_top;
        t_rect.i4_bottom = pt_rect->i4_bottom;
    }

    /*create detail page*/
    *ph_detail_page = NULL_HANDLE;
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 MMP_COM_UI_DEFAULT_ALPHA,
                                 (VOID*)MMP_COM_UI_RC_DETAILPAGE_STYLE,
                                 0,
                                 ph_detail_page);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));
        
        *ph_detail_page = NULL_HANDLE;
        return MMPR_FAIL;
    }

    do 
    {    
        /*get image*/
        i4_ret = mmp_img_get_img(MMP_IMG_IMAGE_ID_DETAIL_PAGE, &t_img_info.u_img_data.t_standard.t_enable);
        if(MMPR_OK != i4_ret)
        {
            break;
        }
    
        /*set background image*/
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_disable   = t_img_info.u_img_data.t_standard.t_enable;
        t_img_info.u_img_data.t_standard.t_highlight = t_img_info.u_img_data.t_standard.t_enable;
        i4_ret = c_wgl_do_cmd(*ph_detail_page, WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_BK), WGL_PACK(&t_img_info));
        if(WGLR_OK != i4_ret)
        {
            break;
        }

        /*create hints*/
        i4_ret = MMPR_OK;
        for(i = 0; i < ui4_elem_count; i++)
        {
            i4_ret = mmp_com_ui_create_txt_widget(*ph_detail_page, 
                                                   ui4_text_style,
                                                   at_elem_param[i].ws_desc,
                                                   &at_elem_param[i].t_rect,
                                                   &t_color,
                                                   &t_font_info,
                                                   &ah_elem[i]);
            if(MMPR_OK != i4_ret)
            {
                break;
            }
          
            /* set text alignment for multi language*/
            i4_ret = c_wgl_do_cmd(ah_elem[i], 
                                  WGL_CMD_TEXT_SET_ALIGN,
                                  (VOID*)((i%2==0)?WGL_AS_RIGHT_CENTER:WGL_AS_LEFT_CENTER), 
                                  NULL);

            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_TEXT_SET_ALIGN) fail. i4_ret = %d.\r\n", i4_ret));
                break;
            }
        }
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        return MMPR_OK;

    } while(0);

    /*free detail page*/
    i4_ret = c_wgl_destroy_widget_ex(*ph_detail_page,FALSE);
    MMP_ASSERT(WGLR_OK == i4_ret);
    
    *ph_detail_page = NULL_HANDLE;
    return MMPR_FAIL;
}
#endif

/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_create_pg_bar
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_create_pg_bar(HANDLE_T h_parent,
                              GL_RECT_T* pt_rect,
                               HANDLE_T* ph_pg_bar)
{
    INT32                       i4_ret;
    WGL_INSET_T     t_inset;
    WGL_HIMG_TPL_T h_vol_bar_bg,h_vol_bar;
    WGL_IMG_INFO_T        t_img_info;

    /* create progress bar */
    i4_ret = c_wgl_create_widget(h_parent,     
                                 HT_WGL_WIDGET_PROGRESS_BAR, 
                                 WGL_CONTENT_PROGRESS_BAR_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 NULL,
                                 255,
                                 (VOID *)NULL,
                                 NULL,
                                 ph_pg_bar);
    IS_MMPR_OK (i4_ret);

    /* Set background image */
    IS_MMPR_OK (mmp_img_get_img(MMP_IMG_IMAGE_ID_VOL_BAR_BG,&h_vol_bar_bg));
    t_img_info.e_type = WGL_IMG_SET_BASIC;
    t_img_info.u_img_data.t_standard.t_enable =    h_vol_bar_bg;
    t_img_info.u_img_data.t_standard.t_disable =   h_vol_bar_bg;
    i4_ret = c_wgl_do_cmd(*ph_pg_bar,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    IS_MMPR_OK (i4_ret);

    /* Set progressbar's BAR */
    IS_MMPR_OK (mmp_img_get_img(MMP_IMG_IMAGE_ID_VOL_BAR,&h_vol_bar));
    t_img_info.e_type = WGL_IMG_SET_BASIC;
    t_img_info.u_img_data.t_standard.t_enable =    h_vol_bar;
    t_img_info.u_img_data.t_standard.t_disable =   h_vol_bar;
    i4_ret = c_wgl_do_cmd(*ph_pg_bar,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_LEVEL_1),
                          WGL_PACK(&t_img_info));

    /* Set Insets */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_pg_bar, 
                          WGL_CMD_PG_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    IS_MMPR_OK (i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_pg_bar, 
                          WGL_CMD_PG_SET_BAR_INSET,
                          &t_inset,
                          NULL);
    IS_MMPR_OK (i4_ret);

    /* Set Range */
    i4_ret = c_wgl_do_cmd(*ph_pg_bar,
                          WGL_CMD_PG_SET_RANGE,
                          WGL_PACK((INT32)0),
                          WGL_PACK((INT32)100));
    IS_MMPR_OK (i4_ret);

    /* Set Display Modes */
    i4_ret = c_wgl_do_cmd (*ph_pg_bar,
                           WGL_CMD_PG_SET_DISPLAY_MODE,
                           WGL_PACK(WGL_PG_DM_HIDE_IDR),
                           NULL);
    IS_MMPR_OK (i4_ret);

    /* Set Position */
    i4_ret = c_wgl_do_cmd(*ph_pg_bar,
                          WGL_CMD_PG_SET_POS,
                          WGL_PACK((INT32)0),
                          NULL);
    IS_MMPR_OK (i4_ret);

    return i4_ret ; 
}


/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_create_running_ball
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_create_running_box(
    HANDLE_T                                h_parent,
    const MMP_COM_UI_RUNNING_BOX_PARAM_T*   pt_param,
    MMP_COM_UI_RUNNING_BOX_T*               pt_running_box)
{
    GL_RECT_T                   t_rect;
    INT32                       i4_ret;
    UINT32                      ui4_style = MMP_COM_UI_RC_ICON_STYLE;

    /*check param*/
    if(NULL == pt_param || NULL == pt_running_box)
    {
        return MMPR_INV_ARG;
    }

    /*zero instance first*/
    c_memset(pt_running_box, 0, sizeof(MMP_COM_UI_RUNNING_BOX_T));

    /*create a icon widget*/
    SET_RECT_BY_SIZE(&t_rect, 
                     pt_param->t_offset.i4_x, 
                     pt_param->t_offset.i4_y, 
                     49, 
                     16);
    
    i4_ret = mmp_com_ui_create_icon_widget(h_parent, 
                                            ui4_style,
                                            &t_rect,
                                            MMP_SCANNING_ANI_ICON_IMG(0),
                                            &pt_running_box->h_icon);
    if(MMPR_OK != i4_ret)
    {
        pt_running_box->h_icon = NULL_HANDLE;
        return i4_ret;
    }

    /*create a timer for running*/
    i4_ret = c_timer_create(&pt_running_box->h_timer);
    if(OSR_OK != i4_ret)
    {
        pt_running_box->h_timer = NULL_HANDLE;
        
        mmp_com_ui_free_running_box(pt_running_box);
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_free_running_box
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_free_running_box(
    MMP_COM_UI_RUNNING_BOX_T*   pt_running_box)
{
    if(NULL == pt_running_box)
    {
        return MMPR_OK;
    }

    /*free widget*/
    if(pt_running_box->h_icon)
    {
        c_wgl_destroy_widget_ex(pt_running_box->h_icon,FALSE);
        pt_running_box->h_icon = NULL_HANDLE;
    }

    /*free timer*/
    if(pt_running_box->h_timer)
    {
        c_timer_delete(pt_running_box->h_timer);
        pt_running_box->h_timer = NULL_HANDLE;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_start_running_box
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_start_running_box(
    MMP_COM_UI_RUNNING_BOX_T*   pt_running_box)
{
    INT32                       i4_ret;
    
    if(NULL == pt_running_box)
    {
        return MMPR_INV_ARG;
    }

    if(pt_running_box->b_running)
    {
        return MMPR_OK;
    }

    pt_running_box->ui1_scene_idx = 0;

    i4_ret = _mmp_com_ui_update_running_box(pt_running_box);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }
    
    pt_running_box->b_running = TRUE;
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_stop_running_box
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_stop_running_box(
    MMP_COM_UI_RUNNING_BOX_T*   pt_running_box)
{
    INT32                       i4_ret;
    
    if(NULL == pt_running_box)
    {
        return MMPR_INV_ARG;
    }
    
    if(FALSE == pt_running_box->b_running)
    {
        return MMPR_OK;
    }

    /*hide widget*/
    i4_ret = c_wgl_show(pt_running_box->h_icon, WGL_SW_HIDE);
    if(WGLR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    /*stop timer*/
    i4_ret = c_timer_stop(pt_running_box->h_timer);
    if(OSR_OK != i4_ret)
    {
        ABORT_APPL(DBG_MOD_PHOTO, ("stop Error-Timer failed!"));
    }
    pt_running_box->b_running = FALSE;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_create_nfybox
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_create_nfybox(HANDLE_T            h_parent,
                               HANDLE_T*           ph_nfybox)
{
    GL_RECT_T                   t_rect = {MMP_COM_UI_RC_NFY_X, MMP_COM_UI_RC_NFY_Y, MMP_COM_UI_RC_NFY_X + MMP_COM_UI_RC_NFY_W, MMP_COM_UI_RC_NFY_Y + MMP_COM_UI_RC_NFY_H};
    WGL_FONT_INFO_T             t_font_info = MMP_COM_UI_RC_NFY_GET_TEXT_FONT();
    GL_COLOR_T                  t_color = MMP_COM_UI_RC_NFY_GET_TEXT_COLOR();
    /*WGL_IMG_INFO_T              t_img_info;*/
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_INSET_T                 t_inset;
    INT32                       i4_ret;
        
    /*check param*/
    if(NULL == ph_nfybox)
    {
        return MMPR_INV_ARG;
    }

    /*create widget*/
    *ph_nfybox = NULL_HANDLE;
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL, 
                                 &t_rect,
                                 NULL,
                                 MMP_COM_UI_DEFAULT_ALPHA,
                                 (VOID*)(MMP_COM_UI_RC_NFY_TEXT_STYLE),
                                 NULL,
                                 ph_nfybox);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));
        
        *ph_nfybox = NULL_HANDLE;
        return MMPR_FAIL;
    }

    do 
    {
        /*get image*/
        /*
        i4_ret = mmp_img_get_img(MMP_IMG_IMAGE_ID_NFY_BK, &t_img_info.u_img_data.t_standard.t_enable);
        if(MMPR_OK != i4_ret)
        {
            break;
        }
        */
        /*set background image*/
        /*
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_disable   = t_img_info.u_img_data.t_standard.t_enable;
        t_img_info.u_img_data.t_standard.t_highlight = t_img_info.u_img_data.t_standard.t_enable;
        i4_ret = c_wgl_do_cmd(*ph_nfybox, WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_BK), WGL_PACK(&t_img_info));
        if(WGLR_OK != i4_ret)
        {
            break;
        }
        */
        
        /*foreground color*/
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable = t_color;
        t_clr_info.u_color_data.t_standard.t_disable = t_color;
        t_clr_info.u_color_data.t_standard.t_highlight = t_color;
        i4_ret = c_wgl_do_cmd(*ph_nfybox, WGL_CMD_GL_SET_COLOR, WGL_PACK(WGL_CLR_TEXT), WGL_PACK(&t_clr_info));
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_GL_SET_COLOR) fail. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        /*set inset*/
        t_inset.i4_left = MMP_COM_UI_RC_NFY_INSET_LEFT;
        t_inset.i4_top = MMP_COM_UI_RC_NFY_INSET_TOP;
        t_inset.i4_right = MMP_COM_UI_RC_NFY_INSET_RIGHT;
        t_inset.i4_bottom = MMP_COM_UI_RC_NFY_INSET_BOTTOM;
        i4_ret = c_wgl_do_cmd(*ph_nfybox, WGL_CMD_TEXT_SET_CNT_INSET, (VOID*)&t_inset, NULL);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_TEXT_SET_CNT_INSET) fail. i4_ret = %d.\r\n", i4_ret));
            break;
        }
        
        /*font*/
        i4_ret = c_wgl_do_cmd(*ph_nfybox, WGL_CMD_GL_SET_FONT, (VOID*)&t_font_info, NULL);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_GL_SET_FONT) fail. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        /* set text alignment */
        i4_ret = c_wgl_do_cmd(*ph_nfybox, WGL_CMD_TEXT_SET_ALIGN, (VOID*)MMP_COM_UI_RC_NFY_TEXT_ALIGN, NULL);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_TEXT_SET_ALIGN) fail. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        return MMPR_OK;

    } while(0);

    /*free statusbar*/
    i4_ret = c_wgl_destroy_widget_ex(*ph_nfybox,FALSE);
    MMP_ASSERT(WGLR_OK == i4_ret);
    
    *ph_nfybox = NULL_HANDLE;
    return MMPR_FAIL;
}

/*-----------------------------------------------------------------------------
 * private VIEW methods implementations
 *---------------------------------------------------------------------------*/ 
/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_create_txt_widget
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_create_txt_widget(
    HANDLE_T                    h_parent,
    UINT32                      ui4_style,
    UTF16_T*                    ws_text,
    const GL_RECT_T*            pt_rect,
    const GL_COLOR_T*           pt_clr_fg,
    const WGL_FONT_INFO_T*      pt_font,
    HANDLE_T*                   ph_txt)
{
    WGL_COLOR_INFO_T            t_clr_info;
    INT32                       i4_ret;
    
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL, 
                                 pt_rect,
                                 NULL,
                                 255,
                                 (VOID*)(ui4_style),
                                 NULL,
                                 ph_txt);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));

        *ph_txt = NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    do 
    {
        /*foreground color*/
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable = *pt_clr_fg;
        t_clr_info.u_color_data.t_standard.t_disable = *pt_clr_fg;
        t_clr_info.u_color_data.t_standard.t_highlight = *pt_clr_fg;
        i4_ret = c_wgl_do_cmd(*ph_txt, WGL_CMD_GL_SET_COLOR, WGL_PACK(WGL_CLR_TEXT), WGL_PACK(&t_clr_info));
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_GL_SET_COLOR) fail. i4_ret = %d.\r\n", i4_ret));
            break;
        }
    
        /*font*/
        i4_ret = c_wgl_do_cmd(*ph_txt, WGL_CMD_GL_SET_FONT, (VOID*)pt_font, NULL);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_GL_SET_FONT) fail. i4_ret = %d.\r\n", i4_ret));
            break;
        }
    
        /*text*/
        if(ws_text)
        {
            i4_ret = c_wgl_do_cmd(*ph_txt, WGL_CMD_TEXT_SET_TEXT, WGL_PACK(ws_text), WGL_PACK((UINT16)0xFFFF));
            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_TEXT_SET_TEXT) fail. i4_ret = %d.\r\n", i4_ret));
                break;
            }
        }

        return MMPR_OK;
    
    } while(0);

    /*free widget*/
    i4_ret = c_wgl_destroy_widget_ex(*ph_txt,FALSE);
    MMP_ASSERT(WGLR_OK == i4_ret);
    
    *ph_txt = NULL_HANDLE;
    return MMPR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_create_icon_widget
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_create_icon_widget(
    HANDLE_T                    h_parent,
    UINT32                      ui4_style,
    const GL_RECT_T*            pt_rect,
    WGL_HIMG_TPL_T              t_img_tpl,
    HANDLE_T*                   ph_icon)
{
    WGL_IMG_INFO_T              t_img_info;
    INT32                       i4_ret;
    
    /*create widget*/
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 NULL,
                                 255,
                                 (VOID*)(ui4_style),
                                 NULL,
                                 ph_icon);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));
        
        *ph_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    do 
    {
        if(NULL_HANDLE != t_img_tpl)
        {
            /*set image*/
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
            t_img_info.u_img_data.t_standard.t_enable    = t_img_tpl;
            t_img_info.u_img_data.t_standard.t_disable   = t_img_tpl;
            t_img_info.u_img_data.t_standard.t_highlight = t_img_tpl;
            i4_ret = c_wgl_do_cmd(*ph_icon, WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_FG), WGL_PACK(&t_img_info));
            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_GL_SET_IMAGE) fail. i4_ret = %d.\r\n", i4_ret));
                break;
            }
        }
    
        /* set icon alignment */
        i4_ret = c_wgl_do_cmd(*ph_icon, WGL_CMD_ICON_SET_ALIGN, (VOID*)WGL_AS_CENTER_CENTER, NULL);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_ICON_SET_ALIGN) fail. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        return MMPR_OK;

    } while(0);

    /*free widget*/
    i4_ret = c_wgl_destroy_widget_ex(*ph_icon,FALSE);
    MMP_ASSERT(WGLR_OK == i4_ret);
    
    *ph_icon = NULL_HANDLE;
    return MMPR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_com_ui_running_box_timer_cb
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _mmp_com_ui_running_box_timer_cb(
    HANDLE_T                    h_timer,
    VOID*                       pv_pt_running_box)
{
    /*post a message to itself*/
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                _mmp_com_ui_running_box_timer_handler,
                                (VOID*)pv_pt_running_box,
                                NULL, 
                                NULL,
                                NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_com_ui_running_box_timer_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _mmp_com_ui_running_box_timer_handler(
    VOID*                       pv_pt_running_box,
    VOID*                       pv_unused1, 
    VOID*                       pv_unused2, 
    VOID*                       pv_unused3)
{
    MMP_COM_UI_RUNNING_BOX_T*   pt_running_box = (MMP_COM_UI_RUNNING_BOX_T*)pv_pt_running_box;
    
    if(NULL == pt_running_box)
    {
        MMP_ASSERT(0);
        return;
    }
    
    if(FALSE == pt_running_box->b_running)
    {
        return;
    }
    
    pt_running_box->ui1_scene_idx++;
    if(pt_running_box->ui1_scene_idx >= MMP_SCANNING_ANI_IMG_NUM)
    {
        pt_running_box->ui1_scene_idx %= MMP_SCANNING_ANI_IMG_NUM;
    }
    
    /**/
    _mmp_com_ui_update_running_box(pt_running_box);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_com_ui_update_running_box
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _mmp_com_ui_update_running_box(
    MMP_COM_UI_RUNNING_BOX_T*   pt_running_box)
{
    WGL_IMG_INFO_T              t_img_info;
    INT32                       i4_ret;
    
    if(pt_running_box->ui1_scene_idx >= MMP_SCANNING_ANI_IMG_NUM)
    {
        pt_running_box->ui1_scene_idx %= MMP_SCANNING_ANI_IMG_NUM;
    }
    /*update image*/
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = MMP_SCANNING_ANI_ICON_IMG(pt_running_box->ui1_scene_idx);
    t_img_info.u_img_data.t_standard.t_disable   = MMP_SCANNING_ANI_ICON_IMG(pt_running_box->ui1_scene_idx);
    t_img_info.u_img_data.t_standard.t_highlight = MMP_SCANNING_ANI_ICON_IMG(pt_running_box->ui1_scene_idx);
    i4_ret = c_wgl_do_cmd(pt_running_box->h_icon, WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_FG), WGL_PACK(&t_img_info));
    if(WGLR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }
    
    /*show widget*/
    if(pt_running_box->b_running)
    {
        c_wgl_repaint(pt_running_box->h_icon, NULL, TRUE);
    }
    else
    {
        c_wgl_show(pt_running_box->h_icon, WGL_SW_NORMAL);    
    }
    
    i4_ret = c_timer_start(pt_running_box->h_timer,
                           MMP_COM_UI_RC_RB_DUR,
                           X_TIMER_FLAG_ONCE,
                           _mmp_com_ui_running_box_timer_cb,
                           pt_running_box);
    
    if(OSR_OK != i4_ret)
    {
        ABORT_APPL(DBG_MOD_PHOTO, ("start Error-Timer failed!"));
    }

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_load_icon
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_load_icon(HANDLE_T  h_icon,
                          WGL_HIMG_TPL_T t_img_tpl,
                          BOOL b_repaint)
{
    INT32 i4_ret; 
    WGL_IMG_INFO_T t_img_info;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = t_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = t_img_tpl;
    i4_ret = c_wgl_do_cmd(h_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info)
                          );
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    if (b_repaint)
    {
        c_wgl_repaint(h_icon,NULL,TRUE);
    }

    return i4_ret ; 
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_set_text
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_set_text(HANDLE_T      h_txt,
                          UTF16_T*      w2s_text,
                          BOOL          b_repaint)
{
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(h_txt, 
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_text),
                          WGL_PACK((UINT16)0xFFFF));
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }    

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(h_txt,NULL,TRUE);
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_create_player_frm
 *
 * Description: This function creates the main (root) frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_create_player_frm (HANDLE_T    h_canvas,
                                  wgl_widget_proc_fct pf_wdgt_proc,
                                  UINT8    ui1_alpha,
                                  HANDLE_T*   ph_frm)
{
    INT32               i4_ret;
    UINT32              ui4_canvas_width;
    UINT32              ui4_canvas_height;
    GL_RECT_T           t_rect;
    WGL_HIMG_TPL_T      h_img=NULL_HANDLE;
#if 0    
    WGL_COLOR_INFO_T    t_clr_info;
    GL_COLOR_T          t_color_bk = MMP_COM_UI_GET_CLR_BK();
#endif    
    WGL_IMG_INFO_T    t_img_info;

    /* Get canvas size. */
    i4_ret = c_wgl_get_canvas_size (h_canvas,
                                    & ui4_canvas_width,
                                    & ui4_canvas_height);
    if(WGLR_OK != i4_ret)
    {
         MMP_DBG_ERROR(("c_wgl_get_canvas_size() fail. i4_ret = %d.\r\n", i4_ret));
         return i4_ret;
    }  
    

    SET_RECT_BY_SIZE (& t_rect,
                      0,
                      0,
                      MMP_COM_UI_MAIN_W,
                      MMP_COM_UI_MAIN_H);

    /* Create widget. */
    i4_ret = c_wgl_create_widget (h_canvas,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  pf_wdgt_proc,
                                  ui1_alpha,
                                  (VOID*) 0,
                                  0,
                                  ph_frm);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));

        *ph_frm= NULL_HANDLE;
        return MMPR_FAIL;
    }
#if 0    
    /* Set background color. */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_color_bk;
    t_clr_info.u_color_data.t_standard.t_disable   = t_color_bk;
    t_clr_info.u_color_data.t_standard.t_highlight = t_color_bk;

    i4_ret = c_wgl_do_cmd (*ph_frm,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK (WGL_CLR_BK),
                           WGL_PACK (& t_clr_info));
#endif

    mmp_img_get_img(MMP_IMG_IMAGE_ID_MUSIC_PLAYER_BK,&h_img);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_img;
    t_img_info.u_img_data.t_standard.t_disable   = h_img;
    
    i4_ret = c_wgl_do_cmd(*ph_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_GL_SET_COLOR) fail. i4_ret = %d.\r\n", i4_ret));
        
        i4_ret = c_wgl_destroy_widget_ex(*ph_frm,FALSE);
        MMP_ASSERT(WGLR_OK == i4_ret);
        
        *ph_frm= NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    c_wgl_set_visibility(*ph_frm,WGL_SW_HIDE);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_info_ui_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_info_ui_create(HANDLE_T                      h_parent,
                              GL_RECT_T*                    pt_rect,
                              MMP_FP_INFO_HDLR_UI_TYPE_T    e_ui_type,
                              UINT8                         ui1_itm_num,
                              HANDLE_T*                     ph_page,
                              HANDLE_T*                     ah_title,
                              HANDLE_T*                     ah_value)
{
    INT32            i4_ret = -1;
    BOOL             b_thumb = TRUE;
    GL_RECT_T        t_rect_title, t_rect_val;
    UINT8            i = 0;
    GL_COLOR_T       t_mus_color_nor = MMP_COM_UI_RC_NFY_GET_TEXT_COLOR();;
    WGL_FONT_INFO_T  t_font_info;
#if NEVER
    switch(e_ui_type)
    {
        case MMP_FP_INFO_HDLR_UI_TYPE_TM_FOCUS:
        case MMP_FP_INFO_HDLR_UI_TYPE_TM_ACT_BK:
            b_thumb = TRUE;
            break;
        case MMP_FP_INFO_HDLR_UI_TYPE_LM_FOCUS:
        case MMP_FP_INFO_HDLR_UI_TYPE_LM_ACT_BK:
            b_thumb = TRUE;
            break;
        default:
            b_thumb = FALSE;
            break;
    }
#endif
    /*For New UI design, thumbnail and list mode use the same layout for info handler*/
    b_thumb = FALSE;

    /*prepare font info*/
    t_font_info.e_font_size = FE_FNT_SIZE_SMALL;
    t_font_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_font_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
    c_strcpy(t_font_info.a_c_font_name , SN_FONT_DEFAULT_SMALL);  
    t_font_info.i2_width = 0;

    do
    {
        i4_ret = c_wgl_create_widget(h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     pt_rect,
                                     NULL,
                                     255,
                                     (VOID*)WGL_STL_GL_NO_BK,
                                     0,
                                     ph_page);
        if(WGLR_OK != i4_ret)
        {
            break;
        }
        
        for(i = 0; i < ui1_itm_num; i++)
        {
            /*create title*/
            #if Never
            if(b_thumb)/*icon*/
            {
                WGL_HIMG_TPL_T   h_img = NULL_HANDLE;
                
                SET_RECT_BY_SIZE (&t_rect_title,
                                  TM_INFO_UI_TITLE_X + i*(TM_INFO_UI_TITLE_W + TM_INFO_UI_TITLE_GRAP + TM_INFO_UI_VAL_W),
                                  TM_INFO_UI_TITLE_Y,
                                  TM_INFO_UI_TITLE_W,
                                  TM_INFO_UI_TITLE_H);

                i4_ret = mmp_img_get_img(MMP_IMG_IMAGE_ID_REPEAT_ONCE, &h_img);
                if(MMPR_OK != i4_ret)
                {
                    break;
                }
                
                i4_ret = mmp_com_ui_create_icon_widget(*ph_page,
                                                       WGL_STL_GL_NO_BK,
                                                       &t_rect_title,
                                                       h_img,
                                                       &ah_title[i]);
                if(MMPR_OK != i4_ret)
                {
                    break;
                }
            }
            else/*text*/
            #endif
            {
                SET_RECT_BY_SIZE (&t_rect_title,
                                  LT_INFO_UI_TITLE_X,
                                  LT_INFO_UI_TITLE_Y + i*(LT_INFO_UI_TITLE_H + LT_INFO_UI_TITLE_GRAP),
                                  LT_INFO_UI_TITLE_W,
                                  LT_INFO_UI_TITLE_H);
                
                i4_ret = mmp_com_ui_create_txt_widget(*ph_page,
                                                      (WGL_STL_GL_NO_BK | WGL_STL_TEXT_SMART_CUT | WGL_STL_TEXT_MAX_512),
                                                      NULL,
                                                      &t_rect_title,
                                                      &t_mus_color_nor,
                                                      &t_font_info,
                                                      &ah_title[i]);
                if(MMPR_OK != i4_ret)
                {
                    break;
                }

                i4_ret = c_wgl_do_cmd(ah_title[i],
                                      WGL_CMD_TEXT_SET_ALIGN,
                                      (VOID*)WGL_AS_LEFT_CENTER,
                                      NULL);
                if(MMPR_OK != i4_ret)
                {
                    break;
                }
            }

            /*create value*/
            #if NEVER
            if(b_thumb)
            {
                SET_RECT_BY_SIZE (&t_rect_val,
                                  TM_INFO_UI_VAL_X + i*(TM_INFO_UI_VAL_W + TM_INFO_UI_TITLE_GRAP + TM_INFO_UI_TITLE_W),
                                  TM_INFO_UI_TITLE_Y,
                                  TM_INFO_UI_VAL_W,
                                  TM_INFO_UI_TITLE_H);
            }
            else
            #endif
            {
                SET_RECT_BY_SIZE (&t_rect_val,
                                  LT_INFO_UI_VAL_X,
                                  LT_INFO_UI_TITLE_Y + i*(LT_INFO_UI_TITLE_H + LT_INFO_UI_TITLE_GRAP),
                                  LT_INFO_UI_VAL_W,
                                  LT_INFO_UI_TITLE_H);
            }

            i4_ret = mmp_com_ui_create_txt_widget(*ph_page,
                                                  (WGL_STL_GL_NO_BK | WGL_STL_TEXT_SMART_CUT | WGL_STL_TEXT_MAX_512),
                                                  NULL,
                                                  &t_rect_val,
                                                  &t_mus_color_nor,
                                                  &t_font_info,
                                                  &ah_value[i]);
            if(MMPR_OK != i4_ret)
            {
                break;
            }

            i4_ret = c_wgl_do_cmd(ah_value[i],
                                  WGL_CMD_TEXT_SET_ALIGN,
                                  (VOID*)WGL_AS_LEFT_CENTER,
                                  NULL);
            if(MMPR_OK != i4_ret)
            {
                break;
            }
        }
    }while(0);
        
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_load_icon
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_info_ui_destroy(HANDLE_T       h_page)
{
    INT32 i4_ret = -1;
    
    if (NULL_HANDLE == h_page)
    {
        return MMPR_INV_ARG;
    }

    i4_ret = c_wgl_destroy_widget_ex(h_page, FALSE);
    
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_load_icon
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_info_ui_icon_create(HANDLE_T                      h_parent,
                                  UINT8                         ui1_icon_w,
                                  UINT8                         ui1_icon_h,
                                  UINT8                         ui1_index,
                                  HANDLE_T*                     ph_icon)
{
    INT32     i4_ret = -1;
    GL_RECT_T t_rect;

    SET_RECT_BY_SIZE (&t_rect,
                      LT_INFO_UI_TITLE_X,
                      LT_INFO_UI_TITLE_Y + ui1_index*(LT_INFO_UI_TITLE_H + LT_INFO_UI_TITLE_GRAP),
                      ui1_icon_w,
                      ui1_icon_h);
    
    i4_ret = mmp_com_ui_create_icon_widget(h_parent,
                                           WGL_STL_GL_NO_BK,
                                           &t_rect,
                                           NULL_HANDLE,
                                           ph_icon);
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: mmp_com_ui_get_date_time
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
extern INT32 mmp_com_ui_get_date_time(
   BOOL                         b_is_dtg_fmt,
   CHAR*                        ws_info,
   DTG_T*                       pt_dtg,
   UTF16_T*                     ws_d_and_t,
   UTF16_T*                     ws_date,
   UTF16_T*                     ws_time,
   UINT16                       ui2_lang_id)
{
    INT32    i4_ret = -1;
    CHAR     ac_year[5] = {0};
    CHAR     ac_month[16] = {0};
    CHAR     ac_day[3] = {0};
    CHAR     ac_hour[3] = {0};
    CHAR     ac_minute[3] = {0};
    CHAR     ac_second[3] = {0};
    CHAR*    pws_ptr = NULL;
    CHAR     s_str_d_and_t[128 + 1] = {0}, s_str_date[128 + 1] = {0},s_str_time[128 + 1] = {0};
    
    if(b_is_dtg_fmt)
    {
        if( pt_dtg == NULL )
        {
            return MMPR_FAIL;
        }
    }
    else
    {
        if( ws_info == NULL )
        {
            return MMPR_FAIL;
        }
    }

    if(b_is_dtg_fmt)
    {
        ac_year[0]   = pt_dtg->ui2_yr/1000 + '0';
        ac_year[1]   = (pt_dtg->ui2_yr - pt_dtg->ui2_yr/1000 * 1000)/100 + '0';
        ac_year[2]   = (pt_dtg->ui2_yr - pt_dtg->ui2_yr/100 * 100)/10 + '0';
        ac_year[3]   = (pt_dtg->ui2_yr - pt_dtg->ui2_yr/10 * 10) + '0';

        ac_month[0]  = pt_dtg->ui1_mo/10 + '0';
        ac_month[1]  = (pt_dtg->ui1_mo - pt_dtg->ui1_mo/10*10) + '0';

        ac_day[0]    = pt_dtg->ui1_day/10 + '0';
        ac_day[1]    = (pt_dtg->ui1_day - pt_dtg->ui1_day/10*10) + '0';

        ac_hour[0]   = pt_dtg->ui1_hr/10 + '0';
        ac_hour[1]   = (pt_dtg->ui1_hr - pt_dtg->ui1_hr/10*10) + '0';

        ac_minute[0] = pt_dtg->ui1_min/10 + '0';
        ac_minute[1] = (pt_dtg->ui1_min - pt_dtg->ui1_min/10*10) + '0';
    }
    else
    {
        pws_ptr = ws_info;
        c_strncpy(ac_year, pws_ptr, 4);
        pws_ptr = pws_ptr + 4 + 1;
        c_strncpy(ac_month, pws_ptr, 2);
        pws_ptr = pws_ptr + 2 + 1;
        c_strncpy(ac_day, pws_ptr, 2);
        pws_ptr = pws_ptr + 2 + 1;
        c_strncpy(ac_hour, ws_info+11, 2);
        pws_ptr = pws_ptr + 2 + 1;
        c_strncpy(ac_minute, ws_info+14, 2);
        pws_ptr = pws_ptr + 2 + 1;
        c_strncpy(ac_second, ws_info+17, 2);
    }

    c_sprintf(s_str_d_and_t, "%s-%s-%s %s:%s", ac_year, ac_month, ac_day, ac_hour, ac_minute);
    c_sprintf(s_str_date, "%s-%s-%s", ac_year, ac_month, ac_day);
    c_sprintf(s_str_time, "%s:%s", ac_hour, ac_minute);
    
    i4_ret = c_uc_ps_to_w2s(s_str_d_and_t, ws_d_and_t, 128 + 1 );
    if(UCR_OK != i4_ret)
    {
        ws_d_and_t = NULL;
    }

    i4_ret = c_uc_ps_to_w2s(s_str_date, ws_date, 128 + 1 );
    if(UCR_OK != i4_ret)
    {
        ws_d_and_t = NULL;
    }

    i4_ret = c_uc_ps_to_w2s(s_str_time, ws_time, 128 + 1 );
    if(UCR_OK != i4_ret)
    {
        ws_d_and_t = NULL;
    }
    
    return MMPR_OK;
}

#ifdef MMP_GUI_AUTHORING
static INT32 _mmp_com_ui_msg_box_frm_nfy(HANDLE_T            h_widget,
                                         UINT32              ui4_msg,
                                         VOID*               pv_param1,
                                         VOID*               pv_param2)
{   
    HANDLE_T                    h_wgt_src;
    WGL_NOTIFY_DATA_T*          pt_nfy_data;
    com_ui_msg_box_user_sel_nfy pf_user_sel_nfy;
    VOID*                       pv_tag;
    INT32                       i4_ret;
    switch(ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        pf_user_sel_nfy = g_pf_msg_box_nfy;
        pv_tag = g_pv_msg_box_tag;
        h_wgt_src = (HANDLE_T) pv_param1;
        pt_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

        if (WGL_NC_BTN_PUSHED == pt_nfy_data->ui4_nc_code)
        {
            if (h_wgt_src == mmp_common_ui_diag_2_option_get_wgt_hdl(WID_MMP_COMMON_UI_DIAG_2_OPTION_BTN_ITEM0))
            {
                pf_user_sel_nfy(MMP_COM_UI_MSG_BOX_ITEM0, pv_tag);
            }
            else if(h_wgt_src == mmp_common_ui_diag_2_option_get_wgt_hdl(WID_MMP_COMMON_UI_DIAG_2_OPTION_BTN_ITEM1))
            {
                pf_user_sel_nfy(MMP_COM_UI_MSG_BOX_ITEM1, pv_tag);
            }
            i4_ret = c_wgl_float(h_widget, FALSE, WGL_NO_AUTO_REPAINT);
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_destroy_widget_ex(h_widget, TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        
        break;

    default:
        break;
    }   
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _mmp_com_ui_msg_box_build_nav(VOID)
{
    INT32           i4_ret;
    WGL_KEY_LINK_T  at_link[1];
    HANDLE_T        h_wid_item0;
    HANDLE_T        h_wid_item1;
    
    h_wid_item0 = mmp_common_ui_diag_2_option_get_wgt_hdl(WID_MMP_COMMON_UI_DIAG_2_OPTION_BTN_ITEM0);
    h_wid_item1 = mmp_common_ui_diag_2_option_get_wgt_hdl(WID_MMP_COMMON_UI_DIAG_2_OPTION_BTN_ITEM1);

    if (NULL_HANDLE == h_wid_item0 ||
        NULL_HANDLE == h_wid_item1)
    {
        return (MMPR_FAIL);
    }

    at_link[0].ui4_key  = BTN_CURSOR_RIGHT;
    at_link[0].h_widget = h_wid_item1;
    i4_ret = c_wgl_set_navigation(h_wid_item0, 1, at_link);
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }

    at_link[0].ui4_key  = BTN_CURSOR_LEFT;
    at_link[0].h_widget = h_wid_item0;
    i4_ret = c_wgl_set_navigation(h_wid_item1, 1, at_link);
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }    
    return (MMPR_OK);
}
#endif
INT32 mmp_com_ui_msg_box_2_option(HANDLE_T h_parent,
                                  MMP_COM_UI_MSG_BOX_2_OP_PARAM_T *pt_param,
                                  VOID* pv_tag)
{   
#ifdef MMP_GUI_AUTHORING
    INT32       i4_ret;
    HANDLE_T    h_widget;
    HANDLE_T    h_focus_widget;

    i4_ret = mmp_common_ui_diag_2_option_reg_wgt_cb(WID_MMP_COMMON_UI_DIAG_2_OPTION_FRM_FRM,
                                                    _mmp_com_ui_msg_box_frm_nfy);
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret= mmp_common_ui_diag_2_option_create_ui(h_parent);
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }

    h_widget = mmp_common_ui_diag_2_option_get_wgt_hdl(WID_MMP_COMMON_UI_DIAG_2_OPTION_TXT_TITLE);

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pt_param->pw2s_title),
                          WGL_PACK((UINT16)0xFFFF));
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }

    h_widget = mmp_common_ui_diag_2_option_get_wgt_hdl(WID_MMP_COMMON_UI_DIAG_2_OPTION_TXT_CAPTION);

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pt_param->pw2s_promt_text),
                          WGL_PACK((UINT16)0xFFFF));
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }

    h_widget = mmp_common_ui_diag_2_option_get_wgt_hdl(WID_MMP_COMMON_UI_DIAG_2_OPTION_BTN_ITEM0);

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(pt_param->pw2s_item0_caption),
                          WGL_PACK((UINT16)0xFFFF));
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }
    h_focus_widget = h_widget;

    h_widget = mmp_common_ui_diag_2_option_get_wgt_hdl(WID_MMP_COMMON_UI_DIAG_2_OPTION_BTN_ITEM1);

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(pt_param->pw2s_item1_caption),
                          WGL_PACK((UINT16)0xFFFF));
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }

    _mmp_com_ui_msg_box_build_nav();
    
    h_widget = mmp_common_ui_diag_2_option_get_wgt_hdl(WID_MMP_COMMON_UI_DIAG_2_OPTION_FRM_FRM);

    i4_ret = c_wgl_set_visibility(h_widget, WGL_SW_RECURSIVE);
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret = c_wgl_set_focus(h_focus_widget, WGL_NO_AUTO_REPAINT);
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }
    
    g_pf_msg_box_nfy = pt_param->pf_user_sel_proc_fct;
    g_pv_msg_box_tag = pv_tag;

    i4_ret = c_wgl_float(h_widget, TRUE, WGL_ASYNC_AUTO_REPAINT);
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }
#endif    
    return (MMPR_OK);
}
