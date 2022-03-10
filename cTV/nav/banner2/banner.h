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
#ifndef _BANNER_H_
#define _BANNER_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "c_dbg.h"


#include "nav/sys_info/a_sys_info.h"
#include "nav/nav_common.h"
#include "nav/nav_bnr_state_mgr.h"

#include "res/nav/nav_variant.h"

#include "res/nav/banner2/banner_rc.h"

#include "app_util/config/_acfg.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define BANNER_TEXT(_txt)    ((UTF16_T*)L##_txt)

#define BANNER_CHK_FAIL(_ret)  \
    do{ \
        INT32                   i4_banner_ch_fial_ret = _ret ;  \
                                                                \
        if (i4_banner_ch_fial_ret < 0)                          \
    {   \
            DBG_ERROR(("<NAV> banner: Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_banner_ch_fial_ret)); \
            return i4_banner_ch_fial_ret;                       \
    }   \
    }while(FALSE)

#define BANNER_LOG_ON_FAIL(_ret)  \
    do{ \
        INT32                   i4_banner_ch_fial_ret = _ret ;  \
                                                                \
        if (i4_banner_ch_fial_ret < 0)                          \
    {   \
            DBG_ERROR(("<NAV> banner: Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_banner_ch_fial_ret)); \
    }   \
    }while(FALSE)

#define BANNER_BREAK_ON_FAIL(_ret)  \
    {   \
        INT32                   i4_banner_ch_fial_ret = _ret ;  \
                                                                \
        if (i4_banner_ch_fial_ret < 0)                          \
        {                                                       \
            DBG_ERROR(("<NAV> record: Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_banner_ch_fial_ret)); \
        break;  \
        }                                                       \
    }

#define BANNER_CONTINUE_ON_FAIL(_ret)  \
    {   \
        INT32                   i4_banner_ch_fial_ret = _ret ;  \
            \
        if (i4_banner_ch_fial_ret < 0)                          \
        {                                                       \
            DBG_ERROR(("<NAV> record: Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_banner_ch_fial_ret)); \
        continue;  \
        }                                                       \
    }

#define _BANNER_LOG_TYPE_NONE                       (UINT16)0
#define _BANNER_LOG_TYPE_STATE                      MAKE_BIT_MASK_16 (0)
#define _BANNER_LOG_TYPE_ITEM                       MAKE_BIT_MASK_16 (1)
#define _BANNER_LOG_TYPE_VIEW                       MAKE_BIT_MASK_16 (2)
#define _BANNER_LOG_TYPE_MESSAGE                    MAKE_BIT_MASK_16 (3)
#define _BANNER_LOG_TYPE_LOCATION                   MAKE_BIT_MASK_16 (4)
#define _BANNER_LOG_TYPE_OTH_INFO                   MAKE_BIT_MASK_16 (5)

#define BANNER_LOG(ui2_log_type, param)                                        \
    {                                                                          \
        if (banner_enable_this_log(ui2_log_type))                              \
        {                                                                      \
            if (ui2_log_type == _BANNER_LOG_TYPE_STATE)                        \
            {                                                                  \
                DBG_LOG_PRINT (("\t[Banner S]"));                                    \
            }                                                                  \
            else if (                                                          \
                ui2_log_type == _BANNER_LOG_TYPE_ITEM)                         \
            {                                                                  \
                DBG_LOG_PRINT (("\t[Banner I]"));                                    \
            }                                                                  \
            else if (                                                          \
                ui2_log_type == _BANNER_LOG_TYPE_VIEW)                         \
            {                                                                  \
                DBG_LOG_PRINT (("\t[Banner V]"));                                    \
            }                                                                  \
            else if (                                                          \
                ui2_log_type == _BANNER_LOG_TYPE_MESSAGE)                      \
            {                                                                  \
                DBG_LOG_PRINT (("\t[Banner M]"));                                    \
            }                                                                  \
            else if (                                                          \
                ui2_log_type == _BANNER_LOG_TYPE_OTH_INFO)                     \
            {                                                                  \
                DBG_LOG_PRINT (("\t[Banner O]"));                                    \
            }                                                                  \
            else                                                               \
            {                                                                  \
                DBG_LOG_PRINT (("\t[Banner ?]"));                                    \
            }                                                                     \
            DBG_LOG_PRINT (("[%+13s:%s:%-4d]", __FILE__,__FUNCTION__, __LINE__)); \
            c_dbg_stmt param;                                                 \
                                                                               \
        }                                                                      \
    }


#define UP_TO_VIEW_AT_ONCE                          (BOOL)TRUE
#define NEED_SHOW_BANNER_VIEW                       (BOOL)TRUE

/* for virtual state */
#define BANNER_STATE_VIRTUAL_ALL_STATE              (UINT8)255
#define BANNER_STATE_VIRTUAL_FINAL                  (UINT8)254  /* it is not a truly state, just for changing to final state */
#define BANNER_STATE_VIRTUAL_TV_DEFAULT             (UINT8)253  /* it is not a truly state, just for changing to tv default state */

#define BANNER_STATE_PRI_TV_DEFAULT                 (UINT8)255

/* force to unlock */
#define BANNER_STATE_PRI_FORCE_TO_UNLOCK            (UINT8)0

/** ====================== structure for ITEMs ======================= **/
/*  ITEM type  */
typedef enum
{
    BANNER_ITEM_TYPE_FRM = 0 ,          /* frame item */
    BANNER_ITEM_TYPE_TEXT ,             /* text item */
    BANNER_ITEM_TYPE_ICON ,             /* icon item */
    BANNER_ITEM_TYPE_LAST_ENTRY         /* for counting purpose */
}BANNER_ITEM_TYPE_T ;

typedef struct
{
    UINT8                               ui1_item_id ;
    BANNER_ITEM_TYPE_T                  e_item_type ;
    HANDLE_T*                           ph_handle ;
    GL_RECT_T*                          pt_rect;

} BANNER_ITEM_INFO_T ;

/** ===================== structure for STATEs ======================= **/
typedef VOID (*banner_custom_pre_enter_state)(
    UINT8                               ui1_state_id
    ) ;

typedef struct
{
    UINT8                               ui1_state_id ;
    UINT8                               ui1_state_pri ;
    BNR_ITEM_SET_T                      t_item_includs ;
    UINT32                              ui4_time_out_duration ;

    /* when time out, it will change to a specified state if
     * TIME_OUT_OPERATION_TYPE is NAV_BNR_STATE_TMOT_BY_STATE
     */
    UINT8                               ui1_chg_to_state_when_timeout ;

    banner_custom_pre_enter_state       pf_pre_process_when_enter ;
    BOOL                                b_lock_when_enter ;
    BOOL                                b_set_as_fnl_when_enter ;

} BANNER_STATE_INFO_T ;

/** ======== strcture for state handler and SysInfo handler  ========== **/
typedef enum
{
    BANNER_NFY_TYPE_UPDATE_STATE = 0 ,                      /* state updated */
    BANNER_NFY_TYPE_UPDATE_ITEM,                            /* item updated */
    BANNER_NFY_TYPE_PRE_UPDATE_VIEW,                        /* pre view update */
    BANNER_NFY_TYPE_POST_UPDATE_VIEW,                       /* post view udated */
    BANNER_NFY_TYPE_LAST_ENTRY

} BANNER_NTF_TYPE ;

typedef struct
{
    UINT8                               ui1_state ;

} BANNER_NTF_DATE_UP_STATE_T ;

typedef struct
{
    UINT8                               ui1_item_id;
    UTF16_T*                            pw2s_text;          /* for text item */
    HANDLE_T                            h_icon;             /* for icon item */

} BANNER_NTF_DATE_UP_ITEM_T ;

typedef struct
{
    BANNER_NTF_TYPE                     e_nfy_type ;

    union
    {
        /* state change notify */
        BANNER_NTF_DATE_UP_STATE_T      t_up_state ;

        /* item update notify */
        BANNER_NTF_DATE_UP_ITEM_T       t_up_item ;

        /* view update notify */
        BNR_ITEM_SET_T                  t_view_updated_mask_pre ;     /* valid for BANNER_NFY_TYPE_PRE_UPDATE_VIEW, topmost-bit for STATE, others for ITEMS */
        BNR_ITEM_SET_T                  t_view_updated_mask_post ;    /* valid for BANNER_NFY_TYPE_POST_UPDATE_VIEW, topmost-bit for STATE, others for ITEMS */

    } u_nfy_data ;

} BANNER_UPDATE_NFY_T ;

typedef INT32 (*banner_state_item_update_listener)(
    BANNER_UPDATE_NFY_T                 t_update
    ) ;

/** ====================== strcture for banner  ======================= **/
typedef struct _BANNER_T
{
    BANNER_STATE_INFO_T*                pt_state_info ;
    BANNER_ITEM_INFO_T*                 pt_item_info ;
    UINT16                              ui2_state_num ;
    UINT16                              ui2_item_num ;
    HANDLE_T                            h_root_frame ;
    HANDLE_T                            h_toast_view;
    UINT8                               ui1_def_tv_state ;  /* default TV state */
    UINT8                               ui1_crnt_state ;

    UINT16                              ui2_si_listener_id ;
    UINT16                              ui2_gui_lang_nfy;
    BOOL                                b_excl_comp_is_on ;
    UINT16                              ui2_msg_id;
    UINT16                              i2_g_log_type ;     /* log state/item information */
} BANNER_T;

/*for check if these items updated to view using*/
typedef enum _UPDATE_FINISH_ITEM_IDX_T
{
    BANNER_ITM_UPDATED_RESOLUTION_TXT = 0,
    BANNER_ITM_UPDATED_AUDIO_FARMAT,
    BANNER_ITM_UPDATED_ASPECT
}NAV_BNR_UPDATED_ITEM_IDX_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

/** function for state_handler **/
extern INT32 banner_state_handler_init (
    banner_state_item_update_listener   pf_reporter
    ) ;
#ifdef APP_ZOOM_MODE_SUPPORT
extern VOID banner_set_first_power_on_state(BOOL b_first_power_on);
#endif
/** function for SysInfo_handler **/
extern INT32 banner_sys_info_handler_init (
    banner_state_item_update_listener   pf_reporter ,
    UINT16*                             pui2_si_listener_id
    ) ;

/** function for control & model **/
extern INT32 banner_change_state_to(
    UINT8                               ui1_state_name,
    BOOL                                b_need_show_banner_view,
    BOOL                                b_up_state_to_view_at_once
    ) ;

extern UINT16 banner_get_total_state_num (VOID) ;

extern UINT16 banner_get_total_item_num (VOID) ;

extern BANNER_STATE_INFO_T* banner_get_state_info (
    UINT8                               ui1_state_id
    );

extern BANNER_ITEM_INFO_T* banner_get_item_info (
    UINT8                               ui1_item_id
    ) ;

extern BOOL banner_enable_this_log (
    UINT16                              ui2_log_type
    ) ;

extern CHAR* banner_get_last_app_when_switch_app (VOID) ;

extern BOOL banner_is_under_excl (VOID) ;

extern INT32 banner_set_default_tv_state (
    UINT8                               ui1_state
    ) ;

extern INT32 banner_get_crnt_state(
    UINT8*                              pui1_state
    ) ;

extern INT32 banner_rcu_key_handler(
    UINT32                              ui4_key_code
    );

extern INT32 banner_unlock_state(
    UINT8                               ui1_state
    ) ;

extern INT32 banner_request_resend_item_info (
    VOID
    ) ;

/** function for view **/
extern INT32 banner_view_update_state (
    UINT8                               ui1_state
    );

extern INT32 banner_view_set_visible (
    BOOL                                b_show
    );

extern INT32 banner_view_refresh (
    BOOL                                b_at_once
    );

extern BOOL banner_view_is_on_show (    VOID ) ;

extern INT32 banner_view_update_item (
    UINT8                               ui1_item_id,
    UTF16_T*                            pw2s_text,          /* for text item */
    HANDLE_T                            h_icon,             /* for icon item */
    BOOL                                b_up_to_view_at_once
    );

extern INT32 banner_view_freeze (
    BOOL                                b_freeze,
    UINT32                              ui4_freeze_key
    );

extern INT32 banner_view_show (
    BOOL                                b_is_excl_on
    );

extern INT32 banner_view_init(
    BANNER_T*                           pt_this,
    HANDLE_T                            h_root_frame,
    banner_state_item_update_listener   pf_reporter
    );

extern INT32 banner_view_deinit        (VOID) ;
extern INT32 banner_view_hide          (VOID) ;
extern INT32 banner_view_set_focus     (VOID) ;

/** ================= function for customization ===================== **/
extern INT32 banner_custom_init (
    HANDLE_T                            h_parent,
    APP_COLOR_TYPE_T                    e_color_type,
    BANNER_STATE_INFO_T**               pt_states_info,
    BANNER_ITEM_INFO_T**                pt_items_info,
    UINT16*                             pui2_state_num,
    UINT16*                             pui2_item_num,
    HANDLE_T*                           ph_root_frame
    );

extern INT32 banner_custom_handle_msg (
    NAV_UI_MSG_T*                       pt_ui_msg,
    VOID*                               pv_arg1
    ) ;

extern INT32 banner_custom_rcu_key_handler (
    UINT32                              ui4_key_code
    ) ;

extern INT32 banner_custom_before_view_updated (
    BNR_ITEM_SET_T                      t_updated_mask
    ) ;

extern INT32 banner_custom_after_view_updated (
    BNR_ITEM_SET_T                      t_updated_mask
    ) ;

extern UINT8 banner_custom_get_idle_state               (VOID) ;
extern INT32 banner_custom_preset_data_when_nav_inited  (VOID) ;

extern INT32 nav_bnr_timer_reload(HANDLE_T                        h_timer,
                    UINT32                          ui4_duration,
                    NAV_BNR_STATE_TIMER_OPER_TYPE_T e_timer_op);
extern UINT8 nav_bnr_timer_state(NAV_BNR_STATE_TIMER_OPER_TYPE_T e_timer_op);

/** function for cli **/
extern UINT16 banner_get_log_type (VOID) ;

extern VOID banner_set_log_type     (
    UINT16                              ui2_log_type
    ) ;

#ifdef CLI_SUPPORT
extern INT32 banner_cli_init        (
    BANNER_T*                           pt_this
    ) ;
#endif

extern VOID a_banner_view_set_delay_show_banner (BOOL b_is_show, INT32 i4_delay_time);
extern VOID a_banner_view_disable_delay_show_banner (VOID);

#ifdef APP_TTS_SUPPORT

extern VOID banner_view_tts_reset_updated_mask();
extern VOID banner_view_tts_fill_string();
extern INT32 banner_tts_play(UTF16_T* pws_content);

#endif

extern INT32 banner_item_lock(VOID);
extern INT32 banner_item_unlock(VOID);
extern BOOL banner_view_tv_info_updeted_is_finished(VOID);
extern VOID banner_view_tv_info_updeted_update(NAV_BNR_UPDATED_ITEM_IDX_T e_item);
extern VOID banner_view_tv_info_updeted_erase(VOID);

extern VOID banner_view_set_ch_name_split_flag(BOOL b_falg);
extern VOID banner_show_msg(UINT16 ui2_msg_id);
extern VOID banner_hide_msg();

//extern INT32 banner_show_siderbar(BANNER_SIDERBAR_HDR e_hdr);
//extern INT32 banner_show_siderbar_ex(BANNER_SIDERBAR_EX e_type);
extern INT32 banner_show_siderbar_logo(BANNER_SIDERBAR_LOGO e_type);
extern INT32 banner_hide_siderbar_logo(BANNER_SIDERBAR_LOGO e_type);
extern VOID banner_view_update_logo_flag(BANNER_SIDERBAR_LOGO e_type);
extern BOOL banner_hide_sidebar(VOID);

extern INT32 banner_cust_evt_handle_chg_hdr(UINT32 e_update_reason,UINT32 data);
extern INT32 banner_sys_audio_stream_update(VOID);
extern BOOL banner_view_set_name_update_flag(BOOL val);
extern BOOL banner_view_get_name_update_flag(VOID);
extern INT32 banner_view_update_scrl_banner_name(const UTF16_T *src,UINT32 len);

extern INT32 banner_view_mm_update_start_timer(VOID);
extern INT32 banner_view_mm_update_stop_timer(VOID);

#if (CUSTOMER == VIZIO)
extern INT32 banner_cust_evt_handle_headphones(BOOL b_connected);
#endif

#endif /* _BANNER_H_ */
