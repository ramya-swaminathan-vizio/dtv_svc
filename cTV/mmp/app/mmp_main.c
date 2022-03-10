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
 * $RCSfile: mmp_main.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_sys_name.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_scc.h"
#include "c_svctx.h"
#include "c_dbg.h"
#include "am/a_am.h"
#include "app_util/a_common.h"
#include "app_util/a_tv.h"
#include "app_util/a_cfg.h"
#include "app_util/a_icl.h"
#include "mmp/a_mmp.h"
#include "mmp/mmp_mmc_basic.h"
#include "mmp/mmp_tools.h"
#include "mmp/app/mmp_main.h"
#include "mmp/app/mmp_cli.h"
#include "res/mmp/app/mmp_main_rc.h"
#include "mmp/browse_eng/mmp_browse_eng.h"

#include "res/mmp/file_filter/mmp_ff_rc.h"
#include "nav/a_navigator.h"
#include "msgconvert/msgconvert.h"

#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
#include "mmp/rmk_client/mmp_rmk_client.h"
#endif

#ifdef APP_MENU_MMP_COEXIST
#include "menu2/a_menu.h"
#include "epg/a_epg.h"
#include "mmp/photo_eng/mmp_photo_eng.h"
#endif

#ifdef APP_MJC_SUPPORT
    #include "c_rm.h"
    #include "u_rm_dev_types.h"
    #include "u_drv_cust.h"
#endif

#include "agent/a_agent.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "c_fm_dlnafs.h"

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
#include "mmp/dmr/mmp_dmr.h"
#endif

#ifdef APP_C4TV_SUPPORT
#include "nav/link_mode/link_mode.h"
#endif

#include "mmp/disp_res_ctrler/mmp_drc.h"

#include "mmp/foreground/mmp_foreground.h"
#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif

#include "rest/a_rest_event.h"

#include "res/app_util/icl/a_icl_custom.h"
#include "msgconvert/msgconvert.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define MMP_MSG_TYPE_SWTH_CTX   ((UINT32) 0)
#define MMP_MSG_TYPE_SWTH_CTX_WO_RES_CHK   ((UINT32) 1)

typedef enum __MMP_MAIN_BM_OPTION_T
{
    _MMP_MAIN_BM_OPTION_DISABLE = 0,
    _MMP_MAIN_BM_OPTION_RESET
} _MMP_MAIN_BM_OPTION_T;

typedef enum __MMP_MAIN_GAMMA_OPTION_T
{
    _MMP_MAIN_GAMMA_OPTION_DEFAULT = 0,
    _MMP_MAIN_GAMMA_OPTION_RESET
} _MMP_MAIN_GAMMA_OPTION_T;

typedef struct _MMP_MAIN_MSG_SWTH_CTX_T
{
    mmp_mc_event_handler        pf_event_handler;
    VOID*                       pv_param1;
    VOID*                       pv_param2;
    VOID*                       pv_param3;
    VOID*                       pv_param4;
} MMP_MAIN_MSG_SWTH_CTX_T;

typedef struct _MMP_MAIN_APP_INST_T
{
    HANDLE_T                    h_app;
    HANDLE_T                    h_main_svctx;
    HANDLE_T                    h_sub_svctx;
    HANDLE_T                    h_tvbypass_svctx;
    HANDLE_T                    h_mnbypass_svctx;
#ifdef APP_NAV_REC_SUPPORT
    HANDLE_T                    h_rec_svctx;
#endif
    HANDLE_T                    h_cable_svl;
    HANDLE_T                    h_air_svl;
    HANDLE_T                    h_canvas;
    HANDLE_T                    h_sbtl_canvas;
    UINT16                      ui2_gui_lang_nfy;
    BOOL                        b_is_working_res_ready;
    HANDLE_T                    h_ready_signal;

    WGL_CANVAS_INFO_T           t_orig_canvas_info;

    HANDLE_T                    h_transparent_lst;

    UINT32                      ui4_activation_key;

    BOOL                        b_chk_key_traffic;
    UINT32                      ui4_last_rece_key_tick;
    UINT32                      ui4_last_handle_key_tick;
#ifdef APP_CAST_TV_MMP
    ISL_REC_T                   t_last_isl_rec;
#endif

    BOOL                        b_skip_restore_tv_res_while_pause;
} MMP_MAIN_APP_INST_T;

typedef struct __MMP_MAIN_TS_INST_T
{
    HANDLE_T                    h_mutex;
    MMP_MAIN_AP_STATUS_T        e_app_status;
} _MMP_MAIN_TS_INST_T;

#define _MMP_MAIN_TS_LOCK(_pt_this, _err_stmt)                                      \
{                                                                                   \
    if(OSR_OK != c_sema_lock((_pt_this)->h_mutex, X_SEMA_OPTION_WAIT))              \
    {                                                                               \
        _err_stmt;                                                                  \
    }                                                                               \
}

#define _MMP_MAIN_TS_UNLOCK(_pt_this, _err_stmt)                                    \
{                                                                                   \
    if(OSR_OK != c_sema_unlock((_pt_this)->h_mutex))                                \
    {                                                                               \
        MMP_ASSERT(0);                                                              \
        _err_stmt;                                                                  \
    }                                                                               \
}

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static MMP_MAIN_APP_INST_T t_g_app_inst = {0};
static _MMP_MAIN_TS_INST_T t_g_app_ts_inst = {0};

#define MMP_MAIN_APP_DEFAULT_GAMMA      ((UINT16) 2)

/*-----------------------------------------------------------------------------
 * customization declarations
 *---------------------------------------------------------------------------*/
#ifndef _MMP_MAIN_RC_STACK_SIZE
    #define _MMP_MAIN_RC_STACK_SIZE     (16 * 1024) /*bytes*/
#endif

#ifndef _MMP_MAIN_RC_MAX_MSGS
    #define _MMP_MAIN_RC_MAX_MSGS       (192)
#endif

#ifndef _MMP_MAIN_RC_MSG_MAX_SIZE
    #define _MMP_MAIN_RC_MSG_MAX_SIZE   (64)    /*bytes*/
#endif

#ifndef _MMP_MAIN_RC_MEM_MIN_SIZE
    #define _MMP_MAIN_RC_MEM_MIN_SIZE   (0)
#endif

#ifndef _MMP_MAIN_RC_MEM_MAX_SIZE
    #define _MMP_MAIN_RC_MEM_MAX_SIZE   (50 * 1024 + MMP_RC_POOL_TOTAL_SIZE)   /*bytes*/
#endif

#ifndef _MMP_MAIN_RC_FILE_MAX_SIZE
    #define _MMP_MAIN_RC_FILE_MAX_SIZE  (16777216)  /*bytes*/
#endif

#ifndef _MMP_MAIN_RC_MAX_FILES
    #define _MMP_MAIN_RC_MAX_FILES      (64)
#endif

#ifndef _MMP_MAIN_RC_MAX_HANDLES
    #define _MMP_MAIN_RC_MAX_HANDLES    (1024)
#endif

#ifndef _MMP_MAIN_RC_MAX_SEMAS
    #define _MMP_MAIN_RC_MAX_SEMAS      (16)
#endif

#ifndef APP_VTRL_INP_SRC_MMP_SUPPORT
#ifndef MMP_MAIN_RC_SYSTEM_KEY_HANDLER
    #define MMP_MAIN_RC_SYSTEM_KEY_HANDLER(_ui4_keycode)        \
    (                                                           \
        _mmp_main_sys_key_hdlr((_ui4_keycode))                  \
    )

    #define _MMP_MAIN_ENABLE_SYS_KEY_HDLR   1
    static BOOL _mmp_main_sys_key_hdlr(UINT32 ui4_keycode);
#endif
#endif

#ifndef MMP_MAIN_RC_CHECK_MENU_MMP_COEXIST_COND
    #define MMP_MAIN_RC_CHECK_MENU_MMP_COEXIST_COND()   (TRUE)
#endif

#ifndef MMP_MAIN_RC_MISS_KEY_THRESHOLD
    #define MMP_MAIN_RC_MISS_KEY_THRESHOLD (10)
#endif


/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _mmp_main_app_init_fct(
        const CHAR*             ps_name,
        HANDLE_T                h_app);

static INT32 _mmp_main_app_exit_fct(
        HANDLE_T                h_app,
        APP_EXIT_MODE_T         e_exit_mode);

static INT32 _mmp_main_app_pause_fct(
        HANDLE_T                h_app);

static INT32 _mmp_main_app_resume_fct(
        HANDLE_T                h_app);

static INT32 _mmp_main_app_process_msg_fct(
        HANDLE_T                h_app,
        UINT32                  ui4_type,
        const VOID*             pv_msg,
        SIZE_T                  z_msg_len,
        BOOL                    b_paused);

static BOOL _mmp_main_app_system_key_fct(
        UINT32                  ui4_evt_code);

static BOOL _mmp_main_chk_resume(VOID);
static BOOL _mmp_main_app_pre_resume_fct (VOID);

static INT32 _mmp_main_init_ts_inst(VOID);

static VOID _mmp_main_deinit_ts_inst(VOID);

static INT32 _mmp_main_ts_set_app_status(
        MMP_MAIN_AP_STATUS_T    e_status);

static MMP_MAIN_AP_STATUS_T _mmp_main_ts_get_app_status(VOID);

static INT32 _mmp_main_init_working_resource(
        MMP_MAIN_APP_INST_T*    pt_this,
        BOOL                    b_stop_tv);

static INT32 _mmp_main_deinit_working_resource(
        MMP_MAIN_APP_INST_T*    pt_this);

static INT32 _mmp_main_register_wm(
        MMP_MAIN_APP_INST_T*    pt_this);

static INT32 _mmp_main_init_svctx(
        MMP_MAIN_APP_INST_T*    pt_this);

static VOID _mmp_main_deinit_svctx(
        MMP_MAIN_APP_INST_T*    pt_this);

static INT32 _mmp_main_init_canvas(
        MMP_MAIN_APP_INST_T*    pt_this);

static INT32 _mmp_main_init_svl(
        MMP_MAIN_APP_INST_T*    pt_this);

static VOID _mmp_main_deinit_svl(
        MMP_MAIN_APP_INST_T*    pt_this);

static INT32 _mmp_main_register_nfy(
        MMP_MAIN_APP_INST_T*    pt_this);

static VOID _mmp_main_unregister_nfy(
        MMP_MAIN_APP_INST_T*    pt_this);

static INT32 _mmp_main_widget_cb(
        UINT32                  ui4_msg,
        VOID*                   pv_param1,
        VOID*                   pv_param2);

static VOID _mmp_main_widget_event_handler(
        VOID*                   pv_ui4_msg,
        VOID*                   pv_param1,
        VOID*                   pv_param2,
        VOID*                   pv_unused);

static VOID _mmp_main_gui_lang_nfy_cb(
        UINT16                  ui2_nfy_id,
        VOID*                   pv_tag,
        UINT16                  ui2_id);

static VOID _mmp_main_gui_lang_event_handler(
        VOID*                   pv_ui2_nfy_id,
        VOID*                   pv_unused1,
        VOID*                   pv_unused2,
        VOID*                   pv_unused3);

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
static VOID _mmp_main_dmr_show_event_handler(
        VOID*                   pv_dmr_cmd,
        VOID*                   pv_unused1,
        VOID*                   pv_unused2,
        VOID*                   pv_unused3);
#endif

static INT32 _mmp_main_free_video_resource(
    MMP_MAIN_APP_INST_T*        pt_this);

static INT32 _mmp_send_msg(
    HANDLE_T                    h_app,
    UINT32                      ui4_type,
    VOID*                       pv_msg,
    SIZE_T                      z_msg_size,
    MMP_MC_CSC_RETRY_TYPE_T     e_retry_type);

static VOID _mmp_main_req_working_res_handler(
        VOID*                   pv_b_init,
        VOID*                   pv_unused1,
        VOID*                   pv_unused2,
        VOID*                   pv_unused3);

static INT32 _mmp_main_update_blue_mute(
        MMP_MAIN_APP_INST_T*    pt_this,
        _MMP_MAIN_BM_OPTION_T   e_option);

static INT32 _mmp_main_update_gamma(
        MMP_MAIN_APP_INST_T*        pt_this,
        _MMP_MAIN_GAMMA_OPTION_T    e_option);

static INT32 _mmp_main_update_canvas_setting(
        MMP_MAIN_APP_INST_T*        pt_this,
        BOOL                        b_resume);


/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: a_mmp_init
 *
 * Description: This API performs the registration for the EPG application.
 *
 * Inputs:  pt_reg       References the registration structure.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

VOID a_mmp_init(AMB_REGISTER_INFO_T*  pt_reg)
{
    APP_DESC_T  t_desc = {
                    ~((UINT64)0),                       /* ui8_flags */
                    {
                        _MMP_MAIN_RC_STACK_SIZE,        /* z_stack_size */
                        200,                            /* ui1_priority */
                        _MMP_MAIN_RC_MAX_MSGS           /* ui2_num_msgs */
                    },
                    0,                                  /* ui4_app_group_id */
                    0,                                  /* ui4_app_id */
                    {
                        _MMP_MAIN_RC_MEM_MIN_SIZE,      /* z_min_memory */
                        _MMP_MAIN_RC_MEM_MAX_SIZE,      /* z_max_memory */
                        _MMP_MAIN_RC_FILE_MAX_SIZE,     /* ui8_max_files_size */
                        _MMP_MAIN_RC_MAX_FILES,         /* ui2_max_files */
                        _MMP_MAIN_RC_MAX_HANDLES,       /* ui2_max_handles */
                        2,                              /* ui2_max_threads */
                        _MMP_MAIN_RC_MAX_SEMAS,         /* ui2_max_semaphores */
                        1,                              /* ui2_max_msg_queues */
                        _MMP_MAIN_RC_MAX_MSGS,          /* ui2_max_nb_msgs */
                        _MMP_MAIN_RC_MSG_MAX_SIZE       /* ui2_max_msg_size */
                    },
                    _MMP_MAIN_RC_MAX_MSGS,              /* ui2_msg_count */
                    _MMP_MAIN_RC_MSG_MAX_SIZE           /* ui2_max_msg_size */
                };

    /* fill registration information */
    c_strcpy(pt_reg->s_name, MMP_NAME);
    pt_reg->s_name[APP_NAME_MAX_LEN] = '\0';

    /* lifecycle callback functions */
    pt_reg->t_fct_tbl.pf_init        = _mmp_main_app_init_fct;
    pt_reg->t_fct_tbl.pf_exit        = _mmp_main_app_exit_fct;
    pt_reg->t_fct_tbl.pf_pause       = _mmp_main_app_pause_fct;
    pt_reg->t_fct_tbl.pf_resume      = _mmp_main_app_resume_fct;
    pt_reg->t_fct_tbl.pf_process_msg = _mmp_main_app_process_msg_fct;
    pt_reg->pf_system_key_cb         = _mmp_main_app_system_key_fct;

    /* application descriptor */
    pt_reg->t_desc                   = t_desc;

    /* system keys */
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
    pt_reg->at_system_keys[0].ui4_key_code  = 0;
    pt_reg->at_system_keys[0].ui2_state_num = 0;
    pt_reg->ui2_key_num                     = 0;
#else
    pt_reg->at_system_keys[0].ui4_key_code  = MMP_RC_MEDIA_KEY;
    pt_reg->at_system_keys[0].ui2_state_num = 2;
    pt_reg->ui2_key_num                     = 1;
#endif

	/* Pre-resume callback. */
	pt_reg->pf_pre_resume_cb				= _mmp_main_app_pre_resume_fct;

}

