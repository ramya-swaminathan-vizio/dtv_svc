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
 * $RCSfile: epg_ctrl.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/92 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 0c200501127fc8d07c4dbaeda3ddf488 $
 *
 * Description:
 *         This file contains the implementation of the APIs of EPG controller.
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "epg/epg_ctrl.h"

/*-----------------------------------------------------------------------------
                    defines
 ----------------------------------------------------------------------------*/
#define  DT_DISCONT_DELTA        (-5)                   /* Delta time for date-time discontinuity (in seconds). */

#ifndef  EPG_MSG_MAX_DELAY
    #ifdef LINUX_TURNKEY_SOLUTION
    #define  EPG_MSG_MAX_DELAY   (2000)                 /* Temporary solution to resolve CR[DTV00141763] */
    #else
    #define  EPG_MSG_MAX_DELAY   (1000)                 /* Maximum delay for processing a message. */
    #endif
#endif
/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
/* Epg controller variables. */
static EPG_CTRL_T    t_g_ctrl;

/* Password to disable auto-pause function. */
static CHAR          ac_g_passwd [EPG_PASSWD_DIGIT] = { 0,
                                                        0,
                                                        0,
                                                        0 };

static UTF16_T       w2s_g_null_str [] = {0};
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
/*
   Lifecycle functions.
*/
static INT32 _epg_ctrl_app_init (VOID);
static INT32 _epg_ctrl_app_exit (VOID);
static INT32 _epg_ctrl_app_pause (VOID);
static INT32 _epg_ctrl_app_resume (VOID);

/*
   Button functions.
*/
static INT32 _epg_ctrl_btn_handler (UINT32 ui4_key_code);
static INT32 _epg_ctrl_btn_released (VOID);
static INT32 _epg_ctrl_btn_digit (CHAR c_digit);
static INT32 _epg_ctrl_btn_select (VOID);
static INT32 _epg_ctrl_btn_exit (VOID);
static INT32 _epg_ctrl_btn_pvr_keys (UINT32 ui4_key_code);


/*
   Configuration functions.
*/
static INT32 _epg_ctrl_cfg_language_updated (VOID);
static INT32 _epg_ctrl_cfg_vchip_updated (VOID);
static INT32 _epg_ctrl_cfg_brdcst_svc_updated (VOID);


/*
   Channel functions.
*/
static INT32 _epg_ctrl_chn_update (BOOL b_update_chn_txt);

/*
   Direct channel input (DCI) functions.
*/
#ifdef APP_EPG_DCI_SUPPORT

static CHAR  _epg_ctrl_dci_get_digit (UINT16 ui2_number, UINT16 ui2_offset);
static INT32 _epg_ctrl_dci_input (VOID);
static BOOL  _epg_ctrl_dci_is_match (UINT32 ui4_channel_id);
static INT32 _epg_ctrl_dci_reset (BOOL b_repaint);
static INT32 _epg_ctrl_dci_update_text (UINT32 ui4_channel_id);

#endif /* APP_EPG_DCI_SUPPORT */

/*
   Description functions.
*/
static INT32 _epg_ctrl_desc_change_page (EPG_DESC_PAGE_TYPE_T e_type);
static INT32 _epg_ctrl_desc_hide_frame (VOID);
static INT32 _epg_ctrl_desc_update (VOID);


/*
   Date-time functions.
*/
#ifndef APP_NO_COLOR_KEY

static INT32 _epg_ctrl_dt_change_date (BOOL b_prev);

#endif /* APP_NO_COLOR_KEY */

static INT32 _epg_ctrl_dt_estimate_avail_time (BOOL b_cb_complete);
static INT32 _epg_ctrl_dt_get_date_idx (HANDLE_T h_event, INT16* pi2_date_idx);
static INT32 _epg_ctrl_dt_get_dow (DTG_T* pt_crnt_loc_dtg, DTG_T* pt_evt_loc_dtg, UTF16_T* pw2s_dow);
static INT32 _epg_ctrl_dt_update_crnt_time (VOID);


/*
   Event funtions.
*/
static BOOL  _epg_ctrl_evt_is_caption_avail (HANDLE_T h_event);
static BOOL  _epg_ctrl_evt_is_crnt (HANDLE_T h_event);
static BOOL  _epg_ctrl_evt_is_expired (HANDLE_T h_event);
static INT32 _epg_ctrl_evt_retry (VOID);
static INT32 _epg_ctrl_evt_update (VOID);
static INT32 _epg_ctrl_evt_nfy (UINT32 ui4_type, HANDLE_T h_event);
static INT32 _epg_ctrl_evt_free_all (VOID);
static INT32 _epg_ctrl_evt_display_none (VOID);


/*
   Help list functions.
*/
#ifndef APP_NO_COLOR_KEY

static INT32 _epg_ctrl_help_lst_reset (BOOL b_repaint);
static INT32 _epg_ctrl_help_lst_update_date_help (BOOL b_repaint);
static INT32 _epg_ctrl_help_lst_update_date_idx (BOOL b_repaint);

#endif /* APP_NO_COLOR_KEY */

static INT32 _epg_ctrl_help_lst_update_page_help (BOOL b_repaint);

#ifdef APP_EPG_THEME_SEARCH

static INT32 _epg_ctrl_help_lst_update_dvb_help (BOOL b_repaint);

#endif /* APP_EPG_THEME_SEARCH */

/*
   Password functions.
*/
static INT32 _epg_ctrl_passwd_hide_frame (BOOL b_repaint);
static INT32 _epg_ctrl_passwd_show_frame (VOID);
static INT32 _epg_ctrl_passwd_display_msg (BOOL b_clean);
static INT32 _epg_ctrl_passwd_input (VOID);


/*
   Program list functions.
*/
static INT32 _epg_ctrl_prg_lst_change_page (BOOL b_prev);
static INT32 _epg_ctrl_prg_lst_clean_elems (BOOL b_repaint);
static INT32 _epg_ctrl_prg_lst_free_elem (WGL_LB_ELEM_DATA_T* pt_elem);
static INT32 _epg_ctrl_prg_lst_get_elem (WGL_LB_ELEM_DATA_T* pt_elem, UINT16 ui2_idx);
static INT32 _epg_ctrl_prg_lst_make_up_elems (VOID);
static INT32 _epg_ctrl_prg_lst_shift_elems (BOOL b_found_event_0);
static INT32 _epg_ctrl_prg_lst_reach_boundary (BOOL b_top);
static INT32 _epg_ctrl_prg_lst_elem_hlted (VOID);
static INT32 _epg_ctrl_prg_lst_update (TIME_T t_time_start, BOOL b_clean);
static INT32 _epg_ctrl_prg_lst_update_elem (UINT16 ui2_idx);
static INT32 _epg_ctrl_prg_lst_update_scroll_images (VOID);


/*
   Type list functions.
*/
static INT32 _epg_ctrl_type_lst_elem_hlted (VOID);

/*
   Retrieving functions.
*/
static INT32 _epg_ctrl_retrieve_update_state (VOID);


/*
   OSD functions.
*/
static INT32 _epg_ctrl_screen_clean (VOID);

/*
   Service functions.
*/
static INT32 _epg_ctrl_svc_select (SURF_MODE_T e_surf_mode);
static INT32 _epg_ctrl_svc_signal_locked (VOID);
static INT32 _epg_ctrl_svc_signal_loss (VOID);
static INT32 _epg_ctrl_svc_input_blocked (VOID);
static INT32 _epg_ctrl_svc_event_blocked (VOID);
static INT32 _epg_ctrl_svc_channel_blocked (VOID);
static INT32 _epg_ctrl_svc_hidden_channel (VOID);
static INT32 _epg_ctrl_svc_normal_service (VOID);
static INT32 _epg_ctrl_svc_scdb_updated (VOID);
static INT32 _epg_ctrl_svc_scrambled (VOID);
static INT32 _epg_ctrl_svc_authorized (VOID);
static INT32 _epg_ctrl_svc_service_changed (VOID);
static INT32 _epg_ctrl_svc_audio_video (VOID);
static INT32 _epg_ctrl_svc_audio_only (VOID);
static INT32 _epg_ctrl_svc_no_audio_video (VOID);
static INT32 _epg_ctrl_svc_event_ready_handler (BOOL b_read);


/*
   SVL functions.
*/
static INT32 _epg_ctrl_svl_update (UINT32 ui4_reason);


/*
   Rating check functions.
*/
static INT32 _epg_ctrl_check_rating (HANDLE_T h_event, BOOL* pb_exceed);


/*
   Video text functions.
*/
static INT32 _epg_ctrl_video_txt_msg (UTF16_T* pw2s_text);


/*
   Widget notifications handler.
*/
static INT32 _epg_ctrl_wgl_process_nfy (WIDGET_MSG_T* pt_wgl_msg);
static INT32 _epg_ctrl_wgl_get_focus (VOID);

/*
   Timer handler.
*/
static INT32 _epg_ctrl_timer_expired_handler (HANDLE_T h_timer);
static INT32 _epg_ctrl_timer_reset_pause (VOID);

/*
   Theme search.
*/
#ifdef APP_EPG_THEME_SEARCH

static INT32 _epg_ctrl_theme_search_show (BOOL b_repaint);
static INT32 _epg_ctrl_theme_search_hide (BOOL b_repaint);

#endif /* APP_EPG_THEME_SEARCH */

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_app_init
 *
 * Description: This function is called when EPG starts.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_app_init (VOID)
{
    /*
       Reset controller variables.
    */
    c_memset (& t_g_ctrl, 0, sizeof(EPG_CTRL_T));

    /* initialize view */
    RET_ON_ERR (epg_view_init ());

    /*
       Set visibilities to widgets.
    */
    RET_ON_ERR (epg_view_main_frm_set_visibility      (TRUE));   /* main frame */
    RET_ON_ERR (epg_view_passwd_frm_set_visibility    (FALSE));   /* password frame */
    RET_ON_ERR (epg_view_desc_frm_set_visibility      (FALSE));   /* description frame */
    RET_ON_ERR (epg_view_desc_bk_frm_set_visibility   (TRUE));    /* description background frame */
    RET_ON_ERR (epg_view_video_frm_set_visibility     (TRUE));    /* video frame */
    RET_ON_ERR (epg_view_base_frm_set_visibility      (TRUE));    /* base map frame widget */

    RET_ON_ERR (epg_view_passwd_edit_set_visibility   (TRUE));    /* password edit box */

#ifdef APP_EPG_ICON_MSG

    RET_ON_ERR (epg_view_retrieve_icon_set_visibility (TRUE));    /* retrieving icon */
    RET_ON_ERR (epg_view_retrieve_txt_set_visibility  (FALSE));   /* retrieving text */

#else /* #ifndef APP_EPG_ICON_MSG */

    RET_ON_ERR (epg_view_retrieve_icon_set_visibility (FALSE));   /* retrieving icon */
    RET_ON_ERR (epg_view_retrieve_txt_set_visibility  (TRUE));    /* retrieving text */

#endif /* APP_EPG_ICON_MSG */

    RET_ON_ERR (epg_view_time_txt_set_visibility      (TRUE));    /* time text */
    RET_ON_ERR (epg_view_prg_txt_set_visibility       (TRUE));    /* program text */
    RET_ON_ERR (epg_view_video_txt_set_visibility     (TRUE));    /* video text */
    RET_ON_ERR (epg_view_page_txt_set_visibility      (TRUE));    /* page index text */
    RET_ON_ERR (epg_view_desc_txt_set_visibility      (TRUE));    /* program description text */
    RET_ON_ERR (epg_view_passwd_txt_set_visibility    (TRUE));    /* password text */
    RET_ON_ERR (epg_view_chn_lst_set_visibility       (TRUE));    /* channel list */
    RET_ON_ERR (epg_view_chn_txt_set_visibility       (TRUE));    /* channel info text */

#ifdef APP_EPG_FULL_VIDEO
    RET_ON_ERR (epg_view_passwd_alarm_txt_set_visibility(FALSE));	  /* password alarm text */
#endif

#ifdef APP_EPG_DCI_SUPPORT

    RET_ON_ERR (epg_view_dci_hts_set_visibility       (TRUE));    /* direct channel input text */

#else

    RET_ON_ERR (epg_view_dci_hts_set_visibility       (FALSE));   /* direct channel input text */

#endif /* APP_EPG_DCI_SUPPORT */

    RET_ON_ERR (epg_view_prg_lst_set_visibility       (TRUE));    /* program list */
    RET_ON_ERR (epg_view_desc_lst_set_visibility      (TRUE));    /* description list */

#ifdef APP_EPG_ICON_SEP

    RET_ON_ERR (epg_view_icon_lst_set_visibility      (TRUE));    /* icon list */

#else /* #ifndef APP_EPG_ICON_SEP */

    RET_ON_ERR (epg_view_icon_lst_set_visibility      (FALSE));   /* icon list */

#endif /* APP_EPG_ICON_SEP */

    RET_ON_ERR (epg_view_help_lst_set_visibility      (TRUE));    /* help list */

    /* CR[DTV00137785] Video display incorrect while enter to EPG */
    /* Set main frame invisible to fix this CR, otherwise repaint video text will result in main frame displayed */
    
    /* CR[DTV00211581] [Pre-Test Fail][5388 64M]Cannot display video if unplug/plug signal line or */
    /* block channel then change channel in EPG */
    /* Set main frame invisible after set its child widgets attributes */
    RET_ON_ERR (epg_view_main_frm_set_visibility      (FALSE));   /* main frame */

    /*
       Update language.
    */
    RET_ON_ERR (_epg_ctrl_cfg_language_updated ());

#ifdef APP_EPG_ICON_MSG

    /*
       Set default retrieving icon.
    */
    t_g_ctrl.h_retrieve_icon = RETRIEVE_ICON_IMG_1;

    /*
       Set image to retrieving icon.
    */
    RET_ON_ERR (epg_view_retrieve_icon_set_image (t_g_ctrl.h_retrieve_icon));

#endif /* APP_EPG_ICON_MSG */

    /*
       Reset current channel id.
    */
    t_g_ctrl.ui4_crnt_channel_id = INVALID_CHANNEL_ID;

#ifdef APP_DVBT_SUPPORT

    /*
       Read event type from acfg.
    */
    a_cfg_get_evt_type (& t_g_ctrl.ui1_event_type);

#endif /* APP_DVBT_SUPPORT */

    /*
       Create timers.
    */
    RET_ON_ERR (epg_timer_create (& t_g_ctrl.h_timer_clock));
    RET_ON_ERR (epg_timer_create (& t_g_ctrl.h_timer_retry));
    RET_ON_ERR (epg_timer_create (& t_g_ctrl.h_timer_pause));
    RET_ON_ERR (epg_timer_create (& t_g_ctrl.h_timer_retrieve));
    RET_ON_ERR (epg_timer_create (& t_g_ctrl.h_timer_dci));
    RET_ON_ERR (epg_timer_create (& t_g_ctrl.h_timer_passwd_msg));
    RET_ON_ERR (epg_timer_create (& t_g_ctrl.h_timer_passwd_dlg));
    RET_ON_ERR (epg_timer_create (& t_g_ctrl.h_timer_delay_update));
    RET_ON_ERR (epg_timer_create (& t_g_ctrl.h_timer_delay_query_cc));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_app_exit
 *
 * Description: This function is called when EPG exits.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_app_exit (VOID)
{
    UINT16  ui2_i;

    /*
       Free event handles.
    */
    for (ui2_i = 0; ui2_i < EPG_EVT_BUFFER_SIZE; ui2_i ++)
    {
        if (t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE)
        {
            epg_evt_free (t_g_ctrl.ah_events[ui2_i]);
            t_g_ctrl.ah_events[ui2_i] = NULL_HANDLE;
        }
    }

    /*
       Free elements in previous/next page.
    */
    for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
    {
        _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_i]);
        _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_i]);
    }

    /*
       Free current/next events.
    */
    if (t_g_ctrl.h_event_crnt != NULL_HANDLE)
    {
        epg_evt_free (t_g_ctrl.h_event_crnt);
        t_g_ctrl.h_event_crnt = NULL_HANDLE;
    }

    if (t_g_ctrl.h_event_next != NULL_HANDLE)
    {
        epg_evt_free (t_g_ctrl.h_event_next);
        t_g_ctrl.h_event_next = NULL_HANDLE;
    }

    /*
       Free timers.
    */
    c_timer_delete (t_g_ctrl.h_timer_clock);
    c_timer_delete (t_g_ctrl.h_timer_retry);
    c_timer_delete (t_g_ctrl.h_timer_pause);
    c_timer_delete (t_g_ctrl.h_timer_retrieve);
    c_timer_delete (t_g_ctrl.h_timer_dci);
    c_timer_delete (t_g_ctrl.h_timer_passwd_msg);
    c_timer_delete (t_g_ctrl.h_timer_passwd_dlg);
    c_timer_delete (t_g_ctrl.h_timer_delay_update);
    c_timer_delete (t_g_ctrl.h_timer_delay_query_cc);

    /* Update blue mute. */
    RET_ON_ERR (a_cfg_av_update (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE)));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_app_pause
 *
 * Description: This function is called when EPG pauses.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_app_pause (VOID)
{
    INT32    i4_ret;

    if (epg_cli_is_running ()) /* CLI command is running. */
    {
        /* Stop cli command. */
        epg_cli_stop ();
    }

    /*
       Adjust video plane.
    */
    if (epg_svl_is_found ()) /* SVL is found. */
    {
        if (a_am_is_power_on ()) /* TV is on. */
        {
            #ifndef APP_EPG_FULL_VIDEO
            /* [DTV00211641] [5388] EPG thumbnail video flash on the black screen, after exit EPG */
            /* The result should not depend on performance and multi-thread co-work sequence */
            /* Before select_svc, invoke epg_svc_blank_video to force blank current  thumbnail video*/
            /* Blank video. */
            EPG_LOG_ON_FAIL (epg_svc_blank_video (TRUE));
            #endif
        }
        else /* TV is going to be off. */
        {
            /* Blank video. */
            EPG_LOG_ON_FAIL (epg_svc_blank_video (TRUE));
        }
    }

    /*
       Hide main frame.
    */
    RET_ON_ERR (epg_view_main_frm_hide ());

    /* Enable audio port after leave EPG. */
    if (epg_cfg_is_av_mute())
    {
        epg_util_set_sound_out_port(TRUE);
    }

    /*
       Select service to full-screen after hide EPG main frame to avoid PIP window transparent issue
    */
    if (epg_svl_is_found ()) /* SVL is found. */
    {
        if (a_am_is_power_on ()) /* TV is on. */
        {
            /* Select service to full-screen mode. */
            i4_ret = epg_svc_select_service (TRUE, SURF_MODE_THIS);

            if (i4_ret != EPGR_OK)
            {
                DBG_ERROR (("<EPG> ERR: select service failed = %d\n\r", i4_ret));
            }
        }
    }

    /*
       Free event handles.
    */
    RET_ON_ERR (_epg_ctrl_evt_free_all ());

    /*
       Stop timers.
    */
    RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_clock));
    RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_pause));
    RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_retry));
    RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_retrieve));
    RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_dci));
    RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_passwd_msg));
    RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_passwd_dlg));

    /*
       Reset variables.
    */
    t_g_ctrl.i2_date_idx           = 0;
    t_g_ctrl.ui2_date_num          = 0;
    t_g_ctrl.ui2_events_crnt_page  = 0;
    t_g_ctrl.ui2_events_prev_page  = 0;
    t_g_ctrl.ui2_events_next_page  = 0;
    t_g_ctrl.b_svc_signal_locked   = FALSE;
    t_g_ctrl.b_svc_signal_loss     = FALSE;
    t_g_ctrl.b_svc_input_blocked   = FALSE;
    t_g_ctrl.b_svc_event_blocked   = FALSE;
    t_g_ctrl.b_svc_channel_blocked = FALSE;
    t_g_ctrl.b_svc_scrambled       = FALSE;
    t_g_ctrl.b_svc_hidden_channel  = FALSE;
    t_g_ctrl.b_retrieving          = FALSE;

    /*
       Hide description frame and reset data within the frame.
    */
    RET_ON_ERR (_epg_ctrl_desc_hide_frame ());

    /*
       Hide password frame and reset data within the frame.
    */
    RET_ON_ERR (_epg_ctrl_passwd_hide_frame (FALSE));

    /*
       Reset text widgets.
    */
    RET_ON_ERR (epg_view_time_txt_set_text (w2s_g_null_str));
    RET_ON_ERR (epg_view_prg_txt_set_text (w2s_g_null_str));
    RET_ON_ERR (epg_view_video_txt_set_text (w2s_g_null_str));

    /*
       Clean-up program list.
    */
    RET_ON_ERR (_epg_ctrl_prg_lst_clean_elems (FALSE));

    /*
       Disable control keys of program list.
    */
    RET_ON_ERR (epg_view_prg_lst_enable_control_key (FALSE));

    /*
       Reset channel list.
    */
    RET_ON_ERR (epg_view_chn_lst_reset (FALSE));

    /*
       Reset channel text.
    */
    RET_ON_ERR (epg_view_chn_txt_set_text (w2s_g_null_str));

#ifdef APP_EPG_DCI_SUPPORT

    /*
       Reset dci info.
    */
    RET_ON_ERR (_epg_ctrl_dci_reset (FALSE));

#endif /* APP_EPG_DCI_SUPPORT */

    /*
        Reset current channel id.
    */
    t_g_ctrl.ui4_crnt_channel_id = INVALID_CHANNEL_ID;

#ifndef APP_NO_COLOR_KEY

    /*
       Reset help list.
    */
    RET_ON_ERR (_epg_ctrl_help_lst_reset (FALSE));

