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
 * $RCSfile: nav_bnr_state_handler.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor: min.li $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "c_os.h"
#include "c_dbg.h"

#include "banner.h"
#include "nav/nav_common.h"
#include "nav/nav_bnr_state_mgr.h"
#include "nav/navigator.h"
#include "res/nav/nav_variant.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * customization
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static banner_state_item_update_listener    pf_g_reporter = NULL ;
static UINT8                                g_ui1_timer_operate_id = 0 ;
#ifdef APP_ZOOM_MODE_SUPPORT
static BOOL                                 b_banner_state_first_power_on_state = FALSE;
#endif
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

#ifdef APP_TTS_SUPPORT
static INT32         g_i4_banner_tts_id    = 0;
static INT32         g_i4_banner_tts_playing_id = 0;
static INT32         g_i4_banner_tts_more_than_time_id = 0;/*if tts read more than 5s*/

static VOID _banner_view_wait_tts_notify(TTS_STRING_STATE_E e_tts_str_state, UINT32 ui4_tts_play_id, VOID* pv_tag);
#endif

static HANDLE_T                        h_last_timer = NULL_HANDLE;
static UINT32                          ui4_last_duration = 0;
static NAV_BNR_STATE_TIMER_OPER_TYPE_T e_last_timer_op = NAV_BNR_STATE_TMOT_DO_NOTHING;

/*timer operation executer*/
static INT32 _nav_bnr_timer_op_executer (
    VOID*                               pv_tag,
    HANDLE_T                            h_timer,
    NAV_BNR_STATE_TIMER_OPER_TYPE_T     e_op_type
    );

static INT32 _nav_bnr_repaint_op_executer(
    VOID*                               pv_tag,
    UINT8                               ui1_item_count,
    NAV_BNR_STATE_DIRTY_ITEM_T*         at_dirty_items
    );

static VOID _nav_bnr_timer_cb(
    HANDLE_T                            h_timer,
    VOID*                               pv_tag
    );

static VOID _nav_bnr_timer_msg_handler (
    VOID*                               pv_type,
    VOID*                               pv_reserved1,
    VOID*                               pv_reserved2
    );

/*-----------------------------------------------------------------------------
 * private VIEW methods implementations
 *---------------------------------------------------------------------------*/
#ifdef APP_TTS_SUPPORT
INT32 banner_tts_play(UTF16_T* pws_content)
{
    INT32 i4_len = c_uc_w2s_strlen(pws_content);
    if(i4_len > 0)
    {
        a_app_tts_nfy_reg(_banner_view_wait_tts_notify, NULL);
        g_i4_banner_tts_id = a_app_tts_play_new_gap_just_once(pws_content, i4_len, 3);
    }
    return NAVR_OK;
}

INT32 banner_view_tts_reading(VOID)
{
    UINT8    switch_status = APP_CFG_TTS_SWITCH_OFF;
    a_cfg_get_tts_switch_status(&switch_status);
    if(!switch_status)
        return NAVR_FAIL;

    if(g_i4_banner_tts_id == g_i4_banner_tts_playing_id)
        return NAVR_OK;
    else
        return NAVR_FAIL;
}

static VOID _banner_tts_onetime_finish(VOID* p_arg_first, VOID* p_arg_second, VOID* p_arg_third)
{
    BANNER_STATE_INFO_T*    pt_state_info = NULL ;
    UINT8                   ui1_crnt_state = 0 ;
    UINT8                   ui1_final_state = 0 ;
    UINT32                  ui4_play_id = (UINT32)p_arg_first;
    UINT32                  ui4_play_state = (UINT32)p_arg_second;
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,(" ui4_play_id = %d,ui4_play_state = %d ,g_i4_banner_tts_id = %d,g_i4_banner_tts_more_than_time_id = %d\r\n",
        ui4_play_id,
        ui4_play_state,
        g_i4_banner_tts_id,
        g_i4_banner_tts_more_than_time_id));

    if(g_i4_banner_tts_more_than_time_id == 1)
    {
        if(g_i4_banner_tts_id != ui4_play_id)
        {
            if(TTS_STR_ST_PLAYING == ui4_play_state)
            a_app_tts_nfy_unreg(_banner_view_wait_tts_notify);
            BANNER_LOG_ON_FAIL(c_timer_start (h_last_timer,
                                              ui4_last_duration, X_TIMER_FLAG_ONCE,
                                            _nav_bnr_timer_cb, (VOID*)e_last_timer_op));
        }
        else if(TTS_STR_ST_PLAYED == ui4_play_state)
        {
             g_i4_banner_tts_more_than_time_id = 0;
            /*get current and final state*/
            BANNER_LOG_ON_FAIL (nav_bnr_state_get_status(
                                        &ui1_crnt_state,
                                        &ui1_final_state,
                                        NULL,
                                        NULL));

            /* get the information of current state */
           if(NULL !=  (pt_state_info = banner_get_state_info (ui1_crnt_state)))
           {
                /* change to customization state */
                BANNER_LOG_ON_FAIL (banner_change_state_to (
                                        pt_state_info->ui1_chg_to_state_when_timeout,
                                        !NEED_SHOW_BANNER_VIEW,
                                        UP_TO_VIEW_AT_ONCE));
               // banner_view_hide();
            }
        }
    }
}

