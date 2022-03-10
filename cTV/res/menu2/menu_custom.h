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
 * $RCSfile: menu_custom.h,v $
 * $Revision: #3 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/14 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 530b5f614fc48ad655af79370de4cf1b $
 *
 * Description:
 *         This file contains the declarations of APPLICATION-RELATED functions
 * of the MENU applcation.
 *---------------------------------------------------------------------------*/

#ifndef _MENU_CUSTOM_H_
#define _MENU_CUSTOM_H_


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <unistd.h>

#include "u_common.h"
#include "u_handle.h"
#include "u_sys_name.h"
#include "u_sb.h"
#include "u_time_msrt.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_page_tree.h"

#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "nav/sleep/a_sleep.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "wdk/widget/wdk_widget.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "app_util/mapi_common/mapi_common.h"
#include "app_util/splayer/splayer.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define MENU_DEBUG_TIME(x)  // x

extern UINT32 g_menu_u32_sys_tick_period;
extern UINT32 g_menu_u32_sys_tick_last;

#if 0
#define MENU_DEBUG_TIME_CHECK_POINT()   do { \
    UINT32 u32_sys_tick = c_os_get_sys_tick(); \
    DBG_LOG_PRINT(("[daniel][MENU][TIME]{%s,%d} %d, %d, %d\n", __FUNCTION__, __LINE__, \
        u32_sys_tick, \
        u32_sys_tick*g_menu_u32_sys_tick_period, \
        (u32_sys_tick-g_menu_u32_sys_tick_last)*g_menu_u32_sys_tick_period )); \
    g_menu_u32_sys_tick_last = u32_sys_tick; \
} while(0)
#else
    #define MENU_DEBUG_TIME_CHECK_POINT()
#endif
//=================================================================

#define MENU_DEBUG_TIMEOUT(x)   //x
//=================================================================
#if 0 // debug backlight
#define MENU_DEBUG_BACKLIGHT(x) do { \
        { \
            x; \
        } \
    } while(0)
#else
#define MENU_DEBUG_BACKLIGHT(x)
#endif
//=================================================================

#define MENU_DEBUG_KEY(x)       //x

#define MENU_DEBUG_HOT_KEY(x)   //x

#define MENU_DEBUG_KEY_PIC(x)   //x

#define MENU_DEBUG_KEY_ASPECT_RATIO(x) //x

#define MENU_DEBUG_SHORT_CUT(x)     //x

#define MENU_DEBUG_PIC_MODE(x)      //x

#define MENU_DEBUG_ASPECT_RATIO(x)  //x

#define MENU_DEBUG_KEY_INPUT_SRC(x) //x
#define MENU_DEBUG_INPUT_SRC(x)     //x


#define MENU_DEBUG_HELP(x)      //x

#define MENU_DEBUG_FOCUS(x)     //x

//=================================================================

// MVD-1913/MVV-9526:PIC and WIDE key deep links to setting in sidebar
#define MENU_SUPPORT_HOT_KEY_PIC        1

#define MENU_SUPPORT_HOT_KEY_ASPECT_RATIO   1
#if(MENU_SUPPORT_HOT_KEY_ASPECT_RATIO)
extern UINT16 g_menu_u16_item_id_PICTURE_ASPECT_RATIO;
#endif
//=================================================================

#define MENU_COLOR_CALI_ENABLE_CALI_TEST    1

//=================================================================


typedef struct _MENU_CUSTOM_T {
    UINT16      ui2_acfg_gl_nfy;
    UINT16      ui2_acfg_inp_src_nfy;
    UINT16      ui2_acfg_nav_nfy;
    UINT16      ui2_icl_aud_nfy;
    UINT16      ui2_icl_ddp_nfy;
    UINT16      ui2_acfg_audio_nfy;
    UINT16      ui2_acfg_video_nfy;
    UINT16      ui2_acfg_disp_nfy;
    UINT16      ui2_acfg_cc_nfy;
    UINT16      ui2_acfg_custom_base_nfy;
    UINT16      ui2_acfg_tv_name_nfy;
    UINT16      ui2_acfg_hdr_nfy;
} MENU_CUSTOM_T;

