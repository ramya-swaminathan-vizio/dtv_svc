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
 * $RCSfile: audio_info.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
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
#include "u_cfg.h"

#include "c_svctx.h"
#include "c_handle.h"
#include "c_dt.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_scc.h"

#include "app_util/a_cfg.h"
#include "app_util/a_icl.h"
#include "app_util/audio/a_audio.h"

#include "nav/audio_info/audio_info.h"
#include "nav/sys_info/a_sys_info.h"
#include "nav/misc/a_nav_misc.h"
#include "nav/nav_bnr_state_mgr.h"
#include "nav/banner2/a_banner.h"

#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_dbg.h"

/* ATSC/DVBT only */
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#ifndef AUDIO_INFO_TIMER_DELAY
#define AUDIO_INFO_TIMER_DELAY          (2000) /* in ms */
#endif

typedef enum __AUDIO_INFO_SWITCH_AUDIO_METHOD_T
{
    _AUDIO_INFO_SAM_NONE = 0,           /*used for init only*/
    _AUDIO_INFO_SAM_NEXT,
    _AUDIO_INFO_SAM_PREV,
    _AUDIO_INFO_SAM_FIRST,
    _AUDIO_INFO_SAM_BY_INFO
} _AUDIO_INFO_SWITCH_AUDIO_METHOD_T;

/*-----------------------------------------------------------------------------
 * customization
 *---------------------------------------------------------------------------*/
#ifdef APP_DVBT_SUPPORT
#define _AUDIO_INFO_GET_NEXT_MTS(_e_crnt_mts, _e_new_mts)     \
{                                                                   \
    switch(_e_crnt_mts)                                             \
    {                                                               \
    case SCC_AUD_MTS_MONO:                                          \
        (_e_new_mts) = SCC_AUD_MTS_STEREO;                          \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_STEREO:                                        \
        (_e_new_mts) = SCC_AUD_MTS_SUB_LANG;                        \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_SUB_LANG:                                      \
        (_e_new_mts) = SCC_AUD_MTS_NICAM_MONO;                      \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_NICAM_MONO:                                    \
        (_e_new_mts) = SCC_AUD_MTS_NICAM_STEREO;                    \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_NICAM_STEREO:                                  \
        (_e_new_mts) = SCC_AUD_MTS_NICAM_DUAL1;                     \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_NICAM_DUAL1:                                   \
        (_e_new_mts) = SCC_AUD_MTS_NICAM_DUAL2;                     \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_NICAM_DUAL2:                                   \
    case SCC_AUD_MTS_UNKNOWN:                                       \
    default:                                                        \
        (_e_new_mts) = SCC_AUD_MTS_MONO;                            \
        break;                                                      \
    }                                                               \
}

#define _AUDIO_INFO_GET_PREV_MTS(_e_crnt_mts, _e_new_mts)     \
{                                                                   \
    switch(_e_crnt_mts)                                             \
    {                                                               \
    case SCC_AUD_MTS_MONO:                                          \
        (_e_new_mts) = SCC_AUD_MTS_NICAM_DUAL2;                     \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_STEREO:                                        \
        (_e_new_mts) = SCC_AUD_MTS_MONO;                            \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_SUB_LANG:                                      \
        (_e_new_mts) = SCC_AUD_MTS_STEREO;                          \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_NICAM_MONO:                                    \
        (_e_new_mts) = SCC_AUD_MTS_SUB_LANG;                        \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_NICAM_STEREO:                                  \
        (_e_new_mts) = SCC_AUD_MTS_NICAM_MONO;                      \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_NICAM_DUAL1:                                   \
        (_e_new_mts) = SCC_AUD_MTS_NICAM_STEREO;                    \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_NICAM_DUAL2:                                   \
    case SCC_AUD_MTS_UNKNOWN:                                       \
    default:                                                        \
        (_e_new_mts) = SCC_AUD_MTS_NICAM_DUAL1;                     \
        break;                                                      \
    }                                                               \
}

#define _AUDIO_INFO_GET_FIRST_MTS(_e_new_mts)                 \
{                                                                   \
    (_e_new_mts) = SCC_AUD_MTS_MONO;                                \
}

#else /* APP_DVBT_SUPPORT */
#define _AUDIO_INFO_GET_NEXT_MTS(_e_crnt_mts, _e_new_mts)     \
{                                                                   \
    switch(_e_crnt_mts)                                             \
    {                                                               \
    case SCC_AUD_MTS_MONO:                                          \
        (_e_new_mts) = SCC_AUD_MTS_STEREO;                          \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_STEREO:                                        \
        (_e_new_mts) = SCC_AUD_MTS_SUB_LANG;                        \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_SUB_LANG:                                      \
    case SCC_AUD_MTS_UNKNOWN:                                       \
    default:                                                        \
        (_e_new_mts) = SCC_AUD_MTS_MONO;                            \
        break;                                                      \
    }                                                               \
}

#define _AUDIO_INFO_GET_PREV_MTS(_e_crnt_mts, _e_new_mts)     \
{                                                                   \
    switch(_e_crnt_mts)                                             \
    {                                                               \
    case SCC_AUD_MTS_MONO:                                          \
        (_e_new_mts) = SCC_AUD_MTS_SUB_LANG;                        \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_STEREO:                                        \
        (_e_new_mts) = SCC_AUD_MTS_MONO;                            \
        break;                                                      \
                                                                    \
    case SCC_AUD_MTS_SUB_LANG:                                      \
    case SCC_AUD_MTS_UNKNOWN:                                       \
    default:                                                        \
        (_e_new_mts) = SCC_AUD_MTS_STEREO;                          \
        break;                                                      \
    }                                                               \
}

#define _AUDIO_INFO_GET_FIRST_MTS(_e_new_mts)                 \
{                                                                   \
    (_e_new_mts) = SCC_AUD_MTS_MONO;                                \
}
#endif /* APP_DVBT_SUPPORT */

#ifdef APP_NAV_AI_MTS_BY_CAPACITY
    #define _AUDIO_INFO_MTS_ARRAY_SIZE                        (5)

    #ifdef APP_DVBT_SUPPORT
        #define _AUDIO_INFO_IS_ANALOG_AUDIO_FMT(_e_aud_fmt)                                       \
        (                                                                                               \
            (ASH_AUDIO_FMT_MTS != (_e_aud_fmt) && ASH_AUDIO_FMT_TV_SYS != (_e_aud_fmt) && ASH_AUDIO_FMT_EU_CANAL_PLUS != (_e_aud_fmt)) ? FALSE : TRUE  \
        )
    #else
        #define _AUDIO_INFO_IS_ANALOG_AUDIO_FMT(_e_aud_fmt)                           \
        (                                                                                   \
            (ASH_AUDIO_FMT_MTS != (_e_aud_fmt)) ? FALSE : TRUE                              \
        )
    #endif /*APP_DVBT_SUPPORT*/

    #ifdef APP_NAV_AI_MTS_FORCE_RESELECT
        #define _AUDIO_INFO_IS_FORCE_RESELECT()   (TRUE)
    #else
        #define _AUDIO_INFO_IS_FORCE_RESELECT()   (FALSE)
    #endif /*APP_NAV_AI_MTS_FORCE_RESELECT*/

    #define _AUDIO_INFO_RESELECT_ANALOG_AUDIO(_pt_this, _e_grp)                   \
    {                                                                                   \
        _audio_info_reselect_analog_audio((_pt_this), (_e_grp));                  \
    }

    #define _AUDIO_INFO_SWITCH_ANALOG_AUDIO(_pt_this, _e_method, _e_grp, _e_mts_info, _i4_ret)                        \
    {                                                                                                                       \
        (_i4_ret) = _audio_info_switch_analog_audio_by_capacity((_pt_this), (_e_method), (_e_grp), (_e_mts_info), TRUE);    \
    }

    #define _AUDIO_INFO_IS_ANALOG_AUDIO_CAPACITY_READY(_b_is_ready, _e_grp)       \
    {                                                                                   \
        (_b_is_ready) = _audio_info_is_analog_audio_capacity_ready((_e_grp));     \
    }

    #define _AUDIO_INFO_IS_MTS_BY_CAPACITY()                     (TRUE)

    #define _AUDIO_INFO_RESET_MTS_BACKUP(_pt_this)                                \
    {                                                                                   \
        (_pt_this)->e_capacity_backup = SCC_AUD_MTS_UNKNOWN;                            \
    }

    #define _AUDIO_INFO_CFG_XNG(_pt_this, _e_grp)                                 \
    {                                                                                   \
        _AUDIO_INFO_RESELECT_ANALOG_AUDIO((_pt_this), (_e_grp));                  \
    }

    static INT32 _audio_info_reselect_analog_audio(
                        AUDIO_INFO_T*                            pt_this,
                        TV_WIN_ID_T                                    e_grp
                        );

    static INT32 _audio_info_get_analog_audio_channel(
                        TV_WIN_ID_T                                    e_grp,
                        ASH_CHANNELS_T*                                pe_audio_channel
                        );

    static INT32 _audio_info_switch_analog_audio_by_capacity(
                        AUDIO_INFO_T*                            pt_this,
                        _AUDIO_INFO_SWITCH_AUDIO_METHOD_T        e_method,
                        TV_WIN_ID_T                                    e_grp,
                        SCC_AUD_MTS_T                                  e_mts_info,        /*for _AUDIO_INFO_SAM_BY_INFO*/
                        BOOL                                           b_by_key
                        );

    static BOOL _audio_info_is_analog_audio_capacity_ready(
                        TV_WIN_ID_T                                    e_grp
                        );

    static VOID _audio_info_convert_mts(
                    ASH_CHANNELS_T                                     e_channel,
                    SCC_AUD_MTS_T*                                     pe_mts);

#else /* APP_NAV_AI_MTS_BY_CAPACITY */
	#define _AUDIO_INFO_IS_FORCE_RESELECT()   				(FALSE)

    #define _AUDIO_INFO_RESELECT_ANALOG_AUDIO(_pt_this, _e_grp)   \
    {                                                                   \
    }

    #define _AUDIO_INFO_SWITCH_ANALOG_AUDIO(_pt_this, _e_method, _e_grp, _e_mts_info, _i4_ret)            \
    {                                                                                                           \
        (_i4_ret) = _audio_info_switch_analog_audio((_pt_this), (_e_method), (_e_grp), (_e_mts_info));    \
    }

    #define _AUDIO_INFO_IS_ANALOG_AUDIO_CAPACITY_READY(_b_is_ready, _e_grp)       \
    {                                                                                   \
        (_b_is_ready) = TRUE;                                                           \
    }

    #define _AUDIO_INFO_IS_MTS_BY_CAPACITY()                     (FALSE)

    #define _AUDIO_INFO_RESET_MTS_BACKUP(_pt_this)                                \
    {                                                                                   \
    }

    #define _AUDIO_INFO_CFG_XNG(_pt_this, _e_grp)                                 \
    {                                                                                   \
        _audio_info_reset_analog_audio((_pt_this), (_e_grp), NULL);               \
    }

    static INT32 _audio_info_switch_analog_audio(
                        AUDIO_INFO_T*                            pt_this,
                        _AUDIO_INFO_SWITCH_AUDIO_METHOD_T        e_method,
                        TV_WIN_ID_T                                    e_grp,
                        SCC_AUD_MTS_T                                  e_mts_info         /*for _AUDIO_INFO_SAM_BY_INFO*/
                        );
#endif /*APP_NAV_AI_MTS_BY_CAPACITY*/

#if defined(APP_NAV_AI_SAVE_MTS) || defined(APP_NAV_AI_SAVE_MTS_SPECIFIC)
    #ifdef APP_NAV_AI_SAVE_MTS_SPECIFIC
        #ifndef _AUDIO_INFO_IS_SAVE_MTS
        #define _AUDIO_INFO_IS_SAVE_MTS(_e_new_mts, _b_is)                    \
        {                                                                           \
            switch((_e_new_mts))                                                    \
            {                                                                       \
            case SCC_AUD_MTS_NICAM_DUAL1:                                           \
            case SCC_AUD_MTS_NICAM_DUAL2:                                           \
            case SCC_AUD_MTS_DUAL1:                                                 \
            case SCC_AUD_MTS_DUAL2:                                                 \
                (_b_is) = TRUE;                                                     \
                break;                                                              \
            default:                                                                \
                (_b_is) = FALSE;                                                    \
                break;                                                              \
            }                                                                       \
        }
        #endif

        #define _AUDIO_INFO_SAVE_MTS(_pt_this, _e_new_mts, _i4_ret)                                                   \
        {                                                                                                                   \
            BOOL    _b_is_save;                                                                                             \
                                                                                                                            \
            _AUDIO_INFO_IS_SAVE_MTS((_e_new_mts), _b_is_save);                                                        \
            if(_b_is_save)                                                                                                  \
            {                                                                                                               \
                (_i4_ret) = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS), (INT16)(_e_new_mts));     \
                (_i4_ret) = (APP_CFGR_OK != (_i4_ret)) ? NAVR_FAIL : NAVR_OK;                                               \
            }                                                                                                               \
            else                                                                                                            \
            {                                                                                                               \
                (_pt_this)->b_is_mts_changed = TRUE;                                                                        \
                (_i4_ret) = NAVR_OK;                                                                                        \
            }                                                                                                               \
        }
    #else /* APP_NAV_AI_SAVE_MTS_SPECIFIC */
        #define _AUDIO_INFO_SAVE_MTS(_pt_this, _e_new_mts, _i4_ret)                                               \
        {                                                                                                               \
            (_i4_ret) = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS), (INT16)(_e_new_mts));     \
            (_i4_ret) = (APP_CFGR_OK != (_i4_ret)) ? NAVR_FAIL : NAVR_OK;                                               \
        }
    #endif /* APP_NAV_AI_SAVE_MTS_SPECIFIC */
