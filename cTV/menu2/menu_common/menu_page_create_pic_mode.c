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
 * $RCSfile: menu_page_nw_pwd.c,v  $
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
#include "u_drv_cust.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_page_animation.h"
#include "app_util/a_cfg.h"
#include "app_util/a_drv_interface.h"

#include "wdk/a_vkb.h"
#include "wdk/a_wdk.h"
#include "res/wdk/a_vkb_custom.h"
#include "wdk/vkb/vkb.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_video.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/menu2/menu_custom.h"
#include "res/menu2/menu_custom_dialog.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "menu2/menu_dbg.h"

#ifdef LINUX_AUTO_TEST
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#define save_pic_mode_file  "test_save_pic_mode_ok"
#endif

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/

#define CREATE_PIC_MODE_NAME_MAX_LEN            (16)

#define CREATE_PIC_MODE_SAVE_BTN_X              (FRAME_LEFT_RIGHT_INTV)
#define CREATE_PIC_MODE_SAVE_BTN_Y              (420)
#define CREATE_PIC_MODE_SAVE_BTN_W              (MENU_ITEM_V_WIDE - FRAME_LEFT_RIGHT_INTV*2)
#define CREATE_PIC_MODE_SAVE_BTN_H              (MENU_ITEM_V_HEIGHT)

#define CREATE_PIC_MODE_GUIDE_TEXT_X            (5)
#define CREATE_PIC_MODE_GUIDE_TEXT_Y            (5)
#define CREATE_PIC_MODE_GUIDE_TEXT_W            (CONTENT_W -60)
#define CREATE_PIC_MODE_GUIDE_TEXT_H            (60)



/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct _CREATE_PIC_MODE
{
    HANDLE_T     h_cnt_frm;
    HANDLE_T     h_eb_name;
    HANDLE_T     h_vkb;
    HANDLE_T     h_save_btn;
    HANDLE_T     h_guide_text1;
    HANDLE_T     h_vkb_last_focus;
    HANDLE_T     h_warning_dlg;
    HANDLE_T     h_menu_current_focus;
    BOOL         b_vkb_showed;
    BOOL         b_finish;
    BOOL         b_timer_result;
    UINT8        ui1_animation_count;
    CHAR         s_input_buf[CREATE_PIC_MODE_NAME_MAX_LEN];
    UINT32       ui4_nw_nfy_id;
    BOOL         b_this_page_show;
    BOOL         b_is_dlg_show;
    BOOL         b_save_enable;
    BOOL         b_latin_selected;
    HANDLE_T     h_create_pic_mode_handle;
    UINT32       ui4_cur_page_id;

}CREATE_PIC_MODE;

static UINT8        ui1_g_ssid_scan_count = 0;

static UINT16       g_aui2_idx_map[ACFG_PRE_SET_PIC_MODE_NUM+ACFG_CUST_SET_PIC_MODE_NUM]={0,1,2,3,4,5};
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_page_create_pic_mode;
static  CREATE_PIC_MODE    t_create_pic_mode_page_data;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _eb_name_set_text(
                    CHAR*                   s_txt,
                    BOOL                    b_repaint);

static INT32 _show_create_pic_mode_vkb(VOID);

/*----------------------------------------------------------------------------
 * Name: a_create_pic_mode_warn_dlg_hide
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
INT32 a_create_pic_mode_warn_dlg_hide(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;

    i4_ret = a_ui_simple_dialog_hide(pt_page_data->h_warning_dlg);
    MENU_LOG_ON_FAIL(i4_ret);
    pt_page_data->b_is_dlg_show  = FALSE;
    c_wgl_float(pt_page_data->h_warning_dlg,FALSE,FALSE);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_create_pic_mode_warn_dlg_is_show
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
BOOL a_create_pic_mode_warn_dlg_is_show(VOID)
{
    return t_create_pic_mode_page_data.b_is_dlg_show;
}

/*----------------------------------------------------------------------------
 * Name: a_create_pic_mode_warn_dlg_show
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
INT32 a_create_pic_mode_warn_dlg_show(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;

    i4_ret = a_ui_simple_dialog_set_text(pt_page_data->h_warning_dlg,
                                                  MENU_TEXT(MLM_MENU_KEY_MENU_CREATE_PIC_MODE_WARN_MSG));
    MENU_LOG_ON_FAIL(i4_ret);


    if(pt_page_data->h_menu_current_focus == NULL_HANDLE)
    {
        i4_ret = c_wgl_get_focus(&pt_page_data->h_menu_current_focus);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = a_ui_simple_dialog_show(pt_page_data->h_warning_dlg);
    MENU_LOG_ON_FAIL(i4_ret);
    c_wgl_float(pt_page_data->h_warning_dlg,TRUE,FALSE);
    a_ui_simple_dialog_set_focus(pt_page_data->h_warning_dlg, TRUE);
    a_ui_simple_dialog_repaint(pt_page_data->h_warning_dlg);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
    UTF16_T w2s_tmp_str[128] = {0};

    c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_MENU_CREATE_PIC_MODE_WARN_MSG));
    c_uc_w2s_strcpy(w2s_tmp_str,MENU_TTS_TEXT(MLM_MENU_KEY_OK));
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif
    pt_page_data->b_is_dlg_show = TRUE;

    return MENUR_OK;
}

VOID a_create_pic_mode_name_exceeding_yes_fct(VOID)
{
    INT32  i4_ret;
    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;

    MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_page_data->h_vkb,
                                      VKB_CMD_CLEAR_TEXT,
                                      (VOID*)NULL,
                                      (VOID*)NULL));

    i4_ret = a_vkb_set_focus(pt_page_data->h_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_vkb_repaint(pt_page_data->h_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
    MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
    pt_page_data->b_save_enable = FALSE;

}

/*----------------------------------------------------------------------------
 * Name: _update_ui
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
static INT32 _update_ui(VOID)
{
    INT32       i4_ret;
    UINT16      ui1_model_idx = 0;
    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;
    UINT16  ui2_count = 0;
    GL_RECT_T                   t_rect = {0};
    HANDLE_T                    h_last_shadow_item = NULL_HANDLE;

    /*Adjust last shadow position*/
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = CREATE_PIC_MODE_SAVE_BTN_Y + CREATE_PIC_MODE_SAVE_BTN_H + CONTENT_Y;
    t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_count = get_cust_picture_mode_num();
    if(ui2_count < (ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM_EX))
    {
        /*Save TXT*/
        i4_ret = c_wgl_do_cmd(pt_page_data->h_save_btn,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_LOCK_PIC_MODE_SAVE)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_LOCK_PIC_MODE_SAVE))));
        i4_ret = c_wgl_set_visibility(pt_page_data->h_save_btn, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
        #if 0
        i4_ret = c_wgl_set_visibility(pt_page_data->h_guide_text1, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
        #endif

        /*set edit box*/
        i4_ret = _eb_name_set_text(pt_page_data->s_input_buf, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        if (0 == ui1_model_idx)
        {
            i4_ret = _show_create_pic_mode_vkb();
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else if(1 == ui1_model_idx)
        {

            i4_ret = c_wgl_set_visibility(pt_page_data->h_eb_name, WGL_SW_NORMAL);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=  a_vkb_set_visibility(pt_page_data->h_vkb,FALSE);
            MENU_LOG_ON_FAIL(i4_ret);

            pt_page_data->b_vkb_showed = FALSE;
        }
        /* Change the menu title */
        menu_main_set_title(MLM_MENU_KEY_MENU_ITEM_CREATE_PIC_MODE);
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_CREATE_PIC_MODE_VKB_EX));
    }
    else
    {
        DBG_INFO(("\n=====create pic mode  pic mode num >= 16=========%d\n",__LINE__));
        /* set visibility */
        i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                    WGL_SW_HIDE_RECURSIVE);
        MENU_LOG_ON_FAIL(i4_ret);
        a_create_pic_mode_warn_dlg_show();
    }


    return MENUR_OK;

}