typedef enum {
    BLK_SCRN_NORMAL,
    BLK_SCRN_OLED_NO_SIGNAL,
    BLK_SCRN_OLED_STILL_IMAGE,
    BLK_SCRN_OLED_SMART_UI,     // no action in smart cast/3rd app/native app ui
} MENU_CUSTOM_BLK_SCRN_MODE;

#define BLK_SCRN_OLED_NO_SIGNAL_DELAY   (1000 * 60)
#define BLK_SCRN_OLED_STILL_IMAGE_DELAY (1000 * 60 * 9)

#define BLK_SCRN_OLED_SMART_UI_DELAY    (1000 * 60 * 2)

#define BLK_SCRN_OLED_TOAST_NTY         (1000 * 30)

#ifndef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
#define NEW_TIME_LOCAL_AUTO_DST_SUPPORT
#endif
/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
extern MENU_CUSTOM_T        t_g_menu_custom;

/* settings definition */
extern MENU_ITEM_T          t_g_menu_custom_item_page_bass_treble;
extern MENU_ITEM_T          t_g_menu_custom_item_gui_lang;
extern MENU_ITEM_T          t_g_menu_custom_item_energy_saving_mode;
extern MENU_ITEM_T          t_g_menu_custom_item_aud_lang;
extern MENU_ITEM_T          t_g_menu_custom_item_time_zone;
extern MENU_ITEM_T          t_g_menu_custom_item_time_dls;
extern MENU_ITEM_T          t_g_menu_custom_item_auto_update_time;
extern MENU_ITEM_T          t_g_menu_custom_item_block_unrated;
extern MENU_ITEM_T          t_g_menu_custom_item_vga_clr_tmp_mode;
extern MENU_ITEM_T          t_g_menu_custom_item_vid_dcr;
extern MENU_ITEM_T          t_g_menu_custom_item_vid_lit_sns;
extern MENU_ITEM_T          t_g_menu_custom_item_gamma;
extern MENU_ITEM_T          t_g_menu_custom_item_cc;
extern MENU_ITEM_T          t_g_menu_custom_item_cc_on_mute;
extern MENU_ITEM_T		    t_g_menu_custom_item_cc_enabled;
extern MENU_ITEM_T          t_g_menu_custom_item_cc_ana;
extern MENU_ITEM_T          t_g_menu_custom_item_cc_dig;
extern MENU_ITEM_T          t_g_menu_custom_item_vid_size_h;
extern MENU_ITEM_T          t_g_menu_custom_item_vid_size_v;

extern MENU_ITEM_T          t_g_menu_custom_item_slideshow_repeat;
extern MENU_ITEM_T          t_g_menu_custom_item_slideshow_shuffle;
extern MENU_ITEM_T          t_g_menu_custom_item_slideshow_speed;
extern MENU_ITEM_T          t_g_menu_custom_item_slideshow_fullscreen;

extern MENU_ITEM_T          t_g_menu_custom_item_lst_additional_scan;
extern MENU_ITEM_T          t_g_menu_custom_item_ch_scan;
extern MENU_ITEM_T          t_g_menu_custom_item_user_ctrl_lock;
extern MENU_ITEM_T          t_g_menu_custom_item_reset_channel_lock;

extern MENU_ITEM_T          t_g_menu_custom_item_ana_aud_out;

extern MENU_ITEM_T          t_g_menu_custom_item_input_src;

extern MENU_ITEM_T          t_menu_item_page_tuner_setup;
extern MENU_ITEM_T          t_menu_item_page_network_setup;
extern MENU_ITEM_T          t_menu_item_voice_remote;

extern MENU_ITEM_T          t_menu_item_page_wifi_remote_setup;

extern MENU_ITEM_T          t_menu_item_page_wifi_device_setup;


extern HANDLE_T 			h_g_last_shadow_item ;
extern HANDLE_T             h_g_input_source_wgt;
extern HANDLE_T             h_g_page_naming_inp_lable;
extern HANDLE_T             h_g_aud_lang_list_wgt;
extern HANDLE_T             h_g_cc_digital_style_wgt;
/* 3D setting */
extern MENU_PAGE_FCT_TBL_T  t_g_menu_custom_page_3D_setting;

