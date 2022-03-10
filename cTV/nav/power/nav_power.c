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
 * $RCSfile: nav_power.c,v $
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
#ifdef APP_NAV_PWR_SUPPORT

#include "u_common.h"
#include "u_irrc_btn_def.h"
#include "c_handle.h"
#include "c_pcl.h"
#include "c_cfg.h"
#include "c_svctx.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_icl_common.h"
#include "nav/a_navigator.h"
#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "am/a_am.h"

#include "nav/power/a_nav_power.h"
#include "nav/power/nav_power.h"
#include "nav/power/nav_power_view.h"
#include "am/a_am.h"
#include "res/nav/nav_variant.h"
#include "mmp/a_mmp.h"
#include "menu2/a_menu.h"
#include "wizard2/a_wzd.h"
#include "bgm/a_bgm.h"
#include "res/menu2/menu_custom.h"

#include "app_util/a_cfg.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "msgconvert/a_msgconvert.h"
#include "res/msgconvert/msgconvert_custom.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef INT32                               _NAV_PWR_COND_STATUS_T;
#define _NAV_PWR_COND_STATUS_EMPTY          ((_NAV_PWR_COND_STATUS_T)-1)
#define _NAV_PWR_COND_STATUS_OFF            ((_NAV_PWR_COND_STATUS_T)FALSE)
#define _NAV_PWR_COND_STATUS_ON             ((_NAV_PWR_COND_STATUS_T)TRUE)
#define _NAV_SMART_UI_CHECK_PERIOD          (1000 * 10)

typedef struct __NAV_PWR_MEMBER_T
{
    BOOL                          b_enabled;                          /* This component is enabled or not */
    NAV_PWR_UI_INFO_T             t_last_notify;
    NAV_PWR_VIEW_HANDLER_T        t_view_handler;                     /*UI handler*/
    VOID*                         pv_view;                            /*Power-View's instance*/

    NAV_PWR_ON_COND_T             e_on_cond;
    NAV_PWR_OFF_COND_T            e_off_cond;
    NAV_PWR_SRC_TYPE_T            e_src_type;                         /* VGA, DVD, TV, or AV */


    UINT16                        ui2_burn_mode_cfg_nfy;
    HANDLE_T                      h_iom;
    HANDLE_T                      h_svctx_main;
    UINT16                        ui2_dpms_cfg_nfy;
    UINT16                        ui2_icl_nfy_id;
    UINT16                        ui2_icl_net_tv_svc_nfy_id;
    UINT16                        ui2_icl_cast_nfy_id;
	UINT16                        ui2_3rd_play_id;
    BOOL                          b_is_normal;                        /* TV_NORMAL or PIP/POP */
    BOOL                          b_dpms_enabled;
} _NAV_PWR_MEMBER_T;
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _NAV_PWR_MEMBER_T          t_g_pwr;
static BOOL                       b_is_first_power_on = FALSE;
static HANDLE_T                   h_smart_ui_check_timer;
static BOOL                       b_smart_ui_check_timer_start = FALSE;
static BOOL                       b_oled = FALSE;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_init(NAV_CONTEXT_T*                   pt_ctx);

static INT32 _nav_pwr_deinit(VOID);

static INT32 _nav_pwr_hide(VOID);

static INT32 _nav_pwr_handle_msg(NAV_CONTEXT_T*             pt_ctx,
                                 NAV_UI_MSG_T*              pt_ui_msg,
                                 VOID*                      pv_arg1);

static INT32 _nav_pwr_reset_wakeup_setting(_NAV_PWR_MEMBER_T*   pt_this);

static VOID _nav_pwr_cfg_change_cb(UINT16                   ui2_nfy_id,
                                   VOID*                    pv_tag,
                                   UINT16                   ui2_id);

static VOID _nav_pwr_cfg_change_msg_hdlr(VOID*              pv_unused,
                                         VOID*              pv_unused2,
                                         VOID*              pv_unused3);

static INT32 _nav_pwr_update_src_type(_NAV_PWR_MEMBER_T*        pt_this,
                                      TV_WIN_ID_T               e_focus,
                                      const NAV_XNG_SRC_TRGT_T* pt_xng_info);

static NAV_PWR_SRC_TYPE_T _nav_pwr_check_src_type(_NAV_PWR_MEMBER_T*        pt_this,
                                      TV_WIN_ID_T               e_focus,
                                      const NAV_XNG_SRC_TRGT_T* pt_xng_info);


static BOOL _nav_pwr_is_cond_type_match(_NAV_PWR_MEMBER_T*      pt_this);
static INT32 _nav_pwr_get_cond_status_for_signal_loss(_NAV_PWR_MEMBER_T* pt_this,
                                                      _NAV_PWR_COND_STATUS_T* pe_status);
static BOOL _nav_pwr_is_mmp_app_active    (VOID);
static BOOL _nav_pwr_is_3rd_widget_active (VOID);
static BOOL _nav_pwr_is_auto_power_off_func_active (VOID) ;
static INT32 _nav_pwr_icl_app_status_cb (UINT16             ui2_nfy_id,
                                                     VOID*              pv_tag,
                                                     ICL_NOTIFY_DATA_T* pt_notify_data);

static INT32 _nav_pwr_icl_net_tv_svc_status_cb (UINT16             ui2_nfy_id,
                                                            VOID*              pv_tag,
                                                            ICL_NOTIFY_DATA_T* pt_notify_data);
static INT32 _nav_pwr_cast_icl_nfy_cb(UINT16                 ui2_nfy_id,
                                              VOID*                 pv_tag,
                                              ICL_NOTIFY_DATA_T*    pt_notify_data);

static VOID _nav_pwr_dpms_cfg_change_msg_hdlr(VOID*              pv_unused,
                                             VOID*              pv_unused2,
                                             VOID*              pv_unused3);

static VOID _nav_pwr_svctx_notify_fct(HANDLE_T                    h_svctx,          /* in  */
                                                SVCTX_COND_T                e_nfy_cond,       /* in  */
                                                SVCTX_NTFY_CODE_T           e_code,           /* in  */
                                                STREAM_TYPE_T               e_stream_type,    /* in  */
                                                VOID*                       pv_nfy_tag        /* in  */
                                                );
static VOID _nav_pwr_svctx_msg_hdlr(
    VOID*                               pv_tag1,
    VOID*                               pv_tag2,
    VOID*                               pv_tag3);

static VOID _nav_pwr_iom_nfy_fct (
                          VOID*             pv_nfy_tag,
                          IOM_NFY_COND_T    e_nfy_cond,
                          UINT32            ui4_evt_code,
                          UINT32            ui4_data
                          );

static VOID _nav_pwr_iom_nfy_hdlr(
    VOID*                               pv_nfy_cond,
    VOID*                               pv_evt_code,
    VOID*                               pv_data);
extern INT32 nav_pwr_set_status(VOID*   pv_view, POWER_OFF_STATUS e_status);

extern INT32 cmd_convert_send_cmd(CHAR* ps_cmd);
extern VOID a_set_pwd_to_unlock_state(UINT8 ui2_state);
extern VOID a_set_5351_pin_state(UINT32 ui4_pin_state);
extern UINT32 a_get_5351_pin_state(VOID);
static INT32 _nav_pwr_3rd_play_nfy_cb(UINT16                 ui2_nfy_id,
                                  VOID*                 pv_tag,
                                  ICL_NOTIFY_DATA_T*    pt_notify_data);
extern BOOL a_is_oled_compensation_support();

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

