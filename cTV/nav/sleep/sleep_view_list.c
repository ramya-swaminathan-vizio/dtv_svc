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
 * $RCSfile: sleep_view.c,v $
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

#include "app_util/a_sleep_timer.h"
#include "a_sleep.h"
#include "sleep.h"
#include "nav/nav_common.h"
#include "res/nav/sleep/sleep_view_list_rc.h"
#include "res/menu2/menu_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"

#ifdef APP_AUD_DIRECT_ADJUST
    typedef enum
    {
        WGL_NOT_FORCE,
        WGL_FORCE_Change,
        WGL_FORCE_ShowOSD,
    }WGL_FORCE_State;
    //static WGL_FORCE_State       WGL_Force_Flag = WGL_NOT_FORCE ;
#endif

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)

typedef struct _NAV_SLEEP_VIEW_T
{
    /* Internal Control */

    NAV_SLEEP_T*             pt_ctrl;
    BOOL                     b_is_refreshing;     /* FALSE -> Do Process Notification */
                                                     /* TRUE  -> No Process Notification */
    /* Widgets */

    HANDLE_T                 h_frame;
    HANDLE_T                 h_listbox;

    /* Widgets Resource: Template image */

    WGL_HIMG_TPL_T           h_lb_bk_img;
    WGL_HIMG_TPL_T           h_lb_ht_img;
} NAV_SLEEP_VIEW_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_SLEEP_VIEW_T t_g_nav_sleep_view = {0};

static BOOL             b_g_exit_by_btn_select      = FALSE;

UINT16                  ui2_g_hlt_idx;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_view_frame_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );

static INT32 _nav_sleep_view_listbox_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );

static INT32  __sleep_listbox_load_skin(VOID);

