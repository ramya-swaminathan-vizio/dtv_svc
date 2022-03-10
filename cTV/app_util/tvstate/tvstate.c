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
 * $RCSfile: network.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/**
 * @file network.c
 *
 * @brief This file implements the API of network.
 *
 * @author
 */

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <unistd.h>
#include <pthread.h>
#include "c_os.h"

#include "u_svctx.h"

#include "app_util/tvstate/tvstate.h"
#include "app_util/tvstate/smart_dim.h"
#include "agent/agent.h"
#include "app_util/a_cfg.h"

#ifdef APP_NET_NEIGHBOR_SUPPORT
#include "c_dm_smb.h"
#include "c_fm_smb.h"
#endif

#include "app_client.h"
#include "app_util/a_tv.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "menu2/a_menu.h"
#include "menu2/menu_page.h"

#include "am/a_am.h"
#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"

#ifdef APP_WFD_SUPPORT
#include "wfd/wfd.h"
#endif
#include "wizard/a_wzd.h"

/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/
#define TS_COMP_NOT_DUPLICATE                                   ((UINT8)0xFF)
#define TS_TIMEER_DELAY                                         ((UINT32)200)
#define _TS_LOCK(_pt_this)                                                \
{                                                                           \
    if(OSR_OK != c_sema_lock((_pt_this)->h_mtx, X_SEMA_OPTION_WAIT))       \
    {                                                                       \
        DBG_ERROR(("[TVSTATE] File %s Line %d_TS_LOCK error!\n", __FILE__, __LINE__));  \
        return TSR_FAIL;                                              \
    }                                                                       \
}

#define _TS_UNLOCK(_pt_this)                                              \
{                                                                           \
    if(OSR_OK != c_sema_unlock((_pt_this)->h_mtx))                         \
    {                                                                       \
        DBG_ERROR(("[TVSTATE] File %s Line %d_TS_UNLOCK error!\n", __FILE__, __LINE__)); \
        return TSR_FAIL;                                        \
    }                                                                       \
}

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/
static TVSTATE_UTIL_T       t_g_ts_util;

#ifdef APP_PORTING
static UINT16 ui2_ts_scvx_listener_idx;
#endif

static BOOL b_audio_only = FALSE;
#ifdef APP_PORTING
static BOOL b_no_signal = FALSE;
#endif
static BOOL b_video = FALSE;
static BOOL b_menu_slider = FALSE;
static BOOL b_menu_pic_page = FALSE;
static UINT16 ui2_yahoo_state_nfy = 0;
static UINT32 ui4_yahoo_stat = 0;

#ifdef APP_PORTING
typedef struct _SVCTX_LISTENER_MSG
{
    SVCTX_SINK_DISP_T       t_sink_disp;
    SVCTX_COND_T            e_nfy_cond;
    SVCTX_NTFY_CODE_T       e_code;
    STREAM_TYPE_T           e_stream_type;
    VOID*                   pv_nfy_tag;
}SVCTX_LISTENER_MSG;
#endif
/*-----------------------------------------------------------------------------
                    static function declarations
----------------------------------------------------------------------------*/