static INT32 _nav_pwr_refresh_current_status(VOID)
{
    _NAV_PWR_MEMBER_T*          pt_this = &t_g_pwr;

    if(pt_this->b_is_normal)
    {
        UINT8       ui1_input_id = 0;
        ISL_REC_T   t_isl_rec;

        a_cfg_get_input_src(SN_PRES_MAIN_DISPLAY, &ui1_input_id);

        a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);


        if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status() && msg_convert_custom_airplay_active())//Airplay
        {
            if(TRUE == pt_this->b_dpms_enabled)
            {
                pt_this->t_last_notify.b_is_meet = _NAV_PWR_COND_STATUS_ON;
            }
            else
            {
                pt_this->t_last_notify.b_is_meet = _NAV_PWR_COND_STATUS_OFF;
            }

        }
        else if(nav_is_signal_loss(TV_WIN_ID_MAIN) && (t_isl_rec.e_src_type != INP_SRC_TYPE_VTRL))
        {
            if(NAV_PWR_SRC_TYPE_VGA == pt_this->e_src_type || TRUE == pt_this->b_dpms_enabled)
            {
                pt_this->t_last_notify.b_is_meet = _NAV_PWR_COND_STATUS_ON;
            }
            else
            {
                pt_this->t_last_notify.b_is_meet = _NAV_PWR_COND_STATUS_OFF;
            }
        }
        else
        {
            pt_this->t_last_notify.b_is_meet = _NAV_PWR_COND_STATUS_OFF;
        }
    }
    else
    {
        if(nav_is_signal_loss(TV_WIN_ID_MAIN) &&
           nav_is_signal_loss(TV_WIN_ID_SUB)  &&
           TRUE == pt_this->b_dpms_enabled)
        {
             pt_this->t_last_notify.b_is_meet = _NAV_PWR_COND_STATUS_ON;
        }
        else
        {
            pt_this->t_last_notify.b_is_meet = _NAV_PWR_COND_STATUS_OFF;
        }
    }

    if(_NAV_PWR_COND_STATUS_ON == pt_this->t_last_notify.b_is_meet)
    {
        if(FALSE == _nav_pwr_is_auto_power_off_func_active())
        {
            pt_this->t_last_notify.b_is_meet = _NAV_PWR_COND_STATUS_OFF;
        }
    }

    /* Resend current status */
    pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                           NAV_PWR_UI_IF_MEET_COND,
                                           &pt_this->t_last_notify);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_power_set_component_enable
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_power_set_component_enable(BOOL     b_enabled)
{
    _NAV_PWR_MEMBER_T*          pt_this = &t_g_pwr;
    INT32                       i4_ret;

    /* Set component state */
    pt_this->b_enabled = b_enabled;

    if (b_enabled == TRUE)
    {
        /* Refresh current status */
        i4_ret = _nav_pwr_refresh_current_status();
        NAV_CHK_FAIL(i4_ret);
    }
    else
    {
        if(pt_this->pv_view == NULL)
        {
            DBG_LOG_PRINT(("[NAV][Power] a_nav_power_set_component_enable can't find view \n"));
            return NAVR_OK;
        }

        /* Send FORCE_STOP_TIMER to view */
        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               NAV_PWR_UI_FORCE_STOP_TIMER,
                                               NULL);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_power_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_power_register(
    const NAV_PWR_VIEW_HANDLER_T*     pt_view_handler)
{
    NAV_COMP_T                        t_comp;
    _NAV_PWR_MEMBER_T*                pt_this = &t_g_pwr;
    INT32                             i4_ret;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    /*set view handler*/
    if(pt_view_handler)
    {
        pt_this->t_view_handler = *pt_view_handler;
    }
    else
    {
        i4_ret = nav_pwr_get_default_handler(&pt_this->t_view_handler);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to get default Power-View handler. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }
    }

    if(FALSE == NAV_PWR_IS_LEGAL_VIEW_HANDLER(&pt_this->t_view_handler))
    {
        DBG_ERROR((_ERROR_HEADER"Power-View handler is illegal.\r\n"));
        return NAVR_FAIL;
    }

    t_comp.pf_init           = _nav_pwr_init;
    t_comp.pf_deinit         = _nav_pwr_deinit;
    t_comp.pf_is_key_handler = NULL;
    t_comp.pf_activate       = NULL;
    t_comp.pf_inactivate     = NULL;
    t_comp.pf_hide           = _nav_pwr_hide;
    t_comp.pf_handle_msg     = _nav_pwr_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_POWER, &t_comp, COMP_EXEC_SET_POWER);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"nav_register_component(NAV_COMP_ID_POWER) failed. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_pwr_power_off
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_pwr_power_off(
    NAV_PWR_WAKEUP_METHOD_T     e_method)
{
    UINT32                      ui4_setup = 0 /*for Klocwork*/;
    UINT8                       ui1_setup;
    INT32                       i4_ret;

    if(FALSE == _nav_pwr_is_auto_power_off_func_active())
    {
        return NAVR_OK;
    }

    switch(e_method)
    {
        case NAV_PWR_WM_VGA:
            {
                /*get current setting*/
                i4_ret = c_pcl_get_wakeup_setup(&ui4_setup);
                if(PCLR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"c_pcl_get_wakeup_setup() failed. i4_ret = %d\r\n", i4_ret));
                    return NAVR_FAIL;
                }

                /*add VGA wakeup*/
                i4_ret = c_pcl_set_wakeup_setup(ui4_setup | PCL_WAKE_UP_CAP_VGA);
                if(PCLR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"c_pcl_set_wakeup_setup(%d) failed. i4_ret = %d\r\n", (ui4_setup | PCL_WAKE_UP_CAP_VGA), i4_ret));
                    return NAVR_FAIL;
                }

                /* Get current setting: in BGM, the VGA wakeup would be clear, so AP keep one byte to denote it */
                i4_ret = a_cfg_get_enable_signal_wakeup_bit(& ui1_setup);
                if (APP_CFGR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"a_cfg_get_enable_signal_wakeup_bit() failed. i4_ret = %d\r\n", i4_ret));
                    return NAVR_FAIL;
                }
                /* Add VGA wakeup */
                i4_ret = a_cfg_set_enable_signal_wakeup_bit(ui1_setup | APP_CFG_VID_ENABLE_SGNL_WAKEUP_VGA);
                if(APP_CFGR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"a_cfg_set_enable_signal_wakeup_bit(%d) failed. i4_ret = %d\r\n", (ui1_setup), i4_ret));
                    return NAVR_FAIL;
                }
                /*Power down*/
                i4_ret = a_amb_power_on(FALSE);
                if(AMBR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"a_amb_power_on(FALSE) failed. i4_ret = %d\r\n", i4_ret));
                    return NAVR_FAIL;
                }
            }
            break;

        case NAV_PWR_WM_EMPTY:
            {
                /*Power down only*/
                menu_custom_blank_screen_set_block_power_off(FALSE);
                i4_ret = a_amb_power_on(FALSE);
                if(AMBR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"a_amb_power_on(%d) failed. i4_ret = %d\r\n", i4_ret));
                    return NAVR_FAIL;
                }
            }

        default:
            break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static VOID _nav_pwr_check_smart_ui_action (
                    VOID*                       pv_grp,
                    VOID*                       pv_unused1,
                    VOID*                       pv_unused2
                    )
{
    INT32 i4_ret = NAVR_OK;
    DBG_INFO(("[NAV][Power][OLED PROTECT]%s %d\n",__FUNCTION__,__LINE__));
    ACFG_MI_MM_INFO_T     st_mi_info = {0};
    if (menu_custom_is_blank_screen())
    {
        DBG_INFO(("[NAV][Power][OLED PROTECT] already blankscreen, no action %s %d\n",__FUNCTION__,__LINE__));
    }
    if (NAVR_OK != a_cfg_mi_mm_querry(&st_mi_info))
    {
        if (menu_custom_blank_oled_scrn_timer_is_start() && BLK_SCRN_OLED_SMART_UI == menu_custom_get_blank_scrn_mode())
        {
            DBG_INFO(("[NAV][Power][OLED PROTECT] BLK_SCRN_OLED_SMART_UI scrn timer started %s %d\n",__FUNCTION__,__LINE__));
        }
        else
        {
            DBG_LOG_PRINT(("[NAV][Power][OLED PROTECT] start scrn timer %s %d\n",__FUNCTION__,__LINE__));
            menu_custom_set_blank_scrn_mode(BLK_SCRN_OLED_SMART_UI);
            i4_ret = menu_blank_oled_scrn_timer_start();
            if (i4_ret != NAVR_OK)
            {
                DBG_ERROR((_ERROR_HEADER"start scrn timer failed\r\n"));
            }
        }
    }
    else
    {
        if (BLK_SCRN_OLED_SMART_UI == menu_custom_get_blank_scrn_mode() && menu_custom_blank_oled_scrn_timer_is_start())
        {
            i4_ret = menu_blank_oled_scrn_timer_stop();
            if (i4_ret != NAVR_OK)
            {
                DBG_ERROR((_ERROR_HEADER"start scrn timer failed\r\n"));
            }
            if (a_acfg_get_still_image_status() == ACFG_OLED_ERR_EVENT_GSP_IMG_STILL)
            {
                menu_custom_set_blank_scrn_mode(BLK_SCRN_OLED_STILL_IMAGE);
                i4_ret = menu_blank_oled_scrn_timer_start();
                if (i4_ret != NAVR_OK)
                {
                    DBG_ERROR((_ERROR_HEADER"start scrn timer failed\r\n"));
                }
            }
        }
    }
}


static VOID _nav_pwr_check_smart_ui_nfy_fct(HANDLE_T  pt_tm_handle,
                           VOID*     pv_tag)
{
    nav_request_context_switch(_nav_pwr_check_smart_ui_action, pv_tag, NULL, NULL);
}

static INT32 _nav_pwr_check_smart_ui_start(VOID)
{
    INT32 i4_ret = NAVR_OK;
    DBG_INFO(("[NAV][Power][OLED PROTECT]%s %d\n",__FUNCTION__,__LINE__));
    if (b_smart_ui_check_timer_start)
    {
        c_timer_stop(h_smart_ui_check_timer);
    }
    i4_ret = c_timer_start(h_smart_ui_check_timer,
                           _NAV_SMART_UI_CHECK_PERIOD,
                           X_TIMER_FLAG_REPEAT,
                           _nav_pwr_check_smart_ui_nfy_fct,
                           NULL);
    if (i4_ret == NAVR_OK)
    {
        b_smart_ui_check_timer_start = TRUE;
    }
    return i4_ret;
}

