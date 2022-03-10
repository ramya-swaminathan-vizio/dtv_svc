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
 * $RCSfile: cc_info_view_onoff_box.c,v $
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
#if !(defined(APP_DVBT_SUPPORT) || defined(APP_ISDB_SUPPORT)) && defined(APP_NAV_CI_ONOFF)

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
#include "res/nav/cc_info/cc_info_view_onoff_box_rc.h"

/*banner state mgr*/
#include "nav/nav_bnr_state_mgr.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         TRUE
#define NAV_CIVOX_CC_DETAIL_STR_LEN             ((SIZE_T)64)

typedef enum __NAV_CIVOX_FLAG_T
{
    _NAV_CIVOX_FLAG_CAP_ICN_READY   = 0x00000001,
    _NAV_CIVOX_FLAG_ON              = 0x00000002
} _NAV_CIVOX_FLAG_T;

typedef struct __NAV_CIVOX_T
{
    HANDLE_T            h_hide_timer;
    HANDLE_T            h_frame;
    HANDLE_T            h_msg;
    HANDLE_T            h_caption_icon;                 /*read only*/
    WGL_HIMG_TPL_T      h_img_bk;
    _NAV_CIVOX_FLAG_T   e_flag;
    UINT8               ui1_lang_id;
} _NAV_CIVOX_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*view handler*/
static INT32 _nav_civox_init(HANDLE_T                   h_canvas,
                             INT32                      i4_frame_x_offset,
                             INT32                      i4_frame_y_offset,
                             APP_COLOR_TYPE_T           e_color_type,
                             VOID**                     ppv_view);

static INT32 _nav_civox_deinit(VOID*                    pv_view);

static INT32 _nav_civox_data_change(VOID*                   pv_view,
                                    NAV_CI_UI_INFO_FIELD_T  e_update_field,
                                    const NAV_CI_UI_INFO_T* pt_update_data);

static BOOL _nav_civox_is_key_handler(VOID*             pv_view,
                                      UINT32            ui4_key_code);

static INT32 _nav_civox_key_handler(VOID*               pv_view,
                                    UINT32              ui4_key_code);

static INT32 _nav_civox_hide(VOID*                      pv_view);

/**/
static INT32 _nav_civox_rc_init(_NAV_CIVOX_T*           pt_this,
                                HANDLE_T                h_parent,
                                INT32                   i4_frame_x_offset,
                                INT32                   i4_frame_y_offset,
                                APP_COLOR_TYPE_T        e_color_type);

static VOID _nav_civox_rc_deinit(_NAV_CIVOX_T*          pt_this);

static INT32 _nav_civox_show(_NAV_CIVOX_T*              pt_this);

static INT32 _nav_civox_update_detail(_NAV_CIVOX_T*                  pt_this,
                                      const NAV_CI_UI_CC_DETAIL_T*  pt_cc_detail);

static INT32 _nav_civox_update_dscrptr(_NAV_CIVOX_T*            pt_this,
                                       NAV_CI_UI_INFO_STATUS_T  e_dscrptr_status);

static INT32 _nav_civox_update_cc_status(_NAV_CIVOX_T*      pt_this,
                                         NAV_CI_EXEC_COND_T e_cond);

static INT32 _nav_civox_get_detail(_NAV_CIVOX_T*        pt_this,
                                   NAV_CI_CC_TYPE_T     e_cc_type,
                                   UINT8                ui1_cc_id,
                                   UTF16_T*             pw2s_string,
                                   SIZE_T               z_str_len);

static INT32 _nav_civox_get_off_detail(_NAV_CIVOX_T*    pt_this,
                                       UTF16_T*         pw2s_string,
                                       SIZE_T           z_str_len);

static INT32 _nav_civox_frame_skin(_NAV_CIVOX_T*        pt_this,
                                   APP_COLOR_TYPE_T     e_color_type);

static VOID _nav_civox_stop_timer(_NAV_CIVOX_T*         pt_this);

static VOID _nav_civox_reset_timer(_NAV_CIVOX_T*        pt_this);

