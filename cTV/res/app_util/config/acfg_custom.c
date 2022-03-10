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
 * $RCSfile: acfg_custom.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *      This file implements the APP CFG APIs. APP CFG is a utility library which
 * encapsulates the definition of config database and builds a facade for the
 * application developer.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON.h>


#include "u_device_type.h"
#include "u_irrc_btn_def.h"

#include "c_common.h"
#include "c_uc_str.h"
#include "c_svctx.h"
#include "c_dt.h"
#include "c_pcl.h"
#include "c_iom.h"
#include "c_cecm.h"
#include "c_rm.h"
#include "c_scc.h"
#include "c_dbg.h"

#include "u_scc.h"

#include "am/a_am.h"
#include "amb/a_amb.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"
#include "app_util/a_screen_mode.h"
#include "app_util/network/network.h"
#include "app_util/a_pre_unmute.h"

#ifdef APP_C4TV_SUPPORT
#include "rest/a_rest.h"
#endif

#include "nav/nav_common.h"
#include "nav/cc_info/cc_info.h"
#include "nav/banner2/banner.h"
#include "nav/input_src/a_input_src.h"
#include "nav/cec2/nav_cec.h"
#include "app_util/a_cfg.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_factory.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/config/acfg_cust_ble.h"
#include "res/app_util/dst/a_dst_custom.h"
#include "res/app_util/network/network_custom.h"
#include "res/app_util/dev_db/a_dev_db_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/mtk_tvap_proxy/tvap_proxy_custom.h"
#include "res/app_util/simple_logo/a_simple_logo.h"
#include "res/revolt/revolt_settings_mlm.h"
#ifdef APP_ULI_UPG_SUPPORT
#include "nav/updater/a_nav_updater.h"
#endif


#include "u_drv_cust.h"

#ifdef APP_NETWORK_SUPPORT
#include "app_util/a_network.h"
#endif

#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#endif

#ifdef LINUX_TURNKEY_SOLUTION
#include <stdio.h>
#endif

#ifdef APP_NET_DLNA_SUPPORT
#ifdef APP_DMR_SUPPORT
#include "app_util/a_network.h"
#endif
#endif

#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#endif

#include "c_net_wlan_ctl.h"
#include "wdk/a_vkb.h"
#include "menu2/menu.h"
#include "app_util/tvstate/tvstate.h"
#ifdef APP_WFD_SUPPORT
#include "wfd_client_export.h"
#endif
#include "res/menu2/menu_custom.h"

#if defined(APP_WAKE_ON_LAN) || defined(APP_WAKE_ON_WLAN)
#include "u_pcl.h"
#include "c_pcl.h"
#endif

#ifdef APP_BLUETOOTH_SUPPORT
#include "app_util/a_bluetooth.h"
#endif

#include "app_util/config/_acfg.h"

#include "mtcommon.h"

#include "mi_common.h"
#include "mi_sys.h"

#ifdef CLI_SUPPORT
#include "res/app_util/config/acfg_cust_cli.h"
#endif
#include "project-mtk-new-api.h"

#include "app_util/uli/uli_custom.h"
#include "mi_flash.h"
#include "bgm/bgm.h"

#include "nav/ch_select/ch_select.h"
#include "menu2/menu_device/menu_page_input_ope_lst.h"
#include "cmd_convert.h"

#define PIC_REST_TARGET_VERSION  "1.1.14.3"


//===========================================================================================
//#define HDMI_PORT_NUM_MAX   4

//================================================================================================================================

#if( ACFG_CUST_DEBUG_ID_CAL_OFFSET )
UINT16 g_AcfgCust_u16DebugID_CalOffset = CFG_MAKE_ID(APP_CFG_GRPID_DISP,  APP_CFG_RECID_DISP_BACK_LIGHT);
#endif
//-----------------------------------------------------------------------------------------

UINT32 g_ACFG_u32DebugPicture = 0
    |ACFG_DBG_PICT_GAME
#ifdef MT5695_MODEL
    |ACFG_DBG_PICT_MEMC
    //| ACFG_DBG_PICT_CLEAR_ACTION  // Debug ClearAction
    | ACFG_DBG_PICT_LIGHT_SENSOR  // Debug LightSensor
#endif
#ifdef MT5691_MODEL
    //|ACFG_DBG_PICT_NR
#endif
    ;

//UINT32 g_ACFG_u32DebugPicture = ACFG_DBG_PICT_BACKLIGHT|ACFG_DBG_PICT_MODE;

//===========================================================================================


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
extern INT32 acfg_custom_odm_update_all(ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data);
extern INT32 acfg_custom_odm_pre_update_all( ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data);
#if (VIEWPORT_SUPPORT == 1)
extern VOID a_cfg_custom_set_view_mode_idx(APP_CFG_VIEWPORT_TYPE_T e_viewport);
#endif

extern UINT32 sys_cust_get_cc_width( VOID );
extern UINT32 sys_cust_get_cc_height( VOID );
static INT32 _acfg_cust_init_speaker_auto(VOID);
static VOID _cfg_cust_check_pic_mode_changed_status();
#ifdef MT5691_MODEL
static BOOL _cfg_cust_check_trigger_reset_pic(VOID);
#endif
static INT32 _cfg_hdmi_detect_vrr_stream_nfy_fct(UINT32  ui4_data);
static INT32 _cfg_hdmi_detect_freesync_flag_nfy_fct(UINT32  ui4_data);
static VOID _cfg_tv_soure_av_update_delay (VOID);


extern INT32 a_c4tv_apron_suspend_cast(c4tv_apron_custom_nfy_fct pf_nfy,C4TV_APRON_SUSPEND_REASON e_suspend_reason);

//extern INT32 acfg_cust_video_get_special_item_idx(UINT8  ui1_input_src,UINT16*  pui2_idx);
INT32 acfg_cust_video_Get_DataOffset_By_Src_Content_PicMode( UINT16 u16RecId, UINT8 ui1_input_src, UINT16* pui2_idx);

extern VOID menu_game_low_latency_toast(VOID);
extern BOOL a_bgm_is_running(VOID);
extern INT32 a_tv_nav_cec_set_arc_spdif_mute(BOOL b_mute);

extern INT32 a_acfg_disp_detect_oled_pal_err_nfy_fct(
                               HANDLE_T                         h_disp,
                               VOID*                            pv_nfy_tag,
                               UINT32                           ui4_data );
VOID a_cfg_set_hdr_type(SCC_VID_HDR_TYPE_T t_hdr_type);
INT32 a_cfg_cust_drv_get_oled_support_compensation(UINT32 *pui4_val);
INT32 acfg_cust_get_crnt_isl(ISL_REC_T* pt_isl_rec);

extern void NAV_Check_Back_Panel_Button(void);

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static HANDLE_T g_h_cecm = NULL_HANDLE;
static BOOL     b_during_power_ignore_count =TRUE;
/* Reserve Field */
static UINT8    ui1_g_cust_rsev_def = 0;
static UINT8    ui1_g_pixel_shift_def = 1;
static UINT8    aui1_g_clear_action [ACFG_PIC_QLT_ELEM_NUM] = {0};
static UINT8    ui1_g_cust_rsev_tv_def = 1; /*add for SRS StudioSound HD default value*/
static UINT16   ui2_g_cust_rsev_def = 0;
static UINT32   ui4_g_cust_rsev_def = 0;
static UINT16   ui2_g_cust_acfg_lst_idx = IDX_CUSTOM_ACFG_LAST_IDX;
static UINT8    ui1_g_cust_rsev_def_acr = ACFG_ACR_OFF;
static UINT8    ui1_g_cust_pair_status_def = WIFI_REMOTE_PAIR_STATUS_UNPAIRED;
static UINT8    ui1_g_cust_last_p2p0_opch_def = LAST_P2P0_OP_CHANNEL_UNKNOWN;
static UINT8    ui1_g_cust_start_setup_def = WIFI_REMOTE_START_SETUP_OFF;
static UINT8    ui1_bs_src_def = APP_CFG_BS_SRC_CABLE;
static UINT8    ui1_g_cust_scrn_saver_time = 0;

#if( ENABLE_HDMI_EDID_NEW_METHOD )
  #define HDMI_EDID_DEFALUT(ed1,ed2,ed3,ed4)    ((ed1)|(ed2<<2)|(ed3<<4)|(ed4<<6))

  #if( defined(MT5583_MODEL) )
    UINT8    ui1_g_cust_hdmi_mode_def = // 4 port = ACFG_EDID_IDX_1_4
        HDMI_EDID_DEFALUT(ACFG_EDID_IDX_1_4, ACFG_EDID_IDX_1_4, ACFG_EDID_IDX_1_4, ACFG_EDID_IDX_1_4);
  #else
    UINT8    ui1_g_cust_hdmi_mode_def = // 4 port = ACFG_EDID_IDX_AUTO
        HDMI_EDID_DEFALUT(ACFG_EDID_IDX_AUTO, ACFG_EDID_IDX_AUTO, ACFG_EDID_IDX_AUTO, ACFG_EDID_IDX_AUTO);
  #endif

#else
  #ifdef MT5583_MODEL
    UINT8    ui1_g_cust_hdmi_mode_def = 0; // 4 port = ACFG_EDID_IDX_1_4
  #else
    UINT8    ui1_g_cust_hdmi_mode_def = 170; // 0xAA(1010-1010)=> ACFG_EDID_IDX_AUTO
  #endif
#endif

//--------------------------------------------------------------------------------------
#if( defined(ACFG_NETFLIX_CERT_PATCH_PQ) \
  || defined(ACFG_DV_CERT_PATCH_PQ)      \
  )
    #define ACFG_CUST_DEFAULT__MEMC  0 // Off
#else
    #define ACFG_CUST_DEFAULT__MEMC  1 // On
#endif
static UINT8    ui1_g_cust_memc = ACFG_CUST_DEFAULT__MEMC;
//--------------------------------------------------------------------------------------

static UINT8    ui1_g_cust_earc = 0;
static UINT8    ui1_g_cust_limited_ad_tracking_def = 1;
static UINT16   ui2_g_cust_oled_jb_cooling_time_def = 60;// 1 HR

static UINT8    ui1_g_cust_miracast_enable_status = 0;
static UINT8    ui1_g_cust_pic_quality_adjust_page = 0;
static UINT16   ui2_g_cust_3d_brightness_boost = 0;
static UINT16   ui2_g_cust_lang_select = 0;
static UINT16   ui2_g_cust_country_select = 0;
static UINT16   ui2_g_cust_tz_select = 0;
static UINT16   ui2_g_cust_is_reduce_blur_support = ACFG_REDUCE_BLUR_OFF;
static UINT8    ui1_g_cust_vol_control = 0;
static UINT16   ui2_g_cust_dhcp_status = ACFG_DHCP_OFF;

static UINT8    ui1_aud_ad_speaker_out_def  = (UINT8)APP_CFG_AUD_AD_SPEAKER_AUTO;
static UINT8    ui1_aud_ad_digital_auto_def  = (UINT8)APP_AUD_SPDIF_FMT_AUTO;

static UINT8    ui1_g_cust_log_to_usb_def = 0;

static UINT8    ui1_g_cust_sys_updater_force_reboot_def = ACFG_FORCE_REBOOT_UP_OFF;
static UINT8    ui1_g_cust_color_tune_offset = 128;
static UINT8    ui1_g_demo_mode = 0;
static UINT8    ui1_g_automatic_def = 0;

static UINT8    ui1_g_dv_last_pic_mode_def = 0;

#ifdef VLOG_DEFAULT_ON  // defined in sys_build MTxxxx.cfg
static UINT8    ui1_g_vlog_def = ACFG_VLOG_ON;
#else
static UINT8    ui1_g_vlog_def = ACFG_VLOG_OFF;
#endif

static UINT8    aui1_g_contrast_en [ACFG_PIC_QLT_ELEM_NUM] = {0};
static UINT8    aui1_g_super_resolution [ACFG_PIC_QLT_ELEM_NUM] = {2};
static UINT8    aui1_g_edge_enhancement [ACFG_PIC_QLT_ELEM_NUM] = {1};
static UINT8    aui1_g_game_hdr [ACFG_PIC_QLT_ELEM_NUM] = {0};
static UINT8    aui1_g_peak_lunimance [ACFG_PIC_QLT_ELEM_NUM] = {0};
static UINT8    aui1_g_motion_blur_reduction [ACFG_PIC_QLT_ELEM_NUM] = {0};
static UINT8    aui1_g_variable_refresh_rate [ACFG_PIC_QLT_ELEM_NUM] = {1};
static UINT8    aui1_g_eotf [ACFG_INPUT_SRC_NUM] = {0};
static UINT8    aui1_g_en_view_angle [ACFG_PIC_QLT_ELEM_NUM] = {1};
static UINT8    aui1_g_game_low_latency [ACFG_PIC_QLT_ELEM_NUM] = {0};
static UINT8    aui1_g_judder_reduction [ACFG_PIC_QLT_ELEM_NUM] = {0};
static UINT8    aui1_g_film_maker_mode [ACFG_INPUT_SRC_NUM] = {0};
static UINT8    aui1_g_contrast_smothing [ACFG_PIC_QLT_ELEM_NUM] = {1};
static UINT8    aui1_g_pq_reserve [ACFG_PIC_QLT_ELEM_NUM] = {0};

/* PARTITION mount all flag*/
static BOOL     b_g_fs_partition_all = FALSE;

static UINT8    ui1_g_cust_acr_magic_def = 0x29;

static UINT8    ui1_g_cust_use_net_time = USE_NET_TIME_ON;
static UINT8    ui1_g_cust_time_format = USE_TIME_12H;
static UINT8    ui1_g_cust_ipts_sel = IPTS_IS_SELEC_FALSE;
static UINT8    ui1_g_cust_ch_scan_progress_def = 0;

static UINT8    ui1_g_cust_vol_slider_display_def = ACFG_CUSTOM_VOL_SLIDER_DIS_ON;
static UINT8    ui1_g_cust_oobe_ir_mode = 0;

static UINT8    ui1_g_retail_mode_first_time_setting = 0;

static BOOL     b_bgm_wake_up_disable = TRUE;
static UINT8    ui1_g_cust_vtrl_hide_def = 31; //0x1F all hide

static CHAR     sz_g_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};
static CHAR     s_wifi_module_name[ACFG_CUSTOM_WIFI_MODULE_NAME_LEN] = {0};
static EnuCusModelSeries s_eCurModelSeries = CUS_MODEL_UNKNOWN;
static BOOL     b_2021_83_FHD_is_FreeSync_logo_support = FALSE;

//static BOOL     s_bIsCurModel_2021 = FALSE;
static UINT16   s_u16CurModel_Year = 2021;
static BOOL s_b_is_OLED_model = FALSE;

static UINT8    ui1_g_pq_bypass = 0;

static BOOL     b_g_gll_off_flag = FALSE;
//static BOOL     b_g_detect_hdmi_vrr_stream = FALSE;
//static BOOL     b_g_detect_hdmi_freesync_flag = FALSE;
EnuAcfgVrrStatus g_ACFG_eCurVrrFreeSyncStatus = ACFG_VRR_STATUS_NONE;

static BOOL     b_g_backlight_ctrl_lock = FALSE;
static BOOL     b_g_is_oled_suppend = FALSE;
static BOOL     b_g_oled_bypass_img_still = FALSE;

static UINT8    ui1_g_game_mode_flag = APP_CFG_VID_GAME_MODE_OFF;
//static BOOL     b_g_had_switch_dv_game_mode = FALSE;

static ACFG_OLED_ERROR_DETECT_TYPE t_still_image_status = ACFG_OLED_ERR_EVENT_GSP_IMG_MOVE;

HANDLE_T      h_tv_source_av_update_delay_timer = NULL_HANDLE;

extern BOOL b_is_factory_auto_test;

extern BOOL b_is_detected_spd_info;


/* Access Mask */
/*
other predefine masks are in _acfg.h, using this just to make sure
the acfg memory field using ACFG_ACCESS_HIDE_INPUT will not be clear
when do system factory reset
*/
#define     ACFG_ACCESS_HIDE_INPUT                  MAKE_BIT_MASK_8(5)
#define SCREEN_WIDTH_1366   ((UINT32)  1366)
#define SCREEN_HEIGHT_768   ((UINT32)  768)
#define SCREEN_WIDTH_1920   ((UINT32)  1920)
#define SCREEN_HEIGHT_1080   ((UINT32)  1080)

#define TV_SOURCE_AV_UPDATE_DELAY_1000   ((UINT32)  1000)


UINT8 aui1_backlight_ini_def[APP_CFG_PQ_ITEMS_NUM] =
{

  /*user, cinema, sport, vivid, hi_bri, dovi_bri, dovi_dark, standard, natural, movie, game, energy_saving, AI_PQ, dovi_vivid*/
    50, 60, 50, 40, 70, 60, 50, 50, 50, 40, 50, 30, 100, 50, /* CVBS & TV */
    50, 60, 50, 40, 70, 60, 50, 50, 50, 40, 50, 30, 100, 50,/* COMPONENT */
    50, 60, 50, 40, 70, 60, 50, 50, 50, 40, 50, 30, 100, 50,/* HDMI */
    50, 60, 50, 40, 70, 60, 50, 50, 50, 40, 50, 30, 100, 50,/* DVI */
    50, 60, 50, 40, 70, 60, 50, 50, 50, 40, 50, 30, 100, 50,/* VGA */
    50, 60, 50, 40, 70, 60, 50, 50, 50, 40, 50, 30, 100, 50 /* MMP */
#ifdef APP_3D_PHOTO_SUPPORT
    ,
    50, 60, 50, 40, 70, 60, 50, 50, 50, 40, 50, 30, 100, 50  /* MMP_IMG */
#endif
};

UINT8 aui1_gamma_ini_def[APP_CFG_PQ_ITEMS_NUM] =
{
    /*user, cinema, sport, vivid, hi_bri, dovi_bri, dovi_dark, standard, natural, movie, game, energy_saving, AI_PQ, dovi_vivid*/
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* CVBS & TV */
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* COMPONENT */
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* HDMI */
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* DVI */
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* VGA */
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  /* MMP */
#ifdef APP_3D_PHOTO_SUPPORT
    ,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 /* MMP_IMG */
#endif
};

UINT8 aui1_contrast_ini_def[APP_CFG_PQ_ITEMS_NUM] =
{
    /*user, cinema, sport, vivid, hi_bri, dovi_bri, dovi_dark, standard, natural, movie, game, energy_saving, AI_PQ, dovi_vivid*/
    50, 60, 70, 80, 75, 50, 52, 50, 40, 60, 40, 50, 50, 50, /* CVBS & TV */
    50, 60, 70, 80, 75, 50, 52, 50, 40, 60, 40, 50, 50, 50, /* COMPONENT */
    50, 60, 70, 80, 75, 50, 52, 50, 40, 60, 40, 50, 50, 50, /* HDMI */
    50, 60, 70, 80, 75, 50, 52, 50, 40, 60, 40, 50, 50, 50, /* DVI */
    50, 60, 70, 80, 75, 50, 52, 50, 40, 60, 40, 50, 50, 50, /* VGA */
    50, 60, 70, 80, 75, 50, 52, 50, 40, 60, 40, 50, 50, 50  /* MMP */
#ifdef APP_3D_PHOTO_SUPPORT
    ,
    50, 60, 70, 80, 75, 50, 52, 50, 40, 60, 40, 50, 50, 50  /* MMP_IMG */
#endif
};

UINT8 aui1_brightness_ini_def[APP_CFG_PQ_ITEMS_NUM] =
{
    /*user, cinema, sport, vivid, hi_bri, dovi_bri, dovi_dark, standard, natural, movie, game, energy_saving, AI_PQ, dovi_vivid*/
    50, 40, 50, 50, 60, 60, 40, 50, 55, 40, 50, 50, 50, 50, /* CVBS & TV */
    50, 40, 50, 50, 60, 60, 40, 50, 55, 40, 50, 50, 50, 50, /* COMPONENT */
    50, 40, 50, 50, 60, 60, 40, 50, 55, 40, 50, 50, 50, 50, /* HDMI */
    50, 40, 50, 50, 60, 60, 40, 50, 55, 40, 50, 50, 50, 50, /* DVI */
    50, 40, 50, 50, 60, 60, 40, 50, 55, 40, 50, 50, 50, 50, /* VGA */
    50, 40, 50, 50, 60, 60, 40, 50, 55, 40, 50, 50, 50, 50  /* MMP */
#ifdef APP_3D_PHOTO_SUPPORT
    ,
    50, 40, 50, 50, 60, 60, 40, 50, 55, 40, 50, 50, 50, 50  /* MMP_IMG */
#endif
};

UINT8 aui1_saturation_ini_def[APP_CFG_PQ_ITEMS_NUM] =
{
    /*user, cinema, sport, vivid, hi_bri, dovi_bri, dovi_dark, standard, natural, movie, game, energy_saving, AI_PQ, dovi_vivid*/
    50, 50, 55, 60, 50, 50, 50, 50, 55, 70, 55, 40, 70, 50, /* CVBS & TV */
    50, 50, 55, 60, 50, 50, 50, 50, 55, 70, 55, 40, 70, 50, /* COMPONENT */
    50, 50, 55, 60, 50, 50, 50, 50, 55, 70, 55, 40, 70, 50, /* HDMI */
    50, 50, 55, 60, 50, 50, 50, 50, 55, 70, 55, 40, 70, 50, /* DVI */
    50, 50, 55, 60, 50, 50, 50, 50, 55, 70, 55, 40, 70, 50, /* VGA */
    50, 50, 55, 60, 50, 50, 50, 50, 55, 70, 55, 40, 70, 50  /* MMP */
#ifdef APP_3D_PHOTO_SUPPORT
    ,
    50, 50, 55, 60, 50, 50, 50, 50, 55, 70, 55, 40, 70, 50  /* MMP_IMG */
#endif
};



INT8 ai1_hue_ini_def[APP_CFG_PQ_ITEMS_NUM] =
{
    /*user, cinema, sport, vivid, hi_bri, dovi_bri, dovi_dark, standard, natural, movie, game, energy_saving, AI_PQ, dovi_vivid*/
    0, 0, 0, 0, 0, 1, 1, 0, 5, 0, -3, 0, 0, 1, /* CVBS & TV */
    0, 0, 0, 0, 0, 1, 1, 0, 5, 0, -3, 0, 0, 1, /* COMPONENT */
    0, 0, 0, 0, 0, 1, 1, 0, 5, 0, -3, 0, 0, 1, /* HDMI */
    0, 0, 0, 0, 0, 1, 1, 0, 5, 0, -3, 0, 0, 1, /* DVI */
    0, 0, 0, 0, 0, 1, 1, 0, 5, 0, -3, 0, 0, 1, /* VGA */
    0, 0, 0, 0, 0, 1, 1, 0, 5, 0, -3, 0, 0, 1  /* MMP */
#ifdef APP_3D_PHOTO_SUPPORT
    ,
    0, 0, 0, 0, 0, 1, 1, 0, 5, 0, -3, 0, 0, 1  /* MMP_IMG */
#endif
};

UINT8 aui1_sharpness_ini_def[APP_CFG_PQ_ITEMS_NUM] =
{
    /*user, cinema, sport, vivid, hi_bri, dovi_bri, dovi_dark, standard, natural, movie, game, energy_saving, AI_PQ, dovi_vivid*/
    12, 6, 14, 12, 12, 4, 4, 10, 8, 10, 5, 12, 10, 4, /* CVBS & TV */
    12, 6, 14, 12, 12, 4, 4, 10, 8, 10, 5, 12, 10, 4, /* COMPONENT */
    12, 6, 14, 12, 12, 4, 4, 10, 8, 10, 5, 12, 10, 4, /* HDMI */
    12, 6, 14, 12, 12, 4, 4, 10, 8, 10, 5, 12, 10, 4, /* DVI */
    12, 6, 14, 12, 12, 4, 4, 10, 8, 10, 5, 12, 10, 4, /* VGA */
    12, 6, 14, 12, 12, 4, 4, 10, 8, 10, 5, 12, 10, 4  /* MMP */
#ifdef APP_3D_PHOTO_SUPPORT
    ,
    12, 6, 14, 12, 12, 4, 4, 10, 8, 10, 5, 12, 10, 4  /* MMP_IMG */
#endif
};

static INT32   _acfg_custom_acr_file_init();


/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/

static VOID _acfg_custom_cec_nfy_fct (CECM_NFY_T*   pv_nfy_data,
                              VOID*         pv_tag,
                              UINT32        ui4_data)
{
    return;
}

static INT32 _acfg_custom_get_model_name_from_driver(void)
{
    INT32                       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T   t_op_info = {0};
    SIZE_T                      z_size_drv = 0;
    static CHAR                 s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};
    SIZE_T                      z_size = 0;


    z_size = sizeof(s_model_name);
    z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    c_memset (&t_op_info, 0, sizeof (DRV_CUST_OPERATION_INFO_T));
    c_memset (s_model_name, 0, sizeof(s_model_name));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_MODEL_NAME;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)s_model_name;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        DBG_ERROR(("!!!!%s Get Fail i4_ret : %d\n", __FUNCTION__, i4_ret));
        return APP_CFGR_INTERNAL_ERR;
    }

    DBG_LOG_PRINT(("[ACFG][%s] model name:(%s)\n",__FUNCTION__,s_model_name));
    c_strncpy(sz_g_model_name, s_model_name, strlen(s_model_name));

    // Convert model name to model series...
    s_eCurModelSeries = a_cfg_cust_Convert_ModelNameToModelSeries(sz_g_model_name);
    DBG_LOG_PRINT(("[ACFG][%s] s_eCurModelSeries:%d\n", __FUNCTION__, s_eCurModelSeries ));

    // Check if model is 2021...
    if( c_strstr(sz_g_model_name, "-J") != NULL ) // 2021 model
    {
        //s_bIsCurModel_2021 = TRUE;
        s_u16CurModel_Year = 2021;
    }
    else if( c_strstr(sz_g_model_name, "-H") != NULL ) // 2020 model
    {
        s_u16CurModel_Year = 2020;
    }
    else if( c_strstr(sz_g_model_name, "-K") != NULL ) // 2022 model
    {
        s_u16CurModel_Year = 2022;
    }
    else
    {
        s_u16CurModel_Year = 2021;
        DBG_LOG_PRINT(("[ACFG][%s] Warning: Cannot get model year! Force s_u16CurModel_Year=%d\n", __FUNCTION__, s_u16CurModel_Year ));
    }

    //DBG_LOG_PRINT(("[ACFG][%s] s_bIsCurModel_2021:%d\n", __FUNCTION__, s_bIsCurModel_2021 ));
    DBG_LOG_PRINT(("[ACFG][%s] s_u16CurModel_Year:%d\n", __FUNCTION__, s_u16CurModel_Year ));

    // Check keyword "OLED"
    if( c_strstr(sz_g_model_name, "OLED") != NULL ) // OLED model
    {
        s_b_is_OLED_model = TRUE;
    }
    else
    {
        s_b_is_OLED_model = FALSE;
    }
    DBG_LOG_PRINT(("[ACFG][%s] s_b_is_OLED_model:%d\n", __FUNCTION__, s_b_is_OLED_model ));

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
#ifdef APP_CFG_CH_LST_CHECK_INSERT_FAKE_BY_FUNCTION
BOOL  acfg_ch_lst_custom_check_insert_fake(BOOL b_air)
{
    return FALSE;
}
#endif

UINT8 acfg_custom_get_input_grp (ISL_REC_T* pt_isl_rec)
{
    ACFG_CUST_INPUT_GRP_T        e_inp_grp = ACFG_CUST_INPUT_GRP_TV;
    UINT8 ui1_ret_val = 0;

    if(pt_isl_rec->e_src_type == INP_SRC_TYPE_MM ||
       a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
    {
        e_inp_grp = ACFG_CUST_INPUT_GRP_MMP;
    }
    else if(pt_isl_rec->e_src_type == INP_SRC_TYPE_VTRL)
    {
        e_inp_grp = ACFG_CUST_INPUT_GRP_MMP;
    }
    else if(pt_isl_rec->e_src_type == INP_SRC_TYPE_TV)
    {
        e_inp_grp = ACFG_CUST_INPUT_GRP_TV;
    }
    else if(pt_isl_rec->e_src_type == INP_SRC_TYPE_AV)
    {
        switch(pt_isl_rec->t_avc_info.e_video_type)
        {
        case DEV_AVC_COMP_VIDEO:
        case DEV_AVC_S_VIDEO:
        case DEV_AVC_COMBI:
        case DEV_AVC_SCART:
            e_inp_grp = ACFG_CUST_INPUT_GRP_CVBS;
            break;
        case DEV_AVC_Y_PB_PR:
            e_inp_grp = ACFG_CUST_INPUT_GRP_COMPONENT;
            break;
        case DEV_AVC_HDMI:
        {
            /* Vedio timing */
            if (pt_isl_rec->ui1_internal_id == 0)
            {
                e_inp_grp = ACFG_CUST_INPUT_GRP_HDMI1;
            }
            else if (pt_isl_rec->ui1_internal_id == 1)
            {
                e_inp_grp = ACFG_CUST_INPUT_GRP_HDMI2;
            }
            else if (pt_isl_rec->ui1_internal_id == 2)
            {
                e_inp_grp = ACFG_CUST_INPUT_GRP_HDMI3;
            }
            else
            {
                e_inp_grp = ACFG_CUST_INPUT_GRP_HDMI4;
            }
            break;
        }
        case DEV_AVC_VGA:
            e_inp_grp = ACFG_CUST_INPUT_GRP_VGA;
            break;
        default:
            e_inp_grp = ACFG_CUST_INPUT_GRP_CVBS;
            break;
        }
    }
    else
    {
        e_inp_grp = ACFG_CUST_INPUT_GRP_TV;
    }

    ui1_ret_val = (UINT8)e_inp_grp;

    return ui1_ret_val;
}

static INT32 _acfg_custom_pre_init_cus_resv_8bit(VOID)
{
    /* used, IDX_CUSTOM_RSERVE_UI1_0 -> IDX_CUSTOM_LIP_SYNC_IDX_TV*/
    DECLARE_FIELD(IDX_CUSTOM_LIP_SYNC_IDX_TV,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_0,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_1 -> IDX_CUSTOM_LIP_SYNC_IDX_CVBS*/
    DECLARE_FIELD(IDX_CUSTOM_LIP_SYNC_IDX_CVBS,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_1,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_2 -> IDX_CUSTOM_LIP_SYNC_IDX_COMP*/
    DECLARE_FIELD(IDX_CUSTOM_LIP_SYNC_IDX_COMP,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_2,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_3 -> IDX_CUSTOM_LIP_SYNC_IDX_HDMI1*/
    DECLARE_FIELD(IDX_CUSTOM_LIP_SYNC_IDX_HDMI1,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_3,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_4 -> IDX_CUSTOM_LIP_SYNC_IDX_HDMI2*/
    DECLARE_FIELD(IDX_CUSTOM_LIP_SYNC_IDX_HDMI2,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_4,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_5 -> IDX_CUSTOM_LIP_SYNC_IDX_HDMI3*/
    DECLARE_FIELD(IDX_CUSTOM_LIP_SYNC_IDX_HDMI3,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_5,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_6 -> IDX_CUSTOM_LIP_SYNC_IDX_HDMI4*/
    DECLARE_FIELD(IDX_CUSTOM_LIP_SYNC_IDX_HDMI4,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_6,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_7 -> IDX_CUSTOM_LIP_SYNC_IDX_VGA*/
    DECLARE_FIELD(IDX_CUSTOM_LIP_SYNC_IDX_VGA,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_7,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_8 -> IDX_CUSTOM_LIP_SYNC_IDX_MMP*/
    DECLARE_FIELD(IDX_CUSTOM_LIP_SYNC_IDX_MMP,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_8,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_9 -> IDX_CUSTOM_LIP_SYNC_IDX_VTRL*/
    DECLARE_FIELD(IDX_CUSTOM_LIP_SYNC_IDX_VTRL,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_9,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_10 -> IDX_CUSTOM_SRS_SRUND_IDX_TV*/
    DECLARE_FIELD(IDX_CUSTOM_SRS_SRUND_IDX_TV,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_10,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_tv_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_11 -> IDX_CUSTOM_SRS_SRUND_IDX_CVBS*/
    DECLARE_FIELD(IDX_CUSTOM_SRS_SRUND_IDX_CVBS,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_11,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_tv_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_12 -> IDX_CUSTOM_SRS_SRUND_IDX_COMP*/
    DECLARE_FIELD(IDX_CUSTOM_SRS_SRUND_IDX_COMP,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_12,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_tv_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_13 -> IDX_CUSTOM_SRS_SRUND_IDX_HDMI1*/
    DECLARE_FIELD(IDX_CUSTOM_SRS_SRUND_IDX_HDMI1,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_13,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_tv_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_14 -> IDX_CUSTOM_SRS_SRUND_IDX_HDMI2*/
    DECLARE_FIELD(IDX_CUSTOM_SRS_SRUND_IDX_HDMI2,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_14,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_tv_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_15 -> IDX_CUSTOM_SRS_SRUND_IDX_HDMI3*/
    DECLARE_FIELD(IDX_CUSTOM_SRS_SRUND_IDX_HDMI3,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_15,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_tv_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_16 -> IDX_CUSTOM_SRS_SRUND_IDX_HDMI4*/
    DECLARE_FIELD(IDX_CUSTOM_SRS_SRUND_IDX_HDMI4,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_16,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_tv_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_17 -> IDX_CUSTOM_SRS_SRUND_IDX_VGA*/
    DECLARE_FIELD(IDX_CUSTOM_SRS_SRUND_IDX_VGA,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_17,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_tv_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_18 -> IDX_CUSTOM_SRS_SRUND_IDX_MMP*/
    DECLARE_FIELD(IDX_CUSTOM_SRS_SRUND_IDX_MMP,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_18,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_tv_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_19 -> IDX_CUSTOM_SRS_SRUND_IDX_VTRL*/
    DECLARE_FIELD(IDX_CUSTOM_SRS_SRUND_IDX_VTRL,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_19,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_tv_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_20 -> IDX_CUSTOM_ACR_IDX */
    DECLARE_FIELD(IDX_CUSTOM_ACR_IDX,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_20,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def_acr,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_21  -> IDX_CUSTOM_WIFI_REMOTE_PAIR_STATUS */
    DECLARE_FIELD(IDX_CUSTOM_WIFI_REMOTE_PAIR_STATUS,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_21,
                  CFG_8BIT_T,   1,           &ui1_g_cust_pair_status_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_FACTORY);

    /* used, IDX_CUSTOM_RSERVE_UI1_22  -> IDX_CUSTOM_ETHERNET_CONNECTED_STATUS */
    DECLARE_FIELD(IDX_CUSTOM_ENTERNET_CONNECTED_STATUS,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_22,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_23  -> IDX_CUSTOM_MAIN_MENU_PRE_ITEM */
    DECLARE_FIELD(IDX_CUSTOM_MAIN_MENU_PRE_ITEM,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_23,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_24 -> IDX_CUSTOM_MIRACAST_ENABLE_STATUS */
    DECLARE_FIELD(IDX_CUSTOM_MIRACAST_ENABLE_STATUS,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_24,
                  CFG_8BIT_T,   1,           &ui1_g_cust_miracast_enable_status,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_25  -> IDX_CUSTOM_START_SETUP */
    DECLARE_FIELD(IDX_CUSTOM_START_SETUP,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_25,
                  CFG_8BIT_T,   1,           &ui1_g_cust_start_setup_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

   /* used, IDX_CUSTOM_RSERVE_UI1_26  -> IDX_CUSTOM_LAST_P2P0_OP_CHANNEL */
    DECLARE_FIELD(IDX_CUSTOM_LAST_P2P0_OP_CHANNEL,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_26,
                  CFG_8BIT_T,   1,           &ui1_g_cust_last_p2p0_opch_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);


    /* used, APP_CFG_RECID_CUST_RSEV_UI1_27 -> IDX_CUSTOM_VOL_CONTROL */
    DECLARE_FIELD(IDX_CUSTOM_VOL_CONTROL,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_27,
                  CFG_8BIT_T,   1,           &ui1_g_cust_vol_control,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);


    /* used, IDX_CUSTOM_RSERVE_UI1_28  -> IDX_CUSTOM_SCRN_SAVER_TIME */
    DECLARE_FIELD(IDX_CUSTOM_SCRN_SAVER_TIME,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_28,
                  CFG_8BIT_T,   1,           &ui1_g_cust_scrn_saver_time,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);


    /* used, IDX_CUSTOM_RSERVE_UI1_29 -> IDX_CUSTOM_PIC_QUALITY_ADJUST_PAGE */
    DECLARE_FIELD(IDX_CUSTOM_PIC_QUALITY_ADJUST_PAGE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_29,
                  CFG_8BIT_T,   1,         &ui1_g_cust_pic_quality_adjust_page,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    return APP_CFGR_OK;
}

static INT32 _acfg_custom_pre_init_cus_resv_16bit(VOID)
{
    /* used, APP_CFG_RECID_CUST_RSEV_UI2_0  -> Postal Code of Canada */
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_0,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_0,
                  CFG_16BIT_T,   1,          &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, APP_CFG_RECID_CUST_RSEV_UI2_1 -> IDX_CUSTOM_3D_BRIGHTNESS_BOOST */
    DECLARE_FIELD(IDX_CUSTOM_3D_BRIGHTNESS_BOOST,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_1,
                  CFG_16BIT_T,   1,          &ui2_g_cust_3d_brightness_boost,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, APP_CFG_RECID_CUST_RSEV_UI2_2 -> IDX_CUSTOM_LANG_SELECT */
    DECLARE_FIELD(IDX_CUSTOM_LANG_SELECT,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_2,
                  CFG_16BIT_T,   1,          &ui2_g_cust_lang_select,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, APP_CFG_RECID_CUST_RSEV_UI2_3 -> IDX_CUSTOM_COUNTRY_SELECT */
    DECLARE_FIELD(IDX_CUSTOM_COUNTRY_SELECT,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_3,
                  CFG_16BIT_T,   1,          &ui2_g_cust_country_select,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, APP_CFG_RECID_CUST_RSEV_UI2_4 -> IDX_CUSTOM_REDUCE_BLUR */
    DECLARE_FIELD(IDX_CUSTOM_REDUCE_BLUR,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_4,
                  CFG_16BIT_T,   1,          &ui2_g_cust_is_reduce_blur_support,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, APP_CFG_RECID_CUST_RSEV_UI2_5 -> IDX_CUSTOM_VGA_H_SIZE */
    DECLARE_FIELD(IDX_CUSTOM_VGA_H_SIZE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_5,
                  CFG_16BIT_T,   1,          &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, APP_CFG_RECID_CUST_RSEV_UI2_6 -> IDX_CUSTOM_VGA_V_SIZE */
    DECLARE_FIELD(IDX_CUSTOM_VGA_V_SIZE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_6,
                  CFG_16BIT_T,   1,          &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, APP_CFG_RECID_CUST_RSEV_UI2_7 -> IDX_CUSTOM_DST */
    DECLARE_FIELD(IDX_CUSTOM_DST,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_7,
                  CFG_16BIT_T,   1,          &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, APP_CFG_RECID_CUST_RSEV_UI2_8 -> IDX_CUSTOM_TIMEZONE_SELECT */
    DECLARE_FIELD(IDX_CUSTOM_TIMEZONE_SELECT,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_8,
                  CFG_16BIT_T,   1,          &ui2_g_cust_tz_select,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, APP_CFG_RECID_CUST_RSEV_UI2_9 -> IDX_CUSTOM_DHCP_STATUS */
    DECLARE_FIELD(IDX_CUSTOM_DHCP_STATUS,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_9,
                  CFG_16BIT_T,   1,          &ui2_g_cust_dhcp_status,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    return APP_CFGR_OK;
}

static INT32 _acfg_custom_pre_init_cus_resv_32bit(VOID)
{
    /* used for a_cfg_custom_get_total_aging_time */
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI4_0,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_0,
                  CFG_32BIT_T,   1,          &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI4_1 -> IDX_CUSTOM_SYS_BOOT_UP_TIMES */
    DECLARE_FIELD(IDX_CUSTOM_SYS_BOOT_UP_TIMES,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_1,
                  CFG_32BIT_T,   1,          &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI4_2 -> IDX_CUSTOM_SYS_TOTAL_RUNNING_TIME */
    DECLARE_FIELD(IDX_CUSTOM_SYS_TOTAL_RUNNING_TIME,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_2,
                  CFG_32BIT_T,   1,          &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    return APP_CFGR_OK;
}

static INT32 _acfg_custom_pre_init_cus_resv_ex_8bit(VOID)
{
    UINT16  ui2_ipt_idx        = 0;
    UINT16  ui2_idx            = 0;
    UINT16  ui2_item_idx       = 0;
    /*the field IDX_CUSTOM_RSERVE_UI1_EX_0 have been used for the arc magic def
    *and the magic acr will be use for the correct acr version, otherwise the
    *acr value is not correct, and this solution will be only used for y15.
    */
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI1_EX_0,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_0,
                  CFG_8BIT_T,   1,           &ui1_g_cust_acr_magic_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used for log2usb, and log2usb not use this field again currently */
    DECLARE_FIELD(IDX_CUSTOM_LOG_TO_USB,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_1,
                  CFG_8BIT_T,   1,           &ui1_g_cust_log_to_usb_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used IDX_CUSTOM_RSERVE_UI1_EX_2 -> IDX_CUSTOM_VGA_POS_H_EXT */
    DECLARE_FIELD(IDX_CUSTOM_VGA_POS_H_EXT,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_2,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_3 -> IDX_CUSTOM_USE_INTERNET_TIME */
    DECLARE_FIELD(IDX_CUSTOM_USE_INTERNET_TIME,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_3,
                  CFG_8BIT_T,   1,           &ui1_g_cust_use_net_time,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_4 -> IDX_CUSTOM_TIME_FORMAT */
    DECLARE_FIELD(IDX_CUSTOM_TIME_FORMAT,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_4,
                  CFG_8BIT_T,   1,           &ui1_g_cust_time_format,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI4_5 -> IDX_CUSTOM_SPEAKER_OUT_ADDRESS */
    DECLARE_FIELD(IDX_CUSTOM_SPEAKER_OUT_ADDRESS,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_5,
                  CFG_8BIT_T,   1,           &ui1_aud_ad_speaker_out_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

     /* used, IDX_CUSTOM_RSERVE_UI4_6 -> IDX_CUSTOM_DIGITAL_AUDIO_ADDRESS */
    DECLARE_FIELD(IDX_CUSTOM_DIGITAL_AUDIO_ADDRESS,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_6,
                  CFG_8BIT_T,   1,           &ui1_aud_ad_digital_auto_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_7 -> IDX_CUSTOM_LAST_CHANNEL_TUNER_TYPE*/
    DECLARE_FIELD(IDX_CUSTOM_LAST_CHANNEL_TUNER_TYPE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_7,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_8 -> IDX_CUSTOM_IPTS_SELECT_TIME*/
    DECLARE_FIELD(IDX_CUSTOM_IPTS_SELECT_TIME,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_8,
                  CFG_8BIT_T,   1,           &ui1_g_cust_ipts_sel,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_9 -> IDX_CUSTOM_CH_SCAN_PROGRESS*/
    DECLARE_FIELD(IDX_CUSTOM_CH_SCAN_PROGRESS,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_9,
                  CFG_8BIT_T,   1,           &ui1_g_cust_ch_scan_progress_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_10 -> IDX_CUSTOM_FORCE_REBOOT_UP*/
    DECLARE_FIELD(IDX_CUSTOM_FORCE_REBOOT_UP,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_10,
                  CFG_8BIT_T,   1,           &ui1_g_cust_sys_updater_force_reboot_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_11 -> IDX_CUSTOM_VLOG_CONTORL*/
    DECLARE_FIELD(IDX_CUSTOM_VLOG_CONTORL,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_11,
                  CFG_8BIT_T,   1,           &ui1_g_vlog_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_12 -> IDX_CUSTOM_VOL_CONTROL_DISPLAY*/
    DECLARE_FIELD(IDX_CUSTOM_VOL_CONTROL_DISPLAY,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_12,
                  CFG_8BIT_T,   1,           &ui1_g_cust_vol_slider_display_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_14 -> IDX_CUSTOM_OOBE_IR_MODE */
    DECLARE_FIELD(IDX_CUSTOM_OOBE_IR_MODE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_14,
                  CFG_8BIT_T,   1,           &ui1_g_cust_oobe_ir_mode,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_15 -> IDX_CUSTOM_HIDE_FROM_INPUT_LIST */
    DECLARE_FIELD(IDX_CUSTOM_HIDE_FROM_INPUT_LIST,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_15,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_HIDE_INPUT);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_16 -> IDX_CUSTOM_HIDE_FROM_INPUT_LIST_MANUAL*/
    DECLARE_FIELD(IDX_CUSTOM_HIDE_FROM_INPUT_LIST_MANUAL,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_16,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
        /* used, IDX_CUSTOM_RSERVE_UI1_EX_17 -> IDX_CUSTOM_COLOR_TUNER_OFFSET_ID*/
    DECLARE_FIELD(IDX_CUSTOM_COLOR_TUNER_OFFSET_ID,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_17,
                  CFG_8BIT_T,   1,           &ui1_g_cust_color_tune_offset,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
   /* used, IDX_CUSTOM_RSERVE_UI1_EX_18 -> IDX_CUSTOM_FULL_UHD_COLOR*/
    DECLARE_FIELD(IDX_CUSTOM_FULL_UHD_COLOR,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_18,
                  CFG_8BIT_T,   1,           &ui1_g_cust_hdmi_mode_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_19 -> IDX_CUSTOM_RETAIL_MODE_FIRST_TIME_SETTING */
    DECLARE_FIELD(IDX_CUSTOM_RETAIL_MODE_FIRST_TIME_SETTING,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_19,
                  CFG_8BIT_T,   1,           &ui1_g_retail_mode_first_time_setting,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_20 -> IDX_CUSTOM_RETAIL_MODE_SOURCE_INFO_STORE */
    DECLARE_FIELD(IDX_CUSTOM_RETAIL_MODE_SOURCE_INFO_STORE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_20,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_21 -> IDX_CUSTOM_USB_POWER_CTRL */
    DECLARE_FIELD(IDX_CUSTOM_USB_POWER_CTRL,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_21,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_22 -> IDX_CUSTOM_COLOR_SPACE */
    DECLARE_FIELD(IDX_CUSTOM_COLOR_SPACE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_22,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_23 -> IDX_CLEAR_ACTION */
    DECLARE_FIELD(IDX_CLEAR_ACTION,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_23,
                  CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_clear_action,      ACFG_PIC_QLT_ELEM_NUM,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_24 -> IDX_DEMO_MODE */
    DECLARE_FIELD(IDX_DEMO_MODE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_24,
                  CFG_8BIT_T,   1,           &ui1_g_demo_mode,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI1_EX_25,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_25,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
     /* used, IDX_CUSTOM_RSERVE_UI1_EX_26 -> IDX_CUSTOM_AIRPLAY_STATE_CTRL */
    DECLARE_FIELD(IDX_CUSTOM_AIRPLAY_STATE_CTRL,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_26,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
                  /* used, IDX_CUSTOM_RSERVE_UI1_EX_27 -> IDX_IPTS_VTRL_HIDE_MANUAL */
    DECLARE_FIELD(IDX_IPTS_VTRL_HIDE_MANUAL,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_27,
                  CFG_8BIT_T,   1,           &ui1_g_cust_vtrl_hide_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_28 -> IDX_CUSTOM_CONTRAST_EN */
    DECLARE_FIELD(IDX_CUSTOM_CONTRAST_EN,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_28,
                  CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_contrast_en,      ACFG_PIC_QLT_ELEM_NUM,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_29 -> IDX_CUSTOM_SUPER_RESOLUTION */
    DECLARE_FIELD(IDX_CUSTOM_SUPER_RESOLUTION,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_29,
                   CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_super_resolution,      ACFG_PIC_QLT_ELEM_NUM,
                   NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_30 -> IDX_CUSTOM_MOTION_BLUR_REDUCTION */
    DECLARE_FIELD(IDX_CUSTOM_MOTION_BLUR_REDUCTION,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_30,
                   CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_motion_blur_reduction,      ACFG_PIC_QLT_ELEM_NUM,
                   NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* set the  def on for vrr DTV02029264*/
    for (ui2_idx = 0; ui2_idx < ACFG_PIC_QLT_ELEM_NUM; ui2_idx ++)
    {
        aui1_g_variable_refresh_rate[ui2_idx] = ACFG_CUST_COMMON_ON;
    }
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_31 -> IDX_CUSTOM_VARIABLE_REFRESH_RATE */
    DECLARE_FIELD(IDX_CUSTOM_VARIABLE_REFRESH_RATE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_31,
                   CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_variable_refresh_rate,      ACFG_PIC_QLT_ELEM_NUM,
                   NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_32 -> IDX_CUSTOM_ETOF */
    DECLARE_FIELD(IDX_CUSTOM_ETOF,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_32,
                   CFG_8BIT_T,   ACFG_INPUT_SRC_NUM,      aui1_g_eotf,      ACFG_INPUT_SRC_NUM,
                   NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* set the  def off DTV DTV02029264*/
    for (ui2_idx = 0; ui2_idx < ACFG_PIC_QLT_ELEM_NUM; ui2_idx ++)
    {
        aui1_g_en_view_angle[ui2_idx] = ACFG_CUST_COMMON_OFF;
    }

    /* modify vivid  def to on */
    for (ui2_ipt_idx = 0;
         ui2_ipt_idx < ACFG_CUST_INPUT_GRP_MAX;
         ui2_ipt_idx ++)
    {
        ui2_item_idx = ui2_ipt_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_DV* ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_PIC_MODE_VIVID;

        if(ui2_item_idx < ACFG_VID_CUST_GAMMA_ELEM_NUM )
        {
            //sdr
            aui1_g_en_view_angle[ui2_ipt_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_PIC_MODE_VIVID] = ACFG_CUST_COMMON_ON;
            //hdr10 ,hdr10+
            aui1_g_en_view_angle[ui2_ipt_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_HDR* ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_PIC_MODE_VIVID] = ACFG_CUST_COMMON_ON;
            //hlg
            aui1_g_en_view_angle[ui2_ipt_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_HLG* ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_PIC_MODE_VIVID] = ACFG_CUST_COMMON_ON;
            //dv
            aui1_g_en_view_angle[ui2_ipt_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_CONTENT_DV* ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_PIC_MODE_VIVID] = ACFG_CUST_COMMON_ON;
        }
    }

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_33 -> IDX_CUSTOM_EN_VIEW_ANGLE */
    DECLARE_FIELD(IDX_CUSTOM_EN_VIEW_ANGLE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_33,
                   CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_en_view_angle,      ACFG_PIC_QLT_ELEM_NUM,
                   NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_34 -> IDX_CUSTOM_GAME_LOW_LATENCY */
    DECLARE_FIELD(IDX_CUSTOM_GAME_LOW_LATENCY,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_34,
                   CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_game_low_latency,      ACFG_PIC_QLT_ELEM_NUM,
                   NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_35 -> IDX_CUSTOM_JUDDER_REDUCTION */
    DECLARE_FIELD(IDX_CUSTOM_JUDDER_REDUCTION,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_35,
                   CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_judder_reduction,      ACFG_PIC_QLT_ELEM_NUM,
                   NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_36 -> IDX_CUSTOM_FILM_MAKER_MODE */
    DECLARE_FIELD(IDX_CUSTOM_FILM_MAKER_MODE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_36,
                   CFG_8BIT_T,   ACFG_INPUT_SRC_NUM,      aui1_g_film_maker_mode,      ACFG_INPUT_SRC_NUM,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_37 -> IDX_CUSTOM_CONTOUR_SMOOTHING */
    DECLARE_FIELD(IDX_CUSTOM_CONTOUR_SMOOTHING,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_37,
                  CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_contrast_smothing,      ACFG_PIC_QLT_ELEM_NUM,
                   NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_38 -> IDX_CUSTOM_OLED_OFF_RS */
    DECLARE_FIELD(IDX_CUSTOM_OLED_OFF_RS,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_38,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_39 -> IDX_CUSTOM_OLED_JB */
    DECLARE_FIELD(IDX_CUSTOM_OLED_JB,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_39,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_40 -> IDX_CUSTOM_OLED_PANEL_REFRESH */
    DECLARE_FIELD(IDX_CUSTOM_OLED_PANEL_REFRESH,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_40,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_41 -> IDX_CUSTOM_OLED_PIXEL_SHIFT */
    DECLARE_FIELD(IDX_CUSTOM_OLED_PIXEL_SHIFT,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_41,
                  CFG_8BIT_T,   1,           &ui1_g_pixel_shift_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_42 -> IDX_CUSTOM_DYNAMIC_CONTENT */
    DECLARE_FIELD(IDX_CUSTOM_DYNAMIC_CONTENT,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_42,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_43 -> IDX_CUSTOM_OTA_LOOP_TEST */
    DECLARE_FIELD(IDX_CUSTOM_OTA_LOOP_TEST,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_43,
                  CFG_8BIT_T,   1,           &ui1_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_44 -> IDX_CUSTOM_MEMC */
    DECLARE_FIELD(IDX_CUSTOM_MEMC,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_44,
                  CFG_8BIT_T,   1,           &ui1_g_cust_memc,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_45 -> IDX_CUSTOM_LIMITED_AD_TRACKING */
    DECLARE_FIELD(IDX_CUSTOM_LIMITED_AD_TRACKING,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_45,
                  CFG_8BIT_T,   1,           &ui1_g_cust_limited_ad_tracking_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_46 -> IDX_CUST_GAMMA */
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_47 -> IDX_CUST_CH_SCAN_STATUS */
    /* This two item are declared in other place */

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_48 -> IDX_CUSTOM_EDGE_ENHANCEMENT */
    for (ui2_idx = 0; ui2_idx < ACFG_PIC_QLT_ELEM_NUM; ui2_idx ++)
    {
        aui1_g_edge_enhancement[ui2_idx] = ACFG_CUST_VID_EDGE_EN_LOW;
    }

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_48 -> IDX_CUSTOM_EDGE_ENHANCEMENT */
    DECLARE_FIELD(IDX_CUSTOM_EDGE_ENHANCEMENT,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_48,
                   CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_edge_enhancement,      ACFG_PIC_QLT_ELEM_NUM,
                   NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* used, IDX_CUSTOM_RSERVE_UI1_EX_49 -> IDX_CUSTOM_GAME_HDR */
    DECLARE_FIELD(IDX_CUSTOM_GAME_HDR,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_49,
                  CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_game_hdr,      ACFG_PIC_QLT_ELEM_NUM,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    /* used, IDX_CUSTOM_RSERVE_UI1_EX_50 -> IDX_CUSTOM_PEAK_LUMINANCE */
    DECLARE_FIELD(IDX_CUSTOM_PEAK_LUMINANCE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_50,
                  CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_peak_lunimance,      ACFG_PIC_QLT_ELEM_NUM,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* from  APP_CFG_RECID_CUST_RSEV_UI1_EX_51 to APP_CFG_RECID_CUST_RSEV_UI1_EX_54 are reserved for pq ,please do not used */
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI1_EX_51,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_51,
                  CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_pq_reserve,      ACFG_PIC_QLT_ELEM_NUM,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI1_EX_52,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_52,
                  CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_pq_reserve,      ACFG_PIC_QLT_ELEM_NUM,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI1_EX_53,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_53,
                  CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_pq_reserve,      ACFG_PIC_QLT_ELEM_NUM,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI1_EX_54,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_54,
                  CFG_8BIT_T,   ACFG_PIC_QLT_ELEM_NUM,      aui1_g_pq_reserve,      ACFG_PIC_QLT_ELEM_NUM,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_EARC_MODE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_55,
                  CFG_8BIT_T,   1,                          &ui1_g_cust_earc,      1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OLED_STATUS,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_56,
                  CFG_8BIT_T,   1,                          &ui1_g_cust_rsev_def,      1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    //IDX_CUSTOM_RSERVE_UI1_EX_57
    DECLARE_FIELD(IDX_CUSTOM_OLED_ERR_COUNT_CHECKSUM,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_57,
                  CFG_8BIT_T,   1,                          &ui1_g_cust_rsev_def,      1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    //IDX_CUSTOM_RSERVE_UI1_EX_58
    DECLARE_FIELD(IDX_CUSTOM_DEMO_TYPE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_58,
                  CFG_8BIT_T,   1,                          &ui1_g_cust_rsev_def,      1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);


    /************** demo *************/
/*
      DECLARE_FIELD(IDX_CUSTOM_ACFG_DEMO_TEST,         //Setting name
                               APP_CFG_GRPID_CUSTOM_BASE,
                               APP_CFG_RECID_CUST_RSEV_UI1_EX_X,    //setting ID  max is 0xff,this field maybe change acfg layout,you should take care of this field
                               CFG_8BIT_T,
                               1,                                        //field length,this field maybe change acfg layout,you should take care of this field
                               &ui1_g_cust_rsev_def,          //default field value,this field should be a pointer,you should take care of this field
                               1,
                               NULL,
                               NULL,
                               ACFG_ACCESS_PUBLIC);

*/
    //IDX_CUSTOM_RSERVE_UI1_EX_59
    DECLARE_FIELD(IDX_CUSTOM_OLED_ERROR_COUNT,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_59,
                  CFG_8BIT_T,   1,                          &ui1_g_cust_rsev_def,      1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

      //IDX_CUSTOM_RSERVE_UI1_EX_60
    DECLARE_FIELD(IDX_CUSTOM_OLED_ERROR_COUNT_BACKUP1,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_60,
                  CFG_8BIT_T,   1,                          &ui1_g_cust_rsev_def,      1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    //IDX_CUSTOM_RSERVE_UI1_EX_61
    DECLARE_FIELD(IDX_CUSTOM_OLED_ERROR_COUNT_BACKUP2,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_61,
                  CFG_8BIT_T,   1,                          &ui1_g_cust_rsev_def,      1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    //IDX_CUSTOM_RSERVE_UI1_EX_62
    DECLARE_FIELD(IDX_CUSTOM_OLED_ERROR_DETECT_ON_OFF,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_62,
                  CFG_8BIT_T,   1,                          &ui1_g_cust_rsev_def,      1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    //IDX_CUSTOM_RSERVE_UI1_EX_63
    DECLARE_FIELD(IDX_CUSTOM_OLED_POWER_MODE_SAVE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_63,
                  CFG_8BIT_T,   1,                          &ui1_g_cust_rsev_def,      1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    //IDX_CUSTOM_RSERVE_UI1_EX_64
    DECLARE_FIELD(IDX_CUSTOM_AUTOMATIC_TIME,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_64,
                  CFG_8BIT_T,   1,                          &ui1_g_automatic_def,      1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    //IDX_CUSTOM_RSERVE_UI1_EX_65  for dv game mode and freesync
    DECLARE_FIELD(IDX_CUSTOM_DV_GAME_MODE_LAST_PIC_MODE,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI1_EX_65,
                  CFG_8BIT_T,   1,                          &ui1_g_dv_last_pic_mode_def,      1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);


    //declare field APP_CFG_RECID_CUST_RSEV_UI1_EX_X + 1  to IDX_CUSTOM_RSERVE_UI1_EX_99
    for(ui2_ipt_idx = 0;
        (ui2_ipt_idx + IDX_CUSTOM_RSERVE_UI1_EX_66) < IDX_CUSTOM_RSERVE_UI1_EX_99; // you need modif this field,do not modif IDX_CUSTOM_RSERVE_UI1_EX_99
        ui2_ipt_idx++)
    {
        DECLARE_FIELD((IDX_CUSTOM_RSERVE_UI1_EX_66 + ui2_ipt_idx),                 // you need modif this field
                      APP_CFG_GRPID_CUSTOM_BASE,
                      (APP_CFG_RECID_CUST_RSEV_UI1_EX_66 + ui2_ipt_idx),           // you need modif this field
                      CFG_8BIT_T,
                      1,
                      &ui1_g_cust_rsev_def,
                      1,
                      NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    }

    return APP_CFGR_OK;
}
static INT32 _acfg_custom_pre_init_cus_resv_ex_16bit(VOID)
{
    UINT16  ui2_ipt_idx        = 0;
    /* used IDX_CUSTOM_RSERVE_UI2_EX_0 -> IDX_CUSTOM_WHITE_BALANCE_OFFSET_ID */

    DECLARE_FIELD(IDX_CUSTOM_WHITE_BALANCE_OFFSET_ID,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_0,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_OLED_JB_COOLING_TIME,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_1,
                  CFG_16BIT_T,   1,           &ui2_g_cust_oled_jb_cooling_time_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OLED_OFFRS_COUNT,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_2,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OLED_JB_COUNT,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_3,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_4,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_4,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_5,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_5,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_6,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_6,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_7,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_7,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_8,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_8,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_9,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_9,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_10,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_10,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_11,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_11,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_12,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_12,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_13,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_13,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_14,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_14,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_15,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_15,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_16,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_16,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_17,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_17,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_18,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_18,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_19,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_19,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_20,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_20,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_21,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_21,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_22,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_22,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_23,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_23,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_24,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_24,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_25,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_25,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_26,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_26,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_27,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_27,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_28,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_28,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_RSERVE_UI2_EX_29,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI2_EX_29,
                  CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    for(ui2_ipt_idx = 0;(ui2_ipt_idx + IDX_CUSTOM_RSERVE_UI2_EX_30) < IDX_CUSTOM_RSERVE_UI2_EX_79;ui2_ipt_idx++)
    {
        DECLARE_FIELD((IDX_CUSTOM_RSERVE_UI2_EX_30 + ui2_ipt_idx),   APP_CFG_GRPID_CUSTOM_BASE,  (APP_CFG_RECID_CUST_RSEV_UI2_EX_30 + ui2_ipt_idx),
                      CFG_16BIT_T,   1,           &ui2_g_cust_rsev_def,  1,
                      NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    }

    return APP_CFGR_OK;
}
static INT32 _acfg_custom_pre_init_cus_resv_ex_32bit(VOID)
{
    UINT16  ui2_ipt_idx        = 0;
    /* used, IDX_CUSTOM_RSERVE_UI4_EX_0 -> IDX_CUSTOM_LAST_CHANNEL_ID*/
    DECLARE_FIELD(IDX_CUSTOM_LAST_CHANNEL_ID,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_0,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_HDMI1_VGA_SETTING,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_1,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_HDMI2_VGA_SETTING,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_2,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_HDMI3_VGA_SETTING,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_3,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_HDMI4_VGA_SETTING,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_4,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_COMP_VGA_SETTING,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_5,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OLED_PANEL_DISPLAY_TIME,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_6,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OLED_DEMO_MODE_DECLINE_TIME_H,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_7,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OLED_DEMO_MODE_DECLINE_TIME_L,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_8,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OLED_LAST_SCREEN_REFRESH_TIME_H,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_9,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OLED_LAST_SCREEN_REFRESH_TIME_L,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_10,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_DISPLAY_TIME,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_11,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_OFFRS_TIME,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_12,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_JB_TIME,   APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_RSEV_UI4_EX_13,
                  CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    for(ui2_ipt_idx = 0;(ui2_ipt_idx + IDX_CUSTOM_RSERVE_UI4_EX_14) < IDX_CUSTOM_RSERVE_UI4_EX_69;ui2_ipt_idx++)
    {
        DECLARE_FIELD((IDX_CUSTOM_RSERVE_UI4_EX_14 + ui2_ipt_idx),   APP_CFG_GRPID_CUSTOM_BASE,  (APP_CFG_RECID_CUST_RSEV_UI4_EX_14 + ui2_ipt_idx),
                      CFG_32BIT_T,   1,           &ui4_g_cust_rsev_def,  1,
                      NULL,         NULL,        ACFG_ACCESS_PUBLIC);
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_custom_pre_init
 *
 * Description:
 *      Pre initialiation. You can do following thing here:
 *  1. Override the default value
 *  2. Put some config in EEPROM
 *  3. Remove some configs by setting them as b_enable=FALSE
 *  4. Change the value in at_acfg_descr
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static void _acfg_custom_ParseFileSetVar(const char* pcVarName, unsigned int uiVal)
{
    //DBG_LOG_PRINT(("[ACFG][DEBUG]_acfg_custom_ParseFileSetVar(%s, %u)\n", pcVarName, uiVal));

    if( 0 == strcmp("g_ACFG_u32DebugPicture", pcVarName) )
    {
        //printf(" Found ==> VarName=%s, uiVal=%d\n", pcVarName, uiVal);
        //DBG_LOG_PRINT(("[ACFG][DEBUG] Set %s = %u\n", pcVarName, uiVal ));
        g_ACFG_u32DebugPicture = uiVal;
        DBG_LOG_PRINT(("[ACFG][DEBUG]g_ACFG_u32DebugPicture: 0x%X\n", g_ACFG_u32DebugPicture));
    }
    else if( 0 == strcmp("g_ACFG_u32DebugFlag", pcVarName) )
    {
        //printf(" Found ==> VarName=%s, uiVal=%d\n", pcVarName, uiVal);
        //DBG_LOG_PRINT(("[ACFG][DEBUG] Set %s = %u\n", pcVarName, uiVal ));
        g_ACFG_u32DebugFlag = uiVal;
        DBG_LOG_PRINT(("[ACFG][DEBUG]g_ACFG_u32DebugFlag: 0x%X\n", g_ACFG_u32DebugFlag));
    }
}

extern INT32 acfg_custom_pre_init(VOID)
{
    INT32 i4_ret = APP_CFGR_OK;

    DBG_LOG_PRINT(("[ACFG][%s %s %d] \n", __FILE__, __func__, __LINE__));

    _acfg_custom_get_model_name_from_driver();

    NAV_Check_Back_Panel_Button();

    {
        UINT32 ui4_support = 0;

        a_cfg_cust_drv_get_oled_support_compensation(&ui4_support);
        if(ui4_support)
        {
            DBG_LOG_PRINT(("support oled compensation!\n"));
            b_g_is_oled_suppend = TRUE;
        }
    }

    // Read debug para ...
    AppTV_ParseDgbFile( "/data/acfg_debug.txt", _acfg_custom_ParseFileSetVar );


    // Check /data/acfg_debug_backlight
    // Check file should exist...
    if( access("/data/acfg_debug_backlight", F_OK) == 0 )
    {
        DBG_LOG_PRINT(("acfg_debug_backlight exist~\n"));
        g_ACFG_u32DebugPicture |= ACFG_DBG_PICT_BACKLIGHT;
    }
    else
    {
        //DBG_LOG_PRINT(("acfg_debug_backlight is not exist~\n"));
    }

    /* Set the access mask to  factory */
    at_acfg_descr[IDX_AIR_CCH].ui1_access_mask = ACFG_ACCESS_FACTORY;
    at_acfg_descr[IDX_AIR_LCH].ui1_access_mask = ACFG_ACCESS_FACTORY;
    at_acfg_descr[IDX_CAB_CCH].ui1_access_mask = ACFG_ACCESS_FACTORY;
    at_acfg_descr[IDX_CAB_LCH].ui1_access_mask = ACFG_ACCESS_FACTORY;
    #ifdef APP_DCR_SUPPORT
    at_acfg_descr[IDX_DCR_CCH].ui1_access_mask = ACFG_ACCESS_FACTORY;
    at_acfg_descr[IDX_DCR_LCH].ui1_access_mask = ACFG_ACCESS_FACTORY;
    #endif
    at_acfg_descr[IDX_INPUT_MAIN].ui1_access_mask = ACFG_ACCESS_FACTORY;
    at_acfg_descr[IDX_INPUT_SUB].ui1_access_mask = ACFG_ACCESS_FACTORY;
    at_acfg_descr[IDX_BS_SRC].ui1_access_mask = ACFG_ACCESS_FACTORY;
    at_acfg_descr[IDX_BS_SRC].pt_def_value = &ui1_bs_src_def;

    if (!g_h_cecm)
    {
        i4_ret = c_cecm_open_svc (_acfg_custom_cec_nfy_fct, NULL, &g_h_cecm);
        ACFG_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = acfg_cust_video_pre_init();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_audio_pre_init();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_vga_pre_init();
    ACFG_LOG_ON_FAIL(i4_ret);

#ifdef APP_MMP_SUPPORT
    i4_ret = acfg_cust_mmp_pre_init();
    ACFG_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = acfg_cust_network_pre_init();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_hotel_pre_init();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_misc_pre_init();
    ACFG_LOG_ON_FAIL(i4_ret);

#ifndef APP_CUST_FAC
    if (a_app_cust_fac())
#endif
    {
        i4_ret = acfg_cust_factory_pre_init();
        ACFG_LOG_ON_FAIL(i4_ret);
    }

#ifndef APP_CUST_PLT_OPT
    if (a_app_cust_plt_opt())
#endif
    {
        i4_ret = acfg_cust_plf_opt_pre_init();
        ACFG_LOG_ON_FAIL(i4_ret);
    }

    acfg_cust_ble_pre_init();

    /* Reserve Field, 8 bit, total 30 */
    i4_ret = _acfg_custom_pre_init_cus_resv_8bit();
    ACFG_LOG_ON_FAIL(i4_ret);

    /* Reserve Field, 16 bit, total 10 */
    i4_ret = _acfg_custom_pre_init_cus_resv_16bit();
    ACFG_LOG_ON_FAIL(i4_ret);

    /* Reserve Field, 32 bit, total 4 */
    i4_ret = _acfg_custom_pre_init_cus_resv_32bit();
    ACFG_LOG_ON_FAIL(i4_ret);

    /* the following for the reserve field ex*/

    /* Reserve Field ex, 8 bit, total 51 */
    i4_ret = _acfg_custom_pre_init_cus_resv_ex_8bit();
    ACFG_LOG_ON_FAIL(i4_ret);

    /* Reserve Field ex, 16 bit, total 30 */
    i4_ret = _acfg_custom_pre_init_cus_resv_ex_16bit();
    ACFG_LOG_ON_FAIL(i4_ret);

    /* Reserve Field ex, 32 bit, total 12*/
    i4_ret = _acfg_custom_pre_init_cus_resv_ex_32bit();
    ACFG_LOG_ON_FAIL(i4_ret);

    acfg_cust_video_update_pq_def_from_odm();

    /*Note, this field is to stroe the last acfg idx which has been released*/
    DECLARE_FIELD(IDX_CUSTOM_ACFG_LAST_IDX,  APP_CFG_GRPID_CUSTOM_BASE,  APP_CFG_RECID_CUST_ACFG_LST_IDX,
                  CFG_16BIT_T,   1,           &ui2_g_cust_acfg_lst_idx,  1,
                  NULL,         NULL,        ACFG_ACCESS_PUBLIC);

    /* Setup EEPROM */
    i4_ret = acfg_cust_eep_field_assign();
    ACFG_LOG_ON_FAIL(i4_ret);

    /* to move the dev db init from post init to the pre init*/
    if (a_cfg_custom_get_wifi_remote_support())
    {
        /*dev setup init*/
        a_dev_db_init();
    }

    return APP_CFGR_OK;
}

extern INT32 MTVDECEX_HDMI_SetEdidIndexByPort(UINT8 ui1_port_idx,UINT8 ui1_edid_idx,BOOL b_hdmi_mode);

static INT32 acfg_get_serial_number()
{
    CHAR            s_sn[64] = {0};
    CHAR            s_tmn[164] = {0};
    UINT32          ui4_buff_len = sizeof(s_sn);

    ACFG_LOG_ON_FAIL(a_uli_get_serial_number((UINT8 *)&(s_sn[0]), &ui4_buff_len));

    if(0 == c_strlen(s_sn))
    {
        c_strcpy(s_sn, "000000000000");

        DBG_INFO(("%s() s_dst=[%s]......\r\n",__FUNCTION__, (char *)s_sn));
        c_snprintf(s_tmn, 128, "echo \"%s\" > /tmp/cfg_tv_sn", (char *)s_sn);

        AP_SYSTEM_CALL(s_tmn);

        return APP_CFGR_NO_ACTION;
    }

    c_snprintf(s_tmn, 164, "echo \"%s\" > /tmp/cfg_tv_sn", (char *)s_sn);

    AP_SYSTEM_CALL(s_tmn);

    // keep cast_root as a read-only partition; read /tmp/cfg_tv_sn instead
    /*
    c_snprintf(s_tmn, 164, "mount -o rw,remount /cast_root/;echo \"%s\" > /cast_root/system/factory/serial.txt;mount -o ro,remount /cast_root/", (char *)s_sn);

    AP_SYSTEM_CALL(s_tmn);
    */

    DBG_INFO(("%s() s_dst=[%s] len:%d......\r\n",__FUNCTION__, (char *)s_sn, c_strlen(s_sn)));

    return APP_CFGR_OK;

}

/*-----------------------------------------------------------------------------
 * Name: acfg_custom_post_init
 *
 * Description:
 *      Post initialiation. You can do following thing here:
 *  1. Update the middleware component in accordance with config value.
 *  2. Always set a config to a specific value.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_custom_post_init(VOID)
{
    INT32 i4_ret = APP_CFGR_OK;

    DBG_LOG_PRINT(("[ACFG]{%s, %s,%d} ================================ start \n", __FILE__, __FUNCTION__, __LINE__ ));
    //DBG_LOG_PRINT(("[%s %s %d] \n", __FILE__, __func__, __LINE__));
    ACFG_COUNTRY_CODE_T t_country = ACFG_COUNTRY_CODE_LAST_ENTRY;
    ISO_639_LANG_T s639_lang = {0};
#ifdef MT5695_MODEL
    UINT8 ui1_oled_error_detect_disable = 0;
#endif
#ifdef APP_WAKE_ON_WLAN
    PCL_WIFI_WOL_CTRL_T e_wlan_wol = PCL_WIFI_WOL_ENABLE;
#endif
    a_tv_custom_set_model_name();
    a_tv_custom_set_version();
    a_tv_custom_set_serial_number();
    a_uli_msg_create();
    acfg_get_serial_number();

    i4_ret = a_cfg_custom_get_country_code(&t_country);
    ACFG_LOG_ON_FAIL(i4_ret);

    a_tv_custom_set_country((UINT16)t_country);

    b_g_gll_off_flag = FALSE;

#ifdef APP_MMP_SUPPORT
    i4_ret = acfg_cust_mmp_post_init();
    ACFG_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = acfg_cust_network_post_init();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_hotel_post_init();
    ACFG_LOG_ON_FAIL(i4_ret);

#ifndef APP_CUST_FAC
    if (a_app_cust_fac())
#endif
    {
        i4_ret = acfg_cust_factory_post_init();
        ACFG_LOG_ON_FAIL(i4_ret);
    }

#ifndef APP_CUST_PLT_OPT
    if (a_app_cust_plt_opt())
#endif
    {
        i4_ret = acfg_cust_plf_opt_post_init();
        ACFG_LOG_ON_FAIL(i4_ret);
    }

    acfg_cust_ble_post_init();

#ifdef LINUX_TURNKEY_SOLUTION
    a_tv_custom_set_3rd_app_info();
#endif

#ifdef APP_NET_DLNA_SUPPORT
#ifdef APP_DMR_SUPPORT
    i4_ret = a_nw_enable_dlna_dmr();
    ACFG_LOG_ON_FAIL(i4_ret);
#endif
#endif

    _acfg_custom_acr_file_init();

#ifdef TVIS_SUPPORT
    CHAR       s_cmd[128] = {0};
    TV_WIN_ID_T                 e_focus_id;
    ISL_REC_T                   t_isl_rec;
    CHAR       s_disp_name[128] = {0};

    i4_ret = a_tv_get_focus_win(&e_focus_id);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_isl_rec);
    ACFG_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_to_ps(a_isl_get_display_name(&t_isl_rec),
                   s_disp_name, 128);

    c_sprintf(s_cmd, "echo %s > /tmp/input", s_disp_name);
    AP_SYSTEM_CALL(s_cmd);
#endif

#ifndef APP_CUST_PLT_OPT
    if (a_app_cust_plt_opt())
#endif
    {
#ifdef LINUX_TURNKEY_SOLUTION
        /*BOOL b_3D_support = FALSE;
        a_cfg_custom_plf_opt_get_3d_support(&b_3D_support);
        if (b_3D_support)*/
        {
            FILE *pf = NULL;

            if ((pf = fopen("/tmp/device_name", "w")) != NULL)
            {
                fprintf(pf, "%s", "Vizio DTV");
                fclose(pf);
                pf = NULL;
            }
        }
#endif
    }

    /* set language of vkb */
    a_cfg_get_gui_lang(s639_lang);
    a_vkb_set_lang(s639_lang);


    a_tv_state_init();

#ifdef MTK_TVAP_PROXY_CUSTOM_SUPPORT
    tvap_proxy_cust_init();
#endif

#ifdef APP_WAKE_ON_WLAN
    c_pcl_get_wifi_wol_ctrl(&e_wlan_wol);
    if (PCL_WIFI_WOL_DISABLE == e_wlan_wol)
    {
        c_pcl_set_wifi_wol_ctrl(PCL_WIFI_WOL_ENABLE);
    }
#endif

    {
        /* Sync power mode to icl */
        UINT32  ui4_eco = 0;
        a_cfg_custom_get_drv_eco_mode(&ui4_eco);    /* 0:Eco Mode, 1:Quick Start Mode */
#ifdef APP_SUPPORT_STR_CORE_OFF
        a_cfg_set_fast_boot(((0 == ui4_eco) ? APP_CFG_FAST_BOOT_ON : APP_CFG_FAST_BOOT_OFF));
#endif
        a_icl_custom_set_power_mode(((0 == ui4_eco) ? ICL_CUSTOM_POWER_MODE_ECO : ICL_CUSTOM_POWER_MODE_QUICK_START));
    }

#if 0//( !ENABLE_HDMI_EDID_NEW_METHOD )
    //for factory reset full uhd color in "input setting"
    {
        UINT8   ui1_color_value;
        i4_ret = a_cfg_cust_get_full_uhd_color(&ui1_color_value);
        ACFG_DEBUG_HDMI_EDID(
            DBG_LOG_PRINT(("[ACFG][HDMI][EDID]{%s,%d} ACFG.ui1_color_value:%d\n",
                __FUNCTION__, __LINE__, ui1_color_value ));
        );

        DBG_INFO(("<UHD COLOR> file: %s line: %d  %s a_cfg_cust_get_full_uhd_color(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_color_value));
        if(ui1_color_value == 0)
        {
            ACFG_DEBUG_HDMI_EDID(
                DBG_LOG_PRINT(("[ACFG][HDMI][EDID]{%s,%d} set edid 1~3\n",
                    __FUNCTION__, __LINE__ ));
            );

            inp_lst_set_edid_by_port(1,0);
            inp_lst_set_edid_by_port(2,0);
            inp_lst_set_edid_by_port(3,0);
        }
    }
#endif

    {
        UINT16          ui2_idx = 0;

        a_cfg_custom_get_speakers_out(&ui2_idx);

        if(2 == ui2_idx)    //Auto
        {
            _acfg_cust_init_speaker_auto();

        }
    }

    if(a_cfg_custom_get_updater_completed_flag())
    {
#ifdef MT5691_MODEL
        //read version file to reset pic value
        if(_cfg_cust_check_trigger_reset_pic())
        {
            DBG_LOG_PRINT(("[%s %s %d] _cfg_cust_check_trigger_reset_pic \n", __FILE__, __func__, __LINE__));
            a_cfg_reset_all_pic_settings();
            a_cfg_store();
        }
#endif

        //DBG_INFO(("[%s %s %d] _cfg_cust_check_pic_mode_changed_status here\n", __FILE__, __func__, __LINE__));
        //_cfg_cust_check_pic_mode_changed_status();
    }

#ifdef CLI_SUPPORT
    /* Add cli commands */
    acfg_cust_regist_cli_cmd_tbl();
#endif

    {
         UINT8 ui1_log_level = 0;
         a_cfg_cust_get_log_level(&ui1_log_level);
         /* turn off driver log */
         DBG_LOG_PRINT(("[%s %s %d] set log level here\n", __FILE__, __func__, __LINE__));
         a_cfg_cust_set_log_level(ui1_log_level);
     }

#ifdef MT5695_MODEL
    a_cfg_custom_get_oled_error_detect_disable(&ui1_oled_error_detect_disable);
    /*need get oled supported and error detect is disable or not*/
    if(a_is_oled_compensation_support()&&ui1_oled_error_detect_disable == 0)
    {
        ACFG_LOG_ON_FAIL(c_scc_disp_set_detect_oled_pal_err_nfy(h_g_acfg_scc_main_disp,a_acfg_disp_detect_oled_pal_err_nfy_fct,NULL));
    }
#endif

    if (TVR_OK != a_tv_set_env_to_mpool("wdt_reset_count", "0"))
    {
        DBG_ERROR(("%s %d <#> Reset wdt_reset_count failed\n", __func__, __LINE__));
    }

    DBG_LOG_PRINT(("[ACFG]{%s, %s,%d} ---------------------------------  end \n", __FILE__, __FUNCTION__, __LINE__ ));

    return APP_CFGR_OK;
}
extern HANDLE_T acfg_custom_get_cec_handle (VOID)
{
    return g_h_cecm;
}

#if 0
extern VOID acfg_custom_set_crnt_pic_mode_all_dynamic_en_view_angle_for_on(VOID)
{
    INT32           i4_ret = APP_CFGR_OK;
    UINT16          ui2_elem_idx = 0;
    UINT8           ui1_video_type;
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1];
    ISL_REC_T       t_isl_rec;
    UINT16          ui2_ipt = 0;
    INT16           i2_pic_mode = 0;
    UINT8           ui1_input_src = 0;

    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input_src);
    ACFG_LOG_ON_FAIL(i4_ret);

    /* Step 2: Get the index */
    c_memset (&t_isl_rec, 0, sizeof (ISL_REC_T));
    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input_src, & t_isl_rec);
    ui2_ipt = acfg_custom_get_input_grp(&t_isl_rec);

    /* Get picture mode */
    i4_ret = a_cfg_av_get (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
    ACFG_LOG_ON_FAIL(i4_ret);


    for (ui1_video_type = ACFG_CUST_CONTENT_SDR ;ui1_video_type < ACFG_CUST_CONTENT_MAX;ui1_video_type ++)
    {
        if(i2_pic_mode <  ACFG_PRE_SET_PIC_MODE_NUM)
        {
            ui2_elem_idx = ui2_ipt * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ui1_video_type * ACFG_PRE_SET_PIC_MODE_NUM + i2_pic_mode;
        }
        else
        {
            i2_pic_mode = i2_pic_mode - ACFG_PRE_SET_PIC_MODE_NUM;
            ui2_elem_idx = APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + ui1_video_type * ACFG_CUST_SET_PIC_MODE_NUM + i2_pic_mode;
        }
        //DBG_LOG_PRINT( ("------SET-----[ACFG]  %s %d  ::APP_CFG_RECID_VID_EN_VIEW_ANGLE:::type:%d  ui2_elem_idx:%d\n",__FUNCTION__,__LINE__,a_acfg_cust_get_dynamic_range(),ui2_elem_idx));
        i4_ret = acfg_set_int16_by_idx (IDX_CUSTOM_EN_VIEW_ANGLE, ui2_elem_idx, (INT16)ACFG_CUST_COMMON_ON);
        ACFG_LOG_ON_FAIL(i4_ret);
    }

}
#endif


/*-----------------------------------------------------------------------------
 * Name: acfg_custom_get_elem_index
 *
 * Description:
 *      Get the element index for given config id and the target input source.
 *  The caller of this API would ensure thread-safe.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_custom_get_elem_index(
    UINT16  ui2_id,
    UINT8   ui1_input_src,
    UINT16* pui2_idx)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;
    UINT16  ui2_cfg_grp = CFG_GET_GROUP(ui2_id);

    switch(ui2_cfg_grp)
    {
    case APP_CFG_GRPID_VIDEO:
    case APP_CFG_GRPID_DISP:
        i4_ret = acfg_cust_video_get_elem_idx(ui2_id, ui1_input_src, pui2_idx);
        ACFG_LOG_ON_FAIL(i4_ret);
        break;
    case APP_CFG_GRPID_AUDIO:
        i4_ret = acfg_cust_audio_get_elem_idx(ui2_id, ui1_input_src, pui2_idx);
        ACFG_LOG_ON_FAIL(i4_ret);
        break;
    default:
        *pui2_idx = 0;
        break;
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_custom_get_predefined_value
 *
 * Description:
 *      Some settings may have predefined value. For example, for video quality,
 *  there would be a picture mode
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_custom_get_predefined_value(
    UINT16  ui2_id,
    UINT8   ui1_mode,
    INT16*  pi2_val)
    {
    INT32   i4_ret = APP_CFGR_NO_ACTION;
    UINT16  ui2_cfg_grp = CFG_GET_GROUP(ui2_id);

    switch(ui2_cfg_grp)
        {
    case APP_CFG_GRPID_VIDEO:
        i4_ret = acfg_cust_video_get_predef_value(ui2_id, ui1_mode, pi2_val);
                ACFG_LOG_ON_FAIL(i4_ret);
        break;
    case APP_CFG_GRPID_AUDIO:
        i4_ret = acfg_cust_audio_get_predef_value(ui2_id, ui1_mode, pi2_val);
                ACFG_LOG_ON_FAIL(i4_ret);
        break;
    default:
        return APP_CFGR_INV_ARG;
            }

    return APP_CFGR_OK;
}

#ifdef ACFG_CUSTOM_DEF_UPDATE_TIME_ZONE
INT32 acfg_custom_update_cast_time (VOID)
/*-----------------------------------------------------------------------------
 * Name: acfg_custom_update_cast_time
 *
 * Description:
 *     This function updates cast time according to local time change.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
{
#if 0
        CHAR *str_cast_zone[]={
        "Pacific/Honolulu",//-10
        "America/Anchorage",//-9
        "America/Los_Angeles",//-8
        "America/Denver",//-7
        //"America/Phoenix",//-7
        "America/Chicago",//-6
        //"America/Bogota",//-5 //---"America/Indiana/Indianapolis",
        "America/New_York",//-5
        "America/Halifax",//-4
        //"America/St_Johns",//"America/St_Johns",//-3.5
        "America/Sao_Paulo",//-3
        "America/Noronha",//-2
        "Atlantic/Cape_Verde",//-1
        "Africa/Bamako",//"Europe/London",//0
        "Europe/Lisbon",//"Atlantic/Faroe",//+1
        "Europe/Oslo",//"Europe/Istanbul",//+2
        "Europe/Istanbul",//"Europe/Moscow",//+3
        "Asia/Dubai",//+4//"Asia/Tehran"
        "Asia/Ashgabat",//+5
        "Asia/Thimphu",//"Asia/Dhaka"//+6
        "Asia/Ho_Chi_Minh",//+7
        "Asia/Hong_Kong",//+8
        "Asia/Seoul",//+9
        "Australia/Brisbane",//+10
        "Pacific/Pohnpei",//+11
        "Pacific/Kwajalein",//+12
        "Pacific/Kwajalein",//-12
        "Pacific/Pago_Pago",//-11
    };
#endif

    CHAR *str_cast_zone_wo_dst[]={
        "Etc/GMT+10",
        "Etc/GMT+9",
        "Etc/GMT+8",
        "Etc/GMT+7",
        //"Etc/GMT+7",
        "Etc/GMT+6",
        //"Etc/GMT+5",   remove for vizio spec change 4.2.1
        "Etc/GMT+5",
        "Etc/GMT+4",
        //"Etc/GMT+3.5",
        "Etc/GMT+3",
        "Etc/GMT+2",
        "Etc/GMT+1",
        "Etc/GMT",
        "Etc/GMT-1",
        "Etc/GMT-2",
        "Etc/GMT-3",
        "Etc/GMT-4",
        "Etc/GMT-5",
        "Etc/GMT-6",
        "Etc/GMT-7",
        "Etc/GMT-8",
        "Etc/GMT-9",
        "Etc/GMT-10",
        "Etc/GMT-11",
        "Etc/GMT-12",
        "Etc/GMT+12",
        "Etc/GMT+11",
    };

    UINT8   ui1_tz = 0;
    UINT16  ui2_dls = 0;
    CHAR  cast_str_zone[128]={0};

    a_cfg_custom_get_timezone_idx(&ui1_tz);
    a_cfg_custom_get_dst(&ui2_dls);

    DBG_INFO(("\n<ACFG> %s() ui2_dls=%d,ui1_tz=%d\n", __FUNCTION__, ui2_dls, ui1_tz));

    if (ui1_tz >= sizeof(str_cast_zone_wo_dst)/sizeof(CHAR *))
    {
        DBG_ERROR(("\r\n%s %d <#> ERROR! ui1_tz(%d) too big\r\n", __func__, __LINE__, ui1_tz));
        return APP_CFGR_INV_ARG;
    }

    c_strcpy(cast_str_zone,str_cast_zone_wo_dst[ui1_tz]);

    DBG_INFO(("\n<ACFG> %s() cast_str_zone=%s\n", __FUNCTION__, cast_str_zone));
    a_c4tv_apron_set_timezone(cast_str_zone);
    return APP_CFGR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: acfg_custom_update_time_zone
 *
 * Description:
 *     This function updates time zone setting to Data/Time library.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 acfg_custom_update_time_zone(VOID)
{
    INT32   i4_ret;
    TIME_T  t_tz_offset = 0;
    BOOL    b_dst;
    UINT8   ui1_dt_sync_mode;
    BOOL    b_dt_ctrl = FALSE;

    /* TODO: (Steven) update base on IDX_CUSTOM_TIMEZONE_IDX is better */
  #if 0
    i4_ret = a_cfg_custom_update_time_zone_data();
    if (i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }
  #endif
    i4_ret = a_cfg_get_time_zone_data(&t_tz_offset, &b_dst);

    if (i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }
    //DBG_LOG_PRINT(("[TIME +++ ] {%s %s() %d}. t_tz_offset = %lld\n",__FILE__, __FUNCTION__, __LINE__,t_tz_offset));
    i4_ret = a_cfg_get_dt_sync_mode(&ui1_dt_sync_mode);
    if (i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    b_dt_ctrl = c_dt_get_tz_ctrl();

    /* force set tz ctrl to off */
    c_dt_set_tz_ctrl(FALSE);

    c_dt_set_tz(t_tz_offset);

    c_dt_set_tz_ctrl(b_dt_ctrl);

    if(ui1_dt_sync_mode == APP_CFG_DT_SYNC_MODE_MANUAL)
    {
        c_dt_set_dst_ctrl(FALSE);
        c_dt_set_dst(FALSE);
    }
    else
    {
#ifdef APP_CFG_UPD_TZ_IGNORE_TS_INFO
        c_dt_set_dst_ctrl(FALSE);
        c_dt_set_dst(b_dst);
#else
        c_dt_set_dst_ctrl(b_dst);
        if(b_dst == FALSE)
        {
            c_dt_set_dst(FALSE);
        }
#endif
    }

    acfg_custom_update_cast_time();
    return APP_CFGR_OK;
}
#endif

/*******************************************************************************
* Name:_acfg_cust_scr_mode_info
* Description:
* Inputs:
* Outputs:
* Returns:
*******************************************************************************/
static VOID _acfg_cust_scr_mode_info(
    VOID*                       pv_unused,
    VOID*                       pv_unused2,
    VOID*                       pv_unused3)
{
    extern INT32 banner_update_scr_mode(VOID);
    banner_update_scr_mode();
}

/*******************************************************************************
* Name:_acfg_cust_scr_mode_change
* Description:
* Inputs:
* Outputs:
* Returns:
*******************************************************************************/
static VOID _acfg_cust_scr_mode_change(VOID)
{
    nav_request_context_switch(_acfg_cust_scr_mode_info,
                               NULL,
                               NULL,
                               NULL);
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_reset(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    INT32       i4_ret;
    UINT16      ui2_svc_lst_id;
#ifdef APP_537X_SUPPORT
    TV_MODE_T   e_tv_mode;
    CHAR        s_curr_disp_name[ACFG_MAX_DISP_NAME+1];
    CHAR*       s_target_disp_name = NULL;
    ISL_REC_T   t_isl_rec;
    UINT8       ui1_i;
#endif  /* APP_537X_SUPPORT */

#if 0
    /* Color gain, offset are factory settings. Howerver, user mode should
       be always reset to default regardless of reset level. */
    i4_ret = a_cfg_custom_reset_usr_clr_temp(ACFG_ACCESS_PUBLIC);
    ACFG_LOG_ON_FAIL(i4_ret);
#endif

    /* common settings */
    i4_ret = a_cfg_update_time_zone();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_update_dcs();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_svc_lst_id, NULL);
    ACFG_LOG_ON_FAIL(i4_ret);

    /* also run a_cfg_update_dt_sync_mode() */
    i4_ret = a_cfg_set_tuner_sync_src(ui2_svc_lst_id, NULL);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_update_rating_settings();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_update_vchip_rating_region();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_update_auto_sleep();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_update_timer_power();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_update_input_src_attr();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_update_factory_mode();
    ACFG_LOG_ON_FAIL(i4_ret);

    /* DVBT */
#ifdef  APP_DVBT_SUPPORT
    i4_ret = a_cfg_update_country_and_region_id();
    ACFG_LOG_ON_FAIL(i4_ret);
#endif  /* APP_DVBT_SUPPORT */

    /* Audio settings */
    i4_ret = a_tv_set_audio_mute(TV_AUDIO_MUTE_MASK_FORCE, TRUE);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_update_spdif_type();
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_update_drc_mode();
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_update_cmpss_mode();
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_update_dmix_mode();
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_update_agc();
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_update_aud_latency();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_FRONT_LEFT));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_FRONT_RIGHT));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_REAR_LEFT));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_REAR_RIGHT));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_CENTER));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_SUB_WOOFER));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_AD_VOLUME));
    ACFG_LOG_ON_FAIL(i4_ret);
#ifdef APP_SPDIF_DELAY_SUPPORT
    i4_ret = a_cfg_update_spdif_delay();
    ACFG_LOG_ON_FAIL(i4_ret);
#endif

#ifdef APP_537X_SUPPORT
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_SURROUND));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_REVERB));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQUALIZER));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("\n======update _acfg_cust_evt_handle_reset======\n"));

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS));
    ACFG_LOG_ON_FAIL(i4_ret);
#ifdef APP_BBE_SUPPORT
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BBE_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_update_aud_bbe_eq_band_lvl_all();
    ACFG_LOG_ON_FAIL(i4_ret);
#endif /* APP_BBE_SUPPORT */

    i4_ret = a_tv_set_audio_mute(TV_AUDIO_MUTE_MASK_FORCE, FALSE);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
    ACFG_LOG_ON_FAIL(i4_ret);

    /* Advanced video */
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_ETI));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FLESH_TONE));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HDMI_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VGA_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);

#ifdef APP_MJC_SUPPORT
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT));
    ACFG_LOG_ON_FAIL(i4_ret);
#endif /* APP_MJC_SUPPORT */
#ifdef APP_DI_SUPPORT
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_MA));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_EDGE));
    ACFG_LOG_ON_FAIL(i4_ret);
#endif
#ifdef APP_GAME_MODE_SUPPORT
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);
#endif

#ifdef APP_PQ_DEMO_SUPPORT
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_PQ_DEMO));
    ACFG_LOG_ON_FAIL(i4_ret);
#endif

   i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLACK_STRETCH));
   ACFG_LOG_ON_FAIL(i4_ret);

   i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_WHITE_STRETCH));
   ACFG_LOG_ON_FAIL(i4_ret);

#ifdef APP_XVYCC_SUPPORT
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_XVYCC));
    ACFG_LOG_ON_FAIL(i4_ret);
#endif
#ifdef APP_WCG_SUPPORT
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_WCG));
    ACFG_LOG_ON_FAIL(i4_ret);
#endif
#ifdef APP_BLUE_STRETCH_SUPPORT
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_STRETCH));
    ACFG_LOG_ON_FAIL(i4_ret);
#endif
#ifdef APP_MPEG_NR_SUPPORT
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR));
    ACFG_LOG_ON_FAIL(i4_ret);
#endif

    /* settings are relative to display group */
    a_cfg_av_get_disp_name(s_curr_disp_name,
                           sizeof(s_curr_disp_name));

    for(ui1_i = 0; ui1_i < 2; ui1_i++) /* MAIN and SUB */
    {
        if(ui1_i==0)
        {
            s_target_disp_name  = SN_PRES_MAIN_DISPLAY;
        }
        else if(ui1_i == 1)
        {
            a_tv_get_mode(&e_tv_mode);
            if(e_tv_mode == TV_MODE_TYPE_NORMAL)
            {
                /* not pip/pop */
                break;
            }
            s_target_disp_name  = SN_PRES_SUB_DISPLAY;
        }

        a_cfg_av_set_disp_name(s_target_disp_name);

        a_tv_get_crnt_isl_rec(s_target_disp_name, &t_isl_rec);

        /* Video settings */
        /* Overscan */
        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE));
        ACFG_LOG_ON_FAIL(i4_ret);

        /* Reset Video H/V pos. */
        if(((t_isl_rec.e_src_type == INP_SRC_TYPE_AV) || ((t_isl_rec.e_src_type == INP_SRC_TYPE_TV)))
           &&
           (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_VGA))
        {
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V));
            ACFG_LOG_ON_FAIL(i4_ret);
        }
        /* VGA settings */
        i4_ret = acfg_vga_reset();
        ACFG_LOG_ON_FAIL(i4_ret);

        a_tv_get_crnt_isl_rec(s_target_disp_name, &t_isl_rec);
        if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
           t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
        {
            /* Auto */
            i4_ret = a_cfg_vga_auto_clk_phs_pos();
            ACFG_LOG_ON_FAIL(i4_ret);
        }
    }

    a_cfg_av_set_disp_name(s_curr_disp_name);
#endif  /* APP_537X_SUPPORT */

#ifdef APP_NETWORK_SUPPORT
    if ((a_mmp_get_ap_status() != MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC) &&
        (a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED))
    {
        i4_ret = a_nw_default_reset_update();
        ACFG_LOG_ON_FAIL(i4_ret);
    }
#endif

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_chg_service(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    /* turn off test patterns when input source and channel changed */
    UINT8   ui1_val = 1;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_TEST_PATTERN),
             (VOID *) &ui1_val,
             ICL_RECID_CUSTOM_COLOR_TUNER_TEST_PATTERN_SIZE);

    //note: no signal need close clear action
    if(a_cfg_cust_oled_support() == TRUE)
    {
        a_cfg_cust_drv_set_oled_cmo((UINT8)0);
    }
    if (a_cfg_cust_get_support_clear_aciton() == TRUE)
    {
        VIZIO_CLEAR_ACTION_D_SET(0);
    }

    a_cfg_set_hdr_type(SCC_VID_PQ_SDR);

    return APP_CFGR_OK;
}

#if 0
static VOID _acfg_cust_show_game_low_latency(VOID *arg1,VOID *arg2,VOID *arg3)
{
    menu_game_low_latency_toast();
}
#endif


BOOL a_cfg_cust_is_tts_item_enable(VOID)
{
#ifdef APP_TTS_SUPPORT
    ACFG_RETAIL_MODE_T      t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    INT32                   i4_ret = MENUR_OK;
    ISO_639_LANG_T          s639_lang={0};

    {
        i4_ret = a_cfg_get_gui_lang(s639_lang);
        if(i4_ret != MENUR_OK)
        {
            /*get current language fail can not set tts*/
            return FALSE;
        }

        if(c_strncmp(s639_lang,"eng",3) != 0 )
        {
            /*only set in english*/
            return FALSE;
        }
    }
/*
    if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status())
    {
        DBG_INFO(("_is_tts_item_enable() return FALSE due to 3RD AP \n"));
        return FALSE;
    }
*/
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    DBG_INFO(("%s:%d,_is_tts_item_enable,retail_mode:%d\r\n",__FILE__,__LINE__,t_retail_mode));
    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        return FALSE;
    }
    return TRUE;
#else
    return FALSE;
#endif
}

// Spec 3.1:
// Support V-Gaming:
//      2020 V5, M6
//      2021 D FHD, V5, V6, M6
//
// Support ProGaming:
//      2020 M7/M8, P9/PX, POLED
//      2021 M7, P9, PX
//
// Not support:
//      2021 D HD

BOOL a_acfg_is_support_v_gaming_engine(VOID)
{
    CHAR   s_name[32] = {0};
    INT32  i4_ret  = 0;
    BOOL   is_support = FALSE;

    i4_ret = a_cfg_custom_get_model_name(s_name);
    ACFG_LOG_ON_FAIL(i4_ret);

    BOOL bIsAfter2021_J_Model = a_cfg_cust_Is_CurModel_after_2021_J();

    BOOL bIsOLEDModel = FALSE; //  : OLED Panel
    if( c_strstr(s_name,"OLED") != NULL )
    {
        bIsOLEDModel =  TRUE;
    }

    if(bIsAfter2021_J_Model)
    {
        switch(s_name[0])
        {
            case 'D':
                //2k21 5583 D series FHD support V-gaming
                if( s_name[3] == 'f' )
                {
                    is_support =  TRUE;
                }
                break;

            case 'V': // 2021 v5 & v6 support V-gaming
                {
                    is_support =  TRUE;
                }
                break;

            case 'M':
                if( s_name[4] == '6') // 2021 M6 support V-gaming
                {
                    is_support =  TRUE;
                }
                break;

            default:
                break;
        }
    }
    else //2020
    {
        if ( bIsOLEDModel ) //2020 OLED model (POLED support Progaming)
        {
            is_support =  FALSE;
        }
        else
        {
            switch(s_name[0])
            {
                case 'V': // 2020 v5 support V-gaming
                    {
                        is_support =  TRUE;
                    }
                    break;

                case 'M':
                    if( s_name[3] == '6' ) // 2020 M6 support V-gaming
                    {
                        is_support =  TRUE;
                    }

                default:
                    break;
            }
        }
    }


    return  is_support;
}

// Spec 3.1:
// Support V-Gaming:
//      2020 V5, M6
//      2021 D FHD, V5, V6, M6
//
// Support ProGaming:
//      2020 M7/M8, P9/PX, POLED
//      2021 M7, P9, PX
//
// Not support:
//      2021 D HD

BOOL a_acfg_is_support_pro_gaming_engine(VOID)
{
    CHAR   s_name[32] = {0};
    INT32  i4_ret  = 0;
    BOOL   is_support = FALSE;

    i4_ret = a_cfg_custom_get_model_name(s_name);
    ACFG_LOG_ON_FAIL(i4_ret);


    BOOL bIsAfter2021_J_Model = a_cfg_cust_Is_CurModel_after_2021_J();

    BOOL bIsOLEDModel = FALSE; //  : OLED Panel
    if( c_strstr(s_name,"OLED") != NULL )
    {
        bIsOLEDModel =  TRUE;
    }

    if(bIsAfter2021_J_Model) // After 2021
    {
        switch(s_name[0])
        {
            case 'M':
                if( s_name[4] == '7'||s_name[4] == 'X')
                {
                    is_support =  TRUE;
                }
                break;

            case 'P': // 2021 P9,PX support proGaming
                {
                    is_support =  TRUE;
                }
                break;

            default:
                break;
        }
    }
    else //2020
    {
        if ( bIsOLEDModel ) //2020 OLED model (POLED support Progaming)
        {
            is_support =  TRUE;
        }
        else
        {
            switch(s_name[0])
            {
                case 'M':
                    if( s_name[4] == '7' || s_name[4] == '8')
                    {
                        is_support =  TRUE;
                    }
                    break;

                case 'P': // 2020 P9,PX,POLED support Progaming
                    {
                        is_support =  TRUE;
                    }
                    break;

                default:
                    break;
            }
        }
    }

    return  is_support;
}

/*-----------------------------------------------------------------------------
 * Name: a_acfg_update_gaming_logo
 * Description: Base on Game Low Latency option & ALLM flag to update banner logo
 * Inputs: NULL
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
void a_acfg_update_gaming_logo(void)
{
    DBG_LOG_PRINT(("[ACFG][GAME][GLL][LOGO]{%s,%d} b_is_factory_auto_test = %d\n", __FUNCTION__,__LINE__,b_is_factory_auto_test));
    if(b_is_factory_auto_test)
    {
        DBG_LOG_PRINT(("[ACFG][GAME][GLL][LOGO]{%s,%d} factory auto test case, should not update gaming logo!!!\n", __FUNCTION__,__LINE__));
        return;
    }
    BANNER_SIDERBAR_LOGO e_logo_type = (a_acfg_is_support_v_gaming_engine() ? BANNER_LOGO_V_GAMING_ENGINE : (a_acfg_is_support_pro_gaming_engine() ? BANNER_LOGO_PROGAMING_ENGINE : BANNER_LOGO_EX_COUNT));

    ACFG_DEBUG_LOG(ACFG_DBG_ALLM,
        DBG_LOG_PRINT(("[ACFG][GAME][LOGO]{%s:%d} e_logo_type [%d]\n", __FUNCTION__, __LINE__, e_logo_type)); );


    if( a_cfg_cust_is_support_game_low_latency() == FALSE )
    {
        ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][GLL][LOGO]{%s,%d} Not support GLL => Hide Gaming_LOGO\n", __FUNCTION__,__LINE__)); );
        banner_hide_siderbar_logo(e_logo_type);
        return ;
    }

  #if( VZO_DV__GLL_CONTROL_BY_DV_GAME )
    if( a_cfg_get_hdr_type() == SCC_VID_PQ_DOVI )
    {
        if( APP_CFG_VID_GAME_MODE_OFF == a_cfg_cust_get_cur_dv_game_mode_flag() )
        {
            ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][DV][GAME][GLL][LOGO]{%s, %d} DV(non-Game) => Hide Gaming_LOGO\n", __FUNCTION__,__LINE__)); );
            banner_hide_siderbar_logo(e_logo_type);
        }
        else // DV Game
        {
            DBG_LOG_PRINT(("[ACFG][DV][GAME][GLL][LOGO]{%s, %d} DV(Game) => Show Gaming_LOGO\n", __FUNCTION__,__LINE__));

            //delay it for not overlop
            a_banner_custom_update_logo_for_gll(e_logo_type,500);
        }
        return ;
    }
  #endif


    INT32  i4_ret  = 0;
    INT16 i2_User_GameLowLatency = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i2_User_GameLowLatency);
    ACFG_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_LOG(ACFG_DBG_ALLM,
        DBG_LOG_PRINT(("[ACFG][GAME][GLL][LOGO]{%s,%d} i2_User_GameLowLatency:%d\n", __FUNCTION__, __LINE__, i2_User_GameLowLatency )); );

    if ( ACFG_CUST_GAME_LOW_LATENCY_AUTO == i2_User_GameLowLatency)
    {
        if( a_cfg_cust_drv_get_allm_status() == TRUE)
        {
            ACFG_DEBUG_LOG(ACFG_DBG_ALLM, DBG_LOG_PRINT(("[ACFG][GAME] %s:%d, SHOW LOGO, a_cfg_cust_drv_get_allm_status = TRUE, e_logo_type [%d]\n", __FUNCTION__, __LINE__, e_logo_type)););
            //delay it for not overlop
            a_banner_custom_update_logo_for_gll(e_logo_type,500);
        }
        else
        {
            ACFG_DEBUG_LOG(ACFG_DBG_ALLM, DBG_LOG_PRINT(("[ACFG][GAME] %s:%d, HIDE LOGO, a_cfg_cust_drv_get_allm_status = FLASE, e_logo_type [%d]\n", __FUNCTION__, __LINE__, e_logo_type)););
            banner_hide_siderbar_logo(e_logo_type);
        }
    }
    else if (ACFG_CUST_GAME_LOW_LATENCY_ON == i2_User_GameLowLatency)
    {
        ACFG_DEBUG_LOG(ACFG_DBG_ALLM, DBG_LOG_PRINT(("[ACFG][GAME] %s:%d, SHOW LOGO, ACFG_CUST_GAME_LOW_LATENCY_ON, e_logo_type [%d]\n", __FUNCTION__, __LINE__, e_logo_type)););
        //delay it for not overlop
        a_banner_custom_update_logo_for_gll(e_logo_type,500);
    }
    else // ACFG_CUST_GAME_LOW_LATENCY_OFF == i2_User_GameLowLatency
    {
        ACFG_DEBUG_LOG(ACFG_DBG_ALLM, DBG_LOG_PRINT(("[ACFG][GAME] %s:%d, HIDE LOGO, ACFG_CUST_GAME_LOW_LATENCY_OFF, e_logo_type [%d]\n", __FUNCTION__, __LINE__, e_logo_type)););
        banner_hide_siderbar_logo(e_logo_type);
    }

}

UINT8 acfg_cust_get_CurSrcHdmi_UI_Idx(void)
{
    UINT8 u8PortIdx = 0xFF;
    INT32  i4_ret = 0;

    ISL_REC_T  t_isl_rec = {0};
    i4_ret = acfg_cust_get_crnt_isl(&t_isl_rec);
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("\n[ACFG][HDMI]{%s:%d} Error: acfg_cust_get_crnt_isl() fail! i4_ret:%d\n", __FUNCTION__, __LINE__, i4_ret));
        return u8PortIdx;
    }

    // Only HDMI support ...
    if( (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
      ||(t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI)
      )
    {
        u8PortIdx = t_isl_rec.ui1_internal_id;
        //DBG_LOG_PRINT(("[ACFG][HDMI]{%s:%d} Cur HDMI u8PortIdx => %d\n", __FUNCTION__, __LINE__, u8PortIdx ));
        return u8PortIdx;
    }

    // Other not HDMI source ==> return -1
    //DBG_LOG_PRINT(("[ACFG][HDMI]{%s:%d} ==> FALSE\n", __FUNCTION__, __LINE__ ));

    return u8PortIdx;
}

void _acfg_cust_evt_handle_VrrFreeSync(UINT8 u8VrrFreeSyncStatus)
{
    static UINT8 _au8VrrFreeSyncStatus_Last[HDMI_PORT_NUM_MAX] = {0};

    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]_acfg_cust_evt_handle_VrrFreeSync(%d) ========== start \n", u8VrrFreeSyncStatus));


    if( u8VrrFreeSyncStatus >= ACFG_VRR_STATUS_UNKNOWN )
    {
        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s,%d} Error: Invalid u8VrrFreeSyncStatus:%d !!!! Force to FreeSync(2)\n",__FUNCTION__,__LINE__, u8VrrFreeSyncStatus));
        u8VrrFreeSyncStatus = ACFG_VRR_STATUS_FREE_SYNC;
    }

#if( ACFG_CUST_VRR_INPUT_DO_FREESYNC_JOB )
    if( u8VrrFreeSyncStatus == ACFG_VRR_STATUS_VRR )
    {
        u8VrrFreeSyncStatus = ACFG_VRR_STATUS_FREE_SYNC;
        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} Force cur-u8VrrFreeSyncStatus from VRR to FreeSync \n", __FUNCTION__, __LINE__ ));
    }
#endif

    g_ACFG_eCurVrrFreeSyncStatus = (EnuAcfgVrrStatus)u8VrrFreeSyncStatus;
    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} Set g_ACFG_eCurVrrFreeSyncStatus=%d \n", __FUNCTION__, __LINE__, g_ACFG_eCurVrrFreeSyncStatus ));


    UINT8 u8CurHdmi_UI_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();
    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} u8CurHdmi_UI_Idx:%d \n", __FUNCTION__, __LINE__, u8CurHdmi_UI_Idx ));

    // If not HDMI, do nothing
    if( u8CurHdmi_UI_Idx >= HDMI_PORT_NUM_MAX )
    {
        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s,%d} Error: Invalid u8CurHdmi_UI_Idx:%d !!!!\n",
            __FUNCTION__,__LINE__, u8CurHdmi_UI_Idx));
        a_acfg_cust_reset_VRR_FreeSync_status();
        return;
    }

    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} _au8VrrFreeSyncStatus_Last[%d]:%d, cur-u8VrrFreeSyncStatus:%d \n", __FUNCTION__, __LINE__,
        u8CurHdmi_UI_Idx, _au8VrrFreeSyncStatus_Last[u8CurHdmi_UI_Idx], u8VrrFreeSyncStatus));

    if( u8VrrFreeSyncStatus == _au8VrrFreeSyncStatus_Last[u8CurHdmi_UI_Idx] )
    {
        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] Status no changed~\n" ));
        return ;
    }

    // Recovery for pre VRR/FreeSync
    if(_au8VrrFreeSyncStatus_Last[u8CurHdmi_UI_Idx] == 1) // PreStatus is VRR
    {
        _cfg_hdmi_detect_vrr_stream_nfy_fct(0);
    }
    else if(_au8VrrFreeSyncStatus_Last[u8CurHdmi_UI_Idx] == 2) // PreStatus is FreeSync
    {
        _cfg_hdmi_detect_freesync_flag_nfy_fct(0);
    }

    // Change to VRR/FreeSync
    if( u8VrrFreeSyncStatus == 1 ) // ?? => VRR
    {
        // If Vrr not on, turn on
        _cfg_hdmi_detect_vrr_stream_nfy_fct(1);
    }
    else if( u8VrrFreeSyncStatus == 2 ) // ?? => FreeSync
    {
        // If freeSync not on, turn on
        _cfg_hdmi_detect_freesync_flag_nfy_fct(1);
    }

    _au8VrrFreeSyncStatus_Last[u8CurHdmi_UI_Idx] = u8VrrFreeSyncStatus;

    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} Set _au8VrrFreeSyncStatus_Last[%d]=%d \n", __FUNCTION__, __LINE__,
        u8CurHdmi_UI_Idx, _au8VrrFreeSyncStatus_Last[u8CurHdmi_UI_Idx] ));

}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_chg_timing(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    INT32       i4_ret;

    CHAR        s_curr_disp_name[ACFG_MAX_DISP_NAME+1];
    CHAR*       s_target_disp_name = (CHAR*)pv_data;
    VSH_SRC_RESOLUTION_INFO_T   t_timing;
    ISL_REC_T   t_isl_rec;

#ifdef APP_MENU_3D_BRIGHTNESS_BOOST
    UINT16  ui2_idx = 0;
#endif

    BOOL bIsSrcVGA = FALSE;

    ACFG_DBG_PRINT(" Enter : \r\n");

    DBG_LOG_PRINT(("[MSG][ACFG][chg_timing] {%s: %d} e_update_reason=%d\n", __FUNCTION__, __LINE__, e_update_reason));

#ifdef NEVER
    SCC_VID_HDR_TYPE_T t_hdr_type = SCC_VID_PQ_SDR;

    i4_ret = c_scc_vid_get_hdr_type(h_g_acfg_scc_main_vid,
                                     &t_hdr_type);
    ACFG_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("[ACFG] t_hdr_type :%d,%s,%d\r\n",t_hdr_type,__FUNCTION__,__LINE__));
    a_cfg_set_hdr_type(t_hdr_type);
#endif /* NEVER */


    c_memset( &t_timing, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T) );
    c_memset( &t_isl_rec, 0, sizeof(t_isl_rec) );


    a_cfg_av_get_disp_name(s_curr_disp_name, sizeof(s_curr_disp_name));

    a_cfg_av_set_disp_name(s_target_disp_name);

    a_cfg_av_get_timing(s_target_disp_name, &t_timing);


    DBG_LOG_PRINT(("[ACFG][chg_timing][ALLM][VRR][GAME]{%s,%d} ui1_allm_config:%d, u1_vrr_en:%d \n",
        __FUNCTION__,__LINE__, t_timing.ui1_allm_config, t_timing.u1_vrr_en));

    DBG_LOG_PRINT(("[ACFG][chg_timing][DV][GAME]{%s: %d} Last ACFG_MSG_SCC_EVNT: ui4_dolby_cond:%d, game:%d\n",
        __FUNCTION__,__LINE__, acfg_get_dolby_value(), acfg_get_game_value() ));

#if 1 // Check allm/vrr status by calling driver directly
    {
        DBG_LOG_PRINT(("[ACFG][chg_timing][GAME][ALLM] {%s: %d} BSP_allm_Status:%d \n",
            __FUNCTION__,__LINE__, a_cfg_cust_drv_get_allm_status() ));
        DBG_LOG_PRINT(("[ACFG][chg_timing][GAME][VRR] {%s: %d} BSP_vrr_Status:%d \n",
            __FUNCTION__,__LINE__, a_cfg_cust_drv_get_vrr_status() ));
    }
#endif


#if( ENABLE_ACFG_HDMI_TASK )
    acfg_cust_HDMI_task_stop();
#endif
#if( ENABLE_VIZIO_AUTO_PC)
    acfg_cust_AutoPc_stop();
#endif


    /*--------------BEGIN--------------*/
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_FULL_COLOR_444));
    ACFG_LOG_ON_FAIL(i4_ret);

    a_tv_get_crnt_isl_rec(s_target_disp_name, &t_isl_rec);

    // Print input source ...
    DBG_LOG_PRINT(("[ACFG][chg_timing][SRC] e_src_type:%d, e_video_type: 0x%X\n", t_isl_rec.e_src_type, t_isl_rec.t_avc_info.e_video_type ));

    // Print timing ...
    DBG_LOG_PRINT(("[ACFG][chg_timing][timing] width: %d, high: %d, freq: %d\n", t_timing.ui4_width, t_timing.ui4_height, t_timing.ui4_frame_rate ));



    /* HDMI */
    BOOL bIsSrcHDMI = FALSE;
    BOOL bIsSrcDVI = FALSE;
    if( (t_isl_rec.e_src_type == INP_SRC_TYPE_AV) )
    {
        if( t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI ) // HDMI
        {
            bIsSrcHDMI = TRUE;
            // Get HDMI color format ...
            ACFG_CUST_HDMI_COLOR_FORMAT_T eHdmiColorForamt = acfg_cust_video_get_hdmi_color_space();
            DBG_LOG_PRINT(("[ACFG][chg_timing] Src is HDMI, hdmi_color => %d(%s) \n",
                eHdmiColorForamt, acfg_cust_video_get_hdmi_color_space_string(eHdmiColorForamt) ));
        }
        else if( t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI) // DVI
        {
            bIsSrcDVI = TRUE;
            DBG_LOG_PRINT(("[ACFG][chg_timing] Src is DVI\n" ));
        }

        // Check HDMI/DVI ...
        SCC_VID_HDMI_DVI_MODE_T eSCC_VID_HDMI_DVI_MODE = a_cfg_custom_get_hdmi_dvi_signal();
        char* pcStr_SCC_VID_HDMI_DVI_MODE = "NO_SIGNAL";

        switch(eSCC_VID_HDMI_DVI_MODE)
        {
            case SCC_VID_HDMI_DVI_MODE_DVI:
                pcStr_SCC_VID_HDMI_DVI_MODE = "DVI";
                break;
            case SCC_VID_HDMI_DVI_MODE_HDMI:
                pcStr_SCC_VID_HDMI_DVI_MODE = "HDMI";
                break;
            default:
                pcStr_SCC_VID_HDMI_DVI_MODE = "NO_SIGNAL";
                break;
        }
        
        acfg_signal_loss_count_increase();

        DBG_LOG_PRINT(("[ACFG][chg_timing][PC]{%s,%d} eSCC_VID_HDMI_DVI_MODE:%d(%s)\n", __FUNCTION__,__LINE__, eSCC_VID_HDMI_DVI_MODE, pcStr_SCC_VID_HDMI_DVI_MODE));

    }


    BOOL bIs_support_game_low_latency = a_cfg_cust_is_support_game_low_latency();
    DBG_LOG_PRINT(("[ACFG][chg_timing][GAME] %s: %d: bIs_support_game_low_latency=%d\n", __FUNCTION__,__LINE__, bIs_support_game_low_latency));


    //if (a_cfg_cust_is_support_game_low_latency())
    if( bIs_support_game_low_latency )
    {
        a_acfg_update_gaming_logo();
    }

    //process VRR and FreeSync notify
    if( bIsSrcHDMI )
    {
        _acfg_cust_evt_handle_VrrFreeSync(t_timing.u1_vrr_en);
    }
    else
    {
        a_acfg_cust_reset_VRR_FreeSync_status();
    }


    /* check if it is a valid timing */
    if(t_timing.ui4_width != 0  &&
       t_timing.ui4_height != 0 &&
       t_timing.ui4_frame_rate != 0)
    {
        #if 0 /*used to update picture mode after 3rd app exited, don't need anymore*/
        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
        ACFG_LOG_ON_FAIL(i4_ret);
        #endif

        /* YPbPr */
        if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV          &&  /* chech if it is a ypbpr input */
           t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR)
        {
            if(!a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
            {
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_YPBPR_PHASE));
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        }

        /* VGA */
        if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV          &&  /* chech if it is a vga input */
           t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
        {
            bIsSrcVGA = TRUE;
            DBG_LOG_PRINT(("[ACFG][chg_timing] Src is VGA\n" ));
            if(!a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
            {
                BOOL b_auto_done = FALSE;

                a_cfg_vga_is_auto_done(&b_auto_done);

                if(b_auto_done)
                {
                    DBG_INFO(("<ACFG>Auto Done!!!\n"));

                    i4_ret = acfg_cust_video_pos_reset(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V));
                    ACFG_LOG_ON_FAIL(i4_ret);
                    i4_ret = acfg_cust_video_pos_reset(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H));
                    ACFG_LOG_ON_FAIL(i4_ret);

                    /* Update user settings to driver */
                    a_cfg_vga_update_clk_phs_pos();
                }
                else
                {
                    DBG_INFO(("<ACFG>Not auto Done!!!\n"));

                    /* auto auto */
                    i4_ret = a_cfg_vga_auto_clk_phs_pos();
                    ACFG_LOG_ON_FAIL(i4_ret);
                }
            }
        }

        #if 0  /*Update picture mode too many times, video flash*/
        /* HDMI */
        if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV          &&
           t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
        {
            if(!a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
            {
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
                ACFG_LOG_ON_FAIL(i4_ret);

            }
        }
        #endif

        /* Video H/V pos. */
        if( !(t_isl_rec.e_src_type == INP_SRC_TYPE_AV && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA))
        {
            if(!a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
            {
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H));
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V));
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        }
         /* Overscan
        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
        ACFG_LOG_ON_FAIL(i4_ret);*/

#if 0 //def APP_3D_MODE_SUPPORT
        {
            if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
            {
                if (VSH_SRC_TAG3D_2D            != t_timing.e_src_tag3d_type &&
                    VSH_SRC_TAG3D_NOT_SUPPORT   != t_timing.e_src_tag3d_type &&
                    VSH_SRC_TAG3D_TTDO          != t_timing.e_src_tag3d_type)
                    {
                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE), (INT16)APP_CFG_3D_MODE_AUTO);
                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D), (INT16 )APP_CFG_3D_TO_2D_OFF);

                        DBG_LOG_PRINT(("[3D] change 3D mode APP_CFG_3D_MODE_AUTO. FUNC:%s --- LINE:%d ---\n",__FUNCTION__,__LINE__));
                    }
            }

            a_cfg_set_3d_display (a_tv_custom_is_3D_mode_playing ());
            //a_cfg_update_viewport ();

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));
            ACFG_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));
            ACFG_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_3D_BRIGHTNESS_BOOST
            if(a_tv_custom_is_3D_mode_playing ())
            {

                //c_dbg_stmt("\n========_acfg_cust_evt_handle_chg_timing======%d\n",__LINE__);
                a_cfg_custom_get_3d_brightness_boost(&ui2_idx);
                if(ui2_idx)
                {
                    //c_dbg_stmt("\n========_acfg_cust_evt_handle_chg_timing======%d\n",__LINE__);
                    a_cfg_custom_3d_brightness_boost(TRUE);
                }
            }
            else
            {
                //c_dbg_stmt("\n========_acfg_cust_evt_handle_chg_timing======%d\n",__LINE__);
                a_cfg_custom_3d_brightness_boost(FALSE);
            }
#endif
        }
#endif
#ifdef NEVER
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
#endif /* NEVER */

        if (a_cfg_custom_chk_freqence_120hz())
        {
        #if (VIEWPORT_SUPPORT == 1)
            a_cfg_custom_set_view_mode_idx(APP_CFG_VIEWPORT_TYPE_OVERLAY);
        #endif
        }

        /* Screen Mode */
#ifdef APP_HDR_SUPPORT
        /* UI SPEC3.5 Normal is the only available WIDE setting for HLG content.*/
        do {
            UINT8   ui1_type = a_acfg_cust_get_video_type();
            if ( ui1_type != SCC_VID_PQ_SDR )
            {
                DBG_ERROR(("<ACFG> :%s:%d: set SCC_VID_SCREEN_MODE_NORMAL !!!\r\n", __FILE__, __LINE__));
                i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), SCC_VID_SCREEN_MODE_NORMAL);
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        } while(0);
#endif
        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));
        ACFG_LOG_ON_FAIL(i4_ret);

        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));
    }
    else
    {
        // Timing invalid ...
        DBG_LOG_PRINT(("[ACFG][chg_timing][timing] Invalid timing!!!\n" ));

        // Print timing ...
        DBG_LOG_PRINT(("[ACFG][chg_timing][timing] width: %d, high: %d, freq: %d\n", t_timing.ui4_width, t_timing.ui4_height, t_timing.ui4_frame_rate ));

        a_cfg_set_3d_display (FALSE);

    #ifdef APP_MENU_3D_BRIGHTNESS_BOOST
        //c_dbg_stmt("\n========_acfg_cust_evt_handle_chg_timing======%d\n",__LINE__);
        a_cfg_custom_3d_brightness_boost(FALSE);
    #endif
    }

    /*--------------END--------------*/
    a_cfg_av_set_disp_name(s_curr_disp_name);
    _acfg_cust_scr_mode_change();

    // HDR type ...
    UINT8 u8VideoType = a_acfg_cust_get_video_type();
    DBG_LOG_PRINT(("[ACFG][chg_timing][HDR] u8VideoType:%d\n", u8VideoType ));

    if( u8VideoType == SCC_VID_PQ_SDR) //for hdr case will update by _acfg_cust_evt_handle_hdr_change
    {
        TV_WIN_ID_T  e_tv_win_id;
        INT32 i4_ret;
        static ISL_REC_T    t_isl_rec_last           = {0};
        ISL_REC_T    t_isl_rec_cur                   = {0};

        nav_get_focus_id(&e_tv_win_id);
        i4_ret = nav_get_isl_rec (e_tv_win_id, &t_isl_rec_cur);
        if( i4_ret == NAVR_OK )
        {
            if( a_nav_ipts_is_tv_source(&t_isl_rec_cur) )
            {
                //just update TV av when first change to TV,not always,otherwise change channel too much would hung up in update av
                if((t_isl_rec_cur.e_src_type != t_isl_rec_last.e_src_type))
                {
                    DBG_LOG_PRINT(("[ACFG]%s,%d, delay update av\n",__FUNCTION__,__LINE__));
                    _cfg_tv_soure_av_update_delay();
                }
            }
            else
            {
                ACFG_LOG_ON_FAIL(a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE)));
            }

            memcpy(&t_isl_rec_last,&t_isl_rec_cur,sizeof(ISL_REC_T));
        }

    }

    a_cfg_custom_set_ipcc_idx(NULL);

    //Start SPD info handler ...
    if( bIsSrcHDMI || bIsSrcDVI )
    {
        acfg_cust_SPD_Info_handler();
    }

#if( ENABLE_VIZIO_AUTO_PC )
    // Start Auto_PC job ...
    if(( bIsSrcDVI || bIsSrcHDMI ) &&
       (acfg_cust_is_Vrr_or_FreeSync_detected() == FALSE) &&
       (a_cfg_cust_get_cur_dv_game_mode_flag() == APP_CFG_VID_GAME_MODE_OFF)&&
       (b_is_detected_spd_info == FALSE))
    {
        acfg_cust_AutoPc_start();
    }
    else
    {
        acfg_cust_AutoPc_stop();
    }
#endif


#if( ENABLE_ACFG_HDMI_TASK )
    // Start HDMI task ...
    if( bIsSrcHDMI )
    {
        acfg_cust_HDMI_task_start();
    }
    else
    {
        acfg_cust_HDMI_task_stop();
    }
#endif

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_vga_auto_tune(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    INT32       i4_ret;
    CHAR        s_curr_disp_name[ACFG_MAX_DISP_NAME+1];
    CHAR*       s_target_disp_name = (CHAR*)pv_data;
    ISL_REC_T   t_isl_rec;

    a_cfg_av_get_disp_name(s_curr_disp_name,
                           sizeof(s_curr_disp_name));

    a_cfg_av_set_disp_name(s_target_disp_name);

    /*--------------BEGIN--------------*/
    /* VGA */
    a_tv_get_crnt_isl_rec(s_target_disp_name, &t_isl_rec);
    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
    {
        if(!a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
        {
            i4_ret = a_cfg_vga_sync_clk_phs_pos();
            ACFG_LOG_ON_FAIL(i4_ret);
            if (e_update_reason == ACFG_UPDATE_REASON_VGA_AUTO_DONE)
            {
                i4_ret = a_cfg_vga_set_auto_done(TRUE);
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        }
    }
    /*--------------END--------------*/

    a_cfg_av_set_disp_name(s_curr_disp_name);

    return APP_CFGR_OK;
}

#if 0
static VOID _acfg_show_notify_for_use_digit_pad(
                                    VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3)
{

    UINT16          ui2_rec_num=0;
    ui2_rec_num = ocl_get_ocl_num();
    if (ui2_rec_num <= 0) return;
    WDK_TOAST_T    t_toast          = {0};
    c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;
    t_toast.style.style_4.w2s_str = (VOID*)MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_USE_DIGIT_PAD_FOR_CHANNEL);
    menu_send_string_to_nav_toast(&t_toast);
}
#endif

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_chg_input(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    INT32       i4_ret;
    CHAR        s_curr_disp_name[ACFG_MAX_DISP_NAME+1];
    CHAR*       s_target_disp_name = (CHAR*)pv_data;
    BOOL        b_flag = FALSE;


    DBG_LOG_PRINT(("[MSG][ACFG][CHG_INPUT] %s(e_update_reason:%d, %s) \n", __FUNCTION__, e_update_reason,
        ( (s_target_disp_name)?(s_target_disp_name):("NULL")) ));


    extern VOID menu_page_input_async_action(VOID* pv_data, SIZE_T z_data_size);
    menu_async_invoke(menu_page_input_async_action, &b_flag, sizeof(BOOL), TRUE);

    a_cfg_av_get_disp_name(s_curr_disp_name, sizeof(s_curr_disp_name));
    DBG_LOG_PRINT(("[ACFG][CHG_INPUT] s_curr_disp_name:{%s}\n", s_curr_disp_name));

    DBG_LOG_PRINT(("[ACFG][CHG_INPUT] Set acfg_disp_name={%s}\n", s_target_disp_name));
    a_cfg_av_set_disp_name(s_target_disp_name);


    ISL_REC_T   t_isl_rec = {0};
    a_tv_get_crnt_isl_rec(s_target_disp_name, &t_isl_rec);

    DBG_LOG_PRINT(("[ACFG][CHG_INPUT] ui1_id:%d, ui1_internal_id:%d, e_src_type:%d\n",
        t_isl_rec.ui1_id, t_isl_rec.ui1_internal_id, t_isl_rec.e_src_type));

    DBG_LOG_PRINT(("[ACFG][CHG_INPUT] e_src_type:0x%X\n", t_isl_rec.t_avc_info.e_video_type));


    /*--------------BEGIN--------------*/
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_FULL_COLOR_444));
    ACFG_LOG_ON_FAIL(i4_ret);

    /* Video */
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);


    DBG_LOG_PRINT(("[ACFG][CHG_INPUT] Set acfg_disp_name={%s}\n", s_curr_disp_name));
    a_cfg_av_set_disp_name(s_curr_disp_name);


    _acfg_cust_scr_mode_change();

    //when the source is virtual,set the position default
    if(t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL)
    {
        //DBG_LOG_PRINT(("\n%s t_isl_rec.e_src_type:%d\n",__FUNCTION__,t_isl_rec.e_src_type));
        i4_ret = acfg_cust_video_pos_reset(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V));
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_cust_video_pos_reset(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H));
        ACFG_LOG_ON_FAIL(i4_ret);
    }

    if (INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
    {
        // hide digit for mp
        // menu_request_context_switch(_acfg_show_notify_for_use_digit_pad,NULL,NULL,NULL);
        a_ch_select_view_notification();
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_pre_chg_input(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    INT32       i4_ret = 0;
    CHAR*       s_target_disp_name = (CHAR*)pv_data;
    INT16       i2_val = 0;


    DBG_LOG_PRINT(("[MSG][ACFG][PRE_CHG_INPUT] %s( e_update_reason:%d, %s)\n", __FUNCTION__, e_update_reason,
                        ( (s_target_disp_name)?(s_target_disp_name):("NULL")) ));



    CHAR  s_curr_disp_name[ACFG_MAX_DISP_NAME+1] = {0};

    a_cfg_av_get_disp_name(s_curr_disp_name, sizeof(s_curr_disp_name));
    DBG_LOG_PRINT(("[ACFG][PRE_CHG_INPUT] s_curr_disp_name:{%s}\n", s_curr_disp_name));

    DBG_LOG_PRINT(("[ACFG][PRE_CHG_INPUT] Set acfg_disp_name={%s}\n", s_target_disp_name));
    a_cfg_av_set_disp_name(s_target_disp_name);


    ISL_REC_T   t_isl_rec = {0};
    a_tv_get_crnt_isl_rec(s_target_disp_name, &t_isl_rec);

    DBG_LOG_PRINT(("[ACFG][PRE_CHG_INPUT] ui1_id:%d, ui1_internal_id:%d, e_src_type:%d\n",
        t_isl_rec.ui1_id, t_isl_rec.ui1_internal_id, t_isl_rec.e_src_type));

    DBG_LOG_PRINT(("[ACFG][PRE_CHG_INPUT] e_video_type:0x%X\n", t_isl_rec.t_avc_info.e_video_type));


#ifdef TVIS_SUPPORT
    {
        CHAR  s_cmd[128] = {0};
        CHAR  s_isl_input_src_name[128] = {0};

        c_uc_w2s_to_ps(a_isl_get_display_name(&t_isl_rec), s_isl_input_src_name, 128);
        DBG_LOG_PRINT(("[ACFG][PRE_CHG_INPUT] s_isl_input_src_name={%s}\n", s_isl_input_src_name));

        c_sprintf(s_cmd, "echo %s > /tmp/input", s_isl_input_src_name);
        AP_SYSTEM_CALL(s_cmd);
    }
#endif


    /*--------------BEGIN--------------*/
    /* Video */
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
    ACFG_LOG_ON_FAIL(i4_ret);
    /* Audio */
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));
    ACFG_LOG_ON_FAIL(i4_ret);


    /*update lip sync*/
    i4_ret = a_cfg_get_lip_sync(&i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY), i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /*update srs sorround hd*/
    i4_ret = a_cfg_get_srs_sorround_hd(&i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_SURROUND), i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_SURROUND));
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    a_cfg_set_hdr_type(SCC_VID_PQ_SDR);


    /*--------------END--------------*/
    DBG_LOG_PRINT(("[ACFG][PRE_CHG_INPUT] Set acfg_disp_name={%s}\n", s_curr_disp_name));
    a_cfg_av_set_disp_name(s_curr_disp_name);

    /*change input source, should reset 3D MODE */
    a_cfg_custom_3D_setting_reset_3D_mode();

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _acfg_cust_update_ir_mode
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_update_ir_mode(VOID)
{
    if (a_cfg_custom_get_wifi_remote_support())
    {
        UINT8       ui1_status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;
        ISL_REC_T   t_isl_rec = {0};
        CHAR        s_type_name[32]   = {0};
        CHAR        s_brand_name[32]  = {0};
        CHAR        s_model_name[32]  = {0};
        CHAR        s_codeset[6]      = {0};
        UINT8       ui1_vol_ctrl_val  = 0;

        a_cfg_custom_get_wifi_remote_pair_status(&ui1_status);
        if (ui1_status == WIFI_REMOTE_PAIR_STATUS_PAIRED)
        {
            /* for Sound bar and AVR/Amplifer */
            a_cfg_custom_get_vol_control(&ui1_vol_ctrl_val);
            a_cfg_custom_get_device_info(0, s_type_name, s_brand_name, s_model_name, s_codeset);

            if (c_strcmp(s_codeset, "") != 0 && ui1_vol_ctrl_val > 0)
            {
                a_tv_net_custom_set_soundbar_flag(TRUE);
                a_tv_net_custom_set_soundbar_codeset(s_codeset);
            }
            else
            {
                a_tv_net_custom_set_soundbar_flag(FALSE);
            }

            /* for cable box device */
            c_memset(s_type_name, 0 , 32);
            c_memset(s_brand_name, 0 , 32);
            c_memset(s_model_name, 0 , 32);
            c_memset(s_codeset, 0 , 6);

            a_tv_get_crnt_isl_rec(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
            a_cfg_custom_get_device_info(t_isl_rec.ui1_id, s_type_name, s_brand_name, s_model_name, s_codeset);

            if (c_strcmp(s_codeset, "") != 0)
            {
                /* set codeset */
                a_tv_net_custom_set_codeset(s_codeset);
            }
            else
            {
                a_tv_net_send_cmd("\n:am,am,:codeset=C0105\n");
                a_tv_net_custom_set_ir_mode(IR_MODE_TV);
                return APP_CFGR_OK;
            }

            /* update ir mode */
            if (a_cfg_get_app_status () != APP_CFG_APP_STATUS_LAST_ENTRY)
            {
                /* _tv_custom_icl_app_status_cb deal with this situation */
                DBG_INFO(("[IR] --- MENU or 3rd APP in FUNC: %s.\n", __FUNCTION__));
                return APP_CFGR_OK;;
            }

            if (a_tv_net_custom_get_OSD_status() == 0)
            {
                DBG_INFO(("[IR] --- update ir mode in FUNC: %s.\n", __FUNCTION__));
                a_tv_net_custom_update_ir_mode();
            }
            else
            {
                DBG_INFO(("[IR] --- set ir mode force to TV mode in FUNC: %s.\n", __FUNCTION__));
                a_tv_net_custom_set_ir_mode(IR_MODE_TV);
            }
        }
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_select_service(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    DBG_INFO(("[IR] --- update IR mode in FUNC: %s.\n", __FUNCTION__));
    _acfg_cust_update_ir_mode();

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _acfg_cust_evt_handle_chg_aud_fmt
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_chg_aud_fmt(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    ASH_AUDIO_INFO_T    t_audio_info;
    INT32               i4_ret = 0;
    UINT8               ui1_val = RECID_CUSTOM_DTS_STATUS_OFF;
    SIZE_T              z_size = ICL_RECID_CUSTOM_AUD_FMT_DTS_FLAG_SIZE;
    UINT8               ui1_dts_status = RECID_CUSTOM_DTS_STATUS_OFF;
    INT16               i2_val = 0;

    c_memset(&t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));

    i4_ret = c_svctx_get_audio_info(h_g_acfg_svctx_main, &t_audio_info);
    if(i4_ret != SVCTXR_OK)
    {
        DBG_INFO(("%s,%d [acfg dts] get audio type fail \r\n",__FUNCTION__,__LINE__));
    }

    if(t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_DTS)
    {
        ui1_val = RECID_CUSTOM_DTS_STATUS_ON;
        a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_FLAG_CHANGE, ICL_RECID_CUSTOM_AUD_FMT_DTS_FLAG),
                      (VOID*) &ui1_val,
                      z_size);

        DBG_INFO(("%s,%d [acfg dts] source is dts \r\n",__FUNCTION__,__LINE__));
    }
    else
    {
        i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CUSTOM_FLAG_CHANGE, ICL_RECID_CUSTOM_AUD_FMT_DTS_FLAG),
                       &ui1_dts_status,
                       &z_size);
        if (i4_ret != ICLR_OK)
        {
            DBG_INFO(("%s,%d [acfg dts] get dts icl fail \r\n",__FUNCTION__,__LINE__));
        }

        if(ui1_dts_status != RECID_CUSTOM_DTS_STATUS_OFF)
        {
            ui1_val = RECID_CUSTOM_DTS_STATUS_OFF;
            a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_FLAG_CHANGE, ICL_RECID_CUSTOM_AUD_FMT_DTS_FLAG),
                      (VOID*) &ui1_val,
                      z_size);

            DBG_INFO(("%s,%d [acfg dts] dts source switch to other source \r\n",__FUNCTION__,__LINE__));
        }
    }

    /* update spdif setting*/
    a_cfg_update_spdif_type();
    /*update lip sync*/
    i4_ret = a_cfg_get_lip_sync(&i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY), i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_chg_tv_mode(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
#ifdef APP_MJC_SUPPORT
    INT32       i4_ret;
    /*TV_MODE_T   e_tv_mode = (TV_MODE_T)(UINT32)pv_data;*/

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT));
    ACFG_LOG_ON_FAIL(i4_ret);
#endif /* APP_MJC_SUPPORT */

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_check_usb_devices_using_status()
{
    INT32   i4_ret= 0;
    UINT32  ui4_use_count = 0;
    UINT32  ui4_mnt_count = 0;
    UINT32  ui4_mnt_point_idx = 0;
    RMV_DEV_DEVICE_STATUS_T         t_rmv_dev_status;

    a_rmv_dev_lock();

    i4_ret = a_rmv_dev_get_mnt_count (&ui4_mnt_count);
    if (i4_ret == RMVR_OK && ui4_mnt_count > 0)
    {
        for(ui4_mnt_point_idx = 0;
            ui4_mnt_point_idx < ui4_mnt_count;
            ui4_mnt_point_idx ++)
        {
            /* Get the mount point status */
            i4_ret= a_rmv_dev_get_mnt_point_status_by_idx(ui4_mnt_point_idx, &t_rmv_dev_status);

            /* Check the mount point status */
            if ((i4_ret != RMVR_OK) ||
                (TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(t_rmv_dev_status))||
                (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(t_rmv_dev_status))||
                (TRUE == RMV_DEV_DEVICE_IS_REMOVED(t_rmv_dev_status))||
                (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(t_rmv_dev_status)))
            {
                continue;
            }
            ui4_use_count ++;
            DBG_INFO(("[%s,%d]usb idx:%d is in use\n", __func__, __LINE__, ui4_mnt_point_idx));
        }
    }

    a_rmv_dev_unlock();
    DBG_INFO(("[%s,%d]%d usb devices in use\n", __func__, __LINE__, ui4_use_count));

    return ui4_use_count;
}

static INT32 _acfg_cust_evt_handle_pre_power_off(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    UINT32  ui4_key_code = (UINT32)pv_data;
    UINT32  ui4_key_src  = IOM_GET_EVT_SRC(ui4_key_code);
    BOOL    b_is_plug = FALSE;
    UINT8   ui1_interface = 0;
    UINT32  ui4_eco = 0;
#ifdef APP_WAKE_ON_WLAN
    PCL_WIFI_WOL_CTRL_T e_wlan_wol = PCL_WIFI_WOL_DISABLE;
#endif


    DBG_LOG_PRINT(("[ACFG][POWER]{%s,%d} \n", __FUNCTION__, __LINE__  ));


    /* deal with the youtube wakeup on dial*/
#ifdef APP_WAKE_ON_DIAL_SUPPORT
      AP_SYSTEM_CALL("/basic/bin/wpa_supplicant/atheros/iwpriv ra0 set usbWOWSuspend=1");
#endif
#ifdef APP_LED_LOGO_CTRL
    DBG_ERROR(("a_cfg_custom_set_dc_qs_off_start_led.\r\n"));
    a_cfg_custom_set_dc_qs_off_start_led();
#endif

    a_cfg_custom_get_drv_eco_mode(&ui4_eco);
    DBG_INFO(("[ACFG][%s %d] current power mode = %d\n",__FUNCTION__,__LINE__,ui4_eco ));
    //a_cfg_disp_set_back_light_ctrl(FALSE);
    if(ICL_CUSTOM_POWER_MODE_QUICK_START == ui4_eco)
    {
        a_cfg_disp_set_back_light_ctrl(FALSE);
    }
#ifdef APP_C4TV_SUPPORT
    else if (ICL_CUSTOM_POWER_MODE_ECO == ui4_eco)
    {
        DBG_INFO(("Noitfy Cast shell to enter suspend mode.\r\n"));
        a_c4tv_apron_suspend_cast(NULL, C4TV_APRON_USER_SUSPEND_REASON_USERSHUTDOWN);
    }
#endif

    if (0 == ui4_eco)
    {
        //set delay time to usb driver before suspend
        if (0 == _acfg_cust_check_usb_devices_using_status())
        {
            DBG_INFO(("echo 0 > /sys/module/mtk_hcd/parameters/mgc_suspend_delay\n"));
            AP_SYSTEM_CALL("echo 0 > /sys/module/mtk_hcd/parameters/mgc_suspend_delay");
        }
        else
        {
            DBG_INFO(("echo 500 > /sys/module/mtk_hcd/parameters/mgc_suspend_delay\n"));
            AP_SYSTEM_CALL("echo 500 > /sys/module/mtk_hcd/parameters/mgc_suspend_delay");
        }

        //set wifi radio off
        //system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 radio_off");
        //DBG_ERROR(("Noitfy wlan0 to radio_off.\r\n"));
    }

    /* here will store the last interface as will to power off*/
    a_nw_get_ethernet_connect_info(&b_is_plug);
    if (b_is_plug)
    {
        ui1_interface = APP_CFG_NET_INTERFACE_ETH0;
    }
    else
    {
        ui1_interface = APP_CFG_NET_INTERFACE_WIFI;
    }
    a_cfg_custom_set_ethernet_connected_status(ui1_interface);

    /* Tell driver that app is standby.
       This code is orignally at _handle_cust_d_in_led() in bgm_power_mgmt_cust.c */
    if(ui4_key_src == KEY_SRC_FRONT_PANEL)
    {
        c_pcl_set_power_down_reason(PCL_POWER_DOWN_REASON_FP, NULL);
    }
    else
    {
        c_pcl_set_power_down_reason(PCL_POWER_DOWN_REASON_IRRC, NULL);
    }

#ifdef APP_C4TV_SUPPORT
    if(0 == ui4_eco)
    {
        // Enter ECO mode, stop softap to save power consumption.
        rest_stop_softap_ex();
    }
#endif

#ifdef APP_WAKE_ON_WLAN
    c_pcl_get_wifi_wol_ctrl(&e_wlan_wol);
    if(e_wlan_wol == PCL_WIFI_WOL_ENABLE)
    {
        DBG_INFO(("<WoWlan>set wifi dongle into wowlan mode\n"));
    #ifdef APP_WIFI_IS_MT7601U
        AP_SYSTEM_CALL("/3rd/bin/wpa_supplicant/common/iwpriv ra0 set usbWOWSuspend=1");
    #else
        #ifndef APP_C4TV_SUPPORT
        AP_SYSTEM_CALL("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set usbWOWSuspend=1");
        #else
        DBG_INFO(("<WoWlan>set wifi dongle into cast wakeup mode\n"));
        //system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set wow_enable=1");
        //system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set wow_inband=0");
        //system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set wow_tcp_port_v4=8008,8009");
        //system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set wow_udp_port_v4=5353");
        //c_thread_delay(1000 * 2);
        #endif
    #endif
    }
    //Add for debug temperary
    DBG_INFO(("===== Enable WOW ====\n"));
    AP_SYSTEM_CALL("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 driver \"SET_WOW_ENABLE 1\"");
#if 0 //mask cast wakeup
    system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 driver \"set_wow_tcp 0 5353,8080\"");
    system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 driver \"set_wow_tcp 1 8000\"");
    system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 driver \"set_wow_udp 0 5353,8080\"");
    system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 driver \"set_wow_ucp 1 8000\"");
#endif
#endif

    c_pcl_set_power_state (PCL_PWR_STATE_CTRL_STANBY);

    a_util_cnfg_set_last_channel_id(INVALID_CHANNEL_ID);

    if(a_cfg_custom_get_wifi_remote_support())
{
    UINT8   ui1_status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;

    a_cfg_custom_get_wifi_remote_pair_status(&ui1_status);
    if(ui1_status == WIFI_REMOTE_PAIR_STATUS_PAIRED)
    {
        ISL_REC_T   t_isl_rec = {0};

        a_tv_get_crnt_isl_rec(SN_PRES_MAIN_DISPLAY, &t_isl_rec);
        if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
        {
            CHAR    s_type_name[32]   = {0};
            CHAR    s_brand_name[32]  = {0};
            CHAR    s_model_name[32]  = {0};
            CHAR    s_codeset[6]      = {0};

            a_cfg_custom_get_device_info(t_isl_rec.ui1_id, s_type_name, s_brand_name, s_model_name, s_codeset);

            DBG_INFO(("\n --------- %s, %d: %s------\n", __FUNCTION__, __LINE__,s_codeset));

            if (c_strcmp(s_codeset, "") != 0)
            {
                a_cfg_custom_set_current_codeset(s_codeset);
            }
        }
        a_cfg_custom_set_soundbar_codeset();
    }
}


    /*Reset input pin code state for this power session*/
    ACFG_DEBUG_SYS_PIN(DBG_LOG_PRINT(("[ACFG][SYS_PIN]{%s,%d} call a_cfg_custom_set_sys_pin_passed(FALSE) \n", __FUNCTION__, __LINE__  )););
    a_cfg_custom_set_sys_pin_passed(FALSE);

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_before_pre_power_off(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{

    INT32       i4_ret = APP_CFGR_OK;
#ifdef APP_CUST_SPEC_TYPE
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT16 ui2_info = 1;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_VIZIO_LED_LOGO_CTRL;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_info;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT16);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

    DBG_INFO(("\n[ACFG]=====Call DRV_CUSTOM_CUST_SPEC_TYPE_VIZIO_LED_LOGO_CTRL to standby!! \n"));
    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                         FALSE,
                         ANY_PORT_NUM,
                         0,
                         &t_op_info,
                         z_size);
    ACFG_LOG_ON_FAIL(i4_ret);
#endif

#ifdef APP_CFG_CUSTOM_POWER_ON_OFF_AUDIO_CONTROL
        /* Turn on the audio */
        a_cfg_turn_on_off_audio_by_outport(FALSE);
#endif

#ifdef APP_CFG_CUSTOM_POWER_ON_OFF_BACKLIGHT_LVDS_CONTROL
                {
                    SM_COMMAND_T            at_scc_cmds [4];
                    /* Turn off backlight & LVDS */
                    at_scc_cmds [0].e_code      = SCC_CMD_CODE_GRP_TYPE;
                    at_scc_cmds [0].u.ui4_data  = SCC_CMD_TYPE_DISP;
                    at_scc_cmds [1].e_code      = SCC_CMD_CODE_NAME;
                    at_scc_cmds [1].u.ps_text   = SN_PRES_MAIN_DISPLAY;
                    at_scc_cmds [2].e_code      = SCC_CMD_CODE_DISP_CTRL;
                    at_scc_cmds [2].u.ui4_data  = SCC_DISP_CTRL_DISABLE;
                    at_scc_cmds [3].e_code      = SM_CMD_CODE_END;
                    c_scc_comp_grp_set (at_scc_cmds);
                }
#endif  /* APP_CFG_CUSTOM_POWER_ON_OFF_BACKLIGHT_LVDS_CONTROL */


#ifdef APP_WIFI_REMOTE
    if (!menu_get_factory_reset_status())
    {
        c_set_remote_reconnect_times(240); //set remote to retry reconnections for 2mins long
        DBG_INFO(("WiFi remote reconnection retries set to 2mins long\n"));
        c_thread_delay(200);
        c_set_remote_keep_alive_cycles(60); //set remote to retry reconnections for 2mins long
        DBG_INFO(("WiFi remote keep alive cycles set to 2mins\n"));
        c_thread_delay(200);
        //wfd_client_unreg_all_callback();
        //i4_ret = system("echo \"r p2p0\" > /sys/class/ozmo_wpan/ozwpan/bind");
        //c_dbg_stmt("unbind ozwpan driver return=%d\n", i4_ret);
        //c_thread_delay(200);
        //i4_ret = system("wpa_cli -i p2p0 p2p_group_remove p2p0");
        //c_dbg_stmt("Remove GO; Sending p2p0 deauth return=%d\n", i4_ret);
        AP_SYSTEM_CALL("sh /etc/scripts/wifi_direct_suspend.sh");

    }
#else
    AP_SYSTEM_CALL("sh /etc/scripts/wifi_direct_suspend.sh");

#endif


        if (access("/tmp/reboot_required", F_OK) == 0)
        {
            DBG_INFO(("1st time enter standby after ULI upgrade, additional reboot required\n"));
            c_thread_delay(2000);

#ifdef APP_ULI_UPG_SUPPORT
            /* fix the bug if loop test should reset the watch 0*/
            if (FALSE == a_nav_updater_is_uli_loop_test())
            {
           if (!menu_get_factory_reset_status())
           {
                    AP_SYSTEM_CALL("sync; sync; sync; reboot");
           }
            }
#else
            if (!menu_get_factory_reset_status())
            {
                AP_SYSTEM_CALL("sync; sync; sync; reboot");
            }
#endif
        }


    return i4_ret;
}

VOID _acfg_custom_set_wakeup_time(VOID);
/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_power_off(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    UINT32    ui4_setup         = 0;
    TIME_T    t_utc_wakeup_time = 0;
    TIME_T    t_utc_now         = 0;
    INT32     i4_ret            = APP_CFGR_OK;

#ifdef APP_CUST_SPEC_TYPE
    DRV_CUST_OPERATION_INFO_T   t_op_info;
    UINT16  ui2_Burn_idx = 0;
    SIZE_T  z_size = sizeof(ui2_Burn_idx);
    SIZE_T  z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
#endif

    UINT32  ui4_drv_eco = ICL_CUSTOM_POWER_MODE_ECO;
    UINT16  ui2_val = 0;
    SIZE_T  z_size;

    acfg_get(IDX_CUSTOM_USB_POWER_CTRL, (VOID*)&ui2_val, &z_size);

    a_cfg_custom_get_drv_eco_mode(&ui4_drv_eco);
    //Quick start mode, USB power=off if TV off
    if(ui4_drv_eco == ICL_CUSTOM_POWER_MODE_QUICK_START && ui2_val == 1)
    {
        a_cfg_custom_set_usb_virtual_power_ctrl(1); //close USB power
    }
    c_pcl_get_wakeup_setup(&ui4_setup);

    if (ui4_setup & PCL_WAKE_UP_CAP_RTC)
    {
        c_pcl_get_wakeup_time (&t_utc_wakeup_time);
        t_utc_now = c_dt_get_utc(NULL,NULL);

        /* Check Power ON timer is too near. */
        if (t_utc_wakeup_time > t_utc_now &&
            (ABS(t_utc_wakeup_time - t_utc_now) <= 5))
        {
#ifdef APP_AM_NO_POWER_DOWN
            a_amb_power_on(TRUE);
#else
            c_pcl_set_reboot();
#endif
        }
    }
#ifdef APP_CUST_SPEC_TYPE
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* get from driver */
    i4_ret = c_rm_set_comp(
                           DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );
    ACFG_LOG_ON_FAIL(i4_ret);
#endif
    if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
    {
        a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED);
    }
    _acfg_custom_set_wakeup_time();

    a_cfg_custom_update_long_press_ignore();
    if(ui4_drv_eco == ICL_CUSTOM_POWER_MODE_ECO)
    {
        b_during_power_ignore_count = TRUE;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_power_on(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    INT32   i4_ret = APP_CFGR_OK;
    UINT32  ui4_eco = 0;

   a_cfg_custom_service_reset(0,FALSE);
   a_cfg_custom_set_drv_watchdog_flag(0);
#ifdef APP_CFG_CUSTOM_POWER_ON_OFF_BACKLIGHT_LVDS_CONTROL
    SM_COMMAND_T            at_scc_cmds [4];

    /* Turn on backlight & LVDS */
    at_scc_cmds [0].e_code      = SCC_CMD_CODE_GRP_TYPE;
    at_scc_cmds [0].u.ui4_data  = SCC_CMD_TYPE_DISP;
    at_scc_cmds [1].e_code      = SCC_CMD_CODE_NAME;
    at_scc_cmds [1].u.ps_text   = SN_PRES_MAIN_DISPLAY;
    at_scc_cmds [2].e_code      = SCC_CMD_CODE_DISP_CTRL;
    at_scc_cmds [2].u.ui4_data  = SCC_DISP_CTRL_ENABLE;
    at_scc_cmds [3].e_code      = SM_CMD_CODE_END;
    c_scc_comp_grp_set (at_scc_cmds);
#endif  /* APP_CFG_CUSTOM_POWER_ON_OFF_BACKLIGHT_LVDS_CONTROL */

#ifdef APP_CFG_CUSTOM_POWER_ON_OFF_AUDIO_CONTROL
    if (a_cfg_custom_get_wifi_remote_support())
    {
        UINT8   ui1_status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;

        a_cfg_custom_get_wifi_remote_pair_status(&ui1_status);
        if(ui1_status != WIFI_REMOTE_PAIR_STATUS_PAIRED)
        {
            /* Turn on the audio */
            a_cfg_turn_on_off_audio_by_outport(TRUE);
        }
    }
    else
    {
        a_cfg_turn_on_off_audio_by_outport(TRUE);
    }
#endif

    a_cfg_custom_get_drv_eco_mode(&ui4_eco);

    if(ICL_CUSTOM_POWER_MODE_QUICK_START == ui4_eco)
    {
        a_cfg_disp_set_back_light_ctrl(TRUE);
    }

    a_cfg_custom_set_usb_virtual_power_ctrl(0); //open USB power

    /* Tell driver that app is power on */
    c_pcl_set_power_state (PCL_PWR_STATE_CTRL_RUNNING);

    a_cfg_custom_get_drv_eco_mode(&ui4_eco);

    i4_ret = acfg_cust_video_post_init();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_audio_post_init();
    ACFG_LOG_ON_FAIL(i4_ret);

    /*when power on, set audio ini to driver*/
    i4_ret = acfg_cust_audio_update_post_init();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_vga_post_init();
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_misc_post_init();
    ACFG_LOG_ON_FAIL(i4_ret);
#ifdef APP_LED_LOGO_CTRL
    a_cfg_custom_update_led_logo_ctrl();
#endif

#ifdef APP_C4TV_SUPPORT
    if (0 == ui4_eco)
    {
        DBG_INFO(("Noitfy Cast shell to enter resume mode.\r\n"));
        a_c4tv_apron_resume_cast();
    }
#endif

    /* set RGB enable  fix DTV00788461 */
    a_cfg_av_set( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED), 1);
    a_cfg_av_set( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN), 1);
    a_cfg_av_set( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE), 1);

    a_cfg_custom_set_rgb_on_off(1,1,1);
    b_during_power_ignore_count = FALSE;

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_dt_discont(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    a_cfg_update_timer_power();

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_hdphone_sts(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    INT32   i4_ret;

    /* Update AD settings (only need to update speaker or headphone) */
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_AD_SPEAKER));
    ACFG_LOG_ON_FAIL(i4_ret);

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_signal_loss(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    INT32   i4_ret;
    UINT8   ui1_val = 1;
    CHAR     s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    HANDLE_T h_scc_comp = NULL_HANDLE;
    SCC_VID_HDR_TYPE_T t_hdr_type = SCC_VID_PQ_SDR;


    DBG_LOG_PRINT(("[MSG][ACFG][chg_timing] {%s: %d} e_update_reason=%d\n", __FUNCTION__, __LINE__, e_update_reason));



    /* signal lost, should reset 3D MODE*/
    i4_ret = a_cfg_custom_3D_setting_reset_3D_mode();
    ACFG_LOG_ON_FAIL(i4_ret);

    a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_TEST_PATTERN),
             (VOID *) &ui1_val,
             ICL_RECID_CUSTOM_COLOR_TUNER_TEST_PATTERN_SIZE);

    /* Get SCC handle by display name. */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    if(APP_CFGR_OK == i4_ret)
    {
        h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);
        c_scc_vid_get_hdr_type(h_scc_comp, &t_hdr_type);
    }

    a_cfg_set_hdr_type(t_hdr_type);

#if ENABLE_ACFG_HDMI_TASK
    // Stop HDMI task
    acfg_cust_HDMI_task_stop();
#endif
#if( ENABLE_VIZIO_AUTO_PC)
    acfg_cust_AutoPc_stop();
#endif

    // Update Vrr/FreeSync status ...
    UINT8 u8CurHdmi_UI_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();
    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} u8CurHdmi_UI_Idx:%d \n", __FUNCTION__, __LINE__, u8CurHdmi_UI_Idx ));

    // If not HDMI, Reset VRR/FreeSync status
    if( u8CurHdmi_UI_Idx >= HDMI_PORT_NUM_MAX ) // Not HDMI
    {
        //DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s,%d} Error: Invalid u8CurHdmiPortIdx:%d !!!!\n",__FUNCTION__,__LINE__, u8CurHdmiPortIdx));
        a_acfg_cust_reset_VRR_FreeSync_status();
    }
    else
    {
        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s: %d} Do VRR/FreeSync ...\n", __FUNCTION__, __LINE__, e_update_reason));
        _acfg_cust_evt_handle_VrrFreeSync(0);
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_evt_handle_audio_value_update(
                ACFG_UPDATE_REASON_T    e_update_reason,
                VOID*                   pv_data
                )
{
    INT32   i4_ret;
    CHAR    s_app_name[APP_NAME_MAX_LEN];

    i4_ret = a_am_get_active_app(s_app_name);
    if (AMR_OK == i4_ret && 0 == c_strcmp (s_app_name, MMP_NAME))
    {
        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));
        ACFG_LOG_ON_FAIL(i4_ret);
    }
    return APP_CFGR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:_acfg_cust_init_speaker_auto
 * Description:When speaker set to auto, reset audio out when power on
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 _acfg_cust_init_speaker_auto(VOID)
{
    UINT16          ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16          ui2_aud_out_mask;
    INT16           i2_val;
    UINT8           ui1_icl_val = ICL_CEC_SAC_STATUS_OFF;
    SIZE_T          z_size = sizeof(UINT8);
    UINT8           ui1_sac_func = 0;
    INT32           i4_ret;

    a_cfg_av_get(ui2_id, &i2_val);
    ui2_aud_out_mask = (UINT16)i2_val;

            // get is or not cec device connected
    z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                       &ui1_icl_val,
                       &z_size);
    if(i4_ret != ICLR_OK)
    {
        DBG_INFO((" [tv speaker] get sac status icl fail \n"));
    }

    if(ui1_sac_func == APP_CFG_CEC_OFF)
    {
        a_cfg_set_cec_sac_func(1);
    }

    DBG_INFO(("%s,%d [tv speaker] icl_sac_status=%d \n",__FUNCTION__,__LINE__,ui1_icl_val));
    if(ICL_CEC_SAC_STATUS_ON == ui1_icl_val)
    {
        // set_aud_speaker_status(0), Just like set tv speaker off
        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);
    }
    else
    {
        //AMP is disconnected. Just like set tv speaker on, tv speake audio, but sac set to 1.
        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask | SCC_AUD_OUT_PORT_SPEAKER);
    }
    a_cfg_custom_set_speakers_out(APP_CFG_AUD_AD_SPEAKER_AUTO);
    a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
    i4_ret = a_cfg_av_update(ui2_id);

    return i4_ret;

}
/*-----------------------------------------------------------------------------
 * Name: acfg_custom_regular_update
 *
 * Description:
 *       acfg will call this function regularly.
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_custom_regular_update(VOID)
{
    INT32       i4_ret;

    /* Update Power on/Power off Timer by Day_Sec */
    i4_ret = a_cfg_update_timer_power();
    ACFG_LOG_ON_FAIL(i4_ret);

    return APP_CFGR_OK;
}

static INT32 _acfg_cust_evt_handle_hdr_change()
{
    DBG_LOG_PRINT(("[ACFG][HDR]{%s: %d} \n", __FUNCTION__, __LINE__ ));

    ACFG_LOG_ON_FAIL(a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE)));

    return APP_CFGR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: acfg_custom_update_all
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/

static char* AcfgCust_Get_UpdateReasonString( ACFG_UPDATE_REASON_T e_update_reason )
{
    char* pcUpdateReasonString = "NoName";

    switch (e_update_reason)
    {
        case ACFG_UPDATE_REASON_CHG_INPUT: // 1 /* Notify when signal lock/loss after input change */
            pcUpdateReasonString = "CHG_INPUT";
            break;

        case ACFG_UPDATE_REASON_CHG_CHANNEL: // 2 /* Notify when signal lock/loss after channel change */
            pcUpdateReasonString = "CHG_CHANNEL";
            break;
        case ACFG_UPDATE_REASON_PRE_CHG_INPUT: // 3 /* Notify when the config "INPUT" is set */
            pcUpdateReasonString = "PRE_CHG_INPUT";
            break;

        case ACFG_UPDATE_REASON_CHG_TIMING: // 4 /* Notify when video format update */
            pcUpdateReasonString = "CHG_TIMING";
            break;

        case ACFG_UPDATE_REASON_CHG_AUD_FMT: // 5 /* Notify when audio format update */
            pcUpdateReasonString = "CHG_AUD_FMT";
            break;

        case ACFG_UPDATE_REASON_CHG_COLOR_SYS: // 6 /* Notify when color sys update */
            pcUpdateReasonString = "CHG_COLOR_SYS";
            break;

        case ACFG_UPDATE_REASON_CHG_TV_MODE:
            pcUpdateReasonString = "CHG_TV_MODE";
            break;

        case ACFG_UPDATE_REASON_SIGNAL_LOSS: // 8 /* Notify when signal is loss */
            pcUpdateReasonString = "SIGNAL_LOSS";
            break;

        case ACFG_UPDATE_REASON_SIGNAL_LOCK: // 9 /* Notify when signal is locked */
            pcUpdateReasonString = "SIGNAL_LOCK";
            break;

        case ACFG_UPDATE_REASON_CHG_SERVICE: // 10 /* Notify when the the service is changed. Ex. Ch change or inp src change. */
            pcUpdateReasonString = "CHG_SERVICE";
            break;

        case ACFG_UPDATE_REASON_RESET:
            pcUpdateReasonString = "RESET";
            break;

        case ACFG_UPDATE_REASON_VGA_AUTO_DONE:
            pcUpdateReasonString = "VGA_AUTO_DONE";
            break;
        case ACFG_UPDATE_REASON_VGA_AUTO_FAIL:
            pcUpdateReasonString = "VGA_AUTO_FAIL";
            break;
        case ACFG_UPDATE_REASON_PRE_POWER_OFF:
            pcUpdateReasonString = "PRE_POWER_OFF";
            break;
        case ACFG_UPDATE_REASON_POWER_OFF:
            pcUpdateReasonString = "POWER_OFF";
            break;
        case ACFG_UPDATE_REASON_POWER_ON:
            pcUpdateReasonString = "POWER_ON";
            break;
        case ACFG_UPDATE_REASON_DT_DISCONT:
            pcUpdateReasonString = "DT_DISCONT";
            break;
        case ACFG_UPDATE_REASON_HDPHONE_PLUGED:
            pcUpdateReasonString = "HDPHONE_PLUGED";
            break;
        case ACFG_UPDATE_REASON_HDPHONE_UNPLUGED:
            pcUpdateReasonString = "HDPHONE_UNPLUGED";
            break;
        case ACFG_UPDATE_REASON_APP_ACTIVE:
            pcUpdateReasonString = "APP_ACTIVE";
            break;
        case ACFG_UPDATE_REASON_APP_PAUSED: // 25
            pcUpdateReasonString = "APP_PAUSED";
            break;
        case ACFG_UPDATE_REASON_SELECT_SERVICE_NORMAL: // 26
            pcUpdateReasonString = "SELECT_SERVICE_NORMAL";
            break;
        case ACFG_UPDATE_REASON_HAVE_VIDEO: // 27
            pcUpdateReasonString = "HAVE_VIDEO";
            break;
        case ACFG_UPDATE_REASON_NO_VIDEO: // 28
            pcUpdateReasonString = "NO_VIDEO";
            break;
        case ACFG_UPDATE_REASON_HDR_CHG: // 29
            pcUpdateReasonString = "HDR_CHG";
            break;

        case ACFG_UPDATE_REASON_HDMI_CONTENT_TYPE_CHG: // 31
            pcUpdateReasonString = "HDMI_CONTENT_TYPE_CHG";
            break;

        case ACFG_UPDATE_REASON_BEFORE_PRE_POWER_OFF:
            pcUpdateReasonString = "BEFORE_PRE_POWER_OFF";
            break;
        case ACFG_UPDATE_REASON_VIDEO_STOPPED_BY_APP:
            pcUpdateReasonString = "VIDEO_STOPPED_BY_APP";
            break;

        default:
            break;
    }

    return pcUpdateReasonString;
}

extern INT32 acfg_custom_update_all(
    ACFG_UPDATE_REASON_T e_update_reason,
    VOID* pv_data)
{
    INT32   i4_ret;

    DBG_LOG_PRINT(("[ACFG][MSG]acfg_custom_update_all(e_update_reason=%d(%s) =================================== start\n", e_update_reason, AcfgCust_Get_UpdateReasonString(e_update_reason) ));

    ACFG_LOG_ON_FAIL(acfg_custom_odm_pre_update_all(e_update_reason, pv_data));

    switch (e_update_reason){
    case ACFG_UPDATE_REASON_RESET:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_reset(e_update_reason, pv_data));
        break;
#ifdef APP_537X_SUPPORT
    case ACFG_UPDATE_REASON_CHG_SERVICE:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_chg_service(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_CHG_TIMING:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_chg_timing(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_VGA_AUTO_DONE:
    case ACFG_UPDATE_REASON_VGA_AUTO_FAIL:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_vga_auto_tune(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_CHG_INPUT:
        _acfg_cust_evt_handle_chg_input(e_update_reason, pv_data);
        break;
    case ACFG_UPDATE_REASON_PRE_CHG_INPUT:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_pre_chg_input(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_CHG_TV_MODE:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_chg_tv_mode(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_PRE_POWER_OFF:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_pre_power_off(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_POWER_OFF:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_power_off(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_POWER_ON:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_power_on(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_DT_DISCONT:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_dt_discont(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_HDPHONE_PLUGED:
    case ACFG_UPDATE_REASON_HDPHONE_UNPLUGED:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_hdphone_sts(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_SIGNAL_LOSS:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_signal_loss(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_APP_ACTIVE:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_audio_value_update(e_update_reason, pv_data));
        break;
#endif  /* APP_537X_SUPPORT */
    case ACFG_UPDATE_REASON_BEFORE_PRE_POWER_OFF:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_before_pre_power_off(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_VIDEO_STOPPED_BY_APP:
        ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_select_service(e_update_reason, pv_data));
        break;
    case ACFG_UPDATE_REASON_CHG_AUD_FMT:
         ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_chg_aud_fmt(e_update_reason, pv_data));
        break;

    case ACFG_UPDATE_REASON_HAVE_VIDEO:
    case ACFG_UPDATE_REASON_SIGNAL_LOCK:
        ACFG_LOG_ON_FAIL(scrn_svr_set_str_id_to_empty());

        /*Add for DTV03361663, Update the screen mode before unlock channel*/
        ACFG_LOG_ON_FAIL(a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE)));
        break;

    case ACFG_UPDATE_REASON_HDR_CHG:
    {
         ACFG_MSG_SCC_VID_HDR_VDP_EVNT_T* pt_msg_hdr_evnt = (ACFG_MSG_SCC_VID_HDR_VDP_EVNT_T*)pv_data;
         DBG_INFO(("[ACFG][%s %d] ACFG_UPDATE_REASON_HDR_CHG hdr_type = %d\n",__FUNCTION__,__LINE__, pt_msg_hdr_evnt->e_vid_hdr_type ));

         DBG_LOG_PRINT(("[ACFG][HDR]{%s: %d} HDR_type change => %d \n",
                                            __FUNCTION__, __LINE__, pt_msg_hdr_evnt->e_vid_hdr_type ));

         a_cfg_set_hdr_type(pt_msg_hdr_evnt->e_vid_hdr_type);

         ACFG_LOG_ON_FAIL(_acfg_cust_evt_handle_hdr_change());

    }
        break;
    default:
        i4_ret = APP_CFGR_NO_ACTION;
        break;
    }

    i4_ret = acfg_custom_odm_update_all(e_update_reason, pv_data);
    ACFG_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("[ACFG][MSG]acfg_custom_update_all(e_update_reason=%d(%s) --------------- end\n", e_update_reason, AcfgCust_Get_UpdateReasonString(e_update_reason) ));

    return i4_ret;
}

/*------------------------------------------------------------------------------
                              External Functions
------------------------------------------------------------------------------*/
extern INT32 a_cfg_get_dcr_def_value(UINT8 *pui1_dcr_def)
{
    TV_WIN_ID_T     t_win_id;
    ISL_REC_T       t_isl_rec;
    ISL_REC_T       t_isl_rec_crnt;
    UINT8           ui1_inp_src_idx = 0;
    INT16           i2_pic_mode_id = 0;
    UINT8           ui1_rec_num;
    UINT8           ui1_idx;

    if (NULL == pui1_dcr_def)
    {
        return APP_CFGR_INV_ARG;
    }

    a_tv_get_focus_win(&t_win_id);

    a_isl_get_num_rec(&ui1_rec_num);
    a_tv_get_isl_rec_by_win_id(t_win_id, &t_isl_rec_crnt);

    /* get current input source index */
    for(ui1_idx = 0 ; ui1_idx < ui1_rec_num ; ui1_idx++)
    {
        a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);

        if(t_isl_rec.ui1_id == t_isl_rec_crnt.ui1_id)
        {
            ui1_inp_src_idx = ui1_idx;
            break;
        }
    }
    if(ui1_inp_src_idx == ui1_rec_num)
    {
        ui1_inp_src_idx = 0;
    }

    /*get current pic mode index*/
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode_id);

    *pui1_dcr_def = *(((UINT8*)at_acfg_descr[IDX_CUSTOM_DCR_IDX].pt_def_value)+
                        ui1_inp_src_idx * ACFG_PIC_MODE_NUM + i2_pic_mode_id);


    return APP_CFGR_OK;
}


extern INT32 a_cfg_av_get_min_max(
    UINT16  ui2_id,
    INT16*  pi2_min,
    INT16*  pi2_max)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;


    switch(CFG_GET_GROUP(ui2_id)){
    case APP_CFG_GRPID_VIDEO:
    case APP_CFG_GRPID_DISP:
        i4_ret = acfg_cust_video_get_min_max(ui2_id, pi2_min, pi2_max);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_video_get_min_max(ui2_id, pi2_min, pi2_max);
        }
        break;
    case APP_CFG_GRPID_AUDIO:
        i4_ret = acfg_cust_audio_get_min_max(ui2_id, pi2_min, pi2_max);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_audio_get_min_max(ui2_id, pi2_min, pi2_max);
        }
        break;
    case APP_CFG_GRPID_VGA:
        i4_ret = acfg_cust_vga_get_min_max(ui2_id, pi2_min, pi2_max);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_vga_get_min_max(ui2_id, pi2_min, pi2_max);
        }
        break;
    case APP_CFG_GRPID_FACTORY:
        i4_ret = acfg_cust_fact_get_min_max(ui2_id, pi2_min, pi2_max);
        if (i4_ret == APP_CFGR_NO_ACTION){
            return APP_CFGR_INV_ARG;
        }
        break;
    default:
        return APP_CFGR_INV_ARG;
    }

    return i4_ret;
}

extern INT32 a_cfg_set_lip_sync(INT16 i2_val)
{
    INT32       i4_ret = -1;
    UINT8       ui1_input;
    ISL_REC_T   t_isl_rec;
    UINT16      ui2_cfg_id = IDX_CUSTOM_LIP_SYNC_IDX_TV;
    UINT8       ui1_input_grp = 0;
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8       ui1_lip_val = 0;

    /* Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

    ui1_input_grp = acfg_custom_get_input_grp(&t_isl_rec);

    ui2_cfg_id = IDX_CUSTOM_LIP_SYNC_IDX_TV + (UINT16)((ACFG_CUST_INPUT_GRP_T)ui1_input_grp - ACFG_CUST_INPUT_GRP_TV);

    ui1_lip_val = (UINT8)i2_val;
//    i4_ret = acfg_set(ui2_cfg_id, &i2_val, 1);
    i4_ret = acfg_set(ui2_cfg_id, &ui1_lip_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}

extern INT32 a_cfg_get_lip_sync(INT16* pi2_val)
{
#ifdef ACFG_SUPPORT_AUD_SET_GLOBAL
    INT32       i4_ret = -1;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY), pi2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
#else
    INT32       i4_ret = -1;
    UINT8       ui1_input;
    SIZE_T      z_size;
    ISL_REC_T   t_isl_rec;
    UINT16      ui2_cfg_id = IDX_CUSTOM_LIP_SYNC_IDX_TV;
    UINT8       ui1_input_grp = 0;
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8       ui1_lip_val = 0;

    /* Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

    ui1_input_grp = acfg_custom_get_input_grp(&t_isl_rec);

    ui2_cfg_id = IDX_CUSTOM_LIP_SYNC_IDX_TV + (UINT16)((ACFG_CUST_INPUT_GRP_T)ui1_input_grp - ACFG_CUST_INPUT_GRP_TV);

//    i4_ret = acfg_get(ui2_cfg_id, pi2_val, &z_size);
    i4_ret = acfg_get(ui2_cfg_id, &ui1_lip_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    *pi2_val= ui1_lip_val;
#endif
    return APP_CFGR_OK;
}

extern INT32 a_cfg_set_srs_sorround_hd(INT16 i2_val)
{
    INT32       i4_ret = -1;
    UINT8       ui1_input;
    ISL_REC_T   t_isl_rec;
    UINT16      ui2_cfg_id = IDX_CUSTOM_SRS_SRUND_IDX_TV;
    UINT8       ui1_input_grp = 0;
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8       ui1_val = 0;

    /* Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

    ui1_input_grp = acfg_custom_get_input_grp(&t_isl_rec);

    ui2_cfg_id = IDX_CUSTOM_SRS_SRUND_IDX_TV + (UINT16)((ACFG_CUST_INPUT_GRP_T)ui1_input_grp - ACFG_CUST_INPUT_GRP_TV);

    ui1_val = (UINT8)i2_val;
    //i4_ret = acfg_set(ui2_cfg_id, &i2_val, 1);
    i4_ret = acfg_set(ui2_cfg_id, &ui1_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_SURROUND), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}

extern INT32 a_cfg_get_srs_sorround_hd(INT16* pi2_val)
{
    INT32       i4_ret = -1;
#ifndef ACFG_SUPPORT_AUD_SET_GLOBAL
    UINT8       ui1_input;
    SIZE_T      z_size;
    ISL_REC_T   t_isl_rec;
    UINT16      ui2_cfg_id = IDX_CUSTOM_SRS_SRUND_IDX_TV;
    UINT8       ui1_input_grp = 0;
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8       ui1_val = 0;

    /* Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

    ui1_input_grp = acfg_custom_get_input_grp(&t_isl_rec);

    ui2_cfg_id = IDX_CUSTOM_SRS_SRUND_IDX_TV + (UINT16)((ACFG_CUST_INPUT_GRP_T)ui1_input_grp - ACFG_CUST_INPUT_GRP_TV);

    //i4_ret = acfg_get(ui2_cfg_id, pi2_val, &z_size);
    i4_ret = acfg_get(ui2_cfg_id, &ui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    *pi2_val = (INT16)ui1_val;
#else
    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SOUND_MODE), pi2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    if(((SURROUND_MODE) *pi2_val != SURROUND_SOUND_ON))
    {
        *pi2_val  = SURROUND_SOUND_OFF;
    }
#endif

    return APP_CFGR_OK;
}

extern INT32 a_cfg_av_incr(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;

    switch(CFG_GET_GROUP(ui2_id))
    {
    case APP_CFG_GRPID_VIDEO:
    case APP_CFG_GRPID_DISP:
        i4_ret = acfg_cust_video_incr(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_video_incr(ui2_id, pi2_val);
        }
        break;
    case APP_CFG_GRPID_AUDIO:
        i4_ret = acfg_cust_audio_incr(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_audio_incr(ui2_id, pi2_val);
        }
        break;
    case APP_CFG_GRPID_VGA:
        i4_ret = acfg_cust_vga_incr(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_vga_incr(ui2_id, pi2_val);
        }
        break;
    case APP_CFG_GRPID_FACTORY:
        i4_ret = acfg_cust_fact_incr(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            return APP_CFGR_INV_ARG;
        }
    default:
        return APP_CFGR_INV_ARG;
    }

    return i4_ret;
}

extern INT32  a_cfg_av_decr(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;

    switch(CFG_GET_GROUP(ui2_id))
    {
    case APP_CFG_GRPID_VIDEO:
    case APP_CFG_GRPID_DISP:
        i4_ret = acfg_cust_video_decr(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_video_decr(ui2_id, pi2_val);
        }
        break;
    case APP_CFG_GRPID_AUDIO:
        i4_ret = acfg_cust_audio_decr(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_audio_decr(ui2_id, pi2_val);
        }
        break;
    case APP_CFG_GRPID_VGA:
        i4_ret = acfg_cust_vga_decr(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_vga_decr(ui2_id, pi2_val);
        }
        break;
    case APP_CFG_GRPID_FACTORY:
        i4_ret = acfg_cust_fact_decr(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            return APP_CFGR_INV_ARG;
        }
        break;
    default:
        return APP_CFGR_INV_ARG;
    }

    return i4_ret;
}

extern INT32 a_cfg_av_get(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;

    switch(CFG_GET_GROUP(ui2_id))
    {
    case APP_CFG_GRPID_VIDEO:
    case APP_CFG_GRPID_DISP:
        i4_ret = acfg_cust_video_get(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_video_get(ui2_id, pi2_val);
        }
        break;
    case APP_CFG_GRPID_AUDIO:
        i4_ret = acfg_cust_audio_get(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_audio_get(ui2_id, pi2_val);
        }
        break;
    case APP_CFG_GRPID_VGA:
        i4_ret = acfg_cust_vga_get(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_vga_get(ui2_id, pi2_val);
        }
        break;
    case APP_CFG_GRPID_FACTORY:
        i4_ret = acfg_cust_fact_get(ui2_id, pi2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            return APP_CFGR_INV_ARG;
        }
        break;
    default:
        return APP_CFGR_INV_ARG;
    }

    return i4_ret;
}

extern INT32 a_cfg_av_set(
    UINT16  ui2_id,
    INT16   i2_val)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;
    switch(CFG_GET_GROUP(ui2_id))
    {
    case APP_CFG_GRPID_VIDEO:
    case APP_CFG_GRPID_DISP:
        i4_ret = acfg_cust_video_set(ui2_id, i2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_video_set(ui2_id, i2_val);
        }
        break;
    case APP_CFG_GRPID_AUDIO:
        i4_ret = acfg_cust_audio_set(ui2_id, i2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_audio_set(ui2_id, i2_val);
        }
        break;
    case APP_CFG_GRPID_VGA:
        i4_ret = acfg_cust_vga_set(ui2_id, i2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_vga_set(ui2_id, i2_val);
        }
        break;
    case APP_CFG_GRPID_FACTORY:
        i4_ret = acfg_cust_fact_set(ui2_id, i2_val);
        if (i4_ret == APP_CFGR_NO_ACTION){
            return APP_CFGR_INV_ARG;
        }
        break;
    default:
        return APP_CFGR_INV_ARG;
    }

    return i4_ret;
}
extern INT32 a_cfg_av_update(
    UINT16  ui2_id)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;

    switch(CFG_GET_GROUP(ui2_id))
    {
    case APP_CFG_GRPID_VIDEO:
    case APP_CFG_GRPID_DISP:
        i4_ret = acfg_cust_odm_video_update(ui2_id);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_cust_video_update(ui2_id);
            if (i4_ret == APP_CFGR_NO_ACTION){
                i4_ret = acfg_video_update(ui2_id);
            }
        }
        break;
    case APP_CFG_GRPID_AUDIO:
        i4_ret = acfg_cust_odm_audio_update(ui2_id);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_cust_audio_update(ui2_id);
            if (i4_ret == APP_CFGR_NO_ACTION){
                i4_ret = acfg_audio_update(ui2_id);
            }
        }
        break;
    case APP_CFG_GRPID_VGA:
        i4_ret = acfg_cust_odm_vga_update(ui2_id);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_cust_vga_update(ui2_id);
            if (i4_ret == APP_CFGR_NO_ACTION){
                i4_ret = acfg_vga_update(ui2_id);
            }
        }
        break;
    case APP_CFG_GRPID_FACTORY:
        i4_ret = acfg_cust_fact_update(ui2_id);
        if (i4_ret == APP_CFGR_NO_ACTION){
            return APP_CFGR_INV_ARG;
        }
        break;
    default:
        return APP_CFGR_INV_ARG;
    }

    return i4_ret;
}
extern INT32 a_cfg_av_sync(
    UINT16  ui2_id)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;

    switch(CFG_GET_GROUP(ui2_id))
    {
    case APP_CFG_GRPID_VIDEO:
    case APP_CFG_GRPID_DISP:
        i4_ret = acfg_cust_video_sync(ui2_id);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_video_sync(ui2_id);
        }
        break;
    case APP_CFG_GRPID_AUDIO:
        i4_ret = acfg_cust_audio_sync(ui2_id);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_audio_sync(ui2_id);
        }
        break;
    case APP_CFG_GRPID_VGA:
        i4_ret = acfg_cust_vga_sync(ui2_id);
        if (i4_ret == APP_CFGR_NO_ACTION){
            i4_ret = acfg_vga_sync(ui2_id);
        }
        break;
    default:
        return APP_CFGR_INV_ARG;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
* Name: a_cfg_custom_set_auto_ip_config
*
* Description: store network tv type info to flash
*
* Inputs:
*      ui1_tv_type
*
* Outputs: -
*
* Returns:
*      APP_CFGR_OK             - Successful
*      APP_CFGR_NOT_INIT       - Not Initiated
*      APP_CFGR_INTERNAL_ERR   - Internal Error
*--------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_set_auto_ip_config(BOOL b_enable, UINT8 ui1_idx)
{
    UINT8       aui1_auto_ip_config[2] = {0};
    SIZE_T      z_size = 0;
    INT32       i4_ret;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    i4_ret = acfg_get(IDX_AUTO_IP_CONFIG, aui1_auto_ip_config , &z_size);
    if(i4_ret != APP_CFGR_OK)
    {
        return APP_CFGR_INTERNAL_ERR;
    }

    DBG_INFO(("<ACFG> %s, LINE: %d, ui1_idx: %u, b_enable: %d\n", __FUNCTION__, __LINE__, ui1_idx, b_enable));

    if (ui1_idx >= 2)
    {
        return APP_CFGR_INV_ARG;
    }

    aui1_auto_ip_config[ui1_idx] = (UINT8)b_enable;
    i4_ret= acfg_set(IDX_AUTO_IP_CONFIG, aui1_auto_ip_config , 2);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_auto_ip_config
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_get_auto_ip_config(BOOL* pb_enable, UINT8 ui1_idx)
{
    UINT8       aui1_auto_ip_config[2] = {0};
    SIZE_T      z_size = 0;
    INT32       i4_ret = APP_CFGR_OK;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    if (pb_enable == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_AUTO_IP_CONFIG, aui1_auto_ip_config , &z_size);

    if (ui1_idx >= 2)
    {
        return APP_CFGR_INV_ARG;
    }

    *pb_enable = (BOOL)aui1_auto_ip_config[ui1_idx];

    return i4_ret;
}

/*-----------------------------------------------------------------------------
* Name: a_cfg_custom_set_ip_addr
*
* Description: store network tv type info to flash
*
* Inputs:
*      ui1_tv_type
*
* Outputs: -
*
* Returns:
*      APP_CFGR_OK             - Successful
*      APP_CFGR_NOT_INIT       - Not Initiated
*      APP_CFGR_INTERNAL_ERR   - Internal Error
*--------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_set_ip_addr(UINT32 ui4_address, UINT8    ui1_idx)
{
    UINT32      aui4_addr[2] = {0};
    SIZE_T      z_size;
    INT32       i4_ret;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    i4_ret = acfg_get(IDX_IP_ADDR, aui4_addr , &z_size);
    if(i4_ret != APP_CFGR_OK)
    {
        return APP_CFGR_INTERNAL_ERR;
    }

    aui4_addr[ui1_idx] = ui4_address;
    i4_ret= acfg_set(IDX_IP_ADDR, aui4_addr , 2);
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_ip_addr
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
extern INT32  a_cfg_custom_get_ip_addr(UINT32 *pui4_address, UINT8     ui1_idx)
{
    SIZE_T      z_size;
    UINT32      aui4_addr[2] = {0};
    INT32       i4_ret = APP_CFGR_OK;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    if (pui4_address == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_IP_ADDR, aui4_addr , &z_size);
    *pui4_address = aui4_addr[ui1_idx];

    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name: a_cfg_custom_set_subnet_mask
*
* Description: store network tv type info to flash
*
* Inputs:
*      ui1_tv_type
*
* Outputs: -
*
* Returns:
*      APP_CFGR_OK             - Successful
*      APP_CFGR_NOT_INIT       - Not Initiated
*      APP_CFGR_INTERNAL_ERR   - Internal Error
*--------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_set_subnet_mask(UINT32 ui4_netmask, UINT8    ui1_idx)
{
    UINT32      aui4_mask[2] = {0};
    SIZE_T      z_size;
    INT32       i4_ret;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    i4_ret = acfg_get(IDX_SUBNET_MASK, aui4_mask , &z_size);
    if(i4_ret != APP_CFGR_OK)
    {
        return APP_CFGR_INTERNAL_ERR;
    }

    aui4_mask[ui1_idx] = ui4_netmask;
    i4_ret= acfg_set(IDX_SUBNET_MASK, aui4_mask , 2);
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_subnet_mask
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
extern INT32  a_cfg_custom_get_subnet_mask(UINT32 *pui4_netmask, UINT8     ui1_idx)
{
    SIZE_T      z_size;
    UINT32      aui4_netmask[2] = {0};
    INT32       i4_ret = APP_CFGR_OK;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    if (pui4_netmask == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_SUBNET_MASK, aui4_netmask, &z_size);
    *pui4_netmask = aui4_netmask[ui1_idx];

    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name: a_cfg_custom_set_default_gateway
*
* Description:
*
* Inputs:
*
*
* Outputs: -
*
* Returns:
*      APP_CFGR_OK             - Successful
*      APP_CFGR_NOT_INIT       - Not Initiated
*      APP_CFGR_INTERNAL_ERR   - Internal Error
*--------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_set_default_gateway(UINT32 ui4_gw, UINT8    ui1_idx)
{
    UINT32      aui4_gw[2] = {0};
    SIZE_T      z_size;
    INT32       i4_ret;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    i4_ret = acfg_get(IDX_DEFAULT_GATEWAY, aui4_gw , &z_size);
    if(i4_ret != APP_CFGR_OK)
    {
        return APP_CFGR_INTERNAL_ERR;
    }

    aui4_gw[ui1_idx] = ui4_gw;
    i4_ret= acfg_set(IDX_DEFAULT_GATEWAY, aui4_gw , 2);
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_default_gateway
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
extern INT32  a_cfg_custom_get_default_gateway(UINT32* pui4_gw, UINT8     ui1_idx)
{
    SIZE_T      z_size;
    UINT32      aui4_gw[2] = {0};
    INT32       i4_ret = APP_CFGR_OK;


    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    if (pui4_gw == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_DEFAULT_GATEWAY, aui4_gw , &z_size);
    *pui4_gw = aui4_gw[ui1_idx];

    return i4_ret;

}
/*-----------------------------------------------------------------------------
* Name: a_cfg_custom_set_1st_dns
*
* Description:
*
* Inputs:
*
*
* Outputs: -
*
* Returns:
*      APP_CFGR_OK             - Successful
*      APP_CFGR_NOT_INIT       - Not Initiated
*      APP_CFGR_INTERNAL_ERR   - Internal Error
*--------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_set_1st_dns(UINT32 ui4_1st_DNS, UINT8    ui1_idx)
{
    UINT32      aui4_1st_dns[2] = {0};
    SIZE_T      z_size;
    INT32       i4_ret;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    i4_ret = acfg_get(IDX_1ST_DNS, aui4_1st_dns , &z_size);
    if(i4_ret != APP_CFGR_OK)
    {
        return APP_CFGR_INTERNAL_ERR;
    }

    aui4_1st_dns[ui1_idx] = ui4_1st_DNS;
    i4_ret= acfg_set(IDX_1ST_DNS, aui4_1st_dns , 2);
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_1st_dns
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
extern INT32  a_cfg_custom_get_1st_dns(UINT32* pui4_1st_DNS, UINT8    ui1_idx)
{
    SIZE_T      z_size;
    UINT32      aui4_1st_dns[2] = {0};
    INT32       i4_ret = APP_CFGR_OK;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    if (pui4_1st_DNS == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_1ST_DNS, aui4_1st_dns , &z_size);
    *pui4_1st_DNS = aui4_1st_dns[ui1_idx];

    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name: a_cfg_custom_set_2nd_dns
*
* Description:
*
* Inputs:
*
*
* Outputs: -
*
* Returns:
*      APP_CFGR_OK             - Successful
*      APP_CFGR_NOT_INIT       - Not Initiated
*      APP_CFGR_INTERNAL_ERR   - Internal Error
*--------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_set_2nd_dns(UINT32 ui4_2nd_DNS, UINT8    ui1_idx)
{
    UINT32      aui4_2nd_dns[2] = {0};
    SIZE_T      z_size;
    INT32       i4_ret;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    i4_ret = acfg_get(IDX_2ND_DNS, aui4_2nd_dns , &z_size);
    if(i4_ret != APP_CFGR_OK)
    {
        return APP_CFGR_INTERNAL_ERR;
    }

    aui4_2nd_dns[ui1_idx] = ui4_2nd_DNS;
    i4_ret= acfg_set(IDX_2ND_DNS, aui4_2nd_dns , 2);
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_2nd_dns
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
extern INT32  a_cfg_custom_get_2nd_dns(UINT32* pui4_2nd_DNS, UINT8     ui1_idx)
{
    SIZE_T      z_size;
    UINT32      aui4_2nd_dns[2] = {0};
    INT32       i4_ret = APP_CFGR_OK;

    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    if (pui4_2nd_DNS == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_2ND_DNS, aui4_2nd_dns , &z_size);
    *pui4_2nd_DNS = aui4_2nd_dns[ui1_idx];

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_3D_setting_reset_3D_mode
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
*
 *-----------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_3D_setting_reset_3D_mode(VOID)
{
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                 (INT16)APP_CFG_3D_MODE_OFF);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

    /* 3D to 2D*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
             (INT16 )APP_CFG_3D_TO_2D_OFF);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));

    return APP_CFGR_OK;
}

extern INT32  a_cfg_custom_reset_public_default(VOID)
{
    INT32   i4_ret;
    UINT16  ui2_i;
    ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    UINT8   ui1_mask = ACFG_ACCESS_PUBLIC;

    DBG_API(("<ACFG>a_cfg_custom_reset_public_default\r\n"));

    for(ui2_i = 0; ui2_i < IDX_MAX; ui2_i++)
    {
        if (ui2_i == IDX_GL)
        {
            continue;
        }

        if(at_acfg_descr[ui2_i].b_enable &&
           ((at_acfg_descr[ui2_i].ui1_access_mask & ui1_mask) != 0))
        {
#ifdef APP_MENU_MMP_COEXIST
            if(a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
            {
                if(ui2_i == IDX_CUSTOM_MMP_PHOTO_SET_INFO ||
                   ui2_i == IDX_CUSTOM_MMP_PHOTO_RECUR_PARSING ||
                   ui2_i == IDX_CUSTOM_MMP_PHOTO_SORT ||
                   ui2_i == IDX_CUSTOM_MMP_AUDIO_RECUR_PARSING ||
                   ui2_i == IDX_CUSTOM_MMP_VIDEO_RECUR_PARSING ||
                   ui2_i == IDX_CUSTOM_MMP_AUDIO_SORT ||
                   ui2_i == IDX_CUSTOM_MMP_VIDEO_SORT)
                {
                    continue;
                }
             }

            if (((a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED) ||
                 (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)) &&
                 (ui2_i == IDX_AL || ui2_i == IDX_AL_2ND || ui2_i == IDX_AUD_TYPE))
#else
            if ((a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED) &&
                 (ui2_i == IDX_AL || ui2_i == IDX_AL_2ND || ui2_i == IDX_AUD_TYPE))
#endif
            {
                a_cfg_set_fire_nfy_switch(FALSE);
                acfg_set_default(ui2_i);
                a_cfg_set_fire_nfy_switch(TRUE);
            }
            else
            {
                acfg_set_default(ui2_i);
            }
        }
        if ((IDX_NETWORK_ENABLE == ui2_i ||
            IDX_IP_ADDR == ui2_i ||
            IDX_SUBNET_MASK == ui2_i ||
            IDX_DEFAULT_GATEWAY == ui2_i ||
            IDX_1ST_DNS == ui2_i ||
            IDX_2ND_DNS == ui2_i ||
            IDX_NET_INTERFACE == ui2_i ||
            IDX_WLAN_BSSID == ui2_i ||
            IDX_WLAN_SSID == ui2_i ||
            IDX_WLAN_ASSOC_CASE == ui2_i ||
            IDX_WLAN_AUTH_MODE == ui2_i ||
            IDX_WLAN_AUTH_CIPHER == ui2_i ||
            IDX_WLAN_KEY == ui2_i   ||
            IDX_AUTO_IP_CONFIG == ui2_i
        #ifdef APP_NET_DLNA_SUPPORT
            || IDX_DLNA_ENABLE == ui2_i
        #ifdef APP_DMR_SUPPORT
            || IDX_DLNA_DMR_ENABLE == ui2_i
        #endif
        #endif
            || IDX_INPUT_MAIN == ui2_i
            || IDX_BS_SRC == ui2_i) &&
            at_acfg_descr[ui2_i].b_enable &&
            ((at_acfg_descr[ui2_i].ui1_access_mask & (UINT8)ACFG_ACCESS_FACTORY) != 0))
        {
            acfg_set_default(ui2_i);
        }
    }

#if (VIEWPORT_SUPPORT == 1)
    {
        APP_CFG_VIEWPORT_T t_viewport;

        t_viewport.e_type = APP_CFG_VIEWPORT_TYPE_OVERLAY;
        t_viewport.i4_x = 0;
        t_viewport.i4_y = 0;
        t_viewport.i4_w = 1920;
        t_viewport.i4_h = 1080;

        i4_ret = a_cfg_set_viewport (&t_viewport);
        ACFG_LOG_ON_FAIL(i4_ret);

    }
#endif

#ifdef APP_RETAIL_MODE_SUPPORT
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        a_cfg_custom_set_pic_mode_vivid();
    }
#endif

    acfg_lock();

    i4_ret = acfg_custom_update_all(ACFG_UPDATE_REASON_RESET, (VOID*)(UINT32)ui1_mask);

    acfg_unlock();

    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}

INT32 a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data)
{
    INT32                        i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    switch(e_op_type)
    {
        case DRV_CUSTOM_OPERATION_TYPE_AUD_SET:
        {
            AUD_TYPE_SET_INFO_T*    pt_aud_set_info = (AUD_TYPE_SET_INFO_T*)pv_data;

            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_SET;
            t_op_info.u.t_aud_set_info.e_aud_type = pt_aud_set_info->e_aud_type;
            t_op_info.u.t_aud_set_info.pv_set_info = (VOID*)pt_aud_set_info->pv_set_info;
            t_op_info.u.t_aud_set_info.z_size = pt_aud_set_info->z_size;
            t_op_info.u.t_aud_set_info.b_store = FALSE;

            break;
        }
        case DRV_CUSTOM_OPERATION_TYPE_VID_SET:
        {
            VID_TYPE_SET_INFO_T*    pt_vid_set_info = (VID_TYPE_SET_INFO_T*)pv_data;

            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
            t_op_info.u.t_vid_set_info.e_vid_type = pt_vid_set_info->e_vid_type;
            t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)pt_vid_set_info->pv_set_info;
            t_op_info.u.t_vid_set_info.z_size = pt_vid_set_info->z_size;
            t_op_info.u.t_vid_set_info.b_store = FALSE;

            break;
        }
        case DRV_CUSTOM_OPERATION_TYPE_MISC_SET:
        {
            MISC_TYPE_SET_INFO_T*    pt_misc_set_info = (MISC_TYPE_SET_INFO_T*)pv_data;

            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_MISC_SET;
            t_op_info.u.t_misc_set_info.e_misc_type = pt_misc_set_info->e_misc_type;
            t_op_info.u.t_misc_set_info.pv_set_info = (VOID*)pt_misc_set_info->pv_set_info;
            t_op_info.u.t_misc_set_info.z_size = pt_misc_set_info->z_size;
            t_op_info.u.t_misc_set_info.b_store = FALSE;

            break;
        }
        case DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET:
        {
            CUST_SPEC_TYPE_SET_INFO_T*    pt_cust_spec_set_info = (CUST_SPEC_TYPE_SET_INFO_T*)pv_data;

            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
            t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = pt_cust_spec_set_info->e_cust_spec_type;
            t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID*)pt_cust_spec_set_info->pv_set_info;
            t_op_info.u.t_cust_spec_set_info.z_size = pt_cust_spec_set_info->z_size;
            t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

            break;
        }
        case DRV_CUSTOM_OPERATION_TYPE_TUNER_SET:
        {
            TUNER_TYPE_SET_INFO_T*    pt_tuner_set_info = (TUNER_TYPE_SET_INFO_T*)pv_data;

            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_SET;
            t_op_info.u.t_tuner_set_info.e_tuner_type = pt_tuner_set_info->e_tuner_type;
            t_op_info.u.t_tuner_set_info.e_tuner_set_type = pt_tuner_set_info->e_tuner_set_type;
            t_op_info.u.t_tuner_set_info.pv_set_info = (VOID*)pt_tuner_set_info->pv_set_info;
            t_op_info.u.t_tuner_set_info.z_size = pt_tuner_set_info->z_size;

            break;
        }
        default:
            return APP_CFGR_OK;
    }

    /*set value to driver*/
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T)
                            );

    ACFG_LOG_ON_FAIL(i4_ret);

    return APP_CFGR_OK;
}

INT32 a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_op_info_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    switch(e_op_type)
    {
        case DRV_CUSTOM_OPERATION_TYPE_AUD_GET:
        {
            AUD_TYPE_GET_INFO_T*    pt_aud_get_info = (AUD_TYPE_GET_INFO_T*)pv_data;

            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_GET;
            t_op_info.u.t_aud_get_info.e_aud_type = pt_aud_get_info->e_aud_type;
            t_op_info.u.t_aud_get_info.pv_get_info = pt_aud_get_info->pv_get_info;
            t_op_info.u.t_aud_get_info.pz_size = pt_aud_get_info->pz_size;

            break;
        }
        case DRV_CUSTOM_OPERATION_TYPE_VID_GET:
        {
            VID_TYPE_GET_INFO_T*    pt_vid_get_info = (VID_TYPE_GET_INFO_T*)pv_data;

            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_GET;
            t_op_info.u.t_vid_get_info.e_vid_type = pt_vid_get_info->e_vid_type;
            t_op_info.u.t_vid_get_info.pv_get_info = pt_vid_get_info->pv_get_info;
            t_op_info.u.t_vid_get_info.pz_size = pt_vid_get_info->pz_size;

            break;
        }
        case DRV_CUSTOM_OPERATION_TYPE_MISC_GET:
        {
            MISC_TYPE_GET_INFO_T*    pt_misc_get_info = (MISC_TYPE_GET_INFO_T*)pv_data;

            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_MISC_GET;
            t_op_info.u.t_misc_get_info.e_misc_type = pt_misc_get_info->e_misc_type;
            t_op_info.u.t_misc_get_info.pv_get_info = pt_misc_get_info->pv_get_info;
            t_op_info.u.t_misc_get_info.pz_size = pt_misc_get_info->pz_size;

            break;
        }
        case DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET:
        {
            CUST_SPEC_TYPE_GET_INFO_T*    pt_cust_spec_get_info = (CUST_SPEC_TYPE_GET_INFO_T*)pv_data;

            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
            t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = pt_cust_spec_get_info->e_cust_spec_type;
            t_op_info.u.t_cust_spec_get_info.pv_get_info = pt_cust_spec_get_info->pv_get_info;
            t_op_info.u.t_cust_spec_get_info.pz_size = pt_cust_spec_get_info->pz_size;

            break;
        }
        case DRV_CUSTOM_OPERATION_TYPE_VID_GET_MIN_MAX:
        {
            VID_TYPE_GET_MIN_MAX_INFO_T*    pt_vid_get_min_max_info = (VID_TYPE_GET_MIN_MAX_INFO_T*)pv_data;

            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_GET_MIN_MAX;
            t_op_info.u.t_vid_get_min_max_info.e_vid_type = pt_vid_get_min_max_info->e_vid_type;
            t_op_info.u.t_vid_get_min_max_info.e_vid_inp = pt_vid_get_min_max_info->e_vid_inp;
            t_op_info.u.t_vid_get_min_max_info.pui2_max = pt_vid_get_min_max_info->pui2_max;
            t_op_info.u.t_vid_get_min_max_info.pui2_min = pt_vid_get_min_max_info->pui2_min;

            break;
        }
        case DRV_CUSTOM_OPERATION_TYPE_AUD_GET_MIN_MAX:
        {
            AUD_TYPE_GET_MIN_MAX_INFO_T*    pt_aud_get_min_max_info = (AUD_TYPE_GET_MIN_MAX_INFO_T*)pv_data;

            t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_GET_MIN_MAX;
            t_op_info.u.t_aud_get_min_max_info.e_aud_type = pt_aud_get_min_max_info->e_aud_type;
            t_op_info.u.t_aud_get_min_max_info.pi2_max = pt_aud_get_min_max_info->pi2_max;
            t_op_info.u.t_aud_get_min_max_info.pi2_min = pt_aud_get_min_max_info->pi2_min;

            break;
        }

        default:
            return APP_CFGR_INV_ARG;
    }

    /*get driver value */
    INT32 i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_op_info_size
                            );
    if( i4_ret != RMR_OK )
    {
        DBG_LOG_PRINT(("[ACFG]{%s, %d} Error: call c_rm_get_comp() failed ==> %d\n", __FUNCTION__,__LINE__, i4_ret));
        return APP_CFGR_NOT_SUPPORT;
    }

    return APP_CFGR_OK;    /*set value to driver*/
}

extern INT32 a_cfg_custom_set_acr(UINT16 ui2_value)
{
    INT32   i4_ret = APP_CFGR_OK;
    UINT8   ui1_acr_val = ui2_value;
    BOOL    b_file_exist = TRUE;
    BOOL    b_tos_pri_apply = FALSE;

    b_tos_pri_apply = (a_tv_custom_get_tos() && a_tv_custom_get_privacy());
    b_file_exist = (access("/tmp/inscape/cfg_ACR_disabled", 0) == 0 ? TRUE : FALSE);

    DBG_INFO(("\n a_cfg_custom_set_acr: %d b_file_exist:%d,b_tos_pri_apply:%d\n",
                ui2_value, b_file_exist, b_tos_pri_apply));

    i4_ret = acfg_set(IDX_CUSTOM_ACR_IDX, &ui1_acr_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    if (ACFG_ACR_OFF == ui2_value)
    {
#ifdef SAMBA_SUPPORT
        AP_SYSTEM_CALL("/3rd/samba/enable_samba.sh false &");
#endif
        if (!b_file_exist)
        {
            DBG_INFO(("\n%s,%s,%d,touch /tmp/inscape/cfg_ACR_disabled\n",
                        __FILE__, __FUNCTION__, __LINE__));
            AP_SYSTEM_CALL("touch /tmp/inscape/cfg_ACR_disabled");

#if defined(LINUX_TURNKEY_SOLUTION) && defined(TVIS_SUPPORT)
            a_tv_custom_reload_tvis_wrapper();
#endif
        }
        a_tv_custom_set_viewing_data_accepted(FALSE);
        a_tv_custom_set_viewing_data_show(FALSE);
    }
    else
    {
#ifdef SAMBA_SUPPORT
        if (b_tos_pri_apply) /* is TOS enable? */
        {
            AP_SYSTEM_CALL("/3rd/samba/enable_samba.sh true &");
        }
        else
        {
            AP_SYSTEM_CALL("/3rd/samba/enable_samba.sh false &");
        }
#endif
        if (b_file_exist && b_tos_pri_apply)
        {
            DBG_INFO(("\n%s,%s,%d,rm -f /tmp/inscape/cfg_ACR_disabled\n",
                        __FILE__, __FUNCTION__, __LINE__));
            AP_SYSTEM_CALL("rm -f /tmp/inscape/cfg_ACR_disabled");

#if defined(LINUX_TURNKEY_SOLUTION) && defined(TVIS_SUPPORT)
            a_tv_custom_reload_tvis_wrapper();
#endif
        }
        a_tv_custom_set_viewing_data_accepted(TRUE);
    }

    ACFG_COUNTRY_CODE_T t_country_code = ACFG_COUNTRY_CODE_US;

    a_cfg_custom_get_country_code(&t_country_code);

    if(a_tv_custom_get_viewing_data_accepted_by_oobe_menu())
    {
        b_tos_pri_apply = TRUE;
    }
    else
    {
        b_tos_pri_apply = FALSE;
    }

    a_nw_custom_get_http_url_for_acr(b_tos_pri_apply);
    return i4_ret;
}

extern INT32 a_cfg_custom_get_acr(UINT16 *pui2_val)
{
    SIZE_T      z_size;
    UINT8       ui1_acr_val;
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_ACR_IDX, &ui1_acr_val, &z_size);
    *pui2_val = ui1_acr_val;

    return i4_ret;
}

#ifdef TVIS_SUPPORT
static INT32 _acfg_custom_arc_get_mg_fw(VOID)
{
    CHAR s_mg[32] = {0};
    CHAR s_fw[32] = {0};
    CHAR s_tmp_buf[128] = {0};
    CHAR p_str[8] = {0};
    extern CHAR* sys_cust_get_usb_upg_version(VOID);

    CHAR  str_mg[32] = {0};

    FILE* fp=fopen("/proc/cmdline","r");
    if (fp)
    {
        while(!feof(fp) && fscanf(fp,"%30s",str_mg) == 1)
        {
            if (sscanf(str_mg,"MODELGROUP=%s",p_str) == 1)
            {
                break;
            }
        }
        fclose(fp);
    }
    c_strcpy(s_mg, "MG");
    c_strncat(s_mg, (c_strlen(p_str)>2 ? p_str+2 : "000"),31);
    s_mg[5] = 0;

    c_strncpy(s_fw, sys_cust_get_usb_upg_version(), (SIZE_T)31);

    DBG_INFO(("%s() Line %d: mg=[%s], fw=[%s]", __FUNCTION__,__LINE__,s_mg,s_fw));
    c_snprintf(s_tmp_buf, 128, "echo \"%s\" > /tmp/cfg_firmware_version", s_fw);
    AP_SYSTEM_CALL(s_tmp_buf);

    c_snprintf(s_tmp_buf, 128, "echo \"%s\" > /tmp/MG", s_mg);
    AP_SYSTEM_CALL(s_tmp_buf);

    return APP_CFGR_OK;
}
#endif

static INT32 _acfg_custom_acr_file_init()
{
    INT32 i4_ret = APP_CFGR_OK;

#ifdef TVIS_SUPPORT
    BOOL b_tos_pri_apply = FALSE;
    UINT16 ui2_val = 0;

    b_tos_pri_apply = (a_tv_custom_get_tos() && a_tv_custom_get_privacy());

    i4_ret = a_cfg_custom_get_acr(&ui2_val);

    ACFG_LOG_ON_FAIL(i4_ret);

    if (ACFG_ACR_OFF == ui2_val || !b_tos_pri_apply)
    {
        AP_SYSTEM_CALL("touch /tmp/inscape/cfg_ACR_disabled");
        DBG_INFO(("[APP CFG] %d set acr disabled.\n",__LINE__));
    }
    else
    {
        AP_SYSTEM_CALL("rm -f /tmp/inscape/cfg_ACR_disabled");
        DBG_INFO(("[APP CFG] %d set acr disabled.\n",__LINE__));
    }

    _acfg_custom_arc_get_mg_fw();
#endif
    return i4_ret;
}

extern INT32 a_cfg_custom_set_wifi_remote_pair_status(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_WIFI_REMOTE_PAIR_STATUS, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_custom_get_wifi_remote_pair_status(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_WIFI_REMOTE_PAIR_STATUS, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

/* for customer dns only */
/*
    0: ETH
    1: WIFI
*/
extern INT32 a_cfg_custom_set_dhcp_status(UINT8 ui1_dhcp_status, UINT8 ui1_idx)
{
    SIZE_T      z_size = sizeof(UINT16);
    INT32       i4_ret = APP_CFGR_OK;
    UINT16      ui2_curr_status = 0;

    i4_ret = acfg_get(IDX_CUSTOM_DHCP_STATUS, &ui2_curr_status, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /*
       High 00000000 -> Ethernet
       Low  00000000 -> WiFi
    */
    if (ui1_idx == 0)
    {
        ui2_curr_status = (UINT16)((ui1_dhcp_status << 8) | (ui2_curr_status & 0xff));
    }
    else
    {
        ui2_curr_status = (UINT16)((ui1_dhcp_status) | (ui2_curr_status & 0xff00));
    }

    DBG_INFO(("<ACFG> %s, LINE: %d, ui1_idx: %u, dhcp_status: %u\n", __FUNCTION__, __LINE__, ui1_idx, ui2_curr_status));

    i4_ret = acfg_set(IDX_CUSTOM_DHCP_STATUS, &ui2_curr_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_custom_get_dhcp_status(UINT8* pui1_dhcp_status, UINT8 ui1_idx)
{
    SIZE_T      z_size = sizeof(UINT16);
    INT32       i4_ret = APP_CFGR_OK;
    UINT16      ui2_curr_status = 0;

    i4_ret = acfg_get(IDX_CUSTOM_DHCP_STATUS, &ui2_curr_status, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /*
       High 00000000 -> Ethernet
       Low  00000000 -> WiFi
    */
    if (ui1_idx == 0)
    {
        *pui1_dhcp_status = (UINT8)(ui2_curr_status >> 8);
    }
    else
    {
        *pui1_dhcp_status = (UINT8)(ui2_curr_status & 0xff);
    }

    return i4_ret;
}

extern INT32 a_cfg_custom_set_reduce_blur(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;
    INT16   i2_val = (INT16)ui1_status;
    i4_ret = a_cfg_av_set (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_REDUCE_BLUR), i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

#ifdef APP_CUST_REDUCE_BLUR_SUPPORT
    a_cfg_odm_set_reduce_blur(ui1_status);
#endif
    return i4_ret;
}

extern INT32 a_cfg_custom_get_reduce_blur(UINT8 *pui1_val)
{
    INT32       i4_ret = APP_CFGR_OK;
    INT16       i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_REDUCE_BLUR), &i2_val);
    *pui1_val = (UINT8)i2_val;

    return i4_ret;
}

extern INT32 a_cfg_custom_update_reduce_blur(UINT8 ui1_value)
{
    INT32       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

#ifdef APP_CUST_REDUCE_BLUR_SUPPORT
    a_cfg_odm_update_reduce_blur(ui1_value);
#endif

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_DISP_TYPE_REDUCE_BLUR;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)&ui1_value;
    t_op_info.u.t_vid_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_vid_set_info.b_store = FALSE;

    /*set value to driver*/
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T)
                            );
    ACFG_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("\n<ACFG> %s() Line %d: ui1_value = %d, i4_ret = %d\n", __FUNCTION__,
                                                                       __LINE__,
                                                                       ui1_value,
                                                                       i4_ret));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));

    return i4_ret;
}

UINT16 a_cfg_cust_get_panel_max_freq(void)
{
#if( defined(MT5695_MODEL)||defined(MT5695L_MODEL) )

    return 120;

#else

    UINT16 u16PanelMaxFreq = 60;

    EnuCusModelSeries eCusModelSeries = a_cfg_cust_get_CurModelSeries();
    switch(eCusModelSeries)
    {
      #if( defined(MT5695_MODEL)||defined(MT5695L_MODEL) )
        // 120Hz
        case CUS_MODEL_2020_95_P9:   // 5, P***9-H**: P65Q9-H1
        case CUS_MODEL_2020_95_PX:   // 6, P***X-H*: P75QX-H1
        case CUS_MODEL_2021_95_P9:   // 15, P***9-J**: P65Q9-J01
        case CUS_MODEL_2021_95_PX:   // 16, P***X-J**:
            {
                u16PanelMaxFreq = 120;
            }
            break;
      #endif

        default: // 60Hz
            {
                u16PanelMaxFreq = 60;
            }
            break;
    }

    return u16PanelMaxFreq;
#endif
}

static BOOL _is_DVI_signal(void)
{
    if( SCC_VID_HDMI_DVI_MODE_DVI == a_cfg_custom_get_hdmi_dvi_signal() )
        return TRUE;
    else
        return FALSE;
}

BOOL a_cfg_cust_FilmMode_CheckIfCanTurnOn(void)
{
    if( _is_DVI_signal() )
    {
        //ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_FILM_MODE,
            DBG_LOG_PRINT(("[ACFG][FilmMode]{%s:%d} DVI signal => FilmMode cannot turn on\n", __FUNCTION__, __LINE__));
        //);
        return FALSE;
    }

#if 1//(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    if( acfg_cust_Is_CurHDMI_PQ_PCMode() == TRUE )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_FILM_MODE,
            DBG_LOG_PRINT(("[ACFG][FilmMode]{%s:%d} PC mode => FilmMode cannot turn on\n", __FUNCTION__, __LINE__));
        );

        return FALSE;
    }
#endif


    //DTV02170653
    //if P series, panel is 120 HZ, spec had flow
    //Film Mode is available for 120 Hz panel for detection of film content only. Not disabled nor grayout with MEMC or Game Low Latency.
    //60 Hz television, if Game Low Latency is turned on, and Film Mode is On then is Film Mode turned off temporarily.
    if( (a_acfg_cust_is_gll_enable() == TRUE)
      &&(a_cfg_cust_get_panel_max_freq() == 60 )//s_name[0] != 'P')
      )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_FILM_MODE,
            DBG_LOG_PRINT(("[ACFG][FilmMode]{%s:%d} Gll enable => FilmMode cannot turn on\n", __FUNCTION__, __LINE__));
        );
        return FALSE;
    }

    return TRUE;
}

extern INT32 a_cfg_custom_update_film_mode(UINT8 ui1_value)
{
    INT32 i4_ret = MENUR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;

    //60 Hz television, if Game Low Latency is turned on, and Film Mode is On then is Film Mode turned off temporarily.
    if( ui1_value != 0 ) // Want to turn on film_mode
    {
        //if(a_acfg_cust_is_gll_enable())
        if( FALSE == a_cfg_cust_FilmMode_CheckIfCanTurnOn() )
        {
            ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_FILM_MODE,
                DBG_LOG_PRINT(("[ACFG][FilmMode]{%s:%d} Force FilmMode off\n", __FUNCTION__, __LINE__));
            );

            ui1_value = 0;
        }
    }


    c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    ACFG_DBG_INFO("Set ui1_value :%d \r\n",ui1_value);


    ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_FILM_MODE,
        DBG_LOG_PRINT(("[ACFG][FilmMode]{%s:%d} Set drvier: FilmMode=%d\n", __FUNCTION__, __LINE__, ui1_value));
    );

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_DISP_TYPE_UI_PURE_CINEMA;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)&ui1_value;
    t_op_info.u.t_vid_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_vid_set_info.b_store = FALSE;

    /*set value to driver*/
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T)
                            );
    ACFG_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_custom_is_reduce_blur_support(BOOL *pb_support)
{
    *pb_support = FALSE;
    return APP_CFGR_OK;
}

extern INT32 a_cfg_custom_set_miracast_enable_status(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_MIRACAST_ENABLE_STATUS, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_custom_get_miracast_enable_status(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_MIRACAST_ENABLE_STATUS, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_custom_set_last_p2p0_op_channel(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_LAST_P2P0_OP_CHANNEL, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_custom_get_last_p2p0_op_channel(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_LAST_P2P0_OP_CHANNEL, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_custom_set_usb_powersaving(VOID)
{
    INT32   i4_ret = APP_CFGR_OK;

    AP_SYSTEM_CALL_EX("sh /etc/scripts/wifi_direct_suspend.sh",i4_ret);
    DBG_INFO(("WiFi dongle suspend mode return= %d\n", i4_ret));
    return i4_ret;
}

INT32 a_cfg_custom_set_main_menu_pre_item(UINT8 ui1_idx)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_MAIN_MENU_PRE_ITEM, &ui1_idx, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_get_main_menu_pre_item(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_MAIN_MENU_PRE_ITEM, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_custom_set_vol_control(UINT8 ui1_value)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_VOL_CONTROL, &ui1_value, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_custom_update_vol_control();
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_custom_get_vol_control(UINT8 *pui1_val)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_VOL_CONTROL, pui1_val, &z_size);

    return i4_ret;
}

extern INT32 a_cfg_custom_update_vol_control(VOID)
{
    INT32       i4_ret = APP_CFGR_OK;
    SIZE_T      z_size;
    UINT8       ui1_value = 0;
    CHAR        s_type_name[32]   = {0};
    CHAR        s_brand_name[32]  = {0};
    CHAR        s_model_name[32]  = {0};
    CHAR        s_codeset[6]      = {0};

    i4_ret = acfg_get(IDX_CUSTOM_VOL_CONTROL, &ui1_value, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    if (a_cfg_custom_get_wifi_remote_support())
    {
        a_cfg_custom_get_device_info(0, s_type_name, s_brand_name, s_model_name, s_codeset);
        if (c_strcmp(s_codeset, "") != 0)
        {
            a_tv_net_custom_set_soundbar_codeset(s_codeset);
        }

        if (ui1_value == 0)
        {
            a_tv_net_custom_set_soundbar_flag(FALSE);
        }
        else
        {
            a_tv_net_custom_set_soundbar_flag(TRUE);
        }
    }

    return i4_ret;
}


extern INT32 a_cfg_custom_set_scrn_saver_time(UINT16 ui2_val)
{
    UINT8   ui1_scrn_saver_time = 0;

    switch (ui2_val)
    {
        case 0:
            ui1_scrn_saver_time = ACFG_CUSTOM_SCRN_BLANK_DISABLE;
            break;
        case 1:
            ui1_scrn_saver_time = ACFG_CUSTOM_SCRN_BLANK_2MIN;
            break;
        case 2:
            ui1_scrn_saver_time = ACFG_CUSTOM_SCRN_BLANK_10MIN;
            break;
        case 3:
            ui1_scrn_saver_time = ACFG_CUSTOM_SCRN_BLANK_20MIN;
            break;
        default:
            ui1_scrn_saver_time = ACFG_CUSTOM_SCRN_BLANK_DISABLE;
            break;
    }

    return acfg_set(IDX_CUSTOM_SCRN_SAVER_TIME, &ui1_scrn_saver_time, 1);
}

extern INT32 a_cfg_custom_get_scrn_saver_time(UINT16 *pui2_val)
{
    INT32   i4_ret = APP_CFGR_OK;
    UINT8   ui1_scrn_saver_time = 0;
    SIZE_T  z_size = sizeof(UINT8);

    acfg_get(IDX_CUSTOM_SCRN_SAVER_TIME, &ui1_scrn_saver_time, &z_size);

    switch (ui1_scrn_saver_time)
    {
        case 0:
            *pui2_val = ACFG_CUSTOM_SCRN_BLANK_DISABLE;
            break;
        case 1:
            *pui2_val = ACFG_CUSTOM_SCRN_BLANK_2MIN;
            break;
        case 2:
            *pui2_val = ACFG_CUSTOM_SCRN_BLANK_10MIN;
            break;
        case 3:
            *pui2_val = ACFG_CUSTOM_SCRN_BLANK_20MIN;
            break;
        default:
            *pui2_val = ACFG_CUSTOM_SCRN_BLANK_DISABLE;
            break;
    }

    return i4_ret;
}

extern INT32 a_cfg_custom_set_pic_quality_page(UINT16 ui2_val)
{
    UINT8   ui1_pic_quality_page = 0;

    switch (ui2_val)
    {
        case 0:
            ui1_pic_quality_page = ACFG_CUSTOM_COLOR_TUNER;
            break;
        case 1:
            ui1_pic_quality_page = ACFG_CUSTOM_11_PIONT_GAIN;
            break;
        case 2:
            ui1_pic_quality_page = ACFG_CUSTOM_SMPTE_TEST_PATTERNS;
            break;
        case 3:
            ui1_pic_quality_page = ACFG_CUSTOM_FLAT_TEST_PATTERNS;
            break;
        case 4:
            ui1_pic_quality_page = ACFG_CUSTOM_RAMP_TEST_PATTERNS;
            break;
    #ifdef APP_CAST_TEST_PATTERN
        case 5:
            ui1_pic_quality_page = ACFG_CUSTOM_UNIFORMITY_ANALYZER_TEST_PATTERNS;
            break;
    #endif
        default:
            ui1_pic_quality_page = ACFG_CUSTOM_COLOR_TUNER;
            break;
    }

    return acfg_set(IDX_CUSTOM_PIC_QUALITY_ADJUST_PAGE, &ui1_pic_quality_page, 1);
}

extern INT32 a_cfg_custom_get_pic_quality_page(UINT16 *pui2_val)
{
    INT32   i4_ret = APP_CFGR_OK;
    UINT8   ui1_pic_quality_page = 0;
    SIZE_T  z_size = sizeof(UINT8);

    acfg_get(IDX_CUSTOM_PIC_QUALITY_ADJUST_PAGE, &ui1_pic_quality_page, &z_size);

    switch (ui1_pic_quality_page)
    {
        case 0:
            *pui2_val = ACFG_CUSTOM_COLOR_TUNER;
            break;
        case 1:
            *pui2_val = ACFG_CUSTOM_11_PIONT_GAIN;
            break;
        case 2:
            *pui2_val = ACFG_CUSTOM_SMPTE_TEST_PATTERNS;
            break;
        case 3:
            *pui2_val = ACFG_CUSTOM_FLAT_TEST_PATTERNS;
            break;
        case 4:
            *pui2_val = ACFG_CUSTOM_RAMP_TEST_PATTERNS;
            break;
    #ifdef APP_CAST_TEST_PATTERN
        case 5:
            *pui2_val = ACFG_CUSTOM_UNIFORMITY_ANALYZER_TEST_PATTERNS;
            break;
    #endif
        default:
            *pui2_val = ACFG_CUSTOM_COLOR_TUNER;
            break;
    }

    return i4_ret;
}

#ifdef APP_MENU_3D_BRIGHTNESS_BOOST
extern INT32 a_cfg_custom_set_3d_brightness_boost(UINT16 ui2_value)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_3D_BRIGHTNESS_BOOST, &ui2_value, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return i4_ret;
}

extern INT32 a_cfg_custom_get_3d_brightness_boost(UINT16 *pui2_val)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_3D_BRIGHTNESS_BOOST, pui2_val, &z_size);

    return i4_ret;
}
#endif

extern INT32 a_cfg_custom_set_lang_select(UINT16 ui2_value)
{
    INT32   i4_ret = APP_CFGR_OK;
    SIZE_T  z_size = sizeof(ui2_value);

    i4_ret = acfg_set(IDX_CUSTOM_LANG_SELECT, &ui2_value, z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return i4_ret;
}

extern INT32 a_cfg_custom_get_lang_select(UINT16 *pui2_val)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_LANG_SELECT, pui2_val, &z_size);

    return i4_ret;
}

extern INT32 a_cfg_custom_set_country_select(UINT16 ui2_value)
{
    INT32   i4_ret = APP_CFGR_OK;
    SIZE_T  z_size = sizeof(ui2_value);

    i4_ret = acfg_set(IDX_CUSTOM_COUNTRY_SELECT, &ui2_value, z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return i4_ret;
}

extern INT32 a_cfg_custom_get_country_select(UINT16 *pui2_val)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_COUNTRY_SELECT, pui2_val, &z_size);

    return i4_ret;
}

extern INT32 a_cfg_custom_set_tz_select(UINT16 ui2_value)
{
    INT32   i4_ret = APP_CFGR_OK;
    SIZE_T  z_size = sizeof(ui2_value);

    i4_ret = acfg_set(IDX_CUSTOM_TIMEZONE_SELECT, &ui2_value, z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return i4_ret;
}

extern INT32 a_cfg_custom_get_tz_select(UINT16 *pui2_val)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_TIMEZONE_SELECT, pui2_val, &z_size);

    return i4_ret;
}


#define _ACFG_SET_REGION(pt_reg, x, y, w, h)               \
    do {                                                   \
        (pt_reg)->ui4_x      = x;                          \
        (pt_reg)->ui4_y      = y;                          \
        (pt_reg)->ui4_width  = w;                          \
        (pt_reg)->ui4_height = h;                          \
    } while (0)
static INT32 a_cfg_get_disp_region_by_viewport (
        APP_CFG_VIEWPORT_TYPE_T e_curr_viewport,
        VSH_REGION_INFO_T* pt_disp_region)
{
    if (a_cfg_get_app_status () == APP_CFG_APP_STATUS_MENU_WIDE_MODE)
    {
        _ACFG_SET_REGION (pt_disp_region, 0, 0, VSH_REGION_MAX_WIDTH, VSH_REGION_MAX_HEIGHT);

        return APP_CFGR_OK;
    }
    switch (e_curr_viewport)
    {
    case APP_CFG_VIEWPORT_TYPE_VIEWPORT:
        _ACFG_SET_REGION (pt_disp_region, 3333, 1666, 6667, (VSH_REGION_MAX_WIDTH-1666*2));
        break;
    case APP_CFG_VIEWPORT_TYPE_CENTER_OVERLAY:
        _ACFG_SET_REGION (pt_disp_region, 1615, 0, VSH_REGION_MAX_WIDTH, VSH_REGION_MAX_HEIGHT);
        break;
    default:
        _ACFG_SET_REGION (pt_disp_region, 0, 0, VSH_REGION_MAX_WIDTH, VSH_REGION_MAX_HEIGHT);
        break;
    }

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_recover_viewport_by_tv(UINT8 i1_viewport_type)
    {
        INT32 i4_ret;
        APP_CFG_VIEWPORT_T t_curr_viewport;
        VSH_REGION_INFO_T t_disp_region;

        if (i1_viewport_type<1 || i1_viewport_type > 2) /*invalid value*/
        {
            i4_ret = a_cfg_get_viewport (&t_curr_viewport);
            if (i4_ret != APP_CFGR_OK)
            {
                return i4_ret;
            }
            i1_viewport_type = t_curr_viewport.e_type;
        }

        a_cfg_get_disp_region_by_viewport (i1_viewport_type, &t_disp_region);

        t_curr_viewport.e_type = i1_viewport_type;
        t_curr_viewport.i4_x = (INT32)(t_disp_region.ui4_x*1920/VSH_REGION_MAX_WIDTH);
        t_curr_viewport.i4_y = (INT32)(t_disp_region.ui4_y*1080/VSH_REGION_MAX_HEIGHT);
        t_curr_viewport.i4_w = (INT32)(t_disp_region.ui4_width*1920/VSH_REGION_MAX_WIDTH);
        t_curr_viewport.i4_h = (INT32)(t_disp_region.ui4_height*1080/VSH_REGION_MAX_HEIGHT);

        a_cfg_set_viewport (&t_curr_viewport);

        return APP_CFGR_OK;
    }

/*-----------------------------------------------------------------------------
 * Name: a_cfg_chk_lock_pic_mode_password
 *
 * Description:
 *
 * Inputs: -
 *      w2s_pwd_chk - password to be checked. This unicode string shall NULL-
 *                    terminated string.
 * Outputs:
 *      pb_pass     - if the password is valid
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG         - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
extern INT32  a_cfg_chk_lock_pic_mode_password(UTF16_T* w2s_pwd_chk,
                                 BOOL* pb_pass)
{
    INT32       i4_ret = 0;
    CHAR        s_password[APP_CFG_MAX_PWD_LEN+1] = {0};
    UTF16_T     w2s_password[APP_CFG_MAX_PWD_LEN+1]= {0};
    UTF16_T     w2s_master_code[APP_CFG_MAX_PWD_LEN+1] = L"5351";

    if (pb_pass == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    c_memset(w2s_password, 0, sizeof(w2s_password));

    i4_ret = a_cfg_cust_get_cust_pic_mode_lock_pwd(s_password, APP_CFG_MAX_PWD_LEN);
    if (i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    c_uc_ps_to_w2s(s_password,w2s_password,APP_CFG_MAX_PWD_LEN);

    if (c_uc_w2s_strcmp(w2s_pwd_chk, w2s_password) == 0)
    {
        *pb_pass = TRUE;
    }
    else if (c_uc_w2s_strcmp(w2s_pwd_chk, w2s_master_code) == 0)
    {
        *pb_pass = TRUE;
    }
    else
    {
        *pb_pass = FALSE;
    }

    return APP_CFGR_OK;
}
extern INT32  a_cfg_get_cust_pic_lock_status( BOOL* pb_is_lock)
{
    INT32   i4_ret;
    SIZE_T  z_size;
    UINT8   ui1_lock = 0;

    if(pb_is_lock == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUST_PIC_LOCK_STATUS,
                      &ui1_lock,
                      &z_size);
    if(i4_ret == APP_CFGR_OK)
    {
        *pb_is_lock = ui1_lock;
    }

    return i4_ret;
}
extern INT32  a_cfg_set_cust_pic_lock_status( BOOL b_is_lock)
{
    INT32   i4_ret;
    SIZE_T  z_size = 1;
    UINT8   ui1_lock = (UINT8)b_is_lock;

    i4_ret = acfg_set(IDX_CUST_PIC_LOCK_STATUS,
                      &ui1_lock,
                      z_size);

    return i4_ret;
}


extern  INT32 a_cfg_cust_set_flat_test_pattern(UINT8 ui1_OnOff, UINT8 ui2_Ydata)
{
    DRV_CUSTOM_SCE_PATTERN_T CPattern = {1, 0};
    INT32       i4_ret;

    /* set values to acfg */

    /* update */
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    CPattern.ui1_OnOff = ui1_OnOff;
    CPattern.ui2_Ydata = ui2_Ydata;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_SCE_PATTERN;
    t_op_info.u.t_vid_set_info.pv_set_info = &CPattern;
    t_op_info.u.t_vid_set_info.z_size = sizeof(DRV_CUSTOM_SCE_PATTERN_T);
    t_op_info.u.t_vid_set_info.b_store = FALSE;


    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size);

    return i4_ret;
}

extern INT32 a_cfg_cust_set_smpte_test_pattern(UINT8 ui1_val)
{
    INT32       i4_ret;

    /* update */
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_PRE_PATTERN;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)(&ui1_val);
    t_op_info.u.t_vid_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_vid_set_info.b_store = FALSE;


    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size);


    return i4_ret;
}


extern INT32 a_cfg_cust_set_ramp_test_pattern(UINT8 ui1_val)
{
    INT32       i4_ret;
    /* update */
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_PRE_PATTERN;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)(&ui1_val);
    t_op_info.u.t_vid_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_vid_set_info.b_store = FALSE;


    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size);

    return i4_ret;
}


extern INT32 a_cfg_cust_clr_tuner_update_unit_value(VOID)
{
      INT32       i4_ret;

      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_R));
      ACFG_CHK_FAIL(i4_ret, i4_ret);

      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_G));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_B));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_R));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_G));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_B));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_R));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_G));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_B));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_C));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_M));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_Y));
      ACFG_CHK_FAIL(i4_ret, i4_ret);

      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_C));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_M));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_Y));
      ACFG_CHK_FAIL(i4_ret, i4_ret);

      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_C));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_M));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_Y));
      ACFG_CHK_FAIL(i4_ret, i4_ret);

      i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
      ACFG_CHK_FAIL(i4_ret, i4_ret);
      return i4_ret;
}
extern INT32 a_cfg_cust_create_pic_mode(VOID)
{
    INT16                       i2_cust_pic_exist = 0;
    UINT16                      ui2_count = 0;
    INT32                       i4_ret = 0;
    UINT8                       ui1_input_grp = 0;
    INT16                       i2_pic_mode = 0;
    INT16                       i2_cust_pic = 0;
    UINT16                      ui2_elem_idx = 0;

    /* get crnt pic mode*/
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),&i2_pic_mode);

    if (i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
    {
        DBG_ERROR(("\na_cfg_cust_create_pic_mode() refuse for cust pic mode!!!\n"));
        return APP_CFGR_INV_ARG;
    }

    /* here should use the glob cust pic mode input src: */
    ui1_input_grp = ACFG_VID_SETTINS_GLOBAL_IPT_SRC;

    /* first get the crnt src unuse cust pic mode*/
    for (ui2_count = 0; ui2_count < ACFG_CUST_SET_PIC_MODE_NUM_EX; ui2_count++)
    {
        ui2_elem_idx = ui1_input_grp*ACFG_CUST_SET_PIC_MODE_NUM + ui2_count;

        acfg_get_int16_by_idx(IDX_CUST_PIC_EXIST_STATUS,ui2_elem_idx,&i2_cust_pic_exist);

        if (0 == i2_cust_pic_exist)
        {
            i2_cust_pic_exist = 1;
            break;
        }
    }

    if (ui2_count >= ACFG_CUST_SET_PIC_MODE_NUM_EX)
    {
        DBG_ERROR( ("\na_cfg_cust_create_pic_mode() extern max!!!\n"));
        return APP_CFGR_INV_ARG;
    }

    /* set this cust pic mode exist*/
    i4_ret = acfg_set_int16_by_idx(IDX_CUST_PIC_EXIST_STATUS,ui2_elem_idx,i2_cust_pic_exist);
    ACFG_LOG_ON_FAIL(i4_ret);

    /* get crnt pic mode*/
    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),&i2_pic_mode);
    ACFG_LOG_ON_FAIL(i4_ret);

    /* set this cust pic mode BASE PIC*/
    i4_ret = acfg_set_int16_by_idx(IDX_CUST_PIC_COPY_BASE,ui2_elem_idx,i2_pic_mode);
    ACFG_LOG_ON_FAIL(i4_ret);

    /*cust pic mode */
    i2_cust_pic = ACFG_PRE_SET_PIC_MODE_NUM + ui2_count;
    DBG_INFO(("[ACFG][%s %d] i2_cust_pic = %d\n",__FUNCTION__,__LINE__,i2_cust_pic));

    i4_ret = a_cfg_cust_copy_pic_mode_to_pic_mode(i2_pic_mode,i2_cust_pic);
    ACFG_LOG_ON_FAIL(i4_ret);

    /* set crnt pic mode to the create custom and update it*/
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),i2_cust_pic);
    ACFG_LOG_ON_FAIL(i4_ret);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    return APP_CFGR_OK;
}

extern INT32 a_cfg_cust_delete_pic_mode(VOID)
{
    INT16                       i2_cust_pic_exist = 0;
    INT16                       i2_value = 0;
    INT16                       i2_pic_mode = 0;

    /* get crnt pic mode*/
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),&i2_pic_mode);

    if (i2_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM)
    {
        DBG_ERROR( ("\na_cfg_cust_delete_pic_mode(fail) not cust pic mode!!!\n"));

        return APP_CFGR_INV_ARG;
    }

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_PIC_EXIST_STATUS),i2_cust_pic_exist);

    /* set this cust pic mode BASE PIC*/
    i2_pic_mode = 0;
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CUST_PIC_COPY_BASE),i2_pic_mode);

    i2_value = 0;

    /* cust CLR TEMP elem idx*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP),i2_value);

    ////////////////////////////
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_DISP,  APP_CFG_RECID_DISP_BACK_LIGHT),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT),i2_value);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_MODE),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR),i2_value);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FLESH_TONE),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR),i2_value);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_REDUCE_BLUR), i2_value);


    return APP_CFGR_OK;
}

extern INT32 a_cfg_cust_get_cust_pic_mode_name(INT16 i2_pic_mode, CHAR* ps_pic_mode_name,UINT32 ui4_length)
{

     UINT8         pt_values[ACFG_MAX_REC_SIZE] = {0};
     UINT16        ui2_idx = 0;
     UINT16        ui2_idx_int = 0;
     INT32         i4_ret = 0;
     ISL_REC_T     t_isl_rec;
     UINT16        ui2_ipt = 0;
     UINT8         ui1_input = 0;
     CHAR          s_disp_name[ACFG_MAX_DISP_NAME+1];
     UINT16        ui2_off = 0;
     SIZE_T        z_size = ACFG_MAX_REC_SIZE;

     UINT32        ui4_length_cpy = 0;
     if ((i2_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM)
        || (ui4_length <= 0)
        || (!ps_pic_mode_name))
     {
         DBG_ERROR( ("\na_cfg_cust_get_cust_pic_mode_name() pic_mode[%d],ui4_length[%d] INV_ARG!!!\n",i2_pic_mode,ui4_length));
         return APP_CFGR_INV_ARG;
     }

     i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
     ACFG_CHK_FAIL(i4_ret, i4_ret);

     i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
     ACFG_CHK_FAIL(i4_ret, i4_ret);

     a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);

     ui2_ipt = acfg_custom_get_input_grp(&t_isl_rec);


     /* here should use the glob cust pic mode input src: hdmi1*/
     ui2_ipt = ACFG_VID_SETTINS_GLOBAL_IPT_SRC;

     ui2_idx = IDX_CUST_PIC_MODE_0_NAME + i2_pic_mode - ACFG_PRE_SET_PIC_MODE_NUM;

     acfg_get(ui2_idx,(VOID*)pt_values,&z_size);

     ui2_off = ui2_ipt*APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;

     if (ui4_length > APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN)
     {
        ui4_length_cpy = APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;
     }
     else
     {
         ui4_length_cpy = ui4_length;
     }

     for (ui2_idx_int = 0; ui2_idx_int < ui4_length_cpy ; ui2_idx_int ++)
     {
         ps_pic_mode_name[ui2_idx_int] = pt_values[ui2_off + ui2_idx_int];
     }

     ps_pic_mode_name[ui4_length_cpy-1] = '\0';

     DBG_INFO(("\n******%s(%d)ps_pic_mode_name=%s\n",__FUNCTION__,__LINE__,ps_pic_mode_name));

     return APP_CFGR_OK;

}
extern INT32 a_cfg_cust_set_cust_pic_mode_name(INT16 i2_pic_mode, CHAR* ps_pic_mode_name)
{

     UINT8         pt_values[ACFG_MAX_REC_SIZE] = {0};
     UINT16        ui2_idx = 0;
     UINT16        ui2_idx_int = 0;
     INT32         i4_ret = 0;
     ISL_REC_T     t_isl_rec;
     UINT16        ui2_ipt = 0;
     UINT8         ui1_input = 0;
     CHAR          s_disp_name[ACFG_MAX_DISP_NAME+1];
     UINT16        ui2_off = 0;
     SIZE_T        z_size = APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM;

     UINT32        ui4_length = 0;
     UINT32        ui4_length_cpy = 0;
     if ((i2_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM)
        || (!ps_pic_mode_name))
     {
         DBG_ERROR( ("\na_cfg_cust_get_cust_pic_mode_name() pic_mode[%d] INV_ARG!!!\n",i2_pic_mode));
         return APP_CFGR_INV_ARG;
     }

     i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
     ACFG_CHK_FAIL(i4_ret, i4_ret);

     i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
     ACFG_CHK_FAIL(i4_ret, i4_ret);

     a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);

     ui2_ipt = acfg_custom_get_input_grp(&t_isl_rec);

     /* here should use the glob cust pic mode input src: hdmi1*/
     ui2_ipt = ACFG_VID_SETTINS_GLOBAL_IPT_SRC;

     ui2_idx = IDX_CUST_PIC_MODE_0_NAME + i2_pic_mode - ACFG_PRE_SET_PIC_MODE_NUM;

     acfg_get(ui2_idx,(VOID*)pt_values,&z_size);

     ui2_off = ui2_ipt*APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;

     ui4_length = c_strlen(ps_pic_mode_name);

     if (ui4_length >= APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN)
     {
        ui4_length_cpy = APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;
     }
     else
     {
         ui4_length_cpy = ui4_length +1;
     }

     for (ui2_idx_int = 0; ui2_idx_int < ui4_length_cpy; ui2_idx_int ++)
     {
         pt_values[ui2_off + ui2_idx_int]= ps_pic_mode_name[ui2_idx_int];
     }


     acfg_set(ui2_idx,(VOID*)pt_values,z_size);

     return APP_CFGR_OK;

}

extern INT32 a_cfg_cust_get_cust_pic_mode_lock_status(BOOL* pb_is_lock)
{
     UINT8         ui1_values = 0;
     SIZE_T        z_size = sizeof(UINT8);

     if (!pb_is_lock)
     {
         DBG_ERROR( ("\na_cfg_cust_get_cust_pic_mode_lock_status()INV_ARG!!!\n"));
         return APP_CFGR_INV_ARG;
     }

     acfg_get(IDX_CUST_PIC_LOCK_STATUS,&ui1_values,&z_size);

     *pb_is_lock = (BOOL)ui1_values;
     return APP_CFGR_OK;
}
extern INT32 a_cfg_cust_set_cust_pic_mode_lock_status(BOOL b_is_lock)
{
     UINT8         ui1_values = (UINT8)b_is_lock;
     SIZE_T        z_size = 1;

     acfg_set(IDX_CUST_PIC_LOCK_STATUS,&ui1_values,z_size);

     return APP_CFGR_OK;
}

extern INT32 a_cfg_cust_get_cust_pic_mode_exist_status(INT16 i2_pic_mode, BOOL* pb_is_exist)
{

     UINT8         pt_values[ACFG_MAX_REC_SIZE] = {0};
     INT32         i4_ret = 0;
     ISL_REC_T     t_isl_rec;
     UINT16        ui2_ipt = 0;
     UINT8         ui1_input = 0;

     UINT8         ui1_exist_value = 0;
     CHAR          s_disp_name[ACFG_MAX_DISP_NAME+1];
     UINT16        ui2_off = 0;
     SIZE_T        z_size = ACFG_CUST_SET_PIC_MODE_NUM;

     if ((i2_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM)
        || (!pb_is_exist))
     {
         DBG_ERROR( ("\n a_cfg_cust_get_cust_pic_mode_exist_status() pic_mode[%d] INV_ARG!!!\n",i2_pic_mode));
         return APP_CFGR_INV_ARG;
     }

     i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
     ACFG_CHK_FAIL(i4_ret, i4_ret);

     i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
     ACFG_CHK_FAIL(i4_ret, i4_ret);

     a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);

     ui2_ipt = acfg_custom_get_input_grp(&t_isl_rec);

     /* here should use the glob cust pic mode input src: hdmi1*/
     ui2_ipt = ACFG_VID_SETTINS_GLOBAL_IPT_SRC;

     acfg_get(IDX_CUST_PIC_EXIST_STATUS,(VOID*)pt_values,&z_size);

     ui2_off = ui2_ipt*ACFG_CUST_SET_PIC_MODE_NUM + i2_pic_mode - ACFG_PRE_SET_PIC_MODE_NUM;
     ui1_exist_value = pt_values[ui2_off];
     *pb_is_exist = (BOOL)ui1_exist_value;

     return APP_CFGR_OK;

}
extern INT32  a_cfg_cust_get_cust_pic_mode_lock_pwd(CHAR* ps_pwd, UINT32 ui4_length)
{

    UINT8         pt_values[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN] = {0};
    SIZE_T        z_size = APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;

    UINT16        ui2_idx = 0;

    acfg_get(IDX_CUST_PIC_LOCK_PWD,(VOID*)pt_values,&z_size);

    if (ui4_length >= APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN)
    {
        ui4_length = APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;
    }

    for (ui2_idx = 0; ui2_idx < ui4_length - 1; ui2_idx ++)
    {
        ps_pwd[ui2_idx] = pt_values[ui2_idx];
    }

    ps_pwd[ui4_length - 1] = '\0';


    return APP_CFGR_OK;
}

extern INT32  a_cfg_cust_set_cust_pic_mode_lock_pwd(CHAR* ps_pwd,UINT32 ui4_length)
{

    UINT8         pt_values[APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN] = {0};
    SIZE_T        z_size = APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;

    UINT16        ui2_idx = 0;

    acfg_get(IDX_CUST_PIC_LOCK_PWD,(VOID*)pt_values,&z_size);

    if (ui4_length >= APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN)
    {
        ui4_length = APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;
    }

    for (ui2_idx = 0; ui2_idx < ui4_length - 1; ui2_idx ++)
    {
        pt_values[ui2_idx] = ps_pwd[ui2_idx];
    }

    pt_values[ui4_length - 1] = '\0';

    z_size = APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN;

    acfg_set(IDX_CUST_PIC_LOCK_PWD,(VOID*)pt_values,z_size);

    return APP_CFGR_OK;
}

extern INT32 a_cfg_cust_create_cust_aud_mode(VOID)
{
    INT16   i2_aud_mode_usage = 1;

    INT16   i2_sound_mode = 0;

    acfg_set(IDX_CUST_AUD_MODE_EXIST,(VOID*)(&i2_aud_mode_usage),1);

    i2_sound_mode = ACFG_CUST_PRESET_AUD_MODE_NUM + 1;

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE),
                 i2_sound_mode);

    return APP_CFGR_OK;
}

extern INT32 a_cfg_cust_delete_cust_aud_mode(VOID)
{
    INT16   i2_sound_mode = 0;
    INT16   i2_aud_mode_usage = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE),
                 &i2_sound_mode);

    if (i2_sound_mode < ACFG_CUST_PRESET_AUD_MODE_NUM)
    {
        return APP_CFGR_INV_ARG;
    }

    acfg_set(IDX_CUST_AUD_MODE_EXIST,(VOID*)(&i2_aud_mode_usage),1);

    return APP_CFGR_OK;
}

extern INT32 a_cfg_cust_get_cust_nw_register_status(UINT8* pui1_reg_status)
{
     UINT8         ui1_values = 0;
     SIZE_T        z_size = sizeof(UINT8);

     if (!pui1_reg_status)
     {
         return APP_CFGR_INV_ARG;
         DBG_ERROR( ("\na_cfg_cust_get_cust_pic_mode_lock_status()INV_ARG!!!\n"));
     }

     acfg_get(IDX_CUST_NW_REG_STATUS,&ui1_values,&z_size);

     *pui1_reg_status = (UINT8)ui1_values;
     return APP_CFGR_OK;
}
extern INT32 a_cfg_cust_set_cust_nw_register_status(UINT8 ui1_reg_status)
{
     UINT8         ui1_values = (UINT8)ui1_reg_status;
     SIZE_T        z_size = 1;

     acfg_set(IDX_CUST_NW_REG_STATUS,&ui1_values,z_size);
     return APP_CFGR_OK;
}

/* channel scan status */
extern INT32 a_cfg_cust_get_crnt_ch_scan_status(UINT8* pui1_ch_scan_status)
{
     UINT8          pt_values[ACFG_CUST_BS_SRC_NUM] = {0};
     UINT8          ui1_bs_src = 0;
     SIZE_T         z_size = ACFG_CUST_BS_SRC_NUM;

     if (!pui1_ch_scan_status)
     {
         DBG_ERROR (("\a_cfg_cust_get_ch_scan_status()INV_ARG!!!\n"));
         return APP_CFGR_INV_ARG;
     }

     acfg_get(IDX_CUST_CH_SCAN_STATUS,(VOID*)pt_values,&z_size);

     if (ACFG_CUST_BS_SRC_NUM != z_size)
     {
         DBG_ERROR (("\a_cfg_cust_get_ch_scan_status() value size error !!!\n"));
         return APP_CFGR_INTERNAL_ERR;
     }

     a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC,
                          &ui1_bs_src);

     if ((APP_CFG_BS_SRC_AIR != ui1_bs_src)
        && (APP_CFG_BS_SRC_CABLE != ui1_bs_src)
        && (APP_CFG_BS_SRC_SAT != ui1_bs_src))
     {
         ui1_bs_src = APP_CFG_BS_SRC_AIR;
     }

     *pui1_ch_scan_status = (UINT8)(pt_values[ui1_bs_src]);
     return APP_CFGR_OK;
}
extern INT32 a_cfg_cust_set_crnt_ch_scan_status(UINT8 ui1_ch_scan_status)
{
     UINT8          pt_values[ACFG_CUST_BS_SRC_NUM] = {0};
     UINT8          ui1_bs_src = 0;
     SIZE_T         z_size = ACFG_CUST_BS_SRC_NUM;

     acfg_get(IDX_CUST_CH_SCAN_STATUS,(VOID*)pt_values,&z_size);

     if (ACFG_CUST_BS_SRC_NUM != z_size)
     {
         DBG_ERROR (("\a_cfg_cust_set_crnt_ch_scan_status() value size error !!!\n"));
         return APP_CFGR_INTERNAL_ERR;
     }

     a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC,
                          &ui1_bs_src);

     if ((APP_CFG_BS_SRC_AIR != ui1_bs_src)
        && (APP_CFG_BS_SRC_CABLE != ui1_bs_src)
        && (APP_CFG_BS_SRC_SAT != ui1_bs_src))
     {
         ui1_bs_src = APP_CFG_BS_SRC_AIR;
     }

     pt_values[ui1_bs_src] = ui1_ch_scan_status;

     acfg_set(IDX_CUST_CH_SCAN_STATUS,(VOID*)pt_values,z_size);

     return APP_CFGR_OK;
}

/* channel scan status */
extern INT32 a_cfg_cust_get_ch_scan_status(UINT8 ui1_bs_src,
                                          UINT8* pui1_ch_scan_status)
{
     UINT8          pt_values[ACFG_CUST_BS_SRC_NUM] = {0};
     SIZE_T         z_size = ACFG_CUST_BS_SRC_NUM;

     if (!pui1_ch_scan_status)
     {
         DBG_ERROR( ("\a_cfg_cust_get_ch_scan_status()INV_ARG!!!\n"));
         return APP_CFGR_INV_ARG;
     }

     acfg_get(IDX_CUST_CH_SCAN_STATUS,(VOID*)pt_values,&z_size);

     if (ACFG_CUST_BS_SRC_NUM != z_size)
     {
         DBG_ERROR( ("\a_cfg_cust_get_ch_scan_status() value size error !!!\n"));
         return APP_CFGR_INTERNAL_ERR;
     }

     if (ui1_bs_src >= ACFG_CUST_BS_SRC_NUM)
     {
         ui1_bs_src = APP_CFG_BS_SRC_AIR;
     }

     *pui1_ch_scan_status = (UINT8)(pt_values[ui1_bs_src]);
     return APP_CFGR_OK;
}
extern INT32 a_cfg_cust_set_ch_scan_status(UINT8 ui1_bs_src,
                                                UINT8 ui1_ch_scan_status)
{
     UINT8          pt_values[ACFG_CUST_BS_SRC_NUM] = {0};
     SIZE_T         z_size = ACFG_CUST_BS_SRC_NUM;

     acfg_get(IDX_CUST_CH_SCAN_STATUS,(VOID*)pt_values,&z_size);

     if (ACFG_CUST_BS_SRC_NUM != z_size)
     {
         DBG_ERROR( ("\a_cfg_cust_set_crnt_ch_scan_status() value size error !!!\n"));
         return APP_CFGR_INTERNAL_ERR;
     }

     if (ui1_bs_src >= ACFG_CUST_BS_SRC_NUM)
     {
         ui1_bs_src = APP_CFG_BS_SRC_AIR;
     }

     pt_values[ui1_bs_src] = ui1_ch_scan_status;

     acfg_set(IDX_CUST_CH_SCAN_STATUS,(VOID*)pt_values,z_size);

     return APP_CFGR_OK;
}

INT32 a_cfg_copy_model_name(CHAR *dst)
{
    INT32 len;
    len = c_strlen(sz_g_model_name);
    if(!dst || len == 0)
    {
        return -1;
    }
    memcpy((VOID*)dst,(VOID*)sz_g_model_name,len);
    return 0;
}

static INT32 _cfg_cust_get_preset_pic_mode_chg_status_by_ipt(INT16 i2_pic_mode,UINT8 ui1_ipt_grp,UINT8 ui1_type, UINT8* pui1_is_chg)
{
     INT32         i4_ret = 0;
     UINT16        ui2_elem_idx = 0;
     INT16         i2_value = 0;

     ui2_elem_idx =  ui1_ipt_grp * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ui1_type * ACFG_PRE_SET_PIC_MODE_NUM + i2_pic_mode;
     i4_ret = acfg_get_int16_by_idx(IDX_PRE_PIC_CHG,ui2_elem_idx,&i2_value);
     ACFG_LOG_ON_FAIL(i4_ret);

     *pui1_is_chg = (UINT8)i2_value;

     return APP_CFGR_OK;

}

static INT32 _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(UINT8 ui1_pic_mode,UINT8 ui1_ipt_grp,UINT8 ui1_type,  BOOL b_is_chg)
{
     INT32         i4_ret = 0;
     UINT16        ui2_elem_idx = 0;

     if (ui1_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
     {
         DBG_ERROR(("\n _cfg_cust_set_preset_pic_mode_chg_status_by_ipt() pic_mode[%d] INV_ARG!!!\n",ui1_pic_mode));
         return APP_CFGR_INV_ARG;
     }

     ui2_elem_idx =  ui1_ipt_grp * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ui1_type * ACFG_PRE_SET_PIC_MODE_NUM + ui1_pic_mode;

     i4_ret = acfg_set_int16_by_idx(IDX_PRE_PIC_CHG,ui2_elem_idx,b_is_chg);
     ACFG_LOG_ON_FAIL(i4_ret);

     return APP_CFGR_OK;
}

#ifdef MT5691_MODEL
static BOOL _cfg_cust_check_trigger_reset_pic(VOID)
{
    INT32 i4_old_ver1,i4_old_ver2,i4_old_ver3,i4_old_ver4;
    INT32 i4_target_ver1,i4_target_ver2,i4_target_ver3,i4_target_ver4;
    FILE*  fl_old_version = NULL;
    INT32  i4_file_len = 0;
    CHAR  string_old_version[64] ={0};
    BOOL b_need_reset = FALSE;
    INT32  i4_nread = 0;

    if ((0 == access("/data/old_fw_version", F_OK)))
    {
        fl_old_version = fopen("/data/old_fw_version", "r");
        if (fl_old_version != NULL)
        {
            fseek(fl_old_version, 0, SEEK_END);
            i4_file_len = ftell(fl_old_version);
            if(i4_file_len > 0)
            {
                fseek(fl_old_version, 0, SEEK_SET);
                if(i4_file_len > 32)
                {
                    i4_file_len = 32;
                }
                DBG_INFO(("version_length:%d  \n\r",i4_file_len));
                if ((i4_nread = fread((VOID*)string_old_version,i4_file_len,1, fl_old_version)) > 0)
                {
                    DBG_INFO(("string_old_version %s\n\r", string_old_version));
                }
            }
            fclose (fl_old_version);
            sscanf(string_old_version,"%d.%d.%d.%d\n",&i4_old_ver1,&i4_old_ver2,&i4_old_ver3,&i4_old_ver4);
            DBG_INFO(("%d,%s,%s  i4_old_ver1:%d i4_old_ver2:%d i4_old_ver3:%d i4_old_ver4:%d \n",__LINE__,__func__,__FILE__,
                i4_old_ver1,i4_old_ver2,i4_old_ver3,i4_old_ver4));

            sscanf(PIC_REST_TARGET_VERSION,"%d.%d.%d.%d\n",&i4_target_ver1,&i4_target_ver2,&i4_target_ver3,&i4_target_ver4);
            DBG_INFO(("%d,%s,%s  i4_target_ver1:%d i4_target_ver2:%d i4_target_ver3:%d i4_target_ver4:%d \n",__LINE__,__func__,__FILE__,
                i4_target_ver1,i4_target_ver2,i4_target_ver3,i4_target_ver4));

            if(i4_target_ver1 == i4_old_ver1 && i4_target_ver2 == i4_old_ver2 && i4_target_ver3 == i4_old_ver3&& i4_target_ver4 > i4_old_ver4)
            {
                b_need_reset = TRUE;
            }
            else if(i4_target_ver1 == i4_old_ver1 && i4_target_ver2 == i4_old_ver2 && i4_target_ver3 > i4_old_ver3)
            {
                b_need_reset = TRUE;
            }
            else if(i4_target_ver1 == i4_old_ver1 && i4_target_ver2 > i4_old_ver2)
            {
                b_need_reset = TRUE;
            }
            else if(i4_target_ver1 > i4_old_ver1)
            {
                b_need_reset = TRUE;
            }
            DBG_LOG_PRINT(("b_need_reset:%d \n",b_need_reset));
        }
    }
    else //old_fw_version no exist,means mp stage fw,need reset directly
    {
        b_need_reset = TRUE;
        DBG_LOG_PRINT(("b_need_reset:%d \n",b_need_reset));
    }
    return b_need_reset;
}
#endif

static VOID _cfg_cust_check_pic_mode_changed_status()
{
    INT16 i2_value = 0;
    INT16 i2_default_value = 0;
    UINT16 ui2_elem_idx;
    UINT16 ui2_input_idx = 0;
    UINT8  ui1_pic_mode = 0;
    UINT8  ui1_video_type = 0 ;//a_acfg_cust_get_dynamic_range();
    INT32  i4_ret = 0;
    UINT16 ui2_rec_idx = 0;

    ACFG_DBG_PRINT(" Enter : \r\n");

    /* data store in eeprom input source  by picture mode */
    for(ui2_input_idx = 0; ui2_input_idx < ACFG_INPUT_SRC_NUM; ui2_input_idx ++)
    {
        for(ui1_pic_mode = 0;ui1_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM; ui1_pic_mode ++)
        {
            ui2_elem_idx = ui2_input_idx*ACFG_PIC_MODE_NUM + ui1_pic_mode;

            i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_GAME_LOW_LATENCY, ui2_elem_idx,&i2_default_value);
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_GAME_LOW_LATENCY, ui2_elem_idx, &i2_value);
            ACFG_LOG_ON_FAIL(i4_ret);

            if(i2_default_value != i2_value)
            {
                DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_GAME_LOW_LATENCY change \r\n", __FUNCTION__, __LINE__)) ;
                _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                continue;
            }

            i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_GAME_HDR, ui2_elem_idx,&i2_default_value);
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_GAME_HDR, ui2_elem_idx, &i2_value);
            ACFG_LOG_ON_FAIL(i4_ret);

            if(i2_default_value != i2_value)
            {
                DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_GAME_HDR change \r\n", __FUNCTION__, __LINE__)) ;
                _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                continue;
            }

        }
    }

    /* data store in eeprom input source  by picture mode by dynamic range*/
    for(ui2_input_idx = 0; ui2_input_idx < ACFG_INPUT_SRC_NUM; ui2_input_idx ++)
    {
        for(ui1_pic_mode = 0;ui1_pic_mode < ACFG_PIC_MODE_NUM; ui1_pic_mode ++)
        {
            for (ui1_video_type = ACFG_CUST_CONTENT_SDR ;ui1_video_type < ACFG_CUST_CONTENT_MAX;ui1_video_type ++)
            {
                ui2_elem_idx = ui2_input_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ui1_video_type * ACFG_PRE_SET_PIC_MODE_NUM + ui1_pic_mode;

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUST_GAMMA, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUST_GAMMA, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUST_GAMMA change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_DISP_BACK_LIGHT, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_DISP_BACK_LIGHT, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_DISP_BACK_LIGHT change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }


                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_DCR_IDX, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_DCR_IDX, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_DCR_IDX change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_DIMMING, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_DIMMING, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_DIMMING change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }


                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_BRI, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_VID_BRI, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_VID_BRI change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_CNT, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_VID_CNT, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_VID_CNT change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_SAT, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_VID_SAT, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_VID_SAT change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_HUE, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_VID_HUE, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_VID_HUE change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                for (ui2_rec_idx = APP_CFG_RECID_VID_CLR_HUE_R ; ui2_rec_idx <= APP_CFG_RECID_VID_CLR_BRI_Y;  ui2_rec_idx++)
                {
                    i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CLR_HUE_R + (ui2_rec_idx - APP_CFG_RECID_VID_CLR_HUE_R), ui2_elem_idx,&i2_default_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                    i4_ret = acfg_get_int16_by_idx(IDX_CLR_HUE_R + (ui2_rec_idx - APP_CFG_RECID_VID_CLR_HUE_R), ui2_elem_idx, &i2_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                    if(i2_default_value != i2_value)
                    {
                        DBG_LOG_PRINT( (" [-----ACFG] %s %d APP_CFG_RECID_VID_CLR_HUE_R+%d change \r\n", __FUNCTION__, __LINE__,ui2_rec_idx)) ;
                        _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                        continue;
                    }

                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_LIGHT_SENSOR_IDX, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_LIGHT_SENSOR_IDX, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_LIGHT_SENSOR_IDX change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_SHP, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_VID_SHP, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_VID_SHP change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_SUPER_RESOLUTION, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_SUPER_RESOLUTION, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_SUPER_RESOLUTION change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_EN_VIEW_ANGLE, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_EN_VIEW_ANGLE, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_EN_VIEW_ANGLE change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_JUDDER_REDUCTION, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_JUDDER_REDUCTION, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_JUDDER_REDUCTION change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_MOTION_BLUR_REDUCTION, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_MOTION_BLUR_REDUCTION, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_MOTION_BLUR_REDUCTION change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_NR, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_VID_NR, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_VID_NR change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_3D_NR, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_VID_3D_NR, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_VID_3D_NR change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

            #ifdef APP_MPEG_NR_SUPPORT
                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_MPEG_NR, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_VID_MPEG_NR, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_VID_MPEG_NR change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }
            #endif

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CLEAR_ACTION, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CLEAR_ACTION, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CLEAR_ACTION change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

            #ifdef APP_DI_SUPPORT
                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_DI_FILM_MODE, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_VID_DI_FILM_MODE, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_VID_DI_FILM_MODE change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }
            #endif

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_CONTRAST_EN, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_CONTRAST_EN, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_CONTRAST_EN change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CLR_TEMP, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_TEMP, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CLR_TEMP change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                /* new add ,not include pq matrix*/
                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_LOCAL_CONTRAST, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_VID_LOCAL_CONTRAST, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_VID_LOCAL_CONTRAST change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_CONTOUR_SMOOTHING, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_CONTOUR_SMOOTHING, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_CONTOUR_SMOOTHING change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_EDGE_ENHANCEMENT, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_EDGE_ENHANCEMENT, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value)
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_EDGE_ENHANCEMENT change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_PEAK_LUMINANCE, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_get_int16_by_idx(IDX_CUSTOM_PEAK_LUMINANCE, ui2_elem_idx, &i2_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                if(i2_default_value != i2_value && (a_cfg_cust_oled_support() == TRUE))
                {
                    DBG_LOG_PRINT( (" [-----ACFG] %s %d IDX_CUSTOM_PEAK_LUMINANCE change \r\n", __FUNCTION__, __LINE__)) ;
                    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, TRUE);
                    continue;
                }

            }

        }
    }
}

BOOL a_cfg_cust_check_current_color_tuner_chg_status(VOID)
{
    INT16         i2_value     = 0;
    INT32         i4_ret       = 0;
    BOOL          b_chg_status = FALSE;
    UINT32        ui2_rec_idx  = 0;

    do
    {
        // RGB enable ,the default value is 1
        for (ui2_rec_idx = APP_CFG_RECID_VID_RED ; ui2_rec_idx <= APP_CFG_RECID_VID_BLUE;  ui2_rec_idx++)
        {
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED + (ui2_rec_idx - APP_CFG_RECID_VID_RED)), &i2_value);
            ACFG_LOG_ON_FAIL(i4_ret);
            if(1 != i2_value)
            {
                b_chg_status = TRUE;
                break;
            }
        }

        // 2p wb,the default value is 0
        for (ui2_rec_idx = APP_CFG_RECID_VID_CLR_HUE_R ; ui2_rec_idx <= APP_CFG_RECID_VID_CLR_BRI_Y;  ui2_rec_idx++)
        {
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_R + (ui2_rec_idx - APP_CFG_RECID_VID_CLR_HUE_R)), &i2_value);
            ACFG_LOG_ON_FAIL(i4_ret);

            if(0 != i2_value)
            {
                b_chg_status = TRUE;
                break;
            }
        }
    }while(0);
    ACFG_DBG_PRINT("Get b_chg_status :%d \r\n",b_chg_status);

    return b_chg_status;
}


BOOL a_cfg_cust_check_current_wb_tuner_chg_status(VOID)
{
    INT16         i2_value = 0;
    INT32         i4_ret = 0;
    BOOL          b_chg_status = FALSE;

    // calculate elem
    do
    {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_RED), &i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        if(0 != i2_value)
        {
            b_chg_status = TRUE;
            break;
        }

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_GREEN), &i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        if(0 != i2_value)
        {
            b_chg_status = TRUE;
            break;
        }

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_BLUE), &i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        if(0 != i2_value)
        {
            b_chg_status = TRUE;
            break;
        }

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_R), &i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        if(0 != i2_value)
        {
            b_chg_status = TRUE;
            break;
        }

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_G), &i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        if(0 != i2_value)
        {
            b_chg_status = TRUE;
            break;
        }

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_B), &i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        if(0 != i2_value)
        {
            b_chg_status = TRUE;
            break;
        }

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R), &i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        if(0 != i2_value)
        {
            b_chg_status = TRUE;
            break;
        }

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_G), &i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        if(0 != i2_value)
        {
            b_chg_status = TRUE;
            break;
        }

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_B), &i2_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        if(0 != i2_value)
        {
            b_chg_status = TRUE;
            break;
        }
    }while(0);
    ACFG_DBG_PRINT("Get b_chg_status :%d \r\n",b_chg_status);

    return b_chg_status;
}

extern BOOL a_oled_compensation_is_running();

extern INT32 a_cfg_cust_blank_screen(VOID)
{
    if(a_cfg_cust_oled_support())
    {
        a_cfg_custom_set_black_pattern(TRUE);
    }
    else
    {
        INT32 i4_ret = APP_CFGR_OK;
        if(a_oled_compensation_is_running())
        {
            DBG_LOG_PRINT(("[%s %d] it under off-rs,should not blank screen\n",__FUNCTION__,__LINE__));
            return 0;
        }
        a_cfg_custom_set_black_pattern(TRUE);
        i4_ret = a_cfg_cust_drv_set_blank_screen(1);
        ACFG_LOG_ON_FAIL(i4_ret);

        return a_cfg_disp_set_back_light_ctrl(FALSE);
    }
    return 0;
}

extern INT32 a_cfg_cust_unblank_screen(VOID)
{
    if(a_cfg_cust_oled_support())
    {
        a_cfg_custom_set_black_pattern(FALSE);
    }
    else
    {
        a_cfg_custom_set_black_pattern(FALSE);
        return a_cfg_disp_set_back_light_ctrl(TRUE);
    }
    return 0;
}

extern INT32 a_cfg_cust_get_blank_screen_state(VOID* pv_get_info)
{
    INT32 i4_ret = APP_CFGR_OK;

    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
    DRV_CUST_OPERATION_INFO_T t_op_info;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));


    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_GET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_DISP_TYPE_FORCE_BACK_LIGHT;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)pv_get_info;
    t_op_info.u.t_vid_set_info.z_size = sizeof(FORCE_BACK_LIGHT_T);
    t_op_info.u.t_vid_set_info.b_store = FALSE;

    i4_ret = c_rm_get_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           &z_size);
    return i4_ret;
}

extern INT32 a_cfg_get_preset_pic_mode_chg_status(INT16 i2_pic_mode, BOOL* pb_is_chg)
{
    INT32         i4_ret = 0;
    UINT8         ui1_type = a_acfg_cust_get_dynamic_range();
    UINT8         ui1_ipt = 0;
    ISL_REC_T     t_isl_rec;
    UINT8         ui1_input = 0;
    CHAR          s_disp_name[ACFG_MAX_DISP_NAME+1];

    if (i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
    {
        DBG_ERROR( ("\n a_cfg_get_preset_pic_mode_chg_status() pic_mode[%d] INV_ARG!!!\n",i2_pic_mode));
        return APP_CFGR_INV_ARG;
    }

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);

    ui1_ipt = acfg_custom_get_input_grp(&t_isl_rec);

    _cfg_cust_get_preset_pic_mode_chg_status_by_ipt(i2_pic_mode,ui1_ipt,ui1_type,pb_is_chg);

    return APP_CFGR_OK;

}

extern INT32 a_cfg_set_preset_pic_mode_chg_status(INT16 i2_pic_mode, BOOL b_is_chg)
{
    INT32         i4_ret = 0;
    UINT8         ui1_type = a_acfg_cust_get_dynamic_range();
    UINT8         ui1_ipt = 0;
    ISL_REC_T     t_isl_rec;
    UINT8         ui1_input = 0;
    CHAR          s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8         ui1_val = b_is_chg ? ICL_PQ_CHANGE_PRESET_PQ : ICL_PQ_CHANGE_NOTHING;

    if (i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
    {
        DBG_ERROR( ("\n a_cfg_set_preset_pic_mode_chg_status() pic_mode[%d] INV_ARG!!!\n",i2_pic_mode));
        return APP_CFGR_INV_ARG;
    }

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);

    ui1_ipt = acfg_custom_get_input_grp(&t_isl_rec);

    _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(i2_pic_mode,ui1_ipt,ui1_type,b_is_chg);

    a_icl_custom_set_pq_chg_status(ui1_val);

    return APP_CFGR_OK;

}

extern INT32 a_cfg_set_preset_pic_mode_chg_status_ex(INT16 i2_pic_mode, BOOL b_is_chg)
{
    INT32         i4_ret = 0;
    UINT8         ui1_type = 0;
    UINT8         ui1_ipt = 0;
    ISL_REC_T     t_isl_rec;
    UINT8         ui1_input = 0;
    CHAR          s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8         ui1_val = b_is_chg ? ICL_PQ_CHANGE_PRESET_PQ : ICL_PQ_CHANGE_NOTHING;

    if (i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
    {
        DBG_ERROR( ("\n a_cfg_set_preset_pic_mode_chg_status() pic_mode[%d] INV_ARG!!!\n",i2_pic_mode));
        return APP_CFGR_INV_ARG;
    }

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    a_isl_get_rec_by_idx (ui1_input, & t_isl_rec);

    ui1_ipt = acfg_custom_get_input_grp(&t_isl_rec);

    for(ui1_type = ACFG_CUST_CONTENT_SDR; ui1_type < ACFG_CUST_CONTENT_MAX;ui1_type++)
    {
        _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(i2_pic_mode,ui1_ipt,ui1_type,b_is_chg);
    }

    a_icl_custom_set_pq_chg_status(ui1_val);

    return APP_CFGR_OK;

}

extern INT32 a_cfg_set_clr_temp_chg_status(INT16 i2_clr_temp, BOOL b_is_chg)
{
     UINT8         pt_values[ACFG_MAX_REC_SIZE] = {0};
     UINT16        ui2_ipt = ACFG_CUST_INPUT_GRP_HDMI1;

     UINT16        ui2_off = 0;
     SIZE_T        z_size = ACFG_CUST_SET_PIC_MODE_NUM;

     UINT8         ui1_val = b_is_chg ? ICL_PQ_CHANGE_COLOR_TEMP : ICL_PQ_CHANGE_NOTHING;
     UINT8          ui1_play_content = a_acfg_cust_get_dynamic_range();

     acfg_get(IDX_CLR_TEMP_CHG,(VOID*)pt_values,&z_size);

     ui2_off = ui2_ipt*ACFG_CLR_TEMP_NUM + i2_clr_temp;

    if(b_is_chg == TRUE)
    {
        b_is_chg = pt_values[ui2_off] | (1 << ui1_play_content);
        DBG_INFO(("[TEST][%s]:[%d]b_is_chg=%d\n",__FILE__,__LINE__,b_is_chg));
    }
    else
    {
        b_is_chg = pt_values[ui2_off] & (~(1 << ui1_play_content));
        DBG_INFO(("[TEST][%s]:[%d]b_is_chg=%d\n",__FILE__,__LINE__,b_is_chg));
    }
     pt_values[ui2_off] = (UINT8)b_is_chg;

     acfg_set(IDX_CLR_TEMP_CHG,(VOID*)pt_values,z_size);

     a_icl_custom_set_pq_chg_status(ui1_val);

     return APP_CFGR_OK;

}

extern INT32 a_cfg_get_clr_temp_chg_status(INT16 i2_clr_temp, BOOL* pb_is_chg)
{
     UINT8         pt_values[ACFG_MAX_REC_SIZE] = {0};
     UINT16        ui2_ipt = ACFG_CUST_INPUT_GRP_HDMI1;
     UINT8         ui1_values = 0;
     UINT16        ui2_off = 0;
     SIZE_T        z_size = ACFG_CUST_SET_PIC_MODE_NUM;
     UINT8          ui1_play_content = a_acfg_cust_get_dynamic_range();

     acfg_get(IDX_CLR_TEMP_CHG,(VOID*)pt_values,&z_size);

     ui2_off = ui2_ipt*ACFG_CLR_TEMP_NUM + i2_clr_temp;

     ui1_values = pt_values[ui2_off];

     ui1_values = ui1_values & (1 << ui1_play_content);

     ui1_values = (ui1_values > 0) ? TRUE : FALSE;

     *pb_is_chg = ui1_values;

     return APP_CFGR_OK;
}

/* clr tuner reset only reset current clr temp value*/
extern INT32 a_cfg_reset_clr_tuner(INT16 i2_clr_temp)
{
    INT32       i4_ret;
    INT16       i2_val = 0;
    UINT16      ui2_idx_begin = 0;
    UINT16      ui2_idx_end = 0;
    INT16       i2_tmp_val = 0;
    UINT16      ui2_idx = 0;
    UINT8       ui1_input_grp = ACFG_CUST_INPUT_GRP_HDMI1;

#ifdef NEVER
    /* set the RGB def value*/
    i2_val = ACFG_VID_RGB_ENABLE;
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
#endif /* NEVER */

    /* gain offset rgb*/
    i2_val = 0;
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_R), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_G), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_B), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_G), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_B), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

#ifdef NEVER
    /* hrgb*/
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_R), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_G), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_B), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_R), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_G), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_B), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_R), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_G), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_B), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_C), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_M), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_Y), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_C), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_M), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_Y), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_C), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_M), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_Y), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
#endif /* NEVER */

    /* 20 point*/
    ui1_input_grp = a_acfg_cust_get_dynamic_range();

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_tmp_val);
    ui2_idx_begin = ui1_input_grp*ACFG_CLR_TEMP_NUM*APP_CFG_11_POINT_GAIN_NUM + i2_tmp_val*APP_CFG_11_POINT_GAIN_NUM;
    ui2_idx_end = ui1_input_grp*ACFG_CLR_TEMP_NUM*APP_CFG_11_POINT_GAIN_NUM + i2_tmp_val*APP_CFG_11_POINT_GAIN_NUM + APP_CFG_11_POINT_GAIN_NUM;

    i2_val = 0;
    for (ui2_idx = ui2_idx_begin; ui2_idx < ui2_idx_end; ui2_idx ++)
    {
        acfg_set_int16_by_idx(IDX_11_POINT_GAIN_RED,
                            ui2_idx,
                            i2_val);

        acfg_set_int16_by_idx(IDX_11_POINT_GAIN_GREEN,
                            ui2_idx,
                            i2_val);

        acfg_set_int16_by_idx(IDX_11_POINT_GAIN_BLUE,
                            ui2_idx,
                            i2_val);
     }

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* reset clr temp changed status*/
    a_cfg_set_clr_temp_chg_status(i2_clr_temp, FALSE);

    return APP_CFGR_OK;
}


/* clr tuner reset only reset current clr temp value*/
INT32 a_cfg_reset_current_color_temperature(INT16 i2_clr_temp)
{
    INT32       i4_ret;
    INT16       i2_val = 0;
    UINT16      ui2_idx_begin = 0;
    UINT16      ui2_idx_end = 0;
    INT16       i2_tmp_val = 0;
    UINT16      ui2_idx = 0;
    UINT8       ui1_input_grp = ACFG_CUST_INPUT_GRP_HDMI1;

    /* set the RGB def value*/
    i2_val = ACFG_VID_RGB_ENABLE;
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* gain offset rgb*/
    i2_val = 0;
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_R), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_G), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_B), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_G), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_B), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* 20 point*/
    ui1_input_grp = a_acfg_cust_get_dynamic_range();

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_tmp_val);
    ui2_idx_begin = ui1_input_grp*ACFG_CLR_TEMP_NUM*APP_CFG_11_POINT_GAIN_NUM + i2_tmp_val*APP_CFG_11_POINT_GAIN_NUM;
    ui2_idx_end = ui1_input_grp*ACFG_CLR_TEMP_NUM*APP_CFG_11_POINT_GAIN_NUM + i2_tmp_val*APP_CFG_11_POINT_GAIN_NUM + APP_CFG_11_POINT_GAIN_NUM;

    i2_val = 0;
    for (ui2_idx = ui2_idx_begin; ui2_idx < ui2_idx_end; ui2_idx ++)
    {
        acfg_set_int16_by_idx(IDX_11_POINT_GAIN_RED,
                            ui2_idx,
                            i2_val);

        acfg_set_int16_by_idx(IDX_11_POINT_GAIN_GREEN,
                            ui2_idx,
                            i2_val);

        acfg_set_int16_by_idx(IDX_11_POINT_GAIN_BLUE,
                            ui2_idx,
                            i2_val);
     }

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* reset clr temp changed status*/
    a_cfg_set_clr_temp_chg_status(i2_clr_temp, FALSE);

    return APP_CFGR_OK;
}

/* clr tuner reset only reset current clr hsb value*/
INT32 a_cfg_reset_current_color_tuner(INT16 i2_pic)
{
    INT32       i4_ret;
    INT16       i2_val = 0;

    /* set the RGB def value*/
    i2_val = ACFG_VID_RGB_ENABLE;
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* hrgb*/
    i2_val = 0;
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_R), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_G), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_B), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_R), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_G), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_B), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_R), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_G), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_B), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_C), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_M), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_Y), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_C), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_M), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_Y), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_C), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_M), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_Y), i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* check picture changed status*/
    //a_cfg_set_preset_pic_mode_chg_status(i2_pic, FALSE);
    //_cfg_cust_check_pic_mode_changed_status();

    return APP_CFGR_OK;
}

extern INT32 a_cfg_custom_set_tv_name(CHAR *ps_tv_name)
{
    UINT8   pt_values[MAX_TV_NAME_LEN] = {0};
    SIZE_T  z_size = MAX_TV_NAME_LEN;
    UINT32  ui4_idx = 0;
    UINT32  ui4_len = 0;

    if(NULL == ps_tv_name)
    {
        return APP_CFGR_INV_ARG;
    }

    ui4_len = c_strlen(ps_tv_name);

    if (ui4_len >= MAX_TV_NAME_LEN)
    {
        return APP_CFGR_INV_ARG;
    }

    for (ui4_idx = 0;ui4_idx <= ui4_len; ui4_idx ++ )
    {
        pt_values[ui4_idx] = ps_tv_name[ui4_idx];
    }

    acfg_set(IDX_CUST_TV_NAME,(VOID*)pt_values,z_size);


    INT32   i4_ret = 0;

    if (c_strlen(ps_tv_name) > 0)
    {
#ifdef A_C4TV_APRON_CAST_NAME      
        i4_ret = a_c4tv_apron_set_cast_name(ps_tv_name);
#else      
        i4_ret = a_cfg_custom_set_cast_name(ps_tv_name);
#endif      
        if(i4_ret != 0)
        {
            DBG_ERROR(("%s,%d [get cast name fail(%d)] \r\n",__FUNCTION__, __LINE__, i4_ret));
        }
    }

    CMD_CONVERT_SEND_CMD_T t_send_cmd;
    t_send_cmd.s_source = CMDCVT_MACRO_AM;
    t_send_cmd.s_destination = "dialserver";
    t_send_cmd.s_ack = NULL;
    t_send_cmd.s_command = "updateDeviceName";
    t_send_cmd.s_parameter = "dialserver";
    cmd_convert_send_command(&t_send_cmd);

    return APP_CFGR_OK;
}

extern INT32 a_cfg_custom_get_tv_name(CHAR *ps_tv_name,
                                              UINT32* pui4_len)
{
    UINT32  ui4_idx = 0;
    UINT8   pt_values[MAX_TV_NAME_LEN] = {0};
    SIZE_T  z_size = MAX_TV_NAME_LEN;

    UINT32  ui4_len = 0;

    if((NULL == ps_tv_name)
        || (NULL == pui4_len))
    {
        return APP_CFGR_INV_ARG;
    }

    acfg_get(IDX_CUST_TV_NAME,(VOID*)pt_values,&z_size);

    if (*pui4_len >= z_size)
    {
        ui4_len = z_size;
    }
    else
    {
        ui4_len = *pui4_len;
    }

    for (ui4_idx = 0;ui4_idx < ui4_len; ui4_idx ++ )
    {
        ps_tv_name[ui4_idx] = pt_values[ui4_idx];
    }

    ps_tv_name[ui4_len - 1] = '\0';


    INT32   i4_ret = 0;
    CHAR    s_cast_name[MAX_TV_NAME_LEN+1] = {0};
    UINT32  ui4_cast_name_len = MAX_TV_NAME_LEN;

    if (c_strlen(ps_tv_name) == 0)
    {
#ifdef A_C4TV_APRON_CAST_NAME      
        i4_ret = a_c4tv_apron_get_cast_name(s_cast_name, &ui4_cast_name_len);
#else
        i4_ret = a_cfg_custom_get_cast_name(s_cast_name, &ui4_cast_name_len);
#endif      
        if(i4_ret != 0)
        {
            DBG_INFO(("%s,%d [get cast name fail(%d)] \r\n",__FUNCTION__, __LINE__, i4_ret));
        }
        c_strncpy(ps_tv_name, s_cast_name, MAX_TV_NAME_LEN);
        ui4_len = c_strlen(s_cast_name);

        ps_tv_name[ui4_len] = '\0';
    }


    *pui4_len = ui4_len;

    return APP_CFGR_OK;
}
INT32 a_cfg_custom_set_vtrl_name(UINT16 ui2_cfg_idx,CHAR *ps_vtrl_name)
{
    UINT8   pt_values[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    SIZE_T  z_size = APP_CFG_CUSTOM_INP_NAME_LEN;
    UINT32  ui4_idx = 0;
    UINT32  ui4_len = 0;

    if(NULL == ps_vtrl_name)
    {
        return APP_CFGR_INV_ARG;
    }

    ui4_len = c_strlen(ps_vtrl_name);

    if (ui4_len >= APP_CFG_CUSTOM_INP_NAME_LEN)
    {
        return APP_CFGR_INV_ARG;
    }

    for (ui4_idx = 0;ui4_idx <= ui4_len; ui4_idx ++ )
    {
        pt_values[ui4_idx] = ps_vtrl_name[ui4_idx];
    }

    acfg_set(ui2_cfg_idx,(VOID*)pt_values,z_size);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_vtrl_name(UINT16 ui2_cfg_idx,CHAR *ps_vtrl_name,
                                              UINT32* pui4_len)
{
    UINT32  ui4_idx = 0;
    UINT8   pt_values[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    SIZE_T  z_size = APP_CFG_CUSTOM_INP_NAME_LEN;

    UINT32  ui4_len = 0;

    if((NULL == ps_vtrl_name)
        || (NULL == pui4_len))
    {
        return APP_CFGR_INV_ARG;
    }

    acfg_get(ui2_cfg_idx,(VOID*)pt_values,&z_size);
    DBG_INFO((" %s,%d ,name %s\n", __FUNCTION__,__LINE__,pt_values));

    if (*pui4_len >= z_size)
    {
        ui4_len = z_size;
    }
    else
    {
        ui4_len = *pui4_len;
    }

    for (ui4_idx = 0;ui4_idx < ui4_len; ui4_idx ++ )
    {
        ps_vtrl_name[ui4_idx] = pt_values[ui4_idx];
    }

    ps_vtrl_name[ui4_len - 1] = '\0';

    *pui4_len = ui4_len;

    return APP_CFGR_OK;
}

/* set the pre-set pic mode changed or not*/
INT32 a_cfg_reset_preset_pic_mode(VOID)
{
    INT16  i2_pic_mode = 0;
    INT32  i4_ret = 0;

    /* first shoud get the current pic mode*/
    a_cfg_av_get(
            CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
            &i2_pic_mode);


    if ((i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
        || (i2_pic_mode < 0))
    {
        DBG_ERROR((" [ACFG] %s,%d ,Invalid picture mode : %d\n", __FUNCTION__,__LINE__,i2_pic_mode));
        return APP_CFGR_INV_ARG;
    }

    //reset copy_base picture mode to 0
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CUST_PIC_COPY_BASE),0);
    ACFG_LOG_ON_FAIL(i4_ret);

    a_cfg_reset_preset_pic_mode_ex(i2_pic_mode);

    /* set the pq chg status*/
    a_cfg_set_preset_pic_mode_chg_status(i2_pic_mode, FALSE);
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    ACFG_LOG_ON_FAIL(i4_ret);

    return APP_CFGR_OK;

}


/* set the pre-set pic mode changed or not*/
INT32 a_cfg_reset_all_pic_settings(VOID)
{
    INT32 i4_ret        = 0;
    UINT8 ui1_pic_mode  = 0;
    UINT8 ui1_input_grp = 0;
    UINT16 ui2_count    = 0;
    UINT16 ui2_elem_idx = 0;

    INT16 i2_cust_pic_exist = 0;
    INT16  i2_default_value = 0;
    UINT16 ui2_input_idx    = 0;
    UINT8  ui1_video_type   = 0 ;//a_acfg_cust_get_dynamic_range();
    UINT16 ui2_rec_idx      = 0;


    DBG_LOG_PRINT(("[ACFG][default]{%s,%s,%d}  \n", __FILE__, __FUNCTION__,__LINE__));


    /* data store in eeprom input source  by picture mode */
    for(ui2_input_idx = 0; ui2_input_idx < ACFG_INPUT_SRC_NUM; ui2_input_idx ++)
    {
        for(ui1_pic_mode = 0;ui1_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM; ui1_pic_mode ++)
        {
            ui2_elem_idx = ui2_input_idx*ACFG_PIC_MODE_NUM + ui1_pic_mode;

            i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_GAME_LOW_LATENCY, ui2_elem_idx,&i2_default_value);
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_GAME_LOW_LATENCY, ui2_elem_idx, i2_default_value);
            ACFG_LOG_ON_FAIL(i4_ret);

            i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_GAME_HDR, ui2_elem_idx,&i2_default_value);
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_GAME_HDR, ui2_elem_idx, i2_default_value);
            ACFG_LOG_ON_FAIL(i4_ret);

            ////
            _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, FALSE);
        }
    }

    /* data store in eeprom input source  by picture mode by dynamic range*/
    for(ui2_input_idx = 0; ui2_input_idx < ACFG_INPUT_SRC_NUM; ui2_input_idx ++)
    {
        for(ui1_pic_mode = 0;ui1_pic_mode < ACFG_PIC_MODE_NUM; ui1_pic_mode ++)
        {
            for (ui1_video_type = ACFG_CUST_CONTENT_SDR ;ui1_video_type < ACFG_CUST_CONTENT_MAX;ui1_video_type ++)
            {
                ui2_elem_idx = ui2_input_idx * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ui1_video_type * ACFG_PRE_SET_PIC_MODE_NUM + ui1_pic_mode;

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUST_GAMMA, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUST_GAMMA, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_DISP_BACK_LIGHT, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_DISP_BACK_LIGHT, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_DCR_IDX, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_DCR_IDX, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_DIMMING, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_DIMMING, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_BRI, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_VID_BRI, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_CNT, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_VID_CNT, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_SAT, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_VID_SAT, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_HUE, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_VID_HUE, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                for (ui2_rec_idx = APP_CFG_RECID_VID_CLR_HUE_R ; ui2_rec_idx <= APP_CFG_RECID_VID_CLR_BRI_Y;  ui2_rec_idx++)
                {
                    i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CLR_HUE_R + (ui2_rec_idx - APP_CFG_RECID_VID_CLR_HUE_R), ui2_elem_idx,&i2_default_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                    i4_ret = acfg_set_int16_by_idx(IDX_CLR_HUE_R + (ui2_rec_idx - APP_CFG_RECID_VID_CLR_HUE_R), ui2_elem_idx, i2_default_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

                i2_default_value = 1;
                i4_ret = acfg_set_int16_by_idx(IDX_RED, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_set_int16_by_idx(IDX_GREEN, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_set_int16_by_idx(IDX_BLUE, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_LIGHT_SENSOR_IDX, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_LIGHT_SENSOR_IDX, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_SHP, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_VID_SHP, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_SUPER_RESOLUTION, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_SUPER_RESOLUTION, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_EN_VIEW_ANGLE, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_EN_VIEW_ANGLE, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_JUDDER_REDUCTION, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_JUDDER_REDUCTION, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_MOTION_BLUR_REDUCTION, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_MOTION_BLUR_REDUCTION, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);


                ACFG_DEBUG_NR_DEFAULT(
                    DBG_LOG_PRINT(("[ACFG][NR][default]{%s,%s,%d}  \n", __FILE__, __FUNCTION__,__LINE__));
                );

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_NR, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_VID_NR, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_3D_NR, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_VID_3D_NR, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

#ifdef APP_MPEG_NR_SUPPORT
                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_MPEG_NR, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_VID_MPEG_NR, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
#endif
                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CLEAR_ACTION, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CLEAR_ACTION, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

#ifdef APP_DI_SUPPORT
                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_DI_FILM_MODE, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_VID_DI_FILM_MODE, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
#endif

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_CONTRAST_EN, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_CONTRAST_EN, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CLR_TEMP, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CLR_TEMP, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                /* new add ,not include pq matrix*/
                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_LOCAL_CONTRAST, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_VID_LOCAL_CONTRAST, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_CONTOUR_SMOOTHING, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_CONTOUR_SMOOTHING, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_EDGE_ENHANCEMENT, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_EDGE_ENHANCEMENT, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);

                i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_PEAK_LUMINANCE, ui2_elem_idx,&i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);
                i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_PEAK_LUMINANCE, ui2_elem_idx, i2_default_value);
                ACFG_LOG_ON_FAIL(i4_ret);


                ////
                _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui2_input_idx,ui1_video_type, FALSE);

            }
        }
    }


    //2. reset/delete custom picture mode to 0
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CUST_PIC_COPY_BASE),0);
    ACFG_LOG_ON_FAIL(i4_ret);

    /* here should use the glob cust pic mode input src: */
    ui1_input_grp = ACFG_VID_SETTINS_GLOBAL_IPT_SRC;

    /* first get the crnt src unuse cust pic mode*/
    for (ui2_count = 0; ui2_count < ACFG_CUST_SET_PIC_MODE_NUM_EX; ui2_count++)
    {
        ui2_elem_idx = ui1_input_grp*ACFG_CUST_SET_PIC_MODE_NUM + ui2_count;

        acfg_get_int16_by_idx(IDX_CUST_PIC_EXIST_STATUS,ui2_elem_idx,&i2_cust_pic_exist);
        if (1 == i2_cust_pic_exist)
        {
            /* set this cust pic mode no exist*/
            i2_cust_pic_exist = 0;
            i4_ret = acfg_set_int16_by_idx(IDX_CUST_PIC_EXIST_STATUS,ui2_elem_idx,i2_cust_pic_exist);
            ACFG_LOG_ON_FAIL(i4_ret);

            /* set this cust pic mode BASE PIC*/
            i4_ret = acfg_set_int16_by_idx(IDX_CUST_PIC_COPY_BASE,ui2_elem_idx,0);
            ACFG_LOG_ON_FAIL(i4_ret);

            /*After delete is selected, t                        hen Bright Room pictrue mode is set for any sources previously assigned to the picture mode*/
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), ACFG_PIC_MODE_DEF);
            if(i4_ret != MENUR_OK)
            {
                DBG_ERROR(("<MENU>Failed to delete pic mode. [i4_ret = %d]\r\n", i4_ret));
            }
            else
            {
                for(UINT8 ui1_input_src=ACFG_CUST_INPUT_GRP_TV;ui1_input_src<ACFG_CUST_INPUT_GRP_MAX;ui1_input_src++)
                {
                    ui2_elem_idx = ui1_input_src;

                    i4_ret = acfg_set_int16_by_idx(IDX_PIC_MODE, ui2_elem_idx, ACFG_PIC_MODE_DEF);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            }
        }
    }

    return APP_CFGR_OK;

}

/* set the pre-set pic mode changed or not*/
INT32 a_cfg_reset_preset_pic_mode_ex(INT16  i2_pic_mode)
{
    ISL_REC_T                   t_isl_rec;
    UINT8                       ui1_input = 0;
    UINT8                       ui1_input_src = 0;
    CHAR                        s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    INT32                       i4_ret = 0;

    if ((i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
        || (i2_pic_mode < 0))
    {
        return APP_CFGR_INV_ARG;
    }

    /*get current input source*/
    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);
    ui1_input_src = acfg_custom_get_input_grp(&t_isl_rec);
    DBG_INFO((" ui1_input_src :%d, %s,%d\r\n",ui1_input_src,__FUNCTION__,__LINE__));
    a_cfg_reset_preset_pic_mode_by_ipt(i2_pic_mode,ui1_input_src);

    return APP_CFGR_OK;

}

extern INT32 acfg_cust_video_get_reduce_blur_def_value(
    INT16   i2_pic_mode,
    INT16*  pi2_val)
{
    if ((i2_pic_mode < 0)
        || (i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
        || (!pi2_val))
    {
        return APP_CFGR_INV_ARG;
    }

    *pi2_val = ACFG_REDUCE_BLUR_OFF;
    return APP_CFGR_OK;


}
extern INT32 acfg_cust_video_get_game_mode_def_value(
    INT16   i2_pic_mode,
    INT16*  pi2_val)
{
    if ((i2_pic_mode < 0)
        || (i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
        || (!pi2_val))
    {
        return APP_CFGR_INV_ARG;
    }

    if (ACFG_CUST_PIC_MODE_GAME == i2_pic_mode)
    {
        *pi2_val = ACFG_GAME_MODE_ON;
    }
    else
    {
        *pi2_val = ACFG_GAME_MODE_OFF;
    }
    return APP_CFGR_OK;
}

INT32 a_cfg_set_preset_pic_mode_chg_status_by_ipt(UINT8 ui1_pic_mode,UINT8 ui1_ipt_grp,UINT8 ui1_type, BOOL b_is_chg)
{
     INT32         i4_ret = 0;
     i4_ret = _cfg_cust_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui1_ipt_grp,ui1_type,b_is_chg);
     ACFG_LOG_ON_FAIL(i4_ret);

     return i4_ret;

}

/* set the pre-set pic mode changed or not*/
INT32 a_cfg_reset_preset_pic_mode_by_ipt(INT16  i2_pic_mode,UINT8 ui1_inp_src)
{
    UINT16 ui2_elem_idx = 0;
    UINT8  ui1_pic_mode = (UINT8)i2_pic_mode;
    UINT8  ui1_video_type = 0;
    INT16  i2_default_value = 0;
    INT32  i4_ret = 0;
    UINT16 ui2_rec_idx = 0;


    DBG_LOG_PRINT(("[ACFG][pic_mode][default]{%s,%s,%d}  \n", __FILE__, __FUNCTION__,__LINE__));

    if ((i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
        || (i2_pic_mode < 0)
        || (ui1_inp_src >= ACFG_INPUT_SRC_NUM))
    {
        DBG_ERROR(("\n[acfg]a_cfg_reset_preset_pic_mode_by_ipt()pic value[%d],ui1_inp_src[%d] is invalid\n", i2_pic_mode,ui1_inp_src));
        return APP_CFGR_INV_ARG;
    }

    /* data store in eeprom input source  by picture mode*/
    ui2_elem_idx = ui1_inp_src*ACFG_PIC_MODE_NUM + ui1_pic_mode;

    i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_GAME_LOW_LATENCY, ui2_elem_idx,&i2_default_value);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_GAME_LOW_LATENCY, ui2_elem_idx, i2_default_value);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_GAME_HDR, ui2_elem_idx,&i2_default_value);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_GAME_HDR, ui2_elem_idx, i2_default_value);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_VARIABLE_REFRESH_RATE, ui2_elem_idx,&i2_default_value);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_VARIABLE_REFRESH_RATE, ui2_elem_idx, i2_default_value);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_VARIABLE_REFRESH_RATE, ui2_elem_idx,&i2_default_value);
    ACFG_LOG_ON_FAIL(i4_ret);
    i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_VARIABLE_REFRESH_RATE, ui2_elem_idx, i2_default_value);
    ACFG_LOG_ON_FAIL(i4_ret);

    /* set the pq chg status*/
    a_cfg_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui1_inp_src,0, FALSE);

    /* data store in eeprom input source  by picture mode by dynamic range*/
    for (ui1_video_type = ACFG_CUST_CONTENT_SDR ;ui1_video_type < ACFG_CUST_CONTENT_MAX;ui1_video_type ++)
    {
        ui2_elem_idx = ui1_inp_src * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM + ui1_video_type * ACFG_PRE_SET_PIC_MODE_NUM + ui1_pic_mode;

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUST_GAMMA, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUST_GAMMA, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_DISP_BACK_LIGHT, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_DISP_BACK_LIGHT, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_DCR_IDX, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_DCR_IDX, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_DIMMING, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_DIMMING, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_BRI, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_BRI, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_CNT, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_CNT, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_SAT, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_SAT, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_HUE, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_HUE, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        for (ui2_rec_idx = APP_CFG_RECID_VID_CLR_HUE_R ; ui2_rec_idx <= APP_CFG_RECID_VID_CLR_BRI_Y;  ui2_rec_idx++)
        {
            acfg_cust_video_get_predef_value_by_idx(IDX_CLR_HUE_R + (ui2_rec_idx - APP_CFG_RECID_VID_CLR_HUE_R), ui2_elem_idx,&i2_default_value);
            ACFG_LOG_ON_FAIL(i4_ret);
            acfg_set_int16_by_idx(IDX_CLR_HUE_R + (ui2_rec_idx - APP_CFG_RECID_VID_CLR_HUE_R), ui2_elem_idx, i2_default_value);
            ACFG_LOG_ON_FAIL(i4_ret);

        }

        i2_default_value = 1;
        i4_ret = acfg_set_int16_by_idx(IDX_RED, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_set_int16_by_idx(IDX_GREEN, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_set_int16_by_idx(IDX_BLUE, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_LIGHT_SENSOR_IDX, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_LIGHT_SENSOR_IDX, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_SHP, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_SHP, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_SUPER_RESOLUTION, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_SUPER_RESOLUTION, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_EN_VIEW_ANGLE, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_EN_VIEW_ANGLE, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_JUDDER_REDUCTION, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_JUDDER_REDUCTION, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_MOTION_BLUR_REDUCTION, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_MOTION_BLUR_REDUCTION, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        ACFG_DEBUG_NR_DEFAULT(
            DBG_LOG_PRINT(("[ACFG][NR][default]{%s,%s,%d}  \n", __FILE__, __FUNCTION__,__LINE__));
        );
        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_NR, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_NR, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_3D_NR, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_3D_NR, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

#ifdef APP_MPEG_NR_SUPPORT
        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_MPEG_NR, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_MPEG_NR, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
#endif
        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CLEAR_ACTION, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CLEAR_ACTION, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);


#ifdef APP_DI_SUPPORT
        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_DI_FILM_MODE, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_DI_FILM_MODE, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
#endif

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_CONTRAST_EN, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_CONTRAST_EN, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CLR_TEMP, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CLR_TEMP, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /* new add ,not include pq matrix*/
        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_VID_LOCAL_CONTRAST, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_VID_LOCAL_CONTRAST, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_CONTOUR_SMOOTHING, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_CONTOUR_SMOOTHING, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_EDGE_ENHANCEMENT, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_EDGE_ENHANCEMENT, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = acfg_cust_video_get_predef_value_by_idx(IDX_CUSTOM_PEAK_LUMINANCE, ui2_elem_idx,&i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);
        i4_ret = acfg_set_int16_by_idx(IDX_CUSTOM_PEAK_LUMINANCE, ui2_elem_idx, i2_default_value);
        ACFG_LOG_ON_FAIL(i4_ret);

        /* set the pq chg status*/
        a_cfg_set_preset_pic_mode_chg_status_by_ipt(ui1_pic_mode,ui1_inp_src,ui1_video_type, FALSE);

    }

    return APP_CFGR_OK;
}
extern INT32 acfg_cust_video_get_cust_gamma_def_value(
    INT16   i2_pic_mode,
    INT16*  pi2_val)
{
    if ((i2_pic_mode < 0)
        || (i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
        || (!pi2_val))
    {
        return APP_CFGR_INV_ARG;
    }

    if (/*(ACFG_CUST_PIC_MODE_GAME == i2_pic_mode)        //fix DTV00788297 mind 20160613 Game mode Gamma change to 2.1
        ||*/ (ACFG_CUST_PIC_MODE_DARK_ROOM == i2_pic_mode)
        || (ACFG_CUST_PIC_MODE_STANDARD == i2_pic_mode))
    {
        *pi2_val = ACFG_CUST_GAMMA_2_2;
    }
    else
    {
        *pi2_val = ACFG_CUST_GAMMA_2_1;
    }

    return APP_CFGR_OK;
}
extern INT32 acfg_cust_video_get_cust_clear_action_def_value(
    INT16   i2_pic_mode,
    INT16*  pi2_val)
{
    if ((i2_pic_mode < 0)
        || (i2_pic_mode >= ACFG_PRE_SET_PIC_MODE_NUM)
        || (!pi2_val))
    {
        return APP_CFGR_INV_ARG;
    }

    if (i2_pic_mode == ACFG_CUST_PIC_MODE_GAME)
    {
        *pi2_val = 1; //game mode default is ON
    }
    else
    {
        *pi2_val = 0; // other picture mode default is Off
    }

    return APP_CFGR_OK;
}

extern INT32 a_cfg_cust_update_color_tuner(VOID)
{
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
    return APP_CFGR_OK;
}

extern INT32 acfg_cust_video_get_di_film_mode_def_value(
    INT16*  pi2_val)
{
    *pi2_val = ACFG_CUST_DI_FILM_MODE_AUTO;
    return APP_CFGR_OK;
}

extern INT32 a_cfg_cust_update_crnt_11_point_value(VOID)
{
    return a_cfg_cust_drv_set_20_p_wb();
}

#ifdef NEVER
extern INT32 a_cfg_cust_update_crnt_11_point_value(VOID)
{
    UINT8       ui1_input_grp = acfg_check_play_content();
    UINT16      ui2_idx_begin = 0;
    UINT16      ui2_idx_end = 0;
    UINT16      ui2_idx = 0;
    UINT16      ui2_idx_itn = 0;
    INT16       i2_tmp_val = 0;
    INT16       i2_val = 0;
    INT32       i4_GammactrlPts[3][11] = {{0,0}};
    UINT8       ui1_odm_id = 0;
    INT8       i1_offset[3][11] = {{0,0}};
    a_cfg_custom_get_odm_idx(&ui1_odm_id);
//  if (ui1_odm_id == 2)         //Del Foxconn Tommy 20180408
//  if ((ui1_odm_id == 2) || (ui1_odm_id == 4))  //Add Foxconn Tommy 20180408  //Del AMT Mark 20180423
    if ((ui1_odm_id == 2) || (ui1_odm_id == 4) || (ui1_odm_id == 1))     //Add AMT Mark 20180423
    {
        //a_cfg_cust_get_white_balance_offset(&i2_offset);
        //DBG_LOG_PRINT(("%s_%d i2_offset:%d \n",__FUNCTION__,__LINE__,i2_offset));
        UINT8   ui1_j = 0;
        INT8    i1_R[44] = {0}, i1_G[44] = {0}, i1_B[44] = {0};
        SIZE_T  z_size;

        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_tmp_val);

        acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_RED, (VOID*)i1_R, &z_size);
        acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_GREEN, (VOID*)i1_G, &z_size);
        acfg_get(IDX_CUSTOM_FAC_CUST_11_POINT_BLUE, (VOID*)i1_B, &z_size);

        for (ui1_j = 0; ui1_j < 11; ui1_j++)
        {
            i1_offset[0][ui1_j] = i1_R[ui1_j + i2_tmp_val*11];
            i1_offset[1][ui1_j] = i1_G[ui1_j + i2_tmp_val*11];
            i1_offset[2][ui1_j] = i1_B[ui1_j + i2_tmp_val*11];
        }
    }

    if ((ui1_odm_id == 2) || (ui1_odm_id == 1)) //Add AMT David 20190116
    {
        UINT32 ui4_dynamic_address = 0;
        a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

        if(ui4_dynamic_address > 0)
        {
            //overwrite previous offset setting
            // Offset times refer to "menu_page_color_tuner.c"
            //INT32 i4_ret = 0;
            INT8 i1_R[11] = {0}, i1_G[11] = {0}, i1_B[11] = {0};
            UINT8 ui1_play_content = acfg_check_play_content();
            UINT32 ui4_read = 0;
            UINT8 ui1_j = 0;
            UINT32 ui4_dynamic_address = 0;
            const UINT8 ui1_offset[3][3] = {{0,1,2}, {3,4,5}, {6,7,8}};

            a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_tmp_val);

            a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_offset[i2_tmp_val - 1][ui1_play_content - 1] * 57 + 24,
                    (VOID *)&i1_R,
                    11,
                    &ui4_read);

            a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_offset[i2_tmp_val - 1][ui1_play_content - 1] * 57 + 35,
                    (VOID *)&i1_G,
                    11,
                    &ui4_read);

            a_cfg_eep_raw_read(
                    ui4_dynamic_address + ui1_offset[i2_tmp_val - 1][ui1_play_content - 1] * 57 + 46,
                    (VOID *)&i1_B,
                    11,
                    &ui4_read);

            for (ui1_j = 0; ui1_j < 11; ui1_j++)
            {
                i1_offset[0][ui1_j] = i1_R[ui1_j];
                i1_offset[1][ui1_j] = i1_G[ui1_j];
                i1_offset[2][ui1_j] = i1_B[ui1_j];

                //DBG_LOG_PRINT(("###ke_test i1_offset[0][%d]: %d\n", ui1_j, i1_offset[0][ui1_j]));  //ke_test
                //DBG_LOG_PRINT(("###ke_test i1_offset[1][%d]: %d\n", ui1_j, i1_offset[1][ui1_j]));  //ke_test
                //DBG_LOG_PRINT(("###ke_test i1_offset[2][%d]: %d\n", ui1_j, i1_offset[2][ui1_j]));  //ke_test
            }
        }

    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_tmp_val);

    ui2_idx_begin = ui1_input_grp*ACFG_CLR_TEMP_NUM*APP_CFG_11_POINT_GAIN_NUM + i2_tmp_val*APP_CFG_11_POINT_GAIN_NUM;
    ui2_idx_end = ui1_input_grp*ACFG_CLR_TEMP_NUM*APP_CFG_11_POINT_GAIN_NUM + i2_tmp_val*APP_CFG_11_POINT_GAIN_NUM + APP_CFG_11_POINT_GAIN_NUM;

    for (ui2_idx = ui2_idx_begin; ui2_idx < ui2_idx_end; ui2_idx ++)
    {
        acfg_get_int16_by_idx(IDX_11_POINT_GAIN_RED,
                           ui2_idx,
                           &i2_val);
        i4_GammactrlPts[0][ui2_idx_itn] = i2_val+i1_offset[0][ui2_idx_itn];

        acfg_get_int16_by_idx(IDX_11_POINT_GAIN_GREEN,
                           ui2_idx,
                           &i2_val);
        i4_GammactrlPts[1][ui2_idx_itn] = i2_val+i1_offset[1][ui2_idx_itn];

        acfg_get_int16_by_idx(IDX_11_POINT_GAIN_BLUE,
                           ui2_idx,
                           &i2_val);
        i4_GammactrlPts[2][ui2_idx_itn] = i2_val+i1_offset[2][ui2_idx_itn];
        ui2_idx_itn ++;
    }

    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_MANUAL_GAMMA;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)(i4_GammactrlPts);
    t_op_info.u.t_vid_set_info.z_size = sizeof(i4_GammactrlPts);
    t_op_info.u.t_vid_set_info.b_store = FALSE;


    c_rm_set_comp(DRVT_CUST_DRV,
                  DRV_CUST_COMP_ID,
                  FALSE,
                  ANY_PORT_NUM,
                  0,
                  &t_op_info,
                  z_size);

    return APP_CFGR_OK;

}
#endif /* NEVER */

extern INT32 a_cfg_cust_set_sys_boot_up_times(UINT32 ui4_sys_boot_up_times)
{
    INT32   i4_ret = APP_CFGR_OK;
    i4_ret = acfg_set(IDX_CUSTOM_SYS_BOOT_UP_TIMES, &ui4_sys_boot_up_times, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_cust_get_sys_boot_up_times(UINT32 *pui4_sys_boot_up_times)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;
    UINT32      ui4_value = 0;
    if (!pui4_sys_boot_up_times)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_SYS_BOOT_UP_TIMES, &ui4_value, &z_size);

    *pui4_sys_boot_up_times = ui4_value;

    return i4_ret;
}

extern INT32 a_cfg_cust_set_sys_total_running_time(UINT32 ui4_running_times)
{
    INT32   i4_ret = APP_CFGR_OK;
    i4_ret = acfg_set(IDX_CUSTOM_SYS_TOTAL_RUNNING_TIME, &ui4_running_times, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_cust_get_sys_total_running_time(UINT32 *pui4_running_times)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;
    UINT32      ui4_value = 0;

    if (!pui4_running_times)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_SYS_TOTAL_RUNNING_TIME, &ui4_value, &z_size);

    *pui4_running_times = ui4_value;

    return i4_ret;
}

/* tv speaker auto on off set*/
extern INT32 a_cfg_custom_set_speakers_out(UINT16 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_SPEAKER_OUT_ADDRESS, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

/* tv speaker auto on off get*/
extern INT32 a_cfg_custom_get_speakers_out(UINT16 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_SPEAKER_OUT_ADDRESS, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

/* tv earc on off set*/
extern INT32 a_cfg_custom_set_earc(UINT16 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_EARC_MODE, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

/* tv earc on off get*/
extern INT32 a_cfg_custom_get_earc(UINT16 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

#ifdef MT5583_MODEL
    *pui1_val = 0;
    return i4_ret;
#endif
    i4_ret = acfg_get(IDX_CUSTOM_EARC_MODE, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_set_blegatt_macaddress_threshold(BLE_CACHE_DEVICE* ui1_value)
{
    INT32 i4_ret = APP_CFGR_OK;

    if (ui1_value != NULL)
    {
        i4_ret = a_cfg_set_blegatt_cache_dev(ui1_value);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("<ACFG> a_cfg_get_blegatt_macaddress_threshold fail, error code: %d\n", i4_ret));
            return i4_ret;
        }
    }
    else
    {
        i4_ret = APP_CFGR_INV_ARG;
        DBG_ERROR(("<ACFG> a_cfg_get_blegatt_macaddress_threshold fail, error code: %d\n", i4_ret));
    }

    return APP_CFGR_OK;
}

extern INT32 a_cfg_get_blegatt_macaddress_threshold(BLE_CACHE_DEVICE *pui1_value)
{
    INT32    i4_ret = APP_CFGR_OK;

    if (pui1_value != NULL)
    {
        i4_ret = a_cfg_get_blegatt_cache_dev(pui1_value);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("<ACFG> a_cfg_get_blegatt_macaddress_threshold fail, error code: %d\n", i4_ret));
            return i4_ret;
        }
    }
    else
    {
        DBG_ERROR(("<ACFG> a_cfg_get_blegatt_macaddress_threshold fail, error code: %d\n", i4_ret));
        i4_ret = APP_CFGR_INV_ARG;

    }

    return APP_CFGR_OK;
}

extern INT32 a_cfg_cust_set_log_to_usb_status(UINT8 ui1_log_to_usb_status)
{
    INT32   i4_ret = APP_CFGR_OK;
    i4_ret = acfg_set(IDX_CUSTOM_LOG_TO_USB, &ui1_log_to_usb_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

extern INT32 a_cfg_cust_get_log_to_usb_status(UINT8 *pui1_log_to_usb_status)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_value = 0;

    if (!pui1_log_to_usb_status)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_LOG_TO_USB, &ui1_value, &z_size);

    *pui1_log_to_usb_status = ui1_value;

    return i4_ret;
}

extern INT32 a_cfg_set_fs_partition_all (VOID)
{
    DBG_INFO(("\n[ACFG]a_cfg_set_fs_partition_all()\n"));
    b_g_fs_partition_all = TRUE;

    return APP_CFGR_OK;
}

extern BOOL a_cfg_is_fs_partition_all (VOID)
{
    return b_g_fs_partition_all;
}

/* KK_PORTING */
INT32 a_cfg_cust_set_Gamma_table(VID_CUSTOM_TYPE_SET_NVM_GAMMA_T prNVMGamma)
{
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T t_cust_set_info = {0};
    SIZE_T      z_size = sizeof(VID_CUSTOM_TYPE_SET_NVM_GAMMA_T);
    DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    t_cust_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_NVM_GAMMA;
    t_cust_set_info.pv_set_info = (VOID *)&prNVMGamma;
    t_cust_set_info.z_size = z_size;
    t_cust_set_info.b_store = TRUE;
    i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_cust_set_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("%s : a_cfg_cust_set_Gamma_table fail\n", __FUNCTION__));
        return i4_ret;
    }
    return APP_CFGR_OK;
}
/*for INX Gamma table*/
INT32 a_cfg_cust_set_Gamma_table_For_INX(VID_CUSTOM_TYPE_SET_NVM_GAMMA_T prNVMGamma)
{
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T t_cust_set_info = {0};
    SIZE_T      z_size = sizeof(VID_CUSTOM_TYPE_SET_NVM_GAMMA_T);
    DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    t_cust_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_NVM_GAMMA_FOR_INX;
    t_cust_set_info.pv_set_info = (VOID *)&prNVMGamma;
    t_cust_set_info.z_size = z_size;
    t_cust_set_info.b_store = TRUE;
    i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_cust_set_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("%s : a_cfg_cust_set_Gamma_table_For_INX fail\n", __FUNCTION__));
        return i4_ret;
    }
    return APP_CFGR_OK;
}

INT32 a_cfg_cust_get_gamma_table(VOID* pv_data, SIZE_T z_size_val)
{
    DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};

    if(pv_data == NULL)
    {
        DBG_ERROR(("[ACFG] pt_gamma_info is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }


    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_FACTORY_GAMMA_VALUE;
    t_get_info.pv_get_info = (VOID *)pv_data;
    t_get_info.pz_size = &z_size_val;
    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("%s : a_cfg_cust_get_gamma_table fail\n", __FUNCTION__));
        return i4_ret;
    }
    return APP_CFGR_OK;
}

INT32 a_cfg_cust_set_gamma_on_off(BOOL bOnOff)
{
    DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T     t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(bOnOff);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_FACTORY_GAMMA_ONOFF;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&bOnOff;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    return RMR_OK;
}

INT32 a_cfg_cust_get_gamma_on_off(BOOL *bOnOff)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(bOnOff);
    DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_FACTORY_GAMMA_ONOFF;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)bOnOff;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
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

    return RMR_OK;
}


INT32 a_cfg_cust_set_gamma_enable_by_temp(VOID* pv_data, SIZE_T z_size_val)
{
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T    t_set_info = {0};
    if(pv_data == NULL )
    {
        ACFG_DBG_PRINT(" pv_data == NULL  \r\n");
        return APP_CFGR_INTERNAL_ERR;
    }

    t_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GAMMA_ONOFF;
    t_set_info.pv_set_info = (VOID *)pv_data;
    t_set_info.z_size = z_size_val;
    t_set_info.b_store = TRUE;
    i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_set_info);
    if (i4_ret != APP_CFGR_OK)
    {
        ACFG_DBG_PRINT(" a_cfg_set_drv_comp Fail :i4_ret:%d  \r\n",i4_ret);
        return i4_ret;
    }

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Picture Mode
 ----------------------------------------------------------------------------*/
INT32 VIZIO_Picture_mode_D_SET(UINT16 ui2_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(ui2_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_Picture_MODE_VAL;
    t_op_info.u.t_vid_set_info.b_store = TRUE;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)&ui2_idx;
    t_op_info.u.t_vid_set_info.z_size = z_size;


    /* get from driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 VIZIO_COPY_Picture_mode_D_SET(INT16 i2_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(i2_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_CUST_SPEC_TYPE_COPY_PIC_MODE_NOTIFY;
    t_op_info.u.t_vid_set_info.b_store = TRUE;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)&i2_idx;
    t_op_info.u.t_vid_set_info.z_size = z_size;


    /* set to driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 VIZIO_SMART_DIMMING_D_SET(UINT16 ui2_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(ui2_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    #if 1
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SMART_DIMMING;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;
    #endif

    /* get from driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

BOOL a_cfg_cust_BacklightCtrl_CheckIfCanTurnOn(void)
{
    if( a_cfg_cust_get_support_local_dimming() ) // Local dimming
    {
        return FALSE;
    }

    // Backlight ctrl ...

    UINT8 u8HdrType = a_acfg_cust_get_video_type();
    //DBG_LOG_PRINT(("[MENU][HDR]{%s: %s: %d} u8HdrType:%d\n", __FILE__, __FUNCTION__,__LINE__, u8HdrType));

 #if 0
    //for backlight control, it need gray out when HDR
    if( ACFG_CUST_CONTENT_SDR != u8HdrType )
    {
        //ACFG_DEBUG_BACKLIGHT( DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL] {%s: %d} u8HdrType:%d => Cannot turn on BacklightCtrl\n", __FUNCTION__,__LINE__, u8HdrType)); );
        return FALSE;
    }
 #else
    //for backlight control ,it need gray out when dv
    if( u8HdrType == ACFG_CUST_CONTENT_DV )
    {
         return FALSE;
    }
 #endif

    return TRUE;
}

static BOOL b_slogo_forced_update_ld = FALSE;
VOID a_cfg_cust_backlight_ctrl_lock(BOOL b_lock)
{
    b_g_backlight_ctrl_lock = b_lock;
    BOOL b_support_local_dimming = a_cfg_cust_get_support_local_dimming();
    if (b_g_backlight_ctrl_lock)
    {
        b_slogo_forced_update_ld = FALSE;
        if (b_support_local_dimming)
        {
            dtv_svc_write_timestamp("[LOGO][LDM] backlight ctrl locked");
        }
        else
        {
            dtv_svc_write_timestamp("[LOGO] backlight ctrl locked");
        }
        DBG_INFO(("[ACFG] locked\n"));
        return;
    }
    UINT16 ui2_acfg_id = 0;
    if (b_support_local_dimming)
    {
        b_slogo_forced_update_ld = TRUE;
        ui2_acfg_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING);
        a_cfg_av_update(ui2_acfg_id); //Rollback lastest BL ctrl setting by locking
        dtv_svc_write_timestamp("[LOGO][LDM] backlight ctrl unlocked & updated");
    }
    else
    {
        ui2_acfg_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO,APP_CFG_RECID_VID_CUSTOM_DCR);
        a_cfg_av_update(ui2_acfg_id);
        dtv_svc_write_timestamp("[LOGO] backlight ctrl unlocked & updated");
    }
    DBG_INFO(("[ACFG][%s] unlocked & updated\n"));
}

static INT32 VIZIO_BACKLIGHT_CONTROL_D_SET_IMPL(UINT16 ui2_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(ui2_idx);

    if(FALSE == acfg_is_backlight_control_enable())
    {
        ui2_idx = 0;
    }

    if( ui2_idx ) // Turn on backlight_ctrl
    {
        if( FALSE == a_cfg_cust_BacklightCtrl_CheckIfCanTurnOn() )
        {
            ui2_idx = 0;
            //ACFG_DEBUG_BACKLIGHT( DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL] {%s: %d} Cannot turn on BacklightCtrl! Force to off\n", __FUNCTION__,__LINE__)); );
        }
    }


    ACFG_DEBUG_BACKLIGHT(
        DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL]{%s: %d} Call scc( DRV_CUSTOM_CUST_SPEC_TYPE_BACKLIGHT_CONTROL, ui2_idx = %d\n",
                                        __FUNCTION__, __LINE__, ui2_idx ));
    );

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_BACKLIGHT_CONTROL;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;
    DBG_INFO(("[ACFG][%s %d] VIZIO_BACKLIGHT_CONTROL_D_SET %d\n",__FUNCTION__,__LINE__,ui2_idx));

    /* get from driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}


INT32 VIZIO_BACKLIGHT_CONTROL_D_SET(UINT16 ui2_idx)
{

    if (b_g_backlight_ctrl_lock)
    {
        char tmp[128]={0};
        sprintf(tmp,"Vlogo showing, skip backlight ctrl set %d", ui2_idx);
        dtv_svc_write_timestamp(tmp);
        DBG_INFO(("[ACFG][%s %d] Vlogo showing, skip backlight ctrl set %d\n",__FUNCTION__,__LINE__,ui2_idx));
        return 0;
    }

    return VIZIO_BACKLIGHT_CONTROL_D_SET_IMPL(ui2_idx);
}

INT32 VIZIO_BACKLIGHT_CONTROL_D_SET_FORCE(UINT16 ui2_idx)
{
    return VIZIO_BACKLIGHT_CONTROL_D_SET_IMPL(ui2_idx);
}


BOOL a_cfg_cust_LightSensor_CheckIfCanTurnOn(void)
{
    INT16  i2_value = 0;
    INT32  i4_ret   = 0;


    // Check ICL_WIZARD_STATUS ...
    UINT8   ui1_wzd_sts = ICL_WIZARD_STATUS_PAUSE;
    SIZE_T  z_size = ICL_RECID_WIZARD_STATUS_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_WIZARD_STATUS, ICL_RECID_WIZARD_STATUS), &ui1_wzd_sts, &z_size);
    if( i4_ret == APP_CFGR_OK )
    {
        if( ui1_wzd_sts == ICL_WIZARD_STATUS_RESUME )
        {
            ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
                DBG_LOG_PRINT(("[ACFG][LightSensor]{%s: %d} ICL_WIZARD_STATUS_RESUME => LightSensor cannot turn on!\n", __FUNCTION__,__LINE__ ));
            );
            return FALSE;
        }
    }


    // Check retail mode...
	ACFG_RETAIL_MODE_T t_retail_mode = 0;
    if( APP_CFGR_OK == a_cfg_custom_get_retail_mode_setting(&t_retail_mode) )
    {
        if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
        {
            ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
                DBG_LOG_PRINT(("[ACFG][LightSensor]{%s: %d} RETAIL_MODE_NORMAL => LightSensor cannot turn on!\n", __FUNCTION__,__LINE__ ));
            );
            return FALSE;
        }
    }

    // Check HDR type ...
    if (a_acfg_cust_get_dynamic_range() != ACFG_CUST_CONTENT_SDR)
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
            DBG_LOG_PRINT(("[ACFG][LightSensor]{%s: %d} HDR => LightSensor Off!\n", __FUNCTION__,__LINE__ ));
        );

        return FALSE;
    }

    // Check ClearAction ...
    //if( a_cfg_cust_get_support_clear_aciton() == TRUE )
    if( a_cfg_cust_ClaerAction_if_can_turn_on() == TRUE )
    {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION), &i2_value);
        if( i4_ret < 0 )
        {
            DBG_LOG_PRINT(("[ACFG][LightSensor]{%s:%d} Error: Cannot get APP_CFG_RECID_VID_CLEAR_ACTION fail! rtn:%d \n", __FILE__, __LINE__, i4_ret));
            i2_value = 0;
        }

        if( i2_value != 0 ) // Clear Action is On
        {
            ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
                DBG_LOG_PRINT(("[ACFG][LightSensor]{%s: %d} Clear Action is On => LightSensor Off!\n", __FUNCTION__,__LINE__ ));
            );

            return FALSE;
        }
    }

    // Check reduce_blur ...
    UINT8   ui1_blur = 0;
    BOOL    b_is_reduce_blur_support = FALSE;
    if( APP_CFGR_OK == a_cfg_custom_is_reduce_blur_support(&b_is_reduce_blur_support) )
    {
        if( b_is_reduce_blur_support )
        {
            if( APP_CFGR_OK == a_cfg_custom_get_reduce_blur(&ui1_blur) )
            {
                if (ui1_blur != 0)
                {
                    ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
                        DBG_LOG_PRINT(("[ACFG][LightSensor]{%s: %d} reduce_blur is On => LightSensor cannot turn on!\n", __FUNCTION__,__LINE__ ));
                    );
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

INT32 VIZIO_AMBIENT_LIGHT_SENSOR_D_SET(UINT16 ui2_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(ui2_idx);


    ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
        DBG_LOG_PRINT(("[Acfg_Drv][LightSensor] %s(%d) \n", __FUNCTION__, ui2_idx));
    );

    if( ui2_idx > 0 ) // Want to turn on
    {
        if( FALSE == a_cfg_cust_LightSensor_CheckIfCanTurnOn() ) // Cannot turn on
        {
            ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
                DBG_LOG_PRINT(("[Acfg_Drv][LightSensor]{%s: %d} Cannot turn on LightSensor => Force driver val = 0\n", __FUNCTION__,__LINE__ ));
            );
            ui2_idx = 0;
        }
    }


    DBG_LOG_PRINT(("[Acfg_Drv][LightSensor]{%s,%d} Set driver = %d\n", __FUNCTION__,__LINE__, ui2_idx ));

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_AMBIENT_LIGHT_SENSOR;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* get from driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 VIZIO_ADAPTIVE_LUMA_D_SET(UINT16 ui2_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(ui2_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_ADAPTIVE_LUMA;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* get from driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

// ClearAction:
//#define ACFG_CUS_DEBUG_CLEAR_ACTION(x)  //x
BOOL a_cfg_cust_ClaerAction_if_can_turn_on(void)
{
    TV_WIN_ID_T     e_tv_win_id = 0;
    //INT16 i2_vrr = 0;
    INT32 i4_ret = 0;


    if( a_cfg_cust_get_support_clear_aciton() != TRUE )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_CLEAR_ACTION,
            DBG_LOG_PRINT(("[ACFG][ClearAction]{%s,%d} driver not support ClearAction!\n", __FUNCTION__,__LINE__));
        );
        return FALSE;
    }

    //note: no signal need close clear action
    i4_ret = nav_get_focus_id(&e_tv_win_id);
    if( (i4_ret == 0) && (TRUE == nav_is_signal_loss(e_tv_win_id)) )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_CLEAR_ACTION,
            DBG_LOG_PRINT(("[ACFG][ClearAction]{%s,%d} NoSignal ==> Force ClearAction to off\n", __FUNCTION__,__LINE__));
        );
        return FALSE;
    }


    if( a_cfg_cust_is_support_progaming_engine() == TRUE ) // HDMI
    {
        if( a_acfg_cust_is_detect_hdmi_freesync_flag() )
        {
            ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_CLEAR_ACTION,
                DBG_LOG_PRINT(("[ACFG][ClearAction]{%s,%d} freesync detected ==> Force ClearAction to off\n", __FUNCTION__,__LINE__));
            );
            return FALSE;
        }

        if( (a_cfg_cust_is_variable_refresh_rate_support() == TRUE) )
        {
            if( a_cfg_cust_is_VRR_enable_and_driver_detect_VRR() )
            {
                ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_CLEAR_ACTION,
                    DBG_LOG_PRINT(("[ACFG][ClearAction]{%s,%d} VRR detected ==> Force ClearAction to off\n", __FUNCTION__,__LINE__));
                );
                return FALSE;
            }
        }

    }

    return TRUE;
}

INT32 VIZIO_CLEAR_ACTION_D_SET(UINT16 ui2_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(ui2_idx);
    ACFG_DBG_INFO("Set ui2_idx :%d \r\n",ui2_idx);


    if( ui2_idx )
    {
        // If cannot turn on, force off to driver...
        BOOL bClearActionCanTurnOn = a_cfg_cust_ClaerAction_if_can_turn_on();
        if( FALSE == bClearActionCanTurnOn )
        {
            DBG_LOG_PRINT(("[ACFG][ClearAction]{%s,%d} Cannot turn on! Force val=0!\n", __FUNCTION__,__LINE__ ));
            ui2_idx = 0;
        }
    }

    DBG_LOG_PRINT(("[ACFG][ClearAction]{%s: %d} Set driver( ui2_idx=%d)\n", __FUNCTION__,__LINE__, ui2_idx));

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_CLEAR_ACTION;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* get from driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}


static INT32 VIZIO_EXTREME_BLACK_ENGINE_D_SET_IMPL(UINT16 ui2_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(ui2_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_EXTREME_BLACK_ENGINE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* get from driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;

}


INT32 VIZIO_EXTREME_BLACK_ENGINE_D_SET(UINT16 ui2_idx)
{

    if (b_g_backlight_ctrl_lock)
    {
        char tmp[128]={0};
        sprintf(tmp,"Vlogo showing, skip local diming set %d", ui2_idx);
        dtv_svc_write_timestamp(tmp);
        DBG_INFO(("[ACFG][%s %d] Vlogo showing, skip local diming set %d\n",__FUNCTION__,__LINE__,ui2_idx));
        return 0;
    }

    return VIZIO_EXTREME_BLACK_ENGINE_D_SET_IMPL(ui2_idx);

}

INT32 VIZIO_EXTREME_BLACK_ENGINE_D_SET_FORCE(UINT16 ui2_idx)
{
    return VIZIO_EXTREME_BLACK_ENGINE_D_SET_IMPL(ui2_idx);
}



//when local diming device scaning,set it to notify driver
INT32 VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(BOOL ui2_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(ui2_idx);
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_LDM_COMPENSATION;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;
    DBG_INFO(("[xinchen ACFG][%s %d] VIZIO_BACKLIGHT_CONTROL_D_SET %d\n",__FUNCTION__,__LINE__,ui2_idx));
    /* get from driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}


/* use internet time set*/
INT32 a_cfg_cust_set_net_time(UINT8  net_time_status)
{
    return acfg_set(IDX_CUSTOM_USE_INTERNET_TIME, &net_time_status, 1);
}

/* use internet time get*/
INT32 a_cfg_cust_get_net_time(UINT8* net_time_status)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUSTOM_USE_INTERNET_TIME, net_time_status, &z_size);
}


/* rest time format set*/
INT32 a_cfg_cust_set_time_format(UINT8  time_format)
{
    return acfg_set(IDX_CUSTOM_TIME_FORMAT, &time_format, 1);
}

/* use internet time get*/
INT32 a_cfg_cust_get_time_format(UINT8* time_format)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUSTOM_TIME_FORMAT, time_format, &z_size);
}

/* digital audio auto */
extern INT32 a_cfg_custom_set_digital_audio(UINT16 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_DIGITAL_AUDIO_ADDRESS, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

/* digital audio auto */
extern INT32 a_cfg_custom_get_digital_audio(UINT16 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    UINT16   i2_val = 0;
    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16  ui2_aud_out_mask;
    INT16   i2_val_ex = 0;
    UINT16  ui2_aud_out_value = 0;

    a_cfg_av_get(ui2_id, &i2_val_ex);
    ui2_aud_out_mask = (UINT16)i2_val_ex;

    a_cfg_custom_get_speakers_out(&i2_val);
    if(APP_CFG_AUD_AD_SPEAKER_AUTO == i2_val) //Auto
    {
       ui2_aud_out_value = APP_CFG_AUD_AD_SPEAKER_AUTO;
    }
    else
    {
       if(ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) //ON
       {
           ui2_aud_out_value = APP_CFG_AUD_AD_SPEAKER_ON;
       }
       else    //OFF
       {
           ui2_aud_out_value = APP_CFG_AUD_AD_SPEAKER_OFF;
       }
    }

    if (ui2_aud_out_value == APP_CFG_AUD_AD_SPEAKER_ON)
    {
       *pui1_val = AUD_SPDIF_AUDIO_OUT_PCM;
    }
    else
    {
       i4_ret = acfg_get(IDX_CUSTOM_DIGITAL_AUDIO_ADDRESS, pui1_val, &z_size);
       ACFG_CHK_FAIL(i4_ret, i4_ret);
    }

    return i4_ret;
}

/* last channel id set*/
INT32 a_cfg_cust_set_last_channel_id(UINT32  ui4_channel_id)
{
    return acfg_set(IDX_CUSTOM_LAST_CHANNEL_ID, &ui4_channel_id, 1);
}

/* last channel id  get*/
INT32 a_cfg_cust_get_last_channel_id(UINT32* pui4_channel_id)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUSTOM_LAST_CHANNEL_ID, pui4_channel_id, &z_size);
}
/* color tuner offset  set*/
INT32 a_cfg_cust_set_color_tune_offset(UINT8  ui1_value)
{
    return acfg_set(IDX_CUSTOM_COLOR_TUNER_OFFSET_ID, &ui1_value, 1);
}

/* color tune offset get*/
INT32 a_cfg_cust_get_color_tune_offset(UINT8* pui1_value)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUSTOM_COLOR_TUNER_OFFSET_ID, pui1_value, &z_size);
}

/* color tuner offset  set*/
INT32 a_cfg_cust_set_white_balance_offset(INT16 i2_value)
{
    return acfg_set(IDX_CUSTOM_WHITE_BALANCE_OFFSET_ID, &i2_value, 1);
}

/* color tune offset get*/
INT32 a_cfg_cust_get_white_balance_offset(INT16 *pi2_value)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUSTOM_WHITE_BALANCE_OFFSET_ID, pi2_value, &z_size);
}


/* last channel tuner type set*/
INT32 a_cfg_cust_set_last_channel_tuner_type(UINT8  ui1_tt)
{
    return acfg_set(IDX_CUSTOM_LAST_CHANNEL_TUNER_TYPE, &ui1_tt, 1);
}

/* last channel tuner type get*/
INT32 a_cfg_cust_get_last_channel_tuner_type(UINT8* pui1_tt)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUSTOM_LAST_CHANNEL_TUNER_TYPE, pui1_tt, &z_size);
}

INT32 a_cfg_custom_get_model_group_id(UINT32 *pui4_model_group)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(pui4_model_group);


    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_MODEL_GROUP;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_model_group;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
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

INT32 a_cfg_custom_get_odm_idx(UINT8 *pui1_odm_idx)
{
    INT32                       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T   t_op_info = {0};
    SIZE_T                      z_size_drv = 0;
    static BOOL                 b_is_get_odm_idx = FALSE;
    static UINT8                ui1_odm_idx = 0;
    SIZE_T                      z_size = 0;

    if (NULL == pui1_odm_idx)
    {
        DBG_ERROR(("[ACFG] Error: %s\n", __FUNCTION__));
        return APP_CFGR_INV_ARG;
    }

    if (!b_is_get_odm_idx)
    {
        z_size = sizeof(UINT8);
        z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

        c_memset (&t_op_info, 0, sizeof (DRV_CUST_OPERATION_INFO_T));

        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_ODM_INDEX;
        t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_odm_idx;
        t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

        /* get from driver */
        i4_ret = c_rm_get_comp(
                     DRVT_CUST_DRV,
                     DRV_CUST_COMP_ID,
                     FALSE,
                     ANY_PORT_NUM,
                     0,
                     &t_op_info,
                     &z_size_drv
                     );
        if(i4_ret != RMR_OK)
        {
            DBG_ERROR(("<ACFG> Func: %s Get Fail i4_ret : %d\n", __FUNCTION__, i4_ret));
            return APP_CFGR_INTERNAL_ERR;
        }

        b_is_get_odm_idx = TRUE;
    }

    *pui1_odm_idx = ui1_odm_idx;

    if(ui1_odm_idx == 0)
        *pui1_odm_idx = ODM_ID_TPV;

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_model_idx(UINT32 *pui4_model_idx)
{
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};
    UINT32      ui4_model_idx = 0;
    SIZE_T      z_size = sizeof(UINT32);

    if (NULL == pui4_model_idx)
    {
        return APP_CFGR_INV_ARG;
    }

    z_size = sizeof(UINT32);
    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_READ_MODEL_INDEX;
    t_get_info.pv_get_info = (VOID *)&ui4_model_idx;
    t_get_info.pz_size = &z_size;
    a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,
                        (VOID*)&t_get_info);

    *pui4_model_idx = ui4_model_idx;

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_get_model_name(CHAR *ps_model_name)
{
    c_strncpy(ps_model_name, sz_g_model_name, strlen(sz_g_model_name));

    return APP_CFGR_OK;
}

EnuCusModelSeries a_cfg_cust_get_CurModelSeries(void)
{
    return s_eCurModelSeries;
}

UINT16 a_cfg_cust_get_CurModelYear(void)
{
    return s_u16CurModel_Year;
}

BOOL a_cfg_cust_Is_CurModel_2020(void)
{
    return (s_u16CurModel_Year == 2020);
}

BOOL a_cfg_cust_Is_CurModel_2021(void)
{
    //return s_bIsCurModel_2021;
    return (s_u16CurModel_Year == 2021);
}

BOOL a_cfg_cust_Is_CurModel_after_2021_J(void)
{
    //return s_bIsCurModel_2021;
    return (s_u16CurModel_Year >= 2021);
}

BOOL a_cfg_cust_Is_CurModel_2022_K(void)
{
    return (s_u16CurModel_Year == 2022);
}

BOOL a_cfg_cust_Is_CurModel_after_2022_K(void)
{
    return (s_u16CurModel_Year >= 2022);
}

BOOL a_cfg_cust_Is_CurModel_OLED(void)
{
    return (s_b_is_OLED_model);
}

BOOL a_cfg_cust_Is_CurModel_P_series(void)
{
#if( defined(MT5695_MODEL)||defined(MT5695L_MODEL) )
    switch(s_eCurModelSeries)
    {
        case CUS_MODEL_2021_95_P9: // 15, P***9-J**: P65Q9-J01
        case CUS_MODEL_2021_95_PX: // 16, P***X-J**:
        case CUS_MODEL_2022_95S_P: // 23, P65QXM-K04
            return TRUE;

        default: break;
    }
#endif

    return FALSE;
}


#define ACFG_CUS_DEBUG_MODEL(x)     //x
EnuCusModelSeries a_cfg_cust_Convert_ModelNameToModelSeries(const CHAR* pcModelName)
{
    if( pcModelName == NULL )
    {
        return CUS_MODEL_UNKNOWN;
    }

    ACFG_CUS_DEBUG_MODEL( DBG_LOG_PRINT(("[ACFG][%s] pcModelName:%s\n", __FUNCTION__, pcModelName )); );

    BOOL bIs2020Model = FALSE;
    BOOL bIs2021Model = FALSE;
    BOOL bIs2022Model = FALSE;

    if( c_strstr(pcModelName, "-H") != NULL ) // 2020 model
    {
        bIs2020Model = TRUE;
    }
    else if( c_strstr(pcModelName, "-J") != NULL ) // 2021 model
    {
        bIs2021Model = TRUE;
    }
    else if( c_strstr(pcModelName, "-K") != NULL ) // 2022 model
    {
        bIs2022Model = TRUE;
    }
    else
    {
        DBG_LOG_PRINT(("[ACFG]{%s:%d} Error: Invalid model name:[%s]\n", __FUNCTION__, __LINE__, pcModelName));
        return CUS_MODEL_UNKNOWN;
    }

    BOOL bIsOLEDModel = FALSE;
    if( c_strstr(pcModelName, "OLED") != NULL ) // OLED model
    {
        bIsOLEDModel =  TRUE;
    }


    if(bIs2022Model) //2022
    {
        switch(pcModelName[0])
        {
            case 'D': // 2022 5583 D series
              #if( defined(MT5583_MODEL) )
                //if( pcModelName[3] == 'F' ) // D**F*-K**:
                {
                    return CUS_MODEL_2022_83_2K_D; // 21, D**F4-K**:
                }
              #endif
                break;

            case 'V': // 2022 5691 V series
              #if( defined(MT5691_MODEL) )
                //if(pcModelName[3] == '6') // V**6-K**
                {
                    return CUS_MODEL_2022_91_V6; // 20, V**Q6-K**:
                }
              #elif( defined(MT5695L_MODEL) )
                {
                    return CUS_MODEL_2022_95L_V6; // 24, V**CM-K**:
                }
              #endif
                break;

            case 'M': // 2022 5691 M series

              #if( defined(MT5695_MODEL)&&defined(MT5695_FAMILY_S) )
                    return CUS_MODEL_2022_95S_M9;  // 22, M**Q9-K**: M43Q9-K01, M65Q9-K03

              #elif( defined(MT5691_MODEL) )
                //if( (pcModelName[3] == 'Q') && (pcModelName[4] == '6') )
                {
                    return CUS_MODEL_2022_91_M6; // 19, M**Q6-K**:
                }
              #endif

                break;

            case 'P':
              #if( defined(MT5695_MODEL)||defined(MT5695_FAMILY_S) )
                return CUS_MODEL_2022_95S_P; // 23, P65QXM-K04
              #endif
                break;

            default:
                break;
        }

    }
    else if( bIs2021Model ) // 2021
    {
        if( bIsOLEDModel ) // 2021 OLED
        {
            return CUS_MODEL_2021_95_OLED; // OLED**-J*:
        }
        else
        {
            switch(pcModelName[0])
            {
                case 'D': // 2021 5583 D series
                    if( pcModelName[3] == 'f' ) // D**f*-J**: D24f4-J01/D24f-J09
                    {
                        if((c_strstr(pcModelName, "D24f4-J01") != NULL) || (c_strstr(pcModelName, "D32f4-J01") != NULL) ||
                            (c_strstr(pcModelName, "D24f-J09") != NULL) || (c_strstr(pcModelName, "D40f-J09") != NULL))
                        {
                            b_2021_83_FHD_is_FreeSync_logo_support = TRUE;
                        }
                        return CUS_MODEL_2021_83_2K_D_FHD; // D**f*-J**: D24f4-J01/D24f-J09
                    }
                    else
                    {
                        return CUS_MODEL_2021_83_2K_D_HD;  // D**h-J**: D32h-J05
                    }
                    break;

                case 'V': // 2021 5691 V series
                    if( (pcModelName[3] == 'C') && (pcModelName[4] == '6') ) // 2021-5695L V6 // 18, V**C6-J**: V50C6-J09, V65C6-J09,
                    {
                        return CUS_MODEL_2021_95L_V6; // 2021-5695L V6 // 18, V**C6-J**: V50C6-J09, V65C6-J09,
                    }
                    else if( pcModelName[3] == '6' ) // 2021 5691 V6
                    {
                        return CUS_MODEL_2021_91_V6; // V**6*-J**: V556-J01/V556*-J01
                    }
                    else
                    {
                        return CUS_MODEL_2021_91_V5; // V**5-J**: V435-J01
                    }
                    break;

                case 'M': // 2021 5691 M series
                    if( pcModelName[4] == '8' )
                    {
                        return CUS_MODEL_2021_91_M8; // M***8-J**: none
                    }
                    else if( pcModelName[4] == '7' )
                    {
                        return CUS_MODEL_2021_91_M7; // M***7-J**: M50Q7-J01
                    }
                    else
                    {
                        return CUS_MODEL_2021_91_M6; // M***6-J**: M50Q6-J01
                    }
                    break;

                case 'P': // 2021-5695 P Series ...
                    if( pcModelName[4] == 'X' )
                    {
                        return CUS_MODEL_2021_95_PX; // P***X-J**:
                    }
                    else
                    {
                        return CUS_MODEL_2021_95_P9; // P***9-J**: P65Q9-J01
                    }
                    break;

                default:
                    break;
            }
        }
    }
    else if( bIs2020Model )// 2020
    {
        if( bIsOLEDModel ) // 2020 OLED support
        {
            return CUS_MODEL_2020_95_OLED; // OLED**-H*: OLED55-H1/OLED65-H1
        }
        else
        {
            switch( pcModelName[0] )
            {
                case 'V': // 2020 5691 V series
                    {
                        return CUS_MODEL_2020_91_V5; // V**5-H**: V585-H1
                    }
                    break;

                case 'M': // 2020 5691 M series
                    if( pcModelName[4] == '8' )
                    {
                        return CUS_MODEL_2020_91_M8; // M***8-H*: M55Q8-H1
                    }
                    else if( pcModelName[4] == '7' )
                    {
                        return CUS_MODEL_2020_91_M7; // M***7-H*: M55Q7-H1
                    }
                    else
                    {
                        return CUS_MODEL_2020_91_M6; // M**6-H*: M556-H1/M586x-H1
                    }
                    break;


                case 'P': // 2020-5695 P Series ...
                    if( pcModelName[4] == 'X' )
                    {
                        return CUS_MODEL_2020_95_PX; // P***X-H*: P75QX-H1
                    }
                    else
                    {
                        return CUS_MODEL_2020_95_P9; // P***9-H**: P65Q9-H1
                    }
                    break;

                default:
                    break;
            }
        }
    }


    DBG_LOG_PRINT(("[ACFG]{%s:%d} Error: Invalid model name:[%s]\n", __FUNCTION__, __LINE__, pcModelName));

    return CUS_MODEL_UNKNOWN;
}

void a_cfg_cust_get_wifi_model_name(CHAR *ps_model_name, int size)
{
    CHAR tmp[32] = {0};

    c_memset(ps_model_name,0,sizeof(CHAR)*size);
    c_memset(tmp,0,sizeof(CHAR)*32);
    if(c_strlen(s_wifi_module_name) != 0)
    {
        c_strncpy(ps_model_name, s_wifi_module_name, ACFG_CUSTOM_WIFI_MODULE_NAME_LEN);
        // DBG_LOG_PRINT(("%s: ps_model_name %s\n", __FUNCTION__, ps_model_name));
        return;
    }
    if(s_eCurModelSeries == CUS_MODEL_2022_91_M6 || s_eCurModelSeries == CUS_MODEL_2022_91_V6
     ||s_eCurModelSeries == CUS_MODEL_2022_95S_M9 || s_eCurModelSeries == CUS_MODEL_2022_95S_P
     ||s_eCurModelSeries == CUS_MODEL_2022_95L_V6)
    {
        DBG_LOG_PRINT(("%s %d s_eCurModelSeries = %d with 7921 dongle\n",__FUNCTION__,__LINE__,s_eCurModelSeries));
        FILE * fl = popen("iwpriv wlan0  driver  \"get_mcr 0x70010200 \"", "r");
        if (fl == NULL)
        {
            DBG_LOG_PRINT(("L%d iwpriv wlan0  driver  \"get_mcr 0x70010200 \":error\n", __LINE__));
            return 0;
        }
        if (fgets(tmp, 32, fl) == NULL)
        {
            c_strcpy(ps_model_name, "unknow");
        }
        pclose(fl);
        c_strncpy(ps_model_name, tmp + (c_strlen(tmp) - 5), 4);
        if(atoi(ps_model_name)==7961)
        {
            c_strcpy(ps_model_name, "7921");
        }
    }
    else if(s_eCurModelSeries == CUS_MODEL_2021_83_2K_D_HD || s_eCurModelSeries == CUS_MODEL_2021_83_2K_D_FHD)
    {
        DBG_LOG_PRINT(("%s %d s_eCurModelSeries = CUS_MODEL_2021_83_2K_D_HD or CUS_MODEL_2021_83_2K_D_FHD\n",__FUNCTION__,__LINE__));
        c_strcpy(ps_model_name, "7603");
    }
    else
    {
        FILE * fl = popen("iwpriv wlan0  driver  \"get_mcr 0x8000000c \"", "r");
        if (fl == NULL)
        {
            DBG_LOG_PRINT(("L%d iwpriv wlan0  driver  \"get_mcr 0x8000000c \":error\n", __LINE__));
            return 0;
        }
        if (fgets(tmp, 32, fl) == NULL)
        {
            c_strcpy(ps_model_name, "unknow");
        }
        pclose(fl);
        c_strncpy(ps_model_name, tmp + (c_strlen(tmp) - 6), 4);
    }
    c_strncpy(s_wifi_module_name, ps_model_name, ACFG_CUSTOM_WIFI_MODULE_NAME_LEN);
    DBG_LOG_PRINT(("%s: Set s_wifi_module_name to %s\n", __FUNCTION__,s_wifi_module_name));
}

/*-----------------------------------------------------------------------------
 * Name a_cfg_custom_get_panel_name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *     TVR_OK
 *---------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_panel_name(CHAR* pt_name)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    CHAR s_name[35]={0};
    SIZE_T      z_size = sizeof(s_name);


    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_DISP_TYPE_PANEL_NAME;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = s_name;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;


     /* get from driver */
    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        &z_size_drv
                        );
    if(i4_ret != RMR_OK)
    {
        c_sprintf(pt_name, "Get Panel Name Fail");
        return i4_ret;
    }

    c_strcpy(pt_name, s_name);

    return i4_ret;
}

/* for record 1st time chose HDMI-x/COMP */
INT32 a_cfg_cust_get_ipts_select_state(UINT8* ipts_sel_st)
{
    SIZE_T      z_size = sizeof(UINT8);
    return acfg_get(IDX_CUSTOM_IPTS_SELECT_TIME, ipts_sel_st, &z_size);
}
INT32 a_cfg_cust_set_ipts_select_state(UINT8 ipts_sel_st)
{
    return acfg_set(IDX_CUSTOM_IPTS_SELECT_TIME, &ipts_sel_st, 1);
}

/* channel scan progress set*/
extern INT32 a_cfg_cust_set_ch_scan_progress(UINT8  ui1_value)
{
    return acfg_set(IDX_CUSTOM_CH_SCAN_PROGRESS, &ui1_value, 1);
}

/* channel scan progress get*/
extern INT32 a_cfg_cust_get_ch_scan_progress(UINT8* pui1_value)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUSTOM_CH_SCAN_PROGRESS, pui1_value, &z_size);
}


/* wzd system upgrade status set*/
extern INT32 a_cfg_cust_set_wzd_sys_upgrade_status(UINT8  ui1_value)
{
    return acfg_set(IDX_CUST_WZD_SYS_UPGRADE_STATUS, &ui1_value, 1);
}

/* wzd system upgrade status get*/
extern INT32 a_cfg_cust_get_wzd_sys_upgrade_status(UINT8* pui1_value)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUST_WZD_SYS_UPGRADE_STATUS, pui1_value, &z_size);
}

extern INT32 a_cfg_custom_set_cast_name(CHAR *ps_tv_name)
{
    UINT8   pt_values[MAX_CAST_NAME_LEN] = {0};
    SIZE_T  z_size = MAX_CAST_NAME_LEN;
    UINT32  ui4_idx = 0;
    UINT32  ui4_len = 0;

    if(NULL == ps_tv_name)
    {
        return APP_CFGR_INV_ARG;
    }

    ui4_len = c_strlen(ps_tv_name);

    if (ui4_len >= MAX_CAST_NAME_LEN)
    {
        return APP_CFGR_INV_ARG;
    }

    for (ui4_idx = 0;ui4_idx <= ui4_len; ui4_idx ++ )
    {
        pt_values[ui4_idx] = ps_tv_name[ui4_idx];
    }

    acfg_set(IDX_CUST_CAST_NAME,(VOID*)pt_values,z_size);

    return APP_CFGR_OK;
}

extern INT32 a_cfg_custom_get_cast_name(CHAR *ps_tv_name,
                                              UINT32* pui4_len)
{
    UINT32  ui4_idx = 0;
    UINT8   pt_values[MAX_CAST_NAME_LEN] = {0};
    SIZE_T  z_size = MAX_CAST_NAME_LEN;

    UINT32  ui4_len = 0;

    if((NULL == ps_tv_name)
        || (NULL == pui4_len))
    {
        return APP_CFGR_INV_ARG;
    }

    acfg_get(IDX_CUST_CAST_NAME,(VOID*)pt_values,&z_size);

    if (*pui4_len >= z_size)
    {
        ui4_len = z_size;
    }
    else
    {
        ui4_len = *pui4_len;
    }

    for (ui4_idx = 0;ui4_idx < ui4_len; ui4_idx ++ )
    {
        ps_tv_name[ui4_idx] = pt_values[ui4_idx];
    }

    ps_tv_name[ui4_len - 1] = '\0';

    *pui4_len = ui4_len;

    return APP_CFGR_OK;
}

/* force reboot up flag set*/
extern INT32 a_cfg_cust_set_force_reboot_up_flag(UINT8  ui1_value)
{
    DBG_INFO(("\n[ACFG_TEST] a_cfg_cust_set_force_reboot_up_flag ui1_value[%d]\n",ui1_value));
    return acfg_set(IDX_CUSTOM_FORCE_REBOOT_UP, &ui1_value, 1);
}

/* force reboot up flag get*/
extern INT32 a_cfg_cust_get_force_reboot_up_flag(UINT8* pui1_value)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUSTOM_FORCE_REBOOT_UP, pui1_value, &z_size);
}

/* Zoom mode set*/
extern INT32 a_cfg_cust_set_zoom_mode(UINT8  ui1_value)
{
    DBG_INFO(("\n[ACFG_TEST] a_cfg_cust_set_zoom_mode ui1_value[%d]\n",ui1_value));
    return acfg_set(IDX_CUST_ZOOM_MODE, &ui1_value, 1);
}

/* Zoom mode get*/
extern INT32 a_cfg_cust_get_zoom_mode(UINT8* pui1_value)
{
    //SIZE_T   z_size;

    //return acfg_get(IDX_CUST_ZOOM_MODE, pui1_value, &z_size);
    *pui1_value = 0;
    return 0;
}

/* Zoom mode get. New api instead old api which used to old zoom feature.*/
extern INT32 a_cfg_cust_get_zoom_status(UINT8* pui1_value)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUST_ZOOM_MODE, pui1_value, &z_size);
}
/* automatic get */
extern INT32 a_cfg_cust_get_automatic_time(UINT8* pui1_value)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUSTOM_AUTOMATIC_TIME, pui1_value, &z_size);
}
/* automatic set*/
extern INT32 a_cfg_cust_set_automatic_time(UINT8  ui1_value)
{
    return acfg_set(IDX_CUSTOM_AUTOMATIC_TIME, &ui1_value, 1);
}

/* surround mode set*/
extern INT32 a_cfg_cust_set_surround_mode(UINT8  ui1_value)
{
    return acfg_set(IDX_CUST_SURROUND_MODE, &ui1_value, 1);
}

/* surround mode get */
extern INT32 a_cfg_cust_get_surround_mode(UINT8* pui1_value)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUST_SURROUND_MODE, pui1_value, &z_size);
}

#ifdef ACFG_SYNC_POST_INIT_SUPPORT
INT32 acfg_custom_sync_post_init(VOID)
{
    //set zoom mode to mw/widget.
    UINT8   ui1_zoom_mode;
    SIZE_T  size;
    INT32   i4_ret;

    i4_ret = acfg_eep_get(IDX_CUST_ZOOM_MODE, &ui1_zoom_mode, &size);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("{%s %d}get IDX_CUST_ZOOM_MODE fail, i4_ret=%d.\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    c_wgl_enable_zoom((ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON) ? TRUE : FALSE);

    return APP_CFGR_OK;
}
#endif

/* vol control dispaly flag set*/
extern INT32 a_cfg_cust_set_vol_control_dis_flag(UINT8  ui1_value)
{
    return acfg_set(IDX_CUSTOM_VOL_CONTROL_DISPLAY, &ui1_value, 1);
}

/* vol control dispaly flag get*/
extern INT32 a_cfg_cust_get_vol_control_dis_flag(UINT8* pui1_value)
{
    SIZE_T   z_size;

    return acfg_get(IDX_CUSTOM_VOL_CONTROL_DISPLAY, pui1_value, &z_size);
}

/* Full Chroma 4:4:4 */
extern INT32 a_cfg_cust_set_full_color_444(UINT8  ui1_value)
{
    return acfg_set(IDX_CUSTOM_FULL_COLOR_444, &ui1_value, 1);
}

extern INT32 a_cfg_cust_get_full_color_444(UINT8* pui1_value)
{
    SIZE_T t_size;

    return acfg_get(IDX_CUSTOM_FULL_COLOR_444, pui1_value, &t_size);
}

#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
extern INT32 a_cfg_cust_set_full_color_444_ForCurHDMI(UINT8 ui1_value)
{
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} ui1_value:%d\n", __FUNCTION__, __LINE__, ui1_value)); );

    ISL_REC_T  t_isl_rec = {0};

    INT32 i32Ret = acfg_cust_get_crnt_isl(&t_isl_rec);
    if( i32Ret != APP_CFGR_OK )
    {
        DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Error: acfg_cust_get_crnt_isl() failed => %d\n", __FUNCTION__, __LINE__, i32Ret));
        return APP_CFGR_INTERNAL_ERR;
    }

    // Only HDMI support ...
    if( (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI)
      &&(t_isl_rec.t_avc_info.e_video_type != DEV_AVC_DVI)
      )
    {
        return APP_CFGR_INTERNAL_ERR;
    }

    // Get HDMI index
    UINT16 ui2_hdmi_idx = t_isl_rec.ui1_internal_id;
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} ui2_hdmi_idx: %d\n", __FUNCTION__, __LINE__, ui2_hdmi_idx)); );
    if( ui2_hdmi_idx >= 4 )
    {
        DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Error: ui2_hdmi_idx(%d) >= 4\n", __FUNCTION__, __LINE__, ui2_hdmi_idx));
        return APP_CFGR_INTERNAL_ERR;
    }


    UINT8 ui1_chroma_value = 0;
    i32Ret = a_cfg_cust_get_full_color_444(&ui1_chroma_value);
    if( i32Ret != 0 )
    {
        DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Error: a_cfg_cust_get_full_color_444() failed => %d\n", __FUNCTION__, __LINE__, i32Ret));
        return APP_CFGR_INTERNAL_ERR;
    }

    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} ui1_chroma_value: 0x%X\n", __FUNCTION__, __LINE__, ui1_chroma_value)); );

    if( ui1_value )
    {
        ui1_chroma_value |= (UINT8)1 << ui2_hdmi_idx;
    }
    else
    {
        ui1_chroma_value &= ~((UINT8)1 << ui2_hdmi_idx);
    }

    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} => ui1_chroma_value: 0x%X\n", __FUNCTION__, __LINE__, ui1_chroma_value)); );

    i32Ret = a_cfg_cust_set_full_color_444(ui1_chroma_value);
    if( i32Ret != 0 )
    {
        DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Error: a_cfg_cust_set_full_color_444() failed => %d\n", __FUNCTION__, __LINE__, i32Ret));
        return APP_CFGR_INTERNAL_ERR;
    }

    return APP_CFGR_OK;
}

extern INT32 a_cfg_cust_get_full_color_444_ForCurHDMI(UINT8* pui1_value)
{
    //ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} \n", __FUNCTION__, __LINE__)); );

    ISL_REC_T  t_isl_rec = {0};

    INT32 i32Ret = acfg_cust_get_crnt_isl(&t_isl_rec);
    if( i32Ret != APP_CFGR_OK )
    {
        DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Error: acfg_cust_get_crnt_isl() failed => %d\n", __FUNCTION__, __LINE__, i32Ret));
        return APP_CFGR_INTERNAL_ERR;
    }

    // Only HDMI support ...
    if( (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI)
      &&(t_isl_rec.t_avc_info.e_video_type != DEV_AVC_DVI)
      )
    {
        return APP_CFGR_INTERNAL_ERR;
    }

    // Get HDMI index
    UINT16 ui2_hdmi_idx = t_isl_rec.ui1_internal_id;
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} ui2_hdmi_idx: %d\n", __FUNCTION__, __LINE__, ui2_hdmi_idx)); );
    if( ui2_hdmi_idx >= 4 )
    {
        DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Error: ui2_hdmi_idx(%d) >= 4\n", __FUNCTION__, __LINE__, ui2_hdmi_idx));
        return APP_CFGR_INTERNAL_ERR;
    }


    UINT8 ui1_chroma_value = 0;
    i32Ret = a_cfg_cust_get_full_color_444(&ui1_chroma_value);
    if( i32Ret != 0 )
    {
        DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} Error: a_cfg_cust_get_full_color_444() failed => %d\n", __FUNCTION__, __LINE__, i32Ret));
        return APP_CFGR_INTERNAL_ERR;
    }

    *pui1_value = (ui1_chroma_value >> ui2_hdmi_idx) & 1;

    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[ACFG][FullColor444]{%s:%d} ui1_chroma_value: 0x%X ==> u8Result:%d\n", __FUNCTION__, __LINE__, ui1_chroma_value, *pui1_value)); );

    return APP_CFGR_OK;
}
#endif


/* hide form input list*/
extern INT32 a_cfg_cust_set_hide_from_input(UINT8  ui1_value)
{
    INT32  i4_ret;

    i4_ret = acfg_set(IDX_CUSTOM_HIDE_FROM_INPUT_LIST, &ui1_value, 1);
    return i4_ret;
}

extern INT32 a_cfg_cust_get_hide_from_input(UINT8* pui1_value)
{
    SIZE_T t_size;
    INT32  i4_ret;

    i4_ret = acfg_get(IDX_CUSTOM_HIDE_FROM_INPUT_LIST, pui1_value, &t_size);
    return i4_ret;
}

/* full uhd color*/
extern INT32 a_cfg_cust_set_full_uhd_color(UINT8 ui1_value)
{
    ACFG_DEBUG_HDMI_EDID( DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID] {%s,%d} ui1_value:0x%X\n",
            __FUNCTION__, __LINE__, ui1_value)); );

    return acfg_set(IDX_CUSTOM_FULL_UHD_COLOR, &ui1_value, 1);
}

extern INT32 a_cfg_cust_set_full_uhd_color_by_hdmi_idx(UINT8 u8_hdmi_idx, UINT8 ui1_value)
{
    ACFG_DEBUG_HDMI_EDID( DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID] {%s,%d} u8_hdmi_idx:%d, ui1_value:0x%X\n",
            __FUNCTION__, __LINE__, u8_hdmi_idx, ui1_value)); );


    UINT8 ui1_color_value = 0;

    SIZE_T t_size;
    INT32 i32_rtn = acfg_get(IDX_CUSTOM_FULL_UHD_COLOR, &ui1_color_value, &t_size);

    UINT8 ui1_color_value_new = ui1_color_value;

    ui1_color_value_new &= ~((UINT8)3 << (u8_hdmi_idx * 2));
    ui1_color_value_new |= (UINT8)ui1_value << (u8_hdmi_idx * 2);

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} u8_hdmi_idx:%d: full_uhd_color:0x%X => ui1_color_value_new:0x%X\n",
            __FUNCTION__, __LINE__, u8_hdmi_idx, ui1_color_value, ui1_color_value_new ));
    );


    return acfg_set(IDX_CUSTOM_FULL_UHD_COLOR, &ui1_color_value_new, 1);
}

extern INT32 a_cfg_cust_get_full_uhd_color(UINT8* pui1_value)
{
    SIZE_T t_size;

    INT32 i32_rtn = acfg_get(IDX_CUSTOM_FULL_UHD_COLOR, pui1_value, &t_size);
    if( i32_rtn != APP_CFGR_OK )
    {
        DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} Error: acfg_get() failed!! i32_rtn:%d\n",
            __FUNCTION__, __LINE__, i32_rtn ));

        *pui1_value = 0;
        return i32_rtn;
    }

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} => full_uhd_color val:0x%X \n",
            __FUNCTION__, __LINE__, *pui1_value  ));
    );

    return APP_CFGR_OK;
}

extern INT32 a_cfg_cust_get_full_uhd_color_by_hdmi_idx(UINT8 u8_hdmi_idx, UINT8* pui1_value)
{
    UINT8 ui1_color_value = 0;

    //1, set ui1_color_value to acfg
    //INT32 i32_rtn = a_cfg_cust_get_full_uhd_color(&ui1_color_value);
    SIZE_T t_size;

    INT32 i32_rtn = acfg_get(IDX_CUSTOM_FULL_UHD_COLOR, &ui1_color_value, &t_size);
    if( i32_rtn != APP_CFGR_OK )
    {
        DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} u8_hdmi_idx:%d : acfg_get() failed!! i32_rtn:%d\n",
            __FUNCTION__, __LINE__, u8_hdmi_idx, i32_rtn ));
        *pui1_value = 0;
        return i32_rtn;
    }

    *pui1_value = ( ui1_color_value >> (u8_hdmi_idx * 2) ) & 3;

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} u8_hdmi_idx:%d => full_uhd_color val:0x%X => Val:%d\n",
            __FUNCTION__, __LINE__, u8_hdmi_idx, ui1_color_value, *pui1_value ));
    );

    return APP_CFGR_OK;
}

/* for settings just in menu/Input settings/device*/
extern INT32 a_cfg_cust_set_hide_from_input_manually(UINT8  ui1_value)
{
    INT32  i4_ret;

    i4_ret = acfg_set(IDX_CUSTOM_HIDE_FROM_INPUT_LIST_MANUAL, &ui1_value, 1);
    return i4_ret;
}

extern INT32 a_cfg_cust_get_hide_from_input_manually(UINT8* pui1_value)
{
    SIZE_T t_size;
    INT32  i4_ret;

    i4_ret = acfg_get(IDX_CUSTOM_HIDE_FROM_INPUT_LIST_MANUAL, pui1_value, &t_size);
    return i4_ret;
}

/* oobe ir mode set*/
extern INT32 a_cfg_cust_set_oobe_ir_mode(UINT8  ui1_value)
{
    DBG_INFO(("\n[ACFG_TEST] a_cfg_cust_set_oobe_ir_mode ui1_value: %d\n",ui1_value));
    return acfg_set(IDX_CUSTOM_OOBE_IR_MODE, &ui1_value, 1);
}

/* oobr ir mode get*/
extern INT32 a_cfg_cust_get_oobe_ir_mode(UINT8* pui1_value)
{
    SIZE_T   z_size;
    return acfg_get(IDX_CUSTOM_OOBE_IR_MODE, pui1_value, &z_size);
}

/* retail mode set*/
extern INT32 a_cfg_cust_set_retail_mode_first_time_setting(UINT8  ui1_value)
{
    DBG_INFO(("\n[ACFG] %s ui1_value: %d\n",__FUNCTION__,ui1_value));
    return acfg_set(IDX_CUSTOM_RETAIL_MODE_FIRST_TIME_SETTING, &ui1_value, 1);
}

/* retail mode get*/
extern INT32 a_cfg_cust_get_retail_mode_first_time_setting(UINT8* pui1_value)
{
    SIZE_T   z_size;
    return acfg_get(IDX_CUSTOM_RETAIL_MODE_FIRST_TIME_SETTING, pui1_value, &z_size);
}
/* retail mode source info*/
extern INT32 a_cfg_cust_set_retail_mode_source_info(UINT8  ui1_value)
{
    return acfg_set(IDX_CUSTOM_RETAIL_MODE_SOURCE_INFO_STORE, &ui1_value, 1);
}

/* retail mode get*/
extern INT32 a_cfg_cust_get_retail_mode_source_info(UINT8* pui1_value)
{
    SIZE_T   z_size;
    return acfg_get(IDX_CUSTOM_RETAIL_MODE_SOURCE_INFO_STORE, pui1_value, &z_size);
}

extern INT32 a_cfg_set_vtrl_name (UINT8 ui1_source_id, VOID* pt_vtrl_name,SIZE_T z_size)
{
    INT32 i4_ret = 0;
    UINT32 ui4_written = 0;

    i4_ret = a_cfg_eep_raw_write(IDX_IPTS_VTRL_NAME_1_ADDR + ui1_source_id*24+ui1_source_id, pt_vtrl_name, z_size, &ui4_written);

    return i4_ret;
}
extern INT32 a_cfg_get_vtrl_name (UINT8 ui1_source_id, VOID* pt_vtrl_name,SIZE_T z_size)
{
    INT32 i4_ret = 0;
    UINT32 ui4_written = 0;

    i4_ret = a_cfg_eep_raw_read(IDX_IPTS_VTRL_NAME_1_ADDR + ui1_source_id*24+ui1_source_id, pt_vtrl_name, z_size, &ui4_written);

    return i4_ret;
}


extern INT32 a_cfg_set_name_display (UINT8  ui1_lang_id,UINT8 ui1_source_id, VOID* pt_vtrl_name,SIZE_T z_size)
{
    INT32 i4_ret = 0;
    UINT32 ui4_written = 0;
    UINT32 ui4_offset  = 0;
    if(ui1_lang_id  == 1)
    {
        ui4_offset = IDX_IPTS_VTRL_DSP_NAME_ENG_1_ADDR + ui1_source_id*24 + ui1_source_id;
    }
    else if(ui1_lang_id  == 2)
    {
        ui4_offset = IDX_IPTS_VTRL_DSP_NAME_FRE_1_ADDR + ui1_source_id*24 + ui1_source_id;
    }
    else if(ui1_lang_id  == 3)
    {
        ui4_offset = IDX_IPTS_VTRL_DSP_NAME_SPA_1_ADDR + ui1_source_id*24 + ui1_source_id;
    }

    i4_ret = a_cfg_eep_raw_write(ui4_offset, pt_vtrl_name, z_size, &ui4_written);

    return i4_ret;
}
extern INT32 a_cfg_get_name_display (UINT8  ui1_lang_id, UINT8 ui1_source_id,VOID* pt_vtrl_name,SIZE_T z_size)
{
    INT32 i4_ret = 0;
    UINT32 ui4_written = 0;
    UINT32 ui4_offset  = 0;
    if(ui1_lang_id  == 1)
    {
        ui4_offset = IDX_IPTS_VTRL_DSP_NAME_ENG_1_ADDR + ui1_source_id*24 + ui1_source_id;
    }
    else if(ui1_lang_id  == 2)
    {
        ui4_offset = IDX_IPTS_VTRL_DSP_NAME_FRE_1_ADDR + ui1_source_id*24 + ui1_source_id;
    }
    else if(ui1_lang_id  == 3)
    {
        ui4_offset = IDX_IPTS_VTRL_DSP_NAME_SPA_1_ADDR + ui1_source_id*24 + ui1_source_id;
    }

    i4_ret = a_cfg_eep_raw_read(ui4_offset, pt_vtrl_name, z_size, &ui4_written);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name:          a_cfg_set_bgm_wake_disable
 * Description:  To disable the bgm wakeup for ODM energy test.
 *---------------------------------------------------------------------------*/
VOID a_cfg_set_bgm_wake_disable(BOOL b_disable_bgm)
{
    b_bgm_wake_up_disable = b_disable_bgm;
}

BOOL a_cfg_get_bgm_wake_up(VOID)
{
    return b_bgm_wake_up_disable;
}

/* color space set */
INT32 a_cfg_cust_set_color_space_value(UINT8  ui1_value)
{
    INT32 i4_hdmi_idx = 0;
    INT32 i4_ret = APP_CFGR_OK;
    UINT8 ui1_acfg_value = 0;
    UINT8 ui1_max_value = 2;
    if (ui1_value > ui1_max_value)
    {
        return APP_CFGR_INV_ARG;
    }
    i4_hdmi_idx = a_nav_ipts_get_hdmi_comp_idx();
    if (i4_hdmi_idx < 0)
    {
        return APP_CFGR_INTERNAL_ERR;
    }
    i4_ret = a_cfg_cust_get_color_space_value(&ui1_acfg_value);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    DBG_LOG_PRINT(("<COLOR SPACE RANGE> file: %s line: %d  %s ui1_old_value(%d) i4_hdmi_idx: %d ui1_value:%d\n",
        __FILE__, __LINE__, __FUNCTION__, ui1_acfg_value, i4_hdmi_idx, ui1_value));

    ui1_acfg_value = (i4_hdmi_idx << ui1_max_value) + ui1_value;

    return acfg_set(IDX_CUSTOM_COLOR_SPACE, &ui1_acfg_value, 1);
}

/* color space get */
INT32 a_cfg_cust_get_color_space_value(UINT8* ui1_value)
{
    SIZE_T   z_size;
    INT32 i4_ret = APP_CFGR_OK;
    INT32 i4_hdmi_idx = 0;
    UINT8 ui1_acfg_value = 0;
    UINT8 ui1_max_value = 2;
    if (ui1_value == NULL)
    {
        DBG_ERROR(("[ACFG][%s]:[%d]This is wrong address\n",__FILE__,__LINE__));
        return FALSE;
    }
    i4_hdmi_idx = a_nav_ipts_get_hdmi_comp_idx();
    if (i4_hdmi_idx < 0)
    {
        *ui1_value = 0;
        return APP_CFGR_INTERNAL_ERR;
    }
    i4_ret = acfg_get(IDX_CUSTOM_COLOR_SPACE, &ui1_acfg_value, &z_size);
    MENU_CHK_FAIL(i4_ret);
    DBG_LOG_PRINT(("<COLOR SPACE RANGE> file: %s line: %d  %s ui1_acfg_value(%d) i4_hdmi_idx = %d\n", __FILE__, __LINE__, __FUNCTION__, ui1_acfg_value, i4_hdmi_idx));
    *ui1_value = (UINT8)(ui1_acfg_value - (i4_hdmi_idx << ui1_max_value));
    DBG_LOG_PRINT(("<COLOR SPACE RANGE> file: %s line: %d  %s ui1_value = %d\n", __FILE__, __LINE__, __FUNCTION__, *ui1_value));
    return i4_ret;
}


INT32 a_cfg_cust_set_oled_panel_refresh_value(UINT8  ui1_value)
{
    acfg_set(IDX_CUSTOM_OLED_PANEL_REFRESH, &ui1_value, 1);
    switch(ui1_value)
    {
        case SCREEN_REFRESH_START_CANCEL:
             a_cfg_cust_drv_set_oled_jb(0);
             a_cfg_cust_set_oled_jb(0);
             a_cfg_cust_set_oled_off_rs(0);
             break;
        case SCREEN_REFRESH_START_AT_NOW:
            a_cfg_cust_set_oled_jb(1);
            a_cfg_cust_set_oled_off_rs(1);
            a_amb_power_on(FALSE);
            break;
        case SCREEN_REFRESH_START_AT_POWER_OFF:
            a_cfg_cust_set_oled_jb(1);
            a_cfg_cust_set_oled_off_rs(1);
            break;
    }

    return 0;
}


INT32 a_cfg_cust_get_oled_panel_refresh_value(UINT8* ui1_value)
{
    SIZE_T   z_size;
    if (ui1_value == NULL)
    {
        DBG_ERROR(("[ACFG][%s]:[%d]This is wrong address\n",__FILE__,__LINE__));
        return FALSE;
    }
    return acfg_get(IDX_CUSTOM_OLED_PANEL_REFRESH, ui1_value, &z_size);
}

INT32 a_cfg_cust_set_oled_pixel_shift_value(UINT8  ui1_value)
{
    return acfg_set(IDX_CUSTOM_OLED_PIXEL_SHIFT, &ui1_value, 1);
}


INT32 a_cfg_cust_get_oled_pixel_shift_value(UINT8* ui1_value)
{
    SIZE_T   z_size;
    if (ui1_value == NULL)
    {
        DBG_ERROR(("[ACFG][%s]:[%d]This is wrong address\n",__FILE__,__LINE__));
        return FALSE;
    }
    return acfg_get(IDX_CUSTOM_OLED_PIXEL_SHIFT, ui1_value, &z_size);
}


/*demo mode set */
INT32 a_cfg_cust_set_demo_mode_value(UINT8  ui1_value)
{
    return acfg_set(IDX_DEMO_MODE, &ui1_value, 1);
}

/* demo mode get */
INT32 a_cfg_cust_get_demo_mode_value(UINT8* ui1_value)
{
    SIZE_T   z_size;
    if (ui1_value == NULL)
    {
        DBG_ERROR(("[ACFG][%s]:[%d]This is wrong address\n",__FILE__,__LINE__));
        return FALSE;
    }
    return acfg_get(IDX_DEMO_MODE, ui1_value, &z_size);
}

INT32 a_cfg_cust_get_hdmi_dectect_range(UINT8* ui1_range)
{
    INT32       i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size = sizeof(UINT8);
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT8 ui1_hdmi_range;
    c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI_DETECT_RANGE;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID*)&ui1_hdmi_range;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*set value to driver*/
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    ACFG_LOG_ON_FAIL(i4_ret);

    *ui1_range = ui1_hdmi_range;
    return i4_ret;
}

BOOL a_cfg_cust_get_support_clear_aciton(VOID)
{
    //Add for DTV03322701
    if((s_eCurModelSeries == CUS_MODEL_2022_91_M6)  ||
       (s_eCurModelSeries == CUS_MODEL_2022_95S_M9) ||
       (s_eCurModelSeries == CUS_MODEL_2022_95S_P))
    {
        return TRUE;
    }

    BOOL is_support_clear_action = FALSE;

    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(is_support_clear_action);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;

    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_CLEAR_ACTION;

    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&is_support_clear_action;

    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    ACFG_LOG_ON_FAIL(c_rm_get_comp(DRVT_CUST_DRV,
                                   DRV_CUST_COMP_ID,
                                   FALSE,
                                   ANY_PORT_NUM,
                                   0,
                                   &t_op_info,
                                   &z_size_drv));

    DBG_INFO(("acfg_custom.c L%d DRV_CUSTOM_CUST_SPEC_TYPE_GET_CLEAR_ACTION :%d \n", __LINE__, is_support_clear_action));

    return is_support_clear_action;

}

UINT8 acfg_check_play_content(VOID)
{
    if( a_acfg_cust_get_dynamic_range() == ACFG_CUST_CONTENT_HDR ||
        a_acfg_cust_get_dynamic_range() == ACFG_CUST_CONTENT_HLG)
    {
        return ACFG_CUST_RGB_CONTENT_HDR_HLG;
    }
    else if(a_acfg_cust_get_dynamic_range() == ACFG_CUST_CONTENT_DV)
    {
        return ACFG_CUST_RGB_CONTENT_DOLBY_VERSION;
    }
    else
    {
        return ACFG_CUST_RGB_CONTENT_SDR;
    }
}

INT32 VIZIO_CTRL_ENABLE_SPI_HW_MODE(UINT16 ui2_idx)
{
    INT32                           i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T       t_op_info;
    SIZE_T                          z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT32                          ui4_drv_type = 0;

    if (ui2_idx == TRUE)
    {
        ui4_drv_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_ENABLE_SPI_HW_MODE;
    }
    else
    {
        ui4_drv_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_DISABLE_SPI_HW_MODE;
    }

    SIZE_T z_size = sizeof(ui2_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = ui4_drv_type;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* get from driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

UINT16 a_cfg_get_local_dimming_mlm_string(VOID)
{
#if 0
    UINT16  ui2_ret = MLM_SETTINGS_KEY_LOCAL_DEMMING_E_SERIES;
    CHAR    s_model_name[16+1] = {0};

    a_cfg_custom_get_model_name(s_model_name);
    if (s_model_name[0] == 'M')  //M series model
    {
        ui2_ret = MLM_SETTINGS_KEY_LOCAL_DEMMING_M_SERIES;
        return ui2_ret;
    }
    else if (s_model_name[0] == 'P') //P series model
    {
        ui2_ret = MLM_SETTINGS_KEY_LOCAL_DEMMING_P_SERIES;
        return ui2_ret;
    }
    else                             //E series model
    {
        ui2_ret = MLM_SETTINGS_KEY_LOCAL_DEMMING_E_SERIES;
        return ui2_ret;
    }
#else
    return MLM_SETTINGS_KEY_LOCAL_DEMMING_ACTIVE_FULL_ARRAY;
#endif
}

BOOL a_cfg_cust_get_support_local_dimming(VOID)
{
    BOOL is_support_local_dimming = FALSE;

    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(is_support_local_dimming);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;

    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_MODEL_SUPPORT_LOCAL_DIMMING;

    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&is_support_local_dimming;

    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    ACFG_LOG_ON_FAIL(c_rm_get_comp(DRVT_CUST_DRV,
                                   DRV_CUST_COMP_ID,
                                   FALSE,
                                   ANY_PORT_NUM,
                                   0,
                                   &t_op_info,
                                   &z_size_drv));

    ACFG_DBG_INFO(" Get is_support_local_dimming = %d \r\n",is_support_local_dimming);

    return is_support_local_dimming;

}

/*demo mode set */
INT32 a_cfg_cust_set_local_dimming_value(UINT8  ui1_value)
{
    return acfg_set(IDX_LOCAL_DIMMING, &ui1_value, 1);
}

/* demo mode get */
INT32 a_cfg_cust_get_local_dimming_value(UINT8* ui1_value)
{
    SIZE_T   z_size;
    if (ui1_value == NULL)
    {
        DBG_ERROR(("[ACFG][%s]:[%d]This is wrong address\n",__FILE__,__LINE__));
        return FALSE;
    }
    return acfg_get(IDX_LOCAL_DIMMING, ui1_value, &z_size);
}
extern INT32 MTDRVCUST_dcustom_cust_spec_get (DRV_CUSTOM_CUST_SPEC_TYPE_T e_cust_spec_type,VOID*  pv_get_info,SIZE_T* pz_size);

UINT8 a_cfg_gethdmiports(VOID)
{
    UINT8 ui1_num = 0;
    SIZE_T count = sizeof(ui1_num);

    if (MTAL_Init() != 0)//MTR_OK
    {
        return 0xFF;
    }

    MTDRVCUST_dcustom_cust_spec_get(
                        DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI_PORT,
                        (VOID *)&ui1_num,
                        &count);
    DBG_INFO(("%s_%d ui1_num:%d \n",__FUNCTION__,__LINE__,ui1_num));
    return ui1_num;
}

INT32 ui4_minutes = 0;
BOOL b_power_off_by_python = FALSE;
VOID acfg_custom_set_wakeup_time(INT32 time)
{
    ui4_minutes = time;
}
VOID acfg_custom_power_off_by_python()
{
    b_power_off_by_python = TRUE;
}

VOID _acfg_custom_set_wakeup_time(VOID)
{
    TIME_T   t_current_utc_time  = 0;
    TIME_T  t_timer_wakeup_time = NULL_TIME;
    BOOL    b_wakeup_cap        = FALSE;
    BOOL    b_wakeup            = FALSE;
    INT32   i4_ret              = -1;
    UINT32  ui4_wakeup_cap      = 0;
    UINT32  ui4_wakeup_ctrl_cap = 0;
    UINT32  ui4_setup           = 0;
    UINT32  ui4_misc_ctrl       = 0;
    UINT16  ui2_reason          = 0;

    DBG_INFO(("[%s %d] Enter\r\n", __FUNCTION__, __LINE__));

    if (!b_power_off_by_python)
    {
        DBG_ERROR(("[%s %d] wasn't power off by python !!!!!\r\n", __FUNCTION__,__LINE__));
        return ;
    }

    /* Get the wakeup capability */
    i4_ret = c_pcl_get_wakeup_capability(&ui4_wakeup_cap, &ui4_wakeup_ctrl_cap);
    if(i4_ret < 0)
    {
        /* wakeup capability get failed, assume no wakeup capability */
        ui4_wakeup_cap = 0;
    }

    /* Wakeup from RTC ? */
    if(ui4_wakeup_cap & PCL_WAKE_UP_CAP_RTC)
    {
        b_wakeup_cap = TRUE;
    }
    else
    {
        b_wakeup_cap = FALSE;
    }

    /* Get current UTC time */
    t_current_utc_time = c_dt_get_utc(NULL, NULL);

    if (b_wakeup_cap)
    {

        if (FALSE == a_am_is_power_on() &&
            FALSE == a_bgm_is_running())
        {
            /* Get current misc ctrl */
            c_pcl_get_misc_ctrl(&ui4_misc_ctrl);

            ui4_misc_ctrl |= PCL_MISC_CTRL_QUIET_BOOT;

            c_pcl_set_misc_ctrl(ui4_misc_ctrl);

            a_cfg_get_rtc_wakeup_type(&ui2_reason);

            ui2_reason &=  ~APP_CFG_RTC_WAKEUP_TYPE_CI_EMM_ONLY;
#ifdef SYS_C4TV_SUPPORT
            ui2_reason &=  ~APP_CFG_RTC_WAKEUP_TYPE_CAST_ONLY;
#endif
            ui2_reason |= APP_CFG_RTC_WAKEUP_TYPE_NONE;
            a_cfg_set_rtc_wakeup_type(ui2_reason);

            t_timer_wakeup_time = t_current_utc_time + 60 * ui4_minutes;
            b_wakeup = TRUE;
        }

        if(!a_cfg_get_bgm_wake_up())
        {
            DBG_INFO(("Will disable bgm wake up \n"));
            b_wakeup = FALSE;
        }
        if (TRUE == b_wakeup)
        {
            DBG_INFO(("<ACFG>Set Wakeup_Time to %llu\n", t_timer_wakeup_time));

            /*get current setting*/
            i4_ret = c_pcl_get_wakeup_setup(&ui4_setup);
            ACFG_LOG_ON_FAIL(i4_ret);

            /*add RTC wakeup*/
            i4_ret = c_pcl_set_wakeup_setup(ui4_setup | PCL_WAKE_UP_CAP_RTC);
            ACFG_LOG_ON_FAIL(i4_ret);
            /*set wakeup time*/
            i4_ret = c_pcl_set_wakeup_time(t_timer_wakeup_time);

            if(i4_ret < 0)
            {
                DBG_INFO(("[ACFG] c_pcl_set_wakeup_time fail\n"));
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        }
        else
        {
            DBG_INFO(("<ACFG>Set Wakeup_Time to NULL\n"));
            /*get current setting*/
            i4_ret = c_pcl_get_wakeup_setup(&ui4_setup);
            ACFG_LOG_ON_FAIL(i4_ret);

            /*add RTC wakeup*/
            i4_ret = c_pcl_set_wakeup_setup(ui4_setup & (~PCL_WAKE_UP_CAP_RTC));
            ACFG_LOG_ON_FAIL(i4_ret);

            /* Set to pcl the wakeup time to NULL */
            i4_ret = c_pcl_set_wakeup_time(NULL_TIME);
            if(i4_ret < 0)
            {
                DBG_INFO(("[ACFG] c_pcl_set_wakeup_time fail\n"));
                ACFG_LOG_ON_FAIL(i4_ret);
            }
        }
    }
    DBG_INFO(("[%s %d] End\r\n", __FUNCTION__, __LINE__));
    b_power_off_by_python = FALSE;
    ui4_minutes = 0;
}

INT32  a_cfg_11_point_gain_default(VOID)
{
    if (b_g_app_cfg_init == FALSE)
    {
        return APP_CFGR_NOT_INIT;
    }

    ACFG_LOG_ON_FAIL(acfg_set_default(IDX_11_POINT_GAIN));
    ACFG_LOG_ON_FAIL(acfg_set_default(IDX_11_POINT_GAIN_RED));
    ACFG_LOG_ON_FAIL(acfg_set_default(IDX_11_POINT_GAIN_GREEN));
    ACFG_LOG_ON_FAIL(acfg_set_default(IDX_11_POINT_GAIN_BLUE));
    return APP_CFGR_OK;
}

INT32 a_cfg_get_dolby_version_info(DRV_CUSTOM_DOLBY_VERSION_TYPE_T* pt_dv_info)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size     = sizeof(DRV_CUSTOM_DOLBY_VERSION_TYPE_T);

    /* set operation type */
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_DOLBY_VER_INFO;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = pt_dv_info;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    return c_rm_get_comp(DRVT_CUST_DRV,
                         DRV_CUST_COMP_ID,
                         FALSE,
                         ANY_PORT_NUM,
                         0,
                         &t_op_info,
                         &z_size_drv);

}

INT32 acfg_get_crnt_dolby_version_ver(INT32        i4_argc,
                                            const CHAR** pps_argv)
{
      DRV_CUSTOM_DOLBY_VERSION_TYPE_T  t_dolby_ver = {0,{0}};

      /* get from driver */
      ACFG_LOG_ON_FAIL(a_cfg_get_dolby_version_info(&t_dolby_ver));
      DBG_INFO(("\r\ndolby version info: idx:%d,ver:%s\r\n",t_dolby_ver.ui1DVIndexByPanel,t_dolby_ver.szDolbyVerInfo));

      return APP_CFGR_OK;
}

INT32 a_cfg_cust_set_limited_ad_tracking(UINT8 ui1_value)
{
    INT32   i4_ret = APP_CFGR_OK;
    if(ui1_value == 1)
    {
        AP_SYSTEM_CALL("touch /tmp/cfg_adtracking_enabled");
    }
    else
    {
        ACFG_LOG_ON_FAIL(remove("/tmp/cfg_adtracking_enabled"));
    }
    i4_ret = acfg_set(IDX_CUSTOM_LIMITED_AD_TRACKING, &ui1_value, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_cust_get_limited_ad_tracking(UINT8 *pui1_value)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_value = 0;

    if (!pui1_value)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_LIMITED_AD_TRACKING, &ui1_value, &z_size);

    *pui1_value = ui1_value;

    return i4_ret;
}


INT32 a_cfg_cust_set_memc(UINT8 ui1_value)
{
    DBG_LOG_PRINT(("[ACFG][MEMC]{%s,%d} Set value= %d\n",__FUNCTION__,__LINE__, ui1_value));

    INT32   i4_ret = APP_CFGR_OK;
    i4_ret = acfg_set(IDX_CUSTOM_MEMC, &ui1_value, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_cust_get_memc(UINT8 *pui1_value)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_value = 0;

    if (!pui1_value)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_MEMC, &ui1_value, &z_size);

    *pui1_value = ui1_value;

    return i4_ret;
}


INT32 a_cfg_cust_set_ota_loop_test(UINT8 ui1_value)
{
    INT32   i4_ret = APP_CFGR_OK;
    i4_ret = acfg_set(IDX_CUSTOM_OTA_LOOP_TEST, &ui1_value, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_cust_get_ota_loop_test(UINT8 *pui1_value)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_value = 0;

    if (!pui1_value)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_OTA_LOOP_TEST, &ui1_value, &z_size);

    *pui1_value = ui1_value;

    return i4_ret;
}

INT32 a_cfg_cust_set_log_level(UINT8 log_level){

    INT32   i4_ret = MI_OK;
    char    str_command[MI_FLASH_ENV_VALUE_LEN_MAX] = {'\0'};
    int     kernel_log_level = 0;
    INT32     cec_log_level = 0;
    DBG_LOG_PRINT(("[%s %d] level = %x\n\r",__FUNCTION__,__LINE__,log_level));

    // Set Uli log
    if(log_level > 1)
    {
         AP_SYSTEM_CALL("rm -f /tmp/uli_log_enable");
    }
    else
    {
         AP_SYSTEM_CALL("touch /tmp/uli_log_enable");
    }

    switch(log_level){
        case LOGLEVEL_OFF: // OFF
            kernel_log_level = 0; break;
        case LOGLEVEL_APP_ONLY: // APP_ONLY
            kernel_log_level = 4; break;
        case LOGLEVEL_KERNEL_ONLY: // KERNEL_ONLY
            kernel_log_level = 7; break;
        case LOGLEVEL_ALL: // ALL (APP and Kernel)
            kernel_log_level = 7; break;
        default:
            break;
    }

    //open cec log
    if(log_level >= LOGLEVEL_APP_ONLY)
    {
        cec_log_level = 7;
    }
    else
    {
        cec_log_level = 0;
    }
    nav_cec_set_dbg_lvl(cec_log_level);
    {
        DRV_CUST_OPERATION_INFO_T t_op_info;
        SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

        c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
        t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_SET_LOG_CONTROL_LEVEL ;
        t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&cec_log_level;
        t_op_info.u.t_cust_spec_set_info.z_size = sizeof(INT32);
        t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

        i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                               FALSE,
                               ANY_PORT_NUM,
                               0,
                               &t_op_info,
                               z_size);
    }

    // 0. update log level in eeprom
    {
        UINT8 ui1_value = 0;
        SIZE_T      z_size = 0;

        i4_ret = acfg_get(IDX_CUSTOM_VLOG_CONTORL, &ui1_value, &z_size);

        if ( ui1_value != log_level) {
            i4_ret = acfg_set(IDX_CUSTOM_VLOG_CONTORL, &log_level, 1);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
        }
    }

    // 1. set middware dbg loglevel
    x_dbg_set_ctrl_stmt((log_level == LOGLEVEL_APP_ONLY || log_level == LOGLEVEL_ALL) ? TRUE : FALSE);

    // 2. set kernel loglevel
    {
        sprintf(str_command, "echo %d > /proc/sys/kernel/printk", (UINT32)kernel_log_level);
        AP_SYSTEM_CALL(str_command);
    }

    // 3. set ubootenv loglevel
    {
        int i4_ret = 0;

        MI_HANDLE                    hFlash         = MI_HANDLE_NULL;
        MI_FLASH_EnvInfo_t*          pstEnvInfo     = NULL;
        MI_FLASH_SetEnvVar_t         stSetEnvParams;

        MI_FLASH_Type_e              eType          = E_MI_FLASH_TYPE_SPI;
        MI_FLASH_QueryHandleParams_t stQueryParams;
        MI_FLASH_OpenParams_t        stOpenParams;
        // 1. Get flash handle
        i4_ret = MI_FLASH_GetAttr(MI_HANDLE_NULL, E_MI_FLASH_ATTR_TYPE_ENV_LOCATION, NULL, (void *)&eType);
        if (i4_ret != MI_OK)
        {
            DBG_ERROR((" get MI flash type failed, i4_ret: %d\n", i4_ret));
            return MI_ERR_FAILED;
        }
        c_memset(&stQueryParams, 0, sizeof(MI_FLASH_QueryHandleParams_t));
        stQueryParams.eType = eType;
        i4_ret = MI_FLASH_GetHandle(&stQueryParams, &hFlash);
        if (i4_ret != MI_OK)
        {
            DBG_ERROR(("get MI flash handle failed, i4_ret: %d\n", i4_ret));

            c_memset(&stOpenParams, 0, sizeof(MI_FLASH_OpenParams_t));
            stOpenParams.eType = eType;
            i4_ret = MI_FLASH_Open(&stOpenParams, &hFlash);
            if (i4_ret != MI_OK)
            {
                DBG_ERROR(("[TVAPI] <%s:%4d> open MI flash handle failed, i4_ret: %d\n", __FILE__, __LINE__, i4_ret));
                return MI_ERR_FAILED;
            }
        }

        // 2. set attri
        c_memset(&stSetEnvParams, 0, sizeof(MI_FLASH_SetEnvVar_t));
        stSetEnvParams.pstCurEnv = pstEnvInfo;
        stSetEnvParams.pszName   = (MI_U8*)"loglevel";

        sprintf(str_command, "%d", (UINT32)kernel_log_level);
        stSetEnvParams.pszValue  = (MI_U8*)str_command;

        pstEnvInfo = (MI_FLASH_EnvInfo_t*)c_mem_alloc(sizeof(MI_FLASH_EnvInfo_t));
        if (pstEnvInfo == NULL)
        {
            DBG_ERROR(("allocate memory failed\n"));
            return MI_ERR_MEMORY_ALLOCATE;
        }
        c_memset(pstEnvInfo, 0, sizeof(MI_FLASH_EnvInfo_t));
        i4_ret = MI_FLASH_LoadEnv(hFlash, pstEnvInfo);
        if (i4_ret != MI_OK)
        {
            DBG_ERROR(("load current env data failed, i4_ret: %d\n", i4_ret));
            i4_ret = MI_ERR_FAILED;
            goto MEM_FREE;
        }

        stSetEnvParams.pstCurEnv = pstEnvInfo;
        i4_ret = MI_FLASH_SetEnvVar(hFlash, &stSetEnvParams);
        if (i4_ret != MI_OK)
        {
            DBG_ERROR((" set new env failed, i4_ret: %d\n",  i4_ret));
            i4_ret = MI_ERR_FAILED;
            goto MEM_FREE;
        }

        i4_ret = MI_FLASH_StoreEnv(hFlash, pstEnvInfo);
        if (i4_ret != MI_OK)
        {
            DBG_ERROR((" store env failed, i4_ret: %d\n", i4_ret));
            i4_ret = MI_ERR_FAILED;
            goto MEM_FREE;
        }

        MEM_FREE:
        if (pstEnvInfo != NULL)
        {
            c_mem_free(pstEnvInfo);
            pstEnvInfo = NULL;
        }
    }
    return MI_OK;
}

INT32 a_cfg_cust_set_vlog_status(UINT8 ui1_vlog_status)
{
    // This API not used any more , please use a_cfg_cust_set_log_level
    return APP_CFGR_NOT_SUPPORT;
}

INT32 a_cfg_cust_get_log_level(UINT8 *pui1_vlog_status)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_value = 0;

    if (!pui1_vlog_status)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_VLOG_CONTORL, &ui1_value, &z_size);

    *pui1_vlog_status = ui1_value;

    return i4_ret;
}

extern INT32 a_cfg_fusion_av_get_min_max(
    UINT16  ui2_id,
    INT16*  pi2_min,
    INT16*  pi2_max)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;

    switch(CFG_GET_GROUP(ui2_id)){
    case APP_CFG_GRPID_PICTURE:
        i4_ret = acfg_fusion_pic_get_min_max(ui2_id, pi2_min, pi2_max);
        break;
    default:
        return APP_CFGR_INV_ARG;
    }

    return i4_ret;
}

extern INT32 a_cfg_fusion_av_get(
    UINT16  ui2_id,
    INT16*  pi2_val)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;

    switch(CFG_GET_GROUP(ui2_id))
    {
    case APP_CFG_GRPID_SOUND:
        i4_ret = acfg_fusion_tv_sound_get(ui2_id, pi2_val);
        break;

    default:
        return APP_CFGR_INV_ARG;
    }
    return i4_ret;
}

extern INT32 a_cfg_fusion_av_set(
    UINT16  ui2_id,
    INT16   i2_val)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;

    switch(CFG_GET_GROUP(ui2_id))
    {
    case APP_CFG_GRPID_SOUND:
        i4_ret = acfg_fusion_tv_sound_set(ui2_id, i2_val);
        break;

    default:
        return APP_CFGR_INV_ARG;
    }

    return i4_ret;
}

extern INT32 a_cfg_fusion_av_update(
    UINT16  ui2_id)
{
    INT32   i4_ret = APP_CFGR_NO_ACTION;

    switch(CFG_GET_GROUP(ui2_id))
    {
    case APP_CFG_GRPID_PICTURE:
        i4_ret = acfg_fusion_tv_pic_update(ui2_id);
        break;

    case APP_CFG_GRPID_SOUND:
        i4_ret = acfg_fusion_tv_sound_update(ui2_id);
        break;

    default:
        return APP_CFGR_INV_ARG;
    }
    return i4_ret;
}

BOOL a_cfg_get_energy_star(VOID)
{
    return FALSE;
#ifdef NEVER
    CHAR s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};
    BOOL b_e_support = FALSE;

    a_cfg_custom_get_model_name(s_model_name);

    if((s_model_name[0] == 'V')&&(s_model_name[3] == '5'))
    {
        b_e_support =  FALSE;
    }
    else
    {
        b_e_support = TRUE;
    }
    ACFG_DBG_PRINT(" name : %s, b_e_support :%d \n",s_model_name, b_e_support);

    return b_e_support;
#endif /* NEVER */
}

BOOL a_cfg_cust_get_support_energy_start_by_mode_name(VOID)
{
    return a_cfg_get_energy_star();
}

BOOL a_cfg_cust_contrast_en_CheckIfCanTurnOn(void)
{
#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    // 2021-04-15: MVV-8350: Only RGB&&FullColor=On ==> Black_Detail grey out
    EnuAcfgFullColor444Status eAcfgFullColor444Status = acfg_cust_get_FullColor444_status();
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU]FullColor444{%s:%d} eAcfgFullColor444Status:%d\n",
        __FILE__, __LINE__, eAcfgFullColor444Status  )); );
    if( eAcfgFullColor444Status == ACFG_INPUT_RGB__FULL_COLOR_444_ON )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_BLACK_DETAIL|ACFG_DBG_PICT_FULL_COLOR444,
            DBG_LOG_PRINT(("[ACFG][Black_Detail]{%s,%d} FullColor444 => Black_Detail cannot turn on\n", __FUNCTION__,__LINE__ ));
        );
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
#endif

    if( a_acfg_cust_is_gll_enable() == TRUE )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_BLACK_DETAIL,
            DBG_LOG_PRINT(("[ACFG][Black_Detail]{%s,%d} GLL => Black_Detail cannot turn on!\n", __FUNCTION__,__LINE__ ));
        );
        return FALSE;
    }

    if( a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_BLACK_DETAIL,
            DBG_LOG_PRINT(("[ACFG][Black_Detail][VRR]{%s: %d} FreeSync => Black_Detail cannot turn on!\n", __FUNCTION__,__LINE__ ));
        );
        return FALSE;
    }

    if( a_cfg_cust_is_VRR_enable_and_driver_detect_VRR() == TRUE )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_BLACK_DETAIL,
            DBG_LOG_PRINT(("[ACFG][Black_Detail]{%s,%d} VRR => Black_Detail cannot turn on!\n", __FUNCTION__,__LINE__ ));
        );
        return FALSE;
    }

    return TRUE;
}

INT32 a_cfg_cust_drv_set_contrast_enhancement(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);


    if( ui1_idx )
    {
        if( a_cfg_cust_contrast_en_CheckIfCanTurnOn() == FALSE )
        {
            DBG_LOG_PRINT(("[ACFG][Black_Detail]{%s,%d} => Black_Detail cannot turn on => Force OFF\n", __FUNCTION__,__LINE__ ));
            ui1_idx = 0;
        }
    }


    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_CONTRAST_ENHANCEMENT;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_super_resolution(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
#ifndef MT5583_MODEL
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    if (a_cfg_cust_drv_get_4k_source())
    {
        ui1_idx = 0;
    }

    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SUPER_RESOLUTION;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );
#endif
    return i4_ret;
}

INT32 a_cfg_cust_drv_set_edge_enhancement(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_EDGE_ENHANCEMENT;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_peak_lunminance(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    ACFG_DEBUG_OLED_LUMI(
        DBG_LOG_PRINT(("[ACFG][OLED][BACKLIGHT][PeakLumi]{%s,%d} ui1_idx:%d\n", __func__, __LINE__, ui1_idx ));
    );

    if( ui1_idx >= 3 )
    {
        DBG_LOG_PRINT(("[ACFG][OLED][PeakLumi]{%s,%d} Error: Invalid ui1_idx:%d\n", __func__, __LINE__, ui1_idx ));
        return APP_CFGR_INV_ARG;
    }


    // MVP-3909
    // Peak Luminance:
    // High = 100% (1.0 x maximum peak value)  for both HDR and SDR
    // Mid  = 75% (0.75 x maximum peak value)  for both HDR and SDR
    // Low  = 50% (0.50 x maximum peak value) for SDR
    //        33% (0.33 x maximum peak value) for HDR
    // Off  = No peak luminance.   Currently we don¡¦t have this option

    UINT8 u8_percent = 100;

    switch( ui1_idx )
    {
        default:
        case 2: // High
            u8_percent = 100;
            break;
        case 1: // Mid
            u8_percent = 75;
            break;
        case 0: // Low
            {
                UINT8 ui1_HDR_type = a_acfg_cust_get_dynamic_range();
                if( ACFG_CUST_CONTENT_SDR == ui1_HDR_type )
                    u8_percent = 50;
                else
                    u8_percent = 33;

                ACFG_DEBUG_OLED_LUMI(
                    DBG_LOG_PRINT(("[ACFG][OLED][BACKLIGHT][PeakLumi]{%s,%d} ui1_HDR_type:%d, u8_percent:%d\n",
                        __func__, __LINE__, ui1_HDR_type, u8_percent ));
                );

            }
            break;
    }

    DBG_LOG_PRINT(("[ACFG][OLED][BACKLIGHT][PeakLumi]{%s,%d} call driver(PEAK_LUMINANCE) u8_percent:%d\n",
        __func__, __LINE__, u8_percent ));


    SIZE_T z_size = sizeof(u8_percent);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_PEAK_LUMINANCE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&u8_percent;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

#if 1//(ACFG_CUST_MEMC_NEW_METHOD)
BOOL a_cfg_cust_MEMC_get_UserOnOff(void)
{
    UINT8 ui1_test_memc = 0;

    INT32 i4_ret = a_cfg_cust_get_memc(&ui1_test_memc);
    if( i4_ret != APP_CFGR_OK )
    {
        DBG_LOG_PRINT(("[ACFG][MEMC]{%s,%d} a_cfg_cust_get_memc() failed => Force Memc=On\n", __FUNCTION__, __LINE__ ));
        ui1_test_memc = 1;
    }

    return ui1_test_memc;
}
#endif

INT32 a_cfg_cust_drv_set_judder_reduction(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
#ifdef APP_SUPPPORT_FRC
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(ui1_idx);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);


#if(ACFG_CUST_MEMC_NEW_METHOD)
    // Get MEMC On/Off
    if( a_cfg_cust_MEMC_get_UserOnOff() == FALSE )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_MEMC,
            DBG_LOG_PRINT(("[ACFG][MEMC]{%s,%d} MEMC user off => Set driver(JUDDER_REDUCTION)\n", __FUNCTION__, __LINE__ ));
        );
        return APP_CFGR_NO_ACTION;
    }
#endif

    DBG_LOG_PRINT(("[ACFG][MEMC]{%s,%d} Set driver(JUDDER_REDUCTION): ui1_idx:%d \n", __FUNCTION__, __LINE__, ui1_idx ));

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_JUDDER_REDUCTION;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );
#endif

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_motion_blur_reduction(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
#ifdef APP_SUPPPORT_FRC
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);


#if(ACFG_CUST_MEMC_NEW_METHOD)
    // Get MEMC On/Off
    if( a_cfg_cust_MEMC_get_UserOnOff() == FALSE )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_MEMC,
            DBG_LOG_PRINT(("[ACFG][MEMC]{%s,%d} MEMC User off => Set driver(MOTION_BLUR_REDUCTION)\n", __FUNCTION__, __LINE__ ));
        );
        return APP_CFGR_NO_ACTION;
    }
#endif


    DBG_LOG_PRINT(("[ACFG][MEMC]{%s,%d} Set driver(MOTION_BLUR_REDUCTION): ui1_idx:%d \n", __FUNCTION__, __LINE__, ui1_idx ));

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_MOTION_BLUR_REDUCTION;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );
#endif

    return i4_ret;
}

BOOL a_cfg_cust_local_contrast_CheckIfCanTurnOn(void)
{
#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    // 2021-04-15: MVV-8350: Only RGB&&FullColor=On ==> local_contrast grey out
    EnuAcfgFullColor444Status eAcfgFullColor444Status = acfg_cust_get_FullColor444_status();
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU]FullColor444{%s:%d} eAcfgFullColor444Status:%d\n",
        __FILE__, __LINE__, eAcfgFullColor444Status  )); );
    if( eAcfgFullColor444Status == ACFG_INPUT_RGB__FULL_COLOR_444_ON )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LOCAL_CONTRAST|ACFG_DBG_PICT_FULL_COLOR444,
            DBG_LOG_PRINT(("[ACFG][LocalContrast][FullColor444]{%s: %d} FullColor444 => LocalContrast cannot turn on!\n", __FUNCTION__,__LINE__ ));
        );
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
#endif

#if !( defined(MT5695_MODEL) && defined(MT5695_FAMILY_S) )
    if (a_acfg_cust_get_dynamic_range () == ACFG_CUST_CONTENT_DV)
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LOCAL_CONTRAST,
            DBG_LOG_PRINT(("[ACFG][LocalContrast][DV]{%s: %d} DV => LocalContrast cannot turn on!\n", __FUNCTION__,__LINE__ ));
        );
        return FALSE;
    }
#endif

    if( a_acfg_cust_is_gll_enable() == TRUE )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LOCAL_CONTRAST,
            DBG_LOG_PRINT(("[ACFG][LocalContrast][GLL]{%s: %d} GLL => LocalContrast cannot turn on!\n", __FUNCTION__,__LINE__ ));
        );
        return FALSE;
    }

    if( a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LOCAL_CONTRAST,
            DBG_LOG_PRINT(("[ACFG][LocalContrast][VRR]{%s: %d} FreeSync => LocalContrast cannot turn on!\n", __FUNCTION__,__LINE__ ));
        );
        return FALSE;
    }

    if( a_cfg_cust_is_VRR_enable_and_driver_detect_VRR() == TRUE )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LOCAL_CONTRAST,
            DBG_LOG_PRINT(("[ACFG][LocalContrast][VRR]{%s: %d} VRR => LocalContrast cannot turn on!\n", __FUNCTION__,__LINE__ ));
        );
        return FALSE;
    }

    return TRUE;
}

INT32 a_cfg_cust_drv_set_local_contrast(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(ui1_idx);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);


    ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LOCAL_CONTRAST,
        DBG_LOG_PRINT(("[ACFG_Drv][LocalContrast]{%s: %d} ui1_idx:%d\n", __FUNCTION__,__LINE__, ui1_idx ));
    );

    if( ui1_idx )
    {
        if( FALSE == a_cfg_cust_local_contrast_CheckIfCanTurnOn() )
        {
            ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LOCAL_CONTRAST,
                DBG_LOG_PRINT(("[ACFG_Drv][LocalContrast]{%s: %d} LocalContrast cannot turn on! => Force driver off\n", __FUNCTION__,__LINE__ ));
            );
            ui1_idx = 0;
        }
    }


    DBG_LOG_PRINT(("[ACFG_Drv][LocalContrast]{%s: %d} Set driver:ui1_idx:%d\n", __FUNCTION__,__LINE__, ui1_idx ));


    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_LOCAL_CONTRAST;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

//APP_CFG_RECID_VID_CUST_FULL_COLOR_444
#if 0
typedef enum
{
    SCC_VID_HDMI_MODE_UNKNOWN = 0,
    SCC_VID_HDMI_MODE_AUTO,
    SCC_VID_HDMI_MODE_GRAPHIC,
    SCC_VID_HDMI_MODE_VIDEO
}   SCC_VID_HDMI_MODE_T;
#endif

char* acfg_cust_get_SCC_VID_HDMI_MODE_name(SCC_VID_HDMI_MODE_T e_hdmi_mode)
{
    char* pcName = "Unknown";

    switch(e_hdmi_mode)
    {
        default:
            break;
        case SCC_VID_HDMI_MODE_AUTO:    pcName = "AUTO";
            break;
        case SCC_VID_HDMI_MODE_GRAPHIC: pcName = "GRAPHIC";
            break;
        case SCC_VID_HDMI_MODE_VIDEO:   pcName = "VIDEO";
            break;
    }

    return pcName;
}

BOOL g_ACFG_Drv_bCurHdmiModeIsGraphicMode = 0;

//INT32 a_cfg_cust_drv_set_full_color_444(SCC_VID_HDMI_MODE_T e_hdmi_mode)
INT32 a_cfg_cust_drv_set_full_color_444(UINT8 u8_full_color_444)
{
#if( ENABLE_FULL_COLOR_444 )
    INT32 i4_ret = 0;

    SCC_VID_HDMI_MODE_T e_hdmi_mode = (u8_full_color_444 ? SCC_VID_HDMI_MODE_GRAPHIC : SCC_VID_HDMI_MODE_AUTO);

    DBG_LOG_PRINT(("[ACFG][FullColor444][MEMC]{%s(full_color_444:%d)} => e_hdmi_mode:%d(%s)\n",
        __FUNCTION__, u8_full_color_444, e_hdmi_mode, acfg_cust_get_SCC_VID_HDMI_MODE_name(e_hdmi_mode) ));


    ACFG_VID_UPDATE_TRACE_LOG_PRINT((ACFG_VID_UPDATE_PREFIX"APP_CFG_RECID_VID_CUST_FULL_COLOR_444 ("
                   "e_hdmi_mode = %d, "
                   ")\r\n",
                   e_hdmi_mode
                   ));

    if( e_hdmi_mode == SCC_VID_HDMI_MODE_GRAPHIC )
        g_ACFG_Drv_bCurHdmiModeIsGraphicMode = TRUE;
    else
        g_ACFG_Drv_bCurHdmiModeIsGraphicMode = FALSE;


   /* Set the HDMI mode to both main and sub */
   i4_ret = c_scc_vid_set_hdmi_mode(h_g_acfg_scc_main_vid, e_hdmi_mode);
   ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);

   i4_ret = c_scc_vid_set_hdmi_mode(h_g_acfg_scc_sub_vid, e_hdmi_mode);
   ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);

 #if 0
   /* Print message */
   DBG_INFO(("<ACFG> HDMI mode =%d\n",e_hdmi_mode));
   switch(e_hdmi_mode)
   {
   case SCC_VID_HDMI_MODE_AUTO:
       DBG_INFO(("Auto\n"));
       break;
   case SCC_VID_HDMI_MODE_VIDEO:
       DBG_INFO(("Video\n"));
       break;
   case SCC_VID_HDMI_MODE_GRAPHIC:
       DBG_INFO(("Graphics\n"));
       break;
   default:
       DBG_INFO(("Unknown\n"));
       break;
   }
 #endif

   return i4_ret;

#else

    DBG_LOG_PRINT(("[ACFG][FullColor444][MEMC]{%s(%d)} 5583 ==> skip \n", __FUNCTION__, u8_full_color_444 ));
    return APP_CFGR_NO_ACTION;

#endif
}

INT32 a_cfg_cust_drv_set_contour_smoothing(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
#ifndef MT5583_MODEL
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(ui1_idx);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_CONTOUR_SMOOTHING;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );
#endif

    return i4_ret;
}

// Spec 3.1:
// Support:
//      2020 M7/M8, P9/PX, POLED
//      2021 D FHD, V6, M6, M7, P9/PX
// Not support:
//      2020 V5,M6
//      2021 D HD, V5
//
// 2021-03-05: MVV-8128: 2021 V5 should support VRR.
// 2021-03-10: MVV-8353: Vizio ask should test first, and then turn on OSD.
BOOL a_cfg_cust_is_variable_refresh_rate_support(VOID)
{
#if( defined(MT5695_MODEL)||defined(MT5695L_MODEL) )
    return TRUE;
#else
    CHAR   s_name[32] = {0};
    INT32  i4_ret  = 0;
    BOOL   is_support = FALSE;

    EnuCusModelSeries eCusModelSeries = a_cfg_cust_get_CurModelSeries();

    i4_ret = a_cfg_custom_get_model_name(s_name);
    ACFG_LOG_ON_FAIL(i4_ret);

    BOOL bIs2021Model = a_cfg_cust_Is_CurModel_after_2021_J();
    BOOL bIsOLEDModel = a_cfg_cust_Is_CurModel_OLED(); //  : OLED Panel


    if( a_cfg_cust_Is_CurModel_after_2022_K() ) // 2022
    {
        switch(s_name[0])
        {
            case 'V':
                // 2021-03-05: MVV-8128: 2021 V5 should support VRR.
                //if( CUS_MODEL_2022_91_V6 == eCusModelSeries )
                {
                    is_support =  TRUE;
                }
                break;

            case 'M': // For example: M55Q7-J01
                //if( CUS_MODEL_2022_91_M6 == eCusModelSeries )
                {
                    is_support =  TRUE;
                }
                break;

            case 'P': // 2022 P9,PX support
                {
                    is_support =  TRUE;
                }
                break;

            case 'D':
                //2022 5583 D series FHD support VRR, HD not support
                if( s_name[3] == 'f' )
                {
                    is_support =  TRUE;
                }
                break;

            default:
                break;
        }
    }
    else if( bIs2021Model ) // 2021
    {
        if( bIsOLEDModel ) // 2021 OLED support
        {
            is_support =  TRUE;
        }
        else
        {
            switch(s_name[0])
            {
                case 'D':
                    //2k21 5583 D series FHD support VRR, HD not support
                    if( s_name[3] == 'f' )
                    {
                        is_support =  TRUE;
                    }
                    break;

                case 'V':
                    // 2021-03-05: MVV-8128: 2021 V5 should support VRR.
                    if( CUS_MODEL_2021_91_V5 == eCusModelSeries ) // 2021 V5 support
                    {
                        // 2021-03-10: MVV-8353: Vizio ask should test first, and then turn on OSD.
                        //is_support =  TRUE;
                    }
                    else if( CUS_MODEL_2021_95L_V6 == eCusModelSeries ) // 2021-5695L V6 // 18, V**C6-J**: V50C6-J09, V65C6-J09,
                    {
                        is_support =  TRUE;
                    }
                    else if( s_name[3] == '6' ) // 2021 5691 V6 support
                    {
                        is_support =  TRUE;
                    }
                    break;

                case 'M': // For example: M55Q7-J01
                    if( (s_name[4] == '6')||(s_name[4] == '7') ) // 2021 M6/M7 support
                    {
                        is_support =  TRUE;
                    }
                    break;

                case 'P': // 2021 P9,PX support
                    {
                        is_support =  TRUE;
                    }
                    break;

                default:
                    break;
            }
        }
    }
    else // 2020
    {
        if( bIsOLEDModel ) // 2020 OLED support
        {
            is_support =  TRUE;
        }
        else
        {
            switch(s_name[0])
            {
                case 'M': // For example: M55Q8-H1
                    if( (s_name[4] == '7')||(s_name[4] == '8') ) // 2020 M7/M8 support
                    {
                        is_support =  TRUE;
                    }
                    break;

                case 'P': // 2020 P9,PX support
                    {
                        is_support =  TRUE;
                    }
                    break;

                default:
                    break;
            }
        }
    }


    ACFG_DBG_INFO(" s_name :%s,is_support :%d \r\n",s_name,is_support);
    //DBG_LOG_PRINT(("[ACFG][VRR] {%s: %s: %d} s_name :%s,is_support :%d\n", __FILE__, __FUNCTION__,__LINE__, s_name,is_support ));

    return  is_support;
#endif
}

// spec 4.0 2021 D skus only supported but no cert
BOOL a_cfg_cust_is_FreeSync_logo_support(VOID)
{

    EnuCusModelSeries enModel = a_cfg_cust_get_CurModelSeries();
    BOOL is_support = FALSE;

    switch(enModel)
    {
    #if( defined(MT5695_MODEL)||defined(MT5695L_MODEL) )
        case CUS_MODEL_2020_95_P9:
        case CUS_MODEL_2020_95_PX:
        case CUS_MODEL_2021_95_P9:
        case CUS_MODEL_2021_95_PX:
        case CUS_MODEL_2022_95S_P:
    #endif
        case CUS_MODEL_2020_91_M7:
        case CUS_MODEL_2020_91_M8:
        case CUS_MODEL_2021_91_V6:
        case CUS_MODEL_2021_91_M6:
        case CUS_MODEL_2021_91_M7:
        case CUS_MODEL_2022_91_V6:
        case CUS_MODEL_2022_91_M6:
        case CUS_MODEL_2022_95L_V6:
        case CUS_MODEL_2022_83_2K_D:
        {
            is_support = TRUE;
        }
        break;

        default:
            break;
    }

    if (b_2021_83_FHD_is_FreeSync_logo_support)
    {
        is_support = TRUE;
    }

    return is_support;
}

BOOL a_cfg_cust_is_gll_support_and_gaming_engine_no_support(VOID)
{
    CHAR   s_name[32] = {0};
    INT32  i4_ret  = 0;
    BOOL   is_support = FALSE;

    i4_ret = a_cfg_custom_get_model_name(s_name);
    ACFG_LOG_ON_FAIL(i4_ret);


    //2k21/2022 5583 D series HD support GLL but without progaming/v-gaming engine item
    if( ( s_name[0] == 'D' )&&( s_name[3] == 'h' ) /*&& (c_strstr(s_name,"-J")!= NULL)*/ )
    {
        is_support =  TRUE;
    }


    ACFG_DBG_INFO(" s_name :%s,is_support :%d \r\n",s_name,is_support);

    return  is_support;
}

INT32 a_cfg_cust_drv_set_variable_refresh_rate(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_PRINT("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    if (a_cfg_cust_is_variable_refresh_rate_support() == FALSE)
    {
        ACFG_DBG_INFO("NOT Support variable_refresh_rate \r\n");
        return i4_ret;
    }

    // Check source: If not HDMI, then skip
    UINT8 u8CurHdmiUiIdx = acfg_cust_get_CurSrcHdmi_UI_Idx();
    if( u8CurHdmiUiIdx >= 4 )
    {
        DBG_LOG_PRINT(("[ACFG][VRR][EDID]{%s,%d} Cur source is not HDMI => skip set VRR\n", __FUNCTION__, __LINE__ ));
        return APP_CFGR_NO_ACTION;
    }

#if( ACFG_CUST_VRR_SET_DRIVER_BY_PORT )
    extern INT16 g_ai16_vrr_last[4];

    // Check if setting is the same...
    if( ui1_idx == g_ai16_vrr_last[u8CurHdmiUiIdx] )
    {
        DBG_LOG_PRINT(("[ACFG][VRR][EDID]{%s,%d} Cur VRR setting(%d) is the same => skip\n", __FUNCTION__, __LINE__, ui1_idx ));
        return APP_CFGR_NO_ACTION;
    }

    g_ai16_vrr_last[u8CurHdmiUiIdx] = ui1_idx;

#else
    extern INT16 i2_g_vrr_set;

    // Check if setting is the same...
    if( ui1_idx == i2_g_vrr_set )
    {
        DBG_LOG_PRINT(("[ACFG][VRR][EDID]{%s,%d} Cur VRR setting(%d) is the same => skip\n", __FUNCTION__, __LINE__, ui1_idx ));
        return APP_CFGR_NO_ACTION;
    }

    i2_g_vrr_set = ui1_idx;

#endif


    DBG_LOG_PRINT(("[ACFG][VRR][EDID]{%s,%d} call driver(VARIABLE_REFRESH_RATE) ui1_idx:%d\n",
        __FUNCTION__, __LINE__, ui1_idx ));

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_VARIABLE_REFRESH_RATE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    //Fix VRR on off  abnormol
    if(a_menu_is_resume())
    {
        c_thread_delay(200);
    }

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_blank_screen(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_BLANK_SCREEN;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

BOOL a_cfg_cust_zoom_digit_selection_support(VOID)
{
    BOOL   is_support = TRUE;

    if( a_cfg_cust_Is_CurModel_after_2021_J() ) // 2021/2022/...
    {
        is_support =  FALSE;
    }
    else // 2020
    {
        EnuCusModelSeries eCusModel = a_cfg_cust_get_CurModelSeries();

        // 2k20 P-model
        if( (eCusModel == CUS_MODEL_2020_95_P9) // 5, P***9-H**: P65Q9-H1
          ||(eCusModel == CUS_MODEL_2020_95_PX) // 6, P***X-H*: P75QX-H1
          ||(eCusModel == CUS_MODEL_2020_95_OLED) // 7, OLED**-H*: OLED55-H1/OLED65-H1
          )
        {
            is_support = FALSE;
        }
    }

    return is_support;
}

BOOL a_cfg_cust_oled_support(VOID)
{
#if 1
    return s_b_is_OLED_model;
#else
    CHAR   s_name[32] = {0};
    INT32  i4_ret  = 0;
    BOOL   is_support = FALSE;

    i4_ret = a_cfg_custom_get_model_name(s_name);
    ACFG_LOG_ON_FAIL(i4_ret);

    //  : OLED Panel
    if(c_strstr(s_name,"OLED")!= NULL)
    {
        is_support =  TRUE;
    }

    return  is_support;
#endif
}

BOOL a_cfg_cust_is_support_progaming_engine(VOID)
{
    CHAR          s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8         ui1_input;
    ISL_REC_T     t_isl_rec = {0};

    /* Get target input source */
    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

    #if 0
    /*current state is smart cast */
    if(t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL &&  t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
    {
        return TRUE;
    }

    //Hdmi source
    if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI ||
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI)
    {
        return TRUE;
    }
    #endif

    //DTV02231351
    //ProGaming Engine for only HDMI source
    //Hdmi source
    if(a_nav_ipts_is_hdmi_source(&t_isl_rec))
    {
        return TRUE;
    }


    return FALSE;
}

//Dv game mode
#if 0
static VOID _cfg_cust_set_dv_game_mode_flag(UINT8 ui1_val)
{
    ACFG_DEBUG_LOG( ACFG_DBG_DV,
        DBG_LOG_PRINT(("[ACFG][DV][GAME]_cfg_cust_set_dv_game_mode_flag(%d)\n", ui1_val ));
    );

    ui1_g_game_mode_flag = ui1_val;
}
#endif

UINT8 a_cfg_cust_get_cur_dv_game_mode_flag(VOID)
{
    return ui1_g_game_mode_flag;
}

BOOL a_cfg_cust_is_support_game_low_latency(VOID)
{
    INT32                       i4_ret     = 0;
    ISL_REC_T                   t_isl_rec;
    UINT8                       ui1_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;

    c_memset (&t_isl_rec, 0, sizeof(ISL_REC_T));

    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
    ACFG_LOG_ON_FAIL(i4_ret);

    //only for hdmi source
    if (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI &&
        t_isl_rec.t_avc_info.e_video_type != DEV_AVC_DVI)
    {
        ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} Non-HDMI => Not support GLL \n", __FUNCTION__,__LINE__)); );
        return FALSE;
    }

#if 0 // 2021/04/12. No this spec!
    //dobly vision not support gll, but dv game mode support gll
    if (a_cfg_get_hdr_type() == SCC_VID_PQ_DOVI && _cfg_cust_get_dv_game_mode_flag() != APP_CFG_VID_GAME_MODE_ON)
    {
        DBG_LOG_PRINT((" [ACFG] <%s:%4d> content_type:%d  dv_game_mode_flag:%d \r\n", __FUNCTION__, __LINE__,a_cfg_get_hdr_type(),_cfg_cust_get_dv_game_mode_flag()));
        return FALSE;
    }
#endif

    if (a_menu_test_patterns_is_show() == TRUE)
    {
        //ACFG_DBG_INFO(" a_menu_test_patterns_is_show1 \r\n");
        DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} a_menu_test_patterns_is_show => Not support GLL \n", __FUNCTION__,__LINE__));
        return FALSE;
    }

    a_icl_custom_get_test_pattern_status(&ui1_val);
    if(ui1_val != ICL_RECID_TEST_PATTERN_STATUS_DISABLE)
    {
        //ACFG_DBG_INFO(" a_menu_test_patterns_is_show2 \r\n");
        DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} a_icl_custom_get_test_pattern_status => Not support GLL \n", __FUNCTION__,__LINE__));
        return FALSE;
    }

    return TRUE;
}

BOOL a_cfg_cust_drv_get_allm_status(VOID)
{
    BOOL                         b_status   = FALSE;
    DRV_CUST_OPERATION_INFO_T    t_op_info = {0};

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_ALLM;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&b_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    INT32 i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);
    if( i4_ret != RMR_OK )
    {
        DBG_LOG_PRINT(("[ACFG]{%s, %d} Error: call c_rm_get_comp() failed ==> %d\n", __FUNCTION__,__LINE__, i4_ret));
        return FALSE;
    }

    return (BOOL)b_status;
}

char* a_cfg_cust_get_GLL_para_str(UINT8 ui1_idx)
{
    char* pc_GLL_para_str = "Unknown";

    switch( ui1_idx )
    {
        default:    break;
        case ACFG_CUST_GAME_LOW_LATENCY_AUTO:
            pc_GLL_para_str = "GLL_AUTO";
            break;

        case ACFG_CUST_GAME_LOW_LATENCY_OFF:
            pc_GLL_para_str = "GLL_OFF";
            break;

        case ACFG_CUST_GAME_LOW_LATENCY_ON:
            pc_GLL_para_str = "GLL_ON";
            break;
    }

    return pc_GLL_para_str;
}

BOOL a_cfg_cust_GLL_get_force_value(UINT8* pu8_GLL_setting)
{
    if( a_cfg_cust_is_support_game_low_latency() == FALSE )
    {
        ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} Not support GLL => Force GLL OFF\n", __FUNCTION__,__LINE__)); );
        *pu8_GLL_setting = ACFG_CUST_GAME_LOW_LATENCY_OFF;
        return TRUE;
    }

#if( VZO_DV__GLL_CONTROL_BY_DV_GAME )
    if( a_cfg_get_hdr_type() == SCC_VID_PQ_DOVI )
    {
        if( APP_CFG_VID_GAME_MODE_OFF == a_cfg_cust_get_cur_dv_game_mode_flag() )
        {
            *pu8_GLL_setting = ACFG_CUST_GAME_LOW_LATENCY_OFF;
            DBG_LOG_PRINT(("[ACFG][DV][GAME][GLL]{%s, %d} DV(non-Game) => Force GLL OFF\n", __FUNCTION__,__LINE__));
        }
        else // DV Game
        {
            *pu8_GLL_setting = ACFG_CUST_GAME_LOW_LATENCY_ON;
            DBG_LOG_PRINT(("[ACFG][DV][GAME][GLL]{%s, %d} DV(Game) => Force GLL ON\n", __FUNCTION__,__LINE__));
        }

        return TRUE;
    }
#endif

    return FALSE;
}

//
INT32 a_cfg_cust_drv_set_game_low_latency(UINT8 ui1_idx)
{
    INT32 i4_ret = APP_CFGR_OK;


    DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s,%d} a_cfg_cust_drv_set_game_low_latency(ui1_idx:%d(%s))\n",
        __FUNCTION__,__LINE__, ui1_idx, a_cfg_cust_get_GLL_para_str(ui1_idx) ));

#if 1

 #if 0// Test no set driver...
    if( a_cfg_get_hdr_type() == SCC_VID_PQ_DOVI )
    {
        DBG_LOG_PRINT(("[ACFG][GAME][GLL][DV]{%s,%d} DV ==> skip a_cfg_cust_drv_set_game_low_latency(ui1_idx:%d(%s))\n",
            __FUNCTION__,__LINE__, ui1_idx, a_cfg_cust_get_GLL_para_str(ui1_idx) ));
        return APP_CFGR_OK;
    }
 #endif


    // Check if need to force value ...
    UINT8 u8_force_GLL_setting = 0;
    if( a_cfg_cust_GLL_get_force_value(&u8_force_GLL_setting) )
    {
        ui1_idx = u8_force_GLL_setting;
        DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s,%d} Force GLL => ui1_idx:%d(%s)\n",
            __FUNCTION__,__LINE__, ui1_idx, a_cfg_cust_get_GLL_para_str(ui1_idx) ));
    }


    if( ui1_idx != ACFG_CUST_GAME_LOW_LATENCY_OFF )
    {
        if ( a_cfg_cust_is_support_game_low_latency() == FALSE )
        {
            DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} Not support GLL => Force OFF\n", __FUNCTION__,__LINE__));
            ui1_idx = ACFG_CUST_GAME_LOW_LATENCY_OFF;
        }
    }


    UINT8 u8_game_mode_en = FALSE;

    switch( ui1_idx )
    {
        case ACFG_CUST_GAME_LOW_LATENCY_AUTO:
            if( a_cfg_cust_drv_get_allm_status() == TRUE)
            {
                u8_game_mode_en = TRUE;
            }
            else
            {
                u8_game_mode_en = FALSE;
            }
            break;

        case ACFG_CUST_GAME_LOW_LATENCY_OFF:
            u8_game_mode_en = FALSE;
            break;

        case ACFG_CUST_GAME_LOW_LATENCY_ON:
            u8_game_mode_en = TRUE;
            break;

        default:
            return APP_CFGR_INV_ARG;
            break;

    }

    // set to driver ...
    ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} u8_game_mode_en:%d \n", __FUNCTION__,__LINE__, u8_game_mode_en )); );

    i4_ret = a_cfg_cust_drv_set_game_mode(u8_game_mode_en);

    return i4_ret;

#else


    if ( a_cfg_cust_is_support_game_low_latency() == FALSE )
    {
        if (b_g_gll_off_flag == TRUE)
        {
            DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} Skip call driver\n", __FUNCTION__,__LINE__));
            return i4_ret;
        }
        b_g_gll_off_flag = TRUE;
        ui1_idx = ACFG_CUST_GAME_LOW_LATENCY_OFF;
    }
    else if ( ui1_idx == ACFG_CUST_GAME_LOW_LATENCY_AUTO )
    {
        if( a_cfg_cust_drv_get_allm_status() == TRUE)
        {
            a_cfg_cust_drv_set_game_mode(TRUE);
        }
        else
        {
            a_cfg_cust_drv_set_game_mode(FALSE);
        }
        b_g_gll_off_flag = FALSE;
    }
    else // Off/On
    {
        b_g_gll_off_flag = FALSE;
    }


    DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s,%d} Set driver(GAME_LOW_LATENCY) ui1_idx:%d \n",
        __FUNCTION__,__LINE__, ui1_idx));


    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GAME_LOW_LATENCY;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;

#endif
}

INT32 a_cfg_cust_drv_set_game_hdr(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    SIZE_T z_size = sizeof(ui1_idx);

    if ( a_cfg_cust_is_support_game_low_latency() == FALSE )
    {
       ui1_idx = ACFG_CUST_COMMON_OFF;
    }

    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GAME_HDR;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_game_mode(BOOL b_enable)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set b_enable :%d \r\n",b_enable);

    SIZE_T z_size = sizeof(b_enable);


    //ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][Game]a_cfg_cust_drv_set_game_mode(b_enable:%d)\n", b_enable)); );
    DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s,%d} Set driver(GAME_MODE) b_enable:%d \n", __FUNCTION__,__LINE__, b_enable));

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GAME_MODE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&b_enable;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_drv_eotf(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
#ifdef NEVER
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_EOTF;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );
#endif /* NEVER */

    return i4_ret;
}

BOOL a_cfg_cust_en_view_angle_Is_Panel_Support_But_UI_Not_Support(void)
{
#ifdef MT5691_MODEL
    UINT32 ui4_model_group = 0;
    INT32 i32Rtn = a_cfg_custom_get_model_group_id(&ui4_model_group);
    if( i32Rtn != 0 )
    {
        DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): Error: Cannot get model_group_id! i32Rtn:%d\n", __func__, i32Rtn));
        return FALSE;
    }

    ACFG_DEBUG_VIEW_ANGLE(
        DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): ui4_model_group:%d\n", __func__, ui4_model_group));
    );


    UINT32 ui4_model_idx = 0;
    i32Rtn = a_cfg_custom_get_model_idx(&ui4_model_idx);
    if( i32Rtn != 0 )
    {
        DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): Error: Cannot get model_idx! i32Rtn:%d\n", __func__, i32Rtn));
        return FALSE;
    }

    ACFG_DEBUG_VIEW_ANGLE(
        DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): ui4_model_idx:%d\n", __func__, ui4_model_idx));
    );

    // TPV: V435-J01: Group=302, ModelIdx=40.
    if( (ui4_model_group == 0x302)&&(ui4_model_idx==40) )
    {
        ACFG_DEBUG_VIEW_ANGLE(
            DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): ==> TRUE\n", __func__));
        );
        return TRUE;
    }
#endif

    return FALSE;
}

// Jira: MVP-3672: P75Q9-J01: no viewing angle enhancement.
BOOL a_cfg_cust_en_view_angle_support(VOID)
{
#ifdef MT5583_MODEL
    return FALSE;

#else
    static int _s_iIsSupport_ViewAngle = -1;

    CHAR   s_name[32] = {0};
    INT32  i4_ret  = 0;
    BOOL   is_support = FALSE;
    UINT8  ui1_odm_id = 0;
    UINT32 ui4_model_idx = 0;


    ACFG_DEBUG_VIEW_ANGLE( DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): _s_iIsSupport_ViewAngle=%d\n", __func__, _s_iIsSupport_ViewAngle)); );

    if( _s_iIsSupport_ViewAngle != -1 )
    {
        ACFG_DEBUG_VIEW_ANGLE( DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): 1 return support=%d\n", __func__, _s_iIsSupport_ViewAngle)); );
        return _s_iIsSupport_ViewAngle;
    }

    i4_ret = a_cfg_custom_get_model_name(s_name);
    ACFG_LOG_ON_FAIL(i4_ret);

    //  : ,MXXQ7,MXXQ8
    if( (s_name[0] == 'M') )
    {
        if( (c_strstr(s_name,"Q8")!= NULL)||(c_strstr(s_name,"Q7")!= NULL) )
        {
            //  M65Q7 ,M65Q8 inch not support alcw
            //  2k21 M70Q7-J03  and M75Q7-J03  don't support ELCE
            if ((c_strstr(s_name,"65")!= NULL) || (c_strstr(s_name,"J03")!= NULL))
            {
                is_support =  FALSE;
            }
            else
            {
                is_support =  TRUE;
            }
        }
        //  : M50QX-K01,M55QX-K01, Add for DTV03326414
        else if( (c_strstr(s_name,"QX")!= NULL) && (c_strstr(s_name,"K01")!= NULL) )
        {
            if ( c_strstr(s_name,"55") != NULL )
            {
                is_support =  TRUE;
            }
        }
    }
    //  : PX,P9
    else if(s_name[0] == 'P')
    {
        if( 0 == c_strcmp(s_name, "P75Q9-J01") )
        {
            is_support =  FALSE;
        }
        else
        {
            is_support =  TRUE;
        }
    }

    if( is_support == FALSE )
    {
        if( a_cfg_cust_en_view_angle_Is_Panel_Support_But_UI_Not_Support() )
        {
            is_support =  TRUE;
        }
    }

    if( is_support == FALSE )
    {
        //
        i4_ret = a_cfg_custom_get_odm_idx(&ui1_odm_id);
        ACFG_LOG_ON_FAIL(i4_ret);
        //
        i4_ret = a_cfg_custom_get_model_idx(&ui4_model_idx);
        ACFG_LOG_ON_FAIL(i4_ret);

        //v505-h9 v655-h9 v655x-h9 v655x-h9(tcon-less) m506x-h9 need to support ELCE
        if(ui1_odm_id == ODM_ID_Innolux) //innolux
        {
        #if 0
            if((ui4_model_idx == 2) || (ui4_model_idx == 6) || (ui4_model_idx == 7) || (ui4_model_idx == 8) || (ui4_model_idx == 9) || (ui4_model_idx == 10) || (ui4_model_idx >= 12))
            {
                is_support = TRUE;
            }
        #else //ELCS judgement by [PANEL_I2C] config in 'Customer_1.ini'
            MI_HANDLE               h_acfg_ini = NULL_HANDLE;
            MI_SYS_ConfigData_t     t_ini_data;
            CHAR                    s_file_path[] = "/config/model/Customer_1.ini\0";
            CHAR                    s_key[] = "PANEL_I2C:u16PnlI2cSlaveAddr\0";
            i4_ret = MI_SYS_OpenConfigFile((MI_U8*)s_file_path, &h_acfg_ini);
            if (i4_ret == MI_OK)
            {
                c_memset(&t_ini_data, 0, sizeof(MI_SYS_ConfigData_t));
                t_ini_data.eDataType = E_MI_SYS_CONFIG_DATA_TYPE_U32;
                i4_ret = MI_SYS_GetConfigData(h_acfg_ini, (const MI_U8 *)s_key, &t_ini_data);
                if (i4_ret == MI_OK)
                {
                    DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): u16PnlI2cSlaveAddr=0x%X\r\n", __func__, t_ini_data.u32Data));

                    if (t_ini_data.u32Data != 0xFFFFFFFF)
                    {
                        is_support = TRUE;
                    }
                    else
                    {
                        DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): invalid data\n", __func__));
                    }
                }
                else
                {
                    DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): Get '%s' from ini failed! i4_ret:%d\n", __func__, s_key, i4_ret));
                }
                MI_SYS_CloseConfigFile(h_acfg_ini);
                h_acfg_ini = NULL_HANDLE;
            }
            else
            {
                DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): Open config file %s error! i4_ret:%d\n", __func__, s_file_path, i4_ret));
            }
        #endif

        }

    }

    DBG_LOG_PRINT(("[ACFG][ViewAngle] s_name :%s,is_support :%d \r\n",s_name,is_support));

    _s_iIsSupport_ViewAngle = is_support;
    //DBG_LOG_PRINT(("[ACFG][ViewAngle]%s(): _s_iIsSupport_ViewAngle=%d\n", __func__, _s_iIsSupport_ViewAngle));

    return  is_support;
#endif
}

BOOL a_cfg_cust_enhanced_viewing_angle_IfCanTurnOn(void)
{
    //MVP-2383
    //if TV detect VRR signal, then EVA should grayout and off
    if( (a_acfg_cust_vrr_is_enable_and_detect_stream() == TRUE)
      ||(a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE)
      )
    {
        ACFG_DEBUG_VIEW_ANGLE( DBG_LOG_PRINT(("[ACFG][ViewAngle]%s() Cannot turn on! => 0\n", __func__ )); );
        return FALSE;
    }

    ACFG_DEBUG_VIEW_ANGLE( DBG_LOG_PRINT(("[ACFG][ViewAngle]%s() Can turn on! => 1\n", __func__ )); );

    return TRUE;
}

INT32 a_cfg_cust_drv_set_enhanced_viewing_angle(UINT8 ui1_idx)
{
    INT32  i4_ret = APP_CFGR_OK;

#ifndef MT5583_MODEL

    ACFG_DEBUG_VIEW_ANGLE( DBG_LOG_PRINT(("[ACFG][ViewAngle] %s(%d)\n", __FUNCTION__, ui1_idx)); );

    if( a_cfg_cust_en_view_angle_support() == FALSE )
    {
        //ACFG_DBG_INFO("NOT Support enhanced view angle \r\n");
        DBG_LOG_PRINT(("[ACFG][ViewAngle]{%s:%d} Warning: NOT Support enhanced view angle!!\n", __FUNCTION__, __LINE__));
        return APP_CFGR_NOT_SUPPORT;
    }

    if( ui1_idx != 0 ) // Turn on
    {
        if( a_cfg_cust_en_view_angle_Is_Panel_Support_But_UI_Not_Support() )
        {
            DBG_LOG_PRINT(("[ACFG][ViewAngle]{%s:%d} Warning: Patch!! Force to off!!\n", __FUNCTION__, __LINE__));
            ui1_idx = 0;
        }
        else if( a_cfg_cust_enhanced_viewing_angle_IfCanTurnOn() == FALSE )
        {
            DBG_LOG_PRINT(("[ACFG][ViewAngle]{%s:%d} Warning: Cannot turn on enhanced view angle!! Force to off\n", __FUNCTION__, __LINE__));
            ui1_idx = 0;
        }
    }


    DBG_LOG_PRINT(("[ACFG][ViewAngle] {%s:%d} Call SCC set ENHANCED_VIEWING_ANGLE ui1_idx :%d \n", __FUNCTION__, __LINE__,ui1_idx));

    DRV_CUST_OPERATION_INFO_T   t_op_info = {0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_ENHANCED_VIEWING_ANGLE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

#endif

    return i4_ret;
}

INT32 a_cfg_update_20_point(VOID* pv_GammactrlPts, SIZE_T z_size_val)
{
    INT32 i4_ret = APP_CFGR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T z_size = sizeof(DRV_CUST_OPERATION_INFO_T);

    if (NULL == pv_GammactrlPts || 0 == z_size_val)
    {
         DBG_ERROR(("[ACFG] NULL Para %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INV_ARG;
    }
    ACFG_DBG_INFO("Enter \r\n");

#if 0
    UINT16 ui2_point_index,ui2_gain_index;
    INT32 (*pi4_GammactrlPts)[APP_CFG_11_POINT_GAIN_NUM] = (INT32 (*)[APP_CFG_11_POINT_GAIN_NUM])pv_GammactrlPts;
    DBG_LOG_PRINT(("\n############## MAMA dump ############\n"));

    for(ui2_point_index = 0;ui2_point_index < 3;ui2_point_index++)
    {
        for(ui2_gain_index = 0;ui2_gain_index < APP_CFG_11_POINT_GAIN_NUM;ui2_gain_index++)
        {
            DBG_LOG_PRINT(("pi4_GammactrlPts[%d][%2d] = %d\n",ui2_point_index,ui2_gain_index,pi4_GammactrlPts[ui2_point_index][ ui2_gain_index]));
        }
    }
    DBG_INFO(("\n################################\n"));
#endif
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_20_P_WB;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)(pv_GammactrlPts);
    t_op_info.u.t_vid_set_info.z_size = z_size_val;
    t_op_info.u.t_vid_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_size);

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_20_p_wb(VOID)
{
    UINT8                       ui1_j = 0;
    INT32                       i4_ret = 0;
    UINT16                      ui2_ipt = a_acfg_cust_get_dynamic_range();
    INT16                       i2_clr_tmp = 0;
    UINT16                      ui2_elem_idx;
    INT32                       ai4_11_point_values[3][APP_CFG_11_POINT_GAIN_NUM];
    INT16                       i2_val;
    UINT8                       ui1_odm_id = 0;
    INT16                       ai2_20_point_fac_values_R[APP_CFG_11_POINT_GAIN_NUM] = {0};
    INT16                       ai2_20_point_fac_values_G[APP_CFG_11_POINT_GAIN_NUM] = {0};
    INT16                       ai2_20_point_fac_values_B[APP_CFG_11_POINT_GAIN_NUM] = {0};

    /* layout by src*clr_temp*11_point_gain, and will use the global one*/
    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_tmp);
    ACFG_LOG_ON_FAIL(i4_ret);

    a_cfg_custom_get_odm_idx(&ui1_odm_id);
    if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE))
    {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_11_POINT_RED), ai2_20_point_fac_values_R);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_11_POINT_GREEN), ai2_20_point_fac_values_G);
        ACFG_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_11_POINT_BLUE), ai2_20_point_fac_values_B);
        ACFG_LOG_ON_FAIL(i4_ret);
    }

    for(ui1_j = 0; ui1_j < APP_CFG_11_POINT_GAIN_NUM; ui1_j++)
    {
        ui2_elem_idx = ui2_ipt * ACFG_CLR_TEMP_NUM*APP_CFG_11_POINT_GAIN_NUM
                        + i2_clr_tmp*APP_CFG_11_POINT_GAIN_NUM
                        + ui1_j;

        i4_ret = acfg_get_int16_by_idx(IDX_11_POINT_GAIN_RED,ui2_elem_idx,&i2_val);
        ACFG_LOG_ON_FAIL(i4_ret);
        ai4_11_point_values[0][ui1_j] = (INT32)i2_val + (INT32)ai2_20_point_fac_values_R[ui1_j];

        i4_ret = acfg_get_int16_by_idx(IDX_11_POINT_GAIN_GREEN,ui2_elem_idx,&i2_val);
        ACFG_LOG_ON_FAIL(i4_ret);
        ai4_11_point_values[1][ui1_j] = (INT32)i2_val + (INT32)ai2_20_point_fac_values_G[ui1_j];

        i4_ret = acfg_get_int16_by_idx(IDX_11_POINT_GAIN_BLUE,ui2_elem_idx,&i2_val);
        ACFG_LOG_ON_FAIL(i4_ret);
        ai4_11_point_values[2][ui1_j] = (INT32)i2_val + (INT32)ai2_20_point_fac_values_B[ui1_j];

    }

    i4_ret = a_cfg_update_20_point((VOID*)ai4_11_point_values, sizeof(ai4_11_point_values));
    ACFG_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT32 a_cfg_cust_get_color_tuner_items_value(UINT8 ui1_item_idx, UINT8 ui1_sub_item_idx, INT16* pui2_value)
{
    INT32       i4_ret = 0;
    UINT16      ui2_idx = 0;
    INT16       i2_value = 0;
    INT16       i2_fac_value = 0;
    UINT8       ui1_input = 0;
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8       ui1_odm_id = 0;

    /* Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    //acfg_cust_video_get_special_item_idx(ui1_input,&ui2_idx);
    acfg_cust_video_Get_DataOffset_By_Src_Content_PicMode( APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_M, ui1_input, &ui2_idx);

    i4_ret = a_cfg_custom_get_odm_idx(&ui1_odm_id);
    ACFG_LOG_ON_FAIL(i4_ret);

    switch(ui1_item_idx)
    {
        case ACFG_COLOR_TUNER_BRI:
        {
            if(ui1_sub_item_idx == ACFG_COLOR_TUNER_M)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_BRI_M, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_M), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }
            }
            else  if(ui1_sub_item_idx == ACFG_COLOR_TUNER_R)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_BRI_R, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_R), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_Y)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_BRI_Y, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_Y), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_G)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_BRI_G, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_G), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_C)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_BRI_C, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_C), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_B)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_BRI_B, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_BRI_B), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else
            {
                 DBG_ERROR(("[ACFG] Invalid data  %s,%d\r\n",__FUNCTION__,__LINE__));
                 i2_value = 0;
            }
            break;
        }
        case ACFG_COLOR_TUNER_SAT:
        {
            if(ui1_sub_item_idx == ACFG_COLOR_TUNER_M)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_SAT_M, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_M), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else  if(ui1_sub_item_idx == ACFG_COLOR_TUNER_R)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_SAT_R, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_R), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_Y)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_SAT_Y, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_Y), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_G)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_SAT_G, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_G), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_C)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_SAT_C, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_C), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_B)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_SAT_B, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_SAT_B), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else
            {
                 DBG_ERROR(("[ACFG] Invalid data  %s,%d\r\n",__FUNCTION__,__LINE__));
                 i2_value = 0;
            }
            break;
        }
        case ACFG_COLOR_TUNER_HUE:
        {
            if(ui1_sub_item_idx == ACFG_COLOR_TUNER_M)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_HUE_M, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_M), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }
            }
            else  if(ui1_sub_item_idx == ACFG_COLOR_TUNER_R)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_HUE_R, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_R), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_Y)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_HUE_Y, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_Y), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_G)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_HUE_G, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_G), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_C)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_HUE_C, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_C), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else if(ui1_sub_item_idx == ACFG_COLOR_TUNER_B)
            {
                i4_ret = acfg_get_int16_by_idx(IDX_CLR_HUE_B, ui2_idx, &i2_value);
                ACFG_CHK_FAIL(i4_ret, i4_ret);
                if ( (ui1_odm_id == ODM_ID_TPV) || (ui1_odm_id == ODM_ID_Foxconn) || (ui1_odm_id == ODM_ID_Innolux) || (ui1_odm_id == ODM_ID_BOE) )
                {
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_FACTORY, APP_CFG_RECID_CUST_FAC_CLR_TUNER_HUE_B), &i2_fac_value);
                    ACFG_LOG_ON_FAIL(i4_ret);
                }

            }
            else
            {
                 DBG_ERROR(("[ACFG] Invalid data  %s,%d\r\n",__FUNCTION__,__LINE__));
                 i2_value = 0;
            }
            break;
        }
            break;
        default:
            break;
    }

    //*pui2_value = i2_value;
    *pui2_value = i2_value + i2_fac_value;


    return i4_ret;
}

/*
//pq exp color define
#define SCC_PQ_EXP_COLOR_NUMBER  7
typedef struct _SCC_PQ_EXP_COLOR_T
{
    UINT8 ui1_color;   //<M,R,Y,G,C,B,Flesh tone>
    UINT8 ui1_module;  //<Lina,Sat,Hue>
    UINT8 ui1_value;   //<0~0xFF>
}SCC_PQ_EXP_COLOR_GROUP_T[SCC_PQ_EXP_COLOR_NUMBER];
*/
INT32 a_cfg_cust_user_set_color_tuner_hsb(UINT8 ui1_main_item)
{
    INT32                    i4_ret = APP_CFGR_OK;
    UINT8                    ui1_x = 0;
    SCC_PQ_EXP_COLOR_GROUP_T t_data;
    INT16                    i2_value = 0;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    SIZE_T                  z_size = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_main_item :%d \r\n",ui1_main_item);

    if ((ui1_main_item > ACFG_COLOR_TUNER_SAT) || (ui1_main_item < ACFG_COLOR_TUNER_BRI))
    {
        DBG_ERROR(("[ACFG] ui1_main_item :%d, %s,%d\r\n",ui1_main_item,__FUNCTION__,__LINE__));
        return i4_ret;
    }

    c_memset(&t_data, 0, sizeof(SCC_PQ_EXP_COLOR_GROUP_T));

    for (ui1_x = ACFG_COLOR_TUNER_M; ui1_x <= ACFG_COLOR_TUNER_B; ui1_x++)
    {
        a_cfg_cust_get_color_tuner_items_value(ui1_main_item, ui1_x, &i2_value);
        t_data[ui1_x].ui1_color  = ui1_x;
        t_data[ui1_x].ui1_module = ui1_main_item;

        /* map data ap -50 ~ 50  to driver 0 ~ 100 */
        i2_value = i2_value + 50;

        if(i2_value < 0)
        {
            i2_value = 0;
        }

        if(i2_value > 100)
        {
            i2_value = 100;
        }

        t_data[ui1_x].ui1_value  = (UINT8)i2_value;

        ACFG_DBG_INFO("Set t_data[%d].ui1_value :%d \r\n",ui1_x,t_data[ui1_x].ui1_value);

    }

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_SET_COLOR_TUNER_HSB;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID*)(t_data);
    t_op_info.u.t_vid_set_info.z_size = sizeof(SCC_PQ_EXP_COLOR_GROUP_T);
    t_op_info.u.t_vid_set_info.b_store = FALSE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_size);

    return i4_ret;
}

INT32 a_cfg_cust_set_rgb_pattern(VOID* pv_data, SIZE_T z_size_val)
{
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T    t_set_info = {0};
    if(pv_data == NULL )
    {
        DBG_ERROR(("[ACFG] a_cfg_cust_set_rgb_pattern is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_RGB_PATTERN;
    t_set_info.pv_set_info = (VOID *)pv_data;
    t_set_info.z_size = z_size_val;
    t_set_info.b_store = TRUE;
    i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_set_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("%s : a_cfg_cust_set_rgb_pattern fail\n", __FUNCTION__));
        return i4_ret;
    }

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));

    return i4_ret;
}


INT32 a_cfg_cust_set_flat_pattern(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_FLAT_PATTERN;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_set_color_temp(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_COLOR_TEMP;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_drv_film_maker_mode(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;

    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_FILM_MAKER_MODE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_drv_Lcdim_Scrolling_OnOff(BOOL bOnOff)
{
    INT32             i4_ret = 0;
    UINT32            u4ScrollingParam;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_PRINT("Set bOnOff :%d \r\n",bOnOff);

    SIZE_T z_size = sizeof(UINT32);
    if (bOnOff == TRUE)
    {
        u4ScrollingParam = 0x10000FFF; // bit-0~3 light level, bit-7 on/off
    }
    else
    {
        u4ScrollingParam = 0x00000FFF; // bit-0~3 light level, bit-7 on/off
    }

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_LDM_SCROLLING_FUN;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&u4ScrollingParam;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

BOOL a_cfg_cust_drv_get_drv_game_mode_enable(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_GAME_MODE_STATUS;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if( i4_ret != RMR_OK )
    {
        DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} driver DRV_CUSTOM_CUST_SPEC_TYPE_GET_GAME_MODE_STATUS failed => Game_mode: off \n", __FUNCTION__,__LINE__));
        return FALSE;
    }

    ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} GET_GAME_MODE_STATUS => ui1_status: %d \n",
        __FUNCTION__,__LINE__, ui1_status)); );

    if( ui1_status == 1 )
    {
        ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} GET_GAME_MODE_STATUS => Game_mode: On \n", __FUNCTION__,__LINE__)); );
        return TRUE;
    }
    else
    {
        ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} GET_GAME_MODE_STATUS => Game_mode: Off \n", __FUNCTION__,__LINE__)); );
        return FALSE;
    }

    //return FALSE;
}

UINT8 a_cfg_cust_get_pqbypass_status(VOID)
{
    return ui1_g_pq_bypass;
}

INT32 a_cfg_cust_drv_set_pq_bypass(UINT8 ui1_idx)
{
    INT32                        i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    ui1_g_pq_bypass = ui1_idx;

    ACFG_DBG_PRINT("Set ui1_idx :%d,b_g_pq_bypass :%d,1:bypass pq, 0,not bypass pq \r\n",ui1_idx,ui1_g_pq_bypass);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
    ACFG_LOG_ON_FAIL(i4_ret);


    DBG_LOG_PRINT(("[ACFG][PQ]{%s,%d} Set driver(PQ_ALL_ONOFF) ui1_idx:%d \r\n", __FUNCTION__,__LINE__, ui1_idx));


    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_VID_PQ_ALL_ONOFF;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: a_cfg_cust_drv_set_pq_bypass_ex
 *
 * Description:will consider by whether by pass gamma
 *
 * Inputs:  -
 * typedef struct {
 *   BOOL   bEnable;
 *   UINT32  u4Val;
 * }   DRV_CUSTOM_PQ_BYPASS_T;
 *
 typedef enum
 {
     BYPASS_PQ_MODULE_HDR_IDX = 0,
     BYPASS_PQ_MODULE_TNR_IDX,
     BYPASS_PQ_MODULE_DI_FILM_IDX,
     BYPASS_PQ_MODULE_MPEGNR_IDX,
     BYPASS_PQ_MODULE_VIDEO_ENHANCE_IDX,
     BYPASS_PQ_RESOLUTION_ENHANCE_IDX,
     BYPASS_PQ_MODULE_CONSTRAST_ENHANCE_IDX,
     BYPASS_PQ_MODULE_COLOR_ENHANCE_IDX,
     BYPASS_PQ_MODULE_GAMUT_MAPPING_IDX,
     BYPASS_PQ_MODULE_PQ_GAMMA_IDX,
     BYPASS_PQ_MODULE_LOCALDIMING_IDX,
     BYPASS_PQ_MODULE_PANEL_IDX,
     BYPASS_PQ_MODULE_IDX_EXTERNAL_MAX,
     BYPASS_PQ_MODULE_ABF_IDX,
     BYPASS_PQ_MODULE_IDX_MAX
 }  BYPASS_PQ_MODULE_IDX;
 *  for BYPASS_PQ_MODULE_HDR_IDX : value = 2^0 = 1
 *  for BYPASS_PQ_MODULE_TNR_IDX : value = 2^1 = 2
 *  ....
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
INT32 a_cfg_cust_drv_set_pq_bypass_ex(VOID* pv_data, SIZE_T z_size_val)
{
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T    t_set_info = {0};
    if(pv_data == NULL )
    {
        ACFG_DBG_ERROR(" pv_data == NULL \r\n");
        return APP_CFGR_INTERNAL_ERR;
    }
    ACFG_DBG_PRINT("Enter \r\n");
    DRV_CUSTOM_PQ_BYPASS_T *ptInfo = (DRV_CUSTOM_PQ_BYPASS_T *)pv_data;

    ui1_g_pq_bypass = 0;
    if(ptInfo->bEnable)
    {
        ui1_g_pq_bypass = 1;
    }
    a_cfg_cust_set_full_color_444_ForCurHDMI(ui1_g_pq_bypass);
    ACFG_DBG_PRINT("Set b_g_pq_bypass :%d,1:bypass pq, 0,not bypass pq \r\n",ui1_g_pq_bypass);

    /* On/Off color 444*/
    i4_ret = a_cfg_av_update( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_FULL_COLOR_444) );
    ACFG_LOG_ON_FAIL(i4_ret);

    /* active full array set off when bypass on */
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
    ACFG_LOG_ON_FAIL(i4_ret);

    /*Brightness / contrast/ color/ tint /  set mid value when bypass on */
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT));
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE));
    ACFG_LOG_ON_FAIL(i4_ret);

    t_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_VID_PQ_BYPASS;
    t_set_info.pv_set_info = (VOID *)pv_data;
    t_set_info.z_size = z_size_val;
    t_set_info.b_store = TRUE;
    i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_set_info);
    if (i4_ret != APP_CFGR_OK)
    {
        ACFG_DBG_ERROR("a_cfg_set_drv_comp :i4_ret:%d \r\n",i4_ret);
        return i4_ret;
    }

    return i4_ret;
}

INT32 a_cfg_cust_get_yuv_data(VOID* pv_s_data, SIZE_T z_s_size_val,VOID* pv_g_data, SIZE_T z_g_size_val)
{
    ACFG_DBG_INFO("Enter");
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T    t_set_info = {0};
    CUST_SPEC_TYPE_GET_INFO_T    t_get_info = {0};

    if(pv_s_data == NULL || pv_g_data == NULL )
    {
        DBG_ERROR(("[ACFG] a_cfg_cust_get_yuv_data is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_SET_GAMMA_X_Y;
    t_set_info.pv_set_info = (VOID *)pv_s_data;
    t_set_info.z_size = z_s_size_val;
    t_set_info.b_store = TRUE;
    i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_set_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("%s : DRV_CUSTOM_CUST_SPEC_SET_GAMMA_X_Y fail\n", __FUNCTION__));
        return i4_ret;
    }

    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_YUV_DATA;
    t_get_info.pv_get_info = (VOID *)pv_g_data;
    t_get_info.pz_size = &z_g_size_val;
    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("%s : DRV_CUSTOM_CUST_SPEC_TYPE_GET_YUV_DATA fail\n", __FUNCTION__));
        return i4_ret;
    }

    return APP_CFGR_OK;
}

INT32 a_cfg_cust_get_rgb_output_status(UINT16 ui2_x_pos, UINT16 ui2_y_pos, UINT16 *pui2_RGB)
{
    INT32 i4_ret = 0;
    UINT16 ui2_data[5] = {0};
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(ui2_data);

    ui2_data[0] = ui2_x_pos;
    ui2_data[1] = ui2_y_pos;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_DRV_RGB_OUPTUT_STATUS;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)ui2_data;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
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

    *pui2_RGB = ui2_data[2];
    *(pui2_RGB+1) = ui2_data[3];
    *(pui2_RGB+2) = ui2_data[4];

    return RMR_OK;
}

INT32 a_cfg_cust_drv_get_panel_nits_addr(UINT32 *pui4_addr)
{
    INT32                       i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T   t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size = sizeof(UINT32);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDR_PANEL_NITS;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_addr;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        ACFG_DBG_ERROR("i4_ret :%d \r\n",i4_ret);
        return i4_ret;
    }

    ACFG_DBG_INFO("Enter pui4_addr :0x%x \r\n",*pui4_addr);

    return i4_ret;
}

INT32 a_cfg_cust_drv_read_panel_nits(UINT16 *ui2_panel_nits)
{
    UINT32   ui4_addr = 0;
    UINT8    aui1_val[6] = {0};
    UINT32   ui4_read = 0;
    INT32    i4_ret = 0;
    INT16    i2_val = 0;
    UINT16   ui2_idx = 0;
    UINT8    ui1_odm_id = 0;

    a_cfg_cust_drv_get_panel_nits_addr(&ui4_addr);
    i4_ret = a_cfg_eep_raw_read(ui4_addr, aui1_val, 6, &ui4_read);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    if(i2_val == ACFG_CUST_CLR_TEMP_WARM)
    {
        ui2_idx = aui1_val[1];
        ui2_idx = ui2_idx << 8 |aui1_val[0];
    }
    else if (i2_val == ACFG_CUST_CLR_TEMP_COOL)
    {
        ui2_idx = aui1_val[3];
        ui2_idx = ui2_idx << 8 |aui1_val[2];
    }
    else if (i2_val == ACFG_CUST_CLR_TEMP_NORMAL)
    {
        ui2_idx = aui1_val[5];
        ui2_idx = ui2_idx << 8 |aui1_val[4];
    }
    else
    {
        ui2_idx = 0;
    }

    //set default value 300 if current data is 0
    if(ui2_idx == 0)
    {
        i4_ret = a_cfg_custom_get_odm_idx(&ui1_odm_id);
        ACFG_LOG_ON_FAIL(i4_ret);

        if(ui1_odm_id == ODM_ID_TPV) // only for TPV
        {
            i4_ret = acfg_cust_odm_current_default_hdr_panel_nits(&ui2_idx);
            ACFG_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            ui2_idx = 300;
        }
    }

    *ui2_panel_nits = ui2_idx;

    ACFG_DBG_INFO(" *ui4_addr 0x:%x \r\n",ui4_addr);
    ACFG_DBG_INFO(" *ui2_panel_nits :%d \r\n",*ui2_panel_nits);

    return i4_ret;
}

INT32 a_cfg_cust_drv_write_panel_nits(UINT16 ui2_panel_nits, UINT8 ui1_col_tmp)
{
    UINT32   ui4_addr = 0;
    UINT8    aui1_val[2] = {0};
    UINT32   ui4_write = 0;
    INT32    i4_ret = 0;

    i4_ret = a_cfg_cust_drv_get_panel_nits_addr(&ui4_addr);
    ACFG_LOG_ON_FAIL(i4_ret);

    aui1_val[0] = ui2_panel_nits&0x00ff;
    aui1_val[1] = (ui2_panel_nits&0xff00) >> 8;

    if(ui1_col_tmp == ACFG_CUST_CLR_TEMP_WARM)
    {
        i4_ret = a_cfg_eep_raw_write(ui4_addr, aui1_val, 2, &ui4_write);
    }
    else if (ui1_col_tmp == ACFG_CUST_CLR_TEMP_COOL)
    {
        i4_ret = a_cfg_eep_raw_write(ui4_addr+2, aui1_val, 2, &ui4_write);
    }
    else if (ui1_col_tmp == ACFG_CUST_CLR_TEMP_NORMAL)
    {
        i4_ret = a_cfg_eep_raw_write(ui4_addr+4, aui1_val, 2, &ui4_write);
    }

    ACFG_DBG_PRINT(" *ui4_addr 0x:%x \r\n",ui4_addr);
    ACFG_DBG_PRINT(" *ui2_panel_nits :%d \r\n",ui2_panel_nits);

    ACFG_DBG_PRINT(" *aui1_val[0] :%d \r\n",aui1_val[0]);
    ACFG_DBG_PRINT(" *aui1_val[1] :%d \r\n",aui1_val[1]);
    return i4_ret;
}


INT32 a_cfg_cust_drv_update_panel_nits(VOID)
{
    INT32    i4_ret = 0;
    UINT16   ui2_val = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Enter \r\n");

    SIZE_T z_size = sizeof(ui2_val);

    i4_ret = a_cfg_cust_drv_read_panel_nits(&ui2_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    ACFG_DBG_PRINT(" ui2_val :%d \r\n",ui2_val);
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_PANEL_NITS_BY_CT;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_val;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}


BOOL a_cfg_cust_drv_get_memc_enable(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_IS_MEMC_ENABLE;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if((ui1_status == 1)&&(i4_ret == RMR_OK))
    {
        return TRUE;
    }
    ACFG_DBG_INFO("Get ui1_status :%d \r\n",ui1_status);

    return FALSE;

}

BOOL a_cfg_cust_drv_get_4k_source(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_IS_4K_SOURCE;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if((ui1_status == 1)&&(i4_ret == RMR_OK))
    {
        return TRUE;
    }
    ACFG_DBG_INFO("Get ui1_status :%d \r\n",ui1_status);

    return FALSE;

}

INT32 a_cfg_cust_drv_get_RJ45_addr(UINT32 *pui4_addr)
{
    INT32                       i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T   t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size = sizeof(UINT32);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_RJ45_ADDR;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_addr;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        ACFG_DBG_ERROR("i4_ret :%d \r\n",i4_ret);
        return i4_ret;
    }

    ACFG_DBG_PRINT("Enter pui4_addr :0x%x \r\n",*pui4_addr);

    return i4_ret;
}

INT32 a_cfg_cust_drv_read_RJ45_value(UINT8 *aui1_val)
{
    UINT32   ui4_addr = 0;
    UINT32   ui4_read = 0;
    INT32    i4_ret = 0;
    UINT8    ui1_idx = 0;

    a_cfg_cust_drv_get_RJ45_addr(&ui4_addr);
    i4_ret = a_cfg_eep_raw_read(ui4_addr, aui1_val, 6, &ui4_read);
    ACFG_LOG_ON_FAIL(i4_ret);

    ACFG_DBG_PRINT(" *ui4_addr 0x:%x \r\n",ui4_addr);

    for(ui1_idx = 0; ui1_idx < 6;ui1_idx++)
    {
        ACFG_DBG_PRINT(" *aui1_val[%d] :%d \r\n",ui1_idx,aui1_val[ui1_idx]);
    }

    return i4_ret;
}

INT32 a_cfg_cust_drv_write_RJ45_value(UINT8* aui1_val)
{
    UINT32   ui4_addr = 0;
    UINT32   ui4_write = 0;
    INT32    i4_ret = 0;
    UINT8    ui1_idx = 0;

    i4_ret = a_cfg_cust_drv_get_RJ45_addr(&ui4_addr);
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_eep_raw_write(ui4_addr, aui1_val, 6, &ui4_write);

    ACFG_DBG_PRINT(" *ui4_addr 0x:%x \r\n",ui4_addr);

    for(ui1_idx = 0; ui1_idx < 6;ui1_idx++)
    {
        ACFG_DBG_PRINT(" *aui1_val[%d] :%d \r\n",ui1_idx,aui1_val[ui1_idx]);
    }

    return i4_ret;
}

INT32 a_cfg_cust_drv_update_eth0_mac(VOID)
{
    INT32    i4_ret = 0;
    UINT8    aui1_val[6] = {0};
    CHAR     s_rj45_mac_str[18] = {0};

    ACFG_DBG_INFO("Enter \r\n");

    i4_ret = a_cfg_cust_drv_read_RJ45_value(aui1_val);
    ACFG_LOG_ON_FAIL(i4_ret);

    c_sprintf(s_rj45_mac_str,"%02X:%02X:%02X:%02X:%02X:%02X\0",aui1_val[0],
                                                                aui1_val[1],
                                                                aui1_val[2],
                                                                aui1_val[3],
                                                                aui1_val[4],
                                                                aui1_val[5]);
    ACFG_DBG_PRINT("  s_rj45_mac_str :%s \r\n",s_rj45_mac_str);

    i4_ret = a_nw_save_mac_addr_string("eth0", s_rj45_mac_str);

    return i4_ret;
}

// Why not use "BOOL a_cfg_custom_odm_is_lightsensor_support(VOID)"??
// 2021-08-18: MVS-360: 5695s 2022-K all model should support lightsensor
//
// 2020/11/13: The "Ambient Light Sensor" option should not appear on V706-J03.
//
// Spec 3.1:
//  Support: (M7/8, P9/X, OLED)
//  Not support: Ambient light sensor does not apply to D, V or M6 skus
//
// Spec 2.0:
//  supportL M,P,OLED
BOOL a_cfg_cust_drv_is_lightsensor_support(VOID)
{
#if( defined(MT5695_MODEL)&&defined(MT5695_FAMILY_S) )

    // 2021-08-18: There are only these model:
    // TPV: M9
    // FOXCONN: M9
    // BOE: PX
    return TRUE;

#else
    CHAR   s_name[32] = {0};
    INT32  i4_ret  = 0;
    BOOL   is_support = FALSE; // Change Default=false

    i4_ret = a_cfg_custom_get_model_name(s_name);
    ACFG_LOG_ON_FAIL(i4_ret);

    // Test model_name
    //c_strcpy(s_name, "V706-J03");
    //DBG_LOG_PRINT(("%s: %d: s_name=%s\n",__FUNCTION__,__LINE__, s_name));

    BOOL bIs_after_2021_Model = a_cfg_cust_Is_CurModel_after_2021_J();

    BOOL bIsOLEDModel = a_cfg_cust_Is_CurModel_OLED(); //  : OLED Panel


    if( bIs_after_2021_Model )
    {
        if( bIsOLEDModel )
        {
            is_support = TRUE;
        }
        else
        {
            switch( s_name[0] )
            {
                case 'D':
                    // Dxxf4-J01 not support
                    // All D model not support
                    {
                        is_support =  FALSE;
                    }
                break;

                case 'M':
                    // M6 not support...
                    if( (s_name[4] == '7') ) // M7: Mxxx7-J
                    {
                        is_support =  TRUE;
                    }
                    else if( (s_name[4] == '8') ) // M8: Mxxx8-J
                    {
                        is_support =  TRUE;
                    }
                    break;

                case 'P':
                    is_support = TRUE;
                    break;

                case 'V':
                    // [Vizio][MVV-7127][Release1.1][2021][FXN][V706-J03]
                    // The "Ambient Light Sensor" option should not appear on V706-J03.

                    // V6 not support...
                    if( (s_name[3] == '6') ) // Check if name is "Vxx6-J"
                    {
                        //DBG_LOG_PRINT(("[LightSensor] %s: %d: Vxx6 not support lightsensor\n",__FUNCTION__,__LINE__));
                        is_support =  FALSE;
                    }

                    // V5 not support ...
                    if( (s_name[3] == '5') ) // V5: Vxx5-J
                    {
                        is_support =  FALSE;
                    }

                    break;

                default:
                    break;
            }
        }

    }
    else // 2020
    {
        // "-H" => 2020
        if( bIsOLEDModel )
        {
            is_support = TRUE;
        }
        else
        {
            switch( s_name[0] )
            {
                case 'M':
                    // Mxx6-xx not support
                    if( (s_name[3] == '6')||(s_name[4] == '6') )
                    {
                        is_support =  FALSE;
                    }
                    else // For M5/M7 case
                    {
                        is_support = TRUE;
                    }
                    break;

                case 'P':
                    is_support = TRUE;
                    break;

                case 'V':
                    // V6 not support...
                    if( (s_name[3] == '6') ) // Check if name is "Vxx6"
                    {
                        //DBG_LOG_PRINT(("[LightSensor] %s: %d: Vxx6 not support lightsensor\n",__FUNCTION__,__LINE__));
                        is_support =  FALSE;
                    }

                    // V5 not support ...
                    //if((s_name[0] == 'V') && (c_strstr(s_name,"5")!= NULL))
                    if( (s_name[3] == '5') )
                    {
                        is_support =  FALSE;
                    }
                    break;

                default:
                    break;
            }
        }
    }

    return  is_support;
#endif
}

INT32 a_cfg_cust_drv_set_vcom_pattern(VOID* pv_data, SIZE_T z_size_val)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T t_op_info;

    if(pv_data == NULL )
    {
        ACFG_DBG_PRINT(" pv_data == NULL ");
        return APP_CFGR_INTERNAL_ERR;
    }

    c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_VCOM_PATTERN;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)pv_data;
    t_op_info.u.t_vid_set_info.z_size = z_size_val;
    t_op_info.u.t_vid_set_info.b_store = TRUE;

    /*set value to driver*/
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T)
                            );
    ACFG_LOG_ON_FAIL(i4_ret);
    ACFG_DBG_PRINT("Return i4_ret :%d \r\n",i4_ret);

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_mod_pattern(VOID* pv_data, SIZE_T z_size_val)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T t_op_info;

    if(pv_data == NULL )
    {
        ACFG_DBG_PRINT(" pv_data == NULL ");
        return APP_CFGR_INTERNAL_ERR;
    }

    c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_MOD_PATTERN;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)pv_data;
    t_op_info.u.t_vid_set_info.z_size = z_size_val;
    t_op_info.u.t_vid_set_info.b_store = TRUE;

    /*set value to driver*/
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T)
                            );
    ACFG_LOG_ON_FAIL(i4_ret);
    ACFG_DBG_PRINT("Return i4_ret :%d \r\n",i4_ret);

    return i4_ret;
}

/* OLED related API start*/
/*  OFF RS*/
INT32 a_cfg_cust_drv_set_oled_off_rs(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_OFF_RS;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

BOOL a_cfg_cust_drv_get_oled_off_rs(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_OFF_RS;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if((ui1_status == 1)&&(i4_ret == RMR_OK))
    {
        return TRUE;
    }
    ACFG_DBG_INFO("Get ui1_status :%d \r\n",ui1_status);

    return FALSE;

}

/* get off rs jb status*/
BOOL a_cfg_cust_drv_get_oled_off_rs_jb_status(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_OFFRS_JB_STATUS;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if((ui1_status == 1)&&(i4_ret == RMR_OK))
    {
        return TRUE;
    }
    DBG_INFO(("Get ui1_status :%d \r\n",ui1_status));

    return FALSE;

}

/* get on-rf status*/
BOOL a_cfg_cust_drv_get_oled_on_rf_status(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_ON_RF_STATUS;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if((ui1_status == 1)&&(i4_ret == RMR_OK))
    {
        return TRUE;
    }
    ACFG_DBG_INFO("Get ui1_status :%d \r\n",ui1_status);

    return FALSE;
}


/*  JB */
INT32 a_cfg_cust_drv_set_oled_jb(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_JB;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

BOOL a_cfg_cust_drv_get_oled_jb(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_JB;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if((ui1_status == 1)&&(i4_ret == RMR_OK))
    {
        return TRUE;
    }
    ACFG_DBG_INFO("Get ui1_status :%d \r\n",ui1_status);

    return FALSE;

}

/*  LEA*/
INT32 a_cfg_cust_drv_set_oled_lea(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_LEA;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

BOOL a_cfg_cust_drv_get_oled_lea(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_LEA;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if((ui1_status == 1)&&(i4_ret == RMR_OK))
    {
        return TRUE;
    }
    ACFG_DBG_INFO("Get ui1_status :%d \r\n",ui1_status);

    return FALSE;

}

/*  TPC */
INT32 a_cfg_cust_drv_set_oled_tpc(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_TPC;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

BOOL a_cfg_cust_drv_get_oled_tpc(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_TPC;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if((ui1_status == 1)&&(i4_ret == RMR_OK))
    {
        return TRUE;
    }
    ACFG_DBG_INFO("Get ui1_status :%d \r\n",ui1_status);

    return FALSE;

}

/*  CPC*/
INT32 a_cfg_cust_drv_set_oled_cpc(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_CPC;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

BOOL a_cfg_cust_drv_get_oled_cpc(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_CPC;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if((ui1_status == 1)&&(i4_ret == RMR_OK))
    {
        return TRUE;
    }
    ACFG_DBG_INFO("Get ui1_status :%d \r\n",ui1_status);

    return FALSE;

}

/*  HDR*/
INT32 a_cfg_cust_drv_set_oled_hdr(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_HDR;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

BOOL a_cfg_cust_drv_get_oled_hdr(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_HDR;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if((ui1_status == 1)&&(i4_ret == RMR_OK))
    {
        return TRUE;
    }
    ACFG_DBG_INFO("Get ui1_status :%d \r\n",ui1_status);

    return FALSE;

}

/*  CMO*/
INT32 a_cfg_cust_drv_set_oled_cmo(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_CMO;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

BOOL a_cfg_cust_drv_get_oled_cmo(VOID)
{
    INT32                        i4_ret     = 0;
    UINT8                        ui1_status = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(UINT8);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_CMO;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)&ui1_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);

    if((ui1_status == 1)&&(i4_ret == RMR_OK))
    {
        return TRUE;
    }
    ACFG_DBG_INFO("Get ui1_status :%d \r\n",ui1_status);

    return FALSE;

}

/*  PLC CURVE*/
INT32 a_cfg_cust_drv_set_oled_plc_curve(VOID* pv_data, SIZE_T z_size_val)
{
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T    t_set_info = {0};
    if(pv_data == NULL )
    {
        DBG_ERROR(("[ACFG] a_cfg_cust_drv_set_oled_plc_curve is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_PLC_CURVE;
    t_set_info.pv_set_info = (VOID *)pv_data;
    t_set_info.z_size = z_size_val;
    t_set_info.b_store = TRUE;
    i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_set_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("%s : a_cfg_cust_drv_set_oled_plc_curve fail\n", __FUNCTION__));
        return i4_ret;
    }

    return i4_ret;
}

INT32 a_cfg_cust_drv_get_oled_plc_curve(VOID* pv_data, SIZE_T z_size_val)
{
    DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};

    if(pv_data == NULL)
    {
        DBG_ERROR(("[ACFG] a_cfg_cust_drv_get_oled_plc_curve is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }


    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_PLC_CURVE;
    t_get_info.pv_get_info = (VOID *)pv_data;
    t_get_info.pz_size = &z_size_val;
    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("%s : a_cfg_cust_drv_get_oled_plc_curve fail\n", __FUNCTION__));
        return i4_ret;
    }
    return APP_CFGR_OK;
}

BOOL a_cfg_cust_CheckIfPeakLumiCanAdjust(void)
{
#if 0
    UINT8 u8HdmiPortIdx = acfg_cust_get_CurSrcHdmi_UI_Idx();

    // Is HDMI source
    if( u8HdmiPortIdx < HDMI_PORT_NUM_MAX )
    {
        UINT8 u8HdrType = a_acfg_cust_get_video_type();
        if( u8HdrType != ACFG_CUST_CONTENT_SDR ) // Is HDR mode
        {
            return FALSE;
        }
    }
#endif

    return TRUE;
}

/**/
INT32 a_cfg_cust_drv_set_oled_panel_gain(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);


    DBG_LOG_PRINT(("[ACFG][OLED][BACKLIGHT][LUMI]{%s: %d} Call scc( DRV_CUSTOM_CUST_SPEC_TYPE_OLED_PLC_GAIN, ui1_idx = %d\n",
                                        __FUNCTION__, __LINE__, ui1_idx ));


    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_PLC_GAIN;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

/* TEMPERATURE */
INT32 a_cfg_cust_drv_get_oled_temperature(UINT8 ui1_idx,UINT32 *pui4_val)
{
    INT32                       i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T   t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size = sizeof(UINT32);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    if(ui1_idx == 0)
    {
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_TEMPERATURE_0;
    }
    else if(ui1_idx == 1)
    {
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_TEMPERATURE_1;
    }
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_val;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        ACFG_DBG_ERROR("i4_ret :%d \r\n",i4_ret);
        return i4_ret;
    }

    ACFG_DBG_PRINT("Enter pui4_val :0x%x \r\n",*pui4_val);

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_oled_pixel_shift(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;

    ACFG_DBG_PRINT(" Set ui1_idx :%d \r\n",ui1_idx);
    if(a_cfg_cust_oled_support() == FALSE)
    {
        return i4_ret;
    }

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_oled_orbit(BOOL b_en)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    DRV_CUSTOM_OLED_ORBIT_T      t_info;

    c_memset(&t_info, 0, sizeof(DRV_CUSTOM_OLED_ORBIT_T));
    ACFG_DBG_PRINT("Set b_en :%d \r\n",b_en);

    if(a_cfg_cust_oled_support() == FALSE)
    {
        ACFG_DBG_INFO("NOT Support oled orbit \r\n");
        return i4_ret;
    }

    SIZE_T z_size = sizeof(DRV_CUSTOM_OLED_ORBIT_T);

    t_info.bEnable = b_en;
    t_info.u1OledOrbitType = 2;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_ORBIT;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&t_info;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_drv_get_oled_support_compensation(UINT32 *pui4_val)
{
    INT32                       i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T   t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size = sizeof(UINT32);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_SUPPORT_COMPENSATION;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_val;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        ACFG_DBG_ERROR("i4_ret :%d \r\n",i4_ret);
        return i4_ret;
    }

    //ACFG_DBG_PRINT("Enter pui4_val :0x%x \r\n",*pui4_val);

    return i4_ret;
}

INT32 a_cfg_cust_drv_get_oled_display_total(UINT32 *pui4_val)
{
    INT32                       i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T   t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size = sizeof(UINT32);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_DISPALY_TOTAL;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_val;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        ACFG_DBG_ERROR("i4_ret :%d \r\n",i4_ret);
        return i4_ret;
    }

    ACFG_DBG_PRINT("Enter pui4_val :0x%x \r\n",*pui4_val);

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_oled_display_time(UINT32 ui4_display_time)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size     = sizeof(ui4_display_time);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_EEPROM_PANEL_DISPLAY_TIME;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui4_display_time;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );

    return i4_ret;
}

INT32 a_cfg_cust_drv_get_oled_display_time(UINT32* pui4_display_time)
{
    INT32                       i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T   t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size = sizeof(UINT32);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_EEPROM_PANEL_DISPLAY_TIME;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_display_time;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
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
        ACFG_DBG_ERROR("i4_ret :%d \r\n",i4_ret);
        return i4_ret;
    }

    return i4_ret;
}


INT32 a_cfg_cust_drv_get_oled_display_period(UINT32 *pui4_val)
{
    INT32                       i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T   t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size = sizeof(UINT32);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_DISPALY_PREIOD;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_val;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        ACFG_DBG_ERROR("i4_ret :%d \r\n",i4_ret);
        return i4_ret;
    }

    ACFG_DBG_PRINT("Enter pui4_val :0x%x \r\n",*pui4_val);

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_oled_mute(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_MUTE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_drv_set_oled_panel_power_reset(UINT8 ui1_value)
{
    INT32                       i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T   t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                      z_size = sizeof(ui1_value);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_OLED_PWR_RESET;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_value;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* get from driver */
    i4_ret = c_rm_set_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        ACFG_DBG_ERROR("i4_ret :%d \r\n",i4_ret);
        return i4_ret;
    }

    return i4_ret;
}


/* OLED related API end*/

INT32 a_cfg_cust_set_sif_data(VOID* pv_data, SIZE_T z_size_val)
{
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T    t_set_info = {0};
    if(pv_data == NULL )
    {
        DBG_ERROR(("[ACFG] a_cfg_cust_set_sif_data is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_set_info.e_cust_spec_type = DRV_CUSTOM_OPERATION_TYPE_SIF_WRITE;
    t_set_info.pv_set_info = (VOID *)pv_data;
    t_set_info.z_size = z_size_val;
    t_set_info.b_store = TRUE;
    i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_set_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("%s : a_cfg_cust_set_sif_data fail\n", __FUNCTION__));
        return i4_ret;
    }

    return i4_ret;
}

INT32 a_cfg_cust_get_sif_data(VOID* pv_data, SIZE_T z_size_val)
{
    DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};

    if(pv_data == NULL)
    {
        DBG_ERROR(("[ACFG] a_cfg_cust_get_sif_data is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_get_info.e_cust_spec_type = DRV_CUSTOM_OPERATION_TYPE_SIF_READ;
    t_get_info.pv_get_info = (VOID *)pv_data;
    t_get_info.pz_size = &z_size_val;
    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("%s : a_cfg_cust_get_sif_data fail\n", __FUNCTION__));
        return i4_ret;
    }
    return APP_CFGR_OK;
}

INT32 a_cfg_cust_update_hdcp(VOID)
{
    INT32                        i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT8                        ui1_idx =0;
    ACFG_DBG_INFO("Set ui1_idx :%d \r\n",ui1_idx);

    SIZE_T z_size = sizeof(ui1_idx);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_UPDATE_HDCP;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}


extern BOOL a_slogo_is_show(void);

INT32 a_cfg_cust_update_local_dimming(VOID)
{
    UINT16 i2_val = 0;
    INT32  i4_ret = 0;

    if(a_cfg_cust_get_support_local_dimming() == FALSE)
    {
        return APP_CFGR_OK;
    }

    if( ui1_g_pq_bypass == 1)
    {
        ACFG_DBG_INFO(" ui1_g_pq_bypass :%d \r\n",ui1_g_pq_bypass);
        i4_ret = VIZIO_EXTREME_BLACK_ENGINE_D_SET((UINT16)0);
        ACFG_LOG_ON_FAIL(i4_ret);
        return APP_CFGR_OK;
    }

#ifdef APP_CFG_DIMMING_OFF_IN_EMANUAL
    UINT8   ui1_val   = ICL_EMANUAL_STATUS_OFF;
    SIZE_T  z_size    = ICL_RECID_EMANUAL_STATUS_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_EMANUAL_STATUS, ICL_RECID_EMANUAL_STATUS),
                       &ui1_val, &z_size);
    ACFG_DBG_INFO(" ui1_val :%d ,i4_ret :%d \r\n",ui1_val,i4_ret);
    if ((i4_ret==APP_CFGR_OK)&&(ui1_val == ICL_EMANUAL_STATUS_ON))
    {
        return APP_CFGR_OK;
    }
#endif

    i4_ret = a_cfg_custom_get_dimming_idx(&i2_val);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    if(a_wzd_is_oobe_mode() == TRUE)
    {
        i4_ret = VIZIO_EXTREME_BLACK_ENGINE_D_SET((UINT16)0);
        ACFG_LOG_ON_FAIL(i4_ret);
    }
    else if (a_slogo_is_show() == TRUE && !b_slogo_forced_update_ld)
    {
        ACFG_DBG_INFO("Show logo, bypass local dimming.\n");
        i4_ret = VIZIO_EXTREME_BLACK_ENGINE_D_SET((UINT16)0);
        b_slogo_forced_update_ld = FALSE;
        ACFG_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = VIZIO_EXTREME_BLACK_ENGINE_D_SET((UINT16)i2_val);
        ACFG_LOG_ON_FAIL(i4_ret);
    }

    return APP_CFGR_OK;
}

UINT8 a_acfg_cust_get_video_type(VOID)
{
    UINT8              ui1_type = ACFG_CUST_CONTENT_SDR;
    INT32              i4_dv    = 0;

    ui1_type = (UINT8)a_cfg_get_hdr_type();

    i4_dv = a_icl_custom_get_dolby_vision_status();
    if(i4_dv == 1)
    {
        ui1_type = SCC_VID_PQ_DOVI;
    }

    return ui1_type;
}

UINT8 a_acfg_cust_get_dynamic_range(VOID)
{
    UINT8 ui1_type = a_acfg_cust_get_video_type();

    if((ui1_type == SCC_VID_PQ_HDR10 )|| (ui1_type == SCC_VID_PQ_HDR10PLUS))
    {
        ui1_type = ACFG_CUST_CONTENT_HDR;
    }
    else if (ui1_type == SCC_VID_PQ_HLG )
    {
        ui1_type = ACFG_CUST_CONTENT_HLG;
    }
    else if (ui1_type == SCC_VID_PQ_DOVI )
    {
        ui1_type = ACFG_CUST_CONTENT_DV;
    }
    else
    {
        ui1_type = ACFG_CUST_CONTENT_SDR;
    }

    ACFG_DBG_INFO(" ui1_type :%d \r\n",ui1_type);
    return ui1_type;
}

BOOL a_acfg_cust_is_gll_enable(VOID)
{
    if ( a_cfg_cust_is_support_game_low_latency() == FALSE )
    {
        return FALSE;
    }

    if (a_cfg_cust_drv_get_drv_game_mode_enable() == TRUE)
    {
        return TRUE;
    }

#if( VZO_DV__GLL_CONTROL_BY_DV_GAME )
    if( a_cfg_get_hdr_type() == SCC_VID_PQ_DOVI )
    {
        if( APP_CFG_VID_GAME_MODE_OFF == a_cfg_cust_get_cur_dv_game_mode_flag() )
        {
            ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][DV][GAME][GLL]{%s, %d} DV(non-Game) => GLL is OFF\n", __FUNCTION__,__LINE__)); );
            return FALSE;
        }
        else // DV Game
        {
            ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][DV][GAME][GLL]{%s, %d} DV(Game) => GLL is ON\n", __FUNCTION__,__LINE__)); );
            return TRUE;
        }
    }
#endif


    INT16  i2_gll = ACFG_CUST_GAME_LOW_LATENCY_AUTO;
    INT32  i4_ret  = 0;


    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i2_gll);
    //ACFG_LOG_ON_FAIL(i4_ret);
    if(i4_ret < 0)
    {
        //DBG_ERROR(("<ACFG> Return fail:%d\r\n", _ret));
        DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s, %d} Error: Get GLL setting fail! i4_ret:%d\n", __FUNCTION__,__LINE__, i4_ret ));
        return FALSE;
    }

    if (i2_gll == ACFG_CUST_GAME_LOW_LATENCY_AUTO && a_cfg_cust_drv_get_allm_status() == TRUE)
    {
        return TRUE;
    }

    if (i2_gll == ACFG_CUST_GAME_LOW_LATENCY_ON)
    {
        return TRUE;
    }

    return FALSE;
}

INT32 a_cfg_cust_info_get_gamma_table_ini_path(CHAR * ps_str)
{
    INT32       i4_ret       = 0;
    UINT8       ui1_odm_id   = 0;
    UINT32      ui4_group_id = 0;
    UINT32      ui4_model_id = 0;
    CHAR        s_str[MI_INI_FILE_PATH_LEN+1] = {0};
    CHAR        s_tmp[20]                     = {0};
    CHAR        s_panel_name[64]              = {0};

    i4_ret = a_cfg_custom_get_odm_idx(&ui1_odm_id);
    ACFG_LOG_ON_FAIL(i4_ret);
    DBG_INFO(("[ACFG] ui1_odm_id:%d,%s,%d\r\n",ui1_odm_id,__FUNCTION__,__LINE__));

    i4_ret = a_cfg_custom_get_model_group_id(&ui4_group_id);
    ACFG_LOG_ON_FAIL(i4_ret);
    DBG_INFO(("[ACFG] ui4_group_id:0x%x,%s,%d\r\n",ui4_group_id,__FUNCTION__,__LINE__));

    i4_ret = a_cfg_custom_get_model_idx(&ui4_model_id);
    ACFG_LOG_ON_FAIL(i4_ret);
    DBG_INFO(("[ACFG] ui4_model_id:%d,%s,%d\r\n",ui4_model_id,__FUNCTION__,__LINE__));

    i4_ret = a_cfg_custom_get_panel_name(s_panel_name);
    ACFG_LOG_ON_FAIL(i4_ret);
    DBG_INFO(("[ACFG] s_panel_name:%s,%s,%d\r\n",s_panel_name,__FUNCTION__,__LINE__));

    switch(ui1_odm_id)
    {
        case ODM_ID_Amtran:
        {
            c_strncpy(s_str,"/config/amtran/",MI_INI_FILE_PATH_LEN);
        }
        break;

        case ODM_ID_TPV:
        {
            c_strncpy(s_str,"/config/tpv/",MI_INI_FILE_PATH_LEN);
        }
        break;

        case ODM_ID_Wistron:
        {
            c_strncpy(s_str,"/config/wst/",MI_INI_FILE_PATH_LEN);
        }
        break;

        case ODM_ID_Foxconn:
        {
            c_strncpy(s_str,"/config/foxconn/",MI_INI_FILE_PATH_LEN);
        }
        break;

        case ODM_ID_BOE:
        {
            c_strncpy(s_str,"/config/boe/",MI_INI_FILE_PATH_LEN);
        }
        break;

        case ODM_ID_Innolux:
        {
            c_strncpy(s_str,"/config/innolux/",MI_INI_FILE_PATH_LEN);

        }
        break;

        default:
            break;
    }


    c_sprintf(s_tmp,"ModelGroup%x/",ui4_group_id);
    c_strncat(s_str,s_tmp,MI_INI_FILE_PATH_LEN);

    c_sprintf(s_tmp,"ModelIndex%x/panel/",ui4_model_id);
    c_strncat(s_str,s_tmp,MI_INI_FILE_PATH_LEN);

    //c_strncat(s_str,"ModelGroup192/",MI_INI_FILE_PATH_LEN);
    //c_strncat(s_str,"ModelIndex1/",MI_INI_FILE_PATH_LEN);

    c_strncat(s_str,s_panel_name,MI_INI_FILE_PATH_LEN);
    c_strncat(s_str,".ini",MI_INI_FILE_PATH_LEN);
    DBG_INFO(("[ACFG] s_str:%s, %s,%d\r\n",s_str,__FUNCTION__,__LINE__));

    c_strncpy(ps_str,s_str,MI_INI_FILE_PATH_LEN);

    return APP_CFGR_OK;
}


INT32 a_cfg_cust_info_get_gamma_table_from_ini(INT8 i1_idx,ACFG_GAMMA_TABLE_T* pt_gamma_info)
{
    CHAR                    s_file_path[MI_INI_FILE_PATH_LEN+1] = {0};
    INT32                   i4_ret = 0;
    MI_HANDLE               h_acfg_ini = NULL_HANDLE;
    MI_SYS_ConfigData_t     t_ini_data;
    CHAR*                   pc_data = NULL;
    CHAR*                   pc_str = NULL;
    INT16                   i2_data = 0;
    UINT16                  ui2_idx = 0;
    UINT8                   ui1_idx = 0;
    CHAR                    s_key[MI_INI_FILE_KEY_LEN + 1];

    if(pt_gamma_info == NULL)
    {
        DBG_ERROR(("[ACFG] pt_gamma_info is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    a_cfg_cust_info_get_gamma_table_ini_path(s_file_path);
    //c_strncpy(s_file_path,MI_INI_FILE_PATH,MI_INI_FILE_PATH_LEN);
    DBG_INFO(("[ACFG] s_path:%s, %s,%d\r\n",s_file_path,__FUNCTION__,__LINE__));

    i4_ret = MI_SYS_OpenConfigFile((MI_U8*)s_file_path, &h_acfg_ini);
    if (i4_ret != MI_OK)
    {
        DBG_ERROR(("[ACFG]Open config file %s error! i4_ret:%d\n", s_file_path, i4_ret));
        return APP_CFGR_INTERNAL_ERR;
    }

    for(ui1_idx = 0;ui1_idx < 3;ui1_idx++)
    {
        c_memset(&t_ini_data, 0, sizeof(MI_SYS_ConfigData_t));   //c_memset(&t_clr_temp_data, 0, sizeof(A_CFG_CONFIGDATA_T));
        t_ini_data.eDataType = E_MI_SYS_CONFIG_DATA_TYPE_DATA;

        if(ui1_idx == 0)
        {
            c_snprintf(s_key, 128, "gamma_table_%d:parameter_r", i1_idx);
        }
        else if (ui1_idx == 1)
        {
            c_snprintf(s_key, 128, "gamma_table_%d:parameter_g", i1_idx);
        }
        else if (ui1_idx == 2)
        {
            c_snprintf(s_key, 128, "gamma_table_%d:parameter_b", i1_idx);
        }

        DBG_INFO(("[ACFG] s_key:%s,%d\r\n",s_key,__LINE__));

        i4_ret = MI_SYS_GetConfigData(h_acfg_ini, (const MI_U8 *)s_key, &t_ini_data);

        pc_data = (CHAR *)t_ini_data.stData.pBuf;
        DBG_INFO(("[ACFG] pc_data:%s,%d\r\n",pc_data,__LINE__));

        if (i4_ret == MI_OK)
        {
            pc_data = (CHAR *)t_ini_data.stData.pBuf;
            //DBG_INFO(("[ACFG] pc_data:%s,%d\r\n",pc_data,__LINE__));
            pc_str = strtok(pc_data+1, ","); //remove  "{"

            for (ui2_idx = 0; pc_str != NULL ; ui2_idx++)
            {
                sscanf(pc_str, "%x", (unsigned int*)&i2_data);
                if(ui1_idx == 0)
                {
                    pt_gamma_info->gamma_r[ui2_idx] = i2_data;
                    //DBG_INFO(("pt_gamma_info->gamma_r[%d]  = %d:i2_data = 0x%x \n",ui2_idx, pt_gamma_info->gamma_r[ui2_idx], i2_data));
                }
                else if (ui1_idx == 1)
                {
                    pt_gamma_info->gamma_g[ui2_idx] = i2_data;
                    //DBG_INFO(("pt_gamma_info->gamma_g[%d]  = %d:i2_data = 0x%x \n",ui2_idx, pt_gamma_info->gamma_g[ui2_idx], i2_data));
                }
                else if (ui1_idx == 2)
                {
                    pt_gamma_info->gamma_b[ui2_idx] = i2_data;
                    //DBG_INFO(("pt_gamma_info->gamma_b[%d]  = %d:i2_data = 0x%x \n",ui2_idx, pt_gamma_info->gamma_b[ui2_idx], i2_data));
                }
                else
                {
                    break;
                }

                pc_str = strtok(NULL, ",");
            }
        }
        else
        {
            DBG_ERROR(("[ACFG_VIDEO]Get Gamma default value form ini failed! i4_ret:%d\n", i4_ret));
        }

    }

    MI_SYS_CloseConfigFile(h_acfg_ini);
    h_acfg_ini = NULL_HANDLE;
    return i4_ret;

}


INT32 a_cfg_cust_info_set_gamma_table_to_ini(INT8 i1_idx,ACFG_GAMMA_TABLE_T* pt_gamma_info)
{
    CHAR                    s_file_path[MI_INI_FILE_PATH_LEN+1] = {0};
    INT32                   i4_ret = 0;
    MI_HANDLE               h_acfg_ini = NULL_HANDLE;
    MI_SYS_ConfigData_t     t_ini_data;
    UINT8                   ui1_idx = 0;
    CHAR                    s_key[MI_INI_FILE_KEY_LEN + 1];
    CHAR                    *ps_buffer = NULL;
    UINT16                  ui2_idy = 0;
    CHAR                    s_tmp[10];

    if(pt_gamma_info == NULL)
    {
        DBG_ERROR(("[ACFG] pt_gamma_info is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    a_cfg_cust_info_get_gamma_table_ini_path(s_file_path);
    //c_strncpy(s_file_path,MI_INI_FILE_PATH,MI_INI_FILE_PATH_LEN);
    DBG_INFO(("[ACFG]s_path:%s, %s,%d\r\n",s_file_path,__FUNCTION__,__LINE__));

    i4_ret = MI_SYS_OpenConfigFile((MI_U8*)s_file_path, &h_acfg_ini);
    if (i4_ret != MI_OK)
    {
        DBG_ERROR(("[ACFG] MI_SYS_OpenConfigFile at i4_ret:%d,  %s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    ps_buffer = (CHAR *)c_mem_alloc(MI_INI_FILE_SIZE_LEN);
    if(NULL == ps_buffer)
    {
        DBG_ERROR(("[ACFG] c_mem_alloc at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }
    c_memset(ps_buffer, 0, MI_INI_FILE_SIZE_LEN);

    for(ui1_idx = 0;ui1_idx < 3;ui1_idx++)
    {
        c_memset(ps_buffer, 0, MI_INI_FILE_SIZE_LEN);
        c_strncpy(ps_buffer,"\\\n{\\\n",9);
        if(ui1_idx == 0)
        {
            c_snprintf(s_key, MI_INI_FILE_KEY_LEN, "gamma_table_%d:parameter_r", i1_idx);
            for (ui2_idy = 0;ui2_idy < (GAMMA_LEN - 1);ui2_idy ++ )
            {
                c_sprintf(s_tmp,"0x%02X,",pt_gamma_info->gamma_r[ui2_idy]);
                c_strncat(ps_buffer,s_tmp,9);
                if(ui2_idy % GAMMA_ERERY_LINE_LEN == (GAMMA_ERERY_LINE_LEN - 1))
                {
                    c_strncat(ps_buffer,"\\\n",9);
                }
            }

            c_sprintf(s_tmp,"0x%02X",pt_gamma_info->gamma_r[GAMMA_LEN - 1]);
        }
        else if (ui1_idx == 1)
        {
            c_snprintf(s_key, MI_INI_FILE_KEY_LEN, "gamma_table_%d:parameter_g", i1_idx);
            for (ui2_idy = 0;ui2_idy < (GAMMA_LEN - 1);ui2_idy ++ )
            {
                c_sprintf(s_tmp,"0x%02X,",pt_gamma_info->gamma_g[ui2_idy]);
                c_strncat(ps_buffer,s_tmp,9);
                if(ui2_idy % GAMMA_ERERY_LINE_LEN == (GAMMA_ERERY_LINE_LEN - 1))
                {
                    c_strncat(ps_buffer,"\\\n",9);
                }
            }

            c_sprintf(s_tmp,"0x%02X",pt_gamma_info->gamma_g[GAMMA_LEN - 1]);
        }
        else if (ui1_idx == 2)
        {
            c_snprintf(s_key, MI_INI_FILE_KEY_LEN, "gamma_table_%d:parameter_b", i1_idx);
            for (ui2_idy = 0;ui2_idy < (GAMMA_LEN - 1);ui2_idy ++ )
            {
                c_sprintf(s_tmp,"0x%02X,",pt_gamma_info->gamma_b[ui2_idy]);
                c_strncat(ps_buffer,s_tmp,9);
                if(ui2_idy % GAMMA_ERERY_LINE_LEN == (GAMMA_ERERY_LINE_LEN - 1))
                {
                    c_strncat(ps_buffer,"\\\n",9);
                }
            }

            c_sprintf(s_tmp,"0x%02X",pt_gamma_info->gamma_b[GAMMA_LEN - 1]);
        }

        c_strncat(ps_buffer,s_tmp,9);
        c_strncat(ps_buffer,"\\\n};\n",9);

        DBG_INFO(("[ACFG] s_key:%s\r\n",s_key));
        //DBG_LOG_PRINT(("[ACFG] ps_buffer:\r\n%s\r\n",ps_buffer));

        c_memset(&t_ini_data, 0, sizeof(MI_SYS_ConfigData_t));
        t_ini_data.eDataType = E_MI_SYS_CONFIG_DATA_TYPE_DATA;
        t_ini_data.stData.pBuf = (void *)ps_buffer;
        t_ini_data.stData.u32Len = c_strlen((char *)ps_buffer);
        t_ini_data.eDataType = E_MI_SYS_CONFIG_DATA_TYPE_DATA;
        DBG_INFO(("[ACFG] u32Len:%d,%d\r\n",t_ini_data.stData.u32Len,__LINE__));

        i4_ret = MI_SYS_SetConfigData(h_acfg_ini, (const MI_U8 *)s_key, &t_ini_data);

        if (i4_ret == MI_OK)
        {
            DBG_INFO(("[ACFG]MI_SYS_SetConfigData Successfull %s,%d\r\n",__FUNCTION__,__LINE__));
        }
        else
        {
            DBG_ERROR(("[ACFG]MI_SYS_SetConfigData Fait,i4_ret = %d,  %s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
        }

    }

    if(ps_buffer != NULL)
    {
        c_mem_free(ps_buffer);
    }

    MI_SYS_CloseConfigFile(h_acfg_ini);
    h_acfg_ini = NULL_HANDLE;

    return i4_ret;

}

INT32 a_cfg_cust_get_wifi_module_info(WIFI_DEVICE_INFO* pt_info )
{
    FILE*    pf_out = NULL;
    CHAR     buf[512] = {0};
    CHAR*    ptr = NULL;
    SIZE_T   rlen;


    if(!pt_info)
    {
        return APP_CFGR_INV_ARG;
    }
    c_memset(pt_info,0,sizeof(WIFI_DEVICE_INFO));
    if((pf_out = popen("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 driver get_hifl","r")))
    {
        rlen = fread(buf,sizeof(buf),1,pf_out);
        if (rlen < 0) {
            DBG_ERROR(("[%s %d] fread failed\n",__FUNCTION__,__LINE__));
            pclose(pf_out);
            return APP_CFGR_INV_ARG;
        }
        buf[rlen] = '\0';
        DBG_INFO(("[%s %d] buf = %s\n",__FUNCTION__,__LINE__,buf));
        ptr = strtok(buf,"\r\n");

         while(ptr)
         {
             if(strstr(ptr,"VenderID:"))
             {
                 c_strcpy(pt_info->c_VenderID,ptr + c_strlen("VenderID:") + 1);
             }
             else  if(strstr(ptr,"ProductID:"))
             {
                 c_strcpy(pt_info->c_ProductID,ptr + c_strlen("ProductID:") + 1);
             }
             ptr = strtok(NULL,"\r\n");
         }
         DBG_INFO(("[%s %d] VenderID =%s\n",__FUNCTION__,__LINE__,pt_info->c_VenderID));
         DBG_INFO(("[%s %d] ProductID =%s\n",__FUNCTION__,__LINE__,pt_info->c_ProductID));
         pclose(pf_out);
         pf_out = NULL;
    }
    else
    {
         DBG_ERROR(("[%s %d] popen failed\n",__FUNCTION__,__LINE__));
    }
    return APP_CFGR_OK;
}

INT32 a_cfg_cust_drv_set_spdif_enable(BOOL bOnOff)
{
    INT32             i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_PRINT("Set bOnOff :%d \r\n",bOnOff);
    //DBG_INFO(("[spdif fusion1.5] {%s %s() %d}. \n",__FILE__, __FUNCTION__, __LINE__));
    SIZE_T z_size = sizeof(bOnOff);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    //t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_LDM_SCROLLING_FUN;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_SPDIF_ENABLE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&bOnOff;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );
    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    return i4_ret;
}

INT32 a_cfg_cust_set_oled_off_rs(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;
    i4_ret = acfg_set(IDX_CUSTOM_OLED_OFF_RS, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_cust_get_oled_off_rs(UINT8 *pui1_status)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_value = 0;

    if (!pui1_status)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_OLED_OFF_RS, &ui1_value, &z_size);

    *pui1_status = ui1_value;

    return i4_ret;
}

INT32 a_cfg_cust_set_oled_jb(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;
    i4_ret = acfg_set(IDX_CUSTOM_OLED_JB, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_cust_get_oled_jb(UINT8 *pui1_status)
{
    SIZE_T      z_size;
    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_value = 0;

    if (!pui1_status)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_OLED_JB, &ui1_value, &z_size);

    *pui1_status = ui1_value;

    return i4_ret;
}

BOOL a_cfg_cust_is_oled_compensation_jb_enable()
{
    BOOL  b_enable   = FALSE;
    UINT8 ui1_enable = 0;
    a_cfg_cust_get_oled_jb(&ui1_enable);
    do{
        if(ui1_enable > 0)
        {
            b_enable = TRUE;
        }
    }while(0);

    return b_enable;
}

UINT32 a_cfg_cust_get_oled_compensation_cooling_time()
{
    UINT16 ui2_cooling_time = 60;
    a_cfg_custom_get_oled_jb_cooling_time(&ui2_cooling_time);
    if(ui2_cooling_time == 0)
    {
        ui2_cooling_time = 60;
    }
    DBG_INFO(("[ACFG][%s %d] ui2_cooling_time = %d\n",__FUNCTION__,__LINE__,ui2_cooling_time));
    return (UINT32)(ui2_cooling_time * 60);
}

static HANDLE_T h_led_timer     = NULL_HANDLE;
static BOOL     b_led_light     = FALSE;
static UINT8    ui1_breath_sec  = 3;
static UINT16   ui2_led_ctrl    = 0;

static VOID _led_action (VOID*   pv_tag,VOID*   pv_tag2,VOID*   pv_tag3)
{
    a_cfg_custom_set_led_breath_to_drv(ui1_breath_sec);
}

static VOID  led_timer_nfy(HANDLE_T    h_timer,VOID*  pv_tag)
{
    nav_request_context_switch (_led_action,NULL,NULL,NULL);
}

INT32 a_cfg_cust_led_blinking_start(UINT32 ui4_time)
{
    if(NULL_HANDLE != h_led_timer)
    {
        c_timer_stop(h_led_timer);
    }
    else
    {
        ACFG_LOG_ON_FAIL(c_timer_create(&h_led_timer));
    }

    ui2_led_ctrl   = a_cfg_custom_get_led_logo_ctrl();
    ui1_breath_sec = ui4_time;
    a_cfg_custom_set_led_logo_ctrl(0);

    DBG_LOG_PRINT(("led:breath start,ui2_led_ctrl = %d,ui1_breath_sec = %d\n",ui2_led_ctrl,ui1_breath_sec));

    return c_timer_start(h_led_timer,
                         ui4_time*1000,
                         X_TIMER_FLAG_REPEAT,
                         led_timer_nfy,
                         NULL);
}

INT32 a_cfg_cust_led_blinking_stop()
{
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = c_timer_stop(h_led_timer);
    a_cfg_custom_set_led_logo_ctrl((UINT8)ui2_led_ctrl);
    ui1_breath_sec = 3;

    DBG_INFO(("led:%d stop\n",b_led_light));
    return i4_ret;
}

static SCC_VID_HDR_TYPE_T t_acfg_hdr_type = SCC_VID_PQ_SDR;

/*----------------------------------------------------------------------------
 * Name: a_cfg_get_hdr_type
 *
 * Description: Get the hdr statue.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
UINT32 a_cfg_get_hdr_type(VOID)
{
    return t_acfg_hdr_type;
}

VOID a_cfg_set_hdr_type(SCC_VID_HDR_TYPE_T t_hdr_type)
{
    DBG_LOG_PRINT(("[ACFG][HDR]a_cfg_set_hdr_type() %d => %d \n", t_acfg_hdr_type, t_hdr_type ));

    t_acfg_hdr_type = t_hdr_type;

    a_icl_set_hdr_type_status (t_hdr_type);

    if(a_cfg_cust_oled_support() == TRUE)
    {
        if( t_hdr_type == SCC_VID_PQ_SDR)
        {
            a_cfg_cust_drv_set_oled_hdr(0);
        }
        else
        {
            a_cfg_cust_drv_set_oled_hdr(1);
        }
    }
}

INT32 a_cfg_cust_drv_set_outregion(VOID* pv_data, SIZE_T z_size_val)
{
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T    t_set_info = {0};
    if(pv_data == NULL )
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_OUT_REGION;
    t_set_info.pv_set_info = (VOID *)pv_data;
    t_set_info.z_size = z_size_val;
    t_set_info.b_store = TRUE;
    i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_set_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return i4_ret;
    }

    return i4_ret;
}

INT32 a_cfg_cust_drv_get_outregion(VOID* pv_data, SIZE_T z_size_val)
{
    //DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};

    if(pv_data == NULL)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_OUT_REGION;
    t_get_info.pv_get_info = (VOID *)pv_data;
    t_get_info.pz_size = &z_size_val;
    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return i4_ret;
    }
    return APP_CFGR_OK;
}

INT32 a_cfg_cust_drv_set_srcregion(VOID* pv_data, SIZE_T z_size_val)
{
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T    t_set_info = {0};
    if(pv_data == NULL )
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_SRC_REGION;
    t_set_info.pv_set_info = (VOID *)pv_data;
    t_set_info.z_size = z_size_val;
    t_set_info.b_store = TRUE;
    i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_set_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return i4_ret;
    }

    return i4_ret;
}

INT32 a_cfg_cust_drv_get_srcregion(VOID* pv_data, SIZE_T z_size_val)
{
    //DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};

    if(pv_data == NULL)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_SRC_REGION;
    t_get_info.pv_get_info = (VOID *)pv_data;
    t_get_info.pz_size = &z_size_val;
    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return i4_ret;
    }
    return APP_CFGR_OK;
}

INT32 a_cfg_cust_drv_get_support_hdr_type(VOID* pv_data, SIZE_T z_size_val)
{
    //DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};

    if(pv_data == NULL)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDR_SUPPORT_TYPE;
    t_get_info.pv_get_info = (VOID *)pv_data;
    t_get_info.pz_size = &z_size_val;

    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return i4_ret;
    }
    return APP_CFGR_OK;
}

#if 1 // New api
//INT32 a_cfg_cust_drv_get_vrr_status(VOID* pv_data, SIZE_T z_size_val)
BOOL a_cfg_cust_drv_get_vrr_status(void)
{
    UINT8 u8VrrStatus = 0;
    SIZE_T z_size_val = 1;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};

    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_VRR_STATUS;
    t_get_info.pv_get_info = (VOID *)(&u8VrrStatus);
    t_get_info.pz_size = &z_size_val;

    INT32 i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET, (VOID *)&t_get_info);
    if( i4_ret != APP_CFGR_OK )
    {
        DBG_LOG_PRINT(("[ACFG]{%s, %d} Error: call a_cfg_get_drv_comp() failed ==> %d\n", __FUNCTION__,__LINE__, i4_ret));
        return FALSE;
    }

    return (BOOL)u8VrrStatus;
}
#else
INT32 a_cfg_cust_drv_get_vrr_status(VOID* pv_data, SIZE_T z_size_val)
{
    //DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};

    if(pv_data == NULL)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_VRR_STATUS;
    t_get_info.pv_get_info = (VOID *)pv_data;
    t_get_info.pz_size = &z_size_val;

    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return i4_ret;
    }
    return APP_CFGR_OK;
}
#endif

BOOL a_cfg_cust_is_VRR_enable_and_driver_detect_VRR(VOID)
{
    INT32   i4_ret = 0;
    INT16   i2_VrrEnable = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i2_VrrEnable);
    if( i4_ret != APP_CFGR_OK )
    {
        DBG_LOG_PRINT(("[ACFG]{%s,%d} rtn:%d => Get VRR fail! \n", __FILE__, __LINE__, i4_ret));
        return FALSE;
    }

    if( i2_VrrEnable != ACFG_CUST_COMMON_ON )
    {
        return FALSE;
    }

    BOOL b_vrr_drv_detected = a_cfg_cust_drv_get_vrr_status();
    if( b_vrr_drv_detected )
    {
        return TRUE;
    }

    return FALSE;
}

#if 1 // new api
//INT32 a_cfg_cust_drv_get_free_sync_rate(VOID* pv_data, SIZE_T z_size_val)
UINT16 a_cfg_cust_drv_get_free_sync_rate(void)
{
    UINT16 u16FreeSyncRate = 0;
    SIZE_T z_size_val = 2;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};

    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_FREE_SYNC_RATE;
    t_get_info.pv_get_info = (VOID *)(&u16FreeSyncRate);
    t_get_info.pz_size = &z_size_val;

    INT32 i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("[ACFG]{%s, %d} Error: call a_cfg_get_drv_comp() failed ==> %d\n", __FUNCTION__,__LINE__, i4_ret));
        return FALSE;
    }

    return u16FreeSyncRate;
}
#else
INT32 a_cfg_cust_drv_get_free_sync_rate(VOID* pv_data, SIZE_T z_size_val)
{
    //DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};

    if(pv_data == NULL)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_FREE_SYNC_RATE;
    t_get_info.pv_get_info = (VOID *)pv_data;
    t_get_info.pz_size = &z_size_val;

    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return i4_ret;
    }
    return APP_CFGR_OK;
}
#endif

INT32 a_cfg_cust_drv_get_frc_version(VOID* pv_data, SIZE_T z_size_val)
{
    //DBG_INFO(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};

    if(pv_data == NULL)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_FRC_VERSION;
    t_get_info.pv_get_info = (VOID *)pv_data;
    t_get_info.pz_size = &z_size_val;

    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return i4_ret;
    }
    return APP_CFGR_OK;
}

extern BOOL a_oled_compensation_is_off_rs_applicable();

BOOL a_cfg_cust_is_off_rs_enable()
{
    return a_oled_compensation_is_off_rs_applicable();
}

VOID a_cfg_cust_audio_mute_to_drv(BOOL b_mute)
{

    SM_COMMAND_T    at_sm_cmds[4];

    at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text     = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code        = SCC_CMD_CODE_AUDIO_MUTE;
    at_sm_cmds[2].u.b_boolean   = b_mute;
    at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
    at_sm_cmds[3].u.ui4_data    = 0;

    c_scc_comp_grp_set(at_sm_cmds);

    at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text     = SN_PRES_AUX_SOUND;
    at_sm_cmds[2].e_code        = SCC_CMD_CODE_AUDIO_MUTE;
    at_sm_cmds[2].u.b_boolean   = b_mute;
    at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
    at_sm_cmds[3].u.ui4_data    = 0;

    c_scc_comp_grp_set(at_sm_cmds);


    DBG_LOG_PRINT(("SET  AUDIO %s\n",b_mute ? "MUTE" : "UNMUTE"));

}


VOID a_cfg_cust_audio_mute(BOOL b_mute)
{
    if(!a_tv_get_mute())
    {
        SM_COMMAND_T    at_sm_cmds[4];

        at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
        at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_AUDIO;
        at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
        at_sm_cmds[1].u.ps_text     = SN_PRES_MAIN_DISPLAY;
        at_sm_cmds[2].e_code        = SCC_CMD_CODE_AUDIO_MUTE;
        at_sm_cmds[2].u.b_boolean   = b_mute;
        at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
        at_sm_cmds[3].u.ui4_data    = 0;

        c_scc_comp_grp_set(at_sm_cmds);

        at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
        at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_AUDIO;
        at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
        at_sm_cmds[1].u.ps_text     = SN_PRES_AUX_SOUND;
        at_sm_cmds[2].e_code        = SCC_CMD_CODE_AUDIO_MUTE;
        at_sm_cmds[2].u.b_boolean   = b_mute;
        at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
        at_sm_cmds[3].u.ui4_data    = 0;

        c_scc_comp_grp_set(at_sm_cmds);

        /*mute spdif/arc,there is no need modify acfg status*/
        a_tv_nav_cec_set_arc_spdif_mute(b_mute);

        DBG_LOG_PRINT(("SET  AUDIO %s\n",b_mute ? "MUTE" : "UNMUTE"));
    }

}

VOID a_cfg_cust_backlight_onoff(BOOL b_on)
{
    a_cfg_custom_set_black_pattern(b_on ? FALSE : TRUE);
}

VOID a_cfg_cust_panel_onoff(BOOL b_on)
{
    if(a_oled_compensation_is_running() && FALSE == b_on)
    {
       DBG_LOG_PRINT(("oled_compensation_is_running skip panel_onoff[%d] ",b_on));
       return ;
    }
    {
        SM_COMMAND_T   at_scc_cmds [4];
        /* Turn off backlight & LVDS */
        at_scc_cmds [0].e_code      = SCC_CMD_CODE_GRP_TYPE;
        at_scc_cmds [0].u.ui4_data  = SCC_CMD_TYPE_DISP;
        at_scc_cmds [1].e_code      = SCC_CMD_CODE_NAME;
        at_scc_cmds [1].u.ps_text   = SN_PRES_MAIN_DISPLAY;
        at_scc_cmds [2].e_code      = SCC_CMD_CODE_DISP_CTRL;
        at_scc_cmds [2].u.ui4_data  = b_on == TRUE ? SCC_DISP_CTRL_ENABLE : SCC_DISP_CTRL_DISABLE;
        at_scc_cmds [3].e_code      = SM_CMD_CODE_END;
        c_scc_comp_grp_set (at_scc_cmds);
    }
    DBG_LOG_PRINT(("TURN %s PANEL\n",b_on ? "ON": "OFF"));
}

UINT32 acfg_default_wakeup_time()
{
    UINT32 ui4_default_wakeup_timer = 24*60*60;  //24 hours

    if(access("/data/uli/check_update.json",0) == 0)
    {
        FILE* fp = fopen("/data/uli/check_update.json","r");
        if(fp)
        {
            CHAR read_buf[1024] = {0};
            INT32 i4_nread = fread(read_buf,1,1024,fp);

            DBG_INFO(("content:\n%s\n",read_buf));

            if(i4_nread > 0)
            {
                cJSON *root = NULL;
                if(NULL != (root = cJSON_Parse(read_buf)))
                {
                    cJSON *updater = NULL;

                    if(NULL != (updater = cJSON_GetObjectItem(root,"timer")))
                    {
                        if(NULL != updater->valuestring)
                        {
                            DBG_INFO(("%s %d value %s\n",__FUNCTION__,__LINE__,updater->valuestring));
                            INT32 i4_timer = atoi(updater->valuestring);
                            ui4_default_wakeup_timer = i4_timer * 60;
                        }
                    }
                    else
                    {
                        DBG_ERROR(("%s %d,error:%s\n",__FUNCTION__,__LINE__,cJSON_GetErrorPtr()));
                    }
                    cJSON_Delete(root);
                }
                else
                {
                    DBG_ERROR(("%s %d,error:%s\n",__FUNCTION__,__LINE__,cJSON_GetErrorPtr()));
                }
            }
            fclose(fp);
        }
    }

    /* if in the loop test mode, always set the wakeup time to 1 minite */
#ifdef ULI_USE_ODL_LIB
    if (TRUE == a_uli_is_loop_test_mode())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"IN LOOP TEST MODE ==> Set next wake up time to 1 minite.\n"));
        ui4_default_wakeup_timer = 60;
    }
#endif
    DBG_INFO(("%s %d,ui4_default_wakeup_timer = %d\n\r",__FUNCTION__,__LINE__,ui4_default_wakeup_timer));
    return ui4_default_wakeup_timer;
}

BOOL a_is_oled_compensation_support()
{
    return b_g_is_oled_suppend;
}

INT32 a_cfg_custom_set_oled_status(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_OLED_STATUS, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_get_oled_status(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_OLED_STATUS, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_set_oled_err_detect_checksum(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_OLED_ERR_COUNT_CHECKSUM, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_get_oled_err_detect_checksum(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_OLED_ERR_COUNT_CHECKSUM, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_set_demo_type(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_DEMO_TYPE, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* write to EEPROM */
    i4_ret =  acfg_eep_flush();
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_get_demo_type(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_DEMO_TYPE, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

UINT32 a_cfg_cust_v_logo_delay()
{
#if 0
    UINT32 ui4_support = 0;
    a_cfg_cust_drv_get_oled_support_compensation(&ui4_support);

    return (0 == ui4_support) ? 3 : 6; //oled panel rc on will display back display before normal display
#else
    return 4;
#endif
}

/***
This API will set the oled error detect on/off
0:means oled error detect enable
1:means oled error detect disable
****/

INT32 a_cfg_custom_set_oled_error_detect_disable(UINT8 ui1_disable)
{
    INT32   i4_ret = APP_CFGR_OK;
    i4_ret = acfg_set(IDX_CUSTOM_OLED_ERROR_DETECT_ON_OFF, &ui1_disable, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return i4_ret;
}

/***
This API will get the oled error detect on/off
0:means oled error detect enable
1:means oled error detect disable
****/
INT32 a_cfg_custom_get_oled_error_detect_disable(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_OLED_ERROR_DETECT_ON_OFF, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return i4_ret;

}


INT32 a_cfg_custom_set_oled_error_detect_count(UINT8 ui1_status)
{
    INT32   i4_ret = APP_CFGR_OK;
    UINT32 ui4_checksum=0;
    i4_ret = acfg_set(IDX_CUSTOM_OLED_ERROR_COUNT, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    ui4_checksum+=ui1_status;
    i4_ret = acfg_set(IDX_CUSTOM_OLED_ERROR_COUNT_BACKUP1, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    ui4_checksum+=ui1_status;
    i4_ret = acfg_set(IDX_CUSTOM_OLED_ERROR_COUNT_BACKUP2, &ui1_status, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    ui4_checksum+=ui1_status;
    ui4_checksum = (0xff-(UINT8)ui4_checksum);
    DBG_LOG_PRINT(("[ACFG][%s %d] ui4_checksum:%d error_detect_count:%d\n",__FUNCTION__,__LINE__,ui4_checksum,ui1_status));
    a_cfg_custom_set_oled_err_detect_checksum((UINT8)ui4_checksum);
    return i4_ret;
}

INT32 a_cfg_custom_get_oled_error_detect_count(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;
    UINT8       ui1_error_count_backup1 = 0;
    UINT8       ui1_error_count_backup2 = 0;
    UINT8       ui1_error_count_checksum = 0;
    i4_ret = acfg_get(IDX_CUSTOM_OLED_ERROR_COUNT, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = acfg_get(IDX_CUSTOM_OLED_ERROR_COUNT, &ui1_error_count_backup1, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = acfg_get(IDX_CUSTOM_OLED_ERROR_COUNT, &ui1_error_count_backup2, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    a_cfg_custom_get_oled_err_detect_checksum(&ui1_error_count_checksum);
    if(ui1_error_count_checksum + ui1_error_count_backup1 + ui1_error_count_backup2 + *pui1_val == 0xff)
    {
        return i4_ret;
    }
    else
    {
        a_cfg_custom_set_oled_error_detect_count(0);
        *pui1_val = 0;
        return i4_ret;
    }
}

static VOID _cfg_detect_oled_pal_err_action (
            VOID*                       pv_tag1,
            VOID*                       pv_tag2,
            VOID*                       pv_tag3 )
{
    ACFG_OLED_ERROR_DETECT_TYPE e_error_type = (ACFG_OLED_ERROR_DETECT_TYPE) ((UINT32) pv_tag1);
    UINT8 ui1_error_count = 0;
    UINT32 ui4_drv_eco = ICL_CUSTOM_POWER_MODE_ECO;
    BGM_STATE_T state = bgm_get_state();
    a_cfg_custom_get_oled_error_detect_count(&ui1_error_count);
    a_cfg_custom_get_drv_eco_mode(&ui4_drv_eco);
    DBG_LOG_PRINT(("e_error_type:%d ui1_error_count:%d \n",e_error_type,ui1_error_count));
    if((e_error_type == ACFG_OLED_ERR_EVENT_PNL_ERR||
       e_error_type == ACFG_OLED_ERR_EVENT_PWM_ERR)&&
       (!b_during_power_ignore_count||state == BGM_STATE_RUNNING || state == BGM_STATE_PRE_RUNNING ||
       (ui4_drv_eco == ICL_CUSTOM_POWER_MODE_QUICK_START)))
    {
         // three times will block the backlight and panel
         if(ui1_error_count >= 3)
         {
            DBG_LOG_PRINT(("sys block,ignore \n"));
            return;
         }
         if(e_error_type == ACFG_OLED_ERR_EVENT_PNL_ERR)
         {
             FILE * fl ;

             ui1_error_count++;
             b_during_power_ignore_count = TRUE;
             a_cfg_custom_set_oled_error_detect_count(ui1_error_count);

             fl = fopen ("/data/oled_error_detect_reboot","w");
             fclose (fl);
         }
         DBG_LOG_PRINT((" OLED ui1_error_count:%d \n",ui1_error_count));
         if(ui1_error_count < 3 )
        {
            if((ui4_drv_eco == ICL_CUSTOM_POWER_MODE_QUICK_START)||state == BGM_STATE_RUNNING || state == BGM_STATE_PRE_RUNNING)
            {
                if(ui4_drv_eco == ICL_CUSTOM_POWER_MODE_QUICK_START)
                {
                    FILE * fl ;
                    fl = fopen ("/data/oled_restore_eco_qs","w");
                    fclose (fl);

                    a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_ON);
                    a_cfg_custom_set_drv_eco_mode(ICL_CUSTOM_POWER_MODE_ECO);  //just set to eco then reboot
                    a_cfg_store();
                }
                DBG_LOG_PRINT((" OLED Panel error detect in QS or under bgm runing,TV reboot\n"));
                AP_SYSTEM_CALL("reboot");
            }
            else if(a_am_is_power_on()&&(ui4_drv_eco == ICL_CUSTOM_POWER_MODE_ECO))
            {
                c_iom_send_evt(BTN_POWER,100);
            }

        }
        else if((ui1_error_count == 3)&&(e_error_type == ACFG_OLED_ERR_EVENT_PNL_ERR))
        {
            a_tv_set_env_to_mpool("oled_block", "1");
            a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_OFF);
            a_cfg_custom_set_drv_eco_mode(ICL_CUSTOM_POWER_MODE_QUICK_START);  //just set to eco then reboot
            a_cfg_store();
            DBG_LOG_PRINT((" OLED PanelLocked done,TV reboot\n"));
            AP_SYSTEM_CALL("reboot");
        }
    }
    else if (ACFG_OLED_ERR_EVENT_GSP_IMG_STILL == e_error_type)
    {
        t_still_image_status = ACFG_OLED_ERR_EVENT_GSP_IMG_STILL;
        if (menu_custom_get_blank_scrn_mode() == BLK_SCRN_OLED_NO_SIGNAL
            || menu_custom_get_blank_scrn_mode() == BLK_SCRN_OLED_SMART_UI
            || menu_custom_is_blank_screen())
        {
            return;
        }
        menu_custom_set_blank_scrn_mode(BLK_SCRN_OLED_STILL_IMAGE);

        if(b_g_oled_bypass_img_still)
        {
            b_g_oled_bypass_img_still = FALSE;
        }
        else
        {
            menu_blank_oled_scrn_timer_start();
        }
    }
    else if (ACFG_OLED_ERR_EVENT_GSP_IMG_MOVE == e_error_type)
    {
        t_still_image_status = ACFG_OLED_ERR_EVENT_GSP_IMG_MOVE;

        if(menu_custom_blank_screen_is_oled_toast_show())
        {
            b_g_oled_bypass_img_still = TRUE;
        }
        else  if (menu_custom_get_blank_scrn_mode() == BLK_SCRN_OLED_STILL_IMAGE)
        {
            if(menu_custom_is_blank_screen())
            {
                menu_custom_unblank_screen(BTN_CURSOR_UP);
            }
            else
            {
                menu_blank_oled_scrn_timer_stop();
            }
        }
    }
}

void a_cfg_custom_oled_bypass_img_still(BOOL bBypass)
{
    b_g_oled_bypass_img_still = bBypass;
}

INT32 a_acfg_disp_detect_oled_pal_err_nfy_fct(
                               HANDLE_T                         h_disp,
                               VOID*                            pv_nfy_tag,
                               UINT32                           ui4_data )
{
    nav_request_context_switch (_cfg_detect_oled_pal_err_action,(VOID*) ui4_data,NULL,NULL);
    return APP_CFGR_OK;
}



static INT32 _video_get_info(
    UINT16              ui2_id,
    const CHAR*         s_disp_name,
    HANDLE_T*           ph_scc_comp,    /* out */
    SCC_CMD_TYPE_T*     pe_cmd_type,     /* out */
    SM_CMD_CODE_T*      pe_cmd_code,    /* out */
    VOID**              ppv_cmd_arg,    /* out */
    INT16*              pi2_val_min,    /* out */
    INT16*              pi2_val_max)    /* out */
{
    SM_CMD_CODE_T           e_cmd_code = 0;
    SCC_CMD_TYPE_T          e_cmd_type = SCC_CMD_TYPE_VIDEO;
    VOID*                   pv_cmd_arg = NULL;
    INT16                   i2_val_min = 0;
    INT16                   i2_val_max = 0;
    UINT16                  ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16                  ui2_cfg_rec = CFG_GET_SETTING(ui2_id);

    /* Get the info by group and record id */
    if(APP_CFG_GRPID_VIDEO == ui2_cfg_grp)
    {
        switch(ui2_cfg_rec)
        {

            case  APP_CFG_RECID_VID_NR:
                e_cmd_type = SCC_CMD_TYPE_VIDEO;
                e_cmd_code = SCC_CMD_CODE_VIDEO_NR;
                i2_val_min = t_g_acfg_cfg.t_video_cfg.t_nr_mmd[0].i2_min;
                i2_val_max = t_g_acfg_cfg.t_video_cfg.t_nr_mmd[0].i2_max;
                break;

            case  APP_CFG_RECID_VID_3D_NR:
                e_cmd_type = SCC_CMD_TYPE_VIDEO;
                e_cmd_code = SCC_CMD_CODE_VIDEO_3D_NR;
                i2_val_min = t_g_acfg_cfg.t_video_cfg.t_3d_nr_mmd[0].i2_min;
                i2_val_max = t_g_acfg_cfg.t_video_cfg.t_3d_nr_mmd[0].i2_max;
                break;
            default:
                return APP_CFGR_NOT_SUPPORT;
        }
    }
    else
    {
         return APP_CFGR_NOT_SUPPORT;
    }

    /* copy out the value */
    if(e_cmd_type == SCC_CMD_TYPE_DISP)
    {
        *ph_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                        h_g_acfg_scc_main_disp :
                        h_g_acfg_scc_sub_disp);
    }
    else if(e_cmd_type == SCC_CMD_TYPE_VIDEO)
    {
        *ph_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                        h_g_acfg_scc_main_vid :
                        h_g_acfg_scc_sub_vid);
    }
    else
    {
        /* never go this path */
        ACFG_ASSERT(FALSE);
    }

    *pe_cmd_type = e_cmd_type;
    *pe_cmd_code = e_cmd_code;
    *ppv_cmd_arg = pv_cmd_arg;
    *pi2_val_min = i2_val_min;
    *pi2_val_max = i2_val_max;

    return APP_CFGR_OK;
}



//
//copy by common , not get data form eeporm
//
static INT32 acfg_video_update_ex(UINT16  ui2_id, INT16 i2_app_val)
{
    INT32           i4_ret = 0;
    INT16           i2_app_min = 0;
    INT16           i2_app_max = 0;
    INT32           i4_drv_val = 0;
    UINT16          ui2_scc_val = 0;
    UINT16          ui2_cfg_grp = CFG_GET_GROUP(ui2_id);
    UINT16          ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    SCC_CMD_TYPE_T  e_cmd_type = SCC_CMD_TYPE_VIDEO;
    SM_COMMAND_T    at_sm_cmds[4];
    SM_CMD_CODE_T   e_cmd_code;
    HANDLE_T        h_scc_comp;
    VOID*           pv_cmd_arg;
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1];


    /* Reset the array */
    c_memset(at_sm_cmds, 0, sizeof(at_sm_cmds));

    /* Step 1: Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    /* Step 2: get from individual group */
    switch(ui2_cfg_grp)
    {
        case APP_CFG_GRPID_VIDEO:
        {
            switch(ui2_cfg_rec)
            {
                case APP_CFG_RECID_VID_NR:
                case APP_CFG_RECID_VID_3D_NR:

                    /* get info */
                    i4_ret = _video_get_info(ui2_id,
                                             s_disp_name,
                                             &h_scc_comp,
                                             &e_cmd_type,
                                             &e_cmd_code,
                                             &pv_cmd_arg,
                                             &i2_app_min,
                                             &i2_app_max);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    /* convert to scc value */
                    i4_ret = acfg_app2drv(i2_app_min, i2_app_max, i2_app_val,
                                          0, (INT32)SCC_ATTRIB_VALUE_MAX, &i4_drv_val);
                    ACFG_CHK_FAIL(i4_ret, i4_ret);

                    ui2_scc_val = (UINT16)i4_drv_val;

                    /* For BLE, WPL, CTI, ETI, LUMA, only apply these feature for main path in driver */
                    /* For NR, 3DNR, only need to set to main.
                       If main is VGA and sub is TVD, driver will apply NR to sub automatically. */
                    /* For FLESHTONE has different value in driver */
                    at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
                    at_sm_cmds[0].u.ui4_data    = e_cmd_type;
                    at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
                    at_sm_cmds[1].u.ps_text     = SN_PRES_MAIN_DISPLAY;
                    at_sm_cmds[2].e_code        = e_cmd_code;
                    at_sm_cmds[2].u.ui2_data    = ui2_scc_val;
                    at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
                    at_sm_cmds[3].u.ui4_data    = 0;
                    i4_ret = c_scc_comp_grp_set(at_sm_cmds);
                    ACFG_CHK_FAIL(i4_ret, APP_CFGR_INTERNAL_ERR);

                    break;
                default:
                    return APP_CFGR_NOT_SUPPORT;
            }
            default:
                return APP_CFGR_NOT_SUPPORT;
        }
    }

    return APP_CFGR_OK;
}

static VOID _cfg_hdmi_detect_vrr_stream_action (
            VOID*                       pv_tag1,
            VOID*                       pv_tag2,
            VOID*                       pv_tag3 )
{
    INT32  i4_ret;
    BOOL b_is_vrr_stream = (UINT32)pv_tag1;


    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] _cfg_hdmi_detect_vrr_stream_action(b_is_vrr_stream:%d)\n", b_is_vrr_stream ));


  #if 1 // Check VRR setting..., why ???
    if( b_is_vrr_stream )
    {
        INT16 i2_VRR_val = 0;
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i2_VRR_val);
        if(i4_ret != APP_CFGR_OK)
        {
            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s,%d} Error: Cannot get VRR!!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i4_ret));
            return ;
        }

        if(i2_VRR_val != ACFG_CUST_COMMON_ON)
        {
            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s,%d} Error: VRR detected but VRR setting is OFF!!! i2_VRR_val:%d\n", __FUNCTION__,__LINE__, i2_VRR_val));
            //b_g_detect_hdmi_vrr_stream = 0;
            //return ;

            // Force to OFF
            b_is_vrr_stream = 0;
        }
    }
  #endif


    //1. Black detail
    //2. Local contrast
    //3. Signal nosie
    //4. Contour smoothing
    //5. Judder reduction
    //6. Motion blir reduction
    //7. Clear action
    //8. Active full arry (remove)
    //9. Enhanced Viewing Angle
    if(b_is_vrr_stream) //turn off no oporation eeprom
    {
        //b_g_detect_hdmi_vrr_stream = TRUE;

        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} VRR detected => Disable some PQ ...\n", __FUNCTION__,__LINE__ ));

        //1. Black Detail           // 0:off ; 1:low; 2:medim; 3:high
        a_cfg_cust_drv_set_contrast_enhancement((UINT8)0);

        //2. Local contrast         // 0:off ; 1:low; 2:medim; 3:high
        a_cfg_cust_drv_set_local_contrast((UINT8)0);

        //3. Signal Noise           // 0:off ; 1:low; 2:medim; 3:high
        acfg_video_update_ex(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR),    (UINT8)0);
        acfg_video_update_ex(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR), (UINT8)0);

        //4. Contour Smoothing      // 0:off ; 1:low; 2:medim; 3:high
        a_cfg_cust_drv_set_contour_smoothing((UINT8)0);

        //5. Judder reduction       // 0 - 10
        a_cfg_cust_drv_set_judder_reduction((UINT8)0);

        //6. Motion blir reduction  // 0 - 10
        a_cfg_cust_drv_set_motion_blur_reduction((UINT8)0);

        //7. Clear action           // 0: off ; 1 : on
        if (a_cfg_cust_get_support_clear_aciton() == TRUE)
        {
            VIZIO_CLEAR_ACTION_D_SET(0);
        }

    #if 0
        //8. Active full arry       // 0: off
        if(a_cfg_cust_get_support_local_dimming() == TRUE)
        {
            i4_ret = VIZIO_EXTREME_BLACK_ENGINE_D_SET((UINT16)0);
            ACFG_LOG_ON_FAIL(i4_ret);
        }
    #endif

        //9. Enhanced Viewing Angle         // 0: off ; 1 : on
        if (a_cfg_cust_en_view_angle_support() == TRUE)
        {
            a_cfg_cust_drv_set_enhanced_viewing_angle(0);
        }

    }
    else
    {
        //b_g_detect_hdmi_vrr_stream = FALSE;

        //if(b_g_detect_hdmi_vrr_stream != FALSE) // VRR status: 1 -> 0
        {
            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} VRR not detected: Recovery some PQ ...\n", __FUNCTION__,__LINE__ ));

            //1. Black Detail
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN));

            //2. Local contrast
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST));

            //3. Signal Noise
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));

            //4. Contour Smoothing
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTOUR_SMOTHING));

            //5. Judder reduction
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION));

            //6. Motion blir reduction
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION));

            //7. Clear action
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION));

        #if 0
            //8. Active full arry
            if(a_cfg_cust_get_support_local_dimming() == TRUE)
            {
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
            }
        #endif

            //9. Enhanced Viewing Angle
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));

        }

    }

    //refresh menu
    if (a_menu_is_resume())
    {
        menu_pm_repaint();
        menu_pm_refresh();
    }

}

static INT32 _cfg_hdmi_detect_vrr_stream_nfy_fct(UINT32  ui4_data)
{
    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] _cfg_hdmi_detect_vrr_stream_nfy_fct(%d)\n", ui4_data));

    nav_request_context_switch (_cfg_hdmi_detect_vrr_stream_action,(VOID*) ui4_data,NULL,NULL);
    return APP_CFGR_OK;
}

BOOL a_acfg_cust_vrr_is_enable_and_detect_stream(VOID)
{
    //return b_g_detect_hdmi_vrr_stream;
    return (g_ACFG_eCurVrrFreeSyncStatus == ACFG_VRR_STATUS_VRR);
}

#if( ACFG_CUST_VRR_INPUT_DO_FREESYNC_JOB )
    #define ACFG_CUST_FREE_SYNC_INPUT_AUTO_ENABLE_VRR   1
#else
    #define ACFG_CUST_FREE_SYNC_INPUT_AUTO_ENABLE_VRR   0
#endif

static VOID _cfg_detect_freesync_flag_action (
            VOID*                       pv_tag1,
            VOID*                       pv_tag2,
            VOID*                       pv_tag3 )
{
    INT32  i4_ret;

    static UINT16 _s_au16_pre_gll[ACFG_CUST_INPUT_GRP_MAX] = {0};
    static UINT8 _s_au8_pre_gll_valid[ACFG_CUST_INPUT_GRP_MAX] = {0};

    static UINT8 _s_au8_pre_pic_mode_Valid[ACFG_CUST_INPUT_GRP_MAX] = {0};
    static UINT16 _s_au16_pre_pic_mode[ACFG_CUST_INPUT_GRP_MAX] = {0};

  #if(ACFG_CUST_FREE_SYNC_INPUT_AUTO_ENABLE_VRR)
    static UINT8 _s_au8_pre_VRR[ACFG_CUST_INPUT_GRP_MAX] = {0};
    static UINT8 _s_au8_pre_VRR_valid[ACFG_CUST_INPUT_GRP_MAX] = {0};
  #endif

    BOOL b_is_detect_hdmi_freesync = (BOOL) ((UINT32) pv_tag1);
    static BOOL ab_is_detect_hdmi_freesync[ACFG_CUST_INPUT_GRP_MAX] = {0};


    ACFG_CUST_INPUT_GRP_T  eAcfgInputGrp = acfg_cust_Get_CurInputGrp();

    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] _cfg_detect_freesync_flag_action(freesync:%d), eAcfgInputGrp:%d\n", b_is_detect_hdmi_freesync, eAcfgInputGrp));

    if( eAcfgInputGrp >= ACFG_CUST_INPUT_GRP_MAX )
    {
        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s,%d} Error: Invalid eAcfgInputGrp:%d !!!!\n",__FUNCTION__,__LINE__, eAcfgInputGrp));
        return;
    }


    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s,%d} ab_is_detect_hdmi_freesync[%d]: %d --> %d \n",
                    __FUNCTION__,__LINE__, eAcfgInputGrp, ab_is_detect_hdmi_freesync[eAcfgInputGrp], b_is_detect_hdmi_freesync ));

    //If the AMD VSIF v.1 or v.2 is detected, TV must switch to game low latency mode and FreeSync/VRR mode.
    //If the AMD VSIF is no longer detected, it should switch back to the previous picture mode/setting before the auto switch
    if( b_is_detect_hdmi_freesync == TRUE )
    {
        //b_g_detect_hdmi_freesync_flag = TRUE;
        //DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} Set b_g_detect_hdmi_freesync_flag=%d \n",__FUNCTION__,__LINE__, b_g_detect_hdmi_freesync_flag));
        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} FreeSync == 1 job ...\n",__FUNCTION__,__LINE__ ));

        ab_is_detect_hdmi_freesync[eAcfgInputGrp] = 1;


        // (0) switch game picture mode  eg: vivi --- game    ui2_pre_pic_mode = vivi
        // Get current picture mode...
        UINT16 ui2_cur_pic_mode = menu_get_vid_pic_mode_idx();
        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} ui2_cur_pic_mode:%d \n",__FUNCTION__,__LINE__, ui2_cur_pic_mode));
        if( ui2_cur_pic_mode != ACFG_CUST_PIC_MODE_GAME )
        {
            _s_au16_pre_pic_mode[eAcfgInputGrp] = ui2_cur_pic_mode;
            _s_au8_pre_pic_mode_Valid[eAcfgInputGrp] = 1;

            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} Auto change picture_mode: %d --> GAME\n",__FUNCTION__,__LINE__, ui2_cur_pic_mode));
            menu_set_vid_pic_mode_idx(ACFG_CUST_PIC_MODE_GAME);
        }

        // (1) Set GLL to On ...
        INT16 i16CurGLL = 0;
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i16CurGLL);
        if(i4_ret != APP_CFGR_OK)
        {
            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s,%d} Error: Cannot get GLL!!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i4_ret));
            return;
        }
        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} i16CurGLL:%d \n",__FUNCTION__,__LINE__, i16CurGLL));

        if(i16CurGLL != ACFG_CUST_GAME_LOW_LATENCY_ON) // Change GLL to on if needed
        {
            // Backup current GLL
            _s_au16_pre_gll[eAcfgInputGrp] = i16CurGLL;
            _s_au8_pre_gll_valid[eAcfgInputGrp] = 1;

            // Force GLL of PictureMode_Game to on...
            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} Auto change GLL: %d --> ON\n", __FUNCTION__,__LINE__, i16CurGLL));
            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), (INT16)ACFG_CUST_GAME_LOW_LATENCY_ON);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY));

            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE));
        }

    #if(ACFG_CUST_FREE_SYNC_INPUT_AUTO_ENABLE_VRR)
        // (2) Change VRR to on ...
        INT16 i16CurVRR = 0;
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i16CurVRR);
        if(i4_ret != APP_CFGR_OK)
        {
            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s,%d} Error: Cannot get VRR!!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i4_ret));
            return;
        }
        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} i16CurVRR:%d \n",__FUNCTION__,__LINE__, i16CurVRR));
        if(i16CurVRR != ACFG_CUST_COMMON_ON) // Change VRR to on if needed
        {
            // Backup current GLL
            _s_au8_pre_VRR[eAcfgInputGrp] = i16CurVRR;
            _s_au8_pre_VRR_valid[eAcfgInputGrp] = 1;

            // Force GLL of PictureMode_Game to on...
            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} Auto change VRR: %d --> ON\n", __FUNCTION__,__LINE__, i16CurVRR));
            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), (INT16)ACFG_CUST_COMMON_ON);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE));
            //a_cfg_cust_drv_set_variable_refresh_rate((UINT8)1);
            //a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));
        }
    #endif


        //note: 1 - 6 don't need opo by eeprom, as need grayout ui,
        //1. Black Detail           // 0:off ; 1:low; 2:medim; 3:high
        a_cfg_cust_drv_set_contrast_enhancement((UINT8)0);

        //2. Local contrast         // 0:off ; 1:low; 2:medim; 3:high
        a_cfg_cust_drv_set_local_contrast((UINT8)0);

        //3. Signal Noise           // 0:off ; 1:low; 2:medim; 3:high
        acfg_video_update_ex(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR),    (UINT8)0);
        acfg_video_update_ex(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR), (UINT8)0);

        //4. Contour Smoothing      // 0:off ; 1:low; 2:medim; 3:high
        a_cfg_cust_drv_set_contour_smoothing((UINT8)0);

        //5. Judder reduction       // 0 - 10
        a_cfg_cust_drv_set_judder_reduction((UINT8)0);

        //6. Motion blir reduction  // 0 - 10
        a_cfg_cust_drv_set_motion_blur_reduction((UINT8)0);


        //7. Clear action => Turn Off  // 0: off ; 1 : on
        if (a_cfg_cust_get_support_clear_aciton() == TRUE)
        {
            VIZIO_CLEAR_ACTION_D_SET(0);
        }


        //9. Enhanced Viewing Angle         // 0: off ; 1 : on
        if (a_cfg_cust_en_view_angle_support() == TRUE)
        {
            a_cfg_cust_drv_set_enhanced_viewing_angle(0);
        }

    }
    else
    {
        //b_g_detect_hdmi_freesync_flag = FALSE;

        //if( b_g_detect_hdmi_freesync_flag != FALSE )
        if( ab_is_detect_hdmi_freesync[eAcfgInputGrp] )
        {
            //DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} b_g_detect_hdmi_freesync_flag:%d \n",__FUNCTION__,__LINE__, b_g_detect_hdmi_freesync_flag));
            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} FreeSync is 0 ...\n", __FUNCTION__,__LINE__ ));

            // Get current picture mode...
            UINT16 ui2_cur_pic_mode = menu_get_vid_pic_mode_idx();
            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} ui2_cur_pic_mode:%d \n",__FUNCTION__,__LINE__, ui2_cur_pic_mode));

            // Get current GLL
            INT16 i16CurGLL = 0;
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i16CurGLL);
            if(i4_ret != APP_CFGR_OK)
            {
                DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s,%d} Error: Cannot get GLL!!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i4_ret));
                return;
            }
            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} i16CurGLL:%d \n",__FUNCTION__,__LINE__, i16CurGLL));

        #if(ACFG_CUST_FREE_SYNC_INPUT_AUTO_ENABLE_VRR)
            // Get current VRR
            INT16 i16CurVRR = 0;
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i16CurVRR);
            if(i4_ret != APP_CFGR_OK)
            {
                DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] {%s,%d} Error: Cannot get VRR!!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i4_ret));
                return;
            }
            DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} i16CurVRR:%d \n",__FUNCTION__,__LINE__, i16CurVRR));
        #endif


            // (1) Restore GLL of picture_mode_game ...
            if( _s_au8_pre_gll_valid[eAcfgInputGrp] ) // Need to recovery
            {
                _s_au8_pre_gll_valid[eAcfgInputGrp] = 0;

                if( ui2_cur_pic_mode == ACFG_CUST_PIC_MODE_GAME ) // Picture_mode no changed
                {
                    if( i16CurGLL != _s_au16_pre_gll[eAcfgInputGrp] )
                    {
                        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} Recovery GLL: ON --> %d\n", __FUNCTION__,__LINE__, _s_au16_pre_gll[eAcfgInputGrp] ));
                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), (INT16)_s_au16_pre_gll[eAcfgInputGrp]);
                        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY));

                        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE));
                    }
                }
                else // Picture_mode already changed ...
                {
                    // No need to recover
                }
            }

        #if(ACFG_CUST_FREE_SYNC_INPUT_AUTO_ENABLE_VRR)
            // (1) Restore VRR of picture_mode_game ...
            if( _s_au8_pre_VRR_valid[eAcfgInputGrp] ) // Need to recovery
            {
                _s_au8_pre_VRR_valid[eAcfgInputGrp] = 0;

                if( ui2_cur_pic_mode == ACFG_CUST_PIC_MODE_GAME ) // Picture_mode no changed
                {
                    if( i16CurVRR != _s_au8_pre_VRR[eAcfgInputGrp] )
                    {
                        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} Recovery VRR: ON --> %d\n", __FUNCTION__,__LINE__, _s_au8_pre_VRR[eAcfgInputGrp] ));
                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), (INT16)_s_au8_pre_VRR[eAcfgInputGrp]);
                        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE));
                    }
                }
                else // Picture_mode already changed ...
                {
                    // No need to recover
                }
            }
        #endif


            // (3) Restore previous picture mode ...
            //  Check if need to recovery picture_mode
            if( _s_au8_pre_pic_mode_Valid[eAcfgInputGrp] )
            {
                // (0) recover picture mode   eg1: game --- vivi    eg2: other user switch to dark mode. so don't need recover
                if( (ui2_cur_pic_mode == ACFG_CUST_PIC_MODE_GAME) )
                {
                    if( _s_au16_pre_pic_mode[eAcfgInputGrp] != ACFG_CUST_PIC_MODE_GAME )
                    {
                        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} Recovery picture_mode: GAME --> %d\n", __FUNCTION__,__LINE__, _s_au16_pre_pic_mode[eAcfgInputGrp]));
                        menu_set_vid_pic_mode_idx(_s_au16_pre_pic_mode[eAcfgInputGrp]);
                    }
                }
                else // User already change picture mode...
                {
                    // No need to do recovery!
                }

                _s_au8_pre_pic_mode_Valid[eAcfgInputGrp] = 0;
            }



            //1. recover Black Detail
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN));

            //2. recover Local contrast
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST));

            //3. recover Signal Noise
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));

            //4. recover Contour Smoothing
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTOUR_SMOTHING));

            //5. recover Judder reduction
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION));

            //6. recover Motion blir reduction
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION));

            //8. recover Clear action
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION));

            //9. recover Enhanced Viewing Angle
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));

        }

        ab_is_detect_hdmi_freesync[eAcfgInputGrp] = 0;

    }

    //refresh menu
    if (a_menu_is_resume())
    {
        menu_pm_repaint();
        menu_pm_refresh();
    }
}

static INT32 _cfg_hdmi_detect_freesync_flag_nfy_fct(UINT32  ui4_data)
{
    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR] _cfg_hdmi_detect_freesync_flag_nfy_fct(%d)\n", ui4_data));

    nav_request_context_switch (_cfg_detect_freesync_flag_action,(VOID*) ui4_data,NULL,NULL);
    return APP_CFGR_OK;
}

BOOL a_acfg_cust_is_detect_hdmi_freesync_flag(VOID)
{
    //return b_g_detect_hdmi_freesync_flag;
    return (g_ACFG_eCurVrrFreeSyncStatus == ACFG_VRR_STATUS_FREE_SYNC);
}

EnuAcfgVrrStatus acfg_cust_get_cur_VrrFreeSync_status(void)
{
    return g_ACFG_eCurVrrFreeSyncStatus;
}

BOOL acfg_cust_is_Vrr_or_FreeSync_detected(void)
{
    if( (g_ACFG_eCurVrrFreeSyncStatus == ACFG_VRR_STATUS_VRR)
      ||(g_ACFG_eCurVrrFreeSyncStatus == ACFG_VRR_STATUS_FREE_SYNC)
      )
    {
        return TRUE;
    }

    return FALSE;
}

void a_acfg_cust_reset_VRR_FreeSync_status(void)
{
    DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]a_acfg_cust_reset_VRR_FreeSync_status() \n"));
    g_ACFG_eCurVrrFreeSyncStatus = ACFG_VRR_STATUS_NONE;
}

ACFG_OLED_ERROR_DETECT_TYPE a_acfg_get_still_image_status(VOID)
{
    return t_still_image_status;
}

INT32 a_cfg_custom_set_oled_panel_display_time(UINT32 ui4_val)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_OLED_PANEL_DISPLAY_TIME, &ui4_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_get_oled_panel_display_time(UINT32 *pui4_val)
{
    SIZE_T      z_size = sizeof(UINT32);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_OLED_PANEL_DISPLAY_TIME, pui4_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_set_oled_jb_cooling_time(UINT16 ui2_val)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_OLED_JB_COOLING_TIME, &ui2_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_get_oled_jb_cooling_time(UINT16 *pui2_val)
{
    SIZE_T      z_size = sizeof(UINT16);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_OLED_JB_COOLING_TIME, pui2_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_set_oled_ex_factory_offrs_count(UINT16 ui2_val)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_OLED_OFFRS_COUNT, &ui2_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_get_oled_ex_factory_offrs_count(UINT16 *pui2_val)
{
    SIZE_T      z_size = sizeof(UINT16);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_OLED_OFFRS_COUNT, pui2_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_set_oled_ex_factory_jb_count(UINT16 ui2_val)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_OLED_JB_COUNT, &ui2_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_get_oled_ex_factory_jb_count(UINT16 *pui2_val)
{
    SIZE_T      z_size = sizeof(UINT16);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_OLED_JB_COUNT, pui2_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_custom_set_power_mode_save(UINT8 ui1_val)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_OLED_POWER_MODE_SAVE, &ui1_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    a_cfg_store();
    return i4_ret;
}

INT32 a_cfg_custom_get_power_mode_save(UINT8 *pui1_val)
{
    SIZE_T      z_size = sizeof(UINT8);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_OLED_POWER_MODE_SAVE, pui1_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT32 a_cfg_cust_drv_get_pq_ver_by_bin_type(UINT8 ui1_idx, UINT8 *aui1_val, SIZE_T z_size_val)
{
    INT32                       i4_ret = APP_CFGR_OK;
    CUST_SPEC_TYPE_GET_INFO_T   t_get_info = {0};
    DRV_CUSTOM_PQ_BIN_VER_T     t_pq_bin_ver = {0};
    SIZE_T                      z_size = sizeof(DRV_CUSTOM_PQ_BIN_VER_T);

    if((ui1_idx >= DRV_CUSTOM_PQ_TYPE_MAX) || (aui1_val == NULL))
    {
        DBG_ERROR(("[ACFG] input value is invalid at %s,%d\r\n",__FUNCTION__,__LINE__));
        return APP_CFGR_INV_ARG;
    }

    t_pq_bin_ver.e_pq_type = (DRV_CUSTOM_PQ_TYPE_T)ui1_idx;
    c_memset((VOID*)t_pq_bin_ver.ui1_pq_ver, 0, sizeof(t_pq_bin_ver.ui1_pq_ver));

    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_PQ_VER_BY_BIN_TYPE;
    t_get_info.pv_get_info = (VOID *)&t_pq_bin_ver;
    t_get_info.pz_size = &z_size;
    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);

    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[ACFG]  is NULL at %s,%d\r\n",__FUNCTION__,__LINE__));
        return i4_ret;
    }
    c_memcpy((VOID*)aui1_val,(VOID*)t_pq_bin_ver.ui1_pq_ver,z_size_val);

    return APP_CFGR_OK;
}

INT32 a_cfg_custom_set_oled_demo_mode_decline_time(INT64 t_val)
{
    INT32   i4_ret = APP_CFGR_OK;
    UINT32  ui4_time_l = t_val & 0xffffffff;
    UINT32  ui4_time_h = (t_val >> 32) & 0xffffffff;

    DBG_INFO(("[ACFG][%s %d]t_val:%lld ,ui4_time_h:0x%x,ui4_time_l:0x%x\n",__FUNCTION__,__LINE__,t_val,ui4_time_h,ui4_time_l));
    i4_ret = acfg_set(IDX_CUSTOM_OLED_DEMO_MODE_DECLINE_TIME_H, &ui4_time_h, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = acfg_set(IDX_CUSTOM_OLED_DEMO_MODE_DECLINE_TIME_L, &ui4_time_l, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT64 a_cfg_custom_get_oled_demo_mode_decline_time()
{
    SIZE_T      z_size = sizeof(UINT32);
    INT64        t_tmp = 0;
    UINT32  ui4_time_h = 0;
    UINT32  ui4_time_l = 0;

    acfg_get(IDX_CUSTOM_OLED_DEMO_MODE_DECLINE_TIME_H, &ui4_time_h, &z_size);
    acfg_get(IDX_CUSTOM_OLED_DEMO_MODE_DECLINE_TIME_L, &ui4_time_l, &z_size);

    t_tmp = ui4_time_h;
    t_tmp = (t_tmp << 32);
    t_tmp |= ui4_time_l;

    DBG_INFO(("[ACFG][%s %d]t_val:%lld ,ui4_time_h:%ld,ui4_time_l:%ld,sizeof(INT64)=%ld\n",__FUNCTION__,__LINE__,t_tmp,ui4_time_h,ui4_time_l,sizeof(INT64)));
    return t_tmp;
}

INT32 a_cfg_custom_set_oled_last_screen_refresh_time(INT64 t_val)
{
    INT32   i4_ret     = APP_CFGR_OK;
    UINT32  ui4_time_l = t_val & 0xffffffff;
    UINT32  ui4_time_h = (t_val >> 32) & 0xffffffff;

    DBG_INFO(("[ACFG][%s %d]t_val:%lld ,ui4_time_h:0x%x,ui4_time_l:0x%x\n",__FUNCTION__,__LINE__,t_val,ui4_time_h,ui4_time_l));
    i4_ret = acfg_set(IDX_CUSTOM_OLED_LAST_SCREEN_REFRESH_TIME_H, &ui4_time_h, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = acfg_set(IDX_CUSTOM_OLED_LAST_SCREEN_REFRESH_TIME_L, &ui4_time_l, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

INT64 a_cfg_custom_get_oled_last_screen_refresh_time()
{
    SIZE_T      z_size = sizeof(UINT32);
    INT64        t_tmp = 0;
    UINT32  ui4_time_h = 0;
    UINT32  ui4_time_l = 0;

    acfg_get(IDX_CUSTOM_OLED_LAST_SCREEN_REFRESH_TIME_H, &ui4_time_h, &z_size);
    acfg_get(IDX_CUSTOM_OLED_LAST_SCREEN_REFRESH_TIME_L, &ui4_time_l, &z_size);

    t_tmp = ui4_time_h;
    t_tmp  = t_tmp<<32;
    t_tmp |= ui4_time_l;

    DBG_INFO(("[ACFG][%s %d]t_val:%lld ,ui4_time_h:%ld,ui4_time_l:%ld,sizeof(INT64)=%ld\n",__FUNCTION__,__LINE__,t_tmp,ui4_time_h,ui4_time_l,sizeof(INT64)));

    return t_tmp;
}

INT32 a_cfg_custom_set_oled_ex_factory_display_time(UINT32 ui4_val)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_DISPLAY_TIME, &ui4_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    a_cfg_store();

    return i4_ret;
}

INT32 a_cfg_custom_get_oled_ex_factory_display_time(UINT32 *pui4_val)
{
    SIZE_T      z_size = sizeof(UINT32);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_DISPLAY_TIME, pui4_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return i4_ret;
}

INT32 a_cfg_custom_set_oled_ex_factory_offrs_time(UINT32 ui4_val)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_OFFRS_TIME, &ui4_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    a_cfg_store();

    return i4_ret;
}

INT32 a_cfg_custom_get_oled_ex_factory_offrs_time(UINT32 *pui4_val)
{
    SIZE_T      z_size = sizeof(UINT32);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_OFFRS_TIME, pui4_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return i4_ret;
}

INT32 a_cfg_custom_set_oled_ex_factory_jb_time(UINT32 ui4_val)
{
    INT32   i4_ret = APP_CFGR_OK;

    i4_ret = acfg_set(IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_JB_TIME, &ui4_val, 1);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    a_cfg_store();

    return i4_ret;
}

INT32 a_cfg_custom_get_oled_ex_factory_jb_time(UINT32 *pui4_val)
{
    SIZE_T      z_size = sizeof(UINT32);
    INT32       i4_ret = APP_CFGR_OK;

    i4_ret = acfg_get(IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_JB_TIME, pui4_val, &z_size);
    ACFG_CHK_FAIL(i4_ret, i4_ret);
    return i4_ret;
}

//================================================================================================
typedef enum
{
    ACFG_DV_STATUS_NONE,
    ACFG_DV_STATUS_DV_ACTIVE,
    ACFG_DV_STATUS_DV_GAME,
} EnuAcfgDvStatus;

typedef struct
{
    BOOL bInUsed;

    // Backup picture_mode
    UINT16 u16PicMode_Pre;
    BOOL bIs_PicMode_Pre_Valid;

    // Backup GLL
    INT16 i16GLL_Pre;
    BOOL bIs_GLL_Pre_Valid;

    // Backup VRR
    INT16 i16VRR_Pre;
    BOOL bIs_VRR_Pre_Valid;

} StruAcfgGameBackup;

typedef struct
{
    UINT8 au8_DV_Game_Status_Last[HDMI_PORT_NUM_MAX];

    // Backup UI setting
    StruAcfgGameBackup astAcfgGameBackup[HDMI_PORT_NUM_MAX];

} StruAcfgDVInfo;

static StruAcfgDVInfo g_stAcfgDVInfo = {0};

void acfg_cust_reset_DV_game_status(void)
{
    ui1_g_game_mode_flag = APP_CFG_VID_GAME_MODE_OFF;
}

void acfg_cust_Game_SwitchPictureMode( BOOL bIsGame, BOOL bSetGLL, BOOL bSetVRR, StruAcfgGameBackup* pstAcfgGameBackup )
{
    DBG_LOG_PRINT(("[ACFG][GAME] %s(bIsGame=%d, bSetGLL=%d, bSetVRR=%d)\n", __FUNCTION__, bIsGame, bSetGLL, bSetVRR ));

    INT32 i4_ret;
    BOOL bIs_picture_mode_changed = FALSE;
    BOOL bIs_GLL_changed = FALSE;
    BOOL bIs_VRR_changed = FALSE;

    // Get current Picture Mode
    UINT16 ui2_cur_pic_mode = menu_get_vid_pic_mode_idx();
    ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME]{%s,%d} ui2_cur_pic_mode:%d \n",__FUNCTION__,__LINE__, ui2_cur_pic_mode)); );

    if( bIsGame )
    {
        if( pstAcfgGameBackup->bInUsed )
        {
            DBG_LOG_PRINT(("[ACFG][GAME]{%s,%d} Warning: Already changed! => skip\n", __FUNCTION__,__LINE__));
            return ;
        }

        // (1) Switch picture_mode to Game ...
        if( ui2_cur_pic_mode != ACFG_CUST_PIC_MODE_GAME )
        {
            // Backup current picture_mode
            pstAcfgGameBackup->u16PicMode_Pre = ui2_cur_pic_mode;
            pstAcfgGameBackup->bIs_PicMode_Pre_Valid = TRUE;
            pstAcfgGameBackup->bInUsed = TRUE;

            DBG_LOG_PRINT(("[ACFG][GAME]{%s,%d} Auto change picture_mode: %d --> GAME\n", __FUNCTION__, __LINE__, ui2_cur_pic_mode ));
            menu_set_vid_pic_mode_idx(ACFG_CUST_PIC_MODE_GAME);
            bIs_picture_mode_changed = TRUE;
        }

        // (2) Change GLL to on if needed ...
        if( bSetGLL )
        {
            INT16 i16CurGLL = 0;
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i16CurGLL);
            if(i4_ret != APP_CFGR_OK)
            {
                DBG_LOG_PRINT(("[ACFG][GAME][GLL] {%s,%d} Error: Cannot get GLL!!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i4_ret));
                return;
            }
            ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s,%d} i16CurGLL:%d \n",__FUNCTION__,__LINE__, i16CurGLL)); );

            if(i16CurGLL != ACFG_CUST_GAME_LOW_LATENCY_ON) // Change GLL to on if needed
            {
                // Backup current GLL
                pstAcfgGameBackup->i16GLL_Pre = i16CurGLL;
                pstAcfgGameBackup->bIs_GLL_Pre_Valid = TRUE;
                pstAcfgGameBackup->bInUsed = TRUE;

                // Force GLL of PictureMode_Game to on...
                DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s,%d} Auto change GLL: %d --> ON\n", __FUNCTION__,__LINE__, i16CurGLL));
                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), (INT16)ACFG_CUST_GAME_LOW_LATENCY_ON);
                bIs_GLL_changed = TRUE;
            }
        }


        // (3) Change VRR to on if needed
        if(bSetVRR)
        {
            INT16 i16CurVRR = 0;
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i16CurVRR);
            if(i4_ret != APP_CFGR_OK)
            {
                DBG_LOG_PRINT(("[ACFG][GAME][VRR] {%s,%d} Error: Cannot get VRR!!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i4_ret));
                return;
            }
            ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][VRR]{%s,%d} i16CurVRR:%d \n", __FUNCTION__,__LINE__, i16CurVRR)); );
            if(i16CurVRR != ACFG_CUST_COMMON_ON)
            {
                // Backup current GLL
                pstAcfgGameBackup->i16VRR_Pre = i16CurVRR;
                pstAcfgGameBackup->bIs_VRR_Pre_Valid = TRUE;
                pstAcfgGameBackup->bInUsed = TRUE;

                // Force VRR of PictureMode_Game to on...
                DBG_LOG_PRINT(("[ACFG][GAME][VRR]{%s,%d} Auto change VRR: %d --> ON\n", __FUNCTION__,__LINE__, i16CurVRR));
                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), (INT16)ACFG_CUST_COMMON_ON);
                bIs_VRR_changed = TRUE;
            }
        }

    }
    else
    {
        if( FALSE == pstAcfgGameBackup->bInUsed )
        {
            DBG_LOG_PRINT(("[ACFG][GAME]{%s,%d} Warning: No backup data! => skip\n", __FUNCTION__,__LINE__));
            return ;
        }

        pstAcfgGameBackup->bInUsed = FALSE;

        // (1) Recovery GLL of picture_mode-Game...
        if( bSetGLL )
        {
            if( pstAcfgGameBackup->bIs_GLL_Pre_Valid ) // Need to recovery
            {
                pstAcfgGameBackup->bIs_GLL_Pre_Valid = 0;

                if( ui2_cur_pic_mode == ACFG_CUST_PIC_MODE_GAME ) // Picture_mode no changed
                {
                    INT16 i16CurGLL = 0;
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i16CurGLL);
                    if(i4_ret != APP_CFGR_OK)
                    {
                        DBG_LOG_PRINT(("[ACFG][GAME][GLL] {%s,%d} Error: Cannot get GLL!!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i4_ret));
                        return;
                    }
                    ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s,%d} i16CurGLL:%d \n",__FUNCTION__,__LINE__, i16CurGLL)); );

                    if( i16CurGLL != pstAcfgGameBackup->i16GLL_Pre )
                    {
                        DBG_LOG_PRINT(("[ACFG][chg_timing][VRR]{%s,%d} Recovery GLL: ON --> %d\n", __FUNCTION__,__LINE__, pstAcfgGameBackup->i16GLL_Pre ));
                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), pstAcfgGameBackup->i16GLL_Pre );
                        bIs_GLL_changed = TRUE;
                    }
                }
                else // Picture_mode already changed ...
                {
                    // No need to recover
                    ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][GLL]{%s,%d} Picture_mode not Game => Can't recovery GLL \n",__FUNCTION__,__LINE__ )); );
                }
            }
        }


        // (2) Recovery VRR of picture_mode-Game...
        if( bSetVRR )
        {
            if( pstAcfgGameBackup->bIs_VRR_Pre_Valid ) // Need to recovery
            {
                pstAcfgGameBackup->bIs_VRR_Pre_Valid = 0;

                if( ui2_cur_pic_mode == ACFG_CUST_PIC_MODE_GAME ) // Picture_mode no changed
                {
                    // Get current VRR
                    INT16 i16CurVRR = 0;
                    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i16CurVRR);
                    if(i4_ret != APP_CFGR_OK)
                    {
                        DBG_LOG_PRINT(("[ACFG][GAME][VRR] {%s,%d} Error: Cannot get VRR!!!! i4_ret:%d\n", __FUNCTION__,__LINE__, i4_ret));
                        return;
                    }
                    ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][VRR]{%s,%d} i16CurVRR:%d \n",__FUNCTION__,__LINE__, i16CurVRR)); );

                    if( i16CurVRR != pstAcfgGameBackup->i16VRR_Pre )
                    {
                        DBG_LOG_PRINT(("[ACFG][GAME][VRR]{%s,%d} Recovery VRR: ON --> %d\n", __FUNCTION__,__LINE__, pstAcfgGameBackup->i16VRR_Pre ));
                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), pstAcfgGameBackup->i16VRR_Pre );
                        bIs_VRR_changed = TRUE;
                    }
                }
                else // Picture_mode already changed ...
                {
                    // No need to recover
                    ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME][VRR]{%s,%d} Picture_mode not Game => Can't recovery VRR \n",__FUNCTION__,__LINE__ )); );
                }
            }
        }


        // (3) Restore previous picture mode ...
        //Case1: no ones switch picture mode, so recover pre picture mode
        //Case2: After switch game picture mode, someone switch picture mode to other, so no process

        //  Check if need to recovery picture_mode
        //BOOL bPictureMode_changed = FALSE;
        if( pstAcfgGameBackup->bIs_PicMode_Pre_Valid )
        {
            pstAcfgGameBackup->bIs_PicMode_Pre_Valid = 0;

            if( ui2_cur_pic_mode == ACFG_CUST_PIC_MODE_GAME ) // No switch picture_mode && ui2_pre_pic_mode != ACFG_CUST_PIC_MODE_GAME)
            {
                if( pstAcfgGameBackup->u16PicMode_Pre != ACFG_CUST_PIC_MODE_GAME )
                {
                    DBG_LOG_PRINT(("[ACFG][GAME]{%s,%d} Recovery picture_mode: GAME --> %d\n", __FUNCTION__,__LINE__, pstAcfgGameBackup->u16PicMode_Pre ));
                    menu_set_vid_pic_mode_idx( pstAcfgGameBackup->u16PicMode_Pre );
                    bIs_picture_mode_changed = TRUE;
                }
            }
            else // Picture_mode already changed by user
            {
                // No need to recover picture_mode
                ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME]{%s,%d} Picture_mode changed => Won't recovery picture_mode \n",__FUNCTION__,__LINE__ )); );
            }
        }
    }


    // Direct some relative setting ...
    if( bIs_picture_mode_changed )
    {
        ACFG_DEBUG_GAME( DBG_LOG_PRINT(("[ACFG][GAME]{%s,%d} Picture_mode changed ~ \n",__FUNCTION__,__LINE__ )); );
    }
    else
    {
    #if(VZO_DV__GLL_CONTROL_BY_DV_GAME)
       bIs_GLL_changed = TRUE;
    #endif
    }

    if( bIs_GLL_changed )
    {
        //a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY));
        //a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE));
        acfg_cust_video_update_GLL_all(FALSE);
    }

    if( bIs_VRR_changed )
    {
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE));

        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION));
    }
}


//Note: vizio use d_interface Turn on/off game mode
//dobly vision content don't need consider ALLM (Auto Low Latency Mode), only consider game mode flag
//i4_ret = a_cfg_cust_drv_set_game_mode(APP_CFG_VID_GAME_MODE_ON);

//Please see attached for updated spec. When AMD VSIF is detected:
//1. Change to game picture mode.
//2. Game Low Latency is set to ON.
//3. Variable Refresh Rate is set to ON.
INT32 a_cfg_custom_switch_dv_game_mode(UINT8 ui1_dv_game_mode_flag)
{
    //INT32  i4_ret = 0;

    UINT8 u8CurHdmi_UI_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();

    DBG_LOG_PRINT(("[ACFG][chg_timing][DV][GAME] %s(ui1_dv_game_mode_flag=%d), u8CurHdmi_UI_Idx:%d\n", __FUNCTION__,
        ui1_dv_game_mode_flag, u8CurHdmi_UI_Idx ));

    // If not HDMI, do nothing
    if( u8CurHdmi_UI_Idx >= HDMI_PORT_NUM_MAX )
    {
        DBG_LOG_PRINT(("[ACFG][DV][GAME] {%s,%d} Error: Invalid u8CurHdmi_UI_Idx:%d !!!!\n",__FUNCTION__,__LINE__, u8CurHdmi_UI_Idx));
        acfg_cust_reset_DV_game_status(); // Force off
        return APP_CFGR_INTERNAL_ERR;
    }

    //Set dv game mode flag-1 ...
    if( ui1_dv_game_mode_flag != ui1_g_game_mode_flag )
    {
        DBG_LOG_PRINT(("[ACFG][DV][GAME]{%s,%d} Current DV_Game status: %d -> %d\n", __FUNCTION__, __LINE__, ui1_g_game_mode_flag, ui1_dv_game_mode_flag ));
        ui1_g_game_mode_flag = ui1_dv_game_mode_flag;
    }

    // Check dv_game status change...
    if( ui1_dv_game_mode_flag == g_stAcfgDVInfo.au8_DV_Game_Status_Last[u8CurHdmi_UI_Idx] )
    {
        return APP_CFGR_NO_ACTION;
    }
    else
    {
        //Set dv game mode flag-2 ...
        ACFG_DEBUG_LOG( ACFG_DBG_DV,
            DBG_LOG_PRINT(("[ACFG][DV][GAME]{%s,%d} Set au8_DV_Game_Status_Last[%d]: %d -> %d\n",
                    __FUNCTION__, __LINE__, u8CurHdmi_UI_Idx, g_stAcfgDVInfo.au8_DV_Game_Status_Last[u8CurHdmi_UI_Idx], ui1_dv_game_mode_flag ));
        );
        g_stAcfgDVInfo.au8_DV_Game_Status_Last[u8CurHdmi_UI_Idx] = ui1_dv_game_mode_flag;
    }


    if(ui1_dv_game_mode_flag == APP_CFG_VID_GAME_MODE_ON)
    {
        ACFG_DEBUG_LOG( ACFG_DBG_DV,
            DBG_LOG_PRINT(("[ACFG][DV][GAME]{%s,%d} dv_game_mode is on ...\n", __FUNCTION__, __LINE__  ));
        );

        BOOL bSetGLL = FALSE; // No need for DV_Game
        BOOL bSetVRR = FALSE; // No need for DV_Game

        // Switch picture_mode to game/GLL to on/VRR to On
        acfg_cust_Game_SwitchPictureMode( TRUE, bSetGLL, bSetVRR, &(g_stAcfgDVInfo.astAcfgGameBackup[u8CurHdmi_UI_Idx]) );
    }
    else
    {
        ACFG_DEBUG_LOG( ACFG_DBG_DV,
            DBG_LOG_PRINT(("[ACFG][DV][GAME]{%s,%d} dv_game_mode is OFF ...\n", __FUNCTION__, __LINE__  ));
        );

        BOOL bSetGLL = FALSE; // No need for DV_Game
        BOOL bSetVRR = FALSE; // No need for DV_Game

        // Restore previous picture mode/GLL/VRR
        acfg_cust_Game_SwitchPictureMode( FALSE, bSetGLL, bSetVRR, &(g_stAcfgDVInfo.astAcfgGameBackup[u8CurHdmi_UI_Idx]) );
    }

    //if menu exist, refresh menu
    if( a_menu_is_resume() )
    {
        menu_pm_repaint();
        menu_pm_refresh();
    }

    BOOL bIs_support_game_low_latency = a_cfg_cust_is_support_game_low_latency();
    DBG_LOG_PRINT(("[ACFG][DV][GAME] %s: %d: bIs_support_game_low_latency=%d\n", __FUNCTION__,__LINE__, bIs_support_game_low_latency));
    if( bIs_support_game_low_latency )
    {
        a_acfg_update_gaming_logo();
    }

    return APP_CFGR_OK;
}

INT32 a_cfg_cust_drv_set_backlight_status(BOOL b_enable)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set b_enable :%d \r\n",b_enable);

    SIZE_T z_size = sizeof(b_enable);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_BACKLIGHT;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&b_enable;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_drv_get_backlight_status(BOOL *b_enable)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(BOOL);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_BACKLIGHT;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)b_enable;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);
    return i4_ret;
}

static VOID _cfg_tv_soure_av_update_delay_action (
            VOID*                       pv_tag1,
            VOID*                       pv_tag2,
            VOID*                       pv_tag3 )
{
    if(a_acfg_cust_get_video_type() == SCC_VID_PQ_SDR)
    {
        ACFG_LOG_ON_FAIL(a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE)));
    }
}


static VOID _cfg_tv_soure_av_update_delay_cb_fct(HANDLE_T  pt_tm_handle,
                                            VOID*     pv_tag)
{
    nav_request_context_switch (_cfg_tv_soure_av_update_delay_action,NULL,NULL,NULL);
}


static VOID _cfg_tv_soure_av_update_delay (VOID)
{
    if(h_tv_source_av_update_delay_timer == NULL_HANDLE)
    {
        if(OSR_OK != c_timer_create(&h_tv_source_av_update_delay_timer))
        {
            DBG_LOG_PRINT(("[ACFG] create timer fail\n"));
            return;
        }
    }

    c_timer_stop(h_tv_source_av_update_delay_timer);
    c_timer_start(h_tv_source_av_update_delay_timer,
                                 TV_SOURCE_AV_UPDATE_DELAY_1000,
                                 X_TIMER_FLAG_ONCE,
                                 _cfg_tv_soure_av_update_delay_cb_fct,
                                 NULL);
}

INT32 a_cfg_cust_set_panel_ssc_en(BOOL b_enable)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set b_enable :%d \r\n",b_enable);

    SIZE_T z_size = sizeof(b_enable);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_PANEL_SSC_EN;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&b_enable;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_trigger_led_ac_on_ready_action(void)
{
    INT32 i4_ret = 0;
    BOOL b_enable = TRUE;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set led b_enable :%d \r\n",b_enable);

    SIZE_T z_size = sizeof(b_enable);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_AC_ON_TO_STDBY_LED;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&b_enable;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}
// DCR or LocalDimming
// DCR: INT32 VIZIO_BACKLIGHT_CONTROL_D_SET(UINT16 ui2_idx)
// LD: INT32 VIZIO_EXTREME_BLACK_ENGINE_D_SET(UINT16 ui2_idx)
//
INT32 ACFG_CustDrv_Set_BacklightCtrl( INT8 iBacklightCtrl )
{
    ACFG_DEBUG_BACKLIGHT( DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL] {%s: %d} iBacklightCtrl:%d\n", __FUNCTION__,__LINE__, iBacklightCtrl)); );

    if( (iBacklightCtrl < 0)
      ||(iBacklightCtrl > 1)
      )
    {
        DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL] {%s: %d} Error: Para wrong! iBacklightCtrl:%d\n", __FUNCTION__,__LINE__, iBacklightCtrl));
        return APP_CFGR_INV_ARG;
    }

    BOOL b_support_local_dimming = a_cfg_cust_get_support_local_dimming();
    //ACFG_DEBUG_BACKLIGHT( DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL] {%s: %d} b_support_local_dimming:%d\n", __FUNCTION__,__LINE__, b_support_local_dimming)); );

    INT32 i4_ret = 0;
    if(b_support_local_dimming) // Local Dimming
    {
        INT16 u16LD_Val = iBacklightCtrl;
        ACFG_DEBUG_BACKLIGHT( DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL] {%s: %d} Call VIZIO_EXTREME_BLACK_ENGINE_D_SET(%d)\n", __FUNCTION__,__LINE__, u16LD_Val)); );
        i4_ret = VIZIO_EXTREME_BLACK_ENGINE_D_SET_FORCE(u16LD_Val);
        if( i4_ret < 0 )
        {
            DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL] {%s: %d} Error: VIZIO_EXTREME_BLACK_ENGINE_D_SET() failed!(rtn:%d,u16LD_Val:%d, iBacklightCtrl:%d)\n",
                                            __FUNCTION__,__LINE__, i4_ret, u16LD_Val, iBacklightCtrl));
            return APP_CFGR_INTERNAL_ERR;
        }
    }
    else // DCR:
    {
        INT16 i2_dcr_val = iBacklightCtrl;
        ACFG_DEBUG_BACKLIGHT( DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL] {%s: %d} Call VIZIO_BACKLIGHT_CONTROL_D_SET_4VLOGO(%d)\n", __FUNCTION__,__LINE__, i2_dcr_val)); );
        i4_ret = VIZIO_BACKLIGHT_CONTROL_D_SET_FORCE(i2_dcr_val);
        if( i4_ret < 0 )
        {
            DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL] {%s: %d} Error: VIZIO_BACKLIGHT_CONTROL_D_SET() failed!(rtn:%d,i2_dcr_val:%d, iBacklightCtrl:%d)\n",
                                                __FUNCTION__,__LINE__, i4_ret, i2_dcr_val, iBacklightCtrl));
            return APP_CFGR_INTERNAL_ERR;
        }
    }

#if 0
    UINT16 ui2_scc_val = iBacklightCtrl;

    //#define SN_PRES_MAIN_DISPLAY  "snk_MainDisp"     /**<        */
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1]={0};
    c_strcpy(s_disp_name, SN_PRES_MAIN_DISPLAY);

    ACFG_DEBUG_BACKLIGHT(
        DBG_LOG_PRINT(("[ACFG][BACKLIGHT] Call scc( s_disp_name[]={%s}, SCC_CMD_CODE_DISP_ADP_BACK_LIGHT, ui2_scc_val = %d\n",
                        s_disp_name, ui2_scc_val ));
    );

    /* Step 3: get from individual group */
    SM_COMMAND_T    at_sm_cmds[4] = {0};
    at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_DISP;
    at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text     = s_disp_name;
    at_sm_cmds[2].e_code        = SCC_CMD_CODE_DISP_ADP_BACK_LIGHT;
    at_sm_cmds[2].u.ui4_data    = ui2_scc_val;
    at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
    at_sm_cmds[3].u.ui4_data    = 0;

    INT32 i4_ret = c_scc_comp_grp_set(at_sm_cmds);
    if (i4_ret < 0)
    {
        DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL] {%s: %d} Error: set SCC backlight_ctrl failed!(rtn:%d,u16Backlight:%d, iBacklightCtrl:%d)\n", __FUNCTION__,__LINE__, i4_ret, u16Backlight, iBacklightCtrl));
        return APP_CFGR_INTERNAL_ERR;
    }
#endif

    return APP_CFGR_OK;
}

// If iBacklightCtrl > 0, then also control "BacklightCtrl"
INT32 ACFG_CustDrv_Set_Backlight( UINT16 u16Backlight, INT8 iBacklightCtrl )
{
    ACFG_DEBUG_BACKLIGHT( DBG_LOG_PRINT(("[ACFG][BACKLIGHT] {%s: %d} u16Backlight:%d, iBacklightCtrl:%d\n", __FUNCTION__,__LINE__, u16Backlight, iBacklightCtrl)); );

    INT32 i4_ret = 0;

    if( (iBacklightCtrl >= 0) )
    {
        i4_ret = ACFG_CustDrv_Set_BacklightCtrl(iBacklightCtrl);
        if (i4_ret < 0)
        {
            DBG_LOG_PRINT(("[ACFG][BACKLIGHT] {%s: %d} Error: acfg_CustDrv_Set_BacklightCtrl failed!(rtn:%d,u16Backlight:%d, iBacklightCtrl:%d)\n", __FUNCTION__,__LINE__, i4_ret, u16Backlight, iBacklightCtrl));
            return APP_CFGR_INTERNAL_ERR;
        }
    }


    UINT16 ui2_scc_val = u16Backlight;

    //#define SN_PRES_MAIN_DISPLAY  "snk_MainDisp"     /**<        */
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1]={0};
    c_strcpy(s_disp_name, SN_PRES_MAIN_DISPLAY);

    ACFG_DEBUG_BACKLIGHT(
        DBG_LOG_PRINT(("[ACFG][BACKLIGHT] Call scc( SCC_CMD_TYPE_DISP, s_disp_name[]={%s}, SCC_CMD_CODE_DISP_BACK_LIGHT, ui2_scc_val = %d\n",
                        s_disp_name, ui2_scc_val ));
    );


    /* Step 3: get from individual group */
    SM_COMMAND_T    at_sm_cmds[4] = {0};
    at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_DISP;
    at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text     = s_disp_name;
    at_sm_cmds[2].e_code        = SCC_CMD_CODE_DISP_BACK_LIGHT;
    at_sm_cmds[2].u.ui4_data    = ui2_scc_val;
    at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
    at_sm_cmds[3].u.ui4_data    = 0;

    i4_ret = c_scc_comp_grp_set(at_sm_cmds);
    if (i4_ret < 0)
    {
        DBG_LOG_PRINT(("[ACFG][BACKLIGHT] {%s: %d} Error: set scc backlight failed!(rtn:%d,u16Backlight:%d, iBacklightCtrl:%d)\n", __FUNCTION__,__LINE__, i4_ret, u16Backlight, iBacklightCtrl));
        return APP_CFGR_INTERNAL_ERR;
    }

    dtv_svc_write_timestamp("[LOGO] Set backlight done");
    return APP_CFGR_OK;
}

//=========================================================
BOOL acfg_custom_get_enable_soundbarsettings(VOID)
{
    return nav_cec_custom_get_enable_soundbarsettings();
}

BOOL acfg_custom_get_soundbarsettings_ready(VOID)
{
    return nav_cec_custom_get_soundbarsettings_ready();
}

BOOL acfg_custom_get_enable_eq(VOID)
{
    return nav_cec_custom_get_enable_eq();
}

BOOL acfg_custom_get_enable_bass(VOID)
{
    return nav_cec_custom_get_enable_bass();
}

BOOL acfg_custom_get_enable_treble(VOID)
{
    return nav_cec_custom_get_enable_treble();
}

BOOL acfg_custom_get_enable_dialogue(VOID)
{
    return nav_cec_custom_get_enable_dialogue();
}

BOOL acfg_custom_get_enable_subwoofer(VOID)
{
    return nav_cec_custom_get_enable_subwoofer();
}

BOOL acfg_custom_get_enable_nightmode(VOID)
{
    return nav_cec_custom_get_enable_nightmode();
}

BOOL acfg_custom_get_enable_virtual(VOID)
{
    return nav_cec_custom_get_enable_virtual();
}

BOOL acfg_custom_get_eq_mode_enable_music(VOID)
{
    return nav_cec_custom_get_eq_mode_enable_music();
}

BOOL acfg_custom_get_eq_mode_enable_movie(VOID)
{
    return nav_cec_custom_get_eq_mode_enable_movie();
}

BOOL acfg_custom_get_eq_mode_enable_game(VOID)
{
    return nav_cec_custom_get_eq_mode_enable_game();
}

BOOL acfg_custom_get_eq_mode_enable_direct(VOID)
{
    return nav_cec_custom_get_eq_mode_enable_direct();
}

BOOL acfg_custom_get_eq_mode_enable_dialogue(VOID)
{
    return nav_cec_custom_get_eq_mode_enable_dialogue();
}

UINT8 acfg_custom_get_eq_mode_type(VOID)
{
    return nav_cec_custom_get_enable_eq_mode_type();
}

VOID acfg_custom_set_eq_mode_type(UINT8 eq_mode_type)
{
    nav_cec_custom_set_enable_eq_mode_type(eq_mode_type);
}

UINT8 acfg_custom_get_eq_mode_valid_num(VOID)
{
    return nav_cec_custom_get_enable_eq_mode_valid_num();
}

UINT8 acfg_custom_get_bass_type(VOID)
{
    return nav_cec_custom_get_enable_bass_type();
}

UINT8 acfg_custom_get_treble_type(VOID)
{
    return nav_cec_custom_get_enable_treble_type();
}

UINT8 acfg_custom_get_dialogue_type(VOID)
{
    return nav_cec_custom_get_enable_dialogue_type();
}

UINT8 acfg_custom_get_subwoofer_type(VOID)
{
    return nav_cec_custom_get_enable_subwoofer_type();
}

UINT8 acfg_custom_get_nightmode_type(VOID)
{
    return nav_cec_custom_get_enable_nightmode_type();
}

UINT8 acfg_custom_get_virtualx_type(VOID)
{
    return nav_cec_custom_get_enable_virtualx_type();
}

//=================================================================
INT32 acfg_custom_set_eq_mode(INT32 i4_val)
{
    return nav_cec_custom_set_eq_mode(i4_val);
}

INT32 acfg_custom_set_bass_val(INT32 i4_val)
{
    return nav_cec_custom_set_bass_val(i4_val);
}

INT32 acfg_custom_set_treble_val(INT32 i4_val)
{
    return nav_cec_custom_set_treble_val(i4_val);
}

INT32 acfg_custom_set_dialogue_val(INT32 i4_val)
{
    return nav_cec_custom_set_dialogue_val(i4_val);
}

INT32 acfg_custom_set_subwoofer_val(INT32 i4_val)
{
    return nav_cec_custom_set_subwoofer_val(i4_val);
}

INT32 acfg_custom_set_nightmode_val(INT32 i4_val)
{
    return nav_cec_custom_set_nightmode_val(i4_val);
}

INT32 acfg_custom_set_virtualx_val(INT32 i4_val)
{
    return nav_cec_custom_set_virtualx_val(i4_val);
}

INT32 acfg_custom_set_speakertest_val(INT32 i4_val)
{
    return nav_cec_custom_set_speakertest_val(i4_val);
}

INT32 acfg_custom_set_info_val(INT32 i4_val)
{
    return nav_cec_custom_set_info_val(i4_val);
}
INT32 a_cfg_cust_set_demura(BOOL b_enable)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    ACFG_DBG_INFO("Set b_enable :%d \r\n",b_enable);

    SIZE_T z_size = sizeof(b_enable);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_DEMURA;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&b_enable;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_get_demura(UINT32 *pu4_RegValue)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;

    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size     = sizeof(BOOL);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_DEMURA;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pu4_RegValue;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv);
    return i4_ret;
}

INT32 a_cfg_cust_set_LED_indicator(VOID* pv_data, SIZE_T z_size_val)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_LED_INDICATOR;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)pv_data;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size_val;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

INT32 a_cfg_cust_set_LED_light_rate(UINT8 u8light_rate)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T	 t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_LED_LIGHT_RATE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&u8light_rate;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );

    return i4_ret;
}

