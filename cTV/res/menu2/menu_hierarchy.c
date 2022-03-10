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
 * $RCSfile: menu_hierarchy.c,v $
 * $Revision: #4 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/21 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 1433fe1fd8b5fe1dfc2a58820b53a685 $
 *
 * Description:
 *         This file contains all the customizable code in menu.
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_irrc_btn_def.h"
#include "u_sm_video_hdlr.h"
#include "u_pcl.h"

#include "c_os.h"
#include "c_dbg.h"
#include "c_common.h"
#include "c_handle.h"
#include "c_svl.h"
#include "c_cfg.h"
#include "c_tsl.h"
#include "c_svctx.h"
#include "c_sys_config.h"
#include "nav/updater/nav_updater.h"
#include "c_netflix_api.h"
#include "c_dt.h"
#include "c_rm.h"
#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "app_util/a_rating.h"
#include "app_util/a_ui.h"
#include "app_util/a_tv.h"
#include "app_util/a_isl.h"
#include "app_util/a_sleep_timer.h"
#include "app_util/a_screen_mode.h"
#include "menu2/a_menu.h"
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_page_tree.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_device/menu_device.h"
#include "menu2/menu_device/menu_page_add_new_device.h"
#include "menu2/menu_device/menu_page_input_ope_lst.h"
#include "menu2/menu_device/menu_page_hide_from_input_list.h"

#include "menu2/menu_common/menu_common.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_page_ex/menu_page_ex.h"
#include "res/menu2/menu_cust_define.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "app_util/a_cfg.h"
#include "cmd_convert.h"
#include "menu2/menu_network_phase1/menu_network.h"

#include "am/a_am.h"
#include "mmp/a_mmp.h"
#include "mmp/file_browser/a_file_browser.h"
#include "nav/pop/a_pop.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/config/acfg_cust_factory.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/config/acfg_cust_plf_opt.h"
#include "res/app_util/config/acfg_cust_ble.h"
#include "menu2/menu_mtktvapi.h"
#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif

#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#endif

#ifdef APP_WIFI_REMOTE
#include "wfrrc_interface.h"
#ifdef APP_WFD_SUPPORT
#include "wfd_client_export.h"
#endif
#endif

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "wizard_anim/a_wzd.h"

#include "rest/a_rest_event.h"
#include "rest/a_rest_api.h"
#include "menu2/menu_common/menu_factory/menu_factory.h"
#include "menu2/menu_dbg.h"
#include "nav/cec2/sac/nav_cec_sac.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define eMEMC               ((UINT16)(0x1000))
#define eNON_MEMC         ((UINT16)(0x2000))
#define CHECK_1080P_120HZ_SUPPORT()   \
{\
    if (a_cfg_custom_chk_freqence_120hz() == TRUE)   \
    {   \
        DBG_INFO(("%s() Line %d: CHECK_1080P_120HZ_SUPPORT return FALSE.\n", __FUNCTION__, __LINE__)); \
        return FALSE;   \
    }\
}

extern CEC_SB_VNDR_INFO amp_vndr_info;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_ver_info;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_ver_info_mc;
extern BOOL b_is_read_reset_advertiser_info;
extern BOOL menu_custom_is_aud_stream_enabled(VOID);
extern BOOL menu_cc_is_visible(VOID);
extern BOOL a_is_oled_compensation_support();

#define SUPPORT_MENU_CODE    (1) /*remove UI,until next stage*/

/*-----------------------------------------------------------------------------
                    enum settings
 ----------------------------------------------------------------------------*/

typedef enum
{
    _MENU_HIERARCHY_SB_SETTINGS_EQ_MODE_DEFAULT = 0,
    _MENU_HIERARCHY_SB_SETTINGS_EQ_MODE_MUSIC = _MENU_HIERARCHY_SB_SETTINGS_EQ_MODE_DEFAULT,
    _MENU_HIERARCHY_SB_SETTINGS_EQ_MODE_MOVIE,
    _MENU_HIERARCHY_SB_SETTINGS_EQ_MODE_GAME,
    _MENU_HIERARCHY_SB_SETTINGS_EQ_MODE_DIRECT,
    _MENU_HIERARCHY_SB_SETTINGS_EQ_MODE_DIALOGUE,
    _MENU_HIERARCHY_SB_SETTINGS_EQ_MODE_MAX

} _MENU_HIERARCHY_SETTINGS_SB_SETTINGS_EQ_MODE_T;

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
/* global */
UINT16  ui2_g_menu_tab_vid;
UINT16  ui2_g_menu_tab_aud;
UINT16  ui2_g_menu_tab_tv;
UINT16  ui2_g_menu_tab_setup;
UINT16  ui2_g_menu_tab_par;
UINT16  ui2_item_acr;
UINT16  ui2_item_page_help_tos;
UINT16  ui2_item_fast_boot;
UINT16  ui2_item_page_ch_scan;
UINT16  ui2_item_page_ch_scan_new;
UINT16  ui2_item_page_help_sys_info_and_reset;
UINT16  ui2_item_page_accessibility;
UINT16  ui2_item_page_ver_info;

/* page id */
UINT32 ui4_g_menu_page_mmp;
UINT32 ui4_g_menu_page_tv;
UINT32 ui4_g_menu_page_par;

UINT32 ui4_g_menu_page_setup_wizard_pwd;
UINT32 ui4_g_menu_page_pic_custom;
UINT32 ui4_g_menu_page_clr_tmp;
UINT32 ui4_g_menu_page_device_setting;
UINT32 ui4_g_menu_page_chg_pwd;
UINT32 ui4_g_page_input_sys_pin;

/*Main menu page id for vizio non_BT*/
UINT32 ui4_g_menu_page_inp_src;
UINT32 ui4_g_menu_page_scr_mode;
UINT32 ui4_g_menu_page_aspect_ratio;
UINT32 ui4_g_menu_page_sb_setting_eq_mode;
UINT32 ui4_g_menu_page_cc;
UINT32 ui4_g_menu_page_slp;
UINT32 ui4_g_menu_page_vid;
UINT32 ui4_g_menu_page_aud;  /*=ui4_page_aud*/
UINT32 ui4_g_menu_page_setup;
UINT32 ui4_g_menu_page_sys;//guide setup
UINT32 ui4_g_menu_page_user_manual;
UINT32 ui4_g_menu_page_mobile_device;
UINT32 ui4_mobile_device_delete_dialog_page_id;

UINT32 ui4_g_menu_page_pip;
UINT32 ui4_g_menu_page_channels;

UINT32 ui4_g_menu_page_advertising;

UINT32 ui4_g_menu_page_bt_headphones;
/* 3D setting */
UINT32 ui4_g_menu_page_3D_setting;

UINT32 ui4_g_menu_page_cust_setting = -1;

UINT32 ui4_g_menu_page_network;
/*for BT tv */
UINT32 ui4_g_menu_page_tv_setting;

UINT32 ui4_g_menu_page_picture_reset;
UINT32 ui4_g_menu_page_pic_mode_reset;

UINT32 ui4_g_menu_page_audio_reset;
UINT32 ui4_g_menu_page_del_aud_mode;
UINT32 ui4_g_menu_page_channel_lock_reset;

UINT32 ui4_g_menu_page_blank_scrn;
UINT32 ui4_g_menu_page_reset_pub;
UINT32 ui4_g_menu_page_pwd;

UINT32 ui4_g_menu_page_main_menu;

UINT32 ui4_g_page_input;

UINT32 ui4_g_menu_page_inp_naming;
UINT32 ui4_g_menu_page_power_on_input;

UINT32 ui4_g_menu_page_ch_scan;
UINT32 ui4_g_menu_page_ch_scan_new;
UINT32 ui4_g_menu_page_ch_scan2_pwd;

UINT32 ui4_g_page_clear_memory;
UINT32 ui4_g_page_clear_memory_dialog;
UINT32 ui4_g_page_service_check_dialog;
UINT32 ui4_g_page_service_rst_dialog;
UINT32 ui4_page_inp_set;
UINT32 ui4_page_chg_country_code_dialog;
UINT32 ui4_page_reset_tv_ad_id_dialog;
UINT32 ui4_page_off_rs_entry;
UINT32 ui4_page_oled_jb;

UINT32 ui4_g_menu_page_mmp_dev_list;
UINT32 ui4_g_menu_page_mmp_media_type;
UINT32 ui4_page_clr_tmp_reset_pm;

UINT32 ui4_page_ch_scan;
UINT32 ui4_page_ch_scan_new;

UINT32 ui4_page_vid_professional;

#ifdef APP_MENU_VCT_RAW_SUPPORT
UINT32 ui4_g_menu_page_vct_raw_dump;
#endif

UINT32 ui4_g_menu_page_terms;
UINT32 ui4_g_menu_page_terms_sub;
UINT32 ui4_page_vizio_tos;

/*picture mode */
UINT32 ui4_g_menu_custom_page_pic_mode;

/*picture mode management(common)->picture mode edit(special)*/
UINT32 ui4_g_menu_custom_page_pic_mode_edit;
UINT32 ui4_g_menu_custom_page_lock_pic_lb2;

/*color calibration*/
UINT32 ui4_g_menu_custom_page_color_calibration;
/*Professional Picture*/
UINT32 ui4_g_menu_custom_page_create_pic_mode;
UINT32 ui4_g_menu_custom_page_lock_pic_mode;
UINT32 ui4_g_menu_custom_page_unlock_pic_mode;
UINT32 ui4_g_menu_custom_page_delete_pic_mode;

UINT32 ui4_g_menu_custom_page_pic_quality;//color tuner page
UINT32 ui4_g_menu_white_balance_tuner_page;//white balance tuner page

UINT32 ui4_g_menu_page_eq_bands_setting;
UINT32 ui4_g_menu_page_ver_info;
UINT32 ui4_g_menu_page_mc_ver;

UINT32 ui4_g_menu_page_reset_admin;

UINT32 ui4_page_aud_sb_settings;

UINT32 ui4_page_aud_tv_aud_settings;


/************************* global page id end *************************************/

/************************* global item id begin *************************************/
UINT32 ui2_g_item_id_lst_acr;
/************************* global item id end *************************************/

#ifdef APP_2K12_RETAIL_DEMO_MODE
static UINT32 ui4_page_help_demo_mode;
#endif


//static UINT32 ui4_page_clr_tmp;
static UINT32 ui4_page_vga;
static UINT32 ui4_page_aud;
static UINT32 ui4_page_adv_scan_rng;
static UINT32 ui4_page_adv_scan_sgl;
#ifdef APP_MENU_FAV_LST
static UINT32 ui4_page_ch_fav;
#endif
static UINT32 ui4_page_cap_stl;
static UINT32 ui4_page_prg_bk;
static UINT32 ui4_page_vchip_us_tv;
static UINT32 ui4_page_vchip_us_movie;
static UINT32 ui4_page_vchip_ca_en;
static UINT32 ui4_page_vchip_ca_fr;
static UINT32 ui4_page_scr_mode;
static UINT32 ui4_menu_page_tv_name;
#ifdef APP_MENU_OP_VCHIP_ENABLE
static UINT32 ui4_page_op_vchip_rgn;
static UINT32 ui4_page_op_vchip_dim;
static UINT32 ui4_page_op_vchip_lvl;

static UINT32 ui4_page_op_vchip_drrt;
#endif
static UINT32 ui4_page_chg_pwd;
static UINT32 ui4_page_ch_bk;
#ifndef APP_MENU_CUSTOM_FACTORY_TREE
static UINT32 ui4_page_fac;
static UINT32 ui4_page_fac_vid;
static UINT32 ui4_page_fac_aud;
static UINT32 ui4_page_fac_tv;
static UINT32 ui4_page_fac_setup;
static UINT32 ui4_page_auto_color;
static UINT32 ui4_page_fac_clr_tmp;
#endif
static UINT32 ui4_page_inp_sk;
static UINT32 ui4_page_inp_bk;
static UINT32 ui4_page_date_time;
static UINT32 ui4_page_date;
static UINT32 ui4_page_hv_pos;
static UINT32 ui4_page_inp_edit;
static UINT32 ui4_page_ver_info;
static UINT32 ui4_page_sys_info;
static UINT32 ui4_page_sys_reset;
static UINT32 ui4_page_reset_fac;
//static UINT32 ui4_page_check_for_updates;
static UINT32 ui4_page_reset_pri;
static UINT32 ui4_page_auto_phase;
#ifdef COMMON_IMG_CLNR_ENABLE
static UINT32 ui4_page_img_clnr;
#endif

#ifdef APP_CEC_MENU
static UINT32 ui4_page_cec;
static UINT32 ui4_page_cec_dev_discovery;
#endif

/* 3D setting */
static UINT32 ui4_page_3D_setting;

static UINT32 ui4_page_nw;
UINT32 ui4_g_menu_page_nw;
UINT32 ui4_g_menu_page_test_special_param;

#ifdef APP_LOG2USB_SUPPORT
UINT32 ui4_g_menu_page_log_to_usb;
#endif
#ifdef APP_NETWORK_SUPPORT
UINT32 ui4_g_menu_page_network_main;
#endif

UINT32 ui4_g_menu_page_audio_dbginfo;
UINT32 ui4_g_menu_page_hdmi_dbginfo;

static UINT32 ui4_page_time_local_setting;

static UINT32 ui4_page_device_setting;

static UINT32 ui4_page_bass_treble;
static UINT32 ui4_page_setup_wizard_reset;

static UINT32       ui4_page_masterlist;
static UINT32       ui4_page_ch_edit;

static MENU_ITEM_T  t_menu_item_page_channels;
static MENU_ITEM_T  t_menu_item_page_masterlist;
static MENU_ITEM_T  t_menu_item_page_ch_edit;

static UINT32 ui4_page_start_wizard;

static MENU_ITEM_T t_menu_page_vid_pic_mode;

static MENU_ITEM_T t_g_menu_custom_item_color_tuner;
static MENU_ITEM_T t_g_menu_custom_item_white_balance_tuner;

static UINT32 ui4_page_vid_more;
static UINT32 ui4_page_vid_more_sz_pos;

/* picture VGA auto size */
UINT32 ui4_g_menu_page_vga_auto;
/* picture size */
UINT32 ui4_g_menu_page_pic_size;
/* picture position */
UINT32 ui4_g_menu_page_pic_postion;

static UINT32 ui4_page_vid_more_size_position;
//static UINT32 ui4_page_vid_more_clr_tmp;

UINT32 ui4_page_vid_more_adv_pic;
static UINT32 ui4_page_vid_inp_settings;
static UINT32 ui4_page_picture_size_position;


UINT32 ui4_page_vid_motion_control;
UINT32 ui4_page_vid_progame_engine;

UINT32 ui4_page_vid_cal_pattern_test;
UINT32 ui4_page_vid_cal_dn_sdr;
UINT32 ui4_page_vid_cal_dn_hdr;
UINT32 ui4_page_vid_cal_dn_hlg;
UINT32 ui4_page_vid_cal_dn_dv;

/* OLED Panel page*/
UINT32 ui4_page_vid_oled_panel;
UINT32 ui4_page_oled_screen_1;
UINT32 ui4_page_oled_screen_2;


/* Reduce Noise */
UINT32 ui4_page_reduce_noise;

static UINT32 ui4_page_eq_bands_setting = 0;
static UINT32 ui4_page_aud_adv;
UINT32 ui4_page_help_sys_info_and_reset;

/* MMP sider menu */
static UINT32 ui4_page_mmp_dev_list;
static UINT32 ui4_page_mmp_media_type_page;

static MENU_ITEM_T t_menu_item_page_clear_memory;
//static MENU_ITEM_T t_menu_item_page_srv_chk;

static MENU_ITEM_T t_menu_item_pic_mode_edit;

/*color calibration*/
static MENU_ITEM_T t_menu_item_color_calibration;
static MENU_ITEM_T t_menu_item_page_vid_more;
static MENU_ITEM_T t_menu_item_page_vid_more_sz_pos;
static MENU_ITEM_T t_menu_item_page_vid_more_position;
static MENU_ITEM_T t_menu_item_page_vid_more_size;
static MENU_ITEM_T t_menu_item_page_vid_more_size_pos;
static MENU_ITEM_T t_menu_item_page_vid_more_clr_tmp;
static MENU_ITEM_T t_menu_item_page_vid_more_adv_pic;
static MENU_ITEM_T t_menu_item_page_vid_inp_settings;
static MENU_ITEM_T t_menu_item_page_picture_size_position;
static MENU_ITEM_T t_menu_item_page_vid_motion_control;
static MENU_ITEM_T t_menu_item_page_vid_oled_panel;
static MENU_ITEM_T t_menu_item_page_vid_progame_engine;

static MENU_ITEM_T t_menu_item_page_vid_cal_pattern_test;
static MENU_ITEM_T t_menu_item_page_vid_cal_dn_sdr;
static MENU_ITEM_T t_menu_item_page_vid_cal_dn_hdr;
static MENU_ITEM_T t_menu_item_page_vid_cal_dn_hlg;
static MENU_ITEM_T t_menu_item_page_vid_cal_dn_dv;

//static MENU_ITEM_T t_menu_item_page_clr_tmp_reset_pm;
static MENU_ITEM_T t_g_menu_common_item_page_aud_adv;
static MENU_ITEM_T t_menu_item_page_eq_settings;
static MENU_ITEM_T t_menu_item_page_setup_par_ctrl;
static MENU_ITEM_T t_menu_item_device_page_device_setting;
static MENU_ITEM_T t_menu_item_page_mobile_device;

static MENU_ITEM_T t_menu_item_page_help_sys_info_and_reset;

static MENU_ITEM_T t_menu_item_page_help_tos;

static MENU_ITEM_T t_menu_item_time_local_setting;

/* menu items */
static MENU_ITEM_T t_menu_item_page_sys_reset;
static MENU_ITEM_T t_menu_item_start_setup_wizard;
static MENU_ITEM_T t_menu_item_setup_audio_mode;

static MENU_ITEM_T t_menu_item_page_clr_tmp;
/*static MENU_ITEM_T t_menu_item_page_adv_vid;*/
static MENU_ITEM_T t_menu_item_page_vga;
static MENU_ITEM_T t_menu_item_page_vga_auto;
static MENU_ITEM_T t_menu_item_page_adv_scan_rng;
static MENU_ITEM_T t_menu_item_page_adv_scan_sgl;
static MENU_ITEM_T t_menu_item_page_ch_bk;
#ifdef APP_MENU_FAV_LST
static MENU_ITEM_T t_menu_item_page_ch_fav;
#endif
static MENU_ITEM_T t_menu_item_page_cap_stl;
static MENU_ITEM_T t_menu_item_page_prg_bk;
static MENU_ITEM_T t_menu_item_page_vchip_us_tv;
static MENU_ITEM_T t_menu_item_page_vchip_us_movie;
static MENU_ITEM_T t_menu_item_page_vchip_ca_en;
static MENU_ITEM_T t_menu_item_page_vchip_ca_fr;
#ifdef APP_MENU_OP_VCHIP_ENABLE
static MENU_ITEM_T t_menu_item_page_op_vchip;
static MENU_ITEM_T t_menu_item_page_op_vchip_drrt;
#endif
static MENU_ITEM_T t_menu_item_page_chg_pwd;
static MENU_ITEM_T t_menu_item_page_ch_bk;
static MENU_ITEM_T t_menu_item_page_reset_pri;
static MENU_ITEM_T t_menu_item_page_reset_pub;
static MENU_ITEM_T t_menu_item_page_reset_fac;
static MENU_ITEM_T t_menu_item_page_start_wizard;
static MENU_ITEM_T t_menu_item_page_picture_reset;
static MENU_ITEM_T t_menu_item_page_pic_mode_reset;
static MENU_ITEM_T t_menu_item_page_audio_reset;
static MENU_ITEM_T t_menu_item_page_del_aud_mode;
static MENU_ITEM_T t_menu_item_page_channel_lock_reset;

#ifndef APP_MENU_CUSTOM_FACTORY_TREE
static MENU_ITEM_T t_menu_item_page_fac_vid;
static MENU_ITEM_T t_menu_item_page_fac_aud;
static MENU_ITEM_T t_menu_item_page_fac_tv;
static MENU_ITEM_T t_menu_item_page_fac_setup;
static MENU_ITEM_T t_menu_item_page_auto_color;
static MENU_ITEM_T t_menu_item_page_fac_clr_tmp;
#endif

static MENU_ITEM_T t_menu_item_page_auto_phase;
static MENU_ITEM_T t_menu_item_page_inp_sk;
static MENU_ITEM_T t_menu_item_page_inp_bk;
static MENU_ITEM_T t_menu_item_page_date_time;
static MENU_ITEM_T t_menu_item_page_date;
static MENU_ITEM_T t_menu_item_page_hv_pos;
static MENU_ITEM_T t_menu_item_page_inp_edit;
#ifdef COMMON_IMG_CLNR_ENABLE
static MENU_ITEM_T t_menu_item_page_img_clnr;
#endif
static MENU_ITEM_T t_menu_item_page_cc;

static MENU_ITEM_T t_menu_item_page_inp;
static MENU_ITEM_T t_menu_item_page_inp_src;
static MENU_ITEM_T t_menu_item_page_inp_name;

static MENU_ITEM_T t_menu_item_page_tv_pic;
static MENU_ITEM_T t_menu_item_page_tv_aud;
static MENU_ITEM_T t_menu_item_page_tv_aud_sb_settings;
static MENU_ITEM_T t_menu_item_page_tv_audio_settings;

static UINT32 ui4_page_cc;

#ifdef APP_PIP_POP_CTRL
static UINT32 ui4_page_pip;
static UINT32 ui4_page_pip_source;
static MENU_ITEM_T t_menu_item_page_pip_source;
static MENU_ITEM_T t_menu_item_pip_swap;
static MENU_ITEM_T t_menu_item_page_pip;
#endif

static UINT32 ui4_page_tv_setting;
static UINT32 ui4_page_pc_setting;
static MENU_ITEM_T t_menu_item_page_tv_setting;
static MENU_ITEM_T t_menu_item_page_pc_setting;

static MENU_ITEM_T t_menu_item_page_add_analog_scan;
static UINT32 ui4_g_menu_atsc_page_add_analog;

static MENU_ITEM_T t_menu_item_page_ch_scan;
static MENU_ITEM_T t_menu_item_page_ch_scan_new;

static UINT32 ui4_page_ch_sk;
static MENU_ITEM_T t_menu_item_page_ch_sk;

#ifdef APP_TTS_SUPPORT
static MENU_ITEM_T  t_menu_item_page_accessibility;
#endif
UINT32       ui4_page_accessibility;
static MENU_ITEM_T  t_menu_item_page_timers;

#ifdef APP_CEC_MENU
static MENU_ITEM_T t_menu_item_page_cec;
static MENU_ITEM_T t_menu_item_page_cec_dev_discovery;
#endif

#ifdef APP_2K12_RETAIL_DEMO_MODE
static MENU_ITEM_T t_menu_item_page_help_demo_mode;
#endif
static CHAR sn_path[36] =  "/3rd_rw/serial_number";


#ifdef ENABLE_MENU_DLNA_SETTINGS
#if defined (APP_NET_DLNA_SUPPORT) && defined(APP_NETWORK_SUPPORT)
static UINT32      ui4_page_dlna_setting;
static MENU_ITEM_T t_menu_item_page_dlna_setting;
#endif
#endif

MENU_ITEM_T t_g_menu_item_page_check_info;
MENU_ITEM_T t_g_menu_item_page_ver_info;
MENU_ITEM_T t_g_menu_item_page_vid_3d_mode;
MENU_ITEM_T t_g_menu_item_page_wide_mode;
MENU_ITEM_T t_g_menu_item_page_support_code;

#ifdef APP_MENU_3D_BRIGHTNESS_BOOST
MENU_ITEM_T t_g_menu_item_3d_brightness_boost;
#endif

MENU_ITEM_T             t_menu_item_soft_power_cycle;
MENU_ITEM_T             t_menu_item_reset_tv_ad_id;
MENU_ITEM_T             t_menu_item_oled_screen_refresh_1;
MENU_ITEM_T             t_menu_item_oled_screen_refresh_2;
MENU_ITEM_T             t_g_menu_custom_item_advertising;


#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
UINT32 ui4_page_menu_language_dialog;
UINT16 ui2_menu_language_new_idx;
static UINT16 aui2_lang_id[MLM_MENU_NUM_LANG] = {MLM_MENU_LANG_ENG, MLM_MENU_LANG_SPA, MLM_MENU_LANG_FRE};
static UINT16 aui2_lang_idx[MLM_MENU_NUM_LANG] = {0, 2, 1};
#endif

static BOOL b_is_factory_reset = FALSE;
static BOOL b_is_factory_reset_ex = TRUE;
static MENU_ITEM_T  t_menu_item_page_reduce_noise;
extern BOOL            b_is_press_ok_from_check_update;
static BOOL b_last_444_content_status = FALSE;
static BOOL b_last_444_on_status = FALSE;
static BOOL b_last_hide_supportcode_status = TRUE;
/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/

static BOOL _is_adv_vid_local_dimming_enable(VOID);
static BOOL _is_hdmi_sdr_hdr_444_content(VOID);

/*-----------------------------------------------------------------------------
                    static functions implementation
 ----------------------------------------------------------------------------*/
BOOL   a_menu_is_cust_pic_mode_and_locked(VOID); // If the picture mode is customer picture mode and it's status is locked then disable the PQ items which relates to the picture mode .
static BOOL _is_vid_more_sz_enabled(VOID);
static BOOL _is_vid_more_pos_enabled(VOID);
static BOOL _is_VRR_enable_and_VRR_stream_detect(VOID);

static BOOL _is_full_color_444_enable();

static BOOL _is_native_app_enabled(VOID);






static UINT16 _get_parental_ctrl_enable_idx(VOID)
{
    UINT8   ui1_rating_enabled;
    UINT8   ui1_val = RATING_ENABLED_STATUS_ON;
    SIZE_T  z_size = ICL_RECID_RATING_ENABLED_STATUS_SIZE;

    a_icl_get(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
            &ui1_val, &z_size);

    if (RATING_ENABLED_STATUS_OFF == ui1_val)
    {
        ui1_rating_enabled = 0;
    }
    else
    {
        a_cfg_get_rating_enabled(&ui1_rating_enabled);
    }

    #ifdef APP_NAV_PIP_VCHIP_SOL
    return (ui1_rating_enabled == APP_CFG_RATING_ENABLED_OFF) ? 0 : 1;
    #else
        return ui1_rating_enabled ? 1 : 0;
    #endif
}


static BOOL _is_support_3D(VOID)
{
    INT32       i4_ret = MENUR_OK;
    BOOL        b_3D_support = FALSE;

#ifdef APP_CUST_PLT_OPT
    i4_ret = a_cfg_custom_plf_opt_get_3d_support(&b_3D_support);
    DBG_INFO(("\n------get 3D support , ret:%d , support: %d\n", i4_ret, b_3D_support? 1:0));
#else
    if (a_app_cust_plt_opt())
    {
        i4_ret = a_cfg_custom_plf_opt_get_3d_support(&b_3D_support);
        DBG_INFO(("\n------get 3D support , ret:%d , support: %d\n", i4_ret, b_3D_support? 1:0));
    }
#endif

    return b_3D_support;
}

static VOID _clean_svl_and_tsl(VOID)
{
    INT32 i4_ret = 0;

    /* clean air svl */
    if (t_g_menu_common.h_svl_air != NULL_HANDLE)
    {
        i4_ret = c_svl_clean(t_g_menu_common.h_svl_air);
        if (i4_ret != SBR_OK)
        {
            DBG_ERROR(("<MENU>Failed to clean Air SVL in the memory. [i4_ret = %d]\r\n", i4_ret));
        }

        t_g_menu_common.b_svl_air_dirty = TRUE;
    }

    /* clean cable svl */
    if (t_g_menu_common.h_svl_cable != NULL_HANDLE)
    {
        i4_ret = c_svl_clean(t_g_menu_common.h_svl_cable);
        if (i4_ret != SBR_OK)
        {
            DBG_ERROR(("<MENU>Failed to clean Cable SVL in the memory. [i4_ret = %d]\r\n", i4_ret));
        }

        t_g_menu_common.b_svl_cable_dirty = TRUE;
    }

    /* clean air tsl */
    if (t_g_menu_common.h_tsl_air != NULL_HANDLE)
    {
        i4_ret = c_tsl_clean(t_g_menu_common.h_tsl_air);
        if (i4_ret != SBR_OK)
        {
            DBG_ERROR(("<MENU>Failed to clean Air SVL in the memory. [i4_ret = %d]\r\n", i4_ret));
        }

        t_g_menu_common.b_tsl_air_dirty = TRUE;
    }

    /* clean cable tsl */
    if (t_g_menu_common.h_tsl_cable != NULL_HANDLE)
    {
        i4_ret = c_tsl_clean(t_g_menu_common.h_tsl_cable);
        if (i4_ret != SBR_OK)
        {
            DBG_ERROR(("<MENU>Failed to clean Cable SVL in the memory. [i4_ret = %d]\r\n", i4_ret));
        }

        t_g_menu_common.b_tsl_cable_dirty = TRUE;
    }
}

/* Reset TV Settings */
static VOID _reset_pub(VOID)
{
    #ifdef APP_LED_LOGO_CTRL
    /* reset led logo ctrl to default */
    a_cfg_custom_set_led_logo_ctrl(0);
    #endif

    /* Disable CEC function. */
    a_cfg_set_cec_func (APP_CFG_CEC_OFF);

    a_cfg_custom_reset_public_default();

    a_cfg_custom_reset_usr_clr_temp(ACFG_ACCESS_FACTORY);

#ifdef APP_CUST_RESET_DAYLIGHT_SAVING_SETTING_IN_TV_RESET
        a_cfg_custom_reset_daylight_saving_setting();
#endif

    menu_reset_audio_stream();

    /* set acr default value */
    a_cfg_custom_set_acr(ACFG_ACR_ON);

    if (a_cfg_custom_get_wifi_remote_support())
    {
        a_cfg_custom_update_vol_control();
    }

#ifdef APP_C4TV_SUPPORT
    a_c4tv_apron_reset_default();
#endif

    /* Sleep timer off */
    a_sleep_timer_stop();

    menu_custom_chg_lang();
}

static VOID _reset_pri(VOID)
{

    a_cfg_reset_private_default();

    /* Reset Input Source Block */
    /* Auto done in ACFG */

    /* Reset Block Channel */

    menu_reset_svl_by_mask(t_g_menu_common.h_svl_air,
                           SB_VNET_BLOCKED,
                           0);

    menu_reset_svl_by_mask(t_g_menu_common.h_svl_cable,
                           SB_VNET_BLOCKED,
                           0);

    /* Try to unblock service since Channel Block/Input Src Block changed */

    if(c_svctx_unblock_svc(t_g_menu_common.h_svctx, FALSE) != SVCTXR_OK)
    {
        DBG_ERROR(("<MENU> (MAIN) c_svctx_unblock_svc() failed.\n"));
    }
    if(c_svctx_unblock_svc(t_g_menu_common.h_svctx_sub, FALSE) != SVCTXR_OK)
    {
        DBG_ERROR(("<MENU> (SUB) c_svctx_unblock_svc() failed.\n"));
    }

#ifdef APP_C4TV_SUPPORT
    a_c4tv_apron_reset_default();
#endif


    a_sleep_timer_stop();

    /* reset the RRT */
    a_rating_atsc_storage(FALSE);

    menu_custom_chg_lang();
}

static VOID _reset_fac(VOID)
{
    _clean_svl_and_tsl();

    a_sleep_timer_stop();

#ifdef APP_C4TV_SUPPORT
    a_c4tv_apron_reset_default();
#endif

    a_rating_atsc_storage(FALSE);

    menu_custom_chg_lang();
}

static VOID _chg_country_code(VOID)
{
    UINT16 ui2_country_code;
    extern VOID menu_time_local_setting_set_country(UINT16 ui2_idx);

    menu_custom_page_get_tmp_country_code(&ui2_country_code);
    menu_time_local_setting_set_country(ui2_country_code);

    a_tv_net_reset_3rd_ap_data(APP_TV_NET_RESET_ITEM_ALL);
    a_tv_custom_set_tos(FALSE);
    a_tv_custom_set_privacy(FALSE);
    a_tv_custom_clear_tos_version();

    a_amb_reboot();
}

#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
UINT16 menu_get_gui_lang_idx(VOID)
{
    INT32   i4_ret;
    ISO_639_LANG_T s639_lang;
    UINT16 ui2_idx;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        return 0;
    }

    ui2_idx = mlm_menu_s639_to_langidx(s639_lang);

    return aui2_lang_idx[ui2_idx];
}





