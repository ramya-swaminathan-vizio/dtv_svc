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
 * $RCSfile: menu_page_tuner_fac.c,v $
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
#ifdef APP_537X_SUPPORT
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

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "app_util/a_cfg.h"
#include "menu2/menu_dbg.h"

/* If we include the "d_5371_cust.h", let this page empty */
#ifdef _D_5371_CUST_H_
    #define _EMPTY_PAGE_
#endif

#ifdef COMMON_TUNER_FAC_ENABLE

#include "c_rm.h"
#include "u_rm_dev_types.h"

#ifndef _EMPTY_PAGE_
/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MAX_TEXT_LEN   32

typedef struct _TUENR_FAC_T
{
    UINT32                  ui4_page_id;
    HANDLE_T                h_lb;
    HANDLE_T                h_timer;
    UINT16                  ui2_timer_period;
    UINT8                   ui1_item_num;
    DRV_CUSTOM_TUNER_TYPE_T e_tuner_type;
}   TUENR_FAC_T;
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_tuner_fac;

static TUENR_FAC_T  t_g_tuner_fac;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
static INT32 _lb_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
        case BTN_EXIT:
            menu_nav_back();
            return WGLR_OK;
        case BTN_CURSOR_UP:
        case BTN_CURSOR_DOWN:
            ui4_msg = WGL_MSG_KEY_DOWN;
            break;
        default:
            break;
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _tuner_fac_lb_create(
    HANDLE_T            h_parent)
{
    INT32                       i4_ret;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[2];
    GL_RECT_T                   t_rect;

    /* channel no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = MAX_TEXT_LEN;
    at_cols[0].ui2_width        = GRID_W * 8 - MENU_ITEM_BAR_CNT_INSET_L;

    /* ATV/DTV */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[1].ui2_max_text_len = MAX_TEXT_LEN;
    at_cols[1].ui2_width        = GRID_W * 8  - MENU_ITEM_BAR_CNT_INSET_R;


    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT      |
                                  WGL_STL_LB_ELEM_NO_PUSH   |
                                  WGL_STL_LB_MULTI_SEL;

    t_lb_init.ui2_max_elem_num  = 20;
    t_lb_init.ui2_elem_size     = GRID_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect, 0, 0, CONTENT_W, CONTENT_H);

    i4_ret = menu_list2_create (h_parent,
                                &t_rect,
                                _lb_proc_fct,
                                &t_lb_init,
                                NULL,
                                &t_g_tuner_fac.h_lb);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for channel list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    if(t_g_tuner_fac.ui1_item_num == 0)
    {
        i4_ret = c_wgl_do_cmd(t_g_tuner_fac.h_lb,
                              WGL_CMD_LB_SET_ELEM_NUM,
                              WGL_PACK(1),
                              WGL_PACK(NULL));
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_do_cmd(t_g_tuner_fac.h_lb,
                              WGL_CMD_LB_SET_ELEM_NUM,
                              WGL_PACK(t_g_tuner_fac.ui1_item_num),
                              WGL_PACK(NULL));
        MENU_CHK_FAIL(i4_ret);
    }


    return MENUR_OK;
}




