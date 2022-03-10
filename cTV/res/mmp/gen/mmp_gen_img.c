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

#include "./mmp_img_169.i"
#include "res/nav/nav_img_rc.h"

#define RET_ON_ERR(_expr) if(_expr !=0) {return -1;}

extern BOOL a_is_oled_compensation_support();

WGL_HIMG_TPL_T h_g_mmp_thumbnail_top_bg_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_detail_page_bg = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_list_mode_hl_bar = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_lstmod_icon_folder = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_btn_nr_bk = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_btn_hlt_bk = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_listmode_viewer_bg = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_MMP_Common_bg_top = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_err_frm_bk = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_thumbnail_mid_bg_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_icon_info = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_icon_urgent = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_icon_warning = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_info_bar_bg = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_back_btn_template = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_music_bg_template = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_floder_focus_hlt = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_img_sel_hlt = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_lg_btn_hlt = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_lg_btn = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_lg_folder_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_lg_folder_icon_small = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_now_playing_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_null_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pause_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pg_back_icon_dim = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pg_back_icon_nr = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pg_next_icon_dim = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pg_next_icon_nr = NULL_HANDLE;
#if 0
WGL_HIMG_TPL_T h_g_mmp_photo_bg_template = NULL_HANDLE;
#endif
WGL_HIMG_TPL_T h_g_mmp_previous_folder_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_previous_folder_icon_small = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_small_btn_hlt = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_small_btn = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_track_back_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_track_next_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_track_time_bar_fill = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_track_time_bar_outline = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_vizio_logo = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_video_outline = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_back_bar_hlt = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_back_bar_nr = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_lst_hlt = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_rotate_cw_hlt = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_rotate_ccw_hlt = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_bg_temp_no_thumb = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_bg_temp = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_photo_info_hlt = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_photo_rotate_cw = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_rotate_cw = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_rotate_ccw = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_photo_info = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_exculde_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_exculde_htl_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_video_player_pause_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_video_player_play_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_video_player_play_ff1_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_video_player_play_rw1_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_video_player_play_ff2_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_video_player_play_rw2_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_video_player_play_ff3_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_video_player_play_rw3_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_no_thumbnail = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_exclude_icon = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_pop_up_no_thumbnail_5x4 = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_photo_ex_bg_template = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_prev_focus_hlt = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_media_type_bg = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_dolbyAudio_Vert_white = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_dolbyVision_Vert_white = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_dolbyVision_Vert_white_Banner = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_dolbyAtmos_Vert_white = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_HLG_Vert_white = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_mmp_HDR10_Vert_white = NULL_HANDLE;

INT32 mmp_gen_init_image(VOID)
{
	BOOL B_OLED = FALSE;
	B_OLED = a_is_oled_compensation_support();

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_back_bar_hlt_oled : &t_g_mmp_back_bar_hlt,
            &h_g_mmp_back_bar_hlt));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_back_bar_oled : &t_g_mmp_back_bar_nr,
            &h_g_mmp_back_bar_nr));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_back_btn_oled : &t_g_mmp_back_btn_template,
            &h_g_mmp_back_btn_template));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pop_up_exclude_icon_oled : &t_g_mmp_pop_up_exclude_icon,
            &h_g_mmp_pop_up_exclude_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pop_up_exculde_htl_icon_oled : &t_g_mmp_pop_up_exculde_htl_icon,
            &h_g_mmp_pop_up_exculde_htl_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_floder_focus_hlt_oled : &t_g_mmp_floder_focus_hlt,
            &h_g_mmp_floder_focus_hlt));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_prev_focus_hlt_oled : &t_g_mmp_prev_focus_hlt,
            &h_g_mmp_prev_focus_hlt));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_img_sel_hlt_oled : &t_g_mmp_img_sel_hlt,
            &h_g_mmp_img_sel_hlt));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_lg_btn_hlt_oled : &t_g_mmp_lg_btn_hlt,
            &h_g_mmp_lg_btn_hlt));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_lg_folder_icon_oled : &t_g_mmp_lg_folder_icon,
            &h_g_mmp_lg_folder_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_lg_folder_icon_small_oled : &t_g_mmp_lg_folder_icon_small,
            &h_g_mmp_lg_folder_icon_small));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY,
            B_OLED ? &t_g_mmp_lst_hlt_oled : &t_g_mmp_lst_hlt,
            &h_g_mmp_lst_hlt));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_lstmod_icon_folder_oled : &t_g_mmp_lstmod_icon_folder,
            &h_g_mmp_lstmod_icon_folder));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pop_up_exculde_icon_oled : &t_g_mmp_pop_up_exculde_icon,
            &h_g_mmp_pop_up_exculde_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pop_up_photo_info_oled : &t_g_mmp_pop_up_photo_info,
            &h_g_mmp_pop_up_photo_info));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pop_up_rotate_ccw_oled : &t_g_mmp_pop_up_rotate_ccw,
            &h_g_mmp_pop_up_rotate_ccw));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pop_up_photo_rotate_cw_oled : &t_g_mmp_pop_up_photo_rotate_cw,
            &h_g_mmp_pop_up_photo_rotate_cw));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_music_bg_template_oled : &t_g_mmp_music_bg_template,
            &h_g_mmp_music_bg_template));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pop_up_no_thumbnail_oled : &t_g_mmp_pop_up_no_thumbnail,
            &h_g_mmp_pop_up_no_thumbnail));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pop_up_no_thumbnail_5x4_oled : &t_g_mmp_pop_up_no_thumbnail_5x4,
            &h_g_mmp_pop_up_no_thumbnail_5x4));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_now_playing_icon_oled : &t_g_mmp_now_playing_icon,
            &h_g_mmp_now_playing_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pause_icon_oled : &t_g_mmp_pause_icon,
            &h_g_mmp_pause_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pg_back_icon_nr_oled : &t_g_mmp_pg_back_icon_nr,
            &h_g_mmp_pg_back_icon_nr));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pg_next_icon_nr_oled : &t_g_mmp_pg_next_icon_nr,
            &h_g_mmp_pg_next_icon_nr));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_photo_ex_bg_template_oled : &t_g_mmp_photo_ex_bg_template,
            &h_g_mmp_photo_ex_bg_template));