static VOID _set_gui_lang_idx(UINT16 ui2_idx)
{
    ISO_639_LANG_T  s639_lang;

    mlm_menu_langidx_to_s639(aui2_lang_id[ui2_idx], s639_lang);
    a_cfg_set_gui_lang(s639_lang);

    menu_chg_lang(aui2_lang_id[ui2_idx]);

}

static VOID _reset_menu_language(VOID)
{
    UINT16  ui2_idx  = ui2_menu_language_new_idx;

    _set_gui_lang_idx(ui2_idx);

    a_amb_reboot();
}

static VOID _cancel_menu_language(VOID)
{
    INT32   i4_ret;

    i4_ret = a_ui_simple_dialog_hide(ui4_page_menu_language_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_float(ui4_page_menu_language_dialog, FALSE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);
    return;
}

#endif



BOOL menu_is_vrr_enable_and_vrr_stream_detect(VOID)
{

    return _is_VRR_enable_and_VRR_stream_detect();

}


//MVV-4803
//BSP(Aldrich) and VIZIO(Derek) need grayout  and set off folow UI when VRR Stream be detested in Phase 1
//1. Black detail
//2. Local contrast
//3. Signal nosie
//4. Contour smoothing
//5. Judder reduction
//6. Motion blir reduction
//7. Clarn action
//8. Active full arry
static BOOL _is_VRR_enable_and_VRR_stream_detect(VOID)
{
#if 1
    return a_cfg_cust_is_VRR_enable_and_driver_detect_VRR();
#else
    INT32   i4_ret = 0;
    INT16   i2_VrrEnable = 0;
    BOOL    b_vrr_apply = FALSE;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i2_VrrEnable);
    //MENU_LOG_ON_FAIL(i4_ret);
    if( i4_ret < 0 )
    {
        DBG_LOG_PRINT(("<MENU> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        return FALSE;
    }

    if( i2_VrrEnable != ACFG_CUST_COMMON_ON )
    {
        return FALSE;
    }

    //i4_ret = a_cfg_cust_drv_get_vrr_status(&b_vrr_apply, 1);
    //MENU_LOG_ON_FAIL(i4_ret);
    b_vrr_apply = a_cfg_cust_drv_get_vrr_status();

    if( (b_vrr_apply || a_acfg_cust_vrr_is_enable_and_detect_stream()) )
    {
        return TRUE;
    }

    return FALSE;
#endif
}

static VOID _service_check(VOID)
{
    INT32 i4_ret         = MENUR_OK;
    UINT8 pui1_fw_status = 0;
    UINT8 pui_fw_policy  = 0;
    b_is_press_ok_from_check_update = FALSE;
    i4_ret = a_nav_updater_check_network_update(&pui1_fw_status,&pui_fw_policy);
    DBG_INFO(("<MENU> Do SERVICE CHECK i4_ret = %d\n", i4_ret));
}

BOOL menu_get_factory_reset_status(VOID)
{
    return b_is_factory_reset;
}

extern BOOL a_msg_convert_custom_stop(BOOL b_wait_for_power_off);

static VOID _service_reset(VOID)
{
    INT32 i4_ret = MENUR_OK;
    UINT8       ui1_save_led_ctrl_state;

    ui1_save_led_ctrl_state = a_cfg_custom_get_led_logo_ctrl();
#if 0
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

    a_cfg_cust_backlight_onoff(FALSE);
#else
    a_cfg_cust_blank_screen();
#endif
    a_cfg_cust_audio_mute(TRUE);
    cmd_convert_shutdown("suspend");
    cmd_convert_wait_shtdn_signal();
    a_msg_convert_custom_stop(FALSE);

    if(a_app_tts_is_enable())
    {
        a_cfg_cust_audio_mute(FALSE);
        TTS_PLAY(L"power off");
        c_thread_delay(1000);
    }

    a_cfg_custom_set_led_logo_ctrl(ui1_save_led_ctrl_state);

    i4_ret = a_cfg_custom_service_reset(1,TRUE);
    DBG_INFO(("<MENU> Do SERVICE RESET i4_ret = %d\n", i4_ret));
}


static VOID _menu_set_factory_reset_status(VOID)
{
    b_is_factory_reset = TRUE;
}

UINT32 _menu_set_hdmi_edid(VOID)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT8   ui1_idx= 0;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_HDMI_EDID;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE;

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
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("!!!!%s fail\n", __func__));
        return i4_ret;
    }

    return i4_ret;
}

static VOID _reset_tv_ad_id(VOID)
{
    UTF16_T        *pw2s_text       = NULL;
    WDK_TOAST_T    t_toast          = {0};
    UTF16_T        w2s_tmp_str[512] = {0};

    b_is_read_reset_advertiser_info = TRUE;
    rest_event_notify("tv_settings/system/reset_and_admin/tvad_id_reset", 0, NULL);
#if 0
    pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESET_TV_AD_ID_MSG);
    c_uc_w2s_strcpy(w2s_tmp_str, pw2s_text);
    c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_WARNING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;
    t_toast.style.style_4.w2s_str = (VOID*)w2s_tmp_str;
    menu_send_string_to_nav_toast(&t_toast);
#endif
}

static VOID _oled_screen_refresh_start_now(VOID)
{
    a_cfg_cust_set_oled_panel_refresh_value(SCREEN_REFRESH_START_AT_NOW);
}

static VOID _oled_screen_refresh_cancel(VOID)
{
    a_cfg_cust_set_oled_panel_refresh_value(SCREEN_REFRESH_START_CANCEL);
}
#if 0/*Unused*/
static VOID _oled_screen_refresh_start_at_power_off_popup_cancel(VOID)
{
     a_cfg_cust_set_oled_panel_refresh_value(SCREEN_REFRESH_START_AT_POWER_OFF);
}
#endif
static VOID _oled_screen_refresh_start_at_power_off(VOID)
{
   a_cfg_cust_set_oled_panel_refresh_value(SCREEN_REFRESH_START_AT_POWER_OFF);
}

VOID menu_clear_memory_ex(BOOL b_need_reboot)
{
    if (!b_need_reboot)
    {
        b_is_factory_reset_ex = FALSE;
    }

    clear_memory();

    b_is_factory_reset_ex = TRUE;
}
static VOID _menu_hierarchy_clean_virtual_input(VOID)
{
    UINT16  ui2_i;
    CHAR    s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    for(ui2_i = 0; ui2_i < 5; ui2_i++)//Find del id
    {
        //Coverity ID:4490831
        if (a_cfg_set_vtrl_name(ui2_i, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN) != APP_CFGR_OK)
        {
            DBG_ERROR(("\n[MENU HIERARCHY] clean virtual input fail,can not set vtrl name"));
        }

        a_cfg_set_name_display(1,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);

        //Coverity ID:44074
        if (a_cfg_set_name_display(2,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN) != APP_CFGR_OK){
            DBG_ERROR(("\n[MENU HIERARCHY] clean virtual input fail,can not set French name dispaly"));
        }

        if (a_cfg_set_name_display(3,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN) != APP_CFGR_OK)
        {
            DBG_ERROR(("\n[MENU HIERARCHY] clean virtual input fail,can not set Spanish name diaplay"));
        }

    }
}

extern INT32 MTVDECEX_HDMI_SetEdidIndexByPort(UINT8 ui1_port_idx,UINT8 ui1_edid_idx,BOOL b_hdmi_mode);

static INT32 clean_3rd_reset()
{
    return cmd_reset_3rd_party("3rd_party");
}

extern BOOL a_msg_convert_custom_stop(BOOL b_wait_for_power_off);

VOID clear_memory(VOID)
{
    UINT8 ui1_hdmi_num = a_cfg_gethdmiports();
    UINT8 ui1_idx;

    DBG_LOG_PRINT(("[Factory][Reset]{%s,%d} \n", __FUNCTION__, __LINE__ ));

#ifdef MT5695_MODEL
    UINT32 ui4_panel_display = 0;
    UINT32 ui4_panel_ex_factory = 0;
    INT64  t_last_deline_time = a_cfg_custom_get_oled_demo_mode_decline_time();
    INT64  t_last_complete_time = a_cfg_custom_get_oled_last_screen_refresh_time();
    UINT8 ui1_error_count = 0;

    a_cfg_custom_get_oled_error_detect_count(&ui1_error_count);
    a_cfg_custom_get_oled_ex_factory_display_time(&ui4_panel_ex_factory);
    a_cfg_custom_get_oled_panel_display_time(&ui4_panel_display);
#endif
#if 0
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
    a_cfg_cust_backlight_onoff(FALSE);
#else
    a_cfg_cust_blank_screen();
#endif
    a_cfg_cust_audio_mute(TRUE);
    a_tv_set_audio_mute(TV_AUDIO_MUTE_MASK_RESET, TRUE);

    a_msg_convert_custom_stop(FALSE);

    clean_3rd_reset();

    // disable power key while factory reset
    a_amb_enable_power_key(FALSE);

    /* do NOT allow banner popup */
    a_tv_custom_set_banner_visiable_allow(FALSE);

#ifdef APP_ULI_UPG_SUPPORT
        {
            UINT32 ui4_buff_len = 64;
            UINT32  ui4_digs_len = 0;
            CHAR        serial_num[64] = "1234";
            CHAR        temp_string[64] = "1234";
            char        cmd[64];

            memset(cmd, 0, 64);
            c_memset(serial_num, '\0', 64);
            c_memset(temp_string, 0, 64);
            a_uli_get_serial_number((UINT8*)serial_num, &ui4_buff_len);
            if (ui4_buff_len < 15)
            {
                c_strncpy(temp_string, serial_num + 2, 2);
                c_strncat(temp_string, serial_num, 2);
                c_strncat(temp_string, serial_num + 6, 2);
                c_strncat(temp_string, serial_num + 4, 2);
                c_strncat(temp_string, serial_num + 8, 5);

                ui4_digs_len = c_strlen(temp_string);
                c_strcat(temp_string, serial_num + ui4_digs_len);
            }
            else
            {
                c_strncpy(temp_string, serial_num + 8, 2);
                c_strncat(temp_string, serial_num, 8);

                ui4_digs_len = c_strlen(temp_string);
                c_strcat(temp_string, serial_num + ui4_digs_len);
            }

            a_menu_custom_save_sn_to_file(temp_string);
        }
#endif


#ifdef APP_WIFI_REMOTE
    INT32 i4_ret;

    if (a_cfg_custom_get_wifi_remote_support())
    {
        c_set_remote_reconnect_times(240); //set remote to retry reconnections for 2mins long
        DBG_INFO(("WiFi remote reconnection retries set to 2mins long\n"));
        c_thread_delay(200);
        AP_SYSTEM_CALL("sh /etc/scripts/wifi_direct_suspend.sh");
    }
#endif

#ifdef TVIS_SUPPORT
    AP_SYSTEM_CALL("rm -rf /data/tvis; sync");
    AP_SYSTEM_CALL("rm -rf /data/app/inscape*; sync");              //hongzhao 2020/2/12 add for acr downloadable
#endif

#ifdef APP_EMANUAL_SUPPORT
#ifdef APP_EMANUAL_SP6_SUPPORT
    // remove manual folder
    AP_SYSTEM_CALL("rm -rf /data/manual; sync");
#endif
#endif

    if (0 == (access("/data/cobalt", 0)))
    {
        AP_SYSTEM_CALL("rm -rf /data/cobalt/.starboard.*; sync");
    }

    a_rest_app_factory_reset();

    AP_SYSTEM_CALL("rm -f /data/cfg_energy; sync; sync; sync");

    _menu_set_factory_reset_status();

    /*if don't clear wifi_device_info banner will read info wrong after reset*/
    a_cfg_custom_clear_device_info();

#ifdef NETFLIX_SUPPORT
    c_netflix_deactivate(); //stop netflix
#endif

#ifdef NETFLIX_SUPPORT_TEMP
    AP_SYSTEM_CALL("mount -t tmpfs none /data/netflix/nrd-app/data/var");
#endif
    a_tv_custom_set_viewing_data_accepted(FALSE);
    a_tv_custom_set_viewing_data_accepted_by_oobe_menu(FALSE);
    a_tv_custom_set_tos(FALSE);
    a_tv_custom_set_viewing_data_accepted(FALSE);
    a_tv_custom_set_viewing_data_accepted_by_oobe_menu(FALSE);
    rest_event_notify("tv_settings/cast/tos_accepted", 0, "");
    a_tv_custom_set_privacy(FALSE);
    a_tv_custom_clear_tos_version();
    a_tv_custom_clear_http_url_status();
    a_cfg_set_tts_switch_status(0);
    a_cfg_update_tts_switch_status();
    /* reset viewing data to not showed. */
    a_tv_custom_set_viewing_data_show(FALSE);
    a_cfg_set_dt_sync_mode(APP_CFG_DT_SYNC_MODE_AUTO);
    if (a_tv_stop(menu_get_crnt_svctx()) != TVR_OK)
    {
        DBG_ERROR (("<MENU> Stop service failed! \n\r"));
    }
    a_tv_net_send_cmd(":dtv_app_mtk,am,:unblock_3rd\n");

#ifdef APP_C4TV_SUPPORT
    DBG_INFO (("<MENU> reset c4tv timezone\n\r"));
    a_c4tv_apron_set_timezone("America/Los_Angeles");
    a_c4tv_apron_set_locale("en");
    a_c4tv_apron_set_time_format(1);/* 1 for 12 hour 0 for other*/
    a_c4tv_apron_reset_default();
#endif

#ifndef APP_CUST_FAC
    if (a_app_cust_fac())
#endif
    {
        a_cfg_custom_reset_fac();
    }
    else
    {
        DBG_INFO (("<MENU> No custom factory, call a_cfg_custom_reset_public_default() instead! \n\r"));
        a_cfg_custom_reset_public_default();
    }

#ifdef MT5695_MODEL
    a_cfg_custom_set_oled_error_detect_count(ui1_error_count);  // error count need keep during reset
    a_cfg_custom_set_oled_ex_factory_display_time(ui4_panel_ex_factory); //total display time should keep  during reset
    a_cfg_custom_set_oled_panel_display_time(ui4_panel_display);        //panel display time should keep in epprom
    a_cfg_custom_set_oled_last_screen_refresh_time(t_last_complete_time);
    a_cfg_custom_set_oled_demo_mode_decline_time(t_last_deline_time);
#endif
    _menu_hierarchy_clean_virtual_input();

#ifdef APP_LED_LOGO_CTRL
    /* reset led logo ctrl to default */
    a_cfg_custom_set_led_logo_ctrl(0);
#endif


    a_cfg_blegatt_cache_dev_reset();

    /* Reset Power Mode */
    a_cfg_custom_reset_power_mode();

    //a_cfg_custom_reset_usr_clr_temp(ACFG_ACCESS_FACTORY);

#ifdef VIZIO_PORTING
    c_pcl_set_wifi_wol_ctrl(PCL_WIFI_WOL_DISABLE);
#endif

    a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);

#ifdef APP_C4TV_SUPPORT
    DBG_LOG_PRINT(("<MENU> %s, a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_START_OOBE \n\r", __FUNCTION__));
    a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));
#else
    a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT);
#endif

    a_cfg_custom_set_wzd_subpage_id(0);
    a_cfg_custom_reset_channel_lock();
    a_cfg_set_password_default();

    a_cfg_custom_set_bootup_assistant_flag(ACFG_BOOTUP_ASSISTANT_FAC_RESET);
    DBG_LOG_PRINT(("%s() set bootup assistant flag\n", __FUNCTION__));

#ifdef APP_ULI_UPG_SUPPORT
    //a_uli_project_remove_user_info();
#endif
    _clean_svl_and_tsl();

    //a_cfg_ch_lst_store();
    a_cfg_ch_lst_air_store_ex(DUAL_BANK_AS_MODE_TO_MAIN_SUB);
    a_cfg_ch_lst_cable_store_ex(DUAL_BANK_AS_MODE_TO_MAIN_SUB);

    a_cfg_set_crnt_channel_id_default();
    a_cfg_custom_reset_input_src_pic_setting();
    a_cfg_11_point_gain_default();
#ifdef APP_ARC_ONLY
    /*CEC default setting:ARC only/sac on*/
    /* change CEC default setting from ARC only to Enable, follow UI spec4.1 4.9.5 */
    //a_cfg_set_cec_func (APP_CFG_CEC_ARC_ONLY);
    a_cfg_set_cec_sac_func(1);
#endif

#ifdef MW_FAST_BOOT_PRE_SELECT
    /* for CR:DTV00447913 */
    c_sys_config_reset();
#endif
    if(a_cfg_cust_get_support_local_dimming())
    {
        ACFG_CustDrv_Set_Backlight(10000, 0);
    }
    a_sleep_timer_stop();

    c_dt_set_utc(APP_RTC_LOW_BOUNDARY, 0);

    a_rating_atsc_storage(FALSE);
    a_cfg_set_dt_sync_mode(APP_CFG_DT_SYNC_MODE_AUTO);
    for(ui1_idx = 0; ui1_idx < ui1_hdmi_num; ui1_idx++)
    {
        MTVDECEX_HDMI_SetEdidIndexByPort(ui1_idx + 1,0,FALSE);
    }

    a_cfg_cust_set_hide_from_input(0);
    AP_SYSTEM_CALL("rm /data/hdmi*; sync");

    _menu_set_hdmi_edid();
    menu_custom_chg_lang();
    set_power_on_device_to_default();
    AP_SYSTEM_CALL("rm -rf /data/uli/check_update.json");
    AP_SYSTEM_CALL("sh /application/vzservices/bin/FactoryReset.sh");

#if(ENABLE_VIZIO_AUTO_PC)
    // Delete user setting
    DBG_LOG_PRINT(("[Factory][Reset][AutoPC]{%s,%d} Delete user setting.\n", __FUNCTION__, __LINE__ ));
    AP_SYSTEM_CALL("rm -rf /data/auto_pc_*.db");
#endif

    AP_SYSTEM_CALL("sync");

    if (b_is_factory_reset_ex)
    {
        DBG_LOG_PRINT((" factory reset reboot\n"));
        a_cfg_store();
        a_amb_reboot();
    }
}
#if 0/*Unused*/
static BOOL _is_tv_input_src(VOID)
{
    ISL_REC_T   t_isl_rec;

    menu_get_crnt_isl(&t_isl_rec);

    return t_isl_rec.e_src_type == INP_SRC_TYPE_TV;
}
#endif
static BOOL _is_vga_hidden(VOID)
{
    ISL_REC_T   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T t_timing;

    HANDLE_T    h_svctx;

    c_memset(&t_timing, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    h_svctx = menu_get_crnt_svctx();
    c_svctx_get_video_src_resolution(h_svctx, &t_timing);

    menu_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA &&
       t_timing.e_timing_type != VSH_SRC_TIMING_VIDEO)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

static BOOL _is_new_vga_hidden(VOID)
{
    ISL_REC_T   t_isl_rec;

    menu_get_crnt_isl(&t_isl_rec);

#ifdef APP_MENU_MMP_COEXIST
    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        return TRUE;
    }
#endif

    if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
    {
        return TRUE;
    }

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/* when vga/hdmi/mmp/3rd/component resume,parental controls should be hidden */
static BOOL _is_vga_hdmi_hidden(VOID)
{
    ISL_REC_T   t_isl_rec;
    INT32       i4_ret = -1;
    #ifdef APP_AV_COMPONENT_USE_ONE_PORT
    UINT8 SrcId = 0;
    #endif

#ifdef APP_MENU_MMP_COEXIST
    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        return TRUE;
    }
#endif
    /* judge if 3RD resume */
   if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status())
    {
        return TRUE;
    }
    menu_get_crnt_isl(&t_isl_rec);
    /* Only tuner and complsite are visible*/
#ifdef APP_AV_COMPONENT_USE_ONE_PORT
    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA ||
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR || /* Component*/
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI ||
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI ||
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI))
    {
        /*AV source and component source use the same port*/
        if(t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI)
        {
            i4_ret = a_cfg_custom_get_srcid_com_or_av(&SrcId);
                if(i4_ret != MENUR_OK)
                {
                    DBG_INFO(("<MENU>a_cfg_custom_get_srcid_com_or_av fail   fail(%d), line(%d)\n",i4_ret,__LINE__));
                    return TRUE;
                }

                if((SrcId == 1) || (SrcId == 0))/*component source or no source*/
                {
                    return TRUE;
                }
                else /*2, AV source */
                {
                    return FALSE;
                }
        }
        return TRUE;
    }
#endif
    else
    {
        return FALSE;
    }
}

static BOOL _is_vga_connected(VOID)
{
    ISL_REC_T   t_isl_rec;

    menu_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
    {
        if(menu_is_signal_loss())
        {
            return FALSE;
        }

        if(menu_is_video_block())
        {
            return FALSE;
        }

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static BOOL _is_pic_mode_hidden(VOID)
{
    ISL_REC_T   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T t_timing;

    HANDLE_T    h_svctx;

    c_memset(&t_timing, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    h_svctx = menu_get_crnt_svctx();
    c_svctx_get_video_src_resolution(h_svctx, &t_timing);

    menu_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA ||
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI) &&
       t_timing.e_timing_type != VSH_SRC_TIMING_VIDEO)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static BOOL _is_adv_vid_hidden(VOID)
{
    return !_is_vga_hidden();
}

static BOOL _is_adv_vid_enable(VOID)
{
    INT32       i4_ret;
    ISL_REC_T   t_isl_rec;
    SVL_REC_T   t_svl_rec;
    BOOL        b_found = FALSE;
    BOOL        b_enable = TRUE;

    i4_ret = menu_get_crnt_isl(&t_isl_rec);
    if ((i4_ret == MENUR_OK) && (t_isl_rec.e_src_type == INP_SRC_TYPE_TV))
    {
        menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
        if ((b_found) && (t_svl_rec.uheader.t_rec_hdr.e_brdcst_type != BRDCST_TYPE_ANALOG))
        {
            /* DTV */
            //b_enable = FALSE;
        }
        else
        {
            /* ATV */
            b_enable = TRUE;
        }
    }

    return b_enable;
}

static BOOL _is_h_pos_enabled(VOID)
{
    INT32                           i4_ret;
    BOOL                            b_enable = TRUE;
    SCC_VID_OVER_SCAN_CLIPPER_T     t_overscan = {0,0,0,0};
    CHAR                            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    ISL_REC_T                       t_isl_rec;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_video_get_overscan_with_h_v_size(s_disp_name, &t_overscan);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));
    menu_get_crnt_isl(&t_isl_rec);

    /* HDMI Source always enable */
    if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI))
    {
        b_enable = TRUE;
    }

    if (t_overscan.ui4_left == 0 && t_overscan.ui4_right == 0)
    {
        b_enable = TRUE;
        /* Do Nothing */
    }

    b_enable = b_enable && _is_adv_vid_enable();

    return b_enable;
}

static BOOL _is_v_pos_enabled(VOID)
{
    INT32                           i4_ret;
    BOOL                            b_enable = TRUE;
    SCC_VID_OVER_SCAN_CLIPPER_T     t_overscan = {0,0,0,0};
    CHAR                            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    ISL_REC_T                       t_isl_rec;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = acfg_cust_video_get_overscan_with_h_v_size(s_disp_name, &t_overscan);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));
    menu_get_crnt_isl(&t_isl_rec);

    /* HDMI Source always enable */
    if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI))
    {
        b_enable = TRUE;
    }

    if (t_overscan.ui4_top == 0 && t_overscan.ui4_bottom == 0)
    {
        b_enable = TRUE;
        /* Do Nothing */
    }

    return b_enable;
}

#ifdef APP_PIP_POP_CTRL

static BOOL _is_pip_enbale(VOID)
{
    TV_MODE_T e_tv_mode;
    INT32     i4_ret;

    i4_ret = nav_get_tv_mode(&e_tv_mode);
    if (i4_ret != NAVR_OK) {
        return FALSE;
    }

    if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
        return FALSE;
    }
    return TRUE;
}
#endif

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
static BOOL _is_usa_hidden(VOID)
{
#if 0
    INT32   i4_ret = MENUR_OK;
    ACFG_COUNTRY_CODE_T t_country;

    i4_ret = a_cfg_custom_get_country_code(&t_country);
    if (CFGR_OK == i4_ret)
    {
        if (t_country == ACFG_COUNTRY_CODE_CA
            || t_country == ACFG_COUNTRY_CODE_MEX)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
#else
    return FALSE;
#endif
}

static BOOL _is_can_hidden(VOID)
{
#if 0
    INT32   i4_ret;
    ACFG_COUNTRY_CODE_T t_country;

    i4_ret = a_cfg_custom_get_country_code(&t_country);
    if (CFGR_OK == i4_ret)
    {
        if (t_country == ACFG_COUNTRY_CODE_US
            || t_country == ACFG_COUNTRY_CODE_MEX)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
#else
    return FALSE;
#endif
}
#endif


static BOOL _is_date_time_enable(VOID)
{
    UINT8  ui1_dt_sync_mode;

    a_cfg_get_dt_sync_mode(&ui1_dt_sync_mode);
    if (ui1_dt_sync_mode == APP_CFG_DT_SYNC_MODE_AUTO)
    {
        return FALSE;
    }
    return TRUE;
}

static BOOL _is_hv_pos_hidden(VOID)
{
    ISL_REC_T   t_isl_rec;

    menu_get_crnt_isl(&t_isl_rec);
    if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        return FALSE;
    }
    else if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
    {
        if(t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
        {
            /* VGA */
            return TRUE;
        }
        else
        {
            /* Other AV */
            return FALSE;
        }
    }
    else
    {
        return TRUE;
    }
}

static BOOL _is_hv_pos_enabled(VOID)
{
    return !menu_is_signal_loss();
}

static BOOL _is_ypbpr_phase_hidden(VOID)
{
    INT32   i4_ret;
    ISL_REC_T   t_isl_rec;

    i4_ret = menu_get_crnt_isl(&t_isl_rec);
    if(i4_ret != MENUR_OK)
    {
        return TRUE;
    }

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

static BOOL _is_tv_page_enabled(VOID)
{
    ISL_REC_T   t_isl_rec;

    menu_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        return TRUE;
    }

    return FALSE;
}

static BOOL _is_palying_retail_demo(VOID)
{
    ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
#ifdef APP_RETAIL_MODE_SUPPORT
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
#endif

    return (ACFG_RETAIL_MODE_NORMAL == t_retail_mode);
}

static INT32 _menu_get_inpt_rec(ISL_REC_T* pt_isl_rec)
{
    INT32       i4_ret = -1;
    UINT8       ui1_input;
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];

    /* Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    MENU_CHK_FAIL(i4_ret);

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input, pt_isl_rec);

    MENU_CHK_FAIL(i4_ret);
    return i4_ret;
}

static BOOL _is_engary_saving_mode_hide(VOID)
{
    return TRUE;
}


static BOOL _is_name_input_auto_enable(VOID)
{
    INT32               i4_ret = MENUR_OK;
    ISL_REC_T           t_isl_rec;

    i4_ret = _menu_get_inpt_rec(&t_isl_rec);
    MENU_CHK_FAIL(i4_ret);

    if (t_isl_rec.e_src_type == INP_SRC_TYPE_TV )    /* TV */
    {
        return FALSE;
    }
    else if (t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL)  /* virtual */
    {
        return FALSE;
    }
    else if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)     /* HDMI */
    {
        return TRUE;
    }
    else if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV
        && (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI
        || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMP_VIDEO
        || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR))    /* COMP */
    {
        return TRUE;
    }
    return FALSE;
}

static BOOL _is_oled_panel_auto_hide(VOID)
{
    if(a_cfg_cust_oled_support() == TRUE)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL menu_is_voice_remote_hidden(VOID)
{
    return menu_common_get_chipset() != CHIPSET_5695
        && ((menu_common_get_chipset() == CHIPSET_5691 || menu_common_get_chipset() == CHIPSET_5583) && access("/tmp/bt_dongle_inserted", 0) != 0);
}

static VOID _menu_get_capabilities_status(VOID *p1, VOID *p2, VOID *p3)
{
    rest_get_capabilities_troubleshoot_status(&b_last_hide_supportcode_status);
    DBG_INFO(("[MENU][%s %d] b_last_hide_supportcode_status : %d\n", __FUNCTION__, __LINE__, b_last_hide_supportcode_status));
}

BOOL menu_is_support_code_hidden(VOID)
{
    return !b_last_hide_supportcode_status;
}

static BOOL _is_retail_mode_start(VOID)
{
    BOOL b_ret = FALSE;
    b_ret = _is_palying_retail_demo();
    DBG_ERROR(("\n[MENU HIERARCHY] _is_palying_retail_demo:%d, line:%d \n", b_ret, __LINE__));

    return !b_ret;
}

static BOOL _is_3d_support_and_3d_playing(VOID)
{
     if( _is_support_3D())
     {
        if ( a_tv_custom_is_3D_mode_playing())
        {
            return TRUE;
        }
     }
     return FALSE;
}

static BOOL _is_not_3d_support_and_3d_playing(VOID)
{
    BOOL b_ret = FALSE;

    if(a_menu_is_cust_pic_mode_and_locked())//customer picture mode  and it's status is locked then disable the PQ items. It's relates to picture mode issue.
    {
        return FALSE;
    }

#ifdef APP_MENU_MMP_COEXIST
    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        if(MMP_BE_BROWSER_MEDIA_TYPE_VIDEO != a_mmp_be_get_media_type())
        {
            return FALSE;
        }
    }
#endif

    b_ret = _is_3d_support_and_3d_playing();
    return !b_ret;
}

extern UINT32  a_ope_lst_get_full_chroma(UINT8* ui1_value);

static BOOL _is_contour_smoothing_enable(VOID)
{
#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    if( acfg_cust_Is_CurHDMI_PQ_PCMode() == TRUE )
    {
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
#endif

    if(a_acfg_cust_is_gll_enable() == TRUE)
    {
        return FALSE;
    }

    if(_is_VRR_enable_and_VRR_stream_detect() == TRUE)
    {
        return FALSE;
    }

    return TRUE;
}

static BOOL _is_dnr_mpeg_noise_reduce_enable(VOID)
{
    BOOL b_ret = TRUE;

    /* 1080P 120Hz not supported */
    CHECK_1080P_120HZ_SUPPORT();


  #if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    if( acfg_cust_Is_CurHDMI_PQ_PCMode() == TRUE )
    {
        return FALSE;
    }
  #else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
  #endif

    if(a_acfg_cust_is_gll_enable() == TRUE)
    {
        return FALSE;
    }

    if(_is_VRR_enable_and_VRR_stream_detect() == TRUE)
    {
        return FALSE;
    }

    b_ret = _is_not_3d_support_and_3d_playing();

    return b_ret;
}

#ifdef NEVER

static BOOL _is_abc_enable(VOID)
{
    SCC_VID_HDR_TYPE_T t_acfg_hdr_type = SCC_VID_PQ_SDR;
    HANDLE_T  h_scc_comp;
    UINT16  ui2_value = 0;
    UINT8   t_retail_mode = 0;

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        return FALSE;
    }

    INT32    i4_dolby_vision = a_icl_custom_get_dolby_vision_status();

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION),&ui2_value);

    if (ui2_value == 1)
    {
        return FALSE;
    }

    c_scc_vid_get_hdr_type(h_g_acfg_scc_main_vid,&t_acfg_hdr_type);

    if ((SCC_VID_PQ_HDR10 == t_acfg_hdr_type)
        ||(SCC_VID_PQ_HDR10PLUS== t_acfg_hdr_type)
        ||(SCC_VID_PQ_HLG == t_acfg_hdr_type)
        ||(i4_dolby_vision == 1)
        )
    {
        return FALSE;
    }

    if(a_menu_is_cust_pic_mode_and_locked())
    {
        return FALSE;
    }

     /*spec 5.2 requirement  active full arryay is > low, we need disable ABC and set OFF  to driver*/
    if(a_cfg_cust_get_support_local_dimming())
    {
        INT16 i2_val = 0;
        if(CFGR_OK == a_cfg_custom_get_dimming_idx(&i2_val)&&
            i2_val > 1)
        {
            return FALSE;
        }

        i2_val = 0;
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                     &i2_val);

        if( (_is_adv_vid_local_dimming_enable()) &&
            (SCC_VID_PQ_SDR == t_acfg_hdr_type) &&
            ((i2_val == ACFG_CUST_PIC_MODE_VIVID) || (i2_val == ACFG_CUST_PIC_MODE_BRIGHT_ROOM)))
        {
            return FALSE;
        }
    }

    return TRUE;

}
#endif /* NEVER */

