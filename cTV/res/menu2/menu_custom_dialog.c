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
 * $RCSfile: menu_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/21 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 1433fe1fd8b5fe1dfc2a58820b53a685 $
 *
 * Description:
 *         This file contains all the customizable code in menu.
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_irrc_btn_def.h"
#include "u_svctx.h"
#include "u_drv_cust.h"

#include "c_os.h"
#include "c_dbg.h"
#include "c_common.h"
#include "c_handle.h"
#include "c_cfg.h"
#include "c_fe.h"
#include "c_svctx.h"
#include "c_wgl.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_isl.h"
#include "app_util/a_ui.h"
#include "res/app_util/ui/ui_custom.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "res/menu2/menu_custom_dialog.h"
#include "res/menu2/menu_custom.h"

#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif

#ifdef APP_TTS_SUPPORT
#include "res/menu2/menu_mlm.h"
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "res/app_util/rmv_dev/a_rmv_dev_custom.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MAX_NOTIFY_CLIENT_NUM (16)
#define MENU_DIALOG_SCREEN_MODE_TIMER_DELAY     5000

typedef enum{
  CREATE_PIC_DLG = 0,/*For create pic mode warn dlg*/
  PIC_MODE_EDIT_DLG,/*For reset pic mode dlg && delete pic mode dlg*/
  COLOR_CALIBRATION_DLG,/*For reset color tuner dlg*/
  DLG_LAST_ENTRY
} PRE_DLG_T;

typedef struct __MENU_CUSTOM_DLG_DATA_T
{
    HANDLE_T                    h_parent;
    HANDLE_T                    h_dialog;
    HANDLE_T                    h_menu_current_focus;
    HANDLE_T                    h_hide_timer;
    UINT32                      ui4_timer_delay;
    MENU_CUSTOM_DIALOG_ID_T     e_dialog_id;
    BOOL                        b_is_show;
    BOOL                        b_is_inited;
    MENU_CUSTOM_DIALOG_LOOSELY_EXCLUSIVE_SET_NFY_CLIENT_T at_notify_client[MAX_NOTIFY_CLIENT_NUM];
    PRE_DLG_T                   e_pre_dlg;
}   _MENU_CUSTOM_DLG_DATA_T;

static BOOL  b_pre_page_is_warn_dlg = FALSE;
static UINT32 ui4_warn_page_dlg = 0;
#define MENU_DIALOG_DEFAULT_TIMER_DELAY     10000

static VOID _broadcast_msg(VOID);

/*-----------------------------------------------------------------------------
                           data declaraions
 ----------------------------------------------------------------------------*/
static _MENU_CUSTOM_DLG_DATA_T  t_g_menu_custom_dialog;
/*-----------------------------------------------------------------------------
                        function implementation
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:
 *      _menu_custom_dialog_hide
 * Description:
 *      hide menu custom dialog
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _menu_custom_dialog_hide(VOID)
{
    INT32                       i4_ret = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    if ((TRUE == pt_this->b_is_show)&&
        (NULL_HANDLE != pt_this->h_dialog))
    {
        if (pt_this->h_menu_current_focus != NULL_HANDLE)
        {
            i4_ret = c_wgl_set_focus(pt_this->h_menu_current_focus, WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        
        //i4_ret = a_ui_simple_dialog_hide(pt_this->h_dialog);
        //MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_focus(pt_this->h_menu_current_focus, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        if ( pt_this->b_is_show == TRUE)
        {
            i4_ret = a_ui_simple_dialog_hide(pt_this->h_dialog);
            MENU_LOG_ON_FAIL(i4_ret);

            pt_this->b_is_show   = FALSE;
        }

        i4_ret = a_ui_simple_dialog_repaint(pt_this->h_parent);
        MENU_LOG_ON_FAIL(i4_ret);

        /* stop the timer */
        i4_ret = c_timer_stop(pt_this->h_hide_timer);
        MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_ZOOM_MODE_SUPPORT
        a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
