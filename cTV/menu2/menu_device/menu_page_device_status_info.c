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
#include "u_sb_atsc_eng.h"
#include "u_sb_cqam_eng.h"
#include "u_sb_ntsc_eng.h"
#include "u_cli.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svctx.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_sb.h"
#include "c_dt.h"
#include "c_net_p2p_ctl.h"
#include "c_aee.h"

#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu_page_device_setting.h"
#include "menu_device.h"
#include "menu_page_device_status_info.h"
#include "wfd/wfd_dev_list.h"

#include "res/wdk/wdk_img.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/dev_db/a_dev_db_custom.h"

#ifdef APP_WFD_SUPPORT
#include "wfd_client_export.h"
#endif
#include "wfrrc_interface.h"

#include "c_rm.h"
#include "u_drv_cust.h"
#include "menu2/menu_dbg.h"

extern UINT16 menu_device_get_help_txt(UINT8 e_idx);
/*-----------------------------------------------------------------------------
                    defines, typedefs, enums
 ----------------------------------------------------------------------------*/

typedef struct _MENU_DEVICE_STATUS_INFO_PAGE_DATA_T
{
    HANDLE_T     h_cnt_frm;
    HANDLE_T     h_txt_device_name;
    HANDLE_T     h_txt_status_info;
    HANDLE_T     h_btn_unpair;
    HANDLE_T     h_name_input;
    HANDLE_T     h_confirm_dialog_frm;
    HANDLE_T     h_confirm_dialog_title;
    HANDLE_T     h_confirm_dialog_ok;

    HANDLE_T     h_timer;
    MENU_DEVICE_PAGE_DEVICE_INFO_T t_device_info;

    UTF16_T      w2s_dlg_text[MENU_DEVICE_SETTING_REMOTE_NAME_LEN+1];

    BOOL         b_paired;
}MENU_DEVICE_STATUS_INFO_PAGE_DATA_T;

/*-----------------------------------------------------------------------------
                 data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_device_status_info;
static MENU_DEVICE_STATUS_INFO_PAGE_DATA_T t_g_device_status_info_page_data;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _device_status_info_text_create(HANDLE_T    h_parent,
                            HANDLE_T*               ph_widget,
                            const GL_RECT_T*        pt_rect,
                            wgl_widget_proc_fct     pf_wgt_proc);
static INT32 _device_status_info_txt_create(VOID);
static INT32 _device_status_info_page_confirm_dialog_hide(BOOL  b_repaint);

/*-----------------------------------------------------------------------------
                    function implementations
 ----------------------------------------------------------------------------*/
