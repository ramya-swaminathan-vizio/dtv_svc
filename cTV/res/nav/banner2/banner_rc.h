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
 * $RCSfile: banner.h,v $
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
#ifndef _BANNER_RC_H_
#define _BANNER_RC_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#include "nav/nav_common.h"
#include "nav/nav_bnr_state_mgr.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_bnr_item_def.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/* the key which used to freeze/un-freeze view, MAX_SUPPORT 32 keys */
#define BANNER_CUSTOM_FREEZE_VIEW_ID_CHG_FOCUS  MAKE_BIT_MASK_32 (0)
#define BANNER_CUSTOM_FREEZE_VIEW_ID_SVC_SWAP   MAKE_BIT_MASK_32 (1)
#define BANNER_CUSTOM_FREEZE_VIEW_ID_TV_MODE    MAKE_BIT_MASK_32 (2)
/* the key which used to freeze/un-freeze view, MAX_SUPPORT 32 keys */


#define GET_STATE_DISP_NAME(state_id)                                           \
        (BANNER_STATE_NONE              == state_id) ? "BANNER_STATE_NONE"       :           \
        (BANNER_STATE_IDLE              == state_id) ? "BANNER_STATE_IDLE"       :           \
        (BANNER_STATE_CH                == state_id) ? "BANNER_STATE_CH"         :           \
        (BANNER_STATE_PCH               == state_id) ? "BANNER_STATE_PCH"        :           \
        (BANNER_STATE_PDCH              == state_id) ? "BANNER_STATE_PDCH"       :           \
        (BANNER_STATE_IPTS              == state_id) ? "BANNER_STATE_IPTS"       :           \
        (BANNER_STATE_EMPTY_SVL         == state_id) ? "BANNER_STATE_EMPTY_SVL"  :           \
        (BANNER_STATE_INPTTING          == state_id) ? "BANNER_STATE_INPTTING"   :           \
        (BANNER_STATE_CHANGING          == state_id) ? "BANNER_STATE_CHANGING"   :           \
        (BANNER_STATE_SHOW_MSG          == state_id) ? "BANNER_STATE_SHOW_MSG"   :           \
        (BANNER_STATE_NO_SIG            == state_id) ? "BANNER_STATE_NO_SIG"     :           \
        (BANNER_STATE_RETRIEVE          == state_id) ? "BANNER_STATE_RETRIEVE"   :           \
        (BANNER_STATE_HIDDEN_CH         == state_id) ? "BANNER_STATE_HIDDEN_CH"  :           \
        (BANNER_STATE_VIRTUAL_ALL_STATE == state_id) ? "BANNER_STATE_VIRTUAL_ALL_STATE"  :           \
        (BANNER_STATE_VIRTUAL_FINAL     == state_id) ? "BANNER_STATE_VIRTUAL_FINAL"  :           \
        (BANNER_STATE_VIRTUAL_TV_DEFAULT== state_id) ? "BANNER_STATE_VIRTUAL_TV_DEFAULT"  :           \
        (BANNER_STATE_PRI_TV_DEFAULT    == state_id) ? "BANNER_STATE_PRI_TV_DEFAULT"  :           \
        "UNKNOWN_STATE"

#if (CUSTOMER != VIZIO)
  #define BANNER_ITM_HEADPHONES BANNER_ITM_LAST_VALID_ENTRY+1
#endif

