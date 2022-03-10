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
 * $RCSfile: cc_info.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_scc.h"
#include "u_scdb.h"
#include "u_sm_cc_hdlr.h"
#include "c_sm_cc_hdlr.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_cfg.h"
#include "c_wgl.h"
#include "c_iom.h"
#include "am/a_am.h"
#include "app_client.h"
#include "app_util/a_cfg.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "nav/cc_info/a_cc_info.h"
#include "nav/cc_info/cc_info.h"
#include "nav/cc_info/cc_info_view.h"
#include "nav/cc_loop.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/menu2/menu_custom.h"
#include "msgconvert/msgconvert.h"
#include "app_client.h"

#if !(defined(APP_DVBT_SUPPORT) || defined(APP_ISDB_SUPPORT))

#ifdef APP_NAV_CI_SAVE_CC
#undef APP_NAV_CI_SAVE_CC
#endif

#ifdef APP_NAV_CI_SAVE_CC
#include "res/nav/cc_info/nav_cc_info_rc.h"
#endif
#include "rest/a_rest_event.h"

#include "res/nav/nav_dbg.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define _NAV_CI_SELECT_DELAY_DUR             (2000)   /* in ms */
#define _NAV_CI_UPDATE_DELAY_DUR             (500)    /* in ms */
#define _NAV_CI_GUI_LANG_NULL                ((UINT8)255)

#define _NAV_CI_CFG_ENABLE_ID                CFG_MAKE_ID(APP_CFG_GRPID_CC, APP_CFG_RECID_CC_ENABLED)
#define _NAV_CI_CFG_ANALOG_ID                CFG_MAKE_ID(APP_CFG_GRPID_CC, APP_CFG_RECID_ANLG_CC)
#define _NAV_CI_CFG_DIG_ID                   CFG_MAKE_ID(APP_CFG_GRPID_CC, APP_CFG_RECID_DIG_CC)

#ifdef APP_NAV_CI_FULL_ANALOG_CC
#define _NAV_CI_CC_RESET_METHOD              (NTSC_CC_ALL | NTSC_TT_ALL)
#else
#define _NAV_CI_CC_RESET_METHOD              (NTSC_CC_ALL)
#endif

#define _NAV_CI_INFO_TO_UI_T                UINT32
#define _NAV_CI_INFO_TUI_EMPTY              ((_NAV_CI_INFO_TO_UI_T)          0)
#define _NAV_CI_INFO_TUI_CC_NOT_READY       ((_NAV_CI_INFO_TO_UI_T) 0x00000001)
#define _NAV_CI_INFO_TUI_CC_QUERY           ((_NAV_CI_INFO_TO_UI_T) 0x00000002)
#define _NAV_CI_INFO_TUI_CC_WITHOUT         ((_NAV_CI_INFO_TO_UI_T) 0x00000004)
#define _NAV_CI_INFO_TUI_CC_LANG_NOT_READY  ((_NAV_CI_INFO_TO_UI_T) 0x00000008)
#define _NAV_CI_INFO_TUI_CC_LANG_QUERY      ((_NAV_CI_INFO_TO_UI_T) 0x00000010)
#define _NAV_CI_INFO_TUI_CC_LANG_WITHOUT    ((_NAV_CI_INFO_TO_UI_T) 0x00000020)
#define _NAV_CI_INFO_TUI_DSCRPTR_NOT_READY  ((_NAV_CI_INFO_TO_UI_T) 0x00000040)
#define _NAV_CI_INFO_TUI_DSCRPTR_QUERY      ((_NAV_CI_INFO_TO_UI_T) 0x00000080)
#define _NAV_CI_INFO_TUI_DSCRPTR_WITHOUT    ((_NAV_CI_INFO_TO_UI_T) 0x00000100)
#define _NAV_CI_INFO_TUI_STATE_ITEM         ((_NAV_CI_INFO_TO_UI_T) 0x00000200)

#define _NAV_CI_INFO_TUI_CC_TYPE_MASK       (_NAV_CI_INFO_TUI_CC_NOT_READY |                \
                                             _NAV_CI_INFO_TUI_CC_QUERY |                    \
                                             _NAV_CI_INFO_TUI_CC_WITHOUT)

#define _NAV_CI_INFO_TUI_CC_LANG_MASK       (_NAV_CI_INFO_TUI_CC_LANG_NOT_READY |           \
                                             _NAV_CI_INFO_TUI_CC_LANG_QUERY |               \
                                             _NAV_CI_INFO_TUI_CC_LANG_WITHOUT)

#define _NAV_CI_INFO_TUI_DETAIL_MASK        (_NAV_CI_INFO_TUI_CC_TYPE_MASK |                \
                                             _NAV_CI_INFO_TUI_CC_LANG_MASK)

#define _NAV_CI_INFO_TUI_DSCRPTR_MASK       (_NAV_CI_INFO_TUI_DSCRPTR_NOT_READY |           \
                                             _NAV_CI_INFO_TUI_DSCRPTR_QUERY |               \
                                             _NAV_CI_INFO_TUI_DSCRPTR_WITHOUT)

#define _NAV_CI_INFO_DELAY_UPDATE_MASK      (_NAV_CI_INFO_TUI_CC_QUERY |                    \
                                             _NAV_CI_INFO_TUI_CC_LANG_QUERY |               \
                                             _NAV_CI_INFO_TUI_DSCRPTR_QUERY)

#define _NAV_CI_INFO_TUI_IS_DETAIL_NOT_READY(_e_type)                                       \
(                                                                                           \
    ((_e_type) & _NAV_CI_INFO_TUI_CC_NOT_READY)                                             \
)

#define _NAV_CI_IS_SAME_AUTO_FILTER(_t_filter_1, _t_filter_2)                                   \
(                                                                                               \
    (SM_CC_TYPE_AUTO_SEL == (_t_filter_1).e_cc_type &&                                              \
    (_t_filter_1).e_cc_type == (_t_filter_2).e_cc_type &&                                       \
    (_t_filter_1).u.t_auto_sel.b_prefer_dtvcc == (_t_filter_2).u.t_auto_sel.b_prefer_dtvcc &&   \
    (_t_filter_1).u.t_auto_sel.ui1_ntsccc_mask == (_t_filter_2).u.t_auto_sel.ui1_ntsccc_mask && \
    (_t_filter_1).u.t_auto_sel.ui8_dtvcc_mask == (_t_filter_2).u.t_auto_sel.ui8_dtvcc_mask      \
    ) ? TRUE : FALSE                                                                                \
)

#define _NAV_CI_IS_EMPTY_AUTO_FILTER(_t_filter)                                             \
(                                                                                           \
    (SM_CC_TYPE_AUTO_SEL == (_t_filter).e_cc_type &&                                        \
     (0 == (_t_filter).u.t_auto_sel.ui1_ntsccc_mask) &&                                     \
     (0 == (_t_filter).u.t_auto_sel.ui8_dtvcc_mask)) ? TRUE : FALSE                         \
)

#define _NAV_CI_IS_IGNORE_FILTER(_t_filter)                                                 \
(                                                                                           \
    (SM_CC_TYPE_IGNORE == (_t_filter).e_cc_type) ? TRUE : FALSE                             \
)

#define _NAV_CI_COPY_FILTER(_pt_this, _e_dest_grp, _e_src_grp)                                  \
{                                                                                               \
    (_pt_this)->at_grp[(_e_dest_grp)].t_cc = (_pt_this)->at_grp[(_e_src_grp)].t_cc;             \
    (_pt_this)->at_grp[(_e_dest_grp)].t_user_cc = (_pt_this)->at_grp[(_e_src_grp)].t_user_cc;   \
}

#define _NAV_CI_EMPTY_AUTO_FILTER(_t_filter)                                                \
{                                                                                           \
    (_t_filter).e_cc_type = SM_CC_TYPE_AUTO_SEL;                                            \
    (_t_filter).u.t_auto_sel.b_prefer_dtvcc = _NAV_CI_IS_PREFER_DTVCC();                    \
    (_t_filter).u.t_auto_sel.ui8_dtvcc_mask = 0;                                            \
    (_t_filter).u.t_auto_sel.ui1_ntsccc_mask = 0;                                           \
}

#define _NAV_CI_SET_FILTER_IGNORE(_t_filter)                                                \
{                                                                                           \
    /*reset cc setting*/                                                                    \
    (_t_filter).e_cc_type = SM_CC_TYPE_IGNORE;                                              \
    (_t_filter).u.ui1_service_num = 0xff;                                                   \
}

#define _NAV_CI_ZERO_FILTER(_pt_this, _e_grp, _b_inc_user)                                  \
{                                                                                           \
    /*reset cc setting*/                                                                    \
    (_pt_this)->at_grp[(_e_grp)].t_cc.e_cc_type = SM_CC_TYPE_IGNORE;                        \
    (_pt_this)->at_grp[(_e_grp)].t_cc.u.ui1_service_num = 0xff;                             \
                                                                                            \
    /*backup cc*/                                                                           \
    if(_b_inc_user)                                                                         \
    {                                                                                       \
        (_pt_this)->at_grp[(_e_grp)].t_user_cc = (_pt_this)->at_grp[(_e_grp)].t_cc;         \
    }                                                                                       \
}

typedef enum __NAV_CI_SWITCH_EXEC_MODE_T
{
    _NAV_CI_SEM_NORMAL = 0,
    _NAV_CI_SEM_WAIT_EVENT,
    _NAV_CI_SEM_DELAY,
    _NAV_CI_SEM_IMMEDIATE
} _NAV_CI_SWITCH_EXEC_MODE_T;

/*stream status*/
typedef UINT8                                   NAV_CC_STREAM_STATUS_T;
#define NAV_CC_STREAM_STATUS_CLOSED             ((NAV_CC_STREAM_STATUS_T) 0)
#define NAV_CC_STREAM_STATUS_OPENING            ((NAV_CC_STREAM_STATUS_T) 1)
#define NAV_CC_STREAM_STATUS_OPENED             ((NAV_CC_STREAM_STATUS_T) 2)

/*cc state*/
typedef UINT32                                  CC_STATE_T;
#define CC_STATE_DEFAULT                        ((CC_STATE_T)0x80000000)
#define CC_STATE_UNKNOWN                        ((CC_STATE_T)0x0)
#define CC_STATE_WITH_CC                        ((CC_STATE_T)0x1)
#define CC_STATE_WITHOUT_CC                     ((CC_STATE_T)0x2)
#define CC_STATE_LAST_VALID_ENTRY               ((CC_STATE_T)0x3)            /* only for counting purpose */


#define _NAV_CC_STATE_IS_DEFAULT(_e_state)              (0 != (CC_STATE_DEFAULT & (_e_state)))
#define _NAV_CC_STATE_IS_NOT_DEFAULT(_e_state)          (0 == (CC_STATE_DEFAULT & (_e_state)))
#define _NAV_CC_STATE_IS_WITHOUT(_e_state)              (CC_STATE_WITHOUT_CC == ((_e_state) & (~CC_STATE_DEFAULT)))
#define _NAV_CC_STATE_IS_WITH(_e_state)                 (CC_STATE_WITH_CC == ((_e_state) & (~CC_STATE_DEFAULT)))
#define _NAV_CC_STATE_SET_WITHOUT(_e_state)                                         \
{                                                                                   \
    (_e_state) = CC_STATE_WITHOUT_CC | ((_e_state) & CC_STATE_DEFAULT);             \
}
#define _NAV_CC_STATE_SET_WITH(_e_state)                                            \
{                                                                                   \
    (_e_state) = CC_STATE_WITH_CC | ((_e_state) & CC_STATE_DEFAULT);                \
}
#define _NAV_CC_STATE_SET_NOT_DEFAULT(_e_state)                                     \
{                                                                                   \
    (_e_state) &= (~CC_STATE_DEFAULT);                                              \
}
#define _NAV_CC_STATE_SET_UNKNOWN_DEFAULT(_e_state)                                 \
{                                                                                   \
    (_e_state) = CC_STATE_DEFAULT;                                                  \
}

typedef struct __NAV_CC_SETTING_T
{
    SM_CC_FILTER_T          t_cc;                     /*current cc filter*/
    SM_CC_FILTER_T          t_user_cc;                /*cc filter by user, from toggle or default*/
    CC_STATE_T              e_cc_state;               /*state for User operation and UI display: DEFAULT, WITH, WITHOUT*/
} _NAV_CC_SETTING_T;

typedef UINT32                                  _NAV_CI_STATUS_FLAG_T;
#define _NAV_CI_STATUS_FLAG_EMPTY               ((_NAV_CI_STATUS_FLAG_T) 0)
#define _NAV_CI_STATUS_FLAG_ACTIVE              ((_NAV_CI_STATUS_FLAG_T) 0x00000001)
#define _NAV_CI_STATUS_FLAG_INFO_STABLE         ((_NAV_CI_STATUS_FLAG_T) 0x00000002)
#define _NAV_CI_STATUS_FLAG_FOCUS_CHANGING      ((_NAV_CI_STATUS_FLAG_T) 0x00000004)
#define _NAV_CI_STATUS_FLAG_DISABLE_CC          ((_NAV_CI_STATUS_FLAG_T) 0x00000008)

typedef struct __NAV_CI_T
{
    NAV_CI_VIEW_HANDLER_T   t_view_handler;           /*UI handler*/
    NAV_CI_UI_INFO_T        t_last_notify;            /*keep last notification cc info*/
    _NAV_CC_SETTING_T       at_grp[TV_WIN_ID_LAST_VALID_ENTRY];
    TV_WIN_ID_T             e_focus_grp;
    HANDLE_T                h_focus_svctx;             /*handle of service context. Sync this handle with Nav-Ctrler everytime the CC-Info is activated.*/
    HANDLE_T                h_delay_timer;            /*handle of timer for delaying cc selection*/
    HANDLE_T                h_update_timer;             /*handle of timer for delaying cc selection*/
    HANDLE_T                h_excluse_timer;            /*handle of timer for exclusing other osd*/
    GL_HPLANE_T             h_cc_plane;               /*handle of graphic plane for displaying cc. Sync this handle with Nav-Ctrler everytime the CC-Info is activated.*/
    VOID*                   pv_view;                  /*CC-Info-View's instance*/
    _NAV_CI_STATUS_FLAG_T   e_status_flag;
    NAV_CI_EXEC_COND_T      e_exec_cond;              /*cc execution condition*/
    UINT16                  ui2_cc_cfg_nfy;           /*id of config field to receive cc setting change*/
    NAV_CC_STREAM_STATUS_T  e_stream_status;            /*status of CC stream*/
    BOOL                    b_is_select_req_queued;
    BOOL                    b_first_svc_xng;
    BOOL                    b_channel_dirty;          /*channel is changed in other application or not*/
#ifdef APP_IPCC_SUPPORT
    BOOL                    b_ipcc_visible;           /*Indicate the IPCC is visible or not*/
    HANDLE_T                h_iom;
#endif
} _NAV_CI_T;
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _NAV_CI_T               t_g_cc_info;
static NAV_CI_UI_CC_DETAIL_T   t_g_empty_detail;    /*only for coding*/

/*-----------------------------------------------------------------------------
 * public declarations
 *---------------------------------------------------------------------------*/
 extern NAV_MODEL_T     t_g_navigator;

/*-----------------------------------------------------------------------------
 * customization declarations
 *---------------------------------------------------------------------------*/
#ifdef APP_NAV_CI_SAVE_CC
    #define NAV_CI_GET_SAVE_CFG(_b_save)                                        \
    {                                                                           \
        (_b_save) = TRUE;                                                       \
    }
#else
    #define NAV_CI_GET_SAVE_CFG(_b_save)                                        \
    {                                                                           \
        (_b_save) = FALSE;                                                      \
    }
#endif

#ifdef APP_NAV_DEFAULT_DTVCC_FIRST
    #define _NAV_CI_IS_PREFER_DTVCC()           (TRUE)
#else
    #define _NAV_CI_IS_PREFER_DTVCC()           (FALSE)
#endif

#ifdef APP_NAV_CI_SAVE_CC_ONOFF
    #define _NAV_CI_SAV_ONOFF_CFG(_e_exec_cond, _i4_ret)                        \
    {                                                                           \
        (_i4_ret) = _nav_ci_save_onoff_cfg((_e_exec_cond));                     \
    }

    static INT32 _nav_ci_save_onoff_cfg(NAV_CI_EXEC_COND_T              e_exec_cond);

#else
    #define _NAV_CI_SAV_ONOFF_CFG(_e_exec_cond, _i4_ret)                        \
    {                                                                           \
        (_i4_ret) = NAVR_OK;                                                    \
    }
#endif

#ifdef APP_NAV_CI_SAVE_CC
    #define _NAV_CI_SAVE_SELECTION(_pt_this)                                    \
    {                                                                           \
        _nav_ci_save_selection((_pt_this));                                     \
    }

    static INT32 _nav_ci_save_selection(_NAV_CI_T*                      pt_this);
#else
    #define _NAV_CI_SAVE_SELECTION(_pt_this)                                    \
    {                                                                           \
    }
#endif

#ifdef APP_NAV_CI_AUTO_SELECT_WITH_TOGGLE
    #define APP_NAV_CI_AUTO_SELECT 1
#endif

/**/
#ifdef APP_NAV_CI_AUTO_SELECT_WITH_TOGGLE
    #define _NAV_CI_IS_AUTO_WITH_TOGGLE()   (TRUE)
#else
    #define _NAV_CI_IS_AUTO_WITH_TOGGLE()   (FALSE)
#endif

#ifndef APP_NAV_CI_AUTO_SELECT
    #define _NAV_CI_IS_AUTO_SELECT()            (FALSE)
    #define _NAV_CI_CHECK_DESCRIPTOR            (_NAV_CI_INFO_TUI_DSCRPTR_QUERY)

    static BOOL _nav_ci_set_default_ntsc_cc_filter(SM_CC_FILTER_T*      pt_cc_filter);

    static BOOL _nav_ci_set_default_dtv_cc_filter(_NAV_CI_T*            pt_this,
                                                  SM_CC_FILTER_T*       pt_cc_filter);
#else
    #define _NAV_CI_IS_AUTO_SELECT()            (TRUE)
    #define _NAV_CI_CHECK_DESCRIPTOR            (_NAV_CI_INFO_TUI_EMPTY)
#endif

#ifdef APP_NAV_DISABLE_CC_IN_PIP_POP
    #define _NAV_CI_TV_MODE_XNG_NFY_HANDLER(_pt_this, _pt_info)         \
    {                                                                   \
        _nav_ci_tv_mode_xng_nfy_handler((_pt_this), (_pt_info));        \
    }

    static VOID _nav_ci_tv_mode_xng_nfy_handler(_NAV_CI_T*              pt_this,
                                                NAV_TV_MODE_XNG_INFO_T* pt_info);
#else
    #define _NAV_CI_TV_MODE_XNG_NFY_HANDLER(_pt_this, _pt_info)         \
    {                                                                   \
    }
#endif

#ifdef APP_NAV_NO_1_TIME_DELAY
    #define _NAV_CI_IS_ALWAYS_DELAY()           (FALSE)
#else
    #define _NAV_CI_IS_ALWAYS_DELAY()           (TRUE)
#endif

#ifndef NAV_CI_CUSTOM_DEF_DTVCC_BYTE_1
    #define NAV_CI_CUSTOM_DEF_DTVCC_BYTE_1      ((UINT8) 0) /*x7E for Service1~Service6*/
#endif

#ifndef NAV_CI_CUSTOM_DEF_DTVCC_BYTE_2
    #define NAV_CI_CUSTOM_DEF_DTVCC_BYTE_2      ((UINT8) 0)
#endif

#ifndef NAV_CI_CUSTOM_DEF_DTVCC_BYTE_3
    #define NAV_CI_CUSTOM_DEF_DTVCC_BYTE_3      ((UINT8) 0)
#endif

#ifndef NAV_CI_CUSTOM_DEF_DTVCC_BYTE_4
    #define NAV_CI_CUSTOM_DEF_DTVCC_BYTE_4      ((UINT8) 0)
