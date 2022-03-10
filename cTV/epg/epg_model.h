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
 * $RCSfile: epg_model.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This file contains function prototypes of EPG model.
 *---------------------------------------------------------------------------*/

#ifndef _EPG_MODEL_H_
#define _EPG_MODEL_H_

/*---------------------------------------------------------------------------
                    include files
----------------------------------------------------------------------------*/
#include "epg/epg.h"

/*-----------------------------------------------------------------------------
                    structures
-----------------------------------------------------------------------------*/

/*
   Widget messages structure.
*/
typedef struct
{
    UINT32                      ui4_msg;
    VOID*                       pv_param1;
    VOID*                       pv_param2;
}   WIDGET_MSG_T;

/*
   DT notify structure.
*/
typedef struct
{
    TIME_T                      t_delta_time;
    UINT32                      ui4_time_stamp;
}   DT_NFY_DATA_T;

/*
   Model messages.
*/
typedef enum
{
    EPG_MSG_BEGIN = 0,                       /* Begin of Model messages. */

    /* Lifecycle notifications. */
    EPG_MSG_APP_INIT,                        /* Application starts. */
    EPG_MSG_APP_EXIT,                        /* Application exits. */
    EPG_MSG_APP_RESUME,                      /* Application resumes. */
    EPG_MSG_APP_PAUSE,                       /* Application pauses. */

    /* Widget notifications. */
    EPG_MSG_WGL_NFY,                         /* Widget notifications. */

    /* Timer notifications. */
    EPG_MSG_TIMER_EXPIRED,                   /* Timer expired. */

    /* Event notifications. */
    EPG_MSG_EVT_AVAIL,                       /* Event available. */
    EPG_MSG_EVT_UNAVAIL,                     /* Event unavailable. */
    EPG_MSG_EVT_EXPIRED,                     /* Event expired. */
    EPG_MSG_EVT_UPDATED,                     /* Event updated. */

    /* Service notifications. */
    EPG_MSG_SVC_BEGIN,                       /* Begin of service notificatons (for internal use only). */

    EPG_MSG_SVC_SIGNAL_LOCKED,               /* Signal locked. */
    EPG_MSG_SVC_SIGNAL_LOSS,                 /* Signal loss. */
    EPG_MSG_SVC_EVENT_BLOCKED,               /* Event blocked. */
    EPG_MSG_SVC_CHANNEL_BLOCKED,             /* Channel blocked. */
    EPG_MSG_SVC_INPUT_BLOCKED,               /* Input source blocked. */
    EPG_MSG_SVC_HIDDEN_CHANNEL,              /* Hidden channel. */
    EPG_MSG_SVC_NORMAL_SERVICE,              /* Normal service. */
    EPG_MSG_SVC_AUDIO_VIDEO,                 /* Normal AV. */
    EPG_MSG_SVC_AUDIO_ONLY,                  /* Audio-only program. */
    EPG_MSG_SVC_NO_AUDIO_VIDEO,              /* No AV. */
    EPG_MSG_SVC_SCDB_UPDATED,                /* SCDB updated. */
    EPG_MSG_SVC_SERVICE_CHANGED,             /* Service changed. */
    EPG_MSG_SVC_SCRAMBLED,                   /* Scrambled. */
    EPG_MSG_SVC_AUTHORIZED,                  /* Authorized. */
    
    EPG_MSG_SVC_WITH_CC,                     /* Current event has CC. */
    EPG_MSG_SVC_NO_CC,                       /* No CC in current event. */
    EPG_MSG_SVC_CC_CHG,                      /* CC indicator changed in current event. */

    EPG_MSG_SVC_CC_AVIL_STATUS_CHG,          /* CC available status changed in current event. */
    EPG_MSG_SVC_EXISTED_CC_IND_CHG,          /* CC existed indicator changed in current event. */

    EPG_MSG_SVC_CRNT_EVN_READY,              /* Current event ready. */
    EPG_MSG_SVC_CRNT_EVN_NOT_READY,          /* Current event not ready. */

    EPG_MSG_SVC_END,                         /* End of service notifications (for internal use only). */

    /* Configuration notifications. */
    EPG_MSG_CFG_LANGUAGE_UPDATED,            /* Language updated. */
    EPG_MSG_CFG_VCHIP_UPDATED,               /* V-chip updated. */
    EPG_MSG_CFG_BRDCST_SVC_UPDATED,          /* Broadcast service updated. */

    /* Date-time notifications. */
    EPG_MSG_DT_DISCONT,                      /* Date-time is discontinuous. */
    EPG_MSG_DT_DAY_LGT_SAV_CHANGED,          /* Day-light-saving is changed. */

    /* SVL notifictions. */
    EPG_MSG_SVL_UPDATED,                     /* SVL updated. */
    
    /* RRCTX notifications. */
    EPG_MSG_RRT_UPDATED,                     /* RRT updated. */

    EPG_MSG_END                              /* End of Model messages. */

}   EPG_MSG_T;