#if 0
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_photo_bg_template_oled : &t_g_mmp_photo_bg_template,
            &h_g_mmp_photo_bg_template));
#endif
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pop_up_photo_info_hlt_oled : &t_g_mmp_pop_up_photo_info_hlt,
            &h_g_mmp_pop_up_photo_info_hlt));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_previous_folder_icon_oled : &t_g_mmp_previous_folder_icon,
            &h_g_mmp_previous_folder_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_previous_folder_icon_small_oled : &t_g_mmp_previous_folder_icon_small,
            &h_g_mmp_previous_folder_icon_small));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pop_up_rotate_cw_hlt_oled : &t_g_mmp_pop_up_rotate_cw_hlt,
            &h_g_mmp_pop_up_rotate_cw_hlt));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_pop_up_rotate_ccw_hlt_oled : &t_g_mmp_pop_up_rotate_ccw_hlt,
            &h_g_mmp_pop_up_rotate_ccw_hlt));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_small_btn_hlt_oled : &t_g_mmp_small_btn_hlt,
            &h_g_mmp_small_btn_hlt));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_track_back_icon_oled : &t_g_mmp_track_back_icon,
            &h_g_mmp_track_back_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_track_next_icon_oled : &t_g_mmp_track_next_icon,
            &h_g_mmp_track_next_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY,
            B_OLED ? &t_g_mmp_track_time_bar_fill_oled : &t_g_mmp_track_time_bar_fill,
            &h_g_mmp_track_time_bar_fill));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_video_outline_oled : &t_g_mmp_video_outline,
            &h_g_mmp_video_outline));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_video_player_pause_icon_oled : &t_g_mmp_video_player_pause_icon,
            &h_g_mmp_video_player_pause_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_video_player_play_ff1_icon_oled : &t_g_mmp_video_player_play_ff1_icon,
            &h_g_mmp_video_player_play_ff1_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_video_player_play_ff2_icon_oled : &t_g_mmp_video_player_play_ff2_icon,
            &h_g_mmp_video_player_play_ff2_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_video_player_play_ff3_icon_oled : &t_g_mmp_video_player_play_ff3_icon,
            &h_g_mmp_video_player_play_ff3_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_video_player_play_icon_oled : &t_g_mmp_video_player_play_icon,
            &h_g_mmp_video_player_play_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_video_player_play_rw1_icon_oled : &t_g_mmp_video_player_play_rw1_icon,
            &h_g_mmp_video_player_play_rw1_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_video_player_play_rw2_icon_oled : &t_g_mmp_video_player_play_rw2_icon,
            &h_g_mmp_video_player_play_rw2_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_video_player_play_rw3_icon_oled : &t_g_mmp_video_player_play_rw3_icon,
            &h_g_mmp_video_player_play_rw3_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            B_OLED ? &t_g_mmp_vizio_logo_oled : &t_g_mmp_vizio_logo,
            &h_g_mmp_vizio_logo));


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_thumbnail_top_bg_img,
            &h_g_mmp_thumbnail_top_bg_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_HV,
            &t_g_detail_page_bg,
            &h_g_detail_page_bg));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY,
            &t_g_mmp_list_mode_hl_bar,
            &h_g_mmp_list_mode_hl_bar));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY,
            &t_g_mmp_btn_nr_bk,
            &h_g_mmp_btn_nr_bk));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY,
            &t_g_mmp_btn_hlt_bk,
            &h_g_mmp_btn_hlt_bk));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_listmode_viewer_bg,
            &h_g_mmp_listmode_viewer_bg));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_MMP_Common_bg_top,
            &h_g_MMP_Common_bg_top));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_err_frm_bk,
            &h_g_mmp_err_frm_bk));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_thumbnail_mid_bg_img,
            &h_g_mmp_thumbnail_mid_bg_img));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_icon_info,
            &h_g_mmp_icon_info));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_icon_urgent,
            &h_g_mmp_icon_urgent));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_icon_warning,
            &h_g_mmp_icon_warning));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_HV,
            &t_g_mmp_info_bar_bg,
            &h_g_mmp_info_bar_bg));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_lg_btn,
            &h_g_mmp_lg_btn));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_null_icon,
            &h_g_mmp_null_icon));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_pg_back_icon_dim,
            &h_g_mmp_pg_back_icon_dim));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_pg_next_icon_dim,
            &h_g_mmp_pg_next_icon_dim));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_small_btn,
            &h_g_mmp_small_btn));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_HV,
            &t_g_mmp_track_time_bar_outline,
            &h_g_mmp_track_time_bar_outline));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_pop_up_bg_temp_no_thumb,
            &h_g_mmp_pop_up_bg_temp_no_thumb));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_pop_up_bg_temp,
            &h_g_mmp_pop_up_bg_temp));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_pop_up_rotate_cw,
            &h_g_mmp_pop_up_rotate_cw));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_mmp_media_type_bg,
            &h_g_mmp_media_type_bg));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_Dolby_Audio_116x43,
            &h_g_mmp_dolbyAudio_Vert_white));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_Dolby_Vision_116x43,
            &h_g_mmp_dolbyVision_Vert_white));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_banner_slider_icon_dolby_vision,
            &h_g_mmp_dolbyVision_Vert_white_Banner));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_Dolby_Atmos_116x43,
            &h_g_mmp_dolbyAtmos_Vert_white));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_HLG_Logo,
            &h_g_mmp_HLG_Vert_white));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_HDR10_Logo,
            &h_g_mmp_HDR10_Vert_white));
    return 0;
}