#else /* APP_NAV_AI_SAVE_MTS || APP_NAV_AI_SAVE_MTS_SPECIFIC */
    #define _AUDIO_INFO_SAVE_MTS(_pt_this, _e_new_mts, _i4_ret)                                                   \
    {                                                                                                                   \
        (_pt_this)->b_is_mts_changed = TRUE;                                                                            \
        (_i4_ret) = NAVR_OK;                                                                                            \
    }
#endif /* APP_NAV_AI_SAVE_MTS || APP_NAV_AI_SAVE_MTS_SPECIFIC */

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
AUDIO_INFO_T t_g_audio_info;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _audio_info_stop_timer(
                    AUDIO_INFO_T*           pt_this
                    );
static VOID _audio_info_reset_timer(
                    AUDIO_INFO_T*           pt_this
                    );
static VOID _audio_info_handle_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );
static VOID _audio_info_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    );
static INT32 _audio_info_audio_init(
                    AUDIO_INFO_T*               pt_this
                    );
static INT32 _audio_info_audio_deinit(
                    AUDIO_INFO_T*               pt_this
                    );
static INT32 _audio_info_reset_analog_audio(
                    AUDIO_INFO_T*               pt_this,
                    TV_WIN_ID_T                 e_grp,
                    const NAV_XNG_SRC_TRGT_T*   pt_xng_info);

static VOID _audio_info_check_mts(
                    AUDIO_INFO_T*               pt_this,
                    TV_WIN_ID_T                 e_grp,
                    const NAV_XNG_SRC_TRGT_T*   pt_xng_info);

static VOID _audio_info_update_audio_info(
                    AUDIO_INFO_T*               pt_this,
                    TV_WIN_ID_T                 e_grp,
                    BOOL                        b_invalid_info_as_no_audio
                    );
static INT32 _audio_info_update_digital_audio_info(
                    AUDIO_INFO_T*               pt_this,
                    TV_WIN_ID_T                 e_grp,
                    BOOL                        b_invalid_info_as_no_audio
                    );
static INT32 _audio_info_update_analog_audio_info(
                    AUDIO_INFO_T*               pt_this,
                    TV_WIN_ID_T                 e_grp
                    );

static INT32 _audio_info_set_mts(
                    AUDIO_INFO_T*               pt_this,
                    TV_WIN_ID_T                 e_grp,
                    SCC_AUD_MTS_T               e_mts_new,
                    const SCC_AUD_MTS_T*        pe_mts_crnt
                    );

static VOID _audio_info_mts_cfg_change_cb(
                    UINT16                      ui2_nfy_id,
                    VOID*                       pv_tag,
                    UINT16                      ui2_id);

static VOID _audio_info_mts_cfg_change_msg_hdlr(
                    VOID*                       pv_unused,
                    VOID*                       pv_unused2,
                    VOID*                       pv_unused3);