/* MMP sider menu */
extern MENU_PAGE_FCT_TBL_T  t_g_menu_custom_page_mmp_dev_list;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_custom_page_mmp_media_type;

extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_vid_position;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_vid_size;

/* pages definition */
#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
extern MENU_PAGE_FCT_TBL_T  t_g_menu_custom_page_time_local_setting_auto_dst;
#else
extern MENU_PAGE_FCT_TBL_T  t_g_menu_custom_page_time_local_setting;
#endif

#ifdef APP_2K12_RETAIL_DEMO_MODE
extern MENU_ITEM_T          t_menu_item_page_demo_mode_start;
extern MENU_ITEM_T          t_menu_item_page_demo_mode_off;
#endif

/* tab */
extern UINT16  ui2_g_menu_tab_vid;
extern UINT16  ui2_g_menu_tab_aud;
extern UINT16  ui2_g_menu_tab_tv;
extern UINT16  ui2_g_menu_tab_setup;
extern UINT16  ui2_g_menu_tab_par;
extern UINT32  ui4_g_menu_page_3D_setting;
extern UINT16  ui2_item_acr;
extern UINT16  ui2_item_page_help_tos;
extern UINT16  ui2_item_fast_boot;
extern UINT16  ui2_item_page_ch_scan;
extern UINT16  ui2_item_page_ch_scan_new;
extern UINT16  ui2_item_page_help_sys_info_and_reset;
extern UINT16  ui2_item_page_accessibility;
extern UINT16  ui2_item_page_ver_info;




/* page */
extern UINT32 ui4_g_menu_page_pic_mode;
extern UINT32 ui4_g_menu_page_slp;
extern UINT32 ui4_g_menu_page_vid;
extern UINT32 ui4_g_menu_page_scr_mode;
extern UINT32 ui4_g_menu_page_aspect_ratio;
extern UINT32 ui4_g_menu_page_sb_setting_eq_mode;
extern UINT32 ui4_g_menu_page_aud;
extern UINT32 ui4_g_menu_page_sys;
extern UINT32 ui4_g_menu_page_mmp;
extern UINT32 ui4_g_menu_page_tv;
extern UINT32 ui4_g_menu_page_par;
extern UINT32 ui4_g_menu_page_setup;
extern UINT32 ui4_g_menu_page_setup_wizard_pwd;
extern UINT32 ui4_g_menu_page_clr_tmp;
extern UINT32 ui4_g_menu_page_device_setting;
extern UINT32 ui4_g_menu_page_channels;
extern UINT32 ui4_g_menu_page_user_manual;
extern UINT32 ui4_g_menu_page_mobile_device;
extern UINT32 ui4_mobile_device_delete_dialog_page_id;
extern UINT32 ui4_g_menu_custom_page_pic_mode;

/*KASI*/
extern UINT32 ui4_g_menu_page_bt_headphones;

extern UINT32 ui4_g_menu_page_inp_src;
extern UINT32 ui4_g_menu_page_network;
extern UINT32 ui4_g_menu_page_pip;

extern UINT32 ui4_g_menu_page_picture_reset;
extern UINT32 ui4_g_menu_page_pic_mode_reset;
extern UINT32 ui4_g_menu_page_audio_reset;
extern UINT32 ui4_g_menu_page_del_aud_mode;
extern UINT32 ui4_g_menu_page_blank_scrn;
extern UINT32 ui4_g_menu_page_reset_pub;
extern UINT32 ui4_g_menu_page_pwd;
extern UINT32 ui4_g_menu_page_main_menu;
extern UINT32 ui4_g_menu_page_channel_lock_reset;

extern UINT32 ui4_g_menu_page_cc;
extern UINT32 ui4_g_menu_page_inp_naming;

extern UINT32 ui4_g_menu_page_ch_scan;
extern UINT32 ui4_g_menu_page_ch_scan_new;
extern UINT32 ui4_g_menu_page_ch_scan2_pwd;