static INT32 _nav_pwr_check_smart_ui_stop(VOID)
{
    INT32 i4_ret = NAVR_OK;
    DBG_INFO(("[NAV][Power][OLED PROTECT]%s %d\n",__FUNCTION__,__LINE__));
    i4_ret = c_timer_stop(h_smart_ui_check_timer);
    if (i4_ret == NAVR_OK)
    {
        b_smart_ui_check_timer_start = FALSE;
    }
    return i4_ret;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_init( NAV_CONTEXT_T*   pt_ctx)
{
    _NAV_PWR_MEMBER_T*     pt_this = &t_g_pwr;
    INT32                  i4_ret;

    do
    {
        /*init data member*/
        pt_this->b_enabled   = TRUE;
        pt_this->b_is_normal = TRUE;
        pt_this->t_last_notify.b_normal = TRUE;
        pt_this->e_src_type = NAV_PWR_SRC_TYPE_UNKNOWN;
        pt_this->ui2_burn_mode_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;

        i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_FACTORY,
                                  NULL,
                                  _nav_pwr_cfg_change_cb,
                                  &pt_this->ui2_burn_mode_cfg_nfy);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"register ui2_burn_mode_cfg_nfy failed\r\n"));

            pt_this->ui2_burn_mode_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
            break;
        }

        i4_ret = a_icl_notify_reg(ICL_GRPID_APP_STATUS,
                                  ICL_PRIORITY_DEFAULT,
                                  NULL,
                                  NULL,
                                  _nav_pwr_icl_app_status_cb,
                                  &pt_this->ui2_icl_nfy_id);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"register ICL_GRPID_APP_STATUS icl notify failed\r\n"));

            pt_this->ui2_icl_nfy_id = 0xFFFF;
            break;
        }

        i4_ret = a_icl_notify_reg(ICL_GRPID_NET_TV_SVC_STATUS,
                                  ICL_PRIORITY_DEFAULT,
                                  NULL,
                                  NULL,
                                  _nav_pwr_icl_net_tv_svc_status_cb,
                                  &pt_this->ui2_icl_net_tv_svc_nfy_id);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"register ICL_GRPID_NET_TV_SVC_STATUS icl notify failed\r\n"));

            pt_this->ui2_icl_net_tv_svc_nfy_id = 0xFFFF;
            break;
        }

        i4_ret = a_icl_notify_reg(ICL_GRPID_CAST_SRC_STATUS,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _nav_pwr_cast_icl_nfy_cb,
                              &(pt_this->ui2_icl_cast_nfy_id));
        if (ICLR_OK != i4_ret)
        {
            pt_this->ui2_icl_nfy_id = 0;
            break;
        }
		i4_ret = a_icl_notify_reg(ICL_GRPID_3RD_PLAY_STATUS,
						 ICL_PRIORITY_DEFAULT,
						 NULL,
						 NULL,
						 _nav_pwr_3rd_play_nfy_cb,
						 &(pt_this->ui2_3rd_play_id));
        if (ICLR_OK != i4_ret)
        {
            pt_this->ui2_3rd_play_id = 0;
            break;
        }

        i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_MISC,
                                  NULL,
                                  _nav_pwr_cfg_change_cb,
                                  &pt_this->ui2_dpms_cfg_nfy);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"register ui2_dpms_cfg_nfy failed\r\n"));

            pt_this->ui2_dpms_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
            break;
        }

        {
            /* SVCTX */
            i4_ret = c_svctx_open (SVCTX_NAME_MAIN, &pt_this->h_svctx_main);
            if(i4_ret != SMR_OK)
            {
              DBG_ERROR((_ERROR_HEADER"Can't Open SVCTX handle"));
              pt_this->h_svctx_main = NULL_HANDLE;
              return NAVR_FAIL;
            }

            i4_ret = c_svctx_set_listener (pt_this->h_svctx_main,
                                          _nav_pwr_svctx_notify_fct,
                                          NULL);
            if(i4_ret != SMR_OK)
            {
              DBG_ERROR((_ERROR_HEADER"c_svctx_set_listener failed"));
              c_svctx_close (pt_this->h_svctx_main);
              pt_this->h_svctx_main = NULL_HANDLE;
              return NAVR_FAIL;
            }
        }

        {
            IRRC_SETTING_T          t_irrc_setting;
            /* IOM for menu*/
             c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
             t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
             t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = 50; /* No repeat key */
             t_irrc_setting.t_rpt_evt_itvl.ui2_other = 20; /* No repeat key */
             t_irrc_setting.b_notify_raw_data        = TRUE;

             i4_ret = c_iom_open(IOM_DEV_TYPE_IN_IRRC,
                                 IOM_DEV_ID_ANY,
                                 NULL,
                                 &t_irrc_setting,
                                 NULL,
                                 _nav_pwr_iom_nfy_fct,
                                 & pt_this->h_iom
                                 );
             if(i4_ret != SMR_OK)
             {
               DBG_ERROR((_ERROR_HEADER"Can't Open iom \n"));
               pt_this->h_iom = NULL_HANDLE;
               return NAVR_FAIL;
             }
        }

        /* Menu->Setup->DPMS setting */
        if(APP_CFGR_OK != a_cfg_get_dpms(&pt_this->b_dpms_enabled))
        {
            pt_this->b_dpms_enabled = TRUE;
        }

        /*create FRZ-View*/
        i4_ret = pt_this->t_view_handler.pf_init(pt_ctx->t_gui_res.h_canvas,
                                                 pt_ctx->t_gui_res.i4_x_offset,
                                                 pt_ctx->t_gui_res.i4_y_offset,
                                                 pt_ctx->t_gui_res.e_color_type,
                                                 &pt_this->pv_view,
                                                 &pt_this->e_on_cond,
                                                 &pt_this->e_off_cond);
        if(NAVR_OK != i4_ret)
        {
            pt_this->pv_view = NULL;
            break;
        }

        b_oled = a_is_oled_compensation_support();

        i4_ret = c_timer_create(&h_smart_ui_check_timer);
        if(i4_ret != NAVR_OK)
        {
            DBG_ERROR(("<NAV>[power]Can't create h_smart_ui_check_timer\r\n"));
        }

        return NAVR_OK;

    } while(0);

    /*free resoruce*/
    _nav_pwr_deinit();
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_deinit(VOID)
{
    _NAV_PWR_MEMBER_T*       pt_this = &t_g_pwr;
    INT32                    i4_ret;

    /**/
    if(APP_CFG_NOTIFY_NULL_ID != pt_this->ui2_burn_mode_cfg_nfy)
    {
        a_cfg_notify_unreg(pt_this->ui2_burn_mode_cfg_nfy);
        pt_this->ui2_burn_mode_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
    }

    if(0xFFFF != pt_this->ui2_icl_nfy_id)
    {
        a_icl_notify_unreg(pt_this->ui2_icl_nfy_id);
        pt_this->ui2_icl_nfy_id = 0xFFFF;
    }

    if(0xFFFF != pt_this->ui2_icl_net_tv_svc_nfy_id)
    {
        a_icl_notify_unreg(pt_this->ui2_icl_net_tv_svc_nfy_id);
        pt_this->ui2_icl_net_tv_svc_nfy_id = 0xFFFF;
    }

    /*deinit Power-View*/
    if(pt_this->t_view_handler.pf_deinit)
    {
        i4_ret = pt_this->t_view_handler.pf_deinit(pt_this->pv_view);
    }
    else
    {
        i4_ret = NAVR_OK;
    }

    /*zero memory*/
    c_memset(pt_this, 0, sizeof(_NAV_PWR_MEMBER_T));

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_hide(VOID)
{
    _NAV_PWR_MEMBER_T*     pt_this = &t_g_pwr;

    pt_this->t_view_handler.pf_hide(pt_this->pv_view);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_handle_msg
 * Description
 *      maybe this msg is better to handle by _nav_pwr_svctx_notify_fct
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_handle_msg(
    NAV_CONTEXT_T*                 pt_ctx,
    NAV_UI_MSG_T*                  pt_ui_msg,
    VOID*                          pv_arg1)
{
    _NAV_PWR_MEMBER_T*             pt_this      = &t_g_pwr;
    INT32                          i4_ret;
    _NAV_PWR_COND_STATUS_T         e_status     = _NAV_PWR_COND_STATUS_EMPTY;
    UINT8                          ui1_fac_mode = APP_CFG_FAC_MODE_NORMAL;
    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_AS_APP_PAUSED:
            {
                if(pt_ui_msg->e_id_as_paused == NAV_UI_MSG_BEFORE_SVC_CHANGE)
                {
                    cmd_convert_send_cmd("\n:dtv_app_mtk,am,:keyIdleNotify=0\n");
                }
            }
            break;
        case NAV_UI_MSG_BEFORE_SVC_CHANGE:
            {
                NAV_XNG_SRC_TRGT_T*     pt_xng_info = (NAV_XNG_SRC_TRGT_T*)pv_arg1;

                NAV_ASSERT(pt_xng_info);

                DBG_LOG_PRINT(("[NAV][Power][Handle_Msg] NAV_UI_MSG_BEFORE_SVC_CHANGE  %d \n", pt_xng_info->e_type));
                cmd_convert_send_cmd("\n:dtv_app_mtk,am,:keyIdleNotify=0\n");

                if(pt_this->t_last_notify.e_src_type != _nav_pwr_check_src_type(pt_this,pt_ctx->t_svc_res.e_focus_tv_win_id,pt_xng_info))
                {
                     /* Force stop the timer do matter TV/AV (VGA) */
                     pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                                            NAV_PWR_UI_FORCE_STOP_TIMER,
                                                            NULL);

                     e_status = _NAV_PWR_COND_STATUS_OFF;  /* Always set off if input src changed */
                }
               NAV_CHK_FAIL(_nav_pwr_update_src_type(pt_this, pt_ctx->t_svc_res.e_focus_tv_win_id, pt_xng_info));
            }
            break;
        case NAV_UI_MSG_OTHER_APP_PAUSED:
            if(c_strcmp ((CHAR*)pv_arg1, "mscvt") != 0 && b_oled)
            {
                if (menu_custom_blank_oled_scrn_timer_is_start() && BLK_SCRN_OLED_SMART_UI == menu_custom_get_blank_scrn_mode())
                {
                    i4_ret = menu_blank_oled_scrn_timer_stop();
                    if (i4_ret != NAVR_OK)
                    {
                        DBG_ERROR((_ERROR_HEADER"Can't stop smart ui timer \n"));
                    }
                }
                i4_ret = _nav_pwr_check_smart_ui_stop();
                if (i4_ret != NAVR_OK)
                {
                    DBG_ERROR((_ERROR_HEADER"Can't stop smart ui timer \n"));
                }
            }

            break;
        case NAV_UI_MSG_OTHER_APP_RESUMED:
            {
                if(c_strcmp ((CHAR*)pv_arg1, "mscvt") == 0 &&
                   APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status())
                {
                    NAV_XNG_SRC_TRGT_T*     pt_xng_info = (NAV_XNG_SRC_TRGT_T*)pv_arg1;
                    NAV_ASSERT(pt_xng_info);
                    NAV_CHK_FAIL(_nav_pwr_update_src_type(pt_this, pt_ctx->t_svc_res.e_focus_tv_win_id, pt_xng_info));

                    DBG_LOG_PRINT(("[power][%s %d] 3rd app resumed\n",__FUNCTION__,__LINE__));

                    if(TRUE == _nav_pwr_is_auto_power_off_func_active())
                    {
                        _nav_pwr_get_cond_status_for_signal_loss(pt_this, &e_status);
                    }
                    if (b_oled)
                    {
                        i4_ret = _nav_pwr_check_smart_ui_start();
                        if (i4_ret != NAVR_OK)
                        {
                            DBG_ERROR((_ERROR_HEADER"Can't start smart ui timer \n"));
                        }
                    }
                    break;
                }
                if (((c_strcmp ((CHAR*)pv_arg1, (CHAR*)MMP_NAME) == 0) ||
                    (c_strcmp ((CHAR*)pv_arg1, (CHAR*)WZD_NAME) == 0) ||
                    (c_strcmp ((CHAR*)pv_arg1, (CHAR*)MSCVT_NAME) == 0)) &&
                    !msg_convert_custom_browser_ctrl_active())
                {
                    /* Force stop the timer when MMP resumed */
                    pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                                           NAV_PWR_UI_FORCE_STOP_TIMER,
                                                           NULL);
                    pt_this->t_last_notify.b_is_meet = FALSE;

                    return NAVR_OK;
                }
            }
            break;

        case NAV_UI_MSG_WITH_SIGNAL:
            {
                LOCKED_STATUS_T e_lock_status = LOCKED_STATUS_NONE;

                e_lock_status = nav_get_locked_status(pt_ctx->t_svc_res.e_focus_tv_win_id);

                if ((LOCKED_STATUS_PROGRAM_RATING == e_lock_status) ||
                    (LOCKED_STATUS_CHANNEL_LOCKED == e_lock_status) ||
                    (LOCKED_STATUS_INP_SRC_LOCKED == e_lock_status))
                {
                    break;
                }
                {
                    if(_nav_pwr_is_cond_type_match(pt_this) && pt_this->b_is_normal)
                    {
                        e_status = _NAV_PWR_COND_STATUS_OFF;
                    }

                    if(FALSE == pt_this->b_is_normal)
                    {
                        if(FALSE == nav_is_signal_loss(TV_WIN_ID_MAIN) || FALSE == nav_is_signal_loss(TV_WIN_ID_SUB))
                        {
                            e_status = _NAV_PWR_COND_STATUS_OFF;
                        }
                    }
                }
            }
            break;
        /*spec4.0(p90 4.5.2) if a channel or program is locked,after 10 minutes,TV power off*/
        case NAV_UI_MSG_LOCKED_CH:
        case NAV_UI_MSG_LOCKED_PROG:
        case NAV_UI_MSG_LOCKED_INP:
        case NAV_UI_MSG_NO_SIGNAL:
        case NAV_UI_MSG_EMPTY_SVL:
            {
                if(TRUE == _nav_pwr_is_auto_power_off_func_active())
                {
                    _nav_pwr_get_cond_status_for_signal_loss(pt_this, &e_status);
                }
            }
            break;

        case NAV_UI_MSG_BEFORE_TV_MODE_CHANGE:
            {
                NAV_TV_MODE_XNG_INFO_T* pt_info = (NAV_TV_MODE_XNG_INFO_T*)pv_arg1;

                NAV_ASSERT(pt_info);

                pt_this->b_is_normal = (TV_MODE_TYPE_NORMAL == pt_info->e_new_tv_mode);
                pt_this->t_last_notify.b_normal = pt_this->b_is_normal;
            }
            break;

        case NAV_UI_MSG_FOCUS_CHANGED:
            {
                i4_ret = _nav_pwr_update_src_type(pt_this, (TV_WIN_ID_T)(INT32) pv_arg1, NULL);
                if(NAVR_OK != i4_ret)
                {
                    return i4_ret;
                }
            }
            break;

        case NAV_UI_MSG_APP_PAUSING:
            {
                {
                    CHAR    s_app_name [APP_NAME_MAX_LEN + 1] = {0};
                    a_am_get_resuming_app(s_app_name);
                    DBG_LOG_PRINT(("[POWER] s_app_name [%s].\n", s_app_name));

                    /*only handle in menu*/
                    if (c_strcmp(s_app_name, MENU_NAME) == 0)
                    {
                        DBG_LOG_PRINT(("\n[POWER] not need handle nav msg event.\n"));
                        return NAVR_OK;
                    }
                }

                if(NAV_PWR_OFC_APP_PAUSE & pt_this->e_off_cond)
                {
                    // blank screnn with no signal should not stop sleep timer
                    if (menu_custom_is_blank_screen() && (menu_custom_get_blank_scrn_mode() == BLK_SCRN_OLED_NO_SIGNAL || menu_custom_get_blank_scrn_mode() == BLK_SCRN_NORMAL))
                    {
                        DBG_LOG_PRINT(("\n[POWER] blank screen nomal and no signal should not stop sleep timer.\n"));
                        if (pt_this->t_last_notify.b_is_meet != _NAV_PWR_COND_STATUS_ON)
                        {
                            e_status = _NAV_PWR_COND_STATUS_ON;
                        }
                        break;
                    }
                    e_status = _NAV_PWR_COND_STATUS_OFF;
                }
            }
            break;

        case NAV_UI_MSG_POWER_ON:
            {
                e_status = _NAV_PWR_COND_STATUS_ON;
                b_is_first_power_on = TRUE;
                a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, FALSE);
                _nav_pwr_reset_wakeup_setting(pt_this);
            }
            break;
        case NAV_UI_MSG_POWER_OFF:
            {
                UINT8       ui1_odm_id = 0;
                a_cfg_custom_get_odm_idx(&ui1_odm_id);
                a_set_pwd_to_unlock_state(FALSE);
                if(a_get_5351_pin_state() == 1)
                {
                    a_set_5351_pin_state(2);
                }

                if(ui1_odm_id != 1) //add AMT Mark , 20180425
                {
                    a_cfg_get_factory_mode(&ui1_fac_mode);

                    if(ui1_fac_mode & APP_CFG_FAC_MODE_FACTORY_MASK)
                    {
                        ui1_fac_mode = (UINT8)(ui1_fac_mode & ~APP_CFG_FAC_MODE_FACTORY_MASK);
                        /* If it is not in factory mode, enter factory mode */
                        a_cfg_set_factory_mode(ui1_fac_mode);

                        a_cfg_update_factory_mode();

                        /* flush the settings to storage right away */
                        a_cfg_store();
                    }
                }
            }
            break;
        case NAV_UI_MSG_BACKGROUND_MODE:
        {
            BOOL b_in_bgm = (BOOL)(UINT32)pv_arg1;

            if(b_in_bgm)
            {
                e_status = _NAV_PWR_COND_STATUS_OFF;
            }
        }
            break;
        default:
            break;
    }

    if(_NAV_PWR_COND_STATUS_EMPTY != e_status)
    {
        /*If this component is disabled or MENU/DPMS is OFF*/
        if((FALSE == pt_this->b_enabled || FALSE == pt_this->b_dpms_enabled)&&
            _NAV_PWR_COND_STATUS_ON == e_status)
        {
            if(NAV_PWR_SRC_TYPE_VGA != pt_this->e_src_type)
            {
                e_status = _NAV_PWR_COND_STATUS_OFF;
            }
        }

        if(e_status != pt_this->t_last_notify.b_is_meet)   /*ON <--> OFF*/
        {
            pt_this->t_last_notify.b_is_meet = e_status;

            pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                                   NAV_PWR_UI_IF_MEET_COND,
                                                   &pt_this->t_last_notify);
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_reset_wakeup_setting
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_reset_wakeup_setting(
    _NAV_PWR_MEMBER_T*                     pt_this)
{
    UINT32                      ui4_setup = 0 /*for Klocwork*/;
    UINT8                       ui1_setup;
    INT32                       i4_ret;

    /*get current setting*/
    i4_ret = c_pcl_get_wakeup_setup(&ui4_setup);
    if(PCLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_pcl_get_wakeup_setup() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /*remove VGA wakeup*/
    ui4_setup &= (~(PCL_WAKE_UP_CAP_VGA));
    i4_ret = c_pcl_set_wakeup_setup(ui4_setup);
    if(PCLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_pcl_set_wakeup_setup(%d) failed. i4_ret = %d\r\n", (ui4_setup & ~PCL_WAKE_UP_CAP_VGA), __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /*get current setting*/
    i4_ret = a_cfg_get_enable_signal_wakeup_bit(&ui1_setup);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): a_cfg_get_enable_signal_wakeup_bit() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /*remove VGA wakeup*/
    ui1_setup &= (~(APP_CFG_VID_ENABLE_SGNL_WAKEUP_VGA));
    i4_ret = a_cfg_set_enable_signal_wakeup_bit(ui1_setup);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): a_cfg_set_enable_signal_wakeup_bit(%d) failed. i4_ret = %d\r\n", ui1_setup, __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_cfg_change_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_pwr_cfg_change_cb(
    UINT16                         ui2_nfy_id,
    VOID*                          pv_tag,
    UINT16                         ui2_id)
{
    _NAV_PWR_MEMBER_T*             pt_this;

    if(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_FACTORY) == ui2_id)
    {
        pt_this = &t_g_pwr;

        if(pt_this->ui2_burn_mode_cfg_nfy == ui2_nfy_id)
        {
            /*post a message to itself*/
            nav_request_context_switch(_nav_pwr_cfg_change_msg_hdlr,
                                       NULL,
                                       NULL,
                                       NULL);
        }
    }

    if(CFG_MAKE_ID(APP_CFG_GRPID_MISC, APP_CFG_RECID_DPMS) == ui2_id)
    {
        pt_this = &t_g_pwr;

        if(pt_this->ui2_dpms_cfg_nfy == ui2_nfy_id)
        {
             /*post a message to itself*/
             nav_request_context_switch(_nav_pwr_dpms_cfg_change_msg_hdlr,
                                        NULL,
                                        NULL,
                                        NULL);
        }
    }


}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_is_mmp_app_active
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_pwr_is_mmp_app_active (VOID)
{
    ISL_REC_T   t_isl_rec           = {0};
    CHAR        s_disp_name[16+1]   = {0};
    UINT8       ui1_crnt_input_src  = 0;

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_input_src(s_disp_name, &ui1_crnt_input_src);
    a_isl_get_rec_by_id(ui1_crnt_input_src, &t_isl_rec);
    if((INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type && DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type) || INP_SRC_TYPE_MM == t_isl_rec.e_src_type)
    {
        return TRUE;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_is_3rd_widget_active
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_pwr_is_3rd_widget_active (VOID)
{
    INT32     i4_ret = -1;
    UINT8     ui1_val = 0;
    extern BOOL menu_custom_is_blank_screen(VOID);

    i4_ret = a_icl_get_app_status(&ui1_val);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to get icl rec. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
    }

    if((2 == ui1_val || 0 == ui1_val || 1 == ui1_val)
        && !menu_custom_is_blank_screen())/* 2---APP_STATUS_YH_DOCK, 3---APP_STATUS_YH_SIDEBAR a_icl.h*/
    {
        return TRUE;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_is_uli_active
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_pwr_is_uli_active (VOID)
{
    INT32     i4_ret = -1;
    UINT8     ui1_val = 0;
    SIZE_T    z_size = ICL_RECID_USB_UPGRADE_STATUS_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_USB_UPGRADE, ICL_RECID_USB_UPGRADE_STATUS),
                       &ui1_val,
                       &z_size);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to get icl rec. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return FALSE;
    }

    if(ICL_USB_UPGRADE_STATUS_RUNNING == ui1_val)
    {
        return TRUE;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_is_bgm_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_pwr_is_bgm_mode (VOID)
{
    if(a_bgm_is_running())
    {
        return TRUE;
    }

    if(FALSE == a_am_is_power_on())
    {
        return TRUE;
    }

    return FALSE;
}

extern BOOL a_oled_compensation_is_running();

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_is_auto_power_off_func_active
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_pwr_is_auto_power_off_func_active (VOID)
{
    _NAV_PWR_MEMBER_T*  pt_this = &t_g_pwr;
    BOOL                b_power_off_active = TRUE;
    ACFG_RETAIL_MODE_T  e_retail_mode = 0;

    a_cfg_custom_get_retail_mode_setting(&e_retail_mode);

    do
    {
		if (menu_oled_pro_auto_pwr_off_timer_is_start() == TRUE)
	    {
		   DBG_LOG_PRINT(("[power][%s %d] dpms enable for oled protected\n",__FUNCTION__,__LINE__));
		   b_power_off_active =	FALSE;
		   break;
	    }
	    else 
	    {
		   if((FALSE == pt_this->b_enabled || FALSE == pt_this->b_dpms_enabled))
		   {
			   DBG_LOG_PRINT(("[power][%s %d] dpms disabled\n",__FUNCTION__,__LINE__));
			   b_power_off_active = FALSE;
			   break;
		   }
		   if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status()&&
            FALSE == msg_convert_custom_airplay_active() &&
            FALSE == msg_convert_custom_browser_ctrl_active() )
		   {
			  DBG_LOG_PRINT(("[power][%s %d] 3rd app lanuching\n",__FUNCTION__,__LINE__));
			  b_power_off_active =	FALSE;
			  break;
		   }
	    }

        if(ACFG_RETAIL_MODE_HOME != e_retail_mode)
        {
            DBG_LOG_PRINT(("[power][%s %d] retail mode\n",__FUNCTION__,__LINE__));
            b_power_off_active = FALSE;
            break;
        }
        if(a_oled_compensation_is_running())
        {
            DBG_LOG_PRINT(("[power][%s %d] off-rs/jb is activing\n",__FUNCTION__,__LINE__));
            b_power_off_active = FALSE;
            break;
        }

        if(_nav_pwr_is_mmp_app_active())
        {
            DBG_LOG_PRINT(("[power][%s %d] mmp lanuching\n",__FUNCTION__,__LINE__));
            b_power_off_active =  FALSE;
            break;
        }

        if(_nav_pwr_is_uli_active())
        {
             DBG_LOG_PRINT(("[power][%s %d] uli activing\n",__FUNCTION__,__LINE__));
             b_power_off_active = FALSE;
             break;
        }

        if(_nav_pwr_is_bgm_mode())
        {
            DBG_LOG_PRINT(("[power][%s %d] bgm activing\n",__FUNCTION__,__LINE__));
            b_power_off_active = FALSE;
            break;
        }
    }while(0);

    return b_power_off_active;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_icl_app_status_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_pwr_icl_app_status_handler (VOID*    pv_tag1,
                                        VOID*    pv_tag2,
                                        VOID*    pv_tag3 )
{
    _NAV_PWR_MEMBER_T*  pt_this = &t_g_pwr;

    if(FALSE == pt_this->b_enabled || !pt_this->b_dpms_enabled)
    {
        return;
    }
    if(!pt_this->b_dpms_enabled)
    {
        BOOL    b_dpms_enabled = FALSE;
        if(APP_CFGR_OK != a_cfg_get_dpms(&b_dpms_enabled) || b_dpms_enabled == FALSE)
        {
            return;
        }
    }

    {
        CHAR   s_app_name [APP_NAME_MAX_LEN + 1] = {0};
        a_am_get_resuming_app(s_app_name);
        DBG_LOG_PRINT(("\n[POWER] s_app_name [%s].\n", s_app_name));

        if (c_strcmp(s_app_name, MENU_NAME) == 0)
        {
            DBG_LOG_PRINT(("\n[POWER] not need handle.\n"));
            return;
        }
    }

    if(_nav_pwr_is_3rd_widget_active())
    {
        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               NAV_PWR_UI_FORCE_STOP_TIMER,
                                               NULL);

        pt_this->t_last_notify.b_is_meet = FALSE;
    }
    else
    {
        if(pt_this->b_is_normal)
        {
            if(nav_is_signal_loss(TV_WIN_ID_MAIN))
            {
                pt_this->t_last_notify.b_is_meet = TRUE;
            }
            else
            {
                pt_this->t_last_notify.b_is_meet = FALSE;
            }
        }
        else
        {
            if(nav_is_signal_loss(TV_WIN_ID_MAIN) && nav_is_signal_loss(TV_WIN_ID_SUB))
            {
                pt_this->t_last_notify.b_is_meet = TRUE;
            }
            else
            {
                pt_this->t_last_notify.b_is_meet = FALSE;
            }
        }
    }

    pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                           NAV_PWR_UI_IF_MEET_COND,
                                           &pt_this->t_last_notify);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_icl_net_tv_svc_status_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_pwr_icl_net_tv_svc_status_handler (VOID*    pv_tag1,
                                             VOID*    pv_tag2,
                                             VOID*    pv_tag3 )
{
    _NAV_PWR_MEMBER_T*  pt_this = &t_g_pwr;
    TV_WIN_ID_T                 t_win_id;
    ISL_REC_T                   t_isl_rec;
	ACFG_MI_MM_INFO_T    t_mi_mm_info_t  = {0};
	BOOL         b_interlace             = FALSE;
	UINT8  play_status =0;
	a_icl_get_3rd_play_status (&play_status);

    a_tv_get_focus_win(&t_win_id);

    if (b_is_first_power_on == TRUE)
    {
        b_is_first_power_on = FALSE;
        return;
    }

    if((FALSE == pt_this->b_enabled || FALSE == pt_this->b_dpms_enabled))
    {
        return;
    }
    a_tv_get_isl_rec_by_win_id(t_win_id,&t_isl_rec);
    if((a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_PAUSED)&&
      (t_isl_rec.t_avc_info.e_video_type != DEV_VTRL_CAST))
    {
        return;
    }
    if((a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_PAUSED)&&
      (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)&&
       FALSE == msg_convert_custom_airplay_active())
    {
        pt_this->t_last_notify.b_is_meet = FALSE;
        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                           NAV_PWR_UI_IF_MEET_COND,
                           &pt_this->t_last_notify);
		return;
    }

    if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status() &&
      FALSE == msg_convert_custom_airplay_active()&&
      FALSE == msg_convert_custom_browser_ctrl_active())
    {
        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               NAV_PWR_UI_FORCE_STOP_TIMER,
                                               NULL);

        pt_this->t_last_notify.b_is_meet = FALSE;
    }
    else/*APP_STATUS_NET_TV_SVC_PAUSE a_icl.h*/
    {
    	if(MENUR_OK == a_cfg_mi_mm_querry_ex(&t_mi_mm_info_t,&b_interlace))
		{
			DBG_LOG_PRINT(("%s %d eAudioCodec = %d\n",__FUNCTION__,__LINE__, t_mi_mm_info_t.eAudioCodec));
		}
        if(pt_this->b_is_normal)
        {
            if(t_mi_mm_info_t.eAudioCodec > 0|| play_status > 0)
            {
                pt_this->t_last_notify.b_is_meet = FALSE;
            }
            else
            {
                pt_this->t_last_notify.b_is_meet = TRUE;
            }
	        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                       NAV_PWR_UI_IF_MEET_COND,
                                       &pt_this->t_last_notify);
        }
        else
        {
            if(nav_is_signal_loss(TV_WIN_ID_MAIN) && nav_is_signal_loss(TV_WIN_ID_SUB))
            {
                pt_this->t_last_notify.b_is_meet = TRUE;
            }
            else
            {
                pt_this->t_last_notify.b_is_meet = FALSE;
            }
        }

    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_icl_app_status_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_icl_app_status_cb (UINT16             ui2_nfy_id,
                                     VOID*              pv_tag,
                                     ICL_NOTIFY_DATA_T* pt_notify_data)
{
    return nav_request_context_switch(_nav_pwr_icl_app_status_handler,
                                      NULL,
                                      NULL,
                                      NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_icl_net_tv_svc_status_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_icl_net_tv_svc_status_cb (UINT16             ui2_nfy_id,
                                           VOID*              pv_tag,
                                           ICL_NOTIFY_DATA_T* pt_notify_data)
{
    return nav_request_context_switch(_nav_pwr_icl_net_tv_svc_status_handler,
                                      NULL,
                                      NULL,
                                      NULL);
}

static VOID _nav_pwr_cast_icl_msg_hdlr(
                    VOID*            pv_unused1,
                    VOID*            pv_unused2,
                    VOID*            pv_unused3
                    )
{
    INT32               i4_ret  = NAVR_OK;
    _NAV_PWR_MEMBER_T*              pt_this = &t_g_pwr;
    NAV_CONTEXT_T*                  pt_ctx = NULL;
    _NAV_PWR_COND_STATUS_T          e_status = _NAV_PWR_COND_STATUS_EMPTY;

    pt_ctx = nav_get_context();

    if(pt_this->b_is_normal)
    {
        /* Force stop the timer do matter TV/AV (VGA) */
        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               NAV_PWR_UI_FORCE_STOP_TIMER,
                                               NULL);

        e_status = _NAV_PWR_COND_STATUS_OFF;  /* Always set off if input src changed */
    }

    i4_ret = _nav_pwr_update_src_type(pt_this, pt_ctx->t_svc_res.e_focus_tv_win_id, NULL);
    if(NAVR_OK != i4_ret)
    {
        return;
    }

    if(_NAV_PWR_COND_STATUS_EMPTY != e_status)
    {
        /*If this component is disabled or MENU/DPMS is OFF*/
        if((FALSE == pt_this->b_enabled || FALSE == pt_this->b_dpms_enabled)
            && _NAV_PWR_COND_STATUS_ON == e_status)
        {
            if(NAV_PWR_SRC_TYPE_VGA != pt_this->e_src_type)
            {
                e_status = _NAV_PWR_COND_STATUS_OFF;
            }
        }

        if(e_status != pt_this->t_last_notify.b_is_meet)   /*ON <--> OFF*/
        {
            pt_this->t_last_notify.b_is_meet = e_status;

            pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                                   NAV_PWR_UI_IF_MEET_COND,
                                                   &pt_this->t_last_notify);
        }
    }
}

