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
#include "u_wgl.h"
#include "u_wgl_sets.h"
#include "c_wgl_image.h"
#include "c_handle.h"

#include "./banner_img.i"
#include "./banner_slider_icon.i"
#if (CUSTOMER == VIZIO)
#include "./ib_btaudio_s_image_8888.i"
#endif
#include "res/nav/nav_img_rc.h"
#include "rest/a_rest_api.h"
#include "res/nav/nav_dbg.h"

#define RET_ON_ERR(_expr) if(_expr !=0) {return -1;}

WGL_HIMG_TPL_T h_g_banner_ch_bar_bmp = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_prog_bar_bmp = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_frame_bk_bmp = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_lock_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_caption_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_ttx_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_favorite_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_fav_full_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_arrow_up_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_arrow_down_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_ad_ear_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_ad_eye_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_banner_3d_bar_bmp = NULL_HANDLE;

WGL_HIMG_TPL_T h_g_nav_banner_new_bg_info_level_1_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_bg_info_level_2_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_bg_info_gradient_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_bg_info_toast_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_bg_info_toast_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_bg_level2_icon = NULL_HANDLE;


WGL_HIMG_TPL_T h_g_nav_banner_new_lastshadow_img = NULL_HANDLE;

WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_480i_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_480p_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_720p_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_1080i_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_1080p_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_resolution_none_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_tuner_img = NULL_HANDLE;

WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_0_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_1_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_2_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_3_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_4_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_wifi_level_5_img = NULL_HANDLE;
WGL_HIMG_TPL_T at_img_signal_icon[5];

WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_error_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_0_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_1_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_2_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_3_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_network_wifi_4_img = NULL_HANDLE;
WGL_HIMG_TPL_T at_img_signal_icon1[5];

WGL_HIMG_TPL_T h_g_nav_banner_dolby_audio_ver_icon;
WGL_HIMG_TPL_T h_g_nav_banner_dolby_atmos_ver_icon;


WGL_HIMG_TPL_T h_g_nav_banner_dolby_vision_vert_icon;
WGL_HIMG_TPL_T h_g_banner_slider_icon_prg;
WGL_HIMG_TPL_T h_g_banner_slider_icon_fmm;
WGL_HIMG_TPL_T h_g_banner_slider_icon_freesync;
WGL_HIMG_TPL_T h_g_banner_slider_icon_dolby_audio;
WGL_HIMG_TPL_T h_g_banner_slider_icon_dolby_atmos;
WGL_HIMG_TPL_T h_g_banner_slider_icon_dolby_vision;
WGL_HIMG_TPL_T h_g_banner_slider_icon_v_gaming_engine;
WGL_HIMG_TPL_T h_g_banner_slider_icon_hlg;
WGL_HIMG_TPL_T h_g_banner_slider_icon_hdr10;



WGL_HIMG_TPL_T h_g_nav_banner_new_ethernet_on_img_ex= NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_ethernet_on_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_ethernet_off_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_ethernet_reconnect_img = NULL_HANDLE;

WGL_HIMG_TPL_T h_g_nav_banner_new_input_hdmi_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_cable_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_blueray_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_av_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_dvr_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_vcr_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_computer_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_satellite_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_dvd_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_audio_reciever_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_game_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_via_img = NULL_HANDLE;

WGL_HIMG_TPL_T h_g_nav_banner_new_input_hdmi_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_cable_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_blueray_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_av_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_dvr_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_vcr_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_computer_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_satellite_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_dvd_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_audio_reciever_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_game_lt_img = NULL_HANDLE;

WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_normal_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_zoom_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_panoramic_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_wide_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_stretch_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_icon_base_pic = NULL_HANDLE;

WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_cast_pic = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_component_pic = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_computer_pic = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_hdmi_pic = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_satellite_pic = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_box_pic = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_dvd_blueray_pic = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_game_pic = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_dvd_pic = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_new_dvr_pic = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_input_airplay_pic = NULL_HANDLE;

WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_normal_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_zoom_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_panoramic_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_wide_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_banner_new_aspect_stretch_lt_img = NULL_HANDLE;