// Light_sensor
static BOOL _is_abc_enable(VOID)
{
#if 1
    if( FALSE == a_cfg_cust_LightSensor_CheckIfCanTurnOn() )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
            DBG_LOG_PRINT(("[MENU][LightSensor]{%s: %d} Cannot turn on LightSensor => Menu disable!\n", __FUNCTION__,__LINE__ ));
        );

        return FALSE;
    }

#else
    INT16  i2_value = 0;
    INT32  i4_ret   = 0;


    //if( a_cfg_cust_get_support_clear_aciton() == TRUE )
    if( a_cfg_cust_ClaerAction_if_can_turn_on() == TRUE )
    {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION), &i2_value);
        if( i4_ret < 0 )
        {
            DBG_LOG_PRINT(("<MENU> {%s:%d} Cannot get APP_CFG_RECID_VID_CLEAR_ACTION! rtn:%d \n", __FILE__, __LINE__, i4_ret));
            i2_value = 0;
        }

        if (i2_value == 1)
        {
            return FALSE;
        }
    }

    if (a_acfg_cust_get_dynamic_range() != ACFG_CUST_CONTENT_SDR)
    {
        return FALSE;
    }
#endif


    if( a_menu_is_cust_pic_mode_and_locked() )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
            DBG_LOG_PRINT(("[MENU][LightSensor]{%s: %d} is_cust_pic_mode_and_locked => Menu disable!\n", __FUNCTION__,__LINE__ ));
        );

        return FALSE;
    }

    return TRUE;
}


#ifdef APP_MJC_SUPPORT

static BOOL _is_mjc_mode_hidden(VOID)
{
    UINT32  ui4_memc_flag = 0;

    a_cfg_custom_plf_opt_get_model_memc_flag(&ui4_memc_flag);

    if(eNON_MEMC == ui4_memc_flag)
    {
        return TRUE;
    }
    else
    {
#ifdef APP_MENU_MMP_COEXIST
        MMP_BE_BROWSER_STATUS_T e_mmp_browse_status = a_mmp_be_get_browser_status();

        if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status()
            && !((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING == e_mmp_browse_status) ||
            (MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING == e_mmp_browse_status) ||
            (MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING == e_mmp_browse_status) ||
            (MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING == e_mmp_browse_status)))
        {
            return TRUE;
        }
#endif
        return FALSE;
    }
}
#endif


//V5 / M6 need rename ProGaming Engine for V-Gaming Engine
#if 0/*Unused*/
static BOOL _is_rename_v_gaming_engine(VOID)
{
    CHAR   s_name[32] = {0};
    INT32  i4_ret  = 0;
    BOOL   is_support = FALSE;

    i4_ret = a_cfg_custom_get_model_name(s_name);
    ACFG_LOG_ON_FAIL(i4_ret);

    do{
        if(s_name[0] == 'M')
        {
            if(s_name[3] == '6')
            {
                is_support =  TRUE;
            }
            else
            {
                is_support =  FALSE;
            }
            break;
        }
        if(s_name[0] == 'V')
        {
            is_support =  TRUE;
        }

        //2k20 5583 D series FHD support V-gaming eng
        if(s_name[0] == 'D' && s_name[3] == 'f' && (c_strstr(s_name,"-J")!= NULL))
        {
            is_support =  TRUE;
        }
    }while(0);


    return  is_support;
}
#endif






#ifdef NEVER
static BOOL _is_adv_vid_blur_hidden()
{
    BOOL b_support = FALSE;

    MENU_LOG_ON_FAIL(a_cfg_custom_is_reduce_blur_support(&b_support));
    return !b_support;
}

static BOOL _is_adv_vid_blur_enable()
{
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }

    return TRUE;
}
#endif

static BOOL _is_DVI_signal()
{
    CHAR  s_disp_name[SYS_NAME_LEN+1] = {0};
    HANDLE_T  h_scc_comp;

    if (a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name)) == APP_CFGR_OK)
    {
        ISL_REC_T  t_isl_rec = {0};
        SCC_VID_HDMI_DVI_MODE_T  e_hdmi_dvi_mode;

        menu_get_crnt_isl(&t_isl_rec);

        if (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI &&
            t_isl_rec.t_avc_info.e_video_type != DEV_AVC_DVI)
        {
            return FALSE;
        }

        h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0) ? h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid;
        c_scc_vid_get_hdmi_dvi_mode(h_scc_comp, &e_hdmi_dvi_mode);

        if (SCC_VID_HDMI_DVI_MODE_DVI == e_hdmi_dvi_mode)
            return TRUE;
        else
            return FALSE;
    }

    return FALSE;
}

static BOOL _is_filmmaker_mode_hidden(VOID)
{
    return TRUE;
}


static BOOL is_adv_color_space_hidden(VOID)
{

// color space is visiable in any source
#if 0
    ISL_REC_T    t_isl_rec;
    CHAR         s_disp_name[SYS_NAME_LEN+1] = {0};

    if (a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name)) == APP_CFGR_OK &&
        MENUR_OK == menu_get_crnt_isl(&t_isl_rec))
    {
       return (t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL && t_isl_rec.ui1_internal_id == 0);//spec 5.0 smart cast should not show color space
    }
#endif
    return FALSE;
}

#ifdef NEVER

static BOOL _is_dv_444_content()
{
    if(a_acfg_cust_get_video_type == SCC_VID_PQ_DOVI)
    {
        return TRUE;
    }

    if ( a_cfg_cust_video_is_sdr_hdr_444_content() == TRUE )
    {
        return TRUE;
    }

    return FALSE;
}
#endif

static BOOL is_adv_color_space_enable(VOID)
{
    ISL_REC_T    t_isl_rec;
    CHAR         s_disp_name[SYS_NAME_LEN+1] = {0};

    if (a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name)) == APP_CFGR_OK &&
        MENUR_OK == menu_get_crnt_isl(&t_isl_rec) &&
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
    {
        if (a_cfg_get_hdr_type() == SCC_VID_PQ_DOVI)
        {
            return FALSE;
        }
        return TRUE ;
    }
    return FALSE;
}
#ifdef NEVER

static BOOL _is_adv_vid_nr_hidden(VOID)
{
    HANDLE_T                    h_svctx;
    ISL_REC_T                   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};

#ifdef APP_MENU_MMP_COEXIST

#if 0
        INT16 i2_val = 0;
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_MODE), &i2_val);

        /* game low  latency is on ,not display film mode (Pure Cinema Mode)*/
        if(i2_val == 1)
        {
            return TRUE;
        }
#endif

    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        return FALSE;
    }
    else
    {
        menu_get_crnt_isl(&t_isl_rec);

        h_svctx = menu_get_crnt_svctx();
        c_svctx_get_video_src_resolution(h_svctx, &t_timing);

        if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
            t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA &&
            t_timing.e_timing_type != VSH_SRC_TIMING_VIDEO)
        {
            return TRUE;
        }
        else
        {
            if(menu_is_signal_loss())
            {
                return FALSE;
            }
            else
            {
                #if 0   //DTV00896158
                if (a_cfg_custom_chk_freqence_24hz())
                {
                    return TRUE;
                }
                else
                #endif
                if (_is_DVI_signal())
                {
                    return FALSE;
                }
                else if(t_timing.e_timing_type == VSH_SRC_TIMING_GRAPHIC)
                {
                    return TRUE;
                }
                else
                {
                    return FALSE;
                }
            }
        }
    }
#else
    menu_get_crnt_isl(&t_isl_rec);

    h_svctx = menu_get_crnt_svctx();
    c_svctx_get_video_src_resolution(h_svctx, &t_timing);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA &&
        t_timing.e_timing_type != VSH_SRC_TIMING_VIDEO)
    {
        return TRUE;
    }
    else
    {
        if(menu_is_signal_loss())
        {
            return FALSE;
        }
        else
        {
            if(t_timing.e_timing_type == VSH_SRC_TIMING_GRAPHIC || a_cfg_custom_chk_freqence_24hz())
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }
#endif

}


static BOOL _is_adv_vid_clear_action_hide(VOID)
{
    return FALSE;
}


static BOOL _is_adv_vid_graphic_hide(VOID)
{
    HANDLE_T                    h_svctx;
    ISL_REC_T                   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};

    menu_get_crnt_isl(&t_isl_rec);

    h_svctx = menu_get_crnt_svctx();
    c_svctx_get_video_src_resolution(h_svctx, &t_timing);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA &&
       t_timing.e_timing_type != VSH_SRC_TIMING_VIDEO)
    {
        return TRUE;
    }
    else
    {
        if(menu_is_signal_loss())
        {
            return FALSE;
        }
        else
        {
            if (_is_DVI_signal())
            {
                return FALSE;
            }
            else if(t_timing.e_timing_type == VSH_SRC_TIMING_GRAPHIC)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }
}
#endif /* NEVER */


static BOOL _is_vid_lit_sns_hide(VOID)
{
    HANDLE_T                    h_svctx;
    ISL_REC_T                   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};
    CHAR        s_disp_name[SYS_NAME_LEN+1] = {0};
    INT32       i4_ret = -1;
    UINT8       ui1_input_grp = 0;
    UINT8       ui1_input = 0;
    VSH_SRC_RESOLUTION_INFO_T   t_resol;

    c_memset(&t_resol, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);

    /* Get target input source */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    if (i4_ret != APP_CFGR_OK)
    {
        return TRUE;
    }

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    if (i4_ret != APP_CFGR_OK)
    {
        return TRUE;
    }

    if( a_acfg_cust_get_video_type() != SCC_VID_PQ_SDR)
    {
        return TRUE;
    }

    /* Get input group */
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

    ui1_input_grp = acfg_custom_get_input_grp(&t_isl_rec);
    if((ui1_input_grp == ACFG_CUST_INPUT_GRP_MMP) &&
       (a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED))
    {
        return FALSE;
    }

    menu_get_crnt_isl(&t_isl_rec);

    h_svctx = menu_get_crnt_svctx();
    c_svctx_get_video_src_resolution(h_svctx, &t_timing);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA &&
        t_timing.e_timing_type != VSH_SRC_TIMING_VIDEO)
    {
        return TRUE;
    }
    else
    {
        if(menu_is_signal_loss())
        {
            return FALSE;
        }
        else
        {
            if (_is_DVI_signal())
            {
                return FALSE;
            }
            else if(t_resol.e_timing_type == VSH_SRC_TIMING_GRAPHIC)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }
}
static BOOL _is_local_dimming_hide(VOID)
{
    if (a_cfg_custom_get_lcdim_used() == FALSE)
    {
        DBG_INFO(("[MENU][%s %d ] lcdim_used = %d\n",__FUNCTION__,__LINE__,a_cfg_custom_get_lcdim_used()));
        return TRUE;
    }

    return FALSE;
}

// Spec 3.1:
// ClearAction:
// 2020 M6 support, M6X not support
// 2021 M6 not support!
static BOOL _is_motion_control_hide(VOID)
{
    CHAR   s_name[32] = {0};
    INT32  i4_ret  = 0;
    BOOL   is_hide = FALSE;

    i4_ret = a_cfg_custom_get_model_name(s_name);
    ACFG_LOG_ON_FAIL(i4_ret);

    //5583 D series and 2020 Mxx6x-h  don't support motion control item show
    if(s_name[0] == 'V' || s_name[0] == 'D')
    {
        is_hide =  TRUE;
    }
    else if( s_name[0] == 'M' ) // Mxxx
    {
        if( a_cfg_cust_Is_CurModel_2021() )
        {
            if( s_name[4] == '6' ) // 2021 M6 should hide
            {
                is_hide =  TRUE;
            }
        }
        else if( a_cfg_cust_Is_CurModel_2020() )// 2020
        { // 2020 M6 support, M6X not support
            if( c_strstr(s_name,"6x")!= NULL )
            {
                is_hide =  TRUE;
            }
        }
    }

    return is_hide;
}

static BOOL _is_ana_mts_hide(VOID)
{
    INT32           i4_ret = 0;
    ISL_REC_T       t_isl_rec;
    i4_ret = menu_get_crnt_isl(&t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);
    //2022-k remove Analog Audio from TV channels menu without a composite input
    if(!a_cfg_cust_Is_CurModel_after_2022_K() || a_nav_ipts_is_comp_source(&t_isl_rec))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

static BOOL _is_dig_mts_hide(VOID)
{
    return FALSE;
}

static BOOL _is_pic_mode_custom_enabled(VOID)
{
    ISL_REC_T   t_isl_rec;

    menu_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
    {
        return TRUE;
    }
    else
    {
        INT16   i2_val = 0;

        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                     &i2_val);

        if(i2_val == ACFG_CUST_PIC_MODE_CUSTOM)     /* CUSTOM mode */
        {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL is_3d_playing(VOID)
{
    /*if (a_tv_custom_is_3D_mode_playing())
    {
        return FALSE;
    }*/
    return TRUE;
}

static BOOL _is_item_gamma_hide(VOID)
{
    return FALSE;
}

BOOL a_menu_is_cust_pic_mode_and_locked(VOID)
{
    INT32       i4_ret = MENUR_OK;
    INT16       i2_pic_mode = 0;
    //BOOL        b_is_lock_status = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                                                &i2_pic_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    if ((i2_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM) ||
        (i2_pic_mode >(ACFG_CUST_SET_PIC_MODE_NUM_EX+ACFG_PRE_SET_PIC_MODE_NUM)))
    {
        return FALSE;
    }
    else
    {
        /*check if it is locked*/
        //a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);
        //MENU_LOG_ON_FAIL(i4_ret);
        if(a_menu_is_picture_locked())
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

static BOOL _is_cust_pic_mode_pq_enable(VOID)
{
    if(a_menu_is_cust_pic_mode_and_locked())
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

static BOOL _is_item_sharpness_enable(VOID)
{
    if (a_menu_is_cust_pic_mode_and_locked())
    {
        DBG_INFO(("[MENU][%s %d] current pic mode is locked\n",__FUNCTION__,__LINE__));
        return FALSE;
    }

    if (_is_DVI_signal())
    {
        DBG_INFO(("[MENU][%s %d] current is dvi singnal\n",__FUNCTION__,__LINE__));
        return FALSE;
    }


#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    // 2021-04-15: MVV-8350: Only RGB&&FullColor=On ==> sharpness grey out
    EnuAcfgFullColor444Status eAcfgFullColor444Status = acfg_cust_get_FullColor444_status();
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU]FullColor444{%s:%d} eAcfgFullColor444Status:%d\n",
        __FILE__, __LINE__, eAcfgFullColor444Status  )); );

    if( eAcfgFullColor444Status == ACFG_INPUT_RGB__FULL_COLOR_444_ON )
    {
        DBG_LOG_PRINT(("[MENU][Sharpness]{%s,%d} FullColor444 => UI sharpness Hide\n", __FUNCTION__,__LINE__ ));
        return FALSE;
    }

#else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
#endif

    return TRUE;
}

#ifdef NEVER

static BOOL _is_content_below_59_fps()
{
    VSH_SRC_RESOLUTION_INFO_T t_timing = {0};

    if (a_cfg_av_get_timing(SN_PRES_MAIN_DISPLAY, &t_timing) == APP_CFGR_OK &&
        (t_timing.ui4_frame_rate < 59 || (1000 <= t_timing.ui4_frame_rate && t_timing.ui4_frame_rate < 5900)))
    {
        return TRUE;
    }

    return FALSE;
}
#endif

static BOOL _is_item_progaming_engine_enable(VOID)
{
    if(a_menu_is_cust_pic_mode_and_locked())
    {
        return FALSE;
    }
    if (a_cfg_cust_is_support_progaming_engine() == TRUE)
    {
        return TRUE;
    }

    return FALSE;
}

static BOOL _is_item_game_hdr_enable(VOID)
{
    ISL_REC_T  t_isl_rec = {0};
    menu_get_crnt_isl(&t_isl_rec);

    if (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI &&
        t_isl_rec.t_avc_info.e_video_type != DEV_AVC_DVI)
    {
        return FALSE;
    }

    return TRUE;
}

static BOOL _is_item_game_low_latency_enable(VOID)
{
#if( VZO_DV__GLL_CONTROL_BY_DV_GAME )
    if( a_cfg_get_hdr_type() == SCC_VID_PQ_DOVI )
    {
        DBG_LOG_PRINT(("[MENU][DV][GAME][GLL]{%s, %d} DV => Grey out GLL \n", __FUNCTION__,__LINE__));
        return FALSE;
    }
#endif

    if( a_cfg_cust_is_support_game_low_latency() )
    {
        return TRUE;
    }

    return FALSE;
}

#ifdef APP_SUPPPORT_FRC
static BOOL _is_item_judder_reduction_enable(VOID)
{
#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    if( acfg_cust_Is_CurHDMI_PQ_PCMode() == TRUE )
    {
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
#endif

    if(a_acfg_cust_is_gll_enable() == TRUE)
    {
        return FALSE;
    }

    if(_is_VRR_enable_and_VRR_stream_detect() == TRUE)
    {
        return FALSE;
    }

    return TRUE;
}

static BOOL _is_item_motion_control_enable(VOID)
{
#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    if( acfg_cust_Is_CurHDMI_PQ_PCMode() == TRUE )
    {
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
#endif

    if(a_acfg_cust_is_gll_enable() == TRUE)
    {
        return FALSE;
    }

    if(_is_VRR_enable_and_VRR_stream_detect() == TRUE)
    {
        return FALSE;
    }

    return TRUE;
}
#endif

static BOOL _is_item_clear_action_enable(VOID)
{
#if 1
    // Only enable when it support turn on...
    // if cannot turn on, grey this item!

    // Check if can turn on
    BOOL bClearActionCanTurnOn = a_cfg_cust_ClaerAction_if_can_turn_on();
    //DBG_LOG_PRINT(("[MENU][ClearAction]{%s: %s: %d} a_cfg_cust_ClaerAction_if_can_turn_on()=> %d\n", __FILE__, __FUNCTION__,__LINE__, bClearActionCanTurnOn ));
    if( FALSE == bClearActionCanTurnOn ) // Cannot turn on
    {
        //DBG_LOG_PRINT(("[MENU][ClearAction]{%s: %s: %d} UI-ClearAction grey\n", __FILE__, __FUNCTION__,__LINE__ ));
        return FALSE; // UI-ClearAction disable!
    }

    return TRUE;

#else
    INT16  i2_val = 0;
    INT32  i4_ret  = 0;

    if ((a_cfg_cust_is_variable_refresh_rate_support() == TRUE)&&(a_cfg_cust_is_support_progaming_engine() == TRUE))
    {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i2_val);
        MENU_LOG_ON_FAIL(i4_ret);

        if(i2_val == ACFG_CUST_COMMON_ON)
        {
            return FALSE;
        }
    }

    if(_is_VRR_enable_and_VRR_stream_detect() == TRUE || a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE)
    {
        return FALSE;
    }

    return  TRUE;
#endif
}

static BOOL _is_item_gamma_enable(VOID)
{
    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        if(MMP_BE_BROWSER_MEDIA_TYPE_VIDEO != a_mmp_be_get_media_type())
        {
            return FALSE;
        }
        else return TRUE;
    }

    else if (a_menu_is_cust_pic_mode_and_locked())
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

BOOL a_menu_is_color_tuner_enable(VOID)
{
    MMP_BE_BROWSER_STATUS_T e_mmp_browser_status = MMP_BE_BROWSER_STATUS_NONE;
    ISL_REC_T       t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_resol;

    if(a_menu_is_cust_pic_mode_and_locked())
    {
        return FALSE;
    }
    else
    {
    #ifdef APP_MENU_MMP_COEXIST
        if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
        {
            e_mmp_browser_status = a_mmp_be_get_browser_status();

            if(e_mmp_browser_status == MMP_BE_BROWSER_STATUS_PHOTO)
            {
                 return FALSE;
            }
            else
            {
                return TRUE;
            }
        }
    #endif

        c_memset (&t_isl_rec, 0, sizeof(ISL_REC_T));
        c_memset (&t_resol, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T));

        c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);
        menu_get_crnt_isl(&t_isl_rec);
        if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
           t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
        {
            return FALSE;
        }

        else if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
            t_resol.e_timing_type == VSH_SRC_TIMING_GRAPHIC)
        {
            return FALSE;
        }
#ifdef NEVER
        else if(_is_hdmi_sdr_hdr_444_content() == TRUE)
        {
            return FALSE;
        }
#endif /* NEVER */
        else
        {
            return TRUE;
        }

    }
}

 BOOL a_is_color_tuner_enable(VOID)
{
    return a_menu_is_color_tuner_enable();
}

static BOOL _is_vid_more_sz_pos_enabled(VOID)
{
    BOOL        b_found = FALSE;
    ISL_REC_T   t_isl_rec;
    SVL_REC_T   t_svl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_resol;

    c_memset (&t_isl_rec, 0, sizeof(ISL_REC_T));
    c_memset (&t_resol, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T));

    c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);
    menu_get_crnt_isl(&t_isl_rec);

    if ((t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
        &&(_get_parental_ctrl_enable_idx() == TRUE)
        &&(t_resol.ui4_height == 0)
        &&(t_resol.ui4_width== 0))
    {
        return FALSE;
    }

    if (a_tv_custom_is_3D_mode_playing())
    {
        return FALSE;
    }
    #ifdef APP_MENU_MMP_COEXIST
    else if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        return FALSE;
    }
    #endif
    else
    {
        /* 1080P 120Hz not supported */
        CHECK_1080P_120HZ_SUPPORT();

        if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status())
        {
            /* In 3rd full screen status, disable the function */
            return FALSE;
        }

        /* If the source is not VGA then disable the Size & Plsition item */
        else if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
                t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA &&
                t_resol.e_timing_type != VSH_SRC_TIMING_VIDEO)
        {
            if(menu_is_signal_loss())
            {
                return FALSE;
            }

            if(menu_is_video_block())
            {
                return FALSE;
            }

            return TRUE;
        }

        else
        {
            menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
            if (t_isl_rec.e_src_type == INP_SRC_TYPE_TV
                && b_found && t_svl_rec.uheader.t_rec_hdr.e_brdcst_type != BRDCST_TYPE_ANALOG)
            {
                /* DTV */
                if (!(_is_h_pos_enabled() || _is_v_pos_enabled()))
                {
                    return FALSE;
                }
            }

            return (menu_is_signal_loss() || _is_hv_pos_hidden() ? FALSE : TRUE);
        }
    }
}


static BOOL _is_full_chroma_visibility(VOID)
{
    /*   The Full Color 4:4:4 setting (previously known and Full Chroma 4:4:4)
    only applies to 2019 skus. Under picture,
    Full Color 4:4:4 with ON/Off settings does NOT apply to D43-F1, D50-F1, and D65-F1 that are 2018 skus. */
    /* get model name */
    CHAR s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};

    a_cfg_custom_get_model_name(s_model_name);

    if ((c_strchr( s_model_name, 'G' )) != NULL)
    {
        return TRUE;
    }
    return FALSE;
}




static BOOL _is_hdmi_sdr_hdr_444_content(VOID)
{
    ISL_REC_T                   t_isl_rec;
    BOOL                        is_444 = FALSE;
    c_memset (&t_isl_rec, 0, sizeof(ISL_REC_T));
    menu_get_crnt_isl(&t_isl_rec);

    do
    {
        if (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI &&
            t_isl_rec.t_avc_info.e_video_type != DEV_AVC_DVI)
        {
            is_444 = FALSE;
            break;
        }

        if( menu_is_signal_loss() == TRUE || menu_is_video_block() == TRUE )
        {
            is_444 = FALSE;
            break;
        }

        if (a_acfg_cust_get_dynamic_range () == ACFG_CUST_CONTENT_DV)
        {
            is_444 = FALSE;
            break;
        }

        if(a_cfg_cust_video_is_sdr_hdr_444_content())
        {
            is_444 = TRUE;
            if(b_last_444_content_status != is_444)
            {
                DBG_LOG_PRINT(("[menu] b_last_444_content_status change from %d, to %d, %s,%d\r\n",b_last_444_content_status,is_444,__FUNCTION__,__LINE__));
                b_last_444_content_status = is_444;
            }
            break;
        }
        else
        {
            b_last_444_content_status = FALSE;
        }

        if (menu_inp_is_full_color_444_on())
        {
            is_444 = TRUE;
            if(b_last_444_on_status != is_444)
            {
                DBG_LOG_PRINT(("[menu] b_last_444_content_status change from %d, to %d, %s,%d\r\n",b_last_444_on_status,is_444,__FUNCTION__,__LINE__));
                b_last_444_on_status = is_444;
            }
            break;
        }
        else
        {
            b_last_444_on_status = FALSE;
        }

    }while(0);

    return is_444;
}

static BOOL _is_hdmi_sdr_hdr_rgb_content(VOID)
{
    ISL_REC_T                   t_isl_rec;
    BOOL                        is_rgb = FALSE;
    c_memset (&t_isl_rec, 0, sizeof(ISL_REC_T));
    menu_get_crnt_isl(&t_isl_rec);

    do
    {
        if (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI &&
            t_isl_rec.t_avc_info.e_video_type != DEV_AVC_DVI)
        {
            is_rgb = FALSE;
            break;
        }

        if( menu_is_signal_loss() == TRUE || menu_is_video_block() == TRUE )
        {
            is_rgb = FALSE;
            break;
        }

        if (a_acfg_cust_get_dynamic_range () == ACFG_CUST_CONTENT_DV)
        {
            is_rgb = FALSE;
            break;
        }

        if(a_cfg_cust_video_is_sdr_hdr_444_content())
        {
            is_rgb = TRUE;
            break;
        }

    }while(0);

    return is_rgb;
}

static BOOL _is_hdmi_mode_enable(VOID)
{
    ISL_REC_T   t_isl_rec;
    MENU_LOG_ON_FAIL(menu_get_crnt_isl(&t_isl_rec));
    return menu_full_color_is_enable(t_isl_rec.ui1_internal_id);
}

static BOOL _is_hdmi_mode_hidden(VOID)
{
    BOOL b_visible = FALSE;
    ISL_REC_T   t_isl_rec;

    MENU_LOG_ON_FAIL(menu_get_crnt_isl(&t_isl_rec));

    if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)     /* HDMI */
    {
        b_visible = menu_full_color_is_enable(t_isl_rec.ui1_internal_id);
    }

    return !b_visible;

}

static BOOL _is_full_color_444_hidden(VOID)
{
    ISL_REC_T t_isl_rec;
    menu_get_crnt_isl(&t_isl_rec);

    return t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI;
}

static BOOL _is_full_color_444_enable(VOID)
{
#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)

    BOOL bIs_FullColor444_CanTurnOn = acfg_cust_FullColor444_IfCanTurnOn();

    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d} rtn => %d\n", __FUNCTION__, __LINE__, bIs_FullColor444_CanTurnOn)); );

    return bIs_FullColor444_CanTurnOn;

#else
    MENU_HDMI_IF_CLR_SPC e_color_space = MENU_HDMI_IF_CLRSPC_UNKNOW;
    INT32  i4_ret = MENUR_OK;
    INT32  i4_color = 0;
    ISL_REC_T  t_isl_rec;

    c_memset (&t_isl_rec, 0, sizeof(ISL_REC_T));
    menu_get_crnt_isl(&t_isl_rec);

    if (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI &&
        t_isl_rec.t_avc_info.e_video_type != DEV_AVC_DVI)
    {
        return FALSE;
    }

    if( menu_is_signal_loss() == TRUE || menu_is_video_block() == TRUE )
    {
       return FALSE;
    }
    if (a_icl_custom_get_dolby_vision_status() == 1)
    {
        return FALSE;
    }
    if (a_cfg_get_hdr_type() != SCC_VID_PQ_SDR)
    {
        return FALSE;
    }
    i4_ret = menu_ope_lst_get_hdmi_color_space(&i4_color);

    if (i4_ret != MENUR_OK)
    {
       return FALSE;
    }
    DBG_LOG_PRINT((" hdmi_color_space : %d, %s,%d\r\n",i4_color,__FUNCTION__,__LINE__));

    e_color_space = (MENU_HDMI_IF_CLR_SPC)i4_color;
    if(menu_ope_lst_hdmi_color_space_is_444(e_color_space) == FALSE )
    {
        return FALSE;
    }
    return  TRUE;
#endif
}

static BOOL _is_full_color_enable(UINT8 ui1_hdmi_port)
{
    BOOL  b_support = FALSE;
    INT32 i4_ret = MENUR_OK;
    i4_ret = menu_ope_lst_get_hdmi2_0_is_support(ui1_hdmi_port,&b_support);
    if (i4_ret != MENUR_OK)
    {
       return FALSE;
    }

    if( b_support == FALSE)
    {
       return FALSE;
    }

    return  TRUE;
}

static BOOL _is_vid_more_sz_enabled(VOID)
{
    BOOL        b_enable = TRUE;
    ISL_REC_T   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_resol;

    c_memset (&t_isl_rec, 0, sizeof(ISL_REC_T));
    c_memset (&t_resol, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T));

    c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);
    menu_get_crnt_isl(&t_isl_rec);

    do {
        if ((INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
            &&(_get_parental_ctrl_enable_idx() == TRUE)
            &&(0 == t_resol.ui4_height)
            &&(0 == t_resol.ui4_width))
        {
            b_enable = FALSE;
            break;
        }

        if (a_tv_custom_is_3D_mode_playing())
        {
            b_enable = FALSE;
            break;
        }
        #ifdef APP_MENU_MMP_COEXIST
        else if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
        {
            b_enable = FALSE;
            break;
        }
        #endif
        else if(t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI
                &&(t_resol.ui4_width == 3840)
                &&(t_resol.ui4_height == 2160))
        {
            b_enable = FALSE;
            break;
        }
        else
        {
            /* 1080P 120Hz not supported */
            CHECK_1080P_120HZ_SUPPORT();

            if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status())
            {
                /* In 3rd full screen status, disable the function */
                b_enable = FALSE;
                break;
            }

            /* If the source is not VGA then disable the Size & Plsition item */
            else if(INP_SRC_TYPE_AV == t_isl_rec.e_src_type &&
                    DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type &&
                    t_resol.e_timing_type != VSH_SRC_TIMING_VIDEO)
            {
                if(menu_is_signal_loss())
                {
                    b_enable = FALSE;
                    break;
                }

                if(menu_is_video_block())
                {
                    b_enable = FALSE;
                    break;
                }
            }
            else
            {
                b_enable = (menu_is_signal_loss()) ? FALSE : TRUE;
                break;
            }

        }
    }while (0);

    return b_enable;
}

static BOOL _is_vid_more_pos_enabled(VOID)
{
    BOOL        b_enable = TRUE;
    ISL_REC_T   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_resol;
    MENU_HDMI_IF_CLR_SPC e_color_space = MENU_HDMI_IF_CLRSPC_UNKNOW;
    INT32  i4_ret = MENUR_OK;
    INT32  i4_color = 0;

    c_memset (&t_isl_rec, 0, sizeof(ISL_REC_T));
    c_memset (&t_resol, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T));

    c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);
    menu_get_crnt_isl(&t_isl_rec);

    i4_ret = menu_ope_lst_get_hdmi_color_space(&i4_color);
    DBG_LOG_PRINT((" hdmi_color_space : %d, %s,%d\r\n",i4_color,__FUNCTION__,__LINE__));

    e_color_space = (MENU_HDMI_IF_CLR_SPC)i4_color;
    do {
        if ((t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
            &&(_get_parental_ctrl_enable_idx() == TRUE)
            &&(0 == t_resol.ui4_height)
            &&(0 == t_resol.ui4_width))
        {
            b_enable = FALSE;
            DBG_INFO(("[MENU][%s %d] ui4_width(0)or ui4_height() is 0,not support\n",__FUNCTION__,__LINE__));
            break;
        }

        if (a_tv_custom_is_3D_mode_playing())
        {
            b_enable = FALSE;
            DBG_INFO(("[MENU][%s %d] a_tv_custom_is_3D_mode_playing,not support\n",__FUNCTION__,__LINE__));
            break;
        }
        #ifdef APP_MENU_MMP_COEXIST
        else if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
        {
            b_enable = FALSE;
            DBG_INFO(("[MENU][%s %d] MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC,not support\n",__FUNCTION__,__LINE__));
            break;
        }
        #endif
        else if(t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI
                &&(t_resol.ui4_width == 3840)
                &&(t_resol.ui4_height == 2160))
        {
            b_enable = FALSE;
            i4_ret = acfg_cust_video_pos_reset(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V));
            ACFG_LOG_ON_FAIL(i4_ret);
            i4_ret = acfg_cust_video_pos_reset(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H));
            ACFG_LOG_ON_FAIL(i4_ret);
            DBG_INFO(("[MENU][%s %d] ui4_width(3840)or ui4_height(2160),not support and will reset position\n",__FUNCTION__,__LINE__));
            break;
        }
        else if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI
            && menu_ope_lst_hdmi_color_space_is_444(e_color_space)
            && menu_inp_is_full_color_444_on())
        {
            b_enable = FALSE;
            DBG_INFO(("[MENU][%s %d] full color 444 is on,not support\n",__FUNCTION__,__LINE__));
            break;
        }
        else
        {
            /* 1080P 120Hz not supported */
            CHECK_1080P_120HZ_SUPPORT();

            if(APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status())
            {
                /* In 3rd full screen status, disable the function */
                b_enable = FALSE;
                DBG_INFO(("[MENU][%s %d] APP_TV_NET_SVC_STATUS_RESUMED,not support\n",__FUNCTION__,__LINE__));
                break;
            }

            /* If the source is not VGA then disable the Size & Plsition item */
            else if(INP_SRC_TYPE_AV == t_isl_rec.e_src_type &&
                    DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type &&
                    t_resol.e_timing_type != VSH_SRC_TIMING_VIDEO)
            {
                if(menu_is_signal_loss())
                {
                    b_enable = FALSE;
                    DBG_INFO(("[MENU][%s %d] menu_is_signal_loss,not support\n",__FUNCTION__,__LINE__));
                    break;
                }

                if(menu_is_video_block())
                {
                    b_enable = FALSE;
                    DBG_INFO(("[MENU][%s %d] menu_is_video_block,not support\n",__FUNCTION__,__LINE__));
                    break;
                }

            }
            else
            {
                if (menu_is_signal_loss())
                {
                    b_enable = FALSE;
                    DBG_INFO(("[MENU][%s %d] menu_is_signal_loss,not support\n",__FUNCTION__,__LINE__));
                    break;
                }

            }
        }

        b_enable = TRUE;
    } while (0);

    return b_enable;
}

