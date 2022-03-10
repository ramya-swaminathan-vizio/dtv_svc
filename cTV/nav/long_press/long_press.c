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
 * $RCSfile: nav_fav_lst.c,v $
 * $Revision: #2 $
 * $Date: 2015/06/22 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/118 $
 * $SWAuthor: $
 * $MD5HEX: 74c34b81b9b0a7ed0de302079c3cacb3 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
//#ifdef APP_LONG_PRESS_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "app_client.h"

#include "am/a_am.h"
#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_ui.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "nav/twinkle_msg/a_scrn_svr.h"
#include "res/app_util/config/acfg_custom.h"
#include "app_util/config/_acfg.h"
#include "app_util/a_cfg.h"
#include "app_util/config/acfg_tv.h"
#include "mmp/a_mmp.h"
#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_img.h"
#include "res/revolt/revolt_warnings_mlm.h"
#include "res/revolt/revolt_settings_mlm.h"
#include "menu2/a_menu.h"
#include "menu2/menu.h"

#include "long_press.h"
#include "nav/input_src/a_input_src.h"

#ifdef APP_2K12_RETAIL_DEMO_MODE
#include "menu2/a_menu.h"
#include "wizard_anim/wzd.h"
#include "wizard_anim/a_wzd.h"
#endif

#include "msgconvert/msgconvert.h"
#include "res/app_util/model/model.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/msgconvert/msgconvert_custom.h"

#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/nav/banner2/banner_rc.h"
#include "nav/power/a_nav_power.h"
#include "wdk/widget/wdk_widget.h"

#include "nav/core/_nav_view.h"

#include "menu2/menu_common/menu_common.h"

#include "u_common.h"
#include "u_wgl_common.h"
#include "c_wgl.h"
#include "u_wgl.h"
#include "c_wgl_image.h"
#include "c_handle.h"
#include "c_os.h"
#include "c_dbg.h"
#include "u_cecm.h"
#include "stdlib.h"
#include "string.h"

#include "res/app_util/config/acfg_cust_misc.h"
#include "nav/retail_mode/nav_retail_mode.h"
#include "nav/link_mode/link_mode.h"
#include "bgm/a_bgm.h"
#include "bgm/mtk_comp/bgm_cast_c4tv/a_bgm_cast_c4tv.h"
#include "bgm/bgm_common.h"

#include "app_util/toast_widget/a_toast.h"

#include "res/nav/c4tv_apron/c4tv_apron_custom_view.h"
#include "nav/tuner_setup/tuner_setup.h"

#include "nav/cec2/nav_cec.h"
#include "c_cecm.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#include "registry/a_registry.h"
#endif

#include "rest/a_rest_api.h"
#include "rest/a_rest_event.h"
#include "mmp/a_mmp.h"
#include "res/nav/nav_dbg.h"

#include "nav/revolt_misc/revolt_misc.h"
#include "nav/revolt_misc/revolt_misc_view.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define  NAV_LONG_PRESS_AUTO_HIDE_TIMER_DURATION           10000
NAV_LONG_PRESS_STATUS_T LONG_PRESS_STATUS;
static NAV_LONG_PRESS_T t_g_nav_long_press;
#ifdef APP_C4TV_SUPPORT
#ifdef APP_RETAIL_MODE_SUPPORT
static ACFG_RETAIL_MODE_T   t_retail_mode = ACFG_RETAIL_MODE_HOME;
#endif
#endif
static BOOL b_long_press_tts_status = FALSE; /*Record TTS status before launch OOBE*/
static INT32 LINK_STATE = LINK_OFF;
static BOOL b1_skip_virtual_input = FALSE;
static BOOL b1_toast_display_state = FALSE;
ISL_REC_T  t_isl_rec;


VOID nav_long_press_reset_timer(NAV_LONG_PRESS_T* pt_this);
/*
   when link key second time or long input,
   softap up,long press vol+ & input not handle,
   only handle exit OOBE
*/
INT32 set_link_state(INT32 state,UINT8 input_src_idx,DEVICE_TYPE_T type){
    LINK_STATE = state;
    t_isl_rec.ui1_id = input_src_idx;
    t_isl_rec.t_avc_info.e_video_type = type;
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static BOOL _long_press_get_wzd_status(VOID);
static BOOL _long_press_set_tts_switch_status(BOOL b_enable);
static VOID _nav_long_press_p_effect_nfy_fct(VOID* pv_param1,VOID* pv_param2,VOID* pv_param3);

static INT32 _nav_long_press_deinit(VOID);
static INT32 _long_press_frame_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );

static INT32 _nav_send_toast_msg(WDK_TOAST_T* pt_toast)
{
    WDK_TOAST_T* pt_toast_cpy = NULL;

    if (NULL == pt_toast)
    {
        DBG_LOG_PRINT(("_nav_send_toast_msg NULL == pt_toast!!\n"));
        return NAVR_FAIL;
    }

    pt_toast_cpy = (WDK_TOAST_T*)c_mem_alloc(sizeof(WDK_TOAST_T));

    if (NULL == pt_toast_cpy)
    {
        DBG_LOG_PRINT(("_nav_send_toast_msg NULL == pt_toast_cpy!!\n"));
        return NAVR_FAIL;
    }

    c_memcpy((VOID*)pt_toast_cpy, (const VOID*)pt_toast, sizeof(WDK_TOAST_T));

    if (pt_toast->e_string_style == WDK_STRING_STRING)
    {
        CHAR     str[256]  = {0};
        UTF16_T* p_w2s_str = (UTF16_T*)pt_toast->style.style_4.w2s_str;
        INT32    len  = 0;

        c_uc_w2s_to_ps((const UTF16_T*)p_w2s_str, str, 255);
        DBG_INFO(("_nav_send_toast_msg str: %s\n\r", str));

        len = (c_uc_w2s_strlen(p_w2s_str)+1)*2;

        DBG_INFO(("_nav_send_toast_msg c_uc_w2s_strlen: %d\n\r", len));

        pt_toast_cpy->style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(len);

        c_memset((VOID*)pt_toast_cpy->style.style_4.w2s_str, 0, len);

        c_memcpy((VOID*)pt_toast_cpy->style.style_4.w2s_str, (const VOID*)pt_toast->style.style_4.w2s_str, len);
    }
    else if (pt_toast->e_string_style == WDK_STRING_TITLE_CONTENT)
    {
        INT32    len  = 0;

        len = (c_uc_w2s_strlen((UTF16_T*)pt_toast->style.style_5.w2s_title_str)+1)*2;

        DBG_INFO(("_nav_send_toast_msg c_uc_w2s_strlen: %d\n\r", len));
        pt_toast_cpy->style.style_5.w2s_title_str = (UTF16_T*)c_mem_alloc(len);
        c_memset((VOID*)pt_toast_cpy->style.style_5.w2s_title_str, 0, len);
        c_memcpy((VOID*)pt_toast_cpy->style.style_5.w2s_title_str, (const VOID*)pt_toast->style.style_5.w2s_title_str, len);


        len = (c_uc_w2s_strlen((UTF16_T*)pt_toast->style.style_5.w2s_content_str)+1)*2;
        pt_toast_cpy->style.style_5.w2s_content_str = (UTF16_T*)c_mem_alloc(len);
        c_memset((VOID*)pt_toast_cpy->style.style_5.w2s_content_str, 0, len);
        c_memcpy((VOID*)pt_toast_cpy->style.style_5.w2s_content_str, (const VOID*)pt_toast->style.style_5.w2s_content_str, len);
    }

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                              NAV_UI_MSG_REST_NOTIFICATION,
                              (VOID*) pt_toast_cpy);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_long_press_set_focus
 * Description
 *      set focus of long press focus.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_long_press_set_focus(VOID)
{
    //by sbx_11 0220 _1
    NAV_LONG_PRESS_T* pt_this = &t_g_nav_long_press;
    INT32 i4_ret;

    /* Let's focus on the frame */
    i4_ret = c_wgl_set_focus(pt_this->h_frame, WGL_NO_AUTO_REPAINT);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_frame, WGL_SW_RECURSIVE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_this->h_frame, NULL, TRUE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_long_press_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_long_press_stop_timer(
                    NAV_LONG_PRESS_T*                pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        DBG_LOG_PRINT(("[%s]++,line:%d\n",__FUNCTION__,__LINE__));
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop revolt_info::h_hide_timer failed!"));
    }

}

