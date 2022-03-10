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
 * $RCSfile: pic_mode.c,v $
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
#include "res/app_util/icl/a_icl_custom.h"

#include "nav/pic_mode/pic_mode.h"
#include "res/nav/pic_mode/pic_mode_custom.h"
#include <unistd.h>
#include "fcntl.h"
#include "res/nav/nav_dbg.h"
#include "registry/a_registry.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_PIC_MODE_T t_g_nav_pic_mode;
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
static VOID _nav_pic_mode_refresh_list(VOID)
{
    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;

    /* Get the element numbers */
    UINT16   ui2_elem_num, ui2_elem_idx;
    UINT16   ui2_idx;
	UTF16_T  w2s_str[64] = {0};

	c_memset(w2s_str, 0, sizeof(w2s_str));

    ui2_elem_num = nav_pic_mode_custom_get_vid_pic_mode_numbers();

	/* Set Elem Num */
	pt_this->t_view_hdlr.pf_set_elem_num(ui2_elem_num);

    /* Set Title */
    pt_this->t_view_hdlr.pf_set_title_text(nav_pic_mode_custom_get_title());

    /* Set Index Text */
    for(ui2_idx = 0 ; ui2_idx < ui2_elem_num ; ui2_idx++)
    {
    	nav_pic_mode_custom_get_index_text_ex (ui2_idx, w2s_str);
        pt_this->t_view_hdlr.pf_set_index_text(ui2_idx, w2s_str);
    }

    /* Load config & Get Current Index & Set the Current Index */
    ui2_elem_idx = nav_pic_mode_custom_get_vid_pic_mode_idx();
    pt_this->t_view_hdlr.pf_set_hlt_index(ui2_elem_idx);
    pt_this->ui2_curr_idx = ui2_elem_idx;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_pic_mode_stop_timer(
                    NAV_PIC_MODE_T*                pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop pic_mode::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;
    INT32           i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    if (c_handle_valid(pt_this->h_update_ctrl_timer) == TRUE) {
        c_timer_delete(pt_this->h_update_ctrl_timer);
    }

    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->h_update_ctrl_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;
    pt_this->b_is_view_init      = FALSE;
    pt_this->ui4_timeout  = NAV_PIC_MODE_AUTO_HIDE_TIMER_DURATION;

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_timer_create(&(pt_this->h_update_ctrl_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    /* the view will be inited once the component to be active in order to shrink the memory*/
#if 0
    i4_ret = pt_this->t_view_hdlr.pf_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset,
                    nav_pic_mode_custom_get_vid_pic_mode_numbers()      /* Elem Numbers */
                    );
#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_deinit(VOID)
{
    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;
    INT32           i4_ret;

    if (c_handle_valid(pt_this->h_update_ctrl_timer) == TRUE) {
        c_timer_delete(pt_this->h_update_ctrl_timer);
    }

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    /* deinit the view*/

    if (pt_this->b_is_view_init == TRUE)
    {
    i4_ret = pt_this->t_view_hdlr.pf_deinit();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
        else
        {
            pt_this->b_is_view_init = FALSE;
        }
    }

    pt_this->h_update_ctrl_timer = NULL_HANDLE;
    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_pic_mode_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_ANY_UI) == TRUE) {
        return FALSE;
    }

    return pt_this->t_view_hdlr.pf_is_key_handler(ui4_key_code);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;
    INT32           i4_ret;
    static UINT16   ui2_elem_num = 0;
    UINT16          ui2_elem_num_tmp;
    DBG_LOG_PRINT(("[NAV][%s %d]\n",__FUNCTION__,__LINE__));
    ui2_elem_num_tmp = nav_pic_mode_custom_get_vid_pic_mode_numbers();      /* Elem Numbers */
    if (ui2_elem_num_tmp != ui2_elem_num)
    {
        if (pt_this->b_is_view_init == TRUE)
        {
            pt_this->t_view_hdlr.pf_deinit();
            pt_this->b_is_view_init = FALSE;
        }
        ui2_elem_num = ui2_elem_num_tmp;
    }

    /* do the view init*/
    if (pt_this->b_is_view_init == FALSE)
    {
        i4_ret = pt_this->t_view_hdlr.pf_init(
                        pt_this,
                        pt_ctx->t_gui_res.h_canvas,
                        pt_ctx->t_gui_res.i4_x_offset,
                        pt_ctx->t_gui_res.i4_y_offset,
                        ui2_elem_num_tmp
                        );

        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
        else
        {
            pt_this->b_is_view_init = TRUE;
        }
    }

    /* Set Refreshing Flag */
    pt_this->t_view_hdlr.pf_set_is_refreshing(TRUE);

    /* Refresh the Title text / element text */
    _nav_pic_mode_refresh_list();

    /* Unset Refreshing Flag */
    pt_this->t_view_hdlr.pf_set_is_refreshing(FALSE);

    i4_ret = pt_this->t_view_hdlr.pf_activate(ui4_key_code);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    /* Enable PQ update */
    pt_this->b_can_update_pq = TRUE;

    nav_pic_mode_reset_timer(pt_this);
    nav_grab_activation(NAV_COMP_ID_PICTURE_EFFECT);
    nav_set_component_visible(NAV_COMP_ID_PICTURE_EFFECT);

    if (pt_this->b_is_on == FALSE)
    {
        pt_this->b_is_on = TRUE;
        a_tv_net_OSD_appear();
        a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_EXIST);
    }

	close(open("/tmp/sidebar_menu_show", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));

#ifdef APP_REGISTRY_SUPPORT
        a_registry_set_menu_ui_state(REG_UI_STATE_VISIBLE);
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;

    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        {
            if(pt_this->b_is_on == TRUE)
            {
                nav_hide_component(NAV_COMP_ID_PICTURE_EFFECT);
            }
            break;
        }

        /* [DTV00120546] [5391 US]"picture mode" display wrong */
        /* When timing change, update the picture mode index. */
        case NAV_UI_MSG_STREAM_NOTIFY:
        {
            if( TRUE == pt_this->b_is_on )
            {
                UINT16 ui2_idx;

                ui2_idx = nav_pic_mode_custom_get_vid_pic_mode_idx();
                pt_this->t_view_hdlr.pf_set_hlt_index(ui2_idx);
            }
        }
        break;
        default:
            break;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_hide(
                    VOID
                    )
{
    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }
    DBG_LOG_PRINT(("[MMP][%s %d]",__FUNCTION__,__LINE__));
    pt_this->t_view_hdlr.pf_hide();

    if(pt_this->b_is_on)
    {
        a_tv_net_OSD_disapper();
        a_tv_net_send_cmd(":dtv_app_mtk,am,:unfocus=dtv_app_mtk\n");
    }
    pt_this->b_is_on = FALSE;
    _nav_pic_mode_stop_timer(pt_this);
    c_wgl_set_highlight_widget(NULL_HANDLE);
    /* Return control. */
    if (nav_get_active_component() == NAV_COMP_ID_PICTURE_EFFECT)
    {
        nav_return_activation(NAV_COMP_ID_PICTURE_EFFECT);
    }

    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);
	unlink("/tmp/sidebar_menu_show");