#endif /* APP_NO_COLOR_KEY */

    /* Do not update blue mute if TV is going to off: CR[215470] */
    if (a_am_is_power_on ())
    {
        /* Update blue mute. */
        RET_ON_ERR (a_cfg_av_update (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE)));
    }

    /* Clear image cache which used to improve Animation performance */
    c_wgl_img_cache_flush();

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_app_resume
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
static INT32 _epg_ctrl_app_resume (VOID)
{
    EPG_CONFIG_T   t_config;

    c_memset(&t_config, 0, sizeof(EPG_CONFIG_T));

    /* Clear image cache which used to improve Animation performance */
    c_wgl_img_cache_flush();

    /* Get EPG background configuration */
    epg_cfg_get_config_data(&t_config);

    /* Adjust background by configuration data */
    epg_view_adjust_background_by_config(&t_config);
        
    /* Disable blue mute without overwrite ACFG. */
    epg_svc_disable_blue_mute();

    /* Disable audio port if AV is mute. */
    if (epg_cfg_is_av_mute())
    {
        epg_util_set_sound_out_port(FALSE);
    }

#ifndef APP_EPG_FULL_VIDEO

    /* Blank video. */
    EPG_LOG_ON_FAIL (epg_svc_blank_video (TRUE));

    /* Force disable video before show EPG main frame. */
    EPG_LOG_ON_FAIL (epg_svc_enable_default_video_plane_mode(FALSE));

#endif /* APP_EPG_FULL_VIDEO */

    /*
       Set focus to program list.
    */
    RET_ON_ERR (epg_view_set_focus_widget (EPG_FOCUS_WIDGET_PRG_LST));

    /*
       Reset retrieving text.
    */
    RET_ON_ERR (epg_view_retrieve_txt_set_text (w2s_g_null_str));

#ifndef APP_NO_COLOR_KEY

    /* Reset help. */
    RET_ON_ERR (_epg_ctrl_help_lst_reset (FALSE));

#endif /* APP_NO_COLOR_KEY */

#ifdef APP_EPG_THEME_SEARCH

    /* Update help for theme search. */
    RET_ON_ERR (_epg_ctrl_help_lst_update_dvb_help (FALSE));

#endif /* APP_EPG_THEME_SEARCH */

    /*
       Update broadcast service.
    */
    RET_ON_ERR (_epg_ctrl_cfg_brdcst_svc_updated ());

    /*
       Show main frame.
    */
    RET_ON_ERR (epg_view_main_frm_show ());

#ifndef APP_EPG_FULL_VIDEO

    /* Force enable video after show EPG main frame. */
    EPG_LOG_ON_FAIL (epg_svc_enable_default_video_plane_mode(TRUE));

#endif /* APP_EPG_FULL_VIDEO */

    /*
       Display "Input lock" if needed.
    */
    if (epg_svc_is_tv_block ())
    {
        /* Display "input locked" message. */
        RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_INPUT_LOCKED)));

        /* Turn on input-blocked flag. */
        t_g_ctrl.b_svc_input_blocked = TRUE;
    }

    /*
       Disable control keys of program list.
    */
    RET_ON_ERR (epg_view_prg_lst_enable_control_key (FALSE));

    /*
       Start clock timer.
    */
    RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_clock,
                                 TIMER_DELAY_CLOCK,
                                 X_TIMER_FLAG_REPEAT));

    /*
       Start auto-pause timer.
    */
    RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_pause,
                                 TIMER_DELAY_PAUSE,
                                 X_TIMER_FLAG_ONCE));

    /*
       Turn on auto-pause flag.
    */
    t_g_ctrl.b_app_auto_pause = TRUE;


    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_btn_handler
 *
 * Description: The function handles the condition when a button is pressed.
 *
 * Inputs:  ui4_key_code           Key code.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_btn_handler (UINT32    ui4_key_code)
{
    BOOL          b_reset_pause_timer;

    b_reset_pause_timer = TRUE;

    switch (ui4_key_code)
    {
        case BTN_PRG_UP:
        case BTN_PRG_DOWN:
        {
            UINT16    ui2_num_recs;

            /* Get the number of records of SVL. */
            RET_ON_ERR (epg_svl_get_num_recs (& ui2_num_recs));

            if (ui2_num_recs > 1) /* The number of records is greater than 1. */
            {
                if (ui4_key_code == BTN_PRG_UP) /* Channel up. */
                {
                    /* Select next service. */
                    RET_ON_ERR (_epg_ctrl_svc_select (SURF_MODE_NEXT));
                }
                else /* Channel down. */
                {
                    /* Select previous service. */
                    RET_ON_ERR (_epg_ctrl_svc_select (SURF_MODE_PREV));
                }

                if (t_g_ctrl.b_btn_held) /* button is being held. */
                {
                    /* Turn on flag indicating channel button is being held */
                    t_g_ctrl.b_btn_chn_held = TRUE;
                }
            }
        }
        break;

        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
        {
            UINT16    ui2_num_recs;

            /* Get the number of records of SVL. */
            RET_ON_ERR (epg_svl_get_num_recs (& ui2_num_recs));

            if ((ui2_num_recs > 1) && /* The number of records is greater than 1. */
                (! t_g_ctrl.b_theme_search)) /* No theme search */
            {
                if (ui4_key_code == BTN_CURSOR_LEFT) /* Cursor left. */
                {
                    /* Select previous service. */
                    RET_ON_ERR (_epg_ctrl_svc_select (SURF_MODE_PREV));
                }
                else /* Cursor right. */
                {
                    /* Select next service. */
                    RET_ON_ERR (_epg_ctrl_svc_select (SURF_MODE_NEXT));
                }

                if (t_g_ctrl.b_btn_held) /* Button is being held. */
                {
                    /* Turn on flag indicating channel button is being held. */
                    t_g_ctrl.b_btn_chn_held = TRUE;
                }
            }
        }
        break;

        case BTN_CURSOR_UP:
        case BTN_CURSOR_DOWN:
        {
            if (t_g_ctrl.e_widget_focus_crnt == EPG_FOCUS_WIDGET_PASSWD_EDIT) /* Password edit is focused. */
            {
                /* Send a request to hide password frame  - important !!! */
                epg_app_send_msg (EPG_MSG_CTRL_REQ_HIDE_PASSWD_FRM, NULL, 0);
            }
            else if (t_g_ctrl.e_widget_focus_crnt == EPG_FOCUS_WIDGET_PRG_LST) /* Program list is focused */
            {
                if (t_g_ctrl.b_btn_held) /* Button is being held. */
                {
                    /* Turn on flag indicating program button is being held. */
                    t_g_ctrl.b_btn_prg_held = TRUE;
                }
            }
            else if (t_g_ctrl.e_widget_focus_crnt == EPG_FOCUS_WIDGET_SURF_LST) /* Surfing list is focused. */
            {
                UINT16    ui2_num_recs;

                /* Get the number of records of SVL. */
                RET_ON_ERR (epg_svl_get_num_recs (& ui2_num_recs));

                if (ui2_num_recs > 1) /* The number of records is greater than 1. */
                {
                    if (ui4_key_code == BTN_CURSOR_UP) /* Cursor up. */
                    {
                        /* Select previous service */
                        RET_ON_ERR (_epg_ctrl_svc_select (SURF_MODE_PREV));
                    }
                    else /* Cursor down */
                    {
                        /* Select next service */
                        RET_ON_ERR (_epg_ctrl_svc_select (SURF_MODE_NEXT));
                    }

                    if (t_g_ctrl.b_btn_held) /* Button is being held. */
                    {
                        /* Turn on flag indicating channel button is being held. */
                        t_g_ctrl.b_btn_chn_held = TRUE;
                    }
                }
            }
        }
        break;

        case BTN_SELECT:
        {
            /* Call select button handler. */
            RET_ON_ERR (_epg_ctrl_btn_select ());
        }
        break;

        case BTN_EXIT:
        case BTN_RETURN:
        {
            /* Call exit button handler. */
            RET_ON_ERR (_epg_ctrl_btn_exit ());
        }
        break;

#ifndef APP_NO_COLOR_KEY

        case BTN_RED:
        {
            /* Change to previous day. */
            RET_ON_ERR (_epg_ctrl_dt_change_date (TRUE));
        }
        break;

        case BTN_GREEN:
        {
            /* Change to next day. */
            RET_ON_ERR (_epg_ctrl_dt_change_date (FALSE));
        }
        break;

        case BTN_YELLOW:
        {
#ifndef APP_EPG_THEME_SEARCH
            /* Change to previous page of description. */
            RET_ON_ERR (_epg_ctrl_desc_change_page (EPG_DESC_PAGE_TYPE_PREV));
#else
            /* Toggle description pages. */
            RET_ON_ERR (_epg_ctrl_desc_change_page (EPG_DESC_PAGE_TYPE_TOGGLE));
#endif /* APP_EPG_THEME_SEARCH */
        }
        break;

        case BTN_BLUE:
        {
#ifndef APP_EPG_THEME_SEARCH
            /* Change to next page of description. */
            RET_ON_ERR (_epg_ctrl_desc_change_page (EPG_DESC_PAGE_TYPE_NEXT));
#else
            /* Show theme search. */
            RET_ON_ERR (_epg_ctrl_theme_search_show (TRUE));
#endif /* APP_EPG_THEME_SEARCH */
        }
        break;

#endif /* APP_NO_COLOR_KEY */

        case BTN_DIGIT_0: case BTN_DIGIT_1: case BTN_DIGIT_2: case BTN_DIGIT_3: case BTN_DIGIT_4:
        case BTN_DIGIT_5: case BTN_DIGIT_6: case BTN_DIGIT_7: case BTN_DIGIT_8: case BTN_DIGIT_9:
        {
            /* Call digit button handler. */
            RET_ON_ERR (_epg_ctrl_btn_digit ((CHAR) (ui4_key_code - BTN_DIGIT_0)));
        }
        break;

        case BTN_VOL_UP:
        case BTN_VOL_DOWN:
        case BTN_MUTE:
        {
			if (epg_cfg_is_av_mute() == FALSE)
			{
	            /* Call default key handler. */
	            a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*) ui4_key_code, NULL);
			}
        }
        break;
        case BTN_ADD_ERASE:
        {
            /* Call PVR related key handler. */
            RET_ON_ERR (_epg_ctrl_btn_pvr_keys (ui4_key_code));
        }
        break;

        default:
        {
            /* Don't reset auto-pause timer. */
            b_reset_pause_timer = FALSE;
        }
        break;
    }

    /* Update retrieving states if required. */
    if ((t_g_ctrl.b_btn_chn_held) && /* Channel button is being held. */
        (t_g_ctrl.b_retrieving))     /* Retrieving data. */
    {
        /* Turn off retrieving flag. */
        t_g_ctrl.b_retrieving = FALSE;

        /* Update retrieving state */
        RET_ON_ERR (_epg_ctrl_retrieve_update_state ());
    }

    if (b_reset_pause_timer)
    {
        /* Reset auto-pause timer. */
        RET_ON_ERR (_epg_ctrl_timer_reset_pause ());
    }

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_btn_digit
 *
 * Description: The function handles digit buttons.
 *
 * Inputs:  c_digit                The input digit.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_btn_digit (CHAR    c_digit)
{
    /* Password dialog is not focused. */
    if (t_g_ctrl.e_widget_focus_crnt != EPG_FOCUS_WIDGET_PASSWD_EDIT)
    {
        /* Check if password is correct to disable auto-pause function. */
        if ((t_g_ctrl.ui2_passwd_idx < EPG_PASSWD_DIGIT) &&
            (c_digit == ac_g_passwd [t_g_ctrl.ui2_passwd_idx])) /* Password is correct. */
        {
            /* Increase password index. */
            t_g_ctrl.ui2_passwd_idx ++;

            /* All passwords are matched. */
            if (t_g_ctrl.ui2_passwd_idx >= EPG_PASSWD_DIGIT)
            {
                /* Turn off auto-pause flag. */
                t_g_ctrl.b_app_auto_pause = FALSE;

                /* Reset password index. */
                t_g_ctrl.ui2_passwd_idx = 0;

                DBG_INFO (("<EPG> disable auto-pause function\n\r"));
            }
        }
        else /* Password is incorrect. */
        {
            /* Reset password index. */
            t_g_ctrl.ui2_passwd_idx = 0;
        }

#ifdef APP_EPG_DCI_SUPPORT

        /*
           Handle direct channel input.
        */
        if (t_g_ctrl.ui2_dci_idx >= EPG_DCI_MAX_DIGIT)
        {
            /* Reset dci index. */
            t_g_ctrl.ui2_dci_idx = 0;
        }

        /* Store digit */
        t_g_ctrl.ac_dci[t_g_ctrl.ui2_dci_idx ++] = c_digit;

        /* Call dci input handler. */
        RET_ON_ERR (_epg_ctrl_dci_input ());

#endif /* APP_EPG_DCI_SUPPORT */

    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_btn_select
 *
 * Description: The function handles the selection button.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_btn_select (VOID)
{
    UINT16        ui2_hlt_idx;
    UINT16        ui2_text_len;
    BOOL          b_exceed;
    BOOL          b_do_passwd_req;

#ifdef APP_EPG_THEME_SEARCH

    if (t_g_ctrl.b_theme_search) /* Theme search is active. */
    {
        /* Hide theme search. */
        RET_ON_ERR (_epg_ctrl_theme_search_hide (TRUE));

        if (! t_g_ctrl.b_svc_signal_loss)
        {
            /* Update program list. */
            RET_ON_ERR (_epg_ctrl_prg_lst_update (0, TRUE));
        }

        return 0;
    }

#endif /* APP_EPG_THEME_SEARCH */

    if (t_g_ctrl.b_passwd_show) /* Password frame is being shown. */
    {
        /* Get text length of password edit. */
        RET_ON_ERR (epg_view_passwd_edit_get_text_len (& ui2_text_len));

        /* Display incorrect password message if the length is not 0. */
        if (ui2_text_len > 0)
        {
            RET_ON_ERR (_epg_ctrl_passwd_display_msg (FALSE));
        }

        /* Hide password frame. */
        RET_ON_ERR (_epg_ctrl_passwd_hide_frame (TRUE));

        return  0;
    }

#ifdef APP_EPG_DCI_SUPPORT

    /* Direct channel input. */
    if ((t_g_ctrl.ui4_crnt_channel_id != t_g_ctrl.ui4_dci_channel_id) ||
        (t_g_ctrl.ui2_dci_idx > 0) ||
        (t_g_ctrl.b_dci_complete))
    {
        /* Reset dci info. */
        RET_ON_ERR (_epg_ctrl_dci_reset (TRUE));

        if (t_g_ctrl.ui4_crnt_channel_id != t_g_ctrl.ui4_dci_channel_id)
        {
            /* Save channel IDs. */
            a_util_cnfg_set_crnt_channel_id (t_g_ctrl.ui4_dci_channel_id);
            a_util_cnfg_set_last_channel_id (t_g_ctrl.ui4_crnt_channel_id);

            /* Select service. */
            RET_ON_ERR (_epg_ctrl_svc_select (SURF_MODE_THIS));
        }

        return  0;
    }

#endif /* APP_EPG_DCI_SUPPORT */

    b_exceed = FALSE;
    b_do_passwd_req = FALSE;

    if ((t_g_ctrl.b_svc_input_blocked) ||   /* Input blocked */
        (t_g_ctrl.b_svc_channel_blocked) || /* Channel blocked */
        (t_g_ctrl.b_svc_event_blocked))     /* Event blocked */
    {
        b_do_passwd_req = TRUE;
    }
    else /* Check if highlighted event is blocked. */
    {
        /* Get highlight index. */
        RET_ON_ERR (epg_view_prg_lst_get_hlt_idx (& ui2_hlt_idx));

        if ((ui2_hlt_idx != WGL_LB_NULL_INDEX) &&
            (ui2_hlt_idx < EPG_EVT_BUFFER_SIZE))
        {
            RET_ON_ERR (_epg_ctrl_check_rating (t_g_ctrl.ah_events[ui2_hlt_idx], & b_exceed));

            if (b_exceed) /* Exceed rating. */
            {
               b_do_passwd_req = TRUE;
            }
        }
    }

    if ((b_do_passwd_req) && /* Password digalog request. */
        (t_g_ctrl.e_widget_focus_crnt != EPG_FOCUS_WIDGET_PASSWD_EDIT)) /* Password edit is not currently focused. */
    {
        /* Show password frame. */
        RET_ON_ERR (_epg_ctrl_passwd_show_frame ());
    }
    else if (t_g_ctrl.ui2_desc_page_num > 1) /* Toggle pages of program descriptions. */
    {
        /* Toggle description pages. */
        RET_ON_ERR (_epg_ctrl_desc_change_page (EPG_DESC_PAGE_TYPE_TOGGLE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_btn_exit
 *
 * Description: The function handles EXIT button.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_btn_exit (VOID)
{
    BOOL          b_pause_epg = TRUE;

#ifdef APP_EPG_THEME_SEARCH

    if (t_g_ctrl.b_theme_search) /* Theme search is active */
    {
        /* Pause EPG. */
        RET_ON_ERR (epg_app_pause_req ());

        return 0;
    }

#endif /* #ifdef APP_EPG_THEME_SEARCH */

#ifndef APP_EPG_FORCE_EXIT

    if (epg_cli_is_running ()) /* CLI command is running. */
    {
        /* Stop cli command. */
        epg_cli_stop ();

        return  0;
    }

    if (t_g_ctrl.b_passwd_show) /* Password frame is being shown. */
    {
        /* Hide password frame. */
        RET_ON_ERR (_epg_ctrl_passwd_hide_frame (TRUE));

        return  0;
    }

#ifdef APP_EPG_DCI_SUPPORT

    /* Direct channel input. */
    if ((t_g_ctrl.ui4_crnt_channel_id != t_g_ctrl.ui4_dci_channel_id) ||
        (t_g_ctrl.ui2_dci_idx > 0) ||
        (t_g_ctrl.b_dci_complete))
    {
        /* Reset dci info. */
        RET_ON_ERR (_epg_ctrl_dci_reset (TRUE));

        /* Set dci channel id to current channel id. */
        t_g_ctrl.ui4_dci_channel_id = t_g_ctrl.ui4_crnt_channel_id;

        /* Update channel list only. */
        RET_ON_ERR (_epg_ctrl_chn_update (FALSE));

        return  0;
    }

#endif /* APP_EPG_DCI_SUPPORT */

#if 0
    b_pause_epg = FALSE;

    UINT16        ui2_hlt_idx;

    if ((! epg_svl_is_found ()) ||               /* SVL is not found. */
        ((t_g_ctrl.ui2_events_crnt_page == 0) && /* There is no event in current page. */
         (t_g_ctrl.ui2_events_prev_page == 0)))  /* There is no event in previous page. */
    {
        b_pause_epg = TRUE;
    }
    else
    {
        /* Get highlighted index. */
        RET_ON_ERR (epg_view_prg_lst_get_hlt_idx (& ui2_hlt_idx));

        if (ui2_hlt_idx != WGL_LB_NULL_INDEX)
        {
            if (_epg_ctrl_evt_is_crnt (t_g_ctrl.ah_events[ui2_hlt_idx])) /* Current event. */
            {
                b_pause_epg = TRUE;
            }
            else /* Not current event. */
            {
                if ((ui2_hlt_idx == 0) &&
                    (t_g_ctrl.ui2_events_prev_page == 0)) /* Event in future. */
                {
                    b_pause_epg = TRUE;
                }
            }
        }
    }
#endif /* #if 0 */

#endif /* APP_EPG_FORCE_EXIT */

    if (b_pause_epg) /* Pause EPG. */
    {
        RET_ON_ERR (epg_app_pause_req ());
    }
    else /* Jump to first program */
    {
        /* Update program list. */
        RET_ON_ERR (_epg_ctrl_prg_lst_update (0, TRUE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_btn_pvr_keys
 *
 * Description: The function handles PVR related buttons.
 *
 * Inputs:  ui4_key_code                The input keycode.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_btn_pvr_keys (UINT32    ui4_key_code)
{
#ifdef APP_NAV_REC_PVR_SCH_SUPPORT

    EVENT_REMINDER_T    t_reminder;
    INT32               i4_rc;
    UINT16              ui2_hlt;
    SIZE_T              z_info_size = 0;
    TIME_T              t_time_start;
    TIME_T              t_time_duration;
    HANDLE_T            h_event = NULL_HANDLE;
    UTF16_T             s_event_title[MAX_REMINDER_EVENT_TITLE_LEN];
    CHAR*               ps_title = NULL;

    do
    {
        /* Only process PVR keys when focus on program list */
        if (t_g_ctrl.e_widget_focus_crnt != EPG_FOCUS_WIDGET_PRG_LST)
        {
            break;
        }

        /* Get highlight index of program list */
        i4_rc = epg_view_prg_lst_get_hlt_idx (& ui2_hlt);
        if (EPGR_OK != i4_rc)
        {
            break;
        }

        /* Check highlight index validation */
        if ((ui2_hlt == WGL_LB_NULL_INDEX)   || /* no element highlighted */
            (ui2_hlt >= EPG_EVT_BUFFER_SIZE)) /* something wrong? */
        {
            break;
        }

        h_event = t_g_ctrl.ah_events[ui2_hlt];

        /* Check highlight event handle validation */
        if ((h_event == NULL_HANDLE) ||
            (FALSE == t_g_ctrl.ab_events_cb[ui2_hlt]))
        {
            break;
        }

        /* Get event start time (UTC time) */
        i4_rc = epg_evt_get_start_time (h_event, & t_time_start);
        if (EPGR_OK != i4_rc)
        {
            break;
        }

        /* Get event duration */
        i4_rc = epg_evt_get_duration (h_event, & t_time_duration);
        if (EPGR_OK != i4_rc)
        {
            break;
        }

        /* Get event title length */
        i4_rc = epg_evt_get_title_len (h_event, & z_info_size);
        if (EPGR_OK != i4_rc)
        {
            break;
        }

        /* Event title not found */
        if (z_info_size == 0)
        {
            break;
        }

        /* allocate UTF8 buffer for event title */
        ps_title = (CHAR*) c_mem_alloc (z_info_size * sizeof(CHAR));

        if (ps_title == NULL)
        {
            break;
        }

        /* get event title */
        i4_rc = epg_evt_get_title (h_event, z_info_size, ps_title);

        if (EVCTXR_OK != i4_rc)
        {
            break;
        }

        /* Trim spaces */
        epg_str_trim (ps_title);

        epg_str_ps_to_w2s (ps_title,
                           s_event_title,
                           MAX_REMINDER_EVENT_TITLE_LEN);
        s_event_title[MAX_REMINDER_EVENT_TITLE_LEN-1] = (UTF16_T)0;

        /* Reset reminder data */
        c_memset(&t_reminder, 0, sizeof(EVENT_REMINDER_T));

        /* Set current channel id */
        t_reminder.ui4_channel_id = t_g_ctrl.ui4_crnt_channel_id;

        /* Set event title */
        c_uc_w2s_strncpy(t_reminder.s_event_title, s_event_title, MAX_REMINDER_EVENT_TITLE_LEN -1);

        /* Set event time info */    
        t_reminder.ui4_start_time = (UINT32)t_time_start;
        t_reminder.ui4_duration = (UINT32)t_time_duration;

        /* Set reminder type and mode */    
        t_reminder.e_rmd_mode=  APP_CFG_RMDR_MODE_RMDR;
        t_reminder.ui1_day = APP_CFG_RMDR_WEEK_ONCE;

        /* Exit EPG and resume NAV reminder component */
    	nav_reminder_view_add_sch_by_reminder(&t_reminder);
        
    } while(FALSE);

    /* Free resource */
    if (NULL == ps_title)
    {
        c_mem_free(ps_title);
    }
    
#endif /* APP_NAV_REC_PVR_SCH_SUPPORT */
    
    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_cfg_language_updated
 *
 * Description: The function handles the condition when language is updated.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_cfg_language_updated (VOID)
{
    /* Update text of password text widget. */
    RET_ON_ERR (epg_view_passwd_txt_set_text (EPG_MLM (MLM_EPG_KEY_MSG_PASSWD)));
#ifdef APP_EPG_FULL_VIDEO
    RET_ON_ERR (epg_view_passwd_alarm_txt_set_text (EPG_MLM (MLM_EPG_KEY_MSG_PASSWD_ALARM)));
#endif

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_cfg_vchip_updated
 *
 * Description: The function handles the condition when V-chip is updated.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_cfg_vchip_updated (VOID)
{
    if ((! t_g_ctrl.b_svc_channel_blocked) && /* Channel is not blocked. */
        (! t_g_ctrl.b_svc_input_blocked))     /* Input is not blocked. */
    {
        /* Unblock service. */
        RET_ON_ERR (epg_svc_unblock ());
    }

    /* Update events. */
    RET_ON_ERR (_epg_ctrl_evt_update ());

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_cfg_brdcst_svc_updated
 *
 * Description: The function handles the condition when broadcast service is
 *              updated.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_cfg_brdcst_svc_updated (VOID)
{
    if (t_g_ctrl.b_passwd_show) /* Password frame is being shown. */
    {
        /* Hide password frame. */
        RET_ON_ERR (_epg_ctrl_passwd_hide_frame (TRUE));
    }

    /* Clean video message. */
    RET_ON_ERR (_epg_ctrl_video_txt_msg (NULL));

    /* Update retrieving state. */
    RET_ON_ERR (_epg_ctrl_retrieve_update_state ());

    /* Reset current channel id. */
    t_g_ctrl.ui4_crnt_channel_id = INVALID_CHANNEL_ID;

    /* Udpate svl. */
    RET_ON_ERR (_epg_ctrl_svl_update (0xFFFF));

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_chn_update
 *
 * Description: This function updates channel information in channel list (
 &              and channel text).
 *
 * Inputs:  b_update_chn_txt       Update channel text or not.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_chn_update (BOOL    b_update_chn_txt)
{
    INT32       i4_rc;
    CHAR        s_channel_info[EPG_CHN_INFO_MAX_LEN] = {0};
    UTF16_T     w2s_channel_info[EPG_CHN_INFO_MAX_LEN];
    UINT32      ui4_channel_id;
    UINT32      ui4_crnt_channel_id;
    UINT16      ui2_num_recs;
    SVL_REC_T   t_svl_rec;

    /* Get current channel id. */
    ui4_channel_id      = a_util_cnfg_get_crnt_channel_id ();
    ui4_crnt_channel_id = ui4_channel_id;

    if ((epg_svl_is_found ()) &&                /* SVL is found. */
        (ui4_channel_id != INVALID_CHANNEL_ID)) /* Channel id is valid. */
    {
        /* Get the record of current channel. */
        RET_ON_ERR (epg_svl_get_rec_by_surf_mode (SURF_MODE_THIS,
                                                  & ui4_channel_id,
                                                  & t_svl_rec));

        /* Check channel type. */
        if (SB_ATSC_IS_ONE_PART_CHANNEL_ID (ui4_channel_id)) /* One-part */
        {
            /* Discard separator and minor number. */
            c_sprintf (s_channel_info,
                       "%d  %s",
                       SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id),
                       t_svl_rec.uheader.t_rec_hdr.ac_name);
        }
        else /* Two-part */
        {
            /* Display "major-minor service_name". */
            c_sprintf (s_channel_info,
                       "%d%c%d  %s",
                       SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id),
                       MAJOR_MINOR_SEPARATOR,
                       SB_ATSC_GET_MINOR_CHANNEL_NUM (ui4_channel_id),
                       t_svl_rec.uheader.t_rec_hdr.ac_name);
        }

        /* UTF8 to UTF16 */
        i4_rc = epg_str_ps_to_w2s (s_channel_info,
                                   w2s_channel_info,
                                   EPG_CHN_INFO_MAX_LEN);

        if (i4_rc == UCR_OK)
        {
            /* Set text to current channel of channel list. */
            RET_ON_ERR (epg_view_chn_lst_set_text (EPG_CHN_TYPE_CRNT, w2s_channel_info));

            if (b_update_chn_txt) /* Also update channel text. */
            {
                /* Set text to channel text. */
                RET_ON_ERR (epg_view_chn_txt_set_text (w2s_channel_info));
            }
        }
        else
        {
            DBG_ERROR (("<EPG> ERR: UTF8_T to UTF16_T failed = %d\n\r", i4_rc));

            /* Reset current channel of channel listing. */
            RET_ON_ERR (epg_view_chn_lst_set_text (EPG_CHN_TYPE_CRNT, w2s_g_null_str));

            if (b_update_chn_txt) /* Also update channel text. */
            {
                /* Reset channel text. */
                RET_ON_ERR (epg_view_chn_txt_set_text (w2s_g_null_str));
            }
        }
    }
    else /* SVL is not found. */
    {
        /* Reset current channel of channel listing. */
        RET_ON_ERR (epg_view_chn_lst_set_text (EPG_CHN_TYPE_CRNT, w2s_g_null_str));

        if (b_update_chn_txt) /* Also update channel text. */
        {
            /* Reset channel text. */
            RET_ON_ERR (epg_view_chn_txt_set_text (w2s_g_null_str));
        }
    }

    /* Get the number of records. */
    i4_rc = epg_svl_get_num_recs (& ui2_num_recs);

    /* The number of records is greater than 1 => Update previous/next channel infomation. */
    if ((i4_rc == SVLR_OK) && (ui2_num_recs > 1))
    {
        /*
           Update previous channel info.
        */
        RET_ON_ERR (epg_svl_get_rec_by_surf_mode (SURF_MODE_PREV,
                                                  & ui4_channel_id,
                                                  & t_svl_rec));

        /* Check channel type. */
        if (SB_ATSC_IS_ONE_PART_CHANNEL_ID (ui4_channel_id)) /* One-part */
        {
            c_sprintf (s_channel_info,
                       "%d",
                       SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id));
        }
        else /* Two-part */
        {
            c_sprintf (s_channel_info,
                       "%d%c%d",
                       SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id),
                       MAJOR_MINOR_SEPARATOR,
                       SB_ATSC_GET_MINOR_CHANNEL_NUM (ui4_channel_id));
        }

        /* UTF8 to UTF16 */
        i4_rc = epg_str_ps_to_w2s (s_channel_info,
                                   w2s_channel_info,
                                   EPG_CHN_INFO_MAX_LEN);

        if (i4_rc == UCR_OK)
        {
            /* Set text to previous channel column of channel list. */
            RET_ON_ERR (epg_view_chn_lst_set_text (EPG_CHN_TYPE_PREV, w2s_channel_info));
        }
        else
        {
            DBG_ERROR (("<EPG> ERR: UTF8_T to UTF16_T failed = %d\n\r", i4_rc));

            /* Reset text of previous channel column of channel list. */
            RET_ON_ERR (epg_view_chn_lst_set_text (EPG_CHN_TYPE_PREV, w2s_g_null_str));
        }

        /*
           Update next channel info.
        */
        ui4_channel_id = ui4_crnt_channel_id;

        /* Get the record of next channel. */
        RET_ON_ERR (epg_svl_get_rec_by_surf_mode (SURF_MODE_NEXT,
                                                  & ui4_channel_id,
                                                  & t_svl_rec));

        /* Check channel type. */
        if (SB_ATSC_IS_ONE_PART_CHANNEL_ID (ui4_channel_id)) /* One-part */
        {
            c_sprintf (s_channel_info,
                       "%d",
                       SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id));
        }
        else /* Two-part */
        {
            c_sprintf (s_channel_info,
                       "%d%c%d",
                       SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id),
                       MAJOR_MINOR_SEPARATOR,
                       SB_ATSC_GET_MINOR_CHANNEL_NUM (ui4_channel_id));
        }

        /* UTF8 to UTF16 */
        i4_rc = epg_str_ps_to_w2s (s_channel_info,
                                   w2s_channel_info,
                                   EPG_CHN_INFO_MAX_LEN);

        if (i4_rc == UCR_OK)
        {
            /* Set text to next channel column of channel list. */
            RET_ON_ERR (epg_view_chn_lst_set_text (EPG_CHN_TYPE_NEXT, w2s_channel_info));
        }
        else
        {
            DBG_ERROR (("<EPG> ERR: UTF8_T to UTF16_T failed = %d\n\r", i4_rc));

            /* Reset text of next channel column of channel list. */
            RET_ON_ERR (epg_view_chn_lst_set_text (EPG_CHN_TYPE_NEXT, w2s_g_null_str));
        }
    }
    else /* The number of records is less or equals 1. */
    {
        /* Reset text of previous channel of channel list. */
        RET_ON_ERR (epg_view_chn_lst_set_text (EPG_CHN_TYPE_PREV, w2s_g_null_str));

        /* Reset text of next channel of channel list. */
        RET_ON_ERR (epg_view_chn_lst_set_text (EPG_CHN_TYPE_NEXT, w2s_g_null_str));
    }

    /* Repaint channel list. */
    RET_ON_ERR (epg_view_chn_lst_repaint ());

    if (b_update_chn_txt) /* Also update channel text. */
    {
       /* Repaint channel text. */
       RET_ON_ERR (epg_view_chn_txt_repaint ());
    }

    return  0;
}

#ifdef APP_EPG_DCI_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_dci_get_digit
 *
 * Description: This function returns a digit given a number and an offset.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: The digit.
 ----------------------------------------------------------------------------*/
static CHAR _epg_ctrl_dci_get_digit (UINT16    ui2_number,
                                     UINT16    ui2_offset)
{
    UINT16    ui2_temp;
    UINT16    ui2_len;
    UINT16    ui2_i;
    CHAR      c_digit;

    /* calculate the length of number */
    ui2_temp = ui2_number;
    ui2_len  = 0;
    c_digit  = 0;

    do
    {
        ui2_temp /= 10;
        ui2_len ++;

    } while (ui2_temp > 0);

    /* check if the length of input number is too short to get the requested digit */
    if (ui2_len < (ui2_offset+1)) /* too short */
    {
        c_digit = -1;
    }
    else /* long enough */
    {
        /* get requested digit */
        for (ui2_i = 0; ui2_i < (ui2_len-ui2_offset); ui2_i ++)
        {
            c_digit = ui2_number % 10;
            ui2_number = ui2_number / 10;
        }
    }

    return  c_digit;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_dci_reset
 *
 * Description: This function resets the direct channel input, including text and
 *              input digits.
 *
 * Inputs:  b_repaint              Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_dci_reset (BOOL    b_repaint)
{
    /* reset dci variables */
    t_g_ctrl.ui2_dci_idx = 0;
    t_g_ctrl.b_dci_complete = FALSE;

    /* stop dci timer */
    RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_dci));

    /* reset dci text */
    RET_ON_ERR (epg_view_dci_hts_clear ());

    /* repaint dci text */
    if (b_repaint)
    {
        RET_ON_ERR (epg_view_dci_hts_repaint ());
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_dci_update_text
 *
 * Description: This function updates the text of direct channel input.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_dci_update_text (UINT32    ui4_channel_id)
{
    UINT16      ui2_i;
    CHAR        s_dci[EPG_CHN_NO_MAX_LEN] = {0};
    CHAR        s_dummy[EPG_CHN_INFO_MAX_LEN] = {0};
    UTF16_T     w2s_dci[EPG_CHN_NO_MAX_LEN];
    UTF16_T     w2s_dummy[EPG_CHN_INFO_MAX_LEN];
    UINT16      ui2_major;
    UINT16      ui2_minor;
    UINT16      ui2_major_len;
    UINT16      ui2_minor_len;
    UINT16      ui2_dci_len;
    SVL_REC_T   t_svl_rec;

    /* get major and minor numbers */
    ui2_major = SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id);
    ui2_minor = SB_ATSC_GET_MINOR_CHANNEL_NUM (ui4_channel_id);

    /* calculate the length of major number */
    ui2_major_len = 0;

    do
    {
        ui2_major /= 10;
        ui2_major_len ++;

    } while (ui2_major > 0);

    /* calculae the length of minor number */
    ui2_minor_len = 0;

    if (! SB_ATSC_IS_ONE_PART_CHANNEL_ID (ui4_channel_id)) /* two-part */
    {
        do
        {
            ui2_minor /= 10;
            ui2_minor_len ++;

        } while (ui2_minor > 0);
    }

    /* format dci string */
    ui2_dci_len = 0;

    for (ui2_i = 0; ui2_i < t_g_ctrl.ui2_dci_idx; ui2_i ++)
    {
        c_sprintf (s_dci + ui2_dci_len, "%d", t_g_ctrl.ac_dci[ui2_i]);
        ui2_dci_len ++;

        /* cascade separator */
        if ((ui2_i == (ui2_major_len - 1)) &&
            (! SB_ATSC_IS_ONE_PART_CHANNEL_ID (ui4_channel_id))) /* two-part */
        {
            c_sprintf (s_dci + ui2_dci_len, "%c", MAJOR_MINOR_SEPARATOR);
            ui2_dci_len ++;
        }
    }

    /* put NULL-terminated char */
    s_dci [ui2_dci_len] = 0;

    /* UTF8_T to UTF16_T */
    RET_ON_ERR (epg_str_ps_to_w2s (s_dci,
                                   w2s_dci,
                                   EPG_CHN_NO_MAX_LEN));

    /* get current svl record */
    RET_ON_ERR (epg_svl_get_rec_by_surf_mode (SURF_MODE_THIS,
                                              & ui4_channel_id,
                                              & t_svl_rec));

    /* format dummy text */
    if (SB_ATSC_IS_ONE_PART_CHANNEL_ID (ui4_channel_id)) /* one-part */
    {
        /* discard separator and minor number */
        c_sprintf (s_dummy,
                   "%d  %s",
                   SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id),
                   t_svl_rec.uheader.t_rec_hdr.ac_name);
    }
    else /* two-part */
    {
        /* display "major-minor service_name" */
        c_sprintf (s_dummy,
                   "%d%c%d  %s",
                   SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id),
                   MAJOR_MINOR_SEPARATOR,
                   SB_ATSC_GET_MINOR_CHANNEL_NUM (ui4_channel_id),
                   t_svl_rec.uheader.t_rec_hdr.ac_name);
    }

    /* UTF8_T to UTF16_T */
    RET_ON_ERR (epg_str_ps_to_w2s (s_dummy,
                                   w2s_dummy,
                                   EPG_CHN_INFO_MAX_LEN));

    /* set text to dci hyper text */
    RET_ON_ERR (epg_view_dci_hts_set_text (w2s_dci, w2s_dummy + ui2_dci_len));

    /* repaint dci text */
    RET_ON_ERR (epg_view_dci_hts_repaint ());

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_dci_is_match
 *
 * Description: This function checks if a given channel id matches direct
 *              channel input (DCI).
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE       Matched.
 *          FALSE      Not matched.
 ----------------------------------------------------------------------------*/
static BOOL _epg_ctrl_dci_is_match (UINT32    ui4_channel_id)
{
    UINT16    ui2_i;
    UINT16    ui2_major;
    UINT16    ui2_minor;
    UINT16    ui2_major_len;
    CHAR      c_dci, c_code;
    BOOL      b_match;

    /* get major number */
    ui2_major = SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id);

    /* calculate the length of major number */
    ui2_major_len = 0;

    do
    {
        ui2_major /= 10;
        ui2_major_len ++;

    } while (ui2_major > 0);

    /* re-get major and minor numbers */
    ui2_major = SB_ATSC_GET_MAJOR_CHANNEL_NUM (ui4_channel_id);
    ui2_minor = SB_ATSC_GET_MINOR_CHANNEL_NUM (ui4_channel_id);

    b_match = FALSE;

    for (ui2_i = 0; ui2_i < t_g_ctrl.ui2_dci_idx; ui2_i ++)
    {
        /* get dci digit */
        c_dci = t_g_ctrl.ac_dci[ui2_i];

        if (ui2_i < ui2_major_len) /* compare digit with major number */
        {
            c_code = _epg_ctrl_dci_get_digit (ui2_major, ui2_i);
        }
        else
        {
            if (SB_ATSC_IS_ONE_PART_CHANNEL_ID (ui4_channel_id)) /* one-part */
            {
                break;
            }
            else /* two-part => compare digit with minor number */
            {
                c_code = _epg_ctrl_dci_get_digit (ui2_minor, ui2_i - ui2_major_len);
            }
        }

        if (c_dci == c_code)
        {
            if (ui2_i == (t_g_ctrl.ui2_dci_idx - 1))
            {
                b_match = TRUE; /* matched */
            }
        }
        else /* not matched */
        {
            break;
        }
    }

    return  b_match;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_dci_input
 *
 * Description: This function handles direct channel input.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_dci_input (VOID)
{
    INT32               i4_rc;
    UINT16              ui2_i;
    UINT16              ui2_num_recs;
    UINT32              ui4_channel_id;
    SVL_REC_T           t_svl_rec;
    BOOL                b_match;

    b_match        = FALSE;
    ui4_channel_id = a_util_cnfg_get_crnt_channel_id ();

    /* get the number of records */
    RET_ON_ERR (epg_svl_get_num_recs (& ui2_num_recs));

    if (ui2_num_recs > 0)
    {
        /* get first record */
        RET_ON_ERR (epg_svl_iterate_rec (ui4_channel_id,
                                         SVL_CHANNEL_SMALLEST,
                                         & t_svl_rec));

        /* iterate all the records */
        for (ui2_i = 0; ui2_i < ui2_num_recs; ui2_i ++)
        {
            ui4_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;

            if (_epg_ctrl_dci_is_match (ui4_channel_id))
            {
                if (ui4_channel_id != t_g_ctrl.ui4_dci_channel_id)
                {
                    /* reset dci text */
                    RET_ON_ERR (epg_view_dci_hts_clear ());

                    /* repaint dci text */
                    RET_ON_ERR (epg_view_dci_hts_repaint ());
                }

                /* temporarily set dci to current channel id */
                a_util_cnfg_set_crnt_channel_id (ui4_channel_id);

                /* update channel list only */
                RET_ON_ERR (_epg_ctrl_chn_update (FALSE));

                /* restore current channel id */
                a_util_cnfg_set_crnt_channel_id (t_g_ctrl.ui4_crnt_channel_id);

                /* update dci text */
                RET_ON_ERR (_epg_ctrl_dci_update_text (ui4_channel_id));

                t_g_ctrl.ui4_dci_channel_id = ui4_channel_id; /* store channel id */

                b_match = TRUE;

                break;
            }

            /* get next record */
            i4_rc = epg_svl_iterate_rec (ui4_channel_id,
                                         SVL_CHANNEL_PLUS,
                                         & t_svl_rec);

            if ((i4_rc == SVLR_END_OF_ITERATION) || (i4_rc == SVLR_MODIFIED))
            {
                break;
            }
            else if (i4_rc != SVLR_OK)
            {
                DBG_ERROR (("<EPG> ERR: iterate record failed = %d\n\r", i4_rc));

                break;
            }
        }

        if (! b_match) /* no record matches direct channel input */
        {
            /* reset dci info */
            RET_ON_ERR (_epg_ctrl_dci_reset (TRUE));
        }

        if ((b_match) ||
            (t_g_ctrl.ui4_crnt_channel_id != t_g_ctrl.ui4_dci_channel_id))

        {
            /* restart dci timer */
            RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_dci,
                                         TIMER_DELAY_DCI,
                                         X_TIMER_FLAG_ONCE));
        }
    }

    return  0;
}

#endif /* APP_EPG_DCI_SUPPORT */

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_desc_change_page
 *
 * Description: The function changes pages of the program descriptions.
 *
 * Inputs:  e_type                 Paging type.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_desc_change_page (EPG_DESC_PAGE_TYPE_T    e_type)
{
    switch (e_type)
    {
        case EPG_DESC_PAGE_TYPE_TOGGLE: /* toggle pages circularly */
        {
            /* Go to first page. */
            if (t_g_ctrl.ui2_desc_page_idx == (UINT16)(t_g_ctrl.ui2_desc_page_num-1))
            {
                t_g_ctrl.ui2_desc_page_idx = 0;

                /* Update paging help. */
                RET_ON_ERR (_epg_ctrl_help_lst_update_page_help (FALSE));

                /* Display first page. */
                RET_ON_ERR (epg_view_desc_txt_first_page ());
            }
            else /* Page down. */
            {
                t_g_ctrl.ui2_desc_page_idx ++;

                /* Update paging help. */
                RET_ON_ERR (_epg_ctrl_help_lst_update_page_help (FALSE));

                /* Page down. */
                RET_ON_ERR (epg_view_desc_txt_page_down ());
            }
        }
        break;

        case EPG_DESC_PAGE_TYPE_PREV:   /* change to previous page */
        {
            if (t_g_ctrl.ui2_desc_page_idx > 0)
            {
                t_g_ctrl.ui2_desc_page_idx --;

                DBG_INFO (("<EPG> description page index = %d\n\r", t_g_ctrl.ui2_desc_page_idx));

                /* update page help */
                RET_ON_ERR (_epg_ctrl_help_lst_update_page_help (FALSE));

                /* page up description text */
                RET_ON_ERR (epg_view_desc_txt_page_up ());
            }
        }
        break;

        case EPG_DESC_PAGE_TYPE_NEXT:   /* change to next page */
        {
            if (t_g_ctrl.ui2_desc_page_idx < (UINT16)(t_g_ctrl.ui2_desc_page_num-1))
            {
                t_g_ctrl.ui2_desc_page_idx ++;

                DBG_INFO (("<EPG> description page index = %d\n\r", t_g_ctrl.ui2_desc_page_idx));

                /* update page help */
                RET_ON_ERR (_epg_ctrl_help_lst_update_page_help (FALSE));

                /* page down description text */
                RET_ON_ERR (epg_view_desc_txt_page_down ());
            }
        }
        break;

        default:
            break;
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_desc_hide_frame
 *
 * Description: The function hides description frame and resets data within
 *              description frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_desc_hide_frame (VOID)
{
    if (t_g_ctrl.b_desc_show)
    {
        /* reset description list box */
        RET_ON_ERR (epg_view_desc_lst_reset (FALSE));

        /* reset description text */
        RET_ON_ERR (epg_view_desc_txt_set_text (w2s_g_null_str));

        /* reset page index text */
        RET_ON_ERR (epg_view_page_txt_set_text (w2s_g_null_str));

        /* reset description page data */
        t_g_ctrl.ui2_desc_page_num = 0;
        t_g_ctrl.ui2_desc_page_idx = 0;

        /* hide description frame */
        RET_ON_ERR (epg_view_desc_frm_hide ());

        t_g_ctrl.b_desc_show = FALSE;
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_desc_update
 *
 * Description: The function updates the program details for a selected event.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_desc_update (VOID)
{
    INT32                        i4_rc;
    UINT16                       ui2_hlt;
    DTG_T                        t_crnt_loc_dtg;
    DTG_T                        t_start_loc_dtg;
    DTG_T                        t_end_loc_dtg;
    UTF16_T                      w2s_time_start[EPG_DT_HOUR_MIN_MAX_LEN];
    UTF16_T                      w2s_time_end[EPG_DT_HOUR_MIN_MAX_LEN];
    UTF16_T                      w2s_time_info[EPG_DT_TIME_MAX_LEN];
    UTF16_T                      w2s_ca[EPG_CA_MSG_MAX_LEN];
    UTF16_T                      w2s_dow[EPG_DT_DATE_MAX_LEN];
    UTF16_T                      w2s_date[EPG_DT_DATE_MAX_LEN];
    CHAR*                        ps_text;
    UTF16_T*                     pw2s_text;
    BOOL                         b_found_time_detail;
    BOOL                         b_found_program_detail;
    BOOL                         b_found_ca;
    BOOL                         b_exceed;
    SIZE_T                       z_info_size = 0;
    EVCTX_ATSC_RATING_LIST_T*    pt_rating;

    /* get highlight index of program list */
    RET_ON_ERR (epg_view_prg_lst_get_hlt_idx (& ui2_hlt));

    if ((ui2_hlt == WGL_LB_NULL_INDEX)   || /* no element highlighted */
        (ui2_hlt >= EPG_EVT_BUFFER_SIZE) || /* something wrong? */
        (t_g_ctrl.b_theme_search)) /* theme search */
    {
        /* hide description frmae */
        RET_ON_ERR (_epg_ctrl_desc_hide_frame ());

        return  EPGR_OK;
    }

    if ((t_g_ctrl.ah_events[ui2_hlt] != NULL_HANDLE) &&
        (t_g_ctrl.ab_events_cb[ui2_hlt]))
    {
        b_found_time_detail = FALSE;

        /* get current local dtg */
        RET_ON_ERR (epg_dt_get_loc_dtg (& t_crnt_loc_dtg));

        /* get local start dtg */
        i4_rc = epg_dt_get_start_loc_dtg_by_event (t_g_ctrl.ah_events[ui2_hlt],
                                                   & t_start_loc_dtg);

        if (i4_rc == 0)
        {
            /* get start hour:minute string */
            RET_ON_ERR (epg_dt_get_time_str (t_start_loc_dtg,
                                             EPG_TIME_MODE_HM,
                                             w2s_time_start));

            /* get local end time */
            i4_rc = epg_dt_get_end_loc_dtg_by_event (t_g_ctrl.ah_events[ui2_hlt],
                                                     & t_end_loc_dtg);

            if (i4_rc == 0)
            {
                /* get end hour:minute string */
                RET_ON_ERR (epg_dt_get_time_str (t_end_loc_dtg,
                                                 EPG_TIME_MODE_HM,
                                                 w2s_time_end));

                /* combine start and end time */
                epg_str_w2s_strcpy (w2s_time_info, w2s_time_start);
                epg_str_w2s_strcat (w2s_time_info, EPG_MLM (MLM_EPG_KEY_SYM_START_END_SEPR));
                epg_str_w2s_strcat (w2s_time_info, w2s_time_end);

                /* append a separtator between end time and day-of-week string */
                epg_str_w2s_strcat (w2s_time_info, EPG_MLM (MLM_EPG_KEY_SYM_DATE_TIME_SEPR));

                /* get day-of-week string */
                RET_ON_ERR (epg_dt_get_time_str (t_start_loc_dtg,
                                                 EPG_TIME_MODE_DOW,
                                                 w2s_dow));

                /* append day-of-week */
                epg_str_w2s_strcat (w2s_time_info, w2s_dow);

                /* append a separator between day-of-week and date */
                epg_str_w2s_strcat (w2s_time_info, EPG_MLM (MLM_EPG_KEY_SYM_DOW_DATE_SEPR));

                /* get month-day string */
                RET_ON_ERR (epg_dt_get_time_str (t_start_loc_dtg,
                                                 EPG_TIME_MODE_MD,
                                                 w2s_date));

                /* append date */
                epg_str_w2s_strcat (w2s_time_info, w2s_date);

                /* set text to the time column of description list */
                RET_ON_ERR (epg_view_desc_lst_set_text (EPG_DESC_TYPE_TIME, w2s_time_info));

                /* turn on the flag indicating time detail is found */
                b_found_time_detail = TRUE;
            }
        }

        if (! b_found_time_detail) /* time detail is not found */
        {
            /* reset time column of description list */
            RET_ON_ERR (epg_view_desc_lst_set_text (EPG_DESC_TYPE_TIME, w2s_g_null_str));
        }

        /* content advisory */
        b_found_ca = FALSE;

        /* get rating info length */
        i4_rc = epg_evt_get_rating_len (t_g_ctrl.ah_events[ui2_hlt], & z_info_size);

        if (i4_rc == EVCTXR_OK && z_info_size != 0)
        {
            /* allocate buffer for atsc rating */
            pt_rating = (EVCTX_ATSC_RATING_LIST_T*) c_mem_alloc (z_info_size);

            if (pt_rating == NULL) /* out of memory */
            {
                DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

                return  EPGR_OUT_OF_MEM;
            }

            /* get rating info */
            i4_rc = epg_evt_get_rating (t_g_ctrl.ah_events[ui2_hlt], z_info_size, pt_rating);

            if (i4_rc == EVCTXR_OK)
            {
                b_found_ca = TRUE;

                /* get normalized rating description */
                i4_rc = a_rating_atsc_get_text (pt_rating,
                                                w2s_ca,
                                                EPG_CA_MSG_MAX_LEN);

                if (i4_rc == APP_RATINGR_OK)
                {
                    /* set text to the rating column of description list */
                    i4_rc = epg_view_desc_lst_set_text (EPG_DESC_TYPE_RATING, w2s_ca);

                    if (i4_rc != EPGR_OK)
                    {
                        DBG_ERROR (("<EPG> ERR: set text failed = %d\n\r", i4_rc));
                    }
                }
                else
                {
                    /* reset text of rating column of description list */
                    i4_rc = epg_view_desc_lst_set_text (EPG_DESC_TYPE_RATING, w2s_g_null_str);

                    if (i4_rc != EPGR_OK)
                    {
                        DBG_ERROR (("<EPG> ERR: set text failed = %d\n\r", i4_rc));
                    }
                }
            }

            c_mem_free (pt_rating); /* free pt_rating */
        }

        if (! b_found_ca) /* no content advisory */
        {
#ifndef APP_REMOVE_UNRATED_RATING
            /* set i18n text to the rating column of description list */
            RET_ON_ERR (epg_view_desc_lst_set_text (EPG_DESC_TYPE_RATING,
                                                    EPG_MLM (MLM_EPG_KEY_MSG_RATING_UNRATED)));
#else
            /* set i18n text to the rating column of description list */
            RET_ON_ERR (epg_view_desc_lst_set_text (EPG_DESC_TYPE_RATING,
                                                    w2s_g_null_str));
#endif /* APP_REMOVE_UNRATED_RATING */
        }

#ifdef APP_REMOVE_VCHIP

        /* clean the text of rating column of description list */
        RET_ON_ERR (epg_view_desc_lst_set_text (EPG_DESC_TYPE_RATING, w2s_g_null_str));

#endif /* APP_REMOVE_VCHIP */

#ifdef APP_EPG_ICON_SEP

        /* cc flag */
        if (_epg_ctrl_evt_is_caption_avail (t_g_ctrl.ah_events[ui2_hlt])) /* cc is found */
        {
            /* set cc icon of icon list */
            RET_ON_ERR (epg_view_icon_lst_set_image (EPG_ICON_TYPE_CC, TRUE));
        }
        else /* cc is not found */
        {
            /* clear cc icon of icon list */
            RET_ON_ERR (epg_view_icon_lst_set_image (EPG_ICON_TYPE_CC, FALSE));
        }

#endif /* APP_EPG_ICON_SEP */

        /* program description */
        b_exceed                    = FALSE;
        b_found_program_detail      = FALSE;
        t_g_ctrl.ui2_desc_page_num  = 0;
        t_g_ctrl.ui2_desc_page_idx  = 0;

        /* Check if the event is blocked. */
        i4_rc = _epg_ctrl_check_rating (t_g_ctrl.ah_events[ui2_hlt], & b_exceed);

        if (i4_rc != 0)
        {
            DBG_ERROR (("<EPG> ERR: check rating failed = %d\n\r", i4_rc));
        }

        if (! b_exceed) /* below rating levels */
        {
            /* get event description length */
            i4_rc = epg_evt_get_text_len (t_g_ctrl.ah_events[ui2_hlt], & z_info_size);

            if (i4_rc == EVCTXR_OK && z_info_size != 0)
            {
                /* allocate UTF8 buffer for event description */
                ps_text = (CHAR*) c_mem_alloc (z_info_size * sizeof(CHAR));

                if (ps_text == NULL) /* out of memory */
                {
                    DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

                    return  EPGR_OUT_OF_MEM;
                }

                /* get event description */
                i4_rc = epg_evt_get_text (t_g_ctrl.ah_events[ui2_hlt], z_info_size, ps_text);

                if (i4_rc == EVCTXR_OK)
                {
                    /* trim spaces */
                    epg_str_trim (ps_text);

                    if (c_strlen (ps_text) > 0)
                    {
                        /* allocate UTF16 buffer for event description */
                        pw2s_text = (UTF16_T*) c_mem_alloc (z_info_size * sizeof(UTF16_T));

                        if (pw2s_text == NULL) /* out of memory */
                        {
                            /* free UTF8 buffer */
                            c_mem_free (ps_text);

                            DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

                            return  EPGR_OUT_OF_MEM;
                        }

                        /* convert UTF8 to UTF16 */
                        i4_rc = epg_str_ps_to_w2s (ps_text,
                                                   pw2s_text,
                                                   z_info_size);

                        /* error handling */
                        if (i4_rc == UCR_NO_ENOUGH_BUFFER) /* buffer underflow */
                        {
                            pw2s_text[z_info_size-1] = 0;
                            i4_rc = UCR_OK;
                        }
                        else if (i4_rc != UCR_OK) /* something error? */
                        {
                            pw2s_text[0] = 0; /* NULL string */
                            i4_rc = UCR_OK;
                        }

                        if (i4_rc == UCR_OK)
                        {
                            if (epg_str_w2s_strlen (pw2s_text) > 0) /* the length of description must be greater than 0 */
                            {
                                /* set text to description text */
                                i4_rc = epg_view_desc_txt_set_text (pw2s_text);

                                if (i4_rc != EPGR_OK)
                                {
                                    DBG_ERROR (("<EPG> ERR: set text failed = %d\n\r", i4_rc));
                                }

                                /* get total pages */
                                i4_rc = epg_view_desc_txt_get_num_pages (& t_g_ctrl.ui2_desc_page_num);

                                if (i4_rc != EPGR_OK)
                                {
                                    DBG_ERROR (("<EPG> ERR: get number of pages failed = %d\n\r", i4_rc));
                                }

                                /* update page help */
                                i4_rc = _epg_ctrl_help_lst_update_page_help (FALSE);

                                if (i4_rc != EPGR_OK)
                                {
                                    DBG_ERROR (("<EPG> ERR: update page help failed = %d\n\r", i4_rc));
                                }

                                /* turn on flag indicating program detail is found */
                                b_found_program_detail = TRUE;
                            }
                        }

                        /* free memory */
                        c_mem_free (pw2s_text);
                    }
                }

                /* free memory */
                c_mem_free (ps_text);
            }

            if (! b_found_program_detail) /* program detail is not found */
            {
                /* set "no program details" to description text */
                RET_ON_ERR (epg_view_desc_txt_set_text (EPG_MLM (MLM_EPG_KEY_MSG_NO_EVENT_DETAIL)));

                /* update page help */
                RET_ON_ERR (_epg_ctrl_help_lst_update_page_help (FALSE));
            }

#ifdef APP_EPG_ICON_SEP

            /* clean lock icon of icon list */
            RET_ON_ERR (epg_view_icon_lst_set_image (EPG_ICON_TYPE_LOCK, FALSE));

#endif /* APP_EPG_ICON_SEP */

        }
        else /* above rating levels */
        {
            /* reset description text */
            RET_ON_ERR (epg_view_desc_txt_set_text (w2s_g_null_str));

            /* reset page text */
            RET_ON_ERR (epg_view_page_txt_set_text (w2s_g_null_str));

            /* update page help */
            RET_ON_ERR (_epg_ctrl_help_lst_update_page_help (FALSE));

#ifdef APP_EPG_ICON_SEP

            /* set lock icon to icon list */
            RET_ON_ERR (epg_view_icon_lst_set_image (EPG_ICON_TYPE_LOCK, TRUE));

#endif /* APP_EPG_ICON_SEP */

        }

        if (t_g_ctrl.b_passwd_show) /* password frame is being shown */
        {
            /* reset description text */
            RET_ON_ERR (epg_view_desc_txt_set_text (w2s_g_null_str));

            /* reset page text */
            RET_ON_ERR (epg_view_page_txt_set_text (w2s_g_null_str));

            /* reset description page data */
            t_g_ctrl.ui2_desc_page_num = 0;
            t_g_ctrl.ui2_desc_page_idx = 0;
        }

        if (t_g_ctrl.b_desc_show) /* description frame is shown */
        {
            /* repaint description frame */
            RET_ON_ERR (epg_view_desc_frm_repaint ());
        }
        else /* description frame is hide */
        {
            /* show description frame */
            RET_ON_ERR (epg_view_desc_frm_show ());

            /* turn on flag indicating description is shown */
            t_g_ctrl.b_desc_show = TRUE;
        }

#ifndef APP_NO_COLOR_KEY

        /* repaint help list */
        RET_ON_ERR (epg_view_help_lst_repaint ());

#endif /* APP_NO_COLOR_KEY */

    }
    else /* t_g_ctrl.ah_events[ui2_hlt] == NULL_HANDLE */
    {
        if (t_g_ctrl.b_desc_show)
        {
            /* hide description frame */
            RET_ON_ERR (_epg_ctrl_desc_hide_frame());
        }
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_is_time_stamp_valid
 *
 * Description: This function checks if a message has valid time stamp.
 *
 * Inputs:  ui4_time_stamp       Time stamp.
 *
 * Outputs: -
 *
 * Returns: TRUE                 Valid.
 *          FALSE                Invalid.
 ----------------------------------------------------------------------------*/
static BOOL _epg_ctrl_is_time_stamp_valid (UINT32    ui4_time_stamp)
{
    UINT32    ui4_current_tick;
    UINT32    ui4_delta_time;
    BOOL      b_valid;

    b_valid = FALSE;

    if (ui4_time_stamp == 0) /* The message should always be processed. */
    {
        b_valid = TRUE;
    }
    else
    {
        /* Check if the message is out-of-date. */
        ui4_current_tick = c_os_get_sys_tick (); /* Get current system tick. */

        if (ui4_current_tick >= ui4_time_stamp) /* Current system tick must be greater than time stamp. */
        {
            /* Calculate delta time. */
            ui4_delta_time = (ui4_current_tick - ui4_time_stamp) * c_os_get_sys_tick_period ();

            if (ui4_delta_time <= EPG_MSG_MAX_DELAY) /* Check if delta time is greater than maximum delay. */
            {
                b_valid = TRUE;
            }
        }
    }

    return b_valid;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_dt_discont_handler
 *
 * Description: The function handlers the condition when DT is discontinue.
 *
 * Inputs:  pt_dt_nfy_data         Date-time notification data.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_dt_discont_handler (DT_NFY_DATA_T*    pt_dt_nfy_data)
{
    UINT16    ui2_i;
    BOOL      b_update = FALSE;

    do
    {
        /* Check if time stamp is valid */
        if (! _epg_ctrl_is_time_stamp_valid (pt_dt_nfy_data->ui4_time_stamp))
        {
            break;
        }

        if (pt_dt_nfy_data->t_delta_time > 0) /* Jump forward */
        {
            /* Check if the time of current event is valid */
            for (ui2_i = 0; ui2_i < EPG_EVT_BUFFER_SIZE; ui2_i ++)
            {
                if ((t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE) &&
                    (t_g_ctrl.ab_events_cb[ui2_i]))
                {
                    /* Find current event. */
                    if (_epg_ctrl_evt_is_crnt (t_g_ctrl.ah_events[ui2_i]))
                    {
                        if (_epg_ctrl_evt_is_expired (t_g_ctrl.ah_events[ui2_i]))
                        {
                            b_update = TRUE;
                        }

                        break;
                    }
                }
            }
        }
        else /* Jump backward */
        {
            /* Check if jump backward for more than a negative delta. */
            if (pt_dt_nfy_data->t_delta_time < DT_DISCONT_DELTA)
            {
                b_update = TRUE;
            }
        }

    } while (0);

    /* Update program list only if required */
    if (b_update)
    {
        RET_ON_ERR (_epg_ctrl_prg_lst_update (0, TRUE));
    }

    return EPGR_OK;
}

#ifndef APP_NO_COLOR_KEY

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_dt_change_date
 *
 * Description: The function changes the date to previous/next day. The events
 *              will be displayed according to the date.
 *
 * Inputs:  b_prev                 TRUE - change to previous day.
 *                                 FALSE - change to next day.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_dt_change_date (BOOL    b_prev)
{
    TIME_T    t_time_start;

#ifndef APP_DVBT_SUPPORT

    if (t_g_ctrl.b_date_changing) /* changing date */
    {
        return  0;
    }

#endif /* APP_DVBT_SUPPORT */

    if ((b_prev && (((t_g_ctrl.i2_date_idx > 0) && (t_g_ctrl.ui2_date_num > 1)) ||
                    ((t_g_ctrl.b_event_yesterday) && (t_g_ctrl.i2_date_idx > -1) && (t_g_ctrl.ui2_date_num > 0)))) || /* previous date */
        (!b_prev && (t_g_ctrl.i2_date_idx < (t_g_ctrl.ui2_date_num-1)))) /* next date */
    {
        if (b_prev)
        {
            t_g_ctrl.i2_date_idx --;
        }
        else
        {
            t_g_ctrl.i2_date_idx ++;
        }

        DBG_INFO (("<EPG> change to date index = %d\n\r", t_g_ctrl.i2_date_idx));

        /* hide description frame */
        RET_ON_ERR (_epg_ctrl_desc_hide_frame ());

        /* get start time by date index */
        RET_ON_ERR (epg_dt_get_start_utc_sec_by_date (t_g_ctrl.i2_date_idx, & t_time_start));

#ifdef APP_DVBT_SUPPORT

        /* Turn on flag indicating date is already jumped. */
        t_g_ctrl.b_date_jumped = TRUE;

#endif /* APP_DVBT_SUPPORT */

        /* update program listing */
        RET_ON_ERR (_epg_ctrl_prg_lst_update (t_time_start, TRUE));

        /* turn on date changing flag */
        t_g_ctrl.b_date_changing = TRUE;

#ifdef APP_DVBT_SUPPORT

        /* update date help with repaint */
        RET_ON_ERR (_epg_ctrl_help_lst_update_date_help (TRUE));

#endif /* APP_DVBT_SUPPORT */
    }

    return  0;
}

#endif /* APP_NO_COLOR_KEY */

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_dt_estimate_avail_time
 *
 * Description: The function estimates the available hours for current channel.
 *
 * Inputs:  b_cb_complete       Event call backs completed or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_dt_estimate_avail_time (BOOL    b_cb_complete)
{
#ifdef APP_DVBT_SUPPORT

    DBG_INFO (("<EPG> available days = %d\n\r", EPG_MAX_AVAIL_DAYS));

    t_g_ctrl.ui2_date_num       = ((epg_svl_is_analog_chn ())            ||
                                   ((t_g_ctrl.ui2_events_crnt_page == 0) &&
                                    (t_g_ctrl.ui2_events_prev_page == 0))) ?
                                  0 : (UINT16)EPG_MAX_AVAIL_DAYS;
    t_g_ctrl.b_time_total_avail = TRUE;
    t_g_ctrl.b_date_changing    = FALSE;

#ifndef APP_NO_COLOR_KEY
    /* update date help */
    RET_ON_ERR (_epg_ctrl_help_lst_update_date_help (TRUE));
#endif /* APP_NO_COLOR_KEY */

#else /* #ifndef APP_DVBT_SUPPORT */

    INT32                     i4_res;
    UINT16                    ui2_i;
    UINT16                    ui2_evt_idx;
    DTG_T                     t_crnt_loc_dtg;
    UINT16                    ui2_avail_hour;
    UINT16                    ui2_avail_min;
    UINT16                    ui2_fine_tune_min;
    BOOL                      b_found_event;
    BOOL                      b_fine_tune;
    TIME_T                    t_time_start;
    TIME_T                    t_time_estimate;

    b_found_event  = FALSE;
    b_fine_tune    = FALSE;
    ui2_evt_idx    = 0;     
     
    c_memset(&t_crnt_loc_dtg, 0, sizeof(DTG_T));

    if (b_cb_complete) /* call backs completed */
    {
        /* find event */
        if (t_g_ctrl.ui2_events_next_page > 0) /* there are events in next page */
        {
            ui2_evt_idx = (UINT16)(2*ELEM_VIEW_SIZE + t_g_ctrl.ui2_events_next_page - 1);
            b_found_event = TRUE;

            if ((t_g_ctrl.ui2_events_next_page < ELEM_VIEW_SIZE) && (! t_g_ctrl.b_event_shifted))
            {
                b_fine_tune = TRUE;
            }
        }
        else if (t_g_ctrl.ui2_events_crnt_page > 0) /* there are events in current page */
        {
            ui2_evt_idx = (UINT16)(t_g_ctrl.ui2_events_crnt_page - 1);
            b_found_event = TRUE;
            b_fine_tune = TRUE;
        }
        else if (t_g_ctrl.ui2_events_prev_page > 0) /* there are events in previous page */
        {
            ui2_evt_idx = 2*ELEM_VIEW_SIZE-1; /* event with index -1 */
            b_found_event = TRUE;
        }

        /* check the event to be estimated */
        if (ui2_evt_idx < EPG_EVT_BUFFER_SIZE)
        {
            if ((t_g_ctrl.ah_events[ui2_evt_idx] == NULL_HANDLE) || /* event doesn't exist */
                (! t_g_ctrl.ab_events_cb[ui2_evt_idx]))             /* event has not been called back */
            {
                b_found_event = FALSE;
                b_fine_tune = FALSE;
            }
        }
    }

    if (! b_found_event) /* last event is not found */
    {
        /* check if there is any event available */
        for (ui2_i = 0; ui2_i < EPG_EVT_BUFFER_SIZE; ui2_i ++)
        {
            if ((t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE) && /* event exists */
                (t_g_ctrl.ab_events_cb[ui2_i]))               /* event has been called back */
            {
                ui2_evt_idx = ui2_i;
                b_found_event = TRUE;

                break;
            }
        }
    }

    if (b_found_event && (ui2_evt_idx < EPG_EVT_BUFFER_SIZE))
    {
        /* get available hours */
        i4_res = epg_evt_get_hours (t_g_ctrl.ah_events[ui2_evt_idx], & ui2_avail_hour);

        if (i4_res == 0) /* get available hours successfully */
        {
            ui2_avail_min = (UINT16)(ui2_avail_hour * 60);

            /* get current local time */
            RET_ON_ERR (epg_dt_get_loc_dtg (& t_crnt_loc_dtg));

            if (b_fine_tune) /* fine tune available time */
            {
                /* estimate time */
                t_time_estimate = epg_dt_get_utc_sec () + (ui2_avail_hour * 3600);

                /* get start time */
                i4_res = epg_evt_get_start_time (t_g_ctrl.ah_events[ui2_evt_idx], & t_time_start);

                if (i4_res == EPGR_OK)
                {
                    /* calculate fine-tune minutes */
                    /* CR[DTV00211521] Do not show "Prev day"  when focus on the last day in the EPG */
                    /* Compare estimate time and last event start time, only do fine tune when estimate bigger than the start time */
                    if (t_time_estimate > t_time_start)
                    {
                        ui2_fine_tune_min = (UINT16)((t_time_estimate - t_time_start) / 60);

                        if (ui2_avail_min >= ui2_fine_tune_min)
                        {
                            ui2_avail_min -= ui2_fine_tune_min;
                        }
                        else /* time error ? */
                        {
                            ui2_avail_min = 0;
                        }
                    }
                }
                else /* something wrong? */
                {
                    ui2_avail_min = 0;
                }
            }

            DBG_INFO (("<EPG> available minutes = %d\n\r", ui2_avail_min));

            if (ui2_avail_min > 0)
            {
                t_g_ctrl.ui2_date_num = 1;

                while (ui2_avail_min >= 1440)
                {
                    t_g_ctrl.ui2_date_num ++;
                    ui2_avail_min -= 1440;
                }

                if ((t_crnt_loc_dtg.ui1_hr * 60 + t_crnt_loc_dtg.ui1_min + ui2_avail_min) >= 1440)
                {
                    t_g_ctrl.ui2_date_num ++;
                }
            }
            else
            {
                t_g_ctrl.ui2_date_num = 0;
            }

            /* Turn on flag indicating total available time is found. */
            t_g_ctrl.b_time_total_avail = TRUE;
        }
        else /* failed to get available hours */
        {
            t_g_ctrl.ui2_date_num = 0;

            DBG_ERROR (("<EPG> get available hours failed = %d\n\r", i4_res));
        }

        DBG_INFO (("<EPG> available days = %d\n\r", t_g_ctrl.ui2_date_num));

        t_g_ctrl.b_date_changing = FALSE;

#ifndef APP_NO_COLOR_KEY
        /* update date help */
        RET_ON_ERR (_epg_ctrl_help_lst_update_date_help (TRUE));
#endif /* APP_NO_COLOR_KEY */

    }

#endif /* #ifndef APP_DVBT_SUPPORT */

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_dt_get_date_idx
 *
 * Description: The function returns date index given an event handle.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pi2_date_idx        Data index relative to current date.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_dt_get_date_idx (HANDLE_T    h_event,
                                        INT16*      pi2_date_idx)
{
    INT32          i4_rc;
    INT16          i2_date_idx;
    TIME_T         t_time_crnt;
    TIME_T         t_time_diff;
    DTG_T          t_crnt_loc_dtg, t_evt_loc_dtg;
    
    c_memset(&t_crnt_loc_dtg, 0, sizeof(DTG_T));

    i2_date_idx = t_g_ctrl.i2_date_idx;

    /* get current local dtg */
    i4_rc = epg_dt_get_loc_dtg (& t_crnt_loc_dtg);

    if (i4_rc == 0)
    {
        /* get event start local dtg */
        i4_rc = epg_dt_get_start_loc_dtg_by_event (h_event, & t_evt_loc_dtg);

        if (i4_rc == 0) /* get starting time successful */
        {
            i2_date_idx = 0;

            t_time_diff = epg_dt_diff (& t_crnt_loc_dtg, & t_evt_loc_dtg);

            while (t_time_diff >= (24*3600))
            {
                i2_date_idx ++;
                t_time_diff -= (24*3600);
            }

            t_time_crnt = t_crnt_loc_dtg.ui1_hr*3600 +
                          t_crnt_loc_dtg.ui1_min*60 +
                          t_crnt_loc_dtg.ui1_sec;

            if ((t_time_crnt + t_time_diff) >= 24*3600)
            {
                i2_date_idx ++;
            }
            else if ((t_time_crnt + t_time_diff) < 0) /* event started at yesterday */
            {
                i2_date_idx = -1;
                t_g_ctrl.b_event_yesterday = TRUE;
            }

            *pi2_date_idx = i2_date_idx;
        }
        else /* get starting time failed */
        {
            DBG_ERROR (("<EPG> ERR: get event local start dtg failed = %d\n\r", i4_rc));

            *pi2_date_idx = 0;
        }
    }
    else /* get current dtg failed */
    {
        DBG_ERROR (("<EPG> ERR: get current dtg failed = %d\n\r", i4_rc));

        *pi2_date_idx = 0;
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_dt_get_dow
 *
 * Description: The function returns day of week for a event given current local
 *              time and event local time.
 *
 * Inputs:  pt_crnt_loc_dtg     Current local dtg.
 *          pt_evt_loc_dtg      Event's local dtg.
 *
 * Outputs: pw2s_dow            Day of week string.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_dt_get_dow (DTG_T*      pt_crnt_loc_dtg,
                                   DTG_T*      pt_evt_loc_dtg,
                                   UTF16_T*    pw2s_dow)
{
    INT8      i1_date_offset;
    TIME_T    t_time_delta;
    UINT8     ui1_dow_idx;

    i1_date_offset = (INT8)(pt_evt_loc_dtg->ui1_dow - pt_crnt_loc_dtg->ui1_dow);
    t_time_delta = epg_dt_diff (pt_crnt_loc_dtg, pt_evt_loc_dtg);

    if ((t_time_delta < 0) && ((i1_date_offset == -1) || (i1_date_offset == 6)))
    {
        ui1_dow_idx = MLM_EPG_KEY_DOW_YES; /* yesterday */
    }
    else if ((t_time_delta < 86400) && (i1_date_offset == 0))
    {
        ui1_dow_idx = MLM_EPG_KEY_DOW_TOD; /* today */
    }
    else if ((t_time_delta < 172800) && ((i1_date_offset == 1) || (i1_date_offset == -6)))
    {
        ui1_dow_idx = MLM_EPG_KEY_DOW_TOM; /* tomorrow */
    }
    else
    {
        ui1_dow_idx = MLM_EPG_KEY_DOW_SUN + pt_evt_loc_dtg->ui1_dow;
    }

    epg_str_w2s_strcpy (pw2s_dow, EPG_MLM (ui1_dow_idx));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_dt_update_crnt_time
 *
 * Description: The function updates current system time when clock timer expired
                after a pre-set interval (maybe every second).
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_dt_update_crnt_time (VOID)
{
    UTF16_T    w2s_time[EPG_DT_TIME_MAX_LEN];
    DTG_T      t_crnt_loc_dtg;
    DT_COND_T  t_dt_cond;

    c_memset(&t_crnt_loc_dtg, 0, sizeof(DTG_T));

    /* Get current condition of date-time */
    t_dt_cond = epg_dt_get_cond ();

    if ((! epg_svl_is_found ())           ||  /* svl is not found */
		(t_g_ctrl.b_svc_input_blocked)    ||  /* TV is input blocked.*/
        (! t_g_ctrl.b_svc_signal_locked)  ||  /* signal is not locked */
        (t_dt_cond == DT_FREE_RUNNING)    ||  /* Date-time is free-running */
        (t_dt_cond == DT_NOT_RUNNING)     ||  /* Date-time is not-running */
        (t_dt_cond == DT_NO_SYNC_SRC))        /* No sync source */
    {

        if (t_g_ctrl.b_time_display)
        {
            /* set text to time text */
            RET_ON_ERR (epg_view_time_txt_set_text (EPG_MLM (MLM_EPG_KEY_MSG_NULL)));

            /* repaint time text */
            RET_ON_ERR (epg_view_time_txt_repaint ());

            t_g_ctrl.b_time_display = FALSE;
        }

        return  0;
    }

    /* get current local dtg */
    RET_ON_ERR (epg_dt_get_loc_dtg (& t_crnt_loc_dtg));

    /* get time string */
    RET_ON_ERR (epg_dt_get_time_str (t_crnt_loc_dtg,
                                     EPG_TIME_MODE_FULL,
                                     w2s_time));

    /* set text to time text */
    RET_ON_ERR (epg_view_time_txt_set_text (w2s_time));

    /* repaint time text */
    RET_ON_ERR (epg_view_time_txt_repaint ());

    /* update events if the time is acrossing date boundary */
    if ((t_crnt_loc_dtg.ui1_hr == 0) &&
        (t_crnt_loc_dtg.ui1_min == 0) &&
        (t_crnt_loc_dtg.ui1_sec == 0))
    {
        /* update events */
        RET_ON_ERR (_epg_ctrl_evt_update ());

        /* Turn-on yesterday flag. */
        t_g_ctrl.b_event_yesterday = TRUE;

        /* Subtract one from available days. */
        t_g_ctrl.ui2_date_num --;

#ifndef APP_NO_COLOR_KEY

        /* update date index with repaint */
        RET_ON_ERR (_epg_ctrl_help_lst_update_date_idx (TRUE));

#endif /* APP_NO_COLOR_KEY */

        /* update available hours */
        RET_ON_ERR (_epg_ctrl_dt_estimate_avail_time (t_g_ctrl.b_event_cb_complete));
    }

    t_g_ctrl.b_time_display = TRUE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_evt_is_caption_avail
 *
 * Description: The function checks if there is any cc available for an event.
 *
 * Inputs:  h_event                Event handle.
 *
 * Outputs: -
 *
 * Returns: TRUE                   Yes - CC available.
 *          FALSE                  No - CC not available.
 ----------------------------------------------------------------------------*/
static BOOL _epg_ctrl_evt_is_caption_avail (HANDLE_T    h_event)
{
    INT32           i4_rc;
    BOOL            b_caption;
    BOOL            b_caption_avail;

    b_caption_avail = FALSE;

    if (_epg_ctrl_evt_is_crnt (h_event)) /* current event */
    {
        EPG_CC_QUERY_DATA_T t_cc_query_data;
        c_memset (&t_cc_query_data, 0, sizeof(EPG_CC_QUERY_DATA_T));
        
        /* Query whether there is any CC in current event from SVCTX */
        t_cc_query_data.e_query_mode = EPG_CC_QUERY_SVCTX;
        b_caption_avail = epg_svc_is_crnt_event_with_cc(&t_cc_query_data);

        /* update current event CC indicator */
        t_g_ctrl.b_event_crnt_with_cc_info = b_caption_avail;

        if (t_cc_query_data.b_delay_query)
        {
            DBG_INFO (("<EPG> start a timer to delay query CC again from SVCTX. \n\r"));
            /* Start a timer to delay query CC again from SVCTX. */
            epg_timer_start (t_g_ctrl.h_timer_delay_query_cc,
                                 TIMER_DEALY_QUERY_CC_FROM_SVC,
                                 X_TIMER_FLAG_ONCE);
        }
    }
    else /* not current event */
    {
        /* get cc info */
        i4_rc = epg_evt_get_caption (h_event, & b_caption);

        if ((i4_rc == EVCTXR_OK) && (b_caption))
        {
            b_caption_avail = TRUE;
        }
    }

    return  b_caption_avail;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_evt_is_crnt
 *
 * Description: The function checks if a given event is current event.
 *
 * Inputs:  h_event                Event handle.
 *
 * Outputs: -
 *
 * Returns: TRUE                   Yes - current event.
 *          FALSE                  No - not current event.
 ----------------------------------------------------------------------------*/
static BOOL _epg_ctrl_evt_is_crnt (HANDLE_T    h_event)
{
    INT32          i4_rc;
    TIME_T         t_time_start;
    TIME_T         t_time_duration;
    TIME_T         t_time_crnt;
    BOOL           b_crnt_event;

    b_crnt_event = FALSE;

    if (epg_svl_is_analog_chn ()) /* Analog channel */
    {
        b_crnt_event = TRUE;
    }
    else
    {
        /* get starting time */
        i4_rc = epg_evt_get_start_time (h_event, & t_time_start);

        if (i4_rc == 0)
        {
            /* get duration */
            i4_rc = epg_evt_get_duration (h_event, & t_time_duration);

            if (i4_rc == 0)
            {
                /* get current UTC time */
                t_time_crnt = epg_dt_get_utc_sec ();

                if ((t_time_start <= t_time_crnt) &&
                    ((t_time_start + t_time_duration) > t_time_crnt))
                {
                    /* current event */
                    b_crnt_event = TRUE;
                }
            }
        }
    }

    return  b_crnt_event;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_evt_is_expired
 *
 * Description: The function checks if an events is expired.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: -
 *
 * Returns: TRUE                Expired.
 *          FALSE               Not expired.
 ----------------------------------------------------------------------------*/
static BOOL _epg_ctrl_evt_is_expired (HANDLE_T    h_event)
{
    INT32     i4_rc;
    BOOL      b_expired;
    TIME_T    t_time_crnt;
    TIME_T    t_time_start;
    TIME_T    t_time_duration;

    b_expired = FALSE;

    /* get current UTC time */
    t_time_crnt = epg_dt_get_utc_sec ();

    /* get event start time (UTC time) */
    i4_rc = epg_evt_get_start_time (h_event, & t_time_start);

    if (i4_rc == 0)
    {
        /* get event duration */
        i4_rc = epg_evt_get_duration (h_event, & t_time_duration);

        if (i4_rc == 0)
        {
            if ((t_time_start + t_time_duration) < t_time_crnt)
            {
                /* turn on expired flag */
                b_expired = TRUE;
            }
        }
    }

    return  b_expired;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_evt_display_none
 *
 * Description: The function updates the display when there is no event
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_evt_display_none (VOID)
{
    /* Update program text. */
    RET_ON_ERR (epg_view_prg_txt_set_text (EPG_MLM (MLM_EPG_KEY_MSG_NO_EVENT_DATA)));
    RET_ON_ERR (epg_view_prg_txt_repaint ());

    if (! t_g_ctrl.b_svc_event_blocked)
    {
        /* Update program detail. */
        RET_ON_ERR (epg_view_desc_txt_set_text (EPG_MLM (MLM_EPG_KEY_MSG_NO_EVENT_DETAIL)));
    }

    /* Update rating info. */
#if 0

    INT32        i4_rc;
    UTF16_T      w2s_ca[EPG_CA_MSG_MAX_LEN];

    /* Get normalized rating description */
    i4_rc = a_rating_atsc_get_text (NULL,
                                    w2s_ca,
                                    EPG_CA_MSG_MAX_LEN);

    if (i4_rc == APP_RATINGR_OK)
    {
        /* Set normalized text to the rating column of description list */
        RET_ON_ERR (epg_view_desc_lst_set_text (EPG_DESC_TYPE_RATING, w2s_ca));
    }

#else

    /* set i18n text to the rating column of description list */
    RET_ON_ERR (epg_view_desc_lst_set_text (EPG_DESC_TYPE_RATING,
                                            EPG_MLM (MLM_EPG_KEY_MSG_RATING_UNRATED)));
#endif /* if 0 */

    /* Update description frame. */
    if (t_g_ctrl.b_desc_show) /* description frame is shown */
    {
        /* repaint description frame */
        RET_ON_ERR (epg_view_desc_frm_repaint ());
    }
    else /* description frame is hide */
    {
        /* show description frame */
        RET_ON_ERR (epg_view_desc_frm_show ());

        /* turn on flag indicating description is shown */
        t_g_ctrl.b_desc_show = TRUE;
    }

    return EPGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_evt_retry
 *
 * Description: The function retries getting current/next events.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_evt_retry (VOID)
{
    EVCTX_OFFSET_T    t_offset;

    DBG_INFO (("<EPG> retry getting events\n\r"));

    t_offset.e_offset_type = EVCTX_OFFSET_TYPE_INDEX;
    t_offset.t_time_start = 0;

    if (t_g_ctrl.ui2_events_crnt_page == 0)
    {
        /* load current event */
        t_offset.u_offset.i2_index = 0;

        RET_ON_ERR (epg_evt_load (& t_offset, t_g_ctrl.ui1_event_type, & t_g_ctrl.h_event_crnt));

        /* load next event */
        t_offset.u_offset.i2_index = 1;

        RET_ON_ERR (epg_evt_load (& t_offset, t_g_ctrl.ui1_event_type, & t_g_ctrl.h_event_next));
    }
    else if (t_g_ctrl.ui2_events_crnt_page == 1)
    {
        if (t_g_ctrl.b_event_shifted)
        {
            /* load current event */
            t_offset.u_offset.i2_index = 0;

            RET_ON_ERR (epg_evt_load (& t_offset, t_g_ctrl.ui1_event_type, & t_g_ctrl.h_event_crnt));
        }
        else
        {
            /* load next event */
            t_offset.u_offset.i2_index = 1;

            RET_ON_ERR (epg_evt_load (& t_offset, t_g_ctrl.ui1_event_type, & t_g_ctrl.h_event_next));
        }
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_evt_free_all
 *
 * Description: The function frees all the event handles.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_evt_free_all (VOID)
{
    UINT16    ui2_i;

    /*
       Free event handles.
    */
    for (ui2_i = 0; ui2_i < EPG_EVT_BUFFER_SIZE; ui2_i ++)
    {
        if (t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE)
        {
            epg_evt_free (t_g_ctrl.ah_events[ui2_i]);
            t_g_ctrl.ah_events[ui2_i] = NULL_HANDLE;
        }
    }

    /*
       Free elements in previous/next page.
    */
    for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
    {
        _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_i]);
        _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_i]);
    }

    /*
       Free current/next event.
    */
    if (t_g_ctrl.h_event_crnt != NULL_HANDLE)
    {
        epg_evt_free (t_g_ctrl.h_event_crnt);
        t_g_ctrl.h_event_crnt = NULL_HANDLE;
    }

    if (t_g_ctrl.h_event_next != NULL_HANDLE)
    {
        epg_evt_free (t_g_ctrl.h_event_next);
        t_g_ctrl.h_event_next = NULL_HANDLE;
    }

    return EPGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_evt_update
 *
 * Description: The function updates all the events.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_evt_update (VOID)
{
    UINT16    ui2_i;
    UINT16    ui2_evt_idx;
    UINT16    ui2_hlt = 0;

    if (t_g_ctrl.ui2_events_crnt_page > 0) /* there are events in current page */
    {
        /* get highlighted index of program list */
        RET_ON_ERR (epg_view_prg_lst_get_hlt_idx (& ui2_hlt));

        /* update events */
        for (ui2_i = 0; ui2_i < EPG_EVT_BUFFER_SIZE; ui2_i ++)
        {
            if ((t_g_ctrl.ah_events[ui2_i] == NULL_HANDLE) ||
                (! t_g_ctrl.ab_events_cb[ui2_i])) /* event is not called back */
            {
                continue;
            }

            /* update events data */
            if (ui2_i < ELEM_VIEW_SIZE) /* events in current page */
            {
                /* update program element */
                RET_ON_ERR (_epg_ctrl_prg_lst_update_elem (ui2_i));

                if (ui2_i == ui2_hlt) /* the element which is being highlighted */
                {
                    /* update program detail */
                    RET_ON_ERR (_epg_ctrl_desc_update ());
                }
            }
            else if (ui2_i < (2*ELEM_VIEW_SIZE)) /* events in previous page */
            {
                ui2_evt_idx = (UINT16)(ui2_i - ELEM_VIEW_SIZE);

                /* free elements in previous page */
                _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_evt_idx]);

                /* get elements in previous page */
                RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_evt_idx], ui2_i));
            }
            else /* events in next page */
            {
                ui2_evt_idx = (UINT16)(ui2_i - (2*ELEM_VIEW_SIZE));

                /* free elements in next page */
                _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_evt_idx]);

                /* get elements in next page */
                RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_evt_idx], ui2_i));
            }
        }

        /* make up elements for previous page */
        RET_ON_ERR (_epg_ctrl_prg_lst_make_up_elems ());
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_evt_nfy
 *
 * Description: The function handles the conditions while receiving notifications
 *              from event context.
 *
 * Inputs:  ui4_type            Notification reason.
 *          h_event             Handle to the event.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_evt_nfy (UINT32      ui4_type,
                                HANDLE_T    h_event)
{
    INT32               i4_rc;
    TIME_T              t_time;
    UINT16              ui2_i;
    UINT16              ui2_evt_idx;
    UINT16              ui2_idx;
    UINT16              ui2_hlt;
    UINT16              ui2_elem_num;
    INT16               i2_date_idx;
    BOOL                b_found;
    BOOL                b_update;
    BOOL                b_cb;

    b_found     = FALSE;
    b_cb        = FALSE;
    ui2_evt_idx = 0;

    /* reset message if there is no signal or the channel is blocked */
    if ((t_g_ctrl.b_svc_signal_loss) ||
        (t_g_ctrl.b_svc_input_blocked) ||
        (t_g_ctrl.b_svc_channel_blocked))
    {
        if (t_g_ctrl.b_retrieving) /* retrieving data */
        {
            /* turn off retrieving flag */
            t_g_ctrl.b_retrieving = FALSE;

            /* update retrieving state */
            RET_ON_ERR (_epg_ctrl_retrieve_update_state ());
        }
    }

    /* retrying events call back */
    if ((h_event == t_g_ctrl.h_event_crnt) ||
        (h_event == t_g_ctrl.h_event_next))
    {
        if (ui4_type == EPG_MSG_EVT_AVAIL) /* event is available */
        {
            /* free event handles */
            epg_evt_free (t_g_ctrl.h_event_crnt);
            epg_evt_free (t_g_ctrl.h_event_next);
            t_g_ctrl.h_event_crnt = NULL_HANDLE;
            t_g_ctrl.h_event_next = NULL_HANDLE;

            /* update program listing */
            RET_ON_ERR (_epg_ctrl_prg_lst_update (0, TRUE));
        }
        else if (ui4_type == EPG_MSG_EVT_UNAVAIL) /* event is unavailable */
        {
            /* do not need to free event handles since EVCTX has done it for applications */
            if (h_event == t_g_ctrl.h_event_crnt)
            {
                t_g_ctrl.h_event_crnt = NULL_HANDLE;
            }
            else if (h_event == t_g_ctrl.h_event_next)
            {
                t_g_ctrl.h_event_next = NULL_HANDLE;
            }

            /* both current and next events are not found */
            if ((t_g_ctrl.h_event_crnt == NULL_HANDLE) &&
                (t_g_ctrl.h_event_next == NULL_HANDLE) &&
                (! t_g_ctrl.b_svc_signal_loss) &&   /* there is signal */
                (! t_g_ctrl.b_svc_input_blocked) && /* input is not blocked */
                (! t_g_ctrl.b_svc_channel_blocked)) /* channel is not blocked */
            {
                /* restart timer to retry getting events */
                RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_retry,
                                             TIMER_DELAY_RETRY,
                                             X_TIMER_FLAG_ONCE));
            }
        }

        return 0;
    }

    /* Events in current/previous/next page */
    for (ui2_i = 0; ui2_i < EPG_EVT_BUFFER_SIZE; ui2_i ++)
    {
        if (t_g_ctrl.ah_events[ui2_i] == h_event) /* find event */
        {
            if ((ui4_type == EPG_MSG_EVT_AVAIL) || /* event is available */
                (ui4_type == EPG_MSG_EVT_UNAVAIL)) /* event is not available */
            {
                b_cb = (t_g_ctrl.ab_events_cb[ui2_i] == TRUE) ? TRUE : FALSE;

                /* turn on call back flag */
                t_g_ctrl.ab_events_cb[ui2_i] = TRUE;

                /* accumulate the number of call backs */
                if (! b_cb)
                {
                    t_g_ctrl.ui2_events_cb ++;
                }
                else /* the event has been called back */
                {
                    if (ui4_type == EPG_MSG_EVT_AVAIL)
                    {
                        /* treat the available event as an update event */
                        ui4_type = EPG_MSG_EVT_UPDATED;
                    }
                }
            }

            /* record event index */
            ui2_evt_idx = ui2_i;

            /* turn on the flag indicating the event is found */
            b_found = TRUE;

            break;
        }
    }

    DBG_INFO (("<EPG> event notify, handle = %d, index = %d, type = %d\n\r", h_event, ui2_i, ui4_type));

    if ((b_found) &&                        /* event can be found */
        (! t_g_ctrl.b_svc_signal_loss) &&   /* there is signal */
        (! t_g_ctrl.b_svc_input_blocked) && /* input is not blocked */
        (! t_g_ctrl.b_svc_channel_blocked)) /* channel is not blocked */
    {
        if (ui4_type == EPG_MSG_EVT_AVAIL)  /* event is available */
        {
            if (! b_cb) /* the event has not been called back */
            {
                /* validate event data */
                if ((! epg_svl_is_analog_chn()) && (ui2_evt_idx != 0))
                {
                    i4_rc = epg_evt_get_start_time (t_g_ctrl.ah_events[ui2_evt_idx], & t_time);

                    if (i4_rc != EPGR_OK) /* no valid time? */
                    {
                        /* free event handle */
                        epg_evt_free (h_event);
                        t_g_ctrl.ah_events[ui2_evt_idx] = NULL_HANDLE;

                        /* CR[DTV00211520] Display "(No program title)" message and  press "red" key no response in the EPG */
                        /* all events have been called back */
                        if ((t_g_ctrl.ui2_events_cb == t_g_ctrl.ui2_events_req) &&
                            (! t_g_ctrl.b_event_cb_complete))
                        {
                            /* turn on call-back completed flag */
                            t_g_ctrl.b_event_cb_complete = TRUE;

                            /* clean up "Retrieving data ..." message */
                            if (t_g_ctrl.b_retrieving) /* retrieving data */
                            {
                                /* turn off retrieving flag */
                                t_g_ctrl.b_retrieving = FALSE;

                                /* update retrieving state */
                                RET_ON_ERR (_epg_ctrl_retrieve_update_state ());
                            }
                        }

                        return EPGR_OK;
                    }
                }

                /* turn on flag indicating the event should be updated */
                b_update = TRUE;

                if (ui2_evt_idx < ELEM_VIEW_SIZE) /* events in current page */
                {
                    if ((ui2_evt_idx == 0) &&          /* current event */
                        (t_g_ctrl.b_date_changing) &&  /* changing date */
                        (! t_g_ctrl.b_event_shifted))  /* events has not been shifted */
                    {
                        /* get date index of current event */
                        RET_ON_ERR (_epg_ctrl_dt_get_date_idx (t_g_ctrl.ah_events[0], & i2_date_idx));

                        /* current event is acrossing date boundary (current event started at last day */
                        if (i2_date_idx != t_g_ctrl.i2_date_idx)
                        {
                            /* CR[DTV00211520] Display "(No program title)" message and  press "red" key no response in the EPG */
                            i4_rc = epg_evt_get_start_time (t_g_ctrl.ah_events[0], & t_time);

                            if (i4_rc == EPGR_OK) /* valid time */
                            {
                                /* shift events upward one slot */
                                RET_ON_ERR (_epg_ctrl_prg_lst_shift_elems (TRUE));

                                /* turn on event-shift flag */
                                t_g_ctrl.b_event_shifted = TRUE;

                                /* do not need to update event data */
                                b_update = FALSE;
                            }
                        }
                    }

                    if (b_update) /* event should be updated */
                    {
                        /* event index exceeds the number of element. */
                        RET_ON_ERR (epg_view_prg_lst_get_elem_num (& ui2_elem_num));

                        if (ui2_elem_num < (UINT16)(ui2_evt_idx+1))
                        {
                            /* set the number of elements of program list to (event index+1) */
                            RET_ON_ERR (epg_view_prg_lst_set_elem_num ((UINT16)(ui2_evt_idx+1)));
                        }

                        /* no element in current page */
                        if (t_g_ctrl.ui2_events_crnt_page == 0)
                        {
                            /* highlight the element of event index */
                            RET_ON_ERR (epg_view_prg_lst_hlt_elem (ui2_evt_idx));

#ifndef APP_NO_COLOR_KEY

                            /* update date index without repaint */
                            RET_ON_ERR (_epg_ctrl_help_lst_update_date_idx (FALSE));

#endif /* APP_NO_COLOR_KEY */

                            /* enable control keys of program list */
                            RET_ON_ERR (epg_view_prg_lst_enable_control_key (TRUE));
                        }

                        /* update program element */
                        RET_ON_ERR (_epg_ctrl_prg_lst_update_elem (ui2_evt_idx));

                        /* update event details if required */
                        RET_ON_ERR (epg_view_prg_lst_get_hlt_idx (& ui2_hlt));

                        if (ui2_evt_idx == ui2_hlt) /* the call-back event was already highlighted */
                        {
                            /* Send a pseudo highlight event. */
                            epg_app_send_msg (EPG_MSG_VIEW_WGL_PRG_LST_ELEM_HLT, NULL, 0);
                        }

                        /* accumulate the number of events in current page */
                        t_g_ctrl.ui2_events_crnt_page ++;

#if 0
                        /* estimate available time if the third event in current page is called back */
                        /* (the date-change function will be enabled) */
                        if (((t_g_ctrl.i2_date_idx == 0) && (ui2_evt_idx == ELEM_VIEW_SIZE-1))  || /* the last event of current page */
                            ((t_g_ctrl.i2_date_idx == -1) && (ui2_evt_idx == 0)) || /* the event of today is called back */
                            ((t_g_ctrl.i2_date_idx > 0) && (ui2_evt_idx == 0)))  ||  /* the first event of other day */
                            ((t_g_ctrl.ui2_events_prev_page > 0) && (ui2_evt_idx == 0))) /* there are events in previous page */
                        {
                            /* update available hours */
                            RET_ON_ERR (_epg_ctrl_dt_estimate_avail_time (FALSE));
                        }
#endif
                    }
                }
                else if (ui2_evt_idx < (2*ELEM_VIEW_SIZE)) /* events in previous page */
                {
                    if (! _epg_ctrl_evt_is_expired (t_g_ctrl.ah_events[ui2_evt_idx])) /* event is not expired */
                    {
                        ui2_idx = (UINT16)(ui2_evt_idx - ELEM_VIEW_SIZE);

                        /* cache elements in previous page */
                        RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_idx], ui2_evt_idx));

                        /* accumulate the number of events in previous page */
                        t_g_ctrl.ui2_events_prev_page ++;
                    }
                    else /* event is expired */
                    {
                        /* free event handle */
                        epg_evt_free (h_event);
                        t_g_ctrl.ah_events[ui2_evt_idx] = NULL_HANDLE;
                    }
                }
                else /* events in next page */
                {
                    ui2_idx = (UINT16)(ui2_evt_idx - (2*ELEM_VIEW_SIZE));

                    /* cache elements in next page */
                    RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_idx], ui2_evt_idx));

                    /* accumulate the number of events in next page */
                    t_g_ctrl.ui2_events_next_page ++;
                }

                if ((ui2_evt_idx == 2*ELEM_VIEW_SIZE-1) || /* last event in previous page */
                    (ui2_evt_idx == 2*ELEM_VIEW_SIZE) ||   /* first event in next page */
                    (! b_update)) /* event doens't need to be updated => must be an event acrossing two days */
                {
                    if (t_g_ctrl.ui2_events_crnt_page == ELEM_VIEW_SIZE) /* events in current page have been retrieved */
                    {
                        /* update scrolling images of program list */
                        RET_ON_ERR (_epg_ctrl_prg_lst_update_scroll_images ());

                        /* enable control keys of program list */
                        RET_ON_ERR (epg_view_prg_lst_enable_control_key (TRUE));
                    }
                }

#ifdef APP_DVBT_SUPPORT
                /* try to update available time if required. */
                if (! t_g_ctrl.b_time_total_avail)
                {
                    /* update available hours */
                    RET_ON_ERR (_epg_ctrl_dt_estimate_avail_time (FALSE));
                }
#else
                /* try to update available time if total available time has not been found. */
                if ((! t_g_ctrl.b_time_total_avail) && (t_g_ctrl.ui2_events_crnt_page == ELEM_VIEW_SIZE))
                {
                    /* update available hours */
                    RET_ON_ERR (_epg_ctrl_dt_estimate_avail_time (FALSE));
                }
#endif /* APP_DVBT_SUPPORT */

            }
        }
        else if (ui4_type == EPG_MSG_EVT_UNAVAIL) /* event is not available */
        {
            if (b_cb) /* event had been called back */
            {
                /* update program listing */
                RET_ON_ERR (_epg_ctrl_prg_lst_update (0, TRUE));
            }
            else /* event had not been called back */
            {
                /* do not need to free handle since EVCTX has done it for applications */
                t_g_ctrl.ah_events[ui2_evt_idx] = NULL_HANDLE;

                if ((ui2_evt_idx == 2*ELEM_VIEW_SIZE-1) || /* last event in previous page */
                    (ui2_evt_idx == 2*ELEM_VIEW_SIZE))     /* first event in next page */
                {
                    /* update scrolling images of program list */
                    RET_ON_ERR (_epg_ctrl_prg_lst_update_scroll_images ());
                }

                if ((ui2_evt_idx < ELEM_VIEW_SIZE) ||  /* event in current page */
                    (ui2_evt_idx >= 2*ELEM_VIEW_SIZE)) /* events in next page */
                {
                    if (! t_g_ctrl.b_time_avail_updated) /* available time has not been updated */
                    {
                        /* update available hours */
                        RET_ON_ERR (_epg_ctrl_dt_estimate_avail_time (TRUE));

                        /* turn on flag indicating the available time has been updated */
                        t_g_ctrl.b_time_avail_updated = TRUE;
                    }
                }

                if ((ui2_evt_idx == 0) &&         /* current event */
                    (! t_g_ctrl.b_event_shifted)) /* events have not been shifted */
                {
                    /* shift events upward one slot */
                    RET_ON_ERR (_epg_ctrl_prg_lst_shift_elems (FALSE));

                    /* turn on event-shift flag */
                    t_g_ctrl.b_event_shifted = TRUE;
                }
            }
        }
        else if (ui4_type == EPG_MSG_EVT_EXPIRED) /* event expired */
        {
            if (ui2_evt_idx == 0) /* the first event in current page expired */
            {
                /* decrease the number of events in current page */
                t_g_ctrl.ui2_events_crnt_page --;

                /* shift events upward one slot */
                RET_ON_ERR (_epg_ctrl_prg_lst_shift_elems (FALSE));
            }
            else /* expired event is in previous page */
            {
                if (t_g_ctrl.ah_events[ELEM_VIEW_SIZE] != NULL_HANDLE)
                {
                    /* free the first event in previous page */
                    epg_evt_free (t_g_ctrl.ah_events[ELEM_VIEW_SIZE]);
                    t_g_ctrl.ah_events[ELEM_VIEW_SIZE] = NULL_HANDLE;

                    if (t_g_ctrl.ab_events_cb[ELEM_VIEW_SIZE] == TRUE) /* event is called back */
                    {
                        /* decrease the number of events in previous page */
                        t_g_ctrl.ui2_events_prev_page --;
                    }
                    else /* event is not called back */
                    {
                        /* accumulate the number of call backs */
                        t_g_ctrl.ui2_events_cb ++;
                    }

                    /* make up elements in previous page */
                    RET_ON_ERR (_epg_ctrl_prg_lst_make_up_elems ());
                }
            }

            /* turn off flag indicating the event started at yesterday */
            t_g_ctrl.b_event_yesterday = FALSE;
        }
        else if (ui4_type == EPG_MSG_EVT_UPDATED) /* event is updated */
        {
            if (ui2_evt_idx < ELEM_VIEW_SIZE) /* event in current page */
            {
                /* update program element */
                RET_ON_ERR (_epg_ctrl_prg_lst_update_elem (ui2_evt_idx));

                /* get highlighted index of program list */
                RET_ON_ERR (epg_view_prg_lst_get_hlt_idx (& ui2_hlt));

                if ((ui2_evt_idx == ui2_hlt) && /* the call-back event is highlighted */
                    (t_g_ctrl.b_desc_show))     /* program description frame is shown */
                {
                    /* update program detail */
                    RET_ON_ERR (_epg_ctrl_desc_update ());
                }
            }
            else if (ui2_evt_idx < (2*ELEM_VIEW_SIZE)) /* events in previous page */
            {
                if (t_g_ctrl.b_event_cb_complete) /* call backs are completed */
                {
                    ui2_idx = (UINT16)((ui2_evt_idx - ELEM_VIEW_SIZE) - (ELEM_VIEW_SIZE - t_g_ctrl.ui2_events_prev_page));
                }
                else /* call backs are not completed */
                {
                    ui2_idx = (UINT16)(ui2_evt_idx - ELEM_VIEW_SIZE);
                }
                
                if (ui2_idx < ELEM_VIEW_SIZE) /* validate index */
                {
                    /* free elements in previous page */
                    _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_idx]);
                    
                    /* get elements in previous page */
                    RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_idx], ui2_evt_idx));
                }
            }
            else /* events in next page */
            {
                ui2_idx = (UINT16)(ui2_evt_idx - (2*ELEM_VIEW_SIZE));
                
                if (ui2_idx < ELEM_VIEW_SIZE) /* validate index */
                {
                    /* free elements in next page */
                    _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_idx]);
                    
                    /* get elements in next page */
                    RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_idx], ui2_evt_idx));
                }
            }
        }

        /* all events have been called back */
        if ((t_g_ctrl.ui2_events_cb == t_g_ctrl.ui2_events_req) &&
            (! t_g_ctrl.b_event_cb_complete))
        {
            /* validate current event */
            if ((! epg_svl_is_analog_chn()) &&
                (t_g_ctrl.ui2_events_crnt_page > 1) &&
                (t_g_ctrl.ah_events[0] != NULL_HANDLE))
            {
                i4_rc = epg_evt_get_start_time (t_g_ctrl.ah_events[0], & t_time);

                if (i4_rc != EPGR_OK) /* no valid time? */
                {
                    /* decrease the number of events in current page */
                    t_g_ctrl.ui2_events_crnt_page --;

                    /* shift events upward one slot */
                    RET_ON_ERR (_epg_ctrl_prg_lst_shift_elems (FALSE));

                    /* turn on event-shift flag */
                    t_g_ctrl.b_event_shifted = TRUE;
                }
            }

            if (t_g_ctrl.ui2_events_crnt_page == 0) /* no events in current page */
            {
                if (t_g_ctrl.ui2_events_prev_page > 0) /* there are events in previous page */
                {
                    /* set the number of elements to 1 */
                    RET_ON_ERR (epg_view_prg_lst_set_elem_num (1));

                    /* highlight first element */
                    RET_ON_ERR (epg_view_prg_lst_hlt_elem (0));

                    /* enable control keys */
                    RET_ON_ERR (epg_view_prg_lst_enable_control_key (TRUE));
                }
                else /* there is no event in previous page */
                {
                    /* disable control keys */
                    RET_ON_ERR (epg_view_prg_lst_enable_control_key (FALSE));
                }
            }

            /* make up elements in previous page */
            RET_ON_ERR (_epg_ctrl_prg_lst_make_up_elems ());

            /* turn on call-back completed flag */
            t_g_ctrl.b_event_cb_complete = TRUE;

            /* clean up "Retrieving data ..." message */
            if (t_g_ctrl.b_retrieving) /* retrieving data */
            {
                /* turn off retrieving flag */
                t_g_ctrl.b_retrieving = FALSE;

                /* update retrieving state */
                RET_ON_ERR (_epg_ctrl_retrieve_update_state ());
            }

            /* start timer to retry getting events if there is no event in current page and previous page */
            if ((t_g_ctrl.ui2_events_crnt_page == 0) &&
                (t_g_ctrl.ui2_events_prev_page == 0))
            {
                /* update osd in case there is no event */
                RET_ON_ERR (_epg_ctrl_evt_display_none ());
            }

#ifdef APP_DVBT_SUPPORT

            /* retry getting events if the number of events in current page in less than 1 */
            if ((t_g_ctrl.ui2_events_crnt_page <= 1) &&
                (! epg_svl_is_analog_chn ())) /* not a analog channel */
            {
                /* start timer to retry getting events */
                RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_retry,
                                             TIMER_DELAY_RETRY,
                                             X_TIMER_FLAG_ONCE));
            }

