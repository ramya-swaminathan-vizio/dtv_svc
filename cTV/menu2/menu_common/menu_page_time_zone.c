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
 * $RCSfile: menu_page_time_zone.c,v $
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

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_dt.h"
#include "c_pcl.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"


#include "app_util/a_cfg.h"
#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_page_tree.h"
#include "menu2/menu_common/menu_common.h"

#ifdef COMMON_GUI_TIME_ZONE_SELECTION
#include "res/theme/theme_img.h"
#endif

#include "menu2/menu_dbg.h"
#ifdef COMMON_GUI_TIME_ZONE_SELECTION

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_custom_page_time_zone;
static MENU_ITEM_T   t_menu_additional_item;
static HANDLE_T      h_lb_additional;

static    HANDLE_T      h_time_zone_map_icon;           /* time zone map icon */

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _get_menu_item_data_by_widget
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
static INT32 _get_menu_item_data_by_widget(
    HANDLE_T           h_widget,
    MENU_ITEM_T**      ppt_menu_item)
{
    INT32 i4_ret;
    if(h_widget == NULL_HANDLE)
    {
        return MENUR_INV_ARG;
    }


    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_menu_item),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _set_time_zone_idx
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
static VOID _set_time_zone_idx(UINT16 ui2_idx)
{
    a_cfg_set_time_zone((UINT8)ui2_idx);

    a_cfg_update_time_zone();

    a_cfg_update_timer_power();
}

