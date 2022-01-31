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
 * $RCSfile: menu_custom_settings.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/9 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 9cd3c20f32467f383f0d47c1431bb92b $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_svctx.h"
#include "c_os.h"
#include "c_wgl_image.h"
#include "u_drv_cust.h"
#include "cmd_convert.h"

#include "wizard_anim/a_wzd.h"
#include "wizard_anim/wzd.h"
#include "wizard/a_wzd.h"
#include "wizard/wzd.h"

#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"

#include "nav/pop/a_pop.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_page_ex/menu_page_ex.h"
#include "res/menu2/menu_custom.h"
#include "res/menu2/menu_cust_define.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "nav/input_src/a_input_src.h"
#include "res/app_util/icl/a_icl_custom.h"
#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#endif

#ifdef APP_RETAIL_MODE_SUPPORT
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/retail_mode/nav_retail_mode.h"
#endif

#include "res/app_util/model/model.h"
#include "wdk/a_vkb.h"

#include "menu2/menu_common/a_menu_page_color_tuner.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "rest/a_rest_event.h"
#include "app_util/a_screen_mode.h"
#include "menu2/menu_device/menu_page_device_setting.h"
#include "menu2/menu_dbg.h"
#include "res/revolt/revolt_settings_mlm.h"

extern INT32 a_wzd_resume_c4tv(UINT8 ui1_state, UINT8 ui1_page_idx);


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_ITEM_T          t_g_menu_custom_item_page_bass_treble;
MENU_ITEM_T          t_g_menu_custom_item_gui_lang;
MENU_ITEM_T          t_g_menu_custom_item_energy_saving_mode;
MENU_ITEM_T          t_g_menu_custom_item_aud_lang;
MENU_ITEM_T          t_g_menu_custom_item_time_zone;
MENU_ITEM_T          t_g_menu_custom_item_time_dls;
MENU_ITEM_T          t_g_menu_custom_item_auto_update_time;
MENU_ITEM_T          t_g_menu_custom_item_block_unrated;
MENU_ITEM_T          t_g_menu_custom_item_vga_clr_tmp_mode;
MENU_ITEM_T          t_g_menu_custom_item_vid_dcr;
MENU_ITEM_T          t_g_menu_custom_item_vid_lit_sns;
MENU_ITEM_T          t_g_menu_custom_item_gamma;
MENU_ITEM_T          t_g_menu_custom_item_cc;
MENU_ITEM_T          t_g_menu_custom_item_cc_on_mute;
MENU_ITEM_T          t_g_menu_custom_item_cc_enabled;
MENU_ITEM_T          t_g_menu_custom_item_cc_ana;
MENU_ITEM_T          t_g_menu_custom_item_cc_dig;
MENU_ITEM_T          t_g_menu_custom_item_vid_size_h;
MENU_ITEM_T          t_g_menu_custom_item_vid_size_v;

MENU_ITEM_T          t_g_menu_custom_item_lst_additional_scan;
MENU_ITEM_T          t_g_menu_custom_item_ch_scan;
MENU_ITEM_T          t_g_menu_custom_item_reset_channel_lock;

MENU_ITEM_T          t_g_menu_custom_item_ana_aud_out;

MENU_ITEM_T          t_menu_item_page_tuner_setup;
MENU_ITEM_T          t_menu_item_page_network_setup;
MENU_ITEM_T          t_menu_item_voice_remote;


#ifdef APP_2K12_RETAIL_DEMO_MODE
MENU_ITEM_T          t_menu_item_page_demo_mode_start;
MENU_ITEM_T          t_menu_item_page_demo_mode_off;
MENU_ITEM_T         t_g_menu_common_item_demo_mode;
#endif

MENU_ITEM_T          t_menu_item_page_wifi_remote_setup;

MENU_ITEM_T          t_menu_item_page_wifi_device_setup;


MENU_ITEM_T          t_g_menu_custom_item_input_src;
MENU_ITEM_T          t_g_menu_item_page_tv_name;
#ifdef APP_EMANUAL_SUPPORT
MENU_ITEM_T             t_menu_item_page_manual;
#endif
MENU_ITEM_T             t_g_menu_custom_item_lst_acr;
MENU_ITEM_T             t_g_menu_custom_item_dynamic_content;
MENU_ITEM_T             t_g_menu_custom_item_limited_ad_tracking;
BOOL                     b_g_menu_mmp_coexist_allow_key = TRUE;

#ifdef APP_SUPPORT_STR_CORE_OFF
MENU_ITEM_T          t_g_menu_custom_item_fast_boot;
#endif
MENU_ITEM_T          t_g_menu_custom_item_aspect_ratio;

#ifdef APP_NETWORK_SUPPORT
#ifdef APP_WAKE_ON_LAN_ENABLE_UI
MENU_ITEM_T          t_g_menu_custom_item_wake_on_lan;
#endif
#ifdef APP_NETWORK_WIFI_SUPPORT
//#ifdef APP_WAKE_ON_WLAN_ENABLE_UI
MENU_ITEM_T          t_g_menu_custom_item_wake_on_wlan;
//#endif
#endif
#endif

//MENU_ITEM_T             t_g_menu_custom_item_color_tuner;

#ifdef APP_MENU_3D_BRIGHTNESS_BOOST
extern MENU_ITEM_T 		   t_g_menu_item_3d_brightness_boost;
#endif

#ifdef DYNAMIC_NATIVE_DIAL_SUPPORT
MENU_ITEM_T         t_g_menu_custom_item_native_dial;
#endif

static UINT8 aui1_input_source[256] = {0};
static UINT8 ui1_input_source_num = 0;


static UINT16 aui2_lang_id[MLM_MENU_NUM_LANG] = {MLM_MENU_LANG_ENG, MLM_MENU_LANG_SPA, MLM_MENU_LANG_FRE};
static UINT16 aui2_lang_idx[MLM_MENU_NUM_LANG] = {0, 2, 1};
/*-----------------------------------------------------------------------------
                    static function declarations
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_dcr_idx(VOID);
static UINT16 _get_vid_auto_brightness_control_idx(VOID);
extern INT32 a_mmp_update_ap_info_frm_by_lang_change(VOID);
extern VOID set_preset_pic_mode_chg_status(BOOL b_is_chg);
/*-----------------------------------------------------------------------------
                    static function implementation
 ----------------------------------------------------------------------------*/
#ifdef APP_SUPPORT_STR_CORE_OFF
static VOID _set_fast_boot_mode_idx(UINT16 ui2_idx)
{
	UINT8		ui1_power_mode = ICL_CUSTOM_POWER_MODE_ECO;

	DBG_LOG_PRINT(("{Menu} _set_fast_boot_mode_idx with idx:%d \n",ui2_idx));

	ui1_power_mode = (0 == ui2_idx) ? ICL_CUSTOM_POWER_MODE_ECO : ICL_CUSTOM_POWER_MODE_QUICK_START;
	a_icl_custom_set_power_mode(ui1_power_mode);

	DBG_LOG_PRINT(("{Menu} _set_fast_boot_mode_idx with idx:%d,ui1_power_mode=%d \n",ui2_idx,ui1_power_mode));

	if (ui1_power_mode == ICL_CUSTOM_POWER_MODE_ECO)
	{
		a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_ON);
        a_cfg_custom_set_drv_eco_mode(ICL_CUSTOM_POWER_MODE_ECO);
        a_cfg_custom_set_power_mode_save(ICL_CUSTOM_POWER_MODE_ECO);
        rest_event_notify("tv_settings/system/power_mode",0,"Eco Mode");
	}
	else
	{
		a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_OFF);
        a_cfg_custom_set_drv_eco_mode(ICL_CUSTOM_POWER_MODE_QUICK_START);
        a_cfg_custom_set_power_mode_save(ICL_CUSTOM_POWER_MODE_QUICK_START);
        rest_event_notify("tv_settings/system/power_mode",0,"Quick Start");
	}

}
/*----------------------------------------------------------------------------
 * Name: _get_tshift_mode_idx
 *
 * Description:
 *
 * Inputs:	-
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_fast_boot_mode_idx(VOID)
{
	UINT8 ui1_fast_boot = 0;
	a_cfg_get_fast_boot(&ui1_fast_boot);
	DBG_INFO(("{Menu} _get_fast_boot_mode_idx with idx:%d \n",ui1_fast_boot));

    ui1_fast_boot = (APP_CFG_FAST_BOOT_OFF == ui1_fast_boot) ? 1 : 0;

	return (UINT16)ui1_fast_boot;
}
#endif /*APP_SUPPORT_STR_CORE_OFF*/

static VSH_SRC_ASPECT_RATIO_T _get_src_asp_ration(VOID)
{
    INT32 i4_ret;
    CHAR  s_disp_name[SYS_NAME_LEN + 1];
    VSH_SRC_RESOLUTION_INFO_T  t_timing = {0};
    VSH_SRC_ASPECT_RATIO_T     e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_UNKNOWN;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_get_timing(s_disp_name, &t_timing);
    MENU_LOG_ON_FAIL(i4_ret);

    e_src_asp_ratio = a_sml_get_src_asp_ratio(&t_timing);

    if(e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_UNKNOWN)
    {
        e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;
    }

    return e_src_asp_ratio;
}

static SCC_VID_SCREEN_MODE_T  _get_scr_mode(VSH_SRC_ASPECT_RATIO_T e_src_asp_ratio, SML_ITERATE_T e_dir)
{
    INT32  i4_ret;
    INT16  i2_value = 0;
    SCC_VID_SCREEN_MODE_T  e_screen_mode;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), &i2_value);
    MENU_CHK_FAIL(i4_ret);

    e_screen_mode = (SCC_VID_SCREEN_MODE_T)i2_value;

    i4_ret = a_sml_iterate_rec(e_src_asp_ratio,
                               e_dir,
                               &e_screen_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    return e_screen_mode;
}

static UINT16 _get_scr_mode_mlm_idx(SCC_VID_SCREEN_MODE_T e_screen_mode)
{
    UINT16  ui2_idx;

    switch (e_screen_mode)
    {
        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:    /* Zoom */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_ZOOM;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:    /* Wide */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_WIDE;
            break;

        case SCC_VID_SCREEN_MODE_NORMAL:          /* Normal */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_NORMAL;
            break;

        case SCC_VID_SCREEN_MODE_LETTERBOX:       /* Stretch */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_STRETCH;
            break;

        case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM: /* Panoramic */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_PANORAMIC;
            break;

        default:                                  /* unknown screen mode? */
            ui2_idx = MLM_MENU_KEY_EMPTY;
            break;
    }

    return ui2_idx;

}

static VOID _get_menu_aspect_ratio_text(UINT16    ui2_idx,   /* in */
                                                  UTF16_T*  w2s_str,   /* out */
                                                  SIZE_T    z_len)
{
    c_uc_w2s_strncpy(w2s_str, MENU_TEXT(ui2_idx), z_len);
}

static UINT16 _next_menu_aspect_ratio_idx(VOID)
{
    INT32  i4_ret;
    SCC_VID_SCREEN_MODE_T e_screen_mode;

    e_screen_mode = _get_scr_mode(_get_src_asp_ration(), SML_ITERATE_DIR_NEXT);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE),(INT16)e_screen_mode);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_update_screen_mode_ex();
    MENU_CHK_FAIL(i4_ret);

    return _get_scr_mode_mlm_idx(e_screen_mode);
}

static UINT16 _prev_menu_aspect_ratio_idx(VOID)
{
    INT32  i4_ret;
    SCC_VID_SCREEN_MODE_T e_screen_mode;

    e_screen_mode = _get_scr_mode(_get_src_asp_ration(), SML_ITERATE_DIR_PREV);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE),(INT16)e_screen_mode);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_update_screen_mode_ex();
    MENU_CHK_FAIL(i4_ret);

    return _get_scr_mode_mlm_idx(e_screen_mode);
}

static UINT16 _get_menu_aspect_ratio_idx(VOID)
{
    return _get_scr_mode_mlm_idx(_get_scr_mode(_get_src_asp_ration(), SML_ITERATE_DIR_THIS));
}

