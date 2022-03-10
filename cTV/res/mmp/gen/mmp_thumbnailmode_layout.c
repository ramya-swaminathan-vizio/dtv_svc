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

#include "mmp_thumbnailmode_layout.h"

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_frm_base_frm = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_base_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 960, 540},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_frm_base_frm},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_frm_left_base_frm = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_left_base_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 287, 540},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_frm_left_base_frm},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_btn_logo_icon = 
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

static WDK_IMG_INFO_T t_fg_img_info_mmp_thumbnailmode_btn_logo_icon = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_vizio_logo,
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_logo_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    0,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 3, 87, 36},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_left_ui_frm1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 3, 287, 370},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_frm_left_base_frm},
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_media_type = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {50, 36, 276, 59},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {2, 0, 0, 0},
    &t_font_info_btn_media_type,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_lb_driver = 
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

static WDK_LB_IMG_SET_T t_bk_lbimg_lb_driver = 
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
        90,
        60
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        180,
        80
    }
};

static WGL_INSET_T t_lbcol_inset_lb_driver_array[] = 
{
    {5, 0, 0, 0},
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

static WDK_LB_WGT_T t_wdk_param_mmp_thumbnailmode_lb_driver = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_LB_FIXED_ELEM_NUM,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {5, 72, 274, 105},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_lb_driver},
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    1,
    1,
    33,
    5,
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

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_btn_start_slideshow = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_start_slideshow = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {75, 245, 215, 266},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_start_slideshow},
    0,
    WGL_AS_CENTER_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_name_a_z = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {74, 268, 214, 289},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_start_slideshow},
    0,
    WGL_AS_CENTER_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_thumbnails = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {74, 291, 214, 312},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_start_slideshow},
    0,
    WGL_AS_CENTER_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_settings = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {74, 314, 214, 335},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_start_slideshow},
    MLM_MMP_KEY_THUBM_BTN_SETTINGS,
    WGL_AS_CENTER_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_browse_music = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {74, 337, 214, 358},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_start_slideshow},
    0,
    WGL_AS_CENTER_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_thumbnailmode_icon_file_icon = 
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

