/*----------------------------------------------------------------------------*
 * No Warranty                                                                *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MTK with respect to any MTK *
 * Deliverables or any use thereof, and MTK Deliverables are provided on an   *
 * "AS IS" basis.  MTK hereby expressly disclaims all such warranties,        *
 * including any implied warranties of merchantability, non-infringement and  *
 * fitness for a particular purpose and any warranties arising out of course  *
 * of performance, course of dealing or usage of trade.  Parties further      *
 * acknowledge that Company may, either presently and/or in the future,       *
 * instruct MTK to assist it in the development and the implementation, in    *
 * accordance with Company's designs, of certain softwares relating to        *
 * Company's product(s) (the "Services").  Except as may be otherwise agreed  *
 * to in writing, no warranties of any kind, whether express or implied, are  *
 * given by MTK with respect to the Services provided, and the Services are   *
 * provided on an "AS IS" basis.  Company further acknowledges that the       *
 * Services may contain errors, that testing is important and Company is      *
 * solely responsible for fully testing the Services and/or derivatives       *
 * thereof before they are used, sublicensed or distributed.  Should there be *
 * any third party action brought against MTK, arising out of or relating to  *
 * the Services, Company agree to fully indemnify and hold MTK harmless.      *
 * If the parties mutually agree to enter into or continue a business         *
 * relationship or other arrangement, the terms and conditions set forth      *
 * hereunder shall remain effective and, unless explicitly stated otherwise,  *
 * shall prevail in the event of a conflict in the terms in any agreements    *
 * entered into between the parties.                                          *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Copyright (c) 2005, CrystalMedia Technology, Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: wzd_anim.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_ATSC/23 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 47aa641dbb1c0b2b64f3264199a32d61 $
 *
 * Description:
 *      This file contains the implementation of GUI-related functions of the 
 * WIZARD application
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                  include files
-----------------------------------------------------------------------------*/
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_wgl_bdr_uniform.h"
#include "u_wgl_bdr_timg.h"
#include "u_wgl_animation.h"
 
#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_wgl_sets.h"
#include "c_gl.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_wgl_rect.h"

#include "wizard_anim/wzd_view.h"
#include "wizard_anim/wzd_anim.h"
#include "wizard_anim/wzd.h"

/*-----------------------------------------------------------------------------
                          Customizable macros
 ----------------------------------------------------------------------------*/
#ifndef WZD_DEFAULT_ANIM_CONTEXT
#define WZD_DEFAULT_ANIM_CONTEXT   ANIM_CONTEXT_APP_SYNC
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
* Menu animation config mask
*---------------------------------------------------------------------------*/
typedef UINT32 WZD_ANIM_CFG_MASK_T;

#define WZD_ANIM_CFG_MASK_FONT_ENLARGE                      MAKE_BIT_MASK_32(0)
#define WZD_ANIM_CFG_MASK_IMAGE_ENLARGE                     MAKE_BIT_MASK_32(1)
#define WZD_ANIM_CFG_MASK_ITEM_MOVE_ANIMATION               MAKE_BIT_MASK_32(2)
#define WZD_ANIM_CFG_MASK_FADE_IN_OUT_ANIMATION             MAKE_BIT_MASK_32(3)
#define WZD_ANIM_CFG_MASK_ICON_ANIMATION                    MAKE_BIT_MASK_32(4)

typedef struct _WZD_ANIMATION_DATA_T
{
    HANDLE_T            h_anim_item_move;               /* the item move animation handle */
    
    UINT16              ui2_item_move_total_steps;      /* how many steps for animation */
    UINT16              ui2_item_move_frame_interval;   /* frame interval*/

    UINT32              ui4_wzd_anim_cfg_mask;          /* wizard animation config mask */ 
    
} WZD_ANIMATION_DATA_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

static WZD_ANIMATION_DATA_T     t_g_wzd_anim_data;

static WGL_ANIMATION_DATA_T     t_anim_data_scale_down;
static WGL_ANIMATION_DATA_T     t_anim_data_scale_up;

static WGL_ANIMATION_DATA_T     t_anim_data_small_sb_scale_down;

static GL_RECT_T    t_g_rect_left = {0};
static GL_RECT_T    t_g_rect_center = {0};
static GL_RECT_T    t_g_rect_right = {0};

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _wzd_anim_start_move_animation(
    WZD_ANIM_TYPE_T    e_anim_type,
    VOID*               pv_param1,
    VOID*               pv_param2);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static INT32 _wzd_anim_init_scale_down(VOID)
{
    WGL_ANIMATION_DATA_T*   pt_anim_data_scale = &t_anim_data_scale_down;

    /* Clear animation data */
    c_memset (pt_anim_data_scale, 0, sizeof (WGL_ANIMATION_DATA_T));

    do
    {   
        /* begin animation */
        pt_anim_data_scale->ui2_count = 2;

        /* Alloc memory for animation control data */        
        pt_anim_data_scale->pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * pt_anim_data_scale->ui2_count));
        pt_anim_data_scale->pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * pt_anim_data_scale->ui2_count));
        
        if((NULL == pt_anim_data_scale->pt_anim_data) || 
           (NULL == pt_anim_data_scale->pt_path_mode))
        {
            DBG_ERROR(("[%s] ERROR @ File:%s(L%d)\n", __FUNCTION__, __FILE__, __LINE__));
            break;
        }

        c_memset(pt_anim_data_scale->pt_anim_data, 0, sizeof(WGL_ANIM_DATA_INFO) * pt_anim_data_scale->ui2_count);
        c_memset(pt_anim_data_scale->pt_path_mode, 0, sizeof(WGL_ANIM_PATH_DATA_T) * pt_anim_data_scale->ui2_count);

        /* Initialize animation path mode */
        pt_anim_data_scale->ui4_flag |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;

        /* Alpha animation path mode */        
        pt_anim_data_scale->pt_path_mode[0].ui2_anim_type |= WGL_ANIM_TYPE_SCALE;        
        pt_anim_data_scale->pt_path_mode[0].ui2_total_steps = WZD_ANIM_SCALE_TOTAL_STEPS;
        pt_anim_data_scale->pt_path_mode[0].ui2_frame_interval = 50;
        pt_anim_data_scale->pt_path_mode[0].ui4_start_tick = 1;
        pt_anim_data_scale->pt_path_mode[0].pf_type_cb = NULL;

        pt_anim_data_scale->pt_path_mode[1].ui2_anim_type |= WGL_ANIM_TYPE_ALPHA;        
        pt_anim_data_scale->pt_path_mode[1].ui2_total_steps = WZD_ANIM_SCALE_TOTAL_STEPS;
        pt_anim_data_scale->pt_path_mode[1].ui2_frame_interval = 50;
        pt_anim_data_scale->pt_path_mode[1].ui4_start_tick = 1;
        pt_anim_data_scale->pt_path_mode[1].pf_type_cb = NULL;

        pt_anim_data_scale->ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF; 

        pt_anim_data_scale->pt_anim_data[0].ui2_anim_type |= WGL_ANIM_TYPE_SCALE;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_start_w = WZD_SEL_BOX_BTN_W;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_start_h = WZD_SEL_BOX_BTN_H;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_end_w   = WZD_SB_SCALE_DOWN_BTN_W;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_end_h   = WZD_SB_SCALE_DOWN_BTN_H;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.e_ref_type  = ANIM_STD_REF_CENTER_CENTER;

        pt_anim_data_scale->pt_anim_data[1].ui2_anim_type |= WGL_ANIM_TYPE_ALPHA;
        pt_anim_data_scale->pt_anim_data[1].u_data.t_alpha.ui1_start_alpha = 255;
        pt_anim_data_scale->pt_anim_data[1].u_data.t_alpha.ui1_end_alpha = 0;

    } while(0);

    return WZDR_OK;
}

