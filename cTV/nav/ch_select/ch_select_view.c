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
 * $RCSfile: ch_select_view.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: yuwen han $
 * $MD5HEX: 7793009dbc122937a0001b34eec5772f $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


#include "ch_select_view.h"
#include "res/menu2/menu_mlm.h"
#include "res/nav/nav_colors.h"
#include "res/menu2/menu_clr.h"
#include "menu2/menu_page.h"
#include "res/wdk/digit_pad/digit_images.h"

#include "res/nav/one_channel_list/ocl.h"
#include "nav/banner2/banner.h"
#include "rest/a_rest_api.h"
#include "app_util/toast_widget/a_toast.h"
#include "app_util/a_zoom_mode.h"


#define MAX_LEN (128)
#define AUTO_INSERT_DASH_LEN (3)
#define INPUT_LABEL_W (306)
#define INPUT_LABEL_H (82)
#define INPUT_INTERVAL (12)
#define DIGIT_PAD_X   (51)
#define CH_FRAME_X       (150)
#define CH_FRAME_Y       (600)
#define DIGIT_PAD_DISPLAY_TIMER (30000) /* in ms */

typedef struct _CH_SELECT_VIEW
{
    HANDLE_T h_canvas;
    HANDLE_T digit_pad;
    HANDLE_T input_label;
    HANDLE_T h_toast_view;
    CHAR s_content[MAX_LEN + 1];
    BOOL b_showing;
    BOOL b_showing_toast;
    CH_SELECT_CTRL_T t_ctrl;
    BOOL b_hide_timer_active;
    HANDLE_T                  h_hide_timer;
    UINT32                    ui4_hide_timeout;
    HANDLE_T                  h_select_timer;
    UINT32                    ui4_sel_timeout;
} CH_SELECT_VIEW;

static CH_SELECT_VIEW *pt_this;

static      UINT8   i2_notification_timer_count  =   0;
static HANDLE_T    h_ch_select_notification_msg_timer  =   NULL_HANDLE;
static HANDLE_T    h_ch_select_toast_msg_timer  =   NULL_HANDLE;
static ZOOM_SECTOR_ITEM e_ch_select_pre_sector  = ZOOM_SECTOR_ITEM_2;

WGL_HIMG_TPL_T     h_g_nav_img_toast_msg_icon_arrow_up      =   NULL_HANDLE;
WGL_HIMG_TPL_T     h_g_nav_img_toast_msg_icon_arrow_down    =   NULL_HANDLE;
WGL_HIMG_TPL_T     h_g_nav_img_toast_msg_icon_ok_key        =   NULL_HANDLE;

static BOOL b_ch_msg_show_flag = TRUE;
static BOOL b_go_into_power_off = FALSE;

static INT32 _ch_select_view_init(CH_SELECT_CTRL_T t_ctrl,
                                  HANDLE_T h_canvas,
                                  INT32 i4_frame_x_offset,
                                  INT32 i4_frame_y_offset);

static INT32 _ch_select_view_create_digit_pad(HANDLE_T parent,
                                              INT32 i4_frame_x_offset,
                                              INT32 i4_frame_y_offset);
static INT32 _ch_select_view_create_input_label(HANDLE_T parent,
                                                INT32 i4_frame_x_offset,
                                                INT32 i4_frame_y_offset);

static VOID _ch_select_view_digit_pad_key_event_nfy(DIGIT_PAD_EVENT_TYPE event_type,
                                                    VOID *pv_param);
static INT32 _ch_select_view_show_label(BOOL b_show);
static INT32 _ch_select_view_show(VOID);
static INT32 _ch_select_view_hide(VOID);
static INT32 _ch_select_view_deinit(VOID);
static INT32 _ch_select_label_update_text(VOID);

static VOID _ch_select_view_show_notification_cb_fct(HANDLE_T  pt_tm_handle,
                                            VOID*     pv_tag);

INT32 ch_select_view_toast_msg_show(UTF16_T*  pw2s_string);
INT32 ch_select_view_toast_msg_hide(VOID);


static INT32 _select_view_digit_pad_create_timer(CH_SELECT_VIEW* pt_this);
static INT32 _select_view_digit_pad_del_timer(CH_SELECT_VIEW* pt_this);
static VOID _select_view_digit_pad_stop_hide_timer(CH_SELECT_VIEW* pt_this);
static VOID _select_view_digit_pad_reset_hide_timer(CH_SELECT_VIEW* pt_this);
static VOID _select_view_digit_pad_do_hide_timeout(
    VOID*                       pv_unused0,
    VOID*                       pv_unused1,
    VOID*                       pv_unused2
    );