static WDK_ICON_WGT_T t_wdk_param_mmp_thumbnailmode_icon_file_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {96, 114, 196, 189},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    {0, 0, 0, 0},
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_thumbnailmode_icon_file_icon,
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

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_file_name = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_512,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 190, 194, 202},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
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

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_sort = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {10, 265, 59, 285},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_TOP,
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_txt_sort,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_view = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {10, 286, 59, 306},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_TOP,
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_txt_sort,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_btn_back = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_back = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {5, 35, 49, 60},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_back},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_logo_icon_1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 3, 87, 36},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_file_info = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {11, 381, 281, 481},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_right_base_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {287, 0, 960, 540},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_thumbnailmode_btn_right_to_left_btn = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_right_to_left_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 38, 40, 61},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_thumbnailmode_btn_right_to_left_btn,
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

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_page_num = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {19, 511, 642, 532},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_txt_page_num,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_path = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_IGNORE_NEWLINE|WGL_STL_TEXT_MAX_512,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {41, 38, 644, 58},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_frm_left_base_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_thumbnailmode_btn_page_next = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_page_next = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {645, 516, 665, 534},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_thumbnailmode_btn_page_next,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_thumbnailmode_btn_page_back = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_page_back = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 515, 19, 535},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_frm_left_base_frm},
    0,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_mmp_thumbnailmode_btn_page_back,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_thumbnailmode_ui = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 62, 673, 533},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
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
    {4, 4, 4, 4},
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

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_hlt_thumb_mov_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_frm_hlt_thumb_mov_frm,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {71, 14, 213, 126},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_BORDER_INFO_T t_uniform_bdr_info_btn_thumbnailmode0 = 
{
    {3, 3, 3, 3},
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode0 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {10, 6, 39, 38},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext0 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {233, 136, 333, 151},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode1 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {7, 7, 38, 36},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 136, 195, 151},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode2 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {11, 3, 37, 31},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_TEXT_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext2 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 138, 195, 153},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode3 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {7, 4, 41, 35},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    MLM_MMP_KEY_ARTIST_HINT,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
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

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext3 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 138, 195, 153},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_newtext3,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode4 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {14, 11, 37, 37},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext4 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 138, 195, 153},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode5 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {7, 6, 41, 37},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext5 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 135, 195, 153},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode6 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {7, 6, 41, 37},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext6 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 138, 195, 159},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode7 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {7, 6, 41, 37},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext7 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 138, 195, 153},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode8 = 
{
    NULL_HANDLE,
    WGL_BORDER_UNIFORM,
    &t_uniform_bdr_info_btn_thumbnailmode0,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {7, 6, 41, 37},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    MLM_MMP_KEY_SB_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext8 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {94, 117, 194, 141},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_frm_hlt_folder_move_frm = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_hlt_folder_move_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {88, 35, 202, 134},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_frm_hlt_folder_move_frm},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext_455 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {8, 85, 103, 95},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    MLM_MMP_KEY_EMPTY,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_frm_pre_folder = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_pre_folder = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 42, 195, 121},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_frm_pre_folder},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtex0 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 139, 195, 154},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_folder1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {284, 42, 384, 120},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext_1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {285, 139, 385, 154},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_folder2 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {474, 42, 574, 120},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext_2 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {472, 142, 572, 157},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_folder3 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 194, 195, 272},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext_3 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {94, 292, 194, 307},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_folder4 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {285, 194, 385, 272},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext_4 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {285, 291, 385, 306},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_folder5 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {474, 194, 574, 272},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext_5 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {482, 288, 582, 303},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_folder6 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {95, 341, 195, 419},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext_6 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {93, 426, 193, 441},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_folder7 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {285, 341, 385, 419},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext_7 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {285, 423, 385, 438},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_folder8 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {474, 341, 574, 419},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_newtext_8 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {472, 423, 572, 438},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_txt_file_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_skip0 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {9, 4, 37, 33},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_skip0_1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {11, 7, 30, 23},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_skip0_2 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {13, 9, 31, 30},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_skip0_3 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {17, 12, 32, 31},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_skip0_4 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {14, 13, 35, 30},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_skip0_5 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {9, 8, 39, 36},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_skip0_6 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {11, 9, 33, 31},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_skip0_7 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {20, 9, 32, 33},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_skip0_8 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {8, 4, 29, 29},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
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

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_frm_pop_up_base_frm = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_pop_up_base_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_RAISED,
    &t_raised_bdr_info_frm_pop_up_base_frm,
    0,
    255,
    TRUE,
    WGL_SW_RECURSIVE,
    NULL,
    {336, 100, 617, 460},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_frm_pop_up_base_frm},
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_image_preview_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK,
    255,
    TRUE,
    WGL_SW_RECURSIVE,
    NULL,
    {67, 40, 213, 148},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_thumbnailmode_frm_pop_up_bg = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_RECURSIVE,
    NULL,
    {0, 0, 281, 360},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_frm_pop_up_base_frm},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_exclude_status_text = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MULTILINE|WGL_STL_TEXT_MAX_512,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {7, 321, 277, 358},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_file_name,
    &t_text_clr_info_btn_media_type,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_startslideshow_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {68, 230, 211, 250},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_start_slideshow},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_btn_photo_info_btn = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_photo_info_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {48, 172, 90, 214},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_photo_info_btn},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_photo_info_btn,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_btn_photo_rotate_left_btn = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_photo_rotate_left_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {96, 172, 142, 214},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_photo_rotate_left_btn},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_btn_rotate_right_btn = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_rotate_right_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {143, 172, 183, 211},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_rotate_right_btn},
    0,
    WGL_AS_LEFT_TOP,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_thumbnailmode_btn_stop_btn = 
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

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_stop_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {190, 172, 236, 211},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_stop_btn},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_logo_icon,
    &t_bk_clr_info_frm_base_frm,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_done_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {68, 284, 211, 304},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_start_slideshow},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_mmp_thumbnailmode_btn_full_screen_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {68, 257, 211, 277},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_start_slideshow},
    0,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon,
    {0, 0, 0, 0},
    &t_font_info_btn_start_slideshow,
    &t_text_clr_info_btn_media_type,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_thumbnailmode_txt_modify_photo = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {7, 7, 202, 33},
    {&t_bk_clr_info_frm_base_frm, &t_bk_img_info_mmp_thumbnailmode_btn_logo_icon},
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
        WID_MMP_THUMBNAILMODE_BTN_MEDIA_TYPE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_media_type,
        NULL
    },
    {
        HT_WGL_WIDGET_LIST_BOX,
        WID_MMP_THUMBNAILMODE_LB_DRIVER,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_lb_driver,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_START_SLIDESHOW,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_start_slideshow,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_NAME_A_Z,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_name_a_z,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_THUMBNAILS,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_thumbnails,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_SETTINGS,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_settings,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_BROWSE_MUSIC,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_browse_music,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_THUMBNAILMODE_ICON_FILE_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_icon_file_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_FILE_NAME,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_file_name,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_SORT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_sort,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_VIEW,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_view,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_BACK,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_back,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_LOGO_ICON_1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_logo_icon_1,
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
        WID_MMP_THUMBNAILMODE_BTN_LOGO_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_logo_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_LEFT_UI_FRM1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_left_ui_frm1,
        (VOID *) &t_wdk_list_frm_left_ui_frm1
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_FILE_INFO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_file_info,
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
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_455,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext_455,
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
        WID_MMP_THUMBNAILMODE_FRM_HLT_THUMB_MOV_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_hlt_thumb_mov_frm,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE0,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode0,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT0,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext0,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode1,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext1,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode2,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext2,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode3,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext3,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode4,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext4,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE5,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode5,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT5,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext5,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE6,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode6,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT6,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext6,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE7,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode7,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT7,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext7,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE8,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_thumbnailmode8,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT8,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext8,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_HLT_FOLDER_MOVE_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_hlt_folder_move_frm,
        (VOID *) &t_wdk_list_frm_hlt_folder_move_frm
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_PRE_FOLDER,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_pre_folder,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEX0,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtex0,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_FOLDER1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_folder1,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext_1,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_FOLDER2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_folder2,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext_2,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_FOLDER3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_folder3,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext_3,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_FOLDER4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_folder4,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext_4,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_FOLDER5,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_folder5,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_5,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext_5,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_FOLDER6,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_folder6,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_6,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext_6,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_FOLDER7,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_folder7,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_7,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext_7,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_FOLDER8,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_folder8,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_8,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_newtext_8,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_SKIP0,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_skip0,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_SKIP0_1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_skip0_1,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_SKIP0_2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_skip0_2,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_SKIP0_3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_skip0_3,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_SKIP0_4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_skip0_4,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_SKIP0_5,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_skip0_5,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_SKIP0_6,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_skip0_6,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_SKIP0_7,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_skip0_7,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_SKIP0_8,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_skip0_8,
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
        WID_MMP_THUMBNAILMODE_BTN_RIGHT_TO_LEFT_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_right_to_left_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_PAGE_NUM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_page_num,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_PATH,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_path,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_PAGE_NEXT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_page_next,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_PAGE_BACK,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_page_back,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_THUMBNAILMODE_UI,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_thumbnailmode_ui,
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
        WID_MMP_THUMBNAILMODE_TXT_EXCLUDE_STATUS_TEXT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_exclude_status_text,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_STARTSLIDESHOW_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_startslideshow_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_PHOTO_INFO_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_photo_info_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_PHOTO_ROTATE_LEFT_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_photo_rotate_left_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_ROTATE_RIGHT_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_rotate_right_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_STOP_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_stop_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_DONE_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_done_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_MMP_THUMBNAILMODE_BTN_FULL_SCREEN_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_btn_full_screen_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_THUMBNAILMODE_TXT_MODIFY_PHOTO,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_txt_modify_photo,
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
        WID_MMP_THUMBNAILMODE_FRM_IMAGE_PREVIEW_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_image_preview_frm,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_POP_UP_BG,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_pop_up_bg,
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
        WID_MMP_THUMBNAILMODE_FRM_LEFT_BASE_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_left_base_frm,
        (VOID *) &t_wdk_list_frm_left_base_frm
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_RIGHT_BASE_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_right_base_frm,
        (VOID *) &t_wdk_list_frm_right_base_frm
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_POP_UP_BASE_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_pop_up_base_frm,
        (VOID *) &t_wdk_list_frm_pop_up_base_frm
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_base_frm = 
{
    sizeof(t_wdk_item_frm_base_frm_array)/sizeof(t_wdk_item_frm_base_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_base_frm_array
};

static WDK_ITEM_T t_wdk_item_view_thumbnailmode_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_THUMBNAILMODE_FRM_BASE_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_thumbnailmode_frm_base_frm,
        (VOID *) &t_wdk_list_frm_base_frm
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_thumbnailmode = 
{
    sizeof(t_wdk_item_view_thumbnailmode_array)/sizeof(t_wdk_item_view_thumbnailmode_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_thumbnailmode_array
};

static HANDLE_T ah_wgt_handle_mmp_thumbnailmode[WID_MMP_THUMBNAILMODE_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_mmp_thumbnailmode[WID_MMP_THUMBNAILMODE_TOTAL_COUNT];


INT32 mmp_thumbnailmode_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_mmp_thumbnailmode, 0, 
             WID_MMP_THUMBNAILMODE_TOTAL_COUNT*sizeof(af_wgt_cb_mmp_thumbnailmode[0]));
    return (WDKR_OK);
}

INT32 mmp_thumbnailmode_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_MMP_THUMBNAILMODE_TOTAL_COUNT)
    {
        af_wgt_cb_mmp_thumbnailmode[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }

    return (WDKR_FAILED);
}


INT32 mmp_thumbnailmode_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_thumbnailmode, 
                                 ah_wgt_handle_mmp_thumbnailmode,
                                 af_wgt_cb_mmp_thumbnailmode));
}

HANDLE_T mmp_thumbnailmode_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_MMP_THUMBNAILMODE_TOTAL_COUNT)
    {
        return ah_wgt_handle_mmp_thumbnailmode[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_thumbnailmode_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_thumbnailmode, 
                                      ah_wgt_handle_mmp_thumbnailmode,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_thumbnailmode_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_thumbnailmode, 
                                         ah_wgt_handle_mmp_thumbnailmode))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 mmp_thumbnailmode_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_MMP_THUMBNAILMODE_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_thumbnailmode, 
                                 *pt_mi,
                                 af_wgt_cb_mmp_thumbnailmode));
}

HANDLE_T mmp_thumbnailmode_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_mmp_thumbnailmode = NULL;

    h_wgt_handle_mmp_thumbnailmode = (VOID *)t_mi;

    if (NULL == h_wgt_handle_mmp_thumbnailmode)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_MMP_THUMBNAILMODE_TOTAL_COUNT)
    {
        return h_wgt_handle_mmp_thumbnailmode[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_thumbnailmode_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_thumbnailmode, 
                                      (HANDLE_T *)t_mi,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_thumbnailmode_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_thumbnailmode, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}



