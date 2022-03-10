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
 * $RCSfile: menu_common.h,v $
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

#ifndef _MENU_COMMON_H_
#define _MENU_COMMON_H_


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_handle.h"
#include "u_sys_name.h"
#include "u_sb.h"
#include "u_time_msrt.h"

#include "app_util/a_network.h"
#include "app_util/a_ui.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_page_tree.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_common/menu_common_simple_dialog.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct _MENU_COMMON_T {
    HANDLE_T        h_svl_air;         /* ATSC AIR */
    HANDLE_T        h_tsl_air;         /* ATSC AIR */
    HANDLE_T        h_svl_cable;         /* ClearQAM Cable */
    HANDLE_T        h_tsl_cable;         /* ClearQAM Cable */
    HANDLE_T        h_nwl_air ;          /* NWL air */
    HANDLE_T        h_lol_air ;          /* LOL air */
#ifdef APP_DVBC_SUPPORT
    HANDLE_T        h_nwl_cable ;        /*  NWL cable */
    HANDLE_T        h_lol_cable ;        /*  LOL cable */
#endif
    HANDLE_T        h_svctx;             /* SVCTX handle for MAIN */
    HANDLE_T        h_svctx_sub;         /* SVCTX handle for SUB  */
    HANDLE_T        h_scan_svctx;        /* SVCTX handle used in scan for MAIN  */
    HANDLE_T        h_scan_svctx_sub;    /* SVCTX handle used in scan for SUB  */
    HANDLE_T        h_scc_aud;
    BOOL            b_tsl_air_dirty;
    BOOL            b_svl_air_dirty;
    BOOL            b_tsl_cable_dirty;
    BOOL            b_svl_cable_dirty;
    BOOL            b_dual_bank_dirty;
    BOOL            b_cfg_dirty;        /* if config is dirty */
    BOOL            b_src_dirty;        /* if tuner source is changed */
    BOOL            b_is_pausing;       /* Indicate that it is pausing now */
    BOOL            b_is_hot_key_enter;
    UINT32          ui4_key_code;
} MENU_COMMON_T;

/* channel list 2 page */
typedef struct _MENU_COMMON_CHANNEL_LIST_INIT_T{
    UINT16              ui2_msg_title;
    UINT32              ui4_lst_mask;
    UINT32              ui4_sel_mask;
    BRDCST_TYPE_T       e_brdcst_type;  /* BRDCST_TYPE_UNKNOWN to list all the broadcast type */
    WGL_HIMG_TPL_T      h_img_normal;
    WGL_HIMG_TPL_T      h_img_selected;
    WGL_HIMG_TPL_T      h_img_highlight;
    WGL_HIMG_TPL_T      h_img_selected_highlight;
    UINT16              ui2_max_rec_num;
    BOOL                b_scroll;       /* TRUE, then turns off the listbox
                                           WGL_STL_LB_NO_SCROLL style */
    BOOL                b_wrap_over;    /* TRUE, then turns off the listbox
                                           WGL_STL_LB_NO_WRAP_OVER */
    BOOL                b_back_on_left; /* Back to previous page by
                                           BTN_CURSOR_LEFT */
}MENU_COMMON_CHANNEL_LIST_INIT_T;

/* Enum of the picture mode items*/
typedef enum
{
	PQ_ITEMS_CHECK_NONE  = 0,
	NO_NEED_CREATE_A_NEW_PICTURE_MODE,  					/*cust picture modes areenough*/
	NEED_CREATE_A_NEW_PICTURE_MODE, 						/*cust picture modes are not enough*/
	CUST_PIC_MODE_LOCKED_AND_DELAY_LOCK,					/*cust picture modes are locked*/
	CUST_PIC_MODE_LOCKED_AND_NO_DELAY_LOCK,					/*cust picture modes are in delay lock state,still can adjust the pq settings */
	CUST_PIC_MODE_NOT_LOCKED								/*cust picture modes are not locked*/
}PQ_ITEMS_CHECK;

typedef enum _CHIPSET
{
    CHIPSET_UNKNOW,
    CHIPSET_5691,
    CHIPSET_5695,
    CHIPSET_5583,
    CHIPSET_5695L
} CHIPSET;

typedef enum _POWER_ON_INPUT
{
    E_POWER_ON_INP_AUTOMATIC,
    E_POWER_ON_INP_SMARTCAST,
    E_POWER_ON_INP_HDMI1,
    E_POWER_ON_INP_HDMI2,
    E_POWER_ON_INP_HDMI3,
    E_POWER_ON_INP_HDMI4,
    E_POWER_ON_INP_PREVIOUS_INPUT,
    E_POWER_ON_INP_AIRPLAY,
    E_POWER_ON_INP_ANTENNA,
    E_POWER_ON_INP_COMPOSITE,
    E_POWER_ON_INP_NUM_DEVICES
} Enu_POWER_ON_INPUT;


