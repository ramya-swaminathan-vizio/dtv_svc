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
 * $RCSfile: sleep.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_537X_SUPPORT
#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_wgl.h"

#include "app_util/a_cfg.h"
#include "nav/a_navigator.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "sleep.h"
#include "res/menu2/menu_mlm.h"
#include "app_util/a_sleep_timer.h"
#include "res/nav/sleep/sleep_view_rc.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_SLEEP_T t_g_nav_sleep;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Refresh the list.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_sleep_refresh_list(VOID)
{
    NAV_SLEEP_T* pt_this = &t_g_nav_sleep;

    /* Get the element numbers */
    UTF16_T  w2s_value_string[16+1] = {0};
    UTF16_T  w2s_title_string[16] = {0};
    SIZE_T   z_len=32;
    UINT32   ui4_time;
    UINT8    ui1_elem_num;
    UINT8    ui1_idx;
    //UINT8    ui1_id;

    //ui1_id = nav_get_mlm_lang_id();

    a_sleep_timer_get_num_rec(&ui1_elem_num);

    /* Set Title */
    c_uc_w2s_strcat(w2s_title_string, MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SLEEP_TIMER));
    pt_this->t_view_list_hdlr.pf_set_title_text(w2s_title_string);

    /* Set Index Text */

    for(ui1_idx = 0 ; ui1_idx < ui1_elem_num ; ui1_idx++)
    {
        a_sleep_timer_get_time_by_idx(ui1_idx, &ui4_time);
        a_sleep_timer_get_text(ui4_time, w2s_value_string, z_len);
        pt_this->t_view_list_hdlr.pf_set_index_text((UINT16)ui1_idx, w2s_value_string);
    }

    /* Load config & Get Current Index & Set the Current Index */
   /* a_sleep_timer_get_remaining_time(&ui4_time);
    a_sleep_timer_get_idx_by_timer(ui4_time, &ui1_idx);*/
    pt_this->t_view_list_hdlr.pf_set_hlt_index();

}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_sleep_stop_timer(
                    NAV_SLEEP_T*                pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop sleep::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    NAV_SLEEP_T* pt_this = &t_g_nav_sleep;
    INT32       i4_ret;
    UINT8    ui1_elem_num;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    a_sleep_timer_get_num_rec(&ui1_elem_num);

    i4_ret = pt_this->t_view_hdlr.pf_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset,
                    ui1_elem_num);

    i4_ret = pt_this->t_view_list_hdlr.pf_init(
                     pt_this,
                     pt_ctx->t_gui_res.h_canvas,
                     pt_ctx->t_gui_res.i4_x_offset,
                     pt_ctx->t_gui_res.i4_y_offset,
                     ui1_elem_num);


    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_deinit(VOID)
{
    NAV_SLEEP_T* pt_this = &t_g_nav_sleep;
    INT32       i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    i4_ret = pt_this->t_view_hdlr.pf_deinit();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = pt_this->t_view_list_hdlr.pf_deinit();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_sleep_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_SLEEP_T* pt_this = &t_g_nav_sleep;
    BOOL    b_view_hanlde = FALSE;
    BOOL    b_view_list_handle = FALSE;

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_ANY_UI) == TRUE) {
        return FALSE;
    }

    b_view_list_handle = pt_this->t_view_hdlr.pf_is_key_handler(ui4_key_code);
    b_view_hanlde = pt_this->t_view_list_hdlr.pf_is_key_handler(ui4_key_code);

    return (b_view_list_handle || b_view_hanlde);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_SLEEP_T* pt_this = &t_g_nav_sleep;
    INT32        i4_ret;

    if(pt_this->b_stimer_enable != TRUE)
    {
    /* Set Refreshing Flag */
        pt_this->t_view_list_hdlr.pf_set_is_refreshing(TRUE);

    /* Refresh the Title text / element text */
    _nav_sleep_refresh_list();

    /* Unset Refreshing Flag */
        pt_this->t_view_list_hdlr.pf_set_is_refreshing(FALSE);
    }

    if(ui4_key_code == BTN_SLEEP)
    {
        i4_ret = pt_this->t_view_list_hdlr.pf_activate(ui4_key_code);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }
    }

    if(pt_this->b_stimer_enable == TRUE)
    {
        //nav_sleep_reset_timer(pt_this, SLEEP_TIMEOUT);
        i4_ret = pt_this->t_view_hdlr.pf_activate(ui4_key_code);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
    }

    nav_set_component_visible(NAV_COMP_ID_SLEEP);
    pt_this->b_is_on = TRUE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_POWER_OFF:
        {
            a_sleep_timer_stop();
			/*CR:DTV00845808,DTV00863934,if 3rd resume，nav is pause,API:nav_hide_component(NAV_COMP_ID_SLEEP) not work*/
			if (nav_is_active() == FALSE)
			{
				sleep_timer_view_hide();
				break;
			}
            nav_hide_component(NAV_COMP_ID_SLEEP);
            break;
        }
        default:
            break;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    //a_sleep_timer_stop();
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_hide(
                    VOID
                    )
{
    NAV_SLEEP_T* pt_this = &t_g_nav_sleep;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    pt_this->t_view_hdlr.pf_hide();
    pt_this->t_view_list_hdlr.pf_hide();
    pt_this->b_is_on = FALSE;
    //_nav_sleep_stop_timer(pt_this);
    nav_return_activation(NAV_COMP_ID_SLEEP);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_sleep_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    /* execute in navigator's thread context */
    nav_hide_component(NAV_COMP_ID_SLEEP);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_sleep_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_sleep_timeout_to_hide, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_sleep_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_sleep_reset_timer(
                    NAV_SLEEP_T*                 pt_this,
                    UINT32                       ui4_timeout
                    )
{
    INT32 i4_ret;

    _nav_sleep_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _nav_sleep_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start sleep::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_sleep_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_sleep_register(
                    NAV_SLEEP_VIEW_HDLR_T*      pt_view_hdlr
                    )
{
    NAV_SLEEP_T* pt_this = &t_g_nav_sleep;
    NAV_COMP_T  t_comp;
    INT32       i4_ret;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    /* NAV_COMP_ID_SLEEP */
    t_comp.pf_init           = _nav_sleep_init;
    t_comp.pf_deinit         = _nav_sleep_deinit;
    t_comp.pf_is_key_handler = _nav_sleep_is_key_handler;
    t_comp.pf_activate       = _nav_sleep_activate;
    t_comp.pf_inactivate     = _nav_sleep_inactivate;
    t_comp.pf_hide           = _nav_sleep_hide;
    t_comp.pf_handle_msg     = _nav_sleep_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_SLEEP, &t_comp, COMP_EXEC_SET_SLEEP);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (pt_view_hdlr == NULL)
    {
        nav_sleep_view_register_default_hdlr(&pt_this->t_view_hdlr);
        nav_sleep_view_list_register_default_hdlr(&pt_this->t_view_list_hdlr);
    }
    else {
        pt_this->t_view_hdlr = *pt_view_hdlr;
    }

    return NAVR_OK;
}

VOID a_nav_sleep_timer_set_sleep_reason(UINT32 ui4_stimer_reason,BOOL b_stimer, UINT32 ui4_stimer_nfy_src)
{
    NAV_SLEEP_T* pt_this = &t_g_nav_sleep;

    pt_this->ui4_stimer_reason = ui4_stimer_reason;
    pt_this->b_stimer_enable = b_stimer;
    pt_this->ui4_stimer_nfy_src = ui4_stimer_nfy_src;
}
VOID a_nav_sleep_timer_get_sleep_reason(UINT32* pui4_stimer_reason, BOOL* pb_stimer, UINT32* pui4_stimer_nfy_src)
{
    NAV_SLEEP_T* pt_this = &t_g_nav_sleep;

    *pui4_stimer_reason = pt_this->ui4_stimer_reason;
    *pui4_stimer_nfy_src = pt_this->ui4_stimer_nfy_src;
    *pb_stimer = pt_this->b_stimer_enable;
}

#endif