/*----------------------------------------------------------------------------
 * Name: mmp_main_get_ap_status
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
MMP_MAIN_AP_STATUS_T mmp_main_get_ap_status(VOID)
{
    return _mmp_main_ts_get_app_status();
}

/*----------------------------------------------------------------------------
 * Name: mmp_main_set_ap_status
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 mmp_main_set_ap_status(MMP_MAIN_AP_STATUS_T e_status)
{
    return _mmp_main_ts_set_app_status(e_status);
}

/*----------------------------------------------------------------------------
 * Name: mmp_main_is_ap_resumed_status
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
BOOL mmp_main_is_ap_resumed_status(VOID)
{
    MMP_MAIN_AP_STATUS_T e_status = _mmp_main_ts_get_app_status();

#ifdef APP_MENU_MMP_COEXIST
    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == e_status)
    {
        return TRUE;
    }
#endif

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    return (MMP_MAIN_AP_STATUS_RESUMED == e_status           ||
            MMP_MAIN_AP_STATUS_RESUMED_PHOTO_FRM == e_status ||
            MMP_MAIN_AP_STATUS_RESUMED_DMR == e_status) ? TRUE : FALSE;
#else
    return (MMP_MAIN_AP_STATUS_RESUMED == e_status || MMP_MAIN_AP_STATUS_RESUMED_PHOTO_FRM == e_status) ? TRUE : FALSE;
#endif
}

/*----------------------------------------------------------------------------
 * Name: mmp_mc_event_switch_context
 *
 * Description: This API performs the registration for the EPG application.
 *
 * Inputs:  pt_reg       References the registration structure.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 mmp_mc_event_switch_context(
    MMP_MC_CSC_RETRY_TYPE_T     e_retry_type,
    mmp_mc_event_handler        pf_event_handler,
    VOID*                       pv_param1,
    VOID*                       pv_param2,
    VOID*                       pv_param3,
    VOID*                       pv_param4)
{
    return mmp_mc_event_switch_context_ex(e_retry_type, pf_event_handler, pv_param1, pv_param2, pv_param3, pv_param4, TRUE);
}

/*----------------------------------------------------------------------------
 * Name: mmp_mc_event_switch_context_ex
 *
 * Description: This API performs the registration for the EPG application.
 *
 * Inputs:  pt_reg       References the registration structure.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 mmp_mc_event_switch_context_ex(
    MMP_MC_CSC_RETRY_TYPE_T     e_retry_type,
    mmp_mc_event_handler        pf_event_handler,
    VOID*                       pv_param1,
    VOID*                       pv_param2,
    VOID*                       pv_param3,
    VOID*                       pv_param4,
    BOOL                        b_chk_res)
{
    MMP_MAIN_MSG_SWTH_CTX_T     t_swth_msg;

    if(b_chk_res && FALSE == t_g_app_inst.b_is_working_res_ready)
    {
        MMP_DBG_ERROR(("Working resource is not ready.\r\n"));
        return MMPR_FAIL;
    }

    if(NULL == pf_event_handler)
    {
        MMP_DBG_ERROR(("pf_event_handler cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }

    t_swth_msg.pf_event_handler = pf_event_handler;
    t_swth_msg.pv_param1 = pv_param1;
    t_swth_msg.pv_param2 = pv_param2;
    t_swth_msg.pv_param3 = pv_param3;
    t_swth_msg.pv_param4 = pv_param4;

    if (b_chk_res)
    {
        return _mmp_send_msg(t_g_app_inst.h_app, MMP_MSG_TYPE_SWTH_CTX, &t_swth_msg, sizeof(MMP_MAIN_MSG_SWTH_CTX_T), e_retry_type);
    }
    else
    {
        return _mmp_send_msg(t_g_app_inst.h_app, MMP_MSG_TYPE_SWTH_CTX_WO_RES_CHK, &t_swth_msg, sizeof(MMP_MAIN_MSG_SWTH_CTX_T), e_retry_type);
    }
}

/*----------------------------------------------------------------------------
 * Name: mmp_main_get_canvas
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
HANDLE_T mmp_main_get_canvas(VOID)
{
    return t_g_app_inst.h_canvas;
}
HANDLE_T mmp_main_get_sbtl_canvas(VOID)
{
    return t_g_app_inst.h_sbtl_canvas;
}

/*----------------------------------------------------------------------------
 * Name: mmp_main_get_transparent_lst
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
HANDLE_T mmp_main_get_transparent_lst(VOID)
{
    return t_g_app_inst.h_transparent_lst;
}

/*----------------------------------------------------------------------------
 * Name: a_mmp_init_working_resource
 *
 * Description: This API perform resource initiation when mmp is started
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_mmp_init_working_resource(VOID)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;
    MMP_MAIN_MSG_SWTH_CTX_T     t_swth_msg;
    INT32                       i4_ret;

    if (pt_this->h_app == NULL_HANDLE)
    {
        return MMPR_FAIL;
    }

    t_swth_msg.pf_event_handler = _mmp_main_req_working_res_handler;
    t_swth_msg.pv_param1 = (VOID*)(UINT32)TRUE;
    t_swth_msg.pv_param2 = NULL;
    t_swth_msg.pv_param3 = NULL;
    t_swth_msg.pv_param4 = NULL;
    i4_ret = _mmp_send_msg(pt_this->h_app, MMP_MSG_TYPE_SWTH_CTX_WO_RES_CHK, &t_swth_msg, sizeof(MMP_MAIN_MSG_SWTH_CTX_T), MMP_MC_CSC_RETRY_TYPE_CRITICAL);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /*wait result*/
    i4_ret = c_sema_lock(pt_this->h_ready_signal, X_SEMA_OPTION_WAIT);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_sema_lock() failed. i4_ret = %d.\r\n", i4_ret));
        return MMPR_INTERNAL_ERROR;
    }

    return pt_this->b_is_working_res_ready ? MMPR_OK : MMPR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: a_mmp_deinit_working_resource
 *
 * Description: This API perform resource de-initiation when mmp is started
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_mmp_deinit_working_resource(VOID)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;
    MMP_MAIN_MSG_SWTH_CTX_T     t_swth_msg;
    INT32                       i4_ret;

    if (pt_this->h_app == NULL_HANDLE)
    {
        return MMPR_FAIL;
    }

    t_swth_msg.pf_event_handler = _mmp_main_req_working_res_handler;
    t_swth_msg.pv_param1 = (VOID*)(UINT32)FALSE;
    t_swth_msg.pv_param2 = NULL;
    t_swth_msg.pv_param3 = NULL;
    t_swth_msg.pv_param4 = NULL;
    i4_ret = _mmp_send_msg(pt_this->h_app, MMP_MSG_TYPE_SWTH_CTX_WO_RES_CHK, &t_swth_msg, sizeof(MMP_MAIN_MSG_SWTH_CTX_T), MMP_MC_CSC_RETRY_TYPE_CRITICAL);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /*wait result*/
    i4_ret = c_sema_lock(pt_this->h_ready_signal, X_SEMA_OPTION_WAIT);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_sema_lock() failed. i4_ret = %d.\r\n", i4_ret));
        return MMPR_INTERNAL_ERROR;
    }

    return pt_this->b_is_working_res_ready ? MMPR_FAIL : MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_mmp_request_operation
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_mmp_request_operation(MMP_REQ_OP_T e_req_op)
{
    MMP_MAIN_AP_STATUS_T        e_status = _mmp_main_ts_get_app_status();
    UINT8                       ui1_req_op = ICL_RECID_MMP_REQ_OP_NONE;

    switch (e_req_op)
    {
        case MMP_REQ_OP_START_PHOTO_FRM:
        case MMP_REQ_OP_ENTER_PHOTO_BWR:
        case MMP_REQ_OP_ENTER_AUDIO_BWR:
        case MMP_REQ_OP_ENTER_VIDEO_BWR:
        {
            if ((MMP_MAIN_AP_STATUS_PAUSED   != e_status) &&
                (MMP_MAIN_AP_STATUS_DEINITED != e_status))
            {
                return MMPR_NOT_SUPPORT;
            }

            if (MMP_REQ_OP_START_PHOTO_FRM == e_req_op)
            {
                ui1_req_op = ICL_RECID_MMP_REQ_OP_START_PHOTO_FRM;
            }
            else if (MMP_REQ_OP_ENTER_PHOTO_BWR == e_req_op)
            {
                ui1_req_op = ICL_RECID_MMP_REQ_OP_ENTER_PHOTO_BWR;
            }
            else if (MMP_REQ_OP_ENTER_AUDIO_BWR == e_req_op)
            {
                ui1_req_op = ICL_RECID_MMP_REQ_OP_ENTER_AUDIO_BWR;
            }
            else
            {
                ui1_req_op = ICL_RECID_MMP_REQ_OP_ENTER_VIDEO_BWR;
            }

            a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_REQUEST_OP),
                      &ui1_req_op,
                      ICL_RECID_MMP_REQUEST_OP_SIZE);

#ifdef LINUX_TURNKEY_SOLUTION
            a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=mmp\n");
#else
            a_amb_resume_app(MMP_NAME);
#endif
        }
        break;

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
        case MMP_REQ_OP_DMR_START:
        {
            if ((MMP_MAIN_AP_STATUS_PAUSED   == e_status) ||
                (MMP_MAIN_AP_STATUS_PAUSING  == e_status) ||
                (MMP_MAIN_AP_STATUS_DEINITED == e_status))
            {
                 DBG_LOG_PRINT(("<MMP> a_mmp_request_operation a_amb_resume_app MMP_NAME  %s:%d \r\n", __FILE__, __LINE__));
                ui1_req_op = ICL_RECID_MMP_REQ_OP_ENTER_DMR;
                a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_REQUEST_OP),
                          &ui1_req_op,
                          ICL_RECID_MMP_REQUEST_OP_SIZE);

#ifdef LINUX_TURNKEY_SOLUTION
                a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=mmp\n");
#else
                a_amb_resume_app(MMP_NAME);
#endif
            }
            else if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == e_status)
            {
                a_amb_sync_resume_app(MMP_NAME);

                mmp_mc_event_switch_context(
                            MMP_MC_CSC_RETRY_TYPE_NORMAL,
                            _mmp_main_dmr_show_event_handler,
                            (VOID*)(UINT32)MMP_FP_SHOW_CMD_ID_START,
                            NULL, NULL, NULL
                            );
            }
            else
            {
                 DBG_LOG_PRINT(("<MMP> a_mmp_request_operation already in MMP  %s:%d \r\n", __FILE__, __LINE__));
                _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_RESUMED_DMR);

                mmp_mc_event_switch_context(
                            MMP_MC_CSC_RETRY_TYPE_NORMAL,
                            _mmp_main_dmr_show_event_handler,
                            (VOID*)(UINT32)MMP_FP_SHOW_CMD_ID_START,
                            NULL, NULL, NULL
                            );
            }
        }
        break;

        case MMP_REQ_OP_DMR_PAUSE:
        {
            mmp_mc_event_switch_context(
                        MMP_MC_CSC_RETRY_TYPE_NORMAL,
                        _mmp_main_dmr_show_event_handler,
                        (VOID*)(UINT32)MMP_FP_SHOW_CMD_ID_PAUSE,
                        NULL, NULL, NULL
                        );
        }
        break;

        case MMP_REQ_OP_DMR_RESUME:
        {
            mmp_mc_event_switch_context(
                        MMP_MC_CSC_RETRY_TYPE_NORMAL,
                        _mmp_main_dmr_show_event_handler,
                        (VOID*)(UINT32)MMP_FP_SHOW_CMD_ID_RESUME,
                        NULL, NULL, NULL
                        );
        }
        break;

        case MMP_REQ_OP_DMR_STOP:
        {
            mmp_mc_event_switch_context(
                        MMP_MC_CSC_RETRY_TYPE_NORMAL,
                        _mmp_main_dmr_show_event_handler,
                        (VOID*)(UINT32)MMP_FP_SHOW_CMD_ID_STOP,
                        NULL, NULL, NULL
                        );
        }
        break;
#endif

        default:
            break;
    }


    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_mmp_get_ap_status
 *
 * Description: This API is used to get mmp status by other ap modules.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
