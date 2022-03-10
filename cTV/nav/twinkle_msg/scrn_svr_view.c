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
 * $RCSfile: scrn_svr_view.c,v $
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
#include "u_wgl_common.h"

#include "c_handle.h"
#include "c_gl.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_os.h"

#include "wdk/a_wdk.h"
#include "app_util/toast_widget/a_toast.h"
#include "res/nav/nav_img.h"
#include "nav/twinkle_msg/scrn_svr.h"
#include "res/app_util/config/a_cfg_custom.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "app_util/a_cec.h"
#include "nav/cec2/a_nav_cec.h"
#include "rest/metrics/bootsc_metrics.h"

#include "nav/banner2/a_banner.h"
#include "nav/banner2/banner.h"
#include "res/nav/nav_dbg.h"
#include "res/menu2/menu_custom.h"

#ifndef SCRN_SVR_DELAY_TO_ACTIVATE_NO_SIGNAL_SWITCH_VIEW
#define SCRN_SVR_DELAY_TO_ACTIVATE_NO_SIGNAL_SWITCH_VIEW (5*1000)
#endif

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef enum
{
    SCRN_SVR_TOAST_SELECTION_NONE = 0,
    SCRN_SVR_TOAST_SELECTION_CANCEL,
    SCRN_SVR_TOAST_SELECTION_RETURN_HOME
}SCRN_SVR_TOAST_SELECTION_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static WDK_OSD_TOAST_T      t_g_wdk_scrn_svr_middle = {0};
static WDK_OSD_TOAST_T      t_g_wdk_scrn_svr_av_status = {0};

static WGL_HIMG_TPL_T       h_g_remote_link_icon = NULL_HANDLE;

static WGL_HIMG_TPL_T       h_g_input_icon = NULL_HANDLE;

static TOAST_STYLE_T        e_g_toast_style = TOAST_STYLE_MAX_NUM;

static BOOL b_tuner_setup_view_showing  =   FALSE;

static BOOL                 b_oled = FALSE;

static SCRN_SVR_VIEW_T*     t_g_pt_view = NULL;

static SCRN_SVR_TOAST_SELECTION_T g_scrn_svr_toast_selection          = SCRN_SVR_TOAST_SELECTION_NONE;

static HANDLE_T h_no_signal_timer;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _change_no_signal_toast(
                    VOID*           pv_unused1,
                    VOID*           pv_unused2,
                    VOID*           pv_unused3
                    )
{
    SCRN_SVR_VIEW_T*    pt_view = t_g_pt_view;
    INT32               i4_ret  = NAVR_OK;

    //Hide no_signal_1
    i4_ret = scrn_svr_view_hide(pt_view, TOAST_STYLE_NO_SIGNAL_1);
    NAV_LOG_ON_FAIL(i4_ret);

    //... and show no_signal_2
    if(nav_is_component_visible(NAV_COMP_ID_SCREEN_SAVER))
    {

        i4_ret = scrn_svr_view_show(pt_view, nav_get_crnt_err_msg(), TOAST_STYLE_NO_SIGNAL_2);

    }

    NAV_LOG_ON_FAIL(i4_ret);

}

static VOID _no_signal_callback_view(
                    HANDLE_T                    h_timer,
                    SCRN_SVR_VIEW_T*             pt_view
                    )
{
    if (
        !a_nav_ipts_first_input_after_boot() &&
        a_power_state_off() == FALSE &&
        a_smart_cast_switch_pending() == TRUE &&
        a_nav_ipts_on_smartcast() == FALSE
        )
    {
        nav_request_context_switch(_change_no_signal_toast,
                               NULL,
                               NULL,
                               NULL);
    }
}
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
extern message boot_sc_logger;
extern SCRN_SVR_T  t_g_scrn_svr;

extern INT32 tuner_setup_warning_show(UTF16_T* w2s_str);
extern INT32 tuner_setup_warning_hide(VOID);


