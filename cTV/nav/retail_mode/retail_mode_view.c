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
 * $RCSfile: nav_retail_view.c,v $
 * $Revision: #1 $
 * $Date: 2016/07/25 $
 * $Author: sin_stevenshan $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 164f107778d40dc636d1d0f28124de3c $
 *
 * Description:
 *      This file contains the view func used by the NAV application.
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "u_cli.h"
#include "c_dbg.h"
#include "u_common.h"
#include "u_btn_map.h"
#include "x_os.h"
#include "c_os.h"
#include "c_aee.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_wgl_image.h"

#include "am/a_am.h"
#include "menu2/a_menu.h"
#include "nav/nav_common.h"
#include "nav/c4tv_apron/c4tv_apron.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "wizard_anim/a_wzd.h"
#include "app_util/toast_widget/a_toast.h"
#include "nav/link_mode/link_mode.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "res/app_util/a_custom_log.h"
#include "res/app_util/model/model.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/c4tv_apron/c4tv_apron_custom.h"
#include "res/nav/c4tv_apron/c4tv_apron_custom_view.h"

#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/retail_mode/nav_retail_mode.h"
#include "nav/retail_mode/retail_mode_view.h"
#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif

#define RETAIL_MODE_VIEW_LOG_PREFIX "[RETAIL] "

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
static VOID _retail_mode_view_timer_cb_fct(
                    HANDLE_T        h_timer,
                    VOID*           pv_tag
                    );

static RETAIL_MODE_VIEW_T   t_g_retail_mode_view;

static WGL_HIMG_TPL_T       h_g_remote_input_icon = NULL_HANDLE;
static WGL_HIMG_TPL_T       h_g_remote_logo_icon = NULL_HANDLE;

static BOOL                 b_g_power_on_from_retail_mode = FALSE;

extern INT32 nav_zoom_mode_hide_img_title();

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
#if 0
static BOOL __retail_mode_is_on(VOID)
{
    ACFG_RETAIL_MODE_T      t_retail_mode   = ACFG_RETAIL_MODE_HOME;

#ifdef APP_RETAIL_MODE_SUPPORT
    INT32                   i4_ret          = NAVR_OK;
    i4_ret = a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (APP_CFGR_OK != i4_ret)
    {
        DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"acfg get_retail_mode_setting failed !!!!\n"));
        return FALSE;
    }
#endif

    if (t_retail_mode == ACFG_RETAIL_MODE_NORMAL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif
static VOID _c4tv_apron_cust_view_timer_hdlr_fct(
                    VOID*           pv_tag1,
                    VOID*           pv_tag2,
                    VOID*           pv_tag3
                    )
{
    RETAIL_MODE_VIEW_T*     pt_this         = &t_g_retail_mode_view;
    INT32                   i4_ret          = NAVR_OK;

    DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"%s, %d, e_timer_status: %d, ui4_timeout: %u, ui2_timer_count: %u\n",
                    __FUNCTION__, __LINE__,
                    (INT32)pt_this->e_timer_status,
                    pt_this->ui4_timeout,
                    pt_this->ui2_timer_count));

    if (RETAIL_MODE_VIEW_TIMER_NOTIFICATION != pt_this->e_timer_status)
    {
        return;
    }

    /* need update timer count  */
    if (pt_this->ui2_timer_count < (pt_this->ui4_timeout/1000)-1)
    {
        pt_this->ui2_timer_count++;
        retail_mode_view_show(NULL);
        return;
    }

    /* should NOT change input source if power on from retail mode */
    nav_retail_mode_skip_chg_src(b_g_power_on_from_retail_mode);

    i4_ret = c_timer_stop (pt_this->h_timer);
    if (i4_ret != OSR_OK)
    {
        DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"c_timer_stop failed !!!!\n"));
    }

    pt_this->e_timer_status = RETAIL_MODE_VIEW_TIMER_STOP;
    pt_this->ui2_timer_count = 0;

    retail_mode_view_hide();

    KK_LOG(KK_LOG_LVL_KEY, RETAIL_MODE_VIEW_LOG_PREFIX, "launch retail mode app.\n");

    a_nav_link_mode_set_mode(NAV_LINK_MODE_INITIAL);

    /* reset retail mode env */
    a_nav_retail_mode_reset_env();

    /* check oobe status*/
    if (a_wzd_is_oobe_mode() == TRUE)
    {
        a_c4tv_apron_revoke_exit_cast(NULL);
    }

    /* start playing */
    nav_retail_mode_go(NAV_RETAIL_MODE_RUNNING);

    return;
}