MMP_MAIN_AP_STATUS_T a_mmp_get_ap_status(VOID)
{
    return _mmp_main_ts_get_app_status();
}
#ifdef APP_MENU_MMP_COEXIST
/*----------------------------------------------------------------------------
 * Name: a_mmp_send_sync_msg
 *
 * Description: This API is used to send a msg by other ap modules.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID       a_mmp_send_sync_msg(MMP_EXT_MSG_T e_msg)
{
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_EXTERN_MSG,(VOID*)e_msg);;
}

#ifdef APP_3D_PHOTO_SUPPORT

BOOL a_mmp_get_3d_mode_disable(VOID)
{
	return _mmp_pe_get_3D_mode_disable();
}
#endif
#endif
/*-----------------------------------------------------------------------------
 * private VIEW methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _mmp_main_app_init_fct
 *
 * Description: This function is called in the context of the application
 *              when the application starts.
 *
 * Inputs:  ps_name             References the application's name.
 *          h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_main_app_init_fct(
    const CHAR*                 ps_name,
    HANDLE_T                    h_app)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;

    /*check app handle*/
    if(NULL_HANDLE == h_app)
    {
        return AEER_FAIL;
    }

    /*init app thread-safe instance*/
    i4_ret = _mmp_main_init_ts_inst();
    if(MMPR_OK != i4_ret)
    {
        return AEER_FAIL;
    }

    /*update ap status*/
    i4_ret = _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_INITING);
    if(MMPR_OK != i4_ret)
    {
        return AEER_FAIL;
    }

    /*init member*/

    /*register to widget manager*/
    i4_ret = _mmp_main_register_wm(pt_this);
    if(MMPR_OK != i4_ret)
    {
        return AEER_FAIL;
    }

    /*init widget canvas*/
    i4_ret = _mmp_main_init_canvas(pt_this);
    if(MMPR_OK != i4_ret)
    {
        return AEER_FAIL;
    }

    i4_ret = _mmp_main_init_working_resource(pt_this, FALSE);
    if(MMPR_OK != i4_ret)
    {
        return AEER_FAIL;
    }

    /*create a semaphore for protection*/
    i4_ret = c_sema_create(&pt_this->h_ready_signal, X_SEMA_TYPE_BINARY, X_SEMA_STATE_LOCK);
    if(OSR_OK != i4_ret)
    {
        pt_this->h_ready_signal = NULL_HANDLE;
        return AEER_FAIL;
    }

    pt_this->h_app = h_app;

    /*update ap status*/
    i4_ret = _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_PAUSED);
    if(MMPR_OK != i4_ret)
    {
        return AEER_FAIL;
    }

    /*Transparent list*/
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

    i4_ret = c_wgl_create_transparent_list(mmp_main_get_canvas(),
                                           &t_rect,
                                           1,
                                           &pt_this->h_transparent_lst);
    if (WGLR_OK != i4_ret)
    {
       return AEER_FAIL;
    }

    c_wgl_enable_transparent_list(pt_this->h_transparent_lst, FALSE, FALSE);

    pt_this->ui4_activation_key = BTN_INVALID;

    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_main_app_exit_fct
 *
 * Description: This function is called in the context of the application
 *              when the application quits. This API should be
 *              responsible for saving data, clean-up, etc.
 *
 * Inputs:  h_app               Contains the application handle.
 *          e_exit_mode         Contains the exit mode.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_main_app_exit_fct(
    HANDLE_T                    h_app,
    APP_EXIT_MODE_T             e_exit_mode)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;
    INT32                       i4_ret = MMPR_OK;

    /*update ap status*/
    _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_DEINITING);

    _mmp_main_deinit_working_resource(pt_this);

    /*free semaphore for protection*/
    if(NULL_HANDLE != pt_this->h_ready_signal)
    {
        MMP_EXEC_WITH_ASSERT(c_sema_delete(pt_this->h_ready_signal), OSR_OK);

        pt_this->h_ready_signal = NULL_HANDLE;
    }

    pt_this->h_canvas = NULL_HANDLE;
    pt_this->h_app = NULL_HANDLE;

    i4_ret = c_wgl_delete_transparent_list(pt_this->h_transparent_lst);
    if(MMPR_OK!= i4_ret)
    {
        MMP_DBG_ERROR((" c_wgl_delete_transparent_list() fail. i4_ret = %d.\r\n", i4_ret));
    }

    /*update ap status*/
    _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_DEINITED);

    /*free app threadsafe instance*/
    _mmp_main_deinit_ts_inst();

    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_main_app_pause_fct
 *
 * Description: This function is called in the context of the application
                when the application is paused.
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_main_app_pause_fct(
    HANDLE_T                    h_app)
{
    UINT8                       ui1_icl_status;
    INT32                       i4_ret;

#ifdef APP_MENU_MMP_COEXIST
    CHAR                        s_app_name[APP_NAME_MAX_LEN] = {0};

     DBG_LOG_PRINT(("<app_main>: _mmp_main_app_pause_fct begin !!\r\n"));
    if (MMP_MAIN_RC_CHECK_MENU_MMP_COEXIST_COND())
    {
        i4_ret = a_am_get_next_active_app (s_app_name);
        if ((AMR_OK == i4_ret) && (0 == c_strcmp (s_app_name, MENU_NAME)))
        {
            _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC);
            return AEER_OK;
        }
    }
#endif

    /*update ap status*/
    i4_ret = _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_PAUSING);
    if(MMPR_OK != i4_ret)
    {
        return AEER_FAIL;
    }

    /**/
    mmp_main_rc_pre_pause();

    /*turn off RESUMED flag before broadcast MMP_MSG_ID_APP_PAUSED message*/
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_APP_PAUSED, NULL);

    //if (a_am_is_power_on())    /* pause fct power on flag == false fix DTV00783226 */
    {
    #ifdef APP_3D_PHOTO_SUPPORT
        /* photo exit release res ,set source off ,before select source ,fix DTV00861046*/
        mmp_drc_switch_mode(MMP_DRC_MODE_FREE);
    #endif
        mmp_main_restore_video_resource();
    }

    /**/
    mmp_main_rc_post_pause();

    _mmp_main_update_canvas_setting(&t_g_app_inst, FALSE);

#ifndef APP_MMP_PAUSE_KEEP_RESOURCE /*#ifdef APP_MMP_PAUSE_FREE_RESOURCE*/
    _mmp_main_deinit_working_resource(&t_g_app_inst);
#endif

    /*Set media play status*/
    ui1_icl_status = ICL_MMP_MEDIA_PLAY_STATUS_OFF;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_MEDIA_PLAY_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_MMP_MEDIA_PLAY_STATUS_SIZE);

    /*update ap status*/
    i4_ret = _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_PAUSED);
    if(MMPR_OK != i4_ret)
    {
        return AEER_FAIL;
    }

    /* Set icl status */
#if (!defined(APP_VTRL_INP_SRC_MMP_SUPPORT) && !defined(APP_MMP_ENABLE_SCART_AUTO_SWITCH))
    ui1_icl_status = ICL_SCART_EXCL_AP_STATUS_PAUSE;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_SCART_EXCL_AP, ICL_RECID_SCART_EXCL_AP_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_SCART_EXCL_AP_STATUS_SIZE);
#endif

    c_wgl_img_cache_flush();

#ifdef APP_CAST_TV_MMP_FG
    /*Clean request OP type*/
    ui1_icl_status = ICL_RECID_MMP_REQ_OP_NONE;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_REQUEST_OP),
              (VOID*) &ui1_icl_status,
              ICL_RECID_MMP_REQUEST_OP_SIZE);
#endif

     DBG_LOG_PRINT(("<app_main>: _mmp_main_app_pause_fct end !!\r\n"));
    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_main_app_resume_fct
 *
 * Description: This function is called in the context of the application
 *              when the application is resumed.
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_main_app_resume_fct(
    HANDLE_T                    h_app)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;
    UINT8                       ui1_icl_status;
    INT32                       i4_ret;
    MMP_APP_RESUME_INFO_T       e_resume_info = MMP_APP_RESUME_INFO_NONE;
    MMP_MAIN_AP_STATUS_T        e_resume_status = MMP_MAIN_AP_STATUS_RESUMED;
    SIZE_T                      z_size = ICL_RECID_MMP_REQUEST_OP_SIZE;

     DBG_LOG_PRINT(("<app_main>: _mmp_main_app_resume_fct begin !!\r\n"));
#ifdef APP_MENU_MMP_COEXIST
    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == _mmp_main_ts_get_app_status())
    {
    #if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
        if (a_mmp_dmr_is_active())
        {
            _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_RESUMED_DMR);
        }
        else
        {
            _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_RESUMED);

        //#ifdef APP_MMP_RC_PAUSED_WAIT_SVC
            mmp_main_rc_paused_wait_svc();
        //#endif
        }
    #else
        _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_RESUMED);

    //#ifdef APP_MMP_RC_PAUSED_WAIT_SVC
        mmp_main_rc_paused_wait_svc();
    //#endif
    #endif

        if (BTN_INVALID != pt_this->ui4_activation_key)
        {
            mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                        _mmp_main_widget_event_handler,
                                        (VOID*)WGL_MSG_KEY_DOWN,
                                        (VOID*)pt_this->ui4_activation_key,
                                        (VOID*)c_os_get_sys_tick(),
                                        NULL);

            pt_this->ui4_activation_key = BTN_INVALID;
        }

        return AEER_OK;
    }
#endif

    /*Check request OP type*/
    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_REQUEST_OP),
                       &ui1_icl_status,
                       &z_size);
    if(i4_ret != ICLR_OK)
    {
        ui1_icl_status = ICL_RECID_MMP_REQ_OP_NONE;
    }

#ifndef MMP_MAIN_RC_REQUEST_OP_REMAPPING
    switch (ui1_icl_status)
    {
        case ICL_RECID_MMP_REQ_OP_START_PHOTO_FRM:
            e_resume_info = MMP_APP_RESUME_INFO_PHOTO_FRM;
            e_resume_status = MMP_MAIN_AP_STATUS_RESUMED_PHOTO_FRM;
            break;
        case ICL_RECID_MMP_REQ_OP_ENTER_PHOTO_BWR:
            e_resume_info = MMP_APP_RESUME_INFO_PHOTO_BWR;
            e_resume_status = MMP_MAIN_AP_STATUS_RESUMED;
            break;
        case ICL_RECID_MMP_REQ_OP_ENTER_AUDIO_BWR:
            e_resume_info = MMP_APP_RESUME_INFO_AUDIO_BWR;
            e_resume_status = MMP_MAIN_AP_STATUS_RESUMED;
            break;
        case ICL_RECID_MMP_REQ_OP_ENTER_VIDEO_BWR:
            e_resume_info = MMP_APP_RESUME_INFO_VIDEO_BWR;
            e_resume_status = MMP_MAIN_AP_STATUS_RESUMED;
            break;
        case ICL_RECID_MMP_REQ_OP_ENTER_TEXT_BWR:
            e_resume_info = MMP_APP_RESUME_INFO_TEXT_BWR;
            e_resume_status = MMP_MAIN_AP_STATUS_RESUMED;
            break;
#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
        case ICL_RECID_MMP_REQ_OP_ENTER_DMR:
            e_resume_info = MMP_APP_RESUME_INFO_DMR;
            e_resume_status = MMP_MAIN_AP_STATUS_RESUMED_DMR;
            break;
#endif
        default:
            break;
    }
#else
    MMP_MAIN_RC_REQUEST_OP_REMAPPING(ui1_icl_status, e_resume_info, e_resume_status);
#endif

    /*update ap status*/
    i4_ret = _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_RESUMING);
    if(MMPR_OK != i4_ret)
    {
         DBG_LOG_PRINT(("<app_main>: _mmp_main_ts_set_app_status failed. i4_ret = %d. line(%d) \r\n", i4_ret, __LINE__));
        return AEER_FAIL;
    }

    /**/
    i4_ret = _mmp_main_init_working_resource(pt_this, TRUE);
    if(MMPR_OK != i4_ret && MMPR_ALREADY_INIT != i4_ret)
    {
        DBG_LOG_PRINT(("<app_main>: _mmp_main_init_working_resource() failed. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
        return AEER_FAIL;
    }

    /**/
    mmp_main_rc_pre_resume();
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_APP_PRE_RESUMED, (VOID*)e_resume_info);

#ifndef APP_CAST_TV_MMP
    if(MMPR_ALREADY_INIT == i4_ret)
    {
        i4_ret = _mmp_main_free_video_resource(pt_this);
        if(MMPR_OK != i4_ret)
        {
             DBG_LOG_PRINT(("<app_main>: _mmp_main_free_video_resource() failed. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return AEER_FAIL;
        }
    }
#endif

    _mmp_main_update_canvas_setting(pt_this, TRUE);

    /*update ap status*/
    i4_ret = _mmp_main_ts_set_app_status(e_resume_status);
    if(MMPR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("<app_main>: _mmp_main_ts_set_app_status() failed. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
        return AEER_FAIL;
    }

    /*turn on RESUMED flag before broadcast MMP_MSG_ID_APP_RESUMED message*/
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_APP_RESUMED, (VOID*)e_resume_info);

    /**/
    mmp_main_rc_post_resume();

    /* Set icl status */
#if (!defined(APP_VTRL_INP_SRC_MMP_SUPPORT) && !defined(APP_MMP_ENABLE_SCART_AUTO_SWITCH))
    ui1_icl_status = ICL_SCART_EXCL_AP_STATUS_RESUME;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_SCART_EXCL_AP, ICL_RECID_SCART_EXCL_AP_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_SCART_EXCL_AP_STATUS_SIZE);
#endif

    ui1_icl_status = ICL_MMP_MEDIA_PLAY_STATUS_ON;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_MEDIA_PLAY_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_MMP_MEDIA_PLAY_STATUS_SIZE);

#ifndef MMP_MEMORIZE_LAST_REQ_OP
    /*Clean request OP type*/
    ui1_icl_status = ICL_RECID_MMP_REQ_OP_NONE;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_REQUEST_OP),
              (VOID*) &ui1_icl_status,
              ICL_RECID_MMP_REQUEST_OP_SIZE);
#endif

    pt_this->ui4_last_rece_key_tick = c_os_get_sys_tick();
    pt_this->ui4_last_handle_key_tick = c_os_get_sys_tick();

     DBG_LOG_PRINT(("<app_main>: _mmp_main_app_resume_fct end \r\n"));
    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_main_app_process_msg_fct
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
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_main_app_process_msg_fct(
    HANDLE_T                    h_app,
    UINT32                      ui4_type,
    const VOID*                 pv_msg,
    SIZE_T                      z_msg_len,
    BOOL                        b_paused)
{
    MMP_MAIN_APP_INST_T*        pt_this;

    if(NULL_HANDLE == h_app || NULL == pv_msg)
    {
        return AEER_FAIL;
    }

    pt_this = &t_g_app_inst;

    switch(ui4_type)
    {
    case MMP_MSG_TYPE_SWTH_CTX:
        {
            MMP_MAIN_MSG_SWTH_CTX_T*    pt_msg = (MMP_MAIN_MSG_SWTH_CTX_T*)pv_msg;

            MMP_ASSERT(z_msg_len == sizeof(MMP_MAIN_MSG_SWTH_CTX_T));

            /*invoke command handler*/
            if(pt_msg->pf_event_handler && pt_this->b_is_working_res_ready)
            {
                pt_msg->pf_event_handler(pt_msg->pv_param1,
                                         pt_msg->pv_param2,
                                         pt_msg->pv_param3,
                                         pt_msg->pv_param4);
            }
        }
        break;

    case MMP_MSG_TYPE_SWTH_CTX_WO_RES_CHK:
        {
            MMP_MAIN_MSG_SWTH_CTX_T*    pt_msg = (MMP_MAIN_MSG_SWTH_CTX_T*)pv_msg;

            MMP_ASSERT(z_msg_len == sizeof(MMP_MAIN_MSG_SWTH_CTX_T));

            /*invoke command handler*/
            if(pt_msg->pf_event_handler)
            {
                pt_msg->pf_event_handler(pt_msg->pv_param1,
                                         pt_msg->pv_param2,
                                         pt_msg->pv_param3,
                                         pt_msg->pv_param4);
            }
        }
        break;

    case AM_BRDCST_MSG_PRE_POWER_OFF:
        {
            mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_PRE_POWER_OFF, NULL);

        #ifdef APP_CAST_TV_MMP_FG
            SIZE_T z_size = ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE;
            INT32  i4_ret = MMPR_OK;
            UINT32 ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_USER;

            MMP_MAIN_AP_STATUS_T    e_ap_status = a_mmp_get_ap_status();
            MMP_DBG_INFO(("<mmp> inp to cast %s,%d,status:%d\n\r",__FILE__,__LINE__,e_ap_status));

            i4_ret = a_icl_set(ICL_MAKE_ID (ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_EXIT_REASON),
                                   (VOID*) &ui4_exit_reason, z_size);
            if(MMPR_OK != i4_ret)
            {
                 MMP_DBG_ERROR(("a_icl_set() fail. i4_ret = %d.\r\n", i4_ret));
            }

        #ifdef APP_MENU_MMP_COEXIST
            if ((MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == e_ap_status)
                || (MMP_MAIN_AP_STATUS_RESUMED == e_ap_status)
                || (MMP_MAIN_AP_STATUS_RESUMING == e_ap_status))
        #else
            if ((MMP_MAIN_AP_STATUS_RESUMED == e_ap_status)
                || (MMP_MAIN_AP_STATUS_RESUMING == e_ap_status))
        #endif
            {
                mmp_foreground_chg_inp_src_to_cast();
            }
        #endif
        }
        break;

    case AM_BRDCST_MSG_POWER_OFF:
        {
        #ifdef APP_MENU_MMP_COEXIST
        #if defined(APP_SUPPORT_STR_CORE_OFF)
            if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
            {
                a_mmp_pause_background_mmp();
            }
            else
            {
                mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_POWER_OFF, NULL);
            }
        #endif
        #else
             mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_POWER_OFF, NULL);
        #endif
        }
        break;