static VOID _nav_pwr_dpms_cfg_change_msg_hdlr(VOID*              pv_unused,
                                                             VOID*              pv_unused2,
                                                             VOID*              pv_unused3)
{
    _NAV_PWR_MEMBER_T*   pt_this        = &t_g_pwr;
    BOOL                 b_dpms_enabled = FALSE;
    INT32                i4_ret;
    i4_ret = a_cfg_get_dpms(&b_dpms_enabled);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("[Power] a_cfg_get_dpms error : %d\n",i4_ret));
        return;
    }

    pt_this->b_dpms_enabled = b_dpms_enabled;

    if(pt_this->b_dpms_enabled)
    {
        /* Refresh current status */
        if(_nav_pwr_refresh_current_status() != NAVR_OK)
        {
            return;
        }
    }
    else
    {
         pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                                NAV_PWR_UI_FORCE_STOP_TIMER,
                                                NULL);
    }
}

static INT32 _nav_pwr_cast_icl_nfy_cb(UINT16                 ui2_nfy_id,
                                  VOID*                 pv_tag,
                                  ICL_NOTIFY_DATA_T*    pt_notify_data)
{
    INT32               i4_ret     = NAVR_OK;
    UINT8               ui1_status = ICL_RECID_CAST_SRC_STATUS_FALSE;
    SIZE_T              z_size     = ICL_RECID_CAST_SRC_STATUS_SIZE;
    ICL_GRPID_TYPE         e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);

    if (e_grp_id != ICL_GRPID_CAST_SRC_STATUS)
    {
        return NAVR_OK;
    }

    i4_ret = a_icl_get (ICL_MAKE_ID(ICL_GRPID_CAST_SRC_STATUS, ICL_RECID_CAST_SRC_STATUS), &ui1_status, &z_size);
    if (ICLR_OK != i4_ret || ui1_status == ICL_RECID_CAST_SRC_STATUS_FALSE)
    {
        return NAVR_OK;
    }

    nav_request_context_switch(_nav_pwr_cast_icl_msg_hdlr,
                               NULL,
                               NULL,
                               NULL);
    return NAVR_OK;
}