VOID clear_count_timer_status(VOID)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;
    INT32                   i4_ret  = NAVR_OK;

    i4_ret = c_timer_stop (pt_this->h_timer);
    if (i4_ret != OSR_OK)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] c_timer_stop failed !\n", __FUNCTION__, __LINE__));
    }

    pt_this->e_timer_status = RETAIL_MODE_VIEW_TIMER_STOP;
    pt_this->ui2_timer_count = 0;

    retail_mode_view_hide();
}


static VOID _retail_mode_view_timer_cb_fct(
                    HANDLE_T        h_timer,
                    VOID*           pv_tag
                    )
{
    nav_request_context_switch(_c4tv_apron_cust_view_timer_hdlr_fct, NULL, NULL, NULL);
}

static VOID __wzd_status_nfy_hdlr_fct(
                    VOID*           pv_tag1,
                    VOID*           pv_tag2,
                    VOID*           pv_tag3
                    )
{
    INT32                   i4_ret          = NAVR_OK;
    UINT16                  ui2_status      = 0;
    UINT8                   ui1_state       = 0;
    UINT8                   ui1_page_idx    = 0;

    i4_ret = a_cfg_get_wzd_status(&ui2_status);
    if (APP_CFGR_OK != i4_ret)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] a_cfg_get_wzd_status failed !\n", __FUNCTION__, __LINE__));
        return;
    }

    ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);

    KK_LOG(KK_LOG_LVL_API, RETAIL_MODE_VIEW_LOG_PREFIX, "oobe [state= %u] [page= %u].\n",
                    ui1_state, ui1_page_idx);

    /*Reuse this acfg notification handler for Bootup assistant */
    if ((WZD_STATE_RESUME_C4TV_END & ui1_state) != 0
        || WZD_PAGE_INDEX_C4TV_ALL_SET == ui1_page_idx
        || WZD_PAGE_INDEX_C4TV_END == ui1_page_idx
        || WZD_PAGE_INDEX_C4TV_LINK_START == ui1_page_idx)
    {
        DBG_INFO(("%s() clean bootup assistant flag\n", __FUNCTION__));
        a_cfg_custom_set_bootup_assistant_flag(ACFG_BOOTUP_ASSISTANT_NONE);
    }

    return;
}

static VOID __wzd_status_nfy_func(UINT16 ui2_nfy_id, VOID* pv_tag, UINT16 ui2_id)
{
    RETAIL_MODE_VIEW_T*     pt_this         = &t_g_retail_mode_view;

    if (pt_this->ui2_cfg_nfy_id != ui2_nfy_id)
    {
        return;
    }

    if (CFG_MAKE_ID(APP_CFG_GRPID_WZD, APP_CFG_RECID_WZD_STATUS) != ui2_id)
    {
        return;
    }

    /*post a message to itself*/
    nav_request_context_switch(__wzd_status_nfy_hdlr_fct, NULL, NULL, NULL);

    return;
}

