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

#include "res/wfd/gen/wfd_gen_img.h"
#include "res/wfd/gen/wfd_gen_clr.h"
#include "res/wfd/gen/wfd_mlm.h"
#include "res/wfd/gen/wfd_gen_font_info.h"

#include "wfd_wfd_connect_layout.h"

static WDK_IMG_INFO_T t_bk_img_info_wfd_wfd_connect_frm_connect_main = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_wfd_bg_img,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_bk_clr_info_frm_connect_main = 
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

static WDK_FRM_WGT_T t_wdk_param_wfd_wfd_connect_frm_connect_main = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_HIDE_RECURSIVE,
    NULL,
    {208, 66, 742, 334},
    {&t_bk_clr_info_frm_connect_main, &t_bk_img_info_wfd_wfd_connect_frm_connect_main},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_wfd_wfd_connect_btn_pbc = 
{
    WGL_IMG_SET_STANDARD,
    {
        &h_g_wfd_button_img,
        &h_g_wfd_button_img,
        &h_g_wfd_button_hl_img,
        NULL,
        NULL,
        NULL
    }
};

static WDK_IMG_INFO_T t_fg_img_info_wfd_wfd_connect_btn_pbc = 
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

static WDK_FONT_INFO_T t_font_info_btn_pbc = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_wfd_mid,
        &t_g_wfd_mid
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_btn_pbc = 
{
    WGL_COLOR_SET_STANDARD,
    {
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        NULL,
        NULL,
        NULL
    }
};

static WDK_BTN_WGT_T t_wdk_param_wfd_wfd_connect_btn_pbc = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {149, 75, 382, 111},
    {&t_bk_clr_info_frm_connect_main, &t_bk_img_info_wfd_wfd_connect_btn_pbc},
    MLM_WFD_KEY_BTN_PBC,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_wfd_wfd_connect_btn_pbc,
    {0, 0, 0, 0},
    &t_font_info_btn_pbc,
    &t_text_clr_info_btn_pbc,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_FONT_INFO_T t_font_info_txt_conn_title = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_wfd_big,
        &t_g_wfd_big
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_conn_title = 
{
    WGL_COLOR_SET_BASIC,
    {
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        NULL,
        NULL,
        NULL
    }
};

static WDK_TXT_WGT_T t_wdk_param_wfd_wfd_connect_txt_conn_title = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 6, 534, 38},
    {&t_bk_clr_info_frm_connect_main, &t_fg_img_info_wfd_wfd_connect_btn_pbc},
    MLM_WFD_KEY_SELECT_CONNECTION_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_conn_title,
    &t_text_clr_info_txt_conn_title,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_wfd_wfd_connect_btn_show_pin = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {148, 133, 381, 169},
    {&t_bk_clr_info_frm_connect_main, &t_bk_img_info_wfd_wfd_connect_btn_pbc},
    MLM_WFD_KEY_BTN_SHOW_PIN,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_wfd_wfd_connect_btn_pbc,
    {0, 0, 0, 0},
    &t_font_info_btn_pbc,
    &t_text_clr_info_btn_pbc,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_wfd_wfd_connect_btn_enter_pin = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {148, 198, 381, 234},
    {&t_bk_clr_info_frm_connect_main, &t_bk_img_info_wfd_wfd_connect_btn_pbc},
    MLM_WFD_KEY_BTN_ENTER_PIN,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_wfd_wfd_connect_btn_pbc,
    {0, 0, 0, 0},
    &t_font_info_btn_pbc,
    &t_text_clr_info_btn_pbc,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_wfd_wfd_connect_frm_req_bar = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_wfd_background_img,
        &h_g_wfd_background_img,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_wfd_wfd_connect_frm_req_bar = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 416, 720},
    {&t_bk_clr_info_frm_connect_main, &t_bk_img_info_wfd_wfd_connect_frm_req_bar},
    NULL
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_req_name = 
{
    WGL_COLOR_SET_BASIC,
    {
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        NULL,
        NULL
    }
};

