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
/*-----------------------------------------------------------------------------
 * $RCSfile: menu_page_adv_scan_rng.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/22 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 223730d1bdc36ed27cb26dea5de9232d $
 *
 * Description:
 *      This scan includes both ATV channel scan and DTV channel scan.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
//#include "u_sb_atsc_eng.h"
//#include "u_sb_cqam_eng.h"
//#include "u_sb_ntsc_eng.h"
#include "u_cli.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu_page_mobile_device_setting.h"
//#include "menu_device.h"
//#include "menu2/menu_common/menu_page_animation.h"

//#include "wizard/a_wzd.h"
#include "res/app_util/config/a_cfg_custom.h"
//#include "res/app_util/config/acfg_cust_odm.h"

#include "res/menu2/menu_custom.h"
#include "res/menu2/menu_custom_dialog.h"
#include "res/app_util/dev_db/a_dev_db_custom.h"

#include "rest/a_rest_api.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#ifdef LINUX_TURNKEY_SOLUTION
#include <stdio.h>
#endif

#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    defines, typedefs, enums
 ----------------------------------------------------------------------------*/

typedef struct _MENU_MOBILE_DEVICE_PAGE_DATA_T
{
    HANDLE_T     h_cnt_frm;
    HANDLE_T     h_device_list;
    HANDLE_T     h_last_focus;

    UINT32  ui4_mobile_device_page_id;
    UINT16       ui2_hlt_idx;
    UINT16       ui2_delete_item;

    REST_API_PAIRED_DEV_T *p_mobile_device_array;
    UINT32  ui4_mobile_device_arr_size;
    UINT32   ui4_mobile_device_number;

    UINT32 ui4_mobile_device_from_page_id;
    UTF16_T w2s_cur_dev_name[64];
}MENU_MOBILE_DEVICE_PAGE_DATA_T;

#define MOBILE_DEVICE_NUMBER    6

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_mobile_device;
static MENU_MOBILE_DEVICE_PAGE_DATA_T t_g_mobile_device_page_data;
/*UINT32  ui4_mobile_device_delete_dialog_page_id;*/

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

static INT32 _device_listbox_create(
    HANDLE_T                h_parent,
    const GL_RECT_T*        pt_rect,
    wgl_widget_proc_fct     pf_wdgt_proc,
    const WGL_LB_INIT_T*    pt_lb_init,
    VOID*                   pv_tag,
    HANDLE_T*               ph_lb);



/*-----------------------------------------------------------------------------
                    function implementations
 ----------------------------------------------------------------------------*/
static INT32 _mobile_device_build_array(UINT32 device_number)
{
    MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;

    /*array already existed, return*/
    if(pt_this->ui4_mobile_device_arr_size != 0)
    {
        MENU_LOG_ON_FAIL(-1);
        return -1;
    }

    pt_this->p_mobile_device_array= (REST_API_PAIRED_DEV_T *)malloc(
                                    sizeof(REST_API_PAIRED_DEV_T) * device_number);
    if(pt_this->p_mobile_device_array == NULL)
    {
        MENU_LOG_ON_FAIL(-1);
        return -1;
    }

    pt_this->ui4_mobile_device_arr_size = device_number;
    c_memset(pt_this->p_mobile_device_array, 0, sizeof(REST_API_PAIRED_DEV_T) * device_number);

    return 0;
}

static INT32 _mobile_device_destroy_array()
{
    MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;

    if(pt_this->p_mobile_device_array == NULL)
    {
        MENU_LOG_ON_FAIL(-1);
        return -1;
    }

    free(pt_this->p_mobile_device_array);
    pt_this->p_mobile_device_array = NULL;
    pt_this->ui4_mobile_device_arr_size = 0;

    return 0;
}