#define GET_ITEM_DISP_NAME(item_id)                                                                  \
        (BANNER_ITM_FRM_CH              == item_id) ? "BANNER_ITM_FRM_CH"               :            \
        (BANNER_ITM_FRM_INF             == item_id) ? "BANNER_ITM_FRM_INF"              :            \
        (BANNER_ITM_FRM_DTL             == item_id) ? "BANNER_ITM_FRM_DTL"              :            \
        (BANNER_ITM_CH_NO               == item_id) ? "BANNER_ITM_CH_NO"                :            \
        (BANNER_ITM_CH_NAME             == item_id) ? "BANNER_ITM_CH_NAME"              :            \
        (BANNER_ITM_MSG                 == item_id) ? "BANNER_ITM_MSG"                  :            \
        (BANNER_ITM_PROG_TITLE          == item_id) ? "BANNER_ITM_PROG_TITLE"           :            \
        (BANNER_ITM_NEXT_PROG_TITLE     == item_id) ? "BANNER_ITM_NEXT_PROG_TITLE"      :            \
        (BANNER_ITM_PROG_TIME           == item_id) ? "BANNER_ITM_PROG_TIME"            :            \
        (BANNER_ITM_WIFI_TXT            == item_id) ? "BANNER_ITM_WIFI_TXT"             :            \
        (BANNER_ITM_AUDIO_FARMAT        == item_id) ? "BANNER_ITM_AUDIO_FARMAT"         :            \
        (BANNER_ITM_TV_NAME             == item_id) ? "BANNER_ITM_TV_NAME"              :            \
        (BANNER_ITM_NEXT_PROG_TIME      == item_id) ? "BANNER_ITM_NEXT_PROG_TIME"       :            \
        (BANNER_ITM_PROG_DETAIL         == item_id) ? "BANNER_ITM_PROG_DETAIL"          :            \
        (BANNER_ITM_PROG_DETAIL_PG_IDX  == item_id) ? "BANNER_ITM_PROG_DETAIL_PG_IDX"   :            \
        (BANNER_ITM_RATING              == item_id) ? "BANNER_ITM_RATING"               :            \
        (BANNER_ITM_CAPTION             == item_id) ? "BANNER_ITM_CAPTION"              :            \
        (BANNER_ITM_AUDIO_LANG          == item_id) ? "BANNER_ITM_AUDIO_LANG"           :            \
        (BANNER_ITM_VIDEO_INFO          == item_id) ? "BANNER_ITM_VIDEO_INFO"           :            \
        (BANNER_ITM_IPT_CH_NO           == item_id) ? "BANNER_ITM_IPT_CH_NO"            :            \
        (BANNER_ITM_IPTS_LOCK_ICON      == item_id) ? "BANNER_ITM_IPTS_LOCK_ICON"       :            \
        (BANNER_ITM_TV_LOCK_ICON        == item_id) ? "BANNER_ITM_TV_LOCK_ICON"         :            \
        (BANNER_ITM_CAPTION_ICON        == item_id) ? "BANNER_ITM_CAPTION_ICON"         :            \
        (BANNER_ITM_PROG_DETAIL_UP_ICON == item_id) ? "BANNER_ITM_PROG_DETAIL_UP_ICON"  :            \
        (BANNER_ITM_PROG_DETAIL_DN_ICON == item_id) ? "BANNER_ITM_PROG_DETAIL_DN_ICON"  :            \
        (BANNER_ITM_AD_EYE              == item_id) ? "BANNER_ITM_AD_EYE"               :            \
        (BANNER_ITM_RESOLUTION_TXT      == item_id) ? "BANNER_ITM_RESOLUTION_TXT"       :            \
        (BANNER_ITM_TIMER_24            == item_id) ? "BANNER_ITM_TIMER_24"             :            \
        (BANNER_ITM_FRM_3D              == item_id) ? "BANNER_ITM_FRM_3D"               :            \
        (BANNER_ITM_3D_MODE             == item_id) ? "BANNER_ITM_3D_MODE"              :            \
        (BANNER_ITM_3D_FMT              == item_id) ? "BANNER_ITM_3D_FMT"               :            \
        (BANNER_ITM_ASPECT              == item_id) ? "BANNER_ITM_ASPECT"               :            \
        (BANNER_ITM_IPTS_ICON           == item_id) ? "BANNER_ITM_IPTS_ICON"            :            \
        (BANNER_ITM_WIFI_ICON           == item_id) ? "BANNER_ITM_WIFI_ICON"            :            \
        (BANNER_ITM_DOLBY_VISION        == item_id) ? "BANNER_ITM_DOLBY_VISION"         :            \
        (BANNER_ITM_DOLBY_AUDIO         == item_id) ? "BANNER_ITM_DOLBY_AUDIO"          :            \
        (BANNER_ITM_HEADPHONES          == item_id) ? "BANNER_ITM_HEADPHONES"           :            \
        (BANNER_ITM_AUDIO_OUT           == item_id) ? "BANNER_ITM_AUDIO_OUT"            :            \
        "UNKNOWN_ITEM"

