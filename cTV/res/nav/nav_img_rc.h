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
 * $RCSfile: nav_img_rc.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/8 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: fad6e0fd4edaccd0084a192f40b2c916 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_IMG_RC_H_
#define _NAV_IMG_RC_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_common.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
extern WGL_IMG_T t_g_nav_hlt_bar_bmp;
extern WGL_IMG_T t_g_nav_volume_progress_bk_bmp;
extern WGL_IMG_T t_g_nav_ch_list_frame_bmp;
extern WGL_IMG_T t_g_nav_frame_bk_bmp;
extern WGL_IMG_T t_g_nav_volume_progress_bar_bmp;
extern WGL_IMG_T t_g_nav_cross_img;
extern WGL_IMG_T t_g_nav_cc_box_bk_img;

#ifdef APP_NAV_CEC_SUPPORT
/*
extern WGL_IMG_T t_g_nav_cec_circle_img;
extern WGL_IMG_T t_g_nav_cec_wait_img;
extern WGL_IMG_T t_g_nav_cec_stop_img;
extern WGL_IMG_T t_g_nav_cec_fast_forward_img;
extern WGL_IMG_T t_g_nav_cec_fast_reverse_img;
extern WGL_IMG_T t_g_nav_cec_stop_resume_img;
*/
#endif /* APP_NAV_CEC_SUPPORT */


#define T_G_NAV_NO_REC_IMG_STYLE                        WGL_IMG_ST_NO_SEGMENT
#define T_G_NAV_HLT_BAR_BMP_STYLE                       WGL_IMG_ST_H_ONLY
#define T_G_NAV_VOLUME_PROGRESS_BK_BMP_STYLE            WGL_IMG_ST_HV
#define T_G_NAV_CH_LIST_FRAME_BMP_STYLE                 WGL_IMG_ST_HV
#define T_G_NAV_FRAME_BK_BMP_STYLE                      WGL_IMG_ST_HV
#define T_G_NAV_CH_BAR_BMP_STYLE                        WGL_IMG_ST_HV
#define T_G_NAV_VOLUME_PROGRESS_BAR_BMP_STYLE           WGL_IMG_ST_H_ONLY
#define T_G_NAV_CROSS_IMG_STYLE                         WGL_IMG_ST_NO_SEGMENT
#define T_G_NAV_NO_REC_AUDIO_IMG_STYLE                  WGL_IMG_ST_NO_SEGMENT
#define T_G_NAV_PROG_BAR_BMP_STYLE                      WGL_IMG_ST_HV
#define T_G_NAV_NO_REC_VIDEO_IMG_STYLE                  WGL_IMG_ST_NO_SEGMENT

extern WGL_IMG_T t_g_nav_banner_new_input_button_hover_img;
extern WGL_IMG_T t_g_nav_banner_new_input_button_default_img;
extern WGL_IMG_T t_g_nav_banner_new_lastshadow_img;

extern WGL_IMG_T t_g_nav_banner_new_bg_info_level_1_img;
extern WGL_IMG_T t_g_nav_banner_new_bg_info_level_2_img;
extern WGL_IMG_T t_g_nav_banner_new_bg_info_gradient_img;
extern WGL_IMG_T t_g_nav_banner_new_bg_info_toast_img;
extern WGL_IMG_T t_g_nav_banner_new_bg_info_toast_icon;
extern WGL_IMG_T t_g_nav_banner_new_bg_level2_icon;

extern WGL_IMG_T t_g_nav_banner_new_input_av_img;
extern WGL_IMG_T t_g_nav_banner_new_input_blueray_img;
extern WGL_IMG_T t_g_nav_banner_new_input_cable_img;
extern WGL_IMG_T t_g_nav_banner_new_input_hdmi_img;
extern WGL_IMG_T t_g_nav_banner_new_input_dvr_img;
extern WGL_IMG_T t_g_nav_banner_new_input_vcr_img;
extern WGL_IMG_T t_g_nav_banner_new_input_computer_img;
extern WGL_IMG_T t_g_nav_banner_new_input_satellite_img;
extern WGL_IMG_T t_g_nav_banner_new_input_dvd_img;
extern WGL_IMG_T t_g_nav_banner_new_input_audio_reciever_img;
extern WGL_IMG_T t_g_nav_banner_new_input_game_img;
extern WGL_IMG_T t_g_nav_banner_new_input_via_img;