static VOID _nav_civox_timer_nfy(HANDLE_T               h_timer,
                                 VOID*                  pv_tag);

static VOID _nav_civox_handle_timeout(VOID*             pv_tag,
                                      VOID*             pv_tag2,
                                      VOID*             pv_tag3);

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

    pt_view_handler->pf_init = _nav_civox_init;
    pt_view_handler->pf_deinit = _nav_civox_deinit;
    pt_view_handler->pf_data_change = _nav_civox_data_change;
    pt_view_handler->pf_is_key_handler = _nav_civox_is_key_handler;
    pt_view_handler->pf_key_handler = _nav_civox_key_handler;
    pt_view_handler->pf_hide = _nav_civox_hide;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_init(
    HANDLE_T                 h_canvas,
    INT32                    i4_frame_x_offset,
    INT32                    i4_frame_y_offset,
    APP_COLOR_TYPE_T         e_color_type,
    VOID**                   ppv_view)
{
    _NAV_CIVOX_T*            pt_this;
    INT32                    i4_ret;

    /*new instance*/
    pt_this = c_mem_alloc(sizeof(_NAV_CIVOX_T));
    if(NULL == pt_this)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to alloc memory, size = %d\r\n", sizeof(_NAV_CIVOX_T)));
        return NAVR_OUT_OF_MEM;
    }
    c_memset(pt_this, 0, sizeof(_NAV_CIVOX_T));
    pt_this->ui1_lang_id = 0;

    do 
    {
        /*timer for auto-hide*/
        i4_ret = c_timer_create(&pt_this->h_hide_timer);
        if(OSR_OK != i4_ret) 
        {
            pt_this->h_hide_timer = NULL_HANDLE;
            DBG_ERROR((_ERROR_HEADER"c_timer_create() failed. i4_ret = %d\r\n", i4_ret));
            break;
        }
        
        i4_ret = _nav_civox_rc_init(pt_this, h_canvas, i4_frame_x_offset, i4_frame_y_offset, e_color_type);
        if(NAVR_OK != i4_ret)
        {
            break;
        }

        i4_ret = _nav_civox_frame_skin(pt_this, e_color_type);
        if(NAVR_OK != i4_ret)
        {
            break;
        }
        
        *ppv_view = pt_this;
        return NAVR_OK;

    } while(0);

    _nav_civox_deinit(pt_this);
    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_deinit(
    VOID*                      pv_view)
{
    _NAV_CIVOX_T*              pt_this = (_NAV_CIVOX_T*)pv_view;

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
    
    _nav_civox_rc_deinit(pt_this);
    
    c_mem_free(pt_this);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_data_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_data_change(
    VOID*                           pv_view,
    NAV_CI_UI_INFO_FIELD_T          e_update_field,
    const NAV_CI_UI_INFO_T*         pt_update_data)
{
    _NAV_CIVOX_T*                   pt_this = (_NAV_CIVOX_T*)pv_view;

    if(NULL == pv_view) /*before init*/
    {
        return NAVR_OK;
    }
    NAV_ASSERT(pt_update_data);

    if(NAV_CI_IF_GUI_LANG & e_update_field)
    {
        pt_this->ui1_lang_id = pt_update_data->ui1_gui_lang_id;
    }
    
    if(NAV_CI_IF_DETAIL & e_update_field)
    {
        _nav_civox_update_detail(pt_this, &pt_update_data->t_cc_detail);
    }

    if(NAV_CI_IF_DSCRPTR & e_update_field)
    {
        _nav_civox_update_dscrptr(pt_this, pt_update_data->e_dscrptr_status);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_civox_is_key_handler(
    VOID*                             pv_view,
    UINT32                            ui4_key_code)
{
    return ((BTN_CC == ui4_key_code) ? TRUE : FALSE);    
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_key_handler(
    VOID*                           pv_view,
    UINT32                          ui4_key_code)
{
    _NAV_CIVOX_T*                   pt_this = (_NAV_CIVOX_T*)pv_view;
    NAV_CI_EXEC_COND_T              e_cond;
    INT32                           i4_ret;
    
    /*get current status*/
    i4_ret = nav_ci_get_exec_cond(&e_cond);
    if(i4_ret != NAVR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"nav_ci_get_exec_cond() failed. i4_ret = %d\r\n", i4_ret));
        return i4_ret;
    }
    
    /*show cc info first if it's invisible*/
    if(FALSE == nav_is_component_visible(NAV_COMP_ID_CC_SEL))
    {
        /*update current status*/
        _nav_civox_update_cc_status(pt_this, e_cond);
        
        _nav_civox_show(pt_this);
    }
    else
    {
        /*turn on/off cc*/
        e_cond = (NAV_CI_EC_ON == e_cond) ? NAV_CI_EC_OFF : NAV_CI_EC_ON;
        i4_ret = nav_ci_set_exec_cond(e_cond);
        if(i4_ret != NAVR_OK) 
        {
            DBG_ERROR((_ERROR_HEADER"nav_ci_set_exec_cond() failed. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }
        
        /*update message*/
        _nav_civox_update_cc_status(pt_this, e_cond);
    }

    _nav_civox_reset_timer(pt_this);
    return NAVR_NO_ACTION;          /*not to be the key owner*/
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_hide(
    VOID*                    pv_view)
{
    _NAV_CIVOX_T*            pt_this = (_NAV_CIVOX_T*)pv_view;
    INT32                    i4_ret;

    NAV_ASSERT(pt_this);

    if(0 == (_NAV_CIVOX_FLAG_ON & pt_this->e_flag))
    {
        return NAVR_OK;
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_frame, WGL_SW_HIDE);
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_set_visibility() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
    
    pt_this->e_flag &= ~(_NAV_CIVOX_FLAG_ON);

    i4_ret = c_wgl_repaint(pt_this->h_frame, NULL, IS_SYNC_REPAINT);
    if(i4_ret != WGLR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_repaint() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    _nav_civox_stop_timer(pt_this);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_rc_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_rc_init(
    _NAV_CIVOX_T*               pt_this,
    HANDLE_T                    h_parent,
    INT32                       i4_frame_x_offset,
    INT32                       i4_frame_y_offset,
    APP_COLOR_TYPE_T            e_color_type)
{
    GL_RECT_T                   t_rect;
    INT32                       i4_ret;
    
    /*create background template image*/
#ifdef NAV_CI_VOX_BK_IMG
    i4_ret = c_wgl_img_tpl_create(NAV_CI_VOX_BK_IMG_STYLE, &NAV_CI_VOX_BK_IMG, &pt_this->h_img_bk);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"c_wgl_img_tpl_create(NAV_CI_VOX_BK_IMG_STYLE) failed. i4_ret = %d\r\n", i4_ret));
        pt_this->h_img_bk = NULL_HANDLE;
        return NAVR_FAIL;
    }
#else
    pt_this->h_img_bk = NULL_HANDLE;
#endif    

    do 
    {
        /*create frame*/
        SET_RECT_BY_SIZE(&t_rect,
                         NAV_CI_VOX_FM_LEFT + i4_frame_x_offset,
                         NAV_CI_VOX_FM_TOP + i4_frame_y_offset,
                         NAV_CI_VOX_FM_WIDTH,
                         NAV_CI_VOX_FM_HEIGHT);

        i4_ret = c_wgl_create_widget(h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     NAV_CI_VOX_FM_ALPHA,
                                     (VOID*)NAV_CI_VOX_FM_STYLE,
                                     NULL,
                                     &pt_this->h_frame);
        if(WGLR_OK != i4_ret) 
        {
            DBG_ERROR((_ERROR_HEADER"c_wgl_create_widget(HT_WGL_WIDGET_FRAME) failed. i4_ret = %d\r\n", i4_ret));
            break;
        }

        /*create message*/
        SET_RECT_BY_SIZE(&t_rect,
                         NAV_CI_VOX_MSG_LEFT,
                         NAV_CI_VOX_MSG_TOP,
                         NAV_CI_VOX_MSG_WIDTH,
                         NAV_CI_VOX_MSG_HEIGHT);
        
        i4_ret = c_wgl_create_widget(pt_this->h_frame,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     NAV_CI_VOX_MSG_ALPHA,
                                     (VOID*)(NAV_CI_VOX_MSG_STYLE),
                                     NULL,
                                     &pt_this->h_msg);
        if(i4_ret != WGLR_OK) 
        {
            DBG_ERROR((_ERROR_HEADER"c_wgl_create_widget(HT_WGL_WIDGET_TEXT) failed. i4_ret = %d\r\n", i4_ret));
            break;
        }
        
        return NAVR_OK;
        
    } while(0);
    
    _nav_civox_rc_deinit(pt_this);
    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_rc_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_civox_rc_deinit(
    _NAV_CIVOX_T*                pt_this)
{
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
    
    if(NULL_HANDLE != pt_this->h_img_bk)
    {
        c_wgl_img_tpl_destroy(pt_this->h_img_bk);
        pt_this->h_img_bk = NULL_HANDLE;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_show(
    _NAV_CIVOX_T*            pt_this)
{
    INT32                    i4_ret;

    i4_ret = c_wgl_set_visibility(pt_this->h_frame, WGL_SW_RECURSIVE);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s() c_wgl_set_visibility() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_this->h_frame, NULL, IS_SYNC_REPAINT);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s() c_wgl_repaint() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
    
    nav_set_component_visible(NAV_COMP_ID_CC_SEL);
    pt_this->e_flag |= _NAV_CIVOX_FLAG_ON;
    
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_update_detail
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_update_detail(
    _NAV_CIVOX_T*                    pt_this,
    const NAV_CI_UI_CC_DETAIL_T*     pt_cc_detail)
{
    UTF16_T                          w2s_string[NAV_CIVOX_CC_DETAIL_STR_LEN + 1] = {0};
    UTF16_T                          w2s_unknown_lang[ISO_639_LANG_LEN] = {0};
    UTF16_T                          w2s_space[]  = {0x0020, 0};
    HANDLE_T                         h_caption_msg;
    UTF16_T*                         pw2s_cc_lang;
    SIZE_T                           z_len;
    INT32                            i4_ret;
    BNR_ITEM_SET_T                         t_orig_visible;
    UINT8                            ui1_type;

    /*caption handle*/        
    i4_ret = nav_bnr_state_get_item_widget(NAV_BNR_STATE_II_CAPTION,
                                           &h_caption_msg,
                                           &ui1_type);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): nav_bnr_state_get_item_widget(NAV_BNR_STATE_II_CAPTION) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return i4_ret;
    }
    
    if(h_caption_msg)
    {
        do 
        {
            if(NAV_CI_UI_IS_NOT_READY == pt_cc_detail->e_status || NAV_CI_UI_IS_INIT_VALUE == pt_cc_detail->e_status)
            {
                break;
            }
    
            if(NAV_CI_UI_IS_WITHOUT == pt_cc_detail->e_status)
            {
                i4_ret = _nav_civox_get_off_detail(pt_this,
                                                   w2s_string,
                                                   NAV_CIVOX_CC_DETAIL_STR_LEN + 1);
                if(NAVR_OK != i4_ret)
                {
                    return i4_ret;
                }
    
                break;
            }
    
            /*update description*/
            i4_ret = _nav_civox_get_detail(pt_this,
                                           pt_cc_detail->e_cc_type,
                                           pt_cc_detail->ui1_cc_id,
                                           w2s_string,
                                           NAV_CIVOX_CC_DETAIL_STR_LEN + 1);
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
                z_len = c_uc_w2s_strlen(w2s_string);    /*z_len is less than or equal to NAV_CIVOX_CC_DETAIL_STR_LEN*/
                c_uc_w2s_strncat(w2s_string, w2s_space, NAV_CIVOX_CC_DETAIL_STR_LEN - z_len);
    
                /*append language*/
                z_len = c_uc_w2s_strlen(w2s_string);    /*z_len is less than or equal to NAV_CIVOX_CC_DETAIL_STR_LEN*/
                c_uc_w2s_strncat(w2s_string, pw2s_cc_lang, NAV_CIVOX_CC_DETAIL_STR_LEN - z_len);
            }
            
        } while(0);
        
        /*get Caption current status*/
        i4_ret = nav_bnr_state_is_items_visible(NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION),
                                                &t_orig_visible);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): nav_bnr_state_is_items_visible(NAV_BNR_STATE_II_CAPTION) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
            return i4_ret;
        }
        
        /*update cc detail widget*/
        i4_ret = c_wgl_do_cmd(h_caption_msg,
                              WGL_CMD_TEXT_SET_TEXT,
                              (VOID*)w2s_string,
                              (VOID*)NAV_CIVOX_CC_DETAIL_STR_LEN);
        if(i4_ret != WGLR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_do_cmd(WGL_CMD_TEXT_SET_TEXT) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
            return NAVR_FAIL;
        }

        /*repaint detail widget if visible*/
        if(t_orig_visible)
        {
            i4_ret = c_wgl_repaint(h_caption_msg,
                                   NULL,
                                   IS_SYNC_REPAINT);
            if(i4_ret != WGLR_OK)
            {
                DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_repaint() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }
        }
    }
    
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_update_dscrptr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_update_dscrptr(
    _NAV_CIVOX_T*                      pt_this,
    NAV_CI_UI_INFO_STATUS_T            e_dscrptr_status)
{
    BNR_ITEM_SET_T                           t_orig_visible;
    INT32                              i4_ret;
    UINT8                              ui1_type;
    BOOL                               b_show_icon;

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
    if(!(_NAV_CIVOX_FLAG_CAP_ICN_READY & pt_this->e_flag))
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
        pt_this->e_flag |= _NAV_CIVOX_FLAG_CAP_ICN_READY;
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
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_update_cc_status
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_update_cc_status(
    _NAV_CIVOX_T*                        pt_this,
    NAV_CI_EXEC_COND_T                   e_cond)
{
    INT32                                i4_ret;
    UTF16_T*                             pw2s_msg;
    
    /*set title*/
    i4_ret = c_wgl_do_cmd(pt_this->h_msg,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)MLM_NAV_TEXT(pt_this->ui1_lang_id, MLM_NAV_KEY_CC_TITLE),
                          (VOID*)0xFFFF);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_do_cmd(WGL_CMD_TEXT_SET_TEXT) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
    
    /*set message*/
    pw2s_msg = (NAV_CI_EC_OFF == e_cond) ? MLM_NAV_TEXT(pt_this->ui1_lang_id, MLM_NAV_KEY_CC_TITLE_OFF) : 
                                           MLM_NAV_TEXT(pt_this->ui1_lang_id, MLM_NAV_KEY_CC_TITLE_ON);
                                           
    i4_ret = c_wgl_do_cmd(pt_this->h_msg,
                          WGL_CMD_TEXT_APPEND_TEXT,
                          (VOID*)pw2s_msg,
                          (VOID*)0xFFFF);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_do_cmd(WGL_CMD_TEXT_APPEND_TEXT) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /*repaint detail widget if visible*/
    if(0 != (_NAV_CIVOX_FLAG_ON & pt_this->e_flag))
    {
        i4_ret = c_wgl_repaint(pt_this->h_msg, NULL, IS_SYNC_REPAINT);
        if(WGLR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_repaint() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
            return NAVR_FAIL;
        }
    }
    
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_get_detail
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_get_detail(
    _NAV_CIVOX_T*                  pt_this,
    NAV_CI_CC_TYPE_T               e_cc_type,
    UINT8                          ui1_cc_id,
    UTF16_T*                       pw2s_string,
    SIZE_T                         z_str_len)
{
    UTF16_T* pw2s_cc_string = NULL;
    CHAR     s_cc_id[4]     = {0};
    UTF16_T  w2s_cc_id[4]   = {0};
    INT32    i4_ret;

    switch(e_cc_type) 
    {
    case NAV_CI_CC_TYPE_NTSC_CC:
        pw2s_cc_string = MLM_NAV_TEXT(pt_this->ui1_lang_id, MLM_NAV_KEY_CC_NTSC_CC);
        break;

    case NAV_CI_CC_TYPE_NTSC_TEXT:
        pw2s_cc_string = MLM_NAV_TEXT(pt_this->ui1_lang_id, MLM_NAV_KEY_CC_NTSC_TEXT);
        break;

    case NAV_CI_CC_TYPE_DIG:
        pw2s_cc_string = MLM_NAV_TEXT(pt_this->ui1_lang_id, MLM_NAV_KEY_CC_DTVCC_SERVICE);
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
 *      _nav_civox_get_off_detail
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_get_off_detail(
    _NAV_CIVOX_T*                      pt_this,
    UTF16_T*                           pw2s_string,
    SIZE_T                             z_str_len)
{
    UTF16_T*                           pw2s_off = MLM_NAV_TEXT(pt_this->ui1_lang_id, MLM_NAV_KEY_CC_OFF);
    
    if(z_str_len >= (c_uc_w2s_strlen(pw2s_off) + 1)) /* 1: null-terminated character*/
    {
        c_uc_w2s_strcat(pw2s_string, pw2s_off);
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
 *      _nav_civox_frame_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civox_frame_skin(
    _NAV_CIVOX_T*                  pt_this,
    APP_COLOR_TYPE_T               e_color_type)
{
    WGL_FONT_INFO_T                t_font_info = NAV_CI_VOX_MSG_FONT;
    GL_COLOR_T                     t_text_color = NAV_CI_VOX_FG_COLOR;
    WGL_COLOR_INFO_T               t_clr_info;
    WGL_IMG_INFO_T                 t_img_info;
    INT32                          i4_ret;
    UINT8                          ui1_type;

    /*get Caption-Icon*/
    if(!(_NAV_CIVOX_FLAG_CAP_ICN_READY & pt_this->e_flag))
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
        pt_this->e_flag |= _NAV_CIVOX_FLAG_CAP_ICN_READY;
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
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_do_cmd(WGL_CMD_GL_SET_IMAGE) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
    
    /* set message color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable   = t_text_color;
    t_clr_info.u_color_data.t_standard.t_enable    = t_text_color;
    t_clr_info.u_color_data.t_standard.t_highlight = t_text_color;

    i4_ret = c_wgl_do_cmd(pt_this->h_msg,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_TEXT,
                          &t_clr_info);
    if(i4_ret != WGLR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_do_cmd(WGL_CMD_GL_SET_COLOR) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /*set message font*/
    i4_ret = c_wgl_do_cmd(pt_this->h_msg,
                          WGL_CMD_GL_SET_FONT,
                          (VOID*)&t_font_info,
                          NULL);
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_do_cmd(WGL_CMD_GL_SET_FONT) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* set message align*/
    i4_ret = c_wgl_do_cmd(pt_this->h_msg,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)NAV_CI_VOX_MSG_ALIGN,
                          NULL);
    if(i4_ret != WGLR_OK) 
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_do_cmd(WGL_CMD_TEXT_SET_ALIGN) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_civox_stop_timer(
    _NAV_CIVOX_T*                 pt_this)
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
 *      _nav_civox_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_civox_reset_timer(
    _NAV_CIVOX_T*                  pt_this)
{
    INT32 i4_ret;

    _nav_civox_stop_timer(pt_this);

    i4_ret = c_timer_start(pt_this->h_hide_timer,
                           NAV_CI_VOX_TIMEOUT,
                           X_TIMER_FLAG_ONCE,
                           _nav_civox_timer_nfy,
                           pt_this);
    if(i4_ret != OSR_OK) 
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start cc_info::h_hide_timer failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_civox_timer_nfy(
    HANDLE_T                    h_timer,
    VOID*                       pv_tag)
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_civox_handle_timeout, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civox_handle_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_civox_handle_timeout(
    VOID*                            pv_tag,
    VOID*                            pv_tag2,
    VOID*                            pv_tag3)
{
    nav_hide_component(NAV_COMP_ID_CC_SEL);
}

#endif /*!defined(APP_DVBT_SUPPORT) || defined(APP_SEPARATED_CC_INFO)*/

