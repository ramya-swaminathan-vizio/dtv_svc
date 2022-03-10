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
 * $RCSfile: usb_pld_view.c,v $
 * $Revision: #2 $
 * $Date: 2015/06/09 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *       USB Plug Detection.
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_NAV_USB_PLD

#include "u_common.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_gl.h"
#include "c_os.h"
#include "c_handle.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_svctx.h"

#include "menu2/a_menu.h"
#include "am/a_am.h"
#include "amb/a_amb.h"

#include "app_util/rmv_dev/a_rmv_dev.h"
#include "nav/nav_common.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"
#include "nav/dialog/nav_dialog.h"
#include "nav/usb_pld/nav_usb_pld_view.h"

#include "app_util/a_ui.h"
#include "app_util/a_tv.h"

#include "res/app_util/rmv_dev/a_rmv_dev_custom.h"
#include "res/app_util/icl/a_icl_custom.h"

#ifdef APP_CAST_TV_MMP
#include "wdk/widget/wdk_widget.h"
#include "res/revolt/revolt_settings_mlm.h"
#endif
#include "res/app_util/config/acfg_cust_misc.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/banner2/banner.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#include "nav/banner2/a_banner.h"
#endif
#include "res/menu2/menu_custom.h"

#include "mmp/a_mmp.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

typedef struct _NAV_USB_PLD_VIEW_T
{
    NAV_USB_PLD_HDLR_T*     pt_ctrl;

    HANDLE_T                h_canvas;
    HANDLE_T                h_hide_timer;
#ifdef APP_CAST_TV_MMP
    HANDLE_T                h_toast_timer;
    BOOL                    b_is_toast_show;
#endif
    UINT32                  ui4_time_delay;

    BOOL                    b_is_show;
} NAV_USB_PLD_VIEW_T;

