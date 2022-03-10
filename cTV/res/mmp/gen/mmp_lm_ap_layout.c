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

#include "res/mmp/gen/mmp_gen_img.h"
#include "res/mmp/gen/mmp_gen_clr.h"
#include "res/mmp/gen/mmp_mlm.h"
#include "res/mmp/gen/mmp_gen_font_info.h"

#include "mmp_lm_ap_layout.h"

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_ap_frm_ap_frm = 
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

static WDK_COLOR_INFO_T t_bk_clr_info_frm_ap_frm = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_ap_frm_ap_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 1342, 260},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    NULL
};

static WDK_FONT_INFO_T t_font_info_txt_name = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_font_small,
        &t_g_mmp_font_small
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_name = 
{
    WGL_COLOR_SET_BASIC,
    {
        &t_g_mmp_white,
        &t_g_mmp_white,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FONT_INFO_T t_font_info_pb_pos = 
{
    WGL_FONT_SET_BASIC,
    {
        NULL,
        NULL
    }
};

static WDK_IMG_INFO_T t_pb_body_bk_img_info_mmp_lm_ap_pb_pos = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_track_time_bar_outline,
        &h_g_mmp_track_time_bar_outline,
        &h_g_mmp_track_time_bar_outline,
        NULL,
        NULL,
        NULL
    }
};

static WDK_IMG_INFO_T t_pb_level_1_img_info_mmp_lm_ap_pb_pos = 
{
    WGL_IMG_SET_STANDARD,
    {
        &h_g_mmp_track_time_bar_fill,
        &h_g_mmp_track_time_bar_fill,
        &h_g_mmp_track_time_bar_fill,
        NULL,
        NULL,
        NULL
    }
};

static WDK_PB_WGT_T t_wdk_param_mmp_lm_ap_pb_pos = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {468, 190, 830, 219},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    WGL_PG_DM_PERCENT,
    0,
    100,
    20,
    {
        1,
        {100,100,100,100}
    },
    {
        {0, 0, 0, 0},
        WGL_AS_CENTER_CENTER
    },
    {
        {0, 0, 0, 0},
        WGL_AS_CENTER_CENTER
    },
    {
        {0, 0, 0, 0},
        WGL_AS_CENTER_CENTER
    },
    27,
    27,
    {
        0,
        0,
        0,
        0
    },
    {
        4,
        4,
        6,
        2
    },
    &t_font_info_pb_pos,
    &t_bk_clr_info_frm_ap_frm,
    {&t_bk_clr_info_frm_ap_frm, &t_pb_body_bk_img_info_mmp_lm_ap_pb_pos},
    {
        {&t_bk_clr_info_frm_ap_frm, &t_pb_level_1_img_info_mmp_lm_ap_pb_pos},
        {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
        {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
        {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
        {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm}
    },
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_cur = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {355, 190, 467, 217},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_RIGHT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_tol = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {830, 190, 942, 217},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

#define LABLE_LEFT (20)
#define LABLE_WIDE (120)
#define LABLE_RIGHT (LABLE_LEFT + LABLE_WIDE)
#define TEXT_WIDE (800)
#define TEXT_RIGHT (LABLE_RIGHT + TEXT_WIDE)

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_name = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_SMART_CUT_OVER_MAX|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_RIGHT, 0, TEXT_RIGHT, 24},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_title = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_SMART_CUT_OVER_MAX|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_RIGHT, 24, TEXT_RIGHT, 48},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_artist = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_SMART_CUT_OVER_MAX|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_RIGHT, 48, TEXT_RIGHT, 72},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_album = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_SMART_CUT_OVER_MAX|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_RIGHT, 72, TEXT_RIGHT, 96},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_duration = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_RIGHT, 96, TEXT_RIGHT, 120},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_director = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_RIGHT, 120, TEXT_RIGHT, 144},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_gerner = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_RIGHT, 144, TEXT_RIGHT, 168},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_year = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_RIGHT, 168, TEXT_RIGHT, 192},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_producer = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_RIGHT, 192, TEXT_RIGHT, 216},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_protect = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_RIGHT, 216, TEXT_RIGHT, 240},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_size = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_RIGHT, 240, TEXT_RIGHT, 268},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};