#ifdef APP_MENU_MMP_COEXIST
    case AM_BRDCST_MSG_APP_PAUSED_IN_SYNC:
        {
            INT32                   i4_ret;
            CHAR                    s_app_name[APP_NAME_MAX_LEN];
            MMP_MAIN_AP_STATUS_T    t_app_status;

            t_app_status = _mmp_main_ts_get_app_status();

            /* Do nothing if MMP OSD is not displayed. */
            if (MMP_MAIN_AP_STATUS_RESUMED         == t_app_status ||
                MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == t_app_status)
            {
                i4_ret = a_am_get_next_active_app (s_app_name);
                if (AMR_OK == i4_ret)
                {
                    /* If next AP is NAV/EPG & MMP OSD is displayed, hide MMP OSD. */
                    if ((0 == c_strcmp (s_app_name, NAV_NAME)) ||
                        (0 == c_strcmp (s_app_name, EPG_NAME)))
                    {
                        _mmp_main_app_pause_fct (h_app);
                    }
                }
            }
        }
        break;
#endif

#ifdef APP_CAST_TV_MMP_FG
    case MMP_MSG_EXTERNAL_REQ_INSET_USB:
        {
            MMP_DBG_INFO(("<MMP> inset usb %s,%d\n\r",__FILE__,__LINE__));
            mmp_foreground_view_repaint();
        }
        break;
#endif

    default:
        return AEER_OK;
    }

    return AEER_OK;
}

/*----------------------------------------------------------------------------
 * Name
 *      _mmp_main_app_system_key_fct
 * Description
 *      The API is used to override the default RCU key handler. If pf_handler
 *      is NULL, it will change to use system default key handler.
 * Input arguments
 *      pf_handler      the key handler
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK
 *      NAVR_FAIL
 *----------------------------------------------------------------------------*/
static BOOL _mmp_main_app_system_key_fct(
    UINT32     ui4_evt_code)
{
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
    UINT32 ui4_key_code = IOM_GET_EVT_GRP_ID (ui4_evt_code);
    if (ui4_key_code == BTN_MEM_CARD)
    {
        return FALSE;
    }
    else if (ui4_key_code == BTN_EPG)
    {
        return FALSE;
    }
    else if (ui4_key_code == BTN_MENU)
    {
#ifndef APP_MENU_MMP_COEXIST
        mmp_rmk_client_cancel_remote_handling(ui4_key_code);
        return FALSE;
#else
        return TRUE;
#endif
    }
    else
    {
        return TRUE;
    }
#else
    return MMP_MAIN_RC_SYSTEM_KEY_HANDLER(ui4_evt_code);
#endif
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_main_app_pre_resume_fct
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
static BOOL _mmp_main_app_pre_resume_fct (VOID)
{
    BOOL               b_resume = TRUE;
	MSG_CONVERT_SEND_CMD_T t_send_cmd;

    if(!_mmp_main_chk_resume())
    {
		b_resume = FALSE;
    }
	if(b_resume)
	{
		t_send_cmd.s_source = "browser_ctrl";
		t_send_cmd.s_destination = "browser_ctrl";
		t_send_cmd.s_ack = NULL;
		t_send_cmd.s_command = "widget_ui_show=browser_ctrl";
		t_send_cmd.s_parameter = NULL;
		a_msg_convert_send_command(&t_send_cmd);
	}

    return b_resume;
}

/*******************************************************************************
 * Name
 *          _mmp_main_chk_resume
 * Description
 * Input arguments
 *  Check if the MMP can be resumed.
 * Output arguments
 *  TRUE: The MMP can be resumed
 *  FALSE: The MMP cant not be resumed
 *
 * Returns
 ******************************************************************************/
static BOOL _mmp_main_chk_resume(VOID)
{
    INT32   i4_ret;
    SIZE_T  z_size;
    UINT32  ui4_disable_mask = 0;
    UINT8   ui1_resume_cond = ICL_RECID_MMP_RESUME_COND_OK;


    z_size = ICL_RECID_MMP_DISABLE_MASK_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_DISABLE_MASK),
                       &ui4_disable_mask,
                       &z_size);

    if(i4_ret != ICLR_OK)
    {
        ui4_disable_mask = 0;
    }
#ifndef APP_CAST_TV_MMP
    if(ICL_RECID_MMP_DISABLE_MASK_CAST_TV == ui4_disable_mask)
    {
        ui4_disable_mask = 0;
    }
#endif
    DBG_LOG_PRINT(("[%s %d] ui4_disable_mask = 0x%x\n",__FUNCTION__,__LINE__,ui4_disable_mask));
    ui1_resume_cond = (UINT8)((ui4_disable_mask == 0) ?
                              ICL_RECID_MMP_RESUME_COND_OK :
                              ICL_RECID_MMP_RESUME_COND_FAILED);

    z_size = ICL_RECID_MMP_RESUME_COND_SIZE;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_RESUME_COND),
              &ui1_resume_cond,
              z_size);

    return (ui4_disable_mask == 0);
}

/*******************************************************************************
 * Name
 *          _mmp_main_init_ts_inst
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_init_ts_inst(VOID)
{
    _MMP_MAIN_TS_INST_T*        pt_ts_this = &t_g_app_ts_inst;
    INT32                       i4_ret;

    /**/
    if(NULL_HANDLE != pt_ts_this->h_mutex && c_handle_valid(pt_ts_this->h_mutex))
    {
        return MMPR_ALREADY_INIT;
    }

    /*clean members*/
    c_memset(pt_ts_this, 0, sizeof(_MMP_MAIN_TS_INST_T));

    /*create a mutex for protection*/
    i4_ret = c_sema_create(&pt_ts_this->h_mutex, X_SEMA_TYPE_MUTEX, X_SEMA_STATE_UNLOCK);
    if(OSR_OK != i4_ret)
    {
        pt_ts_this->h_mutex = NULL_HANDLE;
        return MMPR_FAIL;
    }

    do /*for resource*/
    {
        /*lock mutex*/
        if(OSR_OK != c_sema_lock(pt_ts_this->h_mutex, X_SEMA_OPTION_WAIT))
        {
            i4_ret = MMPR_FAIL;
            break;
        }

        do /*for protected*/
        {
            pt_ts_this->e_app_status = MMP_MAIN_AP_STATUS_DEINITED;

            i4_ret = MMPR_OK;

        } while(0);

        /*unlock mutex*/
        if(OSR_OK != c_sema_unlock(pt_ts_this->h_mutex))
        {
            MMP_ASSERT(0);
            i4_ret = MMPR_FAIL;
        }

        if(MMPR_OK != i4_ret)
        {
            break;
        }

        return MMPR_OK;

    } while(0);

    _mmp_main_deinit_ts_inst();
    return i4_ret;
}

/*******************************************************************************
 * Name
 *          _mmp_main_deinit_ts_inst
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _mmp_main_deinit_ts_inst(VOID)
{
    _MMP_MAIN_TS_INST_T*        pt_ts_this = &t_g_app_ts_inst;
    HANDLE_T                    h_mutex;

    /**/
    if(OSR_OK != c_sema_lock(pt_ts_this->h_mutex, X_SEMA_OPTION_WAIT))
    {
        /*check protection mutex*/
        if(FALSE == c_handle_valid(pt_ts_this->h_mutex))
        {
            pt_ts_this->h_mutex = NULL_HANDLE;
            return;
        }
        else
        {
            MMP_ASSERT(0);
            return;
        }
    }

    /*clean members*/
    h_mutex = pt_ts_this->h_mutex;
    c_memset(pt_ts_this, 0, sizeof(_MMP_MAIN_TS_INST_T));

    /*free the protection mutex*/
    if(OSR_OK != c_sema_delete(h_mutex))
    {
        MMP_ASSERT(0);
    }
}