extern WGL_IMG_T t_g_nav_banner_new_input_av_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_input_blueray_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_input_cable_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_input_hdmi_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_input_dvr_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_input_vcr_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_input_computer_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_input_satellite_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_input_dvd_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_input_audio_reciever_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_input_game_lt_img;

extern WGL_IMG_T t_g_nav_banner_new_aspect_normal_img;
extern WGL_IMG_T t_g_nav_banner_new_aspect_zoom_img;
extern WGL_IMG_T t_g_nav_banner_new_aspect_panoramic_img;
extern WGL_IMG_T t_g_nav_banner_new_aspect_wide_img;
extern WGL_IMG_T t_g_nav_banner_new_aspect_stretch_img;
extern WGL_IMG_T t_g_nav_banner_new_input_icon_base_pic;

extern WGL_IMG_T t_g_nav_banner_new_input_new_cast_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_new_component_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_new_computer_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_new_hdmi_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_new_satellite_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_new_box_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_new_dvd_blueray_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_new_game_pic;
extern WGL_IMG_T t_g_nav_banner_new_airplay_input_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_new_cast_aiyplay_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_new_component_aiyplay_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_new_hdmi_aiyplay_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_new_satellite_aiyplay_pic;
extern WGL_IMG_T t_g_nav_banner_new_input_tuner_aiyplay_img;

extern WGL_IMG_T t_g_nav_banner_new_aspect_normal_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_aspect_zoom_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_aspect_panoramic_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_aspect_wide_lt_img;
extern WGL_IMG_T t_g_nav_banner_new_aspect_stretch_lt_img;
extern WGL_IMG_T t_g_nav_input_demo_off_lt;

extern WGL_IMG_T t_g_nav_banner_new_resolution_480i_img;
extern WGL_IMG_T t_g_nav_banner_new_resolution_480p_img;
extern WGL_IMG_T t_g_nav_banner_new_resolution_720p_img;
extern WGL_IMG_T t_g_nav_banner_new_resolution_1080i_img;
extern WGL_IMG_T t_g_nav_banner_new_resolution_1080p_img;
extern WGL_IMG_T t_g_nav_banner_new_resolution_none_img;
extern WGL_IMG_T t_g_nav_banner_new_input_tuner_img;
/*
extern WGL_IMG_T t_g_nav_banner_new_wifi_level_0_img;
extern WGL_IMG_T t_g_nav_banner_new_wifi_level_1_img;
extern WGL_IMG_T t_g_nav_banner_new_wifi_level_2_img;
extern WGL_IMG_T t_g_nav_banner_new_wifi_level_3_img;
extern WGL_IMG_T t_g_nav_banner_new_wifi_level_4_img;
extern WGL_IMG_T t_g_nav_banner_new_wifi_level_5_img;
*/
extern WGL_IMG_T t_g_nav_banner_new_network_wifi_error_img;//jg_zhiquanwu
extern WGL_IMG_T t_g_nav_banner_new_network_wifi_0_img;
extern WGL_IMG_T t_g_nav_banner_new_network_wifi_1_img;
extern WGL_IMG_T t_g_nav_banner_new_network_wifi_2_img;
extern WGL_IMG_T t_g_nav_banner_new_network_wifi_3_img;
extern WGL_IMG_T t_g_nav_banner_new_network_wifi_4_img;

extern WGL_IMG_T t_g_nav_banner_dolby_audio_ver_icon;
extern WGL_IMG_T t_g_nav_banner_dolby_atmos_ver_icon;