#else /* ATSC */

            /* retry getting events if the number of events in current page in less than 0 */
            if (t_g_ctrl.ui2_events_crnt_page == 0)
            {
                /* start timer to retry getting events */
                RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_retry,
                                             TIMER_DELAY_RETRY,
                                             X_TIMER_FLAG_ONCE));
            }

#endif /* APP_DVBT_SUPPORT */

            /* estimate available hours */
            RET_ON_ERR (_epg_ctrl_dt_estimate_avail_time (TRUE));

            /* update scrolling images of program list */
            RET_ON_ERR (_epg_ctrl_prg_lst_update_scroll_images ());

            /* reset counters */
            t_g_ctrl.ui2_events_req = 0;
            t_g_ctrl.ui2_events_cb  = 0;
        }
    }

    return  0;
}

#ifdef APP_EPG_THEME_SEARCH

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_help_lst_show_theme_search
 *
 * Description: The function updates help for theme search.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_help_lst_update_dvb_help (BOOL    b_repaint)
{
    /* set images. */
    RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_RED,    HELP_LB_IMG_BTN_RED_DISABLE));
    RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_GREEN,  HELP_LB_IMG_BTN_GREEN_DISABLE));
    RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_YELLOW, HELP_LB_IMG_BTN_YELLOW_DISABLE));
    RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_BLUE,   HELP_LB_IMG_BTN_BLUE_ENABLE));

    /* set text. */
    RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_RED,    EPG_MLM (MLM_EPG_KEY_MSG_NULL)));
    RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_GREEN,  EPG_MLM (MLM_EPG_KEY_MSG_NULL)));
    RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_YELLOW, EPG_MLM (MLM_EPG_KEY_MSG_NULL)));
    RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_BLUE,   EPG_MLM (MLM_EPG_KEY_HELP_TYPE)));

    if (b_repaint)
    {
        /* repaint help list */
        RET_ON_ERR (epg_view_help_lst_repaint ());
    }

    return  0;
}

