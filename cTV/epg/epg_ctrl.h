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
 * $RCSfile: epg_ctrl.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/41 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 44fcab2cb57e22ab81550785e74341d2 $
 *
 * Description:
 *         This header file contains definitions for EPG Controller. (Actually,
 *         it's a Presentation Model because it handles not only Control but
 *         UI updates.)
 *---------------------------------------------------------------------------*/

#ifndef _EPG_CTRL_H_
#define _EPG_CTRL_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "epg/epg.h"
#include "epg/epg_model.h"
#include "epg/epg_view.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/* Timer delay to update system time. */
#ifndef TIMER_DELAY_CLOCK
    #define  TIMER_DELAY_CLOCK               (250)     /* in milliseconds */
#endif /* TIMER_DELAY_CLOCK */

/* Timer delay to retry getting events. */
#ifndef TIMER_DELAY_RETRY
    #define  TIMER_DELAY_RETRY               (200)     /* in milliseconds */
#endif /* TIMER_DELAY_RETRY */

/* Timer delay for direct channel input. */
#ifndef TIMER_DELAY_DCI
    #define  TIMER_DELAY_DCI                 (3000)    /* in milliseconds */
#endif /* TIMER_DELAY_DCI */

/* Timer delay to retrieve data. */
#ifndef TIMER_DELAY_RETRIEVE
    #define  TIMER_DELAY_RETRIEVE            (1000)    /* in milliseconds */
#endif /* TIMER_DELAY_RETRIEVE */

/* Timer delay to hide password dialog. */
#ifndef TIMER_DEALY_PASSWD_DLG
    #define  TIMER_DELAY_PASSWD_DLG          (5000)    /* in milliseconds */
#endif /* TIMER_DELAY_PASSWD_DLG */

/* Timer delay to hide incorrect password message. */
#ifndef TIMER_DEALY_PASSWD_MSG
    #define  TIMER_DELAY_PASSWD_MSG          (2000)    /* in milliseconds */
#endif /* TIMER_DELAY_PASSWD */

/* Timer delay to update events. */
#ifndef TIMER_DEALY_UPDATE_EVENTS
    #define  TIMER_DEALY_UPDATE_EVENTS       (1000)    /* in milliseconds */
#endif /* TIMER_DELAY_PASSWD */

/* Timer delay to query CC from SVCTX. */
#ifndef TIMER_DEALY_QUERY_CC_FROM_SVC
    #define  TIMER_DEALY_QUERY_CC_FROM_SVC   (500)     /* in milliseconds */
#endif /* TIMER_DEALY_QUERY_CC_FROM_SVCTX */


/* The number of password digits. */
#ifndef EPG_PASSWD_DIGIT
    #define  EPG_PASSWD_DIGIT                (4)
#endif /* EPG_PASSWD_DIGIT */

/* Maximum number of channel digits. */
#ifndef EPG_DCI_MAX_DIGIT
    #define  EPG_DCI_MAX_DIGIT               (6)
#endif /* EPG_DCI_MAX_DIGIT */

/* The maximum available days for DVB-T. */
#ifndef EPG_MAX_AVAIL_DAYS
    #define  EPG_MAX_AVAIL_DAYS              (8)
#endif /* EPG_MAX_AVAIL_DAYS */

/* 0                ~ ELEM_VIEW_SIZE-1   : Events in current page. */
/* ELEM_VIEW_SIZE   ~ 2*ELEM_VIEW_SIZE-1 : Events in previous page. */
/* 2*ELEM_VIEW_SIZE ~ 3*ELEM_VIEW_SIZE-1 : Events in next page. */
#ifndef EPG_EVT_BUFFER_SIZE
    #define  EPG_EVT_BUFFER_SIZE             (3 * ELEM_VIEW_SIZE)
#endif /* EPG_EVT_BUFFER_SIZE */

/*-----------------------------------------------------------------------------
                    structure
 ----------------------------------------------------------------------------*/

/*
   Controller messages.
*/
typedef enum
{
    EPG_MSG_CTRL_BEGIN = EPG_MSG_VIEW_END,                 /* Begin of controller messages. */

    EPG_MSG_CTRL_REQ_HIDE_PASSWD_FRM,                      /* A request to hide password frame. */
    EPG_MSG_CTRL_BTN_HELD,                                 /* Button is being held. */
    EPG_MSG_CTRL_BTN_RELEASED,                             /* Button is releassed. */

    EPG_MSG_CTRL_END                                       /* End of controller messages. */

}   EPG_MSG_CTRL_T;

/*
   Description paging type.
*/
typedef enum
{
    EPG_DESC_PAGE_TYPE_TOGGLE    =    0,                   /* Toggle pages circularly */
    EPG_DESC_PAGE_TYPE_PREV,                               /* Change to previous page */
    EPG_DESC_PAGE_TYPE_NEXT                                /* Change to next page */
}   EPG_DESC_PAGE_TYPE_T;

/*
   Surfing list elements structure.
*/
typedef struct
{
    UTF16_T             w2s_ch_no[EPG_CHN_NO_MAX_LEN];
    UTF16_T             w2s_ch_name[EPG_CHN_NAME_MAX_LEN];
    UINT32              ui4_channel_id;
}   EPG_SURF_LST_ELEM;

