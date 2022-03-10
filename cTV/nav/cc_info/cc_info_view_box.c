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
 * $RCSfile: cc_info_view_box.c,v $
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
#include "u_common.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_handle.h"
#include "c_gl.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"

#include "nav/cc_info/a_cc_info.h"
#include "nav/cc_info/cc_info.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"

/*banner state mgr*/
#include "nav/nav_bnr_state_mgr.h"

#if !(defined(APP_DVBT_SUPPORT) || defined(APP_ISDB_SUPPORT)) && defined(APP_SEPARATED_CC_INFO)

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#ifndef NAV_CI_TIMER_DELAY
#define NAV_CI_TIMER_DELAY                      (2000) /* in ms */
#endif

#define IS_SYNC_REPAINT                         TRUE
#ifdef APP_IMG_UI
#define FRAME_STYLE                             (NULL)
#else
#define FRAME_STYLE                             ((VOID*)(WGL_STL_GL_NO_IMG_UI))
#endif

#define NAV_CIVX_CC_DETAIL_STR_LEN              ((SIZE_T)64)

typedef enum __NAV_CIVX_INTL_FALG_T
{
    _NAV_CIVX_IFLG_CAPTION_ICON_INIT_READY      = 0x00000001,
    _NAV_CIVX_IFLG_ON                           = 0x00000002
} _NAV_CIVX_INTL_FALG_T;

