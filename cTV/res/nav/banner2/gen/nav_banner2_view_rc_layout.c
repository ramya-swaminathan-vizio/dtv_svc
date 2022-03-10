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
#include "wdk/wdk_api.h"

#include "res/nav/nav_img_rc.h"
#include "nav_banner2_view_rc_layout.h"
#include "res/nav/nav_bnr_item_def.h"
#include "res/nav/banner2/banner_rc.h"
#include "c_wgl.h"
#include "res/nav/nav_dbg.h"

#define INSERT_GAP_SMAll  (12)
#define INSERT_GAP_NORMAL (64)
#define INSERT_GAP_LARGE  (96)

#define BANNER2_S         (96)
#define BANNER2_T         (0)
#define BANNER2_B         (160)
#define BANNER2_DB        (415)

#define BANNER_BORDER_STYLE  WGL_BORDER_NULL
//#define BANNER_BORDER_STYLE  WGL_BORDER_UNIFORM


#define BANNER2_TV_NAME_S (0   + BANNER2_S)
#define BANNER2_TV_NAME_W (400)
#define BANNER2_TV_NAME_E (BANNER2_TV_NAME_S + BANNER2_TV_NAME_W)

#define BANNER2_IPTS_ICON_S (BANNER2_TV_NAME_E +  INSERT_GAP_SMAll)
#define BANNER2_IPTS_ICON_W (54)
#define BANNER2_IPTS_ICON_E (BANNER2_IPTS_ICON_S + BANNER2_IPTS_ICON_W)

#define BANNER2_CH_NAME_S   (BANNER2_IPTS_ICON_E + INSERT_GAP_SMAll)
#define BANNER2_CH_NAME_W   (300)
#define BANNER2_CH_NAME_E   (BANNER2_CH_NAME_S + BANNER2_CH_NAME_W)

#define BANNER2_CH_INPUT_NO_S   (BANNER2_CH_NAME_E + INSERT_GAP_NORMAL)
#define BANNER2_CH_INPUT_NO_W   (200)
#define BANNER2_CH_INPUT_NO_E   (BANNER2_CH_NAME_S + BANNER2_CH_NAME_W)

#define BANNER2_SCREEN_W (1920)
#define BANNER2_SCREEN_H (1080)

#define BANNER2_TIMER_24_E (BANNER2_SCREEN_W - BANNER2_S)
#define BANNER2_TIMER_24_W  (190)
#define BANNER2_TIMER_24_S  (BANNER2_TIMER_24_E - BANNER2_TIMER_24_W )

#define BANNER2_TIMER_APM_S  BANNER2_TIMER_24_S
#define BANNER2_TIMER_APM_W  BANNER2_TIMER_24_W
#define BANNER2_TIMER_APM_E  BANNER2_TIMER_24_E

#define BANNER2_WIFI_TXT_E (BANNER2_TIMER_APM_S - INSERT_GAP_NORMAL)
#define BANNER2_WIFI_TXT_W  (210)
#define BANNER2_WIFI_TXT_S  (BANNER2_WIFI_TXT_E - BANNER2_WIFI_TXT_W)

#define BANNER2_WIFI_ICON_E (BANNER2_WIFI_TXT_S - INSERT_GAP_SMAll)
#define BANNER2_WIFI_ICON_W  (36)
#define BANNER2_WIFI_ICON_S  (BANNER2_WIFI_ICON_E - BANNER2_WIFI_ICON_W)

#if (CUSTOMER == VIZIO)
/* insert headphones icon between Dolby Audio and Wifi icons */
#define BANNER2_HEADPHONES_ICON_E  (BANNER2_WIFI_ICON_S - INSERT_GAP_NORMAL)
#define BANNER2_HEADPHONES_ICON_W  (40)
#define BANNER2_HEADPHONES_ICON_S  (BANNER2_HEADPHONES_ICON_E - BANNER2_HEADPHONES_ICON_W)

#define BANNER2_DOLBY_AUDIO_ICON_E (BANNER2_HEADPHONES_ICON_S - INSERT_GAP_NORMAL)
#define BANNER2_DOLBY_AUDIO_ICON_W  (116)
#define BANNER2_DOLBY_AUDIO_ICON_S  (BANNER2_DOLBY_AUDIO_ICON_E - BANNER2_DOLBY_AUDIO_ICON_W)

#define BANNER2_AUDIO_FMT_E (BANNER2_HEADPHONES_ICON_S - INSERT_GAP_NORMAL)
#define BANNER2_AUDIO_FMT_W  (120)
#define BANNER2_AUDIO_FMT_S  (BANNER2_AUDIO_FMT_E - BANNER2_AUDIO_FMT_W)

#else
#define BANNER2_DOLBY_AUDIO_ICON_E (BANNER2_WIFI_ICON_S - INSERT_GAP_NORMAL)
#define BANNER2_DOLBY_AUDIO_ICON_W  (116)
#define BANNER2_DOLBY_AUDIO_ICON_S  (BANNER2_DOLBY_AUDIO_ICON_E - BANNER2_DOLBY_AUDIO_ICON_W)

#define BANNER2_AUDIO_FMT_E (BANNER2_WIFI_ICON_S - INSERT_GAP_NORMAL)
#define BANNER2_AUDIO_FMT_W  (120)
#define BANNER2_AUDIO_FMT_S  (BANNER2_AUDIO_FMT_E - BANNER2_AUDIO_FMT_W)
#endif

