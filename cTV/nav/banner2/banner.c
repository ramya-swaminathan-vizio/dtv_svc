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
 *                                                                             *
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
 * $RCSfile: banner.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *---------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_scc.h"
#include "u_scdb.h"
#include "u_sm_cc_hdlr.h"
#include "c_svctx.h"
#include "c_handle.h"

#include "amb/a_amb.h"
#include "nav/nav_bnr_state_mgr.h"
#include "nav/input_src/a_input_src.h"
#include "banner.h"
#include "nav/input_src/input_src_list.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "../../../dev/app_util/mtktvapi/a_mtktvapi_banner.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_mlm.h"
#include "wdk/a_wdk.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#ifdef APP_BANNER_PARALLEL_HANDLE_MSG
#define NAV_BANNER_MSG_QUEUE_SIZE            2000
#define NAV_BANNER_THREAD_NAME               "nav_banner_thread"
#define NAV_BANNER_DEFAULT_STACK_SIZE        32768
#define NAV_BANNER_DEFAULT_THREAD_PRIORITY   127

typedef struct _NAV_BANNER_INTERNAL_MSG_T
{
    NAV_UI_MSG_ID_T   e_msg;
    VOID*             pv_param1;
    VOID*             pv_param2;
    VOID*             pv_param3;
} NAV_BANNER_INTERNAL_MSG_T;
typedef struct _NAV_BANNER_HANDLER_INFO_T
{
    HANDLE_T h_handler_msgq;
} NAV_BANNER_HANDLER_INFO_T;
#endif
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static BANNER_T t_g_banner;
static HANDLE_T h_sema_banner_mtx = NULL_HANDLE;

/* SPECIAL_NOTE_2010_12_15_001
 * Sometimes, when we switch application from Not-NAV to NAV,
 * some message which may change banner state was triggled automatic,
 * that will display banner.
 * In some case we don't want to show banner(such as enter menu and return to NAV).
 * to support this, we need check that NAV was switched from which application
 *
 * So, variable s_last_app_name was defineded.
 * The variable only valida during application switching.
 * To aviod the variable was changed or accessed in a inapposite time,
 * we have not put it into Struct BANNER_T
 *
 * PLEASE use following function to set/access the variable
 * _banner_set_last_app --> set last application's name
 * banner_get_last_app_when_switch_app  --> get last application's name
 */
static CHAR     s_last_app_name[APP_NAME_MAX_LEN + 1] ;

static WDK_OSD_TOAST_T  	t_g_wdk_view = {0};

#ifdef APP_BANNER_PARALLEL_HANDLE_MSG
static HANDLE_T  _h_banner_msgq = NULL_HANDLE;
extern INT32 x_thread_create(HANDLE_T    *ph_th_hdl,         /* thread handle */
            const CHAR  *ps_name,
            SIZE_T       z_stacksize,
            UINT8        ui1_pri,           /* thread priority */
            x_os_thread_main_fct pf_main,   /* thread's main function */
            SIZE_T       z_arg_size,
            VOID         *pv_arg);
#endif
/*-----------------------------------------------------------------------------
 * customization declarations
 *---------------------------------------------------------------------------*/
#ifndef COMP_EXEC_SET_BANNER
    #define COMP_EXEC_SET_BANNER     NAV_MAKE_NOT_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)
