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
 * $RCSfile: cc_info_view_banner.c,v $
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
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_gl.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"

#include "nav/cc_info/a_cc_info.h"
#include "nav/cc_info/cc_info.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "wdk/widget/wdk_widget.h"
#include "res/revolt/revolt_settings_mlm.h"
#include "res/revolt/revolt_warnings_mlm.h"
#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "wizard_anim/a_wzd.h"
#include "wizard/a_wzd.h"

#include "nav/sys_info/a_sys_info.h"
#include "nav/banner2/a_banner.h"

/*banner state mgr*/
#include "nav/nav_bnr_state_mgr.h"
#include "res/menu2/menu_custom.h"
#include "res/nav/banner2/banner_rc.h"
#include "res/nav/nav_dbg.h"
#include "cc_info.h"
#include "res/msgconvert/msgconvert_custom.h"

#if !(defined(APP_DVBT_SUPPORT) || defined(APP_ISDB_SUPPORT)) && !defined(APP_SEPARATED_CC_INFO) && !defined(APP_NAV_CI_ONOFF)

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define CC_BANNER_UPDATE
#define CAST_CC

typedef enum __CC_INFO_SHOW_ITEM_E
{
    CC_INFO_SHOW_ITEM_OFF      = 0,
    CC_INFO_SHOW_ITEM_ON

} CC_INFO_SHOW_ITEM_E;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*view handler*/
static INT32 _nav_civn_init(HANDLE_T                    h_canvas,
                            INT32                       i4_frame_x_offset,
                            INT32                       i4_frame_y_offset,
                            APP_COLOR_TYPE_T            e_color_type,
                            VOID**                      ppv_view);

static INT32 _nav_civn_deinit(VOID*                     pv_view);

static INT32 _nav_civn_data_change(VOID*                    pv_view,
                                   NAV_CI_UI_INFO_FIELD_T   e_update_field,
                                   const NAV_CI_UI_INFO_T*  pt_update_data);

static BOOL _nav_civn_is_key_handler(VOID*              pv_view,
                                     UINT32             ui4_key_code);

//static INT32 _nav_civn_key_handler(VOID*                pv_view,
//                                   UINT32               ui4_key_code);
static INT32 _nav_civn_key_handler_ex(
                                    VOID*               pv_view,
                                    UINT32              ui4_key_code);

static INT32 _nav_civn_hide(VOID*                       pv_view);

static INT32 _nav_civn_update_detail(TV_WIN_ID_T           e_tv_win_id,
                                     const NAV_CI_UI_CC_DETAIL_T*   pt_cc_detail);

static INT32 _nav_civn_update_dscrptr(TV_WIN_ID_T           e_tv_win_id,
                                      NAV_CI_UI_INFO_STATUS_T       e_dscrptr_status);

/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_civ_get_default_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_civ_get_default_handler(NAV_CI_VIEW_HANDLER_T*     pt_view_handler)
{
    NAV_ASSERT(pt_view_handler);

    pt_view_handler->pf_init = _nav_civn_init;
    pt_view_handler->pf_deinit = _nav_civn_deinit;
    pt_view_handler->pf_data_change = _nav_civn_data_change;
    pt_view_handler->pf_is_key_handler = _nav_civn_is_key_handler;
    #ifdef CAST_CC
        pt_view_handler->pf_key_handler = _nav_civn_key_handler_ex;
    #else
        //pt_view_handler->pf_key_handler = _nav_civn_key_handler;
    #endif

    pt_view_handler->pf_hide = _nav_civn_hide;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_init(
    HANDLE_T                h_canvas,
    INT32                   i4_frame_x_offset,
    INT32                   i4_frame_y_offset,
    APP_COLOR_TYPE_T        e_color_type,
    VOID**                  ppv_view)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_deinit(
    VOID*                     pv_view)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_data_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_data_change(
    VOID*                          pv_view,
    NAV_CI_UI_INFO_FIELD_T         e_update_field,
    const NAV_CI_UI_INFO_T*        pt_update_data)
{
    INT32 i4_ret;
    TV_WIN_ID_T           e_tv_win_id;

    NAV_ASSERT(pt_update_data);

    i4_ret = nav_get_focus_id(& e_tv_win_id);
    if (i4_ret < NAVR_OK)
    {
        return NAVR_FAIL;
    }

    if(NAV_CI_IF_DSCRPTR & e_update_field)
    {
        _nav_civn_update_dscrptr(e_tv_win_id, pt_update_data->e_dscrptr_status);
    }

    if(NAV_CI_IF_DETAIL & e_update_field)
    {
        _nav_civn_update_detail(e_tv_win_id, &pt_update_data->t_cc_detail);
    }

    return NAVR_OK;
}

static BOOL _current_source_is_cast(VOID)
{
    ISL_REC_T               t_isl_rec   = {0};
    TV_WIN_ID_T             e_tv_win_id = TV_WIN_ID_MAIN;

    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));

    /*get current source*/
    nav_get_focus_id(&e_tv_win_id);
    nav_get_isl_rec(e_tv_win_id, &t_isl_rec);

    if ((INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type) && (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type))
    {
        CC_LOG(("automan debug!!!\n"));
        return TRUE;
    }

    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_civn_is_key_handler(
    VOID*                            pv_view,
    UINT32                           ui4_key_code)
{
    TV_WIN_ID_T                      e_focus;
    INT32                            i4_ret;

    if(BTN_CC != ui4_key_code)
    {
        return FALSE;
    }
    if(a_wzd_is_oobe_mode())
    {
        return FALSE;
    }
    menu_blank_oled_scrn_timer_refresh();
    if(menu_custom_is_blank_screen())
    {
        menu_custom_unblank_screen(ui4_key_code);
        return FALSE;
    }
    /*DTV00864213,3rd resume,CC key need work*/
    if (TRUE == _current_source_is_cast())
    {
        return TRUE;
    }

    i4_ret = nav_get_focus_id(&e_focus);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): nav_get_focus_id() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return FALSE;
    }

    return ((SVCTX_CAPABILITY_YES != nav_get_cc_capability(e_focus)) ? FALSE : TRUE);
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_cc_info_send_string_to_nav
 * Description
 *      Send WDK_TOAST_T to nav component of REVOLT INFO.
 * Input arguments
 *    pt_toast
 * Output arguments
 *    NULL
 * Returns
 *    NAVR_OK: The API routine is success.
 *---------------------------------------------------------------------------*/
