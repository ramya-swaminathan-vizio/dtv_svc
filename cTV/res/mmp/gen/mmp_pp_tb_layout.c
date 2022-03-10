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

#include "mmp_pp_tb_layout.h"

static WDK_IMG_INFO_T t_bk_img_info_mmp_pp_tb_frm_main_frm = 
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

static WDK_COLOR_INFO_T t_bk_clr_info_frm_main_frm = 
{
    WGL_COLOR_SET_STANDARD,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_mmp_pp_tb_frm_main_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    0,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {1, 0, 961, 720},
    {&t_bk_clr_info_frm_main_frm, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    NULL
};

static WDK_COLOR_INFO_T t_bk_clr_info_frm_top_bar = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_pp_tb_frm_top_bar = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    0,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {106, 80, 306, 130},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_play_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 40, 46},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_repeat_ab_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {70, 0, 170, 46},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_pp_tb_frm_player_bar = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {102, 406, 857, 484},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    NULL
};

static WDK_FONT_INFO_T t_font_info_txt_player_hint = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_font_small,
        &t_g_mmp_font_small
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_player_hint = 
{
    WGL_COLOR_SET_BASIC,
    {
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white
    }
};

static WDK_TXT_WGT_T t_wdk_param_mmp_pp_tb_txt_player_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {30, 10, 80, 35},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    MLM_MMP_KEY_MEDIA_TYPE_OPTION_PHOTO,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_player_hint,
    &t_text_clr_info_txt_player_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_line_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {90, 10, 111, 36},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_dura_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {455, 10, 491, 33},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_pp_tb_txt_dura_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {491, 10, 570, 35},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    MLM_MMP_KEY_EMPTY,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_player_hint,
    &t_text_clr_info_txt_player_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_effect_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {109, 40, 146, 65},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_pp_tb_txt_effect_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {146, 40, 256, 65},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    MLM_MMP_KEY_EMPTY,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_player_hint,
    &t_text_clr_info_txt_player_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_shuffle_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {368, 10, 425, 35},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_fileidx_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {591, 10, 624, 33},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_pp_tb_txt_fileidx_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {626, 10, 727, 35},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    0,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_player_hint,
    &t_text_clr_info_txt_player_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_filename_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {300, 41, 336, 66},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_pp_tb_txt_filename_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {336, 41, 720, 66},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    0,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_player_hint,
    &t_text_clr_info_txt_player_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_repeat_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {215, 10, 258, 36},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_pp_tb_txt_repeat_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {258, 10, 338, 35},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    MLM_MMP_KEY_EMPTY,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_player_hint,
    &t_text_clr_info_txt_player_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_zoom_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {109, 13, 145, 36},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_pp_tb_txt_zoom_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {145, 10, 185, 35},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    MLM_MMP_KEY_EMPTY,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_player_hint,
    &t_text_clr_info_txt_player_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_pp_tb_frm_info_bar = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {102, 484, 857, 520},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_menu_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {110, 6, 160, 31},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_pp_tb_txt_menu_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {152, 3, 212, 28},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    MLM_MMP_KEY_LM_MENU,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_player_hint,
    &t_text_clr_info_txt_player_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_select_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {355, 6, 405, 31},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_pp_tb_txt_select_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {397, 3, 457, 28},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    MLM_MMP_KEY_EMPTY,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_player_hint,
    &t_text_clr_info_txt_player_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_pp_tb_icon_enter_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {576, 6, 626, 31},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_pp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_pp_tb_txt_enter_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {619, 3, 679, 28},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_pp_tb_frm_main_frm},
    MLM_MMP_KEY_LM_ENTER,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_player_hint,
    &t_text_clr_info_txt_player_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ITEM_T t_wdk_item_frm_top_bar_array[] = 
{
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_PLAY_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_play_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_REPEAT_AB_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_repeat_ab_icon,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_top_bar = 
{
    sizeof(t_wdk_item_frm_top_bar_array)/sizeof(t_wdk_item_frm_top_bar_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_top_bar_array
};

static WDK_ITEM_T t_wdk_item_frm_player_bar_array[] = 
{
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_PP_TB_TXT_PLAYER_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_txt_player_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_LINE_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_line_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_DURA_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_dura_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_PP_TB_TXT_DURA_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_txt_dura_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_EFFECT_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_effect_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_PP_TB_TXT_EFFECT_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_txt_effect_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_SHUFFLE_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_shuffle_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_FILEIDX_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_fileidx_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_PP_TB_TXT_FILEIDX_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_txt_fileidx_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_FILENAME_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_filename_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_PP_TB_TXT_FILENAME_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_txt_filename_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_REPEAT_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_repeat_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_PP_TB_TXT_REPEAT_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_txt_repeat_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_ZOOM_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_zoom_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_PP_TB_TXT_ZOOM_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_txt_zoom_hint,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_player_bar = 
{
    sizeof(t_wdk_item_frm_player_bar_array)/sizeof(t_wdk_item_frm_player_bar_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_player_bar_array
};

static WDK_ITEM_T t_wdk_item_frm_info_bar_array[] = 
{
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_MENU_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_menu_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_PP_TB_TXT_MENU_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_txt_menu_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_SELECT_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_select_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_PP_TB_TXT_SELECT_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_txt_select_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_PP_TB_ICON_ENTER_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_icon_enter_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_PP_TB_TXT_ENTER_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_txt_enter_hint,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_info_bar = 
{
    sizeof(t_wdk_item_frm_info_bar_array)/sizeof(t_wdk_item_frm_info_bar_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_info_bar_array
};

static WDK_ITEM_T t_wdk_item_frm_main_frm_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_PP_TB_FRM_TOP_BAR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_frm_top_bar,
        (VOID *) &t_wdk_list_frm_top_bar
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_PP_TB_FRM_PLAYER_BAR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_frm_player_bar,
        (VOID *) &t_wdk_list_frm_player_bar
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_PP_TB_FRM_INFO_BAR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_frm_info_bar,
        (VOID *) &t_wdk_list_frm_info_bar
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_main_frm = 
{
    sizeof(t_wdk_item_frm_main_frm_array)/sizeof(t_wdk_item_frm_main_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_main_frm_array
};

static WDK_ITEM_T t_wdk_item_view_pp_tb_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_PP_TB_FRM_MAIN_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_pp_tb_frm_main_frm,
        (VOID *) &t_wdk_list_frm_main_frm
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_pp_tb = 
{
    sizeof(t_wdk_item_view_pp_tb_array)/sizeof(t_wdk_item_view_pp_tb_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_pp_tb_array
};

static HANDLE_T ah_wgt_handle_mmp_pp_tb[WID_MMP_PP_TB_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_mmp_pp_tb[WID_MMP_PP_TB_TOTAL_COUNT];


INT32 mmp_pp_tb_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_mmp_pp_tb, 0, 
             WID_MMP_PP_TB_TOTAL_COUNT*sizeof(af_wgt_cb_mmp_pp_tb[0]));
    return (WDKR_OK);
}

INT32 mmp_pp_tb_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_MMP_PP_TB_TOTAL_COUNT)
    {
        af_wgt_cb_mmp_pp_tb[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }

    return (WDKR_FAILED);
}


INT32 mmp_pp_tb_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_pp_tb, 
                                 ah_wgt_handle_mmp_pp_tb,
                                 af_wgt_cb_mmp_pp_tb));
}

HANDLE_T mmp_pp_tb_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_MMP_PP_TB_TOTAL_COUNT)
    {
        return ah_wgt_handle_mmp_pp_tb[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_pp_tb_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_pp_tb, 
                                      ah_wgt_handle_mmp_pp_tb,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_pp_tb_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_pp_tb, 
                                         ah_wgt_handle_mmp_pp_tb))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 mmp_pp_tb_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_MMP_PP_TB_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_pp_tb, 
                                 *pt_mi,
                                 af_wgt_cb_mmp_pp_tb));
}

HANDLE_T mmp_pp_tb_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_mmp_pp_tb = NULL;

    h_wgt_handle_mmp_pp_tb = (VOID *)t_mi;

    if (NULL == h_wgt_handle_mmp_pp_tb)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_MMP_PP_TB_TOTAL_COUNT)
    {
        return h_wgt_handle_mmp_pp_tb[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_pp_tb_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_pp_tb, 
                                      (HANDLE_T *)t_mi,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_pp_tb_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_pp_tb, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}