#endif

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _banner_hide (VOID) ;
static VOID banner_update_msg();
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
* private methods implementations
*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
*      _banner_set_last_app
* Description
* Input arguments
* Output arguments
* Returns
*---------------------------------------------------------------------------*/
static INT32 _banner_set_last_app (const CHAR* ps_app_name)
{
    /* Read SPECIAL_NOTE_2010_12_15_001 first before you use this function, */

    if (!ps_app_name)
    {
        return NAVR_INV_ARG ;
    }

    c_memset (s_last_app_name, 0 ,sizeof (s_last_app_name)) ;
    c_strncpy (s_last_app_name, ps_app_name, APP_NAME_MAX_LEN) ;
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE, (" app[%s] resume \n", s_last_app_name)) ;
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_state_changed_notify
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_state_changed_notify (
    UINT8                       ui1_state
    )
{
    BANNER_T*                   pt_this = &t_g_banner;
    BANNER_STATE_INFO_T*        pt_state_info = NULL ;

    BANNER_LOG (_BANNER_LOG_TYPE_STATE, ("---->change state to %s success\n", GET_STATE_DISP_NAME(ui1_state))) ;
    pt_state_info = banner_get_state_info (ui1_state) ;
    NAV_ASSERT (pt_state_info) ;
    BANNER_CHK_FAIL ( (pt_state_info) ? NAVR_OK : NAVR_FAIL) ;

    /* do pre-process */
    if (pt_state_info->pf_pre_process_when_enter)
    {
        pt_state_info->pf_pre_process_when_enter (ui1_state) ;
    }

    /* adjust view for the new state */
    BANNER_CHK_FAIL (banner_view_update_state (ui1_state)) ;

    /* save current state */
    pt_this->ui1_crnt_state   = ui1_state ;

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_item_update_notify
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_item_update_notify (
    UINT8                       ui1_item_id,
    UTF16_T*                    pw2s_text,          /* for text item */
    HANDLE_T                    h_icon              /* for icon item , 0 means set this icon to empty*/
    )
{
    /* update to banner view */
    BANNER_LOG_ON_FAIL (banner_view_update_item (ui1_item_id, pw2s_text, h_icon, !UP_TO_VIEW_AT_ONCE));

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_view_update_notify
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_view_update_notify (
                                         BOOL               b_pre_view_update,
                                         BNR_ITEM_SET_T     t_updated_mask    /* topmost-bit for STATE, others for ITEMS */
    )
{
    /* notify custom part that view updated/updating */
    if (b_pre_view_update)
    {
        BANNER_LOG_ON_FAIL (banner_custom_before_view_updated (t_updated_mask)) ;
    }
    else
    {
        BANNER_LOG_ON_FAIL (banner_custom_after_view_updated (t_updated_mask)) ;
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_listener
 * Description
 *      The API is used to listen the state changed or item updated notification
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static INT32 _banner_listener (
    BANNER_UPDATE_NFY_T         t_update
    )
{
    switch (t_update.e_nfy_type)
    {
    case BANNER_NFY_TYPE_UPDATE_STATE :
        BANNER_LOG_ON_FAIL (_banner_state_changed_notify (
                                t_update.u_nfy_data.t_up_state.ui1_state));
        break ;

    case BANNER_NFY_TYPE_UPDATE_ITEM :
        BANNER_LOG_ON_FAIL (_banner_item_update_notify (
                                t_update.u_nfy_data.t_up_item.ui1_item_id,
                                t_update.u_nfy_data.t_up_item.pw2s_text,
                                t_update.u_nfy_data.t_up_item.h_icon));
        break ;

    case BANNER_NFY_TYPE_PRE_UPDATE_VIEW :
        BANNER_LOG_ON_FAIL (_banner_view_update_notify (TRUE,
                                t_update.u_nfy_data.t_view_updated_mask_pre));
        break ;

    case BANNER_NFY_TYPE_POST_UPDATE_VIEW :
        BANNER_LOG_ON_FAIL (_banner_view_update_notify (FALSE,
                                t_update.u_nfy_data.t_view_updated_mask_post));
        break ;

    default :
        break ;
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _crnt_source_is_blocked
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _crnt_source_is_blocked (VOID)
{
    TV_WIN_ID_T                 e_tv_win_id = TV_WIN_ID_MAIN ;
    ISL_REC_T                   t_isl_rec = {0} ;
    SVL_REC_T                   t_svl_rec = {0} ;
    SVC_BLOCK_COND_T            e_svc_block_cond = SVC_BLOCK_COND_EXCEED_RATING ;

    BANNER_LOG_ON_FAIL (nav_get_focus_id (&e_tv_win_id)) ;
    BANNER_LOG_ON_FAIL (a_tv_get_isl_rec_by_win_id (e_tv_win_id, &t_isl_rec)) ;
    BANNER_LOG_ON_FAIL (nav_get_svl_rec (e_tv_win_id, &t_svl_rec)) ;

    e_svc_block_cond = a_tv_default_block_check_fct (
                                SVC_BLOCK_CHECK_USER_BLOCK ,
                                t_isl_rec.s_src_name ,
                                &t_svl_rec,
                                NULL) ;

    if (SVC_BLOCK_COND_USER_BLOCK_INP == e_svc_block_cond)
    {
        return TRUE ;
    }
    else
    {
        return FALSE ;
    }
}

/*-----------------------------------------------------------------------------
 * Name: banner_item_lock
 *
 * Description:
 *      The banner lock function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 banner_item_lock(VOID)
{
    return c_sema_lock(h_sema_banner_mtx, X_SEMA_OPTION_WAIT) == OSR_OK ?
           APP_CFGR_OK :
           APP_CFGR_INTERNAL_ERR;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_unlock
 *
 * Description:
 *      The banner unlokc function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 banner_item_unlock(VOID)
{
    return c_sema_unlock(h_sema_banner_mtx) == OSR_OK ?
           APP_CFGR_OK :
           APP_CFGR_INTERNAL_ERR;
}

static VOID _banner_gui_lang_nfy_cb(UINT16    ui2_nfy_id,
                                          VOID*    pv_tag,
                                          UINT16   ui2_id)
{
    if(CFG_MAKE_ID(APP_CFG_GRPID_GUI_LANG, APP_CFG_RECID_GUI_LANG) == ui2_id)
    {
        banner_update_msg();

        //just for aspect items(Normal,Zoom,Wide...),hdr content not changed by language
        banner_sys_info_update_hdr();
    }
}

/*-----------------------------------------------------------------------------
 * nav component related function
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_init(
    NAV_CONTEXT_T*              pt_ctx
    )
{
    BANNER_T*                   pt_this = &t_g_banner;

    c_memset(pt_this, 0, sizeof(BANNER_T));

    /* init custom data first as we need get state and item information to initial other part */
    BANNER_CHK_FAIL (banner_custom_init (pt_ctx->t_gui_res.h_canvas,
                                         pt_ctx->t_gui_res.e_color_type,
                                         &pt_this->pt_state_info,
                                         &pt_this->pt_item_info,
                                         &pt_this->ui2_state_num,
                                         &pt_this->ui2_item_num,
                                         &pt_this->h_root_frame)) ;

    /* init state manager */
    BANNER_CHK_FAIL (nav_bnr_state_mgr_init((UINT8)pt_this->ui2_state_num, 0)) ;

    /* init banner view (init all items) */
    BANNER_CHK_FAIL (banner_view_init (pt_this,
                                       pt_this->h_root_frame,
                                       _banner_listener)) ;
/* init banner cli */
#ifdef CLI_SUPPORT
    BANNER_CHK_FAIL (banner_cli_init (pt_this)) ;
#endif

   BANNER_CHK_FAIL(c_sema_create(&h_sema_banner_mtx,
                           X_SEMA_TYPE_MUTEX,
                           X_SEMA_STATE_UNLOCK));
    if(!t_g_wdk_view.b_have_init)
    {
        WDK_TOAST_PARAM_T  tg_toast_param;
        c_memset(&tg_toast_param, 0, sizeof(WDK_TOAST_PARAM_T));
        tg_toast_param.e_toast_style = WDK_SCREEN_CENTER_MSG;
        tg_toast_param.pf_cb         = NULL;
        BANNER_CHK_FAIL(a_wdk_toast_init(pt_ctx->t_gui_res.h_canvas,&tg_toast_param,&t_g_wdk_view));
    }

    /* init private data */
    pt_this->ui1_crnt_state     = 0 ;
    pt_this->ui1_def_tv_state   = 0 ;
    pt_this->b_excl_comp_is_on  = FALSE;

    /*register GUI lang notify*/
    BANNER_CHK_FAIL(a_cfg_notify_reg(APP_CFG_GRPID_GUI_LANG, NULL, _banner_gui_lang_nfy_cb, &pt_this->ui2_gui_lang_nfy));
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_deinit(
                    VOID
                    )
{
    BANNER_CHK_FAIL (banner_view_deinit()) ;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _banner_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _banner_is_key_handler (
    NAV_CONTEXT_T*              pt_ctx ,
    UINT32                      ui4_key_code
    )
{
    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_BANNER_UI))
    {
        return FALSE;
    }

    if (NAVR_DO_NOT_CONTINUE == banner_rcu_key_handler (ui4_key_code))
    {
        /* for these keys, banner handle them inside */
        return TRUE ;
    }
    else
    {
        return FALSE ;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_activate(
    NAV_CONTEXT_T*              pt_ctx,
    UINT32                      ui4_key_code
    )
{
    /* please note,
     * BANNER WILL NEVER ACTIVATE. (just show osd)
     * for some keys, banner do not want other component handle them,
     * he will activate himself first when receiving these keys (gain focus from navigator)
     * then, return to navigator with NAVR_NO_ACTION (return focus to navigator)
     * by this way, these keys which banner do not want other components handled
     * will be eat by banner and will not dispath to other components.
     */
    return NAVR_NO_ACTION ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_inactivate(
    NAV_CONTEXT_T*              pt_ctx
    )
{
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_hide (VOID)
{
    BANNER_T*                   pt_this = &t_g_banner ;
    UINT8                       ui1_idle_state = 0 ;
    UINT8                       ui1_cc_val  = ICL_CC_ITEM_STATUS_HIDE;

    /* 1) get idle state */
    ui1_idle_state = banner_custom_get_idle_state () ;

    /* 2) force to change state to IDLE */
    if (ui1_idle_state != pt_this->ui1_crnt_state)
    {
        BANNER_LOG (_BANNER_LOG_TYPE_STATE,("hide banner\n")) ;
        BANNER_CHK_FAIL (banner_change_state_to (
                                ui1_idle_state,
                                !NEED_SHOW_BANNER_VIEW,
                                UP_TO_VIEW_AT_ONCE)) ;
    }

    /* 3) force to stop timer */
    BANNER_LOG_ON_FAIL (nav_bnr_state_timer_op (
                                NAV_BNR_STATE_TMOT_STOP)) ;

    /* hide view */
    BANNER_LOG_ON_FAIL (banner_view_hide ()) ;

    /* return control to navigator */
    nav_return_activation ( NAV_COMP_ID_BANNER ) ;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_CC_ITEM_STATUS, ICL_RECID_CC_ITEM_STATUS),
              &ui1_cc_val, ICL_RECID_CC_ITEM_STATUS_SIZE);

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
#ifdef APP_BANNER_PARALLEL_HANDLE_MSG
static VOID _nav_banner_send_msg(HANDLE_T                     h_msg_hdl,
                                 NAV_BANNER_INTERNAL_MSG_T*   pt_msg,
                                 SIZE_T                       z_size,
                                 UINT8                        ui1_pri)
{
    INT32 i4_ret = OSR_OK;
    i4_ret = c_msg_q_send(h_msg_hdl, pt_msg, z_size, ui1_pri);
    if (i4_ret != OSR_OK)
    {
        while (i4_ret == OSR_TOO_MANY)
        {
            i4_ret = c_msg_q_send(h_msg_hdl,pt_msg,z_size,ui1_pri);
        }
    }
}
#endif

static INT32 _banner_handle_msg (
    NAV_CONTEXT_T*              pt_ctx,
    NAV_UI_MSG_T*               pt_ui_msg,
    VOID*                       pv_arg1
    )
{
#ifdef APP_BANNER_PARALLEL_HANDLE_MSG
    NAV_BANNER_INTERNAL_MSG_T  t_msg;

    t_msg.e_msg = pt_ui_msg->e_id;
    t_msg.pv_param1 = (VOID*)pt_ctx;
    t_msg.pv_param2 = (VOID*)pt_ui_msg;
    t_msg.pv_param3 = (VOID*)pv_arg1;

    _nav_banner_send_msg(_h_banner_msgq, &t_msg, sizeof(NAV_BANNER_INTERNAL_MSG_T), 255);
#else
    BANNER_T*                   pt_this = &t_g_banner ;

    if (NAV_UI_MSG_APP_INITED == pt_ui_msg->e_id)
    {
        /* init state handler (register all state to state mamager) */
        BANNER_CHK_FAIL (banner_state_handler_init (
                                _banner_listener )) ;

        /* init item handler */
        BANNER_CHK_FAIL (banner_sys_info_handler_init (
                                _banner_listener,
                                &pt_this->ui2_si_listener_id)) ;

        /* prset custom data */
        BANNER_CHK_FAIL (banner_custom_preset_data_when_nav_inited ());
    }
    #ifdef APP_ZOOM_MODE_SUPPORT
    if (NAV_UI_MSG_POWER_ON == pt_ui_msg->e_id)
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner msg] receive  NAV_UI_MSG_POWER_ON")) ;
        banner_set_first_power_on_state(TRUE);
    }
    if (NAV_UI_MSG_POWER_OFF == pt_ui_msg->e_id)
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner msg] receive  NAV_UI_MSG_POWER_ON")) ;
        banner_set_first_power_on_state(FALSE);
    }
    #endif

    if (NAV_UI_MSG_OTHER_APP_RESUMED == pt_ui_msg->e_id)
    {
        /* save the latest app, it will be used to check which APP the NAV was switched from */
        BANNER_LOG_ON_FAIL (_banner_set_last_app ((CHAR*)(UINT32)pv_arg1)) ;
    }

    /* customize this message */
    BANNER_LOG_ON_FAIL (banner_custom_handle_msg (pt_ui_msg, pv_arg1)) ;
#endif

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
* the function for sharing in banner inside
*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
*     banner_get_last_app_when_switch_app
* Description
* Input arguments
* Output arguments
* Returns
*---------------------------------------------------------------------------*/
CHAR* banner_get_last_app_when_switch_app (VOID)
{
    /* Read SPECIAL_NOTE_2010_12_15_001 first before you use this function, */

    if (FALSE == nav_is_resumed_from_app_switch ())
    {
        return NULL ;
    }

    return s_last_app_name ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_rcu_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_rcu_key_handler(
    UINT32                      ui4_key_code
    )
{
    return (banner_custom_rcu_key_handler (ui4_key_code)) ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_request_resend_item_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_request_resend_item_info (VOID)
{
    BANNER_T*                   pt_this = &t_g_banner ;
    TV_WIN_ID_T                 e_tv_win_id = TV_WIN_ID_MAIN ;

    /* get focused win id */
    BANNER_CHK_FAIL (nav_get_focus_id (&e_tv_win_id)) ;

    /* 1)
     * request all si info
     */
    BANNER_CHK_FAIL (a_si_request_resend_item_info_by_win_id (
                                pt_this->ui2_si_listener_id ,
                                e_tv_win_id)) ;

    /* FIXME_MIN */
    /* 2)
     * some message will change banner state,
     * we need re-trigger these messages manual as navigator
     * will not resend them for some case(such as window focuse changed)
     */

    /* 2.1)
     * re-trigger NAV_UI_MSG_EMPTY_SVL
     */
    if (nav_is_specified_ch_lst_empty (e_tv_win_id))
    {
        BANNER_CHK_FAIL (nav_send_msg_to_component (
                                NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER),
                                NAV_UI_MSG_EMPTY_SVL,
                                NULL)) ;
    }

    /* 2.2)
     * re-trigger NAV_UI_MSG_HIDDEN_CH
     */
    if (nav_is_hidden_ch (e_tv_win_id))
    {
        BANNER_CHK_FAIL (nav_send_msg_to_component (
                                NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER),
                                NAV_UI_MSG_HIDDEN_CH,
                                (VOID*)TRUE)) ;
    }

    /* 2.3)
     * re-trigger NAV_UI_MSG_AV_STATUS_NOTIFY
     */
    BANNER_CHK_FAIL (nav_send_msg_to_component (
                                NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER),
                                NAV_UI_MSG_AV_STATUS_NOTIFY,
                                (VOID*)nav_get_av_status (e_tv_win_id))) ;

    /* 2.4)
     * re-trigger NAV_UI_MSG_NO_SIGNAL/NAV_UI_MSG_WITH_SIGNAL
     */
    BANNER_CHK_FAIL (nav_send_msg_to_component (
                                NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER),
                                (nav_is_signal_loss (e_tv_win_id))
                                ? NAV_UI_MSG_NO_SIGNAL
                                : NAV_UI_MSG_WITH_SIGNAL ,
                                NULL )) ;

#ifdef APP_ISDB_SUPPORT
    /* 2.5)
     * re-trigger NAV_UI_MSG_NON_BRDCSTING
     */
    {
        HANDLE_T                h_svctx = NULL_HANDLE ;
        BOOL                    b_is_non_brdcsting = FALSE ;
        SIZE_T                  z_size = sizeof(BOOL) ;

        BANNER_CHK_FAIL (nav_get_svctx_handle (e_tv_win_id, &h_svctx)) ;

        BANNER_LOG_ON_FAIL (c_svctx_get (
                                h_svctx,
                                SVCTX_CH_GET_NON_BRDCSTING_SVC,
                                (VOID*)&b_is_non_brdcsting,
                                &z_size)) ;

        if (b_is_non_brdcsting)
        {
            BANNER_CHK_FAIL (nav_send_msg_to_component (
                                NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER),
                                NAV_UI_MSG_NON_BRDCSTING ,
                                NULL )) ;
        }
    }
#endif

    /* 2.6)
     * re-trigger LOCK/UNLOCK message
     */
    if (_crnt_source_is_blocked ())
    {
        /* SPECIAL_NOTE_2010_05_26_001
         * we cannot get actual locked state if service is not ready.
         * at here, we will get input source block flag from isl record.
         * please search SPECIAL_NOTE_2010_05_26_002 to read reltated information
         */
        BANNER_CHK_FAIL (nav_send_msg_to_component (
                                NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER),
                                NAV_UI_MSG_LOCKED_INP,
                                NULL )) ;
    }
    else
    {
        switch (nav_get_locked_status (e_tv_win_id))
        {
        case LOCKED_STATUS_PROGRAM_RATING:
            BANNER_CHK_FAIL (nav_send_msg_to_component (
                                NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER),
                                NAV_UI_MSG_LOCKED_PROG,
                                NULL )) ;
            break ;

        case LOCKED_STATUS_CHANNEL_LOCKED:
            BANNER_CHK_FAIL (nav_send_msg_to_component (
                                NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER),
                                NAV_UI_MSG_LOCKED_CH,
                                NULL )) ;
            break ;

        case LOCKED_STATUS_INP_SRC_LOCKED:
            /* SPECIAL_NOTE_2010_05_26_002
             * when service is not ready, we cannot get actually lock_state
             * by this way. so, just do nothing here,
             * please search SPECIAL_NOTE_2010_05_26_001 to read reltated information
             */
            break ;

        case LOCKED_STATUS_NONE:
        default :
            BANNER_CHK_FAIL (nav_send_msg_to_component (
                                NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER),
                                NAV_UI_MSG_UNLOCKED,
                                NULL )) ;
            break ;
        }

    }

    /* 2.xx)
     * re-trigger other mesages...
     */

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_unlock_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_unlock_state(
    UINT8                       ui1_state
    )
{
    UINT8                       ui1_unlock_priority  = 0 ;
    UINT8                       ui1_crnt_lock_priority = 0 ;
    BANNER_STATE_INFO_T*        pt_state_info = NULL ;

    if (BANNER_STATE_VIRTUAL_FINAL == ui1_state||
        BANNER_STATE_VIRTUAL_TV_DEFAULT == ui1_state)
    {
        return NAVR_INV_ARG ;
    }
    else if (BANNER_STATE_VIRTUAL_ALL_STATE == ui1_state)
    {
        /* unlock all state means force to unlock current state */
        ui1_unlock_priority = BANNER_STATE_PRI_FORCE_TO_UNLOCK ;
    }
    else
    {
        pt_state_info = banner_get_state_info (ui1_state) ;
        NAV_ASSERT (pt_state_info) ;
        BANNER_CHK_FAIL ( (pt_state_info) ? NAVR_OK : NAVR_FAIL) ;
        ui1_unlock_priority = pt_state_info->ui1_state_pri ;

        BANNER_CHK_FAIL (nav_bnr_state_get_status (
                                        NULL,
                                        NULL,
                                        NULL,
                                        &ui1_crnt_lock_priority)) ;

        if (ui1_crnt_lock_priority != ui1_unlock_priority)
        {
            /* specifiled state is already in unlock state */
            return NAVR_OK ;
        }
    }

    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("<--oo unlock state %s(%d) pri = %d\n",
                                        GET_STATE_DISP_NAME(ui1_state),
                                        ui1_state,
                                        ui1_unlock_priority)) ;
    BANNER_LOG_ON_FAIL (nav_bnr_state_unlock (ui1_unlock_priority)) ;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_change_state_to
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_change_state_to(
                             UINT8    ui1_state_name,
                             BOOL     b_need_show_banner_view,
                             BOOL     b_up_state_to_view_at_once
    )
{
    BANNER_T*               pt_this = &t_g_banner ;
    UINT8                   ui1_final_state = 0 ;
    UINT8                   ui1_actual_state = 0 ;
    UINT8                   ui1_priority = 0 ;
    BANNER_STATE_INFO_T*    pt_state_info = NULL ;

    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("try to change state to %s\n", GET_STATE_DISP_NAME(ui1_state_name))) ;
    if (BANNER_STATE_VIRTUAL_FINAL == ui1_state_name)
    {
        /* change to final state */
        BANNER_CHK_FAIL (nav_bnr_state_get_status (
                                        NULL,
                                        &ui1_final_state,
                                        NULL,
                                        NULL)) ;
        BANNER_LOG (_BANNER_LOG_TYPE_STATE,("current  state is %s\n", GET_STATE_DISP_NAME(ui1_final_state))) ;
        if (NAV_BNR_STATE_NULL_STATE_NAME != ui1_final_state)
        {
            ui1_actual_state = ui1_final_state ;
        }
        else
        {
            BANNER_CHK_FAIL (banner_get_crnt_state (&ui1_actual_state)) ;
        }
    }
    else if (BANNER_STATE_VIRTUAL_TV_DEFAULT == ui1_state_name)
    {
        /* change to default tv state */
        /*int TV source, the default state need to set PDCH, because the spec ask to show program detail info*/
        TV_WIN_ID_T    e_tv_win_id = TV_WIN_ID_MAIN ;
        nav_get_focus_id (&e_tv_win_id) ;
        BANNER_LOG (_BANNER_LOG_TYPE_STATE,("nav_get_src_type => %d\n", nav_get_src_type (e_tv_win_id))) ;
        if (INP_SRC_TYPE_TV == nav_get_src_type (e_tv_win_id) )
        {
             banner_get_crnt_state (&ui1_actual_state);
             if(BANNER_STATE_CH != ui1_actual_state &&
                BANNER_STATE_PCH != ui1_actual_state &&
                BANNER_STATE_PDCH != ui1_actual_state
               )
              {
                  ui1_actual_state = BANNER_STATE_CH;
              }
        }
        else
        {
             ui1_actual_state = pt_this->ui1_def_tv_state ;
        }
    }
    else if (BANNER_STATE_VIRTUAL_ALL_STATE == ui1_state_name)
    {
        /* this virtural state just for unlock purpose */
        return NAVR_OK ;
    }
    else if (ui1_state_name >= BANNER_STATE_LAST_VALID_ENTRY)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }
    else
    {
        ui1_actual_state = ui1_state_name ;
    }

    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("before  state is %s\n", GET_STATE_DISP_NAME(ui1_actual_state))) ;
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("b_need_show_banner_view = %d\n", b_need_show_banner_view)) ;
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("b_up_state_to_view_at_once = %d\n", b_up_state_to_view_at_once)) ;

    /* get the specified state's info */
    pt_state_info = banner_get_state_info (ui1_actual_state) ;
    NAV_ASSERT (pt_state_info) ;
    BANNER_CHK_FAIL ( (pt_state_info) ? NAVR_OK : NAVR_FAIL) ;

    ui1_priority = pt_state_info->ui1_state_pri ;

    /* change to specified state */
    BANNER_CHK_FAIL (nav_bnr_state_to ( ui1_actual_state,
                                        ui1_priority,
                                        NAV_BNR_STATE_TMOT_BY_STATE)) ;
    BANNER_CHK_FAIL (nav_bnr_state_get_status (
                                        NULL,
                                        &ui1_final_state,
                                        NULL,
                                        NULL)) ;
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("after state is %s \n", GET_STATE_DISP_NAME(ui1_final_state))) ;
    /* lock it */
    if (pt_state_info->b_lock_when_enter)
    {
        BANNER_LOG (_BANNER_LOG_TYPE_STATE,("lock state %s(%d) pri = %d\n",
                                        GET_STATE_DISP_NAME(ui1_actual_state),
                                        ui1_actual_state,
                                        pt_state_info->ui1_state_pri)) ;

        BANNER_CHK_FAIL (nav_bnr_state_lock_crnt_state (pt_state_info->ui1_state_pri)) ;
    }

    /* refresh view */
    BANNER_CHK_FAIL(banner_view_refresh (TRUE));

    /* set view visibility */
    if (b_need_show_banner_view)
    {
        BANNER_LOG_ON_FAIL (banner_view_set_visible (TRUE)) ;
    }

    /* if current state is IDLE invisible this component */
    if (banner_custom_get_idle_state() == pt_this->ui1_crnt_state &&
        nav_is_component_visible(NAV_COMP_ID_BANNER))
    {
        BANNER_LOG_ON_FAIL (nav_hide_component (NAV_COMP_ID_BANNER)) ;
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_get_crnt_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_get_crnt_state(
    UINT8*                      pui1_state
    )
{
    BANNER_T* pt_this = &t_g_banner;

    if (pui1_state == NULL)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    *pui1_state = (UINT8)pt_this->ui1_crnt_state;

    return NAVR_OK;
}

INT32 a_banner_get_crnt_state(INT32* pi4_state)
{
    UINT8                      ui1_crnt_state = 0 ;
    TV_WIN_ID_T                e_tv_win_id = TV_WIN_ID_MAIN ;
    LOCKED_STATUS_T            e_lock_status = LOCKED_STATUS_NONE ;

    if(pi4_state == NULL)
    {
        return NAVR_INV_ARG;
    }
    *pi4_state=MTKTVAPI_BANNER_STATE_DEFAULT;

    BANNER_CHK_FAIL (banner_get_crnt_state (&ui1_crnt_state)) ;
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("ui1_crnt_state= %d",ui1_crnt_state)) ;
    switch(ui1_crnt_state)
    {
        case BANNER_STATE_NO_SIG:
        {
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("BANNER_STATE_NO_SIG\n"));
            *pi4_state = MTKTVAPI_BANNER_STATE_NO_SIGNAL;
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("i4_state= %d",*pi4_state)) ;
            break;
        }

        case BANNER_STATE_EMPTY_SVL:
        {
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("BANNER_STATE_EMPTY_SVL\n"));
            *pi4_state = MTKTVAPI_BANNER_STATE_EMPTY_SVL;
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("i4_state= %d",*pi4_state)) ;
            break;
        }

        case BANNER_STATE_SHOW_MSG:
        case BANNER_STATE_IPTS:
        case BANNER_STATE_NONE:
        case BANNER_STATE_IDLE:
        {
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("BANNER_STATE_CHECK LOCK\n"));
            nav_get_focus_id (&e_tv_win_id);
            e_lock_status = nav_get_locked_status (e_tv_win_id);
            if(e_lock_status == LOCKED_STATUS_INP_SRC_LOCKED)
            {
               BANNER_LOG (_BANNER_LOG_TYPE_STATE,("LOCKED_STATUS_INP_SRC_LOCKED\n"));
               *pi4_state = MTKTVAPI_BANNER_STATE_LOCKED_SOURCE;
            }
            else if(e_lock_status == LOCKED_STATUS_CHANNEL_LOCKED)
            {
               BANNER_LOG (_BANNER_LOG_TYPE_STATE,("LOCKED_STATUS_CHANNEL_LOCKED\n"));
               *pi4_state = MTKTVAPI_BANNER_STATE_LOCKED_CHANNEL;
            }
            else if(e_lock_status == LOCKED_STATUS_PROGRAM_RATING)
            {
               BANNER_LOG (_BANNER_LOG_TYPE_STATE,("LOCKED_STATUS_PROGRAM_RATING\n"));
               *pi4_state =  MTKTVAPI_BANNER_STATE_LOCKED_PROGRAM;
            }
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("i4_state= %d",*pi4_state)) ;
            break;
        }

        case BANNER_STATE_RETRIEVE:
        {
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("BANNER_STATE_RETRIEVE\n"));
            *pi4_state = MTKTVAPI_BANNER_STATE_RETRIEVE;
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("i4_state= %d",*pi4_state)) ;
            break;
        }

        case BANNER_STATE_CH:
        case BANNER_STATE_PCH:
        case BANNER_STATE_PDCH:
        case BANNER_STATE_CHANGING:
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("default\n"));
            *pi4_state = MTKTVAPI_BANNER_STATE_DEFAULT;
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("i4_state= %d",*pi4_state)) ;
            break;

        case BANNER_STATE_INPTTING:
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("BANNER_STATE_INPTTING\n"));
            *pi4_state = MTKTVAPI_BANNER_STATE_INPUTTING;
            BANNER_LOG (_BANNER_LOG_TYPE_STATE,("i4_state= %d",*pi4_state)) ;
            break;
        default:
            break;
    }