/*-----------------------------------------------------------------------------
 * Name: _cec_info_send_string_to_nav
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _cec_info_send_string_to_nav(WDK_TOAST_T *pt_toast)
{
    WDK_TOAST_T* pt_toast_cpy = NULL;

    pt_toast_cpy = (WDK_TOAST_T*)c_mem_alloc(sizeof(WDK_TOAST_T));

    if (NULL == pt_toast_cpy)
    {
        DBG_INFO(("NULL == pt_toast_cpy!!\n"));
        return -1;
    }

    c_memcpy((VOID*)pt_toast_cpy, (const VOID*)pt_toast, sizeof(WDK_TOAST_T));

    if (pt_toast->e_string_style == WDK_STRING_STRING)
    {
        CHAR     str[128]  = {0};
        UTF16_T* p_w2s_str = (UTF16_T*)pt_toast->style.style_4.w2s_str;
        INT32    len  = 0;

        c_uc_w2s_to_ps((const UTF16_T*)p_w2s_str, str, 127);

        len = (c_uc_w2s_strlen(p_w2s_str)+1)*2;

        pt_toast_cpy->style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(len);

        c_memset((VOID*)pt_toast_cpy->style.style_4.w2s_str, 0, len);

        c_memcpy((VOID*)pt_toast_cpy->style.style_4.w2s_str, (const VOID*)pt_toast->style.style_4.w2s_str, len);
    }

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                              NAV_UI_MSG_REST_NOTIFICATION,
                              (VOID*) pt_toast_cpy);
    return NAVR_OK;
}

extern UINT32       ui4_page_accessibility;
/*-----------------------------------------------------------------------------
 * Name:
 *      _long_press_cc_resume_accessibility_page_fct
 * Description:
 *      After long press CC key turn to Accessibility page.
 * Input arguments:
 *      pv_data
 *      z_data_size
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
VOID _long_press_cc_resume_accessibility_page_fct(VOID*        pv_data,
                                              SIZE_T       z_data_size)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = menu_nav_go(ui4_page_accessibility, NULL);
    NAV_LOG_ON_FAIL(i4_ret);

    return;
}

BOOL _long_press_get_wzd_status(VOID)
{
    UINT16  ui2_status    = 0;
    UINT8   ui1_state   = 0;
    /*get system state*/
    a_cfg_get_wzd_status(&ui2_status);
    ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    if (ui1_state != WZD_STATE_RESUME_C4TV)
    {
        DBG_INFO(("{%s %s() %d}. not oobe\n",__FILE__, __FUNCTION__, __LINE__));
        return FALSE;
    }
    else
    {
        DBG_INFO(("{%s %s() %d}. IN oobe\n",__FILE__, __FUNCTION__, __LINE__));
        return TRUE;
    }

}
BOOL _long_press_set_tts_switch_status(BOOL b_enable)
{
    /*to disable TTS*/
    DBG_INFO(("{%s() %d}. launch oobe ->(%s) TTS.\n", __FUNCTION__, __LINE__,(TRUE == b_enable)?"enable":"disable"));
    if (TRUE == b_enable)
    {
        a_cfg_set_tts_switch_status(1);
    }
    else if (FALSE == b_enable)
    {
        a_cfg_set_tts_switch_status(0);
    }

    a_cfg_update_tts_switch_status();

    return TRUE;
}

BOOL a_nav_long_press_set_tts_status(BOOL b_enable)
{
    UINT8  ui1_tts_switch = 0;
    a_cfg_get_tts_switch_status(&ui1_tts_switch);
    if((TRUE == b_long_press_tts_status) && (0 == ui1_tts_switch))
    {   /*the last TTS is ON, NOW is off*/
        DBG_INFO(("{%s() %d}. launch oobe ->(%s) TTS.\n", __FUNCTION__, __LINE__,(TRUE == b_enable)?"enable":"disable"));

    /*SPEC1.8, press CC key to enable TTS in oobe instead of long press CC key,
        finish or exit oobe,oobe will disable TTS*/
#if 0
        _long_press_set_tts_switch_status(b_long_press_tts_status);
#endif
    }
    return TRUE;
}

static VOID _long_cc_handler(VOID *pv_tag1, VOID *pv_tag2, VOID *pv_tag3)
{

    INT32               i4_ret;

    if (a_menu_is_resume())
    {
        i4_ret = menu_async_invoke(_long_press_cc_resume_accessibility_page_fct, NULL, 0, TRUE);
        NAV_LOG_ON_FAIL(i4_ret);
        menu_pm_refresh();
    }
    else
    {
        if(TRUE == _long_press_get_wzd_status())
        {
        /*SPEC1.8, press CC key to enable TTS in oobe instead of long press CC key*/
#if 0
            DBG_LOG_PRINT(("[input +++] {%s %s() %d}. oobe -> cc key enable TTS\n",__FILE__, __FUNCTION__, __LINE__));
            _nav_long_press_p_effect_nfy_fct(NULL,NULL,NULL);
#endif
        }
        else
        {
            i4_ret = a_menu_shortcut_link(MENU_SHORT_CUT_ACCESSIBILITY_PAGE);
            NAV_LOG_ON_FAIL(i4_ret);
        }
    }

#if 0
    INT32           i4_ret;
    UINT16          ui2_idx = 0;
    UINT16          ui2_tmp_idx = 0;
    ISO_639_LANG_T  s639_lang = {0};
    UTF16_T         w2s_str[64] = {0};
    WDK_TOAST_T     t_toast;
    UINT16          ui2_mlm_warning_key;
    UINT32          ui4_long_key = BTN_LONG_CC;

    i4_ret = a_cfg_get_aud_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("Get aud lang fail\n"));
        return;
    }
    ui2_tmp_idx = mlm_nav_s639_to_langidx(s639_lang);

    switch (ui2_tmp_idx)
    {
        case 0: /* English */
        case 1: /* French */
            ui2_idx = 2; /* change to Spanish */
            ui2_mlm_warning_key = MLM_MENU_KEY_STATE_TWO_ON;
            break;
        case 2: /* Spanish */
            ui2_idx = 0; /* to English/change to english */
            ui2_mlm_warning_key = MLM_MENU_KEY_STATE_TWO_OFF;
            break;
        default:
            ui2_idx = 0;
            ui2_mlm_warning_key = MLM_MENU_KEY_STATE_TWO_OFF;
            break;
    }

    mlm_nav_langidx_to_s639(ui2_idx, s639_lang);
    a_cfg_set_aud_lang(s639_lang);

    memset((VOID*)w2s_str, 0, sizeof(w2s_str));
    memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;
    t_toast.style.style_4.w2s_str = (VOID *)&w2s_str[0];
    c_uc_w2s_strcpy (w2s_str, MENU_TEXT(MLM_MENU_KEY_LONG_CC_MSG));
    c_uc_w2s_strcat(w2s_str, L" ");
    c_uc_w2s_strcat(w2s_str, MENU_TEXT(ui2_mlm_warning_key));

    if (a_menu_is_resume())
    {
        a_amb_dispatch_msg(MENU_NAME, MENU_MSG_LONG_KEY_PRESS, (VOID*)&ui4_long_key, sizeof(ui4_long_key));
        if (i4_ret != AEER_OK)
        {
            DBG_ERROR(("%s line: %d BTN_LONG_CC send message failed!\n", __FUNCTION__, __LINE__));
        }
    }

    _nav_send_toast_msg(&t_toast);

    return;
#endif
}

static VOID _nav_long_aspect_handler(VOID *pv_tag1, VOID *pv_tag2, VOID *pv_tag3)
{
    INT32       i4_ret = NAVR_OK;
    UINT8       ui1_idx = 0;
    WDK_TOAST_T t_toast;
    UTF16_T     w2s_str[256] = {0};
    UINT32      ui4_long_key = BTN_GFX_ZOOM;

    i4_ret = a_cfg_cust_get_zoom_status(&ui1_idx);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("Get zoom mode fail!\n"));
        return;
    }

    ui1_idx = (APP_CFG_CUST_ZOOM_MODE_OFF == ui1_idx) ? APP_CFG_CUST_ZOOM_MODE_ON : APP_CFG_CUST_ZOOM_MODE_OFF;
    a_cfg_cust_set_zoom_mode(ui1_idx);
    //if don not if 0, will show two message on screen