extern UINT32 ui4_g_menu_page_terms;
extern UINT32 ui4_g_menu_page_terms_sub;

extern UINT32 ui4_g_page_clear_memory;
extern UINT32 ui4_g_page_clear_memory_dialog;
extern UINT32 ui4_g_page_service_check_dialog;
extern UINT32 ui4_g_page_service_rst_dialog;
extern UINT32 ui4_page_reset_tv_ad_id_dialog;
extern UINT32 ui4_page_off_rs_entry;
extern UINT32 ui4_page_oled_jb;
extern UINT32 ui4_page_oled_screen_1;
extern UINT32 ui4_page_oled_screen_2;


extern UINT32 ui4_page_inp_set;

extern UINT32 ui4_g_menu_page_mmp_dev_list;
extern UINT32 ui4_g_menu_page_mmp_media_type;

extern UINT32 ui4_page_clr_tmp_reset_pm;

extern UINT32  ui4_g_menu_page_cust_setting;

/*picture mode */
extern UINT32 ui4_g_menu_custom_page_pic_mode;

/*picture mode management(common)->picture mode edit(special)*/
extern UINT32 ui4_g_menu_custom_page_pic_mode_edit;
extern UINT32 ui4_g_menu_custom_page_lock_pic_lb2;

/*color calibration*/
extern UINT32 ui4_g_menu_custom_page_color_calibration;

/*color tuner*/
extern UINT32 ui4_g_menu_custom_page_pic_quality;
/*white balance tuner*/
extern UINT32 ui4_g_menu_white_balance_tuner_page;

/*Professional Picture*/
extern UINT32 ui4_g_menu_custom_page_create_pic_mode;
extern UINT32 ui4_g_menu_custom_page_lock_pic_mode;
extern UINT32 ui4_g_menu_custom_page_unlock_pic_mode;

extern UINT32 ui4_g_menu_custom_page_delete_pic_mode;
extern UINT32 ui4_g_menu_page_eq_bands_setting;
extern UINT32 ui4_g_menu_page_chg_pwd;
extern UINT32 ui4_g_page_input_sys_pin;
extern UINT32 ui4_page_chg_country_code_dialog;
extern UINT32 ui4_g_menu_page_ver_info;
extern UINT32 ui4_page_help_sys_info_and_reset;
extern UINT32 ui4_g_menu_page_mc_ver;
/*test special param page id*/
extern UINT32 ui4_g_menu_page_test_special_param;
extern UINT32 ui4_g_menu_page_audio_dbginfo;
extern UINT32 ui4_g_menu_page_hdmi_dbginfo;
/* picture VGA auto size */
extern UINT32 ui4_g_menu_page_vga_auto;
/* picture size */
extern UINT32 ui4_g_menu_page_pic_size;
/* picture position */
extern UINT32 ui4_g_menu_page_pic_postion;

extern UINT32 ui4_page_vid_more_adv_pic;
/* Reduce Noise */
extern UINT32 ui4_page_reduce_noise;
extern UINT32 ui4_page_vid_motion_control;
extern UINT32 ui4_page_vid_progame_engine;

extern UINT32 ui4_page_vid_cal_pattern_test;
extern UINT32 ui4_page_vid_cal_dn_sdr;
extern UINT32 ui4_page_vid_cal_dn_hdr;
extern UINT32 ui4_page_vid_cal_dn_hlg;
extern UINT32 ui4_page_vid_cal_dn_dv;

/* OLED Panel page*/
extern UINT32 ui4_page_vid_oled_panel;

#ifdef APP_SUPPORT_STR_CORE_OFF
extern MENU_ITEM_T          t_g_menu_custom_item_fast_boot;
#endif

extern MENU_ITEM_T          t_g_menu_custom_item_aspect_ratio;

#ifdef APP_NETWORK_SUPPORT
#ifdef APP_NETWORK_WIFI_SUPPORT
#ifdef APP_WAKE_ON_LAN_ENABLE_UI
extern MENU_ITEM_T          t_g_menu_custom_item_wake_on_lan;
#endif
#endif
//#ifdef APP_WAKE_ON_WLAN_ENABLE_UI
extern MENU_ITEM_T          t_g_menu_custom_item_wake_on_wlan;
//#endif
#endif