static INT32 _wzd_anim_init_scale_up(VOID)
{
    WGL_ANIMATION_DATA_T*   pt_anim_data_scale = &t_anim_data_scale_up;
    
    /* Clear animation data */
    c_memset (pt_anim_data_scale, 0, sizeof (WGL_ANIMATION_DATA_T));
    
    do
    {   
        /* begin animation */
        pt_anim_data_scale->ui2_count = 1;

        /* Alloc memory for animation control data */        
        pt_anim_data_scale->pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * pt_anim_data_scale->ui2_count));
        pt_anim_data_scale->pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * pt_anim_data_scale->ui2_count));

        if((NULL == pt_anim_data_scale->pt_anim_data) || 
           (NULL == pt_anim_data_scale->pt_path_mode))
        {
            DBG_ERROR(("[%s] ERROR @ File:%s(L%d)\n", __FUNCTION__, __FILE__, __LINE__));
            break;
        }

        c_memset(pt_anim_data_scale->pt_anim_data, 0, sizeof(WGL_ANIM_DATA_INFO) * pt_anim_data_scale->ui2_count);
        c_memset(pt_anim_data_scale->pt_path_mode, 0, sizeof(WGL_ANIM_PATH_DATA_T) * pt_anim_data_scale->ui2_count);

        /* Initialize animation path mode */
        pt_anim_data_scale->ui4_flag |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;

        /* Alpha animation path mode */
        pt_anim_data_scale->pt_path_mode[0].ui2_anim_type |= WGL_ANIM_TYPE_SCALE;        
        pt_anim_data_scale->pt_path_mode[0].ui2_total_steps = WZD_ANIM_SCALE_TOTAL_STEPS;
        pt_anim_data_scale->pt_path_mode[0].ui2_frame_interval = 50;
        pt_anim_data_scale->pt_path_mode[0].ui4_start_tick = 0;
        pt_anim_data_scale->pt_path_mode[0].pf_type_cb = NULL;

        pt_anim_data_scale->ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF;

        pt_anim_data_scale->pt_anim_data[0].ui2_anim_type |= WGL_ANIM_TYPE_SCALE;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_start_w = WZD_SEL_BOX_BTN_W;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_start_h = WZD_SEL_BOX_BTN_H;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_end_w   = WZD_SB_SCALE_UP_BTN_W;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_end_h   = WZD_SB_SCALE_UP_BTN_H;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.e_ref_type  = ANIM_STD_REF_CENTER_CENTER;

    } while(0);

    return WZDR_OK;    
}

/*----------------------------------------------------------------------------
 * Name: _wzd_anim_init_small_sb_scale_down
 *
 * Description: scale down the lose focus box for small sel box, such as: device type box, time zone box....
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_anim_init_small_sb_scale_down(VOID)
{
    WGL_ANIMATION_DATA_T*   pt_anim_data_scale = &t_anim_data_small_sb_scale_down;

    /* Clear animation data */
    c_memset (pt_anim_data_scale, 0, sizeof (WGL_ANIMATION_DATA_T));

    do
    {   
        /* begin animation */
        pt_anim_data_scale->ui2_count = 2;

        /* Alloc memory for animation control data */        
        pt_anim_data_scale->pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * pt_anim_data_scale->ui2_count));
        pt_anim_data_scale->pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * pt_anim_data_scale->ui2_count));
        
        if((NULL == pt_anim_data_scale->pt_anim_data) || 
           (NULL == pt_anim_data_scale->pt_path_mode))
        {
            DBG_ERROR(("[%s] ERROR @ File:%s(L%d)\n", __FUNCTION__, __FILE__, __LINE__));
            break;
        }

        c_memset(pt_anim_data_scale->pt_anim_data, 0, sizeof(WGL_ANIM_DATA_INFO) * pt_anim_data_scale->ui2_count);
        c_memset(pt_anim_data_scale->pt_path_mode, 0, sizeof(WGL_ANIM_PATH_DATA_T) * pt_anim_data_scale->ui2_count);

        /* Initialize animation path mode */
        pt_anim_data_scale->ui4_flag |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;

        /* Alpha animation path mode */        
        pt_anim_data_scale->pt_path_mode[0].ui2_anim_type |= WGL_ANIM_TYPE_SCALE;        
        pt_anim_data_scale->pt_path_mode[0].ui2_total_steps = WZD_ANIM_SCALE_TOTAL_STEPS;
        pt_anim_data_scale->pt_path_mode[0].ui2_frame_interval = 40;
        pt_anim_data_scale->pt_path_mode[0].ui4_start_tick = 1;
        pt_anim_data_scale->pt_path_mode[0].pf_type_cb = NULL;

        pt_anim_data_scale->pt_path_mode[1].ui2_anim_type |= WGL_ANIM_TYPE_ALPHA;        
        pt_anim_data_scale->pt_path_mode[1].ui2_total_steps = WZD_ANIM_SCALE_TOTAL_STEPS;
        pt_anim_data_scale->pt_path_mode[1].ui2_frame_interval = 50;
        pt_anim_data_scale->pt_path_mode[1].ui4_start_tick = 1;
        pt_anim_data_scale->pt_path_mode[1].pf_type_cb = NULL;

        pt_anim_data_scale->ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF; 

        pt_anim_data_scale->pt_anim_data[0].ui2_anim_type |= WGL_ANIM_TYPE_SCALE;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_start_w = WZD_SMALL_SEL_BOX_BTN_W;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_start_h = WZD_SMALL_SEL_BOX_BTN_H;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_end_w   = WZD_SMALL_SB_SCALE_DOWN_BTN_W;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.ui8_end_h   = WZD_SMALL_SB_SCALE_DOWN_BTN_H;
        pt_anim_data_scale->pt_anim_data[0].u_data.t_scale.e_ref_type  = ANIM_STD_REF_CENTER_CENTER;

        pt_anim_data_scale->pt_anim_data[1].ui2_anim_type |= WGL_ANIM_TYPE_ALPHA;
        pt_anim_data_scale->pt_anim_data[1].u_data.t_alpha.ui1_start_alpha = 255;
        pt_anim_data_scale->pt_anim_data[1].u_data.t_alpha.ui1_end_alpha = 0;

    } while(0);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description: 
 * Inputs: -
 * Outputs: -
 * Returns: 
 ----------------------------------------------------------------------------*/ 