#endif

#ifndef NAV_CI_CUSTOM_DEF_DTVCC_BYTE_5
    #define NAV_CI_CUSTOM_DEF_DTVCC_BYTE_5      ((UINT8) 0)
#endif

#ifndef NAV_CI_CUSTOM_DEF_DTVCC_BYTE_6
    #define NAV_CI_CUSTOM_DEF_DTVCC_BYTE_6      ((UINT8) 0)
#endif

#ifndef NAV_CI_CUSTOM_DEF_DTVCC_BYTE_7
    #define NAV_CI_CUSTOM_DEF_DTVCC_BYTE_7      ((UINT8) 0)
#endif

#ifndef NAV_CI_CUSTOM_DEF_DTVCC_BYTE_8
    #define NAV_CI_CUSTOM_DEF_DTVCC_BYTE_8      ((UINT8) 0)
#endif

#define APP_DISABLE_COMP_SOURCE		1

static BOOL b_cc_info_debug = 0;

BOOL nav_ci_get_debug_level()
{
   return b_cc_info_debug;
}

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/* lifecycle functions */
static INT32 _nav_ci_init(NAV_CONTEXT_T*                                pt_ctx);

static INT32 _nav_ci_deinit(VOID);

static BOOL _nav_ci_is_key_handler(NAV_CONTEXT_T*                       pt_ctx,
                                   UINT32                               ui4_key_code);

static INT32 _nav_ci_activate(NAV_CONTEXT_T*                            pt_ctx,
                              UINT32                                    ui4_key_code);

static INT32 _nav_ci_hide(VOID);

static INT32 _nav_ci_handle_msg(NAV_CONTEXT_T*                          pt_ctx,
                                NAV_UI_MSG_T*                           pt_ui_msg,
                                VOID*                                   pv_arg1);

static INT32 _nav_ci_cfg_init(_NAV_CI_T*                                pt_this);

static VOID _nav_ci_cfg_deinit(_NAV_CI_T*                               pt_this);

static VOID _nav_ci_stream_nfy_handler(_NAV_CI_T*                       pt_this,
                                       NAV_STREAM_NOTIFY_TYPE_T         e_type,
                                       _NAV_CI_INFO_TO_UI_T*            pe_to_ui);

static INT32 _nav_ci_focus_xng_nfy_handler(_NAV_CI_T*                   pt_this,
                                           TV_WIN_ID_T                  e_new_focus);

/*cc filter setting*/
static VOID _nav_ci_sync_exec_cond(_NAV_CI_T*                           pt_this);

static INT32 _nav_ci_set_cc_filter(_NAV_CI_T*                           pt_this,
                                   const NAV_XNG_SRC_TRGT_T*            pt_xng_info);

static BOOL _nav_ci_default_cc_strm_comp_filter(UINT16                  ui2_num_recs,
                                                UINT16                  ui2_idx,
                                                const STREAM_COMP_ID_T* pt_comp_id,
                                                const SCDB_REC_T*       pt_scdb_rec,
                                                VOID*                   pv_tag);

static INT32 _nav_ci_change_cc(_NAV_CI_T*                               pt_this,
                               NAV_CI_SWITCH_METHOD_T                   e_method,
                               _NAV_CI_SWITCH_EXEC_MODE_T               e_exec_mode,
                               BOOL                                     b_save,
                               _NAV_CI_INFO_TO_UI_T                     e_to_ui);

static INT32 _nav_ci_apply_cc_selection(_NAV_CI_T*                      pt_this,
                                        _NAV_CI_SWITCH_EXEC_MODE_T      e_exec_mode,
                                        _NAV_CI_INFO_TO_UI_T*           pe_to_ui);

static INT32 _nav_ci_sync_crnt_filter(_NAV_CI_T*                        pt_this);

/*helper function*/
static SVCTX_CAPABILITY_T _nav_ci_get_focus_capability(_NAV_CI_T*       pt_this);

static INT32 _nav_ci_update_cc_info(_NAV_CI_T*                          pt_this,
                                    _NAV_CI_INFO_TO_UI_T                e_to_ui);

static BOOL _nav_ci_scdb_is_default_ntsc_cc(UINT8                       ui1_default_anlg_cc,
                                            const SCDB_REC_T*           pt_scdb_rec);

static BOOL _nav_ci_scdb_is_default_dtv_cc(UINT8                        ui1_default_dig_cc,
                                           const SCDB_REC_T*            pt_scdb_rec);

static BOOL _nav_ci_is_with_dscrptr(_NAV_CI_T*                          pt_this);

static BOOL _nav_ci_is_support_digital_cc(_NAV_CI_T*                    pt_this);

static INT32 _nav_ci_swap_cc(_NAV_CI_T*                                 pt_this);

static INT32 _nav_ci_cc_type_classify(const SM_CC_FILTER_T*             pt_filter,
                                      NAV_CI_CC_TYPE_T*                 pe_cc_type,
                                      UINT8*                            pui1_cc_id);

static VOID _nav_ci_reset_delay_timer(_NAV_CI_T*                        pt_this,
                                      BOOL                              b_stop_only);

static VOID _nav_ci_delay_cb(HANDLE_T                                   h_timer,
                             VOID*                                      pv_tag);

static VOID _nav_ci_delay_msg_hdlr(VOID*                                pv_unused,
                                   VOID*                                pv_unused2,
                                   VOID*                                pv_unused3);

static VOID _nav_ci_cfg_change_cb(UINT16                                ui2_nfy_id,
                                  VOID*                                 pv_tag,
                                  UINT16                                ui2_id);

static VOID _nav_ci_cfg_change_msg_hdlr(VOID*                           pv_ui2_id,
                                        VOID*                           pv_unused1,
                                        VOID*                           pv_unused2);

static VOID _nav_ci_reset_update_timer(_NAV_CI_T*                       pt_this,
                                       _NAV_CI_INFO_TO_UI_T             e_to_ui,
                                       BOOL                             b_stop_only);

static VOID _nav_ci_delay_update_cb(HANDLE_T                            h_timer,
                                    VOID*                               pv_tag);

static VOID _nav_ci_delay_update(VOID*                                  pv_e_to_ui,
                                 VOID*                                  pv_unused2,
                                 VOID*                                  pv_unused3);

static VOID _nav_ci_delay_update(VOID*                                  pv_e_to_ui,
                                 VOID*                                  pv_unused2,
                                 VOID*                                  pv_unused3);

static VOID _nav_ci_auto_cc_to_normal_cc(const SM_CC_FILTER_T*         pt_auto_filter,
                                         SM_CC_FILTER_T*               pt_normal_filter);

static VOID _nav_ci_set_default_cc_filter(_NAV_CI_T*                    pt_this,
                                          TV_WIN_ID_T                   e_grp);

static INT32 _nav_ci_get_using_cc_scdb(_NAV_CI_T*                       pt_this,
                                       SM_CC_FILTER_T*                  pt_filter,
                                       SCDB_REC_T*                      pt_scdb_rec);

static VOID _nav_ci_next_cc(_NAV_CI_T*                                  pt_this,
                            _NAV_CI_INFO_TO_UI_T*                       pe_to_ui,
                            BOOL*                                       pb_is_xng);

static VOID _nav_ci_delay_first_svc_xng(
                                       VOID*                            pv_unused1,
                                       VOID*                            pv_unused2,
                                       VOID*                            pv_unused3);

static BOOL _nav_ci_is_same_cc_filter(SM_CC_FILTER_T*                   pt_filter_1,
                                      SM_CC_FILTER_T*                   pt_filter_2);

static INT32 _nav_ci_reset_loop(
    TV_WIN_ID_T                 e_win_id);


#ifdef APP_IPCC_SUPPORT

static INT32 _nav_ci_update_ipcc_idx(VOID);

extern INT32 acfg_get_svctx(
    const CHAR*     s_disp_name,
    HANDLE_T*       ph_svctx);
#endif

#ifdef CLI_SUPPORT
extern INT32 cc_info_cli_init();
#endif

extern VOID nav_banner_set_cc_state(BOOL b_on,BOOL visiable);

VOID nav_ci_enable_log(BOOL b_on)
{
    b_cc_info_debug = b_on;
}


static VOID _send_event_notify(VOID)
{
    UINT8 ui1_cfg;

    a_cfg_get_cc_enabled(&ui1_cfg);

    if (APP_CFG_CC_ON == ui1_cfg)
    {
       rest_event_notify("tv_settings/closed_captions/closed_captions_enabled", 1, "");;
    }
    else
    {
        rest_event_notify("tv_settings/closed_captions/closed_captions_enabled", 0, "");;
    }

	DBG_LOG_PRINT(("Pass CC key to rest ap.\n"));
 //   rest_event_notify("key_command", BTN_CC, "");

}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_cc_info_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_cc_info_register(
    const NAV_CI_VIEW_HANDLER_T*    pt_view_handler)
{
    _NAV_CI_T*                      pt_this = &t_g_cc_info;
    NAV_COMP_T                      t_comp;
    INT32                           i4_ret;

    /*set view handler*/
    if(pt_view_handler)
    {
        pt_this->t_view_handler = *pt_view_handler;
    }
    else
    {
        i4_ret = nav_civ_get_default_handler(&pt_this->t_view_handler);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to get default view handler. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }
    }

    if(FALSE == NAV_CI_IS_LEGAL_VIEW_HANDLER(&pt_this->t_view_handler))
    {
        DBG_ERROR((_ERROR_HEADER"CC-INFO view handler is illegal.\r\n"));
        return NAVR_FAIL;
    }

    c_memset(&t_comp,0,sizeof(NAV_COMP_T));

    /*register CC-Info UI component*/
    t_comp.pf_init           = _nav_ci_init;
    t_comp.pf_deinit         = _nav_ci_deinit;
    t_comp.pf_is_key_handler = _nav_ci_is_key_handler;
    t_comp.pf_activate       = _nav_ci_activate;
    t_comp.pf_inactivate     = NULL;
    t_comp.pf_hide           = _nav_ci_hide;
    t_comp.pf_handle_msg     = _nav_ci_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_CC_SEL, &t_comp, COMP_EXC_SET_CC_SEL);
    if(i4_ret != NAVR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"nav_register_comp(NAV_COMP_ID_CC_SEL) failed\r\n"));
        return i4_ret;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
 * Name
 *      nav_ci_switch_cc
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
INT32 nav_ci_switch_cc(
    NAV_CI_SWITCH_METHOD_T  e_method)
{
    BOOL                    b_save;

    NAV_CI_GET_SAVE_CFG(b_save);

    return _nav_ci_change_cc(&t_g_cc_info, e_method, _NAV_CI_SEM_NORMAL, b_save, _NAV_CI_INFO_TUI_EMPTY);
}

/*------------------------------------------------------------------------------
 * Name
 *      nav_ci_set_exec_cond
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
INT32 nav_ci_set_exec_cond(
    NAV_CI_EXEC_COND_T     e_cond)
{
    _NAV_CI_T*              pt_this = &t_g_cc_info;
    NAV_CI_SWITCH_METHOD_T  e_method;
    INT32                   i4_ret;

    nav_ci_set_ipcc_visible((NAV_CI_EC_ON == e_cond || NAV_CI_EC_MUTE_ON == e_cond) ? TRUE : FALSE);

    if(e_cond == pt_this->e_exec_cond)
    {
        CC_LOG((" is the same e_cond\n "));
        return NAVR_OK;
    }

    pt_this->e_exec_cond = e_cond;

    /*save setting to config*/
    _NAV_CI_SAV_ONOFF_CFG(e_cond, i4_ret);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): _NAV_CI_SAV_ONOFF_CFG(%d) failed, ret = %d\r\n", __FUNCTION__, e_cond, i4_ret));
    }

    e_method = (NAV_CI_EC_ON == e_cond || NAV_CI_EC_MUTE_ON == e_cond) ? NAV_CI_SM_DEFAULT : NAV_CI_SM_STOP;
    return _nav_ci_change_cc(pt_this, e_method, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
}

/*------------------------------------------------------------------------------
 * Name
 *      nav_ci_get_exec_cond
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
INT32 nav_ci_get_exec_cond(
    NAV_CI_EXEC_COND_T*    pe_cond)
{
    _NAV_CI_T*             pt_this = &t_g_cc_info;

    if(NULL == pe_cond)
    {
        return NAVR_INV_ARG;
    }

    *pe_cond = pt_this->e_exec_cond;
    return NAVR_OK;
}

#if (defined(APP_ATSC_SUPPORT))
INT32 nav_ci_get_active_cc(SI_CC_RENDERING_T* pe_rendering, CHAR* ps_lang)
{
    _NAV_CI_T*             pt_this = &t_g_cc_info;
    SM_CC_FILTER_T         t_auto_cc_filter;
    SM_CC_FILTER_T*        pt_cc_filter = NULL;
    SCDB_REC_T             t_scdb_rec;
    NAV_CI_CC_TYPE_T       e_cc_type;
    SIZE_T                 z_size;
    UINT8                  ui1_cc_id;
    INT32                  i4_ret = NAVR_OK;

    if(SM_CC_TYPE_AUTO_SEL == pt_this->at_grp[pt_this->e_focus_grp].t_cc.e_cc_type)
    {
        if(_NAV_CI_IS_AUTO_WITH_TOGGLE())
        {
            _nav_ci_auto_cc_to_normal_cc(&pt_this->at_grp[pt_this->e_focus_grp].t_cc, &t_auto_cc_filter);
            pt_cc_filter = &t_auto_cc_filter;
        }
        else
        {
            z_size = sizeof(SM_CC_FILTER_T);

            i4_ret = c_svctx_get_stream_attr(pt_this->h_focus_svctx,
                                             ST_CLOSED_CAPTION,
                                             SM_CCH_GET_TYPE_SELECTED_CC_FLTR,
                                             &t_auto_cc_filter,
                                             &z_size);

            if(SVCTXR_OK == i4_ret)
            {
                pt_cc_filter = &t_auto_cc_filter;
                i4_ret = NAVR_OK;
            }
            else
            {
                DBG_ERROR(("[%s](%d) get select cc filter fail, error value: %d\n", __FUNCTION__, __LINE__, i4_ret));
                return NAVR_FAIL;
            }
        }
    }
    else
    {
        pt_cc_filter = &pt_this->at_grp[pt_this->e_focus_grp].t_cc;
    }

    if(i4_ret == NAVR_OK)
    {
        i4_ret = _nav_ci_cc_type_classify(pt_cc_filter,
                                          &e_cc_type,
                                          &ui1_cc_id);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR(("[%s](%d) get cc type fail, error value: %d\n", __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }

        i4_ret = _nav_ci_get_using_cc_scdb(pt_this, pt_cc_filter, &t_scdb_rec);
        if(NAVR_OK != i4_ret)
        {
           DBG_ERROR(("[%s](%d) get cc scdb fail, error value: %d\n", __FUNCTION__, __LINE__, i4_ret));
           return NAVR_FAIL;
        }

        c_strncpy(ps_lang, t_scdb_rec.u.t_atsc_cc.s_lang, ISO_639_LANG_LEN);

        if(e_cc_type == NAV_CI_CC_TYPE_INIT_VALUE)
        {
            *pe_rendering = SI_CC_RENDERING_TYPE_UNKNOWN;
        }
        else if(e_cc_type == NAV_CI_CC_TYPE_NTSC_CC)
        {
            *pe_rendering = (SI_CC_RENDERING_T)(ui1_cc_id + SI_CC_RENDERING_TYPE_CC1 - 1);
        }
        else if(e_cc_type == NAV_CI_CC_TYPE_NTSC_TEXT)
        {
            *pe_rendering =(SI_CC_RENDERING_T)( ui1_cc_id + SI_CC_RENDERING_TYPE_TEXT1 -1);
        }
        else if(e_cc_type == NAV_CI_CC_TYPE_DIG)
        {
             *pe_rendering = (SI_CC_RENDERING_T)(ui1_cc_id + SI_CC_RENDERING_TYPE_SERVICE1 - 1);
        }
        else
        {
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}

#endif

INT32 nav_ci_set_visible(BOOL b_visible)
{
    _NAV_CI_T*  pt_this = &t_g_cc_info;
    INT32       i4_ret = NAVR_OK;

    i4_ret = nav_get_svctx_handle(TV_WIN_ID_MAIN, &pt_this->h_focus_svctx);

    if(i4_ret != 0)
    {
        DBG_ERROR((" -- Error - Function : %s, Line : %d, i4_ret = %d-- \n",__FUNCTION__,__LINE__,i4_ret));
        return -1;
    }
    c_sm_cc_hdlr_set_global_visible(b_visible);
    CC_LOG(("SM_CCH_SET_TYPE_CC_GLOBAL_VISIBLE %s \n",b_visible == TRUE ? "YES":"NO"));
    if(SVCTXR_OK != c_svctx_set_stream_attr(pt_this->h_focus_svctx,
                                            ST_CLOSED_CAPTION,
                                            SM_CCH_SET_TYPE_CC_GLOBAL_VISIBLE,
                                            (VOID*)(UINT32)(b_visible),
                                            sizeof(BOOL)))
    {
        i4_ret = NAVR_FAIL;
    }
    a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);
    a_cfg_update_dcs();
    return i4_ret;
}

/*------------------------------------------------------------------------------
 * Name
 *      nav_ci_set_ipcc_visible
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
INT32 nav_ci_set_ipcc_visible(BOOL b_visible)
{
    INT32 i4_ret = NAVR_OK;

    DBG_INFO(("<NAV> %s enter ============\n", __FUNCTION__));

#ifdef APP_IPCC_SUPPORT
    _NAV_CI_T*              pt_this = &t_g_cc_info;
    HANDLE_T                h_focus_svctx = NULL_HANDLE;
    MM_SVC_SBTL_SHOW_HIDE_T t_ipcc_show;

    t_ipcc_show.b_sbtl_show = b_visible;

    i4_ret = nav_get_svctx_handle(TV_WIN_ID_MAIN, &h_focus_svctx);
    NAV_CHK_FAIL(i4_ret);

    i4_ret = c_svctx_set(h_focus_svctx,
                SVCTX_MM_SBTL_SET_TYPE_SHOW_HIDE,
                (VOID *)&t_ipcc_show,
                sizeof(MM_SVC_SBTL_SHOW_HIDE_T));

    pt_this->b_ipcc_visible = b_visible;

    DBG_INFO(("<NAV> %s %s, return %d\n", __FUNCTION__,
                                        b_visible == TRUE ? "TRUE" : "FALSE",
                                        i4_ret));
#endif

    return i4_ret;
}

/*------------------------------------------------------------------------------
 * Name
 *      nav_ci_get_ipcc_visible
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
BOOL nav_ci_get_ipcc_visible(VOID)
{
#ifdef APP_IPCC_SUPPORT
    return t_g_cc_info.b_ipcc_visible;
#else
    return FALSE;
#endif
}

static BOOL _need_to_change_cc(VOID)
{
    ISL_REC_T      t_isl_rec   = {0};
    TV_WIN_ID_T    e_tv_win_id = TV_WIN_ID_MAIN;

    /*get current source*/
    nav_get_focus_id(&e_tv_win_id);
    nav_get_isl_rec(e_tv_win_id, &t_isl_rec);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        return TRUE;
    }

    return FALSE;
}