static INT32 _mobile_device_get_paired_device()
{
    INT32 i4_ret = 0;
    UINT32 ui4_current_device_num = 0;
    GL_RECT_T           t_rect;
    MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;

    if(pt_this->ui4_mobile_device_number == 0
        && pt_this->p_mobile_device_array == NULL)
    {
        i4_ret = _mobile_device_build_array(MOBILE_DEVICE_NUMBER);
        if(i4_ret != 0)
        {
            MENU_LOG_ON_FAIL(i4_ret);
            return i4_ret;
        }
    }

    ui4_current_device_num = MOBILE_DEVICE_NUMBER;
    i4_ret = rest_get_paired_devices(&ui4_current_device_num, pt_this->p_mobile_device_array);
    if(i4_ret != 0)
    {
        if(ui4_current_device_num > pt_this->ui4_mobile_device_arr_size)
        {
            _mobile_device_destroy_array();
            pt_this->ui4_mobile_device_arr_size = ui4_current_device_num;
            _mobile_device_build_array(ui4_current_device_num);
        }
        i4_ret = rest_get_paired_devices(&ui4_current_device_num, pt_this->p_mobile_device_array);
        if(i4_ret != 0)
        {
            MENU_LOG_ON_FAIL(i4_ret);
            return i4_ret;
        }
    }

    if(ui4_current_device_num > MOBILE_DEVICE_NUMBER)
    {
        ui4_current_device_num = MOBILE_DEVICE_NUMBER;
    }

    /*for the zoom on concern*/
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                 MENU_MOBILE_DEVICE_SETTING_DEV_LIST_X,
                 MENU_MOBILE_DEVICE_SETTING_DEV_LIST_Y,
                 MENU_MOBILE_DEVICE_SETTING_DEV_LIST_W,
                 MENU_MOBILE_DEVICE_SETTING_DEV_LIST_ELEM_HEIGHT * ui4_current_device_num);

    c_wgl_move(pt_this->h_device_list, &t_rect, WGL_NO_AUTO_REPAINT);

    pt_this->ui4_mobile_device_number = ui4_current_device_num;
    return 0;
}

VOID mobile_device_delete_paired_device()
{
    INT32 i4_ret = 0;
    CHAR device_id[50];
    UINT16 ui2_device_index = 0;
    UINT16 ui2_item_index = 0;
    MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;
    ui2_item_index = pt_this->ui2_delete_item;

    if(pt_this->ui4_mobile_device_number < (UINT32)ui2_item_index)
    {
        MENU_LOG_ON_FAIL(i4_ret);
    }

    c_memset(device_id, 0, sizeof(CHAR) * 50);
    c_strncpy(device_id, pt_this->p_mobile_device_array[ui2_item_index].device_id,
                        c_strlen(pt_this->p_mobile_device_array[ui2_item_index].device_id));

    i4_ret = rest_delete_paired_device(device_id);
    if(i4_ret != 0)
    {
        MENU_LOG_ON_FAIL(i4_ret);
    }

    for(ui2_device_index = ui2_item_index;
        ui2_device_index < pt_this->ui4_mobile_device_number;
        ui2_device_index++)
    {
        if(ui2_device_index < pt_this->ui4_mobile_device_arr_size)
        {
            c_memcpy(&(pt_this->p_mobile_device_array[ui2_device_index]),
                     &(pt_this->p_mobile_device_array[ui2_device_index + 1]),
                     sizeof(REST_API_PAIRED_DEV_T));
        }
        else if(ui2_device_index == pt_this->ui4_mobile_device_arr_size)
        {
            c_memset(&(pt_this->p_mobile_device_array[ui2_device_index]),
                        0, sizeof(REST_API_PAIRED_DEV_T));
        }
    }
    pt_this->ui4_mobile_device_number--;
}

