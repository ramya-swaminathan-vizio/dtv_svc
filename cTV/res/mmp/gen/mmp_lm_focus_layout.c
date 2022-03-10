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

#include "mmp_lm_focus_layout.h"

extern BOOL a_is_oled_compensation_support();

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_focus_frm_focus_frm =
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

static WDK_COLOR_INFO_T t_bk_clr_info_frm_focus_frm =
{
    WGL_COLOR_SET_EXTEND,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_focus_frm_focus_frm =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 715, 232},
    {&t_bk_clr_info_frm_focus_frm, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
    NULL
};

static WDK_COLOR_INFO_T t_bk_clr_info_lb_file =
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

static WDK_FONT_INFO_T t_font_info_lb_file =
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_font_small,
        &t_g_mmp_font_small
    }
};

static WDK_LB_IMG_SET_T t_bk_lbimg_lb_file =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static WDK_LB_COLOR_SET_T t_bk_lbclr_lb_file =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static WDK_LB_HLT_ELEM_EFFECT_T t_hlt_elem_effect_lb_file =
{
    0,
    {0, 0, 0, 0},
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        0,
        0,
        0,
        0,
        FALSE
    }
};

static WGL_LB_COL_INIT_T t_lbcolumn_init_lb_file_array[] =
{
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        107,
        80
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        267,
        200
    }
};

