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
 * $RCSfile: menu_page_op_vchip.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/19 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 7ed3c11a9ed90eba15305b24039bcab7 $
 *
 * Description:
 *      This file contains the implementation of region pard of open vchip.
 *---------------------------------------------------------------------------*/

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_sb.h"
#include "u_rrctx.h"
#include "u_rrctx_rrt_eng.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_rrctx.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"

#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_dbg.h"


#ifdef ATSC_OP_VCHIP_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/* Max numbers of the regions, of the dimensions per region, and of the levels per dimension */
#define MENU_OP_VCHIP_MAX_RGN_NUM       ((UINT8)  8)
#define MENU_OP_VCHIP_MAX_DIM_NUM       ((UINT8) 32)
#define MENU_OP_VCHIP_MAX_LVL_NUM       ((UINT8) 32)

#define MENU_ELM_TEXT_MAX_LEN           ((UINT8) 32)
#define MENU_LVL_ELM_IDX_OFFSET         ((UINT8)  1)

/* Page Types of the Open-Vchip */
#define MENU_OP_VCHIP_RGN_PAGE          ((UINT8)  0)
#define MENU_OP_VCHIP_DIM_PAGE          ((UINT8)  1)
#define MENU_OP_VCHIP_LVL_PAGE          ((UINT8)  2)
#define MENU_OP_VCHIP_TOTAL_PAGE_NUM    ((UINT8)  3)

/* The specific page don't have the subpage */
#define MENU_OP_VCHIP_NO_SUBPAGE        ((UINT32)  0x0f0f0f0f)

/* If the ui1_prev_sel_idx & ui1_crnt_sel_idx are set as this definition.
   The page element needed to rebuilt.
   Used in the Region and Dimension Pages */
#define MENU_OP_VCHIP_NO_SEL_IDX        ((UINT8) 255)

/* Only used in the Level Page */
#define MENU_OP_VCHIP_NO_BLOCK_LVL      ((UINT8) 255)

#ifndef MENU_OP_VCHIP_X
#define MENU_OP_VCHIP_X                 (0)
#endif
#ifndef MENU_OP_VCHIP_Y
#define MENU_OP_VCHIP_Y                 (0)
#endif
#ifndef MENU_OP_VCHIP_W
#define MENU_OP_VCHIP_W                 ((CONTENT_W))
#endif
#ifndef MENU_OP_VCHIP_H
#define MENU_OP_VCHIP_H                 (10 * GRID_H)
#endif

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T     t_g_menu_atsc_page_op_vchip;

/* RRCTX RRT */
static HANDLE_T         h_rrctx_rrt     = NULL_HANDLE;
static BOOL             b_rrt_dirty     = FALSE;        /* TRUE: New RRT available or Old RRT unavailable */

static BOOL             b_store_rrt     = FALSE;        /* TRUE: Store the RRT data */

typedef struct _MENU_OP_VCHIP_INIT_T{
    UINT8               ui1_page_type;      /* the page type: region page, dimension page, level page */
    UINT16              ui2_msg_title;      /* the menu_mlm id of the page title */
    UINT32              ui4_subpage_id;    /* the page id of the subpage. */
    UINT16              ui2_max_elm_num;    /* the max element number of this specific page */
    /* Now, the following three flags are always set as FALSE. Reserved. */
    BOOL                b_scroll;           /* TRUE, then turns off the listbox WGL_STL_LB_NO_SCROLL style */
    BOOL                b_back_on_left;     /* Back to previous page by BTN_CURSOR_LEFT */
} MENU_OP_VCHIP_INIT_T;

typedef struct _MENU_OP_VCHIP_PAGE_T
{
    UINT32                  ui4_page_id;
    MENU_OP_VCHIP_INIT_T    t_op_vchip_init;
    UINT8                   ui1_valid_elm_num;
    UINT8                   ui1_prev_sel_idx;   /* Valid in region/dimension page only */
    UINT8                   ui1_crnt_sel_idx;   /* Valid in region/dimension page only */
    HANDLE_T                h_lb_lst;
    BOOL                    b_is_refreshing;
    BOOL                    b_is_showing;
    BOOL                    b_is_created;
} MENU_OP_VCHIP_PAGE_T;

static MENU_OP_VCHIP_PAGE_T     t_op_vchip_page[MENU_OP_VCHIP_TOTAL_PAGE_NUM];

