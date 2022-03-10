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
 * $RCSfile: menu_page_nw_pwd.c,v $
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
#include "menu2/menu_dbg.h"

#if 1

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define WLAN_SCANNING_TIMEOUT         (10)   /*about 30 s*/
#define WLAN_CONNECTING_TIMEOUT       (15)   /*about 45 s*/

#define DELETE_PIC_MODE_NAME_MAX_LEN           (32+1)

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct _DELETE_PIC_MODE
{
    HANDLE_T     h_cnt_frm;
    HANDLE_T     h_eb_name;
    HANDLE_T     h_vkb;
    BOOL         b_vkb_showed;
    HANDLE_T     h_vkb_last_focus;
    BOOL         b_finish;
    BOOL         b_timer_result;
    UINT8        ui1_animation_count;
    CHAR         s_input_buf[DELETE_PIC_MODE_NAME_MAX_LEN+1];
    UINT32       ui4_nw_nfy_id;
    BOOL         b_this_page_show;

}DELETE_PIC_MODE;

static UINT8        ui1_g_ssid_scan_count = 0;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_page_delete_pic_mode;
static  DELETE_PIC_MODE    t_delete_pic_mode_page_data;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _eb_name_set_text(
                    CHAR*                   s_txt,
                    BOOL                    b_repaint);