#if 0
    e_lock_status = banner_get_locked_status ();
    if(e_lock_status == SVC_BLOCK_COND_USER_BLOCK_INP)
    {
       BANNER_LOG (_BANNER_LOG_TYPE_STATE,("LOCKED_STATUS_INP_SRC_LOCKED\n"));
       *pi4_state = MTKTVAPI_BANNER_STATE_LOCKED_SOURCE;
    }
    else if(e_lock_status == SVC_BLOCK_COND_USER_BLOCK_CH)
    {
       BANNER_LOG (_BANNER_LOG_TYPE_STATE,("LOCKED_STATUS_CHANNEL_LOCKED\n"));
       *pi4_state = MTKTVAPI_BANNER_STATE_LOCKED_CHANNEL;
    }
    else if(e_lock_status == SVC_BLOCK_COND_EXCEED_RATING)
    {
       BANNER_LOG (_BANNER_LOG_TYPE_STATE,("LOCKED_STATUS_PROGRAM_RATING\n"));
       *pi4_state =  MTKTVAPI_BANNER_STATE_LOCKED_PROGRAM;
    }
#endif
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("i4_state= %d, LINE:%d",*pi4_state, __LINE__)) ;

    return NAVR_OK;

}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_set_default_tv_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_set_default_tv_state (
    UINT8                       ui1_state
    )
{
    BANNER_T*                   pt_this = &t_g_banner ;

    pt_this->ui1_def_tv_state = ui1_state ;

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_get_total_state_num
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UINT16 banner_get_total_state_num (VOID)
{
    BANNER_T*                   pt_this = &t_g_banner ;

    return pt_this->ui2_state_num ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_get_state_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BANNER_STATE_INFO_T* banner_get_state_info (
    UINT8                       ui1_state_id
    )
{
    BANNER_T*                   pt_this = &t_g_banner ;
    UINT8                       ui1_idx = 0 ;
    BANNER_STATE_INFO_T*        pt_state_info = NULL ;

    /* find out the specified state */
    for (ui1_idx = 0 ;
         ui1_idx < pt_this->ui2_state_num ;
         ui1_idx ++ )
    {
        pt_state_info = &pt_this->pt_state_info[ui1_idx] ;

        if (ui1_state_id == pt_state_info->ui1_state_id)
        {
            break ;
        }
    }

    if (ui1_idx < pt_this->ui2_state_num)
    {
        return pt_state_info ;
    }
    else
    {
        return NULL ;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_get_log_type
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UINT16 banner_get_log_type (VOID)
{
    BANNER_T*                   pt_this = &t_g_banner ;

    return pt_this->i2_g_log_type ;
}
/*-----------------------------------------------------------------------------
 * Name
 *      banner_set_log_type
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID banner_set_log_type (
    UINT16                              ui2_log_type
    )
{
    BANNER_T*                   pt_this = &t_g_banner ;

    pt_this->i2_g_log_type = ui2_log_type ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_get_total_item_num
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UINT16 banner_get_total_item_num (VOID)
{
    BANNER_T*                   pt_this = &t_g_banner ;

    return pt_this->ui2_item_num ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_get_item_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BANNER_ITEM_INFO_T* banner_get_item_info (UINT8    ui1_item_id)
{
    BANNER_T*                   pt_this = &t_g_banner ;
    UINT8                       ui1_idx = 0 ;
    BANNER_ITEM_INFO_T*         pt_item_info = NULL ;

    if(ui1_item_id >= BANNER_ITM_LAST_VALID_ENTRY)
    {
        DBG_ERROR(("[Banner][%s %d] error  out of range item[%d]\n",__FUNCTION__,__LINE__,ui1_item_id));
        return NULL;
    }
    /* find out the specified item */
    for (ui1_idx = 0 ;
         ui1_idx < pt_this->ui2_item_num && ui1_idx < BANNER_ITM_LAST_VALID_ENTRY ;
         ui1_idx ++ )
    {
        pt_item_info = &pt_this->pt_item_info[ui1_idx] ;

        if (ui1_item_id == pt_item_info->ui1_item_id)
        {
            if(NULL_HANDLE == *(pt_item_info->ph_handle))
            {
                DBG_ERROR(("[Banner][%s %d] error to get item[%s],handle is NULL_HANDLE\n",__FUNCTION__,__LINE__,GET_ITEM_DISP_NAME(ui1_item_id)));
            }
            return pt_item_info ;
        }
    }
    return NULL ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_enable_this_log
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL banner_enable_this_log (
    UINT16                      ui2_log_type
    )
{
    BANNER_T*                   pt_this = &t_g_banner ;

    return ((ui2_log_type & pt_this->i2_g_log_type) == ui2_log_type) ;
    //return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_is_under_excl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL banner_is_under_excl (VOID)
{
    BANNER_T*                   pt_this = &t_g_banner ;

    return (pt_this->b_excl_comp_is_on) ;
}

/*-----------------------------------------------------------------------------
 * Name: a_banner_cli_cmd
 *
 * Description: This API is used to do cli cmd for banner
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
INT32 a_banner_cli_cmd (
   INT32                        i4_argc,
   const CHAR**                 pps_argv
   )
{
   BANNER_T*                    pt_this = &t_g_banner ;
   const CHAR*                  ps = NULL ;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: log [-|s|i|v|m]")) ;
        DBG_LOG_PRINT(("\n        [-] -> NONE ")) ;
        DBG_LOG_PRINT(("\n        [s] -> state ")) ;
        DBG_LOG_PRINT(("\n        [i] -> item ")) ;
        DBG_LOG_PRINT(("\n        [v] -> view ")) ;
        DBG_LOG_PRINT(("\n        [m] -> message ")) ;
        DBG_LOG_PRINT(("\n        [l] -> location ")) ;
        DBG_LOG_PRINT(("\n        [o] -> other infor ")) ;
        return NAVR_OK ;
    }

    ps = pps_argv[1] ;

    if (!ps)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    pt_this->i2_g_log_type = 0 ;

    while (*ps)
    {
        if (*ps == '-')
        {
            pt_this->i2_g_log_type = 0 ;
            return NAVR_OK ;
        }

        if (*ps == 's'|| *ps =='S')
        {
            pt_this->i2_g_log_type |= _BANNER_LOG_TYPE_STATE ;
        }

        if (*ps == 'i' || *ps == 'I')
        {
            pt_this->i2_g_log_type |= _BANNER_LOG_TYPE_ITEM ;
        }

        if (*ps == 'v' || *ps == 'V')
        {
            pt_this->i2_g_log_type |= _BANNER_LOG_TYPE_VIEW ;
        }

        if (*ps == 'm' || *ps == 'M')
        {
            pt_this->i2_g_log_type |= _BANNER_LOG_TYPE_MESSAGE ;
        }

        if (*ps == 'l' || *ps == 'L')
        {
            pt_this->i2_g_log_type |= _BANNER_LOG_TYPE_LOCATION ;
        }

        if (*ps == 'o' || *ps == 'O')
        {
            pt_this->i2_g_log_type |= _BANNER_LOG_TYPE_OTH_INFO ;
        }

        ps ++ ;
    }

    DBG_LOG_PRINT(("\n        ncurrent = ")) ;
    if (pt_this->i2_g_log_type == 0)
    {
        DBG_LOG_PRINT(("NONE")) ;
    }
    else
    {
        if (pt_this->i2_g_log_type & _BANNER_LOG_TYPE_STATE)
        {
            DBG_LOG_PRINT(("s")) ;
        }
        if (pt_this->i2_g_log_type & _BANNER_LOG_TYPE_ITEM)
        {
            DBG_LOG_PRINT(("i")) ;
        }
        if (pt_this->i2_g_log_type & _BANNER_LOG_TYPE_VIEW)
        {
            DBG_LOG_PRINT(("v")) ;
        }
        if (pt_this->i2_g_log_type & _BANNER_LOG_TYPE_MESSAGE)
        {
            DBG_LOG_PRINT(("m")) ;
        }
        if (pt_this->i2_g_log_type & _BANNER_LOG_TYPE_LOCATION)
        {
            DBG_LOG_PRINT(("l")) ;
        }
        if (pt_this->i2_g_log_type & _BANNER_LOG_TYPE_OTH_INFO)
        {
            DBG_LOG_PRINT(("o")) ;
        }
    }
    DBG_LOG_PRINT(("\n")) ;
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_banner_set_excl_comp_on
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_banner_set_excl_comp_on(BOOL    b_on)
{
    BANNER_T*    pt_this = &t_g_banner;

    pt_this->b_excl_comp_is_on = b_on;

    if (b_on)
    {
        if(nav_is_component_visible(NAV_COMP_ID_BANNER))
        {
#ifdef APP_BANNER_AMIN
            nav_banner_set_hide_mode(FALSE);
#endif
            BANNER_LOG_ON_FAIL (nav_hide_component (NAV_COMP_ID_BANNER));
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_banner_allow_to_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL a_banner_allow_to_show (VOID)
{
    return (banner_custom_allow_visible () ) ;
}

#ifdef APP_BANNER_AMIN
VOID a_banner_hide(BOOL b_anim)
{
    BANNER_LOG(_BANNER_LOG_TYPE_MESSAGE, ("\n"));
    if(nav_is_component_visible(NAV_COMP_ID_BANNER))
    {
        BANNER_LOG(_BANNER_LOG_TYPE_MESSAGE, ("\n"));
        nav_banner_set_hide_mode(b_anim);
        BANNER_LOG_ON_FAIL (nav_hide_component (NAV_COMP_ID_BANNER));
    }
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      a_banner_is_item_visible
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL a_banner_is_item_visible (NAV_BNR_STATE_ITEM_IDX_T    e_item_idx)
{
    BANNER_T*                   pt_this = &t_g_banner ;
    BNR_ITEM_SET_T              t_item_includs = 0 ;
    BANNER_STATE_INFO_T*        pt_state_info = NULL ;

    /* get current state info */
    pt_state_info = banner_get_state_info (pt_this->ui1_crnt_state) ;
    NAV_ASSERT (pt_state_info) ;
    if (!pt_state_info)
    {
        BANNER_LOG_ON_FAIL (NAVR_FAIL) ;
        return FALSE ;
    }

    t_item_includs    =       pt_state_info->t_item_includs;

    return ( a_banner_allow_to_show()       /* enable to show banner? */
             &&
             banner_view_is_on_show ()      /* banner is on showing */
             &&
             (t_item_includs & NAV_BNR_STATE_IDX_TO_ID (e_item_idx)) ) ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_banner_show_items
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_banner_show_items (BNR_ITEM_SET_T    t_item_ids)
{
    UINT8                       ui1_suit_state = 0 ;

    if (FALSE == a_banner_allow_to_show ())
    {
        return NAVR_NOT_ALLOW ;
    }

    /* restore final state first */
    BANNER_CHK_FAIL (banner_change_state_to (
                                BANNER_STATE_VIRTUAL_FINAL,
                               !NEED_SHOW_BANNER_VIEW,
                               !UP_TO_VIEW_AT_ONCE)) ;

    /* find out a state which include this itme */
    BANNER_CHK_FAIL (nav_bnr_state_lookup_state (
                                t_item_ids,
                                NAV_BNR_STATE_OT_CRNT_FINAL,
                                &ui1_suit_state)) ;

    /* change to the state */
    BANNER_CHK_FAIL (banner_change_state_to (
                                ui1_suit_state,
                                NEED_SHOW_BANNER_VIEW,
                                UP_TO_VIEW_AT_ONCE)) ;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_banner_set_item_content
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_banner_set_item_content (
    NAV_BNR_STATE_ITEM_IDX_T    e_item_id,
    UTF16_T*                    pw2s_text,      /* valide for BANNER_ITEM_TYPE_TEXT */
    HANDLE_T                    h_icon          /* valide for BANNER_ITEM_TYPE_ICON */
    )
{
    BANNER_CHK_FAIL (banner_view_update_item (
                                (UINT8)e_item_id, pw2s_text, h_icon, UP_TO_VIEW_AT_ONCE)) ;

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_banner_reset_state_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_banner_reset_state_timer (VOID)
{
    /* FIXME_MIN */
    if(banner_view_is_on_show())
        nav_bnr_state_timer_op(NAV_BNR_STATE_TMOT_BY_STATE ) ;
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_banner_register
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
#ifdef APP_BANNER_PARALLEL_HANDLE_MSG
static VOID _nav_banner_handle_msg_thread_main (VOID* pv_arg)
{
    NAV_BANNER_HANDLER_INFO_T*  pt_info;
    BOOL                        b_exit = FALSE;
    UINT16                      u2_index;
    NAV_BANNER_INTERNAL_MSG_T   t_msg;
    SIZE_T                      z_msg_size;

    while (!b_exit)
    {
        z_msg_size = sizeof(NAV_BANNER_INTERNAL_MSG_T);
        pt_info = (NAV_BANNER_HANDLER_INFO_T*) pv_arg;

        if (OSR_OK != c_msg_q_receive(& u2_index,
                                      & t_msg,
                                      & z_msg_size,
                                      & pt_info->h_handler_msgq, 1,
                                      X_MSGQ_OPTION_WAIT))
        {
            /* failure is ignored */
            continue;
        }

        {
            BANNER_T*    pt_this = &t_g_banner ;

            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,
                        ("receive message %s:%s(0x%x),%d  ",
                        (TV_WIN_ID_MAIN == ((NAV_UI_MSG_T*)t_msg.pv_param2)->e_tv_win_id) ? "Main" : "Sub",
                        GET_NAV_UI_MSG_STRING(t_msg.e_msg),
                        t_msg.e_msg,
                        (UINT32)t_msg.pv_param3)) ;

            if (NAV_UI_MSG_APP_INITED == t_msg.e_msg)
            {
                /* init state handler (register all state to state mamager) */
                if (banner_state_handler_init (_banner_listener ) < 0 ) continue;

                /* init item handler */
                if (banner_sys_info_handler_init (
                                                  _banner_listener,
                                                  &pt_this->ui2_si_listener_id) < 0) continue;

                /* prset custom data */
                if (banner_custom_preset_data_when_nav_inited () < 0) continue;
            }

            if (NAV_UI_MSG_OTHER_APP_RESUMED == t_msg.e_msg)
            {
                /* save the latest app, it will be used to check which APP the NAV was switched from */
                if (_banner_set_last_app ((CHAR*)(UINT32)t_msg.pv_param3) < 0) continue;
            }

            /* customize this message */
            if (banner_custom_handle_msg (t_msg.pv_param2, t_msg.pv_param3) < 0) continue;
        }
    }
}
#endif

INT32 a_banner_register (VOID)
{
    NAV_COMP_T    t_comp ;

    c_memset (&t_comp, 0 ,sizeof (NAV_COMP_T)) ;

    t_comp.pf_init           = _banner_init;
    t_comp.pf_deinit         = _banner_deinit;
    t_comp.pf_is_key_handler = _banner_is_key_handler;
    t_comp.pf_activate       = _banner_activate;
    t_comp.pf_inactivate     = _banner_inactivate;
    t_comp.pf_hide           = _banner_hide;
    t_comp.pf_handle_msg     = _banner_handle_msg;

    BANNER_CHK_FAIL (nav_register_component (
                                NAV_COMP_ID_BANNER,
                                &t_comp,
                                COMP_EXEC_SET_BANNER)) ;

#ifdef APP_BANNER_PARALLEL_HANDLE_MSG
    /* create handle message thread*/
    if (c_msg_q_create(& _h_banner_msgq,
                       NAV_BANNER_THREAD_NAME,
                       sizeof(NAV_BANNER_INTERNAL_MSG_T),
                       NAV_BANNER_MSG_QUEUE_SIZE)== OSR_OK)
    {
        NAV_BANNER_HANDLER_INFO_T    t_info;
        HANDLE_T                     h_thread;
        INT32 z_stack_size         = NAV_BANNER_DEFAULT_STACK_SIZE;
        CHAR ui1_priority          = NAV_BANNER_DEFAULT_THREAD_PRIORITY;

        t_info.h_handler_msgq = _h_banner_msgq;

        if (x_thread_create(& h_thread,
                            NAV_BANNER_THREAD_NAME,
                            z_stack_size,
                            ui1_priority,
                            _nav_banner_handle_msg_thread_main,
                            sizeof(t_info), (VOID*) & t_info)!= OSR_OK)
        {
            c_msg_q_delete(_h_banner_msgq);
            return NAVR_FAIL;
        }
    }
#endif

    return NAVR_OK;
}

VOID banner_sync_sys_info()
{
    BANNER_T*            pt_this = &t_g_banner ;
    TV_WIN_ID_T      e_tv_win_id = TV_WIN_ID_MAIN ;

    /* get focused win id */
    if( 0 == nav_get_focus_id (&e_tv_win_id))
    {
        a_si_request_resend_item_info_by_win_id (pt_this->ui2_si_listener_id ,e_tv_win_id) ;
    }
}

VOID banner_show_msg(UINT16 ui2_msg)
{
    WDK_TOAST_PARAM_T param;

    c_memset(&param,0,sizeof(param));
    param.w2s_str = MLM_NAV_TEXT(nav_get_mlm_lang_id(), ui2_msg);
    param.e_toast_style = WDK_SCREEN_CENTER_MSG;
    c_wgl_float(t_g_wdk_view.h_base_frm, TRUE, FALSE);
    a_wdk_toast_activate(TRUE,&param,&t_g_wdk_view);
    t_g_banner.ui2_msg_id = ui2_msg;
}

VOID banner_hide_msg()
{
    a_wdk_toast_hide(TRUE,NULL,&t_g_wdk_view);
    c_wgl_float(t_g_wdk_view.h_base_frm, FALSE, FALSE);
    t_g_banner.ui2_msg_id = 0;
}

VOID banner_update_msg()
{
    BOOL  b_visible = FALSE;

    c_wgl_get_visibility(t_g_wdk_view.h_base_frm,&b_visible);

    if(b_visible)
    {
        UTF16_T* w2s_str = MLM_NAV_TEXT(nav_get_mlm_lang_id(), t_g_banner.ui2_msg_id);

        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (t_g_wdk_view.h_txt_toast_box,
                                     WGL_CMD_TEXT_SET_TEXT,
                                     w2s_str,
                                     (VOID*)c_uc_w2s_strlen(w2s_str)));
        c_wgl_repaint(t_g_wdk_view.h_base_frm,NULL,FALSE);
    }
}