#ifdef APP_REGISTRY_SUPPORT
        a_registry_set_menu_ui_state(REG_UI_STATE_INVISIBLE);
#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_pic_mode_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    /* execute in navigator's thread context */
    nav_hide_component(NAV_COMP_ID_PICTURE_EFFECT);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_pic_mode_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_pic_mode_timeout_to_hide, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_timeout_to_update
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_pic_mode_timeout_to_update(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;

    pt_this->b_can_update_pq = TRUE;

    if (pt_this->ui2_last_idx != pt_this->ui2_curr_idx)
    {
        nav_pic_mode_ctrl_update_index();
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_update_ctrl_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_pic_mode_update_ctrl_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_pic_mode_timeout_to_update, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_reset_update_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_pic_mode_reset_update_timer(VOID)
{
    INT32       i4_ret;

    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;

    if (c_handle_valid(pt_this->h_update_ctrl_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_update_ctrl_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop pic_mode::h_update_ctrl_timer failed!"));
    }

    i4_ret = c_timer_start(
                pt_this->h_update_ctrl_timer,
                NAV_PIC_MODE_UPDATE_PQ_CTRL_TIMER_DURATION,
                X_TIMER_FLAG_ONCE,
                _nav_pic_mode_update_ctrl_timer_nfy,
                pt_this
                );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start pic_mode::h_hide_timer failed!"));
    }

    pt_this->b_can_update_pq = FALSE;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_pic_mode_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_pic_mode_reset_timer(
                    NAV_PIC_MODE_T*                 pt_this
                    )
{
    INT32 i4_ret;

    if(pt_this == NULL)
    {
        pt_this = & t_g_nav_pic_mode;
    }

    _nav_pic_mode_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    pt_this->ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _nav_pic_mode_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start pic_mode::h_hide_timer failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_pic_mode_is_on
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL nav_pic_mode_is_on(VOID)
{
   NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;

   return pt_this->b_is_on;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: API for view to set the index.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID nav_pic_mode_ctrl_set_index(UINT16       ui2_idx)
{
    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;

    if (ui2_idx == pt_this->ui2_curr_idx)
    {
        return;
    }

    pt_this->ui2_curr_idx = ui2_idx;

    if (pt_this->b_can_update_pq)
    {
        nav_pic_mode_ctrl_update_index();
    }
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: API for view to update the index value.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID nav_pic_mode_ctrl_update_index(VOID)
{
    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;

    _nav_pic_mode_reset_update_timer();

    pt_this->ui2_last_idx = pt_this->ui2_curr_idx;

    nav_pic_mode_custom_set_vid_pic_mode_idx(pt_this->ui2_curr_idx);
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_pic_mode_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_pic_mode_register(
                    NAV_PIC_MODE_VIEW_HDLR_T*      pt_view_hdlr,
                    NAV_PIC_MODE_STYLE             e_style
                    )
{
    NAV_PIC_MODE_T* pt_this = &t_g_nav_pic_mode;
    NAV_COMP_T      t_comp;
    INT32           i4_ret;

    NAV_DEBUG_PIC_MODE( DBG_LOG_PRINT(("[NAV][PIC_MODE]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    c_memset( &t_comp, 0, sizeof(NAV_COMP_T) );

    /* NAV_COMP_ID_PICTURE_EFFECT */
    t_comp.pf_init           = _nav_pic_mode_init;
    t_comp.pf_deinit         = _nav_pic_mode_deinit;
    t_comp.pf_is_key_handler = _nav_pic_mode_is_key_handler;
    t_comp.pf_activate       = _nav_pic_mode_activate;
    t_comp.pf_inactivate     = _nav_pic_mode_inactivate;
    t_comp.pf_hide           = _nav_pic_mode_hide;
    t_comp.pf_handle_msg     = _nav_pic_mode_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_PICTURE_EFFECT, &t_comp, COMP_EXEC_SET_PICTURE_EFFECT);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (pt_view_hdlr == NULL)
    {
        if(e_style == NAV_PIC_MODE_STYLE_LISTBOX)
        {
            nav_pic_mode_view_register_list_hdlr(&pt_this->t_view_hdlr);
        }
        else if(e_style == NAV_PIC_MODE_STYLE_DIALOG)
        {
            nav_pic_mode_view_register_dialog_hdlr(&pt_this->t_view_hdlr);
        }
        else if(e_style == NAV_PIC_MODE_STYLE_SINGLE_SELECT_LIST)
        {
            nav_pic_mode_view_register_single_select_list_hdlr(&pt_this->t_view_hdlr);
        }
        else
        {    /* Default */
            nav_pic_mode_view_register_list_hdlr(&pt_this->t_view_hdlr);
        }
    }
    else {
        pt_this->t_view_hdlr = *pt_view_hdlr;
    }

    return NAVR_OK;
}

BOOL nav_pic_mode_is_dovi_mode(VOID)
{
   return NAVR_OK;
}

#endif /* APP_537X_SUPPORT */