static VOID _select_view_digit_pad_timer_hide_nfy(HANDLE_T  h_timer);


static VOID _select_view_digit_pad_stop_sel_timer(CH_SELECT_VIEW* pt_this);
static VOID _select_view_digit_pad_reset_sel_timer(CH_SELECT_VIEW* pt_this);
static VOID _select_view_digit_pad_do_sel_timeout(
                    VOID*                       pv_unused0,
                    VOID*                       pv_unused1,
                    VOID*                       pv_unused2
                    );
static VOID _select_view_digit_pad_timer_sel_nfy(HANDLE_T  h_timer);


VOID a_ch_select_view_build(CH_SELECT_VIEW_T *pt_ch_select_view_t)
{
    pt_ch_select_view_t->pf_init = _ch_select_view_init;
    pt_ch_select_view_t->pf_show = _ch_select_view_show;
    pt_ch_select_view_t->pf_hdie = _ch_select_view_hide;
    pt_ch_select_view_t->pf_deinit = _ch_select_view_deinit;
}

static INT32 _ch_select_view_init(CH_SELECT_CTRL_T t_ctrl,
                                  HANDLE_T h_canvas,
                                  INT32 i4_frame_x_offset,
                                  INT32 i4_frame_y_offset)
{
    wdk_digit_pad_init_image();
    INT32 i4_ret = NAVR_OK;
    pt_this = (CH_SELECT_VIEW *)c_mem_alloc(sizeof(CH_SELECT_VIEW));
    if (NULL == pt_this)
    {
        return NAVR_OUT_OF_MEM;
    }
    pt_this->s_content[0] = '\0';
    pt_this->t_ctrl = t_ctrl;
    pt_this->b_showing = FALSE;
    pt_this->h_canvas = h_canvas;

    i4_ret = _select_view_digit_pad_create_timer(pt_this);
    NAV_CS_CHK_FAIL(i4_ret, "Can't create timer for digit pad");
    i4_ret = _ch_select_view_create_digit_pad(h_canvas, i4_frame_x_offset, i4_frame_y_offset);
    NAV_CS_CHK_FAIL(i4_ret, "Can't create digit pad");
    i4_ret = _ch_select_view_create_input_label(h_canvas, i4_frame_x_offset, i4_frame_y_offset);
    NAV_CS_CHK_FAIL(i4_ret, "Can't create input label");

    i4_ret = nav_img_create_arrow_up_down_icon(&h_g_nav_img_toast_msg_icon_ok_key,&h_g_nav_img_toast_msg_icon_arrow_up,&h_g_nav_img_toast_msg_icon_arrow_down);
    NAV_CS_CHK_FAIL(i4_ret,"Can't create arrow up/down icon");

    c_timer_create (&h_ch_select_notification_msg_timer);
    c_timer_create (&h_ch_select_toast_msg_timer);
    return i4_ret;
}

