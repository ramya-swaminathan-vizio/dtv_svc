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
 * $RCSfile: nav_zoom_view.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Zoom mode is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_ZOOM_MODE_SUPPORT


#include "c_gl.h"
#include "c_wgl.h"

#include "c_handle.h"


#include "res/app_util/a_custom_log.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_mlm.h"

#include "res/nav/zoom/nav_zoom_indicate_img.h"
#include "nav/zoom/nav_zoom_view.h"
#include "nav/zoom/a_nav_zoom.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#ifdef APP_2K12_RETAIL_DEMO_MODE
#include "nav/retail_mode/a_nav_retail_mode.h"
#endif
#include "c_pcl.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "nav/usb_pld/nav_usb_pld_view.h"
#include "res/menu2/menu_custom_dialog.h"
#include "wdk/widget/wdk_widget.h"
#include "res/revolt/revolt_settings_mlm.h"
#include "nav/revolt_info/revolt_info.h"
#include "res/nav/nav_dbg.h"
#include "app_util/toast_widget/toast.h"
#include "res/nav/zoom/system_notification.i"
#include "res/menu2/menu_mlm.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
ZOOM_INDICATE_T   indicate_view      = {0};

#define SECTOR_FRAME_W     (indicate_view.ui4_canvas_width)
#define SECTOR_FRAME_H     (indicate_view.ui4_canvas_height)
#define SECTOR_FRAME_X     (0)
#define SECTOR_FRAME_Y     (0)
#define SECTOR_ICON_W      (64)
#define SECTOR_ICON_H      (36)
#define SECTOR_ICON_X      (indicate_view.ui4_canvas_width - SECTOR_ICON_W - 16)//-404
#define SECTOR_ICON_Y      (16)//+72
#define HILITE_FRAME_W     (indicate_view.ui4_canvas_width)
#define HILITE_FRAME_H     (indicate_view.ui4_canvas_height)
#define HILITE_FRAME_X     SECTOR_ICON_X//(0)
#define HILITE_FRAME_Y     SECTOR_ICON_Y//(0)
#define HILITE_ICON_W      (SECTOR_ICON_W)
#define HILITE_ICON_H      (SECTOR_ICON_H)
#define HILITE_ICON_X      (0)
#define HILITE_ICON_Y      (0)
#define ZOOM_MSG_FRAME_X   ((DISPLAY_WIDTH - TWINKLE_MSG_FRAME_WIDTH*2)/2)
#define ZOOM_MSG_FRAME_Y   ((DISPLAY_HEIGHT - TWINKLE_MSG_FRAME_HEIGHT*2)/2)
#define ZOOM_MSG_FRAME_W   (TWINKLE_MSG_FRAME_WIDTH*2)
#define ZOOM_MSG_FRAME_H   (TWINKLE_MSG_FRAME_HEIGHT*2)

#define IS_SYNC_REPAINT                         (TRUE)

/*--------------------------------------------------------------------------
 * variable declarations
 *------------------------------------------------------------------------*/
