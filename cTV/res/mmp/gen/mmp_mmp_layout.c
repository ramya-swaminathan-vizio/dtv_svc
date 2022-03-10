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

#include "mmp_mmp_layout.h"

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_frm_base_frm = 
{
    WGL_IMG_SET_STANDARD,
    {
        &h_g_mmp_photo_ex_bg_template,
        &h_g_mmp_photo_ex_bg_template,
        &h_g_mmp_photo_ex_bg_template,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_bk_clr_info_frm_base_frm = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_base_frm = 
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
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_frm_base_frm},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_frm_left_base_frm = 
{
    WGL_IMG_SET_STANDARD,
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_left_base_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 574, 1080},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_frm_left_base_frm},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_btn_logo_icon = 
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

static WDK_FONT_INFO_T t_font_info_btn_logo_icon = 
{
    WGL_FONT_SET_BASIC,
    {
        NULL,
        NULL
    }
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_logo_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    0,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 6, 174, 72},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_left_ui_frm1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 4, 574, 737},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_frm_left_base_frm},
    NULL
};

static WDK_FONT_INFO_T t_font_info_btn_media_type = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_title_font,
        &t_g_mmp_title_font
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_btn_media_type = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_media_type = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {100, 70, 551, 118},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_LEFT_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {3, 0, 0, 0},
    &t_font_info_btn_media_type,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_lb_driver = 
{
    WGL_IMG_SET_EXTEND,
    {
        NULL,
        NULL,
        &h_g_mmp_lst_hlt,
        &h_g_mmp_lst_hlt,
        &h_g_mmp_lst_hlt,
        NULL
    }
};

static WDK_LB_IMG_SET_T t_bk_lbimg_lb_driver = 
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

static WDK_LB_COLOR_SET_T t_bk_lbclr_lb_driver = 
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static WDK_LB_HLT_ELEM_EFFECT_T t_hlt_elem_effect_lb_driver = 
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

static WGL_LB_COL_INIT_T t_lbcolumn_init_lb_driver_array[] = 
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
        107
    }
};

static WGL_INSET_T t_lbcol_inset_lb_driver_array[] = 
{
    {7, 0, 0, 0},
    {0, 0, 0, 0}
};

static WDK_LB_FONT_SET_T t_column_lbfont_lb_driver_array[] = 
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

static WDK_LB_COLOR_SET_T t_col_text_lbclr_lb_driver_array[] = 
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

static WDK_LB_COLOR_SET_T t_col_bk_lbclr_lb_driver_array[] = 
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

static WDK_LB_ITEM_INFO_T t_lbitem_lb_driver_array[] = 
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

static WDK_LB_FONT_SET_T t_item_lbfont_lb_driver_array[] = 
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

static WDK_LB_IMG_SET_T t_item_set_lbimg_lb_driver_array[] = 
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

static WDK_LB_COLOR_SET_T t_item_text_lbclr_lb_driver_array[] = 
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

static WDK_LB_COLOR_SET_T t_item_bk_lbclr_lb_driver_array[] = 
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

static WDK_LB_WGT_T t_wdk_param_mmp_mmp_lb_driver = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_LB_FIXED_ELEM_NUM,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {4, 138, 566, 204},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_lb_driver},
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    1,
    1,
    66,
    7,
    {0, 0, 0, 0},
    {&t_bk_lbclr_lb_driver, &t_bk_lbimg_lb_driver},
    &t_hlt_elem_effect_lb_driver,
    1,
    2,
    t_lbcolumn_init_lb_driver_array,
    t_lbcol_inset_lb_driver_array,
    t_column_lbfont_lb_driver_array,
    t_col_text_lbclr_lb_driver_array,
    t_col_bk_lbclr_lb_driver_array,
    t_lbitem_lb_driver_array,
    t_item_lbfont_lb_driver_array,
    t_item_set_lbimg_lb_driver_array,
    t_item_text_lbclr_lb_driver_array,
    t_item_bk_lbclr_lb_driver_array,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_btn_start_slideshow = 
{
    WGL_IMG_SET_EXTEND,
    {
        &h_g_mmp_lg_btn,
        &h_g_mmp_lg_btn,
        &h_g_mmp_lg_btn_hlt,
        &h_g_mmp_lg_btn_hlt,
        &h_g_mmp_lg_btn_hlt,
        &h_g_mmp_lg_btn
    }
};