WGL_HIMG_TPL_T h_g_nav_banner_new_input_off_lt_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_cc_on_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_cc_off_img = NULL_HANDLE;

#if (CUSTOMER == VIZIO)
WGL_HIMG_TPL_T h_g_nav_btui_headphones_40x40_img = NULL_HANDLE;
#endif

//check model series PX/P9
BOOL nav_banner_check_model_PX_P9(VOID)
{
    CHAR            s_model_name[32] = {0};
    CHAR            s_model_series[32] = {0};
    
    a_cfg_custom_get_model_name(s_model_name);

    if (c_strlen(s_model_name) == 0)
    {
        return FALSE;
    }
    if(c_strstr(s_model_name,"OLED")!=NULL || c_strstr(s_model_name,"oled")!=NULL) //ex: OLED55-H1->OLED
    {
        c_strcpy(s_model_series,"OLED");
    }
    else //ex:M556-H1 ->M6	P65Q9->P9 P65QX->PX  V505x-H1->V5x M706x-H3->M6x
    {
        s_model_series[0] = s_model_name[0]; //M V P
        if(s_model_name[3]=='Q' ||s_model_name[3]=='q') //P65Q9->P9
        {
            s_model_series[1] = s_model_name[4];
        }
        else //M556-H1
        {
            s_model_series[1] = s_model_name[3]; //5 6 7
            if(s_model_name[4]=='x' || s_model_name[4]=='X')//M706x-H3->M6x
            {
                s_model_series[2] = s_model_name[4];
            }
        }
    }

    if(c_strstr(s_model_series,"PX") || c_strstr(s_model_series,"P9"))
    {
        return TRUE;
    }

    return FALSE; 
}



