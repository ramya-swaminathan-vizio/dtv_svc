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
//#ifdef APP_LINK_MODE_SUPPORT
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

#include "mmp/a_mmp.h"
#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_img.h"
#include "res/revolt/revolt_warnings_mlm.h"

#include "link_mode.h"
#include "nav/input_src/a_input_src.h"
#include "nav/long_press/long_press.h"
#include "nav/tuner_setup/tuner_setup_view.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/updater/nav_updater.h"


#ifdef APP_2K12_RETAIL_DEMO_MODE
#include "menu2/a_menu.h"
//#include "wizard/wzd_util.h"
//#include "wizard/a_wzd.h"
#include "wizard_anim/wzd.h"
#include "wizard_anim/a_wzd.h"
#endif

#include "u_common.h"
#include "u_wgl_common.h"
#include "c_wgl.h"
#include "u_wgl.h"
#include "c_wgl_image.h"
#include "c_handle.h"
#include "c_os.h"


#include "msgconvert/msgconvert.h"
#include "res/app_util/model/model.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/msgconvert/msgconvert_custom.h"

#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/nav/banner2/banner_rc.h"
#include "nav/power/a_nav_power.h"
#include "wdk/widget/wdk_widget.h"

#include "res/menu2/menu_custom.h"

#include "app_util/toast_widget/a_toast.h"
#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#endif

