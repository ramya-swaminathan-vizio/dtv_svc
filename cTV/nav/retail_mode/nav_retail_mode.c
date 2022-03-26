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
#ifdef APP_RETAIL_MODE_SUPPORT
//#define RETAIL_RCOVERY_DEBUG

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
#include "nav/revolt_misc/revolt_misc_view.h"

#include "nav/link_mode/link_mode.h"

#ifdef APP_2K12_RETAIL_DEMO_MODE
#include "menu2/a_menu.h"
#include "wizard/wzd_util.h"
#include "wizard_anim/a_wzd.h"
#endif
#include "wdk/vkb/vkb.h"

#include "msgconvert/msgconvert.h"
#include "res/app_util/model/model.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/msgconvert/msgconvert_custom.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "res/app_util/a_custom_log.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/nav/banner2/banner_rc.h"
#include "nav/power/a_nav_power.h"

#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "nav/input_src/a_input_src.h"
#include "nav/c4tv_apron/c4tv_apron.h"

#include "wdk/a_wdk.h"

#include "app_util/toast_widget/a_toast.h"

#include "nav_retail_mode.h"
#include "a_nav_retail_mode.h"

#include "registry/a_registry.h"

#include "rest/a_rest_event.h"
#include "rest/a_rest.h"
#include "bluetooth_gatt/bluetooth_gattc.h"
#include "res/menu2/menu_custom.h"
#include "rest/a_rest_api.h"
#include "nav/tuner_setup/tuner_setup_view.h"
#include "nav/input_src/input_src.h"
#include "nav/vol_ctrl/a_vol_ctrl.h"
#include "nav/ulpk/a_ulpk.h"
#include "nav/ulpk/ulpk.h"
#include "nav/updater/a_nav_updater.h"
#include "nav/updater/nav_updater.h"

#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif

#ifdef SYS_MTKTVAPI_SUPPORT
#include "app_util/mtktvapi/mtktvapi_config_type.h"
#include "app_util/mtktvapi/a_mtktvapi_config.h"
#endif
#include "nav/banner2/a_banner.h"
#include "menu2/menu.h"

#include "res/nav/nav_dbg.h"


#include "mi_common.h"
#include "mi_mm.h"
#include "mi_aout.h"
#include "mi_disp.h"
#include "mi_osd.h"
#include "mi_os.h"
#include "mi_sys.h"
#include "mi_video.h"

#include "directfb.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define NAV_RETAIL_MODE_TEXT(_txt)  ((UTF16_T*)L##_txt)

#define NAV_RETAIL_MODE_ENABLE_MSG  (0)
#define NAV_RETAIL_MODE_DISABLE_MSG (1)
#define DLG_HIDE_AFTER_90_SECOND    (90)

#define NAV_RETAIL_MODE_DFB_LAYER_0 (0)
#define NAV_RETAIL_MODE_4K_OVERLAY_W (3840)
#define NAV_RETAIL_MODE_4K_OVERLAY_H (2160)

typedef struct __NAV_RETAIL_MODE_T
{
    HANDLE_T                    h_canvas;

    HANDLE_T                    h_resume_dlg;
    HANDLE_T                    h_pause_dlg;
    HANDLE_T                    h_info_dlg;
    HANDLE_T                    h_pause_timer;
    HANDLE_T                    h_overlay_recheck_timer;
    BOOL                        b_is_pause_timer_start;

    /*RETAIL_MODE_LAUNCH_INFO_T*/
    NAV_RETAIL_MODE_RESUME_FROM_T   e_resume_from_app;
    RETAIL_MODE_LAUNCH_OSD_TYPE_T   e_launch_osd_type;
    UINT16                          ui2_count;
    /*  RETAIL_MODE_EXIT_INFO_T */
    NAV_RETAIL_MODE_RESUME_FROM_T   e_exit_from_app;


    NAV_RETAIL_MODE_STATUS_T    e_status;
    NAV_RETAIL_MODE_POPUP_DLG_T e_popup_dlg;
    RETAIL_MODE_RUNNING_TYPE_T  e_running_type;

    /* picture mode acfg notify callback */
    UINT16                      ui2_cfg_nfy_id_pic_mode;  /* The ACFG picture mode notify id */
    UINT16                      ui2_icl_nfy_id_pic_mode;  /* The icl picture mode notify id */
    HANDLE_T                    h_cfg_nfy_timer;
    BOOL                        b_is_ignore_pic_nfy;     /* is ignore picture mode notify */
    BOOL                        b_is_cfg_nfy_timer_start;

    /* iom to check key*/
    HANDLE_T                    h_iom;

    /*cec to check hdmi*/
    HANDLE_T                    h_cecm_svc_svc;

    /* 3rd app status notify callback */
    UINT16                      ui2_yahoo_status_nfy;
    UINT32                      ui4_yahoo_status;
    UINT32                      ui4_app_status;


    /* record input and volume status */
    BOOL                        b_rec_mute;
    INT16                       i2_rec_vol;
    //enum                          input source;
    HANDLE_T 					h_dialag_hide_timer;
} _NAV_RETAIL_MODE_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _NAV_RETAIL_MODE_T   t_g_retail_mode;
static BOOL                 b_g_is_demo_flash_playing = FALSE;

static NAV_RETAILMODE_ACTIVE_APP_T  e_active_app  = ACTIVE_APP_UNKNOWN;

static BOOL     b_ir_exit_key = FALSE;
static BOOL     b_2th_press_play_pause_key = FALSE;

static BOOL     b_is_skip_chg_inp_src = FALSE;
static BOOL     b_last_input_signal_locked = FALSE;
BOOL b_g_oobe_retail_mode = FALSE; /*demo mode in oobe then power off.*/
BOOL b_g_oobe_retail_pause_by_app = FALSE; /*demo mode in oobe then paused by other apps or compements.*/
static UINT32 ui4_g_overlay_demo_service_tick = 0;
static UINT8  uii_last_video_demo_input_src = 0xF0;//This value is to declare the last input before video demo mode
static BOOL   b_g_retail_mode_need_recheck_hdmi_plug_in_out = FALSE;//To declare the hdmi plug in/out status,only for video demo mode
static BOOL   b_g_oobe_retail_mute_before_power_off = FALSE; /*Mute during demo mode will need keep mute after DC on.*/
static BOOL   b1_hide_resume_dlg_timer = FALSE;
static UINT16 ui2_backup_demo_idx = 0;
static UINT8  ui1_cur_hdmi_port = 0x0F;
static UINT8  ui1_chg_to_signal_input = 0x0F;
static BOOL   b1_first_enter_flag = FALSE;
static BOOL b_force_enable_store_mode = 0;

static BOOL b_4k_overlay = FALSE;
static DFBDisplayLayerConfig t_dfb_config_layer0;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_deinit(VOID);

/* picture mode func */
static INT32 _nav_retail_mode_init_pic_mode(VOID);
static INT32 _nav_retail_mode_reset_pic_mode(VOID);

/* pause dialog related function */
static INT32 _nav_retail_pause_dlg_init(VOID);
static INT32 _nav_retail_pause_dlg_show(VOID);
static INT32 _nav_retail_pause_dlg_hide(VOID);
static VOID  _nav_retail_pause_dlg_pause_fct(VOID);
static VOID  _nav_retail_pause_dlg_exit_fct(VOID);
static INT32 _nav_retail_pause_dlg_default_msg_proc(
                                            HANDLE_T            h_widget,
                                            UINT32              ui4_msg,
                                            VOID*               pv_param1,
                                            VOID*               pv_param2
                                            );

static VOID  _nav_retail_mode_exit_demo_mode(VOID);
static INT32 _nav_retail_mode_check_logo(VOID);

/* resume dialog related function */
static INT32 _nav_retail_resume_dlg_init(VOID);
static INT32 _nav_retail_resume_dlg_show(VOID);
static INT32 _nav_retail_resume_dlg_hide(VOID);
static VOID  _nav_retail_resume_dlg_resume_fct(VOID);
static VOID  _nav_retail_resume_dlg_exit_fct(VOID);
static INT32 _nav_retail_resume_dlg_default_msg_proc(
                                            HANDLE_T            h_widget,
                                            UINT32              ui4_msg,
                                            VOID*               pv_param1,
                                            VOID*               pv_param2
                                            );
static VOID  _nav_retail_resume_dlg_info_btn_fct(VOID);
static INT32 _nav_retail_info_dlg_hide(VOID);

/* warning dialog related function  */


/* dialog control function */

static INT32 _nav_retail_mode_dialog_deinit(HANDLE_T h_dlg);
static INT32 _nav_retail_mode_dialog_hide(HANDLE_T h_dlg);

static VOID _nav_retail_mode_start_pause_timer(VOID);
static VOID _nav_retail_mode_start_cfg_nfy_timer(VOID);


static VOID _nav_retail_mode_stop_pause_timer(VOID);
static VOID _nav_retail_mode_stop_cfg_nfy_timer(VOID);
static VOID _nav_retail_mode_cfg_change_timer_cb( HANDLE_T h_timer,VOID* pv_tag);

static VOID _nav_retail_pause_restart_demo_mode(
                                            VOID*           pv_tag1,
                                            VOID*           pv_tag2,
                                            VOID*           pv_tag3
                                            );


/*status*/
//static NAV_RETAIL_MODE_STATUS_T _nav_retail_mode_check_status(VOID);
//static NAV_RETAIL_MODE_STATUS_T _nav_retail_mode_get_status();
static INT32 _nav_retail_mode_set_status(NAV_RETAIL_MODE_STATUS_T e_status);
//static INT32 _nav_retail_mode_update_status(VOID);


/*running type*/
static RETAIL_MODE_RUNNING_TYPE_T _nav_retail_mode_check_running_type(VOID);
static RETAIL_MODE_RUNNING_TYPE_T _nav_retail_mode_get_running_type();
static INT32 _nav_retail_mode_set_running_type(RETAIL_MODE_RUNNING_TYPE_T e_type);
static INT32 _nav_retail_mode_update_running_type(VOID);


static INT32 _nav_retail_mode_start(RETAIL_MODE_PARAM_T* pt_param);
static INT32 _nav_retail_mode_exit(VOID);

/*play*/
static INT32 _nav_retail_mode_start_play(VOID);
static INT32 _nav_retail_mode_stop_play(VOID);
static INT32 _nav_retail_mode_stop_play_by_power_off();

static INT32 _nav_retail_mode_start_overlay(VOID);
static INT32 _nav_retail_mode_start_overlay_setup_env(VOID);
static INT32 _nav_retail_mode_stop_overlay(VOID);
static INT32 _nav_retail_mode_stop_overlay_setup_env(VOID);

static INT32 _nav_retail_mode_start_video(VOID);
static INT32 _nav_retail_mode_start_video_setup_env(VOID);
static INT32 _nav_retail_mode_stop_video(VOID);
static INT32 _nav_retail_mode_stop_video_setup_env(VOID);

static INT32 _nav_retail_mode_start_internal_video(VOID);
static INT32 _nav_retail_mode_start_internal_video_setup_env(VOID);
static INT32 _nav_retail_mode_stop_internal_video(VOID);
static INT32 _nav_retail_mode_stop_internal_video_setup_env(VOID);

/*other*/
static INT32 _nav_retail_mode_stop_timer(VOID);

static INT32 _nav_retail_mode_go_pause(VOID);
static INT32 _nav_retail_mode_go_pause_setup(VOID);
static INT32 _nav_retail_mode_go_pause_setup_env(VOID);

static INT32 _nav_retail_mode_go_running(VOID);
static INT32 _nav_retail_mode_go_play_setup(VOID);
static INT32 _nav_retail_mode_go_play_setup_env(VOID);

static INT32 _nav_retail_mode_exit_hide(VOID);
static INT32 _nav_retail_mode_exit_setup_env(VOID);

static INT32 _nav_retail_mode_get_dfb_layer_config(INT32 layerId, DFBDisplayLayerConfig* pLayerConfig);
static INT32 _nav_retail_mode_set_dfb_layer_config(INT32 layerId, DFBDisplayLayerConfig* pLayerConfig);


/*wzd*/
static INT32 _nav_retail_mode_recover_wzd_stat(VOID);
static INT32 _nav_retail_mode_update_volume(VOID);
static VOID _nav_retail_mode_cec_clear_element(VOID);
static VOID _nav_ratail_mode_cec_save_video_mode_element(VOID);

static INT32 _is_need_change_hdmi_port(UINT8 *switch_hdmi_port);
static INT32 _retail_mode_detect_video_thread(VOID);
#ifdef RETAIL_RCOVERY_DEBUG
static INT32 _retail_mode_recovery_test_thread(VOID);
#endif
extern INT32 nav_view_set_focus(VOID);
extern INT32 cmd_convert_send_cmd(CHAR* ps_cmd);
extern VOID a_nav_retail_mode_clean_usb_device(VOID);
extern BOOL a_is_oled_compensation_support();


/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
NAV_RETAIL_MODE_STATUS_T _nav_retail_mode_get_status(VOID)
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] get status: %d \r\n",  pt_this->e_status));

    return pt_this->e_status;
}

static INT32 _nav_retail_mode_set_status(NAV_RETAIL_MODE_STATUS_T e_status)
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;
    if (pt_this->e_status == e_status)
    {
        return NAVR_OK;
    }

    DBG_LOG_PRINT(("[RETAIL MODE] set status: %d \r\n", e_status));
    pt_this->e_status = e_status;
    return NAVR_OK;
}

static RETAIL_MODE_RUNNING_TYPE_T _nav_retail_mode_get_running_type(VOID)
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    DBG_LOG_PRINT(("[RETAIL MODE] get running type: %d \r\n", pt_this->e_running_type));

    return pt_this->e_running_type;
}

static INT32 _nav_retail_mode_set_running_type(RETAIL_MODE_RUNNING_TYPE_T e_type)
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    if (pt_this->e_running_type == e_type)
    {
        return NAVR_OK;
    }

    if(e_type == RETAIL_MODE_TYPE_OVERLAY)
    {
        ui4_g_overlay_demo_service_tick = c_os_get_sys_tick();
    }

    DBG_INFO(("[RETAIL MODE] set running type: %d \r\n", e_type));
    pt_this->e_running_type = e_type;
    return NAVR_OK;
}

static INT32 _nav_retail_mode_exit_hide(VOID)
{
    INT32                   i4_ret = NAVR_OK;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    if (pt_this->e_popup_dlg == NAV_RETAIL_MODE_POPUP_PAUSE_DLG)
    {
        i4_ret = _nav_retail_pause_dlg_hide();
        NAV_LOG_ON_FAIL(i4_ret);
    }

    if (pt_this->e_popup_dlg == NAV_RETAIL_MODE_POPUP_RESUME_DLG)
    {
        i4_ret = _nav_retail_resume_dlg_hide();
        NAV_LOG_ON_FAIL(i4_ret);
    }

    if (pt_this->e_popup_dlg == NAV_RETAIL_MODE_POPUP_INFO_DLG)
    {
        i4_ret = _nav_retail_info_dlg_hide();
        NAV_LOG_ON_FAIL(i4_ret);
    }

    if ( (pt_this->e_popup_dlg == NAV_RETAIL_MODE_POPUP_LAUNCHING_DLG)
       ||(retail_mode_view_is_on()) )
    {
        i4_ret = retail_mode_view_timer_stop();
        NAV_LOG_ON_FAIL(i4_ret);

        i4_ret = retail_mode_view_hide();
        NAV_LOG_ON_FAIL(i4_ret);
    }

    if (pt_this->e_popup_dlg == NAV_RETAIL_MODE_POPUP_WARNING_DLG)
    {
        //hide warning osd
    }

    if (FALSE == retail_mode_view_logo_is_show())
    {
        i4_ret = retail_mode_view_logo_hide();
        NAV_LOG_ON_FAIL(i4_ret);
    }

    return NAVR_OK;
}

static INT32 _nav_retail_mode_exit_setup_env(VOID)
{
    INT32                   i4_ret = NAVR_OK;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    pt_this->b_is_ignore_pic_nfy = TRUE;
    pt_this->ui4_yahoo_status = YAHOO_STATUS_HIDE;
    pt_this->ui4_app_status = NW_APP_STATUS_HIDE;

    pt_this->e_resume_from_app  = NAV_RETAIL_MODE_RESUME_FROM_NULL;
    pt_this->e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;

    if ((pt_this->e_resume_from_app == NAV_RETAIL_MODE_RESUME_FROM_POWER)&&(_nav_retail_mode_get_running_type()!=RETAIL_MODE_TYPE_UNKNOW))
    {
        i4_ret = _nav_retail_mode_reset_pic_mode();
        NAV_CHK_FAIL(i4_ret);
    }

  #ifdef SYS_C4TV_SUPPORT
    {
        UINT8 ui1_cast_tv_status = 0;
        ISL_REC_T   t_isl_rec = {0};
        TV_WIN_ID_T e_focus_win = TV_WIN_ID_MAIN;
        a_cfg_get_cast_tv_status(&ui1_cast_tv_status);
        nav_get_focus_id(&e_focus_win);
        nav_get_isl_rec(e_focus_win, &t_isl_rec);
        DBG_INFO(("<vol view> %s,%d,type:%d\n\r",__FILE__,__LINE__,t_isl_rec.e_src_type ));
        if((ui1_cast_tv_status == 1)&&(t_isl_rec.e_src_type != INP_SRC_TYPE_VTRL))
        {
            a_cfg_set_cast_tv_status(APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE);
        }
    }
  #endif

    if (FALSE == a_wzd_is_oobe_mode())
    {
      a_amb_enable_system_key(TRUE);
    }

    /* enable screen saver */
    a_scrn_svr_set_enable(TRUE);

    /* enable BT */
    //a_bluetooth_gattc_force_stop_scan(FALSE);
    /* enable softAP */
    rest_start_softap_ex();

    return NAVR_OK;
}

static INT32 _nav_retail_mode_get_dfb_layer_config(INT32 layerId, DFBDisplayLayerConfig* pLayerConfig)
{
    if (NULL == pLayerConfig)
    {
        DBG_ERROR(("[RETAIL MODE]%s, pLayerConfig should not be NULL\n", __FUNCTION__));
        return NAVR_FAIL;
    }

    DFBResult ret;
    ret = DirectFBInit(NULL, NULL);
    if (ret)
    {
        DBG_ERROR(("[RETAIL MODE]%s, failed to init dfb\n", __FUNCTION__));
        return NAVR_FAIL;
    }

    IDirectFB* pDfb = NULL;
    /* Create the super interface. */
    ret = DirectFBCreate(&pDfb);
    if (ret || NULL == pDfb)
    {
        DBG_ERROR(("[RETAIL MODE]%s, failed to create dfb\n", __FUNCTION__));
        return NAVR_FAIL;
    }

    IDirectFBDisplayLayer* pLayer = NULL;
    ret = pDfb->GetDisplayLayer(pDfb, layerId, &pLayer);
    if (ret)
    {
        if (pDfb)
        {
            pDfb->Release(pDfb);
        }
        DBG_ERROR(("[RETAIL MODE]%s, failed to get display layer %d\n", __FUNCTION__, layerId));
        return NAVR_FAIL;
    }

    pLayer->SetCooperativeLevel(pLayer, DLSCL_ADMINISTRATIVE);
    ret = pLayer->GetConfiguration(pLayer, pLayerConfig);
    if (ret)
    {
        DBG_ERROR(("[RETAIL MODE]%s, failed to get dfb config for layer %d\n", __FUNCTION__, layerId));
    }

    if (pDfb)
    {
        pDfb->Release(pDfb);
    }
    return (ret == DFB_OK)? NAVR_OK : NAVR_FAIL;
}

static INT32 _nav_retail_mode_set_dfb_layer_config(INT32 layerId, DFBDisplayLayerConfig* pLayerConfig)
{
    if (NULL == pLayerConfig)
    {
        DBG_ERROR(("[RETAIL MODE]%s, pLayerConfig should not be NULL\n", __FUNCTION__));
        return NAVR_FAIL;
    }

    DFBResult ret;
    ret = DirectFBInit(NULL, NULL);
    if (ret)
    {
        DBG_ERROR(("[RETAIL MODE]%s, failed to init dfb\n", __FUNCTION__));
        return NAVR_FAIL;
    }

    IDirectFB* pDfb = NULL;
    /* Create the super interface. */
    ret = DirectFBCreate(&pDfb);
    if (ret || NULL == pDfb)
    {
        DBG_ERROR(("[RETAIL MODE]%s, failed to create dfb\n", __FUNCTION__));
        return NAVR_FAIL;
    }

    IDirectFBDisplayLayer* pLayer = NULL;
    ret = pDfb->GetDisplayLayer(pDfb, layerId, &pLayer);
    if (ret)
    {
        if (pDfb)
        {
            pDfb->Release(pDfb);
        }
        DBG_ERROR(("[RETAIL MODE]%s, failed to get display layer %d\n", __FUNCTION__, layerId));
        return NAVR_FAIL;
    }

    pLayer->SetCooperativeLevel(pLayer, DLSCL_ADMINISTRATIVE);
    ret = pLayer->SetConfiguration(pLayer, pLayerConfig);
    if (ret)
    {
        DBG_ERROR(("[RETAIL MODE]%s, failed to set dfb config for layer %d\n", __FUNCTION__, layerId));
    }

    if (pDfb)
    {
        pDfb->Release(pDfb);
    }
    return (ret == DFB_OK)? NAVR_OK : NAVR_FAIL;
}

static INT32 _nav_retail_mode_update_volume(VOID)
{
    INT32 i4_ret = NAVR_OK;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE]Enter \r\n"));

    switch(_nav_retail_mode_get_status())
    {
        case NAV_RETAIL_MODE_INITIAL:
        case NAV_RETAIL_MODE_LAUNCHING:
        case NAV_RETAIL_MODE_CHECKING:
        {
          #if 1

            /*nothing to do*/

          #else
            /* record volume  */
            {
                UINT16              i2_vol = 0;
                i4_ret=a_tv_get_vol(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),(INT16*)&i2_vol);
                NAV_LOG_ON_FAIL(i4_ret == TVR_OK ? NAVR_OK :i4_ret);

                pt_this->i2_rec_vol = i2_vol;
            }

            /* cec volume */
            {
            #ifdef APP_CEC_SUPPORT
              #ifdef APP_CEC2_SUPPORT
                UINT8 ui1_icl_val;
                SIZE_T z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
                i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                                   &ui1_icl_val,
                                   &z_size);
                NAV_LOG_ON_FAIL(i4_ret == ICLR_OK ? NAVR_OK : i4_ret);

                if (ui1_icl_val == ICL_CEC_SAC_STATUS_ON && i4_ret == ICLR_OK )
              #else
                if (a_nav_cec_is_audio_under_ctrl () == TRUE)
              #endif /* APP_CEC2_SUPPORT */
            #endif /* APP_CEC_SUPPORT */
                {
                    /*update mute status*/
                    i4_ret = nav_get_mute(&pt_this->b_rec_mute);
                    NAV_CHK_FAIL(i4_ret);
                }
            }
      #endif

            break;
        }


        case NAV_RETAIL_MODE_EXIT:
        {
        #if 1

            /*nothing to do*/

        #else
            /* set volume 0 */
            {
                i4_ret = a_tv_set_vol(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL), pt_this->i2_rec_vol);
                NAV_LOG_ON_FAIL(i4_ret == TVR_OK ? NAVR_OK :i4_ret);

                DBG_INFO(("[RETAIL MODE]recover volume %d .\n\r",pt_this->i2_rec_vol));
            }

            {
                /* cec volume */
            #ifdef APP_CEC_SUPPORT
              #ifdef APP_CEC2_SUPPORT
                UINT8 ui1_icl_val;
                SIZE_T z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
                i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                                   &ui1_icl_val,
                                   &z_size);
                NAV_LOG_ON_FAIL(i4_ret == ICLR_OK ? NAVR_OK : i4_ret);

                if (ui1_icl_val == ICL_CEC_SAC_STATUS_ON && i4_ret == ICLR_OK )
              #else
                if (a_nav_cec_is_audio_under_ctrl () == TRUE)
              #endif /* APP_CEC2_SUPPORT */
            #endif /* APP_CEC_SUPPORT */
                {
                    /* recover cec volume */
                    {
                        BOOL                    b_mute_current = FALSE;

                        i4_ret = nav_get_mute(&b_mute_current);
                        NAV_CHK_FAIL(i4_ret);
                        if(pt_this->b_rec_mute != b_mute_current)
                        {
                            i4_ret = nav_set_mute(pt_this->b_rec_mute);
                            NAV_CHK_FAIL(i4_ret);
                        }
                    }
                }
            }
        #endif

            break;
        }


        case NAV_RETAIL_MODE_RUNNING:
        {
            UINT8 ui1_idx_mode = ACFG_RETAIL_MODE_IS_NOT_FIRST_TIME_SETTING;

            i4_ret = a_cfg_cust_get_retail_mode_first_time_setting(&ui1_idx_mode);
            NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK :i4_ret);

            if( ui1_idx_mode == ACFG_RETAIL_MODE_IS_NOT_FIRST_TIME_SETTING)
            {
                break;
            }
            else
            {
               ui1_idx_mode = ACFG_RETAIL_MODE_IS_NOT_FIRST_TIME_SETTING;
               i4_ret = a_cfg_cust_set_retail_mode_first_time_setting(ui1_idx_mode);
               NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK :i4_ret);
            }

            /* cec volume :  cec can not set volume to 0*/
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT

            UINT8 ui1_icl_val;
            SIZE_T z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
            i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                               &ui1_icl_val,
                               &z_size);
            NAV_LOG_ON_FAIL(i4_ret == ICLR_OK ? NAVR_OK : i4_ret);

            if (ui1_icl_val == ICL_CEC_SAC_STATUS_ON && i4_ret == ICLR_OK )
#else
            if (a_nav_cec_is_audio_under_ctrl () == TRUE)
#endif /* APP_CEC2_SUPPORT */
#endif /* APP_CEC_SUPPORT */
            {
                i4_ret = nav_get_mute(&pt_this->b_rec_mute);
                NAV_CHK_FAIL(i4_ret);
                DBG_INFO(("#### %s(%d) b_rec_mute=%d\n", __FILE__, __LINE__,  pt_this->b_rec_mute));
                if(pt_this->b_rec_mute == FALSE)
                {
                    i4_ret = nav_set_mute(TRUE);
                    NAV_CHK_FAIL(i4_ret);
                    DBG_INFO(("[RETAIL MODE]set scc audio out port speaker mute.\n\r"));
                }
            }
            else
            {
                /* record volume */
                UINT16  i2_vol = 0;
                i4_ret=a_tv_get_vol(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),(INT16*)&i2_vol);
                NAV_LOG_ON_FAIL(i4_ret == TVR_OK ? NAVR_OK :i4_ret);
                pt_this->i2_rec_vol = i2_vol;

                /* set volume 0 */
                i4_ret = a_tv_set_vol(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL), 0);
                NAV_LOG_ON_FAIL(i4_ret == TVR_OK ? NAVR_OK :i4_ret);

                DBG_INFO(("[RETAIL MODE]set volume 0.\n\r"));
            }
        }
            break;


        case NAV_RETAIL_MODE_PAUSE:
        case NAV_RETAIL_MODE_ERROR:
            break;  /*nothing to do*/

        default:
        {
            NAV_LOG_ON_FAIL(NAVR_NO_ACTION);

            break;
        }
    }

    return NAVR_OK;
}


