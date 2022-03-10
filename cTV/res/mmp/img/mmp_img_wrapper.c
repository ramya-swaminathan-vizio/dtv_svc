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
 * $RCSfile: mmp_img.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/4 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 6995d119ffe2091e31d2bc97171ebd19 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl_common.h"
#include "c_wgl_image.h"

#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"

#ifdef MMP_GUI_AUTHORING
#include "res/mmp/gen/mmp_gen_img.h"
#else
#ifdef APP_COLOR_MODE_PALLET
    #include "res/mmp/img/mmp_img_palette.i"
#else
    #include "res/mmp/img/mmp_img_169.i"    /* 16:9 images */
#endif
#endif

#include "res/mmp/img/mmp_img.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef struct __MMP_SHARE_RC_T
{
    INT32                       i4_init_count;
    WGL_HIMG_TPL_T              h_red_icon;
    WGL_HIMG_TPL_T              h_green_icon;
    WGL_HIMG_TPL_T              h_yellow_icon;
    WGL_HIMG_TPL_T              h_blue_icon;
    WGL_HIMG_TPL_T              h_play_icon;
    WGL_HIMG_TPL_T              h_pause_icon;
    WGL_HIMG_TPL_T              h_stop_icon;
    WGL_HIMG_TPL_T              h_prev_icon;
    WGL_HIMG_TPL_T              h_next_icon;
    WGL_HIMG_TPL_T              h_vol_icon;
    WGL_HIMG_TPL_T              h_vol_mute_icon;
    WGL_HIMG_TPL_T              h_vol_bar;
    WGL_HIMG_TPL_T              h_vol_bar_bg;
    WGL_HIMG_TPL_T              h_status_bar;
    WGL_HIMG_TPL_T              h_playback_pg_bar;
    WGL_HIMG_TPL_T              h_audio_main_frm;
    WGL_HIMG_TPL_T              h_tool_bar;
    WGL_HIMG_TPL_T              h_detail_page;
    WGL_HIMG_TPL_T              h_repeat_once_icon;
    WGL_HIMG_TPL_T              h_repeat_all_icon;
    WGL_HIMG_TPL_T              h_repeat_a_icon;
    WGL_HIMG_TPL_T              h_repeat_ab_icon;
    WGL_HIMG_TPL_T              h_repeat_abx_icon;
    WGL_HIMG_TPL_T              h_shuffle_icon;
    WGL_HIMG_TPL_T              h_fast_forward_icon;
    WGL_HIMG_TPL_T              h_fast_rewind_icon;
    WGL_HIMG_TPL_T              h_thumbnail_photo;
    WGL_HIMG_TPL_T              h_thumbnail_folder;
    WGL_HIMG_TPL_T              h_thumbnail_dlna_folder;
    WGL_HIMG_TPL_T              h_thumbnail_music;
    WGL_HIMG_TPL_T              h_detail_audio_icon;
    WGL_HIMG_TPL_T              h_highlight_thumbnail;
    WGL_HIMG_TPL_T              h_g_mmp_thumb_hl_m;
    WGL_HIMG_TPL_T              h_g_mmp_thumb_hl_l;
    WGL_HIMG_TPL_T              h_select_thumbnail;
    WGL_HIMG_TPL_T              h_copy_thumbnail;
    WGL_HIMG_TPL_T              h_thumbnail_top_bg;
    WGL_HIMG_TPL_T              h_thumbnail_btm_bg;
    WGL_HIMG_TPL_T              h_folder_icon;
    WGL_HIMG_TPL_T              h_music_icon;
    WGL_HIMG_TPL_T              h_photo_icon;
    WGL_HIMG_TPL_T              h_video_icon;
    WGL_HIMG_TPL_T              h_txt_icon; 
    WGL_HIMG_TPL_T              h_page_icon;
    WGL_HIMG_TPL_T              h_size_icon;
    WGL_HIMG_TPL_T              h_duration_icon;
    WGL_HIMG_TPL_T              h_scroll_bar_bk;
    WGL_HIMG_TPL_T              h_scroll_bar;
    WGL_HIMG_TPL_T              h_status_bar_play;
    WGL_HIMG_TPL_T              h_status_bar_pause;
    WGL_HIMG_TPL_T              h_music_play_icon;
    WGL_HIMG_TPL_T              h_read_only_icon;
    /*Added for video player*/
    WGL_HIMG_TPL_T              h_divx_btn_nor;
    WGL_HIMG_TPL_T              h_divx_btn_hlt;
    WGL_HIMG_TPL_T              h_divx_frm;
    WGL_HIMG_TPL_T              h_divx_top;
    WGL_HIMG_TPL_T              h_vp_repeat_all;
    WGL_HIMG_TPL_T              h_vp_repeat_once;
    WGL_HIMG_TPL_T              h_vp_repeat_single;
    WGL_HIMG_TPL_T              h_vp_stop;
    WGL_HIMG_TPL_T              h_vp_fast_forward;
    WGL_HIMG_TPL_T              h_vp_fast_reverse;
    WGL_HIMG_TPL_T              h_vp_no_fast_forward;
    WGL_HIMG_TPL_T              h_vp_no_fast_reverse;
    WGL_HIMG_TPL_T              h_vp_not_support;
    WGL_HIMG_TPL_T              h_vp_zoom;
    WGL_HIMG_TPL_T              h_vp_no_zoom;
    WGL_HIMG_TPL_T              h_vp_no_audio;
    WGL_HIMG_TPL_T              h_vp_subtitle;
    WGL_HIMG_TPL_T              h_vp_no_subtitle;
    WGL_HIMG_TPL_T              h_status_bar_no_pause;
    /*Added for music list mode */
    WGL_HIMG_TPL_T              h_g_mmp_list_mode_scroll_body;
    WGL_HIMG_TPL_T              h_g_mmp_list_mode_scroll_thumb;
    WGL_HIMG_TPL_T              h_g_mmp_list_mode_hl_bar;    
    WGL_HIMG_TPL_T              h_g_mmp_music_file_list_bk;
    WGL_HIMG_TPL_T              h_g_mmp_music_1_bk;
    WGL_HIMG_TPL_T              h_g_mmp_list_mode_music_2_bk;
    WGL_HIMG_TPL_T              h_g_mmp_lstmod_right_lb_title;
    WGL_HIMG_TPL_T              h_g_mmp_lstmod_right_lb_bk;
    WGL_HIMG_TPL_T              h_g_mmp_lstmod_bar_down_cursor;
    WGL_HIMG_TPL_T              h_g_mmp_lstmod_bar_top_cursor;
    WGL_HIMG_TPL_T              h_g_mmp_lstmod_bexclamation_mark;    
    WGL_HIMG_TPL_T              h_g_mmp_lstmod_icon_folder;
    
    /* music list toolbar icon */
    WGL_HIMG_TPL_T              h_music_list_enter;
    WGL_HIMG_TPL_T              h_music_list_exit;
    WGL_HIMG_TPL_T              h_music_list_menu;
    WGL_HIMG_TPL_T              h_music_list_select;
    WGL_HIMG_TPL_T              h_music_player_bk;
    WGL_HIMG_TPL_T              h_music_player_cover_pic_bk;
    
    
    /*listmode item status */
    WGL_HIMG_TPL_T              h_select_listmode;
    WGL_HIMG_TPL_T              h_copy_listmode;
    WGL_HIMG_TPL_T              h_g_mmp_btm_select_thumbnail;
    WGL_HIMG_TPL_T              h_g_mmp_btm_select_filter;
    WGL_HIMG_TPL_T              h_g_mmp_playing_repeat_one;
    WGL_HIMG_TPL_T              h_g_mmp_playing_repeat_all;
    WGL_HIMG_TPL_T              h_g_mmp_playing_a;
    WGL_HIMG_TPL_T              h_g_mmp_playing_ab;
    WGL_HIMG_TPL_T              h_g_mmp_playing_shuffle;
    WGL_HIMG_TPL_T              h_g_mmp_playing_play;
    WGL_HIMG_TPL_T              h_g_mmp_playing_pause;
    WGL_HIMG_TPL_T              h_g_mmp_playing_stop;
    WGL_HIMG_TPL_T              h_g_mmp_playing_ff;
    WGL_HIMG_TPL_T              h_g_mmp_playing_fr;
    WGL_HIMG_TPL_T              h_g_mmp_playing_vol_nor;
    WGL_HIMG_TPL_T              h_g_mmp_playing_vol_mute;   
    WGL_HIMG_TPL_T              h_g_mmp_thumbnail_load_fail_s;
    WGL_HIMG_TPL_T              h_g_mmp_thumbnail_load_fail_m;
    WGL_HIMG_TPL_T              h_g_mmp_thumbnail_load_fail_l;

    /* thumbnail size icon */
    WGL_HIMG_TPL_T              h_g_mmp_folder_l;
    WGL_HIMG_TPL_T              h_g_mmp_folder_m;
    WGL_HIMG_TPL_T              h_g_mmp_folder_s;
    WGL_HIMG_TPL_T              h_g_mmp_dlna_folder_l;
    WGL_HIMG_TPL_T              h_g_mmp_dlna_folder_m;
    WGL_HIMG_TPL_T              h_g_mmp_dlna_folder_s;
    WGL_HIMG_TPL_T              h_g_mmp_mnp_folder_l;
    WGL_HIMG_TPL_T              h_g_mmp_mnp_folder_m;
    WGL_HIMG_TPL_T              h_g_mmp_mnp_folder_s;    
    WGL_HIMG_TPL_T              h_g_mmp_audio_icon_l;
    WGL_HIMG_TPL_T              h_g_mmp_audio_icon_m;
    WGL_HIMG_TPL_T              h_g_mmp_audio_icon_s;
    WGL_HIMG_TPL_T              h_g_mmp_video_file_l;
    WGL_HIMG_TPL_T              h_g_mmp_video_file_m;
    WGL_HIMG_TPL_T              h_g_mmp_video_file_s;
    WGL_HIMG_TPL_T              h_g_mmp_photo_file_l;
    WGL_HIMG_TPL_T              h_g_mmp_photo_file_m;
    WGL_HIMG_TPL_T              h_g_mmp_photo_file_s;
    WGL_HIMG_TPL_T              h_g_mmp_text_file_l;
    WGL_HIMG_TPL_T              h_g_mmp_text_file_m;
    WGL_HIMG_TPL_T              h_g_mmp_text_file_s;

    WGL_HIMG_TPL_T              h_g_mmp_btm_exit;

    WGL_HIMG_TPL_T              h_g_mmp_frm_bk;
    WGL_HIMG_TPL_T              h_g_mmp_btn_nr_bk;
    WGL_HIMG_TPL_T              h_g_mmp_btn_hlt_bk;

    WGL_HIMG_TPL_T              h_g_mmp_track_time_bar_fill;

    WGL_HIMG_TPL_T              h_g_mmp_lm_play;
    WGL_HIMG_TPL_T              h_g_mmp_lm_pause;

} _MMP_SHARE_RC_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _MMP_SHARE_RC_T          t_g_share_rc;