/*
*a notify func registe to tts_custom to get the state when playing tts.
*if string in banner is still playing the banner view should still display.
*/
static VOID _banner_view_wait_tts_notify(TTS_STRING_STATE_E e_tts_str_state, UINT32 ui4_tts_play_id, VOID* pv_tag)
{
    UINT8     ui1_state;

    banner_get_crnt_state(&ui1_state);
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,(" ui1_state = %s, ui4_tts_play_id = %d,e_tts_str_state = %d,g_i4_banner_tts_id = %d\n",
                    GET_STATE_DISP_NAME (ui1_state),
                    ui4_tts_play_id,
                    e_tts_str_state,
                    g_i4_banner_tts_id));
    if (ui1_state == BANNER_STATE_PDCH  &&  e_tts_str_state == TTS_STR_ST_PLAYED)
    {
        /*issue:DTV00835170,when TTS=ON,if the banner show channel details, will timeout*/
        DBG_INFO(("DEBUG!functon:%s,line:%d\n",__FUNCTION__,__LINE__));
        nav_request_context_switch(_banner_tts_onetime_finish, (VOID *)-1, (VOID *)TTS_STR_ST_UNKNOW, NULL);
    }

    if(e_tts_str_state == TTS_STR_ST_PLAYING)
    {//playing or interrupt by other string play
        nav_request_context_switch(_banner_tts_onetime_finish, (VOID *)ui4_tts_play_id, (VOID *)e_tts_str_state, NULL);

        g_i4_banner_tts_playing_id = ui4_tts_play_id;
    }
    else if(e_tts_str_state == TTS_STR_ST_PLAYED &&
            g_i4_banner_tts_id == ui4_tts_play_id)
    {//play complete
        nav_request_context_switch(_banner_tts_onetime_finish, (VOID *)ui4_tts_play_id, (VOID *)e_tts_str_state, NULL);
    }
};

#endif

INT32 nav_bnr_timer_reload(HANDLE_T                        h_timer,
                               UINT32                          ui4_duration,
                               NAV_BNR_STATE_TIMER_OPER_TYPE_T e_timer_op)
{

    if(NULL_HANDLE != h_timer)
    {
        h_last_timer = h_timer;
        ui4_last_duration = ui4_duration;
        e_last_timer_op = e_timer_op;
    }

    if(h_last_timer != NULL_HANDLE)
    {
        BANNER_CHK_FAIL (c_timer_stop(h_last_timer)) ;
        BANNER_LOG (_BANNER_LOG_TYPE_STATE,(" timer start\n"));
        BANNER_CHK_FAIL (c_timer_start (h_last_timer,
                                        ui4_last_duration, X_TIMER_FLAG_ONCE,
                                        _nav_bnr_timer_cb, (VOID*)e_last_timer_op));
    }

    return NAVR_OK;
}

UINT8 nav_bnr_timer_state(NAV_BNR_STATE_TIMER_OPER_TYPE_T e_timer_op)
{
    static UINT8    ui1_timer_op = NAV_BNR_STATE_TMOT_DO_NOTHING;

    if(0xFF == (UINT8)e_timer_op)
        return ui1_timer_op;
    else
    {
        ui1_timer_op = (UINT8) e_timer_op;
        return 0xFF;
    }

}

