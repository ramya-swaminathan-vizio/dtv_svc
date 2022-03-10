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
 * $RCSfile: pic_mode_view_dialog.c,v $
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
#include "res/nav/pic_mode/pic_mode_view_dialog_custom.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)

typedef struct _NAV_PIC_MODE_VIEW_T
{
    /* Internal Control */

    NAV_PIC_MODE_T*             pt_ctrl;

    /* Widgets */

    HANDLE_T                    h_frame;
    HANDLE_T                    h_txt_msg;

    /* Widgets Resource: Template image */

    WGL_HIMG_TPL_T              h_img_bk;

} NAV_PIC_MODE_VIEW_T;

#ifndef MAX_TXT_MSG_NUM
#define MAX_TXT_MSG_NUM                  8
#endif
#ifndef MAX_TXT_MSG_CHAR
#define MAX_TXT_MSG_CHAR                 16
#endif

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_PIC_MODE_VIEW_T t_g_nav_pic_mode_view       = {0};
static UTF16_T*            apw2s_txt_msg[MAX_TXT_MSG_NUM];

static UINT16              ui2_g_hlt_index = 0;
static UINT16              ui2_g_elem_num = 0;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

static INT32 _nav_pic_mode_view_frame_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );

static INT32  __pic_mode_load_skin(VOID);

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
static INT32 __pic_mode_create_image(VOID)
{
    INT32    i4_ret;
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;

    /* dialog background image */
    i4_ret = nav_pic_mode_custom_view_dialog_create_image(&pt_view->h_img_bk);

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
                     PIC_MODE_FRAME_LEFT + i4_frame_x_offset,
                     PIC_MODE_FRAME_TOP  + i4_frame_y_offset,
                     PIC_MODE_FRAME_WIDTH,
                     PIC_MODE_FRAME_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _nav_pic_mode_view_frame_wdgt_proc_fct,
                                 DEFAULT_BK_ALPHA,
                                 NULL,
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
static INT32 __pic_mode_create_txt(HANDLE_T                       h_parent)
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;
    GL_RECT_T                           t_rect;
    INT32                               i4_ret;
    WGL_TEXT_KEY_MAP_T                  t_key_map;

    /* create message text */

    SET_RECT_BY_SIZE (& t_rect,
                      PIC_MODE_MSG_LEFT,
                      PIC_MODE_MSG_TOP,
                      PIC_MODE_MSG_WIDTH,
                      PIC_MODE_MSG_HEIGHT);

    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  NULL,
                                  DEFAULT_BK_ALPHA,
                                  (VOID*)(WGL_STL_TEXT_MAX_32
                                        | WGL_STL_TEXT_SMART_CUT
                                        | WGL_STL_GL_NO_IMG_UI
                                        | WGL_STL_GL_NO_BK),
                                  NULL,
                                  & pt_view->h_txt_msg);

    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_create_widget(HT_WGL_WIDGET_FRAME) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* Clear key map. */
    t_key_map.ui4_line_up   = 0;
    t_key_map.ui4_line_down = 0;
    t_key_map.ui4_page_up   = 0;
    t_key_map.ui4_page_down = 0;

    i4_ret = c_wgl_do_cmd (pt_view->h_txt_msg,
                           WGL_CMD_TEXT_SET_KEY_MAP,
                           WGL_PACK (& t_key_map),
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
 * Description: alloc text buffer for apw2s_txt_msg
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  __pic_mode_alloc_text(VOID)
{
    UINT8           ui1_idx;

    for(ui1_idx = 0 ; ui1_idx < MAX_TXT_MSG_NUM ; ui1_idx++)
    {
        apw2s_txt_msg[ui1_idx] = c_mem_alloc(MAX_TXT_MSG_CHAR * sizeof(UTF16_T));

        if(apw2s_txt_msg[ui1_idx] == NULL)
        {
            DBG_ERROR(("[NAV] pic_mode_alloc_text fail. \n"));
            return NAVR_FAIL;
        }

        /* Clear the content first */
        c_memset(apw2s_txt_msg[ui1_idx], 0, MAX_TXT_MSG_CHAR * sizeof(UTF16_T));
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: update current text (by highlight index) to widget
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  __pic_mode_update_text(VOID)
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;
    INT32           i4_ret;
    SIZE_T          z_len;

    if (ui2_g_hlt_index >= MAX_TXT_MSG_NUM)
    {
        return NAVR_FAIL;
    }
    z_len       = c_uc_w2s_strlen( (UTF16_T *) apw2s_txt_msg[ui2_g_hlt_index]);

    i4_ret = c_wgl_do_cmd (pt_view->h_txt_msg,
                           WGL_CMD_TEXT_SET_TEXT,
                           (VOID*)apw2s_txt_msg[ui2_g_hlt_index],
                           (VOID*)(z_len));

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

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
 * Description: set skin / bk images
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  __pic_mode_load_skin(VOID)
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;
    WGL_COLOR_INFO_T                         t_clr_info;
    WGL_IMG_INFO_T                           t_img_info;
    INT32                                    i4_ret;

    /* Frame's background */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_view->h_img_bk;
    t_img_info.u_img_data.t_standard.t_highlight = pt_view->h_img_bk;
    t_img_info.u_img_data.t_standard.t_disable   = pt_view->h_img_bk;

    i4_ret = c_wgl_do_cmd (pt_view->h_frame,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));

    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* TXT msg's FG color */

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = t_g_nav_pic_mode_color_txt_msg_fg;
    t_clr_info.u_color_data.t_standard.t_enable      = t_g_nav_pic_mode_color_txt_msg_fg;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_g_nav_pic_mode_color_txt_msg_fg;

    i4_ret = c_wgl_do_cmd (pt_view->h_txt_msg,
                           WGL_CMD_GL_SET_COLOR,
                           (VOID*)WGL_CLR_TEXT,
                           &t_clr_info);

    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* TXT msg's font */
    i4_ret = c_wgl_do_cmd (pt_view->h_txt_msg,
                           WGL_CMD_GL_SET_FONT,
                           (VOID*)&t_g_pic_mode_txt_msg_font_info,
                           NULL);

    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* TXT msg's alignment  */
    i4_ret = c_wgl_do_cmd (pt_view->h_txt_msg,
                           WGL_CMD_TEXT_SET_ALIGN,
                           (VOID*)NAV_PIC_MODE_TXT_MSG_ALIGNMENT,
                           NULL);

    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
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
    switch (ui4_key_code) {
    case BTN_P_EFFECT:
        return TRUE;
    default:
        return FALSE;
    }
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

    /* Let's focus on the frame */
    i4_ret = c_wgl_set_focus(pt_view->h_frame, WGL_NO_AUTO_REPAINT);
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
        nav_pic_mode_reset_timer(pt_view->pt_ctrl);
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
static INT32 _nav_pic_mode_view_frame_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32 i4_ret;
    BOOL  b_processed;

    /* To be implemented */

    /* Can be customized */
    /* The listbox wdgt proc fct */
    i4_ret = nav_pic_mode_custom_view_dialog_frame_wdgt_proc_fct(h_widget,
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
        _nav_pic_mode_view_rcu_key_handler((UINT32)pv_param1);
        break;

    default:
        break;
    }

    /* Run specified key handler next */

    switch(ui4_msg) {
    case WGL_MSG_KEY_DOWN:
        {
            UINT32    ui4_key_code = (UINT32) pv_param1;

            if(ui4_key_code == BTN_P_EFFECT)
            {
                /* Toggle the highlight index */
                ui2_g_hlt_index = (UINT16) ((ui2_g_hlt_index+1)%ui2_g_elem_num);

                /* Call the Ctrl's API */
                nav_pic_mode_ctrl_set_index(ui2_g_hlt_index);

                /* Update to widget */
                __pic_mode_update_text();

                /* Repaint the widget */
                __pic_mode_repaint();

            }

        }
        break;

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
    INT32                i4_ret;

    /* Save the ctrl to view */
    pt_view->pt_ctrl = pt_ctrl;

    /* create image */
    __pic_mode_create_image();

    /* create frame */
    __pic_mode_create_frame(h_canvas,
                            i4_frame_x_offset,
                            i4_frame_y_offset);
    /* create txt_msg */
    __pic_mode_create_txt(pt_view->h_frame);

    /* load skin for frame/txt msg */

    __pic_mode_load_skin();

    /* alloc space for ui2_elem_num */
    __pic_mode_alloc_text();

    /* Set the highlight index = 0 */
    ui2_g_hlt_index = 0;

    /* Keep the element numbers */

    ui2_g_elem_num = ui2_elem_num;

    /* Update text to widget */
    __pic_mode_update_text();

    i4_ret = c_wgl_show(pt_view->h_frame, WGL_SW_HIDE);
    NAV_PIC_MODE_LOG_ON_FAIL(i4_ret);

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
    c_wgl_destroy_widget(pt_view->h_txt_msg);
    c_wgl_img_tpl_destroy(pt_view->h_img_bk);

    pt_view->pt_ctrl     = NULL;
    pt_view->h_frame     = NULL_HANDLE;
    pt_view->h_txt_msg   = NULL_HANDLE;
    pt_view->h_img_bk    = NULL_HANDLE;

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
    ui2_g_hlt_index = ui2_idx;

    /* Update the text to widget by current index */
    __pic_mode_update_text();

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
    c_uc_w2s_strcpy( (UTF16_T *) apw2s_txt_msg[ui2_idx], pw2s_text);

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
    /* not needed */

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
    /* no title text capability */

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
INT32 nav_pic_mode_view_register_dialog_hdlr(
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