#define RET_ON_ERR(_expr)  \
{ \
INT32 expr = _expr; \
if(expr != 0)\
{\
    DBG_ERROR (("<NAV_USB_PLD> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__)); \
    return expr;\
} \
}

#define NAV_USB_PLD_DLG_DEFAULT_TIMER_DELAY     10000
#ifdef APP_TTS_SUPPORT
#define NAV_TTS_TEXT(key)   \
            MLM_NAV_TEXT(0, (key))  /* 0:english  nav_get_mlm_lang_id() */
#endif
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_USB_PLD_VIEW_T       t_g_nav_usb_pld_view = {0};
#ifdef APP_CAST_TV_MMP
static WDK_TOAST_PARAM_T       tg_toast_param = {0} ;
static WDK_OSD_TOAST_T          t_g_wdk_view={0} ;
#endif

#ifdef APP_TTS_SUPPORT
static UINT32 g_ui4_uplg_usb_tts_play_id = 0;
#endif


/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_view_show (NAV_USB_PLD_PAGE_E e_page_id);
static INT32 _nav_usb_pld_view_hide (VOID);
extern BOOL a_nav_via_dlg_is_dtv_resuming(VOID);

VOID a_nav_usb_pld_view_dialog_hide(VOID)
{
	nav_dialog_stop_hide_timer();

    nav_hide_component(NAV_COMP_ID_USB_PLD);

    _nav_usb_pld_view_hide();

    return;
}


/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_dlg_hide_timer_fct
 * Description:
 *      nav usb plugin detection dialog hide timer notify
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_usb_pld_dlg_hide_timer_fct(VOID*        pv_tag1,
                                            VOID*        pv_tag2,
                                            VOID*        pv_tag3)
{
    nav_hide_component(NAV_COMP_ID_USB_PLD);

    _nav_usb_pld_view_hide();

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_dlg_hide_timer_nfy
 * Description:
 *      nav usb plugin detection dialog hide timer notify
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_usb_pld_dlg_hide_timer_nfy(HANDLE_T        h_timer,
                                            VOID*           pv_tag)
{
    nav_request_context_switch(_nav_usb_pld_dlg_hide_timer_fct, NULL, NULL, NULL);

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_dlg_hide_timer_start
 * Description:
 *      start nav usb plugin detection dialog timer
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_dlg_hide_timer_start(VOID)
{
    INT32                       i4_ret = NAVR_OK;
    NAV_USB_PLD_VIEW_T*         pt_view = &t_g_nav_usb_pld_view;

    if (NULL_HANDLE != pt_view->h_hide_timer)
    {
        i4_ret = c_timer_start(pt_view->h_hide_timer,
                               pt_view->ui4_time_delay,
                               X_TIMER_FLAG_ONCE,
                               _nav_usb_pld_dlg_hide_timer_nfy,
                               NULL);
        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_dlg_yes_fct
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
static VOID _nav_usb_pld_dlg_yes_fct(VOID)
{
#if 0
    if ((a_nav_via_dlg_is_dtv_resuming()) == FALSE)
    {
        RMV_DEV_MNT_POINT_INFO_T t_mount_point_info;

        c_memset(&t_mount_point_info, 0, sizeof(t_mount_point_info));
        a_rmv_dev_get_mount_point_info(&t_mount_point_info);

        a_rmv_dev_set_active_mnt_pnt(t_mount_point_info.ui4_last_effective_idx);
        a_menu_shortcut_link(MENU_SHORT_CUT_MMP_MEDIA_TYPE);

        nav_dialog_stop_hide_timer();

        nav_hide_component(NAV_COMP_ID_USB_PLD);

        _nav_usb_pld_view_hide();
    }
#endif

    INT32     i4_ret = NAVR_OK;;
    CHAR      s_active_app[APP_NAME_MAX_LEN+1] = {0};

    a_am_get_active_app (s_active_app) ;

    if (AMR_OK == i4_ret && 0 == c_strcmp (s_active_app, NAV_NAME))
    {

        RMV_DEV_MNT_POINT_INFO_T t_mount_point_info;

        c_memset(&t_mount_point_info, 0, sizeof(t_mount_point_info));
        a_rmv_dev_get_mount_point_info(&t_mount_point_info);

        RET_ON_ERR(a_rmv_dev_set_active_mnt_pnt(t_mount_point_info.ui4_last_effective_idx));

        a_menu_custom_page_mmp_media_set_enter_flag(TRUE);
        a_menu_shortcut_link(MENU_SHORT_CUT_MMP_MEDIA_TYPE);

        nav_dialog_stop_hide_timer();

        nav_hide_component(NAV_COMP_ID_USB_PLD);

        _nav_usb_pld_view_hide();
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_dlg_no_fct
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
static VOID _nav_usb_pld_dlg_no_fct(VOID)
{
	nav_dialog_stop_hide_timer();

    nav_hide_component(NAV_COMP_ID_USB_PLD);

    _nav_usb_pld_view_hide();

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_dlg_ok_fct
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
static VOID _nav_usb_pld_dlg_ok_fct(VOID)
{

	nav_dialog_stop_hide_timer();

    nav_hide_component(NAV_COMP_ID_USB_PLD);

    _nav_usb_pld_view_hide();

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_dlg_default_msg_proc
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
static INT32 _nav_usb_pld_dlg_default_msg_proc(HANDLE_T            h_widget,
                                               UINT32              ui4_msg,
                                               VOID*               pv_param1,
                                               VOID*               pv_param2)
{
    INT32           i4_ret = NAVR_OK;
#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
#endif

    switch(ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;

            i4_ret = _nav_usb_pld_dlg_hide_timer_start();
            RET_ON_ERR(i4_ret);

            switch(ui4_keycode)
            {
                case BTN_CURSOR_LEFT:
                #ifdef APP_TTS_SUPPORT
                    c_memset(w2s_str, 0, sizeof(w2s_str));
                    c_uc_w2s_strcpy(w2s_str,NAV_TTS_TEXT(MLM_NAV_KEY_DIALOG_YES));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    break;
                #endif
                case BTN_CURSOR_RIGHT:
                #ifdef APP_TTS_SUPPORT
                    c_memset(w2s_str, 0, sizeof(w2s_str));
                    c_uc_w2s_strcpy(w2s_str,NAV_TTS_TEXT(MLM_NAV_KEY_DIALOG_NO));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    break;
                #endif
                case BTN_SELECT:
                    break;
                case BTN_EXIT:
                {
                    nav_hide_component(NAV_COMP_ID_USB_PLD);
                    _nav_usb_pld_view_hide();
                }
                    break;
                default:
                    nav_rcu_key_handler(ui4_keycode);
                    return NAVR_OK;
                }
                break;
        }

        default:
            break;
    }

    return a_ui_simple_dialog_default_msg_proc(h_widget,
                                               ui4_msg,
                                               pv_param1,
                                               pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_usb_pld_view_plg_dialog_show
 * Description:
 *      set dialog navigation.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_view_plg_dialog_show(VOID)
{
    INT32   i4_ret = NAVR_OK;
    GL_POINT_T t_begin_offset = {NAV_USB_PLD_OFFSET_X, 0};

    /* show dialog */
    i4_ret = nav_dialog_prompt_yes_no_dialog_ex(
                        NAV_DIALOG_ID_USB_PLG_DLG,
                        MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_USB_PLD_DLG_PLG_MSG),
                        MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_DIALOG_YES),
                        MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_DIALOG_NO),
                        UI_SIMPLE_DIALOG_STYLE_SMALL,
                        WGL_AS_CENTER_CENTER,
                        &t_begin_offset,
                        TRUE,
                        _nav_usb_pld_dlg_default_msg_proc,
                        _nav_usb_pld_dlg_yes_fct,
                        _nav_usb_pld_dlg_no_fct,
                        NULL,
                        NULL);
    RET_ON_ERR(i4_ret);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
    UTF16_T w2s_tmp_str[128] = {0};

    c_uc_w2s_strcpy(w2s_str,NAV_TTS_TEXT(MLM_NAV_KEY_USB_PLD_DLG_PLG_MSG));
    c_uc_w2s_strcpy(w2s_tmp_str,NAV_TTS_TEXT(MLM_NAV_KEY_DIALOG_YES));
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif
    i4_ret = nav_dialog_stop_hide_timer();
    RET_ON_ERR(i4_ret);

    i4_ret = _nav_usb_pld_dlg_hide_timer_start();
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_usb_pld_view_plg_dialog_show
 * Description:
 *      set dialog navigation.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_view_uplg_dialog_show(VOID)
{
    INT32   i4_ret = NAVR_OK;
    GL_POINT_T t_begin_offset = {NAV_USB_PLD_OFFSET_X, 0};
    UINT32     ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_UNKNOWN;
    SIZE_T z_size = ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE;
    UINT16 ui2_key = MLM_NAV_KEY_USB_PLD_DLG_UPLG_MSG;

    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_EXIT_REASON),
                       (VOID*) &ui4_exit_reason, &z_size);
    RET_ON_ERR(i4_ret);

    if (ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_REMOVE_USB == ui4_exit_reason)
    {
        ui2_key = MLM_NAV_KEY_USB_PLD_DLG_UPLG_MSG;
    }
    else if (ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_REMOVE_DLNA == ui4_exit_reason)
    {
        ui2_key = MLM_NAV_KEY_DLNA_PLD_DLG_UPLG_MSG;
    }

    /* show disconnected dialog */
    i4_ret = nav_dialog_prompt_msg_dialog(
                        NAV_DIALOG_ID_USB_UPLG_DLG,
                        MLM_NAV_TEXT(nav_get_mlm_lang_id(), ui2_key),
                        MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_DIALOG_OK),
                        &t_begin_offset,
                        _nav_usb_pld_dlg_default_msg_proc,
                        _nav_usb_pld_dlg_ok_fct);
    RET_ON_ERR(i4_ret);
#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
    UTF16_T w2s_tmp_str[128] = {0};

    c_uc_w2s_strcpy(w2s_str,NAV_TTS_TEXT(ui2_key));
    c_uc_w2s_strcpy(w2s_tmp_str,NAV_TTS_TEXT(MLM_NAV_KEY_DIALOG_OK));
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    g_ui4_uplg_usb_tts_play_id = a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif

    i4_ret = nav_dialog_stop_hide_timer();
    RET_ON_ERR(i4_ret);

    i4_ret = _nav_usb_pld_dlg_hide_timer_start();
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

#ifdef APP_TTS_SUPPORT
static VOID _nav_usb_pld_view_tts_cb_fct(
                                    VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3)
{
    DBG_LOG_PRINT(("nav usb pld view set banner tts enable %s,%d\n\r",__FILE__,__LINE__));
    set_banner_tts_enable(TRUE);
}


static VOID _nav_usb_pld_view_tts_nfy(TTS_STRING_STATE_E e_tts_str_state, UINT32 ui4_tts_play_id, VOID* pv_tag)
{
    if (TTS_STR_ST_PLAYED == e_tts_str_state &&
        g_ui4_uplg_usb_tts_play_id == ui4_tts_play_id)
    {
        nav_request_context_switch(_nav_usb_pld_view_tts_cb_fct,
                                    NULL,
                                    NULL,
                                    NULL);
    }
}
#endif



/*-----------------------------------------------------------------------------
 * Name
 *      _nav_usb_pld_view_init
 * Description:
 *      usb plugin detection view initialization.
 * Input arguments:
 *      pt_ctrl         pointer to struct _NAV_USB_PLD_HDLR_T
 *      h_canvas        canvas handle
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_view_init(
                    NAV_USB_PLD_HDLR_T*         pt_ctrl,
                    HANDLE_T                    h_canvas)
{
    INT32                    i4_ret = NAVR_OK;
    NAV_USB_PLD_VIEW_T*      pt_view = &t_g_nav_usb_pld_view;

    i4_ret = c_timer_create(&pt_view->h_hide_timer);
    RET_ON_ERR(i4_ret);

    pt_view->pt_ctrl = pt_ctrl;
    pt_view->h_canvas = h_canvas;
    pt_view->ui4_time_delay = NAV_USB_PLD_DLG_DEFAULT_TIMER_DELAY;
    pt_view->b_is_show = FALSE;
#ifdef APP_CAST_TV_MMP
    pt_view->h_toast_timer = NULL_HANDLE;
    pt_view->b_is_toast_show = FALSE;
#endif

#ifdef APP_TTS_SUPPORT
    i4_ret = a_app_tts_nfy_reg(_nav_usb_pld_view_tts_nfy, NULL);
    if (APP_TTSR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("[nav_usb_pld_view] Can't  reg tts nfy"));
    }
#endif


    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_view_deinit
 * Description:
 *      usb plugin detection view deinitialization.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_view_deinit (VOID)
{
    INT32                    i4_ret = NAVR_OK;
    NAV_USB_PLD_VIEW_T*      pt_view = &t_g_nav_usb_pld_view;

    if (NULL_HANDLE != pt_view->h_hide_timer)
    {
        i4_ret = c_timer_delete(pt_view->h_hide_timer);
        RET_ON_ERR(i4_ret);
    }

#ifdef APP_TTS_SUPPORT
    a_app_tts_nfy_unreg(_nav_usb_pld_view_tts_nfy);
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_view_hide
 * Description:
 *      hide UI.
 * Input arguments:
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_view_hide (VOID)
{
    INT32                    i4_ret = NAVR_OK;
    NAV_USB_PLD_VIEW_T*      pt_view = &t_g_nav_usb_pld_view;

    if (pt_view->b_is_show == FALSE)
    {
        return NAVR_NO_ACTION;
    }

#ifdef APP_TTS_SUPPORT
    /* reset banner tts flag */
    set_banner_tts_enable(TRUE);
#endif

    i4_ret = nav_dialog_hide();
    RET_ON_ERR(i4_ret);

    pt_view->b_is_show = FALSE;
    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);

    nav_return_activation(NAV_COMP_ID_USB_PLD);

    return NAVR_OK;
}

#ifdef APP_CAST_TV_MMP
/*----------------------------------------------------------------------------
 * Name: nav_usb_hide_toast_view
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID nav_usb_hide_toast_view(VOID)
{
    NAV_USB_PLD_VIEW_T*      pt_view = &t_g_nav_usb_pld_view;

    if(pt_view->b_is_toast_show)
    {
        a_wdk_toast_hide(FALSE,&tg_toast_param,&t_g_wdk_view);
        pt_view->b_is_toast_show = FALSE;
        if(pt_view->h_toast_timer)
        {
            c_timer_stop(pt_view->h_toast_timer);
            c_timer_delete(pt_view->h_toast_timer);
            pt_view->h_toast_timer = NULL_HANDLE;
        }
        nav_hide_component(NAV_COMP_ID_USB_PLD);
        nav_return_activation(NAV_COMP_ID_USB_PLD);

        /* If retail mode is running,just quit. */
        ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
        if((ACFG_RETAIL_MODE_HOME == t_retail_mode) && nav_usb_pld_get_retail_mode_status())
        {
            RETAIL_MODE_PARAM_T t_param;
            c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));

            t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_HOTKEY;
            t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
            t_param.t_launch_info.ui2_count = 15;

            a_nav_retail_mode_start(&t_param);
        }
    }
}
/*----------------------------------------------------------------------------
 * Name: _nav_usb_do_show_toast_view_timer
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_usb_do_show_toast_view_timer(VOID* pv_data1,
                                VOID* pv_data2,
                                VOID* pv_data3)
{
    nav_usb_hide_toast_view();
}

/*----------------------------------------------------------------------------
 * Name: _nav_usb_timer_show_toast_view_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_usb_timer_show_toast_view_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    nav_request_context_switch(_nav_usb_do_show_toast_view_timer,NULL, NULL,NULL);
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_string_toast_view
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_string_toast_view(VOID)
{
    INT32     i4_ret = 0;
    UTF16_T   w2s_txt[128] = {0};
    UINT16    ui2_lang = 0;
    ISO_639_LANG_T     s639_lang;
    NAV_USB_PLD_VIEW_T*      pt_view = &t_g_nav_usb_pld_view;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    RET_ON_ERR(i4_ret);

    ui2_lang = mlm_settings_s639_to_langidx(s639_lang);

    c_uc_w2s_strcpy(w2s_txt,MLM_SETTINGS_TEXT(ui2_lang,MLM_SETTINGS_KEY_MMP_REMOVE_TEXT));
    c_memset(&tg_toast_param,0,sizeof(WDK_TOAST_PARAM_T));
    tg_toast_param.e_toast_style = WDK_STRING_TOAST;
    tg_toast_param.w2s_str       = (VOID*)w2s_txt;
    tg_toast_param.pf_cb         = NULL;

    i4_ret = a_wdk_toast_init(pt_view->h_canvas,&tg_toast_param,&t_g_wdk_view);
    RET_ON_ERR(i4_ret);
    tg_toast_param.h_t_focus_handle = t_g_wdk_view.h_base_frm;

    i4_ret = a_wdk_toast_activate(FALSE,&tg_toast_param,&t_g_wdk_view);
    RET_ON_ERR(i4_ret);

    pt_view->b_is_toast_show = TRUE;

    a_banner_view_set_delay_show_banner(TRUE,5000);

    i4_ret = c_timer_create(&pt_view->h_toast_timer);
    if(i4_ret < 0)
    {
        DBG_ERROR(("<NAV_USB_PLD> c_timer_create fail,i4_ret=%d\r\n",i4_ret));
    }

    /* enable the show timer */
    i4_ret = c_timer_start(pt_view->h_toast_timer,
                            5000,
                            X_TIMER_FLAG_ONCE,
                            _nav_usb_timer_show_toast_view_fct,
                            NULL);
    if(i4_ret < 0)
    {
        DBG_ERROR(("<NAV_USB_PLD> Can't start show timer,i4_ret=%d\r\n",i4_ret));
    }

    return NAVR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_view_show
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_view_show (NAV_USB_PLD_PAGE_E e_page_id)
{
    INT32                    i4_ret = NAVR_OK;
    NAV_USB_PLD_VIEW_T*      pt_view = &t_g_nav_usb_pld_view;

    a_tv_net_send_cmd("\n:dtv_app_mtk,yahoo,:ui_show=yes\n");

    switch (e_page_id)
    {
        case NAV_USB_PLD_PAGE_PLG_DIALOG:
        {
            i4_ret = _nav_usb_pld_view_plg_dialog_show();
            RET_ON_ERR(i4_ret);
        }
            break;
        case NAV_USB_PLD_PAGE_UPLG_DIALOG:
        {
        #ifdef APP_CAST_TV_MMP
            _nav_usb_string_toast_view();
            break;
        #endif
            i4_ret = _nav_usb_pld_view_uplg_dialog_show();
            RET_ON_ERR(i4_ret);
        }
            break;
        default:
            break;
    }

    pt_view->b_is_show = TRUE;
    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_EXIST);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_view_is_key_handler
 * Description:
 *
 * Input arguments:
 *      UINT32
 * Output arguments:
 *      None
 * Returns:
 *      TRUE        Successful
 *      FALSE       Fail
 *---------------------------------------------------------------------------*/
static BOOL _nav_usb_pld_view_is_key_handler (UINT32     ui4_key_code)
{
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:
 *      nav_usb_pld_view_register_default_hdlr
 * Description:
 *      usb plugin view register.
 * Input arguments:
 *      NAV_USB_PLD_VIEW_HDLR_T*
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 nav_usb_pld_view_register_default_hdlr (NAV_USB_PLD_VIEW_HDLR_T*      pt_view_hdlr)
{
    if (NULL == pt_view_hdlr)
    {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init           = _nav_usb_pld_view_init;
    pt_view_hdlr->pf_deinit         = _nav_usb_pld_view_deinit;
    pt_view_hdlr->pf_hide           = _nav_usb_pld_view_hide;
    pt_view_hdlr->pf_show           = _nav_usb_pld_view_show;
    pt_view_hdlr->pf_is_key_handler = _nav_usb_pld_view_is_key_handler;

    return NAVR_OK;
}

#endif /* APP_NAV_USB_PLD */