static INT32 _nav_retail_mode_start_overlay(VOID)
{
    INT32 i4_ret = NAVR_OK;

    if (_nav_retail_mode_get_running_type() == RETAIL_MODE_TYPE_OVERLAY)
    {
         /*already run*/
        return NAVR_OK;   //     return _nav_retail_mode_restart_overlay();
    }

    /*stop current type*/
    i4_ret = _nav_retail_mode_stop_play();
    NAV_LOG_ON_FAIL(i4_ret);
    /*start new type*/
    i4_ret = nav_retail_mode_send_cmd(TRUE);
    NAV_CHK_FAIL(i4_ret);
    /*update type*/
    i4_ret = _nav_retail_mode_set_running_type(RETAIL_MODE_TYPE_OVERLAY);
    NAV_CHK_FAIL(i4_ret);
    /*update env*/
    i4_ret = _nav_retail_mode_start_overlay_setup_env();
    NAV_CHK_FAIL(i4_ret);
    /*update ui*/
    i4_ret = _nav_retail_mode_check_logo();
    NAV_CHK_FAIL(i4_ret);
    /*init pq*/
    a_cfg_custom_set_pic_mode_vivid();

    return NAVR_OK;
}
static INT32 _nav_retail_mode_stop_overlay(VOID)
{
    INT32 i4_ret = NAVR_OK;

    if( _nav_retail_mode_get_running_type() != RETAIL_MODE_TYPE_OVERLAY)
    {
        return NAVR_OK;
    }
    /*stop current type*/
    i4_ret = nav_retail_mode_send_cmd(FALSE);
    NAV_LOG_ON_FAIL(i4_ret);
    /*update ui*/
    i4_ret = retail_mode_view_logo_hide();
    NAV_CHK_FAIL(i4_ret);
    /*update type*/
    i4_ret = _nav_retail_mode_set_running_type(RETAIL_MODE_TYPE_UNKNOW);
    NAV_CHK_FAIL(i4_ret);
     /*update env*/
    return NAVR_OK;
}

static INT32 _nav_retail_mode_start_video(VOID)
{
    INT32 i4_ret = NAVR_OK;
    if (_nav_retail_mode_get_running_type() == RETAIL_MODE_TYPE_VIDEO)
    {
         /*already run*/
        return NAVR_OK;   //     return _nav_retail_mode_restart_video();
    }

    /*stop current type*/
    i4_ret = _nav_retail_mode_stop_play();
    NAV_LOG_ON_FAIL(i4_ret);
    /*start new type*/
    i4_ret = nav_retail_start_end_cap();
    NAV_CHK_FAIL(i4_ret);
    /*update type*/
    i4_ret = _nav_retail_mode_set_running_type(RETAIL_MODE_TYPE_VIDEO);
    NAV_CHK_FAIL(i4_ret);
    /*update env*/
    i4_ret = _nav_retail_mode_start_video_setup_env();
    NAV_CHK_FAIL(i4_ret);
    return NAVR_OK;
}
static INT32 _nav_retail_mode_stop_video(VOID)
{
    INT32 i4_ret = NAVR_OK;

    if ( _nav_retail_mode_get_running_type() != RETAIL_MODE_TYPE_VIDEO)
    {
        return NAVR_OK;
    }
    /*Clear element for cec only*/
//    _nav_retail_mode_cec_clear_element();
    /*stop current type*/
    i4_ret = nav_retail_stop_end_cap();
    NAV_CHK_FAIL(i4_ret);
    /*update type*/
    i4_ret = _nav_retail_mode_set_running_type(RETAIL_MODE_TYPE_UNKNOW);
    NAV_CHK_FAIL(i4_ret);
    /*update env*/
    i4_ret = _nav_retail_mode_stop_video_setup_env();
    NAV_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

static INT32 _nav_retail_mode_start_internal_video(VOID)
{
    INT32 i4_ret = NAVR_OK;
    if (_nav_retail_mode_get_running_type() == RETAIL_MODE_TYPE_VIDEO_INTERNAL)
    {
         /*already run*/
        return NAVR_OK;   //     return _nav_retail_mode_restart_internal_video();
    }
//    _nav_ratail_mode_cec_save_video_mode_element();
    /*stop current type*/
    i4_ret = _nav_retail_mode_stop_play();
    NAV_LOG_ON_FAIL(i4_ret);
    /*start new type*/
    i4_ret = nav_retail_start_internal_video();
    NAV_CHK_FAIL(i4_ret);
    /*update type*/
    i4_ret = _nav_retail_mode_set_running_type(RETAIL_MODE_TYPE_VIDEO_INTERNAL);
    NAV_CHK_FAIL(i4_ret);
    /*update env*/
    i4_ret = _nav_retail_mode_start_internal_video_setup_env();
    NAV_CHK_FAIL(i4_ret);
    return NAVR_OK;
}
static INT32 _nav_retail_mode_stop_internal_video(VOID)
{
    INT32 i4_ret = NAVR_OK;

    if (nav_retail_mode_get_is_play() == FALSE || _nav_retail_mode_get_running_type() != RETAIL_MODE_TYPE_VIDEO_INTERNAL)
    {
        return NAVR_OK;
    }
    /*stop current type*/
    i4_ret = nav_retail_stop_internal_video();
    NAV_CHK_FAIL(i4_ret);
    /*update type*/
    i4_ret = _nav_retail_mode_set_running_type(RETAIL_MODE_TYPE_UNKNOW);
    NAV_CHK_FAIL(i4_ret);
    /*update env*/
    i4_ret = _nav_retail_mode_stop_internal_video_setup_env();
    NAV_CHK_FAIL(i4_ret);
    return NAVR_OK;
}

static INT32 _nav_retail_mode_stop_timer(VOID)
{
    _nav_retail_mode_stop_pause_timer();
//    _nav_retail_mode_stop_cfg_nfy_timer();
    return NAVR_OK;
}

static INT32 _get_crnt_isl(ISL_REC_T* pt_isl_rec)
{
    INT32           i4_ret;
    TV_WIN_ID_T     t_win_id;

    i4_ret = a_tv_get_focus_win(&t_win_id);
    NAV_CHK_FAIL( i4_ret == TVR_OK ? NAVR_OK : i4_ret );

    i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id, pt_isl_rec);
    NAV_CHK_FAIL( i4_ret == TVR_OK ? NAVR_OK : i4_ret );

    return i4_ret;
}


static VOID _nav_ratail_mode_cec_save_video_mode_element(VOID)
{
    INT32 i4_ret = NAVR_OK;
    CHAR  s_disp_name[SYS_NAME_LEN+1] = {0};
    UINT8 ui1_input_id = 0;
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    NAV_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    NAV_LOG_ON_FAIL(i4_ret);
    uii_last_video_demo_input_src = ui1_input_id;   //Need mark the input source before video demo demo running
}

static VOID _nav_retail_mode_cec_clear_element(VOID)
{
    uii_last_video_demo_input_src = 0xF0;//Need restore the input source value
    b_g_retail_mode_need_recheck_hdmi_plug_in_out = FALSE;
}

static VOID _nav_retail_cec_hdmi_plug_in_out_recheck(NAV_RETAIL_MODE_STATUS_T e_status)//For HDMI plug in/out tress test,need recheck the demo mode type with the HDMI plug in/out status
{
    ISL_REC_T   t_isl_rec   =  {0};

    /* Check the input source on FOCUSED WIN */
    _get_crnt_isl(&t_isl_rec);
    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV
        && (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI))
    {
        DBG_INFO(("%s_%d b_g_retail_mode_need_recheck_hdmi_plug_in_out:%d \n",__FUNCTION__,__LINE__,b_g_retail_mode_need_recheck_hdmi_plug_in_out));
        if(b_g_retail_mode_need_recheck_hdmi_plug_in_out&&
//           (_nav_retail_mode_get_running_type() == RETAIL_MODE_TYPE_VIDEO_INTERNAL)&&
           (e_status == NAV_RETAIL_MODE_RUNNING))
        {
            _nav_retail_mode_exit();
            _nav_retail_mode_set_status(NAV_RETAIL_MODE_RESTARTING);
        }
    }
}

static VOID _nav_retail_cec_nfy_fct_func (VOID*    pv_tag1,
                              VOID*         pv_tag2,
                              VOID*        pv_tag3)
{
    UINT16  ui2_port_id = (UINT16)(UINT32)pv_tag1;;
    BOOL    b_5v_status = (BOOL)(UINT32)pv_tag2;

    RETAIL_MODE_RUNNING_TYPE_T e_running_type = a_nav_retail_mode_get_running_type();

    DBG_LOG_PRINT(("[RETAIL MODE]ui2_port_id:%d b_5v_status:%d uii_last_video_demo_input_src:%d,ui1_cur_hdmi_port:%d \n",ui2_port_id,b_5v_status,uii_last_video_demo_input_src,ui1_cur_hdmi_port));

    /*1:HDMI1,2:HDMI2,3:DHMI3*/
    b_g_retail_mode_need_recheck_hdmi_plug_in_out = FALSE;

    /*  just return */
    if( NAV_RETAIL_MODE_RUNNING != _nav_retail_mode_get_status() )
    {
        return;
    }
    else if(_nav_retail_mode_check_running_type() == RETAIL_MODE_TYPE_VIDEO)
    {
        return;
    }

    if (ui2_port_id == ui1_cur_hdmi_port+1 )
    {
        if(_nav_retail_mode_get_running_type() == RETAIL_MODE_TYPE_OVERLAY)
        {
            DBG_INFO(("[%s][%d] The HDMI in/out source is not match with video demo mode \n", __FUNCTION__, __LINE__));
            return;
        }
    }

    if(b_5v_status && e_running_type != RETAIL_MODE_TYPE_UNKNOW)
    {
//        b_g_retail_mode_need_recheck_hdmi_plug_in_out = TRUE;
     }
    else if (b_5v_status == 0 && e_running_type != RETAIL_MODE_TYPE_UNKNOW)
    {
        a_cfg_custom_set_demo_type(0xF0);
    }

    DBG_INFO(("[RETAIL MODE]Enter.\n\r"));

    if(b_5v_status)
    {
        //i4_ret = _nav_retail_mode_update_running_type();
        //NAV_LOG_ON_FAIL(i4_ret);
        c_thread_delay(1000);
    #if APP_RETAIL_DEMO_BACKUP_MMP_PQ
        nav_recover_mmp_pq_value_in_exit();
    #endif
       _nav_retail_mode_exit();
        a_nav_retail_mode_reset_env();
       _nav_retail_mode_set_status(NAV_RETAIL_MODE_RESTARTING);

    }

    nav_send_msg_to_component (
                            NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_RETAIL_MODE),
                            (b_5v_status)
                            ? NAV_UI_MSG_WITH_SIGNAL
                            : NAV_UI_MSG_NO_SIGNAL,
                            NULL );
}

static VOID _nav_retail_cec_nfy_fct(CECM_NFY_T* pt_nfy_data,
                                    VOID*       pv_tag,
                                    UINT32      ui4_data)
{
    if(pt_nfy_data->e_nfy_type == CECM_NFY_TYPE_MSGCODE && pt_nfy_data->u_code.e_msgcode == CECM_MSGCODE_5V_PWR)
    {
        nav_request_context_switch (_nav_retail_cec_nfy_fct_func,
                               (VOID *)(UINT32)pt_nfy_data->u_data.t_5v_pwr_info.ui2_comp_id,
                               (VOID *)(UINT32)pt_nfy_data->u_data.t_5v_pwr_info.b_5v_power,
                               NULL);
    }

}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_yahoo_status_nfy_func
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_yahoo_status_nfy_func(UINT16  ui2_nfy_id,
                                                    VOID*   pv_tag,
                                                    ICL_NOTIFY_DATA_T* pt_notify_data)
{
    DBG_INFO(("[RETAIL MODE]Enter.\n\r"));

    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;
    INT32               i4_ret;
    ICL_GRPID_TYPE      e_grp_id;
    SIZE_T              z_size ;
    UINT8               ui1_info_status;
    ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

    e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    if (e_grp_id != ICL_GRPID_CUSTOM_NW_WIDGET)
    {
        return NAVR_OK;
    }

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL != t_retail_mode)
    {
        return NAVR_OK;
    }

    if (NAV_RETAIL_MODE_RESUME_FROM_NULL != pt_this->e_resume_from_app)
    {
        return NAVR_OK;
    }

    /* get network widget dock status */
    z_size = ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CUSTOM_NW_WIDGET, ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS),
                       &ui1_info_status,
                       &z_size);
    if (ICLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    pt_this->ui4_yahoo_status = ui1_info_status;

    /* get network app status */
    z_size = ICL_RECID_CUSTOM_NW_WIDGET_APP_STATUS_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CUSTOM_NW_WIDGET, ICL_RECID_CUSTOM_NW_WIDGET_APP_STATUS),
                       &ui1_info_status,
                       &z_size);
    if (ICLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    pt_this->ui4_app_status = ui1_info_status;


    if (pt_this->ui4_yahoo_status == (UINT32)YAHOO_STATUS_HIDE &&
        pt_this->ui4_app_status == (UINT32)NW_APP_STATUS_HIDE)
    {
        _nav_retail_mode_start_pause_timer();

        /* reset focus to pause dialog */
        /* MAYBE can NOT goto this flow anymore */
        if (pt_this->e_popup_dlg == NAV_RETAIL_MODE_POPUP_PAUSE_DLG)
        {
            a_ui_simple_dialog_set_focus(pt_this->h_pause_dlg, TRUE);
        }
    }
    else
    {
        /* if pause dialog is popup */
        if(pt_this->e_popup_dlg == NAV_RETAIL_MODE_POPUP_PAUSE_DLG)
        {
            _nav_retail_pause_dlg_hide();
        }
    }

    DBG_INFO(("[RETAIL MODE] --- yahoo and 3rd app status = %d - %d\n", pt_this->ui4_yahoo_status, pt_this->ui4_app_status));

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _backup_set_demo_idx
 *
 * Description: Return the index of picture mode
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID _backup_set_demo_idx(UINT16 ui2_idx)
{
	ui2_backup_demo_idx = ui2_idx;
}

/*----------------------------------------------------------------------------
 * Name: _get_backup_demo_idx
 *
 * Description: Return the index of picture mode
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
UINT16 _get_backup_demo_idx(VOID)
{
	return ui2_backup_demo_idx;
}


/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_get_pq_idx
 *
 * Description: Return the index of picture mode
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
UINT16 _nav_retail_mode_get_pq_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 &i2_val);

    return (UINT16)i2_val;
}


/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_set_pq_idx
 *
 * Description: Set picture mode
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID _nav_retail_mode_set_pq_idx(UINT16 ui2_idx)
{
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 (INT16)ui2_idx);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
}

/*----------------------------------------------------------------------------
 * Name: a_check_is_2K18_model_platform
 *
 * Description: check 2K18 or 2K19 platform
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
BOOL a_check_is_2K18_model_platform(VOID)
{
    /* get model name */
    CHAR s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};

    a_cfg_custom_get_model_name(s_model_name);

    if ((c_strchr( s_model_name, 'F' )) != NULL)
    {
        return TRUE;
    }
    return FALSE;
}


/*----------------------------------------------------------------------------
 * Name: _nav_retail_restart_demo_mode
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_pause_restart_demo_mode(
                    VOID*           pv_tag1,
                    VOID*           pv_tag2,
                    VOID*           pv_tag3
                    )
{
    CHAR                        s_app_name [APP_NAME_MAX_LEN + 1];
    ACFG_RETAIL_MODE_T          t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    _NAV_RETAIL_MODE_T*         pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    a_am_get_active_app(s_app_name);

    if (pt_this->ui4_yahoo_status != (UINT32)YAHOO_STATUS_HIDE ||
        pt_this->ui4_app_status != (UINT32)NW_APP_STATUS_HIDE)
    {
        /* Do nothing */
        DBG_INFO(("[RETAIL]pt_this->ui4_yahoo_status != (UINT32)YAHOO_STATUS_HIDE --- FUNC:%s LINE:%d.\n",__FUNCTION__,__LINE__));
    }
    else if ((a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
        || (c_strcmp(s_app_name, MMP_NAME) == 0))
    {
        /* Do nothing */
        DBG_INFO(("[RETAIL]a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SV--- FUNC:%s LINE:%d.\n",__FUNCTION__,__LINE__));
    }
    else if ((pt_this->e_resume_from_app == NAV_RETAIL_MODE_RESUME_FROM_NULL)
        && (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
        && (c_strcmp(s_app_name, MENU_NAME) == 0)
        && (NAV_RETAIL_MODE_PAUSE == _nav_retail_mode_get_status()))
    {
        /* menu dealing with special case, NOT start store demo */
        if (nav_is_channel_scan_active ())
        {
            _nav_retail_mode_stop_pause_timer();
            return;
        }
        else
        {
            DBG_INFO(("[RETAIL MODE] the pause timer out in menu should resume nav and start store demo !!\n"));
            _nav_retail_mode_set_status(NAV_RETAIL_MODE_INITIAL);
            nav_retail_mode_go(NAV_RETAIL_MODE_RUNNING);
        }
    }
    else
    {
        nav_retail_mode_go(NAV_RETAIL_MODE_RUNNING);
    }

    DBG_INFO(("[RETAIL MODE] [%s] End \r\n", __FUNCTION__));

    _nav_retail_mode_stop_pause_timer();
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_pause_timer_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_pause_timer_cb(
                    HANDLE_T        h_timer,
                    VOID*           pv_tag
                    )
{
    nav_request_context_switch(_nav_retail_pause_restart_demo_mode, NULL, NULL, NULL);
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_restart_demo_mode
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_overlay_demo_update(
                    VOID*           pv_tag1,
                    VOID*           pv_tag2,
                    VOID*           pv_tag3
                    )
{
    INT32            i4_ret = 0;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    _nav_retail_mode_update_running_type();

    i4_ret = a_start_retail_mode_in_no_overlay();
    NAV_LOG_ON_FAIL(i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_overlay_demo_update_timer_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_overlay_demo_update_timer_cb(
                    HANDLE_T        h_timer,
                    VOID*           pv_tag
                    )
{
    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    nav_request_context_switch(_nav_retail_overlay_demo_update, NULL, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_stop_pause_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_retail_mode_stop_pause_timer(VOID)
{
    INT32 i4_ret;

    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    if (c_handle_valid(pt_this->h_pause_timer) == FALSE)
    {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_pause_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop nav_retail::h_pause_timer failed!"));
    }

    pt_this->b_is_pause_timer_start = FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_stop_cfg_nfy_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_retail_mode_stop_cfg_nfy_timer(VOID)
{
    INT32 i4_ret;

    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

//    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    if (c_handle_valid(pt_this->b_is_cfg_nfy_timer_start) == FALSE)
    {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_cfg_nfy_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop nav_retail::h_cfg_nfy_timer failed!"));
    }

    pt_this->b_is_cfg_nfy_timer_start = FALSE;
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_start_pause_timer
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_mode_start_pause_timer()
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    DBG_LOG_PRINT(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    /* if timer is running just restart it */
    if (pt_this->b_is_pause_timer_start)
    {
       _nav_retail_mode_stop_pause_timer();
    }

    c_timer_start(pt_this->h_pause_timer,
                  NAV_RETAIL_MODE_PAUSE_NFY_TIMER,
                  X_TIMER_FLAG_ONCE,
                  _nav_retail_pause_timer_cb,
                  NULL);

    t_g_retail_mode.b_is_pause_timer_start = TRUE;
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_start_cfg_nfy_timer
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_mode_start_cfg_nfy_timer()
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

//    DBG_INFO(("[RETAIL MODE]Enter.\n\r");

    /* if timer is running just restart it */
    if (pt_this->b_is_cfg_nfy_timer_start == TRUE)
    {
       _nav_retail_mode_stop_cfg_nfy_timer();
    }

    c_timer_start(pt_this->h_cfg_nfy_timer,
                  NAV_RETAIL_MODE_ACFG_NFY_TIMER,
                  X_TIMER_FLAG_ONCE,
                  _nav_retail_mode_cfg_change_timer_cb,
                  NULL);

    pt_this->b_is_cfg_nfy_timer_start = TRUE;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_pause_dlg_default_msg_proc
 * Description  Initialize the pause dialog.
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_pause_dlg_default_msg_proc(
                                            HANDLE_T            h_widget,
                                            UINT32              ui4_msg,
                                            VOID*               pv_param1,
                                            VOID*               pv_param2
                                            )
{

#ifdef APP_TTS_SUPPORT
    UTF16_T             w2s_tts_str[128] = {0};

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        if (ui4_keycode == BTN_CURSOR_LEFT)
        {
            c_memset(w2s_tts_str, 0, sizeof(w2s_tts_str));
            c_uc_w2s_strcpy(w2s_tts_str, MLM_NAV_TEXT(0, MLM_NAV_KEY_RETAIL_MODE_PAUSE_BTN));
            a_app_tts_play(w2s_tts_str, c_uc_w2s_strlen(w2s_tts_str));
        }
        else if (ui4_keycode == BTN_CURSOR_RIGHT)
        {
            c_memset(w2s_tts_str, 0, sizeof(w2s_tts_str));
            c_uc_w2s_strcpy(w2s_tts_str, MLM_NAV_TEXT(0, MLM_NAV_KEY_RETAIL_MODE_EXIT_BTN));
            a_app_tts_play(w2s_tts_str, c_uc_w2s_strlen(w2s_tts_str));
        }
    }
#endif

    return a_ui_simple_dialog_default_msg_proc(h_widget,
                                               ui4_msg,
                                               pv_param1,
                                               pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_pause_dlg_init
 * Description  Initialize the pause dialog.
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_pause_dlg_init(VOID)
{
    INT32                       i4_ret  = NAVR_OK;
    _NAV_RETAIL_MODE_T*         pt_this = &t_g_retail_mode;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    GL_POINT_T                  t_offset = {NAV_RETAIL_MODE_DIALOG_OFFSET, 0};

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = pt_this->h_canvas;
    t_simple_dialog_init.b_one_btn_mode                 = FALSE;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = _nav_retail_pause_dlg_exit_fct;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _nav_retail_pause_dlg_pause_fct;
    t_simple_dialog_init.pf_wdgt_proc                   = _nav_retail_pause_dlg_default_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = &t_offset;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = FALSE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &pt_this->h_pause_dlg);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_pause_dlg,
                                         MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                         MLM_NAV_KEY_RETAIL_MODE_PAUSE_MSG));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);


    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_pause_dlg,
                                             MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                             MLM_NAV_KEY_RETAIL_MODE_PAUSE_BTN));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);


    i4_ret = a_ui_simple_dialog_set_no_text(pt_this->h_pause_dlg,
                                            MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                            MLM_NAV_KEY_RETAIL_MODE_EXIT_BTN));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);


    /* Set default focus button to Pause Demo */
    i4_ret = a_ui_simple_dialog_set_answer(pt_this->h_pause_dlg, TRUE);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    return NAVR_OK;
}


static INT32 _nav_retail_resume_dlg_show(VOID)
{
    INT32                   i4_ret  = NAVR_OK;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    /* if dialog is popup just return */
    if (NAV_RETAIL_MODE_POPUP_RESUME_DLG == pt_this->e_popup_dlg)
    {
        return NAVR_OK;
    }

    /* disable screen saver */
    a_scrn_svr_set_enable(FALSE);

    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_resume_dlg,
                                         MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                         MLM_NAV_KEY_RETAIL_MODE_PAUSE_MSG));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_resume_dlg,
                                             MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                             MLM_NAV_KEY_RETAIL_MODE_RESUME_BTN));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);


    i4_ret = a_ui_simple_dialog_set_no_text(pt_this->h_resume_dlg,
                                            MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                            MLM_NAV_KEY_RETAIL_MODE_EXIT_BTN));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_set_info_text(pt_this->h_resume_dlg,
                                            MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                            MLM_NAV_KEY_DEMO_MODE_POP_INFO));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    /* Set default focus button to Pause Demo */
    i4_ret = a_ui_simple_dialog_set_answer(pt_this->h_resume_dlg, TRUE);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_show(pt_this->h_resume_dlg);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_set_focus(pt_this->h_resume_dlg, FALSE);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_repaint(pt_this->h_resume_dlg);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    /*Hide logo after pause dialog show.*/
    i4_ret = retail_mode_view_logo_hide();
    NAV_CHK_FAIL(i4_ret);

    pt_this->e_popup_dlg = NAV_RETAIL_MODE_POPUP_RESUME_DLG;

    a_amb_enable_system_key(FALSE);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_tts_str[256] = {0};

    c_uc_w2s_strcpy(w2s_tts_str, MLM_NAV_TEXT(0, MLM_NAV_KEY_RETAIL_MODE_PAUSE_MSG));
    c_uc_w2s_strcat(w2s_tts_str, (UTF16_T*)L".");
    c_uc_w2s_strcat(w2s_tts_str, MLM_NAV_TEXT(0, MLM_NAV_KEY_RETAIL_MODE_EXIT_BTN));

    a_app_tts_play(w2s_tts_str, c_uc_w2s_strlen(w2s_tts_str));
#endif

    return NAVR_OK;
}

static INT32 _nav_retail_resume_dlg_init(VOID)
{
    INT32                       i4_ret  = NAVR_OK;
    _NAV_RETAIL_MODE_T*         pt_this = &t_g_retail_mode;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    GL_POINT_T                  t_offset = {NAV_RETAIL_MODE_DIALOG_OFFSET, 0};

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = pt_this->h_canvas;
    t_simple_dialog_init.b_one_btn_mode                 = FALSE;
    t_simple_dialog_init.b_three_btn_mode                 = TRUE;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = _nav_retail_resume_dlg_exit_fct;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _nav_retail_resume_dlg_resume_fct;
    t_simple_dialog_init.pf_ui_simple_dialog_info_cb_fct = _nav_retail_resume_dlg_info_btn_fct;
    t_simple_dialog_init.pf_wdgt_proc                   = _nav_retail_resume_dlg_default_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = &t_offset;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = FALSE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &pt_this->h_resume_dlg);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);


    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_resume_dlg,
                                         MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                         MLM_NAV_KEY_RETAIL_MODE_RESUME_MSG));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_resume_dlg,
                                             MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                             MLM_NAV_KEY_RETAIL_MODE_RESUME_BTN));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);


    i4_ret = a_ui_simple_dialog_set_no_text(pt_this->h_resume_dlg,
                                            MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                            MLM_NAV_KEY_RETAIL_MODE_EXIT_BTN));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);
    i4_ret = a_ui_simple_dialog_set_info_text(pt_this->h_resume_dlg,
                                            MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                            MLM_NAV_KEY_DEMO_MODE_POP_INFO));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    /* Set default focus button to Pause Demo */
    i4_ret = a_ui_simple_dialog_set_answer(pt_this->h_resume_dlg, TRUE);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    return NAVR_OK;
}


static INT32 _nav_retail_resume_dlg_hide(VOID)
{
    INT32 i4_ret = NAVR_OK;
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    {
       RETAIL_MODE_RUNNING_TYPE_T e_type = _nav_retail_mode_get_running_type();

       if( e_type != RETAIL_MODE_TYPE_VIDEO && e_type != RETAIL_MODE_TYPE_VIDEO_INTERNAL )
       {
           NAV_CHK_FAIL(NAVR_NO_ACTION);
       }
       if( e_type == RETAIL_MODE_TYPE_OVERLAY)
       {
//           a_amb_enable_system_key(TRUE);
       }
       if(( e_type == RETAIL_MODE_TYPE_VIDEO||
          e_type == RETAIL_MODE_TYPE_VIDEO_INTERNAL)&&
          (nav_retail_mode_get_is_video_paused() == TRUE))
       {
          i4_ret = nav_retail_end_cap_ctrl_video(NAV_RETAIL_END_CAP_PLAY);
          NAV_CHK_FAIL(i4_ret);
       }
    }

    _nav_retail_mode_dialog_hide(pt_this->h_resume_dlg);

    if(NAV_RETAIL_MODE_PAUSE == pt_this->e_status)
    {
        a_amb_enable_system_key(TRUE);
    }

    /* enable screen saver */
    a_scrn_svr_set_enable(TRUE);

    pt_this->e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;

    /*Show logo after pause dialog hide.*/
    i4_ret = _nav_retail_mode_check_logo();
    NAV_CHK_FAIL(i4_ret);

    nav_view_set_focus();

    return NAVR_OK;
}