#ifdef APP_NETWORK_SUPPORT
#ifdef APP_WAKE_ON_LAN_ENABLE_UI
static VOID _set_wake_on_lan_idx(UINT16 ui2_idx)
{
    PCL_Ethernet_WOL_CTRL_T b_enable = ui2_idx>0? PCL_ETHERNET_WOL_ENABLE:PCL_ETHERNET_WOL_DISABLE;

    c_pcl_set_ethernet_wol_ctrl(b_enable);
    return;
}
static UINT16 _get_wake_on_lan_idx(VOID)
{
    PCL_Ethernet_WOL_CTRL_T b_enable = PCL_ETHERNET_WOL_DISABLE;

    c_pcl_get_ethernet_wol_ctrl(&b_enable);

    return (UINT16)b_enable;
}
#endif

//#ifdef APP_WAKE_ON_WLAN_ENABLE_UI
static VOID _set_wake_on_wlan_idx(UINT16 ui2_idx)
{
    PCL_WIFI_WOL_CTRL_T e_wlan_wol = ui2_idx > 0 ? PCL_WIFI_WOL_ENABLE : PCL_WIFI_WOL_DISABLE;

    c_pcl_set_wifi_wol_ctrl(e_wlan_wol);
    return;
}
static UINT16 _get_wake_on_wlan_idx(VOID)
{
    UINT16              ui2_val    = 0;
    PCL_WIFI_WOL_CTRL_T e_wlan_wol = PCL_WIFI_WOL_DISABLE;

    c_pcl_get_wifi_wol_ctrl(&e_wlan_wol);
    ui2_val = (e_wlan_wol == PCL_WIFI_WOL_ENABLE)?1:0;

    return ui2_val;
}
//#endif
#endif

/*GUI Language */
static VOID _set_gui_lang_idx(UINT16 ui2_idx)
{
    ISO_639_LANG_T  s639_lang;

    mlm_menu_langidx_to_s639(aui2_lang_id[ui2_idx], s639_lang);
#ifdef APP_MENU_MMP_COEXIST
	if (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
	{
		b_g_menu_mmp_coexist_allow_key = FALSE;
	}
#endif

#ifdef APP_MENU_MMP_COEXIST
    if (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
    {
        b_g_menu_mmp_coexist_allow_key = FALSE;
    }
#endif

    a_cfg_set_gui_lang(s639_lang);

    a_mmp_update_ap_info_frm_by_lang_change();

    menu_chg_lang(aui2_lang_id[ui2_idx]);
    a_vkb_set_lang(s639_lang);

    if(ui2_idx == 0)
    {
        a_c4tv_apron_set_locale("en");
    }
    else if(ui2_idx == 1)
    {
        a_c4tv_apron_set_locale("es");
    }
    else
    {
        a_c4tv_apron_set_locale("fr");
    }

    if (strncmp((char *)s639_lang, "spa", 3) == 0)
    {
        rest_event_notify("tv_settings/system/menu_language", 1, "Espa?ol");
    }
    else if (strncmp((char *)s639_lang, "fre", 3) == 0)
    {
        rest_event_notify("tv_settings/system/menu_language", 2, "Fran?ais");
    }
    else
    {
        rest_event_notify("tv_settings/system/menu_language", 0, "English");
    }

    //Send GAM event to Netflix for changing language. (MVD-2191)
    CMD_CONVERT_SEND_CMD_T t_send_cmd;
    t_send_cmd.s_source = "dtv_app_mtk";
    t_send_cmd.s_destination = "netflix";
    t_send_cmd.s_ack = NULL;
    t_send_cmd.s_command = "am_tv_lang";
    t_send_cmd.s_parameter = NULL;
    cmd_convert_send_command(&t_send_cmd);
}

VOID menu_custom_set_gui_lang_idx(UINT16 ui2_idx)
{
    _set_gui_lang_idx(ui2_idx);
}

static UINT16 _get_gui_lang_idx(VOID)
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
    /* Auto Test menu language */
    if( i4_ret == APP_CFGR_OK && c_strcmp(s639_lang,"spa") ==0 )
    DBG_CREATE_TEMP_FILE("test_case_menu_language_ok");

    return aui2_lang_idx[ui2_idx];
}

UINT16 menu_custom_get_gui_lang_idx(VOID)
{
    return _get_gui_lang_idx();
}

/*Audio Language */
static VOID _set_aud_lang_idx(UINT16 ui2_idx)
{
    ISO_639_LANG_T  s639_lang;
    UINT16          ui2_tmp_idx = 0;

    switch (ui2_idx)
    {
        case 0:
            /* English */
            ui2_tmp_idx = 0;
            break;
        case 1:
            /* Spanish */
            ui2_tmp_idx = 2;
            break;
        case 2:
            /* French */
            ui2_tmp_idx = 1;
            break;
        default:
            ui2_tmp_idx = 0;
            break;
    }

    mlm_menu_langidx_to_s639(ui2_tmp_idx, s639_lang);

    a_cfg_set_aud_lang(s639_lang);
    a_cfg_custom_set_aud_lang_vid_des(ui2_tmp_idx);
}

static UINT16 _get_aud_lang_idx(VOID)
{
    INT32   i4_ret;
    ISO_639_LANG_T s639_lang = {0};
    UINT16 ui2_idx = 0;
    UINT16 ui2_tmp_idx = 0;

    i4_ret = a_cfg_get_aud_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        return 0;
    }

    ui2_tmp_idx = mlm_menu_s639_to_langidx(s639_lang);

    switch (ui2_tmp_idx)
    {
        case 0:
            /* English */
            ui2_idx = 0;
            break;
        case 1:
            /* Spanish */
            ui2_idx = 2;
            break;
        case 2:
            /* French */
            ui2_idx = 1;
            break;
        default:
            ui2_idx = 0;
            break;
    }

    return ui2_idx;
}

/* Time Zone */
static VOID _set_time_zone_idx(UINT16 ui2_idx)
{
    TIME_T      t_tz_offset = 0;
    BOOL        b_dls       = FALSE;

    a_cfg_get_time_zone_data(&t_tz_offset, &b_dls);
    switch (ui2_idx)
    {
    case 0:
        t_tz_offset = -3.5 * 3600;/* Newfoundland*/
        break;
    case 1:
        t_tz_offset = -4   * 3600;  /* atlantic*/
        break;
    case 2:
        t_tz_offset = -5   * 3600; /* Eastern*/
        break;
    case 3:
        t_tz_offset = -6   * 3600; /* Central*/
        break;
    case 4:
        t_tz_offset = -7   * 3600; /* Mountain*/
        break;
    case 5:
        t_tz_offset = -8   * 3600; /* Pacific*/
        break;
    case 6:
        t_tz_offset = -9   * 3600; /* Alaska*/
        break;
    case 7:
        t_tz_offset = -10  * 3600; /* Hawaii*/
        break;
    case 8:
        t_tz_offset = -5   * 3600; /* Indiana*/
        break;
    case 9:
        t_tz_offset = -7   * 3600; /* Arizona*/
       break;
    case 10:
        t_tz_offset = -11  * 3600; /* samoa*/
       break;
    default:
        ui2_idx     = 5;
        t_tz_offset = -8   * 3600;
        break;
    }

    a_cfg_set_time_zone_data(t_tz_offset, b_dls);
    a_cfg_custom_set_timezone_idx((UINT8)ui2_idx);
    a_cfg_update_time_zone();
}

static UINT16 _get_time_zone_idx(VOID)
{
    UINT8 ui1_tz = APP_CFG_TZ_EASTERN_TIME;

    a_cfg_custom_get_timezone_idx(&ui1_tz);

    return (UINT16)ui1_tz;
}

/* Daylight Saving */
extern VOID _set_dls_idx(UINT16 ui2_idx)
{
    TIME_T      t_tz_offset = 0;
    BOOL        b_dls       = FALSE;

    a_cfg_get_time_zone_data(&t_tz_offset, &b_dls);
    a_cfg_set_time_zone_data(t_tz_offset,
                             ui2_idx == 0 ? FALSE : TRUE);
    a_cfg_update_time_zone();
}

static UINT16 _get_dls_idx(VOID)
{
    TIME_T      t_tz_offset = 0;
    BOOL        b_dls       = FALSE;

    a_cfg_get_time_zone_data(&t_tz_offset,
                             &b_dls);

    return (UINT16)b_dls ? 1 : 0;
}

/* H Size */
static VOID _set_vid_size_h_val(INT32 i4_val)
{
    #if 1
    INT16 i2_hsize;

    i2_hsize = (INT16)i4_val;

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE), i2_hsize);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
    #endif
}
static INT32 _get_vid_size_h_val(VOID)
{
   #if 1
   INT16 i2_hsize;

   a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE), &i2_hsize);
   return i2_hsize;
   #endif
}

/* V Size */
static VOID _set_vid_size_v_val(INT32 i4_val)
{
    #if 1
    INT16 i2_vsize;

    i2_vsize = (INT16)i4_val;

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE), i2_vsize);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
    #endif
}
static INT32 _get_vid_size_v_val(VOID)
{

   INT16 i2_vsize = 0;
   #if 1
   a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE), &i2_vsize);
   #endif

   return i2_vsize;
}

#ifdef APP_AUD_LANUAGE_CUSTOM_SUPPORT
/* deal with audio info */
UINT16  ui2_g_audio_stream_idx = (UINT16)0xffff;
static BOOL b_g_audio_stream_sel = TRUE;

static UINT16 _get_num_of_audio_stream()
{
    INT32       i4_ret;
    HANDLE_T    h_svctx = menu_get_current_svctx();
    UINT16      ui2_num = 0;
#if (defined(APP_PIP_POP_CTRL) || defined (APP_VOG_SUPPORT))

    TV_MODE_T   e_tv_mode = TV_MODE_TYPE_NORMAL;;
    TV_WIN_ID_T ui1_pip_aud_src;
    ISL_REC_T   t_isl_rec;

    a_tv_get_mode(&e_tv_mode);
    if( e_tv_mode != TV_MODE_TYPE_NORMAL)
    {
        ui1_pip_aud_src = (TV_WIN_ID_T)a_pop_get_audio_focus();
        if(ui1_pip_aud_src != TV_WIN_ID_MAIN)
        {

            i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_SUB,
                                                &t_isl_rec);
            if( (i4_ret != TVR_OK) ||
                (t_isl_rec.e_src_type != INP_SRC_TYPE_TV) )
            {
                return 0;
            }
        }
    }
#endif
    i4_ret = c_svctx_get_scdb_num_recs(h_svctx, ST_AUDIO, &ui2_num);
    if(i4_ret != SVCTXR_OK)
    {
        return 0;
    }
    else
    {
        return ui2_num;
    }
}

static INT32 _get_audio_stream_curr(
    UINT16*     pui2_idx,
    SCDB_REC_T* pt_scdb_rec)
{
    INT32       i4_ret;
    HANDLE_T    h_svctx = menu_get_current_svctx();
    SVCTX_GET_USING_SCDB_REC_T  t_using_scdb_rec;
    SIZE_T      z_get_info_size;

    t_using_scdb_rec.e_strm_type = ST_AUDIO;
    z_get_info_size = sizeof(SVCTX_GET_USING_SCDB_REC_T);
    i4_ret = c_svctx_get(h_svctx,
                         SVCTX_COMMON_GET_USING_SCDB_REC,
                         &t_using_scdb_rec,
                         &z_get_info_size);
    if(i4_ret != SVCTXR_OK)
    {
        return MENUR_FAIL;
    }
    else
    {
        *pui2_idx = t_using_scdb_rec.ui2_idx;
        c_memcpy(pt_scdb_rec, &t_using_scdb_rec.t_scdb_rec, sizeof(SCDB_REC_T));

        return MENUR_OK;
    }
}

static INT32 _get_audio_stream_by_idx(
    UINT16      ui2_idx,
    SCDB_REC_T* pt_scdb_rec)
{
    INT32       i4_ret;
    HANDLE_T    h_svctx = menu_get_current_svctx();
    SVCTX_GET_SCDB_REC_BY_IDX_T t_scdb_rec_by_id;
    SIZE_T      z_get_info_size;

    t_scdb_rec_by_id.e_strm_type = ST_AUDIO;
    t_scdb_rec_by_id.ui2_idx     = ui2_idx;
    z_get_info_size = sizeof(SVCTX_GET_SCDB_REC_BY_IDX_T);
    i4_ret = c_svctx_get(h_svctx,
                         SVCTX_COMMON_GET_SCDB_REC_BY_IDX,
                         &t_scdb_rec_by_id,
                         &z_get_info_size);
    if (i4_ret == SVCTXR_OK) {
        DBG_INFO(("Got 0-th Audio SCDB\r\n"));
    }
    if(i4_ret != SVCTXR_OK)
    {
        return MENUR_FAIL;
    }
    else
    {
        c_memcpy(pt_scdb_rec, &t_scdb_rec_by_id.t_scdb_rec, sizeof(SCDB_REC_T));

        return MENUR_OK;
    }
}