static VOID _iom_nfy_fct (VOID*             pv_nfy_tag,
                          IOM_NFY_COND_T    e_nfy_cond,
                          UINT32            ui4_evt_code,
                          UINT32            ui4_data)
{
    if(e_nfy_cond == IOM_NFY_COND_BTN_DOWN)
    {
        switch (IOM_GET_EVT_GRP_ID(ui4_evt_code))
        {
            case BTN_CC:
            {
                menu_blank_oled_scrn_timer_refresh();
				if (menu_custom_is_blank_screen())
				{
                    menu_custom_unblank_screen(BTN_CC);
					return;
				}
                /*the case need to change cc*/
                if ((nav_is_active() == FALSE) && (_need_to_change_cc()))
                {
                    nav_rcu_key_handler(BTN_CC);
                }
                break;
            }
            default:
                break;
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ci_init(
    NAV_CONTEXT_T*        pt_ctx)
{
    _NAV_CI_T*            pt_this = &t_g_cc_info;
    HANDLE_T              h_svctx;
    INT32                 i4_ret, i;

    NAV_ASSERT(NULL_HANDLE == pt_this->h_focus_svctx);

    do
    {
        /*timer for delay selection*/
        i4_ret = c_timer_create(&pt_this->h_delay_timer);
        if(OSR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to create timer for cc delay selection, ret = %d\r\n", i4_ret));
            pt_this->h_delay_timer = NULL_HANDLE;
            i4_ret = NAVR_FAIL;
            break;
        }

        /*timer for update*/
        i4_ret = c_timer_create(&pt_this->h_update_timer);
        if(OSR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to create timer for cc delay update, ret = %d\r\n", i4_ret));
            pt_this->h_update_timer = NULL_HANDLE;
            i4_ret = NAVR_FAIL;
            break;
        }

#ifdef APP_NAV_MOVE_CC_TO_SECOND_PLANE
        i4_ret = c_timer_create(&pt_this->h_excluse_timer);
        if(OSR_OK != i4_ret)
        {
            pt_this->h_excluse_timer = NULL_HANDLE;
            i4_ret = NAVR_FAIL;
            break;
        }

#endif
        pt_this->t_last_notify.ui1_gui_lang_id = _NAV_CI_GUI_LANG_NULL;
        pt_this->e_focus_grp = pt_ctx->t_svc_res.e_focus_tv_win_id;
        pt_this->h_cc_plane = pt_ctx->t_gui_res.h_cc_plane;
        pt_this->ui2_cc_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
#ifdef APP_IPCC_SUPPORT
        pt_this->b_ipcc_visible = TRUE;
#endif
        /*init exec condition*/
        _nav_ci_sync_exec_cond(pt_this);

        /*if no default focus*/
        if(TV_WIN_ID_LAST_VALID_ENTRY == pt_this->e_focus_grp)
        {
            pt_this->e_focus_grp = TV_WIN_ID_MAIN;
        }

        /*svctx handle*/
        i4_ret = nav_get_svctx_handle(pt_this->e_focus_grp, &pt_this->h_focus_svctx);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to get focus svctx handler (focus=%d), ret = %d\r\n", pt_this->e_focus_grp, i4_ret));
            pt_this->h_focus_svctx = NULL_HANDLE;
            i4_ret = NAVR_FAIL;
            break;
        }

        /*init config*/
        i4_ret = _nav_ci_cfg_init(pt_this);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to register config notification for CC-Info! ret=%d\r\n", i4_ret));
        }

        /*create cc info view*/
        i4_ret = pt_this->t_view_handler.pf_init(pt_ctx->t_gui_res.h_canvas,
                                                 pt_ctx->t_gui_res.i4_x_offset,
                                                 pt_ctx->t_gui_res.i4_y_offset,
                                                 pt_ctx->t_gui_res.e_color_type,
                                                 &pt_this->pv_view);
        if(NAVR_OK != i4_ret)
        {
            pt_this->pv_view = NULL;
            break;
        }

        /* set default c stream filter */
        for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
        {
            i4_ret = nav_get_svctx_handle((TV_WIN_ID_T)i, &h_svctx);
            if(NAVR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"Fail to get svctx handler (grp=%d), ret = %d\r\n", i, i4_ret));
                i4_ret = NAVR_FAIL;
                break;
            }

            i4_ret = c_svctx_set_default_strm_filter(h_svctx,
                                                     ST_CLOSED_CAPTION,
                                                     _nav_ci_default_cc_strm_comp_filter,
                                                     NULL);
            if(SVCTXR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"c_svctx_set_default_strm_filter(CC) failed (grp=%d)! ret=%d\r\n", i4_ret, i));
                i4_ret = NAVR_FAIL;
                break;
            }
        }
        if(NAVR_OK != i4_ret)
        {
            break;
        }

        /*get default cc filter*/
        for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
        {
            _nav_ci_set_default_cc_filter(pt_this, (TV_WIN_ID_T)i);
        }

#if 0
#ifdef APP_NAV_MOVE_CC_TO_SECOND_PLANE
        i4_ret = c_wgl_set_canvas_callback(pt_ctx->t_gui_res.h_canvas,
                        _wgl_canvas_callback_fct,
                        TRUE);
        if(WGLR_OK != i4_ret)
        {
            break;
        }
        CC_LOG(("[NAV][CC][%s %d] cc plane is 0x%x t_gui_res.h_canvas = 0x%x\n",__FUNCTION__,__LINE__,pt_this->h_cc_plane,pt_ctx->t_gui_res.h_canvas));
#endif
#endif

#ifdef APP_IPCC_SUPPORT
        #define FIRST_KEY_REP_DELAY                 (400)
        #define NEXT_KEY_REP_DELAY                  (100)

        IRRC_SETTING_T          t_irrc_setting;

        /* Open IOM handler. */
        c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));

        t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_TO_MASK(KEY_GROUP_PRG_CTRL);
        t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = (UINT16)(FIRST_KEY_REP_DELAY / 10); /* 10 ms per unit */
        t_irrc_setting.t_rpt_evt_itvl.ui2_other = (UINT16)(NEXT_KEY_REP_DELAY / 10);  /* 10 ms per unit */

        NAV_LOG_ON_FAIL(c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                                    IOM_DEV_ID_ANY,
                                    NULL,
                                    (VOID*) & t_irrc_setting,
                                    NULL,
                                    _iom_nfy_fct,
                                    & pt_this->h_iom));

#endif
#ifdef CLI_SUPPORT
        cc_info_cli_init();