static BOOL _is_pic_mode_back_light_enable(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 &i2_val);

    if(i2_val == ACFG_CUST_PIC_MODE_CUSTOM)     /* CUSTOM mode */
    {
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT), &i2_val);

        if(i2_val == 0)   /* OFF */
        {
            return TRUE;
        }
    }

    return FALSE;
}

#ifdef NEVER

static BOOL _is_sat_hue_shp_hidden(VOID)
{
    ISL_REC_T   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_resol;

    c_memset(&t_resol, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    menu_get_crnt_isl(&t_isl_rec);
    c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA &&
       t_resol.e_timing_type != VSH_SRC_TIMING_VIDEO
      )
    {
        return TRUE;
    }
    else
    {
        if(menu_is_signal_loss())
        {
            return FALSE;
        }
        else
        {
            if (_is_DVI_signal())
            {
                return FALSE;
            }
            else if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
                     t_resol.e_timing_type == VSH_SRC_TIMING_GRAPHIC)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }
}
#endif

/*******************************************
* Description:
* Task: make menu OAS co-exist with Network APs
*
*
*******************************************/
BOOL _is_ch_scan_enabled(VOID)
{
    APP_TV_NET_SVC_STATUS t_svc_state;

    t_svc_state = a_tv_net_get_tv_svc_status();

    if(APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

#ifdef APP_MENU_MMP_COEXIST
static BOOL _is_guide_setup_enabled(VOID)
{
    return TRUE;
}
#endif

static BOOL _is_device_setup_enabled(VOID)
{
    UINT8   ui1_status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;

    a_cfg_custom_get_wifi_remote_pair_status(&ui1_status);

    if(WIFI_REMOTE_PAIR_STATUS_PAIRED == ui1_status)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#ifdef APP_MENU_OP_VCHIP_ENABLE
static BOOL _is_op_vchip_drrt_hide(VOID)
{
    if (menu_atsc_op_vchip_drrt_is_active())
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

static BOOL _is_op_vchip_hide(VOID)
{
    if (_is_op_vchip_drrt_hide() == FALSE)
    {
        return TRUE;
    }

    if (menu_atsc_op_vchip_is_active())
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
#endif

BOOL menu_picture_size_is_enable(VOID)
{
    return _is_vid_more_sz_enabled();
}

BOOL menu_picture_position_is_enable(VOID)
{
    return _is_vid_more_pos_enabled();
}

BOOL menu_vga_auto_is_enable(VOID)
{
    return _is_vga_connected();
}

BOOL menu_full_chroma_is_visibility(VOID)
{
     return _is_full_chroma_visibility();
}
BOOL menu_full_color_444_is_enable(VOID)
{
    return _is_full_color_444_enable();
}
BOOL menu_full_color_is_enable(UINT8 ui1_hdmi_port)
{
    return _is_full_color_enable(ui1_hdmi_port);
}

static BOOL _is_hdr_content(VOID)
{
    if (a_acfg_cust_get_dynamic_range () != ACFG_CUST_CONTENT_SDR)
    {
        return TRUE;
    }

    return FALSE;
}

static BOOL _is_sdr_content(VOID)
{
    if(_is_hdr_content())
    {
        return FALSE;
    }
    return TRUE;
}

static BOOL _is_vid_backlight_enabled(VOID)
{
    INT16 i2_val = 0;

    if(a_menu_is_cust_pic_mode_and_locked())
    {
        DBG_INFO(("[MENU][%s %d] pic locked\n",__FUNCTION__,__LINE__));
        return FALSE;
    }

    if(a_cfg_cust_drv_is_lightsensor_support() == FALSE)
    {
        return TRUE;
    }

    if (_is_vid_lit_sns_hide() == TRUE)
    {
        return TRUE;
    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR),&i2_val);

    if(0 != i2_val)
    {
        DBG_INFO(("[MENU][%s %d] APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR is %d\n",__FUNCTION__,__LINE__,i2_val));
        return FALSE;
    }

    return TRUE;
}

#ifdef APP_MENU_MMP_COEXIST
static BOOL _is_pic_item_enabled(VOID)
{
    if(a_menu_is_cust_pic_mode_and_locked())
    {
        return FALSE;
    }

    return TRUE;
}
#endif

static BOOL _is_item_contrast_enable(VOID)
{
    if (a_menu_is_cust_pic_mode_and_locked())
    {
        return FALSE;
    }

#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    // 2021-04-15: MVV-8350: contrast should not grey out for FullColor444=On
    /*if( acfg_cust_Is_CurHDMI_PQ_PCMode() == TRUE )
    {
        return FALSE;
    }*/
#else
    if(_is_hdmi_sdr_hdr_rgb_content() == TRUE)
    {
        return FALSE;
    }
#endif

    return TRUE;
}

static BOOL _is_item_color_enable(VOID)
{
    if (a_menu_is_cust_pic_mode_and_locked())
    {
        return FALSE;
    }

#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    // 2021-04-15: MVV-8350: Only RGB&&FullColor=On ==> Color grey out
    EnuAcfgFullColor444Status eAcfgFullColor444Status = acfg_cust_get_FullColor444_status();
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU]FullColor444{%s:%d} eAcfgFullColor444Status:%d\n",
        __FILE__, __LINE__, eAcfgFullColor444Status  )); );

    if( eAcfgFullColor444Status == ACFG_INPUT_RGB__FULL_COLOR_444_ON )
    {
        DBG_LOG_PRINT(("[MENU][Color]{%s,%d} FullColor444 => UI Color Hide\n", __FUNCTION__,__LINE__ ));
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_rgb_content() == TRUE)
    {
        return FALSE;
    }
#endif

    return TRUE;
}

static BOOL _is_item_tint_enable(VOID)
{
    if (a_menu_is_cust_pic_mode_and_locked())
    {
        DBG_LOG_PRINT(("[MENU][TINT] {%s,%d} cust_pic_mode_and_locked => UI Tint Hide\n", __FUNCTION__,__LINE__ ));
        return FALSE;
    }

#if (ENABLE_COLOR_444_TO_422_NEW_SPEC)
    // 2021-04-15: MVV-8350: Only RGB&&FullColor=On ==> Tint grey out
    EnuAcfgFullColor444Status eAcfgFullColor444Status = acfg_cust_get_FullColor444_status();
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU]FullColor444{%s:%d} eAcfgFullColor444Status:%d\n",
        __FILE__, __LINE__, eAcfgFullColor444Status  )); );

    if( eAcfgFullColor444Status == ACFG_INPUT_RGB__FULL_COLOR_444_ON )
    {
        DBG_LOG_PRINT(("[MENU][TINT]{%s,%d} FullColor444 => UI Tint Hide\n", __FUNCTION__,__LINE__ ));
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_rgb_content() == TRUE)
    {
        return FALSE;
    }
#endif

    return TRUE;
}

static BOOL _is_adv_vid_local_dimming_enable(VOID)
{
    //for backlight control ,it need gray out when HDR
    if( FALSE == a_cfg_cust_get_support_local_dimming() ) // Backlight_ctrl
    {
        if( FALSE == a_cfg_cust_BacklightCtrl_CheckIfCanTurnOn() )
        {
            return FALSE;
        }
    }

#if 0
    if(_is_VRR_enable_and_VRR_stream_detect() == TRUE)
    {
        return FALSE;
    }
#endif

#ifdef APP_MENU_MMP_COEXIST
    return _is_pic_item_enabled();
#endif
    return TRUE;
}

#ifdef NEVER
static BOOL _is_adv_vid_alc_enable(VOID)
{
    if (_is_DVI_signal()) {
        return FALSE;
    }

    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }

#ifdef APP_MENU_MMP_COEXIST
    return _is_pic_item_enabled();
#endif

    return TRUE;
}
#endif /* NEVER */

// Black detail
static BOOL _is_contrast_en_enable(VOID)
{
#if 1
    // Use ACFG status
    if( a_cfg_cust_contrast_en_CheckIfCanTurnOn() == FALSE )
    {
        DBG_LOG_PRINT(("[MENU][Black_Detail]{%s,%d} => UI Black_Detail Hide\n", __FUNCTION__,__LINE__ ));
        return FALSE;
    }

#else

#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    // 2021-04-15: MVV-8350: Only RGB&&FullColor=On ==> Black_Detail grey out
    EnuAcfgFullColor444Status eAcfgFullColor444Status = acfg_cust_get_FullColor444_status();
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU]FullColor444{%s:%d} eAcfgFullColor444Status:%d\n",
        __FILE__, __LINE__, eAcfgFullColor444Status  )); );
    if( eAcfgFullColor444Status == ACFG_INPUT_RGB__FULL_COLOR_444_ON )
    {
        DBG_LOG_PRINT(("[MENU][Black_Detail]{%s,%d} FullColor444 => UI Black_Detail Hide\n", __FUNCTION__,__LINE__ ));
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
#endif

    if(a_acfg_cust_is_gll_enable() == TRUE)
    {
        DBG_LOG_PRINT(("[MENU][Black_Detail]{%s,%d} GLL => UI Black_Detail Hide\n", __FUNCTION__,__LINE__ ));
        return FALSE;
    }

    if(_is_VRR_enable_and_VRR_stream_detect() == TRUE)
    {
        DBG_LOG_PRINT(("[MENU][Black_Detail]{%s,%d} VRR => UI Black_Detail Hide\n", __FUNCTION__,__LINE__ ));
        return FALSE;
    }
#endif

    return TRUE;
}

static BOOL _is_supper_resolution_enable(VOID)
{
#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    // 2021-04-15: MVV-8350: Only RGB&&FullColor=On ==> Super_Resolution grey out
    EnuAcfgFullColor444Status eAcfgFullColor444Status = acfg_cust_get_FullColor444_status();
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU]FullColor444{%s:%d} eAcfgFullColor444Status:%d\n",
        __FILE__, __LINE__, eAcfgFullColor444Status  )); );
    if( eAcfgFullColor444Status == ACFG_INPUT_RGB__FULL_COLOR_444_ON )
    {
        DBG_LOG_PRINT(("[MENU][Super_Resolution]{%s,%d} FullColor444 => UI Super_Resolution Hide\n", __FUNCTION__,__LINE__ ));
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
#endif

    if (a_cfg_cust_drv_get_4k_source())
    {
        DBG_LOG_PRINT(("[MENU][Super_Resolution]{%s,%d} 4K => UI Super_Resolution Hide\n", __FUNCTION__,__LINE__ ));
        return FALSE;
    }

    return TRUE;
}

static BOOL _is_edge_enhancement_enable(VOID)
{
#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    // 2021-04-15: MVV-8350: Only RGB&&FullColor=On ==> edge_enhancement grey out
    EnuAcfgFullColor444Status eAcfgFullColor444Status = acfg_cust_get_FullColor444_status();
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU]FullColor444{%s:%d} eAcfgFullColor444Status:%d\n",
        __FILE__, __LINE__, eAcfgFullColor444Status  )); );
    if( eAcfgFullColor444Status == ACFG_INPUT_RGB__FULL_COLOR_444_ON )
    {
        DBG_LOG_PRINT(("[MENU][edge_enhancement]{%s,%d} FullColor444 => UI edge_enhancement Hide\n", __FUNCTION__,__LINE__ ));
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
#endif

    return TRUE;
}

static BOOL _is_local_contrast_enable(VOID)
{
#if 1
    if( FALSE == a_cfg_cust_local_contrast_CheckIfCanTurnOn() )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LOCAL_CONTRAST,
            DBG_LOG_PRINT(("[MENU][LocalContrast]{%s: %d} LocalContrast cannot turn on! ==> Menu disable\n", __FUNCTION__,__LINE__ ));
        );
        return FALSE;
    }
#else
    if (a_acfg_cust_get_dynamic_range () == ACFG_CUST_CONTENT_DV)
    {
        return FALSE;
    }

#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    if( acfg_cust_Is_CurHDMI_PQ_PCMode() == TRUE )
    {
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
#endif

    if(a_acfg_cust_is_gll_enable() == TRUE)
    {
        return FALSE;
    }

    if(_is_VRR_enable_and_VRR_stream_detect() == TRUE)
    {
        return FALSE;
    }
#endif

    return TRUE;
}

static BOOL _is_auto_sb_soundbarsettings_hidden(VOID)
{
#if 0
    return TRUE;
#else
    return (!amp_vndr_info.items_enable.soundbarsettings);
#endif
}

static BOOL _nav_cec_sac_is_sb_ready(VOID)
{
    if((amp_vndr_info.sb_is_ready == TRUE) && (amp_vndr_info.items_enable.soundbarsettings == TRUE))
    return TRUE;
    else
    return FALSE;
}

static BOOL _is_auto_hidden_when_tv_audio_setting_show(VOID)
{
    if(_nav_cec_sac_is_sb_ready() == TRUE)
    return TRUE;
    else
    return FALSE;
}

static BOOL _nav_cec_sac_sb_setting_title_hidden(VOID)
{
    if(_is_auto_sb_soundbarsettings_hidden() == TRUE)
    return TRUE;
    else
    return FALSE;
}

static BOOL _nav_cec_sac_sb_setting_show_title(VOID)
{
    return FALSE;
}


static BOOL _is_equalizerdia_enhancer_enable(VOID)
{
    if(_is_auto_hidden_when_tv_audio_setting_show() == TRUE)
    return FALSE;
    else
    return TRUE;
}

static BOOL _is_dia_enhancer_hidden(VOID)
{
    return FALSE;
}

static BOOL _is_equalizer_enable(VOID)
{
    if(_is_auto_hidden_when_tv_audio_setting_show() == TRUE)
    return FALSE;
    else
    return TRUE;
}

static BOOL _is_equalizer_hidden(VOID)
{
    //remove equalizer for MVP-3687 SPEC
    return TRUE;//acfg_cust_audio_is_surround_mode_enable();
}

extern BOOL is_audio_custom_mode_created(VOID);
static BOOL _is_del_aud_mode_enabled(VOID)
{
    if(_is_auto_hidden_when_tv_audio_setting_show() == TRUE)
    return FALSE;
    else
    return TRUE;
}

static BOOL _is_del_aud_mode_hidden(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), &i2_val);

    if (i2_val == 5)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

static BOOL _is_audio_mode_setup_enabled(VOID)
{
    UINT8   ui1_status = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;

    a_cfg_custom_get_wifi_remote_pair_status(&ui1_status);

    /* if the wifi remote have not paired, should let this item disable*/
    if (WIFI_REMOTE_PAIR_STATUS_PAIRED == ui1_status)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#ifdef APP_SB_ENABLE
static BOOL _is_auto_vol_ctrl_enable(VOID)
{
    if(_is_auto_hidden_when_tv_audio_setting_show() == TRUE)
    return FALSE;
    else
    return TRUE;
}

static BOOL _is_auto_vol_ctrl_hidden(VOID)
{
    if (a_cfg_custom_get_wifi_remote_support())
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
#endif

static BOOL _is_analog_audio_out_hidden(VOID)
{
    BOOL    b_hide = FALSE;
    UINT8   ui1_aud_out_type = AUDIO_OUTPUT_TYPE_LINE_OUT;

    a_cfg_custom_plf_opt_is_analog_aud_out_support(&ui1_aud_out_type);

    switch (ui1_aud_out_type)
    {
        case AUDIO_OUTPUT_TYPE_HEADPHONE:
        {
            b_hide = FALSE;
            break;
        }

        case AUDIO_OUTPUT_TYPE_LINE_OUT:
        case AUDIO_OUTPUT_TYPE_BOTH:
        default:
        {
            b_hide = FALSE;
            break;
        }
    }

    DBG_INFO(("_is_analog_audio_out_hidden() b_hide = %d\n", b_hide));
    return b_hide;
}

static VOID _reset_wizard_mode(VOID)
{
#ifdef APP_C4TV_SUPPORT
    DBG_INFO (("<MENU> %s, a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_START_OOBE \n\r", __FUNCTION__));
    a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));
#else
    a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT);
#endif

    _clean_svl_and_tsl();
    a_amb_resume_app (WZD_NAME);
    a_amb_clean_stack();
    a_cfg_store();
}

static VOID _reset_picture_page(VOID)
{
     a_cfg_custom_reset_pic_settings();
}

static VOID _reset_pic_mode_page(VOID)
{
     a_cfg_custom_reset_pic_settings();
}

#ifdef ENABLE_MENU_DLNA_SETTINGS
#ifdef APP_NETWORK_SUPPORT
static BOOL _is_nw_connection_enable(VOID)
{
    BOOL b_enable = FALSE;

    a_cfg_get_network_enable(&b_enable);

    return b_enable;
}
#endif
#endif

#ifdef APP_PIP_POP_CTRL
static VOID _pip_swap(VOID)
{
    a_pop_request_swap();
}
#endif

static VOID _start_setup_wizard(VOID)
{
    menu_hide_help_tip();

    a_tv_stop_all_svc(t_g_menu_common.h_svctx, t_g_menu_common.h_svctx_sub);
    a_amb_pause_app(MENU_NAME);

    a_cfg_set_blue_mute(FALSE);
    a_cfg_custom_reset_channel_lock();
    a_sleep_timer_stop();
    menu_custom_chg_lang();

    a_cfg_store();

    _clean_svl_and_tsl();

    menu_pm_repaint();

#ifdef APP_C4TV_SUPPORT
    DBG_INFO (("<MENU> %s, a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_START_OOBE \n\r", __FUNCTION__));
    a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));
#else
    a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT);
#endif

    a_amb_resume_app (WZD_NAME);
}

static VOID _go_setup_wizard_pwd(VOID)
{
    menu_nav_go(ui4_g_menu_page_setup_wizard_pwd, NULL);
}

static VOID _go_to_dev_setup_audio_mode_setup(VOID)
{
    UINT32              ui4_page_id = 0;
    menu_device_page_add_new_device_enter_from_set(ADD_NEW_DEVICE_PAGE_ENTERN_FROM_AUDIO_MODE_SETUP);
    ui4_page_id = menu_device_get_pageid(MENU_DEVICE_PAGE_ADD_NEW_DEVICE);
    menu_nav_go(ui4_page_id, NULL);
}
#if SUPPORT_MENU_CODE
static VOID _action_support_code(VOID)
{
    a_nav_ipts_select_virtual_input("SMARTCAST");
    rest_event_notify("app/current", 2, "12");
    DBG_LOG_PRINT(("[MENU] _action_support_code.\r\n"));
    menu_leave(FALSE,0);
}
#endif
static VOID _reset_audio_page(VOID)
{
    a_cfg_custom_reset_audio();

}

extern VOID menu_delete_audio_mode(VOID);
static VOID _delete_audio_mode(VOID)
{
    menu_delete_audio_mode();
    menu_page_tree_set_offset(ui4_page_aud, 0);
    menu_pm_refresh();
    menu_pm_repaint();
}

static VOID _reset_channel_lock_page(VOID)
{
    a_cfg_custom_reset_channel_lock();

}

static BOOL _is_adv_vid_graphic_hidden(VOID)
{
    ISL_REC_T                   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_resol;

    c_memset(&t_resol, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);
    menu_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA &&
       t_resol.e_timing_type != VSH_SRC_TIMING_VIDEO
      )
    {
        return TRUE;
    }
    else
    {
        if(menu_is_signal_loss())
        {
            return FALSE;
        }
        else
        {
            if(t_resol.e_timing_type == VSH_SRC_TIMING_GRAPHIC)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }
}


static BOOL _is_network_enabled(VOID)
{
    return TRUE;
}

#ifdef NEVER
static BOOL _get_3d_setting_mode(VOID)
{
    BOOL        b_3D_support = FALSE;
    INT32       i4_ret = MENUR_OK;

#ifdef APP_CUST_PLT_OPT
    i4_ret = a_cfg_custom_plf_opt_get_3d_support(&b_3D_support);
    DBG_INFO(("\n------get 3D support , ret:%d , support: %d\n", i4_ret, b_3D_support? 1:0));
#else
    if (a_app_cust_plt_opt())
    {
        i4_ret = a_cfg_custom_plf_opt_get_3d_support(&b_3D_support);
        DBG_INFO(("\n------get 3D support , ret:%d , support: %d\n", i4_ret, b_3D_support? 1:0));
    }
#endif

    return b_3D_support;
}
#endif

static BOOL _is_acr_hidden(VOID)
{
//#ifdef TVIS_SUPPORT
    ACFG_COUNTRY_CODE_T t_country_code = ACFG_COUNTRY_CODE_US;

    a_cfg_custom_get_country_code(&t_country_code);
    if (ACFG_COUNTRY_CODE_US != t_country_code)
    {
        return TRUE;
    }

    return !(a_tv_custom_get_tos() && a_tv_custom_get_privacy());;
//#else
//    return TRUE;
//#endif
}

static BOOL _is_dynamic_content_hidden(VOID)
{
    if (0 == (access("/data/showAdReplacement", 0)))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

#ifdef NEVER
static BOOL _vid_more_adv_wide_hidden(VOID)
{
    return TRUE;
}

static BOOL _vid_more_adv_wide_enable(VOID)
{
    BOOL    b_enable = TRUE;
#ifdef  APP_MENU_MMP_COEXIST
    if (a_tv_custom_is_3D_mode_playing())
    {
        return FALSE;
    }

    a_cfg_custom_get_wide_mode_enable_change(&b_enable);

    return b_enable;
#else
    return TRUE;
#endif

}


static BOOL _is_view_mode_enable(VOID)
{
    BOOL    b_enable = TRUE;

#ifdef  APP_MENU_MMP_COEXIST

    a_cfg_custom_get_wide_mode_enable_change(&b_enable);

    return b_enable;
#else
    return TRUE;
#endif

}

static BOOL _vid_more_adv_3d_hidden(VOID)
{
#ifdef  APP_MENU_MMP_COEXIST
    if(_get_3d_setting_mode())
    {
        if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
        {
            if ((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status())
            ||(MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING == a_mmp_be_get_browser_status())
            ||(MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status())
            ||(MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status()))
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
    else
    {
        return TRUE;
    }
#else
    return !_get_3d_setting_mode();
#endif

}


static BOOL _vid_more_adv_3d_enable(VOID)
{
    if(_get_3d_setting_mode())
    {
        return a_menu_3d_setting_is_able_to_enable();
    }

    else
    {
        return FALSE;
    }
}
#endif

static BOOL _is_film_mode_enabled(VOID)
{
#if 1 // Use ACFG api to check
    if( FALSE == a_cfg_cust_FilmMode_CheckIfCanTurnOn() )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_FILM_MODE,
            DBG_LOG_PRINT(("[MENU][FilmMode]{%s:%d} FilmMode cannot turn on => UI Grey out\n", __FUNCTION__, __LINE__));
        );

        return FALSE;
    }
#else

    CHAR    s_name[32] = {0};
    INT32   i4_ret  = 0;
#ifdef APP_SUPPPORT_FRC
    INT16   i2_val = 0;
#endif /* NEVER */

    if (_is_DVI_signal()) {
        return FALSE;
    }

#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    if( acfg_cust_Is_CurHDMI_PQ_PCMode() == TRUE )
    {
        return FALSE;
    }
#else
    if(_is_hdmi_sdr_hdr_444_content() == TRUE)
    {
        return FALSE;
    }
#endif


    i4_ret = a_cfg_custom_get_model_name(s_name);
    ACFG_LOG_ON_FAIL(i4_ret);

    //DTV02170653
    //if P series, panel is 120 HZ, spec had flow
    //Film Mode is available for 120 Hz panel for detection of film content only. Not disabled nor grayout with MEMC or Game Low Latency.
    if(a_acfg_cust_is_gll_enable() == TRUE && s_name[0] != 'P')
    {
        return FALSE;
    }
#endif

#if 0//def APP_SUPPPORT_FRC
    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION), &i2_val);
    MENU_LOG_ON_FAIL(i4_ret);

    //if(a_cfg_cust_drv_get_memc_enable() == TRUE)
    if (i2_val == 0)
    {
        //return FALSE;
    }
#endif

    if( FALSE == _is_pic_item_enabled()  )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_FILM_MODE,
            DBG_LOG_PRINT(("[MENU][FilmMode]{%s:%d} picture_lock => UI Grey out\n", __FUNCTION__, __LINE__));
        );
        return FALSE;
    }


    return TRUE;
}

static BOOL _vid_en_view_angle_enable(VOID)
{
    //MVP-2383
    //if TV detect VRR signal, then EVA should grayout and off
    //if(a_acfg_cust_vrr_is_enable_and_detect_stream() == TRUE || a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE)
    if( FALSE == a_cfg_cust_enhanced_viewing_angle_IfCanTurnOn() )
    {
        ACFG_DEBUG_VIEW_ANGLE( DBG_LOG_PRINT(("[ACFG][ViewAngle]%s() => rtn FALSE!\n", __func__, __LINE__ )); );
        return FALSE;
    }

    ACFG_DEBUG_VIEW_ANGLE( DBG_LOG_PRINT(("[ACFG][ViewAngle]%s() => rtn TRUE!\n", __func__, __LINE__ )); );
    return TRUE;
}

#if 0
static BOOL _is_adv_vid_peak_luminance_enable(VOID)
{
    if( FALSE == a_cfg_cust_CheckIfPeakLumiCanAdjust() )
    {
        DBG_LOG_PRINT(("[MENU][OLED][PeakLumi]{%s,%d} => UI greyout\n", __func__, __LINE__ ));
        return FALSE;
    }

    return TRUE;
}
#endif

/* func is used auto_enable Smart Interactivity */
static BOOL _is_smart_int_enable(VOID)
{
    // BOOL s_enable = TRUE;
    #ifdef APP_ADD_COUNTRY_CODE_SUPPORT
     ACFG_COUNTRY_CODE_T t_country;

     a_cfg_custom_get_country_code(&t_country);
     if ((t_country == ACFG_COUNTRY_CODE_CA)||(t_country == ACFG_COUNTRY_CODE_MEX) || (t_country == ACFG_COUNTRY_CODE_UNKNOWN))
    {
        /* if canada or mexico, enable Smart Interactivity */
        return FALSE;
    }
    else
    {
        /* if usa, disable Smart Interactivity*/
        return TRUE;
    }
    #else
        return TRUE;
    #endif
}

static BOOL _is_cc_enabled()
{
#if 0 //shoulde be enable as requirement
    UINT8   ui1_enabled = 0;

    a_cfg_get_cc_enabled(&ui1_enabled);
    if(ui1_enabled == APP_CFG_CC_OFF)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
#else
    return TRUE;
#endif
}

/* This func was used to auto_enbale channel scan status */
static BOOL _is_ch_scan_status_enable(VOID)
{
    return FALSE;
}

/* This func was used to auto_enbale tts item */
#ifdef APP_TTS_SUPPORT
static BOOL _is_tts_item_enable(VOID)
{
    return a_cfg_cust_is_tts_item_enable();
}
#endif

/* This func was used to auto_enbale zoom mode item */
static BOOL _is_zoom_mode_item_enable(VOID)
{
    //INT32                    i4_ret = 0;
    //NAV_RETAIL_MODE_STATUS_T retm_status;
    //i4_ret = a_nav_retail_mode_get_status(&retm_status);
    ACFG_RETAIL_MODE_T      t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    DBG_INFO(("%s:%d,_is_zoom_mode_item_enable,retail_mode:%d\r\n",__FILE__,__LINE__,t_retail_mode));
    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        return FALSE;
    }
    return TRUE;
}

static BOOL _is_cc_hiden()
{
    return !menu_cc_is_visible();
}
static BOOL _is_video_description_item_enable(VOID)
{
    CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8       ui1_input;
    ISL_REC_T   t_isl_rec = {0};

    /* Get target input source */
    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

     /*current state is not in TV and composite source */
#if 0
     if(t_isl_rec.e_src_type != INP_SRC_TYPE_TV &&  t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI)
     {
         return FALSE;
     }

     return TRUE;
#endif

        if((t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI)||
            (t_isl_rec.t_avc_info.e_video_type == (DEV_TUNER | 0x00000000)) ||
            (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMP_VIDEO))
         {
            DBG_INFO(("_is_video_description_item_enable TRUE L3734\n"));
             return TRUE;
         }else{
            DBG_INFO(("_is_video_description_item_enable FALSE L3737\n"));
             return FALSE;
         }

}

