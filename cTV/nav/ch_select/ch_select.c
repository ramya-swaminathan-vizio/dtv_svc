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
 * $RCSfile: ch_select.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: yuwen han $
 * $MD5HEX: 7793009dbc122937a0001b34eec5772f $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "ch_select.h"
#include<stdlib.h>
#include "nav/ch_lst/ch_number.h"
#include "nav/sys_info/a_sys_info.h"
#include "menu2/menu_common/menu_common.h"
#include "res/nav/one_channel_list/ocl.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "rest/a_rest_api.h"
#include "res/app_util/config/acfg_custom.h"
#include "wizard_anim/a_wzd.h"


typedef struct _CH_SELECT_CTRL
{
    CH_SELECT_VIEW_T t_view;
    BOOL b_enable;
} CH_SELECT_CTRL;

static CH_SELECT_CTRL *pt_this;
static BOOL _ch_select_osd_enable = TRUE;
static INT32 _ch_select_init(NAV_CONTEXT_T *pt_ctx);
static INT32 _ch_select_deinit(VOID);
static BOOL _ch_select_is_key_handler(NAV_CONTEXT_T *pt_ctx,
                                      UINT32 ui4_key_code);
static INT32 _ch_select_hide(VOID);
static INT32 _ch_select_handle_msg(NAV_CONTEXT_T *pt_ctx,
                                   NAV_UI_MSG_T *pt_ui_msg,
                                   VOID *pv_arg1);
static INT32 _ch_select_ctrl_select(CHAR *channel_num);
static INT32 _ch_select_ctrl_hide(VOID);
BOOL _ch_select_check_bt_remote_paired_and_connected(VOID);


static INT32 _ch_select_init(NAV_CONTEXT_T *pt_ctx)
{
    INT32 i4_ret;
    CH_SELECT_CTRL_T t_ch_select_ctrl;
    t_ch_select_ctrl.pf_select = _ch_select_ctrl_select;
    t_ch_select_ctrl.pf_hide = _ch_select_ctrl_hide;
    i4_ret = pt_this->t_view.pf_init(t_ch_select_ctrl,
                            pt_ctx->t_gui_res.h_canvas,
                            pt_ctx->t_gui_res.i4_x_offset,
                            pt_ctx->t_gui_res.i4_y_offset);
    NAV_CS_CHK_FAIL(i4_ret, "Create channel select view failed");
    return i4_ret;
}

static INT32 _ch_select_deinit(VOID)
{
    return NAVR_OK;
}

static BOOL _ch_select_is_key_handler(
    NAV_CONTEXT_T *pt_ctx,
    UINT32 ui4_key_code)
{
    switch (ui4_key_code)
    {
        case BTN_SELECT:
            return a_ch_select_ctrl_is_enable();
    }
    return FALSE;
}

static INT32 _ch_select_inactivate(NAV_CONTEXT_T* pt_ctx)
{
    return NAVR_OK;
}

static INT32 _ch_select_activate(
    NAV_CONTEXT_T *pt_ctx,
    UINT32 ui4_key_code)
{
    INT32 i4_ret = NAVR_OK;
    switch (ui4_key_code)
    {
        case BTN_SELECT:
            if (!a_ch_select_ctrl_is_enable()) break;
            i4_ret = pt_this->t_view.pf_show();
            NAV_CS_CHK_FAIL(i4_ret, "Create channel select view failed");
            i4_ret = nav_set_component_visible(NAV_COMP_ID_CH_SELECT);
            NAV_CS_CHK_FAIL(i4_ret, "nav_set_component_visible failed");
            break;
    }
    return NAVR_OK;
}

static INT32 _ch_select_hide(VOID)
{
    INT32 i4_ret = NAVR_OK;
    nav_return_activation(NAV_COMP_ID_CH_SELECT);
    i4_ret = pt_this->t_view.pf_hdie();
    NAV_CS_CHK_FAIL(i4_ret, "Cann't hide digit pad");
    return NAVR_OK;
}

static INT32 _ch_select_handle_msg(
    NAV_CONTEXT_T *pt_ctx,
    NAV_UI_MSG_T *pt_ui_msg,
    VOID *pv_arg1)
{
    INT32 i4_ret = NAVR_OK;
    if (NAV_UI_MSG_POWER_OFF == pt_ui_msg->e_id)
    {
        ch_select_view_set_power_off_flag(TRUE);
        DBG_LOG_PRINT(("<NAV ch select>[%s,%d] NAV_UI_MSG_POWER_OFF", __FUNCTION__, __LINE__));
        i4_ret = a_ch_select_view_reset_to_default();
        NAV_CS_CHK_FAIL(i4_ret, "Cannot hide digit pad msg\n");
    }
    else if(NAV_UI_MSG_POWER_ON == pt_ui_msg->e_id)
    {
        ch_select_view_set_power_off_flag(FALSE);
    }

    return NAVR_OK;
}

INT32 a_ch_select_register(CH_SELECT_VIEW_T t_view)
{
    INT32 i4_ret = NAVR_OK;
    NAV_COMP_T t_comp;
    pt_this = (CH_SELECT_CTRL *)c_mem_alloc(sizeof(CH_SELECT_CTRL));
    if (NULL == pt_this)
    {
        return NAVR_OUT_OF_MEM;
    }
    pt_this->b_enable = FALSE;
    pt_this->t_view = t_view;
    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));
    t_comp.pf_init = _ch_select_init;
    t_comp.pf_deinit = _ch_select_deinit;
    t_comp.pf_is_key_handler = _ch_select_is_key_handler;
    t_comp.pf_activate = _ch_select_activate;
    t_comp.pf_inactivate = _ch_select_inactivate;
    t_comp.pf_hide = _ch_select_hide;
    t_comp.pf_handle_msg = _ch_select_handle_msg;
    i4_ret = nav_register_component(NAV_COMP_ID_CH_SELECT, &t_comp, COMP_EXC_SET_CH_SELECT);
    if (i4_ret < 0)
    {
        return i4_ret;
    }
    return NAVR_OK;
}

