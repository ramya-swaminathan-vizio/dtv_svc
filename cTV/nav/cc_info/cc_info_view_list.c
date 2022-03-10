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
 * $RCSfile: cc_info_view_list.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Randy Liu $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*randy 20060920*/
#ifdef APP_NAV_CC_SEL_LIST

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

#include "nav/nav_common.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"
#include "res/nav/cc_info/cc_info_view_list_custom.h"
#include "nav/cc_info/cc_info.h"
/*randy 20060918*/
#include "nav/cc_info/a_cc_info.h"
/*banner state mgr*/
#include "nav/banner/nav_bnr_state_mgr.h"

#if !(defined(APP_DVBT_SUPPORT) || defined(APP_ISDB_SUPPORT))
#ifndef APP_SEPARATED_CC_INFO

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef struct _NAV_CC_SELECT_VIEW_T
{
    /* Internal Control */
    
    _NAV_CI_T*            pt_ctrl;
    BOOL                        b_is_refreshing;     /* FALSE -> Do Process Notification */
                                                     /* TRUE  -> No Process Notification */
    /* Widgets */
                                                     
    HANDLE_T                    h_frame;
    HANDLE_T                    h_listbox;

    /* Widgets Resource: Template image */
    
    WGL_HIMG_TPL_T              h_lb_bk_img;
    WGL_HIMG_TPL_T              h_lb_ht_img;
        
} NAV_CC_SELECT_VIEW_T;

/*randy 20060918*/
#define IS_SYNC_REPAINT                         TRUE
#define NAV_CIVN_CC_DETAIL_STR_LEN              ((SIZE_T)64)
#define NAV_CIVN_UI_ITEMS                       (NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION) |            \
                                                 NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION_ICON))
typedef enum __NAV_CIVN_INTL_FALG_T
{
    _NAV_CIVN_IFLG_CAPTION_ICON_INIT_READY      = 0x00000001,
    _NAV_CIVN_IFLG_CAPTION_MSG_INIT_READY       = 0x00000002
} _NAV_CIVN_INTL_FALG_T;

typedef struct __NAV_CIVN_T
{
    HANDLE_T            h_caption_icon;         /*from state manager, cannot be destroyed*/
    HANDLE_T            h_caption_msg;          /*from state manager, cannot be destroyed*/
    _NAV_CIVN_INTL_FALG_T   e_intl_flag;
} _NAV_CIVN_T;


/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_CC_SELECT_VIEW_T t_g_nav_cc_select_view       = {0};

static BOOL                b_g_toggle_by_btn_cc_select = FALSE;
static BOOL                b_g_exit_by_btn_cc_select   = FALSE;
static BOOL                b_g_exit_by_btn_select     = FALSE;

/*randy 20060918*/
static UTF16_T           w2s_g_space[]  = {0x0020, 0};
static UTF16_T*          pw2s_g_cc      = NULL;
static UTF16_T*          pw2s_g_text    = NULL;
static UTF16_T*          pw2s_g_service = NULL;
#if 0
static UTF16_T*          pw2s_g_off     = NULL;
#endif

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

static INT32 _nav_cc_select_view_frame_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );

static INT32 _nav_cc_select_view_listbox_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );

static INT32  __cc_select_listbox_load_skin(VOID);

/*randy 20060918*/
/*view handler*/
static INT32 _nav_cilb_data_change(VOID*                    pv_view,
                                   NAV_CI_UI_INFO_FIELD_T   e_update_field,
                                   const NAV_CI_UI_INFO_T*  pt_update_data);

static INT32 _nav_cilb_key_handler(VOID*                pv_view,
                                   UINT32               ui4_key_code);

/**/
static VOID _nav_cilb_load_msgs(UINT8                  ui1_lang_id);

static INT32 _nav_cilb_update_detail(_NAV_CIVN_T*                   pt_this,
                                     const NAV_CI_UI_CC_DETAIL_T*   pt_cc_detail);

static INT32 _nav_cilb_update_dscrptr(_NAV_CIVN_T*                  pt_this,
                                      NAV_CI_UI_INFO_STATUS_T       e_dscrptr_status);

static INT32 _nav_cilb_get_detail(NAV_CI_CC_TYPE_T     e_cc_type,
                                  UINT8                ui1_cc_id,
                                  UTF16_T*             pw2s_string,
                                  SIZE_T               z_str_len);

static INT32 _nav_cilb_get_off_detail(UTF16_T*         pw2s_string,
                                      SIZE_T           z_str_len);