static BOOL _is_video_description_item_hiden(VOID)
{
    CHAR          s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8         ui1_input;
    ISL_REC_T     t_isl_rec = {0};

    /* Get target input source */
    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

     /*current state is smart cast */
     if(t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL &&  t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
     {
         return TRUE;
     }

     return FALSE;
}

#ifdef NEVER
static BOOL _is_smart_cast_app_source(VOID)
{
    CHAR          s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8         ui1_input;
    ISL_REC_T     t_isl_rec = {0};

    /* Get target input source */
    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

     /*current state is smart cast */
     if(t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL &&  t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
     {
         return TRUE;
     }

     return FALSE;
}
#endif /* NEVER */

static BOOL _is_auto_power_off_enable(VOID)
{
    ACFG_RETAIL_MODE_T      t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        return FALSE;
    }
    return TRUE;
}

static BOOL _is_blank_scrn_hidden(VOID)
{
    return FALSE;
}
static BOOL _is_scrn_saver_hidden(VOID)
{
    return TRUE;
}

//-----------------------------new add-------------------------------------//
static BOOL _is_auto_eq_mode_hidden(VOID)
{
    if(_is_auto_sb_soundbarsettings_hidden() == TRUE)
    return TRUE;
    else
    return (!amp_vndr_info.items_enable.eq);
}

static BOOL _is_auto_bass_enable(VOID)
{
    if(_is_auto_hidden_when_tv_audio_setting_show() == TRUE)
    return FALSE;
    else
    return TRUE;
}

static BOOL _is_auto_bass_hidden(VOID)
{
    return FALSE;//MVP-3687
}

static BOOL _is_auto_aud_balance_enable(VOID)
{
    if(_nav_cec_sac_is_sb_ready() == TRUE)
    return FALSE;
    else
    return TRUE;
}

static UINT16 _get_aud_speaker_idx(VOID)
{
    UINT16   ui2_val = 0;
    UINT16   ui2_idx = 0;
    UINT16   ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16   ui2_aud_out_mask = 0;
    INT16    i2_val_ex = 0;

    a_cfg_custom_get_speakers_out(&ui2_idx);
    a_cfg_av_get(ui2_id, &i2_val_ex);
    ui2_aud_out_mask = (UINT16)i2_val_ex;

    if(2 == ui2_idx)    //Off
    {
        ui2_val = APP_CFG_AUD_AD_SPEAKER_OFF;
    }
    else
    {
        if(ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) //On
        {
            ui2_val = APP_CFG_AUD_AD_SPEAKER_ON;
        }
        else  //Auto
        {
            ui2_val = APP_CFG_AUD_AD_SPEAKER_AUTO;
        }
    }

    return ui2_val;
}

static BOOL _is_auto_spdif_enable(VOID)
{
    if(_get_aud_speaker_idx() == APP_CFG_AUD_AD_SPEAKER_ON)
    return FALSE;
    else
    return TRUE;
}

static BOOL _is_auto_balance_hidden(VOID)
{
    return FALSE;
}

static BOOL _is_auto_aud_surround_enable(VOID)
{
    if(_nav_cec_sac_is_sb_ready() == TRUE)
    return FALSE;
    else
    return TRUE;
}

static BOOL _is_auto_aud_surround_hidden(VOID)
{
    return FALSE;
}

static BOOL _is_auto_tur_volume_hidden(VOID)
{
    if(_is_auto_hidden_when_tv_audio_setting_show() == TRUE)
    return TRUE;
    else
    return FALSE;
}

static BOOL _is_auto_sb_bass_hidden(VOID)
{
    if(_is_auto_sb_soundbarsettings_hidden() == TRUE)
    return TRUE;
    else
    return ((!amp_vndr_info.items_enable.bass));
}

static BOOL _is_auto_treble_enable(VOID)
{
    if(_is_auto_hidden_when_tv_audio_setting_show() == TRUE)
    return FALSE;
    else
    return TRUE;
}

static BOOL _is_auto_treble_hidden(VOID)
{
    return FALSE;//MVP-3687
}

static BOOL _is_auto_sb_treble_hidden(VOID)
{
    if(_is_auto_sb_soundbarsettings_hidden() == TRUE)
    return TRUE;
    else
    return (!amp_vndr_info.items_enable.treble);
}


static BOOL _is_auto_dialogue_hidden(VOID)
{
    if(_is_auto_sb_soundbarsettings_hidden() == TRUE)
    return TRUE;
    else
    return (!amp_vndr_info.items_enable.dialogue);
}

static BOOL _is_auto_dialogue_enable(VOID)
{
    if(amp_vndr_info.items_type.eq == _MENU_HIERARCHY_SB_SETTINGS_EQ_MODE_DIRECT)
    return FALSE;
    else
    return TRUE;
}


static BOOL _is_auto_sb_subwoofer_hidden(VOID)
{
    if(_is_auto_sb_soundbarsettings_hidden() == TRUE)
    return TRUE;
    else
    return (!amp_vndr_info.items_enable.subwoofer);
}

static BOOL _is_auto_night_mode_hidden(VOID)
{
    if(_is_auto_sb_soundbarsettings_hidden() == TRUE)
    return TRUE;
    else
    return (!amp_vndr_info.items_enable.nightmode);
}

static BOOL _is_auto_virtualx_hidden(VOID)
{
    if(_is_auto_sb_soundbarsettings_hidden() == TRUE)
    return TRUE;
    else
    return (!amp_vndr_info.items_enable.virtul);
}

static BOOL _is_auto_sb_speakertest_hidden(VOID)
{
    if(_is_auto_sb_soundbarsettings_hidden() == TRUE)
    return TRUE;
    else
    return (!amp_vndr_info.items_enable.speakertest);
}

static BOOL _is_auto_sb_info_hidden(VOID)
{
    if(_is_auto_sb_soundbarsettings_hidden() == TRUE)
    return TRUE;
    else
    return (!amp_vndr_info.items_enable.info);
}

static BOOL _title_tv_audio_settings_enable(VOID)
{
    return FALSE;
}


//-----------------------------new add--------------------------------------//


#ifdef APP_WAKE_ON_WLAN_ENABLE_UI
#ifdef APP_NETWORK_WIFI_SUPPORT
static BOOL _is_nw_wifi_setting_enable(VOID)
{
    BOOL b_enable = FALSE;

    a_cfg_get_network_enable(&b_enable);

    if (b_enable)
    {
        UINT8   ui1_interface;

        a_cfg_get_network_interface(&ui1_interface);

        return ui1_interface == APP_CFG_NET_INTERFACE_WIFI;
    }

    return b_enable;
}
#endif

#include "app_util/a_network.h"

static BOOL _is_nw_wifi_wol_enable(VOID)
{
#ifdef APP_NETWORK_WIFI_SUPPORT
    NW_WLAN_STATE_T  e_wlan_state = NW_WLAN_UNPLUG;
    if (_is_nw_wifi_setting_enable() == FALSE)
    {
        return FALSE;
    }
#endif

    a_nw_wlan_status(&e_wlan_state);

    if (e_wlan_state == NW_WLAN_UNPLUG)
    {
        return FALSE;
    }

    return TRUE;
}
#endif

#ifdef APP_WAKE_ON_LAN_ENABLE_UI
static BOOL _is_nw_ethernet_setting_enable(VOID)
{
    BOOL b_enable = FALSE;

   a_cfg_get_network_enable(&b_enable);
#ifdef APP_NETWORK_WIFI_SUPPORT
    if (b_enable)
    {
        UINT8   ui1_interface;

        a_cfg_get_network_interface(&ui1_interface);

        return ui1_interface == APP_CFG_NET_INTERFACE_ETH0;
    }
    return b_enable;
#else
    return b_enable;
#endif
}
#endif

static BOOL _is_native_app_enabled(VOID)
{
    if (msg_convert_custom_netflix_active() || msg_convert_custom_cobalt_alive() || msg_convert_custom_appletv_plus_active() || msg_convert_custom_hbomax_active() || msg_convert_custom_castcore_active())
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}



#ifdef APP_CTV_FAC_MENU_TREE
static VOID _set_internal_pattern_idx(UINT16 ui2_idx)
{
    return;
    //DTV00724780
}

static UINT16 _get_internal_pattern_idx(VOID)
{
    return 0;
}

static VOID _set_power_status_idx(UINT16 ui2_idx)
{
    _set_fac_power_status(ui2_idx);
}

static UINT16 _get_power_status_idx(VOID)
{
    return(_get_fac_power_status());
}
#endif

static INT32 _menu_page_tree_add(UINT16 ui2_parent,
                                         MENU_ITEM_T* pt_item,
                                         UINT16* pui2_item_id,
                                         menu_item_is_enabled_fct pf_item_is_enabled,
                                         menu_item_is_hidden_fct pf_item_is_hidden)
{
    MENU_CHK_FAIL(menu_page_tree_add(ui2_parent,
                                pt_item,
                                pui2_item_id));

    if (pf_item_is_enabled != NULL)
    {
        MENU_LOG_ON_FAIL(menu_page_tree_set_auto_enable(ui2_parent, *pui2_item_id
            , pf_item_is_enabled));
    }
    if (pf_item_is_hidden != NULL)
    {
        MENU_LOG_ON_FAIL(menu_page_tree_set_auto_hide(ui2_parent, *pui2_item_id
            , pf_item_is_hidden));
    }
    return MENUR_OK;
}

BOOL menu_picture_size_poition_is_hidde(VOID)
{
    ISL_REC_T t_isl_rec;
    MENU_CHK_FAIL(menu_get_crnt_isl(&t_isl_rec));

    /* set visibilty */
    if (t_isl_rec.e_src_type == INP_SRC_TYPE_TV)    /* TV */
    {
        return FALSE;
    }
    else if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)     /* HDMI */
    {
        return FALSE;
    }
    else if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV
        && (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI
        || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMP_VIDEO
        || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR))    /* COMP */
    {
        return FALSE;
    }
    return TRUE;
}

static INT32 _init_page_picture_size(UINT16 ui2_parent)
{
    UINT16 ui2_item_id;

    MENU_CHK_FAIL(menu_pm_page_create(&t_g_menu_page_vid_size,
                                 NULL,
                                 &ui4_g_menu_page_pic_size));

    MENU_CHK_FAIL(menu_page_tree_subpage_item(&t_menu_item_page_vid_more_size,
                                        MLM_MENU_KEY_ADJUST_PIC_SIZE,
                                        MLM_MENU_KEY_HELP_PIC_SIZE,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_g_menu_page_pic_size));

    MENU_CHK_FAIL(_menu_page_tree_add(ui2_parent,
                        &t_menu_item_page_vid_more_size,
                        &ui2_item_id,
                        NULL,
                        NULL));

    return MENUR_OK;

}

static INT32 _init_page_picture_position(UINT16 ui2_parent)
{
    UINT16 ui2_item_id;

    MENU_CHK_FAIL(menu_pm_page_create(&t_g_menu_page_vid_position,
                                 NULL,
                                 &ui4_g_menu_page_pic_postion));

    MENU_CHK_FAIL(menu_page_tree_subpage_item(&t_menu_item_page_vid_more_position,
                                        MLM_MENU_KEY_ADJUST_PIC_POS,
                                        MLM_MENU_KEY_HELP_PIC_POS,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_g_menu_page_pic_postion));

    MENU_CHK_FAIL(_menu_page_tree_add(ui2_parent,
                        &t_menu_item_page_vid_more_position,
                        &ui2_item_id,
                        NULL,
                        NULL));

    return MENUR_OK;

}

static INT32 _init_tree_picture_size_position(UINT16 ui2_parent)
{
    UINT16 ui2_item_id;

    MENU_CHK_FAIL(menu_page_tree_create(2,
                                   MLM_MENU_KEY_VID_PAGE_SIZE_POSITION,
                                   &ui4_page_picture_size_position));

    MENU_CHK_FAIL(menu_page_tree_subpage_item(&t_menu_item_page_picture_size_position,
                                            MLM_MENU_KEY_VID_PAGE_SIZE_POSITION,
                                            MLM_MENU_KEY_HELP_PAGE_SIZE_POSITION,
                                            MLM_MENU_KEY_EMPTY,
                                            ui4_page_picture_size_position));

    MENU_CHK_FAIL(_menu_page_tree_add(ui2_parent,
                                &t_menu_item_page_picture_size_position,
                                &ui2_item_id,
                                menu_picture_position_is_enable,
                                menu_picture_size_poition_is_hidde));

    MENU_LOG_ON_FAIL(_init_page_picture_size(ui4_page_picture_size_position));

    MENU_LOG_ON_FAIL(_init_page_picture_position(ui4_page_picture_size_position));

    return MENUR_OK;

}


static INT32 _init_tree_input_settings(UINT16 ui2_parent)
{
    UINT16 ui2_item_id;

    MENU_CHK_FAIL(menu_page_tree_create(5,
                           MLM_MENU_KEY_DEVICES,
                           &ui4_page_vid_inp_settings));

    MENU_CHK_FAIL(menu_page_tree_subpage_item(&t_menu_item_page_vid_inp_settings,
                                            MLM_MENU_KEY_DEVICES,
#ifdef MT5583_MODEL
                                            MLM_MENU_KEY_TAB_HELP_DEVICE_NAME_INPUT_2,
#else
                                            MLM_MENU_KEY_TAB_HELP_DEVICE_NAME_INPUT,
#endif
                                            MLM_MENU_KEY_EMPTY,
                                            ui4_page_vid_inp_settings));

    MENU_CHK_FAIL(menu_page_tree_add(ui2_parent,
                                &t_menu_item_page_vid_inp_settings,
                                &ui2_item_id));

    MENU_CHK_FAIL(inp_init_ctx());

    MENU_LOG_ON_FAIL(_init_tree_picture_size_position(ui4_page_vid_inp_settings));


    MENU_LOG_ON_FAIL(_menu_page_tree_add(ui4_page_vid_inp_settings,
                                      &t_g_menu_common_item_inp_hdmi_mode,
                                      &ui2_item_id,
                                      _is_hdmi_mode_enable,
                                      _is_hdmi_mode_hidden));

#if( ENABLE_FULL_COLOR_444 )
    MENU_LOG_ON_FAIL(_menu_page_tree_add(ui4_page_vid_inp_settings,
                                      &t_g_menu_common_item_inp_full_color_444,
                                      &ui2_item_id,
                                      _is_full_color_444_enable,
                                      _is_full_color_444_hidden));
#endif

    MENU_LOG_ON_FAIL(_menu_page_tree_add(ui4_page_vid_inp_settings,
                                      &t_g_menu_common_item_inp_film_maker_mode,
                                      &ui2_item_id,
                                      NULL,
                                      _is_filmmaker_mode_hidden));

    MENU_LOG_ON_FAIL(_menu_page_tree_add(ui4_page_vid_inp_settings,
                                      &t_g_menu_common_item_vid_hdmi_mode,
                                      &ui2_item_id,
                                      is_adv_color_space_enable,
                                      is_adv_color_space_hidden));

    return MENUR_OK;
}

static INT32 _init_menu_tree(VOID)
{
    INT32               i4_ret;
    UINT16              ui2_item_id;
    UINT16              ui2_item_txt = MLM_MENU_KEY_EMPTY;

    /*----------------------------------------------------------------*/
    /*                        Create all pages                        */
    /*----------------------------------------------------------------*/
    /*KASI*/
    extern MENU_PAGE_FCT_TBL_T t_g_menu_device_page_bt_device;
    i4_ret = menu_pm_page_create(&t_g_menu_device_page_bt_device,
                                 NULL,
                                 &ui4_g_menu_page_bt_headphones);
    MENU_LOG_ON_FAIL(i4_ret);

    /* create Timers page */
    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_MAIN_MENU_TIMERS,
                                   &ui4_g_menu_page_slp);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_timers,
                                         MLM_MENU_KEY_MAIN_MENU_TIMERS,
                                         MLM_MENU_KEY_TAB_SLEEP_TIMER,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_slp);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(3,
                                   MLM_MENU_KEY_ADVERTISING,
                                   &ui4_g_menu_page_advertising);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_subpage_item(&t_g_menu_custom_item_advertising,
                                         MLM_MENU_KEY_ADVERTISING,
                                         MLM_MENU_KEY_ADVERTISING_TIP,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_advertising);
    MENU_CHK_FAIL(i4_ret);

     /**
    *Create Audio Sound Bar Settings Subpage
    */
    i4_ret = menu_page_tree_create(1,\
                                   MLM_MENU_KEY_AUD_SOUND_BAR_SETTINGS,
                                   &ui4_page_aud_sb_settings);
    MENU_LOG_ON_FAIL(i4_ret);

    /**
    *Create Audio Sound Bar Settings Subpage
    */
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_tv_aud_sb_settings,
                                                    MLM_MENU_KEY_AUD_SOUND_BAR_SETTINGS,
                                                    MLM_MENU_KEY_AUD_SOUND_BAR_SETTINGS_TIP,
                                                    MLM_MENU_KEY_EMPTY,
                                                    ui4_page_aud_sb_settings);
    MENU_LOG_ON_FAIL(i4_ret);

    /**
    *Create TV Audio Settings Subpage
    */

    i4_ret = menu_page_tree_create(1,\
                                    MLM_MENU_KEY_AUD_SOUND_BAR_SETTINGS,
                                    &ui4_page_aud_tv_aud_settings);

    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_tv_audio_settings,
                                                    MLM_MENU_KEY_TV_AUDIO_SETTINGS,
                                                    MLM_MENU_KEY_EMPTY,
                                                    MLM_MENU_KEY_EMPTY,
                                                    ui4_page_aud_tv_aud_settings);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(40,
                                   MLM_MENU_KEY_VID_PICTURE_TITLE,
                                   &ui4_g_menu_page_vid);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_MAIN_MENU_PIC_SETTING,
                                   &ui4_page_vid_more);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VID_SZ_POS,
                                   &ui4_page_vid_more_sz_pos);
    MENU_LOG_ON_FAIL(i4_ret);

#if 0
    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VID_CLR_TEMP,
                                   &ui4_page_vid_more_clr_tmp);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = menu_page_tree_create(20,
                                   MLM_MENU_KEY_VID_ADVANCED_PICTURE,
                                   &ui4_page_vid_more_adv_pic);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(8,
                                   MLM_MENU_KEY_VID_MOTION_CONTROL,
                                   &ui4_page_vid_motion_control);
    MENU_LOG_ON_FAIL(i4_ret);

#if 1 // 2020-12-07.Spec has been updated to rename all instances to Gaming instead of V-Gaming or ProGaming
    ui2_item_txt = MLM_MENU_KEY_VID_GAMEING_ENGINE;
#else
    if(_is_rename_v_gaming_engine())
    {
        ui2_item_txt = MLM_MENU_KEY_VID_V_GAMEING_ENGINE;
    }
    else
    {
        ui2_item_txt = MLM_MENU_KEY_VID_PROGAMEING_ENGINE;
    }
#endif
    i4_ret = menu_pm_page_create(&t_g_menu_page_gaming_mode,
                                 NULL,
                                 &ui4_page_vid_progame_engine);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(8,
                                   MLM_MENU_KEY_VID_CALI_TESTS,
                                   &ui4_page_vid_cal_pattern_test);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(4,
                                   MLM_MENU_KEY_VID_OLED_PANEL,
                                   &ui4_page_vid_oled_panel);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_AUD_ADV,
                                   &ui4_page_aud_adv);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VID,
                                   &ui4_g_menu_page_mmp);
    MENU_LOG_ON_FAIL(i4_ret);
#if 0
    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VID_CLR_TEMP,
                                   &ui4_page_clr_tmp);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    i4_ret = menu_page_tree_create(15,
                                   MLM_MENU_KEY_VID_PIC_MODE_CUSTOM,
                                   &ui4_g_menu_page_pic_custom);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VID_CLR_TEMP_USER,
                                   &ui4_g_menu_page_clr_tmp);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_PIP_POP_CTRL
    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_PIP_MODE_PIP,
                                   &ui4_page_pip);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_network;
    i4_ret = menu_pm_page_create(&t_g_menu_common_page_network,
                                 NULL,
                                 &ui4_page_nw);
    MENU_CHK_FAIL(i4_ret);

    ui4_g_menu_page_nw = ui4_page_nw;

    i4_ret = menu_pm_page_create(&t_g_menu_page_audio_dbginfo, NULL, &ui4_g_menu_page_audio_dbginfo);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_page_hdmi_dbginfo, NULL, &ui4_g_menu_page_hdmi_dbginfo);
    MENU_CHK_FAIL(i4_ret);

    /*test special param page*/
    i4_ret = menu_pm_page_create(&t_g_menu_common_test_special_param,
                                 (VOID*)NULL,
                                 &ui4_g_menu_page_test_special_param);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_LOG2USB_SUPPORT
    i4_ret = menu_pm_page_create(&t_g_menu_common_log_to_usb,
                                 (VOID*)NULL,
                                 &ui4_g_menu_page_log_to_usb);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VGA,
                                   &ui4_page_vga);
    MENU_LOG_ON_FAIL(i4_ret);

    /**
    *Create Audio Subpage
    */
    i4_ret = menu_page_tree_create(32,
                                   MLM_MENU_KEY_AUD,
                                   &ui4_page_aud);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_MAIN_MENU_TV_SETTING,
                                   &ui4_g_menu_page_tv);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(11,
                                   MLM_MENU_KEY_CLRMEM_PWD_TITLE,
                                   &ui4_g_menu_page_par);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(4,
                                   MLM_MENU_KEY_CC,
                                   &ui4_g_menu_page_cc);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_cc,
                                 MLM_MENU_KEY_CC,
                                 MLM_MENU_KEY_TAB_HELP_CC,
                                 MLM_MENU_KEY_EMPTY,
                                 ui4_g_menu_page_cc);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(3,
                                   MLM_MENU_KEY_CC,
                                   &ui4_page_cc);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(5,
                                   MLM_MENU_KEY_PC_SETTING,
                                   &ui4_page_pc_setting);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(15,
                                   MLM_MENU_KEY_TV_SETTING,
                                   &ui4_page_tv_setting);
    MENU_CHK_FAIL(i4_ret);

    /* create System page */
    i4_ret = menu_page_tree_create(20,     //12,
                                   MLM_MENU_KEY_MAIN_MENU_SYSTEM,
                                   &ui4_g_menu_page_setup);
    MENU_LOG_ON_FAIL(i4_ret);

    /* create Reset & Admin page */
    i4_ret = menu_page_tree_create(14,
                                   MLM_MENU_KEY_MAIN_MENU_SYS_INFO_AND_RESET,
                                   &ui4_page_help_sys_info_and_reset);
    ui4_g_menu_page_reset_admin = ui4_page_help_sys_info_and_reset;
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_H_V_POS,
                                   &ui4_page_hv_pos);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_TV_SETTINGS_DATE_TIME,
                                   &ui4_page_date_time);
    MENU_LOG_ON_FAIL(i4_ret);

    /* bass & treble */
    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_AUD_BLASS_AND_TREBLE,
                                   &ui4_page_bass_treble);
    MENU_LOG_ON_FAIL(i4_ret);

    /* create Guided Setup page */
    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_GUIDE_SETUP,
                                   &ui4_page_sys_info);
    MENU_LOG_ON_FAIL(i4_ret);

    /* create System Reset page */
    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_SYSTEM_RESET,
                                   &ui4_page_sys_reset);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_2K12_RETAIL_DEMO_MODE

    /* create Store Demo page */
    i4_ret = menu_page_tree_create(5,
                                   MLM_MENU_KEY_DEMO_MODE,
                                   &ui4_page_help_demo_mode);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifdef ENABLE_MENU_DLNA_SETTINGS
#if defined (APP_NET_DLNA_SUPPORT) && defined(APP_NETWORK_SUPPORT)
    i4_ret = menu_page_tree_create(3,
                                   MLM_MENU_KEY_NET_CFG_DLNA_SETTINGS,
                                   &ui4_page_dlna_setting);
    MENU_CHK_FAIL(i4_ret);
#endif
#endif

#ifdef OLD_EQ
    i4_ret = menu_pm_page_create(&t_g_menu_common_page_eq_bands_setting,
                                 NULL,
                                 &ui4_page_eq_bands_setting);
    MENU_CHK_FAIL(i4_ret);
#else
    i4_ret = menu_pm_page_create(&t_g_menu_common_page_new_eq,
                                 NULL,
                                 &ui4_page_eq_bands_setting);
    MENU_CHK_FAIL(i4_ret);
#endif
    ui4_g_menu_page_eq_bands_setting = ui4_page_eq_bands_setting;

    /* create Channel page */
    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_auto_scan2,
                                 NULL,
                                 &ui4_g_menu_page_ch_scan);
    MENU_LOG_ON_FAIL(i4_ret);

    /* create Find New Channels page */
    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_auto_scan2_new,
                                 NULL,
                                 &ui4_g_menu_page_ch_scan_new);
    MENU_LOG_ON_FAIL(i4_ret);

    /* create Partial Channel Scan page */
    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_adv_scan_rng,
                                 NULL,
                                 &ui4_page_adv_scan_rng);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_adv_scan_sgl,
                                 NULL,
                                 &ui4_page_adv_scan_sgl);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_FAV_LST
    i4_ret = menu_common_create_page_fav_lst2(&ui4_page_ch_fav);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /* create Device page */
    i4_ret = menu_pm_page_create(&t_g_menu_device_page_device_setting,
                                 NULL,
                                 &ui4_page_device_setting);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_cap_stl,
                                 NULL,
                                 &ui4_page_cap_stl);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_pwd,
                                 (VOID*)ui4_g_menu_page_par,
                                 &ui4_g_menu_page_pwd);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_vchip_us_tv,
                                 NULL,
                                 &ui4_page_vchip_us_tv);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_vchip_us_movie,
                                 NULL,
                                 &ui4_page_vchip_us_movie);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_vchip_ca_en,
                                 NULL,
                                 &ui4_page_vchip_ca_en);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_vchip_ca_fr,
                                 NULL,
                                 &ui4_page_vchip_ca_fr);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_page_screen_mode,
                                 NULL,
                                 &ui4_page_scr_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_g_menu_page_scr_mode = ui4_page_scr_mode;

    MENU_DEBUG_ASPECT_RATIO( DBG_LOG_PRINT(("[MENU][ASPECT]{%s,%d} ui4_g_menu_page_scr_mode:%d\n",
        __FUNCTION__, __LINE__, ui4_g_menu_page_scr_mode )); );

    i4_ret = menu_pm_page_create(&t_g_menu_page_aspect_ratio,
                                 NULL,
                                 &ui4_g_menu_page_aspect_ratio);
    MENU_LOG_ON_FAIL(i4_ret);

    MENU_DEBUG_ASPECT_RATIO( DBG_LOG_PRINT(("[MENU][ASPECT]{%s,%d} ui4_g_menu_page_aspect_ratio:%d\n",
        __FUNCTION__, __LINE__, ui4_g_menu_page_aspect_ratio )); );

    i4_ret = menu_pm_page_create(&t_g_menu_page_sb_setting_eq_mode,
                                 NULL,
                                 &ui4_g_menu_page_sb_setting_eq_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_page_tv_name,
                                 NULL,
                                 &ui4_menu_page_tv_name);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_pm_page_create(&t_g_menu_device_page_device_setting,
                                 NULL,
                                 &ui4_g_menu_page_device_setting);
    MENU_LOG_ON_FAIL(i4_ret);
/*
    i4_ret = menu_pm_page_create(&t_g_menu_device_page_mobile_device,
                                 NULL,
                                 &ui4_g_menu_page_mobile_device);
    MENU_LOG_ON_FAIL(i4_ret);
*/
    //color tuner
    i4_ret = menu_pm_page_create(&t_g_menu_common_page_pic_quality,
                                 (VOID*)NULL,
                                 &ui4_g_menu_custom_page_pic_quality);
    MENU_LOG_ON_FAIL(i4_ret);

    //white balance tuner
    i4_ret = menu_pm_page_create(&t_g_menu_common_page_white_balance_tuner,
                                 (VOID*)NULL,
                                 &ui4_g_menu_white_balance_tuner_page);
    MENU_LOG_ON_FAIL(i4_ret);



    /* Reduce Noise page */
    i4_ret = menu_page_tree_create(5,
                                   MLM_MENU_KEY_REDUCE_NOISE,
                                   &ui4_page_reduce_noise);
    MENU_CHK_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                           Device Setup Page                                                          */
    /*----------------------------------------------------------------*/
    /* 3D setting */
    i4_ret = menu_pm_page_create(&t_g_menu_custom_page_3D_setting,
                                 NULL,
                                 &ui4_page_3D_setting);
    MENU_CHK_FAIL(i4_ret);
    ui4_g_menu_page_3D_setting = ui4_page_3D_setting;

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_nw_terms,
                                 NULL,
                                 &ui4_g_menu_page_terms);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_nw_terms_sub,
                                 NULL,
                                 &ui4_g_menu_page_terms_sub);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VID_PAGE_SIZE_POSITION,
                                   &ui4_page_vid_more_size_position);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_custom_page_mmp_dev_list,
                                 NULL,
                                 &ui4_page_mmp_dev_list);
    MENU_CHK_FAIL(i4_ret);
    ui4_g_menu_page_mmp_dev_list = ui4_page_mmp_dev_list;

    i4_ret = menu_pm_page_create(&t_g_menu_custom_page_mmp_media_type,
                                 NULL,
                                 &ui4_page_mmp_media_type_page);
    MENU_CHK_FAIL(i4_ret);
    ui4_g_menu_page_mmp_media_type = ui4_page_mmp_media_type_page;

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_RESET_CONFIRM_SETUP_WIZARD,
                                                   MLM_MENU_KEY_YES,
                                                   MLM_MENU_KEY_NO,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _start_setup_wizard,
                                                   NULL,
                                                   &ui4_page_setup_wizard_reset);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_pwd,
                                 (VOID*)ui4_page_setup_wizard_reset,
                                 &ui4_g_menu_page_setup_wizard_pwd);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_pwd,
                                 (VOID*)ui4_g_menu_page_ch_scan,
                                 &ui4_g_menu_page_ch_scan2_pwd);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_auto_scan2,
                                 NULL,
                                 &ui4_page_ch_scan);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_auto_scan2_new,
                                 NULL,
                                 &ui4_page_ch_scan_new);
    MENU_CHK_FAIL(i4_ret);


#ifdef APP_CEC_MENU
    /*CEC special page*/
    i4_ret = menu_pm_page_create(&t_g_menu_common_page_cec,
                                 NULL,
                                 &ui4_page_cec);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_cec,
                                     MLM_MENU_KEY_CEC_SETTINGS,
                                     MLM_MENU_KEY_HELP_SETUP_CEC,
                                     MLM_MENU_KEY_EMPTY,
                                     ui4_page_cec);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_cec_dev_discovery,
                                        MLM_MENU_KEY_CEC_DEV_DISCOVER,
                                        MLM_MENU_KEY_CEC_DEV_DISCOVER_HELP,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_page_cec_dev_discovery);
    MENU_LOG_ON_FAIL(i4_ret);
#endif /* APP_CEC_MENU */

    i4_ret = menu_pm_page_create(&t_g_menu_device_page_mobile_device,
                             NULL,
                             &ui4_g_menu_page_mobile_device);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_mobile_device,
                                     MLM_MENU_KEY_MOBILE_DEVICE,
                                     MLM_MENU_KEY_MOBILE_DEVICE_HELP,
                                     MLM_MENU_KEY_EMPTY,
                                     ui4_g_menu_page_mobile_device);
    MENU_LOG_ON_FAIL(i4_ret);


    /*subpage of user manual , just for temporary using*/
    i4_ret = menu_pm_page_create(&t_g_menu_user_manual,
                             NULL,
                             &ui4_g_menu_page_user_manual);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_REMOVE_MOBILE_DEVICE_DIALOG,
                           MLM_MENU_KEY_MOBILE_DEVICE_DIALOG_REMOVE,
                           MLM_MENU_KEY_MOBILE_DEVICE_DIALOG_CNCL,
                           UI_SIMPLE_DIALOG_STYLE_SMALL,
                           WGL_AS_CENTER_CENTER,
                           FALSE,
                           mobile_device_delete_paired_device,
                           NULL,
                           &ui4_mobile_device_delete_dialog_page_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*subpage of user manual , just for temporary using*/
    i4_ret = menu_pm_page_create(&t_g_menu_user_manual,
                             NULL,
                             &ui4_g_menu_page_user_manual);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                               MLM_MENU_KEY_TTS_ACCESSIBILITY,
                               &ui4_page_accessibility);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_accessibility,
                                         MLM_MENU_KEY_TTS_ACCESSIBILITY,
                                         MLM_MENU_KEY_HELP_TIP_ACCESSIBILITY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_accessibility);
    MENU_CHK_FAIL(i4_ret);


#ifdef ENABLE_MENU_DLNA_SETTINGS
#if defined (APP_NET_DLNA_SUPPORT) && defined(APP_NETWORK_SUPPORT)
        i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_dlna_setting,
                                             MLM_MENU_KEY_NET_CFG_DLNA_SETTINGS,
                                             MLM_MENU_KEY_NET_CFG_DLNA_SETTINGS,
                                             MLM_MENU_KEY_EMPTY,
                                             ui4_page_dlna_setting);
        MENU_CHK_FAIL(i4_ret);
#endif
#endif
    /* create Find Channels subpage */
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_ch_scan,
                                         MLM_MENU_KEY_SCAN_AUTO_CHANNEL,
                                         MLM_MENU_KEY_TAB_HELP_AUOT_SEARCH,
                                         MLM_MENU_KEY_HELP_SCAN,
                                         ui4_page_ch_scan);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_ch_scan_new,
                                         MLM_MENU_KEY_FIND_NEW_CHANNELS,
                                         MLM_MENU_KEY_TAB_HELP_AUOT_SEARCH_NEW,
                                         MLM_MENU_KEY_HELP_SCAN,
                                         ui4_page_ch_scan_new);
    MENU_CHK_FAIL(i4_ret);


    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_add_analog_scan,
                               NULL,
                               &ui4_g_menu_atsc_page_add_analog);
    MENU_LOG_ON_FAIL(i4_ret);
    /* create Add Analog Channel subpage */
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_add_analog_scan,
                                         MLM_MENU_KEY_ADD_ANALOG_SCAN_TITLE,
                                         MLM_MENU_KEY_TAB_HELP_ANALOG_SCAN,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_atsc_page_add_analog);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_CEC_MENU
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_cec,
                                         MLM_MENU_KEY_CEC_SETTINGS,
                                         MLM_MENU_KEY_HELP_SETUP_CEC,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_cec);
    MENU_CHK_FAIL(i4_ret);
#endif

    i4_ret = menu_common_create_page_sk_ch2(&ui4_page_ch_sk);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_ch_sk,
                                         MLM_MENU_KEY_CH_SK,
                                         MLM_MENU_KEY_TAB_HELP_SKIP_CH,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_ch_sk);
    MENU_CHK_FAIL(i4_ret);

    /* create the level page of the open-vchip */
