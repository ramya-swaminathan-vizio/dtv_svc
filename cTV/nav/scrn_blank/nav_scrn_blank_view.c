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
 * $RCSfile: scrn_blank_view.c,v $
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
#include "c_os.h"

#include "nav/scrn_blank/nav_scrn_blank.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define _ENABLE_LOG_                            0
#define IS_SYNC_REPAINT                         TRUE
#define MSG_UPDATE_TIMES                        (UINT8)20

#if _ENABLE_LOG_
#define _USER_DBG_LOG(_stmt)    DBG_INFO (_stmt);
#else
#define _USER_DBG_LOG(_stmt)
#endif
extern INT32 menu_custom_unblank_screen(UINT32 ui4_keycode);
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
SCRN_BLANK_VIEW_T*            pt_scrn_blank_view;

static HANDLE_T         h_old_focus = NULL_HANDLE;
static HANDLE_T         h_msg_timer = NULL_HANDLE;
static UINT8            ui1_sec = MSG_UPDATE_TIMES;
static CHAR             s_g_msg[256] = {0};
static UINT8            b_disable_keyroute = FALSE;
static WGL_FONT_INFO_T t_font_info  = {FE_FNT_SIZE_SMALL,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _scrn_blank_frame_skin(
                    SCRN_BLANK_VIEW_T*            pt_view,
                    APP_COLOR_TYPE_T            e_color_type
                    );
static INT32 _scrn_blank_default_key_hander(HANDLE_T            h_widget,
                                               UINT32              ui4_msg,
                                               VOID*               pv_param1,
                                               VOID*               pv_param2);
static VOID _timer_cb_fct (HANDLE_T pt_tm_handle, VOID* pv_tag);
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      scrn_blank_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 scrn_blank_view_init(
                    SCRN_BLANK_T*                 pt_this,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    INT32            i4_ret;
    GL_RECT_T        t_rect;
    SCRN_BLANK_VIEW_T* pt_view = &pt_this->t_view;
    pt_scrn_blank_view = &pt_this->t_view;

    /* create frame */
    SET_RECT_BY_SIZE(
                    &pt_view->t_orig_rect,
                    i4_frame_x_offset + TWINKLE_MSG_FRAME_LEFT,
                    i4_frame_y_offset + TWINKLE_MSG_FRAME_TOP,
                    TWINKLE_MSG_FRAME_WIDTH,
                    TWINKLE_MSG_FRAME_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    h_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &pt_view->t_orig_rect,
                    _scrn_blank_default_key_hander,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(0),
                    pt_this,
                    &(pt_view->h_frame)
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* create title */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    TWINKLE_MSG_TITLE_LEFT,
                    TWINKLE_MSG_TITLE_TOP,
                    TWINKLE_MSG_TITLE_WIDTH,
                    TWINKLE_MSG_TITLE_HEIGHT
                    );

    i4_ret = c_wgl_create_widget(
                    pt_view->h_frame,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_512
                          | WGL_STL_TEXT_MULTILINE
                          | WGL_STL_TEXT_SMART_CUT
                          ),
                    NULL,
                    &pt_view->h_title
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* background image */
    WGL_HIMG_TPL_T  t_lb_bk_img = NULL_HANDLE;

    i4_ret = nav_img_create_scr_svr_bk_img_tpl(&t_lb_bk_img);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    WGL_IMG_INFO_T  t_img_info ;
    c_memset (&t_img_info, 0, sizeof(t_img_info));

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_lb_bk_img;
    t_img_info.u_img_data.t_standard.t_highlight = t_lb_bk_img;
    t_img_info.u_img_data.t_standard.t_disable   = t_lb_bk_img;

    i4_ret = c_wgl_do_cmd(pt_view->h_title,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _scrn_blank_frame_skin(
                    pt_view,
                    e_color_type
                    );
    if(NAVR_FAIL == i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_show(
                    pt_view->h_frame,
                    WGL_SW_HIDE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    pt_view->b_show = FALSE;

    i4_ret = c_timer_create(&h_msg_timer);

    if(i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      scrn_blank_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 scrn_blank_view_deinit(
                    SCRN_BLANK_VIEW_T*            pt_view
                    )
{
    c_wgl_destroy_widget(pt_view->h_frame);
    c_wgl_destroy_widget(pt_view->h_title);

    if (c_handle_valid(h_msg_timer) == TRUE)
    {
        c_timer_delete(h_msg_timer);
        h_msg_timer = NULL_HANDLE;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      scrn_blank_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 scrn_blank_view_show(
                    SCRN_BLANK_VIEW_T*            pt_view,
                    UTF16_T*                    pw2s_string
                    )
{
    INT32 i4_ret = NAVR_OK;
    pt_scrn_blank_view = pt_view;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_title,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)pw2s_string,
                    (VOID*)c_uc_w2s_strlen(pw2s_string)
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_frame,
                    WGL_SW_RECURSIVE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    c_wgl_get_focus(&h_old_focus);
    c_wgl_set_focus(pt_view->h_frame, WGL_NO_AUTO_REPAINT);

    c_wgl_float(pt_view->h_frame, TRUE, FALSE);

    i4_ret = c_wgl_repaint(
                    pt_view->h_frame,
                    NULL,
                    FALSE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    pt_view->b_show = TRUE;

    /* count down 20s */
    c_uc_w2s_to_ps(pw2s_string, s_g_msg, sizeof(s_g_msg)-1);

    i4_ret = c_timer_start(h_msg_timer,
                            (UINT32)1000,
                            X_TIMER_FLAG_REPEAT,
                            _timer_cb_fct,
                            NULL);
    NAV_LOG_ON_FAIL(i4_ret);

    if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
    {
        a_tv_net_send_cmd("\n:am,am,:disable_keyroute\n");
        b_disable_keyroute = TRUE;
    }

    a_tv_net_OSD_appear();

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      scrn_blank_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 scrn_blank_view_hide(
                    SCRN_BLANK_VIEW_T*            pt_view
                    )
{
    INT32 i4_ret;

    i4_ret = c_timer_stop(h_msg_timer);
    NAV_LOG_ON_FAIL(i4_ret);

    c_wgl_float(pt_view->h_frame, FALSE, FALSE);

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_frame,
                    WGL_SW_HIDE_RECURSIVE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(
                    pt_view->h_frame,
                    NULL,
                    FALSE
                    );

    pt_view->b_show = FALSE;
    ui1_sec = MSG_UPDATE_TIMES;

    if (b_disable_keyroute)
    {
        a_tv_net_send_cmd("\n:am,am,:enable_keyroute\n");
    }

    a_tv_net_OSD_disapper();

    if (h_old_focus != NULL_HANDLE)
    {
        c_wgl_set_focus(h_old_focus, WGL_NO_AUTO_REPAINT);
        h_old_focus = NULL_HANDLE;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_frame_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _scrn_blank_frame_skin(
                    SCRN_BLANK_VIEW_T*            pt_view,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    WGL_COLOR_INFO_T t_clr_info;
    INT32            i4_ret;

    /* set title color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = TWINKLE_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = TWINKLE_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = TWINKLE_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = DEFAULT_FG_ALPHA;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_title,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set title font */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_title,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_font_info,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set title align*/
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_title,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _scrn_blank_default_key_hander
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _scrn_blank_default_key_hander(HANDLE_T            h_widget,
                                               UINT32              ui4_msg,
                                               VOID*               pv_param1,
                                               VOID*               pv_param2)
{
    INT32           i4_ret = NAVR_OK;
    UINT32          ui4_key_code = (UINT32)pv_param1;

    _USER_DBG_LOG(("%s(): ui4_msg = 0x%x, key_code = 0x%x\n",
                                            __FUNCTION__,
                                            ui4_msg,
                                            (UINT32)pv_param1));

    if (pt_scrn_blank_view->b_show)
    {
        switch (ui4_msg)
        {
            case WGL_MSG_KEY_DOWN:
            {
                if(ui4_key_code != BTN_VOL_UP
                    && ui4_key_code != BTN_VOL_DOWN
                    && ui4_key_code != BTN_MUTE)
                {
                    if(NAV_SCRN_BLANK_STATE_BLANK == a_scrn_blank_get_state())
                    {
                        /*hide ui*/
                        nav_hide_component(NAV_COMP_ID_SCRN_BLANK);
                        menu_custom_unblank_screen(ui4_key_code);
                        return NAVR_OK;
                    }
                    else if (NAV_SCRN_BLANK_STATE_TIMER_PHASE1 == a_scrn_blank_get_state()
                            || NAV_SCRN_BLANK_STATE_TIMER_PHASE2 == a_scrn_blank_get_state())
                    {
                        a_scrn_blank_reset();
                    }
                    else
                    {
                        //Do nothing
                    }
                }
                else
                {
                    if(NAV_SCRN_BLANK_STATE_BLANK == a_scrn_blank_get_state())
                    {
                        a_amb_default_key_handler_ex(ui4_msg, pv_param1, pv_param2);
                        return NAVR_OK;
                    }
                }
                break;
            }
            default:
                break;
        }
        return i4_ret;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

VOID _timer_nfy_fct(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3)
{
    INT32 i4_ret = NAVR_OK;

    CHAR *ps_tmp = NULL;
    CHAR s_sec[3] = {0};
static UTF16_T w2s_msg[256] = {0};

    s_sec[0] = (ui1_sec/10 == 0) ? ' ' : (ui1_sec/10 + '0');
    s_sec[1] = ui1_sec%10 + '0';

    if (0 != ui1_sec)
    {
        ui1_sec--;
        ps_tmp = c_strstr(s_g_msg, s_sec);

        if (ps_tmp != NULL)
        {
            ps_tmp[0] = (ui1_sec/10 == 0) ? ' ' : (ui1_sec/10 + '0');
            ps_tmp[1] = ui1_sec%10 + '0';

            c_memset(w2s_msg, 0, sizeof(w2s_msg));
            c_uc_ps_to_w2s(s_g_msg, w2s_msg, 255);

            i4_ret = c_wgl_do_cmd(pt_scrn_blank_view->h_title,
                                    WGL_CMD_TEXT_SET_TEXT,
                                    (VOID*)w2s_msg,
                                    (VOID*)c_uc_w2s_strlen(w2s_msg));
            NAV_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_repaint(pt_scrn_blank_view->h_title, NULL, FALSE);
            NAV_LOG_ON_FAIL(i4_ret);
        }

        if (0 == ui1_sec)
        {
            i4_ret = c_wgl_set_visibility(pt_scrn_blank_view->h_frame, WGL_SW_HIDE_RECURSIVE);
            NAV_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_repaint(pt_scrn_blank_view->h_frame, NULL, FALSE);
            NAV_LOG_ON_FAIL(i4_ret);
        }
    }
    else
    {
        i4_ret = c_timer_stop(h_msg_timer);
        NAV_LOG_ON_FAIL(i4_ret);
    }

}

VOID _timer_cb_fct (HANDLE_T pt_tm_handle, VOID* pv_tag)
{
    nav_request_context_switch(_timer_nfy_fct,
                                NULL,
                                NULL,
                                NULL);
}