static INT32 _show_wifi_pwd_vkb(VOID);
/*----------------------------------------------------------------------------
 * Name: _update_net_info_data
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
static INT32 _set_suggest_txt(VOID)
{


    return MENUR_OK;

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

    DELETE_PIC_MODE* pt_page_data = &t_delete_pic_mode_page_data;

    GL_RECT_T          t_rect = {0};



    i4_ret = _set_suggest_txt();
    MENU_LOG_ON_FAIL(i4_ret);

    /*set edit box*/
    i4_ret = _eb_name_set_text(pt_page_data->s_input_buf, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    if (0 == ui1_model_idx)
    {
        i4_ret = _show_wifi_pwd_vkb();
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

    SET_RECT_BY_SIZE(&t_rect,
                 CONTENT_X + (CONTENT_W -ICON_ANIMATION_W)/2,
                 CONTENT_Y + MENU_ITEM_V_HEIGHT * 4 - ICON_ANIMATION_H,
                 ICON_ANIMATION_W,
                 ICON_ANIMATION_H);

    return MENUR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _input_naming_cust_lbl_page_refresh
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
static INT32 _show_wifi_pwd_vkb(VOID)
{
    DELETE_PIC_MODE* pt_page_data = &t_delete_pic_mode_page_data;
    INT32    i4_ret = MENUR_OK;
//    GL_RECT_T                      t_rect = {0};
    UTF16_T      w2s_star_txt[DELETE_PIC_MODE_NAME_MAX_LEN +1] = {0};    /* input text value: UTF16_T */

    /* set max char num to MAX_LBL_NAME_LEN */
    a_vkb_do_cmd (pt_page_data->h_vkb,
                   DELETE_PIC_MODE_NAME_MAX_LEN,
                   (VOID*) 32,
                   NULL);

    c_memset(w2s_star_txt, 0, sizeof(w2s_star_txt));
    c_uc_ps_to_w2s (pt_page_data->s_input_buf, w2s_star_txt, DELETE_PIC_MODE_NAME_MAX_LEN);

    /* set initial editbox text */
    a_vkb_do_cmd (pt_page_data->h_vkb,
                  VKB_CMD_SET_INITIAL_TEXT,
                  (VOID*) w2s_star_txt,
                  (VOID*) 0xFF);

    a_vkb_set_focus(pt_page_data->h_vkb);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

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
        case BTN_RETURN:
        {
            UTF16_T             w2s_str[DELETE_PIC_MODE_NAME_MAX_LEN+1] = {0};
            INT32               i4_ret = MENUR_OK;

            if(t_delete_pic_mode_page_data.b_vkb_showed)
            {
                /* retrieve the new channel name. */
                i4_ret = a_vkb_do_cmd(t_delete_pic_mode_page_data.h_vkb,
                             VKB_CMD_GET_TEXT,
                             WGL_PACK (w2s_str),
                             WGL_PACK (DELETE_PIC_MODE_NAME_MAX_LEN));
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_uc_w2s_to_ps(w2s_str, t_delete_pic_mode_page_data.s_input_buf,DELETE_PIC_MODE_NAME_MAX_LEN);
                MENU_LOG_ON_FAIL(i4_ret);

                //i4_ret = _update_ui();
                //MENU_LOG_ON_FAIL(i4_ret);
            }
            //else
            {
                MENU_LOG_ON_FAIL (menu_nav_back ()) ;
            }

            menu_pm_repaint();
            return MENUR_OK;
        }

        case BTN_CURSOR_DOWN:
            if(t_delete_pic_mode_page_data.b_vkb_showed)
            {
                a_vkb_set_focus_ex(t_delete_pic_mode_page_data.h_vkb);
                menu_pm_repaint();
            }
            else
            {
                c_wgl_set_focus(t_delete_pic_mode_page_data.h_eb_name, WGL_SYNC_AUTO_REPAINT);
            }
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
            //menu_netowrk_nav_back();
            return MENUR_OK;
        case BTN_CURSOR_DOWN :
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
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
    UTF16_T      w2s_star_txt[DELETE_PIC_MODE_NAME_MAX_LEN +1] = {0};    /* input text value: UTF16_T */
    UINT32       ui4_len;
    DELETE_PIC_MODE* pt_page_data = &t_delete_pic_mode_page_data;

    c_memset(w2s_star_txt, 0, sizeof(w2s_star_txt));
    c_uc_ps_to_w2s (s_txt, w2s_star_txt, DELETE_PIC_MODE_NAME_MAX_LEN);

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
        UTF16_T         w2s_str[DELETE_PIC_MODE_NAME_MAX_LEN+1];
        UINT16          ui2_len = 0;

        switch ((UINT32)pv_param1)
        {
        case BTN_SELECT :
        {
            c_memset(w2s_str, 0, sizeof(UTF16_T)*(DELETE_PIC_MODE_NAME_MAX_LEN+1));

            i4_ret = c_wgl_do_cmd (h_widget,
                                    WGL_CMD_EB_GET_TEXT,
                                    WGL_PACK (w2s_str),
                                    WGL_PACK (DELETE_PIC_MODE_NAME_MAX_LEN));
            if (i4_ret != MENUR_OK)
            {
                c_memset(w2s_str, 0, sizeof(UTF16_T)*(DELETE_PIC_MODE_NAME_MAX_LEN+1));
            }
            c_memset(t_delete_pic_mode_page_data.s_input_buf, 0, sizeof(CHAR)*(DELETE_PIC_MODE_NAME_MAX_LEN+1));

            c_uc_w2s_to_ps(w2s_str, t_delete_pic_mode_page_data.s_input_buf, DELETE_PIC_MODE_NAME_MAX_LEN);

            DBG_INFO(("\n\n\r~~~~%s, %s, %d, input ssid = %s, start to scan it.\n\n\r~~~~",
                       __FILE__,
                       __FUNCTION__,
                       __LINE__,
                       t_delete_pic_mode_page_data.s_input_buf));
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
            DELETE_PIC_MODE* pt_page_data = &t_delete_pic_mode_page_data;
            UTF16_T                 w2s_name[DELETE_PIC_MODE_NAME_MAX_LEN+1];

            c_memset(w2s_name, 0, sizeof(UTF16_T)*(DELETE_PIC_MODE_NAME_MAX_LEN+1));

            i4_ret = c_wgl_do_cmd (h_widget,
                                    WGL_CMD_EB_GET_TEXT,
                                    WGL_PACK (w2s_name),
                                    WGL_PACK (DELETE_PIC_MODE_NAME_MAX_LEN));
            if (i4_ret != MENUR_OK)
            {
                c_memset(w2s_name, 0, sizeof(UTF16_T)*(DELETE_PIC_MODE_NAME_MAX_LEN+1));
            }
            c_memset(t_delete_pic_mode_page_data.s_input_buf, 0, sizeof(CHAR)*(DELETE_PIC_MODE_NAME_MAX_LEN+1));

            c_uc_w2s_to_ps(w2s_name, t_delete_pic_mode_page_data.s_input_buf, DELETE_PIC_MODE_NAME_MAX_LEN);
            DBG_INFO(("\n[nw_iput ssid test]------------------%s------------------\n",
                      t_delete_pic_mode_page_data.s_input_buf));

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
            c_memset(w2s_str, 0, sizeof(UTF16_T)*(DELETE_PIC_MODE_NAME_MAX_LEN+1));

            c_wgl_do_cmd (h_widget,
                                    WGL_CMD_EB_GET_TEXT,
                                    WGL_PACK (w2s_str),
                                    WGL_PACK (DELETE_PIC_MODE_NAME_MAX_LEN));
            ui2_len = c_uc_w2s_strlen(w2s_str);
            DBG_INFO(("\n[nw input ssid]----------------%d\n",
                      ui2_len));
            if (ui2_len >= (DELETE_PIC_MODE_NAME_MAX_LEN - 1))
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

        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }
    else if(WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        UTF16_T                 w2s_name[DELETE_PIC_MODE_NAME_MAX_LEN+1];
        UINT32                  ui4_len;

        c_memset(w2s_name, 0, sizeof(UTF16_T)*(DELETE_PIC_MODE_NAME_MAX_LEN+1));

        i4_ret = c_wgl_do_cmd (h_widget,
                                WGL_CMD_EB_GET_TEXT,
                                WGL_PACK (w2s_name),
                                WGL_PACK (DELETE_PIC_MODE_NAME_MAX_LEN));
        if (i4_ret != MENUR_OK)
        {
            c_memset(w2s_name, 0, sizeof(UTF16_T)*(DELETE_PIC_MODE_NAME_MAX_LEN+1));
        }
        c_memset(t_delete_pic_mode_page_data.s_input_buf, 0, sizeof(CHAR)*(DELETE_PIC_MODE_NAME_MAX_LEN+1));

        c_uc_w2s_to_ps(w2s_name, t_delete_pic_mode_page_data.s_input_buf, DELETE_PIC_MODE_NAME_MAX_LEN);

        DBG_INFO(("\n[nw_iput ssid test]------------------%s------------------\n",
                  t_delete_pic_mode_page_data.s_input_buf));
        ui4_len = c_strlen(t_delete_pic_mode_page_data.s_input_buf);
        t_delete_pic_mode_page_data.s_input_buf[ui4_len] = '\0';

        i4_ret = c_wgl_do_cmd (h_widget,
                                WGL_CMD_EB_ENABLE_CURSOR_HT,
                                WGL_PACK (FALSE),
                                NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

#if 0
/*----------------------------------------------------------------------------
 * Name: _action_show_vkb_proc_fct
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
static INT32 _action_show_vkb_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)pv_param1)
        {
        case BTN_SELECT :
            _show_wifi_pwd_vkb();
            return WGLR_OK;
        case BTN_CURSOR_UP :
            return WGLR_OK;

        case BTN_CURSOR_DOWN :
            menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
            menu_pm_repaint();
            return WGLR_OK;

        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_netowrk_nav_back();
            return WGLR_OK;

        default :
            return WGLR_OK;
        }
    }
    else if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NW_HELP_SHOW_KB));
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
#endif
/*----------------------------------------------------------------------------
 * Name: _delete_pic_mode_name_vbk_data_change_nfy
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
static INT32 _delete_pic_mode_name_vbk_data_change_nfy (
    VOID*    pv_tag,
    UINT32   ui4_msg,
    VOID*    pv_param1,
    VOID*    pv_param2)
{
    INT32               i4_ret       = WDKR_OK;

    if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        UINT32*  pui4_key_code = (UINT32*) pv_param1;
        BOOL     b_is_top_bottom = FALSE;
        DELETE_PIC_MODE* pt_page_data = &t_delete_pic_mode_page_data;
        UTF16_T             w2s_str[DELETE_PIC_MODE_NAME_MAX_LEN+1] = {0};

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
                                 WGL_PACK (DELETE_PIC_MODE_NAME_MAX_LEN));
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_uc_w2s_to_ps(w2s_str, pt_page_data->s_input_buf,DELETE_PIC_MODE_NAME_MAX_LEN);
                    MENU_LOG_ON_FAIL(i4_ret);

                    //i4_ret = _update_ui();
                    //MENU_LOG_ON_FAIL(i4_ret);

                    if(!pt_page_data->b_vkb_showed)
                    {
                        c_wgl_set_focus(pt_page_data->h_eb_name, WGL_NO_AUTO_REPAINT);
                    }
                }
                //else
                {
                    //menu_netowrk_nav_back();
                }

                menu_pm_repaint();
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
                    i4_ret = WDK_NO_ACTION;
                    menu_pm_repaint();

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
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NW_HELP_CON_SSID));
                    i4_ret = WDK_NO_ACTION;
                }
            }
                break;
            default :
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
                     MENU_ITEM_V_INSET_L,
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
                          WGL_PACK((UINT16)(DELETE_PIC_MODE_NAME_MAX_LEN + 1)),
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
 * Name: _delete_pic_mode_vkb_create
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
static INT32 _delete_pic_mode_vkb_create(VOID)
{
    INT32       i4_ret;

    DELETE_PIC_MODE* pt_page_data = &t_delete_pic_mode_page_data;
    VKB_INIT_T           t_init_data;

    /* Create Virtual key board */
    t_init_data.h_parent            = pt_page_data->h_cnt_frm;
    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_WIFI_SSID | VKB_STYLE_MASK_NO_COM_KEY;
    t_init_data.t_gui_rc.i4_left    = MENU_ITEM_V_INSET_L;
    t_init_data.t_gui_rc.i4_top     = (GRID_H*3 - 15*4/3);
    t_init_data.pf_data_change_fct  = _delete_pic_mode_name_vbk_data_change_nfy;
    t_init_data.pv_tag              = NULL;

    i4_ret = a_vkb_create(&t_init_data,&pt_page_data->h_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret;

    DELETE_PIC_MODE* pt_page_data = &t_delete_pic_mode_page_data;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page_data->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    /* pwd label */
    i4_ret = _eb_pic_mode_name_create(pt_page_data->h_cnt_frm,
                              4,
                              _eb_pic_mode_name_proc_fct,
                              &pt_page_data->h_eb_name);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = _delete_pic_mode_vkb_create();
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_finish = TRUE;

    /* set visibility */
    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32       i4_ret;
    DELETE_PIC_MODE* pt_page_data = &t_delete_pic_mode_page_data;

    /* shit. */
    pt_page_data->b_finish = TRUE;

    i4_ret = _update_ui();
    MENU_LOG_ON_FAIL(i4_ret);

    /* Change the menu title */
    menu_main_set_title(MLM_MENU_KEY_MENU_ITEM_DELETE_PIC_MODE);
    menu_help_tip_keytip_show(FALSE);
    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{

    DELETE_PIC_MODE* pt_page_data = &t_delete_pic_mode_page_data;

    if(pt_page_data->b_this_page_show == FALSE)
    {
        return MENUR_OK;
    }
    menu_help_tip_keytip_show(TRUE);

    pt_page_data->b_this_page_show = FALSE;
    pt_page_data->b_finish = TRUE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    DELETE_PIC_MODE* pt_page_data = &t_delete_pic_mode_page_data;

    if(!pt_page_data->b_vkb_showed)
    {
        c_wgl_set_focus(pt_page_data->h_eb_name, WGL_NO_AUTO_REPAINT);
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
extern INT32 menu_page_delete_new_pic_mode_init(VOID)
{
    t_g_menu_page_delete_pic_mode.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_delete_pic_mode.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_delete_pic_mode.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_delete_pic_mode.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_delete_pic_mode.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_delete_pic_mode.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_delete_pic_mode.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

#endif