#if 0
    rest_event_notify("app/zoom/enabled", ui1_idx, "");
    menu_backbar_move_by_zoom_mode();
#ifdef VIZIO_FUSION_SUPPORT
    c_wgl_enable_zoom((ui1_idx == APP_CFG_CUST_ZOOM_MODE_ON) ? TRUE : FALSE);
#endif
    memset((VOID*)w2s_str, 0, sizeof(w2s_str));
    memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;
    t_toast.style.style_4.w2s_str = (VOID *)&w2s_str[0];

    if (ui1_idx == APP_CFG_CUST_ZOOM_MODE_OFF)
    {
        c_uc_w2s_strcpy(w2s_str, MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_ZOOM_MODE_OFF));
    }
    else
    {
        c_uc_w2s_strcpy(w2s_str, MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_ZOOM_MODE_ON));
    }

    if (a_menu_is_resume())
    {
        a_amb_dispatch_msg(MENU_NAME, MENU_MSG_LONG_KEY_PRESS, (VOID*)&ui4_long_key, sizeof(ui4_long_key));
        if (i4_ret != AEER_OK)
        {
            DBG_ERROR(("%s line: %d BTN_GFX_ZOOM send message failed!\n", __FUNCTION__, __LINE__));
        }
    }

    _nav_send_toast_msg(&t_toast);
#endif
    return;
}


static VOID _nav_long_press_p_effect_nfy_fct(VOID*        pv_param1,
                                        VOID*                   pv_param2,
                                        VOID*                   pv_param3)
{
    UINT8           ui1_tts_switch;
    UINT16          ui2_mlm_warning_key;
    UINT16          ui2_w2s_len;
    UTF16_T*        pt_w2s = NULL;
    WDK_TOAST_T*    pt_toast = NULL;
    UINT32          ui4_long_key = BTN_LONG_P_EFFECT;
    INT32           i4_ret = NAVR_OK;

    a_cfg_get_tts_switch_status(&ui1_tts_switch);
    if (ui1_tts_switch == 0)
    {
        a_cfg_set_tts_switch_status(1);
        ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_61;
        rest_event_notify("app/tts/enabled", 1, "");
        a_registry_set_tts_state(REG_TTS_STATE_ON);
    }
    else
    {
        a_cfg_set_tts_switch_status(0);
        ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_62;
        rest_event_notify("app/tts/enabled", 0, "");
        a_registry_set_tts_state(REG_TTS_STATE_OFF);
    }

    a_cfg_update_tts_switch_status();

    pt_toast = (WDK_TOAST_T*)c_mem_alloc(sizeof(WDK_TOAST_T));
    c_memset((VOID*)pt_toast, 0, sizeof(WDK_TOAST_T));
    pt_toast->e_toast_style  = WDK_STRING_TOAST;
    pt_toast->e_string_style = WDK_STRING_STRING;

    pt_w2s = MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), ui2_mlm_warning_key);

    ui2_w2s_len = (c_uc_w2s_strlen(pt_w2s)+1)*sizeof(UTF16_T);
    pt_toast->style.style_4.w2s_str = (UTF16_T *)c_mem_alloc(ui2_w2s_len);
    if (pt_toast->style.style_4.w2s_str != NULL)
    {
        c_memset((VOID*)pt_toast->style.style_4.w2s_str, 0x0, ui2_w2s_len);
        c_memcpy((VOID*)pt_toast->style.style_4.w2s_str, (const VOID *)pt_w2s, c_uc_w2s_strlen(pt_w2s)*sizeof(UTF16_T));
        nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                                  NAV_UI_MSG_REST_NOTIFICATION,
                                  (VOID*)pt_toast);
    }

#ifdef APP_TTS_SUPPORT
    a_app_tts_play(pt_w2s, c_uc_w2s_strlen(pt_w2s));
#endif

    if (a_menu_is_resume())
    {
        i4_ret = a_amb_dispatch_msg(MENU_NAME, MENU_MSG_LONG_KEY_PRESS, (VOID*)&ui4_long_key, sizeof(ui4_long_key));
        if (i4_ret != AMBR_OK)
        {
            DBG_ERROR(("%s line: %d BTN_LONG_P_EFFECT send message failed!\n", __FUNCTION__, __LINE__));
        }
    }

}

static INT32 _get_cast_src_isl_rec(ISL_REC_T*     pt_isl_cast_rec)
{
    UINT8       ui1_index = 0, ui1_src_num = 0;
    ISL_REC_T   t_isl_rec = {0};

    if (pt_isl_cast_rec == NULL) {
        return NAVR_INV_ARG;
    }

    a_isl_get_num_rec(&ui1_src_num);
    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
        a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);
        if (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
        {
            c_memcpy(pt_isl_cast_rec, &t_isl_rec, sizeof(ISL_REC_T));
            return NAVR_OK;
        }
    }

    return NAVR_NOT_EXIST;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_power_nfy_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_power_nfy_stop_timer(
                    NAV_LONG_PRESS_T*                pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_panel_power_timer) == FALSE) {
        DBG_LOG_PRINT(("[%s]++,line:%d\n",__FUNCTION__,__LINE__));
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_panel_power_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop revolt_info::h_panel_power_timer failed!"));
    }

}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_power_nfy_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_power_nfy_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
        NAV_LONG_PRESS_T* pt_this = &t_g_nav_long_press;

        nav_hide_component(NAV_COMP_ID_LONG_PRESS);

        _nav_power_nfy_stop_timer(pt_this);

        a_toast_hide(pt_this->h_toast_warning);

        /* Return control. */
        nav_return_activation(NAV_COMP_ID_LONG_PRESS);

        b1_toast_display_state = FALSE;

        if ((INT32)pv_tag == PRESS_KEYPAD_POWER_TO_INPUT)
        {
            nav_show_banner_input_source_msg_hdlr();
        }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_power_nfy_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_power_nfy_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
     nav_request_context_switch(_nav_power_nfy_timeout_to_hide, pv_tag, NULL, NULL);
}


BOOL get_one_button_toast_state(VOID)
{
    DBG_LOG_PRINT(("<WJ> %s b1_toast_display_state:%d \n",__FUNCTION__,b1_toast_display_state));

    return b1_toast_display_state;
}

VOID nav_long_press_power_nfy_timer(VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3)
{
    INT32             i4_ret;
    NAV_LONG_PRESS_T* pt_this  = &t_g_nav_long_press;
    TOAST_CUSTOMIZATION_DATA_T t_custom_data;
    UINT32 ui4_timeout         = (UINT32)pv_tag1;
    UINT32 ui4_str_type        = (UINT32)pv_tag2;

    a_toast_hide(pt_this->h_toast_warning);

    /*set focus*/
    nav_grab_activation(NAV_COMP_ID_LONG_PRESS);
    _nav_long_press_set_focus();
    nav_set_component_visible(NAV_COMP_ID_LONG_PRESS);


    _nav_power_nfy_stop_timer(pt_this);
    i4_ret = c_timer_start(
                    pt_this->h_panel_power_timer,
                    ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _nav_power_nfy_hide_timer_nfy,
                    (VOID*)ui4_str_type
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start revolt_info::h_hide_timer failed!"));
    }

    c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));

    DBG_LOG_PRINT(("{PWD} %s ui4_str_type:%d \n",__FUNCTION__,ui4_str_type));

    switch(ui4_str_type)
    {
        case PRESS_KEYPAD_POWER_2_SEC:
        {
            // To power off TV, release key now.
#if(NAV_INPUT_SRC_UI_VERTICAL)
            t_custom_data.u.t_msg_init.w2s_msg_str = WGL_PACK (MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_ISL_POWER_OFF_HELP_TEXT));
#else
            t_custom_data.u.t_msg_init.w2s_msg_str = WGL_PACK (MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_LONG_POWER_2S_TO_NOTIFY));
#endif
            break;
        }
        case PRESS_KEYPAD_POWER_7_SEC:
        {
            // To power off TV, release key now. Or to reset to factory settings, hold key for 5 more seconds.
#if(NAV_INPUT_SRC_UI_VERTICAL)
            t_custom_data.u.t_msg_init.w2s_msg_str = WGL_PACK (MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_LONG_POWER_10S_TO_NOTIFY));