static UINT32 _set_audio_stream_lang_by_idx(UINT16 ui2_idx)
{
	INT32		i4_ret;
	SCDB_REC_T  t_scdb_rec;
	UINT16		ui2_rec_idx;
	CHAR*		ps_audio_lang;
	ISO_639_LANG_T	s639_lang;

	if(b_g_audio_stream_sel == TRUE)
    {
        ui2_rec_idx = ui2_idx;
        i4_ret = _get_audio_stream_by_idx(ui2_rec_idx, &t_scdb_rec);
    }
    else
    {
        i4_ret = _get_audio_stream_curr(&ui2_rec_idx, &t_scdb_rec);
    }

	/* Manipulate the language string */
	ps_audio_lang   = t_scdb_rec.e_rec_type == SCDB_REC_TYPE_AUDIO_MPEG ? t_scdb_rec.u.t_audio_mpeg.s_lang : "eng";
	if (ps_audio_lang == NULL)
	{
		return MENUR_FAIL;
	}
	c_strncpy(s639_lang,ps_audio_lang,ISO_639_LANG_LEN);

	a_cfg_set_aud_lang(s639_lang);

	return MENUR_OK;
}

static VOID _set_audio_stream_idx(UINT16 ui2_idx)
{
    ui2_g_audio_stream_idx = ui2_idx;
    b_g_audio_stream_sel   = TRUE;
	_set_audio_stream_lang_by_idx(ui2_g_audio_stream_idx);
}

static UINT16 _get_audio_stream_idx(VOID)
{
    UINT16   	ui2_num = 0;
    UINT16      ui2_idx_curr;
    SCDB_REC_T  t_scdb_rec;

	ui2_num = _get_num_of_audio_stream();

	/* power on init audio index*/
	if(ui2_g_audio_stream_idx >= ui2_num )
	{
	    if(_get_audio_stream_curr(&ui2_idx_curr, &t_scdb_rec) == MENUR_OK)
		{
		    if(ui2_idx_curr >= ui2_num)
		    {
		       	b_g_audio_stream_sel = FALSE;
		       	ui2_g_audio_stream_idx = 0;
			}
			else
			{
				b_g_audio_stream_sel = TRUE;
				ui2_g_audio_stream_idx = ui2_idx_curr;
			}
			return ui2_g_audio_stream_idx;
	    }
		else
		{
			ui2_g_audio_stream_idx = 0;
		}
	}
	if(ui2_g_audio_stream_idx == (UINT16)0xffff){
			ui2_g_audio_stream_idx = 0;
	}
	b_g_audio_stream_sel = TRUE;
    return ui2_g_audio_stream_idx;
}

static UINT16 _next_audio_stream_idx(VOID)
{
    UINT16      ui2_num;
    UINT16      ui2_idx_curr;
    SCDB_REC_T  t_scdb_rec;

    ui2_num = _get_num_of_audio_stream();
    if(_get_audio_stream_curr(&ui2_idx_curr, &t_scdb_rec) == MENUR_OK)
    {
        if(ui2_idx_curr + 1< ui2_num)
        {
            ui2_idx_curr += 1;
        }
        else
        {
            ui2_idx_curr =  0;
        }

        ui2_g_audio_stream_idx = ui2_idx_curr;
        b_g_audio_stream_sel   = TRUE;
		_set_audio_stream_lang_by_idx(ui2_g_audio_stream_idx);
    }

    return ui2_idx_curr;
}

static UINT16 _prev_audio_stream_idx(VOID)
{
    UINT16      ui2_num;
    UINT16      ui2_idx_curr;
    SCDB_REC_T  t_scdb_rec;

    ui2_num = _get_num_of_audio_stream();
    if(_get_audio_stream_curr(&ui2_idx_curr, &t_scdb_rec) == MENUR_OK)
    {
        if(ui2_idx_curr == 0)
        {
            ui2_idx_curr = ui2_num - 1;
        }
        else
        {
            ui2_idx_curr --;
        }

        ui2_g_audio_stream_idx = ui2_idx_curr;
        b_g_audio_stream_sel   = TRUE;
		_set_audio_stream_lang_by_idx(ui2_g_audio_stream_idx);
    }

    return ui2_idx_curr;
}
#endif

extern UTF16_T* nav_get_display_lang(const ISO_639_LANG_T*  ps639_lang);
extern UTF16_T* nav_get_audio_fmt_str(ASH_CHANNELS_T        e_channels);

#ifdef APP_AUD_LANUAGE_CUSTOM_SUPPORT
static VOID _get_audio_stream_text(
    UINT16    ui2_idx,   /* in */
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len)     /* in, len of w2s_str */
{
    INT32       i4_ret;
    UINT16      ui2_rec_ttl;
    UINT16      ui2_rec_idx;
    UTF16_T     w2s_string[65]  = {0};
    UTF16_T     w2s_order_string[11+1] = {0};
    UTF16_T     w2s_lang_string[3+1] = {0};
    UTF16_T     *pw2s_lang = NULL, *pw2s_order = NULL;
    CHAR*       ps_audio_lang;
    UTF16_T*    pw2s_audio_lang = NULL;
    UTF16_T*    pw2s_audio_fmt  = NULL;
    SCDB_REC_T  t_scdb_rec;
    ASH_AUDIO_INFO_T t_audio_info;
    SIZE_T      z_len_remain = 64;

    c_memset(&t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));

    ui2_rec_ttl = _get_num_of_audio_stream();

    if(ui2_rec_ttl == 0)
    {
        c_uc_ps_to_w2s("N/A", w2s_str, z_len);
        w2s_str[z_len - 1] = 0;
        return ;
    }
    else
    {
        if(ui2_idx >= ui2_rec_ttl)
        {
            return ;
        }
    }

    if(b_g_audio_stream_sel == TRUE)
    {
        ui2_rec_idx = ui2_idx;
        i4_ret = _get_audio_stream_by_idx(ui2_rec_idx, &t_scdb_rec);
    }
    else
    {
        i4_ret = _get_audio_stream_curr(&ui2_rec_idx, &t_scdb_rec);
    }

    if(i4_ret != MENUR_OK)
    {
        c_uc_ps_to_w2s("N/A", w2s_str, z_len);
        w2s_str[z_len - 1] = 0;
    }
    else
    {
        /* Manipulate the order string */
        if(ui2_rec_ttl > 1)
        {
            CHAR    s_order_string[11+1]   = {0};

            if(ui2_rec_ttl < 100)
            {
                c_sprintf(s_order_string, "%d/%d", ui2_rec_idx + 1, ui2_rec_ttl);
            }
            else
            {
                c_sprintf(s_order_string, "%d.", ui2_rec_idx + 1, ui2_rec_ttl);
            }

            i4_ret = c_uc_ps_to_w2s(s_order_string, w2s_order_string, 11);
            if(UCR_OK == i4_ret)
            {
                pw2s_order = w2s_order_string;
            }
        }

        /* Manipulate the language string */
        ps_audio_lang   = t_scdb_rec.e_rec_type == SCDB_REC_TYPE_AUDIO_MPEG ? t_scdb_rec.u.t_audio_mpeg.s_lang : "eng";
        pw2s_audio_lang = nav_get_display_lang((const ISO_639_LANG_T*)ps_audio_lang);

        if(pw2s_audio_lang != NULL)
        {
            pw2s_lang = pw2s_audio_lang;
        }
        else if(ps_audio_lang != NULL &&
                c_strcmp(ps_audio_lang, "   ") != 0)
        {
            i4_ret = c_uc_ps_to_w2s(ps_audio_lang, w2s_lang_string, 3);
            if(UCR_OK == i4_ret && '\0' != ps_audio_lang[0])
            {
                pw2s_lang = w2s_lang_string;
            }
        }

        i4_ret = c_svctx_get_audio_info(menu_get_crnt_svctx(), &t_audio_info);
        if(i4_ret == SVCTXR_OK)
        {
            pw2s_audio_fmt = nav_get_audio_fmt_str(t_audio_info.e_channels);
        }

        /*audio order*/
        if(pw2s_order)
        {
            z_len_remain = c_uc_w2s_strlen(w2s_string);
            c_uc_w2s_strncat(w2s_string, pw2s_order, 64 - z_len_remain);

            z_len_remain = c_uc_w2s_strlen(w2s_string);
            c_uc_w2s_strncat(w2s_string, L" ", 64 - z_len_remain);
        }

        /*audio language*/
        if(pw2s_lang)
        {
            z_len_remain = c_uc_w2s_strlen(w2s_string);
            c_uc_w2s_strncat(w2s_string, pw2s_lang, 64 - z_len_remain);

            z_len_remain = c_uc_w2s_strlen(w2s_string);
            c_uc_w2s_strncat(w2s_string, L" ", 64 - z_len_remain);
        }

        /*audio format*/
        if(pw2s_audio_fmt)
        {
            if(ui2_rec_ttl == 1 ||              /* Always show the format text if only one audio stream */
               b_g_audio_stream_sel == FALSE)   /* Don't show audio stream when it is just selected by user */
            {
                if (ASH_AUDIO_FMT_MPEG == t_audio_info.e_aud_fmt)
                {
                    z_len_remain = c_uc_w2s_strlen(w2s_string);
                    c_uc_w2s_strncat(w2s_string, L"MPEG ", 64 - z_len_remain);
                }
                else if (ASH_AUDIO_FMT_AC3 ==  t_audio_info.e_aud_fmt)
                {
                    z_len_remain = c_uc_w2s_strlen(w2s_string);
                    c_uc_w2s_strncat(w2s_string, L"D ", 64 - z_len_remain);
                }
                else if (ASH_AUDIO_FMT_E_AC3 == t_audio_info.e_aud_fmt)
                {
                    z_len_remain = c_uc_w2s_strlen(w2s_string);
                    c_uc_w2s_strncat(w2s_string, L"D + ", 64 - z_len_remain);
                }
                /*z_len_remain = c_uc_w2s_strlen(w2s_string);
                c_uc_w2s_strncat(w2s_string, pw2s_audio_fmt, 64 - z_len_remain);*/
            }
        }

        c_uc_w2s_strncpy(w2s_str, w2s_string, z_len);
        w2s_str[z_len - 1] = 0;
    }
}
#endif

/* dt sync mode */
static VOID _set_auto_update_time_idx(UINT16 ui2_idx)
{
    UINT8  ui1_dt_sync_mode;

    if (ui2_idx == 0)
    {
        ui1_dt_sync_mode = APP_CFG_DT_SYNC_MODE_MANUAL;
    }
    else
    {
        ui1_dt_sync_mode = APP_CFG_DT_SYNC_MODE_AUTO;
    }

    a_cfg_set_dt_sync_mode(ui1_dt_sync_mode);

    a_cfg_update_dt_sync_mode();
    a_cfg_update_time_zone();
}

static UINT16 _get_auto_update_time_idx(VOID)
{
    UINT8  ui1_dt_sync_mode;

    a_cfg_get_dt_sync_mode(&ui1_dt_sync_mode);
    if (ui1_dt_sync_mode == APP_CFG_DT_SYNC_MODE_AUTO)
    {
        return 1;
    }

    return 0;
}

/* block unrated */
static VOID _set_block_unrated_idx(UINT16 ui2_idx)
{
    UINT8   ui1_mpaa        = APP_CFG_VCHIP_US_MPAA_OFF;
    UINT8   ui1_tv_age      = APP_CFG_VCHIP_US_AGE_OFF;
    UINT64  ui8_tv_cnt_map  = 0;
    BOOL    b_mpaa_bu       = FALSE;
    BOOL    b_tv_bu         = FALSE;
    BOOL    b_block         = (ui2_idx == 0? FALSE: TRUE);

    a_cfg_lock();

    a_cfg_set_vchip_unrated(b_block);

    a_cfg_get_vchip_us(&ui1_mpaa,
                       &ui1_tv_age,
                       &ui8_tv_cnt_map,
                       &b_mpaa_bu,
                       &b_tv_bu);

    a_cfg_set_vchip_us(ui1_mpaa,
                       ui1_tv_age,
                       ui8_tv_cnt_map,
                       b_block,     /* block MPAA NA/NR as well */
                       b_block);    /* block TV None setting */

    a_cfg_unlock();
}

