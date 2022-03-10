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
 * $RCSfile: epg_view.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/13 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 0dc5e5894593d8bd6b2c6ecc9869c8fa $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "epg/epg_view.h"
#include "epg/epg_ctrl.h"


/*
   Structures.
*/
typedef struct
{
    /* frame widgets */
    HANDLE_T      h_main_frm;                /* main frame */
    HANDLE_T      h_base_frm;                /* base map frame */
    HANDLE_T      h_desc_frm;                /* program description frame */
    HANDLE_T      h_desc_bk_frm;             /* description background frame */
    HANDLE_T      h_video_frm;               /* video frame */
    HANDLE_T      h_passwd_frm;              /* password frame */

    /* list box widgets */
    HANDLE_T      h_chn_lst;                 /* channel list box */
    HANDLE_T      h_prg_lst;                 /* program list box */
    HANDLE_T      h_surf_lst;                /* surf list box */
    HANDLE_T      h_desc_lst;                /* program description list box */
    HANDLE_T      h_icon_lst;                /* icon list box */
    HANDLE_T      h_help_lst;                /* help list box */
    HANDLE_T      h_type_lst;                /* type list box */
    HANDLE_T      h_subtype_lst;             /* subtype list box */

    /* text widgets */
    HANDLE_T      h_time_txt;                /* time text */
    HANDLE_T      h_retrieve_txt;            /* retrieving text */
    HANDLE_T      h_prg_txt;                 /* program info text */
    HANDLE_T      h_chn_txt;                 /* channel info text */
    HANDLE_T      h_video_txt;               /* video text */
    HANDLE_T      h_desc_txt;                /* program description text */
    HANDLE_T      h_page_txt;                /* page index text */
    HANDLE_T      h_passwd_txt;              /* password text */

#ifdef APP_EPG_FULL_VIDEO
    HANDLE_T      h_passwd_alarm_txt;              /* password alarm text */
#endif

    /* hyper text widgets */
    HANDLE_T      h_dci_hts;                 /* direct channel input hyper text */

    /* icon widgets */
    HANDLE_T      h_retrieve_icon;           /* retrieving icon */

    /* edit widgets */
    HANDLE_T      h_passwd_edit;             /* password edit box */

    CHAR          s_font_name[32];           /* font name */

}   EPG_VIEW_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static EPG_VIEW_T  t_g_view;

/*-----------------------------------------------------------------------------
                    static function declarations
-----------------------------------------------------------------------------*/
static INT32 _epg_view_create_main_frm (VOID);
static INT32 _epg_view_create_base_frm (VOID);
static INT32 _epg_view_create_desc_frm (VOID);
static INT32 _epg_view_create_desc_bk_frm (VOID);
static INT32 _epg_view_create_video_frm (VOID);
static INT32 _epg_view_create_passwd_frm (VOID);
static INT32 _epg_view_create_chn_lst (VOID);
static INT32 _epg_view_create_prg_lst (VOID);
static INT32 _epg_view_create_surf_lst (VOID);
static INT32 _epg_view_create_desc_lst (VOID);
static INT32 _epg_view_create_icon_lst (VOID);
static INT32 _epg_view_create_help_lst (VOID);
static INT32 _epg_view_create_time_txt (VOID);
static INT32 _epg_view_create_retrieve_txt (VOID);
static INT32 _epg_view_create_prg_txt (VOID);
static INT32 _epg_view_create_chn_txt (VOID);
static INT32 _epg_view_create_video_txt (VOID);
static INT32 _epg_view_create_desc_txt (VOID);
static INT32 _epg_view_create_page_txt (VOID);
static INT32 _epg_view_create_passwd_txt (VOID);
static INT32 _epg_view_create_dci_hts (VOID);
static INT32 _epg_view_create_retrieve_icon (VOID);
static INT32 _epg_view_create_passwd_edit (VOID);

#ifdef APP_EPG_THEME_SEARCH

static INT32 _epg_view_create_type_lst (VOID);
static INT32 _epg_view_create_subtype_lst (VOID);

#endif /* APP_EPG_THEME_SEARCH */


/*-----------------------------------------------------------------------------
 * Name: _epg_nfy_frm
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_nfy_frm (HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    HANDLE_T              h_cb_widget;
    WGL_NOTIFY_DATA_T*    pt_wgl_nfy_data;

    h_cb_widget     = (HANDLE_T) pv_param1;
    pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if (ui4_msg == WGL_MSG_NOTIFY)
    {
        if (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_GL_GET_FOCUS) /* Some widget gets focus. */
        {
            epg_ctrl_process_msg (EPG_MSG_VIEW_WGL_GET_FOCUS, NULL, 0);
        }
        else if ((h_cb_widget == t_g_view.h_prg_lst) &&
                 (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_LB_ELEM_HLT)) /* Program list's element is highlighted. */
        {
            if (pt_wgl_nfy_data->u.t_lb_elem_hlt.b_is_highlighted)
            {
                epg_app_send_msg (EPG_MSG_VIEW_WGL_PRG_LST_ELEM_HLT, NULL, 0);
            }
        }
        else if ((h_cb_widget == t_g_view.h_prg_lst) &&
                 (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_LB_REACH_TOP)) /* Program list reaches top. */
        {
            epg_app_send_msg (EPG_MSG_VIEW_WGL_PRG_LST_ELEM_REACH_TOP, NULL, 0);
        }
        else if ((h_cb_widget == t_g_view.h_prg_lst) &&
                 (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_LB_REACH_BOTTOM)) /* Program list reaches bottom. */
        {
            epg_app_send_msg (EPG_MSG_VIEW_WGL_PRG_LST_ELEM_REACH_BOTTOM, NULL, 0);
        }
        else if ((h_cb_widget == t_g_view.h_passwd_edit) &&
                 (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_EB_CHANGED)) /* Password edit gets input. */
        {
            epg_ctrl_process_msg (EPG_MSG_VIEW_WGL_PASSWD_EDIT_INPUT, NULL, 0);
        }
        else if ((h_cb_widget == t_g_view.h_type_lst) &&
                 (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_LB_ELEM_HLT)) /* Type list's element is highlighted. */
        {
            if (pt_wgl_nfy_data->u.t_lb_elem_hlt.b_is_highlighted)
            {
                epg_ctrl_process_msg (EPG_MSG_VIEW_WGL_TYPE_LST_ELEM_HLT, NULL, 0);
            }
        }
    }

    /* Call default procedure. */
    RET_ON_ERR (c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_main_frm
 *
 * Description: This function creates the main/root frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_main_frm (VOID)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    HANDLE_T            h_canvas;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)epg_osd_get_offset_x (),
                      (INT32)epg_osd_get_offset_y (),
                      (INT32)MAIN_FRM_W,
                      (INT32)MAIN_FRM_H);

    /* Get canvas handle. */
    RET_ON_ERR (epg_osd_get_canvas_handle (& h_canvas));

    /* Create widget. */
    RET_ON_ERR (c_wgl_create_widget (h_canvas,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     _epg_nfy_frm,
                                     255,
                                     (VOID*) WGL_STL_GL_NO_IMG_UI,
                                     0,
                                     & t_g_view.h_main_frm));

    /* Set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_main_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_main_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_main_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_main_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Background color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_base_frm
 *
 * Description: This function creates a base frame to display background
 *              image.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_base_frm (VOID)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)BASE_FRM_X,
                      (INT32)BASE_FRM_Y,
                      (INT32)BASE_FRM_W,
                      (INT32)BASE_FRM_H);

    /* Create widget. */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) EPG_WIDGET_STYLE,
                                     0,
                                     & t_g_view.h_base_frm));

    /* Set theme. */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_base_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = BASE_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = BASE_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = BASE_FRM_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_base_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* Background image */
                              WGL_PACK (& t_img_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_desc_frm
 *
 * Description: This function creates the description frame to contain time
 *              details, TV-rating and program details.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_desc_frm (VOID)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)DESC_FRM_X,
                      (INT32)DESC_FRM_Y,
                      (INT32)DESC_FRM_W,
                      (INT32)DESC_FRM_H);

    /* Create widget. */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) EPG_WIDGET_STYLE,
                                     0,
                                     & t_g_view.h_desc_frm));

    /* Set theme. */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_desc_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_desc_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_desc_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),   /* Background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = DESC_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = DESC_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = DESC_FRM_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* Background image */
                              WGL_PACK (& t_img_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_desc_bk_frm
 *
 * Description: This function creates the description background frame to
 *              display the background when the description frame is hided.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_desc_bk_frm (VOID)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)DESC_BK_FRM_X,
                      (INT32)DESC_BK_FRM_Y,
                      (INT32)DESC_BK_FRM_W,
                      (INT32)DESC_BK_FRM_H);

    /* Create widget. */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) EPG_WIDGET_STYLE,
                                     0,
                                     & t_g_view.h_desc_bk_frm));

    /* Set theme. */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_desc_bk_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_desc_bk_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_desc_bk_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_bk_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = DESC_BK_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = DESC_BK_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = DESC_BK_FRM_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_bk_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* Background image */
                              WGL_PACK (& t_img_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_video_frm
 *
 * Description: This function creates a video frame to display a black background
 *              while changing channels.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_video_frm (VOID)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)VIDEO_FRM_X,
                      (INT32)VIDEO_FRM_Y,
                      (INT32)VIDEO_FRM_W,
                      (INT32)VIDEO_FRM_H);

    /* Create widget. */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) EPG_WIDGET_STYLE,
                                     0,
                                     & t_g_view.h_video_frm));

    /* Set theme. */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_video_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_video_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_video_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_video_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Background color */
                              WGL_PACK (& t_color_info)));

#ifndef APP_EPG_FULL_VIDEO

    WGL_IMG_INFO_T      t_img_info;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = VIDEO_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = VIDEO_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = VIDEO_FRM_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_video_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* Background image */
                              WGL_PACK (& t_img_info)));

#endif /* APP_EPG_FULL_VIDEO */

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_passwd_frm
 *
 * Description: This function creates a password frame to contin the password
 *              dialog.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_passwd_frm (VOID)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)PASSWD_FRM_X,
                      (INT32)PASSWD_FRM_Y,
                      (INT32)PASSWD_FRM_W,
                      (INT32)PASSWD_FRM_H);

    /* Create widget. */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     _epg_nfy_frm,
                                     255,
                                     (VOID*) EPG_WIDGET_STYLE,
                                     0,
                                     & t_g_view.h_passwd_frm));

    /* Set theme. */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_passwd_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_passwd_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_passwd_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = PASSWD_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = PASSWD_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = PASSWD_FRM_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_frm,
                              WGL_CMD_GL_SET_IMAGE, /* Background image */
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(& t_img_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_chn_lst
 *
 * Description: This function creates a channel list to display channel no.
 *              and channel name in horizontal style.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_chn_lst (VOID)
{
    UINT16                      ui2_i;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[5];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_IMG_INFO_T              t_img_info;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;

    /* Previous channel */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = CHN_LB_COL_PREV_ALIGN;
    at_cols[0].ui2_max_text_len = 10;
    at_cols[0].ui2_width        = (UINT16)CHN_LB_COL_PREV_W;

    /* Arrow left */
    at_cols[1].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[1].ui1_align        = CHN_LB_COL_LEFT_ALIGN;
    at_cols[1].ui2_width        = (UINT16)CHN_LB_COL_LEFT_W;

    /* Current channel */
    at_cols[2].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[2].ui1_align        = CHN_LB_COL_CRNT_ALIGN;
    at_cols[2].ui2_max_text_len = 60;
    at_cols[2].ui2_width        = (UINT16)CHN_LB_COL_CRNT_W;

    /* Arrow right */
    at_cols[3].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[3].ui1_align        = CHN_LB_COL_RIGHT_ALIGN;
    at_cols[3].ui2_width        = (UINT16)CHN_LB_COL_RIGHT_W;

    /* Next channel */
    at_cols[4].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[4].ui1_align        = CHN_LB_COL_NEXT_ALIGN;
    at_cols[4].ui2_max_text_len = 10;
    at_cols[4].ui2_width        = (UINT16)CHN_LB_COL_NEXT_W;

    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT | WGL_STL_LB_FIXED_ELEM_NUM | EPG_WIDGET_STYLE;
    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = (UINT16)CHN_LB_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 5;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)CHN_LB_X,
                      (INT32)CHN_LB_Y,
                      (INT32)CHN_LB_W,
                      (INT32)CHN_LB_H);

    /* Create widget. */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_LIST_BOX,
                                     WGL_CONTENT_LIST_BOX_DEF,
                                     WGL_BORDER_TRANSP,
                                     &t_rect,
                                     NULL,
                                     255,
                                     & t_lb_init,
                                     NULL,
                                     & t_g_view.h_chn_lst));

    /* Set font size to previous channel. */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = CHN_LB_COL_PREV_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (0),
                              WGL_PACK (& t_fnt_info)));

    /* Set font size to current channel. */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = CHN_LB_COL_CRNT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (2),
                              WGL_PACK (& t_fnt_info)));

    /* Set font size to next channel. */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = CHN_LB_COL_NEXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (4),
                              WGL_PACK (& t_fnt_info)));

    /* Set content inset. */
    t_inset.i4_left   = CHN_LB_CNT_INSET_L;
    t_inset.i4_right  = CHN_LB_CNT_INSET_R;
    t_inset.i4_top    = CHN_LB_CNT_INSET_T;
    t_inset.i4_bottom = CHN_LB_CNT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* Set element inset. */
    t_inset.i4_left   = CHN_LB_ELEM_INSET_L;
    t_inset.i4_right  = CHN_LB_ELEM_INSET_R;
    t_inset.i4_top    = CHN_LB_ELEM_INSET_T;
    t_inset.i4_bottom = CHN_LB_ELEM_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_ELEM_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* Set column previous channel insets. */
    t_inset.i4_left   = CHN_LB_COL_PREV_INSET_L;
    t_inset.i4_right  = CHN_LB_COL_PREV_INSET_R;
    t_inset.i4_top    = CHN_LB_COL_PREV_INSET_T;
    t_inset.i4_bottom = CHN_LB_COL_PREV_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (0),
                              WGL_PACK (& t_inset)));

    /* Set column arrow left insets. */
    t_inset.i4_left   = CHN_LB_COL_LEFT_INSET_L;
    t_inset.i4_right  = CHN_LB_COL_LEFT_INSET_R;
    t_inset.i4_top    = CHN_LB_COL_LEFT_INSET_T;
    t_inset.i4_bottom = CHN_LB_COL_LEFT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (1),
                              WGL_PACK (& t_inset)));

    /* Set column current channel insets. */
    t_inset.i4_left   = CHN_LB_COL_CRNT_INSET_L;
    t_inset.i4_right  = CHN_LB_COL_CRNT_INSET_R;
    t_inset.i4_top    = CHN_LB_COL_CRNT_INSET_T;
    t_inset.i4_bottom = CHN_LB_COL_CRNT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (2),
                              WGL_PACK (& t_inset)));

    /* Set column arrow right insets. */
    t_inset.i4_left   = CHN_LB_COL_RIGHT_INSET_L;
    t_inset.i4_right  = CHN_LB_COL_RIGHT_INSET_R;
    t_inset.i4_top    = CHN_LB_COL_RIGHT_INSET_T;
    t_inset.i4_bottom = CHN_LB_COL_RIGHT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (3),
                              WGL_PACK (& t_inset)));

    /* Set column next channel insets. */
    t_inset.i4_left   = CHN_LB_COL_NEXT_INSET_L;
    t_inset.i4_right  = CHN_LB_COL_NEXT_INSET_R;
    t_inset.i4_top    = CHN_LB_COL_NEXT_INSET_T;
    t_inset.i4_bottom = CHN_LB_COL_NEXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (4),
                              WGL_PACK (& t_inset)));

    /* Set images. */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_ITEM_IMAGE,
                              WGL_PACK_2 (0, 1),
                              WGL_PACK (h_g_epg_img_arrow_left)));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_ITEM_IMAGE,
                              WGL_PACK_2 (0, 3),
                              WGL_PACK (h_g_epg_img_arrow_right)));

    /* Set theme. */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_chn_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_chn_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_chn_lst_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = CHN_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = CHN_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = CHN_LB_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* Background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_chn_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_chn_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_chn_lst_vp);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_VP_BK), /* Viewport background color */
                              WGL_PACK (& t_color_info)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_chn_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_chn_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_chn_lst_elem_hlt_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_chn_lst_elem_hlt_uf_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_chn_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_chn_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_chn_lst_elem_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_ELEM_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Element background color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_chn_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_chn_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_chn_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_chn_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_chn_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_chn_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_chn_lst_col_bk);

    for (ui2_i = 0; ui2_i < 5; ui2_i ++ )
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2 (ui2_i, WGL_CLR_BK), /* Columns background color */
                                  WGL_PACK (& t_color_elem)));
    }

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_chn_lst_col_prev_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_chn_lst_col_prev_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_chn_lst_col_prev_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_chn_lst_col_prev_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_chn_lst_col_prev_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_chn_lst_col_prev_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_chn_lst_col_prev_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (0, WGL_CLR_TEXT), /* Previous channel text color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_chn_lst_col_crnt_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_chn_lst_col_crnt_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_chn_lst_col_crnt_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_chn_lst_col_crnt_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_chn_lst_col_crnt_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_chn_lst_col_crnt_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_chn_lst_col_crnt_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (2, WGL_CLR_TEXT), /* Current channel text color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_chn_lst_col_next_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_chn_lst_col_next_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_chn_lst_col_next_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_chn_lst_col_next_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_chn_lst_col_next_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_chn_lst_col_next_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_chn_lst_col_next_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (4, WGL_CLR_TEXT), /* Next channel text color */
                              WGL_PACK (& t_color_elem)));

    /* Set long text scroll effect */
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_FORCE_SCRL_UNFOCUS;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 1;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = EPG_LONG_TXT_SCRL_DELAY;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                              WGL_PACK (& t_hlt_elem_effect),
                              NULL));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_prg_lst
 *
 * Description: This function creates a program listing to display events.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_prg_lst (VOID)
{
    UINT16                      ui2_i;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[PRG_LB_COL_NUM];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_LB_TITLE_INFO_T         t_title_info;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_IMG_INFO_T              t_img_info;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;

    /* Date */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = PRG_LB_COL_DATE_ALIGN;
    at_cols[0].ui2_max_text_len = EPG_DT_SYMBOL_MAX_LEN;
    at_cols[0].ui2_width        = (UINT16)PRG_LB_COL_DATE_W;

    /* Time */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = PRG_LB_COL_TIME_ALIGN;
    at_cols[1].ui2_max_text_len = EPG_DT_HOUR_MIN_MAX_LEN;
    at_cols[1].ui2_width        = (UINT16)PRG_LB_COL_TIME_W;

    /* Event title */
    at_cols[2].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[2].ui1_align        = PRG_LB_COL_TITLE_ALIGN;
    at_cols[2].ui2_max_text_len = 80;
    at_cols[2].ui2_width        = (UINT16)PRG_LB_COL_TITLE_W;

#ifndef APP_EPG_ICON_SEP

    /* Lock indicator */
    at_cols[3].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[3].ui1_align        = PRG_LB_COL_LOCK_ALIGN;
    at_cols[3].ui2_width        = (UINT16)PRG_LB_COL_LOCK_W;

    /* CC flag */
    at_cols[4].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[4].ui1_align        = PRG_LB_COL_CC_ALIGN;
    at_cols[4].ui2_width        = (UINT16)PRG_LB_COL_CC_W;

#endif /* APP_EPG_ICON_SEP */

    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER
                                  | WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_NO_SCROLL
                                  | WGL_STL_LB_ANIM_FORCE_DISABLE
                                  | EPG_WIDGET_STYLE;

    t_lb_init.ui2_max_elem_num  = ELEM_VIEW_SIZE;
    t_lb_init.ui2_elem_size     = (UINT16)PRG_LB_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = PRG_LB_COL_NUM;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      (INT32)PRG_LB_X,
                      (INT32)PRG_LB_Y,
                      (INT32)PRG_LB_W,
                      (INT32)PRG_LB_H);

    /* Create widget. */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_LIST_BOX,
                                     WGL_CONTENT_LIST_BOX_DEF,
                                     WGL_BORDER_UNIFORM,
                                     &t_rect,
                                     NULL,
                                     255,
                                     & t_lb_init,
                                     NULL,
                                     & t_g_view.h_prg_lst));

    if (! ((PRG_LB_TITLE_X == 0) &&
           (PRG_LB_TITLE_Y == 0) &&
           (PRG_LB_TITLE_W == 0) &&
           (PRG_LB_TITLE_H == 0)))
    {
        /* Set title info. */
        SET_RECT_BY_SIZE (& t_title_info.t_rect,
                          PRG_LB_TITLE_X,
                          PRG_LB_TITLE_Y,
                          PRG_LB_TITLE_W,
                          PRG_LB_TITLE_H);

        t_title_info.ui1_align = PRG_LB_TITLE_ALIGN;

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                                  WGL_CMD_LB_SET_TITLE_INFO,
                                  WGL_PACK (& t_title_info),
                                  NULL));

        /* Set title font. */
        c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
        c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

        t_fnt_info.e_font_size  = PRG_LB_TITLE_FNT_SIZE;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                                  WGL_CMD_GL_SET_FONT,
                                  WGL_PACK (& t_fnt_info),
                                  NULL));
    }

    /* Set font size to column date. */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = PRG_LB_COL_DATE_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (0),
                              WGL_PACK ( &t_fnt_info)));

    /* Set font size to column time. */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = PRG_LB_COL_TIME_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (1),
                              WGL_PACK (& t_fnt_info)));

    /* Set font size to column title. */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = PRG_LB_COL_TITLE_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (2),
                              WGL_PACK (& t_fnt_info)));

    /* Set border inset. */
    t_inset.i4_left   = PRG_LB_BDR_INSET_L;
    t_inset.i4_right  = PRG_LB_BDR_INSET_R;
    t_inset.i4_top    = PRG_LB_BDR_INSET_T;
    t_inset.i4_bottom = PRG_LB_BDR_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_GL_SET_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* Set content inset. */
    t_inset.i4_left   = (INT32)PRG_LB_CNT_INSET_L;
    t_inset.i4_right  = (INT32)PRG_LB_CNT_INSET_R;
    t_inset.i4_top    = (INT32)PRG_LB_CNT_INSET_T;
    t_inset.i4_bottom = (INT32)PRG_LB_CNT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* Set element inset. */
    t_inset.i4_left   = PRG_LB_ELEM_INSET_L;
    t_inset.i4_right  = PRG_LB_ELEM_INSET_R;
    t_inset.i4_top    = PRG_LB_ELEM_INSET_T;
    t_inset.i4_bottom = PRG_LB_ELEM_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_ELEM_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* Set column data inset. */
    t_inset.i4_left   = (INT32)PRG_LB_COL_DATE_INSET_L;
    t_inset.i4_right  = (INT32)PRG_LB_COL_DATE_INSET_R;
    t_inset.i4_top    = (INT32)PRG_LB_COL_DATE_INSET_T;
    t_inset.i4_bottom = (INT32)PRG_LB_COL_DATE_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (0),
                              WGL_PACK (& t_inset)));

    /* Set column time inset. */
    t_inset.i4_left   = (INT32)PRG_LB_COL_TIME_INSET_L;
    t_inset.i4_right  = (INT32)PRG_LB_COL_TIME_INSET_R;
    t_inset.i4_top    = (INT32)PRG_LB_COL_TIME_INSET_T;
    t_inset.i4_bottom = (INT32)PRG_LB_COL_TIME_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (1),
                              WGL_PACK (& t_inset)));

    /* Set column title inset. */
    t_inset.i4_left   = PRG_LB_COL_TITLE_INSET_L;
    t_inset.i4_right  = PRG_LB_COL_TITLE_INSET_R;
    t_inset.i4_top    = PRG_LB_COL_TITLE_INSET_T;
    t_inset.i4_bottom = PRG_LB_COL_TITLE_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (2),
                              WGL_PACK (& t_inset)));