static VOID _ch_select_view_digit_pad_key_event_nfy(DIGIT_PAD_EVENT_TYPE event_type, VOID *pv_param)
{
    CHAR digit_val;
    UINT8 ui1_content_len = 0;
    BOOL b_insert_dash = FALSE;
    INT32 i4_ret = NAVR_OK;

    switch (event_type)
    {
        case DIGIT_PAD_DIGIT_KEY:

            _select_view_digit_pad_stop_hide_timer(pt_this);
            _select_view_digit_pad_reset_sel_timer(pt_this);

            digit_val = *((CHAR *)pv_param);
            ui1_content_len = c_strlen(pt_this->s_content);
            if (ui1_content_len < MAX_LEN)
            {
                if (ui1_content_len == AUTO_INSERT_DASH_LEN && digit_val != '-')
                {
                    b_insert_dash = TRUE;
                    for (UINT8 ui1_i = 0; ui1_i < AUTO_INSERT_DASH_LEN; ui1_i++)
                    {
                        if (pt_this->s_content[ui1_i] == '-')
                        {
                            b_insert_dash = FALSE;
                            break;
                        }
                    }
                    if (TRUE == b_insert_dash)
                    {
                        pt_this->s_content[ui1_content_len] = '-';
                        pt_this->s_content[ui1_content_len + 1] = '\0';
                        ui1_content_len = c_strlen(pt_this->s_content);
                    }
                }
                pt_this->s_content[ui1_content_len] = digit_val;
                pt_this->s_content[ui1_content_len + 1] = '\0';
                i4_ret = _ch_select_label_update_text();
                NAV_CS_LOG_FAIL(i4_ret, "Can't update text of label");
                i4_ret = a_digit_pad_grayout_dash(pt_this->digit_pad, FALSE);
                NAV_CS_LOG_FAIL(i4_ret, "Can't gray dash key in digit pad");
                i4_ret = a_digit_pad_grayout_del(pt_this->digit_pad, FALSE);
                NAV_CS_CHK_FAIL(i4_ret, "Can't gray del key in digit pad");
            }
            break;

        case DIGIT_PAD_DEL_KEY:
            _select_view_digit_pad_stop_hide_timer(pt_this);
            ui1_content_len = c_strlen(pt_this->s_content);
            if (ui1_content_len > 0)
            {
                pt_this->s_content[ui1_content_len - 1] = '\0';
            }
            ui1_content_len = c_strlen(pt_this->s_content);
            if (ui1_content_len == 0)
            {
                i4_ret = a_digit_pad_grayout_dash(pt_this->digit_pad, TRUE);
                NAV_CS_LOG_FAIL(i4_ret, "Can't gray dash key in digit pad");
                i4_ret = a_digit_pad_grayout_del(pt_this->digit_pad, TRUE);
                NAV_CS_CHK_FAIL(i4_ret, "Can't gray del key in digit pad");
            }
            i4_ret = _ch_select_label_update_text();
            NAV_CS_LOG_FAIL(i4_ret, "Can't update text of label");
            break;

        case DIGIT_PAD_BUTTON_OK:
            i4_ret = pt_this->t_ctrl.pf_select(pt_this->s_content);
            NAV_CS_LOG_FAIL(i4_ret, "Can't hide component");
            pt_this->s_content[0] = '\0';
            break;

        case DIGIT_PAD_BUTTON_CANCEL:
            break;

        case DIGIT_PAD_BUTTON_INFO:
            a_nav_show_detail_banner_ex();
            break;

        case DIGIT_PAD_NAV_BACK:
            i4_ret = pt_this->t_ctrl.pf_hide();
            NAV_CS_LOG_FAIL(i4_ret, "Can't hide component");
            pt_this->s_content[0] = '\0';
            break;

        case DIGIT_PAD_FOCUS_TO_ABOVE_WGL:
            break;
        case DIGIT_PAD_FOCUS_TO_BELOW_WGL:
            break;
        default:
            break;
    }
}

static BOOL _ch_select_view_digit_rc_event_default_handle(UINT32 ui4_msg,
                                                          VOID *pv_param1,
                                                          VOID *pv_param2)
{
    UINT32 ui4_keycode = (UINT32)pv_param1;

    INT32 i4_ret = NAVR_OK;
    // if (!a_ch_select_ctrl_is_enable())
    // {
    //     i4_ret = pt_this->t_ctrl.pf_hide();
    //     NAV_CS_CHK_FAIL(i4_ret, "Can't hide component");
    //     nav_rcu_key_handler(ui4_keycode);
    //     return FALSE;
    // }
    // if (pt_this->b_showing == FALSE)
    // {
    //     nav_rcu_key_handler(ui4_keycode);
    //     return FALSE;
    // }
    switch (ui4_keycode)
    {
        case BTN_VOL_UP:
        case BTN_VOL_DOWN:
        case BTN_MUTE:
        case BTN_P_EFFECT:
        case BTN_INPUT_SRC:
        case BTN_PRG_INFO:
        case BTN_CC:
        case BTN_WIDGET:
        case BTN_POWER:
        case BTN_EXIT:
        case BTN_PRG_UP:
        case BTN_PRG_DOWN:
            if (TRUE == pt_this->b_showing)
            {
                i4_ret = pt_this->t_ctrl.pf_hide();
                NAV_CS_CHK_FAIL(i4_ret, "Can't hide component");
                nav_rcu_key_handler(ui4_keycode);
                return TRUE;
            }
    }
    return FALSE;
}

