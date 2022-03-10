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
 * $RCSfile: wdk_wgl_util.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_sets.h"

#include "c_dbg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "c_appman.h"
#include "menu2/menu.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_colors.h"

#include "app_util/option_list/a_optl.h"


#include "c_handle.h"
#include "c_gl.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_fe.h"
#include "c_iom.h"
#include "nav/navigator.h"


#include "app_util/a_common.h"
#include "app_util/a_lbw.h"

#include "wdk/a_wdk.h"
#include "wdk_widget.h"
#include "res/wdk/wdk_img.h"
#include "menu2/menu_page.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#if 0
#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif
#endif


/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/
#define WDK_DEBUG_INPUT_SRC(x)  //x

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/

#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/

#if(NAV_INPUT_SRC_UI_VERTICAL)
#define WDK_INPUT_LIST_FRAME_X          (0)
#define WDK_INPUT_LIST_FRAME_Y          (0)
#define WDK_INPUT_LIST_FRAME_W          (1600)
#define WDK_INPUT_LIST_FRAME_H          (1000)

#define WDK_INPUT_LIST_DIALOG_FRAME_X   (0)
#define WDK_INPUT_LIST_DIALOG_FRAME_Y   (0)
#define WDK_INPUT_LIST_DIALOG_FRAME_W   (1200 )//(1700)
#define WDK_INPUT_LIST_DIALOG_FRAME_H   (WDK_INPUT_LIST_FRAME_H-100)//(1000)

#define WDK_VIEW_INPUT_LIST_BOX_X       (0)
#define WDK_VIEW_INPUT_LIST_BOX_Y       (0)
#define WDK_VIEW_INPUT_LIST_BOX_W       (960)
#define WDK_VIEW_INPUT_LIST_BOX_H       (WDK_INPUT_LIST_DIALOG_FRAME_H-100)//(900)

#define WDK_VIEW_INPUT_LIST_TITLE_TXT_X (32)
#define WDK_VIEW_INPUT_LIST_TITLE_TXT_Y (20)

#define WDK_VIEW_INPUT_LIST_TXT_ITEM_X  (90)
#define WDK_VIEW_INPUT_LIST_TXT_ITEM_Y  (180)
#define WDK_VIEW_INPUT_LIST_TXT_ITEM_W  (180)
#define WDK_VIEW_INPUT_LIST_TXT_ITEM_H  (50)
#endif

#define WDK_VIEW_BASE_FRAME_X                           (0)
#define WDK_VIEW_BASE_FRAME_Y                           (-2)
#define WDK_VIEW_BASE_FRAME_W                           (1920)
#define WDK_VIEW_BASE_FRAME_H                           (440)

#define WDK_VIEW_LIST_TXT_W_EX                          (170)

#define WDK_VIEW_CENTER_BASE_FRAME_W                 (1920)
#define WDK_VIEW_CENTER_BASE_FRAME_H                 (440)
#define WDK_VIEW_CENTER_BASE_FRAME_X                 (0)
#define WDK_VIEW_CENTER_BASE_FRAME_Y                 ((1080 - WDK_VIEW_CENTER_BASE_FRAME_H)/2)

#define WDK_LB_COL_MAX_TEXT_LENGTH          (80)
#define WDK_LB_MAX_ELEM_NUM                 (256)
#define WDK_LB_ELEM_H                       (50)
#define WDK_LB_ELEM_SPACE_V                 (2)
#define TXT_GRID_W                          (22)
#define TXT_GRID_H                          (28)
#define WDK_LONG_TXT_SCRL_DELAY             (180)

#define WDK_VIEW_ICON_TOASTBOX_X            (0)
#define WDK_VIEW_ICON_TOASTBOX_Y            (0)
#define WDK_VIEW_ICON_TOASTBOX_W            (WDK_VIEW_BASE_FRAME_W)
#define WDK_VIEW_ICON_TOASTBOX_H            (162)

#define WDK_VIEW_MSG_TOASTBOX_X             ((WDK_VIEW_BASE_FRAME_W-1400)/2)
#define WDK_VIEW_MSG_TOASTBOX_Y             (0)
#define WDK_VIEW_MSG_TOASTBOX_W             (1400)
#define WDK_VIEW_MSG_TOASTBOX_H             (WDK_VIEW_ICON_TOASTBOX_H-63)

#define WDK_VIEW_HELP_MSG_TOASTBOX_X        ((WDK_VIEW_BASE_FRAME_W-1400)/2)
#define WDK_VIEW_HELP_MSG_TOASTBOX_Y        (164)
#define WDK_VIEW_HELP_MSG_TOASTBOX_W        (1400)
#define WDK_VIEW_HELP_MSG_TOASTBOX_H        (WDK_VIEW_ICON_TOASTBOX_H-63)

#define WDK_VIEW_LINE_TITLE_X               (0)
#define WDK_VIEW_LINE_TITLE_Y               (162-4)
#define WDK_VIEW_LINE_TITLE_W               (WDK_VIEW_BASE_FRAME_W)
#define WDK_VIEW_LINE_TITLE_H               (39)

#define WDK_VIEW_ICON_MARK_X                ((WDK_VIEW_BASE_FRAME_W-4)/2)
#define WDK_VIEW_ICON_MARK_Y                (162-9)
#define WDK_VIEW_ICON_MARK_W                (4)
#define WDK_VIEW_ICON_MARK_H                (14)

#define WDK_VIEW_MSG_MARK_TXT_Y             (WDK_VIEW_ICON_TOASTBOX_H+30)
#define WDK_VIEW_MSG_MARK_TXT_H             (TXT_GRID_H)

#define WDK_VIEW_STRING_TOAST_MSG_X         ((WDK_VIEW_BASE_FRAME_W-1400)/2)
#define WDK_VIEW_STRING_TOAST_MSG_Y         (33)
#define WDK_VIEW_STRING_TOAST_MSG_H         (78)
#define WDK_VIEW_STRING_TOAST_MSG_W         (1400)

#define WDK_VIEW_ICON_WARNING_X             (0)
#define WDK_VIEW_ICON_WARNING_Y             (160+60)
#define WDK_VIEW_ICON_WARNING_W             (WDK_VIEW_BASE_FRAME_W)
#define WDK_VIEW_ICON_WARNING_H             (28)


#define WDK_VIEW_LINE_X                     (124)
#define WDK_VIEW_LINE_Y                     (560)
#define WDK_VIEW_LINE_W                     (TXT_GRID_W/22)
#define WDK_VIEW_LINE_H                     (1)

#define WDK_VIEW_LIST_TXT_W                 (WDK_VIEW_BASE_FRAME_W)
#define WDK_VIEW_LIST_TXT_H                 (164)
#define WDK_VIEW_LIST_TXT_X                 (0)
#define WDK_VIEW_LIST_TXT_Y                 ((440-164)/2) //(458-317)

#define WDK_VIEW_LIST_TXT_ITEM_X            (124)
#define WDK_VIEW_LIST_TXT_ITEM_Y            (68) //(526-458)
#define WDK_VIEW_LIST_TXT_ITEM_W            (202)
#define WDK_VIEW_LIST_TXT_ITEM_H            (28)

#define WDK_VIEW_SELECT_FRAME_Y             (0)
#define WDK_VIEW_SELECT_FRAME_H             (440)


#define WDK_VIEW_NO_SIGNAL_TXT_W                (WDK_VIEW_BASE_FRAME_W)
#define WDK_VIEW_NO_SIGNAL_TXT_H                (164)
#define WDK_VIEW_NO_SIGNAL_TXT_X                (0)
#define WDK_VIEW_NO_SIGNAL_TXT_Y                ((WDK_VIEW_CENTER_BASE_FRAME_H-WDK_VIEW_NO_SIGNAL_TXT_H)/2)

#define WDK_VIEW_ENERGY_STAR_ICON_X         (0)
#define WDK_VIEW_ENERGY_STAR_ICON_Y         (55)
#define WDK_VIEW_ENERGY_STAR_ICON_W         (54)
#define WDK_VIEW_ENERGY_STAR_ICON_H         (54)

#define WDK_VIEW_DOLBY_VISION_ICON_X         (300)
#define WDK_VIEW_DOLBY_VISION_ICON_Y         (65+15)
#define WDK_VIEW_DOLBY_VISION_ICON_W         (116)
#define WDK_VIEW_DOLBY_VISION_ICON_H         (43)

#define WDK_VIEW_ZOOM_ENERGY_STAR_ICON_X            (0)
#define WDK_VIEW_ZOOM_ENERGY_STAR_ICON_Y            (43)
#define WDK_VIEW_ZOOM_ENERGY_STAR_ICON_W            (76)
#define WDK_VIEW_ZOOM_ENERGY_STAR_ICON_H            (78)

#define WDK_VIEW_PIC_POPUP_FRAME_W         (1371)
#define WDK_VIEW_PIC_POPUP_FRAME_H         (755)

#define WDK_VIEW_PW_POPUP_FRAME_W          (1056)
#define WDK_VIEW_PW_POPUP_FRAME_H          (723)

#define WDK_VIEW_PIC_BUTTON_LEFT_X         (135)
#define WDK_VIEW_PIC_BUTTON_LEFT_Y         (555)
#define WDK_VIEW_PIC_BUTTON_LEFT_W         (210)
#define WDK_VIEW_PIC_BUTTON_LEFT_H         (54)

#define WDK_VIEW_PW_BUTTON_LEFT_X          (165)
#define WDK_VIEW_PW_BUTTON_LEFT_Y          (500)
#define WDK_VIEW_PW_BUTTON_LEFT_W          (210)
#define WDK_VIEW_PW_BUTTON_LEFT_H          (54)

#define WDK_VIEW_ENERGY_STAR_DISTANCE       (10)

#define TTS_ARGUMENT_NUMBER_BUFF_LEN            (32)

#define TTS_TOAST_MAX_NUBMER_BUFF_LEN       (256)

#define WDK_VIEW_CENTER_MSG_W           (WDK_VIEW_CENTER_BASE_FRAME_W)
#define WDK_VIEW_CENTER_MSG_H           (164)
#define WDK_VIEW_CENTER_MSG_X           (0)
#define WDK_VIEW_CENTER_MSG_Y           ((WDK_VIEW_CENTER_BASE_FRAME_H - WDK_VIEW_CENTER_MSG_H)/2)

#define SOURCE_TITLE_SCRL_TIMER   (200)
#define SOURCE_TITLE_SCRL_LEN     (15)            // if title length > SOURCE_TITLE_SCRL_LEN, should scrol

//font size

#define WDK_VIEW_HEADLINE_1_FONT_SIZE                 (42)
#define WDK_VIEW_HEADLINE_2_FONT_SIZE                 (27)
#define WDK_VIEW_CAPTION_2_FONT_SIZE                  (21)
/* Text color*/
#define WDK_VIEW_EACH_FRAME_W               (WDK_VIEW_LINE_TITLE_W/100)

static GL_COLOR_T   t_g_optl_clr_normal    =  { 255, {  85}, {  85}, {  85}} ;    /*Normal text */
//static GL_COLOR_T   t_g_optl_clr_on_cursor = { 255, { 238}, { 238}, { 238}} ;    /* On-Cursor text */
static GL_COLOR_T   t_g_optl_clr_on_cursor_highlight = { 255, { 255}, { 255}, { 255}} ;    /* On-Cursor text */
static GL_COLOR_T   t_g_optl_clr_on_cursor_highlight_oled = { 255, { 191 }, { 191 }, { 191 }};    /* On-Cursor text */

//static GL_COLOR_T   t_g_optl_clr_rrr_x = { 255, { 255}, { 0}, { 0}} ;    /* On-Cursor text */

static GL_RECT_T    t_g_rect_out = {0};
static GL_RECT_T    t_g_rect_in  = {0};


static WDK_WIDGETS_T        t_g_widget_info={0};

static INT32                ui1_sum =0;
static WDK_TOAST_PARAM_T    toast_param_temp={0};

/*wdk common res*/
static WDK_WIDGET_COMMON_RES_T     t_g_wdk_widget_common_res = {0};
static UINT32                    i4_seq=0;

static WGL_HIMG_TPL_T       arr_img_ppp[PP_POPUP_IMG_NUM] = {0};
static wgl_widget_proc_fct  pf_ppp_button_cb = NULL;

static HANDLE_T     h_g_toast_iom;
WDK_OSD_TOAST_T*    tp_g_wdk_cur_active_handle = NULL;

static HANDLE_T         h_txt_title;
static UINT32           i4_scrl_title_offset = 0;
static UTF16_T          w2s_text_title[128] = {0};
static HANDLE_T         h_srcl_title_timer;
static BOOL             h_source_timer_create = FALSE;

static VOID _toast_iom_handler(VOID*    pv_tag1,
                                   VOID*    pv_tag2,
                                   VOID*    pv_tag3)
{
   IOM_NFY_COND_T          e_nfy_cond   = (IOM_NFY_COND_T)(UINT32)pv_tag1;
   UINT32                  ui4_evt_code = (UINT32)pv_tag2;
   UINT32                  ui4_key_code = IOM_GET_EVT_GRP_ID (ui4_evt_code);

    if(e_nfy_cond == IOM_NFY_COND_BTN_DOWN)
    {
        switch(ui4_key_code)
        {
            case BTN_MENU:
            case BTN_EXIT:
            case BTN_INPUT_SRC:
            {
                if(tp_g_wdk_cur_active_handle &&
                   tp_g_wdk_cur_active_handle->e_style != WDK_CENTER_DIALOG)
                {
                    a_wdk_toast_hide(TRUE, NULL, tp_g_wdk_cur_active_handle);
                }
                break;
            }
            default:break;
        }

    }
}

static VOID _toast_iom_cb_func (
                VOID*               pv_nfy_tag,
                IOM_NFY_COND_T      e_nfy_cond,
                UINT32              ui4_evt_code,
                UINT32              ui4_data)
{
    if (IOM_NFY_COND_BTN_DOWN == e_nfy_cond &&
        NULL != tp_g_wdk_cur_active_handle)
    {
        nav_request_context_switch(_toast_iom_handler,
                                   (VOID*) (UINT32)e_nfy_cond,
                                   (VOID*) ui4_evt_code,
                                   NULL);
    }
}

static INT32 _toast_register_iom()
{
    IRRC_SETTING_T   t_irrc_setting;

    /* IOM open */
    c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
    t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
    t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = IOM_ZERO_RPT_EVT_ITVL;
    t_irrc_setting.t_rpt_evt_itvl.ui2_other = IOM_ZERO_RPT_EVT_ITVL;
    t_irrc_setting.b_notify_raw_data        = TRUE;

    return c_iom_open(IOM_DEV_TYPE_IN_IRRC,
                      IOM_DEV_ID_ANY,
                      NULL,
                      (VOID*)&t_irrc_setting,
                      NULL,
                      _toast_iom_cb_func,
                      &h_g_toast_iom);
}

/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/
static VOID _line_step_nfy_fct(
    HANDLE_T  h_timer,
    VOID*     pv_tag);

INT32 wdk_view_set_text (
    HANDLE_T                    h_txt,
    VOID*                       w2s_str
    );

//static VOID _bk_step_nfy_fct(
//  HANDLE_T  h_timer,
//  VOID*     pv_tag);

static INT32 source_scrl_title_timer_start(VOID);
static INT32 source_scrl_title_timer_stop(VOID);
static INT32 source_scrl_title_reset(UTF16_T* w2s_new_title);
static VOID _timer_scrl_title_fct(HANDLE_T  h_timer, VOID*     pv_tag);


/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    private function implementations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    public function implementations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    export function implementations
-----------------------------------------------------------------------------*/

static INT32 _wdk_widget_common_res_init(VOID)
{
    INT32                        i4_ret = 0;
    WGL_FONT_INFO_T              t_fnt_info;
    WDK_WIDGET_COMMON_RES_T     *pt_common_res = &t_g_wdk_widget_common_res;

    if (pt_common_res->b_is_init)
    {
        /* do nothing*/
    }
    else
    {

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.ui1_custom_size = WDK_VIEW_HEADLINE_2_FONT_SIZE;

    i4_ret = c_fe_create_font(t_fnt_info.a_c_font_name,
                     t_fnt_info.e_font_size,
                     t_fnt_info.e_font_style,
                     t_fnt_info.e_font_cmap,
                         &pt_common_res->h_font_handle);
    WDK_CHK_FAIL(i4_ret);

        if( t_fnt_info.e_font_size == FE_FNT_SIZE_CUSTOM )
        {
             i4_ret = c_fe_set_custom_size(pt_common_res->h_font_handle,t_fnt_info.ui1_custom_size);
             DBG_INFO(("{%s %d}x_fe_set_custom_size i4_ret=%d.\n", __FUNCTION__, __LINE__, i4_ret));
             WDK_CHK_FAIL(i4_ret);
        }

        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.ui1_custom_size = WDK_VIEW_HEADLINE_2_FONT_SIZE*2;

        i4_ret = c_fe_create_font(t_fnt_info.a_c_font_name,
                     t_fnt_info.e_font_size,
                     t_fnt_info.e_font_style,
                     t_fnt_info.e_font_cmap,
                         &pt_common_res->h_zoom_font_handle);
        WDK_CHK_FAIL(i4_ret);

        if( t_fnt_info.e_font_size == FE_FNT_SIZE_CUSTOM )
        {
             i4_ret = c_fe_set_custom_size(pt_common_res->h_zoom_font_handle,t_fnt_info.ui1_custom_size);
             DBG_INFO(("{%s %d}x_fe_set_custom_size i4_ret=%d.\n", __FUNCTION__, __LINE__, i4_ret));
             WDK_CHK_FAIL(i4_ret);
        }

        _toast_register_iom();
        pt_common_res->b_is_init = TRUE;
    }

    return WDKR_OK;

}