/*randy 20060918*/
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_cc_select_get_active
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_cc_select_get_active(
    UINT8*                    pui1_idx)
{
    NAV_CC_SELECT_VIEW_T* pt_view = &t_g_nav_cc_select_view;
    INT32                       i4_ret;
    UINT16                      ui2_idx;
    
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_GET_SEL_INDEXES,
                          WGL_PACK((UINT16)1),      /* buffer size */
                          WGL_PACK(&ui2_idx));      /* the buffer  */
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to get active index. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
    *pui1_idx = ui2_idx;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_cc_select_get_ht
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_cc_select_get_ht(
    UINT8*                pui1_idx)
{
    NAV_CC_SELECT_VIEW_T* pt_view = &t_g_nav_cc_select_view;
    INT32                       i4_ret;
    UINT16                      ui2_idx;
    
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(&ui2_idx),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to get highlight index. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
    *pui1_idx = ui2_idx;

    return NAVR_OK;
}

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
static INT32 __cc_select_create_image(VOID)
{
    INT32    i4_ret;
    NAV_CC_SELECT_VIEW_T* pt_view = &t_g_nav_cc_select_view;

    /* listbox background image */
    /* listbox bar (highlight image) */

    i4_ret = nav_cc_select_custom_view_list_create_image(&pt_view->h_lb_bk_img,
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
static INT32 __cc_select_create_frame(
                    HANDLE_T                       h_parent,
                    INT32                          i4_frame_x_offset,
                    INT32                          i4_frame_y_offset
                    )
{
    NAV_CC_SELECT_VIEW_T* pt_view = &t_g_nav_cc_select_view;
    GL_RECT_T                           t_rect;
    INT32                               i4_ret;

    /* create channel frame */
    SET_RECT_BY_SIZE(&t_rect,
                     NAV_CC_SELECT_LST_FM_LEFT + i4_frame_x_offset,
                     NAV_CC_SELECT_LST_FM_TOP  + i4_frame_y_offset,
                     NAV_CC_SELECT_LST_FM_WIDTH,
                     NAV_CC_SELECT_LST_FM_HEIGHT);
    
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _nav_cc_select_view_frame_wdgt_proc_fct,
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
static INT32 __cc_select_create_listbox(
                    HANDLE_T                       h_parent,
                    UINT16                         ui2_elem_num
                    )
{
    NAV_CC_SELECT_VIEW_T* pt_view = &t_g_nav_cc_select_view;
    INT32                                 i4_ret;
    UINT16                                ui2_idx;
    GL_RECT_T                             t_rect;
    WGL_LB_INIT_T                         t_init_info;
    WGL_LB_TITLE_INFO_T                   t_title_info;    
    WGL_LB_COL_INIT_T                     at_cols[1];
    
    WGL_LB_ITEM_T                         at_items[1];
    

    /* Sound Effect column */
    at_cols[0].e_col_type         = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align          = NAV_CC_SELECT_LST_BOX_NAME_ALIGNMENT;
    at_cols[0].ui2_width          = NAV_CC_SELECT_LST_BOX_NAME_WIDHT;
    at_cols[0].ui2_max_text_len   = NAV_CC_SELECT_LST_BOX_NAME_MAX_TEXT_LEN;

    t_init_info.ui4_style                   = NAV_CC_SELECT_LST_BOX_STYLE;
    t_init_info.ui2_max_elem_num            = ui2_elem_num;
    t_init_info.ui2_elem_size               = NAV_CC_SELECT_LST_BOX_ELEM_HEIGHT;
    t_init_info.ui2_elem_distance           = NAV_CC_SELECT_LST_BOX_ELEM_DTANCE;
    t_init_info.ui1_col_num                 = 1;
    t_init_info.at_cols                     = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     NAV_CC_SELECT_LST_BOX_LEFT,
                     NAV_CC_SELECT_LST_BOX_TOP,
                     NAV_CC_SELECT_LST_BOX_WIDTH,
                     NAV_CC_SELECT_LST_BOX_HEIGHT(ui2_elem_num));

    i4_ret = c_wgl_create_widget(h_parent, 
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _nav_cc_select_view_listbox_wdgt_proc_fct,
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
    t_title_info.ui1_align = NAV_CC_SELECT_LST_TITLE_ALIGN;
    
    SET_RECT_BY_SIZE(&t_title_info.t_rect,
                     NAV_CC_SELECT_LST_TITLE_LEFT,
                     NAV_CC_SELECT_LST_TITLE_TOP,
                     NAV_CC_SELECT_LST_TITLE_WIDTH,
                     NAV_CC_SELECT_LST_TITLE_HEIGHT);

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_TITLE_INFO,
                          (VOID*)&t_title_info,
                          (VOID*)0);
                          
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);

    /* Set Skin */

    i4_ret = __cc_select_listbox_load_skin();
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);    

    /* Insert ui2_elem_num nothing field first */

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = NULL;
    
    for(ui2_idx = 0 ; ui2_idx < ui2_elem_num ; ui2_idx++)
    {
        i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);
    }

    /* Launch Customer layer setting */
    /* For additional effect for Scroll Bar, etc. */

    nav_cc_select_custom_view_list_create_listbox_postinit(pt_view->h_listbox);
    
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
static INT32  __cc_select_listbox_load_skin(VOID)
{
    NAV_CC_SELECT_VIEW_T* pt_view = &t_g_nav_cc_select_view;
    WGL_COLOR_INFO_T                         t_clr_info;
    WGL_INSET_T                              t_inset;
    WGL_LB_COLOR_ELEM_SET_T                  t_color_elem;
    WGL_IMG_INFO_T                           t_img_info;
    WGL_LB_IMG_ELEM_SET_T                    t_img_elem = {0};
    INT32                                    i4_ret;
    
   /* listbox view port background color */
    t_clr_info.e_type              = WGL_COLOR_SET_STANDARD;
    
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_nav_cc_select_color_listbox_vp_bk;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_nav_cc_select_color_listbox_vp_bk;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_nav_cc_select_color_listbox_vp_bk;
    
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_VP_BK),
                          WGL_PACK(&t_clr_info));
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);

    /* listbox background image */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_view->h_lb_bk_img;
    t_img_info.u_img_data.t_standard.t_disable   = pt_view->h_lb_bk_img;
    t_img_info.u_img_data.t_standard.t_highlight = pt_view->h_lb_bk_img;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);

    /* element image background */
    t_img_elem.h_highlight           = pt_view->h_lb_ht_img;
    t_img_elem.h_highlight_unfocus   = pt_view->h_lb_ht_img;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                          WGL_PACK(& t_img_elem),
                          NULL);
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);                          

    /* element background colors */
    t_color_elem.t_normal              = t_g_nav_cc_select_color_listbox_elem_bk;
    t_color_elem.t_disable             = t_g_nav_cc_select_color_listbox_elem_bk;
    t_color_elem.t_highlight           = t_g_nav_cc_select_color_listbox_elem_bk;
    t_color_elem.t_highlight_unfocus   = t_g_nav_cc_select_color_listbox_elem_bk;
    t_color_elem.t_pushed              = t_g_nav_cc_select_color_listbox_elem_bk;
    t_color_elem.t_selected            = t_g_nav_cc_select_color_listbox_elem_bk;
    t_color_elem.t_selected_disable    = t_g_nav_cc_select_color_listbox_elem_bk;

    i4_ret = c_wgl_do_cmd (pt_view->h_listbox,
                           WGL_CMD_LB_SET_ELEM_COLOR,
                           WGL_PACK(WGL_CLR_BK),
                           WGL_PACK(&t_color_elem));
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);                          

    /*column bk color*/
    t_color_elem.t_normal              = t_g_nav_cc_select_color_listbox_col_bk;
    t_color_elem.t_disable             = t_g_nav_cc_select_color_listbox_col_bk;
    t_color_elem.t_highlight           = t_g_nav_cc_select_color_listbox_col_bk;
    t_color_elem.t_highlight_unfocus   = t_g_nav_cc_select_color_listbox_col_bk;
    t_color_elem.t_pushed              = t_g_nav_cc_select_color_listbox_col_bk;
    t_color_elem.t_selected            = t_g_nav_cc_select_color_listbox_col_bk;
    t_color_elem.t_selected_disable    = t_g_nav_cc_select_color_listbox_col_bk;

    /* one column only */

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_BK),
                          WGL_PACK(&t_color_elem));
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);                          

    /*set Sound Effect text color*/
    t_color_elem.t_normal              = t_g_nav_cc_select_color_listbox_elem_fg;
    t_color_elem.t_disable             = t_g_nav_cc_select_color_listbox_elem_fg;
    t_color_elem.t_highlight           = t_g_nav_cc_select_color_listbox_elem_fg_hlt;
    t_color_elem.t_highlight_unfocus   = t_g_nav_cc_select_color_listbox_elem_fg_hlt;
    t_color_elem.t_pushed              = t_g_nav_cc_select_color_listbox_elem_fg;
    t_color_elem.t_selected            = t_g_nav_cc_select_color_listbox_elem_fg;
    t_color_elem.t_selected_disable    = t_g_nav_cc_select_color_listbox_elem_fg;
    
    i4_ret = c_wgl_do_cmd (pt_view->h_listbox,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(0, WGL_CLR_TEXT),
                           WGL_PACK(&t_color_elem));
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);                             

    /*Title's foreground color*/
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = t_g_nav_cc_select_color_listbox_title_fg;
    t_clr_info.u_color_data.t_standard.t_enable      = t_g_nav_cc_select_color_listbox_title_fg;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_g_nav_cc_select_color_listbox_title_fg;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_LB_TITLE_FG,
                          &t_clr_info);
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);                             

    /*Title's background color*/
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = t_g_nav_cc_select_color_listbox_title_bk;
    t_clr_info.u_color_data.t_standard.t_enable      = t_g_nav_cc_select_color_listbox_title_bk;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_g_nav_cc_select_color_listbox_title_bk;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_LB_TITLE_BK,
                          &t_clr_info);
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);                             

    /* set Sound Effect's font */
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_COL_FONT,
                          WGL_PACK(0),
                          WGL_PACK(&t_g_cc_select_text_font_info));
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);                             

    /* set Title's font */
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_GL_SET_FONT,
                          (VOID*)&t_g_cc_select_title_font_info,
                          NULL);                          
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);                             

    /* set Sound Effect's inset */
    NAV_CC_SELECT_LST_BOX_NAME_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(0),
                          WGL_PACK(&t_inset));
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);                             

    /* set content inset */
    NAV_CC_SELECT_LST_BOX_CONTENT_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);                                                       

    /* set element inset */
    NAV_CC_SELECT_LST_BOX_ELEM_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
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
static INT32 __cc_select_listbox_on_notify(WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_LB_ELEM_SEL:
        {
            UINT16 i2_idx = pt_nfy_data->u.t_lb_elem_sel.ui2_elem_idx;
            BOOL b_sel = pt_nfy_data->u.t_lb_elem_sel.b_is_selected;

                if(b_sel)
                {
                    nav_cc_select_ctrl_set_index(i2_idx);
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
 *              Currently, it listens BTN_CC
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 * 
 ----------------------------------------------------------------------------*/ 
static BOOL _nav_cc_select_view_is_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    switch (ui4_key_code) {
    case BTN_CC:
        return TRUE;
    default:
        return FALSE;
    }
}

/*----------------------------------------------------------------------------
 * Name: 
 *
 * Description: Activate the view, focus on the "Listbox"
 *              Currently, it listens BTN_CC.
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 * 
 ----------------------------------------------------------------------------*/ 
static INT32 _nav_cc_select_view_activate(
                    UINT32                      ui4_key_code
                    )
{
    NAV_CC_SELECT_VIEW_T*  pt_view = &t_g_nav_cc_select_view;
    INT32                 i4_ret;

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
static INT32 _nav_cc_select_view_hide(
                    VOID
                    )
{
    NAV_CC_SELECT_VIEW_T* pt_view = &t_g_nav_cc_select_view;
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
static VOID _nav_cc_select_view_rcu_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    NAV_CC_SELECT_VIEW_T* pt_view = &t_g_nav_cc_select_view;
    INT32                 i4_ret;
    UINT8                 ui1_idx;

    switch(ui4_key_code) {
    case BTN_CC:
    case BTN_CURSOR_UP:
    case BTN_CURSOR_DOWN:
        nav_cc_select_reset_timer(pt_view->pt_ctrl);
        break;
    /*randy 20060918*/
    case BTN_SELECT:
        nav_cc_select_reset_timer(pt_view->pt_ctrl);
        nav_cc_select_get_ht(&ui1_idx);
        a_cfg_custom_set_cc (ui1_idx); 
        nav_cc_select_cc_state_classify(ui1_idx);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to classify CC state. i4_ret = %d\r\n", i4_ret));
        }        

        if(b_g_exit_by_btn_select)
        {
            ui4_key_code = (UINT32) BTN_EXIT;
            nav_rcu_key_handler(ui4_key_code);
        }
        break;
 
    default:
        nav_rcu_key_handler(ui4_key_code);
        break;
    }
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
static INT32 _nav_cc_select_view_frame_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32 i4_ret;
    NAV_CC_SELECT_VIEW_T*  pt_view = &t_g_nav_cc_select_view;
    
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
                    __cc_select_listbox_on_notify(pt_nfy_data);
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

static INT32 _nav_cc_select_view_listbox_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32 i4_ret;
    BOOL  b_processed = FALSE;

    /* Can be customized */
    /* Translate BTN_CC => BTN_CURSOR_DOWN */
       
    if(b_g_toggle_by_btn_cc_select)
    {
        if( (UINT32) pv_param1 == BTN_CC )
        {
            pv_param1 = (VOID *) BTN_CURSOR_DOWN;
        }
    }

    /* Can be customized */
    /* Translate BTN_CC => BTN_EXIT */

    if(b_g_exit_by_btn_cc_select)
    {
        if( (UINT32) pv_param1 == BTN_CC )
        {
            pv_param1 = (VOID *) BTN_EXIT;
        }
    }
    
    /* Can be customized */
    /* Translate BTN_SELECT => BTN_EXIT */

    /*randy 20060918*/
    /*if(b_g_exit_by_btn_select)
    {
        if( (UINT32) pv_param1 == BTN_SELECT )
        {
            pv_param1 = (VOID *) BTN_EXIT;
        }
    }*/

    /* Can be customized */
    /* The listbox wdgt proc fct */
    i4_ret = nav_cc_select_custom_view_list_listbox_wdgt_proc_fct(h_widget,
                                                                 ui4_msg,
                                                                 pv_param1,
                                                                 pv_param2,
                                                                 &b_processed);

    if(b_processed)
    {
        return NAVR_OK;
    }

    switch(ui4_msg) {
    case WGL_MSG_KEY_DOWN:
    
        /* Run NAV default key handler first */
        _nav_cc_select_view_rcu_key_handler((UINT32)pv_param1);
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

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_cc_select_view_init(
                    _NAV_CI_T*                     pt_ctrl,
                    HANDLE_T                       h_canvas,
                    INT32                          i4_frame_x_offset,
                    INT32                          i4_frame_y_offset,
                    UINT16                         ui2_elem_num
                    )
{
    NAV_CC_SELECT_VIEW_T* pt_view = &t_g_nav_cc_select_view;
    INT32                i4_ret;

    /* Save the ctrl to view */
    pt_view->pt_ctrl = pt_ctrl;

    /* create image */
    __cc_select_create_image();

    /* create frame */
    __cc_select_create_frame(h_canvas,
                            i4_frame_x_offset,
                            i4_frame_y_offset);
    /* create listbox */
    __cc_select_create_listbox(pt_view->h_frame,
                              ui2_elem_num);

    i4_ret = c_wgl_show(pt_view->h_frame, WGL_SW_HIDE);
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);
    
    /* Customization Environment */

    b_g_toggle_by_btn_cc_select = NAV_CC_SELECT_TOGGLE_BY_BTN_CC;
    b_g_exit_by_btn_cc_select   = NAV_CC_SELECT_EXIT_BY_BTN_CC;
    b_g_exit_by_btn_select     = NAV_CC_SELECT_EXIT_BY_BTN_SELECT;
    
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
static INT32 _nav_cc_select_view_deinit(
                    VOID
                    )
{
    NAV_CC_SELECT_VIEW_T* pt_view = &t_g_nav_cc_select_view;

    c_wgl_destroy_widget(pt_view->h_frame);
    c_wgl_destroy_widget(pt_view->h_listbox);
    c_wgl_img_tpl_destroy(pt_view->h_lb_bk_img);
    c_wgl_img_tpl_destroy(pt_view->h_lb_ht_img);

    pt_view->pt_ctrl     = NULL;
    pt_view->h_frame     = NULL_HANDLE;
    pt_view->h_listbox   = NULL_HANDLE;
    pt_view->h_lb_bk_img = NULL_HANDLE;
    pt_view->h_lb_ht_img = NULL_HANDLE;
    
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
static INT32 _nav_cc_select_view_set_hlt_index(UINT16    ui2_idx)
{
    INT32    i4_ret;
    NAV_CC_SELECT_VIEW_T *pt_view = &t_g_nav_cc_select_view;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(ui2_idx),
                          NULL);
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);                          
    

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
static INT32 _nav_cc_select_view_set_index_text(UINT16    ui2_idx,
                                               UTF16_T*  pw2s_text)
{
    INT32    i4_ret;
    NAV_CC_SELECT_VIEW_T *pt_view = &t_g_nav_cc_select_view;

    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(ui2_idx, 0),
                          WGL_PACK(pw2s_text));
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);

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
static INT32 _nav_cc_select_view_set_is_refreshing(BOOL      b_is_refreshing)
{
    NAV_CC_SELECT_VIEW_T *pt_view = &t_g_nav_cc_select_view;

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
static INT32 _nav_cc_select_view_set_title_text(UTF16_T*  pw2s_title)
                                               
{
    INT32    i4_ret;
    NAV_CC_SELECT_VIEW_T *pt_view = &t_g_nav_cc_select_view;

    /*set title*/
    i4_ret = c_wgl_do_cmd(pt_view->h_listbox,
                          WGL_CMD_LB_SET_TITLE_TEXT,
                          (VOID*)pw2s_title,
                          (VOID*)((NULL == pw2s_title) ? 0 : c_uc_w2s_strlen(pw2s_title)));
    NAV_CC_SELECT_LOG_ON_FAIL(i4_ret);
    
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
INT32 nav_cc_select_view_register_list_hdlr(
                    NAV_CI_VIEW_HANDLER_T*      pt_view_hdlr
                    )
{
    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init              = _nav_cc_select_view_init;
    pt_view_hdlr->pf_deinit            = _nav_cc_select_view_deinit;
    pt_view_hdlr->pf_is_key_handler    = _nav_cc_select_view_is_key_handler;
    pt_view_hdlr->pf_activate          = _nav_cc_select_view_activate;
    pt_view_hdlr->pf_hide              = _nav_cc_select_view_hide;
    pt_view_hdlr->pf_set_hlt_index     = _nav_cc_select_view_set_hlt_index;
    pt_view_hdlr->pf_set_index_text    = _nav_cc_select_view_set_index_text;
    pt_view_hdlr->pf_set_is_refreshing = _nav_cc_select_view_set_is_refreshing;
    pt_view_hdlr->pf_set_title_text    = _nav_cc_select_view_set_title_text;
    /*randy 20060918*/
    pt_view_hdlr->pf_data_change       = _nav_cilb_data_change;
    pt_view_hdlr->pf_key_handler       = _nav_cilb_key_handler;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_cilb_data_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_cilb_data_change(
    VOID*                          pv_view,
    NAV_CI_UI_INFO_FIELD_T         e_update_field,
    const NAV_CI_UI_INFO_T*        pt_update_data)
{
    _NAV_CIVN_T*                   pt_this = (_NAV_CIVN_T*)pv_view;

    if(NULL == pv_view) /*before init*/
    {
        return NAVR_OK;
    }

    NAV_ASSERT(pt_update_data);

    if(NAV_CI_IF_GUI_LANG & e_update_field)
    {
        _nav_cilb_load_msgs(pt_update_data->ui1_gui_lang_id);
    }

    if(NAV_CI_IF_DSCRPTR & e_update_field)
    {
        _nav_cilb_update_dscrptr(pt_this, pt_update_data->e_dscrptr_status);
    }

    if(NAV_CI_IF_DETAIL & e_update_field)
    {
        _nav_cilb_update_detail(pt_this, &pt_update_data->t_cc_detail);
    }

    if(NAV_CI_IF_STATE_ITEM & e_update_field)
    {
        pt_this->e_intl_flag &= ~(_NAV_CIVN_IFLG_CAPTION_ICON_INIT_READY | 
                                  _NAV_CIVN_IFLG_CAPTION_MSG_INIT_READY);
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_cilb_load_msgs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_cilb_load_msgs(
    UINT8                       ui1_lang_id)
{
    pw2s_g_cc       = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_NTSC_CC);
    pw2s_g_text     = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_NTSC_TEXT);
    pw2s_g_service  = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_DTVCC_SERVICE);
#if 0    
    pw2s_g_off      = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_OFF);
#endif    
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_cilb_update_detail
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_cilb_update_detail(
    _NAV_CIVN_T*                     pt_this,
    const NAV_CI_UI_CC_DETAIL_T*     pt_cc_detail)
{
    UTF16_T                          w2s_string[NAV_CIVN_CC_DETAIL_STR_LEN + 1] = {0};
    UTF16_T                          w2s_unknown_lang[ISO_639_LANG_LEN] = {0};
    UTF16_T*                         pw2s_cc_lang;
    SIZE_T                           z_len;
    INT32                            i4_ret;
    BNR_ITEM_SET_T                         t_orig_visible;
    UINT8                            ui1_type;

    do 
    {
        if(NAV_CI_UI_IS_NOT_READY == pt_cc_detail->e_status || NAV_CI_UI_IS_INIT_VALUE == pt_cc_detail->e_status)
        {
            break;
        }

        if(NAV_CI_UI_IS_WITHOUT == pt_cc_detail->e_status)
        {
            i4_ret = _nav_cilb_get_off_detail(w2s_string,
                                              NAV_CIVN_CC_DETAIL_STR_LEN + 1);
            if(NAVR_OK != i4_ret)
            {
                return i4_ret;
            }

            break;
        }

        /*update description*/
        i4_ret = _nav_cilb_get_detail(pt_cc_detail->e_cc_type,
                                      pt_cc_detail->ui1_cc_id,
                                      w2s_string,
                                      NAV_CIVN_CC_DETAIL_STR_LEN + 1);
        if(NAVR_OK != i4_ret)
        {
            return i4_ret;
        }

        /*update language*/
        if((NAV_CI_UI_IS_INIT_VALUE == pt_cc_detail->e_lang_status) ||
           (NAV_CI_UI_IS_NOT_READY == pt_cc_detail->e_lang_status) ||
           (NAV_CI_UI_IS_WITHOUT == pt_cc_detail->e_lang_status))
        {
            break;
        }

        /*get language string*/
        pw2s_cc_lang = nav_get_display_lang(&pt_cc_detail->s639_lang);

        if(NULL == pw2s_cc_lang && 0 < c_strlen((const CHAR*)&pt_cc_detail->s639_lang))
        {            
            i4_ret = c_uc_ps_to_w2s((const CHAR*)&pt_cc_detail->s639_lang,
                                    w2s_unknown_lang,
                                    ISO_639_LANG_LEN);
            if(UCR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"Fail to convert unknown CC lang(%s) from UTF8 to UFT16. i4_ret = %d\r\n", pt_cc_detail->s639_lang, i4_ret));
            }
            else
            {
                pw2s_cc_lang = w2s_unknown_lang;
            }
        }

        if(pw2s_cc_lang)
        {
            /*append space*/
            z_len = c_uc_w2s_strlen(w2s_string);    /*z_len is less than or equal to NAV_CIVN_CC_DETAIL_STR_LEN*/
            c_uc_w2s_strncat(w2s_string, w2s_g_space, NAV_CIVN_CC_DETAIL_STR_LEN - z_len);

            /*append language*/
            z_len = c_uc_w2s_strlen(w2s_string);    /*z_len is less than or equal to NAV_CIVN_CC_DETAIL_STR_LEN*/
            c_uc_w2s_strncat(w2s_string, pw2s_cc_lang, NAV_CIVN_CC_DETAIL_STR_LEN - z_len);
        }
        
    } while(0);

    /*get Caption current status*/
    i4_ret = nav_bnr_state_is_items_visible(NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION),
                                            &t_orig_visible);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to query CAPTION's status. i4_ret = %d\r\n", i4_ret));
        return i4_ret;
    }

    /*get Caption-msg widget*/
    if(!(_NAV_CIVN_IFLG_CAPTION_MSG_INIT_READY & pt_this->e_intl_flag))
    {
        i4_ret = nav_bnr_state_get_item_widget(NAV_BNR_STATE_II_CAPTION,
                                               &pt_this->h_caption_msg,
                                               &ui1_type);
        if(NAVR_OK != i4_ret)
        {
            pt_this->h_caption_msg = NULL_HANDLE;
            DBG_ERROR((_ERROR_HEADER"Fail to get CAPTION's handle. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }
        
        /*turn on ready-flag*/
        pt_this->e_intl_flag |= _NAV_CIVN_IFLG_CAPTION_MSG_INIT_READY;
    }

    if(NULL_HANDLE != pt_this->h_caption_msg)
    {
        /*update cc detail widget*/
        i4_ret = c_wgl_do_cmd(pt_this->h_caption_msg,
                              WGL_CMD_TEXT_SET_TEXT,
                              (VOID*)w2s_string,
                              (VOID*)NAV_CIVN_CC_DETAIL_STR_LEN);
        if(i4_ret != WGLR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to set the cc detail to detail widget of CC-Info-Banner. i4_ret = %d\r\n", i4_ret));
            return NAVR_FAIL;
        }

        /*repaint detail widget if visible*/
        if(t_orig_visible)
        {
            i4_ret = c_wgl_repaint(pt_this->h_caption_msg,
                                   NULL,
                                   IS_SYNC_REPAINT);
            if(i4_ret != WGLR_OK)
            {
                DBG_ERROR((_ERROR_HEADER"Fail to raise a repaint for the msg widget of CC-Info-Banner. i4_ret = %d\r\n", i4_ret));
                return NAVR_FAIL;
            }
        }
        else
        {
            /*make Caption-Icon visible*/
            /*nav_bnr_state_set_items_visible(NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION),
                                            NAV_BNR_STATE_OT_CRNT_FIRST,
                                            NAV_CTM_BS_CAPTION_ICON_PRI,
                                            NULL);*/
        }
    }
    
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_cilb_update_dscrptr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_cilb_update_dscrptr(
    _NAV_CIVN_T*                      pt_this,
    NAV_CI_UI_INFO_STATUS_T           e_dscrptr_status)
{
    BNR_ITEM_SET_T                          t_orig_visible;
    INT32                             i4_ret;
    UINT8                             ui1_type;
    BOOL                              b_show_icon;

    if((NAV_CI_UI_IS_INIT_VALUE == e_dscrptr_status) ||
       (NAV_CI_UI_IS_NOT_READY == e_dscrptr_status) ||
       (NAV_CI_UI_IS_WITHOUT == e_dscrptr_status))
    {
        b_show_icon = FALSE;
    }
    else
    {
        b_show_icon = TRUE;
    }

    /*get Caption-Icon current status*/
    i4_ret = nav_bnr_state_is_items_visible(NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION_ICON),
                                            &t_orig_visible);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to query CAPTION-ICON's status. i4_ret = %d\r\n", i4_ret));
        return i4_ret;
    }

    /*get Caption-Icon*/
    if(!(_NAV_CIVN_IFLG_CAPTION_ICON_INIT_READY & pt_this->e_intl_flag))
    {
        i4_ret = nav_bnr_state_get_item_widget(NAV_BNR_STATE_II_CAPTION_ICON,
                                               &pt_this->h_caption_icon,
                                               &ui1_type);
        if(NAVR_OK != i4_ret)
        {
            pt_this->h_caption_icon = NULL_HANDLE;
            DBG_ERROR((_ERROR_HEADER"Fail to get CAPTION-ICON's handle. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }

        /*turn on ready-flag*/
        pt_this->e_intl_flag |= _NAV_CIVN_IFLG_CAPTION_ICON_INIT_READY;
    }
    
    if(NULL_HANDLE != pt_this->h_caption_icon)
    {
        /*show/hide cc icon*/
        i4_ret = c_wgl_set_visibility(pt_this->h_caption_icon, 
                                      (b_show_icon) ? WGL_SW_NORMAL : WGL_SW_HIDE);
        if(i4_ret != WGLR_OK) 
        {
            DBG_ERROR((_ERROR_HEADER"Fail to change the visibility of the caption-icon widget of CC-Info-Banner. i4_ret = %d\r\n", i4_ret));
            return NAVR_FAIL;
        }

        if(t_orig_visible)
        {
            /*refresh Caption-Icon widget*/
            i4_ret = c_wgl_repaint(pt_this->h_caption_icon,
                                   NULL,
                                   IS_SYNC_REPAINT);
            if(i4_ret != WGLR_OK)
            {
                DBG_ERROR((_ERROR_HEADER"Fail to raise a repaint for CAPTION-ICON. i4_ret = %d\r\n", i4_ret));
                return NAVR_FAIL;
            }
        }
        else
        {
            /*make Caption-Icon visible*/
            /*nav_bnr_state_set_items_visible(NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION_ICON),
                                            NAV_BNR_STATE_OT_CRNT_FIRST,
                                            NAV_CTM_BS_CAPTION_ICON_PRI,
                                            NULL);*/
        }
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_cilb_get_detail
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
 static INT32 _nav_cilb_get_detail(
     NAV_CI_CC_TYPE_T              e_cc_type,
     UINT8                         ui1_cc_id,
     UTF16_T*                      pw2s_string,
     SIZE_T                        z_str_len)

{
    UTF16_T* pw2s_cc_string = NULL;
    CHAR     s_cc_id[4]     = {0};
    UTF16_T  w2s_cc_id[4]   = {0};
    INT32    i4_ret;

    switch(e_cc_type) 
    {
    case NAV_CI_CC_TYPE_NTSC_CC:
        pw2s_cc_string = pw2s_g_cc;
        break;

    case NAV_CI_CC_TYPE_NTSC_TEXT:
        pw2s_cc_string = pw2s_g_text;
        break;

    case NAV_CI_CC_TYPE_DIG:
        pw2s_cc_string = pw2s_g_service;
        break;

    case NAV_CI_CC_TYPE_INIT_VALUE:
    default:
        {
            if(z_str_len > 0)
            {
                pw2s_string[0] = '\0';
            }
        }
    }
        
    /*convert cc_id to string*/
    c_sprintf(s_cc_id, "%d", ui1_cc_id);
    i4_ret = c_uc_ps_to_w2s(s_cc_id, w2s_cc_id, 3);
    if (UCR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to convert cc-id to string. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    if(z_str_len >= (c_uc_w2s_strlen(pw2s_cc_string) + 3 + 1)) /* 3: cc_id length, 1: null-terminated character*/
    {
        c_uc_w2s_strcat(pw2s_string, pw2s_cc_string);
        c_uc_w2s_strcat(pw2s_string, w2s_cc_id);
    }
    else
    {
        DBG_ERROR((_ERROR_HEADER"Buffer size for cc info is too small.\r\n"));
        NAV_ASSERT(0);
    }

    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
 * Name
 *      _nav_cilb_get_off_detail
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_cilb_get_off_detail(
    UTF16_T*                          pw2s_string,
    SIZE_T                            z_str_len)
{
#if 0
    if(z_str_len >= (c_uc_w2s_strlen(pw2s_g_off) + 1)) /* 1: null-terminated character*/
    {
        c_uc_w2s_strcat(pw2s_string, pw2s_g_off);
    }
    else
    {
        DBG_ERROR((_ERROR_HEADER"Buffer size for cc off is too small.\r\n"));
        NAV_ASSERT(0);
    }
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_cilb_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_cilb_key_handler(
    VOID*                          pv_view,
    UINT32                         ui4_key_code)
{
    INT32                          i4_ret;
    UINT8                          ui1_cc = APP_CFG_CUST_CC_OFF;    

    do
    {
        /*play default cc*/
        /*randy 20060918*/
        a_cfg_custom_get_cc (& ui1_cc);
        nav_cc_select_cc_state_classify(ui1_cc);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to classify CC state. i4_ret = %d\r\n", i4_ret));
        }

        i4_ret = NAVR_NO_ACTION;

    } while(0);

    /*restart timer*/
    /*nav_bnr_state_timer_op(NAV_BNR_STATE_TMOT_BY_STATE);*/

    return i4_ret;              /*not to be the key owner*/
}
#endif /*#ifndef APP_SEPARATED_CC_INFO*/
#endif /*#ifndef APP_DVBT_SUPPORT*/
#endif /*APP_NAV_CC_SEL_LIST*/