#define GET_ITEM_SETS_MASK_STRING(t_item_sets)          nav_bnr_get_item_sets_mask_string(t_item_sets)

#define GET_SI_NOTIFY_CATEGORY(e_category)                                                           \
        (SI_CATEGORY_SUBTITLE_INFO      == e_category) ? "SI_CATEGORY_SUBTITLE_INFO"    :            \
        (SI_CATEGORY_TUNING_INFO        == e_category) ? "SI_CATEGORY_TUNING_INFO"      :            \
        (SI_CATEGORY_EVENT_INFO         == e_category) ? "SI_CATEGORY_EVENT_INFO"       :            \
        (SI_CATEGORY_TTX_INFO           == e_category) ? "SI_CATEGORY_TTX_INFO"         :            \
        (SI_CATEGORY_CH_NUM_INFO        == e_category) ? "SI_CATEGORY_CH_NUM_INFO"      :            \
        (SI_CATEGORY_DATE_TIME_INFO     == e_category) ? "SI_CATEGORY_DATE_TIME_INFO"   :            \
        (SI_CATEGORY_CC_INFO            == e_category) ? "SI_CATEGORY_CC_INFO"          :            \
        (SI_CATEGORY_MHEG5_INFO         == e_category) ? "SI_CATEGORY_MHEG5_INFO"       :            \
        (SI_CATEGORY_FAV_LIST_INFO      == e_category) ? "SI_CATEGORY_FAV_LIST_INFO"    :            \
        (SI_CATEGORY_AUD_STRM_INFO      == e_category) ? "SI_CATEGORY_AUD_STRM_INFO"    :            \
        (SI_CATEGORY_CI_INFO            == e_category) ? "SI_CATEGORY_CI_INFO"          :            \
        (SI_CATEGORY_CUSTOM_1           == e_category) ? "SI_CATEGORY_CUSTOM_1"         :            \
        (SI_CATEGORY_CUSTOM_2           == e_category) ? "SI_CATEGORY_CUSTOM_2"         :            \
        (SI_CATEGORY_CUSTOM_3           == e_category) ? "SI_CATEGORY_CUSTOM_3"         :            \
        "UNKNOWN_CATEGORY"