static UINT16 _get_block_unrated_idx(VOID)
{
    UINT8   ui1_mpaa        = APP_CFG_VCHIP_US_MPAA_OFF;
    UINT8   ui1_tv_age      = APP_CFG_VCHIP_US_AGE_OFF;
    UINT64  ui8_tv_cnt_map  = 0;
    BOOL    b_mpaa_bu       = FALSE;
    BOOL    b_tv_bu         = FALSE;

    a_cfg_get_vchip_us(&ui1_mpaa,
                       &ui1_tv_age,
                       &ui8_tv_cnt_map,
                       &b_mpaa_bu,
                       &b_tv_bu);

    return b_tv_bu ? 1 : 0;
}

static VOID _set_vga_clr_tmp_mode_idx(UINT16 ui2_idx)
{
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), (ui2_idx+1));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
}

static UINT16 _get_vga_clr_tmp_mode_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);
    return (UINT16)(i2_val-1);
}

static BOOL _is_vga_clr_tmp_subpage(UINT16 ui2_idx, UINT32 *pui4_subpage)
{
    if(ui2_idx == 3)
    {
        *pui4_subpage = ui4_g_menu_page_clr_tmp;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/* vid dcr */
extern VOID _set_vid_dcr_idx(UINT16 ui2_idx)
{
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), (INT16)ui2_idx);

    ACFG_DEBUG_BACKLIGHT(
        DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL]{%s: %d} Call a_cfg_av_update(APP_CFG_RECID_VID_CUSTOM_DCR)\n", __FUNCTION__, __LINE__ ));
    );
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));

#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
    a_cfg_custom_plf_opt_set_dcr_setting(ui2_idx);
#endif
}

static UINT16 _get_vid_dcr_idx(VOID)
{
    INT16 i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_val);
#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR

    a_cfg_custom_plf_opt_get_dcr_setting();
#endif

    return (UINT16)(i2_val);
}

/* light sensor */
static VOID _set_vid_auto_brightness_control_idx(UINT16 ui2_idx)
{
    if( FALSE == a_cfg_cust_LightSensor_CheckIfCanTurnOn() )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
            DBG_LOG_PRINT(("[MENU][LightSensor]{%s: %d} Cannot turn on LightSensor => Do nothing disable!\n", __FUNCTION__,__LINE__ ));
        );
        return ;
    }

    UINT16  ui2_idx_pre = _get_vid_auto_brightness_control_idx();

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), (INT16)ui2_idx);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));

#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR

    a_cfg_custom_plf_opt_set_lightsensor(ui2_idx);
#endif

    if (ui2_idx_pre != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

static UINT16 _get_vid_auto_brightness_control_idx(VOID)
{
    INT16 i2_val = 0;

  #if 1
    if( FALSE == a_cfg_cust_LightSensor_CheckIfCanTurnOn() )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LIGHT_SENSOR,
            DBG_LOG_PRINT(("[MENU][LightSensor]{%s: %d} Cannot turn on LightSensor => UI off!\n", __FUNCTION__,__LINE__ ));
        );
        return 0;
    }
  #else
	ACFG_RETAIL_MODE_T t_retail_mode = 0;

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        return 0;
    }
  #endif

#ifdef NEVER
    /*spec 5.2 requirement  active full arryay is > low, we need disable ABC and set OFF  to driver*/
	if(a_cfg_cust_get_support_local_dimming())
	{
        UINT16 ui2_val = 0;
        if(CFGR_OK == a_cfg_custom_get_dimming_idx(&ui2_val) && ui2_val > 1)
        {
            return 0;
        }
    }
#endif /* NEVER */

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), &i2_val);

#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR

    a_cfg_custom_plf_opt_get_lightsensor();
#endif

    return (UINT16)(i2_val);
}

/* picture gamma */
static VOID _set_vid_gamma_idx(UINT16 ui2_idx)
{
	UINT16	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA);
    INT16   ui2_pre_idx = 0;

    a_cfg_av_get(ui2_id, &ui2_pre_idx);
    a_cfg_av_set(ui2_id, ui2_idx);
    a_cfg_av_update(ui2_id);
    if (ui2_pre_idx != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

static UINT16 _get_vid_gamma_idx(VOID)
{
    INT16   i2_val = 0;
	UINT16	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA);

    a_cfg_av_get(ui2_id, &i2_val);

    return (UINT16)(i2_val);
}

static VOID _set_cc_on_off(UINT16 ui2_idx)
{
    INT32 i4_ret = APP_CFGR_OK;


    i4_ret = a_cfg_set_cc_enabled((UINT8)ui2_idx);

    if (APP_CFGR_OK == i4_ret)
    {
        a_cfg_custom_plf_opt_set_cc_onoff(ui2_idx);

        if(ui2_idx)
        {
            nav_zoom_mode_send_toast_msg(MLM_SETTINGS_KEY_CLOSED_CAPTION_ON);
        }
        else
        {
            nav_zoom_mode_send_toast_msg(MLM_SETTINGS_KEY_CLOSED_CAPTION_OFF);
        }
    }
}

static UINT16 _get_cc_on_off(VOID)
{
    UINT8 ui1_cc = APP_CFG_CUSTOM_ANA_CC_CC1;

    a_cfg_get_cc_enabled(&ui1_cc);

    return (UINT16)ui1_cc;
}

static VOID _set_ana_cc_idx(UINT16 ui2_idx)
{
    INT32 i4_ret = APP_CFGR_OK;

    i4_ret = a_cfg_set_anlg_cc((UINT8)ui2_idx);

    if (APP_CFGR_OK == i4_ret)
    {
        a_cfg_custom_plf_opt_set_cc_onoff(ui2_idx);
    }
}

static UINT16 _get_ana_cc_idx(VOID)
{
    UINT8 ui1_cc = APP_CFG_CUSTOM_ANA_CC_CC1;

    a_cfg_get_anlg_cc(&ui1_cc);

    return (UINT16)ui1_cc;
}

static VOID _set_dig_cc_idx(UINT16 ui2_idx)
{
    INT32 i4_ret = APP_CFGR_OK;

    i4_ret = a_cfg_set_dig_cc((UINT8)ui2_idx);

    if (APP_CFGR_OK == i4_ret)
    {
        a_cfg_custom_plf_opt_set_cc_onoff(ui2_idx);
    }
}

static UINT16 _get_dig_cc_idx(VOID)
{
    UINT8 ui1_cc = APP_CFG_CUSTOM_DIG_CC_SERVICE1;

    a_cfg_get_dig_cc(&ui1_cc);

    return (UINT16)ui1_cc;
}

/* CC on mute */
static VOID _set_cc_on_mute_idx(UINT16 ui2_idx)
{
    UINT8   ui1_cc_enabled;

    if(ui2_idx == 1)
    {
        ui1_cc_enabled = APP_CFG_CC_MUTE_ON;
    }
    else
    {
        ui1_cc_enabled = APP_CFG_CC_ON;
    }

    a_cfg_set_cc_enabled(ui1_cc_enabled);
}

static UINT16 _get_cc_on_mute_idx(VOID)
{
    UINT8   ui1_cc_enabled = APP_CFG_CC_ON;

    a_cfg_get_cc_enabled(&ui1_cc_enabled);

    if(ui1_cc_enabled == APP_CFG_CC_MUTE_ON)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*----------------------------------------------------------------------------
 * Name: _set_additional_scan
 *
 * Description:
 *
 * Inputs:
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _set_additional_scan (UINT16 ui2_idx)
{
    MENU_LOG_ON_FAIL (a_cfg_custom_set_additional_scan ((UINT8)ui2_idx));
}

/*----------------------------------------------------------------------------
 * Name: _get_additional_scan
 *
 * Description:
 *
 * Inputs:
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static UINT16 _get_additional_scan (VOID)
{
    INT32                       i4_ret ;
    UINT8                      ui1_value ;

    i4_ret = a_cfg_custom_get_additional_scan (&ui1_value);
    MENU_LOG_ON_FAIL (i4_ret) ;

    if (APP_CFGR_OK != i4_ret)
    {
        ui1_value = 0;
    }

    return ui1_value;
}

/*----------------------------------------------------------------------------
 * Name: _set_ana_aud_out_idx
 *
 * Description:
 *
 * Inputs:
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _set_ana_aud_out_idx (UINT16 ui2_idx)
{
    A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out;

    switch(ui2_idx)
    {
        case 0:
            e_aud_out = A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED;
            break;

        case 1:
            e_aud_out = A_CFG_CUSTOM_ANALOG_AUD_OUT_VARIABLE;
            break;

        default:
            e_aud_out = A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED;
            break;
    }

    a_cfg_custom_set_ana_audio_out (e_aud_out);
    a_cfg_custom_update_ana_audio_out();
    /*update volume value for fusion1.5*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));
}

/*----------------------------------------------------------------------------
 * Name: _get_ana_aud_out_idx
 *
 * Description:
 *
 * Inputs:
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static UINT16 _get_ana_aud_out_idx (VOID)
{
    A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out;

    a_cfg_custom_get_ana_audio_out(&e_aud_out);

    if(e_aud_out == A_CFG_CUSTOM_ANALOG_AUD_OUT_VARIABLE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*----------------------------------------------------------------------------
 * Name: _set_ch_scan
 *
 * Description:
 *
 * Inputs:
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _set_ch_scan (UINT16 ui2_idx)
{
    if (0 == ui2_idx)
    {
        /* do not execute scan */
    }
    else
    {
        if (menu_custom_is_channel_blocked())
        {
            /* go to scan password page */
            MENU_LOG_ON_FAIL (menu_nav_go (ui4_g_menu_page_ch_scan2_pwd, NULL)) ;
        }
        else
        {
            /* do scan */
            MENU_LOG_ON_FAIL (menu_nav_go (ui4_g_menu_page_ch_scan, NULL)) ;
        }
    }
}

/*----------------------------------------------------------------------------
 * Name: _get_ch_scan
 *
 * Description:
 *
 * Inputs:
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static UINT16 _get_ch_scan (VOID)
{
    return 0 ;
}

static VOID _set_reset_channel_lock_idx(UINT16 ui2_idx)
{
    if (ui2_idx == 1)
    {
        a_cfg_custom_reset_channel_lock();
    }
    else
    {
        /* do nothing */
    }
}

static UINT16 _get_reset_channel_lock_idx(VOID)
{
    return 0;
}

static VOID _set_input_source_idx(UINT16 ui2_idx)
{
    INT32       i4_ret=0;
    ISL_REC_T   t_isl_rec;
    UINT8       ui1_num_rec;

    i4_ret=a_isl_get_num_rec(&ui1_num_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    if(ui2_idx >=  ui1_num_rec)
    {
        return;
    }

    i4_ret=a_isl_get_rec_by_idx(aui1_input_source[ui2_idx], &t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_change_input_src_by_rec()\n", __FUNCTION__,__LINE__ ));
    );

    i4_ret=a_tv_change_input_src_by_rec(t_g_menu_common.h_svctx,
                                 SVCTX_STRM_MODE_AS_LAST,
                                 &t_isl_rec,
                                 NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (i4_ret != TVR_OK)
    {
        a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
                           (VOID*)(UINT32)TV_WIN_ID_MAIN,
                           (VOID*)(UINT32)t_isl_rec.ui1_id);
    }

}

static UINT8 _get_input_isl_idx_by_id(VOID)
{
    ISL_REC_T   t_isl_rec;
    ISL_REC_T   t_isl_rec_crnt;
    INT32       i4_ret=0;
    UINT8       ui1_idx;
    UINT8       ui1_rec_num;

    ui1_input_source_num = 0;

	c_memset(aui1_input_source, 0, sizeof(aui1_input_source));
    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
    c_memset(&t_isl_rec_crnt, 0, sizeof(ISL_REC_T));

    /* Get Input Source number */
    i4_ret = a_isl_get_num_rec(&ui1_rec_num);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_PIP_ENABLE
    TV_MODE_T   e_tv_mode;

    i4_ret =a_tv_get_mode(&e_tv_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    if (e_tv_mode == TV_MODE_TYPE_NORMAL)
    {
#endif
        /* get the current svl record */
        i4_ret = menu_get_crnt_isl(&t_isl_rec_crnt);
        MENU_LOG_ON_FAIL(i4_ret);
        for(ui1_idx=0; ui1_idx < ui1_rec_num; ui1_idx++)
        {
            i4_ret =a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);
            MENU_LOG_ON_FAIL(i4_ret);

            ui1_idx = ui1_input_source_num;

    		aui1_input_source[ui1_input_source_num] = t_isl_rec.ui1_id;
            ui1_input_source_num ++;
        }

        /* Iterate the ISL */
        for(ui1_idx = 0 ; ui1_idx < ui1_rec_num ; ui1_idx++)
        {
            i4_ret = a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);
            MENU_LOG_ON_FAIL(i4_ret);

            if(t_isl_rec.ui1_id == t_isl_rec_crnt.ui1_id)
            {
                break;
            }
        }
        if(ui1_idx == ui1_rec_num)
        {
            ui1_idx = 0;
        }

        return ui1_idx;
#ifdef APP_MENU_PIP_ENABLE
    BOOL        b_same_group;
    }
    else
    {
        i4_ret =a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec_crnt);
        MENU_LOG_ON_FAIL(i4_ret);

        for(ui1_idx=0; ui1_idx < ui1_rec_num; ui1_idx++)
        {
            i4_ret = a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);
            MENU_LOG_ON_FAIL(i4_ret);

            if (t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL)
            {
    			continue;
            }

           i4_ret = a_isl_is_same_group(&t_isl_rec_crnt, &t_isl_rec, &b_same_group);
           MENU_LOG_ON_FAIL(i4_ret);

    		if(b_same_group)
            {
        		aui1_input_source[ui1_input_source_num] = t_isl_rec.ui1_id;
                ui1_input_source_num ++;
    		}
        }

        /* Iterate the ISL */
        for(ui1_idx = 0 ; ui1_idx < ui1_rec_num ; ui1_idx++)
        {
            i4_ret = a_isl_get_rec_by_idx(aui1_input_source[ui1_idx], &t_isl_rec);
            MENU_LOG_ON_FAIL(i4_ret);

            if(t_isl_rec.ui1_id == t_isl_rec_crnt.ui1_id)
            {
                break;
            }
        }
        if(ui1_idx == ui1_rec_num)
        {
            ui1_idx = 0;
        }

        return ui1_idx;
    }