static INT32 _wzd_anim_start_move_animation(
    WZD_ANIM_TYPE_T     e_anim_type,
    VOID*               pv_param1,          
    VOID*               pv_param2)
{
    INT32        i4_ret = WZDR_OK;
    GL_RECT_T*   pt_rect_from = NULL;
    GL_RECT_T*   pt_rect_to = NULL;
    HANDLE_T     h_anim_move = NULL_HANDLE;
    
    WZD_ANIMATION_DATA_T*   pt_wzd_anim = &t_g_wzd_anim_data;
    WGL_ANIMATION_DATA_T    t_anim_data;
    WGL_ANIM_CONTEXT_T      e_wzd_anim_context = WZD_DEFAULT_ANIM_CONTEXT;

    /* Check wzd animation configuration */
    if (!wzd_anim_has_feature(WZD_FT_UI_SUPPORT_ITEM_MOVE_ANIMATION))
    {
        return WZDR_OK;
    }

    /* Get move animation data by type */
    switch (e_anim_type)
    {
        case WZD_ANIM_TYPE_MOVE:
        {
            h_anim_move = pt_wzd_anim->h_anim_item_move;
        }
        break;

        default:
            return WZDR_INV_ARG;
    }

    /* Get move animation start, end position */
    pt_rect_from = (GL_RECT_T*)pv_param1;
    pt_rect_to   = (GL_RECT_T*)pv_param2;

    /* Check move animation start, end position */
    if ((NULL == pt_rect_from) ||
        (NULL == pt_rect_to))
    {
        return WZDR_INV_ARG;
    }

    /* Check animation handle validation */
    if (NULL_HANDLE == h_anim_move)
    {
        return WZDR_INV_ARG;
    }

    do
    {
        /* Clear animation data */
        c_memset (&t_anim_data, 0, sizeof (WGL_ANIMATION_DATA_T));
        
        /* Move animation widget */
        i4_ret = c_wgl_move (h_anim_move, 
                             pt_rect_from,
                             WGL_NO_AUTO_REPAINT);
        if (i4_ret != WGLR_OK)
        {
            break;
        }
        
        /* Stop origional animation firstly */
        i4_ret = c_wgl_end_animation (h_anim_move, NULL, NULL);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
        }
        
        /* begin animation */
        t_anim_data.ui2_count = 1;

        /* Alloc memory for animation control data */        
        t_anim_data.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_anim_data.ui2_count));
        t_anim_data.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_anim_data.ui2_count));
        if((NULL == t_anim_data.pt_anim_data) || 
           (NULL == t_anim_data.pt_path_mode))
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        c_memset(t_anim_data.pt_anim_data,0,sizeof(WGL_ANIM_DATA_INFO));
        c_memset(t_anim_data.pt_path_mode,0,sizeof(WGL_ANIM_PATH_DATA_T));

        /* Initialize animation path mode */
        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;
        t_anim_data.pt_path_mode->ui2_anim_type |= WGL_ANIM_TYPE_MOVE;

        t_anim_data.pt_path_mode->ui2_total_steps = pt_wzd_anim->ui2_item_move_total_steps;
        t_anim_data.pt_path_mode->ui2_frame_interval = pt_wzd_anim->ui2_item_move_frame_interval;
        t_anim_data.pt_path_mode->ui4_start_tick = 0;
        t_anim_data.pt_path_mode->pf_type_cb = NULL;

        /* Initialize animation data info */        
        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF;
        t_anim_data.pt_anim_data->ui2_anim_type |= WGL_ANIM_TYPE_MOVE;

        t_anim_data.pt_anim_data->u_data.t_move.i2_start_x = pt_rect_from->i4_left;
        t_anim_data.pt_anim_data->u_data.t_move.i2_start_y = pt_rect_from->i4_top;
        t_anim_data.pt_anim_data->u_data.t_move.i2_end_x   = pt_rect_to->i4_left;
        t_anim_data.pt_anim_data->u_data.t_move.i2_end_y   = pt_rect_to->i4_top;

        /* Show animation widget */
        c_wgl_set_visibility(h_anim_move, WGL_SW_NORMAL);

        /* Start animation */
        i4_ret= c_wgl_start_animation(
                        h_anim_move,
                        &t_anim_data,
                        e_wzd_anim_context);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }
        
    } while(0);

    /* Free memory for animation control data */
    if (t_anim_data.pt_anim_data)
    {
        c_mem_free(t_anim_data.pt_anim_data);
    }

    if (t_anim_data.pt_path_mode)
    {
        c_mem_free(t_anim_data.pt_path_mode);
    }

    /* Stop origional animation */
    i4_ret = c_wgl_end_animation (h_anim_move, NULL, NULL);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
    
/*-----------------------------------------------------------------------------
 * Name: wzd_anim_has_feature
 *
 * Description
 *      The API is used to check whether wzd support queryed feature.
 * Input arguments
 *      e_feature     feature ID
 * Output arguments
 *      None
 * Returns
 *      TRUE    support queryed feature
 *      FALSE   do not support
 *---------------------------------------------------------------------------*/
BOOL wzd_anim_has_feature (WZD_FT_CFG_T  e_feature)

{
    BOOL  b_has_feature = FALSE;
    WZD_ANIMATION_DATA_T* pt_wzd_anim = &t_g_wzd_anim_data;

    switch (e_feature)
    {
        case WZD_FT_UI_SUPPORT_FONT_ENLARGE:
            b_has_feature = (WZD_ANIM_CFG_MASK_FONT_ENLARGE & pt_wzd_anim->ui4_wzd_anim_cfg_mask);
            break;
        
        case WZD_FT_UI_SUPPORT_IMAGE_ENLARGE:
            b_has_feature = (WZD_ANIM_CFG_MASK_IMAGE_ENLARGE & pt_wzd_anim->ui4_wzd_anim_cfg_mask);
            break;

        case WZD_FT_UI_SUPPORT_ITEM_MOVE_ANIMATION:
            b_has_feature = (WZD_ANIM_CFG_MASK_ITEM_MOVE_ANIMATION & pt_wzd_anim->ui4_wzd_anim_cfg_mask);
            break;

        case WZD_FT_UI_SUPPORT_ICON_ANIMATION:
            b_has_feature = (WZD_ANIM_CFG_MASK_ICON_ANIMATION & pt_wzd_anim->ui4_wzd_anim_cfg_mask);
            break;

        case WZD_FT_UI_SUPPORT_FADE_IN_OUT_ANIMATION:
            b_has_feature = (WZD_ANIM_CFG_MASK_FADE_IN_OUT_ANIMATION & pt_wzd_anim->ui4_wzd_anim_cfg_mask);
            break;

        default:
            b_has_feature = FALSE;
            break;
    }

    return b_has_feature;
}