#define BANNER2_DOLBY_VISION_ICON_E (BANNER2_DOLBY_AUDIO_ICON_S - INSERT_GAP_NORMAL)
#define BANNER2_DOLBY_VISION_ICON_W  (128)
#define BANNER2_DOLBY_VISION_ICON_S  (BANNER2_DOLBY_VISION_ICON_E - BANNER2_DOLBY_VISION_ICON_W)

#define BANNER2_RESOLUTION_TXT_E   (BANNER2_DOLBY_VISION_ICON_S - INSERT_GAP_NORMAL)
#define BANNER2_RESOLUTION_TXT_W    (150)
#define BANNER2_RESOLUTION_TXT_S   (BANNER2_RESOLUTION_TXT_E - BANNER2_RESOLUTION_TXT_W)

#define BANNER2_ASPECT_TXT_E   (BANNER2_RESOLUTION_TXT_S - INSERT_GAP_NORMAL)
#define BANNER2_ASPECT_TXT_W    (100)
#define BANNER2_ASPECT_TXT_S   (BANNER2_ASPECT_TXT_E - BANNER2_ASPECT_TXT_W)

#define BANNER2_CLOSED_CAPTION_ICON_E   (BANNER2_ASPECT_TXT_S - INSERT_GAP_NORMAL)
#define BANNER2_CLOSED_CAPTION_ICON_W    (35)
#define BANNER2_CLOSED_CAPTION_ICON_S   (BANNER2_CLOSED_CAPTION_ICON_E - BANNER2_CLOSED_CAPTION_ICON_W)


static WDK_IMG_INFO_T t_bk_img_info_nav_banner2_view_rc_frm_root =
{
    WGL_IMG_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_bk_clr_info_frm_root =
{
    WGL_COLOR_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static GL_COLOR_T t_g_gray = {0xff, {0x2c}, {0x2c}, {0x2c}};


static WDK_COLOR_INFO_T t_bk_clr_info_sidebar_dv =
{
    WGL_COLOR_SET_BASIC,
    {
        //&t_g_gray,
        //&t_g_gray,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_bk_clr_info_sidebar_dd_audio =
{
    WGL_COLOR_SET_BASIC,
    {
        &t_g_gray,
        &t_g_gray,
        NULL,
        NULL,
        NULL,
        NULL
    }
};


static WDK_COLOR_INFO_T t_bk_clr_info_sidebar_progaming_engine =
{
    WGL_COLOR_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_bk_clr_info_sidebar_filmmaker_mode =
{
    WGL_COLOR_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_bk_clr_info_sidebar_freesync =
{
    WGL_COLOR_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};



//Cedric banner root frame
static WDK_FRM_WGT_T t_wdk_param_nav_banner2_view_rc_frm_root =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, NAV_BANNER_ROOT_FRM_WGL_EX, BANNER2_DB},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    NULL
};

static WDK_FONT_INFO_T t_item_ch_and_inp_src_text_font_info_name =
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_banner2_small_font_custom_name_size,
        &t_g_banner2_small_font_custom_name_size
    }
};


static WDK_FONT_INFO_T t_item_ch_and_inp_src_text =
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_banner2_custom_font_custom_name_size,
        &t_g_banner2_custom_font_custom_name_size
    }
};

static WDK_FONT_INFO_T t_item_prog_info_text_font_info =
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_banner2_small_font_small_size,
        &t_g_banner2_small_font_small_size
    }
};

static WDK_FONT_INFO_T t_item_prog_info_text_title_font_info =
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_banner2_small_font_custom_title_size,
        &t_g_banner2_small_font_custom_title_size
    }
};

static WDK_FONT_INFO_T t_g_banner2_time_font_custom_time_size =
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_banner2_time_font_custom_size,
        &t_g_banner2_time_font_custom_size
    }
};

static WDK_FONT_INFO_T t_font_info_txt_itm_msg =
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_banner2_small_font_medium_size,
        &t_g_banner2_small_font_medium_size
    }
};