typedef struct _MENU_VER_ULI_INFO
{
    CHAR   str_reg[8];
    CHAR   str_np[8];
    CHAR   str_uid[32];
    CHAR   str_dev_id[9];
    CHAR   str_prov_id[9];
    CHAR   str_esn[16];
    CHAR   str_device_agent[32];
    CHAR   str_sv[32];
} MENU_VER_ULI_INFO;



#define MENU_SLIDER_BAR_OFFSET_X                (30)
#define MENU_SLIDER_BAR_OFFSET_Y                (-10)
#define MENU_CUST_PIC_MODE_NAME_MAX_LEN			(16)
#define MENU_PRESET_PIC_MODE_NAME_LEN        (32)
#define MENU_PRESET_PIC_MODE_NAME_TITLE_LEN  (32)
#define MENU_PIC_MODE_EDIT_DLG_TEXT_LEN      (128)



/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
extern MENU_COMMON_T        t_g_menu_common;
extern BOOL                 t_g_menu_is_scanning;
extern BOOL                 t_g_menu_enable_channel_change;

/* settings definition */
extern MENU_ITEM_T          t_g_menu_common_item_scan_mode;
extern MENU_ITEM_T          t_g_menu_common_item_tv_ar;
extern MENU_ITEM_T          t_g_menu_common_item_dolby_mode;
extern MENU_ITEM_T          t_g_menu_common_item_drc;
extern MENU_ITEM_T          t_g_menu_common_item_cmpss;
extern MENU_ITEM_T          t_g_menu_common_item_dmix;
extern MENU_ITEM_T          t_g_menu_common_item_aud_bypass_mode;
extern MENU_ITEM_T          t_g_menu_common_item_agc;
extern MENU_ITEM_T          t_g_menu_common_item_aud_latency;

/* Video */
extern MENU_ITEM_T          t_g_menu_common_item_vid_pic_mode;
extern MENU_ITEM_T          t_g_menu_common_item_vid_bri;
extern MENU_ITEM_T          t_g_menu_common_item_vid_cnt;
extern MENU_ITEM_T          t_g_menu_common_item_vid_sat;
extern MENU_ITEM_T          t_g_menu_common_item_vid_hue;
extern MENU_ITEM_T          t_g_menu_common_item_vid_shp;
extern MENU_ITEM_T          t_g_menu_common_item_vid_back_light;
extern MENU_ITEM_T          t_g_menu_common_item_vid_tone_mapping;
extern MENU_ITEM_T          t_g_menu_common_item_vid_oled_luminance;
extern MENU_ITEM_T          t_g_menu_common_item_vid_adp_back_light;
extern MENU_ITEM_T          t_g_menu_common_item_vid_gamma;
extern MENU_ITEM_T          t_g_menu_common_item_vid_clr_tmp_mode;
extern MENU_ITEM_T			t_g_menu_common_item_vid_clear_action;
extern MENU_ITEM_T          t_g_menu_common_item_vid_clr_gain_r;
extern MENU_ITEM_T          t_g_menu_common_item_vid_clr_gain_g;
extern MENU_ITEM_T          t_g_menu_common_item_vid_clr_gain_b;
extern MENU_ITEM_T          t_g_menu_common_item_vid_clr_offset_r;
extern MENU_ITEM_T          t_g_menu_common_item_vid_clr_offset_g;
extern MENU_ITEM_T          t_g_menu_common_item_vid_clr_offset_b;

extern MENU_ITEM_T          t_g_menu_common_item_vid_11_points_gamma_level;
extern MENU_ITEM_T          t_g_menu_custom_item_fac_11_points_gamma_r;
extern MENU_ITEM_T          t_g_menu_custom_item_fac_11_points_gamma_g;
extern MENU_ITEM_T          t_g_menu_custom_item_fac_11_points_gamma_b;
extern MENU_ITEM_T     		t_g_menu_common_item_fac_gamma_key_all;
extern MENU_ITEM_T     		t_g_menu_common_item_fac_gamma_key_cool;
extern MENU_ITEM_T     		t_g_menu_common_item_fac_gamma_key_normal;
extern MENU_ITEM_T     		t_g_menu_common_item_fac_gamma_key_computer;


extern MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_gain_r;
extern MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_gain_g;
extern MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_gain_b;
extern MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_offset_r;
extern MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_offset_g;
extern MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_offset_b;
extern MENU_ITEM_T          t_g_menu_common_item_vid_blur;
extern MENU_ITEM_T          t_g_menu_common_item_vid_dnr;
extern MENU_ITEM_T          t_g_menu_common_item_vid_mpeg_nr;
extern MENU_ITEM_T          t_g_menu_common_item_vid_flesh_tone;
extern MENU_ITEM_T          t_g_menu_common_item_vid_alc;
extern MENU_ITEM_T          t_g_menu_common_item_vid_scr_mode;
extern MENU_ITEM_T          t_g_menu_common_item_vid_ypbpr_phase;
extern MENU_ITEM_T          t_g_menu_common_item_vid_pos_h;
extern MENU_ITEM_T          t_g_menu_common_item_vid_pos_v;
#ifdef APP_MJC_SUPPORT
extern MENU_ITEM_T          t_g_menu_common_item_vid_mjc_effect;
extern MENU_ITEM_T          t_g_menu_common_item_vid_mjc_mode;
extern MENU_ITEM_T          t_g_menu_common_item_vid_mjc_demo_mode;
#endif /* APP_MJC_SUPPORT */
#ifdef APP_MENU_HDMI_MODE_SUPPORT
extern MENU_ITEM_T          t_g_menu_common_item_vid_hdmi_mode;
#endif
#ifdef APP_DI_SUPPORT
extern MENU_ITEM_T          t_g_menu_common_item_vid_di_film_mode;
extern MENU_ITEM_T          t_g_menu_common_item_vid_di_ma;
extern MENU_ITEM_T          t_g_menu_common_item_vid_di_edge;
#endif