/*---------------------------------------------------------------------------
 * Name: _tuner_c_rm_set_comp
 *Description:  set tuner compoment by RM API
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
static INT32
_tuner_c_rm_set_comp(
        DRV_CUSTOM_TUNER_TYPE_T            e_tuner_type,
        DRV_CUSTOM_TUNER_SET_TYPE_T        e_tuner_set_type,
        VOID*                              pv_set_info,
        SIZE_T                             z_size)
{
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    INT32 i4_ret;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_TUNER_SET;

    t_op_info.u.t_tuner_set_info.e_tuner_type = e_tuner_type;
    t_op_info.u.t_tuner_set_info.e_tuner_set_type = e_tuner_set_type;
    t_op_info.u.t_tuner_set_info.pv_set_info = pv_set_info;
    t_op_info.u.t_tuner_set_info.z_size = z_size;

    i4_ret = c_rm_set_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    sizeof(DRV_CUST_OPERATION_INFO_T)
                    );
    return i4_ret;
}

/*---------------------------------------------------------------------------
 * Name: _tuner_c_rm_get_comp
 *Description:  set tuner compoment by RM API
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
static INT32
_tuner_c_rm_get_comp(
        DRV_CUSTOM_TUNER_TYPE_T            e_tuner_type,
        DRV_CUSTOM_TUNER_GET_TYPE_T        e_tuner_get_type,
        VOID*                              pv_get_info,
        SIZE_T*                            pz_size)

{
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    INT32                        i4_ret;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_TUNER_GET;

    t_op_info.u.t_tuner_get_info.e_tuner_type = e_tuner_type;
    t_op_info.u.t_tuner_get_info.e_tuner_get_type = e_tuner_get_type;
    t_op_info.u.t_tuner_get_info.pv_get_info = pv_get_info;
    t_op_info.u.t_tuner_get_info.pz_size = pz_size;

    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                    );
    return i4_ret;
}

static INT32 _tuner_fac_lb_refresh(VOID)
{
    UTF16_T w2s_str[MAX_TEXT_LEN];
    INT32   i4_ret;

    if(t_g_tuner_fac.ui1_item_num == 0)
    {
        /* Name */
        c_uc_ps_to_w2s("No Diag. Info", w2s_str, 16);
        w2s_str[15] = 0;

        c_wgl_do_cmd(t_g_tuner_fac.h_lb,
                     WGL_CMD_LB_SET_ITEM_TEXT,
                     WGL_PACK_2(0, 0),
                     WGL_PACK(w2s_str));

        /* Value */
        c_uc_ps_to_w2s("", w2s_str, 16);
        w2s_str[15] = 0;

        c_wgl_do_cmd(t_g_tuner_fac.h_lb,
                     WGL_CMD_LB_SET_ITEM_TEXT,
                     WGL_PACK_2(0, 1),
                     WGL_PACK(w2s_str));
    }
    else
    {
        UINT8   ui1_i;
        SIZE_T  z_size = sizeof(TUNER_TYPE_DIAG_CONTENT_T) * t_g_tuner_fac.ui1_item_num;
        TUNER_TYPE_DIAG_CONTENT_T* pt_diag_cnt = (TUNER_TYPE_DIAG_CONTENT_T*) c_mem_alloc(z_size);

        i4_ret = _tuner_c_rm_get_comp(t_g_tuner_fac.e_tuner_type,
                               DRV_CUSTOM_TUNER_GET_TYPE_DIAG_CONTENT,
                               pt_diag_cnt,
                               &z_size);
        MENU_LOG_ON_FAIL(i4_ret);

        for(ui1_i=0; ui1_i < t_g_tuner_fac.ui1_item_num; ui1_i++)
        {
            /* Name */
            c_uc_ps_to_w2s(pt_diag_cnt[ui1_i].cDisplayName, w2s_str, 16);
            w2s_str[15] = 0;

            c_wgl_do_cmd(t_g_tuner_fac.h_lb,
                         WGL_CMD_LB_SET_ITEM_TEXT,
                         WGL_PACK_2(ui1_i, 0),
                         WGL_PACK(w2s_str));

            /* Value */
            c_uc_ps_to_w2s(pt_diag_cnt[ui1_i].cDisplayValue, w2s_str, 16);
            w2s_str[15] = 0;

            c_wgl_do_cmd(t_g_tuner_fac.h_lb,
                         WGL_CMD_LB_SET_ITEM_TEXT,
                         WGL_PACK_2(ui1_i, 1),
                         WGL_PACK(w2s_str));
        }

        c_mem_free(pt_diag_cnt);
    }

    return MENUR_OK;
}