static WDK_COLOR_INFO_T t_item_prog_info_text_color_black_info =
{
    WGL_COLOR_SET_STANDARD,
    {
        &t_g_banner2_color_text,
        &t_g_banner2_color_text,
        &t_g_banner2_color_text,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_item_prog_info_text_color_info =
{
    WGL_COLOR_SET_STANDARD,
    {
        &t_g_banner2_color_text,
        &t_g_banner2_color_text,
        &t_g_banner2_color_text,
        NULL,
        NULL,
        NULL
    }
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_prog_title =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_512,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_S, 180, 410, 230},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_LEFT_TOP,
    &t_item_prog_info_text_title_font_info,
    &t_item_prog_info_text_color_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_input_ch_no =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_CH_INPUT_NO_S, 0, BANNER2_CH_INPUT_NO_E, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_LEFT_CENTER,/*WGL_AS_RIGHT_CENTER,*/
    &t_item_ch_and_inp_src_text_font_info_name,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_ch_no =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {550, 0, 670, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_RIGHT_CENTER,
    &t_item_ch_and_inp_src_text_font_info_name,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_ch_name =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|/*WGL_STL_TEXT_MULTILINE|*/WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_CH_NAME_S, 0, BANNER2_CH_NAME_E, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_LEFT_CENTER,
    &t_item_ch_and_inp_src_text_font_info_name,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_prog_crnt_time =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_S, 280, 600, 330},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_LEFT_CENTER,
    &t_item_prog_info_text_title_font_info,
    &t_item_prog_info_text_color_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_nav_banner2_view_rc_icon_itm_tv_lock =
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_banner_lock_img,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_icon_itm_tv_lock =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_BK,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_SX, 0, NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_EX, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_tv_lock,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_rating =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MULTILINE|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_S, 230, 400, 280},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_LEFT_CENTER,
    &t_item_prog_info_text_title_font_info,
    &t_item_prog_info_text_color_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_nav_banner2_view_rc_icon_itm_caption_icon =
{
    WGL_IMG_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_icon_itm_caption_icon =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_BK,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_CLOSED_CAPTION_ICON_S, BANNER2_CLOSED_CAPTION_ICON_W, BANNER2_CLOSED_CAPTION_ICON_E, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_caption_icon,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_caption =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_SX, NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_SY, NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_EX + 20, NAV_BANNER_LEVEL_1_INFO_RESOLUTION_WGL_EY},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_CENTER_CENTER,
    &t_item_prog_info_text_font_info,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_audio_info_lang =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_S, 304, 400, 300},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_CENTER_CENTER,
    &t_item_prog_info_text_font_info,
    &t_item_prog_info_text_color_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_video_info =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MULTILINE|WGL_STL_TEXT_MAX_512,
    180,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {800, 0, 1030, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_RIGHT_CENTER,
    &t_item_prog_info_text_font_info,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_icon_itm_prog_detail_pg_up =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_BK,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {834-234, 62, 860-234, 90},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_nav_banner2_view_rc_frm_root,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_prog_detail_pg_idx =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MULTILINE|WGL_STL_TEXT_MAX_32,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {821-234, 87, 873-234, 114},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_CENTER_CENTER,
    &t_item_prog_info_text_font_info,
    &t_item_prog_info_text_color_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_icon_itm_prog_detail_pg_dn =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_BK,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {834-234, 107, 860-234, 135},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_nav_banner2_view_rc_frm_root,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_prog_detail =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MULTILINE|WGL_STL_TEXT_MAX_4096,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {500, 180, BANNER2_SCREEN_W, 300},

    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_itm_msg,
    &t_item_prog_info_text_color_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_msg =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_512,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {682, 0, 960, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_LEFT_CENTER,
    &t_item_ch_and_inp_src_text_font_info_name,
    &t_item_prog_info_text_color_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

//Cedric program detail level 3
static WDK_IMG_INFO_T t_bk_img_info_nav_banner2_view_rc_frm_itm_pdch =
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_nav_banner_new_bg_level2_icon,
        &h_g_nav_banner_new_bg_level2_icon,
        &h_g_nav_banner_new_bg_level2_icon,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_nav_banner2_view_rc_frm_itm_pdch =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    0,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, BANNER2_B, BANNER2_SCREEN_W, BANNER2_DB},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_itm_pdch},
    NULL
};

//Cedric program title level 2
static WDK_IMG_INFO_T t_bk_img_info_nav_banner2_view_rc_frm_itm_pch =
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_nav_banner_new_bg_level2_icon,
        &h_g_nav_banner_new_bg_level2_icon,
        &h_g_nav_banner_new_bg_level2_icon,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_nav_banner2_view_rc_frm_itm_pch =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    0,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, BANNER2_B, BANNER2_SCREEN_W, BANNER2_DB},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_itm_pch},
    NULL
};

