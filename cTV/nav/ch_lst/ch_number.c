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
 * $RCSfile: ch_number.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor:  $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *  b_is_for_major_ch
 *  b_ch_num_input_processing
 *---------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_sb.h"

#include "c_handle.h"
#include "c_wgl.h"

#include "app_util/a_cfg.h"
#include "app_util/a_ctrl_panel.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "nav/ch_lst/ch_number.h"
#include "nav/sys_info/a_sys_info.h"
#include "nav/banner2/banner_common.h"
#include "nav/input_src/input_src_list.h"
#include "res/nav/one_channel_list/ocl.h"
#include "res/app_util/config/acfg_custom.h"

#include "menu2/a_menu.h"
#include "res/menu2/menu_custom.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define MAX_CH_DIGITS                   (5)

#ifdef SB_VNET_NUMERIC_SELECTABLE
    #define _DIRECT_SELECTABLE_SB_VNET  (SB_VNET_NUMERIC_SELECTABLE)
#else
    #define _DIRECT_SELECTABLE_SB_VNET  (0)
#endif


#ifdef APP_DVBT_SUPPORT

    #ifndef APP_DVBC_SUPPORT
        #define MAX_DIGIT_OF_AIR_MAJOR_CH    (4) /* DVBT */
        #define MAX_DIGIT_OF_CAB_MAJOR_CH    (4) /* DVBT for one-part */
        #define MAX_MAJOR_MINOR_CHAR_SIZE    (4) /* DVBT for displaying */
    #else
        #define MAX_DIGIT_OF_AIR_MAJOR_CH    (4) /* DVBC */
        #define MAX_DIGIT_OF_CAB_MAJOR_CH    (4) /* DVBC for one-part */
        #define MAX_MAJOR_MINOR_CHAR_SIZE    (5) /* DVBT for displaying */
    #endif

    #define MAX_DIGIT_OF_CAB_2P_MAJOR_CH (4) /* for two-part */
    #define MAX_DIGIT_OF_MINOR_CH        (0)
    #define MAX_DIGIT_OF_CHANNEL_NUM     (4)

    /* Active + non-fake */
    #define _DIRECT_INPUT_PRIORITY_1_CHECK_MASK (SB_VNET_ACTIVE | SB_VNET_FAKE)
    #define _DIRECT_INPUT_PRIORITY_1_CHECK_BITS (SB_VNET_ACTIVE)

    /* Active */
    #define _DIRECT_INPUT_PRIORITY_2_CHECK_MASK (SB_VNET_ACTIVE)
    #define _DIRECT_INPUT_PRIORITY_2_CHECK_BITS (SB_VNET_ACTIVE)

    /* Numeric selectable */
    #define _DIRECT_INPUT_PRIORITY_3_CHECK_MASK (_DIRECT_SELECTABLE_SB_VNET)
    #define _DIRECT_INPUT_PRIORITY_3_CHECK_BITS (_DIRECT_SELECTABLE_SB_VNET)

#elif defined(APP_ISDB_BRA_VIRTUAL_CHANNEL)
    #define MAX_DIGIT_OF_AIR_MAJOR_CH    (2)
    #define MAX_DIGIT_OF_CAB_MAJOR_CH    (3) /* for one-part */
    #define MAX_DIGIT_OF_CAB_2P_MAJOR_CH (0) /* for two-part */
    #define MAX_DIGIT_OF_CAB_MINOR_CH    (0) /* for cable */
    #define MAX_DIGIT_OF_MINOR_CH        (2) /* for air*/
    #define MAX_DIGIT_OF_CHANNEL_NUM     (4)
    #define MAX_MAJOR_MINOR_CHAR_SIZE    (8)

    /* Active + non-fake */
    #define _DIRECT_INPUT_PRIORITY_1_CHECK_MASK (SB_VNET_ACTIVE | SB_VNET_FAKE)
    #define _DIRECT_INPUT_PRIORITY_1_CHECK_BITS (SB_VNET_ACTIVE)

    /* Active */
    #define _DIRECT_INPUT_PRIORITY_2_CHECK_MASK (SB_VNET_ACTIVE)
    #define _DIRECT_INPUT_PRIORITY_2_CHECK_BITS (SB_VNET_ACTIVE)

    #define _DIRECT_INPUT_PRIORITY_3_CHECK_MASK (0)  /* Not used */
    #define _DIRECT_INPUT_PRIORITY_3_CHECK_BITS (0)

#else /* ATSC */
    #define MAX_DIGIT_OF_AIR_MAJOR_CH    (3)
    #define MAX_DIGIT_OF_CAB_MAJOR_CH    (5) /* for one-part */
    #define MAX_DIGIT_OF_CAB_2P_MAJOR_CH (3) /* for two-part */
    #define MAX_DIGIT_OF_MINOR_CH        (5)
    #define MAX_DIGIT_OF_CHANNEL_NUM     (8)
    #define MAX_MAJOR_MINOR_CHAR_SIZE    (12)

    #define _DIRECT_INPUT_PRIORITY_1_CHECK_MASK (SB_VNET_ACTIVE | SB_VNET_FAKE)
    #define _DIRECT_INPUT_PRIORITY_1_CHECK_BITS (SB_VNET_ACTIVE)

    /* Active */
    #define _DIRECT_INPUT_PRIORITY_2_CHECK_MASK (0)  /* Not used */
    #define _DIRECT_INPUT_PRIORITY_2_CHECK_BITS (0)

    #define _DIRECT_INPUT_PRIORITY_3_CHECK_MASK (0)  /* Not used */
    #define _DIRECT_INPUT_PRIORITY_3_CHECK_BITS (0)

#endif

typedef struct _CH_NUMBER_T
{
    TV_WIN_ID_T               e_focus;
    HANDLE_T                  h_hide_timer;

    UINT32                    ui4_major_ch_digits;
    UINT32                    ui4_minor_ch_digits;
    UINT32                    ui4_max_major_ch_digits;
    UINT32                    ui4_max_minor_ch_digits;
    UINT32                    ui4_timeout;

    BOOL                      b_is_active;
    BOOL                      b_ch_num_input_processing;
    BOOL                      b_is_for_major_ch;
} CH_NUMBER_T;

typedef enum
{
    CH_MATCH_TYPE_ONE_PART = 0,
    CH_MATCH_TYPE_TWO_PART,
    CH_MATCH_TYPE_NON_PSIP_TWO_PART
} CH_MATCH_TYPE_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static CH_NUMBER_T t_g_ch_number;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _ch_number_num_key_handler (
                    CH_NUMBER_T*                pt_this,
                    TV_WIN_ID_T                 e_grp,
                    UINT32                      ui4_key_code
                    );