WGL_HIMG_TPL_T                  ah_g_mmp_scanning_img [MMP_SCANNING_ANI_IMG_NUM];

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: mmp_img_init
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_img_init(VOID)
{
    _MMP_SHARE_RC_T*            pt_this = &t_g_share_rc;
    INT32                       i4_ret;

    /*check status*/
    if(pt_this->i4_init_count > 0)
    {
        pt_this->i4_init_count++;
        return MMPR_OK;
    }
    MMP_ASSERT(0 == pt_this->i4_init_count);


#ifdef MMP_GUI_AUTHORING
    i4_ret = mmp_gen_init_image();
    if (0 != i4_ret)
    {
        MMP_ASSERT(0);
        return MMPR_FAIL;
    }

    //pt_this->h_vol_icon = h_g_mmp_vol_icon_img;
    pt_this->h_status_bar = h_g_mmp_thumbnail_top_bg_img;
    //pt_this->h_tool_bar = h_g_mmp_thumbnail_btm_bg_img;
    pt_this->h_thumbnail_top_bg = h_g_mmp_thumbnail_top_bg_img;
#if 0
    pt_this->h_thumbnail_btm_bg = h_g_mmp_thumbnail_btm_bg_img;
    pt_this->h_thumbnail_folder = h_g_mmp_thumbnail_folder_img;
    pt_this->h_thumbnail_dlna_folder = h_g_mmp_thumbnail_dlna_folder_img;
    pt_this->h_thumbnail_music = h_g_mmp_thumbnail_music_img;
    pt_this->h_thumbnail_photo = h_g_mmp_thumbnail_photo_img;
    pt_this->h_highlight_thumbnail = h_g_mmp_highlight_thumbnail_img;
    pt_this->h_select_thumbnail = h_g_mmp_select_thumbnail_img;
    pt_this->h_copy_thumbnail = h_g_mmp_copy_thumbnail_img;
    pt_this->h_folder_icon = h_g_mmp_folder_icon_img;
    pt_this->h_music_icon = h_g_mmp_top_filter_audio_img;
    pt_this->h_photo_icon = h_g_mmp_top_filter_photo_img;
    pt_this->h_video_icon = h_g_mmp_top_filter_video_img;
    pt_this->h_txt_icon = h_g_mmp_top_filter_txt_img;   
    pt_this->h_page_icon = h_g_mmp_page_icon_img;
    pt_this->h_scroll_bar_bk = h_g_mmp_scroll_bar_bk_img;
    pt_this->h_scroll_bar = h_g_mmp_scroll_bar_img;
#endif
    pt_this->h_detail_page = h_g_detail_page_bg;
    //pt_this->h_g_mmp_list_mode_scroll_body = h_g_mmp_list_mode_scroll_body;
    //pt_this->h_g_mmp_list_mode_scroll_thumb = h_g_mmp_list_mode_scroll_thumb;
    pt_this->h_g_mmp_list_mode_hl_bar = h_g_mmp_list_mode_hl_bar;
    //pt_this->h_g_mmp_lstmod_bexclamation_mark = h_g_mmp_lstmod_bexclamation_mark;
    pt_this->h_g_mmp_lstmod_icon_folder = h_g_mmp_lstmod_icon_folder;
#if 0
    pt_this->h_music_list_enter = h_g_mmp_enter;
    pt_this->h_music_list_exit = h_g_mmp_exit;
    pt_this->h_music_list_menu = h_g_mmp_menu;
    pt_this->h_music_list_select = h_g_mmp_select;
    pt_this->h_select_listmode = h_g_mmp_select_listmode_img;
    pt_this->h_copy_listmode = h_g_mmp_copy_listmode_img;
    pt_this->h_g_mmp_folder_l = h_g_mmp_folder_l;
    pt_this->h_g_mmp_folder_m = h_g_mmp_folder_m;
    pt_this->h_g_mmp_folder_s = h_g_mmp_folder_s;
    pt_this->h_g_mmp_dlna_folder_l = h_g_mmp_dlna_folder_l;
    pt_this->h_g_mmp_dlna_folder_m = h_g_mmp_dlna_folder_m;
    pt_this->h_g_mmp_dlna_folder_s = h_g_mmp_dlna_folder_s;
    pt_this->h_g_mmp_mnp_folder_l = h_g_mmp_mnp_folder_l;
    pt_this->h_g_mmp_mnp_folder_m = h_g_mmp_mnp_folder_m;
    pt_this->h_g_mmp_mnp_folder_s = h_g_mmp_mnp_folder_s;  
    pt_this->h_g_mmp_audio_icon_l = h_g_mmp_audio_icon_l;
    pt_this->h_g_mmp_audio_icon_m = h_g_mmp_audio_icon_m;
    pt_this->h_g_mmp_audio_icon_s = h_g_mmp_audio_icon_s;
    pt_this->h_g_mmp_video_file_l = h_g_mmp_video_file_l;
    pt_this->h_g_mmp_video_file_m = h_g_mmp_video_file_m;
    pt_this->h_g_mmp_video_file_s = h_g_mmp_video_file_s;
    pt_this->h_g_mmp_photo_file_l = h_g_mmp_photo_file_l;
    pt_this->h_g_mmp_photo_file_m = h_g_mmp_photo_file_m;
    pt_this->h_g_mmp_photo_file_s = h_g_mmp_photo_file_s;	
    pt_this->h_g_mmp_text_file_l = h_g_mmp_text_file_l;
    pt_this->h_g_mmp_text_file_m = h_g_mmp_text_file_m;
    pt_this->h_g_mmp_text_file_s = h_g_mmp_text_file_s;
    #endif
    
    //pt_this->h_g_mmp_frm_bk       = h_g_mmp_frm_bk;
    pt_this->h_g_mmp_btn_nr_bk    = h_g_mmp_btn_nr_bk;
    pt_this->h_g_mmp_btn_hlt_bk   = h_g_mmp_btn_hlt_bk;
    //pt_this->h_g_mmp_btm_select_thumbnail = h_g_mmp_btm_select_img;
    //pt_this->h_g_mmp_btm_select_filter = h_g_mmp_btm_select_filter_img;
    
#if 0
    pt_this->h_g_mmp_thumb_hl_m = h_g_mmp_highlight_m_thumbnail_img;
    pt_this->h_g_mmp_thumb_hl_l = h_g_mmp_highlight_l_thumbnail_img;
    pt_this->h_g_mmp_playing_repeat_one = h_g_mmp_cur_player_repeat_one_img;
    pt_this->h_g_mmp_playing_repeat_all = h_g_mmp_cur_player_repeat_all_img;
    pt_this->h_g_mmp_playing_shuffle = h_g_mmp_cur_player_shuffle_img;
    pt_this->h_g_mmp_playing_a = h_g_mmp_cur_player_a_img;
    pt_this->h_g_mmp_playing_ab = h_g_mmp_cur_player_ab_img;    
    pt_this->h_g_mmp_playing_play = h_g_mmp_cur_player_play_img;
    pt_this->h_g_mmp_playing_pause = h_g_mmp_cur_player_pause_img;
    pt_this->h_g_mmp_playing_stop = h_g_mmp_cur_player_stop_img;   
    pt_this->h_g_mmp_playing_ff = h_g_mmp_cur_player_ff_img;
    pt_this->h_g_mmp_playing_fr = h_g_mmp_cur_player_fr_img;
    pt_this->h_g_mmp_playing_vol_nor = h_g_mmp_tm_player_vol_icon;
    pt_this->h_g_mmp_playing_vol_mute = h_g_mmp_tm_player_mute;   
    pt_this->h_g_mmp_thumbnail_load_fail_s = h_g_mmp_thumbnail_load_fail_s_img;
    pt_this->h_g_mmp_thumbnail_load_fail_m = h_g_mmp_thumbnail_load_fail_m_img;
    pt_this->h_g_mmp_thumbnail_load_fail_l = h_g_mmp_thumbnail_load_fail_l_img;
    pt_this->h_g_mmp_btm_exit = h_g_mmp_btm_exit_img;
#endif
    pt_this->h_g_mmp_lm_play  = h_g_mmp_now_playing_icon;
    pt_this->h_g_mmp_lm_pause = h_g_mmp_pause_icon;
#if 0
    pt_this->h_music_player_bk = h_g_mmp_audio_bg_img;
    pt_this->h_music_player_cover_pic_bk = h_g_mmp_audio_cover_bg_img;
    pt_this->h_music_player_bk = h_g_MMP_Common_bg_Middle_H;
    pt_this->h_music_player_cover_pic_bk = h_g_MMP_Common_bg_Middle_H;
#endif       
    pt_this->h_g_mmp_track_time_bar_fill = h_g_mmp_track_time_bar_fill;
#else
    /*red icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_clr_key_red_icon_img, &pt_this->h_red_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_red_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*green icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_clr_key_green_icon_img, &pt_this->h_green_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_green_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*yellow icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_clr_key_yellow_icon_img, &pt_this->h_yellow_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_yellow_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*blue icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_clr_key_blue_icon_img, &pt_this->h_blue_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_blue_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*play icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_play_icon_img, &pt_this->h_play_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_play_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*pause icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_pause_icon_img, &pt_this->h_pause_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_pause_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*stop icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_stop_icon_img, &pt_this->h_stop_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_stop_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*prev icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_prev_icon_img, &pt_this->h_prev_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_prev_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*next icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_next_icon_img, &pt_this->h_next_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_next_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*vol icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vol_icon_img, &pt_this->h_vol_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_vol_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*vol mute icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vol_mute_icon_img, &pt_this->h_vol_mute_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_vol_mute_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*vol bar bg*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY, &t_g_mmp_vol_bar_bg_img, &pt_this->h_vol_bar_bg);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_vol_bar_bg = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*vol bar*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY, &t_g_mmp_vol_bar_img, &pt_this->h_vol_bar);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_vol_bar = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*status bar*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY, &t_g_mmp_thumbnail_top_bg_img, &pt_this->h_status_bar);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_status_bar = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*tool bar*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY, &t_g_mmp_thumbnail_btm_bg_img, &pt_this->h_tool_bar);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_tool_bar = NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    /*thumbnail top bg */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY, &t_g_mmp_thumbnail_top_bg_img, &pt_this->h_thumbnail_top_bg);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_thumbnail_top_bg = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*thumbnail btm bg */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY, &t_g_mmp_thumbnail_btm_bg_img, &pt_this->h_thumbnail_btm_bg);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_thumbnail_btm_bg = NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    /*thumbnail folder */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_thumbnail_folder_img, &pt_this->h_thumbnail_folder);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_thumbnail_folder = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*thumbnail dlna folder */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_thumbnail_dlna_folder_img, &pt_this->h_thumbnail_dlna_folder);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_thumbnail_dlna_folder = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*thumbnail music */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_thumbnail_music_img, &pt_this->h_thumbnail_music);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_thumbnail_music = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*thumbnail photo */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_thumbnail_photo_img, &pt_this->h_thumbnail_photo);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_thumbnail_photo = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*detail audio */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_detail_audio_img, &pt_this->h_detail_audio_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_detail_audio_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*highlight thumbnail */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_mmp_highlight_thumbnail_img, &pt_this->h_highlight_thumbnail);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_highlight_thumbnail = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*select thumbnail */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_mmp_select_thumbnail_img, &pt_this->h_select_thumbnail);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_select_thumbnail = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*copy thumbnail */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_mmp_copy_thumbnail_img, &pt_this->h_copy_thumbnail);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_copy_thumbnail = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*select listmode */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_mmp_select_listmode_img, &pt_this->h_select_listmode);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_select_listmode = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*copy listmode */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_mmp_copy_listmode_img, &pt_this->h_copy_listmode);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_copy_listmode = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*folder icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_folder_icon_img, &pt_this->h_folder_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_folder_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*music icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_music_icon_img, &pt_this->h_music_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_music_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*photo icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_photo_icon_img, &pt_this->h_photo_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_photo_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*page icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_page_icon_img, &pt_this->h_page_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_page_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*size icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_size_icon_img, &pt_this->h_size_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_size_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*duration icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_duration_icon_img, &pt_this->h_duration_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_duration_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*scroll bar bk*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_V_ONLY, &t_g_mmp_scroll_bar_bk_img, &pt_this->h_scroll_bar_bk);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_scroll_bar_bk = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*scroll bar */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_V_ONLY, &t_g_mmp_scroll_bar_img, &pt_this->h_scroll_bar);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_scroll_bar = NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    /* status bar play icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_status_bar_play_img, &pt_this->h_status_bar_play);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_status_bar_play = NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    /* status bar pause icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_status_bar_pause_img, &pt_this->h_status_bar_pause);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_status_bar_pause = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*detail page*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_detail_page_bg, &pt_this->h_detail_page);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_detail_page = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /* music play icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_music_play_img, &pt_this->h_music_play_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_music_play_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /* read only  icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_read_only, &pt_this->h_read_only_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_read_only_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*repeat_once icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_repeat_once_icon_img, &pt_this->h_repeat_once_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_repeat_once_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*repeat_all icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_repeat_all_icon_img, &pt_this->h_repeat_all_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_repeat_all_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*repeat_a icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_repeat_a, &pt_this->h_repeat_a_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_repeat_a_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    /*repeat_ab icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_repeat_ab, &pt_this->h_repeat_ab_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_repeat_ab_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    /*repeat_abx icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_repeat_abx, &pt_this->h_repeat_abx_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_repeat_abx_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    /*shuffle icon*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_shuffle_icon_img, &pt_this->h_shuffle_icon);
    if(WGLR_OK != i4_ret)
    {
        pt_this->h_shuffle_icon = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /* video player Divx button normal */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_divx_btn_nor, &pt_this->h_divx_btn_nor);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_divx_btn_nor = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player Divx button highlight */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_divx_btn_hlt, &pt_this->h_divx_btn_hlt);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_divx_btn_hlt = NULL_HANDLE;
       return MMPR_FAIL;
    }
    
    /*video player Divx frame*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_divx_frm, &pt_this->h_divx_frm);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_divx_frm= NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player Divx top bk */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_divx_top, &pt_this->h_divx_top);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_divx_top = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player repeat all */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_repeat_all_img, &pt_this->h_vp_repeat_all);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_repeat_all= NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player repeat once */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_repeat_once_img, &pt_this->h_vp_repeat_once);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_repeat_once= NULL_HANDLE;
       return MMPR_FAIL;
    }
    /* video player repeat single */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_repeat_single_img, &pt_this->h_vp_repeat_single);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_repeat_single= NULL_HANDLE;
       return MMPR_FAIL;
    }
    /* video player stop */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_stop_img, &pt_this->h_vp_stop);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_stop= NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player fast forward */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_fast_forward_img, &pt_this->h_vp_fast_forward);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_fast_forward= NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player fast reverse */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_fast_reverse_img, &pt_this->h_vp_fast_reverse);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_fast_reverse= NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player no fast forward */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_no_fast_forward_img, &pt_this->h_vp_no_fast_forward);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_no_fast_forward= NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player no fast reverse */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_no_fast_reverse_img, &pt_this->h_vp_no_fast_reverse);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_no_fast_reverse= NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player not support  */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_not_support_img, &pt_this->h_vp_not_support);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_not_support= NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player zoom */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_zoom_img, &pt_this->h_vp_zoom);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_zoom= NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player no zoom */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_no_zoom_img, &pt_this->h_vp_no_zoom);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_no_zoom= NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player no zoom */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_no_audio_img, &pt_this->h_vp_no_audio);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_no_audio= NULL_HANDLE;
       return MMPR_FAIL;
    }
    
    /* video player subtitle */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_subtitle, &pt_this->h_vp_subtitle);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_subtitle = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player no subtitle */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_vp_no_subtitle, &pt_this->h_vp_no_subtitle);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_vp_no_subtitle = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* no pause icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_status_bar_no_pause_img, &pt_this->h_status_bar_no_pause);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_status_bar_no_pause = NULL_HANDLE;
       return MMPR_FAIL;
    }
    /* h_g_mmp_list_mode_scroll_body */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_list_mode_scroll_body, &pt_this->h_g_mmp_list_mode_scroll_body);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_list_mode_scroll_body = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* h_g_mmp_list_mode_scroll_thumb */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_V_ONLY, &t_g_mmp_list_mode_scroll_thumb, &pt_this->h_g_mmp_list_mode_scroll_thumb);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_list_mode_scroll_thumb = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* h_g_mmp_list_mode_hl_bar */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY, &t_g_mmp_list_mode_hl_bar, &pt_this->h_g_mmp_list_mode_hl_bar);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_list_mode_hl_bar = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player no subtitle */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_music_file_list_bk, &pt_this->h_g_mmp_music_file_list_bk);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_music_file_list_bk = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* video player no subtitle */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_mmp_music_1_bk, &pt_this->h_g_mmp_music_1_bk);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_music_1_bk = NULL_HANDLE;
       return MMPR_FAIL;
    }
    
    /*t_g_mmp_music_2_bk */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_mmp_music_2_bk, &pt_this->h_g_mmp_list_mode_music_2_bk);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_list_mode_music_2_bk = NULL_HANDLE;
       return MMPR_FAIL;
    }
    
    /* t_g_mmp_lstmod_right_lb_title */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_lstmod_right_lb_title, &pt_this->h_g_mmp_lstmod_right_lb_title);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_lstmod_right_lb_title = NULL_HANDLE;
       return MMPR_FAIL;
    }
    
    /* video player no subtitle */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_lstmod_right_lb_bk, &pt_this->h_g_mmp_lstmod_right_lb_bk);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_lstmod_right_lb_bk = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* t_g_mmp_lstmod_bar_down_cursor */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_lstmod_bar_down_cursor, &pt_this->h_g_mmp_lstmod_bar_down_cursor);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_lstmod_bar_down_cursor = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* t_g_mmp_lstmod_bar_top_cursor */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_lstmod_bar_top_cursor, &pt_this->h_g_mmp_lstmod_bar_top_cursor);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_lstmod_bar_top_cursor = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* t_g_mmp_lstmod_bar_top_cursor */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_lstmod_bexclamation_mark, &pt_this->h_g_mmp_lstmod_bexclamation_mark);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_lstmod_bexclamation_mark = NULL_HANDLE;
       return MMPR_FAIL;
    }

    /* music list toolbar icon */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_enter, &pt_this->h_music_list_enter);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_music_list_enter = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_exit, &pt_this->h_music_list_exit);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_music_list_exit = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_menu, &pt_this->h_music_list_menu);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_music_list_menu = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_select, &pt_this->h_music_list_select);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_music_list_select = NULL_HANDLE;
       return MMPR_FAIL;
    }
    
    /* thumbnail size */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_folder_l, &pt_this->h_g_mmp_folder_l);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_folder_l = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_folder_m, &pt_this->h_g_mmp_folder_m);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_folder_m = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_folder_s, &pt_this->h_g_mmp_folder_s);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_folder_s = NULL_HANDLE;
       return MMPR_FAIL;
    }
    
    /*  DLNA */
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_dlna_folder_l, &pt_this->h_g_mmp_dlna_folder_l);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_dlna_folder_l = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_dlna_folder_m, &pt_this->h_g_mmp_dlna_folder_m);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_dlna_folder_m = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_dlna_folder_s, &pt_this->h_g_mmp_dlna_folder_s);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_dlna_folder_s = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_audio_icon_l, &pt_this->h_g_mmp_audio_icon_l);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_audio_icon_l = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_audio_icon_m, &pt_this->h_g_mmp_audio_icon_m);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_audio_icon_m = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_audio_icon_s, &pt_this->h_g_mmp_audio_icon_s);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_audio_icon_s = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_video_file_l, &pt_this->h_g_mmp_video_file_l);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_video_file_l = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_video_file_m, &pt_this->h_g_mmp_video_file_m);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_video_file_m = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_video_file_s, &pt_this->h_g_mmp_video_file_s);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_video_file_s = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_frm_bk, &pt_this->h_g_mmp_frm_bk);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_frm_bk = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_mmp_btn_nr_bk, &pt_this->h_g_mmp_btn_nr_bk);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_btn_nr_bk = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_mmp_btn_hlt_bk, &pt_this->h_g_mmp_btn_hlt_bk);
    if(WGLR_OK != i4_ret)
    {
       pt_this->h_g_mmp_btn_hlt_bk = NULL_HANDLE;
       return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_HV, &t_g_mmp_track_time_bar_fill, &pt_this->h_g_mmp_track_time_bar_fill);
    if (WGLR_OK != i4_ret)
    {
        pt_this->h_g_mmp_track_time_bar_fill = NULL_HANDLE;
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_now_playing_icon, &pt_this->h_g_mmp_lm_play);
    if (WGLR_OK != i4_ret)
    {
        pt_this->h_g_mmp_lm_play = NULL_HANDLE;
        return MMPR_FAIL;
    }
    
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT, &t_g_mmp_pause_icon, &pt_this->h_g_mmp_lm_pause);
    if (WGLR_OK != i4_ret)
    {
        pt_this->h_g_mmp_lm_pause = NULL_HANDLE;
        return (MMPR_FAIL);
    }
    
