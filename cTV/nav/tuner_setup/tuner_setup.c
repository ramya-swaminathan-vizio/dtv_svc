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
 * $RCSfile: tuner_setup.c,v $
 * $Revision: #1 $
 * $Date: 2016/02/03 $
 * $Author: sin_fangyuan $
 * $CCRevision:  $
 * $SWAuthor: W $
 * $MD5HEX:  $
 *
 * Description:
 *
 *
 *---------------------------------------------------------------------------*/
#include <stdio.h>
#include "u_common.h"
#include "u_wgl_sets.h"
#include "u_pcl.h"
#include "c_dbg.h"

#include "c_handle.h"
#include "c_gl.h"
#include "c_wgl.h"
#include "c_wgl_image.h"

#include "res/nav/nav_custom_comp_id.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_variant.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant_custom.h"
#include "wizard/a_wzd.h"

#include "nav/a_navigator.h"
#include "nav/tuner_setup/tuner_setup.h"
#include "nav/tuner_setup/tuner_setup_view.h"
#include "nav/tuner_setup/tuner_setup_cli.h"


#include "app_util/a_common.h"
#include "app_util/a_lbw.h"

#include "u_irrc_btn_def.h"
#include "c_uc_str.h"

#include "app_client.h"
#include "am/a_am.h"
#include "app_util/a_cfg.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "menu2/a_menu.h"
#include "res/nav/nav_variant.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/input_src/input_src.h"
#include "msgconvert/msgconvert.h"
#include "wizard_anim/a_wzd.h"
#include "wizard/wzd_util.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "res/nav/nav_dbg.h"
#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define RET_ON_ERR(_expr)  \
if(_expr != 0)\
{\
    TUNER_LOG_E("fail: %d\n\r", _expr); \
    return _expr;\
}

#define WZD_STATE_RESUME_C4TV                 MAKE_BIT_MASK_8 (5)

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_TUNER_SETUP_T t_g_nav_tuner_setup;
UINT32 ui4_tuner_log_level = 2;

static BOOL _tuner_setup_view_enable = TRUE;


/*-----------------------------------------------------------------------------
 * static function implementations
 *---------------------------------------------------------------------------*/
static INT32 _tuner_setup_init(
    NAV_CONTEXT_T*   pt_ctx);

static INT32 _tuner_setup_deinit(VOID);

static BOOL _tuner_setup_is_key_handler(
    NAV_CONTEXT_T*              pt_ctx,
    UINT32                      ui4_key_code);

static INT32 _tuner_setup_activate(
    NAV_CONTEXT_T*             pt_ctx,
    UINT32                     ui4_key_code);

static INT32 _tuner_setup_inactivate(
    NAV_CONTEXT_T*     pt_ctx);

static INT32 _tuner_setup_hide (VOID);


/*-----------------------------------------------------------------------------
 * Name:
 *      _tuner_setup_init
 * Description:
 *
 * Input arguments:
 *      pt_ctx
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _tuner_setup_init(
           NAV_CONTEXT_T*   pt_ctx)
{

    INT32               i4_ret = NAVR_OK;

    NAV_TUNER_SETUP_T* pt_this = &t_g_nav_tuner_setup;

    //DBG_LOG_PRINT(("<_tuner_setup_init>info:file=%s,line=%d\n\r",__FILE__,__LINE__));

    // init the widgets
    i4_ret = tuner_setup_view_init(pt_ctx->t_gui_res.h_canvas);

    RET_ON_ERR(i4_ret);
    pt_this->b_is_on = FALSE;

    /* init banner cli */