//Cedric program info level 1
static WDK_IMG_INFO_T t_bk_img_info_nav_banner2_view_rc_frm_itm_ch =
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_nav_banner_new_bg_info_toast_icon,
        &h_g_nav_banner_new_bg_info_toast_icon,
        &h_g_nav_banner_new_bg_info_toast_icon,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_nav_banner2_view_rc_frm_itm_ch =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0,0,BANNER2_SCREEN_W,BANNER2_B},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_itm_ch},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_nav_banner2_view_rc_frm_itm_3d =
{
    WGL_IMG_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_nav_banner2_view_rc_frm_itm_3d =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {550-234, 32, 866-234, 63},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_itm_3d},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_timer_24 =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_TIMER_24_S, 0, BANNER2_TIMER_24_E, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_RIGHT_CENTER,
    &t_g_banner2_time_font_custom_time_size,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_3d_mode =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {550-234, 32, 708-234, 63},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_CENTER_CENTER,
    &t_item_prog_info_text_font_info,
    &t_item_prog_info_text_color_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_3d_fmt =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {708-234, 32, 866-234, 63},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_CENTER_CENTER,
    &t_item_prog_info_text_font_info,
    &t_item_prog_info_text_color_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_prog_next_title =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_512,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 50, 50, 100},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_LEFT_TOP,
    &t_item_prog_info_text_font_info,
    &t_item_prog_info_text_color_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_prog_next_time =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {167, 192, 336-234, 214},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_RIGHT_TOP,
    &t_item_prog_info_text_font_info,
    &t_item_prog_info_text_color_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_nav_banner2_view_rc_icon_itm_ad_eye =
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_banner_ad_eye_img,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_icon_itm_ad_eye =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_BK,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 61, 38, 96},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_TOP,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_ad_eye,
    0,
    0,
    0,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_icon_itm_ipts_lock =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_BK,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 50, 50},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_nav_banner2_view_rc_frm_root,
    0,
    0,
    0,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_nav_banner2_view_rc_icon_itm_input_icon =
{
    WGL_IMG_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_icon_itm_input_icon =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_BK,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_IPTS_ICON_S,0,BANNER2_IPTS_ICON_E,160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_input_icon,
    0,
    0,
    0,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_nav_banner2_view_rc_icon_itm_wifi_icon =
{
    WGL_IMG_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_icon_itm_wifi_icon =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_BK,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_WIFI_ICON_S,0,BANNER2_WIFI_ICON_E,160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_wifi_icon,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_wifi =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    180,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_WIFI_TXT_S, 0, BANNER2_WIFI_TXT_E, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_LEFT_CENTER,
    &t_item_ch_and_inp_src_text,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_audio_format =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    180,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_AUDIO_FMT_S, 0, BANNER2_AUDIO_FMT_E, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_RIGHT_CENTER,
    &t_item_ch_and_inp_src_text,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_tv_name =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_TV_NAME_S, 0, BANNER2_TV_NAME_E, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_LEFT_CENTER,
    &t_g_banner2_time_font_custom_time_size,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_fg_img_info_nav_banner2_view_rc_icon_itm_resolution_txt =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    180,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_RESOLUTION_TXT_S, 0, BANNER2_RESOLUTION_TXT_E, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_RIGHT_CENTER,
    &t_item_ch_and_inp_src_text,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_nav_banner2_view_rc_icon_itm_dolby_icon =
{
    WGL_IMG_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_IMG_INFO_T t_fg_img_info_nav_banner2_view_rc_icon_itm_dd_audio =
{
    WGL_IMG_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};


static WDK_IMG_INFO_T t_fg_img_info_nav_banner2_view_rc_icon_itm_progaming_engine =
{
    WGL_IMG_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_IMG_INFO_T t_fg_img_info_nav_banner2_view_rc_icon_itm_filmmaker_mode =
{
    WGL_IMG_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};


static WDK_IMG_INFO_T t_fg_img_info_nav_banner2_view_rc_icon_itm_freesync =
{
    WGL_IMG_SET_BASIC,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};


static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_icon_itm_dolby_audio_icon =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_BK,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_DOLBY_AUDIO_ICON_S, 0, BANNER2_DOLBY_AUDIO_ICON_E, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_dolby_icon,
    0,
    0,
    0,
    NULL
};

#if (CUSTOMER == VIZIO)
static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_icon_itm_headphones_icon =
{
    NULL_HANDLE,           // h_parent
    BANNER_BORDER_STYLE,   // ui4_border
    NULL,                  // pt_border
    WGL_STL_GL_NO_BK,      // ui4_style
    220,                   // ui1_alpha
    TRUE,                  // ui1_enable
    WGL_SW_NORMAL,         // ui1_visibility
    NULL,                  // pf_wdgt_proc
    {BANNER2_HEADPHONES_ICON_S, 0, BANNER2_HEADPHONES_ICON_E, 160},          // t_rect
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},  // t_bk_set
    {0, 0, 0, 0},          // t_cnt_inset
    WGL_AS_CENTER_CENTER,  // ui1_align
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_dolby_icon,   // pt_fg_img
    0,                     // u4_multi_image_max
    0,                     // u4_multi_image_num
    0,                     // pt_img_node
    NULL                   // pv_data
};
#endif

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_icon_itm_dolby_vision_icon =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_BK,
    220,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_DOLBY_VISION_ICON_S, 0, BANNER2_DOLBY_VISION_ICON_E, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_dolby_icon,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_aspect =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    180,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_ASPECT_TXT_S, 0, BANNER2_ASPECT_TXT_E, 160},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_RIGHT_CENTER,
    &t_item_ch_and_inp_src_text,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_nav_banner2_view_rc_txt_itm_audio_out =
{
    NULL_HANDLE,
    BANNER_BORDER_STYLE,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER2_DOLBY_AUDIO_ICON_S, 0, BANNER2_DOLBY_AUDIO_ICON_E, 40},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_RIGHT_CENTER,
    &t_item_ch_and_inp_src_text,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};