static VOID _ch_number_reset_input_status(
                    CH_NUMBER_T*                pt_this
                    );
static INT32 _ch_number_get_first_channel(
                    HANDLE_T                    h_crnt_svl,
                    UINT32*                     pui4_channel_id,
                    SVL_REC_T*                  pt_svl_rec
                    );
static INT32 _ch_number_ok_key_handler (
                    CH_NUMBER_T*                pt_this,
                    TV_WIN_ID_T                 e_grp,
                    UINT32                      ui4_key_code
                    );
static VOID _ch_number_stop_timer(
                    CH_NUMBER_T*                pt_this
                    );
static VOID _ch_number_reset_timer(
                    CH_NUMBER_T*                pt_this,
                    TV_WIN_ID_T                 e_grp
                    );
static VOID _ch_number_do_timeout (
                    VOID*                       pv_grp,
                    VOID*                       pv_unused1,
                    VOID*                       pv_unused2
                    );
static VOID _ch_number_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_grp
                    );
static INT32 _ch_number_config_chdt(
                    CH_NUMBER_T*                pt_this,
                    UINT16                      ui2_svl_id
                    );
static BOOL _ch_number_is_able_to_handle_number_key(
                    TV_WIN_ID_T                 e_focus_id
                    );

/*key*/
static INT32 _ch_number_key_handler(
                    CH_NUMBER_T*                pt_this,
                    TV_WIN_ID_T                 e_grp,
                    UINT32                      ui4_key_code
                    );

static INT32 _ch_number_cancel_input(VOID);
static INT32 _ch_number_get_matched_channel (
                    HANDLE_T                    h_svl,
                    CH_MATCH_TYPE_T             e_match_type,
                    UINT32                      ui4_major_ch_num,
                    UINT32                      ui4_minor_ch_num,
                    SVL_REC_T*                  pt_svl_rec
                    );
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

INT32 ch_number_get_matched_channel (
                    HANDLE_T                    h_svl,
                    BOOL                        b_major_only,
                    UINT32                      ui4_major_ch_num,
                    UINT32                      ui4_minor_ch_num,
                    SVL_REC_T*                  pt_svl_rec
                    )
{
    INT32 i4_ret;
    UINT32 ui4_channel_id;

    if(pt_svl_rec == NULL)
    {
        return NAVR_INV_ARG;
    }

    if (b_major_only && ui4_minor_ch_num == 0)
    {
        /* try to find one-part channel*/
        i4_ret = _ch_number_get_matched_channel (
                        h_svl,
                        CH_MATCH_TYPE_ONE_PART,
                        ui4_major_ch_num,
                        ui4_minor_ch_num,
                        pt_svl_rec
                        );

        if (i4_ret != NAVR_OK)
        {
            /* try to find two-part channel*/
            i4_ret = _ch_number_get_matched_channel (
                        h_svl,
                        CH_MATCH_TYPE_TWO_PART,
                        ui4_major_ch_num,
                        ui4_minor_ch_num,
                        pt_svl_rec
                        );
        }

        if (i4_ret != NAVR_OK)
        {
            /* try to find non-PISP channel*/
            i4_ret = _ch_number_get_matched_channel (
                        h_svl,
                        CH_MATCH_TYPE_NON_PSIP_TWO_PART,
                        ui4_major_ch_num,
                        ui4_minor_ch_num,
                        pt_svl_rec
                        );
        }
    }
    else
    {
        /* try to find two-part channel*/
        i4_ret = _ch_number_get_matched_channel (
                        h_svl,
                        CH_MATCH_TYPE_TWO_PART,
                        ui4_major_ch_num,
                        ui4_minor_ch_num,
                        pt_svl_rec
                        );

        if (i4_ret != NAVR_OK)
        {
            /* try to find non-PISP channel*/
            i4_ret = _ch_number_get_matched_channel (
                        h_svl,
                        CH_MATCH_TYPE_NON_PSIP_TWO_PART,
                        ui4_major_ch_num,
                        ui4_minor_ch_num,
                        pt_svl_rec
                        );
        }

        if (i4_ret != NAVR_OK && ui4_minor_ch_num == 0)
        {
            /* try to find two-part channel*/
            i4_ret = _ch_number_get_matched_channel (
                        h_svl,
                        CH_MATCH_TYPE_ONE_PART,
                        ui4_major_ch_num,
                        ui4_minor_ch_num,
                        pt_svl_rec
                        );
        }
    }

    /* The system allow duplicated major number, the above function are correctly filtered,
       no more check needed. */
    if (nav_is_allow_dup_ch_num() && i4_ret != NAVR_OK)
    {
        return NAVR_INVALID_CH_ID;
    }

    if (i4_ret != NAVR_OK)
    {
        if (ui4_minor_ch_num == 0)
        {
            ui4_channel_id = SB_ATSC_GEN_ONE_PART_CHANNEL_ID(ui4_major_ch_num, 0);
        }
        else
        {
            ui4_channel_id = SB_ATSC_GEN_CHANNEL_ID(ui4_major_ch_num, ui4_minor_ch_num, 0);
        }

        i4_ret = _ch_number_get_first_channel(
                        h_svl,
                        &ui4_channel_id,
                        pt_svl_rec
                        );
        if (i4_ret != NAVR_OK)
        {
            return NAVR_INVALID_CH_ID;
        }
    }

    return NAVR_OK;


}