static INT32 _ch_select_view_create_input_label(HANDLE_T parent,
                                                INT32 i4_frame_x_offset,
                                                INT32 i4_frame_y_offset)
{
    INT32                   i4_ret = WDKR_OK;
    WDK_TXT_WIDGET_PARAM_T  t_txt_param;

    c_memset(&t_txt_param, 0, sizeof(WDK_TXT_WIDGET_PARAM_T));
    t_txt_param.h_parent      = parent;
    t_txt_param.ui1_alpha     = 255;
    t_txt_param.b_visibility  = TRUE;
    t_txt_param.i4_x          = CH_FRAME_X;
    t_txt_param.i4_y          = CH_FRAME_Y;
    t_txt_param.i4_w          = INPUT_LABEL_W;
    t_txt_param.i4_h          = INPUT_LABEL_H;
    t_txt_param.ui4_style     = WGL_STL_TEXT_MAX_32 | WGL_STL_TEXT_END_AS_NEWLINE | WGL_STL_TEXT_SMART_CUT;
    t_txt_param.ps_font_name  = APP_FONT_MENU_NAME;
    t_txt_param.e_font_size   = FE_FNT_SIZE_CUSTOM;
    t_txt_param.ui1_font_custom_size = 32;
    t_txt_param.e_font_style  = FE_FNT_STYLE_REGULAR;
    t_txt_param.ui1_align     = WGL_AS_CENTER_CENTER;
    t_txt_param.b_img_bk      = TRUE;
    t_txt_param.pt_clr_txt    = & (NAV_COLOR(NAV_COLOR_ID_TEXT));
    t_txt_param.pt_hlt_clr_txt= & (NAV_COLOR(NAV_COLOR_ID_TEXT));
    t_txt_param.pt_dis_clr_txt= & (t_g_menu_color_bk2_txt_disable);

    t_txt_param.t_img_bk.h_enable    = h_g_digit_pad_channel_field;
    t_txt_param.t_img_bk.h_highlight = h_g_digit_pad_channel_field;
    t_txt_param.t_img_bk.h_disable   = h_g_digit_pad_channel_field;

    t_txt_param.pf_wdgt_proc = NULL;

    t_txt_param.ph_created_txt= &(pt_this->input_label);

    i4_ret = a_wdk_create_txt_widget (t_txt_param);
    WDK_CHK_FAIL(i4_ret);

    // i4_ret = a_wdk_text_set_text(*t_txt_param.ph_created_txt, MENU_TEXT(pt_this->cfg.btn_ok.ui2_text_key));
    // WDK_CHK_FAIL(i4_ret);

    /* Clear key map to make sure text widget will notify CURSOR key to its parent frame. */
    // i4_ret = _digit_key_set_text_keymap(*(t_txt_param.ph_created_txt));
    // WDK_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_set_visibility(pt_this->input_label, WGL_SW_HIDE);
    NAV_CS_CHK_FAIL(i4_ret, "Can't set visibility of input label");
    return i4_ret;
}

static INT32 _ch_select_view_create_digit_pad(HANDLE_T parent,
                                              INT32 i4_frame_x_offset,
                                              INT32 i4_frame_y_offset)
{
    INT32 i4_ret = NAVR_OK;
    DIGIT_PAD_CONFIG cfg;
    a_digit_pad_init_config(&cfg);
    cfg.parent_frame = parent;
    cfg.position.ui4_left = CH_FRAME_X + DIGIT_PAD_X;
    cfg.position.ui4_top = CH_FRAME_Y + INPUT_LABEL_H + INPUT_INTERVAL;
    cfg.digit_key_event_nfy = _ch_select_view_digit_pad_key_event_nfy;
    cfg.pf_rc_event_default_handle = _ch_select_view_digit_rc_event_default_handle;
    cfg.b_info_ok_key_enable = TRUE;
    cfg.b_dash_key_enable = TRUE;
    cfg.b_dash_key_grayout= TRUE;
    i4_ret = a_digit_pad_create(cfg, &pt_this->digit_pad);
    NAV_CS_CHK_FAIL(i4_ret, "Create create digit pad");
    i4_ret = a_digit_pad_hide(pt_this->digit_pad);
    NAV_CS_CHK_FAIL(i4_ret, "Cann't hide digit pad");

    return i4_ret;
}

static INT32 _ch_select_label_update_text(VOID)
{
    INT32 i4_ret = NAVR_OK;
    UTF16_T w2s_tmp_str[128] = {0};
    c_uc_ps_to_w2s(pt_this->s_content, w2s_tmp_str, c_strlen(pt_this->s_content));
    i4_ret = a_wdk_text_set_text(pt_this->input_label, w2s_tmp_str);
    NAV_CS_CHK_FAIL(i4_ret, "Can't set text of label");
    i4_ret = c_wgl_repaint(pt_this->input_label, NULL, TRUE);
    NAV_CS_CHK_FAIL(i4_ret, "Can't repaint input label");
    return i4_ret;
}

static INT32 _ch_select_view_show_label(BOOL b_show)
{
    INT32 i4_ret = NAVR_OK;
    i4_ret = _ch_select_label_update_text();
    NAV_CS_CHK_FAIL(i4_ret, "Can't update text of label");
    i4_ret = c_wgl_set_visibility(pt_this->input_label, b_show ? WGL_SW_RECURSIVE : WGL_SW_HIDE);
    NAV_CS_CHK_FAIL(i4_ret, "Can't set visibility of input label");
    i4_ret = c_wgl_repaint(pt_this->input_label, NULL, TRUE);
    NAV_CS_CHK_FAIL(i4_ret, "Can't repaint input label");
    return i4_ret;
}