static WGL_FONT_INFO_T t_font_info  = {FE_FNT_SIZE_SMALL,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

extern NAV_MODEL_T t_g_navigator;
extern BOOL b_is_zoom_on_from_power_on;
BOOL               b_g_zoom_dlg_showing = FALSE;
HANDLE_T           h_g_last_foucs;
HANDLE_T           h_g_current_foucs;

extern INT32 nav_view_set_focus(VOID);



static WGL_HIMG_TPL_T       h_g_zoom_input_icon = NULL_HANDLE;

typedef struct _ZOOM_MODE_VIEW_T
{
    BOOL            b_is_init;
    BOOL            b_is_on;

    HANDLE_T        h_canvas;
    HANDLE_T        h_toast_view;

   // HANDLE_T        h_frame_logo;
   // HANDLE_T        h_icon_logo;
   // BOOL            b_is_logo_on;

    HANDLE_T        h_timer;
    UINT32          ui4_timeout;
    UINT16          ui2_timer_count; /* ui2_timer_count*1000 <= ui4_timeout */
   // RETAIL_MODE_VIEW_TIMER_T    e_timer_status;
    BOOL            b_is_pair_page;

    UINT16          ui2_cfg_nfy_id;
} ZOOM_MODE_VIEW_T;
static ZOOM_MODE_VIEW_T  t_g_zoom_addimg;

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
VOID a_nav_zoom_mode_msg_hide(VOID)
{
    nav_zoom_mode_msg_hide();

    return;
}

BOOL a_nav_zoom_mode_get_msg_show_status(VOID)
{
    return b_g_zoom_dlg_showing;
}

/*--------------------------------------------------------------------------
 * Name
 *      _nav_zoom_mode_indicate_attr_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _nav_zoom_mode_indicate_attr_init(VOID)
{
    WGL_IMG_INFO_T              t_img_info;
    INT32                       i4_ret;

    /* make icon visible */
    i4_ret = c_wgl_set_visibility(indicate_view.h_icon_sector,
                                  WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_set_visibility(indicate_view.h_icon_sector_hilite,
                                  WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* set icon  buffer */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_zoom_sector_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_zoom_sector_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_zoom_sector_img_tpl;

    i4_ret = c_wgl_do_cmd(
                    indicate_view.h_icon_sector,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_FG),
                    WGL_PACK(&t_img_info));
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(
                    indicate_view.h_icon_sector,
                    WGL_CMD_ICON_SET_ALIGN,
                    (VOID*)WGL_AS_LEFT_TOP,
                    NULL);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_zoom_sector_hilite_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_zoom_sector_hilite_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_zoom_sector_hilite_img_tpl;

    i4_ret = c_wgl_do_cmd(
                    indicate_view.h_icon_sector_hilite,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_FG),
                    WGL_PACK(&t_img_info));
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(
                    indicate_view.h_icon_sector_hilite,
                    WGL_CMD_ICON_SET_ALIGN,
                    (VOID*)WGL_AS_RIGHT_TOP,
                    NULL);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_mode_indicate_view_init_widgets
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 _nav_zoom_mode_indicate_view_init_widgets(VOID)
{
    GL_RECT_T                   t_rect;
    INT32                       i4_ret;

    /* Create sector frame */
    SET_RECT_BY_SIZE (& t_rect,
                      SECTOR_FRAME_X,
                      SECTOR_FRAME_Y,
                      SECTOR_FRAME_W,
                      SECTOR_FRAME_H);

    i4_ret = c_wgl_create_widget (indicate_view.h_canvas,//h_cc_canvas
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  NULL,
                                  DEFAULT_BK_ALPHA,
                                  (VOID*) WGL_STL_GL_NO_BK,
                                  NULL,
                                  & indicate_view.h_frame_sector);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Create sector icon */
    SET_RECT_BY_SIZE(&t_rect,
                     SECTOR_ICON_X,
                     SECTOR_ICON_Y,
                     SECTOR_ICON_W,
                     SECTOR_ICON_H);
    i4_ret = c_wgl_create_widget (indicate_view.h_frame_sector,
                                  HT_WGL_WIDGET_ICON,
                                  WGL_CONTENT_ICON_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  NULL,
                                  DEFAULT_BK_ALPHA,
                                  (VOID*) WGL_STL_GL_NO_BK,
                                  NULL,
                                  & indicate_view.h_icon_sector);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Create hilite icon */
    SET_RECT_BY_SIZE(&t_rect,
                     HILITE_ICON_X,
                     HILITE_ICON_Y,
                     HILITE_ICON_W,
                     HILITE_ICON_H);
    i4_ret = c_wgl_create_widget (indicate_view.h_icon_sector,
                                  HT_WGL_WIDGET_ICON,
                                  WGL_CONTENT_ICON_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  NULL,
                                  DEFAULT_BK_ALPHA,
                                  (VOID*) WGL_STL_GL_NO_BK,
                                  NULL,
                                  & indicate_view.h_icon_sector_hilite);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* init the attributes of indicate img */
    i4_ret = _nav_zoom_mode_indicate_attr_init();
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_sector_indicate_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_sector_indicate_stop_timer(
                    ZOOM_INDICATE_T*                 pt_this
                    )
{
    INT32    i4_ret;

    if (c_handle_valid (pt_this->h_icon_timer_hide) == FALSE)
    {
        return;
    }

    /* Stop timer. */
    i4_ret = c_timer_stop (pt_this->h_icon_timer_hide);

    if (i4_ret != OSR_OK)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("Stop zoom indicate::c_timer_stop failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_mode_indicate_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_mode_indicate_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(nav_zoom_mode_indicate_icon_hide, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_sector_msg_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_sector_msg_stop_timer(
                    ZOOM_INDICATE_T*                 pt_this
                    )
{
    INT32    i4_ret;

    if (c_handle_valid (pt_this->h_msg_timer_hide) == FALSE)
    {
        return;
    }

    /* Stop timer. */
    i4_ret = c_timer_stop (pt_this->h_msg_timer_hide);

    if (i4_ret != OSR_OK)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("Stop zoom msg::c_timer_stop failed!"));
    }
}

static VOID _nav_zoom_mode_msg_hide(
                        VOID*                       pv_tag,
                        VOID*                       pv_tag2,
                        VOID*                       pv_tag3
                        )
{
    nav_zoom_mode_msg_hide();
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_mode_msg_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_mode_msg_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_zoom_mode_msg_hide, NULL, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_mode_index_to_align_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static UINT8* _nav_zoom_mode_index_to_align_mode(ZOOM_SECTOR_ITEM e_item)
{
    UINT8*    align = (UINT8*)0x11;

    switch(e_item)
    {
        case 1:
            {
                align = (UINT8*)WGL_AS_LEFT_TOP;
            }
            break;
        case 2:
            {
                align = (UINT8*)WGL_AS_CENTER_TOP;
            }
            break;
        case 3:
            {
                align = (UINT8*)WGL_AS_RIGHT_TOP;
            }
            break;
        case 4:
            {
                align = (UINT8*)WGL_AS_LEFT_CENTER;
            }
            break;
        case 5:
            {
                align = (UINT8*)WGL_AS_CENTER_CENTER;
            }
            break;
        case 6:
            {
                align = (UINT8*)WGL_AS_RIGHT_CENTER;
            }
            break;
        case 7:
            {
                align = (UINT8*)WGL_AS_LEFT_BOTTOM;
            }
            break;
        case 8:
            {
                align = (UINT8*)WGL_AS_CENTER_BOTTOM;
            }
            break;
        case 9:
            {
                align = (UINT8*)WGL_AS_RIGHT_BOTTOM;
            }
            break;
        default:
            return align;
    }

    return align;
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_mode_msg_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_mode_msg_skin(
                    ZOOM_INDICATE_T*            indicate_view,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    WGL_COLOR_INFO_T t_clr_info;
    INT32            i4_ret;

    /* set msg color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = TWINKLE_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = TWINKLE_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = TWINKLE_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = DEFAULT_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = DEFAULT_FG_ALPHA;

    i4_ret = c_wgl_do_cmd(
                    indicate_view->h_text_msg,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_do_cmd(
                    indicate_view->h_text_zoom_msg,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set msg font */
    i4_ret = c_wgl_do_cmd(
                    indicate_view->h_text_msg,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_font_info,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    t_font_info.e_font_size = FE_FNT_SIZE_CUSTOM;
    t_font_info.ui1_custom_size = 36;
    i4_ret = c_wgl_do_cmd(
                    indicate_view->h_text_zoom_msg,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_font_info,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set msg align*/
    i4_ret = c_wgl_do_cmd(
                    indicate_view->h_text_msg,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_do_cmd(
                    indicate_view->h_text_zoom_msg,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_zoom_mode_msg_dlg_proc_fct
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
static INT32 _nav_zoom_mode_msg_dlg_proc_fct (HANDLE_T   h_widget,
                                    UINT32     ui4_msg,
                                    VOID*      param1,
                                    VOID*      param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_EXIT:
                nav_zoom_mode_msg_hide();
                return WGLR_OK;
        default:
            a_amb_default_key_handler_ex(ui4_msg, param1, param2);
            return WGLR_OK;
        }
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_check_wakeup_reason
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_zoom_cust_check_wakeup_reason (VOID)
{
#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    UINT8                ui1_ap_status   = 0;
    PCL_WAKEUP_KEY_T     t_wakeup_key    = {0};
    INT32                i4_ret          = PCLR_OK;
    PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
    c_pcl_get_wakeup_reason(&e_wakeup_reason,NULL);

    a_tv_custom_get_hotkey_wakeup_active(&ui1_ap_status);

    i4_ret = c_pcl_get_wakeup_irkey(&t_wakeup_key);
    if( c_pcl_get_hotkey_active() && i4_ret == PCLR_OK)
    {
        if ( (PCL_WAKEUP_KEY_HOTKEY == t_wakeup_key.e_key_type) && (PCL_WAKE_UP_REASON_IRRC == e_wakeup_reason) &&
             (0x0 == ui1_ap_status) )
        {
            DBG_LOG_PRINT(("ZOOM_CHECK_WACKUP power_seq_cb return true. \n"));
            return TRUE;
        }
        else
        {
            DBG_LOG_PRINT(("ZOOM_CHECK_WACKUP type=%d,reason=%d,status=%d \n",t_wakeup_key.e_key_type,e_wakeup_reason,ui1_ap_status));
            return FALSE;
        }
    }
    else
    {
        DBG_LOG_PRINT(("ZOOM_CHECK_WACKUP active=%d,i4_ret=%d \n",c_pcl_get_hotkey_active(),i4_ret));
        return FALSE;
    }
#endif
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_mode_indicate_icon_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_zoom_mode_indicate_icon_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32    i4_ret;

    i4_ret = c_wgl_set_visibility(indicate_view.h_frame_sector, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK)
    {
        return;
    }
    i4_ret = c_wgl_repaint(indicate_view.h_frame_sector, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK)
    {
        return;
    }
    indicate_view.b_icon_show = FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_sector_indicate_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_zoom_sector_indicate_reset_timer(
                    ZOOM_INDICATE_T*                 pt_this
                    )
{
    INT32 i4_ret;

    /* Stop indicate icon hide timer. */
    _nav_zoom_sector_indicate_stop_timer (pt_this);

    /* Start indicate icon hide timer. */
    i4_ret = c_timer_start (pt_this->h_icon_timer_hide,
                            pt_this->ui4_icon_timeout,
                            X_TIMER_FLAG_ONCE,
                            _nav_zoom_mode_indicate_hide_timer_nfy,
                            pt_this);
    if (i4_ret != OSR_OK)
    {
        ABORT_APPL (DBG_MOD_NAVIGATOR, ("Start zoom indicate::c_timer_start failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_mode_msg_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_mode_msg_hide(VOID)
{
    INT32    i4_ret;

    if (!indicate_view.b_icon_show)
    {
        i4_ret = c_gl_plane_reorder(indicate_view.h_plane, GL_REORDER_ABSOLUTE, 1);
        if (i4_ret != WGLR_OK)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "msg hide timer,reorder cc_plane failed.\n\r");
        }
    }

    if (FALSE == indicate_view.b_msg_show)
    {
        return NAVR_OK;
    }


    i4_ret = c_wgl_get_focus(&h_g_current_foucs);
    NAV_LOG_ON_FAIL(i4_ret);
    /*no other widget get the foucs when the dialog showing.*/
    if (h_g_current_foucs == indicate_view.h_text_msg || h_g_current_foucs == indicate_view.h_text_zoom_msg)
    {
        if (h_g_last_foucs != 0)
        {
            i4_ret = c_wgl_set_focus(h_g_last_foucs, WGL_NO_AUTO_REPAINT);
            NAV_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            nav_view_set_focus();
        }
    }

    i4_ret = c_wgl_set_visibility(indicate_view.h_frame_msg, WGL_SW_HIDE);
    NAV_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_repaint(indicate_view.h_frame_msg, NULL, IS_SYNC_REPAINT);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(indicate_view.h_frame_zoom_msg, WGL_SW_HIDE);
    NAV_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_repaint(indicate_view.h_frame_zoom_msg, NULL, IS_SYNC_REPAINT);
    NAV_LOG_ON_FAIL(i4_ret);

    indicate_view.b_msg_show = FALSE;
    b_g_zoom_dlg_showing = FALSE;
    a_tv_net_OSD_disapper();

    if(b_is_zoom_on_from_power_on == TRUE)
    {
        DBG_LOG_PRINT(("%s:%d.Nfy retailmode to launch when zoom msg hide at power on.\n",__FILE__,__LINE__));
        b_is_zoom_on_from_power_on = FALSE;
        nav_send_msg_to_component(
                    NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_RETAIL_MODE),
                    NAV_UI_MSG_ZOOM_MSG_HIDE,
                    NULL);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_sector_msg_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_zoom_sector_msg_reset_timer(
                    ZOOM_INDICATE_T*                 pt_this
                    )
{
    INT32 i4_ret;

    /* Stop zoom msg hide timer. */
    _nav_zoom_sector_msg_stop_timer (pt_this);

    /* Start zoom msg hide timer. */
    i4_ret = c_timer_start (pt_this->h_msg_timer_hide,
                            pt_this->ui4_msg_timeout,
                            X_TIMER_FLAG_ONCE,
                            _nav_zoom_mode_msg_hide_timer_nfy,
                            pt_this);
    if (i4_ret != OSR_OK)
    {
        ABORT_APPL (DBG_MOD_NAVIGATOR, ("Start zoom msg::c_timer_start failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_sector_indicate_move
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_sector_indicate_move(INT32 sector_item)
{
    INT32               i4_ret = NAVR_OK;
    GL_RECT_T           t_rect = {0};
    GL_RECT_T           t_rect_item = {0};
    UINT32              ui_sector;

    ui_sector = sector_item - 1;
    i4_ret = c_wgl_get_coords(indicate_view.h_frame_msg,
                              WGL_COORDS_SCREEN,
                              &t_rect_item);

	t_rect.i4_top = (indicate_view.ui4_canvas_height/4)*(ui_sector/3) + 16;
	t_rect.i4_bottom = t_rect.i4_top + SECTOR_ICON_H;
	t_rect.i4_left = (indicate_view.ui4_canvas_width/4)*(ui_sector%3) + indicate_view.ui4_canvas_width/2 - SECTOR_ICON_W - 16;
	t_rect.i4_right = t_rect.i4_left + SECTOR_ICON_W;

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "left:%d,right:%d,top:%d,bottom:%d .\n\r",t_rect.i4_left,t_rect.i4_right,t_rect.i4_top,t_rect.i4_bottom);
    i4_ret = c_wgl_move(indicate_view.h_icon_sector, &t_rect, WGL_NO_AUTO_REPAINT);
    if(i4_ret != WGLR_OK) {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "c_wgl_move failed.\n\r");
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_sector_indicate_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_sector_indicate_activate(ZOOM_SECTOR_ITEM e_item)
{
    INT32    i4_ret;
    UINT8*    align = (UINT8*)0x11;

    /* use ui_plane but not cc_plane, because cc_plane may be disabled when nav paused. */
    nav_zoom_sector_indicate_move(e_item);

    align = _nav_zoom_mode_index_to_align_mode(e_item);
    /* set lihite icon alignment */
    i4_ret = c_wgl_do_cmd(
                    indicate_view.h_icon_sector_hilite,
                    WGL_CMD_ICON_SET_ALIGN,
                    (VOID*)align,
                    NULL);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(indicate_view.h_frame_sector,
                                  WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    c_wgl_float(indicate_view.h_frame_sector, TRUE, FALSE);
    i4_ret = c_wgl_repaint(indicate_view.h_frame_sector, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    indicate_view.b_icon_show = TRUE;
    nav_zoom_sector_indicate_reset_timer(&indicate_view);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_mode_msg_move
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_mode_msg_move(INT32 sector_item, BOOL reback)//ZOOM_INDICATE_T*            pt_view,
{
    INT32               i4_ret = NAVR_OK;
    GL_RECT_T           t_rect = {0};
    GL_RECT_T           t_rect_item = {0};
    UINT32              ui_sector;
    UINT8               ui1_repaint = indicate_view.b_msg_show ? WGL_SYNC_AUTO_REPAINT : WGL_NO_AUTO_REPAINT;

    ui_sector = sector_item - 1;
    i4_ret = c_wgl_get_coords(indicate_view.h_frame_msg,
                              WGL_COORDS_SCREEN,
                              &t_rect_item);

    if (reback){
        t_rect.i4_top = TWINKLE_MSG_FRAME_TOP;
        t_rect.i4_bottom = t_rect.i4_top + TWINKLE_MSG_FRAME_HEIGHT;
        t_rect.i4_left = TWINKLE_MSG_FRAME_LEFT;
        t_rect.i4_right = t_rect.i4_left + TWINKLE_MSG_FRAME_WIDTH;
    }
    else{
    	t_rect.i4_top = (indicate_view.ui4_canvas_height/4)*(ui_sector/3) + (indicate_view.ui4_canvas_height/2-TWINKLE_MSG_FRAME_HEIGHT)/2;
    	t_rect.i4_bottom = t_rect.i4_top + TWINKLE_MSG_FRAME_HEIGHT;
    	t_rect.i4_left = (indicate_view.ui4_canvas_width/4)*(ui_sector%3) + (indicate_view.ui4_canvas_width/2-TWINKLE_MSG_FRAME_WIDTH)/2;
    	t_rect.i4_right = t_rect.i4_left + TWINKLE_MSG_FRAME_WIDTH;
    }

    i4_ret = c_wgl_move(indicate_view.h_frame_msg, &t_rect, ui1_repaint);
    if(i4_ret != WGLR_OK) {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "c_wgl_move failed.\n\r");
    }

    return i4_ret;
}

INT32 nav_zoom_mode_send_toast_msg(UINT16 ui2_msg_mlm_idx)
{
    WDK_TOAST_T     t_toast;
    UTF16_T         w2s_str[512] = {0};
    WDK_TOAST_T*    pt_toast_cpy = NULL;

    DBG_LOG_PRINT(("%s:%d,msgid:%d.\r\n",__FILE__,__LINE__,ui2_msg_mlm_idx));
    c_memset((VOID*)w2s_str, 0, sizeof(w2s_str));
    c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;
    t_toast.style.style_4.w2s_str = (VOID *)&w2s_str[0];

    c_uc_w2s_strcpy(w2s_str, MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), ui2_msg_mlm_idx));

    pt_toast_cpy = (WDK_TOAST_T*)c_mem_alloc(sizeof(WDK_TOAST_T));
    c_memcpy((VOID*)pt_toast_cpy, (const VOID*)&t_toast, sizeof(WDK_TOAST_T));
    if (t_toast.e_string_style == WDK_STRING_STRING)
    {
        CHAR     str[256]  = {0};
        UTF16_T* p_w2s_str = (UTF16_T*)t_toast.style.style_4.w2s_str;
        INT32    len  = 0;

        c_uc_w2s_to_ps((const UTF16_T*)p_w2s_str, str, 255);
        DBG_ERROR(("nav_zoom_mode_send_toast_msg str: %s\n\r", str));

        len = (c_uc_w2s_strlen(p_w2s_str)+1)*2;

        DBG_ERROR(("nav_zoom_mode_send_toast_msg c_uc_w2s_strlen: %d\n\r", len));

        pt_toast_cpy->style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(len);

        c_memset((VOID*)pt_toast_cpy->style.style_4.w2s_str, 0, len);

        c_memcpy((VOID*)pt_toast_cpy->style.style_4.w2s_str, (const VOID*)t_toast.style.style_4.w2s_str, len);
    }
    else if (t_toast.e_string_style == WDK_STRING_TITLE_CONTENT)
    {
        INT32    len  = 0;

        len = (c_uc_w2s_strlen((UTF16_T*)t_toast.style.style_5.w2s_title_str)+1)*2;

        DBG_INFO(("nav_zoom_mode_send_toast_msg c_uc_w2s_strlen: %d\n\r", len));
        pt_toast_cpy->style.style_5.w2s_title_str = (UTF16_T*)c_mem_alloc(len);
        c_memset((VOID*)pt_toast_cpy->style.style_5.w2s_title_str, 0, len);
        c_memcpy((VOID*)pt_toast_cpy->style.style_5.w2s_title_str, (const VOID*)t_toast.style.style_5.w2s_title_str, len);


        len = (c_uc_w2s_strlen((UTF16_T*)t_toast.style.style_5.w2s_content_str)+1)*2;
        pt_toast_cpy->style.style_5.w2s_content_str = (UTF16_T*)c_mem_alloc(len);
        c_memset((VOID*)pt_toast_cpy->style.style_5.w2s_content_str, 0, len);
        c_memcpy((VOID*)pt_toast_cpy->style.style_5.w2s_content_str, (const VOID*)t_toast.style.style_5.w2s_content_str, len);
    }

    a_revolt_info_set_timeout(ZOOM_MODE_MSG_TIMER_DELAY);
    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                              NAV_UI_MSG_REST_NOTIFICATION,
                              (VOID*) pt_toast_cpy);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_mode_msg_show_delay_timer_cb_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_mode_msg_show_delay_timer_cb_fct(
                                    VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3)
{
    INT32 i4_ret = 0;
    //UINT16 ui2_msg_mlm_idx    = 0 ;

    if (_nav_zoom_cust_check_wakeup_reason())
    {
        /*TV wackup by hotkey,do not show zoom msg,show 3rd launching osd.*/
        //a_zoom_mode_select_sector(ZOOM_SECTOR_ITEM_5, FALSE);
        KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "TV wackup by hotkey,do not show zoom msg.\n\r");
        return;
    }
    //ui2_msg_mlm_idx = MLM_NAV_KEY_ENABLE_ZOOM_MSG;
    //i4_ret = nav_zoom_mode_msg_show(ui2_msg_mlm_idx);
    NAV_LOG_ON_FAIL(i4_ret);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_mode_msg_show_delay_timer_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_mode_msg_show_delay_timer_cb (HANDLE_T  pt_tm_handle,
                                   VOID*     pv_tag)
{
    nav_request_context_switch(_nav_zoom_mode_msg_show_delay_timer_cb_fct,
                                    NULL,
                                    NULL,
                                    NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_mode_msg_show_delay_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_mode_msg_show_delay_timer(
                    VOID
                    )
{
    INT32 i4_ret;
    HANDLE_T nav_zoom_msg_tts_timer;

    i4_ret = c_timer_create (& nav_zoom_msg_tts_timer);
    if (i4_ret != OSR_OK)
    {
        DBG_LOG_PRINT(("%s() Line %d =========\n",__FUNCTION__,__LINE__));
        return NAVR_FAIL;
    }

    i4_ret = c_timer_stop(nav_zoom_msg_tts_timer);
    if(i4_ret != OSR_OK){
        DBG_LOG_PRINT(("%s() Line %d =========\n",__FUNCTION__,__LINE__));
    }

    i4_ret = c_timer_start(
                    nav_zoom_msg_tts_timer,
                    1000,
                    X_TIMER_FLAG_ONCE,
                    _nav_zoom_mode_msg_show_delay_timer_cb,
                    NULL);
    if(i4_ret != OSR_OK){
        DBG_LOG_PRINT(("%s() Line %d =========\n",__FUNCTION__,__LINE__));
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_mode_indicate_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_mode_indicate_view_init(VOID)
{
    INT32                       i4_ret;

    NAV_MODEL_T* pt_this = &t_g_navigator;
    indicate_view.h_screen = pt_this->t_nav_ctx.t_gui_res.h_screen;
    indicate_view.h_canvas = pt_this->t_nav_ctx.t_gui_res.h_canvas;
    indicate_view.h_plane = pt_this->t_nav_ctx.t_gui_res.h_ui_plane;

    /* create the indicate hide timer */
    indicate_view.ui4_icon_timeout = ZOOM_MODE_INDICATE_TIMER_DELAY;
    i4_ret = c_timer_create (& indicate_view.h_icon_timer_hide);
    if (i4_ret != OSR_OK)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "indicate timer create failed.\n\r");
        return NAVR_FAIL;
    }

    /* get the CC plane */
    i4_ret = c_gl_plane_open(
                    indicate_view.h_screen,
                    nav_get_cc_osd_plane_index(),//0
                    &(indicate_view.h_cc_plane));
    if (GLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* get canvas for frame creation */
    i4_ret = c_wgl_get_canvas(
                    indicate_view.h_cc_plane,
                    &indicate_view.h_cc_canvas);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* cerate indicate image */
    i4_ret = nav_zoom_mode_create_indicate_img_tpl();
    if (NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* get canvas width and height */
    i4_ret = c_wgl_get_canvas_size(
                    indicate_view.h_canvas,
                    &indicate_view.ui4_canvas_width,
                    &indicate_view.ui4_canvas_height);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = _nav_zoom_mode_indicate_view_init_widgets();
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_mode_indicate_view_init_widgets failed.\n\r");
        return NAVR_FAIL;
    }

    return NAVR_OK;
}





/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_mode_msg_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_mode_msg_view_init(VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;

    /* create the msg hide timer */
    indicate_view.ui4_msg_timeout = ZOOM_MODE_MSG_TIMER_DELAY;
    i4_ret = c_timer_create (& indicate_view.h_msg_timer_hide);
    if (i4_ret != OSR_OK)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "msg timer create failed.\n\r");
        return NAVR_FAIL;
    }

    /* create frame */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    TWINKLE_MSG_FRAME_LEFT,
                    TWINKLE_MSG_FRAME_TOP,// + TWINKLE_MSG_FRAME_HEIGHT*2
                    TWINKLE_MSG_FRAME_WIDTH,
                    TWINKLE_MSG_FRAME_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    indicate_view.h_cc_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_IMG_UI| WGL_STL_GL_NO_BK),
                    NULL,
                    &(indicate_view.h_frame_msg)
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(
                    &t_rect,
                    TWINKLE_MSG_TITLE_LEFT,
                    TWINKLE_MSG_TITLE_TOP,
                    TWINKLE_MSG_TITLE_WIDTH,
                    TWINKLE_MSG_TITLE_HEIGHT
                    );

    i4_ret = c_wgl_create_widget(
                    indicate_view.h_frame_msg,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    _nav_zoom_mode_msg_dlg_proc_fct,//NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_512
                          | WGL_STL_TEXT_MULTILINE
                          | WGL_STL_TEXT_SMART_CUT),
                    NULL,
                    &indicate_view.h_text_msg
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(
                    &t_rect,
                    ZOOM_MSG_FRAME_X,
                    ZOOM_MSG_FRAME_Y,// + TWINKLE_MSG_FRAME_HEIGHT*2
                    ZOOM_MSG_FRAME_W,
                    ZOOM_MSG_FRAME_H
                    );
    i4_ret = c_wgl_create_widget(
                    indicate_view.h_cc_canvas,//,h_cc_canvas
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_IMG_UI| WGL_STL_GL_NO_BK),
                    NULL,
                    &(indicate_view.h_frame_zoom_msg)
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(
                    &t_rect,
                    TWINKLE_MSG_TITLE_LEFT,
                    TWINKLE_MSG_TITLE_TOP,
                    TWINKLE_MSG_FRAME_WIDTH*2,
                    TWINKLE_MSG_FRAME_HEIGHT*2
                    );

    i4_ret = c_wgl_create_widget(
                    indicate_view.h_frame_zoom_msg,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    _nav_zoom_mode_msg_dlg_proc_fct,//NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_512
                          | WGL_STL_TEXT_MULTILINE
                          | WGL_STL_TEXT_SMART_CUT),
                    NULL,
                    &indicate_view.h_text_zoom_msg
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(
                    indicate_view.h_text_msg,
                    WGL_SW_NORMAL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_set_visibility(
                    indicate_view.h_text_zoom_msg,
                    WGL_SW_NORMAL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    /* listbox background image */
    WGL_HIMG_TPL_T  t_lb_bk_img;
    i4_ret = nav_img_create_scr_svr_bk_img_tpl(&t_lb_bk_img);
    if(WGLR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "nav_img_create_scr_svr_bk_img_tpl failed.\n\r");
        return NAVR_FAIL;
    }
    WGL_HIMG_TPL_T  t_lb_bk_zoom_img;
    //i4_ret = nav_img_create_scr_svr_bk_zoom_img_tpl(&t_lb_bk_zoom_img);
    i4_ret = nav_img_create_scr_svr_bk_img_tpl(&t_lb_bk_zoom_img);
    if(WGLR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "nav_img_create_scr_svr_bk_img_tpl failed.\n\r");
        return NAVR_FAIL;
    }

    WGL_IMG_INFO_T  t_img_info ;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_lb_bk_img;
    t_img_info.u_img_data.t_standard.t_disable   = t_lb_bk_img;
    t_img_info.u_img_data.t_standard.t_highlight = t_lb_bk_img;
    i4_ret = c_wgl_do_cmd(
               indicate_view.h_text_msg,
               WGL_CMD_GL_SET_IMAGE ,
               WGL_PACK(WGL_IMG_BK) ,
               WGL_PACK(&t_img_info)
               ) ;
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_lb_bk_zoom_img;
    t_img_info.u_img_data.t_standard.t_disable   = t_lb_bk_zoom_img;
    t_img_info.u_img_data.t_standard.t_highlight = t_lb_bk_zoom_img;
    i4_ret = c_wgl_do_cmd(
               indicate_view.h_text_zoom_msg,
               WGL_CMD_GL_SET_IMAGE ,
               WGL_PACK(WGL_IMG_BK) ,
               WGL_PACK(&t_img_info)
               ) ;
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _nav_zoom_mode_msg_skin(&indicate_view,2);
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(
                    indicate_view.h_frame_msg,
                    WGL_SW_HIDE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(
                    indicate_view.h_frame_msg,
                    NULL,
                    IS_SYNC_REPAINT
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }


    i4_ret = c_wgl_set_visibility(
                    indicate_view.h_text_zoom_msg,
                    WGL_SW_HIDE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(
                    indicate_view.h_text_zoom_msg,
                    NULL,
                    IS_SYNC_REPAINT
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

	nav_zoom_mode_img_init();
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_mode_img_init
 * Description
 *		init some parameters and create a img
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/

INT32 nav_zoom_mode_img_init()
{
	ZOOM_MODE_VIEW_T*     pt_this = &t_g_zoom_addimg;
    INT32                   i4_ret  = 0;

    if (pt_this->b_is_init)
    {
        DBG_LOG_PRINT((" retail_mode_view_init already.\n"));
        return NAVR_OK;
    }

    DBG_LOG_PRINT(("%s, %d start.\n", __FUNCTION__, __LINE__));

    pt_this->b_is_on        = FALSE;
    pt_this->h_timer        = NULL_HANDLE;
    pt_this->ui4_timeout    = 0;
    pt_this->ui2_timer_count= 0;
    pt_this->h_canvas       = indicate_view.h_canvas;
    pt_this->h_toast_view   = NULL_HANDLE;
    pt_this->ui2_cfg_nfy_id = APP_CFG_NOTIFY_NULL_ID;

    i4_ret = c_wgl_img_tpl_create(
                      WGL_IMG_ST_NO_SEGMENT,
                      &t_g_system_notification,
                      &h_g_zoom_input_icon
                      );

	if(WGLR_OK != i4_ret)
	{
		DBG_LOG_PRINT((" create img icon failed .\n"));
        return NAVR_FAIL;
    }

return OSR_OK;

}
/*-----------------------------------------------------------------------------
 * Name
 *      _nava_zoom_mode_hide_img_cd_fct
 * Description
 *		the timer callback fct hide img
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/

static VOID _nav_zoom_mode_hide_img_cd_fct (HANDLE_T  pt_tm_handle,
                                                      VOID*     pv_tag)
{
   	nav_zoom_mode_hide_img_title();
	a_nav_zoom_cust_select_sector(ZOOM_SECTOR_ITEM_1,TRUE);
	a_nav_zoom_cust_select_top_sector();

   return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nava_zoom_mode_hide_img_title
 * Description
 *		hide the img and title
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_mode_hide_img_title(VOID)
{
    ZOOM_MODE_VIEW_T*     pt_this = &t_g_zoom_addimg;
    INT32                   i4_ret  = 0;

    if (c_wgl_float(pt_this->h_toast_view, FALSE, FALSE) != WGLR_OK) {
        DBG_ERROR(("[NAV] {%s,%d} fail.\r\n", __FUNCTION__, __LINE__));
    }
    i4_ret = a_toast_hide(pt_this->h_toast_view);
    if (OSR_OK != i4_ret)
    {
		DBG_ERROR(("[NAV] {%s,%d} fail.\r\n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }

    i4_ret = a_toast_destroy(pt_this->h_toast_view);
    if (OSR_OK != i4_ret)
    {
        DBG_ERROR(("[NAV] {%s,%d} fail.\r\n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }

    pt_this->b_is_on = FALSE;
    pt_this->h_toast_view = NULL_HANDLE;
    return OSR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_mode_msg_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/

 INT32 nav_zoom_mode_show_img_title(UTF16_T*  pw2s_string)
{
    ZOOM_MODE_VIEW_T*     	pt_this = &t_g_zoom_addimg;
    INT32                   i4_ret  = 0;
    UTF16_T*                pw2s_msg = pw2s_string;
    UTF16_T*                pw2s_title = NULL;

    CHAR                    s_timer_string[5] = {0};
    UTF16_T                 w2s_timer_string[5+1] = {0};
    UTF16_T 				w2s_tts_str[1024] = {0};

    UINT8                   ui1_zoom_mode = 0;
    i4_ret = a_cfg_cust_get_zoom_status(&ui1_zoom_mode);

    /* create toast osd */
    if (pt_this->h_toast_view == NULL_HANDLE)
    {
        TOAST_INIT_PARAM_T  t_toast_init;
        c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));

        t_toast_init.e_toast_style  = TOAST_STYLE_MSG_WITH_TITLE_CONTENT;
        t_toast_init.h_canvas       = pt_this->h_canvas;
        t_toast_init.t_custom_setting.u.t_msg_with_title_init.e_msg_type = TOAST_MSG_TYPE_WITH_TIMER_COUNTDOWN;
        t_toast_init.t_custom_setting.u.t_msg_with_title_init.ui1_title_align = WGL_AS_CENTER_CENTER;
		t_toast_init.t_custom_setting.u.t_msg_with_title_init.ui1_text_align = WGL_HTS_JUSTIF_CENTER;
        t_toast_init.t_custom_setting.ui2_toast_msg_id = MLM_MENU_KEY_ACCESS_ZOOM_MODE;
        i4_ret = a_toast_create(&t_toast_init, &(pt_this->h_toast_view));
        if (OSR_OK != i4_ret)
        {
            DBG_LOG_PRINT((" a_toast_create failed !!!!\n"));
            return NAVR_FAIL;
        }
    }
    else
    {
        DBG_LOG_PRINT((" [zoom] %s(), a_toast_create ok !!!!\n",__func__));
    }

    TOAST_CUSTOMIZATION_DATA_T  t_custom_data;
    c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));
    t_custom_data.u.t_msg_with_title_init.w2s_msg_str = (VOID*)pw2s_msg;
    t_custom_data.u.t_msg_with_title_init.h_insert_img = h_g_zoom_input_icon;
    if (c_wgl_float(pt_this->h_toast_view, TRUE, FALSE) != WGLR_OK) {
       // DBG_ERROR(("[NAV] {%s,%d} fail.\r\n", __FUNCTION__, __LINE__));
    }
    a_nav_zoom_cust_select_sector(ZOOM_SECTOR_ITEM_2,TRUE);
    a_nav_zoom_cust_select_top_sector();


    i4_ret = a_toast_show(pt_this->h_toast_view, &t_custom_data);
    if (OSR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("a_toast_show failed !!!!\n"));
        return NAVR_FAIL;
    }

     if(pt_this->h_timer  != NULL)
    {
        c_timer_stop(pt_this->h_timer );
        c_timer_delete(pt_this->h_timer );
        pt_this->h_timer   =  NULL_HANDLE;
    }
    i4_ret = c_timer_create(&pt_this->h_timer );
    if (i4_ret != OSR_OK)
    {
        DBG_LOG_PRINT(("[ZOOM]create failed\n"));
        return NAVR_FAIL;
    }
    i4_ret = c_timer_start(pt_this->h_timer ,
                        10000,
                        X_TIMER_FLAG_ONCE,
                        _nav_zoom_mode_hide_img_cd_fct,
                        NULL);

    if(ui1_zoom_mode == 1)
    {
        //DBG_LOG_PRINT(("YYYYYYYYYzoom on\n"));
        if (a_cfg_cust_zoom_digit_selection_support())
        {
            c_uc_w2s_strcpy(w2s_tts_str, (UTF16_T*)NAV_ZOOM_TTS_ON);
        }
        else
        {
            c_uc_w2s_strcpy(w2s_tts_str, (UTF16_T*)NAV_ZOOM_NO_NUMBER_PAD_TTS_ON);
        }
    }
    else
    {
        //DBG_LOG_PRINT(("YYYYYYYYYzoom off\n"));
        c_uc_w2s_strcpy(w2s_tts_str, (UTF16_T*)NAV_ZOOM_TTS_OFF);
    }
    a_app_tts_play(w2s_tts_str, c_uc_w2s_strlen(w2s_tts_str));

    return NAVR_OK;
}


#endif /*APP_ZOOM_MODE_SUPPORT*/
