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
 * $RCSfile: ch_lst_view.c,v $
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
#include "res/nav/nav_variant.h"

#include "u_common.h"
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
#include "c_fe.h"

#include "nav/ch_lst/ch_lst.h"
#include "nav/nav_common.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"

#include "wdk/a_wdk.h"
#include "wdk/a_cnt_indctr.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)

#ifdef APP_IMG_UI
#define FRAME_STYLE                             (NULL)
#else
#define FRAME_STYLE                             ((VOID*)(WGL_STL_GL_NO_IMG_UI))
#endif

/* New layout:

  +--------------------------------------------------------------------+
  | COL0 icon | COL1 icon | COL2 icon | COL3 Number | COL4 Name        |
  +--------------------------------------------------------------------+


    2 customization functions:

    nav_ch_lst_view_custom_init
    nav_ch_lst_view_custom_update_list_attribute (p1,p2,p3,p4)

    1 customization include file:
    #include "res/nav/ch_lst/ch_lst_view_custom.h"

*/

/* Old layout:

  +--------------------------------------------------------------------+
  |  COL0 Number | COL1 Name                                           |
  +--------------------------------------------------------------------+

*/

/* For backward compatible. -------------------------------------------------------- */
#ifndef CH_LST_0_COL_ALIGN                 /* ICON Scheme */
#define CH_LST_0_COL_ALIGN                 WGL_AS_CENTER_CENTER     /* Icon1 */
#define CH_LST_0_COL_WIDTH                 0
#define CH_LST_1_COL_ALIGN                 WGL_AS_CENTER_CENTER     /* Icon2 */
#define CH_LST_1_COL_WIDTH                 0
#define CH_LST_2_COL_ALIGN                 WGL_AS_CENTER_CENTER     /* Icon3 */
#define CH_LST_2_COL_WIDTH                 0

#define CH_LST_3_MAX_TEXT_LEN              CH_LST_0_MAX_TEXT_LEN
#define CH_LST_4_MAX_TEXT_LEN              CH_LST_1_MAX_TEXT_LEN

#define CH_LST_3_COL_ALIGNMENT             CH_LST_0_COL_ALIGNMENT
#define CH_LST_4_COL_ALIGNMENT             CH_LST_1_COL_ALIGNMENT
#define CH_LST_3_COL_LEFT_INSET            CH_LST_0_COL_LEFT_INSET
#define CH_LST_3_COL_RIGHT_INSET           CH_LST_0_COL_RIGHT_INSET
#define CH_LST_4_COL_LEFT_INSET            CH_LST_1_COL_LEFT_INSET
#define CH_LST_4_COL_RIGHT_INSET           CH_LST_1_COL_RIGHT_INSET

#define CH_LST_3_COL_WIDHT                 CH_LST_0_COL_WIDHT
#define CH_LST_4_COL_WIDHT                 CH_LST_1_COL_WIDHT

#ifdef CH_LST_0_COL_TOP_INSET
    #define CH_LST_3_COL_TOP_INSET         CH_LST_0_COL_TOP_INSET
#endif

#ifdef CH_LST_0_COL_BOTTOM_INSET
    #define CH_LST_3_COL_BOTTOM_INSET      CH_LST_0_COL_BOTTOM_INSET
#endif

#ifdef CH_LST_1_COL_TOP_INSET
    #define CH_LST_4_COL_TOP_INSET         CH_LST_1_COL_TOP_INSET
#endif

#ifdef CH_LST_1_COL_BOTTOM_INSET
    #define CH_LST_4_COL_BOTTOM_INSET      CH_LST_1_COL_BOTTOM_INSET
#endif

#define nav_ch_lst_view_custom_init(p1,p2,p3,p4,p5)                  NAVR_OK
#define nav_ch_lst_view_custom_update_list_attribute(p1,p2,p3,p4)    NAVR_OK