static INT32 _nav_sleep_view_set_hlt_index(VOID);
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

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
static INT32 __sleep_create_image(VOID)
{
    INT32    i4_ret;
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;

    /* listbox background image */
    /* listbox bar (highlight image) */

    i4_ret = sleep_view_list_init_rc(&pt_view->h_lb_bk_img,
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
static INT32 __sleep_create_frame(
                    HANDLE_T                       h_parent,
                    INT32                          i4_frame_x_offset,
                    INT32                          i4_frame_y_offset
                    )
{
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;
    GL_RECT_T                           t_rect;
    INT32                               i4_ret;

    /* create channel frame */
    SET_RECT_BY_SIZE(&t_rect,
                     NAV_SLEEP_LST_FM_LEFT + i4_frame_x_offset,
                     NAV_SLEEP_LST_FM_TOP  + i4_frame_y_offset,
                     NAV_SLEEP_LST_FM_WIDTH,
                     NAV_SLEEP_LST_FM_HEIGHT+NAV_SLEEP_LST_TITLE_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _nav_sleep_view_frame_wdgt_proc_fct,
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
static INT32 __sleep_create_listbox(
                    HANDLE_T                       h_parent,
                    UINT8                          ui1_elem_num
                    )
{
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;
    INT32                                 i4_ret;
    UINT16                                ui2_idx;
    GL_RECT_T                             t_rect;
    WGL_LB_INIT_T                         t_init_info;
    WGL_LB_TITLE_INFO_T                   t_title_info;
    WGL_LB_COL_INIT_T                     at_cols[1];

    WGL_LB_ITEM_T                         at_items[1];


    /* Picture Mode column */
    at_cols[0].e_col_type         = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align          = NAV_SLEEP_LST_BOX_NAME_ALIGNMENT;
    at_cols[0].ui2_width          = NAV_SLEEP_LST_BOX_NAME_WIDHT;
    at_cols[0].ui2_max_text_len   = NAV_SLEEP_LST_BOX_NAME_MAX_TEXT_LEN;

    t_init_info.ui4_style                   = NAV_SLEEP_LST_BOX_STYLE;
    t_init_info.ui2_max_elem_num            = ui1_elem_num;
    t_init_info.ui2_elem_size               = NAV_SLEEP_LST_BOX_ELEM_HEIGHT;
    t_init_info.ui2_elem_distance           = NAV_SLEEP_LST_BOX_ELEM_DTANCE;
    t_init_info.ui1_col_num                 = 1;
    t_init_info.at_cols                     = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     NAV_SLEEP_LST_BOX_LEFT,
                     NAV_SLEEP_LST_BOX_TOP,
                     NAV_SLEEP_LST_BOX_WIDTH,
                     NAV_SLEEP_LST_BOX_HEIGHT(ui1_elem_num));

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _nav_sleep_view_listbox_wdgt_proc_fct,
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

    c_wgl_set_visibility (pt_view->h_listbox, WGL_SW_NORMAL) ;

    /* Title Alignment and Rect */
    t_title_info.ui1_align = NAV_SLEEP_LST_TITLE_ALIGN;

    SET_RECT_BY_SIZE(&t_title_info.t_rect,
                     NAV_SLEEP_LST_TITLE_LEFT,
                     NAV_SLEEP_LST_TITLE_TOP,
                     NAV_SLEEP_LST_TITLE_WIDTH,
                     NAV_SLEEP_LST_TITLE_HEIGHT);

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_TITLE_INFO,
                          (VOID*)&t_title_info,
                          (VOID*)0);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Set Skin */

    i4_ret = __sleep_listbox_load_skin();
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Set refreshing flag, avoid notify to be processed */
    pt_view->b_is_refreshing = TRUE;

    /* Insert ui2_elem_num nothing field first */

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = NULL;

    for(ui2_idx = 0 ; ui2_idx < ui1_elem_num ; ui2_idx++)
    {
        i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
         if (i4_ret != WGLR_OK)
        {
        return NAVR_FAIL;
        }
    }

    /* Un-set refreshing flag */
    pt_view->b_is_refreshing = FALSE;

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
static INT32  __sleep_listbox_load_skin(VOID)
{
#if 1
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;
    WGL_COLOR_INFO_T                         t_clr_info;
    WGL_INSET_T                              t_inset;
    WGL_LB_COLOR_ELEM_SET_T                  t_color_elem;
    WGL_IMG_INFO_T                           t_img_info;
    WGL_LB_IMG_ELEM_SET_T                    t_img_elem = {0};
    INT32                                    i4_ret;

   /* listbox view port background color */
    c_memset (&t_clr_info, 0, sizeof (t_clr_info)) ;
    t_clr_info.e_type              = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_nav_sleep_color_listbox_vp_bk;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_nav_sleep_color_listbox_vp_bk;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_nav_sleep_color_listbox_vp_bk;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_VP_BK),
                          WGL_PACK(&t_clr_info));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* listbox background image */
    c_memset (&t_img_info, 0, sizeof (t_img_info)) ;
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_view->h_lb_bk_img;
    t_img_info.u_img_data.t_standard.t_disable   = pt_view->h_lb_bk_img;
    t_img_info.u_img_data.t_standard.t_highlight = pt_view->h_lb_bk_img;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* element image background */
    c_memset (&t_img_elem, 0, sizeof (t_img_elem)) ;
    t_img_elem.h_highlight           = pt_view->h_lb_ht_img;
    t_img_elem.h_highlight_unfocus   = pt_view->h_lb_ht_img;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                          WGL_PACK(& t_img_elem),
                          NULL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* element background colors */
    c_memset (&t_color_elem, 0, sizeof (t_color_elem)) ;
    t_color_elem.t_normal              = t_g_nav_sleep_color_listbox_elem_bk;
    t_color_elem.t_disable             = t_g_nav_sleep_color_listbox_elem_bk;
    t_color_elem.t_highlight           = t_g_nav_sleep_color_listbox_elem_bk;
    t_color_elem.t_highlight_unfocus   = t_g_nav_sleep_color_listbox_elem_bk;
    t_color_elem.t_pushed              = t_g_nav_sleep_color_listbox_elem_bk;
    t_color_elem.t_selected            = t_g_nav_sleep_color_listbox_elem_bk;
    t_color_elem.t_selected_disable    = t_g_nav_sleep_color_listbox_elem_bk;

    i4_ret = c_wgl_do_cmd (pt_view->h_listbox,
                           WGL_CMD_LB_SET_ELEM_COLOR,
                           WGL_PACK(WGL_CLR_BK),
                           WGL_PACK(&t_color_elem));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /*column bk color*/
    c_memset (&t_color_elem, 0, sizeof (t_color_elem)) ;
    t_color_elem.t_normal              = t_g_nav_sleep_color_listbox_col_bk;
    t_color_elem.t_disable             = t_g_nav_sleep_color_listbox_col_bk;
    t_color_elem.t_highlight           = t_g_nav_sleep_color_listbox_col_bk;
    t_color_elem.t_highlight_unfocus   = t_g_nav_sleep_color_listbox_col_bk;
    t_color_elem.t_pushed              = t_g_nav_sleep_color_listbox_col_bk;
    t_color_elem.t_selected            = t_g_nav_sleep_color_listbox_col_bk;
    t_color_elem.t_selected_disable    = t_g_nav_sleep_color_listbox_col_bk;

    /* one column only */

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_BK),
                          WGL_PACK(&t_color_elem));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /*set sleep text color*/
    c_memset (&t_color_elem, 0, sizeof (t_color_elem)) ;
    t_color_elem.t_normal              = t_g_nav_sleep_color_listbox_elem_fg;
    t_color_elem.t_disable             = t_g_nav_sleep_color_listbox_elem_fg;
    t_color_elem.t_highlight           = t_g_nav_sleep_color_listbox_elem_fg_hlt;
    t_color_elem.t_highlight_unfocus   = t_g_nav_sleep_color_listbox_elem_fg_hlt;
    t_color_elem.t_pushed              = t_g_nav_sleep_color_listbox_elem_fg;
    t_color_elem.t_selected            = t_g_nav_sleep_color_listbox_elem_fg;
    t_color_elem.t_selected_disable    = t_g_nav_sleep_color_listbox_elem_fg;

    i4_ret = c_wgl_do_cmd (pt_view->h_listbox,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(0, WGL_CLR_TEXT),
                           WGL_PACK(&t_color_elem));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /*Title's foreground color*/
    c_memset (&t_clr_info, 0, sizeof (t_clr_info)) ;
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = t_g_nav_sleep_color_listbox_title_fg;
    t_clr_info.u_color_data.t_standard.t_enable      = t_g_nav_sleep_color_listbox_title_fg;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_g_nav_sleep_color_listbox_title_fg;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_LB_TITLE_FG,
                          &t_clr_info);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /*Title's background color*/
    c_memset (&t_clr_info, 0, sizeof (t_clr_info)) ;
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = t_g_nav_sleep_color_listbox_title_bk;
    t_clr_info.u_color_data.t_standard.t_enable      = t_g_nav_sleep_color_listbox_title_bk;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_g_nav_sleep_color_listbox_title_bk;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_LB_TITLE_BK,
                          &t_clr_info);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set sleep's font */
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_COL_FONT,
                          WGL_PACK(0),
                          WGL_PACK(&t_g_sleep_text_font_info));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set Title's font */
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_FONT,
                          (VOID*)&t_g_sleep_title_font_info,
                          NULL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set sleep's inset */
    NAV_SLEEP_LST_BOX_NAME_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(0),
                          WGL_PACK(&t_inset));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set content inset */
    NAV_SLEEP_LST_BOX_CONTENT_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set element inset */
    NAV_SLEEP_LST_BOX_ELEM_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          WGL_PACK(&t_inset),
                          NULL);

    /* Key Map */
    /* Need not to change */