/*******************************************************************************
 * Name
 *          _nav_bnr_timer_op_executer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _nav_bnr_timer_op_executer(
    VOID*                           pv_tag,
    HANDLE_T                        h_timer,
    NAV_BNR_STATE_TIMER_OPER_TYPE_T e_timer_op
    )
{
    UINT8                           ui1_crnt_state ;
    UINT32                          ui4_duration = 0 ;
    BANNER_STATE_INFO_T*            pt_state_info = NULL ;

    /*get current & final states*/
    BANNER_CHK_FAIL (nav_bnr_state_get_status (
                                    &ui1_crnt_state, NULL, NULL, NULL)) ;
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("state [%s] \n", GET_STATE_DISP_NAME (ui1_crnt_state)));
    /* get current state info */
    pt_state_info = banner_get_state_info (ui1_crnt_state) ;
    NAV_ASSERT (pt_state_info) ;
    BANNER_CHK_FAIL ( (pt_state_info) ? NAVR_OK : NAVR_FAIL) ;

    nav_bnr_timer_state(e_timer_op);

    switch (e_timer_op)
    {
    case NAV_BNR_STATE_TMOT_BY_STATE :
    case NAV_BNR_STATE_TMOT_TO_IDLE:
    case NAV_BNR_STATE_TMOT_TO_FINAL:
        break;

    case NAV_BNR_STATE_TMOT_STOP:
        g_ui1_timer_operate_id ++ ;
        BANNER_CHK_FAIL (c_timer_stop(h_timer)) ;
        return NAVR_OK ;

    case NAV_BNR_STATE_TMOT_DO_NOTHING:
    default:
        /* do nothing */
        return NAVR_OK;
    }

    /*stop timer first*/
    g_ui1_timer_operate_id ++ ;
    BANNER_CHK_FAIL (c_timer_stop(h_timer)) ;

    ui4_duration = pt_state_info->ui4_time_out_duration ;

    /* as c_timer_start NOT support "0" for the duration
     * when the duration was set to "0", we just stop the time
     */
    if (0 == ui4_duration)
    {
        return NAVR_OK ;
    }

    /* reset timer */
    g_ui1_timer_operate_id ++ ;

    nav_bnr_timer_reload(h_timer,ui4_duration,e_timer_op);

    return NAVR_OK;
}