INT32 nav_banner2_gen_init_image(VOID)
{
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_ch_bar_bmp,
            &h_g_banner_ch_bar_bmp));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_3d_bar_bmp,
            &h_g_banner_3d_bar_bmp));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_prog_bar_bmp,
            &h_g_banner_prog_bar_bmp));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY,
            &t_g_banner_frame_bk_bmp,
            &h_g_banner_frame_bk_bmp));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_lock_img,
            &h_g_banner_lock_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_caption_img,
            &h_g_banner_caption_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_ttx_img,
            &h_g_banner_ttx_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_favorite_img,
            &h_g_banner_favorite_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_fav_full_img,
            &h_g_banner_fav_full_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_arrow_up_img,
            &h_g_banner_arrow_up_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_arrow_down_img,
            &h_g_banner_arrow_down_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_ad_ear_img,
            &h_g_banner_ad_ear_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_ad_eye_img,
            &h_g_banner_ad_eye_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_bg_info_level_1_img,
            &h_g_nav_banner_new_bg_info_level_1_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_bg_info_level_2_img,
            &h_g_nav_banner_new_bg_info_level_2_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_bg_info_gradient_img,
            &h_g_nav_banner_new_bg_info_gradient_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_bg_info_toast_img,
            &h_g_nav_banner_new_bg_info_toast_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_bg_info_toast_icon,
            &h_g_nav_banner_new_bg_info_toast_icon));
	RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_bg_level2_icon,
            &h_g_nav_banner_new_bg_level2_icon));


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_lastshadow_img,
            &h_g_nav_banner_new_lastshadow_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_hdmi_img,
            &h_g_nav_banner_new_input_hdmi_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_cable_img,
            &h_g_nav_banner_new_input_cable_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_blueray_img,
            &h_g_nav_banner_new_input_blueray_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_av_img,
            &h_g_nav_banner_new_input_av_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_dvr_img,
            &h_g_nav_banner_new_input_dvr_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_vcr_img,
            &h_g_nav_banner_new_input_vcr_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_computer_img,
            &h_g_nav_banner_new_input_computer_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_satellite_img,
            &h_g_nav_banner_new_input_satellite_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_dvd_img,
            &h_g_nav_banner_new_input_dvd_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_audio_reciever_img,
            &h_g_nav_banner_new_input_audio_reciever_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_game_img,
            &h_g_nav_banner_new_input_game_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_via_img,
            &h_g_nav_banner_new_input_via_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_hdmi_lt_img,
            &h_g_nav_banner_new_input_hdmi_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_cable_lt_img,
            &h_g_nav_banner_new_input_cable_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_blueray_lt_img,
            &h_g_nav_banner_new_input_blueray_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_av_lt_img,
            &h_g_nav_banner_new_input_av_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_dvr_lt_img,
            &h_g_nav_banner_new_input_dvr_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_vcr_lt_img,
            &h_g_nav_banner_new_input_vcr_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_computer_lt_img,
            &h_g_nav_banner_new_input_computer_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_satellite_lt_img,
            &h_g_nav_banner_new_input_satellite_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_dvd_lt_img,
            &h_g_nav_banner_new_input_dvd_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_audio_reciever_lt_img,
            &h_g_nav_banner_new_input_audio_reciever_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_game_lt_img,
            &h_g_nav_banner_new_input_game_lt_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_aspect_normal_img,
            &h_g_nav_banner_new_aspect_normal_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_aspect_zoom_img,
            &h_g_nav_banner_new_aspect_zoom_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_aspect_panoramic_img,
            &h_g_nav_banner_new_aspect_panoramic_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_aspect_wide_img,
            &h_g_nav_banner_new_aspect_wide_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_aspect_stretch_img,
            &h_g_nav_banner_new_aspect_stretch_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_icon_base_pic,
            &h_g_nav_banner_new_input_icon_base_pic));
    if (a_rest_app_check_install_airplay())
    {
        RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_nav_banner_new_input_new_cast_aiyplay_pic,
                &h_g_nav_banner_new_input_new_cast_pic));
        RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_nav_banner_new_input_new_component_aiyplay_pic,
                &h_g_nav_banner_new_input_new_component_pic));
    }
    else
    {
        RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_nav_banner_new_input_new_cast_pic,
                &h_g_nav_banner_new_input_new_cast_pic));
        RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_nav_banner_new_input_new_component_pic,
                &h_g_nav_banner_new_input_new_component_pic));
    }

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_new_computer_pic,
            &h_g_nav_banner_new_input_new_computer_pic));
    if (a_rest_app_check_install_airplay())
    {
        RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_nav_banner_new_input_new_hdmi_aiyplay_pic,
                &h_g_nav_banner_new_input_new_hdmi_pic));
        RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_nav_banner_new_input_new_satellite_aiyplay_pic,
                &h_g_nav_banner_new_input_new_satellite_pic));
    }
    else
    {
        RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_nav_banner_new_input_new_hdmi_pic,
                &h_g_nav_banner_new_input_new_hdmi_pic));
        RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_nav_banner_new_input_new_satellite_pic,
                &h_g_nav_banner_new_input_new_satellite_pic));
    }
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_new_box_pic,
            &h_g_nav_banner_new_input_new_box_pic));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_new_dvd_blueray_pic,
            &h_g_nav_banner_new_input_new_dvd_blueray_pic));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_new_game_pic,
            &h_g_nav_banner_new_input_new_game_pic));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_new_dvd_blueray_pic,
            &h_g_nav_banner_new_input_new_dvd_pic));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_new_dvd_blueray_pic,
            &h_g_nav_banner_new_input_new_dvr_pic));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_airplay_input_pic,
            &h_g_nav_banner_new_input_airplay_pic));


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_aspect_normal_lt_img,
            &h_g_nav_banner_new_aspect_normal_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_aspect_zoom_lt_img,
            &h_g_nav_banner_new_aspect_zoom_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_aspect_panoramic_lt_img,
            &h_g_nav_banner_new_aspect_panoramic_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_aspect_wide_lt_img,
            &h_g_nav_banner_new_aspect_wide_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_aspect_stretch_lt_img,
            &h_g_nav_banner_new_aspect_stretch_lt_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_input_demo_off_lt,
            &h_g_nav_banner_new_input_off_lt_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_cc_on,
            &h_g_nav_cc_on_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_cc_off,
            &h_g_nav_cc_off_img));

#if (CUSTOMER == VIZIO)
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_btui_headphones_40x40_img,
            &h_g_nav_btui_headphones_40x40_img));
