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

#include "mmp_vp_tb_layout.h"

static WDK_IMG_INFO_T t_bk_img_info_mmp_vp_tb_frm_main_frm = 
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

static WDK_FRM_WGT_T t_wdk_param_mmp_vp_tb_frm_main_frm = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    0,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 0, 1920, 1080},
    {&t_bk_clr_info_frm_main_frm, &t_bk_img_info_mmp_vp_tb_frm_main_frm},
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

static WDK_FRM_WGT_T t_wdk_param_mmp_vp_tb_frm_top_bar = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI,
    0,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {559, 820, 1360, 880},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_vp_tb_frm_main_frm},
    NULL
};

static WDK_ICON_WGT_T t_wdk_param_mmp_vp_tb_icon_play_icon = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {319, 0, 439, 60},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_vp_tb_frm_main_frm},
    {0, 0, 0, 0},
    WGL_AS_CENTER_BOTTOM,
    &t_bk_img_info_mmp_vp_tb_frm_main_frm,
    0,
    0,
    0,
    NULL
};

static WDK_FRM_WGT_T t_wdk_param_mmp_vp_tb_frm_player_bar = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {199, 880, 1720, 940},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_vp_tb_frm_main_frm},
    NULL
};

static WDK_FONT_INFO_T t_font_info_txt_elapse_time_hint = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_mmp_font_small,
        &t_g_mmp_font_small
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_elapse_time_hint = 
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

static WDK_TXT_WGT_T t_wdk_param_mmp_vp_tb_txt_elapse_time_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {139, 0, 259, 40},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_vp_tb_frm_main_frm},
    0,
    WGL_AS_RIGHT_CENTER,
    &t_font_info_txt_elapse_time_hint,
    &t_text_clr_info_txt_elapse_time_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_FONT_INFO_T t_font_info_pb_progress_bar = 
{
    WGL_FONT_SET_BASIC,
    {
        NULL,
        NULL
    }
};

static WDK_IMG_INFO_T t_pb_body_bk_img_info_mmp_vp_tb_pb_progress_bar = 
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

static WDK_IMG_INFO_T t_pb_level_1_img_info_mmp_vp_tb_pb_progress_bar = 
{
    WGL_IMG_SET_BASIC,
    {
        &h_g_mmp_track_time_bar_fill,
        &h_g_mmp_track_time_bar_fill,
        &h_g_mmp_track_time_bar_fill,
        NULL,
        NULL,
        NULL
    }
};

static WDK_PB_WGT_T t_wdk_param_mmp_vp_tb_pb_progress_bar = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {280, 4, 1240, 32},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_vp_tb_frm_main_frm},
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
    &t_font_info_pb_progress_bar,
    &t_bk_clr_info_frm_top_bar,
    {&t_bk_clr_info_frm_top_bar, &t_pb_body_bk_img_info_mmp_vp_tb_pb_progress_bar},
    {
        {&t_bk_clr_info_frm_top_bar, &t_pb_level_1_img_info_mmp_vp_tb_pb_progress_bar},
        {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_vp_tb_frm_main_frm},
        {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_vp_tb_frm_main_frm},
        {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_vp_tb_frm_main_frm},
        {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_vp_tb_frm_main_frm}
    },
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_mmp_vp_tb_txt_remain_time_hint = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {1260, 0, 1380, 45},
    {&t_bk_clr_info_frm_top_bar, &t_bk_img_info_mmp_vp_tb_frm_main_frm},
    0,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_elapse_time_hint,
    &t_text_clr_info_txt_elapse_time_hint,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ITEM_T t_wdk_item_frm_top_bar_array[] = 
{
    {
        HT_WGL_WIDGET_ICON,
        WID_MMP_VP_TB_ICON_PLAY_ICON,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_vp_tb_icon_play_icon,
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
        WID_MMP_VP_TB_TXT_ELAPSE_TIME_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_vp_tb_txt_elapse_time_hint,
        NULL
    },
    {
        HT_WGL_WIDGET_PROGRESS_BAR,
        WID_MMP_VP_TB_PB_PROGRESS_BAR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_vp_tb_pb_progress_bar,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_MMP_VP_TB_TXT_REMAIN_TIME_HINT,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_vp_tb_txt_remain_time_hint,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_player_bar = 
{
    sizeof(t_wdk_item_frm_player_bar_array)/sizeof(t_wdk_item_frm_player_bar_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_player_bar_array
};

static WDK_ITEM_T t_wdk_item_frm_main_frm_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_VP_TB_FRM_TOP_BAR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_vp_tb_frm_top_bar,
        (VOID *) &t_wdk_list_frm_top_bar
    },
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_VP_TB_FRM_PLAYER_BAR,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_vp_tb_frm_player_bar,
        (VOID *) &t_wdk_list_frm_player_bar
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_main_frm = 
{
    sizeof(t_wdk_item_frm_main_frm_array)/sizeof(t_wdk_item_frm_main_frm_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_main_frm_array
};

static WDK_ITEM_T t_wdk_item_view_vp_tb_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_MMP_VP_TB_FRM_MAIN_FRM,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_mmp_vp_tb_frm_main_frm,
        (VOID *) &t_wdk_list_frm_main_frm
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_vp_tb = 
{
    sizeof(t_wdk_item_view_vp_tb_array)/sizeof(t_wdk_item_view_vp_tb_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_vp_tb_array
};

static HANDLE_T ah_wgt_handle_mmp_vp_tb[WID_MMP_VP_TB_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_mmp_vp_tb[WID_MMP_VP_TB_TOTAL_COUNT];


INT32 mmp_vp_tb_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_mmp_vp_tb, 0, 
             WID_MMP_VP_TB_TOTAL_COUNT*sizeof(af_wgt_cb_mmp_vp_tb[0]));
    return (WDKR_OK);
}

INT32 mmp_vp_tb_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_MMP_VP_TB_TOTAL_COUNT)
    {
        af_wgt_cb_mmp_vp_tb[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }

    return (WDKR_FAILED);
}


INT32 mmp_vp_tb_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_vp_tb, 
                                 ah_wgt_handle_mmp_vp_tb,
                                 af_wgt_cb_mmp_vp_tb));
}

HANDLE_T mmp_vp_tb_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_MMP_VP_TB_TOTAL_COUNT)
    {
        return ah_wgt_handle_mmp_vp_tb[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_vp_tb_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_vp_tb, 
                                      ah_wgt_handle_mmp_vp_tb,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_vp_tb_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_vp_tb, 
                                         ah_wgt_handle_mmp_vp_tb))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 mmp_vp_tb_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_MMP_VP_TB_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_vp_tb, 
                                 *pt_mi,
                                 af_wgt_cb_mmp_vp_tb));
}

HANDLE_T mmp_vp_tb_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_mmp_vp_tb = NULL;

    h_wgt_handle_mmp_vp_tb = (VOID *)t_mi;

    if (NULL == h_wgt_handle_mmp_vp_tb)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_MMP_VP_TB_TOTAL_COUNT)
    {
        return h_wgt_handle_mmp_vp_tb[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 mmp_vp_tb_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_vp_tb, 
                                      (HANDLE_T *)t_mi,
                                      mlm_mmp_get_text,
                                      ui2_lang));
}

INT32 mmp_vp_tb_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_vp_tb, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}