#endif /* APP_EPG_THEME_SEARCH */

#ifndef APP_NO_COLOR_KEY

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_help_lst_reset
 *
 * Description: This function resets the help list.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_help_lst_reset (BOOL    b_repaint)
{
    /* Set NULL strings. */
    RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_RED,    EPG_MLM (MLM_EPG_KEY_MSG_NULL)));
    RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_GREEN,  EPG_MLM (MLM_EPG_KEY_MSG_NULL)));
    RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_YELLOW, EPG_MLM (MLM_EPG_KEY_MSG_NULL)));
#ifndef APP_EPG_THEME_SEARCH
    RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_BLUE,   EPG_MLM (MLM_EPG_KEY_MSG_NULL)));
#endif /* APP_EPG_THEME_SEARCH */

    /* Set disabled images. */
    RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_RED,    HELP_LB_IMG_BTN_RED_DISABLE));
    RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_GREEN,  HELP_LB_IMG_BTN_GREEN_DISABLE));
    RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_YELLOW, HELP_LB_IMG_BTN_YELLOW_DISABLE));
#ifndef APP_EPG_THEME_SEARCH
    RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_BLUE,   HELP_LB_IMG_BTN_BLUE_DISABLE));
#endif /* APP_EPG_THEME_SEARCH */

    if (b_repaint)
    {
        RET_ON_ERR (epg_view_help_lst_repaint ());
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_help_is_any_yesterday_event
 *
 * Description: The function checks if there is any event start before today.
 *
 * Inputs:  
 *
 * Outputs: -
 *
 * Returns: TRUE                   Yes - current event.
 *          FALSE                  No - not current event.
 ----------------------------------------------------------------------------*/
static BOOL _epg_ctrl_help_is_any_yesterday_event (VOID)
{
    UINT16    ui2_i;
    INT16     i2_date_idx = 0;

    /* Firstly, check events which had been callback in previous page */
    for (ui2_i = ELEM_VIEW_SIZE; ui2_i < 2 * ELEM_VIEW_SIZE; ui2_i ++)
    {
        if ((t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE) &&
            (t_g_ctrl.ab_events_cb[ui2_i]))
        {
            /* get date index of event */
            if (0 != _epg_ctrl_dt_get_date_idx (t_g_ctrl.ah_events[ui2_i], & i2_date_idx))
            {                
                return FALSE;
            }

            /* event start before today */
            if (i2_date_idx < 0)
            {
                return TRUE;
            }
        }
    }

    /* Secondly, check events which had been callback in current page */
    for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
    {
        if ((t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE) &&
            (t_g_ctrl.ab_events_cb[ui2_i]))
        {
            /* get date index of event */
            if (0 != _epg_ctrl_dt_get_date_idx (t_g_ctrl.ah_events[ui2_i], & i2_date_idx))
            {                
                return FALSE;
            }

            /* event start before today */
            if (i2_date_idx < 0)
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_help_lst_update_date_help
 *
 * Description: The function updates date help to info the end-user if the
 *              date-change function is enabled.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_help_lst_update_date_help (BOOL    b_repaint)
{
    BOOL    b_has_yesterday_event = FALSE;

    /* check whether there is any events start before today */
    /* [DTV00211994] [Bitstream]"Prev day" disappear when press DOWN repeatedly to change to next page in EPG */
    b_has_yesterday_event = _epg_ctrl_help_is_any_yesterday_event();
    
    if ((t_g_ctrl.ui2_date_num > 1) ||
        ((t_g_ctrl.ui2_date_num == 1) && (t_g_ctrl.b_event_yesterday)) ||
        ((t_g_ctrl.ui2_date_num == 1) && (b_has_yesterday_event)))
    {
        /* previous day is available */
        if ((t_g_ctrl.i2_date_idx > 0) ||
            ((t_g_ctrl.b_event_yesterday) && (t_g_ctrl.i2_date_idx > -1)) ||
            ((b_has_yesterday_event) && (t_g_ctrl.i2_date_idx > -1)))
        {
            /* set enabled image to previous day column of help list */
            RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_RED, HELP_LB_IMG_BTN_RED_ENABLE));

            /* set text to previous day column of help list */
            RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_RED,
                                                    EPG_MLM (MLM_EPG_KEY_HELP_ABBR_PREV_DAY)));
        }
        else /* previous day is unavailable */
        {
            /* set disabled image to previous day column of help list */
            RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_RED, HELP_LB_IMG_BTN_RED_DISABLE));

            /* reset text of previous day column of help list */
            RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_RED, w2s_g_null_str));
        }

        if (t_g_ctrl.i2_date_idx < (t_g_ctrl.ui2_date_num-1)) /* next day is available */
        {
            /* set enabled image to next day column of help list */
            RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_GREEN, HELP_LB_IMG_BTN_GREEN_ENABLE));

            /* set text to next day column of help list */
            RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_GREEN,
                                                    EPG_MLM (MLM_EPG_KEY_HELP_ABBR_NEXT_DAY)));
        }
        else /* next day is unavailable */
        {
            /* set disabled image to next day column of help list */
            RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_GREEN, HELP_LB_IMG_BTN_GREEN_DISABLE));

            /* reset text of next day column of help list */
            RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_GREEN, w2s_g_null_str));
        }
    }
    else /* one day only */
    {
        /* set disabled images to both previous/next day columns of help list */
        RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_RED, HELP_LB_IMG_BTN_RED_DISABLE));
        RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_GREEN, HELP_LB_IMG_BTN_GREEN_DISABLE));

        /* reset text to both previous/next day columns of help list */
        RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_RED, w2s_g_null_str));
        RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_GREEN, w2s_g_null_str));
    }

    if (b_repaint)
    {
        /* repaint help list */
        RET_ON_ERR (epg_view_help_lst_repaint ());
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_help_lst_update_date_idx
 *
 * Description: The function updates the date index of the highlighted element.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_help_lst_update_date_idx (BOOL    b_repaint)
{
    UINT16    ui2_hlt;
    INT16     i2_date_idx;

    /* get highlight index */
    RET_ON_ERR (epg_view_prg_lst_get_hlt_idx (& ui2_hlt));

    if ((ui2_hlt != WGL_LB_NULL_INDEX) && (ui2_hlt < EPG_EVT_BUFFER_SIZE)) /* validate index */
    {
        if ((t_g_ctrl.ah_events[ui2_hlt] != NULL_HANDLE) &&
            (t_g_ctrl.ab_events_cb[ui2_hlt]))
        {
            /* get date index of highlighted event */
            RET_ON_ERR (_epg_ctrl_dt_get_date_idx (t_g_ctrl.ah_events[ui2_hlt], & i2_date_idx));

            if ((t_g_ctrl.i2_date_idx != i2_date_idx) || /* date index is different */
                (! t_g_ctrl.b_date_updated)) /* the date has not been updated */
            {
                DBG_INFO (("<EPG> current date index = %d\n\r", i2_date_idx));

                t_g_ctrl.i2_date_idx = i2_date_idx;

                if (! t_g_ctrl.b_date_updated)
                {
                    /* turn on flag indicating the date has been updated */
                    t_g_ctrl.b_date_updated = TRUE;
                }

                if (b_repaint)
                {
                    /* update date help with repaint */
                    RET_ON_ERR (_epg_ctrl_help_lst_update_date_help (TRUE));
                }
            }
        }
    }

    return  0;
}

#endif /* APP_NO_COLOR_KEY */

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_help_lst_update_page_help
 *
 * Description: The function updates the page help to info the end-user if he
 *              can change the pages of descriptions.
 *
 * Inputs:  b_repaint           Repaint or not
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_help_lst_update_page_help (BOOL    b_repaint)
{
    INT32      i4_rc;
    CHAR       s_page_index[EPG_PAGE_MSG_MAX_LEN] = {0};
    UTF16_T    w2s_page_index[EPG_PAGE_MSG_MAX_LEN];

    if (t_g_ctrl.ui2_desc_page_num > 1)
    {
        c_sprintf (s_page_index,
                   "%d/%d",
                   (t_g_ctrl.ui2_desc_page_idx+1),
                   t_g_ctrl.ui2_desc_page_num);

        i4_rc = epg_str_ps_to_w2s (s_page_index,
                                   w2s_page_index,
                                   EPG_PAGE_MSG_MAX_LEN);

        if (i4_rc != UCR_OK)
        {
            w2s_page_index[0] = 0;

            DBG_ERROR (("<EPG> ERR: UTF8_T to UTF16_T failed = %d\n\r", i4_rc));
        }

        /* set text to page text */
        RET_ON_ERR (epg_view_page_txt_set_text (w2s_page_index));

        if (b_repaint)
        {
            /* repaint page text */
            RET_ON_ERR (epg_view_page_txt_repaint ());
        }

#ifndef APP_NO_COLOR_KEY

#ifndef APP_EPG_THEME_SEARCH
        if (t_g_ctrl.ui2_desc_page_idx > 0) /* page up is available */
        {
            /* set enabled image to page-up column of help list */
            RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_YELLOW, HELP_LB_IMG_BTN_YELLOW_ENABLE));

            /* set text to page-up column of help list */
            RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_YELLOW,
                                                    EPG_MLM (MLM_EPG_KEY_HELP_ABBR_PAGE_UP)));
        }
        else /* page up is unavailable */
        {
            /* set disabled image to page-up column of help list */
            RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_YELLOW, HELP_LB_IMG_BTN_YELLOW_DISABLE));

            /* reset text of page-up column of help list */
            RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_YELLOW, w2s_g_null_str));
        }

        if (t_g_ctrl.ui2_desc_page_idx < (UINT16)(t_g_ctrl.ui2_desc_page_num-1)) /* page down is available */
        {
            /* set enabled image to page-down column of help list */
            RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_BLUE, HELP_LB_IMG_BTN_BLUE_ENABLE));

            /* set text to page-down column of help list */
            RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_BLUE,
                                                    EPG_MLM (MLM_EPG_KEY_HELP_ABBR_PAGE_DOWN)));
        }
        else /* page down is unavailable */
        {
            /* set disabled image to page-down column of help list */
            RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_BLUE, HELP_LB_IMG_BTN_BLUE_DISABLE));

            /* reset text of page-down column of help list */
            RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_BLUE, w2s_g_null_str));
        }