/*-----------------------------------------------------------------------------
 * Name
 *      scrn_svr_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern  BOOL a_is_oled_compensation_support();

VOID _scrn_svr_view_menu_listener(UINT32 ui4_page_id, MENU_PAGE_EVENT_T e_page_event)
{
    //Regardless of what menu is showing - if any menu is showing cancel timer
    a_nav_ipts_cancel_smart_cast_after_n_seconds();
}

INT32 scrn_svr_view_init(
                    SCRN_SVR_T*                 pt_this,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    INT32            i4_ret = NAVR_OK;
    SCRN_SVR_VIEW_T* pt_view = &pt_this->t_view;

    t_g_pt_view = pt_view;
    pt_view->h_canvas = h_canvas;
    pt_view->h_toast_warning_view = NULL_HANDLE;
    pt_view->h_toast_warning_view_with_title = NULL_HANDLE;
    pt_view->w2s_err_title[0] = 0;

    i4_ret = nav_img_create_remote_link_icon(&h_g_remote_link_icon);
    if (NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_remote_input_icon(&h_g_input_icon);
    if (NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    b_oled = a_is_oled_compensation_support();

    i4_ret = c_timer_create(&h_no_signal_timer);
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }
    menu_pm_set_page_event_listener(_scrn_svr_view_menu_listener);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      scrn_svr_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 scrn_svr_view_deinit(
                    SCRN_SVR_VIEW_T*            pt_view
                    )
{
    INT32                 i4_ret = NAVR_OK;

    if (pt_view->h_toast_warning_view != NULL_HANDLE)
    {
        i4_ret = a_toast_destroy(pt_view->h_toast_warning_view);
        pt_view->h_toast_warning_view = NULL_HANDLE;

        if (TOASTR_OK != i4_ret)
        {
            DBG_INFO(("%s, %d. i4_ret: %d. a_toast_destroy failed!\n", __FUNCTION__, __LINE__, i4_ret));
        }
    }

    if (pt_view->h_toast_warning_view_with_title != NULL_HANDLE)
    {
        i4_ret = a_toast_destroy(pt_view->h_toast_warning_view_with_title);
        pt_view->h_toast_warning_view_with_title = NULL_HANDLE;

        if (TOASTR_OK != i4_ret)
        {
            DBG_INFO(("%s, %d. i4_ret: %d. a_toast_destroy failed!\n", __FUNCTION__, __LINE__, i4_ret));
        }
    }

    if (pt_view->h_toast_no_signal != NULL_HANDLE)
    {
        i4_ret = a_toast_destroy(pt_view->h_toast_no_signal);
        pt_view->h_toast_no_signal = NULL_HANDLE;

        if (TOASTR_OK != i4_ret)
        {
            DBG_INFO(("%s, %d. i4_ret: %d. a_toast_destroy failed!\n", __FUNCTION__, __LINE__, i4_ret));
        }
    }

    if (pt_view->h_toast_no_signal_2 != NULL_HANDLE)
    {
        i4_ret = a_toast_destroy(pt_view->h_toast_no_signal_2);
        pt_view->h_toast_no_signal_2 = NULL_HANDLE;

        if (TOASTR_OK != i4_ret)
        {
            DBG_INFO(("%s, %d. i4_ret: %d. a_toast_destroy failed!\n", __FUNCTION__, __LINE__, i4_ret));
        }
    }

    i4_ret = a_wdk_toast_deinit(&t_g_wdk_scrn_svr_middle);
    if (WDKR_OK != i4_ret)
    {
        DBG_INFO(("%s, %d. i4_ret: %d. a_wdk_toast_deinit failed!\n", __FUNCTION__, __LINE__, i4_ret));
    }

    i4_ret = a_wdk_toast_deinit(&t_g_wdk_scrn_svr_av_status);
    if (WDKR_OK != i4_ret)
    {
        DBG_INFO(("%s, %d. i4_ret: %d. a_wdk_toast_deinit failed!\n", __FUNCTION__, __LINE__, i4_ret));
    }

    if (h_g_remote_link_icon != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy(h_g_remote_link_icon);
        h_g_remote_link_icon = NULL_HANDLE;
    }


    if (h_g_input_icon != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy(h_g_input_icon);
        h_g_input_icon = NULL_HANDLE;
    }

    if (c_handle_valid(h_no_signal_timer) == TRUE) {
        c_timer_delete(h_no_signal_timer);
        h_no_signal_timer = NULL_HANDLE;
    }

    e_g_toast_style = TOAST_STYLE_MAX_NUM;

    return NAVR_OK;
}

static INT32 _scrn_svr_view_no_signal_get_title_str(
                            UTF16_T *pw2s_title_str,
                            UINT32 ui4_str_len
                            )
{
    INT32           i4_ret          = NAVR_OK;
    INT32           i4_ret_cec      = CECR_FAIL;
    ISL_REC_T       t_isl           = {0};
    CEC_DEV_INFO_T  t_dev_info      = {0};
    UINT8           ui1_hide_val    = 0;
    UTF16_T         *pw2s_name      = NULL;
    UINT8           ui1_cec_func    = APP_CFG_CEC_OFF;
    UTF16_T         w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN+1]        = {0};
    UTF16_T         w2s_alias_orig[APP_CFG_CUSTOM_INP_NAME_LEN+1]   = {0};
    UTF16_T         w2s_alias_custom[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    UTF16_T         w2s_alias_cec[APP_CFG_CUSTOM_INP_NAME_LEN+1]    = {0};
    CHAR            s_tmp_name[APP_CFG_CUSTOM_INP_NAME_LEN+1]       = {0};

    /* get current input source name */
    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl);
    if(TVR_OK != i4_ret)
    {
        DBG_ERROR(("%s(): a_tv_get_isl_rec_by_win_id failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    //port name
    /*display name*/
    pw2s_name = a_isl_get_display_name(&t_isl);
    if(c_uc_w2s_strlen(pw2s_name) > 0)
    {
        c_uc_w2s_strcpy(w2s_alias_orig,pw2s_name);
    }

    //cec device name,custom name or port name,depend on isl(ps:but in unplug case,isl has not been updated yet)
    //alias name
    a_isl_get_display_name_ex(&t_isl, w2s_alias, APP_CFG_CUSTOM_INP_NAME_LEN);

    //get input hide list(plug or unplug)
    a_cfg_cust_get_hide_from_input(&ui1_hide_val);
    //get cec device name
    a_cfg_get_cec_func(&ui1_cec_func);
    if(t_isl.e_src_type == INP_SRC_TYPE_AV &&
    t_isl.t_avc_info.e_video_type == DEV_AVC_HDMI &&
    ui1_cec_func != APP_CFG_CEC_OFF)
    {
        UINT8 hdmi_cec_dev_idx = 0;
        i4_ret_cec =  a_cec_get_act_dev_by_no_signal(a_nav_cec_get_mw_handle (), t_isl.ui1_internal_id, &hdmi_cec_dev_idx, &t_dev_info);
        if (i4_ret_cec == CECR_OK && c_uc_w2s_strlen(t_dev_info.aw2_osd_name) > 0)
        {
            c_uc_w2s_strcpy(w2s_alias_cec,t_dev_info.aw2_osd_name);
        }
    }

    //get custom name
    a_cfg_custom_get_inp_name(t_isl.ui1_id,s_tmp_name);
    if(c_strlen(s_tmp_name) > 0)
    {
        c_uc_ps_to_w2s(s_tmp_name,w2s_alias_custom,(sizeof(w2s_alias_custom) - 1) );
    }

    c_uc_w2s_strncpy(pw2s_title_str, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_NO_SIGNAL_DESC1), ui4_str_len);

    //for cec name
    if(c_uc_w2s_strlen(w2s_alias_cec) && (ui1_hide_val ||a_nav_is_signal_loss() == TRUE))
    {
        c_uc_w2s_strncat(pw2s_title_str, w2s_alias_cec, ui4_str_len-c_uc_w2s_strlen(pw2s_title_str));
    }
    //for custom name
    else if(c_uc_w2s_strlen(w2s_alias_custom))
    {
        c_uc_w2s_strncat(pw2s_title_str, w2s_alias_custom, ui4_str_len-c_uc_w2s_strlen(pw2s_title_str));
    }
    //for port name
    else if(c_uc_w2s_strlen(w2s_alias_orig))
    {
        c_uc_w2s_strncat(pw2s_title_str, w2s_alias_orig, ui4_str_len-c_uc_w2s_strlen(pw2s_title_str));
    }
    else
    {
        DBG_ERROR(("%s() Line-%d : can not get input src name \n",__FUNCTION__,__LINE__));
    }

    return NAVR_OK;

}


static INT32 _scrn_svr_view_acquire_signal_get_title_str(
                            UTF16_T *pw2s_title_str,
                            UINT32 ui4_str_len
                            )
{
    INT32           i4_ret          = NAVR_OK;
    INT32           i4_ret_cec      = CECR_FAIL;
    ISL_REC_T       t_isl           = {0};
    CEC_DEV_INFO_T  t_dev_info      = {0};
    UINT8           ui1_hide_val    = 0;
    UTF16_T         *pw2s_name      = NULL;
    UINT8           ui1_cec_func    = APP_CFG_CEC_OFF;
    UTF16_T         w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN+1]        = {0};
    UTF16_T         w2s_alias_orig[APP_CFG_CUSTOM_INP_NAME_LEN+1]   = {0};
    UTF16_T         w2s_alias_custom[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    UTF16_T         w2s_alias_cec[APP_CFG_CUSTOM_INP_NAME_LEN+1]    = {0};
    CHAR            s_tmp_name[APP_CFG_CUSTOM_INP_NAME_LEN+1]       = {0};
    UTF16_T         w2s_alias_temp[APP_CFG_CUSTOM_INP_NAME_LEN+1]   = {0};
    UTF16_T        *pt_w2s_msg = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_ACQUIRING_SIGNAL);
    UINT32          ui4_msg_len = c_uc_w2s_strlen(pt_w2s_msg);

    /* get current input source name */
    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl);
    if(TVR_OK != i4_ret)
    {
        DBG_ERROR(("%s(): a_tv_get_isl_rec_by_win_id failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    //port name
    /*display name*/
    pw2s_name = a_isl_get_display_name(&t_isl);
    if(c_uc_w2s_strlen(pw2s_name) > 0)
    {
        c_uc_w2s_strcpy(w2s_alias_orig,pw2s_name);
    }

    //cec device name,custom name or port name,depend on isl(ps:but in unplug case,isl has not been updated yet)
    //alias name
    a_isl_get_display_name_ex(&t_isl, w2s_alias, APP_CFG_CUSTOM_INP_NAME_LEN);

    //get input hide list(plug or unplug)
    a_cfg_cust_get_hide_from_input(&ui1_hide_val);

    a_cfg_get_cec_func(&ui1_cec_func);
    if(t_isl.e_src_type == INP_SRC_TYPE_AV &&
    t_isl.t_avc_info.e_video_type == DEV_AVC_HDMI &&
    ui1_cec_func != APP_CFG_CEC_OFF)
    {
        UINT8 hdmi_cec_dev_idx = 0;
        i4_ret_cec =  a_cec_get_act_dev_by_no_signal(a_nav_cec_get_mw_handle (), t_isl.ui1_internal_id, &hdmi_cec_dev_idx, &t_dev_info);
        if (i4_ret_cec == CECR_OK && c_uc_w2s_strlen(t_dev_info.aw2_osd_name) > 0)
        {
            c_uc_w2s_strcpy(w2s_alias_cec,t_dev_info.aw2_osd_name);
        }
    }

    //get custom name
    a_cfg_custom_get_inp_name(t_isl.ui1_id,s_tmp_name);
    if(c_strlen(s_tmp_name) > 0)
    {
        c_uc_ps_to_w2s(s_tmp_name,w2s_alias_custom,(sizeof(w2s_alias_custom) - 1) );
    }

    //c_uc_w2s_strncpy(pw2s_title_str, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_NO_SIGNAL_DESC1), ui4_str_len);

    //for cec name
    if(c_uc_w2s_strlen(w2s_alias_cec) && (ui1_hide_val ||a_nav_is_signal_loss() == TRUE))
    {
        c_uc_w2s_strncat(pw2s_title_str, w2s_alias_cec, ui4_str_len-c_uc_w2s_strlen(pw2s_title_str));
    }
    //for custom name
    else if(c_uc_w2s_strlen(w2s_alias_custom))
    {
        c_uc_w2s_strncat(pw2s_title_str, w2s_alias_custom, ui4_str_len-c_uc_w2s_strlen(pw2s_title_str));
    }

    //for port name
    else if(c_uc_w2s_strlen(w2s_alias_orig))
    {
        c_uc_w2s_strncat(pw2s_title_str, w2s_alias_orig, ui4_str_len-c_uc_w2s_strlen(pw2s_title_str));
    }
    else
    {
        DBG_ERROR(("%s() Line-%d : can not get input src name \n",__FUNCTION__,__LINE__));
    }
     
    c_uc_w2s_strcpy(w2s_alias_temp,pt_w2s_msg);
    c_uc_w2s_strncat(w2s_alias_temp, pw2s_title_str, ui4_str_len-c_uc_w2s_strlen(w2s_alias_temp));
    c_uc_w2s_strcpy(pw2s_title_str,w2s_alias_temp);
    //c_uc_w2s_strncat(pw2s_title_str, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_ACQUIRING_SIGNAL), ui4_str_len-c_uc_w2s_strlen(pw2s_title_str));

    return NAVR_OK;

}

static INT32 _scrn_svr_view_blank_scrn_timer_start(VOID)
{
    menu_custom_set_blank_scrn_mode(BLK_SCRN_OLED_NO_SIGNAL);
    menu_blank_oled_scrn_timer_start();

    return NAVR_OK;
}

static INT32 _scrn_svr_view_blank_scrn_timer_stop(VOID)
{
    menu_blank_oled_scrn_timer_stop();

    return NAVR_OK;
}

static INT32 _scrn_svr_view_no_signal_toast_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    SCRN_SVR_VIEW_T* pt_view = t_g_pt_view;
    TOAST_CONTROL_T*  pt_toast_control = NULL;

    INT32  i4_ret = NAVR_OK;

    boot_sc_logger = setUserAction(boot_sc_logger, "ALLOW");
    if(!nav_is_component_visible(NAV_COMP_ID_SCREEN_SAVER))
    {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(pt_view->h_toast_no_signal_2,
                            WGL_CMD_GL_GET_ATTACH_DATA,
                            WGL_PACK(&pt_toast_control),
                            NULL);

    if (i4_ret == WGLR_OK && pt_toast_control != NULL && nav_is_active())
    {
        switch (ui4_msg)
        {
            case WGL_MSG_KEY_DOWN:
                if (IOM_GET_EVT_GRP_ID((UINT32)pv_param1) ==  0x3f000) //Left button
                {
                    //Cancel button becomes "push
                    //Home button becomes "enable
                    c_wgl_do_cmd(pt_toast_control->u.t_no_signal_2.h_rtn_hm_button,
                                    WGL_CMD_BTN_SET_PUSHED,
                                    FALSE,
                                    NULL);

                    c_wgl_do_cmd(pt_toast_control->u.t_no_signal_2.h_cancel_button,
                                    WGL_CMD_BTN_SET_PUSHED,
                                    TRUE,
                                    NULL);

                    g_scrn_svr_toast_selection = SCRN_SVR_TOAST_SELECTION_CANCEL;
                    c_wgl_repaint(pt_toast_control->u.t_no_signal_2.h_rtn_hm_button, NULL, FALSE);
                    c_wgl_repaint(pt_toast_control->u.t_no_signal_2.h_cancel_button, NULL, FALSE);

                }
                else if (IOM_GET_EVT_GRP_ID((UINT32)pv_param1) ==  0x3f001) //Right button
                {
                    //Cancel button becomes "highlight
                    //Home button becomes "push_unhighlight
                    c_wgl_do_cmd(pt_toast_control->u.t_no_signal_2.h_rtn_hm_button,
                                    WGL_CMD_BTN_SET_PUSHED,
                                    TRUE,
                                    NULL);

                    c_wgl_do_cmd(pt_toast_control->u.t_no_signal_2.h_cancel_button,
                                    WGL_CMD_BTN_SET_PUSHED,
                                    FALSE,
                                    NULL);

                    g_scrn_svr_toast_selection = SCRN_SVR_TOAST_SELECTION_RETURN_HOME;
                    c_wgl_repaint(pt_toast_control->u.t_no_signal_2.h_rtn_hm_button, NULL, FALSE);
                    c_wgl_repaint(pt_toast_control->u.t_no_signal_2.h_cancel_button, NULL, FALSE);
                }
                else if (IOM_GET_EVT_GRP_ID((UINT32)pv_param1) ==  0x4f000) //select button
                {
                    CHAR          s_disp_name[33] = {0};
                    UINT8         ui1_input_id = 0;
                    ISL_REC_T     t_isl_rec;
                    char str[10];

                    switch (g_scrn_svr_toast_selection)
                    {
                        case SCRN_SVR_TOAST_SELECTION_CANCEL:
                            //Hide no_signal_2
                            i4_ret = scrn_svr_view_hide(pt_view, TOAST_STYLE_NO_SIGNAL_2);
                            NAV_LOG_ON_FAIL(i4_ret);
                            //... and show no_signal_1
                            i4_ret = scrn_svr_view_show(pt_view, nav_get_crnt_err_msg(), TOAST_STYLE_NO_SIGNAL_1);
                            NAV_LOG_ON_FAIL(i4_ret);
                            a_nav_ipts_cancel_smart_cast_after_n_seconds();
                            a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
                            a_cfg_get_input_src(s_disp_name, &ui1_input_id);
                            a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
                            sprintf(str, "%d", ui1_input_id);
                            boot_sc_logger = setInputFrom(boot_sc_logger, (char*)inputSwitchFromText(ui1_input_id));
                            boot_sc_logger = setUserAction(boot_sc_logger, "CANCEL");
                            boot_sc_logger = setInputTo(boot_sc_logger, str);
                            boot_sc_logger = setPowerOnInputSetting(boot_sc_logger, (char*)powerOnIndexToText(get_power_on_device()));
                            showLog(boot_sc_logger);
                            sendLog(boot_sc_logger);
                            break;

                        case SCRN_SVR_TOAST_SELECTION_RETURN_HOME:
                            a_nav_ipts_cancel_smart_cast_after_n_seconds();
                            a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
                            a_cfg_get_input_src(s_disp_name, &ui1_input_id);
                            a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
                            sprintf(str, "%d", ui1_input_id);
                            boot_sc_logger = setInputFrom(boot_sc_logger, (char*)inputSwitchFromText(ui1_input_id));
                            boot_sc_logger = setUserAction(boot_sc_logger, "HOME");
                            boot_sc_logger = setInputTo(boot_sc_logger, "SMARTCAST");
                            boot_sc_logger = setPowerOnInputSetting(boot_sc_logger, (char*)powerOnIndexToText(get_power_on_device()));
                            showLog(boot_sc_logger);
                            sendLog(boot_sc_logger);
                            rest_event_notify_current_input("CAST:SMARTCAST");
                            break;

                        default:
                            break;
                    }
                }
                else
                {
                    //Hide no_signal_2
                    i4_ret = scrn_svr_view_hide(pt_view, TOAST_STYLE_NO_SIGNAL_2);
                    NAV_LOG_ON_FAIL(i4_ret);
                    //... and show no_signal_1
                    i4_ret = scrn_svr_view_show(pt_view, nav_get_crnt_err_msg(), TOAST_STYLE_NO_SIGNAL_1);
                    NAV_LOG_ON_FAIL(i4_ret);
                    a_nav_ipts_cancel_smart_cast_after_n_seconds();
                    a_amb_default_key_handler(WGL_MSG_KEY_DOWN, pv_param1, NULL);
                }
	            break;
	        default:
                break;
        }
    }
    return c_wgl_default_msg_proc(h_widget,
                              ui4_msg,
                              pv_param1,
                              pv_param2);
}


/*-----------------------------------------------------------------------------
 * Name
 *      scrn_svr_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 scrn_svr_view_show(
                    SCRN_SVR_VIEW_T*            pt_view,
                    UTF16_T*                    pw2s_string,
                    TOAST_STYLE_T               e_toast_style
                    )
{

    INT32                 i4_ret = NAVR_OK;
    UTF16_T  w2s_tts_content[512] = {0};

    if(e_toast_style == TOAST_STYLE_MAX_NUM)
        return NAVR_OK;

    /* hide pre wdk toast */
    if (e_g_toast_style != TOAST_STYLE_MAX_NUM && e_g_toast_style != e_toast_style)
    {
        scrn_svr_view_hide(pt_view, e_g_toast_style);
    }

    DBG_LOG_PRINT(("[SCRN_SVR][%s%d] e_toast_style = %d \n", __FUNCTION__, __LINE__, e_toast_style));
    if(pw2s_string)
    {
        CHAR msg[256] = {0};
        c_uc_w2s_to_ps(pw2s_string,msg,255);
        DBG_INFO(("[SCRN_SVR][%s%d] msg = \"%s\" \n", __FUNCTION__, __LINE__, msg));
    }

    if (TOAST_STYLE_NO_SIGNAL_2 == e_toast_style ||
        TOAST_STYLE_NO_SIGNAL_1 == e_toast_style)
    {
        UTF16_T  w2s_title_str[64]  = {0};
        UTF16_T  w2s_msg_str_1[256] = {0};
        UTF16_T  w2s_msg_str_2[256] = {0};
        CHAR           str_fmt[256] = {0};
        CHAR           str_tmp[256] = {0};

        TOAST_CUSTOMIZATION_DATA_T  t_custom_data;

        if (TOAST_STYLE_NO_SIGNAL_1 == e_toast_style)
        {
            if (pt_view->h_toast_no_signal == NULL_HANDLE)
            {
                TOAST_INIT_PARAM_T  t_toast_init;

                c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));
                t_toast_init.e_toast_style = e_toast_style;
                t_toast_init.h_canvas = pt_view->h_canvas;
                i4_ret = a_toast_create(&t_toast_init, &pt_view->h_toast_no_signal);

                if (TOASTR_OK != i4_ret)
                {
                    DBG_INFO(("%s, %d. i4_ret: %d. a_toast_create failed!\n", __FUNCTION__, __LINE__, i4_ret));
                }
            }
        }
        if (TOAST_STYLE_NO_SIGNAL_2 == e_toast_style)
        {
            if (pt_view->h_toast_no_signal_2 == NULL_HANDLE)
            {
                TOAST_INIT_PARAM_T  t_toast_init;
                c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));
                t_toast_init.e_toast_style = e_toast_style;
                t_toast_init.h_canvas = pt_view->h_canvas;
                i4_ret = a_toast_create(&t_toast_init, &pt_view->h_toast_no_signal_2);
                if (TOASTR_OK != i4_ret)
                {
                    DBG_INFO(("%s, %d. i4_ret: %d. a_toast_create failed!\n", __FUNCTION__, __LINE__, i4_ret));
                }
            }
        }

        _scrn_svr_view_no_signal_get_title_str(w2s_title_str, 64-1);

        do {
            UTF16_T *pt_w2s_msg = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_NO_SIGNAL_DESC2);
            UINT32  ui4_msg_len = c_uc_w2s_strlen(pt_w2s_msg);
            UINT32  ui4_index = 0;

            if (ui4_msg_len >= 256)
            {
                DBG_INFO(("%s, %d. i4_ret: %d. string overflow!\n", __FUNCTION__, __LINE__,i4_ret));
                return NAVR_FAIL;
            }

            while(ui4_index < ui4_msg_len)
            {
                if (*(pt_w2s_msg+ui4_index) == L'.')
                {
                    break;
                }
                ui4_index++;
            }

            if (ui4_index < ui4_msg_len)
            {
                CHAR          s_disp_name[33] = {0};

                UINT8         ui1_input_id = 0;
                ISL_REC_T     t_isl_rec;
                a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
                a_cfg_get_input_src(s_disp_name, &ui1_input_id);
                a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
                DBG_INFO(("current input source type 0x%x, source name is %s e_video_type = 0x%x\n",t_isl_rec.e_src_type,t_isl_rec.s_src_name,t_isl_rec.t_avc_info.e_video_type));

                c_uc_w2s_strncpy(w2s_msg_str_1, pt_w2s_msg, ui4_index+1);
                c_uc_w2s_to_ps(w2s_msg_str_1,str_fmt,256);
                if(INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
                {
                    c_snprintf(str_tmp,256,str_fmt,(MLM_NAV_LANG_ENG == nav_get_mlm_lang_id()) ? "RF Cable" :
                                                   (MLM_NAV_LANG_FRE == nav_get_mlm_lang_id()) ? "Câble RF":"Cable RF");
                }
                else
                {
                    c_snprintf(str_tmp,256,str_fmt,"source device");
                }
                c_uc_ps_to_w2s(str_tmp,w2s_msg_str_2,256);
                INT32 i4_len = c_uc_w2s_strlen(w2s_msg_str_2);
                c_memset(w2s_msg_str_1,0,sizeof(w2s_msg_str_1));
                c_uc_w2s_strncat(w2s_msg_str_1, w2s_msg_str_2, i4_len + 1);
                c_uc_w2s_strncat(w2s_msg_str_1, L"\n", 1);
                c_uc_w2s_strncat(w2s_msg_str_1, pt_w2s_msg+ui4_index+1, c_uc_w2s_strlen(pt_w2s_msg+ui4_index+1));
                c_memset(w2s_msg_str_2,0,sizeof(w2s_msg_str_2));
            }
        } while(FALSE);

        do {
            UTF16_T  *pw2s_start = &w2s_msg_str_1[0];
            UTF16_T  *pw2s_end = &w2s_msg_str_1[0] + c_uc_w2s_strlen(pw2s_start);

            UTF16_T  *pw2s_sub_text = L"ICON";
            SIZE_T   t_sub_size = c_uc_w2s_strlen(pw2s_sub_text);

            UTF16_T  *pw2s_dst = &w2s_msg_str_2[0];

            while (pw2s_start <= (pw2s_end - t_sub_size))
            {
                SIZE_T  t_cmp_offset = 0;
                while (t_cmp_offset < t_sub_size)
                {
                    if (*(pw2s_start + t_cmp_offset) == *(pw2s_sub_text + t_cmp_offset))
                    {
                        t_cmp_offset++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (t_cmp_offset == t_sub_size)
                {
                    c_uc_w2s_strncpy(pw2s_dst, L"%p", 2);
                    pw2s_dst += 2;
                }
                else
                {
                    t_cmp_offset = (t_cmp_offset == 0) ? 1 : t_cmp_offset;
                    c_uc_w2s_strncpy(pw2s_dst, pw2s_start, t_cmp_offset);
                    pw2s_dst += t_cmp_offset;
                }
                pw2s_start += t_cmp_offset;
            }

            if (pw2s_start < pw2s_end)
            {
                c_uc_w2s_strncat(pw2s_dst, pw2s_start, pw2s_end - pw2s_start);
            }

        } while(FALSE);

        banner_hide_sidebar();

        c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));

        if (TOAST_STYLE_NO_SIGNAL_2 == e_toast_style)
        {
            t_custom_data.u.t_no_signal_2_init.w2s_title_str = (VOID*)w2s_title_str;
            t_custom_data.u.t_no_signal_2_init.w2s_msg_str = (VOID*)w2s_msg_str_2;
            t_custom_data.u.t_no_signal_2_init.h_insert_img = h_g_input_icon;
        }
        else if (TOAST_STYLE_NO_SIGNAL_1 == e_toast_style)
        {
            t_custom_data.u.t_no_signal_1_init.w2s_title_str = (VOID*)w2s_title_str;
            t_custom_data.u.t_no_signal_1_init.w2s_msg_str = (VOID*)w2s_msg_str_2;
            t_custom_data.u.t_no_signal_1_init.h_insert_img = h_g_input_icon;
        }


        TOAST_CONTROL_T*  pt_toast_control = NULL;

        if (TOAST_STYLE_NO_SIGNAL_2 == e_toast_style)
        {
            i4_ret = c_wgl_do_cmd(pt_view->h_toast_no_signal_2,
                                    WGL_CMD_GL_GET_ATTACH_DATA,
                                    WGL_PACK(&pt_toast_control),
                                    NULL);
            if (i4_ret == WGLR_OK && pt_toast_control != NULL && nav_is_active())
            {
                t_custom_data.h_focus_handle = pt_toast_control->u.t_no_signal_2.h_rtn_hm_button;
                t_custom_data.pf_wgl_cb = _scrn_svr_view_no_signal_toast_fct;
            }

            //Cancel button becomes "highlight
            //Home button becomes "push_unhighlight
            c_wgl_do_cmd(pt_toast_control->u.t_no_signal_2.h_rtn_hm_button,
                                    WGL_CMD_BTN_SET_PUSHED,
                                    TRUE,
                                    NULL);

            c_wgl_do_cmd(pt_toast_control->u.t_no_signal_2.h_cancel_button,
                                    WGL_CMD_BTN_SET_PUSHED,
                                    FALSE,
                                    NULL);

            g_scrn_svr_toast_selection = SCRN_SVR_TOAST_SELECTION_RETURN_HOME;
            c_wgl_repaint(pt_toast_control->u.t_no_signal_2.h_rtn_hm_button, NULL, FALSE);
            c_wgl_repaint(pt_toast_control->u.t_no_signal_2.h_cancel_button, NULL, FALSE);
        }
        if (TOAST_STYLE_NO_SIGNAL_1 == e_toast_style) {
            if (a_nav_should_display_no_signal_indication()) {
                i4_ret = a_toast_show(pt_view->h_toast_no_signal, &t_custom_data);
            }
            if(a_nav_should_display_messaging())
            {
                a_nav_displaying_no_signal_indication();

                i4_ret = c_timer_stop(h_no_signal_timer);
                i4_ret = c_timer_start(
                        h_no_signal_timer,
                        SCRN_SVR_DELAY_TO_ACTIVATE_NO_SIGNAL_SWITCH_VIEW,
                        X_TIMER_FLAG_ONCE,
                        _no_signal_callback_view,
                       NULL);
            }
        }
        else if (TOAST_STYLE_NO_SIGNAL_2 == e_toast_style) {
            i4_ret = a_toast_show(pt_view->h_toast_no_signal_2, &t_custom_data);
        }
        do {
            UINT32 ui4_msg_len = 0;
            UINT32 ui4_index = 0;

            c_uc_w2s_strncpy(w2s_tts_content, w2s_title_str, 64);
            c_uc_w2s_strncat(w2s_tts_content, L", ", 2);
            c_uc_w2s_strncat(w2s_tts_content,
                             MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_NO_SIGNAL_DESC2_TTS),
                             512-c_uc_w2s_strlen(w2s_tts_content));

            ui4_msg_len = c_uc_w2s_strlen(w2s_tts_content);
            ui4_index = 0;

            while (ui4_index < ui4_msg_len)
            {
                if (w2s_tts_content[ui4_index] == '-')
                {
                    w2s_tts_content[ui4_index] = ' ';
                }
                ui4_index++;
            }

            pw2s_string = &w2s_tts_content[0];
        } while(FALSE);

    }
    else if (TOAST_STYLE_NO_SIGNAL == e_toast_style)
    {
        WDK_TOAST_PARAM_T     t_widget_param;
        c_memset(&t_widget_param, 0, sizeof(WDK_TOAST_PARAM_T));
        t_widget_param.e_toast_style = WDK_NO_SINGLE;
        t_widget_param.w2s_str       = (VOID*)pw2s_string;
        t_widget_param.pf_cb         = NULL;

        if (FALSE == t_g_wdk_scrn_svr_middle.b_have_init)
        {
            i4_ret = a_wdk_toast_init(pt_view->h_canvas, (VOID*)(&t_widget_param), &t_g_wdk_scrn_svr_middle);
            if (WDKR_OK != i4_ret)
            {
                DBG_INFO(("%s, %d. i4_ret: %d. a_wdk_toast_init failed!\n", __FUNCTION__, __LINE__, i4_ret));
            }
        }

        i4_ret = a_wdk_toast_activate(TRUE, (VOID*)(&t_widget_param), &t_g_wdk_scrn_svr_middle);
    }
    else if (TOAST_STYLE_MSG == e_toast_style)
    {
        TV_WIN_ID_T                 e_focus_win_id = TV_WIN_ID_LAST_VALID_ENTRY;
        nav_get_focus_id (&e_focus_win_id);

        //check window ID
        if(e_focus_win_id >= TV_WIN_ID_LAST_VALID_ENTRY)
        {
            return NAVR_FAIL;
        }

        //update TUNER_SETUP start msg,but not do it in scrn_svr,otherwise casue wgl react slow after show twice toast
        if((t_g_scrn_svr.t_msgs[e_focus_win_id].e_type == SCRN_SVR_MSG_TYPE_MLM_KEY) && \
            (t_g_scrn_svr.t_msgs[e_focus_win_id].u.ui2_mlm_key == MLM_NAV_KEY_MSG_NO_CH_LIST))
        {
            DBG_LOG_PRINT(("[tuner setup] %s %d \n",__FUNCTION__,__LINE__));
            b_tuner_setup_view_showing = TRUE;
            tuner_setup_warning_show(MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_MSG_NO_CH_LIST));
        }
        else
        {
            TOAST_CUSTOMIZATION_DATA_T  t_custom_data;
            if (pt_view->h_toast_warning_view == NULL_HANDLE)
            {
                TOAST_INIT_PARAM_T  t_toast_init;

                c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));

                t_toast_init.e_toast_style = TOAST_STYLE_MSG;
                t_toast_init.h_canvas = pt_view->h_canvas;
                t_toast_init.t_custom_setting.u.t_msg_init.e_msg_type = TOAST_MSG_TYPE_WITH_WARNING_ICON;
                i4_ret = a_toast_create(&t_toast_init, &pt_view->h_toast_warning_view);
                if (TOASTR_OK != i4_ret)
                {
                    DBG_INFO(("%s, %d. i4_ret: %d. a_toast_create failed!\n", __FUNCTION__, __LINE__, i4_ret));
                }
            }

            c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));
            t_custom_data.u.t_msg_init.w2s_msg_str = (VOID*)pw2s_string;
            i4_ret = a_toast_show(pt_view->h_toast_warning_view, &t_custom_data);
        }
    }
    else if (TOAST_STYLE_MSG_WITH_TITLE_CONTENT == e_toast_style)
    {
        TOAST_CUSTOMIZATION_DATA_T  t_custom_data;
        if (pt_view->h_toast_warning_view_with_title == NULL_HANDLE)
        {
            TOAST_INIT_PARAM_T  t_toast_init;

            c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));

            t_toast_init.e_toast_style = TOAST_STYLE_MSG_WITH_TITLE_CONTENT;
            t_toast_init.h_canvas = pt_view->h_canvas;
            i4_ret = a_toast_create(&t_toast_init, &pt_view->h_toast_warning_view_with_title);
            if (TOASTR_OK != i4_ret)
            {
                DBG_INFO(("%s, %d. i4_ret: %d. a_toast_create failed!\n", __FUNCTION__, __LINE__, i4_ret));
            }
        }

        c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));
        t_custom_data.u.t_msg_with_title_init.w2s_title_str = (VOID*)(pt_view->w2s_err_title);
        t_custom_data.u.t_msg_with_title_init.w2s_msg_str = (VOID*)pw2s_string;
        t_custom_data.u.t_msg_with_title_init.h_insert_img = h_g_remote_link_icon;
        i4_ret = a_toast_show(pt_view->h_toast_warning_view_with_title, &t_custom_data);
    }
    else if (TOAST_STYLE_CENTER_DIALOG == e_toast_style)
    {
        WDK_TOAST_PARAM_T     t_widget_param;
        c_memset(&t_widget_param, 0, sizeof(WDK_TOAST_PARAM_T));
        t_widget_param.e_toast_style = WDK_SCREEN_CENTER_MSG;
        t_widget_param.w2s_str       = (VOID*)pw2s_string;
        t_widget_param.pf_cb         = NULL;

        if (FALSE == t_g_wdk_scrn_svr_av_status.b_have_init)
        {
            i4_ret = a_wdk_toast_init(pt_view->h_canvas, (VOID*)(&t_widget_param), &t_g_wdk_scrn_svr_av_status);
            if (WDKR_OK != i4_ret)
            {
                DBG_INFO(("%s, %d. i4_ret: %d. a_wdk_toast_init failed!\n", __FUNCTION__, __LINE__, i4_ret));
            }
        }

        i4_ret = a_wdk_toast_activate(TRUE, (VOID*)(&t_widget_param), &t_g_wdk_scrn_svr_av_status);
    }
    else if (TOAST_STYLE_SIGNAL_ACQUIRE == e_toast_style)
    {
        UTF16_T  w2s_title_str[64]  = {0};
        UTF16_T  w2s_msg_str_1[256] = {0};
        UTF16_T  w2s_msg_str_2[256] = {0};
        CHAR           str_fmt[256] = {0};
        CHAR           str_tmp[256] = {0};

        TOAST_CUSTOMIZATION_DATA_T  t_custom_data;

        if (pt_view->h_toast_signal_acquire == NULL_HANDLE)
        {
            TOAST_INIT_PARAM_T  t_toast_init;

            c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));
            t_toast_init.e_toast_style = e_toast_style;
            t_toast_init.h_canvas = pt_view->h_canvas;
            i4_ret = a_toast_create(&t_toast_init, &pt_view->h_toast_signal_acquire);

            if (TOASTR_OK != i4_ret)
            {
                DBG_ERROR(("%s, %d. i4_ret: %d. a_toast_create failed!\n", __FUNCTION__, __LINE__, i4_ret));
            }
        }

        _scrn_svr_view_acquire_signal_get_title_str(w2s_title_str, 64-1);

    #if 0 // no need for Signal Acquire UI
        do {
            UTF16_T *pt_w2s_msg = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_NO_SIGNAL_DESC2);
            //Check if the %s is connected and powered on. Or press the INPUT button to select the input for the source device.
            UINT32  ui4_msg_len = c_uc_w2s_strlen(pt_w2s_msg);
            UINT32  ui4_index = 0;

            if (ui4_msg_len >= 256)
            {
                DBG_INFO(("%s, %d. i4_ret: %d. string overflow!\n", __FUNCTION__, __LINE__,i4_ret));
                return NAVR_FAIL;
            }

            while(ui4_index < ui4_msg_len)
            {
                if (*(pt_w2s_msg+ui4_index) == L'.')
                {
                    break;
                }
                ui4_index++;
            }

            if (ui4_index < ui4_msg_len)
            {
                CHAR          s_disp_name[33] = {0};

                UINT8         ui1_input_id = 0;
                ISL_REC_T     t_isl_rec;
                a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
                a_cfg_get_input_src(s_disp_name, &ui1_input_id);
                a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
                DBG_INFO(("current input source type 0x%x, source name is %s e_video_type = 0x%x\n",t_isl_rec.e_src_type,t_isl_rec.s_src_name,t_isl_rec.t_avc_info.e_video_type));

                c_uc_w2s_strncpy(w2s_msg_str_1, pt_w2s_msg, ui4_index+1);
                c_uc_w2s_to_ps(w2s_msg_str_1,str_fmt,256);
                if(INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
                {
                    c_snprintf(str_tmp,256,str_fmt,(MLM_NAV_LANG_ENG == nav_get_mlm_lang_id()) ? "RF Cable" :
                                                   (MLM_NAV_LANG_FRE == nav_get_mlm_lang_id()) ? "Câble RF":"Cable RF");
                }
                else
                {
                    c_snprintf(str_tmp,256,str_fmt,"source device");
                }
                c_uc_ps_to_w2s(str_tmp,w2s_msg_str_2,256);
                INT32 i4_len = c_uc_w2s_strlen(w2s_msg_str_2);
                c_memset(w2s_msg_str_1,0,sizeof(w2s_msg_str_1));
                c_uc_w2s_strncat(w2s_msg_str_1, w2s_msg_str_2, i4_len + 1);
                c_uc_w2s_strncat(w2s_msg_str_1, L"\n", 1);
                c_uc_w2s_strncat(w2s_msg_str_1, pt_w2s_msg+ui4_index+1, c_uc_w2s_strlen(pt_w2s_msg+ui4_index+1));
                c_memset(w2s_msg_str_2,0,sizeof(w2s_msg_str_2));
            }
        } while(FALSE);
    #endif

    #if 0 // no need for Signal Acquire UI
        do {
            UTF16_T  *pw2s_start = &w2s_msg_str_1[0];
            UTF16_T  *pw2s_end = &w2s_msg_str_1[0] + c_uc_w2s_strlen(pw2s_start);

            UTF16_T  *pw2s_sub_text = L"ICON";
            SIZE_T   t_sub_size = c_uc_w2s_strlen(pw2s_sub_text);

            UTF16_T  *pw2s_dst = &w2s_msg_str_2[0];

            while (pw2s_start <= (pw2s_end - t_sub_size))
            {
                SIZE_T  t_cmp_offset = 0;
                while (t_cmp_offset < t_sub_size)
                {
                    if (*(pw2s_start + t_cmp_offset) == *(pw2s_sub_text + t_cmp_offset))
                    {
                        t_cmp_offset++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (t_cmp_offset == t_sub_size)
                {
                    c_uc_w2s_strncpy(pw2s_dst, L"%p", 2);
                    pw2s_dst += 2;
                }
                else
                {
                    t_cmp_offset = (t_cmp_offset == 0) ? 1 : t_cmp_offset;
                    c_uc_w2s_strncpy(pw2s_dst, pw2s_start, t_cmp_offset);
                    pw2s_dst += t_cmp_offset;
                }
                pw2s_start += t_cmp_offset;
            }

            if (pw2s_start < pw2s_end)
            {
                c_uc_w2s_strncat(pw2s_dst, pw2s_start, pw2s_end - pw2s_start);
            }

        } while(FALSE);
    #endif

        banner_hide_sidebar();

        c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));

        {
            t_custom_data.u.t_signal_acquire_init.w2s_title_str = (VOID*)w2s_title_str;
            t_custom_data.u.t_signal_acquire_init.w2s_msg_str = NULL;
            t_custom_data.u.t_signal_acquire_init.h_insert_img = h_g_input_icon;
        }

        TOAST_CONTROL_T*  pt_toast_control = NULL;

        i4_ret = a_toast_show(pt_view->h_toast_signal_acquire, &t_custom_data);

        do {
            UINT32 ui4_msg_len = 0;
            UINT32 ui4_index = 0;

            c_uc_w2s_strncpy(w2s_tts_content, w2s_title_str, 64);
//            c_uc_w2s_strncat(w2s_tts_content, L", ", 2);
//            c_uc_w2s_strncat(w2s_tts_content,
//                             MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_NO_SIGNAL_DESC2_TTS),
//                             512-c_uc_w2s_strlen(w2s_tts_content));

            ui4_msg_len = c_uc_w2s_strlen(w2s_tts_content);
            ui4_index = 0;

            while (ui4_index < ui4_msg_len)
            {
                if (w2s_tts_content[ui4_index] == '-')
                {
                    w2s_tts_content[ui4_index] = ' ';
                }
                ui4_index++;
            }

            pw2s_string = &w2s_tts_content[0];
        } while(FALSE);
    }
    else
    {
        i4_ret = NAVR_FAIL;
    }

    if (WDKR_OK == i4_ret)
    {
        e_g_toast_style = e_toast_style;
    }