INT32 a_cc_info_send_string_to_nav(WDK_TOAST_T *pt_toast)
{
    CC_LOG(("[CC INFO]Enter a_cc_info_send_string_to_nav\n\r"));

    WDK_TOAST_T* pt_toast_cpy = NULL;

    pt_toast_cpy = (WDK_TOAST_T*)c_mem_alloc(sizeof(WDK_TOAST_T));

    if (NULL == pt_toast_cpy)
    {
        CC_LOG(("NULL == pt_toast_cpy!!\n"));
        return -1;
    }

    c_memcpy((VOID*)pt_toast_cpy, (const VOID*)pt_toast, sizeof(WDK_TOAST_T));

    if (pt_toast->e_string_style == WDK_STRING_STRING)
    {
        CHAR     str[128]  = {0};
        UTF16_T* p_w2s_str = (UTF16_T*)pt_toast->style.style_4.w2s_str;
        INT32    len  = 0;

        c_uc_w2s_to_ps((const UTF16_T*)p_w2s_str, str, 127);
        CC_LOG(("[CC INFO]str: %s\n\r", str));

        len = (c_uc_w2s_strlen(p_w2s_str)+1)*2;

        CC_LOG(("[CC INFO]c_uc_w2s_strlen: %d\n\r", len));

        pt_toast_cpy->style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(len);

        c_memset((VOID*)pt_toast_cpy->style.style_4.w2s_str, 0, len);

        c_memcpy((VOID*)pt_toast_cpy->style.style_4.w2s_str, (const VOID*)pt_toast->style.style_4.w2s_str, len);
    }

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                              NAV_UI_MSG_REST_NOTIFICATION,
                              (VOID*) pt_toast_cpy);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _cc_info_view_toast_show
 * Description
 *      Reorganizate the string.
 * Input arguments
 *    i4_show_item
 * Output arguments
 *    NULL
 * Returns
 *    NAVR_OK: The API routine is success.
 *---------------------------------------------------------------------------*/
static INT32 _cc_info_view_toast_show(INT32 i4_show_item)
{

    WDK_TOAST_T t_toast           = {0};
    INT32       i4_ret            = NAVR_OK;

    c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_ID_ID;
    t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC;

    /* show CC OFF */
    if (CC_INFO_SHOW_ITEM_OFF == i4_show_item)
    {
        t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
    }
    else
    {
        t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
    }

    CC_LOG(("\n"));

    i4_ret = a_cc_info_send_string_to_nav(&t_toast);

    if (NAVR_OK != i4_ret)
    {
        CC_LOG(("_cc_info_view_show_string erro:%d\r\n", i4_ret ));
        return i4_ret;
    }

    return NAVR_OK;
}