/*----------------------------------------------------------------------------
 * Name: wzd_anim_init
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
INT32 wzd_anim_init(VOID)
{
    INT32                   i4_ret = WZDR_OK;
    WZD_ANIMATION_DATA_T*   pt_wzd_anim = &t_g_wzd_anim_data;

    c_memset(pt_wzd_anim, 0, sizeof(WZD_ANIMATION_DATA_T));

    /* Init animation control data */
    pt_wzd_anim->ui2_item_move_total_steps = WZD_ANIM_PAGE_MOVE_STEPS;
    pt_wzd_anim->ui2_item_move_frame_interval = (UINT16)c_wgl_get_tick_interval();

    /* get rectangle size */
    SET_RECT_BY_SIZE (&t_g_rect_center,
                      BASE_FRM_X,
                      BASE_FRM_Y,
                      BASE_FRM_W,
                      BASE_FRM_H);

    t_g_rect_left.i4_left    = t_g_rect_center.i4_left - (WGL_RECT_GET_WIDTH(&t_g_rect_center));
    t_g_rect_left.i4_right   = t_g_rect_center.i4_right - (WGL_RECT_GET_WIDTH(&t_g_rect_center));
    t_g_rect_left.i4_bottom  = t_g_rect_center.i4_bottom;
    t_g_rect_left.i4_top     = t_g_rect_center.i4_top;

    t_g_rect_right.i4_left   = t_g_rect_center.i4_left + (WGL_RECT_GET_WIDTH(&t_g_rect_center));
    t_g_rect_right.i4_right  = t_g_rect_center.i4_right + (WGL_RECT_GET_WIDTH(&t_g_rect_center));
    t_g_rect_right.i4_bottom = t_g_rect_center.i4_bottom;
    t_g_rect_right.i4_top    = t_g_rect_center.i4_top;

    /* Config animation capability */
    pt_wzd_anim->ui4_wzd_anim_cfg_mask = WZD_ANIM_CFG_MASK_IMAGE_ENLARGE             |
                                         WZD_ANIM_CFG_MASK_ITEM_MOVE_ANIMATION       |
                                         WZD_ANIM_CFG_MASK_FADE_IN_OUT_ANIMATION     |
                                         WZD_ANIM_CFG_MASK_ICON_ANIMATION;

    _wzd_anim_init_scale_up();
    _wzd_anim_init_scale_down();
    _wzd_anim_init_small_sb_scale_down();

    do
    {
        /* Create Item move animation widget: frame */
        RET_ON_ERR (wzd_view_get_base_frm(&(pt_wzd_anim->h_anim_item_move)));
        
    }while(0);

    if(i4_ret != WZDR_OK)
    {
        /* Destroy wzd animation data */
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_anim_deinit
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
INT32 wzd_anim_deinit(VOID)
{

    /* Free memory for animation control data */
    if (t_anim_data_scale_up.pt_anim_data)
    {
        c_mem_free(t_anim_data_scale_up.pt_anim_data);
    }
    if (t_anim_data_scale_up.pt_path_mode)
    {
        c_mem_free(t_anim_data_scale_up.pt_path_mode);
    }

    if (t_anim_data_scale_down.pt_anim_data)
    {
        c_mem_free(t_anim_data_scale_down.pt_anim_data);
    }
    if (t_anim_data_scale_down.pt_path_mode)
    {
        c_mem_free(t_anim_data_scale_down.pt_path_mode);
    }

    if (t_anim_data_small_sb_scale_down.pt_anim_data)
    {
        c_mem_free(t_anim_data_small_sb_scale_down.pt_anim_data);
    }
    if (t_anim_data_small_sb_scale_down.pt_path_mode)
    {
        c_mem_free(t_anim_data_small_sb_scale_down.pt_path_mode);
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description: 
 * Inputs: -
 * Outputs: -
 * Returns: 
 ----------------------------------------------------------------------------*/ 
INT32 wzd_anim_start_animation(
    WZD_ANIM_TYPE_T     e_anim_type,
    VOID*               pv_param1,
    VOID*               pv_param2)
{
    switch (e_anim_type)
    {
        case WZD_ANIM_TYPE_MOVE:
        {
            _wzd_anim_start_move_animation(e_anim_type, pv_param1, pv_param2);
        }
        break;

        case WZD_ANIM_TYPE_ALPHA:
        {
            //
        }
        break; 

        default:
            break;
    }
    
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description: 
 * Inputs: -
 * Outputs: -
 * Returns: 
 ----------------------------------------------------------------------------*/ 
INT32 wzd_anim_set_feature_cfg(
    WZD_FT_CFG_T  e_feature,
    BOOL           b_enable)
{
    WZD_ANIMATION_DATA_T* pt_wzd_anim = &t_g_wzd_anim_data;
    WZD_ANIM_CFG_MASK_T t_temp_ft_mask = 0;

    switch (e_feature)
    {
        case WZD_FT_UI_SUPPORT_ITEM_MOVE_ANIMATION:
            t_temp_ft_mask = WZD_ANIM_CFG_MASK_ITEM_MOVE_ANIMATION;
            break;

        case WZD_FT_UI_SUPPORT_ICON_ANIMATION:
            t_temp_ft_mask = WZD_ANIM_CFG_MASK_ICON_ANIMATION;
            break;

        case WZD_FT_UI_SUPPORT_FADE_IN_OUT_ANIMATION:
            t_temp_ft_mask = WZD_ANIM_CFG_MASK_FADE_IN_OUT_ANIMATION;
            break;

        default:
            return WZDR_OK;
    }

    if (b_enable)
    {
        pt_wzd_anim->ui4_wzd_anim_cfg_mask |= t_temp_ft_mask;
    }
    else
    {
        pt_wzd_anim->ui4_wzd_anim_cfg_mask &= ~t_temp_ft_mask;
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_anim_start_move_page
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
INT32 wzd_anim_start_move_page(WZD_ANIM_MOVE_PAGE_TYPE_T  e_move_type)
{
    GL_RECT_T*              pt_rect_from = NULL;
    GL_RECT_T*              pt_rect_to = NULL;

    /* Get move animation start, end position */
    switch (e_move_type)
    {
        case WZD_ANIM_MOVE_PAGE_LEFT_TO_CENTER:
            pt_rect_from = &t_g_rect_left;
            pt_rect_to   = &t_g_rect_center;
            break;

        case WZD_ANIM_MOVE_PAGE_CENTER_TO_RIGHT:
            pt_rect_from = &t_g_rect_center;
            pt_rect_to   = &t_g_rect_right;
            break;

        case WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER:
            pt_rect_from = &t_g_rect_right;
            pt_rect_to   = &t_g_rect_center;
            break;

        case WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT:
            pt_rect_from = &t_g_rect_center;
            pt_rect_to   = &t_g_rect_left;
            break;

        default:
            return WZDR_OK;
    }

    wzd_anim_start_animation (
                        WZD_ANIM_TYPE_MOVE, 
                        pt_rect_from, 
                        pt_rect_to);

    return WZDR_OK;
}

INT32 wzd_anim_fade_out_scale_down(HANDLE_T  h_anim_scale)
{
    INT32                   i4_ret = WZDR_OK;

    if((NULL == t_anim_data_scale_down.pt_anim_data) || 
       (NULL == t_anim_data_scale_down.pt_path_mode))
    {
        DBG_ERROR(("[WZD][%s] ERROR @ File:%s(L%d)\n", __FUNCTION__, __FILE__, __LINE__));
    }

    do
    {
        /* Stop origional animation firstly */
        i4_ret = c_wgl_end_animation (h_anim_scale, NULL, NULL);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        /* Start animation */
        i4_ret= c_wgl_start_animation(
                        h_anim_scale,
                        &t_anim_data_scale_down,
                        ANIM_CONTEXT_APP);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }
        
    } while(0);

    return WZDR_OK;
}

INT32 wzd_anim_small_sb_scale_down(HANDLE_T  h_anim_scale)
{
    INT32                   i4_ret = WZDR_OK;

    if((NULL == t_anim_data_small_sb_scale_down.pt_anim_data) || 
       (NULL == t_anim_data_small_sb_scale_down.pt_path_mode))
    {
        DBG_ERROR(("[WZD][%s] ERROR @ File:%s(L%d)\n", __FUNCTION__, __FILE__, __LINE__));
    }

    do
    {
        /* Stop origional animation firstly */
        i4_ret = c_wgl_end_animation (h_anim_scale, NULL, NULL);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        /* Start animation */
        i4_ret= c_wgl_start_animation(
                        h_anim_scale,
                        &t_anim_data_small_sb_scale_down,
                        ANIM_CONTEXT_APP);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }
        
    } while(0);

    return WZDR_OK;
}

INT32 wzd_anim_scale_up(HANDLE_T  h_anim_scale)
{
    INT32                   i4_ret = WZDR_OK;

    if((NULL == t_anim_data_scale_up.pt_anim_data) || 
       (NULL == t_anim_data_scale_up.pt_path_mode))
    {
        DBG_ERROR(("[WZD][%s] ERROR @ File:%s(L%d)\n", __FUNCTION__, __FILE__, __LINE__));
    }

    do
    {
        /* Stop origional animation firstly */
        i4_ret = c_wgl_end_animation (h_anim_scale, NULL, NULL);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        /* Start animation */
        i4_ret= c_wgl_start_animation(
                        h_anim_scale,
                        &t_anim_data_scale_up,
                        ANIM_CONTEXT_APP);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }
        
    } while(0);

    return WZDR_OK;    
}

INT32 wzd_anim_scale_down_up(HANDLE_T  h_anim_scale)
{  
    INT32                   i4_ret = WZDR_OK;     
    WGL_ANIMATION_DATA_T    t_anim_data;
    WGL_ANIM_CONTEXT_T      e_wzd_anim_context = ANIM_CONTEXT_APP;
    GL_RECT_T               scale_rect;
    INT32                   ui4_frm_width;
    INT32                   ui4_frm_high;

    c_memset (&t_anim_data, 0, sizeof (WGL_ANIMATION_DATA_T));

    c_wgl_get_coords(h_anim_scale, WGL_COORDS_SCREEN, &scale_rect);

    ui4_frm_width = scale_rect.i4_right - scale_rect.i4_left;
    ui4_frm_high = scale_rect.i4_bottom - scale_rect.i4_top;

    do
    {
        /* Stop origional animation firstly */
        i4_ret = c_wgl_end_animation (h_anim_scale, NULL, NULL);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
        }
        
        /* begin animation */
        t_anim_data.ui2_count = 2;

        /* Alloc memory for animation control data */        
        t_anim_data.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_anim_data.ui2_count));
        t_anim_data.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_anim_data.ui2_count));
        
        if((NULL == t_anim_data.pt_anim_data) || 
           (NULL == t_anim_data.pt_path_mode))
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        c_memset(t_anim_data.pt_anim_data, 0, sizeof(WGL_ANIM_DATA_INFO) * t_anim_data.ui2_count);
        c_memset(t_anim_data.pt_path_mode, 0, sizeof(WGL_ANIM_PATH_DATA_T) * t_anim_data.ui2_count);

        /* Initialize animation path mode */
        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;

        /* Scale animation path mode */
        t_anim_data.pt_path_mode[0].ui2_anim_type      |= WGL_ANIM_TYPE_SCALE;        
        t_anim_data.pt_path_mode[0].ui2_total_steps     = 2;
        t_anim_data.pt_path_mode[0].ui2_frame_interval  = 50;
        t_anim_data.pt_path_mode[0].ui4_start_tick      = 0;
        t_anim_data.pt_path_mode[0].pf_type_cb          = NULL;
        t_anim_data.pt_path_mode[0].e_play_mode         = ANIM_PLAY_MODE_ONCE;
        t_anim_data.pt_path_mode[0].ui2_loop_count      = 1;

        t_anim_data.pt_path_mode[1].ui2_anim_type      |= WGL_ANIM_TYPE_SCALE;        
        t_anim_data.pt_path_mode[1].ui2_total_steps     = 4;
        t_anim_data.pt_path_mode[1].ui2_frame_interval  = 50;
        t_anim_data.pt_path_mode[1].ui4_start_tick      = 2;
        t_anim_data.pt_path_mode[1].pf_type_cb          = NULL;
        t_anim_data.pt_path_mode[1].e_play_mode         = ANIM_PLAY_MODE_ONCE;
        t_anim_data.pt_path_mode[1].ui2_loop_count      = 1;


        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF;

        t_anim_data.pt_anim_data[0].ui2_anim_type |= WGL_ANIM_TYPE_SCALE;
        t_anim_data.pt_anim_data[0].u_data.t_scale.ui8_start_w = ui4_frm_width;
        t_anim_data.pt_anim_data[0].u_data.t_scale.ui8_start_h = ui4_frm_high;
        t_anim_data.pt_anim_data[0].u_data.t_scale.ui8_end_w   = 530;
        t_anim_data.pt_anim_data[0].u_data.t_scale.ui8_end_h   = 493;
        t_anim_data.pt_anim_data[0].u_data.t_scale.e_ref_type  = ANIM_STD_REF_CENTER_CENTER;    

        t_anim_data.pt_anim_data[1].ui2_anim_type |= WGL_ANIM_TYPE_SCALE;
        t_anim_data.pt_anim_data[1].u_data.t_scale.ui8_start_w = 530;
        t_anim_data.pt_anim_data[1].u_data.t_scale.ui8_start_h = 493;
        t_anim_data.pt_anim_data[1].u_data.t_scale.ui8_end_w   = ui4_frm_width;
        t_anim_data.pt_anim_data[1].u_data.t_scale.ui8_end_h   = ui4_frm_high;
        t_anim_data.pt_anim_data[1].u_data.t_scale.e_ref_type  = ANIM_STD_REF_CENTER_CENTER;


        /* Start animation */
        i4_ret= c_wgl_start_animation(
                        h_anim_scale,
                        &t_anim_data,
                        e_wzd_anim_context);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

    } while(0);

    /* Free memory for animation control data */
    if (t_anim_data.pt_anim_data)
    {
        c_mem_free(t_anim_data.pt_anim_data);
    }

    if (t_anim_data.pt_path_mode)
    {
        c_mem_free(t_anim_data.pt_path_mode);
    }
 
    return WZDR_OK;
}

