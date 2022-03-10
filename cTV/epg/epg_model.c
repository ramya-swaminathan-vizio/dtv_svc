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
 * $RCSfile: epg_model.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/13 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 0dc5e5894593d8bd6b2c6ecc9869c8fa $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "epg/epg_model.h"

#ifdef APP_DVBT_SUPPORT
#include "res/app_util/a_custom.h"
#endif

/* Need for timeshift reselect funciton */
#ifdef APP_NAV_REC_TSHIFT_SUPPORT
#include "nav/record/tshift/nav_rec_tshift.h"
#endif

#ifndef SHORT_FORM_EVENT_DETAILS_HEADER
    #define SHORT_FORM_EVENT_DETAILS_HEADER     ""
#endif

#ifndef SHORT_FORM_EVENT_DETAILS_FOOTER
    #define SHORT_FORM_EVENT_DETAILS_FOOTER     ""
#endif

#ifndef SHORT_LONG_FORM_SEPERATOR
    #define SHORT_LONG_FORM_SEPERATOR           "\n"
#endif

#ifndef LONG_FORM_EVENT_DETAILS_HEADER
    #define LONG_FORM_EVENT_DETAILS_HEADER      ""
#endif

#ifndef LONG_FORM_EVENT_DETAILS_FOOTER
    #define LONG_FORM_EVENT_DETAILS_FOOTER      ""
#endif

#ifdef APP_NAV_CI_AUTO_SELECT_WITH_TOGGLE
    #define EPG_CI_AUTO_SELECT 1
#endif


/*
   Definitions.
*/

#define  EPG_BRDCST_TYPE         BRDCST_TYPE_UNKNOWN    /* Broadcast type. */

#define  EPG_NET_MASK            SB_VNET_EPG            /* Network mask. */

#define  DT_SHIFT_SECOND         (30)                   /* e.g. 11:59:30 will be shifted to 12:00:00 */

#define  DT_TIME_MAX_LEN         (80)                   /* Maximum length of time. */

#define  DT_DATE_MAX_LEN         (20)                   /* Maximum length of date. */

#define  DT_SYMBOL_MAX_LEN       (10)                   /* Maximum length of symbol. */

#define  WGL_MSG_MAX_DELAY       (200)                  /* Maximum delay for Widget Libary to process messages (in milliseconds). */

#ifdef APP_EPG_FULL_VIDEO
    #ifndef EPG_OSD_ALPHA
        #define  EPG_OSD_ALPHA   (255)                  /* Opaque OSD. (original value is 220) */
    #endif
#endif

#ifndef EPG_OSD_ALPHA
    #define  EPG_OSD_ALPHA       (255)                  /* Opaque OSD. */
#endif

/* Blue mute parameters */
#define EPG_BLUE_MUTE_R          (0)
#define EPG_BLUE_MUTE_G          (0)
#define EPG_BLUE_MUTE_B          (0xFF)

/*-----------------------------------------------------------------------------
                    static function prototype declaraions
-----------------------------------------------------------------------------*/
/*
   Callback function of controller.
*/
extern INT32 epg_ctrl_process_msg (UINT32 ui4_type, const VOID* pv_msg, SIZE_T z_msg_len);


/*
   EPG model data.
*/
typedef struct
{
    /* Application data. */
    HANDLE_T               h_epg;                   /* EPG handle. */
    BOOL                   b_pause;                 /* Indicates if EPG is paused. */

    /* Service data. */
    HANDLE_T               h_svctx;                 /* Service context handle. */
    HANDLE_T               h_svctx_sub;             /* Sub service context. */
    BOOL                   b_with_cc;               /* Indicate if current event has CC. */

    /* Date-time data. */
    HANDLE_T               h_dt;                    /* Date-time handle. */

    /* Configuration data. */
    UINT16                 ui2_lang_id;             /* Language id. */
    ISO_639_LANG_T         s639_lang;               /* ISO 639 language. */
    UINT16                 ui2_acfg_id_lang;        /* Language configuration acfg id. */
    UINT16                 ui2_acfg_id_vchip;       /* V-chip configuration acfg id. */
    UINT16                 ui2_acfg_id_brdsvc;      /* Broadcast service configuration acfg id. */

    /* SVL data. */
    HANDLE_T               h_svl;                   /* SVL handle. */
    UINT16                 ui2_svl_id;              /* SVL id. */
    SVL_REC_T              t_svl_rec;               /* SVL record. */
    CHAR*                  ps_tuner_name;           /* Tuner name. */
    BOOL                   b_svl_found;             /* Indicate if SVL is found. */

    /* RRCTX data. */
    HANDLE_T               h_rrctx;                 /* RRCTX handle. */

    /* OSD data. */
    HANDLE_T               h_canvas;                /* Canvas handle. */
    GL_HPLANE_T            h_plane;                 /* Plane handle. */
    UINT32                 ui4_canvas_width;        /* OSD width. */
    UINT32                 ui4_canvas_height;       /* OSD height. */
    INT32                  i4_osd_offset_x;         /* OSD offset x. */
    INT32                  i4_osd_offset_y;         /* OSD offset y. */

    EPG_CONFIG_T           t_config;                /* EPG configuration data */

}   EPG_MODEL_T;

/*
   Global EPG model data.
*/
static EPG_MODEL_T  t_g_model;


/*
   AEE lifecycle callback functions.
*/
static BOOL  _epg_app_nfy_fct (HANDLE_T h_app, VOID* pv_tag, APP_NFY_REASON_T e_nfy_reason);
static INT32 _epg_app_init_fct (const CHAR* ps_name, HANDLE_T h_app);
static INT32 _epg_app_exit_fct (HANDLE_T h_app, APP_EXIT_MODE_T e_exit_mode);
static INT32 _epg_app_pause_fct (HANDLE_T h_app);
static INT32 _epg_app_resume_fct (HANDLE_T h_app);
static INT32 _epg_app_process_msg_fct (HANDLE_T h_app, UINT32 ui4_type, const VOID* pv_msg, SIZE_T z_msg_len, BOOL b_paused);
static BOOL _epg_app_system_key_cb(UINT32 ui4_evt_code);

/*
   Notifications from middleware components.
*/
static VOID  _epg_nfy_svctx (HANDLE_T h_svctx, SVCTX_COND_T e_nfy_cond, SVCTX_NTFY_CODE_T e_code, STREAM_TYPE_T e_stream_type, VOID* pv_nfy_tag);
static VOID  _epg_nfy_evctx (HANDLE_T h_event, EVCTX_COND_T e_cond, VOID* pv_nfy_tag, UINT32 ui4_data);
static VOID  _epg_nfy_svl (HANDLE_T h_svl, SVL_COND_T e_cond, UINT32 ui4_reason, VOID* pv_tag, UINT32 ui4_data);
static VOID  _epg_nfy_timer (HANDLE_T h_timer, VOID* pv_tag);
static VOID  _epg_nfy_acfg (UINT16 ui2_nfy_id, VOID* pv_tag, UINT16 ui2_id);
static VOID  _epg_nfy_dt (HANDLE_T h_dt, VOID* pv_tag, DT_COND_T t_dt_cond, TIME_T t_delta);
static INT32 _epg_nfy_wgl (UINT32 ui4_msg, VOID* pv_param1, VOID* pv_param2);
static VOID  _epg_nfy_rrt (HANDLE_T h_rrctx, VOID* pv_tag, UINT32 ui4_reason);


/*
   Internal operations of EPG Model.
*/
static INT32 _epg_model_update_svl (VOID);
static INT32 _epg_model_get_svl_rec_by_surf_mode (HANDLE_T h_svl, UINT32 ui4_nw_mask, SURF_MODE_T e_surf_mode, UINT32* pui4_channel_id, SVL_REC_T* pt_svl_rec);
static INT32 _epg_model_update_brdcst_svc (VOID);
static INT32 _epg_model_update_language (VOID);
static INT32 _epg_model_init_canvas (VOID);

#ifndef APP_DVBT_SUPPORT
/*
   Query CC info.
*/
static BOOL _epg_svc_is_with_cc_dscrptr(EPG_CC_QUERY_DATA_T* pt_cc_query_data);
#endif

static BOOL _epg_svc_is_timeshift_pvr_activing(VOID);

/*-----------------------------------------------------------------------------
 * Name: _epg_app_nfy_fct
 *
 * Description: This function is called in the thread context of the EPG
 *              application when a message is received, and when a message is
 *              processed. When a message is received, this API will be called
 *              with one of the APP_NFY_PRE_* notifiction reasons. In that case,
 *              this API should return TRUE if the message is to be ignored, or
 *              FALSE is the message is to be processed. If the message is
 *              processed, then this API will be called again, this time after
 *              the message is processed, with one of the APP_NFY_*_OK or
 *              APP_NFY_*_FAILED notification reasons.
 *
 * Inputs:  h_app               Contains the application handle.
 *          pv_tag              References a tag value. An asynchronous call is
 *                              made if pv_tag is NULL, or a synchronous call is
 *                              made if pv_tag is not a NULL pointer.
 *          e_nfy_reason        Contains the notification reason.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static BOOL _epg_app_nfy_fct (HANDLE_T          h_app,
                              VOID*             pv_tag,
                              APP_NFY_REASON_T  e_nfy_reason)
{
    /*
    TRUE  = ignore message
    FALSE = process message
    */

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_app_pre_resume_cb_fct
 *
 * Description: This function is called by Application Manager when EPG is going
 *              to be resumed.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE                Accept resume request. (EPG will be resumed.)
 *          FALSE               Rejest resume request. (EPG will not be resumed.)
 ----------------------------------------------------------------------------*/