static WGL_INSET_T t_lbcol_inset_lb_file_array[] =
{
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

static WDK_LB_FONT_SET_T t_column_lbfont_lb_file_array[] =
{
    {
        &t_g_mmp_font_small,
        &t_g_mmp_font_small,
        &t_g_mmp_font_small,
        &t_g_mmp_font_small
    },
    {
        &t_g_mmp_font_small,
        &t_g_mmp_font_small,
        &t_g_mmp_font_small,
        &t_g_mmp_font_small
    }
};

static WDK_LB_COLOR_SET_T t_col_text_lbclr_lb_file_array[] =
{
    {
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray
    },
    {
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white
    }
};

static WDK_LB_COLOR_SET_T t_col_bk_lbclr_lb_file_array[] =
{
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_LB_ITEM_INFO_T t_lbitem_lb_file_array[] =
{
    {
        LB_COL_TYPE_TEXT,
        0,
        WGL_AS_LEFT_CENTER,
        TRUE,
        0
    },
    {
        LB_COL_TYPE_TEXT,
        0,
        WGL_AS_LEFT_CENTER,
        FALSE,
        0
    },
    {
        LB_COL_TYPE_TEXT,
        0,
        WGL_AS_LEFT_CENTER,
        TRUE,
        0
    },
    {
        LB_COL_TYPE_TEXT,
        0,
        WGL_AS_LEFT_CENTER,
        TRUE,
        0
    },
    {
        LB_COL_TYPE_TEXT,
        0,
        WGL_AS_CENTER_CENTER,
        TRUE,
        0
    },
    {
        LB_COL_TYPE_TEXT,
        0,
        WGL_AS_CENTER_CENTER,
        TRUE,
        0
    }
};

static WDK_LB_FONT_SET_T t_item_lbfont_lb_file_array[] =
{
    {
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        &t_g_mmp_font_small,
        &t_g_mmp_font_small,
        &t_g_mmp_font_small,
        &t_g_mmp_font_small
    },
    {
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_LB_IMG_SET_T t_item_set_lbimg_lb_file_array[] =
{
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_LB_COLOR_SET_T t_item_text_lbclr_lb_file_array[] =
{
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_LB_COLOR_SET_T t_item_bk_lbclr_lb_file_array[] =
{
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_LB_WGT_T t_wdk_param_mmp_lm_focus_lb_file =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_LB_FIXED_ELEM_NUM,
    255,
    TRUE,
    WGL_SW_RECURSIVE,
    NULL,
    {3, 4, 609, 130},
    {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
    {3, 3, 3, 3},
    &t_font_info_lb_file,
    3,
    3,
    42,
    0,
    {3, 3, 0, 0},
    {&t_bk_lbclr_lb_file, &t_bk_lbimg_lb_file},
    &t_hlt_elem_effect_lb_file,
    1,
    2,
    t_lbcolumn_init_lb_file_array,
    t_lbcol_inset_lb_file_array,
    t_column_lbfont_lb_file_array,
    t_col_text_lbclr_lb_file_array,
    t_col_bk_lbclr_lb_file_array,
    t_lbitem_lb_file_array,
    t_item_lbfont_lb_file_array,
    t_item_set_lbimg_lb_file_array,
    t_item_text_lbclr_lb_file_array,
    t_item_bk_lbclr_lb_file_array,
    NULL
};

static WDK_FONT_INFO_T t_font_info_txt_press_ok_for_fullscreen =
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_thumbnail_font,
        &t_g_mmp_thumbnail_font
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_press_ok_for_fullscreen =
{
    WGL_COLOR_SET_EXTEND,
    {
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_hdr10plus =
{
    WGL_COLOR_SET_EXTEND,
    {
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white
    }
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_focus_txt_press_ok_for_fullscreen =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_128,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {10, 134, 715, 177},
    {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_press_ok_for_fullscreen,
    &t_text_clr_info_txt_press_ok_for_fullscreen,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_focus_txt_elapse =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {10, 184, 108, 232},
    {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_lb_file,
    &t_text_clr_info_txt_press_ok_for_fullscreen,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_focus_txt_remain =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {483, 184, 591, 232},
    {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_lb_file,
    &t_text_clr_info_txt_press_ok_for_fullscreen,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FONT_INFO_T t_font_info_pb_pos =
{
    WGL_FONT_SET_BASIC,
    {
        NULL,
        NULL
    }
};

static WDK_IMG_INFO_T t_pb_body_bk_img_info_mmp_lm_focus_pb_pos =
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

static WDK_IMG_INFO_T t_pb_level_1_img_info_mmp_lm_focus_pb_pos =
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

static WDK_PB_WGT_T t_wdk_param_mmp_lm_focus_pb_pos =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {108, 193, 469, 222},
    {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
    WGL_PG_DM_PERCENT,
    0,
    100,
    0,
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
    &t_bk_clr_info_lb_file,
    {&t_bk_clr_info_lb_file, &t_pb_body_bk_img_info_mmp_lm_focus_pb_pos},
    {
        {&t_bk_clr_info_lb_file, &t_pb_level_1_img_info_mmp_lm_focus_pb_pos},
        {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
        {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
        {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
        {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm}
    },
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_lm_focus_icon_dolby_hdr_hlg_vision =
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

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_focus_icon_dolby_hdr_hlg_vision =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {348, 64, 476, 116},
    {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_fg_img_info_mmp_lm_focus_icon_dolby_hdr_hlg_vision,
    0,
    0,
    0,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_lm_focus_icon_dolby_audio =
{
    WGL_IMG_SET_BASIC,
    {
        //&h_g_mmp_dolbyAudio_Vert_white,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_focus_icon_dolby_audio =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {490, 66, 606, 109},
    {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_fg_img_info_mmp_lm_focus_icon_dolby_audio,
    0,
    0,
    0,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_lm_focus_icon_dolby_atmos =
{
    WGL_IMG_SET_BASIC,
    {
        //&h_g_mmp_dolbyAtmos_Vert_white,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_focus_icon_dolby_atmos =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {431, 67, 547, 110},
    {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_lm_focus_icon_dolby_atmos,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_focus_txt_hdr10plus =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_128,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {370, 66, 500, 130},
    {&t_bk_clr_info_lb_file, &t_bk_img_info_mmp_lm_focus_frm_focus_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_lb_file,
    &t_text_clr_info_txt_hdr10plus,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ITEM_T t_wdk_item_frm_focus_frm_array[] =
{
    {
        HT_WGL_WIDGET_LIST_BOX,
        WID_MMP_LM_FOCUS_LB_FILE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_focus_lb_file,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_FOCUS_TXT_PRESS_OK_FOR_FULLSCREEN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_focus_txt_press_ok_for_fullscreen,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_FOCUS_TXT_ELAPSE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_focus_txt_elapse,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_FOCUS_TXT_REMAIN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_focus_txt_remain,
        NULL
    },
    {
        HT_WGL_WIDGET_PROGRESS_BAR,
        WID_MMP_LM_FOCUS_PB_POS,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_focus_pb_pos,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_FOCUS_ICON_DOLBY_HDR_HLG_VISION,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_focus_icon_dolby_hdr_hlg_vision,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_FOCUS_ICON_DOLBY_AUDIO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_focus_icon_dolby_audio,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_FOCUS_ICON_DOLBY_ATMOS,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_focus_icon_dolby_atmos,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_FOCUS_TXT_HRD10PLUS,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_focus_txt_hdr10plus,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_focus_frm =
{
    sizeof(t_wdk_item_frm_focus_frm_array)/sizeof(t_wdk_item_frm_focus_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_focus_frm_array
};

static WDK_ITEM_T t_wdk_item_view_lm_focus_array[] =
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_FOCUS_FRM_FOCUS_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_focus_frm_focus_frm,
        (VOID *) &t_wdk_list_frm_focus_frm
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_lm_focus =
{
    sizeof(t_wdk_item_view_lm_focus_array)/sizeof(t_wdk_item_view_lm_focus_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_lm_focus_array
};

//add
GL_COLOR_T t_g_mmp_color_text_1 = {0xff, {0xff}, {0xff}, {0xff}};
GL_COLOR_T t_g_mmp_color_text_1_oled = {0xff, {0xbf}, {0xbf}, {0xbf}};
GL_COLOR_T t_g_mmp_gray_1 = {0xff, {0x2c}, {0x2c}, {0x2c}};

#define MMP_SIDERBAR_W (200)
#define MMP_SIDERBAR_H (75)
#define MMP_SCREEN_W (1920)
//#define BANNER2_SCREEN_H (1080)

#define MMP_SIDERBAR_X (MMP_SCREEN_W - MMP_SIDERBAR_W - 40)
#define MMP_SIDERBAR_Y (40)

#define MMP_SB_DV_W (178)
#define MMP_SB_DV_H (100)
#define MMP_SB_DV_X ((200-130)/2)
#define MMP_SB_DV_Y ((75 -69)/2)
#define MMP_SB_DV_S (155) // 75 + 50 + 30

static WGL_FONT_INFO_T t_g_mmp_time_font_custom_size =
{
   FE_FNT_SIZE_CUSTOM,
   FE_FNT_STYLE_REGULAR,
   FE_CMAP_ENC_UNICODE,
   NULL,
   0,
   42
};
static WDK_COLOR_INFO_T t_mmp_bk_clr_info_sidebar_dv =
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

static WDK_FONT_INFO_T t_g_mmp_time_font_custom_time_size =
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_time_font_custom_size,
        &t_g_mmp_time_font_custom_size
    }
};
static WDK_COLOR_INFO_T t_mmp_item_prog_info_text_color_black_info =
{
    WGL_COLOR_SET_STANDARD,
    {
        &t_g_mmp_color_text_1,
        &t_g_mmp_color_text_1,
        &t_g_mmp_color_text_1,
        NULL,
        NULL,
        NULL
    }
};
static WDK_IMG_INFO_T t_fg_img_info_mmp_view_rc_icon_itm_dolby_icon =
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

static WDK_COLOR_INFO_T t_mmp_bk_clr_info_frm_root =
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
static WDK_IMG_INFO_T t_mmp_bk_img_info_nav_banner2_view_rc_frm_root =
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

static WDK_FRM_WGT_T t_wdk_param_mmp_view_rc_frm_sider_bar =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {MMP_SIDERBAR_X,  MMP_SIDERBAR_Y, MMP_SIDERBAR_X + MMP_SIDERBAR_W,  MMP_SIDERBAR_Y + MMP_SIDERBAR_H + 95+75+80},
    {&t_mmp_bk_clr_info_sidebar_dv, &t_mmp_bk_img_info_nav_banner2_view_rc_frm_root},
    NULL
};

static WDK_TXT_WGT_T t_fg_img_info_mmp_fullscreen_view_rc_itm_hdr10plus_txt =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    180,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0,0 ,MMP_SIDERBAR_W, MMP_SIDERBAR_H},
    {&t_mmp_bk_clr_info_frm_root, &t_mmp_bk_img_info_nav_banner2_view_rc_frm_root},
    0,
    WGL_AS_CENTER_CENTER,
    &t_g_mmp_time_font_custom_time_size,
    &t_mmp_item_prog_info_text_color_black_info,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_fullscreen_view_rc_itm_dhv_icon =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {MMP_SB_DV_X,  MMP_SIDERBAR_Y,  MMP_SB_DV_X+MMP_SB_DV_W,  MMP_SIDERBAR_Y+MMP_SB_DV_H},
    {&t_mmp_bk_clr_info_sidebar_dv, &t_mmp_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_view_rc_icon_itm_dolby_icon,
    0,
    0,
    0,
    NULL
};
static WDK_ICON_WGT_T t_wdk_param_mmp_fullscreen_view_rc_itm_da_icon =
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {MMP_SB_DV_X,  MMP_SIDERBAR_Y+MMP_SB_DV_S,  MMP_SB_DV_X+MMP_SB_DV_W,  MMP_SIDERBAR_Y+MMP_SB_DV_S+MMP_SB_DV_H},
    {&t_mmp_bk_clr_info_sidebar_dv, &t_mmp_bk_img_info_nav_banner2_view_rc_frm_root},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_view_rc_icon_itm_dolby_icon,
    0,
    0,
    0,
    NULL
};


static WDK_ITEM_T t_wdk_item_mmp_show_dolbyhdrhlg_array[] =
{
        {
            HT_WGL_WIDGET_TEXT,
            WID_MMP_SIDERBAR_VIEW_RC_TXT_ITM_SIDER_HDR10PLUS,
            WDK_FRM_OPT_BK_IMG,
            (VOID *) &t_fg_img_info_mmp_fullscreen_view_rc_itm_hdr10plus_txt,
            NULL
        },

        {
           HT_WGL_WIDGET_ICON,
           WID_MMP_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_HDR_HLG_VISION,
           WDK_FRM_OPT_BK_IMG,
           (VOID *) &t_wdk_param_mmp_fullscreen_view_rc_itm_dhv_icon,
           NULL
        },
        {
           HT_WGL_WIDGET_ICON,
           WID_MMP_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_AUDIO,
           WDK_FRM_OPT_BK_IMG,
           (VOID *) &t_wdk_param_mmp_fullscreen_view_rc_itm_da_icon,
           NULL
        },

};
static WDK_ITEM_LIST_T t_wdk_item_mmp_show_dolbyhdrhlg =
{
    sizeof(t_wdk_item_mmp_show_dolbyhdrhlg_array)/sizeof(t_wdk_item_mmp_show_dolbyhdrhlg_array[0]),
    (WDK_ITEM_T *) t_wdk_item_mmp_show_dolbyhdrhlg_array
};

static WDK_ITEM_T t_wdk_item_mmp_view_view_siderbar_array[] =
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_SIDERBAR_VIEW_RC_FRM_SIDER_BAR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_view_rc_frm_sider_bar,
        (VOID *) &t_wdk_item_mmp_show_dolbyhdrhlg
    }
};

static WDK_ITEM_LIST_T t_wdk_list_mmp_view_siderbar_rc =
{
    sizeof(t_wdk_item_mmp_view_view_siderbar_array)/sizeof(t_wdk_item_mmp_view_view_siderbar_array[0]),
    (WDK_ITEM_T *) t_wdk_item_mmp_view_view_siderbar_array
};

//add
static HANDLE_T ah_wgt_handle_mmp_siderbar_view_rc[WID_MMP_SIDERBAR_VIEW_RC_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_mmp_siderbar_view_rc[WID_MMP_SIDERBAR_VIEW_RC_TOTAL_COUNT];

static HANDLE_T ah_wgt_handle_mmp_lm_focus[WID_MMP_LM_FOCUS_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_mmp_lm_focus[WID_MMP_LM_FOCUS_TOTAL_COUNT];


INT32 mmp_lm_focus_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_mmp_lm_focus, 0,
             WID_MMP_LM_FOCUS_TOTAL_COUNT*sizeof(af_wgt_cb_mmp_lm_focus[0]));
    return (WDKR_OK);
}

INT32 mmp_lm_focus_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_MMP_LM_FOCUS_TOTAL_COUNT)
    {
        af_wgt_cb_mmp_lm_focus[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }

    return (WDKR_FAILED);
}


INT32 mmp_lm_focus_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container,
                                 &t_wdk_list_view_lm_focus,
                                 ah_wgt_handle_mmp_lm_focus,
                                 af_wgt_cb_mmp_lm_focus));
}

HANDLE_T mmp_lm_focus_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_MMP_LM_FOCUS_TOTAL_COUNT)
    {
        return ah_wgt_handle_mmp_lm_focus[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_lm_focus_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_lm_focus,
                                      ah_wgt_handle_mmp_lm_focus,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_lm_focus_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_lm_focus,
                                         ah_wgt_handle_mmp_lm_focus))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 mmp_lm_focus_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_MMP_LM_FOCUS_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container,
                                 &t_wdk_list_view_lm_focus,
                                 *pt_mi,
                                 af_wgt_cb_mmp_lm_focus));
}

HANDLE_T mmp_lm_focus_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_mmp_lm_focus = NULL;

    h_wgt_handle_mmp_lm_focus = (VOID *)t_mi;

    if (NULL == h_wgt_handle_mmp_lm_focus)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_MMP_LM_FOCUS_TOTAL_COUNT)
    {
        return h_wgt_handle_mmp_lm_focus[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_lm_focus_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_lm_focus,
                                      (HANDLE_T *)t_mi,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_lm_focus_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_lm_focus, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}

//add
INT32 mmp_view_rc_create_siderbar_ui(HANDLE_T h_container)
{
	if (a_is_oled_compensation_support())
	{
		t_g_mmp_color_text_1 = t_g_mmp_color_text_1_oled;
	}
    return (a_wdk_create_widgets(h_container,
                                 &t_wdk_list_mmp_view_siderbar_rc,
                                 ah_wgt_handle_mmp_siderbar_view_rc,
                                 af_wgt_cb_mmp_siderbar_view_rc));
}

HANDLE_T mmp_view_rc_get_siderbar_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_MMP_SIDERBAR_VIEW_RC_TOTAL_COUNT)
    {
        return ah_wgt_handle_mmp_siderbar_view_rc[e_widget_id];
    }

    return (NULL_HANDLE);
}

GL_RECT_T* mmp_view_rc_get_siderbar_frm_rect(void)
{

    GL_RECT_T* tmp = NULL;
    tmp = &(t_wdk_param_mmp_view_rc_frm_sider_bar.t_rect);

    return tmp;
}

INT32 mmp_view_rc_destroy_siderbar_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_item_mmp_show_dolbyhdrhlg,
                                         ah_wgt_handle_mmp_siderbar_view_rc))
    {
        return (WDKR_FAILED);
    }
    return (WDKR_OK);
}