#ifdef APP_LOG2USB_SUPPORT
extern UINT32 ui4_g_menu_page_log_to_usb;
#endif

extern UINT32 ui4_page_vizio_tos;

extern UINT32 ui4_g_menu_page_reset_admin;

extern UINT32 ui4_page_accessibility;


/************************* global item id begin *************************************/
extern UINT32 ui2_g_item_id_lst_acr;
/************************* global item id end *************************************/


#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
extern INT32 menu_custom_page_time_local_setting_auto_dst_init(VOID);
extern INT32 menu_custom_page_time_local_setting_refresh_item(WDK_STRING_STYLE_T e_string_style);
#else
extern INT32 menu_custom_page_time_local_setting_init(VOID);
#endif

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT

extern INT32 menu_custom_page_get_clear_memory_page_status(BOOL* pb_status);
extern INT32 menu_custom_page_get_tmp_country_code(UINT16* pui2_country_code);

#endif

#ifdef APP_EMANUAL_SUPPORT
extern MENU_ITEM_T             t_menu_item_page_manual;
#endif
extern MENU_ITEM_T             t_g_menu_custom_item_lst_acr;
extern MENU_ITEM_T             t_g_menu_custom_item_dynamic_content;
extern MENU_ITEM_T             t_g_menu_custom_item_limited_ad_tracking;
extern MENU_ITEM_T 		   t_g_menu_item_3d_brightness_boost;
extern MENU_ITEM_T              t_menu_item_soft_power_cycle;

/*-----------------------------------------------------------------------------
                    function declaraions
 ----------------------------------------------------------------------------*/
/* menu hierarchy init */
extern INT32 menu_custom_hierarchy_init(VOID);

/* page registration */
extern INT32 menu_custom_create_page_inp_edit(UINT32* pui4_page_id);

/* 3D setting */
extern INT32 menu_custom_page_3D_setting_init(VOID);
extern INT32 menu_page_vid_position_init(VOID);
extern INT32 menu_page_vid_size_init(VOID);
extern INT32 menu_custom_page_mmp_dev_list_init(VOID);
extern INT32 menu_custom_page_mmp_media_type_init(VOID);

/* settings registration */
extern INT32 menu_custom_settings_init(VOID);
extern INT32 menu_custom_chg_lang(VOID);
extern BOOL  menu_custom_is_channel_blocked (VOID);

extern BOOL menu_simple_dialog_page_is_show(VOID);
extern BOOL menu_clear_memory_pwd_is_show(VOID);
extern BOOL menu_scr_mode_show(VOID);

extern BOOL menu_get_factory_reset_status(VOID);
#if 0
/*phase1 no use*/
extern INT32 main_menu_update_3D_item_status(VOID);
#endif

extern INT32 menu_custom_set_aud_spdif(UINT16 ui2_idx);
extern VOID menu_set_start_user_manual_flag(BOOL b_start);
extern BOOL menu_get_start_user_manual_flag(VOID);
#ifdef APP_EMANUAL_SUPPORT
extern BOOL menu_manual_in_flash(VOID);
#endif
extern VOID menu_reset_audio_stream(VOID);
extern UINT16 menu_custom_get_aud_lang_num(VOID);
extern INT32 menu_custom_blank_screen(VOID);
extern INT32 menu_custom_unblank_screen(UINT32 ui4_keycode);
extern VOID menu_custom_set_blank_scrn_flag(UINT8 ui1_flag);
extern INT32 menu_custom_exit_menu_actions(VOID);