static BOOL _epg_app_pre_resume_cb_fct (VOID)
{
    INT32              i4_rc;
    BOOL               b_resume;
    TV_WIN_ID_T        e_focus_wnd;
    ISL_REC_T          t_isl_rec;

    b_resume = TRUE;

    do
    {
        /* Do not allow to resume EPG in PVR & Timeshift recording status */
        if (epg_is_active_refused())
        {
            b_resume = FALSE;
        }

#ifdef APP_EPG_NO_RESUME_IN_PIP_POP

        TV_MODE_T      e_tv_mode;

        i4_rc = a_tv_get_mode (& e_tv_mode);

        if (i4_rc != TVR_OK)
        {
            break;
        }

        if (e_tv_mode != TV_MODE_TYPE_NORMAL) /* PIP/POP */
        {
            /* Don't resume EPG if it is PIP/POP mode. */
            b_resume = FALSE;

            break;
        }

#endif /* APP_EPG_NO_RESUME_IN_PIP_POP */

        /* Check if the source for the focused window is TV. */
        i4_rc = a_tv_get_focus_win (& e_focus_wnd);

        if (i4_rc != TVR_OK)
        {
            break;
        }

        i4_rc = a_tv_get_isl_rec_by_win_id (e_focus_wnd, & t_isl_rec);

        if (i4_rc != TVR_OK)
        {
            break;
        }

        if (DEV_GET_GROUP_ID (t_isl_rec.t_avc_info.e_video_type) != DEV_TUNER)
        {
            b_resume = FALSE;
            break;
        }

        /* show EPG if a_tv_net_get_tv_svc_status == APP_TV_NET_SVC_STATUS_PAUSED */
        if (a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_PAUSED)
        {
            b_resume = FALSE;
            break;
        }


        /* Check whether SVL is available */

        i4_rc = a_tv_get_svl_id(& t_g_model.ui2_svl_id);

        if (i4_rc != TVR_OK)
        {
            break;
        }

        /* Free SVL handle. */
        if (t_g_model.h_svl != NULL_HANDLE)
        {
            c_svl_close (t_g_model.h_svl);

            t_g_model.h_svl = NULL_HANDLE;
        }

        /* Update SVL. */
        _epg_model_update_svl();

        /* Do not allow to resume EPG if there is no SVL */
        if (!t_g_model.b_svl_found)
        {
            b_resume = FALSE;
        }

        /* Free SVL handle. */
        if (t_g_model.h_svl != NULL_HANDLE)
        {
            c_svl_close (t_g_model.h_svl);

            t_g_model.h_svl = NULL_HANDLE;
        }

    } while (0);

    return b_resume;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_app_init_fct
 *
 * Description: This function is called in the context of the EPG application
 *              when the application starts.
 *
 * Inputs:  ps_name             References the application's name.
 *          h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_app_init_fct (const CHAR*    ps_name,
                                HANDLE_T       h_app)
{
    DBG_INFO (("<EPG> initializing EPG (application handle = %d)\n\r", (int) h_app));

#ifdef APP_EPG_CUSTOM_PRE_PROCESS_SUPPORT

    RET_ON_ERR (epg_custom_pre_init ());

#endif /* APP_EPG_CUSTOM_PRE_PROCESS_SUPPORT */

    /* Reset model variables. */
    c_memset (& t_g_model, 0, sizeof(EPG_MODEL_T));

    /* Store EPG handle. */
    t_g_model.h_epg = h_app;

    /* Register to Date-Time library. */
    RET_ON_ERR (c_dt_reg_nfy_fct (_epg_nfy_dt, NULL, & t_g_model.h_dt));

    /* Register to Widget Library. */
    RET_ON_ERR (c_wgl_register (_epg_nfy_wgl));

    /* Set maximum delay tolerance to Widget Library. */
    RET_ON_ERR (c_wgl_set_delay_tolerance (WGL_MSG_MAX_DELAY));

    /* Initialize CLI. */
    RET_ON_ERR (epg_cli_init ());

    /* Register to GUI language group. */
    RET_ON_ERR (a_cfg_notify_reg (APP_CFG_GRPID_GUI_LANG,
                                  NULL,
                                  _epg_nfy_acfg,
                                  & t_g_model.ui2_acfg_id_lang));

    /* Register to V-chip group. */
    RET_ON_ERR (a_cfg_notify_reg (APP_CFG_GRPID_VCHIP,
                                  NULL,
                                  _epg_nfy_acfg,
                                  & t_g_model.ui2_acfg_id_vchip));

    /* Register to Broadcast Service group. */
    RET_ON_ERR (a_cfg_notify_reg (APP_CFG_GRPID_BS,
                                  NULL,
                                  _epg_nfy_acfg,
                                  & t_g_model.ui2_acfg_id_brdsvc));

    /* Open SVCTX. */
    RET_ON_ERR (c_svctx_open (SVCTX_NAME_MAIN, & t_g_model.h_svctx));
    RET_ON_ERR (c_svctx_open (SVCTX_NAME_SUB,  & t_g_model.h_svctx_sub));

    /* Register listener to SVCTX. */
    RET_ON_ERR (c_svctx_set_listener (t_g_model.h_svctx, _epg_nfy_svctx, NULL));

    /* Open RRCTX. */
    RET_ON_ERR (c_rrctx_open_rating (RRCTX_RATING_TYPE_RRT,
                                     NULL,
                                     _epg_nfy_rrt,
                                     NULL,
                                     & t_g_model.h_rrctx));

    /* Update language. */
    RET_ON_ERR (_epg_model_update_language ());

    /* Init canvas. */
    RET_ON_ERR (_epg_model_init_canvas ());

#ifdef APP_EPG_FULL_VIDEO
    /* Default config is No AV in EPG background. */
    t_g_model.t_config.e_av_config = EPG_AV_CONFIG_NO_VIDEO_AUDIO;
#else
    /* With PIP video in EPG background. */
    t_g_model.t_config.e_av_config = EPG_AV_CONFIG_WITH_PIP_VIDEO;
#endif

    /* Call to controller. */
    epg_ctrl_process_msg (EPG_MSG_APP_INIT, NULL, 0);

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_app_exit_fct
 *
 * Description: This function is called in the context of the EPG application
 *              when the application quits. This API should be
 *              responsible for saving data, clean-up, etc.
 *
 * Inputs:  h_app               Contains the application handle.
 *          e_exit_mode         Contains the exit mode.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_app_exit_fct (HANDLE_T         h_app,
                                APP_EXIT_MODE_T  e_exit_mode)
{
    DBG_INFO (("<EPG> exit EPG (handle = %d)\n\r", (int) h_app));

#ifdef APP_EPG_CUSTOM_PRE_PROCESS_SUPPORT

    RET_ON_ERR (epg_custom_pre_exit ());

#endif /* APP_EPG_CUSTOM_PRE_PROCESS_SUPPORT */

    /* Free SVCTX handle. */
    if (t_g_model.h_svctx != NULL_HANDLE)
    {
        RET_ON_ERR (c_svctx_close (t_g_model.h_svctx));
    }

    /* Free SVL handle. */
    if (t_g_model.h_svl != NULL_HANDLE)
    {
        RET_ON_ERR (c_svl_close (t_g_model.h_svl));
    }

    /* Free Date-Time handle. */
    if (t_g_model.h_dt != NULL_HANDLE)
    {
        RET_ON_ERR (c_handle_free (t_g_model.h_dt));
    }

    /* Unregister acfg. */
    a_cfg_notify_unreg (t_g_model.ui2_acfg_id_lang);
    a_cfg_notify_unreg (t_g_model.ui2_acfg_id_vchip);
    a_cfg_notify_unreg (t_g_model.ui2_acfg_id_brdsvc);

    /* Call to controller. */
    epg_ctrl_process_msg (EPG_MSG_APP_EXIT, NULL, 0);

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_app_pause_fct
 *
 * Description: This function is called in the context of the EPG application
                when the application is paused.
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_app_pause_fct (HANDLE_T  h_app)
{
    DBG_INFO (("<EPG> pause EPG (handle = %d)\n\r", (int) h_app));

#ifdef APP_EPG_CUSTOM_PRE_PROCESS_SUPPORT

    RET_ON_ERR (epg_custom_pre_pause ());

#endif /* APP_EPG_CUSTOM_PRE_PROCESS_SUPPORT */

    /* Set plane alpha to opaque. */
    RET_ON_ERR (c_gl_plane_set_alpha (t_g_model.h_plane, 255));

    /* Stop CLI command if it it's running. */
    if (epg_cli_is_running ())
    {
        /* Stop cli command. */
        epg_cli_stop ();
    }

    /* Free SVL handle. */
    if (t_g_model.h_svl != NULL_HANDLE)
    {
        RET_ON_ERR (c_svl_close (t_g_model.h_svl));

        t_g_model.h_svl = NULL_HANDLE;
    }

    /* Call to controller. */
    epg_ctrl_process_msg (EPG_MSG_APP_PAUSE, NULL, 0);

    /* Turn on pause flag. */
    t_g_model.b_pause = TRUE;

    /* Issue a request to exit EPG. */
    /* a_amb_exit_app (EPG_NAME); */

#ifdef LINUX_TURNKEY_SOLUTION
    a_tv_net_OSD_disapper();
#endif

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_app_resume_fct
 *
 * Description: This function is called in the context of the EPG application
 *              when the application is resumed.
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_app_resume_fct (HANDLE_T  h_app)
{
    TV_MODE_T    e_tv_mode;

    DBG_INFO (("<EPG> resume EPG (handle = %d)\n\r", (int) h_app));

    /* show EPG if a_tv_net_get_tv_svc_status == APP_TV_NET_SVC_STATUS_PAUSED */
    if (a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_PAUSED)
    {
        return 0;
    }


#ifdef APP_EPG_CUSTOM_PRE_PROCESS_SUPPORT

    RET_ON_ERR (epg_custom_pre_resume ());

#endif /* APP_EPG_CUSTOM_PRE_PROCESS_SUPPORT */

    /* Set plane alpha. */
    RET_ON_ERR (c_gl_plane_set_alpha (t_g_model.h_plane, EPG_OSD_ALPHA));

    /* Set TV mode to normal. */
    RET_ON_ERR (a_tv_get_mode (& e_tv_mode));

    if (e_tv_mode != TV_MODE_TYPE_NORMAL)
    {
        EPG_LOG_ON_FAIL (epg_svc_blank_video (TRUE));
        EPG_LOG_ON_FAIL (epg_svc_blank_video (FALSE));
        RET_ON_ERR (a_tv_set_mode (TV_MODE_TYPE_NORMAL));
        RET_ON_ERR (a_tv_set_first_input_src_id_by_type (TV_WIN_ID_MAIN, INP_SRC_TYPE_TV));
    }

    /* Update broadcast service. */
    RET_ON_ERR (_epg_model_update_brdcst_svc ());

    /* Call to controller. */
    epg_ctrl_process_msg (EPG_MSG_APP_RESUME, NULL, 0);

    /* Turn off pause flag. */
    t_g_model.b_pause = FALSE;

#ifdef LINUX_TURNKEY_SOLUTION
	a_tv_net_OSD_appear ();
#endif

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_app_process_msg_fct
 *
 * Description: This function is called in the context of the application
 *              when a message is processed.
 *
 * Inputs:  h_app               Contains the application handle.
 *          ui4_type            Contains the type of the data contained in
 *                              pv_msg, or simple a request type. Values are
 *                              defined by the application.
 *          pv_msg              References the message data.
 *          z_msg_len           Contains the length (in bytes) of pv_msg.
 *          b_paused            Sepcifies whether the application is currently
 *                              paused.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_app_process_msg_fct (HANDLE_T     h_app,
                                       UINT32       ui4_type,
                                       const VOID*  pv_msg,
                                       SIZE_T       z_msg_len,
                                       BOOL         b_paused)
{
    BOOL      b_nfy;
    VOID*     pv_nfy_msg;
    SIZE_T    z_nfy_msg_len;

#ifdef APP_EPG_CUSTOM_PRE_PROCESS_SUPPORT

    RET_ON_ERR (epg_custom_pre_process_msg (ui4_type,
                                            pv_msg,
                                            z_msg_len));

#endif /* APP_EPG_CUSTOM_PRE_PROCESS_SUPPORT */

    pv_nfy_msg    = (VOID*) pv_msg;
    z_nfy_msg_len = z_msg_len;

    switch (ui4_type)
    {
        case EPG_MSG_CFG_LANGUAGE_UPDATED: /* Language updated. */
        {
            RET_ON_ERR (_epg_model_update_language ());
        }
        break;

        case EPG_MSG_CFG_BRDCST_SVC_UPDATED: /* Broadcast service updated. */
        {
            RET_ON_ERR (_epg_model_update_brdcst_svc ());
        }
        break;

        case EPG_MSG_SVL_UPDATED: /* SVL updated. */
        {
            RET_ON_ERR (_epg_model_update_svl ());
        }
        break;

        default:
            break;
    }

    /* Decide if a notification to clients is required. */
    b_nfy = TRUE;

    if (t_g_model.b_pause) /* In paused mode. */
    {
        if (ui4_type == EPG_MSG_CFG_LANGUAGE_UPDATED) /* Language updated. */
        {
            b_nfy = TRUE;
        }
        else /* Other messages. */
        {
            b_nfy = FALSE;
        }
    }
    else /* Not in paused mode. */
    {
        /* Service notifications. */
        if ((ui4_type > EPG_MSG_SVC_BEGIN) &&
            (ui4_type < EPG_MSG_SVC_END))
        {
            if (! t_g_model.b_svl_found) /* SVL is not found. */
            {
                b_nfy = FALSE;
            }
            else /* SVL is found. */
            {
                if (pv_msg == NULL) /* Always notify clients if pv_msg is NULL. */
                {
                    b_nfy = TRUE;
                }
                else /* Check if channel IDs match. */
                {
                    if ((*((UINT32*)pv_msg)) != a_util_cnfg_get_crnt_channel_id()) /* Channel IDs do not match. */
                    {
                        b_nfy = FALSE;
                    }
                }
            }
        }
    }

    if (b_nfy)
    {
        /* Call to controller. */
        epg_ctrl_process_msg (ui4_type, pv_nfy_msg, z_nfy_msg_len);
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_app_system_key_cb
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL _epg_app_system_key_cb(UINT32 ui4_evt_code)
{
    ui4_evt_code = IOM_GET_EVT_GRP_ID(ui4_evt_code);

    if (epg_app_is_pause() == FALSE)
    {
        DBG_INFO(("\n _epg_app_system_key_cb: FALSE \n"));
        if(ui4_evt_code == BTN_EPG)
        {
            return FALSE;
        }
    }

    return TRUE;
}


/*-----------------------------------------------------------------------------
 * Name: _epg_nfy_svctx
 *
 * Description: This callback function is called by SVCTX when service's
 *              condition is changed.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _epg_nfy_svctx (HANDLE_T           h_svctx,
                            SVCTX_COND_T       e_nfy_cond,
                            SVCTX_NTFY_CODE_T  e_code,
                            STREAM_TYPE_T      e_stream_type,
                            VOID*              pv_nfy_tag)
{
    INT32              i4_rc;
    UINT32             ui4_channel_id;
    UINT32             ui4_nw_mask;
    SVC_BLOCK_COND_T   e_block_cond;
    SIZE_T             z_size;

    /* Get attached channel. */
    ui4_channel_id = (UINT32) pv_nfy_tag;

    /* Check whether notify is from Timeshift or PVR, treat it same as from TV  */
    if (_epg_svc_is_timeshift_pvr_activing())
    {
        ui4_channel_id = a_util_cnfg_get_crnt_channel_id();
    }

    /* Check if the attached channel id matches current channel id. */
    if (ui4_channel_id == a_util_cnfg_get_crnt_channel_id())
    {
        /* Get network mask. */
        ui4_nw_mask = t_g_model.t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask;

        switch (e_code)
        {
            case SVCTX_NTFY_CODE_SIGNAL_LOCKED: /* Signal locked. */
            {
                DBG_INFO (("<EPG> SVCTX notify: Signal locked\n\r"));

                /* Send a signal-locked message to EPG. */
                epg_app_send_msg (EPG_MSG_SVC_SIGNAL_LOCKED, & ui4_channel_id, 4);
            }
            break;

            case SVCTX_NTFY_CODE_SIGNAL_LOSS: /* Signal loss. */
            {
                DBG_INFO (("<EPG> SVCTX notify: Signal loss\n\r"));

                /* Send a signal-loss message to EPG. */
                epg_app_send_msg (EPG_MSG_SVC_SIGNAL_LOSS, & ui4_channel_id, 4);
            }
            break;

            case SVCTX_NTFY_CODE_SERVICE_BLOCKED: /* Service blocked. */
            {
                DBG_INFO (("<EPG> SVCTX notify: Service blocked\n\r"));

                z_size = sizeof (SVC_BLOCK_COND_T);

                i4_rc = c_svctx_get (t_g_model.h_svctx,
                                     SVCTX_COMMON_GET_TYPE_BLOCK_COND,
                                     & e_block_cond,
                                     & z_size);

                if (i4_rc != SVCTXR_OK)
                {
                    e_block_cond = SVC_BLOCK_COND_USER_BLOCK_INP;
                }

                if (e_block_cond == SVC_BLOCK_COND_USER_BLOCK_INP) /* Input blocked. */
                {
                    DBG_INFO (("<EPG> SVCTX notify: Input blocked\n\r"));

                    /* Send an input-blocked message to EPG. */
                    epg_app_send_msg (EPG_MSG_SVC_INPUT_BLOCKED, & ui4_channel_id, 4);
                }
                else if (e_block_cond == SVC_BLOCK_COND_USER_BLOCK_CH) /* Channel blocked. */
                {
                    DBG_INFO (("<EPG> SVCTX notify: Channel blocked\n\r"));

                    /* Send a channel-blocked message to EPG. */
                    epg_app_send_msg (EPG_MSG_SVC_CHANNEL_BLOCKED, & ui4_channel_id, 4);
                }
                else if (e_block_cond == SVC_BLOCK_COND_EXCEED_RATING) /* Event blocked. */
                {
                    DBG_INFO (("<EPG> SVCTX notify: Event locked\n\r"));

                    /* Send a event-blocked message to EPG. */
                    epg_app_send_msg (EPG_MSG_SVC_EVENT_BLOCKED, & ui4_channel_id, 4);
                }
            }
            break;

            case SVCTX_NTFY_CODE_NORMAL: /* Normal service. */
            {
                DBG_INFO (("<EPG> SVCTX notify: Normal service\n\r"));

                if ((ui4_nw_mask & SB_VNET_ACTIVE) == 0) /* Hidden channel. */
                {
                    DBG_INFO (("<EPG> SVCTX notify: Hidden channel\n\r"));

                    /* Send a hidden-channel message to EPG. */
                    epg_app_send_msg (EPG_MSG_SVC_HIDDEN_CHANNEL, & ui4_channel_id, 4);
                }
                else /* Normal service. */
                {
                    /* Send a normal-service message to EPG. */
                    epg_app_send_msg (EPG_MSG_SVC_NORMAL_SERVICE, & ui4_channel_id, 4);
                }
            }
            break;

            case SVCTX_NTFY_CODE_SCDB_ADD:
            case SVCTX_NTFY_CODE_SCDB_DEL:
            case SVCTX_NTFY_CODE_SCDB_MODIFY: /* SCDB updated. */
            {
                #ifndef EPG_CI_AUTO_SELECT
                DBG_INFO (("<EPG> SVCTX notify: SCDB updated\n\r"));
                /* If CC is auto select, do not need re-query CC info when SCDB update */
                /* Send a SCDB-updated message to EPG. */
                epg_app_send_msg (EPG_MSG_SVC_SCDB_UPDATED, & ui4_channel_id, 4);
                #endif
            }
            break;

#if 0
            case SVCTX_NTFY_CODE_CA: /* Conditional access. */
            {
                DBG_INFO (("<EPG> SVCTX notify: Scrambled service\n\r"));

                SVCTX_CA_INFO_T    t_ca_info;

                /* Get CA info. */
                i4_rc = c_svctx_get_ca_info (h_svctx,
                                             e_stream_type,
                                             & t_ca_info);

                if (i4_rc == SVCTXR_OK)
                {
                    switch (t_ca_info.e_event)
                    {
                        case SM_EVN_CA_COND_NOT_AUTHORIZED: /* Scrambled. */
                        {
                            /* Send an unauthorized message to EPG. */
                            epg_app_send_msg (EPG_MSG_SVC_SCRAMBLED, & ui4_channel_id, 4);
                        }
                        break;

                        case SM_EVN_CA_COND_AUTHORIZED:     /* Authorized. */
                        case SM_EVN_CA_COND_FREE:           /* Free. */
                        {
                            /* Send an authorized message to EPG. */
                            epg_app_send_msg (EPG_MSG_SVC_AUTHORIZED, & ui4_channel_id, 4);
                        }
                        break;

                        default:
                            break;
                    }
                }
            }
            break;
#endif

            case SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_VIDEO_SVC:
            case SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_NO_VIDEO_SVC:
            case SVCTX_NTFY_CODE_SCRAMBLED_VIDEO_NO_AUDIO_SVC:
            {
                /* Send scrambled message to EPG. */
                epg_app_send_msg (EPG_MSG_SVC_SCRAMBLED, & ui4_channel_id, 4);
            }
            break;

            case SVCTX_NTFY_CODE_SCRAMBLED_VIDEO_CLEAR_AUDIO_SVC:
            {
                /* Send audio-only message to EPG. */
                epg_app_send_msg (EPG_MSG_SVC_AUDIO_ONLY, & ui4_channel_id, 4);
            }
            break;

            case SVCTX_NTFY_CODE_AUDIO_VIDEO_SVC: /* Normal AV. */
            {
                DBG_INFO (("<EPG> SVCTX notify: Normal AV\n\r"));

                epg_app_send_msg (EPG_MSG_SVC_AUDIO_VIDEO, & ui4_channel_id, 4);
            }
            break;

            case SVCTX_NTFY_CODE_AUDIO_ONLY_SVC: /* Audio-only program. */
            {
                DBG_INFO (("<EPG> SVCTX notify: Audio-only\n\r"));

                epg_app_send_msg (EPG_MSG_SVC_AUDIO_ONLY, & ui4_channel_id, 4);
            }
            break;

            case SVCTX_NTFY_CODE_NO_AUDIO_VIDEO_SVC: /* No AV. */
            {
                DBG_INFO (("<EPG> SVCTX notify: No AV\n\r"));

                epg_app_send_msg (EPG_MSG_SVC_NO_AUDIO_VIDEO, & ui4_channel_id, 4);
            }
            break;

            #if 0

            case SVCTX_NTFY_CODE_WITH_CC_AVIL_INDICATOR: /* With CC. */
            {
                DBG_INFO (("<EPG> SVCTX notify: With CC\n\r"));

                t_g_model.b_with_cc = TRUE;

                epg_app_send_msg (EPG_MSG_SVC_WITH_CC, & ui4_channel_id, 4);
            }
            break;

            case SVCTX_NTFY_CODE_NO_CC_AVIL_INDICATOR:   /* No CC. */
            {
                DBG_INFO (("<EPG> SVCTX notify: No CC\n\r"));

                t_g_model.b_with_cc = FALSE;

                epg_app_send_msg (EPG_MSG_SVC_NO_CC, & ui4_channel_id, 4);
            }
            break;

            case SVCTX_NTFY_CODE_EXISTED_CC_IND_CHG:   /* CC indicator change */
            {
                DBG_INFO (("<EPG> SVCTX notify: CC indicator change\n\r"));

                epg_app_send_msg (EPG_MSG_SVC_CC_CHG, & ui4_channel_id, 4);
            }
            break;
            #endif

            case SVCTX_NTFY_CODE_WITH_CC_AVIL_INDICATOR:
            case SVCTX_NTFY_CODE_NO_CC_AVIL_INDICATOR:
            {
                #ifndef EPG_CI_AUTO_SELECT
                DBG_INFO (("<EPG> SVCTX notify: CC_AVIL_INDICATOR change \n\r"));
                /* If CC is auto select, do not need re-query CC info when SCDB update */
                epg_app_send_msg (EPG_MSG_SVC_CC_AVIL_STATUS_CHG, & ui4_channel_id, 4);
                #endif
            }
            break;

            case SVCTX_NTFY_CODE_EXISTED_CC_IND_CHG:   /* CC indicator change */
            {
                DBG_INFO (("<EPG> SVCTX notify: EXISTED_CC_IND change\n\r"));

                epg_app_send_msg (EPG_MSG_SVC_EXISTED_CC_IND_CHG, & ui4_channel_id, 4);
            }
            break;

            /* Update rating info. when receive NOT_READY */
            /* CR[215669] [Bitstream Test] Rating info cannot refresh in EPG */
            case SVCTX_NTFY_CODE_CRNT_EVN_NOT_READY:
            {
                DBG_INFO (("<EPG> SVCTX notify: CRNT_EVN_NOT_READY change\n\r"));

                epg_app_send_msg (EPG_MSG_SVC_CRNT_EVN_NOT_READY, NULL, 0);
            }
            break;

            /* Update whole program list when receive CRNT_EVN_READY */
            /* CR[215669] [Bitstream Test] Rating info cannot refresh in EPG */
            case SVCTX_NTFY_CODE_CRNT_EVN_READY:
            {
                DBG_INFO (("<EPG> SVCTX notify: READY change\n\r"));

                epg_app_send_msg (EPG_MSG_SVC_CRNT_EVN_READY, NULL, 0);
            }
            break;

            default:
                break;
        }
    }

    /*
       The Service Context module will call this function to notify any change
       in the service context.  The purpose of this API is to monitor any channel
       change initiate by another applications. When channel change occurs, the
       EPG will take action to select current service to update service information.
    */
    if (e_code == SVCTX_NTFY_CODE_SERVICE_CHANGING)
    {
        DBG_INFO (("<EPG> SVCTX notify: Service changing\n\r"));

        /* Send a service-changed message to EPG. */
        epg_app_send_msg (EPG_MSG_SVC_SERVICE_CHANGED, NULL, 0);
    }
}

/*-----------------------------------------------------------------------------
 * Name: _epg_nfy_svl
 *
 * Description: This callback function is called by SVL when Service List is
 *              updated.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _epg_nfy_svl (HANDLE_T      h_svl,
                          SVL_COND_T    e_cond,
                          UINT32        ui4_reason,
                          VOID*         pv_tag,
                          UINT32        ui4_data)
{
    DBG_INFO (("<EPG> SVL notification = %d\n\r", e_cond));

    /* Do not handle UNKNOWN reason SVL update */
    /* CR[DTV00215661] Video flash black mute in EPG */
    if (e_cond == SVL_UPDATED && ui4_reason == SVL_REASON_UNKNOWN)
    {
        return;
    }

    if ((e_cond == SVL_UPDATED) ||
        (e_cond == SVL_CLOSED))
    {
       if (e_cond == SVL_CLOSED) /* Handle closed. */
       {
           t_g_model.h_svl = NULL_HANDLE;
       }

       /* Send a svl-updated message to EPG. */
       epg_app_send_msg (EPG_MSG_SVL_UPDATED, & ui4_reason, 4);
    }
}

/*-----------------------------------------------------------------------------
 * Name: _epg_nfy_evctx
 *
 * Description: This callback function is called by EVCTX when event's condition
 *              is changed.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _epg_nfy_evctx (HANDLE_T        h_event,
                            EVCTX_COND_T    e_cond,
                            VOID*           pv_nfy_tag,
                            UINT32          ui4_data)
{
    if (e_cond == EVCTX_COND_AVAIL) /* Event available. */
    {
        /* Send a event-available message to EPG. */
        epg_app_send_msg (EPG_MSG_EVT_AVAIL, & h_event, 4);
    }
    else if (e_cond == EVCTX_COND_UNAVAIL) /* Event unavailable. */
    {
        if ((ui4_data == EVCTX_REASON_EVENT_NOT_FOUND) || /* Event is not found. */
            (ui4_data == EVCTX_REASON_DT_TIMEOUT)      || /* Date-time callback timeout. */
            (ui4_data == EVCTX_REASON_EVENT_EXPIRED)
            )
        {
			DBG_INFO (("<EPG> The unauail event reasom is  = %d\n\r", ui4_data));

            /* Send a event-unavialable message to EPG. */
            epg_app_send_msg (EPG_MSG_EVT_UNAVAIL, & h_event, 4);
        }
    }
    else if (e_cond == EVCTX_COND_EXPIRED) /* Event expired. */
    {
        /* Send a event-expired message to EPG. */
        epg_app_send_msg (EPG_MSG_EVT_EXPIRED, & h_event, 4);
    }
    else if (e_cond == EVCTX_COND_UPDATED) /* Event updated. */
    {
        /* Send a event-updated message to EPG. */
        epg_app_send_msg (EPG_MSG_EVT_UPDATED, & h_event, 4);
    }
}

/*-----------------------------------------------------------------------------
 * Name: _epg_nfy_timer
 *
 * Description: This callback function is called when timers expired.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _epg_nfy_timer (HANDLE_T    h_timer,
                            VOID*       pv_tag)
{
    /* Send a timer expired message to EPG. */
    epg_app_send_msg (EPG_MSG_TIMER_EXPIRED, & h_timer, 4);
}

/*-----------------------------------------------------------------------------
 * Name: _epg_nfy_acfg
 *
 * Description: This callback function is called when config database is updated.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _epg_nfy_acfg (UINT16        ui2_nfy_id,
                           VOID*         pv_tag,
                           UINT16        ui2_id)
{
    DBG_INFO (("<EPG> ACFG notification, ID = %d\n\r", ui2_id));

    if (CFG_GET_GROUP (ui2_id) == APP_CFG_GRPID_GUI_LANG) /* Language updated. */
    {
        /* Send a language-updated message to EPG. */
        epg_app_send_msg (EPG_MSG_CFG_LANGUAGE_UPDATED, NULL, 0);
    }
    else if (CFG_GET_GROUP (ui2_id) == APP_CFG_GRPID_VCHIP) /* V-chip updated. */
    {
        /* Send a Vchip-updated message to EPG. */
        epg_app_send_msg (EPG_MSG_CFG_VCHIP_UPDATED, NULL, 0);
    }
    else if (CFG_GET_GROUP (ui2_id) == APP_CFG_GRPID_BS) /* Broadcast service updated. */
    {
        /* Send a broadcast service updated message to EPG. */
        epg_app_send_msg (EPG_MSG_CFG_BRDCST_SVC_UPDATED, NULL, 0);
    }
}

/*-----------------------------------------------------------------------------
 * Name: _epg_nfy_dt
 *
 * Description: This callback function is called by date-time library.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _epg_nfy_dt (HANDLE_T     h_dt,
                         VOID*        pv_tag,
                         DT_COND_T    t_dt_cond,
                         TIME_T       t_delta)
{
    DT_NFY_DATA_T    t_dt_nfy_data;

    if (t_dt_cond == DT_SYNC_DISCONT) /* Date-time is discontinuous. */
    {
        DBG_INFO (("<EPG> DT notify: Date-time is discontinuous, delta = %lld\n\r", t_delta));

        t_dt_nfy_data.t_delta_time   = t_delta;
        t_dt_nfy_data.ui4_time_stamp = c_os_get_sys_tick ();

        /* Send a date-time discontinuous message to EPG. */
        epg_app_send_msg (EPG_MSG_DT_DISCONT, & t_dt_nfy_data, sizeof(DT_NFY_DATA_T));
    }
    else if (t_dt_cond == DT_DAY_LGT_SAV_CHANGED) /* Day-light-saving is changed. */
    {
        DBG_INFO (("<EPG> DT notify: Day-lignt saving changed\n\r"));

        /* Send a day-light-saving changed notify to EPG. */
        epg_app_send_msg (EPG_MSG_DT_DAY_LGT_SAV_CHANGED, NULL, 0);
    }
}

/*-----------------------------------------------------------------------------
 * Name: _epg_nfy_wgl
 *
 * Description: The callback funcation is called by Widget Library (directly
 *              using thread conext of IO Manager).
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_nfy_wgl (UINT32    ui4_msg,
                           VOID*     pv_param1,
                           VOID*     pv_param2)
{
    WIDGET_MSG_T          t_wgl_msg;

    t_wgl_msg.ui4_msg   = ui4_msg;
    t_wgl_msg.pv_param1 = pv_param1;
    t_wgl_msg.pv_param2 = pv_param2;

    /* The message will be dispatched to Widget Manager by using EPG's thread. */
    epg_app_send_msg (EPG_MSG_WGL_NFY, & t_wgl_msg, sizeof (WIDGET_MSG_T));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_nfy_rrt
 *
 * Description: The callback funcation is called by RRCTX when rating table is
 *              updated.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _epg_nfy_rrt (HANDLE_T    h_rrctx,
                          VOID*       pv_tag,
                          UINT32      ui4_reason)
{
    switch (ui4_reason)
    {
    case RRCTX_REASON_RATE_UPDATED:
    case RRCTX_REASON_RATE_AVAIL:
    case RRCTX_REASON_RATE_UNAVAIL:
        epg_app_send_msg (EPG_MSG_RRT_UPDATED, NULL, 0);
        break;
    default:
        break;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _epg_model_init_canvas
 *
 * Description: The function initiates the canvas.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_model_init_canvas (VOID)
{
    UINT16                ui2_plane_num; /* Number of planes. */
    UINT16                ui2_plane_idx; /* Target plane index. */
    GL_HSCREEN_T          h_screen;      /* Screen handle. */

    /* Open screen. */
    RET_ON_ERR (c_gl_screen_open (SN_PRES_MAIN_DISPLAY,
                                  NULL,
                                  NULL,
                                  & h_screen));

    /* Get the number of planes. */
    RET_ON_ERR (c_gl_plane_num (& ui2_plane_num));

    /* Get default OSD plane index. */
    ui2_plane_idx = a_util_get_default_osd_plane_index ();

    /* Open plane. */
    RET_ON_ERR (c_gl_plane_open (h_screen, ui2_plane_idx, & t_g_model.h_plane));

    /* Link plane. */
    RET_ON_ERR (c_gl_plane_link (t_g_model.h_plane, h_screen, TRUE));

    /* Open canvas. */
    RET_ON_ERR (c_wgl_get_canvas (t_g_model.h_plane, & t_g_model.h_canvas));

    /* Get canvas size. */
    RET_ON_ERR (c_wgl_get_canvas_size (t_g_model.h_canvas,
                                       & t_g_model.ui4_canvas_width,
                                       & t_g_model.ui4_canvas_height));

    t_g_model.i4_osd_offset_x = (INT32)((t_g_model.ui4_canvas_width - MAIN_FRM_W) / 2);
    t_g_model.i4_osd_offset_y = (INT32)((t_g_model.ui4_canvas_height - MAIN_FRM_H) / 2);

    /* Free handle. */
    c_handle_free (h_screen);

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_model_get_svl_rec_by_surf_mode
 *
 * Description: This function gets SVL record by channel id and surfing mode, e.g.
 *              next channel, previous channel, or this channel.
 *
 * Inputs:      h_svl               SVL handle.
 *              ui4_nw_mask         Network mask for filtering SVL record.
 *              e_surf_mode         Surfing mode.
 *              pui4_channel_id     Current channel id.
 *              pt_svl_rec          Current SVL record.
 *
 * Outputs:     pui4_channel_id     Resulted channel id.
 *              pt_svl_rec          Resulted SVL record.
 *
 * Returns: 0                       Successful.
 *          Any other values        Failed.
 *-----------------------------------------------------------------------------*/
static INT32 _epg_model_get_svl_rec_by_surf_mode (HANDLE_T       h_svl,           /* in */
                                                  UINT32         ui4_nw_mask,     /* in */
                                                  SURF_MODE_T    e_surf_mode,     /* in */
                                                  UINT32*        pui4_channel_id, /* in/out */
                                                  SVL_REC_T*     pt_svl_rec)      /* in/out */
{
    INT32        i4_rc;
    UINT32       ui4_channel_id;
    UINT32       ui4_svl_ver_id = SVL_NULL_VER_ID;

    /* Check if channel id and SVL record are valid. */
    if ((pui4_channel_id == NULL) || (pt_svl_rec == NULL))
    {
        return EPGR_FAIL;
    }

    /* Current channel id. */
    ui4_channel_id = *pui4_channel_id;

    /* Check if current record exists. */
    i4_rc = c_svl_get_rec_by_channel (h_svl,
                                      ui4_channel_id,
                                      ui4_nw_mask,
                                      0,
                                      pt_svl_rec,
                                      & ui4_svl_ver_id);

    if (i4_rc == SVLR_REC_NOT_FOUND) /* Current record is not found. */
    {
        /* Get first record of current TS. */
        i4_rc = c_svl_get_rec_by_ts (h_svl,
                                     pt_svl_rec->uheader.t_rec_hdr.ui2_tsl_id,
                                     pt_svl_rec->uheader.t_rec_hdr.ui2_tsl_rec_id,
                                     ui4_nw_mask,
                                     0,
                                     pt_svl_rec,
                                     & ui4_svl_ver_id);

        if (i4_rc == SVLR_REC_NOT_FOUND) /* There is no record in current transport stream. */
        {
            /* Get the first record of whole broadcast service. */
            i4_rc = c_svl_get_rec_by_brdcst_type (h_svl,
                                                  EPG_BRDCST_TYPE,
                                                  ui4_nw_mask,
                                                  0,
                                                  pt_svl_rec,
                                                  & ui4_svl_ver_id);
        }

        if (i4_rc == SVLR_OK)
        {
            /* Copy current channel id. */
            *pui4_channel_id = pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id;

            return  EPGR_OK;
        }
        else
        {
            DBG_ERROR (("<EPG> ERR: cann't find any available record = %d\n\r", i4_rc));

            return  EPGR_FAIL;
        }
    }

    switch (e_surf_mode)
    {
        case SURF_MODE_PREV: /* Get previous record. */
        {
            /* Iterate previous record. */
            i4_rc = c_svl_iterate_rec (h_svl,
                                       ui4_channel_id,
                                       ui4_nw_mask,
                                       SVL_CHANNEL_MINUS,
                                       pt_svl_rec,
                                       & ui4_svl_ver_id);

            if (i4_rc == SVLR_END_OF_ITERATION)
            {
                /* Current is the first one => Get the last one. */
                i4_rc = c_svl_iterate_rec (h_svl,
                                           ui4_channel_id,
                                           ui4_nw_mask,
                                           SVL_CHANNEL_LARGEST,
                                           pt_svl_rec,
                                           & ui4_svl_ver_id);
            }
            else if (i4_rc == SVLR_REC_NOT_FOUND)
            {
                /* Get first record. */
                i4_rc = c_svl_iterate_rec (h_svl,
                                           ui4_channel_id,
                                           ui4_nw_mask,
                                           SVL_CHANNEL_SMALLEST,
                                           pt_svl_rec,
                                           & ui4_svl_ver_id);
            }
        }
        break;

        case SURF_MODE_NEXT: /* Get next record. */
        {
            /* Iterate next record. */
            i4_rc = c_svl_iterate_rec (h_svl,
                                       ui4_channel_id,
                                       ui4_nw_mask,
                                       SVL_CHANNEL_PLUS,
                                       pt_svl_rec,
                                       & ui4_svl_ver_id);

            if (i4_rc == SVLR_END_OF_ITERATION)
            {
                /* Current is the last one => get the first one. */
                i4_rc = c_svl_iterate_rec (h_svl,
                                           ui4_channel_id,
                                           ui4_nw_mask,
                                           SVL_CHANNEL_SMALLEST,
                                           pt_svl_rec,
                                           & ui4_svl_ver_id);
            }
            else if (i4_rc == SVLR_REC_NOT_FOUND)
            {
                /* Get first record. */
                i4_rc = c_svl_iterate_rec (h_svl,
                                           ui4_channel_id,
                                           ui4_nw_mask,
                                           SVL_CHANNEL_SMALLEST,
                                           pt_svl_rec,
                                           & ui4_svl_ver_id);
            }
        }
        break;

        case SURF_MODE_THIS: /* Get current record. */
        {
            /* Get current record. */
            i4_rc = c_svl_get_rec_by_channel (h_svl,
                                              ui4_channel_id,
                                              ui4_nw_mask,
                                              0,
                                              pt_svl_rec,
                                              & ui4_svl_ver_id);

            if (i4_rc == SVLR_REC_NOT_FOUND)
            {
                /* Get first record. */
                i4_rc = c_svl_iterate_rec (h_svl,
                                           ui4_channel_id,
                                           ui4_nw_mask,
                                           SVL_CHANNEL_SMALLEST,
                                           pt_svl_rec,
                                           & ui4_svl_ver_id);
            }
        }
        break;

        default:
            break;
    }

    if ((i4_rc != SVLR_OK) && (i4_rc != SVLR_NEAREST_CHAN_MATCH))
    {
        return  EPGR_FAIL;
    }

    /* Copy current channel id. */
    *pui4_channel_id = pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id;

    return  EPGR_OK;
}

#ifdef APP_EPG_SKIP_INVISIBLE_CH
/*-----------------------------------------------------------------------------
 * Name: _epg_svl_rec_update_fct
 *
 * Description: This function updates SVL mask in order to make sure SB_VNET_EPG
 *              flag follows SB_VNET_VISIBLE flag.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_svl_rec_update_fct (HANDLE_T      h_svl,
                                      UINT16        ui2_idx,
                                      SVL_REC_T*    pt_svl_rec,
                                      UINT32        ui4_data1,
                                      UINT32        ui4_data2)
{
    INT32 i4_ret;

    if (((pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_VISIBLE) == 0) && /* Channel is invisible */
        ((pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_EPG)     != 0))   /* EPG is accessible */
    {
        /* When the channel is skipped, we have to guarantee that EPG also skips the channel */
        pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask &= ~SB_VNET_EPG;

        i4_ret = c_svl_update_rec (h_svl,
                                   pt_svl_rec,
                                   TRUE);
        if (i4_ret != SVLR_OK)
        {
            return TVR_FAIL;
        }
    }

    return TVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_update_svl_rec
 *
 * Description: This function updates network masks in order to have consistent
 *              state for SB_VNET_VISIBLE and SB_VNET_EPG flags.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_update_svl_rec (HANDLE_T    h_svl)
{
    a_tv_update_all_svl_recs (h_svl, _epg_svl_rec_update_fct, 0, 0);

    return EPGR_OK;
}

#endif /* APP_EPG_SKIP_INVISIBLE_CH */

/*-----------------------------------------------------------------------------
 * Name: _epg_model_update_svl
 *
 * Description: This function updates SVL.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_model_update_svl (VOID)
{
    INT32     i4_rc;
    UINT16    ui2_num_recs;
    UINT32    ui4_ver_id;

    i4_rc = SVLR_OK;

    /* Create a new handle if there is no svl handle. */
    if (t_g_model.h_svl == NULL_HANDLE)
    {
        /* Open a new svl handle. */
        i4_rc = c_svl_open (t_g_model.ui2_svl_id,
                            NULL,
                            _epg_nfy_svl,
                            & t_g_model.h_svl);

        if ((i4_rc != SVLR_OK) && (i4_rc != SVLR_NOT_FOUND))
        {
            DBG_ERROR (("<EPG> ERR: create svl failed = %d\n\r", i4_rc));
        }
    }

    /* Check if there is any record available. */
    if (i4_rc == SVLR_OK)
    {
        /* Get the number of records. */
        i4_rc = c_svl_get_num_rec_by_brdcst_type (t_g_model.h_svl,
                                                  EPG_BRDCST_TYPE,
                                                  EPG_NET_MASK,
                                                  & ui2_num_recs,
                                                  & ui4_ver_id);

        if (i4_rc != SVLR_OK)
        {
            DBG_ERROR (("<EPG> ERR: get record number failed = %d\n\r", i4_rc));
        }

        if ((i4_rc == SVLR_OK) && (ui2_num_recs == 0)) /* The number of records is 0. */
        {
            i4_rc = SVLR_NOT_FOUND;
        }
    }

    if (i4_rc == SVLR_OK)
    {
        t_g_model.b_svl_found = TRUE;  /* SVL is found. */
#ifdef APP_EPG_SKIP_INVISIBLE_CH
        _epg_update_svl_rec (t_g_model.h_svl);
#endif
    }
    else if (i4_rc == SVLR_NOT_FOUND)
    {
        t_g_model.b_svl_found = FALSE; /* SVL is unavailable. */
    }

    return ((i4_rc == SVLR_OK) || (i4_rc == SVLR_NOT_FOUND)) ? EPGR_OK : EPGR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_model_update_language
 *
 * Description: This function updates language configuration.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_model_update_language (VOID)
{
    INT32             i4_rc;

    /* Get current gui language. */
    i4_rc = a_cfg_get_gui_lang (t_g_model.s639_lang);

    if (i4_rc == CFGR_OK)
    {
#ifdef APP_MLM_S639_TO_LANGIDX_SUPPORT
        t_g_model.ui2_lang_id = mlm_epg_s639_to_langidx (t_g_model.s639_lang);
#else
        if (c_strcmp (t_g_model.s639_lang, s639_app_cfg_lang_eng) == 0) /* English */
        {
            DBG_INFO (("<EPG> set language to English\n\r"));

            /* Set language id to English. */
            t_g_model.ui2_lang_id = 0;
        }
        else if ((c_strcmp (t_g_model.s639_lang, s639_app_cfg_lang_esl) == 0) || /* Spanish */
                 (c_strcmp (t_g_model.s639_lang, s639_app_cfg_lang_spa) == 0))
        {
            DBG_INFO (("<EPG> set language to Spanish\n\r"));

            /* Set language id to Spanish. */
            t_g_model.ui2_lang_id = 1;
        }
        else if ((c_strcmp (t_g_model.s639_lang, s639_app_cfg_lang_fra) == 0) || /* French */
                 (c_strcmp (t_g_model.s639_lang, s639_app_cfg_lang_fre) == 0))
        {
            DBG_INFO (("<EPG> set language to French\n\r"));

            /* Set language id to French. */
            t_g_model.ui2_lang_id = 2;
        }
#endif /* APP_MLM_S639_TO_LANGIDX_SUPPORT */
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_model_update_brdcst_svc
 *
 * Description: This function updates broadcast service.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_model_update_brdcst_svc (VOID)
{
    INT32    i4_rc;

    /* Get tuner source. */
    i4_rc = a_cfg_get_tuner_sync_src (& t_g_model.ui2_svl_id,
                                      (CHAR**) (& t_g_model.ps_tuner_name));

    if (i4_rc != APP_CFGR_OK)
    {
        DBG_ERROR (("<EPG> ERR: get tuner source failed = %d\n\r", i4_rc));
    }

    /* Free SVL handle. */
    if (t_g_model.h_svl != NULL_HANDLE)
    {
        RET_ON_ERR (c_svl_close (t_g_model.h_svl));

        t_g_model.h_svl = NULL_HANDLE;
    }

    /* Update SVL. */
    RET_ON_ERR (_epg_model_update_svl ());

    return  i4_rc;
}

#ifndef APP_DVBT_SUPPORT
#ifdef EPG_CI_AUTO_SELECT

/*------------------------------------------------------------------------------
 * Name
 *      _epg_svc_is_video_content_playing
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static BOOL _epg_svc_is_video_content_playing(VOID)
{
    INT32              i4_rc;
    TV_WIN_ID_T        e_focus_wnd;
    VSH_SRC_RESOLUTION_INFO_T t_video_info;
    SCDB_REC_T t_scdb_rec = {0};

    c_memset(&t_video_info, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    /* Check if the source for the focused window is TV. */
    i4_rc = a_tv_get_focus_win (& e_focus_wnd);

    if (i4_rc != TVR_OK)
    {
        return FALSE;
    }

    i4_rc = c_svctx_get_using_scdb_rec(
                    t_g_model.h_svctx,
                    ST_VIDEO,
                    &t_scdb_rec
                    );
    if (i4_rc != SVCTXR_OK)
    {
        return FALSE;
    }

    i4_rc = c_svctx_get_video_src_resolution(
                    t_g_model.h_svctx,
                    &t_video_info
                    );
    if (i4_rc == SVCTXR_OK
            && t_video_info.ui4_height > 0
            && t_video_info.ui4_width > 0
            && t_video_info.e_timing_type != VSH_SRC_TIMING_NOT_SUPPORT) {
        /* with video */
        return TRUE;
    }

    return FALSE;
}

/*------------------------------------------------------------------------------
 * Name
 *      _epg_svc_is_with_cc_dscrptr
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static BOOL _epg_svc_is_with_cc_dscrptr(EPG_CC_QUERY_DATA_T* pt_cc_query_data)
{
    SM_CC_AUTO_SEL_T                t_exist_cc;
    SIZE_T                          z_size;
    INT32                           i4_ret;

    /* Invalid parameter */
    if (NULL == pt_cc_query_data)
    {
        return FALSE;
    }

    /* reset delay query flag */
    pt_cc_query_data->b_delay_query = FALSE;

    z_size = sizeof(SM_CC_AUTO_SEL_T);

    i4_ret = c_svctx_get_stream_attr(t_g_model.h_svctx,
                                     ST_CLOSED_CAPTION,
                                     SM_CCH_GET_TYPE_EXISTED_CC_IND,
                                     &t_exist_cc,
                                     &z_size);

    if(SVCTXR_OK != i4_ret)
    {
        if(SVCTXR_WRONG_STATE == i4_ret &&
           _epg_svc_is_video_content_playing())
        {
            /* set flag for delay query CC from SVCTX */
            pt_cc_query_data->b_delay_query = TRUE;
        }
        return FALSE;
    }

    return (t_exist_cc.ui1_ntsccc_mask || t_exist_cc.ui8_dtvcc_mask) ? TRUE : FALSE;
}

#else
/*------------------------------------------------------------------------------
 * Name
 *      _epg_svc_is_with_cc_dscrptr
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static BOOL _epg_svc_is_with_cc_dscrptr(EPG_CC_QUERY_DATA_T* pt_cc_query_data)
{
    SVCTX_CC_AVIL_COND_T            e_avail;
    SIZE_T                          z_size;
    INT32                           i4_ret;

    z_size = sizeof(SVCTX_CC_AVIL_COND_T);
    i4_ret = c_svctx_get(t_g_model.h_svctx,
        SVCTX_COMMON_GET_CC_AVIL_COND,
        &e_avail,
        &z_size);

    if(SVCTXR_OK != i4_ret)
    {
        DBG_ERROR (("<EPG> ERR: c_svctx_get(SVCTX_COMMON_GET_CC_AVIL_COND) failed. i4_ret = %d \n\r", i4_ret));
        return FALSE;
    }

    return ((SVCTX_CC_AVIL_COND_YES == e_avail) ? TRUE : FALSE);
}

#endif
#endif

/*------------------------------------------------------------------------------
 * Name
 *      _epg_svc_is_timeshift_pvr_activing
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static BOOL _epg_svc_is_timeshift_pvr_activing(VOID)
{
    BOOL        b_active = FALSE;

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
    {
        INT32       i4_rc = ICLR_OK;
        UINT32      ui4_tshift_status = 0;
        SIZE_T      z_size = (SIZE_T)ICL_RECID_REC_TSHIFT_STATUS_SIZE;

        /* Check if it is timeshifting. */
        i4_rc = a_icl_get(ICL_MAKE_ID(ICL_GRPID_REC, ICL_RECID_REC_TSHIFT_STATUS),
                              &ui4_tshift_status,
                              &z_size);
        if(i4_rc == ICLR_OK &&
           (ui4_tshift_status & ICL_RECID_REC_TSHIFT_STATUS_PLAYING) > 0)
        {
            b_active = TRUE;
        }
    }
#endif

#ifdef APP_NAV_REC_PVR_SUPPORT
    {
        INT32       i4_rc = ICLR_OK;
    	UINT32		ui4_pvr_status = 0;
    	SIZE_T		z_pvr_size = (SIZE_T)ICL_RECID_REC_PVR_STATUS_SIZE;

        /* Check if it is PVR. */
        i4_rc = a_icl_get(ICL_MAKE_ID(ICL_GRPID_REC, ICL_RECID_REC_PVR_STATUS),
                              &ui4_pvr_status,
                              &z_pvr_size);
        if(i4_rc == ICLR_OK &&
           (ui4_pvr_status & ICL_RECID_REC_PVR_STATUS_RECORDING) > 0)
        {
            b_active = TRUE;
        }
    }
#endif

    return b_active;
}

/*-----------------------------------------------------------------------------
 * Name: epg_app_send_msg
 *
 * Description: This API sends a message to the message queue of EPG
 *              applications.
 *
 * Inputs:  ui4_type            Contains the type of the data.
 *          pv_msg              References the message data.
 *          z_msg_len           Contains the length (in bytes) of pv_msg.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_app_send_msg (UINT32         ui4_type,
                        const VOID*    pv_msg,
                        SIZE_T         z_msg_len)
{
    INT32   i4_rc;

    /* Send a message to EPG's message queue. */
    i4_rc = c_app_send_msg (t_g_model.h_epg,
                            ui4_type,
                            pv_msg,
                            z_msg_len,
                            _epg_app_nfy_fct,
                            NULL);

    if (i4_rc != AEER_OK)
    {
        DBG_ERROR (("<EPG> ERR: send message = %d failed = %d\n\r", ui4_type, i4_rc));
    }

    return (i4_rc == AEER_OK) ? EPGR_OK : EPGR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: epg_app_dispatch_msg
 *
 * Description: This API dispatches a message to the message queue of EPG
 *              via Application Manager.
 *
 * Inputs:  ui4_type            Contains the type of the data.
 *          pv_msg              References the message data.
 *          z_msg_len           Contains the length (in bytes) of pv_msg.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_app_dispatch_msg (UINT32         ui4_type,
                            const VOID*    pv_msg,
                            SIZE_T         z_msg_len)
{
    INT32   i4_rc;

    /* Send a message to EPG's message queue via Application Manager. */
    i4_rc = a_amb_dispatch_msg (EPG_NAME,
                                ui4_type,
                                (VOID*) pv_msg,
                                z_msg_len);

    if (i4_rc != AMBR_OK)
    {
        DBG_ERROR (("<EPG> ERR: dispatch message = %d failed = %d\n\r", ui4_type, i4_rc));
    }

    return (i4_rc == AMBR_OK) ? EPGR_OK : EPGR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: epg_app_pause_req
 *
 * Description: This API requests to pauses EPG application.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_app_pause_req (VOID)
{
    /* Pause EPG. */
    return  a_amb_pause_app (EPG_NAME);
}

/*-----------------------------------------------------------------------------
 * Name: epg_app_resume_req
 *
 * Description: This API requests to resume EPG application.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_app_resume_req (VOID)
{
    /* Resume EPG. */
    return  a_amb_resume_app (EPG_NAME);
}

/*-----------------------------------------------------------------------------
 * Name: epg_app_is_pause
 *
 * Description: This API asks if EPG is in paused mode.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE                In paused mode.
 *          FALSE               Not in paused mode.
 ----------------------------------------------------------------------------*/
BOOL epg_app_is_pause (VOID)
{
    return  (t_g_model.b_pause) ? TRUE : FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_load
 *
 * Description: This API loads an event given the starting time and offset.
 *
 * Inputs:  pt_offset           Event offset.
 *          ui1_type            Event type. Upper 4-bits indicates type,
 *                              lower 4-bits indicates subtype.
 *
 * Outputs: ph_event            Event handle.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_load (EVCTX_OFFSET_T*   pt_offset,
                    UINT8             ui1_type,
                    HANDLE_T*         ph_event)
{
    EVCTX_COMMAND_T     at_cmd[7];
    EVCTX_COND_T        e_cond;
    UINT16              ui2_cmd_idx;

    ui2_cmd_idx = 0;

    at_cmd[ui2_cmd_idx].e_code       = EVCTX_CMD_DEV_TYPE;
    at_cmd[ui2_cmd_idx].u.e_dev_type = DEV_TUNER;
    ui2_cmd_idx ++;

    at_cmd[ui2_cmd_idx].e_code       = EVCTX_CMD_SRC_INFO;
    at_cmd[ui2_cmd_idx].u.ps_name    = SN_MAIN_TUNER_GRP;
    ui2_cmd_idx ++;

    at_cmd[ui2_cmd_idx].e_code       = EVCTX_CMD_SVL_ID;
    at_cmd[ui2_cmd_idx].u.ui2_number = t_g_model.ui2_svl_id;
    ui2_cmd_idx ++;

    at_cmd[ui2_cmd_idx].e_code       = EVCTX_CMD_SVL_REC_ID;
    at_cmd[ui2_cmd_idx].u.ui2_number = t_g_model.t_svl_rec.ui2_svl_rec_id;
    ui2_cmd_idx ++;

    if (ui1_type != 0) /* Specify event type. */
    {
        /* Event type */
        at_cmd[ui2_cmd_idx].e_code = EVCTX_CMD_EVENT_CATEGORY;

        switch ((ui1_type & 0xf0) >> 4)
        {
            case 0:  at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_UNKNOWN;     break;
            case 1:  at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_MOVIE_DRAMA; break;
            case 2:  at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_NEWS;        break;
            case 3:  at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_SHOW;        break;
            case 4:  at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_SPORTS;      break;
            case 5:  at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_CHILDREN;    break;
            case 6:  at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_MUSIC;       break;
            case 7:  at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_ARTS;        break;
            case 8:  at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_SOC_POL_EC;  break;
            case 9:  at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_ED_SC_FACT;  break;
            case 10: at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_LEISURE;     break;
            case 11: at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_SPECIAL;     break;
            default: at_cmd[ui2_cmd_idx].u.e_evt_type = EVCTX_CATEGORY_UNKNOWN;     break;
        }

        ui2_cmd_idx ++;

        /* Event subtype. */
        if ((ui1_type & 0x0f) != 0)
        {
            at_cmd[ui2_cmd_idx].e_code       = EVCTX_CMD_EVENT_SUB_TYPE;
            at_cmd[ui2_cmd_idx].u.ui2_number = (UINT16)((ui1_type & 0x0f) - 1);
            ui2_cmd_idx ++;
        }
    }

    at_cmd[ui2_cmd_idx].e_code = EVCTX_CMD_END;

    /* Load event. */
    return  c_evctx_load_schedule_event (at_cmd,
                                         pt_offset,
                                         NULL,
                                         _epg_nfy_evctx,
                                         ph_event,
                                         & e_cond);
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_free
 *
 * Description: This API deletes an event given the event handle.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_free (HANDLE_T    h_event)
{
    return  c_evctx_delete_event (h_event);
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_cond
 *
 * Description: This API gets the condition of an event.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pe_cond             Event condition.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_cond (HANDLE_T         h_event,
                        EVCTX_COND_T*    pe_cond)
{
    return  c_evctx_get_cond (h_event, pe_cond);
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_start_time
 *
 * Description: This API gets the event starting time given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pt_time_start       Starting time of the event.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_start_time (HANDLE_T    h_event,
                              TIME_T*     pt_time_start)
{
    EVCTX_COND_T    e_cond;
    SIZE_T          z_info_size = sizeof (TIME_T);

    return  c_evctx_get_event_info (h_event,
                                    EVCTX_KEY_TYPE_START_TIME,
                                    NULL,
                                    & z_info_size,
                                    pt_time_start,
                                    & e_cond);
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_end_time
 *
 * Description: This API gets the event ending time given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pt_time_start       Ending time of the event.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_end_time (HANDLE_T    h_event,
                            TIME_T*     pt_time_end)
{
    INT32           i4_rc;
    TIME_T          t_time_start;
    TIME_T          t_time_duration;
    EVCTX_COND_T    e_cond;
    SIZE_T          z_info_size = sizeof (TIME_T);

    /* Get event starting time. */
    i4_rc = c_evctx_get_event_info (h_event,
                                    EVCTX_KEY_TYPE_START_TIME,
                                    NULL,
                                    & z_info_size,
                                    & t_time_start,
                                    & e_cond);

    if (i4_rc == EVCTXR_OK)
    {
        /* Get event duration. */
        i4_rc = c_evctx_get_event_info (h_event,
                                        EVCTX_KEY_TYPE_DURATION,
                                        NULL,
                                        & z_info_size,
                                        & t_time_duration,
                                        & e_cond);

        if (i4_rc == EVCTXR_OK)
        {
            /* Ending time = Starting time + Duration */
            *pt_time_end = t_time_start + t_time_duration;
        }
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_duration
 *
 * Description: This API gets the event duration given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pt_time_duration    Duration of the event.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_duration (HANDLE_T    h_event,
                            TIME_T*     pt_time_duration)
{
    EVCTX_COND_T    e_cond;
    SIZE_T          z_info_size = sizeof (TIME_T);

    return  c_evctx_get_event_info (h_event,
                                    EVCTX_KEY_TYPE_DURATION,
                                    NULL,
                                    & z_info_size,
                                    pt_time_duration,
                                    & e_cond);
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_title_len
 *
 * Description: This API gets the event title length given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pz_title_len        Event title length
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_title_len (HANDLE_T h_event, SIZE_T* pz_title_len)
{
    INT32           i4_rc;
    EVCTX_COND_T    e_cond;

    i4_rc = c_evctx_get_event_info_len (h_event,
                                        EVCTX_KEY_TYPE_EVENT_TITLE,
                                        (VOID*) t_g_model.s639_lang,
                                        pz_title_len,
                                        & e_cond);

    /* Title for specified language is not found - Try "eng". */
    if (i4_rc == EVCTXR_INFO_NOT_FOUND)
    {
        i4_rc = c_evctx_get_event_info_len (h_event,
                                            EVCTX_KEY_TYPE_EVENT_TITLE,
                                            "eng",
                                            pz_title_len,
                                            & e_cond);

        if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Title for "eng" is not found. */
        {
            /* Get any language which is available. */
            i4_rc = c_evctx_get_event_info_len (h_event,
                                                EVCTX_KEY_TYPE_EVENT_TITLE,
                                                NULL,
                                                pz_title_len,
                                                & e_cond);

            if (i4_rc != EVCTXR_OK)
            {
                DBG_ERROR (("<EPG> ERR: get event title length failed = %d\n\r", i4_rc));
            }
        }
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_title
 *
 * Description: This API gets the event title given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *          z_title_len         Event title length.
 *
 * Outputs: ps_title            Event title.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_title (HANDLE_T    h_event,
                         SIZE_T      z_title_len,
                         CHAR*       ps_title)
{
    INT32           i4_rc;
    EVCTX_COND_T    e_cond;
    SIZE_T          z_info_size = z_title_len;

    i4_rc = c_evctx_get_event_info (h_event,
                                    EVCTX_KEY_TYPE_EVENT_TITLE,
                                    (VOID*) t_g_model.s639_lang,
                                    & z_info_size,
                                    ps_title,
                                    & e_cond);

    /* Title for specified language is not found - Try "eng". */
    if (i4_rc == EVCTXR_INFO_NOT_FOUND)
    {
        i4_rc = c_evctx_get_event_info (h_event,
                                        EVCTX_KEY_TYPE_EVENT_TITLE,
                                        "eng",
                                        & z_info_size,
                                        ps_title,
                                        & e_cond);

        if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Title for "eng" is not found. */
        {
            /* Get any language which is available. */
            i4_rc = c_evctx_get_event_info (h_event,
                                            EVCTX_KEY_TYPE_EVENT_TITLE,
                                            NULL,
                                            & z_info_size,
                                            ps_title,
                                            & e_cond);

            if (i4_rc != EVCTXR_OK)
            {
                DBG_ERROR (("<EPG> ERR: get event title failed = %d\n\r", i4_rc));
            }
        }
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_text_len
 *
 * Description: This API gets the event title length given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pz_title_len        Event text length
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_text_len (HANDLE_T    h_event,
                            SIZE_T*     pz_text_len)
{
    INT32           i4_rc;
    EVCTX_COND_T    e_cond;
    BOOL            b_found      = FALSE;
    SIZE_T          z_short_len  = 0;
#ifdef APP_DVBT_SUPPORT
    SIZE_T          z_long_len   = 0;
    SIZE_T          z_append_len = 0;
    UINT8           ui1_evt_form;
#endif /* APP_DVBT_SUPPORT */

    i4_rc = c_evctx_get_event_info_len (h_event,
                                        EVCTX_KEY_TYPE_EVENT_TEXT,
                                        (VOID*) t_g_model.s639_lang,
                                        & z_short_len,
                                        & e_cond);

    /* Text for specified language is not found - Try "eng". */
    if (i4_rc == EVCTXR_INFO_NOT_FOUND)
    {
        i4_rc = c_evctx_get_event_info_len (h_event,
                                            EVCTX_KEY_TYPE_EVENT_TEXT,
                                            "eng",
                                            & z_short_len,
                                            & e_cond);

        if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Text for "eng" is not found. */
        {
            /* Get any language which is available. */
            i4_rc = c_evctx_get_event_info_len (h_event,
                                                EVCTX_KEY_TYPE_EVENT_TEXT,
                                                NULL,
                                                & z_short_len,
                                                & e_cond);

            if (i4_rc != EVCTXR_OK)
            {
                DBG_INFO (("<EPG> no short-form text\n\r"));
            }
        }
    }

    if (i4_rc == EVCTXR_OK)
    {
        b_found = TRUE;
    }

    *pz_text_len = z_short_len;

#ifdef APP_DVBT_SUPPORT

    i4_rc = c_evctx_get_event_info_len (h_event,
                                        EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                        (VOID*) t_g_model.s639_lang,
                                        & z_long_len,
                                        & e_cond);

    /* Text for specified language is not found - Try "eng". */
    if (i4_rc == EVCTXR_INFO_NOT_FOUND)
    {
        i4_rc = c_evctx_get_event_info_len (h_event,
                                            EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                            "eng",
                                            & z_long_len,
                                            & e_cond);

        if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Text for "eng" is not found. */
        {
            /* Get any language which is available. */
            i4_rc = c_evctx_get_event_info_len (h_event,
                                                EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                                NULL,
                                                & z_long_len,
                                                & e_cond);

            if (i4_rc != EVCTXR_OK)
            {
                DBG_INFO (("<EPG> no long-form text\n\r"));
            }
        }
    }

    if (i4_rc == EVCTXR_OK)
    {
        b_found = TRUE;
    }

    z_append_len = c_strlen (SHORT_FORM_EVENT_DETAILS_HEADER) +
                   c_strlen (SHORT_FORM_EVENT_DETAILS_FOOTER) +
                   c_strlen (SHORT_LONG_FORM_SEPERATOR)       +
                   c_strlen (LONG_FORM_EVENT_DETAILS_HEADER)  +
                   c_strlen (LONG_FORM_EVENT_DETAILS_FOOTER);

    i4_rc = a_cfg_get_evt_form (& ui1_evt_form);

    if (i4_rc == APP_CFGR_OK)
    {
        if (ui1_evt_form == APP_CFG_EVT_FORM_BOTH)
        {
            *pz_text_len = z_short_len + z_long_len + z_append_len;
        }
        else if (ui1_evt_form == APP_CFG_EVT_FORM_SHORT_FIRST)
        {
            *pz_text_len = (z_short_len == 0) ? z_long_len : z_short_len;
        }
        else if (ui1_evt_form == APP_CFG_EVT_FORM_LONG_FIRST)
        {
            *pz_text_len = (z_long_len == 0) ? z_short_len : z_long_len;
        }
    }

#endif /* APP_DVBT_SUPPORT */

    return (b_found) ? EVCTXR_OK : EVCTXR_INFO_NOT_FOUND;
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_text
 *
 * Description: This API gets the event text given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *          z_title_len         Event text length.
 *
 * Outputs: ps_title            Event text.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_text (HANDLE_T    h_event,
                        SIZE_T      z_text_len,
                        CHAR*       ps_text)
{
    INT32           i4_rc;
    EVCTX_COND_T    e_cond;
    BOOL            b_found     = FALSE;
    SIZE_T          z_info_size = z_text_len;

#ifndef APP_DVBT_SUPPORT

    /* Look up for short-form info. */
    i4_rc = c_evctx_get_event_info (h_event,
                                    EVCTX_KEY_TYPE_EVENT_TEXT,
                                    (VOID*) t_g_model.s639_lang,
                                    & z_info_size,
                                    ps_text,
                                    & e_cond);

    /* Text for specified language is not found - Try "eng". */
    if (i4_rc == EVCTXR_INFO_NOT_FOUND)
    {
        i4_rc = c_evctx_get_event_info (h_event,
                                        EVCTX_KEY_TYPE_EVENT_TEXT,
                                        "eng",
                                        & z_info_size,
                                        ps_text,
                                        & e_cond);

        if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Text for "eng" is not found. */
        {
            /* Get any language which is available. */
            i4_rc = c_evctx_get_event_info (h_event,
                                            EVCTX_KEY_TYPE_EVENT_TEXT,
                                            NULL,
                                            & z_info_size,
                                            ps_text,
                                            & e_cond);
        }
    }

    if (i4_rc == EVCTXR_OK)
    {
        b_found = TRUE;
    }

    /* If the text is too long, it will cause abort. Hence don't show. */
    /* DBG_INFO (("<EPG> short-form text: \"%s\"\n\r", ps_text)); */

#else /* #ifdef APP_DVBT_SUPPORT */

    UINT8    ui1_evt_form;
    BOOL     b_short_found = FALSE;
    BOOL     b_long_found = FALSE;

    i4_rc = a_cfg_get_evt_form (& ui1_evt_form);

    if (i4_rc != APP_CFGR_OK)
    {
        return i4_rc;
    }

    if (ui1_evt_form == APP_CFG_EVT_FORM_BOTH) /* Show both short-form and long-form. */
    {
        /* Append short-form header. */
        c_strcat (ps_text, SHORT_FORM_EVENT_DETAILS_HEADER);
        ps_text += c_strlen (SHORT_FORM_EVENT_DETAILS_HEADER);

        /* Look up for short-form info. */
        i4_rc = c_evctx_get_event_info (h_event,
                                        EVCTX_KEY_TYPE_EVENT_TEXT,
                                        (VOID*) t_g_model.s639_lang,
                                        & z_info_size,
                                        ps_text,
                                        & e_cond);

        /* Text for specified language is not found - Try "eng". */
        if (i4_rc == EVCTXR_INFO_NOT_FOUND)
        {
            i4_rc = c_evctx_get_event_info (h_event,
                                            EVCTX_KEY_TYPE_EVENT_TEXT,
                                            "eng",
                                            & z_info_size,
                                            ps_text,
                                            & e_cond);

            if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Text for "eng" is not found. */
            {
                /* Get any language which is available. */
                i4_rc = c_evctx_get_event_info (h_event,
                                                EVCTX_KEY_TYPE_EVENT_TEXT,
                                                NULL,
                                                & z_info_size,
                                                ps_text,
                                                & e_cond);
            }
        }

        if (i4_rc == EVCTXR_OK)
        {
            b_short_found = TRUE;
        }

        /* If the text is too long, it will cause abort. Hence don't show. */
        /* DBG_INFO (("<EPG> short-form text: \"%s\"\n\r", ps_text)); */

        /* Move pointer if event text found */
        if (b_short_found)
        {
            ps_text += (z_info_size - 1);  /* z_info_size includes '\0' */
        }

        /* If not found, clear z_info_size */
        else
        {
            z_info_size = 0;
        }

        /* Append short-form footer. */
        c_strcat (ps_text, SHORT_FORM_EVENT_DETAILS_FOOTER);
        ps_text += c_strlen (SHORT_FORM_EVENT_DETAILS_FOOTER);

        if (b_short_found && z_info_size > 0)
        {
            /* Append separater. */
            c_strcat (ps_text, SHORT_LONG_FORM_SEPERATOR);
            ps_text += c_strlen (SHORT_LONG_FORM_SEPERATOR);
        }

        /* Append long-form header. */
        c_strcat (ps_text, LONG_FORM_EVENT_DETAILS_HEADER);
        ps_text += c_strlen (LONG_FORM_EVENT_DETAILS_HEADER);

        /* Look up for long-form info. z_info_size is the remaining buffer size  */
        z_info_size = z_text_len                                               /* Total buffer size */
                      - z_info_size                                            /* Short form text length */
                      - c_strlen (SHORT_FORM_EVENT_DETAILS_HEADER)             /* Short form header */
                      - c_strlen (SHORT_FORM_EVENT_DETAILS_FOOTER)             /* Short form footer */
                      - ((b_found) ? c_strlen (SHORT_LONG_FORM_SEPERATOR) : 0) /* Short/Long Seperator */
                      - c_strlen (LONG_FORM_EVENT_DETAILS_HEADER)              /* Long form header */
                      - c_strlen (LONG_FORM_EVENT_DETAILS_FOOTER);             /* Long form footer */

        i4_rc = c_evctx_get_event_info (h_event,
                                        EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                        (VOID*) t_g_model.s639_lang,
                                        & z_info_size,
                                        ps_text,
                                        & e_cond);

        /* Text for specified language is not found - Try "eng". */
        if (i4_rc == EVCTXR_INFO_NOT_FOUND)
        {
            i4_rc = c_evctx_get_event_info (h_event,
                                            EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                            "eng",
                                            & z_info_size,
                                            ps_text,
                                            & e_cond);

            if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Text for "eng" is not found. */
            {
                /* Get any language which is available. */
                i4_rc = c_evctx_get_event_info (h_event,
                                                EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                                NULL,
                                                & z_info_size,
                                                ps_text,
                                                & e_cond);
            }
        }

        if (i4_rc == EVCTXR_OK)
        {
            b_long_found = TRUE;
        }

        /* If the text is too long, it will cause abort. Hence don't show. */
        /* DBG_INFO (("<EPG> long-form text: \"%s\"\n\r", ps_text)); */

        /* Move pointer. */
        if(b_long_found)
        {
            ps_text += (z_info_size - 1); /* z_info_size includes '\0' */
        }

        /* Append long-form footer. */
        c_strcat (ps_text, LONG_FORM_EVENT_DETAILS_FOOTER);

        /* Combine the b_found flag. */
        b_found = b_short_found | b_long_found;

    }
    else if (ui1_evt_form == APP_CFG_EVT_FORM_SHORT_FIRST) /* Show short-form first. */
    {
        /* Look up for short-form info. */
        i4_rc = c_evctx_get_event_info (h_event,
                                        EVCTX_KEY_TYPE_EVENT_TEXT,
                                        (VOID*) t_g_model.s639_lang,
                                        & z_info_size,
                                        ps_text,
                                        & e_cond);

        /* Text for specified language is not found - Try "eng". */
        if (i4_rc == EVCTXR_INFO_NOT_FOUND)
        {
            i4_rc = c_evctx_get_event_info (h_event,
                                            EVCTX_KEY_TYPE_EVENT_TEXT,
                                            "eng",
                                            & z_info_size,
                                            ps_text,
                                            & e_cond);

            if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Text for "eng" is not found. */
            {
                /* Get any language which is available. */
                i4_rc = c_evctx_get_event_info (h_event,
                                                EVCTX_KEY_TYPE_EVENT_TEXT,
                                                NULL,
                                                & z_info_size,
                                                ps_text,
                                                & e_cond);
            }
        }

        if (i4_rc == EVCTXR_OK)
        {
            b_found = TRUE;
        }

        /* If the text is too long, it will cause abort. Hence don't show. */
        /* DBG_INFO (("<EPG> short-form text: \"%s\"\n\r", ps_text)); */

        if (i4_rc == EVCTXR_INFO_NOT_FOUND)
        {
            /* Look up for long-form info. */
            i4_rc = c_evctx_get_event_info (h_event,
                                            EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                            (VOID*) t_g_model.s639_lang,
                                            & z_info_size,
                                            ps_text,
                                            & e_cond);

            /* Text for specified language is not found - Try "eng". */
            if (i4_rc == EVCTXR_INFO_NOT_FOUND)
            {
                i4_rc = c_evctx_get_event_info (h_event,
                                                EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                                "eng",
                                                & z_info_size,
                                                ps_text,
                                                & e_cond);

                if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Text for "eng" is not found. */
                {
                    /* Get any language which is available. */
                    i4_rc = c_evctx_get_event_info (h_event,
                                                    EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                                    NULL,
                                                    & z_info_size,
                                                    ps_text,
                                                    & e_cond);
                }
            }

            if (i4_rc == EVCTXR_OK)
            {
                b_found = TRUE;
            }

            /* If the text is too long, it will cause abort. Hence don't show. */
            /* DBG_INFO (("<EPG> long-form text: \"%s\"\n\r", ps_text)); */
        }
    }
    else if (ui1_evt_form == APP_CFG_EVT_FORM_LONG_FIRST) /* Show long-form first. */
    {
        /* Look up for long-form info. */
        i4_rc = c_evctx_get_event_info (h_event,
                                        EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                        (VOID*) t_g_model.s639_lang,
                                        & z_info_size,
                                        ps_text,
                                        & e_cond);

        /* Text for specified language is not found - Try "eng". */
        if (i4_rc == EVCTXR_INFO_NOT_FOUND)
        {
            i4_rc = c_evctx_get_event_info (h_event,
                                            EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                            "eng",
                                            & z_info_size,
                                            ps_text,
                                            & e_cond);

            if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Text for "eng" is not found. */
            {
                /* Get any language which is available. */
                i4_rc = c_evctx_get_event_info (h_event,
                                                EVCTX_KEY_TYPE_EVENT_EXT_TEXT,
                                                NULL,
                                                & z_info_size,
                                                ps_text,
                                                & e_cond);
            }
        }

        if (i4_rc == EVCTXR_OK)
        {
            b_found = TRUE;
        }

        /* If the text is too long, it will cause abort. Hence don't show. */
        /* DBG_INFO (("<EPG> long-form text: \"%s\"\n\r", ps_text)); */

        if (i4_rc == EVCTXR_INFO_NOT_FOUND)
        {
            /* Look up for short-form info. */
            i4_rc = c_evctx_get_event_info (h_event,
                                            EVCTX_KEY_TYPE_EVENT_TEXT,
                                            (VOID*) t_g_model.s639_lang,
                                            & z_info_size,
                                            ps_text,
                                            & e_cond);

            /* Text for specified language is not found - Try "eng". */
            if (i4_rc == EVCTXR_INFO_NOT_FOUND)
            {
                i4_rc = c_evctx_get_event_info (h_event,
                                                EVCTX_KEY_TYPE_EVENT_TEXT,
                                                "eng",
                                                & z_info_size,
                                                ps_text,
                                                & e_cond);

                if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Text for "eng" is not found. */
                {
                    /* Get any language which is available. */
                    i4_rc = c_evctx_get_event_info (h_event,
                                                    EVCTX_KEY_TYPE_EVENT_TEXT,
                                                    NULL,
                                                    & z_info_size,
                                                    ps_text,
                                                    & e_cond);
                }
            }

            if (i4_rc == EVCTXR_OK)
            {
                b_found = TRUE;
            }

            /* If the text is too long, it will cause abort. Hence don't show. */
            /* DBG_INFO (("<EPG> short-form text: \"%s\"\n\r", ps_text)); */
        }
    }

#endif /* APP_DVBT_SUPPORT */

    return  (b_found) ? EVCTXR_OK : EVCTXR_INFO_NOT_FOUND;
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_rating_len
 *
 * Description: This API gets the rating length given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pz_rating_len       Rating length.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_rating_len (HANDLE_T    h_event,
                              SIZE_T*     pz_rating_len)
{
    INT32           i4_rc;
    EVCTX_COND_T    e_cond;

    i4_rc = c_evctx_get_event_info_len (h_event,
                                        EVCTX_KEY_TYPE_RATING,
                                        (VOID*) t_g_model.s639_lang,
                                        pz_rating_len,
                                        & e_cond);

    /* Rating length for specified language is not found - Try "eng". */
    if (i4_rc == EVCTXR_INFO_NOT_FOUND)
    {
        i4_rc = c_evctx_get_event_info_len (h_event,
                                            EVCTX_KEY_TYPE_RATING,
                                            "eng",
                                            pz_rating_len,
                                            & e_cond);

        if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Rating for "eng" is not found. */
        {
            /* Get any language which is available. */
            i4_rc = c_evctx_get_event_info_len (h_event,
                                                EVCTX_KEY_TYPE_RATING,
                                                NULL,
                                                pz_rating_len,
                                                & e_cond);
        }
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_rating
 *
 * Description: This API gets the event rating given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *          z_rating_len        Rating length.
 *
 * Outputs: ps_atsc_rating      Rating info.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_rating (HANDLE_T                    h_event,
                          SIZE_T                      z_rating_len,
                          EVCTX_ATSC_RATING_LIST_T*   pt_atsc_rating)
{
    INT32           i4_rc;
    EVCTX_COND_T    e_cond;
    SIZE_T          z_info_size = z_rating_len;

    i4_rc = c_evctx_get_event_info (h_event,
                                    EVCTX_KEY_TYPE_RATING,
                                    (VOID*) t_g_model.s639_lang,
                                    & z_info_size,
                                    pt_atsc_rating,
                                    & e_cond);

    /* Rating for specified language is not found - Try "eng". */
    if (i4_rc == EVCTXR_INFO_NOT_FOUND)
    {
        i4_rc = c_evctx_get_event_info (h_event,
                                        EVCTX_KEY_TYPE_RATING,
                                        "eng",
                                        & z_info_size,
                                        pt_atsc_rating,
                                        & e_cond);

        if (i4_rc == EVCTXR_INFO_NOT_FOUND) /* Rating for "eng" is not found. */
        {
            /* Get any language which is available. */
            i4_rc = c_evctx_get_event_info (h_event,
                                            EVCTX_KEY_TYPE_RATING,
                                            NULL,
                                            & z_info_size,
                                            pt_atsc_rating,
                                            & e_cond);

            if (i4_rc != EVCTXR_OK)
            {
                DBG_ERROR (("<EPG> ERR: get rating info failed = %d\n\r", i4_rc));
            }
        }
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_caption
 *
 * Description: This API gets the caption information given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *          z_rating_len        Rating length.
 *
 * Outputs: pb_caption          TRUE  - Caption exists.
 *                              FALSE - Caption doesn't exist.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_caption (HANDLE_T    h_event,
                           BOOL*       pb_caption)
{

    EVCTX_COND_T    e_cond;
    SIZE_T          z_info_size = sizeof (BOOL);

    return  c_evctx_get_event_info (h_event,
                                    EVCTX_KEY_TYPE_CAPTION,
                                    NULL,
                                    & z_info_size,
                                    pb_caption,
                                    & e_cond);
}

/*-----------------------------------------------------------------------------
 * Name: epg_evt_get_hours
 *
 * Description: This API gets the available hours given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pui2_avail_hours    Available hours.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_evt_get_hours (HANDLE_T    h_event,
                         UINT16*     pui2_avail_hours)
{
    EVCTX_COND_T             e_cond;
    EVCTX_ATSC_KEY_INFO_T    t_atsc_key_info;
    SIZE_T                   z_info_size = sizeof (UINT16);

    t_atsc_key_info.e_atsc_key_type  = EVCTX_ATSC_KEY_TYPE_TOTAL_AVAIL_TIME;
    t_atsc_key_info.pv_atsc_key_info = NULL;

    return  c_evctx_get_event_info (h_event,
                                    EVCTX_KEY_TYPE_ENG_SPECIFIC,
                                    & t_atsc_key_info,
                                    & z_info_size,
                                    pui2_avail_hours,
                                    & e_cond);
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_adjust_vplane_order
 *
 * Description: This API adjusts the order of video plane.

 * Inputs:  b_top                  TRUE - Place video plane to the top of OSD plane.
 *                                 FALSE - Place video plane to the bottom of OSD plane.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svc_adjust_vplane_order (BOOL    b_top)
{
#ifndef APP_EPG_FULL_VIDEO
#if 0
    INT32                        i4_rc;
    VSH_SET_PLANE_ORDER_INFO_T   t_vplane_order;

    if (b_top)
    {
        DBG_INFO (("<EPG> adjust video plane to top\n\r"));

        /* Set video-plane order to top. */
        t_vplane_order.e_order_ctrl     = VSH_PLANE_ORDER_CTRL_TOP;
        t_vplane_order.u.ui1_num_layers = 0;
    }
    else
    {
        DBG_INFO (("<EPG> adjust video plane to bottom\n\r"));

        /* Set video-plane order to bottom. */
        t_vplane_order.e_order_ctrl     = VSH_PLANE_ORDER_CTRL_BOTTOM;
        t_vplane_order.u.ui1_num_layers = 0;
    }

    /* Set plane order. */
    i4_rc = c_svctx_set_stream_attr (t_g_model.h_svctx,
                                     ST_VIDEO,
                                     SM_VSH_SET_TYPE_PLANE_ORDER,
                                     (VOID*)(& t_vplane_order),
                                     sizeof (VSH_SET_PLANE_ORDER_INFO_T));

    if (i4_rc != SVCTXR_OK)
    {
        DBG_ERROR (("<EPG> ERR: set plane order failed = %d\n\r", i4_rc));

        /* Don't care return value since the call may fail due to no signal or no video. */
        i4_rc = SVCTXR_OK;
    }
#endif /* #if 0 */
#endif /* APP_EPG_FULL_VIDEO */

    return EPGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_select_service
 *
 * Description: This API selects the service.

 * Inputs:  b_fit_to_screen        Fit to screen size.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svc_select_service (BOOL    b_fit_to_screen,
                              SURF_MODE_T e_surf_mode)
{
    INT32                        i4_rc;
    UINT32                       ui4_channel_id;
    SNK_DESC_T                   t_snk_desc = {0};
    VSH_REGION_INFO_T            t_video_region;
    VSH_REGION_INFO_T            t_disp_region;
    VSH_SET_PLANE_ORDER_INFO_T   t_vplane_order;

#ifndef APP_537X_SUPPORT

    SRC_DESC_T                   t_src_desc = {0};

#endif /* APP_537X_SUPPORT */

    BOOL        b_adjust_only = FALSE;
#ifdef APP_NAV_REC_TSHIFT_SUPPORT
    UINT32      ui4_tshift_status = 0;
    SIZE_T      z_size = (SIZE_T)ICL_RECID_REC_TSHIFT_STATUS_SIZE;
#endif

#ifdef APP_NAV_REC_PVR_SUPPORT
		UINT32		ui4_pvr_status = 0;
		SIZE_T		z_pvr_size = (SIZE_T)ICL_RECID_REC_PVR_STATUS_SIZE;
#endif

    /* Reset structures. */
    c_memset (& t_video_region, 0, sizeof (VSH_REGION_INFO_T));
    c_memset (& t_disp_region,  0, sizeof (VSH_REGION_INFO_T));
    c_memset (& t_vplane_order, 0, sizeof (VSH_SET_PLANE_ORDER_INFO_T));

    /* Reset variables. */
    t_g_model.b_with_cc = FALSE;

#ifdef APP_EPG_FULL_VIDEO

    /* Specify video region. */
    t_video_region.ui4_x                = 0;
    t_video_region.ui4_y                = 0;
    t_video_region.ui4_width            = VSH_REGION_MAX_WIDTH;
    t_video_region.ui4_height           = VSH_REGION_MAX_HEIGHT;

    /* Specify display region. */
    t_disp_region.ui4_x                 = 0;
    t_disp_region.ui4_y                 = 0;
    t_disp_region.ui4_width             = VSH_REGION_MAX_WIDTH;
    t_disp_region.ui4_height            = VSH_REGION_MAX_HEIGHT;

    /* Specify video-plane order. */
    t_vplane_order.e_order_ctrl         = VSH_PLANE_ORDER_CTRL_BOTTOM;
    t_vplane_order.u.ui1_num_layers     = 0;

#else /* #ifndef APP_EPG_FULL_VIDEO */

    if (b_fit_to_screen) /* Adjust video plane to full screen. */
    {
        /* Adjust video plane to the buttom. */
        i4_rc = epg_svc_adjust_vplane_order (FALSE);

        if (i4_rc != SVCTXR_OK)
        {
            DBG_ERROR (("<EPG> ERR: adjust video plane order failed = %d\n\r", i4_rc));
        }

        /* Specify video region. */
        t_video_region.ui4_x            = 0;
        t_video_region.ui4_y            = 0;
        t_video_region.ui4_width        = VSH_REGION_MAX_WIDTH;
        t_video_region.ui4_height       = VSH_REGION_MAX_HEIGHT;

        /* Specify display region. */
        t_disp_region.ui4_x             = 0;
        t_disp_region.ui4_y             = 0;
        t_disp_region.ui4_width         = VSH_REGION_MAX_WIDTH;
        t_disp_region.ui4_height        = VSH_REGION_MAX_HEIGHT;

        /* Specify video-plane order. */
        t_vplane_order.e_order_ctrl     = VSH_PLANE_ORDER_CTRL_BOTTOM;
        t_vplane_order.u.ui1_num_layers = 0;
    }
    else /* Adjust video plane to a quarter window. */
    {
        /* Specify video region. */
        t_video_region.ui4_x            = 0;
        t_video_region.ui4_y            = 0;
        t_video_region.ui4_width        = VSH_REGION_MAX_WIDTH;
        t_video_region.ui4_height       = VSH_REGION_MAX_HEIGHT;

        /* Specify display region. */
        t_disp_region.ui4_x             = (UINT32)(((UINT64)(VIDEO_FRM_X + VIDEO_TXT_X + t_g_model.i4_osd_offset_x) * VSH_REGION_MAX_WIDTH / t_g_model.ui4_canvas_width) + 1);
        t_disp_region.ui4_y             = (UINT32)(((UINT64)(VIDEO_FRM_Y + VIDEO_TXT_Y + t_g_model.i4_osd_offset_y) * VSH_REGION_MAX_HEIGHT / t_g_model.ui4_canvas_height) + 1);
        t_disp_region.ui4_width         = (UINT32)(((UINT64)(VIDEO_TXT_W * VSH_REGION_MAX_WIDTH) / t_g_model.ui4_canvas_width) + 1);
        t_disp_region.ui4_height        = (UINT32)(((UINT64)(VIDEO_TXT_H * VSH_REGION_MAX_HEIGHT) / t_g_model.ui4_canvas_height) + 1);

        /* Specify video-plane order. */
        t_vplane_order.e_order_ctrl     = VSH_PLANE_ORDER_CTRL_TOP;
        t_vplane_order.u.ui1_num_layers = 0;
    }

#endif /* APP_EPG_FULL_VIDEO */

    /* Specify sink description. */
    t_snk_desc.pt_video_region          = & t_video_region;     /* If NULL, using last pt_video_region parameter. */
    t_snk_desc.pt_disp_region           = & t_disp_region;      /* If NULL, using last pt_disp_region parameter. */

#ifdef APP_EPG_FULL_VIDEO
    t_snk_desc.pt_video_plane_order     = NULL;                 /* Video plane won't be changed. */
#else
    t_snk_desc.pt_video_plane_order     = & t_vplane_order;     /* Video plane order. */
#endif /* APP_EPG_FULL_VIDEO */

    t_snk_desc.ps_snk_grp_name          = SN_PRES_MAIN_DISPLAY; /* Defined in u_sys_name.h */

    /* Get current channel id. */
    ui4_channel_id = a_util_cnfg_get_crnt_channel_id();

#ifdef APP_537X_SUPPORT

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
        /* Check if it is timeshifting. If yes, don't reselect the service. */
        i4_rc = a_icl_get(ICL_MAKE_ID(ICL_GRPID_REC, ICL_RECID_REC_TSHIFT_STATUS),
                              &ui4_tshift_status,
                              &z_size);
        if(i4_rc == ICLR_OK &&
           (ui4_tshift_status & ICL_RECID_REC_TSHIFT_STATUS_PLAYING) > 0)
        {
            if(e_surf_mode == SURF_MODE_THIS)
            {
                b_adjust_only = TRUE;
            }
        }
#endif

#ifdef APP_NAV_REC_PVR_SUPPORT
		/* Check if it is PVR. If yes, don't reselect the service. */
		i4_rc = a_icl_get(ICL_MAKE_ID(ICL_GRPID_REC, ICL_RECID_REC_PVR_STATUS),
							  &ui4_pvr_status,
							  &z_pvr_size);
		if(i4_rc == ICLR_OK &&
		   (ui4_pvr_status & ICL_RECID_REC_PVR_STATUS_RECORDING) > 0)
		{
			if(e_surf_mode == SURF_MODE_THIS)
			{
				b_adjust_only = TRUE;
			}
		}
#endif

    if(b_adjust_only)
    {
        /* Adjust the video plane. */
        i4_rc = c_svctx_set_stream_attr (t_g_model.h_svctx,
                                         ST_VIDEO,
                                         SM_VSH_SET_TYPE_DISP_REGION,
                                         (VOID*)(& t_disp_region),
                                         sizeof (VSH_REGION_INFO_T));

        i4_rc = c_svctx_set_stream_attr (t_g_model.h_svctx,
                                         ST_VIDEO,
                                         SM_VSH_SET_TYPE_PLANE_ORDER,
                                         (VOID*)(& t_vplane_order),
                                         sizeof (VSH_SET_PLANE_ORDER_INFO_T));

        c_svctx_set_video_plane (t_g_model.h_svctx, SCC_VID_DEINT);

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
        if(i4_rc == ICLR_OK &&
           (ui4_tshift_status & ICL_RECID_REC_TSHIFT_STATUS_PLAYING) > 0)
        {
            if(e_surf_mode == SURF_MODE_THIS)
            {
                nav_rec_ts_pb_reselect();
            }
        }
#endif
    }
    else
    {
        /* Select service. */
        i4_rc = a_tv_change_channel_ex (t_g_model.h_svctx,
                                        ST_MASK_VIDEO | ST_MASK_AUDIO,
                                        ui4_channel_id,
                                        & t_snk_desc,
                                        _epg_nfy_svctx,
                                        (VOID*) ui4_channel_id);
    }

#else /* #ifndef APP_537X_SUPPORT */

    /* Specify source description. */
    t_src_desc.ui2_svc_lst_id    = t_g_model.ui2_svl_id;
    t_src_desc.ui2_svl_rec_id    = t_g_model.t_svl_rec.ui2_svl_rec_id;  /* SVL record id. */
    t_src_desc.ps_conn_src_type  = BRDCST_HANDLER_DEFAULT_NAME;         /* Defined in u_brdcst.h */
    t_src_desc.ps_conn_src_name  = SN_MAIN_TUNER_GRP;                   /* Tuner name. */

    /* Select service. */
    i4_rc = c_svctx_select_svc (t_g_model.h_svctx,
                                ST_MASK_VIDEO | ST_MASK_AUDIO,          /* Defined in u_common.h */
                                & t_src_desc,                           /* in */
                                & t_snk_desc,                           /* in */
                                _epg_nfy_svctx,                         /* in */
                                (VOID*) ui4_channel_id);                /* Tags */

#endif /* APP_537X_SUPPORT */

    if (i4_rc != SVCTXR_OK)
    {
        DBG_ERROR (("<EPG> ERR: select service failed = %d\n\r", i4_rc));
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_update_svl
 *
 * Description: This API updates SVL given a surfing mode.
 *
 * Inputs:  e_surf_mode         Surfing mode.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svc_update_svl (SURF_MODE_T    e_surf_mode)
{
    INT32     i4_rc;
    UINT32    ui4_channel_id;

    DBG_INFO (("<EPG> select service (mode = %d)\n\r", e_surf_mode));

    /* Get current channel id. */
    ui4_channel_id = a_util_cnfg_get_crnt_channel_id();

#ifdef APP_RESET_TMP_UNLOCK
    UINT32  ui4_svl_ver_id = SVL_NULL_VER_ID;
#endif

#ifdef APP_NAV_REC_PVR_SUPPORT
	UINT32		ui4_pvr_status = 0;
	SIZE_T		z_pvr_size = (SIZE_T)ICL_RECID_REC_PVR_STATUS_SIZE;
#endif


#ifdef APP_NAV_REC_PVR_SUPPORT
	/* Check if it is PVR. If yes, don't reselect the service. */
	i4_rc = a_icl_get(ICL_MAKE_ID(ICL_GRPID_REC, ICL_RECID_REC_PVR_STATUS),
						  &ui4_pvr_status,
						  &z_pvr_size);
	if(i4_rc == ICLR_OK &&
	   (ui4_pvr_status & ICL_RECID_REC_PVR_STATUS_RECORDING) > 0)
	{
		return EPGR_OK;
	}
#endif

#ifdef APP_RESET_TMP_UNLOCK

    if (e_surf_mode != SURF_MODE_THIS)
    {
        /* Get svl record. */
        i4_rc = c_svl_get_rec (t_g_model.h_svl,
                               t_g_model.t_svl_rec.ui2_svl_rec_id,
                               & t_g_model.t_svl_rec,
                               & ui4_svl_ver_id);

        if (i4_rc == SVLR_OK)
        {
            /* If end-user ever temporarily unlock the service. */
            if ((t_g_model.t_svl_rec.uheader.t_rec_hdr.ui4_option_mask & SB_VOPT_USER_TMP_UNLOCK) > 0)
            {
                /* Lock SVL. */
                c_svl_lock (t_g_model.h_svl);

                /* Clean user temporarily unlock bit. */
                t_g_model.t_svl_rec.uheader.t_rec_hdr.ui4_option_mask &= ~SB_VOPT_USER_TMP_UNLOCK;

                /* Update SVL. */
                i4_rc = c_svl_update_rec (t_g_model.h_svl,
                                          & t_g_model.t_svl_rec,
                                          TRUE);

                if (i4_rc != SVLR_OK)
                {
                    DBG_ERROR (("<EPG> ERR: update svl record failed = %d\n\r", i4_rc));
                }

                /* Unlock SVL. */
                c_svl_unlock (t_g_model.h_svl);
            }
        }
        else
        {
            DBG_ERROR (("<EPG> ERR: get svl record failed = %d\n\r", i4_rc));
        }
    }

#endif /* APP_RESET_TMP_UNLOCK */

    /* Get svl record by surfing mode. */
    i4_rc = _epg_model_get_svl_rec_by_surf_mode (t_g_model.h_svl,        /* in */
                                                 EPG_NET_MASK,           /* in */
                                                 e_surf_mode,            /* in */
                                                 & ui4_channel_id,       /* in/out */
                                                 & t_g_model.t_svl_rec); /* in/out */

    if (i4_rc == EPGR_OK)
    {
        if (e_surf_mode != SURF_MODE_THIS) /* Select previous or next channel. */
        {
            /* Save channel IDs. */
            a_util_cnfg_set_last_channel_id (a_util_cnfg_get_crnt_channel_id());
            a_util_cnfg_set_crnt_channel_id (ui4_channel_id);
        }
    }
    else
    {
        DBG_ERROR (("<EPG> ERR: get SVL record failed = %d\n\r", i4_rc));
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_blank_video
 *
 * Description: This API blanks the video but not stop the service.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svc_blank_video (BOOL    b_main)
{
    if (b_main)
    {
        return  c_svctx_set_video_plane (t_g_model.h_svctx, SCC_VID_BLANK);
    }
    else
    {
        return  c_svctx_set_video_plane (t_g_model.h_svctx_sub, SCC_VID_BLANK);
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      epg_svc_enable_default_video_plane_mode
 * Description
 *      The API is used to enable or disable the video plane of EPG video.
 *      If disable, it will be set to SCC_VID_BLANK. If enable, it will
 *      set to SCC_VID_DEINT.
 *
 *      Currently, this API is accomplished by calling video mute manager
 *      implemented in APP_TV.
 *
 * Input arguments
 *      b_enable        the flag to enable or disable video plane
 * Output arguments
 *      None
 * Returns
 *      0                           the routine is successfully.
 *      Any other values    Failed.
 *---------------------------------------------------------------------------*/
INT32 epg_svc_enable_default_video_plane_mode(BOOL    b_enable)
{
    HANDLE_T       h_svctx = t_g_model.h_svctx;
    INT32          i4_ret;

    if (b_enable)
    {
        APPTV_DEBUG_WHO_CALL_MUTE(0, TV_VIDEO_MUTE_MASK_FORCE, FALSE );
        i4_ret = A_TV_SET_VIDEO_MUTE (
                                      VIDEO_MUTE_ID_EPG, 
                                      h_svctx,
                                      TV_VIDEO_MUTE_MASK_FORCE,
                                      FALSE);
    }
    else
    {
        APPTV_DEBUG_WHO_CALL_MUTE(0, TV_VIDEO_MUTE_MASK_FORCE, TRUE );
        i4_ret = A_TV_SET_VIDEO_MUTE (
                                      VIDEO_MUTE_ID_EPG,
                                      h_svctx,
                                      TV_VIDEO_MUTE_MASK_FORCE,
                                      TRUE);
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_disable_blue_mute
 *
 * Description: This function is called when EPG resumes.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svc_disable_blue_mute (VOID)
{
    INT32                   i4_rc;
    BOOL                    b_blue_mute;
    SVCTX_VIDEO_MUTE_INFO_T t_video_mute_info;

    /* Disable blue mute. */
    b_blue_mute = FALSE;

    if (b_blue_mute == TRUE)
    {
        /* blue mute */
        t_video_mute_info.b_enable          = TRUE;
        t_video_mute_info.t_color.ui1_red   = EPG_BLUE_MUTE_R;
        t_video_mute_info.t_color.ui1_green = EPG_BLUE_MUTE_G;
        t_video_mute_info.t_color.ui1_blue  = EPG_BLUE_MUTE_B;
    }
    else
    {
        /* black mute */
        t_video_mute_info.b_enable          = TRUE;
        t_video_mute_info.t_color.ui1_red   = 0;
        t_video_mute_info.t_color.ui1_green = 0;
        t_video_mute_info.t_color.ui1_blue  = 0;
    }

    do
    {
        i4_rc = c_svctx_set(t_g_model.h_svctx,
                             SVCTX_COMMON_SET_VIDEO_MUTE,
                             &t_video_mute_info,
                             sizeof(SVCTX_VIDEO_MUTE_INFO_T));
        if (i4_rc < 0)
        {
            break;
        }

        i4_rc = c_svctx_set(t_g_model.h_svctx_sub,
                             SVCTX_COMMON_SET_VIDEO_MUTE,
                             &t_video_mute_info,
                             sizeof(SVCTX_VIDEO_MUTE_INFO_T));
        if (i4_rc < 0)
        {
            break;
        }
    } while(0);

    return i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_stop
 *
 * Description: This API stops current service.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svc_stop (VOID)
{
    INT32    i4_rc;

    i4_rc = c_svctx_stop_svc (t_g_model.h_svctx);

    return ((i4_rc == SVCTXR_OK) || (i4_rc == SVCTXR_ALREADY_STOPPED)) ? SVCTXR_OK : i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_unblock
 *
 * Description: This API unblocks current service.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svc_unblock (VOID)
{
    INT32     i4_rc;
    UINT32    ui4_ver_id = SVL_NULL_VER_ID;

    /* Unlock current service. */
    i4_rc = a_tv_unlock_crnt_svc (t_g_model.h_svctx, NULL, NULL);

    if (i4_rc == TVR_OK)
    {
        if (t_g_model.b_svl_found)
        {
            /* Update svl record. */
            i4_rc = c_svl_get_rec (t_g_model.h_svl,
                                   t_g_model.t_svl_rec.ui2_svl_rec_id,
                                   & t_g_model.t_svl_rec,
                                   & ui4_ver_id);
        }
    }

    return i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_is_tv_block
 *
 * Description: This API checks if the TV source is blocked.
 *
 * Inputs:  pv_rating           Rating info.
 *
 * Outputs: pb_exceed           TRUE - Blocked.
 *                              FALSE - Not blocked.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
BOOL epg_svc_is_tv_block (VOID)
{
    SVC_BLOCK_COND_T    e_block_cond;

    e_block_cond = c_svctx_svc_block_check (t_g_model.h_svctx,
                                            SVC_BLOCK_CHECK_ALL,
                                            SN_MAIN_TUNER_GRP,
                                            & t_g_model.t_svl_rec,
                                            NULL);

    if (e_block_cond == SVC_BLOCK_COND_USER_BLOCK_INP)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_is_signal_loss
 *
 * Description: This API checks if TV has signal or not.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE                No signal.
 *          FALSE               Has signal.
 ----------------------------------------------------------------------------*/
BOOL epg_svc_is_signal_loss (VOID)
{
    INT32         i4_ret;
    BOOL          b_signal_loss = FALSE;

    i4_ret = c_svctx_is_signal_loss (t_g_model.h_svctx,
                                     & b_signal_loss);

    if (i4_ret != SVCTXR_OK)
    {
        return TRUE;
    }

    return b_signal_loss;
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_check_block
 *
 * Description: This API checks if the event should be blocked.
 *
 * Inputs:  pv_rating           Rating info.
 *
 * Outputs: pb_exceed           TRUE - Blocked.
 *                              FALSE - Not blocked.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svc_check_block (VOID*    pv_rating,
                           BOOL*    pb_exceed)
{
    SVC_BLOCK_COND_T    e_block_cond;

    e_block_cond = c_svctx_svc_block_check (t_g_model.h_svctx,
                                            SVC_BLOCK_CHECK_ALL,
                                            SN_MAIN_TUNER_GRP,
                                            & t_g_model.t_svl_rec,
                                            pv_rating);

    if ((e_block_cond == SVC_BLOCK_COND_PASSED) ||
        (e_block_cond == SVC_BLOCK_COND_PASSED_AND_NO_RATING_SET))
    {
        *pb_exceed = FALSE;
    }
    else
    {
        *pb_exceed = TRUE;
    }

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_get_caption_num_recs
 *
 * Description: This API gets the number of captions in SCDB.
 *
 * Inputs:  e_stream_type       Stream type.
 *
 * Outputs: pui2_num_recs       The number of records.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svc_get_caption_num_recs (UINT16*    pui2_num_recs)
{
#ifdef APP_DVBT_SUPPORT

    INT32     i4_res;
    UINT32    ui4_scdb_info_num;

    extern BOOL a_nav_ttx_sbti_get_scdb_info_num (UINT32* pui4_scdb_info_num);

    *pui2_num_recs = 0;

    /* Check SCDB first. */
    i4_res = c_svctx_get_scdb_num_recs (t_g_model.h_svctx,
                                        ST_SUBTITLE,
                                        pui2_num_recs);

    if ((i4_res == SVCTXR_OK) &&
        (*pui2_num_recs == 0))
    {
        /* Check SCDB info from ttx engine. */
        if (a_nav_ttx_sbti_get_scdb_info_num (& ui4_scdb_info_num))
        {
            *pui2_num_recs = (UINT16)ui4_scdb_info_num;
        }
        else
        {
            i4_res = EPGR_FAIL;
        }
    }

    return i4_res;

#else /* #ifndef APP_DVBT_SUPPORT */

    INT32     i4_res;

    *pui2_num_recs = 0;

    /* Check SCDB first. */
    i4_res = c_svctx_get_scdb_num_recs (t_g_model.h_svctx,
                                        ST_CLOSED_CAPTION,
                                        pui2_num_recs);

    if ((i4_res == SVCTXR_OK) &&
        (*pui2_num_recs == 0))
    {
        /* Check CC indicator from SVCTX if the number of CC in SCDB is 0. */
        *pui2_num_recs = (t_g_model.b_with_cc) ? (UINT16)1 : (UINT16)0;
    }

    return i4_res;

#endif /* APP_DVBT_SUPPORT */
}

/*-----------------------------------------------------------------------------
 * Name: epg_svc_is_crnt_event_with_cc
 *
 * Description: This API checks if the current event has CC
 *
 * Inputs:
 *
 * Outputs:
 *
 *
 * Returns: TRUE                   with CC, EPG will show CC icon on current event.
 *              FALSE                   without CC.
 ----------------------------------------------------------------------------*/
BOOL epg_svc_is_crnt_event_with_cc(EPG_CC_QUERY_DATA_T* pt_cc_query_data)
{
#ifdef APP_DVBT_SUPPORT

    INT32     i4_res;
    UINT32    ui4_scdb_info_num;
    UINT16    ui2_num_recs = 0;

    extern BOOL a_nav_ttx_sbti_get_scdb_info_num (UINT32* pui4_scdb_info_num);

    /* Check SCDB first. */
    i4_res = c_svctx_get_scdb_num_recs (t_g_model.h_svctx,
                                        ST_SUBTITLE,
                                        &ui2_num_recs);

    if ((i4_res == SVCTXR_OK) &&
        (ui2_num_recs == 0))
    {
        /* Check SCDB info from ttx engine. */
        if (a_nav_ttx_sbti_get_scdb_info_num (& ui4_scdb_info_num))
        {
            ui2_num_recs = (UINT16)ui4_scdb_info_num;
        }
    }

    if (ui2_num_recs > 0)
    {
        return TRUE;
    }

    return FALSE;

#else /* #ifndef APP_DVBT_SUPPORT */

    /* Invalid parameter */
    if (NULL == pt_cc_query_data)
    {
        return FALSE;
    }

    /* Get CC indicator from internal cache by EPG */
    if (EPG_CC_QUERY_DIRECTLY == pt_cc_query_data->e_query_mode)
    {
        return t_g_model.b_with_cc;
    }

    /* Query CC indicator from SVCTX */
    else if (EPG_CC_QUERY_SVCTX == pt_cc_query_data->e_query_mode)
    {
        /* Update EPG internal cache flag */
        t_g_model.b_with_cc = _epg_svc_is_with_cc_dscrptr(pt_cc_query_data);

        return t_g_model.b_with_cc;
    }

    else
    {
        return FALSE;
    }

#endif /* APP_DVBT_SUPPORT */
}

/*-----------------------------------------------------------------------------
 * Name: epg_svl_lock
 *
 * Description: This API locks the SVL.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svl_lock (VOID)
{
    return   c_svl_lock (t_g_model.h_svl);
}

/*-----------------------------------------------------------------------------
 * Name: epg_svl_unlock
 *
 * Description: This API unlocks the SVL.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svl_unlock (VOID)
{
    return  c_svl_unlock (t_g_model.h_svl);
}

/*-----------------------------------------------------------------------------
 * Name: epg_svl_get_rec
 *
 * Description: This API gets current SVL record.
 *
 * Inputs:  -
 *
 * Outputs: pt_svl_rec          Current SVL record.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svl_get_rec (SVL_REC_T*    pt_svl_rec)
{
    UINT32  ui4_ver_id = SVL_NULL_VER_ID;

    return  c_svl_get_rec (t_g_model.h_svl,
                           t_g_model.t_svl_rec.ui2_svl_rec_id,
                           pt_svl_rec,
                           & ui4_ver_id);
}

/*-----------------------------------------------------------------------------
 * Name: epg_svl_get_rec_by_channel_id
 *
 * Description: This API gets the SVL record given a channel id.
 *
 * Inputs:  ui4_channel_id      Channel id.
 *
 * Outputs: pt_svl_rec          Current SVL record.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svl_get_rec_by_channel_id (UINT32        ui4_channel_id,
                                     SVL_REC_T*    pt_svl_rec)
{
    UINT32  ui4_ver_id = SVL_NULL_VER_ID;

    return  c_svl_get_rec_by_channel (t_g_model.h_svl,
                                      ui4_channel_id,
                                      EPG_NET_MASK,
                                      0,
                                      pt_svl_rec,
                                      & ui4_ver_id);
}

/*-----------------------------------------------------------------------------
 * Name: epg_svl_get_rec_by_surf_mode
 *
 * Description: This API gets SVL record by channel id and surfing mode, e.g.
 *              next channel, previous channel, or this channel.
 *
 * Inputs:      e_surf_mode         Surfing mode.
 *              pui4_channel_id     Current channel id.
 *              pt_svl_rec          Current SVL record.
 *
 * Outputs:     pui4_channel_id     Resulted channel id.
 *              pt_svl_rec          Resulted SVL record.
 *
 * Returns: 0                       Successful.
 *          Any other values        Failed.
 *-----------------------------------------------------------------------------*/
INT32 epg_svl_get_rec_by_surf_mode (SURF_MODE_T      e_surf_mode,
                                    UINT32*          pui4_channel_id,
                                    SVL_REC_T*       pt_svl_rec)
{
    return  _epg_model_get_svl_rec_by_surf_mode (t_g_model.h_svl,
                                                 EPG_NET_MASK,
                                                 e_surf_mode,
                                                 pui4_channel_id,
                                                 pt_svl_rec);
}

/*-----------------------------------------------------------------------------
 * Name: epg_svl_get_num_recs
 *
 * Description: This API returns the number of SVL records matching the broadcast
 *              type ((e.g., BRDCST_TYPE_ANALOG, BRDCST_TYPE_ATSC, or
 *              BRDCST_TYPE_DVB) and network mask values.
 *
 * Inputs:  -
 *
 * Outputs: pui2_num_recs       The number of records.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svl_get_num_recs (UINT16*    pui2_num_recs)
{
    UINT32  ui4_ver_id = SVL_NULL_VER_ID;

    return  c_svl_get_num_rec_by_brdcst_type (t_g_model.h_svl,
                                              EPG_BRDCST_TYPE,
                                              EPG_NET_MASK,
                                              pui2_num_recs,
                                              & ui4_ver_id);
}

/*-----------------------------------------------------------------------------
 * Name: epg_svl_update_rec
 *
 * Description: This API updates a given SVL record to the SVL.
 *
 * Inputs:  t_svl_rec           SVL record to be updated.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svl_update_rec (SVL_REC_T* pt_svl_rec)
{
    return  c_svl_update_rec (t_g_model.h_svl,
                              pt_svl_rec,
                              TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: epg_svl_iterate_rec
 *
 * Description: This API iterates over service records in the SVL list.
 *
 * Inputs:  ui4_channel_id      Current channel id.
 *          e_iter              Iteration mode.
 *
 * Outputs: pt_svl_rec          SVL record.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_svl_iterate_rec (UINT32           ui4_channel_id,
                           SVL_ITERATE_T    e_iter,
                           SVL_REC_T*       pt_svl_rec)
{
    UINT32  ui4_ver_id = SVL_NULL_VER_ID;

    return  c_svl_iterate_rec (t_g_model.h_svl,
                               ui4_channel_id,
                               EPG_NET_MASK,
                               e_iter,
                               pt_svl_rec,
                               & ui4_ver_id);
}

/*-----------------------------------------------------------------------------
 * Name: epg_svl_is_found
 *
 * Description: This API asks if there is any SVL found.
 *
 * Inputs:  -
 *
 * Outputs: TRUE                SVL exists.
 *          FALSE               No SVL.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
BOOL epg_svl_is_found (VOID)
{
    return  (t_g_model.b_svl_found) ? TRUE : FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: epg_svl_get_id
 *
 * Description: This API returns current SVL id.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: Current SVL id.
 ----------------------------------------------------------------------------*/
UINT16 epg_svl_get_id (VOID)
{
    return  t_g_model.ui2_svl_id;
}

/*-----------------------------------------------------------------------------
 * Name: epg_svl_is_analog_chn
 *
 * Description: This API checks if it is an analog service.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE  - An analog channel.
            FALSE - A digital channel.
 ----------------------------------------------------------------------------*/
BOOL epg_svl_is_analog_chn (VOID)
{
    INT32        i4_rc;
    BOOL         b_analog;
    SVL_REC_T    t_svl_rec;
    ISL_REC_T    t_isl_rec;
    UINT32       ui4_crnt_channel_id;
    UINT32       ui4_ver_id;

    b_analog = FALSE;

    do
    {
        i4_rc = a_cfg_get_crnt_channel_id (& ui4_crnt_channel_id);

        if (i4_rc != APP_CFGR_OK)
        {
            break;
        }

        /* Get ISL record. */
        i4_rc = a_tv_get_isl_rec_by_win_id (TV_WIN_ID_MAIN, & t_isl_rec);

        if (i4_rc != TVR_OK)
        {
            break;
        }

        /* Get SVL record. */
        i4_rc = c_svl_get_rec_by_channel (t_g_model.h_svl,
                                          ui4_crnt_channel_id,
                                          EPG_NET_MASK,
                                          0,
                                          & t_svl_rec,
                                          & ui4_ver_id);

        if (i4_rc == SVLR_REC_NOT_FOUND)
        {
            /* Set broadcast type to unknown. */
            t_svl_rec.uheader.t_rec_hdr.e_brdcst_type = BRDCST_TYPE_UNKNOWN;
        }
        else if (i4_rc != SVLR_OK)
        {
            break;
        }

        /* Check if current service is analog. */
        if ((t_isl_rec.e_src_type == INP_SRC_TYPE_TV) &&
            (t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG))
        {
            b_analog = TRUE;
        }

    } while (0);

    return  b_analog;
}

/*-----------------------------------------------------------------------------
 * Name: epg_dt_get_loc_dtg
 *
 * Description: This API gets current local time in DTG_T structure.
 *
 * Inputs:  -
 *
 * Outputs: pt_local_dtg
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_dt_get_loc_dtg (DTG_T*    pt_loc_dtg)
{
    return  c_dt_utc_sec_to_loc_dtg (c_dt_get_brdcst_utc (NULL, NULL), pt_loc_dtg);
}

/*-----------------------------------------------------------------------------
 * Name: epg_dt_get_utc_sec
 *
 * Description: This API gets current UTC time in seconds.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: Current UTC time in seconds.
 ----------------------------------------------------------------------------*/
TIME_T epg_dt_get_utc_sec (VOID)
{
    return  c_dt_get_brdcst_utc (NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name: epg_dt_get_cond
 *
 * Description: This API gets current condition of date-time.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: Current condition of date-time.
 ----------------------------------------------------------------------------*/
DT_COND_T epg_dt_get_cond (VOID)
{
    DT_COND_T    t_dt_cond;

    c_memset(&t_dt_cond, 0, sizeof(DT_COND_T));

    c_dt_get_brdcst_utc (NULL, & t_dt_cond);

    return t_dt_cond;
}

/*-----------------------------------------------------------------------------
 * Name: epg_dt_get_utc_dtg
 *
 * Description: This API gets current UTC time in DTG_T structure.
 *
 * Inputs:  -
 *
 * Outputs: pt_local_dtg
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_dt_get_utc_dtg (DTG_T*    pt_utc_dtg)
{
    return  c_dt_utc_sec_to_dtg (c_dt_get_brdcst_utc (NULL, NULL), pt_utc_dtg);
}

/*----------------------------------------------------------------------
 *
 * Name: epg_dt_diff
 *
 * Description: Compute the difference in seconds between two DTG times
 *              delta seconds = t_dtg_to - t_dtg_from.
 *
 * Input:
 *     pt_dtg_from    Pointer to a Day-Time-Group (UTC or Local) structure.
 *     pt_dtg_to      Pointer to a Day-Time-Group (UTC or Local) structure.
 *
 * Output:
 *     None.
 *
 * Return:
 *     Number of seconds between two DTG values.
 *     NULL_TIME if 'pt_dtg_from' or 'pt_dtg_to' is NULL.
----------------------------------------------------------------------*/
TIME_T epg_dt_diff (DTG_T*    pt_dtg_from,
                    DTG_T*    pt_dtg_to)
{
    return  c_dt_diff (pt_dtg_from, pt_dtg_to);
}
/*-----------------------------------------------------------------------------
 * Name: epg_dt_get_start_loc_dtg_by_event
 *
 * Description: This API gets local starting time for a given event handle.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pt_start_dtg        Local starting time in DTG_T structure.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_dt_get_start_loc_dtg_by_event (HANDLE_T    h_event,
                                         DTG_T*      pt_start_dtg)
{
    INT32           i4_rc;
    TIME_T          t_time_start;
    EVCTX_COND_T    e_cond;
    SIZE_T          z_info_size = sizeof (TIME_T);

    /* Get event start time. */
    i4_rc = c_evctx_get_event_info (h_event,
                                    EVCTX_KEY_TYPE_START_TIME,
                                    NULL,
                                    & z_info_size,
                                    & t_time_start,
                                    & e_cond);

    if (i4_rc == EVCTXR_OK)
    {
        /* Convert UTC time to local DTG structure. */
        i4_rc = c_dt_utc_sec_to_loc_dtg (t_time_start + DT_SHIFT_SECOND,
                                         pt_start_dtg);
    }

    return i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_dt_get_end_loc_dtg_by_event
 *
 * Description: This API gets local ending time for a given event handle.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pt_end_dtg          Local ending time in DTG_T structure.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_dt_get_end_loc_dtg_by_event (HANDLE_T    h_event,
                                       DTG_T*      pt_end_dtg)
{
    INT32           i4_rc;
    TIME_T          t_time_start;
    TIME_T          t_time_duration;
    EVCTX_COND_T    e_cond;
    SIZE_T          z_info_size = sizeof (TIME_T);

    /* Get event start time. */
    i4_rc = c_evctx_get_event_info (h_event,
                                    EVCTX_KEY_TYPE_START_TIME,
                                    NULL,
                                    & z_info_size,
                                    & t_time_start,
                                    & e_cond);

    if (i4_rc == EVCTXR_OK)
    {
        /* Get event duration. */
        i4_rc = c_evctx_get_event_info (h_event,
                                        EVCTX_KEY_TYPE_DURATION,
                                        NULL,
                                        & z_info_size,
                                        & t_time_duration,
                                        & e_cond);

        if (i4_rc == EVCTXR_OK)
        {
            /* Convert UTC time to local DTG structure. */
            i4_rc = c_dt_utc_sec_to_loc_dtg (t_time_start + t_time_duration + DT_SHIFT_SECOND,
                                             pt_end_dtg);
        }
    }

    return i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_dt_get_start_utc_sec_by_date
 *
 * Description: This API return UTC starting time for a given date offset.
 *
 * Inputs:  i2_date_offset      Date offset compared to current date.
 *
 * Outputs: pt_start_sec        UTC starting time.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_dt_get_start_utc_sec_by_date (INT16      i2_date_offset,
                                        TIME_T*    pt_start_sec)
{
    INT32     i4_rc;
    TIME_T    t_time_start;
    TIME_T    t_time_offset;
    DTG_T     t_crnt_loc_dtg, t_dest_loc_dtg, t_dest_utc_dtg;

    c_memset(&t_crnt_loc_dtg, 0, sizeof(DTG_T));

    /* Get starting time. */
    i4_rc = DTR_OK;

    if (i2_date_offset <= 0)
    {
        t_time_start = 0;
    }
    else
    {
        /* Get current local DTG. */
        i4_rc = c_dt_utc_sec_to_loc_dtg (c_dt_get_brdcst_utc (NULL, NULL), & t_crnt_loc_dtg);

        if (i4_rc == DTR_OK)
        {
            /* Calculate time offset. */
            t_time_offset = (i2_date_offset - 1) * 24 * 3600;

            t_time_offset += (23 - t_crnt_loc_dtg.ui1_hr) * 3600 +
                             (59 - t_crnt_loc_dtg.ui1_min) * 60 +
                             (60 - t_crnt_loc_dtg.ui1_sec);

            /* Add time offset to current local time. */
            i4_rc = c_dt_add (& t_crnt_loc_dtg,
                              t_time_offset,
                              & t_dest_loc_dtg);

            if (i4_rc == DTR_OK)
            {
                /* Convert local time to UTC time. */
                i4_rc = c_dt_conv_utc_local (& t_dest_loc_dtg, & t_dest_utc_dtg);

                if (i4_rc == DTR_OK)
                {
                    /* Start utc time for a given date. */
                    t_time_start = c_dt_dtg_to_sec (& t_dest_utc_dtg);
                }
                else
                {
                    DBG_ERROR (("<EPG> ERR: convert local time to UTC time failed = %d\n\r", i4_rc));
                }
            }
            else
            {
                DBG_ERROR (("<EPG> ERR: dt add failed = %d\n\r", i4_rc));
            }
        }
        else
        {
            DBG_ERROR (("<EPG> ERR: get local time failed = %d\n\r", i4_rc));
        }
    }

    if (i4_rc != DTR_OK) /* Something error? */
    {
        t_time_start = 0;
    }

    /* Copy variable. */
    *pt_start_sec = t_time_start;

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_dt_get_time_str
 *
 * Description: This API returns a format time given a DTG_T structure.
 *
 * Inputs:  t_dtg         Date-time structure.
 *          e_time_mode   Time format.
 *
 * Outputs: pw2s_time     Time string.
 *
 * Returns: -
 *-----------------------------------------------------------------------------*/
INT32 epg_dt_get_time_str (DTG_T              t_dtg,
                           EPG_TIME_MODE_T    e_time_mode,
                           UTF16_T*           pw2s_time)
{
    INT32    i4_rc;
    UINT8    ui1_i;
    CHAR     s_time[DT_TIME_MAX_LEN]       = {0};
    CHAR     s_dow[DT_DATE_MAX_LEN]        = {0};
    CHAR     s_month[DT_DATE_MAX_LEN]      = {0};
    CHAR     s_ampm[DT_SYMBOL_MAX_LEN]     = {0};
    CHAR     s_sepr[DT_SYMBOL_MAX_LEN]     = {0}; /* Separator. */
    CHAR     s_date_seq[DT_SYMBOL_MAX_LEN] = {0}; /* Date sequence. */
    UINT8    ui1_hour;
    UINT8    ui1_dow_idx;
    UINT8    ui1_month_idx;
    UINT8    ui1_ampm_idx;
    UINT8    ui1_offset = 0;
    BOOL     b_24_hour;
    BOOL     b_match;

    /* Convert UTF16_T to UTF8_T. */
    i4_rc = c_uc_w2s_to_ps (MLM_EPG_TEXT (t_g_model.ui2_lang_id, MLM_EPG_KEY_SYM_DATE_SEQ),
                            s_date_seq,
                            DT_SYMBOL_MAX_LEN);

    if (i4_rc != UCR_OK)
    {
        s_dow[0] = 0;

        DBG_ERROR (("<EPG> ERR: UTF16_T to UTF8_T failed = %d\n\r", i4_rc));
    }

    /* Check if the 24-hour format is desired. */
    if ((c_uc_w2s_strlen (MLM_EPG_TEXT (t_g_model.ui2_lang_id, MLM_EPG_KEY_SYM_PM)) == 0) &&
        (c_uc_w2s_strlen (MLM_EPG_TEXT (t_g_model.ui2_lang_id, MLM_EPG_KEY_SYM_PM)) == 0))
    {
        b_24_hour = TRUE;  /* Use 24-hour format. */
    }
    else
    {
        b_24_hour = FALSE; /* Sse 12-hour format. */
    }

    /* Get mlm index. */
    ui1_hour     = t_dtg.ui1_hr;
    ui1_ampm_idx = MLM_EPG_KEY_SYM_AM;

    if (! b_24_hour) /* 12-hour time. */
    {
        if (ui1_hour >= 12)
        {
            ui1_hour -= 12;
            ui1_ampm_idx = MLM_EPG_KEY_SYM_PM;   /* pm */
        }
        else
        {
            ui1_ampm_idx = MLM_EPG_KEY_SYM_AM;   /* am */
        }

        ui1_hour = (ui1_hour == 0) ? (UINT8)12 : ui1_hour;
    }

    if (e_time_mode == EPG_TIME_MODE_FULL) /* Full mode */
    {
        /* Use complete day-of-week and month string. */
        ui1_dow_idx   = (UINT8)(MLM_EPG_KEY_DOW_SUN + t_dtg.ui1_dow);
        ui1_month_idx = (UINT8)(MLM_EPG_KEY_MONTH_JAN + t_dtg.ui1_mo - 1);
    }
    else /* Other modes */
    {
        /* Use abbreviation day-of-week and month string. */
        ui1_dow_idx   = (UINT8)(MLM_EPG_KEY_DOW_ABBR_SUN + t_dtg.ui1_dow);
        ui1_month_idx = (UINT8)(MLM_EPG_KEY_MONTH_ABBR_JAN + t_dtg.ui1_mo - 1);
    }

    /* Convert UTF16_T to UTF8_T. */
    i4_rc = c_uc_w2s_to_ps (MLM_EPG_TEXT (t_g_model.ui2_lang_id, ui1_dow_idx),
                             s_dow,
                             DT_DATE_MAX_LEN);

    if (i4_rc != UCR_OK)
    {
        s_dow[0] = 0;

        DBG_ERROR (("<EPG> ERR: UTF16_T to UTF8_T failed = %d\n\r", i4_rc));
    }

    /* UTF16 to UTF 8 */
    i4_rc = c_uc_w2s_to_ps (MLM_EPG_TEXT (t_g_model.ui2_lang_id, ui1_month_idx),
                            s_month,
                            DT_DATE_MAX_LEN);

    if (i4_rc != UCR_OK)
    {
        s_month[0] = 0;

        DBG_ERROR (("<EPG> ERR: UTF16_T to UTF8_T failed = %d\n\r", i4_rc));
    }

    /* UTF16 to UTF8 */
    if (! b_24_hour) /* 12-hour time */
    {
        i4_rc = c_uc_w2s_to_ps (MLM_EPG_TEXT (t_g_model.ui2_lang_id, ui1_ampm_idx),
                                s_ampm,
                                DT_SYMBOL_MAX_LEN);

        if (i4_rc != UCR_OK)
        {
            s_ampm[0] = 0;

            DBG_ERROR (("<EPG> ERR: UTF16_T to UTF8_T failed = %d\n\r", i4_rc));
        }
    }

    /* Dow, day-month-year hour:minute:sec AM(PM) */
    if (e_time_mode == EPG_TIME_MODE_FULL)
    {
        /* Separator between dow and date. */
        i4_rc = c_uc_w2s_to_ps (MLM_EPG_TEXT (t_g_model.ui2_lang_id, MLM_EPG_KEY_SYM_DOW_DATE_SEPR),
                                s_sepr,
                                DT_SYMBOL_MAX_LEN);

        if (i4_rc != UCR_OK)
        {
            s_sepr[0] = 0;

            DBG_ERROR (("<EPG> ERR: UTF16_T to UTF8_T failed = %d\n\r", i4_rc));
        }

        /* Day of week. */
        c_snprintf (s_time,
                    (SIZE_T)DT_TIME_MAX_LEN,
                    "%s%s",
                    s_dow,
                    s_sepr);

        /* Date separator. */
        i4_rc = c_uc_w2s_to_ps (MLM_EPG_TEXT (t_g_model.ui2_lang_id, MLM_EPG_KEY_SYM_DATE_SEPR),
                                s_sepr,
                                DT_SYMBOL_MAX_LEN);

        if (i4_rc != UCR_OK)
        {
            s_sepr[0] = 0;

            DBG_ERROR (("<EPG> ERR: UTF16_T to UTF8_T failed = %d\n\r", i4_rc));
        }

        /* Date sequence output. */
        for (ui1_i = 0; ui1_i < 3; ui1_i ++)
        {
            if (ui1_i == 2) /* Empty separator. */
            {
                s_sepr[0] = 0;
            }

            ui1_offset = (UINT8) c_strlen (s_time); /* The position to be cascaded. */

            if (ui1_offset >= DT_TIME_MAX_LEN) /* Validate offset */
            {
                break;
            }

            switch (s_date_seq[ui1_i])
            {
                case 'D': /* Day */
                    c_snprintf (s_time + ui1_offset,
                                (SIZE_T)(DT_TIME_MAX_LEN - ui1_offset),
                                "%d%s",
                                t_dtg.ui1_day,
                                s_sepr);
                    break;

                case 'M': /* Month */
                    c_snprintf (s_time + ui1_offset,
                                (SIZE_T)(DT_TIME_MAX_LEN - ui1_offset),
                                "%s%s",
                                s_month,
                                s_sepr);
                    break;

                case 'Y': /* Year */
                    c_snprintf (s_time + ui1_offset,
                                (SIZE_T)(DT_TIME_MAX_LEN - ui1_offset),
                                "%d%s",
                                t_dtg.ui2_yr,
                                s_sepr);
                    break;

                default: /* Unknown */
                    break;
            }
        }

        /* Separator between date and time. */
        i4_rc = c_uc_w2s_to_ps (MLM_EPG_TEXT (t_g_model.ui2_lang_id, MLM_EPG_KEY_SYM_DATE_TIME_SEPR),
                                s_sepr,
                                DT_SYMBOL_MAX_LEN);

        if (i4_rc != UCR_OK)
        {
            s_sepr[0] = 0;

            DBG_ERROR (("<EPG> ERR: UTF16_T to UTF8_T failed = %d\n\r", i4_rc));
        }

        /* Cascade separator. */
        c_strcat (s_time, s_sepr);

        /* Time */
        ui1_offset = (UINT8) c_strlen (s_time);

        /* Time separator */
        i4_rc = c_uc_w2s_to_ps (MLM_EPG_TEXT (t_g_model.ui2_lang_id, MLM_EPG_KEY_SYM_TIME_SEPR),
                                s_sepr,
                                DT_SYMBOL_MAX_LEN);

        if (i4_rc != UCR_OK)
        {
            s_sepr[0] = 0;

            DBG_ERROR (("<EPG> ERR: UTF16_T to UTF8_T failed = %d\n\r", i4_rc));
        }

        if (ui1_offset < DT_TIME_MAX_LEN) /* Validate offset */
        {
#ifdef APP_EPG_NO_SECOND

            c_snprintf (s_time + ui1_offset,
                        (SIZE_T)(DT_TIME_MAX_LEN - ui1_offset),
                        "%d%s%02d",
                        ui1_hour,
                        s_sepr,
                        t_dtg.ui1_min);

#else /* #ifndef APP_EPG_NO_SECOND */

            c_snprintf (s_time + ui1_offset,
                        (SIZE_T)(DT_TIME_MAX_LEN - ui1_offset),
                        "%d%s%02d%s%02d",
                        ui1_hour,
                        s_sepr,
                        t_dtg.ui1_min,
                        s_sepr,
                        t_dtg.ui1_sec);

#endif /* APP_EPG_NO_SECOND */
        }

        /* AM, PM */
        if (! b_24_hour) /* 12-hour time */
        {
            ui1_offset = (UINT8) c_strlen (s_time);

            if (ui1_offset < DT_TIME_MAX_LEN) /* Validate offset */
            {
                c_snprintf (s_time + ui1_offset,
                            (SIZE_T)(DT_TIME_MAX_LEN - ui1_offset),
                            " %s",
                            s_ampm);
            }
        }
    }
    else if (e_time_mode == EPG_TIME_MODE_HM) /* Hour:minute AM(PM) */
    {
        /* Time separator */
        i4_rc = c_uc_w2s_to_ps (MLM_EPG_TEXT (t_g_model.ui2_lang_id, MLM_EPG_KEY_SYM_TIME_SEPR),
                                s_sepr,
                                DT_SYMBOL_MAX_LEN);

        if (i4_rc != UCR_OK)
        {
            s_sepr[0] = 0;

            DBG_ERROR (("<EPG> ERR: UTF16_T to UTF8_T failed = %d\n\r", i4_rc));
        }

        c_snprintf (s_time,
                    (SIZE_T)(DT_TIME_MAX_LEN - ui1_offset),
                    "%d%s%02d",
                    ui1_hour,
                    s_sepr,
                    t_dtg.ui1_min);

        /* AM, PM */
        if (! b_24_hour) /* 12-hour time */
        {
            ui1_offset = (UINT8) c_strlen (s_time);

            if (ui1_offset < DT_TIME_MAX_LEN) /* Validate offset */
            {
                c_snprintf (s_time + ui1_offset,
                            (SIZE_T)(DT_TIME_MAX_LEN - ui1_offset),
                            " %s",
                            s_ampm);
            }
        }
    }
    else if (e_time_mode == EPG_TIME_MODE_MD) /* Month-day */
    {
        /* Date separator */
        i4_rc = c_uc_w2s_to_ps (MLM_EPG_TEXT (t_g_model.ui2_lang_id, MLM_EPG_KEY_SYM_DATE_SEPR),
                                s_sepr,
                                DT_SYMBOL_MAX_LEN);

        if (i4_rc != UCR_OK)
        {
            s_sepr[0] = 0;

            DBG_ERROR (("<EPG> ERR: UTF16_T to UTF8_T failed = %d\n\r", i4_rc));
        }

        /* Date sequence output */
        b_match = FALSE;

        for (ui1_i = 0; ui1_i < 3; ui1_i ++)
        {
            ui1_offset = (UINT8) c_strlen (s_time);

            if (ui1_offset >= DT_TIME_MAX_LEN) /* Validate offset */
            {
                break;
            }

            switch (s_date_seq[ui1_i])
            {
                case 'D': /* Day */
                    b_match = TRUE;

                    c_snprintf (s_time + ui1_offset,
                                (SIZE_T)(DT_TIME_MAX_LEN - ui1_offset),
                                "%d%s",
                                t_dtg.ui1_day,
                                s_sepr);
                    break;

                case 'M': /* Month */
                    b_match = TRUE;

                    c_snprintf (s_time + ui1_offset,
                                (SIZE_T)(DT_TIME_MAX_LEN - ui1_offset),
                                "%s%s",
                                s_month,
                                s_sepr);
                    break;

                default: /* Unknown */
                    break;
            }

            if (b_match) /* Empty separator. */
            {
                s_sepr[0] = 0;
            }
        }
    }
    else if (e_time_mode == EPG_TIME_MODE_DOW) /* Day of week */
    {
        c_snprintf (s_time,
                    (SIZE_T)DT_TIME_MAX_LEN,
                    "%s",
                    s_dow);
    }

#ifdef APP_EPG_CUSTOM_GENERIC_PROCESS_SUPPORT
    i4_rc = epg_custom_generic_process(EPG_CUSTOM_OVERWRITE_DISPLAY_TIME_FORMAT,
                                   (VOID*)&t_dtg,
                                   (VOID*)e_time_mode,
                                   (VOID*)s_time);
    if (i4_rc < 0)
    {
        s_time[0] = 0;

        DBG_ERROR (("<EPG> ERR: epg_custom_generic_process failed = %d\n\r", i4_rc));
    }
#endif

    /* UTF8 to UTF16 */
    i4_rc = c_uc_ps_to_w2s (s_time,
                            pw2s_time,
                            DT_TIME_MAX_LEN);

    if (i4_rc != UCR_OK)
    {
        pw2s_time[0] = 0;

        DBG_ERROR (("<EPG> ERR: UTF16_T to UTF8_T failed = %d\n\r", i4_rc));
    }

    return (i4_rc == UCR_OK) ? EPGR_OK : EPGR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: epg_timer_create
 *
 * Description: This API creates a timer.
 *
 * Inputs:  -
 *
 * Outputs: ph_timer            Timer handle.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_timer_create (HANDLE_T*    ph_timer)
{
    return c_timer_create (ph_timer);
}

/*-----------------------------------------------------------------------------
 * Name: epg_timer_start
 *
 * Description: This API starts a timer.
 *
 * Inputs:  e_timer_type        Timer type.
 *          ui4_delay           Timer delay.
 *          e_timer_flag        Timer flag - either X_TIMER_FLAG_ONCE or
 *                              X_TIMER_FLAG_REPEAT.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_timer_start (HANDLE_T        h_timer,
                       UINT32          ui4_delay,
                       TIMER_FLAG_T    e_timer_flag)
{
    INT32       i4_rc;

    i4_rc = 0;

    if (ui4_delay > 0) /* Start a timer only if the delay is greater than 0. */
    {
        i4_rc = c_timer_start (h_timer,
                               ui4_delay,
                               e_timer_flag,
                               _epg_nfy_timer,
                               NULL);
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: epg_timer_stop
 *
 * Description: This API stops a timer.
 *
 * Inputs:  e_timer_type        Timer type.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_timer_stop (HANDLE_T    h_timer)
{
    return  c_timer_stop (h_timer);
}

/*-----------------------------------------------------------------------------
 * Name: epg_cfg_get_language_id
 *
 * Description: This API returns current language id.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: Current language id.
 ----------------------------------------------------------------------------*/
UINT16 epg_cfg_get_language_id (VOID)
{
    return  t_g_model.ui2_lang_id;
}

/*-----------------------------------------------------------------------------
 * Name:  epg_str_ps_to_w2s
 *
 * Description: This API converts a UTF-8 string to UTF-16 string.
 *              String must be NULL-terminated.
 *
 * Inputs:  ps_src                  Source string to be converted.
 *          ui4_dst_len             Buffer size of pw2s_dst, in character units.
 *
 * Outputs: pw2s_dst                The converted string.
 *
 * Returns: 0                       Successful.
 *          Any other values        Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_str_ps_to_w2s (const CHAR*    ps_src,
                         UTF16_T*       pw2s_dst,
                         UINT32         ui4_dst_len)
{
    return  c_uc_ps_to_w2s (ps_src,
                            pw2s_dst,
                            ui4_dst_len);
}

/*-----------------------------------------------------------------------------
 * Name:  epg_str_w2s_to_ps
 *
 * Description: This API converts a UTF-16 string to UTF-8 string.
 *              String must be NULL-terminated.
 *
 * Inputs:  pw2s_src                Source string to be converted.
 *          ui4_dst_len             Buffer size of ps_dst, in character units.
 *
 * Outputs: ps_dst                  The converted string.
 *
 * Returns: 0                       Successful.
 *          Any other values        Failed.
 ----------------------------------------------------------------------------*/
INT32 epg_str_w2s_to_ps (const UTF16_T*    pw2s_src,
                         CHAR*             ps_dst,
                         UINT32            ui4_dst_len)
{
    return  c_uc_w2s_to_ps (pw2s_src,
                            ps_dst,
                            ui4_dst_len);
}

/*-----------------------------------------------------------------------------
 * Name:  epg_str_w2s_strcpy
 *
 * Description: The API copies a UTF16_T. Note that the original data in pw2s_to
 *              will be overwritten.
 *
 * Inputs:  pw2s_src                Source string to be converted.
 *
 * Outputs: pw2s_dst                The copied string.
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID epg_str_w2s_strcpy (UTF16_T*          pw2s_dst,
                         const UTF16_T*    pw2s_src)
{
    c_uc_w2s_strcpy (pw2s_dst, pw2s_src);
}

/*-----------------------------------------------------------------------------
 * Name:  epg_str_w2s_strcat
 *
 * Description: This API cascades source string to the end of destination string.
 *
 * Inputs:  pw2s_src                Null-terminated source string.
 *
 * Outputs: pw2s_dst                Null-terminated combined string.
 *
 * Returns: pointer of combined string
 ----------------------------------------------------------------------------*/
VOID epg_str_w2s_strcat (UTF16_T*          pw2s_dst,
                         const UTF16_T*    pw2s_src)
{
    c_uc_w2s_strcat (pw2s_dst, pw2s_src);
}

/*-----------------------------------------------------------------------------
 * Name:  epg_str_w2s_strlen
 *
 * Description: This API counts the number of UTF16_T characters in a string.
 *
 * Inputs:  pw2s_str                UTF-16 string to be counted.
 *
 * Outputs: -
 *
 * Returns: string length (UTF16_T characters).
 *          return 0 if pw2s_str is NULL
 ----------------------------------------------------------------------------*/
SIZE_T epg_str_w2s_strlen (UTF16_T*    pw2s_str)
{
    return  c_uc_w2s_strlen (pw2s_str);
}

/*-----------------------------------------------------------------------------
 * Name:  epg_str_w2s_strlen
 *
 * Description: This API counts the number of UTF16_T characters in a string.
 *
 * Inputs:  pw2s_str                UTF-16 string to be counted.
 *
 * Outputs: -
 *
 * Returns: string length (UTF16_T characters).
 *          return 0 if pw2s_str is NULL
 ----------------------------------------------------------------------------*/
VOID epg_str_trim (CHAR*    ps_str)
{
    SIZE_T    z_len;
    INT32     i4_i = 0;
    INT32     i4_j;

    z_len = c_strlen (ps_str);

    if (z_len == 0)
    {
        return;
    }

    /* Trim spaces and tabs from beginning: */
    while ((ps_str[i4_i] == ' ' ) ||
           (ps_str[i4_i] == '\t') ||
           (ps_str[i4_i] == '\n'))
    {
        i4_i ++;
    }

    if (i4_i > 0)
    {
        for (i4_j = 0; i4_j < (INT32)(z_len - i4_i); i4_j ++)
        {
            ps_str[i4_j] = ps_str[i4_j+i4_i];
        }

        ps_str[i4_j] = '\0';
    }

    /* Trim spaces and tabs from end: */
    i4_i = (INT32)(c_strlen (ps_str) - 1);

    while ((ps_str[i4_i] == ' ' ) ||
           (ps_str[i4_i] == '\t') ||
           (ps_str[i4_i] == '\n'))
    {
        i4_i --;
    }

    if (i4_i < (INT32)(c_strlen (ps_str) - 1))
    {
        ps_str[i4_i+1] = '\0';
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: epg_osd_get_canvas_handle
 *
 * Description: This API gets canvas handle.
 *
 * Inputs:  -
 *
 * Outputs: Handle to canvas.
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 epg_osd_get_canvas_handle (HANDLE_T*    ph_canvas)
{
    *ph_canvas = t_g_model.h_canvas;

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: epg_osd_get_offset_x
 *
 * Description: This API returns OSD offset y.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: OSD offset x.
 ----------------------------------------------------------------------------*/
INT32 epg_osd_get_offset_x (VOID)
{
    return  t_g_model.i4_osd_offset_x;
}

/*-----------------------------------------------------------------------------
 * Name: epg_osd_get_offset_y
 *
 * Description: This API returns OSD offset y.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: OSD offset x.
 ----------------------------------------------------------------------------*/
INT32 epg_osd_get_offset_y (VOID)
{
    return  t_g_model.i4_osd_offset_y;
}

/*-----------------------------------------------------------------------------
 * Name: epg_osd_get_canvas_width
 *
 * Description: This API returns the width of canvas.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: The width of OSD.
 ----------------------------------------------------------------------------*/
UINT32 epg_osd_get_canvas_width (VOID)
{
    return  t_g_model.ui4_canvas_width;
}

/*-----------------------------------------------------------------------------
 * Name: epg_osd_get_canvas_height
 *
 * Description: This API returns the height of canvas.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: The height of OSD.
 ----------------------------------------------------------------------------*/
UINT32 epg_osd_get_canvas_height (VOID)
{
    return  t_g_model.ui4_canvas_height;
}

/*
   Configuration model.
*/

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
INT32  epg_cfg_get_config_data (EPG_CONFIG_T* pt_config)
{
    if (NULL == pt_config)
    {
        return EPGR_FAIL;
    }

    c_memcpy(pt_config, &(t_g_model.t_config), sizeof(EPG_CONFIG_T));

    return EPGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL   epg_cfg_is_av_mute(VOID)
{
    EPG_AV_CONFIG_T e_av_cfg = t_g_model.t_config.e_av_config;

    if (EPG_AV_CONFIG_NO_VIDEO_AUDIO == e_av_cfg)
    {
        return TRUE;
    }

    return FALSE;
}

/*
   EPG utility APIs.
*/

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
INT32  epg_util_set_sound_out_port (BOOL b_enabled)
{
#if 0
    SM_COMMAND_T   at_scc_cmds [8];
    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16  ui2_aud_out_mask = 0;
    UINT16  ui2_mute_port_mask = 0;
    INT16   i2_val = 0;

    /* Get current setting */
    a_cfg_av_get(ui2_id, &i2_val);

    /* Initial mute port mask: these mask will be mute */
    ui2_mute_port_mask = SCC_AUD_OUT_PORT_SPEAKER       |
                         SCC_AUD_OUT_PORT_HEADPHONE     |
                         SCC_AUD_OUT_PORT_2_CH          |
                         SCC_AUD_OUT_PORT_5_1_CH        |
                         SCC_AUD_OUT_PORT_SPDIF;

    /* Unset mute port mask */
    ui2_aud_out_mask =  (UINT16)(i2_val & (~ui2_mute_port_mask));

    if (! b_enabled)
    {
        /* Clear all outport */
        at_scc_cmds [0].e_code      = SCC_CMD_CODE_GRP_TYPE;
        at_scc_cmds [0].u.ui4_data  = SCC_CMD_TYPE_AUDIO;
        at_scc_cmds [1].e_code      = SCC_CMD_CODE_NAME;
        at_scc_cmds [1].u.ps_text   = SN_PRES_MAIN_DISPLAY;
        at_scc_cmds [2].e_code      = SCC_CMD_CODE_AUDIO_OUT_PORT;
        at_scc_cmds [2].u.ui4_data  = ui2_aud_out_mask;
        at_scc_cmds [3].e_code      = SM_CMD_CODE_END;

        c_scc_comp_grp_set (at_scc_cmds);
    }
    else
    {
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT));
    }
#else
    INT32                   i4_ret;
    SM_COMMAND_T            at_sm_cmds[4];
    TV_AUDIO_MUTE_MASK_T    t_audio_mute_masks = 0;

    if (b_enabled)
    {
        /* Restore audio mute status after exit EPG */
        a_tv_get_audio_mute_masks(&t_audio_mute_masks);
        a_tv_set_audio_mute_masks(t_audio_mute_masks);
    }
    else
    {
        /* Mute audio via scc before enter EPG */
        at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
        at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_AUDIO;
        at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
        at_sm_cmds[1].u.ps_text     = SN_PRES_MAIN_DISPLAY;
        at_sm_cmds[2].e_code        = SCC_CMD_CODE_AUDIO_MUTE;
        at_sm_cmds[2].u.b_boolean   = !b_enabled;
        at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
        at_sm_cmds[3].u.ui4_data    = 0;

        i4_ret = c_scc_comp_grp_set(at_sm_cmds);
        if (i4_ret != SMR_OK)
        {
            return EPGR_FAIL;
        }

        at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
        at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_AUDIO;
        at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
        at_sm_cmds[1].u.ps_text     = SN_PRES_AUX_SOUND;
        at_sm_cmds[2].e_code        = SCC_CMD_CODE_AUDIO_MUTE;
        at_sm_cmds[2].u.b_boolean   = !b_enabled;
        at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
        at_sm_cmds[3].u.ui4_data    = 0;

        i4_ret = c_scc_comp_grp_set(at_sm_cmds);
        if (i4_ret != SMR_OK)
        {
            return EPGR_FAIL;
        }
    }
#endif

    return EPGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
BOOL epg_is_active_refused(VOID)
{
    INT32   i4_ret;
    SIZE_T  z_size;
    UINT32  ui4_disable_mask = 0;
    UINT8   ui1_resume_cond = ICL_RECID_EPG_RESUME_COND_OK;

    z_size = ICL_RECID_EPG_DISABLE_MASK_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_EPG, ICL_RECID_EPG_DISABLE_MASK),
                       &ui4_disable_mask,
                       &z_size);
    if(i4_ret != ICLR_OK)
    {
        ui4_disable_mask = 0;
    }

    ui1_resume_cond = (UINT8)((ui4_disable_mask == 0) ?
                              ICL_RECID_EPG_RESUME_COND_OK :
                              ICL_RECID_EPG_RESUME_COND_FAILED);

    z_size = ICL_RECID_EPG_RESUME_COND_SIZE;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_EPG, ICL_RECID_EPG_RESUME_COND),
              &ui1_resume_cond,
              z_size);

    /* EPG is not refused if disable_mask is 0 */
    if (ui4_disable_mask == 0)
    {
        return FALSE;
    }

    return TRUE;
}

/*----------------------------------------------------------------------------
 * Name: a_epg_init
 *
 * Description: This API performs the registration for the EPG application.
 *
 * Inputs:  pt_reg       References the registration structure.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID a_epg_init (AMB_REGISTER_INFO_T*  pt_reg)
{
    /* Application descriptor. */
    APP_DESC_T  t_epg_desc =
                {
                    ~((UINT64)0),   /* ui8_flags */
                    {
                        16 * 1024,   /* z_stack_size */
                        200,        /* ui1_priority */
                        16          /* ui2_num_msgs */
                    },
                    0,              /* ui4_app_group_id */
                    0,              /* ui4_app_id */
                    {
                        0,          /* z_min_memory */
                        20 * 1024,  /* z_max_memory */
                        0,          /* ui8_max_files_size */
                        0,          /* ui2_max_files */
                        128,        /* ui2_max_handles */
                        1,          /* ui2_max_threads */
                        2,          /* ui2_max_semaphores */
                        1,          /* ui2_max_msg_queues */
                        64,         /* ui2_max_nb_msgs */
                        16          /* ui2_max_msg_size */
                    },
                    64,             /* ui2_msg_count */
                    16              /* ui2_max_msg_size */
                };

    /* Application name. */
    c_strcpy(pt_reg->s_name, EPG_NAME);
    pt_reg->s_name[APP_NAME_MAX_LEN]        = '\0';

    /* Lifecycle callback functions. */
    pt_reg->t_fct_tbl.pf_init               = _epg_app_init_fct;
    pt_reg->t_fct_tbl.pf_exit               = _epg_app_exit_fct;
    pt_reg->t_fct_tbl.pf_pause              = _epg_app_pause_fct;
    pt_reg->t_fct_tbl.pf_resume             = _epg_app_resume_fct;
    pt_reg->t_fct_tbl.pf_process_msg        = _epg_app_process_msg_fct;

    /* Application descriptor. */
    pt_reg->t_desc                          = t_epg_desc;

    /* System key. */
    pt_reg->at_system_keys[0].ui4_key_code  = BTN_EPG;
    pt_reg->at_system_keys[0].ui2_state_num = 2;
    pt_reg->ui2_key_num                     = 1;

    /* Pre-resume callback. */
    pt_reg->pf_pre_resume_cb                = _epg_app_pre_resume_cb_fct;
    pt_reg->pf_system_key_cb                = _epg_app_system_key_cb;


    /* Call to post-init function in custom part. */
    epg_custom_post_init (pt_reg);
}

/*----------------------------------------------------------------------------
 * Name: a_epg_send_sim_key
 *
 * Description: This API sends a pseudo key to EPG.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID a_epg_send_sim_key (UINT32  ui4_key_code)
{
    if (! t_g_model.b_pause) /* EPG is not in paused mode. */
    {
        /* A pseudo callback of Widget Libary. */
        _epg_nfy_wgl (WGL_MSG_KEY_DOWN, (VOID*) ui4_key_code, NULL);
    }
}