/*key*/
static BOOL _audio_info_is_same_svc_change(
                    const NAV_XNG_SRC_TRGT_T*   pt_xng_info
                    );

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_reset_sys_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_reset_sys_info(
                TV_WIN_ID_T             e_tv_win_id
                )
{
    SI_SET_INFO_T   t_set_info;

    c_memset(&t_set_info, 0 , sizeof(SI_SET_INFO_T));
    t_set_info.e_category = SI_CATEGORY_AUD_STRM_INFO;
    t_set_info.u.t_aud_strm_info.ui4_info_mask =
                                SI_AUD_INFO_MASK_SEL_NUM |
                                SI_AUD_INFO_MASK_SEL_IDX |
                                SI_AUD_INFO_MASK_ANA_AUD_MTS |
                                SI_AUD_INFO_MASK_DIG_AUD_STS |
                                SI_AUD_INFO_MASK_DIG_AUD_LANG |
                                SI_AUD_INFO_MASK_DIG_AUD_LANG2 |
                                SI_AUD_INFO_MASK_DIG_AUD_TYPE |
                                SI_AUD_INFO_MASK_DIG_AUD_INFO ;
    return a_si_unset_item_info_by_win_id(e_tv_win_id, &t_set_info);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_pre_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_pre_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    AUDIO_INFO_T* pt_this = &t_g_audio_info;
    INT32         i4_ret  = NAVR_OK;
    INT32         i;

    c_memset(pt_this, 0, sizeof(AUDIO_INFO_T));

    pt_this->b_is_on = FALSE;
    pt_this->b_is_mts_changed = FALSE;
    pt_this->b_is_same_svc_change = FALSE;
    pt_this->b_is_audio_info_ready = FALSE;
    pt_this->e_capacity_backup = SCC_AUD_MTS_UNKNOWN;
    pt_this->e_crnt_mts = SCC_AUD_MTS_UNKNOWN;
    pt_this->ui2_mts_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
    pt_this->b_from_cfg = FALSE;
    pt_this->b_reset_mts_in_scan = FALSE;
	pt_this->b_aud_ch_alg_mts = FALSE;

    /*Create mutex semaphore*/
    i4_ret = c_sema_create (&pt_this->h_mtx_sema,
                            X_SEMA_TYPE_MUTEX,
                            X_SEMA_STATE_UNLOCK);
    if (OSR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }


    /*init member*/
    for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
    {
        pt_this->at_grp[i].b_is_digital = FALSE;
    }
    pt_this->e_focus = TV_WIN_ID_MAIN;

    /*mts config*/
    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_AUDIO,
                              NULL,
                              _audio_info_mts_cfg_change_cb,
                              &pt_this->ui2_mts_cfg_nfy);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): a_cfg_notify_reg(%d) failed. i4_ret = %d.\r\n", __FUNCTION__, APP_CFG_GRPID_AUDIO, i4_ret));

        pt_this->ui2_mts_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
        return NAVR_FAIL;
    }

    /*init view*/
    i4_ret = audio_info_view_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    0,
                    0,
                    pt_ctx->t_gui_res.e_color_type
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    /*init audio resource*/
    i4_ret = _audio_info_audio_init(pt_this);
    if(NAVR_OK != i4_ret)
    {
        _audio_info_audio_deinit(pt_this);
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_deinit(
                    VOID
                    )
{
    AUDIO_INFO_T* pt_this = &t_g_audio_info;
    INT32         i4_ret  = NAVR_OK;

    /*Delete semaphore*/
    if (c_handle_valid(pt_this->h_mtx_sema) == TRUE)
    {
        c_sema_delete(pt_this->h_mtx_sema);
        pt_this->h_mtx_sema = NULL_HANDLE;
    }

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
        pt_this->h_hide_timer = NULL_HANDLE;
    }

#ifdef APP_DVBT_SUPPORT
        if(APP_CFG_NOTIFY_NULL_ID != pt_this->ui2_mts_cfg_nfy)
        {
            a_cfg_notify_unreg(pt_this->ui2_mts_cfg_nfy);
            pt_this->ui2_mts_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
        }
#endif

    i4_ret = audio_info_view_deinit();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;
	pt_this->b_aud_ch_alg_mts = FALSE;

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_hide(
                    VOID
                    )
{
    AUDIO_INFO_T* pt_this = &t_g_audio_info;
    INT32         i4_ret;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    i4_ret = audio_info_view_hide();
    if (i4_ret == NAVR_OK) {
        pt_this->b_is_on = FALSE;
        _audio_info_stop_timer(pt_this);
    }

    /* Return control. */
    nav_return_activation(NAV_COMP_ID_AUDIO_SEL);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_is_svl_empty
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL _audio_info_is_svl_empty (
                TV_WIN_ID_T     e_tv_win_id
                )
{
    BOOL b_empty  = FALSE;

    if (nav_is_svl_empty(e_tv_win_id) || nav_is_specified_ch_lst_empty(e_tv_win_id))
    {
        b_empty = TRUE;
    }
    return b_empty;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _audio_info_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    AUDIO_INFO_T* pt_this = &t_g_audio_info;

    if((LOCKED_STATUS_NONE != nav_get_locked_status(pt_this->e_focus)) ||
       (TRUE == nav_is_signal_loss(pt_this->e_focus)) ||
       (TRUE == _audio_info_is_svl_empty(pt_this->e_focus)) ||
       (TRUE == nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_AUDIO_SEL_UI)))
    {
        return FALSE;
    }

    if(BTN_MTS == ui4_key_code)
    {
        if(INP_SRC_TYPE_TV == nav_get_src_type(pt_this->e_focus))
        {
            return TRUE;
        }
    }

    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    AUDIO_INFO_T*       pt_this     = &t_g_audio_info;
    TV_WIN_ID_T         e_tv_win_id = TV_WIN_ID_MAIN;
#if 0
    INT32               i4_ret;
    SCDB_REC_T          t_scdb_rec  = {0};
    UINT16              ui2_total   = 0;
    UINT16              ui2_order   = 0;
    UINT32              ui4_scrambled_strm = 0;
    ASH_AUDIO_INFO_T    t_audio_info;

    SCC_AUD_MTS_T       e_mts_crnt;

    nav_get_focus_id(&e_tv_win_id);
    if (e_tv_win_id >= TV_WIN_ID_LAST_VALID_ENTRY)
    {
        e_tv_win_id = TV_WIN_ID_MAIN;
    }


    if (pt_this->at_grp[e_tv_win_id].b_is_digital)
    {
        i4_ret = nav_get_crnt_audio_info(
                    e_tv_win_id,
                    &t_audio_info,
                    &t_scdb_rec,
                    &ui2_total,
                    &ui2_order
                    );
        if (i4_ret != NAVR_OK) {
            i4_ret = audio_info_view_draw_no_feature();
            if (i4_ret != NAVR_OK) {
                return i4_ret;
            }
        }

        i4_ret = nav_get_ca_status(e_tv_win_id, &ui4_scrambled_strm);
        if (i4_ret != NAVR_OK) {
            ui4_scrambled_strm = 0;
        }

        i4_ret = audio_info_view_draw_digital(
                                NULL,
                                &t_scdb_rec,
                                ui2_total,
                                ui2_order,
                                ui4_scrambled_strm
                                );
        if (i4_ret != NAVR_OK) {
            i4_ret = audio_info_view_draw_no_feature();
            if (i4_ret != NAVR_OK) {
                return i4_ret;
            }
        }
    }
    else
    {
        i4_ret = c_scc_aud_get_mts(pt_this->at_grp[e_tv_win_id].h_mts,
                                   &e_mts_crnt);
        if (i4_ret != NAVR_OK) {
            i4_ret = audio_info_view_draw_no_feature();
            if (i4_ret != NAVR_OK) {
                return i4_ret;
            }
        }
        i4_ret = audio_info_view_draw_analog(pt_this->e_crnt_mts);
        if (i4_ret != NAVR_OK) {
            i4_ret = audio_info_view_draw_no_feature();
            if (i4_ret != NAVR_OK) {
                return i4_ret;
            }
        }
    }


    i4_ret = audio_info_view_show();
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    pt_this->b_is_on = TRUE;
    _audio_info_reset_timer(pt_this);

    return NAVR_OK;
#else

    if (TRUE == a_banner_is_item_visible(BANNER_ITM_AUDIO_FARMAT))
    {
        /* do next mts */
        nav_get_focus_id(&e_tv_win_id);

        audio_info_key_handler( pt_this, e_tv_win_id, ui4_key_code) ;

        /* update audio info to banner at once */
        _audio_info_update_audio_info(pt_this, e_tv_win_id, FALSE);
    }

    /* show banner */
    a_banner_show_items (NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_FARMAT));

    return NAVR_NO_ACTION ;

#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_handle_fmt_update
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_handle_fmt_update(
                    AUDIO_INFO_T*               pt_this
                    )
{
    SCDB_REC_T       t_scdb_rec         = {0};
    UINT16           ui2_total_amount   = 0;
    UINT16           ui2_order          = 0;
    UINT32           ui4_scrambled_strm = 0;
    ASH_AUDIO_INFO_T t_audio_info;
    INT32            i4_ret           = NAVR_OK;
    TV_WIN_ID_T      e_tv_win_id      = TV_WIN_ID_MAIN;

    nav_get_focus_id(&e_tv_win_id);

    if (e_tv_win_id >= TV_WIN_ID_LAST_VALID_ENTRY)
    {
        return NAVR_FAIL;
    }

    if(pt_this->at_grp[e_tv_win_id].b_is_digital)
    {
        i4_ret = nav_get_crnt_audio_info(
                        e_tv_win_id,
                        &t_audio_info,
                        &t_scdb_rec,
                        &ui2_total_amount,
                        &ui2_order
                        );
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }

        i4_ret = nav_get_ca_status(e_tv_win_id, &ui4_scrambled_strm);
        if (i4_ret != NAVR_OK) {
            ui4_scrambled_strm = 0;
        }

        /* Update audio select dialog info */
        i4_ret = audio_info_view_draw_digital(
                    NULL,
                    &t_scdb_rec,
                    ui2_total_amount,
                    ui2_order,
                    ui4_scrambled_strm
                    );
    }
    else
    {
        i4_ret = audio_info_view_draw_analog(pt_this->e_crnt_mts);
    }

    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (pt_this->b_is_on == FALSE) {
        return NAVR_OK;
    }

     _audio_info_reset_timer(pt_this);

    i4_ret = audio_info_view_show();

/*#warning check it*/

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    AUDIO_INFO_T*   pt_this = &t_g_audio_info;
    INT32           i4_ret  = NAVR_OK;
    SI_SET_INFO_T   t_set_info;
    TV_WIN_ID_T     e_tv_win_id;

    /* Range protect for e_tv_win_id */
    if (pt_ui_msg->e_tv_win_id >= TV_WIN_ID_LAST_VALID_ENTRY)
    {
        pt_ui_msg->e_tv_win_id = TV_WIN_ID_MAIN;
    }

    switch (pt_ui_msg->e_id) {
    case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        {
            SVL_REC_T        t_svl_rec;

            NAV_ASSERT(pt_ui_msg->e_tv_win_id < TV_WIN_ID_LAST_VALID_ENTRY);

            /*update current svl info*/
            i4_ret= nav_get_svl_rec(pt_ui_msg->e_tv_win_id, &t_svl_rec);
            if(NAVR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s(): nav_get_svl_rec(%d) failed, ret = %d\r\n", __FUNCTION__, pt_ui_msg->e_tv_win_id, i4_ret));
                pt_this->at_grp[pt_ui_msg->e_tv_win_id].b_is_digital = FALSE;
            }
            else
            {
                pt_this->at_grp[pt_ui_msg->e_tv_win_id].b_is_digital = (BRDCST_TYPE_ANALOG != t_svl_rec.uheader.t_rec_hdr.e_brdcst_type) ? TRUE : FALSE;
            }

            nav_get_focus_id(&e_tv_win_id);
            if (e_tv_win_id != pt_ui_msg->e_tv_win_id &&
                FALSE == nav_is_pop_pip_swapping()){
                break;
            }

            _audio_info_reset_sys_info(pt_ui_msg->e_tv_win_id);

            _audio_info_stop_timer(pt_this);

            pt_this->b_is_same_svc_change = _audio_info_is_same_svc_change((const NAV_XNG_SRC_TRGT_T*)pv_arg1);
            if(FALSE == pt_this->b_is_same_svc_change &&
               TRUE == nav_is_pop_pip_swapping())
            {
                pt_this->b_is_same_svc_change = TRUE;
            }

            pt_this->b_been_reset = FALSE;
            if(FALSE == pt_this->b_is_same_svc_change)  /*Always reset mts_changed flag in by-capacity mode*/
            {
                pt_this->b_is_mts_changed = FALSE;
            }

            /*Audio cannot guarantee the audio info before its notification. So, we use this flag to avoid unstable audio info.*/
            pt_this->b_is_audio_info_ready = FALSE;
            pt_this->ui2_selectable_audio_count = 0;

            i4_ret = nav_hide_component(NAV_COMP_ID_AUDIO_SEL);

        }
        break;

    case NAV_UI_MSG_SVL_UPDATE:
        break;

    case NAV_UI_MSG_POWER_ON:
        if(pt_this->b_is_mts_changed)
        {
            _audio_info_reset_analog_audio(pt_this, TV_WIN_ID_MAIN, NULL);
        }
        break;

    case NAV_UI_MSG_AFTER_SVC_CHANGE:
        /*reset mts:DTV02164387*/
#if 0
        _audio_info_check_mts(pt_this, pt_ui_msg->e_tv_win_id, NULL);
        _audio_info_update_audio_info(pt_this, pt_ui_msg->e_tv_win_id, FALSE);
#endif
        break;
    case NAV_UI_MSG_AV_STATUS_NOTIFY:
      {
        ISL_REC_T        t_isl_rec;
        SCDB_REC_T       t_scdb_rec;
        ASH_AUDIO_INFO_T t_audio_info;
        UINT16           ui2_total_amount = 0;
        UINT16           ui2_order = 0;

        nav_get_focus_id(&e_tv_win_id);
        if (e_tv_win_id != pt_ui_msg->e_tv_win_id){
            break;
        }

        switch(nav_get_av_status(pt_ui_msg->e_tv_win_id)) {
        case NAV_AV_STATUS_NO_AUDIO_VIDEO:
        case NAV_AV_STATUS_SCRAMBLED_VIDEO_NO_AUDIO:
        case NAV_AV_STATUS_VIDEO_ONLY:
             _audio_info_reset_sys_info(pt_ui_msg->e_tv_win_id);

            i4_ret = nav_get_isl_rec(pt_ui_msg->e_tv_win_id, &t_isl_rec);
            if(NAVR_OK == i4_ret &&
               INP_SRC_TYPE_TV == t_isl_rec.e_src_type &&
               pt_this->at_grp[pt_ui_msg->e_tv_win_id].b_is_digital)
            {
                nav_get_crnt_audio_info (pt_ui_msg->e_tv_win_id,
                            &t_audio_info,      &t_scdb_rec,
                            &ui2_total_amount,  &ui2_order);
            }
            c_memset(&t_set_info, 0, sizeof(SI_SET_INFO_T));
            t_set_info.e_category = SI_CATEGORY_AUD_STRM_INFO;
            t_set_info.u.t_aud_strm_info.ui4_info_mask = SI_AUD_INFO_MASK_DIG_AUD_STS;
            t_set_info.u.t_aud_strm_info.e_dig_aud_sts = SI_AUD_DIG_AUD_STS_ABSENT;
            if (ui2_order != 0 && ui2_total_amount > 1)
            {
                t_set_info.u.t_aud_strm_info.ui4_info_mask |=
                                            SI_AUD_INFO_MASK_SEL_NUM |
                                            SI_AUD_INFO_MASK_SEL_IDX ;
                t_set_info.u.t_aud_strm_info.ui2_sel_num = ui2_total_amount;
                t_set_info.u.t_aud_strm_info.ui2_sel_idx = ui2_order - 1;
            }
			t_set_info.u.t_aud_strm_info.ui4_info_mask |= SI_AUD_INFO_MASK_DIG_AUD_LANG;
			c_memcpy(t_set_info.u.t_aud_strm_info.s639_dig_aud_lang,
		             t_scdb_rec.u.t_audio_mpeg.s_lang,
		             sizeof(ISO_639_LANG_T));

            a_si_set_item_info_by_win_id(pt_ui_msg->e_tv_win_id, &t_set_info);
            break;
        default:
            break;
        }
        break;
      }
    case NAV_UI_MSG_STREAM_NOTIFY:
      {
        NAV_STREAM_NOTIFY_DATA_T* pt_nfy_data = (NAV_STREAM_NOTIFY_DATA_T*)pv_arg1;

        switch(pt_nfy_data->e_strm_type)
        {
        case ST_AUDIO:
            if(NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type)
            {
                if(nav_is_component_visible(NAV_COMP_ID_MISC))
                {
                    UINT32     ui4_crnt_no_feature_key;

                    a_nav_misc_get_crnt_no_feature_key(&ui4_crnt_no_feature_key);

                    if (ui4_crnt_no_feature_key == BTN_MTS)
                    {
                        nav_hide_component(NAV_COMP_ID_MISC);
                    }
                }

                pt_this->b_is_audio_info_ready = TRUE;
				pt_this->b_aud_ch_alg_mts = TRUE;
                _AUDIO_INFO_RESELECT_ANALOG_AUDIO(pt_this, pt_this->e_focus);
            }
            /*DTV02164387: set MTS after audio play in ATV*/
            if( NAV_SNT_STREAM_STARTED == pt_nfy_data->e_type)
            {
              DBG_LOG_PRINT(("\n\n[ MTS AUDIO +++ ] {%s %s() %d}. NAV_SNT_STREAM_STARTED start to set MTS.\n\n",__FILE__, __FUNCTION__, __LINE__));
              _audio_info_check_mts(pt_this, pt_ui_msg->e_tv_win_id, NULL);
              _audio_info_update_audio_info(pt_this, pt_ui_msg->e_tv_win_id, FALSE);
            }

            if(NAV_SNT_STREAM_STOPPED == pt_nfy_data->e_type)
            {
                _audio_info_reset_sys_info(pt_ui_msg->e_tv_win_id);
                pt_this->b_is_audio_info_ready = FALSE;
            }
            else
            {
                if (NAV_SNT_STREAM_NOT_FOUND == pt_nfy_data->e_type)
                {
                    pt_this->b_is_audio_info_ready = TRUE;
                }
                _audio_info_update_audio_info(
                        pt_this,
                        pt_ui_msg->e_tv_win_id,
                        NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type ? TRUE : FALSE
                        );
            }

            i4_ret = _audio_info_handle_fmt_update(pt_this);
            break;

        default:
            break;
        }
        break;
      }
    case NAV_UI_MSG_NO_SIGNAL:
        if(FALSE == nav_is_channel_scan_active())
        {
            _audio_info_reset_sys_info(pt_ui_msg->e_tv_win_id);
            i4_ret = nav_get_focus_id(&e_tv_win_id);
            if (NAVR_OK != i4_ret){
                break;
            }
            if (pt_ui_msg->e_tv_win_id == e_tv_win_id)
            {
                pt_this->b_been_reset = FALSE;
                pt_this->b_is_audio_info_ready = FALSE;
                i4_ret = nav_hide_component(NAV_COMP_ID_AUDIO_SEL);
            }
        }
        break;
    case NAV_UI_MSG_UNLOCKED:
        break;

    case NAV_UI_MSG_LOCKED_INP:
    case NAV_UI_MSG_LOCKED_CH:
    case NAV_UI_MSG_LOCKED_PROG:
    case NAV_UI_MSG_EMPTY_SVL:
    case NAV_UI_MSG_EMPTY_SPECIFIED_CH_LIST:
        _audio_info_reset_sys_info(pt_ui_msg->e_tv_win_id);

        i4_ret = nav_hide_component(NAV_COMP_ID_AUDIO_SEL);
        break;

    case NAV_UI_MSG_SCDB_UPDATE:
        if (nav_get_locked_status(pt_ui_msg->e_tv_win_id) != LOCKED_STATUS_NONE) {
            break;
        }
        _audio_info_update_audio_info(pt_this, pt_ui_msg->e_tv_win_id, FALSE);
        /*no break here*/
    case NAV_UI_MSG_WITH_SIGNAL:
        {
            i4_ret = nav_get_selectable_audio_count(pt_ui_msg->e_tv_win_id, &pt_this->ui2_selectable_audio_count);
            if(NAVR_OK != i4_ret)
            {
                pt_this->ui2_selectable_audio_count = 0;
            }
        }
        break;
    case NAV_UI_MSG_CA:
      {
        STREAM_TYPE_T e_strm_type = (STREAM_TYPE_T)(UINT32)pv_arg1;
        UINT32        ui4_scrambled_strm = 0;

        if (nav_get_locked_status(pt_ui_msg->e_tv_win_id) == LOCKED_STATUS_INP_SRC_LOCKED)
        {
            break;
        }

        i4_ret = nav_get_ca_status(pt_ui_msg->e_tv_win_id, &ui4_scrambled_strm);
        if (i4_ret != NAVR_OK) {
            break;
        }

        switch(e_strm_type) {
        case ST_AUDIO:
            if ((ui4_scrambled_strm & MAKE_BIT_MASK_32(e_strm_type)) > 0)
            {
                SCDB_REC_T       t_scdb_rec;
                ASH_AUDIO_INFO_T t_audio_info;
                UINT16           ui2_total_amount = 0;
                UINT16           ui2_order = 0;

                i4_ret = nav_get_focus_id(&e_tv_win_id);
                if (NAVR_OK != i4_ret){
                    break;
                }
                _audio_info_reset_sys_info(e_tv_win_id);

                if(e_tv_win_id < TV_WIN_ID_LAST_VALID_ENTRY &&
                   pt_this->at_grp[e_tv_win_id].b_is_digital)
                {
                    nav_get_crnt_audio_info (e_tv_win_id,
                            &t_audio_info,      &t_scdb_rec,
                            &ui2_total_amount,  &ui2_order);
                }
                c_memset(&t_set_info, 0, sizeof(SI_SET_INFO_T));
                t_set_info.e_category = SI_CATEGORY_AUD_STRM_INFO;
                t_set_info.u.t_aud_strm_info.ui4_info_mask = SI_AUD_INFO_MASK_DIG_AUD_STS;
                t_set_info.u.t_aud_strm_info.e_dig_aud_sts = SI_AUD_DIG_AUD_STS_SCRAMBLED;
                if (ui2_order != 0 && ui2_total_amount > 1)
                {
                    t_set_info.u.t_aud_strm_info.ui4_info_mask |=
                                                SI_AUD_INFO_MASK_SEL_NUM |
                                                SI_AUD_INFO_MASK_SEL_IDX ;
                    t_set_info.u.t_aud_strm_info.ui2_sel_num = ui2_total_amount;
                    t_set_info.u.t_aud_strm_info.ui2_sel_idx = ui2_order - 1;
                }

                a_si_set_item_info_by_win_id(e_tv_win_id, &t_set_info);
            } else {
                _audio_info_reset_sys_info(pt_ui_msg->e_tv_win_id);

                _audio_info_update_audio_info(pt_this, pt_ui_msg->e_tv_win_id, FALSE);
            }
            break;
        default:
            break;
        }
        break;
      }
    case NAV_UI_MSG_CP:
      {
        UINT32 ui4_protected_strm = 0;

        if (nav_get_locked_status(pt_ui_msg->e_tv_win_id) != LOCKED_STATUS_NONE) {
            break;
        }

        i4_ret = nav_get_cp_status(pt_ui_msg->e_tv_win_id, &ui4_protected_strm);
        break;
      }

    case NAV_UI_MSG_FOCUS_CHANGED:
        pt_this->e_focus = (TV_WIN_ID_T)(INT32)pv_arg1;
        break;

    case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
        break;

    case NAV_UI_MSG_AS_APP_PAUSED:
    {
        switch(pt_ui_msg->e_id_as_paused)
        {
            case NAV_UI_MSG_STREAM_NOTIFY:
            {
                NAV_STREAM_NOTIFY_DATA_T* pt_nfy_data = (NAV_STREAM_NOTIFY_DATA_T*)pv_arg1;
                if ((FALSE == pt_this->b_is_mts_changed ||
                     TRUE == pt_this->b_reset_mts_in_scan) &&
                    ST_AUDIO == pt_nfy_data->e_strm_type)
                {
                    if(NAV_SNT_STREAM_STARTED == pt_nfy_data->e_type ||
                       NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type)
                    {
                        pt_this->b_is_mts_changed = FALSE;
                        _AUDIO_INFO_RESELECT_ANALOG_AUDIO(pt_this, pt_this->e_focus);
                    }
                }
                if ((FALSE == pt_this->b_reset_mts_in_scan) &&
                    (ST_AUDIO == pt_nfy_data->e_strm_type))
                {
                    if(NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type)
                    {
                        if(nav_is_component_visible(NAV_COMP_ID_MISC))
                        {
                            UINT32     ui4_crnt_no_feature_key;

                            a_nav_misc_get_crnt_no_feature_key(&ui4_crnt_no_feature_key);

                            if (ui4_crnt_no_feature_key == BTN_MTS)
                            {
                                nav_hide_component(NAV_COMP_ID_MISC);
                            }
                        }

                        pt_this->b_is_audio_info_ready = TRUE;
						pt_this->b_aud_ch_alg_mts = TRUE;
                        _AUDIO_INFO_RESELECT_ANALOG_AUDIO(pt_this, pt_this->e_focus);
                    }

                    if(NAV_SNT_STREAM_STOPPED == pt_nfy_data->e_type)
                    {
                        _audio_info_reset_sys_info(pt_ui_msg->e_tv_win_id);
                        pt_this->b_is_audio_info_ready = FALSE;
                    }
                    else
                    {
                        if (NAV_SNT_STREAM_NOT_FOUND == pt_nfy_data->e_type)
                        {
                            pt_this->b_is_audio_info_ready = TRUE;
                        }
                        _audio_info_update_audio_info(
                                pt_this,
                                pt_ui_msg->e_tv_win_id,
                                NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type ? TRUE : FALSE
                                );
                    }

                    i4_ret = _audio_info_handle_fmt_update(pt_this);
                }
                break;
            }
            case NAV_UI_MSG_BEFORE_SVC_CHANGE:
			{
	            SVL_REC_T        t_svl_rec;

	            NAV_ASSERT(pt_ui_msg->e_tv_win_id < TV_WIN_ID_LAST_VALID_ENTRY);

	            /*update current svl info*/
	            i4_ret= nav_get_svl_rec(pt_ui_msg->e_tv_win_id, &t_svl_rec);
	            if(NAVR_OK != i4_ret)
	            {
	                DBG_ERROR((_ERROR_HEADER"%s(): nav_get_svl_rec(%d) failed, ret = %d\r\n", __FUNCTION__, pt_ui_msg->e_tv_win_id, i4_ret));
	                pt_this->at_grp[pt_ui_msg->e_tv_win_id].b_is_digital = FALSE;
	            }
	            else
	            {
	                pt_this->at_grp[pt_ui_msg->e_tv_win_id].b_is_digital = (BRDCST_TYPE_ANALOG != t_svl_rec.uheader.t_rec_hdr.e_brdcst_type) ? TRUE : FALSE;
	            }

                pt_this->b_is_same_svc_change = _audio_info_is_same_svc_change((const NAV_XNG_SRC_TRGT_T*)pv_arg1);
                /*Always reset mts_changed flag in by-capacity mode*/
                if(FALSE == pt_this->b_is_same_svc_change)
                {
                	pt_this->b_is_mts_changed = FALSE;
                }
            }
                break;
            case NAV_UI_MSG_AFTER_SVC_CHANGE:
                _audio_info_check_mts(pt_this, pt_ui_msg->e_tv_win_id, NULL);
                break;
            default:
                /* Do nothing */
                break;
        }
        break;
    }
    case NAV_UI_MSG_CH_SCANNING:
        if (TRUE == (BOOL)((UINT32)pv_arg1))
        {
            pt_this->b_reset_mts_in_scan = TRUE;
        }
        else
        {
            pt_this->b_reset_mts_in_scan = FALSE;
        }
        break;

    default:
        break;
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _audio_info_stop_timer(
                    AUDIO_INFO_T*           pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop audio_info::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _audio_info_reset_timer(
                    AUDIO_INFO_T*           pt_this
                    )
{
    INT32 i4_ret;

    if (FALSE == pt_this->b_is_on)
    {
        return ;
    }

    _audio_info_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    AUDIO_INFO_TIMER_DELAY,
                    X_TIMER_FLAG_ONCE,
                    _audio_info_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start audio_info::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_handle_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _audio_info_handle_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    nav_hide_component(NAV_COMP_ID_AUDIO_SEL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _audio_info_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_audio_info_handle_timeout, pv_tag, NULL, NULL);
}


/*-----------------------------------------------------------------------------
 * From banner
 *---------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
 * Name
 *      _audio_info_is_same_svc_change
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static BOOL _audio_info_is_same_svc_change(
    const NAV_XNG_SRC_TRGT_T*                     pt_xng_info)
{
    if(pt_xng_info)
    {
        /*Don't have to check if the target is TV because Banner-base would block the BEFORE_SVC_CHANGED message.*/
        if(INP_SRC_TYPE_TV == pt_xng_info->e_type)
        {
            if(nav_is_same_channel(pt_xng_info->u.t_tv.ui2_crnt_svl_id,
                                   pt_xng_info->u.t_tv.ui2_crnt_svl_rec_id,
                                   pt_xng_info->u.t_tv.ui4_crnt_channel_id,
                                   pt_xng_info->u.t_tv.ui2_trgt_svl_id,
                                   pt_xng_info->u.t_tv.ui2_trgt_svl_rec_id,
                                   pt_xng_info->u.t_tv.ui4_trgt_channel_id))
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}
/*-----------------------------------------------------------------------------
 * audio-related methods implementations
 *---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
 * Name
 *      _audio_info_audio_init
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _audio_info_audio_init(
    AUDIO_INFO_T*                   pt_this)
{
    SM_COMMAND_T                          at_sm_cmds[3];
    CHAR*                                 as_grp_name[TV_WIN_ID_LAST_VALID_ENTRY] = {0};
    INT32                                 i, i4_ret;

    as_grp_name[TV_WIN_ID_MAIN] = SN_PRES_MAIN_DISPLAY;
    as_grp_name[TV_WIN_ID_SUB] = SN_PRES_SUB_DISPLAY;

    do
    {
        for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
        {
            /*scc component for mts operation*/
            at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
            at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
            at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
            at_sm_cmds[1].u.ps_text  = as_grp_name[i];
            at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
            at_sm_cmds[2].u.ui4_data = 0;

            i4_ret = c_scc_comp_open(at_sm_cmds, &pt_this->at_grp[i].h_mts);
            if(SMR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"Fail to open scc component(grp = %d) for mts operation, ret = %d\r\n", i, i4_ret));
                pt_this->at_grp[i].h_mts = NULL_HANDLE;
                i4_ret = NAVR_FAIL;
                break;
            }
        }

        /*check result*/
        if(NAVR_OK == i4_ret)
        {
            return NAVR_OK;
        }

    } while(0);

    _audio_info_audio_deinit(pt_this);
    return NAVR_FAIL;
}