extern WGL_IMG_T t_g_nav_banner_dolby_vision_vert_icon;
extern WGL_IMG_T t_g_banner_slider_icon_prg;
extern WGL_IMG_T t_g_banner_slider_icon_fmm;
extern WGL_IMG_T t_g_banner_slider_icon_freesync;
extern WGL_IMG_T t_g_banner_slider_icon_freesync_premium;//only for PX/P9
extern WGL_IMG_T t_g_banner_slider_icon_dolby_audio;
extern WGL_IMG_T t_g_banner_slider_icon_dolby_atmos;
extern WGL_IMG_T t_g_banner_slider_icon_dolby_vision;
extern WGL_IMG_T t_g_banner_slider_icon_v_gaming_engine;
extern WGL_IMG_T t_g_banner_slider_icon_hlg;
extern WGL_IMG_T t_g_banner_slider_icon_hdr10;


extern WGL_IMG_T t_g_nav_banner_new_ethernet_on_img_ex;
extern WGL_IMG_T t_g_nav_banner_new_ethernet_on_img;
extern WGL_IMG_T t_g_nav_banner_new_ethernet_off_img;
extern WGL_IMG_T t_g_nav_banner_new_ethernet_reconnect_img;

extern WGL_IMG_T t_g_nav_banner_cc_on;
extern WGL_IMG_T t_g_nav_banner_cc_off;
extern WGL_IMG_T t_g_nav_pin_no_match_img;
extern WGL_IMG_T t_g_nav_pin_down_img;
extern WGL_IMG_T t_g_nav_pin_cancel_focus_img;
extern WGL_IMG_T t_g_nav_pin_cancel_inactive_img;
extern WGL_IMG_T t_g_nav_pin_up_img;

extern WGL_IMG_T t_g_toast_msg_icon_arrow_up;
extern WGL_IMG_T t_g_toast_msg_icon_arrow_down;
extern WGL_IMG_T t_g_toast_msg_icon_ok_key;

extern WGL_HIMG_TPL_T h_g_nav_banner_new_lastshadow_img;

extern WGL_HIMG_TPL_T h_g_nav_banner_new_bg_info_level_1_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_bg_info_level_2_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_bg_info_gradient_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_bg_info_toast_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_bg_info_toast_icon;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_bg_level2_icon;

extern WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_480i_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_480p_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_720p_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_1080i_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_1080p_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_none_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_tuner_img;

extern WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_0_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_1_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_2_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_3_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_4_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_5_img;

extern WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_error_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_0_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_1_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_2_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_3_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_4_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_dolby_audio_ver_icon;
extern WGL_HIMG_TPL_T h_g_nav_banner_dolby_atmos_ver_icon;

extern WGL_HIMG_TPL_T h_g_nav_banner_dolby_vision_vert_icon;
extern WGL_HIMG_TPL_T h_g_banner_slider_icon_prg;
extern WGL_HIMG_TPL_T h_g_banner_slider_icon_fmm;
extern WGL_HIMG_TPL_T h_g_banner_slider_icon_freesync;
extern WGL_HIMG_TPL_T h_g_banner_slider_icon_dolby_audio;
extern WGL_HIMG_TPL_T h_g_banner_slider_icon_dolby_atmos;
extern WGL_HIMG_TPL_T h_g_banner_slider_icon_dolby_vision;
extern WGL_HIMG_TPL_T h_g_banner_slider_icon_v_gaming_engine;

extern WGL_HIMG_TPL_T h_g_banner_slider_icon_hlg;
extern WGL_HIMG_TPL_T h_g_banner_slider_icon_hdr10;



extern WGL_HIMG_TPL_T h_g_nav_banner_new_ethernet_on_img_ex;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_ethernet_on_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_ethernet_off_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_ethernet_reconnect_img;

extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_hdmi_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_cable_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_blueray_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_av_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_dvr_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_vcr_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_computer_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_satellite_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_dvd_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_audio_reciever_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_game_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_via_img;

extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_hdmi_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_cable_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_blueray_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_av_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_dvr_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_vcr_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_computer_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_satellite_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_dvd_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_audio_reciever_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_game_lt_img;

extern WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_normal_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_zoom_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_panoramic_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_wide_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_stretch_img;

extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_cast_pic;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_component_pic;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_computer_pic;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_hdmi_pic;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_satellite_pic;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_box_pic;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_dvd_blueray_pic;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_game_pic;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_dvd_pic;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_dvr_pic;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_airplay_pic;

extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_icon_base_pic;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_normal_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_zoom_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_panoramic_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_wide_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_stretch_lt_img;

extern WGL_HIMG_TPL_T h_g_nav_banner_new_input_off_lt_img;
extern WGL_HIMG_TPL_T h_g_nav_cc_on_img;
extern WGL_HIMG_TPL_T h_g_nav_cc_off_img;

#if (CUSTOMER == VIZIO)
extern WGL_HIMG_TPL_T h_g_nav_btui_headphones_40x40_img;
#endif

extern WGL_HIMG_TPL_T     h_g_nav_img_toast_msg_icon_arrow_up;
extern WGL_HIMG_TPL_T     h_g_nav_img_toast_msg_icon_arrow_down;


#if 1//Cedric
#define OSD_WIDTH		(1280)
#define OSD_HEIGHT		(720)
#define NAV_BANNER_DIVIDER_WGL_W		(2)//(2)
#define NAV_BANNER_DIVIDER_WGL_H		(55)

//level frm
#define NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_REL_W	(486)//(471)
#define NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W		(132)//(153)
#define NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_H		(NAV_BANNER_DIVIDER_WGL_H)
#define NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SX		(0)
#define NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SY		(0)
#define NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_EX		(960)
#define NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_EY		(160)

#define NAV_BANNER_LEVEL_1_INFO_FRM_WGL_W		(218)//(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W)
#define NAV_BANNER_LEVEL_1_INFO_FRM_WGL_H		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_H)
#define NAV_BANNER_LEVEL_1_INFO_FRM_WGL_SX		(960)//(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_EX + NAV_BANNER_DIVIDER_WGL_W)
#define NAV_BANNER_LEVEL_1_INFO_FRM_WGL_SY		(0)
#define NAV_BANNER_LEVEL_1_INFO_FRM_WGL_EX		(960)
#define NAV_BANNER_LEVEL_1_INFO_FRM_WGL_EY		(160)

#define NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_W	(132)//(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W)
#define NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_H	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_H)
#define NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_X_OFFSET	(8)
#define NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_SX	(960)//(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_EX + NAV_BANNER_DIVIDER_WGL_W + NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_X_OFFSET)
#define NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_SY	(0)
#define NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_EX	(960)
#define NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_EY	(160)

#define NAV_BANNER_LEVEL_2_FRM_WGL_W		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_REL_W)//(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W + NAV_BANNER_LEVEL_1_INFO_FRM_WGL_W + NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_W + (NAV_BANNER_DIVIDER_WGL_W * 2))
#define NAV_BANNER_LEVEL_2_FRM_WGL_H		(42 + 3)//(34)
#define NAV_BANNER_LEVEL_2_FRM_WGL_SX		0//(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SX)
#define NAV_BANNER_LEVEL_2_FRM_WGL_SY		160//(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_EY - 9)
#define NAV_BANNER_LEVEL_2_FRM_WGL_EX		1920//(NAV_BANNER_LEVEL_2_FRM_WGL_SX + NAV_BANNER_LEVEL_2_FRM_WGL_W)
#define NAV_BANNER_LEVEL_2_FRM_WGL_EY		280//(NAV_BANNER_LEVEL_2_FRM_WGL_SY + NAV_BANNER_LEVEL_2_FRM_WGL_H)

#define NAV_BANNER_LEVEL_3_FRM_WGL_W		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_REL_W)//(NAV_BANNER_LEVEL_2_FRM_WGL_W)
#define NAV_BANNER_LEVEL_3_FRM_WGL_H		(74)//(70)
#define NAV_BANNER_LEVEL_3_FRM_WGL_SX		500//(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SX)
#define NAV_BANNER_LEVEL_3_FRM_WGL_SY		160//(NAV_BANNER_LEVEL_2_FRM_WGL_EY)
#define NAV_BANNER_LEVEL_3_FRM_WGL_EX		1400//(NAV_BANNER_LEVEL_3_FRM_WGL_SX + NAV_BANNER_LEVEL_3_FRM_WGL_W)
#define NAV_BANNER_LEVEL_3_FRM_WGL_EY		280//(NAV_BANNER_LEVEL_3_FRM_WGL_SY + NAV_BANNER_LEVEL_3_FRM_WGL_H)

