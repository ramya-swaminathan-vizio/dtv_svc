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
 * $RCSfile: eas_view.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This file contains functions and internal variables for EAS view.
 *
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
                    include files
----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_sets.h"
#include "u_wgl_bdr_common.h"
#include "u_irrc_btn_def.h"

#include "c_gl.h"
#include "c_handle.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"

#include "eas/u_eas.h"
#include "eas/eas.h"
#include "res/eas/eas_cfg.h"
#include "res/eas/eas_view.h"

#ifdef APP_COLOR_MODE_PALLET
    GL_COLOR_T COLOR_WHITE  = { 255, {   0 }, {   0 }, {  64 }};
    GL_COLOR_T COLOR_BLUE   = { 255, {   0 }, {   0 }, { 171 }};
#else
    GL_COLOR_T COLOR_WHITE  = { 255, { 255 }, { 255 }, { 255 }};
    GL_COLOR_T COLOR_BLUE   = { 220, {  40 }, {  40 }, {  80 }};
#endif /* APP_COLOR_MODE_PALLET */    

WGL_FONT_INFO_T EAS_FONT_DEFAULT =
                {   FE_FNT_SIZE_SMALL,
                    FE_FNT_STYLE_BOLD,
                    FE_CMAP_ENC_UNICODE,
                    SN_FONT_DEFAULT_BIG    };
/*---------------------------------------------------------------------------
                    typedefs
----------------------------------------------------------------------------*/
typedef struct _EAS_VIEW_T
{
    HANDLE_T             h_frame;        /* Parent frame. */

    BOOL                 b_on;           /* Indicate if the view is being on. */

}   EAS_VIEW_T;

/*---------------------------------------------------------------------------
                    data declarations
----------------------------------------------------------------------------*/
static EAS_VIEW_T  t_g_view;

/*---------------------------------------------------------------------------
                    private function implementations
----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:  eas_view_init
 *
 * Description: This API inits the view of EAS.
 *
 * Inputs:
 *   h_canvas             Canvas handle.
 *   i4_x_offset          X offset.
 *   i4_y_offset          Y offset.
 *
 * Outputs:
 *   ph_frame             Handle to parent frame.
 *
 * Returns:
 *   EASR_OK              Successful.
 *   EASR_FAIL            Init failed.
 ----------------------------------------------------------------------------*/
INT32 eas_view_init(
    HANDLE_T             h_canvas,
    HANDLE_T*            ph_frame
)
{
    INT32                i4_rc;
    GL_RECT_T            t_rect;
    UINT32               ui4_canvas_width;
    UINT32               ui4_canvas_height;
    INT32                i4_x_offset;
    INT32                i4_y_offset;

    /* Get the sizes of the canvas. */
    i4_rc = c_wgl_get_canvas_size (h_canvas,
                                   & ui4_canvas_width,
                                   & ui4_canvas_height);

    if (i4_rc != WGLR_OK)
    {
        return EASR_FAIL;
    }

    /* Calculate offsets. */
    i4_x_offset = (INT32) ((ui4_canvas_width  - EAS_CANVAS_WIDTH)  / 2);
    i4_y_offset = (INT32) ((ui4_canvas_height - EAS_CANVAS_HEIGHT) / 2);

    /*
       Create parent(root) frame.
    */
    SET_RECT_BY_SIZE (& t_rect,
                      EAS_FRAME_X + i4_x_offset,
                      EAS_FRAME_Y + i4_y_offset,
                      EAS_FRAME_W,
                      EAS_FRAME_H);

    i4_rc = c_wgl_create_widget (h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 & t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI | WGL_STL_GL_NO_BK),
                                 NULL,
                                 & t_g_view.h_frame);

    if (i4_rc != WGLR_OK)
    {
        return EASR_FAIL;
    }

    /* Copy handle. */
    *ph_frame = t_g_view.h_frame;

    /* Turn off flag. */
    t_g_view.b_on = FALSE;

    return EASR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:  eas_view_destroy
 *
 * Description: This API destroys the view of EAS.
 *
 * Inputs:
 *   None.
 *
 * Outputs:
 *   None.
 *
 * Returns:
 *   EASR_OK              Successful.
 *   EASR_FAIL            Init failed.
 ----------------------------------------------------------------------------*/
