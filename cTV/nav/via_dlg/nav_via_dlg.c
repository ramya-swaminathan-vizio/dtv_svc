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
 * $RCSfile: nav_via_dlg.c,v $
 * $Revision: #2 $
 * $Date: 2015/06/09 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *       USB Plug Detection.
 *
 *---------------------------------------------------------------------------*/

#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "u_fm.h"
#include "c_fm.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_cfg.h"
#include <stdio.h>

#include "res/nav/nav_mlm.h"
#include "res/nav/nav_variant.h"
#include "app_util/a_cfg.h"
#include "nav/a_navigator.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/nav/nav_view.h"
#include "wizard/a_wzd.h"
#include "nav/banner2/a_banner.h"
#include "res/nav/nav_variant_custom.h"
#include "res/msgconvert/msgconvert_custom.h"
#include "nav/via_dlg/nav_via_dlg.h"
#include "nav/via_dlg/nav_via_dlg_view.h"
#include "am/a_am.h"
#include "mmp/a_mmp.h"
#include "menu2/a_menu.h"

#include "wfrrc_interface.h"
#include "res/nav/nav_dbg.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define RET_ON_ERR(_expr)  \
if(_expr != 0)\
{\
    DBG_ERROR (("<NAV_VIA_DLG> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__)); \
    return _expr;\
}

#define NAV_UPGRADE_FILE            "/upgrade.pkg"
#define NAV_UPDATE_LOGIC_FILE       "/updatelogic.txt"

#define NAV_VIA_DLG_BATTERY_LIFE_CHECK_DELAY                ((UINT32)60*1000)
#define NAV_REMOTE_BATTERY_LEN                              (16)

#define _VIA_DLG_SEND_KEY_DELAY     ((UINT32)(20*1000))

extern UINT32   ui4_delay_key_code;

extern BOOL     msg_convert_custom_is_yahoo_ready(VOID);
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_VIA_DLG_HDLR_T t_g_nav_via_dlg;
static HANDLE_T             h_send_key_timer = NULL_HANDLE;
static BOOL                 b_lock_via_key = FALSE;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_hide (VOID);
static BOOL _nav_via_dlg_check_for_response (VOID);
static INT32 _nav_wifi_remote_battery_level_nfy(UINT16 ui2_nfy_id,
                                                VOID* pv_tag,
                                                ICL_NOTIFY_DATA_T*  pt_notify_data);

static INT32 _nav_via_dlg_get_wifi_remote_battery(UINT32* pui4_lvl);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_get_battery_level(UINT32 *pui4_percent)
{
    if (NULL == pui4_percent)
    {
        DBG_ERROR(("<NAV> Return fail:%s:%d:ARG null Pointer!\n", __FILE__, __LINE__));
        return NAVR_INV_ARG;
    }

    _nav_via_dlg_get_wifi_remote_battery(pui4_percent);

    return NAVR_OK;
}

static VOID _nav_via_dlg_check_battery_life(HANDLE_T h_timer, VOID* pv_tag)
{
    INT32       i4_ret = NAVR_OK;
    UINT32      ui4_percent = 100;
    UINT8       ui1_status = 0;
    UINT8       ui1_pair_status = WIFI_REMOTE_PAIR_STATUS_UNPAIRED;

    CHAR        s_app_name[APP_NAME_MAX_LEN+1] = {0};

    i4_ret = a_cfg_custom_get_wifi_remote_pair_status(&ui1_pair_status);
    NAV_LOG_ON_FAIL(i4_ret);

    /* Not check battery life when Wi-Fi Remote was not paired */
    if (WIFI_REMOTE_PAIR_STATUS_PAIRED != ui1_pair_status)
    {
        return;
    }

    /* Not show Low battery msg until MMP or WZD is paused */
    NAV_LOG_ON_FAIL(a_am_get_active_app(s_app_name));

    if (c_strcmp(s_app_name, WZD_NAME) == 0
        || c_strcmp(s_app_name, MMP_NAME) == 0)
    {
        DBG_INFO(("%s() APP %s is actived, show Battery low msg delay.\n",
                                                                __FUNCTION__,
                                                                s_app_name));
        return;
    }

    _nav_via_dlg_get_battery_level(&ui4_percent);

    if (ui4_percent <= WIFI_REMOTE_BATTERY_LOW_THRESHOLD)
    {
        ui1_status = ICL_WIFI_REMOTE_BATTERY_STATUS_LOW;
    }
    else
    {
        ui1_status = ICL_WIFI_REMOTE_BATTERY_STATUS_NORMAL;
    }

    i4_ret = a_icl_set(ICL_MAKE_ID(ICL_GRPID_WIFI_REMOTE_BATTERY_STATUS, ICL_RECID_WIFI_REMOTE_BATTERY_STATUS),
        				 (VOID*) &ui1_status,
        				 ICL_RECID_WIFI_REMOTE_BATTERYL_STATUS_SIZE);
    NAV_LOG_ON_FAIL(i4_ret);

}
/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_init
 * Description:
 *      USB detection module initialization.
 * Input arguments:
 *      pt_ctx
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_init(NAV_CONTEXT_T*   pt_ctx)
{
    NAV_VIA_DLG_HDLR_T* pt_this = &t_g_nav_via_dlg;
    INT32               i4_ret = NAVR_OK;

    pt_this->pt_ctx = pt_ctx;
    pt_this->b_is_battery_low_level = FALSE;

    /* initialize view */
    i4_ret = pt_this->t_view_hdlr.pf_init(
                    pt_this,
                    pt_this->pt_ctx->t_gui_res.h_canvas);
    RET_ON_ERR(i4_ret);

    if (a_cfg_custom_get_wifi_remote_support())
    {
        /* Register notify function of Wifi Remote battery level */
        i4_ret = a_icl_notify_reg (
                        ICL_GRPID_WIFI_REMOTE_BATTERY_STATUS,
                        ICL_PRIORITY_DEFAULT,
                        NULL,
                        NULL,
                        _nav_wifi_remote_battery_level_nfy,
                        &pt_this->ui2_icl_wifi_remote_battery_status);
        if (i4_ret != APP_CFGR_OK) {
            return NAVR_FAIL;
        }
    }

    i4_ret = c_timer_create(&h_send_key_timer);
    RET_ON_ERR(i4_ret);

    if (a_cfg_custom_get_wifi_remote_support())
    {
        i4_ret = c_timer_create(&pt_this->h_timer_bl);
        NAV_LOG_ON_FAIL(i4_ret);

        i4_ret = c_timer_start(pt_this->h_timer_bl,
                                NAV_VIA_DLG_BATTERY_LIFE_CHECK_DELAY,
                                X_TIMER_FLAG_REPEAT,
                                _nav_via_dlg_check_battery_life,
                                NULL);
        NAV_LOG_ON_FAIL(i4_ret);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_deinit
 * Description:
 *      USB detection module deinitialization.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_deinit(VOID)
{
    NAV_VIA_DLG_HDLR_T* pt_this = &t_g_nav_via_dlg;
    INT32               i4_ret = NAVR_OK;

    if (a_cfg_custom_get_wifi_remote_support())
    {
        /* Unregister notify function of Wifi Remote battery level */
        a_icl_notify_unreg(pt_this->ui2_icl_wifi_remote_battery_status);
    }
    /* deinitialize view */
    i4_ret = pt_this->t_view_hdlr.pf_deinit();
    RET_ON_ERR(i4_ret);

    /*free timer*/
    if (TRUE == c_handle_valid(h_send_key_timer))
    {
        i4_ret = c_timer_delete(h_send_key_timer);
        h_send_key_timer = NULL_HANDLE;
        RET_ON_ERR(i4_ret);
    }

    if (TRUE == c_handle_valid(pt_this->h_timer_bl))
    {
        NAV_LOG_ON_FAIL(c_timer_stop(pt_this->h_timer_bl));
        NAV_LOG_ON_FAIL(c_timer_delete(pt_this->h_timer_bl));
        pt_this->h_timer_bl = NULL_HANDLE;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_is_key_handler
 * Description:
 *
 * Input arguments:
 *      pt_ctx
 *      ui4_key_code
 * Output arguments:
 *      None
 * Returns:
 *
 *---------------------------------------------------------------------------*/
static BOOL _nav_via_dlg_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code)
{
    NAV_VIA_DLG_HDLR_T* pt_this = &t_g_nav_via_dlg;

    return pt_this->t_view_hdlr.pf_is_key_handler(ui4_key_code);
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_activate
 * Description:
 *      USB detection module activation.
 * Input arguments:
 *      pt_ctx
 *      ui4_key_code
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_activate(
                    NAV_CONTEXT_T*             pt_ctx,
                    UINT32                     ui4_key_code)
{
    NAV_VIA_DLG_HDLR_T*   pt_this = &t_g_nav_via_dlg;
    INT32                 i4_ret = NAVR_NO_ACTION;

    ui4_delay_key_code = ui4_key_code;

    if (TRUE == _nav_via_dlg_check_for_response())
    {
        //i4_ret = nav_set_component_visible(NAV_COMP_ID_VIA_DLG);
        //RET_ON_ERR(i4_ret);

        /* show view */
        i4_ret = pt_this->t_view_hdlr.pf_show();
        RET_ON_ERR(i4_ret);
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_inactivate
 * Description:
 *      USB detection module inactivation.
 * Input arguments:
 *      pt_ctx
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_inactivate(NAV_CONTEXT_T*     pt_ctx)
{
    INT32                 i4_ret = NAVR_OK;
    //char                  ac_app_name[APP_NAME_MAX_LEN] = {0};

    if (NAV_COMP_ID_VIA_DLG == nav_get_active_component()
        || (TRUE == nav_is_component_visible(NAV_COMP_ID_VIA_DLG)))
    {
    	a_nav_via_dlg_view_dialog_hide();
    }
#if 0
    else
    {
        i4_ret = a_am_get_active_app (ac_app_name);
        RET_ON_ERR(i4_ret);

        /* If menu is showing, we need notify menu to hide the usb pop up dialog. */
        if(0 == c_strcmp(ac_app_name, MENU_NAME))
        {
            a_amb_dispatch_msg(MENU_NAME, MENU_MSG_EXTERNAL_REQ_HIDE_VIA_POP_DLG, NULL, 0);
        }
    }
#endif
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_handle_msg
 * Description:
 *      USB detection module message handle function.
 * Input arguments:
 *      pt_ctx
 *      pt_ui_msg
 *      pv_arg1
 * Output arguments:
 *
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1)
{
    switch (pt_ui_msg->e_id)
    {
    case NAV_UI_MSG_POWER_ON:
        break;
    case NAV_UI_MSG_APP_RESUMED:
        break;
    case NAV_UI_MSG_APP_PRE_RESUME:
        break;
    case NAV_UI_MSG_APP_PAUSING:
    {
        nav_return_activation(NAV_COMP_ID_VIA_DLG);
    }
        break;
    case NAV_UI_MSG_EXTERNAL_CTRL_BEGIN:
        break;
    case NAV_UI_MSG_EXTERNAL_CTRL_END:
        break;
    default:
        break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_hide
 * Description:
 *      USB detection module hide.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_hide (VOID)
{
    NAV_VIA_DLG_HDLR_T*   pt_this = &t_g_nav_via_dlg;
    INT32                 i4_ret = NAVR_OK;

    /* hide the view*/
    i4_ret = pt_this->t_view_hdlr.pf_hide();
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_check_for_response
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *
 *---------------------------------------------------------------------------*/
static BOOL _nav_via_dlg_check_for_response (VOID)
{
//    BOOL            b_is_need_response = TRUE;

#if 0
    INT32           i4_ret = NAVR_OK;
    CHAR            ac_app_name[APP_NAME_MAX_LEN] = {0};

    if (!nav_is_active() )
    {
        i4_ret = a_am_get_active_app (ac_app_name);
        RET_ON_ERR(i4_ret);

        /* is running MMP? */
        if (0 == c_strcmp(ac_app_name, MMP_NAME))
        {
            b_is_need_response = FALSE;
        }
        /* is MENU & MMP coexist status */
    #ifdef APP_MENU_MMP_COEXIST
        else if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
        {
            b_is_need_response = FALSE;
        }
    #endif
                /* is running WIZARD? */
        else if (0 == c_strcmp(ac_app_name, WZD_NAME))
        {
            b_is_need_response = FALSE;
        }
                /* is running MENU? */
        else if(0 == c_strcmp(ac_app_name, MENU_NAME))
        {
            /* usb device number has been incressed and menu is showing.
               we need send message for menu to show dialog */
            if (b_is_need_response)
            {
                b_is_need_response = FALSE;
                a_amb_dispatch_msg(MENU_NAME, MENU_MSG_EXTERNAL_REQ_SHOW_VIA_POP_DLG, NULL, 0);
            }
        }

    }
#endif

#ifndef APP_YAHOO_LOADING_SPINNER_SUPPORT
    return FALSE;

#else

    // Fix Coverity-4490991: Structurally dead code
    BOOL            b_is_need_response = TRUE;

    if (MLM_NAV_KEY_NAV_VIA_DLG_WRNNG_MSG == a_nav_via_dlg_get_show_info())
    {
        b_is_need_response = TRUE;
    }
    else
    {
        b_is_need_response = FALSE;
    }

    return b_is_need_response;

#endif

}

static VOID _nav_wifi_remote_icl_nfy_hdlr (VOID*   pv_tag1,
                                          VOID*   pv_tag2,
                                          VOID*   pv_tag3)
{
    INT32           i4_ret;
    UINT8           ui1_status = 0;
    NAV_VIA_DLG_HDLR_T*   pt_this = &t_g_nav_via_dlg;

    SIZE_T          z_size = ICL_RECID_WIFI_REMOTE_BATTERYL_STATUS_SIZE;
    ICL_ID_TYPE     e_id = (ICL_ID_TYPE) (((UINT32) pv_tag1) & 0x0000FFFF);

    if (e_id == ICL_MAKE_ID(ICL_GRPID_WIFI_REMOTE_BATTERY_STATUS, ICL_RECID_WIFI_REMOTE_BATTERY_STATUS))
    {
        i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_WIFI_REMOTE_BATTERY_STATUS, ICL_RECID_WIFI_REMOTE_BATTERY_STATUS),
                           &ui1_status,
                           &z_size);

        if(i4_ret != ICLR_OK || ui1_status == 0)
        {
            return;
        }
        else
        {
            pt_this->b_is_battery_low_level = TRUE;

            if (nav_is_component_visible(NAV_COMP_ID_VIA_DLG))
            {
                pt_this->t_view_hdlr.pf_show();
            }
            else
            {
                nav_grab_activation(NAV_COMP_ID_VIA_DLG);
            }

            /* Show battery life low message once only */
            c_timer_stop(pt_this->h_timer_bl);
        }
    }

    pt_this->b_is_battery_low_level = FALSE;
}

static INT32 _nav_wifi_remote_battery_level_nfy(UINT16 ui2_nfy_id,
                                                VOID* pv_tag,
                                                ICL_NOTIFY_DATA_T*  pt_notify_data)
{
    INT32  i4_ret = NAVR_OK;

    ICL_GRPID_TYPE  e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    SIZE_T          z_size = 0;
    UINT8           ui1_icl_mask;
    UINT8           ui1_info_status;

    if (e_grp_id != ICL_GRPID_WIFI_REMOTE_BATTERY_STATUS)
    {
        return NAVR_OK;
    }

    ui1_icl_mask = ICL_RECID_WIFI_REMOTE_BATTERY_STATUS;
    z_size = ICL_RECID_WIFI_REMOTE_BATTERYL_STATUS_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_WIFI_REMOTE_BATTERY_STATUS, ui1_icl_mask),
                       &ui1_info_status,
                       &z_size);

    if (i4_ret != ICLR_OK)
    {
        return NAVR_OK;
    }

    if (ICL_WIFI_REMOTE_BATTERY_STATUS_LOW == ui1_info_status)
    {

        a_nav_via_dlg_set_show_info(MLM_NAV_KEY_WIFI_REMOTE_BATTERY_LEVEL);
        if (nav_is_active () == FALSE
            && (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_PAUSED))
        {
            nav_resume_self();
            nav_request_context_switch_via_am(_nav_wifi_remote_icl_nfy_hdlr,
                                                (VOID*) (UINT32)pt_notify_data->pe_id[0],
                                                (VOID*) NULL,
                                                (VOID*) NULL);
        }
        else
        {
            nav_request_context_switch(_nav_wifi_remote_icl_nfy_hdlr,
                                        (VOID*) (UINT32)pt_notify_data->pe_id[0],
                                        (VOID*) NULL,
                                        (VOID*) NULL);
        }
    }

    return NAVR_OK;
}

#ifdef APP_YAHOO_LOADING_SPINNER_SUPPORT
static VOID _nav_via_snd_key_timer_fct(VOID*        pv_tag1,
                                        VOID*        pv_tag2,
                                        VOID*        pv_tag3)
{
    DBG_INFO(("%s(): Send key BTN_WIDGET=================\n", __FUNCTION__));
    a_nav_via_dlg_set_via_lock(FALSE);
    nav_return_activation(NAV_COMP_ID_VIA_DLG);
    a_amb_default_key_handler_ex(WGL_MSG_KEY_DOWN, (VOID*)pv_tag1, (VOID*)0);
    return;
}

static VOID _nav_via_dlg_snd_key_timer_nfy(HANDLE_T h_timer, VOID* pv_tag)
{
    nav_request_context_switch(_nav_via_snd_key_timer_fct, pv_tag, NULL, NULL);
}

static INT32 _nav_via_dlg_snd_key_timer_start(UINT32 ui4_key_code)
{
    INT32                       i4_ret = NAVR_OK;

    if (NULL_HANDLE != h_send_key_timer)
    {
        DBG_INFO(("%s(): Start timer Send key=============\n", __FUNCTION__));

        a_nav_via_dlg_set_via_lock(TRUE);

        i4_ret = c_timer_start(h_send_key_timer,
                               _VIA_DLG_SEND_KEY_DELAY,
                               X_TIMER_FLAG_ONCE,
                               _nav_via_dlg_snd_key_timer_nfy,
                               (VOID*)ui4_key_code);
        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}

static INT32 _nav_via_dlg_snd_key_timer_stop(VOID)
{
    INT32                       i4_ret = NAVR_OK;

    if (NULL_HANDLE != h_send_key_timer)
    {
        DBG_INFO(("%s(): stop timer =============\n", __FUNCTION__));

        i4_ret = c_timer_stop(h_send_key_timer);
        nav_return_activation(NAV_COMP_ID_VIA_DLG);

        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}
#endif

static VOID _nav_via_dlg_yahoo_nfy_hdlr(VOID *pv_tag1, VOID *pv_tag2, VOID *pv_tag3)
{
#ifdef APP_YAHOO_LOADING_SPINNER_SUPPORT
    if (nav_is_component_visible(NAV_COMP_ID_VIA_DLG)
        && MLM_NAV_KEY_WIFI_REMOTE_BATTERY_LEVEL != a_nav_via_dlg_get_show_info()
        && (UINT32)pv_tag1)
    {
        //Any shortcut key of 3rd is not enable untill yahoo installed
        ui4_delay_key_code = BTN_WIDGET;

        if (BTN_WIDGET == ui4_delay_key_code
            || BTN_AMAZON == ui4_delay_key_code
            || BTN_NETFLIX == ui4_delay_key_code
            || BTN_MGO == ui4_delay_key_code
            || BTN_VUDU == ui4_delay_key_code
            || BTN_IHEART_RADIO == ui4_delay_key_code
            || BTN_WATCHFREE == ui4_delay_key_code
            || BTN_REDBOX == ui4_delay_key_code
            || BTN_HAYSTACK == ui4_delay_key_code)
        {
            DBG_INFO(("%s() SEND BTN_WIDGET after 20s.\n", __FUNCTION__));
            //a_amb_default_key_handler_ex(WGL_MSG_KEY_DOWN, (VOID*)ui4_delay_key_code, (VOID*)0);
            _nav_via_dlg_snd_key_timer_start(ui4_delay_key_code);
        }
        else
        {
            DBG_INFO(("%s():%d Invalid Button\n", __FUNCTION__, __LINE__));
        }
    }
    else if ((UINT32)pv_tag2 == 1)
    {
        DBG_INFO(("%s() pv_tag2 = %d.\n", __FUNCTION__, (UINT32)pv_tag2));
        _nav_via_dlg_snd_key_timer_stop();
    }
#endif
    return;
}

#ifdef APP_PORTING
static INT32 _nav_via_dlg_device_status_info_atohtoi(const CHAR* ps)
{
    INT32  i4_total = 0;

    while((*ps != '\r') && (*ps != '\n') && (*ps != '\0'))
    {
        if ((*ps >= '0') && (*ps <= '9'))
        {
            i4_total = 16 * i4_total + (*ps - '0');
        }
        else if (('A' == *ps) || ('a' == *ps))
        {
            i4_total = 16 * i4_total + 10;
        }
        else if (('B' == *ps) || ('b' == *ps))
        {
            i4_total = 16 * i4_total + 11;
        }
        else if (('C' == *ps) || ('c' == *ps))
        {
            i4_total = 16 * i4_total + 12;
        }
        else if (('D' == *ps) || ('d' == *ps))
        {
            i4_total = 16 * i4_total + 13;
        }
        else if (('E' == *ps) || ('e' == *ps))
        {
            i4_total = 16 * i4_total + 14;
        }
        else if (('F' == *ps) || ('f' == *ps))
        {
            i4_total = 16 * i4_total + 15;
        }

        ps++;
    }

    return i4_total;
}
#endif

static INT32 _nav_via_dlg_get_wifi_remote_battery(UINT32* pui4_lvl)
{
#ifdef APP_PORTING
    CHAR            s_battery[5] = {0};
    INT32           i4_battery = 0;
    INT32           i4_ret = NAVR_OK;

    i4_ret = c_get_remote_info(WFRCCMsg_BatteryLevel, s_battery);

    if (i4_ret != NAVR_OK)
    {
        return NAVR_OK;
    }
    else
    {
        if (s_battery[0] == '\0')
        {
             return NAVR_OK;
        }

        i4_battery = _nav_via_dlg_device_status_info_atohtoi(s_battery);

        *pui4_lvl = (UINT32)i4_battery;
    }
#endif
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
INT32 a_nav_via_dlg_get_yahoo_state_cb(VOID)
{
#ifdef APP_YAHOO_LOADING_SPINNER_SUPPORT
    BOOL b_started = msg_convert_custom_is_yahoo_ready();

    return nav_request_context_switch(_nav_via_dlg_yahoo_nfy_hdlr,
                                        (VOID*) (UINT32)b_started,
                                        (VOID*) NULL,
                                        (VOID*) NULL);
#else
    return 0;
#endif
}

INT32 a_nav_via_dlg_stop_cb(VOID)
{
    _nav_via_dlg_yahoo_nfy_hdlr((VOID*)(UINT32)FALSE, (VOID*)1, (VOID*)NULL);
    return NAVR_OK;
}

VOID a_nav_via_dlg_set_via_lock(BOOL b_lock)
{
    b_lock_via_key = b_lock;
}

BOOL a_nav_via_dlg_get_via_lock(VOID)
{
    return b_lock_via_key;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      a_nav_via_dlg_register
 * Description:
 *      The registration function of the USB detection component.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 a_nav_via_dlg_register(VOID)
{
    NAV_VIA_DLG_HDLR_T* pt_this = &t_g_nav_via_dlg;
    NAV_COMP_T          t_comp;
    INT32               i4_ret = NAVR_OK;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    /* NAV_COMP_ID_VIA_DLG */
    t_comp.pf_init           = _nav_via_dlg_init;
    t_comp.pf_deinit         = _nav_via_dlg_deinit;
    t_comp.pf_is_key_handler = _nav_via_dlg_is_key_handler;
    t_comp.pf_activate       = _nav_via_dlg_activate;
    t_comp.pf_inactivate     = _nav_via_dlg_inactivate;
    t_comp.pf_hide           = _nav_via_dlg_hide;
    t_comp.pf_handle_msg     = _nav_via_dlg_handle_msg;
    t_comp.ui4_exclusive_set = COMP_EXEC_SET_VIA_DLG;

    i4_ret = nav_register_comp(
                NAV_COMP_ID_VIA_DLG,
                &t_comp);
    RET_ON_ERR(i4_ret);

    /* register view */
    i4_ret = nav_via_dlg_view_register_default_hdlr(&pt_this->t_view_hdlr);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