INT32 retail_mode_view_init(HANDLE_T h_canvas)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;
    INT32                   i4_ret  = NAVR_OK;

    if (pt_this->b_is_init)
    {
        DBG_WARN((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] retail_mode_view_init already \n", __FUNCTION__, __LINE__));
        return NAVR_OK;
    }

    DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] start \n", __FUNCTION__, __LINE__));

    pt_this->b_is_on        = FALSE;
    pt_this->h_timer        = NULL_HANDLE;
    pt_this->ui4_timeout    = RETAIL_MODE_POWNER_ON_NOTIFICATION_TIMEOUT;
    pt_this->ui2_timer_count= 0;
    pt_this->e_timer_status = RETAIL_MODE_VIEW_TIMER_STOP;
    pt_this->h_canvas       = h_canvas;
    pt_this->h_toast_view   = NULL_HANDLE;
    pt_this->ui2_cfg_nfy_id = APP_CFG_NOTIFY_NULL_ID;

    i4_ret = nav_img_create_remote_input_icon(&h_g_remote_input_icon);
    if (NAVR_OK != i4_ret)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] nav_img_create remote_input_icon failed \n", __FUNCTION__, __LINE__));
        h_g_remote_input_icon = NULL_HANDLE;
        return NAVR_FAIL;
    }

    /* create toast osd */
    if (pt_this->h_toast_view == NULL_HANDLE)
    {
        TOAST_INIT_PARAM_T  t_toast_init;
        c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));

        t_toast_init.e_toast_style  = TOAST_STYLE_MSG_WITH_TITLE_CONTENT;
        t_toast_init.h_canvas       = pt_this->h_canvas;
        t_toast_init.t_custom_setting.u.t_msg_with_title_init.e_msg_type = TOAST_MSG_TYPE_WITH_TIMER_COUNTDOWN;
        i4_ret = a_toast_create(&t_toast_init, &(pt_this->h_toast_view));
        if (TOASTR_OK != i4_ret)
        {
            DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] a_toast_create failed \n", __FUNCTION__, __LINE__));
            return NAVR_FAIL;
        }
    }

    /* create timer */
    i4_ret = c_timer_create(&(pt_this->h_timer));
    if (i4_ret != OSR_OK)
    {
        return NAVR_FAIL;
    }

    /* register notify */
    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_WZD,
                              NULL,
                              __wzd_status_nfy_func,
                              &(pt_this->ui2_cfg_nfy_id));
    if (APP_CFGR_OK != i4_ret)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] a_cfg_notify_reg failed \n", __FUNCTION__, __LINE__));

        pt_this->ui2_cfg_nfy_id = APP_CFG_NOTIFY_NULL_ID;
        return NAVR_FAIL;
    }

    pt_this->b_is_init  = TRUE;

    DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] end \n", __FUNCTION__, __LINE__));

    return NAVR_OK;
}

INT32 retail_mode_view_deinit(VOID)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;
    INT32                   i4_ret  = NAVR_OK;

    if (!pt_this->b_is_init)
    {
        DBG_WARN((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] retail_mode_view_deinit already \n", __FUNCTION__, __LINE__));
        return NAVR_OK;
    }

    DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] start \n", __FUNCTION__, __LINE__));

    if (pt_this->b_is_on)
    {
        retail_mode_view_hide();
        pt_this->b_is_on = FALSE;
    }

    if (c_handle_valid(pt_this->h_timer) == TRUE)
    {
        c_timer_delete(pt_this->h_timer);
    }
    pt_this->h_timer = NULL_HANDLE;

    if (pt_this->ui2_cfg_nfy_id != APP_CFG_NOTIFY_NULL_ID)
    {
        a_cfg_notify_unreg(pt_this->ui2_cfg_nfy_id);
        pt_this->ui2_cfg_nfy_id = APP_CFG_NOTIFY_NULL_ID;
    }

    /* destroy toast osd */
    if (pt_this->h_toast_view != NULL_HANDLE)
    {
        i4_ret = a_toast_destroy(pt_this->h_toast_view);
        if (TOASTR_OK != i4_ret)
        {
            DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] a_toast_destroy failed \n", __FUNCTION__, __LINE__));
        }
        pt_this->h_toast_view = NULL_HANDLE;
    }

    if (h_g_remote_input_icon != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy(h_g_remote_input_icon);
        h_g_remote_input_icon = NULL_HANDLE;
    }

    pt_this->b_is_init  = FALSE;

    return NAVR_OK;
}