#endif
        return NAVR_OK;

    } while(0);

    _nav_ci_deinit();
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ci_deinit(VOID)
{
    _NAV_CI_T               t_empty_cc_info = {{0}};
    _NAV_CI_T*              pt_this = &t_g_cc_info;
    INT32                   i4_ret;

    /*free delay timer*/
    if(TRUE == c_handle_valid(pt_this->h_delay_timer))
    {
        c_timer_delete(pt_this->h_delay_timer);
    }

    /*free update timer*/
    if(TRUE == c_handle_valid(pt_this->h_update_timer))
    {
        c_timer_delete(pt_this->h_update_timer);
    }

    /*free update timer*/
    if(TRUE == c_handle_valid(pt_this->h_excluse_timer))
    {
        c_timer_delete(pt_this->h_excluse_timer);
    }

    /*unregister config notification*/
    _nav_ci_cfg_deinit(pt_this);

    /*deinit cc-info-view*/
    if(pt_this->t_view_handler.pf_deinit)
    {
        i4_ret = pt_this->t_view_handler.pf_deinit(pt_this->pv_view);
    }
    else
    {
        i4_ret = NAVR_OK;
    }

    *pt_this = t_empty_cc_info;
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_ci_is_key_handler(
    NAV_CONTEXT_T*                 pt_ctx,
    UINT32                         ui4_key_code)
{
    _NAV_CI_T*     pt_this = &t_g_cc_info;

    return pt_this->t_view_handler.pf_is_key_handler(pt_this->pv_view, ui4_key_code);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ci_activate(
    NAV_CONTEXT_T*            pt_ctx,
    UINT32                    ui4_key_code)
{
    _NAV_CI_T*                pt_this = &t_g_cc_info;

    if(nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_CC_SEL_UI) == TRUE)
    {
        return NAVR_NO_ACTION;
    }

    /*handle key*/
    return pt_this->t_view_handler.pf_key_handler(pt_this->pv_view, ui4_key_code);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ci_hide(VOID)
{
    _NAV_CI_T* pt_this = &t_g_cc_info;

    pt_this->t_view_handler.pf_hide(pt_this->pv_view);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ci_handle_msg(
    NAV_CONTEXT_T*              pt_ctx,
    NAV_UI_MSG_T*               pt_ui_msg,
    VOID*                       pv_arg1)
{
    _NAV_CI_T*                  pt_this = &t_g_cc_info;
    _NAV_CI_INFO_TO_UI_T        e_to_ui = _NAV_CI_INFO_TUI_EMPTY;
    INT32                       i4_ret, i;

    if(pt_ctx->t_svc_res.e_focus_tv_win_id != pt_ui_msg->e_tv_win_id)
    {
        switch(pt_ui_msg->e_id)
        {
            case NAV_UI_MSG_APP_PAUSING:
            case NAV_UI_MSG_APP_RESUMED:
            case NAV_UI_MSG_POWER_OFF:
            case NAV_UI_MSG_POWER_ON:
            case NAV_UI_MSG_FOCUS_CHANGED:
            case NAV_UI_MSG_BEFORE_TV_MODE_CHANGE:
            case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
            case NAV_UI_MSG_STATE_ITEM_CHANGED:
            case NAV_UI_MSG_BEFORE_SVCS_SWAP:
            case NAV_UI_MSG_MUTE_STATUS_CHANGED:
            case NAV_UI_MSG_AFTER_SVCS_SWAP:
            case NAV_UI_MSG_AS_APP_PAUSED:
                break;

            default:
                return NAVR_NO_ACTION;
        }
    }

    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_POWER_ON:
            {
                pt_this->b_first_svc_xng = TRUE;
            }
            break;
        case NAV_UI_MSG_APP_INITED:
            {
            #ifdef APP_IPCC_SUPPORT
                a_cfg_custom_set_ipcc_idx(NULL);
                nav_ci_set_ipcc_visible(TRUE);
            #endif
                break;
            }
        case NAV_UI_MSG_BEFORE_SVC_CHANGE:
            {
                NAV_XNG_SRC_TRGT_T*  pt_xng_info = (NAV_XNG_SRC_TRGT_T*)pv_arg1;
                NAV_ASSERT(pt_xng_info);
                CC_LOG((" NAV_UI_MSG_BEFORE_SVC_CHANGE \n"));
                /*reset current status*/
                _nav_ci_reset_delay_timer(pt_this, STOP_TIMER);
                _nav_ci_reset_loop(pt_this->e_focus_grp);

                pt_this->e_status_flag &= (~_NAV_CI_STATUS_FLAG_INFO_STABLE);

                if(pt_this->b_first_svc_xng)
                {
                    pt_this->b_first_svc_xng = FALSE;

                    nav_request_context_switch(_nav_ci_delay_first_svc_xng, NULL, NULL, NULL);
                }
                else
                {
                    if(pt_this->b_channel_dirty)
                    {
                        pt_xng_info = NULL;
                        pt_this->b_channel_dirty = FALSE;
                    }

                    /*set cc related setting*/
                    if(FALSE == nav_is_pop_pip_swapping())
                    {
                        i4_ret = _nav_ci_set_cc_filter(pt_this, pt_xng_info);
                        if(NAVR_OK != i4_ret)
                        {
                            DBG_ERROR((_ERROR_HEADER"Fail to set cc-filter, ret=%d\r\n", i4_ret));
                            return i4_ret;
                        }
                    }

                    e_to_ui = (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY);

                    if(FALSE == nav_is_resumed_from_app_switch())
                    {
                        e_to_ui = _NAV_CI_INFO_TUI_DSCRPTR_NOT_READY;
                    }
                    else
                    {
                        if (pt_this->e_focus_grp >= TV_WIN_ID_LAST_VALID_ENTRY)
                        {
                            DBG_ERROR((_ERROR_HEADER"Focus grp exceed the size, grp_id=%d\r\n", pt_this->e_focus_grp));
                            return NAVR_NOT_ALLOW;
                        }

                        /* Fix: [DTV00126780] From the MMP, the cc_state will keep "CC_STATE_WITHOUT_CC", and it won't goto set filter dafault */
                        if ((_NAV_CC_STATE_IS_NOT_DEFAULT(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state)) &&
                            (_NAV_CI_IS_IGNORE_FILTER(pt_this->at_grp[pt_this->e_focus_grp].t_cc))           &&
                            (pt_this->at_grp[pt_this->e_focus_grp].t_cc.e_cc_type == pt_this->at_grp[pt_this->e_focus_grp].t_user_cc.e_cc_type))
                        {
                            /*reset flag*/
                            _NAV_CC_STATE_SET_UNKNOWN_DEFAULT(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state);

                            i4_ret = _nav_ci_set_cc_filter(pt_this, pt_xng_info);
                            if(NAVR_OK != i4_ret)
                            {
                                DBG_ERROR((_ERROR_HEADER"Fail to set cc-filter, ret=%d\r\n", i4_ret));
                                return i4_ret;
                            }
                        }

                    }
                }
            }
            break;

        case NAV_UI_MSG_EMPTY_SVL:
        case NAV_UI_MSG_LOCKED_INP:
        case NAV_UI_MSG_LOCKED_CH:
        case NAV_UI_MSG_NO_SIGNAL:
            {
                pt_this->e_status_flag |= _NAV_CI_STATUS_FLAG_INFO_STABLE;

                e_to_ui = (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_INFO_TUI_DSCRPTR_NOT_READY);
            }
            break;

        case NAV_UI_MSG_UNLOCKED:
            {
                /*start a timer for update*/
                _nav_ci_reset_update_timer(pt_this, _NAV_CI_INFO_DELAY_UPDATE_MASK, RESET_TIMER);
            }
            break;

        case NAV_UI_MSG_APP_PAUSING:
            {
            CHAR s_app_name[APP_NAME_MAX_LEN + 1] = {0};

            a_am_get_next_active_app(s_app_name);
            CC_LOG((" NAV_UI_MSG_APP_PAUSING next active app is %s\n",s_app_name));
            if(c_strncmp(s_app_name,"menu",strlen("menu")) != 0)
            {
                _nav_ci_change_cc(pt_this, NAV_CI_SM_PAUSE, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
                _nav_ci_reset_update_timer(pt_this, _NAV_CI_INFO_TUI_EMPTY, STOP_TIMER);
                pt_this->e_status_flag &= ~(_NAV_CI_STATUS_FLAG_ACTIVE);
            }
        }
            break;

        case NAV_UI_MSG_APP_RESUMED:
            {
                pt_this->e_status_flag |= _NAV_CI_STATUS_FLAG_ACTIVE;               /*turn on active flag*/
            }
            break;

        case NAV_UI_MSG_AFTER_SVC_CHANGE:
                pt_this->e_status_flag |= _NAV_CI_STATUS_FLAG_INFO_STABLE;          /*turn on info stable flag*/
                /*no break here*/
        case NAV_UI_MSG_SCDB_UPDATE:
            {
                CC_LOG((" NAV_UI_MSG_SCDB_UPDATE \n"));
                /*cc info*/
                _nav_ci_reset_loop(pt_this->e_focus_grp);
                cc_loop_update(pt_this->h_focus_svctx);

                e_to_ui = (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_CHECK_DESCRIPTOR);
            }
            break;

        case NAV_UI_MSG_HIDDEN_CH:
        case NAV_UI_MSG_AV_STATUS_NOTIFY:
            {
                CC_LOG((" NAV_UI_MSG_AV_STATUS_NOTIFY or  NAV_UI_MSG_HIDDEN_CH\n"));
                if(LOCKED_STATUS_NONE == nav_get_locked_status(pt_this->e_focus_grp))
                {
                    switch(nav_get_av_status(pt_this->e_focus_grp))
                    {
                    case NAV_AV_STATUS_AUDIO_ONLY:
                    case NAV_AV_STATUS_NO_AUDIO_VIDEO:
                        e_to_ui = (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_CHECK_DESCRIPTOR);
                        break;

                    case NAV_AV_STATUS_VIDEO_ONLY:
                    case NAV_AV_STATUS_AUDIO_VIDEO:
                        e_to_ui = (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_CHECK_DESCRIPTOR);
                        break;

                    default:
                        break;
                    }
                }
            }
            break;

        case NAV_UI_MSG_AFTER_FREEZE_MODE_CHANGE:
            {
                NAV_UI_MSG_FREEZE_PARAM_T* pt_param = (NAV_UI_MSG_FREEZE_PARAM_T*)pv_arg1;
                CC_LOG((" NAV_UI_MSG_AFTER_FREEZE_MODE_CHANGE \n"));
                if(pt_this->e_focus_grp != pt_param->e_win_id)
                {
                    break; /*do nothing*/
                }
                else
                {
                    _nav_ci_change_cc(pt_this,
                                      (pt_param->b_to_freeze) ? NAV_CI_SM_PAUSE : NAV_CI_SM_USER_SETTING,
                                      _NAV_CI_SEM_NORMAL,
                                      FALSE,
                                      _NAV_CI_INFO_TUI_EMPTY);
                }
            }
            break;

        case NAV_UI_MSG_LOCKED_PROG:
            pt_this->e_status_flag |= _NAV_CI_STATUS_FLAG_INFO_STABLE;
            /*no break here*/
        case NAV_UI_MSG_AS_APP_PAUSED:
            {
                CC_LOG((" NAV_UI_MSG_AS_APP_PAUSED as  %d \n",pt_ui_msg->e_id_as_paused));
                if(NAV_UI_MSG_LOCKED_PROG == pt_ui_msg->e_id_as_paused || NAV_UI_MSG_LOCKED_PROG == pt_ui_msg->e_id)
                {
                    CC_LOG((" NAV_UI_MSG_AS_APP_PAUSED  NAV_UI_MSG_LOCKED_PROG\n"));
                    _nav_ci_change_cc(pt_this,
                                      NAV_CI_SM_PAUSE,
                                      _NAV_CI_SEM_NORMAL,
                                      FALSE,
                                      (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_INFO_TUI_DSCRPTR_NOT_READY));
                    break;
                }
                else if(NAV_UI_MSG_BEFORE_SVC_CHANGE == pt_ui_msg->e_id_as_paused)
                {
                    CC_LOG((" NAV_UI_MSG_AS_APP_PAUSED  NAV_UI_MSG_BEFORE_SVC_CHANGE\n"));
                    pt_this->b_channel_dirty = TRUE;

                    /*reset current status*/
                    _nav_ci_reset_loop(pt_this->e_focus_grp);
                    e_to_ui = _NAV_CI_INFO_TUI_DSCRPTR_NOT_READY;
                    break;
                }
                else if(NAV_UI_MSG_FOCUS_CHANGED == pt_ui_msg->e_id_as_paused)
                {
                   CC_LOG((" NAV_UI_MSG_AS_APP_PAUSED  NAV_UI_MSG_FOCUS_CHANGED\n"));
                    _nav_ci_focus_xng_nfy_handler(pt_this, pt_ctx->t_svc_res.e_focus_tv_win_id);
                    break;
                }
                else if(NAV_UI_MSG_STREAM_NOTIFY != pt_ui_msg->e_id_as_paused)
                {
                    break;
                }
            }
            /*no break here*/
        case NAV_UI_MSG_STREAM_NOTIFY:
            {
                /* if get stream notify, we change the cc state in visible according to yahoo state */
                HANDLE_T    h_focus_svctx = NULL_HANDLE;
#ifndef APP_NAV_MOVE_CC_TO_SECOND_PLANE
                SIZE_T      z_size = sizeof(BOOL);
#endif
                CC_LOG((" NAV_UI_MSG_STREAM_NOTIFY \n"));
                if (NULL_HANDLE == pt_this->h_focus_svctx)
                {
                    i4_ret = nav_get_svctx_handle(TV_WIN_ID_MAIN, &h_focus_svctx);
                    if(NAVR_OK != i4_ret)
                    {
                        DBG_ERROR((_ERROR_HEADER"Function : %s, Line : %d, i4_ret = %d-- \n",__FUNCTION__,__LINE__,i4_ret));
                    }
                }
                else
                {
                    h_focus_svctx = pt_this->h_focus_svctx;
                }

#ifndef APP_NAV_MOVE_CC_TO_SECOND_PLANE
                if (a_cfg_get_app_status () != APP_CFG_APP_STATUS_YH_DOCK &&
                    a_cfg_get_app_status () != APP_CFG_APP_STATUS_YH_SIDEBAR)
                {
                    CC_LOG(("SM_CCH_SET_TYPE_CC_GLOBAL_VISIBLE TRUE \n"));
                    i4_ret = c_svctx_set_stream_attr(h_focus_svctx,
                                                     ST_CLOSED_CAPTION,
                                                     SM_CCH_SET_TYPE_CC_GLOBAL_VISIBLE,
                                                     (VOID*)(UINT32)TRUE,
                                                     z_size);
                    if(SVCTXR_OK != i4_ret)
                    {
                        DBG_ERROR((_ERROR_HEADER"Function : %s, Line : %d, i4_ret = %d-- \n",__FUNCTION__,__LINE__,i4_ret));
                    }
                }
                else if (a_cfg_get_app_status () == APP_CFG_APP_STATUS_YH_DOCK ||
                         a_cfg_get_app_status () == APP_CFG_APP_STATUS_YH_SIDEBAR)
                {
                    CC_LOG((" SM_CCH_SET_TYPE_CC_GLOBAL_VISIBLE FALSE \n"));
                    i4_ret = c_svctx_set_stream_attr(h_focus_svctx,
                                                     ST_CLOSED_CAPTION,
                                                     SM_CCH_SET_TYPE_CC_GLOBAL_VISIBLE,
                                                     (VOID*)(UINT32)FALSE,
                                                     z_size);
                    if(SVCTXR_OK != i4_ret)
                    {
                        DBG_ERROR((_ERROR_HEADER"Function : %s, Line : %d, i4_ret = %d-- \n",__FUNCTION__,__LINE__,i4_ret));
                    }
                }
#endif
                NAV_STREAM_NOTIFY_DATA_T*   pt_nfy_data = (NAV_STREAM_NOTIFY_DATA_T*)pv_arg1;
                CC_LOG((" e_strm_type = %s e_type = %s\n ",
                pt_nfy_data->e_strm_type == ST_CLOSED_CAPTION ? "ST_CLOSED_CAPTION":
                pt_nfy_data->e_strm_type == ST_VIDEO ? "ST_VIDEO":"other stream type",
                pt_nfy_data->e_type == NAV_SNT_STREAM_STARTED ? "NAV_SNT_STREAM_STARTED":
                pt_nfy_data->e_type == NAV_SNT_STREAM_UPDATED ? "NAV_SNT_STREAM_UPDATED":
                pt_nfy_data->e_type == NAV_SNT_STREAM_STOPPED ? "NAV_SNT_STREAM_STOPPED":
                pt_nfy_data->e_type == NAV_SNT_STREAM_NOT_SUPPORT ? "NAV_SNT_STREAM_NOT_SUPPORT":"other e_type"));

                if(ST_CLOSED_CAPTION == pt_nfy_data->e_strm_type)
                {
                    _nav_ci_stream_nfy_handler(pt_this, pt_nfy_data->e_type, &e_to_ui);
                }
                else if(ST_VIDEO == pt_nfy_data->e_strm_type)
                {
                    if(NAV_SNT_STREAM_STARTED == pt_nfy_data->e_type)
                    {
//                       nav_ci_set_visible((NAV_CI_EC_ON == t_g_cc_info.e_exec_cond || NAV_CI_EC_MUTE_ON == t_g_cc_info.e_exec_cond) ? TRUE : FALSE);
					   _nav_ci_sync_exec_cond(pt_this);
                       _nav_ci_change_cc(pt_this, NAV_CI_SM_USER_SETTING, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
                    }
                    else if (NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type)
                    {
                        //stop the delay timer
                        c_timer_stop(pt_this->h_delay_timer);
                        _nav_ci_change_cc(pt_this, NAV_CI_SM_USER_SETTING, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
                    }
                    else if(NAV_SNT_STREAM_STOPPED == pt_nfy_data->e_type ||
                            NAV_SNT_STREAM_NOT_SUPPORT == pt_nfy_data->e_type)
                    {
                        _nav_ci_change_cc(pt_this, NAV_CI_SM_FORCE_PAUSE, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
                    }
                }
            }
            break;

        case NAV_UI_MSG_FREQ_CHANGE:
            {
                CC_LOG((" NAV_UI_MSG_FREQ_CHANGE \n"));
                /*stop timer*/
                _nav_ci_reset_delay_timer(pt_this, STOP_TIMER);
            }
            break;

        case NAV_UI_MSG_POWER_OFF:
            {
                for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
                {
                    _NAV_CC_STATE_SET_UNKNOWN_DEFAULT(pt_this->at_grp[i].e_cc_state);
                }
            }
            break;

        case NAV_UI_MSG_STATE_ITEM_CHANGED:
            {
                e_to_ui = _NAV_CI_INFO_TUI_STATE_ITEM;
            }
            break;

        case NAV_UI_MSG_BEFORE_TV_MODE_CHANGE:
            {
                CC_LOG((" NAV_UI_MSG_BEFORE_TV_MODE_CHANGE \n"));
                _NAV_CI_TV_MODE_XNG_NFY_HANDLER(pt_this, (NAV_TV_MODE_XNG_INFO_T*)pv_arg1);
            }
            break;

        case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
            {
                CC_LOG(("NAV_UI_MSG_AFTER_TV_MODE_CHANGE \n"));
                /*don't have to do anything while mode changing.*/
                if(TV_MODE_TYPE_NORMAL == ((TV_MODE_T)(UINT32)pv_arg1))
                {
                    for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
                    {
                        if(TV_WIN_ID_MAIN == i) /*don't change main's setting*/
                        {
                            continue;
                        }

                        _NAV_CC_STATE_SET_UNKNOWN_DEFAULT(pt_this->at_grp[i].e_cc_state);
                    }
                }
            }
            break;

        case NAV_UI_MSG_FOCUS_CHANGED:
            {
                CC_LOG(("NAV_UI_MSG_FOCUS_CHANGED \n"));
                _nav_ci_focus_xng_nfy_handler(pt_this, pt_ctx->t_svc_res.e_focus_tv_win_id);

                e_to_ui = _NAV_CI_INFO_TUI_STATE_ITEM;
            }
            break;

        case NAV_UI_MSG_BEFORE_SVCS_SWAP:
            {
                _nav_ci_swap_cc(pt_this); /*no update ui*/

                /*empty UI*/
                e_to_ui |= (_NAV_CI_INFO_TUI_CC_NOT_READY | _NAV_CI_INFO_TUI_CC_LANG_NOT_READY | _NAV_CI_INFO_TUI_DSCRPTR_NOT_READY);
            }
            break;

        case NAV_UI_MSG_AFTER_SVCS_SWAP:
            {
                CC_LOG(("NAV_UI_MSG_AFTER_SVCS_SWAP \n"));
                /*refresh cc loop*/
                _nav_ci_reset_loop(pt_this->e_focus_grp);
                cc_loop_update(pt_this->h_focus_svctx);

                /*update ui. CR11892*/
                e_to_ui = (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_CHECK_DESCRIPTOR);
            }
            break;

        case NAV_UI_MSG_CC_AVIL_STATUS_CHANGED:
            {
                e_to_ui = _NAV_CI_CHECK_DESCRIPTOR;
            }
            break;

        case NAV_UI_MSG_EXISTED_CC_IND_CHG:
             {
                 e_to_ui = (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_INFO_TUI_DSCRPTR_QUERY);
             }
             break;

        case NAV_UI_MSG_MUTE_STATUS_CHANGED:
             {
                 CC_LOG((" NAV_UI_MSG_MUTE_STATUS_CHANGED \n"));
                 if(NAV_CI_EC_MUTE_ON == pt_this->e_exec_cond)
                 {
                     if((BOOL)(UINT32)pv_arg1)       /*MUTE*/
                     {
                         _nav_ci_change_cc(pt_this, NAV_CI_SM_DEFAULT, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
                     }
                     else
                     {
                         _nav_ci_change_cc(pt_this, NAV_CI_SM_PAUSE, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
                     }
                nav_banner_set_cc_state((BOOL)(UINT32)pv_arg1 == TRUE ? TRUE : FALSE ,TRUE);
                 }
             }
             break;

         default:
             break;
    }

    if(_NAV_CI_INFO_TUI_EMPTY != e_to_ui)
    {
        return _nav_ci_update_cc_info(pt_this, e_to_ui);
    }

        return NAVR_OK;
    }

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_cfg_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static INT32 _nav_ci_cfg_init(
    _NAV_CI_T*                pt_this)
{
    INT32                     i4_ret;

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_CC,
                              NULL,
                              _nav_ci_cfg_change_cb,
                              &pt_this->ui2_cc_cfg_nfy);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): a_cfg_notify_reg(%d) failed. i4_ret = %d.\r\n", __FUNCTION__, APP_CFG_GRPID_CC, i4_ret));

        pt_this->ui2_cc_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_cfg_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static VOID _nav_ci_cfg_deinit(
    _NAV_CI_T*                 pt_this)
{
    if(APP_CFG_NOTIFY_NULL_ID != pt_this->ui2_cc_cfg_nfy)
    {
        a_cfg_notify_unreg(pt_this->ui2_cc_cfg_nfy);
        pt_this->ui2_cc_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_stream_nfy_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static VOID _nav_ci_stream_nfy_handler(_NAV_CI_T*                     pt_this,
                                       NAV_STREAM_NOTIFY_TYPE_T       e_type,
                                       _NAV_CI_INFO_TO_UI_T*          pe_to_ui)
{
    INT32   i4_ret;

    CC_LOG(("%s .\n",
            e_type == NAV_SNT_STREAM_STOPPED ? "NAV_SNT_STREAM_STOPPED" :
            e_type == NAV_SNT_STREAM_STARTED ? "NAV_SNT_STREAM_STARTED" :
            e_type == NAV_SNT_STREAM_UPDATED ? "NAV_SNT_STREAM_UPDATED" :
            e_type == NAV_SNT_STREAM_NOT_FOUND ? "NAV_SNT_STREAM_NOT_FOUND" :
            e_type == NAV_SNT_PLAY_LOOP_CHANGED ? "NAV_SNT_PLAY_LOOP_CHANGED" :
            e_type == NAV_SNT_PLAY_NOT_ALLOWED ? "NAV_SNT_PLAY_NOT_ALLOWED" :
            e_type == NAV_SNT_PLAY_CHECK_ASKED ? "NAV_SNT_PLAY_CHECK_ASKED" :"Unknow"));
    switch(e_type)
    {
        case NAV_SNT_STREAM_STOPPED:
            {
                if(NAV_CC_STREAM_STATUS_CLOSED != pt_this->e_stream_status && FALSE == pt_this->b_is_select_req_queued)
                {
        			nav_enable_cc_plane(t_g_navigator.t_nav_ctx.t_gui_res.h_cc_plane,FALSE);
                    pt_this->e_stream_status = NAV_CC_STREAM_STATUS_CLOSED;

                    /*update cc info here*/
                    *pe_to_ui = (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY);
                }
                else
                {
                    /*update cc info here*/
                    *pe_to_ui = (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_INFO_TUI_DSCRPTR_QUERY);
                }

            DBG_INFO((_INFO_HEADER"%s(): CC stream closed.\n\r"));
            }
            break;

        case NAV_SNT_STREAM_STARTED:
            {
                pt_this->e_stream_status = NAV_CC_STREAM_STATUS_OPENED;
                i4_ret = _nav_ci_sync_crnt_filter(pt_this);
                if(NAVR_OK != i4_ret) /*fail to update CC filter*/
                {
                    pt_this->e_stream_status = NAV_CC_STREAM_STATUS_CLOSED;

                    /*reselect*/
                    _nav_ci_change_cc(pt_this, NAV_CI_SM_CURRENT, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
                }
                else
                {
                    /*update cc info here*/
                    *pe_to_ui = (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_CHECK_DESCRIPTOR);
        			nav_enable_cc_plane(t_g_navigator.t_nav_ctx.t_gui_res.h_cc_plane,TRUE);
                }
            }
            break;

        case NAV_SNT_STREAM_UPDATED:
            {
                *pe_to_ui = (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY);
            }
            break;

        case NAV_SNT_STREAM_NOT_FOUND:
            {
                /*Note: no update cc info here*/
                _nav_ci_change_cc(pt_this, NAV_CI_SM_FORCE_PAUSE, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
            }
            break;

        case NAV_SNT_PLAY_LOOP_CHANGED:
            {
                INT32           i;

                /*reset all windows' settign*/
                for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
                {
                    _NAV_CC_STATE_SET_UNKNOWN_DEFAULT(pt_this->at_grp[i].e_cc_state);
                }

                /*apply this new setting*/
                if(_NAV_CI_STATUS_FLAG_ACTIVE & pt_this->e_status_flag)
                {
                    cc_loop_update(pt_this->h_focus_svctx);

                    if(FALSE == nav_is_video_content_playing(pt_this->e_focus_grp))
                    {
                        *pe_to_ui = _NAV_CI_INFO_TUI_EMPTY;
                        break;
                    }

                    _nav_ci_change_cc(pt_this, NAV_CI_SM_DEFAULT, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
                }
            }
            break;

        case NAV_SNT_PLAY_NOT_ALLOWED:
            {
                _nav_ci_change_cc(pt_this, NAV_CI_SM_PAUSE, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
            }
            break;

        case NAV_SNT_PLAY_CHECK_ASKED:
            {
                if(TV_WIN_ID_LAST_VALID_ENTRY <= pt_this->e_focus_grp)
                {
                    DBG_ERROR((_ERROR_HEADER"Focus Group (%d) is over boundary. Do nothing\r\n", pt_this->e_focus_grp));
                    NAV_ASSERT(0);
                    break;
                }

                if(_NAV_CC_STATE_IS_WITH(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state) &&
                   SM_CC_TYPE_AUTO_SEL != pt_this->at_grp[pt_this->e_focus_grp].t_cc.e_cc_type)
                {
                    SCDB_REC_T  t_scdb_rec;

                    i4_ret = c_svctx_get_using_scdb_rec(pt_this->h_focus_svctx,
                                                        ST_CLOSED_CAPTION,
                                                        &t_scdb_rec);
                    if (i4_ret != SVCTXR_OK)
                    {
                        _nav_ci_change_cc(pt_this, NAV_CI_SM_USER_SETTING, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);
                    }
                }
            }
            break;

        default:
            break;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_focus_xng_nfy_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static INT32 _nav_ci_focus_xng_nfy_handler(
    _NAV_CI_T*                  pt_this,
    TV_WIN_ID_T                 e_new_focus)
{
    INT32                          i4_ret;
    TV_WIN_ID_T                 e_old_focus = pt_this->e_focus_grp;

    pt_this->e_status_flag |= _NAV_CI_STATUS_FLAG_FOCUS_CHANGING;

    /*if focus change, stop the cc first*/
    if(e_old_focus != e_new_focus)
    {
        _nav_ci_change_cc(pt_this, NAV_CI_SM_FORCE_PAUSE, _NAV_CI_SEM_NORMAL, FALSE, _NAV_CI_INFO_TUI_EMPTY);

        pt_this->e_focus_grp = e_new_focus;

        if(TV_WIN_ID_LAST_VALID_ENTRY <= pt_this->e_focus_grp)
        {
            DBG_ERROR((_ERROR_HEADER"Focus Group (%d) is over boundary. Do nothing\r\n", pt_this->e_focus_grp));
            NAV_ASSERT(0);
            return NAVR_FAIL;
        }

        /*copy settings of the old focus.*/
        if(_NAV_CC_STATE_IS_DEFAULT(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state))
        {
            _NAV_CI_COPY_FILTER(pt_this, pt_this->e_focus_grp, e_old_focus);
            /*Have to check this setting is suitable here.*/
        }
    }

    /*svctx handle*/
    i4_ret = nav_get_svctx_handle(pt_this->e_focus_grp, &pt_this->h_focus_svctx);
    if(NAVR_OK != i4_ret)
    {
        pt_this->e_status_flag &= (~_NAV_CI_STATUS_FLAG_FOCUS_CHANGING);

        DBG_ERROR((_ERROR_HEADER"Fail to get focus svctx handler (focus=%d), ret = %d\r\n", pt_this->e_focus_grp, i4_ret));
        pt_this->h_focus_svctx = NULL_HANDLE;
        return i4_ret;
    }

    /*refresh cc loop*/
    _nav_ci_reset_loop(pt_this->e_focus_grp);
    cc_loop_update(pt_this->h_focus_svctx);

    _nav_ci_change_cc(pt_this, NAV_CI_SM_USER_SETTING, _NAV_CI_SEM_DELAY, FALSE, _NAV_CI_INFO_TUI_EMPTY);

    pt_this->e_status_flag &= (~_NAV_CI_STATUS_FLAG_FOCUS_CHANGING);
    pt_this->e_status_flag |= _NAV_CI_STATUS_FLAG_INFO_STABLE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_sync_exec_cond
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static BOOL _nav_ci_current_is_tv_or_comp_source(VOID)
{
	INT32		i4_ret				= 0;
	ISL_REC_T	t_isl_rec			= {0};
	CHAR		s_disp_name[16+1]	= {0};
	UINT8		ui1_crnt_input_src	= 0;

	i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
	if(ISLR_OK != i4_ret)
	{
		return FALSE;
	}
	i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_crnt_input_src);
	if(ISLR_OK != i4_ret)
	{
		return FALSE;
	}

	i4_ret = a_isl_get_rec_by_id(ui1_crnt_input_src, &t_isl_rec);
	if(ISLR_OK != i4_ret)
	{
		return FALSE;
	}
	if(INP_SRC_TYPE_TV == t_isl_rec.e_src_type || a_nav_ipts_is_comp_source(&t_isl_rec))
	{
		return TRUE;
	}
	return FALSE;
}

		
static VOID _nav_ci_sync_exec_cond(
    _NAV_CI_T*                     pt_this)
{
    INT32                          i4_ret;
    UINT8                          ui1_cfg;

    /*get config*/
    i4_ret = a_cfg_get_cc_enabled(&ui1_cfg);
    if(APP_CFGR_OK == i4_ret)
    {
        switch(ui1_cfg)
        {
            case APP_CFG_CC_ON:
                pt_this->e_exec_cond = NAV_CI_EC_ON;
                break;
            case APP_CFG_CC_MUTE_ON:
                pt_this->e_exec_cond = NAV_CI_EC_MUTE_ON;
                break;
            default:
                pt_this->e_exec_cond = NAV_CI_EC_OFF;
                break;
        }
    }
    else
    {
        pt_this->e_exec_cond = NAV_CI_EC_OFF;
    }

    //Fix input source for TUNER when TV AC on/ RC on can't show cc\
    //Fix when vlog is on, power on can't show cc
    //Fix cc will delay hide when switch next channel
    //Fix DTV02152091 , when source is comp, anolog cc can't show   
    if(t_g_navigator.t_nav_ctx.t_gui_res.h_cc_plane && NAV_CI_EC_ON == pt_this->e_exec_cond && _nav_ci_current_is_tv_or_comp_source())
    {
        i4_ret = c_wgl_flip_canvas(t_g_navigator.t_nav_ctx.t_gui_res.h_cc_plane);
    }


    nav_ci_set_visible((NAV_CI_EC_ON == pt_this->e_exec_cond || NAV_CI_EC_MUTE_ON == pt_this->e_exec_cond) ? TRUE : FALSE);
    nav_banner_set_cc_state(pt_this->e_exec_cond == NAV_CI_EC_OFF ? FALSE : TRUE ,TRUE);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_set_cc_filter
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static INT32 _nav_ci_set_cc_filter(
    _NAV_CI_T*                     pt_this,
    const NAV_XNG_SRC_TRGT_T*      pt_xng_info)
{
    BOOL                           b_play_default = TRUE;
    BOOL                           b_same         = FALSE;

    if(pt_xng_info)
    {
        /* if same channel and already with CC, don't need to set to default */
        if (pt_xng_info->e_type == INP_SRC_TYPE_TV)
        {
            b_same = nav_is_same_channel(pt_xng_info->u.t_tv.ui2_crnt_svl_id,
                               pt_xng_info->u.t_tv.ui2_crnt_svl_rec_id,
                               pt_xng_info->u.t_tv.ui4_crnt_channel_id,
                               pt_xng_info->u.t_tv.ui2_trgt_svl_id,
                               pt_xng_info->u.t_tv.ui2_trgt_svl_rec_id,
                               pt_xng_info->u.t_tv.ui4_trgt_channel_id);
        }
        else if (pt_xng_info->e_type == INP_SRC_TYPE_AV)
        {
            if (pt_xng_info->u.t_av.ui1_crnt_inp_src_id == pt_xng_info->u.t_av.ui1_trgt_inp_src_id)
            {
                b_same = TRUE;
            }
            else
            {
                b_same = FALSE;
            }
        }
    }

    if(b_same)
    {
        if(TV_WIN_ID_LAST_VALID_ENTRY <= pt_this->e_focus_grp)
        {
            DBG_ERROR((_ERROR_HEADER"Focus Group (%d) is over boundary. Do nothing\r\n", pt_this->e_focus_grp));
            NAV_ASSERT(0);
            return NAVR_FAIL;
        }

        if(_NAV_CC_STATE_IS_NOT_DEFAULT(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state))
        {
            b_play_default = FALSE;
        }
    }

    if(b_play_default)
    {
        /*CR215680: _NAV_CI_INFO_TUI_EMPTY --> _NAV_CI_INFO_TUI_DSCRPTR_NOT_READY because we have to clean the CC icon first when channel change and wait for MW's notification.*/
        _nav_ci_change_cc(pt_this, NAV_CI_SM_DEFAULT, _NAV_CI_SEM_WAIT_EVENT, FALSE, (b_same) ? _NAV_CI_INFO_TUI_EMPTY : _NAV_CI_INFO_TUI_DSCRPTR_NOT_READY);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_default_cc_strm_comp_filter
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static BOOL _nav_ci_default_cc_strm_comp_filter(
                                                UINT16                     ui2_num_recs,
                                                UINT16                     ui2_idx,       /* in */
                                                const STREAM_COMP_ID_T*    pt_comp_id,    /* in */
                                                const SCDB_REC_T*          pt_scdb_rec,   /* in */
                                                VOID*                      pv_tag)        /* in */
{
    UINT8    ui1_anlg_cc = APP_CFG_CUSTOM_ANA_CC_CC1;
    UINT8    ui1_dig_cc  = APP_CFG_CUSTOM_DIG_CC_SERVICE1;
    INT32    i4_ret;
    UINT8    ui1_cfg = 0;


    i4_ret = a_cfg_get_cc_enabled(&ui1_cfg);
    if(i4_ret != APP_CFGR_OK)
    {
        a_cfg_set_cc_enabled(APP_CFG_CC_OFF);
    }

    i4_ret = a_cfg_custom_get_cc_val(&ui1_anlg_cc, &ui1_dig_cc);
    if(i4_ret != APP_CFGR_OK)
    {
        a_cfg_set_cc_enabled(APP_CFG_CC_OFF);
    }

    if(_nav_ci_scdb_is_default_ntsc_cc(ui1_anlg_cc, pt_scdb_rec) == TRUE)
    {
        return TRUE;
    }

     if((ui1_cfg != APP_CFG_CC_OFF)&&
        (_nav_ci_is_support_digital_cc(&t_g_cc_info)))
    {
        if(_nav_ci_scdb_is_default_dtv_cc(ui1_dig_cc, pt_scdb_rec) == TRUE)
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_change_cc
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _nav_ci_change_cc(
    _NAV_CI_T*                 pt_this,
    NAV_CI_SWITCH_METHOD_T     e_method,
    _NAV_CI_SWITCH_EXEC_MODE_T e_exec_mode,
    BOOL                       b_save,
    _NAV_CI_INFO_TO_UI_T       e_to_ui)
{
    SVCTX_CAPABILITY_T         e_cc_cap;
    INT32                      i4_ret;
    LOCKED_STATUS_T            e_lock;
    BOOL                       b_mute, b_is_xng, b_is_frozen = FALSE, b_select_new;

    CC_LOG((" e_method = %d,e_exec_mode = %d\n",e_method,e_exec_mode));

    if(TV_WIN_ID_LAST_VALID_ENTRY <= pt_this->e_focus_grp)
    {
        DBG_ERROR((_ERROR_HEADER"Focus Group (%d) is over boundary. Do nothing\r\n", pt_this->e_focus_grp));
        NAV_ASSERT(0);
        return NAVR_FAIL;
    }

    if(NAV_CI_SM_USER_SETTING == e_method &&
       _NAV_CC_STATE_IS_DEFAULT(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state))
    {
        e_method = NAV_CI_SM_DEFAULT;
    }

    if(NAV_CI_SM_DEFAULT == e_method)
    {
        CC_LOG(("_nav_ci_set_default_cc_filter \n"));
        _nav_ci_set_default_cc_filter(pt_this, pt_this->e_focus_grp);
        e_to_ui |= (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_CHECK_DESCRIPTOR);
    }

    if((NAV_CI_SM_PAUSE != e_method) &&
       (NAV_CI_SM_STOP != e_method) &&
       (NAV_CI_SM_FORCE_PAUSE != e_method) &&
       (NAV_CI_SM_FORCE_STOP != e_method))
    {
        e_cc_cap = _nav_ci_get_focus_capability(pt_this);

        if(SVCTX_CAPABILITY_NO == e_cc_cap) /*SVCTX_CAPABILITY_NO or SVCTX_CAPABILITY_UNKNOWN*/
        {
            /*For DTV00211698, because svctx returns NO when AV signal is removed,
            the user setting would be reset if the method is set to FORCE-STOP.
            Hence, we don't set the method to FORCE-STOP but set it to PAUSE.*/
            e_method = NAV_CI_SM_PAUSE;/*NAV_CI_SM_FORCE_STOP*/
        }
        else if(SVCTX_CAPABILITY_UNKNOWN == e_cc_cap)
        {
            e_method = NAV_CI_SM_PAUSE;
        }
    }

    /*get freeze status*/
    i4_ret = nav_get_freeze(pt_this->e_focus_grp, &b_is_frozen);
    if(NAVR_OK != i4_ret)
    {
        b_is_frozen = FALSE;
    }

    /*get lock status*/
    e_lock = nav_get_locked_status(pt_this->e_focus_grp);

    /*check condition*/
    if(NAV_CI_SM_FORCE_PAUSE != e_method && NAV_CI_SM_FORCE_STOP != e_method)
    {
        if(NAV_CI_EC_OFF == pt_this->e_exec_cond) /*check setting*/
        {
            e_method = NAV_CI_SM_STOP;
        }
        else if(LOCKED_STATUS_NONE != e_lock || b_is_frozen)
        {
            e_method = NAV_CI_SM_PAUSE;
        }
        else if(NAV_CI_EC_MUTE_ON == pt_this->e_exec_cond)
        {
            /*check mute*/
            i4_ret = nav_get_mute(&b_mute);
            if(NAVR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s: nav_get_mute() failed, ret=%d\r\n", __FUNCTION__, i4_ret));
                b_mute = FALSE;
            }

            if(FALSE == b_mute)
            {
                e_method = NAV_CI_SM_PAUSE;
            }
        }

        if(NAV_CI_SM_STOP != e_method && NAV_CI_SM_PAUSE != e_method)
        {
            //DTV03031196:_NAV_CI_STATUS_FLAG_ACTIVE & pt_this->e_status_flag only set 1 when recv resumed msg
            //in the issue,exist a timing case(1/100):resumed msg come to CC_info after here already exec,and cause got to _NAV_CC_STATE_SET_WITHOUT case 
            CHAR    s_active_app[APP_NAME_MAX_LEN + 1] = {0} ;
            a_am_get_active_app (&s_active_app);
            DBG_LOG_PRINT((" %s %d s_active_app:%s e_status_flag:0x%x\n",__FUNCTION__,__LINE__,s_active_app,pt_this->e_status_flag));

            /*check PIP/POP and active*/
            if(pt_this->e_status_flag & _NAV_CI_STATUS_FLAG_DISABLE_CC ||
               (0 == (_NAV_CI_STATUS_FLAG_ACTIVE & pt_this->e_status_flag) && c_strcmp(s_active_app,"navigator")))
            {
                e_method = NAV_CI_SM_PAUSE;
            }
        }
    }

    switch(e_method)
    {
        case NAV_CI_SM_NEXT:
            {
                if(FALSE == nav_is_video_content_playing(pt_this->e_focus_grp))
                {
                    DBG_ERROR((_ERROR_HEADER"%s: Cannot play next cc because no video.\r\n", __FUNCTION__));
                    return NAVR_NO_ACTION;
                }

                _nav_ci_next_cc(pt_this, &e_to_ui, &b_is_xng);

                if(b_save)
                {
                    _NAV_CI_SAVE_SELECTION(pt_this);
                }
                else if(b_is_xng)
                {
                    _NAV_CC_STATE_SET_NOT_DEFAULT(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state);
                }
            }
            break;

        case NAV_CI_SM_CURRENT:
            {
                if(_NAV_CI_IS_EMPTY_AUTO_FILTER(pt_this->at_grp[pt_this->e_focus_grp].t_cc))
                {
                    //make sure cc_filter right to update CC
                    _nav_ci_set_default_cc_filter(pt_this, pt_this->e_focus_grp);
                }
                e_to_ui |= (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_CHECK_DESCRIPTOR);
            }
            break;

        case NAV_CI_SM_USER_SETTING:
            {
                /*restore user's setting*/
                pt_this->at_grp[pt_this->e_focus_grp].t_cc = pt_this->at_grp[pt_this->e_focus_grp].t_user_cc;
                e_to_ui |= (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_CHECK_DESCRIPTOR);
            }
            break;

        case NAV_CI_SM_DEFAULT:
            break;

        case NAV_CI_SM_FORCE_STOP:
        case NAV_CI_SM_STOP:
            {
                /*reset cc setting*/
                _NAV_CI_ZERO_FILTER(pt_this, pt_this->e_focus_grp, TRUE);

                if(_NAV_CI_IS_AUTO_SELECT() && NAV_CI_SM_STOP == e_method)
                {
                    _NAV_CI_EMPTY_AUTO_FILTER(pt_this->at_grp[pt_this->e_focus_grp].t_cc);
                }
                e_to_ui |= _NAV_CI_INFO_TUI_CC_QUERY;
            }
            break;

        case NAV_CI_SM_FORCE_PAUSE:
        case NAV_CI_SM_PAUSE:
            {
                if(_NAV_CI_IS_AUTO_SELECT() && NAV_CI_SM_PAUSE == e_method)
                {
                    _NAV_CI_EMPTY_AUTO_FILTER(pt_this->at_grp[pt_this->e_focus_grp].t_cc);
                }
                else
                {
                    _NAV_CI_ZERO_FILTER(pt_this, pt_this->e_focus_grp, FALSE);
                }

                e_to_ui |= _NAV_CI_INFO_TUI_CC_QUERY;
            }
            break;
    case NAV_CI_SM_NONE:
        default:
            return NAVR_OK;
    }

    /*stop timer first*/
    _nav_ci_reset_delay_timer(pt_this, STOP_TIMER);

    /*We don't know why Klocwork warns at_grp[pt_this->e_focus_grp] out of boundary after _nav_ci_reset_delay_timer(),
      so for fixing this warning, we add a check here.*/
    if(TV_WIN_ID_LAST_VALID_ENTRY <= pt_this->e_focus_grp)
    {
        DBG_ERROR((_ERROR_HEADER"Focus Group (%d) is over boundary. Do nothing\r\n", pt_this->e_focus_grp));
        NAV_ASSERT(0);
        return NAVR_FAIL;
    }

    if(_NAV_CI_IS_IGNORE_FILTER(pt_this->at_grp[pt_this->e_focus_grp].t_cc))   /*CC stream isn't used anymore*/
    {
        if(NAV_CC_STREAM_STATUS_CLOSED != pt_this->e_stream_status)    /*CC stream is opening or opened*/
        {
            i4_ret = c_svctx_stop_stream(pt_this->h_focus_svctx, ST_CLOSED_CAPTION);
            if (SVCTXR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s: c_svctx_stop_stream() failed, ret=%d\r\n", __FUNCTION__, i4_ret));
            }
            CC_LOG(("c_svctx_stop_stream %s \n",(SVCTXR_OK == i4_ret) ? "ok" : "failed"));
            pt_this->e_stream_status = NAV_CC_STREAM_STATUS_CLOSED;
        }

        _NAV_CC_STATE_SET_WITHOUT(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state);
        pt_this->e_stream_status = NAV_CC_STREAM_STATUS_CLOSED;

        e_to_ui |= (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY);
    }
    else /*CC stream is necessary*/
    {
        b_select_new = TRUE;
        if(FALSE == _NAV_CI_IS_AUTO_SELECT() ||
           NAV_CC_STREAM_STATUS_OPENING == pt_this->e_stream_status ||
           LOCKED_STATUS_NONE != e_lock ||
           b_is_frozen)
        {
            /*stop current opening*/
            i4_ret = c_svctx_stop_stream(pt_this->h_focus_svctx, ST_CLOSED_CAPTION);
            if (SVCTXR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s: c_svctx_stop_stream() failed, ret=%d\r\n", __FUNCTION__, i4_ret));
            }

            CC_LOG((" c_svctx_stop_stream() %s.\n\r", (SVCTXR_OK == i4_ret) ? "ok" : "failed"));

            pt_this->e_stream_status = NAV_CC_STREAM_STATUS_CLOSED;
        }
        else if(NAV_CC_STREAM_STATUS_OPENED == pt_this->e_stream_status)
        {
            /*apply new CC filter*/
            i4_ret = _nav_ci_sync_crnt_filter(pt_this);
            if(NAVR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s: _nav_ci_sync_crnt_filter() failed, reselect one, ret=%d\r\n", __FUNCTION__, i4_ret));
                pt_this->e_stream_status = NAV_CC_STREAM_STATUS_CLOSED;
            }
            else
            {
                b_select_new = FALSE;
            }
            CC_LOG(("selection filter: type = %s, ntsc mask = 0x%.2x, dtv mask = 0x%.8x.\n",
                    SM_CC_TYPE_AUTO_SEL == pt_this->at_grp[pt_this->e_focus_grp].t_cc.e_cc_type ? "Auto" : "Manual",
                    pt_this->at_grp[pt_this->e_focus_grp].t_cc.u.t_auto_sel.ui1_ntsccc_mask,
                    (UINT32)pt_this->at_grp[pt_this->e_focus_grp].t_cc.u.t_auto_sel.ui8_dtvcc_mask));
            CC_LOG((" _nav_ci_sync_crnt_filter() %s.\n", (SVCTXR_OK == i4_ret) ? "ok" : "failed"));
        }
        else /*NAV_CC_STREAM_STATUS_CLOSED*/
        {
            /*apply new*/
        }

        if(_NAV_CI_IS_EMPTY_AUTO_FILTER(pt_this->at_grp[pt_this->e_focus_grp].t_cc))
        {
            CC_LOG((" _NAV_CC_STATE_SET_WITHOUT  \n"));
            _NAV_CC_STATE_SET_WITHOUT(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state);
            e_to_ui |= (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY);
        }
        else
        {
             CC_LOG((" _NAV_CC_STATE_SET_WITH  \n"));
            _NAV_CC_STATE_SET_WITH(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state);
        }

        CC_LOG((" b_select_new => %s  \n",b_select_new ? "YES" : "NO"));
        if(b_select_new)
        {
            _nav_ci_apply_cc_selection(pt_this, e_exec_mode, &e_to_ui);
        }
    }

    /*update UI*/
    /*In current implementation, we start a timer to delay the real cc selection,
      so the NAV_SNT_STREAM_STARTED will arrive slowly.
      We have to notify view to speed up the UI update.*/
    _nav_ci_update_cc_info(pt_this, e_to_ui);

    return NAVR_OK;
}

/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_apply_cc_selection
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _nav_ci_apply_cc_selection(
    _NAV_CI_T*                          pt_this,
    _NAV_CI_SWITCH_EXEC_MODE_T          e_exec_mode,
    _NAV_CI_INFO_TO_UI_T*               pe_to_ui)
{
    INT32                               i4_ret;

    CC_LOG(("CC execution mode = %s\n\r", _NAV_CI_SEM_IMMEDIATE == e_exec_mode ?
                                          "Immediate" :
                                          _NAV_CI_SEM_DELAY == e_exec_mode ?
                                          "Delay" :
                                          _NAV_CI_SEM_NORMAL == e_exec_mode ?
                                          "Normal" : "Wait Event"));
    /*current*/
    switch(e_exec_mode)
    {
        case _NAV_CI_SEM_IMMEDIATE:
            break;

        case _NAV_CI_SEM_DELAY:
            _nav_ci_reset_delay_timer(pt_this, RESET_TIMER);
            return NAVR_OK;

        case _NAV_CI_SEM_NORMAL:
            {
                if(_NAV_CI_IS_ALWAYS_DELAY() || NAV_CC_STREAM_STATUS_CLOSED != pt_this->e_stream_status)
                {
                    _nav_ci_reset_delay_timer(pt_this, RESET_TIMER);
                    return NAVR_OK;
                }
            }
            break;

        case _NAV_CI_SEM_WAIT_EVENT:
        default:
            /*wait for video stream started*/
            return NAVR_OK;
    }

    if(TV_WIN_ID_LAST_VALID_ENTRY <= pt_this->e_focus_grp)
    {
        DBG_ERROR((_ERROR_HEADER"Focus Group (%d) is over boundary. Do nothing\r\n", pt_this->e_focus_grp));
        NAV_ASSERT(0);
        return NAVR_FAIL;
    }

    /**/
    if(_NAV_CI_IS_IGNORE_FILTER(pt_this->at_grp[pt_this->e_focus_grp].t_cc))
    {
        pt_this->e_stream_status = NAV_CC_STREAM_STATUS_CLOSED;
        _NAV_CC_STATE_SET_WITHOUT(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state);

        *pe_to_ui |= _NAV_CI_INFO_TUI_CC_QUERY;
        return NAVR_OK;
    }

    CC_LOG(("CC selection filter: type = %s, ntsc mask = 0x%.2x, dtv mask = 0x%.8x.\n\r",
                    SM_CC_TYPE_AUTO_SEL == pt_this->at_grp[pt_this->e_focus_grp].t_cc.e_cc_type ? "Auto" : "Manual",
                    pt_this->at_grp[pt_this->e_focus_grp].t_cc.u.t_auto_sel.ui1_ntsccc_mask,
                    (UINT32)pt_this->at_grp[pt_this->e_focus_grp].t_cc.u.t_auto_sel.ui8_dtvcc_mask));

    i4_ret = c_svctx_select_cc_stream(pt_this->h_focus_svctx,
                                      pt_this->h_cc_plane,
                                      &pt_this->at_grp[pt_this->e_focus_grp].t_cc,
                                      nav_svctx_nfy_fct,
                                      (VOID*)nav_get_xng_req_id(pt_this->e_focus_grp));
    if(SVCTXR_OK == i4_ret)
    {
        _NAV_CC_STATE_SET_WITH(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state);
        pt_this->e_stream_status = NAV_CC_STREAM_STATUS_OPENING;

        CC_LOG((" CC c_svctx_select_cc_stream() ok.\n\r"));

        /*In NAV_UI_MSG_NO_STREAM handler, prog_info_banner ignores the notification for ST_CLOSED_CAPTION*/
        *pe_to_ui |= (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY);
    }
    else
    {
        CC_LOG(("CC c_svctx_select_cc_stream() failed ret = %d.\n\r",i4_ret));

        _NAV_CC_STATE_SET_WITHOUT(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state);
        pt_this->e_stream_status = NAV_CC_STREAM_STATUS_CLOSED;
        *pe_to_ui |= _NAV_CI_INFO_TUI_CC_WITHOUT;
    }

    return NAVR_OK;
}

/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_sync_crnt_filter
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _nav_ci_sync_crnt_filter(
    _NAV_CI_T*                      pt_this)
{
    SM_CC_FILTER_T              t_crnt_filter;
    SIZE_T                      z_size = sizeof(SM_CC_FILTER_T);
    INT32                       i4_ret;

    if(NAV_CC_STREAM_STATUS_OPENED != pt_this->e_stream_status)
    {
        DBG_ERROR((_ERROR_HEADER"%s: CC Stream Status should be NAV_CC_STREAM_STATUS_OPENED\r\n", __FUNCTION__));
        return NAVR_FAIL;
    }

    if(TV_WIN_ID_LAST_VALID_ENTRY <= pt_this->e_focus_grp)
    {
        DBG_ERROR((_ERROR_HEADER"Focus Group (%d) is over boundary. Do nothing\r\n", pt_this->e_focus_grp));
        NAV_ASSERT(0);
        return NAVR_FAIL;
    }
    /*get current CC filter*/
    i4_ret = c_svctx_get_stream_attr(pt_this->h_focus_svctx,
                                     ST_CLOSED_CAPTION,
                                     SM_CCH_GET_TYPE_CC_FLTR,
                                     &t_crnt_filter,
                                     &z_size);
   if(SVCTXR_OK != i4_ret || sizeof(SM_CC_FILTER_T) != z_size)
   {
        DBG_ERROR((_ERROR_HEADER"%s: c_svctx_get_stream_attr(SM_CCH_GET_TYPE_CC_FLTR) failed, size = %d, ret=%d\r\n", __FUNCTION__, z_size, i4_ret));
        return NAVR_FAIL;
   }

    /*check CC filter*/

    if(sizeof(SM_CC_FILTER_T) == z_size && _nav_ci_is_same_cc_filter(&(pt_this->at_grp[pt_this->e_focus_grp].t_cc), &t_crnt_filter))
    {
        CC_LOG(("[CC ]it is the same CC filter\n"));
        return NAVR_OK;
    }

    /*apply new CC filter*/
    i4_ret = c_svctx_set_stream_attr(pt_this->h_focus_svctx,
                                     ST_CLOSED_CAPTION,
                                     SM_CCH_SET_TYPE_CC_FLTR,
                                     &(pt_this->at_grp[pt_this->e_focus_grp].t_cc),
                                     sizeof(SM_CC_FILTER_T));
    if(SVCTXR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s: c_svctx_set_stream_attr(SM_CCH_SET_TYPE_CC_FLTR) failed, ret=%d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_get_focus_capability
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static SVCTX_CAPABILITY_T _nav_ci_get_focus_capability(
    _NAV_CI_T*                  pt_this)
{
    INT32                       i4_ret;
    SVCTX_CAPABILITY_T          e_capability = SVCTX_CAPABILITY_NO;

    if(pt_this->e_focus_grp >= TV_WIN_ID_LAST_VALID_ENTRY)
    {
        return SVCTX_CAPABILITY_NO;
    }

    i4_ret = c_svctx_get_cc_capability(pt_this->h_focus_svctx, &e_capability);

    return (SVCTXR_OK != i4_ret) ? SVCTX_CAPABILITY_UNKNOWN : e_capability;
}

/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_update_cc
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _nav_ci_update_cc_info(
    _NAV_CI_T*                      pt_this,
    _NAV_CI_INFO_TO_UI_T            e_to_ui)
{
    INT32                           i4_ret;
    NAV_CI_UI_INFO_FIELD_T          e_notify_field = NAV_CI_IF_EMPTY;
    TV_MODE_T                       e_tv_mode;
    UINT8                           ui1_lang_id;

    if(_NAV_CI_INFO_TUI_STATE_ITEM & e_to_ui)
    {
        e_notify_field = NAV_CI_IF_STATE_ITEM;

        /*reset last notify*/
        pt_this->t_last_notify.t_cc_detail = t_g_empty_detail;
        pt_this->t_last_notify.e_dscrptr_status = NAV_CI_UI_IS_INIT_VALUE;
        pt_this->t_last_notify.ui1_gui_lang_id = _NAV_CI_GUI_LANG_NULL;

        e_to_ui |= (_NAV_CI_INFO_TUI_CC_NOT_READY | _NAV_CI_INFO_TUI_CC_LANG_NOT_READY);

        i4_ret = nav_get_tv_mode(&e_tv_mode);
        if(NAVR_OK == i4_ret && TV_MODE_TYPE_NORMAL != e_tv_mode)
        {
            e_to_ui |= _NAV_CI_INFO_TUI_DSCRPTR_NOT_READY;
        }
    }

    /*disable cc info update during focus changing.*/
    if(_NAV_CI_STATUS_FLAG_FOCUS_CHANGING & pt_this->e_status_flag)
    {
        e_to_ui &= ~(_NAV_CI_INFO_TUI_DETAIL_MASK | _NAV_CI_INFO_TUI_DSCRPTR_MASK);
    }

    /**/
    if((_NAV_CI_INFO_TUI_DETAIL_MASK & e_to_ui) || (_NAV_CI_INFO_TUI_DSCRPTR_MASK & e_to_ui))
    {
        SVCTX_CAPABILITY_T          e_cc_cap = _nav_ci_get_focus_capability(pt_this);

        if((FALSE == nav_is_video_content_playing(pt_this->e_focus_grp)) ||
            nav_is_svl_empty(pt_this->e_focus_grp) ||
           (0 == (_NAV_CI_STATUS_FLAG_INFO_STABLE & pt_this->e_status_flag)) ||
           nav_is_signal_loss(pt_this->e_focus_grp) ||
           (LOCKED_STATUS_NONE != nav_get_locked_status(pt_this->e_focus_grp)) ||
           (SVCTX_CAPABILITY_YES != e_cc_cap))
        {
            if(_NAV_CI_INFO_TUI_CC_TYPE_MASK & e_to_ui)
            {
                e_to_ui |= _NAV_CI_INFO_TUI_CC_NOT_READY;
            }

            if(_NAV_CI_INFO_TUI_CC_LANG_MASK & e_to_ui)
            {
                e_to_ui |= _NAV_CI_INFO_TUI_CC_LANG_NOT_READY;
            }

            if(_NAV_CI_INFO_TUI_DSCRPTR_MASK & e_to_ui)
            {
                e_to_ui |= _NAV_CI_INFO_TUI_DSCRPTR_NOT_READY;
            }
        }
    }

    /*cc detail*/
    if(_NAV_CI_INFO_TUI_DETAIL_MASK & e_to_ui)
    {
        NAV_CI_UI_CC_DETAIL_T           t_detail = t_g_empty_detail;
        SM_CC_FILTER_T                  t_auto_cc_filter;
        SM_CC_FILTER_T*                 pt_cc_filter = NULL;
        SCDB_REC_T                      t_scdb_rec;
        NAV_CI_CC_TYPE_T                e_cc_type;
        SIZE_T                          z_size;
        UINT8                           ui1_cc_id;

        if(TV_WIN_ID_LAST_VALID_ENTRY <= pt_this->e_focus_grp)
        {
            DBG_ERROR((_ERROR_HEADER"Focus Group (%d) is over boundary. Do nothing\r\n", pt_this->e_focus_grp));
            NAV_ASSERT(0);
            return NAVR_FAIL;
        }

        if(((_NAV_CI_INFO_TUI_CC_QUERY & e_to_ui) && _NAV_CC_STATE_IS_WITH(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state))
           || (_NAV_CI_INFO_TUI_CC_LANG_QUERY & e_to_ui))
        {
            if(SM_CC_TYPE_AUTO_SEL == pt_this->at_grp[pt_this->e_focus_grp].t_cc.e_cc_type)
            {
                if(_NAV_CI_IS_AUTO_WITH_TOGGLE())
                {
                    _nav_ci_auto_cc_to_normal_cc(&pt_this->at_grp[pt_this->e_focus_grp].t_cc, &t_auto_cc_filter);
                    pt_cc_filter = &t_auto_cc_filter;
                }
                else
                {
                    z_size = sizeof(SM_CC_FILTER_T);

                    i4_ret = c_svctx_get_stream_attr(pt_this->h_focus_svctx,
                                                     ST_CLOSED_CAPTION,
                                                     SM_CCH_GET_TYPE_SELECTED_CC_FLTR,
                                                     &t_auto_cc_filter,
                                                     &z_size);

                    if(SVCTXR_OK == i4_ret)
                    {
                        pt_cc_filter = &t_auto_cc_filter;
                    }
                    else /*not ready to query information*/
                    {
                        e_to_ui |= _NAV_CI_INFO_TUI_CC_NOT_READY;
                    }
                }
            }
            else
            {
                pt_cc_filter = &pt_this->at_grp[pt_this->e_focus_grp].t_cc;
            }
        }

        if(_NAV_CI_INFO_TUI_IS_DETAIL_NOT_READY(e_to_ui))
        {
            t_detail.e_status = NAV_CI_UI_IS_NOT_READY;
        }
        else if((_NAV_CI_INFO_TUI_CC_WITHOUT & e_to_ui) ||
                (_NAV_CI_IS_IGNORE_FILTER(pt_this->at_grp[pt_this->e_focus_grp].t_cc)) ||
                (_NAV_CI_IS_EMPTY_AUTO_FILTER(pt_this->at_grp[pt_this->e_focus_grp].t_cc)))
        {
            t_detail.e_status = NAV_CI_UI_IS_WITHOUT;
        }
        else
        {
            /*cc type*/
            if(_NAV_CI_INFO_TUI_CC_TYPE_MASK & e_to_ui)
            {
                if((_NAV_CI_INFO_TUI_CC_QUERY & e_to_ui) && _NAV_CC_STATE_IS_WITH(pt_this->at_grp[pt_this->e_focus_grp].e_cc_state))
                {
                    i4_ret = _nav_ci_cc_type_classify(pt_cc_filter,
                                                      &e_cc_type,
                                                      &ui1_cc_id);
                    if(NAVR_OK != i4_ret)
                    {
                        t_detail.e_status = NAV_CI_UI_IS_NOT_READY;
                    }
                    else
                    {
                        t_detail.e_status = NAV_CI_UI_IS_WITH;
                        t_detail.e_cc_type = e_cc_type;
                        t_detail.ui1_cc_id = ui1_cc_id;
                    }
                }
                else /*_NAV_CI_INFO_TUI_CC_WITHOUT || CC_STATE_WITHOUT_CC || CC_STATE_DEFAULT*/
                {
                    t_detail.e_status = NAV_CI_UI_IS_WITHOUT;
                }
            }
            else
            {
                t_detail.e_status = pt_this->t_last_notify.t_cc_detail.e_status;
            }

            /*cc lang*/
            if(_NAV_CI_INFO_TUI_CC_LANG_MASK & e_to_ui)
            {
                if(_NAV_CI_INFO_TUI_CC_LANG_NOT_READY & e_to_ui)
                {
                    t_detail.e_lang_status = NAV_CI_UI_IS_NOT_READY;
                }
                else
                {
                    if((_NAV_CI_INFO_TUI_CC_LANG_QUERY & e_to_ui) && (NAV_CI_UI_IS_WITH == t_detail.e_status))
                    {
                        i4_ret = _nav_ci_get_using_cc_scdb(pt_this, pt_cc_filter, &t_scdb_rec);
                        if(NAVR_OK != i4_ret)
                        {
                            t_detail.e_lang_status = NAV_CI_UI_IS_NOT_READY;
                        }
                        else
                        {
                            t_detail.e_lang_status = NAV_CI_UI_IS_WITH;
                            c_strncpy(t_detail.s639_lang,
                                      t_scdb_rec.u.t_atsc_cc.s_lang,
                                      ISO_639_LANG_LEN);
                        }
                    }
                    else /*_NAV_CI_INFO_TUI_CC_LANG_WITHOUT || CC_STATE_WITHOUT_CC || CC_STATE_DEFAULT*/
                    {
                        t_detail.e_lang_status = NAV_CI_UI_IS_WITHOUT;
                    }
                }
            }
            else
            {
                t_detail.e_lang_status = pt_this->t_last_notify.t_cc_detail.e_lang_status;
            }
        }

        /*diff current detail & last notify*/
        if((t_detail.e_status != pt_this->t_last_notify.t_cc_detail.e_status) ||
           (t_detail.e_cc_type != pt_this->t_last_notify.t_cc_detail.e_cc_type) ||
           (t_detail.ui1_cc_id != pt_this->t_last_notify.t_cc_detail.ui1_cc_id))
        {
            pt_this->t_last_notify.t_cc_detail = t_detail;
            e_notify_field |= NAV_CI_IF_DETAIL;
        }
        else if((t_detail.e_lang_status != pt_this->t_last_notify.t_cc_detail.e_lang_status) ||
                (0 != c_strcmp(t_detail.s639_lang, pt_this->t_last_notify.t_cc_detail.s639_lang)))
        {
            pt_this->t_last_notify.t_cc_detail.e_lang_status = t_detail.e_lang_status;

            c_memcpy(pt_this->t_last_notify.t_cc_detail.s639_lang,
                     t_detail.s639_lang,
                     sizeof(ISO_639_LANG_T));

            e_notify_field |= NAV_CI_IF_DETAIL;
        }
    }

    /*cc descriptor*/
    if(_NAV_CI_INFO_TUI_DSCRPTR_MASK & e_to_ui)
    {
        NAV_CI_UI_INFO_STATUS_T     e_dscrptr_status;

        if(_NAV_CI_INFO_TUI_DSCRPTR_NOT_READY & e_to_ui)
        {
            e_dscrptr_status = NAV_CI_UI_IS_NOT_READY;
        }
        else
        {
            if(_NAV_CI_INFO_TUI_DSCRPTR_QUERY & e_to_ui)
            {
                e_dscrptr_status = (TRUE == _nav_ci_is_with_dscrptr(pt_this)) ? NAV_CI_UI_IS_WITH : NAV_CI_UI_IS_WITHOUT;
            }
            else/*_NAV_CI_INFO_TUI_DSCRPTR_WITHOUT*/
            {
                e_dscrptr_status = NAV_CI_UI_IS_WITHOUT;
            }
        }

        /*diff current dscrptr status & last notify*/
        if(e_dscrptr_status != pt_this->t_last_notify.e_dscrptr_status)
        {
            pt_this->t_last_notify.e_dscrptr_status = e_dscrptr_status;
            e_notify_field |= NAV_CI_IF_DSCRPTR;
        }
    }

    /*notify view*/
    if(e_notify_field)
    {
        /*check gui language*/
        ui1_lang_id = nav_get_mlm_lang_id();

        if(ui1_lang_id != pt_this->t_last_notify.ui1_gui_lang_id)
        {
            pt_this->t_last_notify.ui1_gui_lang_id = ui1_lang_id;

            e_notify_field |= NAV_CI_IF_GUI_LANG;
        }

        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               e_notify_field,
                                               &pt_this->t_last_notify);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_scdb_is_default_ntsc_cc
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static BOOL _nav_ci_scdb_is_default_ntsc_cc(
                                            UINT8                ui1_default_anlg_cc,
                                            const SCDB_REC_T*    pt_scdb_rec)
{
    UINT8          ui1_cfg = APP_CFG_CC_ON;
    _NAV_CI_T*     pt_this = &t_g_cc_info;
    INT32          i4_ret = 0;


    i4_ret = a_cfg_get_cc_enabled(&ui1_cfg);
    if(i4_ret != APP_CFGR_OK)
    {
        a_cfg_set_cc_enabled(APP_CFG_CC_OFF);
    }

    if(ui1_cfg == APP_CFG_CC_OFF)
    {
        return FALSE;
    }

    if(_nav_ci_is_support_digital_cc(pt_this))
    {
        return FALSE;
    }

    if (pt_scdb_rec->u.t_atsc_cc.e_type == CC_ATSC_LINE_21)
    {
        if ((pt_scdb_rec->u.t_atsc_cc.udata.t_cc_atsc_line_21.ui1_cc_id - NTSC_CC1) ==
            (ui1_default_anlg_cc - APP_CFG_CUSTOM_ANA_CC_CC1))
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_scdb_is_default_dtv_cc
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static BOOL _nav_ci_scdb_is_default_dtv_cc(
    UINT8                                  ui1_default_dig_cc,
    const SCDB_REC_T*                      pt_scdb_rec)
{
    if(!(_nav_ci_is_support_digital_cc(&t_g_cc_info)))
    {
        return FALSE;
    }

    if(pt_scdb_rec->u.t_atsc_cc.e_type == CC_ATSC_DTV)
    {
        if (pt_scdb_rec->u.t_atsc_cc.udata.t_cc_atsc_dtv.ui1_caption_svc_num == ui1_default_dig_cc)
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_is_support_digital_cc
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static BOOL _nav_ci_is_support_digital_cc(
    _NAV_CI_T*                            pt_this)
{
    SVL_REC_T                             t_svl_rec;
    INT32                                 i4_ret;

    /*check current source*/
    i4_ret = nav_get_svl_rec(pt_this->e_focus_grp, &t_svl_rec);
    if(NAVR_OK != i4_ret)   /*source is AV or other error*/
    {
        return FALSE;
    }
    if(BRDCST_TYPE_ANALOG == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
    {
        return FALSE;
    }

    return TRUE;
}

/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_swap_cc
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _nav_ci_swap_cc(
    _NAV_CI_T*               pt_this)
{
    _NAV_CC_SETTING_T        t_cc_setting;

    /*copy main setting*/
    t_cc_setting = pt_this->at_grp[TV_WIN_ID_MAIN];

    /*copy sub to main*/
    pt_this->at_grp[TV_WIN_ID_MAIN] = pt_this->at_grp[TV_WIN_ID_SUB];

    /*copy main to sub*/
    pt_this->at_grp[TV_WIN_ID_SUB] = t_cc_setting;

    return NAVR_OK;
}

/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_cc_type_classify
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _nav_ci_cc_type_classify(
    const SM_CC_FILTER_T*             pt_filter,
    NAV_CI_CC_TYPE_T*                 pe_cc_type,
    UINT8*                            pui1_cc_id)
{
    NAV_ASSERT(pe_cc_type && pui1_cc_id);

    if(NULL == pt_filter)
    {
        return NAVR_FAIL;
    }

    switch(pt_filter->e_cc_type)
    {
        case SM_CC_TYPE_NTSC_LINE21:
            {
                switch(pt_filter->u.e_data_type)
                {
                    case SM_NTSC_DATA_TYPE_CC1:
                        *pui1_cc_id = 1;
                        *pe_cc_type = NAV_CI_CC_TYPE_NTSC_CC;
                        break;
                    case SM_NTSC_DATA_TYPE_CC2:
                        *pui1_cc_id = 2;
                        *pe_cc_type = NAV_CI_CC_TYPE_NTSC_CC;
                        break;
                    case SM_NTSC_DATA_TYPE_CC3:
                        *pui1_cc_id = 3;
                        *pe_cc_type = NAV_CI_CC_TYPE_NTSC_CC;
                        break;
                    case SM_NTSC_DATA_TYPE_CC4:
                        *pui1_cc_id = 4;
                        *pe_cc_type = NAV_CI_CC_TYPE_NTSC_CC;
                        break;

                    case SM_NTSC_DATA_TYPE_T1:
                        *pui1_cc_id = 1;
                        *pe_cc_type = NAV_CI_CC_TYPE_NTSC_TEXT;
                        break;
                    case SM_NTSC_DATA_TYPE_T2:
                        *pui1_cc_id = 2;
                        *pe_cc_type = NAV_CI_CC_TYPE_NTSC_TEXT;
                        break;
                    case SM_NTSC_DATA_TYPE_T3:
                        *pui1_cc_id = 3;
                        *pe_cc_type = NAV_CI_CC_TYPE_NTSC_TEXT;
                        break;
                    case SM_NTSC_DATA_TYPE_T4:
                        *pui1_cc_id = 4;
                        *pe_cc_type = NAV_CI_CC_TYPE_NTSC_TEXT;
                        break;

                    default:
                        NAV_ASSERT(0);
                        return NAVR_FAIL;
                }
            }
            break;

        case SM_CC_TYPE_DTVCC:
            {
                *pe_cc_type = NAV_CI_CC_TYPE_DIG;
                *pui1_cc_id = pt_filter->u.ui1_service_num;
            }
            break;

        case SM_CC_TYPE_AUTO_SEL: /*not selected*/
        default: /*SM_CC_TYPE_IGNORE*/
            {
                return NAVR_FAIL;
            }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_reset_delay_timer
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static VOID _nav_ci_reset_delay_timer(
    _NAV_CI_T*                        pt_this,
    BOOL                              b_stop_only)
{
    INT32                             i4_ret;

    i4_ret = c_timer_stop(pt_this->h_delay_timer);
    if(OSR_OK != i4_ret)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop CC-Inof's h_delay_timer failed!"));
    }

    if(STOP_TIMER == b_stop_only)
    {
        pt_this->b_is_select_req_queued = FALSE;
        return;
    }

    i4_ret = c_timer_start(pt_this->h_delay_timer,
                           _NAV_CI_SELECT_DELAY_DUR,
                           X_TIMER_FLAG_ONCE,
                           _nav_ci_delay_cb,
                           pt_this);

    if (OSR_OK != i4_ret)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start CC-Inof's h_delay_timer failed!"));
    }

    pt_this->b_is_select_req_queued = TRUE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_delay_cb
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ci_delay_cb(
    HANDLE_T                 h_timer,
    VOID*                    pv_tag)
{
    /*post a message to itself*/
    nav_request_context_switch(_nav_ci_delay_msg_hdlr,
                               NULL,
                               NULL,
                               NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_delay_msg_hdlr
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ci_delay_msg_hdlr(
    VOID*                          pv_unused,
    VOID*                          pv_unused2,
    VOID*                          pv_unused3)
{
    _NAV_CI_T*                     pt_this = &t_g_cc_info;

    if(FALSE == pt_this->b_is_select_req_queued)
    {
         return;
    }

    pt_this->b_is_select_req_queued = FALSE;

    _nav_ci_change_cc(pt_this, NAV_CI_SM_CURRENT, _NAV_CI_SEM_IMMEDIATE, FALSE, _NAV_CI_INFO_TUI_EMPTY);
}

/*----------------------------------------------------------------------------
 * Name: _nav_ci_cfg_change_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_ci_cfg_change_cb(
    UINT16                        ui2_nfy_id,
    VOID*                         pv_tag,
    UINT16                        ui2_id)
{
    _NAV_CI_T*                    pt_this = &t_g_cc_info;

    if(pt_this->ui2_cc_cfg_nfy != ui2_nfy_id)
    {
        return;
    }

    if((_NAV_CI_CFG_ANALOG_ID == ui2_id) ||
       (_NAV_CI_CFG_DIG_ID == ui2_id) ||
       (_NAV_CI_CFG_ENABLE_ID == ui2_id))
    {
        /*post a message to itself*/
        nav_request_context_switch(_nav_ci_cfg_change_msg_hdlr,
                                   (VOID*)(UINT32)ui2_id,
                                   NULL,
                                   NULL);
    }
}

/*----------------------------------------------------------------------------
 * Name: _nav_ci_cfg_change_msg_hdlr
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_ci_cfg_change_msg_hdlr(
    VOID*                               pv_ui2_id,
    VOID*                               pv_unused1,
    VOID*                               pv_unused2)
{
    _NAV_CI_T*                          pt_this = &t_g_cc_info;
    _NAV_CI_INFO_TO_UI_T                e_to_ui = _NAV_CI_INFO_TUI_EMPTY;
    UINT16                              ui2_id = (UINT16)(UINT32)pv_ui2_id;

#ifdef APP_IPCC_SUPPORT
    UINT8      ui1_icl_mask = 0;
    UINT8      ui1_info_status = 0;
    SIZE_T 	 z_size ;
#endif

    /*The changed setting is used?*/
    if(_NAV_CI_CFG_DIG_ID == ui2_id && FALSE == _nav_ci_is_support_digital_cc(pt_this))
    {
        return;
    }

#ifdef APP_IPCC_SUPPORT
    ui1_icl_mask = ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS;
    z_size = ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS_SIZE;

    a_icl_get(ICL_MAKE_ID(ICL_GRPID_CUSTOM_NW_WIDGET, ui1_icl_mask),
              &ui1_info_status,
              &z_size);

    if((ui1_info_status == YAHOO_STATUS_DOCK_UP) ||
       (ui1_info_status == YAHOO_STATUS_SIDEBAR)||
       (ui1_info_status == YAHOO_STATUS_FULLSCREN))
    {
        _nav_ci_update_ipcc_idx();
        return;
    }
#endif
    /*update exec condition*/
    if(_NAV_CI_CFG_ENABLE_ID == ui2_id)
    {
        _nav_ci_sync_exec_cond(pt_this);
    }

    _nav_ci_stream_nfy_handler(pt_this, NAV_SNT_PLAY_LOOP_CHANGED, &e_to_ui);

    if(_NAV_CI_INFO_TUI_EMPTY != e_to_ui)
    {
        _nav_ci_update_cc_info(pt_this, e_to_ui);
    }

    _send_event_notify();

    return ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_reset_update_timer
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static VOID _nav_ci_reset_update_timer(
    _NAV_CI_T*                        pt_this,
    _NAV_CI_INFO_TO_UI_T              e_to_ui,
    BOOL                              b_stop_only)
{
    INT32                             i4_ret;

    i4_ret = c_timer_stop(pt_this->h_update_timer);
    if(OSR_OK != i4_ret)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop CC-Inof's h_update_timer failed!"));
    }

    if(STOP_TIMER == b_stop_only)
    {
        return;
    }

    i4_ret = c_timer_start(pt_this->h_update_timer,
                           _NAV_CI_UPDATE_DELAY_DUR,
                           X_TIMER_FLAG_ONCE,
                           _nav_ci_delay_update_cb,
                           (VOID*)(e_to_ui));

    if (OSR_OK != i4_ret)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start CC-Inof's h_update_timer failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_delay_update_cb
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ci_delay_update_cb(
    HANDLE_T                 h_timer,
    VOID*                    pv_tag)
{
    /*post a message to itself*/
    nav_request_context_switch(_nav_ci_delay_update, pv_tag, NULL, NULL);
}

/*----------------------------------------------------------------------------
 * Name: _nav_ci_delay_update
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_ci_delay_update(
                                 VOID*    pv_e_to_ui,
                                 VOID*    pv_unused2,
                                 VOID*    pv_unused3)
{
    _NAV_CI_T*              pt_this = &t_g_cc_info;
    _NAV_CI_INFO_TO_UI_T    e_to_ui = (_NAV_CI_INFO_TO_UI_T)(INT32)pv_e_to_ui;

    if(_NAV_CI_INFO_TUI_EMPTY != e_to_ui &&
       0 != (_NAV_CI_STATUS_FLAG_ACTIVE & pt_this->e_status_flag))
    {
        _nav_ci_update_cc_info(pt_this, e_to_ui);
    }
}

/*----------------------------------------------------------------------------
 * Name: _nav_ci_auto_cc_to_normal_cc
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_ci_auto_cc_to_normal_cc(
    const SM_CC_FILTER_T*       pt_auto_filter,
    SM_CC_FILTER_T*             pt_normal_filter)
{
    UINT64          ui8_mask;
    INT32           i;

    if(SM_CC_TYPE_AUTO_SEL != pt_auto_filter->e_cc_type)
    {
        *pt_normal_filter = *pt_auto_filter;
        return;
    }

    if(pt_auto_filter->u.t_auto_sel.ui1_ntsccc_mask)
    {
        for(i = 0, ui8_mask = 1; i < 8; i++)
        {
            if(ui8_mask & pt_auto_filter->u.t_auto_sel.ui1_ntsccc_mask)
            {
                pt_normal_filter->e_cc_type = SM_CC_TYPE_NTSC_LINE21;
                pt_normal_filter->u.e_data_type = (SM_NTSC_DATA_TYPE_T)(i + SM_NTSC_DATA_TYPE_CC1);
            }

            ui8_mask <<= 1;
        }
    }
    else if(pt_auto_filter->u.t_auto_sel.ui8_dtvcc_mask)
    {
        for(i = 0, ui8_mask = 1; i < 64; i++)
        {
            if(ui8_mask & pt_auto_filter->u.t_auto_sel.ui8_dtvcc_mask)
            {
                pt_normal_filter->e_cc_type = SM_CC_TYPE_DTVCC;
                pt_normal_filter->u.ui1_service_num = (UINT8)i;
            }

            ui8_mask <<= 1;
        }
    }
    else
    {
        _NAV_CI_SET_FILTER_IGNORE(*pt_normal_filter);
    }
}

/*-----------------------------------------------------------------------------
* Name
*      _nav_ci_delay_first_svc_xng
* Description  -
* Input        -
* Output       -
* Returns      -
*-----------------------------------------------------------------------------*/
static VOID _nav_ci_delay_first_svc_xng(
    VOID*                       pv_unused1,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3)
{
    _NAV_CI_T*                  pt_this = &t_g_cc_info;
    INT32                       i4_ret;\
      
    i4_ret = _nav_ci_change_cc(pt_this,
                               NAV_CI_SM_DEFAULT,
                               _NAV_CI_SEM_WAIT_EVENT,
                               FALSE,
                               (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_CHECK_DESCRIPTOR));
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to set cc-filter, ret=%d\r\n", i4_ret));
        return;
    }

    _nav_ci_update_cc_info(pt_this, (_NAV_CI_INFO_TO_UI_T)(_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY | _NAV_CI_CHECK_DESCRIPTOR));
}

/*-----------------------------------------------------------------------------
* Name
*      _nav_ci_is_same_cc_filter
* Description  -
* Input        -
* Output       -
* Returns      -
*-----------------------------------------------------------------------------*/
static BOOL _nav_ci_is_same_cc_filter(
    SM_CC_FILTER_T*                   pt_filter_1,
    SM_CC_FILTER_T*                   pt_filter_2)
{
    if(pt_filter_1->e_cc_type != pt_filter_2->e_cc_type)
    {
        return FALSE;
    }
    else
    {
        switch(pt_filter_1->e_cc_type)
        {
            case SM_CC_TYPE_NTSC_LINE21:
                return (pt_filter_1->u.e_data_type == pt_filter_2->u.e_data_type) ? TRUE : FALSE;
            case SM_CC_TYPE_DTVCC:
                return (pt_filter_1->u.ui1_service_num == pt_filter_2->u.ui1_service_num) ? TRUE : FALSE;
            case SM_CC_TYPE_AUTO_SEL:
                return (pt_filter_1->u.t_auto_sel.b_prefer_dtvcc == pt_filter_2->u.t_auto_sel.b_prefer_dtvcc &&
                        pt_filter_1->u.t_auto_sel.ui1_ntsccc_mask == pt_filter_2->u.t_auto_sel.ui1_ntsccc_mask &&
                        pt_filter_1->u.t_auto_sel.ui8_dtvcc_mask == pt_filter_2->u.t_auto_sel.ui8_dtvcc_mask) ? TRUE : FALSE;
            default:
                return FALSE;
        }
    }
}

/*-----------------------------------------------------------------------------
* Name
*      _nav_ci_reset_loop
* Description  -
* Input        -
* Output       -
* Returns      -
*-----------------------------------------------------------------------------*/
static INT32 _nav_ci_reset_loop(
    TV_WIN_ID_T                 e_win_id)
{
    CC_LOOP_RESET_PARAM_T       t_param;
    UINT32                      ui4_idx;
    INT32                       i4_ret;

    NAV_ASSERT(TV_WIN_ID_LAST_VALID_ENTRY != e_win_id);

    c_memset(&t_param, 0, sizeof(CC_LOOP_RESET_PARAM_T));
    t_param.z_struct_size = sizeof(CC_LOOP_RESET_PARAM_T);
    t_param.ui1_ntsc_cc = _NAV_CI_CC_RESET_METHOD;

    if(nav_is_digital_tv(e_win_id))
    {
        for(ui4_idx = 0; ui4_idx < CC_LOOP_DTV_CC_SIZE; ui4_idx++)
        {
            if(0 == ui4_idx)
            {
                t_param.aui1_dtv_cc[ui4_idx] = (NAV_CI_CUSTOM_DEF_DTVCC_BYTE_1 & 0xFE); /*remove Service0*/
            }
            else if(1 == ui4_idx)
            {
                t_param.aui1_dtv_cc[ui4_idx] = NAV_CI_CUSTOM_DEF_DTVCC_BYTE_2;
            }
            else if(2 == ui4_idx)
            {
                t_param.aui1_dtv_cc[ui4_idx] = NAV_CI_CUSTOM_DEF_DTVCC_BYTE_3;
            }
            else if(3 == ui4_idx)
            {
                t_param.aui1_dtv_cc[ui4_idx] = NAV_CI_CUSTOM_DEF_DTVCC_BYTE_4;
            }
            else if(4 == ui4_idx)
            {
                t_param.aui1_dtv_cc[ui4_idx] = NAV_CI_CUSTOM_DEF_DTVCC_BYTE_5;
            }
            else if(5 == ui4_idx)
            {
                t_param.aui1_dtv_cc[ui4_idx] = NAV_CI_CUSTOM_DEF_DTVCC_BYTE_6;
            }
            else if(6 == ui4_idx)
            {
                t_param.aui1_dtv_cc[ui4_idx] = NAV_CI_CUSTOM_DEF_DTVCC_BYTE_7;
            }
            else if(7 == ui4_idx)
            {
                t_param.aui1_dtv_cc[ui4_idx] = NAV_CI_CUSTOM_DEF_DTVCC_BYTE_8;
            }
        }
    }

    i4_ret = cc_loop_reset_ex(CC_LOOP_STRCUT_ID_RESET, &t_param);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"cc_loop_reset_ex() failed, ret=%d\r\n", i4_ret));
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * customization functions
 *---------------------------------------------------------------------------*/
#if APP_DISABLE_COMP_SOURCE
static BOOL _nav_ci_is_comp_source_cc(VOID)
{
    INT32           i4_ret = NAVR_OK;
    ISL_REC_T       t_isl_rec = {0};
    TV_WIN_ID_T     e_tv_win_id = TV_WIN_ID_MAIN;
    UINT8           SrcId = 0;
    extern INT32    a_cfg_custom_get_srcid_com_or_av(UINT8* pSrcId);

    i4_ret = nav_get_isl_rec(e_tv_win_id, &t_isl_rec);
    if(i4_ret != NAVR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"nav_get_isl_rec(). i4_ret = %d\r\n", i4_ret));
    }

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
    {
        if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI)
        {
            i4_ret = a_cfg_custom_get_srcid_com_or_av(&SrcId);
            if(i4_ret != 0)
            {
                DBG_ERROR((_ERROR_HEADER"<BANNER>a_cfg_custom_get_srcid_com_or_av fail i4_ret = %d\n",i4_ret));
            }

           if(SrcId == 1)/*component source*/
           {
               return TRUE;
           }
        }
    }
    return FALSE;
}
#endif


#ifdef APP_IPCC_SUPPORT
/*-----------------------------------------------------------------------------
* Name:
* Description:
* Inputs:
* Outputs:
* Returns:
*-----------------------------------------------------------------------------*/
static INT32 _nav_ci_update_ipcc_idx(VOID)
{
    INT32                   i4_ret = 0;

#ifdef APP_IPCC_SUPPORT
    UINT8                   ui1_idx = 0;
    MM_SVC_CC_IDX_INFO_T    t_cc_info = {0};
    HANDLE_T                h_svctx  = NULL_HANDLE;
    CHAR                    s_curr_disp_name[SYS_NAME_LEN+1]={0};
    UINT8                   ui1_cfg = APP_CFG_CC_ON;

    a_cfg_av_get_disp_name(s_curr_disp_name, sizeof(s_curr_disp_name));

    i4_ret = a_cfg_get_cc_enabled(&ui1_cfg);
    if(i4_ret < 0)
    {
        DBG_ERROR(("<CC_INFO> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
    }

    t_cc_info.b_enable = (ui1_cfg == APP_CFG_CC_ON )? TRUE : FALSE ;

    a_cfg_get_dig_cc(&ui1_idx);
    t_cc_info.ui1_idx = ui1_idx;
    CC_LOG(("set ipcc info = [idx:%d, enable:%d]\n\n",
                    ui1_idx,
                    t_cc_info.b_enable));
    acfg_get_svctx(s_curr_disp_name, &h_svctx);

    /* Set IPCC Index */
    i4_ret = c_svctx_generic_set_info(h_svctx,
                                     NULL_HANDLE,
                                     SVCTX_MM_SET_CC_IDX,
                                     (VOID*)(&t_cc_info),
                                     sizeof(MM_SVC_CC_IDX_INFO_T));
    if(i4_ret < 0)
    {
        DBG_ERROR(("<CC_INFO> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
    }
#if 0
    /* Set IPCC OSD */
    i4_ret = c_svctx_generic_set_info(h_svctx,
                                      NULL_HANDLE,
                                      SVCTX_MM_SET_CC_CANVAS,
                                      (VOID*)(&h_handle),
                                       sizeof(HANDLE_T));
    ACFG_LOG_ON_FAIL(i4_ret);
#endif
    CC_LOG(("set ipcc info = [%s, %d]\n\n",
            t_cc_info.b_enable == TRUE ? "true" : "false",
            t_cc_info.ui1_idx));
#endif

    return i4_ret;
}
#endif

/*-----------------------------------------------------------------------------
 * customization functions
 *---------------------------------------------------------------------------*/
#ifdef APP_NAV_CI_AUTO_SELECT
/*-----------------------------------------------------------------------------
* Name
*      _nav_ci_set_default_cc_filter
* Description
* Input arguments
* Output arguments
* Returns
*-----------------------------------------------------------------------------*/
static VOID _nav_ci_set_default_cc_filter(
    _NAV_CI_T*                                pt_this,
    TV_WIN_ID_T                               e_grp)
{
    SM_CC_FILTER_T* pt_cc_filter = &pt_this->at_grp[e_grp].t_cc;
    INT32    i4_ret;
    UINT8    ui1_cfg = APP_CFG_CC_ON;
    BOOL     b_support_analog_cc = TRUE;
    BOOL     b_support_digital_cc = TRUE;
    UINT8    ui1_dig_cc = 0;
    UINT8    ui1_anlg_cc = 0;


    i4_ret = a_cfg_custom_get_cc_val(&ui1_anlg_cc, &ui1_dig_cc);

    if(i4_ret != APP_CFGR_OK)
    {
        a_cfg_set_cc_enabled(APP_CFG_CC_OFF);
        b_support_digital_cc = FALSE;
        b_support_analog_cc = FALSE;
    }
    else
    {
        i4_ret = a_cfg_get_cc_enabled(&ui1_cfg);
        if((ui1_cfg == APP_CFG_CC_OFF) ||
           (APP_CFGR_OK != i4_ret))
        {
            b_support_digital_cc = FALSE;
            b_support_analog_cc = FALSE;
        }
        else if(_nav_ci_is_comp_source_cc())
        {
            b_support_digital_cc = FALSE;
            b_support_analog_cc = FALSE;
        }
        else
        {
            if(_nav_ci_is_support_digital_cc(pt_this))
            {
                //b_support_analog_cc = FALSE;
            }
            else
            {
                b_support_digital_cc = FALSE;
            }
        }
    }


    pt_cc_filter->e_cc_type = SM_CC_TYPE_AUTO_SEL;
    pt_cc_filter->u.t_auto_sel.b_prefer_dtvcc  = _NAV_CI_IS_PREFER_DTVCC();

    if(_NAV_CI_IS_AUTO_WITH_TOGGLE())
    {
        if(_NAV_CI_IS_PREFER_DTVCC())
        {
            if(FALSE != b_support_digital_cc)
            {
                pt_cc_filter->u.t_auto_sel.ui8_dtvcc_mask = SM_DTVCC_FLAG((ui1_dig_cc - APP_CFG_CUSTOM_DIG_CC_SERVICE1 + 1));
                pt_cc_filter->u.t_auto_sel.ui1_ntsccc_mask = SM_NTSCCC_FLAG((SM_NTSC_DATA_TYPE_T)(ui1_anlg_cc - APP_CFG_CUSTOM_ANA_CC_CC1 + SM_NTSC_DATA_TYPE_CC1));
            }
            else
            {
                pt_cc_filter->u.t_auto_sel.ui8_dtvcc_mask = 0;
                pt_cc_filter->u.t_auto_sel.ui1_ntsccc_mask = (FALSE == b_support_analog_cc) ? 0 : SM_NTSCCC_FLAG((SM_NTSC_DATA_TYPE_T)(ui1_anlg_cc - APP_CFG_CUSTOM_ANA_CC_CC1 + SM_NTSC_DATA_TYPE_CC1));
            }
        }
        else
        {
            if(FALSE != b_support_analog_cc)
            {
                pt_cc_filter->u.t_auto_sel.ui1_ntsccc_mask = SM_NTSCCC_FLAG((SM_NTSC_DATA_TYPE_T)(ui1_anlg_cc - APP_CFG_CUSTOM_ANA_CC_CC1 + SM_NTSC_DATA_TYPE_CC1));
                pt_cc_filter->u.t_auto_sel.ui8_dtvcc_mask = 0;
            }
            else
            {
                pt_cc_filter->u.t_auto_sel.ui1_ntsccc_mask = SM_NTSCCC_FLAG((SM_NTSC_DATA_TYPE_T)(ui1_anlg_cc - APP_CFG_CUSTOM_ANA_CC_CC1 + SM_NTSC_DATA_TYPE_CC1));
                pt_cc_filter->u.t_auto_sel.ui8_dtvcc_mask  = (FALSE == ui1_dig_cc) ? 0 : SM_DTVCC_FLAG((ui1_dig_cc - APP_CFG_CUSTOM_DIG_CC_SERVICE1 + 1));
            }
        }
    }
    else
    {
        pt_cc_filter->u.t_auto_sel.ui1_ntsccc_mask = (FALSE == ui1_anlg_cc) ? 0 : SM_NTSCCC_FLAG((SM_NTSC_DATA_TYPE_T)(ui1_anlg_cc - APP_CFG_CUSTOM_ANA_CC_CC1 + SM_NTSC_DATA_TYPE_CC1));
        pt_cc_filter->u.t_auto_sel.ui8_dtvcc_mask  = (FALSE == ui1_dig_cc) ? 0 : SM_DTVCC_FLAG((ui1_dig_cc - APP_CFG_CUSTOM_DIG_CC_SERVICE1 + 1));
    }

    /*reset flag*/
    _NAV_CC_STATE_SET_UNKNOWN_DEFAULT(pt_this->at_grp[e_grp].e_cc_state);

    /*backup user's setting*/
    pt_this->at_grp[e_grp].t_user_cc = pt_this->at_grp[e_grp].t_cc;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_get_using_cc_scdb
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static INT32 _nav_ci_get_using_cc_scdb(
    _NAV_CI_T*                         pt_this,
    SM_CC_FILTER_T*                    pt_filter,
    SCDB_REC_T*                        pt_scdb_rec)
{
    if(pt_filter)
    {
        return nav_get_cc_scdb_rec(pt_this->e_focus_grp, pt_filter, pt_scdb_rec);
    }
    else
    {
        return NAVR_FAIL;
    }
}

/*-----------------------------------------------------------------------------
* Name
*      _nav_ci_next_cc
* Description  -
* Input        -
* Output       -
* Returns      -
*-----------------------------------------------------------------------------*/
static VOID _nav_ci_next_cc(
    _NAV_CI_T*                  pt_this,
    _NAV_CI_INFO_TO_UI_T*       pe_to_ui,
    BOOL*                       pb_is_xng)
{
    UINT8   ui1_idx;

    a_cfg_custom_get_cc_idx(&ui1_idx);

    if(_nav_ci_is_support_digital_cc(pt_this))
    {
        ui1_idx = (ui1_idx + 1) % (APP_CFG_CUSTOM_DIG_CC_SERVICE6 - APP_CFG_CUSTOM_DIG_CC_SERVICE1 + 1);
    }
    else
    {
        ui1_idx = (ui1_idx + 1) % (APP_CFG_ANLG_CC_CC4 - APP_CFG_CUSTOM_ANA_CC_CC1+1); //can select analog CC4
    }

    a_cfg_custom_set_cc_idx(ui1_idx);

    _nav_ci_set_default_cc_filter(pt_this, pt_this->e_focus_grp);

    *pe_to_ui |= (_NAV_CI_INFO_TUI_CC_QUERY | _NAV_CI_INFO_TUI_CC_LANG_QUERY);

    /*backup user's setting*/
    if (pt_this->e_focus_grp >= TV_WIN_ID_LAST_VALID_ENTRY)
    {
        pt_this->e_focus_grp = TV_WIN_ID_MAIN;
    }
    pt_this->at_grp[pt_this->e_focus_grp].t_user_cc = pt_this->at_grp[pt_this->e_focus_grp].t_cc;

    *pb_is_xng = FALSE;
}

/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_is_with_dscrptr
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static BOOL _nav_ci_is_with_dscrptr(
    _NAV_CI_T*                      pt_this)
{
    SM_CC_AUTO_SEL_T                t_exist_cc;
    SIZE_T                          z_size;
    INT32                           i4_ret;

    z_size = sizeof(SM_CC_AUTO_SEL_T);

    i4_ret = c_svctx_get_stream_attr(pt_this->h_focus_svctx,
                                     ST_CLOSED_CAPTION,
                                     SM_CCH_GET_TYPE_EXISTED_CC_IND,
                                     &t_exist_cc,
                                     &z_size);

    if(SVCTXR_OK != i4_ret)
    {
        if(SVCTXR_WRONG_STATE == i4_ret &&
           0 != (_NAV_CI_STATUS_FLAG_ACTIVE & pt_this->e_status_flag) &&
           nav_is_video_content_playing(pt_this->e_focus_grp))
        {
            /*start a timer for update*/
            _nav_ci_reset_update_timer(pt_this, _NAV_CI_INFO_DELAY_UPDATE_MASK, RESET_TIMER);
        }
        return FALSE;
    }

    return (t_exist_cc.ui1_ntsccc_mask || t_exist_cc.ui8_dtvcc_mask) ? TRUE : FALSE;
}

#else /*APP_NAV_CI_AUTO_SELECT*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_set_default_cc_filter
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static VOID _nav_ci_set_default_cc_filter(
    _NAV_CI_T*                            pt_this,
    TV_WIN_ID_T                           e_grp)
{
    SM_CC_FILTER_T* pt_cc_filter = &pt_this->at_grp[e_grp].t_cc;

    do
    {
        if(_NAV_CI_IS_PREFER_DTVCC())
        {
            if(_nav_ci_set_default_dtv_cc_filter(pt_this, pt_cc_filter) == TRUE)
            {
                CC_LOG((" _nav_ci_set_default_dtv_cc_filter \n"));
                break;
            }

            if(_nav_ci_set_default_ntsc_cc_filter(pt_cc_filter) == TRUE)
            {
                CC_LOG((" _nav_ci_set_default_dtv_cc_filter \n"));
                break;
            }
        }
        else
        {
            if(_nav_ci_set_default_ntsc_cc_filter(pt_cc_filter) == TRUE)
            {
                CC_LOG(("_nav_ci_set_default_dtv_cc_filter \n"));
                break;
            }

            if(_nav_ci_set_default_dtv_cc_filter(pt_this, pt_cc_filter) == TRUE)
            {
                CC_LOG((" _nav_ci_set_default_dtv_cc_filter \n"));
                break;
            }
        }

        _NAV_CI_SET_FILTER_IGNORE(*pt_cc_filter);

    } while(0);

    /*reset flag*/
    _NAV_CC_STATE_SET_UNKNOWN_DEFAULT(pt_this->at_grp[e_grp].e_cc_state);

    /*backup user's setting*/
    pt_this->at_grp[e_grp].t_user_cc = pt_this->at_grp[e_grp].t_cc;

#ifdef APP_IPCC_SUPPORT
    _nav_ci_update_ipcc_idx();
#endif

}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_set_default_ntsc_cc_filter
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static BOOL _nav_ci_set_default_ntsc_cc_filter(
    SM_CC_FILTER_T*                            pt_cc_filter)
{
    UINT8  ui1_anlg_cc = APP_CFG_CUSTOM_ANA_CC_CC1;
    UINT8  ui1_dig_cc  = APP_CFG_CUSTOM_DIG_CC_SERVICE1;
    INT32  i4_ret;
    UINT8   ui1_cfg = APP_CFG_CC_ON;

    i4_ret = a_cfg_get_cc_enabled(&ui1_cfg);
    if(i4_ret != APP_CFGR_OK)
    {
        a_cfg_set_cc_enabled(APP_CFG_CC_OFF);
    }

    else
    {
        if(!(_nav_ci_is_support_digital_cc(&t_g_cc_info)))
        {
            pt_cc_filter->e_cc_type     = SM_CC_TYPE_NTSC_LINE21;
            pt_cc_filter->u.e_data_type = (SM_NTSC_DATA_TYPE_T)(ui1_anlg_cc - APP_CFG_CUSTOM_ANA_CC_CC1 + SM_NTSC_DATA_TYPE_CC1);
            return TRUE;
        }
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_set_default_dtv_cc_filter
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static BOOL _nav_ci_set_default_dtv_cc_filter(
                                             _NAV_CI_T*         pt_this,
                                             SM_CC_FILTER_T*    pt_cc_filter)
{
    INT32   i4_ret;
    UINT8   ui1_anlg_cc = APP_CFG_CUSTOM_ANA_CC_CC1;
    UINT8   ui1_dig_cc  = APP_CFG_CUSTOM_DIG_CC_SERVICE1;
    UINT8   ui1_cfg = APP_CFG_CC_ON;


    i4_ret = a_cfg_get_cc_enabled(&ui1_cfg);
    if(i4_ret != APP_CFGR_OK)
    {
        a_cfg_set_cc_enabled(APP_CFG_CC_OFF);
    }

    /*check current source*/
    else
    {
        if(_nav_ci_is_support_digital_cc(pt_this))
        {
            pt_cc_filter->e_cc_type         = SM_CC_TYPE_DTVCC;
            pt_cc_filter->u.ui1_service_num = ui1_dig_cc;
            return TRUE;
        }
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
* Name
*      _nav_ci_get_using_cc_scdb
* Description  -
* Input        -
* Output       -
* Returns      -
*-----------------------------------------------------------------------------*/
static INT32 _nav_ci_get_using_cc_scdb(
    _NAV_CI_T*                         pt_this,
    SM_CC_FILTER_T*                    pt_filter,
    SCDB_REC_T*                        pt_scdb_rec)
{
    INT32                             i4_ret;

    i4_ret = c_svctx_get_using_scdb_rec(pt_this->h_focus_svctx, ST_CLOSED_CAPTION, pt_scdb_rec);

    return (SVCTXR_OK == i4_ret) ? NAVR_OK : NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
* Name
*      _nav_ci_next_cc
* Description  -
* Input        -
* Output       -
* Returns      -
*-----------------------------------------------------------------------------*/
static VOID _nav_ci_next_cc(
    _NAV_CI_T*                  pt_this,
    _NAV_CI_INFO_TO_UI_T*       pe_to_ui,
    BOOL*                       pb_is_xng)
{
    SM_CC_FILTER_T  t_org_cc;
    INT32           i, i4_count = 63 + 8; /*digital cc: 63, analog cc: 8*/
    BOOL            b_is_support_digital;

    b_is_support_digital = _nav_ci_is_support_digital_cc(pt_this);

    t_org_cc = pt_this->at_grp[pt_this->e_focus_grp].t_cc;
    i = 0;
    while(i <= i4_count)
    {
        i++;

        if(FALSE == cc_loop_next(&(pt_this->at_grp[pt_this->e_focus_grp].t_cc)))
        {
            _NAV_CI_SET_FILTER_IGNORE(pt_this->at_grp[pt_this->e_focus_grp].t_cc);

            *pe_to_ui |= _NAV_CI_INFO_TUI_CC_QUERY;
            break;
        }
        else
        {
            if((SM_CC_TYPE_DTVCC == pt_this->at_grp[pt_this->e_focus_grp].t_cc.e_cc_type) &&
                (FALSE == b_is_support_digital))
            {
                continue;
            }

            *pe_to_ui |= _NAV_CI_INFO_TUI_CC_QUERY;
            break;
        }
    }

    /*backup user's setting*/
    pt_this->at_grp[pt_this->e_focus_grp].t_user_cc = pt_this->at_grp[pt_this->e_focus_grp].t_cc;

    *pb_is_xng = (_nav_ci_is_same_cc_filter(&t_org_cc, &pt_this->at_grp[pt_this->e_focus_grp].t_cc)) ? FALSE : TRUE;
}

/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_is_with_dscrptr
 * Description
 * Input arguments
 *      pt_this
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static BOOL _nav_ci_is_with_dscrptr(
    _NAV_CI_T*                      pt_this)
{
    SVCTX_CC_AVIL_COND_T            e_avail;
    SIZE_T                          z_size;
    INT32                           i4_ret;

    z_size = sizeof(SVCTX_CC_AVIL_COND_T);
    i4_ret = c_svctx_get(pt_this->h_focus_svctx,
        SVCTX_COMMON_GET_CC_AVIL_COND,
        &e_avail,
        &z_size);

    if(SVCTXR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_svctx_get(SVCTX_COMMON_GET_CC_AVIL_COND) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return FALSE;
    }

    return ((SVCTX_CC_AVIL_COND_YES == e_avail) ? TRUE : FALSE);
}

#endif /*APP_NAV_CI_AUTO_SELECT*/

#ifdef APP_NAV_CI_SAVE_CC_ONOFF
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_save_onoff_cfg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static INT32 _nav_ci_save_onoff_cfg(
    NAV_CI_EXEC_COND_T              e_exec_cond)
{
    INT32                           i4_ret;
    UINT8                           ui1_cfg;

    switch(e_exec_cond)
    {
        case NAV_CI_EC_OFF:
            ui1_cfg = APP_CFG_CC_OFF;
            break;

        case NAV_CI_EC_MUTE_ON:
            ui1_cfg = APP_CFG_CC_MUTE_ON;
            break;

        case NAV_CI_EC_ON:
        default:
            ui1_cfg = APP_CFG_CC_ON;
            break;
    }

    i4_ret = a_cfg_set_cc_enabled(ui1_cfg);

    return (APP_CFGR_OK == i4_ret) ? NAVR_OK : NAVR_FAIL;
}
#endif /*APP_NAV_CI_SAVE_CC_ONOFF*/


#ifdef APP_NAV_CI_SAVE_CC
/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_save_selection
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _nav_ci_save_selection(
    _NAV_CI_T*                      pt_this)
{
    SM_CC_FILTER_T                  t_normal_filter;
    BOOL                            b_analog, b_digital;
    UINT8                           ui1_analog_cc, ui1_digital_cc;
    INT32                           i4_analog = APP_CFGR_OK, i4_digital = APP_CFGR_OK;
    UINT8                           ui1_anlg_cc = APP_CFG_CUSTOM_ANA_CC_CC1;
    UINT8                           ui1_dig_cc  = APP_CFG_CUSTOM_DIG_CC_SERVICE1;

#ifdef APP_NAV_CI_AUTO_SELECT
    _nav_ci_auto_cc_to_normal_cc(&pt_this->at_grp[pt_this->e_focus_grp].t_user_cc, &t_normal_filter);
#else
    t_normal_filter = pt_this->at_grp[pt_this->e_focus_grp].t_user_cc;
#endif

   a_cfg_custom_get_cc_val(&ui1_anlg_cc, &ui1_dig_cc);

    if(_NAV_CI_IS_IGNORE_FILTER(t_normal_filter))
    {
        b_analog = FALSE;
        b_digital = FALSE;
        a_cfg_set_cc_enabled(APP_CFG_CC_OFF);
        //ui1_analog_cc = APP_CFG_ANLG_CC_OFF;
        //ui1_digital_cc = APP_CFG_DIG_CC_OFF;
    }
    else if(SM_CC_TYPE_DTVCC == t_normal_filter.e_cc_type)
    {
        if(NAV_CI_CUSTOM_IS_SAVE_DIGITAL_CC(t_normal_filter.u.ui1_service_num))
        {
            b_analog = TRUE;
            b_digital = TRUE;
            ui1_analog_cc = ui1_anlg_cc;
            ui1_digital_cc = t_normal_filter.u.ui1_service_num;
        }
        else
        {
            a_cfg_set_cc_enabled(APP_CFG_CC_OFF);
            b_analog = FALSE;
            b_digital = FALSE;
        }
    }
    else if(SM_CC_TYPE_NTSC_LINE21 == t_normal_filter.e_cc_type) /*analog cc*/
    {
        b_analog = TRUE;
        b_digital = FALSE;
        ui1_analog_cc = t_normal_filter.u.e_data_type - SM_NTSC_DATA_TYPE_CC1 + APP_CFG_CUSTOM_ANA_CC_CC1;
    }
    else
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Unknown CC setting.\r\n", __FUNCTION__));
        return NAVR_FAIL;
    }

    if(b_analog)
    {
        i4_analog = a_cfg_set_anlg_cc(ui1_analog_cc);
        if(APP_CFGR_OK != i4_analog)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): a_cfg_set_anlg_cc(%d) failed, ret=%d\r\n", __FUNCTION__, ui1_analog_cc, i4_analog));
        }
    }

    if(b_digital)
    {
        i4_digital = a_cfg_set_dig_cc(ui1_digital_cc);
        if(APP_CFGR_OK != i4_digital)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): a_cfg_set_dig_cc(%d) failed, ret=%d\r\n", __FUNCTION__, ui1_digital_cc, i4_digital));
        }
    }

    return (((APP_CFGR_OK == i4_analog) && (APP_CFGR_OK == i4_digital)) ? NAVR_OK : NAVR_FAIL);
}
#endif /*#ifdef APP_NAV_CI_SAVE_CC*/

#ifdef APP_NAV_DISABLE_CC_IN_PIP_POP
/*------------------------------------------------------------------------------
 * Name
 *      _nav_ci_save_selection
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static VOID _nav_ci_tv_mode_xng_nfy_handler(
    _NAV_CI_T*                  pt_this,
    NAV_TV_MODE_XNG_INFO_T*     pt_info)
{
    NAV_CI_SWITCH_METHOD_T      e_method;
    BOOL                        b_change_cc;

    if(TV_MODE_TYPE_NORMAL == pt_info->e_new_tv_mode)
    {
        pt_this->e_status_flag &= ~(_NAV_CI_STATUS_FLAG_DISABLE_CC);

        e_method = NAV_CI_SM_USER_SETTING;
        b_change_cc = (TV_MODE_TYPE_LAST_VALID_ENTRY != pt_info->e_old_tv_mode &&
                       TV_WIN_ID_MAIN == pt_this->e_focus_grp) ? TRUE : FALSE;
    }
    else /*PIP or POP*/
    {
        pt_this->e_status_flag |= _NAV_CI_STATUS_FLAG_DISABLE_CC;

        /*stop running cc*/
        e_method = NAV_CI_SM_PAUSE;
        b_change_cc = (TV_MODE_TYPE_LAST_VALID_ENTRY != pt_info->e_old_tv_mode) ? TRUE : FALSE;
    }

    if(b_change_cc)
    {
        _nav_ci_change_cc(pt_this, e_method, _NAV_CI_SEM_DELAY, FALSE, _NAV_CI_INFO_TUI_EMPTY);
    }
}

#endif /*#ifdef APP_NAV_DISABLE_CC_IN_PIP_POP*/

#endif /*#ifndef APP_DVBT_SUPPORT*/