static INT32 _ch_select_view_show(VOID)
{
    INT32 i4_ret = NAVR_OK;
    UINT8 ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;

    pt_this->s_content[0] = '\0';
    i4_ret = a_digit_pad_grayout_dash(pt_this->digit_pad, TRUE);
    NAV_CS_CHK_FAIL(i4_ret, "Can't gray dash key in digit pad");
    i4_ret = a_digit_pad_grayout_del(pt_this->digit_pad, TRUE);
    NAV_CS_CHK_FAIL(i4_ret, "Can't gray del key in digit pad");
    i4_ret = a_digit_pad_show(pt_this->digit_pad);
    NAV_CS_CHK_FAIL(i4_ret, "Can't show digit pad");
    i4_ret = a_digit_pad_focus(pt_this->digit_pad);
    NAV_CS_CHK_FAIL(i4_ret, "Can't focus digit pad");
    i4_ret = _ch_select_view_show_label(TRUE);
    NAV_CS_CHK_FAIL(i4_ret, "Can't show input label");
    pt_this->b_showing = TRUE;
    _select_view_digit_pad_reset_hide_timer(pt_this);
    a_cfg_cust_get_zoom_status(&ui1_zoom_mode);
    if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
    {/*record DTV03027147:show channel numbers pad*/
        e_ch_select_pre_sector  = nav_zoom_cust_get_current_sector_item();
        DBG_LOG_PRINT(("[ZOOM] %s(), e_ch_select_pre_sector = %d.\n\r",__FUNCTION__,e_ch_select_pre_sector));
        i4_ret = a_nav_zoom_cust_select_sector(ZOOM_SECTOR_ITEM_7,TRUE);
        if(i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[ZOOM] %s(),select ZOOM_SECTOR_ITEM_7 failed!!.\n\r",__FUNCTION__));
        }
    }
    return i4_ret;
}

static INT32 _ch_select_view_hide(VOID)
{
    INT32 i4_ret = NAVR_OK;
    UINT8 ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;

    c_wgl_set_focus(NULL_HANDLE, FALSE);
    i4_ret = a_digit_pad_hide(pt_this->digit_pad);
    NAV_CS_CHK_FAIL(i4_ret, "Cann't hide digit pad");
    i4_ret = _ch_select_view_show_label(FALSE);
    NAV_CS_CHK_FAIL(i4_ret, "Can't hide input label");
    pt_this->b_showing = FALSE;
    a_cfg_cust_get_zoom_status(&ui1_zoom_mode);
    if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
    {    i4_ret = a_nav_zoom_cust_select_sector(e_ch_select_pre_sector,TRUE);
        if(i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[ZOOM] %s(),select failed!!.\n\r",__FUNCTION__));
        }
    }
    return i4_ret;
}

static INT32 _ch_select_view_deinit(VOID)
{
    INT32 i4_ret = NAVR_OK;
    i4_ret = _select_view_digit_pad_del_timer(pt_this);
    c_timer_delete(h_ch_select_notification_msg_timer);
    c_timer_delete(h_ch_select_toast_msg_timer);

    return i4_ret;
}

INT32 a_ch_select_view_reset_to_default(void)
{
    i2_notification_timer_count = 0;

    if(h_ch_select_notification_msg_timer)
    {
        c_timer_stop(h_ch_select_notification_msg_timer);
    }

    if(h_ch_select_toast_msg_timer != NULL_HANDLE)
    {
        c_timer_stop(h_ch_select_toast_msg_timer);
    }

    ch_select_view_toast_msg_hide();

    return NAVR_OK;
}