extern MENU_ITEM_T          t_g_menu_common_item_vid_game_low_latency;

#ifdef APP_MENU_PQ_DEMO_SUPPORT
extern MENU_ITEM_T          t_g_menu_common_item_vid_pq;
#endif

#ifdef APP_XVYCC_SUPPORT
extern MENU_ITEM_T          t_g_menu_common_item_vid_xvycc;
#endif
#ifdef APP_WCG_SUPPORT
extern MENU_ITEM_T          t_g_menu_common_item_vid_wcg;
#endif
#ifdef APP_BLUE_STRETCH_SUPPORT
extern MENU_ITEM_T          t_g_menu_common_item_vid_blue_stretch;
#endif
#ifdef APP_MPEG_NR_SUPPORT
extern MENU_ITEM_T          t_g_menu_common_item_vid_mpeg_nr;
#endif
extern MENU_ITEM_T          t_g_menu_common_item_vid_contrast_en;
extern MENU_ITEM_T          t_g_menu_common_item_vid_super_resolution;
extern MENU_ITEM_T          t_g_menu_common_item_vid_edge_enhancement; //de_jaggy
#ifdef APP_SUPPPORT_FRC
extern MENU_ITEM_T          t_g_menu_common_item_vid_judder_reduction;
extern MENU_ITEM_T          t_g_menu_common_item_vid_motion_blur_reduction;
#endif
extern MENU_ITEM_T          t_g_menu_common_item_vid_vss;
extern MENU_ITEM_T          t_g_menu_common_item_vid_game_hdr;
extern MENU_ITEM_T          t_g_menu_common_item_vid_en_view_angle;
extern MENU_ITEM_T          t_g_menu_common_item_vid_local_contrast;
extern MENU_ITEM_T          t_g_menu_common_item_vid_contour_smoothing;
extern MENU_ITEM_T          t_g_menu_common_item_vid_peak_luminance;

/* oled panel page item*/
extern MENU_ITEM_T          t_g_menu_common_item_vid_oled_pixel_shift;

/* Audio */
extern MENU_ITEM_T          t_g_menu_common_item_aud_volume;
extern MENU_ITEM_T          t_g_menu_common_item_aud_sb_bass;
extern MENU_ITEM_T          t_g_menu_common_item_aud_sb_treble;
extern MENU_ITEM_T          t_g_menu_common_item_aud_balance;
extern MENU_ITEM_T          t_g_menu_common_item_aud_sb_eq_mode;
extern MENU_ITEM_T          t_g_menu_common_item_aud_bass;
extern MENU_ITEM_T          t_g_menu_common_item_aud_treble;
extern MENU_ITEM_T          t_g_menu_common_item_aud_dialogue;
extern MENU_ITEM_T          t_g_menu_common_item_aud_subwoofer;
extern MENU_ITEM_T          t_g_menu_common_item_aud_night_mode;
extern MENU_ITEM_T          t_g_menu_common_item_aud_virtualx;
extern MENU_ITEM_T          t_g_menu_common_item_aud_sb_speaker_Test;
extern MENU_ITEM_T          t_g_menu_common_item_aud_sb_Info;
extern MENU_ITEM_T          t_g_menu_common_item_aud_balance;
extern MENU_ITEM_T          t_g_menu_common_item_aud_surround;
extern MENU_ITEM_T          t_g_menu_common_item_aud_reverb;
extern MENU_ITEM_T          t_g_menu_common_item_aud_mode;
extern MENU_ITEM_T          t_g_menu_common_item_aud_speaker;
extern MENU_ITEM_T          t_g_menu_common_item_aud_vol_control;
extern MENU_ITEM_T          t_g_menu_common_item_aud_srs_truvolume;
extern MENU_ITEM_T          t_g_menu_common_item_aud_mts;
extern MENU_ITEM_T          t_g_menu_common_item_aud_spdif;
extern MENU_ITEM_T          t_g_menu_common_item_aud_bbe_mode;
extern MENU_ITEM_T          t_g_menu_common_item_aud_vol_dis;
extern MENU_ITEM_T          t_g_menu_common_item_aud_dia_enhancer;
extern MENU_ITEM_T          t_g_menu_common_item_aud_earc;