INT32 retail_mode_view_show(UTF16_T*  pw2s_string)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;
    INT32                   i4_ret  = NAVR_OK;
    UTF16_T*                pw2s_msg = pw2s_string;
    UTF16_T*                pw2s_title = NULL;

    CHAR                    s_timer_string[5] = {0};
    UTF16_T                 w2s_timer_string[5+1] = {0};

    //hide zoom on title msg
    nav_zoom_mode_hide_img_title();

    c_sprintf(s_timer_string, "%d", pt_this->ui4_timeout/1000 - pt_this->ui2_timer_count);
    c_uc_ps_to_w2s(s_timer_string, w2s_timer_string, 5);

    DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] start (%s) \n", __FUNCTION__, __LINE__, w2s_timer_string));

    /* create toast osd */
    if (pt_this->h_toast_view == NULL_HANDLE)
    {
        TOAST_INIT_PARAM_T  t_toast_init;
        c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));

        t_toast_init.e_toast_style  = TOAST_STYLE_MSG_WITH_TITLE_CONTENT;
        t_toast_init.h_canvas       = pt_this->h_canvas;
        t_toast_init.t_custom_setting.u.t_msg_with_title_init.e_msg_type = TOAST_MSG_TYPE_WITH_TIMER_COUNTDOWN;
        t_toast_init.t_custom_setting.u.t_msg_with_title_init.ui1_title_align = WGL_AS_CENTER_CENTER;
        t_toast_init.t_custom_setting.u.t_msg_with_title_init.ui1_text_align = WGL_HTS_JUSTIF_CENTER;

        i4_ret = a_toast_create(&t_toast_init, &(pt_this->h_toast_view));
        if (TOASTR_OK != i4_ret)
        {
            DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] a_toast_create failed \n", __FUNCTION__, __LINE__));
            return NAVR_FAIL;
        }
    }

    TOAST_CUSTOMIZATION_DATA_T  t_custom_data;
    c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));

    pw2s_title = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_RETAIL_MODE_LAUNCH_TITLE);
    if (pw2s_msg == NULL)
    {
        pw2s_msg = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_RETAIL_MODE_LAUNCH_MSG);
    }

    t_custom_data.u.t_msg_with_title_init.w2s_title_str = (VOID*)pw2s_title;
    t_custom_data.u.t_msg_with_title_init.w2s_msg_str = (VOID*)pw2s_msg;
    t_custom_data.u.t_msg_with_title_init.h_insert_img = h_g_remote_input_icon;
    t_custom_data.u.t_msg_with_title_init.w2s_timer_str = (VOID*)w2s_timer_string;
//    t_custom_data.u.t_msg_with_title_init.ui1_text_align = WGL_HTS_JUSTIF_CENTER;
    t_custom_data.u.t_msg_with_title_init.ui1_text_align =  WGL_HTS_JUSTIF_RIGHT; // rex test

    if (c_wgl_float(pt_this->h_toast_view, TRUE, FALSE) != WGLR_OK) {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] fail \r\n", __FUNCTION__, __LINE__));
    }

  #ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_BANNER));
  #endif

    i4_ret = a_toast_show(pt_this->h_toast_view, &t_custom_data);
    if (TOASTR_OK != i4_ret)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] a_toast_show failed \n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }

    if (FALSE == pt_this->b_is_on)
    {
        pt_this->b_is_on = TRUE;

    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_tts_str[256] = {0};

      #if 0
        c_uc_w2s_strcpy(w2s_tts_str, pw2s_title);
        c_uc_w2s_strcat(w2s_tts_str, (UTF16_T*)L".");
        c_uc_w2s_strcat(w2s_tts_str, pw2s_msg);
      #else
        c_uc_w2s_strcpy(w2s_tts_str, (UTF16_T*)L"Store DEMO is launching. \
                        To cancel, press and hold the INPUT button on \
                        the back panel or press the input button on \
                        the basic remote control.");
      #endif

        a_app_tts_play(w2s_tts_str, c_uc_w2s_strlen(w2s_tts_str));
    #endif
    }

    DBG_LOG_PRINT((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] End \n", __FUNCTION__, __LINE__));
    return NAVR_OK;
}

INT32 retail_mode_view_hide(VOID)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;
    INT32                   i4_ret  = NAVR_OK;

    DBG_LOG_PRINT((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] start \n", __FUNCTION__, __LINE__));

    b_g_power_on_from_retail_mode = FALSE;

    if (!pt_this->b_is_on)
    {
        DBG_WARN((RETAIL_MODE_VIEW_LOG_PREFIX" retail_mode_view_hide already \n"));
        return NAVR_OK;
    }

#ifdef APP_TTS_SUPPORT
    a_app_tts_stop(APP_TTS_STOP_FORCE);
#endif

    if (c_wgl_float(pt_this->h_toast_view, FALSE, FALSE) != WGLR_OK) {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] fail \r\n", __FUNCTION__, __LINE__));
    }
    i4_ret = a_toast_hide(pt_this->h_toast_view);
    if (TOASTR_OK != i4_ret)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] a_toast_hide failed \n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }

    pt_this->b_is_on = FALSE;

    return NAVR_OK;
}

BOOL retail_mode_view_show_fift_minute(VOID)
{
    RETAIL_MODE_VIEW_T* pt_this = &t_g_retail_mode_view;

    return pt_this->b_is_pair_page;
}