#endif /* MMP_GUI_AUTHORING */
    pt_this->i4_init_count++;
    
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_img_deinit
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_img_deinit(VOID)
{
    _MMP_SHARE_RC_T*            pt_this = &t_g_share_rc;

    if(0 == pt_this->i4_init_count)
    {
        return MMPR_OK;
    }
    MMP_ASSERT(pt_this->i4_init_count > 0);

    pt_this->i4_init_count--;
    if(pt_this->i4_init_count > 0)
    {
        return MMPR_OK;
    }

#ifdef MMP_GUI_AUTHORING
    if (MMPR_OK != mmp_gen_deinit_image())
    {
        MMP_ASSERT(0);
        return MMPR_FAIL;
    }
    c_memset(pt_this, 0, sizeof(_MMP_SHARE_RC_T));

    return (MMPR_OK);
#else
    /*red icon*/
    if(NULL_HANDLE != pt_this->h_red_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_red_icon), WGLR_OK);

        pt_this->h_red_icon = NULL_HANDLE;
    }
    
    /*green icon*/
    if(NULL_HANDLE != pt_this->h_green_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_green_icon), WGLR_OK);
        
        pt_this->h_green_icon = NULL_HANDLE;
    }
    
    /*yellow icon*/
    if(NULL_HANDLE != pt_this->h_yellow_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_yellow_icon), WGLR_OK);
        
        pt_this->h_yellow_icon = NULL_HANDLE;
    }
    
    /*blue icon*/
    if(NULL_HANDLE != pt_this->h_blue_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_blue_icon), WGLR_OK);
        
        pt_this->h_blue_icon = NULL_HANDLE;
    }
    
    /*play icon*/
    if(NULL_HANDLE != pt_this->h_play_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_play_icon), WGLR_OK);
        
        pt_this->h_play_icon = NULL_HANDLE;
    }
    
    /*pause icon*/
    if(NULL_HANDLE != pt_this->h_pause_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_pause_icon), WGLR_OK);
        
        pt_this->h_pause_icon = NULL_HANDLE;
    }
    
    /*stop icon*/
    if(NULL_HANDLE != pt_this->h_stop_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_stop_icon), WGLR_OK);
        
        pt_this->h_stop_icon = NULL_HANDLE;
    }

    /*prev icon*/
    if(NULL_HANDLE != pt_this->h_prev_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_prev_icon), WGLR_OK);

        pt_this->h_prev_icon = NULL_HANDLE;
    }

    /*next icon*/
    if(NULL_HANDLE != pt_this->h_next_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_next_icon), WGLR_OK);

        pt_this->h_next_icon = NULL_HANDLE;
    }

    /*vol icon*/
    if(NULL_HANDLE != pt_this->h_vol_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vol_icon), WGLR_OK);

        pt_this->h_vol_icon = NULL_HANDLE;
    }

    /*vol mute icon*/
    if(NULL_HANDLE != pt_this->h_vol_mute_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vol_mute_icon), WGLR_OK);

        pt_this->h_vol_mute_icon = NULL_HANDLE;
    }

    /*vol bar bg*/
    if(NULL_HANDLE != pt_this->h_vol_bar_bg)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vol_bar_bg), WGLR_OK);

        pt_this->h_vol_bar_bg = NULL_HANDLE;
    }

    /*vol bar*/
    if(NULL_HANDLE != pt_this->h_vol_bar)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vol_bar), WGLR_OK);

        pt_this->h_vol_bar = NULL_HANDLE;
    }

    /*playback progress bar*/
    if(NULL_HANDLE != pt_this->h_playback_pg_bar)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_playback_pg_bar), WGLR_OK);
        
        pt_this->h_playback_pg_bar = NULL_HANDLE;
    }
    
    /*status bar*/
    if(NULL_HANDLE != pt_this->h_status_bar)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_status_bar), WGLR_OK);
        
        pt_this->h_status_bar = NULL_HANDLE;
    }
    
    /*audio main frame*/
    if(NULL_HANDLE != pt_this->h_audio_main_frm)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_audio_main_frm), WGLR_OK);
        
        pt_this->h_audio_main_frm = NULL_HANDLE;
    }

    /*tool bar*/
    if(NULL_HANDLE != pt_this->h_tool_bar)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_tool_bar), WGLR_OK);
        
        pt_this->h_tool_bar = NULL_HANDLE;
    }
    
    /*detail page*/
    if(NULL_HANDLE != pt_this->h_detail_page)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_detail_page), WGLR_OK);
        
        pt_this->h_detail_page = NULL_HANDLE;
    }

    /*repeat_once icon*/
    if(NULL_HANDLE != pt_this->h_repeat_once_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_repeat_once_icon), WGLR_OK);
        
        pt_this->h_repeat_once_icon = NULL_HANDLE;
    }

    /*repeat_all icon*/
    if(NULL_HANDLE != pt_this->h_repeat_all_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_repeat_all_icon), WGLR_OK);

        pt_this->h_repeat_all_icon = NULL_HANDLE;
    }

    /*repeat_a icon*/
    if(NULL_HANDLE != pt_this->h_repeat_a_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_repeat_a_icon), WGLR_OK);

        pt_this->h_repeat_a_icon = NULL_HANDLE;
    }
    
    /*repeat_ab icon*/
    if(NULL_HANDLE != pt_this->h_repeat_ab_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_repeat_ab_icon), WGLR_OK);

        pt_this->h_repeat_ab_icon = NULL_HANDLE;
    }
    
    /*repeat_abx icon*/
    if(NULL_HANDLE != pt_this->h_repeat_abx_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_repeat_abx_icon), WGLR_OK);

        pt_this->h_repeat_abx_icon = NULL_HANDLE;
    }
    
    /*shuffle icon*/
    if(NULL_HANDLE != pt_this->h_shuffle_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_shuffle_icon), WGLR_OK);

        pt_this->h_shuffle_icon = NULL_HANDLE;
    }

    /*fast forward icon*/
    if(NULL_HANDLE != pt_this->h_fast_forward_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_fast_forward_icon), WGLR_OK);

        pt_this->h_fast_forward_icon = NULL_HANDLE;
    }

    /*fast rewind icon*/
    if(NULL_HANDLE != pt_this->h_fast_rewind_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_fast_rewind_icon), WGLR_OK);

        pt_this->h_fast_rewind_icon = NULL_HANDLE;
    }

    /*thumbnail photo*/
    if(NULL_HANDLE != pt_this->h_thumbnail_photo)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_thumbnail_photo), WGLR_OK);
        pt_this->h_thumbnail_photo = NULL_HANDLE;
    }

    /*thumbnail folder*/
    if(NULL_HANDLE != pt_this->h_thumbnail_folder)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_thumbnail_folder), WGLR_OK);
        pt_this->h_thumbnail_folder = NULL_HANDLE;
    }

    /*thumbnail dlna folder*/
    if(NULL_HANDLE != pt_this->h_thumbnail_dlna_folder)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_thumbnail_dlna_folder), WGLR_OK);
        pt_this->h_thumbnail_dlna_folder = NULL_HANDLE;
    }

    /*thumbnail music*/
    if(NULL_HANDLE != pt_this->h_thumbnail_music)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_thumbnail_music), WGLR_OK);
        pt_this->h_thumbnail_music = NULL_HANDLE;
    }

    /*detail audio*/
    if(NULL_HANDLE != pt_this->h_detail_audio_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_detail_audio_icon), WGLR_OK);
        pt_this->h_detail_audio_icon = NULL_HANDLE;
    }

    /*highlight thumbnail*/
    if(NULL_HANDLE != pt_this->h_highlight_thumbnail)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_highlight_thumbnail), WGLR_OK);
        pt_this->h_highlight_thumbnail = NULL_HANDLE;
    }

    /*select thumbnail*/
    if(NULL_HANDLE != pt_this->h_select_thumbnail)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_select_thumbnail), WGLR_OK);
        pt_this->h_select_thumbnail = NULL_HANDLE;
    }

    /*copy thumbnail*/
    if(NULL_HANDLE != pt_this->h_copy_thumbnail)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_copy_thumbnail), WGLR_OK);
        pt_this->h_copy_thumbnail = NULL_HANDLE;
    }

    /*select listmode*/
    if(NULL_HANDLE != pt_this->h_select_listmode)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_select_listmode), WGLR_OK);
        pt_this->h_select_listmode = NULL_HANDLE;
    }

    /*copy thumbnail*/
    if(NULL_HANDLE != pt_this->h_copy_listmode)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_copy_listmode), WGLR_OK);
        pt_this->h_copy_listmode = NULL_HANDLE;
    }

    /* Animation images */
    if(NULL_HANDLE != ah_g_mmp_scanning_img[0])
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(ah_g_mmp_scanning_img[0]), WGLR_OK);
        ah_g_mmp_scanning_img[0] = NULL_HANDLE;
    }
    if(NULL_HANDLE != ah_g_mmp_scanning_img[1])
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(ah_g_mmp_scanning_img[1]), WGLR_OK);
        ah_g_mmp_scanning_img[1] = NULL_HANDLE;
    }
    if(NULL_HANDLE != ah_g_mmp_scanning_img[2])
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(ah_g_mmp_scanning_img[2]), WGLR_OK);
        ah_g_mmp_scanning_img[2] = NULL_HANDLE;
    }
    if(NULL_HANDLE != ah_g_mmp_scanning_img[3])
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(ah_g_mmp_scanning_img[3]), WGLR_OK);
        ah_g_mmp_scanning_img[3] = NULL_HANDLE;
    }

    /*thumbnail top bg*/
    if(NULL_HANDLE != pt_this->h_thumbnail_top_bg)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_thumbnail_top_bg), WGLR_OK);
        pt_this->h_thumbnail_top_bg = NULL_HANDLE;
    }

    /*thumbnail btm bg*/
    if(NULL_HANDLE != pt_this->h_thumbnail_btm_bg)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_thumbnail_btm_bg), WGLR_OK);
        pt_this->h_thumbnail_btm_bg = NULL_HANDLE;
    }

    /*folder icon*/
    if(NULL_HANDLE != pt_this->h_folder_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_folder_icon), WGLR_OK);
        pt_this->h_folder_icon = NULL_HANDLE;
    }

    /*music icon*/
    if(NULL_HANDLE != pt_this->h_music_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_music_icon), WGLR_OK);
        pt_this->h_music_icon = NULL_HANDLE;
    }

    /*photo icon*/
    if(NULL_HANDLE != pt_this->h_photo_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_photo_icon), WGLR_OK);
        pt_this->h_photo_icon = NULL_HANDLE;
    }

    /*page icon*/
    if(NULL_HANDLE != pt_this->h_page_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_page_icon), WGLR_OK);
        pt_this->h_page_icon = NULL_HANDLE;
    }

    /*size icon*/
    if(NULL_HANDLE != pt_this->h_size_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_size_icon), WGLR_OK);
        pt_this->h_size_icon = NULL_HANDLE;
    }

    /*duration icon*/
    if(NULL_HANDLE != pt_this->h_duration_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_duration_icon), WGLR_OK);
        pt_this->h_duration_icon = NULL_HANDLE;
    }

    /*scroll bar bk*/
    if(NULL_HANDLE != pt_this->h_scroll_bar_bk)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_scroll_bar_bk), WGLR_OK);
        pt_this->h_scroll_bar_bk = NULL_HANDLE;
    }

    /*scroll bar*/
    if(NULL_HANDLE != pt_this->h_scroll_bar)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_scroll_bar), WGLR_OK);
        pt_this->h_scroll_bar = NULL_HANDLE;
    }
    
    /* status bar play icon */
    if(NULL_HANDLE != pt_this->h_status_bar_play)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_status_bar_play), WGLR_OK);
        pt_this->h_status_bar_play = NULL_HANDLE;
    }
    
    /* status bar pause icon */
    if(NULL_HANDLE != pt_this->h_status_bar_pause)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_status_bar_pause), WGLR_OK);
        pt_this->h_status_bar_pause = NULL_HANDLE;
    }

    /* music play icon */
    if(NULL_HANDLE != pt_this->h_music_play_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_music_play_icon), WGLR_OK);
        pt_this->h_music_play_icon = NULL_HANDLE;
    }
    
    /* read only icon */
    if(NULL_HANDLE != pt_this->h_read_only_icon)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_read_only_icon), WGLR_OK);
        pt_this->h_read_only_icon = NULL_HANDLE;
    }
    
    /* video player Divx button normal */
    if(NULL_HANDLE != pt_this->h_divx_btn_nor)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_divx_btn_nor), WGLR_OK);
        pt_this->h_divx_btn_nor = NULL_HANDLE;
    }

    /* video player Divx button highlight */
    if(NULL_HANDLE != pt_this->h_divx_btn_hlt)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_divx_btn_hlt), WGLR_OK);
        pt_this->h_divx_btn_hlt= NULL_HANDLE;
    }

    /*video player Divx frame*/
    if(NULL_HANDLE != pt_this->h_divx_frm)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_divx_frm), WGLR_OK);
        pt_this->h_divx_frm = NULL_HANDLE;
    }

    /* video player Divx top bk */
    if(NULL_HANDLE != pt_this->h_divx_top)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_divx_top), WGLR_OK);
        pt_this->h_divx_top = NULL_HANDLE;
    }

    /* video player repeat all */
    if(NULL_HANDLE != pt_this->h_vp_repeat_all)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_repeat_all), WGLR_OK);
        pt_this->h_vp_repeat_all = NULL_HANDLE;
    }
    
    /* video player repeat once */
    if(NULL_HANDLE != pt_this->h_vp_repeat_once)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_repeat_once), WGLR_OK);
        pt_this->h_vp_repeat_once= NULL_HANDLE;
    }
    
    /* video player repeat single */
    if(NULL_HANDLE != pt_this->h_vp_repeat_single)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_repeat_single), WGLR_OK);
        pt_this->h_vp_repeat_single= NULL_HANDLE;
    }
    
    /* video player stop */
    if(NULL_HANDLE != pt_this->h_vp_stop)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_stop), WGLR_OK);
        pt_this->h_vp_stop= NULL_HANDLE;
    }

    /* video player fast forward */
    if(NULL_HANDLE != pt_this->h_vp_fast_forward)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_fast_forward), WGLR_OK);
        pt_this->h_vp_fast_forward= NULL_HANDLE;
    }

    /* video player fast reverse */
    if(NULL_HANDLE != pt_this->h_vp_fast_reverse)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_fast_reverse), WGLR_OK);
        pt_this->h_vp_fast_reverse= NULL_HANDLE;
    }

    /* video player no fast forward */
    if(NULL_HANDLE != pt_this->h_vp_no_fast_forward)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_no_fast_forward), WGLR_OK);
        pt_this->h_vp_no_fast_forward = NULL_HANDLE;
    }

    /* video player no fast reverse */
    if(NULL_HANDLE != pt_this->h_vp_no_fast_reverse)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_no_fast_reverse), WGLR_OK);
        pt_this->h_vp_no_fast_reverse = NULL_HANDLE;
    }

    /* video player not support*/
    if(NULL_HANDLE != pt_this->h_vp_not_support)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_not_support), WGLR_OK);
        pt_this->h_vp_not_support = NULL_HANDLE;
    }

    /* video player zoom */
    if(NULL_HANDLE != pt_this->h_vp_zoom)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_zoom), WGLR_OK);
        pt_this->h_vp_zoom= NULL_HANDLE;
    }

    /* video player no zoom */
    if(NULL_HANDLE != pt_this->h_vp_no_zoom)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_no_zoom), WGLR_OK);
        pt_this->h_vp_no_zoom= NULL_HANDLE;
    }

    /* video player no audio */
    if(NULL_HANDLE != pt_this->h_vp_no_audio)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_no_audio), WGLR_OK);
        pt_this->h_vp_no_audio= NULL_HANDLE;
    }

    /* video player subtitle */
    if(NULL_HANDLE != pt_this->h_vp_subtitle)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_subtitle), WGLR_OK);
        pt_this->h_vp_subtitle= NULL_HANDLE;
    }

    /* video player no subtitle */
    if(NULL_HANDLE != pt_this->h_vp_no_subtitle)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_vp_no_subtitle), WGLR_OK);
        pt_this->h_vp_no_subtitle= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_status_bar_no_pause)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_status_bar_no_pause), WGLR_OK);
        pt_this->h_status_bar_no_pause = NULL_HANDLE;
    }

    /* video player no subtitle */
    if(NULL_HANDLE != pt_this->h_g_mmp_list_mode_scroll_body)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_list_mode_scroll_body), WGLR_OK);
        pt_this->h_g_mmp_list_mode_scroll_body= NULL_HANDLE;
    }

    /* h_g_mmp_list_mode_scroll_thumb */
    if(NULL_HANDLE != pt_this->h_g_mmp_list_mode_scroll_thumb)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_list_mode_scroll_thumb), WGLR_OK);
        pt_this->h_g_mmp_list_mode_scroll_thumb= NULL_HANDLE;
    }

    /* h_g_mmp_list_mode_hl_bar */
    if(NULL_HANDLE != pt_this->h_g_mmp_list_mode_hl_bar)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_list_mode_hl_bar), WGLR_OK);
        pt_this->h_g_mmp_list_mode_hl_bar= NULL_HANDLE;
    }

        /* video player no subtitle */
    if(NULL_HANDLE != pt_this->h_g_mmp_music_file_list_bk)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_music_file_list_bk), WGLR_OK);
        pt_this->h_g_mmp_music_file_list_bk= NULL_HANDLE;
    }

        /* h_g_mmp_music_1_bk */
    if(NULL_HANDLE != pt_this->h_g_mmp_music_1_bk)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_music_1_bk), WGLR_OK);
        pt_this->h_g_mmp_music_1_bk= NULL_HANDLE;
    }

    /* h_g_mmp_music_2_bk */
    if(NULL_HANDLE != pt_this->h_g_mmp_list_mode_music_2_bk)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_list_mode_music_2_bk), WGLR_OK);
        pt_this->h_g_mmp_list_mode_music_2_bk= NULL_HANDLE;
    }

        /* video player no subtitle */
    if(NULL_HANDLE != pt_this->h_g_mmp_lstmod_right_lb_title)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_lstmod_right_lb_title), WGLR_OK);
        pt_this->h_g_mmp_lstmod_right_lb_title= NULL_HANDLE;
    }

        /* video player no subtitle */
    if(NULL_HANDLE != pt_this->h_g_mmp_lstmod_right_lb_bk)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_lstmod_right_lb_bk), WGLR_OK);
        pt_this->h_g_mmp_lstmod_right_lb_bk= NULL_HANDLE;
    }
    
    /* video player no subtitle */
    if(NULL_HANDLE != pt_this->h_g_mmp_lstmod_bar_down_cursor)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_lstmod_bar_down_cursor), WGLR_OK);
        pt_this->h_g_mmp_lstmod_bar_down_cursor= NULL_HANDLE;
    }

    /* video player no subtitle */
    if(NULL_HANDLE != pt_this->h_g_mmp_lstmod_bar_top_cursor)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_lstmod_bar_top_cursor), WGLR_OK);
        pt_this->h_g_mmp_lstmod_bar_top_cursor= NULL_HANDLE;
    }

    /* bexclamation_mark */
    if(NULL_HANDLE != pt_this->h_g_mmp_lstmod_bexclamation_mark)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_lstmod_bexclamation_mark), WGLR_OK);
        pt_this->h_g_mmp_lstmod_bexclamation_mark= NULL_HANDLE;
    }

    /* music list toolbar icon */
    if(NULL_HANDLE != pt_this->h_music_list_enter)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_music_list_enter), WGLR_OK);
        pt_this->h_music_list_enter= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_music_list_exit)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_music_list_exit), WGLR_OK);
        pt_this->h_music_list_exit= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_music_list_menu)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_music_list_menu), WGLR_OK);
        pt_this->h_music_list_menu= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_music_list_select)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_music_list_select), WGLR_OK);
        pt_this->h_music_list_select= NULL_HANDLE;
    }

    /* thumbnail size */
    if(NULL_HANDLE != pt_this->h_g_mmp_folder_l)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_folder_l), WGLR_OK);
        pt_this->h_g_mmp_folder_l= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_folder_m)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_folder_m), WGLR_OK);
        pt_this->h_g_mmp_folder_m= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_folder_s)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_folder_s), WGLR_OK);
        pt_this->h_g_mmp_folder_s= NULL_HANDLE;
    }

    /*  DLNA */
    if(NULL_HANDLE != pt_this->h_g_mmp_dlna_folder_l)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_dlna_folder_l), WGLR_OK);
        pt_this->h_g_mmp_dlna_folder_l= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_dlna_folder_m)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_dlna_folder_m), WGLR_OK);
        pt_this->h_g_mmp_dlna_folder_m= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_dlna_folder_s)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_dlna_folder_s), WGLR_OK);
        pt_this->h_g_mmp_dlna_folder_s= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_audio_icon_l)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_audio_icon_l), WGLR_OK);
        pt_this->h_g_mmp_audio_icon_l= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_audio_icon_m)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_audio_icon_m), WGLR_OK);
        pt_this->h_g_mmp_audio_icon_m= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_audio_icon_s)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_audio_icon_s), WGLR_OK);
        pt_this->h_g_mmp_audio_icon_s= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_video_file_l)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_video_file_l), WGLR_OK);
        pt_this->h_g_mmp_video_file_l= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_video_file_m)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_video_file_m), WGLR_OK);
        pt_this->h_g_mmp_video_file_m= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_video_file_s)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_video_file_s), WGLR_OK);
        pt_this->h_g_mmp_video_file_s= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_frm_bk)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_frm_bk), WGLR_OK);
        pt_this->h_g_mmp_frm_bk= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_btn_nr_bk)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_btn_nr_bk), WGLR_OK);
        pt_this->h_g_mmp_btn_nr_bk= NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_g_mmp_btn_hlt_bk)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_btn_hlt_bk), WGLR_OK);
        pt_this->h_g_mmp_btn_hlt_bk= NULL_HANDLE;
    }

    if (NULL_HANDLE != pt_this->h_g_mmp_track_time_bar_fill)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_track_time_bar_fill), WGLR_OK);
        pt_this->h_g_mmp_track_time_bar_fill = NULL_HANDLE;
    }

    if (NULL_HANDLE != pt_this->h_g_mmp_lm_play)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_lm_play), WGLR_OK);
        pt_this->h_g_mmp_lm_play = NULL_HANDLE;
    }

    if (NULL_HANDLE != pt_this->h_g_mmp_lm_pause)
    {
        MMP_EXEC_WITH_ASSERT(c_wgl_img_tpl_destroy(pt_this->h_g_mmp_lm_pause), WGLR_OK);
        pt_this->h_g_mmp_lm_pause = NULL_HANDLE;
    }

    return MMPR_OK;