static INT32 _ch_select_view_send_string_to_nav_toast(WDK_TOAST_T *pt_toast)
{
    WDK_TOAST_T* pt_toast_cpy = NULL;
    UTF16_T* p_w2s_str = (UTF16_T*)pt_toast->style.style_4.w2s_str;

    pt_toast_cpy = (WDK_TOAST_T*)c_mem_alloc(sizeof(WDK_TOAST_T));

    if (NULL == pt_toast_cpy)
    {
        DBG_INFO(("NULL == pt_toast_cpy!!\n"));
        return -1;
    }

    c_memcpy((VOID*)pt_toast_cpy, (const VOID*)pt_toast, sizeof(WDK_TOAST_T));

    if (pt_toast->e_string_style == WDK_STRING_STRING)
    {
        CHAR     str[128]  = {0};
        INT32    len  = 0;

        c_uc_w2s_to_ps((const UTF16_T*)p_w2s_str, str, 127);

        len = (c_uc_w2s_strlen(p_w2s_str)+1)*2;
        pt_toast_cpy->style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(len);

        c_memset((VOID*)pt_toast_cpy->style.style_4.w2s_str, 0, len);

        c_memcpy((VOID*)pt_toast_cpy->style.style_4.w2s_str, (const VOID*)pt_toast->style.style_4.w2s_str, len);
    }

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                              NAV_UI_MSG_REST_NOTIFICATION,
                              (VOID*) pt_toast_cpy);
    /*the conflicts with toast string, OR TTS will play two times.*/
#if 0
#ifdef APP_TTS_SUPPORT
    a_app_tts_play(p_w2s_str, c_uc_w2s_strlen(p_w2s_str));
#endif
#endif
    return NAVR_OK;
}

static VOID _ch_select_view_show_notification(VOID)
{

    WDK_TOAST_T    t_toast          = {0};
    c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;
    t_toast.style.style_4.w2s_str = (VOID*)MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_USE_CHANGE_CHANNEL_NOTIFICATION);
    _ch_select_view_send_string_to_nav_toast(&t_toast);

}

BOOL ch_select_view_set_power_off_flag(BOOL val)
{

    b_go_into_power_off = val;
    return b_go_into_power_off;
}

BOOL ch_select_view_get_power_off_flag(VOID)
{
    return b_go_into_power_off;
}

static VOID _ch_select_view_show_notification_check_show(VOID* pv_data1,
                                    VOID* pv_data2,
                                    VOID* pv_data3)
{
    i2_notification_timer_count++;
    if(ch_select_view_get_power_off_flag() == TRUE)
    {
        DBG_LOG_PRINT(("b_go_into_power_off = TRUE, don't show digit pad notify toast\n"));
        return;
    }

    if(!banner_view_is_on_show())
    {
        //_ch_select_view_show_notification();

        DBG_LOG_PRINT(("chenxin_toast %s %d \n",__FUNCTION__,__LINE__));
        ch_select_view_toast_msg_show(NULL);

        i2_notification_timer_count = 0;
    }
    else if(i2_notification_timer_count < 15) //to avoid repeat timer forever,so set up to 15 times
    {
        c_timer_stop(h_ch_select_notification_msg_timer);
        c_timer_start(h_ch_select_notification_msg_timer,
                     1000,
                     X_TIMER_FLAG_ONCE,
                     _ch_select_view_show_notification_cb_fct,
                     NULL);
    }
    else
    {
        i2_notification_timer_count = 0;
    }

}

static VOID _ch_select_view_show_notification_cb_fct(HANDLE_T  pt_tm_handle,
                                            VOID*     pv_tag)
{
    nav_request_context_switch(_ch_select_view_show_notification_check_show,NULL, NULL,NULL);
}

BOOL ch_select_view_set_b_ch_msg_show_flag(BOOL val)
{

    b_ch_msg_show_flag = val;
    return b_ch_msg_show_flag;
}

BOOL ch_select_view_get_b_ch_msg_show_flag(VOID)
{
    return b_ch_msg_show_flag;
}

static VOID _ch_select_view_show_notification_timer(VOID* pv_data1,
                                    VOID* pv_data2,
                                    VOID* pv_data3)
{
    if (!a_ch_select_ctrl_is_enable()) {
        DBG_LOG_PRINT(("a_ch_select_ctrl_is_enable = FALSE, don't show digit pad notify toast\n"));
        return;
    }

    if(b_ch_msg_show_flag == FALSE)
    {
        DBG_LOG_PRINT(("b_ch_msg_show_flag = FALSE, don't show digit pad notify toast\n"));
        return;
    }

    i2_notification_timer_count = 0;
    if(h_ch_select_notification_msg_timer)
    {
        c_timer_stop(h_ch_select_notification_msg_timer);
        c_timer_start(h_ch_select_notification_msg_timer,
                     1000,
                     X_TIMER_FLAG_ONCE,
                     _ch_select_view_show_notification_cb_fct,
                     NULL);
    }

}

VOID a_ch_select_view_notification(VOID)
{
    nav_request_context_switch(_ch_select_view_show_notification_timer,NULL, NULL,NULL);
}

static VOID _ch_select_view_toast_hide_cd_fct (HANDLE_T  pt_tm_handle,
                                                      VOID*     pv_tag)
{
   ch_select_view_toast_msg_hide();
   return;
}