UINT32 _wdk_get_string_size(HANDLE_T   h_parent)
{
    UINT32                       ui4_string_width = 0;
    UINT32                       ui4_string_height= 0;
    INT32                        i4_ret = 0;
    UTF16_T                      w2s_text[192];
    HFONT_T                      h_font_handle;
    WDK_WIDGET_COMMON_RES_T     *pt_common_res = &t_g_wdk_widget_common_res;
    UINT8                       ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;

    _wdk_widget_common_res_init();

    if (ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON)
    {
        h_font_handle = pt_common_res->h_zoom_font_handle;
    }
    else
    {
        h_font_handle = pt_common_res->h_font_handle;
    }
    /* Get current display text */
    i4_ret = c_wgl_do_cmd (h_parent,
                          WGL_CMD_TEXT_GET_TEXT,
                          WGL_PACK (w2s_text),
                          WGL_PACK (192));
    WDK_CHK_FAIL(i4_ret);

    /* Get string height. */
    i4_ret = c_wgl_get_string_size(h_font_handle,
                                   w2s_text,
                                   (INT32) c_uc_w2s_strlen(w2s_text),
                                   (INT32*)&ui4_string_width,
                                   (INT32*)&ui4_string_height);
    WDK_CHK_FAIL(i4_ret);

#ifdef NEVER
    CHAR                  s_buf[32+1];
    c_uc_w2s_to_ps(w2s_text, s_buf, 32);

    DBG_LOG_PRINT(("\n[WDK_TOAST_TEST] _wdk_get_string_size LEN[%d], Name[%s],width[%d],height[%d]\n",
           c_uc_w2s_strlen(w2s_text),s_buf,ui4_string_width,ui4_string_height));
#endif /* NEVER */

   // due to customer font issue ,we need add 1 here for DTV01502665.
    return (ui4_string_width + 1) ;

}

static INT32 _wdk_toast_list_adjust(WDK_OSD_TOAST_T*            pt_this)
{
    GL_RECT_T   t_rect;
    UINT32      ui4_list_x = WDK_VIEW_LIST_TXT_ITEM_X;
    UINT32      ui4_item_w = WDK_VIEW_LIST_TXT_ITEM_W;
    UINT8       ui1_item_idx = WDK_VIEW_LIST_TXT_ITEM_W;
    UINT32      ui4_item_w_tmp;

    UINT8       ui1_energy_distance = WDK_VIEW_ENERGY_STAR_DISTANCE;

    //UINT8       ui1_zoom_mode_status = APP_CFG_CUST_ZOOM_MODE_OFF;
    //BOOL        b_is_zoom_mode;

    WDK_TOAST_STYLE_T  e_TOAST_style = pt_this->e_style;


    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} e_TOAST_style:%d, .w2s_msg_t.i4_str_num:%d\n",
        __FUNCTION__, __LINE__, e_TOAST_style, toast_param_temp.w2s_msg_t.i4_str_num )); );

  #if 0
    a_cfg_cust_get_zoom_mode(&ui1_zoom_mode_status);
    b_is_zoom_mode = (ui1_zoom_mode_status == APP_CFG_CUST_ZOOM_MODE_ON) ? TRUE : FALSE;
  #endif

    for(UINT8 ui1_idx = 0; ui1_idx < toast_param_temp.w2s_msg_t.i4_str_num; ui1_idx++)
    {
        ui1_item_idx = (ui1_idx+i4_seq)%toast_param_temp.w2s_msg_t.i4_str_num;

    #if(NAV_INPUT_SRC_UI_VERTICAL)
        if( e_TOAST_style == WDK_INPUT_LIST )
        {
            SET_RECT_BY_SIZE (&t_rect,
                    WDK_VIEW_INPUT_LIST_TXT_ITEM_X,
                    WDK_VIEW_INPUT_LIST_TXT_ITEM_Y + (ui1_item_idx * WDK_VIEW_INPUT_LIST_TXT_ITEM_H),
                    WDK_VIEW_INPUT_LIST_TXT_ITEM_W,
                    WDK_VIEW_INPUT_LIST_TXT_ITEM_H   );
        }
        else
    #endif
        {
            ui4_item_w_tmp = _wdk_get_string_size(pt_this->h_list_txt[ui1_item_idx]);
            ui4_item_w = ui4_item_w_tmp > WDK_VIEW_LIST_TXT_ITEM_W ? WDK_VIEW_LIST_TXT_ITEM_W : ui4_item_w_tmp;

            SET_RECT_BY_SIZE (&t_rect,
                    ui4_list_x,
                    WDK_VIEW_LIST_TXT_ITEM_Y-10-8,
                    ui4_item_w,
                    WDK_VIEW_LIST_TXT_ITEM_H+20+16);
        }


#ifdef NEVER
        DBG_LOG_PRINT(("\n[WDK_TOAST_TESTl  list_adjust: i4_seq[%d],ui1_idx[%d],item_idx[%d],item_x[%d],item_y[%d],item_w[%d],item_h[%d]\n",
               i4_seq,ui1_idx,ui1_item_idx,ui4_list_x,WDK_VIEW_LIST_TXT_ITEM_Y,ui4_item_w,WDK_VIEW_LIST_TXT_ITEM_H));
#endif /* NEVER */

        //do not show half string
        if(0)// (ui4_list_x + ui4_item_w > WDK_VIEW_BASE_FRAME_W)
        {
            WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_list_txt[ui1_item_idx], WGL_SW_HIDE)) ;
        }
        else
        {
            WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_list_txt[ui1_item_idx], WGL_SW_NORMAL)) ;

        #if(NAV_INPUT_SRC_UI_VERTICAL)
            if( e_TOAST_style == WDK_INPUT_LIST )
            {
                // don't move test widget
            }
            else
        #endif
            {
                if( e_TOAST_style == WDK_INPUT_LIST )
                {
                    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} ui1_idx:%d, ui1_item_idx:%d, move text:(%d %d %d %d) \n",
                        __FUNCTION__, __LINE__, ui1_idx, ui1_item_idx,
                        t_rect.i4_left, t_rect.i4_top, t_rect.i4_right, t_rect.i4_bottom)); );
                }

                c_wgl_move (pt_this->h_list_txt[ui1_item_idx], &t_rect, WGL_NO_AUTO_REPAINT);
            }

        }

#ifdef NEVER
       if ((pt_this->b_is_pic_mode)
        && (ui1_item_idx == pt_this->ui1_pic_standard_idx))
       {
           if (b_is_zoom_mode && (i4_seq == pt_this->ui1_pic_standard_idx))
           {
                SET_RECT_BY_SIZE (&t_rect,
                    ui4_list_x + ui4_item_w + ui1_energy_distance + ui4_item_w/2,
                    WDK_VIEW_ZOOM_ENERGY_STAR_ICON_Y,
                    WDK_VIEW_ZOOM_ENERGY_STAR_ICON_W,
                    WDK_VIEW_ZOOM_ENERGY_STAR_ICON_H);
           }
           else
           {
                SET_RECT_BY_SIZE (&t_rect,
                        ui4_list_x + ui4_item_w + ui1_energy_distance,
                        WDK_VIEW_ENERGY_STAR_ICON_Y,
                        WDK_VIEW_ENERGY_STAR_ICON_W,
                        WDK_VIEW_ENERGY_STAR_ICON_H);
           }

           c_wgl_move (pt_this->h_energy_star_icon, &t_rect, WGL_NO_AUTO_REPAINT);

           ui4_list_x = ui4_list_x + ui1_energy_distance + WDK_VIEW_ENERGY_STAR_ICON_W;
       }
#endif /* NEVER */


       if((ui1_idx+toast_param_temp.w2s_msg_t.i4_str_num-i4_seq)%(toast_param_temp.w2s_msg_t.i4_str_num) == 0)
       {
            toast_param_temp.ui4_sl_first_num = ui1_idx;
       }

       ui4_list_x = ui4_list_x+ui4_item_w + WDK_VIEW_LIST_TXT_W_EX;
    }


#ifdef NEVER
    if (pt_this->b_is_pic_mode)
    {
        WGL_IMG_INFO_T              t_img_info;
        INT32                       i4_ret;

        c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
        if (i4_seq == pt_this->ui1_pic_standard_idx)
        {
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
            t_img_info.u_img_data.t_standard.t_enable    = b_is_zoom_mode ? h_g_zoom_energy_star : h_g_energy_star;
            t_img_info.u_img_data.t_standard.t_disable   = b_is_zoom_mode ? h_g_zoom_energy_star : h_g_energy_star;
            t_img_info.u_img_data.t_standard.t_highlight = b_is_zoom_mode ? h_g_zoom_energy_star : h_g_energy_star;


        }
        else
        {
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
            t_img_info.u_img_data.t_standard.t_enable    = h_g_energy_star_gray;
            t_img_info.u_img_data.t_standard.t_disable   = h_g_energy_star_gray;
            t_img_info.u_img_data.t_standard.t_highlight = h_g_energy_star_gray;

        }

        if (a_cfg_cust_get_support_energy_start_by_mode_name() == FALSE)
        {
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
            t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
            t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
            t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
        }
        i4_ret = c_wgl_do_cmd (pt_this->h_energy_star_icon,
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK(WGL_IMG_FG),
                                WGL_PACK(&t_img_info));

        WDK_CHK_FAIL (i4_ret);
    }

#endif /* NEVER */

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wdk_view_create_frm
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_frm (
    HANDLE_T                    h_parent,
    INT32                       i4_x,
    INT32                       i4_y,
    INT32                       i4_w,
    INT32                       i4_h,
    WGL_HIMG_TPL_T              h_frm_bk,
    wgl_widget_proc_fct         pf_wdgt_proc,
    HANDLE_T *                  ph_widget
    )
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
    WGL_IMG_INFO_T              t_img_info;

    ui4_style = 0;

    SET_RECT_BY_SIZE (&t_rect, i4_x, i4_y, i4_w, i4_h) ;

    i4_ret = c_wgl_create_widget (h_parent,
                                HT_WGL_WIDGET_FRAME,
                                WGL_CONTENT_FRAME_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                pf_wdgt_proc,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                ph_widget);

    if (i4_ret < 0)
    {
        return WDKR_FAIL;
    }

    if( h_frm_bk != NULL_HANDLE )
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    =  h_frm_bk;
        t_img_info.u_img_data.t_standard.t_highlight =  h_frm_bk;
        t_img_info.u_img_data.t_standard.t_disable   =  h_frm_bk;

        i4_ret = c_wgl_do_cmd   (   *ph_widget,
                                    WGL_CMD_GL_SET_IMAGE,
                                    WGL_PACK(WGL_IMG_BK),
                                    WGL_PACK(&t_img_info));
        WDK_CHK_FAIL(i4_ret);
    }

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wdk_view_create_dialog_frame
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_dialog_frame(
    HANDLE_T *          ph_widget,
    HANDLE_T            h_parent)

{
    INT32           i4_ret;

    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if(ph_widget == NULL)
    {
        return WDKR_FAIL;
    }

    i4_ret = wdk_view_create_frm(h_parent,
                            WDK_VIEW_BASE_FRAME_X,
                            WDK_VIEW_BASE_FRAME_Y,
                            WDK_VIEW_BASE_FRAME_W,
                            WDK_VIEW_BASE_FRAME_H,
                            t_g_widget_info.t_img_dialog_back,
                            NULL,
                            ph_widget);
    WDK_CHK_FAIL (i4_ret);

    return WDKR_OK;
}

INT32 wdk_view_create_center_dialog_frame(
    HANDLE_T *          ph_widget,
    HANDLE_T            h_parent)

{
    if(ph_widget != NULL)
    {
        WDK_CHK_FAIL(wdk_view_create_frm(h_parent,
                                         0,
                                         0,
                                         WDK_VIEW_CENTER_BASE_FRAME_W,
                                         WDK_VIEW_CENTER_BASE_FRAME_H,
                                         t_g_widget_info.t_img_dialog_back,
                                         NULL,
                                         ph_widget));
    }
    return WDKR_OK;
}


/*----------------------------------------------------------------------------
 * Name: wdk_view_set_bk_img
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_set_bk_img (
    HANDLE_T                    h_widget ,
    WGL_HIMG_TPL_T              h_bk_img
    )
{
    INT32                       i4_ret;
    WGL_IMG_INFO_T              t_img_info;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_bk_img ;
    t_img_info.u_img_data.t_standard.t_highlight = h_bk_img ;
    t_img_info.u_img_data.t_standard.t_disable   = h_bk_img ;

    i4_ret = c_wgl_do_cmd (h_widget,
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK(WGL_IMG_BK),
                                WGL_PACK(&t_img_info));
    WDK_CHK_FAIL (i4_ret);

    return WDKR_OK;
}


/*----------------------------------------------------------------------------
 * Name: wdk_view_create_main_frame_animation
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_main_frame_animation(
    HANDLE_T            h_canvas,
    HANDLE_T *          ph_widget
    )

{
    INT32           i4_ret;
    GL_RECT_T       t_rect;

    if(ph_widget == NULL)
    {
        return WDKR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     WDK_VIEW_BASE_FRAME_X,
                     WDK_VIEW_BASE_FRAME_Y-WDK_VIEW_BASE_FRAME_H,
                     WDK_VIEW_BASE_FRAME_W,
                     WDK_VIEW_BASE_FRAME_H);

    i4_ret = wdk_view_create_frm(h_canvas,
                            WDK_VIEW_BASE_FRAME_X,
                            WDK_VIEW_BASE_FRAME_Y-WDK_VIEW_BASE_FRAME_H,
                            WDK_VIEW_BASE_FRAME_W,
                            WDK_VIEW_BASE_FRAME_H,
                            t_g_widget_info.t_img_frm_back,
                            NULL,
                            ph_widget);
    WDK_CHK_FAIL (i4_ret);

    t_g_rect_out = t_rect;

    t_g_rect_out.i4_top = (WDK_VIEW_BASE_FRAME_Y-WDK_VIEW_BASE_FRAME_H);

    t_g_rect_in.i4_left   = t_g_rect_out.i4_left;
    t_g_rect_in.i4_right  = t_g_rect_out.i4_right;
    t_g_rect_in.i4_bottom = t_g_rect_out.i4_bottom+(WGL_RECT_GET_HEIGHT(&t_g_rect_out));
    t_g_rect_in.i4_top    = t_g_rect_out.i4_top+(WGL_RECT_GET_HEIGHT(&t_g_rect_out));

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wdk_view_create_pp_popup_frame
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_pp_popup_frame(
    HANDLE_T            h_canvas,
    INT32               i4_x_offset,
    INT32               i4_y_offset,
    INT32               i4_width,
    INT32               i4_height,
    HANDLE_T *          ph_widget
    )
{
    INT32           i4_ret;

    if(ph_widget == NULL)
    {
        return WDKR_FAIL;
    }

    i4_ret = wdk_view_create_frm(h_canvas,
                                 i4_x_offset,
                                 i4_y_offset,
                                 i4_width,
                                 i4_height,
                                 NULL_HANDLE,
                                 NULL,
                                 ph_widget);
    WDK_CHK_FAIL (i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE);
    WDK_CHK_FAIL (i4_ret);

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wdk_view_create_main_frame
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_main_frame(
    HANDLE_T            h_canvas,
    HANDLE_T *          ph_widget    )

{
    INT32           i4_ret;

    if(ph_widget == NULL)
    {
        return WDKR_FAIL;
    }

    i4_ret = wdk_view_create_frm(h_canvas,
                            WDK_VIEW_BASE_FRAME_X,
                            WDK_VIEW_BASE_FRAME_Y,
                            WDK_VIEW_BASE_FRAME_W,
                            WDK_VIEW_BASE_FRAME_H,
                            t_g_widget_info.t_img_frm_back,
                            NULL,
                            ph_widget);
    WDK_CHK_FAIL (i4_ret);
    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wdk_view_create_main_frame
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_center_main_frame(
    HANDLE_T            h_canvas,
    HANDLE_T *          ph_widget    )

{

    if(ph_widget != NULL)
    {
        WDK_CHK_FAIL(wdk_view_create_frm(h_canvas,
                                         WDK_VIEW_CENTER_BASE_FRAME_X,
                                         WDK_VIEW_CENTER_BASE_FRAME_Y,
                                         WDK_VIEW_CENTER_BASE_FRAME_W,
                                         WDK_VIEW_CENTER_BASE_FRAME_H,
                                         t_g_widget_info.t_img_frm_back,
                                         NULL,
                                         ph_widget));
    }
    return WDKR_OK;
}

#if(NAV_INPUT_SRC_UI_VERTICAL)
INT32 wdk_view_create_input_list_frame(
    HANDLE_T            h_canvas,
    HANDLE_T *          ph_widget    )

{
    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} 0x%X create input_list frame:h_base_frm(%d %d %d %d) \n",
        __FUNCTION__, __LINE__, h_canvas,
        WDK_INPUT_LIST_FRAME_X, WDK_INPUT_LIST_FRAME_Y,
        WDK_INPUT_LIST_FRAME_W, WDK_INPUT_LIST_FRAME_H)); );

    if(ph_widget != NULL)
    {
        WDK_CHK_FAIL(wdk_view_create_frm(h_canvas,
                                         WDK_INPUT_LIST_FRAME_X,
                                         WDK_INPUT_LIST_FRAME_Y,
                                         WDK_INPUT_LIST_FRAME_W,
                                         WDK_INPUT_LIST_FRAME_H,
                                         t_g_widget_info.t_img_frm_back,
                                         NULL,
                                         ph_widget));
    }
    return WDKR_OK;
}

#endif

/*----------------------------------------------------------------------------
 * Name: wdk_view_image_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_image_init(VOID* pv_param)
{
    WDK_TOAST_PARAM_T*  toast_param = (WDK_TOAST_PARAM_T*)pv_param;

    WDK_TOAST_STYLE_T e_toast_style = toast_param->e_toast_style;

    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d}e_toast_style:%d \n",
        __FUNCTION__, __LINE__, e_toast_style )); );

    a_wdk_image_init();

    switch(e_toast_style)
    {
        case WDK_TOAST_SETTINGS_SLIDER:
            t_g_widget_info.t_img_title_line = h_g_wdk_track_fill;
            t_g_widget_info.t_img_toast_box_icon  = h_g_wdk_toast_box;
            t_g_widget_info.t_img_frm_back = h_g_wdk_gradient_top;
            t_g_widget_info.t_img_dialog_back = h_g_wdk_gradient_top;
            break;
        case WDK_STRING_TOAST:
            t_g_widget_info.t_img_toast_box_icon  = h_g_wdk_toast_box_settings;
            t_g_widget_info.t_img_frm_back = h_g_wdk_gradient_top;
            t_g_widget_info.t_img_dialog_back = h_g_wdk_gradient_top;
            break;
        case WDK_WARNING_TOAST:
            t_g_widget_info.t_img_toast_box_icon  = h_g_wdk_toast_box_settings;
            t_g_widget_info.t_img_frm_back = h_g_wdk_gradient_top;
            t_g_widget_info.t_img_dialog_back = h_g_wdk_gradient_top;
            break;

        case WDK_SINGLE_SELECT_LIST:
        case WDK_INPUT_LIST:

            WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

            t_g_widget_info.t_img_title_line = h_g_wdk_track_fill;

        #if( NAV_INPUT_SRC_UI_VERTICAL )
            if( e_toast_style == WDK_INPUT_LIST )
            {
                WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} todo: Add background image!!!! \n", __FUNCTION__, __LINE__ )); );
                //t_g_widget_info.t_img_frm_back = NULL_HANDLE; // todo
                //t_g_widget_info.t_img_frm_back = h_g_wdk_single_select_list;
                t_g_widget_info.t_img_frm_back = h_g_string_toast;
                t_g_widget_info.t_img_toast_box_icon  = NULL_HANDLE;
            }
            else
        #endif
            {
                t_g_widget_info.t_img_frm_back = h_g_wdk_single_select_list;
                t_g_widget_info.t_img_toast_box_icon  = h_g_wdk_toast_box;
            }

            t_g_widget_info.t_img_dialog_back = NULL_HANDLE;
            break;

        case WDK_NO_SINGLE:
            t_g_widget_info.t_img_frm_back =    h_g_wdk_single_select_list;
            t_g_widget_info.t_img_dialog_back = NULL_HANDLE;
            break;

        case WDK_CENTER_DIALOG:
            nav_img_create_revolt_misc_bk(&(t_g_widget_info.t_img_frm_back));
            nav_img_create_revolt_misc_bk(&(t_g_widget_info.t_img_dialog_back));
            //t_g_widget_info.t_img_frm_back = h_g_wdk_vkb_edit_hlt_bk;
            //t_g_widget_info.t_img_dialog_back = h_g_wdk_vkb_edit_hlt_bk;
            break;

        case WDK_PIC_PW_POPUP:
            for (UINT32 ui4_idx = 0; ui4_idx < PP_POPUP_IMG_NUM; ++ui4_idx) {
                WDK_CHK_FAIL(a_wdk_create_pp_popup_img_tpl(&arr_img_ppp[ui4_idx], ui4_idx));
            }
            break;
        case WDK_SCREEN_CENTER_MSG:
            t_g_widget_info.t_img_frm_back =    NULL_HANDLE;
            t_g_widget_info.t_img_dialog_back = NULL_HANDLE;
            break;
        default:
            break;
    }
    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wdk_view_create_icon
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_icon(
    HANDLE_T                    h_parent,
    INT32                       i4_x,
    INT32                       i4_y,
    INT32                       i4_w,
    INT32                       i4_h,
    WGL_HIMG_TPL_T              h_img,
    HANDLE_T *                  ph_widget
    )
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;

    if (!ph_widget)
    {
        return WDKR_FAIL ;
    }

    SET_RECT_BY_SIZE(&t_rect, i4_x, i4_y, i4_w, i4_h) ;

    i4_ret = c_wgl_create_widget (h_parent,
                                HT_WGL_WIDGET_ICON,
                                WGL_CONTENT_ICON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID *)WGL_STL_GL_NO_BK,
                                NULL,
                                ph_widget);
    WDK_CHK_FAIL (i4_ret);

    /* set icon image buffer */

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_img;
    t_img_info.u_img_data.t_standard.t_disable   = h_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_img;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK(WGL_IMG_FG),
                                WGL_PACK(&t_img_info));
    WDK_CHK_FAIL (i4_ret);

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                                WGL_CMD_ICON_SET_ALIGN,
                                (VOID*)WGL_AS_CENTER_CENTER,
                                NULL);
    WDK_CHK_FAIL (i4_ret);

    /* make icon invisible */
    i4_ret = c_wgl_set_visibility (*ph_widget, WGL_SW_HIDE);
    WDK_CHK_FAIL (i4_ret);

    return WDKR_OK;
}