static VOID  _nav_retail_resume_dlg_resume_fct(VOID)
{
    INT32 i4_ret = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    {
        RETAIL_MODE_RUNNING_TYPE_T e_type = _nav_retail_mode_get_running_type();

        switch(e_type)
        {
            case RETAIL_MODE_TYPE_UNKNOW:   /* follow pause timer call back  */
                {
                    _nav_retail_pause_restart_demo_mode(NULL,NULL,NULL);
                }
                break;
            case RETAIL_MODE_TYPE_VIDEO:
            case RETAIL_MODE_TYPE_VIDEO_INTERNAL:
			case RETAIL_MODE_TYPE_OVERLAY:
                {
                    i4_ret = _nav_retail_resume_dlg_hide();
                    NAV_LOG_ON_FAIL(i4_ret);
                }
                break;
            default:
                {
                    NAV_LOG_ON_FAIL(NAVR_NO_ACTION);
                }
                break;
        }
    }

    return;
}

static VOID  _nav_retail_resume_info_dlg_fct(VOID)
{
    INT32 i4_ret = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    i4_ret = _nav_retail_info_dlg_hide();
    NAV_LOG_ON_FAIL(i4_ret);

    return;
}

static INT32 _nav_retail_info_dlg_hide(VOID)
{
    INT32 i4_ret = NAVR_OK;
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    {
       RETAIL_MODE_RUNNING_TYPE_T e_type = _nav_retail_mode_get_running_type();
       if( e_type == RETAIL_MODE_TYPE_OVERLAY)
       {
//          a_amb_enable_system_key(TRUE);
       }
    }

    _nav_retail_mode_dialog_hide(pt_this->h_info_dlg);
    /* enable screen saver */
    a_scrn_svr_set_enable(TRUE);

    pt_this->e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;

    /*Show logo after pause dialog hide.*/
    i4_ret = _nav_retail_mode_check_logo();
    NAV_CHK_FAIL(i4_ret);

    nav_view_set_focus();

    return NAVR_OK;
}
static INT32 _nav_retail_resume_info_pop_show(VOID)
{
    INT32                   i4_ret  = NAVR_OK;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;
    UTF16_T str_tmp[512] = {0};
    UTF16_T    w2s_tmp_str[64] = {0};
    CHAR            ac_buf[32] = {0};
    UTF16_T    w2s_tmp_vaule_str[64] = {0};
    CHAR*     s_tmp_str;
    CHAR     s_str[64];

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    /*serial number*/
#ifdef APP_ULI_UPG_SUPPORT
    UINT32 ui4_buff_len = 64;
    CHAR    str_sn[64] = "N/A";
    CHAR    string_sn[64] = {0};
    UINT32  ui4_digs_len = 0;
    a_uli_get_serial_number((UINT8 *)str_sn, &ui4_buff_len);
    if (ui4_buff_len < 15)
    {
        c_strncpy(string_sn, str_sn + 2, 2);
        c_strncat(string_sn, str_sn, 2);
        c_strncat(string_sn, str_sn + 6, 2);
        c_strncat(string_sn, str_sn + 4, 2);
        c_strncat(string_sn, str_sn + 8, 5);

        ui4_digs_len = c_strlen(string_sn);
        c_strcat(string_sn, str_sn + ui4_digs_len);
    }
    else
    {
        c_strncpy(string_sn, str_sn + 8, 2);
        c_strncat(string_sn, str_sn, 8);

        ui4_digs_len = c_strlen(string_sn);
        c_strcat(string_sn, str_sn + ui4_digs_len);
    }
#endif


    /* disable screen saver */
    a_scrn_svr_set_enable(FALSE);
    /*Title*/

    c_uc_w2s_strncpy(str_tmp,
                    L"                              ",
                    34);

    c_uc_w2s_strncat(str_tmp,
                    MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_DEMO_MODE_POP_INFO),
                    12);
    c_uc_w2s_strncat(str_tmp,L" \n",4);
    /*Model Name*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    a_cfg_custom_get_model_name(ac_buf);
    c_uc_w2s_strncpy(w2s_tmp_str,
                MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_NAV_SYS_INFO_MODEL_NAME),
                24);
    c_uc_ps_to_w2s(ac_buf,w2s_tmp_vaule_str,c_strlen(ac_buf));
    c_uc_w2s_strncat(w2s_tmp_str,w2s_tmp_vaule_str,32);
    c_uc_w2s_strncat(str_tmp,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));
    c_uc_w2s_strncat(str_tmp,L" \n",4);
    c_uc_w2s_strncat(str_tmp,MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_NAV_SYS_INFO_SERIAL_NAME),20);
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_tmp_vaule_str, 0, sizeof(w2s_tmp_vaule_str));
#ifdef APP_ULI_UPG_SUPPORT
    c_uc_ps_to_w2s(string_sn,w2s_tmp_str,c_strlen(string_sn));
#endif
    c_uc_w2s_strncat(str_tmp,w2s_tmp_str,32);
    c_uc_w2s_strncat(str_tmp,L" \n",4);

    /*Version*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_tmp_vaule_str, 0, sizeof(w2s_tmp_vaule_str));
    s_tmp_str = sys_cust_get_usb_upg_version();
    c_uc_ps_to_w2s(s_tmp_str,w2s_tmp_vaule_str,c_strlen(s_tmp_str));
    c_uc_w2s_strncat(str_tmp,MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_NAV_SYS_INFO_VERSION),12);
    c_uc_w2s_strncat(str_tmp,w2s_tmp_vaule_str,12);
    c_uc_w2s_strncat(str_tmp,L" \n",4);

    /*embedded demo video name*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_tmp_vaule_str, 0, sizeof(w2s_tmp_vaule_str));
    if (nav_retail_internal_demo_check() == TRUE)
    {
        s_tmp_str = nav_retail_get_internal_demo_file_name();
	}
    else
    {
        s_tmp_str ="N/A";
    }

    c_uc_w2s_strncat(str_tmp,MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_DEMO_MODE_EMBEDDED_DEMO_FILE),32);

    if(c_strlen(s_tmp_str) > 18)
    {
        c_strncpy(s_str,s_tmp_str,18);
        DBG_INFO(("%s_%d s_str:%s \n",__FUNCTION__,__LINE__,s_str));
        c_uc_ps_to_w2s(s_str,w2s_tmp_vaule_str,18);
        c_uc_w2s_strncat(str_tmp,w2s_tmp_vaule_str,64);
        c_uc_w2s_strncat(str_tmp,L"\n",2);
		c_memset(s_str, 0, sizeof(s_str));
        if(c_strlen(s_tmp_str) <64)
        {
            c_strncpy(s_str,s_tmp_str+18,c_strlen(s_tmp_str) -18);
        }
        else
        {
            c_strncpy(s_str,s_tmp_str+18,64 -18);
        }
        DBG_INFO(("%s_%d s_str:%s \n",__FUNCTION__,__LINE__,s_str));
		c_memset(w2s_tmp_vaule_str, 0, sizeof(w2s_tmp_vaule_str));
		c_uc_ps_to_w2s(s_str,w2s_tmp_vaule_str,c_strlen(s_str));
        c_uc_w2s_strncat(str_tmp,w2s_tmp_vaule_str,64);
    }
	else
	{
		c_strncpy(s_str,s_tmp_str,18);
		c_uc_ps_to_w2s(s_str,w2s_tmp_vaule_str,18);
		c_uc_w2s_strncat(str_tmp,w2s_tmp_vaule_str,64);
		c_uc_w2s_strncat(str_tmp,L"\n",2);

	}
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_info_dlg,str_tmp);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_info_dlg,
                                             MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                             MLM_NAV_KEY_DIALOG_OK));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

//    i4_ret = a_ui_simple_dialog_set_answer(pt_this->h_info_dlg, TRUE);
//    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_show(pt_this->h_info_dlg);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_set_focus(pt_this->h_info_dlg, FALSE);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_repaint(pt_this->h_info_dlg);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    /*Hide logo after pause dialog show.*/
    i4_ret = retail_mode_view_logo_hide();
    NAV_CHK_FAIL(i4_ret);

    pt_this->e_popup_dlg = NAV_RETAIL_MODE_POPUP_INFO_DLG;

    a_amb_enable_system_key(FALSE);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_tts_str[256] = {0};

    c_uc_w2s_strcpy(w2s_tts_str, MLM_NAV_TEXT(0, MLM_NAV_KEY_RETAIL_MODE_PAUSE_MSG));
    c_uc_w2s_strcat(w2s_tts_str, (UTF16_T*)L".");
    c_uc_w2s_strcat(w2s_tts_str, MLM_NAV_TEXT(0, MLM_NAV_KEY_RETAIL_MODE_EXIT_BTN));

    a_app_tts_play(w2s_tts_str, c_uc_w2s_strlen(w2s_tts_str));
#endif

    return NAVR_OK;
}

VOID _nav_retail_hide_dialg_info_timer_cb_context(
								VOID*           pv_tag1,
								VOID*           pv_tag2,
								VOID*           pv_tag3
								)
{

    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

	_nav_retail_mode_dialog_hide(pt_this->h_info_dlg);

}

VOID _nav_retail_hide_dialg_info_timer_cb(HANDLE_T h_timer, VOID* pv_tag)
{
    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

	nav_request_context_switch(_nav_retail_hide_dialg_info_timer_cb_context,NULL,NULL,NULL);
}

static VOID  _nav_retail_resume_dlg_info_btn_fct(VOID)
{
    INT32 i4_ret = NAVR_OK;
  	_NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    i4_ret = _nav_retail_resume_dlg_hide();
    NAV_LOG_ON_FAIL(i4_ret);
    _nav_retail_resume_info_pop_show();
	c_timer_stop(pt_this->h_dialag_hide_timer);
	c_timer_start(pt_this->h_dialag_hide_timer,
			(DLG_HIDE_AFTER_90_SECOND*1000),
			X_TIMER_FLAG_ONCE,
			_nav_retail_hide_dialg_info_timer_cb,
			NULL);
    return;
}