/* CEC */
#ifdef APP_CEC_MENU
extern MENU_ITEM_T	      t_g_menu_common_item_cec_function;
extern MENU_ITEM_T        t_g_menu_common_item_cec_sac_function;
#endif

/*factory test*/
extern MENU_ITEM_T          t_g_menu_common_item_fac_aud_latency;

/* TV */
extern MENU_ITEM_T          t_g_menu_common_item_tv_tuner_mode;

/* MISC */
extern MENU_ITEM_T          t_g_menu_common_item_misc_blue_mute;
extern MENU_ITEM_T          t_g_menu_common_item_misc_auto_sleep;
extern MENU_ITEM_T          t_g_menu_common_item_misc_sleep_timer;
extern MENU_ITEM_T          t_g_menu_common_item_scrn_saver;
extern MENU_ITEM_T          t_g_menu_common_item_blank_scrn_now;
extern MENU_ITEM_T          t_g_menu_common_item_block_unrated;
extern MENU_ITEM_T          t_g_menu_common_item_rating_enable;
extern MENU_ITEM_T          t_g_menu_common_item_burning_mode;
extern MENU_ITEM_T          t_g_menu_common_item_rating_enable;
extern MENU_ITEM_T          t_g_menu_common_item_dpms;
extern MENU_ITEM_T          t_g_menu_common_item_flicker_pattern;
extern MENU_ITEM_T          t_g_menu_common_item_tshift_mode;
extern MENU_ITEM_T          t_g_menu_common_item_local_dimming;

/* VGA */
extern MENU_ITEM_T          t_g_menu_common_item_vga_pos_h;
extern MENU_ITEM_T          t_g_menu_common_item_vga_pos_v;
extern MENU_ITEM_T          t_g_menu_common_item_vga_phase;
extern MENU_ITEM_T          t_g_menu_common_item_vga_clock;

/* PIP & POP */
#if defined(APP_PIP_POP_CTRL) || defined(APP_PIP_SETTINGS_IN_MENU)
extern MENU_ITEM_T          t_g_menu_common_item_pip_mode;
#endif

#ifdef APP_PIP_POP_CTRL
extern MENU_ITEM_T          t_g_menu_common_item_pip_src_ex;
extern MENU_ITEM_T          t_g_menu_common_item_pip_pos_ex;
extern MENU_ITEM_T          t_g_menu_common_item_pip_size_ex;
#endif
#ifdef APP_PIP_SETTINGS_IN_MENU
extern MENU_ITEM_T          t_g_menu_common_item_pip_src;
extern MENU_ITEM_T          t_g_menu_common_item_pip_pos;
extern MENU_ITEM_T          t_g_menu_common_item_pip_size;
#endif /* APP_PIP_SETTINGS_IN_MENU */
#ifdef APP_MENU_HDMI_MODE_SUPPORT
extern MENU_ITEM_T          t_g_menu_common_item_vid_hdmi_mode;
#endif
extern MENU_ITEM_T          t_g_menu_common_item_vid_vga_mode;
extern MENU_ITEM_T          t_g_menu_common_item_inp_hdmi_mode;
extern MENU_ITEM_T          t_g_menu_common_item_inp_full_color_444;
extern MENU_ITEM_T          t_g_menu_common_item_inp_film_maker_mode;

/*Network configuration*/
#ifdef APP_NETWORK_SUPPORT
extern MENU_ITEM_T          t_g_menu_common_item_internet_connection;
extern MENU_ITEM_T          t_g_menu_common_item_dlna_setting;

#endif

#ifdef APP_SPDIF_DELAY_SUPPORT
extern MENU_ITEM_T          t_g_menu_common_item_aud_spdif_delay;
#endif

#ifdef APP_LED_LOGO_CTRL
extern MENU_ITEM_T         t_g_menu_common_item_led_logo_ctrl;
#endif
extern MENU_ITEM_T         t_g_menu_common_item_usb_power_ctrl;
extern MENU_ITEM_T         t_g_menu_common_item_demo_mode;

extern MENU_ITEM_T         t_g_menu_item_page_tv_name;
extern MENU_ITEM_T 		   t_g_menu_item_page_ver_info;

#ifdef DYNAMIC_NATIVE_DIAL_SUPPORT
extern MENU_ITEM_T         t_g_menu_custom_item_native_dial;
#endif

/* page definition */
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_eq_bands_setting;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_new_eq;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_pwd;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_chg_pwd;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_input_sys_pin;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_ch_lst2;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_ver_info;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_ver_info_mc;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_vizio_tos;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_fe_chk;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_divx_info;
#ifdef DIVX_DRM_51
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_divx_deact;
#endif /* DIVX_DRM_51 */
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_simple_dialog;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_vga_auto;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_auto_color;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_auto_phase;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_inp_lst;
#ifdef COMMON_GUI_TIME_ZONE_SELECTION
extern MENU_PAGE_FCT_TBL_T  t_g_menu_custom_page_time_zone;
#endif
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_date_time;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_burn;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_img_clnr;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_aud_fac;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_tuner_fac;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_mjc_demo;