//Level 1 wgl
#define NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_W		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W)
#define NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_H		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_H / 2)
#define NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_SX		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SX)
#define NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_SY		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_EX		(NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_SX + NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_W)
#define NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_EY		(NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_SY + NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_H)

#if 1//Cedric 0604
#define NAV_BANNER_LEVEL_1_INPUT_NAME_WGL_X_OFFSET	(8)
#endif
#define NAV_BANNER_LEVEL_1_INPUT_NAME_WGL_W		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W)
#define NAV_BANNER_LEVEL_1_INPUT_NAME_WGL_H		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_H / 2)
#define NAV_BANNER_LEVEL_1_INPUT_NAME_WGL_SX		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SX)
#define NAV_BANNER_LEVEL_1_INPUT_NAME_WGL_SY		(NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_EY)
#define NAV_BANNER_LEVEL_1_INPUT_NAME_WGL_EX		(NAV_BANNER_LEVEL_1_INPUT_NAME_WGL_SX + NAV_BANNER_LEVEL_1_INPUT_NAME_WGL_W)
#define NAV_BANNER_LEVEL_1_INPUT_NAME_WGL_EY		(NAV_BANNER_LEVEL_1_INPUT_NAME_WGL_SY + NAV_BANNER_LEVEL_1_INPUT_NAME_WGL_H)

#if 1//Cedric 0604
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_LEFT_ADJ	(12)//(15)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_RIGHT_ADJ	(2)

#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_W	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_H	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_H / 2)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_SX	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SX)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_SY	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SY + NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_H)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_EX	(NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_SX + NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_W)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_EY	(NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_SY + NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_H)

#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_W	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_H	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_H / 2)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_SX	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SX)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_SY	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_EX	(NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_SX + NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_W)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_EY	(NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_SY + NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_H)
#else
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_W	( (NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W *2) /3)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_H	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_H / 2)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_SX	(NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_SX)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_SY	(NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_SY)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_EX	(NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_SX + NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_W)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_EY	(NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_SY + NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_H)

#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_W		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_W /3)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_H		(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_H / 2)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_SX	(NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_EX)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_SY	(NAV_BANNER_LEVEL_1_INPUT_ICON_WGL_SY)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_EX	(NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_SX + NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_W)
#define NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_EY	(NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_SY + NAV_BANNER_LEVEL_1_INPUT_CH_NUM_WGL_H)
#endif

#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_ICON_WGL_W		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_W / 4) // 1/4
#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_ICON_WGL_H			(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_H)
#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_ICON_WGL_SX		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_SX)
#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_ICON_WGL_SY		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_ICON_WGL_EX		(NAV_BANNER_LEVEL_1_INFO_RESOLUTION_ICON_WGL_SX + NAV_BANNER_LEVEL_1_INFO_RESOLUTION_ICON_WGL_W)
#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_ICON_WGL_EY		(NAV_BANNER_LEVEL_1_INFO_RESOLUTION_ICON_WGL_SY + NAV_BANNER_LEVEL_1_INFO_RESOLUTION_ICON_WGL_H)

#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_W		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_W / 4) // 1/4
#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_H		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_H)
#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_SX		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_SX)
#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_SY		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_EX		(NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_SX + NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_W)
#define NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_EY		(NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_SY + NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_H)


#define NAV_BANNER_LEVEL_1_INFO_TIME_APM_WGL_W		(30) // 2/4

