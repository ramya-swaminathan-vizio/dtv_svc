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
 * $RCSfile: revolt_misc.c,v $
 * $Revision: #1 $
 * $Date: 2016/01/21 $
 * $Author: sin_fangyuan $
 * $CCRevision:  $
 * $SWAuthor: W $
 * $MD5HEX:  $
 *
 * Description:
 *       System Info
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
#include "wizard_anim/a_wzd.h"

#include "nav/a_navigator.h"
#include "nav/revolt_misc/revolt_misc.h"
#include "nav/revolt_misc/revolt_misc_view.h"

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
#include "msgconvert/msgconvert.h"

#include "wizard/wzd_util.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "app_util/a_network.h"
#include "nav/sys_info/a_sys_info.h"
#include "res/nav/nav_dbg.h"



/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define RET_ON_ERR(_expr)  \
if(_expr != 0)\
{\
    DBG_ERROR (("<REVOLT_MISC> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__)); \
    return _expr;\
}

#define REVOLT_MISC_POWER_ON_TIMER_DELAY     500

typedef struct _REVOLT_MISC_T
{
    HANDLE_T h_app;
}REVOLT_MISC_T;


/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_REVOLT_MISC_T   t_g_revolt_misc;
static BOOL b_is_resume = FALSE;
static BOOL b_first_power_on_to_show = FALSE;

extern BOOL a_revolt_misc_power_seq_cb(VOID);
/*-----------------------------------------------------------------------------
 * static function implementations
 *---------------------------------------------------------------------------*/
static INT32 _revolt_misc_init(
    NAV_CONTEXT_T*   pt_ctx);

static INT32 _revolt_misc_deinit(VOID);

static BOOL _revolt_misc_is_key_handler(
    NAV_CONTEXT_T*              pt_ctx,
    UINT32                      ui4_key_code);

static INT32 _revolt_misc_activate(
    NAV_CONTEXT_T*             pt_ctx,
    UINT32                     ui4_key_code);

static INT32 _revolt_misc_inactivate(
    NAV_CONTEXT_T*     pt_ctx);

static INT32 _revolt_misc_hide (VOID);


/*-------------------------------------------------------------------------
 * Name
 *     _revolt_misc_power_seq_cb
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *-------------------------------------------------------------------------*/

static BOOL _revolt_misc_power_seq_cb(VOID)
{
    BOOL b_resume = FALSE;
    UINT16 ui2_status = APP_CFG_WZD_STATUS_INIT;
    UINT16 ui2_real_status = APP_CFG_WZD_STATUS_INIT;
    INT32 i4_rc = 0;
    PCL_WAKE_UP_REASON_T    e_wake_up_reason = PCL_WAKE_UP_REASON_UNKNOWN;

    //Get the wakeup reason/sub-reason
    i4_rc = c_pcl_get_wakeup_reason (& e_wake_up_reason, NULL);

    DBG_LOG_PRINT(("<REVOLT_MISC>%s,%d,4_rc=%d,e_wake_up_reason = %d\n",__FILE__,__LINE__,i4_rc,e_wake_up_reason));

    if (i4_rc != PCLR_OK)
    {
        DBG_ERROR(("<REVOLT_MISC> ERR: c_pcl_get_wakeup_reason failed = %d\n\r", i4_rc));
    }
    else
    {
        DBG_ERROR(("<REVOLT_MISC> e_wake_up_reason = %d\n",e_wake_up_reason));
    }

    if (e_wake_up_reason == PCL_WAKE_UP_REASON_CUSTOM_2)
    {
        if (a_cfg_get_wzd_status (&ui2_status) == APP_CFGR_OK)
        {
            ui2_real_status = WZD_UTIL_GET_STATUS_STATE( ui2_status );
            DBG_LOG_PRINT(( "[REVOLT_MISC]%s,%d,ui2_status = %d\n", __FILE__,__LINE__,ui2_real_status ));

            if (ui2_real_status == WZD_STATE_RESUME_C4TV_END)
            {
                b_resume = TRUE;
            }
        }
    }

    DBG_INFO(("<REVOLT_MISC> file=%s,line=%d,ui2_status=%d, b_resume = %d\n",__FILE__,__LINE__,ui2_status,b_resume));

    return b_resume;
}

BOOL a_revolt_misc_power_seq_cb(VOID)
{
	return _revolt_misc_power_seq_cb();
}


/*-----------------------------------------------------------------------------
 * Name: _revolt_misc_iom_nfy_hdlr
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _revolt_misc_iom_nfy_hdlr (VOID*           pv_tag1,
                                        VOID*                       pv_tag2,
                                        VOID*                       pv_tag3)
{
    IOM_NFY_COND_T                  e_nfy_cond      = (IOM_NFY_COND_T)(UINT32)pv_tag1;
    UINT32                          ui4_evt_code = (UINT32)pv_tag2;

    switch(ui4_evt_code)
    {
		case BTN_RETURN:
        case BTN_EXIT:
        case BTN_INPUT_SRC:
		case BTN_MENU:
		case BTN_VOL_UP:
		case BTN_VOL_DOWN:
        {
			// hide the view
			 revolt_misc_view_hide();
			 nav_return_activation(NAV_COMP_ID_REVOLT_MISC);
        }
		
        default:
            break;
    }
   
}

/*-----------------------------------------------------------------------------
 * Name: _revolt_misc_iom_nfy_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _revolt_misc_iom_nfy_fct (
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
        nav_request_context_switch(_revolt_misc_iom_nfy_hdlr,
                                   (VOID*)e_nfy_cond,
                                   (VOID*)ui4_evt_code,
                                   (VOID*)ui4_data);

    }
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _revolt_misc_init
 * Description:
 *      system info initialization.
 * Input arguments:
 *      pt_ctx
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _revolt_misc_init(
           NAV_CONTEXT_T*   pt_ctx)
{
    INT32               i4_ret = NAVR_OK;
    NAV_REVOLT_MISC_T*  pt_this = &t_g_revolt_misc;
    IRRC_SETTING_T      t_irrc_setting;

    pt_this->b_is_on = FALSE;
    // init the widgets
    i4_ret = revolt_misc_view_init(pt_ctx->t_gui_res.h_canvas);

    RET_ON_ERR(i4_ret);

    /* IOM open */
    {
        c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
        t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
        t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = 50; /* No repeat key */
        t_irrc_setting.t_rpt_evt_itvl.ui2_other = 20; /* No repeat key */
        t_irrc_setting.b_notify_raw_data        = TRUE;

        i4_ret = c_iom_open(
                        IOM_DEV_TYPE_IN_IRRC,
                        IOM_DEV_ID_ANY,
                        NULL,
                        &t_irrc_setting,
                        NULL,
                        _revolt_misc_iom_nfy_fct,
                        & pt_this->h_iom
                        );
        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _revolt_misc_deinit
 * Description:
 *      system info deinitialization.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _revolt_misc_deinit(VOID)
{

    INT32           i4_ret = NAVR_OK;
    NAV_REVOLT_MISC_T* pt_this = &t_g_revolt_misc;

    pt_this->b_is_on = FALSE;

    i4_ret = revolt_misc_view_deinit();
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _revolt_misc_is_key_handler
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
static BOOL _revolt_misc_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code)
{
    return FALSE;

}

/*-----------------------------------------------------------------------------
 * Name:
 *     _revolt_misc_activate
 * Description:
 *      system info activation.
 * Input arguments:
 *      pt_ctx
 *      ui4_key_code
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _revolt_misc_activate(
                    NAV_CONTEXT_T*             pt_ctx,
                    UINT32                     ui4_key_code)
{
    NAV_REVOLT_MISC_T* pt_this = &t_g_revolt_misc;

    pt_this->b_is_on = TRUE;

    nav_set_component_visible(NAV_COMP_ID_REVOLT_MISC);
    nav_grab_activation(NAV_COMP_ID_REVOLT_MISC);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _ _revolt_misc__inactivate
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
static INT32 _revolt_misc_inactivate(NAV_CONTEXT_T*     pt_ctx)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _revolt_misc_hide
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
static INT32 _revolt_misc_hide (VOID)
{
    INT32              i4_ret = NAVR_OK;
    NAV_REVOLT_MISC_T* pt_this = &t_g_revolt_misc;
	
	if (b_first_power_on_to_show == TRUE)
	{
		b_first_power_on_to_show = FALSE;
		return NAVR_OK;
	}

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    pt_this->b_is_on = FALSE;

    // hide the view
    i4_ret = revolt_misc_view_hide();
    RET_ON_ERR(i4_ret);

    nav_return_activation(NAV_COMP_ID_REVOLT_MISC);

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _revolt_misc_network_sys_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _revolt_misc_network_sys_info (
    SI_INFO_CTRL_T              e_info_ctrl ,
    TV_WIN_ID_T                 e_tv_win_id ,
    SI_SET_INFO_T*              pt_si_info ,
    VOID*                       pv_tag
    )
{
    NAV_REVOLT_MISC_T* pt_this = &t_g_revolt_misc;
    SI_CUST_INFO_1_T*           pt_custom_info = NULL ;

    /* check validation */
    if (!pt_si_info ||
        pt_si_info->e_category != SI_CATEGORY_CUSTOM_1)
    {
        RET_ON_ERR(NAVR_INV_ARG) ;
    }

    /* get custom info */
    pt_custom_info = &pt_si_info->u.t_cust_info_1 ;

    if (pt_custom_info->ui4_info_mask & SI_CUSTOM_INFO_MASK_NETWORK_INFO)
    {
        if(pt_this->b_is_on)
        {
            revolt_misc_view_update_data();
        }
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _revolt_misc_sys_info_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _revolt_misc_sys_info_handler (
                                            SI_INFO_CTRL_T              e_info_ctrl ,
                                            TV_WIN_ID_T                 e_tv_win_id ,
                                            SI_SET_INFO_T*              pt_si_info ,
                                            VOID*                       pv_tag)
{
    /* check validate */
    if (!pt_si_info)
    {
        return NAVR_INV_ARG;
    }

    /* as sys info module is one of navigator's component, we need not change the thread */

    /* switch to sub-handler */
    switch (pt_si_info->e_category)
    {
    case SI_CATEGORY_CUSTOM_1:
        _revolt_misc_network_sys_info (e_info_ctrl, e_tv_win_id, pt_si_info, pv_tag);
        break ;
    default :
        /* Do nothing */
        break ;
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _revolt_misc_network_info_handler_init
 * Description:
 *      _revolt_misc_sys_info_handler_init.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _revolt_misc_sys_info_handler_init(VOID)
{
    INT32   i4_ret = NAVR_OK;
    UINT16  ui2_si_listener_id = 0;

    i4_ret = a_si_listener_register (_revolt_misc_sys_info_handler,
                            NULL ,
                            &ui2_si_listener_id);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *     _revolt_misc_handle_msg
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
static INT32 _revolt_misc_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1)
{
    switch (pt_ui_msg->e_id)
    {
	  	case NAV_UI_MSG_SYSTEM_POWER_ON:
		{
				b_first_power_on_to_show = TRUE;

	            break;
	    }
#if 0
    //case NAV_UI_MSG_POWER_ON:
        {
            b_is_resume = _revolt_misc_power_seq_cb();
            DBG_LOG_PRINT(("<revolt_misc> NAV_UI_MSG_SYSTEM_POWER_ON %s,%d,%d,%d,%d\n\r",__FILE__,__LINE__,b_is_resume,
                                        pt_ui_msg->e_id,nav_is_active()));

            if(b_is_resume && nav_is_active())
            {
                revolt_misc_view_show();
            }
            break;
        }
#endif
    case NAV_UI_MSG_APP_RESUMED:
        {
            DBG_LOG_PRINT(("<revolt_misc> NAV_UI_MSG_APP_RESUMED %s,%d,%d,%d,%d\n\r",__FILE__,__LINE__,b_is_resume,
                                        pt_ui_msg->e_id,nav_is_resumed_from_app_switch()));
            if(!b_is_resume)
            {
               b_is_resume = _revolt_misc_power_seq_cb();
            }
            if(b_is_resume && (nav_is_resumed_from_app_switch() == false))
            {
                revolt_misc_view_show();
            }
        }
        break;
    case NAV_UI_MSG_POWER_OFF:
        break;
    case NAV_UI_MSG_APP_INITED:
         _revolt_misc_sys_info_handler_init();
        break;
    case NAV_UI_MSG_APP_PRE_RESUME:
        break;
    case NAV_UI_MSG_APP_PAUSING:
        {
            nav_return_activation(NAV_COMP_ID_REVOLT_MISC);
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
 *      a_revolt_misc_register
 * Description:
 *      The registration function of the system info component.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 a_nav_revolt_misc_register(VOID)
{
    NAV_COMP_T          t_comp;
    INT32               i4_ret = NAVR_OK;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    /* NAV_COMP_ID_SYSTEM_INFO */
    t_comp.pf_init           = _revolt_misc_init;
    t_comp.pf_deinit         = _revolt_misc_deinit;
    t_comp.pf_is_key_handler = _revolt_misc_is_key_handler;
    t_comp.pf_activate       = _revolt_misc_activate;
    t_comp.pf_inactivate     = _revolt_misc_inactivate;
    t_comp.pf_hide           = _revolt_misc_hide;
    t_comp.pf_handle_msg     = _revolt_misc_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_REVOLT_MISC, &t_comp, COMP_EXEC_SET_REVOLT_MISC);

    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