static INT32 _device_status_info_listbox_create(
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
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;
	GL_COLOR_T          		t_color_txt_disable = { 255, {128}, {128}, {128}};

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
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
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
    t_inset.i4_left   = MENU_DEVICE_SETTING_LB_INSET_LEFT;
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
    t_inset.i4_right  = MENU_DEVICE_SETTING_LB_INSET_RIGHT;
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
    t_clr_info.u_color_data.t_standard.t_disable    =t_color_txt_disable;
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
    t_clr_elem.t_disable            = t_g_menu_color_white;
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
    c_memset(&t_hlt_elem_effect, 0, sizeof(WGL_LB_HLT_ELEM_EFFECT_T));
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

static INT32 _device_status_info_name_input_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    UINT32 ui4_keycode = (UINT32)param1;
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    i4_ret = menu_device_page_nav_go(
                                     NAV_NAME_INPUT_PAGE_FROM_INFO_STATUS_PAGE,
                                     NULL);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_UP:
                {
                    i4_ret = menu_set_focus_on_backbar(TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_DOWN:
                {
                    if (pt_this->b_paired)
                    {
                        i4_ret = c_wgl_set_focus(pt_this->h_btn_unpair,
                                                 WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        i4_ret = menu_help_tip_keytip_set_focus(h_widget, 0 , FALSE);
                        MENU_LOG_ON_FAIL(i4_ret);
                        menu_pm_repaint();
                    }
                }
                    break;

                case BTN_RETURN:
                {
                    i4_ret = menu_device_page_nav_go(NAV_DEVICE_SETTING_PAGE_FROM_STATUS_INFO_PAGE,
                                                     NULL);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                default:
                    break;
            }
        }
            break;

     case WGL_MSG_GET_FOCUS:
     {
        menu_set_and_show_help_tip(MENU_TEXT(menu_device_get_help_txt(MENU_DEVICE_TYPE_IDX_NAME)));
        break;
     }

        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static BOOL _is_3rd_app_running(VOID)
{
    APP_TV_NET_SVC_STATUS t_svc_state = APP_TV_NET_SVC_STATUS_PAUSED;

    t_svc_state = a_tv_net_get_tv_svc_status();
    if(APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static INT32 _device_status_info_add_name_input(VOID)
{
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    INT32               i4_ret = MENUR_OK;
    WGL_LB_ITEM_T   at_items[2];
    CHAR            ac_user_name[32+1] = {0};
    UTF16_T         w2s_user_name[32+1] = {0};

    i4_ret = c_wgl_do_cmd(pt_this->h_name_input,
                          WGL_CMD_LB_DEL_ALL, NULL, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_user_name, 0, sizeof(w2s_user_name));
    a_cfg_custom_get_inp_name(pt_this->t_device_info.u_device_data.t_input.ui1_input_src_idx,
                              ac_user_name);
    if (c_strlen(ac_user_name) > 0)
    {
        c_uc_ps_to_w2s(ac_user_name, w2s_user_name,
                       MENU_DEVICE_SETTING_INPUT_USER_NAME_LEN);
    }

    c_memset(at_items, 0, 2*sizeof(WGL_LB_ITEM_T));
    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = MENU_TEXT(MLM_MENU_KEY_NAME_INPUT);//L"Name Input";
    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_user_name;
    i4_ret = c_wgl_do_cmd(pt_this->h_name_input,
                          WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_name_input,
                                   WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (TRUE == _is_3rd_app_running())
    {
        c_wgl_enable(pt_this->h_name_input, FALSE);
    }
    else
    {
        c_wgl_enable(pt_this->h_name_input, TRUE);
    }

    return i4_ret;
}

static INT32 _device_status_info_name_input_create (VOID)
{
    INT32               i4_ret = MENUR_OK;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[2];
    GL_RECT_T           t_rect;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    c_memset(at_cols, 0, 2*sizeof(WGL_LB_COL_INIT_T));
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = MENU_DEVICE_SETTING_DEV_DISP_NAME_ALIGN;
    at_cols[0].ui2_max_text_len = MENU_DEVICE_SETTING_DEV_DISP_NAME_MAX_TEXT_LEN;
    at_cols[0].ui2_width        = MENU_DEVICE_SETTING_DEV_DISP_NAME_COL_WIDTH;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = MENU_DEVICE_SETTING_DEV_USER_NAME_ALIGN;
    at_cols[1].ui2_max_text_len = MENU_DEVICE_SETTING_DEV_USER_NAME_MAX_TEXT_LEN;
    at_cols[1].ui2_width        = MENU_DEVICE_SETTING_DEV_USER_NAME_COLUMN_WIDTH;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = MENU_DEVICE_SETTING_DEV_LIST_ELEM_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_DEVICE_STATUS_INFO_BTN_UNPAIR_X,
                     (MENU_DEVICE_STATUS_INFO_BTN_UNPAIR_Y-43),
                     MENU_DEVICE_STATUS_INFO_BTN_UNPAIR_W,
                     MENU_DEVICE_STATUS_INFO_BTN_UNPAIR_H);
    i4_ret = _device_status_info_listbox_create(pt_this->h_cnt_frm,
                                    &t_rect,
                                    _device_status_info_name_input_proc_fct,
                                    &t_lb_init,
                                    NULL,
                                    &pt_this->h_name_input);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

#ifdef APP_WIFI_REMOTE

static INT32 _menu_device_status_info_page_atoi(const CHAR* ps)
{
    INT32  i4_total;

    i4_total = 0;
    while ( *ps != 0 )
    {
        if ( *ps >= '0' && *ps <= '9' )
        {
            /* accumulate digit */
            i4_total = 10 * i4_total + (*ps - '0');
            ps++; /* get next char */
        }
        else /* not a digit char */
        {
            return (-1);
        }
    }

    return i4_total;
}


#if 0
static INT32 _menu_device_status_info_page_atohtoi(const CHAR* ps)
{
    INT32  i4_total = 0;

    while((*ps != '\r') && (*ps != '\n') && (*ps != '\0'))
    {
        if ((*ps >= '0') && (*ps <= '9'))
        {
            i4_total = 16 * i4_total + (*ps - '0');
        }
        else if (('A' == *ps) || ('a' == *ps))
        {
            i4_total = 16 * i4_total + 10;
        }
        else if (('B' == *ps) || ('b' == *ps))
        {
            i4_total = 16 * i4_total + 11;
        }
        else if (('C' == *ps) || ('c' == *ps))
        {
            i4_total = 16 * i4_total + 12;
        }
        else if (('D' == *ps) || ('d' == *ps))
        {
            i4_total = 16 * i4_total + 13;
        }
        else if (('E' == *ps) || ('e' == *ps))
        {
            i4_total = 16 * i4_total + 14;
        }
        else if (('F' == *ps) || ('f' == *ps))
        {
            i4_total = 16 * i4_total + 15;
        }

        ps++;
    }

    return i4_total;
}
#endif

static VOID _menu_device_status_info_page_itoa(UTF16_T* w2s_dst,
                                                             INT32 i4_src,
                                                             UINT32 ui4_dst_len)
{
    CHAR    s_buf[32] = {0};
    c_sprintf(s_buf, "%d",  i4_src);
    c_uc_ps_to_w2s(s_buf, w2s_dst, ui4_dst_len);
}
#endif

static INT32 _device_status_info_txt_create(VOID)
{
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T       t_rect;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_DEVICE_STATUS_INFO_PAGE_DEV_STATUS_INFO_X,
                     MENU_DEVICE_STATUS_INFO_PAGE_DEV_STATUS_INFO_Y,
                     MENU_DEVICE_STATUS_INFO_PAGE_DEV_STATUS_INFO_W,
                     MENU_DEVICE_STATUS_INFO_PAGE_DEV_STATUS_INFO_H);
    i4_ret = _device_status_info_text_create(pt_this->h_cnt_frm,
                                              &pt_this->h_txt_status_info,
                                              &t_rect,
                                              NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_txt_status_info,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_TECHNICAL_INFO)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_TECHNICAL_INFO))));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

#ifdef APP_WIFI_REMOTE
INT32 menu_get_remote_name(UTF16_T* pw2s_name)
{
    CHAR    s_name[MENU_DEVICE_STATUS_INFO_REMOTE_NAME_LEN] = {0};
    INT32    i4_ret = MENUR_OK;
    i4_ret = c_get_remote_info(WFRCCMsg_DeviceName, s_name);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_ps_to_w2s(s_name, pw2s_name,
                    MENU_DEVICE_STATUS_INFO_REMOTE_NAME_LEN);
    return i4_ret;
}

INT32 menu_get_wifi_remote_battery(UTF16_T* pw2s_battery)
{
    CHAR            s_battery[5] = {0};
    UINT8           ui1_idx = 0;
    INT32    i4_ret = MENUR_OK;

    i4_ret = c_get_remote_info(WFRCCMsg_BatteryLevel, s_battery);

    if (i4_ret != MENUR_OK)
    {
        c_uc_w2s_strncpy(pw2s_battery, L"N/A",
                        MENU_DEVICE_STATUS_INFO_REMOTE_BATTERY_LEN);
        return MENUR_OK;
    }
    else
        {
        if (s_battery[0] == '\0')
    {
             c_uc_w2s_strncpy(pw2s_battery, L"N/A",
                        MENU_DEVICE_STATUS_INFO_REMOTE_BATTERY_LEN);
        return MENUR_OK;
    }

    for (ui1_idx=0; ui1_idx < 4; ui1_idx++)
    {
            if (s_battery[ui1_idx] == '\0')
        {
                s_battery[ui1_idx] = '%';
                s_battery[ui1_idx + 1] = '\0';
        break;
        }
    }

        DBG_INFO(("<%s>%s: s_battery=%s\n",__FILE__, __FUNCTION__, s_battery);
        c_uc_ps_to_w2s(s_battery, pw2s_battery,
                    MENU_DEVICE_STATUS_INFO_REMOTE_BATTERY_LEN));
    }

    return MENUR_OK;
}

INT32 menu_get_wifi_remote_mac(UTF16_T* pw2s_mac)
{
    CHAR    s_mac[MENU_DEVICE_STATUS_INFO_REMOTE_MAC_LEN] = {0};
    INT32    i4_ret = MENUR_OK;

    i4_ret = c_get_remote_info(WFRCCMsg_DeviceMAC, s_mac);

    if (i4_ret != MENUR_OK)
    {
        c_uc_w2s_strncpy(pw2s_mac, L"N/A",
                        MENU_DEVICE_STATUS_INFO_REMOTE_MAC_LEN);
        return MENUR_OK;
    }
    else
        {
        if (s_mac[0] == '\0')
            {
              c_uc_w2s_strncpy(pw2s_mac, L"N/A",
                        MENU_DEVICE_STATUS_INFO_REMOTE_MAC_LEN);
    }
        else
        {
    c_uc_ps_to_w2s(s_mac, pw2s_mac,
                    MENU_DEVICE_STATUS_INFO_REMOTE_MAC_LEN);
        }
    }

    return i4_ret;
}

INT32 menu_get_wifi_remote_version(UTF16_T* pw2s_ver)
{
    INT32          i4_ret = MENUR_OK;
    CHAR           s_remote_ver[5] = {0};
    INT32          i4_remote_ver = 0;
    INT32          i4_remote_ver_main = 0;
    INT32          i4_remote_ver_sub = 0;
    UTF16_T        w2s_remote_ver_main[MENU_DEVICE_STATUS_INFO_REMOTE_VER_LEN] = {0};
    UTF16_T        w2s_remote_ver_sub[MENU_DEVICE_STATUS_INFO_REMOTE_VER_LEN] = {0};

    i4_ret = c_get_remote_info(WFRCCMsg_DeviceFWVersion, s_remote_ver);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_remote_ver = _menu_device_status_info_page_atoi(s_remote_ver);

    DBG_INFO(("\n%s,%s,%d,s_remote_ver=%s,i4_remote_ver=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                s_remote_ver, i4_remote_ver));

    if (i4_remote_ver > 100)
    {
        i4_remote_ver_main = i4_remote_ver / 100;
        i4_remote_ver_sub = i4_remote_ver % 100;
    }
    else
    {
        i4_remote_ver_main = 0;
        i4_remote_ver_sub = i4_remote_ver;
    }

    if (i4_remote_ver_main == 0)
    {
        c_uc_w2s_strcat(pw2s_ver, L"N/A");
    }
    else
    {
       c_uc_w2s_strcpy(pw2s_ver, L"V");
    _menu_device_status_info_page_itoa(w2s_remote_ver_main, i4_remote_ver_main,
                                       MENU_DEVICE_STATUS_INFO_REMOTE_VER_LEN);

    _menu_device_status_info_page_itoa(w2s_remote_ver_sub, i4_remote_ver_sub,
                                       MENU_DEVICE_STATUS_INFO_REMOTE_VER_LEN);

    c_uc_w2s_strcat(pw2s_ver, w2s_remote_ver_main);
    c_uc_w2s_strcat(pw2s_ver, L".");
    c_uc_w2s_strcat(pw2s_ver, w2s_remote_ver_sub);
    }

    return i4_ret;
}

static INT32 _show_remote_status_info(VOID)
{
    INT32           i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    UTF16_T        w2s_battery[MENU_DEVICE_STATUS_INFO_REMOTE_BATTERY_LEN] = {0};
    UTF16_T        w2s_mac[MENU_DEVICE_STATUS_INFO_REMOTE_MAC_LEN] = {0};
    UTF16_T        w2s_ver[MENU_DEVICE_STATUS_INFO_REMOTE_VER_LEN] = {0};
    UTF16_T*       pw2s_status_info = NULL;

    i4_ret = c_wgl_set_visibility(pt_this->h_name_input,
                                   WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    do
    {
        pw2s_status_info = c_mem_alloc((MENU_DEVICE_STATUS_INFO_INFO_LEN+1)*sizeof(UTF16_T));
        if (NULL == pw2s_status_info)
        {
            DBG_ERROR(("\n%s,%s,%d,c_mem_alloc failed\n",
                        __FILE__, __FUNCTION__, __LINE__));
        }

        i4_ret = menu_get_wifi_remote_battery(w2s_battery);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_get_wifi_remote_mac(w2s_mac);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_get_wifi_remote_version(w2s_ver);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strcpy(pw2s_status_info, MENU_TEXT(MLM_MENU_KEY_TECHNICAL_INFO));
        c_uc_w2s_strcat(pw2s_status_info, L"\n");
        c_uc_w2s_strcat(pw2s_status_info, MENU_TEXT(MLM_MENU_KEY_SYS_INFO_BATTERY));
        c_uc_w2s_strcat(pw2s_status_info, L" ");
        c_uc_w2s_strcat(pw2s_status_info, w2s_battery);
        c_uc_w2s_strcat(pw2s_status_info, L"\n");
        c_uc_w2s_strcat(pw2s_status_info, MENU_TEXT(MLM_MENU_KEY_SYS_INFO_MAC_ADDR));
        c_uc_w2s_strcat(pw2s_status_info, L" ");
        c_uc_w2s_strcat(pw2s_status_info, w2s_mac);
        c_uc_w2s_strcat(pw2s_status_info, L"\n");
        c_uc_w2s_strcat(pw2s_status_info, MENU_TEXT(MLM_MENU_KEY_VERSION));
        c_uc_w2s_strcat(pw2s_status_info, L" ");
        c_uc_w2s_strcat(pw2s_status_info, w2s_ver);
    }while(0);

    i4_ret = c_wgl_do_cmd(pt_this->h_txt_status_info,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)pw2s_status_info,
                          (VOID*)c_uc_w2s_strlen(pw2s_status_info));
    MENU_LOG_ON_FAIL(i4_ret);

    if (pw2s_status_info)
    {
        c_mem_free(pw2s_status_info);
        pw2s_status_info = NULL;
    }

    return i4_ret;
}
#endif
static INT32 _show_input_status_info(VOID)
{
    INT32           i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    i4_ret = _device_status_info_add_name_input();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_txt_status_info,
                                   WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _show_miracast_status_info(VOID)
{
    INT32           i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    NAV_WFD_DEVICE_INFO_T  t_device_info;
    CHAR s_status_info[MENU_DEVICE_STATUS_INFO_INFO_LEN+1] = {0};
    UTF16_T w2s_status_info[MENU_DEVICE_STATUS_INFO_INFO_LEN+1] = {0};

    i4_ret = c_wgl_set_visibility(pt_this->h_txt_device_name,
                                   WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_name_input,
                                   WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_WFD_SUPPORT
    if (a_cfg_custom_get_wfd_support()==TRUE)
    {
        i4_ret = a_wfd_device_info_get_device_info_by_index(pt_this->t_device_info.u_device_data.t_miracast.ui1_miracast_idx,
                                                             &t_device_info);
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif

    c_strncpy(s_status_info, t_device_info.s_device_name, DEVICE_INFO_MAX_NAME_LEN);
    c_strcat(s_status_info, "\n");
    c_strncat(s_status_info, t_device_info.s_device_mac, DEVICE_INFO_MAX_MAC_LEN);

    DBG_INFO(("\n%s,%s,%d,s_status_info=%s\n",
               __FILE__, __FUNCTION__, __LINE__, s_status_info));

    c_uc_ps_to_w2s(s_status_info, w2s_status_info,
                   MENU_DEVICE_STATUS_INFO_INFO_LEN);

    i4_ret = c_wgl_do_cmd(pt_this->h_txt_status_info,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)w2s_status_info,
                          (VOID*)c_uc_w2s_strlen(w2s_status_info));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
#ifdef APP_CEC_MENU
static INT32 _show_cec_dev_name_info(VOID)
{
    INT32           						i4_ret = MENUR_OK;
    WGL_LB_ITEM_T   at_items[2];
    CHAR            ac_user_name[32+1] = {0};
    UTF16_T         w2s_user_name[32+1] = {0};
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* 	pt_this = &t_g_device_status_info_page_data;
    UINT8           ui1_cfg_idx = 0;

    i4_ret = menu_device_get_device_info(&pt_this->t_device_info);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_txt_status_info,
                                   WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_do_cmd(pt_this->h_name_input,
                          WGL_CMD_LB_DEL_ALL, NULL, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_user_name, 0, sizeof(w2s_user_name));
    ui1_cfg_idx = menu_device_cec_list_idx_to_cfg_idx(pt_this->t_device_info.u_device_data.t_cec_dev.ui1_cec_dev_idx);

    a_cfg_custom_get_cec_name(ui1_cfg_idx,
                              ac_user_name);
    if (c_strlen(ac_user_name) > 0)
    {
        c_uc_ps_to_w2s(ac_user_name, w2s_user_name,
                       MENU_DEVICE_SETTING_INPUT_USER_NAME_LEN);
    }

    c_memset(at_items, 0, 2*sizeof(WGL_LB_ITEM_T));
    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = MENU_TEXT(MLM_MENU_KEY_NAME_INPUT);//L"Name Input";
    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_user_name;
    i4_ret = c_wgl_do_cmd(pt_this->h_name_input,
                          WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_name_input,
                                   WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_txt_device_name,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pt_this->t_device_info.u_device_data.t_cec_dev.pw2s_cec_osd_name),
                          WGL_PACK(c_uc_w2s_strlen(pt_this->t_device_info.u_device_data.t_cec_dev.pw2s_cec_osd_name)));
    MENU_LOG_ON_FAIL(i4_ret);

    if (TRUE == _is_3rd_app_running())
    {
        c_wgl_enable(pt_this->h_name_input, FALSE);
    }
    else
    {
        c_wgl_enable(pt_this->h_name_input, TRUE);
    }

    return i4_ret;
}
#endif

#ifdef APP_WIFI_REMOTE
static INT32 _show_remote_name_info(VOID)
{
    INT32           i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    UTF16_T         w2s_remote_name[MENU_DEVICE_STATUS_INFO_REMOTE_NAME_LEN] = {0};
    UTF16_T         w2s_remote_info[MENU_DEVICE_STATUS_INFO_NAME_LEN] = {0};

    i4_ret = menu_get_remote_name(w2s_remote_name);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strcpy(w2s_remote_info, w2s_remote_name);
    c_uc_w2s_strcat(w2s_remote_info, L"\n");
    c_uc_w2s_strcat(w2s_remote_info, MENU_TEXT(MLM_MENU_KEY_REMOTE));
    c_uc_w2s_strcat(w2s_remote_info, L"\n");
    c_uc_w2s_strcat(w2s_remote_info, MENU_TEXT(MLM_MENU_KEY_PAIRED));

    i4_ret = c_wgl_do_cmd(pt_this->h_txt_device_name,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_remote_info),
                          WGL_PACK(c_uc_w2s_strlen(w2s_remote_info)));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
#endif

static INT32 _get_input_name(UTF16_T* pw2s_input_name)
{
    INT32           i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    i4_ret = menu_device_get_device_info(&pt_this->t_device_info);
    MENU_LOG_ON_FAIL(i4_ret);

    if (0)
    {
        c_uc_w2s_strncpy(pw2s_input_name,
                        pt_this->t_device_info.u_device_data.t_input.pw2s_user_name,
                        MENU_DEVICE_STATUS_INFO_INPUT_NAME_LEN);
    }
    else
    {
        c_uc_w2s_strncpy(pw2s_input_name,
                        pt_this->t_device_info.u_device_data.t_input.pw2s_disp_name,
                        MENU_DEVICE_STATUS_INFO_INPUT_NAME_LEN);
    }

    return i4_ret;
}

static INT32 _get_input_type_brand_model(UTF16_T* pw2s_type,
                                             UTF16_T* pw2s_brand,
                                             UTF16_T* pw2s_model)
{
    INT32           i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    CHAR* ps_type_name  = NULL;
    CHAR* ps_brand_name = NULL;
    CHAR* ps_model_name = NULL;
    CHAR* ps_codeset     = NULL;
    UTF16_T* pw2s_temp = NULL;

    do
    {
        ps_type_name = c_mem_alloc((MENU_DEVICE_STATUS_INFO_INPUT_TYPE_LEN+1)*sizeof(CHAR));
        if (NULL == ps_type_name)
        {
            DBG_ERROR(("\n%s,%s,%d,c_mem_alloc() failed\n",
                        __FILE__, __FUNCTION__, __LINE__));
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        ps_brand_name = c_mem_alloc((MENU_DEVICE_STATUS_INFO_INPUT_BRAND_LEN+1)*sizeof(CHAR));
        if (NULL == ps_brand_name)
        {
            DBG_ERROR(("\n%s,%s,%d,c_mem_alloc() failed\n",
                        __FILE__, __FUNCTION__, __LINE__));
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        ps_model_name = c_mem_alloc((MENU_DEVICE_STATUS_INFO_INPUT_MODEL_LEN+1)*sizeof(CHAR));
        if (NULL == ps_model_name)
        {
            DBG_ERROR(("\n%s,%s,%d,c_mem_alloc() failed\n",
                        __FILE__, __FUNCTION__, __LINE__));
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        ps_codeset = c_mem_alloc((MENU_DEVICE_STATUS_INFO_INPUT_CODESET_LEN+1)*sizeof(CHAR));
        if (NULL == ps_codeset)
        {
            DBG_ERROR(("\n%s,%s,%d,c_mem_alloc() failed\n",
                        __FILE__, __FUNCTION__, __LINE__));
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        if (a_cfg_custom_get_wifi_remote_support())
        {
            i4_ret = a_cfg_custom_get_device_info(pt_this->t_device_info.u_device_data.t_input.ui1_input_src_idx,
                                                  ps_type_name, ps_brand_name,
                                                  ps_model_name, ps_codeset);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        if (c_strlen(ps_type_name) > 0)
        {
            a_dev_db_dev_type_name_ps_to_w2s(ps_type_name, &pw2s_temp);
            c_uc_w2s_strncpy(pw2s_type, pw2s_temp,
                             MENU_DEVICE_STATUS_INFO_INPUT_TYPE_LEN);
        }

        c_uc_ps_to_w2s(ps_brand_name, pw2s_brand,
                       MENU_DEVICE_STATUS_INFO_INPUT_BRAND_LEN);

        c_uc_ps_to_w2s(ps_model_name, pw2s_model,
                       MENU_DEVICE_STATUS_INFO_INPUT_MODEL_LEN);
    }while(0);

    if (ps_type_name)
    {
        c_mem_free(ps_type_name);
        ps_type_name = NULL;
    }

    if (ps_brand_name)
    {
        c_mem_free(ps_brand_name);
        ps_brand_name = NULL;
    }

    if (ps_model_name)
    {
        c_mem_free(ps_model_name);
        ps_model_name = NULL;
    }

    if (ps_codeset)
    {
        c_mem_free(ps_codeset);
        ps_codeset = NULL;
    }

    return i4_ret;
}

static INT32 _show_input_name_info(VOID)
{
    INT32           i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    UTF16_T         w2s_input_name[MENU_DEVICE_STATUS_INFO_INPUT_NAME_LEN] = {0};
    UTF16_T         w2s_input_type[MENU_DEVICE_STATUS_INFO_INPUT_TYPE_LEN] = {0};
    UTF16_T         w2s_input_brand[MENU_DEVICE_STATUS_INFO_INPUT_BRAND_LEN] = {0};
    UTF16_T         w2s_input_model[MENU_DEVICE_STATUS_INFO_INPUT_MODEL_LEN] = {0};
    UTF16_T         w2s_input_info[MENU_DEVICE_STATUS_INFO_NAME_LEN] = {0};

    i4_ret = _get_input_name(w2s_input_name);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _get_input_type_brand_model(w2s_input_type,
                                    w2s_input_brand,
                                    w2s_input_model);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strcpy(w2s_input_info, w2s_input_name);
    c_uc_w2s_strcat(w2s_input_info, L"\n");
    c_uc_w2s_strcat(w2s_input_info, w2s_input_type);
    c_uc_w2s_strcat(w2s_input_info, L"\n");
    c_uc_w2s_strcat(w2s_input_info, w2s_input_brand);
    c_uc_w2s_strcat(w2s_input_info, L"\n");
    c_uc_w2s_strcat(w2s_input_info, w2s_input_model);

    i4_ret = c_wgl_do_cmd(pt_this->h_txt_device_name,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_input_info),
                          WGL_PACK(c_uc_w2s_strlen(w2s_input_info)));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _show_soundbar_name_info(VOID)
{
    INT32           i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    UTF16_T         w2s_input_type[MENU_DEVICE_STATUS_INFO_INPUT_TYPE_LEN] = {0};
    UTF16_T         w2s_input_brand[MENU_DEVICE_STATUS_INFO_INPUT_BRAND_LEN] = {0};
    UTF16_T         w2s_input_model[MENU_DEVICE_STATUS_INFO_INPUT_MODEL_LEN] = {0};
    UTF16_T         w2s_input_info[MENU_DEVICE_STATUS_INFO_NAME_LEN] = {0};

    i4_ret = _get_input_type_brand_model(w2s_input_type,
                                    w2s_input_brand,
                                    w2s_input_model);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strcat(w2s_input_info, w2s_input_type);
    c_uc_w2s_strcat(w2s_input_info, L"\n");
    c_uc_w2s_strcat(w2s_input_info, w2s_input_brand);
    c_uc_w2s_strcat(w2s_input_info, L"\n");
    c_uc_w2s_strcat(w2s_input_info, w2s_input_model);

    i4_ret = c_wgl_do_cmd(pt_this->h_txt_device_name,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_input_info),
                          WGL_PACK(c_uc_w2s_strlen(w2s_input_info)));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _show_soundbar_status_info(VOID)
{
    INT32           i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    i4_ret = c_wgl_set_visibility(pt_this->h_name_input,
                                   WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_txt_status_info,
                                   WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_status_info_page_show_ui(
                                MENU_DEVICE_TYPE_T e_current_device_type)
{
    INT32           i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    if (MENU_DEVICE_TYPE_REMOTE == e_current_device_type)
    {
#ifdef APP_WIFI_REMOTE
        i4_ret = _show_remote_name_info();
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = _show_remote_status_info();
        MENU_LOG_ON_FAIL(i4_ret);
#endif
    }


    else if (MENU_DEVICE_TYPE_INPUT == e_current_device_type)
    {
        i4_ret = _show_input_name_info();
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = _show_input_status_info();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    else if (MENU_DEVICE_TYPE_MIRACAST == e_current_device_type)
    {
        i4_ret = _show_miracast_status_info();
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if (MENU_DEVICE_TYPE_SOUNDBAR == e_current_device_type)
    {
        i4_ret = _show_soundbar_name_info();
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = _show_soundbar_status_info();
        MENU_LOG_ON_FAIL(i4_ret);
    }
#ifdef APP_CEC_MENU
    else if (MENU_DEVICE_TYPE_CEC_DEV== e_current_device_type)
    {
        i4_ret = _show_cec_dev_name_info();
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif
    else
    {
        DBG_ERROR(("\n%s,%s,%d,e_current_device_type=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    e_current_device_type));
        return MENUR_INV_ARG;
    }

    i4_ret = c_wgl_do_cmd(pt_this->h_btn_unpair,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_UNPAIR)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_status_info_text_create(HANDLE_T    h_parent,
                            HANDLE_T*               ph_widget,
                            const GL_RECT_T*        pt_rect,
                            wgl_widget_proc_fct     pf_wgt_proc)
{
    INT32               i4_ret = MENUR_OK;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    UINT8               ui1_frame_alpha = 255;
    WGL_INSET_T         t_inset;
    UINT32              ui4_type = WGL_STL_TEXT_MULTILINE |
                                   WGL_STL_TEXT_MAX_2048 |
                                   WGL_STL_TEXT_MAX_DIS_20_LINE |
                                   WGL_STL_GL_NO_BK;

    i4_ret = menu_get_osd_alpha(&ui1_frame_alpha);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_create_widget(h_parent,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                pt_rect,
                                pf_wgt_proc,
                                ui1_frame_alpha,
                                (VOID*)ui4_type,
                                NULL,
                                ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = MENU_DEVICE_STATUS_INFO_TEXT_INSET_LEFT;
    t_inset.i4_right    = MENU_DEVICE_STATUS_INFO_TEXT_INSET_RIGHT;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_TEXT_SET_CNT_INSET,
                           &t_inset,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_GL_SET_FONT,
                            WGL_PACK(&t_fnt_info),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Color */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _device_status_info_btn_create(HANDLE_T h_parent,
                                    GL_RECT_T*           pt_rect,
                                    wgl_widget_proc_fct  pf_wdgt_proc,
                                    UTF16_T*  pw2s_str,
                                    HANDLE_T* ph_widget)
{
    INT32               i4_ret = MENUR_OK;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_color_info = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_FONT_INFO_T     t_font_info = {0};
    GL_COLOR_T          t_color_txt = { 255, { 255 }, { 255 }, { 255 }};
	GL_COLOR_T			t_color_txt_disable = { 255, {128}, {128}, {128}};

    i4_ret = c_wgl_create_widget(h_parent,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                pt_rect,
                                pf_wdgt_proc,
                                255,
                                NULL,
                                NULL,
                                ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left   = MENU_DEVICE_STATUS_INFO_BTN_INSET_LEFT;
    t_inset.i4_right  = MENU_DEVICE_STATUS_INFO_BTN_INSET_RIGHT;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_push               = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_color_info.e_type = WGL_COLOR_SET_EXTEND;
    t_color_info.u_color_data.t_extend.t_enable = t_color_txt;
    t_color_info.u_color_data.t_extend.t_disable = t_color_txt_disable;
    t_color_info.u_color_data.t_extend.t_highlight = t_color_txt;
    t_color_info.u_color_data.t_extend.t_highlight_inactive = t_color_txt;
    t_color_info.u_color_data.t_extend.t_push = t_color_txt;
    t_color_info.u_color_data.t_extend.t_push_unhighlight = t_color_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(& t_color_info));
    MENU_LOG_ON_FAIL(i4_ret);

    c_strncpy(t_font_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_font_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_font_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_font_info.e_font_style = FE_FNT_STYLE_REGULAR;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_font_info),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(MENU_DEVICE_STATUS_INFO_UNPAIR_BTN_ALIGN),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(pw2s_str),
                          WGL_PACK(c_uc_w2s_strlen(pw2s_str)));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_status_info_page_device_name_text_create (VOID)
{
    INT32       i4_ret = MENUR_OK;
    GL_RECT_T   t_rect;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_DEVICE_STATUS_INFO_BTN_DEV_NAME_X,
                     MENU_DEVICE_STATUS_INFO_BTN_DEV_NAME_Y,
                     MENU_DEVICE_STATUS_INFO_BTN_DEV_NAME_W,
                     MENU_DEVICE_STATUS_INFO_BTN_DEV_NAME_H);
    i4_ret = _device_status_info_text_create(pt_this->h_cnt_frm,
                                              &pt_this->h_txt_device_name,
                                              &t_rect,
                                              NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static VOID _wifi_remote_unpair_confirm_dialog_cb_fct(VOID)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = _device_status_info_page_confirm_dialog_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_device_page_nav_go(NAV_DEVICE_SETTING_PAGE_FROM_STATUS_INFO_PAGE,
                                      NULL);
    MENU_LOG_ON_FAIL(i4_ret);
}

static INT32 _device_status_info_page_confirm_dialog_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
        case BTN_SELECT:
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
        {
            menu_device_confirm_dialog_cb_fct  pf_back = NULL;
            INT32           i4_ret;

            i4_ret = c_wgl_do_cmd(h_widget,
                                  WGL_CMD_GL_GET_ATTACH_DATA,
                                  WGL_PACK(&pf_back),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            if(pf_back != NULL)
            {
                pf_back();
            }

            return WGLR_OK;
        }

        default:
            break;
        }

        break;
    }

    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _device_status_info_page_confirm_dialog_create(VOID)
{
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T       t_rect;
    HANDLE_T        h_root_frm = NULL_HANDLE;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    WGL_COLOR_INFO_T  t_clr_info;
    WGL_FONT_INFO_T   t_fnt_info;
    WGL_IMG_INFO_T    t_img_info;
    WGL_INSET_T t_inset = {10, 10, 10, 0};

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_FRAME_X,
                      MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_FRAME_Y,
                      MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_FRAME_W,
                      MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_FRAME_H);

    /* create widget */
    i4_ret = c_wgl_create_widget (h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 0,
                                 &pt_this->h_confirm_dialog_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_bar_background;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_bar_background;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_bar_background;
    i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_frm,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

     SET_RECT_BY_SIZE(&t_rect,
                      MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_TITLE_X,
                      MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_TITLE_Y,
                      MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_TITLE_W,
                      MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_TITLE_H);

     i4_ret = c_wgl_create_widget(pt_this->h_confirm_dialog_frm,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_TRANSP,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)(WGL_STL_TEXT_MAX_128 |WGL_STL_TEXT_MULTILINE),
                                  NULL,
                                  &pt_this->h_confirm_dialog_title);
     if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }

     /* Set Insets */
     i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_title,
                           WGL_CMD_TEXT_SET_CNT_INSET,
                           &t_inset,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     /* Set Alignment */
     i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_title,
                           WGL_CMD_TEXT_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_CENTER,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     /* Set Font */
     c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
     c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
     t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
     t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
     t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
     i4_ret = c_wgl_do_cmd (pt_this->h_confirm_dialog_title,
                            WGL_CMD_GL_SET_FONT,
                            (VOID*)&t_fnt_info,
                            NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
     t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
     i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_title,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(&t_clr_info));
     MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_BTN_OK_X,
                     MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_BTN_OK_Y,
                     MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_BTN_OK_W,
                     MENU_DEVICE_STATUS_INFO_CONFIRM_DIALOG_BTN_OK_H);

    i4_ret = c_wgl_create_widget(pt_this->h_confirm_dialog_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _device_status_info_page_confirm_dialog_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &pt_this->h_confirm_dialog_ok);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_ok,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_ok,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_this->h_confirm_dialog_ok,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_ok,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_ok,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility(pt_this->h_confirm_dialog_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_confirm_dialog_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static VOID _device_status_info_page_do_timer_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = _device_status_info_page_confirm_dialog_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_device_page_nav_go(NAV_DEVICE_SETTING_PAGE_FROM_STATUS_INFO_PAGE,
                                      NULL);
    MENU_LOG_ON_FAIL(i4_ret);
}

static VOID _menu_device_timer_cb_fct (HANDLE_T  pt_tm_handle,
                                    VOID*     pv_tag)
{
    INT32 i4_ret = MENUR_OK;

    i4_ret = menu_async_invoke(_device_status_info_page_do_timer_nfy,
                               NULL, 0, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);
}

static INT32 _device_status_info_page_confirm_dialog_show(
                                    UTF16_T     *w2s_dlg_str,
                                    UTF16_T     *w2s_btn_str,
                                    menu_device_confirm_dialog_cb_fct  pf_back,
                                    BOOL         b_repaint)
{
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_timer_create(&pt_this->h_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_ok,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_dlg_str),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_ok,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_btn_str),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = c_wgl_set_focus(pt_this->h_confirm_dialog_ok,
                             WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_confirm_dialog_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_confirm_dialog_frm,
                               NULL, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_timer_start(pt_this->h_timer, MENU_DEVICE_CONFIRM_DIALOG_TIMEOUT,
                           X_TIMER_FLAG_ONCE, _menu_device_timer_cb_fct, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_status_info_page_confirm_dialog_hide(BOOL  b_repaint)
{
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_timer_stop(pt_this->h_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    if (pt_this->h_timer)
    {
        c_timer_delete(pt_this->h_timer);
        pt_this->h_timer = NULL_HANDLE;
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_confirm_dialog_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_confirm_dialog_frm, NULL, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

extern VOID wfd_app_disconnect_rtsp(VOID);

static INT32 _device_status_info_get_unpair_dlg_text(VOID)
{
    CHAR            s_device_type[MENU_DEVICE_SETTING_REMOTE_NAME_LEN+1]={0};
    UTF16_T         w2s_device_type[MENU_DEVICE_SETTING_REMOTE_NAME_LEN+1]={0};
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    INT32           i4_ret = MENUR_OK;
    CHAR            s_space[8+1] = {0};
    UTF16_T         w2s_space[8+1] = {0};

    c_sprintf(s_space, "  ");
    c_uc_ps_to_w2s(s_space, w2s_space, 8);

    if (MENU_DEVICE_TYPE_INPUT == pt_this->t_device_info.e_current_device_type)
    {
        i4_ret = a_cfg_custom_get_device_type(pt_this->t_device_info.u_device_data.t_input.ui1_input_src_idx,
                                              s_device_type);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if(MENU_DEVICE_TYPE_SOUNDBAR == pt_this->t_device_info.e_current_device_type)
    {
        i4_ret = a_cfg_custom_get_device_type(0,
                                              s_device_type);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    c_uc_ps_to_w2s(s_device_type,w2s_device_type,MENU_DEVICE_SETTING_REMOTE_NAME_LEN);

    c_memset(pt_this->w2s_dlg_text,0,MENU_DEVICE_SETTING_REMOTE_NAME_LEN+1);

    if(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_DEVICE_UNPAIRED_SUCCESS1))!=0)
    {
        c_uc_w2s_strncpy(pt_this->w2s_dlg_text,MENU_TEXT(MLM_MENU_KEY_DEVICE_UNPAIRED_SUCCESS1),MENU_DEVICE_SETTING_REMOTE_NAME_LEN);
        c_uc_w2s_strncat(pt_this->w2s_dlg_text,w2s_space,1);
    }
    c_uc_w2s_strncat(pt_this->w2s_dlg_text,w2s_device_type,c_uc_w2s_strlen(w2s_device_type));

    c_uc_w2s_strncat(pt_this->w2s_dlg_text,w2s_space,1);
    c_uc_w2s_strncat(pt_this->w2s_dlg_text,MENU_TEXT(MLM_MENU_KEY_DEVICE_UNPAIRED_SUCCESS2),c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_DEVICE_UNPAIRED_SUCCESS2)));

    return i4_ret;
}

static INT32 _device_status_info_unpair_btn_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    static BOOL b_unpair_flag = FALSE;
    UINT32 ui4_keycode = (UINT32)param1;
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            if (MENU_DEVICE_TYPE_REMOTE == pt_this->t_device_info.e_current_device_type)
            {
                menu_set_and_show_help_tip(
                    MENU_TEXT(MLM_MENU_KEY_HELP_TIP_UNPAIR_REMOTE));
            }
            else
            {
                menu_set_and_show_help_tip(
                    MENU_TEXT(menu_device_get_help_txt(MENU_DEVICE_TYPE_IDX_UNPAIR)));
            }
            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
            DBG_INFO(("_device_status_info_unpair_btn_proc_fct: WGL_MSG_KEY_DOWN, b_unpair_flag = %d\n", b_unpair_flag));
            b_unpair_flag = TRUE;
                    //unpair device and go to device setting page
                    if (MENU_DEVICE_TYPE_MIRACAST ==
                        pt_this->t_device_info.e_current_device_type)
                    {
                    #ifdef APP_WFD_SUPPORT
                        if (a_cfg_custom_get_wfd_support()==TRUE)
                        {
                            i4_ret = a_wfd_device_info_unpair_device(
                                         pt_this->t_device_info.u_device_data.t_miracast.ui1_miracast_idx);
                            MENU_LOG_ON_FAIL(i4_ret);

                            wfd_app_disconnect_rtsp();
                        }
					#endif
                    }
                    else if (MENU_DEVICE_TYPE_REMOTE ==
                        pt_this->t_device_info.e_current_device_type)
                    {
                        i4_ret = a_cfg_custom_set_wifi_remote_pair_status(WIFI_REMOTE_PAIR_STATUS_UNPAIRED);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = a_tv_net_send_cmd("\n:am,am,:rc_paired=false\n");
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else if (MENU_DEVICE_TYPE_INPUT ==
                        pt_this->t_device_info.e_current_device_type)
                    {
                    	ISL_REC_T       t_isl_rec;
						CHAR			s_inp_name[CONN_SRC_NAME_MAX_STRLEN+1]={0};
                        if (a_cfg_custom_get_wifi_remote_support())
                        {
                            i4_ret = _device_status_info_get_unpair_dlg_text();
                            MENU_LOG_ON_FAIL(i4_ret);

                            i4_ret = a_cfg_custom_delete_device_info(
                                           pt_this->t_device_info.u_device_data.t_input.ui1_input_src_idx);
                            MENU_LOG_ON_FAIL(i4_ret);
                        }
						/*set input name to default when unpair device*/
						c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
		                a_isl_get_rec_by_idx(pt_this->t_device_info.u_device_data.t_input.ui1_input_src_idx, &t_isl_rec);

						c_uc_w2s_to_ps(a_isl_get_display_name(&t_isl_rec), s_inp_name, CONN_SRC_NAME_MAX_STRLEN);
						DBG_INFO(("\n####%s(%d)s_inp_name=%s\n",__FUNCTION__,__LINE__,s_inp_name));

						a_cfg_custom_set_inp_name(t_isl_rec.ui1_id, s_inp_name);
                    }
                    else if (MENU_DEVICE_TYPE_SOUNDBAR ==
                        pt_this->t_device_info.e_current_device_type)
                    {
                        i4_ret = _device_status_info_get_unpair_dlg_text();
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = a_cfg_custom_delete_device_info(
                                       pt_this->t_device_info.u_device_data.t_soundbar.ui1_soundbar_idx);
                        MENU_LOG_ON_FAIL(i4_ret);

                        a_tv_net_custom_set_soundbar_flag(FALSE);

                        UINT16  ui2_aud_out_mask = 0;
                        INT16   i2_val = 0;

                        a_cfg_custom_set_vol_control(0);

                        /* turn on TV speaker */
                        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT),
                                     &i2_val);
                        ui2_aud_out_mask = (UINT16)i2_val;

                        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask | SCC_AUD_OUT_PORT_SPEAKER);

                    #if defined(APP_CEC_SUPPORT) && defined(APP_CEC2_SUPPORT)
                        /* Turn off CEC SAC */
                        a_cfg_set_cec_sac_func(0);
                    #endif

                        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT),
                                     (INT16)ui2_aud_out_mask);
                        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT));
                    }
                }
                    break;

                case BTN_CURSOR_UP:
                {
                    if (MENU_DEVICE_TYPE_INPUT == pt_this->t_device_info.e_current_device_type)
                    {
                        if (TRUE == _is_3rd_app_running())
                        {
                            i4_ret = menu_set_focus_on_backbar(TRUE);
                            MENU_LOG_ON_FAIL(i4_ret);
                        }
                        else
                        {
                            i4_ret = c_wgl_set_focus(pt_this->h_name_input,
                                                     WGL_SYNC_AUTO_REPAINT);
                            MENU_LOG_ON_FAIL(i4_ret);
                        }
                    }
                    else
                    {
                        i4_ret = menu_set_focus_on_backbar(TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }
                    break;

                case BTN_CURSOR_DOWN:
                {
                    i4_ret = menu_help_tip_keytip_set_focus(h_widget, 0 , FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    menu_pm_repaint();
                }
                    break;

                case BTN_CURSOR_RIGHT:
                {
                    if( (MENU_DEVICE_TYPE_INPUT ==
                        pt_this->t_device_info.e_current_device_type)||
                        (MENU_DEVICE_TYPE_CEC_DEV==
                        pt_this->t_device_info.e_current_device_type))
                    {

                    }
                }
                    break;

                case BTN_RETURN:
                {
                    i4_ret = menu_device_page_nav_go(NAV_DEVICE_SETTING_PAGE_FROM_STATUS_INFO_PAGE,
                                                     NULL);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                default:
                    break;
            }
        }
            break;

     case WGL_MSG_KEY_UP:
     {

        switch (ui4_keycode)
             {
                case BTN_SELECT:
                {
             DBG_INFO(("_device_status_info_unpair_btn_proc_fct: WGL_MSG_KEY_UP, b_unpair_flag=%d\n", b_unpair_flag));

             if (b_unpair_flag)
             {
                  b_unpair_flag = FALSE;

                  if (MENU_DEVICE_TYPE_REMOTE == pt_this->t_device_info.e_current_device_type)
                   {
                         #ifdef APP_WIFI_REMOTE
                         i4_ret = c_unpair_remote_ex();
                         DBG_INFO(("c_unpair_remote_ex = %d\n", i4_ret));
                         #endif

                           i4_ret = _device_status_info_page_confirm_dialog_show(
                                  MENU_TEXT(MLM_MENU_KEY_WIFI_REMOTE_UNPAIRED_SUCCESS),
                                  MENU_TEXT(MLM_MENU_KEY_OK),
                                             _wifi_remote_unpair_confirm_dialog_cb_fct,
                                             TRUE);
                           MENU_LOG_ON_FAIL(i4_ret);
                   }
                   else
                   {
                          i4_ret = _device_status_info_page_confirm_dialog_show(
                                  pt_this->w2s_dlg_text,
                                  MENU_TEXT(MLM_MENU_KEY_OK),
                                  _wifi_remote_unpair_confirm_dialog_cb_fct,
                                  TRUE);
                         MENU_LOG_ON_FAIL(i4_ret);
                   }
             }
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

static INT32 _device_status_info_page_unpair_btn_create (VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    GL_RECT_T           t_rect;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_DEVICE_STATUS_INFO_BTN_UNPAIR_X,
                     MENU_DEVICE_STATUS_INFO_BTN_UNPAIR_Y,
                     MENU_DEVICE_STATUS_INFO_BTN_UNPAIR_W,
                     MENU_DEVICE_STATUS_INFO_BTN_UNPAIR_H
                     );

    i4_ret = _device_status_info_btn_create(pt_this->h_cnt_frm,
                                            &t_rect,
                                            _device_status_info_unpair_btn_proc_fct,
                                            MENU_TEXT(MLM_MENU_KEY_UNPAIR),
                                            &pt_this->h_btn_unpair);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_status_info_page_backbar_proc_fct(
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
        MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
            #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
            #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                i4_ret = menu_device_page_nav_go(NAV_DEVICE_SETTING_PAGE_FROM_STATUS_INFO_PAGE,
                                                 NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }

            case BTN_CURSOR_DOWN:
            {
                if (MENU_DEVICE_TYPE_INPUT == pt_this->t_device_info.e_current_device_type)
                {
                    if (TRUE == _is_3rd_app_running())
                    {
                        if (pt_this->b_paired)
                        {
                            i4_ret = c_wgl_set_focus(pt_this->h_btn_unpair,
                                                     WGL_SYNC_AUTO_REPAINT);
                            MENU_LOG_ON_FAIL(i4_ret);
                        }
                        else
                        {
                            i4_ret = menu_help_tip_keytip_set_focus(h_widget, 0 , FALSE);
                            MENU_LOG_ON_FAIL(i4_ret);
                            menu_pm_repaint();
                        }
                    }
                    else
                    {
                        i4_ret = c_wgl_set_focus(pt_this->h_name_input,
                                                 WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }
                else if(MENU_DEVICE_TYPE_CEC_DEV == pt_this->t_device_info.e_current_device_type)
                {
	                i4_ret = c_wgl_set_focus(pt_this->h_name_input,
                                                 WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    if (pt_this->b_paired)
                    {
                        i4_ret = c_wgl_set_focus(pt_this->h_btn_unpair,
                                                 WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        i4_ret = menu_help_tip_keytip_set_focus(h_widget, 0 , FALSE);
                        MENU_LOG_ON_FAIL(i4_ret);
                        menu_pm_repaint();
                    }
                }
            }
                break ;

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

static INT32 _device_status_info_page_homebar_proc_fct(
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
                i4_ret = menu_device_page_nav_go(NAV_ROOT_MENU_FROM_ANY_PAGE,
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

static INT32 _device_status_info_is_paired(BOOL* pb_paired)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    UINT8       ui1_pair_status = 0;
    UTF16_T     w2s_input_type[MENU_DEVICE_STATUS_INFO_INPUT_TYPE_LEN] = {0};
    UTF16_T     w2s_input_brand[MENU_DEVICE_STATUS_INFO_INPUT_BRAND_LEN] = {0};
    UTF16_T     w2s_input_model[MENU_DEVICE_STATUS_INFO_INPUT_MODEL_LEN] = {0};

    if (MENU_DEVICE_TYPE_REMOTE == pt_this->t_device_info.e_current_device_type)
    {
        i4_ret = a_cfg_custom_get_wifi_remote_pair_status(&ui1_pair_status);
        MENU_LOG_ON_FAIL(i4_ret);

        if (WIFI_REMOTE_PAIR_STATUS_PAIRED == ui1_pair_status)
        {
            *pb_paired = TRUE;
        }
    }
    else if (MENU_DEVICE_TYPE_INPUT == pt_this->t_device_info.e_current_device_type)
    {
        i4_ret = _get_input_type_brand_model(w2s_input_type,
                                        w2s_input_brand,
                                        w2s_input_model);
        MENU_LOG_ON_FAIL(i4_ret);

        if ((c_uc_w2s_strlen(w2s_input_brand) > 0)
            ||(c_uc_w2s_strlen(w2s_input_model) > 0))
        {
            *pb_paired = TRUE;
        }
    }
    else if (MENU_DEVICE_TYPE_MIRACAST == pt_this->t_device_info.e_current_device_type)
    {
        *pb_paired = TRUE;
    }
    else if (MENU_DEVICE_TYPE_SOUNDBAR == pt_this->t_device_info.e_current_device_type)
    {
        *pb_paired = TRUE;
    }

    return i4_ret;
}

static INT32 _device_status_info_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    c_memset(pt_this, 0, sizeof(MENU_DEVICE_STATUS_INFO_PAGE_DATA_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_this->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _device_status_info_page_device_name_text_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _device_status_info_txt_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _device_status_info_page_unpair_btn_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _device_status_info_page_confirm_dialog_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _device_status_info_name_input_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_status_info_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _device_status_info_page_show(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;
    HANDLE_T			                        h_last_shadow_item = NULL_HANDLE;

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_device_get_device_info(&pt_this->t_device_info);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->b_paired = FALSE;

    i4_ret = _device_status_info_is_paired(&pt_this->b_paired);
    MENU_LOG_ON_FAIL(i4_ret);

    if (pt_this->b_paired)
    {
        c_wgl_enable(pt_this->h_btn_unpair, TRUE);
    }
    else
    {
        c_wgl_enable(pt_this->h_btn_unpair, FALSE);
    }

    if (MENU_DEVICE_TYPE_REMOTE == pt_this->t_device_info.e_current_device_type)
    {
        i4_ret = menu_main_set_title(MLM_MENU_KEY_REMOTE_STATUS_INFO_PAGE_TITLE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = menu_main_set_title(MLM_MENU_KEY_DEVICE_STATUS_INFO_PAGE_TITLE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = _device_status_info_page_show_ui(pt_this->t_device_info.e_current_device_type);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_backbar_proc(_device_status_info_page_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(_device_status_info_page_homebar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_status_info_page_hide(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    if (pt_this->t_device_info.u_device_data.t_input.pw2s_user_name)
    {
        c_mem_free(pt_this->t_device_info.u_device_data.t_input.pw2s_user_name);
        pt_this->t_device_info.u_device_data.t_input.pw2s_user_name = NULL;
    }

    if (pt_this->t_device_info.u_device_data.t_input.pw2s_disp_name)
    {
        c_mem_free(pt_this->t_device_info.u_device_data.t_input.pw2s_disp_name);
        pt_this->t_device_info.u_device_data.t_input.pw2s_disp_name = NULL;
    }
#ifdef APP_CEC_MENU
    if (pt_this->t_device_info.u_device_data.t_cec_dev.pw2s_cec_osd_name)
    {
        c_mem_free(pt_this->t_device_info.u_device_data.t_cec_dev.pw2s_cec_osd_name);
        pt_this->t_device_info.u_device_data.t_cec_dev.pw2s_cec_osd_name = NULL;
    }
#endif
    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_status_info_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32       i4_ret = MENUR_OK;
    MENU_DEVICE_STATUS_INFO_PAGE_DATA_T* pt_this = &t_g_device_status_info_page_data;

    if (MENU_DEVICE_TYPE_INPUT == pt_this->t_device_info.e_current_device_type
        && pt_hint != NULL
        && MENU_PAGE_HT_BACK == pt_hint->e_hint_type)
    {
        i4_ret = c_wgl_set_focus(pt_this->h_name_input, WGL_NO_AUTO_REPAINT);
    }
    else
    {
        i4_ret = menu_set_focus_on_backbar(FALSE);
    }
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _device_status_info_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _device_status_info_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)

{
    return MENUR_OK;
}

extern INT32 menu_device_page_device_status_info_init(VOID)
{
    t_g_menu_device_page_device_status_info.pf_menu_page_create =    _device_status_info_page_create;
    t_g_menu_device_page_device_status_info.pf_menu_page_destroy=    _device_status_info_page_destroy;
    t_g_menu_device_page_device_status_info.pf_menu_page_show=       _device_status_info_page_show;
    t_g_menu_device_page_device_status_info.pf_menu_page_hide=       _device_status_info_page_hide;
    t_g_menu_device_page_device_status_info.pf_menu_page_get_focus=  _device_status_info_page_get_focus;
    t_g_menu_device_page_device_status_info.pf_menu_page_lose_focus= _device_status_info_page_lose_focus;
    t_g_menu_device_page_device_status_info.pf_menu_page_update=     _device_status_info_page_update;

    return MENUR_OK;
}