#define NAV_BANNER_LEVEL_1_INFO_TIME_WGL_W		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_W / 2) // 2/4
#define NAV_BANNER_LEVEL_1_INFO_TIME_WGL_H		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_H)
#define NAV_BANNER_LEVEL_1_INFO_TIME_WGL_SX		(NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_EX)
#define NAV_BANNER_LEVEL_1_INFO_TIME_WGL_SY		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_1_INFO_TIME_WGL_EX		(NAV_BANNER_LEVEL_1_INFO_TIME_WGL_SX + NAV_BANNER_LEVEL_1_INFO_TIME_WGL_W)
#define NAV_BANNER_LEVEL_1_INFO_TIME_WGL_EY		(NAV_BANNER_LEVEL_1_INFO_TIME_WGL_SY + NAV_BANNER_LEVEL_1_INFO_TIME_WGL_H)

#define NAV_BANNER_LEVEL_1_INFO_TIME_APM_WGL_H		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_H/2)
#define NAV_BANNER_LEVEL_1_INFO_TIME_APM_WGL_SX		(NAV_BANNER_LEVEL_1_INFO_TIME_WGL_SX)
#define NAV_BANNER_LEVEL_1_INFO_TIME_APM_WGL_SY		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_1_INFO_TIME_APM_WGL_EX		(NAV_BANNER_LEVEL_1_INFO_TIME_APM_WGL_SX + NAV_BANNER_LEVEL_1_INFO_TIME_APM_WGL_W)
#define NAV_BANNER_LEVEL_1_INFO_TIME_APM_WGL_EY		(NAV_BANNER_LEVEL_1_INFO_TIME_APM_WGL_SY + NAV_BANNER_LEVEL_1_INFO_TIME_APM_WGL_H)

#define NAV_BANNER_LEVEL_1_INFO_WIFI_WGL_W		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_W / 4)
#define NAV_BANNER_LEVEL_1_INFO_WIFI_WGL_H		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_H)
#define NAV_BANNER_LEVEL_1_INFO_WIFI_WGL_SX		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_SX + (3 * NAV_BANNER_LEVEL_1_INFO_WIFI_WGL_W))
#define NAV_BANNER_LEVEL_1_INFO_WIFI_WGL_SY		(NAV_BANNER_LEVEL_1_INFO_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_1_INFO_WIFI_WGL_EX		(NAV_BANNER_LEVEL_1_INFO_WIFI_WGL_SX + NAV_BANNER_LEVEL_1_INFO_WIFI_WGL_W)
#define NAV_BANNER_LEVEL_1_INFO_WIFI_WGL_EY		(NAV_BANNER_LEVEL_1_INFO_WIFI_WGL_SY + NAV_BANNER_LEVEL_1_INFO_WIFI_WGL_H)

#define NAV_BANNER_LEVEL_1_ASPECT_ICON_WGL_W		(NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_W)
#define NAV_BANNER_LEVEL_1_ASPECT_ICON_WGL_H		(NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_H /2)
#define NAV_BANNER_LEVEL_1_ASPECT_ICON_WGL_SX		(NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_SX)
#define NAV_BANNER_LEVEL_1_ASPECT_ICON_WGL_SY		(NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_1_ASPECT_ICON_WGL_EX		(NAV_BANNER_LEVEL_1_ASPECT_ICON_WGL_SX + NAV_BANNER_LEVEL_1_ASPECT_ICON_WGL_W)
#define NAV_BANNER_LEVEL_1_ASPECT_ICON_WGL_EY		(NAV_BANNER_LEVEL_1_ASPECT_ICON_WGL_SY + NAV_BANNER_LEVEL_1_ASPECT_ICON_WGL_H)