static WDK_ITEM_T t_wdk_item_frm_root_array[] =
{
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_TITLE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_prog_title,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_TV_NAME,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_tv_name,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_INPUT_CH_NO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_input_ch_no,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CH_NO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_ch_no,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CH_NAME,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_ch_name,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_CRNT_TIME,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_prog_crnt_time,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_RATING,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_rating,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_NAV_BANNER2_VIEW_RC_ICON_ITM_CAPTION_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_icon_itm_caption_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CAPTION,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_caption,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_INFO_LANG,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_audio_info_lang,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_VIDEO_INFO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_video_info,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_NAV_BANNER2_VIEW_RC_ICON_ITM_PROG_DETAIL_PG_UP,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_icon_itm_prog_detail_pg_up,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_DETAIL_PG_IDX,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_prog_detail_pg_idx,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_NAV_BANNER2_VIEW_RC_ICON_ITM_PROG_DETAIL_PG_DN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_icon_itm_prog_detail_pg_dn,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_DETAIL,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_prog_detail,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_MSG,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_msg,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_3D_MODE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_3d_mode,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_3D_FMT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_3d_fmt,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_NEXT_TITLE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_prog_next_title,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_NEXT_TIME,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_prog_next_time,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_NAV_BANNER2_VIEW_RC_ICON_ITM_TV_LOCK,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_icon_itm_tv_lock,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_NAV_BANNER2_VIEW_RC_ICON_ITM_AD_EYE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_icon_itm_ad_eye,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_NAV_BANNER2_VIEW_RC_ICON_ITM_IPTS_LOCK,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_icon_itm_ipts_lock,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_NAV_BANNER2_VIEW_RC_FRM_ITM_PDCH,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_frm_itm_pdch,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_NAV_BANNER2_VIEW_RC_FRM_ITM_PCH,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_frm_itm_pch,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_NAV_BANNER2_VIEW_RC_FRM_ITM_CH,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_frm_itm_ch,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_NAV_BANNER2_VIEW_RC_FRM_ITM_3D,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_frm_itm_3d,
        NULL
    }
    ,{
        HT_WGL_WIDGET_ICON,
        WID_NAV_BANNER2_VIEW_RC_ICON_ITM_INPUT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_icon_itm_input_icon,
        NULL
    }
    ,{
        HT_WGL_WIDGET_ICON,
        WID_NAV_BANNER2_VIEW_RC_ICON_ITM_WIFI,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_icon_itm_wifi_icon,
        NULL
    }
    ,{
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_ASPECT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_aspect,
        NULL
    }
    ,{
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_WIFI_TXT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_wifi,
        NULL
    }
   ,{
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_FORMAT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_audio_format,
        NULL
    }
   ,{
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_TIMER_24,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_timer_24,
        NULL
    }
   ,{
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_RESOLUTION,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_fg_img_info_nav_banner2_view_rc_icon_itm_resolution_txt,
        NULL
    }

   ,{
       HT_WGL_WIDGET_ICON,
       WID_NAV_BANNER2_VIEW_RC_ICON_ITM_DOLBY_VISION,
       WDK_FRM_OPT_BK_IMG,
       (VOID *) &t_wdk_param_nav_banner2_view_rc_icon_itm_dolby_vision_icon,
       NULL
   }

   ,{
       HT_WGL_WIDGET_ICON,
       WID_NAV_BANNER2_VIEW_RC_ICON_ITM_DOLBY_AUDIO,
       WDK_FRM_OPT_BK_IMG,
       (VOID *) &t_wdk_param_nav_banner2_view_rc_icon_itm_dolby_audio_icon,
       NULL
   },
#if (CUSTOMER == VIZIO)
   {
       HT_WGL_WIDGET_ICON,
       WID_NAV_BANNER2_VIEW_RC_ICON_ITM_HEADPHONES,
       WDK_FRM_OPT_BK_IMG,
       (VOID *) &t_wdk_param_nav_banner2_view_rc_icon_itm_headphones_icon,
       NULL
   },
#endif
   {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_OUT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_txt_itm_audio_out,
        NULL
    }

};

//width
//HDR10+ > (160+32)
//DV > (75)
//DD > (75)
//PE > (100)
//FM > (75)
//FS > (75)

//height
//All > (96+10)

// 32/word,now 6 word 1 line
#define BANNER_SB_HDR_TEXT_W (160+32)
#define BANNER_SB_HDR_TEXT_H (100)

//as dolby request,logo need show be displayed in center,and make blank space in side
#define BANNER_SB_DV_W (128+50)
#define BANNER_SB_DV_H (100)

#define BANNER_SB_DD_W (116)
#define BANNER_SB_DD_H (100)

#define BANNER_SB_PE_W (150)
#define BANNER_SB_PE_H (100)

#define BANNER_SB_FM_W (49)
#define BANNER_SB_FM_H (100)

#define BANNER_SB_FS_W (128)
#define BANNER_SB_FS_H (100)

//custom spec 34 pixels space between icon
#define BANNER_SB_ICON_SPACE (34)
//the rightest item space to the right border
#define BANNER_SB_BORDER_SPACE (48)

//total width
#define BANNER_SIDERBAR_W (BANNER_SB_HDR_TEXT_W+BANNER_SB_DV_W+BANNER_SB_DD_W+BANNER_SB_PE_W+BANNER_SB_FM_W+BANNER_SB_FS_W+BANNER_SB_ICON_SPACE*5)
//the max highth,because WGL_AS_CENTER_CENTER to make sure logo in a line
#define BANNER_SIDERBAR_H (100)


#define BANNER_SIDERBAR_X (BANNER2_SCREEN_W - BANNER_SIDERBAR_W - BANNER_SB_BORDER_SPACE)
#define BANNER_SIDERBAR_Y (BANNER_SB_BORDER_SPACE)

//all item set to the rightest position,need adjust position before show it
#define BANNER_SB_HDR_TEXT_X ((BANNER_SIDERBAR_W - BANNER_SB_HDR_TEXT_W))
#define BANNER_SB_HDR_TEXT_Y (0)

#define BANNER_SB_DV_X ((BANNER_SIDERBAR_W - BANNER_SB_DV_W))
#define BANNER_SB_DV_Y (0)

#define BANNER_SB_DD_X ((BANNER_SIDERBAR_W - BANNER_SB_DD_W))
#define BANNER_SB_DD_Y (0)

#define BANNER_SB_PE_X ((BANNER_SIDERBAR_W - BANNER_SB_PE_W))
#define BANNER_SB_PE_Y (0)

#define BANNER_SB_FM_X ((BANNER_SIDERBAR_W - BANNER_SB_FM_W))
#define BANNER_SB_FM_Y (0)

#define BANNER_SB_FS_X ((BANNER_SIDERBAR_W - BANNER_SB_FS_W))
#define BANNER_SB_FS_Y (0)