#ifdef APP_MENU_OP_VCHIP_ENABLE
    i4_ret = menu_atsc_create_page_op_vchip_lvl(&ui4_page_op_vchip_lvl, 0);
    MENU_LOG_ON_FAIL(i4_ret);

    if (i4_ret == MENUR_OK)
    {
        /* create the dimension page of the open-vchip */
        i4_ret = menu_atsc_create_page_op_vchip_dim(&ui4_page_op_vchip_dim, ui4_page_op_vchip_lvl);
        MENU_LOG_ON_FAIL(i4_ret);

        if (i4_ret == MENUR_OK)
        {
            /* create the region page of the open-vchip */
            i4_ret = menu_atsc_create_page_op_vchip_rgn(&ui4_page_op_vchip_rgn, ui4_page_op_vchip_dim);
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    i4_ret = menu_pm_page_create(&t_g_menu_atsc_page_drrt_system,
                                 NULL,
                                 &ui4_page_op_vchip_drrt);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    /* create 3D subpage */
    i4_ret = menu_page_tree_subpage_item(&t_g_menu_item_page_vid_3d_mode,
                                        MLM_MENU_KEY_X_3D_SETTING_3D,
                                        MLM_MENU_KEY_HELP_3D_SETTING,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_g_menu_page_3D_setting);
    MENU_LOG_ON_FAIL(i4_ret);

    /* create Wide subpage */
    i4_ret = menu_page_tree_subpage_item(&t_g_menu_item_page_wide_mode,
                                        MLM_MENU_KEY_VID_SCR_MODE,
                                        MLM_MENU_KEY_TAB_HELP_WIDE,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_page_scr_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_create_page_bk_ch2(&ui4_page_ch_bk);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_create_page_sk_inp(&ui4_page_inp_sk);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_create_page_bk_inp(&ui4_page_inp_bk);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_create_page_inp_src(&ui4_g_menu_page_inp_src);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_create_page_inp_set(&ui4_page_inp_set);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_create_page_naming(&ui4_g_menu_page_inp_naming);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_input_sys_pin,
                                 NULL,
                                 &ui4_g_page_input_sys_pin);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_chg_pwd,
                                 NULL,
                                 &ui4_page_chg_pwd);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_vga_auto,
                                 NULL,
                                 &ui4_g_menu_page_vga_auto);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_date_time,
                                 NULL,
                                 &ui4_page_date);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef COMMON_IMG_CLNR_ENABLE
    i4_ret = menu_pm_page_create(&t_g_menu_common_page_img_clnr,
                                 NULL,
                                 &ui4_page_img_clnr);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = menu_pm_page_create(&t_g_menu_page_ex_main_menu,
                               NULL,
                               &ui4_g_menu_page_main_menu);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create (10,
                                    MLM_MENU_KEY_TUNER_SET,
                                    &ui4_g_menu_page_channels);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_page_ex_masterlist,
                                 NULL,
                                 &ui4_page_masterlist);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_page_ex_ch_edit,
                                 NULL,
                                 &ui4_page_ch_edit);
    MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_MENU_VCT_RAW_SUPPORT
    i4_ret = menu_pm_page_create(&t_g_menu_page_vct_raw,
                                 NULL,
                                 &ui4_g_menu_page_vct_raw_dump);
    MENU_LOG_ON_FAIL(i4_ret);
    #endif

    /*----------------------------------------------------------------*/
    /*                        help tos. Page                      */
    /*----------------------------------------------------------------*/
    i4_ret = menu_pm_page_create(&t_g_menu_common_page_vizio_tos,
                                 NULL,
                                 &ui4_page_vizio_tos);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_help_tos,
                                         MLM_MENU_KEY_VIZIO_PRIVACY_POLICY,
                                         MLM_MENU_KEY_VIZIO_TERM_OF_SERVICE,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_vizio_tos);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                       wizard mode. Page                        */
    /*----------------------------------------------------------------*/
    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_RESET_CONFIRM,
                                                   MLM_MENU_KEY_YES,
                                                   MLM_MENU_KEY_NO,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _reset_wizard_mode,
                                                   NULL,
                                                   &ui4_page_start_wizard);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                        picture setting Reset. Page             */
    /*----------------------------------------------------------------*/
    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_RESET_CONFIRM_PICTURE_SETTING,
                                                   MLM_MENU_KEY_HELP_RESET,
                                                   MLM_MENU_KEY_HELP_CNCL,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _reset_picture_page,
                                                   NULL,
                                                   &ui4_g_menu_page_picture_reset);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                        picture mode Reset. Page                */
    /*----------------------------------------------------------------*/
    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_RESET_CONFIRM_PICTURE_MODE,
                                                   MLM_MENU_KEY_HELP_RESET,
                                                   MLM_MENU_KEY_HELP_CNCL,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _reset_pic_mode_page,
                                                   NULL,
                                                   &ui4_g_menu_page_pic_mode_reset);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                        audio Reset. Page                       */
    /*----------------------------------------------------------------*/

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_RESET_CONFIRM_AUDIO_SETTING,
                                                   MLM_MENU_KEY_HELP_RESET,
                                                   MLM_MENU_KEY_HELP_CNCL,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _reset_audio_page,
                                                   NULL,
                                                   &ui4_g_menu_page_audio_reset);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_DELETE_AUD_MODE_DIALOG,
                                                   MLM_MENU_KEY_DELETE_ITEM_DELETE,
                                                   MLM_MENU_KEY_DELETE_ITEM_CANCEL,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _delete_audio_mode,
                                                   NULL,
                                                   &ui4_g_menu_page_del_aud_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_HELP_RESET_CHANNEL_LOCK,
                                                   MLM_MENU_KEY_HELP_RESET,
                                                   MLM_MENU_KEY_HELP_CNCL,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _reset_channel_lock_page,
                                                   NULL,
                                                   &ui4_g_menu_page_channel_lock_reset);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_scrn_blank,
                                 NULL,
                                 &ui4_g_menu_page_blank_scrn);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Blank Screen Now */
    i4_ret = menu_page_tree_subpage_item(&t_g_menu_common_item_blank_scrn_now,
                                      MLM_MENU_KEY_ITEM_BLANK_SCRN_NOW,
                                      MLM_MENU_KEY_HELP_TIP_BLANK_SCRN_NOW,
                                      MLM_MENU_KEY_EMPTY,
                                      ui4_g_menu_page_blank_scrn);
    MENU_CHK_FAIL(i4_ret);




    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_RESET_CONFIRM_ALL_SETTINGS,
                                                   MLM_MENU_KEY_HELP_RESET,
                                                   MLM_MENU_KEY_HELP_CNCL,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _reset_pub,
                                                   NULL,
                                                   &ui4_g_menu_page_reset_pub);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_RESET_CONFIRM,
                                                   MLM_MENU_KEY_YES,
                                                   MLM_MENU_KEY_NO,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _reset_pri,
                                                   NULL,
                                                   &ui4_page_reset_pri);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_RESET_CONFIRM,
                                                   MLM_MENU_KEY_YES,
                                                   MLM_MENU_KEY_NO,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _reset_fac,
                                                   NULL,
                                                   &ui4_page_reset_fac);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_RESET_CONFIRM_FAC_SETTINGS,
                                                   MLM_MENU_KEY_HELP_RESET,
                                                   MLM_MENU_KEY_HELP_CNCL,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   clear_memory,
                                                   NULL,
                                                   &ui4_g_page_clear_memory_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_clear_memory_pwd,
                                 (VOID*)ui4_g_page_clear_memory_dialog,
                                 &ui4_g_page_clear_memory);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_SYS_REST_TV_AD_MSG,
                                                   MLM_MENU_KEY_YES,
                                                   MLM_MENU_KEY_NO,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _reset_tv_ad_id,
                                                   NULL,
                                                   &ui4_page_reset_tv_ad_id_dialog);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_common_page_simple_dialog_create_ex(MLM_MENU_KEY_VID_OLED_SCRREN_REFRESH_MSG,
                                                      MLM_MENU_KEY_VID_OLED_SCRREN_REFRESH_START_AT_POWER_OFF,
                                                      MLM_MENU_KEY_VID_OLED_SCRREN_REFRESH_BTN_START_NOW,
                                                      MLM_MENU_KEY_VID_OLED_SCRREN_REFRESH_BTN_CANCELE,
                                                      UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                      WGL_AS_CENTER_CENTER,
                                                      UI_SIMPLE_DIALOG_ANSWER_INFO,
                                                      _oled_screen_refresh_start_at_power_off,
                                                      _oled_screen_refresh_start_now,
                                                      _oled_screen_refresh_cancel,
                                                      &ui4_page_oled_screen_1);
    MENU_LOG_ON_FAIL(i4_ret);
    MENU_LOG_ON_FAIL(menu_common_page_simple_dialog_create_ex(MLM_MENU_KEY_VID_OLED_SCRREN_REFRESH_START_AT_POWER_OFF_POPUP,
                                                              MLM_MENU_KEY_OK,
                                                              MLM_MENU_KEY_EMPTY,
                                                              MLM_MENU_KEY_EMPTY,
                                                              UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                              WGL_AS_CENTER_CENTER,
                                                              UI_SIMPLE_DIALOG_ANSWER_YES,
                                                              _oled_screen_refresh_start_at_power_off,
                                                              NULL,
                                                              NULL,
                                                              &ui4_page_oled_screen_2));

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_USA_COUNTRY_CODE_HELP_INFO,
                                               MLM_MENU_KEY_HELP_RESET,
                                               MLM_MENU_KEY_HELP_CNCL,
                                               UI_SIMPLE_DIALOG_STYLE_SMALL,
                                               WGL_AS_CENTER_CENTER,
                                               FALSE,
                                               _chg_country_code,
                                               NULL,
                                               &ui4_page_chg_country_code_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_custom_page_time_local_setting_auto_dst,
                                 NULL,
                                 &ui4_page_time_local_setting);
    MENU_CHK_FAIL(i4_ret);
#else
    i4_ret = menu_pm_page_create(&t_g_menu_custom_page_time_local_setting,
                                 (VOID*)ui4_g_page_clear_memory,
                                 &ui4_page_time_local_setting);
    MENU_CHK_FAIL(i4_ret);
#endif
#else

#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
        i4_ret = menu_pm_page_create(&t_g_menu_custom_page_time_local_setting_auto_dst,
                                     NULL,
                                     &ui4_page_time_local_setting);
        MENU_CHK_FAIL(i4_ret);
#else
        i4_ret = menu_pm_page_create(&t_g_menu_custom_page_time_local_setting,
                                     NULL,
                                     &ui4_page_time_local_setting);
        MENU_CHK_FAIL(i4_ret);
#endif
#endif

#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_ENG_MENU_LANGUAGE_HELP_INFO,
                                               MLM_MENU_KEY_HELP_RESET,
                                               MLM_MENU_KEY_HELP_CNCL,
                                               UI_SIMPLE_DIALOG_STYLE_SMALL,
                                               WGL_AS_CENTER_CENTER,
                                               FALSE,
                                               _reset_menu_language,
                                               _cancel_menu_language,
                                               &ui4_page_menu_language_dialog);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_time_local_setting,
                                         MLM_MENU_KEY_TIME_LOCAL,
                                         MLM_MENU_KEY_TAB_HELP_TIME_LOCAL,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_time_local_setting);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_CHECK_FOR_UPDATES_DIALOG,
                                                   MLM_MENU_KEY_YES,
                                                   MLM_MENU_KEY_NO,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _service_check,
                                                   NULL,
                                                   &ui4_g_page_service_check_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_HELP_SERVICE_RST,
                                                   MLM_MENU_KEY_YES,
                                                   MLM_MENU_KEY_NO,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _service_reset,
                                                   NULL,
                                                   &ui4_g_page_service_rst_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_auto_phase,
                                 NULL,
                                 &ui4_page_auto_phase);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_custom_create_page_inp_edit(&ui4_page_inp_edit);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                          Subpage Items                         */
    /*----------------------------------------------------------------*/

    /* create Picture Mode subpage */
#ifdef NEVER
    if(a_cfg_cust_get_support_energy_start_by_mode_name())
    {
        i4_ret = menu_page_tree_subpage_item(&t_menu_page_vid_pic_mode,
                                                MLM_MENU_KEY_VID_PIC_MODE_ITEM,
                                                MLM_MENU_KEY_TAB_HELP_PICTURE_MODE,
                                                MLM_MENU_KEY_EMPTY,
                                                ui4_g_menu_custom_page_pic_mode);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
#endif /* NEVER */

    i4_ret = menu_pm_page_create(&t_g_menu_page_pic_mode,
                                 NULL,
                                 &ui4_g_menu_custom_page_pic_mode);

    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_inp_src,
                                         MLM_MENU_KEY_INPUT_SOURCE,
                                         MLM_MENU_KEY_HELP_TIP_TV_SETTING_SEL_INP,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_inp_src);
    MENU_LOG_ON_FAIL(i4_ret);
    /* create name subpage */
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_inp_name,
                                            MLM_MENU_KEY_NAME_INPUT,
                                            MLM_MENU_KEY_HELP_NAME_INPUT,
                                            MLM_MENU_KEY_EMPTY,
                                            ui4_g_menu_page_inp_naming);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_g_menu_custom_item_cc,
                                         MLM_MENU_KEY_CC,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_cc);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_pc_setting,
                                         MLM_MENU_KEY_PC_SETTING,
                                         MLM_MENU_KEY_HELP_TIP_TV_SETTING_PC_SETTING,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_pc_setting);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_tv_setting,
                                         MLM_MENU_KEY_TV_SETTING,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_tv_setting);
    MENU_LOG_ON_FAIL(i4_ret);

#if 0
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_clr_tmp,
                                         MLM_MENU_KEY_VID_CLR_TEMP,
                                         MLM_MENU_KEY_HELP_TIP_PICTURE_CLR_TEMP,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_clr_tmp);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vga,
                                         MLM_MENU_KEY_VGA,
                                         MLM_MENU_KEY_HELP_TIP_TV_SETTING_HV_POS,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_vga);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vga_auto,
                                         MLM_MENU_KEY_VGA_AUTO,
                                         MLM_MENU_KEY_HELP_TIP_TV_SETTING_AUTO_SYNC,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_vga_auto);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_date,
                                         MLM_MENU_KEY_TIME_MODE_CURRENT_TIME,
                                         MLM_MENU_KEY_HELP_TIP_TV_SETTING_CRNT_TIME,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_date);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_adv_scan_rng,
                                         MLM_MENU_KEY_ATSC_ASR,
                                         MLM_MENU_KEY_TAB_HELP_PART_CH_SEARCH,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_adv_scan_rng);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_adv_scan_sgl,
                                         MLM_MENU_KEY_ATSC_ASS,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_adv_scan_sgl);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_FAV_LST
    /* create Favorite List subpage */
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_ch_fav,
                                         MLM_MENU_KEY_CH_FAV,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_ch_fav);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

   i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_cap_stl,
                                        MLM_MENU_KEY_CC_STL,
                                        MLM_MENU_KEY_EMPTY,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_page_cap_stl);

    MENU_LOG_ON_FAIL(i4_ret);

    /* create Program Block subpage */
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_prg_bk,
                                         MLM_MENU_KEY_PRG_BK,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_prg_bk);
    MENU_LOG_ON_FAIL(i4_ret);
    /* create USA TV subpage */
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vchip_us_tv,
                                         MLM_MENU_KEY_VCHIP_US_TV,
                                         MLM_MENU_KEY_HELP_TIP_PARENT_US_TV,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_vchip_us_tv);
    MENU_LOG_ON_FAIL(i4_ret);

    /* create USA Movie subpage */
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vchip_us_movie,
                                         MLM_MENU_KEY_VCHIP_US_MOVIE,
                                         MLM_MENU_KEY_HELP_TIP_PARENT_US_MOVIE,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_vchip_us_movie);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vchip_ca_en,
                                         MLM_MENU_KEY_VCHIP_CA_EN,
                                         MLM_MENU_KEY_HELP_TIP_PARENT_CA_EN,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_vchip_ca_en);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vchip_ca_fr,
                                         MLM_MENU_KEY_VCHIP_CA_FR,
                                         MLM_MENU_KEY_HELP_TIP_PARENT_CA_FR,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_vchip_ca_fr);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_OP_VCHIP_ENABLE
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_op_vchip,
                                         MLM_MENU_KEY_OP_VCHIP,
                                         MLM_MENU_KEY_HELP_TIP_PARENT_OP_VCHIP,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_op_vchip_rgn);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_op_vchip_drrt,
                                         MLM_MENU_KEY_OP_VCHIP,
                                         MLM_MENU_KEY_HELP_TIP_PARENT_OP_VCHIP,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_op_vchip_drrt);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_ch_bk,
                                         MLM_MENU_KEY_CH_BK,
                                         MLM_MENU_KEY_HELP_TIP_PARENT_CH_BLOCK,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_ch_bk);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_chg_pwd,
                                         MLM_MENU_KEY_CHG_PWD,
                                         MLM_MENU_KEY_HELP_TIP_PARENT_CH_PASSWD,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_chg_pwd);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_g_menu_page_chg_pwd = ui4_page_chg_pwd;

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_date_time,
                                         MLM_MENU_KEY_TV_SETTINGS_DATE_TIME,
                                         MLM_MENU_KEY_HELP_TIP_TV_SETTING_DATETIME,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_date_time);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef COMMON_IMG_CLNR_ENABLE
   i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_img_clnr,
                                         MLM_MENU_KEY_IMG_CLNR,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_img_clnr);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = menu_pm_page_create(&t_g_menu_page_pic_mode_edit,
                                    NULL,
                                    &ui4_g_menu_custom_page_pic_mode_edit);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_pic_mode_edit,
                                        MLM_MENU_KEY_PIC_MODE_EDIT_ITEM,
                                        MLM_MENU_KEY_VID_HELP_PROFESSIONAL_PICTURE_NO_GAMMA,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_g_menu_custom_page_pic_mode_edit);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_page_lock_pic_lb2,
                                    NULL,
                                    &ui4_g_menu_custom_page_lock_pic_lb2);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_page_color_calibration,
                                    NULL,
                                    &ui4_g_menu_custom_page_color_calibration);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_subpage_item(&t_menu_item_color_calibration,
                                        MLM_MENU_KEY_COLOR_CALIBRATION_ITEM,
                                        MLM_MENU_KEY_COLOR_CALIBRATION_HELP,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_g_menu_custom_page_color_calibration);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_cal_dn_sdr,
                                        MLM_MENU_KEY_VID_DN_SDR,
                                        MLM_MENU_KEY_VID_DN_SDR_TIP,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_g_menu_custom_page_pic_quality);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_cal_dn_hdr,
                                        MLM_MENU_KEY_VID_DN_HDR,
                                        MLM_MENU_KEY_VID_DN_HDR_TIP,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_g_menu_custom_page_pic_quality);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_cal_dn_hlg,
                                        MLM_MENU_KEY_VID_DN_HLG,
                                        MLM_MENU_KEY_VID_DN_HLG_TIP,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_g_menu_custom_page_pic_quality);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_cal_dn_dv,
                                        MLM_MENU_KEY_VID_DN_DV,
                                        MLM_MENU_KEY_VID_DN_DV_TIP,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_g_menu_custom_page_pic_quality);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_more_item(&t_menu_item_page_vid_more,
                                         MLM_MENU_KEY_VID_MORE,
                                         MLM_MENU_KEY_HELP_VID_MORE,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_vid_more);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_more_sz_pos,
                                        MLM_MENU_KEY_VID_SZ_POS,
                                        MLM_MENU_KEY_HELP_SZ_POS,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_page_vid_more_sz_pos);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_more_size_pos,
                                        MLM_MENU_KEY_VID_PAGE_SIZE_POSITION,
                                        MLM_MENU_KEY_HELP_PAGE_SIZE_POSITION,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_page_vid_more_size_position);
    MENU_LOG_ON_FAIL(i4_ret);
#if 0
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_more_clr_tmp,
                                        MLM_MENU_KEY_VID_CLR_TEMP,
                                        MLM_MENU_KEY_HELP_CLR_TMP,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_page_vid_more_clr_tmp);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    UINT16 ui2_item_help_txt = MLM_MENU_KEY_EMPTY;
    if (_is_support_3D())
    {
        ui2_item_help_txt = MLM_MENU_KEY_HELP_ADV_PIC;
    }
    else
    {
#if 0    //CID:4491363
    #ifdef APP_MJC_SUPPORT
        if (_is_mjc_mode_hidden())
        {
            ui2_item_help_txt = MLM_MENU_KEY_HELP_ADV_PIC_NO_SMOOTH_MOTION;
        }
        else
        {
            ui2_item_help_txt = MLM_MENU_KEY_HELP_ADV_PIC_NO_SMOOTH_MOTION;
        }
    #else
        ui2_item_help_txt = MLM_MENU_KEY_HELP_ADV_PIC_NO_SMOOTH_MOTION;
    #endif
#endif
    ui2_item_help_txt = MLM_MENU_KEY_HELP_ADV_PIC_NO_SMOOTH_MOTION;
    }

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_more_adv_pic,
                                            MLM_MENU_KEY_VID_ADVANCED_PICTURE,
                                            ui2_item_help_txt,
                                            MLM_MENU_KEY_EMPTY,
                                            ui4_page_vid_more_adv_pic);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_motion_control,
                                            MLM_MENU_KEY_VID_MOTION_CONTROL,
                                            MLM_MENU_KEY_VID_MOTION_CONTROL_TIP,
                                            MLM_MENU_KEY_EMPTY,
                                            ui4_page_vid_motion_control);
    MENU_LOG_ON_FAIL(i4_ret);


#if 1 // 2020-12-07.Spec has been updated to rename all instances to Gaming instead of V-Gaming or ProGaming
    ui2_item_txt = MLM_MENU_KEY_VID_GAMEING_ENGINE;
#else
    if(_is_rename_v_gaming_engine())
    {
        ui2_item_txt = MLM_MENU_KEY_VID_V_GAMEING_ENGINE;
    }
    else
    {
        ui2_item_txt = MLM_MENU_KEY_VID_PROGAMEING_ENGINE;
    }
#endif
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_progame_engine,
                                            ui2_item_txt,
                                            MLM_MENU_KEY_VID_PROGAMEING_ENGINE_TIP,
                                            MLM_MENU_KEY_EMPTY,
                                            ui4_page_vid_progame_engine);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_cal_pattern_test,
                                            MLM_MENU_KEY_VID_CALI_TESTS,
                                            MLM_MENU_KEY_VID_CALI_TESTS,
                                            MLM_MENU_KEY_EMPTY,
                                            ui4_page_vid_cal_pattern_test);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_vid_oled_panel,
                                            MLM_MENU_KEY_VID_OLED_PANEL,
                                            MLM_MENU_KEY_VID_OLED_PANEL_TIP,
                                            MLM_MENU_KEY_EMPTY,
                                            ui4_page_vid_oled_panel);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_eq_settings,
                                         MLM_MENU_KEY_AUD_EQ_SET,
                                         MLM_MENU_KEY_TAB_HELP_EQUALIZER,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_eq_bands_setting);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_g_menu_common_item_page_aud_adv,
                                        MLM_MENU_KEY_AUD_ADV ,
                                        MLM_MENU_KEY_TAB_HELP_AUD_ADV,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_page_aud_adv);
    MENU_LOG_ON_FAIL(i4_ret);

#if 0
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_clr_tmp_reset_pm,
                                        MLM_MENU_KEY_ITEM_CLR_TMP_RESET,
                                        MLM_MENU_KEY_HELP_CLR_TMP_RESET,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_page_clr_tmp_reset_pm);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_channels ,
                                        MLM_MENU_KEY_MENU_TUNER_SET_TITLE,
                                        MLM_MENU_KEY_HELP_TUNER_SET,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_g_menu_page_channels);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_masterlist,
                                        MLM_MENU_KEY_MASTERLIST,
                                        MLM_MENU_KEY_HELP_TIP_TV_SETTING_CH_EDIT,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_page_masterlist);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_ch_edit,
                                         MLM_MENU_KEY_CHANNEL_NAME_EDIT,
                                         MLM_MENU_KEY_HELP_TIP_TV_SETTING_CH_NAME_EDIT,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_ch_edit);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_device_page_device_setting,
                                         MLM_MENU_KEY_HELP_DEVICE_SETUP,
                                         MLM_MENU_KEY_TV_SETTING_DEVICE_SETUP_HELP,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_device_setting);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_setup_par_ctrl,
                                         MLM_MENU_KEY_PAR_CTR,
                                         MLM_MENU_KEY_HELP_PAR_CTR,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_par);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_help_sys_info_and_reset,
                                         MLM_MENU_KEY_MAIN_MENU_SYS_INFO_AND_RESET,
                                         MLM_MENU_KEY_MAIN_MENU_SYS_INFO_AND_RESET_HELP,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_help_sys_info_and_reset);
    MENU_LOG_ON_FAIL(i4_ret);

    //color tuner
    i4_ret = menu_page_tree_subpage_item(&t_g_menu_custom_item_color_tuner,
                                         MLM_MENU_KEY_COLOR_TUNER_TITLE,
                                         MLM_MENU_KEY_MENU_ITEM_HELP_COLOR_TUNER,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_custom_page_pic_quality);
    MENU_LOG_ON_FAIL(i4_ret);

    //white balance tuner
    i4_ret = menu_page_tree_subpage_item(&t_g_menu_custom_item_white_balance_tuner,
                                         MLM_MENU_KEY_VID_WB_TUNER,
                                         MLM_MENU_KEY_MENU_ITEM_HELP_COLOR_TUNER,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_white_balance_tuner_page);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Reduce noise subpage */
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_reduce_noise,
                                        MLM_MENU_KEY_SUB_REDUCE_NOISE,
                                        MLM_MENU_KEY_HELP_REDUCE_NOISE,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_page_reduce_noise);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_2K12_RETAIL_DEMO_MODE
   // t_menu_item_page_clear_memory.u.t_subpage.b_dont_hide_main_menu = TRUE;

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_help_demo_mode,
                                         MLM_MENU_KEY_DEMO_MODE,
                                         MLM_MENU_KEY_DEMO_MODE_HELP,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_help_demo_mode);
    MENU_CHK_FAIL(i4_ret);
#endif

    /*----------------------------------------------------------------*/
    /*                        System Reset. Page                      */
    /*----------------------------------------------------------------*/
    i4_ret = menu_pm_page_create(&t_g_menu_common_page_ver_info,
                                 NULL,
                                 &ui4_page_ver_info);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_g_menu_page_ver_info = ui4_page_ver_info;

    i4_ret = menu_page_tree_subpage_item(&t_g_menu_item_page_check_info,
                                         MLM_MENU_KEY_SERVICE_CHECK_ITEM,
                                         MLM_MENU_KEY_CHECK_FOR_UPDATES_HELP_TEXT,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_page_service_check_dialog);
#if SUPPORT_MENU_CODE
    /*support code*/
    i4_ret = menu_page_tree_action_item(&t_g_menu_item_page_support_code,
                                       MLM_MENU_KEY_SUPPORT_CODE,
                                       MLM_MENU_KEY_SUPPORT_CODE_HELP_TEXT,
                                       MLM_MENU_KEY_EMPTY ,
                                       _action_support_code);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
#ifndef APP_EMANUAL_SP6_SUPPORT
    if (a_cfg_custom_get_wifi_remote_support())
    {
        i4_ret = menu_page_tree_subpage_item(&t_g_menu_item_page_ver_info,
                                             MLM_MENU_KEY_SYSTEM_INFO,
                                             MLM_MENU_KEY_HELP_TIP_SYSTEM_INFO,
                                             MLM_MENU_KEY_EMPTY,
                                             ui4_page_ver_info);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
#endif
    {
        i4_ret = menu_page_tree_subpage_item(&t_g_menu_item_page_ver_info,
                                             MLM_MENU_KEY_SYSTEM_INFO,
                                             MLM_MENU_KEY_HELP_TIP_SYSTEM_INFO_NO_REMOTE,
                                             MLM_MENU_KEY_EMPTY,
                                             ui4_page_ver_info);
        MENU_LOG_ON_FAIL(i4_ret);
    }

#ifdef APP_EMANUAL_SP6_SUPPORT
        i4_ret = menu_pm_page_create(&t_g_menu_common_page_ver_info_mc,
                                     NULL,
                                     &ui4_g_menu_page_mc_ver);
        MENU_LOG_ON_FAIL(i4_ret);
#endif

    /*----------------------------------------------------------------*/
    /*                       wizard mode. Page                        */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_start_wizard,
                                         MLM_MENU_KEY_START_WZD,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_start_wizard);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                        picture setting Reset. Page             */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_picture_reset,
                                         MLM_MENU_KEY_VID_RESET,
                                         MLM_MENU_KEY_HELP_VID_RESET,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_picture_reset);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                        picture mode Reset. Page                */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_pic_mode_reset,
                                         MLM_MENU_KEY_VID_RESET_PIC_MOD,
                                         MLM_MENU_KEY_HELP_TIP_PICTURE_RESET_PIC,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_pic_mode_reset);
    MENU_LOG_ON_FAIL(i4_ret);

   /*----------------------------------------------------------------*/
    /*                           More Audio, Device Setup page                         */
    /*----------------------------------------------------------------*/
    /*----------------------------------------------------------------*/
    /*                        audio Reset. Page                       */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_subpage_item(&t_g_menu_custom_item_page_bass_treble,
                                         MLM_MENU_KEY_AUD_BLASS_AND_TREBLE,
                                         MLM_MENU_KEY_HELP_TIP_AUDIO_BASS_TREBLE,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_bass_treble);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_audio_reset,
                                         MLM_MENU_KEY_RD,
                                         MLM_MENU_KEY_HELP_TIP_AUDIO_RESET_FAC,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_audio_reset);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_del_aud_mode,
                                         MLM_MENU_KEY_TITLE_DELETE_AUD_MODE,
                                         MLM_MENU_KEY_HELP_TIP_DELETE_AUD_MODE,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_del_aud_mode);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_action_item(&t_menu_item_setup_audio_mode,
                                        MLM_MENU_KEY_SETUP_AUDIO_MODE,
                                        MLM_MENU_KEY_SETUP_AUDIO_MODE_DES,
                                        MLM_MENU_KEY_EMPTY ,
                                        _go_to_dev_setup_audio_mode_setup);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_channel_lock_reset,
                                         MLM_MENU_KEY_RESET_LOCK,
                                         MLM_MENU_KEY_HELP_TIP_PARENT_RESET_PARENTAL,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_channel_lock_reset);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_reset_pub,
                                         MLM_MENU_KEY_RESET_ALL_SETTINGS,
                                         MLM_MENU_KEY_HELP_TIP_SYSTEM_RESET_ALL,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_reset_pub);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_reset_pri,
                                         MLM_MENU_KEY_RESET_PRI,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_reset_pri);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_reset_fac,
                                         MLM_MENU_KEY_RESET_FAC,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_reset_fac);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_inp_bk,
                                         MLM_MENU_KEY_INP_BK,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_inp_bk);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_inp_sk,
                                         MLM_MENU_KEY_INP_SK,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_inp_sk);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_hv_pos,
                                         MLM_MENU_KEY_H_V_POS,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_hv_pos);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_auto_phase,
                                         MLM_MENU_KEY_VID_AUTO_PHASE,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_auto_phase);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_inp_edit,
                                         MLM_MENU_KEY_INPUT_EDIT,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_inp_edit);
    MENU_LOG_ON_FAIL(i4_ret);

    /* create Picture subpage */
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_tv_pic,
                                         MLM_MENU_KEY_MAIN_MENU_PIC_SETTING,
                                         MLM_MENU_KEY_VID_PIC_MODE,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_g_menu_page_vid);
    MENU_CHK_FAIL(i4_ret);

    /* Create Audio subpage */
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_tv_aud,
                                         MLM_MENU_KEY_AUD,
                                         MLM_MENU_KEY_MENU_AUDIO_SETTINGS,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_aud);
    MENU_CHK_FAIL(i4_ret);


    /*----------------------------------------------------------------*/
    /*                           Sleep Timer Page                     */
    /*----------------------------------------------------------------*/
    /* Sleep Timer */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_slp,
                                &t_g_menu_common_item_misc_auto_sleep,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Auto Power Off */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_slp,
                                &t_g_menu_common_item_dpms,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_slp,
                                              ui2_item_id,
                                              _is_auto_power_off_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Screen Saver */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_slp,
                                &t_g_menu_common_item_scrn_saver,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_slp,
                                          ui2_item_id,
                                          _is_scrn_saver_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Blank Screen Now*/
    i4_ret = menu_page_tree_add(ui4_g_menu_page_slp,
                                &t_g_menu_common_item_blank_scrn_now,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_slp,
                                          ui2_item_id,
                                          _is_blank_scrn_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                           Video Page                           */
    /*----------------------------------------------------------------*/

    /*Picture Mode*/
    i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                &t_g_menu_common_item_vid_pic_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                            ui2_item_id,
                                            is_3d_playing);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_pic_mode_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    //note: 5583 D series HD model without V-Gaming/Progaming Engine, so need to move GLL item from Gaming Engine to Advance Picture subitem
    if(a_cfg_cust_is_gll_support_and_gaming_engine_no_support() == FALSE)
    {
        /*Gaming Mode*/
        i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                    &t_menu_item_page_vid_progame_engine,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                    ui2_item_id,
                                    _is_item_progaming_engine_enable);

        MENU_LOG_ON_FAIL(i4_ret);
    }

    /*Ambient Light Sensor-->rename as Auto Brightness Control*/
    if(a_cfg_cust_drv_is_lightsensor_support() == TRUE)
    {
        i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                    &t_g_menu_custom_item_vid_lit_sns,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);

