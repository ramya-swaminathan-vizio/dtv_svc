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

#include "mmp_lm_custom_layout.h"

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_custom_frm_lm_main_frm = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_music_bg_template,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_bk_clr_info_frm_lm_main_frm = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_custom_frm_lm_main_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 1920, 1080},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_frm_lm_main_frm},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_custom_icon_logo = 
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

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_custom_icon_logo = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {43, 22, 199, 58},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_icon_logo},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_lm_custom_icon_logo,
    0,
    0,
    0,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_custom_frm_side_panel = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 67, 570, 1073},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_icon_logo},
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_lm_custom_icon_folder_icon = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_lg_folder_icon,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_custom_icon_folder_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {167, 180, 381, 361},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_icon_logo},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_lm_custom_icon_folder_icon,
    0,
    0,
    0,
    NULL
};

static WDK_FONT_INFO_T t_font_info_txt_folder_name = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_font_small,
        &t_g_mmp_font_small
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_folder_name = 
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

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_custom_txt_folder_name = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_BK|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_SMART_CUT_OVER_MAX|WGL_STL_TEXT_MAX_128,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {110, 364, 470, 412},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_icon_logo},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_folder_name,
    &t_text_clr_info_txt_folder_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_custom_frm_control = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {20, 570, 551, 954},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_icon_logo},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_custom_btn_back_to_menu = 
{
    WGL_IMG_SET_EXTEND,
    {
        &h_g_mmp_back_bar_nr,
        &h_g_mmp_back_bar_nr,
        &h_g_mmp_back_bar_hlt,
        &h_g_mmp_back_bar_hlt,
        &h_g_mmp_back_bar_hlt,
        &h_g_mmp_back_bar_nr
    }
};

static WDK_FONT_INFO_T t_font_info_btn_back_to_menu = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_font_medium,
        &t_g_mmp_font_medium
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_btn_back_to_menu = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_lm_custom_btn_back_to_menu = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 8, 567, 59},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_btn_back_to_menu},
    0,
    WGL_AS_LEFT_CENTER,
    &t_bk_img_info_mmp_lm_custom_icon_logo,
    {77, 0, 0, 0},
    &t_font_info_btn_back_to_menu,
    &t_text_clr_info_btn_back_to_menu,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_custom_lb_dev_name = 
{
    WGL_IMG_SET_EXTEND,
    {
        NULL,
        &h_g_mmp_lst_hlt,
        &h_g_mmp_lst_hlt,
        &h_g_mmp_lst_hlt,
        NULL,
        NULL
    }
};

static WDK_FONT_INFO_T t_font_info_lb_dev_name = 
{
    WGL_FONT_SET_BASIC,
    {
        NULL,
        NULL
    }
};

static WDK_LB_IMG_SET_T t_bk_lbimg_lb_dev_name = 
{
    NULL,
    NULL,
    &h_g_mmp_lst_hlt,
    &h_g_mmp_lst_hlt,
    &h_g_mmp_lst_hlt,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static WDK_LB_COLOR_SET_T t_bk_lbclr_lb_dev_name = 
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static WDK_LB_HLT_ELEM_EFFECT_T t_hlt_elem_effect_lb_dev_name = 
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

static WGL_LB_COL_INIT_T t_lbcolumn_init_lb_dev_name_array[] = 
{
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        120,
        80
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        240,
        171
    }
};

static WGL_INSET_T t_lbcol_inset_lb_dev_name_array[] = 
{
    {7, 0, 0, 0},
    {0, 0, 0, 0}
};

static WDK_LB_FONT_SET_T t_column_lbfont_lb_dev_name_array[] = 
{
    {
        &t_g_mmp_font_medium,
        &t_g_mmp_font_medium,
        &t_g_mmp_font_medium,
        &t_g_mmp_font_medium
    },
    {
        &t_g_mmp_font_medium,
        &t_g_mmp_font_medium,
        &t_g_mmp_font_medium,
        &t_g_mmp_font_medium
    }
};

static WDK_LB_COLOR_SET_T t_col_text_lbclr_lb_dev_name_array[] = 
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