#else
            t_custom_data.u.t_msg_init.w2s_msg_str = WGL_PACK (MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_LONG_POWER_7S_TO_NOTIFY));
#endif
            break;
        }
        case PRESS_KEYPAD_POWER_12_SEC:
        {
            // Memory is being cleared. The TV will reset shortly.
            t_custom_data.u.t_msg_init.w2s_msg_str = WGL_PACK (MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_LONG_POWER_RESET_TO_FACTORY_SETTINGS));
            break;
        }
        case PRESS_KEYPAD_POWER_TO_INPUT:
        {
            b1_toast_display_state = TRUE;

            // To power off TV, press and hold panel button for 2 seconds.
            t_custom_data.u.t_msg_init.w2s_msg_str = WGL_PACK (MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_LONG_POWER_POWER_OFF_TO_NOTIFY));
            break;
        }

        default:
            break;
    }
    a_toast_show(pt_this->h_toast_warning, &t_custom_data);

}

VOID vol_down_input_notify_factory_reset(VOID)
{
    DBG_LOG_PRINT(("automan debug!!!line;%d\n",__LINE__));

    /*set focus*/
    nav_grab_activation(NAV_COMP_ID_LONG_PRESS);
    _nav_long_press_set_focus();
    nav_set_component_visible(NAV_COMP_ID_LONG_PRESS);

    NAV_LONG_PRESS_T* pt_this = &t_g_nav_long_press;

    nav_long_press_reset_timer(pt_this);

    TOAST_CUSTOMIZATION_DATA_T t_custom_data;
    c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));
    t_custom_data.u.t_msg_init.w2s_msg_str = WGL_PACK (MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_36));

    a_toast_show(pt_this->h_toast_warning, &t_custom_data);

    /*set status*/
    LONG_PRESS_STATUS = NAV_LONG_PRESS_WARNING;
}