#endif

}

static UINT16 _get_input_source_idx(VOID)
{
    UINT8   ui1_idx;

    ui1_idx = _get_input_isl_idx_by_id();

    return (UINT16)ui1_idx;
}

static UINT16 _prev_input_source_idx(VOID)
{
    INT32       i4_ret;
    UINT8       ui1_i;
    UINT8       ui1_num_rec;
    ISL_REC_T   t_isl_rec_crnt;
    ISL_REC_T   t_isl_rec_next;

    a_isl_get_num_rec(&ui1_num_rec);

    /* get the current svl record */
    c_memset(&t_isl_rec_crnt, 0, sizeof(ISL_REC_T));

    i4_ret = menu_get_crnt_isl(&t_isl_rec_crnt);
	MENU_LOG_ON_FAIL(i4_ret);

	for(ui1_i = 0; ui1_i < ui1_num_rec; ui1_i++)
	{
        if(aui1_input_source[ui1_i] == t_isl_rec_crnt.ui1_id)
        {
             break;
        }
	}

    if(ui1_i >= ui1_input_source_num )
    {
        ui1_i = 0;
    }
    else if(ui1_i == 0)
    {
		ui1_i = ui1_input_source_num - 1;
    }
	else
	{
        ui1_i -- ;
	}

	i4_ret =a_isl_get_rec_by_idx(aui1_input_source[ui1_i], &t_isl_rec_next);
	MENU_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_set_input_src_id(%d)\n", __FUNCTION__,__LINE__, TV_WIN_ID_MAIN ));
    );

    i4_ret =a_tv_set_input_src_id(TV_WIN_ID_MAIN,
                          t_isl_rec_next.ui1_id);
	MENU_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_change_input_src_by_rec()\n", __FUNCTION__,__LINE__ ));
    );

    i4_ret =a_tv_change_input_src_by_rec(t_g_menu_common.h_svctx,
                                 SVCTX_STRM_MODE_AS_LAST,
                                 &t_isl_rec_next,
                                 NULL);
	MENU_LOG_ON_FAIL(i4_ret);

    if (i4_ret != TVR_OK)
    {
        a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
                           (VOID*)(UINT32)TV_WIN_ID_MAIN,
                           (VOID*)(UINT32)t_isl_rec_next.ui1_id);
    }

    i4_ret =menu_pm_refresh();
	MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =menu_pm_repaint();
	MENU_LOG_ON_FAIL(i4_ret);

    return ui1_i;
}

static UINT16 _next_input_source_idx(VOID)
{
    INT32       i4_ret;
	UINT8	    ui1_i;
	UINT8	    ui1_num_rec;
	ISL_REC_T	t_isl_rec_crnt;
	ISL_REC_T	t_isl_rec_next;

	a_isl_get_num_rec(&ui1_num_rec);
    /* get the current svl record */
    c_memset(&t_isl_rec_crnt, 0, sizeof(ISL_REC_T));

    i4_ret = menu_get_crnt_isl(&t_isl_rec_crnt);
	MENU_LOG_ON_FAIL(i4_ret);

	for(ui1_i = 0; ui1_i < ui1_num_rec; ui1_i++)
	{
		if(aui1_input_source[ui1_i] == t_isl_rec_crnt.ui1_id)
		{
			 break;
		}
	}

    ui1_i++;

	if(ui1_i >= ui1_input_source_num )
	{
		ui1_i = 0;
	}

	i4_ret =a_isl_get_rec_by_idx(aui1_input_source[ui1_i], &t_isl_rec_next);
	MENU_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_set_input_src_id(%d)\n", __FUNCTION__,__LINE__, TV_WIN_ID_MAIN ));
    );

    i4_ret =a_tv_set_input_src_id(TV_WIN_ID_MAIN,
                          t_isl_rec_next.ui1_id);
	MENU_LOG_ON_FAIL(i4_ret);

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_change_input_src_by_rec()\n", __FUNCTION__,__LINE__ ));
    );

    i4_ret =a_tv_change_input_src_by_rec(t_g_menu_common.h_svctx,
                                 SVCTX_STRM_MODE_AS_LAST,
                                 &t_isl_rec_next,
                                 NULL);
	MENU_LOG_ON_FAIL(i4_ret);

    if (i4_ret != TVR_OK)
    {
        a_input_src_do_cmd(NAV_IPTS_CMD_CHG_SRC_EXTERNAL,
                           (VOID*)(UINT32)TV_WIN_ID_MAIN,
                           (VOID*)(UINT32)t_isl_rec_next.ui1_id);
    }

    i4_ret =menu_pm_refresh();
	MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =menu_pm_repaint();
	MENU_LOG_ON_FAIL(i4_ret);

	return (UINT16)ui1_i;
}

static VOID _get_input_source_text(
    UINT16    ui2_idx,   /* in */
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len)     /* in, len of w2s_str */
{
    INT32       i4_ret=0;
    UINT8       ui1_isl_id = (UINT8)ui2_idx;
    ISL_REC_T   t_isl_rec;
    UINT8       ui1_num_rec;
    APP_TV_NET_SVC_STATUS t_svc_state;
    CHAR                s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN];
    UTF16_T             w2s_temp_str[APP_CFG_CUSTOM_INP_NAME_LEN];
    BOOL                b_is_subpage_state;

    if(w2s_str == NULL)
    {
        return;
    }

    c_memset(w2s_str, 0x0, z_len * sizeof(UTF16_T));

    i4_ret=a_isl_get_num_rec(&ui1_num_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    if(ui1_isl_id >= ui1_num_rec )
    {
        return;
    }
    if(aui1_input_source[ui1_isl_id] == 255)
    {
        return;
    }

    t_svc_state = a_tv_net_get_tv_svc_status();

    if(APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state)
    {
        c_uc_w2s_strncpy (w2s_str,
                         MENU_TEXT(MLM_MENU_KEY_MENU_INPUT_VIA),
                         (UINT32)z_len - 1);
        w2s_str[z_len - 1] = 0;
    }
    else
    {

        i4_ret=a_isl_get_rec_by_id(aui1_input_source[ui1_isl_id],&t_isl_rec);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncpy(w2s_str,
                         a_isl_get_display_name(&t_isl_rec),
                         (UINT32)z_len - 1);

        i4_ret=a_cfg_custom_get_inp_name(t_isl_rec.ui1_id, s_inp_name);
        MENU_LOG_ON_FAIL(i4_ret);

        b_is_subpage_state = menu_page_is_in_list_subpage_state();

        if((a_cfg_custom_is_inp_name_empty (s_inp_name)==FALSE) &&
           (b_is_subpage_state == TRUE))
        {
            c_uc_ps_to_w2s(s_inp_name, w2s_temp_str, APP_CFG_CUSTOM_INP_NAME_LEN);

            c_uc_w2s_strcat(w2s_str, L"  ");
            c_uc_w2s_strcat(w2s_str,w2s_temp_str);
            w2s_str[z_len - 1] = 0;
            return;
        }
        else
        {
            if(a_cfg_custom_is_inp_name_empty (s_inp_name)==FALSE)
            {
                c_uc_ps_to_w2s(s_inp_name, w2s_str, APP_CFG_CUSTOM_INP_NAME_LEN);
                w2s_str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = 0;
                return;
            }
        }
        w2s_str[z_len - 1] = 0;
    }
    return;
}

// on = 0, off = 1
VOID menu_custom_set_dynamic_content_idx(UINT16 ui2_idx)
{
    a_cfg_cust_set_dynamic_content_value((UINT8)ui2_idx);
    menu_pm_repaint();

}

UINT16 menu_custom_get_dynamic_content_idx(VOID)
{
    UINT8 ui1_idx = 0;
    a_cfg_cust_get_dynamic_content_value(&ui1_idx);
    return ui1_idx;
}

// on = 0, off = 1
VOID menu_custom_set_limited_ad_tracking_idx(UINT16 ui2_idx)
{
    a_cfg_cust_set_limited_ad_tracking(ui2_idx);
    menu_pm_repaint();
}

UINT16 menu_custom_get_limited_ad_tracking_idx(VOID)
{
    UINT8 ui1_value = 0;
    a_cfg_cust_get_limited_ad_tracking(&ui1_value);
    return ui1_value;

}


extern INT32 a_nw_custom_get_http_url_for_acr(BOOL b_accept);
static VOID _set_acr_idx(UINT16 ui2_idx)
{
    if(1 == ui2_idx)
    {
        TV_WIN_ID_T                 e_focus_id;
        ISL_REC_T                   t_isl_rec;

        // Deep-link into OOBE Viewing Data
        DBG_LOG_PRINT(("Deep-linked Viewing Data OOBE launch\n"));

        INT32 i4_ret = a_tv_get_focus_win(&e_focus_id);
        NAV_LOG_ON_FAIL(i4_ret);
        i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);
        NAV_LOG_ON_FAIL(i4_ret);

        if (INP_SRC_TYPE_VTRL != t_isl_rec.e_src_type
            && DEV_VTRL_CAST != t_isl_rec.t_avc_info.e_video_type)
        {
            DBG_LOG_PRINT(("Switching source to SmartCast.\n"));
            change_source_way = TRUE;
        }

        a_wzd_resume_state_only_c4tv(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_VIEWING_DATA);
        a_rest_app_launch_cast_to_conjure_apps();

        // Hide menu
        menu_leave(FALSE, 0);
        return MENUR_OK;
    }
    else if (0 == ui2_idx)
    {
        ui2_idx = ACFG_ACR_OFF;
        a_cfg_custom_set_acr(ui2_idx);
        MENU_LOG_ON_FAIL (a_tv_custom_set_viewing_data_accepted(FALSE)); //CID:4491872
        a_tv_custom_set_viewing_data_show(FALSE);
    }
    return;
}

static UINT16 _get_acr_idx(VOID)
{
    UINT16  ui2_idx = 0;
    BOOL b_viewing_data_accepted = FALSE;

    b_viewing_data_accepted = a_tv_custom_get_viewing_data_accepted();

    if(b_viewing_data_accepted)
    {
        ui2_idx = 1;
    }
    else
    {
        ui2_idx = 0;
    }

    return (ui2_idx);
}

#ifdef APP_MENU_3D_BRIGHTNESS_BOOST
static VOID _set_3d_brightness_boost_idx(UINT16 ui2_idx)
{
	BOOL 	b_on = FALSE;

	a_cfg_custom_set_3d_brightness_boost(ui2_idx);

	b_on =  ui2_idx == 0 ? FALSE : TRUE;
	a_cfg_custom_3d_brightness_boost(b_on);
    return;
}