static WDK_FONT_INFO_T t_font_info_btn_start_slideshow = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_thumbnail_font,
        &t_g_mmp_thumbnail_font
    }
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_start_slideshow = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {148, 484, 427, 526},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_start_slideshow},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_name_a_z = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {148, 529, 427, 571},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_start_slideshow},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_thumbnails = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {148, 574, 427, 616},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_start_slideshow},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_settings = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {148, 619, 427, 661},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_start_slideshow},
    MLM_MMP_KEY_THUBM_BTN_SETTINGS,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_browse_music = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {148, 664, 427, 706},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_start_slideshow},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_mmp_icon_file_icon = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_lg_folder_icon,
        &h_g_mmp_lg_folder_icon,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_mmp_mmp_icon_file_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {162, 226, 391, 376},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_mmp_icon_file_icon,
    0,
    0,
    0,
    NULL
};

static WDK_FONT_INFO_T t_font_info_txt_file_name = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_font_small,
        &t_g_mmp_font_small
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_file_name = 
{
    WGL_COLOR_SET_STANDARD,
    {
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        NULL,
        NULL,
        NULL
    }
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_file_name = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_512,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {162, 378, 394, 411},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_sort = 
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

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_sort = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {18, 529, 117, 569},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_txt_sort,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_view = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {18, 574, 117, 614},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_txt_sort,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_btn_back = 
{
    WGL_IMG_SET_EXTEND,
    {
        NULL,
        NULL,
        &h_g_mmp_back_bar_hlt,
        &h_g_mmp_back_bar_hlt,
        &h_g_mmp_back_bar_hlt,
        &h_g_mmp_back_bar_nr
    }
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_back = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {3, 69, 72, 117},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_back},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_logo_icon_1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 4, 174, 70},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_file_info = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {22, 762, 562, 961},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_right_base_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {570, 0, 1920, 1080},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_mmp_btn_right_to_left_btn = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_right_to_left_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 73, 69, 128},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_mmp_btn_right_to_left_btn,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_page_num = 
{
    WGL_COLOR_SET_BASIC,
    {
        &t_g_mmp_white,
        &t_g_mmp_white,
        &t_g_mmp_white,
        NULL,
        NULL,
        NULL
    }
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_page_num = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {42, 1040, 1288, 1080},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_txt_page_num,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_path = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_IGNORE_NEWLINE|WGL_STL_TEXT_MAX_512,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {87, 73, 1293, 128},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_frm_left_base_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_mmp_btn_page_next = 
{
    WGL_IMG_SET_STANDARD,
    {
        &h_g_mmp_pg_next_icon_nr,
        &h_g_mmp_pg_next_icon_nr,
        &h_g_mmp_pg_next_icon_nr,
        NULL,
        NULL,
        NULL
    }
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_page_next = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {1294, 1040, 1334, 1076},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_mmp_btn_page_next,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_mmp_btn_page_back = 
{
    WGL_IMG_SET_STANDARD,
    {
        &h_g_mmp_pg_back_icon_nr,
        &h_g_mmp_pg_back_icon_nr,
        &h_g_mmp_pg_back_icon_nr,
        NULL,
        NULL,
        &h_g_mmp_pg_back_icon_dim
    }
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_page_back = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {4, 1040, 41, 1076},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_frm_left_base_frm},
    0,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_mmp_btn_page_back,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_thumbnailmode_ui = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {4, 124, 1349, 1066},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_COLOR_INFO_T t_bdr_bk_clr_info_frm_hlt_thumb_mov_frm = 
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

static WDK_BORDER_INFO_T t_uniform_bdr_info_frm_hlt_thumb_mov_frm = 
{
    {5, 5, 5, 5},
    &t_bdr_bk_clr_info_frm_hlt_thumb_mov_frm,
    &t_bk_clr_info_frm_base_frm,
    4,
    0,
    0,
    0,
    NULL,
    {0, 0, 0, 0},
    NULL,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_hlt_thumb_mov_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_frm_hlt_thumb_mov_frm,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {141, 22, 424, 245},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_BORDER_INFO_T t_uniform_bdr_info_btn_thumbnailmode0 = 
{
    {4, 4, 4, 4},
    &t_text_clr_info_txt_sort,
    &t_bk_clr_info_frm_base_frm,
    3,
    0,
    0,
    0,
    NULL,
    {0, 0, 0, 0},
    NULL,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_thumbnailmode0 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {18, 6, 76, 70},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext0 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {465, 265, 664, 307},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_thumbnailmode1 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {12, 7, 75, 65},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 265, 388, 307},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_thumbnailmode2 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {21, 0, 72, 55},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_TEXT_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext2 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 270, 388, 312},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_thumbnailmode3 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {12, 1, 81, 64},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_TEXT_FIRST,
    NULL
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_newtext3 = 
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

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext3 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 270, 388, 312},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_newtext3,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_thumbnailmode4 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {27, 16, 72, 67},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext4 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 270, 388, 312},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_thumbnailmode5 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {12, 6, 81, 67},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext5 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 264, 388, 306},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_thumbnailmode6 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {12, 6, 81, 67},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext6 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 270, 388, 312},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_thumbnailmode7 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {12, 6, 81, 67},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext7 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 270, 388, 312},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_thumbnailmode8 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {12, 6, 81, 67},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext8 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {186, 228, 387, 270},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_frm_hlt_folder_move_frm = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_floder_focus_hlt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_hlt_folder_move_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {174, 64, 402, 262},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_frm_hlt_folder_move_frm},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext_455 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {16, 169, 205, 190},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    MLM_MMP_KEY_EMPTY,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_frm_pre_folder = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_pre_folder = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 78, 417, 274},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_frm_pre_folder},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtex0 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 300, 417, 337},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_folder1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {567, 78, 795, 274},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext_1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {568, 307, 796, 344},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_folder2 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {946, 78, 1174, 274},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext_2 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {942, 307, 1170, 344},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_folder3 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 382, 417, 578},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext_3 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 613, 417, 650},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_folder4 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {568, 382, 796, 578},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext_4 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {568, 613, 796, 650},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_folder5 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {946, 382, 1174, 578},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext_5 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {942, 613, 1170, 650},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_folder6 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 676, 417, 872},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext_6 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {189, 882, 417, 919},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_folder7 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {568, 676, 796, 872},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext_7 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {568, 588, 796, 625},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_folder8 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {946, 676, 1174, 872},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_newtext_8 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {942, 882, 1170, 919},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_skip0 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {16, 1, 71, 59},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_skip0_1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {21, 7, 58, 40},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_skip0_2 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {24, 12, 60, 54},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_skip0_3 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {33, 18, 63, 55},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_skip0_4 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {27, 19, 69, 53},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_skip0_5 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {16, 10, 76, 65},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_skip0_6 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {21, 12, 64, 55},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_skip0_7 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {39, 8, 63, 60},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_skip0_8 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {15, 1, 57, 52},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BORDER_INFO_T t_raised_bdr_info_frm_pop_up_base_frm = 
{
    {0, 0, 0, 0},
    &t_bk_clr_info_frm_base_frm,
    &t_bk_clr_info_frm_base_frm,
    0,
    2,
    0,
    0,
    NULL,
    {0, 0, 0, 0},
    NULL,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_frm_pop_up_base_frm = 
{
    WGL_IMG_SET_EXTEND,
    {
        &h_g_mmp_pop_up_bg_temp,
        &h_g_mmp_pop_up_bg_temp,
        &h_g_mmp_pop_up_bg_temp,
        &h_g_mmp_pop_up_bg_temp,
        &h_g_mmp_pop_up_bg_temp,
        &h_g_mmp_pop_up_bg_temp
    }
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_pop_up_base_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_RAISED,
    &t_raised_bdr_info_frm_pop_up_base_frm,
    0,
    255,
    TRUE,
    WGL_SW_RECURSIVE,
    NULL,
    {672, 199, 1234, 919},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_frm_pop_up_base_frm},
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_image_preview_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_RECURSIVE,
    NULL,
    {133, 79, 425, 295},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_mmp_frm_pop_up_bg = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_RECURSIVE,
    NULL,
    {0, 0, 562, 720},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_frm_pop_up_base_frm},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_exclude_status_text = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MULTILINE|WGL_STL_TEXT_MAX_512,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {13, 642, 553, 715},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_startslideshow_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {136, 460, 421, 499},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_start_slideshow},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_btn_photo_info_btn = 
{
    WGL_IMG_SET_EXTEND,
    {
        &h_g_mmp_pop_up_photo_info,
        &h_g_mmp_pop_up_photo_info,
        &h_g_mmp_pop_up_photo_info_hlt,
        &h_g_mmp_pop_up_photo_info_hlt,
        &h_g_mmp_pop_up_photo_info_hlt,
        &h_g_mmp_pop_up_photo_info
    }
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_photo_info_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {96, 343, 180, 427},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_photo_info_btn},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_photo_info_btn,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_btn_photo_rotate_left_btn = 
{
    WGL_IMG_SET_EXTEND,
    {
        &h_g_mmp_pop_up_rotate_ccw,
        &h_g_mmp_pop_up_rotate_ccw,
        &h_g_mmp_pop_up_rotate_ccw_hlt,
        &h_g_mmp_pop_up_rotate_ccw_hlt,
        &h_g_mmp_pop_up_rotate_ccw_hlt,
        &h_g_mmp_pop_up_rotate_ccw
    }
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_photo_rotate_left_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {192, 343, 283, 427},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_photo_rotate_left_btn},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_btn_rotate_right_btn = 
{
    WGL_IMG_SET_EXTEND,
    {
        &h_g_mmp_pop_up_rotate_cw,
        &h_g_mmp_pop_up_rotate_cw,
        &h_g_mmp_pop_up_rotate_cw_hlt,
        &h_g_mmp_pop_up_rotate_cw_hlt,
        &h_g_mmp_pop_up_rotate_cw_hlt,
        &h_g_mmp_pop_up_rotate_cw
    }
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_rotate_right_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {286, 343, 365, 421},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_rotate_right_btn},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_mmp_btn_stop_btn = 
{
    WGL_IMG_SET_EXTEND,
    {
        &h_g_mmp_pop_up_exculde_icon,
        &h_g_mmp_pop_up_exculde_icon,
        &h_g_mmp_pop_up_exculde_htl_icon,
        &h_g_mmp_pop_up_exculde_htl_icon,
        &h_g_mmp_pop_up_exculde_htl_icon,
        &h_g_mmp_pop_up_exculde_icon
    }
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_stop_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {379, 343, 472, 421},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_stop_btn},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_done_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {136, 568, 421, 607},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_start_slideshow},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_mmp_btn_full_screen_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {136, 514, 421, 553},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_start_slideshow},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_mmp_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_mmp_txt_modify_photo = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {13, 13, 403, 65},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_mmp_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ITEM_T t_wdk_item_frm_left_ui_frm1_array[] = 
{
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_MEDIA_TYPE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_media_type,
        NULL
    },
    {
        HT_WGL_WIDGET_LIST_BOX,
        WID_MMP_MMP_LB_DRIVER,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_lb_driver,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_START_SLIDESHOW,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_start_slideshow,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_NAME_A_Z,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_name_a_z,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_THUMBNAILS,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_thumbnails,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_SETTINGS,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_settings,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_BROWSE_MUSIC,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_browse_music,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_MMP_ICON_FILE_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_icon_file_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_FILE_NAME,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_file_name,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_SORT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_sort,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_VIEW,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_view,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_BACK,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_back,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_LOGO_ICON_1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_logo_icon_1,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_left_ui_frm1 = 
{
    sizeof(t_wdk_item_frm_left_ui_frm1_array)/sizeof(t_wdk_item_frm_left_ui_frm1_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_left_ui_frm1_array
};

static WDK_ITEM_T t_wdk_item_frm_left_base_frm_array[] = 
{
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_LOGO_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_logo_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_LEFT_UI_FRM1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_left_ui_frm1,
        (VOID *) &t_wdk_list_frm_left_ui_frm1
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_FILE_INFO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_file_info,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_left_base_frm = 
{
    sizeof(t_wdk_item_frm_left_base_frm_array)/sizeof(t_wdk_item_frm_left_base_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_left_base_frm_array
};

static WDK_ITEM_T t_wdk_item_frm_hlt_folder_move_frm_array[] = 
{
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT_455,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext_455,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_hlt_folder_move_frm = 
{
    sizeof(t_wdk_item_frm_hlt_folder_move_frm_array)/sizeof(t_wdk_item_frm_hlt_folder_move_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_hlt_folder_move_frm_array
};

static WDK_ITEM_T t_wdk_item_frm_thumbnailmode_ui_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_HLT_THUMB_MOV_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_hlt_thumb_mov_frm,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_THUMBNAILMODE0,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_thumbnailmode0,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT0,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext0,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_THUMBNAILMODE1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_thumbnailmode1,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext1,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_THUMBNAILMODE2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_thumbnailmode2,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext2,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_THUMBNAILMODE3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_thumbnailmode3,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext3,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_THUMBNAILMODE4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_thumbnailmode4,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext4,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_THUMBNAILMODE5,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_thumbnailmode5,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT5,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext5,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_THUMBNAILMODE6,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_thumbnailmode6,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT6,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext6,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_THUMBNAILMODE7,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_thumbnailmode7,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT7,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext7,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_THUMBNAILMODE8,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_thumbnailmode8,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT8,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext8,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_HLT_FOLDER_MOVE_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_hlt_folder_move_frm,
        (VOID *) &t_wdk_list_frm_hlt_folder_move_frm
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_PRE_FOLDER,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_pre_folder,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEX0,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtex0,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_FOLDER1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_folder1,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT_1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext_1,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_FOLDER2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_folder2,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT_2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext_2,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_FOLDER3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_folder3,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT_3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext_3,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_FOLDER4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_folder4,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT_4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext_4,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_FOLDER5,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_folder5,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT_5,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext_5,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_FOLDER6,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_folder6,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT_6,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext_6,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_FOLDER7,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_folder7,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT_7,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext_7,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_FOLDER8,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_folder8,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_NEWTEXT_8,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_newtext_8,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_SKIP0,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_skip0,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_SKIP0_1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_skip0_1,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_SKIP0_2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_skip0_2,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_SKIP0_3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_skip0_3,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_SKIP0_4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_skip0_4,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_SKIP0_5,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_skip0_5,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_SKIP0_6,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_skip0_6,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_SKIP0_7,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_skip0_7,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_SKIP0_8,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_skip0_8,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_thumbnailmode_ui = 
{
    sizeof(t_wdk_item_frm_thumbnailmode_ui_array)/sizeof(t_wdk_item_frm_thumbnailmode_ui_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_thumbnailmode_ui_array
};

static WDK_ITEM_T t_wdk_item_frm_right_base_frm_array[] = 
{
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_RIGHT_TO_LEFT_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_right_to_left_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_PAGE_NUM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_page_num,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_PATH,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_path,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_PAGE_NEXT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_page_next,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_PAGE_BACK,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_page_back,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_THUMBNAILMODE_UI,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_thumbnailmode_ui,
        (VOID *) &t_wdk_list_frm_thumbnailmode_ui
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_right_base_frm = 
{
    sizeof(t_wdk_item_frm_right_base_frm_array)/sizeof(t_wdk_item_frm_right_base_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_right_base_frm_array
};

static WDK_ITEM_T t_wdk_item_frm_pop_up_bg_array[] = 
{
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_EXCLUDE_STATUS_TEXT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_exclude_status_text,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_STARTSLIDESHOW_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_startslideshow_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_PHOTO_INFO_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_photo_info_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_PHOTO_ROTATE_LEFT_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_photo_rotate_left_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_ROTATE_RIGHT_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_rotate_right_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_STOP_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_stop_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_DONE_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_done_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_MMP_BTN_FULL_SCREEN_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_btn_full_screen_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_MMP_TXT_MODIFY_PHOTO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_txt_modify_photo,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_pop_up_bg = 
{
    sizeof(t_wdk_item_frm_pop_up_bg_array)/sizeof(t_wdk_item_frm_pop_up_bg_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_pop_up_bg_array
};

static WDK_ITEM_T t_wdk_item_frm_pop_up_base_frm_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_IMAGE_PREVIEW_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_image_preview_frm,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_POP_UP_BG,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_pop_up_bg,
        (VOID *) &t_wdk_list_frm_pop_up_bg
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_pop_up_base_frm = 
{
    sizeof(t_wdk_item_frm_pop_up_base_frm_array)/sizeof(t_wdk_item_frm_pop_up_base_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_pop_up_base_frm_array
};

static WDK_ITEM_T t_wdk_item_frm_base_frm_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_LEFT_BASE_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_left_base_frm,
        (VOID *) &t_wdk_list_frm_left_base_frm
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_RIGHT_BASE_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_right_base_frm,
        (VOID *) &t_wdk_list_frm_right_base_frm
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_POP_UP_BASE_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_pop_up_base_frm,
        (VOID *) &t_wdk_list_frm_pop_up_base_frm
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_base_frm = 
{
    sizeof(t_wdk_item_frm_base_frm_array)/sizeof(t_wdk_item_frm_base_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_base_frm_array
};

static WDK_ITEM_T t_wdk_item_view_mmp_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_MMP_FRM_BASE_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_mmp_frm_base_frm,
        (VOID *) &t_wdk_list_frm_base_frm
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_mmp = 
{
    sizeof(t_wdk_item_view_mmp_array)/sizeof(t_wdk_item_view_mmp_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_mmp_array
};

static HANDLE_T ah_wgt_handle_mmp_mmp[WID_MMP_MMP_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_mmp_mmp[WID_MMP_MMP_TOTAL_COUNT];


INT32 mmp_mmp_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_mmp_mmp, 0, 
             WID_MMP_MMP_TOTAL_COUNT*sizeof(af_wgt_cb_mmp_mmp[0]));
    return (WDKR_OK);
}

INT32 mmp_mmp_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_MMP_MMP_TOTAL_COUNT)
    {
        af_wgt_cb_mmp_mmp[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }

    return (WDKR_FAILED);
}


INT32 mmp_mmp_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_mmp, 
                                 ah_wgt_handle_mmp_mmp,
                                 af_wgt_cb_mmp_mmp));
}

HANDLE_T mmp_mmp_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_MMP_MMP_TOTAL_COUNT)
    {
        return ah_wgt_handle_mmp_mmp[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_mmp_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_mmp, 
                                      ah_wgt_handle_mmp_mmp,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_mmp_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_mmp, 
                                         ah_wgt_handle_mmp_mmp))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 mmp_mmp_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_MMP_MMP_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_mmp, 
                                 *pt_mi,
                                 af_wgt_cb_mmp_mmp));
}

HANDLE_T mmp_mmp_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_mmp_mmp = NULL;

    h_wgt_handle_mmp_mmp = (VOID *)t_mi;

    if (NULL == h_wgt_handle_mmp_mmp)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_MMP_MMP_TOTAL_COUNT)
    {
        return h_wgt_handle_mmp_mmp[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_mmp_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_mmp, 
                                      (HANDLE_T *)t_mi,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_mmp_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_mmp, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}