/*
   Controller variables.
*/
typedef struct
{
    /* Event data. */
    HANDLE_T            h_event_crnt;                       /* Current event. */
    HANDLE_T            h_event_next;                       /* Next event. */
    HANDLE_T            ah_events[EPG_EVT_BUFFER_SIZE];     /* Events handles. */
    UINT16              ui2_events_crnt_page;               /* The number of events in current page. */
    UINT16              ui2_events_prev_page;               /* The number of events in previous page. */
    UINT16              ui2_events_next_page;               /* The number of events in next page. */
    UINT16              ui2_events_req;                     /* The number of events which are requested. */
    UINT16              ui2_events_cb;                      /* The number of events which have been called back. */
    BOOL                ab_events_cb[EPG_EVT_BUFFER_SIZE];  /* Indicate if the events have been called back. */
    BOOL                b_event_cb_complete;                /* Indicate if events' callbacks are complete. */
    BOOL                b_event_yesterday;                  /* Indicate if current event started at yesterday. */
    BOOL                b_event_shifted;                    /* Events have been shifted. */
    BOOL                b_event_crnt_with_cc_info;          /* Indicate if current event contains CC info. */
    UINT8               ui1_event_type;                     /* Event type to be queried. */

    /* Service data. */
    UINT32              ui4_crnt_channel_id;                /* Current channel id. */
    BOOL                b_svc_signal_locked;                /* Signal locked. */
    BOOL                b_svc_signal_loss;                  /* Signal loss. */
    BOOL                b_svc_input_blocked;                /* Input blocked. */
    BOOL                b_svc_event_blocked;                /* Event blocked. */
    BOOL                b_svc_channel_blocked;              /* Channel blocked. */
    BOOL                b_svc_hidden_channel;               /* Hidden channel. */
    BOOL                b_svc_stop;                         /* Service is stopped. */
    BOOL                b_svc_scrambled;                    /* Service is scrambled. */

    /* Timer data. */
    HANDLE_T            h_timer_clock;                      /* Timer to update system time periodically. */
    HANDLE_T            h_timer_retry;                      /* Timer to retry getting events. */
    HANDLE_T            h_timer_pause;                      /* Timer to auto pause EPG. */
    HANDLE_T            h_timer_retrieve;                   /* Timer to update retrieving states. */
    HANDLE_T            h_timer_dci;                        /* Timer to auto. change channel when direct channel input is active. */
    HANDLE_T            h_timer_passwd_msg;                 /* Timer to hide password error message. */
    HANDLE_T            h_timer_passwd_dlg;                 /* Timer to hide password dialog. */
    HANDLE_T            h_timer_delay_update;               /* Timer to delay update events. */
    HANDLE_T            h_timer_delay_query_cc;             /* Timer to delay query CC info of current event. */

    /* Date-time data. */
    INT16               i2_date_idx;                        /* Date index, -1: yesterday, 0: today, 1: tomorrow,... */
    UINT16              ui2_date_num;                       /* The number of dates. */
    BOOL                b_date_changing;                    /* Date is being changed. */
    BOOL                b_date_updated;                     /* Date index has been updated. */
    BOOL                b_date_jumped;                      /* Date is already jumped. */
    BOOL                b_time_avail_updated;               /* Avaiable time has been updated. */
    BOOL                b_time_display;                     /* System time is being displayed. */
    BOOL                b_time_total_avail;                 /* Indicate if total time is available. */

    /* Program list data. */
    BOOL                b_prg_ctrl_key_disable;             /* Control keys are disabled. */
    BOOL                b_prg_show;                         /* Program list is being shown. */
    WGL_LB_ELEM_DATA_T  at_prg_elems_prev_page[ELEM_VIEW_SIZE]; /* Elements in previous page. */
    WGL_LB_ELEM_DATA_T  at_prg_elems_next_page[ELEM_VIEW_SIZE]; /* Elements in next page. */

    /* Surfing list data. */
    EPG_SURF_LST_ELEM   at_surf_elems[ELEM_VIEW_SIZE];      /* Surfing elements. */

    /* Program description data. */
    UINT16              ui2_desc_page_idx;                  /* Page index of the description. */
    UINT16              ui2_desc_page_num;                  /* Page number of the description. */
    BOOL                b_desc_show;                        /* Description is being shown. */
    BOOL                b_desc_keep;                        /* Indicate if the description should be kept. */

    /* Direct Channel Input (DCI) data. */
    CHAR                ac_dci[EPG_DCI_MAX_DIGIT];          /* Direct channel input. */
    UINT32              ui4_dci_channel_id;                 /* Channel id for direct channel input. */
    UINT16              ui2_dci_idx;                        /* The index of direct channel input. */
    BOOL                b_dci_complete;                     /* Direct channel input is complete. */

    /* Password data. */
    UINT16              ui2_passwd_idx;                     /* Password index. */
    BOOL                b_passwd_show;                      /* Password dialog is being shown. */

    /* Retrieving data. */
    HANDLE_T            h_retrieve_icon;                    /* Handle to retrieving icon. */
    UINT16              ui2_retrieve_state;                 /* Retrieving states. */
    BOOL                b_retrieving;                       /* Retrieving data. */

    /* Application data. */
    BOOL                b_app_auto_pause;                   /* Indicates if auto pause function is enabled. */

    /* Widget data. */
    EPG_FOCUS_WIDGET_T  e_widget_focus_crnt;                /* Current focused widget. */
    EPG_FOCUS_WIDGET_T  e_widget_focus_last;                /* Last focused widget. */

    /* Button data. */
    BOOL                b_btn_held;                         /* Button is being held. */
    BOOL                b_btn_chn_held;                     /* Channel button is being held. */
    BOOL                b_btn_prg_held;                     /* Program button is being held. */

    /* DVB data. */
    BOOL                b_theme_search;                     /* Indicates if theme search is being active. */

}   EPG_CTRL_T;

/*
   Callback function of controller.
*/
extern INT32 epg_ctrl_process_msg (UINT32 ui4_type, const VOID* pv_msg, SIZE_T z_msg_len);


#endif /* _EPG_CTRL_H_ */