static VOID _nav_pwr_3rd_play_icl_msg_hdlr(
                    VOID*            pv_unused1,
                    VOID*            pv_unused2,
                    VOID*            pv_unused3
                    )
{
    _NAV_PWR_MEMBER_T*              pt_this = &t_g_pwr;
	TV_WIN_ID_T                 t_win_id;
	ISL_REC_T                   t_isl_rec;
    _NAV_PWR_COND_STATUS_T          e_status = _NAV_PWR_COND_STATUS_EMPTY;
	BOOL    b_pre_status = pt_this->t_last_notify.b_is_meet;
	UINT8 ui1_play_status = (UINT8) (((UINT32) pv_unused1) & 0x000000FF);
	DBG_LOG_PRINT(("%s_%d  ui1_play_status:%d \n",__FUNCTION__,__LINE__,ui1_play_status));
    if((FALSE == pt_this->b_enabled || FALSE == pt_this->b_dpms_enabled))
    {
        return;
    }
    a_tv_get_isl_rec_by_win_id(t_win_id,&t_isl_rec);
    if((a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_PAUSED)&&
      (t_isl_rec.t_avc_info.e_video_type != DEV_VTRL_CAST))
    {
        return;
    }
    if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status())
    {
		if(ui1_play_status > 0)
		{
			pt_this->t_last_notify.b_is_meet = FALSE;
		}
		else
		{
			pt_this->t_last_notify.b_is_meet = TRUE;
		}
		DBG_LOG_PRINT(("%s_%d  b_is_meet:%d \n",__FUNCTION__,__LINE__,pt_this->t_last_notify.b_is_meet));
		if(b_pre_status != pt_this->t_last_notify.b_is_meet)
		{
			pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
									   NAV_PWR_UI_IF_MEET_COND,
									   &pt_this->t_last_notify);
		}

    }


}