#else /* #ifdef APP_EPG_THEME_SEARCH */

        /* set enabled image to yellow column of help list */
        RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_YELLOW, HELP_LB_IMG_BTN_YELLOW_ENABLE));

        /* set text to yellow column of help list */
        RET_ON_ERR (epg_view_help_lst_set_text (EPG_HELP_TYPE_BTN_YELLOW, EPG_MLM (MLM_EPG_KEY_HELP_DETAIL)));

#endif /* APP_EPG_THEME_SEARCH */

#endif /* #ifndef APP_NO_COLOR_KEY */

    }
    else /* one page only */
    {
        /* reset text of page text */
        RET_ON_ERR (epg_view_page_txt_set_text (w2s_g_null_str));

#ifndef APP_NO_COLOR_KEY

        /* reset yellow column of help list */
        RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_YELLOW, HELP_LB_IMG_BTN_YELLOW_DISABLE));
        RET_ON_ERR (epg_view_help_lst_set_text  (EPG_HELP_TYPE_BTN_YELLOW, w2s_g_null_str));

#ifndef APP_EPG_THEME_SEARCH
        /* reset blue column of help list */
        RET_ON_ERR (epg_view_help_lst_set_image (EPG_HELP_TYPE_BTN_BLUE, HELP_LB_IMG_BTN_BLUE_DISABLE));
        RET_ON_ERR (epg_view_help_lst_set_text  (EPG_HELP_TYPE_BTN_BLUE, w2s_g_null_str));
#endif /* APP_EPG_THEME_SEARCH */

#endif /* #ifndef APP_NO_COLOR_KEY */

    }

#ifndef APP_NO_COLOR_KEY

    if (b_repaint)
    {
        /* repaint help list */
        RET_ON_ERR (epg_view_help_lst_repaint ());
    }

#endif /* #ifndef APP_NO_COLOR_KEY */

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_passwd_display_msg
 *
 * Description: The function is used to display message to info the user that
 *              the password he inputs is incorrect. When the clean flag is set,
 *              the message will be restored according to current state.
 *
 * Inputs:  b_clean             TRUE  - clean and restore message.
 *                              FALSE - alarm message.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_passwd_display_msg (BOOL    b_clean)
{
    if (b_clean) /* clean and restore message */
    {
#ifdef APP_EPG_FULL_VIDEO
		RET_ON_ERR (epg_view_passwd_alarm_txt_set_visibility(FALSE));
		RET_ON_ERR (epg_view_passwd_alarm_txt_repaint());
#else
        if (t_g_ctrl.b_svc_input_blocked) /* input blocked */
        {
            RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_INPUT_LOCKED)));
        }
        else if (t_g_ctrl.b_svc_channel_blocked) /* channel blocked */
        {
            RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_CHANNEL_LOCKED)));
        }
        else if (t_g_ctrl.b_svc_event_blocked) /* event blocked */
        {
            RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_PROGRAM_LOCKED)));
        }
        /* CR[213618] cannot display "no signal" information in EPG after unplug tv signal line */
        /* only clear message when there is not another warning message */
        else if ((! t_g_ctrl.b_svc_signal_loss) &&
                 (! t_g_ctrl.b_svc_hidden_channel) &&
                 (! t_g_ctrl.b_svc_scrambled))
        {
            RET_ON_ERR (_epg_ctrl_video_txt_msg (NULL));
        }
#endif
    }
    else /* incorrect password message */
    {
        if ((t_g_ctrl.b_svc_input_blocked)  ||
            (t_g_ctrl.b_svc_channel_blocked)  ||
            (t_g_ctrl.b_svc_event_blocked))
        {
#ifdef APP_EPG_FULL_VIDEO
            RET_ON_ERR (epg_view_passwd_alarm_txt_set_visibility(TRUE));
            RET_ON_ERR (epg_view_passwd_alarm_txt_repaint());
#else
            RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_PASSWD_ALARM)));
#endif

            /* start password message timer */
            RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_passwd_msg,
                                         TIMER_DELAY_PASSWD_MSG,
                                         X_TIMER_FLAG_ONCE));
        } 
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_passwd_hide_frame
 *
 * Description: The function hides password frame and resets data within password
 *              frame.
 *
 * Inputs:  b_repaint           Repaint after password frame is hided.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_passwd_hide_frame (BOOL    b_repaint)
{
    UINT16    ui2_hlt;

    /* Stop password-dialog timer. */
    RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_passwd_dlg));

    /* reset password edit */
    RET_ON_ERR (epg_view_passwd_edit_set_text (w2s_g_null_str));

    /* hide password frame */
    RET_ON_ERR (epg_view_passwd_frm_hide ());

    /* turn off flag indicating the password is shown */
    t_g_ctrl.b_passwd_show = FALSE;

    /* set focus to last focus widget */
    RET_ON_ERR (epg_view_set_focus_widget (t_g_ctrl.e_widget_focus_last));

    /* assign focused widget to last focused widget */
    t_g_ctrl.e_widget_focus_crnt = t_g_ctrl.e_widget_focus_last;

    if (b_repaint)
    {
        if (t_g_ctrl.e_widget_focus_crnt == EPG_FOCUS_WIDGET_PRG_LST) /* program list */
        {
            /* get highlighted index */
            RET_ON_ERR (epg_view_prg_lst_get_hlt_idx (& ui2_hlt));

            if (ui2_hlt != WGL_LB_NULL_INDEX)
            {
                /* repaint element */
                RET_ON_ERR (epg_view_prg_lst_repaint_elems (ui2_hlt, ui2_hlt));

                /* update program description */
                RET_ON_ERR (_epg_ctrl_desc_update ());
            }
        }
        else if (t_g_ctrl.e_widget_focus_crnt == EPG_FOCUS_WIDGET_SURF_LST) /* surfing list */
        {
            /* get highlighted index */
            RET_ON_ERR (epg_view_surf_lst_get_hlt_idx (& ui2_hlt));

            if (ui2_hlt != WGL_LB_NULL_INDEX)
            {
                /* repaint element */
                RET_ON_ERR (epg_view_surf_lst_repaint_elems (ui2_hlt, ui2_hlt));
            }

            /* update program description */
            RET_ON_ERR (_epg_ctrl_desc_update ());
        }
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_passwd_input
 *
 * Description: The function handles the condition when password is input.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_passwd_input (VOID)
{
    BOOL         b_pass;
    UTF16_T      w2s_passwd[PASSWD_EDIT_MAX_WORD_LEN+1] = {0};

    /* get password in password edit */
    RET_ON_ERR (epg_view_passwd_edit_get_text (w2s_passwd, PASSWD_EDIT_MAX_WORD_LEN+1));

    /* check the length of password */
    if (epg_str_w2s_strlen (w2s_passwd) == PASSWD_EDIT_MAX_WORD_LEN)
    {
        /* thread delay */
        c_thread_delay (PASSWD_EDIT_COMPLETE_DELAY);

        /* check password */
        RET_ON_ERR (a_cfg_chk_password (w2s_passwd, & b_pass));

        if (b_pass) /* password matched */
        {
            /* Clean video message. */
            RET_ON_ERR (_epg_ctrl_video_txt_msg (NULL));

            /* unblock service */
            RET_ON_ERR (epg_svc_unblock ());

            /* hide password frame */
            RET_ON_ERR (_epg_ctrl_passwd_hide_frame (TRUE));

            /* update video text */
            if (! epg_svl_is_found ())
            {
                /* Display "no channel" message. */
                RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_NO_CHANNEL)));
            }

            /* check if there is no signal */
            if (epg_svc_is_signal_loss ())
            {
                /* Display "no signal" message. */
                RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_NO_SIGNAL)));
            }

            /* update events */
            if (t_g_ctrl.ui2_events_crnt_page > 0)
            {
                RET_ON_ERR (_epg_ctrl_evt_update ());
            }
            else
            {
                if ((t_g_ctrl.b_event_cb_complete) &&
                    (t_g_ctrl.b_svc_event_blocked)) /* Event was blocked */
                {
                    /* set "no program details" to description text */
                    RET_ON_ERR (epg_view_desc_txt_set_text (EPG_MLM (MLM_EPG_KEY_MSG_NO_EVENT_DETAIL)));

                    /* Show description frame */
                    if (t_g_ctrl.b_desc_show)
                    {
                        /* repaint description frame */
                        RET_ON_ERR (epg_view_desc_frm_repaint ());
                    }
                    else /* description frame is hide */
                    {
                        /* show description frame */
                        RET_ON_ERR (epg_view_desc_frm_show ());

                        /* turn on flag indicating description is shown */
                        t_g_ctrl.b_desc_show = TRUE;
                    }
                }
            }
        }
        else
        {
            /* display alarm message */
            RET_ON_ERR (_epg_ctrl_passwd_display_msg (FALSE));

            /* reset password edit box */
            RET_ON_ERR (epg_view_passwd_edit_set_text (w2s_g_null_str));

            /* hide password frame */
            RET_ON_ERR (_epg_ctrl_passwd_hide_frame (TRUE));
        }
    }
    else
    {
        /* reset password dialog timer. */
        RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_passwd_dlg));

        RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_passwd_dlg,
                                     TIMER_DELAY_PASSWD_DLG,
                                     X_TIMER_FLAG_ONCE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_passwd_show_frame
 *
 * Description: The function shows the password frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_passwd_show_frame (VOID)
{

#ifndef APP_NO_PWD_DLG

    /* record last focused widget */
    t_g_ctrl.e_widget_focus_last = t_g_ctrl.e_widget_focus_crnt;

    /* set focus to password edit */
    RET_ON_ERR (epg_view_set_focus_widget (EPG_FOCUS_WIDGET_PASSWD_EDIT));

    /* repaint last focus widget */
    if (t_g_ctrl.e_widget_focus_last == EPG_FOCUS_WIDGET_PRG_LST)
    {
        /* repaint program list */
        RET_ON_ERR (epg_view_prg_lst_repaint ());
    }

    /* reset description text */
    RET_ON_ERR (epg_view_desc_txt_set_text (w2s_g_null_str));

    /* repaint description text */
    RET_ON_ERR (epg_view_desc_txt_repaint ());

    /* reset page text */
    RET_ON_ERR (epg_view_page_txt_set_text (w2s_g_null_str));

    /* repaint page text */
    RET_ON_ERR (epg_view_page_txt_repaint ());

    /* reset description page data */
    t_g_ctrl.ui2_desc_page_num = 0;
    t_g_ctrl.ui2_desc_page_idx = 0;

    /* update paging help */
    RET_ON_ERR (_epg_ctrl_help_lst_update_page_help (TRUE));

    /* show password frame */
    RET_ON_ERR (epg_view_passwd_frm_show ());

    /* start password dialog timer */
    RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_passwd_dlg,
                                 TIMER_DELAY_PASSWD_DLG,
                                 X_TIMER_FLAG_ONCE));

    /* turn on flag indicating the password frame is shown */
    t_g_ctrl.b_passwd_show = TRUE;

