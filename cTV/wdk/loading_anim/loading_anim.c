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
 * $RCSfile: menu_animation.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/23 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 47aa641dbb1c0b2b64f3264199a32d61 $
 *
 * Description:
 *      This file contains the implementation of GUI-related functions of the
 * menu application
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                  include files
-----------------------------------------------------------------------------*/

#include "u_wgl_common.h"
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
#include "c_fe.h"

#include "app_util/a_common.h"
#include "app_util/a_tv.h"

#include "menu2/menu_animation.h"

#include "res/menu2/menu_custom.h"
#include "res/wdk/wdk_img.h"

/*-----------------------------------------------------------------------------
                          Customizable macros
 ----------------------------------------------------------------------------*/
#define UI_ANIMATION_RATIO 4/3  //please don't add "()"

#ifndef ICON_LABEL_X
    #define ICON_LABEL_X            0
    #define ICON_LABEL_Y            0
    #define ICON_LABEL_W            (33 * UI_ANIMATION_RATIO)
    #define ICON_LABEL_H            (33 * UI_ANIMATION_RATIO)
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef struct _LOADING_ANIM_DATA_T
{
    UINT16                  ui2_loading_anim_steps;
    UINT16                  ui2_loading_anim_frame_interval; /* how many loop steps for animation */

    WGL_ANIMATION_DATA_T    t_anim_data;
} LOADING_ANIM_DATA_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

static LOADING_ANIM_DATA_T    t_g_loading_anim_data;
static WGL_HIMG_TPL_T         at_loading_anim_imgs_seq[12];
static WGL_ANIM_IMG_SEQ_T     t_g_img_seq;
BOOL                          b_g_init = FALSE;
BOOL                          b_g_is_sync;
/*-----------------------------------------------------------------------------
                    function implementations
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: loading_anim_createnim_init
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
INT32 loading_anim_create(HANDLE_T      h_parent,
                          HANDLE_T*     ph_anim_handle)
{
    INT32                       i4_ret;
    LOADING_ANIM_DATA_T*        pt_anim = &t_g_loading_anim_data;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;
    UINT32                      ui4_style = 0;

    c_memset(pt_anim, 0, sizeof(LOADING_ANIM_DATA_T));

    pt_anim->ui2_loading_anim_steps= t_g_img_seq.ui2_len;
    pt_anim->ui2_loading_anim_frame_interval= (UINT16)(10 * (UINT16)c_wgl_get_tick_interval());

    do
    {
        SET_RECT_BY_SIZE (&t_rect,
                          ICON_LABEL_X,
                          ICON_LABEL_Y,
                          ICON_LABEL_W,
                          ICON_LABEL_H);

        /* create widget */
        i4_ret = c_wgl_create_widget (h_parent,
                                      HT_WGL_WIDGET_ICON,
                                      WGL_CONTENT_ICON_DEF,
                                      WGL_BORDER_NULL,
                                      & t_rect,
                                      NULL,
                                      255,
                                      (VOID*)ui4_style,
                                      NULL,
                                      ph_anim_handle);

        /* set icon image*/
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_wdk_img_loading_icon_1;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_wdk_img_loading_icon_1;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_wdk_img_loading_icon_1;

        i4_ret = c_wgl_do_cmd (*ph_anim_handle,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK (WGL_IMG_FG),  /* foreground image */
                               WGL_PACK(&t_img_info));

            /* set icon alignment */
        i4_ret = c_wgl_do_cmd (*ph_anim_handle,
                               WGL_CMD_ICON_SET_ALIGN,
                               WGL_PACK(WGL_AS_CENTER_CENTER),
                               WGL_PACK(NULL));

        /* set visibility */
        c_wgl_set_visibility(*ph_anim_handle, WGL_SW_HIDE);

        /* Set maximum animation image set number, It must be set before setting image sequence information */
        /* and the number can not change after it set */
        i4_ret = c_wgl_set_animation_max_img_set(*ph_anim_handle, 1);
        if (WGLR_OK != i4_ret)
        {
            break;
        }

    }while(0);

    if(i4_ret != WGLR_OK)
    {
        /* Destroy menu animation data */
    }

    return WGLR_OK;
}