static WDK_LB_COLOR_SET_T t_col_bk_lbclr_lb_dev_name_array[] = 
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

static WDK_LB_ITEM_INFO_T t_lbitem_lb_dev_name_array[] = 
{
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

static WDK_LB_FONT_SET_T t_item_lbfont_lb_dev_name_array[] = 
{
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

static WDK_LB_IMG_SET_T t_item_set_lbimg_lb_dev_name_array[] = 
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
    }
};

static WDK_LB_COLOR_SET_T t_item_text_lbclr_lb_dev_name_array[] = 
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

static WDK_LB_COLOR_SET_T t_item_bk_lbclr_lb_dev_name_array[] = 
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

static WDK_LB_WGT_T t_wdk_param_mmp_lm_custom_lb_dev_name = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_LB_FIXED_ELEM_NUM,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {4, 100, 566, 166},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_lb_dev_name},
    {0, 0, 0, 0},
    &t_font_info_lb_dev_name,
    1,
    1,
    66,
    7,
    {0, 0, 0, 0},
    {&t_bk_lbclr_lb_dev_name, &t_bk_lbimg_lb_dev_name},
    &t_hlt_elem_effect_lb_dev_name,
    1,
    2,
    t_lbcolumn_init_lb_dev_name_array,
    t_lbcol_inset_lb_dev_name_array,
    t_column_lbfont_lb_dev_name_array,
    t_col_text_lbclr_lb_dev_name_array,
    t_col_bk_lbclr_lb_dev_name_array,
    t_lbitem_lb_dev_name_array,
    t_item_lbfont_lb_dev_name_array,
    t_item_set_lbimg_lb_dev_name_array,
    t_item_text_lbclr_lb_dev_name_array,
    t_item_bk_lbclr_lb_dev_name_array,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_custom_frm_info_panel = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {568, 10, 1920, 270},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_icon_logo},
    NULL
};

static WDK_COLOR_INFO_T t_bk_clr_info_frm_lm_video_info = 
{
    WGL_COLOR_SET_EXTEND,
    {
        &t_g_mmp_blue,
        &t_g_mmp_blue,
        &t_g_mmp_blue,
        &t_g_mmp_blue,
        &t_g_mmp_blue,
        &t_g_mmp_blue
    }
};

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_custom_frm_lm_video_info = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {601, 6, 1331, 247},
    {&t_bk_clr_info_frm_lm_video_info, &t_bk_img_info_mmp_lm_custom_icon_logo},
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_custom_frm_lm_audio_info = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 1342, 260},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_icon_logo},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_custom_btn_back_to_side = 
{
    WGL_IMG_SET_EXTEND,
    {
        NULL,
        NULL,
        &h_g_mmp_back_bar_hlt,
        &h_g_mmp_back_bar_hlt,
        &h_g_mmp_back_bar_hlt,
        NULL
    }
};

static WDK_BTN_WGT_T t_wdk_param_mmp_lm_custom_btn_back_to_side = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {570, 271, 642, 322},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_btn_back_to_side},
    0,
    WGL_AS_LEFT_CENTER,
    &t_bk_img_info_mmp_lm_custom_icon_logo,
    {0, 0, 0, 0},
    &t_font_info_lb_dev_name,
    &t_bk_clr_info_frm_lm_main_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_custom_txt_folder_path_txt = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_BK|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_SMART_CUT_OVER_MAX|WGL_STL_TEXT_IGNORE_NEWLINE|WGL_STL_TEXT_MAX_512,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {658, 271, 1897, 329},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_icon_logo},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_folder_name,
    &t_text_clr_info_txt_folder_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_custom_frm_file_list = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {571, 319, 1920, 1080},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_icon_logo},
    NULL
};

static WDK_LB_IMG_SET_T t_bk_lbimg_lb_title_list = 
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

