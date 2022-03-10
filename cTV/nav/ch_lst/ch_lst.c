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
 * $RCSfile: ch_lst.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_irrc_btn_def.h"
#include "u_sb.h"
#include "u_sb_atsc_eng.h"
#include "u_sb_ntsc_eng.h"

#include "c_wgl.h"
#include "c_handle.h"
#include "c_svl.h"
#include "c_evctx.h"
#include "c_uc_str.h"

#include "app_util/a_common.h"
#include "app_util/a_tv.h"
#include "nav/a_navigator.h"
#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"
#include "nav/ch_lst/ch_lst.h"
#include "nav/ch_lst/a_ch_lst.h"
#include "nav/ch_lst/ch_number.h"


#include "wdk/a_cnt_indctr.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "res/nav/one_channel_list/ocl.h"

#include "app_util/config/acfg_ch_lst.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * note
 *---------------------------------------------------------------------------*/
/*
    ATSC:    Page up, Page down
    DVBT/C:  Page up, Page down, List Selection, Exit (Blue)
    DVBS:    Page up, Page down, List Selection, Satellite Selection (Blue)
*/

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_CH_ID_LARGER(p1, p2)                                                 \
    (SB_ATSC_GET_MAJOR_CHANNEL_NUM(p1) >  SB_ATSC_GET_MAJOR_CHANNEL_NUM(p2)     \
 || (SB_ATSC_GET_MAJOR_CHANNEL_NUM(p1) == SB_ATSC_GET_MAJOR_CHANNEL_NUM(p2)     \
 &&  SB_ATSC_GET_MINOR_CHANNEL_NUM(p1) >  SB_ATSC_GET_MINOR_CHANNEL_NUM(p2)))

#define IS_CH_ID_SMALLER(p1, p2)                                                \
    (SB_ATSC_GET_MAJOR_CHANNEL_NUM(p1) <  SB_ATSC_GET_MAJOR_CHANNEL_NUM(p2)     \
 || (SB_ATSC_GET_MAJOR_CHANNEL_NUM(p1) == SB_ATSC_GET_MAJOR_CHANNEL_NUM(p2)     \
 &&  SB_ATSC_GET_MINOR_CHANNEL_NUM(p1) <  SB_ATSC_GET_MINOR_CHANNEL_NUM(p2)))

#define IS_CH_ID_EQUAL(p1, p2)                                                  \
    (SB_ATSC_GET_MAJOR_CHANNEL_NUM(p1) == SB_ATSC_GET_MAJOR_CHANNEL_NUM(p2)     \
 &&  SB_ATSC_GET_MINOR_CHANNEL_NUM(p1) == SB_ATSC_GET_MINOR_CHANNEL_NUM(p2))

#define IS_FAKE_OR_HIDDEN_SVL_REC(p1)                               \
    ((p1)->uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_VISIBLE) == 0

#define CHANNEL_ID(p1)       ((p1)->uheader.t_rec_hdr.ui4_channel_id)
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
NAV_CH_LST_T t_g_ch_lst;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _nav_ch_lst_stop_timer(
                    NAV_CH_LST_T*               pt_this
                    );
static VOID _nav_ch_lst_reset_timer(
                    NAV_CH_LST_T*               pt_this
                    );
static VOID _nav_ch_lst_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );
static VOID _nav_ch_lst_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    );
static INT32 _nav_ch_lst_update_nav_context(
                    NAV_CH_LST_T*               pt_this,
                    const NAV_CONTEXT_T*        pt_ctx
                    );
static VOID _nav_ch_lst_validate(
                    NAV_CH_LST_T*               pt_this,
                    TV_ITERATE_DIR_T            e_iter_dir,
                    UINT32                      ui4_lst_channel_id,
                    const SVL_REC_T*            pt_ref_svl_rec,
                    UINT16*                     pui2_hlt_elem_idx,
                    UINT16*                     pui2_num_recs
                    );
static INT32 _nav_ch_lst_page_up_dn(
                    NAV_CH_LST_T*               pt_this,
                    BOOL                        b_page_up
                    );
static INT32 _nav_ch_lst_update_lst(
                    NAV_CH_LST_T*               pt_this,
                    UINT32                      ui4_channel_id,
                    TV_ITERATE_DIR_T            e_iter_dir,
                    BOOL                        b_force_hlt,
                    UINT16                      ui2_force_hlt_elem_idx,
                    BOOL                        b_repaint
                    );
static BOOL _nav_ch_lst_search_svl_rec(
                    NAV_CH_LST_T*               pt_this,
                    const SVL_REC_T*            pt_svl_rec,
                    UINT16*                     pui2_elem_idx
                    );
static INT32 _nav_ch_lst_update_dtl(
                    NAV_CH_LST_T*               pt_this,
                    HANDLE_T                    h_crnt_svctx
                    );
static INT32 _nav_ch_lst_handle_event_update(
                    NAV_CH_LST_T*               pt_this,
                    HANDLE_T                    h_svctx,
                    BOOL                        b_ready
                    );
static INT32 _nav_ch_lst_handle_ch_change(
                    NAV_CH_LST_T*               pt_this,
                    NAV_CONTEXT_T*              pt_ctx
                    );
static INT32 _nav_ch_lst_handle_svl_update(
                    NAV_CH_LST_T*               pt_this,
                    NAV_CONTEXT_T*              pt_ctx
                    );
static INT32 _nav_ch_lst_handle_no_signal(
                    NAV_CH_LST_T*               pt_this,
                    NAV_CONTEXT_T*              pt_ctx
                    );
static INT32 _nav_ch_lst_handle_with_signal(
                    NAV_CH_LST_T*               pt_this,
                    NAV_CONTEXT_T*              pt_ctx
                    );
static INT32 _nav_ch_lst_handle_locked(
                    NAV_CH_LST_T*               pt_this,
                    NAV_CONTEXT_T*              pt_ctx
                    );
static INT32 _nav_ch_lst_hide_dtls(
                    NAV_CH_LST_T*               pt_this
                    );

static INT32 _nav_ch_lst_reset_list_elmnts(
                    NAV_CH_LST_T*               pt_this
                    );
static BOOL _nav_ch_lst_search_first_svl_rec(
                    NAV_CH_LST_T*               pt_this,
                    UINT16*                     pui2_elem_idx
                    );

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    NAV_CH_LST_T* pt_this = &t_g_ch_lst;
    INT32          i4_ret;

    c_memset (pt_this, 0, sizeof(NAV_CH_LST_T));

    pt_this->b_is_on         = FALSE;
    pt_this->b_is_list_on    = FALSE;
    pt_this->b_is_detail_on  = FALSE;
    pt_this->ui2_focused_idx = 0;
    pt_this->b_ch_changed    = FALSE;

    /* Compile option */
#ifdef APP_SUPPORT_MULTIPLE_CHANNEL_LIST
    /* no channel selection in ATV only model */
    if (a_cfg_ftm_is_atv_only_model ()) {
        pt_this->b_is_support_multiple_channel_list = FALSE;
    } else {
        pt_this->b_is_support_multiple_channel_list = TRUE;
    }
#else
    pt_this->b_is_support_multiple_channel_list = FALSE;
#endif

#ifdef APP_DVBS_SUPPORT
    pt_this->b_is_support_satellite_selection = TRUE;
#else
    pt_this->b_is_support_satellite_selection = FALSE;