#define NAV_BANNER_LEVEL_1_ASPECT_WGL_W		(NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_W)
#define NAV_BANNER_LEVEL_1_ASPECT_WGL_H		(NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_H /2)
#define NAV_BANNER_LEVEL_1_ASPECT_WGL_SX		(NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_SX)
#define NAV_BANNER_LEVEL_1_ASPECT_WGL_SY		(NAV_BANNER_LEVEL_1_ASPECT_ICON_WGL_EY)
#define NAV_BANNER_LEVEL_1_ASPECT_WGL_EX		(NAV_BANNER_LEVEL_1_ASPECT_WGL_SX + NAV_BANNER_LEVEL_1_ASPECT_WGL_W)
#define NAV_BANNER_LEVEL_1_ASPECT_WGL_EY		(NAV_BANNER_LEVEL_1_ASPECT_WGL_SY + NAV_BANNER_LEVEL_1_ASPECT_WGL_H)
//Level 2 wgl - divid 8
#define NAV_BANNER_LEVEL_2_PROG_TITLE_WGL_W			(155)// (118) cedric 0429
#define NAV_BANNER_LEVEL_2_PROG_TITLE_WGL_H			(NAV_BANNER_LEVEL_2_FRM_WGL_H)
#define NAV_BANNER_LEVEL_2_PROG_TITLE_WGL_SX		(NAV_BANNER_LEVEL_2_FRM_WGL_SX)//0301
#define NAV_BANNER_LEVEL_2_PROG_TITLE_WGL_SY		(NAV_BANNER_LEVEL_2_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_2_PROG_TITLE_WGL_EX		(NAV_BANNER_LEVEL_2_PROG_TITLE_WGL_SX + NAV_BANNER_LEVEL_2_PROG_TITLE_WGL_W)
#define NAV_BANNER_LEVEL_2_PROG_TITLE_WGL_EY		(NAV_BANNER_LEVEL_2_PROG_TITLE_WGL_SY + NAV_BANNER_LEVEL_2_PROG_TITLE_WGL_H)

#define NAV_BANNER_LEVEL_2_CC_WGL_W			(1)//(45) cedric 0429
#define NAV_BANNER_LEVEL_2_CC_WGL_H			(NAV_BANNER_LEVEL_2_FRM_WGL_H)
#define NAV_BANNER_LEVEL_2_CC_WGL_SX		(NAV_BANNER_LEVEL_2_PROG_TITLE_WGL_EX + NAV_BANNER_DIVIDER_WGL_W)
#define NAV_BANNER_LEVEL_2_CC_WGL_SY		(NAV_BANNER_LEVEL_2_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_2_CC_WGL_EX		(NAV_BANNER_LEVEL_2_CC_WGL_SX + NAV_BANNER_LEVEL_2_CC_WGL_W)
#define NAV_BANNER_LEVEL_2_CC_WGL_EY		(NAV_BANNER_LEVEL_2_CC_WGL_SY + NAV_BANNER_LEVEL_2_CC_WGL_H)

#define NAV_BANNER_LEVEL_2_RATED_WGL_W		(94)//(82) cedric 0429
#define NAV_BANNER_LEVEL_2_RATED_WGL_H		(NAV_BANNER_LEVEL_2_FRM_WGL_H)
#define NAV_BANNER_LEVEL_2_RATED_WGL_SX		(NAV_BANNER_LEVEL_2_CC_WGL_EX + NAV_BANNER_DIVIDER_WGL_W)
#define NAV_BANNER_LEVEL_2_RATED_WGL_SY		(NAV_BANNER_LEVEL_2_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_2_RATED_WGL_EX		(NAV_BANNER_LEVEL_2_RATED_WGL_SX + NAV_BANNER_LEVEL_2_RATED_WGL_W)
#define NAV_BANNER_LEVEL_2_RATED_WGL_EY		(NAV_BANNER_LEVEL_2_RATED_WGL_SY + NAV_BANNER_LEVEL_2_RATED_WGL_H)

#define NAV_BANNER_LEVEL_2_AUDIO_WGL_W		(114) //cedric 0429
#define NAV_BANNER_LEVEL_2_AUDIO_WGL_H		(NAV_BANNER_LEVEL_2_FRM_WGL_H)
#define NAV_BANNER_LEVEL_2_AUDIO_WGL_SX		(NAV_BANNER_LEVEL_2_RATED_WGL_EX + NAV_BANNER_DIVIDER_WGL_W)
#define NAV_BANNER_LEVEL_2_AUDIO_WGL_SY		(NAV_BANNER_LEVEL_2_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_2_AUDIO_WGL_EX		(NAV_BANNER_LEVEL_2_AUDIO_WGL_SX + NAV_BANNER_LEVEL_2_AUDIO_WGL_W)
#define NAV_BANNER_LEVEL_2_AUDIO_WGL_EY		(NAV_BANNER_LEVEL_2_AUDIO_WGL_SY + NAV_BANNER_LEVEL_2_AUDIO_WGL_H)