#include "nav/cec2/nav_cec.h"
#include "c_cecm.h"
#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define  NAV_LINK_WARNNING_AUTO_HIDE_TIMER_DURATION           5000
NAV_LINK_MODE_STATUS_T LINK_STATUS;
static NAV_LINK_INFO_T t_g_nav_link_info;
ISL_REC_T  t_isl_rec;
#ifdef APP_TTS_SUPPORT
#define LINK_TTS_WARNINGS_TEXT(key)   MLM_WARNINGS_TEXT(0, (key))  /* 0:english   */
#endif
/*
    when long input call softap,
    only link key to exit the pair process
*/
INT32 set_state(INT32 state,UINT8 input_src_idx,DEVICE_TYPE_T type){
    LINK_STATUS = state;
    t_isl_rec.ui1_id = input_src_idx;
    t_isl_rec.t_avc_info.e_video_type = type;
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_link_mode_deinit(VOID);

#if 0
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_link_mode_set_focus
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
static INT32 _nav_link_mode_set_focus(VOID)
{
    //by sbx_12 0220 _1
    NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;
    INT32 i4_ret;

    // Let's focus on the frame
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
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_link_mode_init
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
static INT32 _nav_link_mode_init(NAV_CONTEXT_T* pt_ctx)
{
    /*Init timer and link status*/
    LINK_STATUS = NAV_LINK_MODE_INITIAL;

    NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;
    INT32           i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->h_update_ctrl_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;
    pt_this->twice_key_down = FALSE;
    pt_this->b_is_view_init      = FALSE;
    pt_this->ui4_timeout  = NAV_LINK_WARNNING_AUTO_HIDE_TIMER_DURATION;

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    /*init wdk*/
    TOAST_INIT_PARAM_T t_toast_init;

    c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));

    t_toast_init.e_toast_style                              = TOAST_STYLE_MSG;
    t_toast_init.h_canvas                                   = pt_ctx->t_gui_res.h_canvas;
    t_toast_init.t_custom_setting.u.t_msg_init.e_msg_type   = TOAST_MSG_TYPE_WITH_WARNING_ICON;
    //t_toast_init.t_custom_setting.u.t_msg_init.w2s_msg_str  = WGL_PACK (MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_33));

    if(pt_ctx->t_gui_res.h_canvas == NULL_HANDLE){
        DBG_LOG_PRINT(("h_canvas == NULL FI:%s,LN:%d\n",__FILE__,__LINE__));
    }else{
        DBG_LOG_PRINT(("h_canvas !=NULL file:%s,line:%d\n",__FILE__,__LINE__));
    }

    a_toast_create(&t_toast_init, &pt_this->h_toast_view);

    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    //a_wdk_toast_init (pt_this->h_frame,&pv_param,&t_g_wdk_view);
    return  NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_link_mode_deinit
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
static INT32 _nav_link_mode_deinit(VOID)
{
    //by sbx_12 0218 _1
    LINK_STATUS = NAV_LINK_MODE_INITIAL;
    NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;


    if (c_handle_valid(pt_this->h_update_ctrl_timer) == TRUE) {
        c_timer_delete(pt_this->h_update_ctrl_timer);
    }

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        DBG_LOG_PRINT(("[%s]++,line:%d timer is deleted \n",__FUNCTION__,__LINE__));
        c_timer_delete(pt_this->h_hide_timer);
    }

    // deinit the view
    if (pt_this->b_is_view_init == TRUE)
    {
        pt_this->b_is_view_init = FALSE;
    }

    pt_this->h_update_ctrl_timer = NULL_HANDLE;
    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;
    pt_this->twice_key_down = FALSE;
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_link_info_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_link_info_stop_timer(
                    NAV_LINK_INFO_T*                pt_this
                    )
{
    //by sbx_12 0218 _1
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
 * Name
 *      _nav_link_info_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_link_info_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    //by sbx_12 0218 _1
    if (LINK_STATUS == NAV_LINK_MODE_WARNING){
        nav_hide_component(NAV_COMP_ID_LINK);

        DBG_LOG_PRINT(("sbx call a_wdk_toast_hide \n"));
        NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;
        _nav_link_info_stop_timer(pt_this);

        a_toast_hide(pt_this->h_toast_view);

        DBG_LOG_PRINT(("\n after 5s' no 2rd key down, reset link status\n"));
        LINK_STATUS = NAV_LINK_MODE_INITIAL;
        /* Return control. */
        nav_return_activation(NAV_COMP_ID_LINK);
        pt_this->b_is_on =  FALSE;
        pt_this->twice_key_down = FALSE;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_link_info_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_link_info_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
     nav_request_context_switch(_nav_link_info_timeout_to_hide, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_link_info_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_link_info_reset_timer(
                    NAV_LINK_INFO_T*                 pt_this
                    )
{
    INT32 i4_ret;

    if(pt_this == NULL)
    {
        pt_this = & t_g_nav_link_info;
    }

    _nav_link_info_stop_timer(pt_this);
    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    pt_this->ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _nav_link_info_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start revolt_info::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_link_mode_is_key_handler
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
static BOOL _nav_link_mode_is_key_handler(
                    NAV_CONTEXT_T*  pt_ctx,
                    UINT32          ui4_key_code
                    )
{
#if 0
    //by sbx_12 0218 _1
    if (BTN_LINK == ui4_key_code)
    {
        DBG_LOG_PRINT(("sbx _nav_link_mode_is_key_handler ui4_key_code %x,FUC:%s,LN:%d.\n", ui4_key_code,__FILE__,__LINE__));
        return TRUE;
    }
#endif
    if (BTN_LINK == ui4_key_code)
    {
        DBG_LOG_PRINT(("nav_link_mode_is_key_handler link_state:%d,FUC:%s,LN:%d.\n", LINK_STATUS,__FILE__,__LINE__));
        if ((NAV_LINK_MODE_INITIAL == LINK_STATUS) || (NAV_LINK_MODE_SOFTAP == LINK_STATUS))
        {
            UINT16  ui2_status    = 0;
            UINT8   ui1_state   = 0;
            UINT8   ui1_page_idx  = 0;

            /*when OOBE,link key ignore*/
            if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK)
            {
                ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
                ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);
            }
            DBG_LOG_PRINT(("link key get oobe [state=%d ] [page= %d],link_status:%d LN:%d,\n\r",(int)ui1_state,(int)ui1_page_idx,LINK_STATUS,__LINE__));
            if (WZD_STATE_RESUME_C4TV == ui1_state)
            {
                /*in OOBE but not demo mode*/
                if ((ui1_page_idx >= WZD_PAGE_INDEX_C4TV_START_OOBE && ui1_page_idx <= WZD_PAGE_INDEX_C4TV_END )&& ui1_page_idx != WZD_PAGE_INDEX_C4TV_STORE_DEMO)
                {
                    DBG_LOG_PRINT(("sbx ignore link key when OOBE not store demo page LN:%d\r\n",__LINE__));
                    return FALSE;
                }
            }

            /*if tuner setup is active,link key not action*/
            if(nav_is_channel_scan_active())
            {
                DBG_LOG_PRINT(("sbx tuer scan is on,ignore link key\r\n"));
                return FALSE;
            }


            /*save the input src idx*/
            CHAR       s_disp_name[33] = {0};
            UINT8      ui1_input_id = 0;
            INT32      i4_ret;

            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
            i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
            DBG_LOG_PRINT(("sbx get input_src idx:%d FUC:%s,LN:%d.\n",t_isl_rec.ui1_id,__FILE__,__LINE__));
            if (i4_ret != 0)
            {
                DBG_LOG_PRINT(("get input_src idx err FUC:%s,LN:%d.\n",__FILE__,__LINE__));
            }

            /*set focus of link mode*/
            //_nav_link_mode_set_focus();
            nav_hide_components(COMP_EXEC_SET_LINK);
            nav_set_component_visible(NAV_COMP_ID_LINK);

            NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;
            pt_this->b_is_on = TRUE;
            pt_this->twice_key_down = FALSE;

            nav_link_info_reset_timer(pt_this);

            TOAST_CUSTOMIZATION_DATA_T  t_custom_setting;
            c_memset(&t_custom_setting, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));
            t_custom_setting.u.t_msg_init.w2s_msg_str = WGL_PACK (MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_33));
            a_toast_show(pt_this->h_toast_view, &t_custom_setting);
#ifdef APP_TTS_SUPPORT
            UTF16_T         w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,LINK_TTS_WARNINGS_TEXT(MLM_WARNINGS_KEY_WARNING_33));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif
            LINK_STATUS = NAV_LINK_MODE_WARNING;
            return FALSE;
        }
        else if (NAV_LINK_MODE_WARNING == LINK_STATUS)
        {
            DBG_LOG_PRINT(("sbx link key is_key_handler link_status:%d LN:%d\n\r",LINK_STATUS,__LINE__));
            NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;
            pt_this->twice_key_down = TRUE;
            return TRUE;
        }
        else
        {
            DBG_LOG_PRINT(("sbx link key is_key_handler ignore key link_status:%d\n\r",LINK_STATUS));
            return FALSE;
        }
    }
    return FALSE;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_link_mode_activate
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
static INT32 _nav_link_mode_activate(
                    NAV_CONTEXT_T*  pt_ctx,
                    UINT32          ui4_key_code)
{
    NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;
    pt_this->b_is_on = TRUE;
    pt_this->twice_key_down = FALSE;
    DBG_LOG_PRINT(("sbx link_mode activate link_status:%d FUC:%s,LN:%d.\n",LINK_STATUS,__FILE__,__LINE__));
    if (NAV_LINK_MODE_WARNING == LINK_STATUS)// second key down
    {
        set_link_state(LINK_ON,t_isl_rec.ui1_id,t_isl_rec.t_avc_info.e_video_type);
        /*change link status*/
        LINK_STATUS = NAV_LINK_MODE_SOFTAP;

        /*hide WARNING notification when 2rd key down in 5s after 1st*/
        NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;
        _nav_link_info_stop_timer(pt_this);

        a_toast_hide(pt_this->h_toast_view);

        /*launch softAP*/
#ifdef APP_C4TV_SUPPORT
        a_wzd_resume_c4tv(WZD_STATE_RESUME_C4TV,WZD_PAGE_INDEX_C4TV_LINK_START);
#endif
        return NAVR_OK;
    }
#if 0
    else if (NAV_LINK_MODE_SOFTAP == LINK_STATUS)
    {
        /*change link status*/
        LINK_STATUS = NAV_LINK_MODE_INITIAL;
        /*reload current TV source*/
        DBG_LOG_PRINT(("now load previous source indx:%d FUC:%s,LN:%d.\r\n",t_isl_rec.ui1_id,__FILE__,__LINE__));
        a_tv_set_input_src_id(TV_WIN_ID_MAIN,t_isl_rec.ui1_id);
        a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
                           (VOID*)(UINT32)TV_WIN_ID_MAIN,
                           (VOID*)(UINT32)t_isl_rec.ui1_id);

        /*end Pairing*/
#ifdef APP_C4TV_SUPPORT
        a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
        if (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
        {
            a_nav_stop_ipts_src_c4tv_apron_custom_nfy_from_link(TRUE);
        }
        a_wzd_stop_c4tv(a_nav_ipts_src_c4tv_apron_custom_nfy);
        DBG_LOG_PRINT(("after exit softap set state to cast EXIT FUC:%s,LN:%d.\r\n",__FILE__,__LINE__));
        a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, ui1_page_idx));
#endif

        /* Return control. */
        nav_hide_component(NAV_COMP_ID_LINK);
        nav_return_activation(NAV_COMP_ID_LINK);
        pt_this->b_is_on = FALSE;

        /*stop tuner scan if tuner active*/
        if(nav_is_channel_scan_active())
        {
            DBG_LOG_PRINT(("exit OOBE and stop tuner\r\n"));
            a_tuner_setup_stop_scan(NULL, 0);
        }

        return NAVR_OK;
    }