INT32 a_wzd_anim_mix (HANDLE_T h_widget, ANIM_DATA_MIX_T* pt_anim_data, BOOL b_end)
{
    INT32                   i4_ret = WZDR_OK;     
    WGL_ANIMATION_DATA_T    t_anim_data;
    WGL_ANIM_CONTEXT_T      e_wzd_anim_context = ANIM_CONTEXT_APP;

    if (pt_anim_data == NULL)
    {
        DBG_ERROR(("ERROR: t_anim_data can not be NULL!\n"));
        return WGLR_INV_ARG;
    }

    do
    {
        /* Stop origional animation firstly */
        if (b_end)
        {
            i4_ret = c_wgl_end_animation(h_widget, NULL, NULL);  
            if (i4_ret != WGLR_OK)
            {
                DBG_ERROR(("ERROR: c_wgl_end_animation() failed! i4_ret: %d\n", i4_ret));
               return i4_ret;
            }
        }
        
        /* Clear animation data */
        c_memset (&t_anim_data, 0, sizeof (WGL_ANIMATION_DATA_T)); 

        /* begin animation */
        t_anim_data.ui2_count = 3;

        /* Alloc memory for animation control data */        
        t_anim_data.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_anim_data.ui2_count));
        t_anim_data.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_anim_data.ui2_count));

        if ((NULL == t_anim_data.pt_anim_data) || 
            (NULL == t_anim_data.pt_path_mode))
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        c_memset(t_anim_data.pt_anim_data, 0, sizeof(WGL_ANIM_DATA_INFO) * t_anim_data.ui2_count);
        c_memset(t_anim_data.pt_path_mode, 0, sizeof(WGL_ANIM_PATH_DATA_T) * t_anim_data.ui2_count);

        /* Initialize animation path mode */
        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;

        /* Image animation path mode */
        t_anim_data.pt_path_mode[0].ui2_anim_type     |= WGL_ANIM_TYPE_MOVE;       
        t_anim_data.pt_path_mode[0].ui2_total_steps    = pt_anim_data->ui2_move_steps;
        t_anim_data.pt_path_mode[0].ui2_frame_interval = pt_anim_data->ui2_frame_interval;
        t_anim_data.pt_path_mode[0].ui4_start_tick     = pt_anim_data->ui4_start_tick;
        t_anim_data.pt_path_mode[0].pf_type_cb         = NULL;
        t_anim_data.pt_path_mode[0].e_play_mode        = ANIM_PLAY_MODE_ONCE;
        t_anim_data.pt_path_mode[0].ui2_loop_count     = 1;

        t_anim_data.pt_path_mode[1].ui2_anim_type     |= WGL_ANIM_TYPE_SCALE;        
        t_anim_data.pt_path_mode[1].ui2_total_steps    = pt_anim_data->ui2_scale_steps;
        t_anim_data.pt_path_mode[1].ui2_frame_interval = pt_anim_data->ui2_frame_interval;
        t_anim_data.pt_path_mode[1].ui4_start_tick     = pt_anim_data->ui4_start_tick;
        t_anim_data.pt_path_mode[1].pf_type_cb         = NULL;
        t_anim_data.pt_path_mode[1].e_play_mode        = ANIM_PLAY_MODE_ONCE;
        t_anim_data.pt_path_mode[1].ui2_loop_count     = 1;

        t_anim_data.pt_path_mode[2].ui2_anim_type     |= WGL_ANIM_TYPE_ALPHA;        
        t_anim_data.pt_path_mode[2].ui2_total_steps    = pt_anim_data->ui2_alpha_steps;
        t_anim_data.pt_path_mode[2].ui2_frame_interval = pt_anim_data->ui2_frame_interval;
        t_anim_data.pt_path_mode[2].ui4_start_tick     = pt_anim_data->ui4_start_tick;
        t_anim_data.pt_path_mode[2].pf_type_cb         = NULL;
        t_anim_data.pt_path_mode[2].e_play_mode        = ANIM_PLAY_MODE_ONCE;
        t_anim_data.pt_path_mode[2].ui2_loop_count     = 1;


        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF;

        t_anim_data.pt_anim_data[0].ui2_anim_type |= WGL_ANIM_TYPE_MOVE;
        t_anim_data.pt_anim_data[0].u_data.t_move.i2_start_x = pt_anim_data->i2_start_x;
        t_anim_data.pt_anim_data[0].u_data.t_move.i2_start_y = pt_anim_data->i2_start_y;
        t_anim_data.pt_anim_data[0].u_data.t_move.i2_end_x   = pt_anim_data->i2_end_x;
        t_anim_data.pt_anim_data[0].u_data.t_move.i2_end_y   = pt_anim_data->i2_end_y;   

        t_anim_data.pt_anim_data[1].ui2_anim_type |= WGL_ANIM_TYPE_SCALE;
        t_anim_data.pt_anim_data[1].u_data.t_scale.ui8_start_w = pt_anim_data->ui8_start_w;
        t_anim_data.pt_anim_data[1].u_data.t_scale.ui8_start_h = pt_anim_data->ui8_start_h;
        t_anim_data.pt_anim_data[1].u_data.t_scale.ui8_end_w   = pt_anim_data->ui8_end_w;
        t_anim_data.pt_anim_data[1].u_data.t_scale.ui8_end_h   = pt_anim_data->ui8_end_h;
        t_anim_data.pt_anim_data[1].u_data.t_scale.e_ref_type  = ANIM_STD_REF_CENTER_CENTER;    

        t_anim_data.pt_anim_data[2].ui2_anim_type |= WGL_ANIM_TYPE_ALPHA;
        t_anim_data.pt_anim_data[2].u_data.t_alpha.ui1_start_alpha = pt_anim_data->ui1_start_alpha;
        t_anim_data.pt_anim_data[2].u_data.t_alpha.ui1_end_alpha = pt_anim_data->ui1_end_alpha;
    
        /* set visibility normal */
	    c_wgl_set_visibility(h_widget, WGL_SW_NORMAL);
        
        /* Set initial alpha firstly */
        c_wgl_set_alpha(h_widget, pt_anim_data->ui1_start_alpha);

        /* Start animation */
        i4_ret= c_wgl_start_animation(
                         h_widget,
                         &t_anim_data,
                         e_wzd_anim_context);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

    } while(0);

    /* Free memory for animation control data */
    if (t_anim_data.pt_anim_data)
    {
        c_mem_free(t_anim_data.pt_anim_data);
    }

    if (t_anim_data.pt_path_mode)
    {
        c_mem_free(t_anim_data.pt_path_mode);
    }

    return WZDR_OK;
}