/*-----------------------------------------------------------------------------
 * Name
 *      a_ch_number_is_keying_ch
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_ch_number_is_keying_ch(
    BOOL*                       pt_is_keying)
{
    if(NULL == pt_is_keying)
    {
        return NAVR_INV_ARG;
    }

    *pt_is_keying = t_g_ch_number.b_ch_num_input_processing;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      ch_number_rcu_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID ch_number_rcu_key_handler (
                    UINT32                      ui4_key_code
                    )
{
    CH_NUMBER_T* pt_this = &t_g_ch_number;

    _ch_number_key_handler(pt_this, pt_this->e_focus, ui4_key_code);
}

/*-----------------------------------------------------------------------------
 * Name
 *      ch_number_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 ch_number_init(VOID)
{
    CH_NUMBER_T* pt_this = &t_g_ch_number;
    INT32        i4_ret;
    UINT16       ui2_svl_id;
    CHAR         *ps_src_name;

    c_memset(pt_this, 0, sizeof(CH_NUMBER_T));

    pt_this->b_is_active = FALSE;
    pt_this->b_is_for_major_ch = TRUE;
    pt_this->ui4_major_ch_digits = SI_INVALID_CHANNEL_NUMBER;
    pt_this->ui4_minor_ch_digits = SI_INVALID_CHANNEL_NUMBER;
    pt_this->ui4_timeout       = CH_CHANGE_TIMER_DELAY;
    pt_this->e_focus           = TV_WIN_ID_MAIN;

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_svl_id, &ps_src_name);
    if (i4_ret != APP_CFGR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = _ch_number_config_chdt(pt_this, ui2_svl_id);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      ch_number_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 ch_number_deinit(
                    VOID
                    )
{
    CH_NUMBER_T* pt_this = &t_g_ch_number;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE)
    {
        c_timer_delete(pt_this->h_hide_timer);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      ch_number_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 ch_number_activate(
                    TV_WIN_ID_T                 e_focus_id,
                    UINT32                      ui4_key_code
                    )
{
    CH_NUMBER_T* pt_this = &t_g_ch_number;

    pt_this->b_is_active = TRUE;
    pt_this->e_focus = e_focus_id;
    _ch_number_key_handler(pt_this, pt_this->e_focus, ui4_key_code);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      ch_number_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 ch_number_inactivate(VOID)
{
    CH_NUMBER_T* pt_this = &t_g_ch_number;

    _ch_number_cancel_input();
    _ch_number_reset_input_status(pt_this);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      ch_number_is_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL ch_number_is_activate(VOID)
{
    CH_NUMBER_T* pt_this = &t_g_ch_number;

    return (pt_this->b_is_active);
}

/*-----------------------------------------------------------------------------
 * Name
 *      ch_number_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID ch_number_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    CH_NUMBER_T* pt_this = &t_g_ch_number;
    TV_WIN_ID_T  e_tv_win_id;
    INT32        i4_ret;

    switch(pt_ui_msg->e_id)
    {
    case NAV_UI_MSG_TV_SRC_CHANGED:
        _ch_number_config_chdt(pt_this, (UINT16)(UINT32)pv_arg1);
        break;
    case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        _ch_number_cancel_input();
        _ch_number_reset_input_status(pt_this);
        break;

    case NAV_UI_MSG_APP_PAUSING:
        _ch_number_cancel_input();
        _ch_number_reset_input_status(pt_this);
        break;

    case NAV_UI_MSG_AFTER_SVC_CHANGE:
        {
            _ch_number_cancel_input();
            _ch_number_reset_input_status(pt_this);
        }
        break;

    case NAV_UI_MSG_APP_PRE_RESUME:
        i4_ret = nav_get_focus_id(&e_tv_win_id);
        if ((i4_ret == NAVR_OK) &&
            (nav_is_svl_empty(e_tv_win_id) || nav_is_specified_ch_lst_empty(e_tv_win_id)))
        {
            _ch_number_cancel_input();
            _ch_number_reset_input_status(pt_this);
            //ch_banner_view_empty(&pt_this->t_view, pt_this->b_is_on);
        }
        break;

    case NAV_UI_MSG_LOCKED_INP:
    case NAV_UI_MSG_EMPTY_SVL:
    case NAV_UI_MSG_EMPTY_SPECIFIED_CH_LIST:
        _ch_number_cancel_input();
        _ch_number_reset_input_status(pt_this);
        //ch_banner_view_empty(&pt_this->t_view, pt_this->b_is_on);
        break;

    case NAV_UI_MSG_LOCKED_PROG:
    case NAV_UI_MSG_LOCKED_CH:
        _ch_number_cancel_input();
        _ch_number_reset_input_status(pt_this);
        break;

    case NAV_UI_MSG_FOCUS_CHANGED:
        {
            _ch_number_cancel_input();
            _ch_number_reset_input_status(pt_this);
            pt_this->e_focus = (TV_WIN_ID_T)(INT32)pv_arg1;
        }
        break;
    default:
        break;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      ch_number_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL ch_number_is_key_handler(
                    TV_WIN_ID_T                 e_focus_id,
                    UINT32                      ui4_key_code
                    )
{
    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_CH_CHANGE) == TRUE)
    {
        return FALSE;
    }

    switch(ui4_key_code)
    {
    case BTN_DIGIT_0:
    case BTN_DIGIT_1: case BTN_DIGIT_2: case BTN_DIGIT_3:
    case BTN_DIGIT_4: case BTN_DIGIT_5: case BTN_DIGIT_6:
    case BTN_DIGIT_7: case BTN_DIGIT_8: case BTN_DIGIT_9:

        return _ch_number_is_able_to_handle_number_key(e_focus_id);
    default:
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static INT32 _ch_number_cancel_input(VOID)
{
    SI_SET_INFO_T t_set_info;
    CH_NUMBER_T* pt_this = &t_g_ch_number;

    if (pt_this->b_ch_num_input_processing)
    {
        t_set_info.e_category = SI_CATEGORY_CH_NUM_INFO;
        t_set_info.u.t_ch_num_info.ui4_info_mask = SI_CH_NUM_INFO_MASK_INPUT | SI_CH_NUM_INFO_MASK_RESULT;
        t_set_info.u.t_ch_num_info.t_ch_input.b_is_ch_inputing = FALSE;
        t_set_info.u.t_ch_num_info.t_ch_input.b_is_inputing_major = pt_this->b_is_for_major_ch;
        t_set_info.u.t_ch_num_info.t_ch_input.ui4_major_chn_num = pt_this->ui4_major_ch_digits;
        t_set_info.u.t_ch_num_info.t_ch_input.ui4_minor_chn_num = pt_this->ui4_minor_ch_digits;
        t_set_info.u.t_ch_num_info.e_result = SI_CH_NUM_INFO_RESULT_CANCEL;
        a_si_set_item_info_for_once_by_win_id(pt_this->e_focus,&t_set_info);

        /* unset channel number */
        a_si_unset_item_info_by_win_id (pt_this->e_focus,&t_set_info);
    }

    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_config_chdt
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _ch_number_config_chdt(
                    CH_NUMBER_T*                pt_this,
                    UINT16                      ui2_svl_id
                    )
{
    switch (ui2_svl_id)
    {
    case ATSC_CABLE_SVL_ID:
        pt_this->ui4_max_major_ch_digits = MAX_DIGIT_OF_CAB_MAJOR_CH;
#ifdef APP_ISDB_BRA_VIRTUAL_CHANNEL
        pt_this->ui4_max_minor_ch_digits = MAX_DIGIT_OF_CAB_MINOR_CH;
#else
        pt_this->ui4_max_minor_ch_digits = MAX_DIGIT_OF_MINOR_CH;
#endif
        break;
    case ATSC_TRSTRL_SVL_ID:
    default:
        pt_this->ui4_max_major_ch_digits = MAX_DIGIT_OF_AIR_MAJOR_CH;
        pt_this->ui4_max_minor_ch_digits = MAX_DIGIT_OF_MINOR_CH;
        break;
    }

    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_get_crnt_num_of_digit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UINT8 _ch_number_get_crnt_num_of_digit(UINT32 ui4_ch_digits,UINT32 *pui4_highest_value)
{

    UINT8 ui1_digits_num = 1;
    UINT32 ui4_highest_value = 1;

    if (ui4_ch_digits == SI_INVALID_CHANNEL_NUMBER)
    {
        ui1_digits_num  = 0;
    }
    else if (ui4_ch_digits == 0)
    {
        ui1_digits_num = 1;
    }
    else
    {
        while(ui4_ch_digits / 10)
        {
            ui1_digits_num++;
            ui4_highest_value *= 10;

            ui4_ch_digits /= 10;
        }
    }

    if (pui4_highest_value)
    {
        *pui4_highest_value = ui4_highest_value;
    }

    return ui1_digits_num;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_update_ch_digit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _ch_number_update_ch_digit(UINT32 *pui4_ch_digits,
                                       UINT32 ui4_max_digits_num,
                                       UINT32 ui4_key_num)
{
    UINT8 ui1_digits_crnt_num;
    UINT32 ui4_ch_digits;
    UINT32 ui4_highest_value;

    if (pui4_ch_digits == NULL)
    {
        return;
    }

    ui4_ch_digits = *pui4_ch_digits;

    if (ui4_ch_digits == SI_INVALID_CHANNEL_NUMBER)
    {
        *pui4_ch_digits = ui4_key_num;

        return;
    }

    ui1_digits_crnt_num = _ch_number_get_crnt_num_of_digit(ui4_ch_digits,&ui4_highest_value);

    if (ui1_digits_crnt_num > ui4_max_digits_num)
    {
        return;
    }

    if (ui1_digits_crnt_num < ui4_max_digits_num)
    {
        *pui4_ch_digits = (ui4_ch_digits * 10) + ui4_key_num;
    }
    else
    {
        *pui4_ch_digits = (ui4_ch_digits % ui4_highest_value) * 10 + ui4_key_num;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_is_able_to_handle_number_key
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _ch_number_is_able_to_handle_number_key(
                    TV_WIN_ID_T                 e_focus_id
                    )
{
    TV_MODE_T e_tv_mode;
    INT32     i4_ret;

    /* current input source = TV */
    if (nav_get_src_type(e_focus_id) == INP_SRC_TYPE_TV)
    {
        if (nav_get_locked_status(e_focus_id) == LOCKED_STATUS_INP_SRC_LOCKED ||
            nav_is_svl_empty(e_focus_id) ||
            nav_is_specified_ch_lst_empty(e_focus_id))
        {
            return FALSE;
        }
    }
    else
    {
#ifdef APP_NAV_SUPPORT_NUM_KEY_CHANNEL_CHANGE_ONLY_IN_TV_SOURCE
        return FALSE;
#endif
        /* current input source = AV */
        i4_ret = nav_get_tv_mode(&e_tv_mode);
        if (i4_ret != NAVR_OK)
        {
            return FALSE;
        }

        if (e_tv_mode == TV_MODE_TYPE_PIP || e_tv_mode == TV_MODE_TYPE_POP)
        {
#ifdef APP_NAV_PIP_POP_CH_CHANGE_IN_AV
            TV_WIN_ID_T e_blur_id = NAV_GET_BLUR_ID(e_focus_id);
            ISL_REC_T   t_tv_src_rec;
            ISL_REC_T   t_blur_rec;
            BOOL        b_is_same_grp;

            i4_ret = a_tv_get_isl_rec_by_win_id(e_blur_id, &t_blur_rec);
            if (i4_ret != TVR_OK)
            {
                return FALSE;
            }

            i4_ret = a_tv_get_first_input_src_id_by_type(INP_SRC_TYPE_TV, &t_tv_src_rec);
            if (i4_ret != TVR_OK)
            {
                return FALSE;
            }

            i4_ret = a_isl_is_same_group(&t_blur_rec, &t_tv_src_rec, &b_is_same_grp);
            if (i4_ret != ISLR_OK)
            {
                return FALSE;
            }

            if (b_is_same_grp == TRUE)
            {
                return FALSE;
            }
#else
            return FALSE;
#endif
        }
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_num_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _ch_number_num_key_handler (
                    CH_NUMBER_T*                pt_this,
                    TV_WIN_ID_T                 e_grp,
                    UINT32                      ui4_key_code
                    )
{
    UINT32  ui4_key_number = ui4_key_code - BTN_DIGIT_0;
    SI_SET_INFO_T t_set_info;

    _ch_number_reset_timer(pt_this, e_grp);

    if ((BTN_DIGIT_DOT != ui4_key_code) && (BTN_KB_MINUS_SIGN != ui4_key_code))
    {
        if (pt_this->b_is_for_major_ch == TRUE)
        {
            _ch_number_update_ch_digit(&pt_this->ui4_major_ch_digits, pt_this->ui4_max_major_ch_digits, ui4_key_number);
        }
        else
        {
            _ch_number_update_ch_digit(&pt_this->ui4_minor_ch_digits, pt_this->ui4_max_minor_ch_digits, ui4_key_number);
        }
    }

    pt_this->b_ch_num_input_processing = TRUE;

    t_set_info.e_category = SI_CATEGORY_CH_NUM_INFO;
    t_set_info.u.t_ch_num_info.ui4_info_mask = SI_CH_NUM_INFO_MASK_INPUT;
    t_set_info.u.t_ch_num_info.t_ch_input.b_is_ch_inputing = TRUE;
    t_set_info.u.t_ch_num_info.t_ch_input.b_is_inputing_major = pt_this->b_is_for_major_ch;
    t_set_info.u.t_ch_num_info.t_ch_input.ui4_major_chn_num = pt_this->ui4_major_ch_digits;
    t_set_info.u.t_ch_num_info.t_ch_input.ui4_minor_chn_num = pt_this->ui4_minor_ch_digits;

    a_si_set_item_info_by_win_id(pt_this->e_focus,&t_set_info);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_get_first_channel
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static INT32 _ch_number_get_first_channel(
                    HANDLE_T                    h_crnt_svl,
                    UINT32*                     pui4_channel_id,
                    SVL_REC_T*                  pt_svl_rec
                    )
{
    UINT32    ui4_channel_id = *pui4_channel_id;
    SVL_REC_T t_svl_rec      = {0};
    BOOL      b_found        = FALSE;

    b_found = a_tv_get_svl_rec_by_logic_and_nw_masks(
                    h_crnt_svl,
                    SB_VNET_ACTIVE | SB_VNET_VISIBLE,
                    SB_VNET_ACTIVE | SB_VNET_VISIBLE,
                    TV_ITERATE_DIR_NEXT,
                    &ui4_channel_id,
                    &t_svl_rec
                    );
    if (b_found == FALSE)
    {
        return NAVR_FAIL;
    }

    ui4_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;

    if (SB_ATSC_GET_MAJOR_CHANNEL_NUM((*pui4_channel_id)) != SB_ATSC_GET_MAJOR_CHANNEL_NUM(ui4_channel_id))
    {
        return NAVR_FAIL;
    }

    /* If 2 or more channels with the same channel number,
     * try to get first channel with signal(not SB_VNET_FAKE when channel scan)
     */
    if ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE) > 0)
    {
        UINT32    ui4_not_fake_channel_id = ui4_channel_id;
        SVL_REC_T t_not_fake_svl_rec      = {0};

        b_found = a_tv_get_svl_rec_by_logic_and_nw_masks(
                    h_crnt_svl,
                    SB_VNET_ACTIVE | SB_VNET_FAKE | SB_VNET_VISIBLE,
                    SB_VNET_ACTIVE | SB_VNET_VISIBLE,
                    TV_ITERATE_DIR_NEXT,
                    &ui4_not_fake_channel_id,
                    &t_not_fake_svl_rec
                    );
        if (b_found == TRUE)
        {
            if (SB_ATSC_GET_MAJOR_CHANNEL_NUM(ui4_channel_id)
                == SB_ATSC_GET_MAJOR_CHANNEL_NUM(ui4_not_fake_channel_id)
                    && SB_ATSC_GET_MINOR_CHANNEL_NUM(ui4_channel_id)
                    == SB_ATSC_GET_MINOR_CHANNEL_NUM(ui4_not_fake_channel_id))
            {
                *pui4_channel_id = ui4_not_fake_channel_id;
                *pt_svl_rec      = t_not_fake_svl_rec;

                return NAVR_OK;
            }
        }
    }

    *pui4_channel_id = ui4_channel_id;
    *pt_svl_rec      = t_svl_rec;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_get_matched_channel
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _ch_number_get_matched_channel (
                    HANDLE_T                    h_svl,
                    CH_MATCH_TYPE_T             e_match_type,
                    UINT32                      ui4_major_ch_num,
                    UINT32                      ui4_minor_ch_num,
                    SVL_REC_T*                  pt_svl_rec
                    )
{
    INT32  i4_ret;
    SVL_REC_MATCH_TYPE_T  e_svl_rec_match_type = SVL_REC_MATCH_TYPE_ANY;
    ANA_DIG_TYPE_T        e_ana_dig_type       = ANA_DIG_TYPE_ANY;
    UINT8                 ui1_ch_lst_type      = 0;

    /* Determine the SVL record match type */
    if (e_match_type == CH_MATCH_TYPE_ONE_PART)
    {
        e_svl_rec_match_type = SVL_REC_MATCH_TYPE_ONE_PART;
    }
    else if (e_match_type == CH_MATCH_TYPE_NON_PSIP_TWO_PART)
    {
        e_svl_rec_match_type = SVL_REC_MATCH_TYPE_NON_PSIP_TWO_PART;
    }
    else
    {
        e_svl_rec_match_type = SVL_REC_MATCH_TYPE_TWO_PART;
    }

    /* Determine the analog/digital type if the system support duplicated channel number */
    if (nav_is_allow_dup_ch_num())
    {
        a_cfg_get_ch_list_type (&ui1_ch_lst_type);

        if (ui1_ch_lst_type == APP_CFG_CH_LIST_TYPE_ALL)
        {
            e_ana_dig_type = ANA_DIG_TYPE_ANY;
        }
        else if (ui1_ch_lst_type == APP_CFG_CH_LIST_TYPE_DIGITAL_RADIO)
        {
            e_ana_dig_type = ANA_DIG_TYPE_DIGITAL;
        }
        else if (ui1_ch_lst_type == APP_CFG_CH_LIST_TYPE_DIGITAL)
        {
            e_ana_dig_type = ANA_DIG_TYPE_DIGITAL_ONLY;
        }

        else if (ui1_ch_lst_type == APP_CFG_CH_LIST_TYPE_RADIO)
        {
            e_ana_dig_type = ANA_DIG_TYPE_RADIO_ONLY;
        }

        else if (ui1_ch_lst_type == APP_CFG_CH_LIST_TYPE_ANALOG)
        {
            e_ana_dig_type = ANA_DIG_TYPE_ANALOG;
        }

        else
        {
            e_ana_dig_type = ANA_DIG_TYPE_ANY;
        }
    }


    /* Priority 1: find the active and non-fake one */
    i4_ret = a_tv_filter_svl_rec_by_si_numbers (
                    h_svl,
                    e_ana_dig_type,
                    e_svl_rec_match_type,
                    _DIRECT_INPUT_PRIORITY_1_CHECK_MASK,
                    _DIRECT_INPUT_PRIORITY_1_CHECK_BITS,
                    ui4_major_ch_num,
                    ui4_minor_ch_num,
                    pt_svl_rec
                    );
    if (i4_ret == TVR_OK)
    {
        return NAVR_OK;
    }

    /* Priority 2: find the active only (don't care fake) */
    if (_DIRECT_INPUT_PRIORITY_2_CHECK_MASK != 0)
    {
        i4_ret = a_tv_filter_svl_rec_by_si_numbers (
                        h_svl,
                        e_ana_dig_type,
                        e_svl_rec_match_type,
                        _DIRECT_INPUT_PRIORITY_2_CHECK_MASK,
                        _DIRECT_INPUT_PRIORITY_2_CHECK_BITS,
                        ui4_major_ch_num,
                        ui4_minor_ch_num,
                        pt_svl_rec
                        );
        if (i4_ret == TVR_OK)
        {
            return NAVR_OK;
        }
    }

    /* Priority 3: find the numeric selectable. */
    if (_DIRECT_INPUT_PRIORITY_3_CHECK_MASK != 0)
    {
        i4_ret = a_tv_filter_svl_rec_by_si_numbers (
                        h_svl,
                        e_ana_dig_type,
                        e_svl_rec_match_type,
                        _DIRECT_INPUT_PRIORITY_3_CHECK_MASK,
                        _DIRECT_INPUT_PRIORITY_3_CHECK_BITS,
                        ui4_major_ch_num,
                        ui4_minor_ch_num,
                        pt_svl_rec
                        );
        if (i4_ret == TVR_OK)
        {
            return NAVR_OK;
        }
    }

    return NAVR_NOT_EXIST;
}

INT32 ch_number_select_ch(TV_WIN_ID_T e_grp,
                                UINT32    ui4_major_ch_num,
                                UINT32    ui4_minor_ch_num,
                                BOOL b_is_for_major_ch)
{
    CH_NUMBER_T* pt_this = &t_g_ch_number;
    pt_this->ui4_major_ch_digits = ui4_major_ch_num;
    pt_this->ui4_minor_ch_digits = ui4_minor_ch_num;
    pt_this->b_is_for_major_ch = b_is_for_major_ch;
    return _ch_number_ok_key_handler(pt_this, e_grp, BTN_SELECT);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_ok_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _ch_number_ok_key_handler (
                    CH_NUMBER_T*                pt_this,
                    TV_WIN_ID_T                 e_grp,
                    UINT32                      ui4_key_code
                    )
{
    UINT32    ui4_major_ch_num;
    UINT32    ui4_minor_ch_num;
    SVL_REC_T t_svl_rec;
    HANDLE_T  h_svl;
    UINT32    ui4_channel_id;
    INT32     i4_ret;
    SI_SET_INFO_T t_set_info;
    OCL_SVL_REC_T t_ocl_svl_rec;
    UINT8     ui1_bs_src;

    if (pt_this->ui4_major_ch_digits == SI_INVALID_CHANNEL_NUMBER)
    {
        banner_rcu_key_handler(BANNER_KEY_TT_BY_SPECIFY, e_grp, ui4_key_code);
        return NAVR_OK;
    }

    ui4_major_ch_num = pt_this->ui4_major_ch_digits;
    ui4_minor_ch_num = (pt_this->ui4_minor_ch_digits == SI_INVALID_CHANNEL_NUMBER) ? 0 : pt_this->ui4_minor_ch_digits;

    do {
        t_set_info.e_category = SI_CATEGORY_CH_NUM_INFO;
        t_set_info.u.t_ch_num_info.ui4_info_mask = SI_CH_NUM_INFO_MASK_INPUT | SI_CH_NUM_INFO_MASK_RESULT;
        t_set_info.u.t_ch_num_info.t_ch_input.b_is_ch_inputing = FALSE;
        t_set_info.u.t_ch_num_info.t_ch_input.b_is_inputing_major = pt_this->b_is_for_major_ch;
        t_set_info.u.t_ch_num_info.t_ch_input.ui4_major_chn_num = pt_this->ui4_major_ch_digits;
        t_set_info.u.t_ch_num_info.t_ch_input.ui4_minor_chn_num = pt_this->ui4_minor_ch_digits;

        i4_ret = nav_get_svl_handle(e_grp, &h_svl);
        if (i4_ret != NAVR_OK)
        {
            break;
        }

        if (pt_this->b_is_for_major_ch == TRUE && ui4_minor_ch_num == 0)
        {
            i4_ret = ocl_get_svl_by_ch_num_ex(
                                &t_svl_rec,
                                &t_ocl_svl_rec,
                                ui4_major_ch_num,
                                ui4_minor_ch_num
                                );
            if (i4_ret != NAVR_OK)
            {
                /* try to find one-part channel*/
                i4_ret = _ch_number_get_matched_channel (
                                h_svl,
                                CH_MATCH_TYPE_ONE_PART,
                                ui4_major_ch_num,
                                ui4_minor_ch_num,
                                &t_svl_rec
                                );
            }

            if (i4_ret != NAVR_OK)
            {
                /* try to find two-part channel*/
                i4_ret = _ch_number_get_matched_channel (
                            h_svl,
                            CH_MATCH_TYPE_TWO_PART,
                            ui4_major_ch_num,
                            ui4_minor_ch_num,
                            &t_svl_rec
                            );
            }

            if (i4_ret != NAVR_OK)
            {
                /* try to find non-PISP channel*/
                i4_ret = _ch_number_get_matched_channel (
                            h_svl,
                            CH_MATCH_TYPE_NON_PSIP_TWO_PART,
                            ui4_major_ch_num,
                            ui4_minor_ch_num,
                            &t_svl_rec
                            );
            }

        }
        else
        {
            i4_ret = ocl_get_svl_by_ch_num_ex(
                                &t_svl_rec,
                                &t_ocl_svl_rec,
                                ui4_major_ch_num,
                                ui4_minor_ch_num
                                );

            if (i4_ret != NAVR_OK)
            {
                /* try to find two-part channel*/
                i4_ret = _ch_number_get_matched_channel (
                                h_svl,
                                CH_MATCH_TYPE_TWO_PART,
                                ui4_major_ch_num,
                                ui4_minor_ch_num,
                                &t_svl_rec
                                );
            }

            if (i4_ret != NAVR_OK)
            {
                /* try to find non-PISP channel*/
                i4_ret = _ch_number_get_matched_channel (
                            h_svl,
                            CH_MATCH_TYPE_NON_PSIP_TWO_PART,
                            ui4_major_ch_num,
                            ui4_minor_ch_num,
                            &t_svl_rec
                            );
            }

            if (i4_ret != NAVR_OK && ui4_minor_ch_num == 0)
            {
                /* try to find one-part channel*/
                i4_ret = _ch_number_get_matched_channel (
                            h_svl,
                            CH_MATCH_TYPE_ONE_PART,
                            ui4_major_ch_num,
                            ui4_minor_ch_num,
                            &t_svl_rec
                            );
            }

        }

        /* The system allow duplicated major number, the above function are correctly filtered,
           no more check needed. */
        if (nav_is_allow_dup_ch_num() && i4_ret != NAVR_OK)
        {
            break;
        }
#if 0
        /* Disable this behavior: Input 30.0, if 30.0 is not existed, it will go to 30. */
        if (i4_ret == NAVR_OK &&                                                                          /* Record found. */
            pt_this->b_is_for_major_ch == FALSE &&                                                        /* Minor has been input */
            ui4_minor_ch_num == 0 &&                                                                      /* Minor has been input to 0 */
            SB_ATSC_IS_ONE_PART_CHANNEL_ID(t_svl_rec.uheader.t_rec_hdr.ui4_channel_id) &&                 /* One part channel get. */
            SB_ATSC_GET_MAJOR_CHANNEL_NUM(t_svl_rec.uheader.t_rec_hdr.ui4_channel_id) == ui4_major_ch_num /* Major number match */
           )
        {
            break;  /* ignore */
        }
#endif
        if (i4_ret != NAVR_OK)
        {



            if (ui4_minor_ch_num == 0)
            {
                ui4_channel_id = SB_ATSC_GEN_ONE_PART_CHANNEL_ID(ui4_major_ch_num, 0);
            }
            else
            {
                ui4_channel_id = SB_ATSC_GEN_CHANNEL_ID(ui4_major_ch_num, ui4_minor_ch_num, 0);
            }

            i4_ret = _ch_number_get_first_channel(
                            h_svl,
                            &ui4_channel_id,
                            &t_svl_rec
                            );
            if (i4_ret != NAVR_OK)
            {
                break;
            }
        }

        t_set_info.u.t_ch_num_info.e_result = SI_CH_NUM_INFO_RESULT_SUCCESS;
        a_si_set_item_info_for_once_by_win_id(pt_this->e_focus,&t_set_info);

        _ch_number_reset_input_status(pt_this);

        a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, &ui1_bs_src);
        a_cfg_cust_set_last_channel_tuner_type(ui1_bs_src);
        a_cfg_cust_set_last_channel_id(NAV_UTIL_CNFG_GET_CRNT_CHANNEL_ID(e_grp));

        a_cfg_set_tuner_type(APP_CFG_RECID_BS_SRC,
                             (ANTENNA_SVL_ID==t_ocl_svl_rec.ui2_svl_id) ? APP_CFG_BS_SRC_AIR : APP_CFG_BS_SRC_CABLE
                            );

        i4_ret = nav_change_channel_by_rec(
                    e_grp,
                    &t_svl_rec,
                    NULL
                    );
        if (i4_ret == NAVR_OK)
        {
            return i4_ret;
        }
    } while (0);

    if (i4_ret != NAVR_OK)
    {
        t_set_info.u.t_ch_num_info.e_result = SI_CH_NUM_INFO_RESULT_FAILED;
        a_si_set_item_info_for_once_by_win_id(pt_this->e_focus,&t_set_info);
    }

#ifdef APP_FRONT_PANEL
    i4_ret = nav_get_svl_rec(e_grp, &t_svl_rec);
    if (i4_ret == NAVR_OK)
    {
        a_ctrl_panel_show_channel_id(
                    t_svl_rec.uheader.t_rec_hdr.ui4_channel_id
                    );
    }
#endif

    /*Cannot use nav_change_crnt_channel() because it'll broadcast BEFORE_SVC, AFTER_SVC..ect messages, and this
      causes the banner flash.*/
    _ch_number_reset_input_status(pt_this);

    return NAVR_FAIL;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_reset_input_status
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
static VOID _ch_number_reset_input_status(
                    CH_NUMBER_T*                pt_this
                    )
{
    if (pt_this->b_ch_num_input_processing == FALSE)
    {
        return;
    }

    _ch_number_stop_timer(pt_this);
    pt_this->ui4_major_ch_digits = SI_INVALID_CHANNEL_NUMBER;
    pt_this->ui4_minor_ch_digits = SI_INVALID_CHANNEL_NUMBER;
    pt_this->b_is_for_major_ch         = TRUE;
    pt_this->b_ch_num_input_processing = FALSE;
    pt_this->b_is_active = FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _ch_number_stop_timer(
                    CH_NUMBER_T*                pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE)
    {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop ch_number::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _ch_number_reset_timer(
                    CH_NUMBER_T*                pt_this,
                    TV_WIN_ID_T                 e_grp
                    )
{
    INT32 i4_ret;

    _ch_number_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    pt_this->ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _ch_number_timer_nfy,
                    (VOID*)e_grp
                    );
    if (i4_ret != OSR_OK)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start ch_number::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_do_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _ch_number_do_timeout (
                    VOID*                       pv_grp,
                    VOID*                       pv_unused1,
                    VOID*                       pv_unused2
                    )
{
    CH_NUMBER_T* pt_this = &t_g_ch_number;
    TV_WIN_ID_T  e_grp = (TV_WIN_ID_T)(INT32)pv_grp;

    _ch_number_key_handler(pt_this, e_grp, BTN_SELECT);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _ch_number_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_grp
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch((nav_context_switch_nfy_fct)_ch_number_do_timeout, pv_grp, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ch_number_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _ch_number_key_handler(
    CH_NUMBER_T*                    pt_this,
    TV_WIN_ID_T                     e_grp,
    UINT32                          ui4_key_code)
{
    INT32 i4_ret = NAVR_OK;

    /* do NOT handle any key if input list is running */
    if (TRUE == nav_ipts_list_is_running())
    {
        return NAVR_OK;
    }

#ifdef CH_BANNER_REMAP_CUSTOM_KEY
    ui4_key_code = CH_BANNER_REMAP_CUSTOM_KEY(pt_this->b_ch_num_input_processing, ui4_key_code);
#endif

    switch(ui4_key_code)
    {
    case BTN_SELECT:
        {
            if(nav_is_svl_empty(e_grp) || nav_is_specified_ch_lst_empty(e_grp))
            {
                break;
            }

            _ch_number_stop_timer(pt_this);

            i4_ret = _ch_number_ok_key_handler(pt_this, e_grp, ui4_key_code);

            /*For DTV00006092*/
            if(INP_SRC_TYPE_TV != nav_get_src_type(e_grp))
            {
                /* tricky - hide channel banner before broadcast NAV_UI_MSG_CH_NUM_INPUT_END */
                //nav_return_activation(NAV_COMP_ID_BANNER);
            }
            nav_brdcst_msg_from_component(e_grp, NAV_UI_MSG_CH_NUM_INPUT_END, NULL); /*Broadcast message to components.*/
        }
        break;
    case BTN_KB_MINUS_SIGN:
    case BTN_DIGIT_DOT:
        {
#ifndef APP_ISDB_BRA_VIRTUAL_CHANNEL
            UINT8 ui1_major_digits_amount = 0;
#endif
            if (pt_this->ui4_max_minor_ch_digits == 0)
            {
                break;
            }

            if (nav_is_svl_empty(e_grp) || nav_is_specified_ch_lst_empty(e_grp))
            {
                break;
            }

            if (pt_this->b_ch_num_input_processing == FALSE)
            {
                break;
            }

            if (pt_this->ui4_major_ch_digits == SI_INVALID_CHANNEL_NUMBER)
            {
                break;
            }

            pt_this->b_is_for_major_ch = pt_this->b_is_for_major_ch == TRUE ? FALSE : TRUE;
#ifndef APP_ISDB_BRA_VIRTUAL_CHANNEL
            ui1_major_digits_amount = _ch_number_get_crnt_num_of_digit(pt_this->ui4_major_ch_digits,NULL);
            if (ui1_major_digits_amount > MAX_DIGIT_OF_CAB_2P_MAJOR_CH)
            {
                pt_this->ui4_minor_ch_digits = SI_INVALID_CHANNEL_NUMBER;
                pt_this->ui4_max_minor_ch_digits = MAX_DIGIT_OF_CHANNEL_NUM - ui1_major_digits_amount;
            }
            else
            {
                pt_this->ui4_minor_ch_digits = SI_INVALID_CHANNEL_NUMBER;
                pt_this->ui4_max_minor_ch_digits = MAX_DIGIT_OF_MINOR_CH;
            }
#endif
        }
        /* on purpose to without break statement */

    case BTN_DIGIT_0:
    case BTN_DIGIT_1: case BTN_DIGIT_2: case BTN_DIGIT_3:
    case BTN_DIGIT_4: case BTN_DIGIT_5: case BTN_DIGIT_6:
    case BTN_DIGIT_7: case BTN_DIGIT_8: case BTN_DIGIT_9:

        {
            menu_blank_oled_scrn_timer_refresh();
            if(menu_custom_is_blank_screen())
            {
                menu_custom_unblank_screen(ui4_key_code);
                break;
            }
            if (nav_is_svl_empty(e_grp) || nav_is_specified_ch_lst_empty(e_grp))
            {
                break;
            }

            /*For DTV02026261*/
            {
                ISL_REC_T       t_isl_rec = {0};
                i4_ret = a_tv_get_isl_rec_by_win_id(e_grp, &t_isl_rec);
                NAV_CHK_FAIL(i4_ret == TVR_OK ? NAVR_OK : i4_ret);
                if (INP_SRC_TYPE_TV != t_isl_rec.e_src_type)
                {
                    break;
                }
            }


            /*For DTV00006092*/
            if(FALSE == pt_this->b_ch_num_input_processing) /*notify at the first time*/
            {
                nav_brdcst_msg_from_component(e_grp, NAV_UI_MSG_CH_NUM_INPUT_START, NULL); /*Broadcast message to components.*/
            }
            /*DTV02196394/DTV02194182
            when zoom mode pad is zoom navigation pad, the banner no need to response BTN_DIGIT_0.
            BTN_DIGIT_0 is used to resume/pause zoom mode.
            b_digital_pad: 0:zoom pad,1:digital pad
            */
            UINT8 ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;
            BOOL b_digital_pad  = a_nav_zoom_cust_get_digital_pad_status();
            i4_ret = a_cfg_cust_get_zoom_status(&ui1_zoom_mode);
            if (NAVR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"_ch_number_num_key_handler() failed, ret=%d\r\n", i4_ret));
                break;
            }
            if((ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON) &&
               (b_digital_pad == FALSE && ui4_key_code == BTN_DIGIT_0))
            {
                DBG_LOG_PRINT(("[navigation pad +++] {%s %s() %d}. **ZOOM MODE,BTN_DIGIT_0 no action* ui4_key_code = 0x%x,b_digital_pad  = %d\n",__FILE__, __FUNCTION__, __LINE__,ui4_key_code,b_digital_pad ));
            }
            else
            {
                i4_ret = _ch_number_num_key_handler(pt_this, e_grp, ui4_key_code);
                if (i4_ret != NAVR_OK)
                {
                    DBG_ERROR((_ERROR_HEADER"_ch_number_num_key_handler() failed, ret=%d\r\n", i4_ret));
                    break;
                }
            }
            nav_cancel_delay_change(e_grp);
        }
        break;

    case BTN_PRG_INFO:
        if(INP_SRC_TYPE_TV != nav_get_src_type(e_grp))
        {
            _ch_number_cancel_input();

            /*For DTV00006092*/
            _ch_number_reset_input_status(pt_this);
            /* tricky - hide channel banner before broadcast NAV_UI_MSG_CH_NUM_INPUT_END */
            //nav_return_activation(NAV_COMP_ID_BANNER);
            nav_brdcst_msg_from_component(e_grp, NAV_UI_MSG_CH_NUM_INPUT_END, NULL); /*Broadcast message to components.*/

            /*DTV00103643. When channel input is cancelled, should notify AV.*/
            banner_rcu_key_handler(BANNER_KEY_TT_BY_SPECIFY, e_grp, ui4_key_code);
            break;
        }

    default:
        {
            /*DTV00103643. When channel input is cancelled, should notify AV.*/
            if(pt_this->b_ch_num_input_processing)
            {
                SI_SET_INFO_T t_set_info;
                t_set_info.e_category = SI_CATEGORY_CH_NUM_INFO;
                t_set_info.u.t_ch_num_info.ui4_info_mask = SI_CH_NUM_INFO_MASK_INPUT | SI_CH_NUM_INFO_MASK_RESULT;
                t_set_info.u.t_ch_num_info.t_ch_input.b_is_ch_inputing = FALSE;
                t_set_info.u.t_ch_num_info.t_ch_input.b_is_inputing_major = pt_this->b_is_for_major_ch;
                t_set_info.u.t_ch_num_info.t_ch_input.ui4_major_chn_num = pt_this->ui4_major_ch_digits;
                t_set_info.u.t_ch_num_info.t_ch_input.ui4_minor_chn_num = pt_this->ui4_minor_ch_digits;
                t_set_info.u.t_ch_num_info.e_result = SI_CH_NUM_INFO_RESULT_CANCEL;
                a_si_set_item_info_for_once_by_win_id(pt_this->e_focus,&t_set_info);

                _ch_number_reset_input_status(pt_this);

                /* tricky - hide channel banner before broadcast NAV_UI_MSG_CH_NUM_INPUT_END */
                //nav_return_activation(NAV_COMP_ID_BANNER);
                nav_brdcst_msg_from_component(e_grp, NAV_UI_MSG_CH_NUM_INPUT_END, NULL); /*Broadcast message to components.*/
            }

            banner_rcu_key_handler(BANNER_KEY_TT_BY_SPECIFY, e_grp, ui4_key_code);
        }
        break;
    }

    return NAVR_OK;
}