static VOID _nav_long_press_iom_handler (VOID*    pv_tag1,
                                         VOID*    pv_tag2,
                                         VOID*    pv_tag3)
{
    IOM_NFY_COND_T      e_nfy_cond   = (IOM_NFY_COND_T)(UINT32)pv_tag1;
    UINT32              ui4_evt_code = (UINT32)pv_tag2;
#ifdef APP_C4TV_SUPPORT
    UINT16      ui2_status  = 0;
    UINT8       ui1_state   = 0;
    UINT8       ui1_page_idx = 0;
    BGM_STATE_T e_state = BGM_STATE_UNKNOWN;
    UINT32      ui4_eco = 0;
#endif

    if (e_nfy_cond == IOM_NFY_COND_BTN_DOWN)
    {
        switch (ui4_evt_code)
        {
            case BTN_LONG_INPUT_VOL_DOWN:
                //"Reset so Defaults, from the back panel, press the Input for 10 seconds." is no need.
                //vol_down_input_notify_factory_reset();
                break;

            case BTN_LONG_INPUT_VOL_UP:
            {
            #ifdef APP_C4TV_SUPPORT
                /*get system state*/
                if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK)
                {
                    ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
                    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);
                }
                DBG_LOG_PRINT(("get oobe [state=%d ] [page= %d],LN:%d,\n\r",(int)ui1_state,(int)ui1_page_idx,__LINE__));
                if (WZD_STATE_RESUME_C4TV == ui1_state)
                {
                    /*in OOBE but not demomode*/
                    if (ui1_page_idx >= WZD_PAGE_INDEX_C4TV_START_OOBE && ui1_page_idx <= WZD_PAGE_INDEX_C4TV_END)
                    {
                        if (ui1_page_idx != WZD_PAGE_INDEX_C4TV_STORE_DEMO)
                        {
                           if (LINK_OFF == LINK_STATE)/*case:factory reset OOBE*/
                           {
                               /*change src to HDMI*/
                               wzd_chg_inp_src_to_hdmi();

                               /*exit OOBE and set state*/
                               a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
                               DBG_LOG_PRINT(("now END OOBE FUC:%s,LN:%d.\n",__FILE__,__LINE__));
                               a_wzd_stop_c4tv(a_nav_ipts_src_c4tv_apron_custom_nfy);
                               DBG_LOG_PRINT(("after OOBE EXIT FUC:%s,LN:%d.\n",__FILE__,__LINE__));
                               a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));

                               if (nav_is_channel_scan_active())
                               {
                                   a_tuner_setup_scab_stop();
                               }
                           }
                           else/*case link mode twice OOBE*/
                           {
                           #if 0
                               /*reload current source*/
                               DBG_LOG_PRINT(("now load previous source indx:%d FUC:%s,LN:%d.\r\n",t_isl_rec.ui1_id,__FILE__,__LINE__));
                               a_tv_set_input_src_id(TV_WIN_ID_MAIN,t_isl_rec.ui1_id);
                               a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
                                                   (VOID*)(UINT32)TV_WIN_ID_MAIN,
                                                   (VOID*)(UINT32)t_isl_rec.ui1_id);
                           #else
                               /*change src to HDMI*/                               // fix  DTV00827275
                               wzd_chg_inp_src_to_hdmi();
                           #endif

                               /*exit OOBE */
                               a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
                               //if (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)            // fix  DTV00827275
                               //{
                               //    a_nav_stop_ipts_src_c4tv_apron_custom_nfy_from_link(TRUE);
                               //}
                               a_wzd_stop_c4tv(a_nav_ipts_src_c4tv_apron_custom_nfy);
                               DBG_LOG_PRINT(("after exit softap FUC:%s,LN:%d.\r\n",__FILE__,__LINE__));
                               a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));

                               a_amb_resume_app(NAV_NAME);

                               /*notify link state*/
                               set_state(NAV_LINK_MODE_INITIAL,0,0);
                               nav_hide_component(NAV_COMP_ID_LINK);
                               DBG_LOG_PRINT(("reset link state to initial FUC:%s,LN:%d.\n",__FILE__,__LINE__));

                           }
                           /*If tv connected AMP,show AMP UI when to exit the oobe status :DTV00762743 */
                           if(LINK_OFF == LINK_STATE)
                           {
                                UTF16_T                 *pw2s_text = NULL;
                                WDK_TOAST_T             t_toast = {0};
                                UTF16_T                 w2s_tmp_str[512] = {0};
                                CECM_CTRL_T             t_ctrl;
                                CECM_DEV_T              t_devinfo;
                                INT32                   i4_ret = 0;

                                c_memset(&t_devinfo, 0, sizeof(CECM_DEV_T));

                                t_ctrl.b_sync = TRUE;
                                i4_ret = c_cecm_get_dev_info_by_la(nav_cec_get_mw_handle (),CECM_LOG_ADDR_AUD_SYS,&t_ctrl,&t_devinfo);

                                if(i4_ret != 0)
                                {
                                    DBG_LOG_PRINT(("%s,%d Routine fail= %d \r\n", __FUNCTION__, __LINE__,i4_ret ));
                                }

                                if(t_devinfo.b_dev_present != 0)
                                {
                                    pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_CEC_AUDIO_PLUG_PROMOTE_MSG);
                                    c_uc_w2s_strcpy(w2s_tmp_str, pw2s_text);

                                    c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));
                                    t_toast.e_toast_style  = WDK_WARNING_TOAST;
                                    t_toast.e_string_style = WDK_STRING_STRING;

                                    t_toast.style.style_4.w2s_str = (VOID*)w2s_tmp_str;

                                    _cec_info_send_string_to_nav(&t_toast);

                                }
                           }
                        }
                    }
                }
            #endif

                break;
            }

            case BTN_LONG_INPUT://INPUT_KEY test:0x1010039
                /*handle three case of input long press*/
            {
                ISL_REC_T       t_isl_rec = {0};
                INT32           i4_ret;
                HANDLE_T        h_main_svctx = NULL_HANDLE;

                /* DTV00869742 set soruce is cast ,when launch oobe in mmp status */
                MMP_MAIN_AP_STATUS_T    e_mmp_status = MMP_MAIN_AP_STATUS_DEINITED;
                /*adjust MMP is or not active in the backgroud*/
                e_mmp_status = a_mmp_get_ap_status();

            #ifdef APP_MENU_MMP_COEXIST
                if((MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == e_mmp_status) ||
                    (MMP_MAIN_AP_STATUS_RESUMED == e_mmp_status))
            #else
                if(MMP_MAIN_AP_STATUS_RESUMED == e_mmp_status)
            #endif
                {
                    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
                    i4_ret = _get_cast_src_isl_rec(&t_isl_rec);
                    if (NAVR_OK == i4_ret)
                    {
                        DBG_LOG_PRINT(("<long_press> change src_to_cast from mmp, %d\n\r", t_isl_rec.ui1_id));
                        a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
                    }
                }

                /*case 1*/
                if (NAV_LONG_PRESS_WARNING==LONG_PRESS_STATUS)//notification vol_down+input
                {
                    /*change link status*/
                    LONG_PRESS_STATUS = NAV_LONG_PRESS_RESET_FAC;

                    /*reset to factory after input*/
                    DBG_LOG_PRINT(("sbx reset to factory\n"));
                    NAV_LONG_PRESS_T* pt_this = &t_g_nav_long_press;
                    nav_long_press_reset_timer(pt_this);
                    TOAST_CUSTOMIZATION_DATA_T t_custom_data;
                    c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));
                    t_custom_data.u.t_msg_init.w2s_msg_str = WGL_PACK (MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_63));
                    a_toast_show(pt_this->h_toast_warning, &t_custom_data);

                    clear_memory();

                    break;
                }

            #ifdef APP_C4TV_SUPPORT
            #ifdef APP_RETAIL_MODE_SUPPORT
                /*case 2*/  /*OOBE  count down*/
                {
                    if( retail_mode_view_is_on() == TRUE )
                    {
                        i4_ret = nav_retail_mode_exit_launch_msg();
                        if(i4_ret != NAVR_OK)
                        {
                           NAV_LOG_ON_FAIL(i4_ret);
                           return;
                        }
                        break;
                    }
                }

                /*case 3*/  /*OOBE  demo mode */
                {
                    UINT16    ui2_status      = 0;
                    UINT8    ui1_state    = 0;
                    UINT8    ui1_page_idx  = 0;

                    /*get system state*/
                    i4_ret =  a_cfg_get_wzd_status(&ui2_status);
                    if(i4_ret != APP_CFGR_OK)
                    {
                       NAV_LOG_ON_FAIL(i4_ret);
                       return;
                    }

                    ui1_state     = WZD_UTIL_GET_STATUS_STATE(ui2_status);
                    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX    (ui2_status);

                    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

                    if ( ACFG_RETAIL_MODE_NORMAL == t_retail_mode )
                    {
                        DBG_LOG_PRINT(("sbx pause retail mode when in FUC:%s,LN:%d.\n",__FUNCTION__,__LINE__));
                    #if APP_RETAIL_DEMO_BACKUP_MMP_PQ
                          nav_recover_mmp_pq_value_in_exit();
                    #else
                        a_cfg_custom_set_pic_mode_vivid();
                    #endif
                        i4_ret = nav_retail_mode_exit();
                        if(i4_ret != NAVR_OK)
                        {
                           NAV_LOG_ON_FAIL(i4_ret);
                           return;
                        }
                        break;
                    }

                }

            #endif
                /*case 4*/ /* launch softap in normal mode */
                {
                    UINT16  ui2_status    = 0;
                    UINT8   ui1_state   = 0;

                    /*get system state*/
                    a_cfg_get_wzd_status(&ui2_status);
                    ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);

                    DBG_LOG_PRINT(("ui1_state:%d FUC:%s,LN:%d.\n",ui1_state,__FUNCTION__,__LINE__));

                    if (ui1_state != WZD_STATE_RESUME_C4TV)
                    {
                        //change to cast input
                        c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
                        i4_ret = _get_cast_src_isl_rec(&t_isl_rec);
                        if (NAVR_OK != i4_ret)
                        {
                            NAV_LOG_ON_FAIL(i4_ret);
                            return;
                        }
                        DBG_LOG_PRINT(("get CAST input_src idx:%d FUC:%s,LN:%d.\n",t_isl_rec.ui1_id,__FILE__,__LINE__));

                        nav_get_svctx_handle(TV_WIN_ID_MAIN, &h_main_svctx);
                        a_tv_stop_all_svc(h_main_svctx, NULL_HANDLE);
                        a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);

                        set_link_state(LINK_ON, t_isl_rec.ui1_id, t_isl_rec.t_avc_info.e_video_type);
                        set_state(NAV_LINK_MODE_SOFTAP, t_isl_rec.ui1_id, t_isl_rec.t_avc_info.e_video_type);
                        DBG_LOG_PRINT(("sbx launch softAp FUC:%s,LN:%d.\n",__FILE__,__LINE__));

                        /*long press INPUT key launch OOBE,AND disable TTS*/
                        {
                            UINT8  ui1_tts_switch = 0;
                            a_cfg_get_tts_switch_status(&ui1_tts_switch);
                            b_long_press_tts_status = ui1_tts_switch;
                            if (ui1_tts_switch == 1) //tts is on
                            {
                                _long_press_set_tts_switch_status(FALSE);//disable TTS
                            }
                        }

                        a_rest_launch_static_app();
                        a_wzd_resume_c4tv(WZD_STATE_RESUME_C4TV,WZD_PAGE_INDEX_C4TV_LINK_START);
                        break;
                    }
                }
            #endif
            }
                break;

            case BTN_WIDGET:
                /* BTN_WIDGET key launch cast source */
                 /*get system state*/
                /*if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK)
                {
                    ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
                }
                a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
                DBG_LOG_PRINT(("VIA key launch CAST state:%d,retail_mode:%d,LN:%d.\n",ui1_state,t_retail_mode,__LINE__));
                if (ui1_state != WZD_STATE_RESUME_C4TV && t_retail_mode != ACFG_RETAIL_MODE_NORMAL &&
                    !nav_is_channel_scan_active() && !a_bgm_is_quick_start_running())
                {
                    _launch_cast();
                }*/
                break;

            case BTN_LONG_CC:
            {
                /*if scanning channel,don`t show.*/
                if(nav_is_channel_scan_active())
                {

                }
                else
                {
                    DBG_INFO(("[Long Press]Received BTN_LONG_CC\n"));
                    nav_request_context_switch(_long_cc_handler, NULL, NULL, NULL);
                }
            }
                break;

            case BTN_LONG_P_EFFECT:
            {
                INT32                    i4_ret = 0;
                NAV_RETAIL_MODE_STATUS_T retm_status;
                i4_ret = a_nav_retail_mode_get_status(&retm_status);
                if (NAVR_OK == i4_ret && (NAV_RETAIL_MODE_RUNNING == retm_status))
                {
                    DBG_LOG_PRINT(("Do not launch talk back when overlay retail mode.\r\n"));
                    break;
                }

               if(nav_is_channel_scan_active())
               {
                   DBG_LOG_PRINT(("Scanning,Do not launch talk back.\r\n"));
                   break;
               }

               if(a_cfg_cust_is_tts_item_enable() == FALSE)
               {
                   DBG_LOG_PRINT(("Not Support TTS. Do not launch talk back.\r\n"));
                   break;
               }

                nav_request_context_switch(_nav_long_press_p_effect_nfy_fct,
                                           NULL,
                                           NULL,
                                           NULL);
            }
                break;

            case BTN_GFX_ZOOM:
            {
                ACFG_RETAIL_MODE_T       t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

                a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
                if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
                {
                    DBG_LOG_PRINT(("Do not launch zoom mode when overlay retail mode.\r\n"));
                    break;
                }
                if(nav_is_channel_scan_active())
                {
                    DBG_LOG_PRINT(("Scanning,Do not launch zoom mode.\r\n"));
                    break;
                }
                DBG_INFO(("[Long Press]Received BTN_GFX_ZOOM\n"));
                nav_request_context_switch(_nav_long_aspect_handler, NULL, NULL, NULL);
                break;
            }

            case BTN_LONG_MENU:
            {
                nav_long_press_menu_switch_status();
                /*long press menu to en/disable zoom mode*/
                a_nav_zoom_cust_long_press_menu(TRUE);
                break;
            }

            case BTN_LONG_INPUT_VOL_DOWN_10S:
            {
                NAV_LONG_PRESS_T* pt_this  = &t_g_nav_long_press;
                TOAST_CUSTOMIZATION_DATA_T t_custom_data;

                c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));

                DBG_LOG_PRINT((" [BTN_LONG_INPUT_VOL_DOWN_10S] [%s] \r\n", __FUNCTION__));

                a_toast_hide(pt_this->h_toast_warning);

                /*set focus*/
                nav_grab_activation(NAV_COMP_ID_LONG_PRESS);
                _nav_long_press_set_focus();
                nav_set_component_visible(NAV_COMP_ID_LONG_PRESS);

                b1_toast_display_state = TRUE;

                // Memory is being cleared. The TV will reset shortly.
                t_custom_data.u.t_msg_init.w2s_msg_str = WGL_PACK (MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_LONG_POWER_RESET_TO_FACTORY_SETTINGS));
                a_toast_show(pt_this->h_toast_warning, &t_custom_data);

                /* Notification for memory reset must display for 5 seconds. */
                c_thread_delay(KEY_TIME_5_SEC);

                a_cfg_cust_led_blinking_start(1);
                clear_memory();

                break;
            }

        #if 0
            case (BTN_CUSTOM_1 | KEY_SRC_FRONT_PANEL):
            {

                UINT16 ui2_status = APP_CFG_WZD_STATUS_INIT;
                UINT16 ui2_real_status = APP_CFG_WZD_STATUS_INIT;

                if (a_cfg_get_wzd_status (&ui2_status) == APP_CFGR_OK)
                {
                    ui2_real_status = WZD_UTIL_GET_STATUS_STATE( ui2_status );
                    DBG_LOG_PRINT(( "[REVOLT_MISC]%s,%d,ui2_status = %d\n", __FILE__,__LINE__,ui2_real_status ));

                    if (ui2_real_status == WZD_STATE_RESUME_C4TV_END)
                    {
                        nav_request_context_switch(revolt_misc_view_show, NULL, NULL, NULL);
                    }
                }

                break;
            }
        #endif

            default:
                break;
        }
    }
    else if (e_nfy_cond == IOM_NFY_COND_BTN_UP)
    {
        switch(ui4_evt_code)
        {
            case BTN_LONG_POWER://5 sec
                if(a_am_is_power_on() == FALSE) // do not work under QS standby
                {
                    break;
                }
              #ifdef MT5583_MODEL
                {
                    a_amb_power_on(FALSE);
                    a_scrn_svr_set_enable(TRUE);
                }

                break;
              #else
                if (is_one_button_model_platform() == TRUE)
                {
                    a_amb_power_on(FALSE);
                    a_scrn_svr_set_enable(TRUE);
                    break;
                }
                else
                {
                    /*get system state*/
                    if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK)
                    {
                        ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
                    }
                    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

                    if (ui1_state != WZD_STATE_RESUME_C4TV && t_retail_mode != ACFG_RETAIL_MODE_NORMAL)
                    {
                        a_cfg_custom_get_drv_eco_mode(&ui4_eco);
                        e_state = bgm_get_state();
                        if ((ICL_CUSTOM_POWER_MODE_QUICK_START == ui4_eco)
                            && (e_state == BGM_STATE_PRE_RUNNING || e_state == BGM_STATE_RUNNING))       /* must be this */
                        {
                            DBG_LOG_PRINT(("automan debug!!!LONG_POWER from active-standby mode\n"));
                            a_bgm_exit_active_standby_with_wakeup_reason(PCL_WAKE_UP_REASON_CUSTOM_2);
                        }
                        else
                        {
                            DBG_LOG_PRINT(("automan debug!!!power Reset FUC:%s,LN:%d.\n",__FILE__,__LINE__));
                            a_cfg_custom_service_reset(1,TRUE);
                        }
                    }
                    break;
                }
              #endif

            case BTN_LONG_POWER_12S:
                if(a_am_is_power_on()) // do not work under QS standby
                {
                    nav_long_press_power_nfy_timer((VOID*) 3000,(VOID*) PRESS_KEYPAD_POWER_12_SEC,NULL);

                    a_cfg_cust_led_blinking_start(1);
                    clear_memory();
                }
                break;

             default:
                break;
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name: _nav_long_press_iom_cb_func
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_long_press_iom_cb_func (VOID*             pv_nfy_tag,
                          IOM_NFY_COND_T    e_nfy_cond,
                          UINT32            ui4_evt_code,
                          UINT32            ui4_data)
{
    nav_request_context_switch(_nav_long_press_iom_handler,
                                   (VOID*) (UINT32)e_nfy_cond,
                                   (VOID*) ui4_evt_code,
                                   NULL);

}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_long_press_init
 * Description
 *      Initialize the retail mode compnent.
 * Input arguments
 *      NAV_CONTEXT_T*
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_long_press_init(NAV_CONTEXT_T* pt_ctx)
{
    /*Init timer and link status*/
    LONG_PRESS_STATUS = NAV_LONG_PRESS_INITIAL;
    IRRC_SETTING_T          t_irrc_setting;

    NAV_LONG_PRESS_T* pt_this = &t_g_nav_long_press;
    INT32           i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }
    if (c_handle_valid(pt_this->h_panel_power_timer) == TRUE) {
        c_timer_delete(pt_this->h_panel_power_timer);
    }


    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->h_update_ctrl_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;
    pt_this->b_is_view_init      = FALSE;
    pt_this->ui4_timeout  = NAV_LONG_PRESS_AUTO_HIDE_TIMER_DURATION;

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_timer_create(&(pt_this->h_panel_power_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    /*init wdk*/
    TOAST_INIT_PARAM_T t_toast_init;
    c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));
    t_toast_init.e_toast_style = TOAST_STYLE_MSG;
    t_toast_init.h_canvas = pt_ctx->t_gui_res.h_canvas;
    t_toast_init.t_custom_setting.u.t_msg_init.e_msg_type = TOAST_MSG_TYPE_WITH_WARNING_ICON;
    a_toast_create(&t_toast_init, &pt_this->h_toast_warning);

    /* IOM open */
    c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
    t_irrc_setting.ui8_evt_grp_mask         = (KEY_GROUP_TO_MASK(KEY_GROUP_DIGIT)\
                                              |KEY_GROUP_TO_MASK(KEY_GROUP_PRG_CTRL)\
                                              |KEY_GROUP_TO_MASK(KEY_GROUP_FCT_CTRL)\
                                              |KEY_GROUP_TO_MASK(KEY_GROUP_USER_DEF));
    t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = 50; /* No repeat key */
    t_irrc_setting.t_rpt_evt_itvl.ui2_other = 10; /* No repeat key */
    t_irrc_setting.b_notify_raw_data        = TRUE;
    t_irrc_setting.ui2_long_press_itvl = 500;//by sbx_11 0222 _1

    i4_ret = c_iom_open(
                    IOM_DEV_TYPE_IN_IRRC,
                    IOM_DEV_ID_ANY,
                    NULL,
                    &t_irrc_setting,
                    NULL,
                    _nav_long_press_iom_cb_func,
                    & pt_this->h_iom
                    );
    if (i4_ret != IOMR_OK)
    {
        DBG_LOG_PRINT(("wff iom_open fail file:%s,line:%d\n",__FILE__,__LINE__));
        return NAVR_FAIL;
    }

    /*create WGL for focus*/
    GL_RECT_T t_rect;
    SET_RECT_BY_SIZE(&t_rect, 0, 0, 0, 0);
    i4_ret = c_wgl_create_widget(
                    pt_ctx->t_gui_res.h_orig_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    _long_press_frame_nfy_fct,
                    0,
                    (VOID*)(WGL_STL_GL_NO_IMG_UI),
                    NULL,
                    &pt_this->h_frame
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return  NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_long_press_deinit
 * Description
 *      Denitialize the retail mode compnent.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_long_press_deinit(VOID)
{
    LONG_PRESS_STATUS = NAV_LONG_PRESS_INITIAL;
    NAV_LONG_PRESS_T* pt_this = &t_g_nav_long_press;
    c_iom_close (pt_this->h_iom);

    if (c_handle_valid(pt_this->h_update_ctrl_timer) == TRUE) {
        c_timer_delete(pt_this->h_update_ctrl_timer);
    }

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        DBG_LOG_PRINT(("[%s]++,line:%d timer is deleted \n",__FUNCTION__,__LINE__));
        c_timer_delete(pt_this->h_hide_timer);
    }

    if (c_handle_valid(pt_this->h_panel_power_timer) == TRUE) {
        c_timer_delete(pt_this->h_panel_power_timer);
    }

    a_toast_destroy(pt_this->h_toast_warning);
    // deinit the view
    if (pt_this->b_is_view_init == TRUE)
    {
        pt_this->b_is_view_init = FALSE;
    }

    pt_this->h_update_ctrl_timer = NULL_HANDLE;
    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;
    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_long_press_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_long_press_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    if (NAV_LONG_PRESS_WARNING==LONG_PRESS_STATUS){
        nav_hide_component(NAV_COMP_ID_LONG_PRESS);

        NAV_LONG_PRESS_T* pt_this = &t_g_nav_long_press;
        _nav_long_press_stop_timer(pt_this);

        a_toast_hide(pt_this->h_toast_warning);

        /*after 15s input no key ,reset status*/
        LONG_PRESS_STATUS = NAV_LONG_PRESS_INITIAL;

        /* Return control. */
        nav_return_activation(NAV_COMP_ID_LONG_PRESS);
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_long_press_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_long_press_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
     nav_request_context_switch(_nav_long_press_timeout_to_hide, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_long_press_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_long_press_reset_timer(
                    NAV_LONG_PRESS_T*                 pt_this
                    )
{
    INT32 i4_ret;

    if(pt_this == NULL)
    {
        pt_this = & t_g_nav_long_press;
    }

    _nav_long_press_stop_timer(pt_this);
    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    pt_this->ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _nav_long_press_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start revolt_info::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_long_press_is_key_handler
 * Description
 *      Ask for handle the key from navigator.
 * Input arguments
 *      NAV_CONTEX_T*
 *      UINT32          key code.
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static BOOL _nav_long_press_is_key_handler(
                    NAV_CONTEXT_T*  pt_ctx,
                    UINT32          ui4_key_code
                    )
{

    if ((BTN_LONG_INPUT_VOL_DOWN == ui4_key_code) || (BTN_LONG_INPUT_VOL_UP == ui4_key_code))
    {
        return TRUE;
    }

    return FALSE;
}

/*---------------------------------------------------------------------------
 * Name
 *      _long_press_frame_nfy_fct(
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _long_press_frame_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_long_press_activate
 * Description
 *      Activate retail mode
 * Input arguments
 *      NAV_CONTEXT_T*
 *      UINT32
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_long_press_activate(
                    NAV_CONTEXT_T*  pt_ctx,
                    UINT32          ui4_key_code)
{
    if (NAV_LONG_PRESS_INITIAL==LONG_PRESS_STATUS)
    {
         /*set focus*/
         DBG_LOG_PRINT(("sbx _nav_long_press_activate BEGIN\n"));
        _nav_long_press_set_focus();
        nav_set_component_visible(NAV_COMP_ID_LONG_PRESS);


        NAV_LONG_PRESS_T* pt_this = &t_g_nav_long_press;

        nav_long_press_reset_timer(pt_this);

# if 0
        TOAST_CUSTOMIZATION_DATA_T t_custom_data;
        c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));
        t_custom_data.u.t_msg_init.w2s_msg_str = WGL_PACK (MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_36));
        a_toast_show(pt_this->h_toast_warning, &t_custom_data);
# endif
        /*set status*/
        LONG_PRESS_STATUS = NAV_LONG_PRESS_WARNING;
        DBG_LOG_PRINT(("sbx _nav_long_press_activate END\n"));

    }
    return NAVR_OK;
}