INT32 eas_view_destroy(
    VOID
)
{
    c_wgl_destroy_widget (t_g_view.h_frame);

    return EASR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:  eas_view_show
 *
 * Description: This API shows the view of EAS.
 *
 * Inputs:
 *   pt_eas_event         Eas event data.
 *
 * Outputs:
 *   None.
 *
 * Returns:
 *   EASR_OK              Successful.
 *   EASR_FAIL            Init failed.
 ----------------------------------------------------------------------------*/
INT32 eas_view_show(
    EAS_EVENT_T*    pt_eas_event
)
{
    INT32               i4_rc;

    /* Set visibilities. */
    i4_rc = c_wgl_set_visibility (t_g_view.h_frame,
                                  WGL_SW_RECURSIVE);

    if (i4_rc != WGLR_OK)
    {
        DBG_ERROR(("<EAS> show eas view call c_wgl_set_visibility failed.r4_rc=%d,line=%d,fct=%s,file=%s \n",
                   i4_rc,__LINE__,__FUNCTION__,__FILE__));
        return EASR_FAIL;
    }

    /* Repaint frame. */
    i4_rc = c_wgl_repaint (t_g_view.h_frame,
                           NULL,
                           TRUE);

    if (i4_rc != WGLR_OK)
    {
        DBG_ERROR(("<EAS> show eas view call c_wgl_repaint failed.r4_rc=%d,line=%d,fct=%s,file=%s \n",
                   i4_rc,__LINE__,__FUNCTION__,__FILE__));        
        return EASR_FAIL;
    }

    /* Turn on flag. */
    t_g_view.b_on = TRUE;

    return EASR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:  eas_view_hide
 *
 * Description: This API hides the view of EAS.
 *
 * Inputs:
 *   None
 *
 * Outputs:
 *   None
 *
 * Returns:
 *   EASR_OK              Successful.
 *   EASR_FAIL            Init failed.
 ----------------------------------------------------------------------------*/
INT32 eas_view_hide(
    VOID
)
{
    INT32               i4_rc;

    /* Set visibilities. */
    i4_rc = c_wgl_set_visibility (t_g_view.h_frame,
                                  WGL_SW_HIDE);

    if (i4_rc != WGLR_OK)
    {
        return EASR_FAIL;
    }

    /* Repaint frame. */
    i4_rc = c_wgl_repaint (t_g_view.h_frame,
                           NULL,
                           TRUE);

    if (i4_rc != WGLR_OK)
    {
        return EASR_FAIL;
    }

    /* Turn off flag. */
    t_g_view.b_on = FALSE;

    return EASR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:  eas_view_hide
 *
 * Description: This API hides the view of EAS.
 *
 * Inputs:
 *   None
 *
 * Outputs:
 *   None
 *
 * Returns:
 *   EASR_OK              Successful.
 *   EASR_FAIL            Init failed.
 ----------------------------------------------------------------------------*/
INT32 eas_view_process_msg(
    UINT32              ui4_msg_code,
    const VOID*         pv_data,
    SIZE_T              z_data_len
)
{
    if (ui4_msg_code == EAS_MSG_CODE_IOM_NFY)
    {
        switch ( *((UINT32*) pv_data) )
        {
            case EAS_TERMINATION_BTN: /* The button to terminate EAS. */
            {
                /* Delete the tktp widget and don't wait for
                   text to be scrolled at least one,
                   and restore to user state immediately.
                */
                if (t_g_view.b_on)
                {
                    eas_restore_user_state (FALSE);
                }
            }
            break;

            default:
                break;
        }
    }

    return EASR_OK;
}