static BOOL                     pb_lvl_elem_block [MENU_OP_VCHIP_MAX_LVL_NUM] = { FALSE };
static BOOL                     b_g_is_active        = FALSE;
static BOOL                     b_is_refresh_subpage = FALSE;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    INT32                 i4_ret;
    UINT32                ui4_page_id = 0;
    MENU_OP_VCHIP_PAGE_T* pt_op_vchip_page = NULL;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
        MENU_CHK_FAIL(i4_ret);
        i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_op_vchip_page);
        MENU_CHK_FAIL(i4_ret);

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return MENUR_OK;
        #endif
        case BTN_SELECT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_CURSOR_DOWN:
            if (pt_op_vchip_page->ui1_valid_elm_num >= 1)
            {
                /* set highlight of quick_operation & focus on it */
                c_wgl_do_cmd(pt_op_vchip_page->h_lb_lst,
                             WGL_CMD_LB_HLT_ELEM,
                             WGL_PACK(0),
                             NULL);
                c_wgl_set_focus(pt_op_vchip_page->h_lb_lst, WGL_SYNC_AUTO_REPAINT);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_PARENT_OP_VCHIP));
            }
            break;

        case BTN_CURSOR_UP:
            menu_set_focus_on_homebar(TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _homebar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    INT32                 i4_ret;
    UINT32                ui4_page_id = 0;
    MENU_OP_VCHIP_PAGE_T* pt_op_vchip_page = NULL;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
        MENU_CHK_FAIL(i4_ret);
        i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_op_vchip_page);
        MENU_CHK_FAIL(i4_ret);

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return MENUR_OK;
        #endif
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_SELECT:
            menu_nav_go_home_menu();
            return WGLR_OK;

        case BTN_CURSOR_UP:
            if (pt_op_vchip_page->ui1_valid_elm_num >= 1)
            {
                /* set highlight of quick_operation & focus on it */
                c_wgl_do_cmd(pt_op_vchip_page->h_lb_lst,
                             WGL_CMD_LB_HLT_ELEM,
                             WGL_PACK(0),
                             NULL);
                c_wgl_set_focus(pt_op_vchip_page->h_lb_lst, WGL_SYNC_AUTO_REPAINT);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_PARENT_OP_VCHIP));
            }
            break;

        case BTN_CURSOR_DOWN:
            menu_set_focus_on_backbar(TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _rrctx_nfy_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _op_vchip_nfy_fct(HANDLE_T          h_nfy,
                              VOID*             pv_nfy_tag,
                              UINT32            ui4_reason)
{
    if (h_rrctx_rrt != NULL_HANDLE)
    {   /* The rrt handle is already opened. */
        if (h_nfy != h_rrctx_rrt)
        {
            DBG_ERROR(("<MENU> Invalid notification handle\n\r"));
        }

        DBG_INFO(("<MENU> RRCTX Notification: Reason = [%d], Handle = [%d]\n\r", ui4_reason, h_nfy));

        switch (ui4_reason)
        {
        case RRCTX_REASON_UNKNOWN:
            break;
        case RRCTX_REASON_RATE_ENABLE:
            break;
        case RRCTX_REASON_RATE_DISABLE:
            break;
        case RRCTX_REASON_RATE_UPDATED:
            b_rrt_dirty = TRUE;
            break;
        case RRCTX_REASON_RATE_AVAIL:
            b_rrt_dirty = TRUE;
            break;
        case RRCTX_REASON_RATE_UNAVAIL:
            DBG_ERROR(("<MENU> This case should not happen. [RRCTX_REASON_RATE_UNAVAIL]\n\r"));
            b_rrt_dirty = TRUE;
            break;
        case RRCTX_REASON_HANDLE_CLOSED:
            break;
        default:
            break;
        }
    }
    else
    {
        DBG_ERROR(("<MENU> This situation should not happen. NULL RRT handle when receving the notification.\n\r"));
    }

}

/*----------------------------------------------------------------------------
 * Name: _op_vchip_trigger_vchip_nfy
 *
 * Description: only get the vchip settings and then set the vchip settings.
 *              trigger the acfg nfy only.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _op_vchip_trigger_vchip_nfy (VOID)
{
    INT32   i4_ret;
    UINT8   ui1_mpaa;
    UINT8   ui1_tv_age;
    UINT64  ui8_tv_cnt_map;
    BOOL    b_mpaa_bu;
    BOOL    b_tv_bu;

    /* dummy acfg setup -> trigger the notify only */
    i4_ret = a_cfg_get_vchip_us(&ui1_mpaa,
                                &ui1_tv_age,
                                &ui8_tv_cnt_map,
                                &b_mpaa_bu,
                                &b_tv_bu);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = a_cfg_set_vchip_us(ui1_mpaa,
                                ui1_tv_age,
                                ui8_tv_cnt_map,
                                b_mpaa_bu,
                                b_tv_bu);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _op_vchip_check_rrt_handle
 *
 * Description: open the rrt handle of the RRCTX for get/set rating infomation
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _op_vchip_check_rrt_handle(VOID)
{
    INT32       i4_ret;
    UINT16      ui2_svl_id;
    CHAR*       ps_tuner_name;

    if (h_rrctx_rrt != NULL_HANDLE)
    {
        return MENUR_OK;
    }

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_svl_id, &ps_tuner_name);
    if (i4_ret != APP_CFGR_OK)
    {
        return MENUR_FAIL;
    }

    i4_ret = c_rrctx_open_rating(RRCTX_RATING_TYPE_RRT,
                                 (VOID*) ps_tuner_name,
                                 _op_vchip_nfy_fct,
                                 NULL,
                                 &h_rrctx_rrt);

    if (i4_ret != RRCTXR_OK)
    {
        if (i4_ret == RRCTXR_NOT_INIT)
        {
            DBG_ERROR(("<MENU> RRCTX component is not inited.\n\r"));
        }
        else if (i4_ret == RRCTXR_ENG_NOT_FOUND)
        {
            DBG_ERROR(("<MENU> RRCTX RRT engine was not found.\n\r"));
        }
        else
        {
            DBG_ERROR(("<MENU> Failed to open the rrt handle. [i4_ret = %d]\n\r", i4_ret));
        }
        return MENUR_FAIL;
    }

    DBG_INFO(("<MENU> Succeeded to open the rrt handle [handle = %d].\n\r", h_rrctx_rrt));
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _op_vchip_get_rrt_info
 *
 * Description: get the rrt data from RRCTX
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _op_vchip_get_rating_info(
    VOID*                   pv_key_param,
    VOID*                   pv_data)
{
    INT32                   i4_ret;
    SIZE_T                  z_info_len = 0;

    if (pv_key_param == NULL || pv_data == NULL)
    {
        return MENUR_INV_ARG;
    }

    if ( h_rrctx_rrt == NULL_HANDLE)
    {
        if (MENUR_OK != _op_vchip_check_rrt_handle())
        {
            return MENUR_FAIL;
        }
    }

    i4_ret = c_rrctx_get_rating_info_len(
                    h_rrctx_rrt,
                    RRCTX_KEY_TYPE_ENG_SPECIFIC,
                    pv_key_param,
                    &z_info_len);

    if (i4_ret == RRCTXR_OK)
    {
        i4_ret = c_rrctx_get_rating_info(
                        h_rrctx_rrt,
                        RRCTX_KEY_TYPE_ENG_SPECIFIC,
                        pv_key_param,
                        &z_info_len,
                        pv_data);

        if (i4_ret != RRCTXR_OK)
        {
            DBG_ERROR(("<MENU> Failed to get the data of open-vchip information [i4_ret = %d]\n\r", i4_ret));
            return MENUR_FAIL;
        }
    }
    else
    {
        DBG_ERROR(("<MENU> Failed to get the length of open-vchip information [i4_ret = %d]\n\r", i4_ret));
        return MENUR_FAIL;
    }

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _op_vchip_reset_page_data
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
static VOID _op_vchip_reset_page_data(MENU_OP_VCHIP_PAGE_T* pt_op_vchip_page)
{
    c_memset(pt_op_vchip_page, 0, sizeof(MENU_OP_VCHIP_PAGE_T));
    pt_op_vchip_page->ui4_page_id       = 0;
    pt_op_vchip_page->ui1_valid_elm_num = 0;
    pt_op_vchip_page->ui1_prev_sel_idx  = MENU_OP_VCHIP_NO_SEL_IDX;
    pt_op_vchip_page->ui1_crnt_sel_idx  = MENU_OP_VCHIP_NO_SEL_IDX;
    pt_op_vchip_page->h_lb_lst          = NULL_HANDLE;
    pt_op_vchip_page->b_is_refreshing   = FALSE;
    pt_op_vchip_page->b_is_showing      = FALSE;
    pt_op_vchip_page->b_is_created      = FALSE;
}


/*----------------------------------------------------------------------------
 * Name: _op_vchip_free_resource
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
static VOID _op_vchip_free_resource(MENU_OP_VCHIP_PAGE_T* pt_op_vchip_page)
{
    if(pt_op_vchip_page != NULL)
    {
        if(pt_op_vchip_page->b_is_created)
        {
            if (pt_op_vchip_page->h_lb_lst != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_op_vchip_page->h_lb_lst);
            }
        }
        _op_vchip_reset_page_data(pt_op_vchip_page);
    }
}


/*----------------------------------------------------------------------------
 * Name: _op_vchip_set_attach_data
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
static INT32 _op_vchip_set_attach_data(HANDLE_T               h_lb_lst,
                                       MENU_OP_VCHIP_PAGE_T*  pt_op_vchip_page)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_lst,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_op_vchip_page),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _op_vchip_get_attach_data
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
static INT32 _op_vchip_get_attach_data(HANDLE_T                h_lb_lst,
                                       MENU_OP_VCHIP_PAGE_T**  ppt_op_vchip_page)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_lst,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_op_vchip_page),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _op_vchip_get_page_elm_num
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
static INT32 _op_vchip_get_page_elm_num(
    MENU_OP_VCHIP_PAGE_T*       pt_op_vchip_page,
    UINT8*                      pui1_max_num)
{
    INT32                  i4_ret;
    RRCTX_RRT_KEY_PARAM_T  t_rrt_key_param;
    UINT8                  aui1_sel_idx[2] = {0};

    aui1_sel_idx[0] = t_op_vchip_page[MENU_OP_VCHIP_RGN_PAGE].ui1_crnt_sel_idx;
    aui1_sel_idx[1] = t_op_vchip_page[MENU_OP_VCHIP_DIM_PAGE].ui1_crnt_sel_idx;

    if (MENU_OP_VCHIP_RGN_PAGE ==
                pt_op_vchip_page->t_op_vchip_init.ui1_page_type)
    {   /* Region Page */
        t_rrt_key_param.e_rrt_key_type   = RRCTX_RRT_KEY_TYPE_RGN_NUM;
        t_rrt_key_param.pv_rrt_key_param = NULL;
    }
    else if (MENU_OP_VCHIP_DIM_PAGE ==
                pt_op_vchip_page->t_op_vchip_init.ui1_page_type)
    {   /* Dimension Page */
        t_rrt_key_param.e_rrt_key_type   = RRCTX_RRT_KEY_TYPE_DIM_NUM;
        t_rrt_key_param.pv_rrt_key_param = (VOID*) aui1_sel_idx;
    }
    else
    {   /* Level Page */
        t_rrt_key_param.e_rrt_key_type   = RRCTX_RRT_KEY_TYPE_LVL_NUM;
        t_rrt_key_param.pv_rrt_key_param = (VOID*) aui1_sel_idx;
    }

    i4_ret = _op_vchip_get_rating_info( (VOID*) &t_rrt_key_param,
                                        (VOID*) pui1_max_num );

    if (i4_ret == MENUR_OK &&
        MENU_OP_VCHIP_LVL_PAGE == pt_op_vchip_page->t_op_vchip_init.ui1_page_type)
    {   /* offset. the lvl[0] is NULL level. */
        (*pui1_max_num) = (*pui1_max_num) - MENU_LVL_ELM_IDX_OFFSET;
    }

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: _op_vchip_get_page_elm_text
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
static INT32 _op_vchip_get_page_elm_text(
    MENU_OP_VCHIP_PAGE_T*       pt_op_vchip_page,
    UINT8                       ui1_page_idx,
    UTF16_T*                    w2s_dst)
{
    RRCTX_RRT_KEY_PARAM_T  t_rrt_key_param;
    UINT8                  aui1_sel_idx[3] = {0};

    if (MENU_OP_VCHIP_RGN_PAGE ==
                pt_op_vchip_page->t_op_vchip_init.ui1_page_type)
    {   /* Region Page */
        t_rrt_key_param.e_rrt_key_type = RRCTX_RRT_KEY_TYPE_RGN_TEXT;
        aui1_sel_idx[0]                = ui1_page_idx;
    }
    else if (MENU_OP_VCHIP_DIM_PAGE ==
                pt_op_vchip_page->t_op_vchip_init.ui1_page_type)
    {   /* Dimension Page */
        t_rrt_key_param.e_rrt_key_type = RRCTX_RRT_KEY_TYPE_DIM_TEXT;
        aui1_sel_idx[0]                = t_op_vchip_page[MENU_OP_VCHIP_RGN_PAGE].ui1_crnt_sel_idx;
        aui1_sel_idx[1]                = ui1_page_idx;
    }
    else
    {   /* Level Page */
        t_rrt_key_param.e_rrt_key_type = RRCTX_RRT_KEY_TYPE_LVL_ABBR;
        aui1_sel_idx[0]                = t_op_vchip_page[MENU_OP_VCHIP_RGN_PAGE].ui1_crnt_sel_idx;
        aui1_sel_idx[1]                = t_op_vchip_page[MENU_OP_VCHIP_DIM_PAGE].ui1_crnt_sel_idx;
        /* offset. the lvl[0] is NULL level. */
        aui1_sel_idx[2]                = ui1_page_idx + MENU_LVL_ELM_IDX_OFFSET;
    }

    t_rrt_key_param.pv_rrt_key_param = (VOID*) aui1_sel_idx;

    return _op_vchip_get_rating_info( (VOID*) &t_rrt_key_param,
                                      (VOID*) w2s_dst );
}


/*----------------------------------------------------------------------------
 * Name: _op_vchip_get_page_data
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
static INT32 _op_vchip_get_page_data(
    RRCTX_RRT_KEY_TYPE_T    e_rrt_key_type,
    VOID*                   pv_data)
{
    RRCTX_RRT_KEY_PARAM_T  t_rrt_key_param;
    UINT8                  aui1_sel_idx[3];

    if (e_rrt_key_type != RRCTX_RRT_KEY_TYPE_RGN_ID   &&
        e_rrt_key_type != RRCTX_RRT_KEY_TYPE_DIM_GRAD)
    {
        return MENUR_INV_ARG;
    }

    aui1_sel_idx[0] = t_op_vchip_page[MENU_OP_VCHIP_RGN_PAGE].ui1_crnt_sel_idx;
    aui1_sel_idx[1] = t_op_vchip_page[MENU_OP_VCHIP_DIM_PAGE].ui1_crnt_sel_idx;

    t_rrt_key_param.e_rrt_key_type   = e_rrt_key_type;
    t_rrt_key_param.pv_rrt_key_param = (VOID*) aui1_sel_idx;

    return _op_vchip_get_rating_info( (VOID*) &t_rrt_key_param,
                                      (VOID*) pv_data );
}


/*----------------------------------------------------------------------------
 * Name: _op_vchip_rating_settings
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
static INT32 _op_vchip_rating_settings(
    BOOL*               pb_lvl_block,
    BOOL                b_set_get)
{
    RRCTX_RRT_RATE_SETTING_T t_rrt_setting;

    t_rrt_setting.b_set_get     = b_set_get;                      /* TRUE: Set, FALSE: Get */
    t_rrt_setting.ui1_rgn_idx   = t_op_vchip_page[MENU_OP_VCHIP_RGN_PAGE].ui1_crnt_sel_idx;
    t_rrt_setting.ui1_dim_idx   = t_op_vchip_page[MENU_OP_VCHIP_DIM_PAGE].ui1_crnt_sel_idx;
    t_rrt_setting.pb_lvl_block  = pb_lvl_block;
    t_rrt_setting.pui1_bu       = NULL;

    /* Set the dirty flag for storing the RRT data */
    if (b_set_get)
    {
        b_store_rrt = TRUE;
    }

    return c_rrctx_rating_settings( h_rrctx_rrt,
                                    (VOID*) &t_rrt_setting);
}