extern VOID menu_custom_set_blank_scrn_mode(MENU_CUSTOM_BLK_SCRN_MODE t_mode);
extern MENU_CUSTOM_BLK_SCRN_MODE menu_custom_get_blank_scrn_mode(VOID);
extern INT32 menu_blank_oled_scrn_timer_start(VOID);
extern INT32 menu_blank_oled_scrn_timer_stop(VOID);
extern INT32 menu_blank_oled_scrn_timer_refresh(VOID);
extern BOOL menu_custom_blank_oled_scrn_timer_is_start(VOID);
extern INT32 menu_oled_pro_audio_check_timer_start(VOID);
extern INT32 menu_oled_pro_audio_check_timer_stop(VOID);
extern INT32 menu_oled_pro_auto_pwr_off_timer_start(VOID);
extern INT32 menu_oled_pro_auto_pwr_off_timer_stop(VOID);
extern BOOL menu_oled_pro_auto_pwr_off_timer_is_start(VOID);
extern VOID menu_custom_blank_screen_set_block_power_off(BOOL b_flag);
extern BOOL menu_custom_blank_screen_get_block_power_off(VOID);
extern BOOL menu_custom_blank_screen_is_oled_toast_show(VOID);
extern BOOL menu_custom_set_audio_sync(BOOL b_flag);


extern UINT8 menu_custom_is_blank_screen(VOID);
extern INT32 menu_custom_blank_screen(VOID);
//extern INT32 menu_custom_unblank_screen(VOID);
extern VOID  menu_set_temporary_key_code(UINT32 ui4_keycode);

extern BOOL menu_custom_power_seq_cb(VOID);
extern VOID a_menu_custom_reset_pri(VOID);
extern VOID a_menu_custom_reset_fac(VOID);
extern VOID a_menu_custom_reset_pub(VOID);
extern BOOL menu_common_is_3d_mode_enable(VOID);
extern INT32 menu_setup_string_toast_view(UTF16_T* w2s_txt,BOOL b_show_menu);

extern INT32 menu_pic_energy_change_toast_view(VOID);
extern INT32 menu_pic_erengy_change_toast_reset_status(VOID);
extern INT32 menu_pic_energy_change_set_status(VOID);
extern INT32 menu_pic_energy_change_sepcial_page_set_status(BOOL b_is_change);
extern INT32 a_menu_pic_erengy_change_hide_toast_view(VOID);