/*----------------------------------------------------------------------------
 * Name: _show_create_pic_mode_vkb
 *
 * Description:
 *  Update the cust lbl name to the virtual keyboard UI.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _show_create_pic_mode_vkb(VOID)
{
    CREATE_PIC_MODE*    pt_page_data = &t_create_pic_mode_page_data;
    INT32               i4_ret = MENUR_OK;
    UTF16_T             w2s_star_txt[CREATE_PIC_MODE_NAME_MAX_LEN] = {0};    /* input text value: UTF16_T */

    /* set max char num to MAX_LBL_NAME_LEN */
    a_vkb_do_cmd (pt_page_data->h_vkb,
                   VKB_CMD_SET_MAX_CHAR_NUM,
                   (VOID*) CREATE_PIC_MODE_NAME_MAX_LEN,
                   NULL);

    c_memset(w2s_star_txt, 0, sizeof(w2s_star_txt));

    /* set initial editbox text */
    a_vkb_do_cmd (pt_page_data->h_vkb,
                  VKB_CMD_SET_INITIAL_TEXT,
                  (VOID*) w2s_star_txt,
                  (VOID*) 0xFF);

    a_vkb_set_focus(pt_page_data->h_vkb);

    //menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_CREATE_PIC_MODE_VKB));

    i4_ret=  a_vkb_set_visibility(pt_page_data->h_vkb,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_eb_name,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_vkb_showed = TRUE;

    c_wgl_repaint(pt_page_data->h_cnt_frm, NULL, TRUE);

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
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
static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
        case BTN_RETURN:
        {
            UTF16_T             w2s_str[CREATE_PIC_MODE_NAME_MAX_LEN] = {0};
            INT32               i4_ret = MENUR_OK;

            if(t_create_pic_mode_page_data.b_vkb_showed)
            {
                /* retrieve the new channel name. */
                i4_ret = a_vkb_do_cmd(t_create_pic_mode_page_data.h_vkb,
                             VKB_CMD_GET_TEXT,
                             WGL_PACK (w2s_str),
                             WGL_PACK (CREATE_PIC_MODE_NAME_MAX_LEN));
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_uc_w2s_to_ps(w2s_str, t_create_pic_mode_page_data.s_input_buf,CREATE_PIC_MODE_NAME_MAX_LEN);
                MENU_LOG_ON_FAIL(i4_ret);

                //i4_ret = _update_ui();
                //MENU_LOG_ON_FAIL(i4_ret);
                MENU_LOG_ON_FAIL (menu_nav_back()) ;
            }
            else
            {
                MENU_LOG_ON_FAIL (menu_nav_back()) ;
            }
            return MENUR_OK;
        }

        case BTN_CURSOR_DOWN:
            if(t_create_pic_mode_page_data.b_vkb_showed)
            {
                a_vkb_set_focus_ex(t_create_pic_mode_page_data.h_vkb);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_CREATE_PIC_MODE_VKB_EX));
            }
            else
            {
                c_wgl_set_focus(t_create_pic_mode_page_data.h_eb_name, WGL_SYNC_AUTO_REPAINT);
            }
            menu_pm_refresh();
            break ;
        case BTN_CURSOR_UP:
            MENU_LOG_ON_FAIL (menu_set_focus_on_homebar(TRUE));
            break;
        default:
            break ;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: menu_text_chg_lang
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
static INT32 _homebar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HOME_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
            menu_nav_go_home_menu();
            return MENUR_OK ;
        case BTN_RETURN:
            menu_nav_back();
            return MENUR_OK;
        case BTN_CURSOR_DOWN :
            menu_set_focus_on_backbar(TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _eb_name_set_text(
                    CHAR*                   s_txt,
                    BOOL                    b_repaint)
{
    INT32        i4_ret = 0;
    UTF16_T      w2s_star_txt[CREATE_PIC_MODE_NAME_MAX_LEN] = {0};    /* input text value: UTF16_T */
    UINT32       ui4_len;
    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;

    c_memset(w2s_star_txt, 0, sizeof(w2s_star_txt));
    c_uc_ps_to_w2s (s_txt, w2s_star_txt, CREATE_PIC_MODE_NAME_MAX_LEN);

    i4_ret = c_wgl_do_cmd (pt_page_data->h_eb_name,
                             WGL_CMD_EB_SET_TEXT,
                             WGL_PACK (w2s_star_txt),
                             WGL_PACK (0xFFFF));
    MENU_LOG_ON_FAIL(i4_ret);

    /* set cursor position */
    ui4_len = c_uc_w2s_strlen(w2s_star_txt);
    i4_ret = c_wgl_do_cmd (pt_page_data->h_eb_name,
                          WGL_CMD_EB_SET_CURSOR_POS,
                          WGL_PACK (ui4_len),
                          NULL);
    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_page_data->h_eb_name, NULL, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return   WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _eb_pic_mode_name_proc_fct
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
static INT32 _eb_pic_mode_name_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    INT32                   i4_ret = MENUR_OK;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UTF16_T         w2s_str[CREATE_PIC_MODE_NAME_MAX_LEN];
        UINT16          ui2_len = 0;

        switch ((UINT32)pv_param1)
        {
        case BTN_SELECT :
        {
            c_memset(w2s_str, 0, sizeof(UTF16_T)*(CREATE_PIC_MODE_NAME_MAX_LEN));

            i4_ret = c_wgl_do_cmd (h_widget,
                                    WGL_CMD_EB_GET_TEXT,
                                    WGL_PACK (w2s_str),
                                    WGL_PACK (CREATE_PIC_MODE_NAME_MAX_LEN));
            if (i4_ret != MENUR_OK)
            {
                c_memset(w2s_str, 0, sizeof(UTF16_T)*(CREATE_PIC_MODE_NAME_MAX_LEN));
            }
            c_memset(t_create_pic_mode_page_data.s_input_buf, 0, sizeof(CHAR)*(CREATE_PIC_MODE_NAME_MAX_LEN));

            c_uc_w2s_to_ps(w2s_str, t_create_pic_mode_page_data.s_input_buf, CREATE_PIC_MODE_NAME_MAX_LEN);

            DBG_INFO(("\n\n\r~~~~%s, %s, %d, input ssid = %s, start to scan it.\n\n\r~~~~",
                       __FILE__,
                       __FUNCTION__,
                       __LINE__,
                       t_create_pic_mode_page_data.s_input_buf));
            ui1_g_ssid_scan_count = 0;

            return WGLR_OK;
        }
        case BTN_KB_CURSOR_UP:
        case BTN_CURSOR_UP :
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
            return WGLR_OK;

        case BTN_KB_CURSOR_DOWN:
        case BTN_CURSOR_DOWN :
            return WGLR_OK;

        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            //menu_netowrk_nav_back();
            return WGLR_OK;
        case BTN_KB_CURSOR_LEFT:
        case BTN_KB_BACKSPACE:
        case BTN_CURSOR_LEFT:
        {
            UINT32                  ui4_len = 0;
            CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;
            UTF16_T                 w2s_name[CREATE_PIC_MODE_NAME_MAX_LEN];

            c_memset(w2s_name, 0, sizeof(UTF16_T)*(CREATE_PIC_MODE_NAME_MAX_LEN));

            i4_ret = c_wgl_do_cmd (h_widget,
                                    WGL_CMD_EB_GET_TEXT,
                                    WGL_PACK (w2s_name),
                                    WGL_PACK (CREATE_PIC_MODE_NAME_MAX_LEN));
            if (i4_ret != MENUR_OK)
            {
                c_memset(w2s_name, 0, sizeof(UTF16_T)*(CREATE_PIC_MODE_NAME_MAX_LEN));
            }
            c_memset(t_create_pic_mode_page_data.s_input_buf, 0, sizeof(CHAR)*(CREATE_PIC_MODE_NAME_MAX_LEN));

            c_uc_w2s_to_ps(w2s_name, t_create_pic_mode_page_data.s_input_buf, CREATE_PIC_MODE_NAME_MAX_LEN);
            DBG_INFO(("\n[nw_iput ssid test]------------------%s------------------\n",
                      t_create_pic_mode_page_data.s_input_buf));

            /* check total char number */
            ui4_len = c_strlen(pt_page_data->s_input_buf);
            if (ui4_len > 0)
            {
                /* delete last character from internal buffer */
                pt_page_data->s_input_buf [ui4_len -1] = '\0';

                /* update buffer content to editbox widget */
                i4_ret = _eb_name_set_text(pt_page_data->s_input_buf, TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }

            return WGLR_OK;
        }

        default :
            c_memset(w2s_str, 0, sizeof(UTF16_T)*(CREATE_PIC_MODE_NAME_MAX_LEN));

            c_wgl_do_cmd (h_widget,
                                    WGL_CMD_EB_GET_TEXT,
                                    WGL_PACK (w2s_str),
                                    WGL_PACK (CREATE_PIC_MODE_NAME_MAX_LEN));
            ui2_len = c_uc_w2s_strlen(w2s_str);
            DBG_INFO(("\n[nw input ssid]----------------%d\n",
                      ui2_len));
            if (ui2_len >= (CREATE_PIC_MODE_NAME_MAX_LEN - 1))
            {
                DBG_INFO(("\n[nw input ssid]----------------more characters were input\n"));
                return WGLR_OK;
            }
            break;
        }
    }

    else if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        i4_ret = c_wgl_do_cmd (h_widget,
                                WGL_CMD_EB_ENABLE_CURSOR_HT,
                                WGL_PACK (TRUE),
                                NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_CREATE_PIC_MODE));
    }
    else if(WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        UTF16_T                 w2s_name[CREATE_PIC_MODE_NAME_MAX_LEN];
        UINT32                  ui4_len;

        c_memset(w2s_name, 0, sizeof(UTF16_T)*(CREATE_PIC_MODE_NAME_MAX_LEN));

        i4_ret = c_wgl_do_cmd (h_widget,
                                WGL_CMD_EB_GET_TEXT,
                                WGL_PACK (w2s_name),
                                WGL_PACK (CREATE_PIC_MODE_NAME_MAX_LEN));
        if (i4_ret != MENUR_OK)
        {
            c_memset(w2s_name, 0, sizeof(UTF16_T)*(CREATE_PIC_MODE_NAME_MAX_LEN));
        }
        c_memset(t_create_pic_mode_page_data.s_input_buf, 0, sizeof(CHAR)*(CREATE_PIC_MODE_NAME_MAX_LEN));

        c_uc_w2s_to_ps(w2s_name, t_create_pic_mode_page_data.s_input_buf, CREATE_PIC_MODE_NAME_MAX_LEN);

        DBG_INFO(("\n[nw_iput ssid test]------------------%s------------------\n",
                  t_create_pic_mode_page_data.s_input_buf));
        ui4_len = c_strlen(t_create_pic_mode_page_data.s_input_buf);
        t_create_pic_mode_page_data.s_input_buf[ui4_len] = '\0';

        i4_ret = c_wgl_do_cmd (h_widget,
                                WGL_CMD_EB_ENABLE_CURSOR_HT,
                                WGL_PACK (FALSE),
                                NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

UINT16 get_cust_picture_mode_num()
{
    UINT16  ui2_count = 0;
    UINT16  ui2_i = 0;
    BOOL    b_is_exist= FALSE;


    for(ui2_i=0; ui2_i<ACFG_CUST_SET_PIC_MODE_NUM_EX; ui2_i++)
    {
        a_cfg_cust_get_cust_pic_mode_exist_status(ACFG_PRE_SET_PIC_MODE_NUM+ui2_i,&b_is_exist);

        if (b_is_exist)
        {
            g_aui2_idx_map[ACFG_PRE_SET_PIC_MODE_NUM+ui2_count]= ui2_i+ACFG_PRE_SET_PIC_MODE_NUM;
            ui2_count++;
        }
    }
    DBG_INFO(("\n=========!!!==get_cust_picture_mode_num========%d,%d\n",ui2_count,__LINE__));
    return ui2_count + ACFG_PRE_SET_PIC_MODE_NUM;


}

UINT16 menu_get_cust_picture_mode_num(VOID)
{
    return get_cust_picture_mode_num();
}

UINT16 cvt_acfg_idx_2_list_box_idx(UINT16 ui2_idx)
{
    UINT16 ui2_i = 0;
    UINT16 ui2_list_idx = ui2_idx; /*default value*/

    /*update g_aui2_idx_map[] */
    get_cust_picture_mode_num();

    for(ui2_i=0;ui2_i<ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM_EX;ui2_i++)
    {
        if ( g_aui2_idx_map[ui2_i] == ui2_idx)
        {
            ui2_list_idx = ui2_i;
            break;
        }
    }

    return ui2_list_idx;
}

UINT16 cvt_list_box_idx_2_acfg_idx(UINT16 ui2_idx)
{
    return g_aui2_idx_map[ui2_idx];
}

BOOL create_pic_mode_no_need_show_cnt_page()
{
    UINT16  ui2_count = 0;

    ui2_count = get_cust_picture_mode_num();

    if(ui2_count == ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM_EX)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}
/*----------------------------------------------------------------------------
 * Name: _create_pic_mode_name_mapping
 *
 * Description:append 2 to custom  pic mode name if the created pic mode name is same with the preset pic mode name.
 *          get the current custom name(prefix is preset pic mode name) and append index(2-7) to fill the pic mode name table.
 *
 *          in order to get the next custom pic mode name(conflict with the preset pic mode) append idx.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _create_pic_mode_name_mapping(CHAR* ps_pic_mode_name)
{

    UINT8               ui1_preset_idx=0;
    UINT8               ui1_custom_idx=0;
    UTF16_T             w2s_preset_pic_name[MENU_PRESET_PIC_MODE_NAME_LEN+1] = {0};
    CHAR                s_preset_pic_name[MENU_PRESET_PIC_MODE_NAME_LEN+1] = {0};
    CHAR                s_custom_pic_name[MENU_PRESET_PIC_MODE_NAME_LEN+1] = {0};
    CHAR                s_num[8+1] = {0};
    INT8                i1_row_idx=-1;
    UINT8               ui1_col_idx = 0;
    UINT8               ui1_append_idx = 0;
    UINT8               ui1_cust_pic_mode_idx[ACFG_PRE_SET_PIC_MODE_NUM][ACFG_PRE_SET_PIC_MODE_NUM] = {{0},{0},{0},{0},{0},{0}};
    BOOL                b_is_exist = FALSE;


    /*step1:check custom pic name is same as the preset pic mode name*/
    for(ui1_preset_idx=0;ui1_preset_idx<ACFG_PRE_SET_PIC_MODE_NUM;ui1_preset_idx++)
    {
        c_uc_w2s_strncpy(w2s_preset_pic_name, MENU_TEXT((MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1)+ui1_preset_idx),(MENU_PRESET_PIC_MODE_NAME_LEN));
        c_uc_w2s_to_ps(w2s_preset_pic_name,s_preset_pic_name,MENU_PRESET_PIC_MODE_NAME_LEN);

        /*enter custom pic mode name is same as the preset pic mode name*/
        if((c_strcasecmp(s_preset_pic_name,ps_pic_mode_name))==0)
        {
            /*record the the row idx*/
            i1_row_idx = ui1_preset_idx;
            DBG_INFO(("\n####%s(%d)ui1_row_idx=%d\n",__FUNCTION__,__LINE__,ui1_preset_idx));
            break;
        }
    }

    /*the same pic name not found*/
    if((i1_row_idx==-1)||(i1_row_idx==ACFG_PRE_SET_PIC_MODE_NUM))
    {
        return MENUR_OK;
    }

    /*step2:create cust pic mode idx table base on the current custom pic mode*/
    for(ui1_custom_idx=0;ui1_custom_idx<ACFG_PRE_SET_PIC_MODE_NUM;ui1_custom_idx++)
    {
        b_is_exist = FALSE;
        a_cfg_cust_get_cust_pic_mode_exist_status(ACFG_PRE_SET_PIC_MODE_NUM+ui1_custom_idx,&b_is_exist);

        if (b_is_exist)
        {
            c_memset(s_custom_pic_name,0,MENU_PRESET_PIC_MODE_NAME_LEN+1);
            a_cfg_cust_get_cust_pic_mode_name(ACFG_PRE_SET_PIC_MODE_NUM+ui1_custom_idx,s_custom_pic_name,MENU_PRESET_PIC_MODE_NAME_LEN);
            DBG_INFO(("\n####%s(%d)s_custom_pic_name=%s,ui1_custom_idx=%d\n",__FUNCTION__,__LINE__,s_custom_pic_name,ui1_custom_idx));
            for(ui1_preset_idx=0;ui1_preset_idx<ACFG_PRE_SET_PIC_MODE_NUM;ui1_preset_idx++)
            {
                c_uc_w2s_strncpy(w2s_preset_pic_name, MENU_TEXT((MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1)+ui1_preset_idx),(MENU_PRESET_PIC_MODE_NAME_LEN));
                c_uc_w2s_to_ps(w2s_preset_pic_name,s_preset_pic_name,MENU_PRESET_PIC_MODE_NAME_LEN);
                if((c_strncasecmp(s_preset_pic_name,s_custom_pic_name,c_strlen(s_preset_pic_name))==0)&&    //the preset pic name is the presfix of custom pic name
                    (c_strlen(s_custom_pic_name) == c_strlen(s_preset_pic_name)+1)&&
                    ((s_custom_pic_name[c_strlen(s_preset_pic_name)] - '0')>=2)&&
                    ((s_custom_pic_name[c_strlen(s_preset_pic_name)] - '0')<=7))
                {
                    ui1_col_idx = (s_custom_pic_name[c_strlen(s_preset_pic_name)] - '0')-2;
                    ui1_cust_pic_mode_idx[ui1_preset_idx][ui1_col_idx]++;
                }

            }
        }
    }
    /*for debug*/
    for(int i=0;i<ACFG_PRE_SET_PIC_MODE_NUM;i++)
    {
        for(int j=0;j<ACFG_PRE_SET_PIC_MODE_NUM;j++)
        {
            DBG_INFO(("\n####%s(%d)ui1_cust_pic_mode_idx[%d][%d]=%d\n",__FUNCTION__,__LINE__,i,j,ui1_cust_pic_mode_idx[i][j]));
        }
    }
    /*step3:get the next custom pic mode name append idx base on the table*/
    for(ui1_col_idx=0;ui1_col_idx<ACFG_PRE_SET_PIC_MODE_NUM;ui1_col_idx++)
    {
        if(ui1_cust_pic_mode_idx[i1_row_idx][ui1_col_idx]==0)
        {
            ui1_append_idx = ui1_col_idx+2;

            c_sprintf(s_num, "%d",  ui1_append_idx);
            c_strcat(ps_pic_mode_name,s_num);
            DBG_INFO(("\n####%s(%d)ps_pic_mode_name=%s,ui1_append_idx=%d\n",__FUNCTION__,__LINE__,ps_pic_mode_name,ui1_append_idx));
            break;
        }
    }
    return MENUR_OK;

}

INT32 menu_create_pic_mode_name_mapping(CHAR* ps_pic_mode_name)
{
    return _create_pic_mode_name_mapping(ps_pic_mode_name);
}

INT32 menu_save_pic_btn_fct(CHAR *s_buf)
{
    INT16 i2_pic_mode      = 0;
    BOOL b_is_exist = FALSE;
    UINT16 ui2_count = 0;
    INT16 i2_pic_mode_new  = 0;
    MENU_LOG_ON_FAIL(a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode));

    for(ui2_count=0; ui2_count<ACFG_CUST_SET_PIC_MODE_NUM_EX; ui2_count++)
    {
        a_cfg_cust_get_cust_pic_mode_exist_status(ACFG_PRE_SET_PIC_MODE_NUM+ui2_count,&b_is_exist);

        if (!b_is_exist)
            break;
    }

    _create_pic_mode_name_mapping(s_buf);
    DBG_LOG_PRINT(("[MENU][%s %d] after s_buf=%s, pre i2_pic_mode=%d,ui2_count = %d\n",__FUNCTION__,__LINE__,s_buf,i2_pic_mode,ui2_count));

    /*step2: create pic mode after mapping(create pic mode influence the b_is_exist and mapping will check the flag)*/
    a_cfg_cust_create_pic_mode();
    set_delay_lock_cust_pic_mode_status(TRUE);

    MENU_LOG_ON_FAIL(a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode_new));
    /*step3: reanme custom pic mode name*/
    a_cfg_cust_set_cust_pic_mode_name(i2_pic_mode_new,s_buf);

    /*step4: reset previous pic mode */
    MENU_LOG_ON_FAIL(a_cfg_reset_preset_pic_mode_ex(i2_pic_mode));

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _save_btn_proc_fct
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _save_btn_proc_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               param1,
                    VOID*               param2
                    )