static INT32 _wdk_view_ppp_button_proc_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2
                    )
{
    /*
    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        c_wgl_do_cmd(h_widget,
                     WGL_CMD_BTN_SET_PUSHED,
                     WGL_PACK(TRUE),
                     NULL);
    }
    else if(ui4_msg == WGL_MSG_KEY_UP)
    {
        c_wgl_do_cmd(h_widget,
                     WGL_CMD_BTN_SET_PUSHED,
                     WGL_PACK(FALSE),
                     NULL);
    }
    */
    if (pf_ppp_button_cb) {
        return pf_ppp_button_cb(h_widget, ui4_msg, pv_param1, pv_param2);
    } else {
        return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
    }
}

/*----------------------------------------------------------------------------
 * Name: wdk_view_create_button
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_ppp_button(
    HANDLE_T                    h_parent,
    INT32                       i4_x,
    INT32                       i4_y,
    INT32                       i4_w,
    INT32                       i4_h,
    HANDLE_T *                  ph_widget
    )
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info = {0};
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_COLOR_INFO_T            t_clr_info;
    GL_COLOR_T                  t_ui_color = { 255, { 240 }, { 240 }, { 240 }};

    if (!ph_widget)
    {
        return WDKR_FAIL ;
    }

    SET_RECT_BY_SIZE(&t_rect, i4_x, i4_y, i4_w, i4_h);

    i4_ret = c_wgl_create_widget (h_parent,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                _wdk_view_ppp_button_proc_fct,
                                255,
                                (VOID *)0,
                                NULL,
                                ph_widget);
    WDK_CHK_FAIL (i4_ret);

    /* set button image buffer */
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = arr_img_ppp[PP_POPUP_BUTTON_GRAY];
    t_img_info.u_img_data.t_extend.t_highlight          = arr_img_ppp[PP_POPUP_BUTTON_TEAL];
    t_img_info.u_img_data.t_extend.t_disable            = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push               = arr_img_ppp[PP_POPUP_BUTTON_TEAL];
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = arr_img_ppp[PP_POPUP_BUTTON_GRAY];

    i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_GL_SET_IMAGE,
                            WGL_PACK(WGL_IMG_BK),
                            WGL_PACK(&t_img_info));
    WDK_CHK_FAIL (i4_ret);

    /* set button alignment */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_BTN_SET_ALIGN,
                            (VOID*)WGL_AS_CENTER_CENTER,
                            NULL);
    WDK_CHK_FAIL (i4_ret);

    /* set text color */
    t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_enable             = t_ui_color;
    t_clr_info.u_color_data.t_extend.t_disable            = t_ui_color;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_ui_color;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_ui_color;
    t_clr_info.u_color_data.t_extend.t_push               = t_ui_color;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_ui_color;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    WDK_CHK_FAIL (i4_ret);

    /* Set Font */
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    WDK_CHK_FAIL (i4_ret);

    /* make button invisible */
    i4_ret = c_wgl_set_visibility (*ph_widget, WGL_SW_HIDE);
    WDK_CHK_FAIL (i4_ret);

    return WDKR_OK;
}


/*----------------------------------------------------------------------------
 * Name: wdk_view_create_toast_box_icon
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_toast_box_icon(
    HANDLE_T            h_frm,
    HANDLE_T *          ph_widget
    )
{

    INT32   i4_ret;

    if(ph_widget == NULL)
    {
        return WDKR_FAIL;
    }


    i4_ret = wdk_view_create_icon(h_frm ,
                                WDK_VIEW_ICON_TOASTBOX_X,
                                WDK_VIEW_ICON_TOASTBOX_Y,
                                WDK_VIEW_ICON_TOASTBOX_W,
                                WDK_VIEW_ICON_TOASTBOX_H,
                                t_g_widget_info.t_img_toast_box_icon,
                                ph_widget);
    WDK_CHK_FAIL (i4_ret);

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wdk_view_create_txt
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_txt (
    HANDLE_T                    h_parent,
    UINT8                       ui1_align,
    INT32                       i4_x,
    INT32                       i4_y,
    INT32                       i4_w,
    INT32                       i4_h,
    HANDLE_T*                   ph_widget
    )
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;

    ui4_style       =           WGL_STL_GL_NO_IMG_UI
                                | WGL_STL_TEXT_MAX_512
                                | WGL_STL_GL_NO_BK
                                | WGL_STL_TEXT_MULTILINE
                                | WGL_STL_TEXT_MAX_DIS_10_LINE;

    SET_RECT_BY_SIZE(&t_rect,i4_x,i4_y,i4_w,i4_h);

    i4_ret = c_wgl_create_widget (h_parent,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                ph_widget);
    WDK_CHK_FAIL (i4_ret);

    /* set content insert */
    c_memset (&t_inset ,0 ,sizeof (WGL_INSET_T)) ;
    i4_ret = c_wgl_do_cmd   (   *ph_widget,
                                WGL_CMD_TEXT_SET_CNT_INSET,
                                WGL_PACK(&t_inset),
                                NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = WDK_VIEW_HEADLINE_2_FONT_SIZE;

    i4_ret = c_wgl_do_cmd   (   *ph_widget,
                                WGL_CMD_GL_SET_FONT,
                                WGL_PACK(&t_fnt_info),
                                NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type       =   WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_optl_clr_on_cursor_highlight;
    t_clr_info.u_color_data.t_extend.t_enable             = t_g_optl_clr_on_cursor_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_optl_clr_on_cursor_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_optl_clr_on_cursor_highlight;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_optl_clr_on_cursor_highlight;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_optl_clr_on_cursor_highlight;


    i4_ret = c_wgl_do_cmd   (   *ph_widget,
                                WGL_CMD_GL_SET_COLOR,
                                WGL_PACK(WGL_CLR_TEXT),
                                WGL_PACK(&t_clr_info ));
    WDK_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd   (   *ph_widget,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(ui1_align),
                                NULL);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

INT32 wdk_view_create_list_txt (
    HANDLE_T                    h_parent,
    UINT8                       ui1_align,
    INT32                       i4_x,
    INT32                       i4_y,
    INT32                       i4_w,
    INT32                       i4_h,
    HANDLE_T*                   ph_widget,
    UINT8                       ui1_idx
    )
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;

    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} h_parent:0x%X, ui1_idx:%d, i4_x:%d, i4_y:%d, i4_w:%d, i4_h:%d\n",
        __FUNCTION__, __LINE__, h_parent, ui1_idx, i4_x, i4_y, i4_w, i4_h )); );


    if(ui1_idx == 0)
    {
        ui4_style = WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32|WGL_STL_TEXT_MS_NO_SMARTCUT;
    }
    else
    {
        ui4_style = WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_32|WGL_STL_TEXT_SMART_CUT;
    }

    SET_RECT_BY_SIZE(&t_rect,i4_x,i4_y,i4_w,i4_h);

    i4_ret = c_wgl_create_widget (h_parent,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                ph_widget);
    WDK_CHK_FAIL (i4_ret);
    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} 0x%X create_widget(text, (%d %d %d %d) => 0x%X \n",
        __FUNCTION__, __LINE__, h_parent,
        t_rect.i4_left, t_rect.i4_top, t_rect.i4_right, t_rect.i4_bottom, *ph_widget )); );




    /* set content insert */
    c_memset (&t_inset ,0 ,sizeof (WGL_INSET_T)) ;
    i4_ret = c_wgl_do_cmd   (   *ph_widget,
                                WGL_CMD_TEXT_SET_CNT_INSET,
                                WGL_PACK(&t_inset),
                                NULL);
    WDK_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = WDK_VIEW_HEADLINE_2_FONT_SIZE;

    i4_ret = c_wgl_do_cmd (   *ph_widget,
                                WGL_CMD_GL_SET_FONT,
                                WGL_PACK(&t_fnt_info),
                                NULL);
    WDK_CHK_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type       =   WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_optl_clr_normal;
    t_clr_info.u_color_data.t_extend.t_enable             = t_g_optl_clr_normal;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_optl_clr_on_cursor_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_optl_clr_on_cursor_highlight;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_optl_clr_on_cursor_highlight;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_optl_clr_on_cursor_highlight;

    i4_ret = c_wgl_do_cmd   (   *ph_widget,
                                WGL_CMD_GL_SET_COLOR,
                                WGL_PACK(WGL_CLR_TEXT),
                                WGL_PACK(&t_clr_info ));
    WDK_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd   (   *ph_widget,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(ui1_align),
                                NULL);
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}