/*******************************************************************************
 * Name
 *          _mmp_main_ts_set_app_status
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_ts_set_app_status(
        MMP_MAIN_AP_STATUS_T    e_status)
{
    _MMP_MAIN_TS_INST_T*        pt_ts_this = &t_g_app_ts_inst;
    MMP_STAT_XNG_INFO_T         t_mmp_stat_xng = { pt_ts_this->e_app_status, e_status};

    _MMP_MAIN_TS_LOCK(pt_ts_this, return MMPR_RES_NOT_READY);
    pt_ts_this->e_app_status = e_status;
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_APP_STAT_XNG, &t_mmp_stat_xng);
    _MMP_MAIN_TS_UNLOCK(pt_ts_this, return MMPR_RES_NOT_READY);

    return MMPR_OK;
}

/*******************************************************************************
 * Name
 *          _mmp_main_ts_get_app_status
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static MMP_MAIN_AP_STATUS_T _mmp_main_ts_get_app_status(VOID)
{
    _MMP_MAIN_TS_INST_T*        pt_ts_this = &t_g_app_ts_inst;
    MMP_MAIN_AP_STATUS_T        e_status;

    _MMP_MAIN_TS_LOCK(pt_ts_this, return MMP_MAIN_AP_STATUS_DEINITED);

    e_status = pt_ts_this->e_app_status;

    _MMP_MAIN_TS_UNLOCK(pt_ts_this, return MMP_MAIN_AP_STATUS_DEINITED);

    return e_status;
}

/*******************************************************************************
 * Name
 *          _mmp_main_init_working_resource
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_init_working_resource(
    MMP_MAIN_APP_INST_T*        pt_this,
    BOOL                        b_stop_tv)
{
    INT32                       i4_ret = 0;
	static INT8                 power_on_flag = 0;

    if(!a_appl_splayer_init())
    {
        DBG_LOG_PRINT(("USBMMPlayer [%d][%s] MM init FAIL \n", __LINE__, __FUNCTION__));
    }

	if(power_on_flag == 0)
	{
		power_on_flag = 1;
		DBG_LOG_PRINT(("[%d][%s] Power on does no initialize! \n", __LINE__, __FUNCTION__));
		return MMPR_OK;
	}

    if(FALSE == pt_this->b_is_working_res_ready)
    {
        /*init member*/
        pt_this->ui2_gui_lang_nfy = APP_CFG_NOTIFY_NULL_ID;

        /**/
        i4_ret = mmp_main_rc_pre_init();
        if(MMPR_OK != i4_ret)
        {
             DBG_LOG_PRINT(("<app_main>: mmp_main_rc_pre_init fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return i4_ret;
        }

        /*open service context*/
        i4_ret = _mmp_main_init_svctx(pt_this);
        if(MMPR_OK != i4_ret)
        {
             DBG_LOG_PRINT(("<app_main>: _mmp_main_init_svctx fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return i4_ret;
        }

        /*register all notifications*/
        i4_ret = _mmp_main_register_nfy(pt_this);
        if(MMPR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<app_main>: _mmp_main_register_nfy fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return i4_ret;
        }

#ifdef CLI_SUPPORT
        /*init cli*/
        i4_ret = mmp_cli_init();
        if(MMPR_OK != i4_ret)
        {
             DBG_LOG_PRINT(("<app_main>: mmp_cli_init fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return AEER_FAIL;
        }
#endif

        /*init multimedia controller*/
        i4_ret = mmp_mc_init();
        if(MMPR_OK != i4_ret)
        {
             DBG_LOG_PRINT(("<app_main>: mmp_mc_init fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return i4_ret;
        }

        /**/
        i4_ret = mmp_main_rc_post_init();
        if(MMPR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<app_main>: mmp_main_rc_post_init fail. i4_ret = %d line(%d)\r\n", i4_ret, __LINE__));
            return i4_ret;
        }

        pt_this->b_is_working_res_ready = TRUE;

        i4_ret = MMPR_OK;
    }
    else
    {
        DBG_LOG_PRINT(("<app_main>: already init. line(%d)\r\n", __LINE__));
        i4_ret = MMPR_ALREADY_INIT;
    }
#ifndef APP_CAST_TV_MMP
    /*stop all resource for video*/
    if(b_stop_tv)
    {
        i4_ret = _mmp_main_free_video_resource(pt_this);
        if(MMPR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<app_main>: _mmp_main_free_video_resource fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return i4_ret;
        }
    }
#endif
    return i4_ret;
}

/*******************************************************************************
 * Name
 *          _mmp_main_deinit_working_resource
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_deinit_working_resource(
    MMP_MAIN_APP_INST_T*        pt_this)
{
    /**/
    mmp_main_rc_pre_exit();

    /*deinit multimedia controller*/
    MMP_EXEC_WITH_ASSERT(mmp_mc_deinit(), MMPR_OK);

    /*deinit main service context*/
    _mmp_main_deinit_svctx(pt_this);

    /*unregister all notifications*/
    _mmp_main_unregister_nfy(pt_this);

#ifdef CLI_SUPPORT
    {
        INT32 i4_ret;
        /*deinit cli*/
        i4_ret = mmp_cli_deinit();
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_cli_deinit() failed. i4_ret = %d.\r\n", i4_ret));
        }
    }
#endif

    /**/
    mmp_main_rc_post_exit();

    pt_this->b_is_working_res_ready = FALSE;

    return MMPR_OK;
}

/*******************************************************************************
 * Name
 *          _mmp_main_register_wm
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_register_wm(
    MMP_MAIN_APP_INST_T*        pt_this)
{
    INT32                       i4_ret;

    /* register to widget manager */
    i4_ret = c_wgl_register(_mmp_main_widget_cb);
    if(WGLR_OK != i4_ret)
    {
        return MMPR_INTERNAL_ERROR;
    }

    /* set delay tolerance - in milliseconds */
    i4_ret = c_wgl_set_delay_tolerance(MMP_RC_WGL_MSG_TOLERANCE);
    if(WGLR_OK != i4_ret)
    {
        return MMPR_INTERNAL_ERROR;
    }

    return MMPR_OK;
}

/*******************************************************************************
 * Name
 *          _mmp_main_init_svctx
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_init_svctx(
    MMP_MAIN_APP_INST_T*        pt_this)
{
    INT32                       i4_ret;

    /* open main service context */
    i4_ret = c_svctx_open(SVCTX_NAME_MAIN, &pt_this->h_main_svctx);
    if(SVCTXR_OK != i4_ret)
    {
        return MMPR_INTERNAL_ERROR;
    }

    /* open sub service context */
    i4_ret = c_svctx_open(SVCTX_NAME_SUB, &pt_this->h_sub_svctx);
    if(SVCTXR_OK != i4_ret)
    {
         DBG_LOG_PRINT(("<app_main>: c_svctx_open(sub) failed. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));

        pt_this->h_sub_svctx = NULL_HANDLE;
    }

#ifdef APP_TV_AV_SCART_BYPASS_SUPPORT
    /**/

    i4_ret = c_svctx_open(SVCTX_NAME_MONITOR_BYPASS, &pt_this->h_mnbypass_svctx);
    if(SVCTXR_OK != i4_ret)
    {
         DBG_LOG_PRINT(("<app_main>: c_svctx_open(mn-by-pass) failed. i4_ret = %d.\r\n", i4_ret));
        pt_this->h_mnbypass_svctx = NULL_HANDLE;
    }

    i4_ret = c_svctx_open(SVCTX_NAME_TV_BYPASS, &pt_this->h_tvbypass_svctx);
    if(SVCTXR_OK != i4_ret)
    {
         DBG_LOG_PRINT(("<app_main>: c_svctx_open(tv-by-pass) failed. i4_ret = %d.\r\n", i4_ret));
        pt_this->h_tvbypass_svctx = NULL_HANDLE;
    }
#endif

#ifdef APP_NAV_REC_SUPPORT
    /**/
    i4_ret = c_svctx_open(SVCTX_NAME_REC_TV, &pt_this->h_rec_svctx);
    if(SVCTXR_OK != i4_ret)
    {
         DBG_LOG_PRINT(("<app_main>: c_svctx_open(rec-tv) failed. i4_ret = %d.\r\n", i4_ret));
        pt_this->h_rec_svctx = NULL_HANDLE;
    }
#endif

    return MMPR_OK;
}

/*******************************************************************************
 * Name
 *          _mmp_main_deinit_svctx
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _mmp_main_deinit_svctx(
    MMP_MAIN_APP_INST_T*        pt_this)
{
    /* close main service context */
    if(pt_this->h_main_svctx)
    {
        MMP_EXEC_WITH_ASSERT(c_svctx_close(pt_this->h_main_svctx), SVCTXR_OK);

        pt_this->h_main_svctx = NULL_HANDLE;
    }

    /* close sub service context */
    if(pt_this->h_sub_svctx)
    {
        MMP_EXEC_WITH_ASSERT(c_svctx_close(pt_this->h_sub_svctx), SVCTXR_OK);

        pt_this->h_sub_svctx = NULL_HANDLE;
    }

#ifdef APP_TV_AV_SCART_BYPASS_SUPPORT
    /**/

    if(pt_this->h_mnbypass_svctx)
    {
        MMP_EXEC_WITH_ASSERT(c_svctx_close(pt_this->h_mnbypass_svctx), SVCTXR_OK);
        pt_this->h_mnbypass_svctx = NULL_HANDLE;
    }

    if(pt_this->h_tvbypass_svctx)
    {
        MMP_EXEC_WITH_ASSERT(c_svctx_close(pt_this->h_tvbypass_svctx), SVCTXR_OK);

        pt_this->h_tvbypass_svctx = NULL_HANDLE;
    }
#endif

#ifdef APP_NAV_REC_SUPPORT
    /**/
    if(pt_this->h_rec_svctx)
    {
        MMP_EXEC_WITH_ASSERT(c_svctx_close(pt_this->h_rec_svctx), SVCTXR_OK);

        pt_this->h_rec_svctx = NULL_HANDLE;
    }
#endif

}

/*******************************************************************************
 * Name
 *          _mmp_main_init_canvas
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_init_canvas(
    MMP_MAIN_APP_INST_T*    pt_this)
{
    GL_HSCREEN_T                h_screen = NULL_HANDLE;
    GL_HPLANE_T                 h_plane = NULL_HANDLE;
    INT32                       i4_ret;
    UINT32                      ui4_gui_idx;
    UINT32                      ui4_subitle_idx;

    /*open screen*/
    i4_ret = c_gl_screen_open(MMP_RC_DISPLAY_NAME, NULL, NULL, &h_screen);
    if(GLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_gl_screen_open(%s) failed. i4_ret = %d.\r\n", MMP_RC_DISPLAY_NAME, i4_ret));
        return MMPR_FAIL;
    }

    do
    {
        ui4_gui_idx     = MMP_RC_GUI_OSD_INDEX;
        ui4_subitle_idx = MMP_RC_SBTL_OSD_INDEX;

        /*init plane*/
        i4_ret = c_gl_plane_open(h_screen, (UINT16)ui4_gui_idx, &h_plane);
        if(GLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_gl_plane_open(%d) failed. i4_ret = %d.\r\n", ui4_gui_idx, i4_ret));

            h_plane = NULL_HANDLE;
            i4_ret = MMPR_FAIL;
            break;
        }

        /*canvas*/
        i4_ret = c_wgl_get_canvas(h_plane, &pt_this->h_canvas);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_get_canvas() failed. i4_ret = %d.\r\n", i4_ret));

            pt_this->h_canvas = NULL_HANDLE;
            i4_ret = MMPR_FAIL;
        }
        else
        {
            i4_ret = MMPR_OK;
        }

        if(ui4_gui_idx != ui4_subitle_idx)
        {
            /*init plane*/
            i4_ret = c_gl_plane_open(h_screen, (UINT16)ui4_subitle_idx, &h_plane);
            if(GLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_gl_plane_open(%d) failed. i4_ret = %d.\r\n", ui4_gui_idx, i4_ret));

                h_plane = NULL_HANDLE;
                i4_ret = MMPR_FAIL;
                break;
            }

            /*canvas*/
            i4_ret = c_wgl_get_canvas(h_plane, &pt_this->h_sbtl_canvas);
            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_get_canvas() failed. i4_ret = %d.\r\n", i4_ret));

                pt_this->h_sbtl_canvas = NULL_HANDLE;
                i4_ret = MMPR_FAIL;
            }
            else
            {
                i4_ret = MMPR_OK;
            }
        }
        /*
        else
        {
            pt_this->h_sbtl_canvas = pt_this->h_canvas;
        }*/

    } while(0);

    if(h_screen)
    {
        MMP_EXEC_WITH_ASSERT(c_gl_obj_free(h_screen), GLR_OK);
    }

    if(h_plane)
    {
        MMP_EXEC_WITH_ASSERT(c_gl_obj_free(h_plane), GLR_OK);
    }

    return i4_ret;
}

/*******************************************************************************
 * Name
 *          _mmp_main_init_svl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_init_svl(
        MMP_MAIN_APP_INST_T*    pt_this)
{
    INT32                       i4_ret;

    if (NULL_HANDLE == pt_this->h_cable_svl)
    {
        i4_ret = c_svl_open(ATSC_CABLE_SVL_ID, NULL, NULL, &pt_this->h_cable_svl);
        if(SVLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_svl_open(cable) failed. i4_ret = %d.\r\n", i4_ret));
            pt_this->h_cable_svl = NULL_HANDLE;
            return MMPR_FAIL;
        }
    }

    if (NULL_HANDLE == pt_this->h_air_svl)
    {
        i4_ret = c_svl_open(ATSC_TRSTRL_SVL_ID, NULL, NULL, &pt_this->h_air_svl);
        if(SVLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_svl_open(air) failed. i4_ret = %d.\r\n", i4_ret));
            pt_this->h_air_svl = NULL_HANDLE;

            /*free allocated*/
            _mmp_main_deinit_svl(pt_this);

            return MMPR_FAIL;
        }
    }

    return MMPR_OK;
}

/*******************************************************************************
 * Name
 *          _mmp_main_deinit_svl
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _mmp_main_deinit_svl(
        MMP_MAIN_APP_INST_T*    pt_this)
{
    /**/
    if(pt_this->h_cable_svl)
    {
        MMP_EXEC_WITH_ASSERT(c_svl_close(pt_this->h_cable_svl), SVLR_OK);
        pt_this->h_cable_svl = NULL_HANDLE;
    }

    if(pt_this->h_air_svl)
    {
        MMP_EXEC_WITH_ASSERT(c_svl_close(pt_this->h_air_svl), SVLR_OK);
        pt_this->h_air_svl = NULL_HANDLE;
    }
}

/*******************************************************************************
 * Name
 *          _mmp_main_register_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_register_nfy(
    MMP_MAIN_APP_INST_T*        pt_this)
{
    INT32                       i4_ret;

    /*register GUI lang notify*/
    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_GUI_LANG, NULL, _mmp_main_gui_lang_nfy_cb, &pt_this->ui2_gui_lang_nfy);

    return (APP_CFGR_OK == i4_ret) ? MMPR_OK : MMPR_FAIL;
}

/*******************************************************************************
 * Name
 *          _mmp_main_unregister_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _mmp_main_unregister_nfy(
    MMP_MAIN_APP_INST_T*        pt_this)
{
    if(APP_CFG_NOTIFY_NULL_ID != pt_this->ui2_gui_lang_nfy)
    {
        MMP_EXEC_WITH_ASSERT(a_cfg_notify_unreg(pt_this->ui2_gui_lang_nfy), APP_CFGR_OK);

        pt_this->ui2_gui_lang_nfy = APP_CFG_NOTIFY_NULL_ID;
    }
}

/*******************************************************************************
 * Name
 *          _mmp_main_cancel_op
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _mmp_main_cancel_op(
    VOID*                       pv_data,
    SIZE_T                      z_data_len)
{
    UINT32                  ui4_keycode = *((UINT32*)pv_data);

#ifdef APP_NET_DLNA_SUPPORT
    UINT32                  ui4_idx;
    SIZE_T                  z_size = MMP_RC_PATH_MAX_LEN;
    CHAR                    s_mnt_point[MMP_RC_PATH_MAX_LEN];
    INT32                   i4_ret;

    do {
        c_memset(s_mnt_point, 0, sizeof(CHAR) * MMP_RC_PATH_MAX_LEN);
        i4_ret = a_rmv_dev_get_active_mnt_pnt(&ui4_idx, &z_size, s_mnt_point);
        if (RMVR_OK != i4_ret)
        {
            break;
        }

        z_size = c_strlen(s_mnt_point);
        if (s_mnt_point[z_size - 1] != '/')
        {
            s_mnt_point[z_size] = '/';
        }

        if (c_fm_dlna_is_inread())
        {
            i4_ret = c_fm_dlna_break(s_mnt_point);
             DBG_LOG_PRINT(("<app_main>: c_fm_dlna_break . i4_ret = %d. \r\n", i4_ret));
        }
    } while (0);
#endif

    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                _mmp_main_widget_event_handler,
                                (VOID*)WGL_MSG_KEY_DOWN,
                                (VOID*)ui4_keycode,
                                (VOID*)c_os_get_sys_tick(),
                                NULL);

}

/*******************************************************************************
 * Name
 *          _mmp_main_widget_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_widget_cb(
    UINT32                      ui4_msg,
    VOID*                       pv_param1,
    VOID*                       pv_param2)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;
    BOOL                        b_cancel_op = FALSE;
    UINT32                      ui4_tick_diff;

    MMP_ASSERT(pt_this->h_app);

    if (WGL_MSG_KEY_DOWN == ui4_msg ||
        WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        UINT32  ui4_keycode = (UINT32)pv_param1;

        ui4_tick_diff = pt_this->ui4_last_handle_key_tick - pt_this->ui4_last_rece_key_tick;
        if (ui4_tick_diff * c_os_get_sys_tick_period() >= MMP_MAIN_RC_MISS_KEY_THRESHOLD)
        {
            if (WGL_MSG_KEY_DOWN == ui4_msg &&
                (BTN_EXIT == ui4_keycode || BTN_MENU == ui4_keycode))
            {
                a_agent_async_invoke(_mmp_main_cancel_op, (VOID*)&ui4_keycode, sizeof(UINT32));
                b_cancel_op = TRUE;
            }
        }

        pt_this->ui4_last_rece_key_tick = c_os_get_sys_tick();
        pt_this->ui4_last_handle_key_tick = pt_this->ui4_last_rece_key_tick + MMP_MAIN_RC_MISS_KEY_THRESHOLD/c_os_get_sys_tick_period();

        if (b_cancel_op)
        {
            return WGLR_OK;
        }
    }

    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                              _mmp_main_widget_event_handler,
                              (VOID*)ui4_msg,
                              pv_param1,
                              pv_param2,
                              NULL);

    return WGLR_OK;
}

/*******************************************************************************
 * Name
 *          _mmp_main_widget_event_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _mmp_main_widget_event_handler(
    VOID*                       pv_ui4_msg,
    VOID*                       pv_param1,
    VOID*                       pv_param2,
    VOID*                       pv_unused)
{
    if (WGL_MSG_KEY_DOWN   == (UINT32)pv_ui4_msg ||
        WGL_MSG_KEY_REPEAT == (UINT32)pv_ui4_msg)
    {
        t_g_app_inst.ui4_last_handle_key_tick = c_os_get_sys_tick();
    }
#ifdef APP_ZOOM_MODE_SUPPORT
    else if (WGL_MSG_NOTIFY_HL_AREA == (UINT32)pv_ui4_msg)
    {
        a_zoom_mode_enlarge_wgl_hl_area(ZOOM_MAKE_ID(ZOOM_APP_GRPID_MMP, ZOOM_APP_RECID_MMP_DEFAULT), (GL_RECT_T *)(pv_param2));
    }
#endif

    if(mmp_main_rc_key_pre_handler((UINT32)pv_ui4_msg, (UINT32)pv_param1, pv_param2))
    {
        UINT32                  ui4_msg = 0;

#ifdef MMP_MAIN_RC_KEEP_KEY_REPEAT
        ui4_msg = (UINT32)pv_ui4_msg;
#else
       if((MMP_BE_BROWSER_MEDIA_TYPE_PHOTO == a_mmp_be_get_media_type())&&
			(BTN_SELECT == (UINT32)pv_param1)&&
			(WGL_MSG_KEY_REPEAT == (UINT32)pv_ui4_msg))
		{
			 ui4_msg = (UINT32)pv_ui4_msg;
		}
		else
		{
        ui4_msg = (WGL_MSG_KEY_REPEAT == (UINT32)pv_ui4_msg) ? WGL_MSG_KEY_DOWN : (UINT32)pv_ui4_msg;
		}
#endif
        c_wgl_dispatch_event(ui4_msg, pv_param1, pv_param2);

        mmp_main_rc_key_post_handler((UINT32)pv_ui4_msg, (UINT32)pv_param1, pv_param2);
    }
}
/*******************************************************************************
 * Name
 *          mmp_main_widget_event_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
VOID mmp_main_widget_event_handler(
    VOID*                       pv_ui4_msg,
    VOID*                       pv_param1,
    VOID*                       pv_param2,
    VOID*                       pv_unused)
{
    _mmp_main_widget_event_handler (pv_ui4_msg, pv_param1, pv_param2, pv_unused);
}

/*******************************************************************************
 * Name
 *          _mmp_main_gui_lang_nfy_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _mmp_main_gui_lang_nfy_cb(
    UINT16                      ui2_nfy_id,
    VOID*                       pv_tag,
    UINT16                      ui2_id)
{
    if(CFG_MAKE_ID(APP_CFG_GRPID_GUI_LANG, APP_CFG_RECID_GUI_LANG) != ui2_id)
    {
        return;
    }

    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_IMPORTANT,
                              _mmp_main_gui_lang_event_handler,
                              (VOID*)(UINT32)ui2_nfy_id,
                              NULL,
                              NULL,
                              NULL);
}

/*******************************************************************************
 * Name
 *          _mmp_main_gui_lang_event_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _mmp_main_gui_lang_event_handler(
    VOID*                       pv_ui2_nfy_id,
    VOID*                       pv_unused1,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3)
{
    /*broadcast to all components*/
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_GUI_LANG_XNG, NULL);
}

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
/*******************************************************************************
 * Name
 *          _mmp_main_dmr_show_event_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _mmp_main_dmr_show_event_handler(
        VOID*                   pv_dmr_cmd,
        VOID*                   pv_unused1,
        VOID*                   pv_unused2,
        VOID*                   pv_unused3)
{
    /*broadcast to all components*/
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_DMR_SHOW_CMD, pv_dmr_cmd);
}
#endif