INT32 ch_select_view_toast_msg_show(UTF16_T*  pw2s_string)
{
    INT32                   i4_ret  = 0;
    UTF16_T*                pw2s_msg = pw2s_string;
    UINT8                   ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;

    DBG_LOG_PRINT((">> [%s][%d] \n", __FUNCTION__, __LINE__));

    /* create toast osd */
    if (pt_this->h_toast_view == NULL_HANDLE)
    {
        TOAST_INIT_PARAM_T  t_toast_init;
        c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));

        t_toast_init.e_toast_style  = TOAST_STYLE_MSG_WITH_MULTI_ICON;
        t_toast_init.h_canvas       = pt_this->h_canvas;
        t_toast_init.t_custom_setting.u.t_msg_with_multi_icon_init.e_msg_type = TOAST_MSG_TYPE_NO_WARNING_ICON;
        t_toast_init.t_custom_setting.u.t_msg_with_multi_icon_init.ui1_text_align = WGL_HTS_JUSTIF_CENTER;

        i4_ret = a_toast_create(&t_toast_init, &(pt_this->h_toast_view));
        if (OSR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[%s][%d] a_toast_create failed !!!!\n", __FUNCTION__, __LINE__));
            return NAVR_FAIL;
        }
    }

    TOAST_CUSTOMIZATION_DATA_T  t_custom_data;
    c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));
    if (pw2s_msg == NULL)
    {
        pw2s_msg = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_USE_CHANGE_CHANNEL_NOTIFICATION_BT_CONNECTED);
    }
    t_custom_data.u.t_msg_with_multi_icon_init.w2s_msg_str   = (VOID*)pw2s_msg;
    t_custom_data.u.t_msg_with_multi_icon_init.h_insert_img1  = h_g_nav_img_toast_msg_icon_ok_key;
    t_custom_data.u.t_msg_with_multi_icon_init.h_insert_img2  = h_g_nav_img_toast_msg_icon_arrow_up;
    t_custom_data.u.t_msg_with_multi_icon_init.h_insert_img3  = h_g_nav_img_toast_msg_icon_arrow_down;

    if (c_wgl_float(pt_this->h_toast_view, TRUE, FALSE) != WGLR_OK) {
        DBG_ERROR(("[NAV][%s][%d] fail.\r\n", __FUNCTION__, __LINE__));
    }

    i4_ret = a_toast_show(pt_this->h_toast_view, &t_custom_data);
    if (TOASTR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("a_toast_show failed !!!!\n"));
        return NAVR_FAIL;
    }

    if(h_ch_select_toast_msg_timer != NULL_HANDLE)
    {
        DBG_LOG_PRINT(("[%s][%d] re-start h_ch_select_toast_msg_timer \n", __FUNCTION__, __LINE__));
        c_timer_stop(h_ch_select_toast_msg_timer);
        c_timer_start(h_ch_select_toast_msg_timer,
                    5000,
                    X_TIMER_FLAG_ONCE,
                    _ch_select_view_toast_hide_cd_fct,
                    NULL);
    }

    if (FALSE == pt_this->b_showing_toast)
    {
        pt_this->b_showing_toast = TRUE;

    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_tts_str[256] = {0};

        c_uc_w2s_strcpy(w2s_tts_str, (UTF16_T*)L"Press OK key to enter channel numbers. Press UP or DOWN to change channels.");

        a_app_tts_play(w2s_tts_str, c_uc_w2s_strlen(w2s_tts_str));
    #endif
    }

   a_cfg_cust_get_zoom_status(&ui1_zoom_mode);
   if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
   {/*record DTV03027147:show channel numbers pad*/
      DBG_LOG_PRINT(("[ZOOM] %s(), e_ch_select_pre_sector = %d.\n\r", __FUNCTION__, ZOOM_SECTOR_ITEM_2));
      i4_ret = a_nav_zoom_cust_select_sector(ZOOM_SECTOR_ITEM_2,TRUE);
      if(i4_ret != NAVR_OK)
      {
          DBG_LOG_PRINT(("[ZOOM] %s(),select ZOOM_SECTOR_ITEM_7 failed!!.\n\r", __FUNCTION__));
      }
   }

    return NAVR_OK;
}


