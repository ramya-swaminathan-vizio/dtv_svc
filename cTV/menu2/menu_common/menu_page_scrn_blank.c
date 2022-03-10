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
 * $RCSfile: menu_page_net_info.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_txt.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "menu2/menu.h"
#include "res/menu2/menu_img.h"
#include "res/menu2/menu_clr.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_common/menu_common.h"
#include "app_client.h"
#include "app_util/a_cfg.h"
#include "app_util/a_network.h"

#include "app_util/a_icl.h"
#include "res/app_util/icl/a_icl_custom.h"

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#include "res/app_util/config/a_cfg_custom.h"
#endif
#include "menu2/menu_dbg.h"
#include "am/a_am.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define  _ENABLE_LOG_                   0
#define  MENU_DLG_BTN_TEXT_CLR          (GL_COLOR_T){255, {255}, {255}, {255}})

#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

/* screen saver message */
#define SCRN_BLANK_FRAME_WIDTH          (412)
#define SCRN_BLANK_FRAME_HEIGHT         (179)
#define SCRN_BLANK_FRAME_LEFT           ((SCREEN_W - (SCRN_BLANK_FRAME_WIDTH))/2)
#define SCRN_BLANK_FRAME_TOP            ((SCREEN_H - SCRN_BLANK_FRAME_HEIGHT)/2)

#define SCRN_BLANK_TEXT_LEFT            (10)
#define SCRN_BLANK_TEXT_TOP             (10)
#define SCRN_BLANK_TEXT_WIDTH           (SCRN_BLANK_FRAME_WIDTH - SCRN_BLANK_TEXT_LEFT * 2)
#define SCRN_BLANK_TEXT_HEIGHT          (118)

#define SCRN_BLANK_BUTTON_W             (133)
#define SCRN_BLANK_BUTTON_H             (37)
#define SCRN_BLANK_BUTTON_LEFT          ((SCRN_BLANK_FRAME_WIDTH - SCRN_BLANK_BUTTON_W)/2)
#define SCRN_BLANK_BUTTON_TOP           (SCRN_BLANK_TEXT_TOP * 2 + SCRN_BLANK_TEXT_HEIGHT)

#define MENU_SCRN_BLANK_MSG_DELAY       ((UINT32)(1000))
#define MENU_SCRN_BLANK_MSG_TIMES       ((UINT8)20)
#define MMP_NAME                        "mmp"

#if _ENABLE_LOG_
#define _USER_DBG_LOG(_stmt)    DBG_INFO (_stmt);
#else
#define _USER_DBG_LOG(_stmt)
#endif
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct _SCRN_BLANK_PAGE_DATA_T
{
    HANDLE_T                h_root_frm;
    HANDLE_T                h_dlg;
    HANDLE_T                h_timer;
}SCRN_BLANK_PAGE_DATA_T;
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_scrn_blank;
SCRN_BLANK_PAGE_DATA_T t_g_scrn_blank_page;

GL_COLOR_T           t_g_menu_color_txt_nor = { 255, {200}, {200 }, {200 }}; /* Gray color */
GL_COLOR_T           t_g_menu_color_txt_hlt = { 255, {255 }, {255 }, {255}}; /* white color */

//static UINT8         ui1_msg_times = MENU_SCRN_BLANK_MSG_TIMES;
static CHAR          s_g_msg[128] = {0};
static BOOL          b_is_hot_key_enter = FALSE;
static UINT32        ui4_pre_page_id = ((UINT32)0xFFFFFFFF);

BOOL b_mmp_blank_screen = FALSE;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _menu_scrn_blank_timer_stop(VOID);

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
static INT32 _scrn_blank_nav_back(VOID)
{
    if (b_is_hot_key_enter
        && ui4_pre_page_id == ((UINT32)0xFFFFFFFF))
    {
        _menu_scrn_blank_timer_stop();
        return MENUR_OK;
    }

    _menu_scrn_blank_timer_stop();
    menu_nav_back();

    return MENUR_OK;
}

static VOID _btn_proc_fct(VOID)
{
    menu_custom_blank_screen();
    _scrn_blank_nav_back();
}