#endif

    i4_ret = ch_number_init();
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = nav_ch_lst_view_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset,
                    pt_ctx->t_gui_res.e_color_type
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = nav_ch_dtl_view_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset,
                    pt_ctx->t_gui_res.e_color_type
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    DBG_LOG_PRINT(("[OCL] init ocl at ch_list!\n"));
    ocl_init();

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 _nav_ch_lst_deinit(
                    VOID
                    )
{
    NAV_CH_LST_T* pt_this = &t_g_ch_lst;
    INT32         i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    i4_ret = nav_ch_lst_view_deinit(&pt_this->t_lst_view);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = nav_ch_dtl_view_deinit(&pt_this->t_dtl_view);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = ch_number_deinit();
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }

    pt_this->b_is_on         = FALSE;
    pt_this->b_is_list_on    = FALSE;
    pt_this->b_is_detail_on  = FALSE;
    pt_this->ui2_focused_idx = 0;
    pt_this->h_hide_timer    = NULL_HANDLE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_is_key_handler_ex
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_is_key_handler_ex(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code,
                    NAV_IS_KEY_HANDLER_RET_T*   pe_ret
                    )
{
    ACFG_RETAIL_MODE_T	t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

    /* channel number sub component key handler */
    static BOOL b_is_ch_sel = FALSE;
    if (ch_number_is_activate())
    {
        ch_number_rcu_key_handler(ui4_key_code);
        if(ui4_key_code == BTN_SELECT)
        {
            b_is_ch_sel = TRUE;
            *pe_ret = NAV_IS_KEY_HANDLER_RET_FALSE_WITH_DO_NOT_CONTINUE;
            return NAVR_OK;
        }
        *pe_ret = NAV_IS_KEY_HANDLER_RET_FALSE;
    }
    else if (ch_number_is_key_handler(pt_ctx->t_svc_res.e_focus_tv_win_id,ui4_key_code))
    {
        ch_number_activate(pt_ctx->t_svc_res.e_focus_tv_win_id,ui4_key_code);
        *pe_ret = NAV_IS_KEY_HANDLER_RET_FALSE;
    }

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_CH_LIST_UI) == TRUE) {
        *pe_ret = NAV_IS_KEY_HANDLER_RET_FALSE;
    }

    if (nav_get_src_type(pt_ctx->t_svc_res.e_focus_tv_win_id) != INP_SRC_TYPE_TV) {
        *pe_ret = NAV_IS_KEY_HANDLER_RET_FALSE;
    }

    if (nav_is_svl_empty(pt_ctx->t_svc_res.e_focus_tv_win_id) == TRUE) {
        *pe_ret = NAV_IS_KEY_HANDLER_RET_FALSE;
    }

	a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        *pe_ret = NAV_IS_KEY_HANDLER_RET_FALSE;
    }

    /* as third party app runing should show ch list*/
    if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
    {
        *pe_ret = NAV_IS_KEY_HANDLER_RET_FALSE;
    }

    switch(ui4_key_code) {
#ifndef APP_ONLY_OPERATE_BY_CH_LIST_BTN
    case BTN_SELECT:
        switch(nav_get_locked_status(pt_ctx->t_svc_res.e_focus_tv_win_id)) {
        case LOCKED_STATUS_PROGRAM_RATING:
        case LOCKED_STATUS_CHANNEL_LOCKED:
        case LOCKED_STATUS_INP_SRC_LOCKED:
            *pe_ret = NAV_IS_KEY_HANDLER_RET_FALSE;
        default:
            break;
        }
#endif
    case BTN_CH_LIST:
        if(b_is_ch_sel == TRUE)
        {
            b_is_ch_sel = FALSE;
            *pe_ret = NAV_IS_KEY_HANDLER_RET_FALSE;
        }
        *pe_ret = NAV_IS_KEY_HANDLER_RET_TRUE;
    default:
        break;
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_CH_LST_T* pt_this = &t_g_ch_lst;
    INT32         i4_ret;
    UINT32        ui4_channel_id;
    SVL_REC_T     t_svl_rec;
    BOOL          b_ret = FALSE;

    i4_ret = _nav_ch_lst_update_nav_context(pt_this, pt_ctx);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    nav_ch_lst_view_load_msgs(nav_get_mlm_lang_id());

    /*get first channel info*/
    b_ret = a_tv_mcl_get_svl_rec_by_logic_and_nw_masks(
                    pt_this->h_crnt_svl,
                    a_tv_get_listable_svl_rec_check_nw_mask(),
                    a_tv_get_listable_svl_rec_check_nw_bits(),
                    TV_ITERATE_DIR_FIRST,
                    &ui4_channel_id,
                    &t_svl_rec);
    if(b_ret == FALSE)
    {
        pt_this->ui2_first_svl_rec_id = SVL_NULL_REC_ID;
        pt_this->ui4_first_channel_id = 0;
    }
    else
    {
        pt_this->ui2_first_svl_rec_id = t_svl_rec.ui2_svl_rec_id;
        pt_this->ui4_first_channel_id = ui4_channel_id;
    }

     /*get last channel info*/
    b_ret = a_tv_mcl_get_svl_rec_by_logic_and_nw_masks(
                    pt_this->h_crnt_svl,
                    a_tv_get_listable_svl_rec_check_nw_mask(),
                    a_tv_get_listable_svl_rec_check_nw_bits(),
                    TV_ITERATE_DIR_LAST,
                    &ui4_channel_id,
                    &t_svl_rec);
    if(b_ret == FALSE)
    {
        pt_this->ui2_last_svl_rec_id = SVL_NULL_REC_ID;
        pt_this->ui4_last_channel_id = 0;
    }
    else
    {
        pt_this->ui2_last_svl_rec_id = t_svl_rec.ui2_svl_rec_id;
        pt_this->ui4_last_channel_id = ui4_channel_id;
    }

    i4_ret = _nav_ch_lst_update_lst(
                    pt_this,
                    a_util_cnfg_get_crnt_channel_id(),
                    TV_ITERATE_DIR_CRNT,
                    FALSE, /* b_force_hlt */
                    0,
                    FALSE  /* b_repaint  */
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = nav_ch_lst_view_show(&pt_this->t_lst_view, pt_this->ui4_cnt_indctr_state);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    _nav_ch_lst_reset_timer(pt_this);

    pt_this->b_is_on        = TRUE;
    pt_this->b_is_list_on   = TRUE;
    pt_this->b_is_detail_on = FALSE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_inactivate(NAV_CONTEXT_T*              pt_ctx)
{
    return (ch_number_inactivate());
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_hide(
                    VOID
                    )
{
    NAV_CH_LST_T* pt_this = &t_g_ch_lst;
    INT32         i4_ret;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    i4_ret = nav_ch_lst_view_hide(&pt_this->t_lst_view);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    _nav_ch_lst_hide_dtls(pt_this);

    pt_this->b_is_on        = FALSE;
    pt_this->b_is_list_on   = FALSE;

    _nav_ch_lst_stop_timer(pt_this);
    nav_return_activation(NAV_COMP_ID_CH_LIST);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_get_crnt_svl_rec(NAV_CH_LST_T*      pt_this,
                                          TV_WIN_ID_T        e_tv_win_id,
                                          SVL_REC_T*         pt_crnt_svl_rec)
{
    INT32   i4_ret = NAVR_OK;
    UINT32  ui4_channel_id = a_util_cnfg_get_crnt_channel_id();
    /* Get current channel successfully. */
    BOOL    b_ret      = FALSE;

    i4_ret = nav_get_svl_rec(e_tv_win_id, pt_crnt_svl_rec);
    if (i4_ret < NAVR_OK)
    {
        return NAVR_FAIL;
    }

#ifdef APP_DVBT_SUPPORT

    /*
       In DVBT Environment, no "Hidden" channel will be shown in channel list.
       Hence, if current channel is "Hidden" channel, try to get the first "Non-Hidden"
       channel as current channel.
    */

    /* Check fake or hidden. */
    if (IS_FAKE_OR_HIDDEN_SVL_REC(pt_crnt_svl_rec))
    {
        /* Try to get first non-fake/hidden channel. */
        b_ret = a_tv_mcl_get_svl_rec_by_logic_and_nw_masks(
                    pt_this->h_crnt_svl,
                    SB_VNET_ACTIVE,
                    SB_VNET_ACTIVE,
                    TV_ITERATE_DIR_FIRST,
                    &ui4_channel_id,
                    pt_crnt_svl_rec
                    );
        if (b_ret == FALSE)
        {
            return NAVR_FAIL;
        }
    }
#endif

    if (pt_this->b_is_support_multiple_channel_list)
    {
        /* Check the current channel is in corresponding list. */
        if (! a_tv_mcl_is_svl_rec_in_crnt_list(pt_this->h_crnt_svl,
                                               pt_crnt_svl_rec))
        {
            /* Try to get first non-fake/hidden channel. */
            b_ret = a_tv_mcl_get_svl_rec_by_logic_and_nw_masks(
                        pt_this->h_crnt_svl,
                        SB_VNET_ACTIVE,
                        SB_VNET_ACTIVE,
                        TV_ITERATE_DIR_FIRST,
                        &ui4_channel_id,
                        pt_crnt_svl_rec
                        );
            if (b_ret == FALSE)
            {
                return NAVR_FAIL;
            }
        }
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_hide_dtls
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_hide_dtls(
                    NAV_CH_LST_T*               pt_this
                    )
{
#ifndef APP_CH_LIST_NO_CHANNEL_DETAIL

    INT32 i4_ret;

    if (pt_this->b_is_detail_on == FALSE) {
        return NAVR_OK;
    }

    i4_ret = nav_ch_dtl_view_hide(&pt_this->t_dtl_view);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"nav_ch_dtl_view_hide() failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

    pt_this->b_is_detail_on = FALSE;

#endif
    return NAVR_OK;

}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 _nav_ch_lst_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    NAV_CH_LST_T* pt_this = &t_g_ch_lst;
    INT32         i4_ret  = NAVR_OK;
    /* channel number sub component handle msg */
    ch_number_handle_msg(pt_ctx,pt_ui_msg,pv_arg1);

    if(pt_ui_msg->e_tv_win_id != TV_WIN_ID_LAST_VALID_ENTRY
            && nav_get_src_type(pt_ui_msg->e_tv_win_id) != INP_SRC_TYPE_TV) {
        if (pt_this->b_is_on == TRUE) {

            /* Some message could be ignored, others will hide channel list */
            switch (pt_ui_msg->e_id)
            {
                case NAV_UI_MSG_WITH_SIGNAL:
                case NAV_UI_MSG_WITH_SIGNAL_AS_PARENTAL_LOCKED:
                case NAV_UI_MSG_AFTER_SVC_CHANGE:
                case NAV_UI_MSG_STREAM_NOTIFY:
                case NAV_UI_MSG_SCDB_UPDATE:
                case NAV_UI_MSG_AV_STATUS_NOTIFY:
                break;
                case NAV_UI_MSG_EVENT_READY:
                {
                    if (pt_ui_msg->e_tv_win_id == pt_this->e_focus_tv_win_id)
                    {
                        nav_hide_component(NAV_COMP_ID_CH_LIST);
                    }
                }
                break;

                default:
                    nav_hide_component(NAV_COMP_ID_CH_LIST);
                break;
            }

        }
        return NAVR_OK;
    }

    switch(pt_ui_msg->e_id) {
    case NAV_UI_MSG_NO_SIGNAL:
        i4_ret = _nav_ch_lst_handle_no_signal(pt_this, pt_ctx);
        break;
    case NAV_UI_MSG_WITH_SIGNAL:
        i4_ret = _nav_ch_lst_handle_with_signal(pt_this, pt_ctx);
        break;
    case NAV_UI_MSG_LOCKED_PROG:
    case NAV_UI_MSG_LOCKED_CH:
    case NAV_UI_MSG_LOCKED_INP:
        i4_ret = _nav_ch_lst_handle_locked(pt_this, pt_ctx);
        break;
    case NAV_UI_MSG_BEFORE_SVC_CHANGE:
    {
        NAV_XNG_SRC_TRGT_T* pt_xng_info = (NAV_XNG_SRC_TRGT_T*)pv_arg1;

        if (pt_this->b_ch_changed == FALSE
                && pt_ui_msg->e_src_type == INP_SRC_TYPE_TV
                && nav_is_same_channel(
                                pt_xng_info->u.t_tv.ui2_crnt_svl_id,
                                pt_xng_info->u.t_tv.ui2_crnt_svl_rec_id,
                                pt_xng_info->u.t_tv.ui4_crnt_channel_id,
                                pt_xng_info->u.t_tv.ui2_trgt_svl_id,
                                pt_xng_info->u.t_tv.ui2_trgt_svl_rec_id,
                                pt_xng_info->u.t_tv.ui4_trgt_channel_id
                                ) == TRUE) {
            break;
        }

        pt_this->b_ch_changed = FALSE;
        i4_ret =_nav_ch_lst_hide_dtls(pt_this);
        if (i4_ret != NAVR_OK) {
            break;
        }
        i4_ret = _nav_ch_lst_handle_ch_change(pt_this, pt_ctx);
        break;
    }
    case NAV_UI_MSG_AFTER_SVC_CHANGE:
        pt_this->b_ch_changed = TRUE;
        break;
    case NAV_UI_MSG_SVL_UPDATE:
        i4_ret = _nav_ch_lst_handle_svl_update(pt_this, pt_ctx);
		/*Store SVL/TSL/NWL*/
        #if 0
		i4_ret = a_cfg_ch_lst_store();
		if(i4_ret != APP_CFGR_OK)
		{
			DBG_LOG_PRINT(("<ACFG> %s %d Can't store SVL/TSL/NWL.\n",__FUNCTION__,__LINE__));
		}
        #endif
        break;
    case NAV_UI_MSG_EVENT_READY:
        i4_ret = _nav_ch_lst_handle_event_update(pt_this, pt_ui_msg->h_svctx, TRUE);
        break;
    case NAV_UI_MSG_EVENT_NOT_READY:
        i4_ret = _nav_ch_lst_handle_event_update(pt_this, pt_ui_msg->h_svctx, FALSE);
        break;
    case NAV_UI_MSG_EMPTY_SVL:
    case NAV_UI_MSG_TV_SRC_CHANGED:
        i4_ret = nav_hide_component(NAV_COMP_ID_CH_LIST);
        break;
#ifdef APP_ISDB_SUPPORT
    case NAV_UI_MSG_CH_LOGO_LOAD_OK:
        if (pt_this->b_is_on)
        {
            i4_ret = _nav_ch_lst_update_lst(
                    pt_this,
                    a_util_cnfg_get_crnt_channel_id(),
                    TV_ITERATE_DIR_CRNT,
                    FALSE, /* b_force_hlt */
                    0,
                    pt_this->b_is_on /* b_repaint  */
                    );
        }
        break;
#endif
    default:
        i4_ret = NAVR_OK;
        break;
    }
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_update_lst
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_update_lst(
                    NAV_CH_LST_T*               pt_this,
                    UINT32                      ui4_channel_id,
                    TV_ITERATE_DIR_T            e_iter_dir,
                    BOOL                        b_force_hlt,
                    UINT16                      ui2_force_hlt_elem_idx,
                    BOOL                        b_repaint
                    )
{
    SVL_REC_T t_svl_rec          = {0};
    UINT32    ui4_lst_channel_id = ui4_channel_id;
    UINT16    ui2_hlt_elem_idx = 0;
    UINT16    ui2_num_recs = 0;
    INT32     i4_ret;
    BOOL      b_ret;
    BOOL      b_is_null_list_mode= FALSE;

    if (e_iter_dir == TV_ITERATE_DIR_CRNT && ui4_channel_id == a_util_cnfg_get_crnt_channel_id()) {
        i4_ret = _nav_ch_lst_get_crnt_svl_rec(pt_this,
                                              pt_this->e_focus_tv_win_id,
                                              &t_svl_rec);
        if (i4_ret < NAVR_OK)
        {
            if (pt_this->b_is_support_multiple_channel_list)
            {
                /* Entering NULL LIST mode. */
                b_is_null_list_mode = TRUE;
            }
            else
            {
                return NAVR_FAIL;
            }
        }
    } else {
        b_ret = a_tv_mcl_get_svl_rec_by_logic_and_nw_masks(
                    pt_this->h_crnt_svl,
                    a_tv_get_listable_svl_rec_check_nw_mask(),
                    a_tv_get_listable_svl_rec_check_nw_bits(),
                    e_iter_dir,
                    &ui4_channel_id,
                    &t_svl_rec
                    );
        if (b_ret == FALSE) {
            return NAVR_FAIL;
        }
    }

    /* Normal list mode */
    if (b_is_null_list_mode == FALSE)
    {
        _nav_ch_lst_validate(
                        pt_this,
                        e_iter_dir,
                        ui4_lst_channel_id,
                        &t_svl_rec,
                        &ui2_hlt_elem_idx,
                        &ui2_num_recs
                        );
        if (b_force_hlt == TRUE && ui2_force_hlt_elem_idx < MIN_VALUE(ui2_num_recs, MAX_ELEM_OF_CH_LIST)) {
            ui2_hlt_elem_idx = ui2_force_hlt_elem_idx;
        }

        nav_ch_lst_view_update(
                        &pt_this->t_lst_view,
                        pt_this->t_elements,
                        ui2_num_recs,
                        MIN_VALUE(ui2_num_recs, MAX_ELEM_OF_CH_LIST),
                        ui2_hlt_elem_idx,
                        pt_this->ui4_cnt_indctr_state,
                        b_repaint
                        );
    }
    /* NULL list mode */
    else
    {
        /* reset the list elmnts because of NULL list mode. */
        _nav_ch_lst_reset_list_elmnts(pt_this);

        /* reset the focused index */
        pt_this->ui2_focused_idx = 0;

        nav_ch_lst_view_update(
                        &pt_this->t_lst_view,
                        pt_this->t_elements,
                        0,
                        0,
                        0,
                        pt_this->ui4_cnt_indctr_state,
                        b_repaint
                        );
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_ch_lst_stop_timer(
                    NAV_CH_LST_T*               pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop ch_lst::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_ch_lst_reset_timer(
                    NAV_CH_LST_T*               pt_this
                    )
{
    INT32 i4_ret;

    _nav_ch_lst_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    CH_LIST_TIMER_DELAY,
                    X_TIMER_FLAG_ONCE,
                    _nav_ch_lst_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start ch_lst::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_ch_lst_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    /* execute in navigator's thread context */
    nav_hide_component(NAV_COMP_ID_CH_LIST);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_ch_lst_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_ch_lst_timeout_to_hide, pv_tag, NULL, NULL);
}
/*----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_set_list_elmnt
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_set_list_elmnt(
                    NAV_CH_LST_T*               pt_this,
                    UINT16                      ui2_idx,
                    const SVL_REC_T*            pt_svl_rec
                    )
{
    if (ui2_idx >= MAX_ELEM_OF_CH_LIST) {
        return NAVR_INV_ARG;
    }

    if (pt_svl_rec == NULL) {
        pt_this->t_elements[ui2_idx].ui4_channel_id   = INVALID_CHANNEL_ID;
        pt_this->t_elements[ui2_idx].ui2_svl_id       = SVL_NULL_ID;
        pt_this->t_elements[ui2_idx].ui2_svl_rec_id   = SVL_NULL_REC_ID;
        pt_this->t_elements[ui2_idx].s_ch_num[0]      = '\0';
        pt_this->t_elements[ui2_idx].s_ch_name[0]     = '\0';
        pt_this->t_elements[ui2_idx].ui4_nw_mask      = 0;
        pt_this->t_elements[ui2_idx].e_brdcst_type    = BRDCST_TYPE_UNKNOWN;
        pt_this->t_elements[ui2_idx].e_serv_type      = SVL_SERVICE_TYPE_UNKNOWN;
        pt_this->t_elements[ui2_idx].ui2_ca_system_id = 0;
        pt_this->t_elements[ui2_idx].s_ch_name_short[0] = '\0';
    } else {
        DBG_INFO((_INFO_HEADER"set %d-th element to ch %d.%d \r\n",
                    ui2_idx,
                    SB_ATSC_GET_MAJOR_CHANNEL_NUM(pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id),
                    SB_ATSC_GET_MINOR_CHANNEL_NUM(pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id)
                    ));

        pt_this->t_elements[ui2_idx].ui4_channel_id   = pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id;
        pt_this->t_elements[ui2_idx].ui2_svl_id       = pt_this->ui2_crnt_svl_id;
        pt_this->t_elements[ui2_idx].ui2_svl_rec_id   = pt_svl_rec->ui2_svl_rec_id;
        pt_this->t_elements[ui2_idx].ui4_nw_mask      = pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask;
        pt_this->t_elements[ui2_idx].e_brdcst_type    = pt_svl_rec->uheader.t_rec_hdr.e_brdcst_type;
        pt_this->t_elements[ui2_idx].e_serv_type      = pt_svl_rec->uheader.t_rec_hdr.e_serv_type;
        pt_this->t_elements[ui2_idx].ui2_ca_system_id = pt_svl_rec->u_data.t_dvb.ui2_ca_system_id;
        nav_set_ch_num_and_name(
                    pt_svl_rec,
                    pt_this->t_elements[ui2_idx].s_ch_num,
                    pt_this->t_elements[ui2_idx].s_ch_name
                    );
        c_strncpy(pt_this->t_elements[ui2_idx].s_ch_name_short,
                  pt_svl_rec->u_data.t_dvb.s_svc_name,
                  MAX_DVB_SERVICE_NAME_LEN);

    }
    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_reset_list_elmnts
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_reset_list_elmnts(
                    NAV_CH_LST_T*               pt_this
                    )
{
    UINT16 ui2_idx;

    for (ui2_idx = 0; ui2_idx < MAX_ELEM_OF_CH_LIST; ui2_idx++) {
        _nav_ch_lst_set_list_elmnt(pt_this, ui2_idx, NULL);
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_get_svl_num_rec
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static BOOL _nav_ch_lst_get_svl_num_rec(
                    NAV_CH_LST_T*               pt_this,
                    SVL_REC_T*                  pt_crnt_svl_rec,
                    UINT16*                     pui2_num_recs
                    )
{
    /* Deprecated.
       Use the app_tv API to get the number of channels with Active, and Non-fake attributes.
    */
    INT32   i4_ret;

    i4_ret = a_tv_mcl_get_svl_rec_num_by_nw_masks(
                  pt_this->h_crnt_svl,
                  a_tv_get_listable_svl_rec_check_nw_mask(),
                  a_tv_get_listable_svl_rec_check_nw_bits(),
                  pui2_num_recs);
    if (i4_ret < TVR_OK)
    {
        return FALSE;
    }

    /* Only NTSC environment will show hidden/fake channel. */
#if (APP_NTSC_SPT==1)
    if (IS_FAKE_OR_HIDDEN_SVL_REC(pt_crnt_svl_rec)) {
        *pui2_num_recs += 1;
    }
#endif

    return TRUE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_between
 * Description
 *              chcek ui4_middle is between ui4_left and ui4_right or not.
 * Input        ui4_left
 *              ui4_middle
 *              ui4_right
 *              b_left_is_smallest
 * Output       -
 * Returns      TRUE
 *              FALSE
 *-----------------------------------------------------------------------------*/
static BOOL _nav_ch_lst_between(
                    UINT32                      ui4_left,
                    UINT32                      ui4_middle,
                    UINT32                      ui4_right,
                    UINT32                      b_left_is_smallest
                    )
{
    if (b_left_is_smallest == TRUE) {
        if ((IS_CH_ID_SMALLER(ui4_left, ui4_middle) || IS_CH_ID_EQUAL(ui4_left, ui4_middle))
                && (IS_CH_ID_SMALLER(ui4_middle, ui4_right) || IS_CH_ID_EQUAL(ui4_middle, ui4_right))) {
            return TRUE;
        }
    } else {
        if ((IS_CH_ID_LARGER(ui4_left, ui4_middle) || IS_CH_ID_EQUAL(ui4_left, ui4_middle))
                && (IS_CH_ID_LARGER(ui4_middle, ui4_right) || IS_CH_ID_EQUAL(ui4_middle, ui4_right))) {
            return TRUE;
        }
    }
    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_fill_elements
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static BOOL _nav_ch_lst_fill_elements(
                    NAV_CH_LST_T*               pt_this,
                    const SVL_REC_T*            pt_crnt_svl_rec,
                    UINT32                      ui4_prev_ch_id,
                    TV_ITERATE_DIR_T            e_dir,
                    UINT16                      ui2_from_idx,
                    UINT16                      ui2_times,
                    BOOL*                       pb_to_insert_crnt
                    )
{
    UINT32    ui4_next_ch_id = ui4_prev_ch_id;
    BOOL      b_top_down     = e_dir == TV_ITERATE_DIR_NEXT? TRUE : FALSE;
    SVL_REC_T t_next_svl_rec;
    UINT16    ui2_elm_idx;
    UINT16    ui2_idx;

    for (ui2_idx = 0; ui2_idx < ui2_times; ui2_idx++) {
        if (a_tv_mcl_get_svl_rec_by_logic_and_nw_masks(
                        pt_this->h_crnt_svl,
                        a_tv_get_listable_svl_rec_check_nw_mask(),
                        a_tv_get_listable_svl_rec_check_nw_bits(),
                        e_dir,
                        &ui4_next_ch_id,
                        &t_next_svl_rec
                        ) == FALSE) {
            return FALSE;
        }

        if (*pb_to_insert_crnt == FALSE) {
            do {
                /* normal case */
                if (_nav_ch_lst_between(
                        ui4_prev_ch_id,
                        CHANNEL_ID(pt_crnt_svl_rec),
                        CHANNEL_ID(&t_next_svl_rec),
                        b_top_down) == TRUE) {
                    *pb_to_insert_crnt = TRUE;
                    break;
                }

                if (b_top_down == TRUE) {
                    /* normal case:    prev < next
                     * exception case: loop-back to first one - prev > next
                     * exception case: prev = next < crnt and crnt is fake
                     */
                    if (IS_CH_ID_LARGER(ui4_prev_ch_id, CHANNEL_ID(&t_next_svl_rec))
                            || (ui2_times == 1 && ui4_prev_ch_id == CHANNEL_ID(&t_next_svl_rec)) ) {
                        /* crnt > prev or crnt < next */
                        if (IS_CH_ID_LARGER(CHANNEL_ID(pt_crnt_svl_rec), ui4_prev_ch_id)
                                || IS_CH_ID_SMALLER(CHANNEL_ID(pt_crnt_svl_rec), CHANNEL_ID(&t_next_svl_rec))) {
                            *pb_to_insert_crnt = TRUE;
                            break;
                        }
                    }
                } else {
                    /* normal case:    prev > next
                     * exception case: loop-back to last one - prev < next
                     */
                    if (IS_CH_ID_SMALLER(ui4_prev_ch_id, CHANNEL_ID(&t_next_svl_rec))) {
                        /* crnt < prev or crnt > next */
                        if (IS_CH_ID_SMALLER(CHANNEL_ID(pt_crnt_svl_rec), ui4_prev_ch_id)
                                || IS_CH_ID_LARGER(CHANNEL_ID(pt_crnt_svl_rec), CHANNEL_ID(&t_next_svl_rec))) {
                            *pb_to_insert_crnt = TRUE;
                            break;
                        }
                    }
                }
            } while (0);

            if (*pb_to_insert_crnt == TRUE) {
                /* could insert the pt_crnt_svl_rec before t_next_svl_rec */
                ui2_elm_idx        = b_top_down ? (ui2_from_idx + ui2_idx) : (ui2_from_idx - ui2_idx);
                _nav_ch_lst_set_list_elmnt(pt_this, ui2_elm_idx, pt_crnt_svl_rec);

                ui2_idx++;
                if (ui2_idx >= ui2_times) {
                    break;
                }
            }
        }

        ui2_elm_idx = b_top_down? (ui2_from_idx + ui2_idx) : (ui2_from_idx - ui2_idx);
        _nav_ch_lst_set_list_elmnt(pt_this, ui2_elm_idx, &t_next_svl_rec);
        ui4_prev_ch_id = CHANNEL_ID(&t_next_svl_rec);
    }

    return TRUE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_validate
 * Description  -
 * Input        -
 * Output       pui2_hlt_elem_idx
 *              pui2_num_recs
 * Returns      -
 *-----------------------------------------------------------------------------*/
static VOID _nav_ch_lst_validate(
                    NAV_CH_LST_T*               pt_this,
                    TV_ITERATE_DIR_T            e_iter_dir,
                    UINT32                      ui4_prev_ch_id,
                    const SVL_REC_T*            pt_next_svl_rec,
                    UINT16*                     pui2_hlt_elem_idx,
                    UINT16*                     pui2_num_recs
                    )
{
    SVL_REC_T t_crnt_svl_rec;
    SVL_REC_T t_next_svl_rec;
    SVL_REC_T t_hlt_svl_rec;
    UINT16    ui2_total_num_of_rec;
    UINT16    ui2_next_idx;
    UINT16    ui2_items_above_next;
    UINT16    ui2_items_below_next;
    UINT16    ui2_null_items_below_last;
    BOOL      b_crnt_is_fake_or_hidden;
    BOOL      b_to_insert_crnt;
    UINT16    ui2_idx;
    INT32     i4_ret;
    UINT16    ui2_first_svl_rec_idx;

    if (pt_next_svl_rec == NULL) {
        _nav_ch_lst_reset_list_elmnts(pt_this);
        return;
    } else {
        c_memcpy(&t_next_svl_rec, pt_next_svl_rec, sizeof(SVL_REC_T));
        c_memcpy(&t_hlt_svl_rec,  pt_next_svl_rec, sizeof(SVL_REC_T));
    }

    /* get current channel's SVL record */
    i4_ret = _nav_ch_lst_get_crnt_svl_rec(pt_this, pt_this->e_focus_tv_win_id, &t_crnt_svl_rec);
    if (i4_ret != NAVR_OK) {
        _nav_ch_lst_reset_list_elmnts(pt_this);
        return;
    }

    /* get total num of channel (non-fake and non-hidden) + current(if it is fake or hidden) */
    if (_nav_ch_lst_get_svl_num_rec(pt_this, &t_crnt_svl_rec, &ui2_total_num_of_rec) == FALSE) {
        _nav_ch_lst_reset_list_elmnts(pt_this);
        return;
    }

    b_crnt_is_fake_or_hidden = IS_FAKE_OR_HIDDEN_SVL_REC(&t_crnt_svl_rec);
    b_to_insert_crnt         = b_crnt_is_fake_or_hidden ? FALSE : TRUE;

    /* correct the "next" SVL_REC_T */
    if (ui2_total_num_of_rec <= MAX_ELEM_OF_CH_LIST) {
        BOOL      b_find_first;
        UINT32    ui4_next_channel_id;

        ui2_next_idx         = 0;
        ui2_items_below_next = (UINT16)(ui2_total_num_of_rec - 1);
        b_find_first = a_tv_mcl_get_svl_rec_by_logic_and_nw_masks(
                            pt_this->h_crnt_svl,
                            a_tv_get_listable_svl_rec_check_nw_mask(),
                            a_tv_get_listable_svl_rec_check_nw_bits(),
                            TV_ITERATE_DIR_FIRST,
                            &ui4_next_channel_id,
                            &t_next_svl_rec
                            );

        /* crnt(fake or hidden) < next or no any one for next */
        if (b_find_first == FALSE) {
            t_next_svl_rec = t_hlt_svl_rec = t_crnt_svl_rec;
        } else {
            /* t_next_svl_rec is first non-fake and non-hidden SVL record */
            if (e_iter_dir == TV_ITERATE_DIR_NEXT) {
                if (b_crnt_is_fake_or_hidden) {
                    if (IS_CH_ID_SMALLER(CHANNEL_ID(&t_crnt_svl_rec), ui4_prev_ch_id)
                            && IS_CH_ID_SMALLER(CHANNEL_ID(&t_crnt_svl_rec), CHANNEL_ID(pt_next_svl_rec))) {
                        /* current is just above pt_next_svl_rec,
                         * correct the hlt to current, and
                         * correct the next = current to pupulate SVL records from current
                         */
                        t_next_svl_rec = t_hlt_svl_rec = t_crnt_svl_rec;
                    }
                }
            } else if (e_iter_dir == TV_ITERATE_DIR_PREV) {
                if (b_crnt_is_fake_or_hidden) {
                    if (CHANNEL_ID(&t_crnt_svl_rec) == ui4_prev_ch_id
                            && IS_CH_ID_SMALLER(ui4_prev_ch_id, CHANNEL_ID(pt_next_svl_rec))) {
                        /* current is just above pt_next_svl_rec and euqal to prev
                         * so correct the next = current to pupulate SVL records from current
                         * and don't change the hlt record.
                         */
                        t_next_svl_rec = t_crnt_svl_rec;
                    } else if (IS_CH_ID_LARGER(CHANNEL_ID(&t_crnt_svl_rec), ui4_prev_ch_id)
                            && IS_CH_ID_LARGER(CHANNEL_ID(&t_crnt_svl_rec), CHANNEL_ID(pt_next_svl_rec))) {
                        /* current is just below pt_next_svl_rec,
                         * correct the hlt to current
                         * and still let it from first record to pupulate SVL records
                         */
                        t_hlt_svl_rec = t_crnt_svl_rec;
                    }
                }
            } else {
                if (b_crnt_is_fake_or_hidden
                        && IS_CH_ID_SMALLER(CHANNEL_ID(&t_crnt_svl_rec), CHANNEL_ID(&t_next_svl_rec))) {
                    t_next_svl_rec = t_crnt_svl_rec;
                }
            }
        }
    } else {
        if (e_iter_dir == TV_ITERATE_DIR_NEXT) {

            if(t_next_svl_rec.ui2_svl_rec_id == pt_this->ui2_first_svl_rec_id)
            {
                ui2_next_idx = 0;
            }
            else
            {
                ui2_next_idx = MAX_ELEM_OF_CH_LIST-1;
            }
            if (b_crnt_is_fake_or_hidden) {
                if (_nav_ch_lst_between(
                            ui4_prev_ch_id,
                            CHANNEL_ID(&t_crnt_svl_rec),
                            CHANNEL_ID(&t_next_svl_rec),
                            TRUE)) {
                    if (_nav_ch_lst_search_svl_rec(
                            pt_this,
                            &t_crnt_svl_rec,
                            NULL
                            ) == FALSE) {
                        t_next_svl_rec = t_hlt_svl_rec = t_crnt_svl_rec;
                    }
                } else if (IS_CH_ID_LARGER(ui4_prev_ch_id, CHANNEL_ID(&t_next_svl_rec))) {
                    /* normal case:    prev < next
                     * exception case: loop-back to first one - prev > next
                     */
                    if (CHANNEL_ID(&t_crnt_svl_rec) != ui4_prev_ch_id) {
                        if (IS_CH_ID_LARGER(CHANNEL_ID(&t_next_svl_rec), CHANNEL_ID(&t_crnt_svl_rec))) {
                            /* crnt != prev && prev > next > crnt */
                            t_next_svl_rec = t_hlt_svl_rec = t_crnt_svl_rec;
                        } else if (IS_CH_ID_LARGER(CHANNEL_ID(&t_crnt_svl_rec), ui4_prev_ch_id)) {
                            /* crnt != prev && crnt > prev > next */
                            t_next_svl_rec = t_hlt_svl_rec = t_crnt_svl_rec;
                        }
                    }
                }
            }
        } else if (e_iter_dir == TV_ITERATE_DIR_PREV) {

            if(t_next_svl_rec.ui2_svl_rec_id == pt_this->ui2_last_svl_rec_id)
            {
                ui2_next_idx = MAX_ELEM_OF_CH_LIST-1;
            }
            else
            {
                ui2_next_idx = 0;
            }

            if (b_crnt_is_fake_or_hidden) {
                if (_nav_ch_lst_between(
                            ui4_prev_ch_id,
                            CHANNEL_ID(&t_crnt_svl_rec),
                            CHANNEL_ID(&t_next_svl_rec),
                            FALSE)) {
                    if (_nav_ch_lst_search_svl_rec(
                            pt_this,
                            &t_crnt_svl_rec,
                            NULL
                            ) == FALSE) {
                        t_next_svl_rec = t_hlt_svl_rec = t_crnt_svl_rec;
                    }
                } else if (IS_CH_ID_SMALLER(ui4_prev_ch_id, CHANNEL_ID(&t_next_svl_rec))) {
                    /* normal case:    prev > next
                     * exception case: loop-back to first one - next > prev
                     */
                    if (CHANNEL_ID(&t_crnt_svl_rec) != ui4_prev_ch_id) {
                        if (IS_CH_ID_LARGER(CHANNEL_ID(&t_crnt_svl_rec), CHANNEL_ID(&t_next_svl_rec))) {
                            /* crnt != prev && crnt > next > prev  */
                            t_next_svl_rec = t_hlt_svl_rec = t_crnt_svl_rec;
                        } else if (IS_CH_ID_LARGER(ui4_prev_ch_id, CHANNEL_ID(&t_crnt_svl_rec))) {
                            /* crnt != prev && next > prev > crnt */
                            t_next_svl_rec = t_hlt_svl_rec = t_crnt_svl_rec;
                        }
                    }
                }
            }
        } else { /* e_iter_dir == this */
            if(pt_this->t_elements[0].ui2_svl_rec_id == pt_this->ui2_first_svl_rec_id)
            {
                if (_nav_ch_lst_search_svl_rec(
                                pt_this,
                                &t_next_svl_rec,
                                &ui2_next_idx
                                ) == FALSE) {
                    ui2_next_idx = pt_this->ui2_focused_idx;
                }
            }
            else if(t_next_svl_rec.ui2_svl_rec_id == pt_this->ui2_first_svl_rec_id)
            {
                ui2_next_idx = 0;
            }
            else
            {
                ui2_next_idx = MAX_ELEM_OF_CH_LIST -1;
            }
        }

        ui2_items_below_next = (UINT16)(MAX_ELEM_OF_CH_LIST - ui2_next_idx - 1);
    }

    ui2_items_above_next      = ui2_next_idx;
    ui2_null_items_below_last = (UINT16)(MAX_ELEM_OF_CH_LIST - (ui2_items_above_next + ui2_items_below_next + 1));

    if (b_to_insert_crnt == FALSE && CHANNEL_ID(&t_next_svl_rec) == CHANNEL_ID(&t_crnt_svl_rec)) {
        b_to_insert_crnt = TRUE;
    }

    _nav_ch_lst_reset_list_elmnts(pt_this);

    /* fill elements above "next" */
    if (ui2_items_above_next > 0) {
        _nav_ch_lst_fill_elements(
                            pt_this,
                            &t_crnt_svl_rec,
                            CHANNEL_ID(&t_next_svl_rec),
                            TV_ITERATE_DIR_PREV,
                            (UINT16)(ui2_next_idx-1),
                            ui2_items_above_next,
                            &b_to_insert_crnt
                            );
    }

    if(_nav_ch_lst_search_first_svl_rec(pt_this,&ui2_first_svl_rec_idx) == TRUE)
    {
        if(ui2_first_svl_rec_idx != 0)
        {
            ui2_next_idx              = ui2_next_idx - ui2_first_svl_rec_idx;
            ui2_items_above_next      = ui2_next_idx;
            ui2_items_below_next      = (UINT16)(MAX_ELEM_OF_CH_LIST - ui2_next_idx - 1);
            ui2_null_items_below_last = (UINT16)(MAX_ELEM_OF_CH_LIST - (ui2_items_above_next + ui2_items_below_next + 1));
            _nav_ch_lst_fill_elements(
                            pt_this,
                            &t_crnt_svl_rec,
                            CHANNEL_ID(&t_next_svl_rec),
                            TV_ITERATE_DIR_PREV,
                            (UINT16)(ui2_next_idx-1),
                            ui2_items_above_next,
                            &b_to_insert_crnt
                            );
        }
    }


    /* fill "next" elements */
    _nav_ch_lst_set_list_elmnt(pt_this, ui2_next_idx, &t_next_svl_rec);

    /* fill elements below "next" */
    if (ui2_items_below_next > 0) {
        _nav_ch_lst_fill_elements(
                            pt_this,
                            &t_crnt_svl_rec,
                            CHANNEL_ID(&t_next_svl_rec),
                            TV_ITERATE_DIR_NEXT,
                            (UINT16)(ui2_next_idx+1),
                            ui2_items_below_next,
                            &b_to_insert_crnt
                            );
    }

    /*check show the arrow indicator or not*/
    if(ui2_total_num_of_rec <= MAX_ELEM_OF_CH_LIST)
    {
        pt_this->ui4_cnt_indctr_state = CNT_INDCTR_MASK_NONE;
    }
    else
    {
        /*up arrow*/
        if(pt_this->t_elements[0].ui2_svl_rec_id != pt_this->ui2_first_svl_rec_id)
        {
            pt_this->ui4_cnt_indctr_state |= CNT_INDCTR_MASK_UP;
        }
        else
        {
            pt_this->ui4_cnt_indctr_state &= ~CNT_INDCTR_MASK_UP;
        }

        /*down arrow*/
        if(pt_this->t_elements[MAX_ELEM_OF_CH_LIST-1].ui2_svl_rec_id != pt_this->ui2_last_svl_rec_id)
        {
            pt_this->ui4_cnt_indctr_state |= CNT_INDCTR_MASK_DOWN;
        }
        else
        {
            pt_this->ui4_cnt_indctr_state &= ~CNT_INDCTR_MASK_DOWN;
        }
    }

    /* fill null elements */
    for (ui2_idx = 1; ui2_idx <= ui2_null_items_below_last; ui2_idx++) {
        _nav_ch_lst_set_list_elmnt(pt_this, ui2_next_idx + ui2_items_below_next + ui2_idx, NULL);
    }

    /* set the output values */
    if (pui2_hlt_elem_idx != NULL) {
        if (_nav_ch_lst_search_svl_rec(
                            pt_this,
                            &t_hlt_svl_rec,
                            pui2_hlt_elem_idx
                            ) == FALSE) {
            *pui2_hlt_elem_idx = 0;
        }
    }

    if (pui2_num_recs != NULL) {
        *pui2_num_recs = ui2_total_num_of_rec;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_update_nav_context
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_update_nav_context(
                    NAV_CH_LST_T*               pt_this,
                    const NAV_CONTEXT_T*        pt_ctx
                    )
{
    /* set current svl*/
    pt_this->e_focus_tv_win_id = pt_ctx->t_svc_res.e_focus_tv_win_id;
    nav_get_svl_handle(pt_this->e_focus_tv_win_id, &pt_this->h_crnt_svl);
    nav_get_svl_id(pt_this->e_focus_tv_win_id, &pt_this->ui2_crnt_svl_id);
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_update_dtl
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_update_dtl(
                    NAV_CH_LST_T*               pt_this,
                    HANDLE_T                    h_crnt_svctx
                    )
{
#undef CH_DETAIL_TEST
#ifdef CH_DETAIL_TEST
    UTF16_T* pw2s_detail = NULL;
    SIZE_T   z_len       = 0;
    INT32    i4_ret      = NAVR_OK;
    CHAR*    ps_detail = "The timeline was one issue that was left unresolved Sunday "
                         "as the World Trade Organization negotiations headed into "
                         "the last day. The European Union had suggested 2013 as a "
                         "possible date to end the subsidies, but Brazil, the "
                         "United States and other countries were pushing for 2010."
                         "The agreement came after six round-the-clock days of "
                         "fractious talks between ministers at a Hong Kong "
                         "harbor-side convention center and often violent "
                         "anti-globalization protests outside. "
                         "The draft, which appears to be a compromise, calles for "
                         "subsidies to be progressively ceased.";

    do {
        z_len = c_strlen(ps_detail);
        pw2s_detail = (UTF16_T*) c_mem_alloc((z_len + 1)* sizeof(UTF16_T));
        if (pw2s_detail == NULL) {
            i4_ret = NAVR_FAIL;
            break;
        }

        i4_ret = c_uc_ps_to_w2s(ps_detail, pw2s_detail, z_len);
        if (i4_ret != UCR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }

        pw2s_detail[z_len] = 0;
        i4_ret = nav_ch_dtl_view_update(
                        &pt_this->t_dtl_view,
                        pw2s_detail,
                        pt_this->t_elements[pt_this->ui2_focused_idx].s_ch_name
                        );
    } while (0);

    if (pw2s_detail != NULL) {
        c_mem_free(pw2s_detail);
    }

    return i4_ret;
#else
    ISO_639_LANG_T  s639_lang;
    ISO_639_LANG_T* ps_detail_639_lang = NULL;
    UTF16_T*        pw2s_detail        = NULL;
    CHAR*           ps_detail          = NULL;
    SIZE_T          z_len              = 0;
    INT32           i4_ret;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if (i4_ret == APP_CFGR_OK) {
        ps_detail_639_lang = &s639_lang;
    }

    do {
        i4_ret = c_svctx_get_current_event_info_len(
                        h_crnt_svctx,
                        EVCTX_KEY_TYPE_SVC_TEXT,
                        (VOID*)ps_detail_639_lang,
                        &z_len
                        );
        if (i4_ret == SVCTXR_EVN_INFO_NOT_FOUND && ps_detail_639_lang != NULL) {
            /* no detail for this language, try to get first one */
            ps_detail_639_lang = NULL;
            i4_ret = c_svctx_get_current_event_info_len(
                        h_crnt_svctx,
                        EVCTX_KEY_TYPE_SVC_TEXT,
                        (VOID*)ps_detail_639_lang,
                        &z_len
                        );
        }
        if (i4_ret != SVCTXR_OK || z_len == 0) {
            break;
        }

        ps_detail = (CHAR*) c_mem_alloc(z_len * sizeof(CHAR));
        if (ps_detail == NULL) {
            ABORT_APPL(DBG_MOD_NAVIGATOR, ("c_mem_alloc(ps_detail) failed - size = %d", z_len));
        }

        pw2s_detail = (UTF16_T*) c_mem_alloc(z_len * sizeof(UTF16_T));
        if (pw2s_detail == NULL) {
            ABORT_APPL(DBG_MOD_NAVIGATOR, ("c_mem_alloc(pw2s_detail) failed - size = %d", z_len));
        }

        i4_ret = c_svctx_get_current_event_info(
                        h_crnt_svctx,
                        EVCTX_KEY_TYPE_SVC_TEXT,
                        (VOID*)ps_detail_639_lang,
                        &z_len,
                        ps_detail
                        );
        if (i4_ret == SVCTXR_OK) {
            i4_ret = c_uc_ps_to_w2s(ps_detail, pw2s_detail, z_len);
            if (i4_ret == UCR_INV_CHAR) {
                DBG_ERROR((_ERROR_HEADER"c_uc_ps_to_w2s(ch detail) failed, ret=UCR_INV_CHAR\r\n"));
                pw2s_detail[0] = 0;
            } else if (i4_ret == UCR_NO_ENOUGH_BUFFER) {
                pw2s_detail[z_len-1] = 0;
            }
        } else {
            DBG_ERROR((_ERROR_HEADER"c_evctx_get_event_info() failed, ret=%d\r\n", i4_ret));
            pw2s_detail[0] = 0;
        }
    } while (0);

    if (pt_this->ui2_focused_idx < MAX_ELEM_OF_CH_LIST) {
        i4_ret = nav_ch_dtl_view_update(
                    &pt_this->t_dtl_view,
                    pw2s_detail,
                    pt_this->t_elements[pt_this->ui2_focused_idx].s_ch_name
                    );
    }

    if (ps_detail != NULL) {
        c_mem_free(ps_detail);
    }

    if (pw2s_detail != NULL) {
        c_mem_free(pw2s_detail);
    }

    return i4_ret;
#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_page_up_dn
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_page_up_dn(
                    NAV_CH_LST_T*               pt_this,
                    BOOL                        b_page_up
                    )
{
    UINT32           ui4_last_ch_id  = INVALID_CHANNEL_ID;
    UINT32           ui4_first_ch_id = INVALID_CHANNEL_ID;
    UINT32           ui4_channel_id  = INVALID_CHANNEL_ID;
    TV_ITERATE_DIR_T e_iter_dir      = TV_ITERATE_DIR_PREV;
    SVL_REC_T        t_crnt_svl_rec  = {0};
    UINT16           ui2_num_recs    = 0;
    UINT16           ui2_hlt_elem_idx= 0;
    INT32            i4_ret;

    i4_ret = nav_get_svl_rec(pt_this->e_focus_tv_win_id, &t_crnt_svl_rec);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (_nav_ch_lst_get_svl_num_rec(pt_this, &t_crnt_svl_rec, &ui2_num_recs) == FALSE) {
        return NAVR_FAIL;
    }

    ui4_last_ch_id  = pt_this->t_elements[MAX_ELEM_OF_CH_LIST-1].ui4_channel_id;
    ui4_first_ch_id = pt_this->t_elements[0].ui4_channel_id;

    if (ui4_last_ch_id == INVALID_CHANNEL_ID || ui4_first_ch_id == INVALID_CHANNEL_ID) {
        return NAVR_FAIL;
    }

    /* Exactly in one page, doesn't support page up/page down */
    if (ui2_num_recs == MAX_ELEM_OF_CH_LIST)
    {
        return NAVR_FAIL;
    }

    if (b_page_up == TRUE) {
        ui4_channel_id   = ui4_first_ch_id;
        ui2_hlt_elem_idx = 0;

        if (pt_this->ui2_focused_idx != ui2_hlt_elem_idx) {
            e_iter_dir = TV_ITERATE_DIR_CRNT;
        } else {
            e_iter_dir = TV_ITERATE_DIR_PREV;
        }
    } else {
        ui4_channel_id   = ui4_last_ch_id;
        ui2_hlt_elem_idx = MAX_ELEM_OF_CH_LIST-1;

        if (pt_this->ui2_focused_idx != ui2_hlt_elem_idx) {
            e_iter_dir = TV_ITERATE_DIR_CRNT;
        } else {
            e_iter_dir = TV_ITERATE_DIR_NEXT;
        }
    }

    i4_ret = _nav_ch_lst_update_lst(
                    pt_this,
                    ui4_channel_id,
                    e_iter_dir,
                    TRUE, /* b_force_hlt */
                    ui2_hlt_elem_idx,
                    TRUE
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    _nav_ch_lst_reset_timer(pt_this);
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_handle_event_update
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_handle_event_update(
                    NAV_CH_LST_T*               pt_this,
                    HANDLE_T                    h_svctx,
                    BOOL                        b_ready
                    )
{
    INT32 i4_ret = NAVR_OK;

    if (b_ready == TRUE) {
        i4_ret = _nav_ch_lst_update_dtl(
                    pt_this,
                    h_svctx
                    );
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
    } else {
        if (pt_this->ui2_focused_idx < MAX_ELEM_OF_CH_LIST) {
            i4_ret = nav_ch_dtl_view_update(
                        &pt_this->t_dtl_view,
                        NULL,
                        pt_this->t_elements[pt_this->ui2_focused_idx].s_ch_name
                        );
            if (i4_ret != NAVR_OK) {
                return i4_ret;
            }
        }
    }

    if (pt_this->b_is_detail_on == TRUE) {
        i4_ret = nav_ch_dtl_view_updn_page(
                    &pt_this->t_dtl_view,
                    CH_DTL_THIS_PAGE,
                    TRUE
                    );
    }
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_handle_ch_change
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_handle_ch_change(
                    NAV_CH_LST_T*               pt_this,
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    INT32 i4_ret;
    #if 0
    SVL_REC_T  t_svl_rec  = {0};
    UINT32     ui4_ver_id = 0;
    #endif

    /*clean channel detail*/
    i4_ret = nav_ch_dtl_view_reset_detail(
                    &pt_this->t_dtl_view,
                    pt_this->b_is_detail_on
                    );

    if (pt_this->b_is_on == FALSE) {
        return NAVR_OK;
    }

    if (pt_this->b_is_list_on == FALSE) {
        return NAVR_OK;
    }

    i4_ret = nav_hide_component(NAV_COMP_ID_CH_LIST);

    return i4_ret;

}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_handle_svl_update
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_handle_svl_update(
                    NAV_CH_LST_T*               pt_this,
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    INT32     i4_ret;
    SVL_REC_T t_svl_rec;
    UINT32    ui4_ver_id;
    UINT32    ui4_channel_id;
    BOOL      b_force_hlt = FALSE;
    UINT16    ui2_hlt_elem_idx = 0;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_OK;
    }

    if (pt_this->b_is_list_on == FALSE) {
        return NAVR_OK;
    }

    if (pt_this->ui2_focused_idx >= MAX_ELEM_OF_CH_LIST) {
        return NAVR_FAIL;
    }

    ui4_channel_id = pt_this->t_elements[pt_this->ui2_focused_idx].ui4_channel_id;

    i4_ret = c_svl_get_rec_by_channel (
                    pt_this->h_crnt_svl,
                    ui4_channel_id,
                    SB_VNET_ALL,
                    0,
                    &t_svl_rec,
                    &ui4_ver_id
                    );
    if (i4_ret != SVLR_OK) {
        ui4_channel_id   = a_util_cnfg_get_crnt_channel_id();
        b_force_hlt      = FALSE;
        ui2_hlt_elem_idx = 0;
    } else {
        b_force_hlt      = TRUE;
        ui2_hlt_elem_idx = pt_this->ui2_focused_idx;
    }

    i4_ret = _nav_ch_lst_update_lst(
                    pt_this,
                    ui4_channel_id,
                    TV_ITERATE_DIR_CRNT,
                    b_force_hlt,      /* b_force_hlt */
                    ui2_hlt_elem_idx,
                    TRUE              /* b_repaint  */
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    _nav_ch_lst_reset_timer(pt_this);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_handle_no_signal
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_handle_no_signal(
                    NAV_CH_LST_T*               pt_this,
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    INT32 i4_ret;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_OK;
    }

    i4_ret = _nav_ch_lst_hide_dtls(pt_this);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_handle_with_signal
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_handle_with_signal(
                    NAV_CH_LST_T*               pt_this,
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    /* Try to insert the fake channnel into normal one if signal is detected. */
    UINT32    ui4_ch_id = a_util_cnfg_get_crnt_channel_id();
    UINT32    ui4_ver_id = SVL_NULL_VER_ID;
    TV_WIN_ID_T  e_tv_win_id = TV_WIN_ID_MAIN;
    SVL_REC_T t_svl_rec;
    ISL_REC_T t_isl_rec;
    HANDLE_T  h_svl;
    INT32     i4_ret;

    /* Get focus win */
    i4_ret = nav_get_focus_id (& e_tv_win_id);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }

    /* Check Focus win is TV */
    i4_ret = nav_get_isl_rec(
                    e_tv_win_id,
                    &t_isl_rec
                    );
    if (i4_ret != TVR_OK) {
        return NAVR_OK;
    }

    if (t_isl_rec.e_src_type != INP_SRC_TYPE_TV) {
        return NAVR_OK;
    }

    i4_ret = nav_get_crnt_svl_handle(&h_svl);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    do {
        i4_ret = c_svl_get_rec_by_channel (
                    h_svl,
                    ui4_ch_id,
                    SB_VNET_ACTIVE,
                    0,
                    &t_svl_rec,
                    &ui4_ver_id
                    );
        if (i4_ret != SVLR_OK) {
            break;
        }

        /* analog channel only */
        if (t_svl_rec.uheader.t_rec_hdr.e_brdcst_type != BRDCST_TYPE_ANALOG)
        {
            break;
        }

        if ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE) == 0){
            break;
        }

        t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask &= ~SB_VNET_FAKE;
        t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask |= (SB_VNET_VISIBLE | SB_VNET_EPG);

        c_svl_lock(h_svl);
        c_svl_update_rec(
                h_svl,
                &t_svl_rec,
                TRUE
                );
        c_svl_unlock(h_svl);

        /* insert successfully, update current channel's SVL record of the window. */
        nav_update_svl_rec (e_tv_win_id);

    } while (0);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_handle_locked
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ch_lst_handle_locked(
                    NAV_CH_LST_T*               pt_this,
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    if (pt_this->b_is_on == FALSE) {
        return NAVR_OK;
    }

#ifndef APP_ONLY_OPERATE_BY_CH_LIST_BTN
    nav_hide_component(NAV_COMP_ID_CH_LIST);
    return NAVR_OK;
#else
    return _nav_ch_lst_hide_dtls(pt_this);
#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_search_svl_rec
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_ch_lst_search_svl_rec(
                    NAV_CH_LST_T*               pt_this,
                    const SVL_REC_T*            pt_svl_rec,
                    UINT16*                     pui2_elem_idx
                    )
{
    UINT16 ui2_idx;

    for (ui2_idx = 0; ui2_idx < MAX_ELEM_OF_CH_LIST; ui2_idx++) {
        if (pt_this->t_elements[ui2_idx].ui2_svl_rec_id == SVL_NULL_REC_ID
            || pt_this->t_elements[ui2_idx].ui2_svl_id != pt_this->ui2_crnt_svl_id
            || pt_this->t_elements[ui2_idx].ui2_svl_rec_id != pt_svl_rec->ui2_svl_rec_id
            || pt_this->t_elements[ui2_idx].ui4_channel_id != pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id) {
            continue;
        }

        if (pui2_elem_idx != NULL) {
            *pui2_elem_idx = ui2_idx;
        }
        return TRUE;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ch_lst_search_svl_rec
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_ch_lst_search_first_svl_rec(
                    NAV_CH_LST_T*               pt_this,
                    UINT16*                     pui2_elem_idx
                    )
{
    UINT16 ui2_idx;

    for (ui2_idx = 0; ui2_idx < MAX_ELEM_OF_CH_LIST; ui2_idx++)
    {
        if (pt_this->t_elements[ui2_idx].ui2_svl_rec_id != pt_this->ui2_first_svl_rec_id)
        {
            continue;
        }

        if (pui2_elem_idx != NULL) {
            *pui2_elem_idx = ui2_idx;
        }
        return TRUE;
    }
    return FALSE;
}


/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_rcu_key_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
VOID nav_ch_lst_rcu_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    NAV_CH_LST_T* pt_this = &t_g_ch_lst;
    SVL_REC_T     t_crnt_svl_rec;
    SVL_REC_T     t_svl_rec;
    UINT32        ui4_ver_id;
    INT32         i4_ret;

    i4_ret = nav_get_svl_rec(pt_this->e_focus_tv_win_id, &t_crnt_svl_rec);
    if (i4_ret != NAVR_OK) {

        /* current svl record could not be retrieved. */
        if (nav_is_allow_dup_ch_num())
        {
            /* OK for this condition. */
        }
        else
        {
            return;
        }
    }

    nav_ch_lst_custom_rcu_key_pre_handler(&ui4_key_code);

    switch(ui4_key_code) {
    case BTN_CURSOR_LEFT:
        if (pt_this->b_is_detail_on == TRUE) {
            i4_ret = nav_ch_dtl_view_updn_page(
                        &pt_this->t_dtl_view,
                        CH_DTL_PREV_PAGE,
                        TRUE
                        );
            if (i4_ret == NAVR_OK) {
                _nav_ch_lst_reset_timer(pt_this);
            }
        }
        break;
    case BTN_CURSOR_RIGHT:
        if (pt_this->b_is_detail_on == TRUE) {
            i4_ret = nav_ch_dtl_view_updn_page(
                        &pt_this->t_dtl_view,
                        CH_DTL_NEXT_PAGE,
                        TRUE
                        );
            if (i4_ret == NAVR_OK) {
                _nav_ch_lst_reset_timer(pt_this);
            }
        }
        break;
    case BTN_SELECT:
      {
        if (pt_this->ui2_focused_idx < MAX_ELEM_OF_CH_LIST &&
                pt_this->t_elements[pt_this->ui2_focused_idx].ui2_svl_rec_id != SVL_NULL_REC_ID) {

            if (nav_is_same_channel(
                        pt_this->ui2_crnt_svl_id,
                        t_crnt_svl_rec.ui2_svl_rec_id,
                        t_crnt_svl_rec.uheader.t_rec_hdr.ui4_channel_id,
                        pt_this->t_elements[pt_this->ui2_focused_idx].ui2_svl_id,
                        pt_this->t_elements[pt_this->ui2_focused_idx].ui2_svl_rec_id,
                        pt_this->t_elements[pt_this->ui2_focused_idx].ui4_channel_id) == FALSE) {

                i4_ret = c_svl_get_rec_by_channel(
                            pt_this->h_crnt_svl,
                            pt_this->t_elements[pt_this->ui2_focused_idx].ui4_channel_id,
                            SB_VNET_ALL,
                            0,
                            &t_svl_rec,
                            &ui4_ver_id
                            );
                if (i4_ret != SVLR_OK) {
                    break;
                }
                i4_ret = nav_change_channel_by_rec(
                            pt_this->e_focus_tv_win_id,
                            &t_svl_rec,
                            NULL
                            );
            }
            else
            {
                nav_hide_component(NAV_COMP_ID_CH_LIST);

                nav_dispatch_msg_to_component(
                                    NAV_COMP_ID_BANNER,
                                    NAV_UI_MSG_SHOW_BANNER,
                                    NULL
                                    );
                break;
            }
        }

        _nav_ch_lst_reset_timer(pt_this);
        break;
      }
    case CUSTOM_BTN_CH_LST_PG_UP:
        _nav_ch_lst_page_up_dn(pt_this, TRUE);
        break;
    case CUSTOM_BTN_CH_LST_PG_DN:
        _nav_ch_lst_page_up_dn(pt_this, FALSE);
        break;
    case BTN_CH_LIST:
        nav_hide_component(NAV_COMP_ID_CH_LIST);
        break;

    case BTN_YELLOW:

        /* If Multiple channel list feature is supported, when pressing yellow key,
           switch to channel list selection component */

        if (pt_this->b_is_support_multiple_channel_list)
        {
            nav_grab_activation (NAV_COMP_ID_CH_LIST_SELECTION);
        }
        break;
    case BTN_BLUE:
        /* Priority is higher than multiple channel list */
        if (pt_this->b_is_support_satellite_selection && nav_ch_lst_is_under_satellite_mode())
        {
            nav_grab_activation (NAV_COMP_ID_SATELLITE_SELECTION);
            break;
        }


        if (pt_this->b_is_support_multiple_channel_list)
        {
            nav_hide_component(NAV_COMP_ID_CH_LIST);
            break;
        }
        break;

    default:
        /* channel number sub component key handler */
        if (ch_number_is_key_handler(pt_this->e_focus_tv_win_id,ui4_key_code))
        {
            if (nav_is_component_visible(NAV_COMP_ID_CH_LIST))
            {
                nav_hide_component(NAV_COMP_ID_CH_LIST);
            }

            ch_number_activate(pt_this->e_focus_tv_win_id,ui4_key_code);
        }
        else
        {
            nav_rcu_key_handler(ui4_key_code);
        }
        break;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_do_elem_hlt
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
VOID nav_ch_lst_do_elem_hlt(
                    NAV_CH_LST_T*               pt_this,
                    UINT16                      ui2_hlt_idx
                    )
{
    SVL_REC_T t_crnt_svl_rec;
    INT32     i4_ret;

    i4_ret = nav_get_svl_rec(pt_this->e_focus_tv_win_id, &t_crnt_svl_rec);
    if (i4_ret != NAVR_OK) {
        return;
    }

    do {
        pt_this->ui2_focused_idx = ui2_hlt_idx;

        /* close channel detail if highted element is not current channel */
        if (nav_is_same_channel(
                    pt_this->ui2_crnt_svl_id,
                    t_crnt_svl_rec.ui2_svl_rec_id,
                    t_crnt_svl_rec.uheader.t_rec_hdr.ui4_channel_id,
                    pt_this->t_elements[pt_this->ui2_focused_idx].ui2_svl_id,
                    pt_this->t_elements[pt_this->ui2_focused_idx].ui2_svl_rec_id,
                    pt_this->t_elements[pt_this->ui2_focused_idx].ui4_channel_id) == TRUE) {
            break;
        }

        _nav_ch_lst_hide_dtls(pt_this);
    } while (0);

    _nav_ch_lst_reset_timer(pt_this);
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_do_reach_top
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
VOID nav_ch_lst_do_reach_top(
                    NAV_CH_LST_T*               pt_this
                    )
{
    if (pt_this->ui2_focused_idx < MAX_ELEM_OF_CH_LIST) {
        _nav_ch_lst_update_lst(
                    pt_this,
                    pt_this->t_elements[pt_this->ui2_focused_idx].ui4_channel_id,
                    TV_ITERATE_DIR_PREV,
                    FALSE, /* b_force_hlt */
                    0,
                    TRUE
                    );
    }

    /* don't need to reset timer, in do_elem_hlt, it will be reset */
     _nav_ch_lst_reset_timer(pt_this);
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_do_reach_bottom
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
VOID nav_ch_lst_do_reach_bottom(
                    NAV_CH_LST_T*               pt_this
                    )
{
    if (pt_this->ui2_focused_idx < MAX_ELEM_OF_CH_LIST) {
        _nav_ch_lst_update_lst(
                    pt_this,
                    pt_this->t_elements[pt_this->ui2_focused_idx].ui4_channel_id,
                    TV_ITERATE_DIR_NEXT,
                    FALSE, /* b_force_hlt */
                    0,
                    TRUE
                    );
    }

    /* don't need to reset timer, in do_elem_hlt, it will be reset */
    _nav_ch_lst_reset_timer(pt_this);
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ch_lst_is_under_satellite_mode
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
BOOL  nav_ch_lst_is_under_satellite_mode(VOID)
{
    UINT16 ui2_svl_id = 0;
    INT32 i4_ret;
    /* This function only applies in Satellite channel list only. */
    i4_ret = a_tv_get_svl_id(& ui2_svl_id);
    if (i4_ret < 0)
    {
        return FALSE;
    }
    if (ui2_svl_id != LST_SAT_SVL_ID)
    {
        return FALSE;
    }

    return TRUE;
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_ch_lst_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_ch_lst_register(
                    VOID
                    )
{
    NAV_COMP_EX_T t_comp;
    INT32      i4_ret;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    t_comp.pf_init           = _nav_ch_lst_init;
    t_comp.pf_deinit         = _nav_ch_lst_deinit;
    #if 0
    t_comp.pf_is_key_handler = _nav_ch_lst_is_key_handler;
    #else
    t_comp.pf_is_key_handler_ex = _nav_ch_lst_is_key_handler_ex;
    #endif
    t_comp.pf_activate       = _nav_ch_lst_activate;
    t_comp.pf_inactivate     = _nav_ch_lst_inactivate;
    t_comp.pf_hide           = _nav_ch_lst_hide;
    t_comp.pf_handle_msg     = _nav_ch_lst_handle_msg;

    #if 0
    i4_ret = nav_register_component(NAV_COMP_ID_CH_LIST, &t_comp, COMP_EXC_SET_CH_LST);
    #else
    i4_ret = nav_register_component_ex(NAV_COMP_ID_CH_LIST, &t_comp, COMP_EXC_SET_CH_LST);
    #endif
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"nav_register_component(NAV_COMP_ID_CH_LIST) failed\r\n"));
        return i4_ret;
    }

    return NAVR_OK;
}
