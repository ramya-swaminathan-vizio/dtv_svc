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

#include "wfd_wfd_play_layout.h"

static WDK_IMG_INFO_T t_bk_img_info_wfd_wfd_play_frm_play_main = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_wfd_unfocus_img,
        &h_g_wfd_unfocus_img,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_bk_clr_info_frm_play_main = 
{
    WGL_COLOR_SET_BASIC,
    {
        &t_g_wfd_dark,
        &t_g_wfd_dark,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_FRM_WGT_T t_wdk_param_wfd_wfd_play_frm_play_main = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {170, 645, 1087, 696},
    {&t_bk_clr_info_frm_play_main, &t_bk_img_info_wfd_wfd_play_frm_play_main},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_wfd_wfd_play_icon_vol_icon = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_wfd_icon_vol_img,
        &h_g_wfd_stop_img,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_bk_clr_info_icon_vol_icon = 
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

static WDK_IMG_INFO_T t_fg_img_info_wfd_wfd_play_icon_vol_icon = 
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

static WDK_ICON_WGT_T t_wdk_param_wfd_wfd_play_icon_vol_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {57, 16, 81, 37},
    {&t_bk_clr_info_icon_vol_icon, &t_bk_img_info_wfd_wfd_play_icon_vol_icon},
    {0, 0, 0, 0},
    WGL_AS_LEFT_TOP,
    &t_fg_img_info_wfd_wfd_play_icon_vol_icon,
    0,
    0,
    0,
    NULL
};

static WDK_FONT_INFO_T t_font_info_pb_vol_bar = 
{
    WGL_FONT_SET_BASIC,
    {
        NULL,
        NULL
    }
};

static WDK_IMG_INFO_T t_pb_body_bk_img_info_wfd_wfd_play_pb_vol_bar = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_wfd_bg_top_img,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_IMG_INFO_T t_pb_level_1_img_info_wfd_wfd_play_pb_vol_bar = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_wfd_pb_vol_img,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};

static WDK_PB_WGT_T t_wdk_param_wfd_wfd_play_pb_vol_bar = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {96, 25, 195, 29},
    {&t_bk_clr_info_icon_vol_icon, &t_fg_img_info_wfd_wfd_play_icon_vol_icon},
    WGL_PG_DM_PERCENT,
    0,
    100,
    80,
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
    20,
    20,
    {
        0,
        0,
        0,
        0
    },
    {
        0,
        0,
        0,
        0
    },
    &t_font_info_pb_vol_bar,
    &t_bk_clr_info_icon_vol_icon,
    {&t_bk_clr_info_icon_vol_icon, &t_pb_body_bk_img_info_wfd_wfd_play_pb_vol_bar},
    {
        {&t_bk_clr_info_icon_vol_icon, &t_pb_level_1_img_info_wfd_wfd_play_pb_vol_bar},
        {&t_bk_clr_info_icon_vol_icon, &t_fg_img_info_wfd_wfd_play_icon_vol_icon},
        {&t_bk_clr_info_icon_vol_icon, &t_fg_img_info_wfd_wfd_play_icon_vol_icon},
        {&t_bk_clr_info_icon_vol_icon, &t_fg_img_info_wfd_wfd_play_icon_vol_icon},
        {&t_bk_clr_info_icon_vol_icon, &t_fg_img_info_wfd_wfd_play_icon_vol_icon}
    },
    NULL
};

static WDK_FONT_INFO_T t_font_info_lb_pl_sta_show = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_wfd_mid,
        &t_g_wfd_mid
    }
};

static WDK_LB_IMG_SET_T t_bk_lbimg_lb_pl_sta_show = 
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

static WDK_LB_COLOR_SET_T t_bk_lbclr_lb_pl_sta_show = 
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static WDK_LB_HLT_ELEM_EFFECT_T t_hlt_elem_effect_lb_pl_sta_show = 
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

static WGL_LB_COL_INIT_T t_lbcolumn_init_lb_pl_sta_show_array[] = 
{
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        100,
        31
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        150,
        31
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        20,
        31
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        200,
        31
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        70,
        31
    },
    {
        LB_COL_TYPE_TEXT,
        WGL_AS_LEFT_CENTER,
        100,
        31
    }
};