static UINT16 _get_3d_brightness_boost_idx(VOID)
{
    UINT16  ui2_idx = 0;

    a_cfg_custom_get_3d_brightness_boost(&ui2_idx);
    return (ui2_idx);
}
#endif

#ifdef DYNAMIC_NATIVE_DIAL_SUPPORT
static VOID _set_dynamic_native_dial(UINT16 ui2_idx)
{
    if (ui2_idx == 1)
    {
        system("touch /data/native_dialserver_run; sync; sync; sync");
    }
    else
    {
        system("rm -f /data/native_dialserver_run; sync; sync; sync");
    }
}

static UINT16 _get_dynamic_native_dial(VOID)
{
    if (access("/data/native_dialserver_run", 0) == 0)
        return 1;
    else
        return 0;
}
#endif

/*Demo Mode start/off  */
#ifdef APP_2K12_RETAIL_DEMO_MODE
static VOID _demo_mode_start(VOID)
{
#ifdef APP_RETAIL_MODE_SUPPORT
    /* pause menu */
    //a_tv_net_send_cmd("\n:am,dtv_app_mtk,:button=MENU\n");

    RETAIL_MODE_PARAM_T t_param;
    c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));

    t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_MENU;
    t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
    t_param.t_launch_info.ui2_count = 15;

    a_nav_retail_mode_start(&t_param);
#endif
    return;
}

static VOID _demo_mode_off(VOID)
{
	/* If retail mode is running,just quit. */
	ACFG_RETAIL_MODE_T	t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
	a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

	if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
	{
        a_nav_retail_mode_exit();
	}
	else if(ACFG_RETAIL_MODE_NO_PLAYING == t_retail_mode)
	{
		a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
	}
	// menu_nav_back();
#ifdef APP_C4TV_SUPPORT
    UINT16      ui2_status    = 0;
    UINT8       ui1_state     = 0;
	a_cfg_get_wzd_status(&ui2_status);
	ui1_state	 = WZD_UTIL_GET_STATUS_STATE(ui2_status);

	if (WZD_STATE_RESUME_C4TV == ui1_state)
	{
	    DBG_LOG_PRINT(("[MENU] Resume wzd when exit demo mode which launch from wzd.\r\n"));
        c_svctx_sync_stop_svc(menu_get_crnt_svctx(), DEFAULT_STOP_SVC_TIMEOUT);
		/* resume wizard*/
		a_wzd_resume_c4tv(ui1_state, 10); //WZD_PAGE_INDEX_C4TV_START_OOBE
	}
#endif
}
#endif
static VOID _set_demo_mode_ctrl_idx(UINT16 ui2_idx)
{
    a_cfg_cust_set_demo_mode_value((UINT8)ui2_idx);
	a_cfg_cust_set_retail_mode_first_time_setting(ACFG_RETAIL_MODE_IS_FIRST_TIME_SETTING);

	if(ui2_idx == 0)
    {
        _demo_mode_off();
    }
    else
    {
        _demo_mode_start();
    }
}

static VOID _action_voice_remote(VOID)
{
    a_nav_ipts_select_virtual_input("SMARTCAST");
    rest_event_notify("app/current", 2, "10");
    menu_leave(FALSE,0);
}

/*
Disabled (default)
Overlay
Enabled
*/
static UINT16 _get_demo_mode_ctrl_idx(VOID)
{
    UINT8	ui1_demo_mode = 0;

    a_cfg_cust_get_demo_mode_value(&ui1_demo_mode);

    return ui1_demo_mode;
}

static VOID _restart_wizard_tuner(VOID)
{
    c_wgl_img_cache_flush();

#ifdef APP_MENU_MMP_COEXIST
    if (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
    {
        a_icl_custom_set_next_resume_app(ICL_CUSTOM_RESUME_NEXT_APP_WZD_TUNER_SETUP);
        a_amb_resume_app(MMP_NAME);
    }
    else
#endif
    {
        a_wzd_resume_tv_setup();
    }

    a_amb_clean_stack();
}

static VOID _restart_wizard_network(VOID)
{
    c_wgl_img_cache_flush();

#ifdef APP_MENU_MMP_COEXIST
    if (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
    {
        a_icl_custom_set_next_resume_app(ICL_CUSTOM_RESUME_NEXT_APP_WZD_NW);
        a_amb_resume_app(MMP_NAME);
    }
    else
#endif
    {
        a_wzd_resume_network_setting();
    }

    a_amb_clean_stack();
}

/* Wi-Fi Remote Setup */
static VOID _restart_wizard_wifi_remote_setup(VOID)
{
#ifdef APP_MENU_MMP_COEXIST
		if (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
		{
			a_icl_custom_set_next_resume_app(ICL_CUSTOM_RESUME_NEXT_APP_WIFI_WZD_RC);
			a_amb_resume_app(MMP_NAME);
		}
		else
#endif
	{
    	c_wgl_img_cache_flush();
		a_wzd_resume_tv_remote_pairing_setup();
	}
	a_amb_clean_stack();
}


/* Wi-Fi Device setup*/
static VOID _restart_wizard_wifi_device_setup(VOID)
{
	c_wgl_img_cache_flush();

#ifdef APP_MENU_MMP_COEXIST
    if (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
    {
        a_icl_custom_set_next_resume_app(ICL_CUSTOM_RESUME_NEXT_APP_WZD_DEVICE_SETUP);
        a_amb_resume_app(MMP_NAME);
    }
    else
#endif
    {
        a_wzd_resume_tv_remote_device_setup();
    }

	a_amb_clean_stack();
}

#ifdef APP_EMANUAL_SUPPORT
static VOID _start_e_manual(VOID)
{
#ifndef APP_CUST_PLT_OPT
    if (a_app_cust_plt_opt())
#endif
    {
        menu_set_start_user_manual_flag(TRUE);
        a_tv_net_send_cmd("\n:am,dtv_app_mtk,:button=MENU\n");
    }
}
#endif

static UINT16 _get_tv_name_idx(VOID)
{
    return 0;
}

static VOID _set_tv_name_idx(UINT16 ui2_idx)
{
    return;
}

static VOID _get_tv_name_text(UINT16 ui2_idx, UTF16_T*  w2s_str, SIZE_T z_len)
{
    INT32                         i4_ret = APP_CFGR_OK;
    CHAR    s_tv_name[MAX_TV_NAME_LEN+1] = {0};
    UINT32                       ui4_len = MAX_TV_NAME_LEN;

    DBG_LOG_PRINT (("\n[menu_tv_name] _get_tv_name_text() z_len[%d]\n",z_len));

    #if 1
    i4_ret = a_cfg_custom_get_tv_name(s_tv_name,&ui4_len);
    #endif

    /* Auto Test tv name *
     *if current TV Name is VIZIOTV,then modify to "aaa" */
    if (APP_CFGR_OK == i4_ret && 0 == c_strcmp(s_tv_name, "VIZIOTV"))
    {
       DBG_CREATE_TEMP_FILE("test_case_tv_name_ok");
    }

    DBG_LOG_PRINT (("\n[menu_tv_name] _get_tv_name_text() s_tv_name[%s],ui4_len[%d]\n",s_tv_name,ui4_len));

    c_uc_ps_to_w2s(s_tv_name, w2s_str, z_len);

    return;
}
/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
BOOL menu_custom_is_aud_stream_enabled(VOID)
{
#ifdef APP_AUD_LANUAGE_CUSTOM_SUPPORT
    if(_get_num_of_audio_stream() == 0)
    {
        return FALSE;
    }
    else
#endif
    {
        return TRUE;
    }
}

INT32 menu_custom_settings_init(VOID)
{
    INT32 i4_ret;

    UINT8   ui1_num_rec=0;

    i4_ret=a_isl_get_num_rec(&ui1_num_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_g_menu_custom_item_input_src, 0, sizeof(MENU_ITEM_T));
    t_g_menu_custom_item_input_src.e_item_type                   = MENU_ITEM_TYPE_LIST;
    t_g_menu_custom_item_input_src.ui2_msgid_title               = MLM_MENU_KEY_INPUT_SOURCE;
    t_g_menu_custom_item_input_src.ui2_msgid_desc                = MLM_MENU_KEY_INPUT_SOURCE_SEL_HELP;
    t_g_menu_custom_item_input_src.u.t_list.ui2_elem_num         = ui1_num_rec;
    t_g_menu_custom_item_input_src.u.t_list.pf_set_idx           = _set_input_source_idx;
    t_g_menu_custom_item_input_src.u.t_list.pf_get_idx           = _get_input_source_idx;
    t_g_menu_custom_item_input_src.u.t_list.pf_next_idx          = _next_input_source_idx;
    t_g_menu_custom_item_input_src.u.t_list.pf_prev_idx          = _prev_input_source_idx;
    t_g_menu_custom_item_input_src.u.t_list.pf_get_text          = _get_input_source_text;
    t_g_menu_custom_item_input_src.u.t_list.ui2_msgid_elem_first = MLM_MENU_KEY_EMPTY;
    t_g_menu_custom_item_input_src.u.t_list.ui2_msgid_elem_last  = MLM_MENU_KEY_EMPTY;

    /* GUI Language */
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_gui_lang,
                                         MLM_MENU_KEY_OSD_LANG,
                                         MLM_MENU_KEY_HELP_TIP_TV_SETTING_GUI_LANG,
                                         MLM_MENU_KEY_OSD_LANG + 1,
                                         MLM_MENU_KEY_OSD_LANG + MLM_MENU_NUM_LANG ,
                                         _set_gui_lang_idx,
                                         _get_gui_lang_idx);
    MENU_CHK_FAIL(i4_ret);


#ifdef APP_2K12_RETAIL_DEMO_MODE
    /*Menu Help Demo Mode */
    c_memset(&t_menu_item_page_demo_mode_start, 0, sizeof(MENU_ITEM_T));

       /*
        MLM_MENU_KEY_DEMO_MODE_START,
                                        MLM_MENU_KEY_DEMO_MODE_START_HELP,
       */
    i4_ret = menu_page_tree_action_item(
                                        &t_menu_item_page_demo_mode_start,
                                        MLM_MENU_KEY_DEMO_MODE_START,
                                        MLM_MENU_KEY_DEMO_MODE_START_OVERLAY_HELP,
                                        MLM_MENU_KEY_EMPTY,
                                        _demo_mode_start);

    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_menu_item_page_demo_mode_off, 0, sizeof(MENU_ITEM_T));

    i4_ret = menu_page_tree_action_item(
                                        &t_menu_item_page_demo_mode_off,
                                        MLM_MENU_KEY_DEMO_MODE_OFF,
                                        MLM_MENU_KEY_DEMO_MODE_OFF_HELP,
                                        MLM_MENU_KEY_EMPTY,
                                        _demo_mode_off);

    MENU_CHK_FAIL(i4_ret);

	i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_demo_mode,
									  MLM_MENU_KEY_DEMO_MODE,
									  MLM_MENU_KEY_DEMO_MODE_HELP,
									  MLM_MENU_KEY_DEMO_MODE_2K20_OFF,
									  MLM_MENU_KEY_DEMO_MODE_2K20_DEMO2,
									  _set_demo_mode_ctrl_idx,
									  _get_demo_mode_ctrl_idx);
	MENU_CHK_FAIL(i4_ret);

#endif


    /* Audio Language */
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_aud_lang,
                                         MLM_MENU_KEY_AUD_DIGITAL_PREFERENCE,
                                         MLM_MENU_KEY_HELP_TIP_AUD_LANG,
                                         MLM_MENU_KEY_AUD_LANG + 1,
                                         MLM_MENU_KEY_AUD_LANG + MLM_MENU_NUM_LANG ,
                                         _set_aud_lang_idx,
                                         _get_aud_lang_idx);
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_AUD_LANUAGE_CUSTOM_SUPPORT
	t_g_menu_custom_item_aud_lang.u.t_list.ui2_elem_num = (UINT16)(8);
    t_g_menu_custom_item_aud_lang.u.t_list.pf_set_idx   = _set_audio_stream_idx;
    t_g_menu_custom_item_aud_lang.u.t_list.pf_get_idx   = _get_audio_stream_idx;
    t_g_menu_custom_item_aud_lang.u.t_list.pf_next_idx  = _next_audio_stream_idx;
    t_g_menu_custom_item_aud_lang.u.t_list.pf_prev_idx  = _prev_audio_stream_idx;
    t_g_menu_custom_item_aud_lang.u.t_list.pf_get_text  = _get_audio_stream_text;
#endif

    /* Time Zone */
    i4_ret = menu_page_tree_listbox_item(&t_g_menu_custom_item_time_zone,
                                         MLM_MENU_KEY_TIME_ZONE,
                                         MLM_MENU_KEY_HELP_TIP_TV_SETTING_SET_TZ,
                                         MLM_MENU_KEY_TIME_ZONE_NF,
                                         MLM_MENU_KEY_TIME_ZONE_ARI,
                                         _set_time_zone_idx,
                                         _get_time_zone_idx);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_listbox_item_set_elem_help_tip(&t_g_menu_custom_item_time_zone,
                                                           TRUE,
                                                           MLM_MENU_KEY_TIME_ZONE_NF,
                                                           MLM_MENU_KEY_TIME_ZONE_ARI);
    MENU_CHK_FAIL(i4_ret);

    /* Daylight saving */
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_time_dls,
                                      MLM_MENU_KEY_TIME_DLS,
                                      MLM_MENU_KEY_HELP_TIP_TV_SETTING_SET_DAYLIGHT_SAV,
                                      MLM_MENU_KEY_DISABLE,
                                      MLM_MENU_KEY_ENABLE,
                                      _set_dls_idx,
                                      _get_dls_idx);
    MENU_CHK_FAIL(i4_ret);

    /* dt sync mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_auto_update_time,
                                      MLM_MENU_KEY_TV_AUTO_UPDATE_TIME,
                                      MLM_MENU_KEY_HELP_TIP_TV_SETTING_AUTO_UPDATE,
                                      MLM_MENU_KEY_DISABLE,
                                      MLM_MENU_KEY_ENABLE,
                                      _set_auto_update_time_idx,
                                      _get_auto_update_time_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Block Unrated */
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_block_unrated,
                                      MLM_MENU_KEY_BLOCK_UNRATED,
                                      MLM_MENU_KEY_HELP_TIP_PARENT_BLOCK_UNRATE,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_block_unrated_idx,
                                      _get_block_unrated_idx);
    MENU_CHK_FAIL(i4_ret);

    /* VGA Color Temp. */
    i4_ret = menu_page_tree_listbox_item(&t_g_menu_custom_item_vga_clr_tmp_mode,
                                         MLM_MENU_KEY_VID_CLR_TEMP,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_VID_CLR_TEMP_COOL,
                                         MLM_MENU_KEY_VID_CLR_TEMP_USER,
                                         _set_vga_clr_tmp_mode_idx,
                                         _get_vga_clr_tmp_mode_idx);
    MENU_CHK_FAIL(i4_ret);


    i4_ret = menu_page_tree_listbox_item_set_elem_help_tip(&t_g_menu_custom_item_vga_clr_tmp_mode,
                                                           TRUE,
                                                           MLM_MENU_KEY_VID_CLR_TEMP_COOL,
                                                           MLM_MENU_KEY_VID_CLR_TEMP_USER);
    MENU_CHK_FAIL(i4_ret);

    t_g_menu_custom_item_vga_clr_tmp_mode.u.t_listbox.pf_is_subpage = _is_vga_clr_tmp_subpage;

    /* Adaptive Backlight */
    if ((a_cfg_custom_odm_is_dcr_support() == FALSE))
    {
        //Fix Coverity ID : 4490634 Unused value
        i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_vid_dcr,
                              MLM_MENU_KEY_VID_BACK_LIGHT_CTRL,
                              MLM_MENU_KEY_HELP_VID_BACK_LIGHT_CTRL,
                              MLM_MENU_KEY_VID_BACK_LIGHT2_CTRL_OFF,
                              MLM_MENU_KEY_VID_BACK_LIGHT2_CTRL_OPC,
                              _set_vid_dcr_idx,
                              _get_vid_dcr_idx);
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_vid_dcr,
                                          MLM_MENU_KEY_VID_BACK_LIGHT_CTRL,
                                          MLM_MENU_KEY_HELP_VID_BACK_LIGHT_CTRL,
                                          MLM_MENU_KEY_VID_BACK_LIGHT_CTRL_OFF,
                                          MLM_MENU_KEY_VID_BACK_LIGHT_CTRL_OPC,
                                          _set_vid_dcr_idx,
                                          _get_vid_dcr_idx);
        MENU_CHK_FAIL(i4_ret);
    }

    /* Light Sensor */
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_vid_lit_sns,
                                      MLM_MENU_KEY_VID_AMBIENT_LIGHT_SENSOR,
                                      MLM_MENU_KEY_HELP_TIP_PICTURE_LIGHT_SENSOR,
                                      MLM_MENU_KEY_VID_LIT_SNS_OFF,
                                      MLM_MENU_KEY_VID_LIT_SNS_HIGH,
                                      _set_vid_auto_brightness_control_idx,
                                      _get_vid_auto_brightness_control_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Picture Gamma*/
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_gamma,
                                      MLM_MENU_KEY_VID_GAMMA,
                                      MLM_MENU_KEY_HELP_TIP_VID_GAMMA,
                                      MLM_MENU_KEY_ITME_VID_GAMMA_1_8,
                                      MLM_MENU_KEY_ITME_VID_GAMMA_2_4,
                                      _set_vid_gamma_idx,
                                      _get_vid_gamma_idx);

   /* Closed Caption : On/Off */
   i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_cc_enabled,
                                        MLM_MENU_KEY_MENU_ITEM_CC_ENABLED,
                                        MLM_MENU_KEY_HELP_TIP_CAPTION,
                                        MLM_MENU_KEY_MENU_ITEM_CC_ENABLED_OFF,
                                        MLM_MENU_KEY_MENU_ITEM_CC_ENABLED_ON,
                                        _set_cc_on_off,
                                        _get_cc_on_off);
    MENU_CHK_FAIL(i4_ret);