static INT32 _ch_select(INT16 i2_major,
                        INT16 i2_minor,
                        BOOL b_is_for_major_ch)
{

    TV_WIN_ID_T     t_win_id;
    a_tv_get_focus_win(&t_win_id);
    if(nav_is_svl_empty(t_win_id) || nav_is_specified_ch_lst_empty(t_win_id))
    {
        return NAVR_OK;
    }

    return ch_number_select_ch(t_win_id, i2_major, i2_minor, b_is_for_major_ch);
}

static INT32 _ch_select_ctrl_select(CHAR *channel_num)
{
    INT32 i4_ret = NAVR_OK;
    INT16 i2_major = 0;
    INT16 i2_minor = (INT16)SI_INVALID_CHANNEL_NUMBER;
    BOOL b_is_for_major_ch = TRUE;
    if (c_strlen(channel_num) <= 0) return NAVR_OK;
    i2_major = atoi(channel_num);
    for (UINT16 ui2_idx = 0; ui2_idx < c_strlen(channel_num); ui2_idx++)
    {
        if (channel_num[ui2_idx] == '-' && ui2_idx + 1 < c_strlen(channel_num))
        {
            i2_minor = atoi(&channel_num[ui2_idx + 1]);
            b_is_for_major_ch = FALSE;
        }
    }
    i4_ret = _ch_select(i2_major, i2_minor, b_is_for_major_ch);
    NAV_CS_LOG_FAIL(i4_ret, "_ch_select fialed");
    i4_ret = _ch_select_ctrl_hide();
    return i4_ret;
}

static INT32 _ch_select_ctrl_hide(VOID)
{
    INT32 i4_ret = NAVR_OK;
    i4_ret = nav_hide_component(NAV_COMP_ID_CH_SELECT);
    NAV_CS_CHK_FAIL(i4_ret, "Cann't hide ch select component");
    return i4_ret;
}

// The digit pad is disable for 2020 skus and 2021 D series unless the XRT240 is paired and connected
BOOL _ch_select_check_sku_default_enable(VOID)
{
    BOOL bEnable = FALSE;


    if(a_cfg_cust_Is_CurModel_after_2021_J())
    {
        EnuCusModelSeries enModel = a_cfg_cust_get_CurModelSeries();
        if(enModel == CUS_MODEL_2021_83_2K_D_HD || enModel == CUS_MODEL_2021_83_2K_D_FHD )
        {
            if(_ch_select_check_bt_remote_paired_and_connected())
            {
                bEnable = TRUE;
            }
        }
        else
        {
            bEnable = TRUE;
        }
    }
    else
    {
        if(_ch_select_check_bt_remote_paired_and_connected())
        {
            bEnable = TRUE;
        }
    }
    return bEnable;
}

BOOL _ch_select_check_bt_remote_paired_and_connected(VOID)
{
    REST_API_BT_REMOTE_INFO_T p_remote_info = {0};
    NAV_CS_LOG_FAIL(rest_get_bluetooth_status(&p_remote_info), "Can't get the status of bt remote");
    DBG_LOG_PRINT(("<NAV ch select> p_remote_info.remote_status = %d\r\n", p_remote_info.remote_status));
    return p_remote_info.remote_status == 2;
}

BOOL a_ch_select_ctrl_is_enable(VOID)
{

    TV_WIN_ID_T e_focus_win;
    ISL_REC_T   t_isl_rec;
    UINT16      ocl_num = 0;

    nav_get_focus_id(&e_focus_win);
    nav_get_isl_rec(e_focus_win, &t_isl_rec);
    ocl_num = ocl_get_ocl_num();

    //DTV02533396:ocl_num == 0 means no channel,tuner_setup need handle select key first
    if(t_isl_rec.e_src_type != INP_SRC_TYPE_TV || ocl_num == 0)
    {
        return FALSE;
    }
    else if (a_wzd_is_oobe_mode())
    {
        return FALSE;
    }
    else if(nav_get_active_component() == NAV_COMP_ID_PWD_DLG)
    {
        return FALSE;
    }
    else if(a_ch_select_ctrl_osd_is_enable() == FALSE)
    {
        return FALSE;
    }
#ifdef APP_RETAIL_MODE_SUPPORT
    NAV_RETAIL_MODE_STATUS_T e_retail_status = NAV_RETAIL_MODE_INITIAL;
    a_nav_retail_mode_get_status(&e_retail_status);
    if (NAV_RETAIL_MODE_RUNNING == e_retail_status)
    {
        return FALSE;
    }
#endif

    // The digit pad is disable for 2020 skus and 2021 D series unless the XRT240 is paired and connected
    if (!_ch_select_check_sku_default_enable())
    {
        return FALSE;
    }

    return TRUE;
}
VOID a_ch_select_ctrl_osd_enable(BOOL b_enable)
{
    _ch_select_osd_enable = b_enable;
}
BOOL a_ch_select_ctrl_osd_is_enable(VOID)
{
    return _ch_select_osd_enable;
}