static INT32 _device_listbox_create(
    HANDLE_T                h_parent,
    const GL_RECT_T*        pt_rect,
    wgl_widget_proc_fct     pf_wdgt_proc,
    const WGL_LB_INIT_T*    pt_lb_init,
    VOID*                   pv_tag,
    HANDLE_T*               ph_lb)
{
    INT32                       i4_ret;
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    UINT8                       ui1_col;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_clr_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    GL_COLOR_T          t_color_disable = { 255, {128}, {128}, {128}};

    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_LIST_BOX,
                                  WGL_CONTENT_LIST_BOX_DEF,
                                  WGL_BORDER_TRANSP,
                                  pt_rect,
                                  pf_wdgt_proc,
                                  255,
                                  (VOID*)pt_lb_init,
                                  pv_tag,
                                  ph_lb);
    if (i4_ret != WGLR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if(pt_lb_init->at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd (*ph_lb,
                                   WGL_CMD_LB_SET_COL_FONT,
                                   WGL_PACK((UINT16)ui1_col),
                                   WGL_PACK(&t_fnt_info));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = MENU_MOBILE_DEVICE_SETTING_LB_INSET_LEFT + 8;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)0),
                           WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = 0;
    t_inset.i4_right  = MENU_MOBILE_DEVICE_SETTING_LB_INSET_RIGHT;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_COL_INSET,
                           WGL_PACK((UINT16)1),
                           WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Color */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_clr_elem, 0, sizeof(WGL_LB_COLOR_ELEM_SET_T));
    t_clr_elem.t_normal             = t_g_menu_color_transp;
    t_clr_elem.t_disable            = t_g_menu_color_transp;
    t_clr_elem.t_highlight          = t_g_menu_color_transp;
    t_clr_elem.t_highlight_unfocus  = t_g_menu_color_transp;
    t_clr_elem.t_pushed             = t_g_menu_color_transp;
    t_clr_elem.t_selected           = t_g_menu_color_transp;
    t_clr_elem.t_selected_disable   = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_ELEM_COLOR,
                           WGL_PACK(WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        i4_ret = c_wgl_do_cmd (*ph_lb,
                               WGL_CMD_LB_SET_COL_COLOR,
                               WGL_PACK_2(ui1_col, WGL_CLR_BK),
                               WGL_PACK(& t_clr_elem));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    c_memset(&t_clr_elem, 0, sizeof(WGL_LB_COLOR_ELEM_SET_T));
    t_clr_elem.t_normal             = t_g_menu_color_white;
    t_clr_elem.t_disable            = t_color_disable;
    t_clr_elem.t_highlight          = t_g_menu_color_white;
    t_clr_elem.t_highlight_unfocus  = t_g_menu_color_white;
    t_clr_elem.t_pushed             = t_g_menu_color_white;
    t_clr_elem.t_selected           = t_g_menu_color_white;
    t_clr_elem.t_selected_disable   = t_g_menu_color_white;
    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if(pt_lb_init->at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd (*ph_lb,
                                   WGL_CMD_LB_SET_COL_COLOR,
                                   WGL_PACK_2(ui1_col, WGL_CLR_TEXT),
                                   WGL_PACK(& t_clr_elem));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Set background image */
    c_memset(&t_img_elem, 0, sizeof(WGL_LB_IMG_ELEM_SET_T));
    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_bk;
    t_img_elem.h_pushed             = NULL_HANDLE;
    t_img_elem.h_selected           = NULL_HANDLE;
    t_img_elem.h_selected_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set long text scroll effect */
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect = {0};
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    i4_ret = c_wgl_do_cmd (*ph_lb,
                            WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                            WGL_PACK (& t_hlt_elem_effect),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}


INT32 menu_mobile_device_help_tip_keytip_set_focus(HANDLE_T h_last_widget,
                                 UINT16 ui2_idx,
                                 BOOL b_repaint)
{
    return MENUR_OK;
}

static INT32 _mobile_device_setting_device_list_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32  i4_ret = MENUR_OK;
    UINT16 ui2_hlt_idx = 0;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_MOBILE_DEVICE_HELP));
        }
            break;

        case WGL_MSG_KEY_UP:
        {
            MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;
            UTF16_T w2s_name_str[64] = {0};

            i4_ret = c_wgl_do_cmd (h_widget,
                                   WGL_CMD_LB_GET_HLT_INDEX,
                                   WGL_PACK (&ui2_hlt_idx),
                                   NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd (h_widget,
                                   WGL_CMD_LB_GET_ITEM_TEXT,
                                   WGL_PACK (ui2_hlt_idx),
                                   WGL_PACK   (w2s_name_str));
            MENU_LOG_ON_FAIL(i4_ret);
            c_memset(pt_this->w2s_cur_dev_name, 0, sizeof(64 * sizeof(UTF16_T)));
            c_uc_w2s_strncpy(pt_this->w2s_cur_dev_name, w2s_name_str, c_uc_w2s_strlen(w2s_name_str));

#ifdef APP_TTS_SUPPORT
            if (i4_ret >= 0)
            {
                a_app_tts_play(w2s_name_str, 64);
            }
#endif
            break;
        }

        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;
            UINT16 ui2_elem_num = 0;

            switch (ui4_keycode)
            {
                case BTN_CURSOR_UP:
                {
                    i4_ret = c_wgl_do_cmd (h_widget,
                                           WGL_CMD_LB_GET_HLT_INDEX,
                                           WGL_PACK (&ui2_hlt_idx),
                                           NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    if (ui2_hlt_idx > 0)
                    {
                        i4_ret = c_wgl_do_cmd (h_widget,
                                               WGL_CMD_LB_HLT_PREV_ELEM,
                                               WGL_PACK (TRUE),
                                               NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_MOBILE_DEVICE_HELP));
                    }
                    else
                    {
                        i4_ret = menu_set_focus_on_backbar(TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }
                return WGLR_OK;

                case BTN_CURSOR_DOWN:
                {
                   i4_ret = c_wgl_do_cmd (h_widget,
                                           WGL_CMD_LB_GET_ELEM_NUM,
                                           WGL_PACK (&ui2_elem_num),
                                           NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_do_cmd (h_widget,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK (&ui2_hlt_idx),
                                      NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    if (ui2_elem_num > (ui2_hlt_idx+1))
                    {
                        i4_ret = c_wgl_do_cmd (h_widget,
                                               WGL_CMD_LB_HLT_NEXT_ELEM,
                                               WGL_PACK (TRUE),
                                               NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_MOBILE_DEVICE_HELP));
                    }
                    else
                    {
                        i4_ret = menu_mobile_device_help_tip_keytip_set_focus(h_widget, 0 , FALSE);
                        MENU_LOG_ON_FAIL(i4_ret);
                        menu_pm_repaint();
                    }
                }
                return WGLR_OK;

                case BTN_SELECT:
                {
                    if(0 == _mobile_device_get_paired_device() && t_g_mobile_device_page_data.ui4_mobile_device_number > 0)
                     {
                          /*perform delete device here*/
                          i4_ret = c_wgl_do_cmd (h_widget,
                                           WGL_CMD_LB_GET_HLT_INDEX,
                                           WGL_PACK (&ui2_hlt_idx),
                                           NULL);
                          MENU_LOG_ON_FAIL(i4_ret);

                          pt_this->ui2_delete_item = ui2_hlt_idx;
                          pt_this->ui4_mobile_device_from_page_id = ui4_mobile_device_delete_dialog_page_id;

                          menu_page_set_hide_main_inpageswitch();
                          menu_nav_go(ui4_mobile_device_delete_dialog_page_id, NULL);
                     }
                }
                break;

                case BTN_RETURN:
                {
                    menu_nav_back();
                }
                break;

                default:
                    break;
            }
        }
            break;

        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _mobile_device_page_device_list_create (VOID)
{
    INT32               i4_ret = MENUR_OK;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols;
    GL_RECT_T           t_rect;
    MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;

    c_memset(&at_cols, 0, sizeof(WGL_LB_COL_INIT_T));
    at_cols.e_col_type       = LB_COL_TYPE_TEXT;
    at_cols.ui1_align        = WGL_AS_CENTER_CENTER/*MENU_MOBILE_DEVICE_SETTING_DEV_DISP_NAME_ALIGN*/;
    at_cols.ui2_max_text_len = MENU_MOBILE_DEVICE_SETTING_DEV_DISP_NAME_MAX_TEXT_LEN;
    at_cols.ui2_width        = MENU_MOBILE_DEVICE_SETTING_DEV_DISP_NAME_COL_WIDTH;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = MENU_MOBILE_DEVICE_SETTING_MAX_DEVICE_NUM;
    t_lb_init.ui2_elem_size     = MENU_MOBILE_DEVICE_SETTING_DEV_LIST_ELEM_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = &at_cols;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_MOBILE_DEVICE_SETTING_DEV_LIST_X,
                     MENU_MOBILE_DEVICE_SETTING_DEV_LIST_Y,
                     MENU_MOBILE_DEVICE_SETTING_DEV_LIST_W,
                     MENU_MOBILE_DEVICE_SETTING_DEV_LIST_H);
    i4_ret = _device_listbox_create(pt_this->h_cnt_frm,
                                    &t_rect,
                                    _mobile_device_setting_device_list_proc_fct,
                                    &t_lb_init,
                                    NULL,
                                    &pt_this->h_device_list);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _mobile_device_page_backbar_proc_fct(
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32  i4_ret = MENUR_OK;
        MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
            #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
            #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                menu_nav_back();

                return MENUR_OK;
            }

            case BTN_CURSOR_DOWN:
            {
                if(pt_this->ui4_mobile_device_number != 0)
                {
                    i4_ret = c_wgl_set_focus(pt_this->h_device_list,
                                             WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                break ;
            }

            case BTN_CURSOR_UP:
            {
                i4_ret = menu_set_focus_on_homebar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;

            default:
                break ;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _mobile_device_page_homebar_proc_fct(
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HOME_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32  i4_ret = MENUR_OK;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
            #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
            #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                UINT32 aui4_pages[1] = {ui4_g_menu_page_main_menu};
                i4_ret = menu_nav_go_direct(0,
                                            aui4_pages,
                                            sizeof(aui4_pages)/sizeof(aui4_pages[0]),
                                            NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }

            case BTN_CURSOR_DOWN:
            {
                i4_ret = menu_set_focus_on_backbar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;

            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

static INT32 _mobile_device_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32       i4_ret = MENUR_OK;
    MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;

    c_memset(pt_this, 0, sizeof(MENU_MOBILE_DEVICE_PAGE_DATA_T));

    pt_this->ui4_mobile_device_page_id = ui4_page_id;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_this->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mobile_device_page_device_list_create();
    MENU_LOG_ON_FAIL(i4_ret);
/*
    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_REMOVE_MOBILE_DEVICE_DIALOG,
                           MLM_MENU_KEY_MOBILE_DEVICE_DIALOG_REMOVE,
                           MLM_MENU_KEY_HELP_CNCL,
                           UI_SIMPLE_DIALOG_STYLE_SMALL,
                           WGL_AS_CENTER_CENTER,
                           FALSE,
                           _mobile_device_delete_paired_device,
                           NULL,
                           &ui4_mobile_device_delete_dialog_page_id);
    MENU_LOG_ON_FAIL(i4_ret);
*/
    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _mobile_device_page_destroy(UINT32 ui4_page_id)
{
    _mobile_device_destroy_array();
    return MENUR_OK;
}

static INT32 _mobile_device_show_device_list()
{
    INT32           i4_ret = MENUR_OK;
    UINT32          ui4_index = 0;
    WGL_LB_ITEM_T   at_items;
    UTF16_T         pw2s_name_tmp[32];
    UINT16          ui2_device_num = 0;
    GL_RECT_T       t_rect = {0};
    HANDLE_T		h_last_shadow_item = NULL_HANDLE;
    MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;

    i4_ret = c_wgl_do_cmd(pt_this->h_device_list,
                          WGL_CMD_LB_DEL_ALL, NULL, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mobile_device_get_paired_device();
    if(i4_ret != 0)
    {
        MENU_CHK_FAIL(i4_ret);
    }

    if(pt_this->ui4_mobile_device_number > 0)
    {
        for(ui4_index = 0; ui4_index < pt_this->ui4_mobile_device_number; ui4_index++)
        {
            c_memset(&at_items, 0, sizeof(WGL_LB_ITEM_T));
            c_memset(pw2s_name_tmp, 0, sizeof(UTF16_T) * 32);

            c_uc_ps_to_w2s(pt_this->p_mobile_device_array[ui4_index].device_name,
                                            pw2s_name_tmp, sizeof(UTF16_T) * 32);

            at_items.e_col_type = LB_COL_TYPE_TEXT;
            at_items.data.pw2s_text = pw2s_name_tmp;

            i4_ret = c_wgl_do_cmd(pt_this->h_device_list,
                                  WGL_CMD_LB_APPEND_ELEM, &at_items, NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }
    else
    {
        c_memset(&at_items, 0, sizeof(WGL_LB_ITEM_T));

        at_items.e_col_type = LB_COL_TYPE_TEXT;
        at_items.data.pw2s_text = MENU_TEXT(MLM_MENU_KEY_MOBILE_DEVICE_NO_DEVICE);

        i4_ret = c_wgl_do_cmd(pt_this->h_device_list,
                              WGL_CMD_LB_APPEND_ELEM, &at_items, NULL);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = c_wgl_set_focus(pt_this->h_device_list, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret=menu_set_help_tip(NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_device_list,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* adjust last shadow position */
    i4_ret = c_wgl_do_cmd(pt_this->h_device_list,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK (&ui2_device_num),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;
	t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui2_device_num + CONTENT_Y;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;

	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _mobile_device_page_show(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = menu_main_set_title(MLM_MENU_KEY_MOBILE_DEVICE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _mobile_device_show_device_list();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_backbar_proc(_mobile_device_page_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(_mobile_device_page_homebar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _mobile_device_page_hide(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _mobile_device_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32       i4_ret = MENUR_OK;
    MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;

    if(pt_this->ui4_mobile_device_number != 0)
    {
        if (pt_this->ui4_mobile_device_from_page_id == ui4_mobile_device_delete_dialog_page_id)
        {
            i4_ret = c_wgl_do_cmd(pt_this->h_device_list,
                                  WGL_CMD_LB_HLT_ELEM,
                                  WGL_PACK(pt_this->ui2_hlt_idx),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_MOBILE_DEVICE_HELP));
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_set_focus(pt_this->h_last_focus,
                         WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
            pt_this->ui4_mobile_device_from_page_id = 0;
        }
        else/* if(pt_this->ui4_mobile_device_number != 0)*/
        {
            i4_ret = c_wgl_set_focus(pt_this->h_device_list, WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
     }
    return i4_ret;
}

static INT32 _mobile_device_page_lose_focus(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    HANDLE_T    h_focus = NULL_HANDLE;
    MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;

    /* memorize last focus */
    i4_ret = c_wgl_get_focus(&h_focus);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->h_last_focus = h_focus;

    if (h_focus == pt_this->h_device_list)
    {
        i4_ret = c_wgl_do_cmd (h_focus,
                               WGL_CMD_LB_GET_HLT_INDEX,
                               WGL_PACK (&pt_this->ui2_hlt_idx),
                               NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

static INT32 _mobile_device_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)

{
    return MENUR_OK;
}

extern INT32 mobile_device_get_mobile_dev_name(UTF16_T * p_dev_name)
{
    MENU_MOBILE_DEVICE_PAGE_DATA_T* pt_this = &t_g_mobile_device_page_data;
    if(p_dev_name == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(c_uc_w2s_strlen(pt_this->w2s_cur_dev_name) == 0)
    {
        return MENUR_FAIL;
    }

    c_uc_w2s_strncpy(p_dev_name, pt_this->w2s_cur_dev_name, c_uc_w2s_strlen(pt_this->w2s_cur_dev_name));
    return MENUR_OK;
}

extern INT32 menu_device_page_mobile_device_init(VOID)
{
    t_g_menu_device_page_mobile_device.pf_menu_page_create =    _mobile_device_page_create;
    t_g_menu_device_page_mobile_device.pf_menu_page_destroy=    _mobile_device_page_destroy;
    t_g_menu_device_page_mobile_device.pf_menu_page_show=       _mobile_device_page_show;
    t_g_menu_device_page_mobile_device.pf_menu_page_hide=       _mobile_device_page_hide;
    t_g_menu_device_page_mobile_device.pf_menu_page_get_focus=  _mobile_device_page_get_focus;
    t_g_menu_device_page_mobile_device.pf_menu_page_lose_focus= _mobile_device_page_lose_focus;
    t_g_menu_device_page_mobile_device.pf_menu_page_update=     _mobile_device_page_update;

    return MENUR_OK;
}