#endif /* APP_NO_PWD_DLG */

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_prg_lst_change_page
 *
 * Description: The function changes the pages of program listing.
 *
 * Inputs:  b_prev                 TRUE - change to previous page.
 *                                 FALSE - change to next page.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_prg_lst_change_page (BOOL  b_prev)
{
    INT32             i4_rc;
    UINT16            ui2_source_idx;
    UINT16            ui2_target_idx;
    UINT16            ui2_i;
    UINT16            ui2_events;
    UINT16            ui2_hlt_idx;
    UINT16            ui2_cb_idx;
    TIME_T            t_time_start;

    if (b_prev) /* page up */
    {
        if (t_g_ctrl.ui2_events_prev_page > 0)
        {
            ui2_hlt_idx = (UINT16)(t_g_ctrl.ui2_events_prev_page - 1);
            ui2_events = t_g_ctrl.ui2_events_crnt_page + t_g_ctrl.ui2_events_prev_page;

            /* call backs are not completed */
            if (t_g_ctrl.ui2_events_cb < t_g_ctrl.ui2_events_req)
            {
                /* make up elements in previous page */
                RET_ON_ERR (_epg_ctrl_prg_lst_make_up_elems ());
            }

            /* set element number to ELEM_VIEW_SIZE */
            RET_ON_ERR (epg_view_prg_lst_set_elem_num (ELEM_VIEW_SIZE));

            if (ui2_events < ELEM_VIEW_SIZE)
            {
                /* set elements in previous page to program list */
                RET_ON_ERR (epg_view_prg_lst_set_elems (0, (UINT16)(ui2_events-1), t_g_ctrl.at_prg_elems_prev_page));

                /* clean no-data elements */
                RET_ON_ERR (epg_view_prg_lst_clr_elems (ui2_events, ELEM_VIEW_SIZE-1));
            }
            else
            {
                ui2_events = ELEM_VIEW_SIZE;

                /* set elements in previous page to program list */
                RET_ON_ERR (epg_view_prg_lst_set_elems (0, ELEM_VIEW_SIZE-1, t_g_ctrl.at_prg_elems_prev_page));
            }

            /* highlight element */
            RET_ON_ERR (epg_view_prg_lst_hlt_elem (ui2_hlt_idx));

            /* send a pseudo highlight notification to EPG if highlight index is 0 */
            if (ui2_hlt_idx == 0)
            {
                epg_app_send_msg (EPG_MSG_VIEW_WGL_PRG_LST_ELEM_HLT, NULL, 0);
            }

            /* shift event handles */
            /* replace event handles in next page with event handles in current page */
            ui2_cb_idx = (UINT16)(2*ELEM_VIEW_SIZE+t_g_ctrl.ui2_events_next_page-1);
            t_g_ctrl.ui2_events_next_page = 0;

            for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
            {
                ui2_target_idx = (UINT16)(3*ELEM_VIEW_SIZE-1-ui2_i);

                if (ui2_i < t_g_ctrl.ui2_events_prev_page)
                {
                    /* remove event handles in next page */
                    if (t_g_ctrl.ah_events[ui2_target_idx] != NULL_HANDLE)
                    {
                        if (ui2_target_idx > ui2_cb_idx)
                        {
                            t_g_ctrl.ui2_events_cb ++; /* accumulate call back */
                        }

                        epg_evt_free (t_g_ctrl.ah_events[ui2_target_idx]);
                        t_g_ctrl.ah_events[ui2_target_idx] = NULL_HANDLE;
                        t_g_ctrl.ab_events_cb[ui2_target_idx] = FALSE;
                    }
                }

                if (ui2_i < (UINT16)(ELEM_VIEW_SIZE-t_g_ctrl.ui2_events_prev_page)) /* replace with events in next page */
                {
                    ui2_source_idx = (UINT16)(3*ELEM_VIEW_SIZE-1-(ui2_i+t_g_ctrl.ui2_events_prev_page));
                    t_g_ctrl.ah_events[ui2_target_idx] = t_g_ctrl.ah_events[ui2_source_idx];
                    t_g_ctrl.ab_events_cb[ui2_target_idx] = t_g_ctrl.ab_events_cb[ui2_source_idx];
                }
                else /* replace with events in current page */
                {
                    ui2_source_idx = (UINT16)(ELEM_VIEW_SIZE-1-ui2_i+(ELEM_VIEW_SIZE-t_g_ctrl.ui2_events_prev_page));
                    t_g_ctrl.ah_events[ui2_target_idx] = t_g_ctrl.ah_events[ui2_source_idx];
                    t_g_ctrl.ab_events_cb[ui2_target_idx] = t_g_ctrl.ab_events_cb[ui2_source_idx];
                }

                /* free elements in next page */
                _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_next_page[ELEM_VIEW_SIZE-1-ui2_i]);

                if (t_g_ctrl.ah_events[ui2_target_idx] == NULL_HANDLE)
                {
                    t_g_ctrl.ab_events_cb[ui2_target_idx] = FALSE;
                }
                else if ((t_g_ctrl.ah_events[ui2_target_idx] != NULL_HANDLE) &&
                         (t_g_ctrl.ab_events_cb[ui2_target_idx] == TRUE))
                {
                    /* get elements for next page */
                    i4_rc = _epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_next_page[ELEM_VIEW_SIZE-1-ui2_i],
                                                    ui2_target_idx);

                    if (i4_rc == EPGR_OK)
                    {
                        /* accumulate the number of events in next page */
                        t_g_ctrl.ui2_events_next_page ++;
                    }
                    else
                    {
                        DBG_ERROR (("<EPG> ERR: get element data failed = %d\n\r", i4_rc));
                    }
                }
            }

            /* replace event handles in current page with event handles in previous page */
            t_g_ctrl.ui2_events_crnt_page = 0;

            for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
            {
                ui2_target_idx = (UINT16)(ELEM_VIEW_SIZE-1-ui2_i);

                if (ui2_i < (UINT16)((ELEM_VIEW_SIZE-t_g_ctrl.ui2_events_prev_page))) /* replace with events in current page */
                {
                    ui2_source_idx = (UINT16)(ELEM_VIEW_SIZE-1-(ui2_i+t_g_ctrl.ui2_events_prev_page));
                    t_g_ctrl.ah_events[ui2_target_idx] = t_g_ctrl.ah_events[ui2_source_idx];
                    t_g_ctrl.ab_events_cb[ui2_target_idx] = t_g_ctrl.ab_events_cb[ui2_source_idx];
                }
                else /* replace with events in previous page */
                {
                    ui2_source_idx = (UINT16)(2*ELEM_VIEW_SIZE-1-ui2_i+(ELEM_VIEW_SIZE-t_g_ctrl.ui2_events_prev_page));
                    t_g_ctrl.ah_events[ui2_target_idx] = t_g_ctrl.ah_events[ui2_source_idx];
                    t_g_ctrl.ab_events_cb[ui2_target_idx] = t_g_ctrl.ab_events_cb[ui2_source_idx];

                    t_g_ctrl.ah_events[ui2_source_idx] = NULL_HANDLE;
                    t_g_ctrl.ab_events_cb[ui2_source_idx] = FALSE;
                }

                if (t_g_ctrl.ah_events[ui2_target_idx] == NULL_HANDLE)
                {
                    t_g_ctrl.ab_events_cb[ui2_target_idx] = FALSE;
                }
                else if ((t_g_ctrl.ah_events[ui2_target_idx] != NULL_HANDLE) &&
                         (t_g_ctrl.ab_events_cb[ui2_target_idx] == TRUE))
                {
                    /* accumulate events number in current page */
                    t_g_ctrl.ui2_events_crnt_page ++;
                }
            }

            /* set events in previous page to NULL handles */
            t_g_ctrl.ui2_events_prev_page = 0;

            for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
            {
                ui2_target_idx = (UINT16)(ELEM_VIEW_SIZE+ui2_i);

                if (t_g_ctrl.ah_events[ui2_target_idx] != NULL_HANDLE)
                {
                    t_g_ctrl.ui2_events_cb ++; /* accumulate call back */

                    epg_evt_free (t_g_ctrl.ah_events[ui2_target_idx]);
                    t_g_ctrl.ah_events[ui2_target_idx] = NULL_HANDLE;
                }

                t_g_ctrl.ab_events_cb[ui2_target_idx] = FALSE;

                /* free elements in previous page */
                _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_i]);
            }

            /* get starting time of the first event in current page */
            i4_rc = epg_evt_get_start_time (t_g_ctrl.ah_events[0], & t_time_start);

            if (i4_rc == 0)
            {
                /* repaint program list */
                RET_ON_ERR (epg_view_prg_lst_repaint ());

                /* set element number */
                RET_ON_ERR (epg_view_prg_lst_set_elem_num (ui2_events));

                /* update program list but not clean data */
                RET_ON_ERR (_epg_ctrl_prg_lst_update (t_time_start, FALSE));
            }
            else
            {
                /* update program listing and clean data */
                RET_ON_ERR (_epg_ctrl_prg_lst_update (0, TRUE));
            }

            /* update scroll images */
            RET_ON_ERR (_epg_ctrl_prg_lst_update_scroll_images ());
        }
    }
    else /* page down */
    {
        if (t_g_ctrl.ui2_events_next_page > 0 &&
            t_g_ctrl.ui2_events_crnt_page == ELEM_VIEW_SIZE)
        {
            ui2_events = t_g_ctrl.ui2_events_next_page;

            /* set elements in next page to program list */
            RET_ON_ERR (epg_view_prg_lst_set_elems (0, (UINT16)(ui2_events-1), t_g_ctrl.at_prg_elems_next_page));

            /* clean no-data elements */
            if (ui2_events < ELEM_VIEW_SIZE)
            {
                RET_ON_ERR (epg_view_prg_lst_clr_elems (ui2_events, ELEM_VIEW_SIZE-1));
            }

            /* highlight first element */
            RET_ON_ERR (epg_view_prg_lst_hlt_elem (0));

            /* shift event handles */
            /* replace event handles in previous page with event handles in current page */
            ui2_cb_idx = (UINT16)(2*ELEM_VIEW_SIZE-t_g_ctrl.ui2_events_prev_page);

            for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
            {
                ui2_source_idx = ui2_i;
                ui2_target_idx = (UINT16)(ELEM_VIEW_SIZE+ui2_i);

                if (t_g_ctrl.ah_events[ui2_target_idx] != NULL_HANDLE)
                {
                    if (ui2_target_idx < ui2_cb_idx)
                    {
                        t_g_ctrl.ui2_events_cb ++; /* accumulate call back */
                    }

                    epg_evt_free (t_g_ctrl.ah_events[ui2_target_idx]);
                    t_g_ctrl.ah_events[ui2_target_idx] = NULL_HANDLE;
                    t_g_ctrl.ab_events_cb[ui2_target_idx] = FALSE;
                }

                t_g_ctrl.ah_events[ui2_target_idx] = t_g_ctrl.ah_events[ui2_source_idx];
                t_g_ctrl.ab_events_cb[ui2_target_idx] = t_g_ctrl.ab_events_cb[ui2_source_idx];

                /* free elements in previous page */
                _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_i]);

                if (t_g_ctrl.ah_events[ui2_target_idx] == NULL_HANDLE)
                {
                    t_g_ctrl.ab_events_cb[ui2_target_idx] = FALSE;
                }
                else if ((t_g_ctrl.ah_events[ui2_target_idx] != NULL_HANDLE) &&
                         (t_g_ctrl.ab_events_cb[ui2_target_idx] == TRUE))
                {
                    /* get elements for previous page */
                    i4_rc = _epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_i],
                                                        ui2_target_idx);

                    if (i4_rc != 0)
                    {
                        DBG_ERROR (("<EPG> ERR: get program element failed = %d\n\r", i4_rc));
                    }
                }
            }

            /* replace event handles in current page with event handles in next page */
            for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
            {
                ui2_source_idx = (UINT16)(2*ELEM_VIEW_SIZE+ui2_i);
                ui2_target_idx = ui2_i;

                t_g_ctrl.ah_events[ui2_target_idx] = t_g_ctrl.ah_events[ui2_source_idx];
                t_g_ctrl.ab_events_cb[ui2_target_idx] = t_g_ctrl.ab_events_cb[ui2_source_idx];

                if (t_g_ctrl.ah_events[ui2_target_idx] == NULL_HANDLE)
                {
                    t_g_ctrl.ab_events_cb[ui2_target_idx] = FALSE;
                }
            }

            /* set events in next page to NULL handles */
            for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
            {
                ui2_target_idx = (UINT16)(2*ELEM_VIEW_SIZE+ui2_i);

                t_g_ctrl.ah_events[ui2_target_idx] = NULL_HANDLE;
                t_g_ctrl.ab_events_cb[ui2_target_idx] = FALSE;

                /* free elements in next page */
                _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_i]);
            }

            /* set the number of events */
            t_g_ctrl.ui2_events_prev_page = t_g_ctrl.ui2_events_crnt_page;
            t_g_ctrl.ui2_events_crnt_page = ui2_events;
            t_g_ctrl.ui2_events_next_page = 0;

            /* get starting time of the first event in current page */
            i4_rc = epg_evt_get_start_time (t_g_ctrl.ah_events[0], & t_time_start);

            if (i4_rc == 0)
            {
                /* repaint program list */
                RET_ON_ERR (epg_view_prg_lst_repaint ());

                /* update program list but not clean data */
                RET_ON_ERR (_epg_ctrl_prg_lst_update (t_time_start, FALSE));

                /* set the number of elements to program list */
                RET_ON_ERR (epg_view_prg_lst_set_elem_num (ui2_events));
            }
            else
            {
                /* update program list and clean data */
                RET_ON_ERR (_epg_ctrl_prg_lst_update (0, TRUE));
            }

            /* update scroll images */
            RET_ON_ERR (_epg_ctrl_prg_lst_update_scroll_images ());
        }
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_prg_lst_clean_elems
 *
 * Description: The function cleans up all the elements in current page of
 *              program listing.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_prg_lst_clean_elems (BOOL    b_repaint)
{
    UINT16  ui2_hlt_idx;

    /* get highlighted index */
    RET_ON_ERR (epg_view_prg_lst_get_hlt_idx (& ui2_hlt_idx));

    if (ui2_hlt_idx != WGL_LB_NULL_INDEX)
    {
        /* un-highlight element */
        RET_ON_ERR (epg_view_prg_lst_unhlt_elem (ui2_hlt_idx));
    }

    /* set element number to ELEM_VIEW_SIZE */
    RET_ON_ERR (epg_view_prg_lst_set_elem_num (ELEM_VIEW_SIZE));

    /* clean all elements */
    RET_ON_ERR (epg_view_prg_lst_clr_elems (0, ELEM_VIEW_SIZE-1));

    /* set element number to 0 */
    RET_ON_ERR (epg_view_prg_lst_set_elem_num (0));

    /* disable page up/down images without repainting */
    RET_ON_ERR (epg_view_prg_lst_set_paging_images (FALSE, FALSE, FALSE));

    if (b_repaint)
    {
        /* repaint program list */
        RET_ON_ERR (epg_view_prg_lst_repaint ());
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_prg_lst_free_elem
 *
 * Description: The function frees a given program element.
 *
 * Inputs:  pt_elem             Element data.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_prg_lst_free_elem (WGL_LB_ELEM_DATA_T*    pt_elem)
{
    if (pt_elem->at_items != NULL)
    {
        /* Free date. */
        if (pt_elem->at_items[0].pw2s_text != NULL)
        {
            c_mem_free (pt_elem->at_items[0].pw2s_text);
            pt_elem->at_items[0].pw2s_text = NULL;
        }

        /* Free start time. */
        if (pt_elem->at_items[1].pw2s_text != NULL)
        {
            c_mem_free (pt_elem->at_items[1].pw2s_text);
            pt_elem->at_items[1].pw2s_text = NULL;
        }

        /* Free title. */
        if (pt_elem->at_items[2].pw2s_text != NULL)
        {
            c_mem_free (pt_elem->at_items[2].pw2s_text);
            pt_elem->at_items[2].pw2s_text = NULL;
        }

#ifndef APP_EPG_ICON_SEP

        /* Free lock indicator. */
        if (pt_elem->at_items[3].pt_img_suit != NULL)
        {
            c_mem_free (pt_elem->at_items[3].pt_img_suit);
            pt_elem->at_items[3].pt_img_suit = NULL;
        }

        /* Free cc flag. */
        if (pt_elem->at_items[4].pt_img_suit != NULL)
        {
            c_mem_free (pt_elem->at_items[4].pt_img_suit);
            pt_elem->at_items[4].pt_img_suit = NULL;
        }

#endif /* APP_EPG_ICON_SEP */

        /* Free element. */
        c_mem_free(pt_elem->at_items);
        pt_elem->at_items = NULL;
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_prg_lst_get_elem
 *
 * Description: The function gets program element data, including date, start
 *              time, event title, lock indicator and cc flag.
 *
 * Inputs:  pt_elem             Element data.
 *          ui2_idx             Event index.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_prg_lst_get_elem (WGL_LB_ELEM_DATA_T*    pt_elem,
                                         UINT16                 ui2_idx)
{
    INT32                      i4_rc;
    DTG_T                      t_crnt_loc_dtg;
    DTG_T                      t_evt_loc_dtg;
    CHAR*                      ps_title;
    UTF16_T*                   pw2s_title;
    UTF16_T*                   pw2s_date;
    UTF16_T*                   pw2s_time_start;
    SIZE_T                     z_info_size = 0;
    BOOL                       b_found_date;

#ifndef APP_EPG_ICON_SEP

    BOOL                       b_exceed;
    BOOL                       b_found_caption;

#endif /* APP_EPG_ICON_SEP */

#ifndef APP_EPG_ICON_SEP

    WGL_LB_ITEM_IMG_SUIT_T*    pt_lock_img_suit;
    WGL_LB_ITEM_IMG_SUIT_T*    pt_caption_img_suit;

#endif /* APP_EPG_ICON_SEP */

    if ((ui2_idx >= EPG_EVT_BUFFER_SIZE)             || /* invalid index */
        (t_g_ctrl.ah_events[ui2_idx] == NULL_HANDLE) || /* without handle */
        (t_g_ctrl.ab_events_cb[ui2_idx] == FALSE))      /* has been called back */
    {
        pt_elem->at_items = NULL;

        return  EPGR_OK;
    }

    /* allocate items */
    pt_elem->at_items = (WGL_LB_ITEM_DATA_T*) c_mem_alloc (PRG_LB_COL_NUM * sizeof(WGL_LB_ITEM_DATA_T));

    if (pt_elem->at_items == NULL) /* out of memory */
    {
        DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

        return EPGR_OUT_OF_MEM;
    }

    /* reset items data */
    c_memset (pt_elem->at_items, 0, PRG_LB_COL_NUM * sizeof(WGL_LB_ITEM_DATA_T));

    b_found_date = FALSE;

    /* get local time */
    i4_rc = epg_dt_get_loc_dtg (& t_crnt_loc_dtg);

    if (i4_rc == DTR_OK)
    {
        /* get local start time */
        i4_rc = epg_dt_get_start_loc_dtg_by_event (t_g_ctrl.ah_events[ui2_idx], & t_evt_loc_dtg);

        if (i4_rc == EVCTXR_OK)
        {
            /* allocate date buffer */
            pw2s_date = (UTF16_T*) c_mem_alloc (sizeof(UTF16_T) * EPG_DT_DATE_MAX_LEN);

            if (pw2s_date == NULL)
            {
                /* free program element */
                _epg_ctrl_prg_lst_free_elem (pt_elem);

                DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

                return  EPGR_OUT_OF_MEM;
            }

            /* get day of week */
            _epg_ctrl_dt_get_dow (& t_crnt_loc_dtg, & t_evt_loc_dtg, pw2s_date);

            /* allocate buffer for start time */
            pw2s_time_start = (UTF16_T*) c_mem_alloc (sizeof(UTF16_T) * EPG_DT_HOUR_MIN_MAX_LEN);

            if (pw2s_time_start == NULL) /* out of memory */
            {
                /* free date buffer */
                c_mem_free (pw2s_date);

                /* free program element */
                _epg_ctrl_prg_lst_free_elem (pt_elem);

                DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

                return  EPGR_OUT_OF_MEM;
            }

            /* get hour:minute */
            i4_rc = epg_dt_get_time_str (t_evt_loc_dtg,
                                         EPG_TIME_MODE_HM,
                                         pw2s_time_start);

            if (i4_rc == 0)
            {
                pt_elem->at_items[0].pw2s_text = pw2s_date;
                pt_elem->at_items[1].pw2s_text = pw2s_time_start;

                /* turn on date found flag */
                b_found_date = TRUE;
            }
            else
            {
                DBG_ERROR (("<EPG> ERR: get format time failed = %d\n\r", i4_rc));

                c_mem_free (pw2s_date);
                c_mem_free (pw2s_time_start);
            }
        }
    }

    if (! b_found_date) /* date not found */
    {
        pt_elem->at_items[0].pw2s_text = NULL;
        pt_elem->at_items[1].pw2s_text = NULL;
    }

    /* get event title length */
    i4_rc = epg_evt_get_title_len (t_g_ctrl.ah_events[ui2_idx], & z_info_size);

    if (i4_rc == EVCTXR_OK && z_info_size != 0) /* event title found */
    {
        /* allocate UTF8 buffer for event title */
        ps_title = (CHAR*) c_mem_alloc (z_info_size * sizeof(CHAR));

        if (ps_title == NULL)
        {
            /* free element */
            _epg_ctrl_prg_lst_free_elem (pt_elem);

            DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

            return  EPGR_OUT_OF_MEM;
        }

        /* get event title */
        i4_rc = epg_evt_get_title (t_g_ctrl.ah_events[ui2_idx], z_info_size, ps_title);

        if (i4_rc == EVCTXR_OK)
        {
            /* Trim spaces */
            epg_str_trim (ps_title);

            if (c_strlen (ps_title) > 0) /* The length of title must be greater than 0 */
            {
                /* allocate UTF16 buffer for event title */
                pw2s_title = (UTF16_T*) c_mem_alloc (z_info_size * sizeof(UTF16_T));

                if (pw2s_title == NULL) /* out of memory */
                {
                    /* free UTF8 buffer for event title */
                    c_mem_free (ps_title);

                    _epg_ctrl_prg_lst_free_elem (pt_elem);

                    DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

                    return  EPGR_OUT_OF_MEM;
                }

                i4_rc = epg_str_ps_to_w2s (ps_title,
                                           pw2s_title,
                                           z_info_size);

                /* error handling */
                if (i4_rc == UCR_NO_ENOUGH_BUFFER) /* buffer insufficient */
                {
                    DBG_ERROR (("<EPG> ERR: UTF8_T to UTF16_T failed = %d\n\r", i4_rc));

                    pw2s_title[z_info_size-1] = 0;

                    i4_rc = UCR_OK;
                }
                else if (i4_rc != UCR_OK)
                {
                    DBG_ERROR (("<EPG> ERR: UTF8_T to UTF16_T failed = %d\n\r", i4_rc));

                    pw2s_title[0] = 0; /* NULL string */

                    i4_rc = UCR_OK;
                }

                if (i4_rc == UCR_OK)
                {
                    pt_elem->at_items[2].pw2s_text = pw2s_title;
                }
            }
            else /* no program title */
            {
                DBG_INFO (("<EPG> no program title\n\r"));

                /* display (no program title.) if there is no title */
                z_info_size = epg_str_w2s_strlen (EPG_MLM (MLM_EPG_KEY_MSG_NO_EVENT_TITLE)) + 1;

                /* allocate UTF16 buffer for event title */
                pw2s_title = (UTF16_T*) c_mem_alloc (z_info_size * sizeof(UTF16_T));

                if (pw2s_title == NULL) /* out of memory */
                {
                    /* free UTF8 buffer for event title */
                    c_mem_free (ps_title);

                    _epg_ctrl_prg_lst_free_elem (pt_elem);

                    DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

                    return  EPGR_OUT_OF_MEM;
                }

                epg_str_w2s_strcpy (pw2s_title, EPG_MLM (MLM_EPG_KEY_MSG_NO_EVENT_TITLE));

                pt_elem->at_items[2].pw2s_text = pw2s_title;
            }
        }

        /* free memory */
        c_mem_free (ps_title);
    }
    else
    {
        DBG_INFO (("<EPG> no program title\n\r"));

        /* display (no program title.) if there is no title */
        z_info_size = epg_str_w2s_strlen (EPG_MLM (MLM_EPG_KEY_MSG_NO_EVENT_TITLE)) + 1;

        /* allocate UTF16 buffer for event title */
        pw2s_title = (UTF16_T*) c_mem_alloc (z_info_size * sizeof(UTF16_T));

        if (pw2s_title == NULL) /* out of memory */
        {
            _epg_ctrl_prg_lst_free_elem (pt_elem);

            DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

            return  EPGR_OUT_OF_MEM;
        }

        epg_str_w2s_strcpy (pw2s_title, EPG_MLM (MLM_EPG_KEY_MSG_NO_EVENT_TITLE));

        pt_elem->at_items[2].pw2s_text = pw2s_title;
    }
#if 0
    else /* Something error? */
    {
        DBG_ERROR (("<EPG> ERR: get title failed = %d\n\r", i4_rc));

        /* Set title to NULL. */
        pt_elem->at_items[2].pw2s_text = NULL;

        /* Return without processing lock and cc indicators. */
        return EPGR_OK;
    }
#endif /* # if 0 */

#ifndef APP_EPG_ICON_SEP

    /* allocate image suit for lock indicator */
    pt_lock_img_suit = (WGL_LB_ITEM_IMG_SUIT_T*) c_mem_alloc (sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    if (pt_lock_img_suit == NULL) /* out of memory */
    {
        _epg_ctrl_prg_lst_free_elem (pt_elem);

        DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

        return  EPGR_OUT_OF_MEM;
    }

    /* content advisory */
    b_exceed = FALSE;

    i4_rc = _epg_ctrl_check_rating (t_g_ctrl.ah_events[ui2_idx], & b_exceed);

    if (i4_rc != EPGR_OK)
    {
        DBG_ERROR (("<EPG> ERR: check rating failed = %d\n\r", i4_rc));
    }

    if (b_exceed) /* exceed rating */
    {
        pt_lock_img_suit->h_normal                      = h_g_epg_img_lock;
        pt_lock_img_suit->h_disable                     = h_g_epg_img_lock;
        pt_lock_img_suit->h_highlight                   = h_g_epg_img_lock_hlt;
        pt_lock_img_suit->h_highlight_unfocus           = h_g_epg_img_lock_hlt_uf;
        pt_lock_img_suit->h_pushed                      = h_g_epg_img_lock;
        pt_lock_img_suit->h_selected                    = h_g_epg_img_lock;
        pt_lock_img_suit->h_selected_disable            = h_g_epg_img_lock;
        pt_lock_img_suit->h_selected_highlight          = h_g_epg_img_lock_hlt;
        pt_lock_img_suit->h_selected_highlight_unfocus  = h_g_epg_img_lock;
        pt_lock_img_suit->h_selected_pushed             = h_g_epg_img_lock;

        pt_elem->at_items[3].pt_img_suit                = pt_lock_img_suit;
    }
    else
    {
        pt_lock_img_suit->h_normal                      = NULL_HANDLE;
        pt_lock_img_suit->h_disable                     = NULL_HANDLE;
        pt_lock_img_suit->h_highlight                   = NULL_HANDLE;
        pt_lock_img_suit->h_highlight_unfocus           = NULL_HANDLE;
        pt_lock_img_suit->h_pushed                      = NULL_HANDLE;
        pt_lock_img_suit->h_selected                    = NULL_HANDLE;
        pt_lock_img_suit->h_selected_disable            = NULL_HANDLE;
        pt_lock_img_suit->h_selected_highlight          = NULL_HANDLE;
        pt_lock_img_suit->h_selected_highlight_unfocus  = NULL_HANDLE;
        pt_lock_img_suit->h_selected_pushed             = NULL_HANDLE;

        pt_elem->at_items[3].pt_img_suit                = pt_lock_img_suit;
    }

    /* allocate image suit for cc flag */
    pt_caption_img_suit = (WGL_LB_ITEM_IMG_SUIT_T*) c_mem_alloc (sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    if (pt_caption_img_suit == NULL) /* out of memory */
    {
        /* free element */
        _epg_ctrl_prg_lst_free_elem (pt_elem);

        DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

        return  EPGR_OUT_OF_MEM;
    }

    /* cc flag */
    if (_epg_ctrl_evt_is_crnt (t_g_ctrl.ah_events[ui2_idx] ) && b_exceed) /* current event */
    {
        b_found_caption = FALSE;
    }
    else
    {
        b_found_caption = _epg_ctrl_evt_is_caption_avail (t_g_ctrl.ah_events[ui2_idx]);
    }

    if (b_found_caption) /* caption is found */
    {
        pt_caption_img_suit->h_normal                      = h_g_epg_img_caption;
        pt_caption_img_suit->h_disable                     = h_g_epg_img_caption;
        pt_caption_img_suit->h_highlight                   = h_g_epg_img_caption_hlt;
        pt_caption_img_suit->h_highlight_unfocus           = h_g_epg_img_caption_hlt_uf;
        pt_caption_img_suit->h_pushed                      = h_g_epg_img_caption;
        pt_caption_img_suit->h_selected                    = h_g_epg_img_caption;
        pt_caption_img_suit->h_selected_disable            = h_g_epg_img_caption;
        pt_caption_img_suit->h_selected_highlight          = h_g_epg_img_caption_hlt;
        pt_caption_img_suit->h_selected_highlight_unfocus  = h_g_epg_img_caption;
        pt_caption_img_suit->h_selected_pushed             = h_g_epg_img_caption;

        pt_elem->at_items[4].pt_img_suit                   = pt_caption_img_suit;
    }
    else /* caption is not available */
    {
        pt_caption_img_suit->h_normal                      = NULL_HANDLE;
        pt_caption_img_suit->h_disable                     = NULL_HANDLE;
        pt_caption_img_suit->h_highlight                   = NULL_HANDLE;
        pt_caption_img_suit->h_highlight_unfocus           = NULL_HANDLE;
        pt_caption_img_suit->h_pushed                      = NULL_HANDLE;
        pt_caption_img_suit->h_selected                    = NULL_HANDLE;
        pt_caption_img_suit->h_selected_disable            = NULL_HANDLE;
        pt_caption_img_suit->h_selected_highlight          = NULL_HANDLE;
        pt_caption_img_suit->h_selected_highlight_unfocus  = NULL_HANDLE;
        pt_caption_img_suit->h_selected_pushed             = NULL_HANDLE;

        pt_elem->at_items[4].pt_img_suit                   = pt_caption_img_suit;
    }

 #endif /* APP_EPG_ICON_SEP */

    return (i4_rc == 0) ? EPGR_OK : EPGR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_prg_lst_make_up_elems
 *
 * Description: The function makes up the events in previous page.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_prg_lst_make_up_elems (VOID)
{
    UINT16    ui2_i;
    UINT16    ui2_to_add;

    if ((t_g_ctrl.ui2_events_prev_page > 0) &&
        (t_g_ctrl.ui2_events_prev_page < ELEM_VIEW_SIZE))
    {
        ui2_to_add = (UINT16)(ELEM_VIEW_SIZE - t_g_ctrl.ui2_events_prev_page);

        /* free elements in previous page */
        for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
        {
            /* free program element */
            _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_i]);
        }

        /* re-cache elements in previous page */
        for (ui2_i = 0; ui2_i < t_g_ctrl.ui2_events_prev_page; ui2_i ++)
        {
            /* get program element */
            RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_i],
                                                    (UINT16)(ELEM_VIEW_SIZE+ui2_i+ui2_to_add)));
        }

        /* make up elements with events in current page */
        for (ui2_i = 0; ui2_i < ui2_to_add; ui2_i ++)
        {
            if (t_g_ctrl.ab_events_cb[ui2_i] == TRUE) /* event has been called back */
            {
                if ((ui2_i + t_g_ctrl.ui2_events_prev_page) < ELEM_VIEW_SIZE)
                {
                    RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_i+t_g_ctrl.ui2_events_prev_page], ui2_i));
                }
            }
        }
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_prg_lst_reach_boundary
 *
 * Description: This function handles the conditions when the highlight bar
 *              reached the boundary of program list.
 *
 * Inputs:  ui4_type               Message type of EPG_MSG_MODEL_T.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_prg_lst_reach_boundary (BOOL    b_top)
{
    /* Disable control keys of program list. */
    RET_ON_ERR (epg_view_prg_lst_enable_control_key (FALSE));

    if (b_top) /* Reach top boundary. */
    {
        /* Change to previous page. */
        RET_ON_ERR (_epg_ctrl_prg_lst_change_page (TRUE));
    }
    else /* Reach button boundary. */
    {
        /* Change to next page. */
        RET_ON_ERR (_epg_ctrl_prg_lst_change_page (FALSE));
    }

    /* Enable control keys of program list. */
    RET_ON_ERR (epg_view_prg_lst_enable_control_key (TRUE));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_prg_lst_elem_hlted
 *
 * Description: This function handles the conditions when the element of program
 *              list is highlighted.
 *
 * Inputs:  ui4_type               Message type of EPG_MSG_MODEL_T.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_prg_lst_elem_hlted (VOID)
{

#ifndef APP_NO_COLOR_KEY

    if (t_g_ctrl.b_date_changing) /* changing date */
    {
        /* update date index without repaint */
        RET_ON_ERR (_epg_ctrl_help_lst_update_date_idx (FALSE));
    }
    else
    {
        /* update date index with repaint */
        RET_ON_ERR (_epg_ctrl_help_lst_update_date_idx (TRUE));
    }

#endif /* APP_NO_COLOR_KEY */

    if (t_g_ctrl.b_btn_prg_held) /* program button is being held */
    {
        if (t_g_ctrl.b_desc_show) /* description is shown */
        {
            /* hide description frame */
            RET_ON_ERR (_epg_ctrl_desc_hide_frame ());

            /* update page help */
            RET_ON_ERR (_epg_ctrl_help_lst_update_page_help (TRUE));
        }
    }
    else
    {
        if ((! t_g_ctrl.b_desc_keep) || /* description is not asked to be kept */
            (! t_g_ctrl.b_desc_show))   /* description is not shown */
        {
            /* update program description */
            RET_ON_ERR (_epg_ctrl_desc_update ());
        }
    }

    if (t_g_ctrl.b_desc_keep) /* description is asked to be kept */
    {
        /* turn off description-keep flag */
        t_g_ctrl.b_desc_keep = FALSE;
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_prg_lst_shift_elems
 *
 * Description: This function shifts events upward one slot.
 *
 * Inputs:  b_found_event_0        The first event in current page is found or
 *                                 not.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_prg_lst_shift_elems (BOOL  b_found_event_0)
{
    UINT16  ui2_i;
    UINT16  ui2_hlt;
    UINT16  ui2_evt_idx;

    DBG_INFO (("<EPG> shift events (current event exists = %d)\n\r", b_found_event_0));

    if (t_g_ctrl.b_passwd_show) /* password frame is shown */
    {
        /* hide password frame */
        RET_ON_ERR (_epg_ctrl_passwd_hide_frame (TRUE));
    }

    if (b_found_event_0)
    {
        /* delete first event in previous page */
        if (t_g_ctrl.ah_events[ELEM_VIEW_SIZE] != NULL_HANDLE)
        {
            /* free event handle */
            epg_evt_free (t_g_ctrl.ah_events[ELEM_VIEW_SIZE]);
            t_g_ctrl.ah_events[ELEM_VIEW_SIZE] = NULL_HANDLE;

            if (t_g_ctrl.ab_events_cb[ELEM_VIEW_SIZE] == TRUE) /* event has been called back */
            {
                /* decrease the number of event in previous page */
                t_g_ctrl.ui2_events_prev_page --;
            }
            else /* event has not been called back */
            {
                /* accumulate event call backs */
                t_g_ctrl.ui2_events_cb ++;
            }
        }

        /* shift events in previous page */
        for (ui2_i = ELEM_VIEW_SIZE; ui2_i < 2*ELEM_VIEW_SIZE-1; ui2_i ++)
        {
            /* copy event handle and call back flag */
            t_g_ctrl.ah_events[ui2_i] = t_g_ctrl.ah_events[ui2_i+1];
            t_g_ctrl.ab_events_cb[ui2_i] = t_g_ctrl.ab_events_cb[ui2_i+1];

            ui2_evt_idx = (UINT16)(ui2_i - ELEM_VIEW_SIZE);

            if (t_g_ctrl.at_prg_elems_prev_page[ui2_evt_idx].at_items != NULL)
            {
                /* free elements in previous page */
                _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_evt_idx]);
            }

            if ((t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE) &&
                (t_g_ctrl.ab_events_cb[ui2_i]))
            {
                /* update elements in previous page */
                RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_evt_idx],
                                                        ui2_i));
            }
        }

        /* replace last event in previous page with current event */
        t_g_ctrl.ah_events[2*ELEM_VIEW_SIZE-1] = t_g_ctrl.ah_events[0];
        t_g_ctrl.ab_events_cb[2*ELEM_VIEW_SIZE-1] = t_g_ctrl.ab_events_cb[0];

        if (t_g_ctrl.at_prg_elems_prev_page[ELEM_VIEW_SIZE-1].at_items != NULL)
        {
            /* free elements in previous page */
            _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_prev_page[ELEM_VIEW_SIZE-1]);
        }

        if ((t_g_ctrl.ah_events[2*ELEM_VIEW_SIZE-1] != NULL_HANDLE) &&
            (t_g_ctrl.ab_events_cb[2*ELEM_VIEW_SIZE-1]))
        {
            /* update elements in previous page */
            RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_prev_page[ELEM_VIEW_SIZE-1],
                                                    2*ELEM_VIEW_SIZE-1));

            /* accumulate the number of events in previous page */
            t_g_ctrl.ui2_events_prev_page ++;
        }
    }
    else /* the first event in current page is not found */
    {
        /* free current event */
        epg_evt_free (t_g_ctrl.ah_events[0]);
        t_g_ctrl.ah_events[0] = NULL_HANDLE;
    }

    /* turn off flag indicating the program description should be kept */
    t_g_ctrl.b_desc_keep = FALSE;

    /* get current highlight index of program list */
    RET_ON_ERR (epg_view_prg_lst_get_hlt_idx (& ui2_hlt));

    if (ui2_hlt == WGL_LB_NULL_INDEX) /* no element is highlighted */
    {
        ; /* do nothing */
    }
    else if (ui2_hlt == 0) /* first element is highlighted */
    {
        /* send a pseudo element highlighted notification to EPG */
        epg_app_send_msg (EPG_MSG_VIEW_WGL_PRG_LST_ELEM_HLT, NULL, 0);
    }
    else
    {
        /* turn on flag to keep the program description (the page index will not be updated) */
        t_g_ctrl.b_desc_keep = TRUE;

        /* unhighlight current element */
        RET_ON_ERR (epg_view_prg_lst_unhlt_elem (ui2_hlt));

        /* highlight previous element */
        RET_ON_ERR (epg_view_prg_lst_hlt_elem ((UINT16)(ui2_hlt-1)));
    }

    /* shift events in current page */
    for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE-1; ui2_i ++)
    {
        /* copy event handle and call back flag */
        t_g_ctrl.ah_events[ui2_i] = t_g_ctrl.ah_events[ui2_i+1];
        t_g_ctrl.ab_events_cb[ui2_i] = t_g_ctrl.ab_events_cb[ui2_i+1];

        if ((t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE) &&
            (t_g_ctrl.ab_events_cb[ui2_i]))
        {
            if (ui2_i == (UINT16)(ui2_hlt-1))
            {
                /* repaint highlighted/unhighlighted elements */
                RET_ON_ERR (epg_view_prg_lst_repaint_elems ((UINT16)(ui2_hlt-1), ui2_hlt));
            }

            /* update elements in current page */
            RET_ON_ERR(_epg_ctrl_prg_lst_update_elem (ui2_i));
        }
    }

    /* shift the first event in next page to the last event of current page */
    t_g_ctrl.ah_events[ELEM_VIEW_SIZE-1] = t_g_ctrl.ah_events[2*ELEM_VIEW_SIZE];
    t_g_ctrl.ab_events_cb[ELEM_VIEW_SIZE-1] = t_g_ctrl.ab_events_cb[2*ELEM_VIEW_SIZE];

    if ((t_g_ctrl.ah_events[ELEM_VIEW_SIZE-1] != NULL_HANDLE) &&
        (t_g_ctrl.ab_events_cb[ELEM_VIEW_SIZE-1]))
    {
        /* update program element */
        RET_ON_ERR (_epg_ctrl_prg_lst_update_elem (ELEM_VIEW_SIZE-1));
    }

    if (t_g_ctrl.ui2_events_next_page > 0)
    {
        /* accumulate the number of events in current page */
        t_g_ctrl.ui2_events_crnt_page ++;

        /* decrease the number of events in next page */
        t_g_ctrl.ui2_events_next_page --;
    }

    /* set element number to program list */
    RET_ON_ERR (epg_view_prg_lst_set_elem_num (t_g_ctrl.ui2_events_crnt_page));

    if (t_g_ctrl.ui2_events_crnt_page > 0)
    {
        /* clean no-data elements */
        if (t_g_ctrl.ui2_events_crnt_page < ELEM_VIEW_SIZE)
        {
            /* set the number of elements of program list to ELEM_VIEW_SIZE */
            RET_ON_ERR (epg_view_prg_lst_set_elem_num (ELEM_VIEW_SIZE));

            /* clean no-data elements */
            RET_ON_ERR (epg_view_prg_lst_clr_elems (t_g_ctrl.ui2_events_crnt_page, ELEM_VIEW_SIZE-1));

            /* repaint elements */
            RET_ON_ERR (epg_view_prg_lst_repaint_elems (t_g_ctrl.ui2_events_crnt_page, ELEM_VIEW_SIZE-1));

            /* set the number of elements of program list to the number of elements in current page */
            RET_ON_ERR (epg_view_prg_lst_set_elem_num (t_g_ctrl.ui2_events_crnt_page));
        }
    }

    /* shift events in next page */
    for (ui2_i = 2*ELEM_VIEW_SIZE; ui2_i < 3*ELEM_VIEW_SIZE-1; ui2_i ++)
    {
        /* copy event handles and call back flags */
        t_g_ctrl.ah_events[ui2_i] = t_g_ctrl.ah_events[ui2_i+1];
        t_g_ctrl.ab_events_cb[ui2_i] = t_g_ctrl.ab_events_cb[ui2_i+1];

        ui2_evt_idx = (UINT16)(ui2_i - (2*ELEM_VIEW_SIZE));

        if (t_g_ctrl.at_prg_elems_next_page[ui2_evt_idx].at_items != NULL)
        {
            /* free elements in next page */
            _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_evt_idx]);
        }

        if ((t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE) &&
            (t_g_ctrl.ab_events_cb[ui2_i]))
        {
            /* get elements in next page */
            RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_evt_idx], ui2_i));
        }
    }

    /* free event handle of last event in next page and reset call back flag of it */
    t_g_ctrl.ah_events[3*ELEM_VIEW_SIZE-1] = NULL_HANDLE;
    t_g_ctrl.ab_events_cb[3*ELEM_VIEW_SIZE-1] = TRUE;

    /* reset element data of last event in next page */
    if (t_g_ctrl.at_prg_elems_next_page[ELEM_VIEW_SIZE-1].at_items != NULL)
    {
        /* free last element in next page */
        _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_next_page[ELEM_VIEW_SIZE-1]);
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_prg_lst_update
 *
 * Description: The function updates program listing.
 *
 * Inputs:  t_time_start        Start time to be queried.
 *          b_clean             Clean data or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_prg_lst_update (TIME_T    t_time_start,
                                       BOOL      b_clean)
{
    INT32             i4_rc;
    UINT16            ui2_i;
    UINT16            ui2_offset;
    UINT16            ui2_evt_idx;
    BOOL              b_prev;
    BOOL              b_load;
    BOOL              b_retrieving;
    EVCTX_OFFSET_T    t_offset;
    EVCTX_COND_T      e_cond = EVCTX_COND_AVAIL;

    DBG_INFO (("<EPG> update program list (b_clean = %d)\n\r", b_clean));

    /* Thread delay in order to get into stable state */
    c_thread_delay (500);

    /* Stop retry timer. */
    RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_retry));

    if (t_g_ctrl.b_passwd_show)
    {
        /* Hide password frame. */
        RET_ON_ERR (_epg_ctrl_passwd_hide_frame (FALSE));
    }

    if (b_clean)
    {
        /* Disable control keys of program list. */
        RET_ON_ERR (epg_view_prg_lst_enable_control_key (FALSE));

        /* Clean program text widget. */
        RET_ON_ERR (epg_view_prg_txt_set_text (w2s_g_null_str));

        /* Clean up elements of program list. */
        RET_ON_ERR (_epg_ctrl_prg_lst_clean_elems (TRUE));

        /* Free event handles. */
        for (ui2_i = 0; ui2_i < EPG_EVT_BUFFER_SIZE; ui2_i ++)
        {
            if (t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE)
            {
                epg_evt_free (t_g_ctrl.ah_events[ui2_i]);
                t_g_ctrl.ah_events[ui2_i] = NULL_HANDLE;
            }
        }

        /* Free elements in previous/next page. */
        for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
        {
            _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_i]);
            _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_i]);
        }

        /* Reset variables. */
        t_g_ctrl.ui2_events_crnt_page      = 0;
        t_g_ctrl.ui2_events_prev_page      = 0;
        t_g_ctrl.ui2_events_next_page      = 0;
        t_g_ctrl.ui2_events_req            = 0;
        t_g_ctrl.ui2_events_cb             = 0;

        c_memset (t_g_ctrl.ab_events_cb, 0, sizeof(BOOL) * EPG_EVT_BUFFER_SIZE);

        /* Disable page up/down images without repaint. */
        RET_ON_ERR (epg_view_prg_lst_set_paging_images (FALSE, FALSE, FALSE));