extern INT32 a_menu_custom_page_mmp_media_set_enter_flag(BOOL b_is_enter);
extern INT32 menu_get_netflix_esn2(CHAR* s_esn2_str);
extern INT32 menu_custom_update_the_old_display_region_after_change_source_tv(VOID);
extern INT32 menu_send_string_to_nav_toast(WDK_TOAST_T *pt_toast);
extern BOOL a_menu_is_color_tuner_enable(VOID);
extern BOOL a_menu_is_cust_pic_mode_and_locked(VOID);
extern INT32 a_menu_set_picture_mode_tmp_lock_status(BOOL b_lock);
extern VOID a_menu_custom_save_sn_to_file(CHAR* serial_num);
extern VOID a_menu_custom_get_sn_from_file(CHAR* serial_num);
extern VOID menu_custom_set_dynamic_content_idx(UINT16 ui2_idx);
extern UINT16 menu_custom_get_dynamic_content_idx(VOID);
extern VOID menu_custom_set_limited_ad_tracking_idx(UINT16 ui2_idx);
extern UINT16 menu_custom_get_limited_ad_tracking_idx(VOID);
extern VOID menu_set_vid_back_light_val(INT32 i4_val);
extern INT32 menu_get_vid_back_light_val(VOID);
extern VOID menu_set_vid_clear_action_idx(UINT16 ui2_idx);
extern UINT16 menu_get_vid_clear_action_idx(VOID);
extern VOID menu_set_vid_oled_pixel_shift_idx(UINT16 ui2_val);
extern UINT16 menu_get_vid_oled_pixel_shift_idx(VOID);
extern VOID menu_set_vid_super_resolution_idx(UINT16 ui2_val);
extern UINT16 menu_get_vid_super_resolution_idx(VOID);
extern VOID menu_set_vid_edge_enhancement_idx(UINT16 ui2_val);
extern UINT16 menu_get_vid_edge_enhancement_idx(VOID);
extern VOID menu_set_vid_judder_reduction_idx(INT32 i4_val);
extern INT32 menu_get_vid_judder_reduction_idx(VOID);
extern VOID menu_set_vid_local_contrast_idx(UINT16 ui2_val);
extern UINT16 menu_get_vid_local_contrast_idx(VOID);
extern VOID menu_set_vid_vss_idx(UINT16 ui2_idx);
extern UINT16 menu_get_vid_vss_idx(VOID);
extern VOID menu_set_vid_game_hdr_idx(UINT16 ui2_idx);
extern UINT16 menu_get_vid_game_hdr_idx(VOID);
extern VOID menu_set_vid_peak_luminance_idx(UINT16 ui2_idx);
extern VOID menu_set_vid_contour_smoothing_idx(UINT16 ui2_val);
extern UINT16 menu_get_vid_contour_smoothing_idx(VOID);
extern VOID menu_set_vid_motion_blur_reduction_idx(INT32 i4_val);
extern INT32 menu_get_vid_motion_blur_reduction_idx(VOID);
extern VOID menu_set_inp_full_color_444_idx(UINT16 ui2_val);
extern UINT16 menu_get_inp_full_444_color_idx(VOID);
extern VOID menu_set_inp_film_maker_mode_idx(UINT16 ui2_val);
extern UINT16 menu_get_inp_film_maker_mode_idx(VOID);
extern VOID menu_set_vid_hdmi_mode_idx(UINT16 ui2_val);
extern UINT16 menu_get_vid_hdmi_mode_idx(VOID);
extern VOID menu_set_local_dimming_idx(UINT16 ui2_idx);
extern UINT16 menu_get_local_dimming_idx(VOID);
extern VOID menu_set_vid_pic_mode_idx(UINT16 ui2_idx);
extern UINT16 menu_get_vid_pic_mode_idx(VOID);
extern VOID menu_common_get_vid_pic_mode_text(UINT16 ui2_idx,CHAR* ps_pic_mode, SIZE_T z_len);
extern INT32 menu_create_pic_mode_name_mapping(CHAR* ps_pic_mode_name);
extern INT32 menu_save_pic_btn_fct(CHAR *p_str);
extern UINT16 menu_get_cust_picture_mode_num(VOID);
extern VOID menu_custom_set_gui_lang_idx(UINT16 ui2_idx);
extern UINT16 menu_custom_get_gui_lang_idx(VOID);
extern INT32 menu_copy_cus_pic_mode_to_preset_pic_mode(INT16 i2_to_pic);
extern UINT16 menu_get_font_style_idx(VOID);
extern UINT16 menu_get_font_size_idx(VOID);
extern UINT16 menu_get_font_color_idx(VOID);
extern UINT16 menu_get_font_opac_idx(VOID);
extern UINT16 menu_get_text_edges_idx(VOID);
extern UINT16 menu_get_text_edges_color_idx(VOID);
extern UINT16 menu_get_bg_color_idx(VOID);
extern UINT16 menu_get_bg_opac_idx(VOID);
extern UINT16 menu_get_win_color_idx(VOID);
extern UINT16 menu_get_win_opac_idx(VOID);
extern INT32 menu_get_aud_volume_val(VOID);
extern BOOL  menu_picture_size_poition_is_hidde(VOID);
extern BOOL  menu_picture_position_is_enable(VOID);
extern BOOL  menu_picture_size_is_enable(VOID);
extern BOOL  menu_vga_auto_is_enable(VOID);
extern BOOL  menu_full_color_444_is_enable(VOID);
extern BOOL  menu_full_chroma_is_visibility(VOID);
extern BOOL  menu_full_color_is_enable(UINT8 ui1_hdmi_port);
extern VOID menu_set_automatic_time_idx(UINT16 ui2_idx);
extern UINT16 menu_get_automatic_time_idx(VOID);
extern INT32 menu_page_set_automatic_time_to_refresh(VOID);

extern char* menu_custom_get_char_string( const UTF16_T* w2s_str );

#if 0//(MENU_SUPPORT_HOT_KEY_PIC)
BOOL menu_custom_is_support_hot_key_PIC(VOID);
#endif

#endif /* _MENU_CUSTOM_H_ */