#ifdef APP_TTS_SUPPORT
     a_app_tts_play(pw2s_string,c_uc_w2s_strlen(pw2s_string));
#endif

    if (b_oled == TRUE && !menu_custom_is_blank_screen())
    {
        _scrn_svr_view_blank_scrn_timer_start();
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      scrn_svr_view_move
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 scrn_svr_view_move(
                    SCRN_SVR_VIEW_T*            pt_view,
                    BOOL                        b_first_time,
                    BOOL                        b_repaint
                    )
{
    return NAVR_OK;
}

INT32 scrn_svr_view_hide_no_signal()
{
    return a_wdk_toast_hide(TRUE, NULL,&t_g_wdk_scrn_svr_middle);
}


/*-----------------------------------------------------------------------------
 * Name
 *      scrn_svr_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 scrn_svr_view_hide(
                    SCRN_SVR_VIEW_T*            pt_view,
                    TOAST_STYLE_T               e_toast_style
                    )
{
    INT32    i4_ret = NAVR_OK;
    DBG_INFO(("[%s %d] NAV_COMP_ID_BANNER(%d) visible = %d  active_component = %d,e_g_toast_style = %d\n",
        __FUNCTION__,__LINE__,
        NAV_COMP_ID_BANNER,
        nav_is_component_visible(NAV_COMP_ID_BANNER),
        nav_get_active_component(),
        e_g_toast_style));

    if (TOAST_STYLE_NO_SIGNAL_1 == e_g_toast_style)
    {
        i4_ret = a_toast_hide(pt_view->h_toast_no_signal);
    }
    else if (TOAST_STYLE_NO_SIGNAL_2 == e_g_toast_style)
    {
        i4_ret = a_toast_hide(pt_view->h_toast_no_signal_2);
    }
    else if (TOAST_STYLE_SIGNAL_ACQUIRE == e_g_toast_style)
    {
        i4_ret = a_toast_hide(pt_view->h_toast_signal_acquire);
    }
    else if (TOAST_STYLE_NO_SIGNAL == e_g_toast_style)
    {
        i4_ret = scrn_svr_view_hide_no_signal();
    }
    else if (TOAST_STYLE_CENTER_DIALOG== e_g_toast_style)
    {
        i4_ret = a_wdk_toast_hide(TRUE, NULL,&t_g_wdk_scrn_svr_av_status);
    }
    else if (TOAST_STYLE_MSG == e_g_toast_style)
    {
        if(b_tuner_setup_view_showing)
        {
            DBG_LOG_PRINT(("[tuner setup] %s %d \n",__FUNCTION__,__LINE__));
            b_tuner_setup_view_showing = FALSE;
            tuner_setup_warning_hide();
        }
        else
        {
            i4_ret = a_toast_hide(pt_view->h_toast_warning_view);
        }

    }
    else if (TOAST_STYLE_MSG_WITH_TITLE_CONTENT == e_g_toast_style)
    {
        i4_ret = a_toast_hide(pt_view->h_toast_warning_view_with_title);
    }

    NAV_LOG_ON_FAIL(i4_ret);
    e_g_toast_style = TOAST_STYLE_MAX_NUM;
    if (b_oled == TRUE)
    {
        if (menu_custom_get_blank_scrn_mode() == BLK_SCRN_OLED_NO_SIGNAL && !a_nav_is_signal_loss())
        {
            _scrn_svr_view_blank_scrn_timer_stop();
            menu_custom_unblank_screen(BTN_CURSOR_UP);
        }
    }
    return NAVR_OK;
}
INT32 scrn_svr_view_hide_signal_acquire(VOID)
{
    INT32    i4_ret = NAVR_OK;
    SCRN_SVR_VIEW_T* pt_view = t_g_pt_view;

    i4_ret = scrn_svr_view_hide(pt_view, TOAST_STYLE_SIGNAL_ACQUIRE);
    NAV_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