INT32 a_wzd_anim_image_move(HANDLE_T h_widget, ANIM_DATA_IMG_T* pt_anim_data, BOOL b_end)
{
    INT32                i4_ret;
    WGL_ANIMATION_DATA_T t_begin;

    if (pt_anim_data == NULL)
    {
        DBG_ERROR(("ERROR: t_anim_data can not be NULL!\n"));
        return WGLR_INV_ARG;
    }
    
    if (b_end)
    {
        i4_ret = c_wgl_end_animation(h_widget, NULL, NULL);  
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("ERROR: c_wgl_end_animation() failed! i4_ret: %d\n", i4_ret));
           return i4_ret;
        }
    }

#ifdef TEST_MOVE_ONLY
    t_begin.ui2_count = 1;
#else
    t_begin.ui2_count = 2;
#endif

    t_begin.ui4_flag  = 0;
    t_begin.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_begin.ui2_count));
    t_begin.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_begin.ui2_count));
    if((t_begin.pt_anim_data == NULL) || (t_begin.pt_path_mode == NULL))
    {
        DBG_ERROR(("ERROR: Alloc memory failed! File=%s, Line=%d\n", __FILE__, __LINE__));
    }

    c_memset(t_begin.pt_anim_data, 0, t_begin.ui2_count*sizeof(WGL_ANIM_DATA_INFO));
    c_memset(t_begin.pt_path_mode, 0, t_begin.ui2_count*sizeof(WGL_ANIM_PATH_DATA_T));

#ifndef TEST_MOVE_ONLY
    t_begin.pt_path_mode[0].ui2_anim_type     |= WGL_ANIM_TYPE_IMG;
    t_begin.ui4_flag                          |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;
    t_begin.pt_path_mode[0].ui2_total_steps    = pt_anim_data->ui2_total_steps;
    t_begin.pt_path_mode[0].ui4_start_tick     = 0;
    t_begin.pt_path_mode[0].ui2_frame_interval = pt_anim_data->ui2_frame_interval;
    t_begin.pt_path_mode[0].pf_type_cb         = NULL;
    t_begin.pt_path_mode[0].e_play_mode        = ANIM_PLAY_MODE_LOOP;
    t_begin.pt_path_mode[0].ui2_loop_count     = 10;
  
    t_begin.ui4_flag                          |= WGL_ANIM_DATA_FLAG_DATA_INF;
    t_begin.pt_anim_data[0].ui2_anim_type     |= WGL_ANIM_TYPE_IMG;
    t_begin.pt_anim_data[0].u_data.t_img.ui1_img_seq_id = 0;
    t_begin.pt_anim_data[0].u_data.t_img.ui2_cust_len = 0;
    t_begin.pt_anim_data[0].u_data.t_img.pt_cust_info = NULL;   
 
    t_begin.pt_path_mode[1].ui2_anim_type     |= WGL_ANIM_TYPE_MOVE;
    t_begin.pt_path_mode[1].ui2_total_steps = 10;
    t_begin.pt_path_mode[1].ui4_start_tick = 0;
    t_begin.pt_path_mode[1].ui2_frame_interval = pt_anim_data->ui2_frame_interval;
    t_begin.pt_path_mode[1].pf_type_cb = pt_anim_data->pf_type_cb;
    t_begin.pt_path_mode[1].e_play_mode        = ANIM_PLAY_MODE_LOOP;
    t_begin.pt_path_mode[1].ui2_loop_count     = 10;
    
     t_begin.pt_anim_data[1].ui2_anim_type    |= WGL_ANIM_TYPE_MOVE;
     t_begin.pt_anim_data[1].u_data.t_move.i2_start_x = pt_anim_data->i2_start_x;
     t_begin.pt_anim_data[1].u_data.t_move.i2_start_y = pt_anim_data->i2_start_y;
     t_begin.pt_anim_data[1].u_data.t_move.i2_end_x = pt_anim_data->i2_end_x;
     t_begin.pt_anim_data[1].u_data.t_move.i2_end_y =pt_anim_data->i2_end_y;
#else
    t_begin.ui4_flag                          |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;
    t_begin.pt_path_mode[0].ui2_anim_type     |= WGL_ANIM_TYPE_MOVE;
    t_begin.pt_path_mode[0].ui2_total_steps    = 10;
    t_begin.pt_path_mode[0].ui4_start_tick     = 0;
    t_begin.pt_path_mode[0].ui2_frame_interval = pt_anim_data->ui2_frame_interval;
    t_begin.pt_path_mode[0].pf_type_cb         = pt_anim_data->pf_type_cb;
    t_begin.pt_path_mode->e_play_mode          = ANIM_PLAY_MODE_LOOP;
    t_begin.pt_path_mode->ui2_loop_count       = 3;
    
    t_begin.ui4_flag                          |= WGL_ANIM_DATA_FLAG_DATA_INF;   
     t_begin.pt_anim_data[0].ui2_anim_type    |= WGL_ANIM_TYPE_MOVE;
     t_begin.pt_anim_data[0].u_data.t_move.i2_start_x = pt_anim_data->i2_start_x;
     t_begin.pt_anim_data[0].u_data.t_move.i2_start_y = pt_anim_data->i2_start_y;
     t_begin.pt_anim_data[0].u_data.t_move.i2_end_x   = pt_anim_data->i2_end_x;
     t_begin.pt_anim_data[0].u_data.t_move.i2_end_y   = pt_anim_data->i2_end_y;