#ifdef CLI_SUPPORT
    i4_ret = tuner_setup_cli_init() ;
    if(i4_ret != 0)
    {
        DBG_LOG_PRINT(("<_tuner_setup_init>info:file=%s,line=%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        return AEER_FAIL;
    }

#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _tuner_setup_deinit
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _tuner_setup_deinit(VOID)
{

    INT32           i4_ret = NAVR_OK;

    i4_ret = tuner_setup_view_deinit();
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _tuner_setup_is_key_handler
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
static BOOL _tuner_setup_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code)
{
    return tuner_setup_view_is_key_handler_fct(pt_ctx, ui4_key_code);
}
static VOID _tuner_setup_start_scan_exit_demo_mode (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    tuner_setup_view_show();
}

/*-----------------------------------------------------------------------------
 * Name:
 *    _tuner_setup_activate
 * Description:
 *
 * Input arguments:
 *      pt_ctx
 *      ui4_key_code
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _tuner_setup_activate(
                    NAV_CONTEXT_T*             pt_ctx,
                    UINT32                     ui4_key_code)
{
    NAV_TUNER_SETUP_T* pt_this = &t_g_nav_tuner_setup;

    nav_grab_activation(NAV_COMP_ID_TUNER_SETUP);
    nav_set_component_visible(NAV_COMP_ID_TUNER_SETUP);

    pt_this->b_is_on = TRUE;
    switch(ui4_key_code)
    {
        case BTN_SELECT:
        //case BTN_PAUSE:
        //case BTN_PLAY:
            {
                if (TRUE == a_wzd_is_oobe_mode() || !_tuner_setup_view_enable)
				{
					break;
				}
                ACFG_RETAIL_MODE_T          t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
                RETAIL_MODE_RUNNING_TYPE_T  t_retail_mode_type = RETAIL_MODE_TYPE_OVERLAY;
                NAV_RETAIL_MODE_STATUS_T retm_status;
                a_nav_retail_mode_get_status(&retm_status);

                a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
                t_retail_mode_type = a_nav_retail_mode_get_running_type();

                if(retm_status == NAV_RETAIL_MODE_RUNNING || retm_status == NAV_RETAIL_MODE_PAUSE)
                {
                    break;
                }

                if(t_retail_mode == ACFG_RETAIL_MODE_NORMAL && t_retail_mode_type != RETAIL_MODE_TYPE_OVERLAY)
                {
                    TUNER_LOG_I("retail mode play video, cann't setup tuner.\n\r");
                    a_nav_retail_mode_exit();
                     nav_request_context_switch(_tuner_setup_start_scan_exit_demo_mode, NULL, NULL, NULL);
                    break;
                }

                tuner_setup_view_show();
            }
            break;

        default:
            break;
    }
    //_tuner_setup_view_show();

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _tuner_setup_inactivate
 * Description:
 *      system info inactivation.
 * Input arguments:
 *      pt_ctx
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _tuner_setup_inactivate(NAV_CONTEXT_T*     pt_ctx)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _tuner_setup_hide
 * Description:
 *      system info hide.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _tuner_setup_hide (VOID)
{

    INT32              i4_ret = NAVR_OK;

    NAV_TUNER_SETUP_T* pt_this = &t_g_nav_tuner_setup;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    // hide the view
    i4_ret = tuner_setup_view_hide();
    RET_ON_ERR(i4_ret);

    pt_this->b_is_on = FALSE;

    /* Return control. */
    nav_hide_component(NAV_COMP_ID_TUNER_SETUP);

    nav_return_activation(NAV_COMP_ID_TUNER_SETUP);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:
 *     _tuner_setup_handle_msg
 * Description:
 *
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
static INT32 _tuner_setup_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1)
{
    NAV_TUNER_SETUP_T* pt_this = &t_g_nav_tuner_setup;

    switch (pt_ui_msg->e_id)
    {
    case NAV_UI_MSG_POWER_OFF:
        {
            tuner_setup_view_hide();
            break;
        }
    case NAV_UI_MSG_POWER_ON:
        {
            break;
        }
    case NAV_UI_MSG_APP_RESUMED:
        if(tuner_setup_view_get_need_scan_after_resume())
        {

            INT32       i4_ret              = TSP_OK;
            nav_grab_activation(NAV_COMP_ID_TUNER_SETUP);
            i4_ret = tuner_setup_rest_view_show();
            if (i4_ret != TSP_OK)
            {
                TUNER_LOG_E("tuner_setup_rest_view_show,i4_ret=[%d] \r\n",i4_ret);
            }
        }
        break;
    case NAV_UI_MSG_REST_NOTIFICATION:
        {
            CHAR  s_name [APP_NAME_MAX_LEN + 1]     = { 0 };
            a_am_get_active_app (s_name);
            if(pt_this->b_is_on)
            {
                /* Scan should back to square one when in scanning */
                TUNER_LOG_I("NAV_UI_MSG_REST_NOTIFICATION,Scan should back to square one when in scanning \n\r");
                tuner_setup_view_reset_scan();
            }
            else if(a_get_current_menu_scan_statue()||(c_strcmp(s_name, "mmp") == 0)||(c_strcmp(s_name, "menu") == 0))
            {
                TUNER_LOG_I("NAV_UI_MSG_REST_NOTIFICATION,Scan should cancel the menu scan and start rest scan \n\r");
                tuner_setup_view_prepare_for_rest_scan();
            }
            else
            {
                TUNER_LOG_I("NAV_UI_MSG_REST_NOTIFICATION \n\r");
                UINT16  ui2_status    = 0;
                UINT8   ui1_state     = 0;

                RET_ON_ERR(a_cfg_get_wzd_status(&ui2_status));
                ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

                TUNER_LOG_I("tuner_setup_scan_oobe_state,state=%d\r\n",(int)ui1_state);
                if(WZD_STATE_RESUME_C4TV == ui1_state)
                {
                    TUNER_LOG_I("OOBE scan should not active Tuner setup component.\r\n");
                }
                else
                {
                    nav_grab_activation(NAV_COMP_ID_TUNER_SETUP);
                }

#ifdef APP_TTS_SUPPORT
                UTF16_T     w2s_str[32] = L"Channels Found";
                a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif

                tuner_setup_rest_view_show();
            }
            break;
        }

    case NAV_UI_MSG_REST_STOP_SCAN_TUNER:
        {
            if(pt_this->b_is_on)
            {
                TUNER_LOG_I("NAV_UI_MSG_REST_STOP_SCAN_TUNER \n\r");
                tuner_setup_view_hide();
                nav_set_channel_scan_active(FALSE);
                nav_hide_component(NAV_COMP_ID_TUNER_SETUP);
                nav_return_activation(NAV_COMP_ID_TUNER_SETUP);
            }
            break;
        }
    case NAV_UI_MSG_APP_PAUSING:
        {
            //nav_return_activation(NAV_COMP_ID_TUNER_SETUP);
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
 *      a_nav_tuner_setup_register
 * Description:
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 a_nav_tuner_setup_register(VOID)
{
    NAV_COMP_T          t_comp;
    INT32               i4_ret = NAVR_OK;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    /* NAV_COMP_ID_TUNNER_SETUP */
    t_comp.pf_init           = _tuner_setup_init;
    t_comp.pf_deinit         = _tuner_setup_deinit;
    t_comp.pf_is_key_handler = _tuner_setup_is_key_handler;
    t_comp.pf_activate       = _tuner_setup_activate;
    t_comp.pf_inactivate     = _tuner_setup_inactivate;
    t_comp.pf_hide           = _tuner_setup_hide;
    t_comp.pf_handle_msg     = _tuner_setup_handle_msg;


    i4_ret = nav_register_component(NAV_COMP_ID_TUNER_SETUP, &t_comp, COMP_EXEC_SET_TUNER_SETUP);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    return NAVR_OK;
}

BOOL a_tuner_setup_enable_set(BOOL val)
{
    _tuner_setup_view_enable = val;
    tuner_setup_warning_hide();
    return _tuner_setup_view_enable;
}

BOOL a_tuner_setup_enable_get(VOID)
{
    return _tuner_setup_view_enable;
}