/*------------------------------------------------------------------------------
 * Name
 *      _audio_info_audio_deinit
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _audio_info_audio_deinit(
    AUDIO_INFO_T*                     pt_this)
{
    INT32                                   i, i4_ret;

    for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
    {
        /*close mts handle*/
        if(TRUE == c_handle_valid(pt_this->at_grp[i].h_mts))
        {
            i4_ret = c_scc_comp_close(pt_this->at_grp[i].h_mts);
            if(SMR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s(): Fail to close scc component(grp = %d) for mts operation, ret = %d\r\n", __FUNCTION__, i, i4_ret));
            }
        }

        pt_this->at_grp[i].h_mts = NULL_HANDLE;
    }

    return NAVR_OK;
}

/*------------------------------------------------------------------------------
 * Name
 *      _audio_info_reset_analog_audio
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _audio_info_reset_analog_audio(
    AUDIO_INFO_T*                           pt_this,
    TV_WIN_ID_T                                   e_grp,
    const NAV_XNG_SRC_TRGT_T*                     pt_xng_info)
{
    SCC_AUD_MTS_T                                 e_mts;
    INT32                                         i4_ret;
    INT16                                         i2_value;

    if(pt_xng_info)
    {
        /*Don't have to check if the target is TV because Banner-base would block the BEFORE_SVC_CHANGED message.*/

        if(INP_SRC_TYPE_TV == pt_xng_info->e_type)
        {
            if(nav_is_same_channel(pt_xng_info->u.t_tv.ui2_crnt_svl_id,
                                   pt_xng_info->u.t_tv.ui2_crnt_svl_rec_id,
                                   pt_xng_info->u.t_tv.ui4_crnt_channel_id,
                                   pt_xng_info->u.t_tv.ui2_trgt_svl_id,
                                   pt_xng_info->u.t_tv.ui2_trgt_svl_rec_id,
                                   pt_xng_info->u.t_tv.ui4_trgt_channel_id))
            {
                return NAVR_NO_ACTION;
            }
        }
    }

    /*get setting from config*/
    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS), &i2_value);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"a_cfg_av_get(APP_CFG_RECID_AUD_MTS) failed, ret = %d\r\n", i4_ret));
        e_mts = SCC_AUD_MTS_STEREO;
    }
    else
    {
        e_mts = (SCC_AUD_MTS_T)i2_value;
        switch(e_mts)
        {
        case SCC_AUD_MTS_MONO:
        case SCC_AUD_MTS_STEREO:
        case SCC_AUD_MTS_SUB_LANG:
            break;

#ifdef APP_DVBT_SUPPORT
        case SCC_AUD_MTS_NICAM_MONO:
        case SCC_AUD_MTS_NICAM_STEREO:
        case SCC_AUD_MTS_NICAM_DUAL2:
        case SCC_AUD_MTS_NICAM_DUAL1:
        case SCC_AUD_MTS_DUAL1:
        case SCC_AUD_MTS_DUAL2:
            break;
#endif

        default:
            DBG_ERROR((_ERROR_HEADER"Unknown APP_CFG_RECID_AUD_MTS setting from config.\r\n"));
            e_mts = SCC_AUD_MTS_STEREO;
            break;
        }
    }

    i4_ret = _audio_info_set_mts(pt_this, e_grp, e_mts, NULL);
    if(NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /*turn on dirty flag*/
    pt_this->b_is_mts_changed = FALSE;
    pt_this->b_been_reset = TRUE;
    _AUDIO_INFO_RESET_MTS_BACKUP(pt_this);

    return NAVR_OK;
}