static INT32 _nav_retail_info_dlg_init(VOID)
{
    INT32                       i4_ret  = NAVR_OK;
    _NAV_RETAIL_MODE_T*         pt_this = &t_g_retail_mode;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    GL_POINT_T                  t_offset = {NAV_RETAIL_MODE_DIALOG_OFFSET, 0};
    UTF16_T                     str_tmp[512] = {0};
    UTF16_T    w2s_tmp_str[64] = {0};
    CHAR            ac_buf[32] = {0};

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = pt_this->h_canvas;
    t_simple_dialog_init.b_one_btn_mode                 = TRUE;
    t_simple_dialog_init.b_three_btn_mode                 = FALSE;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _nav_retail_resume_info_dlg_fct;
    t_simple_dialog_init.pf_ui_simple_dialog_info_cb_fct = NULL;
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = &t_offset;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_LEFT_TOP;
    t_simple_dialog_init.b_default_answer               = FALSE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &pt_this->h_info_dlg);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    c_uc_w2s_strncpy(str_tmp,
                    MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_DEMO_MODE_POP_INFO),
                    24);
    c_uc_w2s_strncat(str_tmp,L" \n",4);

    /*Model Name*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    a_cfg_custom_get_model_name(ac_buf);
    c_uc_ps_to_w2s(ac_buf,w2s_tmp_str,c_strlen(ac_buf));
    c_uc_w2s_strncat(str_tmp,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_info_dlg,
                                         str_tmp);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_info_dlg,
                                             MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                             MLM_NAV_KEY_DIALOG_YES));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    return NAVR_OK;
}

#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
VOID nav_recover_mmp_pq_value_in_exit(VOID)
{
		RETAIL_MODE_RUNNING_TYPE_T e_type = RETAIL_MODE_TYPE_UNKNOW;

		e_type = _nav_retail_mode_get_running_type();
	    if (e_type == RETAIL_MODE_TYPE_VIDEO || e_type == RETAIL_MODE_TYPE_VIDEO_INTERNAL )
	    {
		   a_set_mmp_cur_pq_value(TRUE);
		}
		else if (e_type == RETAIL_MODE_TYPE_OVERLAY)
		{
			a_cfg_custom_set_pic_mode_vivid();
		}
}
#endif

static VOID  _nav_retail_resume_dlg_exit_fct(VOID)
{
    INT32 i4_ret = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    b_g_oobe_retail_pause_by_app = FALSE;

	a_cfg_custom_set_pic_mode_vivid();

    a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP,FALSE);

	a_cfg_cust_set_retail_mode_first_time_setting(ACFG_RETAIL_MODE_IS_NOT_FIRST_TIME_SETTING);
	a_cfg_custom_set_demo_type(0xF0);

    i4_ret = nav_retail_mode_go(NAV_RETAIL_MODE_EXIT);
    NAV_LOG_ON_FAIL(i4_ret);

    a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED);

    return;
}
static INT32 _nav_retail_resume_dlg_default_msg_proc(
                                            HANDLE_T            h_widget,
                                            UINT32              ui4_msg,
                                            VOID*               pv_param1,
                                            VOID*               pv_param2
                                            )
{

#ifdef APP_TTS_SUPPORT
    UTF16_T             w2s_tts_str[128] = {0};

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        if (ui4_keycode == BTN_CURSOR_LEFT)
        {
            c_memset(w2s_tts_str, 0, sizeof(w2s_tts_str));
            c_uc_w2s_strcpy(w2s_tts_str, MLM_NAV_TEXT(0, MLM_NAV_KEY_RETAIL_MODE_PAUSE_BTN));
            a_app_tts_play(w2s_tts_str, c_uc_w2s_strlen(w2s_tts_str));
        }
        else if (ui4_keycode == BTN_CURSOR_RIGHT)
        {
            c_memset(w2s_tts_str, 0, sizeof(w2s_tts_str));
            c_uc_w2s_strcpy(w2s_tts_str, MLM_NAV_TEXT(0, MLM_NAV_KEY_RETAIL_MODE_EXIT_BTN));
            a_app_tts_play(w2s_tts_str, c_uc_w2s_strlen(w2s_tts_str));
        }
    }
#endif
    return a_ui_simple_dialog_default_msg_proc(h_widget,
                                               ui4_msg,
                                               pv_param1,
                                               pv_param2);
}



/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_pause_dlg_show
 * Description  Show the retail mode dialog.
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_pause_dlg_show(VOID)
{
    INT32                   i4_ret  = NAVR_OK;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    /* if dialog is popup just return */
    if (NAV_RETAIL_MODE_POPUP_PAUSE_DLG == pt_this->e_popup_dlg)
    {
        return NAVR_OK;
    }

    /* disable screen saver */
    a_scrn_svr_set_enable(FALSE);

    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_pause_dlg,
                                         MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                         MLM_NAV_KEY_RETAIL_MODE_PAUSE_MSG));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);


    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_pause_dlg,
                                             MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                             MLM_NAV_KEY_RETAIL_MODE_PAUSE_BTN));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_set_no_text(pt_this->h_pause_dlg,
                                            MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                            MLM_NAV_KEY_RETAIL_MODE_EXIT_BTN));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    /* Set default focus button to Pause Demo */
    i4_ret = a_ui_simple_dialog_set_answer(pt_this->h_pause_dlg, TRUE);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);


    i4_ret = a_ui_simple_dialog_show(pt_this->h_pause_dlg);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_ui_simple_dialog_set_focus(pt_this->h_pause_dlg, FALSE);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);


    i4_ret = a_ui_simple_dialog_repaint(pt_this->h_pause_dlg);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    /*Hide logo after pause dialog show.*/
    i4_ret = retail_mode_view_logo_hide();
    NAV_CHK_FAIL(i4_ret);

    pt_this->e_popup_dlg = NAV_RETAIL_MODE_POPUP_PAUSE_DLG;

    a_amb_enable_system_key(FALSE);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_tts_str[256] = {0};

    c_uc_w2s_strcpy(w2s_tts_str, MLM_NAV_TEXT(0, MLM_NAV_KEY_RETAIL_MODE_PAUSE_MSG));
    c_uc_w2s_strcat(w2s_tts_str, (UTF16_T*)L".");
    c_uc_w2s_strcat(w2s_tts_str, MLM_NAV_TEXT(0, MLM_NAV_KEY_RETAIL_MODE_PAUSE_BTN));

    a_app_tts_play(w2s_tts_str, c_uc_w2s_strlen(w2s_tts_str));
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_pause_dlg_hide
 * Description
 *      Hide retail mode pause dialog
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_pause_dlg_hide(VOID)
{
    INT32 i4_ret = NAVR_OK;
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    _nav_retail_mode_dialog_hide(pt_this->h_pause_dlg);

    if(NAV_RETAIL_MODE_PAUSE == pt_this->e_status || _nav_retail_mode_get_running_type() == RETAIL_MODE_TYPE_OVERLAY )
    {
//        a_amb_enable_system_key(TRUE);
    }

    /* enable screen saver */
    a_scrn_svr_set_enable(TRUE);

    pt_this->e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;

    /*Show logo after pause dialog hide.*/
    i4_ret = _nav_retail_mode_check_logo();
    NAV_CHK_FAIL(i4_ret);

    nav_view_set_focus();

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_pause_dlg_pause_fct
 * Description
 *      Retail mode dialog callback funtion of button 'OK'.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_retail_pause_dlg_pause_fct(VOID)
{
    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    nav_retail_mode_go(NAV_RETAIL_MODE_PAUSE);

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_pause_dlg_exit_fct
 * Description
 *      Retail mode dialog callback funtion of button 'Cancel'.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_retail_pause_dlg_exit_fct(VOID)
{
    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    nav_retail_mode_go(NAV_RETAIL_MODE_EXIT);

    return;
}


INT32 nav_retail_mode_exit(VOID)
{
    INT32                   i4_ret  = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    i4_ret = nav_retail_mode_go(NAV_RETAIL_MODE_EXIT);
    NAV_CHK_FAIL(i4_ret);

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_exit_demo_mode
 * Description
 *      None
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_retail_mode_exit_demo_mode(VOID)
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;
    INT32                   i4_ret  = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    pt_this->e_resume_from_app = NAV_RETAIL_MODE_RESUME_FROM_NULL;
    pt_this->e_status = NAV_RETAIL_MODE_INITIAL;

    i4_ret = _nav_retail_mode_stop_play();
    NAV_LOG_ON_FAIL(i4_ret);

    /* reset to vivid immediately */
    if (pt_this->b_is_cfg_nfy_timer_start)
    {
        _nav_retail_mode_init_pic_mode();
        pt_this->b_is_ignore_pic_nfy = TRUE;
    }

#if 0
    /*set smart dimming to on*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING), (INT16)1);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
#endif

   // a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NO_PLAYING);
    a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
    a_icl_custom_set_demo_status(0);
    a_tv_custom_set_banner_visiable_allow(TRUE);
    a_cfg_custom_set_retail_mode_led_ctrl(FALSE);
    a_nav_power_set_component_enable(TRUE);


    /* if timer is running just stop it */
    i4_ret = _nav_retail_mode_stop_timer();
    NAV_LOG_ON_FAIL(i4_ret);

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_dialog_hide
 * Description
 *      Hide the retail mode dialog.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_dialog_hide(HANDLE_T h_dlg)
{
    INT32                   i4_ret  = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

#ifdef APP_TTS_SUPPORT
    a_app_tts_stop(APP_TTS_STOP_FORCE);
#endif

    i4_ret = a_ui_simple_dialog_hide(h_dlg);
    if (APP_UIR_OK != i4_ret)
    {
        DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        return NAVR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_repaint(h_dlg);
    if (APP_UIR_OK != i4_ret)
    {
        DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_dialog_deinit
 * Description
 *      Deinitialize the retail mode dialog.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_dialog_deinit(HANDLE_T h_dlg)
{
    INT32                   i4_ret  = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    if (NULL_HANDLE == h_dlg)
    {
        DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        return NAVR_INV_ARG;
    }

    i4_ret = a_ui_simple_dialog_hide(h_dlg);
    if (APP_UIR_OK != i4_ret)
    {
        DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        return NAVR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_repaint(h_dlg);
    if (APP_UIR_OK != i4_ret)
    {
        DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        return NAVR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_destory(h_dlg);
    if (APP_UIR_OK != i4_ret)
    {
        DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        return NAVR_FAIL;
    }
    return  NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_recover_wzd_stat
 * Description
 *      Recover wzd status,because set wzd status when run retail mode.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_recover_wzd_stat(VOID)
{
    UINT16      ui2_status    = 0;
    UINT8       ui1_state     = 0;
    UINT8       ui1_page_idx  = 0;

    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    {
        a_cfg_get_wzd_status(&ui2_status);
        ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
        ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);

        DBG_WARN(("[RETAIL MODE] status: [%u, %u].\n\r", ui1_state, ui1_page_idx));
    }

    if (ui1_state == WZD_STATE_RESUME_C4TV_END || pt_this->e_status == NAV_RETAIL_MODE_PAUSE )
    {
        //Fix DTV00871764
        //when pause demo-mode, wzd status change to WZD_STATE_RESUME_C4TV_END
        //then press exit key before demo-mode resume, cause OOBE launch
    }
    else if (ui1_state == WZD_STATE_RESUME_C4TV_RETAIL_MODE)
    {
        a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));
    }
    else
    {
        CHAR                s_app_name [APP_NAME_MAX_LEN+1] = {0};
        a_am_get_active_app (s_app_name);
          /* wzd to demo, then back to wzd, record the wzd status and resume wzd. */
        a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));
        if ( ( 0 != c_strcmp(s_app_name, MENU_NAME) ) && !b_g_oobe_retail_pause_by_app )
        {
            /*if menu key stop retail demo, do not resume wzd, keep up menu UI.*/
            DBG_INFO(("[RETAIL MODE]current active app: %s.==========\n\r", s_app_name));

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

                a_isl_get_num_rec(&ui1_src_num);

                for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
                {
                    i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);

                    if (i4_ret != NAVR_OK)
                    {
                        return i4_ret;
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

                acfg_tv_get_focus_win(&t_tv_win_id);
                a_nav_change_input_src(t_tv_win_id, t_isl_rec.ui1_id);
            }
            a_wzd_resume_c4tv(WZD_STATE_RESUME_C4TV,WZD_PAGE_INDEX_C4TV_START_OOBE);
        }
        b_g_oobe_retail_pause_by_app = FALSE;
    }

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      nav_retail_mode_send_cmd
 * Description
 *      Send command to Extern AM to paly retail mode video or flash.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
extern INT32 nav_retail_mode_send_cmd(BOOL b_start)
{
    UINT8                         ui1_demo_mode = 0;
    VSH_SRC_RESOLUTION_INFO_T     t_res;
    INT32                         i4_ret = 0;

    a_cfg_cust_get_demo_mode_value(&ui1_demo_mode);

    c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
    i4_ret = c_svctx_get_video_src_resolution(nav_get_crnt_svctx(),&t_res);
    NAV_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("[RETAIL MODE] [%s][%d] cmd: %d,ui1_demo_mode:%d,t_res.ui4_width:%d.\n\r", \
               __FUNCTION__,  __LINE__,(INT32)b_start,ui1_demo_mode, t_res.ui4_width));

    if ( a_is_oled_compensation_support())
    {
        return NAVR_OK;
    }
    else if (ui1_demo_mode == 2)
    {
        if (b_start == TRUE && t_res.ui4_width != 0)
        {
            if (a_c4tv_apron_check_cast_state() ==1)
            {
                a_stop_retail_demo();
            }
            return NAVR_OK;
        }
    }

    if (b_start == FALSE)
    {
        // note: retail demo is being moved to Conjure, and during
        // this transition the code below is moved to nav_retail_demo_go
        // if (a_c4tv_apron_check_cast_state() ==1)
        // {
        //     a_stop_retail_demo();
        // }
    }
    else
    {
    #ifdef APP_3D_RETAIL_DEMO_MODE
        /* if usb video is playing, just quit */
        if(nav_retail_mode_get_is_play() == TRUE)
        {
            return NAVR_OK;
        }
    #endif

        /* skip exit button when store demo is launching */
        //TODO

        /* start retail mode by model name */
        if (a_c4tv_apron_check_cast_state() == 0)
        {

            a_start_retail_demo();

        }


    }

    DBG_INFO(("[RETAIL MODE] [%s][%d] b_g_is_demo_flash_playing:%d \n", \
               __FUNCTION__, __LINE__, b_g_is_demo_flash_playing));

    b_g_is_demo_flash_playing = b_start;

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_cfg_change_reset_pic_mode
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_cfg_change_reset_pic_mode(
                    VOID*           pv_tag1,
                    VOID*           pv_tag2,
                    VOID*           pv_tag3
                    )
{
    ACFG_RETAIL_MODE_T      t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    /* not in retail mode */
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        /*reset every input sourch pic mode to vivid*/
		a_cfg_custom_set_pic_mode_vivid();
	}

    _nav_retail_mode_stop_cfg_nfy_timer();
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_cfg_change_timer_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_mode_cfg_change_timer_cb(
                    HANDLE_T        h_timer,
                    VOID*           pv_tag
                    )
{
    nav_request_context_switch(_nav_retail_cfg_change_reset_pic_mode, NULL, NULL, NULL);
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_cfg_change_timer_start
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_cfg_change_timer_start(VOID)
{
    _nav_retail_mode_start_cfg_nfy_timer();
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_cfg_change_msg_hdlr
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_cfg_change_msg_hdlr(
                    VOID*           pv_unused1,
                    VOID*           pv_unused2,
                    VOID*           pv_unused3
                    )
{
    _nav_retail_cfg_change_timer_start();
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_cfg_change_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_cfg_change_cb(
                    UINT16          ui2_nfy_id,
                    VOID*           pv_tag,
                    UINT16          ui2_id
                    )
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;
    ACFG_RETAIL_MODE_T      t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    UINT16                  ui2_pic_mode_idx = 0;

    if (pt_this->ui2_cfg_nfy_id_pic_mode != ui2_nfy_id)
    {
        return;
    }

    /* not in retail mode */
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL != t_retail_mode)
    {
        return;
    }

    /* ignore retail mode picture action */
    if (pt_this->b_is_ignore_pic_nfy)
    {
        return;
    }

	/*if current demo is not overlay ,return */
	if (pt_this->e_running_type != RETAIL_MODE_TYPE_OVERLAY)
	{
		return;
	}

    /* if current PQ mode is vivid, just return */;
    ui2_pic_mode_idx = _nav_retail_mode_get_pq_idx();

    if (3 == ui2_pic_mode_idx)
    {
        return;
    }

    /* not only picture mode group change */
    /* post a message to itself */
    nav_request_context_switch(_nav_retail_cfg_change_msg_hdlr,
                               NULL,
                               NULL,
                               NULL);

    return;
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_pq_change_icl_nfy_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_retail_pq_change_icl_nfy_cb(UINT16    ui2_nfy_id,
                                              VOID*     pv_tag,
                                              ICL_NOTIFY_DATA_T* pt_notify_data)
{
    INT32               i4_ret;
    ICL_GRPID_TYPE      e_grp_id;
    UINT8               ui1_status = ICL_PQ_CHANGE_NOTHING;
    ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    if (e_grp_id != ICL_GRPID_PQ_CHANGE_STATUS)
    {
        return NAVR_OK;
    }

    /* not in retail mode */
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL != t_retail_mode)
    {
        return NAVR_OK;
    }

    /* ignore retail mode picture action */
    if (pt_this->b_is_ignore_pic_nfy)
    {
        return NAVR_OK;
    }

    /* get download status */
    i4_ret = a_icl_custom_get_pq_chg_status(&ui1_status);
    if (ICLR_OK != i4_ret)
    {
        return NAVR_OK;
    }

	/*if current demo is not overlay ,return */
	if (pt_this->e_running_type != RETAIL_MODE_TYPE_OVERLAY)
	{
		return NAVR_OK;
	}

    if (ICL_PQ_CHANGE_NOTHING != ui1_status)
    {
        /* post a message to itself */
        nav_request_context_switch(_nav_retail_cfg_change_msg_hdlr,
                                   NULL,
                                   NULL,
                                   NULL);
    }

    return NAVR_OK;
}

static RETAIL_MODE_RUNNING_TYPE_T _nav_retail_mode_check_running_type(VOID)
{
    INT32      i4_ret;
    UINT8      ui1_demo_mode = 0;
    UINT8      ui1_demo_type = 0;
    UINT8      ui1_demo_idx;

    a_cfg_cust_get_demo_mode_value(&ui1_demo_mode);
    a_cfg_custom_get_demo_type(&ui1_demo_type);

	if(ui1_demo_mode == 0)
    {
    	ui1_demo_idx = (UINT8)_get_backup_demo_idx();
		if (ui1_demo_idx == 0)
		{
			a_cfg_cust_set_demo_mode_value(1);
		}
		else
		{
			a_cfg_cust_set_demo_mode_value(ui1_demo_idx);
		}
    }

    if (nav_retail_check_end_cap() == TRUE)
    {
        return RETAIL_MODE_TYPE_VIDEO;
    }


    {
        VSH_SRC_RESOLUTION_INFO_T     t_res;
        c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
        i4_ret = c_svctx_get_video_src_resolution(nav_get_crnt_svctx(),&t_res);
        NAV_LOG_ON_FAIL(i4_ret);
        if ((t_res.ui4_width != 0 || (b_last_input_signal_locked) || ui1_chg_to_signal_input != 0x0F) &&
			a_mmp_get_ap_status() != MMP_MAIN_AP_STATUS_RESUMED &&
			ui1_demo_type != 1)
        {
            ui1_chg_to_signal_input = 0x0F;
            return RETAIL_MODE_TYPE_OVERLAY;
        }
    }

    {
        if (nav_retail_internal_demo_check() == TRUE && ui1_demo_type != 2) /* TODO: internal video present & no signal */
        {
            return RETAIL_MODE_TYPE_VIDEO_INTERNAL;
        }
    }

    /* default */
    return RETAIL_MODE_TYPE_OVERLAY;
}

static INT32 _nav_retail_set_next_language(VOID)
{
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;
    UINT8               ui1_idx = 0;
    ISO_639_LANG_T      s639_lang = {0};
    UINT8               ui1_array_size = 0;
    CHAR *              ps639_lang_array[] =
    {
        s639_app_cfg_lang_eng,
        s639_app_cfg_lang_spa,
        s639_app_cfg_lang_fre
    };

    ui1_array_size = sizeof(ps639_lang_array)/sizeof(ps639_lang_array[0]);

    a_cfg_get_gui_lang(s639_lang);

    for (ui1_idx = 0; ui1_idx < ui1_array_size; ui1_idx++)
    {
        if (c_strncmp(s639_lang, ps639_lang_array[ui1_idx], ISO_639_LANG_LEN) == 0)
        {
            break;
        }
    }

    ui1_idx = (ui1_idx + 1 >= ui1_array_size) ? 0 : ui1_idx + 1;

    DBG_INFO(("[RETAIL MODE] change lang to %s.\n\r", ps639_lang_array[ui1_idx]));

    a_cfg_set_gui_lang(ps639_lang_array[ui1_idx]);
    a_tv_custom_set_lang(ui1_idx);
#ifdef LINUX_TURNKEY_SOLUTION
    a_tv_custom_set_3rd_app_info();
#endif
    a_vkb_set_lang(ps639_lang_array[ui1_idx]);

    /* show toast msg */
    WDK_TOAST_T* pt_toast = (WDK_TOAST_T*)c_mem_alloc(sizeof(WDK_TOAST_T));
    if (pt_toast != NULL)
    {
        c_memset((VOID*)pt_toast, 0, sizeof(WDK_TOAST_T));

        pt_toast->e_toast_style  = WDK_STRING_TOAST;
        pt_toast->e_string_style = WDK_STRING_ID_ID;
        pt_toast->style.style_2.ui4_id_1  = MLM_SETTINGS_KEY_MENU_LANG;
        pt_toast->style.style_2.ui4_id_2  = MLM_SETTINGS_KEY_MENU_LANG_ENG;

        nav_send_msg_to_component(
                        NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                        NAV_UI_MSG_REST_NOTIFICATION,
                        (VOID*)pt_toast);
    }

    /* restart demo mode */
    if (pt_this->e_status == NAV_RETAIL_MODE_RUNNING)
    {
        a_restart_retail_demo();
    }

    return NAVR_OK;
}

static INT32 _retail_mode_launch_msg_key_proc(UINT32 ui4_keycode, BOOL *pb_processed)
{
    INT32 i4_ret = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] keycode : 0x%X \r\n", __FUNCTION__, ui4_keycode));

    switch (ui4_keycode)
    {
        case BTN_VOL_DOWN:
        case BTN_VOL_UP:
        case BTN_MUTE:
        {
            if (a_wzd_is_oobe_mode())
            {
                *pb_processed = FALSE;
            }
            else
            {
                if((b_g_oobe_retail_mute_before_power_off)&&(ui4_keycode == BTN_MUTE))
                {
                    b_g_oobe_retail_mute_before_power_off = FALSE;
                    *pb_processed = FALSE;
                }
                *pb_processed = TRUE;
            }
            break;
        }
        case BTN_SELECT:
        {
            if (a_wzd_is_oobe_mode())
            {
                DBG_INFO(("[RETAIL MODE] is oobe mode.\n\r"));
            }
            *pb_processed = TRUE;
            break;
        }
        case BTN_POWER:
        case BTN_CUSTOM_11:
        {
            *pb_processed = TRUE;
            break;
        }
        case BTN_EXIT:
        case BTN_INPUT_SRC:
        case BTN_ASPECT://wide
        case BTN_LINK:
        //case BTN_PIP_CH_DOWN://link
        case BTN_CC:
        case BTN_PRG_UP://channel up
        case BTN_PRG_DOWN://channel down
        case BTN_P_EFFECT://pic
//        case BTN_WIDGET: //via
        case BTN_LONG_INPUT:
        {
            i4_ret = nav_retail_mode_exit_launch_msg();
            NAV_CHK_FAIL(i4_ret);
            *pb_processed = TRUE;
            break;
        }
        default:
        {
            *pb_processed = TRUE;
            break;
        }
    }

    return NAVR_OK;
}

static INT32 _retail_mode_pause_dlg_key_proc(UINT32 ui4_keycode)
{
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;
    INT32 i4_ret = NAVR_OK;

//    DBG_INFO(("[RETAIL MODE] [%s] keycode : 0x%X \r\n", __FUNCTION__, ui4_keycode));

    switch (ui4_keycode)
    {
        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
        case BTN_SELECT:
        {
            break;
        }
		case BTN_RETURN:
        case BTN_EXIT:
        {
            i4_ret = _nav_retail_pause_dlg_hide();
            NAV_CHK_FAIL(i4_ret);
            return NAVR_OK;
        }
        default:
        {
            return NAVR_OK;
        }
    }

    _nav_retail_pause_dlg_default_msg_proc(pt_this->h_pause_dlg, (UINT32)WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);

    return NAVR_OK;
}

static INT32 _retail_mode_resume_dlg_key_proc(UINT32 ui4_keycode)
{
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;
    INT32 i4_ret = NAVR_OK;

//    DBG_INFO(("[RETAIL MODE] [%s] keycode : 0x%X \r\n", __FUNCTION__, ui4_keycode));

    switch (ui4_keycode)
    {
        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
        case BTN_SELECT:
        {
            break;
        }
		case BTN_RETURN:
        case BTN_EXIT:
        {
            i4_ret = _nav_retail_resume_dlg_hide();
            NAV_CHK_FAIL(i4_ret);
            return NAVR_OK;
        }
        default:
        {
            return NAVR_OK;
        }
    }

    _nav_retail_resume_dlg_default_msg_proc(pt_this->h_resume_dlg, (UINT32)WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);

    return NAVR_OK;
}

static INT32 _retail_mode_info_dlg_key_proc(UINT32 ui4_keycode)
{
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;
    INT32 i4_ret = NAVR_OK;

//    DBG_INFO(("[RETAIL MODE] [%s] keycode : 0x%X \r\n", __FUNCTION__, ui4_keycode));

    switch (ui4_keycode)
    {
        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
        case BTN_SELECT:
        {
            break;
        }
		case BTN_RETURN:
        case BTN_EXIT:
        {
            i4_ret = _nav_retail_info_dlg_hide();
            NAV_CHK_FAIL(i4_ret);
            return NAVR_OK;
        }
        default:
        {
            return NAVR_OK;
        }
    }
    a_ui_simple_dialog_default_msg_proc(pt_this->h_info_dlg, (UINT32)WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);

    return NAVR_OK;
}

extern BOOL vol_banber_is_show_state(VOID);
static INT32 _retail_mode_handle_key_for_oobe(UINT32 ui4_keycode)
{
    UINT16              ui2_status     = 0;
    UINT8               ui1_page_idx   = 0;

    a_cfg_get_wzd_status(&ui2_status);

    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);

	if (ui4_keycode != BTN_INPUT_SRC)
	{
		rest_event_notify("key_command", ui4_keycode, "");
	}

    switch (ui4_keycode)
    {
#if 0
        case BTN_INPUT_SRC:
        {
            DBG_INFO(("[RETAIL MODE] received BTN_INPUT_SRC.\n\r");

            if (ui1_page_idx == WZD_PAGE_INDEX_C4TV_START_OOBE ||
                ui1_page_idx == WZD_PAGE_INDEX_C4TV_DEVICE_PAIR ||
                ui1_page_idx == WZD_PAGE_INDEX_C4TV_LINK_START)
            {
                //a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
                {
        			RETAIL_MODE_PARAM_T t_param;
                    INT32           i4_ret;
        			c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));
        			t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_NULL;
        			t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
        			t_param.t_launch_info.ui2_count = 15;
        			i4_ret = a_nav_retail_mode_start(&t_param);
        			NAV_LOG_ON_FAIL(i4_ret);
        		}
            }
            break;
        }

		case BTN_MUTE:
		{
            DBG_INFO(("[RETAIL MODE] received BTN_INPUT_SRC,ui1_page_idx:%d.\n\r",ui1_page_idx));

            if (ui1_page_idx == WZD_PAGE_INDEX_C4TV_START_OOBE ||
                ui1_page_idx == WZD_PAGE_INDEX_C4TV_DEVICE_PAIR ||
                ui1_page_idx == WZD_PAGE_INDEX_C4TV_LINK_START)
            {
                //a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
                {
        			RETAIL_MODE_PARAM_T t_param;
                    INT32           i4_ret;
        			c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));
        			t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_NULL;
        			t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
        			t_param.t_launch_info.ui2_count = 15;
        			i4_ret = a_nav_retail_mode_start(&t_param);
        			NAV_LOG_ON_FAIL(i4_ret);
        		}
            }
            break;
        }
#endif
        case BTN_VOL_UP:
		case BTN_VOL_DOWN:
        case BTN_MUTE:
        {
			if (vol_banber_is_show_state() == FALSE)
			{
				DBG_INFO(("[RETAIL MODE] received vol+/-/mute.\n\r"));
				/* rusume nav for exit retail mode case */
                nav_resume_self();
			    a_amb_default_key_handler(WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);
			}

            break;
        }

        case BTN_EXIT:
        {
            DBG_INFO(("[RETAIL MODE] received BTN_EXIT.\n\r"));

            if (ui1_page_idx == WZD_PAGE_INDEX_C4TV_START_OOBE ||
                ui1_page_idx == WZD_PAGE_INDEX_C4TV_DEVICE_PAIR ||
                ui1_page_idx == WZD_PAGE_INDEX_C4TV_LINK_START)
            {
                b_ir_exit_key = TRUE;
                a_nav_link_mode_set_mode(NAV_LINK_MODE_INITIAL);
                a_cfg_cust_set_ipts_select_state(IPTS_SELECT_NULL);

                //TODO: env reset
            }

            break;
        }
        case BTN_P_EFFECT:
        {
            DBG_INFO(("[RETAIL MODE] received BTN_P_EFFECT.\n\r"));

            if (WZD_PAGE_INDEX_C4TV_IR_REMOTE == ui1_page_idx)
            {
                a_amb_default_key_handler_ex(WGL_MSG_KEY_DOWN, (VOID*)BTN_P_EFFECT, (VOID*)NULL);
            }

            break;
        }
        default:
        {
           /* nothing to do*/
           // DBG_INFO(("[RETAIL MODE] received %u, systen layer no special handling.\n\r", ui4_keycode));
        }
    }

    return NAVR_OK;
}

BOOL a_retail_mode_get_ir_exit_key_state(VOID)
{
    return b_ir_exit_key;
}

VOID a_retail_mode_set_ir_exit_key_state(BOOL b_val)
{
    DBG_INFO(("[RETAIL MODE] [%s] b_ir_exit_key : 0x%X \r\n", __FUNCTION__, b_val));

    b_ir_exit_key = b_val;
}

BOOL a_retail_mode_is_sec_press_play_pause_key(VOID)
{
    BOOL  b_tmp_state = FALSE;

    b_tmp_state = b_2th_press_play_pause_key;
    b_2th_press_play_pause_key = FALSE;

    return b_tmp_state;
}

static INT32 _retail_mode_handle_key_for_overlay(UINT32 ui4_keycode)
{
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;
    UINT32              ui4_keygroup = IOM_GET_EVT_GRP(ui4_keycode);
    INT32               i4_ret = NAVR_OK;

    if(0)
    {
        RETAIL_MODE_RUNNING_TYPE_T e_type = _nav_retail_mode_get_running_type();

        if( e_type != RETAIL_MODE_TYPE_OVERLAY)
        {
            NAV_CHK_FAIL(NAVR_NO_ACTION);
        }
    }


    /* ignore BTN_PLAY/BTN_PAUSE/BTN_CURSOR_LEFT/... */
    if (ui4_keygroup == KEY_GROUP_STRM_CTRL)
    {
        DBG_WARN(("[RETAIL MODE] keycode group is KEY_GROUP_STRM_CTRL, no action !!!\n\r"));
        return NAVR_OK;
    }
    else if (ui4_keygroup == KEY_GROUP_CURSOR)
    {
        DBG_WARN(("[RETAIL MODE] keycode group is KEY_GROUP_CURSOR, no action !!!\n\r"));
        return NAVR_OK;
    }

    switch (ui4_keycode)
    {
        case BTN_SELECT:
        case BTN_RETURN:
        case BTN_ENTER:

        {
            DBG_WARN(("[RETAIL MODE] received %u, no action !!!\n\r", ui4_keycode));
            break;
        }
        /*DTV00883343 WST][TMC-3321][WSQA]Store demo is enabled,press the CH+/- key in the external input source, TV will switch to the TV source*/
        case BTN_PRG_UP:
        case BTN_PRG_DOWN:
        {   ISL_REC_T  t_isl_rec;
            nav_get_isl_rec(TV_WIN_ID_MAIN, &t_isl_rec);
            if(INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
            {
                nav_rcu_key_handler(ui4_keycode);
            }
            else
            {
                DBG_WARN(("[RETAIL MODE] received %u, no action !!!\n\r", ui4_keycode));
            }
            break;
        }

        case BTN_EXIT:
        {
            DBG_WARN(("[RETAIL MODE] received BTN_EXIT, status: %d.\n\r", pt_this->e_status));
			if(0) //DTV00938708 [VIZIO][TMC-4742][SPRINT2]Demo mode, press EXIT, pop up with Resume and Exit buttons
			{
	            if(pt_this->e_status == NAV_RETAIL_MODE_RUNNING)
	            {
	                i4_ret = _nav_retail_pause_dlg_show();
	                NAV_CHK_FAIL(i4_ret);
	            }
	            else if(pt_this->e_status == NAV_RETAIL_MODE_PAUSE)
	            {
	                i4_ret = _nav_retail_resume_dlg_show();
	                NAV_CHK_FAIL(i4_ret);
	            }
			}
            if((pt_this->e_status == NAV_RETAIL_MODE_RUNNING)||
               (pt_this->e_status == NAV_RETAIL_MODE_PAUSE))
            {

		        i4_ret = _nav_retail_resume_dlg_show();
            }
            NAV_CHK_FAIL(i4_ret);
            break;
        }
        case BTN_LONG_INPUT:
        {
            DBG_WARN(("[RETAIL MODE] received BTN_LONG_INPUT.\n\r"));
            break;
        }
        case BTN_KB_MINUS_SIGN:
        {
            DBG_WARN(("[RETAIL MODE] received BTN_KB_MINUS_SIGN.\n\r"));
            _nav_retail_set_next_language();
            nav_rcu_key_handler(ui4_keycode);
            break;
        }
        case BTN_CC:
            DBG_WARN(("[RETAIL MODE] received BTN_CC.\n\r"));
            break;

        default:
        {
            if(ui4_keycode == BTN_INPUT_SRC || ui4_keycode == BTN_PRG_INFO)
            {
                b_g_oobe_retail_pause_by_app = TRUE;


                if (retail_mode_view_show_fift_minute())
                {
                    DBG_INFO(("[RETAIL MODE]received BTN_INPUT_SRC or BTN_PRG_INFO exit retail mode and reset timer 15min.\n\r"));
                    nav_retail_mode_go(NAV_RETAIL_MODE_EXIT);
                    _nav_retail_mode_exit_demo_mode();

                    retail_mode_view_timer_start(RETAIL_MODE_VIEW_TIMER_DEVICE_PAIR, OOBE_DEVICE_PAIR_TIMEOUT);
                }
                else
                {
                    DBG_INFO(("[RETAIL MODE]received BTN_INPUT_SRC or BTN_PRG_INFO pause retail mode.\n\r"));
                    nav_retail_mode_go(NAV_RETAIL_MODE_PAUSE);
                    if(ui4_keycode == BTN_PRG_INFO)
                        a_tv_custom_set_banner_visiable_allow(TRUE);
                }
            }

            DBG_WARN(("[RETAIL MODE] received %x, dispatch to nav rcu.\n\r", ui4_keycode));
            nav_rcu_key_handler(ui4_keycode);
            break;
        }
    }

    return NAVR_OK;
}

static VOID _nav_retail_hide_resume_dlg_timer_cb_context(
                    VOID*           pv_tag1,
                    VOID*           pv_tag2,
                    VOID*           pv_tag3
                    )
{
	INT32 i4_ret = NAVR_OK;

	b1_hide_resume_dlg_timer = FALSE;

	i4_ret = _nav_retail_resume_dlg_hide();
}

static VOID _nav_retail_hide_resume_dlg_timer_cb(
                    HANDLE_T        h_timer,
                    VOID*           pv_tag
                    )
{
    DBG_INFO(("[RETAIL MODE] [%s] \r\n", __FUNCTION__));

    nav_request_context_switch(_nav_retail_hide_resume_dlg_timer_cb_context, NULL, NULL, NULL);
}

extern BOOL usb_file_is_playing(VOID);
extern INT32 a_vol_ctrl_hide (VOID);

static INT32 _retail_mode_handle_key_for_video(UINT32 ui4_keycode)
{
    INT32 i4_ret = NAVR_OK;

    RETAIL_MODE_RUNNING_TYPE_T e_type = _nav_retail_mode_get_running_type();

    if( e_type != RETAIL_MODE_TYPE_VIDEO && e_type != RETAIL_MODE_TYPE_VIDEO_INTERNAL && e_type != RETAIL_MODE_TYPE_OVERLAY)
    {
        NAV_CHK_FAIL(NAVR_NO_ACTION);
    }

    switch (ui4_keycode)
    {
    	case BTN_RETURN:
        case BTN_EXIT:
        {
            _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;
            if(pt_this->e_status != NAV_RETAIL_MODE_RUNNING)
            {
                NAV_CHK_FAIL(NAVR_NO_ACTION);
            }

			a_vol_ctrl_hide();
            i4_ret = _nav_retail_resume_dlg_show();
            NAV_CHK_FAIL(i4_ret);

			c_timer_stop(pt_this->h_dialag_hide_timer);
			c_timer_start(pt_this->h_dialag_hide_timer,
					(DLG_HIDE_AFTER_90_SECOND*1000),
					X_TIMER_FLAG_ONCE,
					_nav_retail_hide_resume_dlg_timer_cb,
					NULL);
			b1_hide_resume_dlg_timer = TRUE;

            break;
        }
        case BTN_LONG_INPUT:
        {
            i4_ret = nav_retail_mode_go(NAV_RETAIL_MODE_EXIT);
            NAV_CHK_FAIL(i4_ret);
            break;
        }
        #if 0
        case BTN_SELECT:
        {

             if( e_type != RETAIL_MODE_TYPE_VIDEO)
             {
                 DBG_WARN(("[RETAIL MODE] select key only for retail demo from usb\n\r"));
                 return NAVR_OK;
             }

             if( nav_retail_mode_get_is_video_paused() == FALSE)
             {
                 i4_ret = nav_retail_end_cap_ctrl_video(NAV_RETAIL_END_CAP_PAUSE);
                 NAV_CHK_FAIL(i4_ret);
             }
             else if( nav_retail_mode_get_is_video_paused() == TRUE)
             {
                 i4_ret = nav_retail_end_cap_ctrl_video(NAV_RETAIL_END_CAP_PLAY);
                 NAV_CHK_FAIL(i4_ret);
             }
             else
             {
                /*unknow*/
             }

             break;
        }
        #endif
        case BTN_PLAY:
        {
             /* TRUE play | FALSE pause */
             if( nav_retail_mode_get_is_video_paused() == FALSE)
             {
                DBG_WARN(("[RETAIL MODE] video is play\n\r"));
                return NAVR_OK;
             }
             i4_ret = nav_retail_end_cap_ctrl_video(NAV_RETAIL_END_CAP_PLAY);
             NAV_CHK_FAIL(i4_ret);
             break;
        }
        #if 1 //DTV00943089 [VIZIO][TMC-4831][SPRINT2] No pause of embedded demo mode content
        case BTN_PAUSE:
        {
			/*Only take effect in USB video*/
			if (usb_file_is_playing() == TRUE)
			{
				/* TRUE play | FALSE pause */
				if( nav_retail_mode_get_is_video_paused() == TRUE)
				{
				   DBG_WARN(("[STORE] video is pause\n\r"));
				   return NAVR_OK;
				}
				i4_ret = nav_retail_end_cap_ctrl_video(NAV_RETAIL_END_CAP_PAUSE);
				NAV_CHK_FAIL(i4_ret);
			}

             break;

        }
		case BTN_POWER:
		{
			if (a_am_is_power_on)
			{
				i4_ret = nav_set_mute(TRUE);
				NAV_CHK_FAIL(i4_ret);
			}

			break;
		}

        #endif
        default:
        {
			if ((BTN_VOL_UP == ui4_keycode)   ||
				(BTN_VOL_DOWN == ui4_keycode) ||
				(BTN_MUTE == ui4_keycode))
			{
				if (vol_banber_is_show_state() == FALSE)
				{
					nav_rcu_key_handler(ui4_keycode);
				}
			}
            DBG_INFO(("[RETAIL MODE] received %u, no action !!!\n\r", ui4_keycode));
            break;
        }
    }

    return NAVR_OK;
}

extern BOOL a_oled_compensation_is_running();

/*----------------------------------------------------------------------------
 * Name: _nav_retail_iom_nfy_hdlr
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_iom_nfy_hdlr(
    VOID*                               pv_nfy_cond,
    VOID*                               pv_evt_code,
    VOID*                               pv_data)
{
    /* here will the following condition:
         * 1. retail mode mode;
         * 2. retail mode in paused status;
         * 3. the current active app is menu;
         */
   /* if the above condition all satified will reset the pause timer*/
    INT32                       i4_ret = NAVR_OK;
    CHAR                        s_active_app[APP_NAME_MAX_LEN+1] = {0};
    CHAR                        s_next_active_app[APP_NAME_MAX_LEN+1] = {0};
    ACFG_RETAIL_MODE_T          t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    _NAV_RETAIL_MODE_T*         pt_this = &t_g_retail_mode;

    UINT32                      ui4_keycode = IOM_GET_EVT_GRP_ID((UINT32)pv_evt_code);
    BOOL                        b_is_processed = FALSE;
    IOM_NFY_COND_T              e_nfy_cond = (IOM_NFY_COND_T)((UINT32)pv_nfy_cond);

    if (IOM_NFY_COND_BTN_REPEAT == e_nfy_cond && FALSE == a_wzd_is_oobe_mode())
    {
        /*Only handle repeat key on OOBE mode*/
        return;
    }

    if(a_oled_compensation_is_running())
    {
        return ;
    }

    if(nav_get_active_component() == NAV_COMP_ID_DIALOG)
    {
        DBG_INFO(("[RETAIL MODE][%s %d] NAV_COMP_ID_DIALOG showing \n",__FUNCTION__,__LINE__));
        return ;
    }

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    if (retail_mode_view_is_on() == TRUE)
    {
        if (!( (a_wzd_is_oobe_mode() == TRUE) && (ui4_keycode == BTN_INPUT_SRC) //For OOBE launch demo mode,short press panel input will be ignore
             &&(IOM_GET_EVT_SRC((UINT32)pv_evt_code) == KEY_SRC_FRONT_PANEL) ) )
        {
            i4_ret = _retail_mode_launch_msg_key_proc(ui4_keycode, &b_is_processed);
            NAV_LOG_ON_FAIL(i4_ret);
        }
        if (b_is_processed)
        {
            return;
        }
    }

	if (ui4_keycode != BTN_CC)
	{
	    rest_event_notify("ir_command", ui4_keycode, "");
	}

	if (ui4_keycode == BTN_CURSOR_LEFT ||
        ui4_keycode == BTN_CURSOR_RIGHT )
	{
		if (b1_hide_resume_dlg_timer == TRUE)
		{
			c_timer_stop(pt_this->h_dialag_hide_timer);
			c_timer_start(pt_this->h_dialag_hide_timer,
					(DLG_HIDE_AFTER_90_SECOND*1000),
					X_TIMER_FLAG_ONCE,
					_nav_retail_hide_resume_dlg_timer_cb,
					NULL);
		}
	}
	else if (ui4_keycode == BTN_SELECT)
	{
		if (b1_hide_resume_dlg_timer == TRUE)
		{
			c_timer_stop(pt_this->h_dialag_hide_timer);
		}
	}


    if (NAV_RETAIL_MODE_POPUP_PAUSE_DLG == pt_this->e_popup_dlg)
    {
        _retail_mode_pause_dlg_key_proc(ui4_keycode);
        return;
    }

    if (NAV_RETAIL_MODE_POPUP_RESUME_DLG == pt_this->e_popup_dlg)
    {
        _retail_mode_resume_dlg_key_proc(ui4_keycode);
        return;
    }
    if (NAV_RETAIL_MODE_POPUP_INFO_DLG == pt_this->e_popup_dlg)
    {
        _retail_mode_info_dlg_key_proc(ui4_keycode);
        return;
    }

    //rest_event_notify("key_command", ui4_keycode, "");
    DBG_INFO(("[chris] receive key %d", ui4_keycode));
	if (ui4_keycode == BTN_POWER
		|| ui4_keycode == BTN_INPUT_SRC
		|| ui4_keycode == BTN_MENU
		|| ui4_keycode == BTN_PRG_INFO
		|| ui4_keycode == BTN_VOL_UP
		|| ui4_keycode == BTN_VOL_DOWN
		|| ui4_keycode == BTN_MUTE
		|| ui4_keycode == BTN_CC
		|| ui4_keycode == BTN_P_EFFECT
		|| ui4_keycode == BTN_ASPECT
		|| ui4_keycode == BTN_LINK
		|| ui4_keycode == BTN_PRG_UP
		|| ui4_keycode == BTN_PRG_DOWN
		|| ui4_keycode == BTN_PREV_PRG)
	{
		#ifdef SYS_MTKTVAPI_SUPPORT
		a_mtktvapi_config_update_inscape_nfy(ACFG_MSG_INSCAP_KEY_CALLBACK,(VOID*)ui4_keycode);
		#endif
	}
    if (ui4_keycode == BTN_WIDGET
        || ui4_keycode == BTN_VUDU
        || ui4_keycode == BTN_AMAZON
        || ui4_keycode == BTN_XUMO
        || ui4_keycode == BTN_CRACKLE
        || ui4_keycode == BTN_HULU
        || ui4_keycode == BTN_IHEART_RADIO
        || ui4_keycode == BTN_NETFLIX
        || ui4_keycode == BTN_WATCHFREE
        || ui4_keycode == BTN_REDBOX
        || ui4_keycode == BTN_HAYSTACK
        || ui4_keycode == BTN_DISNEY
        || ui4_keycode == BTN_PEACOCK
        || ui4_keycode == BTN_TUBI
        || ui4_keycode == BTN_PARTNER_1
        || ui4_keycode == BTN_PARTNER_2
        || ui4_keycode == BTN_PARTNER_3
        || ui4_keycode == BTN_PARTNER_4
        || ui4_keycode == BTN_PARTNER_5
        || ui4_keycode == BTN_PARTNER_6
        || ui4_keycode == BTN_PARTNER_7
        || ui4_keycode == BTN_PARTNER_8
        || ui4_keycode == BTN_PARTNER_9
        || ui4_keycode == BTN_PARTNER_10
        || ui4_keycode == BTN_PARTNER_11
        || ui4_keycode == BTN_PARTNER_12
        || ui4_keycode == BTN_PARTNER_13
        || ui4_keycode == BTN_PARTNER_14
        || ui4_keycode == BTN_PARTNER_15
        || ui4_keycode == BTN_PARTNER_16
        || ui4_keycode == BTN_PARTNER_17
        || ui4_keycode == BTN_PARTNER_18
        || ui4_keycode == BTN_PARTNER_19
        || ui4_keycode == BTN_PARTNER_20)
    {
    	#ifdef SYS_MTKTVAPI_SUPPORT
		a_mtktvapi_config_update_inscape_nfy(ACFG_MSG_INSCAP_KEY_CALLBACK,(VOID*)ui4_keycode);
		#endif
        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

        if (t_retail_mode == ACFG_RETAIL_MODE_NORMAL)
        {
            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
            if(t_retail_mode == ACFG_RETAIL_MODE_NORMAL)
            {
                DBG_INFO(("[RETAIL MODE] Partner keys, in store demo reject.\n\r"));
                return;
            }
        }

        if (nav_is_channel_scan_active())
        {
            DBG_INFO(("[RETAIL MODE] Partner keys, during channel scan reject.\n\r"));
            return;
        }
        menu_blank_oled_scrn_timer_refresh();

        //Add for DTV937675, no handle hot key in blank screen
        if(menu_custom_is_blank_screen())
        {
            DBG_INFO(("[RETAIL MODE] No need to handle in blank screen and unblank.\n\r"));
            menu_custom_unblank_screen(ui4_keycode);
            return;
        }
        banner_hide_msg();
        /* workaround ps: sometime (in usb) msgconvert _hotkey_handle will call at the same time */
        if(ui4_keycode == BTN_WIDGET)
        {
#ifdef APP_TTS_SUPPORT
            UTF16_T w2s_str[128] = {0};
            c_uc_ps_to_w2s("SmartCast TV", w2s_str, 128);
            a_app_tts_play(w2s_str, 128);
#endif
            DBG_INFO(("[RETAIL MODE] hotkey VIA.\n\r"));
        }

        DBG_INFO(("[RETAIL MODE] Partner keys, stop key forwarding on native side. Pass to rest.\n\r"));
        rest_event_notify("key_command", ui4_keycode, "");

        return;
    }

    if (a_wzd_is_oobe_mode() && a_c4tv_apron_check_cast_state())
    {
        _retail_mode_handle_key_for_oobe(ui4_keycode);
        DBG_INFO(("[RETAIL MODE] In OOBE procedure, stop key forwarding to other modules.\n\r"));
        return;
    }

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (t_retail_mode != ACFG_RETAIL_MODE_NORMAL)
    {
        return;
    }

    a_am_get_active_app(s_active_app);
    a_am_get_next_active_app (s_next_active_app);

    DBG_WARN(("[RETAIL MODE] active_app: %s, next_active_app: %s.\n\r", s_active_app, s_next_active_app));
#if 0
    /* ignore exit ir key for app resuming */
    if (c_strcmp(s_next_active_app, NAV_NAME) != 0 && ui4_keycode == BTN_EXIT)
    {
        return;
    }
#endif
    if ((pt_this->e_resume_from_app == NAV_RETAIL_MODE_RESUME_FROM_NULL)
        && (c_strcmp(s_active_app, MENU_NAME) == 0)
        && (NAV_RETAIL_MODE_PAUSE == pt_this->e_status))
    {
        _nav_retail_mode_start_pause_timer();
    }

    if ((NAV_RETAIL_MODE_RUNNING == pt_this->e_status) &&
        (pt_this->e_running_type == RETAIL_MODE_TYPE_VIDEO ||
         pt_this->e_running_type == RETAIL_MODE_TYPE_VIDEO_INTERNAL ||
         pt_this->e_running_type == RETAIL_MODE_TYPE_OVERLAY
        ))
    {
        _retail_mode_handle_key_for_video(ui4_keycode);
        return;
    }
#if 0
    do
    {
        b_is_processed = TRUE;

        if (c_strcmp(s_active_app, NAV_NAME) != 0)
        {
            break;
        }

        if (FALSE == nav_any_component_visible())
        {
            b_is_processed = FALSE;
            break;
        }

        if (nav_get_active_component() == NAV_COMP_ID_SCREEN_SAVER ||
            nav_is_component_visible(NAV_COMP_ID_SCREEN_SAVER))
        {
            b_is_processed = FALSE;
            break;
        }

        if (nav_get_active_component() == NAV_COMP_ID_C4TV_APRON ||
            nav_is_component_visible(NAV_COMP_ID_C4TV_APRON))
        {
            b_is_processed = FALSE;
            break;
        }

        if (nav_get_active_component() == NAV_COMP_ID_RETAIL_MODE ||
            nav_is_component_visible(NAV_COMP_ID_RETAIL_MODE))
        {
            b_is_processed = FALSE;
            break;
        }
        if (nav_get_active_component() == NAV_COMP_ID_REVOLT_INFO ||
            nav_is_component_visible(NAV_COMP_ID_REVOLT_INFO))
        {
            b_is_processed = FALSE;
            break;
        }

    }while(0);

    if (b_is_processed == FALSE)
    {
        _retail_mode_handle_key_for_overlay(ui4_keycode);
    }
#endif
    return;
}

/*-----------------------------------------------------------------------------
 * Name: _retail_mode_iom_nfy_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _retail_mode_iom_nfy_fct (
                          VOID*             pv_nfy_tag,
                          IOM_NFY_COND_T    e_nfy_cond,
                          UINT32            ui4_evt_code,
                          UINT32            ui4_data
                          )
{
    DBG_INFO(("[RETAIL MODE] [%s] e_nfy_cond:%d, ui4_evt_code:%X \r\n", __FUNCTION__, e_nfy_cond, ui4_evt_code));

    if (e_nfy_cond == IOM_NFY_COND_BTN_DOWN ||
        e_nfy_cond == IOM_NFY_COND_BTN_REPEAT)
    {
        /*post a message to itself*/
        nav_request_context_switch(_nav_retail_iom_nfy_hdlr,
                                   (VOID*)e_nfy_cond,
                                   (VOID*)ui4_evt_code,
                                   (VOID*)ui4_data);

    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_init
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
static INT32 _nav_retail_mode_init(NAV_CONTEXT_T* pt_ctx)
{
    INT32                   i4_ret  = NAVR_OK;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    IRRC_SETTING_T          t_irrc_setting;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    b_g_is_demo_flash_playing = FALSE;

    c_memset(pt_this, 0, sizeof(_NAV_RETAIL_MODE_T));
    pt_this->e_status               = NAV_RETAIL_MODE_INITIAL;
    pt_this->e_resume_from_app      = NAV_RETAIL_MODE_RESUME_FROM_POWER;
    pt_this->e_popup_dlg            = NAV_RETAIL_MODE_NO_POPUP_DLG;
    pt_this->e_running_type         = RETAIL_MODE_TYPE_UNKNOW;
    pt_this->b_is_ignore_pic_nfy    = TRUE;
    pt_this->b_is_cfg_nfy_timer_start = FALSE;
    pt_this->b_is_pause_timer_start = FALSE;
    pt_this->ui4_yahoo_status       = YAHOO_STATUS_HIDE;
    pt_this->ui4_app_status         = NW_APP_STATUS_HIDE;

    pt_this->h_canvas               = pt_ctx->t_gui_res.h_canvas;

    /* Init Retail End Cap */
#ifdef APP_3D_RETAIL_DEMO_MODE
    nav_retail_end_cap_init();
#endif

    retail_mode_view_init(pt_this->h_canvas);

    retail_mode_view_logo_init(pt_this->h_canvas);

    /* Register to ACFG to listen PQ change notify */
    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_VIDEO,
                              NULL,
                              _nav_retail_cfg_change_cb,
                              &pt_this->ui2_cfg_nfy_id_pic_mode);
    NAV_CHK_FAIL(APP_CFGR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_icl_notify_reg(ICL_GRPID_PQ_CHANGE_STATUS,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _nav_retail_pq_change_icl_nfy_cb,
                              &pt_this->ui2_icl_nfy_id_pic_mode);
    NAV_CHK_FAIL(ICLR_OK == i4_ret ? NAVR_OK : i4_ret);



    /* IOM open */
    {
        c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
        t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
        t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = 50; /* No repeat key */
        t_irrc_setting.t_rpt_evt_itvl.ui2_other = 20; /* No repeat key */
        t_irrc_setting.b_notify_raw_data        = TRUE;

        i4_ret = c_iom_open(
                        IOM_DEV_TYPE_IN_IRRC,
                        IOM_DEV_ID_ANY,
                        NULL,
                        &t_irrc_setting,
                        NULL,
                        _retail_mode_iom_nfy_fct,
                        & pt_this->h_iom
                        );
         NAV_CHK_FAIL(IOMR_OK == i4_ret ? NAVR_OK : i4_ret);
    }

    /* do NOT have yahoo widget and other 3rd app anymore */
    if (0)
    {
        i4_ret = a_icl_notify_reg(ICL_GRPID_CUSTOM_NW_WIDGET,
                                  ICL_PRIORITY_DEFAULT,
                                  NULL,
                                  NULL,
                                  _nav_retail_mode_yahoo_status_nfy_func,
                                  &pt_this->ui2_yahoo_status_nfy);
        NAV_CHK_FAIL(ICLR_OK == i4_ret ? NAVR_OK : i4_ret);
    }

    {
        i4_ret = c_cecm_open_svc (_nav_retail_cec_nfy_fct, NULL, &pt_this->h_cecm_svc_svc);
        NAV_CHK_FAIL(CECMR_OK == i4_ret ? NAVR_OK : i4_ret);
    }

    do{
        /*Create timer*/

        i4_ret = c_timer_create(&pt_this->h_cfg_nfy_timer);
        NAV_BREAK_ON_FAIL(OSR_OK == i4_ret ? NAVR_OK : i4_ret);

        i4_ret = c_timer_create(&pt_this->h_pause_timer);
        NAV_BREAK_ON_FAIL(OSR_OK == i4_ret ? NAVR_OK : i4_ret);

        i4_ret = c_timer_create(&pt_this->h_overlay_recheck_timer);
        NAV_BREAK_ON_FAIL(OSR_OK == i4_ret ? NAVR_OK : i4_ret);

	i4_ret = c_timer_create(&pt_this->h_dialag_hide_timer);
	NAV_BREAK_ON_FAIL(OSR_OK == i4_ret ? NAVR_OK : i4_ret);

        /* Create dialog */
        i4_ret = _nav_retail_pause_dlg_init();
        NAV_BREAK_ON_FAIL(i4_ret);

        i4_ret = _nav_retail_resume_dlg_init();
        NAV_BREAK_ON_FAIL(i4_ret);
        i4_ret = _nav_retail_info_dlg_init();
        NAV_BREAK_ON_FAIL(i4_ret);

	i4_ret = _retail_mode_detect_video_thread();
	if (NAVR_OK != i4_ret)
	{
		DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
		return NAVR_FAIL;
	}
#ifdef RETAIL_RCOVERY_DEBUG
	i4_ret = _retail_mode_recovery_test_thread();
	if (NAVR_OK != i4_ret)
	{
		DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
	}
#endif
        return  NAVR_OK;
    } while (0);

    i4_ret = _nav_retail_mode_deinit();
    if (NAVR_OK != i4_ret)
    {
        DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
    }
    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_deinit
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
static INT32 _nav_retail_mode_deinit(VOID)
{
    INT32                   i4_ret  = NAVR_OK;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    /* Deinit Retail End Cap */
#ifdef APP_3D_RETAIL_DEMO_MODE
    nav_retail_end_cap_deinit();
#endif

    retail_mode_view_deinit();

    /* Destroy timer */

    if (NULL_HANDLE != pt_this->h_cfg_nfy_timer)
    {
        i4_ret = c_timer_delete(pt_this->h_cfg_nfy_timer);
        if (OSR_OK != i4_ret)
        {
            DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        }
        pt_this->h_cfg_nfy_timer = NULL_HANDLE;
    }

    if (NULL_HANDLE != pt_this->h_pause_timer)
    {
        i4_ret = c_timer_delete(pt_this->h_pause_timer);
        if (OSR_OK != i4_ret)
        {
            DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        }
        pt_this->h_pause_timer = NULL_HANDLE;
    }
    if (NULL_HANDLE != pt_this->h_overlay_recheck_timer)
    {
        i4_ret = c_timer_delete(pt_this->h_overlay_recheck_timer);
        if (OSR_OK != i4_ret)
        {
            DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        }
        pt_this->h_overlay_recheck_timer = NULL_HANDLE;
    }
	if (NULL_HANDLE != pt_this->h_dialag_hide_timer)
	{
		i4_ret = c_timer_delete(pt_this->h_dialag_hide_timer);
		if (OSR_OK != i4_ret)
		{
			DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
		}
		pt_this->h_dialag_hide_timer = NULL_HANDLE;
	}

    /* Destory Dialog */
    if(NULL_HANDLE != pt_this->h_pause_dlg)
    {
        i4_ret = _nav_retail_mode_dialog_deinit(pt_this->h_pause_dlg);
        if (NAVR_OK != i4_ret)
        {
            DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        }
        pt_this->h_pause_dlg = NULL_HANDLE;
    }

    if (pt_this->ui2_icl_nfy_id_pic_mode)
    {
        i4_ret = a_icl_notify_unreg(pt_this->ui2_icl_nfy_id_pic_mode);
        if (ICLR_OK != i4_ret)
        {
            DBG_ERROR(("<RETAIL_MODE> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        }

        pt_this->ui2_icl_nfy_id_pic_mode = 0;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_is_key_handler
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
static BOOL _nav_retail_mode_is_key_handler(
                    NAV_CONTEXT_T*  pt_ctx,
                    UINT32          ui4_key_code
                    )
{
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_activate
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
static INT32 _nav_retail_mode_activate(
                    NAV_CONTEXT_T*  pt_ctx,
                    UINT32          ui4_key_code)
{
    return NAVR_OK;
}

#ifdef APP_2K12_RETAIL_DEMO_MODE
/*----------------------------------------------------------------------------
* Name: _nav_retail_mode_init_pic_mode
*
* Description: This function init pic mode to vivid and
*        backlight control & light sensor
*
* Inputs:
*
* Outputs:
*
* Returns:
*
----------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_init_pic_mode(VOID)
{
    INT16                   i2_clr_temp = 0;
	ACFG_RETAIL_MODE_T	 t_retail_mode = ACFG_RETAIL_MODE_HOME;
	UINT16              ui2_status     = 0;
    UINT8               ui1_state      = 0;
	UINT8               ui1_index      = 0;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

	t_g_retail_mode.b_is_ignore_pic_nfy = TRUE;

    /*exit demo mode*/
    a_cfg_get_wzd_status(&ui2_status);
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_index = WZD_UTIL_GET_STATUS_IDX(ui2_status);


	a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
	if (ACFG_RETAIL_MODE_HOME == t_retail_mode)
	{
		/*if exit to oobe,don`t change current picture mode*/
	    if (WZD_STATE_RESUME_C4TV != ui1_state )
	    {
	     	_nav_retail_mode_set_pq_idx(ACFG_CUST_PIC_MODE_RETAIL);
	    }
	}

    /* set color tuner under current color temp */
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

    a_cfg_reset_clr_tuner(i2_clr_temp);
    a_cfg_cust_update_color_tuner();


    /*set backlight control to off*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), (INT16)0);

    ACFG_DEBUG_BACKLIGHT(
        DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL]{%s: %d} Call a_cfg_av_update(APP_CFG_RECID_VID_CUSTOM_DCR)\n", __FUNCTION__, __LINE__ ));
    );
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));

    /*set light sensor to off*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), (INT16)0);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));

#if 0
    /*set smart dimming to off*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING), (INT16)0);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
#endif

    t_g_retail_mode.b_is_ignore_pic_nfy = FALSE;


    DBG_INFO(("[RETAIL MODE]Leave.\n\r"));

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_reset_pic_mode
 *
 * Description: This function reset pic mode to vivid and
 *        backlight control & light sensor
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_reset_pic_mode(VOID)
{
    UINT8 ui1_dcr_def = 0;
    UINT16 ui2_pic_mode_idx = 0;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    t_g_retail_mode.b_is_ignore_pic_nfy = TRUE;

    /*reset pic mode to default*/
    a_cfg_custom_reset_pic_mode_setting();

    ui2_pic_mode_idx = _nav_retail_mode_get_pq_idx();
    if (ui2_pic_mode_idx != 0)
    {
        ui2_pic_mode_idx = 0;
        _nav_retail_mode_set_pq_idx(ui2_pic_mode_idx);
    }

    /*set backlight control to default*/
    a_cfg_get_dcr_def_value(&ui1_dcr_def);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), (INT16)ui1_dcr_def);

    ACFG_DEBUG_BACKLIGHT(
        DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL]{%s: %d} Call a_cfg_av_update(APP_CFG_RECID_VID_CUSTOM_DCR)\n", __FUNCTION__, __LINE__ ));
    );
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));

    if(a_cfg_cust_drv_is_lightsensor_support() == TRUE)
    {
        /*set light sensor to default*/
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), (INT16)2);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));
    }