INT32 retail_mode_view_timer_start(
                        RETAIL_MODE_VIEW_TIMER_T    e_timer_status,
                        UINT32                      ui4_timeout)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;
    INT32                   i4_ret  = NAVR_OK;

    if (e_timer_status > RETAIL_MODE_VIEW_TIMER_NOTIFICATION)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] retail_mode_timer_start failed \n", __FUNCTION__, __LINE__));
        return NAVR_INV_ARG;
    }

    DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] e_timer_status: %d, ui4_timeout: %u\n",
                    __FUNCTION__, __LINE__,
                    (INT32)e_timer_status, ui4_timeout));

    if (pt_this->e_timer_status != RETAIL_MODE_VIEW_TIMER_STOP)
    {
        c_timer_stop (pt_this->h_timer);
    }

    pt_this->e_timer_status = e_timer_status;
    pt_this->ui4_timeout    = ui4_timeout;
    pt_this->ui2_timer_count = 0;

    if (RETAIL_MODE_VIEW_TIMER_DEVICE_PAIR == e_timer_status)
    {
        i4_ret = c_timer_start (pt_this->h_timer,
                            pt_this->ui4_timeout,
                            X_TIMER_FLAG_ONCE,
                            _retail_mode_view_timer_cb_fct,
                            NULL);
    }
    else
    {
        i4_ret = c_timer_start (pt_this->h_timer,
                            1000,
                            X_TIMER_FLAG_REPEAT,
                            _retail_mode_view_timer_cb_fct,
                            NULL);
    }

    if (i4_ret != OSR_OK)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] c_timer_start failed \n", __FUNCTION__, __LINE__));
        pt_this->e_timer_status = RETAIL_MODE_VIEW_TIMER_STOP;
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

INT32 retail_mode_view_timer_stop(VOID)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;
    INT32                   i4_ret  = NAVR_OK;

    DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] e_timer_status: %d, ui4_timeout: %u \n",
                    __FUNCTION__, __LINE__,
                    (INT32)pt_this->e_timer_status, pt_this->ui4_timeout));

    if (pt_this->e_timer_status == RETAIL_MODE_VIEW_TIMER_STOP)
    {
        return NAVR_OK;
    }

    i4_ret = c_timer_stop (pt_this->h_timer);
    if (i4_ret != OSR_OK)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] c_timer_stop failed !\n", __FUNCTION__, __LINE__));
    }

    pt_this->e_timer_status = RETAIL_MODE_VIEW_TIMER_STOP;
    pt_this->ui2_timer_count = 0;

    return NAVR_OK;
}

INT32 retail_mode_view_timer_restart(VOID)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;
    INT32                   i4_ret  = NAVR_OK;

    DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] e_timer_status: %d, ui4_timeout: %u\n",
                    __FUNCTION__, __LINE__,
                    (INT32)pt_this->e_timer_status, pt_this->ui4_timeout));

    if (pt_this->e_timer_status == RETAIL_MODE_VIEW_TIMER_STOP)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_timer_stop(pt_this->h_timer);
    if (i4_ret != OSR_OK)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] c_timer_stop failed !\n", __FUNCTION__, __LINE__));
    }

    pt_this->ui2_timer_count = 0;

    if (RETAIL_MODE_VIEW_TIMER_DEVICE_PAIR == pt_this->e_timer_status)
    {
        i4_ret = c_timer_start (pt_this->h_timer,
                            pt_this->ui4_timeout,
                            X_TIMER_FLAG_ONCE,
                            _retail_mode_view_timer_cb_fct,
                            NULL);
    }
    else
    {
        i4_ret = c_timer_start (pt_this->h_timer,
                            1000,
                            X_TIMER_FLAG_REPEAT,
                            _retail_mode_view_timer_cb_fct,
                            NULL);
    }

    if (i4_ret != OSR_OK)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] c_timer_start failed \n", __FUNCTION__, __LINE__));
        pt_this->e_timer_status = RETAIL_MODE_VIEW_TIMER_STOP;
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

BOOL retail_mode_view_is_on(VOID)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;

    return pt_this->b_is_on;
}