#endif

    i4_ret= c_wgl_start_animation(
                         h_widget,
                         &t_begin,
                         ANIM_CONTEXT_APP_SYNC);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("ERROR: c_wgl_start_animation() failed! i4_ret: %d\n", i4_ret));
    }

    /* Free memory for animation control data */
    if (t_begin.pt_anim_data)
    {
        c_mem_free(t_begin.pt_anim_data);
    }

    if (t_begin.pt_path_mode)
    {
        c_mem_free(t_begin.pt_path_mode);
    }
    
    return i4_ret;
}

INT32 a_wzd_anim_move(HANDLE_T h_widget, ANIM_DATA_MOVE_T* pt_anim_data, BOOL b_end)
{
    INT32                i4_ret;
    WGL_ANIMATION_DATA_T t_begin;

    if (pt_anim_data == NULL)
    {
        DBG_ERROR(("ERROR: t_anim_data can not be NULL!\n"));
        return WGLR_INV_ARG;
    }
    
    if (b_end)
    {
        i4_ret = c_wgl_end_animation(h_widget, NULL, NULL);  
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("ERROR: c_wgl_end_animation() failed! i4_ret: %d\n", i4_ret));
           return i4_ret;
        }
    }

    t_begin.ui2_count = 1;
    t_begin.ui4_flag  = 0;
    t_begin.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_begin.ui2_count));
    t_begin.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_begin.ui2_count));
    if((t_begin.pt_anim_data == NULL) || (t_begin.pt_path_mode == NULL))
    {
        DBG_ERROR(("ERROR: Alloc memory failed! File=%s, Line=%d\n", __FILE__, __LINE__));
    }

    c_memset(t_begin.pt_anim_data, 0, sizeof(WGL_ANIM_DATA_INFO));
    c_memset(t_begin.pt_path_mode, 0, sizeof(WGL_ANIM_PATH_DATA_T));

    t_begin.pt_path_mode->ui2_anim_type     |= WGL_ANIM_TYPE_MOVE;
    t_begin.ui4_flag                        |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;
    t_begin.pt_path_mode->ui2_total_steps    = pt_anim_data->ui2_total_steps;
    t_begin.pt_path_mode->ui4_start_tick     = 0;
    t_begin.pt_path_mode->ui2_frame_interval = pt_anim_data->ui2_frame_interval;
    t_begin.pt_path_mode->pf_type_cb         = NULL;
    t_begin.pt_path_mode->e_play_mode        = ANIM_PLAY_MODE_ONCE;
    t_begin.pt_path_mode->ui2_loop_count     = 1;
    
    t_begin.ui4_flag                              |= WGL_ANIM_DATA_FLAG_DATA_INF;
    t_begin.pt_anim_data->ui2_anim_type           |= WGL_ANIM_TYPE_MOVE;
    t_begin.pt_anim_data->u_data.t_move.i2_start_x = pt_anim_data->i2_start_x;
    t_begin.pt_anim_data->u_data.t_move.i2_start_y = pt_anim_data->i2_start_y;
    t_begin.pt_anim_data->u_data.t_move.i2_end_x   = pt_anim_data->i2_end_x;
    t_begin.pt_anim_data->u_data.t_move.i2_end_y   = pt_anim_data->i2_end_y;

    i4_ret= c_wgl_start_animation(
                         h_widget,
                         &t_begin,
                         ANIM_CONTEXT_APP_SYNC);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("ERROR: c_wgl_start_animation() failed! i4_ret: %d\n", i4_ret));
    }

    /* Free memory for animation control data */
    if (t_begin.pt_anim_data)
    {
        c_mem_free(t_begin.pt_anim_data);
    }

    if (t_begin.pt_path_mode)
    {
        c_mem_free(t_begin.pt_path_mode);
    }
    
    return i4_ret;
}

INT32 a_wzd_anim_move_ex(HANDLE_T h_widget, ANIM_DATA_MOVE_T* pt_anim_data, BOOL b_end)
{
    INT32                i4_ret;
    WGL_ANIMATION_DATA_T t_begin;

    if (pt_anim_data == NULL)
    {
        DBG_ERROR(("ERROR: t_anim_data can not be NULL!\n"));
        return WGLR_INV_ARG;
    }
    
    if (b_end)
    {
        i4_ret = c_wgl_end_animation(h_widget, NULL, NULL);  
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("ERROR: c_wgl_end_animation() failed! i4_ret: %d\n", i4_ret));
           return i4_ret;
        }
    }

    if (pt_anim_data->i2_start_y > pt_anim_data->i2_end_y)
    {
        t_begin.ui2_count = 2;
    }
    else
    {
        t_begin.ui2_count = 1;
    }
    t_begin.ui4_flag  = 0;
    t_begin.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_begin.ui2_count));
    t_begin.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_begin.ui2_count));
    if((t_begin.pt_anim_data == NULL) || (t_begin.pt_path_mode == NULL))
    {
        DBG_ERROR(("ERROR: Alloc memory failed! File=%s, Line=%d\n", __FILE__, __LINE__));
    }

    c_memset(t_begin.pt_anim_data, 0, t_begin.ui2_count*sizeof(WGL_ANIM_DATA_INFO));
    c_memset(t_begin.pt_path_mode, 0, t_begin.ui2_count*sizeof(WGL_ANIM_PATH_DATA_T));

    t_begin.ui4_flag                          |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;
    t_begin.pt_path_mode[0].ui2_anim_type     |= WGL_ANIM_TYPE_MOVE;
    t_begin.pt_path_mode[0].ui2_total_steps    = pt_anim_data->ui2_total_steps;
    t_begin.pt_path_mode[0].ui4_start_tick     = 0;
    t_begin.pt_path_mode[0].ui2_frame_interval = pt_anim_data->ui2_frame_interval;
    t_begin.pt_path_mode[0].pf_type_cb         = NULL;
    t_begin.pt_path_mode[0].e_play_mode        = ANIM_PLAY_MODE_ONCE;
    t_begin.pt_path_mode[0].ui2_loop_count     = 1;
    if (2 == t_begin.ui2_count)
    {
        t_begin.pt_path_mode[1].ui2_anim_type  |= WGL_ANIM_TYPE_ALPHA;        
        t_begin.pt_path_mode[1].ui2_total_steps = pt_anim_data->ui2_total_steps;
        t_begin.pt_path_mode[1].ui4_start_tick  = 0;
        t_begin.pt_path_mode[1].ui2_frame_interval = pt_anim_data->ui2_frame_interval;
        t_begin.pt_path_mode[1].pf_type_cb      = NULL;
    }
    
    t_begin.ui4_flag                                |= WGL_ANIM_DATA_FLAG_DATA_INF;
    t_begin.pt_anim_data[0].ui2_anim_type           |= WGL_ANIM_TYPE_MOVE;
    t_begin.pt_anim_data[0].u_data.t_move.i2_start_x = pt_anim_data->i2_start_x;
    t_begin.pt_anim_data[0].u_data.t_move.i2_start_y = pt_anim_data->i2_start_y;
    t_begin.pt_anim_data[0].u_data.t_move.i2_end_x   = pt_anim_data->i2_end_x;
    t_begin.pt_anim_data[0].u_data.t_move.i2_end_y   = pt_anim_data->i2_end_y;
    if (2 == t_begin.ui2_count)
    {
        t_begin.pt_anim_data[1].ui2_anim_type |= WGL_ANIM_TYPE_ALPHA;
        t_begin.pt_anim_data[1].u_data.t_alpha.ui1_start_alpha = 255;
        t_begin.pt_anim_data[1].u_data.t_alpha.ui1_end_alpha = 0;
    }

    i4_ret= c_wgl_start_animation(
                         h_widget,
                         &t_begin,
                         ANIM_CONTEXT_APP);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("ERROR: c_wgl_start_animation() failed! i4_ret: %d\n", i4_ret));
    }

    /* Free memory for animation control data */
    if (t_begin.pt_anim_data)
    {
        c_mem_free(t_begin.pt_anim_data);
    }

    if (t_begin.pt_path_mode)
    {
        c_mem_free(t_begin.pt_path_mode);
    }
    
    return i4_ret;
}