INT32 ch_select_view_toast_msg_hide(VOID)
{
    INT32                   i4_ret  = 0;

    if (!pt_this->b_showing_toast)
    {
        DBG_LOG_PRINT((" ch_select_view_toast_msg_hide already.\n"));
        return NAVR_OK;
    }

    if (c_wgl_float(pt_this->h_toast_view, FALSE, FALSE) != WGLR_OK) {
        DBG_LOG_PRINT(("[NAV] {%s,%d} fail.\r\n", __FUNCTION__, __LINE__));
    }
    i4_ret = a_toast_hide(pt_this->h_toast_view);
    if (TOASTR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("[NAV] {%s,%d} a_toast_hide failed !!!!\n",__FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }
    c_timer_stop(h_ch_select_toast_msg_timer);
    pt_this->b_showing_toast = FALSE;

    return NAVR_OK;
}


static INT32 _select_view_digit_pad_create_timer(CH_SELECT_VIEW*      pt_this)
{
    INT32 i4_ret;

    pt_this->ui4_hide_timeout = DIGIT_PAD_DISPLAY_TIMER;
    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK)
    {
        return NAVR_FAIL;
    }

    pt_this->ui4_sel_timeout = CH_CHANGE_TIMER_DELAY;
    i4_ret = c_timer_create(&(pt_this->h_select_timer));
    if (i4_ret != OSR_OK)
    {
        return NAVR_FAIL;
    }


    return NAVR_OK;
}

static INT32 _select_view_digit_pad_del_timer(CH_SELECT_VIEW* pt_this)
{
    INT32 i4_ret;
    if (c_handle_valid(pt_this->h_hide_timer) == TRUE)
    {
        i4_ret = c_timer_delete(pt_this->h_hide_timer);
        if (i4_ret != OSR_OK)
        {
            return NAVR_FAIL;
        }
    }

    if (c_handle_valid(pt_this->h_select_timer) == TRUE)
    {
        i4_ret = c_timer_delete(pt_this->h_select_timer);
        if (i4_ret != OSR_OK)
        {
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}


static VOID _select_view_digit_pad_stop_hide_timer(CH_SELECT_VIEW*    pt_this)
{
    INT32 i4_ret;

    if(pt_this->b_hide_timer_active == FALSE)
    {
        return;
    }

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE)
    {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    pt_this->b_hide_timer_active = FALSE;
    if (i4_ret != OSR_OK)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop ch_select_view::h_hide_timer failed!"));
    }
}

static VOID _select_view_digit_pad_reset_hide_timer(CH_SELECT_VIEW*     pt_this)
{
    INT32 i4_ret;

    _select_view_digit_pad_stop_hide_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    pt_this->ui4_hide_timeout,
                    X_TIMER_FLAG_ONCE,
                    _select_view_digit_pad_timer_hide_nfy,
                    NULL
                    );

    if (i4_ret != OSR_OK)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start ch_select_view::h_select_timer failed!"));

    }
    pt_this->b_hide_timer_active = TRUE;
}

static VOID _select_view_digit_pad_do_hide_timeout (
                    VOID*                       pv_unused0,
                    VOID*                       pv_unused1,
                    VOID*                       pv_unused2
                    )
{
    _ch_select_view_digit_pad_key_event_nfy(DIGIT_PAD_NAV_BACK, NULL);
}

static VOID _select_view_digit_pad_timer_hide_nfy(HANDLE_T     h_timer)
{
    /* execute in timer's thread context */
    nav_request_context_switch((nav_context_switch_nfy_fct)_select_view_digit_pad_do_hide_timeout, NULL, NULL, NULL);
}



static VOID _select_view_digit_pad_stop_sel_timer(
                    CH_SELECT_VIEW*                pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_select_timer) == FALSE)
    {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_select_timer);
    if (i4_ret != OSR_OK)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop ch_select_view::h_select_timer failed!"));
    }
}

static VOID _select_view_digit_pad_reset_sel_timer(
                    CH_SELECT_VIEW*                pt_this
                    )
{
    INT32 i4_ret;

    _select_view_digit_pad_stop_sel_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_select_timer,
                    pt_this->ui4_sel_timeout,
                    X_TIMER_FLAG_ONCE,
                    _select_view_digit_pad_timer_sel_nfy,
                    NULL
                    );

    if (i4_ret != OSR_OK)
    {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start ch_select_view::h_select_timer failed!"));

    }
}

static VOID _select_view_digit_pad_do_sel_timeout (
                    VOID*                       pv_unused0,
                    VOID*                       pv_unused1,
                    VOID*                       pv_unused2
                    )
{
    _ch_select_view_digit_pad_key_event_nfy(DIGIT_PAD_BUTTON_OK, NULL);
}

static VOID _select_view_digit_pad_timer_sel_nfy(
                    HANDLE_T                    h_timer
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch((nav_context_switch_nfy_fct)_select_view_digit_pad_do_sel_timeout, NULL, NULL, NULL);
}