#ifndef APP_NO_COLOR_KEY

        if (t_g_ctrl.b_date_jumped) /* If date is already jumped, don't clean help. */
        {
            t_g_ctrl.b_date_jumped = FALSE;
        }
        else
        {
            /* Reset help. */
            RET_ON_ERR (_epg_ctrl_help_lst_reset (TRUE));
        }

#endif /* APP_NO_COLOR_KEY */

        /* Hide description frame. */
        RET_ON_ERR (_epg_ctrl_desc_hide_frame ());
    }

    /* Reset flags. */
    t_g_ctrl.b_date_updated            = FALSE;
    t_g_ctrl.b_date_changing           = FALSE;
    t_g_ctrl.b_time_avail_updated      = FALSE;
    t_g_ctrl.b_time_total_avail        = FALSE;
    t_g_ctrl.b_event_cb_complete       = FALSE;
    t_g_ctrl.b_event_shifted           = FALSE;
    t_g_ctrl.b_event_yesterday         = FALSE;
    t_g_ctrl.b_event_crnt_with_cc_info = FALSE;

    if (t_g_ctrl.b_retrieving)
    {
        /* Turn off retrieving flag. */
        t_g_ctrl.b_retrieving = FALSE;

        /* Update retrieving state. */
        RET_ON_ERR (_epg_ctrl_retrieve_update_state ());
    }

    if ((! t_g_ctrl.b_svc_signal_loss) &&   /* There is signal. */
        (! t_g_ctrl.b_svc_input_blocked) && /* Input is not blocked. */
        (! t_g_ctrl.b_svc_channel_blocked)) /* Channel is not blocked. */
    {
        /* load events */
        t_offset.e_offset_type = EVCTX_OFFSET_TYPE_INDEX;
        t_offset.t_time_start  = t_time_start;

        b_retrieving  = TRUE;  /* Retrieving event flag. */
        b_prev        = TRUE;  /* Load event in previous/next page. */
        ui2_evt_idx   = 0;     /* Event index. */
        ui2_offset    = 1;     /* Offset related to current event. */

        for (ui2_i = 0; ui2_i < EPG_EVT_BUFFER_SIZE; ui2_i ++)
        {
            b_load = TRUE;

            if (ui2_i < ELEM_VIEW_SIZE) /* Events in current page. */
            {
                t_offset.u_offset.i2_index = (INT16)ui2_i;
                ui2_evt_idx = ui2_i;
            }
            else /* Events in previous/next page. */
            {
                if (b_prev) /* Evnets in previous page. */
                {
                    t_offset.u_offset.i2_index = (-1)*ui2_offset;
                    ui2_evt_idx = (UINT16)(2*ELEM_VIEW_SIZE + (-1)*ui2_offset);

                    if (t_time_start == 0)
                    {
                        b_load = FALSE;
                    }

                    b_prev = FALSE;
                }
                else /* Events in next page. */
                {
                    t_offset.u_offset.i2_index = ELEM_VIEW_SIZE + (ui2_offset-1);
                    ui2_evt_idx = (UINT16)(2*ELEM_VIEW_SIZE + (ui2_offset-1));

                    ui2_offset ++; /* Accumulate offset, */

                    b_prev = TRUE;
                }
            }

            if ((ui2_evt_idx < EPG_EVT_BUFFER_SIZE) &&
                (t_g_ctrl.ah_events[ui2_evt_idx] == NULL_HANDLE) && 
                (b_load)) /* Load event. */
            {
                /* Load event. */
                i4_rc = epg_evt_load (& t_offset, t_g_ctrl.ui1_event_type, & t_g_ctrl.ah_events[ui2_evt_idx]);

                if (i4_rc == EVCTXR_OK) /* Successful. */
                {
                    DBG_INFO (("<EPG> event request, handle = %d, index = %d\n\r",
                               t_g_ctrl.ah_events[ui2_evt_idx],
                               ui2_evt_idx));

                    t_g_ctrl.ui2_events_req ++; /* Accumulate event request. */

                    /* Check event condition. */
                    i4_rc = epg_evt_get_cond (t_g_ctrl.ah_events[ui2_evt_idx], & e_cond);

                    if ((i4_rc == EVCTXR_OK) &&
                        (e_cond == EVCTX_COND_AVAIL))
                    {
                        /* Send a pseudo EPG_MSG_EVT_AVAIL. */
                        _epg_ctrl_evt_nfy (EPG_MSG_EVT_AVAIL, t_g_ctrl.ah_events[ui2_evt_idx]);

                        /* Turn off retrieving flag. */
                        b_retrieving = FALSE;
                    }
                }
                else /* Something error? */
                {
                    if (i4_rc == EVCTXR_INFO_NOT_FOUND)
                    {
                        continue;
                    }
                    else if (i4_rc == EVCTXR_ENG_NOT_FOUND) /* Non-ATSC stream. */
                    {
                        DBG_INFO (("<EPG> Non-ATSC stream\n\r"));

                        /* Disable control keys of program list. */
                        RET_ON_ERR (epg_view_prg_lst_enable_control_key (FALSE));

                        /* Update osd in case there is no event. */
                        RET_ON_ERR (_epg_ctrl_evt_display_none ());

                        /* Turn on callback-complete flag. */
                        t_g_ctrl.b_event_cb_complete = TRUE;
                    }
                    else if (i4_rc == EVCTXR_EVENT_UNAVAIL)
                    {
                        /* Reload from 0 offset to resolve CR[215701][Bitstream Test]:
                                                Cannot display anything in EPG after press RED key */
                        if (t_time_start != 0)
                        {
                            return _epg_ctrl_prg_lst_update(0, b_clean);
                        }
                    }
                    else
                    {
                        DBG_ERROR (("<EPG> ERR: load event failed = %d\n\r", i4_rc));

                        /* Free event handles. */
                        for (ui2_i = 0; ui2_i < EPG_EVT_BUFFER_SIZE; ui2_i ++)
                        {
                            if (t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE)
                            {
                                epg_evt_free (t_g_ctrl.ah_events[ui2_i]);
                                t_g_ctrl.ah_events[ui2_i] = NULL_HANDLE;
                            }
                        }
                    }

                    b_retrieving = FALSE;

                    break;
                }
            }
        }

        if (b_retrieving)
        {
            t_g_ctrl.b_retrieving       = TRUE;

#ifndef APP_EPG_ICON_MSG

            /* Reset retrieving state. */
            t_g_ctrl.ui2_retrieve_state = 0;

#endif /* APP_EPG_ICON_MSG */

            /* Update retrieving state. */
            RET_ON_ERR (_epg_ctrl_retrieve_update_state ());

            /* Start retrieving timer. */
            RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_retrieve,
                                         TIMER_DELAY_RETRIEVE,
                                         X_TIMER_FLAG_REPEAT));
        }
    }

    /* Turn on flag indicating program list is being shown. */
    t_g_ctrl.b_prg_show = TRUE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_prg_lst_update_elem
 *
 * Description: The function updates the event data for a element of program list.
 *
 * Inputs:  ui2_idx             Event index.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_prg_lst_update_elem (UINT16    ui2_idx)
{
    WGL_LB_ELEM_DATA_T    t_elem;

    if (ui2_idx < EPG_EVT_BUFFER_SIZE) /* validate index */
    {
        /* get program element */
        RET_ON_ERR (_epg_ctrl_prg_lst_get_elem (& t_elem, ui2_idx));
        
        /* set element data */
        RET_ON_ERR (epg_view_prg_lst_set_elem (ui2_idx, & t_elem));
        
        /* free event data */
        _epg_ctrl_prg_lst_free_elem (& t_elem);
        
        /* repaint program element */
        RET_ON_ERR (epg_view_prg_lst_repaint_elems (ui2_idx, ui2_idx));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_prg_lst_update_scroll_images
 *
 * Description: The function updates the scrolling images of the program list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_prg_lst_update_scroll_images (VOID)
{
    BOOL    b_page_up;
    BOOL    b_page_down;

    b_page_up   = (t_g_ctrl.ui2_events_prev_page > 0) ? TRUE : FALSE;
    b_page_down = (t_g_ctrl.ui2_events_next_page > 0 &&
                   t_g_ctrl.ui2_events_crnt_page == ELEM_VIEW_SIZE) ? TRUE : FALSE;

    DBG_INFO (("<EPG> set paging images (page up = %d, page down = %d) to program list\n\r", b_page_up, b_page_down));

    /* set paging images to program list */
    RET_ON_ERR (epg_view_prg_lst_set_paging_images (b_page_up, b_page_down, TRUE));

    if ((t_g_ctrl.ui2_events_crnt_page == 0) && /* no events in current page */
        (t_g_ctrl.ui2_events_prev_page > 0) &&  /* there are events in previous page */
        (t_g_ctrl.ab_events_cb[0]))             /* the first event in current page has been called back */
    {
        /* set element number to 1 */
        RET_ON_ERR (epg_view_prg_lst_set_elem_num (1));

        /* highlight first element */
        RET_ON_ERR (epg_view_prg_lst_hlt_elem (0));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_retrieve_update_state
 *
 * Description: The function updates the states of retrieving data.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_retrieve_update_state (VOID)
{

#ifndef APP_EPG_ICON_MSG

    UINT16          ui2_i;
    UTF16_T         w2s_state[EPG_RETRIEVE_MSG_MAX_LEN];

#endif /* #ifndef APP_EPG_ICON_MSG */

    /* Theme search .*/
    if (t_g_ctrl.b_theme_search)
    {
        /* Set text to retrieving text. */
        RET_ON_ERR (epg_view_retrieve_txt_set_text (EPG_MLM (MLM_EPG_KEY_MSG_THEME_SEARCH)));

        /* Repaint retrieving text. */
        RET_ON_ERR (epg_view_retrieve_txt_repaint ());

        return 0;
    }

    if (t_g_ctrl.b_retrieving) /* Retrieving data. */
    {

#ifdef APP_EPG_ICON_MSG

#ifdef RETRIEVE_ICON_IMG_TBL
        WGL_HIMG_TPL_T    at_img[] = RETRIEVE_ICON_IMG_TBL;
        UINT8   ui1_img_num = (UINT8)(sizeof(at_img) / sizeof(at_img[0]));

        if(t_g_ctrl.ui2_retrieve_state < ui1_img_num )
        {
            t_g_ctrl.h_retrieve_icon = at_img[t_g_ctrl.ui2_retrieve_state];
        }
        else
        {
            t_g_ctrl.h_retrieve_icon = at_img[0];
        }

#else
        switch (t_g_ctrl.ui2_retrieve_state)
        {
            case 0:
                t_g_ctrl.h_retrieve_icon = RETRIEVE_ICON_IMG_1;
                break;

            case 1:
                t_g_ctrl.h_retrieve_icon = RETRIEVE_ICON_IMG_2;
                break;

            case 2:
                t_g_ctrl.h_retrieve_icon = RETRIEVE_ICON_IMG_3;
                break;

            default:
                t_g_ctrl.h_retrieve_icon = RETRIEVE_ICON_IMG_1;
                break;
        }
#endif

        /* Set image to retrieving icon. */
        RET_ON_ERR (epg_view_retrieve_icon_set_image (t_g_ctrl.h_retrieve_icon));

        /* Repaint retrieving icon. */
        RET_ON_ERR (epg_view_retrieve_icon_repaint ());

#else /* ifndef APP_EPG_ICON_MSG */

        w2s_state[0] = 0;

#ifdef APP_CLRQAM_SUPPORT

        if (epg_svl_get_id () == ATSC_TRSTRL_SVL_ID) /* Air */
        {
            epg_str_w2s_strcpy (w2s_state, EPG_MLM (MLM_EPG_KEY_MSG_INP_SRC_AIR));
        }
        else /* Cable */
        {
            epg_str_w2s_strcpy (w2s_state, EPG_MLM (MLM_EPG_KEY_MSG_INP_SRC_CABLE));
        }

        epg_str_w2s_strcat (w2s_state, EPG_MLM (MLM_EPG_KEY_SYM_START_END_SEPR));

#endif /* APP_CLRQAM_SUPPORT */

        epg_str_w2s_strcat (w2s_state, EPG_MLM (MLM_EPG_KEY_MSG_RETRIEVE_DATA));

        if (t_g_ctrl.ui2_retrieve_state > 0)
        {
            if (epg_str_w2s_strlen (w2s_state) >= 3)
            {
                w2s_state[epg_str_w2s_strlen (w2s_state)-3] = 0;
            }

            for (ui2_i = 0; ui2_i < t_g_ctrl.ui2_retrieve_state; ui2_i ++)
            {
                epg_str_w2s_strcat (w2s_state, EPG_MLM (MLM_EPG_KEY_SYM_POINT));
            }
        }

        /* Set text to retrieving text. */
        RET_ON_ERR (epg_view_retrieve_txt_set_text (w2s_state));

        /* Repaint retrieving text. */
        RET_ON_ERR (epg_view_retrieve_txt_repaint ());

#endif /* APP_EPG_ICON_MSG */

        /* Add retrieving state. */
        t_g_ctrl.ui2_retrieve_state ++;

        if (t_g_ctrl.ui2_retrieve_state == EPG_RETRIEVE_STATE) /* last state */
        {
            /* reset retrieving state */
            t_g_ctrl.ui2_retrieve_state = 0;
        }
    }
    else /* Stop retrieving data. */
    {
        /* Stop retrieving timer. */
        RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_retrieve));

#ifndef APP_EPG_ICON_MSG

#ifdef APP_CLRQAM_SUPPORT

        /* Set service name to retrieving text. */
        if (epg_svl_get_id () == ATSC_TRSTRL_SVL_ID) /* Air */
        {
            RET_ON_ERR (epg_view_retrieve_txt_set_text (EPG_MLM (MLM_EPG_KEY_MSG_INP_SRC_AIR)));
        }
        else /* Cable */
        {
            RET_ON_ERR (epg_view_retrieve_txt_set_text (EPG_MLM (MLM_EPG_KEY_MSG_INP_SRC_CABLE)));
        }

#else /* #ifndef APP_CLRQAM_SUPPORT */

        RET_ON_ERR (epg_view_retrieve_txt_set_text (w2s_g_null_str));

#endif /* APP_CLRQAM_SUPPORT */

        /* Repaint retrieving text. */
        RET_ON_ERR (epg_view_retrieve_txt_repaint ());

#endif /* #ifndef APP_EPG_ICON_MSG */

    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_screen_clean
 *
 * Description: The function cleans up the screen.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_screen_clean (VOID)
{
    UINT16    ui2_i;

    /* stop retry timer */
    RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_retry));

    /* retrieving data */
    if (t_g_ctrl.b_retrieving)
    {
        /* turn off retrieving flag */
        t_g_ctrl.b_retrieving = FALSE;

        /* update retrieving state */
        RET_ON_ERR (_epg_ctrl_retrieve_update_state ());
    }

    /* reset date index */
    t_g_ctrl.i2_date_idx          = 0;
    t_g_ctrl.ui2_date_num         = 0;
    t_g_ctrl.ui2_events_crnt_page = 0;
    t_g_ctrl.ui2_events_prev_page = 0;
    t_g_ctrl.ui2_events_next_page = 0;

    /* free event handles */
    for (ui2_i = 0; ui2_i < EPG_EVT_BUFFER_SIZE; ui2_i ++)
    {
        if (t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE)
        {
            epg_evt_free (t_g_ctrl.ah_events[ui2_i]);
            t_g_ctrl.ah_events[ui2_i] = NULL_HANDLE;
        }
    }

    /* free elements in previous/next pages */
    for (ui2_i = 0; ui2_i < ELEM_VIEW_SIZE; ui2_i ++)
    {
        _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_prev_page[ui2_i]);
        _epg_ctrl_prg_lst_free_elem (& t_g_ctrl.at_prg_elems_next_page[ui2_i]);
    }

    /* free current/next events */
    if (t_g_ctrl.h_event_crnt != NULL_HANDLE)
    {
        epg_evt_free (t_g_ctrl.h_event_crnt);
        t_g_ctrl.h_event_crnt = NULL_HANDLE;
    }

    if (t_g_ctrl.h_event_next != NULL_HANDLE)
    {
        epg_evt_free (t_g_ctrl.h_event_next);
        t_g_ctrl.h_event_next = NULL_HANDLE;
    }

    /* hide description frame */
    RET_ON_ERR (_epg_ctrl_desc_hide_frame ());

    if (t_g_ctrl.b_passwd_show) /* password frame is shown */
    {
        /* hide password frame */
        RET_ON_ERR (_epg_ctrl_passwd_hide_frame (TRUE));
    }

    /* clean program text */
    RET_ON_ERR (epg_view_prg_txt_set_text (w2s_g_null_str));

    /* clean up elements of program list */
    RET_ON_ERR (_epg_ctrl_prg_lst_clean_elems (TRUE));

#ifdef APP_EPG_DCI_SUPPORT

    /* reset direct channel input */
    RET_ON_ERR (_epg_ctrl_dci_reset (TRUE));

#endif /* APP_EPG_DCI_SUPPORT */

#ifndef APP_NO_COLOR_KEY

    /* reset help list */
    RET_ON_ERR (_epg_ctrl_help_lst_reset (TRUE));

#endif /* APP_NO_COLOR_KEY */

    /* diable control keys of program list */
    RET_ON_ERR (epg_view_prg_lst_enable_control_key (FALSE));

    /* turn off flag indicating program listing is shown */
    t_g_ctrl.b_prg_show = FALSE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_select
 *
 * Description: This function selects a service.
 *
 * Inputs:  e_surf_mode            Surfing mode.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_select (SURF_MODE_T    e_surf_mode)
{
    if (t_g_ctrl.b_passwd_show) /* Password frame is shown. */
    {
        /* Hide password frame. */
        RET_ON_ERR (_epg_ctrl_passwd_hide_frame (TRUE));
    }

    /* Program list is shown. */
    if (t_g_ctrl.b_prg_show)
    {
        /* Clean-up screen. */
        RET_ON_ERR (_epg_ctrl_screen_clean ());
    }

    /* Update SVL. */
    RET_ON_ERR (epg_svc_update_svl (e_surf_mode));

    /* Store current channel id. */
    t_g_ctrl.ui4_crnt_channel_id = a_util_cnfg_get_crnt_channel_id();

    if (! t_g_ctrl.b_svc_signal_loss) /* There is signal. */
    {
        if (! t_g_ctrl.b_svc_input_blocked) /* Input is not blocked. */
        {
            /* Reset video message. */
            RET_ON_ERR (_epg_ctrl_video_txt_msg (NULL));

            t_g_ctrl.b_svc_input_blocked = FALSE;
        }

        t_g_ctrl.b_svc_signal_loss = FALSE;
    }

    /* Reset flags. */
    t_g_ctrl.b_svc_event_blocked   = FALSE;
    t_g_ctrl.b_svc_channel_blocked = FALSE;
    t_g_ctrl.b_svc_scrambled       = FALSE;
    t_g_ctrl.b_event_yesterday     = FALSE;

    /* Set direct channel input to current channel id. */
    t_g_ctrl.ui4_dci_channel_id = a_util_cnfg_get_crnt_channel_id ();

    /* Update channel info. */
    RET_ON_ERR (_epg_ctrl_chn_update (TRUE));

#ifdef APP_EPG_DCI_SUPPORT

    /* Reset dci */
    RET_ON_ERR (_epg_ctrl_dci_reset (FALSE));

#endif /* APP_EPG_DCI_SUPPORT */

    if (t_g_ctrl.b_btn_chn_held) /* Channel button is being held. */
    {
        if (! t_g_ctrl.b_svc_stop) /* Stop service if the service is not stopped. */
        {
            /* Stop service. */
            RET_ON_ERR (epg_svc_stop ());

            /* Turn on flag indicating the service is stopped. */
            t_g_ctrl.b_svc_stop = TRUE;
        }
    }
    else
    {
        /* select service to a quarter-screen. */
        RET_ON_ERR (epg_svc_select_service (FALSE, e_surf_mode));

        /* Turn off flag indicating the service is stopped. */
        t_g_ctrl.b_svc_stop = FALSE;
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_signal_locked
 *
 * Description: The function handles the condition when the signal is locked
 *              (service present).
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_signal_locked (VOID)
{
    if (t_g_ctrl.b_svc_signal_loss      && /* Signal loss */
        ! t_g_ctrl.b_svc_input_blocked)    /* Input source is not blocked */
    {
        /* Clean video message. */
        RET_ON_ERR (_epg_ctrl_video_txt_msg (NULL));
    }

    /* Turn on signal-locked flag. */
    t_g_ctrl.b_svc_signal_locked = TRUE;

    /* Turn off signal-loss flag. */
    t_g_ctrl.b_svc_signal_loss = FALSE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_signal_loss
 *
 * Description: The function handles the condition when the signal is lost.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_signal_loss (VOID)
{
    if (! t_g_ctrl.b_svc_signal_loss)
    {
        /* Clean screen. */
        RET_ON_ERR (_epg_ctrl_screen_clean ());
    }

    /* Reset time text. */
    RET_ON_ERR (epg_view_time_txt_set_text (w2s_g_null_str));

    /* Repaint time text. */
    RET_ON_ERR (epg_view_time_txt_repaint ());

    /* Display video message. */
    if (! t_g_ctrl.b_svc_input_blocked)
    {
        RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_NO_SIGNAL)));
    }

    /* Turn off flags. */
    t_g_ctrl.b_svc_signal_locked   = FALSE;
    t_g_ctrl.b_svc_channel_blocked = FALSE;
    t_g_ctrl.b_svc_event_blocked   = FALSE;

    /* Turn on signal-loss flag. */
    t_g_ctrl.b_svc_signal_loss = TRUE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_input_blocked
 *
 * Description: The function handles the condition when input source is
 *              blocked.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_input_blocked (VOID)
{
    /* Display video message. */
    RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_INPUT_LOCKED)));

    /* Turn on input-blocked flag. */
    t_g_ctrl.b_svc_input_blocked = TRUE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_event_blocked
 *
 * Description: The function handles the condition when current event is
 *              blocked.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_event_blocked (VOID)
{
    /* Turn on event-blocked flag. */
    t_g_ctrl.b_svc_event_blocked = TRUE;

    /* Display video message. */
    RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_PROGRAM_LOCKED)));

    /* Update program list if it's not shown. */
    if (! t_g_ctrl.b_prg_show)
    {
        /* Update program list. */
        RET_ON_ERR (_epg_ctrl_prg_lst_update (0, TRUE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_channel_blocked
 *
 * Description: The function handles the condition when current channel is
 *              blocked.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_channel_blocked (VOID)
{
    /* Display video message. */
    RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_CHANNEL_LOCKED)));

    /* Turn on channel-blocked flag. */
    t_g_ctrl.b_svc_channel_blocked = TRUE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_hidden_channel
 *
 * Description: The function handles the condition when current channel is
 *              hidden.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_hidden_channel (VOID)
{
    /* Call normal service handler. */
    RET_ON_ERR (_epg_ctrl_svc_normal_service ());

    /* Turn on hidden-channel flag. */
    t_g_ctrl.b_svc_hidden_channel = TRUE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_audio_video
 *
 * Description: The function handles the condition when the channel contains both
 *              audio and video.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_audio_video (VOID)
{
    /* Update video message. */
#ifdef APP_EPG_FULL_VIDEO
    if (t_g_ctrl.b_svc_hidden_channel)
    {
        /* Display "Hidden Channel" */
        RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_CHANNEL_HIDED)));

        return 0;
    }