/*----------------------------------------------------------------------------
 * Name: _op_vchip_is_refresh_page
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
static BOOL _op_vchip_is_refresh_page(UINT8 ui1_page_type)
{
    if (b_rrt_dirty)
    {
        /* When b_rrt_dirty is set as TRUE, it must return to the region page at least once */
        if (ui1_page_type == MENU_OP_VCHIP_RGN_PAGE)
        {
            /* reset the selected index -> result in that the page would be refreshed. */
            t_op_vchip_page[MENU_OP_VCHIP_RGN_PAGE].ui1_prev_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;
            t_op_vchip_page[MENU_OP_VCHIP_RGN_PAGE].ui1_crnt_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;

            t_op_vchip_page[MENU_OP_VCHIP_DIM_PAGE].ui1_prev_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;
            t_op_vchip_page[MENU_OP_VCHIP_DIM_PAGE].ui1_crnt_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;

            t_op_vchip_page[MENU_OP_VCHIP_LVL_PAGE].ui1_prev_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;
            t_op_vchip_page[MENU_OP_VCHIP_LVL_PAGE].ui1_crnt_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;

            b_rrt_dirty = FALSE;
        }

        b_is_refresh_subpage = FALSE;
        return TRUE;
    }


    if (b_is_refresh_subpage)
    {
        b_is_refresh_subpage = FALSE;
        return TRUE;
    }

    /* There is no element data in the page. */
    if ( (MENU_OP_VCHIP_NO_SEL_IDX == t_op_vchip_page[ui1_page_type].ui1_prev_sel_idx) &&
         (MENU_OP_VCHIP_NO_SEL_IDX == t_op_vchip_page[ui1_page_type].ui1_crnt_sel_idx) )
    {
        return TRUE;
    }

    return FALSE;
}