static WGL_LB_COL_INIT_T t_lbcolumn_init_lb_title_list_array[] = 
{
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_CENTER_CENTER,
        133,
        41
    },
    {
        LB_COL_TYPE_IMG,
        WGL_AS_LEFT_CENTER,
        0,
        41
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        133,
        41
    },
    {
        LB_COL_TYPE_IMG,
        WGL_AS_LEFT_CENTER,
        0,
        41
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        133,
        41
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        133,
        41
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        133,
        41
    }
};

static WGL_INSET_T t_lbcol_inset_lb_title_list_array[] = 
{
    {0, 0, 0, 0},
    {21, 0, 0, 0},
    {21, 0, 0, 0},
    {21, 0, 0, 0},
    {21, 0, 0, 0},
    {21, 0, 0, 0},
    {21, 0, 0, 0}
};

static WDK_LB_FONT_SET_T t_column_lbfont_lb_title_list_array[] = 
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
    },
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
    },
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
    },
    {
        &t_g_mmp_font_small,
        &t_g_mmp_font_small,
        &t_g_mmp_font_small,
        &t_g_mmp_font_small
    }
};

static WDK_LB_COLOR_SET_T t_col_text_lbclr_lb_title_list_array[] = 
{
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
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white
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
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white
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
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white
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

static WDK_LB_COLOR_SET_T t_col_bk_lbclr_lb_title_list_array[] = 
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

static WDK_LB_ITEM_INFO_T t_lbitem_lb_title_list_array[] = 
{
    {
        LB_COL_TYPE_TEXT,
        0,
        WGL_AS_CENTER_CENTER,
        TRUE,
        0
    },
    {
        LB_COL_TYPE_IMG,
        0,
        WGL_AS_CENTER_CENTER,
        TRUE,
        NULL
    },
    {
        LB_COL_TYPE_TEXT,
        0,
        WGL_AS_CENTER_CENTER,
        TRUE,
        0
    },
    {
        LB_COL_TYPE_IMG,
        0,
        WGL_AS_CENTER_CENTER,
        TRUE,
        NULL
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
    },
    {
        LB_COL_TYPE_TEXT,
        0,
        WGL_AS_CENTER_CENTER,
        TRUE,
        0
    }
};

static WDK_LB_FONT_SET_T t_item_lbfont_lb_title_list_array[] = 
{
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

static WDK_LB_IMG_SET_T t_item_set_lbimg_lb_title_list_array[] = 
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

static WDK_LB_COLOR_SET_T t_item_text_lbclr_lb_title_list_array[] = 
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

static WDK_LB_COLOR_SET_T t_item_bk_lbclr_lb_title_list_array[] = 
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

static WDK_LB_WGT_T t_wdk_param_mmp_lm_custom_lb_title_list = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_BK|WGL_STL_LB_FIXED_ELEM_NUM,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 3, 1332, 45},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_icon_logo},
    {7, 7, 0, 0},
    &t_font_info_txt_folder_name,
    1,
    1,
    28,
    8,
    {0, 0, 0, 0},
    {&t_bk_lbclr_lb_dev_name, &t_bk_lbimg_lb_title_list},
    &t_hlt_elem_effect_lb_dev_name,
    1,
    7,
    t_lbcolumn_init_lb_title_list_array,
    t_lbcol_inset_lb_title_list_array,
    t_column_lbfont_lb_title_list_array,
    t_col_text_lbclr_lb_title_list_array,
    t_col_bk_lbclr_lb_title_list_array,
    t_lbitem_lb_title_list_array,
    t_item_lbfont_lb_title_list_array,
    t_item_set_lbimg_lb_title_list_array,
    t_item_text_lbclr_lb_title_list_array,
    t_item_bk_lbclr_lb_title_list_array,
    NULL
};

static WGL_LB_COL_INIT_T t_lbcolumn_init_lb_page_info_list_array[] = 
{
    {
        LB_COL_TYPE_IMG,
        WGL_AS_CENTER_CENTER,
        40,
        41
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_CENTER_CENTER,
        1268,
        41
    },
    {
        LB_COL_TYPE_IMG,
        WGL_AS_CENTER_CENTER,
        40,
        41
    }
};