/*
   Time formats.
*/
typedef enum
{
    EPG_TIME_MODE_FULL    =    0,            /* Dow, month-day-year, hour:minute:second AM(PM) */
    EPG_TIME_MODE_MD,                        /* Month-day */
    EPG_TIME_MODE_HM,                        /* Hour:minute AM(PM) */
    EPG_TIME_MODE_DOW                        /* Day of week */
}   EPG_TIME_MODE_T;

/*
   Query CC indicator
*/
typedef enum
{
    EPG_CC_QUERY_DIRECTLY   =    0,           /* Get CC indicator from internal cache by EPG */
    EPG_CC_QUERY_SVCTX                        /* Query CC indicator from SVCTX */
}   EPG_CC_QUERY_MODE_T;

/*
   Query CC Data structure.
*/
typedef struct
{
    EPG_CC_QUERY_MODE_T     e_query_mode;     /* [IN]   Query Mode: from EPG internal cache or from SVCTX */
    BOOL                    b_delay_query;    /* [OUT] Whether need reset a timer to query CC again from SVCTX  */
}   EPG_CC_QUERY_DATA_T;

/*
    EPG background configuration.
*/
typedef enum
{
    EPG_AV_CONFIG_WITH_FULL_VIDEO = 0,           /* With full video & audio in background */
    EPG_AV_CONFIG_NO_VIDEO_AUDIO,                /* With no video & audio in background */
    EPG_AV_CONFIG_WITH_PIP_VIDEO,                /* With PIP video & audio in left-bottom corner */
    EPG_AV_CONFIG_LAST_VALID_ENTRY
} EPG_AV_CONFIG_T;

/*
   EPG configuration data.
*/
typedef struct _EPG_CONFIG_T
{    
    EPG_AV_CONFIG_T     e_av_config;             /* EPG video & audio configuration data */
} EPG_CONFIG_T;

/*-----------------------------------------------------------------------------
                    functions
-----------------------------------------------------------------------------*/
/*
    Process message function prototype.
*/
typedef INT32 (*epg_process_msg_fct) (UINT32         ui4_type,
                                      const VOID*    pv_msg,
                                      SIZE_T         z_msg_len);

/*
   Application model.
*/
extern INT32 epg_app_send_msg (UINT32 ui4_type, const VOID* pv_msg, SIZE_T z_msg_len);
extern INT32 epg_app_dispatch_msg (UINT32 ui4_type, const VOID* pv_msg, SIZE_T z_msg_len);
extern INT32 epg_app_pause_req (VOID);
extern INT32 epg_app_resume_req (VOID);
extern BOOL  epg_app_is_pause (VOID);


/*
   Event model.
*/
extern INT32 epg_evt_load (EVCTX_OFFSET_T* pt_offset, UINT8 ui1_type, HANDLE_T* ph_event);
extern INT32 epg_evt_get_cond (HANDLE_T h_event, EVCTX_COND_T* pe_cond);
extern INT32 epg_evt_free (HANDLE_T h_event);
extern INT32 epg_evt_get_start_time (HANDLE_T h_event, TIME_T* pt_time_start);
extern INT32 epg_evt_get_end_time (HANDLE_T h_event, TIME_T* pt_time_end);
extern INT32 epg_evt_get_duration (HANDLE_T h_event, TIME_T* pt_time_duration);
extern INT32 epg_evt_get_title_len (HANDLE_T h_event, SIZE_T* pz_title_len);
extern INT32 epg_evt_get_title (HANDLE_T h_event, SIZE_T z_title_len, CHAR* ps_title);
extern INT32 epg_evt_get_text_len (HANDLE_T h_event, SIZE_T* pz_text_len);
extern INT32 epg_evt_get_text (HANDLE_T h_event, SIZE_T z_text_len, CHAR* ps_text);
extern INT32 epg_evt_get_rating_len (HANDLE_T h_event, SIZE_T* pz_rating_len);
extern INT32 epg_evt_get_rating (HANDLE_T h_event, SIZE_T z_rating_len, EVCTX_ATSC_RATING_LIST_T* pt_atsc_rating);
extern INT32 epg_evt_get_caption (HANDLE_T h_event, BOOL* pb_caption);
extern INT32 epg_evt_get_hours (HANDLE_T h_event, UINT16* pui2_avail_hours);