/*----------------------------------------------------------------------------
 * Name: wdk_view_create_txt
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_msg_toastbox(
    HANDLE_T            h_frm,
    HANDLE_T *          ph_widget
    )
{
    INT32   i4_ret;

    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if(ph_widget == NULL)
    {
        return WDKR_FAIL;
    }

    i4_ret = wdk_view_create_txt(h_frm,
                                WGL_AS_CENTER_BOTTOM,
                                WDK_VIEW_MSG_TOASTBOX_X,
                                WDK_VIEW_MSG_TOASTBOX_Y,
                                WDK_VIEW_MSG_TOASTBOX_W,
                                WDK_VIEW_MSG_TOASTBOX_H,
                                ph_widget);
    WDK_CHK_FAIL (i4_ret);

    return WDKR_OK;
}


/*----------------------------------------------------------------------------
 * Name: wdk_view_create_txt
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

INT32 wdk_view_create_help_msg_toastbox(
    HANDLE_T            h_frm,
    HANDLE_T *          ph_widget
    )
{
    INT32   i4_ret;

    if(ph_widget == NULL)
    {
        return WDKR_FAIL;
    }

    i4_ret = wdk_view_create_txt(h_frm,
                                WGL_AS_CENTER_BOTTOM,
                                WDK_VIEW_HELP_MSG_TOASTBOX_X,
                                WDK_VIEW_HELP_MSG_TOASTBOX_Y,
                                WDK_VIEW_HELP_MSG_TOASTBOX_W,
                                WDK_VIEW_HELP_MSG_TOASTBOX_H,
                                ph_widget);
    WDK_CHK_FAIL (i4_ret);

    return WDKR_OK;
}


/*----------------------------------------------------------------------------
 * Name: wdk_view_create_center_msg
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_center_msg(
    HANDLE_T            h_frm,
    HANDLE_T *          ph_widget
    )
{
    if(ph_widget != NULL)
    {
        WDK_CHK_FAIL(wdk_view_create_txt(h_frm,
                                         WGL_AS_CENTER_CENTER,
                                         WDK_VIEW_CENTER_MSG_X,
                                         WDK_VIEW_CENTER_MSG_Y,
                                         WDK_VIEW_CENTER_MSG_W,
                                         WDK_VIEW_CENTER_MSG_H,
                                         ph_widget));
    }
    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wdk_view_create_title_line
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_title_line(
    HANDLE_T            h_frm,
    HANDLE_T *          ph_widget
    )
{

    INT32   i4_ret;
    if(ph_widget == NULL)
    {
        return WDKR_FAIL;
    }
    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    i4_ret = wdk_view_create_frm(h_frm,
                                WDK_VIEW_LINE_TITLE_X,
                                WDK_VIEW_LINE_TITLE_Y,
                                WDK_VIEW_LINE_TITLE_W,
                                WDK_VIEW_LINE_TITLE_H,
                                t_g_widget_info.t_img_title_line,
                                NULL,
                                ph_widget);
    WDK_CHK_FAIL (i4_ret);
    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wdk_view_create_select_list_txt
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_create_select_list_txt(
    HANDLE_T            h_frm,
    HANDLE_T *          ph_widget,
    WDK_OSD_TOAST_T*     pt_this
    )
{
    UINT8                       ui1_idx;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
//  WGL_COLOR_INFO_T            t_clr_info;

    if( pt_this == NULL )
    {
        return WDKR_INV_ARG;
    }

    WDK_TOAST_STYLE_T  e_TOAST_style = pt_this->e_style;

    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} e_TOAST_style:%d\n", __FUNCTION__, __LINE__, e_TOAST_style )); );


    ui4_style = 0;
    ui4_style |= WGL_STL_GL_NO_IMG_UI;


#if(NAV_INPUT_SRC_UI_VERTICAL )
    if( e_TOAST_style == WDK_INPUT_LIST )
    {
        SET_RECT_BY_SIZE (&t_rect,
            WDK_VIEW_INPUT_LIST_BOX_X,  WDK_VIEW_INPUT_LIST_BOX_Y,
            WDK_VIEW_INPUT_LIST_BOX_W,  WDK_VIEW_INPUT_LIST_BOX_H);
    }
    else
#endif
    {
        SET_RECT_BY_SIZE (&t_rect,
            WDK_VIEW_LIST_TXT_X, WDK_VIEW_LIST_TXT_Y,
            WDK_VIEW_LIST_TXT_W, WDK_VIEW_LIST_TXT_H) ;
    }

    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} h_dialog_frm(0x%X) create h_list_txt_frm:(%d %d %d %d) \n",
        __FUNCTION__, __LINE__, h_frm, t_rect.i4_left, t_rect.i4_top, t_rect.i4_right, t_rect.i4_bottom)); );

    /*create list frm*/
    WDK_CHK_FAIL( c_wgl_create_widget (h_frm,
                                HT_WGL_WIDGET_FRAME,
                                WGL_CONTENT_FRAME_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                ph_widget));

    /*create list item*/
    pt_this->h_list_txt = (HANDLE_T*)c_mem_alloc(sizeof(HANDLE_T)*toast_param_temp.w2s_msg_t.i4_str_num);


    INT32 i4_x, i4_y, i4_w, i4_h;

    for(ui1_idx = 0; ui1_idx < toast_param_temp.w2s_msg_t.i4_str_num; ui1_idx++)
    {
    #if(NAV_INPUT_SRC_UI_VERTICAL )
        if( e_TOAST_style == WDK_INPUT_LIST )
        {
            i4_x = WDK_VIEW_INPUT_LIST_TXT_ITEM_X;
            i4_y = WDK_VIEW_INPUT_LIST_TXT_ITEM_Y + (ui1_idx * WDK_VIEW_INPUT_LIST_TXT_ITEM_H);
            i4_w = WDK_VIEW_INPUT_LIST_TXT_ITEM_W;
            i4_h = WDK_VIEW_INPUT_LIST_TXT_ITEM_H;
        }
        else
    #endif
        {
            i4_x = WDK_VIEW_LIST_TXT_ITEM_X + ui1_idx * WDK_VIEW_LIST_TXT_W_EX;
            i4_y = WDK_VIEW_LIST_TXT_ITEM_Y;
            i4_w = WDK_VIEW_LIST_TXT_ITEM_W;
            i4_h = WDK_VIEW_LIST_TXT_ITEM_H;
        }

        WDK_CHK_FAIL( wdk_view_create_list_txt(*ph_widget,
                                     WGL_AS_LEFT_CENTER,
                                     i4_x, i4_y, i4_w, i4_h,
                                     &pt_this->h_list_txt[ui1_idx],
                                     ui1_idx));

        c_wgl_set_visibility (pt_this->h_list_txt[ui1_idx], WGL_SW_NORMAL);

        c_wgl_do_cmd(pt_this->h_list_txt[ui1_idx],
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_this),
                          NULL);
    }


    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wdk_anim_start_move_animation
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wdk_anim_start_move_animation(
    HANDLE_T            h_anim_move,
    VOID*               pv_param1,
    VOID*               pv_param2)
{
    INT32        i4_ret = WDKR_OK;
    GL_RECT_T*   pt_rect_from = NULL;
    GL_RECT_T*   pt_rect_to = NULL;
    WGL_ANIMATION_DATA_T   t_anim_data;
    WGL_ANIM_CONTEXT_T e_wdk_anim_context = ANIM_CONTEXT_APP_SYNC;

    /* Get move animation start, end position */
    pt_rect_from = (GL_RECT_T*)pv_param1;
    pt_rect_to   = (GL_RECT_T*)pv_param2;

    /* Check move animation start, end position */
    if ((NULL == pt_rect_from) ||
        (NULL == pt_rect_to))
    {
        return WDKR_INV_ARG;
    }

    /* Check animation handle validation */
    if (NULL_HANDLE == h_anim_move)
    {
        return WDKR_INV_ARG;
    }

    do
    {
        /* Clear animation data */
        c_memset (&t_anim_data, 0, sizeof (WGL_ANIMATION_DATA_T));

        /* Move animation widget */
        i4_ret = c_wgl_move (h_anim_move,
                             pt_rect_from,
                             WGL_NO_AUTO_REPAINT);
        if (i4_ret != WGLR_OK)
        {
            break;
        }

        /* Stop origional animation firstly */
        i4_ret = c_wgl_end_animation (h_anim_move, NULL, NULL);
        if (i4_ret != WGLR_OK)
        {
            DBG_INFO (("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        /* begin animation */
        t_anim_data.ui2_count = 1;

        /* Alloc memory for animation control data */
        t_anim_data.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_anim_data.ui2_count));
        t_anim_data.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_anim_data.ui2_count));
        if((NULL == t_anim_data.pt_anim_data) ||
           (NULL == t_anim_data.pt_path_mode))
        {
            DBG_INFO(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        c_memset(t_anim_data.pt_anim_data,0,sizeof(WGL_ANIM_DATA_INFO));
        c_memset(t_anim_data.pt_path_mode,0,sizeof(WGL_ANIM_PATH_DATA_T));

        /* Initialize animation path mode */
        t_anim_data.ui4_flag = WGL_ANIM_DATA_FLAG_PATH_MODE_INF;
        t_anim_data.pt_path_mode->ui2_anim_type = WGL_ANIM_TYPE_MOVE;

        t_anim_data.pt_path_mode->ui2_total_steps = 4;
        t_anim_data.pt_path_mode->ui2_frame_interval = (UINT16)c_wgl_get_tick_interval();
        t_anim_data.pt_path_mode->ui4_start_tick = 0;
        //t_anim_data.pt_path_mode->pf_type_cb = NULL;

        /* Initialize animation data info */
        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF;
        t_anim_data.pt_anim_data->ui2_anim_type |= WGL_ANIM_TYPE_MOVE;

        t_anim_data.pt_anim_data->u_data.t_move.i2_start_x = pt_rect_from->i4_left;
        t_anim_data.pt_anim_data->u_data.t_move.i2_start_y = pt_rect_from->i4_top;
        t_anim_data.pt_anim_data->u_data.t_move.i2_end_x   = pt_rect_to->i4_left;
        t_anim_data.pt_anim_data->u_data.t_move.i2_end_y   = pt_rect_to->i4_top;

        t_anim_data.pt_anim_data->pf_type_cb = WGL_ANIM_MOVE_PATH_JUMP;

        /* Set focus to animation widget */
        //c_wgl_set_focus(h_anim_move, WGL_NO_AUTO_REPAINT);

        /* Show animation widget */
        c_wgl_set_visibility(h_anim_move, WGL_SW_NORMAL);

        /* Start animation */
        i4_ret= c_wgl_start_animation(
                                      h_anim_move,
                                      &t_anim_data,
                                      e_wdk_anim_context);
        if (i4_ret != WGLR_OK)
        {
            DBG_INFO(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

    } while(0);

    /* Free memory for animation control data */
    if (t_anim_data.pt_anim_data)
    {
        c_mem_free(t_anim_data.pt_anim_data);
    }

    if (t_anim_data.pt_path_mode)
    {
        c_mem_free(t_anim_data.pt_path_mode);
    }

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wdk_view_set_text
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_view_set_text (
    HANDLE_T                    h_txt,
    VOID*                       w2s_str
    )
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd (h_txt,
                           WGL_CMD_TEXT_SET_TEXT,
                           w2s_str,
                           (VOID*)c_uc_w2s_strlen(w2s_str) );
    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

INT32 wdk_view_set_button_text(
    HANDLE_T                   h_hdr,
    VOID*                      w2s_str
    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(h_hdr,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(w2s_str),
                            WGL_PACK(c_uc_w2s_strlen(w2s_str)));

    WDK_CHK_FAIL(i4_ret);

    return WDKR_OK;
}

INT32 wdk_view_set_font(HANDLE_T    h_txt, UINT8   ui1_font_size, BOOL b_need_zoom)
{
    WGL_FONT_INFO_T t_fnt_info;
    INT32           i4_ret;
    UINT8           ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;

    i4_ret = a_cfg_cust_get_zoom_mode(&ui1_zoom_mode_value);
    WDK_CHK_FAIL(i4_ret);

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    if (ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON && b_need_zoom)
    {
        t_fnt_info.ui1_custom_size = ui1_font_size * 2;
    }
    else
    {
        t_fnt_info.ui1_custom_size = ui1_font_size;
    }

    i4_ret = c_wgl_do_cmd( h_txt,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    WDK_CHK_FAIL(i4_ret);
    return WDKR_OK;
}
extern BOOL a_is_oled_compensation_support();
/*----------------------------------------------------------------------------
 * Name: a_wdk_toast_box_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_wdk_toast_init (
    HANDLE_T            h_canvas,
    VOID*               pv_param,
    WDK_OSD_TOAST_T*    t_g_wdk_handle)
{

    INT32   i4_ret  = WDKR_OK;
    WDK_OSD_TOAST_T*     pt_this = t_g_wdk_handle;

    if (a_is_oled_compensation_support())
    {
        t_g_optl_clr_on_cursor_highlight = t_g_optl_clr_on_cursor_highlight_oled;
    }

    WDK_TOAST_PARAM_T*  toast_param = (WDK_TOAST_PARAM_T*)pv_param;
    c_memcpy(&toast_param_temp,toast_param,sizeof(WDK_TOAST_PARAM_T));

    DBG_INFO(("\r\n %s,%s(),%d %d b_have_init=%d \r\n", __FILE__,__FUNCTION__,__LINE__,toast_param->e_toast_style,pt_this->b_have_init));

    if(NULL == pt_this ||
       pt_this->b_have_init)
    {
        return WDKR_OK;
    }


    WDK_TOAST_STYLE_T e_toast_style = toast_param->e_toast_style;

    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d}e_toast_style:%d \n",
        __FUNCTION__, __LINE__, e_toast_style )); );


    /*value reset*/
    pt_this->b_is_pic_mode = FALSE;
    pt_this->ui1_pic_standard_idx = 0;

    pt_this->e_style = e_toast_style;


    i4_ret = wdk_view_image_init(pv_param);
    WDK_CHK_FAIL (i4_ret);

    if(toast_param->e_toast_style == WDK_SINGLE_SELECT_LIST ||
       toast_param->e_toast_style == WDK_INPUT_LIST         ||
       toast_param->e_toast_style == WDK_NO_SINGLE          ||
       toast_param->e_toast_style == WDK_CENTER_DIALOG      ||
       toast_param->e_toast_style == WDK_PIC_PW_POPUP       ||
       toast_param->e_toast_style == WDK_SCREEN_CENTER_MSG)
    {
        /*create frame */
        if (NULL_HANDLE == pt_this->h_base_frm)
        {
        #if(NAV_INPUT_SRC_UI_VERTICAL )
            if( toast_param->e_toast_style == WDK_INPUT_LIST )
            {
                WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

                //WDK_CHK_FAIL(wdk_view_create_center_main_frame(h_canvas,&pt_this->h_base_frm));
                WDK_CHK_FAIL(wdk_view_create_input_list_frame(h_canvas,&pt_this->h_base_frm));
            }
            else
        #endif
            if (toast_param->e_toast_style == WDK_NO_SINGLE ||
                toast_param->e_toast_style == WDK_INPUT_LIST ||
                toast_param->e_toast_style == WDK_SINGLE_SELECT_LIST ||
                toast_param->e_toast_style == WDK_SCREEN_CENTER_MSG)
            {
                if(toast_param->e_toast_style == WDK_INPUT_LIST)
                {
                    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );
                }

                WDK_CHK_FAIL(wdk_view_create_center_main_frame(h_canvas,&pt_this->h_base_frm));
            }
            else if (toast_param->e_toast_style == WDK_PIC_PW_POPUP)
            {
                i4_ret = wdk_view_create_pp_popup_frame(h_canvas,
                                    toast_param->style.style_ppp.i4_frame_x_offset,
                                    toast_param->style.style_ppp.i4_frame_y_offset,
                                    WDK_VIEW_PIC_POPUP_FRAME_W,
                                    WDK_VIEW_PIC_POPUP_FRAME_H,
                                    &pt_this->h_base_frm);
                WDK_CHK_FAIL (i4_ret);
            }
            else
            {
                WDK_CHK_FAIL(wdk_view_create_main_frame(h_canvas,&pt_this->h_base_frm));
            }
        }
    }
    else
    {
        /*create animation frame */
        if (NULL_HANDLE == pt_this->h_base_frm)
        {
            WDK_CHK_FAIL(wdk_view_create_main_frame_animation(h_canvas,&pt_this->h_base_frm));
        }
    }

    /*create dialog frame */
    if( NULL_HANDLE == pt_this->h_dialog_frm )
    {
    #if(NAV_INPUT_SRC_UI_VERTICAL )
        if( toast_param->e_toast_style == WDK_INPUT_LIST )
        {
            WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} h_base_frm(0x%X) create h_dialog_frm(%d %d %d %d) \n",
                __FUNCTION__, __LINE__, (UINT32)pt_this->h_base_frm,
                WDK_INPUT_LIST_DIALOG_FRAME_X, WDK_INPUT_LIST_DIALOG_FRAME_Y,
                WDK_INPUT_LIST_DIALOG_FRAME_W, WDK_INPUT_LIST_DIALOG_FRAME_H)); );

            i4_ret = wdk_view_create_frm( pt_this->h_base_frm,
                                WDK_INPUT_LIST_DIALOG_FRAME_X,
                                WDK_INPUT_LIST_DIALOG_FRAME_Y,
                                WDK_INPUT_LIST_DIALOG_FRAME_W,
                                WDK_INPUT_LIST_DIALOG_FRAME_H,
                                NULL_HANDLE, //t_g_widget_info.t_img_dialog_back,
                                NULL,
                                &(pt_this->h_dialog_frm) );
            WDK_CHK_FAIL (i4_ret);

        #if 1 // set h_dialog_frm color
            GL_COLOR_T          t_dialog_frm_back_color = NAV_COLOR(NAV_COLOR_ID_BLACK);
            //GL_COLOR_T          t_color = { 128, { 106}, { 106}, { 106}};
            WGL_COLOR_INFO_T    t_clr_info = {0};

            t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
            t_clr_info.u_color_data.t_standard.t_enable     = t_dialog_frm_back_color;
            t_clr_info.u_color_data.t_standard.t_highlight    = t_dialog_frm_back_color;
            t_clr_info.u_color_data.t_standard.t_disable    = t_dialog_frm_back_color;
            c_wgl_do_cmd(pt_this->h_dialog_frm,
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK(WGL_CLR_BK),
                                  WGL_PACK(&t_clr_info));
        #endif

        }
        else
    #endif
        if (toast_param->e_toast_style == WDK_NO_SINGLE ||
            toast_param->e_toast_style == WDK_SCREEN_CENTER_MSG)
        {
            WDK_CHK_FAIL(wdk_view_create_center_dialog_frame(&pt_this->h_dialog_frm, pt_this->h_base_frm));
        }
        else if (toast_param->e_toast_style == WDK_PIC_PW_POPUP)
        {
            WDK_CHK_FAIL(wdk_view_create_pp_popup_frame(h_canvas,
                                    toast_param->style.style_ppp.i4_frame_x_offset+100,
                                    toast_param->style.style_ppp.i4_frame_y_offset,
                                    WDK_VIEW_PW_POPUP_FRAME_W,
                                    WDK_VIEW_PW_POPUP_FRAME_H,
                                    &pt_this->h_dialog_frm));
        }
        else
        {
            WDK_CHK_FAIL(wdk_view_create_dialog_frame(&pt_this->h_dialog_frm, pt_this->h_base_frm));
        }
    }

    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} toast_param->e_toast_style:%d \n",
        __FUNCTION__, __LINE__, toast_param->e_toast_style )); );

    switch(toast_param->e_toast_style)
    {
        case WDK_TOAST_SETTINGS_SLIDER:
            /*create toast box line*/
            if (NULL_HANDLE == pt_this->h_title_line)
            {
                WDK_CHK_FAIL(wdk_view_create_title_line(pt_this->h_dialog_frm,&pt_this->h_title_line));
            }

            /*create track cap right*/
            i4_ret = wdk_view_create_icon(pt_this->h_dialog_frm ,
                                WDK_VIEW_LINE_TITLE_X,
                                WDK_VIEW_LINE_TITLE_Y,
                                2,
                                WDK_VIEW_LINE_TITLE_H,
                                h_g_wdk_track_cap_right,
                                &pt_this->h_track_cap_right);

            /*create track cap left*/
            i4_ret = wdk_view_create_icon(pt_this->h_dialog_frm ,
                                WDK_VIEW_LINE_TITLE_X,
                                WDK_VIEW_LINE_TITLE_Y,
                                2,
                                WDK_VIEW_LINE_TITLE_H,
                                h_g_wdk_track_cap_left,
                                &pt_this->h_track_cap_left);

            /*create eq hash mark icon*/
            i4_ret = wdk_view_create_icon(pt_this->h_dialog_frm ,
                                WDK_VIEW_ICON_MARK_X,
                                WDK_VIEW_ICON_MARK_Y,
                                WDK_VIEW_ICON_MARK_W,
                                WDK_VIEW_ICON_MARK_H,
                                h_g_wdk_eq_hash_mark,
                                &pt_this->h_eq_hash_mark);
            WDK_CHK_FAIL (i4_ret);

            /*create eq msg*/
            i4_ret = wdk_view_create_txt(pt_this->h_dialog_frm,
                                WGL_AS_CENTER_TOP,
                                WDK_VIEW_MSG_TOASTBOX_X,
                                WDK_VIEW_MSG_MARK_TXT_Y,
                                WDK_VIEW_MSG_TOASTBOX_W,
                                WDK_VIEW_MSG_MARK_TXT_H+20+20,
                                &pt_this->h_eq_msg);
            WDK_CHK_FAIL (i4_ret);

            /*create toast box icon*/
            i4_ret = wdk_view_create_toast_box_icon(pt_this->h_dialog_frm,&pt_this->h_icon_toast_box);
            WDK_CHK_FAIL (i4_ret);
            break;

        case WDK_WARNING_TOAST:
            /*create warningicon*/
            i4_ret = wdk_view_create_icon(pt_this->h_dialog_frm ,
                                WDK_VIEW_ICON_WARNING_X,
                                WDK_VIEW_ICON_WARNING_Y,
                                WDK_VIEW_ICON_WARNING_W,
                                WDK_VIEW_ICON_WARNING_H,
                                h_g_wdk_warning,
                                &pt_this->h_warning_icon);
            WDK_CHK_FAIL (i4_ret);

            /*create toast box icon*/
            WDK_CHK_FAIL(wdk_view_create_toast_box_icon(pt_this->h_dialog_frm,&pt_this->h_icon_toast_box));
            break;

        case WDK_SCREEN_CENTER_MSG:
        {
             WDK_CHK_FAIL(wdk_view_create_center_msg(pt_this->h_dialog_frm,&pt_this->h_txt_toast_box));
             break;
        }

        case WDK_SINGLE_SELECT_LIST:
        case WDK_INPUT_LIST:
        {
            if(toast_param->e_toast_style == WDK_INPUT_LIST)
            {
                WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );
            }

            toast_param_temp.ui4_sl_first_num = 0;
            toast_param_temp.ui4_sl_focus_num = 0;

            if (NULL_HANDLE == pt_this->h_list_txt_frm)
            {
                i4_ret = wdk_view_create_select_list_txt(pt_this->h_dialog_frm,&pt_this->h_list_txt_frm, pt_this);
                WDK_CHK_FAIL (i4_ret);
            }

            /*if this is for pic mode*/
            if (toast_param_temp.b_is_pic_mode)
            {
                pt_this->b_is_pic_mode = toast_param_temp.b_is_pic_mode;
                pt_this->ui1_pic_standard_idx = toast_param_temp.ui1_pic_standard_idx;
            }

#ifdef NEVER
            i4_ret = wdk_view_create_icon(pt_this->h_list_txt_frm,
                                WDK_VIEW_ENERGY_STAR_ICON_X,
                                WDK_VIEW_ENERGY_STAR_ICON_Y,
                                WDK_VIEW_ENERGY_STAR_ICON_W,
                                WDK_VIEW_ENERGY_STAR_ICON_H,
                                h_g_energy_star,
                                &pt_this->h_energy_star_icon);
#endif /* NEVER */

            if (NULL_HANDLE == pt_this->h_title_line)
            {
                i4_ret = wdk_view_create_title_line(pt_this->h_list_txt_frm,&pt_this->h_title_line);
                WDK_CHK_FAIL (i4_ret);
            }

            i4_ret = wdk_view_create_title_line(pt_this->h_list_txt_frm,&pt_this->h_list_txt_focus);
            WDK_CHK_FAIL (i4_ret);

            WDK_CHK_FAIL(c_timer_create(&pt_this->h_line_timer));

            if(pt_this->h_dolby_vision_icon == NULL_HANDLE)
            {
                WGL_IMG_INFO_T              t_img_info;
                i4_ret = wdk_view_create_icon(pt_this->h_dialog_frm,
                        WDK_VIEW_DOLBY_VISION_ICON_X,
                        WDK_VIEW_DOLBY_VISION_ICON_Y,
                        WDK_VIEW_DOLBY_VISION_ICON_W,
                        WDK_VIEW_DOLBY_VISION_ICON_H,
                        h_g_dolby_vision_icon,
                        &pt_this->h_dolby_vision_icon);

                c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
                {
                    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
                    t_img_info.u_img_data.t_standard.t_enable    = h_g_dolby_vision_icon;
                    t_img_info.u_img_data.t_standard.t_disable   = h_g_dolby_vision_icon;
                    t_img_info.u_img_data.t_standard.t_highlight = h_g_dolby_vision_icon;

                }
                i4_ret = c_wgl_do_cmd (pt_this->h_dolby_vision_icon,
                                        WGL_CMD_GL_SET_IMAGE,
                                        WGL_PACK(WGL_IMG_FG),
                                        WGL_PACK(&t_img_info));

                WDK_CHK_FAIL (i4_ret);
            }

            if(h_source_timer_create == FALSE)
            {
                WDK_CHK_FAIL(c_timer_create(&h_srcl_title_timer));
                h_source_timer_create = TRUE;
            }
        }
            break;

        case WDK_NO_SINGLE:
        {
            /*create dialog frame */
            if (NULL_HANDLE == pt_this->h_list_txt_frm)
            {
                GL_RECT_T                   t_rect;
                UINT32                      ui4_style=0;

                SET_RECT_BY_SIZE (&t_rect, WDK_VIEW_LIST_TXT_X, WDK_VIEW_LIST_TXT_Y, WDK_VIEW_LIST_TXT_W, WDK_VIEW_LIST_TXT_H) ;

                /*create list frm*/
                WDK_CHK_FAIL( c_wgl_create_widget (pt_this->h_dialog_frm,
                                            HT_WGL_WIDGET_FRAME,
                                            WGL_CONTENT_FRAME_DEF,
                                            WGL_BORDER_NULL,
                                            &t_rect,
                                            NULL,
                                            255,
                                            (VOID*)ui4_style,
                                            NULL,
                                            &pt_this->h_list_txt_frm));
            }
        }
            break;
        case WDK_CENTER_DIALOG:
            /*create toast content txt */
            if (NULL_HANDLE == pt_this->h_list_txt_frm)
            {
                i4_ret = wdk_view_create_msg_toastbox(pt_this->h_dialog_frm,&pt_this->h_list_txt_frm);
                WDK_CHK_FAIL (i4_ret);
            }
            break;
        case WDK_PIC_PW_POPUP:
        {
            /* alloc button space */
            WDK_PPP_BUTTON_T* pt_button = (WDK_PPP_BUTTON_T*)c_mem_alloc(sizeof(WDK_PPP_BUTTON_T));
            if (pt_button == NULL)
            {
                WDK_CHK_FAIL (-1);
            }
            c_memset(pt_button, 0, sizeof(WDK_PPP_BUTTON_T));
            toast_param->style.style_ppp.pt_wdk_ppp_button = pt_button;

            pt_this->pt_wdk_param = (WDK_TOAST_PARAM_T*)toast_param;

            pf_ppp_button_cb = toast_param->pf_cb;

            /* create picture popup button */
            i4_ret = wdk_view_create_ppp_button(pt_this->h_base_frm,
                                            WDK_VIEW_PIC_BUTTON_LEFT_X,
                                            WDK_VIEW_PIC_BUTTON_LEFT_Y,
                                            WDK_VIEW_PIC_BUTTON_LEFT_W,
                                            WDK_VIEW_PIC_BUTTON_LEFT_H,
                                            &(toast_param->style.style_ppp.pt_wdk_ppp_button->h_pic_left_button));
            WDK_CHK_FAIL (i4_ret);

            i4_ret = wdk_view_create_ppp_button(pt_this->h_base_frm,
                                            WDK_VIEW_PIC_BUTTON_LEFT_X+455,
                                            WDK_VIEW_PIC_BUTTON_LEFT_Y,
                                            WDK_VIEW_PIC_BUTTON_LEFT_W,
                                            WDK_VIEW_PIC_BUTTON_LEFT_H,
                                            &(toast_param->style.style_ppp.pt_wdk_ppp_button->h_pic_middle_button));
            WDK_CHK_FAIL (i4_ret);

            i4_ret = wdk_view_create_ppp_button(pt_this->h_base_frm,
                                            WDK_VIEW_PIC_BUTTON_LEFT_X+915,
                                            WDK_VIEW_PIC_BUTTON_LEFT_Y,
                                            WDK_VIEW_PIC_BUTTON_LEFT_W,
                                            WDK_VIEW_PIC_BUTTON_LEFT_H,
                                            &(toast_param->style.style_ppp.pt_wdk_ppp_button->h_pic_right_button));
            WDK_CHK_FAIL (i4_ret);

            /* create power popup button */
            i4_ret = wdk_view_create_ppp_button(pt_this->h_dialog_frm,
                                            WDK_VIEW_PW_BUTTON_LEFT_X,
                                            WDK_VIEW_PW_BUTTON_LEFT_Y,
                                            WDK_VIEW_PW_BUTTON_LEFT_W,
                                            WDK_VIEW_PW_BUTTON_LEFT_H,
                                            &(toast_param->style.style_ppp.pt_wdk_ppp_button->h_pw_left_button));
            WDK_CHK_FAIL (i4_ret);

            i4_ret = wdk_view_create_ppp_button(pt_this->h_dialog_frm,
                                            WDK_VIEW_PW_BUTTON_LEFT_X+545,
                                            WDK_VIEW_PW_BUTTON_LEFT_Y,
                                            WDK_VIEW_PW_BUTTON_LEFT_W,
                                            WDK_VIEW_PW_BUTTON_LEFT_H,
                                            &(toast_param->style.style_ppp.pt_wdk_ppp_button->h_pw_right_button));
            WDK_CHK_FAIL (i4_ret);
        }
            break;
        default:
            /*create toast box icon*/
            if (NULL_HANDLE == pt_this->h_icon_toast_box)
            {
                i4_ret = wdk_view_create_toast_box_icon(pt_this->h_dialog_frm,&pt_this->h_icon_toast_box);
                WDK_CHK_FAIL (i4_ret);
            }
            break;
    }

    /*create toast box txt*/
    if (NULL_HANDLE == pt_this->h_txt_toast_box)
    {
        i4_ret = wdk_view_create_msg_toastbox(pt_this->h_dialog_frm,&pt_this->h_txt_toast_box);
        WDK_CHK_FAIL (i4_ret);
    }

    /*create toast box txt*/
    if(toast_param->e_toast_style == WDK_INPUT_LIST)
    {
        WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

        if (NULL_HANDLE == pt_this->h_txt_help_toast_box)
        {
            i4_ret = wdk_view_create_help_msg_toastbox(pt_this->h_dialog_frm,&pt_this->h_txt_help_toast_box);
            WDK_CHK_FAIL (i4_ret);
        }
    }

    pt_this->b_have_init=TRUE;
    DBG_INFO(("\r\n %s,%s(),%d  %d end \r\n", __FILE__,__FUNCTION__,__LINE__,i4_ret));
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _wdk_toast_vol_control_activate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _wdk_toast_vol_control_activate(
    WDK_TOAST_PARAM_T* toast_param,
    WDK_OSD_TOAST_T*            pt_this
)
{
    GL_RECT_T                t_rect;
    INT32                    i4_x=0;
    INT32                    i4_w=0;
    FLOAT                    f_each_setp_w=0;
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

    if(toast_param->i4_vol_track_range<=0)
    {
        toast_param->i4_vol_track_range=100;
    }

    f_each_setp_w = WDK_VIEW_LINE_TITLE_W * 1.0 /(toast_param->i4_vol_track_range);
    if(f_each_setp_w<=0)
    {
        f_each_setp_w =1;
    }

    switch(toast_param->e_track_style)
    {
        case WDK_TOAST_VOL_TRACK_CENTER:
            if(toast_param->i4_vol_track_val<0)
            {
                 toast_param->i4_vol_track_val=0;
            }
            i4_w = toast_param->i4_vol_track_val*f_each_setp_w;
            i4_x = (WDK_VIEW_LINE_TITLE_W-i4_w)/2;
            break;
        case WDK_TOAST_VOL_TRACK_HALF:
            i4_w = (toast_param->i4_vol_track_val*f_each_setp_w/2);
            if(i4_w<0)
            {
                WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_track_cap_left, WGL_SW_NORMAL)) ;
                WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_track_cap_right, WGL_SW_HIDE)) ;
                i4_x = (WDK_VIEW_LINE_TITLE_W)/2+i4_w;
            }
            else
            {
                WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_track_cap_right, WGL_SW_NORMAL)) ;
                WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_track_cap_left, WGL_SW_HIDE)) ;
                i4_x = (WDK_VIEW_LINE_TITLE_W)/2;
            }
            break;
        default:
            break;
    }

    SET_RECT_BY_SIZE (&t_rect, i4_x, WDK_VIEW_LINE_TITLE_Y, i4_w>=0?i4_w:(-i4_w), WDK_VIEW_LINE_TITLE_H);
    c_wgl_move (pt_this->h_title_line, &t_rect, WGL_NO_AUTO_REPAINT);

    SET_RECT_BY_SIZE (&t_rect, (i4_x+(i4_w>=0?i4_w:(-i4_w))), WDK_VIEW_LINE_TITLE_Y, 2, 4);
    c_wgl_move (pt_this->h_track_cap_right, &t_rect, WGL_NO_AUTO_REPAINT);

    SET_RECT_BY_SIZE (&t_rect, (i4_x-2), WDK_VIEW_LINE_TITLE_Y, 2, 4);
    c_wgl_move (pt_this->h_track_cap_left, &t_rect, WGL_NO_AUTO_REPAINT);

    if(i4_w==0)
    {
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_title_line, WGL_SW_HIDE)) ;
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_track_cap_right, WGL_SW_HIDE)) ;
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_track_cap_left, WGL_SW_HIDE)) ;
    }
    else
    {
        if(toast_param->e_track_style == WDK_TOAST_VOL_TRACK_CENTER)
        {
            WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_track_cap_right, WGL_SW_NORMAL)) ;
            WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_track_cap_left, WGL_SW_NORMAL)) ;
        }
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_title_line, WGL_SW_NORMAL)) ;
    }


    if(toast_param->e_track_style == WDK_TOAST_VOL_TRACK_HALF)
    {
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_eq_hash_mark, WGL_SW_NORMAL)) ;
    }
    else
    {
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_eq_hash_mark, WGL_SW_HIDE)) ;
    }

    CHAR                        s_buf[32];
    UTF16_T                     w2s_tmp_str[128];
    c_sprintf(s_buf, "%d",  toast_param->i4_vol_track_val);
    c_uc_ps_to_w2s(s_buf, w2s_tmp_str, 9);
    wdk_view_set_text(pt_this->h_txt_toast_box,w2s_tmp_str);

    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_dialog_frm, NULL, FALSE));
    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_base_frm, NULL, FALSE));
    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wdk_widget_select_list_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wdk_widget_select_list_proc_fct(HANDLE_T    h_widget,
                                     UINT32      ui4_msg,
                                     VOID*       param1,
                                     VOID*       param2)
{
    GL_RECT_T                t_rect;
    UINT32                   ui4_width;
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch(ui4_keycode)
            {
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                {
                    INT32 i4_ret;
                    WDK_OSD_TOAST_T* pt_this;
                    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_this),
                          NULL);
                    WDK_CHK_FAIL(i4_ret);

                    c_wgl_set_visibility (pt_this->h_title_line, WGL_SW_HIDE);

                    if (ui4_keycode == BTN_CURSOR_LEFT)
                    {
                        if (i4_seq > 0)
                        {
                            i4_seq--;
                        }
                        else
                        {
                            i4_seq = toast_param_temp.w2s_msg_t.i4_str_num - 1;
                        }
                    }
                    else
                    {
                        i4_seq = (i4_seq+1)%toast_param_temp.w2s_msg_t.i4_str_num;
                    }

                    _wdk_toast_list_adjust(pt_this);

                    if(WDK_INPUT_LIST == toast_param_temp.e_toast_style)
                    {
                        WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

                        ui4_width = _wdk_get_string_size(pt_this->h_list_txt[toast_param_temp.ui4_sl_focus_num]);

                        SET_RECT_BY_SIZE (&t_rect,WDK_VIEW_LINE_X+(toast_param_temp.ui4_sl_focus_num+toast_param_temp.w2s_msg_t.i4_str_num-i4_seq)%(toast_param_temp.w2s_msg_t.i4_str_num) * WDK_VIEW_LIST_TXT_W_EX,(WDK_VIEW_LIST_TXT_ITEM_Y+38+8),WDK_VIEW_LINE_W*ui4_width,WDK_VIEW_LINE_H);
                        c_wgl_move (pt_this->h_list_txt_focus, &t_rect, WGL_NO_AUTO_REPAINT);
                        WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_list_txt_frm, NULL, TRUE));


                        /* Create timer. */
                        ui1_sum=-100;
                        WDK_CHK_FAIL(c_timer_start (pt_this->h_line_timer,
                                                50,
                                                X_TIMER_FLAG_REPEAT,
                                                _line_step_nfy_fct,
                                                pt_this));
                        DBG_INFO(("\r\n %s,%s(),%d end \r\n", __FILE__,__FUNCTION__,__LINE__));
                    }
                    else
                    {
                        toast_param_temp.ui4_sl_focus_num = toast_param_temp.ui4_sl_first_num;
                        c_wgl_set_focus(pt_this->h_list_txt[toast_param_temp.ui4_sl_focus_num], FALSE);
                        c_wgl_repaint(pt_this->h_list_txt_frm, NULL, TRUE);
                        if(NULL_HANDLE != toast_param_temp.pf_send_msg_cb)
                        {
                            WDK_WIDGET_SEND_MSG_T t_g_send_msg;
                            t_g_send_msg.ui4_keycode = ui4_keycode;
                            t_g_send_msg.ui4_selected_num = toast_param_temp.ui4_sl_focus_num;
                            toast_param_temp.pf_send_msg_cb(NULL_HANDLE,0,(VOID*)&t_g_send_msg,NULL);
                        }
                    }
                }
                return WDKR_OK;
            }
        }
        break;
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget,
                                      ui4_msg,
                                      param1,
                                      param2);

}