#ifdef NEVER
        i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_vid,
                                                ui2_item_id,
                                                _is_smart_cast_app_source);
        MENU_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */

        i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                                ui2_item_id,
                                                _is_abc_enable);
        MENU_LOG_ON_FAIL(i4_ret);

    }

    /*Backlight*/
    if(a_cfg_cust_oled_support() == TRUE)
    {
        i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                    &t_g_menu_common_item_vid_oled_luminance,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);

    }
    else
    {
        i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                    &t_g_menu_common_item_vid_back_light,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_hdr_content);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_vid_backlight_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

#if 1//ndef MT5583_MODEL  // MVD-1979
    /*Tone Mapping */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                &t_g_menu_common_item_vid_tone_mapping,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_sdr_content);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_vid_backlight_enabled);
    MENU_LOG_ON_FAIL(i4_ret);
#endif


    /*Brightness*/
    i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                &t_g_menu_common_item_vid_bri,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    #ifdef APP_MENU_MMP_COEXIST
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_pic_item_enabled);
    MENU_LOG_ON_FAIL(i4_ret);
    #else
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_cust_pic_mode_pq_enable);
    MENU_LOG_ON_FAIL(i4_ret);
    #endif

    /*Contrast*/
    i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                &t_g_menu_common_item_vid_cnt,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                            ui2_item_id,
                                            _is_item_contrast_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Color*/
    i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                &t_g_menu_common_item_vid_sat,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_item_color_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Tint*/
    i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                &t_g_menu_common_item_vid_hue,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_item_tint_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Sharpness*/
    i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                &t_g_menu_common_item_vid_shp,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    #ifdef APP_MENU_MMP_COEXIST
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_item_sharpness_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    #else
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_cust_pic_mode_pq_enable);
    MENU_LOG_ON_FAIL(i4_ret);
    #endif
#ifdef NEVER
    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_vid,
                                          ui2_item_id,
                                          _is_smart_cast_app_source);
    MENU_CHK_FAIL(i4_ret);
#endif /* NEVER */

    i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                            &t_g_menu_common_item_vid_clr_tmp_mode,
                            &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_MMP_COEXIST
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                        ui2_item_id,
                                        _is_pic_item_enabled);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                &t_g_menu_custom_item_aspect_ratio,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    MENU_DEBUG_ASPECT_RATIO( DBG_LOG_PRINT(("[MENU][ASPECT]{%s,%d} ui2_item_id:%d \n", __FUNCTION__, __LINE__, ui2_item_id )); );
#if(MENU_SUPPORT_HOT_KEY_ASPECT_RATIO)
    g_menu_u16_item_id_PICTURE_ASPECT_RATIO = ui2_item_id;
#endif


    /*More Picture*/
   i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                               &t_menu_item_page_vid_more_adv_pic,
                               &ui2_item_id);
   MENU_LOG_ON_FAIL(i4_ret);

   i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_vid,
                                         ui2_item_id,
                                         _is_cust_pic_mode_pq_enable);
   MENU_LOG_ON_FAIL(i4_ret);

    MENU_LOG_ON_FAIL(_init_tree_input_settings(ui4_g_menu_page_vid));


    i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                &t_menu_item_pic_mode_edit,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef NEVER
    i4_ret = menu_page_tree_add(ui4_g_menu_page_vid,
                                &t_menu_item_color_calibration,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */


    /*Professional Picture*/
    i4_ret = menu_pm_page_create(&t_g_menu_page_create_pic_mode,
                                    NULL,
                                    &ui4_g_menu_custom_page_create_pic_mode);
    MENU_LOG_ON_FAIL(i4_ret);



    i4_ret = menu_pm_page_create(&t_g_menu_page_lock_pic_mode,
                                    NULL,
                                    &ui4_g_menu_custom_page_lock_pic_mode);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_pm_page_create(&t_g_menu_page_unlock_pic_mode,
                                    NULL,
                                    &ui4_g_menu_custom_page_unlock_pic_mode);
    MENU_LOG_ON_FAIL(i4_ret);


#ifdef APP_PIP_POP_CTRL
    i4_ret = menu_common_create_page_pip_inp_src(&ui4_page_pip_source);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_pip_source,
                                         MLM_MENU_KEY_INPUT_SOURCE,
                                         MLM_MENU_KEY_INPUT_SOURCE,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_pip_source);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_action_item(&t_menu_item_pip_swap,
                                        MLM_MENU_KEY_SWAP,
                                        MLM_MENU_KEY_SWAP,
                                        MLM_MENU_KEY_EMPTY,
                                        _pip_swap);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_pip,
                                         MLM_MENU_KEY_PIP_MODE_PIP,
                                         MLM_MENU_KEY_PIP_MODE_PIP,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_pip);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_pip,
                                &t_g_menu_common_item_pip_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_pip,
                                &t_menu_item_page_pip_source,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_pip,
                                            ui2_item_id,
                                            _is_pip_enbale);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_pip,
                                &t_menu_item_pip_swap,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_pip,
                                            ui2_item_id,
                                            _is_pip_enbale);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_pip,
                                &t_g_menu_common_item_pip_pos_ex,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_pip,
                                            ui2_item_id,
                                            _is_pip_enbale);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_pip,
                                &t_g_menu_common_item_pip_size_ex,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_pip,
                                            ui2_item_id,
                                            _is_pip_enbale);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_pip,
                                &t_g_menu_common_item_pip_src_ex,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_pip,
                                            ui2_item_id,
                                            _is_pip_enbale);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_g_menu_page_pip = ui4_page_pip;

#endif

    /*----------------------------------------------------------------*/
    /*                           Video Professional Picture Page                            */
    /*----------------------------------------------------------------*/

    //color tuenr
    i4_ret = menu_page_tree_add(ui4_g_menu_custom_page_pic_mode_edit,
                                   &t_g_menu_custom_item_color_tuner,
                                   &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_custom_page_pic_mode_edit,
                                          ui2_item_id,
                                          a_menu_is_color_tuner_enable);
    MENU_LOG_ON_FAIL(i4_ret);


    //white balance tuner
    i4_ret = menu_page_tree_add(ui4_g_menu_custom_page_pic_mode_edit,
                                   &t_g_menu_custom_item_white_balance_tuner,
                                   &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    /*----------------------------------------------------------------*/
    /*                           Video More Page                            */
    /*----------------------------------------------------------------*/

    /*Size & Position*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more,
                                &t_menu_item_page_vid_more_sz_pos,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more,
                                            ui2_item_id,
                                            _is_vid_more_sz_pos_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Color Temperature*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more,
                                &t_menu_item_page_vid_more_clr_tmp,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    #ifdef APP_MENU_MMP_COEXIST
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more,
                                            ui2_item_id,
                                            _is_pic_item_enabled);
    MENU_LOG_ON_FAIL(i4_ret);
    #endif

    /*More Picture*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more,
                                &t_menu_item_page_vid_more_adv_pic,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more,
                                          ui2_item_id,
                                          _is_adv_vid_graphic_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /*VGA not support DCR/Smart Dimming,but enable Lightsensor item */
    /*Ambient Light Sensor-->rename as Auto Brightness Control*/
    if(a_cfg_cust_drv_is_lightsensor_support() == TRUE)
    {
        i4_ret = menu_page_tree_add(ui4_page_vid_more,
                                    &t_g_menu_custom_item_vid_lit_sns,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more,
                                                ui2_item_id,
                                                _is_vga_hidden);
        MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_MENU_MMP_COEXIST
        i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more,
                                                ui2_item_id,
                                                _is_pic_item_enabled);
        MENU_LOG_ON_FAIL(i4_ret);
    #endif
    }

    /*Reset Picture Mode*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more,
                                &t_menu_item_page_pic_mode_reset,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                           Video More Page->  Size & Position page                          */
    /*----------------------------------------------------------------*/

    /* vga auto adjust */
    i4_ret = menu_page_tree_add(ui4_page_vid_more_sz_pos,
                                              &t_menu_item_page_vga_auto,
                                              &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_sz_pos,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_sz_pos,
                                               ui2_item_id,
                                               _is_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /* VGA pos_h */
    i4_ret = menu_page_tree_add(ui4_page_vid_more_sz_pos,
                                &t_g_menu_common_item_vga_pos_h,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_sz_pos,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_sz_pos,
                                          ui2_item_id,
                                          _is_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /* vga pos_v */
    i4_ret = menu_page_tree_add(ui4_page_vid_more_sz_pos,
                                &t_g_menu_common_item_vga_pos_v,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_sz_pos,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_sz_pos,
                                                ui2_item_id,
                                                _is_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_HV_POS_MODIFICATION_SUPPORT

    /* video Horiz.Position*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more_sz_pos,
                                &t_g_menu_common_item_vid_pos_h,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_sz_pos,
                                                ui2_item_id,
                                                _is_adv_vid_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_sz_pos,
                                            ui2_item_id,
                                            _is_h_pos_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    /* video Vertical.Position*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more_sz_pos,
                                &t_g_menu_common_item_vid_pos_v,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_sz_pos,
                                                ui2_item_id,
                                                _is_adv_vid_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_sz_pos,
                                            ui2_item_id,
                                            _is_v_pos_enabled);
     MENU_LOG_ON_FAIL(i4_ret);
    #endif

    /* Horizontal Size */
    i4_ret = menu_page_tree_add(ui4_page_vid_more_sz_pos,
                                &t_g_menu_custom_item_vid_size_h,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_sz_pos,
                                          ui2_item_id,
                                          _is_adv_vid_hidden);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_sz_pos,
                                            ui2_item_id,
                                            /*_is_adv_vid_enable*/
                                            _is_h_pos_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_vid_more_sz_pos,
                                &t_g_menu_common_item_vga_clock,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_sz_pos,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_sz_pos,
                                          ui2_item_id,
                                          _is_vga_hidden);
    MENU_CHK_FAIL(i4_ret);

    /* Vertical Size */
    i4_ret = menu_page_tree_add(ui4_page_vid_more_sz_pos,
                                &t_g_menu_custom_item_vid_size_v,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_sz_pos,
                                                ui2_item_id,
                                                _is_adv_vid_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_sz_pos,
                                            ui2_item_id,
                                            _is_adv_vid_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    /* vga phase */
    i4_ret = menu_page_tree_add(ui4_page_vid_more_sz_pos,
                                   &t_g_menu_common_item_vga_phase,
                                   &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_sz_pos,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_sz_pos,
                                                ui2_item_id,
                                                _is_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*    Video More Page->  Color Tempeature page                    */
    /*----------------------------------------------------------------*/

    /*-------------------------------------------------------------------*/
    /*            Video More Page->  More Picture page               */
    /*-------------------------------------------------------------------*/
#ifdef NEVER
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_g_menu_common_item_vid_clr_tmp_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_MENU_MMP_COEXIST
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _is_pic_item_enabled);
    MENU_LOG_ON_FAIL(i4_ret);
    #endif
#endif /* NEVER */

    /*Contrast Enhancement - > rename to Black Detail*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_g_menu_common_item_vid_contrast_en,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                           ui2_item_id,
                                           _is_contrast_en_enable);
    MENU_LOG_ON_FAIL(i4_ret);

#ifndef MT5583_MODEL
    /*Super Resolution*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_g_menu_common_item_vid_super_resolution,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _is_supper_resolution_enable);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /*Edge Enhancement*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_g_menu_common_item_vid_edge_enhancement,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _is_edge_enhancement_enable);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Local Contrast*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_g_menu_common_item_vid_local_contrast,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _is_local_contrast_enable);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef NEVER
     /*Adaptive Luma--->rename as Black Detail*/
     i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                 &t_g_menu_common_item_vid_alc,
                                 &ui2_item_id);
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_adv_pic,
                                             ui2_item_id,
                                             _is_adv_vid_graphic_hide);
     MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                             ui2_item_id,
                                             _is_adv_vid_alc_enable);
     MENU_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */

    if(a_cfg_cust_oled_support() == FALSE)
    {
          /*Smart Dimming && rename as Active LED Zones*/
          i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                      &t_g_menu_common_item_local_dimming,
                                      &ui2_item_id);
          MENU_CHK_FAIL(i4_ret);

          i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_adv_pic,
                                                  ui2_item_id,
                                                  _is_local_dimming_hide);
          MENU_LOG_ON_FAIL(i4_ret);

          i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                                  ui2_item_id,
                                                  _is_adv_vid_local_dimming_enable);
          MENU_LOG_ON_FAIL(i4_ret);
    }

    if(a_cfg_cust_oled_support() == TRUE)
    {
        /* Peak Luminance*/
        i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                    &t_g_menu_common_item_vid_peak_luminance,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);
      #if 0
        i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                                ui2_item_id,
                                                _is_adv_vid_peak_luminance_enable);
        MENU_LOG_ON_FAIL(i4_ret);
      #endif
    }


    /*  Motion Control */
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_menu_item_page_vid_motion_control,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _is_motion_control_hide);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef NEVER
    /* Reduce Blur && Clear Action */
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_g_menu_common_item_vid_blur,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _is_adv_vid_blur_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _is_adv_vid_blur_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    if (a_cfg_cust_get_support_clear_aciton() == TRUE)
    {
        i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                    &t_g_menu_common_item_vid_clear_action,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_adv_pic,
                                                ui2_item_id,
                                                _is_adv_vid_clear_action_hide);

        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif /* NEVER */

    /* Reduce Noise */
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_menu_item_page_reduce_noise,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef NEVER
    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _is_smart_cast_app_source);

    MENU_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */


    //note: 5583 D series HD model without V-Gaming/Progaming Engine, so need to move GLL item from Gaming Engine to Advance Picture subitem
    if(a_cfg_cust_is_gll_support_and_gaming_engine_no_support() == TRUE)
    {
        /*Game low latency*/
        i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                    &t_g_menu_common_item_vid_game_low_latency,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                    ui2_item_id,
                                    _is_item_game_low_latency_enable);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /*Film Mode*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_g_menu_common_item_vid_di_film_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef NEVER
    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _is_adv_vid_nr_hidden);
    MENU_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _is_film_mode_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    //gamma
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                   &t_g_menu_custom_item_gamma,
                                   &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                          ui2_item_id,
                                          _is_item_gamma_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _is_item_gamma_hide);
    MENU_LOG_ON_FAIL(i4_ret);


#ifdef NEVER
    /* 3D */
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_g_menu_item_page_vid_3d_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _vid_more_adv_3d_hidden);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                            ui2_item_id,
                                            _vid_more_adv_3d_enable);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_3D_BRIGHTNESS_BOOST
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_g_menu_item_3d_brightness_boost,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                        ui2_item_id,
                                        a_tv_custom_is_3D_mode_playing);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
#endif /* NEVER */

    /* Enhanced Viewing Angle */
    if( a_cfg_cust_en_view_angle_support() )
    {
        if( FALSE == a_cfg_cust_en_view_angle_Is_Panel_Support_But_UI_Not_Support() ) // Should disable UI
        {
            i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                           &t_g_menu_common_item_vid_en_view_angle,
                                           &ui2_item_id);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_adv_pic,
                                           ui2_item_id,
                                           _vid_en_view_angle_enable);
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Color Calibration ex*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_menu_item_color_calibration,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef NEVER
    /* Color Calibration test*/
    i4_ret = menu_page_tree_add(ui4_page_vid_more_adv_pic,
                                &t_menu_item_page_vid_cal_pattern_test,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */

    /*-------------------------------------------------------------------*/
    /*            Calibration test  page                              */
    /*-------------------------------------------------------------------*/
    i4_ret = menu_page_tree_add(ui4_page_vid_cal_pattern_test,
                                &t_menu_item_page_vid_cal_dn_sdr,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_vid_cal_pattern_test,
                                &t_menu_item_page_vid_cal_dn_hdr,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_vid_cal_pattern_test,
                                &t_menu_item_page_vid_cal_dn_hlg,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_vid_cal_pattern_test,
                                &t_menu_item_page_vid_cal_dn_dv,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    /*-------------------------------------------------------------------*/
    /*            Motion control  page                                      */
    /*-------------------------------------------------------------------*/
#ifdef APP_SUPPPORT_FRC
    /*Judder Reduction*/
    i4_ret = menu_page_tree_add(ui4_page_vid_motion_control,
                                &t_g_menu_common_item_vid_judder_reduction,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_motion_control,
                                        ui2_item_id,
                                        _is_item_judder_reduction_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Motion Blur Reduction*/
    i4_ret = menu_page_tree_add(ui4_page_vid_motion_control,
                                &t_g_menu_common_item_vid_motion_blur_reduction,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_motion_control,
                                        ui2_item_id,
                                        _is_item_motion_control_enable);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

#ifdef NEVER
    /* Variable Refresh Rate*/
    if (a_cfg_cust_is_variable_refresh_rate_support())
    {
        i4_ret = menu_page_tree_add(ui4_page_vid_motion_control,
                                    &t_g_menu_common_item_vid_vss,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif /* NEVER */

    /*Clear Action*/
    //DBG_LOG_PRINT(("[MENU][ClearAction]{%s: %s: %d} a_cfg_cust_get_support_clear_aciton()=>%d\n", __FILE__, __FUNCTION__,__LINE__, a_cfg_cust_get_support_clear_aciton()));
    if ((a_cfg_cust_get_support_clear_aciton() == TRUE)||(a_cfg_cust_oled_support() == TRUE))
    {
        //DBG_LOG_PRINT(("[MENU][ClearAction]{%s: %s: %d} Add item\n", __FILE__, __FUNCTION__,__LINE__));

        i4_ret = menu_page_tree_add(ui4_page_vid_motion_control,
                                    &t_g_menu_common_item_vid_clear_action,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_motion_control,
                                            ui2_item_id,
                                            _is_item_clear_action_enable);
        MENU_LOG_ON_FAIL(i4_ret);
    }

#if 0
    /*-------------------------------------------------------------------*/
    /*            ProGaming Engine page                                      */
    /*-------------------------------------------------------------------*/

    //note: 5583 D series HD model without V-Gaming/Progaming Engine, so need to move GLL item from Gaming Engine to Advance Picture subitem
    if(a_cfg_cust_is_gll_support_and_gaming_engine_no_support() == FALSE)
    {
        /*Game low latency*/
        i4_ret = menu_page_tree_add(ui4_page_vid_progame_engine,
                                    &t_g_menu_common_item_vid_game_low_latency,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_progame_engine,
                                    ui2_item_id,
                                    _is_item_game_low_latency_enable);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Variable Refresh Rate*/
    if (a_cfg_cust_is_variable_refresh_rate_support())
    {
        i4_ret = menu_page_tree_add(ui4_page_vid_progame_engine,
                                    &t_g_menu_common_item_vid_vss,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);
    }

#ifndef MT5583_MODEL
    /* Game HDR*/
    i4_ret = menu_page_tree_add(ui4_page_vid_progame_engine,
                                &t_g_menu_common_item_vid_game_hdr,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_progame_engine,
                                          ui2_item_id,
                                          _is_item_game_hdr_enable);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

#endif
    /*-------------------------------------------------------------------*/
    /*            Reduce Noise page                                      */
    /*-------------------------------------------------------------------*/

    /*Noise Reduction--->rename as Reduce Signal Noise */
    i4_ret = menu_page_tree_add(ui4_page_reduce_noise,
                                &t_g_menu_common_item_vid_dnr,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_reduce_noise,
                                            ui2_item_id,
                                            _is_dnr_mpeg_noise_reduce_enable);
    MENU_LOG_ON_FAIL(i4_ret);
    #ifdef APP_MPEG_NR_SUPPORT
    /* MPEG Noise Reduction---->Reduce Block Noise */
    i4_ret = menu_page_tree_add(ui4_page_reduce_noise,
                                &t_g_menu_common_item_vid_mpeg_nr,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_reduce_noise,
                                            ui2_item_id,
                                            _is_dnr_mpeg_noise_reduce_enable);
    MENU_LOG_ON_FAIL(i4_ret);
    #endif

#ifndef MT5583_MODEL
    /* Contour Smoothing*/
    i4_ret = menu_page_tree_add(ui4_page_reduce_noise,
                                &t_g_menu_common_item_vid_contour_smoothing,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_reduce_noise,
                                            ui2_item_id,
                                            _is_contour_smoothing_enable);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /*----------------------------------------------------------------*/
    /*                   Picture Size & Position Page                 */
    /*----------------------------------------------------------------*/
    /* VGA auto adjust */
    i4_ret = menu_page_tree_add(ui4_page_vid_more_size_position,
                                              &t_menu_item_page_vga_auto,
                                              &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vid_more_size_position,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vid_more_size_position,
                                               ui2_item_id,
                                               _is_new_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_input_ope_list,
                                 NULL,
                                 &ui4_g_page_input);
    MENU_LOG_ON_FAIL(i4_ret);


    /*----------------------------------------------------------------*/
    /*                   Picture Mode Custom Page                     */
    /*----------------------------------------------------------------*/

    i4_ret = menu_page_tree_add(ui4_g_menu_page_pic_custom,
                                &t_g_menu_common_item_vid_bri,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_pic_custom,
                                            ui2_item_id,
                                            _is_pic_mode_custom_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_pic_custom,
                                          ui2_item_id,
                                          _is_bri_con_back_hidden);
    MENU_LOG_ON_FAIL(i4_ret);*/

    i4_ret = menu_page_tree_add(ui4_g_menu_page_pic_custom,
                                &t_g_menu_common_item_vid_cnt,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_pic_custom,
                                            ui2_item_id,
                                            _is_pic_mode_custom_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_pic_custom,
                                          ui2_item_id,
                                          _is_bri_con_back_hidden);
    MENU_LOG_ON_FAIL(i4_ret);*/

    i4_ret = menu_page_tree_add(ui4_g_menu_page_pic_custom,
                                &t_g_menu_common_item_vid_sat,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_pic_custom,
                                            ui2_item_id,
                                            _is_pic_mode_custom_enabled);
    MENU_LOG_ON_FAIL(i4_ret);
    /*i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_pic_custom,
                                          ui2_item_id,
                                          _is_sat_hue_shp_hidden);
    MENU_LOG_ON_FAIL(i4_ret);*/

    i4_ret = menu_page_tree_add(ui4_g_menu_page_pic_custom,
                                &t_g_menu_common_item_vid_hue,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_pic_custom,
                                            ui2_item_id,
                                            _is_pic_mode_custom_enabled);
    MENU_LOG_ON_FAIL(i4_ret);
    /*i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_pic_custom,
                                          ui2_item_id,
                                          _is_sat_hue_shp_hidden);
    MENU_LOG_ON_FAIL(i4_ret);*/

    i4_ret = menu_page_tree_add(ui4_g_menu_page_pic_custom,
                                &t_g_menu_common_item_vid_shp,
                                &ui2_item_id);
     MENU_LOG_ON_FAIL(i4_ret);
     i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_pic_custom,
                                            ui2_item_id,
                                            _is_pic_mode_custom_enabled);
     MENU_LOG_ON_FAIL(i4_ret);
    /*i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_pic_custom,
                                            ui2_item_id,
                                          _is_sat_hue_shp_hidden);
    MENU_LOG_ON_FAIL(i4_ret);*/

    i4_ret = menu_page_tree_add(ui4_g_menu_page_pic_custom,
                                &t_g_menu_common_item_vid_back_light,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_pic_custom,
                                            ui2_item_id,
                                            _is_bri_con_back_hidden);
    MENU_LOG_ON_FAIL(i4_ret);*/

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_pic_custom,
                                            ui2_item_id,
                                            _is_pic_mode_back_light_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_g_menu_page_pic_custom,
                                &t_g_menu_common_item_vid_alc,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_pic_custom,
                                            ui2_item_id,
                                           _is_pic_mode_custom_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_g_menu_page_pic_custom,
                                &t_g_menu_common_item_vid_flesh_tone,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_pic_custom,
                                            ui2_item_id,
                                           _is_pic_mode_custom_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_g_menu_page_pic_custom,
                                &t_menu_item_page_clr_tmp,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_pic_custom,
                                          ui2_item_id,
                                          _is_color_temp_hidden);

    MENU_LOG_ON_FAIL(i4_ret);*/

    i4_ret = menu_page_tree_add(ui4_g_menu_page_pic_custom,
                                &t_g_menu_custom_item_vid_dcr,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_pic_custom,
                                            ui2_item_id,
                                           _is_pic_mode_custom_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_g_menu_page_pic_custom,
                                &t_menu_item_page_pic_mode_reset,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                       system Page                              */
    /*----------------------------------------------------------------*/
    /*create Start Setup Wizard action page*/
    i4_ret = menu_page_tree_action_item(&t_menu_item_start_setup_wizard,
                                        MLM_MENU_KEY_START_WZD,
                                        MLM_MENU_KEY_HELP_TIP_SYSTEM_START_WZD,
                                        MLM_MENU_KEY_EMPTY ,
                                        _go_setup_wizard_pwd);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_sys_reset,
                                         MLM_MENU_KEY_SYSTEM_RESET,
                                         MLM_MENU_KEY_HELP_TIP_SYSTEM_RESET_PIC_AUD,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_sys_reset);
    MENU_LOG_ON_FAIL(i4_ret);
    /*create Reset TV to Factory Defaults subpage*/
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_clear_memory,
                                        MLM_MENU_KEY_RESET_TV_TO_FACTORY_SET,
                                        MLM_MENU_KEY_TAB_HELP_CLEAR_MEMORY,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_g_page_clear_memory_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    /*create Reset tv ad id Defaults subpage*/
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_reset_tv_ad_id,
                                        MLM_MENU_KEY_RESET_TV_AD_ID,
                                        MLM_MENU_KEY_RESET_TV_AD_ID_TIP,
                                        MLM_MENU_KEY_EMPTY,
                                        ui4_page_reset_tv_ad_id_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_oled_screen_refresh_1,
                                         MLM_MENU_KEY_VID_OLED_SCRREN_REFRESH,
                                         MLM_MENU_KEY_VID_OLED_SCRREN_REFRESH_TIP,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_oled_screen_1);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_oled_screen_refresh_2,
                                         MLM_MENU_KEY_VID_OLED_SCRREN_REFRESH,
                                         MLM_MENU_KEY_VID_OLED_SCRREN_REFRESH_TIP,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_oled_screen_2);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_soft_power_cycle,
                                      MLM_MENU_KEY_ITEM_SOFT_POWER_CYCLE,
                                      MLM_MENU_KEY_SOFT_POWER_CYCLE_HELP_TEXT,
                                      MLM_MENU_KEY_EMPTY,
                                      ui4_g_page_service_rst_dialog);
    MENU_CHK_FAIL(i4_ret);

   /*create start setup wizard page*/
    i4_ret = menu_page_tree_add(ui4_page_sys_reset,
                                &t_menu_item_start_setup_wizard,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_sys_reset,
                                &t_menu_item_page_reset_pub,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    /*****  Help page  ********/
    /***************Guide setup page ******************/
    ui4_g_menu_page_sys = ui4_page_sys_info;

    if (a_cfg_custom_get_wifi_remote_support())
    {
       /*create wifi Remote setup page*/
        i4_ret = menu_page_tree_add(ui4_page_sys_info,
                                    &t_menu_item_page_wifi_remote_setup,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = menu_page_tree_add(ui4_page_sys_info,
                                &t_menu_item_page_tuner_setup,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
#ifdef APP_MENU_MMP_COEXIST
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_sys_info,
                                            ui2_item_id,
                                            _is_guide_setup_enabled);
    MENU_CHK_FAIL(i4_ret);
#endif

    if (a_cfg_custom_get_wifi_remote_support())
    {
        i4_ret = menu_page_tree_add(ui4_page_sys_info,
                                    &t_menu_item_page_wifi_device_setup,
                                    &ui2_item_id);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_page_tree_set_auto_enable(ui4_page_sys_info,
                                                ui2_item_id,
                                                _is_device_setup_enabled);
        MENU_CHK_FAIL(i4_ret);
    }

    i4_ret = menu_page_tree_add(ui4_page_sys_info,
                                &t_menu_item_page_network_setup,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);


    i4_ret = menu_page_tree_set_auto_enable(ui4_page_sys_info,
                                                    ui2_item_id,
                                                    _is_network_enabled);
    MENU_CHK_FAIL(i4_ret);


#ifdef APP_NETWORK_WIFI_SUPPORT
#ifdef APP_WAKE_ON_WLAN_ENABLE_UI
    i4_ret = menu_page_tree_add(ui4_page_sys_info,
                                &t_g_menu_custom_item_wake_on_wlan,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_sys_info,
                                            ui2_item_id,
                                            _is_nw_wifi_wol_enable);
    MENU_CHK_FAIL(i4_ret);
#endif
#endif

#ifdef APP_WAKE_ON_LAN_ENABLE_UI
    i4_ret = menu_page_tree_add(ui4_page_sys_info,
                                &t_g_menu_custom_item_wake_on_lan,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_sys_info,
                                            ui2_item_id,
                                            _is_nw_ethernet_setting_enable);
    MENU_CHK_FAIL(i4_ret);
#endif

    /*----------------------------------------------------------------*/
    /*                           Audio Page                           */
    /*----------------------------------------------------------------*/
    /**
    *SB-Sound Bar Settings Title
    */
    MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_aud,
    &t_menu_item_page_tv_aud_sb_settings,&ui2_item_id));

    MENU_LOG_ON_FAIL(menu_page_tree_set_auto_enable_hide(ui4_page_aud,
    ui2_item_id,_nav_cec_sac_sb_setting_show_title,_nav_cec_sac_sb_setting_title_hidden));

    /**
    *SB-EQ Mode
    */
    MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_aud,
    &t_g_menu_common_item_aud_sb_eq_mode,&ui2_item_id));

    MENU_LOG_ON_FAIL(menu_page_tree_set_auto_hide(ui4_page_aud,
    ui2_item_id,_is_auto_eq_mode_hidden));

    /*SB-Bass */
    MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_aud,
    &t_g_menu_common_item_aud_sb_bass,&ui2_item_id));

    MENU_LOG_ON_FAIL(menu_page_tree_set_auto_hide(ui4_page_aud,
    ui2_item_id,_is_auto_sb_bass_hidden));

    /*SB-Treble */
    MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_aud,
    &t_g_menu_common_item_aud_sb_treble,   &ui2_item_id));

    MENU_LOG_ON_FAIL(menu_page_tree_set_auto_hide(ui4_page_aud,
    ui2_item_id,_is_auto_sb_treble_hidden));

    /**
    *SB-Dialogue
    */
    MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_aud,
    &t_g_menu_common_item_aud_dialogue,&ui2_item_id));

#if 1/**MVP-4576
       From Polly -> OK to gray out sound bar Dialogue setting but only when EQ is set to Direct.   For any other EQ (Movie, Music or Game), Dialogue can be adjusted
    **/
        MENU_LOG_ON_FAIL(menu_page_tree_set_auto_enable_hide(ui4_page_aud,
        ui2_item_id, _is_auto_dialogue_enable, _is_auto_dialogue_hidden));
#else
        MENU_LOG_ON_FAIL(menu_page_tree_set_auto_hide(ui4_page_aud_sb_settings,
        ui2_item_id,_is_auto_dialogue_hidden));