{
    UINT32 ui4_keycode = (UINT32)param1;
    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;
    UINT16  ui2_count = 0;
    CHAR    s_buf[MENU_CUST_PIC_MODE_NAME_MAX_LEN]={0};
    UTF16_T      w2s_star_txt[MENU_CUST_PIC_MODE_NAME_MAX_LEN] = {0};
    BOOL        b_is_exist = FALSE;
    INT16       i2_pic_mode      = 0;
    INT16       i2_pic_mode_new  = 0;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_str[128] = {0};

        c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_GAMMA_SAVE));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_CREATE_PIC_MODE));
    }

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            switch(ui4_keycode)
            {
            case BTN_CURSOR_UP:
                c_wgl_set_focus(pt_page_data->h_vkb_last_focus,TRUE);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_CREATE_PIC_MODE_VKB_EX));
                return MENUR_OK;
            case BTN_CURSOR_DOWN:
                menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                menu_pm_repaint();
                break;
            case BTN_SELECT:

#ifdef LINUX_AUTO_TEST
            if( !(access((const char*)save_pic_mode_file, F_OK)) )
            {
                system("rm -rf "save_pic_mode_file);
            }
#endif
                MENU_LOG_ON_FAIL(a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode));

                 for(ui2_count=0; ui2_count<ACFG_CUST_SET_PIC_MODE_NUM_EX; ui2_count++)
                {
                    a_cfg_cust_get_cust_pic_mode_exist_status(ACFG_PRE_SET_PIC_MODE_NUM+ui2_count,&b_is_exist);

                    if (!b_is_exist)
                        break;
                }

                a_vkb_do_cmd(pt_page_data->h_vkb,
                                 VKB_CMD_GET_TEXT,
                                 WGL_PACK (w2s_star_txt),
                                 WGL_PACK (CREATE_PIC_MODE_NAME_MAX_LEN));

                if((c_uc_w2s_strlen(w2s_star_txt)) != 0)
                {
                    /*step1: custom pic mode name mapping*/
                    c_uc_w2s_to_ps(w2s_star_txt, s_buf, CREATE_PIC_MODE_NAME_MAX_LEN);

                    _create_pic_mode_name_mapping(s_buf);
                    DBG_LOG_PRINT(("[MENU][%s %d] after s_buf=%s, pre i2_pic_mode=%d,ui2_count = %d\n",__FUNCTION__,__LINE__,s_buf,i2_pic_mode,ui2_count));

                    /*step2: create pic mode after mapping(create pic mode influence the b_is_exist and mapping will check the flag)*/
                    a_cfg_cust_create_pic_mode();
                    set_delay_lock_cust_pic_mode_status(TRUE);

                    MENU_LOG_ON_FAIL(a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode_new));
                    /*step3: reanme custom pic mode name*/
                    a_cfg_cust_set_cust_pic_mode_name(i2_pic_mode_new,s_buf);

                    /*step4: reset previous pic mode */
                    MENU_LOG_ON_FAIL(a_cfg_reset_preset_pic_mode_ex(i2_pic_mode));

                    menu_pic_energy_change_sepcial_page_set_status(TRUE);

                    #if LINUX_AUTO_TEST
                    DBG_CREATE_TEMP_FILE(save_pic_mode_file);
                    #endif

                    menu_nav_back();
                    return MENUR_OK;
                }
                else
                {
                    break;
                }
            case BTN_RETURN:
                menu_nav_back();
                return MENUR_OK;
            default :
                break;
            }
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}