#endif /* APP_EPG_FULL_VIDEO */

    RET_ON_ERR (_epg_ctrl_video_txt_msg (NULL));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_audio_only
 *
 * Description: The function handles the condition when the channel contains only
 *              audio data.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_audio_only (VOID)
{
    /* Update video message. */
    RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_AUDIO_PROGRAM)));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_no_audio_video
 *
 * Description: The function handles the condition when the channel contains neither
 *              audio nor video.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_no_audio_video (VOID)
{
    if (t_g_ctrl.b_svc_hidden_channel) /* Hidden channel */
    {
        /* Display "Hidden Channel" */
        RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_CHANNEL_HIDED)));
    }
    else
    {
        if (! t_g_ctrl.b_svc_scrambled) /* Not scrambled. */
        {
            /* Update video message. */
            RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_NO_AV)));
        }
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_event_ready_handler
 *
 * Description: The function handles the event ready notification
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_event_ready_handler (BOOL b_read)
{
    UINT16    ui2_hlt = 0;

    do
    {
        /* Do nothing if there is not events in current page */
        if (t_g_ctrl.ui2_events_crnt_page == 0)
        {
            break;
        }

        /* get highlighted index of program list */
        RET_ON_ERR (epg_view_prg_lst_get_hlt_idx (& ui2_hlt));

        /* check index validation */
        if (ui2_hlt >= ELEM_VIEW_SIZE)
        {
            break;
        }

        if ((t_g_ctrl.ah_events[ui2_hlt] == NULL_HANDLE) ||
            (! t_g_ctrl.ab_events_cb[ui2_hlt])) /* event is not called back */
        {
            break;
        }

        /* Reload all event */
        if (t_g_ctrl.b_event_cb_complete)
        {
            RET_ON_ERR (_epg_ctrl_prg_lst_update (0, TRUE));
        }
        
    } while(0);
    
    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_normal_service
 *
 * Description: The function handles the condition when the service is normal.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_normal_service (VOID)
{
    BOOL    b_update;

    if (! t_g_ctrl.b_svc_scrambled) /* The service is not scrambled. */
    {
        if ((t_g_ctrl.b_svc_input_blocked)   ||
            (t_g_ctrl.b_svc_event_blocked)   ||
            (t_g_ctrl.b_svc_channel_blocked) ||
            (t_g_ctrl.b_svc_hidden_channel))
        {
            /* Clean video message. */
            RET_ON_ERR (_epg_ctrl_video_txt_msg (NULL));
        }

        if (t_g_ctrl.b_passwd_show) /* Password frame is being shown. */
        {
            /* Hide password frame. */
            RET_ON_ERR (_epg_ctrl_passwd_hide_frame (TRUE));
        }
    }

    /* Do not need to update program list if current event was blocked. */
    b_update = (t_g_ctrl.b_svc_event_blocked == TRUE) ? FALSE : TRUE;

    /* Turn off event-blocked/channel-blocked/hidden-channel flags. */
    t_g_ctrl.b_svc_input_blocked   = FALSE;
    t_g_ctrl.b_svc_event_blocked   = FALSE;
    t_g_ctrl.b_svc_channel_blocked = FALSE;
    t_g_ctrl.b_svc_hidden_channel  = FALSE;

    /* Update program list if required. */
    if (b_update)
    {
        RET_ON_ERR (_epg_ctrl_prg_lst_update (0, TRUE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_scdb_updated
 *
 * Description: The function handles the condition when the SCDB is updated.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_scdb_updated (VOID)
{
    UINT16    ui2_i;
    BOOL      b_with_cc = FALSE;

    for (ui2_i = 0; ui2_i < EPG_EVT_BUFFER_SIZE; ui2_i ++)
    {
        if ((t_g_ctrl.ah_events[ui2_i] != NULL_HANDLE) &&
            (t_g_ctrl.ab_events_cb[ui2_i]))
        {
            /* Find current event. */
            if (_epg_ctrl_evt_is_crnt (t_g_ctrl.ah_events[ui2_i]))
            {
                EPG_CC_QUERY_DATA_T t_cc_query_data;
                c_memset (&t_cc_query_data, 0, sizeof(EPG_CC_QUERY_DATA_T));
                
                /* Query whether there is any CC in current event from SVCTX */
                t_cc_query_data.e_query_mode = EPG_CC_QUERY_SVCTX;                
                b_with_cc = epg_svc_is_crnt_event_with_cc(&t_cc_query_data);

                if (b_with_cc != t_g_ctrl.b_event_crnt_with_cc_info)
                {
                    /* Send a pesudo event-updated message to EPG. */
                    epg_app_send_msg (EPG_MSG_EVT_UPDATED, & t_g_ctrl.ah_events[ui2_i], 4);
                }

                if (t_cc_query_data.b_delay_query)
                {
                    DBG_INFO (("<EPG> start a timer to delay query CC again from SVCTX. \n\r"));
                    /* Start a timer to delay query CC again from SVCTX. */
                    RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_delay_query_cc,
                                                 TIMER_DEALY_QUERY_CC_FROM_SVC,
                                                 X_TIMER_FLAG_ONCE));
                }

                break;
            }
        }
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_scrambled
 *
 * Description: The function handles the condition when the service is scrambled.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_scrambled (VOID)
{
    /* Update video message. */
    if (t_g_ctrl.b_svc_hidden_channel) /* Hidden channel */
    {
        /* Display "Hidden Channel" */
        RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_CHANNEL_HIDED)));
    }
    else
    {
        if ((! t_g_ctrl.b_svc_input_blocked)   && /* Input is not blocked. */
            (! t_g_ctrl.b_svc_event_blocked)   && /* Event is not blocked. */
            (! t_g_ctrl.b_svc_channel_blocked))   /* Channel is not blocked. */
        {
            RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_SCRAMBLE)));
        }
    }

    /* Turn on scrambled flag. */
    t_g_ctrl.b_svc_scrambled = TRUE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_authorized
 *
 * Description: The function handles the condition when the service is authorized.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_authorized (VOID)
{
    /* Update video message. */
    if ((t_g_ctrl.b_svc_scrambled)         && /* Service is scrambled. */
        (! t_g_ctrl.b_svc_input_blocked)   && /* Input is not blocked. */
        (! t_g_ctrl.b_svc_event_blocked)   && /* Event is not blocked. */
        (! t_g_ctrl.b_svc_channel_blocked) && /* Channel is not blocked. */
        (! t_g_ctrl.b_svc_hidden_channel))    /* Channel is not hidden. */
    {
        /* Clean video message. */
        RET_ON_ERR (_epg_ctrl_video_txt_msg (NULL));
    }

    /* Turn off scrambled flag. */
    t_g_ctrl.b_svc_scrambled = FALSE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svc_service_changed
 *
 * Description: The function handles the condition when the service is changed.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svc_service_changed (VOID)
{
    UINT32    ui4_channel_id;

    /* Get current channel id. */
    ui4_channel_id = a_util_cnfg_get_crnt_channel_id ();

    if (ui4_channel_id != t_g_ctrl.ui4_crnt_channel_id)
    {
        /* Select service. */
        RET_ON_ERR (_epg_ctrl_svc_select (SURF_MODE_THIS));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_svl_update
 *
 * Description: The function update SVL.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_svl_update (UINT32 ui4_reason)
{
    INT32        i4_rc;
    UINT32       ui4_channel_id;
    SVL_REC_T    t_svl_rec;

    if (epg_svl_is_found ()) /* SVL is found. */
    {
        /* Check if current record is available. */
        ui4_channel_id = a_util_cnfg_get_crnt_channel_id ();

        i4_rc = epg_svl_get_rec_by_channel_id (ui4_channel_id, & t_svl_rec);

        if (i4_rc == SVLR_REC_NOT_FOUND) /* Current record is not found. */
        {
            /*
               If current service is not found, the first channel of current transport stream
               or the whole broadcast service will be selected.
            */
            RET_ON_ERR (_epg_ctrl_svc_select (SURF_MODE_PREV));
        }
        else /* Current record is found. */
        {
            if ((ui4_channel_id != t_g_ctrl.ui4_crnt_channel_id) ||
                (ui4_reason == SVL_REASON_UNKNOWN))
            {
                /* Select current service. */
                RET_ON_ERR (_epg_ctrl_svc_select (SURF_MODE_THIS));
            }
        }

        /* Update channel info. */
        RET_ON_ERR (_epg_ctrl_chn_update (TRUE));

        /* Start clock timer. */
        RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_clock,
                                     TIMER_DELAY_CLOCK,
                                     X_TIMER_FLAG_REPEAT));
    }
    else /* SVL is not found. */
    {
        if (! epg_svc_is_tv_block ())
        {
            /* Display "no channel" message. */
            RET_ON_ERR (_epg_ctrl_video_txt_msg (EPG_MLM (MLM_EPG_KEY_MSG_NO_CHANNEL)));
        }

        /* Stop clock timer. */
        RET_ON_ERR (epg_timer_stop (t_g_ctrl.h_timer_clock));

        /* Reset time text. */
        RET_ON_ERR (epg_view_time_txt_set_text (w2s_g_null_str));

        /* Repaint time text. */
        RET_ON_ERR (epg_view_time_txt_repaint ());

        /* Clean up screen. */
        RET_ON_ERR (_epg_ctrl_screen_clean ());

        /* Disable control keys of program list. */
        RET_ON_ERR (epg_view_prg_lst_enable_control_key (FALSE));

        /* Update channel list and channel text. */
        RET_ON_ERR (_epg_ctrl_chn_update (TRUE));

        /* Stop service. */
        RET_ON_ERR (epg_svc_stop ());

        /* Turn on service-stop flag. */
        t_g_ctrl.b_svc_stop = TRUE;

    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_check_rating
 *
 * Description: The function checks if an event exceeds the rating set in Menu.
 *
 * Inputs:  h_event             Event handle.
 *
 * Outputs: pb_exceed           Exceed or not.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_check_rating (HANDLE_T    h_event,
                                     BOOL*       pb_exceed)
{
    INT32                        i4_rc;
    SIZE_T                       z_info_size = 0;
    EVCTX_ATSC_RATING_LIST_T*    pt_rating;

    pt_rating  = NULL;
    *pb_exceed = FALSE;

    /* Get the length of rating. */
    i4_rc = epg_evt_get_rating_len (h_event, & z_info_size);

    if (i4_rc == 0 && z_info_size != 0)
    {
        /* Allocate memory for storing rating info. */
        pt_rating = (EVCTX_ATSC_RATING_LIST_T*) c_mem_alloc (z_info_size);

        if (pt_rating == NULL)
        {
            DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

            return  EPGR_OUT_OF_MEM;
        }

        /* Get rating. */
        i4_rc = epg_evt_get_rating (h_event, z_info_size, pt_rating);

        if (i4_rc != 0)
        {
            /* Free pt_rating. */
            c_mem_free (pt_rating);

            pt_rating = NULL;
        }
    }
    else
    {
        pt_rating = NULL;
    }

    /* Check rating. */
    i4_rc = epg_svc_check_block (pt_rating, pb_exceed);

    if (i4_rc != 0)
    {
        *pb_exceed = FALSE;
    }

    /* Free pt_rating. */
    if (pt_rating != NULL)
    {
        c_mem_free (pt_rating);
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_video_txt_msg
 *
 * Description: The function displays message in video text.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_video_txt_msg (UTF16_T*    pw2s_text)
{
    BOOL b_is_av_mute = FALSE;

    b_is_av_mute = epg_cfg_is_av_mute();

    /* Hide video info. text widget if AV is mute: here "mute" means end-user can not see video and hear audio */        
     if ((pw2s_text == NULL) || b_is_av_mute)
    {
        RET_ON_ERR (epg_view_video_txt_set_text (w2s_g_null_str));
        RET_ON_ERR (epg_view_video_frm_set_visibility (FALSE));
    }
    else
    {
        RET_ON_ERR (epg_view_video_txt_set_text (pw2s_text));
        RET_ON_ERR (epg_view_video_frm_set_visibility (TRUE));
    }

    /* Repaint video text. */
    RET_ON_ERR (epg_view_video_txt_repaint ());

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_wgl_process_nfy
 *
 * Description: The function processes the notifications from Widget Library.
 *
 * Inputs:  pt_wgl_msg          Widget notification message.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_wgl_process_nfy (WIDGET_MSG_T*    pt_wgl_msg)
{
    INT32                 i4_rc;
    UINT32                ui4_key_cond;
    UINT32                ui4_key_code;
    UINT32*               pui4_evt_code;

    /* Key condition - up, down or repeat. */
    ui4_key_cond = (UINT32) pt_wgl_msg->ui4_msg;

    /* Process key condition. */
    if (ui4_key_cond == WGL_MSG_KEY_UP) /* key up */
    {
        if (t_g_ctrl.b_btn_held) /* Button is being held. */
        {
            /* Call to controller. */
            epg_app_send_msg (EPG_MSG_CTRL_BTN_RELEASED, NULL, 0);

            /* Turn off button-held flag */
            t_g_ctrl.b_btn_held = FALSE;
        }
    }
    else if (ui4_key_cond == WGL_MSG_KEY_REPEAT) /* key repeat */
    {
        /* Replace WGL_MSG_KEY_REPEAT with WGL_MSG_KEY_DOWN. */
        pt_wgl_msg->ui4_msg = WGL_MSG_KEY_DOWN;

        if (! t_g_ctrl.b_btn_held) /* Button is released. */
        {
            /* Call to controller. */
            epg_app_send_msg (EPG_MSG_CTRL_BTN_HELD, NULL, 0);

            /* Turn on button-held flag */
            t_g_ctrl.b_btn_held = TRUE;
        }
    }

    /* Call to pre-key handler in custom part. */
    pui4_evt_code = (UINT32*) pt_wgl_msg->pv_param1;

    epg_custom_pre_key_handler (& pui4_evt_code);

    /* Ingore event source. */
    pt_wgl_msg->pv_param1 = (VOID*) IOM_GET_EVT_GRP_ID (pui4_evt_code);

    /* Dispatch message to Widget Library. */
    i4_rc = c_wgl_dispatch_event (pt_wgl_msg->ui4_msg,
                                  pt_wgl_msg->pv_param1,
                                  pt_wgl_msg->pv_param2);

    if (i4_rc == WGLR_OK)
    {
        /* Call button handler. */
        if (pt_wgl_msg->ui4_msg == WGL_MSG_KEY_DOWN)
        {
            RET_ON_ERR (_epg_ctrl_btn_handler ((UINT32) pt_wgl_msg->pv_param1));
        }
    }
    else if (i4_rc == WGLR_EVENT_IGNORED)
    {
        ui4_key_code = (UINT32) pt_wgl_msg->pv_param1;

        if ((ui4_key_code == BTN_CURSOR_LEFT)  ||
            (ui4_key_code == BTN_CURSOR_RIGHT) ||
            (ui4_key_code == BTN_PRG_UP)       ||
            (ui4_key_code == BTN_PRG_DOWN)     ||
            (ui4_key_code == BTN_EXIT))
        {
            /* Call button handler. */
            if (ui4_key_cond == WGL_MSG_KEY_DOWN)
            {
                RET_ON_ERR (_epg_ctrl_btn_handler (ui4_key_code));
            }
        }
    }
    else
    {
        DBG_ERROR (("<EPG> ERR: dispatch event to wgl failed = %d\n\r", i4_rc));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_wgl_get_focus
 *
 * Description: The function handles the condition when a widget gets focus.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_wgl_get_focus (VOID)
{
    /* Get focused widget. */
    RET_ON_ERR (epg_view_get_focus_widget (& t_g_ctrl.e_widget_focus_crnt));

    if (t_g_ctrl.e_widget_focus_crnt == EPG_FOCUS_WIDGET_PRG_LST) /* Program list gets focus. */
    {
        if (epg_svl_is_found ()) /* SVL is found. */
        {
            if (t_g_ctrl.ui2_events_crnt_page == 0) /* The number of elements in current page is 0. */
            {
                if (t_g_ctrl.ui2_events_prev_page > 0) /* The number of elements in previous page is greater than 0. */
                {
                    /* Set the number of elements of program list to 1. */
                    RET_ON_ERR (epg_view_prg_lst_set_elem_num (1));
                }
                else /* The number of elements in previous page is 0. */
                {
                    /* Disable control keys of program list. */
                    RET_ON_ERR (epg_view_prg_lst_enable_control_key (FALSE));
                }
            }
        }
        else /* SVL is not found */
        {
            /* Disable control keys of program list. */
            RET_ON_ERR (epg_view_prg_lst_enable_control_key (FALSE));
        }
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_requery_cc_from_svc
 *
 * Description: The function requery cc from svctx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_requery_cc_from_svc (VOID)
{
    return _epg_ctrl_svc_scdb_updated();
}


/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_timer_expired_handler
 *
 * Description: The function resets pause-timer when a button is pressed.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_timer_expired_handler (HANDLE_T    h_timer)
{
    if (h_timer == t_g_ctrl.h_timer_clock)              /* Clock timer is expired. */
    {
        /* Update current system time. */
        RET_ON_ERR (_epg_ctrl_dt_update_crnt_time ());
    }
    else if (h_timer == t_g_ctrl.h_timer_retry)         /* Retry timer is expired. */
    {
        /* Retry getting current/next events. */
        RET_ON_ERR (_epg_ctrl_evt_retry ());
    }
    else if (h_timer == t_g_ctrl.h_timer_pause)         /* Auto-pause timer is expired. */
    {
        /* Auto-pause EPG if auto-pause flag is set. */
        if (t_g_ctrl.b_app_auto_pause)
        {
            /* Pause EPG application. */
            RET_ON_ERR (epg_app_pause_req ());
        }
    }
    else if (h_timer == t_g_ctrl.h_timer_retrieve)      /* Retrieving timer is expired. */
    {
        if (t_g_ctrl.b_retrieving) /* Retrieving data. */
        {
            /* Update retrieving state. */
            RET_ON_ERR (_epg_ctrl_retrieve_update_state ());
        }
    }
    else if (h_timer == t_g_ctrl.h_timer_dci)           /* DCI timer is expired. */
    {
        /* Call select button handler. */
        RET_ON_ERR (_epg_ctrl_btn_select ());
    }
    else if (h_timer == t_g_ctrl.h_timer_passwd_msg)    /* Password message timer is expired. */
    {
        /* Clean incorrect password message. */
        RET_ON_ERR (_epg_ctrl_passwd_display_msg (TRUE));
    }
    else if (h_timer == t_g_ctrl.h_timer_passwd_dlg)    /* Password dialog timer is expired. */
    {
        /* Hide password dialog. */
        RET_ON_ERR (_epg_ctrl_passwd_hide_frame (TRUE));
    }
    else if (h_timer == t_g_ctrl.h_timer_delay_update)  /* Delay to update evetns. */
    {
        /* Update all the events. */
        RET_ON_ERR (_epg_ctrl_evt_update ());
    }
    else if (h_timer == t_g_ctrl.h_timer_delay_query_cc)  /* Delay to query CC info of current event. */
    {
        /* Requery cc from svctx */
        RET_ON_ERR (_epg_ctrl_requery_cc_from_svc ());
    }

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_timer_reset_pause
 *
 * Description: The function resets pause-timer when a button is pressed.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_timer_reset_pause (VOID)
{
    if (t_g_ctrl.b_app_auto_pause) /* Auto pause function is enabled. */
    {
        if (TIMER_DELAY_PAUSE > 0)
        {
            /* Restart auto-pause timer. */
            RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_pause,
                                         TIMER_DELAY_PAUSE,
                                         X_TIMER_FLAG_ONCE));

            /* Turn on auto-pause flag. */
            t_g_ctrl.b_app_auto_pause = TRUE;
        }
        else
        {
            /* Turn off auto-pause flag. */
            t_g_ctrl.b_app_auto_pause = FALSE;
        }
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_btn_released
 *
 * Description: The function handles the condition when a button is released.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_btn_released (VOID)
{
    UINT16    ui2_num_recs;

    /* Update program description if necessary. */
    if ((t_g_ctrl.b_btn_prg_held) &&  /* Program button is being held. */
        (t_g_ctrl.b_prg_show)     &&  /* Program list is being shown. */
        (! t_g_ctrl.b_desc_show))     /* Program description is not being shown. */
    {
        /* Get the number of records of SVL. */
        RET_ON_ERR (epg_svl_get_num_recs (& ui2_num_recs));

        /* The number of records is greater than 0. */
        if (ui2_num_recs > 0)
        {
            /* Send a pseudo message to EPG. */
            epg_app_send_msg (EPG_MSG_VIEW_WGL_PRG_LST_ELEM_HLT, NULL, 0); /* The element of program list is highlighted. */
        }
    }

    /* Turn off flags. */
    t_g_ctrl.b_btn_held     = FALSE;
    t_g_ctrl.b_btn_chn_held = FALSE;
    t_g_ctrl.b_btn_prg_held = FALSE;

    /* Select service if the service is stopped. */
    if ((t_g_ctrl.b_svc_stop) && /* Service is stopped. */
        (epg_svl_is_found ()))   /* SVL is found. */
    {
        RET_ON_ERR (_epg_ctrl_svc_select (SURF_MODE_THIS));
    }

    return  0;
}

#ifdef APP_EPG_THEME_SEARCH

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_theme_search_show
 *
 * Description: The function shows theme search page.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_theme_search_show (BOOL    b_repaint)
{
    INT32                       i4_ret;
    ISO_3166_COUNT_T            s3166_country;

    if (! t_g_ctrl.b_theme_search)
    {
        /* Turn on theme search flag. */
        t_g_ctrl.b_theme_search = TRUE;

        /* Get event type from acfg */
        a_cfg_get_evt_type (& t_g_ctrl.ui1_event_type);

        /* Set highlighted index */
        i4_ret = epg_view_type_lst_hlt_elem ((t_g_ctrl.ui1_event_type & 0xf0) >> 4);

        if (i4_ret != EPGR_OK)
        {
            /* Reset event type */
            t_g_ctrl.ui1_event_type = 0;

            a_cfg_set_evt_type (t_g_ctrl.ui1_event_type );

            /* Highlight first element */
            RET_ON_ERR (epg_view_type_lst_hlt_elem (0));
        }

        RET_ON_ERR (epg_view_subtype_lst_hlt_elem (t_g_ctrl.ui1_event_type & 0x0f));

        /* Hide program list & channel list & description frame & program info text. */
        RET_ON_ERR (epg_view_prg_lst_set_visibility (FALSE));
        RET_ON_ERR (epg_view_chn_lst_set_visibility (FALSE));
        RET_ON_ERR (epg_view_desc_frm_set_visibility (FALSE));
        RET_ON_ERR (epg_view_prg_txt_set_visibility (FALSE));

        /* Show type list & subtype list. */
        RET_ON_ERR (epg_view_type_lst_set_visibility (TRUE));

        if (a_cfg_get_country (s3166_country) == APP_CFGR_OK)
        {
            /* Show event subtype only if the country is not Australia. */
            if (c_strncmp (s3166_country, s3166_app_cfg_count_aus, ISO_3166_COUNT_LEN) != 0) /* Australia */
            {
                RET_ON_ERR (epg_view_subtype_lst_set_visibility (TRUE));

                /* set navigations */
                RET_ON_ERR (epg_view_set_navigations (EPG_FOCUS_WIDGET_TYPE_LST,
                                                      BTN_CURSOR_UP,
                                                      EPG_FOCUS_WIDGET_SUBTYPE_LST,
                                                      BTN_CURSOR_DOWN,
                                                      EPG_FOCUS_WIDGET_SUBTYPE_LST));

                RET_ON_ERR (epg_view_set_navigations (EPG_FOCUS_WIDGET_SUBTYPE_LST,
                                                      BTN_CURSOR_UP,
                                                      EPG_FOCUS_WIDGET_TYPE_LST,
                                                      BTN_CURSOR_DOWN,
                                                      EPG_FOCUS_WIDGET_TYPE_LST));
            }
        }

        if (t_g_ctrl.b_passwd_show) /* password frame is shown. */
        {
            /* hide password frame. */
            RET_ON_ERR (_epg_ctrl_passwd_hide_frame (FALSE));
        }

        /* Free all the events. */
        _epg_ctrl_evt_free_all ();

        /* Reset variables. */
        t_g_ctrl.i2_date_idx           = 0;
        t_g_ctrl.ui2_date_num          = 0;
        t_g_ctrl.ui2_desc_page_num     = 0;
        t_g_ctrl.ui2_desc_page_idx     = 0;
        t_g_ctrl.ui2_events_crnt_page  = 0;
        t_g_ctrl.ui2_events_prev_page  = 0;
        t_g_ctrl.ui2_events_next_page  = 0;

        /* set text to retrieving text. */
        RET_ON_ERR (epg_view_retrieve_txt_set_text (EPG_MLM (MLM_EPG_KEY_MSG_THEME_SEARCH)));

        /* Set focus to type list. */
        RET_ON_ERR (epg_view_set_focus_widget (EPG_FOCUS_WIDGET_TYPE_LST));

        /* Show help. */
        RET_ON_ERR (_epg_ctrl_help_lst_update_dvb_help (FALSE));

        if (b_repaint)
        {
            /* Repaint main frame. */
            RET_ON_ERR (epg_view_main_frm_repaint ());
        }
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_theme_search_hide
 *
 * Description: The function hides theme search page.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_theme_search_hide (BOOL    b_repaint)
{
    UINT16           ui2_hlt_type;
    UINT16           ui2_hlt_subtype;

    /* Turn off theme search flag */
    t_g_ctrl.b_theme_search = FALSE;

    /* Hide type list & subtype list */
    RET_ON_ERR (epg_view_type_lst_set_visibility (FALSE));
    RET_ON_ERR (epg_view_subtype_lst_set_visibility (FALSE));

    /* Show program list & channel list */
    RET_ON_ERR (epg_view_prg_lst_set_visibility (TRUE));
    RET_ON_ERR (epg_view_chn_lst_set_visibility (TRUE));
    RET_ON_ERR (epg_view_prg_txt_set_visibility (TRUE));

    /* clean retrieving text */
    RET_ON_ERR (epg_view_retrieve_txt_set_text (w2s_g_null_str));

    /* Set focus to program list */
    RET_ON_ERR (epg_view_set_focus_widget (EPG_FOCUS_WIDGET_PRG_LST));

    /* Clean-up program list */
    RET_ON_ERR (_epg_ctrl_prg_lst_clean_elems (FALSE));

    /* Show help */
    RET_ON_ERR (_epg_ctrl_help_lst_update_dvb_help (FALSE));

    /* Get highlighted index of type list & subtype list */
    RET_ON_ERR (epg_view_type_lst_get_hlt_idx (& ui2_hlt_type));
    RET_ON_ERR (epg_view_subtype_lst_get_hlt_idx (& ui2_hlt_subtype));

    /* Store event type to be queried */
    t_g_ctrl.ui1_event_type = (UINT8) (ui2_hlt_type * 16 + ui2_hlt_subtype);

    /* Save event type to acfg */
    a_cfg_set_evt_type (t_g_ctrl.ui1_event_type);

    if (b_repaint)
    {
        /* Repaint main frame */
        RET_ON_ERR (epg_view_main_frm_repaint ());
    }

    return  0;
}

#endif /* APP_EPG_THEME_SEARCH */

/*-----------------------------------------------------------------------------
 * Name: _epg_ctrl_type_lst_elem_hlted
 *
 * Description: This function handles the conditions when the element of type
 *              list is highlighted.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _epg_ctrl_type_lst_elem_hlted (VOID)
{
    UINT16                    ui2_i;
    UINT16                    ui2_hlt_idx;
    UINT16                    ui2_num_subtype;
    UINT16                    ui2_mlm_key_idx;
    WGL_LB_ELEM_DATA_T*       pt_elem_data;

    /* Get highlighted index of type list. */
    RET_ON_ERR (epg_view_type_lst_get_hlt_idx (& ui2_hlt_idx));

    /* Update elements in subtype list. */
    switch (ui2_hlt_idx)
    {
        case 0: /* All types */
            ui2_num_subtype = 1;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_ALL;
            break;

        case 1: /* Movie */
            ui2_num_subtype = 10;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_MOVIE_0;
            break;

        case 2: /* News */
            ui2_num_subtype = 6;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_NEWS_0;
            break;

        case 3: /* Show */
            ui2_num_subtype = 5;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_SHOW_0;
            break;

        case 4: /* Sports */
            ui2_num_subtype = 13;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_SPORT_0;
            break;

        case 5: /* Children's */
            ui2_num_subtype = 7;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_CHILD_0;
            break;

        case 6: /* Music */
            ui2_num_subtype = 8;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_MUSIC_0;
            break;

        case 7: /* Arts */
            ui2_num_subtype = 13;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_ARTS_0;
            break;

        case 8: /* Social */
            ui2_num_subtype = 5;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_SOCIAL_0;
            break;

        case 9: /* Education */
            ui2_num_subtype = 9;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_EDUCTION_0;
            break;

        case 10: /* Leisure Hobbies */
            ui2_num_subtype = 9;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_LEISURE_0;
            break;

        case 11: /* Special */
            ui2_num_subtype = 5;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_SPECIAL_0;
            break;

        default: /* Unknown */
            ui2_num_subtype = 0;
            ui2_mlm_key_idx = MLM_EPG_KEY_EVT_SUBTYPE_ALL;
            break;
    }

    if (ui2_num_subtype > 0)
    {
        /* Allocate elements. */
        pt_elem_data = (WGL_LB_ELEM_DATA_T*) c_mem_alloc (ui2_num_subtype * sizeof (WGL_LB_ELEM_DATA_T));

        if (pt_elem_data == NULL) /* Out of memory */
        {
            DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

            return EPGR_OUT_OF_MEM;
        }

        for (ui2_i = 0; ui2_i < ui2_num_subtype; ui2_i ++)
        {
            /* Allocate items. */
            pt_elem_data[ui2_i].at_items = (WGL_LB_ITEM_DATA_T*) c_mem_alloc (sizeof (WGL_LB_ITEM_DATA_T));

            if (pt_elem_data[ui2_i].at_items == NULL) /* Out of memory */
            {
                DBG_ERROR (("<EPG> ERR: out of memory\n\r"));

                /* Free elements. */
                c_mem_free (pt_elem_data);

                return EPGR_OUT_OF_MEM;
            }

            pt_elem_data[ui2_i].at_items[0].pw2s_text = EPG_MLM (ui2_mlm_key_idx + ui2_i);
        }

        /* Set element number. */
        RET_ON_ERR (epg_view_subtype_lst_set_elem_num (ui2_num_subtype));

        /* Set element data to subtype list. */
        RET_ON_ERR (epg_view_subtype_lst_set_elems (0, (UINT16)(ui2_num_subtype-1), pt_elem_data));

        /* Highlight first element. */
        RET_ON_ERR (epg_view_subtype_lst_hlt_elem (0));

        /* Repaint subtype list. */
        RET_ON_ERR (epg_view_subtype_lst_repaint ());

        /* Free items. */
        for (ui2_i = 0; ui2_i < ui2_num_subtype; ui2_i ++)
        {
            if (pt_elem_data[ui2_i].at_items != NULL)
            {
                c_mem_free (pt_elem_data[ui2_i].at_items);
            }
        }

        /* Free elements. */
        if (pt_elem_data != NULL)
        {
            c_mem_free (pt_elem_data);
        }
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: epg_ctrl_app_process_msg
 *
 * Description: This API is called when EPG extracts a message from it's message
 *              queue.
 *
 * Inputs:  ui4_type            Message type.
 *          pv_msg              Message data.
 *          z_msg_len           The length of message.
 *
 * Outputs: -
 *
 * Returns: 0                   Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
INT32 epg_ctrl_process_msg (UINT32         ui4_type,
                            const VOID*    pv_msg,
                            SIZE_T         z_msg_len)
{
    if (ui4_type > EPG_MSG_BEGIN &&
        ui4_type < EPG_MSG_END)
    {
        /*
            Model messages
        */
        switch (ui4_type)
        {
            /* Lifecycle notifications. */
            case EPG_MSG_APP_INIT:                        /* Applicaiton starts. */
            {
                RET_ON_ERR (_epg_ctrl_app_init ());
            }
            break;

            case EPG_MSG_APP_EXIT:                        /* Application exits. */
            {
                RET_ON_ERR (_epg_ctrl_app_exit ());
            }
            break;

            case EPG_MSG_APP_PAUSE:                       /* Application pauses. */
            {
                RET_ON_ERR (_epg_ctrl_app_pause ());
            }
            break;

            case EPG_MSG_APP_RESUME:                      /* Application resumes. */
            {
                RET_ON_ERR (_epg_ctrl_app_resume ());
            }
            break;


            /*
               Widget notifications.
            */
            case EPG_MSG_WGL_NFY:
            {
                RET_ON_ERR (_epg_ctrl_wgl_process_nfy ((WIDGET_MSG_T*) pv_msg));
            }
            break;


            /*
               Timer notifications.
            */
            case EPG_MSG_TIMER_EXPIRED:                   /* Timer is expired. */
            {
                /* Call timer handler. */
                RET_ON_ERR (_epg_ctrl_timer_expired_handler (*((HANDLE_T*)pv_msg)));
            }
            break;


            /*
               Event notifications.
            */
            case EPG_MSG_EVT_AVAIL:                       /* Event available. */
            case EPG_MSG_EVT_UNAVAIL:                     /* Event unavailable. */
            case EPG_MSG_EVT_EXPIRED:                     /* Event expired. */
            case EPG_MSG_EVT_UPDATED:                     /* Event updated. */
            {
                /* Call event handler. */
                RET_ON_ERR (_epg_ctrl_evt_nfy (ui4_type, *((HANDLE_T*)pv_msg)));
            }
            break;


            /*
               Service notifications.
            */
            case EPG_MSG_SVC_SIGNAL_LOCKED:               /* Signal locked. */
            {
                /* Call signal locked handler. */
                RET_ON_ERR (_epg_ctrl_svc_signal_locked ());
            }
            break;

            case EPG_MSG_SVC_SIGNAL_LOSS:                 /* Signal loss. */
            {
                /* Call signal loss handler. */
                RET_ON_ERR (_epg_ctrl_svc_signal_loss ());
            }
            break;

            case EPG_MSG_SVC_INPUT_BLOCKED:               /* Input blocked. */
            {
                /* Call input blocked handler. */
                RET_ON_ERR (_epg_ctrl_svc_input_blocked ());
            }
            break;

            case EPG_MSG_SVC_EVENT_BLOCKED:               /* Event blocked. */
            {
                /* Call event blocked handler. */
                RET_ON_ERR (_epg_ctrl_svc_event_blocked ());
            }
            break;

            case EPG_MSG_SVC_CHANNEL_BLOCKED:             /* Channel blocked. */
            {
                /* Call channel blocked handler. */
                RET_ON_ERR (_epg_ctrl_svc_channel_blocked ());
            }
            break;

            case EPG_MSG_SVC_HIDDEN_CHANNEL:              /* Hidden channel. */
            {
                /* Call hidden channel handler. */
                RET_ON_ERR (_epg_ctrl_svc_hidden_channel ());
            }
            break;

            case EPG_MSG_SVC_NORMAL_SERVICE:              /* Normal service. */
            {
                /* Call normal service handler. */
                RET_ON_ERR (_epg_ctrl_svc_normal_service ());
            }
            break;

            #if 0
            case EPG_MSG_SVC_SCDB_UPDATED:                /* SCDB is updated. */
            case EPG_MSG_SVC_WITH_CC:                     /* With CC. */
            case EPG_MSG_SVC_NO_CC:                       /* No CC. */
            case EPG_MSG_SVC_CC_CHG:                      /* CC indicator change. */
            {
                /* Call scdb-updated handler. */
                RET_ON_ERR (_epg_ctrl_svc_scdb_updated ());
            }
            break;
            #else
            
            case EPG_MSG_SVC_SCDB_UPDATED:                /* SCDB is updated. */
            case EPG_MSG_SVC_CC_AVIL_STATUS_CHG:          /* CC available status change. */
            case EPG_MSG_SVC_EXISTED_CC_IND_CHG:          /* CC indicator change. */
            {
                /* Call scdb-updated handler. */
                RET_ON_ERR (_epg_ctrl_svc_scdb_updated ());
            }
            break;
            
            #endif

            case EPG_MSG_SVC_SCRAMBLED:                   /* Service is scrambled. */
            {
                /* Call scrambled handler. */
                RET_ON_ERR (_epg_ctrl_svc_scrambled ());
            }
            break;

            case EPG_MSG_SVC_AUTHORIZED:                  /* Service is authorized. */
            {
                /* Call authorized handler. */
                RET_ON_ERR (_epg_ctrl_svc_authorized ());
            }
            break;

            case EPG_MSG_SVC_SERVICE_CHANGED:             /* Service is changed. */
            {
                /* Call service-changed handler. */
                RET_ON_ERR (_epg_ctrl_svc_service_changed ());
            }
            break;

            case EPG_MSG_SVC_AUDIO_VIDEO:                 /* Normal AV. */
            {
                /* Call av handler. */
                RET_ON_ERR (_epg_ctrl_svc_audio_video ());
            }
            break;

            case EPG_MSG_SVC_AUDIO_ONLY:                  /* Audio-only service. */
            {
                /* Call audio-only handler. */
                RET_ON_ERR (_epg_ctrl_svc_audio_only ());
            }
            break;

            case EPG_MSG_SVC_NO_AUDIO_VIDEO:              /* No AV. */
            {
                /* Call no-av handler. */
                RET_ON_ERR (_epg_ctrl_svc_no_audio_video ());
            }
            break;

            case EPG_MSG_SVC_CRNT_EVN_READY:              /* Current event ready */
            {
                /* call event ready handler. */
                RET_ON_ERR (_epg_ctrl_svc_event_ready_handler(TRUE));
            }
            break;

            case EPG_MSG_SVC_CRNT_EVN_NOT_READY:          /* Current event not ready */
            {
                /* call event not ready handler. */
                RET_ON_ERR (_epg_ctrl_svc_event_ready_handler(FALSE));
            }
            break;

            /*
               Configuration notifications.
            */
            case EPG_MSG_CFG_LANGUAGE_UPDATED:            /* Language is updated. */
            {
                /* call language-updated handler */
                RET_ON_ERR (_epg_ctrl_cfg_language_updated ());
            }
            break;

            case EPG_MSG_CFG_VCHIP_UPDATED:               /* V-chip is updated. */
            {
                /* call VChip-updated handler */
                RET_ON_ERR (_epg_ctrl_cfg_vchip_updated ());
            }
            break;

            case EPG_MSG_CFG_BRDCST_SVC_UPDATED:          /* Broadcast service is updated. */
            {
                RET_ON_ERR (_epg_ctrl_cfg_brdcst_svc_updated ());
            }
            break;


            /*
               Date-time notifications.
            */
            case EPG_MSG_DT_DISCONT:                      /* Date-time is discontinuous */
            {
                RET_ON_ERR (_epg_ctrl_dt_discont_handler ((DT_NFY_DATA_T*) pv_msg));
            }
            break;

            case EPG_MSG_DT_DAY_LGT_SAV_CHANGED:          /* Day-light-saving is changed */
            {
                /* Delay update events. */
                RET_ON_ERR (epg_timer_start (t_g_ctrl.h_timer_delay_update,
                                             TIMER_DEALY_UPDATE_EVENTS,
                                             X_TIMER_FLAG_ONCE));
            }
            break;

            /*
               SVL notifictions.
            */
            case EPG_MSG_SVL_UPDATED:                     /* SVL is updated. */
            {
                /* Update svl. */
                RET_ON_ERR (_epg_ctrl_svl_update (*((UINT32*)pv_msg)));
            }
            break;

            /*
               RRT notifications.
            */
            case EPG_MSG_RRT_UPDATED:                     /* RRT is updated. */
            {
                /* Update events. */
                RET_ON_ERR (_epg_ctrl_evt_update ());
            }
            break;
            
            default:
                break;
         }
     }
     else if (ui4_type > EPG_MSG_CTRL_BEGIN &&
              ui4_type < EPG_MSG_CTRL_END)
     {
        /*
           Controller messages.
        */
        switch (ui4_type)
        {
            /*
               Controller internal messages.
            */
            case EPG_MSG_CTRL_REQ_HIDE_PASSWD_FRM:
            {
                /* Hide password frame. */
                RET_ON_ERR (_epg_ctrl_passwd_hide_frame (TRUE));
            }
            break;

            case EPG_MSG_CTRL_BTN_HELD:                   /* Button is being held. */
            {
                /* Turn on button-held flag. */
                t_g_ctrl.b_btn_held = TRUE;
            }
            break;

            case EPG_MSG_CTRL_BTN_RELEASED:               /* Button is released. */
            {
                /* Call button-released handler. */
                RET_ON_ERR (_epg_ctrl_btn_released ());
            }
            break;

            default:
                break;
        }
    }
    else if (ui4_type > EPG_MSG_VIEW_BEGIN && 
             ui4_type < EPG_MSG_VIEW_END)
    {
        /*
           View model messages.
        */
        switch (ui4_type)
        {
            case EPG_MSG_VIEW_WGL_GET_FOCUS:              /* Some widget gets focus. */
            {
                /* Call get-focus handler. */
                RET_ON_ERR (_epg_ctrl_wgl_get_focus ());
            }
            break;
            
            case EPG_MSG_VIEW_WGL_PRG_LST_ELEM_HLT:       /* Program list's element highlighted. */
            {
                /* Call element highlighted handler. */
                RET_ON_ERR (_epg_ctrl_prg_lst_elem_hlted ());
            }
            break;
            
            case EPG_MSG_VIEW_WGL_PRG_LST_ELEM_REACH_TOP: /* Reach top boundary of program list. */
            {
                /* Call reach-boundary handler. */
                RET_ON_ERR (_epg_ctrl_prg_lst_reach_boundary (TRUE));
            }
            break;

            case EPG_MSG_VIEW_WGL_PRG_LST_ELEM_REACH_BOTTOM: /* Reach bottom boundary of program list. */
            {
                /* Call reach-boundary handler. */
                RET_ON_ERR (_epg_ctrl_prg_lst_reach_boundary (FALSE));
            }
            break;

            case EPG_MSG_VIEW_WGL_PASSWD_EDIT_INPUT:      /* Password edit gets input. */
            {
                /* Call password input handler. */
                RET_ON_ERR (_epg_ctrl_passwd_input ());
            }
            break;

            case EPG_MSG_VIEW_WGL_TYPE_LST_ELEM_HLT:      /* Type list element is highlighted. */
            {
                /* Call type list element highlighted handler. */
                RET_ON_ERR (_epg_ctrl_type_lst_elem_hlted ());
            }
            break;

            default:
                break;
        }
    }

    return  0;
}