#define NAV_BANNER_LEVEL_2_PROG_TIME_WGL_W		(109)//(117) //cedric 0429
#define NAV_BANNER_LEVEL_2_PROG_TIME_WGL_H		(NAV_BANNER_LEVEL_2_FRM_WGL_H)
#define NAV_BANNER_LEVEL_2_PROG_TIME_WGL_SX		(NAV_BANNER_LEVEL_2_AUDIO_WGL_EX + NAV_BANNER_DIVIDER_WGL_W)
#define NAV_BANNER_LEVEL_2_PROG_TIME_WGL_SY		(NAV_BANNER_LEVEL_2_FRM_WGL_SY)
#define NAV_BANNER_LEVEL_2_PROG_TIME_WGL_EX		(NAV_BANNER_LEVEL_2_PROG_TIME_WGL_SX + NAV_BANNER_LEVEL_2_PROG_TIME_WGL_W)
#define NAV_BANNER_LEVEL_2_PROG_TIME_WGL_EY		(NAV_BANNER_LEVEL_2_PROG_TIME_WGL_SY + NAV_BANNER_LEVEL_2_PROG_TIME_WGL_H)
//Level 3 wgl
#define NAV_BANNER_LEVEL_3_PROG_DETAIL_WGL_W		(NAV_BANNER_LEVEL_3_FRM_WGL_W)// 2/8 orig is (312)
#define NAV_BANNER_LEVEL_3_PROG_DETAIL_WGL_H		(NAV_BANNER_LEVEL_3_FRM_WGL_H)
#define NAV_BANNER_LEVEL_3_PROG_DETAIL_WGL_SX		(NAV_BANNER_LEVEL_3_FRM_WGL_SX)
#define NAV_BANNER_LEVEL_3_PROG_DETAIL_WGL_SY		(NAV_BANNER_LEVEL_3_FRM_WGL_SY + NAV_BANNER_DIVIDER_WGL_W)
#define NAV_BANNER_LEVEL_3_PROG_DETAIL_WGL_EX		(NAV_BANNER_LEVEL_3_PROG_DETAIL_WGL_SX + NAV_BANNER_LEVEL_3_PROG_DETAIL_WGL_W)
#define NAV_BANNER_LEVEL_3_PROG_DETAIL_WGL_EY		(NAV_BANNER_LEVEL_3_PROG_DETAIL_WGL_SY + NAV_BANNER_LEVEL_3_PROG_DETAIL_WGL_H)

//root frm
#define NAV_BANNER_ROOT_FRM_WGL_X_OFFSET	(-1)
#define NAV_BANNER_ROOT_FRM_WGL_W	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_REL_W)
#define NAV_BANNER_ROOT_FRM_WGL_H	(NAV_BANNER_LEVEL_1_INPUT_FRM_WGL_H + NAV_BANNER_LEVEL_2_FRM_WGL_H + NAV_BANNER_LEVEL_3_FRM_WGL_H)//(214)

#define NAV_BANNER_ROOT_FRM_WGL_SX	(0)//(((OSD_WIDTH - NAV_BANNER_ROOT_FRM_WGL_W)/2) + NAV_BANNER_ROOT_FRM_WGL_X_OFFSET)
#define NAV_BANNER_ROOT_FRM_WGL_SY	(0)
#define NAV_BANNER_ROOT_FRM_WGL_EX	1920//(NAV_BANNER_ROOT_FRM_WGL_SX + NAV_BANNER_ROOT_FRM_WGL_W)
#define NAV_BANNER_ROOT_FRM_WGL_EY	440//(NAV_BANNER_ROOT_FRM_WGL_SY + NAV_BANNER_ROOT_FRM_WGL_H)
#endif

#endif /* _NAV_IMG_RC_H_ */