static INT32 _nav_civox_play_tts(VOID)
{
    INT32 i4_ret = NAVR_OK;

#ifdef APP_TTS_SUPPORT
    UTF16_T                 w2s_str[64] = {0};
    NAV_CI_EXEC_COND_T      e_cond = NAV_CI_EC_OFF;

    nav_ci_get_exec_cond(&e_cond);

    c_uc_w2s_strcpy(w2s_str, MLM_SETTINGS_TEXT(MLM_SETTINGS_LANG_ENG,MLM_SETTINGS_KEY_CC));

    if (NAV_CI_EC_OFF == e_cond)
    {
        c_uc_w2s_strcat(w2s_str, MLM_NAV_TEXT(MLM_NAV_LANG_ENG,MLM_NAV_KEY_CC_TITLE_OFF));
    }
    else if (NAV_CI_EC_ON == e_cond)
    {
        c_uc_w2s_strcat(w2s_str, MLM_NAV_TEXT(MLM_NAV_LANG_ENG,MLM_NAV_KEY_CC_TITLE_ON));
    }

    i4_ret = a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_key_handler_ex
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_key_handler_ex(
    VOID*                          pv_view,
    UINT32                         ui4_key_code)
{
    INT32                   i4_ret = -1;
    NAV_CI_EXEC_COND_T      e_cond = NAV_CI_EC_OFF;

    do
    {
        //DTV02107372 
        //netflix don't need show cc status banner info
        if(msg_convert_custom_netflix_active() || msg_convert_custom_airplay_active() || msg_convert_custom_cobalt_alive())
        {
            return 0;
        }

        /*turn on/off cc*/
        i4_ret = nav_ci_get_exec_cond(&e_cond);
        if(i4_ret != NAVR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"nav_ci_get_exec_cond() failed. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }

        e_cond = (NAV_CI_EC_ON == e_cond) ? NAV_CI_EC_OFF : NAV_CI_EC_ON;
        a_cfg_set_cc_enabled(e_cond);
        nav_banner_set_cc_state(e_cond == NAV_CI_EC_ON ,TRUE);
        _nav_civox_play_tts();

        i4_ret = nav_ci_set_exec_cond(e_cond);
        if(i4_ret != NAVR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"nav_ci_set_exec_cond() failed. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }

        CC_LOG((" _cc_info_view_toast_show(). e_cond = %d\r\n", e_cond));

        i4_ret = _cc_info_view_toast_show(e_cond);
        if(i4_ret != NAVR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"_cc_info_view_toast_show() failed. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }
        nav_banner_set_cc_state(NAV_CI_EC_ON == e_cond ? TRUE : FALSE,TRUE);
        nav_ci_set_visible(NAV_CI_EC_ON == e_cond ? TRUE : FALSE);
        i4_ret = NAVR_NO_ACTION;

    } while(0);

    return i4_ret;              /*not to be the key owner*/
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_hide(
    VOID*                   pv_view)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_update_detail
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_update_detail(
    TV_WIN_ID_T           e_tv_win_id,
    const NAV_CI_UI_CC_DETAIL_T*     pt_cc_detail)
{
    INT32                               i4_ret;
    SI_SET_INFO_T                 t_set_info;

    SI_SET_INFO_ZERO(&t_set_info);

    do
    {
        if(NAV_CI_UI_IS_NOT_READY == pt_cc_detail->e_status ||
           NAV_CI_UI_IS_INIT_VALUE == pt_cc_detail->e_status  ||
           NAV_CI_UI_IS_WITHOUT == pt_cc_detail->e_status)
        {
            t_set_info.u.t_cc_info.e_rendering = SI_CC_RENDERING_TYPE_OFF;
            c_memset(t_set_info.u.t_cc_info.s639_lang,0,ISO_639_LANG_LEN);
            break;
        }
        /*update cc type*/
        if(pt_cc_detail->e_cc_type == NAV_CI_CC_TYPE_INIT_VALUE)
        {
            t_set_info.u.t_cc_info.e_rendering = SI_CC_RENDERING_TYPE_UNKNOWN;
        }
        else if(pt_cc_detail->e_cc_type == NAV_CI_CC_TYPE_NTSC_CC)
        {
            t_set_info.u.t_cc_info.e_rendering = (SI_CC_RENDERING_T)(pt_cc_detail->ui1_cc_id + SI_CC_RENDERING_TYPE_CC1 - 1);
        }
        else if(pt_cc_detail->e_cc_type == NAV_CI_CC_TYPE_NTSC_TEXT)
        {
            t_set_info.u.t_cc_info.e_rendering =(SI_CC_RENDERING_T)( pt_cc_detail->ui1_cc_id + SI_CC_RENDERING_TYPE_TEXT1 -1);
        }
        else if(pt_cc_detail->e_cc_type == NAV_CI_CC_TYPE_DIG)
        {
             t_set_info.u.t_cc_info.e_rendering = (SI_CC_RENDERING_T)(pt_cc_detail->ui1_cc_id + SI_CC_RENDERING_TYPE_SERVICE1 - 1);
        }
        else
        {
            return NAVR_FAIL;
        }

        /*update language*/
        if((NAV_CI_UI_IS_INIT_VALUE == pt_cc_detail->e_lang_status) ||
           (NAV_CI_UI_IS_NOT_READY == pt_cc_detail->e_lang_status) ||
           (NAV_CI_UI_IS_WITHOUT == pt_cc_detail->e_lang_status))
        {
            c_memset(t_set_info.u.t_cc_info.s639_lang,0,ISO_639_LANG_LEN);
            break;
        }
        c_memcpy(t_set_info.u.t_cc_info.s639_lang,pt_cc_detail->s639_lang,ISO_639_LANG_LEN);

    } while(0);

    t_set_info.e_category = SI_CATEGORY_CC_INFO;
    t_set_info.u.t_cc_info.ui4_info_mask = SI_CC_MASK_RENDERING |
                                           SI_CC_MASK_CRNT_CC_LANG;

    i4_ret = a_si_set_item_info_by_win_id(e_tv_win_id,&t_set_info);
    if (i4_ret < NAVR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_update_dscrptr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_update_dscrptr(
    TV_WIN_ID_T                          e_tv_win_id,
    NAV_CI_UI_INFO_STATUS_T     e_dscrptr_status)
{
    INT32                                i4_ret;
    SI_SET_INFO_T                 t_set_info;

    SI_SET_INFO_ZERO(&t_set_info);

    t_set_info.e_category = SI_CATEGORY_CC_INFO;
    t_set_info.u.t_cc_info.ui4_info_mask = SI_CC_MASK_AVAIL;

    if((NAV_CI_UI_IS_INIT_VALUE == e_dscrptr_status) ||
       (NAV_CI_UI_IS_NOT_READY == e_dscrptr_status) ||
       (NAV_CI_UI_IS_WITHOUT == e_dscrptr_status))
    {
        t_set_info.u.t_cc_info.e_avail = SI_CC_AVAIL_FALSE;
    }
    else
    {
        t_set_info.u.t_cc_info.e_avail = SI_CC_AVAIL_TRUE;
    }
    i4_ret = a_si_set_item_info_by_win_id(e_tv_win_id,&t_set_info);
    if (i4_ret < NAVR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

#else

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         TRUE
#define NAV_CIVN_CC_DETAIL_STR_LEN              ((SIZE_T)64)
#define NAV_CIVN_UI_ITEMS                       (NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION) |            \
                                                 NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION_ICON))
typedef enum __NAV_CIVN_INTL_FALG_T
{
    _NAV_CIVN_IFLG_CAPTION_ICON_INIT_READY      = 0x00000001,
    _NAV_CIVN_IFLG_CAPTION_MSG_INIT_READY       = 0x00000002
} _NAV_CIVN_INTL_FALG_T;

typedef struct __NAV_CIVN_T
{
    HANDLE_T            h_caption_icon;         /*from state manager, cannot be destroyed*/
    HANDLE_T            h_caption_msg;          /*from state manager, cannot be destroyed*/
    _NAV_CIVN_INTL_FALG_T   e_intl_flag;
} _NAV_CIVN_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static UTF16_T           w2s_g_space[]  = {0x0020, 0};
static UTF16_T*          pw2s_g_cc      = NULL;
static UTF16_T*          pw2s_g_text    = NULL;
static UTF16_T*          pw2s_g_service = NULL;
static UTF16_T*          pw2s_g_off     = NULL;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*view handler*/
static INT32 _nav_civn_init(HANDLE_T                    h_canvas,
                            INT32                       i4_frame_x_offset,
                            INT32                       i4_frame_y_offset,
                            APP_COLOR_TYPE_T            e_color_type,
                            VOID**                      ppv_view);

static INT32 _nav_civn_deinit(VOID*                     pv_view);

static INT32 _nav_civn_data_change(VOID*                    pv_view,
                                   NAV_CI_UI_INFO_FIELD_T   e_update_field,
                                   const NAV_CI_UI_INFO_T*  pt_update_data);

static BOOL _nav_civn_is_key_handler(VOID*              pv_view,
                                     UINT32             ui4_key_code);

static INT32 _nav_civn_key_handler(VOID*                pv_view,
                                   UINT32               ui4_key_code);

static INT32 _nav_civn_hide(VOID*                       pv_view);

/**/
static VOID _nav_civn_load_msgs(UINT8                  ui1_lang_id);

static INT32 _nav_civn_show(_NAV_CIVN_T*               pt_this);

static INT32 _nav_civn_update_detail(_NAV_CIVN_T*                   pt_this,
                                     const NAV_CI_UI_CC_DETAIL_T*   pt_cc_detail);

static INT32 _nav_civn_update_dscrptr(_NAV_CIVN_T*                  pt_this,
                                      NAV_CI_UI_INFO_STATUS_T       e_dscrptr_status);

static INT32 _nav_civn_get_detail(NAV_CI_CC_TYPE_T     e_cc_type,
                                  UINT8                ui1_cc_id,
                                  UTF16_T*             pw2s_string,
                                  SIZE_T               z_str_len);

static INT32 _nav_civn_get_off_detail(UTF16_T*         pw2s_string,
                                      SIZE_T           z_str_len);

static INT32 _nav_civn_frame_skin(_NAV_CIVN_T*         pt_this,
                                  APP_COLOR_TYPE_T     e_color_type);

/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_civ_get_default_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_civ_get_default_handler(NAV_CI_VIEW_HANDLER_T*     pt_view_handler)
{
    NAV_ASSERT(pt_view_handler);

    pt_view_handler->pf_init = _nav_civn_init;
    pt_view_handler->pf_deinit = _nav_civn_deinit;
    pt_view_handler->pf_data_change = _nav_civn_data_change;
    pt_view_handler->pf_is_key_handler = _nav_civn_is_key_handler;
    pt_view_handler->pf_key_handler = _nav_civn_key_handler;
    pt_view_handler->pf_hide = _nav_civn_hide;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_init(
    HANDLE_T                h_canvas,
    INT32                   i4_frame_x_offset,
    INT32                   i4_frame_y_offset,
    APP_COLOR_TYPE_T        e_color_type,
    VOID**                  ppv_view)
{
    _NAV_CIVN_T*            pt_this;
    INT32                   i4_ret;

    /*new instance*/
    pt_this = c_mem_alloc(sizeof(_NAV_CIVN_T));
    if(NULL == pt_this)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to alloc memory, size = %d\r\n", sizeof(_NAV_CIVN_T)));
        return NAVR_OUT_OF_MEM;
    }
    c_memset(pt_this, 0, sizeof(_NAV_CIVN_T));

    do
    {
        i4_ret = _nav_civn_frame_skin(pt_this,
                                      e_color_type);
        if(i4_ret != NAVR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to create the title icon widget of CC-Info-Banner. i4_ret = %d\r\n", i4_ret));
            break;
        }

        *ppv_view = pt_this;
        return NAVR_OK;

    } while(0);

    _nav_civn_deinit(pt_this);
    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_deinit(
    VOID*                     pv_view)
{
    if(pv_view)
    {
        c_mem_free(pv_view);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_data_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_data_change(
    VOID*                          pv_view,
    NAV_CI_UI_INFO_FIELD_T         e_update_field,
    const NAV_CI_UI_INFO_T*        pt_update_data)
{
    _NAV_CIVN_T*                   pt_this = (_NAV_CIVN_T*)pv_view;

    if(NULL == pv_view) /*before init*/
    {
        return NAVR_OK;
    }

    NAV_ASSERT(pt_update_data);

    if(NAV_CI_IF_STATE_ITEM & e_update_field)
    {
        pt_this->e_intl_flag &= ~(_NAV_CIVN_IFLG_CAPTION_ICON_INIT_READY |
            _NAV_CIVN_IFLG_CAPTION_MSG_INIT_READY);
    }

    if(NAV_CI_IF_GUI_LANG & e_update_field)
    {
        _nav_civn_load_msgs(pt_update_data->ui1_gui_lang_id);
    }

    if(NAV_CI_IF_DSCRPTR & e_update_field)
    {
        _nav_civn_update_dscrptr(pt_this, pt_update_data->e_dscrptr_status);
    }

    if(NAV_CI_IF_DETAIL & e_update_field)
    {
        _nav_civn_update_detail(pt_this, &pt_update_data->t_cc_detail);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_civn_is_key_handler(
    VOID*                            pv_view,
    UINT32                           ui4_key_code)
{
    TV_WIN_ID_T                      e_focus;
    INT32                            i4_ret;

    if(BTN_CC != ui4_key_code)
    {
        return FALSE;
    }

    i4_ret = nav_get_focus_id(&e_focus);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): nav_get_focus_id() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return FALSE;
    }

    return ((SVCTX_CAPABILITY_YES != nav_get_cc_capability(e_focus)) ? FALSE : TRUE);
}

#ifndef  CAST_CC
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_key_handler(
    VOID*                          pv_view,
    UINT32                         ui4_key_code)
{
    _NAV_CIVN_T*         pt_this = (_NAV_CIVN_T*)pv_view;
    INT32                i4_ret;
    BNR_ITEM_SET_T       t_orig_visible;

    CC_LOG(("\n"));
    /*get CAPTION-ICON and CAPTION's status*/
    i4_ret = nav_bnr_state_is_items_visible(NAV_CIVN_UI_ITEMS,
                                            &t_orig_visible);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to query CAPTION-ICON and CAPTION's status. i4_ret = %d\r\n", i4_ret));
        return i4_ret;
    }

    do
    {
        /*show cc info first if it's invisible*/
        if(NAV_CIVN_UI_ITEMS != t_orig_visible)
        {
            DBG_ERROR((_ERROR_HEADER"[CC]. Not to show CC = %d\r\n", __LINE__));

            //_nav_civn_show(pt_this);
            i4_ret = NAVR_NO_ACTION;
            break;
        }

        DBG_ERROR((_ERROR_HEADER"[CC]. CC is showing = %d\r\n", __LINE__));

        /*play next cc*/
        i4_ret = nav_ci_switch_cc(NAV_CI_SM_NEXT);
        if(i4_ret != NAVR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to play the next cc stream. i4_ret = %d\r\n", i4_ret));
            break;
        }

        i4_ret = NAVR_NO_ACTION;

    } while(0);

    /*restart timer*/
    nav_bnr_state_timer_op(NAV_BNR_STATE_TMOT_BY_STATE);

    return i4_ret;              /*not to be the key owner*/
}

#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_hide(
    VOID*                   pv_view)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_load_msgs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_civn_load_msgs(
    UINT8                       ui1_lang_id)
{
    pw2s_g_cc       = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_NTSC_CC);
    pw2s_g_text     = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_NTSC_TEXT);
    pw2s_g_service  = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_DTVCC_SERVICE);
    pw2s_g_off      = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_CC_OFF);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_show(
    _NAV_CIVN_T*            pt_this)
{
    /*make Caption-Icon visible*/
    nav_bnr_state_set_items_visible(NAV_CIVN_UI_ITEMS,
                                    NAV_BNR_STATE_OT_FINAL_FIRST,
                                    NAV_CTM_BS_CAPTION_ICON_PRI,
                                    NAV_BNR_STATE_TMOT_DO_NOTHING,
                                    NULL);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_update_detail
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_update_detail(
    _NAV_CIVN_T*                     pt_this,
    const NAV_CI_UI_CC_DETAIL_T*     pt_cc_detail)
{
    UTF16_T                          w2s_string[NAV_CIVN_CC_DETAIL_STR_LEN + 1] = {0};
    UTF16_T                          w2s_unknown_lang[ISO_639_LANG_LEN] = {0};
    UTF16_T*                         pw2s_cc_lang;
    SIZE_T                           z_len;
    INT32                            i4_ret;
    BNR_ITEM_SET_T                         t_orig_visible;
    UINT8                            ui1_type;

    do
    {
        if(NAV_CI_UI_IS_NOT_READY == pt_cc_detail->e_status || NAV_CI_UI_IS_INIT_VALUE == pt_cc_detail->e_status)
        {
            break;
        }

        if(NAV_CI_UI_IS_WITHOUT == pt_cc_detail->e_status)
        {
            i4_ret = _nav_civn_get_off_detail(w2s_string,
                                              NAV_CIVN_CC_DETAIL_STR_LEN + 1);
            if(NAVR_OK != i4_ret)
            {
                return i4_ret;
            }

            break;
        }

        /*update description*/
        i4_ret = _nav_civn_get_detail(pt_cc_detail->e_cc_type,
                                      pt_cc_detail->ui1_cc_id,
                                      w2s_string,
                                      NAV_CIVN_CC_DETAIL_STR_LEN + 1);
        if(NAVR_OK != i4_ret)
        {
            return i4_ret;
        }

        /*update language*/
        if((NAV_CI_UI_IS_INIT_VALUE == pt_cc_detail->e_lang_status) ||
           (NAV_CI_UI_IS_NOT_READY == pt_cc_detail->e_lang_status) ||
           (NAV_CI_UI_IS_WITHOUT == pt_cc_detail->e_lang_status))
        {
            break;
        }

        /*get language string*/
        pw2s_cc_lang = nav_get_display_lang(&pt_cc_detail->s639_lang);

        if(NULL == pw2s_cc_lang && 0 < c_strlen((const CHAR*)&pt_cc_detail->s639_lang))
        {
            i4_ret = c_uc_ps_to_w2s((const CHAR*)&pt_cc_detail->s639_lang,
                                    w2s_unknown_lang,
                                    ISO_639_LANG_LEN);
            if(UCR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"Fail to convert unknown CC lang(%s) from UTF8 to UFT16. i4_ret = %d\r\n", pt_cc_detail->s639_lang, i4_ret));
            }
            else
            {
                pw2s_cc_lang = w2s_unknown_lang;
            }
        }

        if(pw2s_cc_lang)
        {
            /*append space*/
            z_len = c_uc_w2s_strlen(w2s_string);    /*z_len is less than or equal to NAV_CIVN_CC_DETAIL_STR_LEN*/
            c_uc_w2s_strncat(w2s_string, w2s_g_space, NAV_CIVN_CC_DETAIL_STR_LEN - z_len);

            /*append language*/
            z_len = c_uc_w2s_strlen(w2s_string);    /*z_len is less than or equal to NAV_CIVN_CC_DETAIL_STR_LEN*/
            c_uc_w2s_strncat(w2s_string, pw2s_cc_lang, NAV_CIVN_CC_DETAIL_STR_LEN - z_len);
        }

    } while(0);

    /*get Caption current status*/
    i4_ret = nav_bnr_state_is_items_visible(NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION),
                                            &t_orig_visible);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to query CAPTION's status. i4_ret = %d\r\n", i4_ret));
        return i4_ret;
    }

    /*get Caption-msg widget*/
    if(!(_NAV_CIVN_IFLG_CAPTION_MSG_INIT_READY & pt_this->e_intl_flag))
    {
        i4_ret = nav_bnr_state_get_item_widget(NAV_BNR_STATE_II_CAPTION,
                                               &pt_this->h_caption_msg,
                                               &ui1_type);
        if(NAVR_OK != i4_ret)
        {
            pt_this->h_caption_msg = NULL_HANDLE;
            DBG_ERROR((_ERROR_HEADER"Fail to get CAPTION's handle. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }

        /*turn on ready-flag*/
        pt_this->e_intl_flag |= _NAV_CIVN_IFLG_CAPTION_MSG_INIT_READY;
    }

    if(NULL_HANDLE != pt_this->h_caption_msg)
    {
        /*update cc detail widget*/
        i4_ret = c_wgl_do_cmd(pt_this->h_caption_msg,
                              WGL_CMD_TEXT_SET_TEXT,
                              (VOID*)w2s_string,
                              (VOID*)NAV_CIVN_CC_DETAIL_STR_LEN);
        if(i4_ret != WGLR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to set the cc detail to detail widget of CC-Info-Banner. i4_ret = %d\r\n", i4_ret));
            return NAVR_FAIL;
        }

        /*repaint detail widget if visible*/
        if(t_orig_visible)
        {
            i4_ret = c_wgl_repaint(pt_this->h_caption_msg,
                                   NULL,
                                   IS_SYNC_REPAINT);
            if(i4_ret != WGLR_OK)
            {
                DBG_ERROR((_ERROR_HEADER"Fail to raise a repaint for the msg widget of CC-Info-Banner. i4_ret = %d\r\n", i4_ret));
                return NAVR_FAIL;
            }
        }
        else
        {
            /*make Caption-Icon visible*/
            /*nav_bnr_state_set_items_visible(NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION),
                                            NAV_BNR_STATE_OT_CRNT_FIRST,
                                            NAV_CTM_BS_CAPTION_ICON_PRI,
                                            NULL);*/
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_update_dscrptr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_update_dscrptr(
    _NAV_CIVN_T*                      pt_this,
    NAV_CI_UI_INFO_STATUS_T           e_dscrptr_status)
{
    BNR_ITEM_SET_T                          t_orig_visible;
    INT32                             i4_ret;
    UINT8                             ui1_type;
    BOOL                              b_show_icon;

    if((NAV_CI_UI_IS_INIT_VALUE == e_dscrptr_status) ||
       (NAV_CI_UI_IS_NOT_READY == e_dscrptr_status) ||
       (NAV_CI_UI_IS_WITHOUT == e_dscrptr_status))
    {
        b_show_icon = FALSE;
    }
    else
    {
        b_show_icon = TRUE;
    }

    /*get Caption-Icon current status*/
    i4_ret = nav_bnr_state_is_items_visible(NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION_ICON),
                                            &t_orig_visible);
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to query CAPTION-ICON's status. i4_ret = %d\r\n", i4_ret));
        return i4_ret;
    }

    /*get Caption-Icon*/
    if(!(_NAV_CIVN_IFLG_CAPTION_ICON_INIT_READY & pt_this->e_intl_flag))
    {
        i4_ret = nav_bnr_state_get_item_widget(NAV_BNR_STATE_II_CAPTION_ICON,
                                               &pt_this->h_caption_icon,
                                               &ui1_type);
        if(NAVR_OK != i4_ret)
        {
            pt_this->h_caption_icon = NULL_HANDLE;
            DBG_ERROR((_ERROR_HEADER"Fail to get CAPTION-ICON's handle. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }

        /*turn on ready-flag*/
        pt_this->e_intl_flag |= _NAV_CIVN_IFLG_CAPTION_ICON_INIT_READY;
    }

    if(NULL_HANDLE != pt_this->h_caption_icon)
    {
        /*show/hide cc icon*/
        i4_ret = c_wgl_set_visibility(pt_this->h_caption_icon,
                                      (b_show_icon) ? WGL_SW_NORMAL : WGL_SW_HIDE);
        if(i4_ret != WGLR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to change the visibility of the caption-icon widget of CC-Info-Banner. i4_ret = %d\r\n", i4_ret));
            return NAVR_FAIL;
        }

        if(t_orig_visible)
        {
            /*refresh Caption-Icon widget*/
            i4_ret = c_wgl_repaint(pt_this->h_caption_icon,
                                   NULL,
                                   IS_SYNC_REPAINT);
            if(i4_ret != WGLR_OK)
            {
                DBG_ERROR((_ERROR_HEADER"Fail to raise a repaint for CAPTION-ICON. i4_ret = %d\r\n", i4_ret));
                return NAVR_FAIL;
            }
        }
        else
        {
            /*make Caption-Icon visible*/
            /*nav_bnr_state_set_items_visible(NAV_BNR_STATE_IDX_TO_ID(NAV_BNR_STATE_II_CAPTION_ICON),
                                            NAV_BNR_STATE_OT_CRNT_FIRST,
                                            NAV_CTM_BS_CAPTION_ICON_PRI,
                                            NULL);*/
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_frame_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_frame_skin(
    _NAV_CIVN_T*                  pt_this,
    APP_COLOR_TYPE_T              e_color_type)
{
    INT32                         i4_ret;
    UINT8                         ui1_type;

    /*get Caption-Icon*/
    if(!(_NAV_CIVN_IFLG_CAPTION_ICON_INIT_READY & pt_this->e_intl_flag))
    {
        i4_ret = nav_bnr_state_get_item_widget(NAV_BNR_STATE_II_CAPTION_ICON,
                                               &pt_this->h_caption_icon,
                                               &ui1_type);
        if(NAVR_OK != i4_ret)
        {
            pt_this->h_caption_icon = NULL_HANDLE;
            DBG_ERROR((_ERROR_HEADER"Fail to get CAPTION-ICON's handle. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }

        /*turn on ready-flag*/
        pt_this->e_intl_flag |= _NAV_CIVN_IFLG_CAPTION_ICON_INIT_READY;
    }

    /*get Caption-msg widget*/
    if(!(_NAV_CIVN_IFLG_CAPTION_MSG_INIT_READY & pt_this->e_intl_flag))
    {
        i4_ret = nav_bnr_state_get_item_widget(NAV_BNR_STATE_II_CAPTION,
                                               &pt_this->h_caption_msg,
                                               &ui1_type);
        if(NAVR_OK != i4_ret)
        {
            pt_this->h_caption_msg = NULL_HANDLE;
            DBG_ERROR((_ERROR_HEADER"Fail to get CAPTION's handle. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }

        /*turn on ready-flag*/
        pt_this->e_intl_flag |= _NAV_CIVN_IFLG_CAPTION_MSG_INIT_READY;
    }

    /*Prog_info_banner_view takes care of Icon-Info's attribute now*/

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_get_detail
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
 static INT32 _nav_civn_get_detail(
     NAV_CI_CC_TYPE_T              e_cc_type,
     UINT8                         ui1_cc_id,
     UTF16_T*                      pw2s_string,
     SIZE_T                        z_str_len)

{
    UTF16_T* pw2s_cc_string = NULL;
    CHAR     s_cc_id[4]     = {0};
    UTF16_T  w2s_cc_id[4]   = {0};
    INT32    i4_ret;

    switch(e_cc_type)
    {
    case NAV_CI_CC_TYPE_NTSC_CC:
        pw2s_cc_string = pw2s_g_cc;
        break;

    case NAV_CI_CC_TYPE_NTSC_TEXT:
        pw2s_cc_string = pw2s_g_text;
        break;

    case NAV_CI_CC_TYPE_DIG:
        pw2s_cc_string = pw2s_g_service;
        break;

    case NAV_CI_CC_TYPE_INIT_VALUE:
    default:
        {
            if(z_str_len > 0)
            {
                pw2s_string[0] = (UTF16_T)'\0';
            }
        }
    }

    /*convert cc_id to string*/
    c_sprintf(s_cc_id, "%d", ui1_cc_id);
    i4_ret = c_uc_ps_to_w2s(s_cc_id, w2s_cc_id, 3);
    if (UCR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"Fail to convert cc-id to string. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    if(z_str_len >= (c_uc_w2s_strlen(pw2s_cc_string) + 3 + 1)) /* 3: cc_id length, 1: null-terminated character*/
    {
        c_uc_w2s_strcat(pw2s_string, pw2s_cc_string);
        c_uc_w2s_strcat(pw2s_string, w2s_cc_id);
    }
    else
    {
        DBG_ERROR((_ERROR_HEADER"Buffer size for cc info is too small.\r\n"));
        NAV_ASSERT(0);
    }

    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
 * Name
 *      _nav_civn_get_off_detail
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_civn_get_off_detail(
    UTF16_T*                          pw2s_string,
    SIZE_T                            z_str_len)
{
    if(z_str_len >= (c_uc_w2s_strlen(pw2s_g_off) + 1)) /* 1: null-terminated character*/
    {
        c_uc_w2s_strcat(pw2s_string, pw2s_g_off);
    }
    else
    {
        DBG_ERROR((_ERROR_HEADER"Buffer size for cc off is too small.\r\n"));
        NAV_ASSERT(0);
    }

    return NAVR_OK;
}

#endif /*!defined(APP_DVBT_SUPPORT) && !defined(APP_SEPARATED_CC_INFO) && !defined(APP_NAV_CI_ONOFF)*/
