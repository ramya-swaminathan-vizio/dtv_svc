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
 * $RCSfile: pic_mode_view_single_select_list.c,v $
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
#include "c_handle.h"
#include "pic_pw_popup.h"
#include "nav/navigator.h"
#include "nav/a_navigator.h"
#include "res/nav/nav_variant.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "wizard_anim/a_wzd.h"
#include "am/a_am.h"
#include "nav/retail_mode/a_nav_retail_mode.h"

typedef struct {
    HANDLE_T  h_canvas;
    HANDLE_T  h_timer;
    NAV_PPP_VIEW_HDLR_T t_view_hdlr;
    BOOL      b_is_view_init;
} PPP_T;

////////////////////////////////////////////////////////////////////////////////////////
#define PROMPT_TEST         (1)
#define PPP_TIMER_DURATION  (60*1000)
////////////////////////////////////////////////////////////////////////////////////////
static PPP_T  t_g_ppp = {0};

////////////////////////////////////////////////////////////////////////////////////////
static VOID _ppp_timer_nfy_fct(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );

static INT32 _pic_pw_popup_deinit(
                    VOID
                    )
{
    PPP_T* pt_this = &t_g_ppp;

    c_timer_delete(pt_this->h_timer);

    pt_this->t_view_hdlr.pf_deinit();
    pt_this->b_is_view_init = FALSE;

    return NAVR_OK;
}

static BOOL _pic_pw_popup_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_ANY_UI) == TRUE) {
        return FALSE;
    }

    /* for test */
    //if (ui4_key_code == BTN_P_EFFECT)
    //{
    //    return TRUE;
    //}

    return FALSE;
}

static INT32 _pic_pw_popup_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    INT32  i4_ret;
    PPP_T* pt_this = &t_g_ppp;

    /* do the view init*/
    if (pt_this->b_is_view_init == FALSE)
    {
        pt_this->h_canvas = pt_ctx->t_gui_res.h_canvas;

        i4_ret = pt_this->t_view_hdlr.pf_init(pt_this->h_canvas);
        PPP_CHK_FAIL(i4_ret);

        pt_this->b_is_view_init = TRUE;
    }


    i4_ret = pt_this->t_view_hdlr.pf_activate(ui4_key_code);
    PPP_CHK_FAIL(i4_ret);

    /* for test */
    //nav_grab_activation(NAV_COMP_ID_PPP);
    //nav_set_component_visible(NAV_COMP_ID_PPP);

    a_tv_net_OSD_appear();
    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_EXIST);

    return NAVR_OK;
}

static INT32 _pic_pw_popup_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    return NAVR_OK;
}

static INT32 _pic_pw_popup_hide(
                    VOID
                    )
{
    PPP_T* pt_this = &t_g_ppp;

    pt_this->t_view_hdlr.pf_hide();

    nav_return_activation(NAV_COMP_ID_PPP);

    a_tv_net_OSD_disapper();
    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);

    return NAVR_OK;
}

static INT32 _pic_pw_popup_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_GUI_LANG_CHANGED :
        {
            break;
        }
        default:
            break;
    }

    return NAVR_OK;
}

static VOID _ppp_launch_ppp_nfy_fct(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    nav_grab_activation(NAV_COMP_ID_PPP);
    nav_set_component_visible(NAV_COMP_ID_PPP);
}