/*******************************************************************************
 * Name
 *          _nav_bnr_repaint_op_executer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _nav_bnr_repaint_op_executer(
    VOID*                           pv_tag,
    UINT8                           ui1_item_count,
    NAV_BNR_STATE_DIRTY_ITEM_T*     at_dirty_items)
{
    return NAVR_OK;
}

/*******************************************************************************
 * Name
 *          _nav_bnr_timer_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _nav_bnr_timer_cb(
    HANDLE_T                    h_timer,
    VOID*                       pv_tag)
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_bnr_timer_msg_handler,
                                pv_tag,
                                (VOID*)(UINT32)g_ui1_timer_operate_id,
                                NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_bnr_timer_msg_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_bnr_timer_msg_handler(
    VOID*                           pv_type,
    VOID*                           pv_timer_operate_id,
    VOID*                           pv_reserved2
    )
{
    NAV_BNR_STATE_TIMER_OPER_TYPE_T e_timer_op ;
    UINT8                           ui1_crnt_state = 0 ;
    UINT8                           ui1_final_state = 0 ;
    BANNER_STATE_INFO_T*            pt_state_info = NULL ;
    UINT8                           ui1_timer_operate_id = 0 ;

    if((TTS_STR_ST_PLAYING == a_app_tts_get_string_state()) && NAVR_OK == banner_view_tts_reading())
    {
        /*tts is reading and reading mag in banner then do nothing*/
        /*and wait _banner_tts_onetime_finish() to change state*/
        g_i4_banner_tts_more_than_time_id = 1;/*still reading when count to 5s*/
    }
    else
    {
        g_i4_banner_tts_more_than_time_id = 0;
        ui1_timer_operate_id = (UINT8)((UINT32)pv_timer_operate_id) ;

        if (/*FALSE == nav_is_active()
            ||*/
            ui1_timer_operate_id != g_ui1_timer_operate_id)
        {
            /* if it is a demoded message,
             * we should ignore it as the timer was refreshed again
             */
            return;
        }

        /*get current and final state*/
        BANNER_LOG_ON_FAIL (nav_bnr_state_get_status(
                                    &ui1_crnt_state,
                                    &ui1_final_state,
                                    NULL,
                                    NULL)) ;
        BANNER_LOG (_BANNER_LOG_TYPE_STATE,("state [%s] time out\n", GET_STATE_DISP_NAME (ui1_crnt_state))) ;
        e_timer_op = (NAV_BNR_STATE_TIMER_OPER_TYPE_T)(INT32)pv_type;

        if (NAV_BNR_STATE_TMOT_BY_STATE == e_timer_op)
        {
            /* get the information of current state */
            pt_state_info = banner_get_state_info (ui1_crnt_state) ;

            /* validity check */
            NAV_ASSERT (pt_state_info) ;
            if (!pt_state_info)
            {
                BANNER_LOG_ON_FAIL (NAVR_FAIL) ;
                return ;
            }

            /* change to customization state */
            BANNER_LOG_ON_FAIL (banner_change_state_to (
                                    pt_state_info->ui1_chg_to_state_when_timeout,
                                    !NEED_SHOW_BANNER_VIEW,
                                    UP_TO_VIEW_AT_ONCE)) ;
        }
        else if (
            NAV_BNR_STATE_TMOT_TO_IDLE == e_timer_op)
        {
            BANNER_LOG_ON_FAIL (banner_change_state_to(
                                    banner_custom_get_idle_state (),
                                    !NEED_SHOW_BANNER_VIEW,
                                    UP_TO_VIEW_AT_ONCE)) ;
        }
        else if (
            NAV_BNR_STATE_TMOT_TO_FINAL == e_timer_op)
        {
            BANNER_LOG_ON_FAIL (banner_change_state_to (
                                    ui1_final_state ,
                                    !NEED_SHOW_BANNER_VIEW,
                                    UP_TO_VIEW_AT_ONCE)) ; /*next timer: to idle*/
        }
        else
        {
            ASSERT_APPL(0, 0, ("PLEASE CHECK _nav_bnr_timer_op_executer, Only NAV_BNR_STATE_TMOT_TO_IDLE, NAV_BNR_STATE_TMOT_TO_FINAL and NAV_BNR_STATE_TMOT_BY_STATE can arrive here\r\n"));
        }
    }/*else*/

}


/*******************************************************************************
 * Name
 *          _notify_to_banner_state_changed
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _notify_to_banner_state_changed (
    UINT8                               ui1_state
    )
{
    BANNER_UPDATE_NFY_T                 t_nfy_data ;

    if (pf_g_reporter)
    {
        c_memset (&t_nfy_data, 0, sizeof (BANNER_UPDATE_NFY_T)) ;

        t_nfy_data.e_nfy_type = BANNER_NFY_TYPE_UPDATE_STATE ;
        t_nfy_data.u_nfy_data.t_up_state.ui1_state = ui1_state ;

        BANNER_CHK_FAIL (pf_g_reporter (t_nfy_data)) ;
    }

    return NAVR_OK ;
}
/*******************************************************************************
 * Name
 *          _nav_bnr_state_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _nav_bnr_state_init(
    VOID*                             pv_tag,
    VOID**                            pv_state_dm)
{
    *pv_state_dm = pv_tag ;

    return NAVR_OK;
}

/*******************************************************************************
 * Name
 *          _nav_bnr_state_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _nav_bnr_state_deinit(
    VOID*                               pv_state_dm)
{
    return NAVR_OK;
}

/*******************************************************************************
 * Name
 *          _nav_bnr_state_enter
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _nav_bnr_state_enter(
    VOID*                       pv_state_dm,
    UINT8                       ui1_state_from)
{
    INT32                       i4_ret = 0 ;
    UINT8                       ui1_ent_this_state = 0 ;
    BANNER_STATE_INFO_T*        pt_state_info = NULL ;

    ui1_ent_this_state = (UINT8)((UINT32)(pv_state_dm)) ;
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("ENTER STATE %s \n", GET_STATE_DISP_NAME(ui1_ent_this_state))) ;
    i4_ret = _notify_to_banner_state_changed (ui1_ent_this_state) ;
    BANNER_CHK_FAIL (i4_ret) ;

    if(NAVR_NO_ACTION == i4_ret)
    {
        return NAVR_NO_ACTION ;
    }

    /* do NOT try to lock current state here, its not safty ...
     * for example :
     * assume: current state is INPTTING and the state was locked.
     * if there has a unlock operation, the INPTTING state will be unlocked.
     * then, we try to change state to INPTTING again,
     * as the request state is same as current state, this function will
     * not execute. so the state still in unlocked ...
     * SO, PLEASE DO LOCK OPERATION OURSIDE...
     */