#define GET_NAV_UI_MSG_STRING(msg_id)                                                                          \
        (NAV_UI_MSG_APP_INITED              == msg_id) ? "NAV_UI_MSG_APP_INITED"                :            \
        (NAV_UI_MSG_BEFORE_SVC_CHANGE       == msg_id) ? "NAV_UI_MSG_BEFORE_SVC_CHANGE"         :            \
        (NAV_UI_MSG_AFTER_SVC_CHANGE        == msg_id) ? "NAV_UI_MSG_AFTER_SVC_CHANGE"          :            \
        (NAV_UI_MSG_BEFORE_SVCS_SWAP        == msg_id) ? "NAV_UI_MSG_BEFORE_SVCS_SWAP"          :            \
        (NAV_UI_MSG_AFTER_SVCS_SWAP         == msg_id) ? "NAV_UI_MSG_AFTER_SVCS_SWAP"           :            \
        (NAV_UI_MSG_BEFORE_TV_MODE_CHANGE   == msg_id) ? "NAV_UI_MSG_BEFORE_TV_MODE_CHANGE"     :            \
        (NAV_UI_MSG_AFTER_TV_MODE_CHANGE    == msg_id) ? "NAV_UI_MSG_AFTER_TV_MODE_CHANGE"      :            \
        (NAV_UI_MSG_EMPTY_SVL               == msg_id) ? "NAV_UI_MSG_EMPTY_SVL"                 :            \
        (NAV_UI_MSG_EMPTY_SPECIFIED_CH_LIST == msg_id) ? "NAV_UI_MSG_EMPTY_SPECIFIED_CH_LIST"   :            \
        (NAV_UI_MSG_FOCUS_CHANGED           == msg_id) ? "NAV_UI_MSG_FOCUS_CHANGED"             :            \
        (NAV_UI_MSG_SHOW_BANNER             == msg_id) ? "NAV_UI_MSG_SHOW_BANNER"               :            \
        (NAV_UI_MSG_HIDE_BANNER             == msg_id) ? "NAV_UI_MSG_HIDE_BANNER"               :            \
        (NAV_UI_MSG_HIDDEN_CH               == msg_id) ? "NAV_UI_MSG_HIDDEN_CH"                 :            \
        (NAV_UI_MSG_AV_STATUS_NOTIFY        == msg_id) ? "NAV_UI_MSG_AV_STATUS_NOTIFY"          :            \
        (NAV_UI_MSG_NO_SIGNAL               == msg_id) ? "NAV_UI_MSG_NO_SIGNAL"                 :            \
        (NAV_UI_MSG_WITH_SIGNAL             == msg_id) ? "NAV_UI_MSG_WITH_SIGNAL"               :            \
        (NAV_UI_MSG_LOCKED_CH               == msg_id) ? "NAV_UI_MSG_LOCKED_CH"                 :            \
        (NAV_UI_MSG_LOCKED_PROG             == msg_id) ? "NAV_UI_MSG_LOCKED_PROG"               :            \
        (NAV_UI_MSG_UNLOCKED                == msg_id) ? "NAV_UI_MSG_UNLOCKED"                  :            \
        (NAV_UI_MSG_APP_PRE_RESUME          == msg_id) ? "NAV_UI_MSG_APP_PRE_RESUME"            :            \
        (NAV_UI_MSG_LOCKED_INP              == msg_id) ? "NAV_UI_MSG_LOCKED_INP"                :            \
        (NAV_UI_MSG_EVENT_READY             == msg_id) ? "NAV_UI_MSG_EVENT_READY"               :            \
        (NAV_UI_MSG_POWER_ON                == msg_id) ? "NAV_UI_MSG_POWER_ON"                  :            \
        (NAV_UI_MSG_SVC_STOPPED             == msg_id) ? "NAV_UI_MSG_SVC_STOPPED"               :            \
        (NAV_UI_MSG_TV_SRC_CHANGED          == msg_id) ? "NAV_UI_MSG_TV_SRC_CHANGED"            :            \
        (NAV_UI_MSG_APP_RESUMED             == msg_id) ? "NAV_UI_MSG_APP_RESUMED"               :            \
        (NAV_UI_MSG_STREAM_NOTIFY           == msg_id) ? "NAV_UI_MSG_STREAM_NOTIFY"             :            \
        (NAV_UI_MSG_AS_APP_PAUSED           == msg_id) ? "NAV_UI_MSG_AS_APP_PAUSED"             :            \
        (NAV_UI_MSG_OTHER_APP_RESUMED       == msg_id) ? "NAV_UI_MSG_OTHER_APP_RESUMED"         :            \
        (NAV_UI_MSG_APP_PAUSING             == msg_id) ? "NAV_UI_MSG_APP_PAUSING"               :            \
        (NAV_UI_MSG_OTHER_APP_PAUSED        == msg_id) ? "NAV_UI_MSG_OTHER_APP_PAUSED"          :            \
        (NAV_UI_MSG_DT_CONDITION_CHANGE     == msg_id) ? "NAV_UI_MSG_DT_CONDITION_CHANGE"       :            \
        "UNKNOWN_MSG"