static VOID _ppp_launch_nfy_fct(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    UINT8  ui1_fac_mode = APP_CFG_FAC_MODE_NORMAL;
    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;
    UINT8   ui1_page_idx  = 0;
    CHAR  s_name [APP_NAME_MAX_LEN + 1]     = { 0 };
    NAV_RETAIL_MODE_STATUS_T            retail_status;
    a_cfg_get_wzd_status(&ui2_status);
    
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX(ui2_status);

    a_cfg_get_factory_mode(&ui1_fac_mode);

    if ((ui1_fac_mode & APP_CFG_FAC_MODE_FACTORY_MASK) ||
        (ui1_fac_mode & APP_CFG_FAC_MODE_BURNING_MASK))
    {
        _ppp_timer_nfy_fct(NULL, NULL, NULL);
        return;
    }
    
    if(ui1_state == WZD_STATE_RESUME_C4TV)
    {
        DBG_LOG_PRINT(("[PPP] {%s,%d,%s} {ui1_state:%d,ui1_page_idx:%d}Enter.\n", __FILE__, __LINE__, __FUNCTION__,ui1_state,ui1_page_idx));
        return;
    }
    if(nav_is_channel_scan_active())
    {
        DBG_LOG_PRINT(("[PPP] during scan do not pop up \n"));
        return;
    }
    if(a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
    {
        DBG_LOG_PRINT(("[PPP] 3rd app is running do not pop up \n"));
        return;
    }
    a_am_get_active_app (s_name);
    if(c_strcmp(s_name, "mmp") == 0)
    {
        DBG_LOG_PRINT(("[PPP] MMP is running do not pop up \n"));
        return; 
    }
    a_nav_retail_mode_get_status(&retail_status);
    if((retail_status == NAV_RETAIL_MODE_RUNNING&&(a_nav_retail_mode_get_running_type()== RETAIL_MODE_TYPE_VIDEO||
        a_nav_retail_mode_get_running_type()== RETAIL_MODE_TYPE_VIDEO_INTERNAL))||
      (retail_status == NAV_RETAIL_MODE_LAUNCHING))
     {
        DBG_LOG_PRINT(("[PPP] video demo mode or launching status will not pop up \n"));
        return; 
     }

    //DTV01341135 [Vizio][MUSC-4908]Remove display of the Picture Mode and Power Mode influencers
    if(a_cfg_cust_get_support_energy_start_by_mode_name() == FALSE)
    {
        DBG_LOG_PRINT(("[PPP] PIC_PW influencers not pop up for non energy star TV's \n"));
        return;
    }

    nav_resume_self();
    nav_request_context_switch_via_am(_ppp_launch_ppp_nfy_fct, NULL, NULL, NULL);
}

VOID _ppp_timer_cb_fct (HANDLE_T  pt_tm_handle,
                             VOID*     pv_tag)
{
    nav_request_context_switch(_ppp_launch_nfy_fct, NULL, NULL, NULL);
}

static VOID _ppp_timer_nfy_fct(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    PPP_T* pt_this = &t_g_ppp;

    DBG_LOG_PRINT(("[PPP] {%s,%d,%s} Enter.\n", __FILE__, __LINE__, __FUNCTION__));

    if (pt_this->h_timer == NULL_HANDLE)
    {
        if (0 != c_timer_create(&pt_this->h_timer))
        {
            DBG_LOG_PRINT(("[PPP] {%s,%d,%s} create timer failed.\n", __FILE__, __LINE__, __FUNCTION__));
            return;
        }
    }

    if (c_handle_valid(pt_this->h_timer))
    {
        c_timer_stop(pt_this->h_timer);

        c_timer_start(pt_this->h_timer,
                      PPP_TIMER_DURATION,
                      X_TIMER_FLAG_ONCE,
                      _ppp_timer_cb_fct,
                      NULL);
    }
}

static INT32 _pic_pw_popup_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    INT32  i4_ret = 0;
    PPP_T* pt_this = &t_g_ppp;

    i4_ret = a_nav_ppp_view_register_hdlr(&pt_this->t_view_hdlr);
    PPP_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

VOID a_ppp_timer_launch(VOID)
{
#ifdef NEVER //DTV02004588 removo pop-up picture
    nav_request_context_switch(_ppp_timer_nfy_fct, NULL, NULL, NULL);
#endif /* NEVER */
}

INT32 a_nav_ppp_register(VOID)
{
    NAV_COMP_T  t_comp;
    INT32       i4_ret = NAVR_OK;

    c_memset (&t_comp, 0, sizeof (NAV_COMP_T));

    t_comp.pf_init           = _pic_pw_popup_init;
    t_comp.pf_deinit         = _pic_pw_popup_deinit;
    t_comp.pf_is_key_handler = _pic_pw_popup_is_key_handler;
    t_comp.pf_activate       = _pic_pw_popup_activate;
    t_comp.pf_inactivate     = _pic_pw_popup_inactivate;
    t_comp.pf_hide           = _pic_pw_popup_hide;
    t_comp.pf_handle_msg     = _pic_pw_popup_handle_msg;

    i4_ret = nav_register_component(
                NAV_COMP_ID_PPP,
                &t_comp,
                COMP_EXEC_SET_PPP);

    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    return NAVR_OK;
}

