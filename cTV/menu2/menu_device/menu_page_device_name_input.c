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
 * $RCSfile: menu_page_adv_scan_rng.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/22 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 223730d1bdc36ed27cb26dea5de9232d $
 *
 * Description:
 *      This scan includes both ATV channel scan and DTV channel scan.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_sb_atsc_eng.h"
#include "u_sb_cqam_eng.h"
#include "u_sb_ntsc_eng.h"
#include "u_cli.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svctx.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_sb.h"
#include "c_dt.h"
#include "c_net_p2p_ctl.h"

#include "res/app_util/config/acfg_custom.h"
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu_page_device_setting.h"
#include "menu_device.h"
#include "menu_page_device_status_info.h"
#include "menu_page_pair_wifi_device.h"
#include "menu2/menu_common/menu_page_animation.h"

#include "wdk/a_vkb.h"
#include "wdk/a_wdk.h"
#include "res/wdk/a_vkb_custom.h"
#include "wdk/vkb/vkb.h"

#include "menu_page_device_name_input.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct _MENU_DEVICE_NAME_INPUT_PAGE_DATA_T
{
    HANDLE_T     h_cnt_frm;
    HANDLE_T     h_vkb;
    HANDLE_T     h_vkb_last_focus;
    CHAR         s_input_buf[INPUT_NAME_MAX_LEN+1];
}MENU_DEVICE_NAME_INPUT_PAGE_DATA_T;

/*-----------------------------------------------------------------------------
              data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_name_input;
static MENU_DEVICE_NAME_INPUT_PAGE_DATA_T t_g_device_name_input_page_data;


/*-----------------------------------------------------------------------------
                 function declarations
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                  function implementations
----------------------------------------------------------------------------*/
static INT32 _device_name_input_page_backbar_proc_fct(
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
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32  i4_ret = MENUR_OK;
        //MENU_DEVICE_NAME_INPUT_PAGE_DATA_T* pt_this = &t_g_device_name_input_page_data;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
        #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                i4_ret = menu_device_page_nav_go(NAV_PREV_PAGE_FROM_CURRENT_PAGE,
                                                 NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }

            case BTN_CURSOR_DOWN:
            {

            }
                break ;

            case BTN_CURSOR_UP:
            {
                i4_ret = menu_set_focus_on_homebar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;

            default:
                break ;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _device_name_input_page_homebar_proc_fct(
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
        INT32  i4_ret = MENUR_OK;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
        #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                i4_ret = menu_device_page_nav_go(NAV_ROOT_MENU_FROM_ANY_PAGE,
                                                 NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }

            case BTN_CURSOR_DOWN:
            {
                i4_ret = menu_set_focus_on_backbar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;

            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

static INT32 _name_input_page_vkb_data_change_nfy (
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
        MENU_DEVICE_NAME_INPUT_PAGE_DATA_T* pt_this = &t_g_device_name_input_page_data;
        UTF16_T             w2s_str[INPUT_NAME_MAX_LEN+1] = {0};

        switch(*pui4_key_code)
        {
            case BTN_EXIT:
            case BTN_PREV_PRG:
            case BTN_RETURN:
            {
                i4_ret = a_vkb_do_cmd(pt_this->h_vkb,
                             VKB_CMD_GET_TEXT,
                             WGL_PACK (w2s_str),
                             WGL_PACK (INPUT_NAME_MAX_LEN));
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_uc_w2s_to_ps(w2s_str, pt_this->s_input_buf, INPUT_NAME_MAX_LEN);
                MENU_LOG_ON_FAIL(i4_ret);

                //menu_network_page_nav_go(MENU_NETWORK_NAV_BACK, NULL);

                menu_pm_repaint();
            }
                break;

            case BTN_CURSOR_UP:
            {
                i4_ret = a_vkb_current_is_top_row(pt_this->h_vkb,&b_is_top_bottom);
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
            }
                break;

            case BTN_CURSOR_DOWN:
            {
                i4_ret = a_vkb_current_is_bottom_row(pt_this->h_vkb,
                                                     &pt_this->h_vkb_last_focus,
                                                     &b_is_top_bottom);
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

static INT32 _name_input_page_vkb_create(VOID)
{
    INT32       i4_ret = MENUR_OK;

    MENU_DEVICE_NAME_INPUT_PAGE_DATA_T* pt_this = &t_g_device_name_input_page_data;
    VKB_INIT_T           t_init_data;

    c_memset(&t_init_data, 0, sizeof(t_init_data));
    t_init_data.h_parent            = pt_this->h_cnt_frm;
    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_WIFI_SSID | VKB_STYLE_MASK_NO_COM_KEY;
    t_init_data.t_gui_rc.i4_left    = MENU_ITEM_V_INSET_L;
    t_init_data.t_gui_rc.i4_top     = (GRID_H*3 - 15*4/3);
    t_init_data.pf_data_change_fct  = _name_input_page_vkb_data_change_nfy;
    t_init_data.pv_tag              = NULL;

    i4_ret = a_vkb_create(&t_init_data,&pt_this->h_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_name_input_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_NAME_INPUT_PAGE_DATA_T* pt_this = &t_g_device_name_input_page_data;

    c_memset(pt_this, 0, sizeof(MENU_DEVICE_NAME_INPUT_PAGE_DATA_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_this->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _name_input_page_vkb_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_name_input_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _device_name_input_page_show(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_NAME_INPUT_PAGE_DATA_T* pt_this = &t_g_device_name_input_page_data;

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_main_set_title(MLM_MENU_KEY_NAME_DEVICE_TITLE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_NAME_DEVICE_HELP_TIP));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_backbar_proc(_device_name_input_page_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(_device_name_input_page_homebar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_name_input_page_hide(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_name_input_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_NAME_INPUT_PAGE_DATA_T* pt_this = &t_g_device_name_input_page_data;

    i4_ret = a_vkb_set_focus(pt_this->h_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_name_input_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _device_name_input_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)

{
    return MENUR_OK;
}

extern INT32 menu_device_page_name_input_init(VOID)
{
    t_g_menu_device_page_name_input.pf_menu_page_create =    _device_name_input_page_create;
    t_g_menu_device_page_name_input.pf_menu_page_destroy=    _device_name_input_page_destroy;
    t_g_menu_device_page_name_input.pf_menu_page_show=       _device_name_input_page_show;
    t_g_menu_device_page_name_input.pf_menu_page_hide=       _device_name_input_page_hide;
    t_g_menu_device_page_name_input.pf_menu_page_get_focus=  _device_name_input_page_get_focus;
    t_g_menu_device_page_name_input.pf_menu_page_lose_focus= _device_name_input_page_lose_focus;
    t_g_menu_device_page_name_input.pf_menu_page_update=     _device_name_input_page_update;

    return MENUR_OK;
}