#endif
    /**
    *SB-Subwoofer
    */
    MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_aud,
    &t_g_menu_common_item_aud_subwoofer,&ui2_item_id));

    MENU_LOG_ON_FAIL(menu_page_tree_set_auto_hide(ui4_page_aud,
    ui2_item_id,_is_auto_sb_subwoofer_hidden));

    /**
    SB-Night Mode
    */
    MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_aud,
    &t_g_menu_common_item_aud_night_mode,&ui2_item_id));

    MENU_LOG_ON_FAIL(menu_page_tree_set_auto_hide(ui4_page_aud,
    ui2_item_id,_is_auto_night_mode_hidden));

    /**
    *SB-Virtual:X
    */
    MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_aud,
    &t_g_menu_common_item_aud_virtualx,&ui2_item_id));

    MENU_LOG_ON_FAIL(menu_page_tree_set_auto_hide(ui4_page_aud,
    ui2_item_id,_is_auto_virtualx_hidden));

    /**
    SB-Speaker Test
    */
    MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_aud,
    &t_g_menu_common_item_aud_sb_speaker_Test,&ui2_item_id));

    MENU_LOG_ON_FAIL(menu_page_tree_set_auto_hide(ui4_page_aud,
    ui2_item_id,_is_auto_sb_speakertest_hidden));

    /**
    SB-Info
    */
    MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_aud,
    &t_g_menu_common_item_aud_sb_Info,&ui2_item_id));

    MENU_LOG_ON_FAIL(menu_page_tree_set_auto_hide(ui4_page_aud,
    ui2_item_id,_is_auto_sb_info_hidden));

    /**************
    Tv Audio Settings
    ***************/
    MENU_LOG_ON_FAIL(menu_page_tree_add(ui4_page_aud,
    &t_menu_item_page_tv_audio_settings,&ui2_item_id));

    MENU_LOG_ON_FAIL(menu_page_tree_set_auto_enable_hide(ui4_page_aud,
    ui2_item_id,_title_tv_audio_settings_enable,_nav_cec_sac_sb_setting_title_hidden));

    /*TV Speaker*/
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_common_item_aud_speaker,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
#if 0
    /*vol contro display*/
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_common_item_aud_vol_dis,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /*SRS TrueSurround HD*/
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_common_item_aud_surround,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_set_auto_enable_hide(ui4_page_aud,ui2_item_id,
    _is_auto_aud_surround_enable,_is_auto_aud_surround_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /*SRS TruVolume*/
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_common_item_aud_srs_truvolume,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_set_auto_enable_hide(ui4_page_aud,ui2_item_id,
    _is_auto_aud_surround_enable,_is_auto_tur_volume_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Balance*/
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_common_item_aud_balance,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_set_auto_enable_hide(ui4_page_aud, ui2_item_id,
    _is_auto_aud_balance_enable,_is_auto_balance_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Bass */
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_common_item_aud_bass,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable_hide(ui4_page_aud,ui2_item_id,
    _is_auto_bass_enable,_is_auto_bass_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Treble */
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_common_item_aud_treble,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable_hide(ui4_page_aud,ui2_item_id,
    _is_auto_treble_enable,_is_auto_treble_hidden);
    MENU_LOG_ON_FAIL(i4_ret);


    /*Lip Sync*/
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_common_item_aud_latency,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_SB_ENABLE
    /*Volume Control*/
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_common_item_aud_vol_control,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable_hide(ui4_page_aud,ui2_item_id,
    _is_auto_vol_ctrl_enable,_is_auto_vol_ctrl_hidden);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    if(a_cfg_custom_get_spdif_support() == TRUE)  //customer spec . some model not support it
    {
        /*Digital Audio Out*/
        i4_ret = menu_page_tree_add(ui4_page_aud,
                                    &t_g_menu_common_item_aud_spdif,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_page_tree_set_auto_enable(ui4_page_aud,ui2_item_id,
        _is_auto_spdif_enable);
        MENU_LOG_ON_FAIL(i4_ret);

    }

/*spdif delay*/
#ifdef APP_SPDIF_DELAY_SUPPORT

#if 0
        i4_ret = menu_page_tree_add(ui4_page_aud,
                                        &t_g_menu_common_item_aud_spdif_delay,
                                        &ui2_item_id);
        MENU_CHK_FAIL(i4_ret);
#endif

#endif

    /*Analog Audio Out*/
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_custom_item_ana_aud_out,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_aud,
                                          ui2_item_id,
                                          _is_analog_audio_out_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Dialogue Enhancer*/
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_common_item_aud_dia_enhancer,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable_hide(ui4_page_aud,ui2_item_id,
    _is_equalizerdia_enhancer_enable,_is_dia_enhancer_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

#ifndef MT5583_MODEL
    /*earc mode*/
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_g_menu_common_item_aud_earc,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* eq */
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_menu_item_page_eq_settings,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable_hide(ui4_page_aud,ui2_item_id,
    _is_equalizer_enable,_is_equalizer_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Delete Audio Mode*/
    i4_ret = menu_page_tree_add(ui4_page_aud,
                                &t_menu_item_page_del_aud_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable_hide(ui4_page_aud, ui2_item_id,
    _is_del_aud_mode_enabled,_is_del_aud_mode_hidden);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    ui4_g_menu_page_aud = ui4_page_aud;

    if (a_cfg_custom_get_wifi_remote_support())
    {
        /*Audio Device Setup*/
        i4_ret = menu_page_tree_add(ui4_page_aud,
                                    &t_menu_item_setup_audio_mode,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_page_tree_set_auto_enable(ui4_page_aud,
                                    ui2_item_id,
                                    _is_audio_mode_setup_enabled);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /*----------------------------------------------------------------*/
    /*                        Audio->  More Audio  page           */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /*                            TV Page                             */
    /*----------------------------------------------------------------*/
#ifdef APP_MENU_FAV_LST
    i4_ret = menu_page_tree_add(ui4_g_menu_page_tv,
                                &t_menu_item_page_ch_fav,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /* Input source item */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_tv,
                                &t_menu_item_page_inp,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_g_menu_page_tv,
                                &t_menu_item_page_channels,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_tv,
                                            ui2_item_id,
                                            _is_tv_page_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_g_menu_page_tv,
                                &t_g_menu_custom_item_gui_lang,
                                &ui2_item_id);

    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_g_menu_page_tv,
                                &t_menu_item_page_date_time,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_g_menu_page_tv,
                                &t_menu_item_page_pc_setting,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_tv,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                           Closed Caption Page                  */
    /*----------------------------------------------------------------*/
    /* CC On/Off switch  */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_cc,
                                   &t_g_menu_custom_item_cc_enabled,
                                   &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Analog CC */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_cc,
                                &t_g_menu_custom_item_cc_ana,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_cc,
                                            ui2_item_id,
                                            _is_cc_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Digital CC */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_cc,
                                &t_g_menu_custom_item_cc_dig,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_cc,
                                            ui2_item_id,
                                            _is_cc_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Digital CC Style */
    t_menu_item_page_cap_stl.u.t_list_subpage.ui2_msgid_action = MLM_MENU_KEY_EMPTY;
    t_menu_item_page_cap_stl.u.t_list_subpage.ui4_subpage_id = ui4_page_cap_stl;
    t_menu_item_page_cap_stl.ui2_msgid_desc = MLM_MENU_KEY_HELP_TIP_CAPTION_DCC_STYLE;

    i4_ret = menu_page_tree_add(ui4_g_menu_page_cc,
                                &t_menu_item_page_cap_stl,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                           Date&Time Page                       */
    /*----------------------------------------------------------------*/
    /* Time Zone */
    i4_ret = menu_page_tree_add(ui4_page_date_time,
                                &t_g_menu_custom_item_time_zone,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Daylight Saving */
    i4_ret = menu_page_tree_add(ui4_page_date_time,
                                &t_g_menu_custom_item_time_dls,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Auto-Update Time */
    i4_ret = menu_page_tree_add(ui4_page_date_time,
                                &t_g_menu_custom_item_auto_update_time,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Date & Time */
    i4_ret = menu_page_tree_add(ui4_page_date_time,
                                &t_menu_item_page_date,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_date_time,
                                            ui2_item_id,
                                            _is_date_time_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                    PC setting Page in TV page                  */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_add(ui4_page_pc_setting,
                                &t_menu_item_page_vga_auto,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_pc_setting,
                                &t_g_menu_common_item_vga_pos_h,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_pc_setting,
                                &t_g_menu_common_item_vga_pos_v,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_pc_setting,
                                &t_g_menu_common_item_vga_phase,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                    Size & Position Page                        */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_add(ui4_page_vga,
                                &t_menu_item_page_vga_auto,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vga,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vga,
                                          ui2_item_id,
                                          _is_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_vga,
                                &t_g_menu_common_item_vga_pos_h,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vga,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vga,
                                          ui2_item_id,
                                          _is_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_vga,
                                &t_g_menu_common_item_vga_pos_v,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vga,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vga,
                                          ui2_item_id,
                                          _is_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Horizontal Size */
    i4_ret = menu_page_tree_add(ui4_page_vga,
                                &t_g_menu_custom_item_vid_size_h,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vga,
                                          ui2_item_id,
                                          _is_adv_vid_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Vertical Size */
    i4_ret = menu_page_tree_add(ui4_page_vga,
                                &t_g_menu_custom_item_vid_size_v,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vga,
                                          ui2_item_id,
                                          _is_adv_vid_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_vga,
                                &t_g_menu_common_item_vga_phase,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vga,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vga,
                                          ui2_item_id,
                                          _is_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_vga,
                                &t_g_menu_common_item_vga_clock,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_vga,
                                            ui2_item_id,
                                            _is_vga_connected);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_vga,
                                          ui2_item_id,
                                          _is_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);


    /*----------------------------------------------------------------*/
    /*                          System Info & Reset  Page                  */
    /*----------------------------------------------------------------*/

    /* soft power cycle */
    t_menu_item_soft_power_cycle.u.t_subpage.ui4_subpage_id = ui4_g_page_service_rst_dialog;
    i4_ret = menu_page_tree_add(ui4_page_help_sys_info_and_reset,
                                &t_menu_item_soft_power_cycle,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

     /* System Info */
    i4_ret = menu_page_tree_add(ui4_page_help_sys_info_and_reset,
                                &t_g_menu_item_page_ver_info,
                                &ui2_item_page_ver_info);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Remove Reset TV Settings */
    /*
    i4_ret = menu_page_tree_add(ui4_page_help_sys_info_and_reset,
                                &t_menu_item_page_reset_pub,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    */
#if SUPPORT_MENU_CODE
    /* Support Code */
    i4_ret = menu_page_tree_add(ui4_page_help_sys_info_and_reset,
                                &t_g_menu_item_page_support_code,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_help_sys_info_and_reset,
                                          ui2_item_id,
                                          menu_is_support_code_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_request_context_switch(_menu_get_capabilities_status, NULL, NULL, NULL);
#endif

    /* check for update */
    i4_ret = menu_page_tree_add(ui4_page_help_sys_info_and_reset,
                                   &t_g_menu_item_page_check_info,
                                   &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Clear Memory */
    i4_ret = menu_page_tree_add(ui4_page_help_sys_info_and_reset,
                                &t_menu_item_page_clear_memory,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Viewing Data */
    i4_ret = menu_page_tree_add(ui4_page_help_sys_info_and_reset,
                                &t_g_menu_custom_item_lst_acr,
                                &ui2_item_acr);
    ui2_g_item_id_lst_acr = ui2_item_acr;
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_help_sys_info_and_reset,
                                            ui2_item_acr,
                                            _is_smart_int_enable);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_hide(ui4_page_help_sys_info_and_reset,
                                          ui2_item_acr,
                                          _is_acr_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Advertising */
    i4_ret = menu_page_tree_add(ui4_page_help_sys_info_and_reset,
                                &t_g_menu_custom_item_advertising,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* limited ad tracking */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_advertising,
                                &t_g_menu_custom_item_limited_ad_tracking,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*reset tv ad id*/
    i4_ret = menu_page_tree_add(ui4_g_menu_page_advertising,
                                &t_menu_item_reset_tv_ad_id,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Dynamic Contrast -> rename as ad replacement*/
    i4_ret = menu_page_tree_add(ui4_g_menu_page_advertising,
                                &t_g_menu_custom_item_dynamic_content,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_advertising,
                                          ui2_item_id,
                                          _is_dynamic_content_hidden);
    MENU_LOG_ON_FAIL(i4_ret);




    /* Terms of Service && Smart Interactivity */
    i4_ret = menu_page_tree_add(ui4_page_help_sys_info_and_reset,
                                &t_menu_item_page_help_tos,
                                &ui2_item_page_help_tos);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_2K12_RETAIL_DEMO_MODE
    i4_ret = menu_page_tree_add(ui4_page_help_sys_info_and_reset,
                                &t_g_menu_common_item_demo_mode,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

#endif


    /*----------------------------------------------------------------*/
    /*                           Setting Page                           */
    /*----------------------------------------------------------------*/

    /*Menu Language */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                &t_g_menu_custom_item_gui_lang,
                                &ui2_item_id);

    MENU_LOG_ON_FAIL(i4_ret);

    /* Time */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                &t_menu_item_time_local_setting,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    /* TV Name */
    t_g_menu_item_page_tv_name.u.t_list_subpage.ui2_msgid_action = MLM_MENU_KEY_EMPTY;
    t_g_menu_item_page_tv_name.u.t_list_subpage.ui4_subpage_id = ui4_menu_page_tv_name;
    t_g_menu_item_page_tv_name.ui2_msgid_desc = MLM_MENU_KEY_HELP_TIP_NAME_TV;

    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                &t_g_menu_item_page_tv_name,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    /*Name Input*/
    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                &t_menu_item_page_inp_name,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_setup,
                                            ui2_item_id,
                                            _is_name_input_auto_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    // hide from input list
    MENU_LOG_ON_FAIL(hide_from_inp_init(ui4_g_menu_page_setup));

    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                &t_g_menu_common_item_power_on_input,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


#ifdef APP_SUPPORT_STR_CORE_OFF
    /* Fast Boot */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                &t_g_menu_custom_item_fast_boot,
                                &ui2_item_fast_boot);
    MENU_CHK_FAIL(i4_ret);
#endif

    // energy saving mode
    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                 &t_g_menu_custom_item_energy_saving_mode,
                                 &ui2_item_id);

    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_setup,
                                            ui2_item_id,
                                            _is_engary_saving_mode_hide);
    MENU_LOG_ON_FAIL(i4_ret);


    // OLED panel
    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                &t_menu_item_page_vid_oled_panel,
                                &ui2_item_id);

    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_setup,
                                            ui2_item_id,
                                            _is_oled_panel_auto_hide);
    MENU_LOG_ON_FAIL(i4_ret);

    // usb power
    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                 &t_g_menu_common_item_usb_power_ctrl,
                                 &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    // power indicator
#ifdef APP_LED_LOGO_CTRL
    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                 &t_g_menu_common_item_led_logo_ctrl,
                                 &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_setup,
                                 ui2_item_id,
                                 _is_retail_mode_start);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    // Timers
    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                  &t_menu_item_page_timers,
                                  &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Change PIN */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                             &t_menu_item_page_chg_pwd,
                             &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


#ifdef APP_CEC_MENU
     i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                 &t_menu_item_page_cec,
                                 &ui2_item_id);
     MENU_CHK_FAIL(i4_ret);
#endif

     /*mobile device*/
     i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                             &t_menu_item_page_mobile_device,
                             &ui2_item_id);
     MENU_LOG_ON_FAIL(i4_ret);

     /* voice remote */
     i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                             &t_menu_item_voice_remote,
                             &ui2_item_id);
     MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_setup,
                                            ui2_item_id,
                                            menu_is_voice_remote_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /*-------------------------------------------------------------------*/
    /*            OLED panel  page                                      */
    /*-------------------------------------------------------------------*/
    /*Screen Refresh*/
    i4_ret = menu_page_tree_add(ui4_page_vid_oled_panel,
                                &t_menu_item_oled_screen_refresh_1,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Pixel Shift*/
    i4_ret = menu_page_tree_add(ui4_page_vid_oled_panel,
                            &t_g_menu_common_item_vid_oled_pixel_shift,
                            &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);


    /*----------------------------------------------------------------*/
    /*                           Accessibility Page                           */
    /*----------------------------------------------------------------*/



    /*CC*/
    i4_ret = menu_page_tree_add(ui4_page_accessibility,
                                &t_menu_item_page_cc,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);


    i4_ret = menu_page_tree_set_auto_hide(ui4_page_accessibility,
                                 ui2_item_id,
                                 _is_cc_hiden);
    MENU_CHK_FAIL(i4_ret);

    /*Video description*/
    i4_ret = menu_page_tree_add(ui4_page_accessibility,
                                &t_g_menu_common_item_video_description_mode,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    /*Only TV and composite  source enabled*/
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_accessibility,
                                            ui2_item_id,
                                            _is_video_description_item_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    MENU_LOG_ON_FAIL(menu_page_tree_set_auto_hide(ui4_page_accessibility,
                                                  ui2_item_id,
                                                 _is_video_description_item_hiden));

#ifdef APP_TTS_SUPPORT
    /*Talk Back*/
    i4_ret = menu_page_tree_add(ui4_page_accessibility,
                                &t_g_menu_common_item_talkback,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_accessibility,
                                            ui2_item_id,
                                            _is_tts_item_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Speech rate*/
    i4_ret = menu_page_tree_add(ui4_page_accessibility,
                                &t_g_menu_common_speech_rate,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_accessibility,
                                            ui2_item_id,
                                            _is_tts_item_enable);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /*Zoom Mode*/
    i4_ret = menu_page_tree_add(ui4_page_accessibility,
                                &t_g_menu_common_item_zoom_mode,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_accessibility,
                                            ui2_item_id,
                                            _is_zoom_mode_item_enable);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef ENABLE_MENU_DLNA_SETTINGS
    #if defined (APP_NET_DLNA_SUPPORT) && defined(APP_NETWORK_SUPPORT)
        i4_ret = menu_page_tree_add(ui4_page_setup,
                                    &t_menu_item_page_dlna_setting,
                                    &ui2_item_id);
        MENU_CHK_FAIL(i4_ret);
    #endif
#endif

    /*----------------------------------------------------------------*/
    /*                        wizard mode. Page                       */
    /*----------------------------------------------------------------*/
    #if 0
    i4_ret = menu_page_tree_add(ui4_g_menu_page_setup,
                                &t_menu_item_page_start_wizard,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    #endif

    /*----------------------------------------------------------------*/
    /*                          HV Position Page                      */
    /*----------------------------------------------------------------*/
    /* H.Pos */
    i4_ret = menu_page_tree_add(ui4_page_hv_pos,
                                &t_g_menu_common_item_vid_pos_h,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_hv_pos,
                                            ui2_item_id,
                                            _is_hv_pos_enabled);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_hide(ui4_page_hv_pos,
                                          ui2_item_id,
                                          _is_hv_pos_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /* V.Pos */
    i4_ret = menu_page_tree_add(ui4_page_hv_pos,
                                &t_g_menu_common_item_vid_pos_v,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_hv_pos,
                                            ui2_item_id,
                                            _is_hv_pos_enabled);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_hide(ui4_page_hv_pos,
                                          ui2_item_id,
                                          _is_hv_pos_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Auto Phase */
    i4_ret = menu_page_tree_add(ui4_page_hv_pos,
                                &t_menu_item_page_auto_phase,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_hv_pos,
                                            ui2_item_id,
                                            _is_hv_pos_enabled);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_hide(ui4_page_hv_pos,
                                          ui2_item_id,
                                          _is_ypbpr_phase_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef ENABLE_MENU_DLNA_SETTINGS
#if defined (APP_NET_DLNA_SUPPORT) && defined(APP_NETWORK_SUPPORT)
    /* DMP setting. */
    i4_ret = menu_page_tree_add(ui4_page_dlna_setting,
                                &t_g_menu_common_item_dlna_setting,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_dlna_setting,
                                            ui2_item_id,
                                            _is_nw_connection_enable);
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_DMR_SUPPORT
    /* DMR setting. */
    i4_ret = menu_page_tree_add(ui4_page_dlna_setting,
                                &t_g_menu_common_item_dlna_dmr_setting,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_dlna_setting,
                                            ui2_item_id,
                                            _is_nw_connection_enable);
    MENU_CHK_FAIL(i4_ret);
#endif
#endif
#endif

#ifdef APP_2K12_RETAIL_DEMO_MODE
    /*----------------------------------------------------------------*/
    /*                          Help Page - Demo Mode Page           */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_add(ui4_page_help_demo_mode,
                                &t_menu_item_page_demo_mode_off,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_help_demo_mode,
                                &t_menu_item_page_demo_mode_start,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_page_help_demo_mode,
                                            ui2_item_id,
                                            _is_retail_mode_start);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /*----------------------------------------------------------------*/
    /*                          Parental Page                         */
    /*----------------------------------------------------------------*/
    /* Rating enable */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_par,
                                &t_g_menu_common_item_rating_enable,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Channel block */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_par,
                                &t_menu_item_page_ch_bk,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_par,
                                            ui2_item_id,
                                            _is_tv_input_src);
    MENU_LOG_ON_FAIL(i4_ret);
    */

    /* USA-TV */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_par,
                                &t_menu_item_page_vchip_us_tv,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_par,
                                          ui2_item_id,
                                          _is_usa_hidden);
    MENU_CHK_FAIL(i4_ret);
#endif

    /* USA-MOVIE */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_par,
                                &t_menu_item_page_vchip_us_movie,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_par,
                                          ui2_item_id,
                                          _is_usa_hidden);
    MENU_CHK_FAIL(i4_ret);
#endif

    /* CAN-ENGLISH */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_par,
                        &t_menu_item_page_vchip_ca_en,
                        &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_par,
                                          ui2_item_id,
                                          _is_can_hidden);
    MENU_CHK_FAIL(i4_ret);
#endif

    /* CAN-FRENCH */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_par,
                        &t_menu_item_page_vchip_ca_fr,
                        &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_par,
                                          ui2_item_id,
                                          _is_can_hidden);
    MENU_CHK_FAIL(i4_ret);
#endif

    #ifdef APP_MENU_OP_VCHIP_ENABLE
    /* Alt ratings */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_par,
                                &t_menu_item_page_op_vchip,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_par,
                                            ui2_item_id,
                                            _is_op_vchip_hide);
    MENU_CHK_FAIL(i4_ret);

    /* DRRT */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_par,
                                &t_menu_item_page_op_vchip_drrt,
                                &ui2_item_id);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_par,
                                            ui2_item_id,
                                            _is_op_vchip_drrt_hide);
    MENU_CHK_FAIL(i4_ret);
    #endif

    /* Block unrated */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_par,
                                &t_g_menu_custom_item_block_unrated,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Reset locks */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_par,
                                &t_menu_item_page_channel_lock_reset,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    /*----------------------------------------------------------------*/
    /*                          channel Page                          */
    /*----------------------------------------------------------------*/
     /* channel scan status */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_channels,
                                &t_g_menu_common_item_ch_scan_status,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_channels,
                                            ui2_item_id,
                                            _is_ch_scan_status_enable);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Auto Scan --> rename as Find Channel */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_channels ,
                                &t_menu_item_page_ch_scan,
                                &ui2_item_page_ch_scan);
    ui2_item_id = ui2_item_page_ch_scan;
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_channels,
                                ui2_item_page_ch_scan,
                                _is_native_app_enabled);
    MENU_LOG_ON_FAIL(i4_ret);
    if (0)
    {
    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_channels,
                                            ui2_item_id,
                                            _is_ch_scan_enabled);
    MENU_CHK_FAIL(i4_ret);
    }

    /* Auto Scan --> rename as Find New Channel */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_channels ,
                                &t_menu_item_page_ch_scan_new,
                                &ui2_item_page_ch_scan_new);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_channels,
                                ui2_item_page_ch_scan_new,
                                _is_native_app_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Channel Skip --> rename as Channel Skip */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_channels,
                                &t_menu_item_page_ch_sk,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_channels,
                                ui2_item_id,
                                _is_native_app_enabled);
    MENU_LOG_ON_FAIL(i4_ret);

//atm20111110
     /* Analog MTS modes --> rename as Analog Audio */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_channels,
                                &t_g_menu_common_item_aud_mts,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_channels,
                                           ui2_item_id,
                                           menu_custom_is_aud_stream_enabled);

    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_channels,
                                ui2_item_id,
                                _is_ana_mts_hide);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Digital MTS modes --> rename as Digital Language  */
    i4_ret = menu_page_tree_add(ui4_g_menu_page_channels,
                                &t_g_menu_custom_item_aud_lang,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_channels,
                                ui2_item_id,
                                _is_dig_mts_hide);

    i4_ret = menu_page_tree_set_auto_enable(ui4_g_menu_page_channels,
                                           ui2_item_id,
                                           menu_custom_is_aud_stream_enabled);
    /*Parental Controls*/
    i4_ret = menu_page_tree_add(ui4_g_menu_page_channels,
                                &t_menu_item_page_setup_par_ctrl,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_g_menu_page_channels,
                                          ui2_item_id,
                                          _is_vga_hdmi_hidden);
    MENU_LOG_ON_FAIL(i4_ret);
    /*----------------------------------------------------------------*/
    /*                      Attached Page to Tabs                     */
    /*----------------------------------------------------------------*/
    i4_ret = menu_pm_add_tab(ui4_g_menu_page_main_menu,
                             NULL_HANDLE,
                             NULL_HANDLE,
                             NULL_HANDLE,
                             NULL_HANDLE,
                             &ui2_g_menu_tab_aud);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _init_factory_menu_tree(VOID)
{
    INT32 i4_ret;

#ifdef APP_MENU_CUSTOM_FACTORY_TREE
    i4_ret =  menu_custom_init_factory_tree();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
#else

    UINT16 ui2_item_id;

    /*----------------------------------------------------------------*/
    /*                        Create all pages                        */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_FACTORY,
                                   &ui4_page_fac);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VID,
                                   &ui4_page_fac_vid);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_AUD,
                                   &ui4_page_fac_aud);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_TV,
                                   &ui4_page_fac_tv);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_SETUP,
                                   &ui4_page_fac_setup);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VID_CLR_TEMP,
                                   &ui4_page_fac_clr_tmp);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_auto_color,
                                 NULL,
                                 &ui4_page_auto_color);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                          Subpage Items                         */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_auto_color,
                                         MLM_MENU_KEY_VID_AUTO_COLOR,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_auto_color);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_fac_vid,
                                         MLM_MENU_KEY_VID,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_fac_vid);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_fac_aud,
                                         MLM_MENU_KEY_AUD,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_fac_aud);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_fac_tv,
                                         MLM_MENU_KEY_TV,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_fac_tv);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_fac_setup,
                                         MLM_MENU_KEY_SETUP,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_fac_setup);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_fac_clr_tmp,
                                         MLM_MENU_KEY_VID_CLR_TEMP,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_fac_clr_tmp);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                          Factory Page                          */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_g_menu_custom_item_input_src,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    static MENU_ITEM_T t_menu_item_fac_internal_pattern;

    i4_ret = menu_page_tree_list_item(&t_menu_item_fac_internal_pattern,
                                      MLM_MENU_KEY_INTERNAL_PATTERN,
                                      MLM_MENU_KEY_INTERNAL_PATTERN,
                                      MLM_MENU_KEY_INTERNAL_PATTERN_OFF_EX,
                                      MLM_MENU_KEY_INTERNAL_PATTERN_BLUE_EX,
                                      _set_internal_pattern_idx,
                                      _get_internal_pattern_idx);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_menu_item_fac_internal_pattern,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    static MENU_ITEM_T t_menu_item_page_fac_powe_status;

    i4_ret = menu_page_tree_list_item(&t_menu_item_page_fac_powe_status,
                                      MLM_MENU_KEY_FAC_POWER_STATUS,
                                      MLM_MENU_KEY_FAC_POWER_STATUS,
                                      MLM_MENU_KEY_FAC_LAST_STATUS,
                                      MLM_MENU_KEY_FAC_ALWAYS_ON,
                                      _set_power_status_idx,
                                      _get_power_status_idx);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_menu_item_page_fac_powe_status,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_g_menu_item_page_ver_info,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_menu_item_page_fac_vid,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_menu_item_page_fac_aud,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_menu_item_page_fac_tv,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_menu_item_page_fac_setup,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                      Factory Video Page                        */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_add(ui4_page_fac_vid,
                                &t_menu_item_page_auto_color,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_enable(ui4_page_fac_vid,
                                            ui2_item_id,
                                            menu_common_page_auto_color_is_enabled);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_add(ui4_page_fac_vid,
                                &t_menu_item_page_fac_clr_tmp,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_vid,
                                &t_g_menu_common_item_vid_ypbpr_phase,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_page_tree_set_auto_hide(ui4_page_fac_vid,
                                          ui2_item_id,
                                          _is_ypbpr_phase_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                      Factory Audio Page                        */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_add(ui4_page_fac_aud,
                                &t_g_menu_common_item_dolby_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_aud,
                                &t_g_menu_common_item_cmpss,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_aud,
                                &t_g_menu_common_item_drc,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_aud,
                                &t_g_menu_common_item_dmix,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_aud,
                                &t_g_menu_common_item_aud_bypass_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    /*----------------------------------------------------------------*/
    /*                       Factory TV Page                          */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_add(ui4_page_fac_tv,
                                &t_menu_item_page_adv_scan_rng,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    if(0)
    {
        i4_ret = menu_page_tree_add(ui4_page_fac_tv,
                                    &t_menu_item_page_adv_scan_sgl,
                                    &ui2_item_id);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /*----------------------------------------------------------------*/
    /*                      Factory Setup Page                        */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_add(ui4_page_fac_setup,
                                &t_g_menu_common_item_burning_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_setup,
                                &t_menu_item_page_reset_fac,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                          Color Temp. Page                      */
    /*----------------------------------------------------------------*/

    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_common_item_vid_clr_tmp_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_fac_clr_tmp,
                                          ui2_item_id,
                                          _is_adv_vid_hidden);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_custom_item_vga_clr_tmp_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_fac_clr_tmp,
                                          ui2_item_id,
                                          _is_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_common_item_vid_fac_clr_gain_r,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_common_item_vid_fac_clr_gain_g,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_common_item_vid_fac_clr_gain_b,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set the Factory Page */

    //i4_ret = menu_factory_set_pageid(ui4_page_ver_info);
    i4_ret = menu_factory_set_pageid(ui4_page_fac);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
#endif
}

INT32 menu_custom_hierarchy_init(VOID)
{
    INT32 i4_ret;

    i4_ret = _init_menu_tree();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _init_factory_menu_tree();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

VOID a_menu_custom_reset_pub(VOID)
{
    #ifdef SYS_MTKTVAPI_SUPPORT
    DBG_INFO(("ATSC a_menu_custom_reset_pub entered\n"));
    //_reset_pub();
    clear_memory();
    #endif
}

VOID a_menu_custom_reset_fac(VOID)
{
    #ifdef SYS_MTKTVAPI_SUPPORT
    DBG_INFO(("ATSC a_menu_custom_reset_fac entered\n"));
    //_reset_fac();
    clear_memory();
    #endif
}

VOID a_menu_custom_reset_pri(VOID)
{
    #ifdef SYS_MTKTVAPI_SUPPORT
    DBG_INFO(("ATSC a_menu_custom_reset_pri entered\n"));
    //_reset_pri();
    clear_memory();
    #endif
}

VOID a_menu_custom_save_sn_to_file(CHAR* serial_num)
{
    FILE*   fp_sn  = fopen(sn_path, "w");
    INT32   nwrite = 0;

    if (NULL != fp_sn)
    {
        nwrite = fwrite(serial_num, sizeof(CHAR), 64, fp_sn);
        DBG_INFO(("[MENU][%s %d] nwrite = %d!\n",__FUNCTION__,__LINE__,nwrite));
        fclose(fp_sn);
    }
    else
    {
        DBG_LOG_PRINT(("open %s failed!\n",sn_path));
        return;
    }
    return;

}

VOID a_menu_custom_get_sn_from_file(CHAR* serial_num)
{
    FILE*   fp_sn = fopen(sn_path, "r");
    INT32   nread = 0;

    if (NULL != fp_sn)
    {
        nread = fread(serial_num, sizeof(CHAR), 64, fp_sn);
        DBG_INFO(("[MENU][%s %d] nread = %d!\n",__FUNCTION__,__LINE__,nread));
        fclose(fp_sn);
    }
    else
    {
        DBG_LOG_PRINT(("open %s failed!\n",sn_path));
        return;
    }
    return;

}

BOOL menu_mtktvapi_is_screen_mode_hidden(VOID)
{
    BOOL b_ret = FALSE;

    return b_ret;
}

BOOL menu_mtktvapi_is_item_enable(MTKTVAPI_ITEM_INDEX_T e_item)
{
    BOOL b_ret = FALSE;

    return b_ret;
}

BOOL menu_mtktvapi_is_item_hidden(MTKTVAPI_ITEM_INDEX_T e_item)
{
    BOOL b_ret = FALSE;

    return b_ret;
}