WGL_FONT_INFO_T t_g_ch_lst_title_font_info     = {FE_FNT_SIZE_LARGE,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
#ifdef APP_DVBT_SUPPORT
WGL_FONT_INFO_T t_g_ch_lst_elem_col3_font_info = {FE_FNT_SIZE_LARGE,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
WGL_FONT_INFO_T t_g_ch_lst_elem_col4_font_info = {FE_FNT_SIZE_SMALL, FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
#else
WGL_FONT_INFO_T t_g_ch_lst_elem_col3_font_info = {FE_FNT_SIZE_LARGE,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
WGL_FONT_INFO_T t_g_ch_lst_elem_col4_font_info = {FE_FNT_SIZE_LARGE,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
#endif
WGL_FONT_INFO_T t_g_ch_lst_help_font_info      = {FE_FNT_SIZE_SMALL,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};

#else  /* Backward compatible. (End) ----------------------------------------------- */


#include "res/nav/ch_lst/ch_lst_view_custom.h"


#endif

#ifndef CH_LST_IMG_COL_TOP_INSET
    #define CH_LST_IMG_COL_TOP_INSET            NAV_HEIGHT(0)
#endif
#ifndef CH_LST_3_COL_TOP_INSET
    #define CH_LST_3_COL_TOP_INSET              NAV_HEIGHT(4)
#endif
#ifndef CH_LST_3_COL_BOTTOM_INSET
    #define CH_LST_3_COL_BOTTOM_INSET           NAV_HEIGHT(0)
#endif

#ifndef CH_LST_4_COL_TOP_INSET
    #define CH_LST_4_COL_TOP_INSET              NAV_HEIGHT(0) /* avoid font crop */
#endif
#ifndef CH_LST_4_COL_BOTTOM_INSET
    #define CH_LST_4_COL_BOTTOM_INSET           NAV_HEIGHT(0)
#endif
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static UTF16_T*        pw2s_g_ch_lst_title   = NULL;
static UTF16_T*        pw2s_g_page_up        = NULL;
static UTF16_T*        pw2s_g_page_dn        = NULL;

#ifdef APP_SUPPORT_MULTIPLE_CHANNEL_LIST
static UTF16_T*        pw2s_g_ch_list_type   = NULL;
static UTF16_T*        pw2s_g_sel_list       = NULL;
static UTF16_T*        pw2s_g_exit           = NULL;
static UTF16_T*        pw2s_g_satellite_selection = NULL;

#ifdef APP_DVBS_SUPPORT
static BOOL            b_g_is_dvbs_support   = TRUE;
#else
static BOOL            b_g_is_dvbs_support   = FALSE;
#endif

#endif


/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_view_frame_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );
static INT32 _nav_ch_lst_view_set_skin(
                    NAV_CH_LST_VIEW_T*          pt_view,
                    APP_COLOR_TYPE_T            e_color_type
                    );
static INT32 _nav_ch_lst_view_set_msgs(
                    NAV_CH_LST_VIEW_T*          pt_view
                    );
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_view_init_images
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_view_init_images(NAV_CH_LST_VIEW_T*  pt_view)
{
    INT32              i4_ret;

#ifdef APP_IMG_UI
    i4_ret = nav_img_create_ch_list_bk_img_tpl(
                    &pt_view->h_img_ch_list_bk
                    );
    if(NAVR_OK != i4_ret){
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_hlt_bar_bk_img_tpl(
                    &pt_view->h_img_hlt_bar_bk
                    );
    if(NAVR_OK != i4_ret){
        return NAVR_FAIL;
    }
#endif
#if 0
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_app_red_btn_img,
                    &pt_view->h_img_red_btn
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_app_green_btn_img,
                    &pt_view->h_img_green_btn
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_app_yellow_btn_img,
                    &pt_view->h_img_yellow_btn
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_app_blue_btn_img,
                    &pt_view->h_img_blue_btn
                    );
    if(WGLR_OK != i4_ret){
        return NAVR_FAIL;
    }
#endif

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_lst_view_init(
                    NAV_CH_LST_T*               pt_this,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    INT32              i4_ret;
    GL_RECT_T          t_rect;
    WGL_LB_INIT_T      t_list_box_init;
    WGL_LB_COL_INIT_T  at_cols[7];
    NAV_CH_LST_VIEW_T* pt_view = &(pt_this->t_lst_view);
    CNT_INDCTR_INIT_T  t_init_data = {0};

    /*Init the images*/
    _nav_ch_lst_view_init_images(pt_view);

    /* create channel frame */
    SET_RECT_BY_SIZE(&t_rect,
                    CH_LST_FRAME_LEFT + i4_frame_x_offset,
                    CH_LST_FRAME_TOP  + i4_frame_y_offset,
                    CH_LST_FRAME_WIDTH,
                    CH_LST_FRAME_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    h_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    _nav_ch_lst_view_frame_nfy_fct,
                    0,
                    (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK),
                    pt_this,
                    &pt_view->h_ch_lst_frame
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* icon 1 */
    at_cols[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[0].ui1_align        = CH_LST_0_COL_ALIGN;
    at_cols[0].ui2_width        = CH_LST_0_COL_WIDTH;

    /* icon 2 */
    at_cols[1].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[1].ui1_align        = CH_LST_1_COL_ALIGN;
    at_cols[1].ui2_width        = CH_LST_1_COL_WIDTH;

    /* icon 3 */
    at_cols[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[2].ui1_align        = CH_LST_2_COL_ALIGN;
    at_cols[2].ui2_width        = CH_LST_2_COL_WIDTH;

    /* channel number column */
    at_cols[3].e_col_type             = LB_COL_TYPE_TEXT;
    at_cols[3].ui1_align              = CH_LST_3_COL_ALIGNMENT;
    at_cols[3].ui2_max_text_len       = CH_LST_3_MAX_TEXT_LEN;
    at_cols[3].ui2_width              = CH_LST_3_COL_WIDHT;

    /* channel name column */
    at_cols[4].e_col_type             = LB_COL_TYPE_TEXT;
    at_cols[4].ui1_align              = CH_LST_4_COL_ALIGNMENT;
    at_cols[4].ui2_max_text_len       = CH_LST_4_MAX_TEXT_LEN;
    at_cols[4].ui2_width              = CH_LST_4_COL_WIDHT;

    t_list_box_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH | WGL_STL_LB_NO_WRAP_OVER;
    t_list_box_init.ui2_max_elem_num  = MAX_ELEM_OF_CH_LIST;
    t_list_box_init.ui2_elem_size     = ELEM_HEIGHT_OF_CH_LIST;
    t_list_box_init.ui2_elem_distance = ELEM_DTANCE_OF_CH_LIST;
    t_list_box_init.ui1_col_num       = 5;
    t_list_box_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                    CH_LST_LEFT,
                    CH_LST_TOP,
                    CH_LST_WIDTH,
                    CH_LST_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_ch_lst_frame,
                    HT_WGL_WIDGET_LIST_BOX,
                    WGL_CONTENT_LIST_BOX_DEF,
                    WGL_BORDER_TRANSP,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    &t_list_box_init,
                    NULL,
                    &pt_view->h_ch_lst
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /*create content indicator*/
    SET_RECT_BY_SIZE(&t_rect,
                    CH_LST_INDCTR_LEFT,
                    CH_LST_INDCTR_TOP,
                    CH_LST_INDCTR_WIDTH,
                    CH_LST_INDCTR_HEIGHT
                    );
    t_init_data.h_parent        = pt_view->h_ch_lst_frame;
    t_init_data.i2_inset_up     = 0;
    t_init_data.i2_inset_down   = 0;
    t_init_data.ui4_indctr_mask = CNT_INDCTR_MASK_UD;
    t_init_data.t_rect          = t_rect;

    i4_ret = a_cnt_indctr_create(&t_init_data, &pt_view->h_cnt_indctr);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = a_cnt_indctr_set_visibilty(pt_view->h_cnt_indctr,
                                    CNT_INDCTR_MASK_UD,
                                    FALSE);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* create page up icon */
    SET_RECT_BY_SIZE(&t_rect,
                    CH_LST_PG_UP_ICON_LEFT,
                    CH_LST_PG_UP_ICON_TOP,
                    CH_LST_PG_UP_ICON_WIDTH,
                    CH_LST_PG_UP_ICON_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_ch_lst,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_pg_up_icon
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect,
                    CH_LST_PG_UP_HELP_MSG_LEFT,
                    CH_LST_PG_UP_HELP_MSG_TOP,
                    CH_LST_PG_UP_HELP_MSG_WIDTH,
                    CH_LST_PG_UP_HELP_MSG_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_ch_lst,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(VOID*)(WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_pg_up_help_msg
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* create page dn icon */
    SET_RECT_BY_SIZE(&t_rect,
                    CH_LST_PG_DN_ICON_LEFT,
                    CH_LST_PG_DN_ICON_TOP,
                    CH_LST_PG_DN_ICON_WIDTH,
                    CH_LST_PG_DN_ICON_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_ch_lst,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_pg_dn_icon
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect,
                    CH_LST_PG_DN_HELP_MSG_LEFT,
                    CH_LST_PG_DN_HELP_MSG_TOP,
                    CH_LST_PG_DN_HELP_MSG_WIDTH,
                    CH_LST_PG_DN_HELP_MSG_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_ch_lst,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(VOID*)(WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_pg_dn_help_msg
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

#ifdef APP_SUPPORT_MULTIPLE_CHANNEL_LIST
    /* create select list icon */
    SET_RECT_BY_SIZE(&t_rect,
                    CH_LST_SEL_LIST_ICON_LEFT,
                    CH_LST_SEL_LIST_ICON_TOP,
                    CH_LST_SEL_LIST_ICON_WIDTH,
                    CH_LST_SEL_LIST_ICON_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_ch_lst,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_sel_list_icon
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect,
                    CH_LST_SEL_LIST_HELP_MSG_LEFT,
                    CH_LST_SEL_LIST_HELP_MSG_TOP,
                    CH_LST_SEL_LIST_HELP_MSG_WIDTH,
                    CH_LST_SEL_LIST_HELP_MSG_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_ch_lst,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(VOID*)(WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_sel_list_help_msg
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* create exit list icon */
    SET_RECT_BY_SIZE(&t_rect,
                    CH_LST_EXIT_ICON_LEFT,
                    CH_LST_EXIT_ICON_TOP,
                    CH_LST_EXIT_ICON_WIDTH,
                    CH_LST_EXIT_ICON_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_ch_lst,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_exit_icon
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect,
                    CH_LST_EXIT_HELP_MSG_LEFT,
                    CH_LST_EXIT_HELP_MSG_TOP,
                    CH_LST_EXIT_HELP_MSG_WIDTH,
                    CH_LST_EXIT_HELP_MSG_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_ch_lst,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(VOID*)(WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_exit_help_msg
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

#endif /* APP_SUPPORT_MULTIPLE_CHANNEL_LIST */

    /* invoke custom view's init */
    i4_ret = nav_ch_lst_view_custom_init(pt_this,
                                         h_canvas,
                                         i4_frame_x_offset,
                                         i4_frame_y_offset,
                                         e_color_type);

    if(NAVR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* hide the frame */
    i4_ret = c_wgl_show(
                    pt_view->h_ch_lst_frame,
                    WGL_SW_HIDE
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* font handle. */
    i4_ret =  c_fe_create_font(t_g_ch_lst_elem_col4_font_info.a_c_font_name,
                               t_g_ch_lst_elem_col4_font_info.e_font_size,
                               t_g_ch_lst_elem_col4_font_info.e_font_style,
                               FE_CMAP_ENC_UNICODE,
                               &pt_view->h_font);
    if (i4_ret != FER_OK) {
        return NAVR_FAIL;
    }

    /* load ch list frame skin*/
    i4_ret = _nav_ch_lst_view_set_skin(
                    pt_view,
                    APP_COLOR_TYPE_BLUE
                    );
    if(NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_view_load_msgs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_ch_lst_view_load_msgs(
                    UINT8                       ui1_lang_id
                    )
{
    if (ui1_lang_id >= MLM_NAV_NUM_LANG) {
        return;
    }

    pw2s_g_ch_lst_title = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_TITLE_CH_LIST);
    pw2s_g_page_up      = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_HELP_PAGE_UP);
    pw2s_g_page_dn      = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_HELP_PAGE_DN);

#ifdef APP_SUPPORT_MULTIPLE_CHANNEL_LIST
    /* no channel selection in ATV only model */
    if (a_cfg_ftm_is_atv_only_model ()) {
        pw2s_g_ch_list_type = NULL;
        pw2s_g_sel_list     = NULL;
        pw2s_g_exit         = NULL;
        pw2s_g_satellite_selection = NULL;
    } else {
        UINT8  ui1_ch_list_type  = APP_CFG_CH_LIST_TYPE_ALL;

        /* Determine the channel list name */
        a_cfg_get_ch_list_type (&ui1_ch_list_type);

        if (ui1_ch_list_type == APP_CFG_CH_LIST_TYPE_DIGITAL ||
            ui1_ch_list_type == APP_CFG_CH_LIST_TYPE_DIGITAL_RADIO)
        {
            pw2s_g_ch_list_type = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CH_LIST_TYPE_DIGITAL);
        }
        else if (ui1_ch_list_type == APP_CFG_CH_LIST_TYPE_RADIO)
        {
            pw2s_g_ch_list_type = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CH_LIST_TYPE_RADIO);
        }
        else if (ui1_ch_list_type == APP_CFG_CH_LIST_TYPE_ANALOG)
        {
            pw2s_g_ch_list_type = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CH_LIST_TYPE_ANALOG);
        }
        else
        {
            pw2s_g_ch_list_type = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CH_LIST_TYPE_ALL);
        }

        pw2s_g_sel_list = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_HELP_SELECT_LIST);
        pw2s_g_exit     = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_HELP_EXIT);
        pw2s_g_satellite_selection = MLM_NAV_TEXT (ui1_lang_id, MLM_NAV_KEY_HELP_SELECT_SATELLITE);

    }
#else
#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_lst_view_deinit(
                    NAV_CH_LST_VIEW_T*          pt_view
                    )
{
#ifdef APP_IMG_UI
    c_wgl_img_tpl_destroy(pt_view->h_img_ch_list_bk);
    c_wgl_img_tpl_destroy(pt_view->h_img_hlt_bar_bk);
#endif

    c_wgl_img_tpl_destroy(pt_view->h_img_red_btn);
    c_wgl_img_tpl_destroy(pt_view->h_img_green_btn);
    c_wgl_img_tpl_destroy(pt_view->h_img_yellow_btn);
    c_wgl_img_tpl_destroy(pt_view->h_img_blue_btn);

    c_wgl_destroy_widget(pt_view->h_pg_up_help_msg);
    c_wgl_destroy_widget(pt_view->h_pg_dn_help_msg);
    c_wgl_destroy_widget(pt_view->h_sel_list_help_msg);
    c_wgl_destroy_widget(pt_view->h_exit_help_msg);
    c_wgl_destroy_widget(pt_view->h_pg_up_icon);
    c_wgl_destroy_widget(pt_view->h_pg_dn_icon);
    c_wgl_destroy_widget(pt_view->h_sel_list_icon);
    c_wgl_destroy_widget(pt_view->h_exit_icon);
    c_wgl_destroy_widget(pt_view->h_ch_lst);
    c_wgl_destroy_widget(pt_view->h_ch_lst_frame);
    c_handle_free(pt_view->h_font);

    a_cnt_indctr_destroy(pt_view->h_cnt_indctr);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_lst_view_hide(
                    NAV_CH_LST_VIEW_T*          pt_view
                    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_ch_lst_frame,
                    WGL_SW_HIDE
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(
                    pt_view->h_ch_lst_frame,
                    NULL,
                    IS_SYNC_REPAINT
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_view_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_lst_view_show(
                    NAV_CH_LST_VIEW_T*          pt_view,
                    UINT32                      ui4_cnt_indctr_sts
                    )
{
    INT32 i4_ret;

    i4_ret = _nav_ch_lst_view_set_msgs(pt_view);
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_focus(
                    pt_view->h_ch_lst,
                    FALSE
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_ch_lst_frame,
                    WGL_SW_NORMAL
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    if (ui4_cnt_indctr_sts != pt_view->ui4_indctr_sts)
    {
        pt_view->ui4_indctr_sts = ui4_cnt_indctr_sts;
        a_cnt_indctr_reset_visibilty(pt_view->h_cnt_indctr);
        a_cnt_indctr_set_visibilty(pt_view->h_cnt_indctr,
                               ui4_cnt_indctr_sts,
                               TRUE);
    }

    i4_ret = c_wgl_repaint(
                    pt_view->h_ch_lst_frame,
                    NULL,
                    IS_SYNC_REPAINT
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    nav_set_component_visible(NAV_COMP_ID_CH_LIST);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_view_update
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ch_lst_view_update(
                    NAV_CH_LST_VIEW_T*          pt_view,
                    NAV_CH_LIST_ELMNT_T*        pt_ch_list,
                    UINT16                      ui2_total_size,
                    UINT16                      ui2_ch_list_size,
                    UINT16                      ui2_hlt_elem_idx,
                    UINT32                      ui4_cnt_indctr_sts,
                    BOOL                        b_repaint
                    )
{
    INT32   i4_ret;
    UINT16  ui2_idx;
    UTF16_T w2s_ch_num_string[CH_NUMBER_MAX_LENGTH+1] = {0};
    UTF16_T w2s_ch_name_string[CH_NAME_MAX_LENGTH+1]  = {0};

    i4_ret = c_wgl_do_cmd(
                        pt_view->h_ch_lst,
                        WGL_CMD_LB_SET_ELEM_NUM,
                        WGL_PACK(ui2_ch_list_size),
                        NULL
                        );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    for (ui2_idx = 0; ui2_idx < ui2_ch_list_size; ui2_idx++) {
        /* channel number */
        i4_ret = c_uc_ps_to_w2s(
                        pt_ch_list->s_ch_num,
                        w2s_ch_num_string,
                        CH_NUMBER_MAX_LENGTH
                        );
        if (i4_ret != UCR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_do_cmd(
                        pt_view->h_ch_lst,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(ui2_idx, 3),
                        WGL_PACK(w2s_ch_num_string)
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        /* channel name */
        i4_ret = c_uc_ps_to_w2s(
                        pt_ch_list->s_ch_name,
                        w2s_ch_name_string,
                        CH_NAME_MAX_LENGTH
                        );
        if (i4_ret != UCR_OK) {
            /* allow fault tolerance */
            w2s_ch_name_string[0] = 0;
        }

#ifdef APP_DVBT_SUPPORT
        /* precheck for the name width enough or not. */
        {
            INT32     i4_width = 0;
            INT32     i4_height = 0;

            i4_ret = c_fe_get_string_size(pt_view->h_font,
                                          w2s_ch_name_string,
                                          (-1),
                                          & i4_width,
                                          & i4_height);
            if (i4_ret != FER_OK) {
                return NAVR_FAIL;
            }

            /* If the long-name length is not enough, try shorter-name. */
            if ( (pt_ch_list->e_brdcst_type == BRDCST_TYPE_DVB || pt_ch_list->e_brdcst_type == BRDCST_TYPE_DTMB)
                &&
                i4_width > CH_LST_4_COL_WIDHT)
            {
                /* channel name */
                i4_ret = c_uc_ps_to_w2s(
                                pt_ch_list->s_ch_name_short,
                                w2s_ch_name_string,
                                MAX_DVB_SERVICE_NAME_LEN
                                );
                if (i4_ret != UCR_OK) {
                    /* allow fault tolerance */
                    w2s_ch_name_string[0] = 0;
                }

                /* if short-name is not available, return to original name. */

                if (w2s_ch_name_string[0] == NULL)
                {
                    i4_ret = c_uc_ps_to_w2s(
                                    pt_ch_list->s_ch_name,
                                    w2s_ch_name_string,
                                    CH_NAME_MAX_LENGTH
                                    );
                    if (i4_ret != UCR_OK) {
                        /* allow fault tolerance */
                        w2s_ch_name_string[0] = 0;
                    }
                }
            }
        }
#endif
        i4_ret = c_wgl_do_cmd(
                        pt_view->h_ch_lst,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(ui2_idx, 4),
                        WGL_PACK(w2s_ch_name_string)
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        /* Custom part refine the channel list. */
        i4_ret = nav_ch_lst_view_custom_update_list_attribute(pt_view,
                                                              pt_view->h_ch_lst,
                                                              pt_ch_list,
                                                              ui2_idx);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        pt_ch_list++;
    }

    if (ui2_hlt_elem_idx < ui2_ch_list_size) {
        i4_ret = c_wgl_do_cmd(
                        pt_view->h_ch_lst,
                        WGL_CMD_LB_HLT_ELEM_VISIBLE,
                        WGL_PACK(ui2_hlt_elem_idx),
                        WGL_PACK(ui2_hlt_elem_idx)
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }
#ifdef APP_CH_LST_PAGE_UPDN
    if (ui2_total_size > ui2_ch_list_size) {
        i4_ret = c_wgl_set_visibility(
                        pt_view->h_pg_up_icon,
                        WGL_SW_NORMAL
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_visibility(
                        pt_view->h_pg_up_help_msg,
                        WGL_SW_NORMAL
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_visibility(
                        pt_view->h_pg_dn_icon,
                        WGL_SW_NORMAL
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_visibility(
                        pt_view->h_pg_dn_help_msg,
                        WGL_SW_NORMAL
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    } else {
        i4_ret = c_wgl_set_visibility(
                        pt_view->h_pg_up_icon,
                        WGL_SW_HIDE
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_visibility(
                        pt_view->h_pg_up_help_msg,
                        WGL_SW_HIDE
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_visibility(
                        pt_view->h_pg_dn_icon,
                        WGL_SW_HIDE
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_visibility(
                        pt_view->h_pg_dn_help_msg,
                        WGL_SW_HIDE
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }
#endif

#ifdef APP_SUPPORT_MULTIPLE_CHANNEL_LIST
        i4_ret = c_wgl_set_visibility(
                        pt_view->h_sel_list_icon,
                        WGL_SW_NORMAL
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_visibility(
                        pt_view->h_sel_list_help_msg,
                        WGL_SW_NORMAL
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_visibility(
                        pt_view->h_exit_icon,
                        WGL_SW_NORMAL
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_visibility(
                        pt_view->h_exit_help_msg,
                        WGL_SW_NORMAL
                        );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

#endif /* APP_SUPPORT_MULTIPLE_CHANNEL_LIST */

    i4_ret = c_wgl_set_visibility(
                        pt_view->h_ch_lst,
                        WGL_SW_NORMAL
                        );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(
                        pt_view->h_ch_lst_frame,
                        WGL_SW_NORMAL
                        );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    if (ui4_cnt_indctr_sts != pt_view->ui4_indctr_sts)
    {
        pt_view->ui4_indctr_sts = ui4_cnt_indctr_sts;
        a_cnt_indctr_reset_visibilty(pt_view->h_cnt_indctr);
        a_cnt_indctr_set_visibilty(pt_view->h_cnt_indctr,
                               ui4_cnt_indctr_sts,
                               TRUE);
    }

    if (b_repaint == TRUE) {
        i4_ret = c_wgl_repaint(
                        pt_view->h_ch_lst_frame,
                        NULL,
                        IS_SYNC_REPAINT
                        );

        if(WGLR_OK != i4_ret) {
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_view_set_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_view_set_skin(
                    NAV_CH_LST_VIEW_T*          pt_view,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    INT32                   i4_ret;
    WGL_COLOR_INFO_T        t_clr_info;
    WGL_INSET_T             t_inset;
    WGL_LB_COLOR_ELEM_SET_T t_color_elem;
    WGL_LB_KEY_MAP_T        t_key_map = {0};
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;

#ifdef APP_IMG_UI
    WGL_LB_IMG_ELEM_SET_T   t_img_elem;


    /* listbox background image */
    i4_ret = nav_set_bk_img(
                    pt_view->h_ch_lst,
                    WGL_IMG_SET_STANDARD,
                    pt_view->h_img_ch_list_bk,
                    pt_view->h_img_ch_list_bk,
                    pt_view->h_img_ch_list_bk
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* element image background */
    t_img_elem.h_normal              = NULL_HANDLE;
    t_img_elem.h_disable             = NULL_HANDLE;
    t_img_elem.h_highlight           = pt_view->h_img_hlt_bar_bk;
    t_img_elem.h_highlight_unfocus   = pt_view->h_img_hlt_bar_bk;
    t_img_elem.h_pushed              = NULL_HANDLE;
    t_img_elem.h_selected            = NULL_HANDLE;
    t_img_elem.h_selected_disable    = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                    WGL_PACK(& t_img_elem),
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

#ifndef NAV_CH_LST_CLR_ELEM
    t_color_elem.t_normal              = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
    t_color_elem.t_disable             = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
    t_color_elem.t_highlight           = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
    t_color_elem.t_highlight_unfocus   = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
    t_color_elem.t_pushed              = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
    t_color_elem.t_selected            = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
    t_color_elem.t_selected_disable    = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
#else
    NAV_CH_LST_CLR_ELEM(e_color_type,t_color_elem.t_normal);
    NAV_CH_LST_CLR_ELEM(e_color_type,t_color_elem.t_disable);
    NAV_CH_LST_CLR_ELEM(e_color_type,t_color_elem.t_highlight);
    NAV_CH_LST_CLR_ELEM(e_color_type,t_color_elem.t_highlight_unfocus);
    NAV_CH_LST_CLR_ELEM(e_color_type,t_color_elem.t_pushed);
    NAV_CH_LST_CLR_ELEM(e_color_type,t_color_elem.t_selected);
    NAV_CH_LST_CLR_ELEM(e_color_type,t_color_elem.t_selected_disable);
#endif
    t_color_elem.t_normal.a            = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_disable.a           = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_highlight.a         = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_highlight_unfocus.a = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_pushed.a            = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_selected.a          = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_selected_disable.a  = LST_BOX_ELM_BK_ALPHA;

    /* element bg colors */
    i4_ret = c_wgl_do_cmd (
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_ELEM_COLOR,
                    WGL_PACK(WGL_CLR_BK),
                    WGL_PACK(&t_color_elem)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
#else
    UINT8 ui1_idx;

    /* set channel list bgcolor */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = APP_COLOR(e_color_type, APP_COLOR_ITEM_MAIN);
    t_clr_info.u_color_data.t_standard.t_enable      = APP_COLOR(e_color_type, APP_COLOR_ITEM_MAIN);
    t_clr_info.u_color_data.t_standard.t_highlight   = APP_COLOR(e_color_type, APP_COLOR_ITEM_MAIN);
    t_clr_info.u_color_data.t_standard.t_disable.a   = LST_BOX_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = LST_BOX_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = LST_BOX_BK_ALPHA;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    t_color_elem.t_normal              = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
    t_color_elem.t_disable             = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
    t_color_elem.t_highlight           = APP_COLOR(e_color_type, APP_COLOR_ITEM_TEXT_HLT);
    t_color_elem.t_highlight_unfocus   = APP_COLOR(e_color_type, APP_COLOR_ITEM_TEXT_HLT);
    t_color_elem.t_pushed              = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
    t_color_elem.t_selected            = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
    t_color_elem.t_selected_disable    = APP_COLOR(e_color_type, APP_COLOR_ITEM_CONTENT);
    t_color_elem.t_normal.a            = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_disable.a           = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_highlight.a         = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_highlight_unfocus.a = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_pushed.a            = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_selected.a          = LST_BOX_ELM_BK_ALPHA;
    t_color_elem.t_selected_disable.a  = LST_BOX_ELM_BK_ALPHA;

    /* element bg colors */
    i4_ret = c_wgl_do_cmd (
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_ELEM_COLOR,
                    WGL_PACK(WGL_CLR_BK),
                    WGL_PACK(&t_color_elem)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    for (ui1_idx = 0 ; ui1_idx < 4; ui1_idx++) {
        i4_ret = c_wgl_do_cmd (
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_COL_COLOR,
                    WGL_PACK_2(ui1_idx, WGL_CLR_BK),
                    WGL_PACK(&t_color_elem)
                    );
        if(WGLR_OK != i4_ret) {
            return NAVR_FAIL;
        }
    }
#endif

    /* set channel list column 3 font */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_COL_FONT,
                    WGL_PACK(3),
                    WGL_PACK(&t_g_ch_lst_elem_col3_font_info)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set channel list column 4 font */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_COL_FONT,
                    WGL_PACK(4),
                    WGL_PACK(&t_g_ch_lst_elem_col4_font_info)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set columns 0 inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = CH_LST_IMG_COL_TOP_INSET;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(0),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set columns 1 inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = CH_LST_IMG_COL_TOP_INSET;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(1),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set columns 2 inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = CH_LST_IMG_COL_TOP_INSET;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(2),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set columns 3 inset */
    t_inset.i4_left   = CH_LST_3_COL_LEFT_INSET;
    t_inset.i4_right  = CH_LST_3_COL_RIGHT_INSET;
    t_inset.i4_top    = CH_LST_3_COL_TOP_INSET;
    t_inset.i4_bottom = CH_LST_3_COL_BOTTOM_INSET;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(3),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set columns 4 inset */
    t_inset.i4_left   = CH_LST_4_COL_LEFT_INSET;
    t_inset.i4_right  = CH_LST_4_COL_RIGHT_INSET;
    t_inset.i4_top    = CH_LST_4_COL_TOP_INSET;
    t_inset.i4_bottom = CH_LST_4_COL_BOTTOM_INSET;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(4),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set content inset */
    t_inset.i4_left   = CH_LST_LEFT_INSET;
    t_inset.i4_right  = CH_LST_RIGHT_INSET;
    t_inset.i4_top    = CH_LST_TOP_INSET;
    t_inset.i4_bottom = CH_LST_BOTTOM_INSET;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_CNT_INSET,
                    WGL_PACK(&t_inset),
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set element inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_ELEM_INSET,
                    WGL_PACK(&t_inset),
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    t_color_elem.t_normal             = CH_LIST_COL_N_FG_COLOR(e_color_type);
    t_color_elem.t_disable            = CH_LIST_COL_D_FG_COLOR(e_color_type);
    t_color_elem.t_highlight          = CH_LIST_COL_H_FG_COLOR(e_color_type);
    t_color_elem.t_highlight_unfocus  = CH_LIST_COL_HU_FG_COLOR(e_color_type);
    t_color_elem.t_pushed             = CH_LIST_COL_P_FG_COLOR(e_color_type);
    t_color_elem.t_selected           = CH_LIST_COL_S_FG_COLOR(e_color_type);
    t_color_elem.t_selected_disable   = CH_LIST_COL_SD_FG_COLOR(e_color_type);

    /* column 3 fg colors */
    i4_ret = c_wgl_do_cmd (
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_COL_COLOR,
                    WGL_PACK_2(3, WGL_CLR_TEXT),
                    WGL_PACK(&t_color_elem)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* column 4 fg colors */
    i4_ret = c_wgl_do_cmd (
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_COL_COLOR,
                    WGL_PACK_2(4, WGL_CLR_TEXT),
                    WGL_PACK(&t_color_elem)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set channel list box's title */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_g_ch_lst_title_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = CH_LIST_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = CH_LIST_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = CH_LIST_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = LST_BOX_TITLE_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = LST_BOX_TITLE_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = LST_BOX_TITLE_FG_ALPHA;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_LB_TITLE_FG,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = CH_LIST_TITLE_BK_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = CH_LIST_TITLE_BK_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = CH_LIST_TITLE_BK_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = LST_BOX_TITLE_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = LST_BOX_TITLE_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = LST_BOX_TITLE_BK_ALPHA;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_LB_TITLE_BK,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set highlighted element effect inset */
    c_memset (& t_hlt_elem_effect, 0, sizeof (WGL_LB_HLT_ELEM_EFFECT_T));

    /* set text scrolling styles */
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 1;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    i4_ret = c_wgl_do_cmd (pt_view->h_ch_lst,
                              WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                              WGL_PACK (& t_hlt_elem_effect),
                              NULL);
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set up icon image buffer */
    i4_ret = nav_set_icon(
                    pt_view->h_pg_up_icon,
                    WGL_IMG_SET_STANDARD,
                    pt_view->h_img_red_btn,
                    pt_view->h_img_red_btn,
                    pt_view->h_img_red_btn,
                    WGL_AS_CENTER_CENTER
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* set up icon help msg */
    t_clr_info.e_type                                = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = DEFAULT_FG_ALPHA;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_pg_up_help_msg,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_pg_up_help_msg,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_LEFT_CENTER,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_pg_up_help_msg,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_g_ch_lst_help_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set dn icon image buffer */
    i4_ret = nav_set_icon(
                    pt_view->h_pg_dn_icon,
                    WGL_IMG_SET_STANDARD,
                    pt_view->h_img_green_btn,
                    pt_view->h_img_green_btn,
                    pt_view->h_img_green_btn,
                    WGL_AS_CENTER_CENTER
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* set dn icon help msg */
    t_clr_info.e_type                                = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = DEFAULT_FG_ALPHA;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_pg_dn_help_msg,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_pg_dn_help_msg,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_LEFT_CENTER,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_pg_dn_help_msg,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_g_ch_lst_help_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

#ifdef APP_SUPPORT_MULTIPLE_CHANNEL_LIST
    /* set sel list image buffer */
    i4_ret = nav_set_icon(
                    pt_view->h_sel_list_icon,
                    WGL_IMG_SET_STANDARD,
                    pt_view->h_img_yellow_btn,
                    pt_view->h_img_yellow_btn,
                    pt_view->h_img_yellow_btn,
                    WGL_AS_CENTER_CENTER
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* set sel list help msg */
    t_clr_info.e_type                                = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = DEFAULT_FG_ALPHA;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_sel_list_help_msg,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_sel_list_help_msg,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_LEFT_CENTER,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_sel_list_help_msg,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_g_ch_lst_help_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set sel list image buffer */
    i4_ret = nav_set_icon(
                    pt_view->h_exit_icon,
                    WGL_IMG_SET_STANDARD,
                    pt_view->h_img_blue_btn,
                    pt_view->h_img_blue_btn,
                    pt_view->h_img_blue_btn,
                    WGL_AS_CENTER_CENTER
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* set sel list help msg */
    t_clr_info.e_type                                = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = CH_LIST_HELP_MSG_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = DEFAULT_FG_ALPHA;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_exit_help_msg,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_exit_help_msg,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_LEFT_CENTER,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_exit_help_msg,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_g_ch_lst_help_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }


#endif /* APP_SUPPORT_MULTIPLE_CHANNEL_LIST */

    /* DTV00000742 - handle the BTN_SELECT key by navigator itself */
#ifdef APP_KEY_MIXED_PROG_UPDN_CURSOR_UPDN
    t_key_map.ui4_key_next      = BTN_PRG_DOWN;
    t_key_map.ui4_key_prev      = BTN_PRG_UP;
#else
    t_key_map.ui4_key_next      = BTN_CURSOR_DOWN;
    t_key_map.ui4_key_prev      = BTN_CURSOR_UP;
#endif
    t_key_map.ui4_key_select    = 0;
    t_key_map.ui4_key_page_up   = 0;
    t_key_map.ui4_key_page_down = 0;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_KEY_MAP,
                    WGL_PACK(& t_key_map),
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_view_set_msgs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *----------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_view_set_msgs(
                    NAV_CH_LST_VIEW_T*          pt_view
                    )
{
    WGL_LB_TITLE_INFO_T t_title;
    UTF16_T             w2s_title[256] = {0};
    INT32               i4_ret;

    /* channel list */
    t_title.ui1_align = WGL_AS_LEFT_CENTER;
    SET_RECT_BY_SIZE(
                    &t_title.t_rect,
                    CH_LST_TITLE_LEFT,
                    CH_LST_TITLE_TOP,
                    CH_LST_TITLE_WIDTH,
                    CH_LST_TITLE_HEIGHT
                    );
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_TITLE_INFO,
                    (VOID*)&t_title,
                    (VOID*)0
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Generate the title string. */
    c_uc_w2s_strcpy(w2s_title, pw2s_g_ch_lst_title);
#ifdef APP_SUPPORT_MULTIPLE_CHANNEL_LIST
    /* no channel selection in ATV only model */
    if (a_cfg_ftm_is_atv_only_model ()) {
        /* do not display channel list type */
    } else {
        c_uc_w2s_strcat(w2s_title, L" - ");
        c_uc_w2s_strcat(w2s_title, pw2s_g_ch_list_type);
    }
#endif

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_ch_lst,
                    WGL_CMD_LB_SET_TITLE_TEXT,
                    (VOID*)w2s_title,
                    (VOID*)(c_uc_w2s_strlen(w2s_title))
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_pg_up_help_msg,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)pw2s_g_page_up,
                    (VOID*)(c_uc_w2s_strlen(pw2s_g_page_up))
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_pg_dn_help_msg,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)pw2s_g_page_dn,
                    (VOID*)(c_uc_w2s_strlen(pw2s_g_page_dn))
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

#ifdef APP_SUPPORT_MULTIPLE_CHANNEL_LIST
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_sel_list_help_msg,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)pw2s_g_sel_list,
                    (VOID*)(c_uc_w2s_strlen(pw2s_g_sel_list))
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* In DVBS, Blue button is used as Satellite selection */
    if (b_g_is_dvbs_support && nav_ch_lst_is_under_satellite_mode())
    {
        i4_ret = c_wgl_do_cmd(
                        pt_view->h_exit_help_msg,
                        WGL_CMD_TEXT_SET_TEXT,
                        (VOID*)pw2s_g_satellite_selection,
                        (VOID*)(c_uc_w2s_strlen(pw2s_g_satellite_selection))
                        );
        if(WGLR_OK != i4_ret) {
            return NAVR_FAIL;
        }
    }
    else
    {
        i4_ret = c_wgl_do_cmd(
                        pt_view->h_exit_help_msg,
                        WGL_CMD_TEXT_SET_TEXT,
                        (VOID*)pw2s_g_exit,
                        (VOID*)(c_uc_w2s_strlen(pw2s_g_exit))
                        );
        if(WGLR_OK != i4_ret) {
            return NAVR_FAIL;
        }
    }

#endif

    return NAVR_OK;
}
/*---------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_view_frame_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_view_frame_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    NAV_CH_LST_T*       pt_this = NULL;
    NAV_CH_LST_VIEW_T*  pt_view = NULL;
    VOID*               pv_tag  = NULL;
    INT32               i4_ret;

    i4_ret = c_handle_get_tag(h_widget, &pv_tag);
    if (i4_ret == HR_OK && pv_tag != NULL) {
        pt_this = (NAV_CH_LST_T*)pv_tag;
        pt_view = &(pt_this->t_lst_view);

        switch(ui4_msg) {
        case WGL_MSG_NOTIFY:
        {
            HANDLE_T           h_child_widget = (HANDLE_T) pv_param1;
            WGL_NOTIFY_DATA_T* pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

            if (h_child_widget != pt_view->h_ch_lst) {
                break;
            }
            switch(pt_wgl_nfy_data->ui4_nc_code) {
            case WGL_NC_GL_KEY_DOWN:
                nav_ch_lst_rcu_key_handler(pt_wgl_nfy_data->u.t_key.ui4_key_code);
                break;
            case WGL_NC_GL_LOSE_FOCUS:
                break;
            case WGL_NC_LB_ELEM_HLT:
                if (pt_wgl_nfy_data->u.t_lb_elem_hlt.b_is_highlighted == FALSE) {
                    break;
                }
                nav_ch_lst_do_elem_hlt(
                            pt_this,
                            pt_wgl_nfy_data->u.t_lb_elem_sel.ui2_elem_idx
                            );
                break;
            case WGL_NC_LB_REACH_TOP:
                nav_ch_lst_do_reach_top(
                            pt_this
                            );
                break;
            case WGL_NC_LB_REACH_BOTTOM:
                nav_ch_lst_do_reach_bottom(
                            pt_this
                            );
                break;
            default:
                break;
            }
            break;
        }
        default:
            break;
        }
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );

    return i4_ret;
}