#ifdef APP_VGA_AMBIGUOUS_TIMING_SUPPORT
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_vga_ambi;
#endif

extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_pic_mode;

extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_screen_mode;

extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_aspect_ratio;

extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_sb_setting_eq_mode;

extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_tv_name;

extern MENU_PAGE_FCT_TBL_T  t_g_menu_clear_memory_pwd;

extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_nw_terms;

extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_nw_terms_sub;

#ifdef APP_CEC_MENU
/*CEC special page*/
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_cec;
#endif

extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_scrn_blank;
/*picture mode management(common)->picture mode edit(special)*/
extern MENU_PAGE_FCT_TBL_T t_g_menu_page_pic_mode_edit;
extern MENU_PAGE_FCT_TBL_T t_g_menu_page_lock_pic_lb2;

/*color calibration*/
extern MENU_PAGE_FCT_TBL_T t_g_menu_page_color_calibration;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_test_special_param;

#ifdef APP_LOG2USB_SUPPORT
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_log_to_usb;
#endif

/*Porfessional Picture Mode*/
extern MENU_PAGE_FCT_TBL_T t_g_menu_common_page_pic_quality;//Color tuner
extern MENU_PAGE_FCT_TBL_T t_g_menu_common_page_white_balance_tuner;//White Balance Tuner

extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_create_pic_mode;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_rename_pic_mode;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_lock_pic_mode;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_unlock_pic_mode;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_delete_pic_mode;

/* Gaming Mode page */
extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_gaming_mode;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_audio_dbginfo;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_hdmi_dbginfo;

/* channel scan status */
extern MENU_ITEM_T t_g_menu_common_item_ch_scan_status;
#ifdef APP_TTS_SUPPORT
extern MENU_ITEM_T         t_g_menu_common_item_talkback;
extern MENU_ITEM_T         t_g_menu_common_speech_rate;
#endif
extern MENU_ITEM_T         t_g_menu_common_item_power_on_input;

extern MENU_ITEM_T         t_g_menu_common_item_zoom_mode;
extern MENU_ITEM_T		   t_g_menu_common_item_video_description_mode;

/*-----------------------------------------------------------------------------
                    function declaraions
 ----------------------------------------------------------------------------*/

 VOID set_power_on_device(UINT16 ui2_idx);
 Enu_POWER_ON_INPUT get_power_on_device();
 
 extern VOID inx_set_power_on_input(UINT16 ui2_idx);


/* common app init */
extern UINT32 ui4_g_page_clear_memory_dialog;
extern INT32 menu_common_init (VOID);
extern INT32 menu_common_resume(VOID);
extern INT32 menu_common_pause(VOID);
extern INT32 menu_common_exit(VOID);
extern INT32 menu_common_process_msg (
    UINT32       ui4_type,
    const VOID*  pv_msg,
    SIZE_T       z_msg_len,
    BOOL*        pb_processed
);

/* Channel store */

/* NOTE: This function is asyncrhounously and will check the dirty flag
   Please don't call this function instead of menu.c */
extern INT32    menu_common_store_ch_list(VOID);

/* util function */
extern HANDLE_T menu_get_crnt_svl(VOID);
extern HANDLE_T menu_get_crnt_tsl(VOID);
extern HANDLE_T menu_get_crnt_lol(VOID);
extern HANDLE_T menu_get_crnt_svctx(VOID);
extern HANDLE_T menu_get_crnt_scan_svctx(VOID);
extern INT32    menu_get_crnt_svl_rec(SVL_REC_T* pt_svl_rec, BOOL* pb_found);
extern INT32    menu_get_crnt_isl(ISL_REC_T* pt_il_rec);
extern INT32    menu_get_crnt_tv_mode_and_isl_rec(TV_MODE_T* pt_tv_mode,
                                                  ISL_REC_T* pt_isl_rec);
extern HANDLE_T menu_get_current_svctx(VOID);   /* deprecated */
extern BOOL     menu_is_signal_loss(VOID);
extern BOOL     menu_is_video_block(VOID);
extern BOOL     menu_is_digital_tv(TV_WIN_ID_T e_tv_win_id);
extern INT32    menu_keep_crnt_stream_mode(VOID);
extern INT32    menu_adjust_vplane(VOID);
extern INT32    menu_select_crnt_or_first_channel(BOOL b_skip_fake);
extern INT32    menu_reset_svl_by_mask(HANDLE_T h_svl,
                                       UINT32 ui4_reset_mask,
                                       UINT32 ui4_reset_value);

extern INT32    menu_reset_isl_by_mask(UINT32 ui4_reset_mask,
                                       UINT32 ui4_reset_value);

extern INT32    menu_enable_video_mute(BOOL b_enable);
extern BOOL     menu_is_tv_block(VOID);
extern BOOL     menu_is_crnt_channel_block(VOID);