static INT32 _nav_pwr_3rd_play_nfy_cb(UINT16                 ui2_nfy_id,
                                  VOID*                 pv_tag,
                                  ICL_NOTIFY_DATA_T*    pt_notify_data)
{
    INT32               i4_ret     = NAVR_OK;
    UINT8               ui1_status = ICL_RECID_CAST_SRC_STATUS_FALSE;
    SIZE_T              z_size     = ICL_RECID_CAST_SRC_STATUS_SIZE;
    ICL_GRPID_TYPE         e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    if (e_grp_id != ICL_GRPID_3RD_PLAY_STATUS)
    {
        return NAVR_OK;
    }

    i4_ret = a_icl_get (ICL_MAKE_ID(ICL_GRPID_3RD_PLAY_STATUS, ICL_RECID_3RD_PLAY_STATUS), &ui1_status, &z_size);
    if (ICLR_OK != i4_ret)
    {
        return NAVR_OK;
    }

    nav_request_context_switch(_nav_pwr_3rd_play_icl_msg_hdlr,
                               (VOID*) ui1_status,
                               NULL,
                               NULL);
    return NAVR_OK;
}


static VOID _nav_pwr_svctx_notify_fct(HANDLE_T                    h_svctx,          /* in  */
                                          SVCTX_COND_T                e_nfy_cond,       /* in  */
                                          SVCTX_NTFY_CODE_T           e_code,           /* in  */
                                          STREAM_TYPE_T               e_stream_type,    /* in  */
                                          VOID*                       pv_nfy_tag        /* in  */
                                          )
{
    if(FALSE == t_g_pwr.b_dpms_enabled)
    {
        return ;
    }

    if(e_nfy_cond == SVCTX_COND_PENDING_SELECT_SAME_REQ ||
       e_nfy_cond == SVCTX_COND_PRESENTING_SELECT_SAME_REQ)
    {
        switch(e_code){
        case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
            break;
        default:
            return;
        }
    }

    if((e_code == SVCTX_NTFY_CODE_SIGNAL_LOCKED)             ||
       (e_code == SVCTX_NTFY_CODE_SIGNAL_LOSS)               ||
       (e_code == SVCTX_NTFY_CODE_SERVICE_BLOCKED)           ||
       (e_code == SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE)          ||
       (e_code == SVCTX_NTFY_CODE_AUDIO_FMT_UPDATE)          ||
       (e_code == SVCTX_NTFY_CODE_STOPPED))
    {
        /*post a message to itself*/
        nav_request_context_switch(_nav_pwr_svctx_msg_hdlr,
                                    (VOID*)e_nfy_cond,
                                    (VOID*)e_code,
                                    (VOID*)e_stream_type);
    }
}