static WGL_INSET_T t_lbcol_inset_lb_page_info_list_array[] = 
{
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

static WDK_LB_FONT_SET_T t_column_lbfont_lb_page_info_list_array[] = 
{
    {
        NULL,
        NULL,
        NULL,
        NULL
    },
    {
        &t_g_mmp_font_medium,
        &t_g_mmp_font_medium,
        &t_g_mmp_font_medium,
        &t_g_mmp_font_medium
    },
    {
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_LB_COLOR_SET_T t_col_text_lbclr_lb_page_info_list_array[] = 
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
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray,
        &t_g_mmp_gray
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

static WDK_LB_COLOR_SET_T t_col_bk_lbclr_lb_page_info_list_array[] = 
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
    }
};

static WDK_LB_ITEM_INFO_T t_lbitem_lb_page_info_list_array[] = 
{
    {
        LB_COL_TYPE_IMG,
        0,
        WGL_AS_CENTER_CENTER,
        TRUE,
        NULL
    },
    {
        LB_COL_TYPE_TEXT,
        0,
        WGL_AS_CENTER_CENTER,
        TRUE,
        0
    },
    {
        LB_COL_TYPE_IMG,
        0,
        WGL_AS_CENTER_CENTER,
        TRUE,
        NULL
    }
};

static WDK_LB_FONT_SET_T t_item_lbfont_lb_page_info_list_array[] = 
{
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

static WDK_LB_IMG_SET_T t_item_set_lbimg_lb_page_info_list_array[] = 
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
    }
};

static WDK_LB_COLOR_SET_T t_item_text_lbclr_lb_page_info_list_array[] = 
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
    }
};

static WDK_LB_COLOR_SET_T t_item_bk_lbclr_lb_page_info_list_array[] = 
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
    }
};

static WDK_LB_WGT_T t_wdk_param_mmp_lm_custom_lb_page_info_list = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_LB_FIXED_ELEM_NUM,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 720, 1332, 756},
    {&t_bk_clr_info_frm_lm_main_frm, &t_bk_img_info_mmp_lm_custom_icon_logo},
    {0, 0, 0, 0},
    &t_font_info_btn_back_to_menu,
    1,
    1,
    43,
    7,
    {0, 0, 0, 0},
    {&t_bk_lbclr_lb_dev_name, &t_bk_lbimg_lb_title_list},
    &t_hlt_elem_effect_lb_dev_name,
    1,
    3,
    t_lbcolumn_init_lb_page_info_list_array,
    t_lbcol_inset_lb_page_info_list_array,
    t_column_lbfont_lb_page_info_list_array,
    t_col_text_lbclr_lb_page_info_list_array,
    t_col_bk_lbclr_lb_page_info_list_array,
    t_lbitem_lb_page_info_list_array,
    t_item_lbfont_lb_page_info_list_array,
    t_item_set_lbimg_lb_page_info_list_array,
    t_item_text_lbclr_lb_page_info_list_array,
    t_item_bk_lbclr_lb_page_info_list_array,
    NULL
};