/*----------------------------------------------------------------------------
 * Name: _wdk_settings_slider_activate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _wdk_settings_slider_activate(
    BOOL                        b_repaint,
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            pt_this
)
{
    WDK_TOAST_PARAM_T* toast_param = (WDK_TOAST_PARAM_T*)pv_data;
    CHAR                        s_buf[32];
    UTF16_T                     w2s_tmp_str[128];
    c_sprintf(s_buf, "%d",  toast_param->i4_vol_track_val);
    c_uc_ps_to_w2s(s_buf, w2s_tmp_str, 9);

    wdk_view_set_text(pt_this->h_txt_toast_box,w2s_tmp_str);
    wdk_view_set_font(pt_this->h_txt_toast_box, WDK_VIEW_HEADLINE_1_FONT_SIZE, TRUE);
    wdk_view_set_text(pt_this->h_eq_msg,toast_param->w2s_str);
    wdk_view_set_font(pt_this->h_eq_msg, WDK_VIEW_CAPTION_2_FONT_SIZE, TRUE);

    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_icon_toast_box, WGL_SW_NORMAL)) ;
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_txt_toast_box, WGL_SW_NORMAL)) ;
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_eq_msg, WGL_SW_NORMAL)) ;
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_dialog_frm, WGL_SW_NORMAL));


    _wdk_toast_vol_control_activate(toast_param, pt_this);
    return WDKR_OK;
}

static WGL_HIMG_TPL_T _wdk_ppp_calc_img(UINT8 ui1_crnt_page, UINT8 ui1_lang_idx)
{
    WGL_HIMG_TPL_T t_img = {0};

    if (ui1_crnt_page == 0)                  // in picture mode selection
    {
        switch (ui1_lang_idx)
        {
            case MLM_NAV_LANG_ENG:
                t_img = arr_img_ppp[ENG_PIC_POPUP_BACKGROUND];
                break;
            case MLM_NAV_LANG_SPA:
                t_img = arr_img_ppp[ESP_PIC_POPUP_BACKGROUND];
                break;
            case MLM_NAV_LANG_FRE:
                t_img = arr_img_ppp[FRE_PIC_POPUP_BACKGROUND];
                break;
            default:
                t_img = arr_img_ppp[ENG_PIC_POPUP_BACKGROUND];
                break;
        }
    }
    else                                    // in power mode selection
    {
        switch (ui1_lang_idx)
        {
            case MLM_NAV_LANG_ENG:
                t_img = arr_img_ppp[ENG_PW_POPUP_BACKGROUND];
                break;
            case MLM_NAV_LANG_SPA:
                t_img = arr_img_ppp[ESP_PW_POPUP_BACKGROUND];
                break;
            case MLM_NAV_LANG_FRE:
                t_img = arr_img_ppp[FRE_PW_POPUP_BACKGROUND];
                break;
            default:
                t_img = arr_img_ppp[ENG_PW_POPUP_BACKGROUND];
                break;
        }
    }

    return t_img;
}


INT32 _wdk_ppp_active(
    BOOL                        b_repaint,
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            pt_this
    )
{
    INT32  i4_idx = 0;
    UINT8  ui1_crnt_page;
    UINT8  ui1_lang_idx;
    WDK_TOAST_PARAM_T*  toast_param = (WDK_TOAST_PARAM_T*)pv_data;
    HANDLE_T  h_set_frm, h_unset_frm;
    HANDLE_T  h_button;

    ui1_crnt_page = toast_param->style.style_ppp.ui1_crnt_page;
    ui1_lang_idx  = toast_param->style.style_ppp.ui1_lang_idx;
    h_set_frm = (ui1_crnt_page == 0) ? pt_this->h_base_frm : pt_this->h_dialog_frm;
    h_unset_frm = (ui1_crnt_page == 0) ? pt_this->h_dialog_frm : pt_this->h_base_frm;

    wdk_view_set_bk_img(h_set_frm, _wdk_ppp_calc_img(ui1_crnt_page, ui1_lang_idx));
    WDK_CHK_FAIL(c_wgl_set_visibility(h_set_frm, WGL_SW_RECURSIVE));
    WDK_CHK_FAIL(c_wgl_set_visibility(h_unset_frm, WGL_SW_HIDE_RECURSIVE));

    h_button = toast_param->style.style_ppp.pt_wdk_ppp_button->h_pic_left_button;
    wdk_view_set_button_text(h_button, toast_param->w2s_msg_t.w2s_str[i4_idx++]);

    h_button = toast_param->style.style_ppp.pt_wdk_ppp_button->h_pic_middle_button;
    wdk_view_set_button_text(h_button, toast_param->w2s_msg_t.w2s_str[i4_idx++]);

    h_button = toast_param->style.style_ppp.pt_wdk_ppp_button->h_pic_right_button;
    wdk_view_set_button_text(h_button, toast_param->w2s_msg_t.w2s_str[i4_idx++]);

    h_button = toast_param->style.style_ppp.pt_wdk_ppp_button->h_pw_left_button;
    wdk_view_set_button_text(h_button, toast_param->w2s_msg_t.w2s_str[i4_idx++]);

    h_button = toast_param->style.style_ppp.pt_wdk_ppp_button->h_pw_right_button;
    wdk_view_set_button_text(h_button, toast_param->w2s_msg_t.w2s_str[i4_idx++]);

    if (b_repaint)
    {
        c_wgl_repaint(h_unset_frm, NULL, WGL_NO_AUTO_REPAINT);
        c_wgl_repaint(h_set_frm, NULL, WGL_SYNC_AUTO_REPAINT);
    }

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wdk_string_toast
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _wdk_string_toast(
    BOOL                        b_repaint,
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            pt_this
)
{
    GL_RECT_T                t_rect;
    WDK_TOAST_PARAM_T*       toast_param = (WDK_TOAST_PARAM_T*)pv_data;


    wdk_view_set_bk_img(pt_this->h_icon_toast_box,h_g_wdk_toast_box_settings);

   WDK_CHK_FAIL( c_wgl_do_cmd(pt_this->h_txt_toast_box,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(WGL_AS_CENTER_CENTER),
                                NULL));

    SET_RECT_BY_SIZE (&t_rect, WDK_VIEW_STRING_TOAST_MSG_X, 0, WDK_VIEW_STRING_TOAST_MSG_W, WDK_VIEW_STRING_TOAST_MSG_H*2);
    c_wgl_move (pt_this->h_txt_toast_box, &t_rect, WGL_NO_AUTO_REPAINT);


    WDK_CHK_FAIL(wdk_view_set_font(pt_this->h_txt_toast_box, WDK_VIEW_HEADLINE_2_FONT_SIZE, TRUE));

    wdk_view_set_text(pt_this->h_txt_toast_box,toast_param->w2s_str);

    WDK_CHK_FAIL(c_wgl_do_cmd(pt_this->h_txt_toast_box,
                            WGL_CMD_TEXT_SET_LINE_GAP,
                            WGL_PACK((INT32)7),
                            NULL));

    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_icon_toast_box, WGL_SW_NORMAL)) ;
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_txt_toast_box, WGL_SW_NORMAL)) ;
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_dialog_frm, WGL_SW_NORMAL));

    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_dialog_frm, NULL, TRUE));
    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_base_frm, NULL, TRUE));
#if 0
#ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_REVOLT_INFO));
#endif
#endif
    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wdk_warning_toast
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _wdk_warning_toast(
    BOOL                        b_repaint,
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            pt_this
)
{
    GL_RECT_T                t_rect;
    WDK_TOAST_PARAM_T*       toast_param = (WDK_TOAST_PARAM_T*)pv_data;


    wdk_view_set_bk_img(pt_this->h_icon_toast_box,h_g_wdk_toast_box_settings);

    WDK_CHK_FAIL( c_wgl_do_cmd(pt_this->h_txt_toast_box,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(WGL_AS_CENTER_CENTER),
                                NULL));

    SET_RECT_BY_SIZE (&t_rect, WDK_VIEW_STRING_TOAST_MSG_X, 0, WDK_VIEW_STRING_TOAST_MSG_W, WDK_VIEW_STRING_TOAST_MSG_H*2);

    c_wgl_move (pt_this->h_txt_toast_box, &t_rect, WGL_NO_AUTO_REPAINT);

    WDK_CHK_FAIL(wdk_view_set_font(pt_this->h_txt_toast_box, WDK_VIEW_HEADLINE_2_FONT_SIZE, TRUE));

    wdk_view_set_text(pt_this->h_txt_toast_box,toast_param->w2s_str);

    WDK_CHK_FAIL(c_wgl_do_cmd(pt_this->h_txt_toast_box,
                            WGL_CMD_TEXT_SET_LINE_GAP,
                            WGL_PACK((INT32)7),
                            NULL));

    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_icon_toast_box, WGL_SW_NORMAL)) ;
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_txt_toast_box, WGL_SW_NORMAL)) ;
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_warning_icon, WGL_SW_NORMAL)) ;
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_dialog_frm, WGL_SW_NORMAL));

    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_dialog_frm, NULL, TRUE));
    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_base_frm, NULL, TRUE));
#if 0
#ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_REVOLT_INFO));
#endif
#endif
    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wdk_center_dialog
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _wdk_center_dialog(
    BOOL                        b_repaint,
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            pt_this
)
{
    GL_RECT_T                t_rect;
    WDK_TOAST_PARAM_T*       toast_param = (WDK_TOAST_PARAM_T*)pv_data;

    SET_RECT_BY_SIZE (&t_rect, (600), (400), (613), (234));
    c_wgl_move (pt_this->h_base_frm, &t_rect, WGL_NO_AUTO_REPAINT);

    SET_RECT_BY_SIZE (&t_rect, 200, 30, 200, 16) ;
    c_wgl_move (pt_this->h_txt_toast_box, &t_rect, WGL_NO_AUTO_REPAINT);

    SET_RECT_BY_SIZE (&t_rect, 60, 56, 613-120, (234-86)) ;
    c_wgl_move (pt_this->h_list_txt_frm, &t_rect, WGL_NO_AUTO_REPAINT);

    /* Set Alignment */
    WDK_CHK_FAIL( c_wgl_do_cmd(pt_this->h_txt_toast_box,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(WGL_AS_CENTER_CENTER),
                                NULL));
    wdk_view_set_text(pt_this->h_txt_toast_box,MENU_TEXT(MLM_MENU_KEY_NET_CFG_CONN_TEST));
    wdk_view_set_font(pt_this->h_txt_toast_box, WDK_VIEW_CAPTION_2_FONT_SIZE, TRUE);

    /* Set Alignment */
    WDK_CHK_FAIL( c_wgl_do_cmd(pt_this->h_list_txt_frm,
                                WGL_CMD_TEXT_SET_CUSTOM_ALIGN,
                                (VOID*)WGL_TEXT_H_ALIGN_CUSTOM,
                                NULL));

     c_wgl_do_cmd(pt_this->h_list_txt_frm,
                      WGL_CMD_TEXT_SET_LINE_GAP,
                      WGL_PACK((INT32)5),
                      NULL);

    wdk_view_set_text(pt_this->h_list_txt_frm,toast_param->w2s_str);
    wdk_view_set_font(pt_this->h_list_txt_frm, WDK_VIEW_HEADLINE_2_FONT_SIZE, TRUE);

    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_txt_toast_box, WGL_SW_NORMAL)) ;
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_list_txt_frm, WGL_SW_NORMAL)) ;

    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_dialog_frm, WGL_SW_NORMAL));
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_base_frm, WGL_SW_NORMAL));
    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_base_frm, NULL, TRUE));