INT32 a_wzd_anim_scale(HANDLE_T h_widget, ANIM_DATA_SCALE_T* pt_anim_data, BOOL b_end)
{
    INT32                i4_ret;
    WGL_ANIMATION_DATA_T t_begin;

    if (pt_anim_data == NULL)
    {
        DBG_ERROR(("ERROR: t_anim_data can not be NULL!\n"));
        return WGLR_INV_ARG;
    }
    
    if (b_end)
    {
        i4_ret = c_wgl_end_animation(h_widget, NULL, NULL);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("ERROR: c_wgl_end_animation() failed! i4_ret: %d\n", i4_ret));
            return i4_ret;
        }
    }

    t_begin.ui2_count = 1;
    t_begin.ui4_flag  = 0;
    t_begin.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_begin.ui2_count));
    t_begin.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_begin.ui2_count));
    if((t_begin.pt_anim_data == NULL) || (t_begin.pt_path_mode == NULL))
    {
        DBG_ERROR(("ERROR: Alloc memory failed! File=%s, Line=%d\n", __FILE__, __LINE__));
    }

    c_memset(t_begin.pt_anim_data, 0, sizeof(WGL_ANIM_DATA_INFO));
    c_memset(t_begin.pt_path_mode, 0, sizeof(WGL_ANIM_PATH_DATA_T));

    t_begin.pt_path_mode->ui2_anim_type     |= WGL_ANIM_TYPE_SCALE;
    t_begin.ui4_flag                        |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;
    t_begin.pt_path_mode->ui2_total_steps    = pt_anim_data->ui2_total_steps;
    t_begin.pt_path_mode->ui4_start_tick     = pt_anim_data->ui4_start_tick;
    t_begin.pt_path_mode->ui2_frame_interval = pt_anim_data->ui2_frame_interval;
    t_begin.pt_path_mode->pf_type_cb         = NULL;
    t_begin.pt_path_mode->e_play_mode        = ANIM_PLAY_MODE_ONCE;
    t_begin.pt_path_mode->ui2_loop_count     = 1;
    
    t_begin.ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF;
    t_begin.pt_anim_data->ui2_anim_type |= WGL_ANIM_TYPE_SCALE;
    t_begin.pt_anim_data->u_data.t_scale.ui8_start_w = pt_anim_data->ui8_start_w;
    t_begin.pt_anim_data->u_data.t_scale.ui8_start_h = pt_anim_data->ui8_start_h;
    t_begin.pt_anim_data->u_data.t_scale.ui8_end_w   = pt_anim_data->ui8_end_w;
    t_begin.pt_anim_data->u_data.t_scale.ui8_end_h   = pt_anim_data->ui8_end_h;
    t_begin.pt_anim_data->u_data.t_scale.e_ref_type  = ANIM_STD_REF_CENTER_CENTER;

    i4_ret= c_wgl_start_animation(
                         h_widget,
                         &t_begin,
                         ANIM_CONTEXT_APP);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("ERROR: c_wgl_start_animation() failed! i4_ret: %d\n", i4_ret));
    }
    
    /* Free memory for animation control data */
    if (t_begin.pt_anim_data)
    {
        c_mem_free(t_begin.pt_anim_data);
    }

    if (t_begin.pt_path_mode)
    {
        c_mem_free(t_begin.pt_path_mode);
    }
    
    return i4_ret;
}

INT32 a_wzd_anim_alpha (HANDLE_T h_widget, ANIM_DATA_ALPHA_T* pt_alpha_data, BOOL b_end)
{
    INT32                   i4_ret = WZDR_OK;    
    WGL_ANIMATION_DATA_T    t_anim_data;
    WGL_ANIM_CONTEXT_T      e_wzd_anim_context = ANIM_CONTEXT_APP_SYNC;

    if (pt_alpha_data == NULL)
    {
        DBG_ERROR(("ERROR: t_anim_data can not be NULL!\n"));
        return WGLR_INV_ARG;
    }

    do
    {
        if (b_end)
        {
            i4_ret = c_wgl_end_animation(h_widget, NULL, NULL);
            if (i4_ret != WGLR_OK)
            {
                DBG_ERROR(("ERROR: c_wgl_end_animation() failed! i4_ret: %d\n", i4_ret));
                return i4_ret;
            }
        }

        /* Clear animation data */
        c_memset (&t_anim_data, 0, sizeof (WGL_ANIMATION_DATA_T));

        /* begin animation */
        t_anim_data.ui2_count = 1;

        /* Alloc memory for animation control data */        
        t_anim_data.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_anim_data.ui2_count));
        t_anim_data.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_anim_data.ui2_count));
        if ((NULL == t_anim_data.pt_anim_data) || 
            (NULL == t_anim_data.pt_path_mode))
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        c_memset(t_anim_data.pt_anim_data, 0, sizeof(WGL_ANIM_DATA_INFO));
        c_memset(t_anim_data.pt_path_mode, 0, sizeof(WGL_ANIM_PATH_DATA_T));

        /* Initialize animation path mode */
        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;
        t_anim_data.pt_path_mode->ui2_anim_type |= WGL_ANIM_TYPE_ALPHA;

        t_anim_data.pt_path_mode->ui2_total_steps = pt_alpha_data->ui2_total_steps;
        t_anim_data.pt_path_mode->ui2_frame_interval = pt_alpha_data->ui2_frame_interval;
        t_anim_data.pt_path_mode->ui4_start_tick = 0;
        t_anim_data.pt_path_mode->pf_type_cb = NULL;

        /* Initialize animation data info */        
        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF;
        t_anim_data.pt_anim_data->ui2_anim_type |= WGL_ANIM_TYPE_ALPHA;
        t_anim_data.pt_anim_data->u_data.t_alpha.ui1_start_alpha = pt_alpha_data->ui1_start_alpha;
        t_anim_data.pt_anim_data->u_data.t_alpha.ui1_end_alpha = pt_alpha_data->ui1_end_alpha;

        /* Show animation widget */
        c_wgl_set_visibility(h_widget, WGL_SW_NORMAL);

        /* Set initial alpha firstly */
        c_wgl_set_alpha(h_widget, t_anim_data.pt_anim_data->u_data.t_alpha.ui1_start_alpha);

        /* Start animation */
        i4_ret= c_wgl_start_animation(
                         h_widget,
                         &t_anim_data,
                         e_wzd_anim_context);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

    } while(0);

    /* Free memory for animation control data */
    if (t_anim_data.pt_anim_data)
    {
        c_mem_free(t_anim_data.pt_anim_data);
    }

    if (t_anim_data.pt_path_mode)
    {
        c_mem_free(t_anim_data.pt_path_mode);
    }

    return WZDR_OK;
}

INT32 a_wzd_anim_end(HANDLE_T h_widget)
{
    INT32 i4_ret;
    
    i4_ret = c_wgl_end_animation(h_widget, NULL, NULL);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("ERROR: c_wgl_end_animation() failed! i4_ret: %d\n", i4_ret));
    }
    
    return i4_ret;
}

INT32 a_wzd_anim_set_cb(HANDLE_T                  h_anim_handle,
                        wgl_app_anim_callback_fct pf_anim_nfy_fct,
                        VOID*                     pv_tag)
{
    INT32                   i4_ret;

    if (NULL_HANDLE == h_anim_handle)
    {
        return WGLR_INV_ARG;
    }

    /* Set animation callback */
    i4_ret = c_wgl_set_anim_callback(h_anim_handle,
                                     pf_anim_nfy_fct,
                                     pv_tag);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
        return i4_ret;
    }

    return WGLR_OK;
}