static WDK_ITEM_T t_wdk_item_frm_side_panel_array[] = 
{
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_CUSTOM_ICON_FOLDER_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_icon_folder_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_CUSTOM_TXT_FOLDER_NAME,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_txt_folder_name,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_CUSTOM_FRM_CONTROL,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_frm_control,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_LM_CUSTOM_BTN_BACK_TO_MENU,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_btn_back_to_menu,
        NULL
    },
    {
        HT_WGL_WIDGET_LIST_BOX,
        WID_MMP_LM_CUSTOM_LB_DEV_NAME,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_lb_dev_name,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_side_panel = 
{
    sizeof(t_wdk_item_frm_side_panel_array)/sizeof(t_wdk_item_frm_side_panel_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_side_panel_array
};

static WDK_ITEM_T t_wdk_item_frm_info_panel_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_CUSTOM_FRM_LM_VIDEO_INFO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_frm_lm_video_info,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_CUSTOM_FRM_LM_AUDIO_INFO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_frm_lm_audio_info,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_info_panel = 
{
    sizeof(t_wdk_item_frm_info_panel_array)/sizeof(t_wdk_item_frm_info_panel_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_info_panel_array
};

static WDK_ITEM_T t_wdk_item_frm_file_list_array[] = 
{
    {
        HT_WGL_WIDGET_LIST_BOX,
        WID_MMP_LM_CUSTOM_LB_TITLE_LIST,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_lb_title_list,
        NULL
    },
    {
        HT_WGL_WIDGET_LIST_BOX,
        WID_MMP_LM_CUSTOM_LB_PAGE_INFO_LIST,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_lb_page_info_list,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_file_list = 
{
    sizeof(t_wdk_item_frm_file_list_array)/sizeof(t_wdk_item_frm_file_list_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_file_list_array
};

static WDK_ITEM_T t_wdk_item_frm_lm_main_frm_array[] = 
{
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_CUSTOM_ICON_LOGO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_icon_logo,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_CUSTOM_FRM_SIDE_PANEL,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_frm_side_panel,
        (VOID *) &t_wdk_list_frm_side_panel
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_CUSTOM_FRM_INFO_PANEL,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_frm_info_panel,
        (VOID *) &t_wdk_list_frm_info_panel
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_LM_CUSTOM_BTN_BACK_TO_SIDE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_btn_back_to_side,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_CUSTOM_TXT_FOLDER_PATH_TXT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_txt_folder_path_txt,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_CUSTOM_FRM_FILE_LIST,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_frm_file_list,
        (VOID *) &t_wdk_list_frm_file_list
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_lm_main_frm = 
{
    sizeof(t_wdk_item_frm_lm_main_frm_array)/sizeof(t_wdk_item_frm_lm_main_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_lm_main_frm_array
};

static WDK_ITEM_T t_wdk_item_view_lm_custom_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_CUSTOM_FRM_LM_MAIN_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_custom_frm_lm_main_frm,
        (VOID *) &t_wdk_list_frm_lm_main_frm
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_lm_custom = 
{
    sizeof(t_wdk_item_view_lm_custom_array)/sizeof(t_wdk_item_view_lm_custom_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_lm_custom_array
};

static HANDLE_T ah_wgt_handle_mmp_lm_custom[WID_MMP_LM_CUSTOM_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_mmp_lm_custom[WID_MMP_LM_CUSTOM_TOTAL_COUNT];


INT32 mmp_lm_custom_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_mmp_lm_custom, 0, 
             WID_MMP_LM_CUSTOM_TOTAL_COUNT*sizeof(af_wgt_cb_mmp_lm_custom[0]));
    return (WDKR_OK);
}

INT32 mmp_lm_custom_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_MMP_LM_CUSTOM_TOTAL_COUNT)
    {
        af_wgt_cb_mmp_lm_custom[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }

    return (WDKR_FAILED);
}


INT32 mmp_lm_custom_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_lm_custom, 
                                 ah_wgt_handle_mmp_lm_custom,
                                 af_wgt_cb_mmp_lm_custom));
}

HANDLE_T mmp_lm_custom_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_MMP_LM_CUSTOM_TOTAL_COUNT)
    {
        return ah_wgt_handle_mmp_lm_custom[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_lm_custom_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_lm_custom, 
                                      ah_wgt_handle_mmp_lm_custom,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_lm_custom_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_lm_custom, 
                                         ah_wgt_handle_mmp_lm_custom))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 mmp_lm_custom_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_MMP_LM_CUSTOM_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_lm_custom, 
                                 *pt_mi,
                                 af_wgt_cb_mmp_lm_custom));
}

HANDLE_T mmp_lm_custom_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_mmp_lm_custom = NULL;

    h_wgt_handle_mmp_lm_custom = (VOID *)t_mi;

    if (NULL == h_wgt_handle_mmp_lm_custom)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_MMP_LM_CUSTOM_TOTAL_COUNT)
    {
        return h_wgt_handle_mmp_lm_custom[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_lm_custom_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_lm_custom, 
                                      (HANDLE_T *)t_mi,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_lm_custom_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_lm_custom, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}