#endif

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
static INT32 __sleep_listbox_on_notify(UINT32 ui4_key_code)
{

    NAV_SLEEP_VIEW_T*    pt_view = &t_g_nav_sleep_view;;
    UINT32               ui4_time;
    INT32                i4_ret;
    UINT16               ui2_idx;
    UINT8                ui1_num_rec;
    if(NULL == pt_view)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Parameters is wrong.\r\n", __FUNCTION__));
        return NAVR_INV_ARG;
    }

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(&ui2_idx),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to get highlight index. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    if (ui4_key_code == BTN_SLEEP)
    {
        a_sleep_timer_get_num_rec(&ui1_num_rec);

        if ((ui2_idx+1)==(UINT16)ui1_num_rec)
        {
            ui4_time = 0;
        }
        else
        {
            a_sleep_timer_get_time_by_idx((UINT8)ui2_idx+1, &ui4_time);
        }

        if(ui4_time == 0)
        {
            a_sleep_timer_stop();
            ui2_g_hlt_idx = 0;
        }
        else
        {
            a_sleep_timer_start(ui4_time);
            ui2_g_hlt_idx = ui2_idx+1;
        }
    }
    else
    {
        a_sleep_timer_get_time_by_idx((UINT8)ui2_idx, &ui4_time);

        if(ui4_time == 0)
        {
            a_sleep_timer_stop();
        }
        else
        {
            a_sleep_timer_start(ui4_time);
        }

        ui2_g_hlt_idx = ui2_idx;
    }

    return NAVR_OK;

}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_sleep_view_is_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    BOOL   b_sleep_pop_dialog_show = FALSE;

    switch (ui4_key_code) {
    case BTN_SLEEP:
    {
       a_nav_get_sleep_prompt_dlg_status(&b_sleep_pop_dialog_show);
       if(!b_sleep_pop_dialog_show)
        {
          return TRUE;
        }
       else
       {
          return FALSE;
       }
    }
    break;
    default:
        return FALSE;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_show
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
/*static INT32 _nav_sleep_view_show(
                    NAV_SLEEP_VIEW_T*           pt_view,
                    UINT32                      ui4_time
                    )
{
    UTF16_T  w2s_value_string[16+1] = {0};
    UTF16_T  w2s_string[32+1]       = {0};
    SIZE_T   z_len                  = 32;
    INT32    i4_ret;


    i4_ret = a_sleep_timer_get_text(ui4_time, w2s_value_string, z_len);
    if (i4_ret != STIMERR_OK) {
        return NAVR_FAIL;
    }

    c_uc_w2s_strcat(w2s_string, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_TITLE_SLEEP));
    c_uc_w2s_strcat(w2s_string, w2s_value_string);

    i4_ret = c_wgl_do_cmd(pt_view->h_msg, WGL_CMD_TEXT_SET_TEXT, (VOID*)w2s_string, (VOID*)z_len);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_RECURSIVE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    #ifdef APP_AUD_DIRECT_ADJUST
    	if(WGL_Force_Flag == WGL_FORCE_ShowOSD)
        {
            i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, IS_SYNC_REPAINT);
            if (i4_ret != WGLR_OK)
            {
                return NAVR_FAIL;
            }
        }
    #else
        i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, IS_SYNC_REPAINT);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    #endif

    return NAVR_OK;
}*/

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_activate
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_view_activate(
                    UINT32                      ui4_key_code
                    )
{
    NAV_SLEEP_VIEW_T* pt_view        = &t_g_nav_sleep_view;
    INT32               i4_ret;
	BOOL				b_dlg_show = FALSE;

	 a_nav_get_sleep_prompt_dlg_status(&b_dlg_show);
	if(!b_dlg_show)
	{
    /* Let's focus on the listbox */
    i4_ret = c_wgl_set_focus(pt_view->h_listbox, WGL_NO_AUTO_REPAINT);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    nav_sleep_reset_timer(pt_view->pt_ctrl, SLEEP_TIMEOUT);
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
static INT32 _nav_sleep_view_hide(
                    VOID
                    )
{
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;
    INT32             i4_ret;

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
/*---------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_frame_nfy_fct(
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
/*static INT32 _nav_sleep_view_frame_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32 i4_ret;

    #ifdef APP_AUD_DIRECT_ADJUST
        if(ui4_msg == WGL_MSG_GET_FOCUS)
        {
            WGL_Force_Flag = WGL_FORCE_Change;
        }
        else if( WGL_Force_Flag==WGL_FORCE_Change  & ui4_msg != 0)
        {
            WGL_Force_Flag = WGL_FORCE_ShowOSD;
            ui4_msg = WGL_MSG_KEY_DOWN;
        }
        else if(ui4_msg == WGL_MSG_LOSE_FOCUS)
        {
            WGL_Force_Flag = WGL_NOT_FORCE;
        }
    #endif

    switch(ui4_msg) {
    case WGL_MSG_KEY_DOWN:
        _nav_sleep_view_rcu_key_handler((UINT32)pv_param1);*/  /* key code */
       /* break;
    default:
        break;
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );

    return i4_ret;
}*/
/*---------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_frame_wdgt_proc_fct
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_view_frame_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
#if 0
    NAV_SLEEP_VIEW_T*  pt_view = &t_g_nav_sleep_view;

    /* Listen the notify and do the actual work by Ctrl's API */
    switch (ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
            WGL_NOTIFY_DATA_T*                  pt_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;
            HANDLE_T                            h_source = (HANDLE_T)pv_param1;

            if(pt_view->b_is_refreshing != TRUE)
            {
                /* Not refreshing, dispatch the notify */
                if (h_source == pt_view->h_listbox
                    &&
                    WGL_NC_LB_ELEM_HLT == pt_nfy_data->ui4_nc_code
                    &&
                    TRUE == pt_nfy_data->u.t_lb_elem_hlt.b_is_highlighted)
                {
                    nav_sleep_reset_timer(pt_view->pt_ctrl, SLEEP_TIMEOUT);
                }
            }
        }
        break;
    }
#endif

    return (c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    ));
}

/*----------------------------------------------------------------------------
 * Name: _nav_sleep_view_listbox_wdgt_proc_fct
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
static INT32 _nav_sleep_view_listbox_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32 i4_ret;
    BOOL  b_processed = FALSE;
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;

    if(b_processed)
    {
        return NAVR_OK;
    }

    if(ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch ((UINT32) pv_param1)
        {
        case BTN_CURSOR_UP:
        case BTN_CURSOR_DOWN:
            /* c_wgl_default_msg_proc to will handle this */
            nav_sleep_reset_timer(pt_view->pt_ctrl, SLEEP_TIMEOUT);
            break;

        case BTN_SLEEP :
             __sleep_listbox_on_notify(BTN_SLEEP);
            /* Translate BTN_SELECT to EXIT */
             pv_param1 = (VOID *) BTN_CURSOR_DOWN;
            nav_sleep_reset_timer(pt_view->pt_ctrl, SLEEP_TIMEOUT);
            break ;

        case BTN_SELECT :
            if (b_g_exit_by_btn_select)
            {
                __sleep_listbox_on_notify(BTN_SELECT);
                nav_hide_component(NAV_COMP_ID_SLEEP);
                return WGLR_OK;
            }
            break ;

        default :
            nav_rcu_key_handler ((UINT32) pv_param1) ;
            return WGLR_OK ;
        }
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

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_view_init(
                    NAV_SLEEP_T*                pt_ctrl,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    UINT8                       ui1_elem_num
                    )
{
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;
    INT32             i4_ret;

    pt_view->pt_ctrl = pt_ctrl;

    /* create image */
    __sleep_create_image();

    /* create frame */
    __sleep_create_frame(h_canvas,
                        i4_frame_x_offset,
                        i4_frame_y_offset);
    /* create listbox */
    __sleep_create_listbox(pt_view->h_frame,
                           ui1_elem_num);

    i4_ret = c_wgl_show(pt_view->h_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Customization Environment */
    b_g_exit_by_btn_select      = NAV_SLEEP_EXIT_BY_BTN_SELECT;

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
static INT32 _nav_sleep_view_set_hlt_index(VOID)
{
    INT32               i4_ret  = 0 ;
    NAV_SLEEP_VIEW_T *  pt_view = &t_g_nav_sleep_view;
    UINT8               ui1_idx = 0 ;
    UINT32              ui4_remain_time = 0 ;

    /* sync current hlt */
    {
        a_sleep_timer_iterate (STIMER_ITERATE_DIR_CRNT, &ui1_idx, &ui4_remain_time);
        ui2_g_hlt_idx = ui1_idx ;
    }

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(ui2_g_hlt_idx),
                          NULL);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                          NULL,
                          NULL);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }
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
static INT32 _nav_sleep_view_set_index_text(UINT16    ui2_idx,
                                            UTF16_T*  pw2s_text)
{
    INT32    i4_ret;
    NAV_SLEEP_VIEW_T *pt_view = &t_g_nav_sleep_view;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(ui2_idx, 0),
                          WGL_PACK(pw2s_text));
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

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
static INT32 _nav_sleep_view_set_is_refreshing(BOOL      b_is_refreshing)
{
    NAV_SLEEP_VIEW_T *pt_view = &t_g_nav_sleep_view;

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
static INT32 _nav_sleep_view_set_title_text(UTF16_T*  pw2s_title)

{
    INT32    i4_ret;
    NAV_SLEEP_VIEW_T *pt_view = &t_g_nav_sleep_view;

    /*set title*/
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_TITLE_TEXT,
                          (VOID*)pw2s_title,
                          (VOID*)((NULL == pw2s_title) ? 0 : c_uc_w2s_strlen(pw2s_title)));
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

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
static INT32 _nav_sleep_view_deinit(
                    VOID
                    )
{
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;

    c_wgl_destroy_widget(pt_view->h_frame);
    c_wgl_destroy_widget(pt_view->h_listbox);

    if(TRUE == c_handle_valid(pt_view->h_lb_bk_img))
    {
        c_wgl_img_tpl_destroy(pt_view->h_lb_bk_img);
    }
    if(TRUE == c_handle_valid(pt_view->h_lb_ht_img))
    {
        c_wgl_img_tpl_destroy(pt_view->h_lb_ht_img);
    }

    pt_view->pt_ctrl     = NULL;
    pt_view->h_frame     = NULL_HANDLE;
    pt_view->h_listbox   = NULL_HANDLE;
    pt_view->h_lb_bk_img = NULL_HANDLE;
    pt_view->h_lb_ht_img = NULL_HANDLE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_sleep_view_list_register_default_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_sleep_view_list_register_default_hdlr(
                    NAV_SLEEP_VIEW_HDLR_T*      pt_view_hdlr
                    )
{
    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init              = _nav_sleep_view_init;
    pt_view_hdlr->pf_deinit            = _nav_sleep_view_deinit;
    pt_view_hdlr->pf_is_key_handler    = _nav_sleep_view_is_key_handler;
    pt_view_hdlr->pf_activate          = _nav_sleep_view_activate;
    pt_view_hdlr->pf_hide              = _nav_sleep_view_hide;
    pt_view_hdlr->pf_set_hlt_index     = _nav_sleep_view_set_hlt_index;
    pt_view_hdlr->pf_set_index_text    = _nav_sleep_view_set_index_text;
    pt_view_hdlr->pf_set_is_refreshing = _nav_sleep_view_set_is_refreshing;
    pt_view_hdlr->pf_set_title_text    = _nav_sleep_view_set_title_text;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
#endif