#endif

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_resolution_480i_img,
            &h_g_nav_banner_new_resolution_480i_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_resolution_480p_img,
            &h_g_nav_banner_new_resolution_480p_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_resolution_720p_img,
            &h_g_nav_banner_new_resolution_720p_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_resolution_1080i_img,
            &h_g_nav_banner_new_resolution_1080i_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_resolution_1080p_img,
            &h_g_nav_banner_new_resolution_1080p_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_resolution_none_img,
            &h_g_nav_banner_new_resolution_none_img));
    if (a_rest_app_check_install_airplay())
    {
        RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_nav_banner_new_input_tuner_aiyplay_img,
                &h_g_nav_banner_new_input_tuner_img));
    }
    else
    {
        RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_nav_banner_new_input_tuner_img,
                &h_g_nav_banner_new_input_tuner_img));
    }
    /*
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_wifi_level_0_img,
            &h_g_nav_banner_new_wifi_level_0_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_wifi_level_1_img,
            &h_g_nav_banner_new_wifi_level_1_img));
	at_img_signal_icon[0] = h_g_nav_banner_new_wifi_level_1_img;
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_wifi_level_2_img,
            &h_g_nav_banner_new_wifi_level_2_img));
	at_img_signal_icon[1] = h_g_nav_banner_new_wifi_level_2_img;
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_wifi_level_3_img,
            &h_g_nav_banner_new_wifi_level_3_img));
	at_img_signal_icon[2] = h_g_nav_banner_new_wifi_level_3_img;
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_wifi_level_4_img,
            &h_g_nav_banner_new_wifi_level_4_img));
	at_img_signal_icon[3] = h_g_nav_banner_new_wifi_level_4_img;
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_wifi_level_5_img,
            &h_g_nav_banner_new_wifi_level_5_img));
	at_img_signal_icon[4] = h_g_nav_banner_new_wifi_level_5_img;
    */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_network_wifi_error_img,
            &h_g_nav_banner_new_network_wifi_error_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_network_wifi_0_img,
            &h_g_nav_banner_new_network_wifi_0_img));
    at_img_signal_icon1[0] = h_g_nav_banner_new_network_wifi_0_img;

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_network_wifi_1_img,
            &h_g_nav_banner_new_network_wifi_1_img));
	at_img_signal_icon1[1] = h_g_nav_banner_new_network_wifi_1_img;

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_network_wifi_2_img,
            &h_g_nav_banner_new_network_wifi_2_img));
	at_img_signal_icon1[2] = h_g_nav_banner_new_network_wifi_2_img;

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_network_wifi_3_img,
            &h_g_nav_banner_new_network_wifi_3_img));
	at_img_signal_icon1[3] = h_g_nav_banner_new_network_wifi_3_img;

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_network_wifi_4_img,
            &h_g_nav_banner_new_network_wifi_4_img));
	at_img_signal_icon1[4] = h_g_nav_banner_new_network_wifi_4_img;

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_dolby_audio_ver_icon,
            &h_g_nav_banner_dolby_audio_ver_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_dolby_atmos_ver_icon,
            &h_g_nav_banner_dolby_atmos_ver_icon));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_dolby_vision_vert_icon,
            &h_g_nav_banner_dolby_vision_vert_icon));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_slider_icon_fmm,
            &h_g_banner_slider_icon_fmm));


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_slider_icon_prg,
            &h_g_banner_slider_icon_prg));
    
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            nav_banner_check_model_PX_P9() ? (&t_g_banner_slider_icon_freesync_premium) : (&t_g_banner_slider_icon_freesync),
            &h_g_banner_slider_icon_freesync));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_slider_icon_dolby_audio,
            &h_g_banner_slider_icon_dolby_audio));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_slider_icon_dolby_atmos,
            &h_g_banner_slider_icon_dolby_atmos));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_slider_icon_dolby_vision,
            &h_g_banner_slider_icon_dolby_vision));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_slider_icon_v_gaming_engine,
            &h_g_banner_slider_icon_v_gaming_engine));
    
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_slider_icon_hlg,
            &h_g_banner_slider_icon_hlg));
    
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_slider_icon_hdr10,
            &h_g_banner_slider_icon_hdr10));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_ethernet_on_img_ex,
            &h_g_nav_banner_new_ethernet_on_img_ex));
			
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_ethernet_on_img,
            &h_g_nav_banner_new_ethernet_on_img));

    /*RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_ethernet_off_img,
            &h_g_nav_banner_new_ethernet_off_img));*/

    h_g_nav_banner_new_ethernet_off_img = h_g_nav_banner_new_network_wifi_error_img;

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_ethernet_reconnect_img,
            &h_g_nav_banner_new_ethernet_reconnect_img));

    return 0;
}