static WDK_FRM_WGT_T t_wdk_param_nav_banner2_view_rc_frm_sider_bar =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER_SIDERBAR_X,BANNER_SIDERBAR_Y ,BANNER_SIDERBAR_X + BANNER_SIDERBAR_W, BANNER_SIDERBAR_Y + BANNER_SIDERBAR_H},
    {&t_bk_clr_info_sidebar_dv, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    NULL
};

static WDK_TXT_WGT_T t_fg_img_info_nav_banner2_view_rc_itm_hdr_txt =
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    180,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER_SB_HDR_TEXT_X,BANNER_SB_HDR_TEXT_Y,BANNER_SB_HDR_TEXT_X+BANNER_SB_HDR_TEXT_W, BANNER_SB_HDR_TEXT_Y+BANNER_SB_HDR_TEXT_H},
    {&t_bk_clr_info_frm_root, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_CENTER_CENTER,
    &t_g_banner2_time_font_custom_time_size,
    &t_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};


static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_itm_dv_icon =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER_SB_DV_X,BANNER_SB_DV_Y,BANNER_SB_DV_X + BANNER_SB_DV_W, BANNER_SB_DV_Y + BANNER_SB_DV_H},
    {&t_bk_clr_info_sidebar_dv, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_dolby_icon,
    0,
    0,
    0,
    NULL
};


static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_itm_dd_icon =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER_SB_DD_X,BANNER_SB_DD_Y,BANNER_SB_DD_X + BANNER_SB_DD_W, BANNER_SB_DD_Y + BANNER_SB_DD_H},
    {&t_bk_clr_info_sidebar_dd_audio, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_dd_audio,
    0,
    0,
    0,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_itm_progaming_engine =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER_SB_PE_X,BANNER_SB_PE_Y,BANNER_SB_PE_X + BANNER_SB_PE_W, BANNER_SB_PE_Y + BANNER_SB_PE_H},
    {&t_bk_clr_info_sidebar_progaming_engine, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_progaming_engine,
    0,
    0,
    0,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_itm_filmmaker_mode =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER_SB_FM_X,BANNER_SB_FM_Y,BANNER_SB_FM_X + BANNER_SB_FM_W, BANNER_SB_FM_Y + BANNER_SB_FM_H},
    {&t_bk_clr_info_sidebar_filmmaker_mode, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_filmmaker_mode,
    0,
    0,
    0,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_nav_banner2_view_rc_itm_freesync =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {BANNER_SB_FS_X,BANNER_SB_FS_Y,BANNER_SB_FS_X + BANNER_SB_FS_W, BANNER_SB_FS_Y + BANNER_SB_FS_H},
    {&t_bk_clr_info_sidebar_freesync, &t_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_nav_banner2_view_rc_icon_itm_freesync,
    0,
    0,
    0,
    NULL
};


static WDK_ITEM_T t_wdk_item_frm_siderbar_array[] =
{
    {
        HT_WGL_WIDGET_TEXT,
        WID_NAV_BANNER2_SIDERBAR_VIEW_RC_TXT_ITM_SIDER_HDR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_fg_img_info_nav_banner2_view_rc_itm_hdr_txt,
        NULL
    }

   ,{
       HT_WGL_WIDGET_ICON,
       WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION,
       WDK_FRM_OPT_BK_IMG,
       (VOID *) &t_wdk_param_nav_banner2_view_rc_itm_dv_icon,
       NULL
   }
   ,{
        HT_WGL_WIDGET_ICON,
        WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_AUDIO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_itm_dd_icon,
        NULL
   }
  ,{
       HT_WGL_WIDGET_ICON,
       WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE,
       WDK_FRM_OPT_BK_IMG,
       (VOID *) &t_wdk_param_nav_banner2_view_rc_itm_progaming_engine,
       NULL
   }
  ,{
       HT_WGL_WIDGET_ICON,
       WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE,
       WDK_FRM_OPT_BK_IMG,
       (VOID *) &t_wdk_param_nav_banner2_view_rc_itm_filmmaker_mode,
       NULL
   }
  ,{
       HT_WGL_WIDGET_ICON,
       WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FREESYNC,
       WDK_FRM_OPT_BK_IMG,
       (VOID *) &t_wdk_param_nav_banner2_view_rc_itm_freesync,
       NULL
   }

};

static WDK_ITEM_LIST_T t_wdk_list_frm_sider_bar =
{
    sizeof(t_wdk_item_frm_siderbar_array)/sizeof(t_wdk_item_frm_siderbar_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_siderbar_array
};


static WDK_ITEM_T t_wdk_item_view_view_siderbar_array[] =
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_NAV_BANNER2_SIDERBAR_VIEW_RC_FRM_SIDER_BAR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_frm_sider_bar,
        (VOID *) &t_wdk_list_frm_sider_bar
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_siderbar_rc =
{
    sizeof(t_wdk_item_view_view_siderbar_array)/sizeof(t_wdk_item_view_view_siderbar_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_view_siderbar_array
};

static WDK_ITEM_LIST_T t_wdk_list_frm_root =
{
    sizeof(t_wdk_item_frm_root_array)/sizeof(t_wdk_item_frm_root_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_root_array
};

static WDK_ITEM_T t_wdk_item_view_view_rc_array[] =
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_NAV_BANNER2_VIEW_RC_FRM_ROOT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_nav_banner2_view_rc_frm_root,
        (VOID *) &t_wdk_list_frm_root
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_view_rc =
{
    sizeof(t_wdk_item_view_view_rc_array)/sizeof(t_wdk_item_view_view_rc_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_view_rc_array
};

static HANDLE_T ah_wgt_handle_nav_banner2_view_rc[WID_NAV_BANNER2_VIEW_RC_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_nav_banner2_view_rc[WID_NAV_BANNER2_VIEW_RC_TOTAL_COUNT];


static HANDLE_T ah_wgt_handle_nav_banner2_siderbar_view_rc[WID_NAV_BANNER2_SIDERBAR_VIEW_RC_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_nav_banner2_siderbar_view_rc[WID_NAV_BANNER2_SIDERBAR_VIEW_RC_TOTAL_COUNT] = {c_wgl_default_msg_proc};

INT32 nav_banner2_view_rc_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_nav_banner2_view_rc, 0,
             WID_NAV_BANNER2_VIEW_RC_TOTAL_COUNT*sizeof(af_wgt_cb_nav_banner2_view_rc[0]));
    return (WDKR_OK);
}

INT32 nav_banner2_view_rc_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_NAV_BANNER2_VIEW_RC_TOTAL_COUNT)
    {
        af_wgt_cb_nav_banner2_view_rc[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }
    return (WDKR_FAILED);
}

INT32 nav_banner2_view_rc_create_siderbar_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container,
                                 &t_wdk_list_view_siderbar_rc,
                                 ah_wgt_handle_nav_banner2_siderbar_view_rc,
                                 af_wgt_cb_nav_banner2_siderbar_view_rc));
}

INT32 nav_banner2_view_rc_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container,
                                 &t_wdk_list_view_view_rc,
                                 ah_wgt_handle_nav_banner2_view_rc,
                                 af_wgt_cb_nav_banner2_view_rc));
}