static VOID _tv_state_detector(VOID* pv_data, SIZE_T z_data_len)
{
    INT32 i4_ret = TSR_OK;
    UINT32  tv_state = TV_STATE_UNKNOW;
    MMP_BE_BROWSER_STATUS_T e_mmp_browser_status = MMP_BE_BROWSER_STATUS_NONE;

    //BOOL b_retail_mode = FALSE;
    //BOOL b_wzd_resume = FALSE;
    //BOOL b_mmp_resume = FALSE;
    //BOOL b_menu_resume = FALSE;
    //BOOL b_mscvt_resume = FALSE;

    CHAR ac_app_name[APP_NAME_MAX_LEN+1] = {0};

    do {
#ifdef APP_RETAIL_MODE_SUPPORT
        ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

        i4_ret = a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
        TVSTATE_BREAK_ON_FAIL(i4_ret);

        if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
        {
            //b_retail_mode = TRUE;
            tv_state |= TV_STATE_RETAIL_MODE_MASK;
        }
#endif
	#ifdef VIZIO_FUSION_SUPPORT
        if ((ui4_yahoo_stat &
            (YAHOO_STATUS_DOCK_UP|YAHOO_STATUS_SIDEBAR|YAHOO_STATUS_FULLSCREEN_GALLERY)) != 0)
        {
            tv_state |= TV_STATE_DOCK_MASK;
        }
#endif
        i4_ret = a_am_get_active_app(ac_app_name);
        TVSTATE_BREAK_ON_FAIL(i4_ret);

        if (c_strcmp(ac_app_name, MENU_NAME) == 0)
        {
            UINT32 ui4_page_id;
            //b_menu_resume = TRUE;
            extern UINT32 ui4_g_menu_page_scr_mode;

            menu_nav_get_crnt_page(&ui4_page_id);

            if (ui4_page_id == ui4_g_menu_page_scr_mode)
            {
                tv_state |= TV_STATE_OSD_POP_UP_MASK;
            }
            else
            {
                if (b_menu_slider)
                {
                    tv_state |= TV_STATE_OSD_POP_UP_MASK;
                }
                else if (b_menu_pic_page)
                {
                    tv_state |= TV_STATE_SIDEBAR_PIC_SETTING_MASK;
                }
                else
                {
                    tv_state |= TV_STATE_SIDEBAR_NOT_PIC_SETTING_MASK;
                }

            }

        }
        else if (c_strcmp(ac_app_name, MMP_NAME) == 0)
        {
            //b_mmp_resume = TRUE;

            if (a_mmp_be_get_media_type() == MMP_BE_BROWSER_MEDIA_TYPE_AUDIO
                || a_mmp_be_get_media_type() == MMP_BE_BROWSER_MEDIA_TYPE_PHOTO)
            {
                tv_state |= TV_STATE_FULL_SCREEN_GRAPHIC_MASK;
            }
            else //if (a_mmp_be_get_media_type() == MMP_BE_BROWSER_MEDIA_TYPE_VIDEO)
            {
                e_mmp_browser_status = a_mmp_get_av_stat();
                if (MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING == e_mmp_browser_status
                    || MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING == e_mmp_browser_status
                    || MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING == e_mmp_browser_status
                    || MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING == e_mmp_browser_status)
                {
                    tv_state |= TV_STATE_FULL_SCREEN_VID_MASK;
                }
                else
                {
                    tv_state |= TV_STATE_FULL_SCREEN_GRAPHIC_MASK;
                }
            }

        }
        else if (c_strcmp(ac_app_name, WZD_NAME) == 0)
        {
            //b_wzd_resume = TRUE;
            tv_state |= TV_STATE_FULL_SCREEN_GRAPHIC_MASK;
        }
        else if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
        {
            //b_mscvt_resume = TRUE;

            if (b_audio_only || !b_video)
            {
                tv_state |= TV_STATE_FULL_SCREEN_GRAPHIC_MASK;
            }
            else
            {
                tv_state |= TV_STATE_FULL_SCREEN_VID_MASK;
            }
        }
#ifdef APP_WFD_SUPPORT
        else if (c_strcmp(ac_app_name, WFD_NAME) == 0)
        {
            if (a_wfd_is_rtsp_play_status() == TRUE)
            {
                tv_state |= TV_STATE_FULL_SCREEN_VID_MASK;
            }
            else
            {
                tv_state |= TV_STATE_SIDEBAR_NOT_PIC_SETTING_MASK;
            }
        }
#endif
        else
        {
            tv_state |= TV_STATE_FULL_SCREEN_VID_MASK;
        }
    }while(0);

    a_tv_state_mask_state(tv_state);

}