INT32 nav_banner2_gen_deinit_image(VOID)
{
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_ch_bar_bmp));
    h_g_banner_ch_bar_bmp = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_3d_bar_bmp));
    h_g_banner_3d_bar_bmp = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_prog_bar_bmp));
    h_g_banner_prog_bar_bmp = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_frame_bk_bmp));
    h_g_banner_frame_bk_bmp = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_lock_img));
    h_g_banner_lock_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_caption_img));
    h_g_banner_caption_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_ttx_img));
    h_g_banner_ttx_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_favorite_img));
    h_g_banner_favorite_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_fav_full_img));
    h_g_banner_fav_full_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_arrow_up_img));
    h_g_banner_arrow_up_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_arrow_down_img));
    h_g_banner_arrow_down_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_ad_ear_img));
    h_g_banner_ad_ear_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_ad_eye_img));
    h_g_banner_ad_eye_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_bg_info_level_1_img));
    h_g_nav_banner_new_bg_info_level_1_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_bg_info_level_2_img));
    h_g_nav_banner_new_bg_info_level_2_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_bg_info_gradient_img));
    h_g_nav_banner_new_bg_info_gradient_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_bg_info_toast_img));
    h_g_nav_banner_new_bg_info_toast_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_bg_info_toast_icon));
    h_g_nav_banner_new_bg_info_toast_icon = NULL_HANDLE;
	RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_bg_level2_icon));
    h_g_nav_banner_new_bg_level2_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_lastshadow_img));
    h_g_nav_banner_new_lastshadow_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_hdmi_img));
    h_g_nav_banner_new_input_hdmi_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_cable_img));
    h_g_nav_banner_new_input_cable_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_blueray_img));
    h_g_nav_banner_new_input_blueray_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_av_img));
    h_g_nav_banner_new_input_av_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_dvr_img));
    h_g_nav_banner_new_input_dvr_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_vcr_img));
    h_g_nav_banner_new_input_vcr_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_computer_img));
    h_g_nav_banner_new_input_computer_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_satellite_img));
    h_g_nav_banner_new_input_satellite_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_dvd_img));
    h_g_nav_banner_new_input_dvd_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_audio_reciever_img));
    h_g_nav_banner_new_input_audio_reciever_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_game_img));
    h_g_nav_banner_new_input_game_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_via_img));
    h_g_nav_banner_new_input_via_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_hdmi_lt_img));
    h_g_nav_banner_new_input_hdmi_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_cable_lt_img));
    h_g_nav_banner_new_input_cable_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_blueray_lt_img));
    h_g_nav_banner_new_input_blueray_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_av_lt_img));
    h_g_nav_banner_new_input_av_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_dvr_lt_img));
    h_g_nav_banner_new_input_dvr_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_vcr_lt_img));
    h_g_nav_banner_new_input_vcr_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_computer_lt_img));
    h_g_nav_banner_new_input_computer_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_satellite_lt_img));
    h_g_nav_banner_new_input_satellite_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_dvd_lt_img));
    h_g_nav_banner_new_input_dvd_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_audio_reciever_lt_img));
    h_g_nav_banner_new_input_audio_reciever_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_game_lt_img));
    h_g_nav_banner_new_input_game_lt_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_aspect_normal_img));
    h_g_nav_banner_new_aspect_normal_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_aspect_zoom_img));
    h_g_nav_banner_new_aspect_zoom_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_aspect_panoramic_img));
    h_g_nav_banner_new_aspect_panoramic_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_aspect_wide_img));
    h_g_nav_banner_new_aspect_wide_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_aspect_stretch_img));
    h_g_nav_banner_new_aspect_stretch_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_icon_base_pic));
    h_g_nav_banner_new_input_icon_base_pic = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_new_cast_pic));
    h_g_nav_banner_new_input_new_cast_pic = NULL_HANDLE;
     RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_new_component_pic));
    h_g_nav_banner_new_input_new_component_pic = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_new_computer_pic));
    h_g_nav_banner_new_input_new_computer_pic = NULL_HANDLE;
     RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_new_hdmi_pic));
    h_g_nav_banner_new_input_new_hdmi_pic = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_new_satellite_pic));
    h_g_nav_banner_new_input_new_satellite_pic = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_aspect_normal_lt_img));
    h_g_nav_banner_new_aspect_normal_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_aspect_zoom_lt_img));
    h_g_nav_banner_new_aspect_zoom_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_aspect_panoramic_lt_img));
    h_g_nav_banner_new_aspect_panoramic_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_aspect_wide_lt_img));
    h_g_nav_banner_new_aspect_wide_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_aspect_stretch_lt_img));
    h_g_nav_banner_new_aspect_stretch_lt_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_off_lt_img));
    h_g_nav_banner_new_input_off_lt_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_resolution_480i_img));
    h_g_nav_banner_new_resolution_480i_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_resolution_480p_img));
    h_g_nav_banner_new_resolution_480p_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_resolution_720p_img));
    h_g_nav_banner_new_resolution_720p_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_resolution_1080i_img));
    h_g_nav_banner_new_resolution_1080i_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_resolution_1080p_img));
    h_g_nav_banner_new_resolution_1080p_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_resolution_none_img));
    h_g_nav_banner_new_resolution_none_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_input_tuner_img));
    h_g_nav_banner_new_input_tuner_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_wifi_level_0_img));
    h_g_nav_banner_new_wifi_level_0_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_wifi_level_1_img));
    h_g_nav_banner_new_wifi_level_1_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_wifi_level_2_img));
    h_g_nav_banner_new_wifi_level_2_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_wifi_level_3_img));
    h_g_nav_banner_new_wifi_level_3_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_wifi_level_4_img));
    h_g_nav_banner_new_wifi_level_4_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_wifi_level_5_img));
    h_g_nav_banner_new_wifi_level_5_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_network_wifi_error_img));
    h_g_nav_banner_new_network_wifi_error_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_network_wifi_0_img));
    h_g_nav_banner_new_network_wifi_0_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_network_wifi_1_img));
    h_g_nav_banner_new_network_wifi_1_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_network_wifi_2_img));
    h_g_nav_banner_new_network_wifi_2_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_network_wifi_3_img));
    h_g_nav_banner_new_network_wifi_3_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_network_wifi_4_img));
    h_g_nav_banner_new_network_wifi_4_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_ethernet_on_img_ex));
    h_g_nav_banner_new_ethernet_on_img_ex= NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_ethernet_on_img));
    h_g_nav_banner_new_ethernet_on_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_ethernet_off_img));
    h_g_nav_banner_new_ethernet_off_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_ethernet_reconnect_img));
    h_g_nav_banner_new_ethernet_on_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_new_ethernet_reconnect_img));
    h_g_nav_banner_new_ethernet_on_img_ex= NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_dolby_audio_ver_icon));
    h_g_nav_banner_dolby_audio_ver_icon= NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_dolby_atmos_ver_icon));
    h_g_nav_banner_dolby_atmos_ver_icon= NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_banner_dolby_vision_vert_icon));
    h_g_nav_banner_dolby_vision_vert_icon= NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_banner_slider_icon_dolby_vision));
    h_g_banner_slider_icon_dolby_vision= NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_cc_on_img));
    h_g_nav_cc_on_img = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_cc_off_img));
    h_g_nav_cc_off_img = NULL_HANDLE;

#if (CUSTOMER == VIZIO)
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_nav_btui_headphones_40x40_img));
    h_g_nav_btui_headphones_40x40_img = NULL_HANDLE;
#endif

    return 0;
}