INT32 retail_mode_view_logo_init(HANDLE_T h_canvas)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;
    INT32                   i4_ret  = NAVR_OK;
    GL_RECT_T               t_rect;
    UINT32                  width;
    UINT32                  height;

    DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] start \n", __FUNCTION__, __LINE__));

    pt_this->h_canvas       = h_canvas;
    pt_this->h_toast_view   = NULL_HANDLE;

    i4_ret = nav_img_create_retail_mode_vizio_logo(&h_g_remote_logo_icon);
    if (NAVR_OK != i4_ret)
    {
        DBG_ERROR((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] nav_img_create remote_input_icon failed \n", __FUNCTION__, __LINE__));
        h_g_remote_logo_icon = NULL_HANDLE;
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_get_canvas_size(
                    h_canvas,
                    &width,
                    &height);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Create logo frame */
    SET_RECT_BY_SIZE (& t_rect,
                      LOGO_FRAME_X,
                      LOGO_FRAME_Y,
                      width,
                      height);

    i4_ret = c_wgl_create_widget (h_canvas,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  NULL,
                                  DEFAULT_BK_ALPHA,
                                  (VOID*) WGL_STL_GL_NO_BK,
                                  NULL,
                                  & pt_this->h_frame_logo);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Create logo icon */
    SET_RECT_BY_SIZE(&t_rect,
                     (width-LOGO_FRAME_W)/2,
                     (height-LOGO_FRAME_H)/2,
                     LOGO_FRAME_W,
                     LOGO_FRAME_H);
    i4_ret = c_wgl_create_widget (pt_this->h_frame_logo,
                                  HT_WGL_WIDGET_ICON,
                                  WGL_CONTENT_ICON_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  NULL,
                                  DEFAULT_BK_ALPHA,
                                  (VOID*) WGL_STL_GL_NO_BK,
                                  NULL,
                                  & pt_this->h_icon_logo);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    WGL_IMG_INFO_T              t_img_info;

    /* make icon visible */
    i4_ret = c_wgl_set_visibility(pt_this->h_icon_logo,
                                  WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* set icon  buffer */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_remote_logo_icon;//h_g_pop_warning_bk
    t_img_info.u_img_data.t_standard.t_disable   = h_g_remote_logo_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_remote_logo_icon;

    i4_ret = c_wgl_do_cmd(
                    pt_this->h_icon_logo,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_FG),
                    WGL_PACK(&t_img_info));
    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(
                    pt_this->h_icon_logo,
                    WGL_CMD_ICON_SET_ALIGN,
                    (VOID*)WGL_AS_LEFT_TOP,
                    NULL);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    pt_this->b_is_logo_on = FALSE;

    return NAVR_OK;
}

INT32 retail_mode_view_logo_show(VOID)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;
    INT32                   i4_ret  = NAVR_OK;
    BOOL                    b_retail_mode_view_logo_is_show;

    b_retail_mode_view_logo_is_show = retail_mode_view_logo_is_show();

    DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] retail_mode_view_logo_is_show: %d \n",
                    __FUNCTION__, __LINE__, b_retail_mode_view_logo_is_show));

    if(TRUE == b_retail_mode_view_logo_is_show)
    {
        return NAVR_OK;
    }

    i4_ret = c_wgl_set_visibility(
                    pt_this->h_frame_logo,
                    WGL_SW_RECURSIVE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    c_wgl_float(pt_this->h_frame_logo, TRUE, FALSE);

    i4_ret = c_wgl_repaint(
                    pt_this->h_frame_logo,
                    NULL,
                    IS_SYNC_REPAINT
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    pt_this->b_is_logo_on = TRUE;

    return NAVR_OK;
}


INT32 retail_mode_view_logo_hide(VOID)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;
    INT32                   i4_ret  = NAVR_OK;
    BOOL                    b_retail_mode_view_logo_is_show;

    b_retail_mode_view_logo_is_show = retail_mode_view_logo_is_show();

    DBG_INFO((RETAIL_MODE_VIEW_LOG_PREFIX"[%s][%d] retail_mode_view_logo_is_show: %d \n",
                    __FUNCTION__, __LINE__, b_retail_mode_view_logo_is_show));

    if (FALSE == retail_mode_view_logo_is_show())
    {
        return NAVR_OK;
    }

    i4_ret = c_wgl_set_visibility(
                    pt_this->h_frame_logo,
                    WGL_SW_HIDE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(
                    pt_this->h_frame_logo,
                    NULL,
                    IS_SYNC_REPAINT
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    pt_this->b_is_logo_on = FALSE;

    return NAVR_OK;
}

BOOL retail_mode_view_logo_is_show(VOID)
{
    RETAIL_MODE_VIEW_T*     pt_this = &t_g_retail_mode_view;

    return pt_this->b_is_logo_on;
}

