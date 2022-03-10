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
 * $Revision: #2 $
 * $Date: 2015/06/09 $
 * $Author: heyi.wang $
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

#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu_page_device_setting.h"
#include "menu_device.h"
#include "menu_page_device_status_info.h"
#include "menu_page_pair_wifi_device.h"
#include "menu2/menu_common/menu_page_animation.h"

#include "wfrrc_interface.h"
#ifdef APP_WFD_SUPPORT
#include "wfd_client_export.h"
#endif

#include <unistd.h>
#include <pthread.h>
#include "c_os.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef enum _MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_STATUS_T
{
    MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_UNKNOWN = 0,
    MENU_PAIR_WIFI_DEVICE_PAGE_START_PAIRING,
    MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_SUCCESS,
    MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_TIMEOUT,
    MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_LAST_ENTRY
}MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_STATUS_T;

typedef struct _MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T
{
    HANDLE_T     h_cnt_frm;
    HANDLE_T     h_txt_user_info;
    HANDLE_T     h_txt_pair_result;
    HANDLE_T     h_txt_ready_to_pair;
    HANDLE_T     h_btn_pair;
    HANDLE_T     h_animation;
    HANDLE_T     h_confirm_dialog_frm;
    HANDLE_T     h_confirm_dialog_title;
    HANDLE_T     h_confirm_dialog_ok;

    HANDLE_T     h_timer;

    MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_STATUS_T e_pair_status;
    UINT8        ui1_animation_count;
    BOOL         b_pair_wifi_device_page_show;
    BOOL         b_codeset_upload;
    BOOL         b_animation;
}MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T;

typedef struct _WFD_NOTIFY_DATA_T
{
    int   i4_callbackid;
    void* pParam;
}WFD_NOTIFY_DATA_T;

/*-----------------------------------------------------------------------------
              data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_pair_wifi_device;
static MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T t_g_pair_wifi_device_page_data;

/*-----------------------------------------------------------------------------
                 function declarations
----------------------------------------------------------------------------*/
static INT32 _pair_wifi_device_page_confirm_dialog_hide(BOOL  b_repaint);

/*-----------------------------------------------------------------------------
                  function implementations
----------------------------------------------------------------------------*/
static INT32 _pair_wifi_device_text_create(HANDLE_T    h_parent,
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
                                   WGL_STL_TEXT_MAX_512 |
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
    t_inset.i4_left     = MENU_PAIR_WIFI_DEVICE_TEXT_INSET_LEFT;
    t_inset.i4_right    = MENU_PAIR_WIFI_DEVICE_TEXT_INSET_RIGHT;
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

    return i4_ret;
}