/*----------------------------------------------------------------------------
 * Name: _cnt_frm_proc_fct
 *
 * Description: Dispatch all notifications to corresponding widgets.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _cnt_frm_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        menu_blank_oled_scrn_timer_refresh();

        if (b_is_hot_key_enter
            && ui4_pre_page_id == ((UINT32)0xFFFFFFFF)
            && menu_custom_is_blank_screen()
            && ui4_keycode != BTN_CC)   // process cc key in cc_info.c
        {
            b_is_hot_key_enter = FALSE;
            DBG_INFO(("%s(): will unblank\n", __FUNCTION__));
            menu_custom_unblank_screen(ui4_keycode);
            _scrn_blank_nav_back();
            return WGLR_OK;
        }

        switch (ui4_keycode)
        {
            case BTN_SELECT:
            case BTN_CC:
//                _scrn_blank_nav_back();
//                menu_custom_blank_screen();
                return WGLR_OK;
            default:
                b_is_hot_key_enter = FALSE;
                menu_custom_unblank_screen(ui4_keycode);
                _scrn_blank_nav_back();
                return WGLR_OK;
        }
    }
    default:
        break;
    }

    return a_ui_simple_dialog_default_msg_proc(h_widget,
                                               ui4_msg,
                                               param1,
                                               param2);
    //return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
#if 0 //no need dialog
static VOID _do_timer_nfy(VOID* pv_data, SIZE_T z_data_size)
{
    CHAR *ps_tmp = NULL;
    CHAR s_sec[3] = {0};
    UTF16_T w2s_msg[128] = {0};

    //c_snprintf(s_sec, 3, "%2d", ui1_msg_times);

    s_sec[0] = (ui1_msg_times/10 == 0) ? ' ' : (ui1_msg_times/10 + '0');
    s_sec[1] = ui1_msg_times%10 + '0';

    _USER_DBG_LOG(("%s(): s_sec = [%s], ui1_msg_times = %d, s_g_msg = [%s]\n",
                                                    __FUNCTION__,
                                                    s_sec,
                                                    ui1_msg_times,
                                                    s_g_msg));

    ui1_msg_times--;

    if (0 == ui1_msg_times)
    {
        _scrn_blank_nav_back();
        menu_custom_blank_screen();
    }
    else
    {
        ps_tmp = c_strstr(s_g_msg, s_sec);

        if (ps_tmp != NULL)
        {
            ps_tmp[0] = (ui1_msg_times/10 == 0) ? ' ' : (ui1_msg_times/10 + '0');
            ps_tmp[1] = ui1_msg_times%10 + '0';

            c_uc_ps_to_w2s(s_g_msg, w2s_msg, 127);

            a_ui_simple_dialog_set_text(t_g_scrn_blank_page.h_dlg, w2s_msg);
            a_ui_simple_dialog_repaint(t_g_scrn_blank_page.h_dlg);
        }
    }


}

static VOID _menu_scrn_blank_timer_cb(HANDLE_T h_timer, VOID* pv_tag)
{
    menu_async_invoke(_do_timer_nfy, NULL, 0, FALSE);
}
#endif
static INT32 _menu_scrn_blank_timer_start(VOID)
{
    INT32   i4_ret = MENUR_OK;
#if 0 //no need dialog
    ui1_msg_times = MENU_SCRN_BLANK_MSG_TIMES;
    c_uc_w2s_to_ps(MENU_TEXT(MLM_MENU_KEY_SCRN_BLANK_TIME_MSG),
                    s_g_msg,
                    sizeof(s_g_msg)-1);

    i4_ret = c_timer_start(t_g_scrn_blank_page.h_timer,
                  MENU_SCRN_BLANK_MSG_DELAY,
                  X_TIMER_FLAG_REPEAT,
                  _menu_scrn_blank_timer_cb,
                  NULL);

    MENU_LOG_ON_FAIL(i4_ret);
#endif
    return i4_ret;
}

static INT32 _menu_scrn_blank_timer_stop(VOID)
{
    INT32   i4_ret = MENUR_OK;
#if 0 //no need dialog
    i4_ret = c_timer_stop(t_g_scrn_blank_page.h_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    ui1_msg_times = MENU_SCRN_BLANK_MSG_TIMES;
#endif
    return i4_ret;
}
/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id, VOID*  pv_create_data)
{
    SCRN_BLANK_PAGE_DATA_T*     pt_this = &t_g_scrn_blank_page;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    INT32                       i4_ret;

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));
    c_memset(&t_g_scrn_blank_page, 0, sizeof(t_g_scrn_blank_page));

    i4_ret = menu_pm_get_root_frm(&pt_this->h_root_frm);
    MENU_CHK_FAIL(i4_ret);



    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = pt_this->h_root_frm;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _btn_proc_fct;
    t_simple_dialog_init.pf_wdgt_proc                   = _cnt_frm_proc_fct;
    t_simple_dialog_init.pt_begin_offset                = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_one_btn_mode                 = TRUE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                        &pt_this->h_dlg);
    if (i4_ret != APP_UIR_OK)
    {
        return MENUR_FAIL;
    }

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_dlg, MENU_TEXT(MLM_MENU_KEY_SCRN_BLANK_TIME_MSG));
    if(i4_ret != APP_UIR_OK)
    {
        return MENUR_FAIL;
    }

    c_wgl_set_visibility(pt_this->h_dlg, WGL_SW_HIDE_RECURSIVE);

    c_uc_w2s_to_ps(MENU_TEXT(MLM_MENU_KEY_SCRN_BLANK_TIME_MSG),
                    s_g_msg,
                    sizeof(s_g_msg)-1);

    i4_ret = c_timer_create(&pt_this->h_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    if (c_handle_valid(t_g_scrn_blank_page.h_timer) == TRUE) {
        c_timer_delete(t_g_scrn_blank_page.h_timer);
        t_g_scrn_blank_page.h_timer = NULL_HANDLE;
    }

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32    i4_ret = MENUR_OK;
    SCRN_BLANK_PAGE_DATA_T*     pt_this = &t_g_scrn_blank_page;
    CHAR     s_active_app[APP_NAME_MAX_LEN] = {0};

    a_am_get_active_app(s_active_app);
    if (c_strcmp(s_active_app, MMP_NAME) == 0)
    {
        b_mmp_blank_screen = TRUE;
    }

    //menu_nav_get_crnt_page(&ui4_pre_page_id);
#if 0 //(VIEWPORT_SUPPORT == 1)
    a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_WIDE_MODE);
    a_cfg_update_viewport ();
#endif
#if 0 //no need dialog
    a_ui_simple_dialog_set_text(pt_this->h_dlg, MENU_TEXT(MLM_MENU_KEY_SCRN_BLANK_TIME_MSG));
    a_ui_simple_dialog_set_yes_text(pt_this->h_dlg, MENU_TEXT(MLM_MENU_KEY_OK));
    a_ui_simple_dialog_show(pt_this->h_dlg);
#endif
    a_ui_simple_dialog_set_focus(pt_this->h_dlg, TRUE);
    a_ui_simple_dialog_repaint(pt_this->h_dlg);

    b_is_hot_key_enter =  t_g_menu_common.b_is_hot_key_enter;
    _menu_scrn_blank_timer_start();

   // menu_custom_blank_screen();

  //  a_tv_net_send_cmd("\n:am,am,:disable_keyroute\n");

    return i4_ret;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    SCRN_BLANK_PAGE_DATA_T* pt_page_data = &t_g_scrn_blank_page;
    INT32       i4_ret;

    i4_ret = a_ui_simple_dialog_hide(pt_page_data->h_dlg);

    DBG_INFO(("i4_ret=%d\n", i4_ret));

    menu_help_tip_keytip_show(TRUE);

    _menu_scrn_blank_timer_stop();

    a_tv_net_send_cmd("\n:am,am,:enable_keyroute\n");

#if 0//(VIEWPORT_SUPPORT == 1)
    UINT8   ui1_status = YAHOO_STATUS_HIDE;

    if (a_cfg_get_app_status () == APP_CFG_APP_STATUS_MENU_WIDE_MODE)
    {
        a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
    }

    if (a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_DOCK, &ui1_status) == ICLR_OK)
    {
        if ((YAHOO_STATUS_DOCK_UP & ui1_status) != 0)
        {
            a_cfg_set_app_status (APP_CFG_APP_STATUS_YH_DOCK);
        }
        if ((YAHOO_STATUS_SIDEBAR & ui1_status) != 0)
        {
            a_cfg_set_app_status (APP_CFG_APP_STATUS_YH_SIDEBAR);
        }
    }
    a_cfg_update_viewport ();
#endif


    b_is_hot_key_enter = FALSE;
    ui4_pre_page_id = ((UINT32)0xFFFFFFFF);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
extern INT32 menu_common_page_scrn_blank_init(VOID)
{
    t_g_menu_common_page_scrn_blank.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_scrn_blank.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_scrn_blank.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_scrn_blank.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_scrn_blank.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_scrn_blank.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_scrn_blank.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