static VOID _do_timer_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    MENU_PAGE_STATE_T   e_state;

    menu_page_get_state(t_g_tuner_fac.ui4_page_id, &e_state);
    if(e_state == MENU_PAGE_STATE_FOCUS)
    {
        _tuner_fac_lb_refresh();
        c_wgl_repaint(t_g_tuner_fac.h_lb, NULL, WGL_SYNC_AUTO_REPAINT);
    }
}

static VOID _timer_nfy_fct(
    HANDLE_T  h_timer,
    VOID*     pv_tag)
{
    menu_async_invoke(_do_timer_nfy,
                      NULL,
                      0,
                      FALSE);
}

static INT32 _tuner_fac_timer_create(VOID)
{
    if(t_g_tuner_fac.ui2_timer_period != 0)
    {
        /* Create the timer */
        c_timer_create(&t_g_tuner_fac.h_timer);

        /* Start the timer */
        c_timer_start(t_g_tuner_fac.h_timer,
                      t_g_tuner_fac.ui2_timer_period,
                      X_TIMER_FLAG_REPEAT,
                      _timer_nfy_fct,
                      NULL);
    }

    return MENUR_OK;
}

static INT32 _tuner_fac_timer_destroy(VOID)
{
    if(t_g_tuner_fac.h_timer != NULL_HANDLE)
    {
        /* Stop the timer */
        c_timer_stop(t_g_tuner_fac.h_timer);

        /* Destroy the timer */
        c_timer_delete(t_g_tuner_fac.h_timer);
    }

    return MENUR_OK;
}