/*----------------------------------------------------------------------------
 * Name: _get_time_zone_idx
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
static UINT16 _get_time_zone_idx(VOID)
{
    UINT8 ui1_tz = APP_CFG_TZ_EASTERN_TIME;

    a_cfg_get_time_zone(&ui1_tz);

    return (UINT16)ui1_tz;
}

/*----------------------------------------------------------------------------
 * Name: _lb_additional_item_proc_fct
 *
 * Description: Additional menu item proc fct
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _lb_additional_item_proc_fct(HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       param1,
                                          VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
            case BTN_CURSOR_RIGHT:
                {
                    UINT16       ui2_idx;
                    MENU_ITEM_T* pt_menu_item;
                    _get_menu_item_data_by_widget(h_widget, &pt_menu_item);

                    if(pt_menu_item->u.t_list.pf_prev_idx != NULL)
                    {
                        ui2_idx = pt_menu_item->u.t_list.pf_prev_idx();
                        if(ui2_idx < pt_menu_item->u.t_list.ui2_elem_num)
                        {
                            menu_list_set_idx(h_widget, ui2_idx);
                        }
                    }
                    else
                    {
                        c_wgl_do_cmd(h_widget,
                                     WGL_CMD_LB_HLT_PREV_ELEM,
                                     WGL_PACK(FALSE),
                                     NULL);

                        menu_list_get_idx(h_widget, &ui2_idx);
                        pt_menu_item->u.t_list.pf_set_idx(ui2_idx);

                        /*change img*/
                        theme_time_zone_load_icon(h_time_zone_map_icon, ui2_idx, TRUE);

                    }

                    c_wgl_repaint(h_widget, NULL, TRUE);
                }
                return WMPR_DONE;

            case BTN_CURSOR_LEFT:
                {
                    UINT16       ui2_idx;
                    MENU_ITEM_T* pt_menu_item;
                    _get_menu_item_data_by_widget(h_widget, &pt_menu_item);

                    if(pt_menu_item->u.t_list.pf_next_idx != NULL)
                    {
                        ui2_idx = pt_menu_item->u.t_list.pf_next_idx();
                        if(ui2_idx < pt_menu_item->u.t_list.ui2_elem_num)
                        {
                            menu_list_set_idx(h_widget, ui2_idx);
                        }
                    }
                    else
                    {
                        c_wgl_do_cmd(h_widget,
                                     WGL_CMD_LB_HLT_NEXT_ELEM,
                                     WGL_PACK(FALSE),
                                     NULL);

                        menu_list_get_idx(h_widget, &ui2_idx);
                        pt_menu_item->u.t_list.pf_set_idx(ui2_idx);

                         /*change img*/
                        theme_time_zone_load_icon(h_time_zone_map_icon, ui2_idx, TRUE);
                    }

                    c_wgl_repaint(h_widget, NULL, TRUE);
                }
                return WMPR_DONE;

            case BTN_RETURN:
                menu_nav_back();
                return WMPR_DONE;

            default:
                break;
            }
        }
        break;
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    HANDLE_T      h_cnt_frm;
    INT32         i4_ret = 0;
  GL_RECT_T     t_rect;

  SET_RECT_BY_SIZE(&t_rect,
                     TIME_ZONE_ICON_MENU_X,
                     TIME_ZONE_ICON_Y,
                     TIME_ZONE_ICON_W,
                     TIME_ZONE_ICON_H);

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    /* Additional menu_item founded */
    c_memset(&t_menu_additional_item, 0, sizeof(MENU_ITEM_T));

  t_menu_additional_item.e_item_type                   = MENU_ITEM_TYPE_LIST;
  t_menu_additional_item.ui2_msgid_title               = MLM_MENU_KEY_TIME_ZONE;
  t_menu_additional_item.u.t_list.pf_set_idx           = _set_time_zone_idx;
  t_menu_additional_item.u.t_list.pf_get_idx           = _get_time_zone_idx;
  t_menu_additional_item.u.t_list.ui2_msgid_elem_first = MLM_MENU_KEY_TIME_ZONE_EAS;
  t_menu_additional_item.u.t_list.ui2_msgid_elem_last  = MLM_MENU_KEY_TIME_ZONE_HAW;
  t_menu_additional_item.u.t_list.ui2_elem_num         = MLM_MENU_KEY_TIME_ZONE_HAW -
                                                     MLM_MENU_KEY_TIME_ZONE_EAS + 1;

    i4_ret = menu_list_create(h_cnt_frm,
                              0,
                              t_menu_additional_item.u.t_list.ui2_elem_num,
                              _lb_additional_item_proc_fct,
                              &h_lb_additional);

    MENU_CHK_FAIL(i4_ret);

    menu_list_chg_lang(h_lb_additional,
                       t_menu_additional_item.ui2_msgid_title,
                       t_menu_additional_item.u.t_list.ui2_msgid_elem_first,
                       t_menu_additional_item.u.t_list.ui2_msgid_elem_last);

    /* Attach the menuitem on the widget */

    c_wgl_do_cmd(h_lb_additional,
                 WGL_CMD_GL_SET_ATTACH_DATA,
                 WGL_PACK(&t_menu_additional_item),
                 NULL);


    /*create icon widget*/
    theme_img_init();
    i4_ret = theme_time_zone_create_icon_widget(h_cnt_frm,
                                                NULL,
                                                t_rect,
                                                &h_time_zone_map_icon);
    MENU_CHK_FAIL(i4_ret);

    /* Set visibility */
    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

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
    UINT16 ui2_list_idx;

    /* title */
    menu_main_set_title(MLM_MENU_KEY_TIME_ZONE);

    ui2_list_idx = t_menu_additional_item.u.t_list.pf_get_idx();
    menu_list_set_idx(h_lb_additional, ui2_list_idx);

    /* get and load image*/
    theme_time_zone_load_icon(h_time_zone_map_icon, ui2_list_idx, FALSE);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    theme_time_zone_load_icon(h_time_zone_map_icon, THEME_IMG_TIME_ZONE_ICON_DISABLE, TRUE);
    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    c_wgl_set_focus(h_lb_additional, WGL_NO_AUTO_REPAINT);
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
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        menu_list_chg_lang(h_lb_additional,
                           t_menu_additional_item.ui2_msgid_title,
                           t_menu_additional_item.u.t_list.ui2_msgid_elem_first,
                           t_menu_additional_item.u.t_list.ui2_msgid_elem_last);
    }
    return MENUR_OK;
}

extern INT32 menu_custom_page_time_zone_init(VOID)
{
    t_g_menu_custom_page_time_zone.pf_menu_page_create =    _on_page_create;
    t_g_menu_custom_page_time_zone.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_custom_page_time_zone.pf_menu_page_show=       _on_page_show;
    t_g_menu_custom_page_time_zone.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_custom_page_time_zone.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_custom_page_time_zone.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_custom_page_time_zone.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
#endif