/* page registration */
extern INT32 menu_common_page_cap_stl_init(VOID);
extern INT32 menu_common_page_pwd_init(VOID);
extern INT32 menu_common_page_chg_pwd_init(VOID);
extern INT32 menu_common_page_sys_pin_init(VOID);

extern INT32 menu_common_page_reset_init(VOID);
extern INT32 menu_common_page_ch_lst2_init(VOID);
extern INT32 menu_common_page_ver_info_init(VOID);
extern INT32 menu_page_mc_ver_init(VOID);
extern INT32 menu_common_page_fe_chk_init(VOID);
extern INT32 menu_common_page_divx_info_init(VOID);
extern BOOL  menu_common_page_divx_info_need_hide(VOID);
#ifdef DIVX_DRM_51
extern INT32 menu_common_page_divx_deact_init(VOID);
extern BOOL  menu_common_page_divx_deact_need_confirm(VOID);
#endif /* DIVX_DRM_51 */
extern INT32 menu_common_page_simple_dialog_init(VOID);
extern INT32 menu_common_page_vga_auto_init(VOID);
extern INT32 menu_common_page_auto_color_init(VOID);
extern INT32 menu_common_page_inp_lst_init(VOID);
extern INT32 menu_common_page_inp_src_init(VOID);
extern INT32 menu_common_page_naming_init(VOID);
extern INT32 menu_page_tv_name_init(VOID);

extern INT32 menu_page_pic_mode_init();
extern INT32 menu_common_page_picture_quality_init(VOID);
extern INT32 menu_common_page_white_balance_tuner_init(VOID);
extern INT32 menu_page_create_new_pic_mode_init(VOID);
extern INT32 menu_page_pic_mode_edit_init(VOID);
extern INT32 menu_page_lock_pic_mode_lb2_init(VOID);
extern INT32 menu_page_color_calibration_init(VOID);
extern INT32 menu_page_lock_new_pic_mode_init(VOID);
extern INT32 menu_page_unlock_new_pic_mode_init(VOID);
extern INT32 menu_page_delete_new_pic_mode_init(VOID);
extern INT32 menu_page_gaming_mode_init(VOID);
extern INT32 menu_page_color_tuner_is_scrn_mode(VOID);
extern INT32 menu_page_color_tuner_adjust_test_pattern(UINT16 ui2_test_page,UINT16 ui2_test_pattern);
extern UINT16 menu_page_color_tuner_get_test_pattern(UINT16 ui2_scrn_page);
extern BOOL get_delay_lock_cust_pic_mode_status(VOID);
extern VOID set_delay_lock_cust_pic_mode_status(BOOL b_status);
extern INT32 menu_common_page_test_special_param_init(VOID);
#ifdef APP_LOG2USB_SUPPORT
extern INT32 menu_common_page_log_to_usb_init(VOID);
#endif

extern INT32 menu_page_new_eq_init(VOID);
#ifdef COMMON_GUI_TIME_ZONE_SELECTION
extern INT32 menu_custom_page_time_zone_init(VOID);
#endif
extern INT32 menu_common_page_date_time_init(VOID);
extern INT32 menu_common_page_burn_init(VOID);
extern INT32 menu_common_page_img_clnr_init(VOID);
extern INT32 menu_common_page_auto_phase_init(VOID);
extern INT32 a_create_pic_mode_warn_dlg_hide(VOID);
extern INT32 a_create_pic_mode_warn_dlg_show(VOID);
extern BOOL  a_create_pic_mode_warn_dlg_is_show(VOID);
extern VOID  a_create_pic_mode_name_exceeding_yes_fct(VOID);
extern INT32 a_menu_test_page_osd_hide(VOID);

extern INT32 menu_page_pic_mode_edit_dlg_show(VOID);
extern INT32 menu_page_pic_mode_edit_dlg_hide(VOID);
extern INT32 menu_page_pic_mode_edit_dlg_is_show(VOID);
extern INT32 menu_page_color_calibration_dlg_show(VOID);
extern INT32 menu_page_color_calibration_dlg_hide(VOID);
extern INT32 menu_page_color_calibration_dlg_is_show(VOID);

extern UINT32 ui4_g_menu_page_tv_setting;

extern INT32 menu_common_create_page_sk_ch2(
    UINT32 *pui4_page_id
);

extern INT32 menu_common_create_page_bk_ch2(
    UINT32 *pui4_page_id
);

extern INT32 menu_common_create_page_fav_lst2(
    UINT32 *pui4_page_id
);

extern INT32 mneu_common_ch_lst2_create(
    MENU_COMMON_CHANNEL_LIST_INIT_T t_ch_lst_init,
    UINT32*                         pui4_page_id
);

extern BOOL menu_common_page_ch_lst2_is_enabled(VOID);
extern BOOL menu_common_page_ch_lst2_is_analog_enabled(VOID);

extern INT32 menu_common_create_page_sk_inp(
    UINT32 *pui4_page_id
);