/*******************************************************************************
 * Name
 *          _mmp_main_free_video_resource
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_free_video_resource(
    MMP_MAIN_APP_INST_T*        pt_this)
{
    VSH_REGION_INFO_T t_dsp_region = {0};
    INT32                       i4_ret, i;
    SM_COMMAND_T                at_sm_cmds[4];
    SM_CMD_CODE_T               ae_cmd_code[2] = {SCC_CMD_CODE_VIDEO_NR, SCC_CMD_CODE_VIDEO_3D_NR};

    /*leave PIP/POP mode*/
    i4_ret = a_tv_set_mode(TV_MODE_TYPE_NORMAL);
    if(TVR_OK != i4_ret)
    {
         DBG_LOG_PRINT(("<app_main>: a_tv_set_mode fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
        return AEER_FAIL;
    }

    /*resize video to full screen, set main svctx to full display region*/
    t_dsp_region.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_dsp_region.ui4_height = VSH_REGION_MAX_HEIGHT;
    i4_ret = c_svctx_set_stream_attr(pt_this->h_main_svctx,
                                     ST_VIDEO,
                                     SM_VSH_SET_TYPE_DISP_REGION,
                                     &t_dsp_region,
                                     sizeof(VSH_REGION_INFO_T));
    if(SVCTXR_OK != i4_ret)
    {
         DBG_LOG_PRINT(("<app_main>: c_svctx_set_stream_attr(SM_VSH_SET_TYPE_DISP_REGION) failed. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
    }

    /*disable NR and 3D NR*/
    at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_VIDEO;
    at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text     = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].u.ui2_data    = 0;        /*OFF*/
    at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
    at_sm_cmds[3].u.ui4_data    = 0;
    for(i = 0; i < 2; i++)
    {
        at_sm_cmds[2].e_code    = ae_cmd_code[i];
        i4_ret = c_scc_comp_grp_set(at_sm_cmds);
        if(SMR_OK != i4_ret)
        {
             DBG_LOG_PRINT(("<app_main>: c_scc_comp_grp_set fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return MMPR_FAIL;
        }
    }

    /*stop video*/
    i4_ret = c_svctx_sync_stop_svc(pt_this->h_main_svctx, DEFAULT_STOP_SVC_TIMEOUT);
    if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
    {
         DBG_LOG_PRINT(("<app_main>: c_svctx_sync_stop_svc(main) fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
        return MMPR_FAIL;
    }

    /*stop video*/
    if(pt_this->h_sub_svctx)
    {
        i4_ret = c_svctx_sync_stop_svc(pt_this->h_sub_svctx, DEFAULT_STOP_SVC_TIMEOUT);
        if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
        {
             DBG_LOG_PRINT(("<app_main>: c_svctx_sync_stop_svc(sub) fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return MMPR_FAIL;
        }
    }

    /*stop video*/
#ifdef APP_TV_AV_SCART_BYPASS_SUPPORT
    if(pt_this->h_mnbypass_svctx)
    {
        i4_ret = c_svctx_sync_stop_svc(pt_this->h_mnbypass_svctx, DEFAULT_STOP_SVC_TIMEOUT);
        if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
        {
            DBG_LOG_PRINT(("<app_main>: c_svctx_sync_stop_svc(monitor bypass) fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return MMPR_FAIL;
        }
    }

    if(pt_this->h_tvbypass_svctx)
    {
        i4_ret = c_svctx_sync_stop_svc(pt_this->h_tvbypass_svctx, DEFAULT_STOP_SVC_TIMEOUT);
        if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
        {
            DBG_LOG_PRINT(("<app_main>: c_svctx_sync_stop_svc(tv bypass) fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return MMPR_FAIL;
        }
    }
#endif

    /* Disable SCART bypass assocation */
    a_tv_set_scart_bypass_association(FALSE, FALSE);

    /* stop record */
#ifdef APP_NAV_REC_SUPPORT
    if(pt_this->h_rec_svctx)
    {
        i4_ret = c_svctx_sync_stop_svc(pt_this->h_rec_svctx, DEFAULT_STOP_SVC_TIMEOUT);
        if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
        {
            DBG_LOG_PRINT(("<app_main>: c_svctx_sync_stop_svc(rec) fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
            return MMPR_FAIL;
        }
    }
#endif

    /*disable blue mute*/
    _mmp_main_update_blue_mute(pt_this, _MMP_MAIN_BM_OPTION_DISABLE);

    /*use internal gamma*/
    _mmp_main_update_gamma(pt_this, _MMP_MAIN_GAMMA_OPTION_DEFAULT);

    /*use internal screen mode*/
    a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, TRUE);

    /*For fix DTV00140629*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));

    a_tv_reset_tmp_unlock_info(TV_WIN_ID_MAIN);

    /*Disable MJC effect*/
    //mmp_main_enable_mjc_effect(FALSE);

    return MMPR_OK;
}

/*******************************************************************************
 * Name
 *          _mmp_send_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_send_msg(
    HANDLE_T                    h_app,
    UINT32                      ui4_type,
    VOID*                       pv_msg,
    SIZE_T                      z_msg_size,
    MMP_MC_CSC_RETRY_TYPE_T     e_retry_type)
{
    INT32                    i4_retry, i4_ret, i;

    switch(e_retry_type)
    {
    case MMP_MC_CSC_RETRY_TYPE_CRITICAL:
        i4_retry = 20;
        break;

    case MMP_MC_CSC_RETRY_TYPE_IMPORTANT:
        i4_retry = 10;
        break;

    case MMP_MC_CSC_RETRY_TYPE_NORMAL:
        i4_retry = 5;
        break;

    case MMP_MC_CSC_RETRY_TYPE_ONCE:
    default:
        i4_retry = 1;
        break;
    }

    i4_ret = MMPR_OK;
    for(i = 0; i < i4_retry; i++)
    {
        i4_ret = c_app_send_msg(h_app, ui4_type, pv_msg, z_msg_size, NULL, NULL);
        if(AEER_OK == i4_ret)
        {
            return MMPR_OK;
        }
        else if(AEER_INV_HANDLE == i4_ret)
        {
            MMP_DBG_ERROR(("c_app_send_msg() failed. i4_ret = %d.\r\n", i4_ret));
            MMP_ASSERT(0);

            return MMPR_INTERNAL_ERROR;
        }

        MMP_DBG_ERROR(("c_app_send_msg() failed. i4_ret = %d.\r\n", i4_ret));
    }

    MMP_ASSERT(MMP_MC_CSC_RETRY_TYPE_NORMAL == e_retry_type || MMP_MC_CSC_RETRY_TYPE_ONCE == e_retry_type);
    return MMPR_QUEUE_FULL;
}

/*******************************************************************************
 * Name _mmp_main_req_working_res_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _mmp_main_req_working_res_handler(
        VOID*                   pv_b_init,
        VOID*                   pv_unused1,
        VOID*                   pv_unused2,
        VOID*                   pv_unused3)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;
    BOOL                        b_init = (BOOL)(UINT32)pv_b_init;

    if (b_init)
    {
        _mmp_main_init_working_resource(pt_this, TRUE);
    }
    else
    {
        _mmp_main_deinit_working_resource(pt_this);
    }

    /*raise the signal*/
    if(OSR_OK != c_sema_unlock(pt_this->h_ready_signal))
    {
        MMP_ASSERT(0);
    }
}

/*******************************************************************************
 * Name _mmp_main_update_blue_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_update_blue_mute(
        MMP_MAIN_APP_INST_T*    pt_this,
        _MMP_MAIN_BM_OPTION_T   e_option)
{
    SVCTX_VIDEO_MUTE_INFO_T t_video_mute_info;
    INT32                   i4_ret;
    INT16                   i2_app_val;
    BOOL                    b_blue_mute;

    switch(e_option)
    {
    case _MMP_MAIN_BM_OPTION_DISABLE:
        {
            t_video_mute_info.b_enable          = TRUE;
            t_video_mute_info.t_color.ui1_red   = 0;
            t_video_mute_info.t_color.ui1_green = 0;
            t_video_mute_info.t_color.ui1_blue  = 0;

            b_blue_mute = TRUE;
        }
        break;

    case _MMP_MAIN_BM_OPTION_RESET:
        {
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE), &i2_app_val);
            if(APP_CFGR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("a_cfg_av_get() failed. i4_ret = %d.\r\n", i4_ret));
                return MMPR_FAIL;
            }

            b_blue_mute = (BOOL)i2_app_val;
            if(b_blue_mute)
            {
                t_video_mute_info.b_enable          = TRUE;
                i4_ret = a_cfg_get_blue_mute_color(&t_video_mute_info.t_color.ui1_red,
                                                   &t_video_mute_info.t_color.ui1_green,
                                                   &t_video_mute_info.t_color.ui1_blue);
                if(APP_CFGR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("a_cfg_av_get() failed. i4_ret = %d.\r\n", i4_ret));
                    return MMPR_FAIL;
                }
            }
        }
        break;

    default:
        MMP_DBG_ERROR(("Unknown Blue-Mute option.\r\n"));
        MMP_ASSERT(0);
        return MMPR_FAIL;
    }

    /* blue mute */
    if(b_blue_mute)
    {
        i4_ret = c_svctx_set(pt_this->h_main_svctx,
                             SVCTX_COMMON_SET_VIDEO_MUTE_ATTR,
                             &t_video_mute_info,
                             sizeof(SVCTX_VIDEO_MUTE_INFO_T));
        if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret)
        {
            MMP_DBG_ERROR(("c_svctx_set(main, SVCTX_COMMON_SET_VIDEO_MUTE_ATTR) failed. i4_ret = %d.\r\n", i4_ret));
        }

        i4_ret = c_svctx_set(pt_this->h_sub_svctx,
                             SVCTX_COMMON_SET_VIDEO_MUTE_ATTR,
                             &t_video_mute_info,
                             sizeof(SVCTX_VIDEO_MUTE_INFO_T));
        if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret)
        {
            MMP_DBG_ERROR(("c_svctx_set(main, SVCTX_COMMON_SET_VIDEO_MUTE_ATTR) failed. i4_ret = %d.\r\n", i4_ret));
        }
    }

    return MMPR_OK;
}

/*******************************************************************************
 * Name _mmp_main_update_gamma
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_update_gamma(
    MMP_MAIN_APP_INST_T*        pt_this,
    _MMP_MAIN_GAMMA_OPTION_T    e_option)
{
#if 0
    INT32                       i4_ret;
    switch(e_option)
    {
    case _MMP_MAIN_GAMMA_OPTION_DEFAULT:
        {
            SM_COMMAND_T    at_sm_cmds[4];
            UINT32          i = 0;

            /**/
            at_sm_cmds[i].e_code        = SCC_CMD_CODE_GRP_TYPE;
            at_sm_cmds[i++].u.ui4_data    = SCC_CMD_TYPE_DISP;
            at_sm_cmds[i].e_code        = SCC_CMD_CODE_NAME;
            at_sm_cmds[i++].u.ps_text     = SN_PRES_MAIN_DISPLAY;
            at_sm_cmds[i].e_code        = SCC_CMD_CODE_DISP_GAMMA;
            at_sm_cmds[i++].u.ui2_data    = MMP_MAIN_APP_DEFAULT_GAMMA;
            at_sm_cmds[i].e_code        = SM_CMD_CODE_END;
            at_sm_cmds[i++].u.ui4_data    = 0;
            MMP_ASSERT(i <= 4);

            i4_ret = c_scc_comp_grp_set(at_sm_cmds);
            if(SMR_OK != i4_ret)
            {
                return MMPR_FAIL;
            }
        }
        break;

    case _MMP_MAIN_GAMMA_OPTION_RESET:
        {
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA));
        }
        break;

    default:
        MMP_DBG_ERROR(("Unknown GAMMA option.\r\n"));
        MMP_ASSERT(0);
        return MMPR_FAIL;
    }
#endif
    return MMPR_OK;
}

/*******************************************************************************
 * Name _mmp_main_update_canvas_setting
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static INT32 _mmp_main_update_canvas_setting(
        MMP_MAIN_APP_INST_T*        pt_this,
        BOOL                        b_resume)
{
#if (defined APP_SUPPORT_SECOND_OSD_PLANE) || (defined APP_NAV_MOVE_CC_TO_SECOND_PLANE)
    HANDLE_T            h_plane = NULL_HANDLE;
    HANDLE_T            h_canvas = NULL_HANDLE;
    WGL_CANVAS_CFG_T    t_cfg     = {0};
    GL_HSCREEN_T        h_screen = NULL_HANDLE;
    INT32               i4_ret = 0;

#ifdef APP_SUPPORT_SECOND_OSD_PLANE
    h_plane = a_nav_get_second_osd_plane();
    h_canvas = a_nav_get_canvas_of_second_osd_plane();
#else
    h_canvas = a_nav_get_cc_canvas();
    i4_ret = c_gl_screen_open(
                    SN_PRES_MAIN_DISPLAY,
                    NULL,
                    NULL,
                    &h_screen
                    );
    if (i4_ret != GLR_OK)
    {
        DBG_LOG_PRINT (("{%s %d} return fail,%d.\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    i4_ret = c_gl_plane_open(
                    h_screen,
                    0,
                    &h_plane
                    );
    if (i4_ret != GLR_OK)
    {
        DBG_LOG_PRINT (("{%s %d} return fail,%d.\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
#endif

    t_cfg.ui4_flag     = WGL_CANVAS_CFG_AUTOSCALE | WGL_CANVAS_CFG_COLORMODE | WGL_CANVAS_CFG_WIDTH | WGL_CANVAS_CFG_HEIGHT;
    t_cfg.b_auto_scale = TRUE;


    if (b_resume)
    {
        /*backup current setting*/
        c_wgl_get_canvas_info(h_canvas, &pt_this->t_orig_canvas_info);
    }
    else
    {
        /*restore setting*/
        t_cfg.ui4_width    = pt_this->t_orig_canvas_info.ui4_width;
        t_cfg.ui4_height   = pt_this->t_orig_canvas_info.ui4_height;
        t_cfg.e_clr_mode   = pt_this->t_orig_canvas_info.e_clr_mode;

        c_gl_plane_enable(h_plane, FALSE);
        c_gl_plane_change_resolution_cm(h_plane, t_cfg.ui4_width, t_cfg.ui4_height, t_cfg.e_clr_mode);
        c_wgl_canvas_reconfig(h_canvas, h_plane, &t_cfg);
        c_gl_plane_enable(h_plane, TRUE);
    }

    if(h_screen)
    {
        MMP_EXEC_WITH_ASSERT(c_gl_obj_free(h_screen), GLR_OK);
    }

    if(h_plane)
    {
        MMP_EXEC_WITH_ASSERT(c_gl_obj_free(h_plane), GLR_OK);
    }

#endif
#ifdef SYS_DTV_SECOND_OSD_PLANE_USE_WINDOW
#ifdef APP_NAV_MOVE_CC_TO_SECOND_PLANE
    {
        GL_HPLANE_T            h_plane;
        c_wgl_get_canvas_plane(a_nav_get_cc_canvas(), &h_plane);
        DBG_LOG_PRINT(("{%s %d} here.\n", __FUNCTION__, __LINE__));
        c_gl_plane_enable(h_plane, b_resume);
        DBG_LOG_PRINT(("{%s %d} here.\n", __FUNCTION__, __LINE__));
    }
#endif
#endif
    return MMPR_OK;
}


/*******************************************************************************
 * Name _mmp_main_sys_key_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
#ifdef _MMP_MAIN_ENABLE_SYS_KEY_HDLR
static BOOL _mmp_main_sys_key_hdlr(
    UINT32                      ui4_keycode)
{
    if (ui4_keycode == BTN_MENU)
    {
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
            mmp_main_widget_event_handler,
            (VOID*)WGL_MSG_KEY_DOWN,
            (VOID*)ui4_keycode,
            (VOID*)c_os_get_sys_tick(),
            NULL);

        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
            mmp_main_widget_event_handler,
            (VOID*)WGL_MSG_KEY_UP,
            (VOID*)ui4_keycode,
            (VOID*)c_os_get_sys_tick(),
            NULL);

        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
#endif

/*******************************************************************************
 * Name mmp_main_lock
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
 INT32  mmp_main_lock(VOID)
{
    INT32  i4_ret;
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;

    /*wait result*/
    i4_ret = c_sema_lock(pt_this->h_ready_signal, X_SEMA_OPTION_WAIT);
    if(OSR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("c_sema_lock() failed. i4_ret = %d.\r\n", i4_ret));
        return MMPR_INTERNAL_ERROR;
    }
    return MMPR_OK;
}