#endif
    return NAVR_OK;
}




/*-----------------------------------------------------------------------------
 * Name
 *      _nav_link_mode_inactivate
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
static INT32 _nav_link_mode_inactivate(NAV_CONTEXT_T*   pt_ctx)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_link_mode_hide
 * Description
 *      Hide retail mode component.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Succes
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_link_mode_hide(VOID)
{
    /*hide WARNING notification when receive other key*/
    NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;
    pt_this->b_is_on = FALSE;
    _nav_link_info_stop_timer(pt_this);

    a_toast_hide(pt_this->h_toast_view);

    /*reset link status*/
    DBG_LOG_PRINT(("sbx++++ _nav_link_mode_hide LINK_STATUS:%d,pt_this->twice_key_down:%d LINE:%d\r\n",LINK_STATUS,pt_this->twice_key_down,__LINE__));
    if (FALSE == pt_this->twice_key_down)
    {
        if (NAV_LINK_MODE_WARNING == LINK_STATUS)
        {
            LINK_STATUS = NAV_LINK_MODE_INITIAL;
        }

        /* Return control. */
        nav_return_activation(NAV_COMP_ID_LINK);
    }
    return NAVR_OK;
}

BOOL nav_link_mode_is_on(VOID)
{
   NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;

   return pt_this->b_is_on;
}
VOID nav_link_mode_ui_hide(
    VOID*                               pv_ui2_id,
    VOID*                               pv_unused1,
    VOID*                               pv_unused2)
{
    if (NAV_LINK_MODE_WARNING == LINK_STATUS)
    {
        /*hide WARNING notification when receive other key*/
        NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;
        pt_this->b_is_on = FALSE;
        _nav_link_info_stop_timer(pt_this);

        a_toast_hide(pt_this->h_toast_view);

        /*reset link status*/
        DBG_LOG_PRINT(("sbx nav_link_mode_ui_hide LINK_STATUS:%d,LINE:%d\r\n",LINK_STATUS,__LINE__));

        //LINK_STATUS = NAV_LINK_MODE_INITIAL;


        /* Return control. */
        nav_return_activation(NAV_COMP_ID_LINK);
    }
}
VOID a_nav_link_mode_ui_hide(VOID)
{
    nav_request_context_switch(nav_link_mode_ui_hide,
                               NULL,
                               NULL,
                               NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_link_mode_handle_msg
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
static INT32 _nav_link_mode_handle_msg(
                    NAV_CONTEXT_T*  pt_ctx,
                    NAV_UI_MSG_T*   pt_ui_msg,
                    VOID*           pv_arg1
                    )
{
    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_POWER_OFF:
        {
            UINT16     ui2_status  = APP_CFG_WZD_STATUS_INIT;
            UINT8      ui1_state   = 0;
            UINT8      ui1_page_index = 0;
            BOOL       b_is_factory_reset = FALSE;
	    BOOL	   b_is_oobe_update_complete = FALSE;

            if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK)
            {
                ui1_page_index  = WZD_UTIL_GET_STATUS_IDX  ( ui2_status );
                ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
                b_is_factory_reset = menu_get_factory_reset_status();
		b_is_oobe_update_complete = a_nav_updater_uli_get_oobe_update_finished_complete();

#ifdef APP_C4TV_SUPPORT
                if ((WZD_STATE_RESUME_C4TV == ui1_state) && (NAV_LINK_MODE_SOFTAP == LINK_STATUS) && (!b_is_factory_reset))
                {
			if(!b_is_oobe_update_complete)
			{
				LINK_STATUS = NAV_LINK_MODE_INITIAL;
				DBG_LOG_PRINT(("[LINK_MODE] when in link mode OOBE && not factory reset,set state to end when power off\n"));

				/*reload previous TV source before power off*/
				DBG_LOG_PRINT(("reload previous source before power offindx:%d FUC:%s,LN:%d.\r\n",t_isl_rec.ui1_id,__FILE__,__LINE__));
				a_tv_set_input_src_id(TV_WIN_ID_MAIN,t_isl_rec.ui1_id);
				a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
				(VOID*)(UINT32)TV_WIN_ID_MAIN,
				(VOID*)(UINT32)t_isl_rec.ui1_id);
				/*Exit Cast*/
				a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
				/*if (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)   fix DTV00909362
				{
					a_nav_stop_ipts_src_c4tv_apron_custom_nfy_from_link(TRUE);
				}*/
				a_wzd_stop_c4tv(a_nav_ipts_src_c4tv_apron_custom_nfy);
				a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, ui1_page_index));

				if (t_isl_rec.t_avc_info.e_video_type != DEV_VTRL_CAST)
				{
					DBG_LOG_PRINT(("a_c4tv_apron_resume_cast\r\n"));
					a_c4tv_apron_resume_cast();
					#ifdef SYS_C4TV_SUPPORT
					a_cfg_set_cast_tv_status(APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE);
					#endif
				}
			}
                }
#endif
            }
            NAV_LINK_INFO_T* pt_this = &t_g_nav_link_info;
            pt_this->b_is_on = FALSE;
            pt_this->twice_key_down = FALSE;
	        a_nav_updater_uli_set_oobe_update_finished_complete(FALSE);
            break;
        }
        default:
            break;
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_link_mode_set_mode
 * Description: Set link mode status
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_link_mode_set_mode(NAV_LINK_MODE_STATUS_T e_mode)
{
    DBG_LOG_PRINT(("[LINK_MODE] a_nav_link_mode_set_mode: %d\n", e_mode));

    LINK_STATUS = e_mode;
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_link_mode_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_link_mode_register()
{
    NAV_COMP_T      t_comp;
    INT32           i4_ret = NAVR_OK;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    t_comp.pf_init           = _nav_link_mode_init;
    t_comp.pf_deinit         = _nav_link_mode_deinit;
    t_comp.pf_is_key_handler = _nav_link_mode_is_key_handler;
    t_comp.pf_activate       = _nav_link_mode_activate;
    t_comp.pf_inactivate     = _nav_link_mode_inactivate;
    t_comp.pf_hide           = _nav_link_mode_hide;
    t_comp.pf_handle_msg     = _nav_link_mode_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_LINK,
                                    &t_comp,
                                    COMP_EXEC_SET_LINK);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    return NAVR_OK;
}


//#endif /*APP_LINK_MODE_SUPPORT*/