/*----------------------------------------------------------------------------
 * Name: _create_pic_mode_init_save_button
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _create_pic_mode_init_save_button(HANDLE_T h_parent,HANDLE_T* ph_widget)
{
    INT32               i4_ret;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = 0;

    c_memset(&t_rect, 0x0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     (INT32)CREATE_PIC_MODE_SAVE_BTN_X,
                     (INT32)CREATE_PIC_MODE_SAVE_BTN_Y,
                     (INT32)CREATE_PIC_MODE_SAVE_BTN_W,
                     (INT32)CREATE_PIC_MODE_SAVE_BTN_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _save_btn_proc_fct,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_inset, 0x0, sizeof(WGL_INSET_T));

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_INSET,
                           &t_inset,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);


    c_memset(&t_inset, 0x0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = CREATE_PIC_MODE_GUIDE_TEXT_X;
    t_inset.i4_right      = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_enable             = t_g_menu_color_white;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_menu_color_bk2_txt_disable;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_menu_color_white;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_white;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_menu_color_white;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Image */
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable   = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push_unhighlight = h_g_menu_img_item_bk;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Save TXT*/
   i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_LOCK_PIC_MODE_SAVE)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_LOCK_PIC_MODE_SAVE))));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _create_pic_mode_name_is_space
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
static BOOL _create_pic_mode_name_is_space (UTF16_T* pw2s_text, UINT16 ui2_len)
{
    UINT8  ui1_i = 0;
    UTF16_T  w2s_text[CREATE_PIC_MODE_NAME_MAX_LEN]={0};

    c_memcpy(w2s_text, pw2s_text, CREATE_PIC_MODE_NAME_MAX_LEN*sizeof(UTF16_T));
    w2s_text[CREATE_PIC_MODE_NAME_MAX_LEN-1] = 0;

    for(; ui1_i< ui2_len ; ui1_i++)
    {
        if(w2s_text[ui1_i] != 0x20)
        {
            break;
        }
    }

    if(ui1_i<ui2_len)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/*----------------------------------------------------------------------------
 * Name: _create_pic_mode_name_vbk_data_change_nfy
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
static INT32 _create_pic_mode_name_vbk_data_change_nfy (
    VOID*    pv_tag,
    UINT32   ui4_msg,
    VOID*    pv_param1,
    VOID*    pv_param2)
{
    INT32               i4_ret       = WDKR_OK;
    UTF16_T               w2s_text[CREATE_PIC_MODE_NAME_MAX_LEN+1]={0};
    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;
    VKB_CONTROL_LOGIC_T *pt_vkb_ctrl = NULL;
    if(ui4_msg == VKB_MSG_DLG_KEY_EB_CLEAR)
    {
        MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
        MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
        pt_page_data->b_save_enable = FALSE;
    }
    if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        UINT32*  pui4_key_code = (UINT32*) pv_param1;
        BOOL     b_is_top_bottom = FALSE;
        UTF16_T             w2s_str[CREATE_PIC_MODE_NAME_MAX_LEN] = {0};

        switch(*pui4_key_code)
        {
            case BTN_EXIT:
            case BTN_PREV_PRG:
            case BTN_RETURN:
            {
                if(pt_page_data->b_vkb_showed)
                {
                    /* retrieve the new channel name. */
                    i4_ret = a_vkb_do_cmd(pt_page_data->h_vkb,
                                 VKB_CMD_GET_TEXT,
                                 WGL_PACK (w2s_str),
                                 WGL_PACK (CREATE_PIC_MODE_NAME_MAX_LEN));
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_uc_w2s_to_ps(w2s_str, pt_page_data->s_input_buf,CREATE_PIC_MODE_NAME_MAX_LEN);
                    MENU_LOG_ON_FAIL(i4_ret);

                    //i4_ret = _update_ui();
                    //MENU_LOG_ON_FAIL(i4_ret);

                    if(!pt_page_data->b_vkb_showed)
                    {
                        c_wgl_set_focus(pt_page_data->h_eb_name, WGL_NO_AUTO_REPAINT);
                    }
                    menu_nav_back();
                }
                else
                {
                    menu_nav_back();
                }

                i4_ret = WDK_NO_ACTION;
                break;
            }
            case BTN_CURSOR_UP:
                i4_ret = a_vkb_current_is_top_row(pt_page_data->h_vkb,&b_is_top_bottom);
                if(i4_ret != WDKR_OK)
                {
                    return WDKR_OK;
                }
                if(TRUE == b_is_top_bottom)
                {
                    menu_set_focus_on_backbar(TRUE);
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                    i4_ret = WDK_NO_ACTION;
                }
                break;
            case BTN_CURSOR_DOWN:
            {
                i4_ret = a_vkb_current_is_bottom_row(pt_page_data->h_vkb,&pt_page_data->h_vkb_last_focus,&b_is_top_bottom);
                if(i4_ret != WDKR_OK)
                {
                    return WDKR_OK;
                }
                if(TRUE == b_is_top_bottom)
                {
                    if(FALSE == pt_page_data->b_save_enable)
                    {
                        menu_help_tip_keytip_set_focus(pt_page_data->h_vkb_last_focus, 0, FALSE);
                    }
                    else
                    {
                        c_wgl_set_focus(pt_page_data->h_save_btn,TRUE);
                    }
                    i4_ret = WDK_NO_ACTION;
                }
            }
            break;
            case BTN_CURSOR_LEFT:
            {
                UINT16 ui2_str_len = 0;

                i4_ret = a_vkb_current_is_top_row(pt_page_data->h_vkb,&b_is_top_bottom);

                MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_page_data->h_vkb,
                                        VKB_CMD_GET_EB_CONTENT,
                                        (VOID*)(w2s_text),
                                        (VOID*)(CREATE_PIC_MODE_NAME_MAX_LEN)));


                if((c_uc_w2s_strlen(w2s_text)) <= 1)
                {
                    if((!b_is_top_bottom)&&((c_uc_w2s_strlen(w2s_text)) == 1))
                    {
                        /*focus on vkb*/
                    }
                    else
                    {
                        // focus on edit box
                        MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
                        MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                        pt_page_data->b_save_enable = FALSE;
                    }
                }
                else
                {
                    ui2_str_len = c_uc_w2s_strlen(w2s_text);

                    if(b_is_top_bottom && _create_pic_mode_name_is_space(w2s_text,(ui2_str_len-1)))
                    {
                        MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
                        MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                        pt_page_data->b_save_enable = FALSE;
                    }
                }
                    i4_ret = WDKR_OK;
            }
            break;
            case BTN_CURSOR_RIGHT:
            {
                MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_page_data->h_vkb,
                                        VKB_CMD_GET_EB_CONTENT,
                                        (VOID*)(w2s_text),
                                        (VOID*)(CREATE_PIC_MODE_NAME_MAX_LEN)));


                if((c_uc_w2s_strlen(w2s_text)) < 1)
                {
                    MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
                    MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                    pt_page_data->b_save_enable = FALSE;
                }
                else
                {
                    if(_create_pic_mode_name_is_space(w2s_text,c_uc_w2s_strlen(w2s_text)))
                    {
                        MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
                        MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                        pt_page_data->b_save_enable = FALSE;
                    }
                    else
                    {
                        MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,TRUE));
                        MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                        pt_page_data->b_save_enable = TRUE;
                    }
                }
                    i4_ret = WDKR_OK;
            }
                break;
            case BTN_SELECT:
            {
                 UINT16 ui2_str_len = 0;
                 BOOL   b_latin = FALSE;
                 UINT16 ui2_focus_idx = 0;
                 UINT16  ui2_latin_num = 0;

                i4_ret = a_vkb_is_latin_stat(pt_page_data->h_vkb, &b_latin);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_wgl_do_cmd(pt_page_data->h_vkb,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_vkb_ctrl),
                          NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY)
                {
                    MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_page_data->h_vkb,
                                            VKB_CMD_GET_EB_CONTENT,
                                            (VOID*)(w2s_text),
                                            (VOID*)(CREATE_PIC_MODE_NAME_MAX_LEN)));

                    if((c_uc_w2s_strlen(w2s_text)) == (CREATE_PIC_MODE_NAME_MAX_LEN -1))
                    {
                        #if 0
                        menu_request_context_switch(_create_pic_mode_name_exceeding_show, NULL, NULL, NULL);
                        #endif
                        break;
                    }
                    else
                    {
                        if(b_latin && (pt_page_data->b_latin_selected == FALSE)) // b_latin_lock state but not b_latin_expand
                        {
                            pt_page_data->b_latin_selected = TRUE;
                            i4_ret = WDKR_OK;
                            break;
                        }
                        else
                        {
                            if(b_latin && pt_page_data->b_latin_selected)
                            {
                                MENU_LOG_ON_FAIL ( a_vkb_do_cmd(pt_page_data->h_vkb,
                                            VKB_CMD_GET_LATIN_BTN_IDX,
                                            (VOID*)(&ui2_focus_idx),
                                            (VOID*)(NULL)));


                                MENU_LOG_ON_FAIL ( a_vkb_do_cmd(pt_page_data->h_vkb,
                                                                        VKB_CMD_GET_CUR_LATIN_NUM,
                                                                        (VOID*)&ui2_latin_num,
                                                                        (VOID*)(NULL)));

                                pt_page_data->b_latin_selected = FALSE;

                                if(ui2_focus_idx == ui2_latin_num )//b_latin_expand & focus on latin return icon <<
                                {
                                    //do nothing.
                                }
                                else
                                {
                        MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,TRUE));
                        MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                        pt_page_data->b_save_enable = TRUE;
                                }
                            }

                            else  // normal state not latin state
                            {
                                MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,TRUE));
                                MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                                pt_page_data->b_save_enable = TRUE;
                            }

                        i4_ret = WDKR_OK;
                            break;
                        }
                    }
                }

                else if((pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY)&&
                       (pt_vkb_ctrl->t_focus_item.t_ctrl_key.ui1_focus_idx == 4))
                {
                    /*delete key*/
                    MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_page_data->h_vkb,
                                            VKB_CMD_GET_EB_CONTENT,
                                            (VOID*)(w2s_text),
                                            (VOID*)(CREATE_PIC_MODE_NAME_MAX_LEN)));
                    ui2_str_len = c_uc_w2s_strlen(w2s_text);

                    if((ui2_str_len <= 1)||
                        (_create_pic_mode_name_is_space(w2s_text,(ui2_str_len -1))))
                    {
                        MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
                        MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                        pt_page_data->b_save_enable = FALSE;
                    }

                    i4_ret = WDKR_OK;
                }

                else if((pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY)&&
                       (pt_vkb_ctrl->t_focus_item.t_ctrl_key.ui1_focus_idx == 3))
                {
                    /*space key*/
                    MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_page_data->h_vkb,
                                            VKB_CMD_GET_EB_CONTENT,
                                            (VOID*)(w2s_text),
                                            (VOID*)(CREATE_PIC_MODE_NAME_MAX_LEN)));

                    if((c_uc_w2s_strlen(w2s_text)) == (CREATE_PIC_MODE_NAME_MAX_LEN -1))
                    {
                        #if 0
                        menu_request_context_switch(_create_pic_mode_name_exceeding_show, NULL, NULL, NULL);
                        #endif
                        break;
                    }
                    else if(_create_pic_mode_name_is_space(w2s_text,c_uc_w2s_strlen(w2s_text)))
                    {
                        MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
                        MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                        i4_ret = WDKR_OK;
                        pt_page_data->b_save_enable = FALSE;
                    }
                    }
                }
                break;

            default :
            {
                if (((BTN_DIGIT_0 <= *pui4_key_code) && (BTN_DIGIT_9 >= *pui4_key_code)) ||
                    ((BTN_KB_NULL <= *pui4_key_code) && (BTN_KB_HYPER >= *pui4_key_code)))
                {
                    MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_page_data->h_vkb,
                                            VKB_CMD_GET_EB_CONTENT,
                                            (VOID*)(w2s_text),
                                            (VOID*)(CREATE_PIC_MODE_NAME_MAX_LEN)));
                    #if 0
                    if (((BTN_DIGIT_0 <= *pui4_key_code && BTN_DIGIT_9 >= *pui4_key_code) || (BTN_KB_MINUS_SIGN == *pui4_key_code))
                        && (c_uc_w2s_strlen(w2s_text) == (CREATE_PIC_MODE_NAME_MAX_LEN - 1)))
                    {
                        menu_request_context_switch(_create_pic_mode_name_exceeding_show, NULL, NULL, NULL);
                    }
                    #endif

                    if(BTN_KB_BACKSPACE == *pui4_key_code)
                    {
                        i4_ret = a_vkb_current_is_top_row(pt_page_data->h_vkb,&b_is_top_bottom);

                        if((c_uc_w2s_strlen(w2s_text)) <= 1)
                        {
                            if((!b_is_top_bottom)&&((c_uc_w2s_strlen(w2s_text)) == 1))
                            {
                                /*focus on vkb*/
                            }
                            else
                            {
                                MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
                                MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                                pt_page_data->b_save_enable = FALSE;
                            }
                        }
                        else
                        {
                            if(_create_pic_mode_name_is_space(w2s_text,(c_uc_w2s_strlen(w2s_text)-1)))
                            {
                                MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
                                MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                                pt_page_data->b_save_enable = FALSE;
                            }
                            else
                            {
                                MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,TRUE));
                                MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                                pt_page_data->b_save_enable = TRUE;
                            }
                        }
                            i4_ret = WDKR_OK;
                    }
                    else if(BTN_KB_SPACE == *pui4_key_code)
                    {
                        if((c_uc_w2s_strlen(w2s_text)) == (CREATE_PIC_MODE_NAME_MAX_LEN -1))
                        {
                            break;
                        }
                        else if(_create_pic_mode_name_is_space(w2s_text,c_uc_w2s_strlen(w2s_text)))
                        {
                            MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
                            MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                            pt_page_data->b_save_enable = FALSE;
                        }
                        i4_ret = WDKR_OK;
                    }
                    else
                    {
                        if((c_uc_w2s_strlen(w2s_text)) == (CREATE_PIC_MODE_NAME_MAX_LEN -1))
                        {
                            break;
                        }
                        else
                        {
                            MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,TRUE));
                            MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_save_btn,NULL,TRUE));
                            pt_page_data->b_save_enable = TRUE;
                        }
                            i4_ret = WDKR_OK;
                    }
                }
            }
                break;
        }
    }
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _eb_pic_mode_name_create
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
static INT32 _eb_pic_mode_name_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
){
    INT32               i4_ret = 0;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_EB_KEY_MAP_T    t_eb_key_map;
    UTF16_T             w2s_cursor =(UTF16_T) 0x005F; /* underline */

    /* create editbox */
    ui4_style = WGL_STL_EB_MAX_CHAR_256;

    SET_RECT_BY_SIZE(&t_rect,
                     FRAME_LEFT_RIGHT_INTV,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    t_inset.i4_left     = 8*4/3;
    t_inset.i4_right    = 8*4/3;
    t_inset.i4_top      = 5;
    t_inset.i4_bottom   = 5;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Cnt Insets */
    t_inset.i4_left     = 2*4/3;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = MENU_ITEM_EDIT_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_EDIT_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set txt color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set the cursor highlight */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_EB_ENABLE_CURSOR_HT,
                            WGL_PACK (TRUE),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                             WGL_CMD_EB_SET_CURSOR_CHAR,
                             (VOID*) (&w2s_cursor),/* underline */
                             NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                             WGL_CMD_GL_SET_COLOR,
                             WGL_PACK(WGL_CLR_EB_CURSOR),   /* text color highlighted by cursor */
                             WGL_PACK(& t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set always highlight: this will display cursor even if focus not on editbox. */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK (WGL_EB_ALWAYS_HT | WGL_EB_CHAR_SUPPORT | WGL_EB_EA_AUTO_EDITING | WGL_EB_KEEP_CURSOR_POS),
                          WGL_PACK (WGL_EB_ALWAYS_HT | WGL_EB_CHAR_SUPPORT | WGL_EB_EA_AUTO_EDITING | WGL_EB_KEEP_CURSOR_POS));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       =h_g_menu_img_item_edit;
    t_img_info.u_img_data.t_standard.t_highlight    =h_g_menu_img_item_edit;
    t_img_info.u_img_data.t_standard.t_disable      =h_g_menu_img_item_edit;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)(CREATE_PIC_MODE_NAME_MAX_LEN)),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _create_pic_mode_vkb_create
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
static INT32 _create_pic_mode_vkb_create(VOID)
{
    INT32       i4_ret;

    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;
    VKB_INIT_T           t_init_data;

    /* Create Virtual key board */
    t_init_data.h_parent            = pt_page_data->h_cnt_frm;

    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_WIFI_SSID | VKB_STYLE_MASK_NO_COM_KEY | VKB_STYLE_MASK_WITH_EB_CLEAR;
    t_init_data.t_gui_rc.i4_left    = FRAME_LEFT_RIGHT_INTV;
    t_init_data.t_gui_rc.i4_top     = 5;
    t_init_data.pf_data_change_fct  = _create_pic_mode_name_vbk_data_change_nfy;
    t_init_data.pv_tag              = NULL;

    i4_ret = a_vkb_create(&t_init_data,&pt_page_data->h_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _create_pic_mode_warn_dlg_yes_btn
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
static VOID _create_pic_mode_warn_dlg_yes_btn()
{
    INT32                       i4_ret  = MENUR_OK;
    CREATE_PIC_MODE*        pt_page_data = &t_create_pic_mode_page_data;
    UINT32                      ui4_page_id = 0;

    i4_ret = a_ui_simple_dialog_hide(pt_page_data->h_warning_dlg);
    MENU_LOG_ON_FAIL(i4_ret);
    pt_page_data->b_is_dlg_show  = FALSE;
    menu_nav_get_crnt_page(&ui4_page_id);

    if(ui4_page_id == pt_page_data->ui4_cur_page_id)
    {
        menu_nav_back();
    }
    else
    {
        c_wgl_set_focus(pt_page_data->h_menu_current_focus,TRUE);
        menu_pm_repaint();
    }
}


/*----------------------------------------------------------------------------
 * Name: _create_pic_mode_warn_dlg_create
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
static INT32 _create_pic_mode_warn_dlg_create(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    CREATE_PIC_MODE*        pt_page_data = &t_create_pic_mode_page_data;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    HANDLE_T        h_parent = NULL_HANDLE;


    i4_ret = menu_pm_get_root_frm(&h_parent);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = h_parent;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _create_pic_mode_warn_dlg_yes_btn;
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_one_btn_mode                 = TRUE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                                &pt_page_data->h_warning_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_text(pt_page_data->h_warning_dlg,
                                                  MENU_TEXT(MLM_MENU_KEY_MENU_CREATE_PIC_MODE_WARN_MSG));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_page_data->h_warning_dlg, MENU_TEXT( MLM_MENU_KEY_OK));
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_is_dlg_show   = FALSE;
    return MENUR_OK;

}
/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret=  MENUR_OK;
//  GL_RECT_T   t_rect = {0};

    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;

    pt_page_data->ui4_cur_page_id = ui4_page_id;

    /*create warning dlg*/
    i4_ret = _create_pic_mode_warn_dlg_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page_data->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    /* new name label */
    i4_ret = _eb_pic_mode_name_create(pt_page_data->h_cnt_frm,
                              2,
                              _eb_pic_mode_name_proc_fct,
                              &pt_page_data->h_eb_name);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _create_pic_mode_vkb_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _create_pic_mode_init_save_button(pt_page_data->h_cnt_frm,
                                                          &pt_page_data->h_save_btn);
    MENU_LOG_ON_FAIL(i4_ret);
    /* set visibility */
    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_finish = TRUE;
    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    INT32       i4_ret = 0;

    if (NULL_HANDLE != t_create_pic_mode_page_data.h_warning_dlg)
   {
        i4_ret = a_ui_simple_dialog_destory(t_create_pic_mode_page_data.h_warning_dlg);
        MENU_LOG_ON_FAIL(i4_ret);
        t_create_pic_mode_page_data.b_is_dlg_show = FALSE;
   }
    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32       i4_ret;
    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;

    /* shit. */
    pt_page_data->b_finish = TRUE;

    i4_ret = _update_ui();

    DBG_INFO(("i4_ret=%d\n", i4_ret));

    MENU_LOG_ON_FAIL(c_wgl_enable(pt_page_data->h_save_btn,FALSE));
    pt_page_data->b_save_enable = FALSE;
    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;

    if(pt_page_data->b_this_page_show == FALSE)
    {
        return MENUR_OK;
    }
    menu_help_tip_keytip_show(TRUE);

    pt_page_data->b_this_page_show = FALSE;
    pt_page_data->b_finish = TRUE;

    pt_page_data->h_menu_current_focus = NULL_HANDLE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    CREATE_PIC_MODE* pt_page_data = &t_create_pic_mode_page_data;
    INT32       i4_ret;
    UINT16  ui2_count = 0;

    ui2_count = get_cust_picture_mode_num();
    if(ui2_count >= ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM_EX)
    {
        i4_ret = c_wgl_get_focus(&pt_page_data->h_menu_current_focus);
        MENU_LOG_ON_FAIL(i4_ret);
        a_ui_simple_dialog_set_focus(pt_page_data->h_warning_dlg, FALSE);
    }
    else
    {
        if(!pt_page_data->b_vkb_showed)
        {
            c_wgl_set_focus(pt_page_data->h_eb_name, WGL_NO_AUTO_REPAINT);
        }
    }

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    /* set callback function for backbar */
    menu_set_backbar_proc(NULL) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    /* stop animation */
    menu_page_animation_stop();
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
extern INT32 menu_page_create_new_pic_mode_init(VOID)
{
    t_g_menu_page_create_pic_mode.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_create_pic_mode.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_create_pic_mode.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_create_pic_mode.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_create_pic_mode.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_create_pic_mode.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_create_pic_mode.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