#ifndef APP_EPG_ICON_SEP
    /* Set column lock inset. */
    t_inset.i4_left   = PRG_LB_COL_LOCK_INSET_L;
    t_inset.i4_right  = PRG_LB_COL_LOCK_INSET_R;
    t_inset.i4_top    = PRG_LB_COL_LOCK_INSET_T;
    t_inset.i4_bottom = PRG_LB_COL_LOCK_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (3),
                              WGL_PACK (& t_inset)));

    /* Set column cc inset. */
    t_inset.i4_left   = PRG_LB_COL_CC_INSET_L;
    t_inset.i4_right  = PRG_LB_COL_CC_INSET_R;
    t_inset.i4_top    = PRG_LB_COL_CC_INSET_T;
    t_inset.i4_bottom = PRG_LB_COL_CC_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (4),
                              WGL_PACK (& t_inset)));
#endif /* APP_EPG_ICON_SEP */

    /* Set element number to ELEM_VIEW_SIZE. */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_ELEM_NUM,
                              WGL_PACK (ELEM_VIEW_SIZE),
                              NULL));

    /* Set focus to program listing. */
    RET_ON_ERR (c_wgl_set_focus (t_g_view.h_prg_lst, FALSE));

    /* Set theme. */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_prg_lst_bdr);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_prg_lst_bdr);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_prg_lst_bdr_hlt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_GL_SET_BDR_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Border background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_prg_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_prg_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_prg_lst_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),       /* Background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_prg_lst_title_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_prg_lst_title_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_prg_lst_title_hlt_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_TITLE_FG), /* Title text color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = PRG_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = PRG_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = PRG_LB_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK), /* Background image */
                              WGL_PACK(& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_prg_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_prg_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_prg_lst_vp);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_VP_BK), /* Viewport background color */
                              WGL_PACK (& t_color_info)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_prg_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_prg_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_prg_lst_elem_hlt_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_prg_lst_elem_hlt_uf_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_prg_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_prg_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_prg_lst_elem_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_ELEM_COLOR,
                              WGL_PACK(WGL_CLR_BK), /* Element background color */
                              WGL_PACK(& t_color_elem)));

    t_img_elem.h_normal            = NULL_HANDLE;
    t_img_elem.h_disable           = NULL_HANDLE;
    t_img_elem.h_highlight         = PRG_LB_IMG_SCROLL_BAR;
    t_img_elem.h_highlight_unfocus = NULL_HANDLE;
    t_img_elem.h_pushed            = NULL_HANDLE;
    t_img_elem.h_selected          = NULL_HANDLE;
    t_img_elem.h_selected_disable  = NULL_HANDLE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE, /* Element background image */
                              WGL_PACK(& t_img_elem),
                              NULL));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_prg_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_prg_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_prg_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_prg_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_prg_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_prg_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_prg_lst_col_bk);

    for (ui2_i = 0; ui2_i < PRG_LB_COL_NUM; ui2_i ++ )
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2 (ui2_i, WGL_CLR_BK), /* Column background color */
                                  WGL_PACK (& t_color_elem)));
    }

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_prg_lst_col_date_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_prg_lst_col_date_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_prg_lst_col_date_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_prg_lst_col_date_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_prg_lst_col_date_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_prg_lst_col_date_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_prg_lst_col_date_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (0, WGL_CLR_TEXT), /* Date text color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_prg_lst_col_time_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_prg_lst_col_time_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_prg_lst_col_time_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_prg_lst_col_time_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_prg_lst_col_time_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_prg_lst_col_time_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_prg_lst_col_time_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (1, WGL_CLR_TEXT), /* Time text color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_prg_lst_col_title_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_prg_lst_col_title_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_prg_lst_col_title_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_prg_lst_col_title_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_prg_lst_col_title_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_prg_lst_col_title_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_prg_lst_col_title_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (2, WGL_CLR_TEXT), /* Title text color */
                              WGL_PACK (& t_color_elem)));

    /* Set long text scroll effect */
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 1;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = EPG_LONG_TXT_SCRL_DELAY;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                              WGL_PACK (& t_hlt_elem_effect),
                              NULL));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_surf_lst
 *
 * Description: This function creates a surfing list to display channel no.
 *              and channel name in vertical style.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_surf_lst (VOID)
{
    UINT16                      ui2_i;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[2];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_LB_KEY_MAP_T            t_key_map;
    WGL_LB_TITLE_INFO_T         t_title_info;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_IMG_INFO_T              t_img_info;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;

    /* channel no. */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = SURF_LB_COL_NO_ALIGN;
    at_cols[0].ui2_max_text_len = EPG_CHN_NO_MAX_LEN;
    at_cols[0].ui2_width        = (UINT16)SURF_LB_COL_NO_W;

    /* channel name */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = SURF_LB_COL_NAME_ALIGN;
    at_cols[1].ui2_max_text_len = EPG_CHN_NAME_MAX_LEN;
    at_cols[1].ui2_width        = (UINT16)SURF_LB_COL_NAME_W;

    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER
                                  | WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_NO_SCROLL
                                  | EPG_WIDGET_STYLE;

    t_lb_init.ui2_max_elem_num  = ELEM_VIEW_SIZE;
    t_lb_init.ui2_elem_size     = (UINT16)SURF_LB_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)SURF_LB_X,
                      (INT32)SURF_LB_Y,
                      (INT32)SURF_LB_W,
                      (INT32)SURF_LB_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_LIST_BOX,
                                     WGL_CONTENT_LIST_BOX_DEF,
                                     WGL_BORDER_UNIFORM,
                                     &t_rect,
                                     NULL,
                                     255,
                                     & t_lb_init,
                                     NULL,
                                     & t_g_view.h_surf_lst));

    if (! ((SURF_LB_TITLE_X == 0) &&
           (SURF_LB_TITLE_Y == 0) &&
           (SURF_LB_TITLE_W == 0) &&
           (SURF_LB_TITLE_H == 0)))
    {
        /* set title info */
        SET_RECT_BY_SIZE (& t_title_info.t_rect,
                          (INT32)SURF_LB_TITLE_X,
                          (INT32)SURF_LB_TITLE_Y,
                          (INT32)SURF_LB_TITLE_W,
                          (INT32)SURF_LB_TITLE_H);

        t_title_info.ui1_align = SURF_LB_TITLE_ALIGN;

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                                  WGL_CMD_LB_SET_TITLE_INFO,
                                  WGL_PACK (& t_title_info),
                                  NULL));

        /* set title font */
        c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
        c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

        t_fnt_info.e_font_size  = SURF_LB_TITLE_FNT_SIZE;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                                  WGL_CMD_GL_SET_FONT,
                                  WGL_PACK (& t_fnt_info),
                                  NULL));
    }

    /* set font size to column no. */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = SURF_LB_COL_NO_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (0),
                              WGL_PACK (& t_fnt_info)));

    /* set font size to column name */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = SURF_LB_COL_NAME_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (1),
                              WGL_PACK (& t_fnt_info)));

    /* set border inset */
    t_inset.i4_left   = (INT32)SURF_LB_BDR_INSET_L;
    t_inset.i4_right  = (INT32)SURF_LB_BDR_INSET_R;
    t_inset.i4_top    = (INT32)SURF_LB_BDR_INSET_T;
    t_inset.i4_bottom = (INT32)SURF_LB_BDR_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_GL_SET_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = (INT32)SURF_LB_CNT_INSET_L;
    t_inset.i4_right  = (INT32)SURF_LB_CNT_INSET_R;
    t_inset.i4_top    = (INT32)SURF_LB_CNT_INSET_T;
    t_inset.i4_bottom = (INT32)SURF_LB_CNT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set element inset */
    t_inset.i4_left   = (INT32)SURF_LB_ELEM_INSET_L;
    t_inset.i4_right  = (INT32)SURF_LB_ELEM_INSET_R;
    t_inset.i4_top    = (INT32)SURF_LB_ELEM_INSET_T;
    t_inset.i4_bottom = (INT32)SURF_LB_ELEM_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_SET_ELEM_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set column no. inset */
    t_inset.i4_left   = (INT32)SURF_LB_COL_NO_INSET_L;
    t_inset.i4_right  = (INT32)SURF_LB_COL_NO_INSET_R;
    t_inset.i4_top    = (INT32)SURF_LB_COL_NO_INSET_T;
    t_inset.i4_bottom = (INT32)SURF_LB_COL_NO_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (0),
                              WGL_PACK (& t_inset)));

    /* set column name inset */
    t_inset.i4_left   = SURF_LB_COL_NAME_INSET_L;
    t_inset.i4_right  = SURF_LB_COL_NAME_INSET_R;
    t_inset.i4_top    = SURF_LB_COL_NAME_INSET_T;
    t_inset.i4_bottom = SURF_LB_COL_NAME_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (1),
                              WGL_PACK (& t_inset)));

    /* set element number to ELEM_VIEW_SIZE */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_SET_ELEM_NUM,
                              WGL_PACK(ELEM_VIEW_SIZE),
                              NULL));

    /* disable control keys */
    t_key_map.ui4_key_next      = 0;
    t_key_map.ui4_key_prev      = 0;
    t_key_map.ui4_key_select    = 0;
    t_key_map.ui4_key_page_up   = 0;
    t_key_map.ui4_key_page_down = 0;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_SET_KEY_MAP,
                              WGL_PACK (& t_key_map),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_surf_lst_bdr);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_surf_lst_bdr);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_surf_lst_bdr_hlt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_GL_SET_BDR_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* border background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_surf_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_surf_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_surf_lst_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_surf_lst_title_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_surf_lst_title_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_surf_lst_title_hlt_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_TITLE_FG), /* title text color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = SURF_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = SURF_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = SURF_LB_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_surf_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_surf_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_surf_lst_vp);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_VP_BK), /* viewport background color */
                              WGL_PACK (& t_color_info)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_surf_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_surf_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_surf_lst_elem_hlt_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_surf_lst_elem_hlt_uf_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_surf_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_surf_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_surf_lst_elem_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_SET_ELEM_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* element background color */
                              WGL_PACK (& t_color_elem)));

    t_img_elem.h_normal            = NULL_HANDLE;
    t_img_elem.h_disable           = NULL_HANDLE;
    t_img_elem.h_highlight         = SURF_LB_IMG_SCROLL_BAR;
    t_img_elem.h_highlight_unfocus = NULL_HANDLE;
    t_img_elem.h_pushed            = NULL_HANDLE;
    t_img_elem.h_selected          = NULL_HANDLE;
    t_img_elem.h_selected_disable  = NULL_HANDLE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                              WGL_PACK (& t_img_elem), /* element image */
                              NULL));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_surf_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_surf_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_surf_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_surf_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_surf_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_surf_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_surf_lst_col_bk);

    for (ui2_i = 0; ui2_i < 2; ui2_i ++ )
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2 (ui2_i, WGL_CLR_BK), /* columns background color */
                                  WGL_PACK (& t_color_elem)));
    }

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_surf_lst_col_no_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_surf_lst_col_no_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_surf_lst_col_no_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_surf_lst_col_no_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_surf_lst_col_no_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_surf_lst_col_no_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_surf_lst_col_no_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (0, WGL_CLR_TEXT), /* channel no. text color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_surf_lst_col_name_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_surf_lst_col_name_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_surf_lst_col_name_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_surf_lst_col_name_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_surf_lst_col_name_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_surf_lst_col_name_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_surf_lst_col_name_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (1, WGL_CLR_TEXT), /* channel name text color */
                              WGL_PACK (& t_color_elem)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_desc_lst
 *
 * Description: This function creates a description list to display time details
 *              and TV-rating.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_desc_lst (VOID)
{
    UINT16                      ui2_i;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[2];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_IMG_INFO_T              t_img_info;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;

    /* time duration */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = DESC_LB_COL_TIME_ALIGN;
    at_cols[0].ui2_max_text_len = 50;
    at_cols[0].ui2_width        = (UINT16)DESC_LB_COL_TIME_W;

    /* content advisory */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = DESC_LB_COL_CA_ALIGN;
    at_cols[1].ui2_max_text_len = 32;
    at_cols[1].ui2_width        = (UINT16)DESC_LB_COL_CA_W;

    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT | WGL_STL_LB_FIXED_ELEM_NUM | EPG_WIDGET_STYLE;
    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = (UINT16)DESC_LB_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)DESC_LB_X,
                      (INT32)DESC_LB_Y,
                      (INT32)DESC_LB_W,
                      (INT32)DESC_LB_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_desc_frm,
                                     HT_WGL_WIDGET_LIST_BOX,
                                     WGL_CONTENT_LIST_BOX_DEF,
                                     WGL_BORDER_TRANSP,
                                     &t_rect,
                                     NULL,
                                     255,
                                     & t_lb_init,
                                     NULL,
                                     & t_g_view.h_desc_lst));

    /* set font size to column time */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = DESC_LB_COL_TIME_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (0),
                              WGL_PACK (& t_fnt_info)));

    /* set font size to column ca */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = DESC_LB_COL_CA_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (1),
                              WGL_PACK (& t_fnt_info)));

    /* set content inset */
    t_inset.i4_left   = (INT32)DESC_LB_CNT_INSET_L;
    t_inset.i4_right  = (INT32)DESC_LB_CNT_INSET_R;
    t_inset.i4_top    = (INT32)DESC_LB_CNT_INSET_T;
    t_inset.i4_bottom = (INT32)DESC_LB_CNT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_LB_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set element inset */
    t_inset.i4_left   = (INT32)DESC_LB_ELEM_INSET_L;
    t_inset.i4_right  = (INT32)DESC_LB_ELEM_INSET_R;
    t_inset.i4_top    = (INT32)DESC_LB_ELEM_INSET_T;
    t_inset.i4_bottom = (INT32)DESC_LB_ELEM_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_LB_SET_ELEM_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set column time inset */
    t_inset.i4_left   = (INT32)DESC_LB_COL_TIME_INSET_L;
    t_inset.i4_right  = (INT32)DESC_LB_COL_TIME_INSET_R;
    t_inset.i4_top    = (INT32)DESC_LB_COL_TIME_INSET_T;
    t_inset.i4_bottom = (INT32)DESC_LB_COL_TIME_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (0),
                              WGL_PACK (& t_inset)));

    /* set column conent advisory inset */
    t_inset.i4_left   = (INT32)DESC_LB_COL_CA_INSET_L;
    t_inset.i4_right  = (INT32)DESC_LB_COL_CA_INSET_R;
    t_inset.i4_top    = (INT32)DESC_LB_COL_CA_INSET_T;
    t_inset.i4_bottom = (INT32)DESC_LB_COL_CA_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (1),
                              WGL_PACK (& t_inset)));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_desc_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_desc_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_desc_lst_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = DESC_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = DESC_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = DESC_LB_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_desc_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_desc_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_desc_lst_vp);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_VP_BK), /* viewport background color */
                              WGL_PACK (& t_color_info)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_desc_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_desc_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_desc_lst_elem_hlt_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_desc_lst_elem_hlt_uf_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_desc_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_desc_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_desc_lst_elem_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_LB_SET_ELEM_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* element background color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_desc_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_desc_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_desc_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_desc_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_desc_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_desc_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_desc_lst_col_bk);

    for (ui2_i = 0; ui2_i < 2; ui2_i ++ )
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2 (ui2_i, WGL_CLR_BK), /* columns background color */
                                  WGL_PACK (& t_color_elem)));
    }

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_desc_lst_col_time_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_desc_lst_col_time_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_desc_lst_col_time_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_desc_lst_col_time_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_desc_lst_col_time_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_desc_lst_col_time_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_desc_lst_col_time_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (0, WGL_CLR_TEXT), /* time text color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_desc_lst_col_ca_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_desc_lst_col_ca_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_desc_lst_col_ca_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_desc_lst_col_ca_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_desc_lst_col_ca_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_desc_lst_col_ca_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_desc_lst_col_ca_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (1, WGL_CLR_TEXT), /* ca text color */
                              WGL_PACK (& t_color_elem)));

    /* Set long text scroll effect */
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_FORCE_SCRL_UNFOCUS;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 1;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = EPG_LONG_TXT_SCRL_DELAY;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                              WGL_PACK (& t_hlt_elem_effect),
                              NULL));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_icon_lst
 *
 * Description: This function creates a icon list to display lock and cc icons.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_icon_lst (VOID)
{
    UINT16                      ui2_i;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[2];
    WGL_INSET_T                 t_inset;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_IMG_INFO_T              t_img_info;

    /* lock icon */
    at_cols[0].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[0].ui1_align        = ICON_LB_COL_LOCK_ALIGN;
    at_cols[0].ui2_width        = (UINT16)ICON_LB_COL_LOCK_W;

    /* cc icon */
    at_cols[1].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[1].ui1_align        = ICON_LB_COL_CC_ALIGN;
    at_cols[1].ui2_width        = (UINT16)ICON_LB_COL_CC_W;

    t_lb_init.ui4_style         = WGL_STL_LB_FIXED_ELEM_NUM | EPG_WIDGET_STYLE;
    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = (UINT16)DESC_LB_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)ICON_LB_X,
                      (INT32)ICON_LB_Y,
                      (INT32)ICON_LB_W,
                      (INT32)ICON_LB_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_desc_frm,
                                     HT_WGL_WIDGET_LIST_BOX,
                                     WGL_CONTENT_LIST_BOX_DEF,
                                     WGL_BORDER_TRANSP,
                                     & t_rect,
                                     NULL,
                                     255,
                                     & t_lb_init,
                                     NULL,
                                     & t_g_view.h_icon_lst));

    /* set content inset */
    t_inset.i4_left   = ICON_LB_CNT_INSET_L;
    t_inset.i4_right  = ICON_LB_CNT_INSET_R;
    t_inset.i4_top    = ICON_LB_CNT_INSET_T;
    t_inset.i4_bottom = ICON_LB_CNT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_icon_lst,
                              WGL_CMD_LB_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set element inset */
    t_inset.i4_left   = ICON_LB_ELEM_INSET_L;
    t_inset.i4_right  = ICON_LB_ELEM_INSET_R;
    t_inset.i4_top    = ICON_LB_ELEM_INSET_T;
    t_inset.i4_bottom = ICON_LB_ELEM_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_icon_lst,
                              WGL_CMD_LB_SET_ELEM_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set column lock inset */
    t_inset.i4_left   = ICON_LB_COL_LOCK_INSET_L;
    t_inset.i4_right  = ICON_LB_COL_LOCK_INSET_R;
    t_inset.i4_top    = ICON_LB_COL_LOCK_INSET_T;
    t_inset.i4_bottom = ICON_LB_COL_LOCK_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_icon_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (0),
                              WGL_PACK (& t_inset)));

    /* set column cc inset */
    t_inset.i4_left   = ICON_LB_COL_CC_INSET_L;
    t_inset.i4_right  = ICON_LB_COL_CC_INSET_R;
    t_inset.i4_top    = ICON_LB_COL_CC_INSET_T;
    t_inset.i4_bottom = ICON_LB_COL_CC_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_icon_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (1),
                              WGL_PACK (& t_inset)));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_icon_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_icon_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_icon_lst_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_icon_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = ICON_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = ICON_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = ICON_LB_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_icon_lst,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_icon_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_icon_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_icon_lst_vp);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_icon_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_VP_BK), /* viewport background */
                              WGL_PACK (& t_color_info)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_icon_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_icon_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_icon_lst_elem_hlt_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_icon_lst_elem_hlt_uf_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_icon_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_icon_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_icon_lst_elem_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_icon_lst,
                              WGL_CMD_LB_SET_ELEM_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* element background color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_icon_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_icon_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_icon_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_icon_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_icon_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_icon_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_icon_lst_col_bk);

    for (ui2_i = 0; ui2_i < 2; ui2_i ++ )
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_icon_lst,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2 (ui2_i, WGL_CLR_BK), /* columns background color */
                                  WGL_PACK (& t_color_elem)));
    }

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_help_lst
 *
 * Description: This function creates a help list to show hints.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_help_lst (VOID)
{
    UINT16                      ui2_i;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[8];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_IMG_INFO_T              t_img_info;

    /* image */
    for (ui2_i = HELP_LB_IMG_START_IDX; ui2_i < 8; ui2_i += 2)
    {
        at_cols[ui2_i].e_col_type        = LB_COL_TYPE_IMG;
        at_cols[ui2_i].ui1_align         = HELP_LB_COL_IMG_ALIGN;
        at_cols[ui2_i].ui2_width         = (UINT16)HELP_LB_COL_IMG_W;
    }

    /* text */
    for (ui2_i = HELP_LB_TXT_START_IDX; ui2_i < 8; ui2_i += 2)
    {
        at_cols[ui2_i].e_col_type        = LB_COL_TYPE_TEXT;
        at_cols[ui2_i].ui1_align         = HELP_LB_COL_TEXT_ALIGN;
        at_cols[ui2_i].ui2_max_text_len  = 20;
        at_cols[ui2_i].ui2_width         = (UINT16)HELP_LB_COL_TEXT_W;
    }

    t_lb_init.ui4_style         = WGL_STL_LB_FIXED_ELEM_NUM | EPG_WIDGET_STYLE;
    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = (UINT16)HELP_LB_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 8;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      (INT32)HELP_LB_X,
                      (INT32)HELP_LB_Y,
                      (INT32)HELP_LB_W,
                      (INT32)HELP_LB_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_LIST_BOX,
                                     WGL_CONTENT_LIST_BOX_DEF,
                                     WGL_BORDER_TRANSP,
                                     &t_rect,
                                     NULL,
                                     255,
                                     & t_lb_init,
                                     NULL,
                                     & t_g_view.h_help_lst));

    /* set content inset */
    t_inset.i4_left   = HELP_LB_CNT_INSET_L;
    t_inset.i4_right  = HELP_LB_CNT_INSET_R;
    t_inset.i4_top    = HELP_LB_CNT_INSET_T;
    t_inset.i4_bottom = HELP_LB_CNT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set element inset */
    t_inset.i4_left   = HELP_LB_ELEM_INSET_L;
    t_inset.i4_right  = HELP_LB_ELEM_INSET_R;
    t_inset.i4_top    = HELP_LB_ELEM_INSET_T;
    t_inset.i4_bottom = HELP_LB_ELEM_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_ELEM_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set font size to text columns */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = HELP_LB_COL_TEXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    for (ui2_i = HELP_LB_TXT_START_IDX; ui2_i < 8; ui2_i += 2)
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                                  WGL_CMD_LB_SET_COL_FONT,
                                  WGL_PACK (ui2_i),
                                  WGL_PACK (& t_fnt_info)));
    }

    /* set inset for column images */
    t_inset.i4_left   = HELP_LB_COL_IMG_INSET_L;
    t_inset.i4_right  = HELP_LB_COL_IMG_INSET_R;
    t_inset.i4_top    = HELP_LB_COL_IMG_INSET_T;
    t_inset.i4_bottom = HELP_LB_COL_IMG_INSET_B;

    for (ui2_i = HELP_LB_IMG_START_IDX; ui2_i < 8; ui2_i += 2)
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                                  WGL_CMD_LB_SET_COL_INSET,
                                  WGL_PACK (ui2_i),
                                  WGL_PACK (& t_inset)));
    }

    /* set inset for column text */
    t_inset.i4_left   = HELP_LB_COL_TEXT_INSET_L;
    t_inset.i4_right  = HELP_LB_COL_TEXT_INSET_R;
    t_inset.i4_top    = HELP_LB_COL_TEXT_INSET_T;
    t_inset.i4_bottom = HELP_LB_COL_TEXT_INSET_B;

    for (ui2_i = HELP_LB_TXT_START_IDX; ui2_i < 8; ui2_i += 2)
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                                  WGL_CMD_LB_SET_COL_INSET,
                                  WGL_PACK (ui2_i),
                                  WGL_PACK (& t_inset)));
    }

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_help_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_help_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_help_lst_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = HELP_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = HELP_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = HELP_LB_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_help_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_help_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_help_lst_vp);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_VP_BK), /* viewport background color */
                              WGL_PACK (& t_color_info)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_help_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_help_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_help_lst_elem_hlt_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_help_lst_elem_hlt_uf_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_help_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_help_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_help_lst_elem_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_ELEM_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* element background color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_help_lst_col_bk);

    for (ui2_i = 0; ui2_i < 8; ui2_i ++ )
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2 (ui2_i, WGL_CLR_BK), /* columns background color */
                                  WGL_PACK (& t_color_elem)));
    }

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_help_lst_col_prev_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_help_lst_col_prev_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_help_lst_col_prev_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_help_lst_col_prev_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_help_lst_col_prev_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_help_lst_col_prev_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_help_lst_col_prev_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (HELP_LB_BTN_RED_TXT_IDX, WGL_CLR_TEXT), /* previous day text color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_help_lst_col_next_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_help_lst_col_next_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_help_lst_col_next_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_help_lst_col_next_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_help_lst_col_next_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_help_lst_col_next_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_help_lst_col_next_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (HELP_LB_BTN_GREEN_TXT_IDX, WGL_CLR_TEXT), /* next day text color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_help_lst_col_up_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_help_lst_col_up_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_help_lst_col_up_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_help_lst_col_up_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_help_lst_col_up_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_help_lst_col_up_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_help_lst_col_up_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (HELP_LB_BTN_YELLOW_TXT_IDX, WGL_CLR_TEXT), /* page up text color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_help_lst_col_down_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_help_lst_col_down_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_help_lst_col_down_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_help_lst_col_down_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_help_lst_col_down_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_help_lst_col_down_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_help_lst_col_down_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (HELP_LB_BTN_BLUE_TXT_IDX, WGL_CLR_TEXT), /* page down text color */
                              WGL_PACK (& t_color_elem)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_time_txt
 *
 * Description: This function creates a time text widget to display current
 *              time.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_time_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_IMG_INFO_T              t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)TIME_TXT_X,
                      (INT32)TIME_TXT_Y,
                      (INT32)TIME_TXT_W,
                      (INT32)TIME_TXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) (WGL_STL_TEXT_MAX_128 |
                                              EPG_WIDGET_STYLE),
                                     NULL,
                                     & t_g_view.h_time_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = TIME_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_time_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = (INT32)TIME_TXT_INSET_L;
    t_inset.i4_right  = (INT32)TIME_TXT_INSET_R;
    t_inset.i4_top    = (INT32)TIME_TXT_INSET_T;
    t_inset.i4_bottom = (INT32)TIME_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_time_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_time_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (TIME_TXT_ALIGN),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_time_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_time_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_time_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_time_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = TIME_TXT_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = TIME_TXT_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = TIME_TXT_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_time_txt,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_time_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_time_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_time_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_time_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_retrieve_txt
 *
 * Description: This function creates a retrieving text to display message
 *              while retrieving event data.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_retrieve_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)RETRIEVE_TXT_X,
                      (INT32)RETRIEVE_TXT_Y,
                      (INT32)RETRIEVE_TXT_W,
                      (INT32)RETRIEVE_TXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MAX_128 |
                                             WGL_STL_GL_NO_BK),
                                     NULL,
                                     & t_g_view.h_retrieve_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = RETRIEVE_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_retrieve_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK(& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = (INT32)RETRIEVE_TXT_INSET_L;
    t_inset.i4_right  = (INT32)RETRIEVE_TXT_INSET_R;
    t_inset.i4_top    = (INT32)RETRIEVE_TXT_INSET_T;
    t_inset.i4_bottom = (INT32)RETRIEVE_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_retrieve_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_retrieve_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (RETRIEVE_TXT_ALIGN),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_retrieve_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_retrieve_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_retrieve_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_retrieve_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_retrieve_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_retrieve_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_retrieve_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_retrieve_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_dci_hts
 *
 * Description: This function creates a DCI hyper text to display the direct
 *              channel input.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_dci_hts (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_HTS_INIT_T              t_init;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;

    WGL_HTS_FONT_REG_INFO_T     at_font_reg_tbl[] =
                                {
                                    /* default font */
                                    {
                                        SN_FONT_DEFAULT,
                                        FE_FNT_SIZE_SMALL,
                                        0,
                                        0
                                    },
                                    {
                                        SN_FONT_DEFAULT,
                                        FE_FNT_SIZE_MEDIUM,
                                        0,
                                        0
                                    },
                                    {
                                        SN_FONT_DEFAULT,
                                        FE_FNT_SIZE_LARGE,
                                        0,
                                        0
                                    },

                                    /* EPG specific font */
                                    {
                                        EPG_FONT_NAME,
                                        FE_FNT_SIZE_SMALL,
                                        0,
                                        0
                                    },
                                    {
                                        EPG_FONT_NAME,
                                        FE_FNT_SIZE_MEDIUM,
                                        0,
                                        0
                                    },
                                    {
                                        EPG_FONT_NAME,
                                        FE_FNT_SIZE_LARGE,
                                        0,
                                        0
                                    }
                                };

    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = at_font_reg_tbl;
    t_init.ui2_num_reg_font  = (UINT16)(sizeof (at_font_reg_tbl) / sizeof (WGL_HTS_FONT_REG_INFO_T));

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, t_g_view.s_font_name);
    t_init.t_font_info_dft.e_font_size  = DCI_HTS_FNT_SIZE;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)DCI_HTS_X,
                      (INT32)DCI_HTS_Y,
                      (INT32)DCI_HTS_W,
                      (INT32)DCI_HTS_H);

    /* create hyper text widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     & t_g_view.h_dci_hts));

    /* set content inset */
    t_inset.i4_left   = DCI_HTS_INSET_L;
    t_inset.i4_right  = DCI_HTS_INSET_R;
    t_inset.i4_top    = DCI_HTS_INSET_T;
    t_inset.i4_bottom = DCI_HTS_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_dci_hts,
                              WGL_CMD_HTS_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set justification */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_dci_hts,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_CENTER),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_dci_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_dci_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_dci_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_dci_hts,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_dci_hts,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_HTS_VP_BK), /* viewport color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_video_txt
 *
 * Description: This function creates a video text to display system messages.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_video_txt (VOID)
{
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_INSET_T                 t_inset;
    WGL_COLOR_INFO_T            t_color_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)VIDEO_TXT_X,
                      (INT32)VIDEO_TXT_Y,
                      (INT32)VIDEO_TXT_W,
                      (INT32)VIDEO_TXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_video_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MULTILINE | WGL_STL_GL_NO_IMG_UI),
                                     NULL,
                                     & t_g_view.h_video_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = VIDEO_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_video_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = VIDEO_TXT_INSET_L;
    t_inset.i4_right  = VIDEO_TXT_INSET_R;
    t_inset.i4_top    = VIDEO_TXT_INSET_T;
    t_inset.i4_bottom = VIDEO_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_video_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_video_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (VIDEO_TXT_ALIGN),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_video_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_video_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_video_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_video_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_video_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_video_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_video_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_video_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_prg_txt
 *
 * Description: This function creates a program text to display "No program
 *              data" if there is no event available.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_prg_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)PRG_TXT_X,
                      (INT32)PRG_TXT_Y,
                      (INT32)PRG_TXT_W,
                      (INT32)PRG_TXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_GL_NO_BK),
                                     NULL,
                                     & t_g_view.h_prg_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = PRG_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK(& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = PRG_TXT_INSET_L;
    t_inset.i4_right  = PRG_TXT_INSET_R;
    t_inset.i4_top    = PRG_TXT_INSET_T;
    t_inset.i4_bottom = PRG_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (PRG_TXT_ALIGN),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_prg_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_prg_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_prg_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_prg_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_prg_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_prg_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_prg_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_desc_txt
 *
 * Description: This function creates a description text to display program
 *              details.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_desc_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_IMG_INFO_T              t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)DESC_TXT_X,
                      (INT32)DESC_TXT_Y,
                      (INT32)DESC_TXT_W,
                      (INT32)DESC_TXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_desc_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MULTILINE |
                                             WGL_STL_TEXT_MAX_4096  |
                                             WGL_STL_TEXT_MAX_DIS_5_LINE |
                                             EPG_WIDGET_STYLE),
                                     NULL,
                                     & t_g_view.h_desc_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = DESC_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = (INT32)DESC_TXT_INSET_L;
    t_inset.i4_right  = (INT32)DESC_TXT_INSET_R;
    t_inset.i4_top    = (INT32)DESC_TXT_INSET_T;
    t_inset.i4_bottom = (INT32)DESC_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (DESC_TXT_ALIGN),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) DESC_TXT_LINE_GAPS),
                              NULL));

    /* set page scrolling style */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_TEXT_SET_PAGE_SCROL,
                              WGL_PACK(WGL_TEXT_PS_TYPE_REPLACE_ALL),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_desc_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_desc_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_desc_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = DESC_TXT_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = DESC_TXT_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = DESC_TXT_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_desc_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_page_txt
 *
 * Description: This function creates a page text to display page index of
 *              the program details.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_page_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_IMG_INFO_T              t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)PAGE_TXT_X,
                      (INT32)PAGE_TXT_Y,
                      (INT32)PAGE_TXT_W,
                      (INT32)PAGE_TXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_desc_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_SMART_CUT | EPG_WIDGET_STYLE),
                                     NULL,
                                     & t_g_view.h_page_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = PAGE_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_page_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = (INT32)PAGE_TXT_INSET_L;
    t_inset.i4_right  = (INT32)PAGE_TXT_INSET_R;
    t_inset.i4_top    = (INT32)PAGE_TXT_INSET_T;
    t_inset.i4_bottom = (INT32)PAGE_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_page_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_page_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (PAGE_TXT_ALIGN),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_page_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_page_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_page_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_page_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = PAGE_TXT_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = PAGE_TXT_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = PAGE_TXT_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_page_txt,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_page_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_page_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_page_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_page_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_passwd_txt
 *
 * Description: This function creates the password text to put on the password
 *              dialog.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_passwd_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_COLOR_INFO_T            t_color_info;
    GL_RECT_T                   t_rect;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)PASSWD_TXT_X,
                      (INT32)PASSWD_TXT_Y,
                      (INT32)PASSWD_TXT_W,
                      (INT32)PASSWD_TXT_H);

    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_passwd_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) WGL_STL_GL_NO_IMG_UI,
                                     NULL,
                                     & t_g_view.h_passwd_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = PASSWD_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = PASSWD_TXT_INSET_L;
    t_inset.i4_right  = PASSWD_TXT_INSET_R;
    t_inset.i4_top    = PASSWD_TXT_INSET_T;
    t_inset.i4_bottom = PASSWD_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK(PASSWD_TXT_ALIGN),
                              NULL));

    /* set theme */
        /* password text */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_passwd_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_passwd_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_passwd_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),   /* text background */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_passwd_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_passwd_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_passwd_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