static WDK_TXT_WGT_T t_wdk_param_wfd_wfd_connect_txt_req_name = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {98, 51, 314, 73},
    {&t_bk_clr_info_frm_connect_main, &t_fg_img_info_wfd_wfd_connect_btn_pbc},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_btn_pbc,
    &t_text_clr_info_txt_req_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_wfd_wfd_connect_txt_req_cont = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {67, 76, 347, 102},
    {&t_bk_clr_info_frm_connect_main, &t_fg_img_info_wfd_wfd_connect_btn_pbc},
    MLM_WFD_KEY_REQ_CONNECT,
    WGL_AS_CENTER_CENTER,
    &t_font_info_btn_pbc,
    &t_text_clr_info_txt_req_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_wfd_wfd_connect_btn_req_exit = 
{
    WGL_IMG_SET_STANDARD,
    {
        &h_g_wfd_unfocus_img,
        &h_g_wfd_unfocus_img,
        &h_g_wfd_focus_img,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_btn_req_exit = 
{
    WGL_COLOR_SET_STANDARD,
    {
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white
    }
};

static WDK_BTN_WGT_T t_wdk_param_wfd_wfd_connect_btn_req_exit = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {241, 111, 330, 144},
    {&t_bk_clr_info_frm_connect_main, &t_bk_img_info_wfd_wfd_connect_btn_req_exit},
    MLM_WFD_KEY_BTN_EXIT,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_wfd_wfd_connect_btn_pbc,
    {0, 0, 0, 0},
    &t_font_info_btn_pbc,
    &t_text_clr_info_btn_req_exit,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_wfd_wfd_connect_btn_req_yes = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {88, 111, 169, 145},
    {&t_bk_clr_info_frm_connect_main, &t_bk_img_info_wfd_wfd_connect_btn_req_exit},
    MLM_WFD_KEY_BTN_YES,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_wfd_wfd_connect_btn_pbc,
    {0, 0, 0, 0},
    &t_font_info_btn_pbc,
    &t_text_clr_info_btn_req_exit,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_wfd_wfd_connect_txt_req_title = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {23, 11, 323, 43},
    {&t_bk_clr_info_frm_connect_main, &t_fg_img_info_wfd_wfd_connect_btn_pbc},
    MLM_WFD_KEY_WFD_VIZIO_TITLE,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_conn_title,
    &t_text_clr_info_txt_req_name,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_wfd_wfd_connect_frm_pin_win = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {344, 118, 631, 315},
    {&t_bk_clr_info_frm_connect_main, &t_bk_img_info_wfd_wfd_connect_frm_connect_main},
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_wfd_wfd_connect_txt_pin_title = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {81, 9, 215, 35},
    {&t_bk_clr_info_frm_connect_main, &t_fg_img_info_wfd_wfd_connect_btn_pbc},
    MLM_WFD_KEY_SHOW_PIN_TITLE,
    WGL_AS_LEFT_TOP,
    &t_font_info_txt_conn_title,
    &t_text_clr_info_txt_conn_title,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_wfd_wfd_connect_btn_pin_btn = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {40, 138, 133, 174},
    {&t_bk_clr_info_frm_connect_main, &t_bk_img_info_wfd_wfd_connect_btn_pbc},
    MLM_WFD_KEY_ENTER,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_wfd_wfd_connect_btn_pbc,
    {0, 0, 0, 0},
    &t_font_info_btn_pbc,
    &t_text_clr_info_btn_pbc,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_wfd_wfd_connect_eb_pin_box = 
{
    WGL_IMG_SET_EXTEND,
    {
        &h_g_wfd_bf_mid_img,
        &h_g_wfd_bf_mid_img,
        &h_g_wfd_bf_mid_img,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_cursor_clr_info_eb_pin_box = 
{
    WGL_COLOR_SET_EXTEND,
    {
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white
    }
};

static WDK_EB_WGT_T t_wdk_param_wfd_wfd_connect_eb_pin_box = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_EB_RECYCLE|WGL_STL_EB_MAX_CHAR_16,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {19, 75, 257, 108},
    {&t_bk_clr_info_frm_connect_main, &t_bk_img_info_wfd_wfd_connect_eb_pin_box},
    {0, 0, 0, 0},
    MLM_WFD_KEY_INPUT_STR,
    WGL_AS_LEFT_CENTER,
    &t_font_info_btn_pbc,
    &t_text_clr_info_btn_req_exit,
    &t_cursor_clr_info_eb_pin_box,
    WGL_EB_MODE_REPLACE,
    8,
    0,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_wfd_wfd_connect_btn_pin_btn_1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {169, 138, 252, 174},
    {&t_bk_clr_info_frm_connect_main, &t_bk_img_info_wfd_wfd_connect_btn_pbc},
    MLM_WFD_KEY_CANCEL,
    WGL_AS_CENTER_CENTER,
    &t_fg_img_info_wfd_wfd_connect_btn_pbc,
    {0, 0, 0, 0},
    &t_font_info_btn_pbc,
    &t_text_clr_info_btn_pbc,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_ITEM_T t_wdk_item_frm_connect_main_array[] = 
{
    {
        HT_WGL_WIDGET_BUTTON,
        WID_WFD_WFD_CONNECT_BTN_PBC,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_btn_pbc,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_WFD_WFD_CONNECT_TXT_CONN_TITLE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_txt_conn_title,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_WFD_WFD_CONNECT_BTN_SHOW_PIN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_btn_show_pin,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_WFD_WFD_CONNECT_BTN_ENTER_PIN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_btn_enter_pin,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_connect_main = 
{
    sizeof(t_wdk_item_frm_connect_main_array)/sizeof(t_wdk_item_frm_connect_main_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_connect_main_array
};

static WDK_ITEM_T t_wdk_item_frm_req_bar_array[] = 
{
    {
        HT_WGL_WIDGET_TEXT,
        WID_WFD_WFD_CONNECT_TXT_REQ_NAME,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_txt_req_name,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_WFD_WFD_CONNECT_TXT_REQ_CONT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_txt_req_cont,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_WFD_WFD_CONNECT_BTN_REQ_EXIT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_btn_req_exit,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_WFD_WFD_CONNECT_BTN_REQ_YES,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_btn_req_yes,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_WFD_WFD_CONNECT_TXT_REQ_TITLE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_txt_req_title,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_req_bar = 
{
    sizeof(t_wdk_item_frm_req_bar_array)/sizeof(t_wdk_item_frm_req_bar_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_req_bar_array
};

static WDK_ITEM_T t_wdk_item_frm_pin_win_array[] = 
{
    {
        HT_WGL_WIDGET_TEXT,
        WID_WFD_WFD_CONNECT_TXT_PIN_TITLE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_txt_pin_title,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_WFD_WFD_CONNECT_BTN_PIN_BTN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_btn_pin_btn,
        NULL
    },
    {
        HT_WGL_WIDGET_EDIT_BOX,
        WID_WFD_WFD_CONNECT_EDIT_PIN_BOX,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_eb_pin_box,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_WFD_WFD_CONNECT_BTN_PIN_BTN_1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_btn_pin_btn_1,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_pin_win = 
{
    sizeof(t_wdk_item_frm_pin_win_array)/sizeof(t_wdk_item_frm_pin_win_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_pin_win_array
};

static WDK_ITEM_T t_wdk_item_view_wfd_connect_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_WFD_WFD_CONNECT_FRM_CONNECT_MAIN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_frm_connect_main,
        (VOID *) &t_wdk_list_frm_connect_main
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_WFD_WFD_CONNECT_FRM_REQ_BAR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_frm_req_bar,
        (VOID *) &t_wdk_list_frm_req_bar
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_WFD_WFD_CONNECT_FRM_PIN_WIN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_connect_frm_pin_win,
        (VOID *) &t_wdk_list_frm_pin_win
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_wfd_connect = 
{
    sizeof(t_wdk_item_view_wfd_connect_array)/sizeof(t_wdk_item_view_wfd_connect_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_wfd_connect_array
};

static HANDLE_T ah_wgt_handle_wfd_wfd_connect[WID_WFD_WFD_CONNECT_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_wfd_wfd_connect[WID_WFD_WFD_CONNECT_TOTAL_COUNT];


INT32 wfd_wfd_connect_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_wfd_wfd_connect, 0, 
             WID_WFD_WFD_CONNECT_TOTAL_COUNT*sizeof(af_wgt_cb_wfd_wfd_connect[0]));
    return (WDKR_OK);
}

INT32 wfd_wfd_connect_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_WFD_WFD_CONNECT_TOTAL_COUNT)
    {
        af_wgt_cb_wfd_wfd_connect[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }

    return (WDKR_FAILED);
}


INT32 wfd_wfd_connect_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_wfd_connect, 
                                 ah_wgt_handle_wfd_wfd_connect,
                                 af_wgt_cb_wfd_wfd_connect));
}

HANDLE_T wfd_wfd_connect_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_WFD_WFD_CONNECT_TOTAL_COUNT)
    {
        return ah_wgt_handle_wfd_wfd_connect[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 wfd_wfd_connect_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_wfd_connect, 
                                      ah_wgt_handle_wfd_wfd_connect,
                                      mlm_wfd_get_text,
                                      ui2_lang));
}

INT32 wfd_wfd_connect_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_wfd_connect, 
                                         ah_wgt_handle_wfd_wfd_connect))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 wfd_wfd_connect_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_WFD_WFD_CONNECT_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_wfd_connect, 
                                 *pt_mi,
                                 af_wgt_cb_wfd_wfd_connect));
}

HANDLE_T wfd_wfd_connect_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_wfd_wfd_connect = NULL;

    h_wgt_handle_wfd_wfd_connect = (VOID *)t_mi;

    if (NULL == h_wgt_handle_wfd_wfd_connect)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_WFD_WFD_CONNECT_TOTAL_COUNT)
    {
        return h_wgt_handle_wfd_wfd_connect[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 wfd_wfd_connect_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_wfd_connect, 
                                      (HANDLE_T *)t_mi,
                                      mlm_wfd_get_text,
                                      ui2_lang));
}

INT32 wfd_wfd_connect_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_wfd_connect, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}