#define GET_RCU_KEY_STRING(ui4_key_code)                                        \
        (BTN_CURSOR_UP                == ui4_key_code) ? "BTN_CURSOR_UP"        :            \
        (BTN_CURSOR_DOWN              == ui4_key_code) ? "BTN_CURSOR_DOWN"      :            \
        (BTN_PRG_INFO                 == ui4_key_code) ? "BTN_PRG_INFO"         :            \
        (BTN_PRG_DETAIL               == ui4_key_code) ? "BTN_PRG_DETAIL"       :            \
        "ui4_key_code="

extern  HANDLE_T                                h_g_itm_img_empty ;
extern  HANDLE_T                                h_g_itm_img_icon_lock ;
extern  HANDLE_T                                h_g_itm_img_icon_fav ;
extern  HANDLE_T                                h_g_itm_img_icon_fav_full ;
extern  HANDLE_T                                h_g_itm_img_icon_cc ;
extern  HANDLE_T                                h_g_itm_img_icon_ttx ;
extern  HANDLE_T                                h_g_itm_img_icon_up ;
extern  HANDLE_T                                h_g_itm_img_icon_dn ;
extern  HANDLE_T                                h_g_itm_img_icon_ad_eye ;
extern  HANDLE_T                                h_g_itm_img_icon_ad_ear ;
extern  HANDLE_T                                h_g_itm_img_frm_3d ;

/** channel number format **/
#define CH_NUM_DISP_FMT_MAJOR_ONLY              "%d"
#define CH_NUM_DISP_FMT_MAJOR_MINOR             "%d-%d"
#define CH_NUM_DISP_FMT_MAJOR_WITH_ZERO_MINOR   "%d-"

/* NOTICE,
 * c_timer_star will return OSR_INV_ARG if the parameter "ui4_delay" was set as ZERO
 * So, we just stop the timer when receiving a ZERO for parameter "ui4_delay"
 */
 //Cedric note
#define BANNER_TIME_OUT_DURATION_ZERO           (UINT32)0           /* use to stop timer */
#define BANNER_TIME_OUT_DURATION_SHORT          (UINT32)5000        /* 5 seconds */
#define BANNER_TIME_OUT_DURATION_CHANGING       (UINT32)2000        /* 2 seconds */
#define BANNER_TIME_OUT_DURATION_NONE           (UINT32)50          /* 0.05 seconds */
#define BANNER_TIME_OUT_DURATION_LONG           (UINT32)10000       /* 10 seconds */
#define BANNER_HOLD_ON_BEF_STATE_CHG            (UINT32)500         /* 0.5 seconds */
#if (_APP_ATSC_SPT_ == 1)
#define BANNER_CRNT_EVNT_START_TIME_ROUND_UP_SECONDS   (30)         /* in seconds */
#else
#define BANNER_CRNT_EVNT_START_TIME_ROUND_UP_SECONDS   (0)         /* in seconds */
#endif

/* format of program time */
#if (_APP_ATSC_SPT_ == 1)
#define BANNER_CUSTOM_EVENT_START_END_TIME_FORMAT     "%d:%02d %s - %d:%02d %s"
#define BANNER_CUSTOM_EVENT_START_END_EX_TIME_FORMAT  "%d:%02d %s - %d:%02d %s(%d:%02d)"
#define BANNER_CUSTOM_ANTE_MERIDIEM                   "AM"
#define BANNER_CUSTOM_POST_MERIDIEM                   "PM"
#define BANNER_CUSTOM_NOON_HOUR                       (12)
#define BANNER_CUSTOM_MIDNIGHT_HOUR                   (0)
#define BANNER_CUSTOM_NOON_DISPLAY_HOUR               (12)
#define BANNER_CUSTOM_MIDNIGHT_DISPLAY_HOUR           (12)
#else
#define BANNER_CUSTOM_EVENT_START_END_TIME_FORMAT     "%d:%02d%s-%d:%02d%s"
#define BANNER_CUSTOM_EVENT_START_END_EX_TIME_FORMAT  "%d:%02d%s-%d:%02d%s(%d:%02d)"
#define BANNER_CUSTOM_ANTE_MERIDIEM                   ""
#define BANNER_CUSTOM_POST_MERIDIEM                   ""
#define BANNER_CUSTOM_NOON_HOUR                       (0)
#define BANNER_CUSTOM_MIDNIGHT_HOUR                   (0)
#define BANNER_CUSTOM_NOON_DISPLAY_HOUR               (0)
#define BANNER_CUSTOM_MIDNIGHT_DISPLAY_HOUR           (12)
#endif