#if 0
    /*set smart dimming to default*/
    acfg_set_default(IDX_CUSTOM_DIMMING);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
#endif

    t_g_retail_mode.b_is_ignore_pic_nfy = FALSE;

    DBG_INFO(("[RETAIL MODE] [%s] End \r\n", __FUNCTION__));

    return NAVR_OK;
}

#if 0
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_power_on_show_flash
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static VOID _nav_retail_mode_power_on_show_flash(
                    VOID*           pv_tag1,
                    VOID*           pv_tag2,
                    VOID*           pv_tag3
                    )
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;
    INT32 i4_ret = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    pt_this->e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;

    /* play demo swf or video */
    a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
    a_cfg_custom_set_retail_mode_led_ctrl(TRUE);

    a_nav_power_set_component_enable(FALSE);

    i4_ret = _nav_retail_mode_init_pic_mode();
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = _nav_retail_mode_start_play();
    NAV_LOG_ON_FAIL(i4_ret);
    pt_this->e_resume_from_app = NAV_RETAIL_MODE_RESUME_FROM_NULL;
}
#endif
#endif

static VOID _nav_retail_mode_start_launch_count_down (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    RETAIL_MODE_PARAM_T t_param;
    UINT8   ui1_vol_dis_flag = ACFG_CUSTOM_VOL_SLIDER_DIS_OFF;
    a_cfg_cust_get_vol_control_dis_flag(&ui1_vol_dis_flag);

    //DBG_LOG_PRINT (("\033[45m [%s][%d] \033[0m \n", __FUNCTION__, __LINE__));

    c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));

    t_param.t_launch_info.e_launch_from_app = (NAV_RETAIL_MODE_RESUME_FROM_T)pv_tag1;
    t_param.t_launch_info.e_launch_osd_type = (RETAIL_MODE_LAUNCH_OSD_TYPE_T)pv_tag2;
    t_param.t_launch_info.ui2_count = (UINT32)pv_tag3;

    DBG_INFO((" e_launch_from_app: %d, e_launch_osd_type: %d, ui2_count: %d \n", \
                       t_param.t_launch_info.e_launch_from_app, \
                       t_param.t_launch_info.e_launch_osd_type, \
                       t_param.t_launch_info.ui2_count));

    _nav_retail_mode_start(&t_param);

    if(ui1_vol_dis_flag == ACFG_CUSTOM_VOL_SLIDER_DIS_ON)
    {
        a_vol_ctrl_set_visibility(TRUE);
    }

    a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_on_resume
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_on_nav_resume(const BOOL b_is_power_on)
{
    INT32                   i4_ret  = NAVR_OK;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;
    ACFG_RETAIL_MODE_T      t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

    DBG_INFO(("[RETAIL MODE] [%s] e_retail_mode_status: %X \r\n", __FUNCTION__, pt_this->e_status));

    switch (pt_this->e_status)
    {
        case NAV_RETAIL_MODE_CHECKING:
        {
            i4_ret = nav_retail_mode_go(NAV_RETAIL_MODE_RUNNING);
            NAV_CHK_FAIL(i4_ret);

            break;
        }


        case NAV_RETAIL_MODE_PAUSE:
        {
            /* get retail mode flag from acfg */
            i4_ret = a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
            NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret );

            if(ACFG_RETAIL_MODE_NORMAL != t_retail_mode)
            {
                if( b_g_oobe_retail_mode == FALSE)
                {
                    /* resume retail by retail mode state */
                    /*b_g_oobe_retail_mode means: demo mode in oobe then power off.*/
                    DBG_INFO(("[RETAIL MODE]Is not ACFG_RETAIL_MODE_NORMAL.\n\r"));
                    return NAVR_OK;
                }
                else
                {
                    DBG_INFO(("[RETAIL MODE]Is oobe_retail_mode.\n\r"));
                    b_g_oobe_retail_mode = FALSE;
                }
            }

            _nav_retail_mode_start_pause_timer();

            return NAVR_OK;
            break;
        }


        case NAV_RETAIL_MODE_EXIT:
        case NAV_RETAIL_MODE_INITIAL:
        {
            /* get retail mode flag from acfg */
            i4_ret = a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
            NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret );

            if(ACFG_RETAIL_MODE_NORMAL != t_retail_mode)
            {
                if( b_g_oobe_retail_mode == FALSE)
                {
                    /* resume retail by retail mode state */
                    /*b_g_oobe_retail_mode means: demo mode in oobe then power off.*/
                    DBG_INFO(("[RETAIL MODE]Is not ACFG_RETAIL_MODE_NORMAL.\n\r"));
                    return NAVR_OK;
                }
                else if(_nav_retail_mode_check_running_type() == RETAIL_MODE_TYPE_VIDEO)
                {
                    DBG_INFO(("[RETAIL MODE]Is oobe_retail_mode. but running type is RETAIL_MODE_TYPE_VIDEO\n\r"));
                    return NAVR_OK;
                }

                DBG_LOG_PRINT(("[RETAIL MODE]Is oobe_retail_mode \n\r"));
                b_g_oobe_retail_mode = FALSE;
            }

            {
                RETAIL_MODE_PARAM_T t_param;
                c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));

                if (b_is_power_on)
                {
                    t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_POWER;
                    t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
                    t_param.t_launch_info.ui2_count = 60;
                }
                else
                {
                    t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_NULL;
                    t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
                    t_param.t_launch_info.ui2_count = 15;
                }

                if (b_g_oobe_retail_mute_before_power_off&&b_is_power_on)
                {
                    BOOL   b_mute;
                    i4_ret = nav_get_mute(&b_mute);
                    UINT8   ui1_vol_dis_flag = ACFG_CUSTOM_VOL_SLIDER_DIS_OFF;

                    if(!b_mute)
                    {
                        a_cfg_cust_get_vol_control_dis_flag(&ui1_vol_dis_flag);
                        if(ui1_vol_dis_flag == ACFG_CUSTOM_VOL_SLIDER_DIS_ON)
                        {
                            a_vol_ctrl_set_visibility(FALSE);
                        }

                        c_iom_send_evt(BTN_MUTE, 100);

                        nav_request_context_switch (_nav_retail_mode_start_launch_count_down,
                                (VOID*)(UINT32)(t_param.t_launch_info.e_launch_from_app),
                                (VOID*)(UINT32)(t_param.t_launch_info.e_launch_osd_type),
                                (VOID*)(UINT32)(t_param.t_launch_info.ui2_count) );

                        b_g_oobe_retail_mute_before_power_off = FALSE;
                        return NAVR_OK;
                    }
                }


                i4_ret = _nav_retail_mode_start(&t_param);
                NAV_CHK_FAIL(i4_ret);
                a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
            }

            break;
        }


        default:
        {

            break;
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_inactivate
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
static INT32 _nav_retail_mode_inactivate(NAV_CONTEXT_T*   pt_ctx)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_hide
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
static INT32 _nav_retail_mode_hide(VOID)
{
    return NAVR_OK;
}

static INT32 _nav_retail_mode_reset_power_off(VOID)
{
    INT32 i4_ret = NAVR_OK;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;
    ACFG_RETAIL_MODE_T      t_retail_mode = ACFG_RETAIL_MODE_HOME;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    /* because of retail mode is alive,
       need change status to TV MODE due to not change source to CAST after POWER OFF/ON */
    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
      #ifdef SYS_C4TV_SUPPORT
        a_cfg_set_cast_tv_status(APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE);
      #endif
    }
    else if (ACFG_RETAIL_MODE_NO_PLAYING == t_retail_mode)
    {
        #ifdef SYS_C4TV_SUPPORT
        a_cfg_set_cast_tv_status(APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE);
        #endif
        a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
    }
    else
    {
        return NAVR_OK;
    }

    a_tv_custom_set_banner_visiable_allow(TRUE);

    /* enable screen saver */
    a_scrn_svr_set_enable(TRUE);

    /* if timer is running just stop it */
    i4_ret = _nav_retail_mode_stop_timer();
    NAV_CHK_FAIL(i4_ret);

    /* hide osd */
    i4_ret = _nav_retail_mode_exit_hide();
    NAV_LOG_ON_FAIL(i4_ret);

    /*stop play*/
    i4_ret = _nav_retail_mode_stop_play_by_power_off();
    NAV_LOG_ON_FAIL(i4_ret);

    pt_this->b_is_ignore_pic_nfy = TRUE;
    pt_this->ui4_yahoo_status = YAHOO_STATUS_HIDE;
    pt_this->ui4_app_status = NW_APP_STATUS_HIDE;

    pt_this->e_status = NAV_RETAIL_MODE_INITIAL;

    /* need show countdown dialog next time */
    pt_this->e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;
    pt_this->e_resume_from_app  = NAV_RETAIL_MODE_RESUME_FROM_POWER;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_start_retail_mode_in_no_overlay
 * Description  - restart demo from no overlay
 * Input        -
 * Output       -
 * Returns      -
 *-----------------------------------------------------------------------------*/
UINT32 a_start_retail_mode_in_no_overlay(VOID)
{
    INT32                   i4_ret  = NAVR_OK;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;
    C4TV_APRON_STATE_T      i4_cast_status  = C4TV_APRON_STATE_UNKNOWN;
    UINT8					ui1_demo_mode = 0;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

	a_cfg_cust_get_demo_mode_value(&ui1_demo_mode);

	if ((pt_this->e_status == NAV_RETAIL_MODE_CHECKING)||
			(pt_this->e_status == NAV_RETAIL_MODE_RESTARTING))
	{
		i4_cast_status = a_c4tv_apron_get_cast_running_state();

		i4_ret = nav_retail_mode_go(NAV_RETAIL_MODE_RUNNING);

		NAV_CHK_FAIL(i4_ret);
	}
	return NAVR_OK;

}


static UINT32 _nav_cec_custom_get_amp_hdmi_5v(UINT8 *pui1_5v_status,DRV_CUSTOM_CUST_SPEC_TYPE_T get_hdmi_flag)
{
  INT32   i4_ret;
  DRV_CUST_OPERATION_INFO_T    t_op_info={0};
  SIZE_T					   z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
  SIZE_T					   z_size = sizeof(pui1_5v_status);


  c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
  t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
  t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = get_hdmi_flag;
  t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui1_5v_status;
  t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

  /*get driver value */
    i4_ret = c_rm_get_comp(DRVT_CUST_DRV,
                             DRV_CUST_COMP_ID,
                             FALSE,
                             ANY_PORT_NUM,
                             0,
                             &t_op_info,
                             &z_size_drv
                             );

    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    return i4_ret;
}

static INT32 _is_need_change_hdmi_port(UINT8 *switch_hdmi_port)
{
    INT32			i4_ret = 0;
    UINT8			ui1_src_count = 0;
    UINT8			get_hdmi1_state = 0;
    UINT8			get_hdmi2_state = 0;
    UINT8			get_hdmi3_state = 0;
    UINT8			get_hdmi4_state = 0;
    SIZE_T	        z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
    UINT8           ui1_icl_val;
    UINT8           ui1_demo_type = 0;

    a_cfg_custom_get_demo_type(&ui1_demo_type);

	i4_ret = a_isl_get_num_rec(&ui1_src_count);
	NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret);

	*switch_hdmi_port = 0x0F;

	if( 0 == ui1_src_count )
	{
		return FALSE;
	}
	else if (ui1_demo_type != 0xF0)
	{
		return FALSE;
	}

	_nav_cec_custom_get_amp_hdmi_5v(&get_hdmi1_state,DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI1_5V_STATUS);
	_nav_cec_custom_get_amp_hdmi_5v(&get_hdmi2_state,DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI2_5V_STATUS);
	_nav_cec_custom_get_amp_hdmi_5v(&get_hdmi3_state,DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI3_5V_STATUS);
	_nav_cec_custom_get_amp_hdmi_5v(&get_hdmi4_state,DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI4_5V_STATUS);

	DBG_INFO(("[RETAIL MODE]hdmi1_state:%d,hdmi2_state:%d,hdmi3_state:%d,hdmi4_state:%d. \n\r",get_hdmi1_state,get_hdmi2_state,get_hdmi3_state,get_hdmi4_state));

	a_icl_get(ICL_MAKE_ID(ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
					   &ui1_icl_val,
					   &z_size);

	while(1)
	{
		if(get_hdmi1_state != 0)
		{
			/*this hdmi port is connected to the sound bar*/
			if (ui1_icl_val == ICL_CEC_SAC_STATUS_ON )
			{
				if (get_hdmi2_state == 0
					&& get_hdmi3_state == 0
					&& get_hdmi4_state == 0)
				{
					*switch_hdmi_port = 0;
					i4_ret = TRUE;
					break;
				}
			}
			else
			{
				*switch_hdmi_port = 0;
				i4_ret = TRUE;
				break;
			}

		}
		if(get_hdmi2_state != 0)
		{
			*switch_hdmi_port = 1;
			i4_ret = TRUE;
			break;
		}
		if(get_hdmi3_state != 0)
		{
			*switch_hdmi_port = 2;
			i4_ret = TRUE;
			break;
		}
		if(get_hdmi4_state != 0)
		{
			*switch_hdmi_port = 3;
			i4_ret = TRUE;
			break;
		}
		DBG_INFO(("[RETAIL MODE] There are not hdmi detect \n\r "));
		i4_ret = FALSE;
		break;
	}

	 return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_handle_msg
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
static INT32 _nav_retail_mode_handle_msg(
                    NAV_CONTEXT_T*  pt_ctx,
                    NAV_UI_MSG_T*   pt_ui_msg,
                    VOID*           pv_arg1
                    )
{
    INT32                   i4_ret  = NAVR_OK;
    ACFG_RETAIL_MODE_T      t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;
    C4TV_APRON_STATE_T      i4_cast_status  = C4TV_APRON_STATE_UNKNOWN;

    DBG_INFO(("[RETAIL MODE] [%s] e_id: %X \r\n", __FUNCTION__, pt_ui_msg->e_id));

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    switch (pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        {
            NAV_XNG_SRC_TRGT_T* pt_src_trgt = pv_arg1;
            UINT16      ui2_status  = 0;
            UINT8       ui1_state   = 0;
            UINT8       ui1_index   = 0;

            a_cfg_get_wzd_status(&ui2_status);

            ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
            ui1_index = WZD_UTIL_GET_STATUS_IDX(ui2_status);
            if((_nav_retail_mode_get_status() == NAV_RETAIL_MODE_PAUSE)&&(ui1_state == WZD_STATE_RESUME_C4TV))  //During OOBE  demo mode,switch input source
            {
                UINT8   ui1_idx_mode = 0x00;
                a_cfg_cust_get_retail_mode_source_info(&ui1_idx_mode);
                ui1_idx_mode=ui1_idx_mode&0x0F;

                DBG_INFO(("[%s][%d] ui1_trgt_inp_src_id:%d, ui1_crnt_inp_src_id:%d \n",\
                           __FUNCTION__,__LINE__, \
                           pt_src_trgt->u.t_av.ui1_trgt_inp_src_id, \
                           pt_src_trgt->u.t_av.ui1_crnt_inp_src_id));

                if((pt_src_trgt->u.t_av.ui1_trgt_inp_src_id != 2))//switch to another source during OOBE demo mode
                {

                    ui1_idx_mode |=0x01; // bit 0 1 2 3 means the source is changed during OOBE demo mode
                    a_cfg_cust_set_retail_mode_source_info(ui1_idx_mode);
                }

                ui1_idx_mode |= (UINT8)(pt_src_trgt->u.t_av.ui1_trgt_inp_src_id << 4);
                a_cfg_cust_set_retail_mode_source_info(ui1_idx_mode);
            }
			b_last_input_signal_locked = FALSE;
			if (b_g_retail_mode_need_recheck_hdmi_plug_in_out == TRUE)
			{
				/* enable screen saver */
				a_scrn_svr_set_enable(TRUE);

			}
        }

        break;


        case NAV_UI_MSG_APP_PRE_RESUME:
        {
            /* do nothing */

            break;
        }

        case NAV_UI_MSG_APP_RESUMED:
        {
            if ( !(e_active_app == ACTIVE_APP_3RD) )
            {
                i4_ret = _nav_retail_mode_on_nav_resume((BOOL)(UINT32)pv_arg1);
            }
            NAV_CHK_FAIL(i4_ret);

            break;
        }


        case NAV_UI_MSG_POWER_OFF:
        {
        #if 1
            if(_nav_retail_mode_get_status() == NAV_RETAIL_MODE_RUNNING)//DTV00938877
            {
                BOOL   b_mute;
                i4_ret = nav_get_mute(&b_mute);
                NAV_LOG_ON_FAIL(i4_ret);
                if(b_mute)
                {
                    b_g_oobe_retail_mute_before_power_off = FALSE;
                    //i4_ret = a_tv_set_vol(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL), 0);
                    //NAV_LOG_ON_FAIL(i4_ret);
                }
            }
        #endif
            if (ACFG_RETAIL_MODE_NO_PLAYING == t_retail_mode)
            {
                a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
            }
            b_g_oobe_retail_pause_by_app = FALSE;
            b_last_input_signal_locked = FALSE;
            retail_mode_view_logo_hide();
            retail_mode_view_timer_stop();

        #if APP_RETAIL_DEMO_BACKUP_MMP_PQ
            nav_recover_mmp_pq_value_in_exit();
        #endif
            _nav_retail_mode_reset_power_off();
            _nav_retail_mode_cec_clear_element();
            _nav_retail_mode_recover_wzd_stat();
            a_nav_retail_mode_clean_usb_device();
            c_timer_stop(pt_this->h_dialag_hide_timer);
            clear_count_timer_status();

            break;
        }


        case NAV_UI_MSG_OTHER_APP_RESUMED:
        {
            if (t_retail_mode != ACFG_RETAIL_MODE_NORMAL)
            {
                break;
            }

            if (0 == c_strcmp ((CHAR*)pv_arg1, MENU_NAME))
            {
                if (NAV_RETAIL_MODE_RUNNING == pt_this->e_status)
                {
                    nav_retail_mode_go(NAV_RETAIL_MODE_PAUSE);
                }
                _nav_retail_mode_start_pause_timer();
            }

            if (0 == c_strcmp ((CHAR*)pv_arg1, WZD_NAME))
            {
                if (NAV_RETAIL_MODE_RUNNING == pt_this->e_status)
                {
                    retail_mode_view_logo_hide();
                }
                else if (NAV_RETAIL_MODE_INITIAL == pt_this->e_status)
                {
                    DBG_LOG_PRINT(("[RETAIL MODE]oobe have launch.\n\r"));

                    if(!(e_active_app == ACTIVE_APP_3RD))
                    {
                        i4_ret = _nav_retail_mode_on_nav_resume((BOOL)(UINT32)pv_arg1);
                    }

                    NAV_CHK_FAIL(i4_ret);
                }
            }

            break;
        }


        case NAV_UI_MSG_CH_SCANNING:
        {
            if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
            {
                /* menu dealing with special case, NOT start store demo */
                if (nav_is_channel_scan_active ())
                {
                    _nav_retail_mode_stop_pause_timer();
                }
                else
                {
                    _nav_retail_mode_start_pause_timer();
                }
            }
        }
            break;
//        case NAV_UI_MSG_STREAM_NOTIFY:
        case NAV_UI_MSG_WITH_SIGNAL:
        case NAV_UI_MSG_NO_SIGNAL:
        {
            {
                CHAR            s_active_app[APP_NAME_MAX_LEN + 1] = {0};

                DBG_INFO(("[%s][%d] pt_e_id:%d, e_status:%d \n", __FUNCTION__, __LINE__, \
                           pt_ui_msg->e_id, pt_this->e_status));

                if(pt_ui_msg->e_id == NAV_UI_MSG_WITH_SIGNAL)
                {
                    b_last_input_signal_locked = TRUE;
                }
                else if(pt_ui_msg->e_id == NAV_UI_MSG_NO_SIGNAL)
                {
                	a_cfg_custom_set_demo_type(0xF0);
                    b_last_input_signal_locked = FALSE;
                }
                if (pt_this->e_status == NAV_RETAIL_MODE_RUNNING )
                {

                    if(_nav_retail_mode_get_running_type() == RETAIL_MODE_TYPE_OVERLAY)
                    {
                            /*update*/
                            UINT32 ui4_current_tick = 0;
                            UINT32 ui4_last_select_overlay_tick = 0;
                            UINT32 ui4_tick_period = 0;
                            UINT32 ui4_tick_mist_period = 0;
                            ui4_last_select_overlay_tick = ui4_g_overlay_demo_service_tick;
                            ui4_tick_period = c_os_get_sys_tick_period();
                            ui4_current_tick = c_os_get_sys_tick();
                            /*stop current type*/
                            i4_ret = _nav_retail_mode_set_running_type(RETAIL_MODE_TYPE_UNKNOW);
                            if (ui4_current_tick >= ui4_last_select_overlay_tick)
                            {
                                ui4_tick_mist_period = (ui4_current_tick - ui4_last_select_overlay_tick)*ui4_tick_period;
                                if ( ui4_tick_mist_period <= 4000)
                                {
                                    c_timer_stop(pt_this->h_overlay_recheck_timer);
                                    c_timer_start(pt_this->h_overlay_recheck_timer,
                                      (4000-ui4_tick_mist_period),
                                      X_TIMER_FLAG_ONCE,
                                      _nav_retail_overlay_demo_update_timer_cb,
                                      NULL);
                                    return NAVR_OK;
                                }
                            }

                            i4_ret = _nav_retail_mode_update_running_type();
                            NAV_LOG_ON_FAIL(i4_ret);

							i4_ret = a_start_retail_mode_in_no_overlay();
							NAV_LOG_ON_FAIL(i4_ret);

                            return NAVR_OK;
                    }
                    if((_nav_retail_mode_get_running_type() == RETAIL_MODE_TYPE_VIDEO_INTERNAL)&&b_last_input_signal_locked)
                    {
                        _nav_retail_mode_exit();
                        _nav_retail_mode_set_status(NAV_RETAIL_MODE_RESTARTING);
                        return NAVR_OK;
                    }
                }
                else if ((pt_this->e_status == NAV_RETAIL_MODE_CHECKING)||
                        (pt_this->e_status == NAV_RETAIL_MODE_RESTARTING))
                {
                    i4_cast_status = a_c4tv_apron_get_cast_running_state();
                    if(i4_cast_status != C4TV_APRON_STATE_EXITING_CAST)
                    {
                        i4_ret = a_am_get_active_app (s_active_app);
    					NAV_CHK_FAIL(i4_ret == AMR_OK ? NAVR_OK :i4_ret);
						if ( c_strcmp(s_active_app, "navigator") != 0 )
	   					{
	   						b_force_enable_store_mode = 1;
						}
                        i4_ret = nav_retail_mode_go(NAV_RETAIL_MODE_RUNNING);
                    }
                    NAV_CHK_FAIL(i4_ret);
                    return NAVR_OK;
                }
            }
        }
            break;
        case NAV_UI_MSG_POWER_ON:
        {
            UINT16  ui2_status    = 0;
            UINT8   ui1_state     = 0;
            i4_ret = a_cfg_get_wzd_status(&ui2_status);
            NAV_CHK_FAIL(APP_CFGR_OK == i4_ret ? NAVR_OK : i4_ret);

            ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
            DBG_INFO(("[RETAIL MODE] power on, wzd sta:%x,retail_mode:%x .\n\r",ui1_state,t_retail_mode));
            if (WZD_STATE_RESUME_C4TV == ui1_state && ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
            {
                /* reset retail mode in oobe*/
                {
                    /* Make sure that retail mode can be reset Enable when power on.  Check current state in rest. */
                    a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
                    pt_this->e_status = NAV_RETAIL_MODE_INITIAL;
                    b_g_oobe_retail_mode = TRUE;

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

                        a_isl_get_num_rec(&ui1_src_num);

                        for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
                        {
                        i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);

                        if (i4_ret != NAVR_OK)
                        {
                            return i4_ret;
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

                        acfg_tv_get_focus_win(&t_tv_win_id);
                        a_nav_change_input_src(t_tv_win_id, t_isl_rec.ui1_id);
                    }
                }
            }
            /* some case the logo is show after power off.  */
            retail_mode_view_logo_hide();
        }
        break;


        default:
            break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

#ifdef APP_2K12_RETAIL_DEMO_MODE
/*-----------------------------------------------------------------------------
 * Name
 *      nav_retail_exit_from_other_app
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
VOID nav_retail_exit_from_other_app(BOOL b_show)
{
//    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_retail_mode_exit_key_hdlr
 * Description  -
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
VOID nav_retail_mode_exit_key_hdlr(c4tv_apron_custom_nfy_fct pf_nfy)
{
    _NAV_RETAIL_MODE_T*         pt_this = &t_g_retail_mode;
    INT32 i4_ret = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    if (pt_this->e_popup_dlg == NAV_RETAIL_MODE_POPUP_LAUNCHING_DLG)
    {
        a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);

        if (pt_this->e_resume_from_app == NAV_RETAIL_MODE_RESUME_FROM_POWER)
        {
            _nav_retail_mode_reset_pic_mode();
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* if changed, reset to vivid immediately */
        if (pt_this->b_is_cfg_nfy_timer_start)
        {
            _nav_retail_mode_init_pic_mode();
        }

#if 0
        /*set smart dimming to on*/
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING), (INT16)1);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
#endif

        a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
    }

    a_cfg_custom_set_retail_mode_led_ctrl(FALSE);

    if (b_g_is_demo_flash_playing)
    {
        nav_retail_mode_send_cmd(FALSE);
    }

    if (nav_retail_mode_get_is_play())
    {
        nav_retail_stop_end_cap();
        nav_retail_stop_internal_video();
    }

    /* if timer is running just stop it */
    i4_ret = _nav_retail_mode_stop_timer();
    NAV_LOG_ON_FAIL(i4_ret);

    pt_this->b_is_ignore_pic_nfy = TRUE;
    pt_this->e_status = NAV_RETAIL_MODE_INITIAL;

    /* need show countdown dialog next time */
    pt_this->e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;

    /* enable info banner popup */
    a_tv_custom_set_banner_visiable_allow(TRUE);

    pt_this->e_resume_from_app = NAV_RETAIL_MODE_RESUME_FROM_NULL;

    a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
    a_c4tv_apron_revoke_exit_cast(pf_nfy);

    /* reset OOBE state. */
    a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      nav_retail_mode_is_flash_playing
 * Description
 *      get demo flash playing state
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      TRUE        Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
BOOL  nav_retail_mode_is_flash_playing(VOID)
{
    return b_g_is_demo_flash_playing;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_retail_mode_show_warning_dialog
 * Description
 *      Start retail mode dialog
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
VOID nav_retail_mode_show_warning_dialog(VOID)
{
//    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_retail_mode_hide_pause_dialog
 * Description
 *      Hide retail mode pause dialog
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
VOID nav_retail_mode_hide_pause_dialog(VOID)
{
    NAV_RETAIL_MODE_POPUP_DLG_T e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;
    INT32 i4_ret = NAVR_OK;

    a_nav_retail_mode_get_dlg_show(&e_popup_dlg);
    if(NAV_RETAIL_MODE_POPUP_PAUSE_DLG != e_popup_dlg)
    {
        /*dialog not show*/
        return ;
    }

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    i4_ret = _nav_retail_pause_dlg_hide();
    NAV_LOG_ON_FAIL(i4_ret);
}

INT32 nav_retail_mode_is_show_dialog(VOID)
{
    NAV_RETAIL_MODE_POPUP_DLG_T e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;
    UINT8   ui1_demo_mode = 0;

    a_cfg_cust_get_demo_mode_value(&ui1_demo_mode);

    if (ui1_demo_mode != 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_exit_setup
 * Description
 *      Hide retail mode pause dialog
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_exit_setup(VOID)
{
    INT32 i4_ret = NAVR_OK;
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    if (pt_this->e_status == NAV_RETAIL_MODE_RUNNING)
    {
        _nav_retail_mode_init_pic_mode();
    }

    i4_ret = _nav_retail_mode_set_status(NAV_RETAIL_MODE_EXIT);
    NAV_LOG_ON_FAIL(i4_ret);

    /* if exit dialog is popup, need hide it */
    i4_ret = _nav_retail_mode_exit_hide();
    NAV_CHK_FAIL(i4_ret);

    return i4_ret ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_retail_mode_go_pause_setup
 * Description
 *      Hide retail mode pause dialog
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_go_pause_setup(VOID)
{
    INT32               i4_ret = NAVR_OK;

    i4_ret = _nav_retail_mode_set_status(NAV_RETAIL_MODE_PAUSE);
    NAV_LOG_ON_FAIL(i4_ret);

    /* if exit dialog is popup, need hide it */
    i4_ret = _nav_retail_mode_exit_hide();
    NAV_CHK_FAIL(i4_ret);

    _nav_retail_mode_start_pause_timer();

    return i4_ret;
}

static INT32 _nav_retail_mode_go_play_setup(VOID)
{
    INT32               i4_ret = NAVR_OK;

    i4_ret = _nav_retail_mode_set_status(NAV_RETAIL_MODE_RUNNING);
    NAV_LOG_ON_FAIL(i4_ret);

    /* if exit dialog is popup, need hide it */
    i4_ret = _nav_retail_mode_exit_hide();
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = _nav_retail_mode_check_logo();
    NAV_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _nav_retail_mode_check_logo(VOID)
{
    INT32           i4_ret;
    VSH_SRC_RESOLUTION_INFO_T   t_res;
    _NAV_RETAIL_MODE_T*         pt_this = &t_g_retail_mode;
    UINT8                       ui1_demo_type = 0;

    a_cfg_custom_get_demo_type(&ui1_demo_type);

    c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
    i4_ret = c_svctx_get_video_src_resolution(nav_get_crnt_svctx(),&t_res);

    DBG_INFO(("< retail mode >get resolution check signal.w:%d,h:%d.\n",t_res.ui4_width,t_res.ui4_height));
    if( pt_this->e_status == NAV_RETAIL_MODE_PAUSE ||  pt_this->e_status == NAV_RETAIL_MODE_EXIT || pt_this->e_status == NAV_RETAIL_MODE_ERROR )
    {
        NAV_LOG_ON_FAIL(NAVR_NO_ACTION);
        return NAVR_OK;
    }

    if (_nav_retail_mode_get_running_type() != RETAIL_MODE_TYPE_OVERLAY
        || _nav_retail_mode_check_running_type() != RETAIL_MODE_TYPE_OVERLAY
        || t_res.ui4_width != 0
        || b_last_input_signal_locked
        || ui1_demo_type != 0xF0)
    {
      /*not need*/
      return retail_mode_view_logo_hide();
    }

    return retail_mode_view_logo_show();
}

static INT32 _nav_retail_mode_stop_overlay_setup_env()
{
    INT32 i4_ret = NAVR_OK;
#ifdef APP_RETAIL_MODE_4K_OVERLAY_SUPPORT
    if (TRUE == b_4k_overlay)
    {
        t_dfb_config_layer0.flags = (DLCONF_WIDTH | DLCONF_HEIGHT);
        i4_ret = _nav_retail_mode_set_dfb_layer_config(NAV_RETAIL_MODE_DFB_LAYER_0, &t_dfb_config_layer0);
        NAV_LOG_ON_FAIL(i4_ret);

        t_dfb_config_layer0.flags = (DLCONF_BUFFERMODE);
        i4_ret = _nav_retail_mode_set_dfb_layer_config(NAV_RETAIL_MODE_DFB_LAYER_0, &t_dfb_config_layer0);
        NAV_LOG_ON_FAIL(i4_ret);
        b_4k_overlay = FALSE;
    }
#endif
    return i4_ret;
}

static INT32 _nav_retail_mode_stop_video_setup_env()
{
    INT32               i4_ret = NAVR_OK;

    a_nav_ctrl_ipt_set_change_source_enable(TRUE);

    a_input_src_do_cmd (NAV_IPTS_CMD_MDL_RELOAD_CRNT_SRC, NULL, NULL);

    a_tv_net_disable_keyroute(FALSE);

    a_scrn_svr_set_enable(TRUE);

    return i4_ret;
}

static INT32 _nav_retail_mode_stop_internal_video_setup_env(VOID)
{
    return _nav_retail_mode_stop_video_setup_env();
}

static INT32 _nav_retail_mode_go_pause_setup_env(VOID)
{
    INT32               i4_ret = NAVR_OK;
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    a_icl_custom_set_demo_status(0);

    a_tv_custom_set_banner_visiable_allow(TRUE);

    a_cfg_custom_set_retail_mode_led_ctrl(FALSE);

    if (pt_this->e_resume_from_app == NAV_RETAIL_MODE_RESUME_FROM_POWER)
    {
        i4_ret = _nav_retail_mode_reset_pic_mode();
        NAV_LOG_ON_FAIL(i4_ret);
        pt_this->b_is_ignore_pic_nfy = TRUE;
        pt_this->e_resume_from_app  = NAV_RETAIL_MODE_RESUME_FROM_NULL;
    }

    if (FALSE == a_wzd_is_oobe_mode())
    {
        a_amb_enable_system_key(TRUE);
    }

    /* enable screen saver */
    a_scrn_svr_set_enable(TRUE);

    /* enable BT */
    //a_bluetooth_gattc_force_stop_scan(FALSE);
    /* enable softAP */
    rest_start_softap_ex();

    return i4_ret;
}

static INT32 _nav_retail_mode_start_overlay_setup_env()
{
    INT32 i4_ret = NAVR_OK;
    a_amb_enable_system_key(FALSE);
    //	nav_ci_set_visible(FALSE);
#ifdef APP_RETAIL_MODE_4K_OVERLAY_SUPPORT
    i4_ret = _nav_retail_mode_get_dfb_layer_config(NAV_RETAIL_MODE_DFB_LAYER_0, &t_dfb_config_layer0);
    NAVR_CHK_FAIL(i4_ret);

    b_4k_overlay = TRUE;
    DFBDisplayLayerConfig t_dfb_config_layer0_4k_overlay;
    t_dfb_config_layer0_4k_overlay.width = NAV_RETAIL_MODE_4K_OVERLAY_W;
    t_dfb_config_layer0_4k_overlay.height = NAV_RETAIL_MODE_4K_OVERLAY_H;
    t_dfb_config_layer0_4k_overlay.buffermode =  DLBM_BACKVIDEO;

    t_dfb_config_layer0_4k_overlay.flags = DLCONF_BUFFERMODE;
    i4_ret = _nav_retail_mode_set_dfb_layer_config(NAV_RETAIL_MODE_DFB_LAYER_0, &t_dfb_config_layer0_4k_overlay);
    NAVR_CHK_FAIL(i4_ret);
    DBG_INFO(("[Retail Mode] Succeeded to set dfb double buffer mode for layer%d.\n", NAV_RETAIL_MODE_DFB_LAYER_0));

    t_dfb_config_layer0_4k_overlay.flags = (DLCONF_WIDTH | DLCONF_HEIGHT);
    i4_ret = _nav_retail_mode_set_dfb_layer_config(NAV_RETAIL_MODE_DFB_LAYER_0, &t_dfb_config_layer0_4k_overlay);
    NAVR_CHK_FAIL(i4_ret);
    DBG_INFO(("[Retail Mode] Succeeded to set resolution(%d, %d) for layer%d.\n", NAV_RETAIL_MODE_4K_OVERLAY_W,
                NAV_RETAIL_MODE_4K_OVERLAY_H, NAV_RETAIL_MODE_DFB_LAYER_0));
#endif
    return i4_ret;
}

static INT32 _nav_retail_mode_start_video_setup_env()
{
    INT32               i4_ret = NAVR_OK;

    a_tv_net_disable_keyroute(TRUE);
    a_amb_enable_system_key(FALSE);
    a_scrn_svr_set_enable(FALSE);

    return i4_ret;
}

static INT32 _nav_retail_mode_start_internal_video_setup_env(VOID)
{
    INT32               i4_ret = NAVR_OK;
    i4_ret = _nav_retail_mode_start_video_setup_env();
    return i4_ret;
}

static INT32 _nav_retail_mode_go_play_setup_env(VOID)
{
    INT32               i4_ret = NAVR_OK;
    /*common*/
    {
        i4_ret = a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
        NAV_CHK_FAIL(i4_ret);

        i4_ret = a_icl_custom_set_demo_status(1);
        NAV_CHK_FAIL(i4_ret);

        /*bluetooth*/
        //i4_ret = a_bluetooth_gattc_force_stop_scan(TRUE);
        //NAV_CHK_FAIL(i4_ret == CLIR_OK ? NAVR_OK : i4_ret);
        /*wifi*/
        rest_stop_softap_ex();

        /*disable zoom*/
        a_cfg_cust_set_zoom_mode(APP_CFG_CUST_ZOOM_MODE_OFF);
        rest_event_notify("app/zoom/enabled", APP_CFG_CUST_ZOOM_MODE_OFF, "");
        c_wgl_enable_zoom(FALSE);

#ifdef APP_TTS_SUPPORT
        /*disable tts*/
        a_cfg_set_tts_switch_status(0);
        a_cfg_update_tts_switch_status();
        rest_event_notify("app/tts/enabled", 0, "");
        a_registry_set_tts_state(REG_TTS_STATE_OFF);
#endif
    }

    return i4_ret;
}

static INT32 _nav_retail_mode_set_play_env(VOID)
{
    INT32           i4_ret = NAVR_OK;
    CHAR            s_active_app[APP_NAME_MAX_LEN + 1] = {0};
    VSH_SRC_RESOLUTION_INFO_T     t_res;

    c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
    i4_ret = c_svctx_get_video_src_resolution(nav_get_crnt_svctx(),&t_res);

    i4_ret = a_am_get_active_app (s_active_app);
    NAV_CHK_FAIL(i4_ret == AMR_OK ? NAVR_OK :i4_ret);
    if(nav_is_channel_scan_active())
    {
        a_tuner_setup_stop_scan(NULL,0);
    }

    /* if current app is not nav, resume it. */
    if (0 != c_strcmp(s_active_app, NAV_NAME)
        && 0 != c_strcmp(s_active_app, MSCVT_NAME)
        && a_nav_retail_mode_check_is_resume_nav())
    {
        if(e_active_app == ACTIVE_APP_3RD)
        {
            rest_event_notify_current_input("hdmi1");
            a_amb_resume_app(NAV_NAME);
            a_tv_set_input_src_id (TV_WIN_ID_MAIN, 2);

            return NAVR_OK;
        }
        DBG_INFO(("[RETAIL MODE]current active app:%s\n", s_active_app));
        /*see resume handle msg  */
        i4_ret =nav_resume_self();
        NAV_CHK_FAIL(i4_ret);
        DBG_INFO(("[RETAIL MODE]change active app to navigator\n"));
        if(0 == c_strcmp(s_active_app, MMP_NAME) )
        {
            a_tv_set_input_src_id (TV_WIN_ID_MAIN, 2);
            return NAVR_OK;
        }
    }

    {
        if(0 == c_strcmp(s_active_app, MSCVT_NAME) )
        {
            a_amb_resume_app(NAV_NAME);
            DBG_INFO(("[RETAIL MODE]change active app to navigator\n"));
        }
        if (_is_need_change_hdmi_port(&ui1_cur_hdmi_port)&&t_res.ui4_width == 0)
        {
            /* see signal handle msg  */
            ui1_chg_to_signal_input = ui1_cur_hdmi_port;
            i4_ret = a_nav_retail_mode_chg_inp_src_to_hdmi(ui1_cur_hdmi_port);
            NAV_LOG_ON_FAIL(i4_ret);    /*NAV_CHK_FAIL(i4_ret);*/
            DBG_INFO(("[RETAIL MODE]change src acfg to HDMI%d.\n",ui1_cur_hdmi_port+1));
            /*Clear hdmi statue when change hdmi*/
            _nav_retail_mode_cec_clear_element();

        }
        else
        {
            if (a_nav_retail_mode_need_chg_inp_src_to_hdmi() == TRUE)
            {
                /* see signal handle msg  */
                ui1_cur_hdmi_port = 0;
                i4_ret = a_nav_retail_mode_chg_inp_src_to_hdmi(0);
                NAV_LOG_ON_FAIL(i4_ret);	 /*NAV_CHK_FAIL(i4_ret);*/
                DBG_INFO(("[RETAIL MODE]change src acfg to HDMI1.\n"));
                /*Clear hdmi statue when change hdmi*/
                _nav_retail_mode_cec_clear_element();

            }
        }
    }

    return NAVR_OK;
}

static INT32 _nav_retail_mode_check_play_env(VOID)
{
	INT32           i4_ret = NAVR_OK;
	UINT8		    ui1_hdmi_port = 0;
	VSH_SRC_RESOLUTION_INFO_T     t_res;
    ISL_REC_T       t_isl_rec           = {0};

	c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
	i4_ret = c_svctx_get_video_src_resolution(nav_get_crnt_svctx(),&t_res);
	NAV_LOG_ON_FAIL(i4_ret);

   {
        CHAR            s_active_app[APP_NAME_MAX_LEN + 1] = {0};
        i4_ret = a_am_get_active_app (s_active_app);
        NAV_CHK_FAIL(i4_ret == AMR_OK ? NAVR_OK :i4_ret);

        if (0 != c_strcmp(s_active_app, NAV_NAME) && a_nav_retail_mode_check_is_resume_nav())
        {
        	/*navigator can not resume right now after resume*/
        	if (b_force_enable_store_mode ==0)
        	{
				return NAVR_NOT_ALLOW;
			}

        }
   }

   {
   	   	b_force_enable_store_mode = 0;

        if (a_nav_retail_mode_need_chg_inp_src_to_hdmi() == TRUE)
        {
           return NAVR_NOT_ALLOW;
        }
        if (nav_is_channel_scan_active())
        {
            return NAVR_NOT_ALLOW;
        }

        /*if hdmi hot plug*/
        if (_is_need_change_hdmi_port(&ui1_cur_hdmi_port))
        {
            i4_ret = a_nav_ipts_get_crnt_isl_rec(&t_isl_rec);
            NAV_LOG_ON_FAIL(i4_ret);

            DBG_INFO(("[RETAIL MODE]t_res.ui4_width:%d,pt_isl_rec.ui1_internal_id:%d.\n\r", t_res.ui4_width,t_isl_rec.ui1_internal_id));
            if (t_res.ui4_width == 0)
            {
                /*current hdmi source without signal*/
                if (a_nav_ipts_is_hdmi_source(&t_isl_rec) == TRUE && t_isl_rec.ui1_internal_id != ui1_cur_hdmi_port)
                {
                    return NAVR_NOT_ALLOW;
                }
                /*current comb or tv source without signal*/
                else if(a_nav_ipts_is_hdmi_source(&t_isl_rec) != TRUE)
                {
                    return NAVR_NOT_ALLOW;
                }

            }
        }
   }

   return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_retail_mode_update_rest_currentapp
 * Description
 *     Update current app to SCPL on storedemo started running
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *     None
 *---------------------------------------------------------------------------*/
VOID nav_retail_mode_update_rest_currentapp()
{
   int    name_space = 1;
   DBG_INFO(("[RETAIL MODE] [%s] Update app/current to SCPL after storedemo started running \n\r", __FUNCTION__));
   rest_event_notify("app/current", name_space+1, "4");
}


/*-----------------------------------------------------------------------------
 * Name
 *      nav_retail_mode_go
 * Description
 *      Goto retail mode status
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 nav_retail_mode_go(NAV_RETAIL_MODE_STATUS_T e_status)
{
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;
    INT32               i4_ret = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] e_status: %X \r\n", __FUNCTION__, e_status));

    switch (e_status)
    {
        case NAV_RETAIL_MODE_INITIAL:
            break;

        case NAV_RETAIL_MODE_LAUNCHING:
            break;

        case NAV_RETAIL_MODE_CHECKING:
            return _nav_retail_mode_check_play_env();
            break;

        case NAV_RETAIL_MODE_RUNNING:
            i4_ret = _nav_retail_mode_check_play_env();
            if(i4_ret == NAVR_NOT_ALLOW)
            {
                i4_ret = _nav_retail_mode_set_play_env();
                NAV_BREAK_ON_FAIL(i4_ret);
                if(_nav_retail_mode_get_status() == NAV_RETAIL_MODE_RUNNING)
                {
                    i4_ret = _nav_retail_mode_go_running();
                	NAV_BREAK_ON_FAIL(i4_ret);
                    return NAVR_OK;
                }
                /*it is better to return other value */
                i4_ret = _nav_retail_mode_set_status(NAV_RETAIL_MODE_CHECKING);
                NAV_BREAK_ON_FAIL(i4_ret);
                return NAVR_OK;
            }
            NAV_BREAK_ON_FAIL(i4_ret);

            i4_ret = _nav_retail_mode_go_running();
            NAV_BREAK_ON_FAIL(i4_ret);

            break;

        case NAV_RETAIL_MODE_PAUSE:
            i4_ret = _nav_retail_mode_go_pause();
            NAV_BREAK_ON_FAIL(i4_ret);
            break;

        case NAV_RETAIL_MODE_EXIT:
            i4_ret = _nav_retail_mode_exit();
            NAV_BREAK_ON_FAIL(i4_ret);
            i4_ret = _nav_retail_mode_recover_wzd_stat();
            NAV_BREAK_ON_FAIL(i4_ret);
            a_stop_retail_demo();
            i4_ret = _nav_retail_mode_stop_overlay_setup_env();
            NAV_BREAK_ON_FAIL(i4_ret);
            break;

        default:
            break;
    }

    if(i4_ret != NAVR_OK)
    {
       pt_this->e_status = NAV_RETAIL_MODE_ERROR;
       NAV_CHK_FAIL(i4_ret);
    }

    a_registry_set_store_demo_status(e_status);
    if(e_status == NAV_RETAIL_MODE_RUNNING)
    {
        nav_retail_mode_update_rest_currentapp();
    }
    i4_ret = _nav_retail_mode_set_status(e_status);
    NAV_CHK_FAIL(i4_ret);

    i4_ret = _nav_retail_mode_update_volume();
    NAV_CHK_FAIL(i4_ret);

    _nav_retail_cec_hdmi_plug_in_out_recheck(e_status);

    {
        MSG_CONVERT_SEND_CMD_T t_send_cmd;
        UINT8      ui1_demo_mode = 0;

        a_cfg_cust_get_demo_mode_value(&ui1_demo_mode);
        char* s_command = "system_ui_hide";
        if(_nav_retail_mode_get_running_type() == RETAIL_MODE_TYPE_OVERLAY && (2 != ui1_demo_mode)) {
            s_command = "system_ui_show";
        }
        DBG_LOG_PRINT(("[RETAIL MODE] [%s][%d] Sending %s.\n", __FUNCTION__, __LINE__, s_command));
        t_send_cmd.s_source = "am";
        t_send_cmd.s_destination = "browser_ctrl";
        t_send_cmd.s_ack = NULL;
        t_send_cmd.s_command = s_command;
        t_send_cmd.s_parameter = NULL;
        a_msg_convert_send_command(&t_send_cmd);
    }

    DBG_LOG_PRINT(("[RETAIL MODE] [%s] End(%X) \r\n", __FUNCTION__, i4_ret));
    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_stop_play
 *
 * Description: start playing video or demo swf
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_stop_play()
{
    INT32               i4_ret = NAVR_OK;
    RETAIL_MODE_RUNNING_TYPE_T e_type = RETAIL_MODE_TYPE_UNKNOW;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    e_type = _nav_retail_mode_get_running_type();
    DBG_INFO(("[RETAIL MODE]stop running type: %d.\n\r", e_type));
    if (e_type == RETAIL_MODE_TYPE_OVERLAY)
    {
        i4_ret = _nav_retail_mode_stop_overlay();
        NAV_CHK_FAIL(i4_ret);
    }
#ifdef APP_3D_RETAIL_DEMO_MODE
    else if (e_type == RETAIL_MODE_TYPE_VIDEO)
    {
        i4_ret = _nav_retail_mode_stop_video();
        NAV_CHK_FAIL(i4_ret);
    }
    else if (e_type == RETAIL_MODE_TYPE_VIDEO_INTERNAL)
    {
        i4_ret = _nav_retail_mode_stop_internal_video();
        NAV_CHK_FAIL(i4_ret);
    }
#endif
    else if(e_type == RETAIL_MODE_TYPE_UNKNOW)
    {
        /* do nothing for start play*/
        return NAVR_OK;
    }
    else
    {

        NAV_CHK_FAIL(NAVR_NOT_EXIST);
    }
    a_rest_leave_cast_input();

    DBG_INFO(("[RETAIL MODE]End.\n\r"));

    return NAVR_OK;

}
/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_stop_play_by_power_off
 *
 * Description: for power off stop play  retail mode do not switch input source
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_stop_play_by_power_off()
{
    INT32               i4_ret = NAVR_OK;
    RETAIL_MODE_RUNNING_TYPE_T e_type = RETAIL_MODE_TYPE_UNKNOW;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    e_type = _nav_retail_mode_get_running_type();
    DBG_INFO(("[RETAIL MODE]stop running type: %d.\n\r", e_type));
    if (e_type == RETAIL_MODE_TYPE_OVERLAY)
    {
        i4_ret = _nav_retail_mode_stop_overlay();
        NAV_CHK_FAIL(i4_ret);
    }
#ifdef APP_3D_RETAIL_DEMO_MODE
    else if (e_type == RETAIL_MODE_TYPE_VIDEO)
    {
        i4_ret = nav_retail_stop_end_cap();
        NAV_CHK_FAIL(i4_ret);

        a_tv_net_disable_keyroute(FALSE);

        a_scrn_svr_set_enable(TRUE);
    }
    else if (e_type == RETAIL_MODE_TYPE_VIDEO_INTERNAL)
    {
        i4_ret = nav_retail_stop_internal_video();
        NAV_CHK_FAIL(i4_ret);

        a_tv_net_disable_keyroute(FALSE);

        a_scrn_svr_set_enable(TRUE);
    }
#endif
    else if(e_type == RETAIL_MODE_TYPE_UNKNOW)
    {
        /* do nothing for start play*/
        return NAVR_OK;
    }
    else
    {
        NAV_CHK_FAIL(NAVR_NOT_EXIST);
    }

    /*update type*/
    i4_ret = _nav_retail_mode_set_running_type(RETAIL_MODE_TYPE_UNKNOW);
    NAV_CHK_FAIL(i4_ret);


    DBG_INFO(("[RETAIL MODE]End.\n\r"));

    return NAVR_OK;

}

/*----------------------------------------------------------------------------
 * Name: nav_retail_mode_start_play
 *
 * Description: start playing video or demo swf
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_retail_mode_start_play()
{
    INT32               i4_ret = NAVR_OK;
    RETAIL_MODE_RUNNING_TYPE_T e_type = RETAIL_MODE_TYPE_UNKNOW;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    /*check need to play type, not retail mode type*/
    e_type =  _nav_retail_mode_check_running_type();
    DBG_INFO(("[RETAIL MODE]start running type: %d.\n\r", e_type));

    if (e_type == RETAIL_MODE_TYPE_OVERLAY)
    {
        i4_ret = _nav_retail_mode_start_overlay();
        NAV_CHK_FAIL(i4_ret);
    }
#ifdef APP_3D_RETAIL_DEMO_MODE
    else if (e_type == RETAIL_MODE_TYPE_VIDEO)
    {
        i4_ret = _nav_retail_mode_start_video();
        NAV_CHK_FAIL(i4_ret);
    }
    else if (e_type == RETAIL_MODE_TYPE_VIDEO_INTERNAL)
    {
        i4_ret = _nav_retail_mode_start_internal_video();
        NAV_CHK_FAIL(i4_ret);
    }
#endif
    else if(e_type == RETAIL_MODE_TYPE_UNKNOW)
    {
        return NAVR_OK;
    }
    else
    {
        NAV_CHK_FAIL(NAVR_NOT_EXIST);
    }

    DBG_INFO(("[RETAIL MODE]End.\n\r"));
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_retail_mode_set_resume_from_app
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_retail_mode_set_resume_from_app(NAV_RETAIL_MODE_RESUME_FROM_T e_resume)
{
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] e_resume: %X \r\n", __FUNCTION__, e_resume));

    pt_this->e_resume_from_app = e_resume;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_retail_mode_get_resume_from_app
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
NAV_RETAIL_MODE_RESUME_FROM_T a_nav_retail_mode_get_resume_from_app(VOID)
{
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    return pt_this->e_resume_from_app;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_retail_mode_get_status
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_retail_mode_get_status(NAV_RETAIL_MODE_STATUS_T* pe_status)
{
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    if(pe_status == NULL)
    {
        return NAVR_INV_ARG;
    }

    *pe_status = pt_this->e_status;
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_retail_mode_get_running_type
 * Description overlay/video demo/internal video demo
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
RETAIL_MODE_RUNNING_TYPE_T a_nav_retail_mode_get_running_type(VOID)
{
    //nav_request_context_switch
    return _nav_retail_mode_get_running_type();
}
RETAIL_MODE_RUNNING_TYPE_T a_nav_retail_mode_check_running_type(VOID)
{
    //nav_request_context_switch
    return _nav_retail_mode_check_running_type();
}
INT32 a_nav_retail_mode_update_running_type(VOID)
{
    //nav_request_context_switch
    return _nav_retail_mode_update_running_type();
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_retail_mode_get_dlg_show
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_retail_mode_get_dlg_show(NAV_RETAIL_MODE_POPUP_DLG_T* pe_popup_dlg)
{
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    if(pe_popup_dlg == NULL)
    {
        return NAVR_INV_ARG;
    }

    *pe_popup_dlg = pt_this->e_popup_dlg;
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_retail_mode_get_start_from_oobe
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
BOOL a_nav_retail_mode_get_start_from_oobe(VOID)
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    if (pt_this->b_is_pause_timer_start )//|| pt_this->b_is_pair_page
    {
        return TRUE;
    }
    return FALSE;
}

BOOL a_retail_mode_is_key_to_discard(UINT32 ui4_key_code)
{
    ACFG_RETAIL_MODE_T          t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    _NAV_RETAIL_MODE_T*         pt_this = &t_g_retail_mode;

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL != t_retail_mode)
    {
        return FALSE;
    }

    if (NAV_RETAIL_MODE_POPUP_LAUNCHING_DLG == pt_this->e_popup_dlg ||
        NAV_RETAIL_MODE_POPUP_PAUSE_DLG == pt_this->e_popup_dlg ||
        NAV_RETAIL_MODE_POPUP_RESUME_DLG == pt_this->e_popup_dlg)
    {
        DBG_INFO(("[RETAIL MODE]e_retail_mode_popup_dlg: %d.\n\r", pt_this->e_popup_dlg));
        return TRUE;
    }

    if ((NAV_RETAIL_MODE_RUNNING == pt_this->e_status) &&
        (pt_this->e_running_type == RETAIL_MODE_TYPE_VIDEO ||
         pt_this->e_running_type == RETAIL_MODE_TYPE_VIDEO_INTERNAL ||
         pt_this->e_running_type == RETAIL_MODE_TYPE_OVERLAY
        ))
    {
        // DBG_INFO(("[RETAIL MODE]video is playing.\n\r");

        if (IOM_GET_EVT_GRP(ui4_key_code) == KEY_GROUP_AUD_CTRL || ui4_key_code == BTN_SELECT)
        {
            return FALSE;
        }
		else if(nav_get_active_component() == NAV_COMP_ID_DIALOG && (ui4_key_code == BTN_SELECT || ui4_key_code == BTN_CURSOR_LEFT || ui4_key_code == BTN_CURSOR_RIGHT))
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }

    return FALSE;
}

INT32 a_retail_mode_rcu_key_pre_handler(NAV_EVN_T* pt_event)
{
    return NAVR_OK;

    UINT32  ui4_key_event= pt_event->ui4_data1 ;
    UINT32  ui4_key_code = pt_event->ui4_data2 ;

    //BOOL                      b_is_skip_exit_key = FALSE;
    BOOL                        b_is_need_pause_retail = FALSE;
    CHAR                        s_app_name [APP_NAME_MAX_LEN + 1];
    TV_WIN_ID_T                 e_focus_id = TV_WIN_ID_MAIN;
    ACFG_RETAIL_MODE_T          t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    NAV_RETAIL_MODE_STATUS_T    e_retail_status = NAV_RETAIL_MODE_INITIAL;
    NAV_RETAIL_MODE_POPUP_DLG_T e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    a_am_get_active_app(s_app_name);

    if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode &&
       (c_strcmp(s_app_name, NAV_NAME) == 0))
    {
        /* if pause or launching dialog popup, just return */
        if( NAV_RETAIL_MODE_POPUP_PAUSE_DLG == e_popup_dlg  ||
            NAV_RETAIL_MODE_POPUP_LAUNCHING_DLG == e_popup_dlg)
        {
            return NAVR_DO_NOT_CONTINUE;
        }
        /* retail mode pause state key handle */
        a_nav_retail_mode_get_status(&e_retail_status);
        if (e_retail_status == NAV_RETAIL_MODE_RUNNING)
        {
            if (//ui4_key_code == BTN_ASPECT        ||
                //ui4_key_code == BTN_INPUT_SRC ||
                //ui4_key_code == BTN_PRG_INFO  ||
                //ui4_key_code == BTN_EPG       ||
                ui4_key_code == BTN_PRG_UP      ||
                ui4_key_code == BTN_PRG_DOWN    ||
                ui4_key_code == BTN_PREV_PRG    //||
                //ui4_key_code == BTN_3D            ||
                //ui4_key_code == BTN_P_EFFECT  ||
                //ui4_key_code == BTN_CC
                )
            {
                b_is_need_pause_retail = TRUE;
            }

            switch(ui4_key_code)
            {
            case BTN_DIGIT_0:
            case BTN_DIGIT_1: case BTN_DIGIT_2: case BTN_DIGIT_3:
            case BTN_DIGIT_4: case BTN_DIGIT_5: case BTN_DIGIT_6:
            case BTN_DIGIT_7: case BTN_DIGIT_8: case BTN_DIGIT_9:
                nav_get_focus_id(&e_focus_id);
                if (nav_get_src_type(e_focus_id) == INP_SRC_TYPE_TV &&
                    nav_get_locked_status(e_focus_id) != LOCKED_STATUS_INP_SRC_LOCKED &&
                    FALSE == nav_is_svl_empty(e_focus_id))
                {
                    b_is_need_pause_retail = TRUE;
                }
            }
            /* pause retail mode */
            if (b_is_need_pause_retail)
            {
                nav_retail_mode_go(NAV_RETAIL_MODE_PAUSE);
                _nav_retail_mode_start_pause_timer();
            }
        }
        else if (e_retail_status == NAV_RETAIL_MODE_PAUSE)
        {
            /* restart the timer when key be pressed */
            if(WGL_MSG_KEY_UP == ui4_key_event)
            {
                _nav_retail_mode_start_pause_timer();
            }
        }
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_retail_mode_resume_demo
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_retail_mode_resume_demo(BOOL b_delay)
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;
    INT32 i4_ret = NAVR_OK;

    if (pt_this->e_status == NAV_RETAIL_MODE_LAUNCHING )
    {
        /* demo mode is launching by menu sidebar or other ways */
        DBG_INFO(("[RETAIL MODE]demo mode is launching already.\n\r"));
        return NAVR_OK;
    }

    i4_ret = nav_retail_mode_go(NAV_RETAIL_MODE_RUNNING);
    NAV_CHK_FAIL(i4_ret);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_retail_mode_pause_demo
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_retail_mode_pause_demo(VOID)
{
    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    _nav_retail_pause_dlg_exit_fct();

    return NAVR_OK;
}

VOID nav_retail_mode_skip_chg_src(BOOL b_val)
{
    DBG_INFO(("[RETAIL MODE]b_is_skip_chg_inp_src: %d.\n\r", b_val));
    b_is_skip_chg_inp_src = b_val;
}

BOOL a_nav_retail_mode_need_chg_inp_src_to_hdmi(VOID)
{
    UINT8 ui1_idx_mode = 0x00;
    ISL_REC_T   t_isl_rec   =  {0};

    /* Check the input source on FOCUSED WIN */
    _get_crnt_isl(&t_isl_rec);
    if (TRUE == b_is_skip_chg_inp_src)
    {
        DBG_INFO(("[RETAIL MODE] %s, b_is_skip_chg_inp_src\n", __FUNCTION__));
        return FALSE;
    }
    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV
        && (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI)&&nav_is_running(TV_WIN_ID_MAIN))
    {
       return FALSE;
    }

    if (t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL || t_isl_rec.e_src_type == INP_SRC_TYPE_MM)
    {
        return TRUE;
    }

    {
        UINT16      ui2_status  = 0;
        UINT8       ui1_state   = 0;
        UINT8       ui1_index   = 0;
        a_cfg_cust_get_retail_mode_source_info(&ui1_idx_mode);
        a_cfg_get_wzd_status(&ui2_status);

        ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
        ui1_index = WZD_UTIL_GET_STATUS_IDX(ui2_status);

        if ((ui1_state == WZD_STATE_RESUME_C4TV && ui1_index != WZD_PAGE_INDEX_C4TV_STORE_DEMO))
        {
            if((t_isl_rec.e_src_type == INP_SRC_TYPE_AV||t_isl_rec.e_src_type == INP_SRC_TYPE_TV)&&nav_is_running(TV_WIN_ID_MAIN))
            {
                return FALSE;
            }
            if(!(ui1_idx_mode&0x01))
            {
                return TRUE;
            }
            return TRUE;
        }
    }

    DBG_INFO(("[RETAIL MODE] [%s] End \r\n", __FUNCTION__));

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_retail_mode_chg_inp_src_to_hdmi
 * Description  change input source to HDMI
 * Input        -
 * Output       -
 * Returns      -
 *---------------------------------------------------------------------------*/
INT32 a_nav_retail_mode_chg_inp_src_to_hdmi(UINT8 ui1_hdmi_port)
{
    ISL_REC_T       t_isl_rec;
    INT32           i4_ret;
    UINT8           ui1_index = 0;
    UINT8           ui1_src_num = 0;
    BOOL            b_found_hdmi = TRUE;
    TV_WIN_ID_T     e_tv_win_id = TV_WIN_ID_MAIN;
    UINT16          ui2_status    = 0;
    UINT8        	ui1_state    = 0;
    UINT8       	ui1_idx_mode = 0x00;
    UINT32          ui4_tv_capability = 0;
    a_cfg_get_wzd_status(&ui2_status);

    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    a_isl_get_num_rec(&ui1_src_num);

    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);
        if (i4_ret != APP_CFGR_OK)
        {
            return NAVR_FAIL;
        }

        if ((t_isl_rec.e_src_type == INP_SRC_TYPE_AV) &&
            (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI ||
             t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI))
        {

			/*tv automatically select hdmi port */
			ui1_index += ui1_hdmi_port;
			i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);
			if (i4_ret != APP_CFGR_OK)
			{
				return NAVR_FAIL;
			}
			DBG_INFO(("[RETAIL MODE]switch to hdmi port:%d .\n\r",ui1_hdmi_port+1));

            b_found_hdmi = TRUE;
            break;
        }
    }
    if((ui1_state == WZD_STATE_RESUME_C4TV))
    {
        i4_ret = a_cfg_cust_get_retail_mode_source_info(&ui1_idx_mode);
        if(ui1_idx_mode&0x01) //means source is changed during last OOBE demo mode
        {
            //ui1_index = ((ui1_idx_mode&0xF0)>>4);
            i4_ret = a_isl_get_rec_by_idx(((ui1_idx_mode&0xF0)>>4), &t_isl_rec);
            if((t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL)||(t_isl_rec.e_src_type == INP_SRC_TYPE_MM))
            {
                a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);
                NAV_LOG_ON_FAIL(i4_ret);
            }
        }

    }
    if (b_found_hdmi)
    {
        i4_ret = nav_get_focus_id(&e_tv_win_id);
        NAV_CHK_FAIL(i4_ret);
        a_tv_get_capability (&ui4_tv_capability);
		DBG_INFO(("<NAV INPUT> %s_%d capability:%d \r\n",__FUNCTION__,__LINE__,(ui4_tv_capability & TV_CAPABILITY_MASK_ALLOW_INPUT_SOURCE_CHANGE)));
        /* note : some time return -15 for c4tv*/
        if((ui1_state == WZD_STATE_RESUME_C4TV)&&(ui4_tv_capability & TV_CAPABILITY_MASK_ALLOW_INPUT_SOURCE_CHANGE))
        {
            i4_ret = nav_change_av_inp_by_rec(e_tv_win_id, &t_isl_rec, NULL);
        }
        else
        {
            a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
            i4_ret = nav_ipts_switch_src(NAV_IPTS_SMS_BY_ID, e_tv_win_id, t_isl_rec.ui1_id);
            a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
        }
        NAV_CHK_FAIL(i4_ret);

        /*For no svl record case,change to tv source will not select svc,so will no svctx message such as no_signal signal_lock*/
        if((nav_is_svl_empty(TV_WIN_ID_MAIN) == TRUE)&&(ui1_state == WZD_STATE_RESUME_C4TV)&&(t_isl_rec.e_src_type == INP_SRC_TYPE_TV))
        {
            DBG_INFO(("[RETAIL MODE]will go running directly as for no svl record case.\n\r"));
            i4_ret = _nav_retail_mode_go_running();
            NAV_LOG_ON_FAIL(i4_ret);
        }

    }
    return NAVR_OK;
}

INT32 a_nav_retail_mode_chg_inp_src_to_hdmi_pre(VOID)
{
    ISL_REC_T       t_isl_rec;
    INT32           i4_ret;
    UINT8           ui1_index = 0;
    UINT8           ui1_src_num = 0;
    UINT8           ui1_src_index = 0;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    a_isl_get_num_rec(&ui1_src_num);

    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);
        if (i4_ret != APP_CFGR_OK)
        {
            return NAVR_FAIL;
        }

        if ((t_isl_rec.e_src_type == INP_SRC_TYPE_AV) &&
            (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI ||
             t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI))
        {
            ui1_src_index = ui1_index;
            break;
        }
    }

    if (ui1_src_index < ui1_src_num)
    {
        a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_retail_mode_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_retail_mode_register(VOID)
{
    NAV_COMP_T      t_comp;
    INT32           i4_ret = NAVR_OK;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    t_comp.pf_init           = _nav_retail_mode_init;
    t_comp.pf_deinit         = _nav_retail_mode_deinit;
    t_comp.pf_is_key_handler = _nav_retail_mode_is_key_handler;
    t_comp.pf_activate       = _nav_retail_mode_activate;
    t_comp.pf_inactivate     = _nav_retail_mode_inactivate;
    t_comp.pf_hide           = _nav_retail_mode_hide;
    t_comp.pf_handle_msg     = _nav_retail_mode_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_RETAIL_MODE,
                                    &t_comp,
                                    COMP_EXEC_SET_RETAIL_MODE);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_nav_retail_mode_check_is_resume_nav
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
extern BOOL a_nav_retail_mode_check_is_resume_nav(VOID)
{
    CHAR                        s_app_name [APP_NAME_MAX_LEN + 1];
    ACFG_RETAIL_MODE_T          t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    _NAV_RETAIL_MODE_T*         pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    a_am_get_active_app(s_app_name);

    if (pt_this->ui4_yahoo_status != (UINT32)YAHOO_STATUS_HIDE ||
        pt_this->ui4_app_status != (UINT32)NW_APP_STATUS_HIDE)
    {
        DBG_INFO(("[RETAIL MODE] 3rd resume return!!\n"));
        e_active_app = ACTIVE_APP_3RD;
        return TRUE;
    }
    else if ((a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
        || (c_strcmp(s_app_name, MMP_NAME) == 0))
    {
        DBG_INFO(("[RETAIL MODE] mmp resume return!!\n"));
        e_active_app = ACTIVE_APP_MMP;
        return TRUE;
    }
    else if ((pt_this->e_resume_from_app == NAV_RETAIL_MODE_RESUME_FROM_NULL)
        && (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
        && (c_strcmp(s_app_name, MENU_NAME) == 0)
        && (NAV_RETAIL_MODE_PAUSE == pt_this->e_status))
    {
        /* menu dealing with special case, NOT start store demo */
        if (nav_is_channel_scan_active ())
        {
            DBG_INFO(("[RETAIL MODE] channel scanning , return!!\n"));
            e_active_app = ACTIVE_APP_MENU;
            return FALSE;
        }
        else
        {
            DBG_INFO(("\n[RETAIL MODE]  menu resume ,return!!\n"));
            e_active_app = ACTIVE_APP_MENU;
            return TRUE;
        }
    }
    else if(c_strcmp(s_app_name, MSCVT_NAME) == 0)
    {
       if (!a_wzd_is_oobe_mode())
       {
           return TRUE;
       }
//        e_active_app = ACTIVE_APP_3RD;


    }

    DBG_INFO(("[RETAIL MODE] [%s] default End \r\n", __FUNCTION__));
    e_active_app = ACTIVE_APP_UNKNOWN;

    return FALSE;
}

/*----------------------------------------------------------------------------
 * Name: a_nav_retail_mode_find_active_app
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
extern NAV_RETAILMODE_ACTIVE_APP_T a_nav_retail_mode_find_active_app(VOID)
{
    return e_active_app;
}

/*----------------------------------------------------------------------------
 * Name: _nav_retail_mode_exit_from_mmp
 *
 * Description: when get download speed, show these info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_retail_mode_exit_from_mmp(VOID*  pv_data1,
                                           VOID*  pv_data2,
                                           VOID*  pv_data3)
{
    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    nav_retail_exit_from_other_app(TRUE);
    nav_retail_mode_exit_key_hdlr((c4tv_apron_custom_nfy_fct)pv_data1);
}

/*----------------------------------------------------------------------------
 * Name: a_nav_retail_mode_exit_from_mmp
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
extern VOID a_nav_retail_mode_exit_from_mmp(c4tv_apron_custom_nfy_fct pf_nfy)
{
    nav_request_context_switch(_nav_retail_mode_exit_from_mmp, (VOID*)pf_nfy, NULL, NULL);
}

/*----------------------------------------------------------------------------
 * Name: a_nav_retail_mode_reset_env
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
extern VOID a_nav_retail_mode_reset_env(VOID)
{
    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    pt_this->e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;
    pt_this->e_resume_from_app = NAV_RETAIL_MODE_RESUME_FROM_NULL;

    /* enable the system keys */
    if(FALSE == a_wzd_is_oobe_mode())
    {
        a_amb_enable_system_key(TRUE);
    }

    /* enable screen saver */
    a_scrn_svr_set_enable(TRUE);

    /* allow info banner popup */
    a_tv_custom_set_banner_visiable_allow(TRUE);

    /* play demo or video */
    a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);

    a_cfg_custom_set_retail_mode_led_ctrl(TRUE);

    a_nav_power_set_component_enable(FALSE);

    _nav_retail_mode_init_pic_mode();

}
static INT32 _nav_retail_mode_start(RETAIL_MODE_PARAM_T* pt_param)
{
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;
    INT32               i4_ret = NAVR_OK;
	UINT8	            ui1_pq_dix;

    if (pt_param == NULL)
    {
        DBG_ERROR(("[RETAIL MODE]param is invalid.\n\r"));
        return NAVR_INV_ARG;
    }

    DBG_INFO(("[RETAIL MODE] [%s] current status: %d \r\n", __FUNCTION__, pt_this->e_status));

    if(pt_this->e_status == NAV_RETAIL_MODE_LAUNCHING
        || pt_this->e_status == NAV_RETAIL_MODE_RUNNING
        || pt_this->e_status == NAV_RETAIL_MODE_ERROR
        || pt_this->e_status == NAV_RETAIL_MODE_CHECKING)
    {
       return NAVR_NOT_ALLOW;
    }

    if(pt_this->e_status == NAV_RETAIL_MODE_PAUSE)
    {
        /* TODO: restart immediately */
        nav_retail_mode_go(NAV_RETAIL_MODE_RUNNING);
        return NAVR_OK;
    }

    DBG_INFO(("[RETAIL MODE] param from: %d, osd_type: %d, countdown: %u \r\n", \
                    pt_param->t_launch_info.e_launch_from_app, \
                    pt_param->t_launch_info.e_launch_osd_type, \
                    pt_param->t_launch_info.ui2_count));


    switch(pt_param->t_launch_info.e_launch_osd_type)
    {
        case RETAIL_MODE_LAUNCH_OSD_NULL:
        {
            a_nav_retail_mode_reset_env();
            i4_ret = nav_retail_mode_go(NAV_RETAIL_MODE_RUNNING);

            break;
        }


        case RETAIL_MODE_LAUNCH_OSD_COUNTDOWN:
        {
            NAV_COMP_SET_T      t_visible_comp = 0;

            /* disbale screen saver */
            a_scrn_svr_set_enable(FALSE);

            /* NOT allow info banner popup */
            a_tv_custom_set_banner_visiable_allow(FALSE);
            nav_get_components_visibility(~((NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_C4TV_APRON)) | (NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_RETAIL_MODE))), &t_visible_comp);
            if (t_visible_comp > 0)
            {
                nav_hide_components(t_visible_comp);
            }

            //if (TRUE == a_wzd_is_oobe_mode())
            {
                a_amb_enable_system_key(FALSE);
            }

            nav_retail_mode_go(NAV_RETAIL_MODE_LAUNCHING);

            pt_this->e_popup_dlg = NAV_RETAIL_MODE_POPUP_LAUNCHING_DLG;

            a_cfg_cust_get_demo_mode_value(&ui1_pq_dix);
            _backup_set_demo_idx(ui1_pq_dix);

            retail_mode_view_timer_start(RETAIL_MODE_VIEW_TIMER_NOTIFICATION, pt_param->t_launch_info.ui2_count*1000);
            retail_mode_view_show(NULL);

            break;
        }


        case RETAIL_MODE_LAUNCH_OSD_WARNING:
        {
            break;
        }


        default:
            NAV_LOG_ON_FAIL(NAVR_INV_ARG);
            break;
    }

    /*update popup dialog*/
    {
        DBG_INFO(("[RETAIL MODE] popup_dlg: %d.\n\r", pt_this->e_popup_dlg));
    }

    {
        if(pt_param->t_launch_info.e_launch_osd_type != RETAIL_MODE_LAUNCH_OSD_COUNTDOWN)
        {
            return NAVR_OK;
        }

        switch(pt_param->t_launch_info.e_launch_from_app)
        {
            case NAV_RETAIL_MODE_RESUME_FROM_MENU:
            case NAV_RETAIL_MODE_RESUME_FROM_WZD:
            {
                a_amb_pause_app(MENU_NAME);

                break;
            }


            case NAV_RETAIL_MODE_RESUME_FROM_HOTKEY:
            {
            #if 0
                 CHAR                s_app_name [APP_NAME_MAX_LEN+1] = {0};
                 a_am_get_active_app (s_app_name);

                 DBG_API(("[RETAIL MODE]current active app: %s.\n\r", s_app_name));
                 if( 0 != c_strcmp(s_app_name, NAV_NAME))
                 {
                    nav_resume_self();
                 }
            #endif

                break;
            }


            case NAV_RETAIL_MODE_RESUME_FROM_POWER:
            case NAV_RETAIL_MODE_RESUME_FROM_NULL:
            case NAV_RETAIL_MODE_RESUME_FROM_OOBE:
            {
                /* nothing to do*/
            }
            break;


            default:
            {
                NAV_LOG_ON_FAIL(NAVR_INV_ARG);
            }
            break;
        }
    }

    {
       pt_this->e_launch_osd_type = pt_param->t_launch_info.e_launch_osd_type;
       pt_this->ui2_count         = pt_param->t_launch_info.ui2_count;
       pt_this->e_resume_from_app = pt_param->t_launch_info.e_launch_from_app;
    }


    return NAVR_OK;
}

static VOID _nav_retail_mode_start_handle (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32 i4_ret = NAVR_OK;

    {
        RETAIL_MODE_PARAM_T t_param;

        c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));

        t_param.t_launch_info.e_launch_from_app = (NAV_RETAIL_MODE_RESUME_FROM_T)pv_tag1;
        t_param.t_launch_info.e_launch_osd_type = (RETAIL_MODE_LAUNCH_OSD_TYPE_T)pv_tag2;
        t_param.t_launch_info.ui2_count = (UINT32)pv_tag3;

        i4_ret = _nav_retail_mode_start(&t_param);
        if(i4_ret != NAVR_OK)
        {
            NAV_LOG_ON_FAIL(i4_ret);
            return;
        }
    }

    {
       _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;
       pt_this->e_resume_from_app = (NAV_RETAIL_MODE_RESUME_FROM_T)pv_tag1;
       pt_this->e_launch_osd_type = (RETAIL_MODE_LAUNCH_OSD_TYPE_T)pv_tag2;
       pt_this->ui2_count         = (UINT32)pv_tag3;

       a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
	   a_cfg_custom_set_retail_mode_led_ctrl(TRUE);
    }
}

static INT32 _nav_retail_mode_update_running_type(VOID)
{
    INT32 i4_ret = NAVR_OK;
    _NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    if (pt_this->e_status != NAV_RETAIL_MODE_RUNNING)
    {
        return NAVR_OK;
    }

    /*just update ui*/
    i4_ret = _nav_retail_mode_go_play_setup();
    NAV_LOG_ON_FAIL(i4_ret);
    if (_nav_retail_mode_get_running_type() == _nav_retail_mode_check_running_type())
    {
        return NAVR_OK;
    }

    /*stop current play : maybe _nav_retail_mode_exit()*/
    i4_ret = _nav_retail_mode_stop_play();
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = _nav_retail_mode_set_play_env();
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = _nav_retail_mode_set_status(NAV_RETAIL_MODE_CHECKING);
    NAV_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}

static INT32 _nav_retail_mode_go_running(VOID)
{
    INT32 i4_ret = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    i4_ret = _nav_retail_mode_start_play();
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = _nav_retail_mode_go_play_setup();
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = _nav_retail_mode_go_play_setup_env();
    NAV_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

static INT32 _nav_retail_mode_go_pause(VOID)
{
    INT32 i4_ret = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    i4_ret = _nav_retail_mode_stop_play();
    NAV_LOG_ON_FAIL(i4_ret);
    i4_ret = _nav_retail_mode_go_pause_setup();
    NAV_LOG_ON_FAIL(i4_ret);
    i4_ret = _nav_retail_mode_go_pause_setup_env();
    NAV_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

static INT32 _nav_retail_mode_exit(VOID)
{
//    _NAV_RETAIL_MODE_T*     pt_this = &t_g_retail_mode;
    ACFG_RETAIL_MODE_T      t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    INT32 i4_ret = NAVR_OK;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    DBG_API(("[RETAIL MODE]current status: %d.\n\r", t_retail_mode));

    a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);

    a_icl_custom_set_demo_status(0);

    a_tv_custom_set_banner_visiable_allow(TRUE);

    a_cfg_custom_set_retail_mode_led_ctrl(FALSE);

    /* if timer is running just stop it */
    i4_ret = _nav_retail_mode_stop_timer();
    NAV_CHK_FAIL(i4_ret);

    /* stop play */
    i4_ret = _nav_retail_mode_exit_setup();
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = _nav_retail_mode_stop_play();
    NAV_CHK_FAIL(i4_ret);

	/* set disabled */
    a_cfg_cust_set_demo_mode_value(0);

    /*setup env*/
    i4_ret = _nav_retail_mode_exit_setup_env();
    NAV_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

static VOID _nav_retail_mode_exit_handle (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32 i4_ret = NAVR_OK;
    nav_retail_mode_go(NAV_RETAIL_MODE_EXIT);
    NAV_LOG_ON_FAIL(i4_ret);
}

INT32 a_nav_retail_mode_start(RETAIL_MODE_PARAM_T* pt_param)
{
    if (pt_param == NULL)
    {
        DBG_ERROR(("[RETAIL MODE]param is invalid.\n\r"));
        return NAVR_INV_ARG;
    }

    nav_request_context_switch (_nav_retail_mode_start_handle,
                                (VOID*)(UINT32)(pt_param->t_launch_info.e_launch_from_app),
                                (VOID*)(UINT32)(pt_param->t_launch_info.e_launch_osd_type),
                                (VOID*)(UINT32)(pt_param->t_launch_info.ui2_count)
                               );
    return NAVR_OK;
}

INT32 a_nav_retail_mode_exit(VOID)
{
    nav_request_context_switch(_nav_retail_mode_exit_handle, NULL, NULL, NULL);

    return NAVR_OK;
}

INT32 nav_retail_mode_exit_launch_msg(VOID)
{
    INT32   i4_ret = NAVR_OK;

    if(retail_mode_view_is_on() == FALSE)
    {
          return NAVR_NOT_ALLOW;
    }

    i4_ret = _nav_retail_mode_exit();
    NAV_CHK_FAIL(i4_ret);

    do{
        if (a_wzd_is_oobe_mode() == FALSE)
        {
            break;
        }

        UINT16  ui2_status    = 0;
        UINT8   ui1_page_idx     = 0;
        a_cfg_get_wzd_status(&ui2_status);
        ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);
        DBG_INFO(("[RETAIL]stop launch,current page:%d.\n\r", ui1_page_idx));

        if (ui1_page_idx == WZD_PAGE_INDEX_C4TV_START_OOBE
            || ui1_page_idx == WZD_PAGE_INDEX_C4TV_DEVICE_PAIR
            || ui1_page_idx == WZD_PAGE_INDEX_C4TV_LINK_START)
        {
            break;
        }

        DBG_INFO(("[RETAIL]stop launch,back to Home/Store.\n\r"));
        a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_MODE));
        rest_event_notify("oobe/currentstate", 1, "MODE");
    }while(0);

    return NAVR_OK;
}

static INT32 _get_mm_video_info (VOID)
{

    MI_RESULT                   e_ret               = MI_ERR_FAILED;
    MI_HANDLE                   h_MI_MM_Hdl;
    MI_MM_QueryHandleParams_t   stQueryHandleParams;
    MI_MM_MovieInfo_t           stMovieInfo;
    UINT32                       ui4_idx = 0xD431;
    CHAR                         szMmName[128] = {0};

    c_memset(&stMovieInfo,0,sizeof(MI_MM_MovieInfo_t));

    c_snprintf(szMmName, sizeof(szMmName), "MI_MM_%d", ui4_idx);

    stQueryHandleParams.pszName = (uint8_t *)szMmName;
    stQueryHandleParams.eMediaType = E_MI_MM_MEDIA_MOVIE;

    e_ret = MI_MM_GetHandle(&stQueryHandleParams,&h_MI_MM_Hdl);
    if(e_ret != MI_OK)
    {
        DBG_INFO(("[RETAIL MODE]MI_MM_GetHandle fail ret = %d\n", e_ret));
        return -1;
    }

    e_ret = MI_MM_GetMovieInfo(h_MI_MM_Hdl,&stMovieInfo);
    if(e_ret != MI_OK)
    {
        DBG_INFO(("[RETAIL MODE]MI_MM_GetMovieInfo fail ret = %d\n", e_ret));
        return -1;
    }
    else
    {
        DBG_INFO(("[RETAIL MODE]h:%d. w:%d\n", stMovieInfo.u32MovieHeight, stMovieInfo.u32MovieWidth));
    }

    return 0;
}


/*-----------------------------------------------------------------------------
 * Name     nav_long_press_menu_switch_status
 * Description
 * Input
 * Output   -
 * Returns  -
 *---------------------------------------------------------------------------*/
VOID nav_long_press_menu_switch_status (VOID)
{

    NAV_RETAIL_MODE_STATUS_T e_retail_status = NAV_RETAIL_MODE_ERROR;
    INT32                    i4_ret = NAVR_OK;

    i4_ret = a_nav_retail_mode_get_status(&e_retail_status);
    NAV_LOG_ON_FAIL(i4_ret);

	DBG_INFO(("[RETAIL MODE]e_retail_status:%d.\n\r",e_retail_status));

    /* if not ready to play video, just return */
    if( NAV_RETAIL_MODE_RUNNING != e_retail_status )
    {
        return;
    }

	/*change to embedded demo mode*/
    if(_nav_retail_mode_get_running_type() == RETAIL_MODE_TYPE_OVERLAY
		&& nav_retail_internal_demo_check() == TRUE)
    {
    	a_cfg_custom_set_demo_type(1);
#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
		nav_recover_mmp_pq_value_in_exit();
#endif
        i4_ret = a_nav_retail_mode_update_running_type();
        NAV_LOG_ON_FAIL(i4_ret);

		a_start_retail_mode_in_no_overlay();
    }
    else if(_nav_retail_mode_get_running_type() == RETAIL_MODE_TYPE_VIDEO_INTERNAL
		     && _get_mm_video_info() == 0)/*play overlay*/
    {
        ACFG_RETAIL_MODE_T           t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

        a_cfg_custom_set_demo_type(2);

        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
        {
#if APP_RETAIL_DEMO_BACKUP_MMP_PQ
			nav_recover_mmp_pq_value_in_exit();
#endif
            a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, FALSE);
            if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
            {
			    i4_ret = a_nav_retail_mode_update_running_type();
				NAV_LOG_ON_FAIL(i4_ret);
				a_start_retail_mode_in_no_overlay();
            }
        }
    }
}

