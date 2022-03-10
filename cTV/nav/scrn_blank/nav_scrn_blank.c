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
 * $RCSfile: scrn_blank.c,v $
 * $Revision: #2 $
 * $Date: 2015/08/10 $
 * $Author: jg_lizhuwang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_sb.h"
#include "u_sb_atsc_eng.h"
#include "u_svctx.h"

#include "c_wgl.h"
#include "c_handle.h"
#include "c_svl.h"
#include "c_svctx.h"
#include "c_evctx.h"
#include "c_uc_str.h"
#include "c_os.h"
#include "app_util/a_icl_common.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "app_client.h"
#include "menu2/menu.h"
#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_mlm.h"
#include "nav/scrn_blank/nav_scrn_blank.h"
#include "nav/scrn_blank/a_nav_scrn_blank.h"
#include "nav/scrn_blank/nav_scrn_blank_cli.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "am/a_am.h"
#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#include "nav/sleep/a_sleep.h"
#include "res/nav/nav_dbg.h"

//#ifdef APP_TPV_FAC
//#include "res/nav/factory/fac_menu/nav_fac.h"
//#endif

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define SCRN_BLANK_SCVX_LISTENER_TAG               ((UINT32)1)
#define SCRN_BLANK_DELAY_TO_BLANK_TIMEOUT          (20*1000) /* 20s */

#define _ENABLE_LOG_                               1

#if _ENABLE_LOG_
#define _PRINT_LOG \
{\
    if (b_log_open) \
        {DBG_LOG_PRINT(("%s(): FILE:%s LINE: %d\n", __FUNCTION__, __FILE__, __LINE__));}\
}

#define _USER_DBG_LOG(_stmt) \
{\
    if (b_log_open)\
    {DBG_INFO (_stmt);}    \
}
#else
#define _PRINT_LOG
#define _USER_DBG_LOG(_stmt)
#endif

#define _MSG_SET_MSG_ID(_tv_win_id, _msg_id)                                   \
{                                                                              \
    t_g_scrn_blank.t_msgs[_tv_win_id].e_type        = SCRN_BLANK_MSG_TYPE_MSG_ID;  \
    t_g_scrn_blank.t_msgs[_tv_win_id].u.e_msg_id    = _msg_id;                   \
}

#define _MSG_SET_MLM_KEY(_tv_win_id, _mlm_key)                                 \
{                                                                              \
    t_g_scrn_blank.t_msgs[_tv_win_id].e_type        = SCRN_BLANK_MSG_TYPE_MLM_KEY; \
    t_g_scrn_blank.t_msgs[_tv_win_id].u.ui2_mlm_key = _mlm_key;                  \
}

#define _MSG_SET_UNKNOWN(_tv_win_id)                                           \
{                                                                              \
    t_g_scrn_blank.t_msgs[_tv_win_id].e_type = SCRN_BLANK_MSG_TYPE_UNKNOWN;        \
}

typedef struct _SVCTX_LISTENER_MSG
{
    SVCTX_SINK_DISP_T       t_sink_disp;
    SVCTX_COND_T            e_nfy_cond;
    SVCTX_NTFY_CODE_T       e_code;
    STREAM_TYPE_T           e_stream_type;
    VOID*                   pv_nfy_tag;
}SVCTX_LISTENER_MSG;
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static UINT16 ui2_scrn_blank_state = NAV_SCRN_BLANK_STATE_UNKNOW;
static UINT16 ui2_scrn_blank_scvx_listener_idx = 0;
static BOOL b_3rd_audio_only = FALSE;
static BOOL b_vid_play = TRUE;
static BOOL b_ch_locked = FALSE;
static UINT16 ui2_yahoo_state_nfy = 0;
static AM_CLIENT_STATE ui4_yahoo_stat = YAHOO_STATUS_HIDE;

BOOL b_log_open = FALSE;
MM_SPEED_TYPE_T e_g_speed_type = MM_SPEED_TYPE_FORWARD_1X;

SCRN_BLANK_T  t_g_scrn_blank;

extern BOOL menu_custom_is_blank_screen(VOID);
extern INT32 menu_custom_blank_screen(VOID);
extern INT32 menu_custom_unblank_screen(UINT32 ui4_keycode);
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _scrn_blank_check_to_activate(
                    SCRN_BLANK_T*                 pt_this,
                    BOOL                        b_from_timeout
                    );
static INT32 _scrn_blank_hide(VOID);
static INT32 _scrn_blank_reset(VOID);
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static VOID _scrn_blank_set_3rd_audio_only(SVCTX_NTFY_CODE_T e_nfy_code)
{
    _USER_DBG_LOG(("%s(): Receive svctx nfy code [%d]\n", __FUNCTION__, e_nfy_code));

    do {
        if (a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED)
        {
            b_3rd_audio_only = FALSE;
            break;
        }

        switch (e_nfy_code)
        {
            case SVCTX_NTFY_CODE_AUDIO_ONLY_STRM:
            case SVCTX_NTFY_CODE_AUDIO_ONLY_SVC:
            {
                b_3rd_audio_only = TRUE;
                break;
            }

            case SVCTX_NTFY_CODE_VIDEO_ONLY_STRM:
            case SVCTX_NTFY_CODE_VIDEO_ONLY_SVC:
            case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
            case SVCTX_NTFY_CODE_AUDIO_VIDEO_SVC:
            {
                b_3rd_audio_only = FALSE;
                break;
            }
            default:
                break;
        }
    }while (0);

    _USER_DBG_LOG(("%s(): b_3rd_audio_only = %d\n", __FUNCTION__, b_3rd_audio_only));
}