/*----------------------------------------------------------------------------
 * Name: _op_vchip_page_refresh
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
static INT32 _op_vchip_page_refresh(MENU_OP_VCHIP_PAGE_T*  pt_op_vchip_page)
{
    INT32                       i4_ret;
    UINT8                       ui1_idx;
    UINT8                       ui1_max_num;
    UINT8                       ui1_page_type;
    UTF16_T                     w2s_str[64];
    WGL_LB_ITEM_T               at_items[2];
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit;
    HANDLE_T                    h_lb_lst;

    if (pt_op_vchip_page == NULL)
    {
        DBG_ERROR(("<MENU> Invalid data of the open-vchip page.\n"));
        return MENUR_INV_ARG;
    }
    if (pt_op_vchip_page->t_op_vchip_init.ui1_page_type >= MENU_OP_VCHIP_TOTAL_PAGE_NUM)
    {
        return MENUR_FAIL;
    }

    h_lb_lst      = pt_op_vchip_page->h_lb_lst;
    ui1_page_type = pt_op_vchip_page->t_op_vchip_init.ui1_page_type;

    if ( _op_vchip_is_refresh_page(ui1_page_type) )
    {   /* Whether or not refresh this specific page */

        /* Set the refreshing flag */
        pt_op_vchip_page->b_is_refreshing = TRUE;

        /* clear the region list */
        i4_ret = c_wgl_do_cmd(h_lb_lst,
                              WGL_CMD_LB_DEL_ALL,
                              NULL, NULL);
        MENU_CHK_FAIL(i4_ret);

        /* Determine the max number according to this page definition and RRCTX DB. */
        i4_ret = _op_vchip_get_page_elm_num(pt_op_vchip_page,
                                            &ui1_max_num);
        MENU_CHK_FAIL(i4_ret);

        if (ui1_max_num > (UINT8)pt_op_vchip_page->t_op_vchip_init.ui2_max_elm_num)
        {   /* Choose the smaller number */
            ui1_max_num = (UINT8)pt_op_vchip_page->t_op_vchip_init.ui2_max_elm_num;
        }

        pt_op_vchip_page->ui1_valid_elm_num = 0;

        for (ui1_idx = 0; ui1_idx < ui1_max_num ; ui1_idx++)
        {
            /* Append the data */
            i4_ret = _op_vchip_get_page_elm_text(pt_op_vchip_page,
                                                 ui1_idx,
                                                 w2s_str);
            if (i4_ret != MENUR_OK)
            {
                break;
            }

            if (w2s_str [0] == '\0')
            {   /* NULL String */
                c_uc_w2s_strcpy (w2s_str, _TEXT("(No Text.)"));
            }

            at_items[0].e_col_type     = LB_COL_TYPE_TEXT;
            at_items[0].data.pw2s_text = w2s_str;

            if (MENU_OP_VCHIP_LVL_PAGE != ui1_page_type)
            {   /* Region Page and Dimension Page */
                c_memset(&t_img_suit, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
                t_img_suit.h_normal                     = NULL_HANDLE;
                t_img_suit.h_disable                    = NULL_HANDLE;
                t_img_suit.h_highlight                  = NULL_HANDLE;
                t_img_suit.h_highlight_unfocus          = NULL_HANDLE;
                t_img_suit.h_pushed                     = NULL_HANDLE;
                t_img_suit.h_selected                   = NULL_HANDLE;
                t_img_suit.h_selected_disable           = NULL_HANDLE;
                t_img_suit.h_selected_highlight         = NULL_HANDLE;
                t_img_suit.h_selected_highlight_unfocus = NULL_HANDLE;
                t_img_suit.h_selected_pushed            = NULL_HANDLE;

                at_items[1].e_col_type       = LB_COL_TYPE_IMG_SUIT;
                at_items[1].data.pt_img_suit = &t_img_suit;
            }
            else
            {   /* Level Page */
                c_memset(&t_img_suit, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));

                t_img_suit.h_normal                     = h_g_menu_img_unlock;
                t_img_suit.h_disable                    = NULL_HANDLE;
                t_img_suit.h_highlight                  = h_g_menu_img_unlock_hlt;
                t_img_suit.h_highlight_unfocus          = h_g_menu_img_unlock;
                t_img_suit.h_pushed                     = NULL_HANDLE;
                t_img_suit.h_selected                   = h_g_menu_img_lock;
                t_img_suit.h_selected_disable           = NULL_HANDLE;
                t_img_suit.h_selected_highlight         = h_g_menu_img_lock_hlt;
                t_img_suit.h_selected_highlight_unfocus = h_g_menu_img_lock;
                t_img_suit.h_selected_pushed            = NULL_HANDLE;

                at_items[1].e_col_type       = LB_COL_TYPE_IMG_SUIT;
                at_items[1].data.pt_img_suit = &t_img_suit;
            }

            i4_ret = c_wgl_do_cmd(h_lb_lst,
                                  WGL_CMD_LB_APPEND_ELEM,
                                  WGL_PACK(at_items),
                                  NULL);
            if (i4_ret != MENUR_OK)
            {
                break;
            }

            pt_op_vchip_page->ui1_valid_elm_num++;
        }

        /* set the selected index as the index of the first element */
        pt_op_vchip_page->ui1_prev_sel_idx = 0;
        pt_op_vchip_page->ui1_crnt_sel_idx = 0;

        if (ui1_page_type == MENU_OP_VCHIP_LVL_PAGE)
        {   /* Level Page: Select the related block level */

            /* update the RRCTX Settings */
            i4_ret = _op_vchip_rating_settings(pb_lvl_elem_block, FALSE);  /* TRUE: Set, FALSE: Get */
            MENU_CHK_FAIL(i4_ret);

            for (ui1_idx = 0; ui1_idx < pt_op_vchip_page->ui1_valid_elm_num; ui1_idx++)
            {
                /* offset. the lvl[0] is NULL level. */
                if (ui1_idx + MENU_LVL_ELM_IDX_OFFSET < MENU_OP_VCHIP_MAX_LVL_NUM)
                {
                    if ( pb_lvl_elem_block [ui1_idx + MENU_LVL_ELM_IDX_OFFSET] )
                    {
                        i4_ret = c_wgl_do_cmd(h_lb_lst,
                                              WGL_CMD_LB_SEL_ELEM,
                                              WGL_PACK(ui1_idx),
                                              NULL);
                        MENU_CHK_FAIL(i4_ret);
                    }
                }
            }
        }

        /* Set the refreshing flag */
        pt_op_vchip_page->b_is_refreshing = FALSE;

        if(pt_op_vchip_page->ui1_valid_elm_num > 0)
        {
            i4_ret = c_wgl_do_cmd( h_lb_lst,
                                   WGL_CMD_LB_HLT_ELEM,
                                   WGL_PACK((UINT16) 0), /* highlight the first element */
                                   NULL);
            MENU_CHK_FAIL(i4_ret);
        }
    }

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _cnt_frm_proc_fct
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
static INT32 _cnt_frm_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _op_vchip_lst_proc_fct
 *
 * Description: process the norification of the LB widget
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _op_vchip_lst_proc_fct(HANDLE_T            h_widget,
                             UINT32              ui4_msg,
                             VOID*               pv_param1,
                             VOID*               pv_param2)
{
    INT32   i4_ret;
    UINT16  ui2_sel_idx;
    UINT16  ui2_idx, ui2_start_idx, ui2_end_idx;
    UINT32  ui4_cmd;
    BOOL    b_scale  = FALSE;
    BOOL    b_is_sel = FALSE;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
        {
            MENU_OP_VCHIP_PAGE_T*  pt_op_vchip_page = NULL;
            UINT32 ui4_keycode = (UINT32)pv_param1;

            /* get the open-vchip page data */
            if( MENUR_OK != _op_vchip_get_attach_data(h_widget, &pt_op_vchip_page) )
            {
                DBG_ERROR(("<MENU> Failed to get the attach data of the open-vchip page.\n"));
                return WGLR_OK;
            }

            switch (ui4_keycode)
            {
            case BTN_CURSOR_UP:
                i4_ret = c_wgl_do_cmd (pt_op_vchip_page->h_lb_lst,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK (& ui2_sel_idx),
                                      NULL);
                if (i4_ret == WGLR_OK)
                {
                    if (ui2_sel_idx == 0)
                    {
                        menu_set_focus_on_backbar(TRUE);
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                        return WGLR_OK;
                    }
                }
                break;

            case BTN_CURSOR_LEFT:
            case BTN_PREV_PRG:
            case BTN_RETURN:
                if(pt_op_vchip_page != NULL &&
                   pt_op_vchip_page->t_op_vchip_init.b_back_on_left)
                {   /* return to previous page */
                    menu_nav_back();
                    return WGLR_OK;
                }
                break;
            case BTN_CURSOR_RIGHT:
                /* display the 'empty' region page for users only. invalid subpaeg. */
                if (NULL != pt_op_vchip_page &&
                    MENU_OP_VCHIP_RGN_PAGE == pt_op_vchip_page->t_op_vchip_init.ui1_page_type &&
                    FALSE == b_g_is_active)
                {
                    return WGLR_OK;
                }

                if(pt_op_vchip_page != NULL &&
                   pt_op_vchip_page->t_op_vchip_init.b_back_on_left)
                {   /* go to the next page */
                    if (MENU_OP_VCHIP_LVL_PAGE != pt_op_vchip_page->t_op_vchip_init.ui1_page_type)
                    {
                        i4_ret = c_wgl_do_cmd (pt_op_vchip_page->h_lb_lst,
                                              WGL_CMD_LB_GET_HLT_INDEX,
                                              WGL_PACK (& ui2_sel_idx),
                                              NULL);
                        if (i4_ret == WGLR_OK)
                        {
                            /* record the selected element index */
                            pt_op_vchip_page->ui1_prev_sel_idx = pt_op_vchip_page->ui1_crnt_sel_idx;
                            pt_op_vchip_page->ui1_crnt_sel_idx = (UINT8) ui2_sel_idx;

                            if (MENU_OP_VCHIP_RGN_PAGE == pt_op_vchip_page->t_op_vchip_init.ui1_page_type)
                            {   /* Region Change */
                                t_op_vchip_page[MENU_OP_VCHIP_DIM_PAGE].ui1_prev_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;
                                t_op_vchip_page[MENU_OP_VCHIP_DIM_PAGE].ui1_crnt_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;

                                t_op_vchip_page[MENU_OP_VCHIP_LVL_PAGE].ui1_prev_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;
                                t_op_vchip_page[MENU_OP_VCHIP_LVL_PAGE].ui1_crnt_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;
                            }

                            if (MENU_OP_VCHIP_NO_SUBPAGE !=
                                        pt_op_vchip_page->t_op_vchip_init.ui4_subpage_id)
                            {
                                DBG_INFO(("<MENU> Enter the subpage page. [idx = %d] [crnt pid = %d] [next pid = %d]\r\n",
                                           ui2_sel_idx, pt_op_vchip_page->ui4_page_id,
                                           pt_op_vchip_page->t_op_vchip_init.ui4_subpage_id));

                                if (pt_op_vchip_page->ui1_prev_sel_idx != pt_op_vchip_page->ui1_crnt_sel_idx)
                                {   /* refresh the subpage */
                                    b_is_refresh_subpage = TRUE;
                                }
                                menu_nav_go( pt_op_vchip_page->t_op_vchip_init.ui4_subpage_id , NULL );
                            }
                        }
                    }
                    return WGLR_OK;
                }
                break;

            case BTN_SELECT:
                /* display the 'empty' region page for users only. invalid subpaeg. */
                if (NULL != pt_op_vchip_page &&
                    MENU_OP_VCHIP_RGN_PAGE == pt_op_vchip_page->t_op_vchip_init.ui1_page_type &&
                    FALSE == b_g_is_active)
                {
                    return WGLR_OK;
                }

                if(pt_op_vchip_page != NULL)
                {
                    i4_ret = c_wgl_do_cmd (pt_op_vchip_page->h_lb_lst,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK (& ui2_sel_idx), NULL);
                    if (i4_ret == WGLR_OK)
                    {
                        /* record the selected element index */
                        pt_op_vchip_page->ui1_prev_sel_idx = pt_op_vchip_page->ui1_crnt_sel_idx;
                        pt_op_vchip_page->ui1_crnt_sel_idx = (UINT8) ui2_sel_idx;

                        if (MENU_OP_VCHIP_LVL_PAGE == pt_op_vchip_page->t_op_vchip_init.ui1_page_type)
                        {   /* Level Page */
                            if ( menu_get_cond() != MENU_COND_NOT_INIT &&
                                 !pt_op_vchip_page->b_is_refreshing )
                            {
                                DBG_INFO(("<MENU> Select the element of the level page. [sel_idx = %d] [crnt pid = %d]\r\n",
                                           ui2_sel_idx, pt_op_vchip_page->ui4_page_id));

                                i4_ret = c_wgl_do_cmd( pt_op_vchip_page->h_lb_lst,
                                                       WGL_CMD_LB_IS_INDEX_SEL,
                                                       WGL_PACK(ui2_sel_idx),
                                                       WGL_PACK(&b_is_sel) );
                                MENU_CHK_FAIL(i4_ret);

                                /* Update the RRT settings of the RRCTX */
                                i4_ret = _op_vchip_get_page_data(RRCTX_RRT_KEY_TYPE_DIM_GRAD, &b_scale);
                                MENU_CHK_FAIL(i4_ret);

                                if (b_scale)
                                {   /* unlock : lock */
                                    ui2_start_idx  = (b_is_sel) ? 0 : ui2_sel_idx;
                                    ui2_end_idx    = (b_is_sel) ? ui2_sel_idx : (UINT16)(pt_op_vchip_page->ui1_valid_elm_num - 1);
                                    ui4_cmd        = (b_is_sel) ? WGL_CMD_LB_DESEL_ELEM : WGL_CMD_LB_SEL_ELEM;

                                    for (ui2_idx = ui2_start_idx; ui2_idx <= ui2_end_idx ; ui2_idx++)
                                    {
                                        if ((ui2_idx + MENU_LVL_ELM_IDX_OFFSET) >= MENU_OP_VCHIP_MAX_LVL_NUM)
                                        {
                                            /* buffer overflow */
                                            DBG_ERROR(("<MENU> buffer overflow in access to pb_lvl_elem_block[].\n"));
                                            return MENUR_FAIL;
                                        }
                                        pb_lvl_elem_block [ui2_idx + MENU_LVL_ELM_IDX_OFFSET] = (!b_is_sel);

                                        i4_ret = c_wgl_do_cmd(pt_op_vchip_page->h_lb_lst,
                                                              ui4_cmd,
                                                              WGL_PACK(ui2_idx),
                                                              NULL);
                                        MENU_CHK_FAIL(i4_ret);
                                    }
                                    c_wgl_repaint(pt_op_vchip_page->h_lb_lst, NULL, TRUE);
                                }
                                else
                                {   /* unlock : lock */
                                    ui4_cmd = (b_is_sel) ? WGL_CMD_LB_DESEL_ELEM : WGL_CMD_LB_SEL_ELEM;

                                    if ((ui2_sel_idx + MENU_LVL_ELM_IDX_OFFSET) >= MENU_OP_VCHIP_MAX_LVL_NUM)
                                    {
                                        /* buffer overflow */
                                        DBG_ERROR(("<MENU> buffer overflow in access to pb_lvl_elem_block[].\n"));
                                        return MENUR_FAIL;
                                    }
                                    pb_lvl_elem_block [ui2_sel_idx + MENU_LVL_ELM_IDX_OFFSET] = (!b_is_sel);

                                    i4_ret = c_wgl_do_cmd(pt_op_vchip_page->h_lb_lst,
                                                          ui4_cmd,
                                                          WGL_PACK(ui2_sel_idx),
                                                          NULL);
                                    MENU_CHK_FAIL(i4_ret);

                                    c_wgl_repaint(pt_op_vchip_page->h_lb_lst, NULL, TRUE);
                                }

                                i4_ret = _op_vchip_rating_settings(pb_lvl_elem_block, TRUE);   /* TRUE: Set, FALSE: Get */
                                MENU_CHK_FAIL(i4_ret);
                                i4_ret = _op_vchip_trigger_vchip_nfy();
                                MENU_CHK_FAIL(i4_ret);
                            }
                        }
                        else
                        {   /* Region Page and Dimension Page */
                            if (MENU_OP_VCHIP_RGN_PAGE == pt_op_vchip_page->t_op_vchip_init.ui1_page_type)
                            {   /* Region Change */
                                t_op_vchip_page[MENU_OP_VCHIP_DIM_PAGE].ui1_prev_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;
                                t_op_vchip_page[MENU_OP_VCHIP_DIM_PAGE].ui1_crnt_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;

                                t_op_vchip_page[MENU_OP_VCHIP_LVL_PAGE].ui1_prev_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;
                                t_op_vchip_page[MENU_OP_VCHIP_LVL_PAGE].ui1_crnt_sel_idx = MENU_OP_VCHIP_NO_SEL_IDX;
                            }

                            if (MENU_OP_VCHIP_NO_SUBPAGE !=
                                        pt_op_vchip_page->t_op_vchip_init.ui4_subpage_id)
                            {
                                DBG_INFO(("<MENU> Enter the subpage page. [idx = %d] [crnt pid = %d] [next pid = %d]\r\n",
                                           ui2_sel_idx, pt_op_vchip_page->ui4_page_id,
                                           pt_op_vchip_page->t_op_vchip_init.ui4_subpage_id));

                                if (pt_op_vchip_page->ui1_prev_sel_idx != pt_op_vchip_page->ui1_crnt_sel_idx)
                                {   /* refresh the subpage */
                                    b_is_refresh_subpage = TRUE;
                                }
                                menu_nav_go( pt_op_vchip_page->t_op_vchip_init.ui4_subpage_id , NULL );
                            }
                        }
                    } /* if (i4_ret == WGLR_OK) */
                }
                return WGLR_OK;

            default:
                break;
            }
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _op_vchip_lst_create
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
INT32 _op_vchip_lst_create(HANDLE_T                 h_parent,
                           MENU_OP_VCHIP_PAGE_T*    pt_op_vchip_page)
{
    /* this function should be as similar as the menu_create_submenu_item in menu_util.c */
    INT32                       i4_ret;
    HANDLE_T*                   ph_lb_lst;
    GL_RECT_T                   t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[2];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_clr_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;

    ph_lb_lst = &(pt_op_vchip_page->h_lb_lst);

    /* Create Subpage LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = 32;
    at_cols[0].ui2_width        = (CONTENT_W - 100);
    at_cols[1].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[1].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[1].ui2_width        = 100;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_MULTI_SEL;
    if(!pt_op_vchip_page->t_op_vchip_init.b_scroll)
    {
        t_lb_init.ui4_style     |= WGL_STL_LB_NO_SCROLL;
    }

    t_lb_init.ui2_max_elem_num  = pt_op_vchip_page->t_op_vchip_init.ui2_max_elm_num;
    t_lb_init.ui2_elem_size     = GRID_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect, MENU_OP_VCHIP_X, MENU_OP_VCHIP_Y, MENU_OP_VCHIP_W, MENU_OP_VCHIP_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _op_vchip_lst_proc_fct,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_lb_lst);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("<MENU> Create listbox for region part of open vchip failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_lb_lst,
                          WGL_CMD_LB_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_lb_lst,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left   =  20;
    t_inset.i4_right  =  20;
    t_inset.i4_top    =   0;
    t_inset.i4_bottom =   0;
    i4_ret = c_wgl_do_cmd (*ph_lb_lst,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)0),
                           WGL_PACK(&t_inset));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb_lst,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)1),
                           WGL_PACK(&t_inset));
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_lb_lst,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK((UINT16)0),
                           WGL_PACK(&t_fnt_info));
    MENU_CHK_FAIL(i4_ret);

    /* Set LB colors */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable,    &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable,   &t_g_menu_color_transp);

    i4_ret = c_wgl_do_cmd(*ph_lb_lst,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    MENU_CHK_FAIL(i4_ret);

    MENU_COLOR_COPY(&t_clr_elem.t_normal, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_clr_elem.t_disable, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_clr_elem.t_highlight, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_clr_elem.t_highlight_unfocus, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_clr_elem.t_pushed, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_clr_elem.t_selected, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_clr_elem.t_selected_disable, &t_g_menu_color_transp);

    i4_ret = c_wgl_do_cmd (*ph_lb_lst,
                           WGL_CMD_LB_SET_ELEM_COLOR,
                           WGL_PACK(WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb_lst,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(0, WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb_lst,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(1, WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);


    MENU_COLOR_COPY(&t_clr_elem.t_normal           ,&t_g_menu_color_white);
    MENU_COLOR_COPY(&t_clr_elem.t_disable          ,&t_g_menu_color_white);
    MENU_COLOR_COPY(&t_clr_elem.t_highlight        ,&t_g_menu_color_white);
    MENU_COLOR_COPY(&t_clr_elem.t_highlight_unfocus,&t_g_menu_color_white);
    MENU_COLOR_COPY(&t_clr_elem.t_pushed           ,&t_g_menu_color_white);
    MENU_COLOR_COPY(&t_clr_elem.t_selected         ,&t_g_menu_color_white);
    MENU_COLOR_COPY(&t_clr_elem.t_selected_disable ,&t_g_menu_color_white);

    i4_ret = c_wgl_do_cmd (*ph_lb_lst,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(0, WGL_CLR_TEXT),
                           WGL_PACK(& t_clr_elem));
    MENU_CHK_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (*ph_lb_lst,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(&t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next       = BTN_CURSOR_DOWN;
    t_lb_key_map.ui4_key_prev       = BTN_CURSOR_UP;
    t_lb_key_map.ui4_key_select     = BTN_SELECT;
    t_lb_key_map.ui4_key_page_up    = BTN_RED;
    t_lb_key_map.ui4_key_page_down  = BTN_GREEN;
    i4_ret = c_wgl_do_cmd(*ph_lb_lst,
                          WGL_CMD_LB_SET_KEY_MAP,
                          &t_lb_key_map,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    pt_op_vchip_page->b_is_created = TRUE;

    /* attach data */
    i4_ret = _op_vchip_set_attach_data(*ph_lb_lst, pt_op_vchip_page);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32    i4_ret                        = MENUR_FAIL;
    HANDLE_T h_cnt_frm                     = NULL_HANDLE;
    MENU_OP_VCHIP_PAGE_T* pt_op_vchip_page = NULL;
    MENU_OP_VCHIP_INIT_T* pt_op_vchip_init = (MENU_OP_VCHIP_INIT_T*) pv_create_data;

    if(pt_op_vchip_init == NULL)
    {
        return MENUR_INV_ARG;
    }
    if (pt_op_vchip_init->ui1_page_type >= MENU_OP_VCHIP_TOTAL_PAGE_NUM)
    {
        return MENUR_FAIL;
    }

    /* The data structure of the specific page */
    pt_op_vchip_page = &(t_op_vchip_page[pt_op_vchip_init->ui1_page_type]);

    pt_op_vchip_page->ui4_page_id = ui4_page_id;
    c_memcpy( &(pt_op_vchip_page->t_op_vchip_init),
              pt_op_vchip_init,
              sizeof(MENU_OP_VCHIP_INIT_T) );

    i4_ret = menu_page_set_data(ui4_page_id, pt_op_vchip_page);
    if(i4_ret != MENUR_OK)
    {
        _op_vchip_free_resource(pt_op_vchip_page);
        return i4_ret;
    }

    /* Start to construct the widget of the page UI */
    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    if (i4_ret != MENUR_OK)
    {
        _op_vchip_free_resource(pt_op_vchip_page);
        return i4_ret;
    }

    /* Create the LBs of the VChip pages*/
    i4_ret = _op_vchip_lst_create(h_cnt_frm,
                                  pt_op_vchip_page);
    if (i4_ret != MENUR_OK)
    {
        _op_vchip_free_resource(pt_op_vchip_page);
        return i4_ret;
    }

    /* Widget Process */
    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    if (i4_ret != WGLR_OK)
    {
        _op_vchip_free_resource(pt_op_vchip_page);
        return MENUR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    if (i4_ret != WGLR_OK)
    {
        _op_vchip_free_resource(pt_op_vchip_page);
        return MENUR_FAIL;
    }

    i4_ret = menu_page_set_proc_func(ui4_page_id,
                                     _cnt_frm_proc_fct);
    if (i4_ret != MENUR_OK)
    {
        _op_vchip_free_resource(pt_op_vchip_page);
        return i4_ret;
    }

    _op_vchip_check_rrt_handle();

    return MENUR_OK;
}


static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    MENU_OP_VCHIP_PAGE_T* pt_op_vchip_page = NULL;

    if(MENUR_OK ==
            menu_page_get_data(ui4_page_id, (VOID**)&pt_op_vchip_page))
    {
        _op_vchip_free_resource(pt_op_vchip_page);
    }

    return MENUR_OK;
}


static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32 i4_ret;
    MENU_OP_VCHIP_PAGE_T* pt_op_vchip_page = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_op_vchip_page);
    MENU_CHK_FAIL(i4_ret);

    b_store_rrt = FALSE;
    pt_op_vchip_page->b_is_showing = TRUE;

    if (MENU_OP_VCHIP_RGN_PAGE == pt_op_vchip_page->t_op_vchip_init.ui1_page_type)
    {
        b_g_is_active = menu_atsc_op_vchip_is_active ();
        _op_vchip_check_rrt_handle();
    }
    _op_vchip_page_refresh(pt_op_vchip_page);

    menu_main_set_title(pt_op_vchip_page->t_op_vchip_init.ui2_msg_title);

    return MENUR_OK;
}


static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    INT32 i4_ret;
    MENU_OP_VCHIP_PAGE_T* pt_op_vchip_page = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_op_vchip_page);
    MENU_CHK_FAIL(i4_ret);

    if (b_store_rrt)
    {
        b_store_rrt = FALSE;
        i4_ret = c_rrctx_rating_storage(h_rrctx_rrt, TRUE);
        MENU_CHK_FAIL(i4_ret);
    }

    pt_op_vchip_page->b_is_showing = FALSE;

    return MENUR_OK;
}


static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32 i4_ret;
    MENU_OP_VCHIP_PAGE_T* pt_op_vchip_page = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_op_vchip_page);
    MENU_CHK_FAIL(i4_ret);

    c_wgl_set_focus(pt_op_vchip_page->h_lb_lst, WGL_NO_AUTO_REPAINT);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_PARENT_OP_VCHIP));
    menu_set_backbar_proc(_backbar_proc_fct);

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    return MENUR_OK;
}