/*-----------------------------------------------------------------------------
 * Name
 *      _nav_long_press_inactivate
 * Description
 *      Inactivate retail mode
 * Input arguments
 *      NAV_CONTEXT_T*
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_long_press_inactivate(NAV_CONTEXT_T*   pt_ctx)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_long_press_hide
 * Description
 *      Hide long press  mode component.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Succes
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_long_press_hide(VOID)
{
    if (NAV_LONG_PRESS_WARNING==LONG_PRESS_STATUS){
        DBG_LOG_PRINT(("+++_nav_long_press_hide begin+++\r\n"));

        NAV_LONG_PRESS_T* pt_this = &t_g_nav_long_press;
        _nav_long_press_stop_timer(pt_this);

        a_toast_hide(pt_this->h_toast_warning);

        /*reset status*/
        LONG_PRESS_STATUS = NAV_LONG_PRESS_INITIAL;

        /* Return control. */
        nav_return_activation(NAV_COMP_ID_LONG_PRESS);

        DBG_LOG_PRINT(("---_nav_long_press_hide end---\r\n"));
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_long_press_handle_msg
 * Description
 *      Handle message from navigator.
 * Input arguments
 *      NAV_CONTEX_T*
 *      NAV_UI_MSG_T*       message.
 *      VOID*               argument of message.
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *-----------------------------------------------------------------------------*/
static INT32 _nav_long_press_handle_msg(
                    NAV_CONTEXT_T*  pt_ctx,
                    NAV_UI_MSG_T*   pt_ui_msg,
                    VOID*           pv_arg1
                    )
{
    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_POWER_OFF:
        {
            /* No need to deal with since when power on, wzd will handle: set page to PAIR */
            break;
        }
        default:
            break;
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _launch_cast
 * Description
   when NAV_VIA key down ,cast source launch
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern INT32 _launch_cast(VOID)
{
    INP_SRC_TYPE_T e_src_type = INP_SRC_TYPE_VTRL;
    DEVICE_TYPE_T  e_video_type=DEV_VTRL_CAST;
    ISL_REC_T       t_isl_rec;
    INT32           i4_ret;
    UINT8           ui1_index = 0;
    UINT8           ui1_src_num = 0;
    UINT8           ui1_src_index = 0;
    CHAR       s_disp_name[SYS_NAME_LEN+1] = {0};
    UINT8      ui1_input_id = 0;
    TV_WIN_ID_T t_tv_win_id;
    TV_INPUT_SOURCE_PARAM_T  t_inp_src_param;

    a_isl_get_num_rec(&ui1_src_num);

    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);

        if (i4_ret != NAVR_OK)
        {
            return NAVR_FAIL;
        }

        if ((t_isl_rec.e_src_type == e_src_type) &&
                 (t_isl_rec.t_avc_info.e_video_type == e_video_type))
        {
            ui1_src_index = ui1_index;
            break;
        }
    }

    if (ui1_src_index < ui1_src_num)
    {
        a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
    }

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    DBG_ERROR(("Fail to a_cfg_av_get_disp_name. i4_ret = %d\r\n", i4_ret));
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    DBG_ERROR(("Fail to a_cfg_get_input_src. i4_ret = %d\r\n", i4_ret));
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    DBG_ERROR(("Fail to a_isl_get_rec_by_id. i4_ret = %d\r\n", i4_ret));
    c_memset (&t_inp_src_param, 0, sizeof(TV_INPUT_SOURCE_PARAM_T));
    t_inp_src_param.b_pause_msg_converter = TRUE;

    if (a_c4tv_apron_check_cast_state()
        && t_isl_rec.t_avc_info.e_video_type != DEV_VTRL_CAST)
    {
        NAV_RETAIL_MODE_STATUS_T retm_status;
        i4_ret = a_nav_retail_mode_get_status(&retm_status);
        if (NAVR_OK == i4_ret && (NAV_RETAIL_MODE_RUNNING == retm_status || NAV_RETAIL_MODE_PAUSE == retm_status))
        {
            DBG_LOG_PRINT(("\r[RETLMOD_DONNT_EXIT_CAST] %s LINE=%d\n", __FILE__, __LINE__));
        }
        else
        {
            /*Avoid nav_input start cast to cannot change to TV/AV source*/
            a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
            i4_ret = a_c4tv_apron_revoke_exit_cast(a_nav_ipts_src_c4tv_apron_custom_nfy);
            DBG_ERROR(("Fail to a_c4tv_apron_revoke_exit_cast. i4_ret = %d\r\n", i4_ret));
            return NAVR_OK;
        }
    }

    acfg_tv_get_focus_win(&t_tv_win_id);
    i4_ret = a_nav_change_input_src(t_tv_win_id, t_isl_rec.ui1_id) ? 0 : -1;
    DBG_ERROR(("Fail to a_nav_change_input_src. i4_ret = %d\r\n", i4_ret));
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_long_press_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_long_press_register()
{
    NAV_COMP_T      t_comp;
    INT32           i4_ret = NAVR_OK;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    t_comp.pf_init           = _nav_long_press_init;
    t_comp.pf_deinit         = _nav_long_press_deinit;
    t_comp.pf_is_key_handler = _nav_long_press_is_key_handler;
    t_comp.pf_activate       = _nav_long_press_activate;
    t_comp.pf_inactivate     = _nav_long_press_inactivate;
    t_comp.pf_hide           = _nav_long_press_hide;
    t_comp.pf_handle_msg     = _nav_long_press_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_LONG_PRESS,
                                    &t_comp,
                                    COMP_EXEC_SET_LONG_PRESS);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    return NAVR_OK;
}