static WGL_INSET_T t_lbcol_inset_lb_pl_sta_show_array[] = 
{
    {2, 2, 2, 2},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

static WDK_LB_FONT_SET_T t_column_lbfont_lb_pl_sta_show_array[] = 
{
    {
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid
    },
    {
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid
    },
    {
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid
    },
    {
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid
    },
    {
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid
    },
    {
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid,
        &t_g_wfd_mid
    }
};

static WDK_LB_COLOR_SET_T t_col_text_lbclr_lb_pl_sta_show_array[] = 
{
    {
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white
    },
    {
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        NULL,
        NULL
    },
    {
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        NULL,
        NULL,
        NULL
    },
    {
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        NULL,
        NULL,
        NULL
    },
    {
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        NULL,
        NULL,
        NULL
    },
    {
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        &t_g_wfd_white,
        NULL,
        NULL
    }
};

static WDK_LB_COLOR_SET_T t_col_bk_lbclr_lb_pl_sta_show_array[] = 
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

static WDK_LB_ITEM_INFO_T t_lbitem_lb_pl_sta_show_array[] = 
{
    {
        LB_COL_TYPE_TEXT,
        MLM_WFD_KEY_CONNECT_STR,
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
        MLM_WFD_KEY_IP_STR,
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
        MLM_WFD_KEY_PORT_STR,
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

static WDK_LB_FONT_SET_T t_item_lbfont_lb_pl_sta_show_array[] = 
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
    }
};

static WDK_LB_IMG_SET_T t_item_set_lbimg_lb_pl_sta_show_array[] = 
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

static WDK_LB_COLOR_SET_T t_item_text_lbclr_lb_pl_sta_show_array[] = 
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

static WDK_LB_COLOR_SET_T t_item_bk_lbclr_lb_pl_sta_show_array[] = 
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

static WDK_LB_WGT_T t_wdk_param_wfd_wfd_play_lb_pl_sta_show = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_LB_FIXED_ELEM_NUM,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {250, 12, 905, 51},
    {&t_bk_clr_info_icon_vol_icon, &t_fg_img_info_wfd_wfd_play_icon_vol_icon},
    {5, 5, 5, 5},
    &t_font_info_lb_pl_sta_show,
    1,
    1,
    25,
    0,
    {2, 2, 2, 2},
    {&t_bk_lbclr_lb_pl_sta_show, &t_bk_lbimg_lb_pl_sta_show},
    &t_hlt_elem_effect_lb_pl_sta_show,
    1,
    6,
    t_lbcolumn_init_lb_pl_sta_show_array,
    t_lbcol_inset_lb_pl_sta_show_array,
    t_column_lbfont_lb_pl_sta_show_array,
    t_col_text_lbclr_lb_pl_sta_show_array,
    t_col_bk_lbclr_lb_pl_sta_show_array,
    t_lbitem_lb_pl_sta_show_array,
    t_item_lbfont_lb_pl_sta_show_array,
    t_item_set_lbimg_lb_pl_sta_show_array,
    t_item_text_lbclr_lb_pl_sta_show_array,
    t_item_bk_lbclr_lb_pl_sta_show_array,
    NULL
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_vol_txt = 
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

static WDK_TXT_WGT_T t_wdk_param_wfd_wfd_play_txt_vol_txt = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_HIDE,
    NULL,
    {106, 16, 238, 40},
    {&t_bk_clr_info_icon_vol_icon, &t_fg_img_info_wfd_wfd_play_icon_vol_icon},
    MLM_WFD_KEY_VOLUME_DOWN,
    WGL_AS_LEFT_TOP,
    &t_font_info_lb_pl_sta_show,
    &t_text_clr_info_txt_vol_txt,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ITEM_T t_wdk_item_frm_play_main_array[] = 
{
    {
        HT_WGL_WIDGET_ICON,
        WID_WFD_WFD_PLAY_ICON_VOL_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_play_icon_vol_icon,
        NULL
    },
    {
        HT_WGL_WIDGET_PROGRESS_BAR,
        WID_WFD_WFD_PLAY_PB_VOL_BAR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_play_pb_vol_bar,
        NULL
    },
    {
        HT_WGL_WIDGET_LIST_BOX,
        WID_WFD_WFD_PLAY_LB_PL_STA_SHOW,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_play_lb_pl_sta_show,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_WFD_WFD_PLAY_TXT_VOL_TXT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_play_txt_vol_txt,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_play_main = 
{
    sizeof(t_wdk_item_frm_play_main_array)/sizeof(t_wdk_item_frm_play_main_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_play_main_array
};

static WDK_ITEM_T t_wdk_item_view_wfd_play_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_WFD_WFD_PLAY_FRM_PLAY_MAIN,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_play_frm_play_main,
        (VOID *) &t_wdk_list_frm_play_main
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_wfd_play = 
{
    sizeof(t_wdk_item_view_wfd_play_array)/sizeof(t_wdk_item_view_wfd_play_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_wfd_play_array
};

static HANDLE_T ah_wgt_handle_wfd_wfd_play[WID_WFD_WFD_PLAY_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_wfd_wfd_play[WID_WFD_WFD_PLAY_TOTAL_COUNT];


INT32 wfd_wfd_play_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_wfd_wfd_play, 0, 
             WID_WFD_WFD_PLAY_TOTAL_COUNT*sizeof(af_wgt_cb_wfd_wfd_play[0]));
    return (WDKR_OK);
}

INT32 wfd_wfd_play_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_WFD_WFD_PLAY_TOTAL_COUNT)
    {
        af_wgt_cb_wfd_wfd_play[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }

    return (WDKR_FAILED);
}


INT32 wfd_wfd_play_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_wfd_play, 
                                 ah_wgt_handle_wfd_wfd_play,
                                 af_wgt_cb_wfd_wfd_play));
}

HANDLE_T wfd_wfd_play_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_WFD_WFD_PLAY_TOTAL_COUNT)
    {
        return ah_wgt_handle_wfd_wfd_play[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 wfd_wfd_play_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_wfd_play, 
                                      ah_wgt_handle_wfd_wfd_play,
                                      mlm_wfd_get_text,
                                      ui2_lang));
}

INT32 wfd_wfd_play_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_wfd_play, 
                                         ah_wgt_handle_wfd_wfd_play))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 wfd_wfd_play_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_WFD_WFD_PLAY_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_wfd_play, 
                                 *pt_mi,
                                 af_wgt_cb_wfd_wfd_play));
}

HANDLE_T wfd_wfd_play_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_wfd_wfd_play = NULL;

    h_wgt_handle_wfd_wfd_play = (VOID *)t_mi;

    if (NULL == h_wgt_handle_wfd_wfd_play)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_WFD_WFD_PLAY_TOTAL_COUNT)
    {
        return h_wgt_handle_wfd_wfd_play[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 wfd_wfd_play_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_wfd_play, 
                                      (HANDLE_T *)t_mi,
                                      mlm_wfd_get_text,
                                      ui2_lang));
}

INT32 wfd_wfd_play_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_wfd_play, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}