HANDLE_T nav_banner2_view_rc_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_NAV_BANNER2_VIEW_RC_TOTAL_COUNT)
    {
        return ah_wgt_handle_nav_banner2_view_rc[e_widget_id];
    }

    return (NULL_HANDLE);
}


HANDLE_T nav_banner2_view_rc_get_siderbar_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_NAV_BANNER2_SIDERBAR_VIEW_RC_TOTAL_COUNT)
    {
        return ah_wgt_handle_nav_banner2_siderbar_view_rc[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 nav_banner2_view_rc_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_view_rc,
                                      ah_wgt_handle_nav_banner2_view_rc,
                                      mlm_nav_banner2_get_text,
                                      ui2_lang));
}

INT32 nav_banner2_view_rc_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_view_rc,
                                         ah_wgt_handle_nav_banner2_view_rc))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 nav_banner2_view_rc_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_NAV_BANNER2_VIEW_RC_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container,
                                 &t_wdk_list_view_view_rc,
                                 *pt_mi,
                                 af_wgt_cb_nav_banner2_view_rc));
}

HANDLE_T nav_banner2_view_rc_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_nav_banner2_view_rc = NULL;

    h_wgt_handle_nav_banner2_view_rc = (VOID *)t_mi;

    if (NULL == h_wgt_handle_nav_banner2_view_rc)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_NAV_BANNER2_VIEW_RC_TOTAL_COUNT)
    {
        return h_wgt_handle_nav_banner2_view_rc[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 nav_banner2_view_rc_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_view_rc,
                                      (HANDLE_T *)t_mi,
                                      mlm_nav_banner2_get_text,
                                      ui2_lang));
}

INT32 nav_banner2_view_rc_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_view_rc, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}