#if 0
    t_g_menu_custom_item_cc_enabled.e_item_type                   = MENU_ITEM_TYPE_LIST;
    t_g_menu_custom_item_cc_enabled.ui2_msgid_title               = MLM_MENU_KEY_CC_ANA;
    t_g_menu_custom_item_cc_enabled.ui2_msgid_desc                = MLM_MENU_KEY_HELP_TIP_CAPTION_ACC;
    t_g_menu_custom_item_cc_enabled.u.t_list.ui2_elem_num         = (UINT16)(MLM_MENU_KEY_CC_ANA_CC4 - MLM_MENU_KEY_CC_ANA_OFF+1);
    t_g_menu_custom_item_cc_enabled.u.t_list.pf_set_idx           = _set_cc_on_off;
    t_g_menu_custom_item_cc_enabled.u.t_list.pf_get_idx           = _get_cc_on_off;
    t_g_menu_custom_item_cc_enabled.u.t_list.pf_next_idx          = _next_audio_stream_idx;
    t_g_menu_custom_item_cc_enabled.u.t_list.pf_prev_idx          = _prev_audio_stream_idx;
#endif

    /* Closed Caption : analog */
   i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_cc_ana,
                                        MLM_MENU_KEY_CC_ANA,
                                        MLM_MENU_KEY_HELP_TIP_CAPTION_ACC,
                                        MLM_MENU_KEY_CC_ANA_CC1,
                                        MLM_MENU_KEY_CC_ANA_CC4,
                                        _set_ana_cc_idx,
                                        _get_ana_cc_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Closed Caption : digital */
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_cc_dig,
                                         MLM_MENU_KEY_CC_DIG,
                                         MLM_MENU_KEY_HELP_TIP_CAPTION_DCC,
                                         MLM_MENU_KEY_CC_DIG_SVC1,
                                         MLM_MENU_KEY_CC_DIG_SVC6,
                                         _set_dig_cc_idx,
                                         _get_dig_cc_idx);
    MENU_CHK_FAIL(i4_ret);

    /* H Size */
    i4_ret = menu_page_tree_range_item(&t_g_menu_custom_item_vid_size_h,
                                       MLM_MENU_KEY_H_SIZE,
                                       MLM_MENU_KEY_HELP_H_SIZE,
                                       0,
                                       100,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_size_h_val,
                                       _get_vid_size_h_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_custom_item_vid_size_h.u.t_range.pf_incr = NULL;
    t_g_menu_custom_item_vid_size_h.u.t_range.pf_decr = NULL;

    /* V Size */
    i4_ret = menu_page_tree_range_item(&t_g_menu_custom_item_vid_size_v,
                                       MLM_MENU_KEY_V_SIZE,
                                       MLM_MENU_KEY_HELP_V_SIZE,
                                       0,
                                       100,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_size_v_val,
                                       _get_vid_size_v_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_custom_item_vid_size_v.u.t_range.pf_incr = NULL;
    t_g_menu_custom_item_vid_size_v.u.t_range.pf_decr = NULL;

    /* CC On Mute */
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_cc_on_mute,
                                      MLM_MENU_KEY_CC_ON_MUTE,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_cc_on_mute_idx,
                                      _get_cc_on_mute_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Treble */
    t_g_menu_common_item_aud_treble.u.t_range.b_fast_mode = FALSE;

    /* Bass */
    t_g_menu_common_item_aud_bass.u.t_range.b_fast_mode = FALSE;

    /* additional scan */
    i4_ret = menu_page_tree_list_item (&t_g_menu_custom_item_lst_additional_scan,
                                       MLM_MENU_KEY_ADDITIONAL_SCAN,
                                       MLM_MENU_KEY_HELP_TIP_TV_SETTING_ADDITIONAL_SCAN,
                                       MLM_MENU_KEY_OFF,
                                       MLM_MENU_KEY_ON,
                                       _set_additional_scan,
                                       _get_additional_scan);
    MENU_CHK_FAIL(i4_ret);

    /* analog audio out*/
    i4_ret = menu_page_tree_list_item (&t_g_menu_custom_item_ana_aud_out,
                                       MLM_MENU_KEY_AUD_LINEOUT,
                                       MLM_MENU_KEY_HELP_AUD_LINEOUT,
                                       MLM_MENU_KEY_AUD_LINEOUT_FIXED,
                                       MLM_MENU_KEY_AUD_LINEOUT_VARIABLE,
                                       _set_ana_aud_out_idx,
                                       _get_ana_aud_out_idx);
    MENU_CHK_FAIL(i4_ret);

    /* channel scan */
    i4_ret = menu_page_tree_listbox_item (&t_g_menu_custom_item_ch_scan,
                                          MLM_MENU_KEY_SCAN_CHANNELS,
                                          MLM_MENU_KEY_HELP_TIP_TV_SETTING_PARTIAL_SCAN,
                                          MLM_MENU_KEY_OFF,
                                          MLM_MENU_KEY_ON,
                                          _set_ch_scan,
                                          _get_ch_scan);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_listbox_item_set_elem_help_tip(&t_g_menu_custom_item_ch_scan,
                                                           TRUE,
                                                           MLM_MENU_KEY_OFF,
                                                           MLM_MENU_KEY_ON);
    MENU_CHK_FAIL(i4_ret);

    /* Parental Control - Reset Lock */
    i4_ret = menu_page_tree_listbox_item(&t_g_menu_custom_item_reset_channel_lock,
                                         MLM_MENU_KEY_RESET_LOCK,
                                         MLM_MENU_KEY_HELP_TIP_PARENT_RESET_PARENTAL,
                                         MLM_MENU_KEY_NO,
                                         MLM_MENU_KEY_YES,
                                         _set_reset_channel_lock_idx,
                                         _get_reset_channel_lock_idx);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_listbox_item_set_elem_help_tip(&t_g_menu_custom_item_reset_channel_lock,
                                                           TRUE,
                                                           MLM_MENU_KEY_NO,
                                                           MLM_MENU_KEY_YES);
    MENU_CHK_FAIL(i4_ret);

    /* Guide Help */
    c_memset(&t_menu_item_page_tuner_setup, 0, sizeof(MENU_ITEM_T));

    i4_ret = menu_page_tree_action_item(&t_menu_item_page_tuner_setup,
                                        MLM_MENU_KEY_HELP_TUNER_SETUP,
                                        MLM_MENU_KEY_TAB_HELP_TUNER_SETUP_WZD,
                                        MLM_MENU_KEY_EMPTY,
                                        _restart_wizard_tuner);

    MENU_CHK_FAIL(i4_ret);

    #ifdef APP_EMANUAL_SUPPORT
    i4_ret = menu_page_tree_action_item(&t_menu_item_page_manual,
                                    MLM_MENU_KEY_HELP_MANUAL,
                                    MLM_MENU_KEY_HELP_MANUAL_HELP,
                                    MLM_MENU_KEY_EMPTY,
                                    _start_e_manual);
    MENU_CHK_FAIL(i4_ret);
    #endif

    c_memset(&t_menu_item_page_network_setup, 0, sizeof(MENU_ITEM_T));

    i4_ret = menu_page_tree_action_item(&t_menu_item_page_network_setup,
                                        MLM_MENU_KEY_HELP_NETWORK_SETUP,
                                        MLM_MENU_KEY_TAB_HELP_NETWORK_SETUP_WZD,
                                        MLM_MENU_KEY_EMPTY,
                                        _restart_wizard_network);

    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_action_item(&t_menu_item_voice_remote,
                                        MLM_MENU_KEY_REMOTE_CONTROL,
                                        MLM_MENU_KEY_REMOTE_PAIRING_TIP,
                                        MLM_MENU_KEY_EMPTY,
                                        _action_voice_remote);

    MENU_CHK_FAIL(i4_ret);

    if (a_cfg_custom_get_wifi_remote_support())
    {
    	c_memset(&t_menu_item_page_wifi_remote_setup, 0, sizeof(MENU_ITEM_T));

        i4_ret = menu_page_tree_action_item(&t_menu_item_page_wifi_remote_setup,
                                            MLM_MENU_KEY_HELP_REMOTE_SETUP,
                                            MLM_MENU_KEY_TAB_HELP_REMOTE_SETUP_WZD,
                                            MLM_MENU_KEY_EMPTY,
                                            _restart_wizard_wifi_remote_setup);

        MENU_CHK_FAIL(i4_ret);

    	c_memset(&t_menu_item_page_wifi_device_setup, 0, sizeof(MENU_ITEM_T));

    	i4_ret = menu_page_tree_action_item(&t_menu_item_page_wifi_device_setup,
    										   MLM_MENU_KEY_HELP_DEVICE_SETUP,
    										   MLM_MENU_KEY_TAB_HELP_DEVICE_SETUP_WZD,
    										   MLM_MENU_KEY_EMPTY,
    										   _restart_wizard_wifi_device_setup);


	    MENU_CHK_FAIL(i4_ret);
    }

    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_lst_acr,
                                      MLM_MENU_KEY_ITEM_ACR_SETTING,
                                      MLM_MENU_KEY_HELP_TIP_ACR,
                                      MLM_MENU_KEY_OFF_1,
                                      MLM_MENU_KEY_ON_1,
                                      _set_acr_idx,
                                      _get_acr_idx);

    /* limited ad tracking */
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_limited_ad_tracking,
                                      MLM_MENU_KEY_LIMITED_AD_TRACKING,
                                      MLM_MENU_KEY_LIMITED_AD_TRACKING_TIP,
                                      MLM_MENU_KEY_STATE_ONE_ON,
                                      MLM_MENU_KEY_STATE_ONE_OFF,
                                      menu_custom_set_limited_ad_tracking_idx,
                                      menu_custom_get_limited_ad_tracking_idx);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_dynamic_content,
                                      MLM_MENU_KEY_DYNAMIC_CONTENT,
                                      MLM_MENU_KEY_DYNAMIC_CONTENT_TIP,
                                      MLM_MENU_KEY_STATE_ONE_ON,
                                      MLM_MENU_KEY_STATE_ONE_OFF,
                                      menu_custom_set_dynamic_content_idx,
                                      menu_custom_get_dynamic_content_idx);