typedef struct __NAV_CIVX_T
{
    HANDLE_T            h_hide_timer;
    HANDLE_T            h_frame;
    HANDLE_T            h_msg;
#ifdef APP_IMG_UI       
    HANDLE_T            h_title_icon;
    WGL_HIMG_TPL_T      h_img_bk;
    WGL_HIMG_TPL_T      h_title_img;
#endif

    HANDLE_T                h_caption_icon;         /*from state manager, cannot be destroyed*/
    UINT32                  ui4_timeout;
    _NAV_CIVX_INTL_FALG_T   e_intl_flag;
} _NAV_CIVX_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static WGL_FONT_INFO_T   t_font_info    = {FE_FNT_SIZE_SMALL,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
static GL_COLOR_T        t_g_text_color = CC_INFO_FG_COLOR;
static UTF16_T           w2s_g_space[]  = {0x0020, 0};
static UTF16_T*          pw2s_g_cc      = NULL;
static UTF16_T*          pw2s_g_text    = NULL;
static UTF16_T*          pw2s_g_service = NULL;
static UTF16_T*          pw2s_g_title   = NULL;
static UTF16_T*          pw2s_g_off     = NULL;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*view handler*/
static INT32 _nav_civx_init(HANDLE_T                    h_canvas,
                            INT32                       i4_frame_x_offset,
                            INT32                       i4_frame_y_offset,
                            APP_COLOR_TYPE_T            e_color_type,
                            VOID**                      ppv_view);

static INT32 _nav_civx_deinit(VOID*                     pv_view);

static INT32 _nav_civx_data_change(VOID*                    pv_view,
                                   NAV_CI_UI_INFO_FIELD_T   e_update_field,
                                   const NAV_CI_UI_INFO_T*  pt_update_data);

static BOOL _nav_civx_is_key_handler(VOID*              pv_view,
                                     UINT32             ui4_key_code);

static INT32 _nav_civx_key_handler(VOID*                pv_view,
                                   UINT32               ui4_key_code);

static INT32 _nav_civx_hide(VOID*                       pv_view);

/**/
static VOID _nav_civx_load_msgs(UINT8                   ui1_lang_id);

static INT32 _nav_civx_show(_NAV_CIVX_T*                pt_this);

static INT32 _nav_civx_update_detail(_NAV_CIVX_T*                   pt_this,
                                     const NAV_CI_UI_CC_DETAIL_T*   pt_cc_detail);

static INT32 _nav_civx_update_dscrptr(_NAV_CIVX_T*                  pt_this,
                                      NAV_CI_UI_INFO_STATUS_T       e_dscrptr_status);

static INT32 _nav_civx_get_detail(NAV_CI_CC_TYPE_T      e_cc_type,
                                  UINT8                 ui1_cc_id,
                                  UTF16_T*              pw2s_string,
                                  SIZE_T                z_str_len);

static INT32 _nav_civx_get_off_detail(UTF16_T*          pw2s_string,
                                      SIZE_T            z_str_len);

static INT32 _nav_civx_frame_skin(_NAV_CIVX_T*          pt_this,
                                  APP_COLOR_TYPE_T      e_color_type);

static VOID _nav_civx_stop_timer(_NAV_CIVX_T*           pt_this);

static VOID _nav_civx_reset_timer(_NAV_CIVX_T*          pt_this);

static VOID _nav_civx_timer_nfy(HANDLE_T                h_timer,
                                VOID*                   pv_tag);

static VOID _nav_civx_handle_timeout(VOID*              pv_tag,
                                     VOID*              pv_tag2,
                                     VOID*              pv_tag3);

/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_civ_get_default_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_civ_get_default_handler(NAV_CI_VIEW_HANDLER_T*     pt_view_handler)
{
    NAV_ASSERT(pt_view_handler);

    pt_view_handler->pf_init = _nav_civx_init;
    pt_view_handler->pf_deinit = _nav_civx_deinit;
    pt_view_handler->pf_data_change = _nav_civx_data_change;
    pt_view_handler->pf_is_key_handler = _nav_civx_is_key_handler;
    pt_view_handler->pf_key_handler = _nav_civx_key_handler;
    pt_view_handler->pf_hide = _nav_civx_hide;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civx_init(
    HANDLE_T                h_canvas,
    INT32                   i4_frame_x_offset,
    INT32                   i4_frame_y_offset,
    APP_COLOR_TYPE_T        e_color_type,
    VOID**                  ppv_view)
{
    _NAV_CIVX_T*            pt_this;
    INT32                   i4_ret;
    GL_RECT_T               t_rect;

    /*new instance*/
    pt_this = c_mem_alloc(sizeof(_NAV_CIVX_T));
    if(NULL == pt_this)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to alloc memory, size = %d\r\n", sizeof(_NAV_CIVX_T)));
        return NAVR_OUT_OF_MEM;
    }
    c_memset(pt_this, 0, sizeof(_NAV_CIVX_T));

    do 
    {
        /*timer for auto-hide*/
        pt_this->ui4_timeout = NAV_CI_TIMER_DELAY;
        if (pt_this->ui4_timeout > 0) 
        {
            i4_ret = c_timer_create(&pt_this->h_hide_timer);
            if (OSR_OK != i4_ret) 
            {
                pt_this->h_hide_timer = NULL_HANDLE;
                DBG_ERROR((_ERROR_HEADER"Fail to create auto-hide timer. i4_ret = %d\r\n", i4_ret));
                i4_ret = NAVR_FAIL;
                break;
            }
        }
        
#ifdef APP_IMG_UI
        /*create background template image*/
        i4_ret = nav_img_create_cc_info_bk_img_tpl(&pt_this->h_img_bk);
        if(i4_ret != NAVR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to create template image for the background of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
            break;
        }

        i4_ret = nav_img_create_cc_info_icon_tpl(&pt_this->h_title_img);
        if(i4_ret != NAVR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to create template image for the background of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
            break;
        }
#endif

        /* create frame */
        SET_RECT_BY_SIZE(&t_rect,
                         i4_frame_x_offset + CC_INFO_FRAME_LEFT,
                         i4_frame_y_offset + CC_INFO_FRAME_TOP,
                         CC_INFO_FRAME_WIDTH,
                         CC_INFO_FRAME_HEIGHT);

        i4_ret = c_wgl_create_widget(h_canvas,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     CC_INFO_BK_ALPHA,
                                     FRAME_STYLE,
                                     NULL,
                                     &pt_this->h_frame);
        if(i4_ret != WGLR_OK) 
        {
            DBG_ERROR((_ERROR_HEADER"Fail to create the frame widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
            break;
        }

        /* create message */
        SET_RECT_BY_SIZE(&t_rect,
                         CC_INFO_MSG_LEFT,
                         CC_INFO_MSG_TOP,
                         CC_INFO_MSG_WIDTH,
                         CC_INFO_MSG_HEIGHT);
        
        i4_ret = c_wgl_create_widget(pt_this->h_frame,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     CC_INFO_FG_ALPHA,
                                     (VOID*)(WGL_STL_TEXT_MAX_32 | 
                                             WGL_STL_TEXT_SMART_CUT | 
                                             WGL_STL_GL_NO_IMG_UI | 
                                             WGL_STL_GL_NO_BK),
                                     NULL,
                                     &pt_this->h_msg);
        if(i4_ret != WGLR_OK) 
        {
            DBG_ERROR((_ERROR_HEADER"Fail to create the message widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
            break;
        }

#ifdef APP_IMG_UI
        /* create title icon */
        SET_RECT_BY_SIZE(&t_rect,
                         CC_INFO_ICON_LEFT,
                         CC_INFO_ICON_TOP,
                         CC_INFO_ICON_WIDTH,
                         CC_INFO_ICON_HEIGHT);

        i4_ret = c_wgl_create_widget(pt_this->h_frame,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     DEFAULT_BK_ALPHA,
                                     (VOID*)(WGL_STL_GL_NO_BK),
                                     NULL,
                                     &pt_this->h_title_icon);
        if(i4_ret != WGLR_OK) 
        {
            DBG_ERROR((_ERROR_HEADER"Fail to create the title icon widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
            break;
        }
#endif

        i4_ret = _nav_civx_frame_skin(pt_this,
                                      e_color_type);
        if(i4_ret != NAVR_OK) 
        {
            DBG_ERROR((_ERROR_HEADER"Fail to create the title icon widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
            break;
        }

        i4_ret = c_wgl_show(pt_this->h_frame,
                            WGL_SW_HIDE);
        if(i4_ret != WGLR_OK) 
        {
            DBG_ERROR((_ERROR_HEADER"Fail to hide the frame widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
            break;
        }

        *ppv_view = pt_this;
        return NAVR_OK;

    } while(0);

    _nav_civx_deinit(pt_this);
    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civx_deinit(
    VOID*                     pv_view)
{
    _NAV_CIVX_T*              pt_this = (_NAV_CIVX_T*)pv_view;

    /*check parameter*/
    if(NULL == pv_view)
    {
        return NAVR_OK;
    }

    if(c_handle_valid(pt_this->h_hide_timer) == TRUE) 
    {
        c_timer_delete(pt_this->h_hide_timer);
        pt_this->h_hide_timer = NULL_HANDLE;
    }
    pt_this->h_hide_timer = NULL_HANDLE;
    
    /*free widget*/
    if(NULL_HANDLE != pt_this->h_msg)
    {
        c_wgl_destroy_widget(pt_this->h_msg);
        pt_this->h_msg = NULL_HANDLE;
    }
    
    if(NULL_HANDLE != pt_this->h_frame)
    {
        c_wgl_destroy_widget(pt_this->h_frame);
        pt_this->h_frame = NULL_HANDLE;
    }

#ifdef APP_IMG_UI

    if(NULL_HANDLE != pt_this->h_title_icon)
    {
        c_wgl_destroy_widget(pt_this->h_title_icon);
        pt_this->h_title_icon = NULL_HANDLE;
    }
    
    if(NULL_HANDLE != pt_this->h_img_bk)
    {
        c_wgl_img_tpl_destroy(pt_this->h_img_bk);
        pt_this->h_img_bk = NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_title_img)
    {
        c_wgl_img_tpl_destroy(pt_this->h_title_img);
        pt_this->h_title_img = NULL_HANDLE;
    }
    
#endif
    
    c_mem_free(pt_this);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_data_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civx_data_change(
    VOID*                          pv_view,
    NAV_CI_UI_INFO_FIELD_T         e_update_field,
    const NAV_CI_UI_INFO_T*        pt_update_data)
{
    _NAV_CIVX_T*                   pt_this = (_NAV_CIVX_T*)pv_view;

    if(NULL == pv_view) /*before init*/
    {
        return NAVR_OK;
    }
    NAV_ASSERT(pt_update_data);

    if(NAV_CI_IF_GUI_LANG & e_update_field)
    {
        _nav_civx_load_msgs(pt_update_data->ui1_gui_lang_id);
    }

    if(NAV_CI_IF_DSCRPTR & e_update_field)
    {
        _nav_civx_update_dscrptr(pt_this, pt_update_data->e_dscrptr_status);
    }

    if(NAV_CI_IF_DETAIL & e_update_field)
    {
        _nav_civx_update_detail(pt_this, &pt_update_data->t_cc_detail);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_civx_is_key_handler(
    VOID*                            pv_view,
    UINT32                           ui4_key_code)
{
    return ((BTN_CC == ui4_key_code) ? TRUE : FALSE);    
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civx_key_handler(
    VOID*                          pv_view,
    UINT32                         ui4_key_code)
{
    _NAV_CIVX_T*                   pt_this = (_NAV_CIVX_T*)pv_view;
    INT32                          i4_ret;
    
    /*show cc info first if it's invisible*/
    if(FALSE == nav_is_component_visible(NAV_COMP_ID_CC_SEL))
    {
        _nav_civx_show(pt_this);
        return NAVR_NO_ACTION;      /*not to be the key owner*/
    }
    
    /*play next cc*/
    i4_ret = nav_ci_switch_cc(NAV_CI_SM_NEXT);
    if(i4_ret != NAVR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"nav_ci_switch_cc() failed. i4_ret = %d\r\n", i4_ret));
        return i4_ret;
    }

    _nav_civx_reset_timer(pt_this);
    return NAVR_NO_ACTION;          /*not to be the key owner*/
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civx_hide(
    VOID*                   pv_view)
{
    _NAV_CIVX_T*            pt_this = (_NAV_CIVX_T*)pv_view;
    INT32                   i4_ret;

    NAV_ASSERT(pt_this);

    if(0 == (_NAV_CIVX_IFLG_ON & pt_this->e_intl_flag))
    {
        return NAVR_OK;
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_frame, WGL_SW_HIDE);
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"Fail to change the visibility to HIDE of the frame widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    
    pt_this->e_intl_flag &= ~(_NAV_CIVX_IFLG_ON);

    i4_ret = c_wgl_repaint(pt_this->h_frame,
                           NULL,
                           IS_SYNC_REPAINT);
    if(i4_ret != WGLR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to raise a repaint of the frame widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    _nav_civx_stop_timer(pt_this);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_load_msgs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_civx_load_msgs(
    UINT8                       ui1_lang_id)
{
    pw2s_g_cc       = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_NTSC_CC);
    pw2s_g_text     = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_NTSC_TEXT);
    pw2s_g_service  = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_DTVCC_SERVICE);
    pw2s_g_title    = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_TITLE);
    pw2s_g_off      = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_OFF);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civx_show(
    _NAV_CIVX_T*            pt_this)
{
    INT32                   i4_ret;

    i4_ret = c_wgl_set_visibility(pt_this->h_frame, WGL_SW_RECURSIVE);
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"Fail to change the visibility to SW_RECURSIVE of the frame widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_this->h_frame,
                           NULL,
                           IS_SYNC_REPAINT);
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"Fail to raise a repaint for the frame widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    
    nav_set_component_visible(NAV_COMP_ID_CC_SEL);
    pt_this->e_intl_flag |= _NAV_CIVX_IFLG_ON;
    
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_update_detail
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civx_update_detail(
    _NAV_CIVX_T*                     pt_this,
    const NAV_CI_UI_CC_DETAIL_T*     pt_cc_detail)
{
    UTF16_T                          w2s_string[NAV_CIVX_CC_DETAIL_STR_LEN + 1] = {0};
    UTF16_T                          w2s_unknown_lang[ISO_639_LANG_LEN] = {0};
    UTF16_T*                         pw2s_cc_lang;
    SIZE_T                           z_len;
    INT32                            i4_ret;

    do 
    {
        if(NAV_CI_UI_IS_NOT_READY == pt_cc_detail->e_status)
        {
            break;
        }

        if(NAV_CI_UI_IS_WITHOUT == pt_cc_detail->e_status)
        {
            i4_ret = _nav_civx_get_off_detail(w2s_string,
                                              NAV_CIVX_CC_DETAIL_STR_LEN + 1);
            if(NAVR_OK != i4_ret)
            {
                return i4_ret;
            }

            break;
        }

        /*update description*/
        i4_ret = _nav_civx_get_detail(pt_cc_detail->e_cc_type,
                                      pt_cc_detail->ui1_cc_id,
                                      w2s_string,
                                      NAV_CIVX_CC_DETAIL_STR_LEN + 1);
        if(NAVR_OK != i4_ret)
        {
            return i4_ret;
        }

        /*update language*/
        if((NAV_CI_UI_IS_NOT_READY == pt_cc_detail->e_lang_status) ||
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
            z_len = c_uc_w2s_strlen(w2s_string);    /*z_len is less than or equal to NAV_CIVX_CC_DETAIL_STR_LEN*/
            c_uc_w2s_strncat(w2s_string, w2s_g_space, NAV_CIVX_CC_DETAIL_STR_LEN - z_len);

            /*append language*/
            z_len = c_uc_w2s_strlen(w2s_string);    /*z_len is less than or equal to NAV_CIVX_CC_DETAIL_STR_LEN*/
            c_uc_w2s_strncat(w2s_string, pw2s_cc_lang, NAV_CIVX_CC_DETAIL_STR_LEN - z_len);
        }
        
    } while(0);

    /*update cc detail widget*/
    i4_ret = c_wgl_do_cmd(pt_this->h_msg,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)w2s_string,
                          (VOID*)NAV_CIVX_CC_DETAIL_STR_LEN);
    if(i4_ret != WGLR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to set the cc detail to detail widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    /*repaint detail widget if visible*/
    if(nav_is_component_visible(NAV_COMP_ID_CC_SEL))
    {
        i4_ret = c_wgl_repaint(pt_this->h_msg,
                               NULL,
                               IS_SYNC_REPAINT);
        if(i4_ret != WGLR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to raise a repaint for the msg widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
            return NAVR_FAIL;
        }
    }
    
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_update_dscrptr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civx_update_dscrptr(
    _NAV_CIVX_T*                      pt_this,
    NAV_CI_UI_INFO_STATUS_T           e_dscrptr_status)
{
    BNR_ITEM_SET_T                          t_orig_visible;
    INT32                             i4_ret;
    UINT8                             ui1_type;
    BOOL                              b_show_icon;

    if((NAV_CI_UI_IS_NOT_READY == e_dscrptr_status) ||
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
    if(!(_NAV_CIVX_IFLG_CAPTION_ICON_INIT_READY & pt_this->e_intl_flag))
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
        pt_this->e_intl_flag |= _NAV_CIVX_IFLG_CAPTION_ICON_INIT_READY;
    }
    
    if(NULL_HANDLE != pt_this->h_caption_icon)
    {
        /*show/hide cc icon*/
        i4_ret = c_wgl_set_visibility(pt_this->h_caption_icon, 
                                      (b_show_icon) ? WGL_SW_NORMAL : WGL_SW_HIDE);
        if(i4_ret != WGLR_OK) 
        {
            DBG_ERROR((_ERROR_HEADER"Fail to change the visibility of the caption-icon widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
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
 *      _nav_civx_frame_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civx_frame_skin(
    _NAV_CIVX_T*                  pt_this,
    APP_COLOR_TYPE_T              e_color_type)
{
    WGL_COLOR_INFO_T              t_clr_info;
    INT32                         i4_ret;
    UINT8                         ui1_type;

    /*get Caption-Icon*/
    if(!(_NAV_CIVX_IFLG_CAPTION_ICON_INIT_READY & pt_this->e_intl_flag))
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
        pt_this->e_intl_flag |= _NAV_CIVX_IFLG_CAPTION_ICON_INIT_READY;
    }    

#ifdef APP_IMG_UI
    WGL_IMG_INFO_T                t_img_info;

    /* set title icon image buffer*/
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_this->h_title_img;
    t_img_info.u_img_data.t_standard.t_disable   = pt_this->h_title_img;
    t_img_info.u_img_data.t_standard.t_highlight = pt_this->h_title_img;

    i4_ret = c_wgl_do_cmd(pt_this->h_title_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"Fail to set template image to title-icon widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    /* set title icon alignment */
    i4_ret = c_wgl_do_cmd(pt_this->h_title_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"Fail to set alignment to title-icon widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    /* frame background image */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_this->h_img_bk;
    t_img_info.u_img_data.t_standard.t_highlight = pt_this->h_img_bk;
    t_img_info.u_img_data.t_standard.t_disable   = pt_this->h_img_bk;
    i4_ret = c_wgl_do_cmd(pt_this->h_frame,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"Fail to set bk image to frame widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
#else
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = APP_COLOR(e_color_type, APP_COLOR_ITEM_MAIN);
    t_clr_info.u_color_data.t_standard.t_enable      = APP_COLOR(e_color_type, APP_COLOR_ITEM_MAIN);
    t_clr_info.u_color_data.t_standard.t_highlight   = APP_COLOR(e_color_type, APP_COLOR_ITEM_MAIN);
    t_clr_info.u_color_data.t_standard.t_disable.a   = DEFAULT_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = DEFAULT_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = DEFAULT_BK_ALPHA;

    i4_ret = c_wgl_do_cmd(pt_this->h_frame,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_BK,
                          &t_clr_info);
    if(i4_ret != WGLR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to set bk color to frame widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
#endif
    
    /* set message color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_text_color;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_text_color;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_text_color;

    i4_ret = c_wgl_do_cmd(pt_this->h_msg,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_TEXT,
                          &t_clr_info);
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"Fail to set text color to msg widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    /* set title font */
    i4_ret = c_wgl_do_cmd(pt_this->h_msg,
                          WGL_CMD_GL_SET_FONT,
                          (VOID*)&t_font_info,
                          NULL);
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"Fail to set FONT to msg widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    /* set title align*/
    i4_ret = c_wgl_do_cmd(pt_this->h_msg,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_LEFT_CENTER,
                          NULL);
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"Fail to set alignment to msg widget of CC-Info-Box. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_get_detail
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
 static INT32 _nav_civx_get_detail(
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

    default:
        NAV_ASSERT(0);
        return NAVR_FAIL;
    }
        
    /*convert cc_id to string*/
    c_sprintf(s_cc_id, "%d", ui1_cc_id);
    i4_ret = c_uc_ps_to_w2s(s_cc_id, w2s_cc_id, 3);
    if (UCR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to convert cc-id to string. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    if(z_str_len >= (c_uc_w2s_strlen(pw2s_g_title) + c_uc_w2s_strlen(pw2s_cc_string) + 3 + 1)) /* 3: cc_id length, 1: null-terminated character*/
    {
        c_uc_w2s_strcat(pw2s_string, pw2s_g_title);
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
 *      _nav_civx_get_off_detail
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
 static INT32 _nav_civx_get_off_detail(
     UTF16_T*                          pw2s_string,
     SIZE_T                            z_str_len)
 {
    if(z_str_len >= (c_uc_w2s_strlen(pw2s_g_title) + c_uc_w2s_strlen(pw2s_g_off) + 1)) /* 1: null-terminated character*/
    {
        c_uc_w2s_strcat(pw2s_string, pw2s_g_title);
        c_uc_w2s_strcat(pw2s_string, pw2s_g_off);
    }
    else
    {
        DBG_ERROR((_ERROR_HEADER"Buffer size for cc off is too small.\r\n"));
        NAV_ASSERT(0);
    }

    return NAVR_OK;
 }

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_civx_stop_timer(
    _NAV_CIVX_T*                 pt_this)
{
    INT32 i4_ret;

    if(c_handle_valid(pt_this->h_hide_timer)) 
    {
        i4_ret = c_timer_stop(pt_this->h_hide_timer);
        if(i4_ret != OSR_OK) 
        {
            ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop cc_info::h_hide_timer failed!"));
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_civx_reset_timer(
    _NAV_CIVX_T*                  pt_this)
{
    INT32 i4_ret;

    _nav_civx_stop_timer(pt_this);

    i4_ret = c_timer_start(pt_this->h_hide_timer,
                           pt_this->ui4_timeout,
                           X_TIMER_FLAG_ONCE,
                           _nav_civx_timer_nfy,
                           pt_this);
    if(i4_ret != OSR_OK) 
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start cc_info::h_hide_timer failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_civx_timer_nfy(
    HANDLE_T                    h_timer,
    VOID*                       pv_tag)
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_civx_handle_timeout, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civx_handle_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_civx_handle_timeout(
    VOID*                            pv_tag,
    VOID*                            pv_tag2,
    VOID*                            pv_tag3)
{
    nav_hide_component(NAV_COMP_ID_CC_SEL);
}

#if 0
/*----------------------------------------------------------------------------
 * Name: _cc_info_view_frame_proc_fct
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _cc_info_view_frame_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    VOID*      pv_tag  = NULL;
    CC_INFO_T* pt_this
    INT32      i4_ret;

    i4_ret = c_handle_get_tag(h_widget, &pv_tag);
    if (i4_ret == HR_OK && pv_tag != NULL) {
        pt_this = (CC_INFO_T*)pv_tag;

        switch(ui4_msg){
        case WGL_MSG_NOTIFY:
        {
            HANDLE_T           h_child_widget = (HANDLE_T) pv_param1;
            WGL_NOTIFY_DATA_T* pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

            if (h_child_widget != pt_this->t_view->h_msg) {
                break;
            }
            switch(pt_wgl_nfy_data->ui4_nc_code) {
            case WGL_NC_GL_KEY_DOWN:
                cc_info_do_rcu_key_down(
                            pt_this,
                            pt_wgl_nfy_data->u.t_key.ui4_key_code
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
#endif /*#if 0*/

#endif /*!defined(APP_DVBT_SUPPORT) || defined(APP_SEPARATED_CC_INFO)*/