extern INT32 menu_common_create_page_bk_inp(
    UINT32 *pui4_page_id
);

/* channel scan status */
extern VOID a_get_ch_scan_status_text(
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len /* in, len of w2s_str */);

extern BOOL menu_common_page_auto_color_is_enabled(VOID);
extern BOOL menu_common_page_auto_phase_is_enabled(VOID);

/* BBE */
#ifdef APP_BBE_SUPPORT
extern INT32 menu_common_page_bbe_create(
    UINT32* ui4_page_id
);
#endif

/* Audio Factory Settings Page */
extern INT32 menu_common_page_aud_fac_init(VOID);

extern INT32 menu_common_page_aud_fac_mts_create(UINT32 *pui4_page_id);
extern INT32 menu_common_page_aud_fac_a2_create(UINT32 *pui4_page_id);
extern INT32 menu_common_page_aud_fac_pal_create(UINT32 *pui4_page_id);
extern INT32 menu_common_page_aud_fac_eu_create(UINT32 *pui4_page_id);
extern BOOL menu_inp_is_full_color_444_on(VOID);

extern VOID menu_common_get_vid_pic_mode_text(UINT16    ui2_idx,   /* in */
                                        CHAR*     ps_pic_mode,   /* out */
                                        SIZE_T    z_len);

/* Tuner Factory Page */
extern INT32 menu_common_page_tuner_fac_init(VOID);

/* settings registration */
extern INT32 menu_common_settings_init(VOID);

/* CLI */
extern INT32 menu_cli_attach_cmd_tbl(VOID);
extern INT32 menu_cli_detach_cmd_tbl(VOID);
extern INT32 menu_common_scan_start(x_sb_scan_nfy_fct _pf_scan_notfy);
extern INT32 menu_common_scan_cancel(VOID);

/* Util */
extern INT32 menu_common_help_show_back(VOID);
extern INT32 menu_common_help_show_select_back(VOID);

/* MJC */
#ifdef APP_MJC_SUPPORT
extern INT32 menu_common_page_mjc_demo_init(VOID);
#endif

#ifdef APP_VGA_AMBIGUOUS_TIMING_SUPPORT
extern INT32 menu_common_vga_ambigous_init(VOID);
extern INT32 menu_common_get_ambiguous_vga_timing_num(UINT16 *pui2_num);
#endif

extern INT32 menu_common_page_network_wps_init(VOID);

/* input source */
extern INT32 menu_common_create_page_pip_inp_src(UINT32 *pui4_page_id);
extern INT32 menu_common_create_page_inp_src(UINT32 *pui4_page_id);
extern INT32 menu_common_create_page_inp_set(UINT32 *pui4_page_id);

extern INT32 menu_page_audio_dbginfo_init(VOID);
extern INT32 menu_page_hdmi_dbginfo_init(VOID);

/* page naming */
extern INT32 menu_common_create_page_naming(UINT32 *pui4_page_id);
extern INT32 menu_add_analog_select_channel(UINT32  ui4_channel_num, BOOL* pb_found);

extern INT32 menu_page_screen_mode_init(VOID);
extern INT32 menu_page_aspec_ratio_init(VOID);
extern INT32 menu_page_sb_setting_eq_mode_init(VOID);
extern INT32 menu_page_inp_edit_init(VOID);
extern INT32 menu_clear_memory_pwd_init(VOID);

extern INT32 menu_common_page_terms_init(VOID);
extern INT32 menu_common_page_sub_terms_init(VOID);
extern INT32 menu_common_page_acr_init(VOID);

/*vkb funciton */
extern INT32 a_vkb_current_is_top_row(HANDLE_T      h_vkb_handle,
                                      BOOL*         pb_is_top_row);

extern INT32 a_vkb_current_is_bottom_row(HANDLE_T   h_vkb_handle,
                                         HANDLE_T*  ph_cancel_handle,
                                         BOOL*      pb_is_bottom_row);

extern INT32 a_menu_enter_factory_menu(VOID);

#ifdef APP_CEC_MENU
extern INT32 menu_common_page_cec_init(VOID);
extern UTF16_T* get_def_dev_osd_name (UINT8 ui1_la);
#endif

extern INT32 get_cec_device_name(UINT8 hdmi_port, UTF16_T* cec_device_name, UINT8 ui1_str_len);

extern VOID clear_memory(VOID);
extern UINT32 _menu_set_hdmi_edid(VOID);
extern VOID menu_clear_memory_ex(BOOL b_need_reboot);

extern INT32 menu_common_page_scrn_blank_init(VOID);

extern UINT16 get_cust_picture_mode_num(VOID);
extern UINT16 cvt_acfg_idx_2_list_box_idx(UINT16 ui2_idx);
extern UINT16 cvt_list_box_idx_2_acfg_idx(UINT16 ui2_idx);

extern BOOL create_pic_mode_no_need_show_cnt_page(VOID);
extern BOOL a_menu_is_cc_hot_key(VOID);
extern VOID menu_clear_memory_set_cust_page_id_pass(UINT32 ui4_page_id);

