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
 * $RCSfile: pic_mode_view_list.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_537X_SUPPORT

#include "u_common.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_gl.h"
#include "c_handle.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_svctx.h"

#include "nav/pic_mode/pic_mode.h"
#include "nav/nav_common.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"
#include "res/nav/pic_mode/pic_mode_view_list_custom.h"
#include "res/wdk/wdk_img.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)

typedef struct _NAV_PIC_MODE_VIEW_T
{
    /* Internal Control */

    NAV_PIC_MODE_T*             pt_ctrl;
    BOOL                        b_is_refreshing;     /* FALSE -> Do Process Notification */
                                                     /* TRUE  -> No Process Notification */
    /* Widgets */

    HANDLE_T                    h_frame;
    HANDLE_T                    h_listbox;
	HANDLE_T     				h_icon_up;
    HANDLE_T     				h_icon_down;

    /* Widgets Resource: Template image */

    WGL_HIMG_TPL_T              h_lb_bk_img;
    WGL_HIMG_TPL_T              h_lb_ht_img;

} NAV_PIC_MODE_VIEW_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_PIC_MODE_VIEW_T t_g_nav_pic_mode_view       = {0};

static BOOL                b_g_toggle_by_btn_smart_pic = FALSE;
static BOOL                b_g_exit_by_btn_smart_pic   = FALSE;
static BOOL                b_g_exit_by_btn_select      = FALSE;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_frame_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );

static INT32 _nav_pic_mode_view_listbox_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );

static INT32  __pic_mode_listbox_load_skin(VOID);