VOID _scrn_blank_context_switch_nfy_fct (
                                    VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3
                                    )
{
    SVCTX_LISTENER_MSG      t_msg_listener;
    SVCTX_LISTENER_MSG      *pt_msg_listener = (SVCTX_LISTENER_MSG *)pv_tag1;
    SIZE_T                  t_size = (SIZE_T)pv_tag2;
    MM_SPEED_TYPE_T         e_speed_type = MM_SPEED_TYPE_FORWARD_1X;
    SIZE_T                  get_info_size = sizeof(MM_SPEED_TYPE_T);
    MEDIA_FORMAT_T          t_media_fmt = {0};
    SIZE_T                  get_mm_fmt_size = sizeof(MEDIA_FORMAT_T);
    CHAR                    ac_app_name[APP_NAME_MAX_LEN+1] = {0};
    MMP_BE_BROWSER_STATUS_T e_mmp_browser_status = MMP_BE_BROWSER_STATUS_NONE;

    if (NULL == pt_msg_listener)
    {
        DBG_ERROR (("<NAV_SCRN_BLANK> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__));
        return;
    }

    a_am_get_active_app(ac_app_name);
    /* Nothing to be done while menu resumed */
    if (nav_is_active() == FALSE
        && c_strcmp(ac_app_name, MMP_NAME) != 0
        && a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED)
    {
        if (pt_msg_listener != NULL)
        {
            c_mem_free(pt_msg_listener);
            pt_msg_listener = NULL;
        }
        _USER_DBG_LOG(("%s(): navigator is not active\n", __FUNCTION__));
        return;
    }

    c_memset(&t_msg_listener, 0, sizeof(t_msg_listener));
    c_memcpy(&t_msg_listener, pt_msg_listener, t_size);
    c_mem_free(pt_msg_listener);

    SCRN_BLANK_T* pt_this   = &t_g_scrn_blank;

    _USER_DBG_LOG(("%s(): t_msg_listener=[%d, %d, %d, %d, %d], size = %d\n",
                                        __FUNCTION__,
                                        t_msg_listener.t_sink_disp,
                                        t_msg_listener.e_nfy_cond,
                                        t_msg_listener.e_code,
                                        t_msg_listener.e_stream_type,
                                        (UINT32)t_msg_listener.pv_nfy_tag,
                                        t_size));

    _scrn_blank_set_3rd_audio_only(t_msg_listener.e_code);

    switch (t_msg_listener.e_code)
    {
        /*start screen saver when receive these notifies*/
#ifdef MW_NOTIFY_MMP_PAUSE
        case SVCTX_NTFY_CODE_MEDIA_PAUSE_STATUS:
#endif
        /* Disable blank screen for no signal */
        //case SVCTX_NTFY_CODE_SIGNAL_LOSS:
        //case SVCTX_NTFY_CODE_NO_AUDIO_VIDEO_SVC:
        case SVCTX_NTFY_CODE_AUDIO_ONLY_STRM:
        case SVCTX_NTFY_CODE_AUDIO_ONLY_SVC:
        {
            _USER_DBG_LOG(("%s(): Receive svctx nfy code [%d]\n", __FUNCTION__, t_msg_listener.e_code));

            if ((SVCTX_NTFY_CODE_AUDIO_ONLY_STRM == t_msg_listener.e_code
                || SVCTX_NTFY_CODE_AUDIO_ONLY_SVC == t_msg_listener.e_code)
                && a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
            {
                b_3rd_audio_only = TRUE;
            }

            b_vid_play = FALSE;

            if ((NAV_SCRN_BLANK_STATE_TIMER_PHASE1 == ui2_scrn_blank_state
                || NAV_SCRN_BLANK_STATE_TIMER_PHASE2 == ui2_scrn_blank_state
                || NAV_SCRN_BLANK_STATE_BLANK == ui2_scrn_blank_state)
                && b_3rd_audio_only)
            {
                _USER_DBG_LOG(("%s() %d: Audio only app and had been blanked, no need reset.\n", __FUNCTION__,__LINE__));
                break;
            }

            pt_this->b_enable = TRUE;
            //_scrn_blank_check_to_activate(pt_this, FALSE);
            a_scrn_blank_act((VOID*)SCRN_BLANK_CONTEXT_SWITCH_4_RESET, NULL, NULL);
            break;
        }

        /*stop screen saver when receive these notifies*/
        case SVCTX_NTFY_CODE_SIGNAL_LOSS:
        case SVCTX_NTFY_CODE_NO_AUDIO_VIDEO_SVC:
        case SVCTX_NTFY_CODE_SIGNAL_LOCKED:
        case SVCTX_NTFY_CODE_VIDEO_ONLY_STRM:
        case SVCTX_NTFY_CODE_VIDEO_ONLY_SVC:
        case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
        case SVCTX_NTFY_CODE_AUDIO_VIDEO_SVC:
        case SVCTX_NTFY_CODE_MEDIA_SPEED_UPDATE:
        case SVCTX_NTFY_CODE_STOPPED:
        {
            _USER_DBG_LOG(("%s(): Receive svctx nfy code [%d]\n", __FUNCTION__, t_msg_listener.e_code));

            b_vid_play = TRUE;
            if ((NAV_SCRN_BLANK_STATE_TIMER_PHASE1 == ui2_scrn_blank_state
                || NAV_SCRN_BLANK_STATE_TIMER_PHASE2 == ui2_scrn_blank_state
                || NAV_SCRN_BLANK_STATE_BLANK == ui2_scrn_blank_state)
                && b_3rd_audio_only)
            {
                _USER_DBG_LOG(("%s() %d: Audio only app and had been blanked, no need reset.\n", __FUNCTION__,__LINE__));
                break;
            }

            if (SVCTX_NTFY_CODE_MEDIA_SPEED_UPDATE == t_msg_listener.e_code )
            {
                #if 0
                c_svctx_generic_get_info (menu_get_crnt_svctx(),
                                            NULL_HANDLE,
                                            SVCTX_MM_GET_TYPE_MEDIA_FORMAT,
                                            &(t_divx_drm_generic_info.t_divx_drm_registration_info.s_registration_code),
                                            sizeof(DIVX_DRM_UNION_GENERIC_INFO_T)
                                            );
                #else
                /* get media info for 3rd */
                c_svctx_get(pt_this->h_main_svctx,
                            SVCTX_MM_GET_TYPE_MEDIA_FORMAT,
                            (VOID *)&t_media_fmt,
                            (SIZE_T *)&get_mm_fmt_size);
                #endif

                c_svctx_get(pt_this->h_main_svctx,
                            SVCTX_MM_GET_TYPE_SPEED,
                            (VOID *)&e_speed_type,
                            (SIZE_T *)&get_info_size);

                e_mmp_browser_status = a_mmp_get_av_stat();

                _USER_DBG_LOG(("%s(): e_mmp_browser_status = %d, e_speed_type = %d, e_mm_svc_type = %d\n",
                                                            __FUNCTION__,
                                                            e_mmp_browser_status,
                                                            e_speed_type,
                                                            t_media_fmt.e_mm_svc_type));

                e_g_speed_type = e_speed_type;

                if (MM_SPEED_TYPE_PAUSE == e_speed_type)
                {
                    _USER_DBG_LOG(("%s() Line: %d not stop timer\n", __FUNCTION__, __LINE__));

                    pt_this->b_enable = TRUE;
                    a_scrn_blank_act((VOID*)SCRN_BLANK_CONTEXT_SWITCH_4_RESET, NULL, NULL);
                    break;
                }

                if (c_strcmp(ac_app_name, MMP_NAME)== 0
                    && (a_mmp_be_get_media_type() == MMP_BE_BROWSER_MEDIA_TYPE_AUDIO
                        || t_media_fmt.e_mm_svc_type == MEDIA_SVC_TYPE_AUDIO_ONLY
                       ))
                {
                    _USER_DBG_LOG(("%s() Line: %d not stop timer\n", __FUNCTION__, __LINE__));

                    pt_this->b_enable = TRUE;
                    a_scrn_blank_act((VOID*)SCRN_BLANK_CONTEXT_SWITCH_4_RESET, NULL, NULL);
                    break;
                }
            }

            if (b_3rd_audio_only)
            {
                /* Not set b_enable to false even acfg setting is off */
                _USER_DBG_LOG(("%s() %d: Audio only app and blank screen is off, no need reset.\n", __FUNCTION__,__LINE__));
                break;
            }

            pt_this->b_enable = FALSE;
            _USER_DBG_LOG(("%s() b_enable set to %d\n\n", __FUNCTION__, pt_this->b_enable));

            if (SVCTX_NTFY_CODE_STOPPED == t_msg_listener.e_code
                || SVCTX_NTFY_CODE_SIGNAL_LOCKED == t_msg_listener.e_code)
            {
                if (c_strcmp(ac_app_name, MMP_NAME) != 0
                    && a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED)
                {
                    /* Only MMP & 3RD stopped can stop timer */
                    pt_this->b_enable = TRUE;
                }

                e_g_speed_type = MM_SPEED_TYPE_FORWARD_1X;

                if (c_strcmp(ac_app_name, MMP_NAME) == 0
                    && a_mmp_be_get_media_type() == MMP_BE_BROWSER_MEDIA_TYPE_AUDIO)
                {
                    /* MMP audio can enable */
                    pt_this->b_enable = TRUE;
                }

                if (SVCTX_NTFY_CODE_SIGNAL_LOCKED == t_msg_listener.e_code)
                {
                    if (b_ch_locked)
                    {
                        break;
                    }
                    b_ch_locked = TRUE;
                }
            }
            else if (SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE == t_msg_listener.e_code)
            {
                b_ch_locked = FALSE;
            }

            if (nav_is_component_visible(NAV_COMP_ID_SCRN_BLANK))
            {
                nav_hide_component(NAV_COMP_ID_SCRN_BLANK);
            }
            else
            {
                _scrn_blank_hide();
            }
            //menu_custom_unblank_screen();
            break;
        }
        default:
            break;
    }
}

VOID _nav_scrn_blank_svctx_generic_listener(
                 SVCTX_SINK_DISP_T       t_sink_disp,
                 SVCTX_COND_T            e_nfy_cond,       /* in  */
                 SVCTX_NTFY_CODE_T       e_code,           /* in  */
                 STREAM_TYPE_T           e_stream_type,    /* in  */
                 VOID*                   pv_nfy_tag)
{
    _USER_DBG_LOG(("=============Genereic listener ===============\n"));
    _USER_DBG_LOG(("sink disp     = %4d\n", t_sink_disp));
    _USER_DBG_LOG(("e_nfy_cond    = %4d\n", e_nfy_cond));
    _USER_DBG_LOG(("e_code        = %4d\n", e_code));
    _USER_DBG_LOG(("e_stream_type = %4d\n", e_stream_type ));

    if(pv_nfy_tag != NULL
        && SCRN_BLANK_SCVX_LISTENER_TAG == (UINT32)pv_nfy_tag)
    {
        _USER_DBG_LOG(("*pv_nfy_tag    =%4d\n", (UINT32)(pv_nfy_tag)));

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


        nav_request_context_switch(_scrn_blank_context_switch_nfy_fct,
                                    (VOID *)pt_msg_listener,
                                    (VOID *)t_size,
                                    (VOID *)NULL);

        //c_mem_free(pt_msg_listener);
        pt_msg_listener = NULL;
    }

    _USER_DBG_LOG(("============================================\n"));

}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_show_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _scrn_blank_show_msg(
                    VOID
                    )
{
    SCRN_BLANK_T*   pt_this = &t_g_scrn_blank;

#if 0
    UTF16_T         w2s_string[256] = {0};
    CHAR            s_string[256] = {0};
    CHAR            s_string_tmp[256] = {0};
    CHAR            ps_tmp = NULL;

    c_uc_w2s_to_ps(MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_SCRN_BLANK_MSG), s_string, 255);

    ps_tmp = c_strchr(s_string, '{');
    *ps_tmp = 0;
    c_sprintf(s_string_tmp, "%s%d%s",
                            s_string,
                            SCRN_BLANK_DELAY_TO_BLANK_TIMEOUT,
                            ps_tmp+3);

    c_uc_ps_to_w2s(s_string_tmp, w2s_string, 255);
#endif

    return scrn_blank_view_show(
                    &(pt_this->t_view),
                    MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_SCRN_BLANK_MSG)
                    );
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svctx_nfy_fct
 * Description
 *  Do some dirty trick
 *  - hide screen saver in service context's thread to avoid
 *    video and OSD not controlled in the same thread
 *  6/29/2007 Weider Chang (wait better solution to replace this)
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_svctx_nfy_fct(
                    HANDLE_T                        h_svctx,
                    SVCTX_COND_T                    e_nfy_cond,
                    SVCTX_NTFY_CODE_T               e_code,
                    STREAM_TYPE_T                   e_stream_type,
                    VOID*                           pv_nfy_tag
                    )
{
#if 0
    SCRN_BLANK_T* pt_this = &t_g_scrn_blank;

    switch(e_code) {
    case SVCTX_NTFY_CODE_SIGNAL_LOCKED:
        break;

    case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
        if (e_code == SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE)
        {
            VSH_SRC_RESOLUTION_INFO_T t_res;
            INT32                     i4_ret;

            c_memset (&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T)) ;
            i4_ret = nav_get_crnt_video_res_info(TV_WIN_ID_MAIN, &t_res);
            if (i4_ret == NAVR_OK && (t_res.ui4_width == 0 || t_res.ui4_height == 0))
            {
                /* invalid resolution */
                break;
            }
        }

        if (pt_this->b_is_on == FALSE) {
            break;
        }

        scrn_blank_view_hide(&pt_this->t_view);
        break;
    default:
        break;
    }
#endif
}

static INT32 _nav_scrn_blank_key_moniter(
    UINT32                             ui4_msg,
    VOID*                              pv_ui4_key_code,
    VOID*                              pv_ui4_time_stamp,
    VOID*                              pv_tag)
{
    INT32                   i4_ret = NAVR_OK;
#if 0
    UINT32                  ui4_key_code = (UINT32)pv_ui4_key_code;
    SCRN_BLANK_T*           pt_this = (SCRN_BLANK_T*)pv_tag;

    NAV_ASSERT(pt_this);

    if(WGL_MSG_KEY_UP != ui4_msg
        && ui4_key_code != BTN_VOL_UP
        && ui4_key_code != BTN_VOL_DOWN
        && ui4_key_code != BTN_MUTE)
    {
        if(NAV_SCRN_BLANK_STATE_BLANK == ui2_scrn_blank_state)
        {
            /*hide ui*/
            nav_hide_component(NAV_COMP_ID_SCRN_BLANK);
            i4_ret = NAVR_DO_NOT_CONTINUE
        }
        else if (NAV_SCRN_BLANK_STATE_TIMER_PHASE1 == ui2_scrn_blank_state
                || NAV_SCRN_BLANK_STATE_TIMER_PHASE2 == ui2_scrn_blank_state)
        {
            _scrn_blank_reset();
        }
        else
        {
            //Do nothing
        }
    }
#else
    UINT32 ui4_key_code = (UINT32)pv_ui4_key_code;

    if (WGL_MSG_KEY_UP == ui4_msg)
    {
        return i4_ret;
    }

    if (t_g_scrn_blank.b_is_on || t_g_scrn_blank.b_msg_visible)
    {
        switch (ui4_key_code)
        {
            case BTN_MUTE:
            case BTN_VOL_DOWN:
            case BTN_VOL_UP:
            case BTN_BLANK_SCREEN:
            case BTN_INVALID:
                break;
            default:
                t_g_scrn_blank.b_enable = TRUE;
                _scrn_blank_reset();
                break;
        }
    }

#endif
    return i4_ret;
}

static VOID _scrn_blank_yahoo_stat_proc(VOID*                       pv_tag1,
                                        VOID*                       pv_tag2,
                                        VOID*                       pv_tag3)
{
    _scrn_blank_reset();
}

static INT32 _scrn_blank_yahoo_state_nfy_func(UINT16 ui2_nfy_id,
                                            VOID* pv_tag,
                                            ICL_NOTIFY_DATA_T* pt_notify_data)
{
    INT32  i4_ret;
    ICL_GRPID_TYPE e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    SIZE_T z_size ;
    UINT8      ui1_icl_mask,ui1_info_status;

    if (e_grp_id != ICL_GRPID_CUSTOM_NW_WIDGET)
    {
        return NAVR_OK;
    }

    ui1_icl_mask = ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS;
    z_size = ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CUSTOM_NW_WIDGET, ui1_icl_mask),
                       &ui1_info_status,
                       &z_size);

    NAV_CHK_FAIL(i4_ret);

    ui4_yahoo_stat = ui1_info_status;

    _USER_DBG_LOG(("%s() ui4_yahoo_stat = %d\n", __FUNCTION__, ui4_yahoo_stat));

    nav_request_context_switch(_scrn_blank_yahoo_stat_proc, NULL, NULL, NULL);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_blank_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    SCRN_BLANK_T* pt_this = &t_g_scrn_blank;
    INT32       i4_ret  = NAVR_OK;

    pt_this->ui4_timeout                   = SCRN_BLANK_DELAY_TO_BLANK_TIMEOUT;
    pt_this->b_is_on                       = FALSE;
    pt_this->b_msg_visible                 = FALSE;
    pt_this->b_delay_to_activate           = FALSE;
    pt_this->t_msgs[TV_WIN_ID_MAIN].e_type = SCRN_BLANK_MSG_TYPE_UNKNOWN;
    pt_this->t_msgs[TV_WIN_ID_SUB].e_type  = SCRN_BLANK_MSG_TYPE_UNKNOWN;
    pt_this->h_main_svctx                  = NULL_HANDLE;
    pt_this->b_enable                      = TRUE;
    pt_this->b_phase1                      = TRUE;

    _USER_DBG_LOG(("%s()\n", __FUNCTION__));

    i4_ret = c_timer_create(&pt_this->h_timer);
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_tv_open(
                    SVCTX_NAME_MAIN,
                    _scrn_svctx_nfy_fct,
                    NULL,
                    &pt_this->h_main_svctx
                    );
    if(i4_ret != TVR_OK){
        return NAVR_FAIL;
    }

    i4_ret = scrn_blank_view_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset,
                    pt_ctx->t_gui_res.e_color_type
                    );

    nav_register_key_monitor_nty_fct(NAV_COMP_ID_SCRN_BLANK, _nav_scrn_blank_key_moniter, pt_this);

    c_svctx_register_generic_listener(_nav_scrn_blank_svctx_generic_listener,
                                        (VOID*)SCRN_BLANK_SCVX_LISTENER_TAG,
                                        &ui2_scrn_blank_scvx_listener_idx);

    i4_ret = a_icl_notify_reg(ICL_GRPID_CUSTOM_NW_WIDGET,
                              ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS,
                              NULL,
                              NULL,
                              _scrn_blank_yahoo_state_nfy_func,
                              &ui2_yahoo_state_nfy);

    MENU_CHK_FAIL(i4_ret);

    _USER_DBG_LOG(("%s() RETURN %d\n", __FUNCTION__, i4_ret));
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_blank_deinit(
                    VOID
                    )
{
    SCRN_BLANK_T* pt_this = &t_g_scrn_blank;
    INT32       i4_ret = NAVR_OK;

    if (c_handle_valid(pt_this->h_timer) == TRUE) {
        c_timer_delete(pt_this->h_timer);
        pt_this->h_timer = NULL_HANDLE;
    }

    i4_ret = scrn_blank_view_deinit(&pt_this->t_view);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    pt_this->ui4_timeout         = 0;
    pt_this->b_is_on             = FALSE;
    pt_this->b_msg_visible       = FALSE;
    pt_this->b_delay_to_activate = FALSE;

    c_svctx_unregister_generic_listener(ui2_scrn_blank_scvx_listener_idx);

    i4_ret = a_icl_notify_unreg(ui2_yahoo_state_nfy);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

#if 0
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_is_subtitle_comp_playing
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _scrn_blank_is_subtitle_comp_playing(
                    TV_WIN_ID_T                 e_tv_win_id
                    )
{
#ifdef APP_DVBT_SUPPORT
  #ifndef APP_SCRN_BLANK_NO_VIDEO_IMPLY_NO_SUBTITLE
    STREAM_COMP_ID_T t_comp_id;
    SCDB_REC_T       t_scdb_rec;
    INT32            i4_ret;
    UINT32           ui4_scrambled_strm = 0;

    i4_ret = nav_get_ca_status(
                    e_tv_win_id,
                    &ui4_scrambled_strm
                    );
    if (i4_ret == NAVR_OK) {
        if ((ui4_scrambled_strm & ST_MASK_SUBTITLE) > 0) {
            return FALSE;
        }
    #ifdef APP_SCRAMBLED_VIDEO_IMPLY_NO_SUBTITLE
        if ((ui4_scrambled_strm & ST_MASK_VIDEO) > 0) {
            return FALSE;
        }
    #endif
    }

    i4_ret = nav_get_using_strm_data(
                    e_tv_win_id,
                    ST_SUBTITLE,
                    &t_comp_id,
                    &t_scdb_rec
                    );
    if (i4_ret == NAVR_OK) {
        return TRUE;
    }
  #endif
#endif
    return FALSE;
}
#endif

#if 0
static BOOL _scrn_blank_check_exclusive_set(VOID)
{
    BOOL    b_exclusive = FALSE;
    BOOL    b_slp_dlg_show = FALSE;
    SCRN_BLANK_T*   pt_this = &t_g_scrn_blank;

    /* next state is to show blank dialog */
    if (pt_this->b_delay_to_activate == TRUE
        && pt_this->b_msg_visible == FALSE
        && pt_this->b_phase1)
    {
        a_nav_get_sleep_prompt_dlg_status(&b_slp_dlg_show);
        if (b_slp_dlg_show)
        {
            b_exclusive = TRUE;
            nav_request_context_switch(a_scrn_blank_act,
                                        (VOID*)SCRN_BLANK_CONTEXT_SWITCH_4_RESET,
                                        NULL,
                                        NULL);
        }
    }

    return b_exclusive;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_is_able_to_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_blank_is_able_to_activate(
                    SCRN_BLANK_T*                 pt_this
                    )
{
    INT32       i4_ret = NAVR_NOT_ALLOW;
#if 0
    CHAR        ac_app_name[APP_NAME_MAX_LEN+1] = {0};
    UINT16      ui2_val = ACFG_CUSTOM_SCRN_BLANK_DISABLE;
    TV_MODE_T   e_tv_mode = TV_MODE_TYPE_LAST_VALID_ENTRY;
    UINT8       ui1_status = 0;
    MMP_BE_BROWSER_STATUS_T e_mmp_browser_status = MMP_BE_BROWSER_STATUS_NONE;
    #if 0
    MEDIA_FORMAT_T          t_media_fmt = {0};
    SIZE_T                  get_mm_fmt_size = sizeof(MEDIA_FORMAT_T);
    #endif
    a_am_get_active_app(ac_app_name);

    _USER_DBG_LOG(("%s(): current active app is [%s]\n", __FUNCTION__, ac_app_name));

    #if 0
    /* get media info for 3rd */
    c_svctx_get(pt_this->h_main_svctx,
                SVCTX_MM_GET_TYPE_MEDIA_FORMAT,
                (VOID *)&t_media_fmt,
                (SIZE_T *)&get_mm_fmt_size);
    #endif

    do {
        if (c_strcmp(ac_app_name, MMP_NAME) == 0)
        {
            if (a_mmp_be_get_media_type() == MMP_BE_BROWSER_MEDIA_TYPE_PHOTO)
            {
                _PRINT_LOG
                break;
            }

            e_mmp_browser_status = a_mmp_get_av_stat();
            _USER_DBG_LOG(("%s(): browser_status=%d\n", __FUNCTION__, e_mmp_browser_status));

            if ((a_mmp_be_get_media_type() == MMP_BE_BROWSER_MEDIA_TYPE_VIDEO
                && (e_mmp_browser_status == MMP_BE_BROWSER_STATUS_VIDEO_LIST_NORMAL_PREVIEW
                    || e_mmp_browser_status == MMP_BE_BROWSER_STATUS_VIDEO_LIST_NOT_PLAYING
                    || e_mmp_browser_status == MMP_BE_BROWSER_STATUS_NONE))
                || (a_mmp_be_get_media_type() == MMP_BE_BROWSER_MEDIA_TYPE_AUDIO
                    && (e_mmp_browser_status != MMP_BE_BROWSER_STATUS_AUDIO_LIST_NOT_PLAYING))
                )
            {
                _PRINT_LOG
                break;
            }
        }

#ifdef APP_MENU_MMP_COEXIST
        /* Menu is pausing and MMP is full screen */
        if (c_strcmp(ac_app_name, MENU_NAME) == 0
            && a_menu_is_resume() == FALSE
            && ((a_mmp_be_get_media_type() == MMP_BE_BROWSER_MEDIA_TYPE_AUDIO
                    && a_mmp_get_av_stat() != MMP_BE_BROWSER_STATUS_AUDIO_LIST_NOT_PLAYING)
                || a_mmp_get_av_stat() == MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING
                #if 0
                || (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED
                    && t_media_fmt.e_mm_svc_type == MEDIA_SVC_TYPE_AUDIO_ONLY)
               #endif
               )
           )
        {
            /* Do nothing */
            _USER_DBG_LOG(("%s() LINE:%d Menu is pausing and MMP is full screen\n", __FUNCTION__, __LINE__));
        }
        else
#endif
        if (nav_is_active() == FALSE
            && a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
        {
            if ((b_3rd_audio_only == TRUE || e_g_speed_type == MM_SPEED_TYPE_PAUSE)
                && a_menu_is_resume() == FALSE)
            {
                /* Do nothing */
                _USER_DBG_LOG(("%s() LINE:%d b_3rd_audio_only=%d, e_g_speed_type=%d\n",
                                                                __FUNCTION__,
                                                                __LINE__,
                                                                b_3rd_audio_only,
                                                                e_g_speed_type));
            }
            else
            {
                _PRINT_LOG
                break;
            }
        }
        else if(nav_is_active() == FALSE
            && c_strcmp(ac_app_name, MMP_NAME) != 0)
        {
            _PRINT_LOG
            break;
        }

        if (nav_is_signal_loss(TV_WIN_ID_MAIN))
        {
            _PRINT_LOG
            break;
        }

        if (nav_get_tv_mode(&e_tv_mode) != NAVR_OK)
        {
            _PRINT_LOG
            break;
        }

        if (e_tv_mode != TV_MODE_TYPE_NORMAL)
        {
            _PRINT_LOG
            break;
        }
        /*
        if (nav_any_component_visible() == TRUE)
        {
            break;
        }
        */
        if (nav_get_focus_id(&pt_this->e_focus_tv_win_id) != NAVR_OK)
        {
            _PRINT_LOG
            break;
        }

        /*if (nav_is_video_content_playing(pt_this->e_focus_tv_win_id) == TRUE)
        {
            _PRINT_LOG
            break;
        }*/

        if (_scrn_blank_is_subtitle_comp_playing(pt_this->e_focus_tv_win_id) == TRUE)
        {
            _PRINT_LOG
            break;
        }

        if (nav_get_active_component() == NAV_COMP_ID_UPDATER
            || nav_is_component_visible(NAV_COMP_ID_UPDATER))
        {
            _PRINT_LOG
            break;
        }

        if (a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_DOCK, &ui1_status) == ICLR_OK)
        {
            if ((ui4_yahoo_stat & YAHOO_STATUS_DOCK_UP )
                || (ui4_yahoo_stat & YAHOO_STATUS_FULLSCREEN_GALLERY)
                || (ui4_yahoo_stat & YAHOO_STATUS_SIDEBAR)
                || (ui4_yahoo_stat & YAHOO_STATUS_FULLSCREN))
            {
                _USER_DBG_LOG(("%s() Line %d: ui4_yahoo_stat = %d, b_3rd_audio_only = %d, e_g_speed_type = %d\n\n",
                                                                                __FUNCTION__,
                                                                                __LINE__,
                                                                                ui4_yahoo_stat,
                                                                                b_3rd_audio_only,
                                                                                e_g_speed_type));
                if ((ui4_yahoo_stat & YAHOO_STATUS_FULLSCREN)
                    && (b_3rd_audio_only == TRUE || e_g_speed_type == MM_SPEED_TYPE_PAUSE))
                {

                }
                else
                {
                    _PRINT_LOG
                    break;
                }
            }
        }

        a_cfg_custom_get_scrn_saver_time(&ui2_val);

        if (ACFG_CUSTOM_SCRN_BLANK_DISABLE == ui2_val)
        {
            _PRINT_LOG
            break;
        }

#ifdef APP_TPV_FAC
        if(a_get_fac_status())
    	{
    		_PRINT_LOG
			break;
    	}
#endif

        if (_scrn_blank_check_exclusive_set() == TRUE)
        {
            _PRINT_LOG
			break;
        }

        i4_ret = NAVR_OK;
    } while (0);
#else
    i4_ret = NAVR_NOT_ALLOW;
#endif
    _USER_DBG_LOG(("%s(): i4_ret = %d\n", __FUNCTION__, i4_ret));

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_blank_stop_timer(
                    SCRN_BLANK_T*                 pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop scrn_blank::h_timer failed!"));
    }

    pt_this->b_is_on = FALSE;

    a_nav_scrn_blank_cli_set_timer_info(0, 0);

    _USER_DBG_LOG(("%s(): screen saver timer stopped\n", __FUNCTION__));

}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static  INT32 _scrn_blank_hide(VOID)
{
    SCRN_BLANK_T* pt_this = &t_g_scrn_blank;
    INT32       i4_ret = NAVR_OK;
    static UINT32 ui4_default_keycode = 1;

    if (TRUE == pt_this->b_is_on)
    {
        _scrn_blank_stop_timer(pt_this);
    }

    if (TRUE == pt_this->b_msg_visible)
    {
        i4_ret = scrn_blank_view_hide(&pt_this->t_view);

        if (i4_ret != NAVR_OK)
        {
            return i4_ret;
        }

        pt_this->b_msg_visible = FALSE;
    }

    pt_this->b_delay_to_activate = FALSE;

    if (NAV_SCRN_BLANK_STATE_BLANK == ui2_scrn_blank_state)
    {
        menu_custom_unblank_screen(ui4_default_keycode);
    }

    ui2_scrn_blank_state = NAV_SCRN_BLANK_STATE_UNKNOW;

    if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
    {
        a_tv_net_send_cmd("\n:dtv_app_mtk,am,:force_dtv_input=off\n");
    }

    /* Timer still be restart */
    _USER_DBG_LOG(("%s() b_enable = %d\n", __FUNCTION__, pt_this->b_enable));
    if (pt_this->b_enable)
    {
        _scrn_blank_check_to_activate(pt_this,FALSE);
    }

    return NAVR_OK;
}

static  INT32 _scrn_blank_reset(VOID)
{
#if 0
    SCRN_BLANK_T* pt_this = &t_g_scrn_blank;
    INT32       i4_ret = NAVR_OK;

    if (pt_this->b_is_on == FALSE
        && pt_this->b_msg_visible == FALSE)
    {
        return NAVR_OK;
    }

    _scrn_blank_stop_timer(pt_this);

    i4_ret = scrn_blank_view_hide(&pt_this->t_view);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    pt_this->b_msg_visible       = FALSE;
    pt_this->b_delay_to_activate = FALSE;
#else
    _USER_DBG_LOG(("%s() ui4_yahoo_stat = %d\n", __FUNCTION__, ui4_yahoo_stat));

    if (nav_is_component_visible(NAV_COMP_ID_SCRN_BLANK))
    {
        nav_hide_component(NAV_COMP_ID_SCRN_BLANK);  //No signal could be showed
    }
    else
    {
        _scrn_blank_hide();
    }
#endif
    //_scrn_blank_check_to_activate(pt_this,FALSE);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_blank_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )

{
    INT32   i4_ret = NAVR_OK;
    CHAR    ac_app_name[APP_NAME_MAX_LEN+1] = {0};
    SCRN_BLANK_T* pt_this = &t_g_scrn_blank;

    switch (pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_APP_PAUSING:
        {
            a_am_get_next_active_app(ac_app_name);

            _USER_DBG_LOG(("%s() NAV_UI_MSG_APP_PAUSING next app name = %s\n", __FUNCTION__, ac_app_name));

            if (c_strcmp(ac_app_name, MMP_NAME) == 0)
            {
                break;
            }

            pt_this->b_enable = FALSE;
            _scrn_blank_hide();

            break;
        }
        case NAV_UI_MSG_POWER_ON:
        case NAV_UI_MSG_APP_INITED:
            if (!(pt_this->b_is_on || pt_this->b_msg_visible))
            {
                //t_g_scrn_blank.b_enable = TRUE;
                _USER_DBG_LOG(("%s() NAV_UI_MSG_APP_INITED b_enable = %d\n", __FUNCTION__, t_g_scrn_blank.b_enable));
                a_scrn_blank_act(NULL, NULL, NULL);
                break;
            }
        default:
            break;
    }
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_handle_delay_to_activate_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_blank_handle_delay_to_activate_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    _scrn_blank_check_to_activate(&t_g_scrn_blank, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_delay_to_activate_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_blank_delay_to_activate_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_scrn_blank_handle_delay_to_activate_timeout, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_reset_delay_to_activate_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_blank_reset_delay_to_activate_timer(
                    SCRN_BLANK_T*                 pt_this
                    )
{
    INT32  i4_ret;
    UINT32 ui4_delay;
    UINT16 ui2_val = 0;

    _scrn_blank_stop_timer(pt_this);

    a_cfg_custom_get_scrn_saver_time(&ui2_val);

    switch (ui2_val)
    {
        case 0:     // Disable
            ui4_delay = 0;
            break;
        case 1:     // 2min.
            ui4_delay = 2*60*1000;
            break;
        case 2:     // 10min.
            ui4_delay = 10*60*1000;
            break;
        case 3:     // 20min.
            ui4_delay = 20*60*1000;
            break;
        default:
            ui4_delay = 0;
            break;
    }

    if (TRUE == pt_this->b_phase1)
    {
        ui4_delay = (ui4_delay > SCRN_BLANK_DELAY_TO_BLANK_TIMEOUT
                        ? ui4_delay - SCRN_BLANK_DELAY_TO_BLANK_TIMEOUT
                        : 0);
        #if 0  /* For RD test */
        ui4_delay = ui4_delay > 0 ? 25000 : 0;
        #endif
        //ui2_scrn_blank_state = NAV_SCRN_BLANK_STATE_TIMER_PHASE1;
    }
    else
    {
        ui4_delay = SCRN_BLANK_DELAY_TO_BLANK_TIMEOUT;
        //ui2_scrn_blank_state = NAV_SCRN_BLANK_STATE_TIMER_PHASE2;
    }

    if (0 == ui4_delay)
    {
        return;
    }

    a_nav_scrn_blank_cli_set_timer_info(c_os_get_sys_tick(), ui4_delay);

    i4_ret = c_timer_start(
                    pt_this->h_timer,
                    ui4_delay,
                    X_TIMER_FLAG_ONCE,
                    _scrn_blank_delay_to_activate_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start scrn_blank::h_timer failed!"));
    }

    pt_this->b_is_on = TRUE;

    _USER_DBG_LOG(("%s(): screen saver timer started(%ds)\n", __FUNCTION__, (ui4_delay/1000)));

}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_check_to_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_blank_check_to_activate(
                    SCRN_BLANK_T*                 pt_this,
                    BOOL                        b_from_timeout
                    )
{
    INT32 i4_ret = NAVR_OK;

    _USER_DBG_LOG(("%s() b_is_on = %d, b_delay_to_activate = %d, b_from_timeout = %d, b_msg_visible = %d\n",
                                                                __FUNCTION__,
                                                                pt_this->b_is_on,
                                                                pt_this->b_delay_to_activate,
                                                                b_from_timeout,
                                                                pt_this->b_msg_visible));
    //if (pt_this->b_is_on == TRUE) {
    //    return NAVR_OK;
    //}

    i4_ret = _scrn_blank_is_able_to_activate(pt_this);
    if (i4_ret != NAVR_OK)
    {
        pt_this->b_delay_to_activate = FALSE;
        return i4_ret;
    }



    if ((pt_this->b_delay_to_activate == FALSE || b_from_timeout == FALSE)
         && pt_this->b_msg_visible == FALSE)
    {
        pt_this->b_delay_to_activate = TRUE;
        pt_this->b_phase1 = TRUE;
        _scrn_blank_reset_delay_to_activate_timer(pt_this);
        ui2_scrn_blank_state = NAV_SCRN_BLANK_STATE_TIMER_PHASE1;

        return NAVR_DELAY_ACTION;
    }
    else
    {
        pt_this->b_delay_to_activate = FALSE;
        //pt_this->b_is_on             = TRUE;

    }

    _USER_DBG_LOG(("%s() b_phase1 = %d\n", __FUNCTION__, pt_this->b_phase1));

    if (TRUE == pt_this->b_phase1)
    {
        _USER_DBG_LOG(("%s() PHASE1\n", __FUNCTION__));

        i4_ret = _scrn_blank_show_msg();

        _USER_DBG_LOG(("%s() PHASE1 i4_ret = 0x%x\n", __FUNCTION__, i4_ret));

        if (i4_ret != NAVR_OK)
        {
            return i4_ret;
        }

        nav_set_component_visible(NAV_COMP_ID_SCRN_BLANK);

        //pt_this->b_is_on = FALSE;
        pt_this->b_msg_visible = TRUE;
        pt_this->b_phase1 = FALSE;

        _scrn_blank_reset_delay_to_activate_timer(pt_this);
        ui2_scrn_blank_state = NAV_SCRN_BLANK_STATE_TIMER_PHASE2;

    }
    else
    {
        _USER_DBG_LOG(("%s() PHASE2\n", __FUNCTION__));
        //_scrn_blank_hide();
        menu_custom_blank_screen();

        if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
        {
            /* No need to send EXIT_BLANK_SCREEN command as AM process itself when recieved key */
            a_tv_net_send_cmd("\n:dtv_app_mtk,am,:ENTER_BLANK_SCREEN\n");
            //a_tv_net_send_cmd("\n:dtv_app_mtk,am,:force_dtv_input=on\n");
        }

        pt_this->b_is_on = FALSE;
        ui2_scrn_blank_state = NAV_SCRN_BLANK_STATE_BLANK;
    }

    //_scrn_blank_reset_timer(pt_this);
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_blank_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_blank_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    if (t_g_scrn_blank.b_is_on || t_g_scrn_blank.b_msg_visible)
    {
        _scrn_blank_reset();
        //menu_custom_unblank_screen();
        return NAVR_NO_ACTION;
    }

    t_g_scrn_blank.b_enable = TRUE;
    return _scrn_blank_check_to_activate(&t_g_scrn_blank, FALSE);
}

static BOOL _scrn_blank_is_key_hander(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_scrn_blank_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_scrn_blank_register(VOID)
{
    NAV_COMP_T t_comp;
    INT32      i4_ret;

    c_memset(& t_comp, 0, sizeof(NAV_COMP_T));

    /* NAV_COMP_ID_SCREEN_SAVER */
    t_comp.pf_init           = _scrn_blank_init;
    t_comp.pf_deinit         = _scrn_blank_deinit;
    t_comp.pf_is_key_handler = _scrn_blank_is_key_hander;
    t_comp.pf_activate       = _scrn_blank_activate;
    t_comp.pf_inactivate     = NULL;
    t_comp.pf_hide           = _scrn_blank_hide;
    t_comp.pf_handle_msg     = _scrn_blank_handle_msg;
    t_comp.ui4_exclusive_set = (NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_RETAIL_MODE));

    i4_ret = nav_register_component(NAV_COMP_ID_SCRN_BLANK, &t_comp, t_comp.ui4_exclusive_set);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"nav_register_component(NAV_COMP_ID_SCRN_BLANK) failed\r\n"));
        return i4_ret;
    }

    #ifdef CLI_SUPPORT
    nav_scrn_blank_cli_register_cmd_tbl();
    #endif

    return NAVR_OK;
}

VOID a_scrn_blank_act(VOID*                       pv_tag1,
                        VOID*                       pv_tag2,
                        VOID*                       pv_tag3)
{
    if (_scrn_blank_is_able_to_activate(&t_g_scrn_blank) == NAVR_OK)
    {
        if (SCRN_BLANK_CONTEXT_SWITCH_4_RESET == (UINT32)pv_tag1)
        {
            _scrn_blank_reset(); /* not change focus */
        }
        else
        {
            nav_grab_activation(NAV_COMP_ID_SCRN_BLANK);
            //_scrn_blank_activate(NULL, BTN_INVALID);
        }
    }
}

BOOL a_scrn_blank_is_acting(VOID)
{
    return (t_g_scrn_blank.b_is_on || t_g_scrn_blank.b_msg_visible);
}

INT32 a_scrn_blank_reset(VOID)
{
    return _scrn_blank_reset();
}

UINT16 a_scrn_blank_get_state(VOID)
{
    return ui2_scrn_blank_state;
}

INT32 a_scrn_blank_am_msg_proc(VOID)
{
    if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED
        && a_scrn_blank_get_state() == NAV_SCRN_BLANK_STATE_BLANK)
    {
        a_scrn_blank_reset();
    }

    return NAVR_OK;
}