#if( MENU_SUPPORT_HOT_KEY_PIC|| defined(APP_SUPPORT_PIC_HOT_KEY) )
extern BOOL a_menu_is_pic_hot_key(VOID);
#endif
#if 0//( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO )
extern BOOL a_menu_is_hot_key_BTN_ASPECT(VOID);
#endif

extern VOID set_preset_pic_mode_chg_status(BOOL b_is_chg);
extern VOID set_preset_pic_mode_chg_status_ex(BOOL b_is_chg);

extern BOOL menu_common_is_3d_mode_enable(VOID);
extern BOOL menu_common_is_3d_to_2d_enable(VOID);
extern BOOL menu_common_is_lr_switch_enable(VOID);
extern BOOL menu_common_is_img_safety_enable(VOID);
extern BOOL menu_common_is_3d_hide(VOID);
extern BOOL menu_common_is_protrude_enable(VOID);
extern BOOL menu_common_is_osd_depth_enable(VOID);
extern BOOL menu_common_is_dof_enable(VOID);
extern BOOL menu_common_is_distance_to_tv_enable(VOID);
extern BOOL menu_common_is_3d_navigation_enable(VOID);

extern UINT16 menu_page_naming_is_predef_name(CHAR *p_name);
extern INT32 a_c4tv_apron_get_cast_builder_name(CHAR *ps_cast_builder_name,UINT32 *pui4_cast_builder_name_len);
extern INT32 reset_dialog_go(UINT32 ui4_page_id,MENU_PAGE_HINT_T* pt_hint);
extern INT32 vid_update_position_info(UINT8 u1_input_id,INT32 i4_value,BOOL b_direction_v);
extern CHIPSET menu_common_get_chipset(VOID);
extern UINT16 a_get_cec_earc_idx(VOID);
extern VOID a_set_cec_earc_idx(UINT16 ui2_idx);
extern INT32 menu_ver_info_utv_info_get(MENU_VER_ULI_INFO* pver_uli_info);
extern UINT8 menu_ver_info_get_installed_drmp(VOID);
extern INT32 menu_ver_info_netflix_esn(CHAR* s_esn, UINT32 sesn_max_len);
extern INT32 menu_ver_info_get_resolution(CHAR* res_str);
extern INT32 menu_ver_info_get_audio_stream_text(CHAR* str_type, SIZE_T z_len);
extern INT32 menu_ver_info_get_audio_type_out(CHAR* s_audio_type_out);
extern INT32 menu_ver_info_get_vss(CHAR* s_vss);
extern FLOAT menu_ver_info_get_vertical_frequency(VOID);
extern BOOL menu_get_inp_ffm_apply(VOID);
extern BOOL menu_get_inp_ffm_detected(VOID);
extern VOID menu_set_inp_ffm_detected(BOOL b_detected);
extern INT32 menu_ver_info_apple_tv_ver(CHAR* s_ver, UINT32 max_len);
extern INT32 menu_ver_info_hbomax_ver(CHAR* s_ver, UINT32 max_len);
extern INT32 menu_ver_info_castcore_ver(CHAR* s_ver, UINT32 max_len);
extern INT32 menu_ver_info_airplay_internal_ver(CHAR* s_ver, UINT32 max_len);
extern INT32 menu_ver_info_bluetooth_ver(CHAR* s_ver, UINT32 max_len);
extern INT32 menu_common_page_ch_lst2_refresh(VOID);
extern INT32 menu_page_ip_setting_lb_addr_type_change_fct(UINT16 dhcp_value);
extern INT32 menu_ver_info_get_scc_audio_type_out(SCC_AUD_IEC_TYPE_T*  pe_iec_type);
extern BOOL menu_is_vrr_enable_and_vrr_stream_detect(VOID);
extern INT32 menu_ver_info_accumulated_operating_hours(FLOAT* pf_hours);
extern INT32 menu_smpte_test_pattern_set_value_by_id(UINT16 ui2_val);
extern INT16 menu_get_current_smpte_test_pattern_value(VOID);
extern INT32 menu_smpte_test_pattern_update_txt(BOOL b_repaint);
extern INT32 menu_uniformity_analyzer_test_pattern_set_value_by_id(UINT16 ui2_val);
extern INT16 menu_get_current_uniformity_analyzer_test_pattern_value(VOID);
extern INT32 menu_uniformity_analyzer_test_pattern_update_txt(BOOL b_repaint);
extern BOOL menu_is_support_code_hidden(VOID);
extern INT32 menu_factory_test_pattern_set_value_by_id(UINT16 ui2_val);
extern INT32 menu_ver_info_get_frame_rate(CHAR* frm_rt_str);
extern INT32 ver_info_get_hdr_type(CHAR* str_hdr);
extern INT32 menu_ver_info_get_audio_out(CHAR* aud_ot_str);

#endif /* _MENU_COMMON_H_ */