#ifdef APP_EPG_FULL_VIDEO
/*----------------------------------------------------------------------------
 * Name: _epg_view_create_passwd_txt
 *
 * Description: This function creates the password text to put on the password
 *              dialog.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_passwd_alarm_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_COLOR_INFO_T            t_color_info;
    GL_RECT_T                   t_rect;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)PASSWD_TXT_ALARM_X,
                      (INT32)PASSWD_TXT_ALARM_Y,
                      (INT32)PASSWD_TXT_ALARM_W,
                      (INT32)PASSWD_TXT_ALARM_H);

    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_desc_bk_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) WGL_STL_GL_NO_IMG_UI,
                                     NULL,
                                     & t_g_view.h_passwd_alarm_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = PASSWD_TXT_ALARM_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_alarm_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = PASSWD_TXT_ALARM_INSET_L;
    t_inset.i4_right  = PASSWD_TXT_ALARM_INSET_R;
    t_inset.i4_top    = PASSWD_TXT_ALARM_INSET_T;
    t_inset.i4_bottom = PASSWD_TXT_ALARM_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_alarm_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_alarm_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK(PASSWD_TXT_ALARM_ALIGN),
                              NULL));

    /* set theme */
        /* password text */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_passwd_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_passwd_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_passwd_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_alarm_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),   /* text background */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_passwd_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_passwd_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_passwd_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_alarm_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    return  0;
}
#endif
/*----------------------------------------------------------------------------
 * Name: _epg_view_create_chn_txt
 *
 * Description: This function creates a channel info text to display channel
 *              no. and channel name below the video.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_chn_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_IMG_INFO_T              t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)CHN_TXT_X,
                      (INT32)CHN_TXT_Y,
                      (INT32)CHN_TXT_W,
                      (INT32)CHN_TXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) (EPG_WIDGET_STYLE |
                                              WGL_STL_TEXT_SMART_CUT),
                                     NULL,
                                     & t_g_view.h_chn_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = CHN_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = (INT32)CHN_TXT_INSET_L;
    t_inset.i4_right  = (INT32)CHN_TXT_INSET_R;
    t_inset.i4_top    = (INT32)CHN_TXT_INSET_T;
    t_inset.i4_bottom = (INT32)CHN_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (CHN_TXT_ALIGN),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_chn_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_chn_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_chn_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = CHN_TXT_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = CHN_TXT_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = CHN_TXT_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_txt,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_chn_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_chn_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_chn_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_chn_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_retrieve_icon
 *
 * Description: This function creates a icon widget to display images while
 *              retriving event data.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_retrieve_icon (VOID)
{
    WGL_INSET_T                 t_inset;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)RETRIEVE_ICON_X,
                      (INT32)RETRIEVE_ICON_Y,
                      (INT32)RETRIEVE_ICON_W,
                      (INT32)RETRIEVE_ICON_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_GL_NO_IMG_UI),
                                     NULL,
                                     & t_g_view.h_retrieve_icon));

    /* set content inset */
    t_inset.i4_left   = RETRIEVE_ICON_INSET_L;
    t_inset.i4_right  = RETRIEVE_ICON_INSET_R;
    t_inset.i4_top    = RETRIEVE_ICON_INSET_T;
    t_inset.i4_bottom = RETRIEVE_ICON_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_retrieve_icon,
                              WGL_CMD_ICON_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_retrieve_icon,
                              WGL_CMD_ICON_SET_ALIGN,
                              WGL_PACK (RETRIEVE_ICON_ALIGN),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_retrieve_icon_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_retrieve_icon_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_retrieve_icon_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_retrieve_icon,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),   /* background */
                              WGL_PACK (& t_color_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_passwd_edit
 *
 * Description: This function creates a password edit to input password.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_passwd_edit (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_EB_KEY_MAP_T            t_eb_key_map;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_IMG_INFO_T              t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)PASSWD_EDIT_X,
                      (INT32)PASSWD_EDIT_Y,
                      (INT32)PASSWD_EDIT_W,
                      (INT32)PASSWD_EDIT_H);

    /* Create widget. */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_passwd_frm,
                                     HT_WGL_WIDGET_EDIT_BOX,
                                     WGL_CONTENT_EDIT_BOX_DEF,
                                     WGL_BORDER_UNIFORM,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_EB_PASSWORD |
                                             EPG_WIDGET_STYLE),
                                     NULL,
                                     & t_g_view.h_passwd_edit));

    /* Set font size. */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = PASSWD_EDIT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_edit,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* Set border inset. */
    t_inset.i4_left   = PASSWD_EDIT_BDR_INSET_L;
    t_inset.i4_right  = PASSWD_EDIT_BDR_INSET_R;
    t_inset.i4_top    = PASSWD_EDIT_BDR_INSET_T;
    t_inset.i4_bottom = PASSWD_EDIT_BDR_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_edit,
                              WGL_CMD_GL_SET_INSET,
                              & t_inset,
                              NULL));

    /* Set content inset. */
    t_inset.i4_left   = (INT32)PASSWD_EDIT_CNT_INSET_L;
    t_inset.i4_right  = (INT32)PASSWD_EDIT_CNT_INSET_R;
    t_inset.i4_top    = (INT32)PASSWD_EDIT_CNT_INSET_T;
    t_inset.i4_bottom = (INT32)PASSWD_EDIT_CNT_INSET_T;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_edit,
                              WGL_CMD_EB_SET_CNT_INSET,
                              & t_inset,
                              NULL));

    /* Set alignment. */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_edit,
                              WGL_CMD_EB_SET_ALIGN,
                              WGL_PACK (PASSWD_EDIT_ALIGN),
                              NULL));

    /* Set input limitation. */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_edit,
                              WGL_CMD_EB_SET_INPUT_LIMIT,
                              WGL_PACK (PASSWD_EDIT_MAX_WORD_LEN+1),
                              NULL));

    /* Set key map. */
    c_memset (& t_eb_key_map, 0, sizeof (WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_enter_editing = BTN_SELECT;
    t_eb_key_map.ui4_leave_editing = BTN_EXIT;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_edit,
                              WGL_CMD_EB_SET_KEY_MAP,
                              WGL_PACK (& t_eb_key_map),
                              NULL));

    /* Set auto-edit mode. */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_edit,
                              WGL_CMD_EB_SET_EXT_ATTR,
                              WGL_PACK (WGL_EB_EA_AUTO_EDITING),
                              WGL_PACK (WGL_EB_EA_AUTO_EDITING)));

    /* Set theme. */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_passwd_edit_bdr_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_passwd_edit_bdr_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_passwd_edit_bdr_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_edit,
                              WGL_CMD_GL_SET_BDR_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Border background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_passwd_edit_cnt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_passwd_edit_cnt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_passwd_edit_cnt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_edit,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),   /* Content background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_passwd_edit_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_passwd_edit_txt_hlt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_passwd_edit_txt_hlt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_edit,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* Text color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = PASSWD_EDIT_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = PASSWD_EDIT_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = PASSWD_EDIT_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_passwd_edit,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK), /* Background image */
                              WGL_PACK(& t_img_info)));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_view_desc_txt_repaint_union
 *
 * Description: This functions paints union of following rectangles:
 *                 1. Description text
 *                 2. Page number text
 *                 3. Help list
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_desc_txt_repaint_union (VOID)
{
    INT32       i4_ret;
    GL_RECT_T   t_rect_1;
    GL_RECT_T   t_rect_2;
    GL_RECT_T   t_rect_union;
#ifndef APP_NO_COLOR_KEY
    GL_RECT_T   t_rect_3;
#endif /* APP_NO_COLOR_KEY */    

    /*
       Get union rectangles of
         1.) Description text
         2.) Page number text
    */
    i4_ret = c_wgl_get_coords (t_g_view.h_desc_txt,
                               WGL_COORDS_SCREEN,
                               & t_rect_1);
    EPG_CHK_FAIL (i4_ret, i4_ret);

    i4_ret = c_wgl_get_coords (t_g_view.h_page_txt,
                               WGL_COORDS_SCREEN,
                               & t_rect_2);
    EPG_CHK_FAIL (i4_ret, i4_ret);

    i4_ret = c_wgl_rect_union (& t_rect_union,
                               & t_rect_1,
                               & t_rect_2);
    EPG_CHK_FAIL (i4_ret, i4_ret);

#ifndef APP_NO_COLOR_KEY

    /* Get union rectangles of help listing */
    i4_ret = c_wgl_get_coords (t_g_view.h_help_lst,
                               WGL_COORDS_SCREEN,
                               & t_rect_3);
    EPG_CHK_FAIL (i4_ret, i4_ret);

    i4_ret = c_wgl_rect_union (& t_rect_union,
                               & t_rect_union,
                               & t_rect_3);
    EPG_CHK_FAIL (i4_ret, i4_ret);

#endif /* APP_NO_COLOR_KEY */

    /* Repaint */
    i4_ret = c_wgl_repaint (t_g_view.h_main_frm,
                            & t_rect_union,
                            TRUE);
    EPG_CHK_FAIL (i4_ret, i4_ret);

    return EPGR_OK;
}