#endif
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _menu_custom_dialog_hide_timer_fct
 * Description:
 *      menu custom dialog hide timer notify
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _menu_custom_dialog_hide_timer_fct(VOID*        pv_data,
                                               SIZE_T       z_data_size)
{
    INT32       i4_ret = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    i4_ret = _menu_custom_dialog_hide();
    MENU_LOG_ON_FAIL(i4_ret);
    if(pt_this->e_pre_dlg == CREATE_PIC_DLG)
    {
        i4_ret = a_create_pic_mode_warn_dlg_show();
        MENU_LOG_ON_FAIL(i4_ret); 
        pt_this->e_pre_dlg = DLG_LAST_ENTRY;
    }
    else if(pt_this->e_pre_dlg == PIC_MODE_EDIT_DLG)
    {
        i4_ret = menu_page_pic_mode_edit_dlg_show();
        MENU_LOG_ON_FAIL(i4_ret); 
        pt_this->e_pre_dlg = DLG_LAST_ENTRY;
    }
    else if(pt_this->e_pre_dlg == COLOR_CALIBRATION_DLG)
    {
        i4_ret = menu_page_color_calibration_dlg_show();
        MENU_LOG_ON_FAIL(i4_ret); 
        pt_this->e_pre_dlg = DLG_LAST_ENTRY;
    }
    if (b_pre_page_is_warn_dlg)
    {
    
#ifdef APP_MENU_DLG_COEXIST            
        i4_ret=menu_set_page_hide(FALSE); 
        MENU_LOG_ON_FAIL(i4_ret);
#endif            
        menu_nav_go(ui4_warn_page_dlg, NULL);     
        b_pre_page_is_warn_dlg = FALSE; 
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _menu_custom_dialog_hide_timer_nfy
 * Description:
 *      menu custom dialog hide timer notify
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _menu_custom_dialog_hide_timer_nfy(HANDLE_T        h_timer,
                                               VOID*           pv_tag)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = menu_async_invoke(_menu_custom_dialog_hide_timer_fct, NULL, 0, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _menu_custom_dialog_hide_timer_start
 * Description:
 *      start menu custom dialog timer
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _menu_custom_dialog_hide_timer_start(UINT32    ui4_time)
{
    INT32                       i4_ret = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    if (NULL_HANDLE != pt_this->h_hide_timer)
    {
        i4_ret = c_timer_start(pt_this->h_hide_timer,
                              ui4_time,
                              X_TIMER_FLAG_ONCE,
                              _menu_custom_dialog_hide_timer_nfy,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      menu_custom_dialog_default_msg_proc
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
extern INT32 _menu_custom_dialog_default_msg_proc(HANDLE_T            h_widget,
                                                  UINT32              ui4_msg,
                                                  VOID*               pv_param1,
                                                  VOID*               pv_param2)
{
    INT32                       i4_ret = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;
#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
#endif

    switch(ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;

            i4_ret = _menu_custom_dialog_hide_timer_start(pt_this->ui4_timer_delay);
            MENU_LOG_ON_FAIL(i4_ret);

            switch(ui4_keycode)
            {
                case BTN_CURSOR_LEFT:
                #ifdef APP_TTS_SUPPORT
                    c_memset(w2s_str, 0, sizeof(w2s_str));
                    c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_YES));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    break;
                #endif
                case BTN_CURSOR_RIGHT:
                #ifdef APP_TTS_SUPPORT
                    c_memset(w2s_str, 0, sizeof(w2s_str));
                    c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_NO));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    break;
                #endif
                case BTN_SELECT:
                    break;
                case BTN_EXIT:
                {
                    i4_ret = _menu_custom_dialog_hide();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;
                default:
                    break;
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
 * Name:
 *      _menu_custom_dialog_usb_popup_yes_fct
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static VOID _menu_custom_dialog_usb_popup_yes_fct(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    if (pt_this->b_is_show == TRUE)
    {
        i4_ret = a_ui_simple_dialog_hide(pt_this->h_dialog);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_this->b_is_show = FALSE;

#ifdef APP_ZOOM_MODE_SUPPORT
        a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
#endif
    }

    i4_ret = a_ui_simple_dialog_repaint(pt_this->h_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    /* stop the timer */
    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    RMV_DEV_MNT_POINT_INFO_T t_mount_point_info;
    
    c_memset(&t_mount_point_info, 0, sizeof(t_mount_point_info));
    a_rmv_dev_get_mount_point_info(&t_mount_point_info);

    i4_ret = a_rmv_dev_set_active_mnt_pnt(t_mount_point_info.ui4_last_effective_idx);
    MENU_LOG_ON_FAIL(i4_ret);

    a_menu_custom_page_mmp_media_set_enter_flag(TRUE);
    i4_ret = menu_pm_short_cut_show(MENU_SHORT_CUT_MMP_MEDIA_TYPE);
    MENU_LOG_ON_FAIL(i4_ret);
    
    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _menu_custom_dialog_usb_popup_no_fct
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static VOID _menu_custom_dialog_usb_popup_no_fct(VOID)
{
    INT32       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    i4_ret = _menu_custom_dialog_hide();
    MENU_LOG_ON_FAIL(i4_ret);
	
	if(pt_this->e_pre_dlg == CREATE_PIC_DLG)
	{
		i4_ret = a_create_pic_mode_warn_dlg_show();
		MENU_LOG_ON_FAIL(i4_ret); 
		pt_this->e_pre_dlg = DLG_LAST_ENTRY;
	}
    else if(pt_this->e_pre_dlg == PIC_MODE_EDIT_DLG)
    {
        i4_ret = menu_page_pic_mode_edit_dlg_show();
        MENU_LOG_ON_FAIL(i4_ret); 
        pt_this->e_pre_dlg = DLG_LAST_ENTRY;
    }
    else if(pt_this->e_pre_dlg == COLOR_CALIBRATION_DLG)
    {
        i4_ret = menu_page_color_calibration_dlg_show();
        MENU_LOG_ON_FAIL(i4_ret); 
        pt_this->e_pre_dlg = DLG_LAST_ENTRY;
    }
    if (b_pre_page_is_warn_dlg)
    {
        
#ifdef APP_MENU_DLG_COEXIST            
        i4_ret=menu_set_page_hide(FALSE); 
        MENU_LOG_ON_FAIL(i4_ret);
#endif            
        menu_nav_go(ui4_warn_page_dlg, NULL);     
        b_pre_page_is_warn_dlg = FALSE; 
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _menu_custom_dialog_show_usb_popup
 *
 * Description:
 *      Show the usb popup dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _menu_custom_dialog_show_usb_popup(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_dialog, MENU_TEXT(MLM_MENU_KEY_USB_PLD_DLG_PLG_MSG));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_dialog, MENU_TEXT(MLM_MENU_KEY_YES));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_no_text(pt_this->h_dialog, MENU_TEXT(MLM_MENU_KEY_NO));
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_get_focus(&pt_this->h_menu_current_focus);
	MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_focus(pt_this->h_dialog, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    if (pt_this->b_is_show == FALSE)
    {
        i4_ret = a_ui_simple_dialog_show(pt_this->h_dialog);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_this->b_is_show = TRUE;
    }

    c_wgl_float(pt_this->h_dialog, TRUE, FALSE);
#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
    UTF16_T w2s_tmp_str[128] = {0};

    c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_USB_PLD_DLG_PLG_MSG));
    c_uc_w2s_strcpy(w2s_tmp_str,MENU_TTS_TEXT(MLM_MENU_KEY_YES));
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif

    i4_ret = c_wgl_repaint(pt_this->h_parent, NULL, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_custom_dialog_hide_timer_start(pt_this->ui4_timer_delay);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_custom_dialog_hide_usb_popup
 *
 * Description:
 *      Hide the usb popup dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _menu_custom_dialog_hide_usb_popup(VOID)
{
    INT32       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    c_wgl_float(pt_this->h_dialog, FALSE, FALSE);

    i4_ret = _menu_custom_dialog_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_custom_dialog_show_usb_popup
 *
 * Description:
 *      Create the usb popup dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _menu_custom_dialog_create_usb_popup(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    GL_POINT_T t_begin_offset = {MENU_USB_PLD_OFFSET_X, 0};

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = pt_this->h_parent;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = _menu_custom_dialog_usb_popup_no_fct;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _menu_custom_dialog_usb_popup_yes_fct;
    t_simple_dialog_init.pf_wdgt_proc                   = _menu_custom_dialog_default_msg_proc;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.pt_begin_offset                = &t_begin_offset;
    t_simple_dialog_init.b_one_btn_mode                 = FALSE;
    t_simple_dialog_init.b_default_answer               = TRUE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &pt_this->h_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->e_dialog_id = MENU_CUSTOM_DIALOG_ID_USB_POPUP;
    pt_this->b_is_show   = FALSE;

    return MENUR_OK;
}

static INT32 _menu_custom_dialog_show_scrn_mode_warn(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_dialog, MENU_TEXT(MLM_MENU_KEY_SCRN_MODE_WARNING));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Dialog no need to get focus */
    pt_this->h_menu_current_focus = NULL_HANDLE;

    //i4_ret = a_ui_simple_dialog_set_focus(pt_this->h_dialog, FALSE);
    //MENU_LOG_ON_FAIL(i4_ret);

    if (pt_this->b_is_show == FALSE)
    {
        i4_ret = a_ui_simple_dialog_show(pt_this->h_dialog);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_this->b_is_show = TRUE;
    }

    c_wgl_float(pt_this->h_dialog, TRUE, FALSE);

    i4_ret = c_wgl_repaint(pt_this->h_parent, NULL, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_custom_dialog_hide_timer_start(pt_this->ui4_timer_delay);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _menu_custom_dialog_hide_scrn_mode_warn(VOID)
{
    INT32       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    c_wgl_float(pt_this->h_dialog, FALSE, FALSE);

    i4_ret = _menu_custom_dialog_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _menu_custom_dialog_create_scrn_mode_warning(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    GL_POINT_T t_begin_offset = {MENU_SCRN_MODE_MSG_OFFSET_X, 0};

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_WARNING_MSG;
    t_simple_dialog_init.h_parent                       = pt_this->h_parent;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = NULL;
    t_simple_dialog_init.pf_wdgt_proc                   = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.pt_begin_offset                = &t_begin_offset;
    t_simple_dialog_init.b_one_btn_mode                 = FALSE;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_info_icon                    = TRUE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &pt_this->h_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->ui4_timer_delay = MENU_DIALOG_SCREEN_MODE_TIMER_DELAY;
    pt_this->e_dialog_id = MENU_CUSTOM_DIALOG_ID_SCREEN_MODE_WARN;
    pt_this->b_is_show   = FALSE;

    return MENUR_OK;
}

static INT32 _menu_custom_dialog_show_pic_mode_name_exceeding(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_dialog, MENU_TEXT(MLM_MENU_KEY_MENU_CREATE_PIC_MODE_NAME_EXCEEDING));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_dialog, MENU_TEXT(MLM_MENU_KEY_YES));
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_get_focus(&pt_this->h_menu_current_focus);
	MENU_LOG_ON_FAIL(i4_ret);

    if (pt_this->b_is_show == FALSE)
    {
        i4_ret = a_ui_simple_dialog_show(pt_this->h_dialog);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_this->b_is_show = TRUE;
    }

    c_wgl_float(pt_this->h_dialog, TRUE, FALSE);

    i4_ret = a_ui_simple_dialog_set_focus(pt_this->h_dialog, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_this->h_parent, NULL, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    UTF16_T  w2s_str[128] = {0};
    c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_MENU_CREATE_PIC_MODE_NAME_EXCEEDING), 127);
    c_uc_w2s_strncat(w2s_str, MENU_TEXT(MLM_MENU_KEY_YES), 127-c_uc_w2s_strlen(w2s_str));
    a_app_tts_play(w2s_str, 128);
#endif

    //i4_ret = _menu_custom_dialog_hide_timer_start(pt_this->ui4_timer_delay);
    //MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _menu_custom_dialog_hide_pic_mode_name_exceeding(VOID)
{
    INT32       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    c_wgl_float(pt_this->h_dialog, FALSE, FALSE);

    i4_ret = _menu_custom_dialog_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static VOID _menu_custom_dialog_pic_mode_name_exceeding_yes(VOID)
{
    _menu_custom_dialog_hide_pic_mode_name_exceeding();
    a_create_pic_mode_name_exceeding_yes_fct();
}

static INT32 _menu_custom_dialog_create_pic_mode_name_exceeding(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    GL_POINT_T t_begin_offset = {MENU_SCRN_MODE_MSG_OFFSET_X, 0};

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = pt_this->h_parent;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _menu_custom_dialog_pic_mode_name_exceeding_yes;
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.pt_begin_offset                = &t_begin_offset;
    t_simple_dialog_init.b_one_btn_mode                 = TRUE;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_info_icon                    = TRUE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &pt_this->h_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->ui4_timer_delay = MENU_DIALOG_SCREEN_MODE_TIMER_DELAY;
    pt_this->e_dialog_id = MENU_CUSTOM_DIALOG_ID_PIC_MODE_NAME_EXCEEDING;
    pt_this->b_is_show   = FALSE;

    return MENUR_OK;

}

#ifdef APP_TTS_SUPPORT
static INT32 _menu_custom_dialog_hide_change_to_pcm(VOID)
{
    INT32       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    c_wgl_float(pt_this->h_dialog, FALSE, FALSE);

    i4_ret = _menu_custom_dialog_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _menu_custom_dialog_show_change_to_pcm(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_dialog, MENU_TEXT(MLM_MENU_KEY_MENU_DIGITAL_AUDIO_CHAGE_TO_PCM));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Dialog no need to get focus */
    pt_this->h_menu_current_focus = NULL_HANDLE;

    if (pt_this->b_is_show == FALSE)
    {
        i4_ret = a_ui_simple_dialog_show(pt_this->h_dialog);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_this->b_is_show = TRUE;
    }

    c_wgl_float(pt_this->h_dialog, TRUE, FALSE);

    i4_ret = c_wgl_repaint(pt_this->h_parent, NULL, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_custom_dialog_hide_timer_start(pt_this->ui4_timer_delay);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _menu_custom_dialog_create_change_to_pcm(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    GL_POINT_T t_begin_offset = {MENU_SCRN_MODE_MSG_OFFSET_X, 0};

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY;
    t_simple_dialog_init.h_parent                       = pt_this->h_parent;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = NULL;
    t_simple_dialog_init.pf_wdgt_proc                   = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.pt_begin_offset                = &t_begin_offset;
    t_simple_dialog_init.b_one_btn_mode                 = FALSE;
    t_simple_dialog_init.b_default_answer               = TRUE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &pt_this->h_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->ui4_timer_delay = MENU_DIALOG_SCREEN_MODE_TIMER_DELAY;
    pt_this->e_dialog_id = MENU_CUSTOM_DIALOG_ID_CHANGE_TO_PCM;
    pt_this->b_is_show   = FALSE;

    return MENUR_OK;
}
#endif  

/*----------------------------------------------------------------------------
 * Name: _menu_custom_dialog_destroy
 *
 * Description:
 *      Destroy the custom dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _menu_custom_dialog_destroy(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    if (MENU_CUSTOM_DIALOG_ID_NULL != pt_this->e_dialog_id &&
        NULL_HANDLE != pt_this->h_dialog)
    {
        if ( pt_this->b_is_show == TRUE)
        {
            i4_ret = a_ui_simple_dialog_hide(pt_this->h_dialog);
            MENU_LOG_ON_FAIL(i4_ret);

            pt_this->b_is_show   = FALSE;
        }

        i4_ret = a_ui_simple_dialog_repaint(pt_this->h_dialog);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_ui_simple_dialog_destory(pt_this->h_dialog);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_timer_stop(pt_this->h_hide_timer);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_this->h_dialog    = NULL_HANDLE;
        pt_this->e_dialog_id = MENU_CUSTOM_DIALOG_ID_NULL;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_custom_dialog_create
 *
 * Description:
 *      Create the custom dialog under menu app.
 * Inputs:
 *      MENU_CUSTOM_DIALOG_ID_T     custom dialog id.
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _menu_custom_dialog_create(MENU_CUSTOM_DIALOG_ID_T    e_dialog_id)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    if (MENU_CUSTOM_DIALOG_ID_NULL != pt_this->e_dialog_id &&
        NULL_HANDLE != pt_this->h_dialog)
    {
        i4_ret = _menu_custom_dialog_destroy();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    switch(e_dialog_id)
    {
        case MENU_CUSTOM_DIALOG_ID_USB_POPUP:
        {
            i4_ret = _menu_custom_dialog_create_usb_popup();
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }
        case MENU_CUSTOM_DIALOG_ID_SCREEN_MODE_WARN:
        {
            DBG_LOG_PRINT(("%s() Line %d =========\n",__FUNCTION__,__LINE__));
            i4_ret = _menu_custom_dialog_create_scrn_mode_warning();
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }
        case MENU_CUSTOM_DIALOG_ID_PIC_MODE_NAME_EXCEEDING:
        {
            i4_ret = _menu_custom_dialog_create_pic_mode_name_exceeding();
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }
#ifdef APP_TTS_SUPPORT
        case MENU_CUSTOM_DIALOG_ID_CHANGE_TO_PCM:
        {
            i4_ret = _menu_custom_dialog_create_change_to_pcm();
            MENU_LOG_ON_FAIL(i4_ret);
        }
#endif
        default:
            break;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_custom_dialog_init
 *
 * Description:
 *      Initialize the custom dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _menu_custom_dialog_init(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    if (!pt_this->b_is_inited)
    {
        c_memset(&t_g_menu_custom_dialog, 0, sizeof(_MENU_CUSTOM_DLG_DATA_T));

        pt_this->ui4_timer_delay = MENU_DIALOG_DEFAULT_TIMER_DELAY;

        i4_ret = menu_pm_get_root_frm(&pt_this->h_parent);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_timer_create(&pt_this->h_hide_timer);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_this->b_is_inited = TRUE;
    }

    return MENUR_OK;

}

/*----------------------------------------------------------------------------
 * Name: menu_custom_dialog_show
 *
 * Description:
 *      Show the custom dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
extern INT32 menu_custom_dialog_show(MENU_CUSTOM_DIALOG_ID_T    e_dialog_id)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;
    UINT32                      ui4_cnt_page = 0;
    b_pre_page_is_warn_dlg = FALSE; 

    pt_this->e_pre_dlg = DLG_LAST_ENTRY;

	if(a_create_pic_mode_warn_dlg_is_show())
	{
		i4_ret = a_create_pic_mode_warn_dlg_hide();
		MENU_LOG_ON_FAIL(i4_ret); 
		pt_this->e_pre_dlg = CREATE_PIC_DLG;
	}
    else if(menu_page_pic_mode_edit_dlg_is_show())
    {
        i4_ret = menu_page_pic_mode_edit_dlg_hide();
        MENU_LOG_ON_FAIL(i4_ret); 
        pt_this->e_pre_dlg = PIC_MODE_EDIT_DLG;
    }
    else if(menu_page_color_calibration_dlg_is_show())
    {
        i4_ret = menu_page_color_calibration_dlg_hide();
        MENU_LOG_ON_FAIL(i4_ret); 
        pt_this->e_pre_dlg = COLOR_CALIBRATION_DLG;
    }
    i4_ret = menu_nav_get_crnt_page(&ui4_warn_page_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_cnt_page = ui4_warn_page_dlg;
    
    if (menu_page_is_reset_page(ui4_warn_page_dlg))
    {
        menu_nav_back();
        b_pre_page_is_warn_dlg = TRUE;      
    }
    if (!pt_this->b_is_inited)
    {
        i4_ret = _menu_custom_dialog_init();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if (pt_this->e_dialog_id != e_dialog_id)
    {
        i4_ret = _menu_custom_dialog_destroy();
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = _menu_custom_dialog_create(e_dialog_id);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    switch(e_dialog_id)
    {
        case MENU_CUSTOM_DIALOG_ID_USB_POPUP:
        {
            /* we do not need to show dialog when mmp side menu is showing */
            if ((ui4_g_menu_page_mmp_dev_list != ui4_cnt_page)&&
                (ui4_g_menu_page_mmp_media_type != ui4_cnt_page) &&
                //(ui4_g_menu_page_blank_scrn != ui4_cnt_page) && 
                (menu_simple_dialog_page_is_show() == FALSE) &&
                (menu_clear_memory_pwd_is_show() == FALSE) &&
                (menu_scr_mode_show() == FALSE) &&
                t_g_menu_is_scanning == FALSE)
            {
                _broadcast_msg();
                
                i4_ret = _menu_custom_dialog_show_usb_popup();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            
            break;
        }
        case MENU_CUSTOM_DIALOG_ID_SCREEN_MODE_WARN:
        {
            _broadcast_msg();
                
            i4_ret = _menu_custom_dialog_show_scrn_mode_warn();
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }
        case MENU_CUSTOM_DIALOG_ID_PIC_MODE_NAME_EXCEEDING:
        {
            _broadcast_msg();

            i4_ret = _menu_custom_dialog_show_pic_mode_name_exceeding();
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }
#ifdef APP_TTS_SUPPORT
        case MENU_CUSTOM_DIALOG_ID_CHANGE_TO_PCM:
        {
            _broadcast_msg();

            i4_ret = _menu_custom_dialog_show_change_to_pcm();
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }
#endif
        default:
            break;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_custom_dialog_hide
 *
 * Description:
 *      Hide the custom dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
extern INT32 menu_custom_dialog_hide(MENU_CUSTOM_DIALOG_ID_T    e_dialog_id)
{
    INT32                       i4_ret  = MENUR_OK;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    if (!pt_this->b_is_inited ||
        pt_this->e_dialog_id != e_dialog_id)
    {
        return MENUR_OK;
    }

    switch(e_dialog_id)
    {
        case MENU_CUSTOM_DIALOG_ID_USB_POPUP:
        {
            i4_ret = _menu_custom_dialog_hide_usb_popup();
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }
        case MENU_CUSTOM_DIALOG_ID_SCREEN_MODE_WARN:
        {
            i4_ret = _menu_custom_dialog_hide_scrn_mode_warn();
            MENU_LOG_ON_FAIL(i4_ret);
            
            break;
        }
        case MENU_CUSTOM_DIALOG_ID_PIC_MODE_NAME_EXCEEDING:
        {
            i4_ret = _menu_custom_dialog_hide_pic_mode_name_exceeding();
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }
#ifdef APP_TTS_SUPPORT
        case MENU_CUSTOM_DIALOG_ID_CHANGE_TO_PCM:
        {
            i4_ret = _menu_custom_dialog_hide_change_to_pcm();
            MENU_LOG_ON_FAIL(i4_ret);
        }
#endif
        default:
            break;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_custom_dialog_init
 *
 * Description:
 *      Initialize the custom dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
extern INT32 menu_custom_dialog_init(VOID)
{
    INT32       i4_ret  = MENUR_OK;

    i4_ret = _menu_custom_dialog_init();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

INT32 menu_custom_dialog_hide_dialog(VOID)
{
	INT32       i4_ret  = MENUR_OK;
	_MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;
	
	i4_ret = c_timer_stop(pt_this->h_hide_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    if(pt_this->b_is_show == TRUE)
    {
    	i4_ret = a_ui_simple_dialog_hide(pt_this->h_dialog);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_this->b_is_show = FALSE;
    }

#ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
#endif
    menu_tos_dialog_hide(TRUE);

	return MENUR_OK;
}

static VOID _broadcast_msg(VOID)
{
    UINT16            ui2_i    = 0;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;

    for (ui2_i = 0 ;
         ui2_i < (UINT16)MAX_NOTIFY_CLIENT_NUM;
         ui2_i++)
    {
        if (pt_this->at_notify_client[ui2_i].pf_nfy)
        {
            pt_this->at_notify_client[ui2_i].pf_nfy(
                pt_this->at_notify_client[ui2_i].pv_tag,
                (VOID*)pt_this->at_notify_client[ui2_i].ui4_nfy_id);
        }
    }
}

INT32 menu_custom_dialog_loosely_exclusive_set_register(
                  menu_custom_dialog_loosely_exclusive_set_nfy_fct pf_nfy,
                  VOID* pv_tag,
                  UINT32* pui4_nfy_id)
{
    INT32       i4_ret  = MENUR_OK;
    UINT16            ui2_i    = 0;
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;
    BOOL     b_found = FALSE;

    if ((NULL == pf_nfy) || (NULL == pui4_nfy_id))
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,invalid arg\n", __FILE__, __FUNCTION__, __LINE__));
        return MENUR_INV_ARG;
    }

    for (ui2_i = 0 ;
         ui2_i < (UINT16)MAX_NOTIFY_CLIENT_NUM;
         ui2_i++)
    {
        if (pt_this->at_notify_client[ui2_i].pf_nfy == NULL)
        {
            pt_this->at_notify_client[ui2_i].pf_nfy = pf_nfy;
            pt_this->at_notify_client[ui2_i].pv_tag = pv_tag;
            pt_this->at_notify_client[ui2_i].ui4_nfy_id = ui2_i;
            *pui4_nfy_id = ui2_i;
            b_found = TRUE;
            break;
        }
    }

    if (b_found)
    {
        i4_ret  = MENUR_OK;
    }
    else
    {
        i4_ret  = MENUR_FAIL;
    }
         
    return i4_ret;
}

INT32 menu_custom_dialog_loosely_exclusive_set_unregister(UINT32 ui4_nfy_id)
{
    _MENU_CUSTOM_DLG_DATA_T*    pt_this = &t_g_menu_custom_dialog;
    INT32 i4_ret = MENUR_FAIL;
    
    if (ui4_nfy_id >= (UINT32)MAX_NOTIFY_CLIENT_NUM)
    {
        return MENUR_INV_ARG;
    }

    if (pt_this->at_notify_client[ui4_nfy_id].pf_nfy)
    {
        pt_this->at_notify_client[ui4_nfy_id].pf_nfy = NULL;
        pt_this->at_notify_client[ui4_nfy_id].pv_tag = NULL;
        pt_this->at_notify_client[ui4_nfy_id].ui4_nfy_id = 1024;
        i4_ret = MENUR_OK;
    }

    return i4_ret;
}