GL_RECT_T*  nav_banner2_view_rc_get_wgt_rect(UINT8 u1_item_id)
{
   UINT8  u1_hd_id;

   if(u1_item_id >= BANNER_ITM_LAST_VALID_ENTRY )
   {
       return NULL;
   }

   switch(u1_item_id)
   {
        case  BANNER_ITM_FRM_CH              :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_FRM_ITM_CH                 ;break ;
        case  BANNER_ITM_IPTS_ICON           :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_ICON_ITM_INPUT             ;break ;
        case  BANNER_ITM_WIFI_ICON           :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_ICON_ITM_WIFI              ;break  ;
        case  BANNER_ITM_ASPECT              :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_ASPECT             ;break ;
        case  BANNER_ITM_RESOLUTION_TXT      :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_RESOLUTION         ;break ;
        case  BANNER_ITM_TIMER_24            :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_TIMER_24           ;break ;
        case  BANNER_ITM_FRM_INF             :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_FRM_ITM_PCH                ;break ;
        case  BANNER_ITM_FRM_DTL             :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_FRM_ITM_PDCH               ;break ;
        case  BANNER_ITM_WIFI_TXT            :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_WIFI_TXT           ;break ;
        case  BANNER_ITM_TV_NAME             :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_TV_NAME            ;break ;
        case  BANNER_ITM_CH_NO               :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CH_NO              ;break  ;
        case  BANNER_ITM_CH_NAME             :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CH_NAME            ;break ;
        case  BANNER_ITM_MSG                 :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_MSG                ;break ;
        case  BANNER_ITM_PROG_TITLE          :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_TITLE         ;break ;
        case  BANNER_ITM_PROG_TIME           :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_CRNT_TIME     ;break ;
        case  BANNER_ITM_NEXT_PROG_TITLE     :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_NEXT_TITLE    ;break ;
        case  BANNER_ITM_NEXT_PROG_TIME      :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_NEXT_TIME     ;break ;
        case  BANNER_ITM_PROG_DETAIL         :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_DETAIL        ;break  ;
        case  BANNER_ITM_PROG_DETAIL_PG_IDX  :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_DETAIL_PG_IDX ;break  ;
        case  BANNER_ITM_RATING              :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_RATING             ;break  ;
        case  BANNER_ITM_CAPTION             :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CAPTION            ;break  ;
        case  BANNER_ITM_AUDIO_LANG          :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_INFO_LANG    ;break  ;
        case  BANNER_ITM_VIDEO_INFO          :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_VIDEO_INFO         ;break  ;
        case  BANNER_ITM_IPT_CH_NO           :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_INPUT_CH_NO        ;break  ;
        case  BANNER_ITM_3D_MODE             :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_3D_MODE            ;break  ;
        case  BANNER_ITM_3D_FMT              :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_3D_FMT             ;break  ;
        case  BANNER_ITM_IPTS_LOCK_ICON      :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_ICON_ITM_IPTS_LOCK         ;break  ;
        case  BANNER_ITM_TV_LOCK_ICON        :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_ICON_ITM_TV_LOCK           ;break  ;
        case  BANNER_ITM_CAPTION_ICON        :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_ICON_ITM_CAPTION_ICON      ;break  ;
        case  BANNER_ITM_PROG_DETAIL_UP_ICON :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_ICON_ITM_PROG_DETAIL_PG_UP ;break  ;
        case  BANNER_ITM_PROG_DETAIL_DN_ICON :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_ICON_ITM_PROG_DETAIL_PG_DN ;break  ;
        case  BANNER_ITM_AD_EYE              :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_ICON_ITM_AD_EYE            ;break  ;
        case  BANNER_ITM_FRM_3D              :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_FRM_ITM_3D                 ;break  ;
        case  BANNER_ITM_AUDIO_FARMAT        :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_FORMAT       ;break  ;
        case  BANNER_ITM_DOLBY_VISION        :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_ICON_ITM_DOLBY_VISION      ;break  ;
        case  BANNER_ITM_DOLBY_AUDIO         :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_ICON_ITM_DOLBY_AUDIO       ;break  ;
#if (CUSTOMER == VIZIO)
        case  BANNER_ITM_HEADPHONES          :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_ICON_ITM_HEADPHONES        ;break  ;
#endif
        case  BANNER_ITM_AUDIO_OUT           :   u1_hd_id = WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_OUT          ;break  ;

   }

   UINT8 u1_total = sizeof(t_wdk_item_frm_root_array)/sizeof(t_wdk_item_frm_root_array[0]);
   UINT8 u1_idx;
   GL_RECT_T* tmp = NULL;

   for(u1_idx = 0;u1_idx < u1_total;++u1_idx)
   {
      tmp = t_wdk_item_frm_root_array[u1_idx].e_type == HT_WGL_WIDGET_TEXT ?  &((WDK_TXT_WGT_T*)t_wdk_item_frm_root_array[u1_idx].p_param)->t_rect :
            t_wdk_item_frm_root_array[u1_idx].e_type == HT_WGL_WIDGET_ICON ?  &((WDK_ICON_WGT_T*)t_wdk_item_frm_root_array[u1_idx].p_param)->t_rect :
           &((WDK_FRM_WGT_T*)t_wdk_item_frm_root_array[u1_idx].p_param)->t_rect ;

      if(t_wdk_item_frm_root_array[u1_idx].u2_id == u1_hd_id)
      {
          return tmp;
      }
   }

   return NULL;
}

UINT32 nav_banner2_view_rc_get_wgt_default_width(UINT8 u1_item_id)
{
    GL_RECT_T* tmp = nav_banner2_view_rc_get_wgt_rect(u1_item_id);

    if(tmp)
    {
       return (tmp->i4_right - tmp->i4_left);
    }
    else
        return 0;
}


GL_RECT_T* nav_banner2_view_rc_get_siderbar_frm_rect(void)
{
	GL_RECT_T* tmp = NULL;
	tmp = &(t_wdk_param_nav_banner2_view_rc_frm_sider_bar.t_rect);
    
    return tmp;
}


GL_RECT_T* nav_banner2_view_rc_get_siderbar_item_rect(UINT8 index)
{
    GL_RECT_T   *tmp_rect = NULL_HANDLE;
    WDK_ITEM_T  *wdk_item = NULL_HANDLE;

    UINT8 i = 0;
    for(i=0; i< (sizeof(t_wdk_item_frm_siderbar_array)/sizeof(t_wdk_item_frm_siderbar_array[0]));i++)
    {
         wdk_item = NULL_HANDLE;
         wdk_item = &(t_wdk_item_frm_siderbar_array[i]);
         if(wdk_item->u2_id == index && wdk_item->e_type == HT_WGL_WIDGET_ICON)
         {
            tmp_rect = NULL_HANDLE;
            tmp_rect = &((*(WDK_ICON_WGT_T *)(wdk_item->p_param)).t_rect);
            return tmp_rect;
         }
         else if(wdk_item->u2_id == index && wdk_item->e_type == HT_WGL_WIDGET_TEXT)
         {
            tmp_rect = NULL_HANDLE;
            tmp_rect = &((*(WDK_TXT_WGT_T *)(wdk_item->p_param)).t_rect);
            return tmp_rect;
         }
    }
    return (NULL_HANDLE);
}