static INT32 _MI_disp_open(MI_HANDLE *h)
{
	MI_RESULT ret;
	MI_DISP_QueryHandleParams_t stParams = {0};
	const char *HandleName[] = {
		"MI_DISP_HD0",
		"MI_DISP_HD1",
		"MI_DISP_SD0"
	};

	stParams.pszName = (MI_U8 *)HandleName[0];
	DBG_INFO(("<%s(%d)> Open %s\n", __func__, __LINE__, HandleName[0]));
	ret = MI_DISP_GetHandle(&stParams, h);
	if (ret != MI_OK) {
		DBG_INFO(("<%s(%d)> Open %s failed!\n",
			__func__, __LINE__, HandleName[0]));
		return NAVR_INV_ARG;
	}
	DBG_INFO(("<%s(%d)> Open %s success (0x%x)\n",
		__func__, __LINE__, HandleName[0], *h));
	return NAVR_OK;
}

#ifdef RETAIL_RCOVERY_DEBUG
static VOID retail_recovery_test(VOID* pv_arg)
{
	int cnt = 1;
	_NAV_RETAIL_MODE_T* pt_this = &t_g_retail_mode;
	ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
	// open handle
	MI_HANDLE hd = MI_HANDLE_NULL;
	MI_RESULT ret;

	if (_MI_disp_open(&hd) != NAVR_OK)
		return;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

	do {
		a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
		if (t_retail_mode == ACFG_RETAIL_MODE_NORMAL &&
			(pt_this->e_running_type == RETAIL_MODE_TYPE_VIDEO ||
			 pt_this->e_running_type == RETAIL_MODE_TYPE_VIDEO_INTERNAL))
		{
			if (cnt % 500 == 0) {
				DBG_LOG_PRINT(("<%s(%d)> recover mode test Set mute!\n",
							__func__, __LINE__));
				ret = MI_DISP_SetMute(hd, E_MI_DISP_MUTE_FLAG_VIDEO);
				if (ret != MI_OK) {
					DBG_ERROR(("<%s(%d)> MI_DISP_SetMute HD0 failed!\n",
							__func__, __LINE__));
				}
				c_thread_delay(10000);
				DBG_INFO(("<%s(%d)> recover mode test Set unmute!\n",
							__func__, __LINE__));
				ret = MI_DISP_SetUnMute(hd, E_MI_DISP_MUTE_FLAG_VIDEO);
				if (ret != MI_OK) {
					DBG_ERROR(("<%s(%d)> MI_DISP_SetUnMute HD0 failed!\n",
							__func__, __LINE__));
				}
			}
			cnt++;
		}
		c_thread_delay(10000);
	} while (1);
}