static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    menu_set_backbar_proc(NULL);

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    return MENUR_OK;
}


static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        /* do_nothing */
    }
    return MENUR_OK;
}


/*-----------------------------------------------------------------------------
                    global functions declarations
 ----------------------------------------------------------------------------*/
extern INT32 menu_atsc_create_page_op_vchip_rgn(UINT32* pui4_page_id, UINT32 ui4_subpage_id)
{
    MENU_OP_VCHIP_INIT_T t_op_vchip_init;

    c_memset(&t_op_vchip_init, 0, sizeof(MENU_OP_VCHIP_INIT_T));
    t_op_vchip_init.ui1_page_type   = MENU_OP_VCHIP_RGN_PAGE;
    t_op_vchip_init.ui2_msg_title   = MLM_MENU_KEY_OP_VCHIP;
    t_op_vchip_init.ui4_subpage_id  = (ui4_subpage_id != 0) ? ui4_subpage_id : MENU_OP_VCHIP_NO_SUBPAGE;
    t_op_vchip_init.ui2_max_elm_num = MENU_OP_VCHIP_MAX_RGN_NUM;
    t_op_vchip_init.b_scroll        = FALSE;
    t_op_vchip_init.b_back_on_left  = TRUE;

    return menu_pm_page_create( &t_g_menu_atsc_page_op_vchip,
                                (VOID*) &t_op_vchip_init,
                                pui4_page_id );
}