/*******************************************************************************
 * Name mmp_main_unlock
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
 INT32  mmp_main_unlock(VOID)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;

    /*raise the signal*/
    if(OSR_OK != c_sema_unlock(pt_this->h_ready_signal))
    {
        MMP_ASSERT(0);
    }

    return MMPR_OK;
}
/*******************************************************************************
 * Name mmp_main_get_svctx_handle
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
HANDLE_T mmp_main_get_svctx_handle (TV_WIN_ID_T e_win_id)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;

    if (e_win_id == TV_WIN_ID_MAIN)
    {
        return pt_this->h_main_svctx;
    }
    else
    {
        return pt_this->h_sub_svctx;
    }
}

/*******************************************************************************
 * Name mmp_main_get_app
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
HANDLE_T mmp_main_get_app(VOID)
{
    return t_g_app_inst.h_app;
}

/*******************************************************************************
 * Name mmp_main_set_video_srm_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
INT32 mmp_main_set_video_srm_mode(SCC_VID_SRM_MODE_T e_mode)
{
    INT32               i4_ret = MMPR_OK;
    SM_COMMAND_T        at_sm_cmds[3];
    HANDLE_T            h_scc_handle = NULL_HANDLE;

    /* create the scc handles */
    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_VIDEO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;
    i4_ret = c_scc_comp_open(at_sm_cmds, &h_scc_handle);
    if(i4_ret != SMR_OK)
    {
        DBG_ERROR(("<MMP>Can't Open SCC handle"));
        return MMPR_FAIL;
    }

    i4_ret = c_scc_vid_set_srm_mode (h_scc_handle, e_mode);

    if (NULL_HANDLE != h_scc_handle)
    {
        c_scc_comp_close(h_scc_handle);
    }

    return i4_ret;
}

INT32 mmp_main_set_video_disp_region(VSH_REGION_INFO_T*  pt_region_info)
{
	INT32               i4_ret = MMPR_OK;
    SM_COMMAND_T        at_sm_cmds[4];

    /* create the scc handles */
    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_VIDEO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
	at_sm_cmds[2].e_code     = SCC_CMD_CODE_VIDEO_DISP_REGION;
    at_sm_cmds[2].u.pv_data  = (VOID*)pt_region_info;
    at_sm_cmds[3].e_code = SM_CMD_CODE_END;
    at_sm_cmds[3].u.ui4_data = 0;
    i4_ret = c_scc_comp_grp_set(at_sm_cmds);
    if(SMR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("<app_main>: c_scc_comp_grp_set fail. i4_ret = %d. line(%d)\r\n", i4_ret, __LINE__));
        return MMPR_FAIL;
    }

    return i4_ret;
}

/*******************************************************************************
 * Name mmp_main_enable_mjc_effect
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
INT32 mmp_main_enable_mjc_effect(BOOL b_enable)
{
#ifdef APP_MJC_SUPPORT
    INT32               i4_ret = MMPR_OK;
    SM_COMMAND_T        at_sm_cmds[3];
    HANDLE_T            h_scc = NULL_HANDLE;
    SCC_VID_MJC_T       t_mjc;
    DRV_CUST_OPERATION_INFO_T   t_op_info;
    SIZE_T                      z_size = sizeof(DRV_CUST_OPERATION_INFO_T), z_bool_size = sizeof(BOOL);
    BOOL                        b_mjc_enable;
    EXTMJC_TYPE_SET_OSD_MODE_T  t_set_osd_mode;

    /* create the scc handles */
    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_VIDEO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;
    i4_ret = c_scc_comp_open(at_sm_cmds, &h_scc);
    if(i4_ret != SMR_OK)
    {
        DBG_ERROR(("<MMP>Can't Open SCC handle"));
        return MMPR_FAIL;
    }

    /*Get current MJC setting, and apply effect according to b_enable*/
    do {
       i4_ret = c_scc_vid_get_mjc(h_scc, &t_mjc);
       if (SMR_OK != i4_ret)
       {
           break;
       }

       if (b_enable)
       {
           i4_ret = a_cfg_av_get (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT),
                                  (INT16*)(&t_mjc.e_effect));
           if (APP_CFGR_OK != i4_ret)
           {
               break;
           }
       }
       else
       {
           t_mjc.e_effect = SCC_VID_MJC_EFFECT_OFF;
       }

       i4_ret = c_scc_vid_set_mjc(h_scc, &t_mjc);
       IS_MMPR_OK(i4_ret);

    } while (0);

    if (NULL_HANDLE != h_scc)
    {
        c_scc_comp_close(h_scc);
    }

    /*Set OSD mode*/
    do {
#if 1
        c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_EXTMJC_GET;
        t_op_info.u.t_extmjc_get_info.e_extmjc_type = DRV_CUSTOM_EXTMJC_TYPE_IS_ENABLE;
        t_op_info.u.t_extmjc_get_info.pv_get_info = &b_mjc_enable;
        t_op_info.u.t_extmjc_get_info.pz_size = &z_bool_size;
        i4_ret = c_rm_get_comp(DRVT_CUST_DRV,
                               DRV_CUST_COMP_ID,
                               FALSE,
                               ANY_PORT_NUM,
                               0,
                               &t_op_info,
                               &z_size
                               );
        if (RMR_OK != i4_ret || FALSE == b_mjc_enable)
        {
            break;
        }
#endif
        c_memset(&t_set_osd_mode, 0, sizeof(EXTMJC_TYPE_SET_OSD_MODE_T));
        t_set_osd_mode.ui1_osd_mode = b_enable ? DRV_CUSTOM_EXTMJC_OSD_MODE_DMA : DRV_CUSTOM_EXTMJC_OSD_MODE_NORMAL;

        c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_EXTMJC_SET;
        t_op_info.u.t_extmjc_set_info.e_extmjc_type = DRV_CUSTOM_EXTMJC_TYPE_SET_OSD_MODE;
        t_op_info.u.t_extmjc_set_info.pv_set_info = &t_set_osd_mode;
        t_op_info.u.t_extmjc_set_info.z_size = sizeof(EXTMJC_TYPE_SET_OSD_MODE_T);
        t_op_info.u.t_extmjc_set_info.b_store = TRUE;

        /* set to driver */
        i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                               DRV_CUST_COMP_ID,
                               FALSE,
                               ANY_PORT_NUM,
                               0,
                               &t_op_info,
                               sizeof(DRV_CUST_OPERATION_INFO_T));
        if (RMR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_rm_set_comp(DRV_CUSTOM_OPERATION_TYPE_EXTMJC_SET_OSD_MODE) fail. i4_ret = %d. \r\n", i4_ret));
        }
    } while (0);


    return i4_ret;
#else
    return MMPR_OK;
#endif
}

/*******************************************************************************
 * Name
 *          mmp_main_restore_video_resource
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
INT32 mmp_main_restore_video_resource(VOID)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;
    ISL_REC_T                   t_isl_rec;
    INT32                       i4_ret;
#ifdef APP_C4TV_SUPPORT
    CHAR                        s_app_name[APP_NAME_MAX_LEN];

    /* Get next active AP*/
    c_memset(s_app_name, 0, APP_NAME_MAX_LEN);
    a_am_get_next_active_app (s_app_name);