static INT32 _retail_mode_recovery_test_thread(VOID)
{
	INT32		i4_ret = NAVR_OK;
	HANDLE_T	h_video_status = NULL_HANDLE;

	i4_ret = x_thread_create(
			&h_video_status,
			"recovery_helper_test",
			((SIZE_T)4*1024),
			((UINT8) 200),
			retail_recovery_test,
			0,
			NULL);

	if (i4_ret != NAVR_OK) {
		DBG_ERROR(("[RETAIL] Create recovery_helper_test thread (fail) i4_ret[%d].\n", i4_ret));
	} else {
		DBG_INFO(("[RETAIL] Create recovery_helper_test thread (success) i4_ret[%d].\n", i4_ret));
	}

	return i4_ret;
}
#endif

static VOID retail_mode_detect_video_status(VOID* pv_arg)
{
 	_NAV_RETAIL_MODE_T*         pt_this = &t_g_retail_mode;
	ACFG_RETAIL_MODE_T          t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
	MI_RESULT ret;
	MI_HANDLE hd = MI_HANDLE_NULL;
	MI_U32 u32MuteFlag = 0xffff;
	MI_BOOL bMute = FALSE;
	int cnt = 0;

    DBG_INFO(("[RETAIL MODE] [%s] Enter \r\n", __FUNCTION__));

	// Open MI disp handle
	if (_MI_disp_open(&hd) != NAVR_OK)
		return;

	DBG_INFO(("<%s(%d)> open MI_DISP_HD0 - (MIhandle 0x%x)\n", __func__, __LINE__, hd));

	while (1)
	{
		/* it will detect video status when demo video is playing */
	 	a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
		if (t_retail_mode == ACFG_RETAIL_MODE_NORMAL &&
			(pt_this->e_running_type == RETAIL_MODE_TYPE_VIDEO ||
			 pt_this->e_running_type == RETAIL_MODE_TYPE_VIDEO_INTERNAL))
		{
			// Check mute status
			ret = MI_DISP_GetMuteStatus(hd, u32MuteFlag, &bMute);
			if (ret != MI_OK) {
				DBG_ERROR(("<%s(%d)> Get mute status failed!\n",
						__func__, __LINE__));
			} else {
				DBG_ERROR(("<%s(%d)> Get HD0 mute status %s\n",
						__func__, __LINE__, bMute ? "ON" : "OFF"));
			}

			if (bMute)
				cnt++;
			else
				cnt = 0;

			// display out has been staying in mute for 5min, reboot
			if (cnt >= 5) {
				DBG_LOG_PRINT(("[RETAIL MODE] Warning: dispout mute upto 5min, reboot it\n"));
				a_amb_reboot();
			}
		}
		c_thread_delay(6000*10); // sleep 60s c_thread_delay(6000 * 10);
	}
}

static INT32 _retail_mode_detect_video_thread(VOID)
{
    INT32       i4_ret  = NAVR_OK;
    HANDLE_T    h_video_status = NULL_HANDLE;

    i4_ret = x_thread_create(
			&h_video_status,
			"retail_recovery_helper",
			((SIZE_T)4*1024),
			((UINT8) 200),
			retail_mode_detect_video_status,
			0,
			NULL);

    if (i4_ret != NAVR_OK) {
        DBG_ERROR(("[RETAIL] Create retail_mode_detect_video_status (fail) i4_ret[%d].\n", i4_ret));
    } else {
        DBG_INFO(("[RETAIL] Create retail_mode_detect_video_status (success) i4_ret[%d].\n", i4_ret));
    }

    return i4_ret;
}

#endif /*APP_RETAIL_MODE_SUPPORT*/