/** state name/id **/
typedef enum
{
    BANNER_STATE_NONE = 0,
    BANNER_STATE_IDLE,                          /* banner should hide herself once come to the idle state */
    BANNER_STATE_CH,                            /* simple style */
    BANNER_STATE_PCH,                           /* normal style, show channel number and program information */
    BANNER_STATE_PDCH,                          /* full styoe, show channel number, program information and detail informations */
    BANNER_STATE_IPTS ,                         /* input source */
    BANNER_STATE_EMPTY_SVL,                     /* empty svl/specified-svl */
    BANNER_STATE_INPTTING ,                     /* direct change channel by inputting a channel number */
    BANNER_STATE_CHANGING ,                     /* for the state during channel changing */
    BANNER_STATE_SHOW_MSG ,                     /* show message, such as "channel locked", "program locked", "please scan..." */
#ifdef APP_ISDB_SUPPORT
    BANNER_STATE_NON_BRDCSTING ,                /* show non-board-casting message */
#endif
    BANNER_STATE_NO_SIG ,                       /* no signal */
    BANNER_STATE_HIDDEN_CH,                     /* hidden channel */
    BANNER_STATE_RETRIEVE,                      /* retrieve date */
    BANNER_STATE_LAST_VALID_ENTRY               /* only for counting purpose */

} BANNER_STATE_T;

extern BOOL banner_custom_allow_visible (VOID) ;

extern VOID banner_custom_set_ch_state (VOID);
extern VOID nav_banner_ipts_show_itm(VOID);
extern VOID nav_banner_ipts_hide_itm(VOID);
extern VOID nav_banner_scr_mode_show_itm(VOID);
extern VOID nav_banner_scr_mode_hide_itm(VOID);

extern VOID nav_banner_cc_itm_hide(VOID);
extern VOID nav_banner_set_cc_state(BOOL b_on,BOOL visiable);
extern UINT32  a_nav_show_banner_ex(VOID);
extern UINT32  a_nav_show_detail_banner_ex(VOID);
extern UINT32  a_nav_set_show_banner_expecial_btn(BOOL);
extern BOOL  a_nav_get_show_banner_expecial_btn(VOID);

extern VOID nav_banner_set_from_info_key(BOOL  b_is_info_key);
extern VOID nav_banner_set_from_channel_key(BOOL  b_is_channel_key);
extern VOID nav_banner_set_from_digit_pad_info_key(BOOL  b_is_info_key);
extern BOOL nav_banner_get_from_info_key(VOID);
extern BOOL nav_banner_get_from_channel_key(VOID);
extern BOOL nav_banner_get_from_digit_pad_info_key(VOID);
extern VOID nav_show_banner_input_source_msg_hdlr(VOID);

extern VOID nav_banner_set_from_double_info_key(BOOL b_is_double_info_key);
extern BOOL nav_banner_get_from_double_info_key(VOID);

extern INT32 nav_banner_view_detail_info_tts(VOID);

extern VOID nav_banner_set_from_ch_num_key(BOOL  b_is_ch_num_key);
extern BOOL nav_banner_get_from_ch_num_key(VOID);

extern VOID nav_banner_set_hide_mode(BOOL  b_anim);
extern BOOL nav_banner_get_hide_mode();

extern INT32 menu_main_get_visibility(BOOL* b_visible);

extern VOID a_banner_custom_update_banner_timer(VOID);
extern VOID a_banner_custom_update_logo_for_gll(BANNER_SIDERBAR_LOGO e_type,UINT32 delay_time);


#endif /* _BANNER_RC_H_ */