static INT32 _tuner_fac_help_lst_update(VOID)
{
    /* use help tip instead of menu's help list */
    #if 0
    MENU_HELP_LST_BUCKET_T at_help_lst[] =
    {
        {h_g_menu_img_btn_select,   MLM_MENU_KEY_HELP_SELECT},
        {h_g_menu_img_btn_exit,     MLM_MENU_KEY_HELP_BACK}
    };

    menu_main_set_help(at_help_lst,
                       (UINT16)(sizeof(at_help_lst)/ sizeof(at_help_lst[0])));
    #endif

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
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
    INT32                       i4_ret;
    HANDLE_T                    h_cnt_frm;
    TUNER_TYPE_DIAG_CONTROL_T   t_diag_ctrl;
    SIZE_T                      z_size = sizeof(TUNER_TYPE_DIAG_CONTROL_T);
    SVL_REC_T                   t_svl_rec;
    BOOL                        b_found;

    c_memset(&t_g_tuner_fac, 0, sizeof(t_g_tuner_fac));

    t_g_tuner_fac.ui4_page_id = ui4_page_id;

    /* Get the tuner type */
    menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
    if(b_found &&
       t_svl_rec.uheader.t_rec_hdr.e_brdcst_type != BRDCST_TYPE_ANALOG)
    {
        t_g_tuner_fac.e_tuner_type = DRV_CUSTOM_TUNER_TYPE_DIGITAL;
    }
    else
    {
        t_g_tuner_fac.e_tuner_type = DRV_CUSTOM_TUNER_TYPE_ANALOG;
    }

    /* Open the Diagnosetic */
    i4_ret = _tuner_c_rm_set_comp(t_g_tuner_fac.e_tuner_type,
                            DRV_CUSTOM_TUNER_SET_TYPE_DIAG_OPEN,
                            NULL,
                            0
                            );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Get the Diagnosetic Control */
    c_memset(&t_diag_ctrl, 0, sizeof(t_diag_ctrl));
    i4_ret = _tuner_c_rm_get_comp(t_g_tuner_fac.e_tuner_type,
                                DRV_CUSTOM_TUNER_GET_TYPE_DIAG_CONTROL,
                                &t_diag_ctrl,
                                &z_size);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret == 0)
    {
        t_g_tuner_fac.ui1_item_num      = (UINT8)  t_diag_ctrl.ucCntOfDiagStruc;
        t_g_tuner_fac.ui2_timer_period  = (UINT16) t_diag_ctrl.u2PollPeriodMs;
    }
    else
    {
        t_g_tuner_fac.ui1_item_num      = 0;
        t_g_tuner_fac.ui2_timer_period  = 0;
    }

    /* Create the lisbox */
    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _tuner_fac_lb_create(h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    /* Refresh */
    i4_ret = _tuner_fac_lb_refresh();

    /* Create and start the timer */
    i4_ret = _tuner_fac_timer_create();

    /* Set the listbox visable */
    c_wgl_set_visibility(t_g_tuner_fac.h_lb, WGL_SW_NORMAL);

    /* Change the menu title */
    menu_main_set_title(MLM_MENU_KEY_TUNER_DIAG);

    /* Change the help list */
    _tuner_fac_help_lst_update();

    /* Disable the channel change in background */
    t_g_menu_is_scanning = TRUE;
    a_amb_channel_scan_active(TRUE);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32              i4_ret;

    /* Close the Diagnosetic */
    i4_ret = _tuner_c_rm_set_comp(t_g_tuner_fac.e_tuner_type,
                                DRV_CUSTOM_TUNER_SET_TYPE_DIAG_CLOSE,
                                NULL,
                                0);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Destroy listbox */
    i4_ret = c_wgl_destroy_widget_ex(t_g_tuner_fac.h_lb, FALSE);
    MENU_CHK_FAIL(i4_ret);

    /* Stop and destroy the timer */
    i4_ret = _tuner_fac_timer_destroy();

    /* Enalbe the channel change in background */
    t_g_menu_is_scanning = FALSE;
    a_amb_channel_scan_active(FALSE);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32              i4_ret;

    i4_ret = c_wgl_set_focus(t_g_tuner_fac.h_lb, FALSE);
    MENU_CHK_FAIL(i4_ret);

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

#else /* #ifdef _EMPTY_PAGE_ */

/* In 537x 5330,5331, 5332, there is no tuner fac API defined in d_5371_cust.h
   We leave this page empty and make the compiler happy
*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_tuner_fac;

static INT32 _on_page_create(UINT32 ui4_page_id,VOID*  pv_create_data)          {return MENUR_OK;}
static INT32 _on_page_destroy(UINT32 ui4_page_id)                               {return MENUR_OK;}
static INT32 _on_page_show(UINT32 ui4_page_id)                                  {return MENUR_OK;}
static INT32 _on_page_hide(UINT32 ui4_page_id)                                  {return MENUR_OK;}
static INT32 _on_page_get_focus(UINT32 ui4_page_id,MENU_PAGE_HINT_T* pt_hint)   {return MENUR_OK;}
static INT32 _on_page_lose_focus(UINT32 ui4_page_id)                            {return MENUR_OK;}
static INT32 _on_page_update(UINT32 ui4_page_id, UINT32 ui4_update_mask)        {return MENUR_OK;}
#endif /* _EMPTY_PAGE_ */

extern INT32 menu_common_page_tuner_fac_init(VOID)
{
    t_g_menu_common_page_tuner_fac.pf_menu_page_create    = _on_page_create;
    t_g_menu_common_page_tuner_fac.pf_menu_page_destroy   = _on_page_destroy;
    t_g_menu_common_page_tuner_fac.pf_menu_page_show      = _on_page_show;
    t_g_menu_common_page_tuner_fac.pf_menu_page_hide      = _on_page_hide;
    t_g_menu_common_page_tuner_fac.pf_menu_page_get_focus = _on_page_get_focus;
    t_g_menu_common_page_tuner_fac.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_tuner_fac.pf_menu_page_update    = _on_page_update;

    return MENUR_OK;
}
#endif /* COMMON_TUNER_FAC_ENABLE */
#endif /* APP_537X_SUPPORT */