#endif
}

/*-----------------------------------------------------------------------------
 * Name: mmp_img_get_img
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
INT32 mmp_img_get_img(
    MMP_IMG_IMAGE_ID_T          e_id, 
    WGL_HIMG_TPL_T*             ph_img_tpl)
{
    _MMP_SHARE_RC_T*            pt_this = &t_g_share_rc;
    
    if(0 == pt_this->i4_init_count)
    {
        return MMPR_RES_NOT_READY;
    }

    if(NULL == ph_img_tpl)
    {
        return MMPR_INV_ARG;
    }

    switch(e_id)
    {
    case MMP_IMG_IMAGE_ID_RED_ICON:
        *ph_img_tpl = pt_this->h_red_icon;
        break;
    case MMP_IMG_IMAGE_ID_GREEN_ICON:
        *ph_img_tpl = pt_this->h_green_icon;
        break;
    case MMP_IMG_IMAGE_ID_YELLOW_ICON:
        *ph_img_tpl = pt_this->h_yellow_icon;
        break;
    case MMP_IMG_IMAGE_ID_BLUE_ICON:
        *ph_img_tpl = pt_this->h_blue_icon;
        break;
    case MMP_IMG_IMAGE_ID_PLAY_ICON:
        *ph_img_tpl = pt_this->h_play_icon;
        break;
    case MMP_IMG_IMAGE_ID_PAUSE_ICON:
        *ph_img_tpl = pt_this->h_pause_icon;
        break;
    case MMP_IMG_IMAGE_ID_STOP_ICON:
        *ph_img_tpl = pt_this->h_stop_icon;
        break;
    case MMP_IMG_IMAGE_ID_PREV_ICON:
        *ph_img_tpl = pt_this->h_prev_icon;
        break;
    case MMP_IMG_IMAGE_ID_NEXT_ICON:
        *ph_img_tpl = pt_this->h_next_icon;
        break;
    case MMP_IMG_IMAGE_ID_VOL_ICON:
        *ph_img_tpl = pt_this->h_vol_icon;
        break;
    case MMP_IMG_IMAGE_ID_VOL_MUTE_ICON:
        *ph_img_tpl = pt_this->h_vol_mute_icon;
        break;
    case MMP_IMG_IMAGE_ID_VOL_BAR_BG:
        *ph_img_tpl = pt_this->h_vol_bar_bg;
        break;
    case MMP_IMG_IMAGE_ID_VOL_BAR:
        *ph_img_tpl = pt_this->h_vol_bar;
        break;
    case MMP_IMG_IMAGE_ID_STATUS_BAR:
        *ph_img_tpl = pt_this->h_status_bar;
        break;
    case MMP_IMG_IMAGE_ID_PLAYBACK_PG_BAR:
        *ph_img_tpl = pt_this->h_playback_pg_bar;
        break;
    case MMP_IMG_IMAGE_ID_AUDIO_MAIN_FRM:
        *ph_img_tpl = pt_this->h_audio_main_frm;
        break;
    case MMP_IMG_IMAGE_ID_TOOL_BAR:
        *ph_img_tpl = pt_this->h_tool_bar;
        break;
    case MMP_IMG_IMAGE_ID_DETAIL_PAGE:
        *ph_img_tpl = pt_this->h_detail_page;
        break;
    case MMP_IMG_IMAGE_ID_REPEAT_ONCE:
        *ph_img_tpl = pt_this->h_repeat_once_icon;
        break;
    case MMP_IMG_IMAGE_ID_REPEAT_ALL:
        *ph_img_tpl = pt_this->h_repeat_all_icon;
        break;
    case MMP_IMG_IMAGE_ID_REPEAT_A:
        *ph_img_tpl = pt_this->h_repeat_a_icon;
        break;
    case MMP_IMG_IMAGE_ID_REPEAT_AB:
        *ph_img_tpl = pt_this->h_repeat_ab_icon;
        break;
    case MMP_IMG_IMAGE_ID_REPEAT_ABX:
        *ph_img_tpl = pt_this->h_repeat_abx_icon;
        break;
    case MMP_IMG_IMAGE_ID_SHUFFLE:
        *ph_img_tpl = pt_this->h_shuffle_icon;
        break;
    case MMP_IMG_IMAGE_ID_FAST_FORWARD:
        *ph_img_tpl = pt_this->h_fast_forward_icon;
        break;
    case MMP_IMG_IMAGE_ID_FAST_REWIND:
        *ph_img_tpl = pt_this->h_fast_rewind_icon;
        break;
    case MMP_IMG_IMAGE_ID_THUMBNAIL_PHOTO:
        *ph_img_tpl = pt_this->h_thumbnail_photo;
        break;
    case MMP_IMG_IMAGE_ID_THUMBNAIL_FOLDER:
        *ph_img_tpl = pt_this->h_thumbnail_folder;
        break;
    case MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER:
        *ph_img_tpl = pt_this->h_thumbnail_dlna_folder;
        break;
    case MMP_IMG_IMAGE_ID_THUMBNAIL_MUSIC:
        *ph_img_tpl = pt_this->h_thumbnail_music;
        break;
    case MMP_IMG_IMAGE_ID_DETAIL_AUDIO:
        *ph_img_tpl = pt_this->h_detail_audio_icon;
        break;
    case MMP_IMG_IMAGE_ID_HIGHLIGHT_THUMBNAIL:
        *ph_img_tpl = pt_this->h_highlight_thumbnail;
        break;
    case MMP_IMG_IMAGE_ID_HIGHLIGHT_THUMBNAIL_M:
        *ph_img_tpl = pt_this->h_g_mmp_thumb_hl_m;
        break;
    case MMP_IMG_IMAGE_ID_HIGHLIGHT_THUMBNAIL_L:
        *ph_img_tpl = pt_this->h_g_mmp_thumb_hl_l;
        break;      
    case MMP_IMG_IMAGE_ID_SELECT_THUMBNAIL:
        *ph_img_tpl = pt_this->h_select_thumbnail;
        break;
    case MMP_IMG_IMAGE_ID_COPY_THUMBNAIL:
        *ph_img_tpl = pt_this->h_copy_thumbnail;
        break;
    case MMP_IMG_IMAGE_ID_THUMBNAIL_TOP_BG:
        *ph_img_tpl = pt_this->h_thumbnail_top_bg;
        break;
    case MMP_IMG_IMAGE_ID_THUMBNAIL_BTM_BG:
        *ph_img_tpl = pt_this->h_thumbnail_btm_bg;
        break;
    case MMP_IMG_IMAGE_ID_FOLDER_ICON:
        *ph_img_tpl = pt_this->h_folder_icon;
        break;
    case MMP_IMG_IMAGE_ID_MUSIC_ICON:
        *ph_img_tpl = pt_this->h_music_icon;
        break;
    case MMP_IMG_IMAGE_ID_PHOTO_ICON:
        *ph_img_tpl = pt_this->h_photo_icon;
        break;
    case MMP_IMG_IMAGE_ID_VIDEO_ICON:
        *ph_img_tpl = pt_this->h_video_icon;
        break;
    case MMP_IMG_IMAGE_ID_TXT_ICON:
        *ph_img_tpl = pt_this->h_txt_icon;
        break;          
    case MMP_IMG_IMAGE_ID_PAGE_ICON:
        *ph_img_tpl = pt_this->h_page_icon;
        break;
    case MMP_IMG_IMAGE_ID_SIZE_ICON:
        *ph_img_tpl = pt_this->h_size_icon;
        break;
    case MMP_IMG_IMAGE_ID_DURATION_ICON:
        *ph_img_tpl = pt_this->h_duration_icon;
        break;
    case MMP_IMG_IMAGE_ID_SCROLL_BAR_BK:
        *ph_img_tpl = pt_this->h_scroll_bar_bk;
        break;
    case MMP_IMG_IMAGE_ID_SCROLL_BAR:
        *ph_img_tpl = pt_this->h_scroll_bar;
        break;
        
    case MMP_IMG_IMAGE_ID_STATUS_BAR_PLAY:
        *ph_img_tpl = pt_this->h_status_bar_play;
        break;
    
    case MMP_IMG_IMAGE_ID_STATUS_BAR_PAUSE:
        *ph_img_tpl = pt_this->h_status_bar_pause;
        break;

    case MMP_IMG_IMAGE_ID_MUSIC_PLAY_ICON:
        *ph_img_tpl = pt_this->h_music_play_icon;
        break;

    case MMP_IMG_IMAGE_ID_READ_ONLY_ICON:
        *ph_img_tpl = pt_this->h_read_only_icon;
        break;

    case MMP_IMG_IMAGE_ID_DIVX_BTN_NOR:
        *ph_img_tpl = pt_this->h_divx_btn_nor;
        break;
        
    case MMP_IMG_IMAGE_ID_DIVX_BTN_HLT:
        *ph_img_tpl = pt_this->h_divx_btn_hlt;
        break;

    case MMP_IMG_IMAGE_ID_DIVX_FRM:
        *ph_img_tpl = pt_this->h_divx_frm;
        break;

    case MMP_IMG_IMAGE_ID_DIVX_TOP:
        *ph_img_tpl = pt_this->h_divx_top;
        break;

    case MMP_IMG_IMAGE_ID_VP_REPEAT_ALL:
        *ph_img_tpl = pt_this->h_vp_repeat_all;
        break;

    case MMP_IMG_IMAGE_ID_VP_REPEAT_ONCE:
        *ph_img_tpl = pt_this->h_vp_repeat_once;
        break;

    case MMP_IMG_IMAGE_ID_VP_REPEAT_SINGLE:
        *ph_img_tpl = pt_this->h_vp_repeat_single;
        break;

    case MMP_IMG_IMAGE_ID_VP_STOP:
        *ph_img_tpl = pt_this->h_vp_stop;
        break;

    case MMP_IMG_IMAGE_ID_VP_FAST_FORWARD:
        *ph_img_tpl = pt_this->h_vp_fast_forward;
        break;

    case MMP_IMG_IMAGE_ID_VP_FAST_REVERSE:
        *ph_img_tpl = pt_this->h_vp_fast_reverse;
        break;

    case MMP_IMG_IMAGE_ID_VP_NO_FAST_FORWARD:
        *ph_img_tpl = pt_this->h_vp_no_fast_forward;
        break;

    case MMP_IMG_IMAGE_ID_VP_NO_FAST_REVERSE:
        *ph_img_tpl = pt_this->h_vp_no_fast_reverse;
        break;

    case MMP_IMG_IMAGE_ID_VP_NOT_SUPPORT:
        *ph_img_tpl = pt_this->h_vp_not_support;
        break;

    case MMP_IMG_IMAGE_ID_VP_ZOOM:
        *ph_img_tpl = pt_this->h_vp_zoom;
        break;

    case MMP_IMG_IMAGE_ID_VP_NO_ZOOM:
        *ph_img_tpl = pt_this->h_vp_no_zoom;
        break;
        
    case MMP_IMG_IMAGE_ID_VP_NO_AUDIO:
        *ph_img_tpl = pt_this->h_vp_no_audio;
        break;

    case MMP_IMG_IMAGE_ID_VP_SUBTITLE:
        *ph_img_tpl = pt_this->h_vp_subtitle;
        break;

    case MMP_IMG_IMAGE_ID_VP_NO_SUBTITLE:
        *ph_img_tpl = pt_this->h_vp_no_subtitle;
        break;
        
    case MMP_IMG_IMAGE_ID_STATUS_BAR_NO_PAUSE:
        *ph_img_tpl = pt_this->h_status_bar_no_pause;
        break;
    case MMP_IMG_IMAGE_ID_LIST_MODE_SCROLL_BODY:
        *ph_img_tpl = pt_this->h_g_mmp_list_mode_scroll_body;
        break;
        
    case MMP_IMG_IMAGE_ID_LIST_MODE_SCROLL_THUMB:
        *ph_img_tpl = pt_this->h_g_mmp_list_mode_scroll_thumb;
        break;

    case MMP_IMG_IMAGE_ID_LIST_MODE_HL_BAR:        
        *ph_img_tpl = pt_this->h_g_mmp_track_time_bar_fill;        
        break;    
        
    case MMP_IMG_IMAGE_ID_MUSIC_FILE_LIST_BK:
        *ph_img_tpl = pt_this->h_g_mmp_music_file_list_bk;
        break;

    case MMP_IMG_IMAGE_ID_VP_MUSIC_1_BK:
        *ph_img_tpl = pt_this->h_g_mmp_music_1_bk;
        break;  

    case MMP_IMG_IMAGE_ID_LIST_MODE_MUSIC_2_BK:
        *ph_img_tpl = pt_this->h_g_mmp_list_mode_music_2_bk;
        break;

    case MMP_IMG_IMAGE_ID_LSTMODE_RIGHT_LB_TITLE:
        *ph_img_tpl = pt_this->h_g_mmp_lstmod_right_lb_title;
        break;

    case MMP_IMG_IMAGE_ID_LSTMODE_RIGHT_LB_BK:
        *ph_img_tpl = pt_this->h_g_mmp_lstmod_right_lb_bk;
        break;
        
    case MMP_IMG_IMAGE_ID_LSTMODE_BAR_DOWN_CURSOR:
        *ph_img_tpl = pt_this->h_g_mmp_lstmod_bar_down_cursor;
        break;
    
    case MMP_IMG_IMAGE_ID_LSTMODE_BAR_TOP_CURSOR:
        *ph_img_tpl = pt_this->h_g_mmp_lstmod_bar_top_cursor;
        break;

    case MMP_IMG_IMAGE_ID_LSTMODE_BEXCLAMATION_MARK:
        *ph_img_tpl = pt_this->h_g_mmp_lstmod_bexclamation_mark;
        break;      

    case MMP_IMG_IMAGE_ID_LSTMODE_ICON_FOLDER:
        *ph_img_tpl = pt_this->h_g_mmp_lstmod_icon_folder;
        break;      

    case MMP_IMG_IMAGE_ID_ENTER:
        *ph_img_tpl = pt_this->h_music_list_enter;
        break;

    case MMP_IMG_IMAGE_ID_EXIT:
        *ph_img_tpl = pt_this->h_music_list_exit;
        break;

    case MMP_IMG_IMAGE_ID_MENU:
        *ph_img_tpl = pt_this->h_music_list_menu;
        break;

    case MMP_IMG_IMAGE_ID_SELECT:
        *ph_img_tpl = pt_this->h_music_list_select;
        break;    
    /* thumbnail size */
    case MMP_IMG_IMAGE_ID_FOLDER_L:
        *ph_img_tpl = pt_this->h_g_mmp_folder_l;
        break;

    case MMP_IMG_IMAGE_ID_FOLDER_M:
        *ph_img_tpl = pt_this->h_g_mmp_folder_m;
        break;

    case MMP_IMG_IMAGE_ID_FOLDER_S:
        *ph_img_tpl = pt_this->h_g_mmp_folder_s;
        break;    
    /*  DLNA */
    case MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER_L:
        *ph_img_tpl = pt_this->h_g_mmp_dlna_folder_l;
        break;

    case MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER_M:
        *ph_img_tpl = pt_this->h_g_mmp_dlna_folder_m;
        break;

    case MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER_S:
        *ph_img_tpl = pt_this->h_g_mmp_dlna_folder_s;
        break;    

    /*  MNP */
    case MMP_IMG_IMAGE_ID_THUMBNAIL_MNP_FOLDER_L:
        *ph_img_tpl = pt_this->h_g_mmp_mnp_folder_l;
        break;

    case MMP_IMG_IMAGE_ID_THUMBNAIL_MNP_FOLDER_M:
        *ph_img_tpl = pt_this->h_g_mmp_mnp_folder_m;
        break;

    case MMP_IMG_IMAGE_ID_THUMBNAIL_MNP_FOLDER_S:
        *ph_img_tpl = pt_this->h_g_mmp_mnp_folder_s;
        break;    
        
    case MMP_IMG_IMAGE_ID_AUDIO_ICON_L:
        *ph_img_tpl = pt_this->h_g_mmp_audio_icon_l;
        break;

    case MMP_IMG_IMAGE_ID_AUDIO_ICON_M:
        *ph_img_tpl = pt_this->h_g_mmp_audio_icon_m;
        break;

    case MMP_IMG_IMAGE_ID_AUDIO_ICON_S:
        *ph_img_tpl = pt_this->h_g_mmp_audio_icon_s;
        break;    

    case MMP_IMG_IMAGE_ID_VIDEO_ICON_L:
        *ph_img_tpl = pt_this->h_g_mmp_video_file_l;
        break;

    case MMP_IMG_IMAGE_ID_VIDEO_ICON_M:
        *ph_img_tpl = pt_this->h_g_mmp_video_file_m;
        break;

    case MMP_IMG_IMAGE_ID_VIDEO_ICON_S:
        *ph_img_tpl = pt_this->h_g_mmp_video_file_s;
        break;      

    case MMP_IMG_IMAGE_ID_PHOTO_ICON_L:
        *ph_img_tpl = pt_this->h_g_mmp_photo_file_l;
        break;

    case MMP_IMG_IMAGE_ID_PHOTO_ICON_M:
        *ph_img_tpl = pt_this->h_g_mmp_photo_file_m;
        break;

    case MMP_IMG_IMAGE_ID_PHOTO_ICON_S:
        *ph_img_tpl = pt_this->h_g_mmp_photo_file_s;
        break;      

    case MMP_IMG_IMAGE_ID_TEXT_ICON_L:
        *ph_img_tpl = pt_this->h_g_mmp_text_file_l;
        break;

    case MMP_IMG_IMAGE_ID_TEXT_ICON_M:
        *ph_img_tpl = pt_this->h_g_mmp_text_file_m;
        break;

    case MMP_IMG_IMAGE_ID_TEXT_ICON_S:
        *ph_img_tpl = pt_this->h_g_mmp_text_file_s;
        break;      
		
    case MMP_IMG_IMAGE_ID_FRM_BK:
        *ph_img_tpl = pt_this->h_g_mmp_frm_bk;
        break;
        
    case MMP_IMG_IMAGE_ID_BTN_NR_BK:
        *ph_img_tpl = pt_this->h_g_mmp_btn_nr_bk;
        break;
        
    case MMP_IMG_IMAGE_ID_BTN_HLT_BK:
        *ph_img_tpl = pt_this->h_g_mmp_btn_hlt_bk;
        break;
    
    case MMP_IMG_IMAGE_ID_SELECT_LISTMODE:
        *ph_img_tpl = pt_this->h_select_listmode;
        break;
    case MMP_IMG_IMAGE_ID_COPY_LISTMODE:
        *ph_img_tpl = pt_this->h_copy_listmode;
        break;
    case MMP_IMG_IMAGE_ID_SELECT_THUBNAIL:
        *ph_img_tpl = pt_this->h_g_mmp_btm_select_thumbnail;
        break;      
        
    case MMP_IMG_IMAGE_ID_SELECT_FILTER:  
        *ph_img_tpl = pt_this->h_g_mmp_btm_select_filter;
        break;  

    case MMP_IMG_IMAGE_ID_BTM_EXIT:
        *ph_img_tpl = pt_this->h_g_mmp_btm_exit;
        break;  

    case MMP_IMG_IMAGE_ID_PLAYING_REPEAT_ONE:
        *ph_img_tpl = pt_this->h_g_mmp_playing_repeat_one;
        break;
        
    case MMP_IMG_IMAGE_ID_PLAYING_REPEAT_ALL:
        *ph_img_tpl = pt_this->h_g_mmp_playing_repeat_all;
        break;

    case MMP_IMG_IMAGE_ID_PLAYING_A:
        *ph_img_tpl = pt_this->h_g_mmp_playing_a;
        break;
		
    case MMP_IMG_IMAGE_ID_PLAYING_AB:
        *ph_img_tpl = pt_this->h_g_mmp_playing_ab;
        break;
    
    case MMP_IMG_IMAGE_ID_PLAYING_SHUFFLE:
        *ph_img_tpl = pt_this->h_g_mmp_playing_shuffle;
        break;
        
    case MMP_IMG_IMAGE_ID_PLAYING_PLAY:
        *ph_img_tpl = pt_this->h_g_mmp_playing_play;
        break;
        
    case MMP_IMG_IMAGE_ID_PLAYING_PAUSE:
        *ph_img_tpl = pt_this->h_g_mmp_playing_pause;
        break;      
        
    case MMP_IMG_IMAGE_ID_PLAYING_STOP:  
        *ph_img_tpl = pt_this->h_g_mmp_playing_stop;
        break;  

    case MMP_IMG_IMAGE_ID_PLAYING_FF:
        *ph_img_tpl = pt_this->h_g_mmp_playing_ff;
        break;      
        
    case MMP_IMG_IMAGE_ID_PLAYING_FR:  
        *ph_img_tpl = pt_this->h_g_mmp_playing_fr;
        break;      

    case MMP_IMG_IMAGE_ID_PLAYING_VOL_NOR:
        *ph_img_tpl = pt_this->h_g_mmp_playing_vol_nor;
        break;      
        
    case MMP_IMG_IMAGE_ID_PLAYING_VOL_MUTE:  
        *ph_img_tpl = pt_this->h_g_mmp_playing_vol_mute;
        break;  
        
    case MMP_IMG_IMAGE_ID_THUMB_LOAD_FAIL_S:
        *ph_img_tpl = pt_this->h_g_mmp_thumbnail_load_fail_s;
        break;
        
    case MMP_IMG_IMAGE_ID_THUMB_LOAD_FAIL_M:
        *ph_img_tpl = pt_this->h_g_mmp_thumbnail_load_fail_m;
        break;      
        
    case MMP_IMG_IMAGE_ID_THUMB_LOAD_FAIL_L:  
        *ph_img_tpl = pt_this->h_g_mmp_thumbnail_load_fail_l;
        break;  
        
    case MMP_IMG_IMAGE_ID_MUSIC_PLAYER_BK:  
        *ph_img_tpl = pt_this->h_music_player_bk;
        break; 
        
    case MMP_IMG_IMAGE_ID_MUSIC_PLAYER_COVER_PIC_BK:  
        *ph_img_tpl = pt_this->h_music_player_cover_pic_bk;
        break; 

    case MMP_IMG_IMAGE_ID_LM_PLAY:
        *ph_img_tpl = pt_this->h_g_mmp_lm_play;
        break;

    case MMP_IMG_IMAGE_ID_LM_PAUSE:
        *ph_img_tpl = pt_this->h_g_mmp_lm_pause;
        break;
            
    default:
        return MMPR_INV_ARG;
    }

    return MMPR_OK;
}
