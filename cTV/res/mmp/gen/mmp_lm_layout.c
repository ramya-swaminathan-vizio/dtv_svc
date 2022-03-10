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

#include "mmp_lm_layout.h"

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_frm_top_frm = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_MMP_Common_bg_top,
        &h_g_MMP_Common_bg_top,
        &h_g_MMP_Common_bg_top,
        &h_g_MMP_Common_bg_top,
        &h_g_MMP_Common_bg_top,
        &h_g_MMP_Common_bg_top
    }
};

static WDK_COLOR_INFO_T t_bk_clr_info_frm_top_frm = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_frm_top_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 960, 60},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_frm_top_frm},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_icon_type_icon = 
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

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_icon_type_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {35, 0, 92, 60},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    {0, 0, 0, 0},
    WGL_AS_LEFT_CENTER,
    &t_bk_img_info_mmp_lm_icon_type_icon,
    0,
    0,
    0,
    NULL
};

static WDK_FONT_INFO_T t_font_info_txt_type_txt = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_font_small,
        &t_g_mmp_font_small
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_type_txt = 
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

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_txt_type_txt = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {92, 0, 240, 60},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_type_txt,
    &t_text_clr_info_txt_type_txt,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_icon_path_icon = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_folder_icon_img,
        &h_g_mmp_folder_icon_img,
        &h_g_mmp_folder_icon_img,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_icon_path_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {240, 10, 298, 60},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_path_icon},
    {0, 0, 0, 0},
    WGL_AS_LEFT_CENTER,
    &t_bk_img_info_mmp_lm_icon_type_icon,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_txt_path_txt = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_SMART_CUT_OVER_MAX|WGL_STL_TEXT_MAX_512,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {298, 0, 822, 60},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_type_txt,
    &t_text_clr_info_txt_type_txt,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_icon_page_icon = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_page_icon_img,
        &h_g_mmp_page_icon_img,
        &h_g_mmp_page_icon_img,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_icon_page_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {822, 10, 860, 60},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_page_icon},
    {0, 0, 0, 0},
    WGL_AS_LEFT_CENTER,
    &t_bk_img_info_mmp_lm_icon_type_icon,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_txt_page_txt = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {860, 0, 960, 60},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_type_txt,
    &t_text_clr_info_txt_type_txt,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_frm_mid_frm = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_MMP_Common_bg_Middle_H,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_frm_mid_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 60, 960, 499},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_frm_mid_frm},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_frm_prw_frm = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_listmode_viewer_bg,
        &h_g_mmp_listmode_viewer_bg,
        &h_g_mmp_listmode_viewer_bg,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_frm_prw_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {42, 4, 301, 289},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_frm_prw_frm},
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_frm_ctrl_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {42, 295, 301, 421},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_mmp_lm_frm_btn_frm = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_MMP_Common_bg_bottom_H,
        &h_g_MMP_Common_bg_bottom_H,
        &h_g_MMP_Common_bg_bottom_H,
        &h_g_MMP_Common_bg_bottom_H,
        &h_g_MMP_Common_bg_bottom_H,
        &h_g_MMP_Common_bg_bottom_H
    }
};

static WDK_FRM_WGT_T t_wdk_param_mmp_lm_frm_btn_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 499, 960, 540},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_frm_btn_frm},
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_lm_icon_help_icon_1 = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_btm_select_img,
        &h_g_mmp_btm_select_img,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_icon_help_icon_1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {76, 0, 118, 41},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    {0, 0, 0, 0},
    WGL_AS_LEFT_CENTER,
    &t_fg_img_info_mmp_lm_icon_help_icon_1,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_txt_help_txt_1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {120, 0, 346, 41},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    MLM_MMP_KEY_LM_SELECTION,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_type_txt,
    &t_text_clr_info_txt_type_txt,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_lm_icon_help_icon_2 = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_btm_enter_img,
        &h_g_mmp_btm_enter_img,
        &h_g_mmp_btm_enter_img,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_icon_help_icon_2 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {346, 0, 388, 41},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    {0, 0, 0, 0},
    WGL_AS_LEFT_CENTER,
    &t_fg_img_info_mmp_lm_icon_help_icon_2,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_txt_help_txt_2 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {389, 0, 581, 41},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    MLM_MMP_KEY_LM_ENTER,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_type_txt,
    &t_text_clr_info_txt_type_txt,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_icon_help_icon_3 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {581, 0, 624, 41},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    {0, 0, 0, 0},
    WGL_AS_LEFT_CENTER,
    &t_fg_img_info_mmp_lm_icon_help_icon_2,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_txt_help_txt_3 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {624, 0, 833, 41},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    MLM_MMP_KEY_AUD_OPT_PLAY,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_type_txt,
    &t_text_clr_info_txt_type_txt,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_fg_img_info_mmp_lm_icon_help_icon_4 = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_btm_exit_img,
        &h_g_mmp_btm_exit_img,
        &h_g_mmp_btm_exit_img,
        NULL,
        NULL,
        NULL
    }
};