#if 0
#ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_DIALOG));
#endif
#endif
    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wdk_no_single
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _wdk_no_single(
    BOOL                        b_repaint,
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            pt_this
)
{
    GL_RECT_T                t_rect;
    WDK_TOAST_PARAM_T*       toast_param = (WDK_TOAST_PARAM_T*)pv_data;

    SET_RECT_BY_SIZE (&t_rect, WDK_VIEW_NO_SIGNAL_TXT_X, WDK_VIEW_NO_SIGNAL_TXT_Y, WDK_VIEW_NO_SIGNAL_TXT_W, WDK_VIEW_NO_SIGNAL_TXT_H) ;

    c_wgl_move (pt_this->h_txt_toast_box, &t_rect, WGL_NO_AUTO_REPAINT);

    /* Set Alignment */
    WDK_CHK_FAIL( c_wgl_do_cmd(pt_this->h_txt_toast_box,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(WGL_AS_CENTER_CENTER),
                                NULL));
    wdk_view_set_font(pt_this->h_txt_toast_box, WDK_VIEW_HEADLINE_2_FONT_SIZE, TRUE);
    wdk_view_set_text(pt_this->h_txt_toast_box,toast_param->w2s_str);

    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_txt_toast_box, WGL_SW_NORMAL)) ;
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_list_txt_frm, WGL_SW_NORMAL)) ;

    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_dialog_frm, WGL_SW_NORMAL));
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_base_frm, WGL_SW_NORMAL));
    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_base_frm, NULL, TRUE));

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wdk_set_help_toast
 *
 * Description:set text for help toast box
 *
 * Inputs: handler
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _wdk_set_help_toast(
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            pt_this
)
{
    GL_RECT_T                t_rect;
    INT32                    i4_ret = WDKR_OK;
    WDK_TOAST_PARAM_T*       sel_list_param = (WDK_TOAST_PARAM_T*)pv_data;


    if( sel_list_param->e_toast_style == WDK_INPUT_LIST )
    {
        WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );
    }

    /* Set Alignment */
    WDK_CHK_FAIL( c_wgl_do_cmd(pt_this->h_txt_help_toast_box,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(WGL_AS_LEFT_CENTER),
                                NULL));

    SET_RECT_BY_SIZE (&t_rect, WDK_VIEW_LINE_X, 353, 1400, TXT_GRID_H);
    c_wgl_move (pt_this->h_txt_help_toast_box, &t_rect, WGL_NO_AUTO_REPAINT);


    wdk_view_set_text(pt_this->h_txt_help_toast_box, sel_list_param->w2s_help_str);

    i4_ret = wdk_view_set_font(pt_this->h_txt_help_toast_box, WDK_VIEW_CAPTION_2_FONT_SIZE, FALSE);
    WDK_CHK_FAIL (i4_ret);

    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wdk_set_help_toast
 *
 * Description:set help toast box visible or not
 *
 * Inputs: handler
 *
 * Outputs:
 *
 * Returns: NA
 *
 ----------------------------------------------------------------------------*/

void wdk_set_help_toast_visible(
    BOOL                        b_enalbe,
    WDK_OSD_TOAST_T*            pt_this)
{
    if(b_enalbe)
    {
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_txt_help_toast_box, WGL_SW_NORMAL)) ;
    }
    else
    {
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_txt_help_toast_box, WGL_SW_HIDE_RECURSIVE)) ;
    }

    WDK_CHK_FAIL(c_wgl_repaint(pt_this->h_base_frm, NULL, TRUE));
}

/*----------------------------------------------------------------------------
 * Name: _wdk_settings_slider_activate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _wdk_single_select_list(
    BOOL                        b_repaint,
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            pt_this
)
{
    GL_RECT_T                t_rect;
    UINT8                    ui1_idx=0;

    INT32                    i4_ret = WDKR_OK;
    BOOL                     b_is_chg = 0;

    WDK_TOAST_PARAM_T*       sel_list_param = (WDK_TOAST_PARAM_T*)pv_data;
    UINT8                   ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;


    WDK_TOAST_STYLE_T  e_TOAST_style = pt_this->e_style;

    //if( e_TOAST_style == WDK_INPUT_LIST )
    {
        WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} e_TOAST_style:%d, .w2s_msg_t.i4_str_num:%d\n",
            __FUNCTION__, __LINE__, e_TOAST_style, (sel_list_param->w2s_msg_t).i4_str_num )); );
    }

    DBG_INFO(("\r\n %s,%s(),%d  %d begin \r\n", __FILE__,__FUNCTION__,__LINE__,toast_param_temp.ui4_sl_focus_num));


    for(ui1_idx=0;ui1_idx < (sel_list_param->w2s_msg_t).i4_str_num;ui1_idx++)
    {
        if( e_TOAST_style == WDK_INPUT_LIST )
        {
            WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} ui1_idx:%d, call wdk_view_set_text(%s) \n",
                __FUNCTION__, __LINE__, ui1_idx, menu_custom_get_char_string((sel_list_param->w2s_msg_t).w2s_str[ui1_idx]) )); );
        }

        i4_ret = wdk_view_set_text(pt_this->h_list_txt[ui1_idx], (sel_list_param->w2s_msg_t).w2s_str[ui1_idx] );
        WDK_CHK_FAIL(i4_ret);

        if(NULL_HANDLE != toast_param_temp.pf_cb)
        {
            c_wgl_set_widget_proc(pt_this->h_list_txt[ui1_idx], toast_param_temp.pf_cb);
        }

        i4_ret = wdk_view_set_font(pt_this->h_list_txt[ui1_idx], WDK_VIEW_HEADLINE_2_FONT_SIZE, FALSE);
        WDK_CHK_FAIL (i4_ret);
    }


    UINT32 ui4_width;
    UINT32 ui4_width_tmp = _wdk_get_string_size(pt_this->h_list_txt[toast_param_temp.ui4_sl_focus_num]);
    ui4_width = ui4_width_tmp > WDK_VIEW_LIST_TXT_ITEM_W ? WDK_VIEW_LIST_TXT_ITEM_W : ui4_width_tmp;

    // Move h_title_line
    SET_RECT_BY_SIZE (&t_rect,WDK_VIEW_LINE_X,(WDK_VIEW_LIST_TXT_ITEM_Y+38),WDK_VIEW_LINE_W,WDK_VIEW_LINE_H);
    if( e_TOAST_style == WDK_INPUT_LIST )
    {
        WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} h_title_line(0x%X) move (%d %d %d %d) \n",
            __FUNCTION__, __LINE__, (UINT32)pt_this->h_title_line,
            t_rect.i4_left, t_rect.i4_top, t_rect.i4_right, t_rect.i4_bottom)); );
    }
    c_wgl_move (pt_this->h_title_line, &t_rect, WGL_NO_AUTO_REPAINT);

    // Move h_list_txt_focus
    if (ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON)
    {
        SET_RECT_BY_SIZE (&t_rect,WDK_VIEW_LINE_X,(WDK_VIEW_LIST_TXT_ITEM_Y+38+8),WDK_VIEW_LINE_W*ui4_width,WDK_VIEW_LINE_H);
    }
    else
    {
        SET_RECT_BY_SIZE (&t_rect,WDK_VIEW_LINE_X,(WDK_VIEW_LIST_TXT_ITEM_Y+38),WDK_VIEW_LINE_W*ui4_width,WDK_VIEW_LINE_H);
    }
    if( e_TOAST_style == WDK_INPUT_LIST )
    {
        WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} h_list_txt_focus(0x%X) move (%d %d %d %d) \n",
            __FUNCTION__, __LINE__, (UINT32)pt_this->h_list_txt_focus,
            t_rect.i4_left, t_rect.i4_top, t_rect.i4_right, t_rect.i4_bottom)); );
    }
    c_wgl_move (pt_this->h_list_txt_focus, &t_rect, WGL_NO_AUTO_REPAINT);


    // Move h_dialog_frm
  #if(NAV_INPUT_SRC_UI_VERTICAL)
    if( e_TOAST_style == WDK_INPUT_LIST )
    {
        SET_RECT_BY_SIZE (&t_rect, WDK_INPUT_LIST_DIALOG_FRAME_X, WDK_INPUT_LIST_DIALOG_FRAME_Y,
            WDK_INPUT_LIST_DIALOG_FRAME_W, WDK_INPUT_LIST_DIALOG_FRAME_H);

      #if 0
       //if( e_TOAST_style == WDK_INPUT_LIST )
       {
           WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} h_dialog_frm(0x%X) move (%d %d %d %d) \n",
               __FUNCTION__, __LINE__, (UINT32)pt_this->h_dialog_frm,
               t_rect.i4_left, t_rect.i4_top, t_rect.i4_right, t_rect.i4_bottom)); );
       }
       c_wgl_move (pt_this->h_dialog_frm, &t_rect, WGL_NO_AUTO_REPAINT);
      #endif
    }
    else
  #endif
    {
        SET_RECT_BY_SIZE (&t_rect, 0, WDK_VIEW_SELECT_FRAME_Y, WDK_VIEW_BASE_FRAME_W, WDK_VIEW_SELECT_FRAME_H);
        c_wgl_move (pt_this->h_dialog_frm, &t_rect, WGL_NO_AUTO_REPAINT);
    }


    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_list_txt_frm, WGL_SW_RECURSIVE)) ;

    i4_seq = toast_param_temp.ui4_sl_focus_num;


    _wdk_toast_list_adjust(pt_this);


    /* Set Alignment */
    WDK_CHK_FAIL( c_wgl_do_cmd(pt_this->h_txt_toast_box,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(WGL_AS_LEFT_CENTER),
                                NULL));

    if (ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON)
    {
        SET_RECT_BY_SIZE (&t_rect, WDK_VIEW_LINE_X, 83-TXT_GRID_H, 400*2, TXT_GRID_H*2);
    }
    else
    {
        SET_RECT_BY_SIZE (&t_rect, WDK_VIEW_LINE_X, 83, 400, TXT_GRID_H);
    }
    c_wgl_move (pt_this->h_txt_toast_box, &t_rect, WGL_NO_AUTO_REPAINT);

    wdk_view_set_text(pt_this->h_txt_toast_box,sel_list_param->w2s_str);
    i4_ret = wdk_view_set_font(pt_this->h_txt_toast_box, WDK_VIEW_CAPTION_2_FONT_SIZE, FALSE);
    WDK_CHK_FAIL (i4_ret);
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_txt_toast_box, WGL_SW_NORMAL)) ;

    if(WDK_SINGLE_SELECT_LIST == toast_param_temp.e_toast_style)
    {
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_list_txt_focus, WGL_SW_HIDE)) ;

        if (pt_this->b_is_pic_mode)
        {
            DBG_INFO(("\n[WDK_TOAST_TEST] _wdk_single_select_list XXX b_is_pic_mode[YES]\n"));
#ifdef NEVER
            a_cfg_get_preset_pic_mode_chg_status(0,&b_is_chg); // Need check standard picture mode is modify or not
            if(!b_is_chg)
            {
                WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_energy_star_icon, WGL_SW_NORMAL)) ;
            }
            else
            {
                WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_energy_star_icon, WGL_SW_HIDE)) ;
            }