#endif

    /* fix DTV00783226 */
    /*reset screen mode*/
    a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, FALSE);

    if (FALSE == a_am_is_power_on())
    {
        return MMPR_OK;
    }

    /*open svl*/
    i4_ret = _mmp_main_init_svl(pt_this);
    if(MMPR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    /*reset blue mute*/
    _mmp_main_update_blue_mute(pt_this, _MMP_MAIN_BM_OPTION_RESET);

#ifndef MMP_MAIN_UPDATE_GAMMA_IN_MENU_APP
    /*reset gamma*/
    _mmp_main_update_gamma(pt_this, _MMP_MAIN_GAMMA_OPTION_RESET);
#endif

    /*reset video srm mode*/
    mmp_main_set_video_srm_mode(SCC_VID_SRM_MODE_OFF);

    /*reset NR and 3D_NR*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));

    /*reset MJC effect*/
    mmp_main_enable_mjc_effect(TRUE);

    /*For fix DTV00140629*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));

    /*reset SVCTX attribute*/
    a_tv_reset_svctx_parameter(pt_this->h_main_svctx);

    if (pt_this->b_skip_restore_tv_res_while_pause)
    {
        pt_this->b_skip_restore_tv_res_while_pause = FALSE;
        return MMPR_OK;
    }

    /*restart tv*/
    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
    MMP_DBG_INFO(("<mmp> %s,%d,src_type:0x%x,video_type:0x%x\n\r",__FILE__,__LINE__,
        t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type));

    if(TVR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_tv_get_isl_rec_by_win_id() failed. i4_ret = %d.\r\n", i4_ret));
    }
    else /*TVR_OK*/
    {
#ifdef APP_TV_AV_SCART_BYPASS_SUPPORT
        UINT16 ui2_svl_id;
        CHAR*  ps_src_name;

        i4_ret = a_cfg_get_tuner_sync_src(&ui2_svl_id, &ps_src_name);
        if(APP_CFGR_OK == i4_ret)
        {
            i4_ret = a_tv_update(TV_UPDATE_SCART_BYPASS_RESELECT_TV_SCART,
                                 (VOID*)((ATSC_CABLE_SVL_ID == ui2_svl_id) ? pt_this->h_cable_svl : pt_this->h_air_svl),
                                 NULL,
                                 NULL);
            if(TVR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("a_tv_update(TV_UPDATE_SCART_BYPASS_RESELECT_TV_SCART) failed. i4_ret = %d.\r\n", i4_ret));
            }
        }
        else
        {
            MMP_DBG_ERROR(("a_cfg_get_tuner_sync_src() failed. i4_ret = %d.\r\n", i4_ret));
        }
#endif
#ifdef APP_C4TV_SUPPORT
        if (!nav_link_mode_is_on() && (0 != c_strcmp (s_app_name, MSCVT_NAME)))
        {
            ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
                DBG_LOG_PRINT(("[MMP][INPUT_SRC]{%s,%d} call a_tv_change_input_src_by_rec()\n", __FUNCTION__,__LINE__ ));
            );

        #ifdef APP_CAST_TV_MMP
            if(pt_this->t_last_isl_rec.ui1_id != t_isl_rec.ui1_id)
            {
                i4_ret = a_tv_change_input_src_by_rec(pt_this->h_main_svctx, SVCTX_STRM_MODE_AS_LAST, &pt_this->t_last_isl_rec, NULL);
            }
        #else
            i4_ret = a_tv_change_input_src_by_rec(pt_this->h_main_svctx, SVCTX_STRM_MODE_AS_LAST, &t_isl_rec, NULL);
        #endif

            if(TVR_NO_SVL_RECORD == i4_ret)
            {
                /*reset blue mute immediately.*/
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE));
            }
            else if(TVR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("a_tv_change_input_src_by_rec() failed. i4_ret = %d.\r\n", i4_ret));
            }

        #ifdef APP_CAST_TV_MMP_FG
            UINT8 ui1_cast_tv_status = 0;
            a_cfg_get_cast_tv_status(&ui1_cast_tv_status);
            if (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST && ui1_cast_tv_status == APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE)
            {
                SIZE_T z_size = ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE;
                UINT32 ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_UNKNOWN;

                i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_EXIT_REASON),
                                    &ui4_exit_reason, &z_size);
                MMP_DBG_INFO(("<mmp> notify to cast %s,%d,status:%d\n\r",__FILE__,__LINE__,ui4_exit_reason));
                if((ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_USER == ui4_exit_reason) ||
                   (ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_REMOVE_USB == ui4_exit_reason) ||
                   (ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_REMOVE_DLNA == ui4_exit_reason))
                {
                    rest_event_notify_current_input("CAST:SMARTCAST");
                }
            }
        #endif
        }
#endif
    }

    /*close svl*/
    _mmp_main_deinit_svl(pt_this);

    return MMPR_OK;
}
/*******************************************************************************
 * Name
 *          mmp_main_restore_video_resource_no_need_change_input
 * Description: same as mmp_main_restore_video_resource, but remove change source
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
INT32 mmp_main_restore_video_resource_no_need_change_input(VOID)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;
    ISL_REC_T                   t_isl_rec;
    INT32                       i4_ret;

    /* fix DTV00783226 */
    /*reset screen mode*/
    a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, FALSE);

    if (FALSE == a_am_is_power_on())
    {
        return MMPR_OK;
    }

    /*open svl*/
    i4_ret = _mmp_main_init_svl(pt_this);
    if(MMPR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    /*reset blue mute*/
    _mmp_main_update_blue_mute(pt_this, _MMP_MAIN_BM_OPTION_RESET);

#ifndef MMP_MAIN_UPDATE_GAMMA_IN_MENU_APP
    /*reset gamma*/
    _mmp_main_update_gamma(pt_this, _MMP_MAIN_GAMMA_OPTION_RESET);
#endif

    /*reset video srm mode*/
    mmp_main_set_video_srm_mode(SCC_VID_SRM_MODE_OFF);

    /*reset NR and 3D_NR*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));

    /*reset MJC effect*/
    mmp_main_enable_mjc_effect(TRUE);

    /*For fix DTV00140629*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));

    /*reset SVCTX attribute*/
    a_tv_reset_svctx_parameter(pt_this->h_main_svctx);

    if (pt_this->b_skip_restore_tv_res_while_pause)
    {
        pt_this->b_skip_restore_tv_res_while_pause = FALSE;
        return MMPR_OK;
    }

    /*restart tv*/
    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
    MMP_DBG_INFO(("<mmp> %s,%d,src_type:0x%x,video_type:0x%x\n\r",__FILE__,__LINE__,
        t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type));

    if(TVR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_tv_get_isl_rec_by_win_id() failed. i4_ret = %d.\r\n", i4_ret));
    }
    else /*TVR_OK*/
    {
#ifdef APP_TV_AV_SCART_BYPASS_SUPPORT
        UINT16 ui2_svl_id;
        CHAR*  ps_src_name;

        i4_ret = a_cfg_get_tuner_sync_src(&ui2_svl_id, &ps_src_name);
        if(APP_CFGR_OK == i4_ret)
        {
            i4_ret = a_tv_update(TV_UPDATE_SCART_BYPASS_RESELECT_TV_SCART,
                                 (VOID*)((ATSC_CABLE_SVL_ID == ui2_svl_id) ? pt_this->h_cable_svl : pt_this->h_air_svl),
                                 NULL,
                                 NULL);
            if(TVR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("a_tv_update(TV_UPDATE_SCART_BYPASS_RESELECT_TV_SCART) failed. i4_ret = %d.\r\n", i4_ret));
            }
        }
        else
        {
            MMP_DBG_ERROR(("a_cfg_get_tuner_sync_src() failed. i4_ret = %d.\r\n", i4_ret));
        }
#endif
    }

    /*close svl*/
    _mmp_main_deinit_svl(pt_this);

    return MMPR_OK;
}

#ifdef APP_CAST_TV_MMP
/*******************************************************************************
 * Name
 *          mmp_main_free_video_resource
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
INT32 mmp_main_free_video_resource(VOID)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;
    return _mmp_main_free_video_resource(pt_this);
}
VOID mmp_main_set_last_isl_rec(ISL_REC_T* t_last_isl_rec)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;
    pt_this->t_last_isl_rec = *t_last_isl_rec;
}

VOID mmp_main_change_last_isl_rec(VOID)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MMP][INPUT_SRC]{%s,%d} call a_tv_change_input_src_by_rec()\n", __FUNCTION__,__LINE__ ));
    );

    a_tv_change_input_src_by_rec(pt_this->h_main_svctx, SVCTX_STRM_MODE_AS_LAST, &pt_this->t_last_isl_rec, NULL);
}


static BOOL b_g_is_power = FALSE;

VOID a_mmp_set_power_exit_video_state(BOOL b_is_power)
{
    b_g_is_power = b_is_power;
}

BOOL a_mmp_get_power_exit_video_state(VOID)
{
    return b_g_is_power;
}

static BOOL b_g_is_null_file = FALSE; /*mmp resume MMP_FF_PARSE_STATUS_DONE flag*/

VOID a_mmp_set_is_parse_null_ff_state(BOOL b_is_null_file)
{
    b_g_is_null_file = b_is_null_file;
}

BOOL a_mmp_get_is_parse_null_ff_state(VOID)
{
    return b_g_is_null_file;
}
#endif

#ifdef APP_C4TV_SUPPORT
static INT32 i4_g_back_to_menu_page = MENU_SHORT_CUT_MAX;
VOID mmp_main_set_back_to_menu_page(INT32 i4_menu_page)
{
    i4_g_back_to_menu_page = i4_menu_page;
}

INT32 mmp_main_get_back_to_menu_page(VOID)
{
    return i4_g_back_to_menu_page ;
}
#endif

/*----------------------------------------------------------------------------
 * Name: a_mmp_return_activation_with_key
 *
 * Description: This API is used to resume mmp from menu, and handle a key event
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_mmp_return_activation_with_key(UINT32 ui4_key_code)
{
    MMP_MAIN_APP_INST_T*        pt_this = &t_g_app_inst;

    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC != _mmp_main_ts_get_app_status())
    {
        return MMPR_INV_ARG;
    }

    pt_this->ui4_activation_key = ui4_key_code;

#ifdef LINUX_TURNKEY_SOLUTION
    a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=mmp\n");
#else
    a_amb_resume_app(MMP_NAME);
#endif
    return MMPR_OK;
}

INT32 a_mmp_pause_background_mmp(VOID)
{
    UINT8                       ui1_icl_status;
    INT32                       i4_ret;

    /*update ap status*/
    i4_ret = _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_PAUSING);
    if(MMPR_OK != i4_ret)
    {
        return AEER_FAIL;
    }

    /**/
    mmp_main_rc_pre_pause();

    /*turn off RESUMED flag before broadcast MMP_MSG_ID_APP_PAUSED message*/
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_APP_PAUSED, NULL);

    if (a_am_is_power_on())
    {
        mmp_main_restore_video_resource();
    }

    /**/
    mmp_main_rc_post_pause();

    _mmp_main_update_canvas_setting(&t_g_app_inst, FALSE);

#ifndef APP_MMP_PAUSE_KEEP_RESOURCE /*#ifdef APP_MMP_PAUSE_FREE_RESOURCE*/
    _mmp_main_deinit_working_resource(&t_g_app_inst);
#endif

    /*Set media play status*/
    ui1_icl_status = ICL_MMP_MEDIA_PLAY_STATUS_OFF;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_MEDIA_PLAY_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_MMP_MEDIA_PLAY_STATUS_SIZE);

    /*update ap status*/
    i4_ret = _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_PAUSED);
    if(MMPR_OK != i4_ret)
    {
        return AEER_FAIL;
    }

    /* Set icl status */
#if (!defined(APP_VTRL_INP_SRC_MMP_SUPPORT) && !defined(APP_MMP_ENABLE_SCART_AUTO_SWITCH))
    ui1_icl_status = ICL_SCART_EXCL_AP_STATUS_PAUSE;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_SCART_EXCL_AP, ICL_RECID_SCART_EXCL_AP_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_SCART_EXCL_AP_STATUS_SIZE);
#endif

    c_wgl_img_cache_flush();

    DBG_LOG_PRINT(("<app_main>: _mmp_main_app_pause_fct end !!\r\n"));
    return AEER_OK;
}
/*
    a_mmp_pause_background_mmp_for_menu same as a_mmp_pause_background_mmp, but remove change input source
*/
INT32 a_mmp_pause_background_mmp_for_menu(VOID)
{
    UINT8                       ui1_icl_status;
    INT32                       i4_ret;

    DBG_LOG_PRINT(("<app_main>: a_mmp_pause_background_mmp_for_menu begin !! \r\n"));

    /*update ap status*/
    i4_ret = _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_PAUSING);
    if(MMPR_OK != i4_ret)
    {

        DBG_LOG_PRINT(("<app_main>: a_mmp_pause_background_mmp_for_menu fail line%d %d!!\r\n",__LINE__,i4_ret));
        return AEER_FAIL;
    }
    /**/
    mmp_main_rc_pre_pause();

    /*turn off RESUMED flag before broadcast MMP_MSG_ID_APP_PAUSED message*/
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_APP_PAUSED, NULL);

    if (a_am_is_power_on())
    {
        #ifdef APP_3D_PHOTO_SUPPORT
        /* photo exit release res ,set source off ,before select source ,fix DTV00861046*/
        mmp_drc_switch_mode(MMP_DRC_MODE_FREE);
        #endif
        mmp_main_restore_video_resource_no_need_change_input();
    }

    /**/
    mmp_main_rc_post_pause();

    _mmp_main_update_canvas_setting(&t_g_app_inst, FALSE);

#ifndef APP_MMP_PAUSE_KEEP_RESOURCE /*#ifdef APP_MMP_PAUSE_FREE_RESOURCE*/
    _mmp_main_deinit_working_resource(&t_g_app_inst);
#endif

    /*Set media play status*/
    ui1_icl_status = ICL_MMP_MEDIA_PLAY_STATUS_OFF;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_MEDIA_PLAY_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_MMP_MEDIA_PLAY_STATUS_SIZE);

    /*update ap status*/
    i4_ret = _mmp_main_ts_set_app_status(MMP_MAIN_AP_STATUS_PAUSED);
    if(MMPR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("<app_main>: a_mmp_pause_background_mmp_for_menu fail line%d %d!!\r\n",__LINE__,i4_ret));
        return AEER_FAIL;
    }
    /* Set icl status */
#if  (!defined(APP_VTRL_INP_SRC_MMP_SUPPORT) && !defined(APP_MMP_ENABLE_SCART_AUTO_SWITCH))
    ui1_icl_status = ICL_SCART_EXCL_AP_STATUS_PAUSE;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_SCART_EXCL_AP, ICL_RECID_SCART_EXCL_AP_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_SCART_EXCL_AP_STATUS_SIZE);
#endif

    c_wgl_img_cache_flush();

    DBG_LOG_PRINT(("<app_main>: a_mmp_pause_background_mmp_for_menu end !!\r\n"));
    return AEER_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_mmp_skip_restore_tv_res_while_pause
 *
 * Description: This API is used to ignore select service while pausing mmp
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_mmp_skip_restore_tv_res_while_pause(VOID)
{
    t_g_app_inst.b_skip_restore_tv_res_while_pause = TRUE;

    return MMPR_OK;
}
INT32 a_mmp_get_scc_audio_type_out(SCC_AUD_IEC_TYPE_T*  pe_iec_type )
{
    INT32                     i4_ret = MMPR_OK;
    HANDLE_T                  h_scc = NULL_HANDLE;

    if(pe_iec_type == NULL)
    {
        return MMPR_INV_ARG;
    }

    /* get scc main / sub  handle */
    {
        SM_COMMAND_T                          at_sm_cmds[3];

        if(NULL_HANDLE == h_scc)
        {
             /*scc component for mts operation*/
            at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
            at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
            at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
            at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
            at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
            at_sm_cmds[2].u.ui4_data = 0;

            i4_ret = c_scc_comp_open(at_sm_cmds, &h_scc);
            IS_MMPR_OK(SMR_OK == i4_ret ? MMPR_OK : i4_ret);
        }
    }

    do
    {
        /*get scc audio get &iec_type */
        {
            i4_ret = c_scc_aud_get_iec_type(h_scc,pe_iec_type);
            if(SCC_AUD_IEC_CFG_DDP_ATMOS ==  *pe_iec_type)
            {
               *pe_iec_type = SCC_AUD_IEC_CFG_DDP;
            }
            DBG_LOG_PRINT(("\n[audio type] %s  %s  (%d) i4_ret=(%d) pe_iec_type=(%d)\n",__FILE__,__FUNCTION__,__LINE__,i4_ret,*pe_iec_type));
            if(i4_ret != SMR_OK)
            {
                break;
            }
        }
    }while(0);
    c_scc_comp_close(h_scc);

    return i4_ret;
}