extern INT32 menu_atsc_create_page_op_vchip_dim(UINT32* pui4_page_id, UINT32 ui4_subpage_id)
{
    MENU_OP_VCHIP_INIT_T t_op_vchip_init;

    c_memset(&t_op_vchip_init, 0, sizeof(MENU_OP_VCHIP_INIT_T));
    t_op_vchip_init.ui1_page_type   = MENU_OP_VCHIP_DIM_PAGE;
    t_op_vchip_init.ui2_msg_title   = MLM_MENU_KEY_OP_VCHIP;
    t_op_vchip_init.ui4_subpage_id  = (ui4_subpage_id != 0) ? ui4_subpage_id : MENU_OP_VCHIP_NO_SUBPAGE;
    t_op_vchip_init.ui2_max_elm_num = MENU_OP_VCHIP_MAX_DIM_NUM;
    t_op_vchip_init.b_scroll        = FALSE;
    t_op_vchip_init.b_back_on_left  = TRUE;

    return menu_pm_page_create( &t_g_menu_atsc_page_op_vchip,
                                (VOID*) &t_op_vchip_init,
                                pui4_page_id );
}


extern INT32 menu_atsc_create_page_op_vchip_lvl(UINT32* pui4_page_id, UINT32 ui4_subpage_id)
{
    MENU_OP_VCHIP_INIT_T t_op_vchip_init;

    c_memset(&t_op_vchip_init, 0, sizeof(MENU_OP_VCHIP_INIT_T));
    t_op_vchip_init.ui1_page_type   = MENU_OP_VCHIP_LVL_PAGE;
    t_op_vchip_init.ui2_msg_title   = MLM_MENU_KEY_OP_VCHIP;
    t_op_vchip_init.ui4_subpage_id  = (ui4_subpage_id != 0) ? ui4_subpage_id : MENU_OP_VCHIP_NO_SUBPAGE;
    t_op_vchip_init.ui2_max_elm_num = MENU_OP_VCHIP_MAX_LVL_NUM;
    t_op_vchip_init.b_scroll        = FALSE;
    t_op_vchip_init.b_back_on_left  = TRUE;

    return menu_pm_page_create( &t_g_menu_atsc_page_op_vchip,
                                (VOID*) &t_op_vchip_init,
                                pui4_page_id );
}