#ifdef APP_EPG_THEME_SEARCH

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_type_lst
 *
 * Description: This function creates a type list to display all the event types.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_type_lst (VOID)
{
    UINT16                      ui2_i;
    UINT16                      ui2_elem_num;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_TITLE_INFO_T         t_title_info;
    WGL_LB_SCROLL_IMG_INFO_T    t_scroll_img_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_LB_KEY_MAP_T            t_key_map;
    WGL_IMG_INFO_T              t_img_info;
    WGL_LB_ELEM_DATA_T          at_elem_data[TYPE_LB_ELEM_NUM_MAX];
    ISO_3166_COUNT_T            s3166_country;

    /* Event type */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = TYPE_LB_COL_ALIGN;
    at_cols[0].ui2_max_text_len = 50;
    at_cols[0].ui2_width        = (UINT16)TYPE_LB_COL_W;
    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT |
                                  EPG_WIDGET_STYLE;
    t_lb_init.ui2_max_elem_num  = TYPE_LB_ELEM_NUM_MAX;
    t_lb_init.ui2_elem_size     = (UINT16)TYPE_LB_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)TYPE_LB_X,
                      (INT32)TYPE_LB_Y,
                      (INT32)TYPE_LB_W,
                      (INT32)TYPE_LB_H);

    /* Create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_LIST_BOX,
                                     WGL_CONTENT_LIST_BOX_DEF,
                                     WGL_BORDER_TRANSP,
                                     &t_rect,
                                     NULL,
                                     255,
                                     & t_lb_init,
                                     NULL,
                                     & t_g_view.h_type_lst));

    if (! ((TYPE_LB_TITLE_X == 0) &&
           (TYPE_LB_TITLE_Y == 0) &&
           (TYPE_LB_TITLE_W == 0) &&
           (TYPE_LB_TITLE_H == 0)))
    {
        /* Set title info. */
        SET_RECT_BY_SIZE (& t_title_info.t_rect,
                          (INT32)TYPE_LB_TITLE_X,
                          (INT32)TYPE_LB_TITLE_Y,
                          (INT32)TYPE_LB_TITLE_W,
                          (INT32)TYPE_LB_TITLE_H);

        t_title_info.ui1_align = TYPE_LB_TITLE_ALIGN;

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                                  WGL_CMD_LB_SET_TITLE_INFO,
                                  WGL_PACK (& t_title_info),
                                  NULL));

        /* Set title font. */
        c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
        c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

        t_fnt_info.e_font_size  = TYPE_LB_TITLE_FNT_SIZE;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                                  WGL_CMD_GL_SET_FONT,
                                  WGL_PACK (& t_fnt_info),
                                  NULL));

        /* Set title text. */
        RET_ON_ERR (epg_view_type_lst_set_title (EPG_MLM (MLM_EPG_KEY_EVT_TYPE_TITLE)));
    }

    /* Set font data. */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = TYPE_LB_COL_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (0),
                              WGL_PACK (& t_fnt_info)));


    /* Set content inset. */
    t_inset.i4_left   = (INT32)TYPE_LB_CNT_INSET_L;
    t_inset.i4_right  = (INT32)TYPE_LB_CNT_INSET_R;
    t_inset.i4_top    = (INT32)TYPE_LB_CNT_INSET_T;
    t_inset.i4_bottom = (INT32)TYPE_LB_CNT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_LB_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* Set element inset. */
    t_inset.i4_left   = (INT32)TYPE_LB_ELEM_INSET_L;
    t_inset.i4_right  = (INT32)TYPE_LB_ELEM_INSET_R;
    t_inset.i4_top    = (INT32)TYPE_LB_ELEM_INSET_T;
    t_inset.i4_bottom = (INT32)TYPE_LB_ELEM_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_LB_SET_ELEM_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* Set column inset. */
    t_inset.i4_left   = (INT32)TYPE_LB_COL_INSET_L;
    t_inset.i4_right  = (INT32)TYPE_LB_COL_INSET_R;
    t_inset.i4_top    = (INT32)TYPE_LB_COL_INSET_T;
    t_inset.i4_bottom = (INT32)TYPE_LB_COL_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (0),
                              WGL_PACK (& t_inset)));

    /* Set element data. */
    ui2_elem_num = 12;

    if (a_cfg_get_country (s3166_country) == APP_CFGR_OK)
    {
        if ((c_strncmp (s3166_country, s3166_app_cfg_count_aus, ISO_3166_COUNT_LEN) == 0) || /* Australia */
            (c_strncmp (s3166_country, s3166_app_cfg_count_nzl, ISO_3166_COUNT_LEN) == 0))   /* New Zealand */
        {
            ui2_elem_num = 14;
        }
        else /* Other countries */
        {
            ui2_elem_num = 12;
        }
    }

    for (ui2_i = 0; ui2_i < ui2_elem_num; ui2_i ++)
    {
        /* Allocate items. */
        at_elem_data[ui2_i].at_items = (WGL_LB_ITEM_DATA_T*) c_mem_alloc (sizeof(WGL_LB_ITEM_DATA_T));

        if (at_elem_data[ui2_i].at_items == NULL) /* Out of memory */
        {
            DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

            return EPGR_OUT_OF_MEM;
        }

#ifdef APP_DVBT_OCEANIA_SUPPORT

        if ((c_strncmp (s3166_country, s3166_app_cfg_count_aus, ISO_3166_COUNT_LEN) == 0) || /* Australia */
            (c_strncmp (s3166_country, s3166_app_cfg_count_nzl, ISO_3166_COUNT_LEN) == 0))   /* New Zealand */
        {
            at_elem_data[ui2_i].at_items[0].pw2s_text = EPG_MLM ((UINT16)(MLM_EPG_KEY_EVT_TYPE_AUS_ALL + ui2_i));
        }
        else /* Other countries */
        {
            at_elem_data[ui2_i].at_items[0].pw2s_text = EPG_MLM ((UINT16)(MLM_EPG_KEY_EVT_TYPE_ALL + ui2_i));
        }

#else /* #ifndef APP_DVBT_OCEANIA_SUPPORT */

        at_elem_data[ui2_i].at_items[0].pw2s_text = EPG_MLM ((UINT16)(MLM_EPG_KEY_EVT_TYPE_ALL + ui2_i));

#endif /* APP_DVBT_OCEANIA_SUPPORT */
    }

    /* Set element number. */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_LB_SET_ELEM_NUM,
                              WGL_PACK (ui2_elem_num),
                              NULL));

    /* Set element data. */
    RET_ON_ERR (epg_view_type_lst_set_elems (0, (UINT16)(ui2_elem_num - 1), at_elem_data));

    /* Free element data. */
    for (ui2_i = 0; ui2_i < ui2_elem_num; ui2_i ++)
    {
        if (at_elem_data[ui2_i].at_items != NULL)
        {
            c_mem_free (at_elem_data[ui2_i].at_items);
        }
    }

    /* Set scrolling images. */
    t_scroll_img_info.t_location_up.i4_x     = (INT32)TYPE_LB_IMG_SCROLL_UP_X;
    t_scroll_img_info.t_location_up.i4_y     = (INT32)TYPE_LB_IMG_SCROLL_UP_Y;
    t_scroll_img_info.t_location_down.i4_x   = (INT32)TYPE_LB_IMG_SCROLL_DOWN_X;
    t_scroll_img_info.t_location_down.i4_y   = (INT32)TYPE_LB_IMG_SCROLL_DOWN_Y;

    t_scroll_img_info.h_img_scr_up_on        = h_g_epg_img_arrow_left;
    t_scroll_img_info.h_img_scr_up_off       = h_g_epg_img_arrow_left;
    t_scroll_img_info.h_img_scr_down_on      = h_g_epg_img_arrow_right;
    t_scroll_img_info.h_img_scr_down_off     = h_g_epg_img_arrow_right;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_LB_EXT_SET_PAGING_IMAGE,
                              WGL_PACK (& t_scroll_img_info),
                              WGL_PACK (FALSE)));

    /* Set control keys. */
    t_key_map.ui4_key_next      = BTN_CURSOR_RIGHT;
    t_key_map.ui4_key_prev      = BTN_CURSOR_LEFT;
    t_key_map.ui4_key_select    = 0;
    t_key_map.ui4_key_page_up   = 0;
    t_key_map.ui4_key_page_down = 0;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_LB_SET_KEY_MAP,
                              WGL_PACK (& t_key_map),
                              NULL));

    /* Set theme. */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_type_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_type_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_type_lst_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = TYPE_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = TYPE_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = TYPE_LB_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* Background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_type_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_type_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_type_lst_vp);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_VP_BK), /* Viewport background color */
                              WGL_PACK (& t_color_info)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_type_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_type_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_type_lst_elem_hlt_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_type_lst_elem_hlt_uf_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_type_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_type_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_type_lst_elem_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_LB_SET_ELEM_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Element background color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_type_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_type_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_type_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_type_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_type_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_type_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_type_lst_col_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (0, WGL_CLR_BK), /* Columns background color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_type_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_type_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_type_lst_col_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_type_lst_col_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_type_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_type_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_type_lst_col_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (0, WGL_CLR_TEXT), /* Column text color */
                              WGL_PACK (& t_color_elem)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_type_lst_title_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_type_lst_title_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_type_lst_title_hlt_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_type_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_TITLE_FG), /* title text color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _epg_view_create_subtype_lst
 *
 * Description: This function creates a subtype list to display all the event types.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_view_create_subtype_lst (VOID)
{
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_TITLE_INFO_T         t_title_info;
    WGL_LB_SCROLL_IMG_INFO_T    t_scroll_img_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_LB_KEY_MAP_T            t_key_map;
    WGL_IMG_INFO_T              t_img_info;
    WGL_LB_ELEM_DATA_T          at_elem_data[1];

    /* Event subtype. */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = SUBTYPE_LB_COL_ALIGN;
    at_cols[0].ui2_max_text_len = 50;
    at_cols[0].ui2_width        = (UINT16)SUBTYPE_LB_COL_W;
    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT |
                                  EPG_WIDGET_STYLE;
    t_lb_init.ui2_max_elem_num  = SUBTYPE_LB_ELEM_NUM_MAX;
    t_lb_init.ui2_elem_size     = (UINT16)SUBTYPE_LB_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)SUBTYPE_LB_X,
                      (INT32)SUBTYPE_LB_Y,
                      (INT32)SUBTYPE_LB_W,
                      (INT32)SUBTYPE_LB_H);

    /* Create widget. */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_LIST_BOX,
                                     WGL_CONTENT_LIST_BOX_DEF,
                                     WGL_BORDER_TRANSP,
                                     &t_rect,
                                     NULL,
                                     255,
                                     & t_lb_init,
                                     NULL,
                                     & t_g_view.h_subtype_lst));

    if (! ((SUBTYPE_LB_TITLE_X == 0) &&
           (SUBTYPE_LB_TITLE_Y == 0) &&
           (SUBTYPE_LB_TITLE_W == 0) &&
           (SUBTYPE_LB_TITLE_H == 0)))
    {
        /* Set title info. */
        SET_RECT_BY_SIZE (& t_title_info.t_rect,
                          (INT32)SUBTYPE_LB_TITLE_X,
                          (INT32)SUBTYPE_LB_TITLE_Y,
                          (INT32)SUBTYPE_LB_TITLE_W,
                          (INT32)SUBTYPE_LB_TITLE_H);

        t_title_info.ui1_align = SUBTYPE_LB_TITLE_ALIGN;

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                                  WGL_CMD_LB_SET_TITLE_INFO,
                                  WGL_PACK (& t_title_info),
                                  NULL));

        /* Set title font. */
        c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
        c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

        t_fnt_info.e_font_size  = SUBTYPE_LB_TITLE_FNT_SIZE;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                                  WGL_CMD_GL_SET_FONT,
                                  WGL_PACK (& t_fnt_info),
                                  NULL));

        /* Set title text. */
        RET_ON_ERR (epg_view_subtype_lst_set_title (EPG_MLM (MLM_EPG_KEY_EVT_SUBTYPE_TITLE)));
    }

    /* Set font data. */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = TYPE_LB_COL_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (0),
                              WGL_PACK (& t_fnt_info)));


    /* Set content inset. */
    t_inset.i4_left   = (INT32)SUBTYPE_LB_CNT_INSET_L;
    t_inset.i4_right  = (INT32)SUBTYPE_LB_CNT_INSET_R;
    t_inset.i4_top    = (INT32)SUBTYPE_LB_CNT_INSET_T;
    t_inset.i4_bottom = (INT32)SUBTYPE_LB_CNT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_LB_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* Set element inset. */
    t_inset.i4_left   = (INT32)SUBTYPE_LB_ELEM_INSET_L;
    t_inset.i4_right  = (INT32)SUBTYPE_LB_ELEM_INSET_R;
    t_inset.i4_top    = (INT32)SUBTYPE_LB_ELEM_INSET_T;
    t_inset.i4_bottom = (INT32)SUBTYPE_LB_ELEM_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_LB_SET_ELEM_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* Set column inset. */
    t_inset.i4_left   = (INT32)SUBTYPE_LB_COL_INSET_L;
    t_inset.i4_right  = (INT32)SUBTYPE_LB_COL_INSET_R;
    t_inset.i4_top    = (INT32)SUBTYPE_LB_COL_INSET_T;
    t_inset.i4_bottom = (INT32)SUBTYPE_LB_COL_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (0),
                              WGL_PACK (& t_inset)));

    /* Set scrolling images. */
    t_scroll_img_info.t_location_up.i4_x     = (INT32)SUBTYPE_LB_IMG_SCROLL_UP_X;
    t_scroll_img_info.t_location_up.i4_y     = (INT32)SUBTYPE_LB_IMG_SCROLL_UP_Y;
    t_scroll_img_info.t_location_down.i4_x   = (INT32)SUBTYPE_LB_IMG_SCROLL_DOWN_X;
    t_scroll_img_info.t_location_down.i4_y   = (INT32)SUBTYPE_LB_IMG_SCROLL_DOWN_Y;

    t_scroll_img_info.h_img_scr_up_on        = h_g_epg_img_arrow_left;
    t_scroll_img_info.h_img_scr_up_off       = h_g_epg_img_arrow_left;
    t_scroll_img_info.h_img_scr_down_on      = h_g_epg_img_arrow_right;
    t_scroll_img_info.h_img_scr_down_off     = h_g_epg_img_arrow_right;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_LB_EXT_SET_PAGING_IMAGE,
                              WGL_PACK (& t_scroll_img_info),
                              WGL_PACK (FALSE)));

    /* Set control keys. */
    t_key_map.ui4_key_next      = BTN_CURSOR_RIGHT;
    t_key_map.ui4_key_prev      = BTN_CURSOR_LEFT;
    t_key_map.ui4_key_select    = 0;
    t_key_map.ui4_key_page_up   = 0;
    t_key_map.ui4_key_page_down = 0;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_LB_SET_KEY_MAP,
                              WGL_PACK (& t_key_map),
                              NULL));

    /* Allocate element data. */
    at_elem_data[0].at_items = (WGL_LB_ITEM_DATA_T*) c_mem_alloc (sizeof(WGL_LB_ITEM_DATA_T));

    if (at_elem_data[0].at_items == NULL) /* Out of memory */
    {
        DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

        return EPGR_OUT_OF_MEM;
    }

    at_elem_data[0].at_items[0].pw2s_text = EPG_MLM (MLM_EPG_KEY_EVT_SUBTYPE_ALL);

    /* Set the number of element to 1. */
    RET_ON_ERR (epg_view_subtype_lst_set_elem_num (1));

    /* Set element data. */
    RET_ON_ERR (epg_view_subtype_lst_set_elems (0, 0, at_elem_data));

    /* Free element data. */
    if (at_elem_data[0].at_items != NULL)
    {
        c_mem_free (at_elem_data[0].at_items);
    }

    /* Set theme. */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_subtype_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_subtype_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_subtype_lst_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = SUBTYPE_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = SUBTYPE_LB_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = SUBTYPE_LB_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* Background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_subtype_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_subtype_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_subtype_lst_vp);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_VP_BK), /* Viewport background color */
                              WGL_PACK (& t_color_info)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_subtype_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_subtype_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_subtype_lst_elem_hlt_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_subtype_lst_elem_hlt_uf_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_subtype_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_subtype_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_subtype_lst_elem_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_LB_SET_ELEM_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* Element background color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_subtype_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_subtype_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_subtype_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_subtype_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_subtype_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_subtype_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_subtype_lst_col_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (0, WGL_CLR_BK), /* Columns background color */
                              WGL_PACK (& t_color_elem)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_epg_color_subtype_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_epg_color_subtype_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_epg_color_subtype_lst_col_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_epg_color_subtype_lst_col_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_epg_color_subtype_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_epg_color_subtype_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_epg_color_subtype_lst_col_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (0, WGL_CLR_TEXT), /* Column text color */
                              WGL_PACK (& t_color_elem)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_epg_color_subtype_lst_title_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_epg_color_subtype_lst_title_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_epg_color_subtype_lst_title_hlt_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_subtype_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_TITLE_FG), /* title text color */
                              WGL_PACK (& t_color_info)));

    return  0;
}