VOID _tv_state_tm_cb(HANDLE_T pt_tm_handle, VOID *pv_tag)
{
    a_agent_async_invoke(_tv_state_detector, NULL, 0);
}

static UINT8 _tv_sate_is_comp_dup(TVSTATE_COMP_T *pt_ts_comp)
{
    UINT8   ui1_ret = TS_COMP_NOT_DUPLICATE;
    TVSTATE_UTIL_T*     pt_ts = &t_g_ts_util;

    if (pt_ts_comp != NULL
        && pt_ts_comp->e_ts_comp_id < pt_ts->ui1_comp_num)
    {
        if (pt_ts->pt_comp[pt_ts_comp->e_ts_comp_id].b_reg)
        {
            ui1_ret = pt_ts_comp->e_ts_comp_id;
        }
    }

    return ui1_ret;
}

#ifdef APP_PORTING
VOID _tv_state_context_switch_nfy_fct (
                                    VOID*                       pv_tag1,
                                    SIZE_T                      z_size
                                    )
{
    SVCTX_LISTENER_MSG      t_msg_listener;
    SVCTX_LISTENER_MSG      *pt_msg_listener = (SVCTX_LISTENER_MSG *)pv_tag1;
    CHAR                    ac_app_name[APP_NAME_MAX_LEN+1] = {0};
    MMP_BE_BROWSER_STATUS_T e_mmp_browser_status = MMP_BE_BROWSER_STATUS_NONE;

    if (NULL == pt_msg_listener)
    {
        DBG_ERROR (("<TVSTATE> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__));
        return;
    }

    c_memset(&t_msg_listener, 0, sizeof(t_msg_listener));
    c_memcpy(&t_msg_listener, pt_msg_listener, z_size);
    //c_mem_free(pt_msg_listener);

    DBG_INFO(("%s(): t_msg_listener=[%d, %d, %d, %d, %d], size = %d\n",
                                        __FUNCTION__,
                                        t_msg_listener.t_sink_disp,
                                        t_msg_listener.e_nfy_cond,
                                        t_msg_listener.e_code,
                                        t_msg_listener.e_stream_type,
                                        (UINT32)t_msg_listener.pv_nfy_tag,
                                        z_size));

    switch (t_msg_listener.e_code)
    {
        /*start screen saver when receive these notifies*/
#ifdef MW_NOTIFY_MMP_PAUSE
        case SVCTX_NTFY_CODE_MEDIA_PAUSE_STATUS:
#endif
        case SVCTX_NTFY_CODE_SIGNAL_LOSS:
        case SVCTX_NTFY_CODE_NO_AUDIO_VIDEO_SVC:
            b_no_signal = TRUE;
            b_video = FALSE;
            break;
        case SVCTX_NTFY_CODE_AUDIO_ONLY_STRM:
        case SVCTX_NTFY_CODE_AUDIO_ONLY_SVC:
        {
            DBG_INFO(("%s(): Receive svctx nfy code [%d]\n", __FUNCTION__, t_msg_listener.e_code));
            b_no_signal = FALSE;
            b_audio_only = TRUE;
            b_video = FALSE;
            break;
        }

        /*stop screen saver when receive these notifies*/
        case SVCTX_NTFY_CODE_SIGNAL_LOCKED:
        case SVCTX_NTFY_CODE_VIDEO_ONLY_STRM:
        case SVCTX_NTFY_CODE_VIDEO_ONLY_SVC:
        case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
        case SVCTX_NTFY_CODE_AUDIO_VIDEO_SVC:
        case SVCTX_NTFY_CODE_MEDIA_SPEED_UPDATE:
        case SVCTX_NTFY_CODE_STOPPED:
        {
            DBG_INFO(("%s(): Receive svctx nfy code [%d]\n", __FUNCTION__, t_msg_listener.e_code));

            b_audio_only = FALSE;
            b_no_signal = FALSE;
            b_video = TRUE;

            e_mmp_browser_status = a_mmp_get_av_stat();

            if (c_strcmp(ac_app_name, MMP_NAME)== 0
                && (a_mmp_be_get_media_type() == MMP_BE_BROWSER_MEDIA_TYPE_AUDIO))
            {
                b_audio_only = TRUE;
                break;
            }

            break;
        }
        default:
            break;
    }
}

VOID _tv_state_svctx_generic_listener(
                 SVCTX_SINK_DISP_T       t_sink_disp,
                 SVCTX_COND_T            e_nfy_cond,       /* in  */
                 SVCTX_NTFY_CODE_T       e_code,           /* in  */
                 STREAM_TYPE_T           e_stream_type,    /* in  */
                 VOID*                   pv_nfy_tag)
{
    if(pv_nfy_tag != NULL
        && TV_STATE_SCVX_LISTENER_TAG == (UINT32)pv_nfy_tag)
    {
        SIZE_T t_size = sizeof(SVCTX_LISTENER_MSG);
        SVCTX_LISTENER_MSG *pt_msg_listener = NULL;

        pt_msg_listener = (SVCTX_LISTENER_MSG*)c_mem_alloc(t_size);
        if (NULL == pt_msg_listener)
        {
            DBG_ERROR (("<NAV_SCRN_BLANK> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__));
            return;
        }
        c_memset(pt_msg_listener, 0, t_size);

        pt_msg_listener->t_sink_disp = t_sink_disp;
        pt_msg_listener->e_nfy_cond = e_nfy_cond;
        pt_msg_listener->e_code = e_code;
        pt_msg_listener->e_stream_type = e_stream_type;
        pt_msg_listener->pv_nfy_tag = pv_nfy_tag;


        a_agent_async_invoke(_tv_state_context_switch_nfy_fct,
                                    (VOID *)pt_msg_listener,
                                    t_size);

        c_mem_free(pt_msg_listener);
        pt_msg_listener = NULL;
    }

}
#endif

static VOID _tvstat_yahoo_stat_proc(VOID* pv_tag1, SIZE_T z_size)
{
    return;
}

static INT32 _tvstat_yahoo_state_nfy_func(UINT16 ui2_nfy_id,
                                            VOID* pv_tag,
                                            ICL_NOTIFY_DATA_T* pt_notify_data)
{
    INT32  i4_ret;
    ICL_GRPID_TYPE e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    SIZE_T z_size ;
    UINT8      ui1_icl_mask,ui1_info_status;

    if (e_grp_id != ICL_GRPID_CUSTOM_NW_WIDGET)
    {
        return TSR_OK;
    }

    ui1_icl_mask = ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS;
    z_size = ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CUSTOM_NW_WIDGET, ui1_icl_mask),
                       &ui1_info_status,
                       &z_size);

    TVSTATE_LOG_ON_FAIL(i4_ret);

    ui4_yahoo_stat = ui1_info_status;

    DBG_INFO(("%s() ui4_yahoo_stat = %d\n", __FUNCTION__, ui4_yahoo_stat));

    a_agent_async_invoke(_tvstat_yahoo_stat_proc, NULL, 0);

    return TSR_OK;
}

/*-----------------------------------------------------------------------------
                    static function declarations
----------------------------------------------------------------------------*/
BOOL a_tv_state_chk_state(UINT32 tv_mask)
{
    BOOL b_ret = TRUE;
    TVSTATE_UTIL_T*    pt_ts = &t_g_ts_util;

    b_ret = TS_VALID_MASK(tv_mask);

    //_TS_LOCK(pt_ts);
    if (pt_ts->tv_state & tv_mask)
    {
        b_ret = b_ret && TRUE;
    }
    else
    {
        b_ret = FALSE;
    }
    //_TS_UNLOCK(pt_ts);

    return b_ret;
}

INT32 a_tv_state_get_state(UINT32 *ptv_mask)
{
    TVSTATE_UTIL_T*    pt_ts = &t_g_ts_util;

    *ptv_mask = pt_ts->tv_state;

    return TSR_OK;
}
INT32 a_tv_state_mask_state(UINT32 tv_mask)
{
    INT32  i4_ret = TSR_OK;
    UINT8  ui1_i = 0;
    TVSTATE_UTIL_T*    pt_ts = &t_g_ts_util;

    _TS_LOCK(pt_ts);
    do {
        if (TS_VALID_MASK(tv_mask))
        {
            if (pt_ts->tv_state == tv_mask)
            {
                break;
            }
            pt_ts->tv_state = tv_mask;

            for (ui1_i = 0; ui1_i < pt_ts->ui1_comp_num; ui1_i++)
            {
                if (pt_ts->pt_comp[ui1_i].b_reg
                    && pt_ts->pt_comp[ui1_i].pf_proc)
                {
                    a_agent_async_invoke(pt_ts->pt_comp[ui1_i].pf_proc,
                                        (VOID *)&tv_mask,
                                        sizeof(tv_mask));
                }
            }

        }
    }while(0);
    _TS_UNLOCK(pt_ts);

    return i4_ret;
}

INT32 a_tv_state_unmask_state(UINT32 tv_mask)
{
    INT32  i4_ret = TSR_OK;
    UINT8  ui1_i = 0;
    TVSTATE_UTIL_T*    pt_ts = &t_g_ts_util;

    _TS_LOCK(pt_ts);
    do {
        if (!a_tv_state_chk_state(tv_mask))
        {
            break;
        }

        if (TS_VALID_MASK(tv_mask))
        {
            pt_ts->tv_state = (pt_ts->tv_state & (~tv_mask));

            for (ui1_i = 0; ui1_i < pt_ts->ui1_comp_num; ui1_i++)
            {
                if (pt_ts->pt_comp[ui1_i].b_reg
                    && pt_ts->pt_comp[ui1_i].pf_proc)
                {
                    a_agent_async_invoke(pt_ts->pt_comp[ui1_i].pf_proc,
                                        (VOID *)&tv_mask,
                                        sizeof(tv_mask));
                }
            }
        }
    }while(0);
    _TS_UNLOCK(pt_ts);

    return i4_ret;
}

INT32 a_tv_state_reg(TVSTATE_COMP_T *pt_ts_comp)
{
    INT32 i4_ret = TSR_OK;
    TVSTATE_UTIL_T*    pt_ts = &t_g_ts_util;

    if (_tv_sate_is_comp_dup(pt_ts_comp) != TS_COMP_NOT_DUPLICATE)
    {
        return TSR_OK;
    }

    if (pt_ts->pt_comp != NULL
        && pt_ts_comp != NULL
        && pt_ts_comp->e_ts_comp_id < TS_COMP_TYPE_LAST)
    {
        pt_ts->pt_comp[pt_ts_comp->e_ts_comp_id].b_reg = TRUE;
        pt_ts->pt_comp[pt_ts_comp->e_ts_comp_id].e_ts_comp_id = pt_ts_comp->e_ts_comp_id;
        pt_ts->pt_comp[pt_ts_comp->e_ts_comp_id].pf_proc = pt_ts_comp->pf_proc;
    }
    else
    {
        i4_ret = TSR_INV_ARG;
        DBG_INFO(("[TVSTATE] %s() regist failed!! \n", __FUNCTION__));
    }

    return i4_ret;
}

/**
 * @brief   The tv state init.
 * @param   VOID
 * @retval  TSR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_tv_state_init(VOID)
{
    INT32 i4_ret = TSR_OK;
    TVSTATE_UTIL_T*    pt_ts = &t_g_ts_util;

    c_memset( pt_ts, 0, sizeof(TVSTATE_UTIL_T) );

    /* allocate API mutex */
    i4_ret = c_sema_create(&pt_ts->h_mtx,
                        X_SEMA_TYPE_MUTEX,
                        X_SEMA_STATE_UNLOCK);
    TVSTATE_CHK_FAIL(i4_ret);

    i4_ret = c_timer_create(&(pt_ts->h_timer));
    TVSTATE_CHK_FAIL(i4_ret);

#if 0
    i4_ret = c_timer_start(pt_ts->h_timer,
                            TS_TIMEER_DELAY,
                            X_TIMER_FLAG_REPEAT,
                            _tv_state_tm_cb,
                            NULL);
    TVSTATE_CHK_FAIL(i4_ret);
#endif
    pt_ts->tv_state = TV_STATE_FULL_SCREEN_VID_MASK;
    pt_ts->ui1_comp_num = TS_COMP_TYPE_LAST;

    if (0 == pt_ts->ui1_comp_num)
    {
        DBG_INFO(("[TVSTATE] %s() no component registed\n", __FUNCTION__));
        return TSR_OK;
    }

    pt_ts->pt_comp = (TVSTATE_COMP_T*)c_mem_alloc(sizeof(TVSTATE_COMP_T) * (pt_ts->ui1_comp_num));

    if (NULL == pt_ts->pt_comp)
    {
        DBG_INFO(("[TVSTATE] %s() alloc memery error!\n", __FUNCTION__));
        return TSR_OK;
    }

    c_memset(pt_ts->pt_comp, 0, sizeof(TVSTATE_COMP_T) * (pt_ts->ui1_comp_num));

#ifdef APP_PORTING
    c_svctx_register_generic_listener(_tv_state_svctx_generic_listener,
                                        (VOID*)TV_STATE_SCVX_LISTENER_TAG,
                                        &ui2_ts_scvx_listener_idx);
#endif
    i4_ret = a_icl_notify_reg(ICL_GRPID_CUSTOM_NW_WIDGET,
                              ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS,
                              NULL,
                              NULL,
                              _tvstat_yahoo_state_nfy_func,
                              &ui2_yahoo_state_nfy);

    MENU_CHK_FAIL(i4_ret);
    a_smart_dim_init();

    return TSR_OK;
}

VOID a_tv_state_set_menu_slider(BOOL b_flag)
{
    b_menu_slider = b_flag;
}

VOID a_tv_state_set_menu_pic_page(BOOL b_flag)
{
    b_menu_pic_page = b_flag;
}

INT32 a_tv_state_detector_stop(VOID)
{
    INT32   i4_ret = TSR_OK;
    UINT8   ui1_i = 0;
    TVSTATE_UTIL_T*    pt_ts = &t_g_ts_util;

    i4_ret = c_timer_stop(t_g_ts_util.h_timer);

    pt_ts->tv_state = TV_STATE_UNKNOW;

    for (ui1_i = 0; ui1_i < pt_ts->ui1_comp_num; ui1_i++)
    {
        if (pt_ts->pt_comp[ui1_i].b_reg
            && pt_ts->pt_comp[ui1_i].pf_proc)
        {
            a_agent_async_invoke(pt_ts->pt_comp[ui1_i].pf_proc,
                                (VOID *)&pt_ts->tv_state,
                                sizeof(pt_ts->tv_state));
        }
    }

    return i4_ret;
}

INT32 a_tv_state_detector_start(VOID)
{
    INT32   i4_ret = TSR_OK;
    TVSTATE_UTIL_T*    pt_ts = &t_g_ts_util;

    if (NULL_HANDLE == pt_ts->h_timer)
    {
        return TSR_OK;
    }

    pt_ts->tv_state = TV_STATE_UNKNOW;

    i4_ret = c_timer_start(pt_ts->h_timer,
                            TS_TIMEER_DELAY,
                            X_TIMER_FLAG_REPEAT,
                            _tv_state_tm_cb,
                            NULL);
    TVSTATE_CHK_FAIL(i4_ret);

    return i4_ret;
}


