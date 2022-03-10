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
 * $RCSfile: burning_mode.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Chris Kuo $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_cfg.h"
#include "u_scc.h"
#include "c_scc.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_iom.h"

#include "app_util/a_cfg.h"
#include "app_util/a_common.h"
#include "app_util/a_tv.h"
#include "burning_mode.h"

#ifdef APP_FACTORY_KEY_FLAG
#include "res/app_util/config/a_cfg_custom.h"
#endif
#include "agent/a_agent.h"
#include "res/nav/nav_dbg.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#ifndef BURNING_MODE_TIMER_DELAY
    #define BURNING_MODE_TIMER_DELAY         (3000)  /* in ms */
#endif

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static BURNING_MODE_T    t_g_burning_mode;
#ifdef APP_NAV_BURNING_PLAY_TONE
BOOL is_test_tone_play = FALSE;
#endif

static HANDLE_T g_h_iom;
#if 0
static BOOL     b_start_test_flag=0;
static UINT8    ui1_test_delay_time=0;
static UINT32   ui4_burning_wifi_dt=0;
static BOOL     b_Fake_SSID_Flag=0;
static BOOL     b_Fake_SSID_End_Flag=0;
#endif
static BOOL     b_Load_Default=0;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _burning_mode_stop_timer(
                    BURNING_MODE_T*             pt_this
                    );
static VOID _burning_mode_reset_timer(
                    BURNING_MODE_T*             pt_this
                    );
static VOID _burning_mode_next_pattern(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );
static VOID _burning_mode_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    );
static VOID _burning_mode_stop_burning(
                    VOID
                    );

/* Lifecycle API's */
static INT32 _burning_mode_init(
                    NAV_CONTEXT_T*              pt_ctx
                    );
static INT32 _burning_mode_deinit(
                    VOID
                    );
static BOOL _burning_mode_is_key_handler(
                    NAV_CONTEXT_T*  pt_ctx,
                    UINT32          ui4_key_code
                    );
static INT32 _burning_mode_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    );
static INT32 _burning_mode_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    );
static INT32 _burning_mode_hide(
                    VOID
                    );
static INT32 _burning_mode_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    );
#ifdef APP_NAV_BURNING_PLAY_TONE
static INT32 _burning_mode_stop_audio_tone (VOID);
static INT32 _burning_mode_start_audio_tone (VOID);
#endif
static VOID _set_burning_backlight (INT16 i2_val);

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_burning_mode_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_burning_mode_register(
                    VOID
                    )
{
    NAV_COMP_T     t_comp;
    INT32          i4_ret;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    t_comp.pf_init           = _burning_mode_init;
    t_comp.pf_deinit         = _burning_mode_deinit;
    t_comp.pf_is_key_handler = _burning_mode_is_key_handler;
    t_comp.pf_activate       = _burning_mode_activate;
    t_comp.pf_inactivate     = _burning_mode_inactivate;
    t_comp.pf_hide           = _burning_mode_hide;
    t_comp.pf_handle_msg     = _burning_mode_handle_msg;

    /* Register component. */
    i4_ret = nav_register_component (NAV_COMP_ID_BURNING_MODE, & t_comp, ~NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BURNING_MODE));

    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"nav_register_comp(NAV_COMP_ID_BURNING_MODE) failed\r\n"));
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
#ifdef APP_FACTORY_KEY_FLAG
static VOID _inactivate_remote_ctx_switch (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    UINT32          ui4_evt_code = (UINT32) pv_tag3;
    BURNING_MODE_T* pt_this      = (BURNING_MODE_T*)& t_g_burning_mode;

    ui4_evt_code = IOM_GET_EVT_GRP_ID (ui4_evt_code);

    if( pt_this->b_IR_inactivate && BTN_BURNING_MODE==ui4_evt_code && (UINT32)pv_tag2==IOM_NFY_COND_BTN_DOWN)
    {
        a_nav_burning_mode_toggle_pattern();
        return;
    }
}