static VOID _nav_pwr_svctx_msg_hdlr(
    VOID*                               pv_tag1,
    VOID*                               pv_tag2,
    VOID*                               pv_tag3)
{
    INT32                           i4_ret = NAVR_OK;
    _NAV_PWR_COND_STATUS_T          e_status = _NAV_PWR_COND_STATUS_EMPTY;
    _NAV_PWR_MEMBER_T*              pt_this = &t_g_pwr;
    SVCTX_NTFY_CODE_T               e_code = (SVCTX_NTFY_CODE_T)pv_tag2;

    switch (e_code)
    {
        case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
        case SVCTX_NTFY_CODE_AUDIO_FMT_UPDATE:
            if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status() &&
               FALSE == msg_convert_custom_browser_ctrl_active())//Airplay
            {
                break;
            }
        case SVCTX_NTFY_CODE_SIGNAL_LOCKED:
            {
                {
                    TV_WIN_ID_T     e_win_id      = TV_WIN_ID_MAIN ;
                    LOCKED_STATUS_T e_lock_status = LOCKED_STATUS_NONE;

                    i4_ret = nav_get_focus_id (&e_win_id) ;
                    if (i4_ret != NAVR_OK) {
                        return;
                    }

                    e_lock_status = nav_get_locked_status(e_win_id);

                    if ((LOCKED_STATUS_PROGRAM_RATING == e_lock_status) ||
                        (LOCKED_STATUS_CHANNEL_LOCKED == e_lock_status) ||
                        (LOCKED_STATUS_INP_SRC_LOCKED == e_lock_status))
                    {
                        break;
                    }
                }
                {
                    if(_nav_pwr_is_cond_type_match(pt_this) && pt_this->b_is_normal)
                    {
                        e_status = _NAV_PWR_COND_STATUS_OFF;
                    }

                    if(FALSE == pt_this->b_is_normal)
                    {
                        if(FALSE == nav_is_signal_loss(TV_WIN_ID_MAIN) || FALSE == nav_is_signal_loss(TV_WIN_ID_SUB))
                        {
                            e_status = _NAV_PWR_COND_STATUS_OFF;
                        }
                    }
                }
            }
            break;
        case SVCTX_NTFY_CODE_SIGNAL_LOSS:
        case SVCTX_NTFY_CODE_SERVICE_BLOCKED:
            {
                if(TRUE == _nav_pwr_is_auto_power_off_func_active())
                {
                    _nav_pwr_get_cond_status_for_signal_loss(pt_this, &e_status);
                }
            }
            break;
        case SVCTX_NTFY_CODE_STOPPED:
            if(msg_convert_custom_airplay_active())
            {
                if(TRUE == _nav_pwr_is_auto_power_off_func_active())
                {
                    _nav_pwr_get_cond_status_for_signal_loss(pt_this, &e_status);
                }
            }
            break;
        default:
            return;
    }

    if(e_status != _NAV_PWR_COND_STATUS_EMPTY)
    {
        if(e_status != pt_this->t_last_notify.b_is_meet)   /*ON <--> OFF*/
        {
            pt_this->t_last_notify.b_is_meet = e_status;
            pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                                   NAV_PWR_UI_IF_MEET_COND,
                                                   &pt_this->t_last_notify);
        }
    }
}

static VOID _nav_pwr_iom_nfy_fct (
                          VOID*             pv_nfy_tag,
                          IOM_NFY_COND_T    e_nfy_cond,
                          UINT32            ui4_evt_code,
                          UINT32            ui4_data
                          )
{
    if (e_nfy_cond == IOM_NFY_COND_BTN_DOWN ||
        e_nfy_cond == IOM_NFY_COND_BTN_REPEAT)
    {
        /*post a message to itself*/
        nav_request_context_switch(_nav_pwr_iom_nfy_hdlr,
                                   (VOID*)e_nfy_cond,
                                   (VOID*)ui4_evt_code,
                                   (VOID*)ui4_data);
    }
}