#define One_Back_Panel_Button    1
#define Four_Back_Panel_Button   4
static INT8 one_button_model_platform = One_Back_Panel_Button;

#if 0
INT8 _Return_Back_Panel_Button(CHAR * ps_str)
{
    INT8 iret = One_Back_Panel_Button;

    DBG_LOG_PRINT(("[%s] s_model_name: [%s] \n", __FUNCTION__, ps_str));

    while (*ps_str++)
    {
        if (*ps_str == '-')
        {
            // 5-J   : Four Back Panel Button
            if ( (*(ps_str - 1) == '5') && (*(ps_str + 1) == 'J') )
            {
                iret = Four_Back_Panel_Button;
            }

            // 5x-J  : Four Back Panel Button
            else if ( (*(ps_str - 2) == '5') && (*(ps_str - 1) == 'x') && (*(ps_str + 1) == 'J') )
            {
                iret = Four_Back_Panel_Button;
            }

            // others: One  Back Panel Button
            else
            {
                iret = One_Back_Panel_Button;
            }
        }
    }

    one_button_model_platform = iret;
    DBG_LOG_PRINT (("[%s] %s Back Panel Button \n", __FUNCTION__, ((iret == One_Back_Panel_Button)?("One"):("Four"))));
    return iret;
}
#endif