#if 0
    /* lock current state */
    if (pt_g_state_info[e_ent_this_state].b_lock_when_enter)
    {
        BANNER_CHK_FAIL (banner_lock_state (ui1_ent_this_state)) ;
    }
#endif

    /* get this state's info */
    pt_state_info = banner_get_state_info (ui1_ent_this_state) ;
    NAV_ASSERT (pt_state_info) ;
    BANNER_CHK_FAIL ( (pt_state_info) ? NAVR_OK : NAVR_FAIL) ;

    /* set as final state */
    if (pt_state_info->b_set_as_fnl_when_enter)
    {
        BANNER_CHK_FAIL (nav_bnr_state_set_final (ui1_ent_this_state)) ;
    }

    return NAVR_OK ;
}

/*******************************************************************************
 * Name
 *          _nav_bnr_state_exit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _nav_bnr_state_exit(
    VOID*                             pv_state_dm,
    UINT8                             ui1_state_to)
{
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("EXIT STATE %s \n", GET_STATE_DISP_NAME(ui1_state_to))) ;
    return NAVR_OK ;
}

/*******************************************************************************
 * Name
 *          _nav_bnr_state_sync
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _nav_bnr_state_sync(
    VOID*                             pv_state_dm,
    UINT8*                            pui1_state_at)
{
    return (banner_get_crnt_state((UINT8*)pui1_state_at)) ;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
 #ifdef APP_ZOOM_MODE_SUPPORT
 /*******************************************************************************
 * Name
 *          banner_set_first_power_on_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
 VOID banner_set_first_power_on_state(BOOL b_first_power_on)
{
    b_banner_state_first_power_on_state = b_first_power_on;
}
 #endif

/*******************************************************************************
 * Name
 *          banner_register_state_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
INT32 banner_state_handler_init (
    banner_state_item_update_listener   pf_reporter
    )
{
    NAV_BNR_STATE_INTF_T                t_intf;
    NAV_BNR_STATE_OP_EXECUTER_T         t_op_exec;
    UINT8                               ui1_state_id = 0 ;
    BANNER_STATE_INFO_T*                pt_state_info = NULL ;

    pf_g_reporter = pf_reporter ;

    /*register timer operation executer*/
    t_op_exec.pf_timer_op        = _nav_bnr_timer_op_executer;
    t_op_exec.pf_repaint_op      = _nav_bnr_repaint_op_executer;
    t_op_exec.pf_mode_change_nfy = NULL;
    t_op_exec.ui1_init_mode      = 0;
    BANNER_CHK_FAIL (nav_bnr_state_set_op_executer(&t_op_exec, NULL)) ;

    NAV_ASSERT (banner_get_total_state_num () <= NAV_BNR_STATE_MAX_COUNT) ;

    for (ui1_state_id = 0 ;
         ui1_state_id < banner_get_total_state_num () ;
         ui1_state_id ++ )
    {
        /* get specified state */
        pt_state_info = banner_get_state_info (ui1_state_id) ;
        if (!pt_state_info)
        {
            continue ;
        }

        /* register to banner core layer */
        NAV_BNR_STATE_ZERO_INTF(&t_intf);
        t_intf.pf_init      =   _nav_bnr_state_init;
        t_intf.pf_deinit    =   _nav_bnr_state_deinit;
        t_intf.pf_enter     =   _nav_bnr_state_enter;
        t_intf.pf_exit      =   _nav_bnr_state_exit;
        t_intf.pf_sync      =   _nav_bnr_state_sync;
        BANNER_CHK_FAIL (nav_bnr_state_register(
                                pt_state_info->ui1_state_id,
                                pt_state_info->t_item_includs,
                                &t_intf,
                                (VOID*)(UINT32)(pt_state_info->ui1_state_id))) ;
    }

    return NAVR_OK;
}