static VOID _inactivate_remote_iom_nfy_fct(
                    VOID*                pv_nfy_tag,
                    IOM_NFY_COND_T       e_nfy_cond,
                    UINT32               ui4_evt_code,
                    UINT32               ui4_data
                    )
{
    nav_request_context_switch (_inactivate_remote_ctx_switch, pv_nfy_tag, (VOID*)e_nfy_cond, (VOID*)ui4_evt_code);
    return;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      c_inactivate_remote
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
#ifdef APP_FACTORY_KEY_FLAG
static void c_inactivate_remote( void)
{
    IRRC_SETTING_T     t_irrc_setting;
    SIZE_T             z_info_len;
    UINT64             ui8_evt_src;
    BURNING_MODE_T*    pt_this = (BURNING_MODE_T*)& t_g_burning_mode;

    if( pt_this->b_IR_inactivate == FALSE)
    {
        /* Register to IOM in order to receive raw data. */
        c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));

        t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
        t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = IOM_ZERO_RPT_EVT_ITVL;
        t_irrc_setting.t_rpt_evt_itvl.ui2_other = IOM_ZERO_RPT_EVT_ITVL;
        t_irrc_setting.b_notify_raw_data        = TRUE;
        
        c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                    IOM_DEV_ID_ANY,
                    NULL,
                    (VOID*) & t_irrc_setting,
                    NULL,
                    _inactivate_remote_iom_nfy_fct,
                    &g_h_iom);

        /* Ignore incoming RC commands/Ignore font panel keys. */
        z_info_len = sizeof (UINT64);
        
        c_iom_get (g_h_iom,
                   IOM_GET_IRRC_EVT_SRC_MASK,
                   (VOID*)& ui8_evt_src,
                   & z_info_len);
        
        ui8_evt_src &= ~IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL);
        //ui8_evt_src &= ~IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL);
        
        c_iom_set (g_h_iom,
                   IOM_SET_IRRC_EVT_SRC_MASK,
                   (VOID*)& ui8_evt_src,
                   sizeof (UINT64));

        pt_this->b_IR_inactivate = TRUE; 
        a_tv_net_disable_keyroute(TRUE);   
    }
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      c_activate_remote
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static void c_activate_remote(void)
{
    SIZE_T             z_info_len;
    UINT64             ui8_evt_src;
    BURNING_MODE_T*    pt_this = (BURNING_MODE_T*)& t_g_burning_mode;

    if( pt_this->b_IR_inactivate)
    {
        /* enable incoming RC commands/Ignore font panel keys. */
        z_info_len = sizeof (UINT64);
        
        c_iom_get (g_h_iom,
                   IOM_GET_IRRC_EVT_SRC_MASK,
                   (VOID*)& ui8_evt_src,
                   & z_info_len);
        
        ui8_evt_src |= IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL);
        //ui8_evt_src |= IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL);
        
        c_iom_set (g_h_iom,
                   IOM_SET_IRRC_EVT_SRC_MASK,
                   (VOID*)& ui8_evt_src,
                   sizeof (UINT64));
        
        c_iom_close (g_h_iom);

        pt_this->b_IR_inactivate = FALSE;     
        a_tv_net_disable_keyroute(FALSE);
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _burning_mode_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    INT32              i4_ret;
    BURNING_MODE_T*    pt_this = & t_g_burning_mode;

    pt_this->h_timer            = NULL_HANDLE;
    pt_this->ui4_delay          = BURNING_MODE_TIMER_DELAY;
    pt_this->b_IR_inactivate    = FALSE;

    do
    {
        /* Create timer. */
        if (pt_this->ui4_delay > 0)
        {
            i4_ret = c_timer_create (& pt_this->h_timer);

            if (i4_ret != OSR_OK)
            {
                DBG_ERROR((_ERROR_HEADER"create timer failed\r\n"));

                break;
            }
        }

        /* Init view. */
        i4_ret = burning_mode_view_init (pt_this,
                                         pt_ctx->t_gui_res.h_canvas);

        if (i4_ret != NAVR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"burning_mode_view_init () failed\r\n"));

            break;
        }

    } while (0);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _burning_mode_deinit(
                    VOID
                    )
{
    INT32              i4_ret;
    BURNING_MODE_T*    pt_this = & t_g_burning_mode;

    /* Delete timer. */
    if (c_handle_valid (pt_this->h_timer) == TRUE)
    {
        c_timer_delete (pt_this->h_timer);
    }

    /* Deinit view. */
    i4_ret = burning_mode_view_deinit (& pt_this->t_view);

    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }

    pt_this->h_timer     = NULL_HANDLE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _burning_mode_is_key_handler(
                    NAV_CONTEXT_T*  pt_ctx,
                    UINT32          ui4_key_code
                    )
{
    UINT8           ui1_factory_mode;
    TV_MODE_T       e_tv_mode;
    BURNING_MODE_T* pt_this = (BURNING_MODE_T*)& t_g_burning_mode;

    if (BTN_BURNING_MODE == ui4_key_code)
    {
        DBG_INFO((_INFO_HEADER"burning_mode_activate"));
        
        if (!nav_is_component_visible(NAV_COMP_ID_BURNING_MODE))
        {
            /* Get TV mode. */
            (void)nav_get_tv_mode (& e_tv_mode);
            
            /* Get factory mode. */
            a_cfg_get_factory_mode (& ui1_factory_mode);
            
            if ((e_tv_mode == TV_MODE_TYPE_NORMAL)                      &&  /* Normal mode. */
                (ui1_factory_mode & APP_CFG_FAC_MODE_BURNING_MASK) != 0 &&  /* Burning mode. */
                (! pt_this->b_active))                                      /* Not active. */
            {
                DBG_INFO((_INFO_HEADER"burning_mode_reset_timer\r\n"));
            
                /* Reset timer. */
                _burning_mode_reset_timer (pt_this);
            
                /* Start burning immediately. */
                _burning_mode_next_pattern (NULL, NULL, NULL);
            
                return TRUE;
            }
        }
        else
        {
            /* Stop burning pattern. */
            _burning_mode_stop_burning ();
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name:    _burning_mode_ctx_switch_fct_by_am
 * Description: Toggle burning mode.
 * Input:   -
 * Output:  -
 * Returns  NAVR_OK     This function executed successfully.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
static VOID _burning_mode_ctx_switch_fct_by_am (
    VOID*                       pv_tag1,
    VOID*                       pv_tag2,
    VOID*                       pv_tag3)
{
    /* Simulate a key is arrived. */
    _burning_mode_is_key_handler (NULL, BTN_BURNING_MODE);
}

/*-----------------------------------------------------------------------------
 * Name:    a_nav_burning_mode_toggle_pattern
 * Description: Toggle burning mode.
 * Input:   -
 * Output:  -
 * Returns  NAVR_OK     This function executed successfully.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 a_nav_burning_mode_toggle_pattern (VOID)
{
    if (nav_is_active () == FALSE)
    {
        nav_resume_self ();
        nav_request_context_switch_via_am (_burning_mode_ctx_switch_fct_by_am,
                                           NULL,
                                           NULL,
                                           NULL);
    }
    else
    {
        _burning_mode_is_key_handler (NULL, BTN_BURNING_MODE);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _burning_mode_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    BURNING_MODE_T* pt_this = (BURNING_MODE_T*)& t_g_burning_mode;

    DBG_INFO((_INFO_HEADER"burning_mode_activate"));
    
     a_tv_net_send_cmd(":dtv_app_mtk,am,:disable_PKWD\n");
     a_tv_net_send_cmd(":dtv_app_mtk,am,:block_3rd\n");

    /* Turn on active flag. */
    pt_this->b_active = TRUE;
#ifdef APP_FACTORY_KEY_FLAG
    {        
        a_cfg_set_cec_func(1);
        c_inactivate_remote();
    }
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _burning_mode_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    BURNING_MODE_T*    pt_this = (BURNING_MODE_T*)& t_g_burning_mode;

    DBG_INFO((_INFO_HEADER"burning_mode_inactivate\r\n"));
    //ke_vizio_20130320 cancel ENABLE POWER key watchdog for keypad test.
    //a_tv_net_send_cmd(":dtv_app_mtk,am,:enable_PKWD\n");

    /* Turn off active flag. */
    pt_this->b_active = FALSE;

    /*a_cfg_custom_set_def_ch_load_flag(FALSE);*/

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _burning_mode_hide(
                    VOID
                    )
{
    INT32              i4_ret;
    BURNING_MODE_T*    pt_this = & t_g_burning_mode;

    DBG_INFO((_INFO_HEADER"burning_mode_hide\r\n"));

    /* Hide view. */
    i4_ret = burning_mode_view_hide (& pt_this->t_view);

    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _burning_mode_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    INT32              i4_ret;
    UINT8              ui1_factory_mode;
    TV_MODE_T          e_tv_mode;
    BURNING_MODE_T*    pt_this = & t_g_burning_mode;

    switch (pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_NO_SIGNAL:
        /* If don't insert fake channel,Under TV source need use NAV_UI_MSG_EMPTY_SVL to start burning mode*/
        case NAV_UI_MSG_EMPTY_SVL:
        {
            DBG_INFO((_INFO_HEADER"burning_mode_no_signal_nfy\r\n"));

            /* Get TV mode. */
            i4_ret = nav_get_tv_mode (& e_tv_mode);

            if (i4_ret != NAVR_OK)
            {
                break;
            }

            /* Get factory mode. */
            i4_ret = a_cfg_get_factory_mode (& ui1_factory_mode);

            if (i4_ret != APP_CFGR_OK)
            {
                break;
            }
            #if 0  //ke_vizio_20121213 for the first time AC on, the burn in mode will not auto start.  
            if ((e_tv_mode == TV_MODE_TYPE_NORMAL)                      &&  /* Normal mode. */
                (ui1_factory_mode & APP_CFG_FAC_MODE_BURNING_MASK) != 0 &&  /* Burning mode. */
                (! pt_this->b_active))                                      /* Not active. */
            {
                DBG_INFO((_INFO_HEADER"burning_mode_reset_timer\r\n"));

                /* Reset timer. */
                _burning_mode_reset_timer (pt_this);

                /* Start burning immediately. */
                _burning_mode_next_pattern (NULL, NULL, NULL);
            }
            #else //Rest timer whatever it had shown.
            if ((e_tv_mode == TV_MODE_TYPE_NORMAL)                      &&  /* Normal mode. */
                (ui1_factory_mode & APP_CFG_FAC_MODE_BURNING_MASK) != 0)    /* Burning mode. */
            {
                DBG_INFO((_INFO_HEADER"burning_mode_reset_timer\r\n"));

                /* Reset timer. */
                _burning_mode_reset_timer (pt_this);

                /* Start burning immediately. */
                _burning_mode_next_pattern (NULL, NULL, NULL);

            }
            #endif
        }
        break;

        case NAV_UI_MSG_WITH_SIGNAL:
        {
            DBG_INFO((_INFO_HEADER"burning_mode_with_signal\r\n"));

            /* Stop burning pattern. */
            _burning_mode_stop_burning ();
        }
        break;

        case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
        {
            e_tv_mode = (TV_MODE_T)(INT32)pv_arg1;

            if (e_tv_mode != TV_MODE_TYPE_NORMAL)
            {
                /* Stop burning pattern. */
                _burning_mode_stop_burning ();
            }
            else /* Normal mode. */
            {
                /* Get factory mode. */
                i4_ret = a_cfg_get_factory_mode (& ui1_factory_mode);

                if (i4_ret != APP_CFGR_OK)
                {
                    break;
                }

                if ((ui1_factory_mode & APP_CFG_FAC_MODE_BURNING_MASK) != 0 &&  /* Burning mode. */
                    (nav_is_signal_loss (TV_WIN_ID_MAIN))                   &&  /* No signal. */
                    (! pt_this->b_active))                                      /* Not active. */
                {
                    DBG_INFO((_INFO_HEADER"burning_mode_reset_timer\r\n"));

                    /* Reset timer. */
                    _burning_mode_reset_timer (pt_this);
                }
            }
        }
        break;

        case NAV_UI_MSG_APP_PAUSING:
        {
            /* Stop burning pattern. */
            _burning_mode_stop_burning ();
        }
        break;

#ifdef APP_NAV_BURNING_PLAY_TONE
        case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        {
            _burning_mode_stop_audio_tone ();
        }
        break;
#endif
        default:
            break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_stop_burning
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _burning_mode_stop_burning(
                    VOID
                    )
{
    BURNING_MODE_T* pt_this = (BURNING_MODE_T*)& t_g_burning_mode;

    DBG_INFO((_INFO_HEADER"burning_mode_stop\r\n"));

    if (! pt_this->b_stop) /* Timer is running. */
    {
        /* Stop timer. */
        _burning_mode_stop_timer (pt_this);
        
        /* Hide component. */
        nav_hide_component (NAV_COMP_ID_BURNING_MODE);
    }

    if (pt_this->b_active) /* Burning mode is being active. */
    {
        /* Return activation. */
        nav_return_activation (NAV_COMP_ID_BURNING_MODE);
    }

    c_activate_remote();

}

/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _burning_mode_stop_timer(
                    BURNING_MODE_T*              pt_this
                    )
{
    INT32    i4_ret;

    if (c_handle_valid (pt_this->h_timer) == FALSE)
    {
        return;
    }

    /* Stop timer. */
    i4_ret = c_timer_stop (pt_this->h_timer);

    if (i4_ret != OSR_OK)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("Stop burning_mode::h_timer failed!"));
    }

#ifdef APP_NAV_BURNING_PLAY_TONE
    /* Stop audio test tone. */
    _burning_mode_stop_audio_tone ();
#endif

    /* Turn on stop flag. */
    pt_this->b_stop = TRUE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _burning_mode_reset_timer(
                    BURNING_MODE_T*              pt_this
                    )
{
    INT32    i4_ret;

    /* Stop timer. */
    _burning_mode_stop_timer (pt_this);


#ifdef APP_NAV_BURNING_PLAY_TONE
    /* Start audio test tone. */
    _burning_mode_start_audio_tone ();
#endif

    /* Start timer. */
    i4_ret = c_timer_start (pt_this->h_timer,
                            pt_this->ui4_delay,
                            X_TIMER_FLAG_REPEAT,
                            _burning_mode_timer_nfy,
                            pt_this);

    if (i4_ret != OSR_OK)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("Start burning_mode::h_hide_timer failed!"));
    }

    /* Turn off stop flag. */
    pt_this->b_stop = FALSE;
}

#define AMTRAN_LOAD_CHANNEL "LoadDefaultChannel"
static BOOL _b_CH_DEFAULT = 0;
/*-----------------------------------------------------------------------------
 * Name
 *      _Load_Default_Channel
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _Load_Default_Channel(VOID* pv_data, SIZE_T z_data_len)
{
#if 0
    INT32              i4_ret;
    
    while(!_b_CH_DEFAULT)
    {
    
         i4_ret = a_cfg_custom_load_default_channel();
         if(i4_ret!=0)
         {
            DBG_ERROR(("--------[burning_mode.c]   Load Default Channel error = %x --------------\n",i4_ret));
         }
         _b_CH_DEFAULT = a_cfg_custom_get_def_ch_load_flag();   
            
    }

    b_Load_Default = 0;
    DBG_INFO(("Load Default Channel Complete _b_CH_DEFAULT = %d \n",_b_CH_DEFAULT));
#endif     
}


/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_next_pattern
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _burning_mode_next_pattern(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32              i4_ret;
    NAV_COMP_ID_T      e_active_comp;
    BURNING_MODE_T*    pt_this = & t_g_burning_mode;
#if 0    
    UINT16             ui2_burning_timer_count = 0;
    UINT8              ui1_test_result_tc,ui1_test_tc;
#endif    
    
    if (! pt_this->b_stop) /* Timer is running. */
    {
        /*_b_CH_DEFAULT = a_cfg_custom_get_def_ch_load_flag();*/
        
        //debug use do not mark it
        DBG_INFO(("------[burning_mode.c]-----> LOAD DEFAULT CHANNEL success or not =%x \n",_b_CH_DEFAULT));
        
        if(0==_b_CH_DEFAULT)
        {
            if(b_Load_Default != 1)
            {
                b_Load_Default = 1;
                a_agent_async_invoke(_Load_Default_Channel,NULL,0);
            }
        }
        
        /* Get active component. */
        e_active_comp = nav_get_active_component ();

        DBG_INFO((_INFO_HEADER"burning_mode_timer_nfy, active_comp = %d\r\n", e_active_comp));

        if ((e_active_comp == NAV_COMP_ID_BURNING_MODE) ||
            (e_active_comp == NAV_COMP_ID_BANNER)       ||
            (e_active_comp == NAV_COMP_ID_SCREEN_SAVER) ||
            (e_active_comp == NAV_COMP_ID_LAST_VALID_ENTRY))
        {
#if 0
            if(a_cfg_custom_get_burning_not_test_burningtime_flag()>=1)
            {
                if(ui2_burning_timer_count < 0xFFFF)
                {
                    //Cumulative time after AC power off on
                    ui2_burning_timer_count = a_cfg_custom_get_burning_time();
                    
                    //every 3 sec change next pattern
                    ui2_burning_timer_count++;
                    
                    //c_dbg_secure_stmt("------[burning_mode.c]-----> burning_timer_count =%x \n",ui2_burning_timer_count);
                    
                    i4_ret = a_cfg_custom_set_burning_time(ui2_burning_timer_count);
                    
                    if (i4_ret != NAVR_OK)
                    {
                        DBG_ERROR((_ERROR_HEADER"burning_mode_a_cfg_custom_set_burning_time () failed\r\n"));
                    }
                }
                else
                {
                    ui2_burning_timer_count=0;
                }
            }
            
            if(a_cfg_custom_get_burning_wifi_test_flag()==TRUE)
            {               
                ui4_burning_wifi_dt = a_cfg_custom_get_burning_wifi_test_dt();
                
                ui4_burning_wifi_dt = ui4_burning_wifi_dt*20;        
                
                ui1_test_result_tc = a_cfg_custom_get_burning_wifi_test_result_tc();
        
                ui1_test_tc = a_cfg_custom_get_burning_wifi_test_tc();

                if((ui1_test_result_tc == ui1_test_tc)&&(b_Fake_SSID_End_Flag==0))
                {   
                    b_Fake_SSID_Flag=1;
                }

                if(b_Fake_SSID_Flag==1)
                {
                    Fake_SSID();
                    b_Fake_SSID_Flag=0;
                    b_Fake_SSID_End_Flag=1;
                    a_cfg_custom_set_burning_wifi_test_flag(FALSE);
                    //c_dbg_secure_stmt("------[burning_mode.c]-----> burning wifi test finsh \n");
                }
                
                if((ui2_burning_timer_count >= ui4_burning_wifi_dt)&&(ui1_test_result_tc < ui1_test_tc))
                {
                    //c_dbg_secure_stmt("------[burning_mode.c]-----> b_star_test_flag=1 \n");
                    b_start_test_flag=1;
                }
                else
                {
                    //c_dbg_secure_stmt("------[burning_mode.c]-----> b_star_test_flag=0 \n");
                    b_start_test_flag=0;
                }
                
                if(b_start_test_flag==1)
                {                          
                    ui1_test_delay_time++;
                    //c_dbg_secure_stmt("------[burning_mode.c]-----> start test =%x\n",ui1_test_delay_time);
                    if(ui1_test_delay_time==10)
                    {
                        //c_dbg_secure_stmt("------[burning_mode.c]-----> start test wifi\n");
                        //a_agent_async_invoke(Burning_Wifi_Test, NULL, 0);   
                        Burning_Wifi_Test();
                        ui1_test_delay_time=0;
                    }
                }
            }
#endif            
            
            if (! pt_this->b_active)
            {
                DBG_INFO((_INFO_HEADER"burning_mode_grab_activation\r\n"));

                /* Grab activation. */
                nav_grab_activation (NAV_COMP_ID_BURNING_MODE);
            }

            DBG_INFO((_INFO_HEADER"burning_mode_update_pattern\r\n"));

            /* Update burning pattern. */
            i4_ret = burning_mode_view_update (& pt_this->t_view);

            if (i4_ret != NAVR_OK)
            {
                DBG_ERROR((_ERROR_HEADER"burning_mode_view_update () failed\r\n"));
            }

            /* Show burning pattern. */
            i4_ret = burning_mode_view_show (& pt_this->t_view);

            if (i4_ret != NAVR_OK)
            {
                DBG_ERROR((_ERROR_HEADER"burning_mode_view_show () failed\r\n"));
            }

            if(0){  //ke_vizio_20130812 modify for issue TF1014VIZUSMTKO0-317.
				_set_burning_backlight(100);
			}
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _burning_mode_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* Executed in timer's thread context. */
    nav_request_context_switch (_burning_mode_next_pattern, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      burning_mode_rcu_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID burning_mode_rcu_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    /* Call default rcu key handler */
    nav_rcu_key_handler (ui4_key_code);
}
#ifdef APP_NAV_BURNING_PLAY_TONE
/*-----------------------------------------------------------------------------
 * Name     _burning_mode_stop_audio_tone
 * Description  Stop the audio test tone.
 * Input    -
 * Output   -
 * Returns  NAVR_OK     The operation succeeded.
 *          NAVR_FAIL   The operation failed.
 *---------------------------------------------------------------------------*/
static INT32 _burning_mode_stop_audio_tone (VOID)
{
    INT32 i4_ret;

    /* Stop audio test tone. */
    if (is_test_tone_play)
    {
        TV_WIN_ID_T e_win_id;
        STREAM_COMP_ID_T t_strm_comp_id;
        HANDLE_T h_aud_scc_comp;
        SM_COMMAND_T at_sm_cmds[3];

        at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
        at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
        at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
        at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
        at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
        at_sm_cmds[2].u.ui4_data = 0;
    
        i4_ret = c_scc_comp_open (at_sm_cmds, &h_aud_scc_comp);
        if (i4_ret != SMR_OK)
        {
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }

        i4_ret = nav_get_focus_id (&e_win_id);
        if (i4_ret != NAVR_OK)
        {
            DBG_ERROR (("%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }

        /* Stop audio test tone. */
        i4_ret = c_scc_aud_set_clip_ctrl(h_aud_scc_comp, SCC_AUD_CTRL_MODE_STOP);
        if (i4_ret != SMR_OK)
        {
            c_scc_comp_close (h_aud_scc_comp);
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }
        i4_ret = c_scc_comp_close (h_aud_scc_comp);
        if (i4_ret != SMR_OK)
        {
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }
        is_test_tone_play = FALSE;
        /* Play audio again. */
        i4_ret = nav_select_default_audio_stream(e_win_id, &t_strm_comp_id);
        if (i4_ret != NAVR_OK)
        {
            DBG_ERROR (("%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }
    }
    
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name     _burning_mode_start_audio_tone
 * Description  Start the audio test tone.
 * Input    -
 * Output   -
 * Returns  NAVR_OK     The operation succeeded.
 *          NAVR_FAIL   The operation failed.
 *---------------------------------------------------------------------------*/
static INT32 _burning_mode_start_audio_tone (VOID)
{
    INT32 i4_ret;
    
    if (!is_test_tone_play)
    {
        HANDLE_T h_aud_scc_comp;
        SM_COMMAND_T at_sm_cmds[3];
        TV_WIN_ID_T e_win_id;
        SCC_AUD_CLIP_T      t_aud_clip;
        SCC_AUD_CTRL_MODE_T e_audio_ctrl_mode;

        i4_ret = nav_get_focus_id (&e_win_id);
        if (i4_ret != NAVR_OK)
        {
            DBG_ERROR (("%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }
        at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
        at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
        at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
        at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
        at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
        at_sm_cmds[2].u.ui4_data = 0;
    
        i4_ret = c_scc_comp_open (at_sm_cmds, &h_aud_scc_comp);
        if (i4_ret != SMR_OK)
        {
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }

        /* Stop current current audio. */
        i4_ret = nav_sync_stop_stream (e_win_id, ST_AUDIO);
        if (i4_ret != NAVR_OK)
        {
            DBG_ERROR (("%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        }
        i4_ret = c_scc_aud_get_clip_ctrl (h_aud_scc_comp, &e_audio_ctrl_mode);
        if (i4_ret != SMR_OK)
        {
            c_scc_comp_close (h_aud_scc_comp);
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }

        if (e_audio_ctrl_mode == SCC_AUD_CTRL_MODE_PLAY)
        {
            i4_ret = c_scc_aud_set_clip_ctrl(h_aud_scc_comp, SCC_AUD_CTRL_MODE_STOP);
            if (i4_ret != SMR_OK)
            {
                c_scc_comp_close (h_aud_scc_comp);
                DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
                return NAVR_FAIL;
            }
        }
        /* FIXME !!Left 1KHz. */
        t_aud_clip.e_type           = SCC_AUD_CLIP_TYPE_TONE;           /* Tone */
        t_aud_clip.ui4_out_port_mask= ~0;                               /* All out port */
        t_aud_clip.ui4_repeat_cnt   = SCC_AUD_CLIP_REPEAT_CNT_FOREVER;  /* Forever */

        t_aud_clip.ui4_ch_mask        = ~0;
        t_aud_clip.u.ui4_tone_freq    = 3000;

        /* Set test tone. */
        i4_ret = c_scc_aud_set_clip (h_aud_scc_comp, &t_aud_clip, NULL, NULL);
        if (i4_ret != SMR_OK)
        {
            c_scc_comp_close (h_aud_scc_comp);
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }
        /* Play test tone. */
        i4_ret = c_scc_aud_set_clip_ctrl(h_aud_scc_comp, SCC_AUD_CTRL_MODE_PLAY);
        if (i4_ret != SMR_OK)
        {
            c_scc_comp_close (h_aud_scc_comp);
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }

        i4_ret = c_scc_comp_close (h_aud_scc_comp);
        if (i4_ret != SMR_OK)
        {
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }
        is_test_tone_play = TRUE;
    }

    return NAVR_OK;
}
#endif

static VOID _set_burning_backlight (INT16 i2_val)
{
    INT32 i4_ret;

    DBG_INFO(("\n _set_burning_backlight = %d\n", i2_val));

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT), i2_val );
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));

    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("\n _set_burning_backlight return fail \n"));
    }
}


/*-----------------------------------------------------------------------------
 * Name
 *      _burning_mode_under_ext_rc_control
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID burning_mode_under_ext_rc_control(
                    UINT16                       ui2_idx
                    )
{
    INT32              i4_ret;
    BURNING_MODE_T*    pt_this = & t_g_burning_mode;
			
    if (! pt_this->b_active)
    {
        /* Grab activation. */
        nav_grab_activation (NAV_COMP_ID_BURNING_MODE);
    }

    /* Update burning pattern. */
    i4_ret = burning_mode_ext_rc_control_view_update (& pt_this->t_view,ui2_idx);
    if (i4_ret != NAVR_OK)
    {
        //c_dbg_stmt("!!!!%s burning_mode_view_show FAIL\n", __func__);
// TOP Emerson 20090109 start
        return;
// TOP Emerson 20090109 end 
    }
	
    /* Show burning pattern. */
    i4_ret = burning_mode_view_show (& pt_this->t_view);	
    if (i4_ret != NAVR_OK)
    {
        //c_dbg_stmt("!!!!%s burning_mode_view_show FAIL\n", __func__);
// TOP Emerson 20090109 start
        return;
// TOP Emerson 20090109 end
    }
}