static WDK_ICON_WGT_T t_wdk_param_mmp_lm_icon_help_icon_4 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {833, 0, 876, 41},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    {0, 0, 0, 0},
    WGL_AS_LEFT_CENTER,
    &t_fg_img_info_mmp_lm_icon_help_icon_4,
    0,
    0,
    0,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_lm_txt_help_txt_4 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {876, 0, 960, 41},
    {&t_bk_clr_info_frm_top_frm, &t_bk_img_info_mmp_lm_icon_type_icon},
    MLM_MMP_KEY_LM_EXIT,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_type_txt,
    &t_text_clr_info_txt_type_txt,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ITEM_T t_wdk_item_frm_top_frm_array[] = 
{
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_ICON_TYPE_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_icon_type_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_TXT_TYPE_TXT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_txt_type_txt,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_ICON_PATH_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_icon_path_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_TXT_PATH_TXT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_txt_path_txt,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_ICON_PAGE_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_icon_page_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_TXT_PAGE_TXT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_txt_page_txt,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_top_frm = 
{
    sizeof(t_wdk_item_frm_top_frm_array)/sizeof(t_wdk_item_frm_top_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_top_frm_array
};

static WDK_ITEM_T t_wdk_item_frm_mid_frm_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_FRM_PRW_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_frm_prw_frm,
        NULL
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_FRM_CTRL_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_frm_ctrl_frm,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_mid_frm = 
{
    sizeof(t_wdk_item_frm_mid_frm_array)/sizeof(t_wdk_item_frm_mid_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_mid_frm_array
};

static WDK_ITEM_T t_wdk_item_frm_btn_frm_array[] = 
{
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_ICON_HELP_ICON_1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_icon_help_icon_1,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_TXT_HELP_TXT_1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_txt_help_txt_1,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_ICON_HELP_ICON_2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_icon_help_icon_2,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_TXT_HELP_TXT_2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_txt_help_txt_2,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_ICON_HELP_ICON_3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_icon_help_icon_3,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_TXT_HELP_TXT_3,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_txt_help_txt_3,
        NULL
    },
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_LM_ICON_HELP_ICON_4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_icon_help_icon_4,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_LM_TXT_HELP_TXT_4,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_txt_help_txt_4,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_btn_frm = 
{
    sizeof(t_wdk_item_frm_btn_frm_array)/sizeof(t_wdk_item_frm_btn_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_btn_frm_array
};

static WDK_ITEM_T t_wdk_item_view_lm_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_FRM_TOP_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_frm_top_frm,
        (VOID *) &t_wdk_list_frm_top_frm
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_FRM_MID_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_frm_mid_frm,
        (VOID *) &t_wdk_list_frm_mid_frm
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_LM_FRM_BTN_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_lm_frm_btn_frm,
        (VOID *) &t_wdk_list_frm_btn_frm
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_lm = 
{
    sizeof(t_wdk_item_view_lm_array)/sizeof(t_wdk_item_view_lm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_lm_array
};

static HANDLE_T ah_wgt_handle_mmp_lm[WID_MMP_LM_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_mmp_lm[WID_MMP_LM_TOTAL_COUNT];


INT32 mmp_lm_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_mmp_lm, 0, 
             WID_MMP_LM_TOTAL_COUNT*sizeof(af_wgt_cb_mmp_lm[0]));
    return (WDKR_OK);
}

INT32 mmp_lm_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_MMP_LM_TOTAL_COUNT)
    {
        af_wgt_cb_mmp_lm[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }

    return (WDKR_FAILED);
}


INT32 mmp_lm_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_lm, 
                                 ah_wgt_handle_mmp_lm,
                                 af_wgt_cb_mmp_lm));
}

HANDLE_T mmp_lm_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_MMP_LM_TOTAL_COUNT)
    {
        return ah_wgt_handle_mmp_lm[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_lm_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_lm, 
                                      ah_wgt_handle_mmp_lm,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_lm_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_lm, 
                                         ah_wgt_handle_mmp_lm))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 mmp_lm_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_MMP_LM_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_lm, 
                                 *pt_mi,
                                 af_wgt_cb_mmp_lm));
}

HANDLE_T mmp_lm_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_mmp_lm = NULL;

    h_wgt_handle_mmp_lm = (VOID *)t_mi;

    if (NULL == h_wgt_handle_mmp_lm)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_MMP_LM_TOTAL_COUNT)
    {
        return h_wgt_handle_mmp_lm[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_lm_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_lm, 
                                      (HANDLE_T *)t_mi,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_lm_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_lm, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}