#ifdef APP_MENU_CUSTOM_FACTORY_TREE
	i4_ret = menu_cust_fac_settings_init();
	MENU_CHK_FAIL(i4_ret);
#endif

#ifdef APP_MENU_3D_BRIGHTNESS_BOOST
	i4_ret = menu_page_tree_list_item(&t_g_menu_item_3d_brightness_boost,
                                      MLM_MENU_KEY_MENU_ITEM_3D_BRIGHTNESS_BOOST,
                                      MLM_MENU_KEY_MENU_ITEM_3D_BRIGHTNESS_BOOST,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_3d_brightness_boost_idx,
                                      _get_3d_brightness_boost_idx);
	MENU_CHK_FAIL(i4_ret);
#endif

    MENU_ITEM_SELECTION_LIST_INIT_T t_item_tv_name_init = {0};
    t_item_tv_name_init.pf_get_idx = _get_tv_name_idx;
    t_item_tv_name_init.pf_get_text = _get_tv_name_text;
    t_item_tv_name_init.pf_next_idx = NULL;
    t_item_tv_name_init.pf_prev_idx = NULL;
    t_item_tv_name_init.pf_set_idx = _set_tv_name_idx;
    t_item_tv_name_init.ui2_msgid_elem_first = 0;
    t_item_tv_name_init.ui2_msgid_elem_last = 0;

    menu_page_tree_select_list_subpage_item(&t_g_menu_item_page_tv_name,
                                            MLM_MENU_KEY_ITEM_TV_NAME,
                                            &t_item_tv_name_init);
    t_g_menu_item_page_tv_name.u.t_list_subpage.pf_get_text = _get_tv_name_text;

#ifdef DYNAMIC_NATIVE_DIAL_SUPPORT
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_native_dial,
                                      MLM_MENU_KEY_MENU_ITEM_NATIVE_DIAL,
                                      MLM_MENU_KEY_MENU_ITEM_NATIVE_DIAL,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_dynamic_native_dial,
                                      _get_dynamic_native_dial);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifdef APP_SUPPORT_STR_CORE_OFF
    /* Fast Boot */
    if(a_cfg_cust_get_support_energy_start_by_mode_name())
    {
        i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_fast_boot,
                                          MLM_MENU_KEY_POWER_MODE,
                                          MLM_MENU_KEY_POWER_MODE_HELP,
                                          MLM_MENU_KEY_POWER_MODE_ECO,
                                          MLM_MENU_KEY_POWER_MODE_QUICK,
                                          _set_fast_boot_mode_idx,
                                          _get_fast_boot_mode_idx);
    }
    else
    {
        i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_fast_boot,
                                  MLM_MENU_KEY_POWER_MODE,
                                  MLM_MENU_KEY_POWER_MODE_HELP_NO_ENERGY_START,
                                  MLM_MENU_KEY_POWER_MODE_ECO,
                                  MLM_MENU_KEY_POWER_MODE_QUICK,
                                  _set_fast_boot_mode_idx,
                                  _get_fast_boot_mode_idx);
    }
    MENU_CHK_FAIL(i4_ret);

#endif

    MENU_DEBUG_ASPECT_RATIO( DBG_LOG_PRINT(("[MENU][ASPECT]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    t_g_menu_custom_item_aspect_ratio.e_item_type = MENU_ITEM_TYPE_LIST;
    t_g_menu_custom_item_aspect_ratio.ui2_msgid_title = MLM_MENU_KEY_MENU_ASPECT_RATIO;
    t_g_menu_custom_item_aspect_ratio.ui2_msgid_desc = MLM_MENU_KEY_MENU_ASPECT_RATIO_HELP_TEXT;
    t_g_menu_custom_item_aspect_ratio.u.t_list.ui2_elem_num = (MLM_MENU_KEY_SCREEN_MODE_STRETCH-MLM_MENU_KEY_SCREEN_MODE_NORMAL+1);
    t_g_menu_custom_item_aspect_ratio.u.t_list.pf_get_idx = _get_menu_aspect_ratio_idx;
    t_g_menu_custom_item_aspect_ratio.u.t_list.pf_get_text = _get_menu_aspect_ratio_text;
    t_g_menu_custom_item_aspect_ratio.u.t_list.pf_next_idx = _next_menu_aspect_ratio_idx;
    t_g_menu_custom_item_aspect_ratio.u.t_list.pf_prev_idx = _prev_menu_aspect_ratio_idx;

#ifdef APP_NETWORK_SUPPORT
	/* wake on lan */
#ifdef APP_WAKE_ON_LAN_ENABLE_UI
	i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_wake_on_lan,
								  MLM_MENU_KEY_WAKE_ON_LAN_CFG,
								  MLM_MENU_KEY_WAKE_ON_LAN_CFG,
								  MLM_MENU_KEY_OFF,
								  MLM_MENU_KEY_ON,
								  _set_wake_on_lan_idx,
								  _get_wake_on_lan_idx);
	MENU_CHK_FAIL(i4_ret);

#endif

#ifdef APP_NETWORK_WIFI_SUPPORT
//#ifdef APP_WAKE_ON_WLAN_ENABLE_UI
	i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_wake_on_wlan,
								  MLM_MENU_KEY_WAKE_ON_WLAN_CFG,
								  MLM_MENU_KEY_WAKE_ON_WLAN_CFG,
								  MLM_MENU_KEY_OFF,
								  MLM_MENU_KEY_ON,
								  _set_wake_on_wlan_idx,
								  _get_wake_on_wlan_idx);
	MENU_CHK_FAIL(i4_ret);
//#endif
#endif
#endif

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:  menu_custom_is_channel_blocked
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL menu_custom_is_channel_blocked (VOID)
{
    INT32       i4_rc;
    UINT16      ui2_rec_num = 0;
    UINT16      ui2_rec_idx;
    UINT32      ui4_ver_id;
    SVL_REC_T   t_svl_rec;
    BOOL        b_again;
    HANDLE_T    h_crnt_svl;

    /* check the block status of the channels */
    h_crnt_svl = menu_get_crnt_svl();
    if (h_crnt_svl == NULL_HANDLE)
    {
        return FALSE;
    }

    /* This loop is used for redo the iteration when somebody modify the SVL
       during our iteration. */
    ui4_ver_id = SVL_NULL_VER_ID;
    do
    {
        b_again = FALSE;

        i4_rc = c_svl_get_num_rec_by_brdcst_type(h_crnt_svl,
                                                 BRDCST_TYPE_UNKNOWN,
                                                 SB_VNET_ACTIVE,
                                                 & ui2_rec_num,
                                                 & ui4_ver_id);
        if (i4_rc != SVLR_OK)
        {
            return FALSE;
        }

        for(ui2_rec_idx = 0; ui2_rec_idx < ui2_rec_num; ui2_rec_idx++)
        {
            i4_rc = c_svl_get_rec_by_brdcst_type(h_crnt_svl,
                                                 BRDCST_TYPE_UNKNOWN,
                                                 SB_VNET_ACTIVE,
                                                 ui2_rec_idx,
                                                 & t_svl_rec,
                                                 & ui4_ver_id);
            if (i4_rc == SVLR_MODIFIED)
            {
                DBG_INFO(("<PHM> Somebody modifed the SVL.\r\n"));
                b_again = TRUE;
                break;
            }
            else if(i4_rc != SVLR_OK)
            {
                DBG_ERROR(("<PHM> Can't iterate service list at idx [%d].\r\n", ui2_rec_idx));
                return FALSE;
            }

            /* ignore the FAKE channels */
            if (SB_VNET_ACTIVE != ((SB_VNET_ACTIVE | SB_VNET_FAKE) & t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask))
            {
                continue;
            }

            /* channel block */
            if (t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_BLOCKED)
            {
                return TRUE;
            }
        }
    } while (b_again);

    /* no channel lock */
    return FALSE;
}

VOID menu_reset_audio_stream(VOID)
{
#ifdef APP_AUD_LANUAGE_CUSTOM_SUPPORT
    ui2_g_audio_stream_idx = 0;
#endif

    #ifdef APP_PIP_SETTINGS_IN_MENU
    _reset_pip_aud_src();
    #endif

#ifdef APP_MENU_MMP_COEXIST
    if ((a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED) ||
        (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC))
#else
    if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
#endif
    {
        a_cfg_set_fire_nfy_switch(FALSE);
#ifdef APP_AUD_LANUAGE_CUSTOM_SUPPORT
        _set_audio_stream_idx(0);
#endif
        _set_aud_lang_idx(0);
        a_cfg_set_fire_nfy_switch(TRUE);
    }
    else
    {
#ifdef APP_AUD_LANUAGE_CUSTOM_SUPPORT
        _set_audio_stream_idx(0);
#endif
        _set_aud_lang_idx(0);
    }
}

UINT16 menu_custom_get_aud_lang_num(VOID)
{
#ifdef APP_AUD_LANUAGE_CUSTOM_SUPPORT
    return _get_num_of_audio_stream();
#else
    return 3;
#endif
}

