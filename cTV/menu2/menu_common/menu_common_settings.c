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
 * $RCSfile: menu_common_settings.c,v $
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
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_drv_cust.h"
#include "u_rm_dev_types.h"

#include "c_scc.h"
#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svctx.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_cfg.h"
#include "c_rm.h"
#include "c_sys_config.h"

#include "app_util/a_cfg.h"
#include "app_util/a_screen_mode.h"
#include "app_util/a_sleep_timer.h"
#include "app_util/a_tv.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/config/acfg_cust_plf_opt.h"
#include "res/app_util/config/acfg_cust_factory.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/model/model.h"


/* channel scan status */
#include "res/app_util/config/acfg_custom.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_device/menu_page_input_ope_lst.h"
#include "menu2/menu_device/menu_device.h"
#include "u_sb_atsc_eng.h"
#include "u_sb_ntsc_eng.h"
#include "u_sb_cqam_eng.h"
#include "u_common.h"
#include "u_sb.h"
#include "u_svl.h"

#include  "menu2/menu_mtktvapi.h"
#include "res/nav/nav_mlm.h"
#include "amb/a_amb.h"

#ifdef APP_NAV_FLICKER_SUPPORT
#include "nav/flicker_pattern/a_nav_flicker.h"
#endif

#ifdef APP_NETWORK_SUPPORT
#include "app_util/a_network.h"
#endif

#include "menu2/menu_common/menu_common.h"
#include "app_util/tvstate/tvstate.h"
#include "app_util/tvstate/smart_dim.h"
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
#include "c_cecm.h"
#include "nav/cec2/nav_cec.h"
#include "nav/cec2/a_nav_cec.h"

#endif
#endif
#endif

#include "nav/tuner_setup/a_tuner_setup.h"
#include "nav/tuner_setup/tuner_setup_view.h"
#include "nav/input_src/a_input_src.h"
#include "res/menu2/menu_custom_dialog.h"
#include "nav/banner2/banner.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#include "c_tts.h"
#include "registry/a_registry.h"
#endif
#include "res/menu2/menu_custom.h"
#include "app_util/mtktvapi/a_mtktvapi_cec.h"
#ifdef APP_C4TV_SUPPORT
#include "rest/a_rest_event.h"
#endif

#include "menu2/menu_dbg.h"
#include "nav/cec2/sac/nav_cec_sac.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define AUD_SPDIF_AUDIO_OUT_AUTO                (0)
#define AUD_SPDIF_AUDIO_OUT_PCM                 (1)
#define AUD_SPDIF_AUDIO_OUT_DOLBY_D             (2)
#define AUD_SPDIF_AUDIO_OUT_BITSTREAM           (3)

/*0:disable vol display control,1:enable vol display control*/
#define AUD_DIS_VOL_ENABLE                             (1)
#define MAX_HDMI_PORTS                                 (4)
#define POD_SYSTEM_PATH                                "/data/pod.dat"
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
Enu_POWER_ON_INPUT g_power_on_device = 0;
UINT16 g_power_on_index = 0;

/* general settings */
MENU_ITEM_T          t_g_menu_common_item_scan_mode;  /* APP_MENU_WITH_SCAN_MODE */
MENU_ITEM_T          t_g_menu_common_item_tv_ar;

/* dolby reative menu items */
MENU_ITEM_T          t_g_menu_common_item_dolby_mode;
MENU_ITEM_T          t_g_menu_common_item_drc;
MENU_ITEM_T          t_g_menu_common_item_cmpss;
MENU_ITEM_T          t_g_menu_common_item_dmix;
MENU_ITEM_T          t_g_menu_common_item_aud_bypass_mode;
MENU_ITEM_T          t_g_menu_common_item_agc;
MENU_ITEM_T          t_g_menu_common_item_aud_latency;

/* Video */
MENU_ITEM_T          t_g_menu_common_item_vid_pic_mode;
MENU_ITEM_T          t_g_menu_common_item_vid_bri;
MENU_ITEM_T          t_g_menu_common_item_vid_cnt;
MENU_ITEM_T          t_g_menu_common_item_vid_sat;
MENU_ITEM_T          t_g_menu_common_item_vid_hue;
MENU_ITEM_T          t_g_menu_common_item_vid_shp;
MENU_ITEM_T          t_g_menu_common_item_vid_clr_tmp_mode;
MENU_ITEM_T          t_g_menu_common_item_vid_clear_action;

/* color gain in user menu. If user adjust the value in non-user color temp mode,
   it will load the values from current mode (for example Warn) to user mode and
   then adjust the value base on these values. */
MENU_ITEM_T          t_g_menu_common_item_vid_clr_gain_r;
MENU_ITEM_T          t_g_menu_common_item_vid_clr_gain_g;
MENU_ITEM_T          t_g_menu_common_item_vid_clr_gain_b;
MENU_ITEM_T          t_g_menu_common_item_vid_clr_offset_r;
MENU_ITEM_T          t_g_menu_common_item_vid_clr_offset_g;
MENU_ITEM_T          t_g_menu_common_item_vid_clr_offset_b;

/* color gain in factory menu. It always adjusts the value of current mode. */
MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_gain_r;
MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_gain_g;
MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_gain_b;
MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_offset_r;
MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_offset_g;
MENU_ITEM_T          t_g_menu_common_item_vid_fac_clr_offset_b;

MENU_ITEM_T          t_g_menu_common_item_vid_blur;
MENU_ITEM_T          t_g_menu_common_item_vid_dnr;
MENU_ITEM_T          t_g_menu_common_item_vid_flesh_tone;
MENU_ITEM_T          t_g_menu_common_item_vid_alc;
MENU_ITEM_T          t_g_menu_common_item_vid_gamma;
MENU_ITEM_T          t_g_menu_common_item_vid_back_light;

MENU_ITEM_T          t_g_menu_common_item_vid_tone_mapping;
MENU_ITEM_T          t_g_menu_common_item_vid_oled_luminance;

#ifdef APP_MENU_ADP_BACK_LIGHT_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_vid_adp_back_light;
#endif
MENU_ITEM_T          t_g_menu_common_item_vid_scr_mode;
MENU_ITEM_T          t_g_menu_common_item_vid_ypbpr_phase;
#ifdef APP_HV_POS_MODIFICATION_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_vid_pos_h;
MENU_ITEM_T          t_g_menu_common_item_vid_pos_v;
#endif
#ifdef APP_MJC_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_vid_mjc_effect;
MENU_ITEM_T          t_g_menu_common_item_vid_mjc_mode;
MENU_ITEM_T          t_g_menu_common_item_vid_mjc_demo_mode;
#endif /* APP_MJC_SUPPORT */
#ifdef APP_MENU_HDMI_MODE_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_vid_hdmi_mode;
#endif
MENU_ITEM_T          t_g_menu_common_item_inp_hdmi_mode;
MENU_ITEM_T          t_g_menu_common_item_inp_full_color_444;
MENU_ITEM_T          t_g_menu_common_item_inp_film_maker_mode;

MENU_ITEM_T          t_g_menu_common_item_vid_vga_mode;

#ifdef APP_DI_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_vid_di_film_mode;
MENU_ITEM_T          t_g_menu_common_item_vid_di_ma;
MENU_ITEM_T          t_g_menu_common_item_vid_di_edge;
#endif

MENU_ITEM_T          t_g_menu_common_item_vid_game_low_latency;

#ifdef APP_MENU_PQ_DEMO_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_vid_pq;
#endif

#ifdef APP_XVYCC_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_vid_xvycc;
#endif

#ifdef APP_WCG_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_vid_wcg;
#endif

#ifdef APP_BLUE_STRETCH_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_vid_blue_stretch;
#endif

#ifdef APP_MPEG_NR_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_vid_mpeg_nr;
#endif
MENU_ITEM_T          t_g_menu_common_item_vid_contrast_en;
MENU_ITEM_T          t_g_menu_common_item_vid_super_resolution;
MENU_ITEM_T          t_g_menu_common_item_vid_edge_enhancement;

#ifdef APP_SUPPPORT_FRC
MENU_ITEM_T          t_g_menu_common_item_vid_judder_reduction;
MENU_ITEM_T          t_g_menu_common_item_vid_motion_blur_reduction;
#endif
MENU_ITEM_T          t_g_menu_common_item_vid_vss;
MENU_ITEM_T          t_g_menu_common_item_vid_game_hdr;
MENU_ITEM_T          t_g_menu_common_item_vid_en_view_angle;
MENU_ITEM_T          t_g_menu_common_item_vid_local_contrast;
MENU_ITEM_T          t_g_menu_common_item_vid_contour_smoothing;
MENU_ITEM_T          t_g_menu_common_item_vid_peak_luminance;

/* oled panel page item*/
MENU_ITEM_T          t_g_menu_common_item_vid_oled_pixel_shift;

/* Audio */
MENU_ITEM_T          t_g_menu_common_item_aud_sb_soundbar_settings;
MENU_ITEM_T          t_g_menu_common_item_aud_volume;
MENU_ITEM_T          t_g_menu_common_item_aud_sb_bass;
MENU_ITEM_T          t_g_menu_common_item_aud_sb_treble;
MENU_ITEM_T          t_g_menu_common_item_aud_balance;
MENU_ITEM_T          t_g_menu_common_item_aud_sb_eq_mode;
MENU_ITEM_T          t_g_menu_common_item_aud_bass;
MENU_ITEM_T          t_g_menu_common_item_aud_treble;
MENU_ITEM_T          t_g_menu_common_item_aud_dialogue;
MENU_ITEM_T          t_g_menu_common_item_aud_subwoofer;
MENU_ITEM_T          t_g_menu_common_item_aud_night_mode;
MENU_ITEM_T          t_g_menu_common_item_aud_virtualx;
MENU_ITEM_T          t_g_menu_common_item_aud_sb_speaker_Test;
MENU_ITEM_T          t_g_menu_common_item_aud_sb_Info;
MENU_ITEM_T          t_g_menu_common_item_aud_surround;
MENU_ITEM_T          t_g_menu_common_item_aud_reverb;
MENU_ITEM_T          t_g_menu_common_item_aud_mode;
MENU_ITEM_T          t_g_menu_common_item_aud_speaker;
MENU_ITEM_T          t_g_menu_common_item_aud_vol_control;
MENU_ITEM_T          t_g_menu_common_item_aud_srs_truvolume;
MENU_ITEM_T          t_g_menu_common_item_aud_mts;
MENU_ITEM_T          t_g_menu_common_item_aud_spdif;
MENU_ITEM_T          t_g_menu_common_item_aud_vol_dis;
MENU_ITEM_T          t_g_menu_common_item_aud_dia_enhancer;
MENU_ITEM_T          t_g_menu_common_item_aud_earc;

#ifdef APP_SPDIF_DELAY_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_aud_spdif_delay;
#endif
#ifdef APP_BBE_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_aud_bbe_mode;
#endif

/* audio latency setup in factory menu*/
MENU_ITEM_T          t_g_menu_common_item_fac_aud_latency;

/* TV */
MENU_ITEM_T          t_g_menu_common_item_tv_tuner_mode;

/* VGA */
MENU_ITEM_T          t_g_menu_common_item_vga_pos_h;
MENU_ITEM_T          t_g_menu_common_item_vga_pos_v;
MENU_ITEM_T          t_g_menu_common_item_vga_phase;
MENU_ITEM_T          t_g_menu_common_item_vga_clock;

/* PIP & POP */
#if defined(APP_PIP_POP_CTRL) || defined(APP_PIP_SETTINGS_IN_MENU)
MENU_ITEM_T          t_g_menu_common_item_pip_mode;
#endif

#ifdef APP_PIP_POP_CTRL
MENU_ITEM_T          t_g_menu_common_item_pip_src_ex;
MENU_ITEM_T          t_g_menu_common_item_pip_pos_ex;
MENU_ITEM_T          t_g_menu_common_item_pip_size_ex;
#endif
#ifdef APP_PIP_SETTINGS_IN_MENU
MENU_ITEM_T          t_g_menu_common_item_pip_src;
MENU_ITEM_T          t_g_menu_common_item_pip_pos;
MENU_ITEM_T          t_g_menu_common_item_pip_size;
#endif

/* MISC */
MENU_ITEM_T          t_g_menu_common_item_misc_auto_sleep;
MENU_ITEM_T          t_g_menu_common_item_misc_sleep_timer;
MENU_ITEM_T          t_g_menu_common_item_misc_blue_mute;
MENU_ITEM_T          t_g_menu_common_item_block_unrated;
MENU_ITEM_T          t_g_menu_common_item_rating_enable;
MENU_ITEM_T          t_g_menu_common_item_dpms;
MENU_ITEM_T          t_g_menu_common_item_scrn_saver;
MENU_ITEM_T          t_g_menu_common_item_blank_scrn_now;
MENU_ITEM_T          t_g_menu_common_item_burning_mode;
MENU_ITEM_T          t_g_menu_common_item_local_dimming;

#ifdef APP_NAV_FLICKER_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_flicker_pattern;
#endif

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_tshift_mode;
#endif

/*Network Configuration*/
#ifdef APP_NETWORK_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_internet_connection;
MENU_ITEM_T          t_g_menu_common_item_dlna_setting;
#ifdef APP_DMR_SUPPORT
MENU_ITEM_T          t_g_menu_common_item_dlna_dmr_setting;
#endif
#endif /* APP_NETWORK_SUPPORT */

#ifdef APP_LED_LOGO_CTRL
MENU_ITEM_T         t_g_menu_common_item_led_logo_ctrl;
#endif
MENU_ITEM_T         t_g_menu_common_item_usb_power_ctrl;

MENU_ITEM_T         t_g_menu_common_item_zoom_mode;

MENU_ITEM_T         t_g_menu_common_item_video_description_mode;

#ifdef APP_TTS_SUPPORT
MENU_ITEM_T         t_g_menu_common_item_talkback;
MENU_ITEM_T         t_g_menu_common_speech_rate;
#endif
MENU_ITEM_T         t_g_menu_common_item_power_on_input;

/* channel scan status */
MENU_ITEM_T t_g_menu_common_item_ch_scan_status;

HANDLE_T h_g_svctx;


/* VGA, used for work arround */
static INT16    i2_g_vga_pos_h_last = 0;
static INT16    i2_g_vga_pos_v_last = 0;
static INT16    i2_g_vga_phase_last = 0;
static INT16    i2_g_vga_clock_last = 0;

static UINT16   ui2_aud_bypass_mode_idx = 0;
static INT16    i2_old_latency_val = -1;
static BOOL     b_ffm_detected = FALSE;

/* PIC mode */
extern UINT32 ui4_g_menu_page_pic_custom;
extern CEC_SB_VNDR_INFO amp_vndr_info;

/*UART factory mode*/
static HANDLE_T h_iom_uart = NULL_HANDLE;

/*SB SETTINGS EQ MODE*/
extern INT32 a_vol_ctrl_set_visibility(BOOL b_is_volume_visible);

#ifdef APP_PIP_POP_CTRL

extern INT32 a_tv_get_pip_sub_position_id_by_idx(
                    UINT8                       ui1_idx,             /* in  */
                    TV_PIP_SUB_POSITION_T*      pe_resulted_id       /* out */
                    );
extern INT32 a_tv_set_pip_sub_position(
                    TV_PIP_SUB_POSITION_T       e_pos_id
                    );

extern INT32 a_tv_get_pip_sub_position(
                    TV_PIP_SUB_POSITION_T*      pe_pos_id
                    );
extern INT32 a_tv_set_pip_sub_size(
                    TV_PIP_SUB_SIZE_T           e_size_id
                    );
extern UINT8 a_tv_get_num_of_pip_sub_position(
                    VOID
                    );
extern INT32 a_tv_get_pip_sub_size_id_by_idx(
                    UINT8                       ui1_idx,             /* in  */
                    TV_PIP_SUB_SIZE_T*          pe_resulted_id       /* out */
                    );
extern UINT8 a_tv_get_num_of_pip_sub_size(
                    VOID
                    );

extern INT32 a_pop_get_audio_focus_id(
                    TV_WIN_ID_T*            pe_focus_id
                    );
extern VOID a_pop_set_osd_audio_focus(TV_WIN_ID_T e_focus_id);

extern INT32 a_tv_iterate_pip_sub_position_id(
                    TV_PIP_SUB_POSITION_T       e_ref_id,            /* in  */
                    TV_ITERATE_DIR_T            e_dir,               /* in  */
                    TV_PIP_SUB_POSITION_T*      pe_resulted_id       /* out */
                    );
extern UTF16_T* a_tv_get_pip_sub_position_display_name(
                    TV_PIP_SUB_POSITION_T       e_pos_id
                    );
extern INT32 a_tv_iterate_pip_sub_size_id(
                    TV_PIP_SUB_SIZE_T           e_ref_id,            /* in  */
                    TV_ITERATE_DIR_T            e_dir,               /* in  */
                    TV_PIP_SUB_SIZE_T*          pe_resulted_id       /* out */
                    );
extern UTF16_T* a_tv_get_pip_sub_size_display_name(
                    TV_PIP_SUB_SIZE_T           e_size_id            /* in */
                    );
extern VOID set_preset_pic_mode_chg_status(BOOL b_is_chg);
#endif

/* channel scan status */
extern VOID a_get_ch_scan_status_text(
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len /* in, len of w2s_str */);

extern BOOL a_acfg_is_support_v_gaming_engine(VOID);
extern BOOL a_acfg_is_support_pro_gaming_engine(VOID);
extern INT32 nav_cec_sac_set_AQ_status(UINT8 type, UINT8 ui2_idx);
extern int nav_cec_sac_set_EQ_mode(UINT8 ui2_idx);
extern INT32 nav_cec_sac_set_SpeakerTest(VOID);
extern INT32 nav_cec_sac_set_Info(VOID);
extern BOOL a_nav_ipts_not_support_comp_source(VOID);


static VOID _get_dig_and_ana_num(UINT16* pui2_num_recs_digital,UINT16* pui2_num_recs_analog);
static VOID _set_vid_en_view_angle_idx(UINT16 ui2_val);



/*-----------------------------------------------------------------------------
                    static function implementation
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_gamma_idx(VOID);
static UINT16 _get_vid_clr_tmp_mode_idx(VOID);
static UINT16 _get_vid_clear_action_idx(VOID);
static UINT16 _get_vid_blur_idx(VOID);
static UINT16 _get_vid_dnr_idx(VOID);
static UINT16 _get_vid_alc_idx(VOID);
static UINT16 _get_vid_di_film_mode_idx(VOID);
static UINT16 _get_vid_mjc_effect_idx(VOID);
static UINT16 _get_vid_mpeg_nr_idx(VOID);
static VOID _init_uart_fact_mode(VOID);
static VOID _set_aud_eq_mode_val(INT32 i4_val);
static INT32 _get_aud_eq_mode_val(VOID);

/*-----------------------------------------------------------------------------
                Enum of the function implementation
 ----------------------------------------------------------------------------*/

typedef enum
{
    _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT = 0,
    _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MUSIC = _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT,
    _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MOVIE,
    _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_GAME,
    _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DIRECT,
    _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DIALOGUE,
    _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MAX

} _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_T;


/*-----------------------------------------------------------------------------
                    video related function implementation
 ----------------------------------------------------------------------------*/

#define FACTORY_VIR_UART_ID 7
static VOID _init_uart_fact_mode(VOID)
{
    UART_SETTING_T  t_uart_setting;

    t_uart_setting.e_speed    = IOM_UART_SPEED_115200;
    t_uart_setting.e_data_len = IOM_UART_DATA_LEN_8;
    t_uart_setting.e_parity   = IOM_UART_PARITY_NONE;
    t_uart_setting.e_stop_bit = IOM_UART_STOP_BIT_1;
    DBG_LOG_PRINT(("<fact_parser> UART open port 7 ----\n"));

    /* open UART port */
    if (c_iom_open(IOM_DEV_TYPE_IO_UART,
                   FACTORY_VIR_UART_ID,
                   NULL,
                   (VOID*) &t_uart_setting,
                   NULL,
                   NULL,
                   &h_iom_uart) != IOMR_OK)
    {
        DBG_LOG_PRINT(("<fact_parser> UART open fails\n"));
    }
}

/*----------------------------------------------------------------------------
 * Name: _pm_refresh_repaint()
 *
 * Description: In order to refresh the asterisk appended to preset pic mode name once the pq value is adjust.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _pm_refresh_repaint(VOID)
{
    //menu_pm_refresh();
    //menu_pm_repaint();
}

/*----------------------------------------------------------------------------
 * Name: set_preset_pic_mode_chg_status
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID set_preset_pic_mode_chg_status(BOOL b_is_chg)
{
    INT32       i4_ret = MENUR_OK;
    INT16       i2_pic_mode = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);

    MENU_LOG_ON_FAIL(i4_ret);

    if(i2_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM)
    {
        a_cfg_set_preset_pic_mode_chg_status(i2_pic_mode,b_is_chg);
    }

    DBG_INFO(("\n####%s(%d)i2_pic_mode=%d\n",__FUNCTION__,__LINE__,i2_pic_mode));


}

/*----------------------------------------------------------------------------
 * Name: set_preset_pic_mode_chg_status_ex
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID set_preset_pic_mode_chg_status_ex(BOOL b_is_chg)
{
    INT32       i4_ret = MENUR_OK;
    INT16       i2_pic_mode = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);

    MENU_LOG_ON_FAIL(i4_ret);

    if(i2_pic_mode < ACFG_PRE_SET_PIC_MODE_NUM)
    {
        a_cfg_set_preset_pic_mode_chg_status_ex(i2_pic_mode,b_is_chg);
    }

    DBG_INFO(("\n####%s(%d)i2_pic_mode=%d\n",__FUNCTION__,__LINE__,i2_pic_mode));


}

/*----------------------------------------------------------------------------
 * Name: _set_vid_pic_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_pic_mode_idx(UINT16 ui2_idx)
{
    UINT16      ui2_id = 0;
    INT16       i2_old_val = 0;
    INT16       i2_old_picture_mode_base = 0;
    INT16       i2_picture_mode_base = 0;
    UINT32      ui4_game_mode = (MLM_MENU_KEY_VID_PIC_MODE_ITEM_GAME - (MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1));
    BOOL        b_old_base_game = 0;
    BOOL        b_new_base_game = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),&i2_old_val);//eg vivi
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CUST_PIC_COPY_BASE),&i2_old_picture_mode_base);

    ui2_idx = cvt_list_box_idx_2_acfg_idx(ui2_idx);
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),(INT16)ui2_idx);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CUST_PIC_COPY_BASE),&i2_picture_mode_base);

    b_old_base_game = i2_old_picture_mode_base 	== ui4_game_mode ?   TRUE : FALSE;
    b_new_base_game = i2_picture_mode_base 		== ui4_game_mode ?   TRUE : FALSE;
    DBG_LOG_PRINT(("[MENU][PIC][%s %d] \
		new idx = %d,\
		old = %d  \
		b_old_base_game:%d  \
		b_new_base_game:%d  \
		i2_picture_mode_base;%d\n",__FUNCTION__,__LINE__,ui2_idx,i2_old_val,b_old_base_game,b_new_base_game,i2_picture_mode_base));

    a_acfg_update_gaming_logo();
#if 0
    //from cust pic mod witch to other picture mode
    //game pic mode, gll default on
    if(b_old_base_game != b_new_base_game || ui2_idx == ui4_game_mode)
    {
        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY);
        if( (ui4_game_mode == i2_picture_mode_base) || (ui4_game_mode == ui2_idx))
        {
            a_cfg_av_set(ui2_id, ACFG_CUST_GAME_LOW_LATENCY_ON);
            a_cfg_av_update(ui2_id);
        }
        else
        {
            a_cfg_av_set(ui2_id, ACFG_CUST_GAME_LOW_LATENCY_AUTO);
            a_cfg_av_update(ui2_id);
        }
    }

    if(i2_old_val != ui2_idx)
    {
        set_delay_lock_cust_pic_mode_status(TRUE);
    }
#endif
}

VOID menu_set_vid_pic_mode_idx(UINT16 ui2_idx)
{
    _set_vid_pic_mode_idx(ui2_idx);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_pic_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_pic_mode_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 &i2_val);
    i2_val =(INT16) cvt_acfg_idx_2_list_box_idx((UINT16)i2_val);

    return (UINT16)i2_val;
}

UINT16 menu_get_vid_pic_mode_idx(VOID)
{
    return _get_vid_pic_mode_idx();
}

static VOID _set_fac_aud_latency_val(INT32 i4_val);
static INT32 _get_fac_aud_latency_val(VOID);
extern HANDLE_T        h_g_acfg_scc_main_vid;

extern BOOL menu_common_is_3d_mode_enable(VOID)
{
    BOOL b_enable = FALSE;

    return b_enable;
}

INT32 menu_mtktvapi_get_3d_mode_idx(UINT16* pui2_cur_idx)
{
    INT16   i2_idx = 0;
    if(pui2_cur_idx == NULL)
    {
       return MENUR_INV_ARG;
    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                 &i2_idx);

    DBG_INFO(("<MENU> Get 3D Mode index:%d.\n", i2_idx));

    *pui2_cur_idx = (UINT16)i2_idx;
    return MENUR_OK;
}

extern BOOL menu_common_is_3d_to_2d_enable(VOID)
{
    return TRUE;
}


INT32 menu_mtktvapi_set_fac_aud_latency(UINT16  ui2_vlue)
{
    _set_fac_aud_latency_val((INT32)ui2_vlue);
    return MENUR_OK;
}
INT32 menu_mtktvapi_get_fac_aud_latency(UINT16*  pui2_vlue)
{
    if(pui2_vlue == NULL)
    {
        return MENUR_INV_ARG;
    }
    *pui2_vlue = (UINT16)_get_fac_aud_latency_val();
    return MENUR_OK;
}

BOOL menu_mtktvapi_is_film_mode_enabled(VOID)
{
    return TRUE;
}

INT32 menu_mtktvapi_set_uart_fac_mode(BOOL  b_set)
{
    return MENUR_OK;
}
INT32 menu_mtktvapi_get_uart_fac_mode (BOOL* pb_set)
{
    //UINT32 ui4_current_mode = 0;

    //*pb_set = ((ui4_current_mode&IOM_UART_OPERATION_MODE_FACTORY) == 0 ? 0 : 1);  --> must be 0 , CID:4491063

    *pb_set = 0;
    return MENUR_OK;
}

extern BOOL menu_common_is_lr_switch_enable(VOID)
{
    return FALSE;
}

extern BOOL menu_common_is_img_safety_enable(VOID)
{
    return FALSE;
}

extern BOOL menu_common_is_3d_hide(VOID)
{
    return TRUE;
}

extern BOOL menu_common_is_protrude_enable(VOID)
{
    return FALSE;
}

INT32 menu_mtktvapi_set_flip_mode(BOOL b_flip_on )
{
    INT32 i4_ret;

#ifdef APP_SUPPORT_STR_CORE_OFF
    UINT32 ui4_icl_val = ICL_RECID_FB_DISABLE_MASK_FLIP_MIRROR;
    SIZE_T z_size      = sizeof(UINT32);
#endif

    i4_ret = c_scc_vid_set_flip(h_g_acfg_scc_main_vid, (BOOL)b_flip_on);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_SUPPORT_STR_CORE_OFF
    i4_ret = a_icl_set (ICL_MAKE_ID (ICL_GRPID_FB, ICL_RECID_FB_DISABLE_MASK), (VOID*)&ui4_icl_val, z_size);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
   return i4_ret;

}
INT32 menu_mtktvapi_get_flip_mode(BOOL* pb_flip_on)
{
    INT32 i4_ret;
    BOOL  b_flip = FALSE;
    if(pb_flip_on == NULL)
    {
        return MENUR_INV_ARG;
    }
    i4_ret = c_scc_vid_get_flip(h_g_acfg_scc_main_vid, &b_flip);
    MENU_LOG_ON_FAIL(i4_ret);

    *pb_flip_on = b_flip;

    return MENUR_OK;
}

BOOL menu_mtktvapi_is_game_mode_enabled(VOID)
{
    return TRUE;
}

extern BOOL menu_common_is_osd_depth_enable(VOID)
{
        return FALSE;
}

INT32 menu_mtktvapi_set_burning_mode(BOOL  b_burning_mask_set)
{
    UINT8   ui1_fac_mode = 0;

    a_cfg_get_factory_mode(&ui1_fac_mode);

    if(b_burning_mask_set)
    {
        ui1_fac_mode = (UINT8)(ui1_fac_mode | APP_CFG_FAC_MODE_BURNING_MASK);
    }
    else
    {
        ui1_fac_mode = (UINT8)(ui1_fac_mode & (~APP_CFG_FAC_MODE_BURNING_MASK));
    }

    a_cfg_set_factory_mode(ui1_fac_mode);

    a_cfg_update_factory_mode();

    a_cfg_store();
    return MENUR_OK;
}
INT32 menu_mtktvapi_get_burning_mode (BOOL* pb_burning_mask_set)
{
    UINT8   ui1_fac_mode = 0;
    if(pb_burning_mask_set == NULL)
    {
        return MENUR_INV_ARG;
    }

    a_cfg_get_factory_mode(&ui1_fac_mode);

    *pb_burning_mask_set = ((ui1_fac_mode & APP_CFG_FAC_MODE_BURNING_MASK) == 0 ? 0 : 1);
    return MENUR_OK;
}
#ifdef APP_LOCAL_DIMMING_SUPPORT
INT32 menu_mtktvapi_get_local_dimming_mode (BOOL* pb_set)
{
    INT32         i4_ret=0;
    SCC_VID_LOCAL_DIMMING_TYPE_T e_type=SCC_VID_LOCAL_DIMMING_TYPE_OFF;
    if(pb_set == NULL)
    {
        return MENUR_INV_ARG;
    }

    i4_ret=c_scc_vid_get_local_dimming_mode(h_g_acfg_scc_main_vid,
                                     &e_type);
    MENU_LOG_ON_FAIL(i4_ret);

    switch(e_type)
    {
        case SCC_VID_LOCAL_DIMMING_TYPE_OFF:
        {
            *pb_set = FALSE;
        }
        break;

        case SCC_VID_LOCAL_DIMMING_TYPE_LOW:
        case SCC_VID_LOCAL_DIMMING_TYPE_MID:
        case SCC_VID_LOCAL_DIMMING_TYPE_HIG:
        {
            *pb_set = TRUE;
        }
        break;

        default :
        {
            *pb_set = FALSE;
        }
        break;
    }

    return i4_ret;
}

INT32 menu_mtktvapi_set_local_dimming_mode(BOOL b_set)
{
    INT32         i4_ret=0;
    SCC_VID_LOCAL_DIMMING_TYPE_T e_type=SCC_VID_LOCAL_DIMMING_TYPE_OFF;

    e_type = SCC_VID_LOCAL_DIMMING_TYPE_OFF;
    if(b_set)
    {
        e_type = SCC_VID_LOCAL_DIMMING_TYPE_LOW;
    }

    i4_ret=c_scc_vid_set_local_dimming_mode(h_g_acfg_scc_main_vid,
                                            e_type);
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}
#endif

INT32 menu_mtktvapi_set_mirror_mode(BOOL  b_set)
{
    INT32 i4_ret;
#ifdef APP_SUPPORT_STR_CORE_OFF
    UINT32 ui4_icl_val = ICL_RECID_FB_DISABLE_MASK_FLIP_MIRROR;
    SIZE_T z_size      = sizeof(UINT32);
#endif

    i4_ret = c_scc_vid_set_mirror(h_g_acfg_scc_main_vid, b_set);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_SUPPORT_STR_CORE_OFF
    i4_ret = a_icl_set (ICL_MAKE_ID (ICL_GRPID_FB, ICL_RECID_FB_DISABLE_MASK), (VOID*)&ui4_icl_val, z_size);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    return i4_ret;
}

INT32 menu_mtktvapi_get_mirror_mode(BOOL* pb_set)
{
    INT32 i4_ret;
    BOOL   b_mirror = FALSE;
    if(pb_set == NULL)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = c_scc_vid_get_mirror(h_g_acfg_scc_main_vid, &b_mirror);
    MENU_LOG_ON_FAIL(i4_ret);

    *pb_set = b_mirror;

    return i4_ret;
}

INT32 menu_mtktvapi_set_tuner_type(MTKTVAPI_TUNER_TYPE_T  e_tuner_type, BOOL select_channel_flag)
{
    UINT16      ui2_svl_id;
    CHAR*       ps_src_name;
    UINT8       ui1_tuner_type = APP_CFG_BS_SRC_AIR ;

    switch (e_tuner_type)
    {
    case MTKTVAPI_TUNER_TYPE_AIR:     /* air */
        ui1_tuner_type = APP_CFG_BS_SRC_AIR ;
        break ;

    case MTKTVAPI_TUNER_TYPE_CAB:     /* cab */
        ui1_tuner_type = APP_CFG_BS_SRC_CABLE ;
        break ;
    case MTKTVAPI_TUNER_TYPE_SAT_PREFERRED:     /* sat */
    case MTKTVAPI_TUNER_TYPE_SAT_GENERAL:
        ui1_tuner_type = APP_CFG_BS_SRC_SAT ;
        break ;

    default:
        DBG_ERROR(("<MENU>Invalid argument\r\n"));
        return MENUR_INV_ARG;
    }

    /* save count setting */
    a_cfg_set_tuner_type(APP_CFG_RECID_BS_SRC, ui1_tuner_type);

    /* sync it */
    a_cfg_get_tuner_sync_src(&ui2_svl_id, &ps_src_name);
    a_cfg_set_tuner_sync_src(ui2_svl_id, ps_src_name) ;

#ifdef APP_SEPARATE_INP_SRC_FOR_ATV_DTV
#ifndef SYS_CN_SEPARATE_DTV_SVL
    /* clean svl & tsl (& sat?) */
    {
        MENU_LOG_ON_FAIL (c_svl_clean (t_g_menu_common.h_svl_air[0])) ;
        MENU_LOG_ON_FAIL (c_tsl_clean (t_g_menu_common.h_tsl_air[0])) ;

        MENU_LOG_ON_FAIL (c_svl_clean (t_g_menu_common.h_svl_cable[0])) ;
        MENU_LOG_ON_FAIL (c_tsl_clean (t_g_menu_common.h_tsl_cable[0])) ;
#ifndef APP_LOL_NWL_DISABLE
         /* clean nwl */
        MENU_LOG_ON_FAIL(c_nwl_clean(t_g_menu_common.h_nwl_air[0]));
         /* clean lol */
        MENU_LOG_ON_FAIL(c_lol_clean(t_g_menu_common.h_lol_air[0]));
#ifdef APP_DVBC_SUPPORT
          /* clean nwl */
        MENU_LOG_ON_FAIL(c_nwl_clean(t_g_menu_common.h_nwl_cable[0]));
         /* clean lol */
        MENU_LOG_ON_FAIL(c_lol_clean(t_g_menu_common.h_lol_cable[0]));
#endif
#endif

    }
#endif
#endif

#ifdef APP_DVBS_UI_ALPHA_SUPPORT
#ifdef APP_TWO_SAT_CHLIST
        menu_dvb_special_deal_with_set_tuner_mode_idx((UINT16)e_tuner_type);
#endif
#endif

#ifdef APP_MENU_DONT_SKIP_FAKE_CHANNEL_WHEN_TOGGLE_TUNER_MODE

    /* Reselect the current channel. Don't skip fake channel. */
    menu_select_crnt_or_first_channel(FALSE);

#else

    /* Reselect the current channel. Skip the fake channel. */
    menu_select_crnt_or_first_channel(TRUE);

#endif /* APP_MENU_DONT_SKIP_FAKE_CHANNEL_WHEN_TOGGLE_TUNER_MODE */

    return MENUR_OK;
}

extern BOOL menu_common_is_dof_enable(VOID)
{
    return FALSE;
}

INT32 menu_mtktvapi_set_3d_mode_idx(UINT16 ui2_idx)
{

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                 (INT16)ui2_idx);
    DBG_INFO(("<MENU> Set 3D Mode index:%d.\n", ui2_idx));

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));
    if (a_cfg_update_screen_mode_ex() != APP_CFGR_OK){
        DBG_ERROR(("<MENU> Set 3D Mode index fail"));	//Coverity ID:4490517
    }
    return MENUR_OK;
}


extern BOOL menu_common_is_distance_to_tv_enable(VOID)
{

    return FALSE;
}

extern BOOL menu_common_is_3d_navigation_enable(VOID)
{

    return FALSE;
}

extern BOOL menu_common_is_film_mode_hide(VOID)
{
    INT32          i4_ret=0;
    TV_MODE_T      e_tv_mode=TV_MODE_TYPE_NORMAL;
    TV_WIN_ID_T    e_win_id=TV_WIN_ID_MAIN;
    ISL_REC_T      t_isl_rec;
    BOOL           b_hide = FALSE;

    c_memset(&t_isl_rec,0,sizeof(ISL_REC_T));

    i4_ret=menu_get_crnt_isl(&t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Get current tv_mode */
    i4_ret=a_tv_get_mode(&e_tv_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=a_tv_get_focus_win(&e_win_id);
    MENU_LOG_ON_FAIL(i4_ret);

    do
    {
        /*VGA->hide*/
        if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
           t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
        {
            b_hide = TRUE;
            break;
        }

        if (TV_WIN_ID_SUB==e_win_id &&
            (TV_MODE_TYPE_PIP == e_tv_mode||
            TV_MODE_TYPE_POP == e_tv_mode))/*pip_pop_sub->hide*/
        {
            b_hide = TRUE;
            break;
        }

        b_hide = FALSE;
    }while(0);
    return b_hide;
}

BOOL menu_mtktvapi_is_film_mode_hide(VOID)
{
    return menu_common_is_film_mode_hide();
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_bri
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_bri_val(INT32 i4_val)
{
    INT16   i2_pic_mode;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_set(ui2_id, (INT16)i4_val);

    a_cfg_av_update(ui2_id);
    DBG_INFO(("\n####%s(%d)i2_pic_mode=%d\n",__FUNCTION__,__LINE__,i2_pic_mode));

    set_preset_pic_mode_chg_status(TRUE);

        rest_event_notify("tv_settings/picture/brightness",i4_val,"");
    _pm_refresh_repaint();
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_bri_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vid_bri_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI);
    INT16   i2_vid_bri;

    a_cfg_av_get(ui2_id, &i2_vid_bri);

    return (INT32)i2_vid_bri;
}


/*----------------------------------------------------------------------------
 * Name: _increase_vid_bri
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_vid_bri(VOID)
{
    INT16   i2_pic_mode;
    INT16   i2_vid_bri = 0;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_incr(ui2_id, &i2_vid_bri);

    DBG_INFO(("\n####%s(%d)i2_pic_mode=%d\n",__FUNCTION__,__LINE__,i2_pic_mode));

    set_preset_pic_mode_chg_status(TRUE);
        rest_event_notify("tv_settings/picture/brightness",i2_vid_bri,"");
    _pm_refresh_repaint();
    return i2_vid_bri;
}

/*----------------------------------------------------------------------------
 * Name: _decrease_vid_bri
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_vid_bri(VOID)
{
    INT16   i2_pic_mode;
    INT16   i2_vid_bri;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_decr(ui2_id, &i2_vid_bri);
    DBG_INFO(("\n####%s(%d)i2_pic_mode=%d\n",__FUNCTION__,__LINE__,i2_pic_mode));

    set_preset_pic_mode_chg_status(TRUE);
    rest_event_notify("tv_settings/picture/brightness",i2_vid_bri,"");

    _pm_refresh_repaint();

    return i2_vid_bri;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_cnt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_cnt_val(INT32 i4_val)
{
    INT16   i2_pic_mode;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_set(ui2_id, (INT16)i4_val);

    a_cfg_av_update(ui2_id);
    set_preset_pic_mode_chg_status(TRUE);

    _pm_refresh_repaint();
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_cnt_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vid_cnt_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT);
    INT16   i2_vid_cnt;

    a_cfg_av_get(ui2_id, &i2_vid_cnt);

    return (INT32)i2_vid_cnt;
}


/*----------------------------------------------------------------------------
 * Name: _increase_vid_cnt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_vid_cnt(VOID)
{
    INT16   i2_pic_mode;
    INT16   i2_vid_cnt;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_incr(ui2_id, &i2_vid_cnt);

    set_preset_pic_mode_chg_status(TRUE);

    _pm_refresh_repaint();
    return i2_vid_cnt;
}

/*----------------------------------------------------------------------------
 * Name: _decrease_vid_cnt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_vid_cnt(VOID)
{
    INT16   i2_pic_mode;
    INT16   i2_vid_cnt;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_decr(ui2_id, &i2_vid_cnt);
    set_preset_pic_mode_chg_status(TRUE);

    _pm_refresh_repaint();

    return i2_vid_cnt;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_sat
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_sat_val(INT32 i4_val)
{
    INT16   i2_pic_mode;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_set(ui2_id, (INT16)i4_val);
    set_preset_pic_mode_chg_status(TRUE);

    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_sat_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vid_sat_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT);
    INT16   i2_vid_sat;

    a_cfg_av_get(ui2_id, &i2_vid_sat);

    return (INT32)i2_vid_sat;
}


/*----------------------------------------------------------------------------
 * Name: _increase_vid_sat
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_vid_sat(VOID)
{
    INT16   i2_pic_mode;
    INT16   i2_vid_sat;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_incr(ui2_id, &i2_vid_sat);

    set_preset_pic_mode_chg_status(TRUE);

    _pm_refresh_repaint();
    return i2_vid_sat;
}

/*----------------------------------------------------------------------------
 * Name: _decrease_vid_sat
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_vid_sat(VOID)
{
    INT16   i2_pic_mode;
    INT16   i2_vid_sat;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_decr(ui2_id, &i2_vid_sat);
    set_preset_pic_mode_chg_status(TRUE);

    _pm_refresh_repaint();

    return i2_vid_sat;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_hue
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_hue_val(INT32 i4_val)
{
    INT16   i2_pic_mode;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_set(ui2_id, (INT16)i4_val);

    a_cfg_av_update(ui2_id);
    set_preset_pic_mode_chg_status(TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_hue_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vid_hue_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE);
    INT16   i2_vid_hue;

    a_cfg_av_get(ui2_id, &i2_vid_hue);

    return (INT32)i2_vid_hue;
}


/*----------------------------------------------------------------------------
 * Name: _increase_vid_hue
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_vid_hue(VOID)
{
    INT16   i2_pic_mode;
    INT16   i2_vid_hue;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_incr(ui2_id, &i2_vid_hue);

    set_preset_pic_mode_chg_status(TRUE);
    _pm_refresh_repaint();
    return i2_vid_hue;
}

/*----------------------------------------------------------------------------
 * Name: _decrease_vid_hue
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_vid_hue(VOID)
{
    INT16   i2_pic_mode;
    INT16   i2_vid_hue;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE);

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_decr(ui2_id, &i2_vid_hue);
    set_preset_pic_mode_chg_status(TRUE);

    _pm_refresh_repaint();

    return i2_vid_hue;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_shp
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_shp_val(INT32 i4_val)
{
    INT16   i2_pic_mode;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP);
    INT16  i2_pre_val = 0;

    a_cfg_av_get(ui2_id, &i2_pre_val);
    if(i2_pre_val != i4_val)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_set(ui2_id, (INT16)i4_val);

    a_cfg_av_update(ui2_id);

    _pm_refresh_repaint();
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_shp_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vid_shp_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP);
    INT16   i2_vid_shp;

    a_cfg_av_get(ui2_id, &i2_vid_shp);

    return (INT32)i2_vid_shp;
}


/*----------------------------------------------------------------------------
 * Name: _incr_vid_shp
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_vid_shp(VOID)
{
    INT16   i2_pic_mode;
    INT16   i2_vid_shp;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP);
    INT32  i4_ret = MENUR_OK;
    INT16  i2_val_min = 0;
    INT16  i2_val_max = 0;
    INT16  i2_pre_val = 0;

    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    a_cfg_av_get(ui2_id, &i2_pre_val);
    if(i2_pre_val != i2_val_max)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_incr(ui2_id, &i2_vid_shp);


    _pm_refresh_repaint();
    return i2_vid_shp;
}

/*----------------------------------------------------------------------------
 * Name: _decr_vid_shp
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_vid_shp(VOID)
{
    INT16   i2_pic_mode;
    INT16   i2_vid_shp;

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP);
    INT32  i4_ret = MENUR_OK;
    INT16  i2_val_min = 0;
    INT16  i2_val_max = 0;
    INT16  i2_pre_val = 0;

    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    a_cfg_av_get(ui2_id, &i2_pre_val);
    if(i2_pre_val != i2_val_min)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

    a_cfg_av_get(ui2_mode_id, &i2_pic_mode);
    a_cfg_av_decr(ui2_id, &i2_vid_shp);


    _pm_refresh_repaint();
    return i2_vid_shp;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_contrast_en_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_contrast_en_idx(UINT16 ui2_val)
{
    INT16   i2_pre_val = 0;
    INT32   i4_ret  = 0;


#if 1 // Use ACFG status
    if( ui2_val )
    {
        if( a_cfg_cust_contrast_en_CheckIfCanTurnOn() == FALSE )
        {
            ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_BLACK_DETAIL,
                DBG_LOG_PRINT(("[MENU][Black_Detail]{%s,%d} => Black_Detail cannot turn on => Do nothing\n", __FUNCTION__,__LINE__ ));
            );
            return;
        }
    }
#endif


    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN), &i2_pre_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN), (INT16)ui2_val);
    MENU_LOG_ON_FAIL(i4_ret);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN));

    if (i2_pre_val != ui2_val)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

}

/*----------------------------------------------------------------------------
 * Name: _get_vid_contrast_en_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_contrast_en_idx(VOID)
{
    INT16   i2_val = 0;

#if 1 // Check ACFG status
    if( a_cfg_cust_contrast_en_CheckIfCanTurnOn() == FALSE )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_BLACK_DETAIL,
            DBG_LOG_PRINT(("[MENU][Black_Detail]{%s,%d} => Black_Detail cannot turn on => Force OFF\n", __FUNCTION__,__LINE__ ));
        );
        return 0;
    }
#else
    if(menu_is_vrr_enable_and_vrr_stream_detect() || a_acfg_cust_is_detect_hdmi_freesync_flag())
    {
        return (UINT16)0;
    }
#endif

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN), &i2_val);

    return (UINT16)i2_val;

}

/*----------------------------------------------------------------------------
 * Name: _set_vid_super_resolution_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_super_resolution_idx(UINT16 ui2_val)
{
    INT16   i2_pre_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SUPER_RESOLUTION_EX), &i2_pre_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SUPER_RESOLUTION_EX), (INT16)ui2_val);
    MENU_LOG_ON_FAIL(i4_ret);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SUPER_RESOLUTION_EX));

    if (i2_pre_val != ui2_val)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

}

VOID menu_set_vid_super_resolution_idx(UINT16 ui2_val)
{
    _set_vid_super_resolution_idx(ui2_val);
}


/*----------------------------------------------------------------------------
 * Name: _get_vid_super_resolution_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_super_resolution_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SUPER_RESOLUTION_EX), &i2_val);

    return (UINT16)i2_val;

}

UINT16 menu_get_vid_super_resolution_idx(VOID)
{
    return _get_vid_super_resolution_idx();
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_edge_enhancement_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_edge_enhancement_idx(UINT16 ui2_val)
{
    INT16   i2_pre_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EDGE_ENHANCEMENT), &i2_pre_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EDGE_ENHANCEMENT), (INT16)ui2_val);
    MENU_LOG_ON_FAIL(i4_ret);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EDGE_ENHANCEMENT));

    if (i2_pre_val != ui2_val)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

}

VOID menu_set_vid_edge_enhancement_idx(UINT16 ui2_val)
{
    _set_vid_edge_enhancement_idx(ui2_val);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_edge_enhancement_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_edge_enhancement_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EDGE_ENHANCEMENT), &i2_val);

    return (UINT16)i2_val;

}
UINT16 menu_get_vid_edge_enhancement_idx(VOID)
{
    return _get_vid_edge_enhancement_idx();
}


#ifdef APP_SUPPPORT_FRC
/*----------------------------------------------------------------------------
 * Name: _set_vid_judder_reduction_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_judder_reduction_idx(INT32 i4_val)
{
    INT16   i2_pre_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION), &i2_pre_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION), (INT16)i4_val);
    MENU_LOG_ON_FAIL(i4_ret);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION));

    if (i2_pre_val != i4_val)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

}

VOID menu_set_vid_judder_reduction_idx(INT32 i4_val)
{
    _set_vid_judder_reduction_idx(i4_val);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_judder_reduction_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vid_judder_reduction_idx(VOID)
{
    INT16   i2_val = 0;

    if(menu_is_vrr_enable_and_vrr_stream_detect() || a_acfg_cust_is_detect_hdmi_freesync_flag())
    {
        return (UINT16)0;
    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION), &i2_val);

    return (INT32)i2_val;

}

INT32 menu_get_vid_judder_reduction_idx(VOID)
{
    return _get_vid_judder_reduction_idx();
}

#endif

/*----------------------------------------------------------------------------
 * Name: _set_vid_local_contrast_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_local_contrast_idx(UINT16 ui2_val)
{
    if( FALSE == a_cfg_cust_local_contrast_CheckIfCanTurnOn() )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_LOCAL_CONTRAST,
            DBG_LOG_PRINT(("[MENU][LocalContrast]{%s: %d} LocalContrast cannot turn on! ==> Skip set\n", __FUNCTION__,__LINE__ ));
        );
        return ;
    }

    INT16   i2_pre_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST), &i2_pre_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST), (INT16)ui2_val);
    MENU_LOG_ON_FAIL(i4_ret);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST));

    if (i2_pre_val != ui2_val)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

}

VOID menu_set_vid_local_contrast_idx(UINT16 ui2_val)
{
    _set_vid_local_contrast_idx(ui2_val);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_local_contrast_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_local_contrast_idx(VOID)
{
#if 1
    if( FALSE == a_cfg_cust_local_contrast_CheckIfCanTurnOn() )
    {
        return 0;
    }
#else
    if(menu_is_vrr_enable_and_vrr_stream_detect() || a_acfg_cust_is_detect_hdmi_freesync_flag())
    {
        return (UINT16)0;
    }
    if (a_acfg_cust_get_dynamic_range () == ACFG_CUST_CONTENT_DV)
    {
        return 0;
    }

#endif

    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST), &i2_val);

    return (UINT16)i2_val;

}

UINT16 menu_get_vid_local_contrast_idx(VOID)
{
    return _get_vid_local_contrast_idx();
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_contour_smoothing_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_contour_smoothing_idx(UINT16 ui2_val)
{
    INT16   i2_pre_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTOUR_SMOTHING), &i2_pre_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTOUR_SMOTHING), (INT16)ui2_val);
    MENU_LOG_ON_FAIL(i4_ret);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTOUR_SMOTHING));

    if (i2_pre_val != ui2_val)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

}

VOID menu_set_vid_contour_smoothing_idx(UINT16 ui2_val)
{
    _set_vid_contour_smoothing_idx(ui2_val);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_contour_smoothing_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_contour_smoothing_idx(VOID)
{
    INT16   i2_val = 0;

    if(menu_is_vrr_enable_and_vrr_stream_detect() || a_acfg_cust_is_detect_hdmi_freesync_flag())
    {
        return (UINT16)0;
    }
    if(a_acfg_cust_is_gll_enable() == TRUE)
    {
        return (UINT16)0;
    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTOUR_SMOTHING), &i2_val);

    return (UINT16)i2_val;

}

UINT16 menu_get_vid_contour_smoothing_idx(VOID)
{
    return _get_vid_contour_smoothing_idx();
}


#ifdef APP_SUPPPORT_FRC
/*----------------------------------------------------------------------------
 * Name: _set_vid_motion_blur_reduction_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_motion_blur_reduction_idx(INT32 i4_val)
{
    INT16   i2_pre_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION), &i2_pre_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION), (INT16)i4_val);
    MENU_LOG_ON_FAIL(i4_ret);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION));

    if (i2_pre_val != i4_val)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

}

VOID menu_set_vid_motion_blur_reduction_idx(INT32 i4_val)
{
    _set_vid_motion_blur_reduction_idx(i4_val);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_motion_blur_reduction_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vid_motion_blur_reduction_idx(VOID)
{
    INT16   i2_val = 0;

    if(menu_is_vrr_enable_and_vrr_stream_detect() || a_acfg_cust_is_detect_hdmi_freesync_flag())
    {
        return (UINT16)0;
    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION), &i2_val);

    return (INT32)i2_val;

}

INT32 menu_get_vid_motion_blur_reduction_idx(VOID)
{
    return _get_vid_motion_blur_reduction_idx();
}

#endif

/*----------------------------------------------------------------------------
 * Name: _set_vid_vss_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_vss_idx(UINT16 ui2_idx)
{
    INT16 i2_pre_VRR_val = 0;
    UINT16 ui2_AcfgId_VRR = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE);

    a_cfg_av_get(ui2_AcfgId_VRR, &i2_pre_VRR_val);

    if( ui2_idx != i2_pre_VRR_val )
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

    a_cfg_av_set( ui2_AcfgId_VRR, (INT16)ui2_idx);

    a_cfg_av_update(ui2_AcfgId_VRR);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION));
}

VOID menu_set_vid_vss_idx(UINT16 ui2_idx)
{
    _set_vid_vss_idx(ui2_idx);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_vss_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_vss_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i2_val);
#if 0
    if(a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE && i2_val != 1)//vrr off
    {
        i2_val = 1;//show vrr on
    }
#endif
    return (UINT16)i2_val;

}

UINT16 menu_get_vid_vss_idx(VOID)
{
    return _get_vid_vss_idx();
}


/*----------------------------------------------------------------------------
 * Name: _set_vid_game_hdr_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_game_hdr_idx(UINT16 ui2_val)
{
    INT16   i2_pre_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_HDR), &i2_pre_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_HDR), (INT16)ui2_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_HDR));
    MENU_LOG_ON_FAIL(i4_ret);

    if (i2_pre_val != ui2_val)
    {
        set_preset_pic_mode_chg_status_ex(TRUE);
    }

}

VOID menu_set_vid_game_hdr_idx(UINT16 ui2_idx)
{
    _set_vid_game_hdr_idx(ui2_idx);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_game_hdr_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_game_hdr_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_HDR), &i2_val);

    return (UINT16)i2_val;

}

UINT16 menu_get_vid_game_hdr_idx(VOID)
{
    return _get_vid_game_hdr_idx();
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_peak_luminance_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_peak_luminance_idx(UINT16 ui2_val)
{
    INT16	i2_pre_val = 0;
    INT32	i4_ret	= 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_PEAK_LUMINANCE), &i2_pre_val);
    MENU_LOG_ON_FAIL(i4_ret);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_PEAK_LUMINANCE), (INT16)ui2_val);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_PEAK_LUMINANCE));

    if (i2_pre_val != ui2_val)
    {
        set_preset_pic_mode_chg_status_ex(TRUE);
    }

}

VOID menu_set_vid_peak_luminance_idx(UINT16 ui2_idx)
{
    _set_vid_peak_luminance_idx(ui2_idx);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_peak_luminance_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_peak_luminance_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_PEAK_LUMINANCE), &i2_val);

    return (UINT16)i2_val;

}

/*----------------------------------------------------------------------------
 * Name: _set_vid_en_view_angle_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_en_view_angle_idx(UINT16 ui2_val)
{
    INT16   i2_pre_val = 0;
    INT32   i4_ret  = 0;


    if( ui2_val ) // Turn On
    {
        // Check if can turn on
        if( a_cfg_cust_enhanced_viewing_angle_IfCanTurnOn() == FALSE )
        {
            DBG_LOG_PRINT(("[MENU]{%s:%d} Warning: Cannot turn on enhanced view angle!!\n", __FUNCTION__, __LINE__));
            return;
        }
    }

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE), &i2_pre_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE), (INT16)ui2_val);
    MENU_LOG_ON_FAIL(i4_ret);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));

    if (i2_pre_val != ui2_val)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_en_view_angle_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_en_view_angle_idx(VOID)
{
    INT16   i2_val = 0;
    INT32   i4_ret = 0;


    // Check if can turn on
    if( a_cfg_cust_enhanced_viewing_angle_IfCanTurnOn() == FALSE )
    {
        DBG_LOG_PRINT(("[MENU]{%s:%d} Warning: Cannot turn on enhanced view angle!! Display OFF\n", __FUNCTION__, __LINE__));
        return (UINT16)ACFG_CUST_COMMON_OFF;
    }

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE), &i2_val);
    MENU_LOG_ON_FAIL(i4_ret);


    return (UINT16)i2_val;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_oled_pixel_shift_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_oled_pixel_shift_idx(UINT16 ui2_val)
{
    a_cfg_cust_set_oled_pixel_shift_value((UINT8)ui2_val);

    //Fix DTV0219623
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OLED_PIXEL_SHIFT));
}

VOID menu_set_vid_oled_pixel_shift_idx(UINT16 ui2_val)
{
    _set_vid_oled_pixel_shift_idx(ui2_val);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_oled_pixel_shift_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_oled_pixel_shift_idx(VOID)
{
    UINT8   ui1_val = 0;

    a_cfg_cust_get_oled_pixel_shift_value(&ui1_val);

    return (UINT16)ui1_val;

}

UINT16 menu_get_vid_oled_pixel_shift_idx(VOID)
{
    return _get_vid_oled_pixel_shift_idx();
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_back_light
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_back_light_val(INT32 i4_val)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT);
    INT16   i2_pre_val = 0;

    a_cfg_av_get(ui2_id, &i2_pre_val);
    if(i2_pre_val != i4_val)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

    MENU_DEBUG_BACKLIGHT(DBG_LOG_PRINT(("[MENU][BACKLIGHT] {%s: %s: %d} _set_vid_back_light_val(%d)\n", __FILE__, __FUNCTION__,__LINE__, i4_val )); );

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);

    _pm_refresh_repaint();
}

VOID menu_set_vid_back_light_val(INT32 i4_val)
{
    _set_vid_back_light_val(i4_val);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_back_light_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vid_back_light_val(VOID)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT);
    INT16   i2_vid_back_light = 0;

    a_cfg_av_get(ui2_id, &i2_vid_back_light);

    MENU_DEBUG_BACKLIGHT(DBG_LOG_PRINT(("[MENU][BACKLIGHT] {%s: %s: %d} i2_vid_back_light:%d\n", __FILE__, __FUNCTION__,__LINE__, i2_vid_back_light )); );

    return (INT32)i2_vid_back_light;
}

INT32 menu_get_vid_back_light_val(VOID)
{
    return _get_vid_back_light_val();
}

#ifdef APP_MENU_ADP_BACK_LIGHT_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_vid_adp_back_light_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_adp_back_light_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT);
    INT16   i2_val = ui2_idx;

    a_cfg_av_set(ui2_id, i2_val);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_adp_back_light_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_adp_back_light_idx(VOID)
{
    INT16   i2_val = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT);

    a_cfg_av_get(ui2_id, &i2_val);
    return i2_val;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _set_vid_gamma_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_gamma_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA);
    INT16   i2_val;
    UINT16  ui2_pre_idx = _get_vid_gamma_idx();

    switch(ui2_idx)
    {
    case 0: /* dark */
        i2_val = 1;
        break;
    case 1: /* middle */
        i2_val = 2;
        break;
    case 2: /* bright */
        i2_val = 3;
        break;
    default:
        i2_val = 2;
    }

    a_cfg_av_set(ui2_id, i2_val);
    a_cfg_av_update(ui2_id);
    if (ui2_pre_idx != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_gamma_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_gamma_idx(VOID)
{
    UINT16  ui2_idx;
    INT16   i2_val = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA);

    a_cfg_av_get(ui2_id, &i2_val);

    switch(i2_val)
    {
    case 1:
        ui2_idx = 0;    /* dark */
        break;
    case 3:
        ui2_idx = 2;    /* bright */
        break;
    default:
        ui2_idx = 1;    /* middle */
        break;
    }
    return  ui2_idx;
}

/*----------------------------------------------------------------------------
 * Factory Color Gain R
 ----------------------------------------------------------------------------*/
#ifdef APP_CFG_FAC_CLR_TEMP
static VOID _set_vid_fac_clr_gain_r_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_R);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);
    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R),
                                             (INT16) i4_val);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));
}

static INT32 _get_vid_fac_clr_gain_r_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_R);
    INT16   i2_vid_clr_gain_r;

    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_r);

    return (INT32)i2_vid_clr_gain_r;
}

static INT32 _incr_vid_fac_clr_gain_r(VOID)
{
    INT16   i2_vid_clr_gain_r;
    INT16   i2_clr_gain_r   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_R);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_r);

    if (i2_clr_gain_r >= i2_max)
    {
        i2_vid_clr_gain_r = i2_max;
    }
    else if (i2_clr_gain_r <= i2_min)
    {
        i2_vid_clr_gain_r = i2_min + 1;
    }
    else
    {
        i2_vid_clr_gain_r = i2_clr_gain_r + 1;
    }

    if (i2_clr_gain_r != i2_vid_clr_gain_r)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_r);
        a_cfg_av_update(ui2_mode_id);
    }

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R),
                                             (INT16) i2_vid_clr_gain_r);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));

    return i2_vid_clr_gain_r;
}

static INT32 _decr_vid_fac_clr_gain_r(VOID)
{
    INT16   i2_vid_clr_gain_r;
    INT16   i2_clr_gain_r   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_R);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_r);
    if (i2_clr_gain_r >= i2_max)
    {
        i2_vid_clr_gain_r = (i2_max-1);
    }
    else if (i2_clr_gain_r <= i2_min)
    {
        i2_vid_clr_gain_r = i2_min;
    }
    else
    {
        i2_vid_clr_gain_r = i2_clr_gain_r - 1;
    }

    if (i2_clr_gain_r != i2_vid_clr_gain_r)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_r);
        a_cfg_av_update(ui2_mode_id);
    }

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R),
                                             (INT16) i2_vid_clr_gain_r);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R));

    return i2_vid_clr_gain_r;
}
#else
static VOID _set_vid_fac_clr_gain_r_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);
}

static INT32 _get_vid_fac_clr_gain_r_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    INT16   i2_vid_clr_gain_r;

    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_r);

    return (INT32)i2_vid_clr_gain_r;
}

static INT32 _incr_vid_fac_clr_gain_r(VOID)
{
    INT16   i2_vid_clr_gain_r;
    INT16   i2_clr_gain_r   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_r);

    if (i2_clr_gain_r >= i2_max)
    {
        i2_vid_clr_gain_r = i2_max;
    }
    else if (i2_clr_gain_r <= i2_min)
    {
        i2_vid_clr_gain_r = i2_min + 1;
    }
    else
    {
        i2_vid_clr_gain_r = i2_clr_gain_r + 1;
    }

    if (i2_clr_gain_r != i2_vid_clr_gain_r)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_r);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_gain_r;
}

static INT32 _decr_vid_fac_clr_gain_r(VOID)
{
    INT16   i2_vid_clr_gain_r;
    INT16   i2_clr_gain_r   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_r);
    if (i2_clr_gain_r >= i2_max)
    {
        i2_vid_clr_gain_r = (i2_max-1);
    }
    else if (i2_clr_gain_r <= i2_min)
    {
        i2_vid_clr_gain_r = i2_min;
    }
    else
    {
        i2_vid_clr_gain_r = i2_clr_gain_r - 1;
    }

    if (i2_clr_gain_r != i2_vid_clr_gain_r)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_r);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_gain_r;
}
#endif

/*----------------------------------------------------------------------------
 * Factory Color Gain G
 ----------------------------------------------------------------------------*/
#ifdef APP_CFG_FAC_CLR_TEMP
static VOID _set_vid_fac_clr_gain_g_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_G);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G),
                                             (INT16) i4_val);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));
}

static INT32 _get_vid_fac_clr_gain_g_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_G);
    INT16   i2_vid_clr_gain_g;

    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_g);

    return (INT32)i2_vid_clr_gain_g;
}

static INT32 _incr_vid_fac_clr_gain_g(VOID)
{
    INT16   i2_vid_clr_gain_g;
    INT16   i2_clr_gain_g   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_G);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_g);

    if (i2_clr_gain_g >= i2_max)
    {
        i2_vid_clr_gain_g = i2_max;
    }
    else if (i2_clr_gain_g <= i2_min)
    {
        i2_vid_clr_gain_g = i2_min + 1;
    }
    else
    {
        i2_vid_clr_gain_g = i2_clr_gain_g + 1;
    }

    if (i2_clr_gain_g != i2_vid_clr_gain_g)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_g);
        a_cfg_av_update(ui2_mode_id);
    }

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G),
                                             (INT16) i2_vid_clr_gain_g);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));

    return i2_vid_clr_gain_g;
}

static INT32 _decr_vid_fac_clr_gain_g(VOID)
{
    INT16   i2_vid_clr_gain_g;
    INT16   i2_clr_gain_g   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_G);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_g);
    if (i2_clr_gain_g >= i2_max)
    {
        i2_vid_clr_gain_g = (i2_max-1);
    }
    else if (i2_clr_gain_g <= i2_min)
    {
        i2_vid_clr_gain_g = i2_min;
    }
    else
    {
        i2_vid_clr_gain_g = i2_clr_gain_g - 1;
    }

    if (i2_clr_gain_g != i2_vid_clr_gain_g)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_g);
        a_cfg_av_update(ui2_mode_id);
    }

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G),
                                             (INT16) i2_vid_clr_gain_g);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G));

    return i2_vid_clr_gain_g;
}
#else
static VOID _set_vid_fac_clr_gain_g_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);
}

static INT32 _get_vid_fac_clr_gain_g_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G);
    INT16   i2_vid_clr_gain_g;

    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_g);

    return (INT32)i2_vid_clr_gain_g;
}

static INT32 _incr_vid_fac_clr_gain_g(VOID)
{
    INT16   i2_vid_clr_gain_g;
    INT16   i2_clr_gain_g   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_g);

    if (i2_clr_gain_g >= i2_max)
    {
        i2_vid_clr_gain_g = i2_max;
    }
    else if (i2_clr_gain_g <= i2_min)
    {
        i2_vid_clr_gain_g = i2_min + 1;
    }
    else
    {
        i2_vid_clr_gain_g = i2_clr_gain_g + 1;
    }

    if (i2_clr_gain_g != i2_vid_clr_gain_g)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_g);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_gain_g;
}

static INT32 _decr_vid_fac_clr_gain_g(VOID)
{
    INT16   i2_vid_clr_gain_g;
    INT16   i2_clr_gain_g   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_g);
    if (i2_clr_gain_g >= i2_max)
    {
        i2_vid_clr_gain_g = (i2_max-1);
    }
    else if (i2_clr_gain_g <= i2_min)
    {
        i2_vid_clr_gain_g = i2_min;
    }
    else
    {
        i2_vid_clr_gain_g = i2_clr_gain_g - 1;
    }

    if (i2_clr_gain_g != i2_vid_clr_gain_g)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_g);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_gain_g;
}
#endif

/*----------------------------------------------------------------------------
 * Factory Color Gain B
 ----------------------------------------------------------------------------*/
#ifdef APP_CFG_FAC_CLR_TEMP
static VOID _set_vid_fac_clr_gain_b_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_B);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B),
                                             (INT16) i4_val);

        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));
}

static INT32 _get_vid_fac_clr_gain_b_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_B);
    INT16   i2_vid_clr_gain_b;

    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_b);

    return (INT32)i2_vid_clr_gain_b;
}

static INT32 _incr_vid_fac_clr_gain_b(VOID)
{
    INT16   i2_vid_clr_gain_b;
    INT16   i2_clr_gain_b   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_B);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_b);

    if (i2_clr_gain_b >= i2_max)
    {
        i2_vid_clr_gain_b = i2_max;
    }
    else if (i2_clr_gain_b <= i2_min)
    {
        i2_vid_clr_gain_b = i2_min + 1;
    }
    else
    {
        i2_vid_clr_gain_b = i2_clr_gain_b + 1;
    }

    if (i2_clr_gain_b != i2_vid_clr_gain_b)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_b);
        a_cfg_av_update(ui2_mode_id);
    }

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B),
                                             (INT16) i2_vid_clr_gain_b);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));

    return i2_vid_clr_gain_b;
}

static INT32 _decr_vid_fac_clr_gain_b(VOID)
{
    INT16   i2_vid_clr_gain_b;
    INT16   i2_clr_gain_r   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_GAIN_B);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_r);
    if (i2_clr_gain_r >= i2_max)
    {
        i2_vid_clr_gain_b = (i2_max-1);
    }
    else if (i2_clr_gain_r <= i2_min)
    {
        i2_vid_clr_gain_b = i2_min;
    }
    else
    {
        i2_vid_clr_gain_b = i2_clr_gain_r - 1;
    }

    if (i2_clr_gain_r != i2_vid_clr_gain_b)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_b);
        a_cfg_av_update(ui2_mode_id);
    }

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B),
                                             (INT16) i2_vid_clr_gain_b);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B));

    return i2_vid_clr_gain_b;
}
#else
static VOID _set_vid_fac_clr_gain_b_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);
}

static INT32 _get_vid_fac_clr_gain_b_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B);
    INT16   i2_vid_clr_gain_b;

    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_b);

    return (INT32)i2_vid_clr_gain_b;
}

static INT32 _incr_vid_fac_clr_gain_b(VOID)
{
    INT16   i2_vid_clr_gain_b;
    INT16   i2_clr_gain_b   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_b);

    if (i2_clr_gain_b >= i2_max)
    {
        i2_vid_clr_gain_b = i2_max;
    }
    else if (i2_clr_gain_b <= i2_min)
    {
        i2_vid_clr_gain_b = i2_min + 1;
    }
    else
    {
        i2_vid_clr_gain_b = i2_clr_gain_b + 1;
    }

    if (i2_clr_gain_b != i2_vid_clr_gain_b)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_b);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_gain_b;
}

static INT32 _decr_vid_fac_clr_gain_b(VOID)
{
    INT16   i2_vid_clr_gain_b;
    INT16   i2_clr_gain_b   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_b);
    if (i2_clr_gain_b >= i2_max)
    {
        i2_vid_clr_gain_b = (i2_max-1);
    }
    else if (i2_clr_gain_b <= i2_min)
    {
        i2_vid_clr_gain_b = i2_min;
    }
    else
    {
        i2_vid_clr_gain_b = i2_clr_gain_b - 1;
    }

    if (i2_clr_gain_b != i2_vid_clr_gain_b)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_b);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_gain_b;
}
#endif

/*----------------------------------------------------------------------------
 * Factory Color Offset R
 ----------------------------------------------------------------------------*/
#ifdef APP_CFG_FAC_CLR_TEMP
static VOID _set_vid_fac_clr_offset_r_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_R);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R),
                                             (INT16) i4_val);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));
}

static INT32 _get_vid_fac_clr_offset_r_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_R);
    INT16   i2_vid_clr_offset_r;

    a_cfg_av_get(ui2_id, &i2_vid_clr_offset_r);

    return (INT32)i2_vid_clr_offset_r;
}

static INT32 _incr_vid_fac_clr_offset_r(VOID)
{
    INT16   i2_vid_clr_offset_r;
    INT16   i2_clr_offset_r   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_R);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_r);

    if (i2_clr_offset_r >= i2_max)
    {
        i2_vid_clr_offset_r = i2_max;
    }
    else if (i2_clr_offset_r <= i2_min)
    {
        i2_vid_clr_offset_r = i2_min + 1;
    }
    else
    {
        i2_vid_clr_offset_r = i2_clr_offset_r + 1;
    }

    if (i2_clr_offset_r != i2_vid_clr_offset_r)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_r);
        a_cfg_av_update(ui2_mode_id);
    }

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R),
                                             (INT16) i2_vid_clr_offset_r);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));

    return i2_vid_clr_offset_r;
}

static INT32 _decr_vid_fac_clr_offset_r(VOID)
{
    INT16   i2_vid_clr_offset_r;
    INT16   i2_clr_offset_r   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_R);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_r);
    if (i2_clr_offset_r >= i2_max)
    {
        i2_vid_clr_offset_r = (i2_max-1);
    }
    else if (i2_clr_offset_r <= i2_min)
    {
        i2_vid_clr_offset_r = i2_min;
    }
    else
    {
        i2_vid_clr_offset_r = i2_clr_offset_r - 1;
    }

    if (i2_clr_offset_r != i2_vid_clr_offset_r)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_r);
        a_cfg_av_update(ui2_mode_id);
    }

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R),
                                             (INT16) i2_vid_clr_offset_r);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R));

    return i2_vid_clr_offset_r;
}
#else
static VOID _set_vid_fac_clr_offset_r_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);
}

static INT32 _get_vid_fac_clr_offset_r_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R);
    INT16   i2_vid_clr_offset_r;

    a_cfg_av_get(ui2_id, &i2_vid_clr_offset_r);

    return (INT32)i2_vid_clr_offset_r;
}

static INT32 _incr_vid_fac_clr_offset_r(VOID)
{
    INT16   i2_vid_clr_offset_r;
    INT16   i2_clr_offset_r   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_r);

    if (i2_clr_offset_r >= i2_max)
    {
        i2_vid_clr_offset_r = i2_max;
    }
    else if (i2_clr_offset_r <= i2_min)
    {
        i2_vid_clr_offset_r = i2_min + 1;
    }
    else
    {
        i2_vid_clr_offset_r = i2_clr_offset_r + 1;
    }

    if (i2_clr_offset_r != i2_vid_clr_offset_r)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_r);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_offset_r;
}

static INT32 _decr_vid_fac_clr_offset_r(VOID)
{
    INT16   i2_vid_clr_offset_r;
    INT16   i2_clr_offset_r   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_r);
    if (i2_clr_offset_r >= i2_max)
    {
        i2_vid_clr_offset_r = (i2_max-1);
    }
    else if (i2_clr_offset_r <= i2_min)
    {
        i2_vid_clr_offset_r = i2_min;
    }
    else
    {
        i2_vid_clr_offset_r = i2_clr_offset_r - 1;
    }

    if (i2_clr_offset_r != i2_vid_clr_offset_r)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_r);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_offset_r;
}
#endif

/*----------------------------------------------------------------------------
 * Factory Color Offset G
 ----------------------------------------------------------------------------*/
#ifdef APP_CFG_FAC_CLR_TEMP
static VOID _set_vid_fac_clr_offset_g_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_G);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G),
                                             (INT16) i4_val);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));
}

static INT32 _get_vid_fac_clr_offset_g_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_G);
    INT16   i2_vid_clr_offset_g;

    a_cfg_av_get(ui2_id, &i2_vid_clr_offset_g);

    return (INT32)i2_vid_clr_offset_g;
}

static INT32 _incr_vid_fac_clr_offset_g(VOID)
{
    INT16   i2_vid_clr_offset_g;
    INT16   i2_clr_offset_g   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_G);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_g);

    if (i2_clr_offset_g >= i2_max)
    {
        i2_vid_clr_offset_g = i2_max;
    }
    else if (i2_clr_offset_g <= i2_min)
    {
        i2_vid_clr_offset_g = i2_min + 1;
    }
    else
    {
        i2_vid_clr_offset_g = i2_clr_offset_g + 1;
    }

    if (i2_clr_offset_g != i2_vid_clr_offset_g)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_g);
        a_cfg_av_update(ui2_mode_id);
    }

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G),
                                             (INT16) i2_vid_clr_offset_g);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G));

    return i2_vid_clr_offset_g;
}

static INT32 _decr_vid_fac_clr_offset_g(VOID)
{
    INT16   i2_vid_clr_offset_g;
    INT16   i2_clr_offset_g   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_G);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_g);
    if (i2_clr_offset_g >= i2_max)
    {
        i2_vid_clr_offset_g = (i2_max-1);
    }
    else if (i2_clr_offset_g <= i2_min)
    {
        i2_vid_clr_offset_g = i2_min;
    }
    else
    {
        i2_vid_clr_offset_g = i2_clr_offset_g - 1;
    }

    if (i2_clr_offset_g != i2_vid_clr_offset_g)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_g);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_offset_g;
}
#else
static VOID _set_vid_fac_clr_offset_g_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);
}

static INT32 _get_vid_fac_clr_offset_g_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G);
    INT16   i2_vid_clr_offset_g;

    a_cfg_av_get(ui2_id, &i2_vid_clr_offset_g);

    return (INT32)i2_vid_clr_offset_g;
}

static INT32 _incr_vid_fac_clr_offset_g(VOID)
{
    INT16   i2_vid_clr_offset_g;
    INT16   i2_clr_offset_g   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_g);

    if (i2_clr_offset_g >= i2_max)
    {
        i2_vid_clr_offset_g = i2_max;
    }
    else if (i2_clr_offset_g <= i2_min)
    {
        i2_vid_clr_offset_g = i2_min + 1;
    }
    else
    {
        i2_vid_clr_offset_g = i2_clr_offset_g + 1;
    }

    if (i2_clr_offset_g != i2_vid_clr_offset_g)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_g);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_offset_g;
}

static INT32 _decr_vid_fac_clr_offset_g(VOID)
{
    INT16   i2_vid_clr_offset_g;
    INT16   i2_clr_offset_g   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_g);
    if (i2_clr_offset_g >= i2_max)
    {
        i2_vid_clr_offset_g = (i2_max-1);
    }
    else if (i2_clr_offset_g <= i2_min)
    {
        i2_vid_clr_offset_g = i2_min;
    }
    else
    {
        i2_vid_clr_offset_g = i2_clr_offset_g - 1;
    }

    if (i2_clr_offset_g != i2_vid_clr_offset_g)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_g);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_offset_g;
}
#endif

/*----------------------------------------------------------------------------
 * Factory Color Offset B
 ----------------------------------------------------------------------------*/
#ifdef APP_CFG_FAC_CLR_TEMP
static VOID _set_vid_fac_clr_offset_b_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_B);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B),
                                             (INT16) i4_val);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));
}

static INT32 _get_vid_fac_clr_offset_b_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_B);
    INT16   i2_vid_clr_offset_b;

    a_cfg_av_get(ui2_id, &i2_vid_clr_offset_b);

    return (INT32)i2_vid_clr_offset_b;
}

static INT32 _incr_vid_fac_clr_offset_b(VOID)
{
    INT16   i2_vid_clr_offset_b;
    INT16   i2_clr_offset_b   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_B);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_b);

    if (i2_clr_offset_b >= i2_max)
    {
        i2_vid_clr_offset_b = i2_max;
    }
    else if (i2_clr_offset_b <= i2_min)
    {
        i2_vid_clr_offset_b = i2_min + 1;
    }
    else
    {
        i2_vid_clr_offset_b = i2_clr_offset_b + 1;
    }

    if (i2_clr_offset_b != i2_vid_clr_offset_b)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_b);
        a_cfg_av_update(ui2_mode_id);
    }

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B),
                                             (INT16) i2_vid_clr_offset_b);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));

    return i2_vid_clr_offset_b;
}

static INT32 _decr_vid_fac_clr_offset_b(VOID)
{
    INT16   i2_vid_clr_offset_b;
    INT16   i2_clr_offset_b   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FAC_OFFSET_B);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B), &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_b);
    if (i2_clr_offset_b >= i2_max)
    {
        i2_vid_clr_offset_b = (i2_max-1);
    }
    else if (i2_clr_offset_b <= i2_min)
    {
        i2_vid_clr_offset_b = i2_min;
    }
    else
    {
        i2_vid_clr_offset_b = i2_clr_offset_b - 1;
    }

    if (i2_clr_offset_b != i2_vid_clr_offset_b)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_b);
        a_cfg_av_update(ui2_mode_id);
    }

    a_cfg_custom_set_factory_colortemp(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B),
                                             (INT16) i2_vid_clr_offset_b);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B));

    return i2_vid_clr_offset_b;
}
#else
static VOID _set_vid_fac_clr_offset_b_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_id);
}

static INT32 _get_vid_fac_clr_offset_b_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B);
    INT16   i2_vid_clr_offset_b;

    a_cfg_av_get(ui2_id, &i2_vid_clr_offset_b);

    return (INT32)i2_vid_clr_offset_b;
}

static INT32 _incr_vid_fac_clr_offset_b(VOID)
{
    INT16   i2_vid_clr_offset_b;
    INT16   i2_clr_offset_b   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_b);

    if (i2_clr_offset_b >= i2_max)
    {
        i2_vid_clr_offset_b = i2_max;
    }
    else if (i2_clr_offset_b <= i2_min)
    {
        i2_vid_clr_offset_b = i2_min + 1;
    }
    else
    {
        i2_vid_clr_offset_b = i2_clr_offset_b + 1;
    }

    if (i2_clr_offset_b != i2_vid_clr_offset_b)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_b);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_offset_b;
}

static INT32 _decr_vid_fac_clr_offset_b(VOID)
{
    INT16   i2_vid_clr_offset_b;
    INT16   i2_clr_offset_b   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_offset_b);
    if (i2_clr_offset_b >= i2_max)
    {
        i2_vid_clr_offset_b = (i2_max-1);
    }
    else if (i2_clr_offset_b <= i2_min)
    {
        i2_vid_clr_offset_b = i2_min;
    }
    else
    {
        i2_vid_clr_offset_b = i2_clr_offset_b - 1;
    }

    if (i2_clr_offset_b != i2_vid_clr_offset_b)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_offset_b);
        a_cfg_av_update(ui2_mode_id);
    }

    return i2_vid_clr_offset_b;
}
#endif

/*----------------------------------------------------------------------------
 * Color Temperature
 ----------------------------------------------------------------------------*/
static VOID _set_vid_clr_tmp_mode_idx(UINT16 ui2_idx)
{
    UINT16  ui2_pre_idx = _get_vid_clr_tmp_mode_idx();
    UINT16  ui2_idx_tmp = ui2_idx;

    /*turn off test pattern when change color temp*/
    a_menu_test_patterns_turn_off();

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), (INT16)ui2_idx);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));

#ifdef NEVER
#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT
    a_cfg_custom_set_light_sensor_GAMMA_index((INT16)ui2_idx);
#endif

#ifdef APP_CFG_XVYCC_CHECK
    /* After user modify color temperature mode , check xvYCC matrix */
    a_cfg_custom_check_xvYCC();
#endif
#endif /* NEVER */
    if (ui2_pre_idx != ui2_idx_tmp)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

#ifdef NEVER
    i4_ret = a_color_tuner_update_value();
    MENU_LOG_ON_FAIL(i4_ret);

    /*update 11 point: gain num,R,G,B*/
    MENU_LOG_ON_FAIL(a_color_tuner_update_value());
    MENU_LOG_ON_FAIL(a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN)));
#endif /* NEVER */
}

static UINT16 _get_vid_clr_tmp_mode_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_val);

#ifdef NEVER
    switch (i2_val)
    {
        case ACFG_CUST_CLR_TEMP_WARM:
            i2_val = 0;
            break;
        case ACFG_CUST_CLR_TEMP_COOL:
            i2_val = 1;
            break;
        case ACFG_CUST_CLR_TEMP_NORMAL:
            i2_val = 2;
            break;
        default:
            i2_val = 0;
            break;
    }
#endif /* NEVER */

#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT
    a_cfg_custom_set_light_sensor_GAMMA_index(i2_val);
#endif

    return (UINT16)i2_val;
}

/*----------------------------------------------------------------------------
 * clear Action
 ----------------------------------------------------------------------------*/
static VOID _set_vid_clear_action_idx(UINT16 ui2_idx)
{
    /**
     * idx:
    * 0 ----> OFF;
    * 1-----> ON;
    */

    UINT16  ui2_pre_idx = _get_vid_clear_action_idx();

    DBG_LOG_PRINT(("[MENU][ClearAction]{%s: %s: %d} ui2_pre_idx=%d, ui2_idx=%d\n", __FILE__, __FUNCTION__,__LINE__, ui2_pre_idx, ui2_idx));

    if( (ui2_pre_idx == 0) && (ui2_idx == 1) ) // For 0 -> 1
    {
        // Check if can turn on
        BOOL bClearActionCanTurnOn = a_cfg_cust_ClaerAction_if_can_turn_on();
        //DBG_LOG_PRINT(("[ClearAction]{%s: %s: %d} a_cfg_cust_ClaerAction_if_can_turn_on()=> %d\n", __FILE__, __FUNCTION__,__LINE__, bClearActionCanTurnOn ));

        if( FALSE == bClearActionCanTurnOn ) // Cannot turn on
        {
            DBG_LOG_PRINT(("[MENU][ClearAction]{%s: %s: %d} Can't turn on ClearAction\n", __FILE__, __FUNCTION__,__LINE__ ));
            return;
        }
    }

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION), (INT16)ui2_idx);
    DBG_LOG_PRINT(("[MENU][ClearAction][%s %d] APP_CFG_RECID_VID_CLEAR_ACTION %d\n",__FUNCTION__,__LINE__,ui2_idx));

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION));

    if (ui2_pre_idx != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

VOID menu_set_vid_clear_action_idx(UINT16 ui2_idx)
{
    _set_vid_clear_action_idx(ui2_idx);
}

static UINT16 _get_vid_clear_action_idx(VOID)
{
    INT16   i2_val = 0;
    //INT16   i2_vrr = 0;
    //INT32   i4_ret = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION), &i2_val);

    //DBG_LOG_PRINT(("[MENU][ClearAction]{%s: %s: %d} Get i2_val=%d\n", __FILE__, __FUNCTION__,__LINE__, i2_val));

    switch (i2_val)
    {
        case ACFG_CUST_CLEAR_ACTION_OFF:
            i2_val = 0;
            break;
        case ACFG_CUST_CLEAR_ACTION_ON:
            i2_val = 1;
            break;
        default:
            i2_val = 0;
            break;
    }

#if 1
    // If current setting is on, check if support turn on,
    // if cannot turn on, display off directly!
    if( (i2_val == 1) )
    {
        // Check if can turn on
        BOOL bClearActionCanTurnOn = a_cfg_cust_ClaerAction_if_can_turn_on();
        //DBG_LOG_PRINT(("[MENU][ClearAction]{%s: %s: %d} a_cfg_cust_ClaerAction_if_can_turn_on()=> %d\n", __FILE__, __FUNCTION__,__LINE__, bClearActionCanTurnOn ));
        if( FALSE == bClearActionCanTurnOn ) // Cannot turn on
        {
            DBG_LOG_PRINT(("[MENU][ClearAction]{%s: %s: %d} Force UI-ClearAction off\n", __FILE__, __FUNCTION__,__LINE__ ));
            return 0; // Force UI-ClearAction display off!
        }
    }
#else

    if ((a_cfg_cust_is_variable_refresh_rate_support() == TRUE)&&(a_cfg_cust_is_support_progaming_engine() == TRUE))
    {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i2_vrr);
        MENU_LOG_ON_FAIL(i4_ret);

        if(i2_vrr == ACFG_CUST_COMMON_ON)
        {
            i2_val = 0;
        }
        if(menu_is_vrr_enable_and_vrr_stream_detect())
        {
            i2_val = 0;
        }

    }

    if(a_acfg_cust_is_detect_hdmi_freesync_flag())
    {
        i2_val = 0;
    }
#endif

    return (UINT16)i2_val;
}

UINT16 menu_get_vid_clear_action_idx(VOID)
{
    return _get_vid_clear_action_idx();
}

/*----------------------------------------------------------------------------
 * Color Gain R
 ----------------------------------------------------------------------------*/
static VOID _set_vid_clr_gain_r_val(INT32 i4_val)
{
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_mode_id);
    set_preset_pic_mode_chg_status(TRUE);

}

static INT32 _get_vid_clr_gain_r_val(VOID)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    INT16   i2_vid_clr_gain_r;
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_r);

    if (i2_vid_clr_gain_r > i2_max)
    {
        i2_vid_clr_gain_r = i2_max;
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_r);
    }
    else if (i2_vid_clr_gain_r < i2_min)
    {
        i2_vid_clr_gain_r = i2_min;
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_r);
    }

    return (INT32)i2_vid_clr_gain_r;
}

static INT32 _incr_vid_clr_gain_r(VOID)
{
    INT16   i2_vid_clr_gain_r;
    INT16   i2_clr_gain_r   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_r);

    if (i2_clr_gain_r >= i2_max)
    {
        i2_vid_clr_gain_r = i2_max;
    }
    else if (i2_clr_gain_r <= i2_min)
    {
        i2_vid_clr_gain_r = i2_min + 1;
    }
    else
    {
        i2_vid_clr_gain_r = i2_clr_gain_r + 1;
    }

    if (i2_clr_gain_r != i2_vid_clr_gain_r)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_r);
        a_cfg_av_update(ui2_mode_id);
    }

    set_preset_pic_mode_chg_status(TRUE);
    return i2_vid_clr_gain_r;
}

static INT32 _decr_vid_clr_gain_r(VOID)
{
    INT16   i2_vid_clr_gain_r;
    INT16   i2_clr_gain_r   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_r);
    if (i2_clr_gain_r >= i2_max)
    {
        i2_vid_clr_gain_r = (i2_max-1);
    }
    else if (i2_clr_gain_r <= i2_min)
    {
        i2_vid_clr_gain_r = i2_min;
    }
    else
    {
        i2_vid_clr_gain_r = i2_clr_gain_r - 1;
    }

    if (i2_clr_gain_r != i2_vid_clr_gain_r)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_r);
        a_cfg_av_update(ui2_mode_id);
    }

    set_preset_pic_mode_chg_status(TRUE);
    return i2_vid_clr_gain_r;
}

/*----------------------------------------------------------------------------
 * Color Gain G
 ----------------------------------------------------------------------------*/
static VOID _set_vid_clr_gain_g_val(INT32 i4_val)
{
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_mode_id);
    set_preset_pic_mode_chg_status(TRUE);
}

static INT32 _get_vid_clr_gain_g_val(VOID)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G);
    INT16   i2_vid_clr_gain_g;
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_g);

    if (i2_vid_clr_gain_g > i2_max)
    {
        i2_vid_clr_gain_g = i2_max;
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_g);
    }
    else if (i2_vid_clr_gain_g < i2_min)
    {
        i2_vid_clr_gain_g = i2_min;
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_g);
    }

    return (INT32)i2_vid_clr_gain_g;
}

static INT32 _incr_vid_clr_gain_g(VOID)
{
    INT16   i2_vid_clr_gain_g;
    INT16   i2_clr_gain_g   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_g);
    if (i2_clr_gain_g >= i2_max)
    {
        i2_vid_clr_gain_g = i2_max;
    }
    else if (i2_clr_gain_g <= i2_min)
    {
        i2_vid_clr_gain_g = i2_min + 1;
    }
    else
    {
        i2_vid_clr_gain_g = i2_clr_gain_g + 1;
    }

    if (i2_clr_gain_g != i2_vid_clr_gain_g)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_g);
        a_cfg_av_update(ui2_mode_id);
    }

    set_preset_pic_mode_chg_status(TRUE);
    return i2_vid_clr_gain_g;
}

static INT32 _decr_vid_clr_gain_g(VOID)
{
    INT16   i2_vid_clr_gain_g;
    INT16   i2_clr_gain_g   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_g);
    if (i2_clr_gain_g >= i2_max)
    {
        i2_vid_clr_gain_g = i2_max - 1;
    }
    else if (i2_clr_gain_g <= i2_min)
    {
        i2_vid_clr_gain_g = i2_min;
    }
    else
    {
        i2_vid_clr_gain_g = i2_clr_gain_g - 1;
    }

    if (i2_clr_gain_g != i2_vid_clr_gain_g)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_g);
        a_cfg_av_update(ui2_mode_id);
    }

    set_preset_pic_mode_chg_status(TRUE);
    return i2_vid_clr_gain_g;
}

/*----------------------------------------------------------------------------
 * Color Gain B
 ----------------------------------------------------------------------------*/
static VOID _set_vid_clr_gain_b_val(INT32 i4_val)
{
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B);

    a_cfg_av_set(ui2_id, (INT16)i4_val);
    a_cfg_av_update(ui2_mode_id);
    set_preset_pic_mode_chg_status(TRUE);
}

static INT32 _get_vid_clr_gain_b_val(VOID)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B);
    INT16   i2_vid_clr_gain_b;
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_b);

    if (i2_vid_clr_gain_b > i2_max)
    {
        i2_vid_clr_gain_b = i2_max;
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_b);
    }
    else if (i2_vid_clr_gain_b < i2_min)
    {
        i2_vid_clr_gain_b = i2_min;
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_b);
    }

    return (INT32)i2_vid_clr_gain_b;
}

/*----------------------------------------------------------------------------
 * Color offset R
 ----------------------------------------------------------------------------*/
static VOID _set_vid_clr_offset_r_val(INT32 i4_val)
{
    #ifdef APP_ADJUST_USER_MODE_ONLY
    INT16   i2_clr_temp_mode = 0;
    #endif

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R);

    #ifndef APP_ADJUST_USER_MODE_ONLY
    a_cfg_av_set(ui2_id, i4_val);
    a_cfg_av_update(ui2_mode_id);
    #else
    a_cfg_av_get(ui2_mode_id, &i2_clr_temp_mode);
    //_load_vid_clr_gain_to_user_mode();
    a_cfg_av_set(ui2_id, i4_val);
    a_cfg_av_update(ui2_mode_id);

    #endif
    set_preset_pic_mode_chg_status(TRUE);
}

static INT32 _get_vid_clr_offset_r_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R);
    INT16   i2_vid_clr_gain_r;

    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_r);

    return (INT32)i2_vid_clr_gain_r;
}

/*----------------------------------------------------------------------------
 * Color offset G
 ----------------------------------------------------------------------------*/
static VOID _set_vid_clr_offset_g_val(INT32 i4_val)
{
    #ifdef APP_ADJUST_USER_MODE_ONLY
    INT16   i2_clr_temp_mode = 0;
    #endif

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G);

    #ifndef APP_ADJUST_USER_MODE_ONLY
    a_cfg_av_set(ui2_id, i4_val);
    a_cfg_av_update(ui2_mode_id);
    #else
    a_cfg_av_get(ui2_mode_id, &i2_clr_temp_mode);
    //_load_vid_clr_gain_to_user_mode();
    a_cfg_av_set(ui2_id, i4_val);
    a_cfg_av_update(ui2_mode_id);
    #endif
    set_preset_pic_mode_chg_status(TRUE);
}

static INT32 _get_vid_clr_offset_g_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G);
    INT16   i2_vid_clr_gain_g;

    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_g);

    return (INT32)i2_vid_clr_gain_g;
}

/*----------------------------------------------------------------------------
 * Color offset B
 ----------------------------------------------------------------------------*/
static VOID _set_vid_clr_offset_b_val(INT32 i4_val)
{
    #ifdef APP_ADJUST_USER_MODE_ONLY
    INT16   i2_clr_temp_mode = 0;
    #endif

    UINT16 ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B);

    #ifndef APP_ADJUST_USER_MODE_ONLY
    a_cfg_av_set(ui2_id, i4_val);
    a_cfg_av_update(ui2_mode_id);
    #else
    a_cfg_av_get(ui2_mode_id, &i2_clr_temp_mode);
    //_load_vid_clr_gain_to_user_mode();
    a_cfg_av_set(ui2_id, i4_val);
    a_cfg_av_update(ui2_mode_id);
    #endif
    set_preset_pic_mode_chg_status(TRUE);
}

static INT32 _get_vid_clr_offset_b_val(VOID)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B);
    INT16   i2_vid_clr_gain_b;

    a_cfg_av_get(ui2_id, &i2_vid_clr_gain_b);

    return (INT32)i2_vid_clr_gain_b;
}


static INT32 _incr_vid_clr_gain_b(VOID)
{
    INT16   i2_vid_clr_gain_b;
    INT16   i2_clr_gain_b   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_b);
    if (i2_clr_gain_b >= i2_max)
    {
        i2_vid_clr_gain_b = i2_max;
    }
    else if (i2_clr_gain_b <= i2_min)
    {
        i2_vid_clr_gain_b = i2_min + 1;
    }
    else
    {
        i2_vid_clr_gain_b = i2_clr_gain_b + 1;
    }

    if (i2_clr_gain_b != i2_vid_clr_gain_b)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_b);
        a_cfg_av_update(ui2_mode_id);
    }

    set_preset_pic_mode_chg_status(TRUE);
    return i2_vid_clr_gain_b;
}

static INT32 _decr_vid_clr_gain_b(VOID)
{
    INT16   i2_vid_clr_gain_b;
    INT16   i2_clr_gain_b   = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B);
    UINT16  ui2_mode_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP);
    INT16   i2_min, i2_max;

    a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
    a_cfg_av_get(ui2_id, &i2_clr_gain_b);
    if (i2_clr_gain_b >= i2_max)
    {
        i2_vid_clr_gain_b = i2_max -1;
    }
    else if (i2_clr_gain_b <= i2_min)
    {
        i2_vid_clr_gain_b = i2_min;
    }
    else
    {
        i2_vid_clr_gain_b = i2_clr_gain_b - 1;
    }

    if (i2_clr_gain_b != i2_vid_clr_gain_b)
    {
        a_cfg_av_set(ui2_id, i2_vid_clr_gain_b);
        a_cfg_av_update(ui2_mode_id);
    }

    set_preset_pic_mode_chg_status(TRUE);
    return i2_vid_clr_gain_b;
}

static VOID _set_vid_blur_idx(UINT16 ui2_idx)
{
    UINT8   ui1_val = (UINT8)ui2_idx;
    UINT16  ui2_pre_idx = _get_vid_blur_idx();

    a_cfg_custom_set_reduce_blur(ui1_val);
    a_cfg_custom_update_reduce_blur(ui1_val);
    if (ui2_pre_idx != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

static UINT16 _get_vid_blur_idx(VOID)
{
    UINT8 ui1_idx;

    if(menu_is_vrr_enable_and_vrr_stream_detect() || a_acfg_cust_is_detect_hdmi_freesync_flag())
    {
        return (UINT16)0;
    }

    //Fix Coverity ID : 4899998 Unchecked return value
    if (a_cfg_custom_get_reduce_blur(&ui1_idx) != APP_CFGR_OK)
    {
        DBG_ERROR(("<MENU> Get vid biur idx fail\r\n"));
    }

    return (UINT16)ui1_idx;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_dnr_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_dnr_idx(UINT16 ui2_idx)
{
    UINT16  ui2_nr_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR);
    UINT16  ui2_3d_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR);
    UINT16  ui2_pre_idx = _get_vid_dnr_idx();

    a_cfg_av_set(ui2_nr_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_nr_id);

    a_cfg_av_set(ui2_3d_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_3d_id);
    if (ui2_pre_idx != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_dnr_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_dnr_idx(VOID)
{
    INT16 i2_val;


    if( menu_is_vrr_enable_and_vrr_stream_detect() )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_NR,
            DBG_LOG_PRINT(("[MENU][NR][GAME][VRR]{%s,%d} VRR => Force UI NR off\n", __FUNCTION__,__LINE__));
        );

        return (UINT16)0;
    }

    if( a_acfg_cust_is_detect_hdmi_freesync_flag() )
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_NR,
            DBG_LOG_PRINT(("[MENU][NR][GAME][FreeSync]{%s,%d} FreeSync => Force UI NR off\n", __FUNCTION__,__LINE__));
        );

        return (UINT16)0;
    }

    if(a_acfg_cust_is_gll_enable() == TRUE)
    {
        ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_NR,
            DBG_LOG_PRINT(("[MENU][NR][GAME][GLL]{%s,%d} GLL => Force UI NR off\n", __FUNCTION__,__LINE__));
        );

        return (UINT16)0;
    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR), &i2_val);

    return (UINT16)i2_val;
}


/*----------------------------------------------------------------------------
 * Name: _set_vid_flesh_tone_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_flesh_tone_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FLESH_TONE);
    a_cfg_av_set(ui2_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_id);
    set_preset_pic_mode_chg_status(TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_flesh_tone_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_flesh_tone_idx(VOID)
{
    INT16 i2_val;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FLESH_TONE), &i2_val);

    return (UINT16)i2_val;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_alc_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_alc_idx(UINT16 ui2_idx)
{
    printf("[JDJD] %s:%d, ui2_idx = %d, APP_CFGAPP_CFG_RECID_VID_LUMA = %d\n",__FUNCTION__,__LINE__, ui2_idx, APP_CFG_RECID_VID_LUMA);
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA);
    UINT16  ui2_black_strech_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLACK_STRETCH);
    UINT16  ui2_white_strech_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_WHITE_STRETCH);
    UINT16  ui2_pre_idx = _get_vid_alc_idx();
    printf("[JDJD] %s:%d,ui2_pre_idx = %d\n",__FUNCTION__,__LINE__,ui2_pre_idx);
    a_cfg_av_set(ui2_id, (INT16)ui2_idx);
    a_cfg_av_set(ui2_black_strech_id, (INT16)ui2_idx);
    a_cfg_av_set(ui2_white_strech_id, (INT16)ui2_idx);

    a_cfg_av_update(ui2_id);
    a_cfg_av_update(ui2_black_strech_id);
    a_cfg_av_update(ui2_white_strech_id);
    if (ui2_pre_idx != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_alc_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_alc_idx(VOID)
{
    INT16 i2_val;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA), &i2_val);

    return (UINT16)i2_val;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_scr_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_scr_mode_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE);
    INT16   i2_val;

    i2_val = (INT16)ui2_idx;

    a_cfg_av_set(ui2_id, i2_val);
    a_cfg_av_update(ui2_id);

    /* No overscan when dot by dot */
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_scr_mode_text
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _get_vid_scr_mode_text(
    UINT16    ui2_idx,   /* in */
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len)     /* in, len of w2s_str */
{
    INT32                       i4_ret;
    CHAR                        s_snk_name[SYS_NAME_LEN + 1];
    VSH_SRC_RESOLUTION_INFO_T   t_src_res;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio;
    UTF16_T*                    w2s_text;

    c_memset(& t_src_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
    do
    {
        /* Get current sink(display) name */
        i4_ret = a_cfg_av_get_disp_name(s_snk_name, sizeof(s_snk_name));
        MENU_BREAK_ON_FAIL(i4_ret);

        /* Get current source resolution */
        i4_ret =a_cfg_av_get_timing(s_snk_name, &t_src_res);
        MENU_BREAK_ON_FAIL(i4_ret);

        /* Get the aspect ration */
        e_src_asp_ratio = a_sml_get_src_asp_ratio(&t_src_res);
        if(e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_UNKNOWN)
        {
            e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;
        }

        /* Get text */
        w2s_text = a_sml_get_disp_name(e_src_asp_ratio, (SCC_VID_SCREEN_MODE_T)ui2_idx);
        if(w2s_text != NULL)
        {
            c_uc_w2s_strncpy(w2s_str, w2s_text, z_len-2);
            w2s_str[z_len - 1] = 0;
        }
        else
        {
            w2s_str[0] = 0;
        }

        i4_ret = MENUR_OK;
    }while(0);

    if(i4_ret != MENUR_OK)
    {
        w2s_str[0] = 0;
    }
}



#if 1
static VOID _get_vid_pic_mode_text(
    UINT16    ui2_idx,   /* in */
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len)
{
    extern BOOL b_3d_mode_playing;
    UTF16_T             w2s_asterisk[1] = {0};
    BOOL                b_is_chg = 0;


    //DBG_LOG_PRINT(("[MENU][PIC]{%s,%d} ui2_idx:%d, z_len:%d \n", __FILE__, __LINE__, ui2_idx, z_len ));


    ui2_idx = cvt_list_box_idx_2_acfg_idx(ui2_idx);
    if(b_3d_mode_playing)
    {
        if (ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM)
        {
            c_uc_w2s_strncpy(w2s_str, MENU_TEXT((MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1)+ui2_idx /*MLM_MENU_KEY_X_3D_SETTING_3D*/), z_len-2);
            a_cfg_get_preset_pic_mode_chg_status(ui2_idx,&b_is_chg);
            if(b_is_chg)
            {
                c_uc_ps_to_w2s("*",w2s_asterisk,1);
                c_uc_w2s_strncat(w2s_str,w2s_asterisk,1);
            }
            w2s_str[z_len - 1] = 0;
        }

        else
        {
            CHAR    s_pic_mode_name[MENU_CUST_PIC_MODE_NAME_MAX_LEN+2] = {0};
            BOOL    b_is_exist = FALSE;

            a_cfg_cust_get_cust_pic_mode_exist_status(ui2_idx,&b_is_exist);

            if(b_is_exist)
            {
                c_memset(s_pic_mode_name,0,MENU_CUST_PIC_MODE_NAME_MAX_LEN+2);
                c_memset(w2s_str,0,z_len);
                a_cfg_cust_get_cust_pic_mode_name(ui2_idx, s_pic_mode_name,MENU_CUST_PIC_MODE_NAME_MAX_LEN+1);
                c_uc_ps_to_w2s(s_pic_mode_name, w2s_str, MENU_CUST_PIC_MODE_NAME_MAX_LEN+1);
                w2s_str[MENU_CUST_PIC_MODE_NAME_MAX_LEN+1] = 0;
            }

            else
            {
                c_uc_w2s_strncpy(w2s_str, L"", z_len-1);
                w2s_str[MENU_CUST_PIC_MODE_NAME_MAX_LEN+1] = 0;
            }
        }
    }
    else
    {
        if (ui2_idx < ACFG_PRE_SET_PIC_MODE_NUM)
        {
            c_uc_w2s_strncpy(w2s_str, MENU_TEXT((MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1)+ui2_idx /*MLM_MENU_KEY_X_3D_SETTING_3D*/), z_len-1);
            a_cfg_get_preset_pic_mode_chg_status(ui2_idx,&b_is_chg);
            if(b_is_chg)
            {
                c_uc_ps_to_w2s("*",w2s_asterisk,1);
                c_uc_w2s_strncat(w2s_str,w2s_asterisk,1);
            }
            w2s_str[z_len - 1] = 0;
        }
        else
        {
            CHAR    s_pic_mode_name[MENU_CUST_PIC_MODE_NAME_MAX_LEN+2] = {0};
            BOOL    b_is_exist = FALSE;

            a_cfg_cust_get_cust_pic_mode_exist_status(ui2_idx,&b_is_exist);

            if(b_is_exist)
            {
                c_memset(s_pic_mode_name,0,MENU_CUST_PIC_MODE_NAME_MAX_LEN+2);
                c_memset(w2s_str,0,z_len);
                a_cfg_cust_get_cust_pic_mode_name(ui2_idx, s_pic_mode_name,MENU_CUST_PIC_MODE_NAME_MAX_LEN+1);
                c_uc_ps_to_w2s(s_pic_mode_name, w2s_str, MENU_CUST_PIC_MODE_NAME_MAX_LEN+1);
                w2s_str[MENU_CUST_PIC_MODE_NAME_MAX_LEN+1] = 0;
            }
            else
            {
                c_uc_w2s_strncpy(w2s_str, L"", z_len-1);
                w2s_str[MENU_CUST_PIC_MODE_NAME_MAX_LEN+1] = 0;
            }
        }

        //DBG_LOG_PRINT(("[MENU][PIC]{%s,%d} w2s_str: [%s] \n", __FILE__, __LINE__, menu_custom_get_char_string( w2s_str ) ));
    }
}
#endif

INT16 _power_on_idx_to_hdmi_idx(UINT16 power_on_index, UINT16 num_hdmi_ports)
{
    UINT16 hdmi_min_index = 2;
    UINT16 hdmi_max_index = hdmi_min_index + num_hdmi_ports - 1;

    //If this is not an HDMI index, return -1
    if (power_on_index < hdmi_min_index || power_on_index > hdmi_max_index)
    {
        return -1;
    }
    return power_on_index - hdmi_min_index;
}

extern VOID get_power_on_mode_text(
    UINT16 ui2_idx,   /* in */
    UTF16_T *w2s_str, /* out */
    SIZE_T z_len)
{
    ISL_REC_T t_isl_rec = {0};

    a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 0, &t_isl_rec);

    UINT16 hdmi_port_count = (UINT16)t_isl_rec.ui1_iid_count;
    INT16 hdmi_index = _power_on_idx_to_hdmi_idx(ui2_idx, hdmi_port_count);

    //If this is not HDMI use name from static menu file
    if (hdmi_index == -1)
    {
        if (ui2_idx > hdmi_port_count + 1) //If this is after the HDMI block...
        {
            c_uc_w2s_strncpy(w2s_str, MENU_TEXT((MLM_MENU_KEY_MENU_POWER_ON_INPUT_AUTO) + ui2_idx - hdmi_port_count), z_len - 1);
        }
        else
        {
            c_uc_w2s_strncpy(w2s_str, MENU_TEXT((MLM_MENU_KEY_MENU_POWER_ON_INPUT_AUTO) + ui2_idx ), z_len - 1);
        }
    }
    else
    {
        UTF16_T         cec_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
        CHAR cec_name_char[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
        a_isl_get_display_name_ex(&t_isl_rec, cec_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        c_uc_w2s_to_ps(cec_name, cec_name_char, APP_CFG_CUSTOM_INP_NAME_LEN);

        //If this is HDMI use the display name (CEC)
        a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, hdmi_index, &t_isl_rec);
        a_isl_get_display_name_ex(&t_isl_rec, cec_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        c_uc_w2s_strncpy(w2s_str, cec_name, z_len - 1);
    }
}

VOID menu_common_get_vid_pic_mode_text(UINT16    ui2_idx,   /* in */
                                        CHAR*     ps_pic_mode,   /* out */
                                        SIZE_T    z_len)
{
    UTF16_T w2s_str[32] = {0};
    _get_vid_pic_mode_text(ui2_idx, w2s_str, 32);
    c_uc_w2s_to_ps(w2s_str, ps_pic_mode, c_uc_w2s_strlen(w2s_str));
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_clr_tmp_text
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/

static VOID _get_vid_clr_tmp_text(
    UINT16    ui2_idx,   /* in */
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len)
{
    UTF16_T             w2s_asterisk[1] = {0};
    BOOL                b_is_chg = 0;
    INT16               i2_clr_temp = 0;
    INT32               i4_ret = MENUR_OK;

    c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_VID_CLR_TEMP_WARM+ui2_idx), z_len-2);

    switch (ui2_idx)
    {
        case 0:
            i2_clr_temp = ACFG_CUST_CLR_TEMP_WARM;
            break;
        case 1:
            i2_clr_temp = ACFG_CUST_CLR_TEMP_COOL;
            break;
        case 2:
            i2_clr_temp = ACFG_CUST_CLR_TEMP_NORMAL;
            break;
        default:
            i2_clr_temp = ACFG_CUST_CLR_TEMP_WARM;
            break;
    }

    i4_ret = a_cfg_get_clr_temp_chg_status(i2_clr_temp,&b_is_chg);

    MENU_LOG_ON_FAIL(i4_ret);

    if(b_is_chg)
    {
        c_uc_ps_to_w2s("*",w2s_asterisk,1);
        c_uc_w2s_strncat(w2s_str,w2s_asterisk,1);
    }
    w2s_str[z_len - 1] = 0;

}

static VOID _get_dig_and_ana_num(UINT16* pui2_num_recs_digital,UINT16* pui2_num_recs_analog)
{
    INT32   i4_digital_num = 0;
    INT32   i4_analog_num = 0;

    tuner_setup_scan_digital_get_val(&i4_digital_num);
    tuner_setup_scan_analog_get_val(&i4_analog_num);

    *pui2_num_recs_digital = (UINT16)i4_digital_num;
    *pui2_num_recs_analog  = (UINT16)i4_analog_num;
}

 VOID a_get_ch_scan_status_text(
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len /* in, len of w2s_str */)
{

    DBG_INFO (("<MENU> Judge if can acvtive this func.%s,%s,%d\r\n",
               __FILE__, __FUNCTION__, __LINE__));
    UTF16_T w2s_text[256] = {0};
    UTF16_T w2s_num_digital[10] = {0};
    UTF16_T w2s_num_analog[10] = {0};
    CHAR    s_space_dig[8+1] = {0};
    CHAR    s_space_ana[8+1] = {0};
    UINT16  ui2_num_recs_digital = 0;
    UINT16  ui2_num_recs_analog = 0;

    UINT8   ui1_ch_scan_status = ACFG_CUST_CH_NOT_SCANED;

    /* step1 : get crnt ch scan status by acfg api full scan or partical*/
    a_cfg_cust_get_crnt_ch_scan_status(&ui1_ch_scan_status);
    DBG_INFO (("<MENU> get current scan tuner cable or status.%s,%s,%d,ui1_ch_scan_status=%d\r\n",
               __FILE__, __FUNCTION__, __LINE__,ui1_ch_scan_status));

    _get_dig_and_ana_num(&ui2_num_recs_digital,&ui2_num_recs_analog);

    DBG_INFO (("<MENU> Judge if this func is used.\r\n"));

    /* step2: process case by case*/
    switch(ui1_ch_scan_status)
    {
        case ACFG_CUST_CH_NOT_SCANED:
            /* set value(string) to w2s_str & its z_len according to custom spec*/
            if ((ui2_num_recs_digital + ui2_num_recs_analog) == 0)
            {
                c_uc_w2s_strncpy(w2s_text, MENU_TEXT(MLM_MENU_KEY_CH_NOT_SCAN),z_len-1);
                w2s_text[z_len - 1] = 0;
                c_uc_w2s_strcpy(w2s_str,w2s_text);
            }

            /* add analog channel success */
            else
            {
                c_sprintf(s_space_dig, "%d", ui2_num_recs_digital);
                c_sprintf(s_space_ana, "%d", ui2_num_recs_analog);
                c_uc_ps_to_w2s(s_space_dig, w2s_num_digital, z_len); //convert a UTF-8"pui2_num_recs_digital" string to UTF-16 string"pui2_num_recs_digital".
                c_uc_ps_to_w2s(s_space_ana, w2s_num_analog, z_len);

                /* item combination: Scan Completed: X digital and Y analog */
                c_uc_w2s_strcat(w2s_text, MENU_TEXT(MLM_MENU_KEY_PARTIAL_SCAN_STATUS));
                c_uc_w2s_strcpy(w2s_str,w2s_text);
                c_uc_w2s_strcat(w2s_str, w2s_num_digital);
                c_uc_w2s_strcat(w2s_str, MENU_TEXT(MLM_MENU_KEY_DIGITAL_SCAN_STATUS));
                c_uc_w2s_strcat(w2s_str, w2s_num_analog);
                c_uc_w2s_strcat(w2s_str, MENU_TEXT(MLM_MENU_KEY_ANALOG_SCAN_STATUS));
            }

            break;

        case ACFG_CUST_PARTIAL_SCAN:

            if((ui2_num_recs_digital + ui2_num_recs_analog) == 0)
            {
             DBG_INFO (("%s,%s,%d,(ui2_num_recs_digital + ui2_num_recs_analog)=%d,<MENU> show ui2_num_recs.\r\n",
                           __FILE__, __FUNCTION__, __LINE__, (ui2_num_recs_digital + ui2_num_recs_analog)));

                c_uc_w2s_strncpy(w2s_text, MENU_TEXT(MLM_MENU_KEY_NO_CH_FOUND),z_len-1);
                w2s_text[z_len - 1] = 0;

                c_uc_w2s_strcpy(w2s_str,w2s_text);

            }
            else
            {
                c_sprintf(s_space_dig, "%d", ui2_num_recs_digital);
                c_sprintf(s_space_ana, "%d", ui2_num_recs_analog);
                c_uc_ps_to_w2s(s_space_dig, w2s_num_digital, z_len); //convert a UTF-8"pui2_num_recs_digital" string to UTF-16 string"pui2_num_recs_digital".
                c_uc_ps_to_w2s(s_space_ana, w2s_num_analog, z_len);

                /* item combination: Scan Completed: X digital and Y analog */
                c_uc_w2s_strcat(w2s_text, MENU_TEXT(MLM_MENU_KEY_PARTIAL_SCAN_STATUS));
                c_uc_w2s_strcpy(w2s_str,w2s_text);
                c_uc_w2s_strcat(w2s_str, w2s_num_digital);
                c_uc_w2s_strcat(w2s_str, MENU_TEXT(MLM_MENU_KEY_DIGITAL_SCAN_STATUS));
                c_uc_w2s_strcat(w2s_str, w2s_num_analog);
                c_uc_w2s_strcat(w2s_str, MENU_TEXT(MLM_MENU_KEY_ANALOG_SCAN_STATUS));


            }

            break;

         case ACFG_CUST_CH_SCANED_NO_CH:
            if((ui2_num_recs_digital + ui2_num_recs_analog) == 0)
            {
                DBG_INFO(("%s,%s,%d,(ui2_num_recs_digital + ui2_num_recs_analog)=%d\r\n",
                           __FILE__, __FUNCTION__, __LINE__, (ui2_num_recs_digital + ui2_num_recs_analog)));

                c_uc_w2s_strncpy(w2s_text, MENU_TEXT(MLM_MENU_KEY_NO_CH_FOUND),z_len-1);
                w2s_text[z_len - 1] = 0;

                c_uc_w2s_strcpy(w2s_str,w2s_text);
                DBG_INFO(("%s,%s,%d,w2s_str=%s\r\n",
                           __FILE__, __FUNCTION__, __LINE__, w2s_str));
            }
            break;

        case ACFG_CUST_COMPLETED_SCAN:

            if((ui2_num_recs_digital + ui2_num_recs_analog) == 0)
            {
                DBG_INFO (("%s,%s,%d,(ui2_num_recs_digital + ui2_num_recs_analog)=%d\r\n",
                           __FILE__, __FUNCTION__, __LINE__, (ui2_num_recs_digital + ui2_num_recs_analog)));

                c_uc_w2s_strncpy(w2s_text, MENU_TEXT(MLM_MENU_KEY_NO_CH_FOUND),z_len-1);
                w2s_text[z_len - 1] = 0;

                c_uc_w2s_strcpy(w2s_str,w2s_text);
                DBG_INFO (("%s,%s,%d,w2s_str=%s\r\n",
                           __FILE__, __FUNCTION__, __LINE__, w2s_str));
            }
            else
            {
                c_sprintf(s_space_dig, "%d", ui2_num_recs_digital);
                c_sprintf(s_space_ana, "%d", ui2_num_recs_analog);
                c_uc_ps_to_w2s(s_space_dig, w2s_num_digital, z_len); //convert a UTF-8"pui2_num_recs_digital" string to UTF-16 string"pui2_num_recs_digital".
                c_uc_ps_to_w2s(s_space_ana, w2s_num_analog, z_len);

                /* item combination: Scan Completed: X digital and Y analog */
                c_uc_w2s_strcat(w2s_text, MENU_TEXT(MLM_MENU_KEY_COMPLETED_SCAN_STATUS));
                c_uc_w2s_strcpy(w2s_str,w2s_text);
                c_uc_w2s_strcat(w2s_str, w2s_num_digital);
                c_uc_w2s_strcat(w2s_str, MENU_TEXT(MLM_MENU_KEY_DIGITAL_SCAN_STATUS));
                c_uc_w2s_strcat(w2s_str, w2s_num_analog);
                c_uc_w2s_strcat(w2s_str, MENU_TEXT(MLM_MENU_KEY_ANALOG_SCAN_STATUS));

            }
            break;

        default:
            /* just as case ACFG_CUST_CH_NOT_SCANED*/
            break;


    }

}

/*----------------------------------------------------------------------------
 * Name: a_get_power_on_text
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID a_get_power_on_text(
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len /* in, len of w2s_str */)
{
    UTF16_T w2s_text[256] = {0};

    c_uc_w2s_strncpy(w2s_text, MENU_TEXT(MLM_MENU_KEY_CH_NOT_SCAN),255);
    w2s_text[254] = 0;
    c_uc_w2s_strncpy(w2s_str, w2s_text, z_len-1);
}


/*----------------------------------------------------------------------------
 * Name: _get_vid_scr_mode_idx_by_dir
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_scr_mode_idx_by_dir(
    SML_ITERATE_T               e_iter)
{
    INT32                       i4_ret;
    UINT16                      ui2_cfg_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE);
    CHAR                        s_disp_name[SYS_NAME_LEN + 1];
    VSH_SRC_RESOLUTION_INFO_T   t_src_res;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio;
    INT16                       i2_val;
    SCC_VID_SCREEN_MODE_T       e_scr_mode;
    SCC_VID_SCREEN_MODE_T       e_scr_mode_orig;
    UINT16                      ui2_idx = 0;
    TV_WIN_ID_T                 e_focus_id;

    c_memset(& t_src_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
    do
    {
        /* Get current sink(display) name */
        i4_ret = a_tv_get_focus_win(&e_focus_id);
        MENU_BREAK_ON_FAIL(i4_ret);

        i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        MENU_BREAK_ON_FAIL(i4_ret);

        if((e_focus_id == TV_WIN_ID_MAIN && c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) != 0) ||
           (e_focus_id == TV_WIN_ID_SUB  && c_strcmp(s_disp_name, SN_PRES_SUB_DISPLAY) != 0))
        {
            break;
        }

        /* Get current source resolution */
        i4_ret =a_cfg_av_get_timing(s_disp_name, &t_src_res);
        MENU_BREAK_ON_FAIL(i4_ret);

        /* Get the aspect ration */
        e_src_asp_ratio = a_sml_get_src_asp_ratio(&t_src_res);
        if(e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_UNKNOWN)
        {
            e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;
        }

        /* Get current screen mode. */
        i4_ret = a_cfg_av_get(ui2_cfg_id, &i2_val);
        MENU_BREAK_ON_FAIL(i4_ret);

        e_scr_mode_orig = e_scr_mode = (SCC_VID_SCREEN_MODE_T) i2_val;

        /* Check if current screen mode is valid.
           If not, find the first screen mode */
        i4_ret = a_sml_iterate_rec (e_src_asp_ratio,
                                    SML_ITERATE_DIR_THIS,
                                    & e_scr_mode);
        if (i4_ret != SMLR_OK) /* Invalid screen mode */
        {
            /* Get first screen mode. */
            i4_ret = a_sml_iterate_rec (e_src_asp_ratio,
                                        SML_ITERATE_DIR_FIRST,
                                        & e_scr_mode);
            MENU_BREAK_ON_FAIL(i4_ret);
        }

        /* Get the screen mode by direction */
        i4_ret = a_sml_iterate_rec(e_src_asp_ratio,
                                   e_iter,
                                   &e_scr_mode);
        MENU_BREAK_ON_FAIL(i4_ret);

        /* If the orignal screen mode is not equal to new one,
           set back to config */
        if(e_scr_mode_orig != e_scr_mode)
        {
            /* Set screen mode to config. */
            i4_ret = a_cfg_av_set (ui2_cfg_id, (INT16) e_scr_mode);
            MENU_BREAK_ON_FAIL(i4_ret);

            /* Update config. */
            i4_ret = a_cfg_av_update (ui2_cfg_id);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
            MENU_LOG_ON_FAIL(i4_ret);
        }

        /* convert screen mode to index */
        ui2_idx = e_scr_mode;

        i4_ret = MENUR_OK;
    }while(0);

    if(i4_ret != MENUR_OK)
    {
        ui2_idx = 0;
    }

    return ui2_idx;
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_scr_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_scr_mode_idx(VOID)
{
    return _get_vid_scr_mode_idx_by_dir(SML_ITERATE_DIR_THIS);
}

/*----------------------------------------------------------------------------
 * Name: _prev_vid_scr_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _prev_vid_scr_mode_idx(VOID)
{
    return _get_vid_scr_mode_idx_by_dir(SML_ITERATE_DIR_PREV);
}

/*----------------------------------------------------------------------------
 * Name: _prev_vid_scr_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _next_vid_scr_mode_idx(VOID)
{
    return _get_vid_scr_mode_idx_by_dir(SML_ITERATE_DIR_NEXT);
}


#ifdef APP_HV_POS_MODIFICATION_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_vid_pos_h_val
 *
 * Description: Set video H pos.
 *
 * Inputs:  i4_val
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_pos_h_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H);
    INT16 i2_vid_pos_h;

    i2_vid_pos_h = (INT16)i4_val;
    a_cfg_av_set(ui2_id, i2_vid_pos_h);
    a_cfg_av_update(ui2_id);
}
/*----------------------------------------------------------------------------
 * Name: _set_vid_pos_h_val
 *
 * Description: Get video H pos.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: H pos.
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vid_pos_h_val(VOID)
{
    INT16 i2_vid_pos_h;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H), &i2_vid_pos_h);

    return i2_vid_pos_h;
}
/*----------------------------------------------------------------------------
 * Name: _set_vid_pos_v_val
 *
 * Description: Set video V pos.
 *
 * Inputs:  i4_val
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_pos_v_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V);
    INT16 i2_vid_pos_v;

    i2_vid_pos_v = (INT16)i4_val;
    a_cfg_av_set(ui2_id, i2_vid_pos_v);
    a_cfg_av_update(ui2_id);
}
/*----------------------------------------------------------------------------
 * Name: _get_vid_pos_v_val
 *
 * Description: Get video V pos.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: V pos.
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vid_pos_v_val(VOID)
{
    INT16 i2_vid_pos_v;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V), &i2_vid_pos_v);

    return i2_vid_pos_v;
}
#endif
/*----------------------------------------------------------------------------
 * Name: _set_vid_ypbpr_phase
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_ypbpr_phase_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_YPBPR_PHASE);
    INT16 i2_vid_ypbpr_phase;

    i2_vid_ypbpr_phase = (INT16)i4_val;
    a_cfg_av_set(ui2_id, i2_vid_ypbpr_phase);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_ypbpr_phase_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vid_ypbpr_phase_val(VOID)
{
    INT16 i2_vid_ypbpr_phase;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_YPBPR_PHASE), &i2_vid_ypbpr_phase);

    return i2_vid_ypbpr_phase;
}


#ifdef APP_MJC_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_vid_mjc_effect_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _set_vid_mjc_effect_idx(UINT16 ui2_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT);
    INT16 i2_vid_mjc_effect;
    UINT16 ui2_pre_idx = _get_vid_mjc_effect_idx();

    i2_vid_mjc_effect = (INT16)ui2_val;
    a_cfg_av_set(ui2_id, i2_vid_mjc_effect);
    a_cfg_av_update(ui2_id);

    if (ui2_pre_idx != ui2_val)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_mjc_effect_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_mjc_effect_idx(VOID)
{
    INT16 i2_vid_mjc_effect;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT), &i2_vid_mjc_effect);

    return (UINT16)i2_vid_mjc_effect;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_mjc_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _set_vid_mjc_mode_idx(UINT16 ui2_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_MODE);
    INT16 i2_vid_mjc_mode;

    i2_vid_mjc_mode = (INT16)ui2_val;
    a_cfg_av_set(ui2_id, i2_vid_mjc_mode);
    a_cfg_av_update(ui2_id);
    set_preset_pic_mode_chg_status(TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_mjc_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_mjc_mode_idx(VOID)
{
    INT16 i2_vid_mjc_mode;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_MODE), &i2_vid_mjc_mode);

    return (UINT16)i2_vid_mjc_mode;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_mjc_demo_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _set_vid_mjc_demo_part_idx(UINT16 ui2_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_DEMO);
    INT16 i2_vid_mjc_part;

    i2_vid_mjc_part = (INT16)ui2_val;
    a_cfg_av_set(ui2_id, i2_vid_mjc_part);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_mjc_demo_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_mjc_demo_part_idx(VOID)
{
    INT16 i2_vid_mjc_demo;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_DEMO), &i2_vid_mjc_demo);

    return (UINT16)i2_vid_mjc_demo;
}
#endif /* APP_MJC_SUPPORT */

/*----------------------------------------------------------------------------
 * Name: _set_inp_film_maker_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _set_inp_film_maker_mode_idx(UINT16 ui2_val)
{
    DBG_LOG_PRINT(("-----------------baozi %s %d ui2_val = %d\n",__FUNCTION__,__LINE__, ui2_val));
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FILM_MAEKER_MODE), ui2_val);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FILM_MAEKER_MODE));
}

VOID menu_set_inp_film_maker_mode_idx(UINT16 ui2_val)
{
    _set_inp_film_maker_mode_idx(ui2_val);
}


/*----------------------------------------------------------------------------
 * Name: _get_inp_film_maker_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT16 _get_inp_film_maker_mode_idx(VOID)
{
    INT16 i2_val = 0;
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FILM_MAEKER_MODE), &i2_val);
    DBG_LOG_PRINT(("-----------------baozi %s %d i2_val = %d\n",__FUNCTION__,__LINE__, i2_val));
    return (UINT16)i2_val;
}

UINT16 menu_get_inp_film_maker_mode_idx(VOID)
{
    return _get_inp_film_maker_mode_idx();
}

VOID menu_set_inp_ffm_detected(BOOL b_detected)
{
    b_ffm_detected = b_detected;
}

BOOL menu_get_inp_ffm_detected(VOID)
{
    return b_ffm_detected;
}

BOOL menu_get_inp_ffm_apply(VOID)
{
    return menu_get_inp_ffm_detected() && _get_inp_film_maker_mode_idx() == 0;
}


/*----------------------------------------------------------------------------
 * Name: _set_energy_saving_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _set_energy_saving_mode_idx(UINT16 ui2_idx)
{
    _set_vid_pic_mode_idx(ui2_idx + 2);
}

/*----------------------------------------------------------------------------
 * Name: _get_energy_saving_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT16 _get_energy_saving_mode_idx(VOID)
{
    return _get_vid_pic_mode_idx() == 3 ? 1 : 0;
}

/*----------------------------------------------------------------------------
 * Name: _set_inp_full_color_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _set_inp_full_color_444_idx(UINT16 ui2_val)
{
#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)

    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d} ui2_val: %d\n", __FUNCTION__, __LINE__, ui2_val)); );

    // Check if can turn on ...
    BOOL bIs_FullColor444_CanTurnOn = acfg_cust_FullColor444_IfCanTurnOn();
    if( !bIs_FullColor444_CanTurnOn ) // Cannot turn on
    {
        DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d} Can not turn on, Skip!\n", __FUNCTION__, __LINE__));
        return;
    }

    // Get current FullColor setting
    UINT8 ui1_full_color_444_value = 0;
    UINT32 i32Ret = a_cfg_cust_get_full_color_444_ForCurHDMI(&ui1_full_color_444_value);
    if( i32Ret != 0 )
    {
        DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d} Error: a_cfg_cust_get_full_color_444_ForCurHDMI() failed => %d\n", __FUNCTION__, __LINE__, i32Ret));
        return;
    }
    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d} ui1_full_444_color_value:%d\n", __FUNCTION__, __LINE__, ui1_full_color_444_value)); );

    DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d} Change: %d => %d\n", __FUNCTION__, __LINE__, ui1_full_color_444_value, ui2_val));

    i32Ret = a_cfg_cust_set_full_color_444_ForCurHDMI(ui2_val);
    if( i32Ret != 0 )
    {
        DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d} Error: a_cfg_cust_set_full_color_444() failed => %d\n", __FUNCTION__, __LINE__, i32Ret));
        return;
    }

    a_cfg_av_update( CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_FULL_COLOR_444) );

#else

    ISL_REC_T   t_isl_rec;
    UINT16 ui2_hdmi_idx;
    UINT8 ui1_chroma_value = 0;
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_FULL_COLOR_444);
    MENU_LOG_ON_FAIL(a_cfg_cust_get_full_color_444(&ui1_chroma_value));

    menu_get_crnt_isl(&t_isl_rec);
    ui2_hdmi_idx = t_isl_rec.ui1_internal_id;
    // MENU_CHK_FAIL(a_cfg_cust_get_full_color_444(&ui1_chroma_value));
    DBG_LOG_PRINT(("<FULL CHROMA> file: %s line: %d  %s a_cfg_cust_get_full_color_444(%d) ui1_hdmi_index: %d\n", __FILE__, __LINE__, __FUNCTION__, ui1_chroma_value, ui2_hdmi_idx));

    if(ui2_val == 1)
    {
        ui1_chroma_value |= (UINT8)1 << ui2_hdmi_idx;
    }
    else
    {
        ui1_chroma_value &= ~((UINT8)1 << ui2_hdmi_idx);
    }

    DBG_LOG_PRINT(("<FULL CHROMA> file: %s line: %d  %s a_cfg_cust_set_full_color_444(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_chroma_value));

    MENU_LOG_ON_FAIL(a_cfg_cust_set_full_color_444(ui1_chroma_value));
    a_cfg_av_update(ui2_id);

#endif
}

VOID menu_set_inp_full_color_444_idx(UINT16 ui2_val)
{
    _set_inp_full_color_444_idx(ui2_val);
}

/*----------------------------------------------------------------------------
 * Name: _get_inp_full_color_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT16 _get_inp_full_444_color_idx(VOID)
{
#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
    BOOL bIs_FullColor444_CanTurnOn = acfg_cust_FullColor444_IfCanTurnOn();
    if( !bIs_FullColor444_CanTurnOn ) // Cannot turn on
    {
        ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d} Can not turn on!\n", __FUNCTION__, __LINE__ )); );
        return 0;
    }


    UINT8 ui1_full_color_444_value = 0;

    UINT32 i32Ret = a_cfg_cust_get_full_color_444_ForCurHDMI(&ui1_full_color_444_value);
    if( i32Ret != 0 )
    {
        DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d} Error: a_cfg_cust_get_full_color_444_ForCurHDMI() failed => %d\n", __FUNCTION__, __LINE__, i32Ret));
        return 0;
    }

    ACFG_DEBUG_FULL_COLOR444( DBG_LOG_PRINT(("[MENU][FullColor444]{%s:%d} ==> ui1_full_444_color_value:%d\n", __FUNCTION__, __LINE__, ui1_full_color_444_value )); );

    return ui1_full_color_444_value;

#else
    ISL_REC_T   t_isl_rec;
    UINT8       ui1_chroma_value;
    UINT8       ui1_mask = 1;
    INT32       i4_color;

    MENU_CHK_FAIL(menu_get_crnt_isl(&t_isl_rec));

    if( menu_is_signal_loss() == TRUE || menu_is_video_block() == TRUE )
    {
        return 0;
    }

    if (!menu_full_color_444_is_enable())
    {
        MENU_LOG_ON_FAIL(menu_ope_lst_get_hdmi_color_space(&i4_color));

        if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI
            && menu_ope_lst_hdmi_color_space_is_RGB(i4_color)
            && a_icl_custom_get_dolby_vision_status() != 1)
        {
            return 1;
        }
        return 0;
    }

    MENU_CHK_FAIL(a_cfg_cust_get_full_color_444(&ui1_chroma_value));

    return (UINT8) (ui1_chroma_value >> (t_isl_rec.ui1_internal_id)) & ui1_mask;

#endif
}

UINT16 menu_get_inp_full_444_color_idx(VOID)
{
    return _get_inp_full_444_color_idx();
}

/*----------------------------------------------------------------------------
 * Name: menu_inp_is_full_color_444_on
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
BOOL menu_inp_is_full_color_444_on(VOID)
{
    return _get_inp_full_444_color_idx() == 1;
}

/*----------------------------------------------------------------------------
 * Name: _set_inp_hdmi_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _set_inp_hdmi_mode_idx(UINT16 ui2_val)
{
    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} ui2_val:%d\n",
            __FUNCTION__, __LINE__, ui2_val ));
    );

    UINT8 u8_UI_Hdmi_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();
    //DBG_LOG_PRINT(("[MENU][HDMI]{%s:%d} Cur HDMI u8PortIdx => %d\n", __FUNCTION__, __LINE__, u8CurSrcHdmiPortIdx ));

    UINT8 u8_acfg_hdmi_idx = acfg_cust_HDMI_convert_UI_idx_to_ACFG_idx(u8_UI_Hdmi_Idx);
    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][HDMI]{%s:%d} UI hdmi idx:%d => ACFG hdmi_idx:%d\n",
            __FUNCTION__, __LINE__, u8_UI_Hdmi_Idx, u8_acfg_hdmi_idx ));
    );

#if( ENABLE_HDMI_EDID_NEW_METHOD )
    INT32 i4_hdmi_idx = u8_acfg_hdmi_idx;
#else
    INT32 i4_hdmi_idx = a_nav_ipts_get_hdmi_comp_idx();
#endif
    if( (i4_hdmi_idx < 0) || (i4_hdmi_idx > 3) )
    {
        DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} Error: Invalid i4_hdmi_idx:%d => skip!\n",
            __FUNCTION__, __LINE__, i4_hdmi_idx ));
        return;
    }

#if( ENABLE_HDMI_EDID_NEW_METHOD )
    // Convert UI edid to ACFG edid index ...
    EnuAcfgEdidIdx e_acfg_edid_idx = acfg_cust_EDID_convert_UI_idx_to_acfg_idx(ui2_val);

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} ACFG_hdmi_idx:%d, UI_EDID_Idx:%d => e_acfg_edid_idx:%d(%s)\n",
            __FUNCTION__, __LINE__,
            i4_hdmi_idx, ui2_val, e_acfg_edid_idx, acfg_cust_get_acfg_edid_name(e_acfg_edid_idx) ));
    );

    inp_lst_set_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, e_acfg_edid_idx);

#else

  #ifdef MT5583_MODEL
    inp_lst_set_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, (UINT8)(ui2_val == 0 ? 2 : 0));
  #else
    inp_lst_set_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, (UINT8)(2 - ui2_val));
  #endif
#endif
}

/*----------------------------------------------------------------------------
 * Name: _get_inp_hdmi_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT16 _get_inp_hdmi_mode_idx(VOID)
{
    UINT8 u8_UI_Hdmi_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();
    //DBG_LOG_PRINT(("[MENU][HDMI]{%s:%d} Cur HDMI u8PortIdx => %d\n", __FUNCTION__, __LINE__, u8CurSrcHdmiPortIdx ));

    UINT8 u8_acfg_hdmi_idx = acfg_cust_HDMI_convert_UI_idx_to_ACFG_idx(u8_UI_Hdmi_Idx);
    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][HDMI][EDID]{%s:%d} UI hdmi idx:%d => ACFG hdmi_idx:%d\n",
            __FUNCTION__, __LINE__, u8_UI_Hdmi_Idx, u8_acfg_hdmi_idx ));
    );

#if( ENABLE_HDMI_EDID_NEW_METHOD )
    INT32 i4_hdmi_idx = u8_acfg_hdmi_idx;
#else
    INT32 i4_hdmi_idx = a_nav_ipts_get_hdmi_comp_idx();
#endif

    if( (i4_hdmi_idx < 0) || (i4_hdmi_idx > 3) )
    {
        DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} Error: Invalid i4_hdmi_idx:%d => Force to Auto !\n",
            __FUNCTION__, __LINE__, i4_hdmi_idx ));

        return UI_EDID_SEL_AUTO;
    }

    UINT8 ui1_acfg_edid_idx = 0;

    //inp_lst_get_full_uhd_color_by_hdmi_idx( i4_hdmi_idx, &ui1_acfg_edid_idx);
    INT32 i32_rtn = a_cfg_cust_get_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, &ui1_acfg_edid_idx);
    if( i32_rtn != 0 )
    {
        DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} i4_hdmi_idx:%d: a_cfg_cust_get_full_uhd_color_by_hdmi_idx() failed!! i32_rtn:%d\n",
            __FUNCTION__, __LINE__, i4_hdmi_idx, i32_rtn ));

        return UI_EDID_SEL_AUTO;
    }


#if( ENABLE_HDMI_EDID_NEW_METHOD )
    // Convert ACFG val to UI val
    UINT8 u8_UI_edid_idx = acfg_cust_EDID_convert_ACFG_idx_to_UI_idx(ui1_acfg_edid_idx);

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} UI_HDMI_idx:%d, ACFG_hdmi_idx:%d, ui1_acfg_edid_idx:%d(%s) => u8_UI_edid_idx:%d \n",
            __FUNCTION__, __LINE__, u8_UI_Hdmi_Idx, i4_hdmi_idx,
            ui1_acfg_edid_idx, acfg_cust_get_acfg_edid_name((EnuAcfgEdidIdx)ui1_acfg_edid_idx),
            u8_UI_edid_idx ));
    );

    return u8_UI_edid_idx;

#else

  inp_lst_get_full_uhd_color_by_hdmi_idx( i4_hdmi_idx, &ui1_acfg_edid_idx);

  #ifdef MT5583_MODEL
    return ui1_acfg_edid_idx == 2 ? 0 : 1;
  #else
    return (UINT16)(2 - ui1_acfg_edid_idx);
  #endif

#endif
}

#ifdef APP_MENU_HDMI_MODE_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_vid_hdmi_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _set_vid_hdmi_mode_idx(UINT16 ui2_val)
{
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_COLOR_SPACE),ui2_val > SCC_VID_COLORSPACE_FORCE_YCBCR ? SCC_VID_COLORSPACE_AUTO : ui2_val );
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_COLOR_SPACE));
}

VOID menu_set_vid_hdmi_mode_idx(UINT16 ui2_val)
{
    _set_vid_hdmi_mode_idx(ui2_val);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_hdmi_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_hdmi_mode_idx(VOID)
{
    UINT8   ui1_color_space = SCC_VID_COLORSPACE_AUTO;

    a_cfg_cust_get_color_space_value(&ui1_color_space);

    return (UINT16)ui1_color_space;
}
#endif /*APP_MENU_HDMI_MODE_SUPPORT*/

UINT16 menu_get_vid_hdmi_mode_idx(VOID)
{
    return _get_vid_hdmi_mode_idx();
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_vga_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _set_vid_vga_mode_idx(UINT16 ui2_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VGA_MODE);
    INT16 i2_vid_vga_mode;

    switch(ui2_val)
    {
    case 0: /*Video*/
        i2_vid_vga_mode = (INT16)SCC_VID_COLORSPACE_FORCE_YCBCR;
        break;
    case 1:/*Graphic*/
        i2_vid_vga_mode = (INT16)SCC_VID_COLORSPACE_FORCE_RGB;
        break;
    default:
        i2_vid_vga_mode = (INT16)SCC_VID_COLORSPACE_FORCE_YCBCR;
        break;
    }

    a_cfg_av_set(ui2_id, i2_vid_vga_mode);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_vga_mode_idx
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_vga_mode_idx(VOID)
{
    INT16 i2_vid_vga_mode;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VGA_MODE), &i2_vid_vga_mode);

    switch((SCC_VID_COLORSPACE_T)i2_vid_vga_mode)
    {
    case SCC_VID_COLORSPACE_FORCE_YCBCR:
        return 0;
    case SCC_VID_COLORSPACE_FORCE_RGB:
        return 1;
    default:
        return 0;
    }
}

#ifdef APP_DI_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_vid_di_film_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_di_film_mode_idx(UINT16 ui2_idx)
{
    // Check if can turn on...
    if( FALSE == a_cfg_cust_FilmMode_CheckIfCanTurnOn() )
    {
        // If can not turn on, do nothing!
        return ;
    }

    INT16 i16FilmMode_Val = 0;

    // Convert menu idx to acfg value...
    if(0 == ui2_idx) // FilmMode is auto
    {
        i16FilmMode_Val = 1; // FilmMode is On
    }
    else //if(1 == ui2_idx) // FilmMode is off
    {
        i16FilmMode_Val = 0; // FilmMode is Off
    }


    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE);

    INT16 i16FilmMode_Val_Pre = 0;
    a_cfg_av_get(ui2_id, &i16FilmMode_Val_Pre);

    ACFG_DEBUG_PICTURE_LOG( ACFG_DBG_PICT_FILM_MODE,
        DBG_LOG_PRINT(("[MENU][FilmMode]{%s:%d} Set FilmMode: %d -> %d\n", __FUNCTION__, __LINE__, i16FilmMode_Val_Pre, i16FilmMode_Val ));
    );

    a_cfg_av_set(ui2_id, (INT16)i16FilmMode_Val);
    a_cfg_av_update(ui2_id);

    if( i16FilmMode_Val != i16FilmMode_Val_Pre )
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_di_film_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_di_film_mode_idx(VOID)
{
    INT16 i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE), &i2_val);

    //60 Hz television, if Game Low Latency is turned on, and Film Mode is On then is Film Mode turned off temporarily.
    //if(a_acfg_cust_is_gll_enable())
    if( FALSE == a_cfg_cust_FilmMode_CheckIfCanTurnOn() )
    {
        i2_val = 0;
    }


    // Convert acfg value to menu idx ...
    UINT16 u16FilmModeIdx = 0;
    if( 0 == i2_val ) // ACFG.OFF
    {
        //i2_val = 1;
        u16FilmModeIdx = 1; // OFF
    }
    else //if(1 == i2_val)
    {
        //i2_val = 0;
        u16FilmModeIdx = 0; // ON
    }

    return u16FilmModeIdx;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_di_ma_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_di_ma_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_MA);
    a_cfg_av_set(ui2_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_di_ma_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_di_ma_idx(VOID)
{
    INT16 i2_val;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_MA), &i2_val);

    return (UINT16)i2_val;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_di_edge_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_di_edge_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_EDGE);
    a_cfg_av_set(ui2_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_di_edge_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_di_edge_idx(VOID)
{
    INT16 i2_val;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_EDGE), &i2_val);

    return (UINT16)i2_val;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _get_vid_game_low_latency_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_game_low_latency_idx(VOID)
{
    if( a_cfg_cust_is_support_game_low_latency() == FALSE)
    {
        DBG_LOG_PRINT(("[MENU][GAME][GLL]{%s, %d} Not support GLL => Force GLL off \n", __FUNCTION__,__LINE__));
        return  ACFG_CUST_GAME_LOW_LATENCY_OFF;
    }

    // Check if need to force value ...
    UINT8 u8_force_GLL_setting = 0;
    if( a_cfg_cust_GLL_get_force_value(&u8_force_GLL_setting) )// if( VZO_DV__SKIP_GLL_WHEN_DV_GAME )
    {
         DBG_LOG_PRINT(("[MENU][GAME][GLL]{%s, %d} System force value => ui1_idx:%d(%s)\n",
            __FUNCTION__,__LINE__, u8_force_GLL_setting, a_cfg_cust_get_GLL_para_str(u8_force_GLL_setting) ));

         return u8_force_GLL_setting;
    }


    INT16   i2_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i2_val);
    MENU_LOG_ON_FAIL(i4_ret);

#if 0
    else
    {
        if(a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE && i2_val != ACFG_CUST_GAME_LOW_LATENCY_ON)
        {
        	i2_val = ACFG_CUST_GAME_LOW_LATENCY_ON;
        }
    }
#endif


    return (UINT16)i2_val;
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_game_low_latency_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_game_low_latency_idx(UINT16 ui2_idx)
{
    INT16   i2_pre_gll = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i2_pre_gll);
    MENU_LOG_ON_FAIL(i4_ret);


    if (i2_pre_gll != ui2_idx)
    {
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), (INT16)ui2_idx);

    #if 1
        acfg_cust_video_update_GLL_all(TRUE);
    #else
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY));
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE));
        a_acfg_update_gaming_logo();
    #endif

        set_preset_pic_mode_chg_status_ex(TRUE);
    }

    menu_pm_repaint();
}


#ifdef APP_MENU_PQ_DEMO_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_vid_pq_demo_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_pq_demo_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_PQ_DEMO);
    a_cfg_av_set(ui2_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_pq_demo_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_pq_demo_idx(VOID)
{
    INT16 i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_PQ_DEMO), &i2_val);

    return (UINT16)i2_val;
}
#endif

#ifdef APP_XVYCC_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_vid_xvycc_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_xvycc_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_XVYCC);
    a_cfg_av_set(ui2_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_xvycc_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_xvycc_idx(VOID)
{
    INT16 i2_val;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_XVYCC), &i2_val);

    return (UINT16)i2_val;
}
#endif

#ifdef APP_WCG_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_vid_wcg_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_wcg_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_WCG);
    a_cfg_av_set(ui2_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_wcg_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_wcg_idx(VOID)
{
    INT16 i2_val;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_WCG), &i2_val);

    return (UINT16)i2_val;
}
#endif

#ifdef APP_BLUE_STRETCH_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_vid_blue_stretch_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_blue_stretch_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_STRETCH);

    if(ui2_idx == 0)
    {
        a_cfg_av_set(ui2_id, (INT16)SCC_VID_BLUE_STRETCH_OFF);
    }
    else
    {
        a_cfg_av_set(ui2_id, (INT16)SCC_VID_BLUE_STRETCH_BLUE);
    }

    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_blue_stretch_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_blue_stretch_idx(VOID)
{
    INT16 i2_val;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_STRETCH), &i2_val);


    if(i2_val == (INT16)SCC_VID_BLUE_STRETCH_OFF)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
#endif

#ifdef APP_MPEG_NR_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_vid_mpeg_nr_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vid_mpeg_nr_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR);
    UINT16  ui2_pre_idx = _get_vid_mpeg_nr_idx();

    a_cfg_av_set(ui2_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_id);
    if (ui2_pre_idx != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_mpeg_nr_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_vid_mpeg_nr_idx(VOID)
{
    INT16 i2_val;

    if(a_acfg_cust_is_gll_enable() == TRUE)
    {
        return (UINT16)0;
    }
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR), &i2_val);

    return (UINT16)i2_val;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _set_aud_volume
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_volume_val(INT32 i4_val)
{
    INT16 i2_aud_volume;

    i2_aud_volume = (INT16)i4_val;

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                 i2_aud_volume);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_volume_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_aud_volume_val(VOID)
{
    INT16   i2_aud_volume = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                 &i2_aud_volume);

    return i2_aud_volume;
}

INT32 menu_get_aud_volume_val(VOID)
{
    return _get_aud_volume_val();
}

/*----------------------------------------------------------------------------
 * Name: _increase_aud_volume
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_aud_volume(VOID)
{
    INT16   i2_aud_volume;

    a_cfg_av_incr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                  &i2_aud_volume);

    return i2_aud_volume;
}

/*----------------------------------------------------------------------------
 * Name: _decrease_aud_volume
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_aud_volume(VOID)
{
    INT16   i2_aud_volume;

    a_cfg_av_decr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                  &i2_aud_volume);

    return i2_aud_volume;
}

/*----------------------------------------------------------------------------
 * Name: _set_aud_balance
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_balance_val(INT32 i4_val)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE);
    INT16   i2_aud_balance;

    i2_aud_balance = (INT16)i4_val;

    a_cfg_av_set(ui2_id, i2_aud_balance);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_balance_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_aud_balance_val(VOID)
{
    INT16   i2_aud_balance;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), &i2_aud_balance);

    return (INT32)i2_aud_balance;
}

/*----------------------------------------------------------------------------
 * Name: _incr_aud_balance
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_aud_balance(VOID)
{
    INT16   i2_aud_balance;

    a_cfg_av_incr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), &i2_aud_balance);

    return (INT32)i2_aud_balance;
}

/*----------------------------------------------------------------------------
 * Name: _decr_aud_balance
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_aud_balance(VOID)
{
    INT16   i2_aud_balance;

    a_cfg_av_decr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), &i2_aud_balance);

    return (INT32)i2_aud_balance;
}


#if 1

/*----------------------------------------------------------------------------
 * Name: _set_aud_bass
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_bass_val(INT32 i4_val)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS);
    INT16   i2_aud_bass;

    i2_aud_bass = (INT16)i4_val;

    a_cfg_av_set(ui2_id, i2_aud_bass);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_bass_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_aud_bass_val(VOID)
{
    INT16   i2_aud_bass;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS), &i2_aud_bass);

    return (INT32)i2_aud_bass;
}

/*----------------------------------------------------------------------------
 * Name: _incr_aud_bass
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_aud_bass(VOID)
{
    INT16   i2_aud_bass;

    a_cfg_av_incr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS), &i2_aud_bass);

    return (INT32)i2_aud_bass;
}

/*----------------------------------------------------------------------------
 * Name: _decr_aud_bass
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_aud_bass(VOID)
{
    INT16   i2_aud_bass;

    a_cfg_av_decr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS), &i2_aud_bass);

    return (INT32)i2_aud_bass;
}

/*----------------------------------------------------------------------------
 * Name: _set_aud_treble
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_treble_val(INT32 i4_val)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE);
    INT16   i2_aud_treble;

    i2_aud_treble = (INT16)i4_val;

    a_cfg_av_set(ui2_id, i2_aud_treble);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_treble_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_aud_treble_val(VOID)
{
    INT16   i2_aud_treble;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE), &i2_aud_treble);

    return (INT32)i2_aud_treble;
}

/*----------------------------------------------------------------------------
 * Name: _incr_aud_treble
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_aud_treble(VOID)
{
    INT16   i2_aud_treble;

    a_cfg_av_incr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE), &i2_aud_treble);

    return (INT32)i2_aud_treble;
}

/*----------------------------------------------------------------------------
 * Name: _decr_aud_treble
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_aud_treble(VOID)
{
    INT16   i2_aud_treble;

    a_cfg_av_decr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE), &i2_aud_treble);

    return (INT32)i2_aud_treble;
}

#else

/*----------------------------------------------------------------------------
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/

static VOID _set_aud_bass_val(INT32 i4_val)
{
    amp_vndr_info.Bass = i4_val;
    nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_BASS, i4_val);
}

static INT32 _get_aud_bass_val(VOID)
{
    return (INT32)amp_vndr_info.Bass;
}

static VOID _set_aud_treble_val(INT32 i4_val)
{
    amp_vndr_info.Treble= i4_val;
    nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_TREBLE, i4_val);
}

static INT32 _get_aud_treble_val(VOID)
{
    return (INT32)amp_vndr_info.Treble;
}

#endif

//----------------------------add new----------------------------//
BOOL _get_sb_settings_eq_mode_valid_type(UINT8 eq_type)
{
    if (eq_type == _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MUSIC && amp_vndr_info.eq_mode_type_enable.music == TRUE) return TRUE;
    else if (eq_type == _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MOVIE && amp_vndr_info.eq_mode_type_enable.movie == TRUE) return TRUE;
    else if (eq_type == _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_GAME && amp_vndr_info.eq_mode_type_enable.game == TRUE) return TRUE;
    else if (eq_type == _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DIRECT && amp_vndr_info.eq_mode_type_enable.direct == TRUE) return TRUE;
    else if (eq_type == _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DIALOGUE && amp_vndr_info.eq_mode_type_enable.dialogue == TRUE) return TRUE;
    else return FALSE;
}

static UINT16 _get_menu_eq_mode_first_valid_type(VOID)
{
	INT8 first_eq_type_idx;

    if(amp_vndr_info.eq_mode_valid_num == 0)
    {
        return amp_vndr_info.items_type.eq;
    }

    for(first_eq_type_idx = _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT;first_eq_type_idx < _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MAX; first_eq_type_idx++)
    {
        if(_get_sb_settings_eq_mode_valid_type(first_eq_type_idx) == TRUE)
        {
            break;
        }
    }

    if(first_eq_type_idx >= _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MAX)
    return amp_vndr_info.items_type.eq;
    else
    return first_eq_type_idx;
}


static UINT16 _next_menu_eq_mode_idx(VOID)
{
    UINT8 next_eq_type_idx;
    UINT8 check_count = _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MAX;

    if(amp_vndr_info.eq_mode_valid_num == 0)
    {
        return amp_vndr_info.items_type.eq;
    }

    next_eq_type_idx = amp_vndr_info.items_type.eq;

#if 0
    do{
        next_eq_type_idx++;

        if(next_eq_type_idx >= _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MAX)
        {
            next_eq_type_idx = _get_menu_eq_mode_first_valid_type();
            break;
        }
        else
        {
            if(_get_sb_settings_eq_mode_valid_type(next_eq_type_idx) == TRUE)
            break;
        }

    }while(check_count--);
#endif

    amp_vndr_info.items_type.eq = next_eq_type_idx;
    _set_aud_eq_mode_val(next_eq_type_idx);
    menu_pm_repaint();
    return next_eq_type_idx;
}

static UINT16 _get_menu_eq_mode_last_valid_type(VOID)
{
	INT8 last_eq_type_idx = _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MAX;

    if(amp_vndr_info.eq_mode_valid_num == 0)
    {
        return amp_vndr_info.items_type.eq;
    }

    do{
        last_eq_type_idx--;

        if(_get_sb_settings_eq_mode_valid_type(last_eq_type_idx) == TRUE)
        {
            break;
        }
    }while(last_eq_type_idx > _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT);

    if(last_eq_type_idx < _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT)
    return amp_vndr_info.items_type.eq;
    else
    return last_eq_type_idx;
}


static UINT16 _prev_menu_eq_mode_idx(VOID)
{
	INT8 prev_eq_type_idx;
    UINT8 check_count = _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MAX;

    if(amp_vndr_info.eq_mode_valid_num == 0)
    {
        return amp_vndr_info.items_type.eq;
    }

#if 1
     prev_eq_type_idx = amp_vndr_info.items_type.eq;

#else
	do{
        prev_eq_type_idx--;

        if(prev_eq_type_idx < _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT)
        {
            prev_eq_type_idx = _get_menu_eq_mode_last_valid_type();
            break;
        }
        else
        {
            if(_get_sb_settings_eq_mode_valid_type(prev_eq_type_idx) == TRUE)
            break;
        }

    }while(check_count--);


    for(prev_eq_type_idx = amp_vndr_info.items_type.eq; prev_eq_type_idx >= _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT; --prev_eq_type_idx)
    {
        if(prev_eq_type_idx < _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT)
        {
            return _get_menu_eq_mode_last_valid_type();
        }
        else
        {
            if(_get_sb_settings_eq_mode_valid_type(prev_eq_type_idx) == TRUE)
            break;
        }
    }
#endif
    amp_vndr_info.items_type.eq = prev_eq_type_idx;
    _set_aud_eq_mode_val(prev_eq_type_idx);
    menu_pm_repaint();
    return prev_eq_type_idx;
}


static VOID _get_menu_eq_mode_text(UINT16 ui2_idx,   /* in */
                                                  UTF16_T*  w2s_str,   /* out */
                                                  SIZE_T    z_len)
{

    if(_get_sb_settings_eq_mode_valid_type(ui2_idx) == FALSE){
    c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_EMPTY),(UINT32) z_len-1);
    w2s_str[z_len - 1] = 0;
    return;
    }

    switch (ui2_idx)
    {
        case _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MUSIC:
        c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_EQ_MODE_MUSIC),(UINT32)z_len-1);
        break;

        case _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_MOVIE:
        c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_EQ_MODE_MOVIE),(UINT32)z_len-1);
        break;

        case _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_GAME:
        c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_EQ_MODE_GAME),(UINT32)z_len-1);
        break;

        case _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DIRECT:
        c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_EQ_MODE_DIRECT),(UINT32)z_len-1);
        break;

        case _MENU_COMMON_SETTINGS_SB_SETTINGS_EQ_MODE_DIALOGUE:
        c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_EQ_MODE_DIALOGUE),(UINT32)z_len-1);
        break;
        default:/* unknown eq mode type? */
        c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_EMPTY),(UINT32)z_len-1);
        break;
    }
    w2s_str[z_len - 1] = 0;
}

static VOID _set_aud_eq_mode_val(INT32 i4_val)
{
    amp_vndr_info.items_type.eq = i4_val;
    nav_cec_sac_set_EQ_mode(i4_val);
}

static INT32 _get_aud_eq_mode_val(VOID)
{
    return amp_vndr_info.items_type.eq ;
}

static VOID _set_aud_sb_bass_val(INT32 i4_val)
{
    amp_vndr_info.items_type.bass= (UINT8)i4_val;
    nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_BASS, i4_val);
}

static INT32 _get_aud_sb_bass_val(VOID)
{
    return (INT32)amp_vndr_info.items_type.bass;
}

static VOID _set_aud_sb_treble_val(INT32 i4_val)
{
    amp_vndr_info.items_type.treble = (UINT8)i4_val;
    nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_TREBLE, i4_val);
}

static INT32 _get_aud_sb_treble_val(VOID)
{
    return (INT32)amp_vndr_info.items_type.treble;
}

static VOID _set_aud_dialogue_val(INT32 i4_val)
{
    amp_vndr_info.items_type.dialogue=(UINT8) i4_val;
    nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_DIALOGUE, i4_val);
}

static INT32 _get_aud_dialogue_val(VOID)
{
    return (INT32)amp_vndr_info.items_type.dialogue;
}

static VOID _set_aud_subwoofer_val(INT32 i4_val)
{
    amp_vndr_info.items_type.subwoofer= (UINT8)i4_val;
    nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_SUBWOOFER, i4_val);
}

static INT32 _get_aud_subwoofer_val(VOID)
{
    return (INT32)amp_vndr_info.items_type.subwoofer;
}

static VOID _set_aud_night_mode_val(INT32 i4_val)
{
    amp_vndr_info.items_type.nightmode= (UINT8)i4_val;
    nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_NIGHTMODE, i4_val);
}

static INT32 _get_aud_night_mode_val(VOID)
{
    return (INT32)amp_vndr_info.items_type.nightmode;
}

static VOID _set_aud_virtualx_val(INT32 i4_val)
{
    amp_vndr_info.items_type.virtulx = (UINT8)i4_val;
    nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_VIRTUALX, i4_val);
}

static INT32 _get_aud_virtualx_val(VOID)
{
    return (INT32)amp_vndr_info.items_type.virtulx;
}

static VOID _set_aud_sb_speakertest_val(INT32 i4_val)
{
     amp_vndr_info.items_type.speakerTest = (UINT8)i4_val;
     nav_cec_sac_set_SpeakerTest();
}

static VOID _set_aud_sb_info_val(INT32 i4_val)
{
     amp_vndr_info.items_type.info = (UINT8)i4_val;
     nav_cec_sac_set_Info();
}

//----------------------------------------------------------------//

/*----------------------------------------------------------------------------
 * Name: _set_aud_surround_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_surround_idx(UINT16 ui2_idx)
{
    acfg_cust_audio_enable_surround_mode((SURROUND_MODE)ui2_idx);
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_surround_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_aud_surround_idx(VOID)
{
#if 0
    return (UINT16)acfg_cust_audio_is_surround_mode_enable();
#endif

   UINT8   ui1_mode   = 0;
   a_cfg_cust_get_surround_mode(&ui1_mode);
   return (UINT16)ui1_mode;

}

/*----------------------------------------------------------------------------
 * Name: _set_aud_reverb_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_reverb_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_REVERB);

    a_cfg_av_set(ui2_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_reverb_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_aud_reverb_idx(VOID)
{
    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_REVERB);
    INT16   i2_val = 0;

    a_cfg_av_get(ui2_id, &i2_val);
    return (UINT16)i2_val;
}

/*----------------------------------------------------------------------------
 * Name: _set_aud_speaker_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_speaker_idx(INT16 ui2_idx)
{
    UINT16          ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16          ui2_aud_out_mask;
    INT16           i2_val;
    INT32           i4_ret = 0;
    UINT8           ui1_icl_val = ICL_CEC_SAC_STATUS_OFF;
    SIZE_T          z_size = sizeof(UINT8);
    UINT8           ui1_sac_func = 0;


    a_cfg_av_get(ui2_id, &i2_val);
    ui2_aud_out_mask = (UINT16)i2_val;

    i4_ret = a_cfg_get_cec_sac_func(&ui1_sac_func);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("%s,%d get cec sac func fail i4_ret=%d \r\n",__FUNCTION__,__LINE__,i4_ret));
        return ;
    }

    if(ui2_idx == 2)
    {
        /* Off */
        NAV_CEC_LOG_I("speaker off\r\n");
        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);

    #if defined(APP_CEC_SUPPORT) && defined(APP_CEC2_SUPPORT)
        UINT8 ui1_cec_func=0;

        a_cfg_get_cec_func (&ui1_cec_func);
        if((ui1_cec_func != APP_CFG_CEC_OFF) && (ui1_sac_func == APP_CFG_CEC_OFF))
        {
            /* Turn on CEC SAC */
            a_cfg_set_cec_sac_func(1);
        }

    #endif
        a_cfg_custom_set_speakers_out(APP_CFG_AUD_AD_SPEAKER_OFF);
        rest_event_notify("tv_settings/audio/tv_speakers",0 ,"Off");
    }
    else if(ui2_idx == 1)
    {
        /* On */
        NAV_CEC_LOG_I("speaker on\r\n");
        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask | SCC_AUD_OUT_PORT_SPEAKER);

    #if defined(APP_CEC_SUPPORT) && defined(APP_CEC2_SUPPORT)
        /* Turn off CEC SAC */
        if(ui1_sac_func == APP_CFG_CEC_ON)
        {
            a_cfg_set_cec_sac_func(APP_CFG_CEC_OFF);
        }

        /*power off CEC audio receiver/ soundbar when turn on speaker*/
        c_cecm_set_standby(nav_cec_get_mw_handle(), CECM_LOG_ADDR_AUD_SYS);
        DBG_LOG_PRINT(("%s,%d c_cecm_set_standby\n\r",__FUNCTION__,__LINE__));

        CECM_SYS_AUD_CTRL_T t_sys_aud_ctrl;
        t_sys_aud_ctrl.e_aud_ctrl = CECM_SYS_AUD_STS_OFF;
        c_cecm_set_system_audio_mode_request(nav_cec_get_mw_handle(), &t_sys_aud_ctrl);
        DBG_LOG_PRINT(("%s,%d c_cecm_set_system_audio_mode_request\n\r",__FUNCTION__,__LINE__));

        NAV_CEC_EX_CTRL_PARAM_T t_param;
        NAV_CEC_EX_CTRL_RESULT_T t_result;
        t_param.e_cmd = NAV_CEC_EX_CTRL_CMD_SET_SAM_STATUS_OFF;
        i4_ret = a_nav_cec_do_ex_ctrl(&t_param, &t_result);
        DBG_LOG_PRINT(("%s,%d a_nav_cec_do_ex_ctrl NAV_CEC_EX_CTRL_CMD_SET_SAM_STATUS_OFF ret %d\n\r",__FUNCTION__,__LINE__, i4_ret));
    #endif

        a_cfg_custom_set_speakers_out(APP_CFG_AUD_AD_SPEAKER_ON);
        rest_event_notify("tv_settings/audio/tv_speakers",0 ,"On");


    }
    else if(ui2_idx == 0)
    {
        NAV_CEC_LOG_I("speaker auto\r\n");

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

        DBG_LOG_PRINT(("%s,%d [tv speaker] icl_sac_status=%d \n",__FUNCTION__,__LINE__,ui1_icl_val));
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
        rest_event_notify("tv_settings/audio/tv_speakers",0 ,"Auto");
    }

    NAV_CEC_LOG_I("ui2_aud_out_mask=%d\r\n", (INT16)ui2_aud_out_mask);
    a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
    a_cfg_av_update(ui2_id);

    // if TV Speaker is ON will force the digital mode as PCM,need to update spdif
    i4_ret = a_cfg_update_spdif_type();
}

/*----------------------------------------------------------------------------
 * Name: _set_aud_vol_dis_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_vol_dis_idx(UINT16 ui2_idx)
{
#if AUD_DIS_VOL_ENABLE
    a_cfg_cust_set_vol_control_dis_flag((UINT8)ui2_idx);

    /* set volume OSD hide or show */
    if(ACFG_CUSTOM_VOL_SLIDER_DIS_ON == ui2_idx)
    {
        a_vol_ctrl_set_visibility(TRUE);
    }
    else
    {
        a_vol_ctrl_set_visibility(FALSE);
    }

    DBG_LOG_PRINT(("%s,%d [vol dis idx]=%d \r\n",__FUNCTION__,__LINE__,ui2_idx));
   return;
#else
    UINT32 ui4_debug_mode = IOM_UART_OPERATION_MODE_CLI|IOM_UART_OPERATION_MODE_TRANSPARENT;
    DBG_LOG_PRINT(("%s,%d [vol dis idx]=%d \r\n",__FUNCTION__,__LINE__,ui2_idx));

    if(ui2_idx ==0)
    {
        ui4_debug_mode = IOM_UART_OPERATION_MODE_CLI|IOM_UART_OPERATION_MODE_TRANSPARENT;
    }
    else
    {
        ui4_debug_mode = IOM_UART_OPERATION_MODE_FACTORY|IOM_UART_OPERATION_MODE_TRANSPARENT;
    }
    c_iom_set(  h_iom_uart,
                IOM_SET_UART_OPERATION_MODE,
                &ui4_debug_mode,
                sizeof(ui4_debug_mode));


    DBG_INFO(("%s,%d [vol dis idx]=%d \r\n",__FUNCTION__,__LINE__,ui2_idx));
#endif
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_vol_dis_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_aud_vol_dis_idx(VOID)
{

#if AUD_DIS_VOL_ENABLE
    UINT8   ui1_vol_dis_flag = ACFG_CUSTOM_VOL_SLIDER_DIS_OFF;

    a_cfg_cust_get_vol_control_dis_flag(&ui1_vol_dis_flag);

    DBG_LOG_PRINT(("%s,%d [vol dis idx]=%d \r\n",__FUNCTION__,__LINE__,ui1_vol_dis_flag));

    return (UINT16)ui1_vol_dis_flag;

#else

    UINT32 ui4_current_mode = 0;
    SIZE_T current_mode_len = sizeof(UINT32);

    if (c_iom_get(h_iom_uart,
                  IOM_GET_UART_OPERATION_MODE,
                  &ui4_current_mode,
                  &current_mode_len)!=IOMR_OK)
    {
        DBG_ERROR(("<fact_parser> UART get fails\n"));
    }
    return (UINT16)((ui4_current_mode&IOM_UART_OPERATION_MODE_FACTORY) == 0 ? 0 : 1);
 #endif
}

/*----------------------------------------------------------------------------
 * Name: _set_aud_srs_truvolume_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_srs_truvolume_idx(UINT16 ui2_idx)
{
    acfg_cust_audio_enable_volume_level((INT16)ui2_idx);
}

/*----------------------------------------------------------------------------
 * Name: _set_aud_dialogue_enhancer_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_dialogue_enhancer_idx(UINT16 ui2_idx)
{
    acfg_audio_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_AC4_DE_GAIN), (INT16)ui2_idx);
    acfg_audio_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_AC4_DE_GAIN));
    //DBG_LOG_PRINT(("[screen_mode] {%s() %d}. NOT  ui2_idx = %d\n",__FUNCTION__, __LINE__,ui2_idx));

}

/*----------------------------------------------------------------------------
 * Name: _get_aud_speaker_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
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

    if(2 == ui2_idx)    //Auto
    {
        ui2_val = APP_CFG_AUD_AD_SPEAKER_OFF;
    }
    else
    {
        if(ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) //On
        {
            ui2_val = APP_CFG_AUD_AD_SPEAKER_ON;
        }
        else  // Off
        {
            ui2_val = APP_CFG_AUD_AD_SPEAKER_AUTO;
        }
    }

    return ui2_val;
}
/*----------------------------------------------------------------------------
 * Name: _get_aud_vol_control_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_aud_vol_control_idx(VOID)
{
    UINT8   ui1_val = 0;

    a_cfg_custom_get_vol_control(&ui1_val);

    return (UINT16)(ui1_val);
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_vol_control_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_vol_control_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_SURROUND);

    a_cfg_custom_set_vol_control((INT8)ui2_idx);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_srs_truvolume_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_aud_srs_truvolume_idx(VOID)
{
    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AGC);
    INT16   i2_val;

    a_cfg_av_get(ui2_id, &i2_val);

    return (UINT16)(i2_val);
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_dialogue_enhancer_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_aud_dialogue_enhancer_idx(VOID)
{
    INT16 i2_status = 0;
    acfg_audio_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_AC4_DE_GAIN), &i2_status);
    //DBG_LOG_PRINT(("[screen_mode] {%s() %d}. NOT  ui4_status = %d\n",__FUNCTION__, __LINE__,ui4_status));
    return (UINT16)i2_status;
}

/*----------------------------------------------------------------------------
 * Name: _set_aud_mts_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_mts_idx(UINT16 ui2_idx)
{
    UINT16          ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS);
    SCC_AUD_MTS_T   e_mts;

    switch(ui2_idx)
    {
    case 0: /* STEREO */
        e_mts = SCC_AUD_MTS_STEREO;
        break;
    case 1: /* SAP */
        e_mts = SCC_AUD_MTS_SUB_LANG;
        break;
    case 2: /* MONO */
        e_mts = SCC_AUD_MTS_MONO;
        break;
    default:
        e_mts = SCC_AUD_MTS_STEREO;
        break;
    }

    a_cfg_av_set(ui2_id, (INT16)e_mts);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_mts_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_aud_mts_idx(VOID)
{
    UINT16          ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS);
    INT16           i2_val = (INT16)SCC_AUD_MTS_STEREO;
    SCC_AUD_MTS_T   e_mts;
    UINT16          ui2_idx;

    a_cfg_av_get(ui2_id, &i2_val);

    e_mts = (SCC_AUD_MTS_T)i2_val;

    switch(e_mts)
    {
    case SCC_AUD_MTS_MONO:
        ui2_idx = 2;
        break;
    case SCC_AUD_MTS_STEREO:
        ui2_idx = 0;
        break;
    case SCC_AUD_MTS_SUB_LANG:
        ui2_idx = 1;
        break;
    default:
        ui2_idx = 1;
        break;
    }

    return (UINT16)ui2_idx;
}

/*----------------------------------------------------------------------------
 * Name: _set_aud_latency_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_latency_val(INT32 i4_val)
{
    INT16   i2_latency = (INT16)i4_val;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY);

    if (-1 == i2_old_latency_val)
    {
        a_cfg_get_lip_sync(&i2_old_latency_val);
    }

    if (i2_latency == i2_old_latency_val)
    {
        return;
    }

    i2_old_latency_val = i2_latency;

    i2_latency = i2_latency*10;
    a_cfg_set_lip_sync(i2_latency);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_latency_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_aud_latency_val(VOID)
{
    INT16   i2_latency;

    a_cfg_get_lip_sync(&i2_latency);
    i2_latency = i2_latency/10;
    return i2_latency;
}

/*----------------------------------------------------------------------------
 * Name: _set_fac_aud_latency_val
 *
 * Description:  Update chnnel delay to driver..
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: VOID
 *
 ----------------------------------------------------------------------------*/
static VOID _set_fac_aud_latency_val(INT32 i4_val)
{
    HANDLE_T h_audio = NULL_HANDLE;
    SM_COMMAND_T at_sm_cmds[3];
    SCC_AUD_CHNL_DELAY_T    t_ch_delay;
    INT16 i2_latency;

    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    //Fix Coverity ID :1142707 Unchecked return value
    if (c_scc_comp_open (at_sm_cmds, &h_audio) != SMR_OK)
    {
        DBG_ERROR(("<MENU> Set fac aud latency val fail"));
    }

    i2_latency = (INT16)i4_val;

    t_ch_delay.e_ch_delay_type  = SCC_AUD_CHNL_DELAY_TYPE_ALL;
    t_ch_delay.e_out_port       = SCC_AUD_OUT_PORT_2_CH;
    t_ch_delay.u.ui2_delay      =(UINT16)i2_latency;

    c_scc_aud_set_chnl_delay(h_audio, &t_ch_delay);
    c_scc_comp_close(h_audio);
}

/*----------------------------------------------------------------------------
 * Name: _get_fac_aud_latency_val
 *
 * Description: Get chnnel delay from driver..
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_fac_aud_latency_val(VOID)
{
    HANDLE_T h_audio = NULL_HANDLE;
    SM_COMMAND_T at_sm_cmds[3];
    SCC_AUD_CHNL_DELAY_T    t_ch_delay;
    INT16 i2_latency;

    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    //Fix Coverity ID :1142734 Unchecked return value
    if (c_scc_comp_open (at_sm_cmds, &h_audio) != SMR_OK)
    {
        DBG_ERROR(("<MENU> Get fac aud latency val fail"));
    }

    t_ch_delay.e_ch_delay_type  = SCC_AUD_CHNL_DELAY_TYPE_ALL;
    t_ch_delay.e_out_port = SCC_AUD_OUT_PORT_2_CH;

    c_scc_aud_get_chnl_delay(h_audio, &t_ch_delay);
    i2_latency = (INT16)t_ch_delay.u.ui2_delay;

    c_scc_comp_close(h_audio);

    return i2_latency;
}
#ifdef APP_BBE_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_aud_bbe_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_bbe_mode_idx(UINT16 ui2_idx)
{
    UINT16              ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BBE_MODE);
    SCC_AUD_BBE_MODE_T  e_aud_bbe_mode;

    switch(ui2_idx)
    {
    case 0:
        e_aud_bbe_mode = SCC_AUD_BBE_MODE_OFF;
        break;
    case 1:
        e_aud_bbe_mode = SCC_AUD_BBE_MODE_BBE;
        break;
#ifdef APP_BBE_VIVA_SUPPORT
    case 2:
        e_aud_bbe_mode = SCC_AUD_BBE_MODE_BBE_VIVA;
        break;
#endif
    default:
        e_aud_bbe_mode = SCC_AUD_BBE_MODE_OFF;
        break;
    }

    a_cfg_av_set(ui2_id, (INT16)e_aud_bbe_mode);
    a_cfg_av_update(ui2_id);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQUALIZER));
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_bbe_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_aud_bbe_mode_idx(VOID)
{
    UINT16              ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BBE_MODE);
    INT16               i2_val = (INT16)SCC_AUD_BBE_MODE_OFF;
    SCC_AUD_BBE_MODE_T  e_aud_bbe_mode;
    UINT16              ui2_idx;

    a_cfg_av_get(ui2_id, &i2_val);

    e_aud_bbe_mode = (SCC_AUD_BBE_MODE_T)i2_val;

    switch(e_aud_bbe_mode)
    {
    case SCC_AUD_BBE_MODE_OFF:
        ui2_idx = 0;
        break;
    case SCC_AUD_BBE_MODE_BBE:
        ui2_idx = 1;
        break;
#ifdef APP_BBE_VIVA_SUPPORT
    case SCC_AUD_BBE_MODE_BBE_VIVA:
        ui2_idx = 2;
        break;
#endif
    default:
        ui2_idx = 0;
        break;
    }

    return (UINT16)ui2_idx;
}
#endif /* APP_BBE_SUPPORT */

/*----------------------------------------------------------------------------
 * Name: _set_tv_tuner_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
#ifdef LINUX_AUTO_TEST
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

#define tuner_mode  "/tmp/autotest/tuner_mode_is_cable"
#endif

static VOID _set_tv_tuner_mode_idx(UINT16 ui2_idx)
{
    UINT16      ui2_svl_id;

    if(ui2_idx == 0)
    {
        ui2_svl_id = ATSC_CABLE_SVL_ID;
    }
    else
    {
        ui2_svl_id = ATSC_TRSTRL_SVL_ID;
    #ifdef LINUX_AUTO_TEST
        system("rm -f "tuner_mode);
    #endif
    }

    a_cfg_set_tuner_sync_src(ui2_svl_id, NULL);

#ifdef APP_MENU_DONT_SKIP_FAKE_CHANNEL_WHEN_TOGGLE_TUNER_MODE

    /* Reselect the current channel. Don't skip fake channel. */
    menu_select_crnt_or_first_channel(FALSE);

#else

    /* Reselect the current channel. Skip the fake channel. */
    menu_select_crnt_or_first_channel(TRUE);

#endif /* APP_MENU_DONT_SKIP_FAKE_CHANNEL_WHEN_TOGGLE_TUNER_MODE */

    c_sys_config_reset();

}

/*----------------------------------------------------------------------------
 * Name: _get_tv_tuner_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_tv_tuner_mode_idx(VOID)
{
    UINT8 ui1_value = 0;
    a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, &ui1_value);

    if (APP_CFG_BS_SRC_CABLE == ui1_value)
    {
        ui1_value = 0;
    #ifdef LINUX_AUTO_TEST
        system("touch "tuner_mode);
    #endif
    }
    else
    {
        ui1_value = 1;
    }
    return (UINT16)ui1_value;
}

/*----------------------------------------------------------------------------
 * Name: _set_misc_blue_mute_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_misc_blue_mute_idx(UINT16 ui2_idx)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE);
    a_cfg_av_set(ui2_id, (INT16)ui2_idx);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_misc_blue_mute_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_misc_blue_mute_idx(VOID)
{
    INT16   i2_val;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE);
    a_cfg_av_get(ui2_id, &i2_val);

    return (UINT16)(i2_val ? 1 : 0);
}


/*----------------------------------------------------------------------------
 * Sleep Timer.
 * #Elemenets = #REC + 1
 *
 *  The last element is current remaining time record. It cannot switch to this
 *  record by next and previous operation.
 ----------------------------------------------------------------------------*/
static VOID _set_misc_sleep_timer_idx(UINT16 ui2_idx)
{
    UINT32  ui4_time = 0;

    a_sleep_timer_get_time_by_idx((UINT8)ui2_idx, &ui4_time);
    if(ui4_time == 0)
    {
        a_sleep_timer_stop();
    }
    else
    {
        a_sleep_timer_start(ui4_time);
    }
}

static UINT16 _get_misc_sleep_timer_idx(VOID)
{
    UINT8   ui1_num_rec = 0;
    UINT16  ui1_idx = 0;
    UINT32  ui4_time = 0;
    UINT32  ui4_time_remaining = 0;

    a_sleep_timer_get_num_rec(&ui1_num_rec);
    a_sleep_timer_get_remaining_time(&ui4_time_remaining);

    for(ui1_idx=0; ui1_idx<ui1_num_rec; ui1_idx++)
    {
        a_sleep_timer_get_time_by_idx(ui1_idx,  &ui4_time);
        if(ui4_time_remaining <= ui4_time)
        {
            break;
        }
    }
#if 1
    if(ui1_idx == ui1_num_rec)
    {
        /* only happen when someone sets the timer by a_sleep_timer_start() directly,*/
        /* Use the last element */
        a_sleep_timer_stop();
        ui1_idx = 0;
    }

#else
    if(ui1_idx == ui1_num_rec)
    {
        /* only happen when someone sets the timer by a_sleep_timer_start() directly,*/
        /* Use the last element */
    }
    else if(ui4_time - ui4_time_remaining > 60)
    {
        /* Remaing time is not near one record, use the last element */
        ui1_idx = ui1_num_rec;
    }
    else
    {
        /* Remaing time is near one record, use this index */
    }
#endif
    return ui1_idx;
}

static UINT16 _prev_misc_sleep_timer_idx(VOID)
{
    UINT8   ui1_idx = 0;
    UINT32  ui4_time= 0;

    a_sleep_timer_iterate(STIMER_ITERATE_DIR_PREV,
                          &ui1_idx,
                          &ui4_time);

    return ui1_idx;
}

static UINT16 _next_misc_sleep_timer_idx(VOID)
{
    UINT8   ui1_idx = 0;
    UINT32  ui4_time= 0;

    a_sleep_timer_iterate(STIMER_ITERATE_DIR_NEXT,
                          &ui1_idx,
                          &ui4_time);

    return ui1_idx;
}

static VOID _get_misc_sleep_timer_text(
    UINT16    ui2_idx,   /* in */
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len)     /* in, len of w2s_str */
{
    UINT32  ui4_remaining_time = 0;
    UINT32  ui4_time = 0;
    UINT8   ui1_num_rec = 0;
    BOOL    b_is_the_item = FALSE;

    if(w2s_str == NULL)
    {
        return ;
    }

    a_sleep_timer_get_num_rec(&ui1_num_rec);
    a_sleep_timer_get_remaining_time(&ui4_remaining_time);

    if(ui2_idx < ui1_num_rec)
    {
        if(menu_page_is_in_list_subpage_state())
        {
            b_is_the_item = menu_focus_item_is_the_assign_item(MLM_MENU_KEY_TITLE_SLEEP_TIMER);
            if(b_is_the_item)
            {
            a_sleep_timer_get_time_by_idx(ui2_idx, &ui4_time);
            a_sleep_timer_get_text(ui4_time, w2s_str, z_len);
        }
        else
        {
            if(ui4_remaining_time == 0)
    {
                a_sleep_timer_get_time_by_idx(ui2_idx, &ui4_time);
        a_sleep_timer_get_text(ui4_time, w2s_str, z_len);
    }
    else
    {

                if(ui2_idx == _get_misc_sleep_timer_idx())
                {
                    a_sleep_timer_get_text(ui4_remaining_time, w2s_str, z_len);
                }
                else
                {
        a_sleep_timer_get_time_by_idx(ui2_idx, &ui4_time);
        a_sleep_timer_get_text(ui4_time, w2s_str, z_len);
    }
}
            }
        }
        else
        {
            if(ui4_remaining_time == 0)
            {
                a_sleep_timer_get_time_by_idx(ui2_idx, &ui4_time);
                a_sleep_timer_get_text(ui4_time, w2s_str, z_len);
            }
            else
            {
                if(ui2_idx == _get_misc_sleep_timer_idx())
                {
                    a_sleep_timer_get_text(ui4_remaining_time, w2s_str, z_len);
                }
                else
                {
                    a_sleep_timer_get_time_by_idx(ui2_idx, &ui4_time);
                    a_sleep_timer_get_text(ui4_time, w2s_str, z_len);
                }
            }
        }
    }
    else
    {
        c_memset(w2s_str, 0x0, z_len * sizeof(UTF16_T));
    }

    return;
}

#if 0
/*----------------------------------------------------------------------------
 * Name: _set_misc_auto_sleep_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_misc_auto_sleep_idx(UINT16 ui2_idx)
{
    UINT32 ui4_auto_sleep;

    switch(ui2_idx)
    {
    case 0:
        ui4_auto_sleep = 0;     /* OFF */
        break;
    case 1:
        ui4_auto_sleep = 1800;  /* 30 Min */
        break;
    case 2:
        ui4_auto_sleep = 3600;  /* 60 Min */
        break;
    case 3:
        ui4_auto_sleep = 5400; /* 90 Min */
        break;
    case 4:
        ui4_auto_sleep = 7200; /* 120 Min */
        break;
    case 5:
        ui4_auto_sleep = 10800; /* 180 Min */
        break;
    default:
        ui4_auto_sleep = 0;
        break;
    }

    if(ui4_auto_sleep == 0)
    {
        a_sleep_timer_stop();
    }
    else
    {
        a_sleep_timer_start(ui4_auto_sleep);
    }
}

/*----------------------------------------------------------------------------
 * Name: _get_misc_auto_sleep_idx
 *

 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_misc_auto_sleep_idx(VOID)
{
    UINT16 ui2_idx;
    UINT32  ui4_time_remaining;

    a_sleep_timer_get_remaining_time(&ui4_time_remaining);

    if (ui4_time_remaining == 0)
    {
        ui2_idx = 0;          /* Off */
    }
    else if ((ui4_time_remaining > 0) && (ui4_time_remaining <= 2700))
    {
        ui2_idx = 1;         /* 30 Min */
    }
    else if ((ui4_time_remaining > 2700) && (ui4_time_remaining <= 4500))
    {
        ui2_idx = 2;         /* 60 Min */
    }
    else if ((ui4_time_remaining > 4500) && (ui4_time_remaining <= 6300))
    {
        ui2_idx = 3;         /* 90 Min */
    }
    else if ((ui4_time_remaining > 6300) && (ui4_time_remaining <= 7200))
    {
        ui2_idx = 4;         /* 120 Min */
    }
    else if ((ui4_time_remaining > 7200) && (ui4_time_remaining <= 10800))
    {
        ui2_idx = 5;         /* 180 Min */
    }
    else
    {
        ui2_idx = 0;
    }

    return ui2_idx;
}
#endif
/*----------------------------------------------------------------------------
 * Name: _set_vga_pos_h
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vga_pos_h_val(INT32 i4_val)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_H);
    INT16   i2_vga_pos_h;

    i2_vga_pos_h = (INT16)i4_val;
    a_cfg_av_set(ui2_id, i2_vga_pos_h);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vga_pos_h_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vga_pos_h_val(VOID)
{
    INT32   i4_ret;
    INT16   i2_vga_pos_h;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_H), &i2_vga_pos_h);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_pos_h_last = i2_vga_pos_h;
    }
    else
    {
        i2_vga_pos_h = i2_g_vga_pos_h_last;
    }


    return i2_vga_pos_h;
}

/*----------------------------------------------------------------------------
 * Name: _incr_vga_pos_h
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_vga_pos_h(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_pos_h;

    i4_ret = a_cfg_av_incr(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_H), &i2_vga_pos_h);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_pos_h_last = i2_vga_pos_h;
    }
    else
    {
        i2_vga_pos_h = i2_g_vga_pos_h_last;
    }

    return i2_vga_pos_h;
}

/*----------------------------------------------------------------------------
 * Name: _decr_vga_pos_h
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_vga_pos_h(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_pos_h;

    i4_ret = a_cfg_av_decr(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_H), &i2_vga_pos_h);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_pos_h_last = i2_vga_pos_h;
    }
    else
    {
        i2_vga_pos_h = i2_g_vga_pos_h_last;
    }

    return i2_vga_pos_h;
}

/*----------------------------------------------------------------------------
 * Name: _set_vga_pos_v
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vga_pos_v_val(INT32 i4_val)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_V);
    INT16 i2_vga_pos_v;

    i2_vga_pos_v = (INT16)i4_val;
    a_cfg_av_set(ui2_id, i2_vga_pos_v);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vga_pos_v_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vga_pos_v_val(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_pos_v;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_V), &i2_vga_pos_v);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_pos_v_last = i2_vga_pos_v;
    }
    else
    {
        i2_vga_pos_v = i2_g_vga_pos_v_last;
    }

    return i2_vga_pos_v;
}

/*----------------------------------------------------------------------------
 * Name: _incr_vga_pos_v
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_vga_pos_v(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_pos_v;

    i4_ret = a_cfg_av_incr(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_V), &i2_vga_pos_v);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_pos_v_last = i2_vga_pos_v;
    }
    else
    {
        i2_vga_pos_v = i2_g_vga_pos_v_last;
    }

    return i2_vga_pos_v;
}

/*----------------------------------------------------------------------------
 * Name: _decr_vga_pos_v
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_vga_pos_v(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_pos_v;

    i4_ret = a_cfg_av_decr(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_V), &i2_vga_pos_v);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_pos_v_last = i2_vga_pos_v;
    }
    else
    {
        i2_vga_pos_v = i2_g_vga_pos_v_last;
    }

    return i2_vga_pos_v;
}

/*----------------------------------------------------------------------------
 * Name: _set_vga_phase
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vga_phase_val(INT32 i4_val)
{
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_PHASE);
    INT16 i2_vga_phase;

    i2_vga_phase = (INT16)i4_val;
    a_cfg_av_set(ui2_id, i2_vga_phase);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vga_phase_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vga_phase_val(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_phase;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_PHASE), &i2_vga_phase);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_phase_last = i2_vga_phase;
    }
    else
    {
        i2_vga_phase = i2_g_vga_phase_last;
    }

    return i2_vga_phase;
}

/*----------------------------------------------------------------------------
 * Name: _incr_vga_phase
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_vga_phase(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_phase;

    i4_ret = a_cfg_av_incr(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_PHASE), &i2_vga_phase);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_phase_last = i2_vga_phase;
    }
    else
    {
        i2_vga_phase = i2_g_vga_phase_last;
    }

    return i2_vga_phase;
}

/*----------------------------------------------------------------------------
 * Name: _decr_vga_phase
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_vga_phase(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_phase;

    i4_ret = a_cfg_av_decr(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_PHASE), &i2_vga_phase);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_phase_last = i2_vga_phase;
    }
    else
    {
        i2_vga_phase = i2_g_vga_phase_last;
    }

    return i2_vga_phase;
}

/*----------------------------------------------------------------------------
 * Name: _set_vga_clock
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_vga_clock_val(INT32 i4_val)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_CLOCK);
    INT16   i2_vga_clock;

    i2_vga_clock = (INT16)i4_val;
    a_cfg_av_set(ui2_id, i2_vga_clock);
    a_cfg_av_update(ui2_id);
}

/*----------------------------------------------------------------------------
 * Name: _get_vga_clock_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_vga_clock_val(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_clock;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_CLOCK), &i2_vga_clock);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_clock_last = i2_vga_clock;
    }
    else
    {
        i2_vga_clock = i2_g_vga_clock_last;
    }

    return i2_vga_clock;
}

/*----------------------------------------------------------------------------
 * Name: _incr_vga_clock
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_vga_clock(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_clock;

    i4_ret = a_cfg_av_incr(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_CLOCK), &i2_vga_clock);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_clock_last = i2_vga_clock;
    }
    else
    {
        i2_vga_clock = i2_g_vga_clock_last;
    }

    return i2_vga_clock;
}

/*----------------------------------------------------------------------------
 * Name: _decr_vga_clock
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_vga_clock(VOID)
{
    INT32 i4_ret;
    INT16 i2_vga_clock;

    i4_ret = a_cfg_av_decr(CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_CLOCK), &i2_vga_clock);
    if(i4_ret == APP_CFGR_OK)
    {
        i2_g_vga_clock_last = i2_vga_clock;
    }
    else
    {
        i2_vga_clock = i2_g_vga_clock_last;
    }

    return i2_vga_clock;
}

/* SPDIF */
static VOID _set_aud_spdif_idx(UINT16 ui2_idx)
{
    INT32 i4_ret ;
    i4_ret = menu_custom_set_aud_spdif(ui2_idx);
    MENU_LOG_ON_FAIL(i4_ret);
}

static UINT16 _get_aud_spdif_idx(VOID)
{
    UINT16      ui2_val = 0;
    UINT16      ui2_idx = 0;

    a_cfg_custom_get_digital_audio(&ui2_idx);

    if(AUD_SPDIF_AUDIO_OUT_AUTO == ui2_idx)    // Auto
    {
        ui2_val = AUD_SPDIF_AUDIO_OUT_AUTO;
    }
    else if(AUD_SPDIF_AUDIO_OUT_PCM == ui2_idx) //PCM
    {
        ui2_val = AUD_SPDIF_AUDIO_OUT_PCM;
    }
    else if(AUD_SPDIF_AUDIO_OUT_DOLBY_D == ui2_idx) //Dolby D
    {
        ui2_val = AUD_SPDIF_AUDIO_OUT_DOLBY_D;
    }
    else if(AUD_SPDIF_AUDIO_OUT_BITSTREAM == ui2_idx) //Bitstream
    {
        ui2_val = AUD_SPDIF_AUDIO_OUT_BITSTREAM;
    }
    else
    {
        ui2_val = AUD_SPDIF_AUDIO_OUT_AUTO;    //Auto
    }

    return ui2_val;
}

#ifdef APP_SPDIF_DELAY_SUPPORT
/* SPDIF Delay*/
/*----------------------------------------------------------------------------
 * Name: _set_aud_spdif_delay_val
 *
 * Description: set audio spdif delay value
 *
 * Inputs:  i4_val
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_spdif_delay_val(INT32 i4_val)
{
    INT16   i2_spdif_delay;

    i2_spdif_delay = (INT16)i4_val;

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO,  APP_CFG_RECID_SPDIF_DELAY),
                            i2_spdif_delay);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO,  APP_CFG_RECID_SPDIF_DELAY));
}

/*----------------------------------------------------------------------------
 * Name: _get_vga_clock_val
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_aud_spdif_delay_val(VOID)
{
    INT16 i2_spdif_delay;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SPDIF_DELAY),
                            &i2_spdif_delay);

    //i2_spdif_delay = (INT16)(i2_spdif_delay*10);

    return i2_spdif_delay;
}

/*----------------------------------------------------------------------------
 * Name: _incr_aud_spdif_delay
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _incr_aud_spdif_delay(VOID)
{
    INT16   i2_spdif_delay;

    a_cfg_av_incr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SPDIF_DELAY),
                              &i2_spdif_delay);

    //i2_spdif_delay = (INT16)(i2_spdif_delay*10);

    return i2_spdif_delay;
}

/*----------------------------------------------------------------------------
 * Name: _decr_aud_spdif_delay
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _decr_aud_spdif_delay(VOID)
{
    INT16   i2_spdif_delay;

    a_cfg_av_decr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SPDIF_DELAY),
                              &i2_spdif_delay);

    //i2_spdif_delay = (INT16)(i2_spdif_delay*10);

    return i2_spdif_delay;
}
#endif /* END of APP_SPDIF_DELAY_SUPPORT */

/* Aspect Ratio */
static VOID _set_tv_ar_idx(UINT16 ui2_idx)
{
    SCC_DISP_ASPECT_RATIO_T e_disp_ar;

    switch(ui2_idx)
    {
    case 0:
        e_disp_ar = SCC_DISP_ASPECT_RATIO_4_3;
        break;
    case 1:
    default:
        e_disp_ar = SCC_DISP_ASPECT_RATIO_16_9;
        break;
    }

    a_cfg_set_disp_aspect_ratio(e_disp_ar);

    a_cfg_update_disp_aspect_ratio();
}

static UINT16 _get_tv_ar_idx(VOID)
{
    UINT16 ui2_idx;
    SCC_DISP_ASPECT_RATIO_T e_tv_ar = SCC_DISP_ASPECT_RATIO_16_9;
    a_cfg_get_disp_aspect_ratio(&e_tv_ar);

    switch(e_tv_ar)
    {
    case SCC_DISP_ASPECT_RATIO_4_3:
        ui2_idx = 0;
        break;
    case SCC_DISP_ASPECT_RATIO_16_9:
    default:
        ui2_idx = 1;
        break;
    }

    return ui2_idx;
}

/* Dolby Cert Mode */
/*----------------------------------------------------------------------------
 * Name: _set_dolby_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_dolby_mode_idx(UINT16 ui2_idx)
{
    BOOL b_enable;

    b_enable = (ui2_idx == 0 ? FALSE : TRUE);

    a_cfg_set_dolby_cert_mode(b_enable);

    a_cfg_update_dolby_cert_mode();
}

/*----------------------------------------------------------------------------
 * Name: _get_dolby_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_dolby_mode_idx(VOID)
{
    BOOL   b_enable;

    a_cfg_get_dolby_cert_mode(&b_enable);

    return (UINT16)(b_enable ? 1 : 0);
}

/* Dolby Dynamic Range Compression */
/*----------------------------------------------------------------------------
 * Name: _set_drc_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_drc_idx(UINT16 ui2_idx)
{
    SCC_AUD_DOLBY_DRC_T e_drc;

    switch(ui2_idx)
    {
    case 0:
        e_drc = SCC_AUD_DOLBY_DRC_OFF;
        break;
    case 1:
        e_drc = SCC_AUD_DOLBY_DRC_10;
        break;
    case 2:
        e_drc = SCC_AUD_DOLBY_DRC_20;
        break;
    case 3:
        e_drc = SCC_AUD_DOLBY_DRC_30;
        break;
    case 4:
        e_drc = SCC_AUD_DOLBY_DRC_40;
        break;
    case 5:
        e_drc = SCC_AUD_DOLBY_DRC_50;
        break;
    case 6:
        e_drc = SCC_AUD_DOLBY_DRC_60;
        break;
    case 7:
        e_drc = SCC_AUD_DOLBY_DRC_70;
        break;
    case 8:
        e_drc = SCC_AUD_DOLBY_DRC_80;
        break;
    case 9:
        e_drc = SCC_AUD_DOLBY_DRC_90;
        break;
    case 10:
        e_drc = SCC_AUD_DOLBY_DRC_100;
        break;
    default:
        e_drc = SCC_AUD_DOLBY_DRC_OFF;
        break;
    }

    a_cfg_set_drc_mode(e_drc);

    a_cfg_update_drc_mode();
}

/*----------------------------------------------------------------------------
 * Name: _get_drc_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_drc_idx(VOID)
{
    UINT16 ui2_idx;
    SCC_AUD_DOLBY_DRC_T e_drc = SCC_AUD_DOLBY_DRC_OFF;

    a_cfg_get_drc_mode(&e_drc);

    switch(e_drc)
    {
    case SCC_AUD_DOLBY_DRC_OFF:
        ui2_idx = 0;
        break;
    case SCC_AUD_DOLBY_DRC_10:
        ui2_idx = 1;
        break;
    case SCC_AUD_DOLBY_DRC_20:
        ui2_idx = 2;
        break;
    case SCC_AUD_DOLBY_DRC_30:
        ui2_idx = 3;
        break;
    case SCC_AUD_DOLBY_DRC_40:
        ui2_idx = 4;
        break;
    case SCC_AUD_DOLBY_DRC_50:
        ui2_idx = 5;
        break;
    case SCC_AUD_DOLBY_DRC_60:
        ui2_idx = 6;
        break;
    case SCC_AUD_DOLBY_DRC_70:
        ui2_idx = 7;
        break;
    case SCC_AUD_DOLBY_DRC_80:
        ui2_idx = 8;
        break;
    case SCC_AUD_DOLBY_DRC_90:
        ui2_idx = 9;
        break;
    case SCC_AUD_DOLBY_DRC_100:
        ui2_idx = 10;
        break;
    default:
        DBG_ERROR(("<MENU>Unknown dolby dynamic range compression \r\n"));
        ui2_idx = 0;
    }

    return ui2_idx;
}

/* Dolby Compression Mode */
/*----------------------------------------------------------------------------
 * Name: _set_cmpss_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_cmpss_idx(UINT16 ui2_idx)
{
    SCC_AUD_CMPSS_MDOE_T e_cmpss;

    switch(ui2_idx)
    {
    case 0:
        e_cmpss = SCC_AUD_CMPSS_MDOE_LINE;
        break;
    case 1:
        e_cmpss = SCC_AUD_CMPSS_MDOE_RF;
        break;
    default:
        e_cmpss = SCC_AUD_CMPSS_MDOE_LINE;
        break;
    }

    a_cfg_set_cmpss_mode(e_cmpss);

    a_cfg_update_cmpss_mode();
}

/*----------------------------------------------------------------------------
 * Name: _get_cmpss_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_cmpss_idx(VOID)
{
    UINT16 ui2_idx;
    SCC_AUD_CMPSS_MDOE_T e_cmpss = SCC_AUD_CMPSS_MDOE_LINE;

    a_cfg_get_cmpss_mode(&e_cmpss);

    switch(e_cmpss)
    {
    case SCC_AUD_CMPSS_MDOE_LINE:
        ui2_idx = 0;
        break;
    case SCC_AUD_CMPSS_MDOE_RF:
        ui2_idx = 1;
        break;
    default:
        DBG_ERROR(("<MENU>Unknown dolby compression mode\r\n"));
        ui2_idx = 0;
    }

    return ui2_idx;
}

/* Dolby Downmix Mode */
/*----------------------------------------------------------------------------
 * Name: _set_dmix_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_dmix_idx(UINT16 ui2_idx)
{
    SCC_AUD_DOWNMIX_MODE_T e_dmix;
    INT32 i4_ret;

    switch(ui2_idx)
    {
    case 0:
        e_dmix = SCC_AUD_DOWNMIX_MODE_OFF;
        break;
    case 1:
        e_dmix = SCC_AUD_DOWNMIX_MODE_LT_RT;
        break;
    case 2:
        e_dmix = SCC_AUD_DOWNMIX_MODE_STEREO;
        break;
    default:
        e_dmix = SCC_AUD_DOWNMIX_MODE_OFF;
        break;
    }

    a_cfg_set_dmix_mode(e_dmix);
    //Fix Coverity ID:4491280 Unchecked return value
    i4_ret = a_cfg_update_dmix_mode();
    MENU_LOG_ON_FAIL(i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _set_aud_bypass_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_aud_bypass_mode_idx(UINT16 ui2_idx)
{
    INT32 i4_ret = MENUR_OK;

#ifdef APP_VIZIO_5396_PORTING_FAC
    DRV_CUST_OPERATION_INFO_T   t_op_info;
    AUD_DEC_SRS_BYPASS_MODE_T   e_aud_bypass_mode = AUD_DEC_SRS_BYPASS_OFF;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    if (1 == ui2_idx)
    {
        e_aud_bypass_mode = AUD_DEC_SRS_BYPASS_ON;
    }
    else
    {
        e_aud_bypass_mode = AUD_DEC_SRS_BYPASS_OFF;
    }

    ui2_aud_bypass_mode_idx = ui2_idx;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_AUD_SET;
    t_op_info.u.t_misc_set_info.e_misc_type = DRV_CUSTOM_AUD_SET_SRS_BYPASS;
    t_op_info.u.t_misc_set_info.pv_set_info = (VOID*)&e_aud_bypass_mode;
    t_op_info.u.t_misc_set_info.z_size = sizeof(UINT32);
    t_op_info.u.t_misc_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                DRVT_CUST_DRV,
                DRV_CUST_COMP_ID,
                FALSE,
                ANY_PORT_NUM,
                0,
                &t_op_info,
                sizeof(DRV_CUST_OPERATION_INFO_T)
                );
#endif
    MENU_LOG_ON_FAIL(i4_ret);
    }

/*----------------------------------------------------------------------------
 * Name: _get_dmix_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_dmix_idx(VOID)
{
    UINT16 ui2_idx;
    SCC_AUD_DOWNMIX_MODE_T e_dmix = SCC_AUD_DOWNMIX_MODE_OFF;

    a_cfg_get_dmix_mode(&e_dmix);

    switch(e_dmix)
    {
    case SCC_AUD_DOWNMIX_MODE_OFF:
        ui2_idx = 0;
        break;
    case SCC_AUD_DOWNMIX_MODE_LT_RT:
        ui2_idx = 1;
        break;
    case SCC_AUD_DOWNMIX_MODE_STEREO:
        ui2_idx = 2;
        break;
    default:
        DBG_ERROR(("<MENU>Unknown dolby dowmmix mode\r\n"));
        ui2_idx = 0;
    }

    return ui2_idx;
}

/*----------------------------------------------------------------------------
 * Name: _get_aud_bypass_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_aud_bypass_mode_idx(VOID)
{
    return ui2_aud_bypass_mode_idx;
}

/* Auto Gain Control */
/*----------------------------------------------------------------------------
 * Name: _set_agc_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_agc_idx(UINT16 ui2_idx)
{
    BOOL b_enable;

    b_enable = (ui2_idx == 0 ? FALSE : TRUE);

    a_cfg_set_agc(b_enable);

    a_cfg_update_agc();
}

/*----------------------------------------------------------------------------
 * Name: _get_agc_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_agc_idx(VOID)
{
    BOOL   b_enable;

    a_cfg_get_agc(&b_enable);

    return (UINT16)(b_enable ? 1 : 0);
}

/*----------------------------------------------------------------------------
 * Name: _set_block_unrated_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
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
                       b_tv_bu);    /* Don't affect TV None setting */

    a_cfg_unlock();
}

/*----------------------------------------------------------------------------
 * Name: _get_block_unrated_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_block_unrated_idx(VOID)
{
    BOOL    b_block;

    a_cfg_get_vchip_unrated(&b_block);

    return (UINT16)(b_block ? 1 : 0);
}

/*----------------------------------------------------------------------------
 * Name: _set_rating_enable_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
extern UINT8 a_get_pwd_to_unlock_state(VOID);
extern VOID _set_rating_enable_idx(UINT16 ui2_idx)
{
    #ifdef APP_NAV_PIP_VCHIP_SOL
    a_cfg_set_rating_enabled(ui2_idx == 0 ? APP_CFG_RATING_ENABLED_OFF : APP_CFG_RATING_ENABLED_ON);
    c_svctx_unblock_svc(menu_get_crnt_svctx(), FALSE);
        /* Exit PIP/POP. */
        if (ui2_idx == 1)
        {
            TV_MODE_T e_mode;

            a_tv_get_mode (&e_mode);
            if (e_mode != TV_MODE_TYPE_NORMAL)
            {
                a_tv_set_mode(TV_MODE_TYPE_NORMAL);
                c_thread_delay(100);//Henry Wang - 11/6
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));//Henry Wang - 11/6
            }
        }
    #else
       a_cfg_set_rating_enabled(ui2_idx == 0 ? FALSE : TRUE);
       menu_pm_repaint();

    #endif
}

/*----------------------------------------------------------------------------
 * Name: _get_rating_enable_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_rating_enable_idx(VOID)
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

/*----------------------------------------------------------------------------
 * Name: _get_rating_enable_text
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _get_rating_enable_text(
    UINT16    ui2_idx,   /* in */
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len)     /* in, len of w2s_str */
{
    UINT8               ui1_enabled;

    if(w2s_str == NULL)
    {
        return;
    }

    if (menu_page_is_in_list_subpage_state())
    {
        DBG_INFO(("<LOCK> %s,%d\n\r",__FILE__,__LINE__));
        if (ui2_idx == 0)
        {
            c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_OFF), (UINT32)z_len - 1);
        }
        else
        {
            c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_ON), (UINT32)z_len - 1);
        }
        w2s_str[z_len - 1] = 0;

        return;
    }

# if  0
    UINT8               ui1_val = RATING_ENABLED_STATUS_ON;
    SIZE_T              z_size = ICL_RECID_RATING_ENABLED_STATUS_SIZE;

    a_icl_get(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
            &ui1_val, &z_size);

    c_memset(w2s_str, 0x0, z_len * sizeof(UTF16_T));

    if (ui1_val == RATING_ENABLED_STATUS_OFF)
    {
        c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_OFF), (UINT32)z_len - 1);
    }
    else
    {
        a_cfg_get_rating_enabled(&ui1_enabled);
        if (ui1_enabled == APP_CFG_RATING_ENABLED_OFF)
        {
            c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_OFF), (UINT32)z_len - 1);
        }
        else
        {
            c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_ON), (UINT32)z_len - 1);
        }
    }
# endif


        a_cfg_get_rating_enabled(&ui1_enabled);
        if (ui1_enabled == APP_CFG_RATING_ENABLED_OFF)
        {
             c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_OFF), (UINT32)z_len - 1);
        }
        else
        {
                if (a_get_pwd_to_unlock_state() == TRUE)
                {
                    c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_OFF), (UINT32)z_len - 1);
                }
                else
                {
                    c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_ON), (UINT32)z_len - 1);
                }
        }

#if 0
    a_icl_get(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
            &ui1_val, &z_size);

    c_memset(w2s_str, 0x0, z_len * sizeof(UTF16_T));

    if (ui1_val == RATING_ENABLED_STATUS_OFF)
    {
        c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_ON), (UINT32)z_len - 1);
    }
    else
    {
            c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_OFF), (UINT32)z_len - 1);
    }
#endif

    w2s_str[z_len - 1] = 0;

    return;
}
/*----------------------------------------------------------------------------
 * Name: _set_dpms_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_dpms_idx(UINT16 ui2_idx)
{
    a_cfg_set_dpms(ui2_idx == 0 ? FALSE : TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _get_dpms_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_dpms_idx(VOID)
{
    ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    BOOL    b_dpms = FALSE;

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    a_cfg_get_dpms(&b_dpms);

    if (ACFG_RETAIL_MODE_NORMAL==t_retail_mode)
    {
        return 0;
    }
    else
    {
        return (UINT16)(b_dpms ? 1 : 0);
    }
}

/*----------------------------------------------------------------------------
 * Name: _set_scrn_saver_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_scrn_saver_idx(UINT16 ui2_idx)
{
    a_cfg_custom_set_scrn_saver_time(ui2_idx);
}

/*----------------------------------------------------------------------------
 * Name: _get_scrn_saver_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_scrn_saver_idx(VOID)
{
    UINT16    ui2_idx = 0;

    a_cfg_custom_get_scrn_saver_time(&ui2_idx);

    return ui2_idx;
}

#ifdef APP_NAV_FLICKER_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_flicker_pattern_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_flicker_pattern_idx(UINT16 ui2_idx)
{
    if (ui2_idx == 1)
    {
        a_nav_flicker_toggle_pattern ();
    }
}
/*----------------------------------------------------------------------------
 * Name: _get_flicker_pattern_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_flicker_pattern_idx(VOID)
{
    return 0;
}
#endif

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _set_tshift_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_tshift_mode_idx(UINT16 ui2_idx)
{
    a_cfg_set_tshift_mode((APP_CFG_TSHIFT_MODE_T)ui2_idx);
}
/*----------------------------------------------------------------------------
 * Name: _get_tshift_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_tshift_mode_idx(VOID)
{
    APP_CFG_TSHIFT_MODE_T e_mode = APP_CFG_TSHIFT_MODE_OFF;

    a_cfg_get_tshift_mode(&e_mode);

    return (UINT16)e_mode;
}
#endif /* APP_NAV_REC_TSHIFT_SUPPORT */

/*----------------------------------------------------------------------------
 * Name: _set_burning_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _set_burning_mode_idx(UINT16 ui2_idx)
{
    UINT8   ui1_fac_mode = 0;

    a_cfg_get_factory_mode(&ui1_fac_mode);

    if(ui2_idx == 1)
    {
        ui1_fac_mode = (UINT8)(ui1_fac_mode | APP_CFG_FAC_MODE_BURNING_MASK);
    }
    else
    {
        ui1_fac_mode = (UINT8)(ui1_fac_mode & (~APP_CFG_FAC_MODE_BURNING_MASK));
    }

    a_cfg_set_factory_mode(ui1_fac_mode);

    a_cfg_update_factory_mode();

    a_cfg_store();
}

/*----------------------------------------------------------------------------
 * Name: _get_burning_mode_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_burning_mode_idx(VOID)
{
    UINT8   ui1_fac_mode = 0;

    a_cfg_get_factory_mode(&ui1_fac_mode);

    return (UINT16)((ui1_fac_mode & APP_CFG_FAC_MODE_BURNING_MASK) == 0 ? 0 : 1);
}


/*---------------------------------------------------------------------------*/
/*                             PIP/POP                                       */
/*---------------------------------------------------------------------------*/
#if defined(APP_PIP_POP_CTRL) || defined(APP_PIP_SETTINGS_IN_MENU)
/* PIP Mode */
static VOID _set_pip_mode_idx(UINT16 ui2_idx)
{
    TV_MODE_T   e_tv_mode;

    switch(ui2_idx)
    {
    case 0:
        e_tv_mode = TV_MODE_TYPE_NORMAL;
        break;
    case 1:
        e_tv_mode = TV_MODE_TYPE_PIP;
        break;
    case 2:
        e_tv_mode = TV_MODE_TYPE_POP;
        break;
    default:
        e_tv_mode = TV_MODE_TYPE_NORMAL;
        break;
    }

    a_tv_set_mode(e_tv_mode);
}

static UINT16 _get_pip_mode_idx(VOID)
{
    TV_MODE_T   e_tv_mode = TV_MODE_TYPE_NORMAL;;
    a_tv_get_mode(&e_tv_mode);

    switch(e_tv_mode)
    {
    case TV_MODE_TYPE_NORMAL:
        return 0;
    case TV_MODE_TYPE_PIP:
        return 1;
    case TV_MODE_TYPE_POP:
        return 2;
    default:
        return 0;
    }
}
#endif

#ifdef APP_PIP_POP_CTRL
/* PIP Source */
static VOID _set_pip_src_ex_idx(UINT16 ui2_idx)
{
    TV_WIN_ID_T t_win_id;

    if(ui2_idx == 1)
    {
         t_win_id = TV_WIN_ID_SUB;
    }
    else
    {
         t_win_id = TV_WIN_ID_MAIN;
    }
    a_pop_set_osd_audio_focus(t_win_id);
}

static UINT16 _get_pip_src_ex_idx(VOID)
{
    TV_WIN_ID_T t_win_id;
    UINT16      ui2_idx;

    a_pop_get_audio_focus_id(&t_win_id);
    if(t_win_id == TV_WIN_ID_SUB)
    {
        ui2_idx = 1;
    }
    else
    {
        ui2_idx = 0;
    }
    return (ui2_idx);
}

/* PIP Pos */
static UINT8 _get_pip_pos_idx_by_id(TV_PIP_SUB_POSITION_T e_pos_id)
{
    TV_PIP_SUB_POSITION_T   e_pos_id_temp;
    UINT8                   ui1_idx;
    UINT8                   ui1_num_recs;

    ui1_num_recs = a_tv_get_num_of_pip_sub_position();
    for(ui1_idx = 0; ui1_idx < ui1_num_recs; ui1_idx++)
    {
        a_tv_get_pip_sub_position_id_by_idx(ui1_idx, &e_pos_id_temp);
        if(e_pos_id == e_pos_id_temp)
        {
            break;
        }
    }
    if(ui1_idx == ui1_num_recs)
    {
        ui1_idx = 0;
    }
    return ui1_idx;
}

static VOID _set_pip_pos_ex_idx(UINT16 ui2_idx)
{
    TV_PIP_SUB_POSITION_T   e_pos_id;

    switch(ui2_idx)
    {
        case 0:
            ui2_idx = 2;
            break;

        case 1:
            ui2_idx = 1;
            break;

        case 2:
            ui2_idx = 3;
            break;

        case 3:
        default:
            ui2_idx = 0;
            break;

    }
    a_tv_get_pip_sub_position_id_by_idx(ui2_idx, &e_pos_id);
    a_tv_set_pip_sub_position(e_pos_id);
}

static UINT16 _get_pip_pos_ex_idx(VOID)
{
    UINT16 ui2_idx;
    TV_PIP_SUB_POSITION_T   e_pos_id;
    a_tv_get_pip_sub_position(&e_pos_id);
    ui2_idx = _get_pip_pos_idx_by_id(e_pos_id);
    switch(ui2_idx)
    {
        case 0:
        ui2_idx = 3;
        break;

        case 1:
        ui2_idx = 1;
        break;

        case 2:
        ui2_idx = 0;
        break;

        case 3:
        ui2_idx = 2;
        break;

        default:
        ui2_idx = 0;
        break;
    }
    return ui2_idx;

}

/* PIP Size */
static UINT8 _get_pip_size_idx_by_id(TV_PIP_SUB_POSITION_T e_size_id)
{
    TV_PIP_SUB_POSITION_T   e_size_id_temp;
    UINT8                   ui1_idx;
    UINT8                   ui1_num_recs;

    ui1_num_recs = a_tv_get_num_of_pip_sub_size();
    for(ui1_idx=0; ui1_idx < ui1_num_recs; ui1_idx++)
    {
        a_tv_get_pip_sub_size_id_by_idx(ui1_idx, &e_size_id_temp);
        if(e_size_id == e_size_id_temp)
        {
            break;
        }
    }
    if(ui1_idx == ui1_num_recs)
    {
        ui1_idx = 0;
    }

    return ui1_idx;
}

static VOID _set_pip_size_ex_idx(UINT16 ui2_idx)
{
    TV_PIP_SUB_POSITION_T   e_size_id;
    a_tv_get_pip_sub_size_id_by_idx(ui2_idx, &e_size_id);
    a_tv_set_pip_sub_size(e_size_id);
}

static UINT16 _get_pip_size_ex_idx(VOID)
{
    TV_PIP_SUB_POSITION_T   e_size_id;
    a_tv_get_pip_sub_size(&e_size_id);
    a_tv_set_pip_sub_size(e_size_id);
    return _get_pip_size_idx_by_id(e_size_id);
}
#endif

#ifdef APP_PIP_SETTINGS_IN_MENU
/* PIP Source */
static UINT8 _get_isl_idx_by_id(UINT8   ui1_id)
{
    ISL_REC_T   t_isl_rec;
    UINT8       ui1_idx;
    UINT8       ui1_num_recs;

    a_isl_get_num_rec(&ui1_num_recs);
    for(ui1_idx=0; ui1_idx < ui1_num_recs; ui1_idx++)
    {
        a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);
        if(ui1_id == t_isl_rec.ui1_id)
        {
            break;
        }
    }
    if(ui1_idx == ui1_num_recs)
    {
        ui1_idx = 0;
    }

    return ui1_idx;
}

static VOID _set_pip_src_idx(UINT16 ui2_idx)
{
    ISL_REC_T   t_isl_rec;

    a_isl_get_rec_by_idx((UINT8)ui2_idx, &t_isl_rec);

    a_tv_change_input_src_by_rec(t_g_menu_common.h_svctx_sub,
                                 SVCTX_STRM_MODE_AS_LAST,
                                 &t_isl_rec,
                                 NULL);
}

static UINT16 _get_pip_src_idx(VOID)
{
    ISL_REC_T   t_isl_rec;

    a_tv_get_isl_rec_by_snk_name(SN_PRES_SUB_DISPLAY, &t_isl_rec);
    return _get_isl_idx_by_id(t_isl_rec.ui1_id);
}

static UINT16 _prev_pip_src_idx(VOID)
{
    BOOL    b_same_group;
    UINT8   ui1_i;
    UINT8   ui1_num_rec;
    ISL_REC_T   t_isl_rec_main;
    ISL_REC_T   t_isl_rec_sub;
    ISL_REC_T   t_isl_rec_next;

    /* Get current record */
    a_isl_get_num_rec(&ui1_num_rec);
    a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec_main);
    a_tv_get_isl_rec_by_snk_name(SN_PRES_SUB_DISPLAY, &t_isl_rec_sub);

    /* iterate all spdif in records */
    for(ui1_i = (t_isl_rec_sub.ui1_id + ui1_num_rec - 1) % ui1_num_rec;
        ui1_i != t_isl_rec_sub.ui1_id;
        ui1_i = (ui1_i + ui1_num_rec - 1) % ui1_num_rec)
    {
        a_isl_get_rec_by_idx(ui1_i, &t_isl_rec_next);

        a_isl_is_same_group(&t_isl_rec_main, &t_isl_rec_next, &b_same_group);
        if(!b_same_group)
        {
            break;
        }
    }

    a_tv_change_input_src(t_g_menu_common.h_svctx_sub,
                          SVCTX_STRM_MODE_AS_LAST,
                          (UINT8)ui1_i,
                          NULL);
    return ui1_i;
}

static UINT16 _next_pip_src_idx(VOID)
{
    BOOL    b_same_group;
    UINT8   ui1_i;
    UINT8   ui1_num_rec;
    ISL_REC_T   t_isl_rec_main;
    ISL_REC_T   t_isl_rec_sub;
    ISL_REC_T   t_isl_rec_next;

    /* Get current record */
    a_isl_get_num_rec(&ui1_num_rec);
    a_tv_get_isl_rec_by_snk_name(SN_PRES_MAIN_DISPLAY, &t_isl_rec_main);
    a_tv_get_isl_rec_by_snk_name(SN_PRES_SUB_DISPLAY, &t_isl_rec_sub);

    /* iterate all spdif in records */
    for(ui1_i = (t_isl_rec_sub.ui1_id + 1) % ui1_num_rec;
        ui1_i != t_isl_rec_sub.ui1_id;
        ui1_i = (ui1_i + 1) % ui1_num_rec)
    {
        a_isl_get_rec_by_idx(ui1_i, &t_isl_rec_next);

        a_isl_is_same_group(&t_isl_rec_main, &t_isl_rec_next, &b_same_group);
        if(!b_same_group)
        {
            break;
        }
    }

    a_tv_change_input_src(t_g_menu_common.h_svctx_sub,
                          SVCTX_STRM_MODE_AS_LAST,
                          (UINT8)ui1_i,
                          NULL);

    return ui1_i;
}

static VOID _get_pip_src_text(
    UINT16    ui2_idx,   /* in */
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len)     /* in, len of w2s_str */
{
    UINT8       ui1_isl_id = (UINT8)ui2_idx;
    ISL_REC_T   t_isl_rec;

    a_isl_get_rec_by_id(ui1_isl_id,
                        &t_isl_rec);

    c_uc_w2s_strncpy(w2s_str,
                     a_isl_get_display_name(&t_isl_rec),
                     (UINT32)z_len - 1);

    w2s_str[z_len - 1] = 0;
}

static VOID _set_pip_pos_idx(UINT16 ui2_idx)
{
    TV_PIP_SUB_POSITION_T   e_pos_id;
    a_tv_get_pip_sub_position_id_by_idx(ui2_idx, &e_pos_id);
    a_tv_set_pip_sub_position(e_pos_id);
}

static UINT16 _get_pip_pos_idx(VOID)
{
    TV_PIP_SUB_POSITION_T   e_pos_id;
    a_tv_get_pip_sub_position(&e_pos_id);
    return _get_pip_pos_idx_by_id(e_pos_id);
}

static UINT16 _prev_pip_pos_idx(VOID)
{
    TV_PIP_SUB_POSITION_T   e_pos_id;
    a_tv_get_pip_sub_position(&e_pos_id);
    a_tv_iterate_pip_sub_position_id(e_pos_id,
                                     TV_ITERATE_DIR_PREV,
                                     &e_pos_id);
    a_tv_set_pip_sub_position(e_pos_id);
    return _get_pip_pos_idx_by_id(e_pos_id);

}

static UINT16 _next_pip_pos_idx(VOID)
{
    TV_PIP_SUB_POSITION_T   e_pos_id;
    a_tv_get_pip_sub_position(&e_pos_id);
    a_tv_iterate_pip_sub_position_id(e_pos_id,
                                     TV_ITERATE_DIR_NEXT,
                                     &e_pos_id);
    a_tv_set_pip_sub_position(e_pos_id);
    return _get_pip_pos_idx_by_id(e_pos_id);
}

static VOID _get_pip_pos_text(
    UINT16    ui2_idx,   /* in */
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len)     /* in, len of w2s_str */
{
    TV_PIP_SUB_POSITION_T   e_pos_id;
    UTF16_T*                w2s_disp_name;

    a_tv_get_pip_sub_position_id_by_idx((UINT8)ui2_idx, &e_pos_id);

    w2s_disp_name = a_tv_get_pip_sub_position_display_name(e_pos_id);

    if(w2s_disp_name != 0)
    {
        c_uc_w2s_strncpy(w2s_str,
                         w2s_disp_name,
                         (UINT32)z_len - 1);
        w2s_str[z_len - 1] = 0;
    }
    else
    {
        w2s_str[0] = 0;
    }
}

static VOID _set_pip_size_idx(UINT16 ui2_idx)
{
    TV_PIP_SUB_POSITION_T   e_size_id;
    a_tv_get_pip_sub_size_id_by_idx(ui2_idx, &e_size_id);
    a_tv_set_pip_sub_size(e_size_id);
}

static UINT16 _get_pip_size_idx(VOID)
{
    TV_PIP_SUB_POSITION_T   e_size_id;
    a_tv_get_pip_sub_size(&e_size_id);
    a_tv_set_pip_sub_size(e_size_id);
    return _get_pip_size_idx_by_id(e_size_id);
}

static UINT16 _prev_pip_size_idx(VOID)
{
    TV_PIP_SUB_POSITION_T   e_size_id;
    a_tv_get_pip_sub_size(&e_size_id);
    a_tv_iterate_pip_sub_size_id(e_size_id,
                                     TV_ITERATE_DIR_PREV,
                                     &e_size_id);
    return _get_pip_size_idx_by_id(e_size_id);

}

static UINT16 _next_pip_size_idx(VOID)
{
    TV_PIP_SUB_POSITION_T   e_size_id;
    a_tv_get_pip_sub_size(&e_size_id);
    a_tv_iterate_pip_sub_size_id(e_size_id,
                                     TV_ITERATE_DIR_NEXT,
                                     &e_size_id);
    a_tv_set_pip_sub_size(e_size_id);
    return _get_pip_size_idx_by_id(e_size_id);
}

static VOID _get_pip_size_text(
    UINT16    ui2_idx,   /* in */
    UTF16_T*  w2s_str,   /* out */
    SIZE_T    z_len)     /* in, len of w2s_str */
{
    TV_PIP_SUB_POSITION_T   e_size_id;
    UTF16_T*                w2s_disp_name;

    a_tv_get_pip_sub_size_id_by_idx((UINT8)ui2_idx, &e_size_id);

    w2s_disp_name = a_tv_get_pip_sub_size_display_name(e_size_id);

    if(w2s_disp_name != 0)
    {
        c_uc_w2s_strncpy(w2s_str,
                         w2s_disp_name,
                         (UINT32)z_len - 1);
        w2s_str[z_len - 1] = 0;
    }
    else
    {
        w2s_str[0] = 0;
    }
}
#endif /* APP_PIP_SETTINGS_IN_MENU */

/*Network Configuration*/
#ifdef APP_NETWORK_SUPPORT
static VOID _set_net_connection_idx(UINT16 ui2_idx)
{
    BOOL b_enable = ui2_idx>0? TRUE:FALSE;

    if(b_enable)
    {
        a_nw_enable_network_connection();
    }
    else
    {
        a_nw_disable_network_connection();
    }
    return;
}
static UINT16 _get_net_connection_idx(VOID)
{
    BOOL b_enable = FALSE;

    a_cfg_get_network_enable(&b_enable);

    return (UINT16)b_enable;
}
static VOID _set_dlna_setting_idx(UINT16 ui2_idx)
{
#ifdef APP_NET_DLNA_SUPPORT
    BOOL b_enable = ui2_idx>0? TRUE:FALSE;

    if(b_enable)
    {
        a_nw_enable_dlna();
    }
    else
    {
        a_nw_disable_dlna();
    }
#endif

    return;
}
static UINT16 _get_dlna_setting_idx(VOID)
{
    BOOL b_enable = FALSE;

#ifdef APP_NET_DLNA_SUPPORT
    a_cfg_get_DLNA_enable(&b_enable);
#endif

    return (UINT16)b_enable;
}

#ifdef APP_DMR_SUPPORT
static VOID _set_dlna_dmr_setting_idx(UINT16 ui2_idx)
{
    BOOL b_enable = (ui2_idx > 0) ? TRUE : FALSE;

    if (b_enable)
    {
        a_nw_enable_dlna_dmr();
    }
    else
    {
        a_nw_disable_dlna_dmr();
    }

    return;
}

static UINT16 _get_dlna_dmr_setting_idx(VOID)
{
    BOOL b_enable = FALSE;

    a_cfg_get_DLNA_DMR_enable(&b_enable);

    return (UINT16)b_enable;
}

static VOID _get_dlna_dmr_setting_text(
                    UINT16                          ui2_idx,   /* in  */
                    UTF16_T*                        w2s_str,   /* out */
                    SIZE_T                          z_len      /* in  */
                    )
{
    BOOL      b_net_connection = FALSE;
    BOOL      b_dlna_dmr_setting = FALSE;

    a_cfg_get_network_enable(&b_net_connection);
    a_cfg_get_DLNA_DMR_enable(&b_dlna_dmr_setting);

    if (b_net_connection)
    {
        if (b_dlna_dmr_setting)
        {
            c_uc_w2s_strcpy (w2s_str, MENU_TEXT(MLM_MENU_KEY_ON));
            return ;
        }
        else
        {
            c_uc_w2s_strcpy (w2s_str, MENU_TEXT(MLM_MENU_KEY_OFF));
            return ;
        }
    }

    c_uc_w2s_strcpy (w2s_str, MENU_TEXT(MLM_MENU_KEY_OFF));

    return ;
}
#endif /* APP_DMR_SUPPORT */
#endif /* APP_NETWORK_SUPPORT */

/**
 * @brief  get the local dimming idx or DCR idx.
 * @detail if the local dimming is supported, then it will read the idx from EEPROM.
 *         or it will get the DCR idx from EEPROM.
 *         since _set_local_dimming_idx will set the data into EEPROM
 *         immediately (in theorem), so we discard a_cfg_custom_plf_opt_get_dcr_setting
 */
static UINT16
_get_local_dimming_idx (VOID)
{
    UINT16  ui2_idx = 0;
    BOOL b_support_LD = a_cfg_cust_get_support_local_dimming();
    INT16 i2_val = 0;
    UINT8 ui1_tmp_val = 0;

    ui1_tmp_val = a_smart_dim_get_assume_val();

    a_smart_dim_set_assume_val(SMART_DIM_AS_MENU_SETTING);

    if(b_support_LD)
    {
        a_cfg_custom_get_dimming_idx(&ui2_idx);

        DBG_INFO( ("%s:%d: got local dimming idx: 0x%02x\n",
                    __FUNCTION__, __LINE__, ui2_idx));

        a_smart_dim_set_assume_val(ui1_tmp_val);

        return ui2_idx;
    }
    else // For Backlight_Ctrl
    {
        if( FALSE == a_cfg_cust_BacklightCtrl_CheckIfCanTurnOn() )
        {
            i2_val = 0;
        }
        else
        {
            /* get the val from the EEPROM acfg partition */
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_val);
        }

    #ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
        a_cfg_custom_plf_opt_get_dcr_setting();
    #endif

        a_smart_dim_set_assume_val(ui1_tmp_val);

        return (UINT16)(i2_val);
    }

}

UINT16 menu_get_local_dimming_idx(VOID)
{
    return _get_local_dimming_idx();
}

/**
 * @brief  set the local dimming idx or DCR idx.
 * @detail if the local dimming is supported, then it simply set the idx to EEPROM,
 *         else it will change to setup DCR in mem and EEPROM.
 */
static VOID
_set_local_dimming_idx (UINT16 ui2_idx)
{
    /* for acfg customization ,it should use a_cfg_av_set/a_cfg_av_update  ,make it run to acfg_cust_odm_video_update */
    BOOL b_support = a_cfg_cust_get_support_local_dimming();
    UINT8 ui1_tmp_val = 0;
    UINT16 ui2_pre_idx = _get_local_dimming_idx();

    ui1_tmp_val = a_smart_dim_get_assume_val();

    ACFG_DEBUG_BACKLIGHT(
        DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL]{%s: %d} ui2_idx:%d\n", __FUNCTION__, __LINE__, ui2_idx ));
    );

    DBG_INFO(("[MENU][PIC][%s %d] b_support = %d,ui2_idx = %d\n",__FUNCTION__,__LINE__,b_support,ui2_idx));
    if(b_support)
    {
        DBG_INFO( ("%s:%d: set APP_CFG_RECID_VID_CUSTOM_DIMMING to 0x%02x\n",
                    __FUNCTION__, __LINE__, ui2_idx));

        /* set the value to the EEPROM acfg partition */
        a_cfg_custom_set_dimming_idx((INT16)ui2_idx);
        if (ui1_tmp_val == SMART_DIM_AS_MENU_SETTING)
        {
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
#ifdef NEVER
            VIZIO_EXTREME_BLACK_ENGINE_D_SET(ui2_idx);
#endif /* NEVER */
        }
    }
    else
    {
        /*
         * if we have dcr support, the the DCR_ID val will be: 0: off, 1: DCR, 2: OPC
         * else, it will be 0: off, 1: OPC
         */

        DBG_INFO(("%s:%d: set APP_CFG_RECID_VID_CUSTOM_DCR to 0x%02x\n",
                    __FUNCTION__, __LINE__, ui2_idx));
        /* set the value to the EEPROM acfg partition */
        a_cfg_av_set (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), ui2_idx);

        if (ui1_tmp_val == SMART_DIM_AS_MENU_SETTING)
        {
            ACFG_DEBUG_BACKLIGHT(
                DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL]{%s: %d} Call a_cfg_av_update(APP_CFG_RECID_VID_CUSTOM_DCR)\n", __FUNCTION__, __LINE__ ));
            );

            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));
        }

        /* set the val to mem: _u1DCRSetting@Vizio_d_custom.c */
#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
        a_cfg_custom_plf_opt_set_dcr_setting(ui2_idx);
#endif

    }

    if (ui2_pre_idx != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
        a_cfg_cust_set_local_dimming_value((UINT8)ui2_idx);
    }
}


VOID menu_set_local_dimming_idx (UINT16 ui2_idx)
{
    _set_local_dimming_idx(ui2_idx);
}


#ifdef APP_LED_LOGO_CTRL
static VOID _set_led_logo_ctrl_idx(UINT16 ui2_idx)
{
    a_cfg_custom_set_led_logo_ctrl((UINT8)ui2_idx);
}

static UINT16 _get_led_logo_ctrl_idx(VOID)
{
    UINT16 ui2_idx = 0;

    ui2_idx = a_cfg_custom_get_led_logo_ctrl();

    return ui2_idx;
}
#endif
static VOID _set_usb_power_ctrl_idx(UINT16 ui2_idx)
{
    a_cfg_custom_set_usb_power_ctrl((UINT8)ui2_idx);
}

static UINT16 _get_usb_power_ctrl_idx(VOID)
{
    UINT16 ui2_idx = 0;

    ui2_idx = a_cfg_custom_get_usb_power_ctrl();

    return ui2_idx;
}

static VOID _set_osd_zoom_mode_idx(UINT16 ui2_idx)
{
    UINT8   ui1_zoom_switch = APP_CFG_CUST_ZOOM_MODE_OFF;

    ui1_zoom_switch = (0 == ui2_idx) ? APP_CFG_CUST_ZOOM_MODE_OFF : APP_CFG_CUST_ZOOM_MODE_ON;

    a_cfg_cust_set_zoom_mode(ui1_zoom_switch);
    rest_event_notify("app/zoom/enabled", ui1_zoom_switch, "");
    #ifdef VIZIO_FUSION_SUPPORT
    c_wgl_enable_zoom((ui1_zoom_switch == APP_CFG_CUST_ZOOM_MODE_ON) ? TRUE : FALSE);
    #endif
    return;
}

static UINT16 _get_osd_zoom_mode_idx(VOID)
{
    UINT8              ui1_idx = 0;

    //a_cfg_cust_get_zoom_mode(&ui1_idx);
    a_cfg_cust_get_zoom_status(&ui1_idx);
    return (UINT16)ui1_idx;
}

static VOID _set_vid_des_mode_idx(UINT16 ui2_idx)
{

    ISO_639_LANG_T  s639_lang = {0};
    UINT16          ui2_tmp_idx = 0;

    if (ui2_idx == TRUE)
    {
        ui2_tmp_idx = 2; /* change to Spanish */
    }
    else
    {
        ui2_tmp_idx = 0; /* to English/change to english */
    }

    mlm_nav_langidx_to_s639(ui2_tmp_idx, s639_lang);

    a_cfg_set_aud_lang(s639_lang);

    a_cfg_custom_set_video_description_status(ui2_idx);
}


static UINT16  _get_vid_des_mode_idx(VOID)
{

    INT32           i4_ret;
    ISO_639_LANG_T  s639_lang = {0};
    UINT16          ui2_tmp_idx = 0;

    i4_ret = a_cfg_get_aud_lang(s639_lang);
   if(i4_ret != APP_CFGR_OK)
   {
       DBG_ERROR(("Get aud lang fail\n"));
       return -1;
   }
   ui2_tmp_idx = mlm_nav_s639_to_langidx(s639_lang);

   if (ui2_tmp_idx == 2)
   {
       /* English or French*/
       return TRUE;
   }
   else if (ui2_tmp_idx == 0 || ui2_tmp_idx == 1)
   {
      /* Spanish */
       return FALSE;
   }
   return -1;

}

static UINT16 _get_local_dimming_mlm_key(VOID)
{
    //UINT16  ui2_i = 0;
    UINT16  ui2_ret = MLM_MENU_KEY_LOCAL_DEMMING_E_SERIES;
    CHAR    s_model_name[16+1] = {0};
    //static CHAR ac_model_name[][16+1] = MODEL_NAME_WITH_LD;

    a_cfg_custom_get_model_name(s_model_name);

    ui2_ret = MLM_MENU_KEY_LOCAL_DEMMING_ACTIVE_FULL_ARRAY;

    return ui2_ret;
}

#ifdef APP_TTS_SUPPORT
static VOID _set_aud_tts_speed_idx(UINT16 ui2_idx)
{
    /*convert UINT16 to UNIT8*/
    UINT8   ui1_tts_speed = APP_CFG_TTS_SPEED_NORMAL;

    /*convert UINT16 to UNIT8*/
    if (0 == ui2_idx)           //UI Slow
    {
        ui1_tts_speed = APP_CFG_TTS_SPEED_SLOW;
    }
    else if (1 == ui2_idx)      //UI Normal
    {
        ui1_tts_speed = APP_CFG_TTS_SPEED_NORMAL;
    }
    else if (2 == ui2_idx)      //UI Fast
    {
        ui1_tts_speed = APP_CFG_TTS_SPEED_FAST;
    }
    else
    {
        ui1_tts_speed = APP_CFG_TTS_SPEED_NORMAL;
    }

    a_cfg_set_tts_speed((UINT8)ui1_tts_speed);
    a_cfg_update_tts_speed();
}

static UINT16 _get_aud_tts_speed_idx(VOID)
{
    UINT8              ui1_idx = 0;
    a_cfg_get_tts_speed(&ui1_idx);

    /* convert tts speed to UI index */
    if (APP_CFG_TTS_SPEED_SLOW == ui1_idx)           //UI Slow
    {
        ui1_idx = 0;
    }
    else if (APP_CFG_TTS_SPEED_NORMAL == ui1_idx)      //UI Normal
    {
        ui1_idx = 1;
    }
    else if (APP_CFG_TTS_SPEED_FAST == ui1_idx)      //UI Fast
    {
        ui1_idx = 2;
    }
    else
    {
        ui1_idx = 1;
    }

    return (UINT16)ui1_idx;
}
static VOID _set_aud_tts_switch_idx(UINT16 ui2_idx)
{

   a_cfg_set_tts_switch_status((UINT8)ui2_idx);
   a_cfg_update_tts_switch_status();

    rest_event_notify("app/tts/enabled", ((ui2_idx == 0) ? 0 : 1), "");
    a_registry_set_tts_state((ui2_idx == 0) ? REG_TTS_STATE_OFF : REG_TTS_STATE_ON);
}

static UINT16 _get_aud_tts_switch_idx(VOID)
{
    UINT8              ui1_idx = 0;
    a_cfg_get_tts_switch_status(&ui1_idx);
    return (UINT16)ui1_idx;
}
#endif
UINT16 power_on_index_to_device(UINT16 ui2_idx)
{
    ISL_REC_T t_isl_rec = {0};
    a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 0, &t_isl_rec);
    UINT16 hdmi_port_count = (UINT16)t_isl_rec.ui1_iid_count;
    UINT16 port_offset = MAX_HDMI_PORTS - hdmi_port_count;
    Enu_POWER_ON_INPUT input_device = ui2_idx;

    //If input device is after all the HDMI ports...
    if (input_device > E_POWER_ON_INP_HDMI1 + hdmi_port_count - 1)
    {
        input_device += port_offset;
    }
    return input_device;
}

VOID set_power_on_device_by_index(UINT16 ui2_idx)
{
    g_power_on_device = power_on_index_to_device(ui2_idx);

    FILE *fptr = fopen(POD_SYSTEM_PATH, "w");
    if (NULL != fptr)
    {
        fprintf(fptr, "%d", g_power_on_index);
        fclose(fptr);
    }
}

extern UINT16 get_power_on_input_idx(VOID)
{


    int readIndex;
    FILE *fptr = fopen(POD_SYSTEM_PATH, "r");
    if (NULL == fptr)
    {
        readIndex = 0;
    }
    else
    {
        fscanf(fptr, "%d", &readIndex);
        fclose(fptr);
    }
    g_power_on_index = readIndex;
    return g_power_on_index;
}

HANDLE_T h_Mtx = NULL_HANDLE;
static HANDLE_T init_power_on_input()
{
    INT32 i4_create_result = c_sema_create(&h_Mtx, X_SEMA_TYPE_MUTEX, X_SEMA_STATE_UNLOCK);
    if(i4_create_result != FMR_OK)
    {
        DBG_ERROR(("[MENU][POWERONINPUT] Can't create mutex\n"));
        return NULL_HANDLE;
    }
      
    return i4_create_result;
}

Enu_POWER_ON_INPUT get_power_on_device()
{
    if(h_Mtx == NULL_HANDLE)
    {
        DBG_ERROR(("[MENU][POWERONINPUT] Can't create mutex\n"));
    }
    
    INT32 i_lock_result = c_sema_lock(h_Mtx, X_SEMA_OPTION_WAIT);
    
    if(i_lock_result != OSR_OK)
    {
        DBG_LOG_PRINT(("[MENU][POWERONINPUT] {%s: %s: %d} (i2_val_min:%d, mutex lock failed. err=:%d)\n", __FILE__, __FUNCTION__,__LINE__, i_lock_result));
    }

    g_power_on_device = power_on_index_to_device(g_power_on_index);
    
    
    i_lock_result = c_sema_unlock(h_Mtx);


    if(i_lock_result != OSR_OK)
    {
        DBG_LOG_PRINT(("[MENU][POWERONINPUT] {%s: %s: %d} (i2_val_min:%d, mutex unlock failed. err=:%d)\n", __FILE__, __FUNCTION__,__LINE__, i_lock_result));
    }
   
    return g_power_on_device;
}

extern INT16 get_power_on_input_idx_count()
{
    //Determine how many HDMI ports there are
    ISL_REC_T t_isl_rec = {0};

    //Get first HDMI port
    a_isl_get_rec_by_dev_type(DEV_AVC_HDMI,0,&t_isl_rec);

    BOOL b_is_not_support_comp = a_nav_ipts_not_support_comp_source();
    UINT8 hdmi_port_count = t_isl_rec.ui1_iid_count;
    INT16 tmpCount = hdmi_port_count + E_POWER_ON_INP_NUM_DEVICES-4 - (b_is_not_support_comp ? 1 : 0);
    return tmpCount;
}



static INT32 set_power_on_input_idx(UINT16 ui2_idx)
{
    if(h_Mtx == NULL_HANDLE)
    {
        DBG_ERROR(("[MENU][POWERONINPUT] Can't create mutex\n"));
        return -1;
    }
    
    INT32 i_lock_result = c_sema_lock(h_Mtx, X_SEMA_OPTION_WAIT);
    
    if(i_lock_result != OSR_OK)
    {
        DBG_LOG_PRINT(("[MENU][POWERONINPUT] {%s: %s: %d} (i2_val_min:%d, mutex lock failed. err=:%d)\n", __FILE__, __FUNCTION__,__LINE__, i_lock_result));
    
        return -2;
    }

    g_power_on_index = ui2_idx;
    set_power_on_device_by_index(ui2_idx);
    
    i_lock_result = c_sema_unlock(h_Mtx);


    if(i_lock_result != OSR_OK)
    {
        DBG_LOG_PRINT(("[MENU][POWERONINPUT] {%s: %s: %d} (i2_val_min:%d, mutex unlock failed. err=:%d)\n", __FILE__, __FUNCTION__,__LINE__, i_lock_result));
        return -3;
    }
    
    return 0;
}

extern VOID set_power_on_input_idx_from_rest_api(UINT16 ui2_idx)
{
    set_power_on_input_idx(ui2_idx);
}


static VOID set_power_on_input_idx_from_menu(UINT16 ui2_idx)
{
    set_power_on_input_idx(ui2_idx);
}

extern VOID set_power_on_device_to_default(void)
{
	set_power_on_input_idx((UINT16)E_POWER_ON_INP_AUTOMATIC);
}
// Author : ys.hu
//Action : Packing _set_power_on_input_idx to inx_set_power_on_input.
VOID inx_set_power_on_input(UINT16 ui2_idx)
{
	g_power_on_index = ui2_idx;
	set_power_on_device_by_index(ui2_idx);
}

VOID menu_game_low_latency_toast(VOID)
{
    WDK_TOAST_T    t_toast          = {0};
    UTF16_T        w2s_tmp_str[512] = {0};
    UTF16_T        *pw2s_text       = NULL;

    DBG_LOG_PRINT(("%s() line %d  Enter\n", __FILE__, __LINE__ ));

    pw2s_text = MENU_TEXT(MLM_MENU_KEY_VID_GAME_LOW_LATENCY_WARING);
    c_uc_w2s_strcpy(w2s_tmp_str, pw2s_text);
    c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_WARNING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;
    t_toast.style.style_4.w2s_str = (VOID*)w2s_tmp_str;
    menu_send_string_to_nav_toast(&t_toast);
}

INT32 menu_common_picture_settings_init()
{
    INT32   i4_ret;
    INT16   i2_val_min;
    INT16   i2_val_max;

    /* Picture Mode */
    t_g_menu_common_item_vid_pic_mode.e_item_type                   = MENU_ITEM_TYPE_LIST;
    t_g_menu_common_item_vid_pic_mode.ui2_msgid_title               = MLM_MENU_KEY_VID_PIC_MODE_ITEM;
#ifdef NEVER
    if(a_cfg_cust_get_support_energy_start_by_mode_name())
    {
        t_g_menu_common_item_vid_pic_mode.ui2_msgid_desc  = MLM_MENU_KEY_TAB_HELP_PICTURE_MODE;
    }
    else
#endif /* NEVER */
    {
        t_g_menu_common_item_vid_pic_mode.ui2_msgid_desc  = MLM_MENU_KEY_TAB_HELP_PICTURE_MODE_NO_ENERGY_START;
    }

    t_g_menu_common_item_vid_pic_mode.u.t_list.ui2_elem_num         = (UINT16)14;//(MLM_MENU_KEY_VID_PIC_MODE_ITEM_COMPURER - MLM_MENU_KEY_VID_PIC_MODE_ITEM_STD+1);
    t_g_menu_common_item_vid_pic_mode.u.t_list.pf_set_idx           = _set_vid_pic_mode_idx;
    t_g_menu_common_item_vid_pic_mode.u.t_list.pf_get_idx           = _get_vid_pic_mode_idx;
    t_g_menu_common_item_vid_pic_mode.u.t_list.pf_get_text          = _get_vid_pic_mode_text;
    t_g_menu_common_item_vid_pic_mode.u.t_list.ui2_msgid_elem_first = 0;
    t_g_menu_common_item_vid_pic_mode.u.t_list.ui2_msgid_elem_last  = 0;


    /* Color Temperature */
    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP),
                                  &i2_val_min,
                                  &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    t_g_menu_common_item_vid_clr_tmp_mode.e_item_type                   = MENU_ITEM_TYPE_LIST;
    t_g_menu_common_item_vid_clr_tmp_mode.ui2_msgid_title               = MLM_MENU_KEY_VID_CLR_TEMP,
    t_g_menu_common_item_vid_clr_tmp_mode.ui2_msgid_desc                = MLM_MENU_KEY_HELP_SET_CLR_TMP;
    t_g_menu_common_item_vid_clr_tmp_mode.u.t_list.ui2_elem_num         = (UINT16)(i2_val_max+1);
    t_g_menu_common_item_vid_clr_tmp_mode.u.t_list.pf_set_idx           = _set_vid_clr_tmp_mode_idx;
    t_g_menu_common_item_vid_clr_tmp_mode.u.t_list.pf_get_idx           = _get_vid_clr_tmp_mode_idx;
    t_g_menu_common_item_vid_clr_tmp_mode.u.t_list.pf_get_text          = _get_vid_clr_tmp_text;
    t_g_menu_common_item_vid_clr_tmp_mode.u.t_list.ui2_msgid_elem_first = 0;
    t_g_menu_common_item_vid_clr_tmp_mode.u.t_list.ui2_msgid_elem_last  = 0;

    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_clear_action,
                                      MLM_MENU_KEY_VID_BLUR,
                                      MLM_MENU_KEY_CLEAR_ACTION_HELP_TEXT,
                                      MLM_MENU_KEY_VID_BLUR_OFF,
                                      MLM_MENU_KEY_VID_BLUR_ON,
                                      _set_vid_clear_action_idx,
                                      _get_vid_clear_action_idx);

    /* Brightness */
    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI),
                                  &i2_val_min,
                                  &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_bri,
                                       MLM_MENU_KEY_VID_BRI,
                                       MLM_MENU_KEY_HELP_TIP_PICTURE_BRI,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_bri_val,
                                       _get_vid_bri_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_bri.u.t_range.pf_incr = _incr_vid_bri;
    t_g_menu_common_item_vid_bri.u.t_range.pf_decr = _decr_vid_bri;
    t_g_menu_common_item_vid_bri.u.t_range.b_fast_mode = TRUE;
    /* Contrast */
    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT),
                                  &i2_val_min,
                                  &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_cnt,
                                       MLM_MENU_KEY_VID_CNT,
                                       MLM_MENU_KEY_HELP_TIP_PICTURE_CNT,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_cnt_val,
                                       _get_vid_cnt_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_cnt.u.t_range.pf_incr = _incr_vid_cnt;
    t_g_menu_common_item_vid_cnt.u.t_range.pf_decr = _decr_vid_cnt;
    t_g_menu_common_item_vid_cnt.u.t_range.b_fast_mode = TRUE;
    /* Saturation */
    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT),
                                  &i2_val_min,
                                  &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_sat,
                                       MLM_MENU_KEY_VID_SAT,
                                       MLM_MENU_KEY_TAB_HELP_PIC_CLR,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_sat_val,
                                       _get_vid_sat_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_sat.u.t_range.pf_incr = _incr_vid_sat;
    t_g_menu_common_item_vid_sat.u.t_range.pf_decr = _decr_vid_sat;
    t_g_menu_common_item_vid_sat.u.t_range.b_fast_mode = TRUE;
    /* HUE */
    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE),
                                  &i2_val_min,
                                  &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_hue,
                                       MLM_MENU_KEY_VID_HUE,
                                       MLM_MENU_KEY_TAB_HELP_PIC_TINT,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_hue_val,
                                       _get_vid_hue_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_hue.u.t_range.pf_incr = _incr_vid_hue;
    t_g_menu_common_item_vid_hue.u.t_range.pf_decr = _decr_vid_hue;
    t_g_menu_common_item_vid_hue.u.t_range.b_fast_mode = TRUE;
    /* Sharpness */
    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP),
                                  &i2_val_min,
                                  &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_shp,
                                       MLM_MENU_KEY_VID_SHP,
                                       MLM_MENU_KEY_HELP_TIP_PICTURE_SHP,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_shp_val,
                                       _get_vid_shp_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_shp.u.t_range.pf_incr = _incr_vid_shp;
    t_g_menu_common_item_vid_shp.u.t_range.pf_decr = _decr_vid_shp;
    t_g_menu_common_item_vid_shp.u.t_range.b_fast_mode = TRUE;

    /* Back Light */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    MENU_DEBUG_BACKLIGHT(DBG_LOG_PRINT(("[MENU][BACKLIGHT] {%s: %s: %d} (i2_val_min:%d, i2_val_max:%d)\n", __FILE__, __FUNCTION__,__LINE__, i2_val_min, (i2_val_max) )); );

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_back_light,
                                       MLM_MENU_KEY_VID_BACK_LIGHT,
                                       MLM_MENU_KEY_HELP_TIP_PICTURE_BL,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_back_light_val,
                                       _get_vid_back_light_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_back_light.u.t_range.b_fast_mode = TRUE;

#if 1//ndef MT5583_MODEL // MVD-1979
    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_tone_mapping,
                                       MLM_MENU_KEY_VID_TONE_MAPPING,
                                       MLM_MENU_KEY_HELP_TIP_PICTURE_BL,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_back_light_val,
                                       _get_vid_back_light_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_tone_mapping.u.t_range.b_fast_mode = TRUE;
#endif

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_oled_luminance,
                                       MLM_MENU_KEY_VID_OLED_LUMINANCE,
                                       MLM_MENU_KEY_VID_OLED_LUMINANCE_TIP,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_back_light_val,
                                       _get_vid_back_light_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_oled_luminance.u.t_range.b_fast_mode = TRUE;

    /* Adaptive Back Light */
#ifdef APP_MENU_ADP_BACK_LIGHT_SUPPORT
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_adp_back_light,
                                      MLM_MENU_KEY_VID_ADP_BACK_LIGHT,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_vid_adp_back_light_idx,
                                      _get_vid_adp_back_light_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

    /* Gamma */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_gamma,
                                      MLM_MENU_KEY_VID_GAMMA,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_VID_GAMMA_DARK,
                                      MLM_MENU_KEY_VID_GAMMA_BRIGHT,
                                      _set_vid_gamma_idx,
                                      _get_vid_gamma_idx);
    MENU_CHK_FAIL(i4_ret);


    /* Color Temp. R */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

     i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_clr_gain_r,
                                        MLM_MENU_KEY_VID_CLR_GAIN_R,
                                        MLM_MENU_KEY_HELP_RED_G,
                                        i2_val_min,
                                        i2_val_max,
                                        MENU_ITEM_RANGE_STYLE_BAR,
                                        _set_vid_clr_gain_r_val,
                                        _get_vid_clr_gain_r_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_clr_gain_r.u.t_range.pf_incr = _incr_vid_clr_gain_r;
    t_g_menu_common_item_vid_clr_gain_r.u.t_range.pf_decr = _decr_vid_clr_gain_r;

    /* Color Temp. G */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_clr_gain_g,
                                       MLM_MENU_KEY_VID_CLR_GAIN_G,
                                       MLM_MENU_KEY_HELP_GREEN_G,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_clr_gain_g_val,
                                       _get_vid_clr_gain_g_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_clr_gain_g.u.t_range.pf_incr = _incr_vid_clr_gain_g;
    t_g_menu_common_item_vid_clr_gain_g.u.t_range.pf_decr = _decr_vid_clr_gain_g;

    /* Color Temp. B */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

     i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_clr_gain_b,
                                        MLM_MENU_KEY_VID_CLR_GAIN_B,
                                        MLM_MENU_KEY_HELP_BLUE_G,
                                        i2_val_min,
                                        i2_val_max,
                                        MENU_ITEM_RANGE_STYLE_BAR,
                                        _set_vid_clr_gain_b_val,
                                        _get_vid_clr_gain_b_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_clr_gain_b.u.t_range.pf_incr = _incr_vid_clr_gain_b;
    t_g_menu_common_item_vid_clr_gain_b.u.t_range.pf_decr = _decr_vid_clr_gain_b;


     /* Color Offset R */
    i4_ret = a_cfg_av_get_min_max(
                                  CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R),
                                  &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_clr_offset_r,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_R,
                                       MLM_MENU_KEY_HELP_RED_OFFSET,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_clr_offset_r_val,
                                       _get_vid_clr_offset_r_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_clr_offset_r.u.t_range.pf_incr = NULL;
    t_g_menu_common_item_vid_clr_offset_r.u.t_range.pf_decr = NULL;

    /* Color Offset G */
    i4_ret = a_cfg_av_get_min_max(
                                  CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G),
                                  &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_clr_offset_g,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_G,
                                       MLM_MENU_KEY_HELP_GREEN_OFFSET,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_clr_offset_g_val,
                                       _get_vid_clr_offset_g_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_clr_offset_g.u.t_range.pf_incr = NULL;
    t_g_menu_common_item_vid_clr_offset_g.u.t_range.pf_decr = NULL;

    /* Color Offset B */
    i4_ret = a_cfg_av_get_min_max(
                                  CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B),
                                  &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_clr_offset_b,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_B,
                                       MLM_MENU_KEY_HELP_BLUE_OFFSET,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_clr_offset_b_val,
                                       _get_vid_clr_offset_b_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_clr_offset_b.u.t_range.pf_incr = NULL;
    t_g_menu_common_item_vid_clr_offset_b.u.t_range.pf_decr = NULL;

    /* Factory Color Temp. R */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_fac_clr_gain_r,
                                       MLM_MENU_KEY_VID_CLR_GAIN_R,
                                       MLM_MENU_KEY_VID_CLR_GAIN_R,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_fac_clr_gain_r_val,
                                       _get_vid_fac_clr_gain_r_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_fac_clr_gain_r.u.t_range.pf_incr = _incr_vid_fac_clr_gain_r;
    t_g_menu_common_item_vid_fac_clr_gain_r.u.t_range.pf_decr = _decr_vid_fac_clr_gain_r;

    /* Factory Color Temp. G */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_G),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_fac_clr_gain_g,
                                       MLM_MENU_KEY_VID_CLR_GAIN_G,
                                       MLM_MENU_KEY_VID_CLR_GAIN_G,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_fac_clr_gain_g_val,
                                       _get_vid_fac_clr_gain_g_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_fac_clr_gain_g.u.t_range.pf_incr = _incr_vid_fac_clr_gain_g;
    t_g_menu_common_item_vid_fac_clr_gain_g.u.t_range.pf_decr = _decr_vid_fac_clr_gain_g;

    /* Factory Color Temp. B */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_B),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_fac_clr_gain_b,
                                       MLM_MENU_KEY_VID_CLR_GAIN_B,
                                       MLM_MENU_KEY_VID_CLR_GAIN_B,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_fac_clr_gain_b_val,
                                       _get_vid_fac_clr_gain_b_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_fac_clr_gain_b.u.t_range.pf_incr = _incr_vid_fac_clr_gain_b;
    t_g_menu_common_item_vid_fac_clr_gain_b.u.t_range.pf_decr = _decr_vid_fac_clr_gain_b;

    /* Factory Color Offset R */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_R),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_fac_clr_offset_r,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_R,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_R,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_fac_clr_offset_r_val,
                                       _get_vid_fac_clr_offset_r_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_fac_clr_offset_r.u.t_range.pf_incr = _incr_vid_fac_clr_offset_r;
    t_g_menu_common_item_vid_fac_clr_offset_r.u.t_range.pf_decr = _decr_vid_fac_clr_offset_r;

    /* Factory Color Offset G */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_G),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_fac_clr_offset_g,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_G,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_G,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_fac_clr_offset_g_val,
                                       _get_vid_fac_clr_offset_g_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_fac_clr_offset_g.u.t_range.pf_incr = _incr_vid_fac_clr_offset_g;
    t_g_menu_common_item_vid_fac_clr_offset_g.u.t_range.pf_decr = _decr_vid_fac_clr_offset_g;

    /* Factory Color Offset B */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_OFFSET_B),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_fac_clr_offset_b,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_B,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_B,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vid_fac_clr_offset_b_val,
                                       _get_vid_fac_clr_offset_b_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_fac_clr_offset_b.u.t_range.pf_incr = _incr_vid_fac_clr_offset_b;
    t_g_menu_common_item_vid_fac_clr_offset_b.u.t_range.pf_decr = _decr_vid_fac_clr_offset_b;

    /* Blur */
    if (a_cfg_custom_chk_freqence_120hz()||a_cfg_custom_chk_panel_120hz())
    {
        i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_blur,
                                             MLM_MENU_KEY_VID_BLUR,
                                             MLM_MENU_KEY_HELP_TIP_PICTURE_BLUR_120HZ,
                                             MLM_MENU_KEY_VID_BLUR_OFF,
                                             MLM_MENU_KEY_VID_BLUR_ON,
                                             _set_vid_blur_idx,
                                             _get_vid_blur_idx);
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_blur,
                                         MLM_MENU_KEY_VID_BLUR,
                                         MLM_MENU_KEY_HELP_TIP_PICTURE_BLUR_60HZ,
                                         MLM_MENU_KEY_VID_BLUR_OFF,
                                         MLM_MENU_KEY_VID_BLUR_ON,
                                         _set_vid_blur_idx,
                                         _get_vid_blur_idx);
        MENU_CHK_FAIL(i4_ret);
    }

    /* DNR */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_dnr,
                                         MLM_MENU_KEY_VID_DNR,
                                         MLM_MENU_KEY_HELP_TIP_PICTURE_NR,
                                         MLM_MENU_KEY_VID_DNR_OFF,
                                         MLM_MENU_KEY_VID_DNR_HIGH,
                                         _set_vid_dnr_idx,
                                         _get_vid_dnr_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Flesh Tone */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_flesh_tone,
                                      MLM_MENU_KEY_VID_CLR_STR,
                                      MLM_MENU_KEY_HELP_VID_CLR_STR,
                                      MLM_MENU_KEY_VID_FT_OFF,
                                      MLM_MENU_KEY_VID_FT_GREEN_BLUE,
                                      _set_vid_flesh_tone_idx,
                                      _get_vid_flesh_tone_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Adaptive Luma Control */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_alc,
                                      MLM_MENU_KEY_VID_CON_EHC,
                                      MLM_MENU_KEY_HELP_ADAPTIVE_LUMA,
                                      MLM_MENU_KEY_VID_FTONE_OFF,
                                      MLM_MENU_KEY_VID_FTONE_HIGH,
                                      _set_vid_alc_idx,
                                      _get_vid_alc_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Screen Mode */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    t_g_menu_common_item_vid_scr_mode.e_item_type                   = MENU_ITEM_TYPE_LIST;
    t_g_menu_common_item_vid_scr_mode.ui2_msgid_title               = MLM_MENU_KEY_MENU_SCREEN_MODE;
    t_g_menu_common_item_vid_scr_mode.ui2_msgid_desc                = MLM_MENU_KEY_VID_SCR_MODE;
    t_g_menu_common_item_vid_scr_mode.u.t_list.ui2_elem_num         = (UINT16)(i2_val_max - 1);
    t_g_menu_common_item_vid_scr_mode.u.t_list.pf_set_idx           = _set_vid_scr_mode_idx;
    t_g_menu_common_item_vid_scr_mode.u.t_list.pf_get_idx           = _get_vid_scr_mode_idx;
    t_g_menu_common_item_vid_scr_mode.u.t_list.pf_next_idx          = _next_vid_scr_mode_idx;
    t_g_menu_common_item_vid_scr_mode.u.t_list.pf_prev_idx          = _prev_vid_scr_mode_idx;
    t_g_menu_common_item_vid_scr_mode.u.t_list.pf_get_text          = _get_vid_scr_mode_text;
    t_g_menu_common_item_vid_scr_mode.u.t_list.ui2_msgid_elem_first = 0;
    t_g_menu_common_item_vid_scr_mode.u.t_list.ui2_msgid_elem_last  = 0;

    /* YPbpr Phase */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_YPBPR_PHASE),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_ypbpr_phase,
                                      MLM_MENU_KEY_VID_YPBPR_PHASE,
                                      MLM_MENU_KEY_EMPTY,
                                      i2_val_min,
                                      i2_val_max,
                                      MENU_ITEM_RANGE_STYLE_BAR,
                                      _set_vid_ypbpr_phase_val,
                                      _get_vid_ypbpr_phase_val);

    MENU_CHK_FAIL(i4_ret);
#ifdef APP_HV_POS_MODIFICATION_SUPPORT
    /* Video H pos. */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_pos_h,
                                      MLM_MENU_KEY_H_POS,
                                      MLM_MENU_KEY_HELP_H_POS,
                                      i2_val_min,
                                      i2_val_max,
                                      MENU_ITEM_RANGE_STYLE_BAR,
                                      _set_vid_pos_h_val,
                                      _get_vid_pos_h_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_pos_h.u.t_range.b_fast_mode = FALSE;

    /* Video V pos. */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_pos_v,
                                      MLM_MENU_KEY_V_POS,
                                      MLM_MENU_KEY_HELP_V_POS,
                                      i2_val_min,
                                      i2_val_max,
                                      MENU_ITEM_RANGE_STYLE_BAR,
                                      _set_vid_pos_v_val,
                                      _get_vid_pos_v_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_pos_v.u.t_range.b_fast_mode = FALSE;
#endif

#ifdef APP_MJC_SUPPORT

    /* MJC Effect */
    i4_ret = a_cfg_av_get_min_max(
                    CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT),
                    &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_mjc_effect,
                                      MLM_MENU_KEY_VID_MEMC_EFFECT,
                                      MLM_MENU_KEY_HELP_VID_MEMC_EFFECT,
                                      MLM_MENU_KEY_VID_MJC_EFFECT_OFF,
                                      (UINT16)(MLM_MENU_KEY_VID_MJC_EFFECT_OFF + i2_val_max),
                                      _set_vid_mjc_effect_idx,
                                      _get_vid_mjc_effect_idx);
    MENU_CHK_FAIL(i4_ret);

    /* MJC Mode */
    i4_ret = a_cfg_av_get_min_max(
                    CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_MODE),
                    &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_mjc_mode,
                                      MLM_MENU_KEY_VID_MEMC_MODE,
                                      MLM_MENU_KEY_HELP_VID_MEMC_MODE,
                                      MLM_MENU_KEY_VID_MEMC_MODE_0,
                                      (UINT16)(MLM_MENU_KEY_VID_MEMC_MODE_0 + 2),
                                      _set_vid_mjc_mode_idx,
                                      _get_vid_mjc_mode_idx);
    MENU_CHK_FAIL(i4_ret);

    /* MJC Demo mode */
    i4_ret = a_cfg_av_get_min_max(
                    CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_DEMO),
                    &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_mjc_demo_mode,
                                      MLM_MENU_KEY_VID_MJC_DEMO_PART,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_VID_MJC_DEMO_PART_ALL,
                                      (UINT16)(MLM_MENU_KEY_VID_MJC_DEMO_PART_ALL+i2_val_max),
                                      _set_vid_mjc_demo_part_idx,
                                      _get_vid_mjc_demo_part_idx);
    MENU_CHK_FAIL(i4_ret);
#endif /* APP_MJC_SUPPORT */


#ifdef APP_MENU_HDMI_MODE_SUPPORT
    /* Color Space */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_hdmi_mode,
                                      MLM_MENU_KEY_HDMI_COLOR_SPACE,
                                      MLM_MENU_KEY_HDMI_COLOR_SPACE_HELP_TAB,
                                      MLM_MENU_KEY_VID_HDMI_MODE_COLOR_SPACE_AUTO,
                                      MLM_MENU_KEY_VID_HDMI_MODE_COLOR_SPACE_YCBCR,
                                      _set_vid_hdmi_mode_idx,
                                      _get_vid_hdmi_mode_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifndef MT5583_MODEL
    /* HDMI mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_inp_hdmi_mode,
                                      MLM_MENU_KEY_VID_HDMI_MODE,
                                      MLM_MENU_KEY_HDMI_MODE_TIP,
                                      MLM_MENU_KEY_HDMI_MODE_AUTO,
                                      MLM_MENU_KEY_HDMI_MODE_1_4,
                                      _set_inp_hdmi_mode_idx,
                                      _get_inp_hdmi_mode_idx);
    MENU_CHK_FAIL(i4_ret);
#else
    /* HDMI mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_inp_hdmi_mode,
                                      MLM_MENU_KEY_VID_HDMI_MODE,
                                      MLM_MENU_KEY_HDMI_MODE_SCDS_TIP,
                                      MLM_MENU_KEY_HDMI_MODE_SCDS_AUTO,
                                      MLM_MENU_KEY_HDMI_MODE_SCDS_1_4,
                                      _set_inp_hdmi_mode_idx,
                                      _get_inp_hdmi_mode_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

#if( ENABLE_FULL_COLOR_444 )
    /* Full Color 4:4:4 */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_inp_full_color_444,
                                      MLM_MENU_KEY_FULL_CHROMA,
                                      MLM_MENU_KEY_HELP_FULL_CHROMA,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_inp_full_color_444_idx,
                                      _get_inp_full_444_color_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

    /* Film Maker Mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_inp_film_maker_mode,
                                      MLM_MENU_KEY_FILM_MAKER_MODE,
                                      MLM_MENU_KEY_FILM_MAKER_MODE_TIP,
                                      MLM_MENU_KEY_FILM_MAKER_MODE_AUTO,
                                      MLM_MENU_KEY_FILM_MAKER_MODE_OFF,
                                      _set_inp_film_maker_mode_idx,
                                      _get_inp_film_maker_mode_idx);
    MENU_CHK_FAIL(i4_ret);

    /* energy saving mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_custom_item_energy_saving_mode,
                                     MLM_MENU_KEY_ENERGY_SAVING_MODE,
                                     MLM_MENU_KEY_ENERGY_SAVING_MODE_TIP,
                                     MLM_MENU_KEY_OFF,
                                     MLM_MENU_KEY_ON,
                                     _set_energy_saving_mode_idx,
                                     _get_energy_saving_mode_idx);
    MENU_CHK_FAIL(i4_ret);

    /* VGA mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_vga_mode,
                                      MLM_MENU_KEY_VID_VGA_MODE,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_VID_VGA_MODE_VIDEO,
                                      MLM_MENU_KEY_VID_VGA_MODE_GRAPH,
                                      _set_vid_vga_mode_idx,
                                      _get_vid_vga_mode_idx);
    MENU_CHK_FAIL(i4_ret);


#ifdef APP_DI_SUPPORT

    /* DI Film Mode  change page item off/auto -> auto/off*/
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_di_film_mode,
                                      MLM_MENU_KEY_VID_FILM_MODE,
                                      MLM_MENU_KEY_HELP_VID_FILM_MODE,
                                      MLM_MENU_KEY_FILM_MODE_AUTO_EX,
                                      MLM_MENU_KEY_FILM_MODE_OFF_EX,
                                      _set_vid_di_film_mode_idx,
                                      _get_vid_di_film_mode_idx);
    MENU_CHK_FAIL(i4_ret);

    /* DI MA */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_di_ma,
                                      MLM_MENU_KEY_VID_DI_MA,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_VID_DI_MA_SLOW_PIC,
                                      MLM_MENU_KEY_VID_DI_MA_ACTION_PIC,
                                      _set_vid_di_ma_idx,
                                      _get_vid_di_ma_idx);
    MENU_CHK_FAIL(i4_ret);

    /* DI Edge Preserve*/
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_di_edge,
                                      MLM_MENU_KEY_VID_DI_EDGE,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_VID_DI_EDGE_WEAK,
                                      MLM_MENU_KEY_VID_DI_EDGE_STRONG,
                                      _set_vid_di_edge_idx,
                                      _get_vid_di_edge_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

    /* Game Low Latency */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_game_low_latency,
                                      MLM_MENU_KEY_VID_GAME_LOW_LATENCY,
                                      MLM_MENU_KEY_TAB_HELP_GAME_MODE,
                                      MLM_MENU_KEY_VID_GLL_AUTO,
                                      MLM_MENU_KEY_VID_GLL_ON,
                                      _set_vid_game_low_latency_idx,
                                      _get_vid_game_low_latency_idx);
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_MENU_PQ_DEMO_SUPPORT
        /* pq demo */
        i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_pq,
                                          MLM_MENU_KEY_VID_PQ_DEMO,
                                          MLM_MENU_KEY_EMPTY,
                                          MLM_MENU_KEY_OFF,
                                          MLM_MENU_KEY_ON,
                                          _set_vid_pq_demo_idx,
                                          _get_vid_pq_demo_idx);
        MENU_CHK_FAIL(i4_ret);
#endif

    /* xyYYC */
#ifdef APP_XVYCC_SUPPORT
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_xvycc,
                                      MLM_MENU_KEY_VID_XVYCC,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_vid_xvycc_idx,
                                      _get_vid_xvycc_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifdef APP_WCG_SUPPORT
    /* Wide Color Gamut */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_wcg,
                                      MLM_MENU_KEY_VID_WCG,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_vid_wcg_idx,
                                      _get_vid_wcg_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifdef APP_BLUE_STRETCH_SUPPORT
    /* Blue Stretch*/
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_blue_stretch,
                                      MLM_MENU_KEY_VID_BLUE_STRETCH,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_vid_blue_stretch_idx,
                                      _get_vid_blue_stretch_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifdef APP_MPEG_NR_SUPPORT
    /* MPEG NR */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_mpeg_nr,
                                      MLM_MENU_KEY_VID_MPEG_NR,
                                      MLM_MENU_KEY_HELP_TIP_PICTURE_MPEG_NR,
                                      MLM_MENU_KEY_VID_MPEG_NR_OFF,
                                      MLM_MENU_KEY_VID_MPEG_NR_STRONG,
                                      _set_vid_mpeg_nr_idx,
                                      _get_vid_mpeg_nr_idx);
    MENU_CHK_FAIL(i4_ret);
#endif
    BOOL b_support     = FALSE;
    UINT16 ui2_mlm_key = MLM_MENU_KEY_EMPTY;
    /* Local Dimming */
    b_support = a_cfg_cust_get_support_local_dimming();
    if(b_support)
    {
        ui2_mlm_key = _get_local_dimming_mlm_key();
        i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_local_dimming,
                                  ui2_mlm_key,
                                  MLM_MENU_KEY_HELP_TIP_ITEM_BACKLIGHT_DIMMING,
                                  MLM_MENU_KEY_LOCAL_DEMMING_OFF,
                                  MLM_MENU_KEY_LOCAL_DEMMING_HIGH,
                                  _set_local_dimming_idx,
                                  _get_local_dimming_idx);
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_local_dimming,
                          MLM_MENU_KEY_VID_BACK_LIGHT_CTRL,
                          MLM_MENU_KEY_HELP_LOCAL_DIMMING,
                          MLM_MENU_KEY_MENU_COMMON_OFF,
                          MLM_MENU_KEY_MENU_COMMON_ON,
                          _set_local_dimming_idx,
                          _get_local_dimming_idx);
        MENU_CHK_FAIL(i4_ret);
    }

    /*  Contrast Enhancement */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_contrast_en,
                                      MLM_MENU_KEY_VID_CON_EHC,
                                      MLM_MENU_KEY_VID_CON_EHC_TIP,
                                      MLM_MENU_KEY_VID_CONTRAST_EN_OFF,
                                      MLM_MENU_KEY_VID_CONTRAST_EN_HIGH,
                                      _set_vid_contrast_en_idx,
                                      _get_vid_contrast_en_idx);
    MENU_CHK_FAIL(i4_ret);

#ifndef MT5583_MODEL
    /*  Super Resolution */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_super_resolution,
                                      MLM_MENU_KEY_VID_SUPER_RESOLUTION,
                                      MLM_MENU_KEY_VID_SUPER_RESOLUTION_TIP,
                                      MLM_MENU_KEY_VID_CONTRAST_EN_OFF,
                                      MLM_MENU_KEY_VID_CONTRAST_EN_HIGH,
                                      _set_vid_super_resolution_idx,
                                      _get_vid_super_resolution_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

    /*  Edge Enhancement */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_edge_enhancement,
                                      MLM_MENU_KEY_VID_EDGE_ENHANCEMENT,
                                      MLM_MENU_KEY_VID_EDGE_ENHANCEMENT_TIP,
                                      MLM_MENU_KEY_VID_CONTRAST_EN_OFF,
                                      MLM_MENU_KEY_VID_CONTRAST_EN_HIGH,
                                      _set_vid_edge_enhancement_idx,
                                      _get_vid_edge_enhancement_idx);
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_SUPPPORT_FRC
    /* Judder Reduction */
    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_judder_reduction,
                                      MLM_MENU_KEY_VID_JUDDER_REDUCTION,
                                      MLM_MENU_KEY_VID_JUDDER_REDUCTION_TIP,
                                      0,
                                      10,
                                      MENU_ITEM_RANGE_STYLE_BAR,
                                      _set_vid_judder_reduction_idx,
                                      _get_vid_judder_reduction_idx);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_judder_reduction.u.t_range.b_fast_mode = FALSE;

    /* Motion Blur Reduction */
    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vid_motion_blur_reduction,
                                      MLM_MENU_KEY_VID_MOTION_BLUR_REDUCTION,
                                      MLM_MENU_KEY_VID_MOTION_BLUR_REDUCTION_TIP,
                                      0,
                                      10,
                                      MENU_ITEM_RANGE_STYLE_BAR,
                                      _set_vid_motion_blur_reduction_idx,
                                      _get_vid_motion_blur_reduction_idx);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vid_motion_blur_reduction.u.t_range.b_fast_mode = FALSE;
#endif

    /* Variable Refresh Rate */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_vss,
                                        MLM_MENU_KEY_VID_VARIABLE_REFRESH_RATE,
                                        MLM_MENU_KEY_VID_VARIABLE_REFRESH_RATE_TIP,
                                        MLM_MENU_KEY_MENU_COMMON_OFF,
                                        MLM_MENU_KEY_MENU_COMMON_ON,
                                        _set_vid_vss_idx,
                                        _get_vid_vss_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Local Contrast */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_local_contrast,
                                        MLM_MENU_KEY_VID_LOCAL_CONTRAST,
                                        MLM_MENU_KEY_VID_LOCAL_CONTRAST_TIP,
                                        MLM_MENU_KEY_VID_CONTRAST_EN_OFF,
                                        MLM_MENU_KEY_VID_CONTRAST_EN_HIGH,
                                        _set_vid_local_contrast_idx,
                                        _get_vid_local_contrast_idx);
    MENU_CHK_FAIL(i4_ret);

#ifndef MT5583_MODEL
    /* Contour Smoothing */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_contour_smoothing,
                                        MLM_MENU_KEY_VID_CONTOUR_SMOOTHING,
                                        MLM_MENU_KEY_VID_CONTOUR_SMOOTHING_TIP,
                                        MLM_MENU_KEY_VID_CONTRAST_EN_OFF,
                                        MLM_MENU_KEY_VID_CONTRAST_EN_HIGH,
                                        _set_vid_contour_smoothing_idx,
                                        _get_vid_contour_smoothing_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifndef MT5583_MODEL
    /* Game HDR */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_game_hdr,
                                        MLM_MENU_KEY_VID_GAME_HDR,
                                        MLM_MENU_KEY_VID_GAME_HDR_TIP,
                                        MLM_MENU_KEY_MENU_COMMON_OFF,
                                        MLM_MENU_KEY_MENU_COMMON_ON,
                                        _set_vid_game_hdr_idx,
                                        _get_vid_game_hdr_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

    /* Peak luminance */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_peak_luminance,
                                        MLM_MENU_KEY_VID_PEAK_LUMINANCE,
                                        MLM_MENU_KEY_VID_PEAK_LUMINANCE_TIP,
                                        MLM_MENU_KEY_VID_CONTRAST_EN_LOW,
                                        MLM_MENU_KEY_VID_CONTRAST_EN_HIGH,
                                        _set_vid_peak_luminance_idx,
                                        _get_vid_peak_luminance_idx);
    MENU_CHK_FAIL(i4_ret);

#ifndef MT5583_MODEL
    /* Enhanced Viewing Angle */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_en_view_angle,
                                        MLM_MENU_KEY_VID_ENHANCED_VIEWING_ANGLE,
                                        MLM_MENU_KEY_VID_ENHANCED_VIEWING_ANGLE_TIP,
                                        MLM_MENU_KEY_MENU_COMMON_OFF,
                                        MLM_MENU_KEY_MENU_COMMON_ON,
                                        _set_vid_en_view_angle_idx,
                                        _get_vid_en_view_angle_idx);
    MENU_CHK_FAIL(i4_ret);
#endif
    /* Test Patterns/Calibration Tests */

    /* OLED Pixel Shift */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_vid_oled_pixel_shift,
                                        MLM_MENU_KEY_VID_OLED_PIXEL_SHIFT,
                                        MLM_MENU_KEY_VID_OLED_PIXEL_SHIFT_TIP,
                                        MLM_MENU_KEY_MENU_COMMON_OFF,
                                        MLM_MENU_KEY_MENU_COMMON_ON,
                                        _set_vid_oled_pixel_shift_idx,
                                        _get_vid_oled_pixel_shift_idx);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

INT32 menu_common_audio_settings_init()
{
    INT32   i4_ret;
    INT16   i2_val_min;
    INT16   i2_val_max;

     /* Volume */
    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                                  &i2_val_min,
                                  &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_aud_volume,
                                      MLM_MENU_KEY_AUD_VOL,
                                      MLM_MENU_KEY_EMPTY,
                                      i2_val_min,
                                      i2_val_max,
                                      MENU_ITEM_RANGE_STYLE_BAR,
                                      _set_aud_volume_val,
                                      _get_aud_volume_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_aud_volume.u.t_range.pf_incr = _incr_aud_volume;
    t_g_menu_common_item_aud_volume.u.t_range.pf_decr = _decr_aud_volume;


    /* Balance */
    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE),
                                  &i2_val_min,
                                  &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_aud_balance,
                                      MLM_MENU_KEY_AUD_BAL,
                                      MLM_MENU_KEY_HELP_TIP_AUDIO_BALANCE,
                                      i2_val_min,
                                      i2_val_max,
                                      MENU_ITEM_RANGE_STYLE_BAR,
                                      _set_aud_balance_val,
                                      _get_aud_balance_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_aud_balance.u.t_range.pf_incr = _incr_aud_balance;
    t_g_menu_common_item_aud_balance.u.t_range.pf_decr = _decr_aud_balance;
    t_g_menu_common_item_aud_balance.u.t_range.b_fast_mode = TRUE;

    menu_page_tree_sb_settings_eq_mode_list_item(&t_g_menu_common_item_aud_sb_eq_mode,
                                                                MLM_MENU_KEY_AUD_EQ_MODE_INDENTATION,
                                                                MLM_MENU_KEY_AUD_EQ_MODE_TIP,
                                                                MLM_MENU_KEY_EQ_MODE_MUSIC,
                                                                MLM_MENU_KEY_EQ_MODE_DIALOGUE,
                                                                _set_aud_eq_mode_val,
                                                                _get_aud_eq_mode_val,
                                                                _get_menu_eq_mode_text,
                                                                _prev_menu_eq_mode_idx,
                                                                _next_menu_eq_mode_idx  );

	MENU_CHK_FAIL(i4_ret);

#if 1
    /* Bass */
    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS),
                                  &i2_val_min,
                                  &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_aud_bass,
                                       MLM_MENU_KEY_AUD_BASS,
                                       MLM_MENU_KEY_HELP_TIP_AUDIO_BASS,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_aud_bass_val,
                                       _get_aud_bass_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_aud_bass.u.t_range.pf_incr = _incr_aud_bass;
    t_g_menu_common_item_aud_bass.u.t_range.pf_decr = _decr_aud_bass;

    /* Treble */
    i4_ret = a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE),
                                  &i2_val_min,
                                  &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_aud_treble,
                                       MLM_MENU_KEY_AUD_TREBLE,
                                       MLM_MENU_KEY_HELP_TIP_AUDIO_TREBLE,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_aud_treble_val,
                                       _get_aud_treble_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_aud_treble.u.t_range.pf_incr = _incr_aud_treble;
    t_g_menu_common_item_aud_treble.u.t_range.pf_decr = _decr_aud_treble;

#else
    /* Bass */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_bass,
                                      MLM_MENU_KEY_AUD_BASS,
                                      MLM_MENU_KEY_AUD_SRD_TIP,
                                      MLM_MENU_KEY_DIALOGUE_ENHANCER_OFF,
                                      MLM_MENU_KEY_DIALOGUE_ENHANCER_HIGH,
                                      _set_aud_dialogue_val,
                                      _get_aud_dialogue_val);
    MENU_CHK_FAIL(i4_ret);

    /* Treble */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_treble,
                                      MLM_MENU_KEY_AUD_TREBLE,
                                      MLM_MENU_KEY_AUD_SRD_TIP,
                                      MLM_MENU_KEY_DIALOGUE_ENHANCER_OFF,
                                      MLM_MENU_KEY_DIALOGUE_ENHANCER_HIGH,
                                      _set_aud_subwoofer_val,
                                      _get_aud_subwoofer_val);
    MENU_CHK_FAIL(i4_ret);
#endif
     /**
    *SB-Bass
    */
    MENU_CHK_FAIL(menu_page_tree_list_item(&t_g_menu_common_item_aud_sb_bass,
                                                MLM_MENU_KEY_AUD_BASS_INDENTATION,
                                                MLM_MENU_KEY_AUD_BASS_TIP,
                                                MLM_MENU_KEY_DIALOGUE_ENHANCER_LOW,
                                                MLM_MENU_KEY_DIALOGUE_ENHANCER_HIGH,
                                                _set_aud_sb_bass_val,
                                                _get_aud_sb_bass_val));
      /**
    *SB-Trble
    */
    MENU_CHK_FAIL(menu_page_tree_list_item(&t_g_menu_common_item_aud_sb_treble,
                                                MLM_MENU_KEY_AUD_TREBLE_INDENTATION,
                                                MLM_MENU_KEY_AUD_TREBLE_TIP,
                                                MLM_MENU_KEY_DIALOGUE_ENHANCER_LOW,
                                                MLM_MENU_KEY_DIALOGUE_ENHANCER_HIGH,
                                                _set_aud_sb_treble_val,
                                                _get_aud_sb_treble_val));


    /**
    *SB-Dialogue
    */
    MENU_CHK_FAIL(menu_page_tree_list_item(&t_g_menu_common_item_aud_dialogue,
                                                MLM_MENU_KEY_AUD_DIALOGUE_INDENTATION,
                                                MLM_MENU_KEY_AUD_DIALOGUE_TIP,
                                                MLM_MENU_KEY_DIALOGUE_ENHANCER_LOW,
                                                MLM_MENU_KEY_DIALOGUE_ENHANCER_HIGH,
                                                _set_aud_dialogue_val,
                                                _get_aud_dialogue_val));


    /**
    *SB-Subwoofer
    */
    MENU_CHK_FAIL(menu_page_tree_list_item(&t_g_menu_common_item_aud_subwoofer,
                                                MLM_MENU_KEY_AUD_SUBWOOFER_INDENTATION,
                                                MLM_MENU_KEY_AUD_SUBWOOFER_TIP,
                                                MLM_MENU_KEY_DIALOGUE_ENHANCER_LOW,
                                                MLM_MENU_KEY_DIALOGUE_ENHANCER_HIGH,
                                                _set_aud_subwoofer_val,
                                                _get_aud_subwoofer_val));

    /**
    *SB-Night Mode
    */
    MENU_CHK_FAIL(menu_page_tree_list_item(&t_g_menu_common_item_aud_night_mode,
                                                MLM_MENU_KEY_AUD_NIGHT_MODE_INDENTATION,
                                                MLM_MENU_KEY_AUD_NIGHT_MODE_TIP,
                                                MLM_MENU_KEY_OFF,
                                                MLM_MENU_KEY_ON,
                                                _set_aud_night_mode_val,
                                                _get_aud_night_mode_val));


    /**
    *SB-Virtual:X
    */
    MENU_CHK_FAIL(menu_page_tree_list_item(&t_g_menu_common_item_aud_virtualx,
                                                MLM_MENU_KEY_AUD_VIRTUAL_X_INDENTATION,
                                                MLM_MENU_KEY_AUD_VIRTUAL_X_TIP,
                                                MLM_MENU_KEY_OFF,
                                                MLM_MENU_KEY_ON,
                                                _set_aud_virtualx_val,
                                                _get_aud_virtualx_val));

    /**
    *SB-Speaker Test
    */
    MENU_CHK_FAIL(menu_page_tree_action_item(&t_g_menu_common_item_aud_sb_speaker_Test,
                                                MLM_MENU_KEY_AUD_SPEAKER_TEST_INDENTATION,
                                                MLM_MENU_KEY_AUD_SPEAKER_TEST_TIP,
                                                MLM_MENU_KEY_EMPTY,
                                                _set_aud_sb_speakertest_val));

    /**
    *SB-Info
    */
    MENU_CHK_FAIL(menu_page_tree_action_item(&t_g_menu_common_item_aud_sb_Info,
                                                MLM_MENU_KEY_AUD_INFO_INDENTATION,
                                                MLM_MENU_KEY_AUD_INFO_TIP,
                                                MLM_MENU_KEY_EMPTY,
                                                _set_aud_sb_info_val));


    /* Sound Surround */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_surround,
                                      MLM_MENU_KEY_AUD_SRD,
                                      MLM_MENU_KEY_AUD_SRD_TIP,
                                      MLM_MENU_KEY_SURROUND_SOUND_VIRTUAL,
                                      MLM_MENU_KEY_SURROUND_SOUND_OFF,
                                      _set_aud_surround_idx,
                                      _get_aud_surround_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Reverb */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_reverb,
                                      MLM_MENU_KEY_AUD_RVB,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_AUD_RVB_OFF,
                                      MLM_MENU_KEY_AUD_RVB_CHURCH,
                                      _set_aud_reverb_idx,
                                      _get_aud_reverb_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Volume Conrol */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_vol_control,
                                      MLM_MENU_KEY_AUD_CONTROL,
                                      MLM_MENU_KEY_AUD_CONTROL_HELP,
                                      MLM_MENU_KEY_AUD_CONTROL_TV,
                                      MLM_MENU_KEY_AUD_CONTROL_EXTERNAL,
                                      _set_aud_vol_control_idx,
                                      _get_aud_vol_control_idx);
    MENU_CHK_FAIL(i4_ret);

    /* SRS TruVolume */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_srs_truvolume,
                                      MLM_MENU_KEY_AUD_SRS_TRUVOLUME,
                                      MLM_MENU_KEY_HELP_TIP_AUDIO_SRS,
                                      MLM_MENU_KEY_MENU_COMMON_OFF,
                                      MLM_MENU_KEY_MENU_COMMON_ON,
                                      _set_aud_srs_truvolume_idx,
                                      _get_aud_srs_truvolume_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Speaker */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_speaker,
                                      MLM_MENU_KEY_AUD_SPEAKER,
                                      MLM_MENU_KEY_HELP_TIP_AUDIO_SPEAKER,
                                      MLM_MENU_KEY_AUDIO_AUTO,
                                      MLM_MENU_KEY_AUDIO_OFF,
                                      _set_aud_speaker_idx,
                                      _get_aud_speaker_idx);
    MENU_CHK_FAIL(i4_ret);

    _init_uart_fact_mode();
    /* vol control display */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_vol_dis,
                                         MLM_MENU_KEY_AUD_VOL_CONTROL_DIS,
                                         MLM_MENU_KEY_AUD_VOL_CONTROL_DIS_HELP_TIP,
                                         MLM_MENU_KEY_AUDIO_ON,
                                         MLM_MENU_KEY_AUDIO_OFF,
                                         _set_aud_vol_dis_idx,
                                         _get_aud_vol_dis_idx);
    MENU_CHK_FAIL(i4_ret);

    /* MTS */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_mts,
                                         MLM_MENU_KEY_AUD_ANALOG_PREFERENCE,
                                         MLM_MENU_KEY_HELP_TIP_AUDIO_ANA_MTS,
                                         MLM_MENU_KEY_AUD_MTS_STEREO,
                                         MLM_MENU_KEY_AUD_MTS_MONO,
                                         _set_aud_mts_idx,
                                         _get_aud_mts_idx);
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_BBE_SUPPORT
    /* BBE */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_bbe_mode,
                                      MLM_MENU_KEY_AUD_BBE_MODE,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_AUD_BBE_MODE_OFF,
#ifdef APP_BBE_VIVA_SUPPORT
                                      MLM_MENU_KEY_AUD_BBE_MODE_BBE_VIVA,
#else
                                      MLM_MENU_KEY_AUD_BBE_MODE_BBE,
#endif
                                      _set_aud_bbe_mode_idx,
                                      _get_aud_bbe_mode_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

    /*  Dialogue Enhancer */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_dia_enhancer,
                                      MLM_MENU_KEY_DIALOGUE_ENHANCER,
                                      MLM_MENU_KEY_DIALOGUE_ENHANCER_HELP,
                                      MLM_MENU_KEY_DIALOGUE_ENHANCER_OFF,
                                      MLM_MENU_KEY_DIALOGUE_ENHANCER_HIGH,
                                      _set_aud_dialogue_enhancer_idx,
                                      _get_aud_dialogue_enhancer_idx);
    MENU_CHK_FAIL(i4_ret);

    /* earc*/
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_earc,
                                      MLM_MENU_KEY_EARC_MODE,
                                      MLM_MENU_KEY_EARC_MODE_HELP,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      a_set_cec_earc_idx,
                                      a_get_cec_earc_idx);

return MENUR_OK;

}


/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
INT32 menu_common_settings_init(VOID)
{
    INT32   i4_ret;
    INT16   i2_val_min;
    INT16   i2_val_max;
    UINT8   ui1_num_rec;

    /*-------------------------------------------------------------*/
    /*                           VIDEO                             */
    /*-------------------------------------------------------------*/
    menu_common_picture_settings_init();


    /*-------------------------------------------------------------*/
    /*                           AUDIO                             */
    /*-------------------------------------------------------------*/
    menu_common_audio_settings_init();

    /*-------------------------------------------------------------*/
    /*                            TV                               */
    /*-------------------------------------------------------------*/

    /* channel scan status */
    menu_page_tree_text_item(&t_g_menu_common_item_ch_scan_status,
                             MLM_MENU_KEY_EMPTY,
                             MLM_MENU_KEY_EMPTY,
                             a_get_ch_scan_status_text);
    /* Tuner Mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_tv_tuner_mode,
                                      MLM_MENU_KEY_TV_TUNER,
                                      MLM_MENU_KEY_HELP_TV_TUNER_MODE,
                                      MLM_MENU_KEY_CABLE,
                                      MLM_MENU_KEY_AIR,
                                      _set_tv_tuner_mode_idx,
                                      _get_tv_tuner_mode_idx);
    MENU_CHK_FAIL(i4_ret);

    /* DTV004334908 */
    /*i4_ret = menu_page_tree_list_item_set_elem_help_tip(&t_g_menu_common_item_tv_tuner_mode,
                                                       TRUE,
                                                       MLM_MENU_KEY_HELP_AIR,
                                                       MLM_MENU_KEY_HELP_CABLE);*/
    MENU_CHK_FAIL(i4_ret);

    /*-------------------------------------------------------------*/
    /*                           SETUP                             */
    /*-------------------------------------------------------------*/
    /* Blue mute */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_misc_blue_mute,
                                      MLM_MENU_KEY_BLUE_MUTE,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_misc_blue_mute_idx,
                                      _get_misc_blue_mute_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Sleep Timer */
    c_memset(&t_g_menu_common_item_misc_auto_sleep, 0, sizeof(MENU_ITEM_T));
    a_sleep_timer_get_num_rec(&ui1_num_rec);
    t_g_menu_common_item_misc_auto_sleep.e_item_type                   = MENU_ITEM_TYPE_LIST;
    //t_g_menu_common_item_misc_auto_sleep.ui2_msgid_menu_page           = MLM_MENU_KEY_TIME;
    t_g_menu_common_item_misc_auto_sleep.ui2_msgid_title               = MLM_MENU_KEY_TITLE_SLEEP_TIMER;
    t_g_menu_common_item_misc_auto_sleep.ui2_msgid_desc                = MLM_MENU_KEY_HELP_SLEEP_TIMER;
    t_g_menu_common_item_misc_auto_sleep.u.t_list.ui2_elem_num         = ui1_num_rec + 1;
    t_g_menu_common_item_misc_auto_sleep.u.t_list.pf_set_idx           = _set_misc_sleep_timer_idx;
    t_g_menu_common_item_misc_auto_sleep.u.t_list.pf_get_idx           = _get_misc_sleep_timer_idx;
    t_g_menu_common_item_misc_auto_sleep.u.t_list.pf_next_idx          = _next_misc_sleep_timer_idx;
    t_g_menu_common_item_misc_auto_sleep.u.t_list.pf_prev_idx          = _prev_misc_sleep_timer_idx;
    t_g_menu_common_item_misc_auto_sleep.u.t_list.pf_get_text          = _get_misc_sleep_timer_text;
    t_g_menu_common_item_misc_auto_sleep.u.t_list.ui2_msgid_elem_first = MLM_MENU_KEY_EMPTY;
    t_g_menu_common_item_misc_auto_sleep.u.t_list.ui2_msgid_elem_last  = MLM_MENU_KEY_EMPTY;

    /* Auto Power Off */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_dpms,
                                      MLM_MENU_KEY_AUTO_POWER_OFF,
                                      MLM_MENU_KEY_TAB_HELP_AUTO_POWER_OFF,
                                      MLM_MENU_KEY_AUTO_POWER_OFF_OFF,
                                      MLM_MENU_KEY_AUTO_POWER_OFF_10MIN,
                                      _set_dpms_idx,
                                      _get_dpms_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Screen Saver */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_scrn_saver,
                                      MLM_MENU_KEY_ITEM_SCRN_SAVER,
                                      MLM_MENU_KEY_HELP_TIP_SCRN_SAVER,
                                      MLM_MENU_KEY_SCRN_SAV_DISABLE,
                                      MLM_MENU_KEY_SCRN_SAV_20_MIN,
                                      _set_scrn_saver_idx,
                                      _get_scrn_saver_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Block Unrated */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_block_unrated,
                                      MLM_MENU_KEY_BLOCK_UNRATED,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_block_unrated_idx,
                                      _get_block_unrated_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Rating Enable */
    t_g_menu_common_item_rating_enable.e_item_type                   = MENU_ITEM_TYPE_LIST;
    t_g_menu_common_item_rating_enable.ui2_msgid_title               = MLM_MENU_KEY_RATING_ENABLE;
    t_g_menu_common_item_rating_enable.ui2_msgid_desc                = MLM_MENU_KEY_HELP_TIP_PARENT_RATING_ENABLE;
    t_g_menu_common_item_rating_enable.u.t_list.ui2_elem_num         = 2;
    t_g_menu_common_item_rating_enable.u.t_list.pf_set_idx           = _set_rating_enable_idx;
    t_g_menu_common_item_rating_enable.u.t_list.pf_get_idx           = _get_rating_enable_idx;
    t_g_menu_common_item_rating_enable.u.t_list.pf_next_idx          = NULL;
    t_g_menu_common_item_rating_enable.u.t_list.pf_prev_idx          = NULL;
    t_g_menu_common_item_rating_enable.u.t_list.pf_get_text          = _get_rating_enable_text;
    t_g_menu_common_item_rating_enable.u.t_list.ui2_msgid_elem_first = MLM_MENU_KEY_OFF;
    t_g_menu_common_item_rating_enable.u.t_list.ui2_msgid_elem_last  = MLM_MENU_KEY_ON;

    /* Burning Mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_burning_mode,
                                      MLM_MENU_KEY_BURNING_MODE,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_burning_mode_idx,
                                      _get_burning_mode_idx);
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_NAV_FLICKER_SUPPORT
    /* Flicker pattern */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_flicker_pattern,
                                      MLM_MENU_KEY_FLICKER_PATTERN,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_flicker_pattern_idx,
                                      _get_flicker_pattern_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
    /* Flicker pattern */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_tshift_mode,
                                      MLM_MENU_KEY_TSHIFT_MODE,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_TSHIFT_MODE_OFF,
#ifdef APP_NAV_REC_TSHIFT_AUTO_MODE_SUPPORT
                                      MLM_MENU_KEY_TSHIFT_MODE_AUTO,
#else
                                      MLM_MENU_KEY_TSHIFT_MODE_MNL,
#endif
                                      _set_tshift_mode_idx,
                                      _get_tshift_mode_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

    /*-------------------------------------------------------------*/
    /*                            VGA                              */
    /*-------------------------------------------------------------*/
    /* H. Position */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_H),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vga_pos_h,
                                       MLM_MENU_KEY_VGA_POS_H,
                                       MLM_MENU_KEY_HELP_TIP_TV_SETTING_CH_H_POS,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vga_pos_h_val,
                                       _get_vga_pos_h_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vga_pos_h.u.t_range.pf_incr = _incr_vga_pos_h;
    t_g_menu_common_item_vga_pos_h.u.t_range.pf_decr = _decr_vga_pos_h;

    /* V. Position */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_V),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vga_pos_v,
                                       MLM_MENU_KEY_VGA_POS_V,
                                       MLM_MENU_KEY_HELP_TIP_TV_SETTING_CH_V_POS,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vga_pos_v_val,
                                       _get_vga_pos_v_val);

    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vga_pos_v.u.t_range.pf_incr = _incr_vga_pos_v;
    t_g_menu_common_item_vga_pos_v.u.t_range.pf_decr = _decr_vga_pos_v;

    /* Phase */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_PHASE),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vga_phase,
                                       MLM_MENU_KEY_VGA_PHASE,
                                       MLM_MENU_KEY_HELP_TIP_TV_SETTING_FINE_TUNE,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vga_phase_val,
                                       _get_vga_phase_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vga_phase.u.t_range.pf_incr = _incr_vga_phase;
    t_g_menu_common_item_vga_phase.u.t_range.pf_decr = _decr_vga_phase;
    t_g_menu_common_item_vga_phase.u.t_range.b_fast_mode = FALSE;

    /* Clock */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_CLOCK),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_vga_clock,
                                       MLM_MENU_KEY_VGA_SIZE_H,
                                       MLM_MENU_KEY_TAB_HELP_RGB_H_SIZE,
                                       i2_val_min,
                                       i2_val_max,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_vga_clock_val,
                                       _get_vga_clock_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_vga_clock.u.t_range.pf_incr = _incr_vga_clock;
    t_g_menu_common_item_vga_clock.u.t_range.pf_decr = _decr_vga_clock;
    t_g_menu_common_item_vga_clock.u.t_range.b_fast_mode = FALSE;

    /*-------------------------------------------------------------*/
    /*                           PIP                               */
    /*-------------------------------------------------------------*/
#if defined(APP_PIP_POP_CTRL) || defined(APP_PIP_SETTINGS_IN_MENU)
    /* PIP Mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_pip_mode,
                                      MLM_MENU_KEY_PIP_MODE,
                                      MLM_MENU_KEY_PIP_MODE,
                                      MLM_MENU_KEY_PIP_MODE_OFF,
                                      MLM_MENU_KEY_PIP_MODE_POP,
                                      _set_pip_mode_idx,
                                      _get_pip_mode_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifdef APP_PIP_POP_CTRL
    /* PIP Source */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_pip_src_ex,
                                      MLM_MENU_KEY_AUDIO_SOURCE,
                                      MLM_MENU_KEY_AUDIO_SOURCE,
                                      MLM_MENU_KEY_AUDIO_SOURCE_MAIN_SCREEN,
                                      MLM_MENU_KEY_AUDIO_SOURCE_SUB_SCREEN,
                                      _set_pip_src_ex_idx,
                                      _get_pip_src_ex_idx);
    MENU_CHK_FAIL(i4_ret);

    /* PIP Position */
    i4_ret = menu_page_tree_listbox_item(&t_g_menu_common_item_pip_pos_ex,
                                         MLM_MENU_KEY_POSITION,
                                         MLM_MENU_KEY_POSITION,
                                         MLM_MENU_KEY_POSITION_TOP_LEFT,
                                         MLM_MENU_KEY_POSITION_BOTTOM_RIGHT,
                                         _set_pip_pos_ex_idx,
                                         _get_pip_pos_ex_idx);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_listbox_item_set_elem_help_tip(&t_g_menu_common_item_pip_pos_ex,
                                                           TRUE,
                                                           MLM_MENU_KEY_POSITION_TOP_LEFT,
                                                           MLM_MENU_KEY_POSITION_BOTTOM_RIGHT);
    MENU_CHK_FAIL(i4_ret);

    /* PIP Size */
    i4_ret = menu_page_tree_listbox_item(&t_g_menu_common_item_pip_size_ex,
                                         MLM_MENU_KEY_SIZE,
                                         MLM_MENU_KEY_SIZE,
                                         MLM_MENU_KEY_SIZE_LEVEL_SMALL,
                                         MLM_MENU_KEY_SIZE_LEVEL_LARGE,
                                         _set_pip_size_ex_idx,
                                         _get_pip_size_ex_idx);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_listbox_item_set_elem_help_tip(&t_g_menu_common_item_pip_size_ex,
                                                           TRUE,
                                                           MLM_MENU_KEY_SIZE_LEVEL_SMALL,
                                                           MLM_MENU_KEY_SIZE_LEVEL_LARGE);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifdef APP_PIP_SETTINGS_IN_MENU
    UINT8   ui1_num_rec;
    /* PIP Source */
    a_isl_get_num_rec(&ui1_num_rec);
    t_g_menu_common_item_pip_src.e_item_type                   = MENU_ITEM_TYPE_LIST;
    t_g_menu_common_item_pip_src.ui2_msgid_title               = MLM_MENU_KEY_PIP_SRC;
    t_g_menu_common_item_pip_src.ui2_msgid_desc                = MLM_MENU_KEY_EMPTY;
    t_g_menu_common_item_pip_src.u.t_list.ui2_elem_num         = ui1_num_rec;
    t_g_menu_common_item_pip_src.u.t_list.pf_set_idx           = _set_pip_src_idx;
    t_g_menu_common_item_pip_src.u.t_list.pf_get_idx           = _get_pip_src_idx;
    t_g_menu_common_item_pip_src.u.t_list.pf_next_idx          = _next_pip_src_idx;
    t_g_menu_common_item_pip_src.u.t_list.pf_prev_idx          = _prev_pip_src_idx;
    t_g_menu_common_item_pip_src.u.t_list.pf_get_text          = _get_pip_src_text;
    t_g_menu_common_item_pip_src.u.t_list.ui2_msgid_elem_first = 0;
    t_g_menu_common_item_pip_src.u.t_list.ui2_msgid_elem_last  = 0;

    /* PIP Position */
    a_isl_get_num_rec(&ui1_num_rec);
    t_g_menu_common_item_pip_pos.e_item_type                   = MENU_ITEM_TYPE_LIST;
    t_g_menu_common_item_pip_pos.ui2_msgid_title               = MLM_MENU_KEY_PIP_POS;
    t_g_menu_common_item_pip_pos.ui2_msgid_desc                = MLM_MENU_KEY_EMPTY;
    t_g_menu_common_item_pip_pos.u.t_list.ui2_elem_num         = ui1_num_rec;
    t_g_menu_common_item_pip_pos.u.t_list.pf_set_idx           = _set_pip_pos_idx;
    t_g_menu_common_item_pip_pos.u.t_list.pf_get_idx           = _get_pip_pos_idx;
    t_g_menu_common_item_pip_pos.u.t_list.pf_next_idx          = _next_pip_pos_idx;
    t_g_menu_common_item_pip_pos.u.t_list.pf_prev_idx          = _prev_pip_pos_idx;
    t_g_menu_common_item_pip_pos.u.t_list.pf_get_text          = _get_pip_pos_text;
    t_g_menu_common_item_pip_pos.u.t_list.ui2_msgid_elem_first = 0;
    t_g_menu_common_item_pip_pos.u.t_list.ui2_msgid_elem_last  = 0;

    /* PIP Size */
    a_isl_get_num_rec(&ui1_num_rec);
    t_g_menu_common_item_pip_size.e_item_type                   = MENU_ITEM_TYPE_LIST;
    t_g_menu_common_item_pip_size.ui2_msgid_title               = MLM_MENU_KEY_PIP_SIZE;
    t_g_menu_common_item_pip_size.ui2_msgid_desc                = MLM_MENU_KEY_EMPTY;
    t_g_menu_common_item_pip_size.u.t_list.ui2_elem_num         = ui1_num_rec;
    t_g_menu_common_item_pip_size.u.t_list.pf_set_idx           = _set_pip_size_idx;
    t_g_menu_common_item_pip_size.u.t_list.pf_get_idx           = _get_pip_size_idx;
    t_g_menu_common_item_pip_size.u.t_list.pf_next_idx          = _next_pip_size_idx;
    t_g_menu_common_item_pip_size.u.t_list.pf_prev_idx          = _prev_pip_size_idx;
    t_g_menu_common_item_pip_size.u.t_list.pf_get_text          = _get_pip_size_text;
    t_g_menu_common_item_pip_size.u.t_list.ui2_msgid_elem_first = 0;
    t_g_menu_common_item_pip_size.u.t_list.ui2_msgid_elem_last  = 0;
#endif /* APP_PIP_SETTINGS_IN_MENU */

#ifdef APP_NETWORK_SUPPORT
    /*-------------------------------------------------------------*/
    /*              Network Configuration                          */
    /*-------------------------------------------------------------*/
    /* Internet Connection */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_internet_connection,
                                      MLM_MENU_KEY_NET_CFG_CONN,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_net_connection_idx,
                                      _get_net_connection_idx);
    MENU_CHK_FAIL(i4_ret);


    /* DLNA Setting */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_dlna_setting,
                                      MLM_MENU_KEY_NET_CFG_DLNA,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_dlna_setting_idx,
                                      _get_dlna_setting_idx);
    MENU_CHK_FAIL(i4_ret);
#ifdef APP_DMR_SUPPORT
    /* DMR Setting */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_dlna_dmr_setting,
                                      MLM_MENU_KEY_NET_CFG_DLNA_DMR,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_dlna_dmr_setting_idx,
                                      _get_dlna_dmr_setting_idx);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_dlna_dmr_setting.u.t_list.pf_get_text = _get_dlna_dmr_setting_text;
#endif
#endif /* APP_NETWORK_SUPPORT */

    /*-------------------------------------------------------------*/
    /*                           Other                             */
    /*-------------------------------------------------------------*/
    /* Scan Mode */
#ifdef APP_MENU_WITH_SCAN_MODE
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_scan_mode,
                                      MLM_MENU_KEY_G_SM,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_G_SM_0,
                                      MLM_MENU_KEY_G_SM_2,
                                      _set_scan_mode_idx,
                                      _get_scan_mode_idx);
    MENU_CHK_FAIL(i4_ret);
#endif

    /* SPDIF */
    if(a_cfg_custom_get_OPTICAL_support() == FALSE)
    {
        i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_spdif,
                                      MLM_MENU_KEY_AUD_DIGITAL_AUDIO_OUT,
                                      MLM_MENU_KEY_MENU_HELP_TIP_AUDIO_DIG_AUD_OUT_OPT_NOT_SUPPORT,
                                      MLM_MENU_KEY_AUD_DIGITAL_OUT_AUTO,
                                     #if HIDE_SPDIF_AUDIO_OUT_BITSTREAM
                                      MLM_MENU_KEY_AUD_DIGITAL_OUT_DOLBY_D,
                                     #else
                                      MLM_MENU_KEY_AUD_DIGITAL_OUT_STREAM,
                                     #endif
                                      _set_aud_spdif_idx,
                                      _get_aud_spdif_idx);
    }
    else
    {
        i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_spdif,
                                      MLM_MENU_KEY_AUD_DIGITAL_AUDIO_OUT,
                                      MLM_MENU_KEY_HELP_TIP_AUDIO_DIG_AUD_OUT,
                                      MLM_MENU_KEY_AUD_DIGITAL_OUT_AUTO,
                                    #if HIDE_SPDIF_AUDIO_OUT_BITSTREAM
                                      MLM_MENU_KEY_AUD_DIGITAL_OUT_DOLBY_D,
                                    #else
                                      MLM_MENU_KEY_AUD_DIGITAL_OUT_STREAM,
                                    #endif

                                      _set_aud_spdif_idx,
                                      _get_aud_spdif_idx);
    }

#ifdef APP_SPDIF_DELAY_SUPPORT
    /* SPDIF Delay */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_SPDIF_DELAY),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);
    DBG_LOG_PRINT(("[spdif +++] {%s %s() %d}. i2_val_min = %d, i2_val_max = %d\n",__FILE__, __FUNCTION__, __LINE__,i2_val_min,i2_val_max));
    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_aud_spdif_delay,
                                      MLM_MENU_KEY_AUD_SPDIF_DELAY,
                                      MLM_MENU_KEY_EMPTY,
                                      i2_val_min,
                                      i2_val_max,
                                      MENU_ITEM_RANGE_STYLE_BAR,
                                      _set_aud_spdif_delay_val,
                                      _get_aud_spdif_delay_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_common_item_aud_spdif_delay.u.t_range.pf_incr = _incr_aud_spdif_delay;
    t_g_menu_common_item_aud_spdif_delay.u.t_range.pf_decr = _decr_aud_spdif_delay;
    t_g_menu_common_item_aud_spdif_delay.u.t_range.b_fast_mode = TRUE;

#endif

    /* TV Aspect Ratio */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_tv_ar,
                                      MLM_MENU_KEY_VID_TV_AR,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_VID_TV_AR_4_3,
                                      MLM_MENU_KEY_VID_TV_AR_16_9,
                                      _set_tv_ar_idx,
                                      _get_tv_ar_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Dolby Cert Mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_dolby_mode,
                                      MLM_MENU_KEY_DOLBY_CERT_MODE,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_DOLBY_CERT_MODE_0,
                                      MLM_MENU_KEY_DOLBY_CERT_MODE_1,
                                      _set_dolby_mode_idx,
                                      _get_dolby_mode_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Dolby Dynamic Range Compression */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_drc,
                                      MLM_MENU_KEY_DOLBY_DRC,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_DOLBY_DRC_OFF,
                                      MLM_MENU_KEY_DOLBY_DRC_FULL,
                                      _set_drc_idx,
                                      _get_drc_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Dolby Compression Mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_cmpss,
                                      MLM_MENU_KEY_DOLBY_CMPSS,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_DOLBY_CMPSS_LINE,
                                      MLM_MENU_KEY_DOLBY_CMPSS_RF,
                                      _set_cmpss_idx,
                                      _get_cmpss_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Dolby Downmix Mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_dmix,
                                      MLM_MENU_KEY_DOLBY_DMIX,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_DOLBY_DMIX_OFF,
                                      MLM_MENU_KEY_DOLBY_DMIX_STEREO,
                                      _set_dmix_idx,
                                      _get_dmix_idx);
    MENU_CHK_FAIL(i4_ret);

    /* audio bypass mode */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_aud_bypass_mode,
                                      MLM_MENU_KEY_AUD_BYPASS_MODE,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_aud_bypass_mode_idx,
                                      _get_aud_bypass_mode_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Auto Gain Control */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_agc,
                                      MLM_MENU_KEY_AUD_AGC,
                                      MLM_MENU_KEY_EMPTY,
                                      MLM_MENU_KEY_OFF,
                                      MLM_MENU_KEY_ON,
                                      _set_agc_idx,
                                      _get_agc_idx);
    MENU_CHK_FAIL(i4_ret);

    /* Audio latency */
    i4_ret = a_cfg_av_get_min_max(
        CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY),
        &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_aud_latency,
                                      MLM_MENU_KEY_AUD_LATENCY,
                                      MLM_MENU_KEY_HELP_LIP_SYNC,
                                      i2_val_min,
                                      i2_val_max,
                                      MENU_ITEM_RANGE_STYLE_BAR,
                                      _set_aud_latency_val,
                                      _get_aud_latency_val);

    MENU_CHK_FAIL(i4_ret);

    /* Audio latency for factory usage. Only update to driver. Do not store it to EEPROM. */

    i4_ret = menu_page_tree_range_item(&t_g_menu_common_item_fac_aud_latency,
                                      MLM_MENU_KEY_AUD_LATENCY,
                                      MLM_MENU_KEY_EMPTY,
                                      0,
                                      680,
                                      MENU_ITEM_RANGE_STYLE_BAR,
                                      _set_fac_aud_latency_val,
                                      _get_fac_aud_latency_val);

    MENU_CHK_FAIL(i4_ret);

#ifdef APP_LED_LOGO_CTRL

    /* LED LOGO CONTROL*/
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_led_logo_ctrl,
                                      MLM_MENU_KEY_TITLE_INDICATOR_LED,
                                      MLM_MENU_KEY_TAB_HELP_POWER_LIGHT,
                                      MLM_MENU_KEY_MENU_POWER_INDICATOR_OFF,
                                      MLM_MENU_KEY_MENU_POWER_INDICATOR_ON,
                                      _set_led_logo_ctrl_idx,
                                      _get_led_logo_ctrl_idx);
    MENU_CHK_FAIL(i4_ret);

i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_usb_power_ctrl,
                                  MLM_MENU_KEY_ITEM_USB_POWER,
                                  MLM_MENU_KEY_ITEM_USB_POWER_HELP_TEXT,
                                  MLM_MENU_KEY_ITEM_USB_POWER_ON,
                                  MLM_MENU_KEY_ITEM_USB_POWER_OFF,
                                  _set_usb_power_ctrl_idx,
                                  _get_usb_power_ctrl_idx);
MENU_CHK_FAIL(i4_ret);

#endif

#ifdef APP_TTS_SUPPORT
    /* LED LOGO CONTROL*/
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_talkback,
                                      MLM_MENU_KEY_TTS_TALKBACK,
                                      MLM_MENU_KEY_HELP_TIP_TALK_BACK,
                                      MLM_MENU_KEY_MENU_TALK_BACK_OFF,
                                      MLM_MENU_KEY_MENU_TALK_BACK_ON,
                                      _set_aud_tts_switch_idx,
                                      _get_aud_tts_switch_idx);
    /* LED LOGO CONTROL*/
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_speech_rate,
                                      MLM_MENU_KEY_TTS_TEXT_TO_SPEECH_REATE,
                                      MLM_MENU_KEY_HELP_TIP_SPEECH_RATE,
                                      MLM_MENU_KEY_TTS_SLOW,
                                      MLM_MENU_KEY_TTS_FAST,
                                      _set_aud_tts_speed_idx,
                                      _get_aud_tts_speed_idx);
#endif
 
    init_power_on_input();
    get_power_on_input_idx();

    INT16 i2_enty_count = get_power_on_input_idx_count();
    
    i4_ret = menu_page_tree_list_item_by_text(&t_g_menu_common_item_power_on_input,
                                          MLM_MENU_KEY_POWER_ON_INPUT,
                                          MLM_MENU_KEY_HELP_POWER_ON_INPUT,
                                          i2_enty_count,
                                          set_power_on_input_idx_from_menu,
                                          get_power_on_input_idx,
                                          get_power_on_mode_text);

    /* ZOOM MODE */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_zoom_mode,
                                      MLM_MENU_KEY_ACCESS_ZOOM_MODE,
                                      MLM_MENU_KEY_HELP_TIP_ZOOM_MODE,
                                      MLM_MENU_KEY_MENU_TALK_BACK_OFF,
                                      MLM_MENU_KEY_MENU_TALK_BACK_ON,
                                      _set_osd_zoom_mode_idx,
                                      _get_osd_zoom_mode_idx);

    /* VIDOE DESCRIPTION */
    i4_ret = menu_page_tree_list_item(&t_g_menu_common_item_video_description_mode,
                                  MLM_MENU_KEY_VIDEO_DESCRIPTION_MODE,
                                  MLM_MENU_KEY_HELP_TIP_VIDEO_DESCRIPTION_MODE,
                                  MLM_MENU_KEY_MENU_TALK_BACK_OFF,
                                  MLM_MENU_KEY_MENU_TALK_BACK_ON,
                                  _set_vid_des_mode_idx,
                                  _get_vid_des_mode_idx);

    return MENUR_OK;
}