#endif /* APP_EPG_THEME_SEARCH */

/*-----------------------------------------------------------------------------
 * Name: epg_view_get_focus_widget
 *
 * Description: This API gets current focused widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: OSD offset x.
 ----------------------------------------------------------------------------*/
INT32 epg_view_get_focus_widget (EPG_FOCUS_WIDGET_T*    pe_focus_widget)
{
    HANDLE_T    h_widget;

    RET_ON_ERR (c_wgl_get_focus (& h_widget));

    if (h_widget == t_g_view.h_prg_lst)
    {
        *pe_focus_widget = EPG_FOCUS_WIDGET_PRG_LST;
    }
    else if (h_widget == t_g_view.h_surf_lst)
    {
        *pe_focus_widget = EPG_FOCUS_WIDGET_SURF_LST;
    }
    else if (h_widget == t_g_view.h_passwd_edit)
    {
        *pe_focus_widget = EPG_FOCUS_WIDGET_PASSWD_EDIT;
    }
    else if (h_widget == t_g_view.h_type_lst)
    {
        *pe_focus_widget = EPG_FOCUS_WIDGET_TYPE_LST;
    }
    else if (h_widget == t_g_view.h_subtype_lst)
    {
        *pe_focus_widget = EPG_FOCUS_WIDGET_SUBTYPE_LST;
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_set_focus_widget
 *
 * Description: This API sets focus to a given widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: OSD offset x.
 ----------------------------------------------------------------------------*/
INT32 epg_view_set_focus_widget (EPG_FOCUS_WIDGET_T    e_focus_widget)
{
    HANDLE_T    h_widget;

    switch (e_focus_widget)
    {
        case EPG_FOCUS_WIDGET_PRG_LST:
            h_widget = t_g_view.h_prg_lst;
            break;

        case EPG_FOCUS_WIDGET_SURF_LST:
            h_widget = t_g_view.h_surf_lst;
            break;

        case EPG_FOCUS_WIDGET_PASSWD_EDIT:
            h_widget = t_g_view.h_passwd_edit;
            break;

        case EPG_FOCUS_WIDGET_TYPE_LST:
            h_widget = t_g_view.h_type_lst;
            break;

        case EPG_FOCUS_WIDGET_SUBTYPE_LST:
            h_widget = t_g_view.h_subtype_lst;
            break;

        default:
            return (-1);
    }

    return  c_wgl_set_focus (h_widget, FALSE);
}

/*----------------------------------------------------------------------------
 * Name: epg_view_set_navigations
 *
 * Description: This API sets navigations to widgets.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_set_navigations (EPG_FOCUS_WIDGET_T    e_src_widget,
                                UINT32                ui4_key_1,
                                EPG_FOCUS_WIDGET_T    e_dst_widget_1,
                                UINT32                ui4_key_2,
                                EPG_FOCUS_WIDGET_T    e_dst_widget_2)
{
    WGL_KEY_LINK_T    at_key_lnk[2];
    HANDLE_T          h_src_widget;
    HANDLE_T          h_dst_widget_1;
    HANDLE_T          h_dst_widget_2;

    /* Get source widget handle. */
    switch (e_src_widget)
    {
        case EPG_FOCUS_WIDGET_PRG_LST:
            h_src_widget = t_g_view.h_prg_lst;
            break;

        case EPG_FOCUS_WIDGET_SURF_LST:
            h_src_widget = t_g_view.h_surf_lst;
            break;

        case EPG_FOCUS_WIDGET_PASSWD_EDIT:
            h_src_widget = t_g_view.h_passwd_edit;
            break;

        case EPG_FOCUS_WIDGET_TYPE_LST:
            h_src_widget = t_g_view.h_type_lst;
            break;

        case EPG_FOCUS_WIDGET_SUBTYPE_LST:
            h_src_widget = t_g_view.h_subtype_lst;
            break;

        default:
            return (-1);
    }

    /* Get handle of destination widget 1. */
    switch (e_dst_widget_1)
    {
        case EPG_FOCUS_WIDGET_PRG_LST:
            h_dst_widget_1 = t_g_view.h_prg_lst;
            break;

        case EPG_FOCUS_WIDGET_SURF_LST:
            h_dst_widget_1 = t_g_view.h_surf_lst;
            break;

        case EPG_FOCUS_WIDGET_PASSWD_EDIT:
            h_dst_widget_1 = t_g_view.h_passwd_edit;
            break;

        case EPG_FOCUS_WIDGET_TYPE_LST:
            h_dst_widget_1 = t_g_view.h_type_lst;
            break;

        case EPG_FOCUS_WIDGET_SUBTYPE_LST:
            h_dst_widget_1 = t_g_view.h_subtype_lst;
            break;

        default:
            return (-1);
    }

    /* Get handle of destination widget 2. */
    switch (e_dst_widget_2)
    {
        case EPG_FOCUS_WIDGET_PRG_LST:
            h_dst_widget_2 = t_g_view.h_prg_lst;
            break;

        case EPG_FOCUS_WIDGET_SURF_LST:
            h_dst_widget_2 = t_g_view.h_surf_lst;
            break;

        case EPG_FOCUS_WIDGET_PASSWD_EDIT:
            h_dst_widget_2 = t_g_view.h_passwd_edit;
            break;

        case EPG_FOCUS_WIDGET_TYPE_LST:
            h_dst_widget_2 = t_g_view.h_type_lst;
            break;

        case EPG_FOCUS_WIDGET_SUBTYPE_LST:
            h_dst_widget_2 = t_g_view.h_subtype_lst;
            break;

        default:
            return (-1);
    }

    /* Set navigation keys. */
    at_key_lnk[0].ui4_key  = ui4_key_1;
    at_key_lnk[0].h_widget = h_dst_widget_1;
    at_key_lnk[1].ui4_key  = ui4_key_2;
    at_key_lnk[1].h_widget = h_dst_widget_2;

    RET_ON_ERR (c_wgl_set_navigation (h_src_widget,
                                      2,
                                      at_key_lnk));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_main_frm_set_visibility
 *
 * Description: This API sets visibility to main frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_main_frm_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_main_frm, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_main_frm, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_main_frm_show
 *
 * Description: This API shows the main frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_main_frm_show (VOID)
{
    return  c_wgl_show (t_g_view.h_main_frm, WGL_SW_NORMAL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_main_frm_hide
 *
 * Description: This API hides the main frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_main_frm_hide (VOID)
{
    return  c_wgl_show (t_g_view.h_main_frm, WGL_SW_HIDE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_main_frm_repaint
 *
 * Description: This API repaints the main frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_main_frm_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_main_frm, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_base_frm_set_visibility
 *
 * Description: This API sets visibility to base frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_base_frm_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_base_frm, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_base_frm, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_frm_set_visibility
 *
 * Description: This API sets visibility to description frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_frm_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_desc_frm, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_desc_frm, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_frm_show
 *
 * Description: This API shows the description frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_frm_show (VOID)
{
    return  c_wgl_show (t_g_view.h_desc_frm, WGL_SW_NORMAL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_frm_show
 *
 * Description: This API hides the description frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_frm_hide (VOID)
{
    return  c_wgl_show (t_g_view.h_desc_frm, WGL_SW_HIDE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_frm_repaint
 *
 * Description: This API repaints the description frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_frm_repaint (VOID)
{
    /* Synchronous repaint */
    return  c_wgl_repaint (t_g_view.h_desc_frm, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_bk_frm_set_visibility
 *
 * Description: This API sets visibility to description background frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_bk_frm_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_desc_bk_frm, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_desc_bk_frm, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_video_frm_set_visibility
 *
 * Description: This API sets visibility to video frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_video_frm_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_video_frm, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_video_frm, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_video_frm_show
 *
 * Description: This API shows or hides the video frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_video_frm_show (BOOL    b_show)
{
    if (b_show)
    {
        return  c_wgl_show (t_g_view.h_video_frm, WGL_SW_NORMAL);
    }
    else
    {
        return  c_wgl_show (t_g_view.h_video_frm, WGL_SW_HIDE);   
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_frm_set_visibility
 *
 * Description: This API sets visibility to password frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_frm_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_passwd_frm, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_passwd_frm, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_frm_show
 *
 * Description: This API shows the password frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_frm_show (VOID)
{
    return  c_wgl_show (t_g_view.h_passwd_frm, WGL_SW_NORMAL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_frm_show
 *
 * Description: This API hides the password frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_frm_hide (VOID)
{
    return  c_wgl_show (t_g_view.h_passwd_frm, WGL_SW_HIDE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_edit_set_visibility
 *
 * Description: This API sets visibility to password edit widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_edit_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_passwd_edit, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_passwd_edit, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_edit_set_text
 *
 * Description: This API sets text to password edit.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_edit_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_passwd_edit,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(pw2s_text),
                          WGL_PACK(c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_edit_get_text
 *
 * Description: This API gets text of password edit.
 *
 * Inputs:  ui2_buf_size        Buffer size.
 *
 * Outputs: pw2s_text           Text in edit box.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_edit_get_text (UTF16_T*    pw2s_text,
                                     UINT16      ui2_buf_size)
{
    return  c_wgl_do_cmd (t_g_view.h_passwd_edit,
                          WGL_CMD_EB_GET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (ui2_buf_size));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passed_edit_get_text
 *
 * Description: This API gets the length of text of password edit.
 *
 * Inputs:  -
 *
 * Outputs: pui2_text_len       Text length of edit box.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_edit_get_text_len (UINT16*    pui2_text_len)
{
    return  c_wgl_do_cmd (t_g_view.h_passwd_edit,
                          WGL_CMD_EB_GET_TEXT_LENGTH,
                          WGL_PACK (pui2_text_len),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_retrieve_icon_set_visibility
 *
 * Description: This API sets visibility to retrieving icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_retrieve_icon_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_retrieve_icon, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_retrieve_icon, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_retrieve_icon_set_image
 *
 * Description: This API sets a given image handle to retrieving icon.
 *
 * Inputs:  h_img               Image handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_retrieve_icon_set_image (HANDLE_T    h_img)
{
    WGL_IMG_INFO_T    t_img_info;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;

    t_img_info.u_img_data.t_standard.t_enable    = h_img;
    t_img_info.u_img_data.t_standard.t_disable   = h_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_img;

    return  c_wgl_do_cmd (t_g_view.h_retrieve_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK (WGL_IMG_FG),
                          WGL_PACK (& t_img_info));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_retrieve_icon_repaint
 *
 * Description: This API repaints the retrieving icon.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_retrieve_icon_repaint (VOID)
{
    /* Synchronously repaint. */
    return  c_wgl_repaint (t_g_view.h_retrieve_icon, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_set_visibility
 *
 * Description: This API sets visibility to program list widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_prg_lst, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_prg_lst, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_clr_elems
 *
 * Description: This API clears the elements of the program list within a given
 *              range.
 *
 * Inputs:  ui2_start           Start index.
 *          ui2_end             End index.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_clr_elems (UINT16    ui2_start,
                                  UINT16    ui2_end)
{
    return  c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_CLEAR_ELEMS_BY_RANGE,
                          WGL_PACK (ui2_start),
                          WGL_PACK (ui2_end));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_enable_control_key
 *
 * Description: This API enables/disables the control keys for the program list.
 *
 * Inputs:  b_enable            TRUE - Enable control keys.
 *                              FALSE - Disable control keys.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_enable_control_key (BOOL    b_enable)
{
    INT32               i4_rc;
    WGL_LB_KEY_MAP_T    t_key_map;

    if (b_enable) /* Enable control keys. */
    {
        t_key_map.ui4_key_next      = BTN_CURSOR_DOWN;
        t_key_map.ui4_key_prev      = BTN_CURSOR_UP;
        t_key_map.ui4_key_select    = 0;
        t_key_map.ui4_key_page_up   = 0;
        t_key_map.ui4_key_page_down = 0;

        i4_rc = c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_KEY_MAP,
                              WGL_PACK (& t_key_map),
                              NULL);
    }
    else /* Disable control keys. */
    {
        t_key_map.ui4_key_next      = 0;
        t_key_map.ui4_key_prev      = 0;
        t_key_map.ui4_key_select    = 0;
        t_key_map.ui4_key_page_up   = 0;
        t_key_map.ui4_key_page_down = 0;

        i4_rc = c_wgl_do_cmd (t_g_view.h_prg_lst,
                              WGL_CMD_LB_SET_KEY_MAP,
                              WGL_PACK (& t_key_map),
                              NULL);
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_get_hlt_idx
 *
 * Description: This API gets current highlighted index in the program list.
 *
 * Inputs:  -
 *
 * Outputs: pui2_idx            Highlighted index.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_get_hlt_idx (UINT16*    pui2_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK (pui2_idx),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_hlt_elem
 *
 * Description: This API highlights a specific element in the program list.
 *
 * Inputs:  ui2_idx             The index of element to be highlighted.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_hlt_elem (UINT16    ui2_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK (ui2_idx),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_unhlt_elem
 *
 * Description: This API unhighlights an elements in the program list.
 *
 * Inputs:  ui2_idx             The index of element to be unhighlighted.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_unhlt_elem (UINT16    ui2_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_UNHLT_ELEM,
                          WGL_PACK (ui2_idx),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_set_elem_num
 *
 * Description: This API sets the number of elements to the program list.
 *
 * Inputs:  ui2_elem_num        The number of elements to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_set_elem_num (UINT16    ui2_elem_num)
{
    return  c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK (ui2_elem_num),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_get_elem_num
 *
 * Description: This API gets the number of elements to the program list.
 *
 * Inputs:  -
 *
 * Outputs: ui2_elem_num        The number of elements.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_get_elem_num (UINT16*    pui2_elem_num)
{
    return  c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK (pui2_elem_num),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_set_elem
 *
 * Description: This API sets the element data of a given index to the program
 *              list.
 *
 * Inputs:  ui2_idx             Element index.
 *          pt_elem_data        Element data.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_set_elem (UINT16                 ui2_idx,
                                 WGL_LB_ELEM_DATA_T*    pt_elem_data)
{
    return  c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_SET_ELEM_DATA,
                          WGL_PACK (ui2_idx),
                          WGL_PACK (pt_elem_data));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_set_elems
 *
 * Description: This API sets the elements data for given a range to the program
 *              list.
 *
 * Inputs:  ui2_start           Start index
 *          ui2_end             End index.
 *          pt_elem_data        Elements data.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_set_elems (UINT16                 ui2_start,
                                  UINT16                 ui2_end,
                                  WGL_LB_ELEM_DATA_T*    pt_elem_data)
{
    return  c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_SET_ELEMS_BY_RANGE,
                          WGL_PACK_2 (ui2_start, ui2_end),
                          WGL_PACK (pt_elem_data));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_set_title
 *
 * Description: This API sets the title of the program list.
 *
 * Inputs:  pw2s_text           Title text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_set_title (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_SET_TITLE_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_set_paging_images
 *
 * Description: This API sets paging images of the program list.
 *
 * Inputs:  b_page_up           Page-up function is enabled.
 *          b_page_down         Page-down function is enabled.
 *          b_repaint           Repaint paging images or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_set_paging_images (BOOL    b_page_up,
                                          BOOL    b_page_down,
                                          BOOL    b_repaint)
{
    WGL_LB_SCROLL_IMG_INFO_T    t_scroll_img_info;

    t_scroll_img_info.t_location_up.i4_x     = (INT32)PRG_LB_IMG_SCROLL_UP_X;
    t_scroll_img_info.t_location_up.i4_y     = (INT32)PRG_LB_IMG_SCROLL_UP_Y;
    t_scroll_img_info.t_location_down.i4_x   = (INT32)PRG_LB_IMG_SCROLL_DOWN_X;
    t_scroll_img_info.t_location_down.i4_y   = (INT32)PRG_LB_IMG_SCROLL_DOWN_Y;

    /* Set page-up images. */
    if (b_page_up)
    {
        t_scroll_img_info.h_img_scr_up_on    = PRG_LB_IMG_SCROLL_UP_ENABLE;
        t_scroll_img_info.h_img_scr_up_off   = PRG_LB_IMG_SCROLL_UP_ENABLE;
    }
    else
    {
        t_scroll_img_info.h_img_scr_up_on    = PRG_LB_IMG_SCROLL_UP_DISABLE;
        t_scroll_img_info.h_img_scr_up_off   = PRG_LB_IMG_SCROLL_UP_DISABLE;
    }

    /* Set page-down images. */
    if (b_page_down)
    {
        t_scroll_img_info.h_img_scr_down_on  = PRG_LB_IMG_SCROLL_DOWN_ENABLE;
        t_scroll_img_info.h_img_scr_down_off = PRG_LB_IMG_SCROLL_DOWN_ENABLE;
    }
    else
    {
        t_scroll_img_info.h_img_scr_down_on  = PRG_LB_IMG_SCROLL_DOWN_DISABLE;
        t_scroll_img_info.h_img_scr_down_off = PRG_LB_IMG_SCROLL_DOWN_DISABLE;
    }

    return  c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_EXT_SET_PAGING_IMAGE,
                          WGL_PACK (& t_scroll_img_info),
                          WGL_PACK (b_repaint));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_repaint_elems
 *
 * Description: This API repaints the elements within a given range.
 *
 * Inputs:  ui2_start           Start index.
 *          ui2_end             End index.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_repaint_elems (UINT16    ui2_start,
                                      UINT16    ui2_end)
{
    return  c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_REPAINT_ELEMS,
                          WGL_PACK (ui2_start),
                          WGL_PACK (ui2_end));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_reset
 *
 * Description: This API resets all the elements in the program list.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_reset (BOOL    b_repaint)
{
    INT32    i4_rc;

    i4_rc = c_wgl_do_cmd (t_g_view.h_prg_lst,
                          WGL_CMD_LB_CLEAR_ELEMS_BY_RANGE,
                          WGL_PACK (0),
                          WGL_PACK (ELEM_VIEW_SIZE-1));

    /* Repaint */
    if ((i4_rc == WGLR_OK) && (b_repaint))
    {
        i4_rc = c_wgl_repaint (t_g_view.h_prg_lst, NULL, TRUE);
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_lst_repaint
 *
 * Description: This API repaints the program list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_lst_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_prg_lst, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_surf_lst_set_visibility
 *
 * Description: This API sets the visibility to surfing list widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_surf_lst_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_surf_lst, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_surf_lst, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_surf_lst_clr_elems
 *
 * Description: This API clears the elements of the surfing list within a
 *              given range.
 *
 * Inputs:  ui2_start           Start index.
 *          ui2_end             End index.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_surf_lst_clr_elems (UINT16    ui2_start,
                                   UINT16    ui2_end)
{
    return  c_wgl_do_cmd (t_g_view.h_surf_lst,
                          WGL_CMD_LB_CLEAR_ELEMS_BY_RANGE,
                          WGL_PACK (ui2_start),
                          WGL_PACK (ui2_end));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_surf_lst_get_hlt_idx
 *
 * Description: This API gets current highlighted index in the surfing list.
 *
 * Inputs:  -
 *
 * Outputs: pui2_idx            Highlighted index.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_surf_lst_get_hlt_idx (UINT16*    pui2_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_surf_lst,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK (pui2_idx),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_surf_lst_hlt_elem
 *
 * Description: This API highlights an elements in the surfing list.
 *
 * Inputs:  ui2_idx             The index of element to be highlighted.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_surf_lst_hlt_elem (UINT16    ui2_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_surf_lst,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK (ui2_idx),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_surf_lst_unhlt_elem
 *
 * Description: This API unhighlights an elements in the surfing list.
 *
 * Inputs:  ui2_idx             The index of element to be unhighlighted.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_surf_lst_unhlt_elem (UINT16    ui2_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_surf_lst,
                          WGL_CMD_LB_UNHLT_ELEM,
                          WGL_PACK (ui2_idx),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_surf_lst_set_elems
 *
 * Description: This API sets the elements data for given a range to the surfing
 *              list.
 *
 * Inputs:  ui2_start           Start index
 *          ui2_end             End index.
 *          pt_elem_data        Elements data.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_surf_lst_set_elems (UINT16                 ui2_start,
                                   UINT16                 ui2_end,
                                   WGL_LB_ELEM_DATA_T*    pt_elem_data)
{
    return  c_wgl_do_cmd (t_g_view.h_surf_lst,
                          WGL_CMD_LB_SET_ELEMS_BY_RANGE,
                          WGL_PACK_2 (ui2_start, ui2_end),
                          WGL_PACK (pt_elem_data));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_surf_lst_set_title
 *
 * Description: This API sets the title of the surfing list.
 *
 * Inputs:  pw2s_text           Title text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_surf_lst_set_title (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_surf_lst,
                          WGL_CMD_LB_SET_TITLE_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_surf_lst_set_paging_images
 *
 * Description: This API sets pageing images for the surfing list.
 *
 * Inputs:  b_page_up           Page-up function is enabled.
 *          b_page_down         Page-down function is enabled.
 *          b_repaint           Repaint paging images or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_surf_lst_set_paging_images (BOOL    b_page_up,
                                           BOOL    b_page_down,
                                           BOOL    b_repaint)
{
    INT32                       i4_rc;
    WGL_LB_SCROLL_IMG_INFO_T    t_scroll_img_info;

    t_scroll_img_info.t_location_up.i4_x     = (INT32)SURF_LB_IMG_SCROLL_UP_X;
    t_scroll_img_info.t_location_up.i4_y     = (INT32)SURF_LB_IMG_SCROLL_UP_Y;
    t_scroll_img_info.t_location_down.i4_x   = (INT32)SURF_LB_IMG_SCROLL_DOWN_X;
    t_scroll_img_info.t_location_down.i4_y   = (INT32)SURF_LB_IMG_SCROLL_DOWN_Y;

    /* Set page-up images. */
    if (b_page_up)
    {
        t_scroll_img_info.h_img_scr_up_on    = SURF_LB_IMG_SCROLL_UP_ENABLE;
        t_scroll_img_info.h_img_scr_up_off   = SURF_LB_IMG_SCROLL_UP_ENABLE;
    }
    else
    {
        t_scroll_img_info.h_img_scr_up_on    = SURF_LB_IMG_SCROLL_UP_DISABLE;
        t_scroll_img_info.h_img_scr_up_off   = SURF_LB_IMG_SCROLL_UP_DISABLE;
    }

    /* Set page-down images. */
    if (b_page_down)
    {
        t_scroll_img_info.h_img_scr_down_on  = SURF_LB_IMG_SCROLL_DOWN_ENABLE;
        t_scroll_img_info.h_img_scr_down_off = SURF_LB_IMG_SCROLL_DOWN_ENABLE;
    }
    else
    {
        t_scroll_img_info.h_img_scr_down_on  = SURF_LB_IMG_SCROLL_DOWN_DISABLE;
        t_scroll_img_info.h_img_scr_down_off = SURF_LB_IMG_SCROLL_DOWN_DISABLE;
    }

    /* Repaint */
    if (b_repaint)
    {
        i4_rc = c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_EXT_SET_PAGING_IMAGE,
                              WGL_PACK (& t_scroll_img_info),
                              WGL_PACK (TRUE));
    }
    else
    {
        i4_rc = c_wgl_do_cmd (t_g_view.h_surf_lst,
                              WGL_CMD_LB_EXT_SET_PAGING_IMAGE,
                              WGL_PACK (& t_scroll_img_info),
                              WGL_PACK (FALSE));
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_surf_lst_repaint_elems
 *
 * Description: This API repaints the elements within a given range.
 *
 * Inputs:  ui2_start           Start index.
 *          ui2_end             End index.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_surf_lst_repaint_elems (UINT16    ui2_start,
                                       UINT16    ui2_end)
{
    return  c_wgl_do_cmd (t_g_view.h_surf_lst,
                          WGL_CMD_LB_REPAINT_ELEMS,
                          WGL_PACK (ui2_start),
                          WGL_PACK (ui2_end));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_surf_lst_reset
 *
 * Description: This API resets all the elements in the program list.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_surf_lst_reset (BOOL    b_repaint)
{
    INT32    i4_rc;

    i4_rc = c_wgl_do_cmd (t_g_view.h_surf_lst,
                          WGL_CMD_LB_CLEAR_ELEMS_BY_RANGE,
                          WGL_PACK (0),
                          WGL_PACK (ELEM_VIEW_SIZE-1));

    /* Repaint */
    if ((i4_rc == WGLR_OK) && (b_repaint))
    {
        i4_rc = c_wgl_repaint (t_g_view.h_surf_lst, NULL, TRUE);
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_surf_lst_repaint
 *
 * Description: This API repaints the program list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_surf_lst_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_surf_lst, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_chn_lst_set_visibility
 *
 * Description: This API sets visibility to channel list widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_chn_lst_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_chn_lst, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_chn_lst, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_chn_lst_set_text
 *
 * Description: This API sets text of a given item to the channel list.
 *
 * Inputs:  e_chn_type          Channel type.
 *          pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_chn_lst_set_text (EPG_CHN_TYPE_T    e_chn_type,
                                 UTF16_T*          pw2s_text)
{
    UINT16    ui2_col_idx;

    switch (e_chn_type)
    {
        case EPG_CHN_TYPE_PREV: /* Previous channel */
            ui2_col_idx = 0;
            break;

        case EPG_CHN_TYPE_CRNT: /* Current channel */
            ui2_col_idx = 2;
            break;

        case EPG_CHN_TYPE_NEXT: /* Next channel */
            ui2_col_idx = 4;
            break;

        default:
            return (-1);
    }

    return c_wgl_do_cmd (t_g_view.h_chn_lst,
                         WGL_CMD_LB_SET_ITEM_TEXT,
                         WGL_PACK_2 (0, ui2_col_idx),
                         WGL_PACK (pw2s_text));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_chn_lst_reset
 *
 * Description: This API resets the channel list.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_chn_lst_reset (BOOL    b_repaint)
{
    INT32    i4_rc;

    i4_rc = c_wgl_do_cmd (t_g_view.h_chn_lst,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2 (0, 0),
                          WGL_PACK (EPG_MLM (MLM_EPG_KEY_MSG_NULL)));

    if (i4_rc == WGLR_OK)
    {
        i4_rc = c_wgl_do_cmd (t_g_view.h_chn_lst,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2 (0, 2),
                              WGL_PACK (EPG_MLM (MLM_EPG_KEY_MSG_NULL)));

        if (i4_rc == WGLR_OK)
        {
            i4_rc = c_wgl_do_cmd (t_g_view.h_chn_lst,
                                  WGL_CMD_LB_SET_ITEM_TEXT,
                                  WGL_PACK_2 (0, 4),
                                  WGL_PACK (EPG_MLM (MLM_EPG_KEY_MSG_NULL)));
        }
    }

    /* Repaint */
    if ((i4_rc == WGLR_OK) && (b_repaint))
    {
        i4_rc = c_wgl_repaint (t_g_view.h_chn_lst, NULL, TRUE);
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_chn_lst_repaint
 *
 * Description: This API repaints the channel list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_chn_lst_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_chn_lst, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_lst_set_visibility
 *
 * Description: This API sets visibility to description list widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_lst_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_desc_lst, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_desc_lst, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_lst_set_text
 *
 * Description: This API sets text of a given item to the description list.
 *
 * Inputs:  e_desc_type         Description type.
 *          pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_lst_set_text (EPG_DESC_TYPE_T    e_desc_type,
                                  UTF16_T*           pw2s_text)
{
    UINT16    ui2_col_idx;

    switch (e_desc_type)
    {
        case EPG_DESC_TYPE_TIME:   /* Time details */
            ui2_col_idx = 0;
            break;

        case EPG_DESC_TYPE_RATING: /* Rating */
            ui2_col_idx = 1;
            break;

        default:
            return (-1);
    }

    return  c_wgl_do_cmd (t_g_view.h_desc_lst,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2 (0, ui2_col_idx),
                          WGL_PACK (pw2s_text));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_lst_reset
 *
 * Description: This API resets the description list.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_lst_reset (BOOL    b_repaint)
{
    INT32    i4_rc;

    i4_rc = c_wgl_do_cmd (t_g_view.h_desc_lst,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2 (0, 0),
                          WGL_PACK (EPG_MLM (MLM_EPG_KEY_MSG_NULL)));

    if (i4_rc == WGLR_OK)
    {
        i4_rc = c_wgl_do_cmd (t_g_view.h_desc_lst,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2 (0, 1),
                              WGL_PACK (EPG_MLM (MLM_EPG_KEY_MSG_NULL)));
    }

    /* Repaint */
    if ((i4_rc == WGLR_OK) && (b_repaint))
    {
        i4_rc = c_wgl_repaint (t_g_view.h_desc_lst, NULL, TRUE);
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_lst_repaint
 *
 * Description: This API repaints the description list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_lst_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_desc_lst, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_help_lst_set_visibility
 *
 * Description: This API sets visibility to help list widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_help_lst_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_help_lst, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_help_lst, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_help_lst_set_text
 *
 * Description: This API sets column width for a specific index.
 *
 * Inputs:  e_help_type         Help type.
 *          ui2_width           Column width.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_help_lst_set_col_width (EPG_HELP_TYPE_T    e_help_type,
                                       UINT16             ui2_width)
{
    UINT16      ui2_col_idx;

    switch (e_help_type)
    {
        case EPG_HELP_TYPE_BTN_RED:    /* Red button */
            ui2_col_idx = 0;
            break;

        case EPG_HELP_TYPE_BTN_GREEN:  /* Green button */
            ui2_col_idx = 2;
            break;

        case EPG_HELP_TYPE_BTN_YELLOW: /* Yellow button */
            ui2_col_idx = 4;
            break;

        case EPG_HELP_TYPE_BTN_BLUE:   /* Blue button */
            ui2_col_idx = 6;
            break;

        default:
            return (-1);
    }

    return  c_wgl_do_cmd (t_g_view.h_help_lst,
                          WGL_CMD_LB_SET_COL_WIDTH,
                          WGL_PACK (ui2_col_idx),
                          WGL_PACK (ui2_width));

}

/*-----------------------------------------------------------------------------
 * Name: epg_view_help_lst_set_text
 *
 * Description: This API sets text of a given item to the help list.
 *
 * Inputs:  e_help_type         Help type.
 *          pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_help_lst_set_text (EPG_HELP_TYPE_T    e_help_type,
                                  UTF16_T*           pw2s_text)
{
    UINT16    ui2_col_idx;

    switch (e_help_type)
    {
        case EPG_HELP_TYPE_BTN_RED:    /* Red button */
            ui2_col_idx = 1;
            break;

        case EPG_HELP_TYPE_BTN_GREEN:  /* Green button */
            ui2_col_idx = 3;
            break;

        case EPG_HELP_TYPE_BTN_YELLOW: /* Yellow button */
            ui2_col_idx = 5;
            break;

        case EPG_HELP_TYPE_BTN_BLUE:   /* Blue button */
            ui2_col_idx = 7;
            break;

        default:
            return (-1);
    }

    return  c_wgl_do_cmd (t_g_view.h_help_lst,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2 (0, ui2_col_idx),
                          WGL_PACK (pw2s_text));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_help_lst_set_image
 *
 * Description: This API sets image of a given item to the help list.
 *
 * Inputs:  e_help_type         Help type.
 *          b_enable            Set Enabled/Disabled image.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_help_lst_set_image (EPG_HELP_TYPE_T    e_help_type,
                                   WGL_HIMG_TPL_T     h_img)
{
    UINT16      ui2_col_idx;

    switch (e_help_type)
    {
        case EPG_HELP_TYPE_BTN_RED:    /* Red button */
            ui2_col_idx = 0;
            break;

        case EPG_HELP_TYPE_BTN_GREEN:  /* Green button */
            ui2_col_idx = 2;
            break;

        case EPG_HELP_TYPE_BTN_YELLOW: /* Yellow button */
            ui2_col_idx = 4;
            break;

        case EPG_HELP_TYPE_BTN_BLUE:   /* Blue button */
            ui2_col_idx = 6;
            break;

        default:
            return (-1);
    }

    return  c_wgl_do_cmd (t_g_view.h_help_lst,
                          WGL_CMD_LB_SET_ITEM_IMAGE,
                          WGL_PACK_2 (0, ui2_col_idx),
                          WGL_PACK (h_img));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_help_lst_reset
 *
 * Description: This API resets the help list.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_help_lst_reset (BOOL    b_repaint)
{
    /* Set NULL strings. */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2 (0, HELP_LB_BTN_RED_TXT_IDX),
                              WGL_PACK (EPG_MLM (MLM_EPG_KEY_MSG_NULL))));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2 (0, HELP_LB_BTN_GREEN_TXT_IDX),
                              WGL_PACK (EPG_MLM (MLM_EPG_KEY_MSG_NULL))));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2 (0, HELP_LB_BTN_YELLOW_TXT_IDX),
                              WGL_PACK (EPG_MLM (MLM_EPG_KEY_MSG_NULL))));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2 (0, HELP_LB_BTN_BLUE_TXT_IDX),
                              WGL_PACK (EPG_MLM (MLM_EPG_KEY_MSG_NULL))));

    /* Set disabled images. */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_ITEM_IMAGE,
                              WGL_PACK_2 (0, HELP_LB_BTN_RED_IMG_IDX),
                              WGL_PACK (HELP_LB_IMG_BTN_RED_DISABLE)));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_ITEM_IMAGE,
                              WGL_PACK_2 (0, HELP_LB_BTN_GREEN_IMG_IDX),
                              WGL_PACK (HELP_LB_IMG_BTN_GREEN_DISABLE)));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_ITEM_IMAGE,
                              WGL_PACK_2 (0, HELP_LB_BTN_YELLOW_IMG_IDX),
                              WGL_PACK (HELP_LB_IMG_BTN_YELLOW_DISABLE)));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_help_lst,
                              WGL_CMD_LB_SET_ITEM_IMAGE,
                              WGL_PACK_2 (0, HELP_LB_BTN_BLUE_IMG_IDX),
                              WGL_PACK (HELP_LB_IMG_BTN_BLUE_DISABLE)));

    if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (t_g_view.h_help_lst, NULL, TRUE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_help_lst_repaint
 *
 * Description: This API repaints the help list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_help_lst_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_help_lst, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_icon_lst_set_visibility
 *
 * Description: This API sets visibility to icon list widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_icon_lst_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_icon_lst, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_icon_lst, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_icon_lst_set_image
 *
 * Description: This API sets the image of a given type to the icon list.
 *
 * Inputs:  e_icon_type         Icon type.
 *          b_enable            Set enabled/disabled image.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_icon_lst_set_image (EPG_ICON_TYPE_T    e_icon_type,
                                   BOOL               b_enable)
{
    UINT16      ui2_col_idx;
    HANDLE_T    h_img;

    switch (e_icon_type)
    {
        case EPG_ICON_TYPE_LOCK:
            ui2_col_idx = 0;
            h_img = b_enable ? h_g_epg_img_lock : NULL_HANDLE;
            break;

        case EPG_ICON_TYPE_CC:
            ui2_col_idx = 1;
            h_img = b_enable ? h_g_epg_img_caption : NULL_HANDLE;
            break;

        default:
            return (-1);
    }

    return  c_wgl_do_cmd (t_g_view.h_icon_lst,
                          WGL_CMD_LB_SET_ITEM_IMAGE,
                          WGL_PACK_2 (0, ui2_col_idx),
                          WGL_PACK (h_img));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_icon_lst_reset
 *
 * Description: This API sets the icon list.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_icon_lst_reset (BOOL    b_repaint)
{
    INT32    i4_rc;

    i4_rc = c_wgl_do_cmd (t_g_view.h_icon_lst,
                          WGL_CMD_LB_SET_ITEM_IMAGE,
                          WGL_PACK_2 (0, 0),
                          WGL_PACK (NULL));

    if (i4_rc == WGLR_OK)
    {
        i4_rc = c_wgl_do_cmd (t_g_view.h_icon_lst,
                              WGL_CMD_LB_SET_ITEM_IMAGE,
                              WGL_PACK_2 (0, 1),
                              WGL_PACK (NULL));
    }

    /* Repaint */
    if ((i4_rc == WGLR_OK) && (b_repaint))
    {
        i4_rc = c_wgl_repaint (t_g_view.h_icon_lst, NULL, TRUE);
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_icon_lst_repaint
 *
 * Description: This API repaints the icon list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_icon_lst_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_icon_lst, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_time_txt_set_visibility
 *
 * Description: This API sets visibility to time text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_time_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_time_txt, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_time_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_time_txt_set_text
 *
 * Description: This API sets text to the time text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_time_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_time_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_time_txt_repaint
 *
 * Description: This API repaints the time text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_time_txt_repaint (VOID)
{
    /* Asynchronously repaint */
    return  c_wgl_repaint (t_g_view.h_time_txt, NULL, FALSE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_retrieve_txt_set_visibility
 *
 * Description: This API sets visibility to retrieving text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_retrieve_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_retrieve_txt, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_retrieve_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_retrieve_txt_set_text
 *
 * Description: This API sets text to the retrieving text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_retrieve_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_retrieve_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_retrieve_txt_repaint
 *
 * Description: This API repaints the retrieving text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_retrieve_txt_repaint (VOID)
{
    /* Asynchronously repaint. */
    return  c_wgl_repaint (t_g_view.h_retrieve_txt, NULL, FALSE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_dci_hts_set_visibility
 *
 * Description: This API sets visibility to dci hyper text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_dci_hts_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_dci_hts, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_dci_hts, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_dci_hts_set_text
 *
 * Description: This API sets text to the DCI hyper text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_dci_hts_set_text (UTF16_T*    pw2s_text,
                                 UTF16_T*    pw2s_dummy)
{
    UINT16                 ui2_sec_id;
    WGL_HTS_TEXT_INFO_T    t_hts_info;

    /* Clear hyper text. */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_dci_hts,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL));

    /* Reset hyper text infomation. */
    c_memset (& t_hts_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));

    /* Set font data. */
    c_strcpy (t_hts_info.t_font.a_c_font_name, t_g_view.s_font_name);

    t_hts_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_hts_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
    t_hts_info.t_font.e_font_size  = DCI_HTS_FNT_SIZE;

    /* Set text background color. */
    COLOR_COPY (& t_hts_info.t_clr_text_bk, & t_g_epg_color_dci_txt_bk);

    /* Append text. */
    if (pw2s_text != NULL)
    {
        COLOR_COPY (& t_hts_info.t_clr_text, & t_g_epg_color_dci_txt);

        t_hts_info.t_string.ui2_size_buf = (UINT16)(c_uc_w2s_strlen (pw2s_text) * sizeof(UTF16_T));
        t_hts_info.t_string.w2s_str      = pw2s_text;
        t_hts_info.t_string.ui2_len_str  = (UINT16)c_uc_w2s_strlen (pw2s_text);

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_dci_hts,
                                  WGL_CMD_HTS_APPEND_TEXT_SEC,
                                  WGL_PACK (& t_hts_info),
                                  WGL_PACK (& ui2_sec_id)));
    }


    /* Append dummy text. */
    if (pw2s_dummy != NULL)
    {
        COLOR_COPY (& t_hts_info.t_clr_text, & t_g_epg_color_dci_txt_dummy);

        t_hts_info.t_string.ui2_size_buf = (UINT16)(c_uc_w2s_strlen (pw2s_dummy) * sizeof(UTF16_T));
        t_hts_info.t_string.w2s_str      = pw2s_dummy;
        t_hts_info.t_string.ui2_len_str  = (UINT16)c_uc_w2s_strlen (pw2s_dummy);

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_dci_hts,
                                  WGL_CMD_HTS_APPEND_TEXT_SEC,
                                  WGL_PACK (& t_hts_info),
                                  WGL_PACK (& ui2_sec_id)));
    }

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_dci_hts_clear
 *
 * Description: This API clears the DCI hyper text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_dci_hts_clear (VOID)
{
    return  c_wgl_do_cmd (t_g_view.h_dci_hts,
                          WGL_CMD_HTS_CLEAR_ALL,
                          WGL_PACK (FALSE),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_dci_hts_repaint
 *
 * Description: This API repaints the DCI hyper text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_dci_hts_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_dci_hts, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_txt_set_visibility
 *
 * Description: This API sets visibility to program text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_prg_txt, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_prg_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_txt_set_text
 *
 * Description: This API sets text to the program info text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_prg_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_prg_txt_repaint
 *
 * Description: This API repaints the program info text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_prg_txt_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_prg_txt, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_video_txt_set_visibility
 *
 * Description: This API sets visibility to video text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_video_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_video_txt, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_video_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_video_txt_set_text
 *
 * Description: This API sets text to the video text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_video_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_video_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_video_txt_repaint
 *
 * Description: This API repaints the video text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_video_txt_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_video_txt, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_txt_set_visibility
 *
 * Description: This API sets visibility to description text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_desc_txt, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_desc_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_txt_set_text
 *
 * Description: This API sets text to the description text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_desc_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_txt_repaint
 *
 * Description: This API repaints the video text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_txt_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_desc_txt, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_txt_page_up
 *
 * Description: This API pages up the description text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_txt_page_up (VOID)
{
    INT32     i4_ret;

    i4_ret = c_wgl_do_cmd (t_g_view.h_desc_txt,
                           WGL_CMD_TEXT_PAGE_SCROL,
                           WGL_PACK (TRUE),
                           WGL_PACK (FALSE));
    EPG_CHK_FAIL (i4_ret, i4_ret);

    /* Repaint union */
    i4_ret = _epg_view_desc_txt_repaint_union ();
    EPG_CHK_FAIL (i4_ret, i4_ret);

    return EPGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_txt_page_down
 *
 * Description: This API pages up the description text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_txt_page_down (VOID)
{
    INT32     i4_ret;

    i4_ret = c_wgl_do_cmd (t_g_view.h_desc_txt,
                           WGL_CMD_TEXT_PAGE_SCROL,
                           WGL_PACK (FALSE),
                           WGL_PACK (FALSE));
    EPG_CHK_FAIL (i4_ret, i4_ret);

    /* Repaint union */
    i4_ret = _epg_view_desc_txt_repaint_union ();
    EPG_CHK_FAIL (i4_ret, i4_ret);

    return EPGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_txt_first_page
 *
 * Description: This API displays the first page of the description text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_txt_first_page (VOID)
{
    INT32       i4_ret;

    /* Go to first page */
    i4_ret = c_wgl_do_cmd (t_g_view.h_desc_txt,
                           WGL_CMD_TEXT_SET_DISPLAY_START,
                           WGL_PACK (0),
                           WGL_PACK (NULL));
    EPG_CHK_FAIL (i4_ret, i4_ret);

    /* Repaint union */
    i4_ret = _epg_view_desc_txt_repaint_union ();
    EPG_CHK_FAIL (i4_ret, i4_ret);

    return EPGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_txt_get_num_lines
 *
 * Description: This API gets the total lines of the description text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_txt_get_num_lines (UINT16*    pui2_lines)
{
    return  c_wgl_do_cmd (t_g_view.h_desc_txt,
                          WGL_CMD_TEXT_GET_TOTAL_LINES,
                          WGL_PACK (pui2_lines),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_desc_txt_get_num_pages
 *
 * Description: This API gets the total pages of the description text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_desc_txt_get_num_pages (UINT16*    pui2_pages)
{
    INT32     i4_rc;
    UINT16    ui2_i, ui2_lines, ui2_pages;

    ui2_pages = 0;

    i4_rc = c_wgl_do_cmd (t_g_view.h_desc_txt,
                          WGL_CMD_TEXT_GET_TOTAL_LINES,
                          WGL_PACK (& ui2_lines),
                          NULL);

    if (i4_rc == WGLR_OK)
    {
        ui2_i = 0;

        while (ui2_i < ui2_lines)
        {
            ui2_pages ++;
            ui2_i += DESC_TXT_LINES_PER_PAGE;
        }
    }

    *pui2_pages = ui2_pages;

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_page_txt_set_visibility
 *
 * Description: This API sets visibility to page text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_page_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_page_txt, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_page_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_page_txt_set_text
 *
 * Description: This API sets text to the page text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_page_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_page_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_page_txt_repaint
 *
 * Description: This API repaints the page text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_page_txt_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_page_txt, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_txt_set_visibility
 *
 * Description: This API sets visibility to password text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_passwd_txt, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_passwd_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_txt_set_text
 *
 * Description: This API sets text to the password text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_passwd_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_txt_repaint
 *
 * Description: This API repaints the password text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_txt_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_passwd_txt, NULL, TRUE);
}

#ifdef APP_EPG_FULL_VIDEO
/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_alarm_txt_set_visibility
 *
 * Description: This API sets visibility to password text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_alarm_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* Visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_passwd_alarm_txt, WGL_SW_NORMAL);
    }
    else /* Hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_passwd_alarm_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_alarm_txt_set_text
 *
 * Description: This API sets text to the password text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_alarm_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_passwd_alarm_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_passwd_alarm_txt_repaint
 *
 * Description: This API repaints the password text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_passwd_alarm_txt_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_passwd_alarm_txt, NULL, TRUE);
}
#endif
/*-----------------------------------------------------------------------------
 * Name: epg_view_chn_txt_set_visibility
 *
 * Description: This API sets visibility to channel text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_chn_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_chn_txt, WGL_SW_NORMAL);
    }
    else /* hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_chn_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_chn_txt_set_text
 *
 * Description: This API sets text to the channel info text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_chn_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_chn_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_chn_txt_repaint
 *
 * Description: This API repaints the channel info text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_chn_txt_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_chn_txt, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_type_lst_set_visibility
 *
 * Description: This API sets visibility to type list widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_type_lst_set_visibility (BOOL    b_show)
{
    if (b_show) /* visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_type_lst, WGL_SW_NORMAL);
    }
    else /* hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_type_lst, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_type_lst_set_title
 *
 * Description: This API sets the title of the type list.
 *
 * Inputs:  pw2s_text           Title text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_type_lst_set_title (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_type_lst,
                          WGL_CMD_LB_SET_TITLE_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_type_lst_set_elems
 *
 * Description: This API sets the elements data for a given range to the type
 *              list.
 *
 * Inputs:  ui2_start           Start index
 *          ui2_end             End index.
 *          pt_elem_data        Elements data.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_type_lst_set_elems (UINT16                 ui2_start,
                                   UINT16                 ui2_end,
                                   WGL_LB_ELEM_DATA_T*    pt_elem_data)
{
    return  c_wgl_do_cmd (t_g_view.h_type_lst,
                          WGL_CMD_LB_SET_ELEMS_BY_RANGE,
                          WGL_PACK_2 (ui2_start, ui2_end),
                          WGL_PACK (pt_elem_data));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_type_lst_get_hlt_idx
 *
 * Description: This API gets the index of highlighted element in type list.
 *
 * Inputs:  -
 *
 * Outputs: pui2_hlt_idx        Highlighted index.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_type_lst_get_hlt_idx (UINT16*    pui2_hlt_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_type_lst,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK (pui2_hlt_idx),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_type_lst_hlt_elem
 *
 * Description: This API highlights an elements in the type list.
 *
 * Inputs:  ui2_idx             The index of element to be highlighted.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_type_lst_hlt_elem (UINT16    ui2_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_type_lst,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK (ui2_idx),
                          WGL_PACK (0));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_type_lst_repaint
 *
 * Description: This API repaints the type list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_type_lst_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_type_lst, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_subtype_lst_set_visibility
 *
 * Description: This API sets visibility to subtype list widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_subtype_lst_set_visibility (BOOL    b_show)
{
    if (b_show) /* visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_subtype_lst, WGL_SW_NORMAL);
    }
    else /* hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_subtype_lst, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_subtype_lst_set_title
 *
 * Description: This API sets the title of the subtype list.
 *
 * Inputs:  pw2s_text           Title text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_subtype_lst_set_title (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_subtype_lst,
                          WGL_CMD_LB_SET_TITLE_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_type_lst_set_elems
 *
 * Description: This API sets the elements data for a given range to the subtype
 *              list.
 *
 * Inputs:  ui2_start           Start index
 *          ui2_end             End index.
 *          pt_elem_data        Elements data.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_subtype_lst_set_elems (UINT16                 ui2_start,
                                      UINT16                 ui2_end,
                                      WGL_LB_ELEM_DATA_T*    pt_elem_data)
{
    return  c_wgl_do_cmd (t_g_view.h_subtype_lst,
                          WGL_CMD_LB_SET_ELEMS_BY_RANGE,
                          WGL_PACK_2 (ui2_start, ui2_end),
                          WGL_PACK (pt_elem_data));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_subtype_lst_hlt_elem
 *
 * Description: This API highlights an elements in the subtype list.
 *
 * Inputs:  ui2_idx             The index of element to be highlighted.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_subtype_lst_hlt_elem (UINT16    ui2_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_subtype_lst,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK (ui2_idx),
                          WGL_PACK (0));
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_subtype_lst_get_hlt_idx
 *
 * Description: This API gets the index of highlighted element in subtype list.
 *
 * Inputs:  -
 *
 * Outputs: pui2_hlt_idx        Highlighted index.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_subtype_lst_get_hlt_idx (UINT16*    pui2_hlt_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_subtype_lst,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK (pui2_hlt_idx),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_subtype_lst_repaint
 *
 * Description: This API repaints the subtype list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_subtype_lst_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_subtype_lst, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_subtype_lst_set_elem_num
 *
 * Description: This API sets the number of elements to the subtype list.
 *
 * Inputs:  ui2_elem_num        Element number to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_subtype_lst_set_elem_num (UINT16 ui2_elem_num)
{
    return  c_wgl_do_cmd (t_g_view.h_subtype_lst,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK (ui2_elem_num),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description: 
 * Inputs: -
 * Outputs: -
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32  epg_view_adjust_background_by_config(EPG_CONFIG_T* pt_config)
{
    EPG_AV_CONFIG_T e_av_cfg = EPG_AV_CONFIG_WITH_FULL_VIDEO;
    GL_COLOR_T t_color_main_frm_bk = t_g_epg_color_main_frm_bk;
        
    if (NULL == pt_config)
    {
        return EPGR_FAIL;
    }

    /*e_av_cfg = pt_config->e_av_config;*/

    /* main frame */

    switch (e_av_cfg)
    {
        case EPG_AV_CONFIG_WITH_FULL_VIDEO:
        {
            /* Set background color to transparent */
            t_color_main_frm_bk = t_g_epg_color_main_frm_bk;
        }
        break;

        case EPG_AV_CONFIG_NO_VIDEO_AUDIO:
        {
            /* Set background color to black to blink video */
            t_color_main_frm_bk = EPG_MAIN_FRM_BK_COLOR_BLACK;
        }
        break;

        case EPG_AV_CONFIG_WITH_PIP_VIDEO:
        {
            /* Set background color to transparent */
            t_color_main_frm_bk = t_g_epg_color_main_frm_bk;
        }
        break;

		default:
		break;
        
    }

    a_wdk_set_clr_bk(t_g_view.h_main_frm, 
                    &t_color_main_frm_bk, 
                    &t_color_main_frm_bk, 
                    &t_color_main_frm_bk);
    
    return EPGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: epg_view_init
 *
 * Description: This API initializes all the widgets and sets attributes, colors,
 *              images to the widgets.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_view_init (VOID)
{
    /* Reset variables of view. */
    c_memset (& t_g_view, 0, sizeof(EPG_VIEW_T));

    /* Initialize font. */
    if (c_fe_has_font (EPG_FONT_NAME, FE_FNT_STYLE_REGULAR))
    {
        c_strcpy (t_g_view.s_font_name, EPG_FONT_NAME);
    }

    /* Initialize colors. */
    RET_ON_ERR (epg_color_init ());

    /* Initialize images. */
    RET_ON_ERR (epg_image_init ());

    /* Create widgets. */
    RET_ON_ERR (_epg_view_create_main_frm ());        /* main frame */
    RET_ON_ERR (_epg_view_create_passwd_frm ());      /* password frame */
    RET_ON_ERR (_epg_view_create_desc_frm ());        /* description frame */
    RET_ON_ERR (_epg_view_create_desc_bk_frm ());     /* description background frame */
    RET_ON_ERR (_epg_view_create_video_frm ());       /* video frame */

    RET_ON_ERR (_epg_view_create_passwd_edit ());     /* password edit */
    RET_ON_ERR (_epg_view_create_retrieve_icon ());   /* retrieving icon */

    RET_ON_ERR (_epg_view_create_retrieve_txt ());    /* retrieving text */
    RET_ON_ERR (_epg_view_create_time_txt ());        /* time text */
    RET_ON_ERR (_epg_view_create_prg_txt ());         /* program text */
    RET_ON_ERR (_epg_view_create_video_txt ());       /* video text */
    RET_ON_ERR (_epg_view_create_page_txt ());        /* page index text */
    RET_ON_ERR (_epg_view_create_desc_txt ());        /* program description text */
    RET_ON_ERR (_epg_view_create_passwd_txt ());      /* password text */
    RET_ON_ERR (_epg_view_create_dci_hts ());         /* direct channel input hyper text */

#ifdef APP_EPG_FULL_VIDEO
    RET_ON_ERR (_epg_view_create_passwd_alarm_txt ());      /* password alarm text */
#endif

    RET_ON_ERR (_epg_view_create_chn_lst ());         /* channel list */
    RET_ON_ERR (_epg_view_create_prg_lst ());         /* program list */
    RET_ON_ERR (_epg_view_create_surf_lst ());        /* surfing list */
    RET_ON_ERR (_epg_view_create_desc_lst ());        /* program description list */
    RET_ON_ERR (_epg_view_create_icon_lst ());        /* icons list */
    RET_ON_ERR (_epg_view_create_help_lst ());        /* help list */

    RET_ON_ERR (_epg_view_create_chn_txt ());         /* channel info text */

#ifdef APP_EPG_THEME_SEARCH

    RET_ON_ERR (_epg_view_create_type_lst ());        /* type list */
    RET_ON_ERR (_epg_view_create_subtype_lst ());     /* subtype list */

#endif /* APP_EPG_THEME_SEARCH */

    RET_ON_ERR (_epg_view_create_base_frm ());        /* base map frame */

    return  0;
}