static VOID _nav_pwr_iom_nfy_hdlr(
    VOID*                               pv_nfy_cond,
    VOID*                               pv_evt_code,
    VOID*                               pv_data)
{
    IOM_NFY_COND_T                 e_nfy_cond = (IOM_NFY_COND_T)((UINT32)pv_nfy_cond);
    _NAV_PWR_MEMBER_T*             pt_this = &t_g_pwr;

    if(IOM_NFY_COND_BTN_DOWN  != e_nfy_cond)
    {
        return;
    }

    if(FALSE == _nav_pwr_is_auto_power_off_func_active())
    {
        return;
    }

    NAV_LOG_ON_FAIL(nav_pwr_view_update_status(pt_this->pv_view));
}


VOID nav_pwr_system_ui_key_nfy(VOID)
{
    _NAV_PWR_MEMBER_T*             pt_this = &t_g_pwr;
    NAV_LOG_ON_FAIL(nav_pwr_view_update_status(pt_this->pv_view));
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_cfg_change_msg_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_pwr_cfg_change_msg_hdlr(
    VOID*                               pv_unused,
    VOID*                               pv_unused2,
    VOID*                               pv_unused3)
{
    _NAV_PWR_MEMBER_T*                  pt_this = &t_g_pwr;
    INT32                               i4_ret;
    UINT8                               ui1_factory_mode;

    /*Get factory mode*/
    i4_ret = a_cfg_get_factory_mode(&ui1_factory_mode);
    if(APP_CFGR_OK != i4_ret)
    {
        ui1_factory_mode = APP_CFG_FAC_MODE_NORMAL;
    }

#ifdef APP_NAV_POWER_SAVING_OFF_IN_FACTORY_MODE
    /*Check if factory or burning mode is on*/
    if((APP_CFG_FAC_MODE_NORMAL != ui1_factory_mode) &&
       (TRUE == pt_this->t_last_notify.b_is_meet))
#else
    /*Check if Burning mode is on*/
    if((APP_CFG_FAC_MODE_BURNING_MASK & ui1_factory_mode) &&
       (TRUE == pt_this->t_last_notify.b_is_meet))
#endif
    {
        pt_this->t_last_notify.b_is_meet = FALSE;

        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               NAV_PWR_UI_IF_MEET_COND,
                                               &pt_this->t_last_notify);
    }
}

static BOOL is_src_type_valid(const NAV_XNG_SRC_TRGT_T* pt_xng_info)
{
    if(NULL == pt_xng_info)
    {
        return FALSE;
    }

    switch(pt_xng_info->e_type)
    {
        case INP_SRC_TYPE_MM:
        case INP_SRC_TYPE_TV:
        case INP_SRC_TYPE_AV:
        case INP_SRC_TYPE_1394:
        case INP_SRC_TYPE_VTRL:
          {
              return TRUE;
          }
          break;
        default:
           return FALSE;
           break;
    }

}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_check_src_type
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/

static NAV_PWR_SRC_TYPE_T _nav_pwr_check_src_type(_NAV_PWR_MEMBER_T*        pt_this,
                                                          TV_WIN_ID_T               e_focus,
                                                          const NAV_XNG_SRC_TRGT_T* pt_xng_info)
{

    ISL_REC_T                         t_isl_rec;
    INP_SRC_TYPE_T                    e_grp_type;
    INT32                             i4_ret;
    NAV_PWR_SRC_TYPE_T                e_src_type = NAV_PWR_SRC_TYPE_UNKNOWN;

    e_grp_type = (is_src_type_valid(pt_xng_info)) ? pt_xng_info->e_type : nav_get_src_type(e_focus);

    if(INP_SRC_TYPE_TV == e_grp_type)
    {
        e_src_type = NAV_PWR_SRC_TYPE_TV;
    }
    else if(INP_SRC_TYPE_AV == e_grp_type || INP_SRC_TYPE_VTRL == e_grp_type)
    {
        if(is_src_type_valid(pt_xng_info))
        {
            i4_ret = a_isl_get_rec_by_id(pt_xng_info->u.t_av.ui1_trgt_inp_src_id, &t_isl_rec);
        }
        else
        {
              UINT8       ui1_input_id = 0;
              a_cfg_get_input_src(SN_PRES_MAIN_DISPLAY, &ui1_input_id);
             i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
        }

        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): Fail to get isl rec. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
            return NAVR_FAIL;
        }

        /* CR[DTV00067301] Fix auto power off isue after change source to TV from AV */
        if (INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
        {
            /* Force unset VGA flag when input source change to TV from AV */
            e_src_type = NAV_PWR_SRC_TYPE_TV;
        }
        else if(INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type)
        {
            e_src_type = NAV_PWR_SRC_TYPE_VTRL;
        }
        else if(DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type)
        {
            /* Set VGA flag */
            e_src_type = NAV_PWR_SRC_TYPE_VGA;
        }
        else if(ISL_ATTR_BIT_DVD_BUNDLE & t_isl_rec.ui4_attr_bits)
        {
            e_src_type = NAV_PWR_SRC_TYPE_DVD;
        }
        else
        {
            e_src_type = NAV_PWR_SRC_TYPE_OTHER;
        }

    }
    DBG_INFO(("[Power] check src type :%d  \n",e_src_type));
    return e_src_type;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_update_src_type
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_update_src_type(
    _NAV_PWR_MEMBER_T*                pt_this,
    TV_WIN_ID_T                       e_focus,
    const NAV_XNG_SRC_TRGT_T*         pt_xng_info)
{
    pt_this->e_src_type = _nav_pwr_check_src_type(pt_this,e_focus,pt_xng_info);

    /* insert the input src to notify, will be transfer to view */
    pt_this->t_last_notify.e_src_type = pt_this->e_src_type;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_is_cond_type_match
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_pwr_is_cond_type_match(
    _NAV_PWR_MEMBER_T*      pt_this)
{
    /* VGA Mode */
    if(pt_this->b_is_normal && (NAV_PWR_ONC_VGA_NO_SIGNAL & pt_this->e_on_cond) && (NAV_PWR_SRC_TYPE_VGA == pt_this->e_src_type))
    {
        return TRUE;
    }

    /* TV Mode */
    if(pt_this->b_is_normal && (NAV_PWR_ONC_TV_NO_SIGNAL & pt_this->e_on_cond) && (NAV_PWR_SRC_TYPE_TV == pt_this->e_src_type))
    {
        return TRUE;
    }

    /*DVD Mode*/
    if(pt_this->b_is_normal && (NAV_PWR_ONC_DVD_NO_SIGNAL & pt_this->e_on_cond) && (NAV_PWR_SRC_TYPE_DVD == pt_this->e_src_type))
    {
        return TRUE;
    }

    /* SCH */
    if(pt_this->b_is_normal && (NAV_PWR_ONC_AV_NO_SIGNAL & pt_this->e_on_cond) && (NAV_PWR_SRC_TYPE_VTRL == pt_this->e_src_type))
    {
        return TRUE;
    }

    /*Other AV Mode*/
    if(pt_this->b_is_normal && (NAV_PWR_ONC_AV_NO_SIGNAL & pt_this->e_on_cond) && (NAV_PWR_SRC_TYPE_OTHER == pt_this->e_src_type))
    {
        return TRUE;
    }

    if(FALSE == pt_this->b_is_normal)
    {
        if(nav_is_signal_loss(TV_WIN_ID_MAIN) && nav_is_signal_loss(TV_WIN_ID_SUB))
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_get_cond_status_for_signal_loss
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_get_cond_status_for_signal_loss(_NAV_PWR_MEMBER_T* pt_this,_NAV_PWR_COND_STATUS_T* pe_status)
{
    UINT8                       ui1_factory_mode;
    INT32                       i4_ret;

    if (NULL == pe_status)
    {
        return NAVR_INV_ARG;
    }

    /*Get factory mode*/
    i4_ret = a_cfg_get_factory_mode(&ui1_factory_mode);
    if(APP_CFGR_OK != i4_ret)
    {
        ui1_factory_mode = APP_CFG_FAC_MODE_NORMAL;
    }

#ifdef APP_NAV_POWER_SAVING_OFF_IN_FACTORY_MODE
    /*Check if factory or burning mode is on*/
    if(APP_CFG_FAC_MODE_NORMAL != ui1_factory_mode)
#else
    /*Check if Burning mode is on*/
    if(APP_CFG_FAC_MODE_BURNING_MASK & ui1_factory_mode)
#endif
    {
        *pe_status = _NAV_PWR_COND_STATUS_OFF;
    }
    else
    {
        if(_nav_pwr_is_cond_type_match(pt_this))
        {
            *pe_status = _NAV_PWR_COND_STATUS_ON;
        }
        else
        {
            *pe_status = _NAV_PWR_COND_STATUS_OFF;
        }
    }

    return NAVR_OK;
}

#endif /*APP_NAV_PWR_SUPPORT*/