INT32 loading_anim_destroy(HANDLE_T         h_anim_handle)
{
    c_wgl_destroy_widget(h_anim_handle);

    h_anim_handle = NULL_HANDLE;

    return WGLR_OK;
}
/*----------------------------------------------------------------------------
 * Name: loading_anim_init
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
INT32 loading_anim_init(VOID)
{
    /* Check init flag */
    if (FALSE == b_g_init)
    {
        /* Reset memory firstly */
        c_memset(at_loading_anim_imgs_seq, 0, sizeof(at_loading_anim_imgs_seq));

        /* Init default image sequence */
        at_loading_anim_imgs_seq[0]  = h_g_wdk_img_loading_icon_1;
        at_loading_anim_imgs_seq[1]  = h_g_wdk_img_loading_icon_2;
        at_loading_anim_imgs_seq[2]  = h_g_wdk_img_loading_icon_3;
        at_loading_anim_imgs_seq[3]  = h_g_wdk_img_loading_icon_4;
        at_loading_anim_imgs_seq[4]  = h_g_wdk_img_loading_icon_5;
        at_loading_anim_imgs_seq[5]  = h_g_wdk_img_loading_icon_6;
        at_loading_anim_imgs_seq[6]  = h_g_wdk_img_loading_icon_7;
        at_loading_anim_imgs_seq[7]  = h_g_wdk_img_loading_icon_8;
        at_loading_anim_imgs_seq[8]  = h_g_wdk_img_loading_icon_9;
        at_loading_anim_imgs_seq[9]  = h_g_wdk_img_loading_icon_10;
        at_loading_anim_imgs_seq[10] = h_g_wdk_img_loading_icon_11;
        at_loading_anim_imgs_seq[11] = h_g_wdk_img_loading_icon_12;

        /* Set init flag */
        b_g_init = TRUE;
    }
    else
    {
    }

    c_memset(&t_g_img_seq, 0, sizeof(WGL_ANIM_IMG_SEQ_T));

    /* Get image sequence from custom part */
    t_g_img_seq.ui2_len = 12;
    t_g_img_seq.pt_img_tpl = at_loading_anim_imgs_seq;

    return WGLR_OK;

}

