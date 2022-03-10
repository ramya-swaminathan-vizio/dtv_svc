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
 * $RCSfile: menu_page_ip_setting_dhcp.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "c_svctx.h"
#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_tsl.h"
#include "c_wgl_sets.h"
#include "c_version.h"

#include "menu2/menu_util2.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_page_tree.h"
#include "app_util/a_network.h"

#include "app_util/a_cfg.h"
#include "res/app_util/network/network_custom.h"

#include "menu2/menu_common/menu_page_animation.h"
#include "menu_network.h"
#include "res/app_util/config/acfg_custom.h"
#include "menu2/menu_dbg.h"


typedef struct _PAGE_DHCP_STATE_T
{
    HANDLE_T    h_cnt_frm;
    HANDLE_T    h_listbox;
}PAGE_DHCP_STATE_T;

typedef struct __NW_NFY_DATA
{
    VOID*       pv_tag;
    NW_NFY_ID_T e_nfy_id;
    VOID*       pv_nfy_param;
}_NW_NFY_DATA;

MENU_PAGE_FCT_TBL_T    t_g_menu_common_ip_setting_dhcp;
static PAGE_DHCP_STATE_T    t_page_dhcp_state;
static UINT32               ui4_dhcp_nw_nfy_id = 0;

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
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return MENUR_OK;
        #endif
        case BTN_SELECT :
        case BTN_RETURN:
            menu_nav_back () ;
            return MENUR_OK ;

        case BTN_CURSOR_RIGHT :
        case BTN_CURSOR_DOWN:
            c_wgl_set_focus(t_page_dhcp_state.h_listbox, WGL_SYNC_AUTO_REPAINT);
            break ;

        case BTN_CURSOR_UP:
            MENU_LOG_ON_FAIL (menu_set_focus_on_homebar(TRUE));
            break;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
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
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
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
            menu_nav_back () ;
            return MENUR_OK ;

        case BTN_CURSOR_DOWN :
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
            break ;

        default:
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _nw_notify_handler
 *
 * Description: use to deal with the notify messageo of network
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static VOID _dhcp_nw_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
    _NW_NFY_DATA*        pt_nw_nfy_data = (_NW_NFY_DATA*)pv_data;

    switch(pt_nw_nfy_data->e_nfy_id)
    {
    case NW_NFY_ID_ETHERNET_UNPLUG:
    case NW_NFY_ID_ETHERNET_PLUGIN:
        DBG_INFO(("the network status was changed: PLUGIN/UNPLUG\n"));
        menu_nav_go_home_menu();
        break;
    default:
        break;
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _nw_notify_callback
 *
 * Description: network callback function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _dhcp_nw_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    _NW_NFY_DATA t_nw_nfy_data;

    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;
    menu_async_invoke(_dhcp_nw_notify_handler,&t_nw_nfy_data,sizeof(_NW_NFY_DATA),TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _page_dhcp_state_lb_proc_fct
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
static INT32 _page_dhcp_state_lb_proc_fct(HANDLE_T    h_widget,
                                  UINT32      ui4_msg,
                                  VOID*       param1,
                                  VOID*       param2)
{
    NW_IP_INFO_T            t_dhcp_page_ip_info;
    UINT8                   ui1_interface = 0;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NET_CFG_AT_HELP));

    #ifdef APP_TTS_SUPPORT
        INT32  i4_ret = MENUR_OK;
        UINT16 ui2_idx = 0;
        UTF16_T w2s_tts[32] = {0};

        i4_ret = c_wgl_do_cmd (h_widget,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK (&ui2_idx),
                          NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strcat(w2s_tts, MENU_TTS_TEXT(MLM_MENU_KEY_NET_CFG_AT_AUTO + ui2_idx));

        a_app_tts_play(w2s_tts, c_uc_w2s_strlen(w2s_tts));
    #endif
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_keycode = (UINT32)param1;
        UINT16  ui2_idx = 0;
        INT32   i4_ret;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_DOWN:
            i4_ret = menu_list_get_idx(t_page_dhcp_state.h_listbox, &ui2_idx);
            MENU_LOG_ON_FAIL(i4_ret);
            if(ui2_idx == 2)
            {
                i4_ret = menu_help_tip_keytip_set_focus(h_widget,0,FALSE);
                return i4_ret;
            }
            break;
        case BTN_CURSOR_UP:
            i4_ret = menu_list_get_idx(t_page_dhcp_state.h_listbox, &ui2_idx);
            MENU_LOG_ON_FAIL(i4_ret);
            if(ui2_idx == 0)
            {
                menu_set_focus_on_backbar(TRUE);
                return i4_ret;
            }
            break;
        case BTN_SELECT:
            i4_ret = menu_list_get_idx(t_page_dhcp_state.h_listbox, &ui2_idx);
            MENU_LOG_ON_FAIL(i4_ret);

            if (ui2_idx == 0)
            {
                i4_ret = nw_custom_set_auto_ip_config(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = nw_custom_set_dhcp_status(ACFG_DHCP_OFF);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                /* for dns only */
                if (1 == ui2_idx)
                {
                    i4_ret = nw_custom_set_dhcp_status(ACFG_DHCP_OFF);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else if (2 == ui2_idx)
                {
                    i4_ret = nw_custom_set_dhcp_status(ACFG_DHCP_DNS_ONLY);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                i4_ret = nw_custom_get_network_interface(&ui1_interface);
                if(MENUR_OK != i4_ret)
                {
                    DBG_ERROR(("[ip setting:-----%s--%d--%d--]\n",__FUNCTION__, __LINE__, i4_ret));
                }

                if (NW_NET_INTERFACE_WIFI == ui1_interface)
                {
                    DBG_INFO(("[network ip setting]----wifi: change to manual set ip-----\n"));

                    c_memset(&t_dhcp_page_ip_info, 0, sizeof(NW_IP_INFO_T));
                    i4_ret = a_nw_get_crnt_ip_info(&t_dhcp_page_ip_info );
                    if(MENUR_OK != i4_ret)
                    {
                        DBG_ERROR(("[ip setting:-----%s--%d--%d--]\n",__FUNCTION__, __LINE__, i4_ret));
                    }
                    i4_ret = a_nw_manual_ip_config(&t_dhcp_page_ip_info);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                i4_ret = nw_custom_set_auto_ip_config(FALSE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            i4_ret = menu_nav_back();
            MENU_LOG_ON_FAIL(i4_ret);
            return i4_ret;
        case BTN_EXIT:
            break;
        case BTN_RETURN:
            i4_ret = menu_nav_back();
            return i4_ret;
        default:
            break;
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _dhcp_list_notify
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
static INT32 _dhcp_list_notify(HANDLE_T    h_lb_dhcp,
                               WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    PAGE_DHCP_STATE_T*  pt_page_data = &t_page_dhcp_state;

    if (pt_page_data->h_listbox != h_lb_dhcp)
    {
        return WMPR_DONE;
    }

    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_LB_ELEM_SEL:
        {
            break;
        }

    case WGL_NC_LB_ELEM_HLT:
        {
#ifdef APP_TTS_SUPPORT
        UTF16_T           w2s_text[32] = {0};

        c_wgl_do_cmd(h_lb_dhcp,
                      WGL_CMD_LB_GET_ITEM_TEXT,
                      WGL_PACK_2(pt_nfy_data->u.t_lb_elem_hlt.ui2_elem_idx, 0),
                      WGL_PACK(w2s_text));

        a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
#endif
            break;
        }

    default:
        break;
    }
    return WMPR_DONE;
}

/*----------------------------------------------------------------------------
 * Name: _dhcp_frm_proc_fct
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
static INT32 _dhcp_frm_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
            HANDLE_T h_source = (HANDLE_T)param1;
            WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)param2;
            _dhcp_list_notify(h_source, pt_nfy_data);
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _page_dhcp_state_lb_create
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
static INT32 _page_dhcp_state_lb_create(VOID)
{
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    INT32               i4_ret;
    PAGE_DHCP_STATE_T*  pt_page_data = &t_page_dhcp_state;

    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 15;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

    t_lb_init.ui4_style         =  WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_MULTI_SEL
                                  | WGL_STL_LB_NO_WRAP_OVER;
    t_lb_init.ui2_max_elem_num  = 3;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     0,
                     CONTENT_W,
                     CONTENT_H);

    i4_ret = menu_list2_create(pt_page_data->h_cnt_frm,
                               &t_rect,
                               _page_dhcp_state_lb_proc_fct,
                               &t_lb_init,
                               NULL,
                               &pt_page_data->h_listbox);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (pt_page_data->h_listbox,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_do_cmd(pt_page_data->h_listbox,
                 WGL_CMD_LB_SET_ELEM_NUM,
                 WGL_PACK(3),
                 NULL);

    return (MENUR_OK);
}
/*----------------------------------------------------------------------------
 * Name: _on_page_create
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
static INT32 _on_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32       i4_ret;
    PAGE_DHCP_STATE_T   *pt_page_data = &t_page_dhcp_state;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &pt_page_data->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_dhcp_state_lb_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id,
                                     _dhcp_frm_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_destroy
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
static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _on_page_show
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
static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32               i4_ret = MENUR_OK;
    PAGE_DHCP_STATE_T*  pt_page_data = &t_page_dhcp_state;
    BOOL                b_auto_ip;
    UINT8               ui1_dhcp_status = ACFG_DHCP_OFF;
    UINT16              ui2_hlt_idx = 0;
    UINT16              ui2_i;
    UTF16_T             w2s_str[15] = {0};
    GL_RECT_T           t_rect = {0};
    HANDLE_T		    h_last_shadow_item = NULL_HANDLE;

    /* Show the listbox and insert the items to the listbox */
    for (ui2_i = 0; ui2_i < 3; ui2_i++)
    {
        c_uc_w2s_strcpy(w2s_str,
                        MENU_TEXT(MLM_MENU_KEY_NET_CFG_AT_AUTO + ui2_i));

        c_wgl_do_cmd(pt_page_data->h_listbox,
                     WGL_CMD_LB_SET_ITEM_TEXT,
                     WGL_PACK_2 (ui2_i, 0),
                     w2s_str);
    }

    i4_ret = nw_custom_get_auto_ip_config(&b_auto_ip);
    MENU_LOG_ON_FAIL(i4_ret);

    /*network  callback function*/
    i4_ret = a_nw_register(_dhcp_nw_notify_callback, NULL, &ui4_dhcp_nw_nfy_id );
    MENU_LOG_ON_FAIL(i4_ret);

    if (b_auto_ip)
    {
        ui2_hlt_idx = 0;
    }
    else
    {
        i4_ret = nw_custom_get_dhcp_status(&ui1_dhcp_status);
        MENU_LOG_ON_FAIL(i4_ret);

        if (ACFG_DHCP_OFF == ui1_dhcp_status)
        {
            ui2_hlt_idx = 1;
        }
        else if (ACFG_DHCP_DNS_ONLY == ui1_dhcp_status)
        {
            ui2_hlt_idx = 2;
        }
    }

    i4_ret = c_wgl_do_cmd(pt_page_data->h_listbox,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK((UINT16)(ui2_hlt_idx)),
                          WGL_PACK(0));

    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_focus(pt_page_data->h_listbox,WGL_NO_AUTO_REPAINT);

    i4_ret = c_wgl_show(pt_page_data->h_listbox,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* adjust last shadow position */
	t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;
	t_rect.i4_top = MENU_ITEM_V_HEIGHT * 3 + CONTENT_Y;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;

	menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

    return  i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _on_page_hide
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
static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32       i4_ret;

    i4_ret = menu_network_last_shadow_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    /*unregister network message callback*/
    i4_ret = a_nw_unregister(ui4_dhcp_nw_nfy_id);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _on_page_get_focus
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
static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T * pt_hint)
{
    menu_common_help_show_back();

    /* set callback function for backbar */
    menu_set_backbar_proc (_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _on_page_lose_focus
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
static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    HANDLE_T    h_cnt_frm = NULL_HANDLE;

    /* clean callback function of backbar */
    MENU_LOG_ON_FAIL (menu_set_backbar_proc (NULL)) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                               &h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_visibility(h_cnt_frm,
                        WGL_SW_HIDE_RECURSIVE);

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_common_page_ip_setting_dhcp_init
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
extern INT32 menu_common_page_ip_setting_dhcp_init(VOID)
{
    t_g_menu_common_ip_setting_dhcp.pf_menu_page_create = _on_page_create;
    t_g_menu_common_ip_setting_dhcp.pf_menu_page_destroy = _on_page_destroy;
    t_g_menu_common_ip_setting_dhcp.pf_menu_page_show= _on_page_show;
    t_g_menu_common_ip_setting_dhcp.pf_menu_page_hide = _on_page_hide;
    t_g_menu_common_ip_setting_dhcp.pf_menu_page_get_focus = _on_page_get_focus;
    t_g_menu_common_ip_setting_dhcp.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_ip_setting_dhcp.pf_menu_page_update = _on_page_update;

    return MENUR_OK;
}