/*------------------------------------------------------------------------------
 * Name
 *      _audio_info_check_mts
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static VOID _audio_info_check_mts(
    AUDIO_INFO_T*         pt_this,
    TV_WIN_ID_T                 e_grp,
    const NAV_XNG_SRC_TRGT_T*   pt_xng_info)
{
    INT32                       i4_ret;

    /*reset mts*/
    //qiang liu fix bug141684   del   FALSE == _AUDIO_INFO_IS_MTS_BY_CAPACITY()
    if(/*FALSE == _AUDIO_INFO_IS_MTS_BY_CAPACITY() && */
       FALSE == pt_this->b_is_mts_changed &&
       FALSE == pt_this->b_is_same_svc_change &&
       FALSE == pt_this->b_been_reset)
    {
        _audio_info_reset_analog_audio(pt_this, e_grp, pt_xng_info);
    }
    //qiang liu fix bug141684   del   FALSE == _AUDIO_INFO_IS_MTS_BY_CAPACITY()
    else if (/*FALSE == _AUDIO_INFO_IS_MTS_BY_CAPACITY() &&*/
             SCC_AUD_MTS_UNKNOWN == pt_this->e_crnt_mts)
    {
        _audio_info_reset_analog_audio(pt_this, e_grp, pt_xng_info);
    }
    else
    {
        i4_ret = c_scc_aud_set_mts(pt_this->at_grp[e_grp].h_mts, pt_this->e_crnt_mts);
        if(SMR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): c_scc_aud_set_mts() failed, i4_ret=%d.\r\n", __FUNCTION__, i4_ret));
        }
    }

}

/*------------------------------------------------------------------------------
 * Name
 *      _audio_info_update_audio_info
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static VOID _audio_info_update_audio_info(
                    AUDIO_INFO_T*         pt_this,
                    TV_WIN_ID_T           e_grp,
                    BOOL                  b_invalid_info_as_no_audio
                    )
{
    INT32            i4_ret;
    UINT32           ui4_scrambled_strm = 0;

    i4_ret = nav_get_ca_status(e_grp, &ui4_scrambled_strm);
    if (i4_ret != NAVR_OK || (ui4_scrambled_strm & ST_MASK_AUDIO) > 0) {
        return;
    }

    _audio_info_reset_sys_info(e_grp);

    /**/
    if(FALSE == pt_this->b_is_audio_info_ready)
    {
        return;
    }

    do
    {
        if(pt_this->e_focus == e_grp)
        {
            if((TRUE == nav_is_signal_loss(e_grp)) ||
               (LOCKED_STATUS_NONE != nav_get_locked_status(e_grp)))
            {
                break;
            }

            if(pt_this->at_grp[e_grp].b_is_digital) /*digital program*/
            {
                i4_ret = _audio_info_update_digital_audio_info(pt_this, e_grp, b_invalid_info_as_no_audio);
            }
            else /*audio program*/
            {
                if(FALSE == nav_is_audio_content_playing(e_grp))
                {
                    break;
                }

                i4_ret = _audio_info_update_analog_audio_info(pt_this, e_grp);
            }

            //b_show = (NAVR_OK != i4_ret) ? FALSE : TRUE;
        }
        else
        {
            _audio_info_reset_sys_info(e_grp);
            //b_show = FALSE;
        }
    } while (0);

/*#warning audio_info_view_display_audio_info*/
    /*i4_ret = audio_info_view_display_audio_info( b_show, TRUE);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"audio_info_view_display_audio_info() failed, ret = %d\r\n", i4_ret));
    }*/
}