#endif /* NEVER */

            if(a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI)
            {
                WGL_IMG_INFO_T              t_img_info;
                c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
                {
                    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
                    t_img_info.u_img_data.t_standard.t_enable    = h_g_dolby_vision_icon;
                    t_img_info.u_img_data.t_standard.t_disable   = h_g_dolby_vision_icon;
                    t_img_info.u_img_data.t_standard.t_highlight = h_g_dolby_vision_icon;

                }
                i4_ret = c_wgl_do_cmd (pt_this->h_dolby_vision_icon,
                                        WGL_CMD_GL_SET_IMAGE,
                                        WGL_PACK(WGL_IMG_FG),
                                        WGL_PACK(&t_img_info));

                WDK_CHK_FAIL (i4_ret);
                i4_ret = c_wgl_insert(pt_this->h_dolby_vision_icon,
                                      NULL_HANDLE,
                                      WGL_INSERT_TOPMOST,
                                      WGL_NO_AUTO_REPAINT);
                WDK_CHK_FAIL (i4_ret);
                WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_dolby_vision_icon, WGL_SW_NORMAL)) ;
            }
            else
            {
                 WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_dolby_vision_icon, WGL_SW_HIDE)) ;
            }

            DBG_INFO(("\n[WDK_TOAST_TEST] _wdk_single_select_list b_is_pic_mode[YES]\n"));
        }
        else
        {
            DBG_INFO(("\n[WDK_TOAST_TEST] _wdk_single_select_list XXX b_is_pic_mode[NO]\n"));
#ifdef NEVER
            WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_energy_star_icon, WGL_SW_HIDE)) ;
#endif /* NEVER */
            WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_dolby_vision_icon, WGL_SW_HIDE)) ;

            DBG_INFO(("\n[WDK_TOAST_TEST] _wdk_single_select_list XXX b_is_pic_mode[NO]\n"));
        }
    }
    else
    {
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_list_txt_focus, WGL_SW_NORMAL)) ;
#ifdef NEVER
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_energy_star_icon, WGL_SW_HIDE)) ;
#endif /* NEVER */
        WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_dolby_vision_icon, WGL_SW_HIDE)) ;
    }

    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_title_line, WGL_SW_HIDE)) ;

    WDK_CHK_FAIL(c_wgl_repaint(pt_this->h_base_frm, NULL, TRUE));

    DBG_INFO(("\r\n %s,%s(),%d end \r\n", __FILE__,__FUNCTION__,__LINE__));

    if(h_source_timer_create)
    {
        UTF16_T w2s_text[192];
        c_wgl_do_cmd (pt_this->h_list_txt[0],
                          WGL_CMD_TEXT_GET_TEXT,
                          WGL_PACK (w2s_text),
                          WGL_PACK (192));

        h_txt_title = pt_this->h_list_txt[0];

        source_scrl_title_reset(w2s_text);
    }

    return WDKR_OK;
}

INT32 _wdk_screen_center_msg(BOOL                        b_repaint,
                                    VOID*                       pv_data,
                                    WDK_OSD_TOAST_T*            pt_this)
{
    GL_RECT_T                t_rect;
    WDK_TOAST_PARAM_T*       toast_param = (WDK_TOAST_PARAM_T*)pv_data;

    SET_RECT_BY_SIZE (&t_rect, (WDK_VIEW_CENTER_BASE_FRAME_X), (WDK_VIEW_CENTER_BASE_FRAME_Y), (WDK_VIEW_CENTER_BASE_FRAME_W), (WDK_VIEW_CENTER_BASE_FRAME_H));
    c_wgl_move (pt_this->h_base_frm, &t_rect, WGL_NO_AUTO_REPAINT);

    SET_RECT_BY_SIZE (&t_rect, (WDK_VIEW_CENTER_BASE_FRAME_X), (WDK_VIEW_CENTER_BASE_FRAME_Y), (WDK_VIEW_CENTER_BASE_FRAME_W), (WDK_VIEW_CENTER_BASE_FRAME_H));
    c_wgl_move (pt_this->h_base_frm, &t_rect, WGL_NO_AUTO_REPAINT);

    WDK_CHK_FAIL( c_wgl_do_cmd(pt_this->h_txt_toast_box,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(WGL_AS_CENTER_CENTER),
                                NULL));

    WDK_CHK_FAIL(wdk_view_set_font(pt_this->h_txt_toast_box, WDK_VIEW_HEADLINE_2_FONT_SIZE, TRUE));

    WDK_CHK_FAIL(wdk_view_set_text(pt_this->h_txt_toast_box,toast_param->w2s_str));

    WDK_CHK_FAIL(c_wgl_do_cmd(pt_this->h_txt_toast_box,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK((INT32)7),
                              NULL));
    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_base_frm, WGL_SW_RECURSIVE));
    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_base_frm, NULL, TRUE));
    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_dialog_frm, NULL, TRUE));
    DBG_INFO(("\r\n %s,%s(),%d end \r\n", __FILE__,__FUNCTION__,__LINE__));
    return WDKR_OK;
}

/*----------------------------------------------------------------------------
 * Name: do_timer_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID do_timer_nfy(VOID* pv_data,
                         SIZE_T  z_data_size)
{
    GL_RECT_T   t_rect={0};
    //DBG_INFO(("\r\n %s,%s(),%d ui1_sum=[%d] ui4_sl_first_num=[%d]\r\n",
        //__FILE__,__FUNCTION__,__LINE__,ui1_sum,toast_param_temp.ui4_sl_first_num));
    WDK_OSD_TOAST_T*   pt_this = (WDK_OSD_TOAST_T*)pv_data;;

    ui1_sum++ ;
    UINT32 ui4_width = _wdk_get_string_size(pt_this->h_list_txt[toast_param_temp.ui4_sl_first_num]);

    if(ui1_sum == 0)
    {
        DBG_INFO(("\r\n %s,%s(),%d ui4_width=[%d]\r\n", __FILE__,__FUNCTION__,__LINE__,ui4_width));

        toast_param_temp.ui4_sl_focus_num = toast_param_temp.ui4_sl_first_num;
        c_wgl_set_focus(pt_this->h_list_txt[toast_param_temp.ui4_sl_focus_num], FALSE);

        SET_RECT_BY_SIZE (&t_rect,WDK_VIEW_LINE_X,(WDK_VIEW_LIST_TXT_ITEM_Y+38),WDK_VIEW_LINE_W*ui4_width,WDK_VIEW_LINE_H);
        c_wgl_move (pt_this->h_list_txt_focus, &t_rect, WGL_NO_AUTO_REPAINT);

        SET_RECT_BY_SIZE (&t_rect,WDK_VIEW_LINE_X,(WDK_VIEW_LIST_TXT_ITEM_Y+38),WDK_VIEW_LINE_W,WDK_VIEW_LINE_H);
        c_wgl_move (pt_this->h_title_line, &t_rect, WGL_NO_AUTO_REPAINT);

        c_wgl_set_visibility (pt_this->h_list_txt_focus, WGL_SW_HIDE);
        c_wgl_set_visibility (pt_this->h_title_line, WGL_SW_HIDE);
        c_wgl_repaint(pt_this->h_list_txt_frm, NULL, TRUE);
    }
    else if(ui1_sum>0)
    {
        if(ui1_sum >(ui4_width/10))
        {
            c_timer_stop(pt_this->h_line_timer);

            c_wgl_set_visibility (pt_this->h_list_txt_focus, WGL_SW_NORMAL);
            c_wgl_set_visibility (pt_this->h_title_line, WGL_SW_HIDE);
            c_wgl_repaint(pt_this->h_list_txt_frm, NULL, TRUE);


            if(NULL_HANDLE != toast_param_temp.pf_send_msg_cb)
            {
                WDK_WIDGET_SEND_MSG_T t_g_send_msg;
                t_g_send_msg.ui4_keycode = BTN_CURSOR_LEFT;
                t_g_send_msg.ui4_selected_num = toast_param_temp.ui4_sl_focus_num;
                toast_param_temp.pf_send_msg_cb(NULL_HANDLE,0,(VOID*)&t_g_send_msg,NULL);
            }
        }
        else
        {
            if((ui4_width/10)*ui1_sum>ui4_width)
            {
                SET_RECT_BY_SIZE (&t_rect,
                          WDK_VIEW_LINE_X,
                          (WDK_VIEW_LIST_TXT_ITEM_Y+38),
                          ui4_width,
                          WDK_VIEW_LINE_H);
            }
            else
            {
                SET_RECT_BY_SIZE (&t_rect,
                          WDK_VIEW_LINE_X,
                          (WDK_VIEW_LIST_TXT_ITEM_Y+38),
                          (ui4_width/10)*ui1_sum,
                          WDK_VIEW_LINE_H);
            }

            c_wgl_move (pt_this->h_title_line, &t_rect, WGL_NO_AUTO_REPAINT);
            c_wgl_set_visibility (pt_this->h_title_line, WGL_SW_NORMAL);
            c_wgl_repaint(pt_this->h_title_line, NULL, TRUE);
        }
    }
    else{}

    return ;
}


/*----------------------------------------------------------------------------
 * Name: _line_step_nfy_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _line_step_nfy_fct(
    HANDLE_T  h_timer,
    VOID*     pv_tag)
{
    menu_async_invoke(do_timer_nfy, pv_tag, sizeof(WDK_OSD_TOAST_T), FALSE) ;
}

/*----------------------------------------------------------------------------
 * Name: _revolt_info_tts
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
 #ifdef APP_TTS_SUPPORT
static VOID _revolt_info_tts(const WDK_TOAST_PARAM_T* pt_content)
{
    CHAR ps_number_buffer[TTS_ARGUMENT_NUMBER_BUFF_LEN] = {0};
    UTF16_T  tw2s_number_buffer[TTS_ARGUMENT_NUMBER_BUFF_LEN] = {0};
    UTF16_T* pw2s_buffer = NULL;

    if(pt_content == NULL)
    {
        DBG_INFO(("\r\n %s,%s(),%d Error. \r\n", __FILE__,__FUNCTION__,__LINE__));
        return;
    }

    switch(pt_content->e_toast_style)
    {
        case WDK_TOAST_SETTINGS_SLIDER:
        {
            c_sprintf(ps_number_buffer, "%d", pt_content->i4_vol_track_val);
            c_uc_ps_to_w2s(ps_number_buffer, tw2s_number_buffer, TTS_ARGUMENT_NUMBER_BUFF_LEN);

            if(pw2s_buffer == NULL)
            {
                pw2s_buffer = (UTF16_T*)c_mem_alloc(c_uc_w2s_strlen(pt_content->w2s_str) + TTS_ARGUMENT_NUMBER_BUFF_LEN);
                if(pw2s_buffer == NULL)
                {
                    DBG_INFO(("\r\n %s,%s(),%d malloc memory error! \r\n", __FILE__,__FUNCTION__,__LINE__));
                    return;
                }
                c_memset(pw2s_buffer, 0, c_uc_w2s_strlen(pt_content->w2s_str) + TTS_ARGUMENT_NUMBER_BUFF_LEN);
            }
            c_uc_w2s_strncpy(pw2s_buffer, pt_content->w2s_str, c_uc_w2s_strlen(pt_content->w2s_str));
            c_uc_w2s_strncat(pw2s_buffer, tw2s_number_buffer, c_uc_w2s_strlen(tw2s_number_buffer));

            a_app_tts_play(pw2s_buffer, c_uc_w2s_strlen(pw2s_buffer));
         }
            break;
        case WDK_STRING_TOAST:
            {
                char s_toast_buff[TTS_TOAST_MAX_NUBMER_BUFF_LEN + 1];
                char s_toast_buff_tts_cec[TTS_TOAST_MAX_NUBMER_BUFF_LEN + 1];
                char s_toast_buff_tts_arc[TTS_TOAST_MAX_NUBMER_BUFF_LEN + 1];
                CHAR *s_cec_sub_str = " C E C ";
                CHAR *s_arc_sub_str = " A R C ";
                c_memset(s_toast_buff, 0, TTS_TOAST_MAX_NUBMER_BUFF_LEN + 1);
                c_memset(s_toast_buff_tts_cec, 0, TTS_TOAST_MAX_NUBMER_BUFF_LEN + 1);
                c_memset(s_toast_buff_tts_arc, 0, TTS_TOAST_MAX_NUBMER_BUFF_LEN + 1);
                UTF16_T  w2s_str[256] = {0};

                if (c_uc_w2s_strlen(pt_content->w2s_str) >= TTS_TOAST_MAX_NUBMER_BUFF_LEN)
                {
                    return;
                }

                c_uc_w2s_to_ps(pt_content->w2s_str, s_toast_buff, TTS_TOAST_MAX_NUBMER_BUFF_LEN );

                CHAR*   s_begin_cec = NULL;
                s_begin_cec = c_strstr(s_toast_buff, "CEC");
                if (s_begin_cec != NULL)
                {
                    c_strncpy(s_toast_buff_tts_cec, s_toast_buff, (UINT32)(s_begin_cec - s_toast_buff));
                    c_strcat(s_toast_buff_tts_cec, s_cec_sub_str);
                    c_strcat(s_toast_buff_tts_cec, (s_begin_cec + c_strlen("CEC")));
                    DBG_INFO(("s_toast_buff_tts_cec: %s\r\n", s_toast_buff_tts_cec));
                    c_strncpy(s_toast_buff, s_toast_buff_tts_cec, TTS_TOAST_MAX_NUBMER_BUFF_LEN + 1);
                }

                CHAR*   s_begin_arc = NULL;
                s_begin_arc = c_strstr(s_toast_buff, "ARC");
                if (s_begin_arc != NULL)
                {
                    c_strncpy(s_toast_buff_tts_arc, s_toast_buff, (UINT32)(s_begin_arc - s_toast_buff));
                    c_strcat(s_toast_buff_tts_arc, s_arc_sub_str);
                    c_strcat(s_toast_buff_tts_arc, (s_begin_arc + c_strlen("ARC")));
                    DBG_INFO(("s_toast_buff_tts_arc: %s\r\n", s_toast_buff_tts_arc));
                    c_strncpy(s_toast_buff, s_toast_buff_tts_arc, TTS_TOAST_MAX_NUBMER_BUFF_LEN + 1);
                }

                c_uc_ps_to_w2s(s_toast_buff, w2s_str, c_strlen(s_toast_buff));
                a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
            }

            break;
        default:
            DBG_INFO(("\r\n %s,%s(),%d pv_data error! \r\n", __FILE__,__FUNCTION__,__LINE__));
            break;
    }

    if(pw2s_buffer != NULL)
    {
        c_mem_free(pw2s_buffer);
        pw2s_buffer = NULL;
    }

    return;

}
#endif
/*----------------------------------------------------------------------------
 * Name: a_wdk_toast_activate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_wdk_toast_activate(
    BOOL                        b_repaint,
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            t_g_wdk_handle
)
{
    DBG_INFO(("\r\n %s,%s(),%d BEGIN \r\n", __FILE__,__FUNCTION__,__LINE__));
    WDK_OSD_TOAST_T*     pt_this = t_g_wdk_handle;
    //CHAR dst[512] = {0};

    WDK_TOAST_PARAM_T*      toast_param = (WDK_TOAST_PARAM_T*)pv_data;
    BOOL    b_need_anim = TRUE;

    if (NULL == toast_param)
    {
        DBG_INFO(("\r\n %s,%s(),%d pv_data is NULL  do nothing END. \r\n", __FILE__,__FUNCTION__,__LINE__));
        return WDKR_OK;
    }


    WDK_TOAST_STYLE_T e_toast_style = toast_param->e_toast_style;

    //if( toast_param->e_toast_style == WDK_INPUT_LIST )
    {
        WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} e_toast_style:%d\n", __FUNCTION__, __LINE__, e_toast_style )); );
    }

    if( e_toast_style == WDK_INPUT_LIST )
    {
        if (NULL != toast_param->w2s_str)
        {
            //c_uc_w2s_to_ps((const UTF16_T* )(toast_param->w2s_str), dst, 511);
            //DBG_INFO(("\r\n %s,%s(),w2s_str: %s \r\n", __FILE__,__FUNCTION__,dst));
            WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} toast_param->w2s_str:%s\n",
                __FUNCTION__, __LINE__, menu_custom_get_char_string(toast_param->w2s_str) )); );
        }
    }


    /* do NOT need animation for same widget re-activate */
    if (toast_param_temp.e_toast_style == toast_param->e_toast_style &&
        t_g_widget_info.b_is_show)
    {
        b_need_anim = FALSE;
    }

    c_memcpy(&toast_param_temp,toast_param,sizeof(WDK_TOAST_PARAM_T));

    ui1_sum=0;

    if(NULL_HANDLE != toast_param->h_t_focus_handle)
    {
        WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} c_wgl_set_focus(toast_param->h_t_focus_handle:0x%X)\n",
            __FUNCTION__, __LINE__, toast_param->h_t_focus_handle )); );
        c_wgl_set_focus(toast_param->h_t_focus_handle, FALSE);

        if(NULL_HANDLE != toast_param->pf_cb)
        {
            c_wgl_set_widget_proc(toast_param->h_t_focus_handle, toast_param->pf_cb);
        }
    }

    t_g_wdk_handle->e_style = toast_param->e_toast_style;

    switch(toast_param->e_toast_style)
    {
        case WDK_TOAST_SETTINGS_SLIDER:
            _wdk_settings_slider_activate(TRUE,pv_data, pt_this);

            #ifdef APP_TTS_SUPPORT
            _revolt_info_tts(toast_param);
            #endif
            break;

        case WDK_STRING_TOAST:
            _wdk_string_toast(TRUE,pv_data, pt_this);

            #ifdef APP_TTS_SUPPORT
            _revolt_info_tts(toast_param);
            #endif
            break;

        case WDK_WARNING_TOAST:
            _wdk_warning_toast(TRUE,pv_data, pt_this);
            break;
        case WDK_SCREEN_CENTER_MSG:
            _wdk_screen_center_msg(TRUE,pv_data, pt_this);
            break;

        case WDK_SINGLE_SELECT_LIST:
        case WDK_INPUT_LIST:

            WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

           if(WDK_INPUT_LIST == toast_param->e_toast_style &&
             (NULL_HANDLE    != pt_this->h_list_txt) &&
             (NULL_HANDLE    != pt_this->h_list_txt[0]))
            {
                WGL_COLOR_INFO_T            t_clr_info;

                /* Set Color */
                t_clr_info.e_type       =   WGL_COLOR_SET_EXTEND;
                t_clr_info.u_color_data.t_extend.t_disable            = t_g_optl_clr_on_cursor_highlight;
                t_clr_info.u_color_data.t_extend.t_enable             = t_g_optl_clr_on_cursor_highlight;
                t_clr_info.u_color_data.t_extend.t_highlight          = t_g_optl_clr_on_cursor_highlight;
                t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_optl_clr_on_cursor_highlight;
                t_clr_info.u_color_data.t_extend.t_push               = t_g_optl_clr_on_cursor_highlight;
                t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_optl_clr_on_cursor_highlight;

                WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} wgl set color(pt_this->h_list_txt[0]:0x%X, t_g_optl_clr_on_cursor_highlight)\n",
                    __FUNCTION__, __LINE__, pt_this->h_list_txt[0] )); );

                c_wgl_do_cmd ( pt_this->h_list_txt[0],
                                WGL_CMD_GL_SET_COLOR,
                                WGL_PACK(WGL_CLR_TEXT),
                                WGL_PACK(&t_clr_info ));
            }

            WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_base_frm, WGL_SW_NORMAL)) ;
            WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_dialog_frm, WGL_SW_NORMAL)) ;

            if(WDK_INPUT_LIST == toast_param->e_toast_style &&
              (NULL_HANDLE    != pt_this->h_txt_help_toast_box))
             {
                _wdk_set_help_toast(pv_data, pt_this);
             }

            _wdk_single_select_list(TRUE, pv_data, pt_this);

            break;

        case WDK_NO_SINGLE:
            _wdk_no_single(TRUE,pv_data, pt_this);
            break;
        case WDK_CENTER_DIALOG:
            _wdk_center_dialog(TRUE,pv_data, pt_this);
            break;
        case WDK_PIC_PW_POPUP:
            _wdk_ppp_active(TRUE, pv_data, pt_this);
            break;
        default :
            DBG_INFO(("\r\n %s,%s(),%d pv_data error! \r\n", __FILE__,__FUNCTION__,__LINE__));
            break;

    }

    DBG_INFO(("\r\n %s,%s,%d toast style ==> %d \r\n", __FILE__,__FUNCTION__,__LINE__,toast_param->e_toast_style));

    if (b_need_anim
        &&toast_param->e_toast_style != WDK_SINGLE_SELECT_LIST
        && toast_param->e_toast_style != WDK_INPUT_LIST
        && toast_param->e_toast_style != WDK_NO_SINGLE
        && toast_param->e_toast_style != WDK_CENTER_DIALOG
        && toast_param->e_toast_style != WDK_PIC_PW_POPUP
        &&toast_param->e_toast_style !=  WDK_SCREEN_CENTER_MSG
        && !(t_g_widget_info.b_is_show && toast_param->e_toast_style == WDK_TOAST_SETTINGS_SLIDER )
        )
    {
        if (toast_param->e_toast_style != WDK_TOAST_SETTINGS_SLIDER)
        {
            WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_base_frm, WGL_SW_RECURSIVE)) ;
        }
        if (toast_param->e_toast_style == WDK_TOAST_SETTINGS_SLIDER &&
            toast_param->e_track_style == WDK_TOAST_VOL_TRACK_CENTER)
        {
            WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_eq_hash_mark, WGL_SW_HIDE)) ;
        }
        WDK_CHK_FAIL(_wdk_anim_start_move_animation(pt_this->h_base_frm,
                                                (VOID*)&t_g_rect_out,
                                                (VOID*)&t_g_rect_in));
        tp_g_wdk_cur_active_handle = t_g_wdk_handle;

    }

    t_g_widget_info.b_is_show = TRUE;

    DBG_INFO(("\r\n %s,%s(),%d END \r\n", __FILE__,__FUNCTION__,__LINE__));

    return WDKR_OK;
}