void NAV_Check_Back_Panel_Button(void)
{
    INT8 iret = One_Back_Panel_Button;
    CHAR s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};
    EnuCusModelSeries CurModel = CUS_MODEL_UNKNOWN;

    a_cfg_custom_get_model_name(s_model_name);
    CurModel = a_cfg_cust_get_CurModelSeries();

    DBG_LOG_PRINT(("[%s] Model Name: [%s], Model Series: [%X] \n", __FUNCTION__, s_model_name, CurModel));

/*
2020 + 2021 v5 + 2021 P85QX-J01: Four Button Back Panel
2021 skus (except 2021 V5, 2021 P85QX-J01) : One Button Back Panel
*/
    switch (CurModel)
    {
        // 2020-5691 Series ...
        case CUS_MODEL_2020_91_V5: // 1, V**5-H**: V585-H1
        case CUS_MODEL_2020_91_M6: // 2, M**6-H*: M556-H1/M586x-H1
        case CUS_MODEL_2020_91_M7: // 3, M***7-H*: M55Q7-H1
        case CUS_MODEL_2020_91_M8: // 4, M***8-H*: M55Q8-H1

        // 2020-5695 Series ...
        case CUS_MODEL_2020_95_P9:    // 5, P***9-H**: P65Q9-H1
        case CUS_MODEL_2020_95_PX:    // 6, P***X-H*: P75QX-H1
        case CUS_MODEL_2020_95_OLED:  // 7, OLED**-H*: OLED55-H1/OLED65-H1

        // 2021-5691 Series ...
        case CUS_MODEL_2021_91_V5: // 10, V**5-J**: V435-J01
            iret = Four_Back_Panel_Button;
            break;

        // 2021-5583 Series ...
        case CUS_MODEL_2021_83_2K_D_HD:  // 8, D**h-J**: D32h-J05
        case CUS_MODEL_2021_83_2K_D_FHD: // 9, D**f*-J**: D24f4-J01/D24f-J09

        // 2021-5691 Series ...
        case CUS_MODEL_2021_91_V6: // 11, V**6*-J**: V556-J01/V556*-J01
        case CUS_MODEL_2021_91_M6: // 12, M***6-J**: M50Q6-J01
        case CUS_MODEL_2021_91_M7: // 13, M***7-J**: M50Q7-J01
        case CUS_MODEL_2021_91_M8: // 14, M***8-J**: none

        // 2021-5695 Series ...
        case CUS_MODEL_2021_95_P9: // 15, P***9-J**: P65Q9-J01
        //case CUS_MODEL_2021_95_PX: // 16, P***X-J**:
        case CUS_MODEL_2021_95_OLED: // 17, OLED**-J*:

        // 2021-5695L Series ...
        case CUS_MODEL_2021_95L_V6: // 18, V**C6-J**: V50C6-J09, V65C6-J09

        // 2022-5691 Series ...
        case CUS_MODEL_2022_91_M6:  // 19, M**Q6-K**:
        case CUS_MODEL_2022_91_V6:  // 20, V**Q6-K**:

        // 2022-5695L Series ...
        case CUS_MODEL_2022_95L_V6:  // 24, V**CM-K**:

        // 2022-5583 Series ...
        case CUS_MODEL_2022_83_2K_D:  // 21, D**F4-K**:
            iret = One_Back_Panel_Button;
            break;

        // 2022-5695S Series ...
        case CUS_MODEL_2022_95S_M9:  // 22, M**Q9-K**: M43Q9-K01, M65Q9-K03
        case CUS_MODEL_2022_95S_P:   // 23, P65QXM-K04
            iret = One_Back_Panel_Button;
            break;

        // 2021-5695 Series ... (except P85QX-J01 is Four Button Back Panel)
        case CUS_MODEL_2021_95_PX: // 16, P***X-J**:
        {
            if ( (s_model_name[1] == '8')
               &&(s_model_name[2] == '5')
               &&(s_model_name[3] == 'Q')
               )
            {
                iret = Four_Back_Panel_Button;
            }
            else
            {
                iret = One_Back_Panel_Button;
            }

            break;
        }

        case CUS_MODEL_UNKNOWN:
        default:
            break;
    }

    one_button_model_platform = iret;
    DBG_LOG_PRINT (("[%s] %s Back Panel Button \n", __FUNCTION__, ((iret == One_Back_Panel_Button)?("One"):("Four"))));
    return iret;
}

 /*-----------------------------------------------------------------------------
  * Name
  *      is_one_button_model_platform
  * Description
  * Input arguments
  * Output arguments
  * Returns
  *---------------------------------------------------------------------------*/
BOOL is_one_button_model_platform(VOID)
{
#if 1
    if ( one_button_model_platform == One_Back_Panel_Button ) {
        //DBG_LOG_PRINT (("[%s][%d] One Back Panel Button \n", __FUNCTION__, __LINE__));
        return TRUE;
    }
    else {
        //DBG_LOG_PRINT (("[%s][%d] Four Back Panel Button \n", __FUNCTION__, __LINE__));
        return FALSE;
    }
#else
    /* get model name */
    CHAR s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};
    CHAR * ps_str = NULL;
    a_cfg_custom_get_model_name(s_model_name);
    ps_str = s_model_name;

    while (*ps_str++)
    {
        if (*ps_str == '-')
        {
            if ( (*(ps_str - 1) != '5') && (*(ps_str + 1) == 'J') )
            {
                DBG_LOG_PRINT((" one button platform [%s] \n", s_model_name));
                return TRUE;
            }
        }
    }

    return FALSE;
#endif
}



/*-----------------------------------------------------------------------------
* Name
*      nav_get_skip_virtual_input_state
* Description
* Input arguments
* Output arguments
* Returns
*---------------------------------------------------------------------------*/
BOOL nav_get_skip_virtual_input_state(VOID)
{
    return b1_skip_virtual_input;
}

/*-----------------------------------------------------------------------------
* Name
*      nav_set_skip_virtual_input_state
* Description
* Input arguments
* Output arguments
* Returns
*---------------------------------------------------------------------------*/
VOID nav_set_skip_virtual_input_state(BOOL b1_state)
{
    b1_skip_virtual_input =b1_state;
}


//#endif /*APP_long_press_SUPPORT*/