INT32 mmp_gen_deinit_image(VOID)
{
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_thumbnail_top_bg_img));
    h_g_mmp_thumbnail_top_bg_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_detail_page_bg));
    h_g_detail_page_bg = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_list_mode_hl_bar));
    h_g_mmp_list_mode_hl_bar = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_lstmod_icon_folder));
    h_g_mmp_lstmod_icon_folder = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_btn_nr_bk));
    h_g_mmp_btn_nr_bk = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_btn_hlt_bk));
    h_g_mmp_btn_hlt_bk = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_listmode_viewer_bg));
    h_g_mmp_listmode_viewer_bg = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_MMP_Common_bg_top));
    h_g_MMP_Common_bg_top = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_err_frm_bk));
    h_g_mmp_err_frm_bk = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_thumbnail_mid_bg_img));
    h_g_mmp_thumbnail_mid_bg_img = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_icon_info));
    h_g_mmp_icon_info = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_icon_urgent));
    h_g_mmp_icon_urgent = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_icon_warning));
    h_g_mmp_icon_warning = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_info_bar_bg));
    h_g_mmp_info_bar_bg = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_back_btn_template));
    h_g_mmp_back_btn_template = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_music_bg_template));
    h_g_mmp_music_bg_template = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_floder_focus_hlt));
    h_g_mmp_floder_focus_hlt = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_img_sel_hlt));
    h_g_mmp_img_sel_hlt = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_lg_btn_hlt));
    h_g_mmp_lg_btn_hlt = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_lg_btn));
    h_g_mmp_lg_btn = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_lg_folder_icon));
    h_g_mmp_lg_folder_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_lg_folder_icon_small));
    h_g_mmp_lg_folder_icon_small = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_now_playing_icon));
    h_g_mmp_now_playing_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_null_icon));
    h_g_mmp_null_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pause_icon));
    h_g_mmp_pause_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pg_back_icon_dim));
    h_g_mmp_pg_back_icon_dim = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pg_back_icon_nr));
    h_g_mmp_pg_back_icon_nr = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pg_next_icon_dim));
    h_g_mmp_pg_next_icon_dim = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pg_next_icon_nr));
    h_g_mmp_pg_next_icon_nr = NULL_HANDLE;