static INT32 _nav_pic_mode_update_arrow_icon (const UINT16 ui2_hlt_idx);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: repaint the frame
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  __pic_mode_repaint(VOID)
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;
    INT32        i4_ret;

    i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, TRUE);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: create image handle
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 __pic_mode_create_image(VOID)
{
    INT32    i4_ret;
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;

    /* listbox background image */
    /* listbox bar (highlight image) */
    i4_ret = nav_pic_mode_custom_view_list_create_image(&pt_view->h_lb_bk_img,
                                                        &pt_view->h_lb_ht_img);

    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: create frame handle
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 __pic_mode_create_frame(
                    HANDLE_T                       h_parent,
                    INT32                          i4_frame_x_offset,
                    INT32                          i4_frame_y_offset
                    )
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;
    GL_RECT_T                           t_rect;
    INT32                               i4_ret;

    /* create channel frame */
    SET_RECT_BY_SIZE(&t_rect,
                     NAV_PIC_MODE_LST_FM_LEFT + i4_frame_x_offset,
                     NAV_PIC_MODE_LST_FM_TOP  + i4_frame_y_offset,
                     NAV_PIC_MODE_LST_FM_WIDTH,
                     NAV_PIC_MODE_LST_FM_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _nav_pic_mode_view_frame_wdgt_proc_fct,
                                 DEFAULT_BK_ALPHA,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK),
                                 pt_view,
                                 &pt_view->h_frame);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_create_widget(HT_WGL_WIDGET_FRAME) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: create listbox handle
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 __pic_mode_create_listbox(
                    HANDLE_T                       h_parent,
                    UINT16                         ui2_elem_num
                    )
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;
    INT32                                 i4_ret;
    GL_RECT_T                             t_rect;
    WGL_LB_INIT_T                         t_init_info;
    WGL_LB_TITLE_INFO_T                   t_title_info;
    WGL_LB_COL_INIT_T                     at_cols[1];
    WGL_LB_ITEM_T                         at_items[1];

    /* Picture Mode column */
    at_cols[0].e_col_type         = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align          = NAV_PIC_MODE_LST_BOX_NAME_ALIGNMENT;
    at_cols[0].ui2_width          = NAV_PIC_MODE_LST_BOX_NAME_WIDHT;
    at_cols[0].ui2_max_text_len   = NAV_PIC_MODE_LST_BOX_NAME_MAX_TEXT_LEN;

    t_init_info.ui4_style                   = NAV_PIC_MODE_LST_BOX_STYLE;
    t_init_info.ui2_max_elem_num            = 20;
    t_init_info.ui2_elem_size               = NAV_PIC_MODE_LST_BOX_ELEM_HEIGHT;
    t_init_info.ui2_elem_distance           = NAV_PIC_MODE_LST_BOX_ELEM_DTANCE;
    t_init_info.ui1_col_num                 = 1;
    t_init_info.at_cols                     = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     NAV_PIC_MODE_LST_BOX_LEFT,
                     NAV_PIC_MODE_LST_BOX_TOP,
                     NAV_PIC_MODE_LST_BOX_WIDTH,
                     NAV_PIC_MODE_LST_BOX_HEIGHT(NAV_PIC_MODE_VISIABLE_NUM));

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _nav_pic_mode_view_listbox_wdgt_proc_fct,
                                 DEFAULT_BK_ALPHA,
                                 &t_init_info,
                                 NULL,
                                 &pt_view->h_listbox);

    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_create_widget(HT_WGL_WIDGET_LIST_BOX) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        pt_view->h_listbox = NULL_HANDLE;
        return NAVR_FAIL;
    }

    /* Title Alignment and Rect */
    t_title_info.ui1_align = NAV_PIC_MODE_LST_TITLE_ALIGN;

    SET_RECT_BY_SIZE(&t_title_info.t_rect,
                     NAV_PIC_MODE_LST_TITLE_LEFT,
                     NAV_PIC_MODE_LST_TITLE_TOP,
                     NAV_PIC_MODE_LST_TITLE_WIDTH,
                     NAV_PIC_MODE_LST_TITLE_HEIGHT);

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_TITLE_INFO,
                          (VOID*)&t_title_info,
                          (VOID*)0);

    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* Set Skin */
    i4_ret = __pic_mode_listbox_load_skin();
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* Set refreshing flag, avoid notify to be processed */
    pt_view->b_is_refreshing = TRUE;

    /* Insert one nothing field first */
    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = NULL;

	i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
	                      WGL_CMD_LB_APPEND_ELEM,
	                      WGL_PACK(at_items),
	                      NULL);
	NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* Un-set refreshing flag */
    pt_view->b_is_refreshing = FALSE;

    /* Launch Customer layer setting */
    /* For additional effect for Scroll Bar, etc. */
    nav_pic_mode_custom_view_list_create_listbox_postinit(pt_view->h_listbox);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: set skin / bk images
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  __pic_mode_listbox_load_skin(VOID)
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;
    WGL_COLOR_INFO_T                         t_clr_info;
    WGL_INSET_T                              t_inset;
    WGL_LB_COLOR_ELEM_SET_T                  t_color_elem;
    WGL_IMG_INFO_T                           t_img_info;
    WGL_LB_IMG_ELEM_SET_T                    t_img_elem = {0};
    INT32                                    i4_ret;

   /* listbox view port background color */
    t_clr_info.e_type              = WGL_COLOR_SET_STANDARD;

    t_clr_info.u_color_data.t_standard.t_disable   = t_g_nav_pic_mode_color_listbox_vp_bk;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_nav_pic_mode_color_listbox_vp_bk;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_nav_pic_mode_color_listbox_vp_bk;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_VP_BK),
                          WGL_PACK(&t_clr_info));
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* listbox background image */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_view->h_lb_bk_img;
    t_img_info.u_img_data.t_standard.t_disable   = pt_view->h_lb_bk_img;
    t_img_info.u_img_data.t_standard.t_highlight = pt_view->h_lb_bk_img;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* element image background */
    t_img_elem.h_highlight           = pt_view->h_lb_ht_img;
    t_img_elem.h_highlight_unfocus   = pt_view->h_lb_ht_img;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                          WGL_PACK(& t_img_elem),
                          NULL);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* element background colors */
    t_color_elem.t_normal              = t_g_nav_pic_mode_color_listbox_elem_bk;
    t_color_elem.t_disable             = t_g_nav_pic_mode_color_listbox_elem_bk;
    t_color_elem.t_highlight           = t_g_nav_pic_mode_color_listbox_elem_bk;
    t_color_elem.t_highlight_unfocus   = t_g_nav_pic_mode_color_listbox_elem_bk;
    t_color_elem.t_pushed              = t_g_nav_pic_mode_color_listbox_elem_bk;
    t_color_elem.t_selected            = t_g_nav_pic_mode_color_listbox_elem_bk;
    t_color_elem.t_selected_disable    = t_g_nav_pic_mode_color_listbox_elem_bk;

    i4_ret = c_wgl_do_cmd (pt_view->h_listbox,
                           WGL_CMD_LB_SET_ELEM_COLOR,
                           WGL_PACK(WGL_CLR_BK),
                           WGL_PACK(&t_color_elem));
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /*column bk color*/
    t_color_elem.t_normal              = t_g_nav_pic_mode_color_listbox_col_bk;
    t_color_elem.t_disable             = t_g_nav_pic_mode_color_listbox_col_bk;
    t_color_elem.t_highlight           = t_g_nav_pic_mode_color_listbox_col_bk;
    t_color_elem.t_highlight_unfocus   = t_g_nav_pic_mode_color_listbox_col_bk;
    t_color_elem.t_pushed              = t_g_nav_pic_mode_color_listbox_col_bk;
    t_color_elem.t_selected            = t_g_nav_pic_mode_color_listbox_col_bk;
    t_color_elem.t_selected_disable    = t_g_nav_pic_mode_color_listbox_col_bk;

    /* one column only */

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_BK),
                          WGL_PACK(&t_color_elem));
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /*set picture mode text color*/
    t_color_elem.t_normal              = t_g_nav_pic_mode_color_listbox_elem_fg;
    t_color_elem.t_disable             = t_g_nav_pic_mode_color_listbox_elem_fg;
    t_color_elem.t_highlight           = t_g_nav_pic_mode_color_listbox_elem_fg_hlt;
    t_color_elem.t_highlight_unfocus   = t_g_nav_pic_mode_color_listbox_elem_fg_hlt;
    t_color_elem.t_pushed              = t_g_nav_pic_mode_color_listbox_elem_fg;
    t_color_elem.t_selected            = t_g_nav_pic_mode_color_listbox_elem_fg;
    t_color_elem.t_selected_disable    = t_g_nav_pic_mode_color_listbox_elem_fg;

    i4_ret = c_wgl_do_cmd (pt_view->h_listbox,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(0, WGL_CLR_TEXT),
                           WGL_PACK(&t_color_elem));
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /*Title's foreground color*/
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = t_g_nav_pic_mode_color_listbox_title_fg;
    t_clr_info.u_color_data.t_standard.t_enable      = t_g_nav_pic_mode_color_listbox_title_fg;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_g_nav_pic_mode_color_listbox_title_fg;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_LB_TITLE_FG,
                          &t_clr_info);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /*Title's background color*/
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = t_g_nav_pic_mode_color_listbox_title_bk;
    t_clr_info.u_color_data.t_standard.t_enable      = t_g_nav_pic_mode_color_listbox_title_bk;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_g_nav_pic_mode_color_listbox_title_bk;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_LB_TITLE_BK,
                          &t_clr_info);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* set Picture mode's font */
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_COL_FONT,
                          WGL_PACK(0),
                          WGL_PACK(&t_g_pic_mode_text_font_info));
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* set Title's font */
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_FONT,
                          (VOID*)&t_g_pic_mode_title_font_info,
                          NULL);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* set Picture Mode's inset */
    NAV_PIC_MODE_LST_BOX_NAME_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(0),
                          WGL_PACK(&t_inset));
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* set content inset */
    NAV_PIC_MODE_LST_BOX_CONTENT_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* set element inset */
    NAV_PIC_MODE_LST_BOX_ELEM_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          WGL_PACK(&t_inset),
                          NULL);

    /* Key Map */
    /* Need not to change */

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Process the notify and do the API provided by Ctrl.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 __pic_mode_listbox_on_notify(WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_LB_ELEM_SEL:
        {
            if (pt_nfy_data->u.t_lb_elem_sel.b_is_selected)
            {
            	DBG_INFO(("[PQ] --- ui2_elem_idx: %d.\n",pt_nfy_data->u.t_lb_elem_sel.ui2_elem_idx));

				_nav_pic_mode_update_arrow_icon(pt_nfy_data->u.t_lb_elem_sel.ui2_elem_idx);

                nav_pic_mode_ctrl_set_index(pt_nfy_data->u.t_lb_elem_sel.ui2_elem_idx);
            }
        }
        break;
    default:
        break;
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Return the judgement for key.
 *              Currently, it listens BTN_P_EFFECT
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _nav_pic_mode_view_is_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    return nav_pic_mode_view_custom_is_key_handler(ui4_key_code);
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Activate the view, focus on the "Listbox"
 *              Currently, it listens BTN_P_EFFECT.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_activate(
                    UINT32                      ui4_key_code
                    )
{
    NAV_PIC_MODE_VIEW_T*  pt_view = &t_g_nav_pic_mode_view;
    INT32                 i4_ret;

    i4_ret = c_wgl_float (pt_view->h_frame, TRUE, FALSE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Let's focus on the listbox */
    i4_ret = c_wgl_set_focus(pt_view->h_listbox, WGL_NO_AUTO_REPAINT);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_RECURSIVE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_hide(
                    VOID
                    )
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;
    INT32             i4_ret;

    i4_ret = c_wgl_float (pt_view->h_frame, FALSE, FALSE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_rcu_key_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_pic_mode_view_rcu_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;

    switch(ui4_key_code) {
    case BTN_P_EFFECT:
    case BTN_CURSOR_UP:
    case BTN_CURSOR_DOWN:
        nav_pic_mode_reset_timer(pt_view->pt_ctrl);
        break;
    case BTN_EXIT:
        nav_hide_component(NAV_COMP_ID_PICTURE_EFFECT);
        break;
    case BTN_SELECT:
        break;
    default:
        nav_rcu_key_handler(ui4_key_code);
        break;
    }
}

/*---------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_view_frame_wdgt_proc_fct(
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_frame_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32 i4_ret;
    NAV_PIC_MODE_VIEW_T*  pt_view = &t_g_nav_pic_mode_view;

    /* Listen the notify and do the actual work by Ctrl's API */
    switch (ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
            HANDLE_T h_source = (HANDLE_T)pv_param1;
            WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)pv_param2;

            if(pt_view->b_is_refreshing != TRUE)
            {
                /* Not refreshing, dispatch the notify */
                if(h_source == pt_view->h_listbox)
                {
                    __pic_mode_listbox_on_notify(pt_nfy_data);
                }
            }

        }
        break;
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: ListBox's wdgt proc_fct.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_listbox_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32 i4_ret;
    BOOL  b_processed = FALSE;

    /* Can be customized */
    /* The listbox wdgt proc fct */
    i4_ret = nav_pic_mode_custom_view_list_listbox_wdgt_proc_fct(h_widget,
                                                                 ui4_msg,
                                                                 pv_param1,
                                                                 pv_param2,
                                                                 &b_processed);
    if(b_processed)
    {
        return NAVR_OK;
    }

    if(ui4_msg == WGL_MSG_KEY_DOWN)
    {
        /* Can be customized */
        /* Translate BTN_SMART_PIC => BTN_CURSOR_DOWN */
        if(b_g_toggle_by_btn_smart_pic)
        {
            if( (UINT32) pv_param1 == BTN_P_EFFECT )
            {
                pv_param1 = (VOID *) BTN_CURSOR_DOWN;
            }
        }

        /* Can be customized */
        /* Translate BTN_SMART_PIC to EXIT */
        if(b_g_exit_by_btn_smart_pic)
        {
            if( (UINT32) pv_param1 == BTN_P_EFFECT )
            {
                nav_hide_component(NAV_COMP_ID_PICTURE_EFFECT);
                return WGLR_OK;    /* Return Directly */
            }
        }

        /* Can be customized */
        /* Translate BTN_SELECT to EXIT */
        if(b_g_exit_by_btn_select)
        {
            if( (UINT32) pv_param1 == BTN_SELECT )
            {
                nav_hide_component(NAV_COMP_ID_PICTURE_EFFECT);
                nav_pic_mode_ctrl_update_index();
                return WGLR_OK;    /* Return Directly */
            }
        }
    }

    switch(ui4_msg) {
    case WGL_MSG_KEY_DOWN:

        /* Run NAV default key handler first */
        _nav_pic_mode_view_rcu_key_handler((UINT32)pv_param1);
        break;

    default:
        break;
    }

    /* Run WIDGET default key handler next */
    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: create up/down arrow handle
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 __pic_mode_create_arrow(
					HANDLE_T					   h_parent
					)
{
	NAV_PIC_MODE_VIEW_T* 	pt_view = &t_g_nav_pic_mode_view;
    INT32                	i4_ret;
    GL_RECT_T           	t_rect;

	/* create page up icon */
    SET_RECT_BY_SIZE(&t_rect,
                    NAV_PIC_MODE_UP_ICON_LEFT,
                    NAV_PIC_MODE_UP_ICON_TOP,
                    NAV_PIC_MODE_UP_ICON_WIDTH,
                    NAV_PIC_MODE_UP_ICON_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_listbox,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_icon_up
                    );
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

	/* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_view->h_icon_up,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

	/* create page dn icon */
    SET_RECT_BY_SIZE(&t_rect,
                    NAV_PIC_MODE_DN_ICON_LEFT,
                    NAV_PIC_MODE_DN_ICON_TOP,
                    NAV_PIC_MODE_DN_ICON_WIDTH,
                    NAV_PIC_MODE_DN_ICON_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_listbox,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_icon_down
                    );
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

	/* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_view->h_icon_down,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

	return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: __pic_mode_set_arrow_icon
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
static INT32 __pic_mode_set_icon (HANDLE_T h_icon, HANDLE_T h_img_tpl)
{
    WGL_IMG_INFO_T                  t_img_info;
    INT32                           i4_ret;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = h_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = h_img_tpl;

    i4_ret = c_wgl_do_cmd(h_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_init(
                    NAV_PIC_MODE_T*                pt_ctrl,
                    HANDLE_T                       h_canvas,
                    INT32                          i4_frame_x_offset,
                    INT32                          i4_frame_y_offset,
                    UINT16                         ui2_elem_num
                    )
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;
    INT32                i4_ret = 0;

    /* Save the ctrl to view */
    pt_view->pt_ctrl = pt_ctrl;

    /* create image */
    __pic_mode_create_image();

    /* create frame */
    __pic_mode_create_frame(h_canvas,
                            i4_frame_x_offset,
                            i4_frame_y_offset);
    /* create listbox */
    __pic_mode_create_listbox(pt_view->h_frame,
                              ui2_elem_num);

	/* create up/down arrow */
    __pic_mode_create_arrow(pt_view->h_frame);

    i4_ret = c_wgl_float (pt_view->h_frame, TRUE, FALSE);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_show(pt_view->h_frame, WGL_SW_HIDE);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* Customization Environment */
    b_g_toggle_by_btn_smart_pic = NAV_PIC_MODE_TOGGLE_BY_BTN_SMART_PIC;
    b_g_exit_by_btn_smart_pic   = NAV_PIC_MODE_EXIT_BY_BTN_SMART_PIC;
    b_g_exit_by_btn_select      = NAV_PIC_MODE_EXIT_BY_BTN_SELECT;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_deinit(
                    VOID
                    )
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;

    c_wgl_destroy_widget(pt_view->h_frame);
    c_wgl_destroy_widget(pt_view->h_listbox);
	c_wgl_destroy_widget(pt_view->h_icon_up);
    c_wgl_destroy_widget(pt_view->h_icon_down);
    c_wgl_img_tpl_destroy(pt_view->h_lb_bk_img);
    c_wgl_img_tpl_destroy(pt_view->h_lb_ht_img);

    pt_view->pt_ctrl     = NULL;
    pt_view->h_frame     = NULL_HANDLE;
    pt_view->h_listbox   = NULL_HANDLE;
	pt_view->h_icon_up   = NULL_HANDLE;
	pt_view->h_icon_down = NULL_HANDLE;
    pt_view->h_lb_bk_img = NULL_HANDLE;
    pt_view->h_lb_ht_img = NULL_HANDLE;

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_pic_mode_update_arrow_visibility
 *
 * Description: Set the _nav_pic_mode_update_arrow index
 *
 * Inputs: ui2_num 	visiable num
 *
 * Outputs: -
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_update_arrow_visibility(UINT16    ui2_num)
{
	INT32    				i4_ret;
	NAV_PIC_MODE_VIEW_T* 	pt_view = &t_g_nav_pic_mode_view;

	if (ui2_num > NAV_PIC_MODE_VISIABLE_NUM)
    {
        i4_ret = c_wgl_set_visibility(pt_view->h_icon_up,
                                      WGL_SW_NORMAL);
        NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_view->h_icon_down,
                                      WGL_SW_NORMAL);
        NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_set_visibility(pt_view->h_icon_up,
                                      WGL_SW_HIDE);
        NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_view->h_icon_down,
                                      WGL_SW_HIDE);
        NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);
    }

	return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_pic_mode_update_arrow_icon
 *
 * Description: Set the _nav_pic_mode_update_arrow index
 *
 * Inputs: ui2_hlt_idx 	current highlight index
 *
 * Outputs: -
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_update_arrow_icon (const UINT16 ui2_hlt_idx)
{
	INT32    				i4_ret;
	UINT16                  ui2_elem_num = 0;
	NAV_PIC_MODE_VIEW_T* 	pt_view = &t_g_nav_pic_mode_view;

	i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&ui2_elem_num),
                          NULL);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

	if (ui2_elem_num <= NAV_PIC_MODE_VISIABLE_NUM)
	{
		return NAVR_OK;
	}

	if (ui2_hlt_idx <= 0)
	{
		__pic_mode_set_icon(pt_view->h_icon_up, NULL_HANDLE);
		__pic_mode_set_icon(pt_view->h_icon_down, h_g_wdk_cnt_indctr_img[1]);
	}
	else if (ui2_hlt_idx >= ui2_elem_num - 1)
	{
		__pic_mode_set_icon(pt_view->h_icon_up, h_g_wdk_cnt_indctr_img[0]);
		__pic_mode_set_icon(pt_view->h_icon_down, NULL_HANDLE);
	}
	else
	{

		__pic_mode_set_icon(pt_view->h_icon_up, h_g_wdk_cnt_indctr_img[0]);
		__pic_mode_set_icon(pt_view->h_icon_down, h_g_wdk_cnt_indctr_img[1]);
	}

	i4_ret = c_wgl_repaint(pt_view->h_icon_up, NULL, TRUE);
	NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_repaint(pt_view->h_icon_down, NULL, TRUE);
	NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

	return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Set the _nav_pic_mode_view_set_elem_num index
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_set_elem_num(UINT16    ui2_num)
{
	INT32    				i4_ret;
	NAV_PIC_MODE_VIEW_T* 	pt_view = &t_g_nav_pic_mode_view;

	/* clean brand listbox info */
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
						  WGL_CMD_LB_DEL_ALL,
						  NULL,
						  NULL);
	NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

	/* set listbox item number */
	i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK(ui2_num),
                          NULL);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

	/* update up/down arrow icon */
	i4_ret = _nav_pic_mode_update_arrow_visibility(ui2_num);
	NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Set the highlight index
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_set_hlt_index(UINT16    ui2_idx)
{
    INT32    				i4_ret;
    NAV_PIC_MODE_VIEW_T 	*pt_view = &t_g_nav_pic_mode_view;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(ui2_idx),
                          NULL);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                          NULL,
                          NULL);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

	i4_ret = _nav_pic_mode_update_arrow_icon(ui2_idx);
	NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    /* [DTV00120546] [5391 US]"picture mode" display wrong */
    /* Repaint to show the highlight change immediately. */
    __pic_mode_repaint();

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Set the index's text
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_set_index_text(UINT16    ui2_idx,
                                               UTF16_T*  pw2s_text)
{
    INT32    i4_ret;
    NAV_PIC_MODE_VIEW_T *pt_view = &t_g_nav_pic_mode_view;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(ui2_idx, 0),
                          WGL_PACK(pw2s_text));
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Set the refreshing flag.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_set_is_refreshing(BOOL      b_is_refreshing)
{
    NAV_PIC_MODE_VIEW_T *pt_view = &t_g_nav_pic_mode_view;

    /* Set the b_enable status to indicate whether do notification or not */
    pt_view->b_is_refreshing = b_is_refreshing;

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Set the title text.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_set_title_text(UTF16_T*  pw2s_title)

{
    INT32    i4_ret;
    NAV_PIC_MODE_VIEW_T *pt_view = &t_g_nav_pic_mode_view;

    /*set title*/
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_TITLE_TEXT,
                          (VOID*)pw2s_title,
                          (VOID*)((NULL == pw2s_title) ? 0 : c_uc_w2s_strlen(pw2s_title)));
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_sleep_view_register_default_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_pic_mode_view_register_list_hdlr(
                    NAV_PIC_MODE_VIEW_HDLR_T*      pt_view_hdlr
                    )
{
    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init              = _nav_pic_mode_view_init;
    pt_view_hdlr->pf_deinit            = _nav_pic_mode_view_deinit;
    pt_view_hdlr->pf_is_key_handler    = _nav_pic_mode_view_is_key_handler;
    pt_view_hdlr->pf_activate          = _nav_pic_mode_view_activate;
    pt_view_hdlr->pf_hide              = _nav_pic_mode_view_hide;
	pt_view_hdlr->pf_set_elem_num      = _nav_pic_mode_view_set_elem_num;
    pt_view_hdlr->pf_set_hlt_index     = _nav_pic_mode_view_set_hlt_index;
    pt_view_hdlr->pf_set_index_text    = _nav_pic_mode_view_set_index_text;
    pt_view_hdlr->pf_set_is_refreshing = _nav_pic_mode_view_set_is_refreshing;
    pt_view_hdlr->pf_set_title_text    = _nav_pic_mode_view_set_title_text;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

#endif /* APP_537X_SUPPORT */