static INT32 _pair_wifi_device_page_hyper_text_create(HANDLE_T h_parent,
                                                      HANDLE_T          *ph_widget,
                                                      const GL_RECT_T*   pt_rect)
{
    INT32                       i4_ret = MENUR_OK;
    WGL_INSET_T                 t_inset;
    WGL_HTS_INIT_T              t_init;
    WGL_HTS_PARAG_ATTR_T        t_parag;
    CHAR*                       s_font_name = menu_font_name();

    c_memset (&t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, s_font_name);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_SMALL;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;

    /* create hyper text widget */
    i4_ret = c_wgl_create_widget (h_parent,
                                   HT_WGL_WIDGET_HTS,
                                   WGL_CONTENT_HTS_DEF,
                                   WGL_BORDER_NULL,
                                   pt_rect,
                                   NULL,
                                   255,
                                   (VOID*)(&t_init),
                                   NULL,
                                   ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    /* set content inset */
    t_inset.i4_left   = MENU_PAIR_WIFI_DEVICE_TEXT_INSET_LEFT;
    t_inset.i4_right  = MENU_PAIR_WIFI_DEVICE_TEXT_INSET_RIGHT;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_HTS_SET_CNT_INSET,
                            WGL_PACK (&t_inset),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* set justification */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                            WGL_PACK (WGL_HTS_JUSTIF_LEFT),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset (&t_parag, 0, sizeof(WGL_HTS_PARAG_ATTR_T));
    t_parag.e_justif = WGL_HTS_JUSTIF_LEFT;
    t_parag.ui2_indent = 0;
    t_parag.i4_line_gap_bottom = 2;
    t_parag.i4_line_gap_top = 0;
    t_parag.ui2_parag_gap_bottom = 0;
    t_parag.ui2_parag_gap_top = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                            WGL_CMD_HTS_CUR_PARAG_SET,
                           WGL_PACK(&t_parag),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return  i4_ret;
}

static INT32 _pair_wifi_device_page_user_info_create(VOID)
{
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T       t_rect;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_PAIR_WIFI_DEVICE_USER_INFO_X,
                     MENU_PAIR_WIFI_DEVICE_USER_INFO_Y,
                     MENU_PAIR_WIFI_DEVICE_USER_INFO_W,
                     MENU_PAIR_WIFI_DEVICE_USER_INFO_H);
    i4_ret = _pair_wifi_device_page_hyper_text_create(pt_this->h_cnt_frm,
                                            &pt_this->h_txt_user_info,
                                            &t_rect);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _pair_wifi_device_page_pair_result_create(VOID)
{
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T       t_rect;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_PAIR_WIFI_DEVICE_PAIR_RESULT_X,
                     MENU_PAIR_WIFI_DEVICE_PAIR_RESULT_Y,
                     MENU_PAIR_WIFI_DEVICE_PAIR_RESULT_W,
                     MENU_PAIR_WIFI_DEVICE_PAIR_RESULT_H);
    i4_ret = _pair_wifi_device_text_create(pt_this->h_cnt_frm,
                                            &pt_this->h_txt_pair_result,
                                            &t_rect, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _pair_wifi_device_page_ready_to_pair_text_create(VOID)
{
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T       t_rect;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_PAIR_WIFI_DEVICE_READY_TO_PAIR_X,
                     MENU_PAIR_WIFI_DEVICE_READY_TO_PAIR_Y,
                     MENU_PAIR_WIFI_DEVICE_READY_TO_PAIR_W,
                     MENU_PAIR_WIFI_DEVICE_READY_TO_PAIR_H);
    i4_ret = _pair_wifi_device_text_create(pt_this->h_cnt_frm,
                                            &pt_this->h_txt_ready_to_pair,
                                            &t_rect, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

#ifdef APP_WFD_SUPPORT
static void* _upload_codeset_async_thread(void* pv_data)
{
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

    pthread_detach(pthread_self());

    UINT8 ui1_input_idx = 0;
    CHAR  s_type_name[32 + 1] = {0};
    CHAR  s_brand_name[32 + 1] = {0};
    CHAR  s_model_name[32 + 1] = {0};
    CHAR  s_codeset[5 + 1] = {0};

    for (ui1_input_idx=0; ui1_input_idx<10; ui1_input_idx++)
    {
        a_cfg_custom_get_device_info(ui1_input_idx, s_type_name, s_brand_name,
                                     s_model_name, s_codeset);

        DBG_INFO(("\n%s,%s,%d,ui1_input_idx=%d,s_codeset=%s\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    ui1_input_idx,
                    s_codeset));

        if (c_strlen(s_codeset) > 0)
        {
            c_upload_codeset(s_codeset);
        }
    }

    if (pt_this->b_pair_wifi_device_page_show)
    {
        pt_this->b_codeset_upload = TRUE;
    }

    return NULL;
}

static VOID _upload_codeset_async(VOID)
{
    INT32        i4_ret = MENUR_OK;
    pthread_t    h_thread = {0};

    i4_ret = pthread_create(&h_thread, NULL, _upload_codeset_async_thread, NULL);
    if(i4_ret != 0)
    {
        DBG_ERROR(("\n%s,%s,%d,%d\n",
                   __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }

    return;
}
#endif

static INT32 _pair_wifi_device_page_pair_end(BOOL b_success)
{
    INT32               i4_ret = MENUR_OK;
    UINT16              ui2_key = 0;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

    i4_ret = menu_page_animation_stop();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_animation_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->b_animation = FALSE;

    if (b_success)
    {
        i4_ret = menu_set_focus_on_backbar(FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_this->h_txt_user_info,
                                       WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_this->h_btn_pair,
                              WGL_CMD_BTN_SET_TEXT,
                              WGL_PACK(MENU_TEXT(MLM_MENU_KEY_UNPAIR)),
                              WGL_PACK(0xFF));
        MENU_LOG_ON_FAIL(i4_ret);

        ui2_key = MLM_MENU_KEY_WIFI_REMOTE_FOUND_DESC;
    }
    else
    {
        ui2_key = MLM_MENU_KEY_WIFI_REMOTE_NOT_FOUND_DESC;
    }

    i4_ret = c_wgl_do_cmd(pt_this->h_txt_pair_result,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_key)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_txt_pair_result,
                                   WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_txt_ready_to_pair,
                                   WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pm_repaint();

    return i4_ret;
}

static INT32 _pair_wifi_device_page_pair_start(VOID)
{
    INT32               i4_ret = MENUR_OK;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

    pt_this->e_pair_status = MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_UNKNOWN;

    i4_ret = a_cfg_custom_set_wifi_remote_pair_status(WIFI_REMOTE_PAIR_STATUS_PAIRING);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_txt_pair_result,
                                   WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_this->h_txt_pair_result,
                            NULL, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->ui1_animation_count = 0;
    i4_ret = menu_page_animation_start(1, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);
    pt_this->b_animation = TRUE;
#ifdef APP_PORTING
    i4_ret = wfd_client_connect(WFD_CONNECT_PBC_FORCE_GO, NULL, NULL);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    pt_this->e_pair_status = MENU_PAIR_WIFI_DEVICE_PAGE_START_PAIRING;
#ifdef APP_PORTING
    if (c_wifi_remote_set_mac_when_connected())
    {
        pt_this->e_pair_status = MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_SUCCESS;
        a_cfg_custom_set_wifi_remote_pair_status(WIFI_REMOTE_PAIR_STATUS_PAIRED);
        _pair_wifi_device_page_pair_end(TRUE);
    }
#endif
    return i4_ret;
}

static VOID _pair_wifi_device_page_do_timer_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = _pair_wifi_device_page_confirm_dialog_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_device_page_nav_go(
                          NAV_DEVICE_SETTING_PAGE_FROM_STATUS_INFO_PAGE,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);
}

static VOID _menu_device_timer_cb_fct (HANDLE_T  pt_tm_handle,
                                    VOID*     pv_tag)
{
    INT32 i4_ret = MENUR_OK;

    i4_ret = menu_async_invoke(_pair_wifi_device_page_do_timer_nfy,
                               NULL, 0, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);
}

static INT32 _pair_wifi_device_page_confirm_dialog_proc_fct(
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

static INT32 _pair_wifi_device_page_confirm_dialog_create(VOID)
{
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T       t_rect;
    HANDLE_T        h_root_frm = NULL_HANDLE;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

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
                                 _pair_wifi_device_page_confirm_dialog_proc_fct,
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

static INT32 _pair_wifi_device_page_confirm_dialog_hide(BOOL  b_repaint)
{
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;
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

static INT32 _pair_wifi_device_page_confirm_dialog_show(
                                    UINT16      ui2_msgid_title,
                                    UINT16      ui2_msgid_ok,
                                    menu_device_confirm_dialog_cb_fct  pf_back,
                                    BOOL         b_repaint)
{
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;
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
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_confirm_dialog_ok,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_ok)),
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

static VOID _wifi_remote_unpair_confirm_dialog_cb_fct(VOID)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = _pair_wifi_device_page_confirm_dialog_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_device_page_nav_go(
                          NAV_DEVICE_SETTING_PAGE_FROM_STATUS_INFO_PAGE,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);
}

static INT32 _pair_wifi_device_pair_btn_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;
    UINT32 ui4_keycode = (UINT32)param1;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;
    static BOOL b_unpair_flag = FALSE;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            if (MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_SUCCESS == pt_this->e_pair_status)
            {
                i4_ret=menu_set_and_show_help_tip(
                            MENU_TEXT(MLM_MENU_KEY_HELP_TIP_UNPAIR_REMOTE));
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret=menu_set_and_show_help_tip(
                            MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_ADD_REMOTE));
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
            break;

        case WGL_MSG_KEY_DOWN:
        {
            if (pt_this->b_animation)
            {
                DBG_INFO(("\n%s,%s,%d,e_pair_status=%d,wifi remote is pairing, discard key\n",
                            __FILE__, __FUNCTION__, __LINE__,
                            pt_this->e_pair_status));
                return MENUR_OK;
            }

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    if (MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_SUCCESS == pt_this->e_pair_status)
                    {
                        i4_ret = a_cfg_custom_set_wifi_remote_pair_status(WIFI_REMOTE_PAIR_STATUS_UNPAIRED);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = a_tv_net_send_cmd("\n:am,am,:rc_paired=false\n");
                        MENU_LOG_ON_FAIL(i4_ret);

                        b_unpair_flag = TRUE;
                    }
                    else
                    {
                        i4_ret = _pair_wifi_device_page_pair_start();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
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
                    i4_ret = menu_help_tip_keytip_set_focus(h_widget, 0 , FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    menu_pm_repaint();
                }
                    break;

                case BTN_RETURN:
                {
                    i4_ret = menu_device_page_nav_go(NAV_DEVICE_SETTING_PAGE_FROM_PAIR_WIFI_DEVICE_PAGE,
                                                     NULL);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                default:
                    break;
            }
        }

        case WGL_MSG_KEY_UP:
        {
            if (pt_this->b_animation)
            {
                DBG_INFO(("\n%s,%s,%d,e_pair_status=%d,wifi remote is pairing, discard key\n",
                            __FILE__, __FUNCTION__, __LINE__,
                            pt_this->e_pair_status));
                return MENUR_OK;
            }

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    if (b_unpair_flag)
                    {
                        b_unpair_flag = FALSE;
#ifdef APP_PORTING
                        if (a_cfg_custom_get_wifi_remote_support())
                        {
                            i4_ret = c_unpair_remote_ex();
                            DBG_INFO(("\n%s,%s,%s,%s,%d,i4_ret=%d,e_pair_status=%d\n",
                                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                                        i4_ret,
                                        pt_this->e_pair_status));
                        }
#endif
                        i4_ret = _pair_wifi_device_page_confirm_dialog_show(
                                          MLM_MENU_KEY_WIFI_REMOTE_UNPAIRED_SUCCESS,
                                          MLM_MENU_KEY_OK,
                                          _wifi_remote_unpair_confirm_dialog_cb_fct,
                                          TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }
                    break;

                default:
                    break;
            }
        }
        break;

        case WGL_MSG_KEY_REPEAT:
        {
            if (pt_this->b_animation)
            {
                DBG_INFO(("\n%s,%s,%d,e_pair_status=%d,wifi remote is pairing, discard key\n",
                            __FILE__, __FUNCTION__, __LINE__,
                            pt_this->e_pair_status));
                return MENUR_OK;
            }
        }
            break;

        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _pair_wifi_device_btn_create(HANDLE_T h_parent,
                                    wgl_widget_proc_fct  pf_wdgt_proc,
                                    UTF16_T*  pw2s_str,
                                    HANDLE_T* ph_widget)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_color_info = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_FONT_INFO_T     t_font_info = {0};
    GL_COLOR_T          t_color_txt = { 255, { 255}, { 255}, { 255}};

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_PAIR_WIFI_DEVICE_BTN_PAIR_X,
                     MENU_PAIR_WIFI_DEVICE_BTN_PAIR_Y,
                     MENU_PAIR_WIFI_DEVICE_BTN_PAIR_W,
                     MENU_PAIR_WIFI_DEVICE_BTN_PAIR_H
                     );

    i4_ret = c_wgl_create_widget(h_parent,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                pf_wdgt_proc,
                                255,
                                NULL,
                                NULL,
                                ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left   = MENU_PAIR_WIFI_DEVICE_BTN_INSET_LEFT;
    t_inset.i4_right  = MENU_PAIR_WIFI_DEVICE_BTN_INSET_RIGHT;
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
    t_color_info.u_color_data.t_extend.t_disable = t_color_txt;
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
    t_font_info.e_font_size  = FE_FNT_SIZE_SMALL;
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

static INT32 _pair_wifi_device_page_pair_btn_create (VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

    i4_ret = _pair_wifi_device_btn_create(pt_this->h_cnt_frm,
                                           _pair_wifi_device_pair_btn_proc_fct,
                                           MENU_TEXT(MLM_MENU_KEY_PAIR_DEVICE),
                                           &pt_this->h_btn_pair);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _pair_wifi_device_page_backbar_proc_fct(
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
        MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
            #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
            #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                i4_ret = menu_device_page_nav_go(NAV_DEVICE_SETTING_PAGE_FROM_PAIR_WIFI_DEVICE_PAGE,
                                                 NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }

            case BTN_CURSOR_DOWN:
            {
                i4_ret = c_wgl_set_focus(pt_this->h_btn_pair,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
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

static INT32 _pair_wifi_device_page_homebar_proc_fct(
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

static VOID _menu_pair_wifi_device_do_animation_nfy(
                                                            VOID* pv_data,
                                                            SIZE_T  z_data_size)
{

    INT32    i4_ret = MENUR_OK;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

    DBG_INFO(("\n<MENU_PAIR_WIFI_DEV>%s,%s,%d,ui1_animation_count=%d,e_pair_status=%d,b_codeset_upload=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                pt_this->ui1_animation_count,
                pt_this->e_pair_status,
                pt_this->b_codeset_upload));

    if (pt_this->b_codeset_upload)
    {
        i4_ret = _pair_wifi_device_page_pair_end(TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

        return;
    }
#ifdef APP_PORTING
    if (c_wifi_remote_set_mac_when_connected())
    {
        pt_this->e_pair_status = MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_SUCCESS;
        a_cfg_custom_set_wifi_remote_pair_status(WIFI_REMOTE_PAIR_STATUS_PAIRED);

        i4_ret = _pair_wifi_device_page_pair_end(TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

        return;
    }
#endif
    pt_this->ui1_animation_count++;

    if((pt_this->ui1_animation_count >= MENU_PAIR_WIFI_REMOTE_DEVICE_ANIMATION_COUNT)
        &&(MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_SUCCESS != pt_this->e_pair_status))
    {
        pt_this->e_pair_status = MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_TIMEOUT;
        a_cfg_custom_set_wifi_remote_pair_status(WIFI_REMOTE_PAIR_STATUS_UNPAIRED);

        i4_ret = _pair_wifi_device_page_pair_end(FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = menu_page_animation_start(1, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
}

static INT32 _menu_pair_wifi_device_animation_cb(HANDLE_T  h_widget,
                                              UINT16                  ui2_anim_type,
                                              WGL_ANIM_COND_INF_T     e_anim_cond,
                                              VOID*                   pv_tag)
{
    INT32       i4_ret = MENUR_OK;

    if (_ANIM_TOTAL_END(&e_anim_cond))
    {
        i4_ret = menu_async_invoke(_menu_pair_wifi_device_do_animation_nfy,
                                   NULL, 0, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static INT32 _menu_pair_wifi_device_animation_create(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;
    GL_RECT_T   t_rect;

    c_memset(&t_rect, 0, sizeof(t_rect));
    SET_RECT_BY_SIZE(&t_rect,
                     CONTENT_X + (CONTENT_W -ICON_ANIMATION_W)/2,
                     CONTENT_Y + MENU_ITEM_V_HEIGHT * 4 - ICON_ANIMATION_H,
                     ICON_ANIMATION_W,
                     ICON_ANIMATION_H);

    i4_ret = menu_page_animation_get_handle(&pt_this->h_animation);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_move(pt_this->h_animation, &t_rect, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_animation_set_callback_fct(_menu_pair_wifi_device_animation_cb,
                                                  NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static UTF16_T* _menu_pair_wifi_device_w2s_sch(UTF16_T*        pw2s_text,
                             const UTF16_T*  pw2s_sub_text)
{
    UTF16_T*   pw2s_start = NULL;
    SIZE_T     t_cmp_offset = 0;
    SIZE_T     t_txt_size = 0;
    SIZE_T     t_sub_txt_size = 0;
    if (!pw2s_text ||
        !pw2s_sub_text)
    {
        return (pw2s_start);
    }

    t_txt_size = c_uc_w2s_strlen(pw2s_text);
    t_sub_txt_size = c_uc_w2s_strlen(pw2s_sub_text);

    if (t_txt_size < t_sub_txt_size)
    {
        return (pw2s_start);
    }

    pw2s_start = pw2s_text;

    while (pw2s_start <= pw2s_text + t_txt_size - t_sub_txt_size)
    {
        t_cmp_offset = 0;
        while (t_cmp_offset < t_sub_txt_size)
        {
            if (*(pw2s_start + t_cmp_offset) == *(pw2s_sub_text + t_cmp_offset))
            {
                t_cmp_offset++;
            }
            else
            {
                break;
            }
        }
        if (t_cmp_offset == t_sub_txt_size)
        {
            return (pw2s_start);
        }
        pw2s_start++;
    }

    return (NULL);
}

static INT32 _menu_pair_wifi_device_set_user_info(UTF16_T* pw2s_text,
                                              WGL_HIMG_TPL_T h_img_1,
                                              WGL_HIMG_TPL_T h_img_2)
{
    INT32                  i4_ret = MENUR_OK;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;
    UINT16                 ui2_sec_id = 0;
    UINT16                 ui2_pic_idx = 0;
    WGL_HTS_TEXT_INFO_T    t_hts_txt_info;
    WGL_HTS_IMG_INFO_T     t_hts_img_info;
    UTF16_T                w2s_pic_flag[MENU_PAIR_WIFI_DEVICE_PIC_FLAG_LEN + 1];
    UTF16_T*               pw2s_next = NULL;
    UTF16_T*               pw2s_temp = pw2s_text;
    GL_COLOR_T             t_color_desc_txt = {255, {255}, {255}, {255}};
    GL_COLOR_T             t_color_desc_txt_bk = {0, {0}, {0}, {0}};

    c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
    c_memset (&t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
    c_memset (w2s_pic_flag, 0, sizeof(w2s_pic_flag));

    i4_ret = c_wgl_do_cmd (pt_this->h_txt_user_info,
                           WGL_CMD_HTS_CLEAR_ALL,
                           WGL_PACK (FALSE),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set font data. */
    c_strcpy (t_hts_txt_info.t_font.a_c_font_name, menu_font_name());
    t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
    t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_SMALL;

    t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

    /* Set text background color. */
    c_memcpy(&t_hts_txt_info.t_clr_text,
             &t_color_desc_txt,
             sizeof(GL_COLOR_T));
    c_memcpy(&t_hts_txt_info.t_clr_text_bk,
             &t_color_desc_txt_bk,
             sizeof(GL_COLOR_T));

    c_uc_ps_to_w2s("%p", w2s_pic_flag, sizeof(w2s_pic_flag));

    pw2s_next = _menu_pair_wifi_device_w2s_sch(pw2s_temp, w2s_pic_flag);
    while (pw2s_next)
    {
        t_hts_txt_info.t_string.w2s_str = pw2s_temp;
        t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
        t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * (pw2s_next - pw2s_temp);

        i4_ret = c_wgl_do_cmd(pt_this->h_txt_user_info,
                               WGL_CMD_HTS_APPEND_TEXT_SEC,
                               WGL_PACK (&t_hts_txt_info),
                               WGL_PACK (&ui2_sec_id));
        MENU_LOG_ON_FAIL(i4_ret);

        t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

        if (0 == ui2_pic_idx)
        {
            t_hts_img_info.h_img = h_img_1;
        }
        else if (1 == ui2_pic_idx)
        {
            t_hts_img_info.h_img = h_img_2;
        }

        i4_ret = c_wgl_do_cmd(pt_this->h_txt_user_info,
                               WGL_CMD_HTS_APPEND_IMG_SEC,
                               WGL_PACK(&t_hts_img_info),
                               WGL_PACK(&ui2_sec_id));
        MENU_LOG_ON_FAIL(i4_ret);
        ui2_pic_idx ++;

        pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
        pw2s_next = _menu_pair_wifi_device_w2s_sch(pw2s_temp, w2s_pic_flag);
    }

    if (pw2s_temp < pw2s_text + c_uc_w2s_strlen(pw2s_text))
    {
        t_hts_txt_info.t_string.w2s_str = pw2s_temp;
        t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
        t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

        i4_ret = c_wgl_do_cmd(pt_this->h_txt_user_info,
                               WGL_CMD_HTS_APPEND_TEXT_SEC,
                               WGL_PACK (&t_hts_txt_info),
                               WGL_PACK (&ui2_sec_id));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

#ifdef APP_WFD_SUPPORT
static VOID _menu_page_wifi_device_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;
    #if 0
    INT32       i4_ret = MENUR_OK;
    #endif
    WFD_NOTIFY_DATA_T t_wfd_notify_data = *((WFD_NOTIFY_DATA_T*)pv_data);

    DBG_INFO(("\n<MENU_PAIR_WIFI_DEV>%s,%s,%d,i4CallbackId=%d,e_pair_status=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                t_wfd_notify_data.i4_callbackid, pt_this->e_pair_status));

    switch (t_wfd_notify_data.i4_callbackid)
    {
        case WLAN_NOTIFY_AP_STA_CONNECTED:
        {
            if (MENU_PAIR_WIFI_DEVICE_PAGE_START_PAIRING != pt_this->e_pair_status)
            {
                return;
            }
             _upload_codeset_async();
            pt_this->e_pair_status = MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_SUCCESS;
            a_cfg_custom_set_wifi_remote_pair_status(WIFI_REMOTE_PAIR_STATUS_PAIRED);
        }
            break;
#if 0
        case WLAN_NOTIFY_P2P_WPS_RECEIVE_DPID_PBC:
        {
            if (MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_UNKNOWN != pt_this->e_pair_status)
            {
                return;
            }

            i4_ret = c_wgl_set_visibility(pt_this->h_txt_ready_to_pair,
                                           WGL_SW_NORMAL);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_repaint(pt_this->h_txt_ready_to_pair,
                                   NULL, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;
#endif
        default:
            break;
    }
}

static void _menu_page_wifi_device_notify_entry(int i4CallbackId, void *pParam)
{
    INT32       i4_ret = MENUR_OK;
    WFD_NOTIFY_DATA_T t_wfd_notify_data;

    c_memset(&t_wfd_notify_data, 0, sizeof(t_wfd_notify_data));
    t_wfd_notify_data.i4_callbackid = i4CallbackId;
    t_wfd_notify_data.pParam = pParam;
    i4_ret = menu_async_invoke(_menu_page_wifi_device_notify_handler,
                               &t_wfd_notify_data, sizeof(t_wfd_notify_data), TRUE);
    MENU_LOG_ON_FAIL(i4_ret);
}
#endif

static INT32 _pair_wifi_device_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32       i4_ret = MENUR_OK;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

    c_memset(pt_this, 0, sizeof(MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_this->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _pair_wifi_device_page_user_info_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _pair_wifi_device_page_pair_result_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _pair_wifi_device_page_pair_btn_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _pair_wifi_device_page_ready_to_pair_text_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _pair_wifi_device_page_confirm_dialog_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _pair_wifi_device_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _pair_wifi_device_page_show(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;
    HANDLE_T			                    h_last_shadow_item = NULL_HANDLE;

#ifdef APP_WFD_SUPPORT
    wfd_client_reg_callback(_menu_page_wifi_device_notify_entry);
#endif

    pt_this->e_pair_status = MENU_PAIR_WIFI_DEVICE_PAGE_PAIR_UNKNOWN;

    i4_ret = menu_main_set_title(MLM_MENU_KEY_ADD_REMOTE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_ADD_REMOTE));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_txt_pair_result,
                                   WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_pair_wifi_device_set_user_info(MENU_TEXT(MLM_MENU_KEY_PAIR_OPERATING_MANUAL_INFO),
                                                  h_g_menu_icon_record,
                                                  h_g_menu_icon_green);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_btn_pair,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_PAIR_REMOTE)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_txt_ready_to_pair,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_WIFI_REMOTE_READY_TO_PAIR)),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_txt_ready_to_pair,
                                   WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_backbar_proc(_pair_wifi_device_page_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(_pair_wifi_device_page_homebar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_pair_wifi_device_animation_create();
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
	MENU_LOG_ON_FAIL(i4_ret);

    pt_this->b_pair_wifi_device_page_show = TRUE;
    pt_this->b_codeset_upload = FALSE;
    pt_this->b_animation = FALSE;

    return i4_ret;
}

static INT32 _pair_wifi_device_page_hide(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_animation_stop();
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_WFD_SUPPORT
    wfd_client_unreg_callback(_menu_page_wifi_device_notify_entry);
#endif

    pt_this->b_pair_wifi_device_page_show = FALSE;

    return i4_ret;
}

static INT32 _pair_wifi_device_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32       i4_ret = MENUR_OK;
    MENU_PAIR_WIFI_DEVICE_PAGE_DATA_T* pt_this = &t_g_pair_wifi_device_page_data;

    i4_ret = c_wgl_set_focus(pt_this->h_btn_pair,
                             WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _pair_wifi_device_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _pair_wifi_device_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)

{
    return MENUR_OK;
}

extern INT32 menu_device_page_pair_wifi_device_init(VOID)
{
    t_g_menu_device_page_pair_wifi_device.pf_menu_page_create =    _pair_wifi_device_page_create;
    t_g_menu_device_page_pair_wifi_device.pf_menu_page_destroy=    _pair_wifi_device_page_destroy;
    t_g_menu_device_page_pair_wifi_device.pf_menu_page_show=       _pair_wifi_device_page_show;
    t_g_menu_device_page_pair_wifi_device.pf_menu_page_hide=       _pair_wifi_device_page_hide;
    t_g_menu_device_page_pair_wifi_device.pf_menu_page_get_focus=  _pair_wifi_device_page_get_focus;
    t_g_menu_device_page_pair_wifi_device.pf_menu_page_lose_focus= _pair_wifi_device_page_lose_focus;
    t_g_menu_device_page_pair_wifi_device.pf_menu_page_update=     _pair_wifi_device_page_update;

    return MENUR_OK;
}