/*
   Service model.
*/
extern INT32 epg_svc_update_svl (SURF_MODE_T e_surf_mode);
extern INT32 epg_svc_select_service (BOOL b_fit_to_screen, SURF_MODE_T e_surf_mode);
extern INT32 epg_svc_adjust_vplane_order (BOOL b_top);
extern INT32 epg_svc_stop (VOID);
extern INT32 epg_svc_unblock (VOID);
extern INT32 epg_svc_blank_video (BOOL b_main);
extern INT32 epg_svc_enable_default_video_plane_mode(BOOL    b_enable);
extern INT32 epg_svc_disable_blue_mute (VOID);
extern INT32 epg_svc_get_caption_num_recs (UINT16* pui2_num_recs);
extern INT32 epg_svc_check_block (VOID* pv_rating, BOOL* pb_exceed);
extern BOOL  epg_svc_is_tv_block (VOID);
extern BOOL  epg_svc_is_signal_loss (VOID);
extern BOOL  epg_svc_is_crnt_event_with_cc(EPG_CC_QUERY_DATA_T* pt_cc_query_data);


/*
   SVL model.
*/
extern INT32  epg_svl_lock (VOID);
extern INT32  epg_svl_unlock (VOID);
extern BOOL   epg_svl_is_found (VOID);
extern INT32  epg_svl_update_rec (SVL_REC_T* pt_svl_rec);
extern INT32  epg_svl_iterate_rec (UINT32 ui4_channel_id, SVL_ITERATE_T e_iter, SVL_REC_T* pt_svl_rec);
extern INT32  epg_svl_get_rec (SVL_REC_T* pt_svl_rec);
extern INT32  epg_svl_get_rec_by_channel_id (UINT32 ui4_channel_id, SVL_REC_T* pt_svl_rec);
extern INT32  epg_svl_get_rec_by_surf_mode (SURF_MODE_T e_surf_mode, UINT32* pui4_channel_id, SVL_REC_T* pt_svl_rec);
extern INT32  epg_svl_get_num_recs (UINT16* pui2_num_recs);
extern UINT16 epg_svl_get_id (VOID);
extern BOOL   epg_svl_is_analog_chn (VOID);


/*
   Date-time model.
*/
extern INT32  epg_dt_get_loc_dtg (DTG_T* pt_loc_dtg);
extern TIME_T epg_dt_get_utc_sec (VOID);
extern INT32  epg_dt_get_utc_dtg (DTG_T* pt_utc_dtg);
extern INT32  epg_dt_get_start_loc_dtg_by_event (HANDLE_T h_event, DTG_T* pt_start_dtg);
extern INT32  epg_dt_get_end_loc_dtg_by_event (HANDLE_T h_event, DTG_T* pt_end_dtg);
extern INT32  epg_dt_get_start_utc_sec_by_date (INT16 i2_date_offset, TIME_T* pt_start_sec);
extern INT32  epg_dt_get_time_str (DTG_T t_dtg, EPG_TIME_MODE_T e_time_mode, UTF16_T* pw2s_time);
extern TIME_T epg_dt_diff (DTG_T* pt_dtg_from, DTG_T* pt_dtg_to);
extern DT_COND_T epg_dt_get_cond (VOID);


/*
   Configuration model.
*/
extern UINT16 epg_cfg_get_language_id (VOID);


/*
   Timer model.
*/
extern INT32 epg_timer_create (HANDLE_T* ph_timer);
extern INT32 epg_timer_start (HANDLE_T h_timer, UINT32 ui4_delay, TIMER_FLAG_T e_timer_flag);
extern INT32 epg_timer_stop (HANDLE_T h_timer);


/*
   String model.
*/
extern INT32  epg_str_ps_to_w2s (const CHAR* ps_src, UTF16_T* pw2s_dst, UINT32 ui4_dst_len);
extern INT32  epg_str_w2s_to_ps (const UTF16_T* pw2s_src, CHAR* ps_dst, UINT32 ui4_dst_len);
extern VOID   epg_str_w2s_strcpy (UTF16_T* pw2s_dst, const UTF16_T* pw2s_src);
extern VOID   epg_str_w2s_strcat (UTF16_T* pw2s_dst, const UTF16_T* pw2s_src);
extern SIZE_T epg_str_w2s_strlen (UTF16_T* pw2s_str);
extern VOID   epg_str_trim (CHAR* ps_str);


/*
   OSD model.
*/
extern INT32  epg_osd_get_canvas_handle (HANDLE_T* ph_canvas);
extern UINT32 epg_osd_get_canvas_width (VOID);
extern UINT32 epg_osd_get_canvas_height (VOID);
extern INT32  epg_osd_get_offset_x (VOID);
extern INT32  epg_osd_get_offset_y (VOID);

/*
   Configuration model.
*/
extern INT32  epg_cfg_get_config_data (EPG_CONFIG_T* pt_config);
extern BOOL   epg_cfg_is_av_mute(VOID);

/*
   EPG utility APIs.
*/
extern INT32  epg_util_set_sound_out_port (BOOL b_enabled);
extern BOOL   epg_is_active_refused(VOID);

#endif /* _EPG_MODEL_H_ */
