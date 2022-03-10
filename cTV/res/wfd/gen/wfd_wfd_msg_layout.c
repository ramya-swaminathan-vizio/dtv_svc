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

#include "wfd_wfd_msg_layout.h"

static WDK_IMG_INFO_T t_bk_img_info_wfd_wfd_msg_frm_msg_box = 
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

static WDK_COLOR_INFO_T t_bk_clr_info_frm_msg_box = 
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

static WDK_FRM_WGT_T t_wdk_param_wfd_wfd_msg_frm_msg_box = 
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
    {&t_bk_clr_info_frm_msg_box, &t_bk_img_info_wfd_wfd_msg_frm_msg_box},
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_wfd_wfd_msg_txt_msg_1 = 
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

static WDK_FONT_INFO_T t_font_info_txt_msg_1 = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_wfd_mid,
        &t_g_wfd_mid
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_txt_msg_1 = 
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

static WDK_TXT_WGT_T t_wdk_param_wfd_wfd_msg_txt_msg_1 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 66, 360, 88},
    {&t_bk_clr_info_frm_msg_box, &t_bk_img_info_wfd_wfd_msg_txt_msg_1},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_msg_1,
    &t_text_clr_info_txt_msg_1,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_TXT_WGT_T t_wdk_param_wfd_wfd_msg_txt_msg_2 = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MAX_32,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {0, 92, 360, 118},
    {&t_bk_clr_info_frm_msg_box, &t_bk_img_info_wfd_wfd_msg_txt_msg_1},
    0,
    WGL_AS_CENTER_CENTER,
    &t_font_info_txt_msg_1,
    &t_text_clr_info_txt_msg_1,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_IMG_INFO_T t_bk_img_info_wfd_wfd_msg_btn_msg_cancel = 
{
    WGL_IMG_SET_STANDARD,
    {
        &h_g_wfd_unfocus_img,
        &h_g_wfd_unfocus_img,
        &h_g_wfd_focus_img,
        &h_g_wfd_focus_img,
        NULL,
        NULL
    }
};

static WDK_COLOR_INFO_T t_text_clr_info_btn_msg_cancel = 
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

static WDK_BTN_WGT_T t_wdk_param_wfd_wfd_msg_btn_msg_cancel = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {190, 137, 281, 173},
    {&t_bk_clr_info_frm_msg_box, &t_bk_img_info_wfd_wfd_msg_btn_msg_cancel},
    MLM_WFD_KEY_CANCEL,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_wfd_wfd_msg_txt_msg_1,
    {0, 0, 0, 0},
    &t_font_info_txt_msg_1,
    &t_text_clr_info_btn_msg_cancel,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_BTN_WGT_T t_wdk_param_wfd_wfd_msg_btn_msg_yes = 
{
    NULL_HANDLE,
    WGL_BORDER_NULL,
    NULL,
    0,
    255,
    TRUE,
    WGL_SW_NORMAL,
    NULL,
    {67, 137, 157, 173},
    {&t_bk_clr_info_frm_msg_box, &t_bk_img_info_wfd_wfd_msg_btn_msg_cancel},
    MLM_WFD_KEY_BTN_YES,
    WGL_AS_CENTER_CENTER,
    &t_bk_img_info_wfd_wfd_msg_txt_msg_1,
    {0, 0, 0, 0},
    &t_font_info_txt_msg_1,
    &t_text_clr_info_btn_msg_cancel,
    0,
    WGL_BTN_DO_IMG_FIRST,
    NULL
};

static WDK_FONT_INFO_T t_font_info_txt_msg_title = 
{
    WGL_FONT_SET_BASIC,
    {
        &t_g_wfd_big,
        &t_g_wfd_big
    }
};

static WDK_TXT_WGT_T t_wdk_param_wfd_wfd_msg_txt_msg_title = 
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
    {&t_bk_clr_info_frm_msg_box, &t_bk_img_info_wfd_wfd_msg_txt_msg_1},
    MLM_WFD_KEY_WFD_VIZIO_TITLE,
    WGL_AS_LEFT_CENTER,
    &t_font_info_txt_msg_title,
    &t_text_clr_info_txt_msg_1,
    {0, 0, 0, 0},
    0,
    1,
    NULL
};

static WDK_ITEM_T t_wdk_item_frm_msg_box_array[] = 
{
    {
        HT_WGL_WIDGET_TEXT,
        WID_WFD_WFD_MSG_TXT_MSG_1,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_msg_txt_msg_1,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_WFD_WFD_MSG_TXT_MSG_2,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_msg_txt_msg_2,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_WFD_WFD_MSG_BTN_MSG_CANCEL,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_msg_btn_msg_cancel,
        NULL
    },
    {
        HT_WGL_WIDGET_BUTTON,
        WID_WFD_WFD_MSG_BTN_MSG_YES,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_msg_btn_msg_yes,
        NULL
    },
    {
        HT_WGL_WIDGET_TEXT,
        WID_WFD_WFD_MSG_TXT_MSG_TITLE,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_msg_txt_msg_title,
        NULL
    }
};