/*----------------------------------------------------------------------------
 * Name: loading_anim_set_cb
 *
 * Description: this API must be called before animation start
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 loading_anim_set_cb(HANDLE_T                  h_anim_handle,
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
        DBG_INFO (("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
        return i4_ret;
    }
    return WGLR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: loading_anim_stop_animation
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 loading_anim_stop_animation(HANDLE_T      h_anim_handle)
{
    INT32                   i4_ret;
    LOADING_ANIM_DATA_T*    pt_anim = &t_g_loading_anim_data;

    if (TRUE == b_g_is_sync)
    {
        if (pt_anim->t_anim_data.pt_anim_data)
        {
            c_mem_free(pt_anim->t_anim_data.pt_anim_data);
            pt_anim->t_anim_data.pt_anim_data = NULL;
        }

        if (pt_anim->t_anim_data.pt_path_mode)
        {
            c_mem_free(pt_anim->t_anim_data.pt_path_mode);
            pt_anim->t_anim_data.pt_path_mode = NULL;
        }

    }

    else
    {
        if (NULL_HANDLE == h_anim_handle)
        {
            return WGLR_INV_ARG;
        }

        i4_ret = c_wgl_end_animation (h_anim_handle, NULL, NULL);

        if (i4_ret != WGLR_OK)
        {
            DBG_INFO (("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
        }
        if (pt_anim->t_anim_data.pt_anim_data)
        {
            c_mem_free(pt_anim->t_anim_data.pt_anim_data);
            pt_anim->t_anim_data.pt_anim_data = NULL;
        }

        if (pt_anim->t_anim_data.pt_path_mode)
        {
            c_mem_free(pt_anim->t_anim_data.pt_path_mode);
            pt_anim->t_anim_data.pt_path_mode = NULL;
        }
    }

    i4_ret = c_wgl_float(h_anim_handle, FALSE, WGL_NO_AUTO_REPAINT);
    if (i4_ret != WGLR_OK)
    {
        DBG_INFO(("\nFloat animation widget : fail\r\n"));
    }

    /* Hide animation widget */
    i4_ret = c_wgl_set_visibility(h_anim_handle, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK)
    {
        DBG_INFO(("\nHide animation widget : fail\r\n"));
    }

    return WGLR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: loading_anim_start_animation
 * Description:
 * Inputs: - ui2_count: animation loog count;
             b_is_syunc: if this animation is ANIM_CONTEXT_APP_SYNC;
             pf_anim_nfy_fct: animation callback function, can be NULL;
             pv_tag:  private data set by user and this data will return to user through pf_anim_nfy_fct calling,
                      can be NULL.

 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 loading_anim_start_animation(HANDLE_T     h_anim_handle,
                                   UINT16       ui2_count,
                                   BOOL         b_is_sync)
{
    INT32                   i4_ret = WGLR_OK;
    LOADING_ANIM_DATA_T*    pt_anim = &t_g_loading_anim_data;
    WGL_ANIM_CONTEXT_T      e_menu_anim_context;

    if (TRUE==b_is_sync)
    {
        e_menu_anim_context = ANIM_CONTEXT_APP_SYNC;
    }
    else
    {
        e_menu_anim_context = ANIM_CONTEXT_APP;
    }
    b_g_is_sync = b_is_sync;

    /* Clear animation data */
    c_memset (&pt_anim->t_anim_data, 0, sizeof (WGL_ANIMATION_DATA_T));

    if (NULL_HANDLE == h_anim_handle)
    {
        return WGLR_INV_ARG;
    }
    /* Set image sequence */
    i4_ret = c_wgl_set_animation_img_set (h_anim_handle, 0, &t_g_img_seq);
    if (i4_ret != WGLR_OK)
    {
        DBG_INFO (("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
    }

    do
    {
        /* Stop origional animation firstly */
        i4_ret = c_wgl_end_animation (h_anim_handle, NULL, NULL);
        if (i4_ret != WGLR_OK)
        {
            DBG_INFO (("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
        }



        /* begin animation */
        pt_anim->t_anim_data.ui2_count = 1;

        /* Alloc memory for animation control data */
        pt_anim->t_anim_data.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * pt_anim->t_anim_data.ui2_count));
        pt_anim->t_anim_data.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * pt_anim->t_anim_data.ui2_count));
        if((NULL == pt_anim->t_anim_data.pt_anim_data) ||
           (NULL == pt_anim->t_anim_data.pt_path_mode))
        {
            DBG_INFO (("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        c_memset(pt_anim->t_anim_data.pt_anim_data, 0, sizeof(WGL_ANIM_DATA_INFO) * pt_anim->t_anim_data.ui2_count);
        c_memset(pt_anim->t_anim_data.pt_path_mode, 0, sizeof(WGL_ANIM_PATH_DATA_T) * pt_anim->t_anim_data.ui2_count);

        /* Initialize animation path mode */
        pt_anim->t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_PATH_MODE_INF;

        /* Image animation path mode */
        pt_anim->t_anim_data.pt_path_mode->ui2_anim_type |= WGL_ANIM_TYPE_IMG;
        pt_anim->t_anim_data.pt_path_mode->ui2_total_steps = pt_anim->ui2_loading_anim_steps;
        pt_anim->t_anim_data.pt_path_mode->ui2_frame_interval = pt_anim->ui2_loading_anim_frame_interval;
        pt_anim->t_anim_data.pt_path_mode->ui4_start_tick = 0;
        pt_anim->t_anim_data.pt_path_mode->e_play_mode = ANIM_PLAY_MODE_LOOP;
        pt_anim->t_anim_data.pt_path_mode->ui2_loop_count = ui2_count;
        pt_anim->t_anim_data.pt_path_mode->pf_type_cb = NULL;

        /* Initialize animation data info */
        pt_anim->t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF;

        /* Image animation data */
        pt_anim->t_anim_data.pt_anim_data->ui2_anim_type |= WGL_ANIM_TYPE_IMG;
        pt_anim->t_anim_data.pt_anim_data->u_data.t_img.ui1_img_seq_id = 0;
        pt_anim->t_anim_data.pt_anim_data->u_data.t_img.pt_cust_info = NULL;
        pt_anim->t_anim_data.pt_anim_data->u_data.t_img.ui2_cust_len= 0;

        i4_ret = c_wgl_float(h_anim_handle, TRUE, WGL_NO_AUTO_REPAINT);
        if (i4_ret != WGLR_OK)
        {
            DBG_INFO(("\nFloat animation widget : fail\r\n"));
            break;
        }

        /* Start animation */
        i4_ret= c_wgl_start_animation(h_anim_handle,
                                      &pt_anim->t_anim_data,
                                      e_menu_anim_context);
        if (i4_ret != WGLR_OK)
        {
            DBG_INFO (("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        /* Show animation widget */
        i4_ret = c_wgl_set_visibility(h_anim_handle, WGL_SW_NORMAL);
    } while(0);

    return WGLR_OK;
}

/*----------------------------------------------------------------------------
 * Name: loading_anim_deinit
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
INT32 loading_anim_deinit(VOID)
{
    return WGLR_OK;
}