extern INT32 menu_atsc_page_op_vchip_init(VOID)
{
    UINT16 ui2_idx;
    for (ui2_idx = 0; ui2_idx < MENU_OP_VCHIP_TOTAL_PAGE_NUM; ui2_idx++)
    {   /* Initiate the settings of region/dimension/level pages of the op vchip */
        _op_vchip_reset_page_data( &(t_op_vchip_page[ui2_idx]) );
    }

    t_g_menu_atsc_page_op_vchip.pf_menu_page_create     = _on_page_create;
    t_g_menu_atsc_page_op_vchip.pf_menu_page_destroy    = _on_page_destroy;
    t_g_menu_atsc_page_op_vchip.pf_menu_page_show       = _on_page_show;
    t_g_menu_atsc_page_op_vchip.pf_menu_page_hide       = _on_page_hide;
    t_g_menu_atsc_page_op_vchip.pf_menu_page_get_focus  = _on_page_get_focus;
    t_g_menu_atsc_page_op_vchip.pf_menu_page_lose_focus = _on_page_lose_focus;
    t_g_menu_atsc_page_op_vchip.pf_menu_page_update     = _on_page_update;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_atsc_op_vchip_is_active
 *
 * Description:     Check whether the op vchip should be enabled or not.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: TRUE    Enable OP-VChip Item
 *          FALSE   Disable OP-VChip Item
 ----------------------------------------------------------------------------*/
extern BOOL  menu_atsc_op_vchip_is_active(VOID)
{
    INT32                  i4_ret;
    UINT8                  ui1_rgn_num;
    RRCTX_RRT_KEY_PARAM_T  t_rrt_key_param;

    if (h_rrctx_rrt != NULL_HANDLE)
    {
        t_rrt_key_param.e_rrt_key_type   = RRCTX_RRT_KEY_TYPE_RGN_NUM;
        t_rrt_key_param.pv_rrt_key_param = NULL;

        i4_ret = _op_vchip_get_rating_info( (VOID*) &t_rrt_key_param,
                                            (VOID*) &ui1_rgn_num );
        if (i4_ret == MENUR_OK && ui1_rgn_num > 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}




#endif /* ATSC_OP_VCHIP_ENABLE */