static WDK_ITEM_LIST_T t_wdk_list_frm_msg_box = 
{
    sizeof(t_wdk_item_frm_msg_box_array)/sizeof(t_wdk_item_frm_msg_box_array[0]),
    (WDK_ITEM_T *) t_wdk_item_frm_msg_box_array
};

static WDK_ITEM_T t_wdk_item_view_wfd_msg_array[] = 
{
    {
        HT_WGL_WIDGET_FRAME,
        WID_WFD_WFD_MSG_FRM_MSG_BOX,
        WDK_FRM_OPT_BK_IMG,
        (VOID *) &t_wdk_param_wfd_wfd_msg_frm_msg_box,
        (VOID *) &t_wdk_list_frm_msg_box
    }
};

static WDK_ITEM_LIST_T t_wdk_list_view_wfd_msg = 
{
    sizeof(t_wdk_item_view_wfd_msg_array)/sizeof(t_wdk_item_view_wfd_msg_array[0]),
    (WDK_ITEM_T *) t_wdk_item_view_wfd_msg_array
};

static HANDLE_T ah_wgt_handle_wfd_wfd_msg[WID_WFD_WFD_MSG_TOTAL_COUNT];
static wgl_widget_proc_fct af_wgt_cb_wfd_wfd_msg[WID_WFD_WFD_MSG_TOTAL_COUNT];


INT32 wfd_wfd_msg_clr_wgt_cb(VOID)
{
    c_memset(af_wgt_cb_wfd_wfd_msg, 0, 
             WID_WFD_WFD_MSG_TOTAL_COUNT*sizeof(af_wgt_cb_wfd_wfd_msg[0]));
    return (WDKR_OK);
}

INT32 wfd_wfd_msg_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct pf_cb)
{
    if (e_widget_id < WID_WFD_WFD_MSG_TOTAL_COUNT)
    {
        af_wgt_cb_wfd_wfd_msg[e_widget_id] = pf_cb;
        return (WDKR_OK);
    }

    return (WDKR_FAILED);
}


INT32 wfd_wfd_msg_create_ui(HANDLE_T h_container)
{
    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_wfd_msg, 
                                 ah_wgt_handle_wfd_wfd_msg,
                                 af_wgt_cb_wfd_wfd_msg));
}

HANDLE_T wfd_wfd_msg_get_wgt_hdl(UINT32 e_widget_id)
{
    if (e_widget_id < WID_WFD_WFD_MSG_TOTAL_COUNT)
    {
        return ah_wgt_handle_wfd_wfd_msg[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 wfd_wfd_msg_update_text(UINT16 ui2_lang)
{
    return (a_wdk_widgets_update_text(&t_wdk_list_view_wfd_msg, 
                                      ah_wgt_handle_wfd_wfd_msg,
                                      mlm_wfd_get_text,
                                      ui2_lang));
}

INT32 wfd_wfd_msg_destroy_ui(VOID)
{
    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_wfd_msg, 
                                         ah_wgt_handle_wfd_wfd_msg))
    {
        return (WDKR_FAILED);
    }

    return (WDKR_OK);
}


/* Multi-Instance */
INT32 wfd_wfd_msg_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *pt_mi)
{
    *pt_mi = (WDK_UI_MI_T *)c_mem_alloc(sizeof(HANDLE_T)*WID_WFD_WFD_MSG_TOTAL_COUNT);
    if (NULL == *pt_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_create_widgets(h_container, 
                                 &t_wdk_list_view_wfd_msg, 
                                 *pt_mi,
                                 af_wgt_cb_wfd_wfd_msg));
}

HANDLE_T wfd_wfd_msg_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T t_mi)
{
    HANDLE_T *h_wgt_handle_wfd_wfd_msg = NULL;

    h_wgt_handle_wfd_wfd_msg = (VOID *)t_mi;

    if (NULL == h_wgt_handle_wfd_wfd_msg)
    {
        return (NULL_HANDLE);
    }

    if (e_widget_id < WID_WFD_WFD_MSG_TOTAL_COUNT)
    {
        return h_wgt_handle_wfd_wfd_msg[e_widget_id];
    }

    return (NULL_HANDLE);
}

INT32 wfd_wfd_msg_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    return (a_wdk_widgets_update_text(&t_wdk_list_view_wfd_msg, 
                                      (HANDLE_T *)t_mi,
                                      mlm_wfd_get_text,
                                      ui2_lang));
}

INT32 wfd_wfd_msg_destroy_ui_mi(WDK_UI_MI_T t_mi)
{
    if (NULL == t_mi)
    {
        return (WDKR_FAILED);
    }

    if (WDKR_OK != a_wdk_destory_widgets(&t_wdk_list_view_wfd_msg, t_mi))
    {
        return (WDKR_FAILED);
    }

    c_mem_free(t_mi);
    return (WDKR_OK);
}