#if 0
    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_photo_bg_template));
    h_g_mmp_photo_bg_template = NULL_HANDLE;
#endif

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_previous_folder_icon));
    h_g_mmp_previous_folder_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_previous_folder_icon_small));
    h_g_mmp_previous_folder_icon_small = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_small_btn_hlt));
    h_g_mmp_small_btn_hlt = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_small_btn));
    h_g_mmp_small_btn = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_track_back_icon));
    h_g_mmp_track_back_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_track_next_icon));
    h_g_mmp_track_next_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_track_time_bar_fill));
    h_g_mmp_track_time_bar_fill = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_track_time_bar_outline));
    h_g_mmp_track_time_bar_outline = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_vizio_logo));
    h_g_mmp_vizio_logo = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_video_outline));
    h_g_mmp_video_outline = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_back_bar_hlt));
    h_g_mmp_back_bar_hlt = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_back_bar_nr));
    h_g_mmp_back_bar_nr = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_lst_hlt));
    h_g_mmp_lst_hlt = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_rotate_cw_hlt));
    h_g_mmp_pop_up_rotate_cw_hlt = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_rotate_ccw_hlt));
    h_g_mmp_pop_up_rotate_ccw_hlt = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_bg_temp_no_thumb));
    h_g_mmp_pop_up_bg_temp_no_thumb = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_bg_temp));
    h_g_mmp_pop_up_bg_temp = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_photo_info_hlt));
    h_g_mmp_pop_up_photo_info_hlt = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_photo_rotate_cw));
    h_g_mmp_pop_up_photo_rotate_cw = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_rotate_cw));
    h_g_mmp_pop_up_rotate_cw = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_rotate_ccw));
    h_g_mmp_pop_up_rotate_ccw = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_photo_info));
    h_g_mmp_pop_up_photo_info = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_exculde_icon));
    h_g_mmp_pop_up_exculde_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_exculde_htl_icon));
    h_g_mmp_pop_up_exculde_htl_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_video_player_pause_icon));
    h_g_mmp_video_player_pause_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_video_player_play_icon));
    h_g_mmp_video_player_play_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_video_player_play_ff1_icon));
    h_g_mmp_video_player_play_ff1_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_video_player_play_rw1_icon));
    h_g_mmp_video_player_play_rw1_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_video_player_play_ff2_icon));
    h_g_mmp_video_player_play_ff2_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_video_player_play_rw2_icon));
    h_g_mmp_video_player_play_rw2_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_video_player_play_ff3_icon));
    h_g_mmp_video_player_play_ff3_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_video_player_play_rw3_icon));
    h_g_mmp_video_player_play_rw3_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_no_thumbnail));
    h_g_mmp_pop_up_no_thumbnail = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_exclude_icon));
    h_g_mmp_pop_up_exclude_icon = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_pop_up_no_thumbnail_5x4));
    h_g_mmp_pop_up_no_thumbnail_5x4 = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_photo_ex_bg_template));
    h_g_mmp_photo_ex_bg_template = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_prev_focus_hlt));
    h_g_mmp_prev_focus_hlt = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_media_type_bg));
    h_g_mmp_media_type_bg = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_dolbyAudio_Vert_white));
    h_g_mmp_dolbyAudio_Vert_white = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_dolbyVision_Vert_white));
    h_g_mmp_dolbyVision_Vert_white = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_dolbyVision_Vert_white_Banner));
    h_g_mmp_dolbyVision_Vert_white_Banner = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_dolbyAtmos_Vert_white));
    h_g_mmp_dolbyAtmos_Vert_white = NULL_HANDLE;

	RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_HLG_Vert_white));
    h_g_mmp_HLG_Vert_white = NULL_HANDLE;

	RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_mmp_HDR10_Vert_white));
    h_g_mmp_HDR10_Vert_white = NULL_HANDLE;

    return 0;
}