INT32 a_wdk_toast_hide(
    BOOL                        b_repaint,
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            t_g_wdk_handle
)
{
    WDK_OSD_TOAST_T*     pt_this = t_g_wdk_handle;

    ui1_sum=0;
    //CHAR dst[512] = {0};

    if(NULL == pt_this)
    {
        DBG_INFO(("[%s %d]Waraming  current time toast is not showing\n",__FUNCTION__,__LINE__));
        return WDKR_OK;
    }
    DBG_INFO(("\r\n %s,%s(),%d begin \r\n", __FILE__,__FUNCTION__,__LINE__));

    //if( toast_param->e_toast_style == WDK_INPUT_LIST )
    {
        WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} toast_param_temp.e_toast_style:%d\n",
            __FUNCTION__, __LINE__, toast_param_temp.e_toast_style )); );
    }


    if(NULL_HANDLE != pt_this->h_line_timer)
    {
        WDK_CHK_FAIL(c_timer_stop(pt_this->h_line_timer));
    }

    if(t_g_wdk_handle == tp_g_wdk_cur_active_handle)
        tp_g_wdk_cur_active_handle = NULL;

    if (NULL != toast_param_temp.w2s_str)
    {
        //c_uc_w2s_to_ps((const UTF16_T* )(toast_param_temp.w2s_str), dst, 511);
        //DBG_INFO(("\r\n %s,%s(),w2s_str: %s \r\n", __FILE__,__FUNCTION__,dst));
        WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} toast_param_temp.w2s_str:%s\n",
            __FUNCTION__, __LINE__, menu_custom_get_char_string(toast_param_temp.w2s_str) )); );
    }

    if(toast_param_temp.e_toast_style == WDK_STRING_TOAST ||
       toast_param_temp.e_toast_style == WDK_WARNING_TOAST)
    {
        WDK_CHK_FAIL(_wdk_anim_start_move_animation(pt_this->h_base_frm,
                                                (VOID*)&t_g_rect_in,
                                                (VOID*)&t_g_rect_out));
    }

    if (pt_this->pt_wdk_param != NULL)
    {
        WDK_TOAST_PARAM_T*  pt_param = (WDK_TOAST_PARAM_T*)pt_this->pt_wdk_param;

        if (pt_param->e_toast_style == WDK_PIC_PW_POPUP)
        {
            WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_dialog_frm, WGL_SW_HIDE_RECURSIVE));
            WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_dialog_frm, NULL, TRUE));
        }
    }

    if(h_source_timer_create)
    {
        source_scrl_title_timer_stop();
    }

    WDK_CHK_FAIL(c_wgl_set_visibility (pt_this->h_base_frm, WGL_SW_HIDE_RECURSIVE));
    tp_g_wdk_cur_active_handle = NULL_HANDLE;
    t_g_widget_info.b_is_show = FALSE;
    DBG_INFO(("\r\n %s,%s(),%d END \r\n", __FILE__,__FUNCTION__,__LINE__));
    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_base_frm, NULL, TRUE));
    WDK_CHK_FAIL( c_wgl_repaint(pt_this->h_dialog_frm, NULL, TRUE));
    return WDKR_OK;
}

INT32 a_wdk_toast_deinit(WDK_OSD_TOAST_T*           t_g_wdk_handle)
{
    UINT32 ui4_num=0;
    WDK_OSD_TOAST_T*     pt_this = NULL;

    pt_this = t_g_wdk_handle;
    t_g_widget_info.b_is_show = FALSE;
    pt_this->b_have_init=FALSE;
    HANDLE_T *h_handle  = (HANDLE_T*)pt_this;
    DBG_INFO(("\r\n %s,%s(),%d \r\n", __FILE__,__FUNCTION__,__LINE__));

    if (NULL != pt_this->h_list_txt )
    {
        c_mem_free(pt_this->h_list_txt);
        pt_this->h_list_txt=NULL;
    }

    if (pt_this->pt_wdk_param != NULL)
    {
        WDK_TOAST_PARAM_T*  pt_param = (WDK_TOAST_PARAM_T*)pt_this->pt_wdk_param;

        if (pt_param->e_toast_style == WDK_PIC_PW_POPUP)
        {
            if (pt_param->style.style_ppp.pt_wdk_ppp_button != NULL)
            {
                c_mem_free(pt_param->style.style_ppp.pt_wdk_ppp_button);
                pt_param->style.style_ppp.pt_wdk_ppp_button = NULL;
            }
        }
        pt_this->pt_wdk_param = NULL;
    }

    for(ui4_num=1; ui4_num<sizeof(WDK_OSD_TOAST_T)/sizeof(HANDLE_T)-2;ui4_num++)
    {
        /*free timer*/
        if(NULL_HANDLE != (*(h_handle+ui4_num)) )
        {
            if((*(h_handle+ui4_num)) ==  pt_this->h_bk_timer
                || (*(h_handle+ui4_num)) == pt_this->h_line_timer)
            {
                c_timer_delete((*(h_handle+ui4_num)));
            }



            /*free widget*/
            if(TRUE == c_handle_valid((*(h_handle+ui4_num))))
            {
                c_wgl_destroy_widget((*(h_handle+ui4_num)));
            }
        }
    }

    if(h_source_timer_create)
    {
        c_timer_delete(h_srcl_title_timer);
        h_source_timer_create = FALSE;
    }

    c_memset(pt_this,0,sizeof(WDK_OSD_TOAST_T));

    DBG_INFO(("\r\n %s,%s(),%d end \r\n", __FILE__,__FUNCTION__,__LINE__));
    return WDKR_OK;
}


INT32 a_wdk_toast_list_adjust(HANDLE_T  *ph_list_txt,
                                         UINT32     i4_item_num
                                      )
{
    GL_RECT_T   t_rect;
    UINT8       ui1_idx = 0;
    UINT32      ui4_list_x = WDK_VIEW_LIST_TXT_ITEM_X;
    UINT32      ui4_item_w = WDK_VIEW_LIST_TXT_ITEM_W;
    UINT32      ui4_item_w_tmp;

    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[WDK][INPUT_SRC]{%s,%d} i4_item_num:%d, \n",
        __FUNCTION__, __LINE__, i4_item_num )); );

    if ((NULL == ph_list_txt)
        || (0 == i4_item_num))
    {
        return WDKR_INV_ARG;
    }

    for(ui1_idx = 0; ui1_idx < i4_item_num; ui1_idx++)
    {
        ui4_item_w_tmp = _wdk_get_string_size(ph_list_txt[ui1_idx]);
        ui4_item_w = ui4_item_w_tmp > WDK_VIEW_LIST_TXT_ITEM_W ? WDK_VIEW_LIST_TXT_ITEM_W : ui4_item_w_tmp;

       SET_RECT_BY_SIZE (&t_rect,
                ui4_list_x,
                WDK_VIEW_LIST_TXT_ITEM_Y-10-8,
                ui4_item_w,
                WDK_VIEW_LIST_TXT_ITEM_H+20+16);

      // DBG_INFO(("\n[WDK_TOAST_TESTl a_wdk_toast_list_adjust: ui1_idx[%d],item_x[%d],item_y[%d],item_w[%d],item_h[%d]\n",
      //         ui1_idx,ui4_list_x,WDK_VIEW_LIST_TXT_ITEM_Y,ui4_item_w,WDK_VIEW_LIST_TXT_ITEM_H));

      WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} ui1_idx:%d, c_wgl_move( WGL_NO_AUTO_REPAINT,(%d %d %d %d) ) \n",
          __FUNCTION__, __LINE__, ui1_idx, t_rect.i4_left, t_rect.i4_top, t_rect.i4_right, t_rect.i4_bottom)); );

        c_wgl_move (ph_list_txt[ui1_idx], &t_rect, WGL_NO_AUTO_REPAINT);

        ui4_list_x = ui4_list_x + ui4_item_w + WDK_VIEW_LIST_TXT_W_EX;
    }

    if(h_source_timer_create)
    {
        UTF16_T w2s_text[192];
        c_wgl_do_cmd (ph_list_txt[0],
                          WGL_CMD_TEXT_GET_TEXT,
                          WGL_PACK (w2s_text),
                          WGL_PACK (192));

        h_txt_title = ph_list_txt[0];

        source_scrl_title_reset(w2s_text);
    }

    return WDKR_OK;
}

INT32 a_wdk_toast_adjust_list_focus_line(UINT8 ui1_inp_before/*HANDLE_T  h_list_item*/,
                                                HANDLE_T  h_list_item_focus_line,
                                                HANDLE_T  *ph_list_txt,
                                                UINT32     i4_item_num
                                                )
{
    UINT32      ui4_item_line_w = WDK_VIEW_LIST_TXT_ITEM_W;
    UINT32      ui4_item_w_tmp = WDK_VIEW_LIST_TXT_ITEM_W;
    GL_RECT_T   t_rect;
    UINT8       ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;
    UINT8       ui1_idx = 0;
    UINT32      ui4_list_x = WDK_VIEW_LIST_TXT_ITEM_X;
    UINT32      ui4_start_line_x = 0;
    UINT32      ui4_item_line_w_tmp;
    UINT32      ui4_item_w_tmp_tmp;

    WDK_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_inp_before:%d, i4_item_num:%d, \n",
        __FUNCTION__, __LINE__, ui1_inp_before, i4_item_num )); );

    /*for underline width*/
    ui4_item_line_w_tmp = _wdk_get_string_size(ph_list_txt[ui1_inp_before]);
    ui4_item_line_w = ui4_item_line_w_tmp > WDK_VIEW_LIST_TXT_ITEM_W ? WDK_VIEW_LIST_TXT_ITEM_W : ui4_item_line_w_tmp;

    /*for underline start position*/
    for(ui1_idx = 0; ui1_idx < i4_item_num; ui1_idx++)
    {
       ui4_item_w_tmp_tmp = _wdk_get_string_size(ph_list_txt[ui1_idx]);
       ui4_item_w_tmp = ui4_item_w_tmp_tmp > WDK_VIEW_LIST_TXT_ITEM_W ? WDK_VIEW_LIST_TXT_ITEM_W : ui4_item_w_tmp_tmp;

       if(ui1_idx == ui1_inp_before)
       {
            ui4_start_line_x = ui4_list_x;
       }

       ui4_list_x = ui4_list_x + ui4_item_w_tmp + WDK_VIEW_LIST_TXT_W_EX;
    }

    if (ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON)
    {
        SET_RECT_BY_SIZE (&t_rect,/*WDK_VIEW_LINE_X + */ui4_start_line_x,(WDK_VIEW_LIST_TXT_ITEM_Y+38+8),WDK_VIEW_LINE_W*ui4_item_line_w,WDK_VIEW_LINE_H);
    }
    else
    {
        SET_RECT_BY_SIZE (&t_rect,/*WDK_VIEW_LINE_X + */ui4_start_line_x,(WDK_VIEW_LIST_TXT_ITEM_Y+38),WDK_VIEW_LINE_W*ui4_item_line_w,WDK_VIEW_LINE_H);
    }
    c_wgl_move (h_list_item_focus_line, &t_rect, WGL_NO_AUTO_REPAINT);

    return WDKR_OK;
}

BOOL a_wdk_toast_visible()
{
    return t_g_widget_info.b_is_show && (NULL != tp_g_wdk_cur_active_handle);
}


static VOID _timer_scrl_title_fct(HANDLE_T  h_timer, VOID*     pv_tag)
{
    UINT32 ui4_title_len = c_uc_w2s_strlen(w2s_text_title);
    if (ui4_title_len > SOURCE_TITLE_SCRL_LEN)
    {
        if (i4_scrl_title_offset + SOURCE_TITLE_SCRL_LEN > ui4_title_len + 1)
        {
            i4_scrl_title_offset = 0;
        }

        c_wgl_do_cmd(h_txt_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          w2s_text_title + i4_scrl_title_offset,
                          WGL_PACK((UINT16)0xFF));


        c_wgl_repaint(h_txt_title, NULL, FALSE);
        i4_scrl_title_offset++;
    }
}

static INT32 source_scrl_title_reset(UTF16_T* w2s_new_title)
{
    INT32 i4_ret = WDKR_OK;
    c_uc_w2s_strcpy(w2s_text_title, w2s_new_title);
    i4_scrl_title_offset = 0;
    source_scrl_title_timer_stop();
    UINT32 ui4_title_len = c_uc_w2s_strlen(w2s_text_title);
    if (ui4_title_len > SOURCE_TITLE_SCRL_LEN)
    {
        source_scrl_title_timer_start();
    }
    return i4_ret;
}

static INT32 source_scrl_title_timer_start(VOID)
{
    return c_timer_start(h_srcl_title_timer,
                  SOURCE_TITLE_SCRL_TIMER,
                  X_TIMER_FLAG_REPEAT,
                  _timer_scrl_title_fct,
                  NULL);
}

static INT32 source_scrl_title_timer_stop(VOID)
{
    return c_timer_stop(h_srcl_title_timer);;
}