/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_update_digital_audio_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_update_digital_audio_info(
                AUDIO_INFO_T*           pt_this,
                TV_WIN_ID_T             e_grp,
                BOOL                    b_invalid_info_as_no_audio
                )
{
    SCDB_REC_T       t_scdb_rec;
    ASH_AUDIO_INFO_T t_audio_info;
    INT32            i4_ret;
    UINT16           ui2_total_amount;
    UINT16           ui2_order;
    SI_SET_INFO_T    t_set_info;

    c_memset(&t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));
	c_memset(&t_scdb_rec, 0, sizeof(SCDB_REC_T));

    i4_ret = nav_get_crnt_audio_info(e_grp,
                                     &t_audio_info,
                                     &t_scdb_rec,
                                     &ui2_total_amount,
                                     &ui2_order);

    if(NAVR_NOT_EXIST == i4_ret
        || (NAVR_OK == i4_ret
            && b_invalid_info_as_no_audio == TRUE
            && t_audio_info.e_channels == ASH_CHANNELS_UNKNOWN))
    {
        c_memset(&t_set_info, 0, sizeof(SI_SET_INFO_T));
        t_set_info.e_category = SI_CATEGORY_AUD_STRM_INFO;
        t_set_info.u.t_aud_strm_info.ui4_info_mask = SI_AUD_INFO_MASK_DIG_AUD_STS;
        t_set_info.u.t_aud_strm_info.e_dig_aud_sts = SI_AUD_DIG_AUD_STS_ABSENT;
        if (NAVR_NOT_EXIST != i4_ret
            &&
            ui2_order != 0 && ui2_total_amount > 1)
        {
            t_set_info.u.t_aud_strm_info.ui4_info_mask |=
                                         SI_AUD_INFO_MASK_SEL_NUM|
                                         SI_AUD_INFO_MASK_SEL_IDX;
            t_set_info.u.t_aud_strm_info.ui2_sel_num = ui2_total_amount;
            t_set_info.u.t_aud_strm_info.ui2_sel_idx = ui2_order - 1;
        }
		/* set audio language with NO AUDIO */
		t_set_info.u.t_aud_strm_info.ui4_info_mask |= SI_AUD_INFO_MASK_DIG_AUD_LANG;
		c_memcpy(t_set_info.u.t_aud_strm_info.s639_dig_aud_lang,
		         t_scdb_rec.u.t_audio_mpeg.s_lang,
		         sizeof(ISO_639_LANG_T));

        a_si_set_item_info_by_win_id(e_grp, &t_set_info);
        return NAVR_OK;
    }

    if(NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    DBG_INFO((_INFO_HEADER"audio - fmt=%d, CHs=%d, sample rate=%d, data rate=%d, bit depth=%d (%s %d/%d)\r\n",
                    t_audio_info.e_aud_fmt,
                    t_audio_info.e_channels,
                    t_audio_info.ui4_sample_rate,
                    t_audio_info.ui4_data_rate,
                    t_audio_info.ui1_bit_depth,
                    t_scdb_rec.u.t_audio_mpeg.s_lang,
                    ui2_order,
                    ui2_total_amount));
    c_memset(&t_set_info, 0, sizeof(SI_SET_INFO_T));
    t_set_info.e_category = SI_CATEGORY_AUD_STRM_INFO;
    t_set_info.u.t_aud_strm_info.ui4_info_mask =
                                SI_AUD_INFO_MASK_DIG_AUD_STS |
                                SI_AUD_INFO_MASK_DIG_AUD_LANG |
                                SI_AUD_INFO_MASK_DIG_AUD_INFO ;
    t_set_info.u.t_aud_strm_info.e_dig_aud_sts = SI_AUD_DIG_AUD_STS_NORMAL;
#ifdef APP_DVBT_SUPPORT
    do {
        HANDLE_T            h_svctx;
        TV_WIN_ID_T         e_tv_win_id;
        SM_COND_T           e_sm_cond;
        SIZE_T              z_size = sizeof(SM_COND_T);

        t_set_info.u.t_aud_strm_info.ui4_info_mask |= SI_AUD_INFO_MASK_DIG_AUD_TYPE;
        t_set_info.u.t_aud_strm_info.e_dig_aud_type = AUD_TYPE_UNKNOWN;

        if (AUD_TYPE_HEARING_IMPAIRED == t_scdb_rec.u.t_audio_mpeg.e_type){
            t_set_info.u.t_aud_strm_info.e_dig_aud_type = AUD_TYPE_HEARING_IMPAIRED;
        }
        else if (AUD_TYPE_VISUAL_IMPAIRED == t_scdb_rec.u.t_audio_mpeg.e_type){
            t_set_info.u.t_aud_strm_info.e_dig_aud_type = AUD_TYPE_VISUAL_IMPAIRED;
        }
        else
        {
            i4_ret = nav_get_focus_id(&e_tv_win_id);
            if (NAVR_OK != i4_ret){
                DBG_ERROR((_ERROR_HEADER"%s():nav_get_focus_id(), ret = %d\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = nav_get_svctx_handle(e_tv_win_id, &h_svctx);
            if (NAVR_OK != i4_ret){
                DBG_ERROR((_ERROR_HEADER"%s():nav_get_svctx_handle(), ret = %d\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_svctx_get(h_svctx,
                                 SVCTX_CH_GET_AUX_AUDIO_STATUS,
                                 &e_sm_cond,
                                 &z_size);
            if(i4_ret != SVCTXR_OK){
                DBG_ERROR((_ERROR_HEADER"%s():c_svctx_get(), ret = %d\r\n", __FUNCTION__, i4_ret));
                break;
            }

            if (SM_COND_STARTED == e_sm_cond){
                t_set_info.u.t_aud_strm_info.e_dig_aud_type = AUD_TYPE_VISUAL_IMPAIRED;
            }
        }
    }while(0);

    c_memcpy(t_set_info.u.t_aud_strm_info.s639_dig_aud_lang,
             t_scdb_rec.u.t_audio_mpeg.s_lang,
             sizeof(ISO_639_LANG_T));

#ifdef APP_NAV_AI_MONO_COMBINED_STEREO_SUPPORT
    if (t_scdb_rec.e_rec_type == SCDB_REC_TYPE_AUDIO_MPEG &&
        t_scdb_rec.u.t_audio_mpeg.ui1_index == 2 &&  /* index of fake stereo */
        t_scdb_rec.u.t_audio_mpeg.e_aud_fmt == AUD_FMT_DUAL_MONO &&
        t_scdb_rec.u.t_audio_mpeg.s_lang[0] == '\0')
    {
        NAV_AUD_COMBINED_STEREO_INFO_T  t_aud_lang_info = {0};

        t_aud_lang_info.pt_scdb_rec = &t_scdb_rec;
        i4_ret = audio_info_get_combined_stereo_info(&t_aud_lang_info);
        if (i4_ret == NAVR_OK)
        {
            if (t_aud_lang_info.b_dual_1_valid == TRUE &&
                t_aud_lang_info.b_dual_2_valid == TRUE &&
                c_strcmp(t_aud_lang_info.s_dual_1_lang, t_aud_lang_info.s_dual_2_lang) != 0)
            {
                c_memcpy(t_set_info.u.t_aud_strm_info.s639_dig_aud_lang,
                         t_aud_lang_info.s_dual_1_lang,
                         sizeof(ISO_639_LANG_T));
                /* Support 2nd language */
                t_set_info.u.t_aud_strm_info.ui4_info_mask |= SI_AUD_INFO_MASK_DIG_AUD_LANG2;
                c_memcpy(t_set_info.u.t_aud_strm_info.s639_dig_aud_lang2,
                         t_aud_lang_info.s_dual_2_lang,
                         sizeof(ISO_639_LANG_T));
            }
            else if (t_aud_lang_info.b_dual_1_valid == TRUE)
            {
                c_memcpy(t_set_info.u.t_aud_strm_info.s639_dig_aud_lang,
                         t_aud_lang_info.s_dual_1_lang,
                         sizeof(ISO_639_LANG_T));
            }
            else if (t_aud_lang_info.b_dual_2_valid == TRUE)
            {
                c_memcpy(t_set_info.u.t_aud_strm_info.s639_dig_aud_lang2,
                         t_aud_lang_info.s_dual_2_lang,
                         sizeof(ISO_639_LANG_T));
            }
        }

        /* hardcode ASH_CHANNELS_T as STEREO instead of DUAL MONO */
        t_set_info.u.t_aud_strm_info.ui4_info_mask |= SI_AUD_INFO_MASK_DIG_AUD_INFO;
        t_audio_info.e_channels = ASH_CHANNELS_STEREO;
    }
#endif /* APP_NAV_AI_MONO_COMBINED_STEREO_SUPPORT */

#else /* APP_DVBT_SUPPORT */
    c_memcpy(t_set_info.u.t_aud_strm_info.s639_dig_aud_lang,
             t_scdb_rec.u.t_audio_mpeg.s_lang,
             sizeof(ISO_639_LANG_T));
#endif /* APP_DVBT_SUPPORT */

    t_set_info.u.t_aud_strm_info.t_dig_aud_info = t_audio_info;

    if (t_scdb_rec.u.t_audio_mpeg.e_type != AUD_TYPE_UNKNOWN)
    {
        t_set_info.u.t_aud_strm_info.ui4_info_mask |= SI_AUD_INFO_MASK_DIG_AUD_TYPE;
        t_set_info.u.t_aud_strm_info.e_dig_aud_type = t_scdb_rec.u.t_audio_mpeg.e_type;
    }

    if (ui2_order != 0 && ui2_total_amount > 1)
    {
        t_set_info.u.t_aud_strm_info.ui4_info_mask |=
                                    SI_AUD_INFO_MASK_SEL_NUM |
                                    SI_AUD_INFO_MASK_SEL_IDX ;
        t_set_info.u.t_aud_strm_info.ui2_sel_num = ui2_total_amount;
        t_set_info.u.t_aud_strm_info.ui2_sel_idx = ui2_order - 1;
    }

    a_si_set_item_info_by_win_id(e_grp, &t_set_info);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_update_analog_audio_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_update_analog_audio_info(
                    AUDIO_INFO_T*       pt_this,
                    TV_WIN_ID_T         e_grp
                    )
{
    SI_SET_INFO_T   t_set_info;

#if 0
    BOOL            b_is_ready;

    _AUDIO_INFO_IS_ANALOG_AUDIO_CAPACITY_READY(b_is_ready, e_grp);
    if(FALSE == b_is_ready)
    {
        return NAVR_FAIL;
    }
#endif
    DBG_LOG_PRINT(("[audio_info +++] {%s %s() %d}. care for checking\n",__FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_set_info, 0, sizeof(SI_SET_INFO_T));
    t_set_info.e_category = SI_CATEGORY_AUD_STRM_INFO;
    t_set_info.u.t_aud_strm_info.ui4_info_mask = SI_AUD_INFO_MASK_ANA_AUD_MTS;
    t_set_info.u.t_aud_strm_info.e_ana_aud_mts = pt_this->e_crnt_mts;
    a_si_set_item_info_by_win_id(e_grp, &t_set_info);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_set_mts
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_set_mts(
    AUDIO_INFO_T*                pt_this,
    TV_WIN_ID_T                        e_grp,
    SCC_AUD_MTS_T                      e_mts_new,
    const SCC_AUD_MTS_T*               pe_mts_crnt)
{
    INT32                              i4_ret;
    SCC_AUD_MTS_T                      e_mts_crnt;

    if(pe_mts_crnt)
    {
        e_mts_crnt = *pe_mts_crnt;
    }
    else
    {
        e_mts_crnt = pt_this->e_crnt_mts;
    }

    if( e_mts_crnt != e_mts_new ||
		pt_this->b_aud_ch_alg_mts == TRUE )
    {
        pt_this->e_crnt_mts = e_mts_new;
		pt_this->b_aud_ch_alg_mts = FALSE;
        i4_ret = c_scc_aud_set_mts(pt_this->at_grp[e_grp].h_mts, e_mts_new);
        if(SMR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): c_scc_aud_set_mts() failed, i4_ret=%d.\r\n", __FUNCTION__, i4_ret));
            return NAVR_FAIL;
        }
        if (SMR_OK == i4_ret)
        {
            if(FALSE == nav_is_audio_content_playing(e_grp))
            {
                return NAVR_OK;
            }

            _audio_info_update_analog_audio_info(pt_this, e_grp);
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_mts_cfg_change_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _audio_info_mts_cfg_change_cb(
    UINT16                      ui2_nfy_id,
    VOID*                       pv_tag,
    UINT16                      ui2_id)
{
    AUDIO_INFO_T*         pt_this = &t_g_audio_info;

    if(pt_this->ui2_mts_cfg_nfy == ui2_nfy_id && CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS) == ui2_id)
    {
        /*post a message to itself*/
        nav_request_context_switch(_audio_info_mts_cfg_change_msg_hdlr,
                                   NULL,
                                   NULL,
                                   NULL);
    }
}

/*----------------------------------------------------------------------------
 * Name: _nav_sbti_cfg_change_msg_hdlr
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _audio_info_mts_cfg_change_msg_hdlr(
    VOID*                       pv_unused,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3)
{
    AUDIO_INFO_T*         pt_this = &t_g_audio_info;

    pt_this->b_is_mts_changed = FALSE; /*use config setting*/
    pt_this->b_from_cfg = TRUE;
    _AUDIO_INFO_CFG_XNG(pt_this, pt_this->e_focus);
    pt_this->b_from_cfg = FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      audio_info_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 audio_info_key_handler(
                    AUDIO_INFO_T*       pt_this,
                    TV_WIN_ID_T         e_grp,
                    UINT32              ui4_key_code
                    )
{
    INT32               i4_ret = NAVR_OK;
    SIZE_T              z_size;
    UINT32              ui4_info_status;
    UINT8               ui1_icl_mask;

    switch(ui4_key_code)
    {
    case BTN_MTS:
        {
            if((TRUE == _audio_info_is_svl_empty(e_grp)) ||
               (TRUE == nav_is_signal_loss(e_grp)) ||
               (LOCKED_STATUS_NONE != nav_get_locked_status(e_grp)))
            {
                break;
            }

#ifdef APP_NAV_DISABLE_MTS_WHEN_VIDEO_HD_NOT_SUPPORT
            if((TRUE == nav_is_video_hd_not_support(e_grp)) || ( TRUE == nav_is_video_codec_not_support(e_grp)))
            {
                break;
            }
#endif
            /* Reset timer */
            _audio_info_reset_timer(pt_this);

            if(pt_this->at_grp[e_grp].b_is_digital)
            {
                i4_ret = nav_select_next_audio_stream(e_grp);

                if(NAVR_OK != i4_ret)
                {
                    break;
                }

                if (TV_WIN_ID_MAIN == e_grp)
                {
                    z_size = ICL_RECID_MAIN_RUNNING_STS_MASK_SIZE;
                    ui1_icl_mask = ICL_RECID_MAIN_RUNNING_STS_MASK;
                }
                else
                {
                    z_size = ICL_RECID_SUB_RUNNING_STS_MASK_SIZE;
                    ui1_icl_mask = ICL_RECID_SUB_RUNNING_STS_MASK;
                }

                a_icl_get(ICL_MAKE_ID(ICL_GRPID_RUNNING_SERVICE, ui1_icl_mask),
                                   &ui4_info_status,
                                   &z_size);


                ui4_info_status |= ICL_CHANNEL_RUNNING_STS_TV_AUDIO_LANG_MANUAL_SELECTION;

                a_icl_set(ICL_MAKE_ID(ICL_GRPID_RUNNING_SERVICE, ui1_icl_mask),
                                   (VOID*)&ui4_info_status,
                                   z_size);

                _audio_info_reset_sys_info(e_grp);
            }
            else
            {
                _AUDIO_INFO_SWITCH_ANALOG_AUDIO(pt_this,
                                                      _AUDIO_INFO_SAM_NEXT,
                                                      e_grp,
                                                      SCC_AUD_MTS_UNKNOWN,
                                                      i4_ret);
                if(NAVR_OK != i4_ret)
                {
                    break;
                }
            }

            _audio_info_handle_fmt_update(pt_this);
        }
        break;

    default:
        break;
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * customization methods implementations
 *---------------------------------------------------------------------------*/
#ifndef APP_NAV_AI_MTS_BY_CAPACITY
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_switch_analog_audio
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_switch_analog_audio(
                AUDIO_INFO_T*                       pt_this,
                _AUDIO_INFO_SWITCH_AUDIO_METHOD_T   e_method,
                TV_WIN_ID_T                         e_grp,
                SCC_AUD_MTS_T                       e_mts_info /*for _AUDIO_INFO_SAM_BY_INFO*/
                )
{
    INT32                                          i4_ret = NAVR_OK;
    SCC_AUD_MTS_T                                  e_mts_new = SCC_AUD_MTS_UNKNOWN;
    SCC_AUD_MTS_T                                  e_mts_crnt = SCC_AUD_MTS_UNKNOWN;
    SCC_AUD_MTS_T*                                 pe_mts_crnt = NULL;
    SI_SET_INFO_T                                  t_set_info;

    switch(e_method)
    {
    case _AUDIO_INFO_SAM_NEXT:
    case _AUDIO_INFO_SAM_PREV:
        {
            /*get current mts*/
            e_mts_crnt = pt_this->e_crnt_mts;

            /*new mts setting*/
            if(_AUDIO_INFO_SAM_NEXT == e_method)
            {
                _AUDIO_INFO_GET_NEXT_MTS(e_mts_crnt, e_mts_new);
                e_mts_info = e_mts_new;
            }
            else
            {
                _AUDIO_INFO_GET_PREV_MTS(e_mts_crnt, e_mts_new);
                e_mts_info = e_mts_new;
            }

            pe_mts_crnt = &e_mts_crnt;
        }
        break;

    case _AUDIO_INFO_SAM_FIRST:
        {
            _AUDIO_INFO_GET_FIRST_MTS(e_mts_new);
            pe_mts_crnt = &e_mts_crnt;
        }
        break;

    case _AUDIO_INFO_SAM_BY_INFO:
        {
            if(SCC_AUD_MTS_UNKNOWN == e_mts_info)
            {
                DBG_ERROR((_ERROR_HEADER"%s(): Unknown MTS setting.\r\n", __FUNCTION__));
                return NAVR_FAIL;
            }

            pe_mts_crnt = NULL;
        }
        break;

    case _AUDIO_INFO_SAM_NONE:
    default:
        return NAVR_OK;
    }

    /*set mts*/
    i4_ret = _audio_info_set_mts(pt_this, e_grp, e_mts_info, pe_mts_crnt);
    if(NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /*save mts*/
    if(FALSE == pt_this->b_from_cfg)
    {
        _AUDIO_INFO_SAVE_MTS(pt_this, e_mts_info, i4_ret);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"Save MTS failed, ret = %d\r\n", i4_ret));
        }
    }
    c_memset(&t_set_info, 0, sizeof(SI_SET_INFO_T));
    t_set_info.e_category = SI_CATEGORY_AUD_STRM_INFO;
    t_set_info.u.t_aud_strm_info.ui4_info_mask = SI_AUD_INFO_MASK_ANA_AUD_MTS;
    t_set_info.u.t_aud_strm_info.e_ana_aud_mts = e_mts_info;
    a_si_set_item_info_by_win_id(e_grp, &t_set_info);

    return NAVR_OK;
}

#else
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_reselect_analog_audio
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_reselect_analog_audio(
    AUDIO_INFO_T*                              pt_this,
    TV_WIN_ID_T                                      e_grp)
{
    INT32                                            i4_ret;
    SCC_AUD_MTS_T                                    e_crnt_mts;

    /*if(FALSE == pt_this->b_been_reset && FALSE == pt_this->b_is_same_svc_change)*/
    if(_AUDIO_INFO_IS_FORCE_RESELECT() || FALSE == pt_this->b_is_mts_changed)  /*Should always reset if audio format changed*/
    {
        _audio_info_reset_analog_audio(pt_this, e_grp, NULL);

        /*get new mts*/
        e_crnt_mts = pt_this->e_crnt_mts;
    }
    else
    {
        e_crnt_mts = pt_this->e_crnt_mts;

        /*reset by the backup mts.*/
        /*This is for resolving following case:
            1. Toggle to Dual2
            2. Weak signal (reselect to Mono)
            3. Normal signal (Not switch back to Dual2 becasue the b_mts_changed is TRUE)
        */
        if(SCC_AUD_MTS_UNKNOWN != pt_this->e_capacity_backup && e_crnt_mts != pt_this->e_capacity_backup)
        {
            i4_ret = _audio_info_set_mts(pt_this, e_grp, pt_this->e_capacity_backup, &e_crnt_mts);
            if(NAVR_OK != i4_ret)
            {
                return NAVR_FAIL;
            }

            e_crnt_mts = pt_this->e_capacity_backup;
        }
        else
        {
            e_crnt_mts = SCC_AUD_MTS_UNKNOWN;
            i4_ret = _audio_info_set_mts(pt_this, e_grp, pt_this->e_crnt_mts, &e_crnt_mts);
            if(NAVR_OK != i4_ret)
            {
                return NAVR_FAIL;
            }

            e_crnt_mts = pt_this->e_crnt_mts;
        }
    }

    /*check current mts setting*/
    i4_ret = _audio_info_switch_analog_audio_by_capacity(pt_this, _AUDIO_INFO_SAM_BY_INFO, e_grp, e_crnt_mts, FALSE);
    if(NAVR_OK != i4_ret)
    {
        /*original setting isn't avaiable. Try the next one*/
        i4_ret = _audio_info_switch_analog_audio_by_capacity(pt_this, _AUDIO_INFO_SAM_FIRST, e_grp, SCC_AUD_MTS_UNKNOWN, FALSE);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): Fail to re-select a suitable mts setting, i4_ret=%d.\r\n", __FUNCTION__, i4_ret));
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_get_analog_audio_channel
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_get_analog_audio_channel(
    TV_WIN_ID_T                                    e_grp,
    ASH_CHANNELS_T*                                pe_audio_channel)
{
    ASH_AUDIO_INFO_T                               t_audio_ash;
    HANDLE_T                                       h_svctx;
    INT32                                          i4_ret;

    i4_ret = nav_get_svctx_handle(e_grp, &h_svctx);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): nav_get_svctx_handle(win=%d) failed, i4_ret=%d.\r\n", __FUNCTION__, e_grp, i4_ret));
        return NAVR_FAIL;
    }

    /*get stream capacity*/
    i4_ret = c_svctx_get_audio_info(h_svctx, &t_audio_ash);
    if(SVCTXR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_svctx_get_audio_info() failed. i4_ret=%d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    DBG_INFO((_INFO_HEADER"Audio-Format=0x%.8x, Audio-Channel=0x%.8x.\r\n", t_audio_ash.e_aud_fmt, t_audio_ash.e_channels));

    /*if(ASH_AUDIO_FMT_MTS != t_audio_ash.e_aud_fmt && ASH_AUDIO_FMT_TV_SYS != t_audio_ash.e_aud_fmt)*/
    if(FALSE == _AUDIO_INFO_IS_ANALOG_AUDIO_FMT(t_audio_ash.e_aud_fmt))
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Not analog audio.\r\n", __FUNCTION__));
        return NAVR_FAIL;
    }

    *pe_audio_channel = t_audio_ash.e_channels;
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_switch_analog_audio_by_capacity
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_switch_analog_audio_by_capacity(
                AUDIO_INFO_T*                       pt_this,
                _AUDIO_INFO_SWITCH_AUDIO_METHOD_T   e_method,
                TV_WIN_ID_T                         e_grp,
                SCC_AUD_MTS_T                       e_mts_info,        /*for _AUDIO_INFO_SAM_BY_INFO*/
                BOOL                                b_by_key
                )
{
    INT32                   i4_ret, i4_mts_count, i4_mts_idx;
    SCC_AUD_MTS_T           ae_mts[_AUDIO_INFO_MTS_ARRAY_SIZE], e_crnt_mts;
    ASH_CHANNELS_T          e_channel;
    SI_SET_INFO_T           t_set_info;

    /**/
    i4_ret = _audio_info_get_analog_audio_channel(e_grp, &e_channel);
    if(NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    if(ASH_CHANNELS_UNKNOWN == e_channel)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Analog audio capacity isn't ready.\r\n", __FUNCTION__));
        return NAVR_FAIL;
    }

    /*get current mts*/
    e_crnt_mts = pt_this->e_crnt_mts;

    if(_AUDIO_INFO_SAM_NEXT == e_method || _AUDIO_INFO_SAM_PREV == e_method)
    {
        e_mts_info = e_crnt_mts;
    }

    _audio_info_convert_mts(e_channel, &e_mts_info);

    /*get available mts setting*/
    i4_mts_count = _AUDIO_INFO_MTS_ARRAY_SIZE;
    i4_ret = a_aud_mts_get_all_avail(e_channel, &i4_mts_count, ae_mts);
    if(AAUDR_OK != i4_ret || 0 == i4_mts_count)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Not available setting.\r\n", __FUNCTION__));
        return NAVR_FAIL;
    }

    if(_AUDIO_INFO_SAM_FIRST == e_method)
    {
        i4_mts_idx = 0;
    }
    else
    {
        for(i4_mts_idx = 0; i4_mts_idx < i4_mts_count; i4_mts_idx++)
        {
            if(ae_mts[i4_mts_idx] == e_mts_info)
            {
                switch(e_method)
                {
                case _AUDIO_INFO_SAM_NEXT:
                    {
                        i4_mts_idx++;
                        if(i4_mts_idx >= i4_mts_count)
                        {
                            i4_mts_idx = 0;
                        }
                    }
                    break;

                case _AUDIO_INFO_SAM_PREV:
                    {
                        i4_mts_idx--;
                        if(i4_mts_idx < 0)
                        {
                            i4_mts_idx = i4_mts_count - 1;
                        }
                    }
                    break;

                case _AUDIO_INFO_SAM_BY_INFO:
                    break;

                case _AUDIO_INFO_SAM_NONE:
                default:
                    return NAVR_OK;
                }

                break;
            }
        }

        if(i4_mts_idx >= i4_mts_count)
        {
            if(_AUDIO_INFO_SAM_BY_INFO == e_method)
            {
                DBG_ERROR((_ERROR_HEADER"%s(): Not selected mts setting isn't available.\r\n", __FUNCTION__));
                return NAVR_FAIL;
            }
            else
            {
                i4_mts_idx = 0;
            }
        }
    }

    /*check mts*/
    if(e_crnt_mts == ae_mts[i4_mts_idx])    /*same setting*/
    {
        return NAVR_OK;
    }

    /*backup original mts*/
    if(FALSE == b_by_key && pt_this->b_is_mts_changed)
    {
        pt_this->e_capacity_backup = e_crnt_mts;
    }
    else
    {
        _AUDIO_INFO_RESET_MTS_BACKUP(pt_this);
    }

    /*set mts*/
    i4_ret = _audio_info_set_mts(pt_this, e_grp, ae_mts[i4_mts_idx], &e_crnt_mts);
    if(NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    if(b_by_key)
    {
        /*save mts*/
        _AUDIO_INFO_SAVE_MTS(pt_this, ae_mts[i4_mts_idx], i4_ret);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"Save MTS failed, ret = %d\r\n", i4_ret));
        }
    }

    c_memset(&t_set_info, 0, sizeof(SI_SET_INFO_T));
    t_set_info.e_category = SI_CATEGORY_AUD_STRM_INFO;
    t_set_info.u.t_aud_strm_info.ui4_info_mask = SI_AUD_INFO_MASK_ANA_AUD_MTS;
    t_set_info.u.t_aud_strm_info.e_ana_aud_mts = ae_mts[i4_mts_idx];
    a_si_set_item_info_by_win_id(e_grp, &t_set_info);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_is_analog_audio_capacity_ready
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _audio_info_is_analog_audio_capacity_ready(
    TV_WIN_ID_T                                              e_grp)
{
    INT32               i4_ret;
    ASH_CHANNELS_T      e_channel;

    i4_ret = _audio_info_get_analog_audio_channel(e_grp, &e_channel);
    return (NAVR_OK == i4_ret && ASH_CHANNELS_UNKNOWN != e_channel) ? TRUE : FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_convert_mts
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _audio_info_convert_mts(
    ASH_CHANNELS_T                        e_channel,
    SCC_AUD_MTS_T*                        pe_mts)
{
    switch(e_channel)
    {
    case ASH_CHANNELS_FM_MONO_NICAM_MONO:
    case ASH_CHANNELS_FM_MONO_NICAM_STEREO:
    case ASH_CHANNELS_FM_MONO_NICAM_DUAL:
        switch(*pe_mts)
        {
        case SCC_AUD_MTS_STEREO:
            *pe_mts = SCC_AUD_MTS_NICAM_STEREO;
            break;
        case SCC_AUD_MTS_DUAL1:
            *pe_mts = SCC_AUD_MTS_NICAM_DUAL1;
            break;
        case SCC_AUD_MTS_DUAL2:
            *pe_mts = SCC_AUD_MTS_NICAM_DUAL2;
            break;
        default:
            break;
        }
        break;

    case ASH_CHANNELS_MONO:
    case ASH_CHANNELS_DUAL_MONO:
    case ASH_CHANNELS_MONO_SUB:
    case ASH_CHANNELS_STEREO:
    case ASH_CHANNELS_STEREO_SUB:
        switch(*pe_mts)
        {
        case SCC_AUD_MTS_NICAM_STEREO:
            *pe_mts = SCC_AUD_MTS_STEREO;
            break;
        case SCC_AUD_MTS_NICAM_DUAL1:
            *pe_mts = SCC_AUD_MTS_DUAL1;
            break;
        case SCC_AUD_MTS_NICAM_DUAL2:
            *pe_mts = SCC_AUD_MTS_DUAL2;
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}

#endif /*APP_NAV_AI_MTS_BY_CAPACITY*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ai_pause_audio
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
VOID _nav_ai_pause_audio (
                    VOID*               pv_tag1,
                    VOID*               pv_tag2,
                    VOID*               pv_tag3
                    )
{
    INT32               i4_ret;
    ICL_ID_TYPE         e_icl_id;
    TV_WIN_ID_T         e_foucs_id;
    SIZE_T              z_size = sizeof(TV_WIN_ID_T);
    STREAM_COMP_ID_T    t_comp_id;
    SCDB_REC_T          t_scdb_rec;
    AUDIO_INFO_T*       pt_this = &t_g_audio_info;
    ICL_ID_TYPE         e_id;
    UINT32              ui4_info_status;

    /* Get audio focus win */
    e_icl_id = ICL_MAKE_ID(ICL_GRPID_PIP_POP, ICL_RECID_AUDIO_FOCUS);
    i4_ret = a_icl_get(e_icl_id, &e_foucs_id, &z_size);

    if (i4_ret != ICLR_OK)
    {
        DBG_ERROR (("[NAV][AUD]%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return;
    }

    /* Keep current audio info */
    c_memset (&t_scdb_rec, 0, sizeof(SCDB_REC_T)) ;
    i4_ret = nav_get_using_strm_data(
                    e_foucs_id,
                    ST_AUDIO,
                    &t_comp_id,
                    &t_scdb_rec
                    );
    if (i4_ret == NAVR_OK)
    {
        c_sema_lock(pt_this->h_mtx_sema, X_SEMA_OPTION_WAIT);
        pt_this->t_paused_aud.e_type = t_scdb_rec.e_rec_type;
        pt_this->t_paused_aud.t_comp_id = t_comp_id;
        if (t_scdb_rec.e_rec_type == SCDB_REC_TYPE_AUDIO_MPEG)
        {
            pt_this->t_paused_aud.t_mpeg = t_scdb_rec.u.t_audio_mpeg;
        }
        c_sema_unlock(pt_this->h_mtx_sema);
    }
    else
    {
        pt_this->t_paused_aud.e_type = SCDB_REC_TYPE_UNKNOWN;
        return;
    }

    /* Stop audio stream */
    i4_ret = nav_sync_stop_stream(e_foucs_id, ST_AUDIO);

    if (i4_ret == NAVR_OK)
    {
        /* indicate audio is paused */
        pt_this->b_aud_paused = TRUE;

        /* Disable scdb update audio handler for main */
        e_id =  ICL_MAKE_ID (ICL_GRPID_RUNNING_SERVICE, ICL_RECID_MAIN_RUNNING_STS_MASK);
        z_size = ICL_RECID_MAIN_RUNNING_STS_MASK_SIZE;
        i4_ret = a_icl_get(e_id, &ui4_info_status, &z_size);
        if (i4_ret != ICLR_OK)
        {
            DBG_ERROR (("[NAV][AUD]%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        }
        ui4_info_status |= ICL_CHANNEL_RUNNING_STS_DISABLE_SCDB_AUDIO_UPDATE;
        i4_ret = a_icl_set(e_id, &ui4_info_status, z_size);
        if (i4_ret != ICLR_OK)
        {
            DBG_ERROR (("[NAV][AUD]%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        }

        /* Disable scdb update audio handler for sub */
        e_id =  ICL_MAKE_ID (ICL_GRPID_RUNNING_SERVICE, ICL_RECID_SUB_RUNNING_STS_MASK);
        z_size = ICL_RECID_MAIN_RUNNING_STS_MASK_SIZE;
        i4_ret = a_icl_get(e_id, &ui4_info_status, &z_size);
        if (i4_ret != ICLR_OK)
        {
            DBG_ERROR (("[NAV][AUD]%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        }
        ui4_info_status |= ICL_CHANNEL_RUNNING_STS_DISABLE_SCDB_AUDIO_UPDATE;
        i4_ret = a_icl_set(e_id, &ui4_info_status, z_size);
        if (i4_ret != ICLR_OK)
        {
            DBG_ERROR (("[NAV][AUD]%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ai_resume_aud_strm_comp_filter
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static BOOL _nav_ai_resume_aud_strm_comp_filter (
                    UINT16                      ui2_num_recs,
                    UINT16                      ui2_idx,
                    const STREAM_COMP_ID_T*     pt_comp_id,
                    const SCDB_REC_T*           pt_scdb_rec,
                    VOID*                       pv_tag
                    )
{
    _NAV_AUD_STRM_INFO_T* pt_audio = (_NAV_AUD_STRM_INFO_T*)pv_tag;

    if (pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_AUDIO_MPEG) {
        if (pt_audio != NULL && pt_audio->e_type == SCDB_REC_TYPE_AUDIO_MPEG) {
            if (TRUE == a_aud_is_same_audio_mpeg_stream (
                                    pt_scdb_rec->u.t_audio_mpeg,
                                    pt_audio->t_mpeg)) {
                return TRUE;
            }

            if (ui2_idx < ui2_num_recs) {
                /* if not the last chance (ui2_idx == ui2_num_recs),
                 * just to iterate to next.
                 */
                return FALSE;
            } else {
                /* if last chance, just select this one */
                return TRUE;
            }
        }
    }

    return nav_default_audio_strm_comp_filter(
                    ui2_num_recs,
                    ui2_idx,
                    pt_comp_id,
                    pt_scdb_rec
                    );
}

/*---------------------------------------------------------------------------
 * Name
 *      _nav_view_mono_combined_stereo_lang_filter_fct
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
#ifdef APP_NAV_AI_MONO_COMBINED_STEREO_SUPPORT
static BOOL _audio_info_combined_stereo_lang_filter_fct(
                    UINT16                      ui2_num_recs,
                    UINT16                      ui2_idx,
                    const STREAM_COMP_ID_T*     pt_comp_id,
                    const SCDB_REC_T*           pt_scdb_rec,
                    VOID*                       pv_fltr_tag
                    )
{
    NAV_AUD_COMBINED_STEREO_INFO_T* pt_aud_lang = (NAV_AUD_COMBINED_STEREO_INFO_T*)pv_fltr_tag;

    if (pt_scdb_rec->u.t_audio_mpeg.ui2_pid == pt_aud_lang->pt_scdb_rec->u.t_audio_mpeg.ui2_pid &&
        pt_scdb_rec->u.t_audio_mpeg.e_aud_fmt == AUD_FMT_DUAL_MONO)
    {
        if (pt_scdb_rec->u.t_audio_mpeg.ui1_index == 0)
        {
            c_strcpy(pt_aud_lang->s_dual_1_lang, pt_scdb_rec->u.t_audio_mpeg.s_lang);
            pt_aud_lang->b_dual_1_valid = TRUE;
        }
        else if (pt_scdb_rec->u.t_audio_mpeg.ui1_index == 1)
        {
            c_strcpy(pt_aud_lang->s_dual_2_lang, pt_scdb_rec->u.t_audio_mpeg.s_lang);
            pt_aud_lang->b_dual_2_valid = TRUE;
        }
        if (pt_aud_lang->b_dual_1_valid == TRUE &&
            pt_aud_lang->b_dual_2_valid == TRUE)
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      audio_info_get_combined_stereo_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 audio_info_get_combined_stereo_info(
                NAV_AUD_COMBINED_STEREO_INFO_T*  pt_aud_lang_info
                )
{
    INT32               i4_ret;
    TV_WIN_ID_T         e_tv_win_id;
    STREAM_COMP_ID_T    t_comp_id;
    HANDLE_T            h_svctx;

    i4_ret = nav_get_focus_id(&e_tv_win_id);
    if (NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s():nav_get_focus_id(), ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    i4_ret = nav_get_svctx_handle(e_tv_win_id, &h_svctx);
    if (NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s():nav_get_svctx_handle(), ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    i4_ret = c_svctx_get_stream_comp_id(h_svctx,
                                        ST_AUDIO,
                                        _audio_info_combined_stereo_lang_filter_fct,
                                        (VOID*)pt_aud_lang_info,
                                        &t_comp_id,
                                        NULL);
    if (NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s():c_svctx_get_stream_comp_id(), ret = %d\r\n", __FUNCTION__, i4_ret));
        return i4_ret;
    }

    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ai_resume_audio
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
VOID _nav_ai_resume_audio (
                    VOID*               pv_tag1,
                    VOID*               pv_tag2,
                    VOID*               pv_tag3
                    )
{
    INT32               i4_ret;
    ICL_ID_TYPE         e_icl_id;
    TV_WIN_ID_T         e_foucs_id;
    SIZE_T              z_size = sizeof(TV_WIN_ID_T);
    STREAM_COMP_ID_T    t_using_comp_id;
    SCDB_REC_T          t_using_scdb_rec;
    AUDIO_INFO_T*       pt_this = &t_g_audio_info;
    ICL_ID_TYPE         e_id;
    UINT32              ui4_info_status;

    do {
        /* Get audio focus win */
        e_icl_id = ICL_MAKE_ID(ICL_GRPID_PIP_POP, ICL_RECID_AUDIO_FOCUS);
        i4_ret = a_icl_get(e_icl_id, &e_foucs_id, &z_size);

        if (i4_ret != ICLR_OK)
        {
            DBG_ERROR (("[NAV][AUD]%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            break;
        }

        i4_ret = nav_get_using_strm_data(
                        e_foucs_id,
                        ST_AUDIO,
                        &t_using_comp_id,
                        &t_using_scdb_rec
                        );
        if (i4_ret == NAVR_OK) {
            break;
        }
        else
        {
            /* try to play the stored one */
            if (pt_this->t_paused_aud.e_type != SCDB_REC_TYPE_UNKNOWN) {
                i4_ret = nav_get_stream_comp_id(
                            e_foucs_id,
                            ST_AUDIO,
                            _nav_ai_resume_aud_strm_comp_filter,
                            &pt_this->t_paused_aud,
                            &t_using_comp_id,
                            &t_using_scdb_rec
                            );
                if (i4_ret == NAVR_OK) {
                    i4_ret = nav_select_stream(e_foucs_id, &t_using_comp_id);
                }
            }

            if (i4_ret != NAVR_OK) {
                /* still cannot find comp_id, try to play the default one */
                i4_ret = nav_select_default_audio_stream(e_foucs_id, &t_using_comp_id);
            }
        }
    }
    while(0);

    /* indicate audio isn't paused */
    pt_this->b_aud_paused = FALSE;

    /* Disable scdb update audio handler for main */
    e_id =  ICL_MAKE_ID (ICL_GRPID_RUNNING_SERVICE, ICL_RECID_MAIN_RUNNING_STS_MASK);
    z_size = ICL_RECID_MAIN_RUNNING_STS_MASK_SIZE;
    i4_ret = a_icl_get(e_id, &ui4_info_status, &z_size);
    if (i4_ret != ICLR_OK)
    {
        DBG_ERROR (("[NAV][AUD]%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }
    ui4_info_status &= ~ICL_CHANNEL_RUNNING_STS_DISABLE_SCDB_AUDIO_UPDATE;
    i4_ret = a_icl_set(e_id, &ui4_info_status, z_size);
    if (i4_ret != ICLR_OK)
    {
        DBG_ERROR (("[NAV][AUD]%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }

    /* Disable scdb update audio handler for sub */
    e_id =  ICL_MAKE_ID (ICL_GRPID_RUNNING_SERVICE, ICL_RECID_SUB_RUNNING_STS_MASK);
    z_size = ICL_RECID_SUB_RUNNING_STS_MASK_SIZE;
    i4_ret = a_icl_get(e_id, &ui4_info_status, &z_size);
    if (i4_ret != ICLR_OK)
    {
        DBG_ERROR (("[NAV][AUD]%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }
    ui4_info_status &= ~ICL_CHANNEL_RUNNING_STS_DISABLE_SCDB_AUDIO_UPDATE;
    i4_ret = a_icl_set(e_id, &ui4_info_status, z_size);
    if (i4_ret != ICLR_OK)
    {
        DBG_ERROR (("[NAV][AUD]%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }

    return;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_ai_pause_audio
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_ai_pause_audio(
                    BOOL                b_sync,
                    UINT32              ui4_sync_timeout
                    )
{
    if (b_sync)
    {
        return nav_request_context_switch_in_sync(_nav_ai_pause_audio,
                                                  NULL, NULL, NULL,
                                                  ui4_sync_timeout);
    }
    else
    {
        return nav_request_context_switch(_nav_ai_pause_audio,
                                          NULL, NULL, NULL);
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_ai_resume_audio
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_ai_resume_audio(
                    BOOL                b_sync,
                    UINT32              ui4_sync_timeout
                    )
{
    if (b_sync == TRUE)
    {
        return nav_request_context_switch_in_sync(
                                        _nav_ai_resume_audio,
                                        NULL,
                                        NULL,
                                        NULL,
                                        ui4_sync_timeout);
    }
    else
    {
        return nav_request_context_switch(
                                        _nav_ai_resume_audio,
                                        NULL,
                                        NULL,
                                        NULL);
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_audio_info_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_audio_info_register(
                    VOID
                    )
{
    NAV_COMP_EX_T t_comp;
    INT32         i4_ret;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_EX_T));

    t_comp.pf_pre_init       = _audio_info_pre_init;
    t_comp.pf_init           = _audio_info_init;
    t_comp.pf_deinit         = _audio_info_deinit;
    t_comp.pf_is_key_handler = _audio_info_is_key_handler;
    t_comp.pf_activate       = _audio_info_activate;
    t_comp.pf_inactivate     = NULL;
    t_comp.pf_hide           = _audio_info_hide;
    t_comp.pf_handle_msg     = _audio_info_handle_msg;

    i4_ret = nav_register_component_ex(NAV_COMP_ID_AUDIO_SEL, &t_comp, COMP_EXC_SET_AUDIO_SEL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"nav_register_component(NAV_COMP_ID_AUDIO_SEL) failed\r\n"));
        return i4_ret;
    }

    return NAVR_OK;
}

INT32 a_audio_info_set_next_audio()
{
    TV_WIN_ID_T      e_tv_win_id;
    INT32               i4_ret = NAVR_OK;
    SIZE_T              z_size;
    UINT32              ui4_info_status;
    UINT8               ui1_icl_mask;

    i4_ret = nav_get_focus_id(&e_tv_win_id);
    if(i4_ret != 0)
    {
        return NAVR_FAIL;
    }
    if((TRUE == _audio_info_is_svl_empty(e_tv_win_id)) ||
        (TRUE == nav_is_signal_loss(e_tv_win_id)) ||
        (LOCKED_STATUS_NONE != nav_get_locked_status(e_tv_win_id)))
    {
        return NAVR_FAIL;
    }



#ifdef APP_NAV_DISABLE_MTS_WHEN_VIDEO_HD_NOT_SUPPORT
    if((TRUE == nav_is_video_hd_not_support(e_tv_win_id)) || ( TRUE == nav_is_video_codec_not_support(e_tv_win_id)))
    {
        return NAVR_FAIL;
    }
#endif


    if(t_g_audio_info.at_grp[e_tv_win_id].b_is_digital)
    {
        i4_ret = nav_select_next_audio_stream(e_tv_win_id);

        if(NAVR_OK != i4_ret)
        {
            return NAVR_FAIL;
        }

        if (TV_WIN_ID_MAIN == e_tv_win_id)
        {
            z_size = ICL_RECID_MAIN_RUNNING_STS_MASK_SIZE;
            ui1_icl_mask = ICL_RECID_MAIN_RUNNING_STS_MASK;
        }
        else
        {
            z_size = ICL_RECID_SUB_RUNNING_STS_MASK_SIZE;
            ui1_icl_mask = ICL_RECID_SUB_RUNNING_STS_MASK;
        }

        a_icl_get(ICL_MAKE_ID(ICL_GRPID_RUNNING_SERVICE, ui1_icl_mask),
                           &ui4_info_status,
                           &z_size);


        ui4_info_status |= ICL_CHANNEL_RUNNING_STS_TV_AUDIO_LANG_MANUAL_SELECTION;

        a_icl_set(ICL_MAKE_ID(ICL_GRPID_RUNNING_SERVICE, ui1_icl_mask),
                           (VOID*)&ui4_info_status,
                           z_size);

        _audio_info_reset_sys_info(e_tv_win_id);
    }
    else
    {
        _AUDIO_INFO_SWITCH_ANALOG_AUDIO(&t_g_audio_info,
                                              _AUDIO_INFO_SAM_NEXT,
                                              e_tv_win_id,
                                              SCC_AUD_MTS_UNKNOWN,
                                              i4_ret);
        if(NAVR_OK != i4_ret)
        {
            return NAVR_FAIL;
        }
    }

    return  NAVR_OK;

}

INT32 a_audio_info_update_ATV_mts(SCC_AUD_MTS_T e_new_mts)
{
    return 0;
}

INT32 a_audio_info_set_audio_change_status(VOID)
{
    return  NAVR_OK;
}