static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_name_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_LEFT, 0, LABLE_RIGHT, 24},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_title_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_LEFT, 24, LABLE_RIGHT, 48},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_artist_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_LEFT, 48, LABLE_RIGHT, 72},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_album_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_LEFT, 72, LABLE_RIGHT, 96},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_duration_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_LEFT, 96, LABLE_RIGHT, 120},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_director_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_LEFT, 120, LABLE_RIGHT, 144},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_gerner_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_LEFT, 144, LABLE_RIGHT, 168},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_year_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_LEFT, 168, LABLE_RIGHT, 192},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_producer_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_LEFT, 192, LABLE_RIGHT, 216},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_protect_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_LEFT, 216, LABLE_RIGHT, 240},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};
static WDK_TXT_WGT_T t_wdk_param_mmp_lm_ap_txt_size_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {LABLE_LEFT, 240, LABLE_RIGHT, 268},
    {&t_bk_clr_info_frm_ap_frm, &t_bk_img_info_mmp_lm_ap_frm_ap_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_name,
    &t_text_clr_info_txt_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ITEM_T t_wdk_item_frm_ap_frm_array[] = 
{
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_NAME,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_name,
        NULL
    },
    {
        HT_WGL_WIDGET_PROGRESS_BAR,
        WID_MMP_LM_AP_PB_POS,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_pb_pos,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_CUR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_cur,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_TOL,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_tol,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_ALBUM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_album,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_ARTIST,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_artist,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_ALBUM_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_album_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_ARTIST_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_artist_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_NAME_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_name_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_TITLE_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_title_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_DURATION_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_duration_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_DIRECTOR_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_director_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_GERNER_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_gerner_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_YEAR_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_year_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_PRODUCER_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_producer_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_PROTECT_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_protect_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_SIZE_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_size_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_TITLE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_title,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_DURATION,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_duration,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_DIRECTOR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_director,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_GERNER,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_gerner,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_YEAR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_year,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_PRODUCER,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_producer,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_PROTECT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_protect,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_AP_TXT_SIZE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_txt_size,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_ap_frm = 
{
    sizeof(t_wdk_item_frm_ap_frm_array)/sizeof(t_wdk_item_frm_ap_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_ap_frm_array
};

static WDK_ITEM_T t_wdk_item_view_lm_ap_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_AP_FRM_AP_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_ap_frm_ap_frm,
        (VOID *) &t_wdk_list_frm_ap_frm
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_lm_ap = 
{
    sizeof(t_wdk_item_view_lm_ap_array)/sizeof(t_wdk_item_view_lm_ap_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_lm_ap_array
};

static HANDLE_T ah_wgt_handle_mmp_lm_ap[WID_MMP_LM_AP_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_mmp_lm_ap[WID_MMP_LM_AP_TOTAL_COUNT];


INT32 mmp_lm_ap_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_mmp_lm_ap, 0, 
             WID_MMP_LM_AP_TOTAL_COUNT*sizeof(af_wgt_cb_mmp_lm_ap[0]));
    return (WDKR_OK);
}

INT32 mmp_lm_ap_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_MMP_LM_AP_TOTAL_COUNT)
    {
        af_wgt_cb_mmp_lm_ap[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }

    return (WDKR_FAILED);
}


INT32 mmp_lm_ap_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_lm_ap, 
                                 ah_wgt_handle_mmp_lm_ap,
                                 af_wgt_cb_mmp_lm_ap));
}

HANDLE_T mmp_lm_ap_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_MMP_LM_AP_TOTAL_COUNT)
    {
        return ah_wgt_handle_mmp_lm_ap[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_lm_ap_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_lm_ap, 
                                      ah_wgt_handle_mmp_lm_ap,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_lm_ap_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_lm_ap, 
                                         ah_wgt_handle_mmp_lm_ap))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 mmp_lm_ap_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_MMP_LM_AP_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_lm_ap, 
                                 *pt_mi,
                                 af_wgt_cb_mmp_lm_ap));
}

HANDLE_T mmp_lm_ap_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_mmp_lm_ap = NULL;

    h_wgt_handle_mmp_lm_ap = (VOID *)t_mi;

    if (NULL == h_wgt_handle_mmp_lm_ap)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_MMP_LM_AP_TOTAL_COUNT)
    {
        return h_wgt_handle_mmp_lm_ap[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_lm_ap_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_lm_ap, 
                                      (HANDLE_T *)t_mi,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_lm_ap_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_lm_ap, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}



