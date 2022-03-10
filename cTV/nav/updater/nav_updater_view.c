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
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"

#include "c_wgl.h"
#include "c_fe.h"
#include "c_handle.h"

#include "app_util/a_ui.h"
#include "nav/a_banner.h"
#include "nav/updater/nav_updater.h"

#include "res/app_util/updater/a_updater_custom.h"
#include "res/app_util/ui/ui_custom.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/updater/nav_updater_res.h"
#include "app_util/help_tip/a_help_tip.h"
#include "res/app_util/upgrade/a_upg_custom.h"
#include "res/nav/nav_dbg.h"
#include "app_util/a_network.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 -----------------------------------------------------------------------------*/
typedef struct
{
    /* common */
    HANDLE_T           h_canvas;
    HANDLE_T           h_main_frm_dl;
    HANDLE_T           h_cur_ver_title_txt;
    HANDLE_T           h_cur_ver_txt;
    HANDLE_T           h_new_ver_title_txt;
    HANDLE_T           h_new_ver_txt;
    HANDLE_T           h_upg_pkg_desc_txt;

    HANDLE_T           h_dl_sw_ver_tilte_txt;

    UINT8              u1_lang_id;
    /* current text description */
    UTF16_T            w2s_desc_str[128];

    UPDATER_CTRL_T*    pt_ctrl;

    /* dialog box */
    HANDLE_T           h_dialog;
    HANDLE_T           h_dialog_oob_processing;

    BOOL               b_show_complete_page;
    BOOL               b_show_progress;
   // HANDLE_T           h_progress_bar;

    /*new toast UI*/
    HANDLE_T           h_toast_main_frm;
    HANDLE_T           h_toast_title_txt;
    HANDLE_T           h_toast_warning_txt;
  //  HANDLE_T           h_toast_crnt_ver_txt;

    /*for installing*/
    HANDLE_T           h_toast_base_ver_lable_txt;
    HANDLE_T           h_toast_update_ver_lable_txt;
    HANDLE_T           h_toast_base_ver_txt;
    HANDLE_T           h_toast_update_ver_txt;

    /* for toast process*/
    HANDLE_T           h_toast_process_base_frm;
    HANDLE_T           h_toast_process_bar_frm;
    HANDLE_T           h_toast_process_left_icon;
    HANDLE_T           h_toast_process_right_icon;

    /*for toast process control*/
    BOOL               b_show_toast_progress;

    HANDLE_T           h_timer;

} UPDATER_VIEW_T;


#define NAV_UPDATER_TEXT(ui2_id)     MLM_NAV_TEXT(nav_get_mlm_lang_id(), ui2_id)
#define _TEXT(_txt)                  ((UTF16_T*)L##_txt)

#define NAV_UPDATE_TOAST_WARNNING_FRAME_X          (0)
#define NAV_UPDATE_TOAST_WARNNING_FRAME_Y          (-10)
#define NAV_UPDATE_TOAST_WARNNING_FRAME_W          (1920)
#define NAV_UPDATE_TOAST_WARNNING_FRAME_H          (1080)

#define NAV_UPDATE_TOAST_TITLE_X                   (0)
#define NAV_UPDATE_TOAST_TITLE_Y                   (25)
#define NAV_UPDATE_TOAST_TITLE_W                   (NAV_UPDATE_TOAST_WARNNING_FRAME_W)
#define NAV_UPDATE_TOAST_TITLE_H                   (35)

/* left inset  of version info */
#define NAV_UPDATE_TOAST_VSESION_SPACING           (20)
#define NAV_UPDATE_TOAST_VSESION_Y                 (116)

/* rect info of warnning string */
#define NAV_UPDATE_TOAST_WARNNING_TXT_X            (0)
#define NAV_UPDATE_TOAST_WARNNING_TXT_Y            (50)
#define NAV_UPDATE_TOAST_WARNNING_TXT_W            (NAV_UPDATE_TOAST_WARNNING_FRAME_W)
#define NAV_UPDATE_TOAST_WARNNING_TXT_H            (70)

/* width of version lable */
#define NAV_UPDATE_TOAST_LABLE_W                   (200)

/* hight of version  */
#define NAV_UPDATE_TOAST_LABLE_H                   (20)

/* width of version string */
#define NAV_UPDATE_TOAST_VERSION_W                 (240)
#define NAV_UPDATE_TOAST_VERSION_H                 (NAV_UPDATE_TOAST_LABLE_H)

#define NAV_UPDATE_TOAST_BASE_VER_TXT_X            (NAV_UPDATE_TOAST_TITLE_W / 2 - NAV_UPDATE_TOAST_VSESION_SPACING / 2 - NAV_UPDATE_TOAST_VERSION_W)
#define NAV_UPDATE_TOAST_BASE_VER_TXT_Y            (NAV_UPDATE_TOAST_VSESION_Y)
#define NAV_UPDATE_TOAST_BASE_VER_TXT_W            (NAV_UPDATE_TOAST_VERSION_W)
#define NAV_UPDATE_TOAST_BASE_VER_TXT_H            (NAV_UPDATE_TOAST_VERSION_H)

#define NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_W      (NAV_UPDATE_TOAST_LABLE_W)
#define NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_H      (NAV_UPDATE_TOAST_LABLE_H)
#define NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_X      (NAV_UPDATE_TOAST_BASE_VER_TXT_X - NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_W)
#define NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_Y      (NAV_UPDATE_TOAST_VSESION_Y)

#define NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_X    (NAV_UPDATE_TOAST_TITLE_W / 2 + NAV_UPDATE_TOAST_VSESION_SPACING / 2)
#define NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_Y    (NAV_UPDATE_TOAST_VSESION_Y)
#define NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_W    (NAV_UPDATE_TOAST_LABLE_W)
#define NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_H    (NAV_UPDATE_TOAST_LABLE_H)

#define NAV_UPDATE_TOAST_UPDATE_VER_TXT_X          (NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_X + NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_W)
#define NAV_UPDATE_TOAST_UPDATE_VER_TXT_Y          (NAV_UPDATE_TOAST_VSESION_Y)
#define NAV_UPDATE_TOAST_UPDATE_VER_TXT_W          (NAV_UPDATE_TOAST_VERSION_W)
#define NAV_UPDATE_TOAST_UPDATE_VER_TXT_H          (NAV_UPDATE_TOAST_VERSION_H)

/*version info*/
#define NAV_UPDAT_INFO_X     (0)
#define NAV_UPDAT_INFO_Y     (NAV_UPDATE_TOAST_WARNNING_TXT_H + 10)
#define NAV_UPDAT_INFO_W     (1920)
#define NAV_UPDAT_INFO_H     (NAV_UPDATE_TOAST_VERSION_H)
/*toast progress bar*/
#define NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_X      (0)
#define NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_Y      (NAV_UPDATE_TOAST_UPDATE_VER_TXT_Y + NAV_UPDATE_TOAST_VERSION_H * 2)
#define NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_W      (NAV_UPDATE_TOAST_WARNNING_FRAME_W)
#define NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_H      (39)

#define NAV_UPDATE_TOAST_PROCESS_BAR_FRAME_X       (0)
#define NAV_UPDATE_TOAST_PROCESS_BAR_FRAME_Y       (NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_Y)
#define NAV_UPDATE_TOAST_PROCESS_BAR_FRAME_W       (NAV_UPDATE_TOAST_WARNNING_FRAME_W)
#define NAV_UPDATE_TOAST_PROCESS_BAR_FRAME_H       (39)

#define NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_X       (0)
#define NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_Y       (0)
#define NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_W       (2)
#define NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_H       (4)

#define NAV_UPDATE_TOAST_PROCESS_RIGHT_ICON_X      (0)
#define NAV_UPDATE_TOAST_PROCESS_RIGHT_ICON_Y      (0)
#define NAV_UPDATE_TOAST_PROCESS_RIGHT_ICON_W      (2)
#define NAV_UPDATE_TOAST_PROCESS_RIGHT_ICON_H      (4)


static GL_COLOR_T   t_g_nav_update_warnning_highlight = { 255, { 255}, { 255}, { 255}} ;    /* On-Cursor text */
static GL_COLOR_T   t_g_nav_update_crnt_ver_txt_highlight = { 255, { 230}, { 230}, { 230}} ;    /* On-Cursor text */

#ifdef APP_TTS_SUPPORT
#define TTS_CNT_MAX_LEN        ((UINT16)255)
#endif

/*-----------------------------------------------------------------------------
                    variable declarations
 -----------------------------------------------------------------------------*/

static UPDATER_VIEW_T t_g_updater_view;

/*-----------------------------------------------------------------------------
                    private methods implementation
 -----------------------------------------------------------------------------*/
//static INT32 _nav_updater_show_complete_page(BOOL b_show);
static int _get_log_level_from_file(char *module_name, char *log_level_config_file)
{
    int log_level = 0;

    int i = 0;
    char log_line[128] = {'\0'};
    char *s_temp = NULL;
    char *s_log_level = NULL;
    FILE *log_file = NULL;
    log_file = fopen(log_level_config_file, "r");
    if(log_file == NULL){

        return 0;
    }

    for(;fgets(log_line,128,log_file)!=NULL;){
        s_temp = strstr(log_line, module_name);
        if(s_temp != NULL){
            s_log_level = strstr(s_temp,"=")+1;
            log_level = atoi(s_log_level);
            break;
        }
    }

    fclose(log_file);
    DBG_LOG_PRINT(("[%s %d] loglevel [%d]\n", __func__, __LINE__, log_level));
    return log_level;
}
static INT32 _nav_updater_view_toast_create_frm (VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
    WGL_IMG_INFO_T              t_img_info;

    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    ui4_style = 0;

    SET_RECT_BY_SIZE (&t_rect,
                      NAV_UPDATE_TOAST_WARNNING_FRAME_X,
                      NAV_UPDATE_TOAST_WARNNING_FRAME_Y,
                      NAV_UPDATE_TOAST_WARNNING_FRAME_W,
                      NAV_UPDATE_TOAST_WARNNING_FRAME_H);

    i4_ret = c_wgl_create_widget(pt_this->h_canvas,
                                HT_WGL_WIDGET_FRAME,
                                WGL_CONTENT_FRAME_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                &pt_this->h_toast_main_frm);

    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    =  t_g_nav_updater_res.h_g_nav_updater_warning_toast;
    t_img_info.u_img_data.t_standard.t_highlight =  t_g_nav_updater_res.h_g_nav_updater_warning_toast;
    t_img_info.u_img_data.t_standard.t_disable   =  t_g_nav_updater_res.h_g_nav_updater_warning_toast;

    i4_ret = c_wgl_do_cmd(pt_this->h_toast_main_frm,
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK(WGL_IMG_BK),
                                WGL_PACK(&t_img_info));
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

static INT32 _nav_updater_view_toast_create_warnning_txt (VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    UINT8 ui1_align = WGL_AS_CENTER_CENTER;

    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    ui4_style       =           WGL_STL_GL_NO_IMG_UI
                                | WGL_STL_TEXT_MAX_512
                                | WGL_STL_GL_NO_BK
                                | WGL_STL_TEXT_MULTILINE
                                | WGL_STL_TEXT_MAX_DIS_10_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                     NAV_UPDATE_TOAST_WARNNING_TXT_X,
                     NAV_UPDATE_TOAST_WARNNING_TXT_Y,
                     NAV_UPDATE_TOAST_WARNNING_TXT_W,
                     NAV_UPDATE_TOAST_WARNNING_TXT_H);


    i4_ret = c_wgl_create_widget (pt_this->h_toast_main_frm,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                &pt_this->h_toast_warning_txt);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* set content insert */
    c_memset (&t_inset ,0 ,sizeof (WGL_INSET_T)) ;
    i4_ret = c_wgl_do_cmd   (pt_this->h_toast_warning_txt,
                                WGL_CMD_TEXT_SET_CNT_INSET,
                                WGL_PACK(&t_inset),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = 30;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_warning_txt,
                                WGL_CMD_GL_SET_FONT,
                                WGL_PACK(&t_fnt_info),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Color */
    t_clr_info.e_type       =   WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_nav_update_warnning_highlight;
    t_clr_info.u_color_data.t_extend.t_enable             = t_g_nav_update_warnning_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_nav_update_warnning_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_nav_update_warnning_highlight;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_nav_update_warnning_highlight;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_nav_update_warnning_highlight;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_warning_txt,
                                WGL_CMD_GL_SET_COLOR,
                                WGL_PACK(WGL_CLR_TEXT),
                                WGL_PACK(&t_clr_info ));
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_warning_txt,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(ui1_align),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

static INT32 _nav_updater_view_toast_create_title_txt (VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    UINT8 ui1_align = WGL_AS_CENTER_BOTTOM;

    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    ui4_style   =  WGL_STL_GL_NO_IMG_UI
                  |WGL_STL_TEXT_MAX_512
                  |WGL_STL_GL_NO_BK
                  |WGL_STL_TEXT_MULTILINE
                  |WGL_STL_TEXT_MAX_DIS_10_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                     NAV_UPDATE_TOAST_TITLE_X,
                     NAV_UPDATE_TOAST_TITLE_Y,
                     NAV_UPDATE_TOAST_TITLE_W,
                     NAV_UPDATE_TOAST_TITLE_H);

    i4_ret = c_wgl_create_widget (pt_this->h_toast_main_frm,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)ui4_style,
                                  NULL,
                                  &pt_this->h_toast_title_txt);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* set content insert */
    c_memset (&t_inset ,0 ,sizeof (WGL_INSET_T)) ;
    i4_ret = c_wgl_do_cmd   (pt_this->h_toast_title_txt,
                                WGL_CMD_TEXT_SET_CNT_INSET,
                                WGL_PACK(&t_inset),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = 30;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_title_txt,
                                WGL_CMD_GL_SET_FONT,
                                WGL_PACK(&t_fnt_info),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Color */
    t_clr_info.e_type                                     = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_nav_update_warnning_highlight;
    t_clr_info.u_color_data.t_extend.t_enable             = t_g_nav_update_warnning_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_nav_update_warnning_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_nav_update_warnning_highlight;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_nav_update_warnning_highlight;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_nav_update_warnning_highlight;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_title_txt,
                                WGL_CMD_GL_SET_COLOR,
                                WGL_PACK(WGL_CLR_TEXT),
                                WGL_PACK(&t_clr_info ));
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_title_txt,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(ui1_align),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

static INT32 _nav_updater_view_toast_create_base_ver_lable_txt (VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    UINT8 ui1_align = WGL_AS_RIGHT_CENTER;

    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    ui4_style  =   WGL_STL_GL_NO_IMG_UI
                  |WGL_STL_TEXT_MAX_512
                  |WGL_STL_GL_NO_BK
                  |WGL_STL_TEXT_MULTILINE
                  |WGL_STL_TEXT_MAX_DIS_10_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                     NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_X,
                     NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_Y,
                     NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_W,
                     NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_H);
    NAV_UPGRADE_LOG_PRINT(("[NAV_UPDATER][%s %d][%d %d %d %d]\n",__FUNCTION__,__LINE__,
                     NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_X,
                     NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_Y,
                     NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_W,
                     NAV_UPDATE_TOAST_BASE_VER_LABLE_TXT_H));
    i4_ret = c_wgl_create_widget (pt_this->h_toast_main_frm,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                &pt_this->h_toast_base_ver_lable_txt);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* set content insert */
    c_memset (&t_inset ,0 ,sizeof (WGL_INSET_T)) ;
    i4_ret = c_wgl_do_cmd   (pt_this->h_toast_base_ver_lable_txt,
                                WGL_CMD_TEXT_SET_CNT_INSET,
                                WGL_PACK(&t_inset),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = 20;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_base_ver_lable_txt,
                                WGL_CMD_GL_SET_FONT,
                                WGL_PACK(&t_fnt_info),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Color */
    t_clr_info.e_type                                     = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_enable             = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_nav_update_crnt_ver_txt_highlight;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_base_ver_lable_txt,
                                WGL_CMD_GL_SET_COLOR,
                                WGL_PACK(WGL_CLR_TEXT),
                                WGL_PACK(&t_clr_info ));
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_base_ver_lable_txt,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(ui1_align),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

static INT32 _nav_updater_view_toast_create_update_ver_lable_txt (VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    UINT8 ui1_align = WGL_AS_RIGHT_CENTER;

    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    ui4_style   =   WGL_STL_GL_NO_IMG_UI
                  | WGL_STL_TEXT_MAX_512
                  | WGL_STL_GL_NO_BK
                  | WGL_STL_TEXT_MULTILINE
                  | WGL_STL_TEXT_MAX_DIS_10_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                     NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_X,
                     NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_Y,
                     NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_W,
                     NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_H);
    NAV_UPGRADE_LOG_PRINT(("[NAV_UPDATER][%s %d][%d %d %d %d]\n",__FUNCTION__,__LINE__,
        NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_X,
                     NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_Y,
                     NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_W,
                     NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_H));
    i4_ret = c_wgl_create_widget (pt_this->h_toast_main_frm,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)ui4_style,
                                  NULL,
                                  &pt_this->h_toast_update_ver_lable_txt);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* set content insert */
    c_memset (&t_inset ,0 ,sizeof (WGL_INSET_T)) ;
    i4_ret = c_wgl_do_cmd   (pt_this->h_toast_update_ver_lable_txt,
                             WGL_CMD_TEXT_SET_CNT_INSET,
                             WGL_PACK(&t_inset),
                             NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = 20;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_update_ver_lable_txt,
                                WGL_CMD_GL_SET_FONT,
                                WGL_PACK(&t_fnt_info),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Color */
    t_clr_info.e_type                                     = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_enable             = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_nav_update_crnt_ver_txt_highlight;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_update_ver_lable_txt,
                                WGL_CMD_GL_SET_COLOR,
                                WGL_PACK(WGL_CLR_TEXT),
                                WGL_PACK(&t_clr_info ));
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_update_ver_lable_txt,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(ui1_align),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}


static INT32 _nav_updater_view_toast_create_base_ver_txt (VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    UINT8 ui1_align = WGL_AS_LEFT_CENTER;

    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    ui4_style   =  WGL_STL_GL_NO_IMG_UI
                 | WGL_STL_TEXT_MAX_512
                 | WGL_STL_GL_NO_BK
                 | WGL_STL_TEXT_MULTILINE
                 | WGL_STL_TEXT_MAX_DIS_10_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                     NAV_UPDATE_TOAST_BASE_VER_TXT_X,
                     NAV_UPDATE_TOAST_BASE_VER_TXT_Y,
                     NAV_UPDATE_TOAST_BASE_VER_TXT_W,
                     NAV_UPDATE_TOAST_BASE_VER_TXT_H);
    NAV_UPGRADE_LOG_PRINT(("[NAV_UPDATER][%s %d][%d %d %d %d]\n",__FUNCTION__,__LINE__,
                     NAV_UPDATE_TOAST_BASE_VER_TXT_X,
                     NAV_UPDATE_TOAST_BASE_VER_TXT_Y,
                     NAV_UPDATE_TOAST_BASE_VER_TXT_W,
                     NAV_UPDATE_TOAST_BASE_VER_TXT_H));

    i4_ret = c_wgl_create_widget (pt_this->h_toast_main_frm,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                &pt_this->h_toast_base_ver_txt);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* set content insert */
    c_memset (&t_inset ,0 ,sizeof (WGL_INSET_T)) ;
    i4_ret = c_wgl_do_cmd   (pt_this->h_toast_base_ver_txt,
                             WGL_CMD_TEXT_SET_CNT_INSET,
                             WGL_PACK(&t_inset),
                             NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = 20;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_base_ver_txt,
                                WGL_CMD_GL_SET_FONT,
                                WGL_PACK(&t_fnt_info),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Color */
    t_clr_info.e_type                                    =  WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_enable             = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_nav_update_crnt_ver_txt_highlight;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_base_ver_txt,
                                WGL_CMD_GL_SET_COLOR,
                                WGL_PACK(WGL_CLR_TEXT),
                                WGL_PACK(&t_clr_info ));
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_base_ver_txt,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(ui1_align),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

static INT32 _nav_updater_view_toast_create_update_ver_txt (VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    UINT8 ui1_align = WGL_AS_LEFT_CENTER;

    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    ui4_style   =  WGL_STL_GL_NO_IMG_UI
                 | WGL_STL_TEXT_MAX_512
                 | WGL_STL_GL_NO_BK
                 | WGL_STL_TEXT_MULTILINE
                 | WGL_STL_TEXT_MAX_DIS_10_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                     NAV_UPDATE_TOAST_UPDATE_VER_TXT_X,
                     NAV_UPDATE_TOAST_UPDATE_VER_TXT_Y,
                     NAV_UPDATE_TOAST_UPDATE_VER_TXT_W,
                     NAV_UPDATE_TOAST_UPDATE_VER_TXT_H);
    NAV_UPGRADE_LOG_PRINT(("[NAV_UPDATER][%s %d][%d %d %d %d]\n",__FUNCTION__,__LINE__,
                     NAV_UPDATE_TOAST_UPDATE_VER_TXT_X,
                     NAV_UPDATE_TOAST_UPDATE_VER_TXT_Y,
                     NAV_UPDATE_TOAST_UPDATE_VER_TXT_W,
                     NAV_UPDATE_TOAST_UPDATE_VER_TXT_H));

    i4_ret = c_wgl_create_widget (pt_this->h_toast_main_frm,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                &pt_this->h_toast_update_ver_txt);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* set content insert */
    c_memset (&t_inset ,0 ,sizeof (WGL_INSET_T)) ;
    i4_ret = c_wgl_do_cmd   (pt_this->h_toast_update_ver_txt,
                                WGL_CMD_TEXT_SET_CNT_INSET,
                                WGL_PACK(&t_inset),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = 20;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_update_ver_txt,
                                WGL_CMD_GL_SET_FONT,
                                WGL_PACK(&t_fnt_info),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Color */
    t_clr_info.e_type       =   WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_enable             = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_nav_update_crnt_ver_txt_highlight;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_nav_update_crnt_ver_txt_highlight;

    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_update_ver_txt,
                                WGL_CMD_GL_SET_COLOR,
                                WGL_PACK(WGL_CLR_TEXT),
                                WGL_PACK(&t_clr_info ));
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd   (   pt_this->h_toast_update_ver_txt,
                                WGL_CMD_TEXT_SET_ALIGN,
                                WGL_PACK(ui1_align),
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

static INT32 _nav_updater_view_toast_create_toast_process_bar(VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;
    WGL_IMG_INFO_T              t_img_info;

    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    ui4_style = 0;

    /*step1: create h_toast_process_base_frm*/
    SET_RECT_BY_SIZE (&t_rect,
                      NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_X,
                      NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_Y,
                      NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_W,
                      NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_H);

    i4_ret = c_wgl_create_widget(pt_this->h_toast_main_frm,
                                HT_WGL_WIDGET_FRAME,
                                WGL_CONTENT_FRAME_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                &pt_this->h_toast_process_base_frm);

    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /*step2: create h_toast_process_bar_frm*/
    SET_RECT_BY_SIZE (&t_rect,
                      NAV_UPDATE_TOAST_PROCESS_BAR_FRAME_X,
                      NAV_UPDATE_TOAST_PROCESS_BAR_FRAME_Y,
                      NAV_UPDATE_TOAST_PROCESS_BAR_FRAME_W,
                      NAV_UPDATE_TOAST_PROCESS_BAR_FRAME_H);

    i4_ret = c_wgl_create_widget(pt_this->h_toast_process_base_frm,
                                HT_WGL_WIDGET_FRAME,
                                WGL_CONTENT_FRAME_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                &pt_this->h_toast_process_bar_frm);

    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }


    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    =  t_g_nav_updater_res.h_g_nav_updater_track_fill_toast;
    t_img_info.u_img_data.t_standard.t_highlight =  t_g_nav_updater_res.h_g_nav_updater_track_fill_toast;
    t_img_info.u_img_data.t_standard.t_disable   =  t_g_nav_updater_res.h_g_nav_updater_track_fill_toast;

    i4_ret = c_wgl_do_cmd(pt_this->h_toast_process_bar_frm,
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK(WGL_IMG_BK),
                                WGL_PACK(&t_img_info));
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

   /*step3: create h_toast_process_left_icon*/
   SET_RECT_BY_SIZE (&t_rect,
                     NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_X,
                     NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_Y,
                     NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_W,
                     NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_H);

   i4_ret = c_wgl_create_widget(pt_this->h_toast_process_base_frm,
                               HT_WGL_WIDGET_ICON,
                               WGL_CONTENT_ICON_DEF,
                               WGL_BORDER_NULL,
                               &t_rect,
                               NULL,
                               255,
                               (VOID *)WGL_STL_GL_NO_BK,
                               NULL,
                               &pt_this->h_toast_process_left_icon);
   if (WGLR_OK != i4_ret)
   {
       return NAVR_FAIL;
   }

   t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
   t_img_info.u_img_data.t_standard.t_enable    = t_g_nav_updater_res.h_g_nav_updater_track_cap_left_toast;
   t_img_info.u_img_data.t_standard.t_disable   = t_g_nav_updater_res.h_g_nav_updater_track_cap_left_toast;
   t_img_info.u_img_data.t_standard.t_highlight = t_g_nav_updater_res.h_g_nav_updater_track_cap_left_toast;

   i4_ret = c_wgl_do_cmd (pt_this->h_toast_process_left_icon,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK(WGL_IMG_FG),
                               WGL_PACK(&t_img_info));
   if (WGLR_OK != i4_ret)
   {
       return NAVR_FAIL;
   }

   /* set icon alignment */
   i4_ret = c_wgl_do_cmd (pt_this->h_toast_process_left_icon,
                               WGL_CMD_ICON_SET_ALIGN,
                               (VOID*)WGL_AS_CENTER_CENTER,
                               NULL);
   if (WGLR_OK != i4_ret)
   {
       return NAVR_FAIL;
   }

   /* set icon invisible */
   i4_ret = c_wgl_set_visibility (pt_this->h_toast_process_left_icon, WGL_SW_HIDE);
   if (WGLR_OK != i4_ret)
   {
       return NAVR_FAIL;
   }

    /*step4: create h_toast_process_right_icon*/
    SET_RECT_BY_SIZE (&t_rect,
                      NAV_UPDATE_TOAST_PROCESS_RIGHT_ICON_X,
                      NAV_UPDATE_TOAST_PROCESS_RIGHT_ICON_Y,
                      NAV_UPDATE_TOAST_PROCESS_RIGHT_ICON_W,
                      NAV_UPDATE_TOAST_PROCESS_RIGHT_ICON_H);

    i4_ret = c_wgl_create_widget(pt_this->h_toast_process_base_frm,
                                HT_WGL_WIDGET_ICON,
                                WGL_CONTENT_ICON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID *)WGL_STL_GL_NO_BK,
                                NULL,
                                &pt_this->h_toast_process_right_icon);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_g_nav_updater_res.h_g_nav_updater_track_cap_right_toast;
    t_img_info.u_img_data.t_standard.t_disable   = t_g_nav_updater_res.h_g_nav_updater_track_cap_right_toast;
    t_img_info.u_img_data.t_standard.t_highlight = t_g_nav_updater_res.h_g_nav_updater_track_cap_right_toast;

    i4_ret = c_wgl_do_cmd (pt_this->h_toast_process_right_icon,
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK(WGL_IMG_FG),
                                WGL_PACK(&t_img_info));
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd (pt_this->h_toast_process_right_icon,
                                WGL_CMD_ICON_SET_ALIGN,
                                (VOID*)WGL_AS_CENTER_CENTER,
                                NULL);
    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* set icon invisible */
    i4_ret = c_wgl_set_visibility (pt_this->h_toast_process_right_icon, WGL_SW_HIDE);

    if (WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

static INT32 _nav_updater_view_update_toast_process_bar(UINT8 ui1_value,
                                                            BOOL  b_is_repaint)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;
    FLOAT           f_step_w = 0;
    GL_RECT_T       t_rect;
    UINT32          ui4_process_range = 100;

    /*bar*/
    UINT32          ui4_bar_x = 0;
    UINT32          ui4_bar_y = 0;
    UINT32          ui4_bar_w = 0;
    UINT32          ui4_bar_h = 0;

    /*bar left icon*/
    UINT32          ui4_bar_left_icon_x = 0;
    UINT32          ui4_bar_left_icon_y = 0;
    UINT32          ui4_bar_left_icon_w = 0;
    UINT32          ui4_bar_left_icon_h = 0;

    /*bar right icon*/
    UINT32          ui4_bar_right_icon_x = 0;
    UINT32          ui4_bar_right_icon_y = 0;
    UINT32          ui4_bar_right_icon_w = 0;
    UINT32          ui4_bar_right_icon_h = 0;

    f_step_w = NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_W * 1.0 /ui4_process_range;

    /*check the progress_value first*/
    if (0 == ui1_value)
    {
        /*hide the progress bar*/
        c_wgl_set_visibility(pt_this->h_toast_process_base_frm, WGL_SW_HIDE_RECURSIVE);
    }
    else
    {
        /* adjust the progress bar accoding the process value*/
        /*Bar*/
        ui4_bar_w = ui1_value*f_step_w;
        ui4_bar_y = 0;
        ui4_bar_x = (NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_W-ui4_bar_w)/2;
        ui4_bar_h = NAV_UPDATE_TOAST_PROCESS_BASE_FRAME_H;

        /*Bar left icon*/
        ui4_bar_left_icon_x = ui4_bar_x - NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_W;
        ui4_bar_left_icon_y = NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_Y;
        ui4_bar_left_icon_w = NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_W;
        ui4_bar_left_icon_h = NAV_UPDATE_TOAST_PROCESS_LEFT_ICON_H;

        /*Bar right icon*/
        ui4_bar_right_icon_x = ui4_bar_x + ui4_bar_w;
        ui4_bar_right_icon_y = NAV_UPDATE_TOAST_PROCESS_RIGHT_ICON_Y;
        ui4_bar_right_icon_w = NAV_UPDATE_TOAST_PROCESS_RIGHT_ICON_W;
        ui4_bar_right_icon_h = NAV_UPDATE_TOAST_PROCESS_RIGHT_ICON_H;

        SET_RECT_BY_SIZE (&t_rect,
                          ui4_bar_x,
                          ui4_bar_y,
                          ui4_bar_w,
                          ui4_bar_h);

        c_wgl_move (pt_this->h_toast_process_bar_frm, &t_rect, WGL_NO_AUTO_REPAINT);

        SET_RECT_BY_SIZE (&t_rect,
                          ui4_bar_left_icon_x,
                          ui4_bar_left_icon_y,
                          ui4_bar_left_icon_w,
                          ui4_bar_left_icon_h);

        c_wgl_move (pt_this->h_toast_process_left_icon, &t_rect, WGL_NO_AUTO_REPAINT);

        SET_RECT_BY_SIZE (&t_rect,
                          ui4_bar_right_icon_x,
                          ui4_bar_right_icon_y,
                          ui4_bar_right_icon_w,
                          ui4_bar_right_icon_h);

        c_wgl_move (pt_this->h_toast_process_right_icon, &t_rect, WGL_NO_AUTO_REPAINT);

        /*Set item visible*/
        c_wgl_set_visibility(pt_this->h_toast_process_base_frm, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_process_bar_frm, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_process_left_icon, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_process_right_icon, WGL_SW_NORMAL);

    }

    if (b_is_repaint)
    {
        c_wgl_repaint(pt_this->h_toast_process_base_frm, NULL, TRUE);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_view_txt_descr_set_text
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_view_set_text(
    HANDLE_T          h_widget,
    const UTF16_T*    w2s_str
)
{
    INT32             i4_ret;

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          (VOID*)c_uc_w2s_strlen(w2s_str));

    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    return NAVR_OK;
}

static INT32 _nav_updater_view_key_monitor_nty (UINT32    ui4_msg,
                                                VOID*     pv_param1,
                                                VOID*     pv_param2,
                                                VOID*     pv_tag)
{

    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    if (pt_this->b_show_complete_page)
    {
        if(WGL_MSG_KEY_DOWN == ui4_msg)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_view_key_monitor_nty: WGL_MSG_KEY_DOWN \n"));
            nav_updater_view_show_complete_info(FALSE);
        }
    }
    else if (pt_this->b_show_progress)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"NAVR_DO_NOT_CONTINUE \n"));
        return NAVR_DO_NOT_CONTINUE;
    }

    return NAVR_OK;
}

INT32 _nav_updater_progress_bar_set_pos (INT32    i4_progress)
{
    nav_updater_view_update_toast_process_bar((UINT8)i4_progress,TRUE);
    return  0;
}

static INT32 _nav_updater_show_dlg(BOOL b_show)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;
    INT32           i4_ret;
    UTF16_T         w2s_info[256]   = {0};
    UTF16_T         w2s_ver[128]  = {0};
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (b_show)
    {
        /* Show File SW version and TV System Version */
        c_uc_w2s_strcpy(w2s_info, NAV_UPDATER_TEXT(MLM_NAV_KEY_UPDATER_SW_VER));
        c_uc_w2s_strcpy(w2s_ver, L" ");
        c_uc_w2s_strcat(w2s_ver, L"1.2.11");
        c_uc_w2s_strcat(w2s_ver, L" ");
        c_uc_w2s_strcat(w2s_ver, L"RC5-MP");
        c_uc_w2s_strcat(w2s_ver, L"\n");
        c_uc_w2s_strcat(w2s_ver, L"VIZIO");
        c_uc_w2s_strcat(w2s_ver, L" ");
        c_uc_w2s_strcat(w2s_ver, L"1.2.11");
        c_uc_w2s_strcat(w2s_ver, L" ");
        c_uc_w2s_strcat(w2s_ver, L"RC5-MP");
        c_uc_w2s_strcat(w2s_ver, L" ");
        c_uc_w2s_strcat(w2s_ver, L"25-Apr-2010");

        c_uc_w2s_strcat(w2s_info, w2s_ver);

        i4_ret = _nav_updater_view_set_text(pt_this->h_dl_sw_ver_tilte_txt, w2s_info);
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        c_wgl_set_visibility(pt_this->h_main_frm_dl, WGL_SW_RECURSIVE);
    }
    else
    {
        c_wgl_set_visibility(pt_this->h_main_frm_dl, WGL_SW_HIDE_RECURSIVE);
    }

    c_wgl_repaint(pt_this->h_canvas, NULL, TRUE);

    return NAVR_OK;
}

static VOID _nav_updater_timer_handler_hide_complete_page(VOID*    pv_tag,
                                                          VOID*    pv_reserved1,
                                                          VOID*    pv_reserved2
    )
{
    nav_updater_view_show_complete_info(FALSE);
    nav_return_activation(NAV_COMP_ID_UPDATER);
}

static VOID _nav_updater_timer_handler(HANDLE_T    h_timer,
                                       VOID*       pv_tag)
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_updater_timer_handler_hide_complete_page, pv_tag, NULL, NULL);
}

static VOID _nav_updater_timer_start(BOOL b_start)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    if (!pt_this->h_timer)
    {
        return;
    }

    if (b_start)
    {
        c_timer_start(pt_this->h_timer,
                      20000,
                      X_TIMER_FLAG_ONCE,
                      _nav_updater_timer_handler,
                      NULL);
    }
    else
    {
        c_timer_stop(pt_this->h_timer);
    }
}

static INT32 _nav_updater_view_create_simple_dialog(
    VOID
)
{
    INT32                      i4_ret;
    GL_RECT_T                  t_rect;
    UI_SIMPLE_DIALOG_INIT_T    t_simple_dialog_init;
    UPDATER_VIEW_T*            pt_this = &t_g_updater_view;

    /* create dialog box */
    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    SET_RECT_BY_SIZE(&t_rect,
                     UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_X,
                     UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_Y,
                     UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_W,
                     UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_H);

    t_simple_dialog_init.e_style            = UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY;
    t_simple_dialog_init.h_parent           = nav_get_ui_canvas();
    t_simple_dialog_init.pt_rect            = &t_rect;
    t_simple_dialog_init.pf_wdgt_proc       = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.ui2_txt_align_type = WGL_AS_CENTER_CENTER;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &(pt_this->h_dialog));

    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    return NAVR_OK;
}

static INT32 _nav_updater_view_create_oob_processing_hint(
    VOID
)
{
    INT32                      i4_ret;
    GL_RECT_T                  t_rect;
    UI_SIMPLE_DIALOG_INIT_T    t_simple_dialog_init;
    UPDATER_VIEW_T*            pt_this = &t_g_updater_view;

    /* create dialog box */
    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    SET_RECT_BY_SIZE(&t_rect,
                     (UI_DISPLAY_WIDTH - UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_W)/2,
                     0,
                     UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_W,
                     UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_H);

    t_simple_dialog_init.e_style            = UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY;
    t_simple_dialog_init.h_parent           = nav_get_ui_canvas();
    t_simple_dialog_init.pt_rect            = &t_rect;
    t_simple_dialog_init.pf_wdgt_proc       = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.ui2_txt_align_type = WGL_AS_CENTER_CENTER;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &(pt_this->h_dialog_oob_processing));

    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_view_show_simple_dialog
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_view_show_simple_dialog(UTF16_T*    w2s_text)
{
    UPDATER_VIEW_T*    pt_this = &t_g_updater_view;
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    a_ui_simple_dialog_set_text(pt_this->h_dialog, w2s_text);

    /* show dialog */
    a_ui_simple_dialog_show(pt_this->h_dialog);

    /* repaint dialog */
    a_ui_simple_dialog_repaint(pt_this->h_dialog);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_view_hide_simple_dialog
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_view_hide_simple_dialog(VOID)
{
    UPDATER_VIEW_T*    pt_this = &t_g_updater_view;
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    /* hide dialog */
    a_ui_simple_dialog_hide(pt_this->h_dialog);

    /* repaint dialog */
    a_ui_simple_dialog_repaint(pt_this->h_dialog);

    return NAVR_OK;
}

static INT32 _nav_updater_dlg_show_internet_hint(BOOL b_show, UTF16_T* w2s_text)
{
    NAV_UPGRADE_LOG_PRINT(("[NAV_UPDATER][%s %d]b_show = %d\n",__FUNCTION__,__LINE__,b_show));
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }
    if (b_show)
    {
        _nav_updater_view_show_simple_dialog(w2s_text);
    }
    else
    {
        _nav_updater_view_hide_simple_dialog();
    }

    return NAVR_OK;
}

static INT32 _nav_updater_dlg_show_uli_oob_enter_hint(BOOL b_show, UTF16_T* w2s_text)
{
    NAV_UPGRADE_LOG_PRINT(("[NAV_UPDATER][%s %d]b_show = %d\n",__FUNCTION__,__LINE__,b_show));
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }
    if (b_show)
    {
        _nav_updater_view_show_simple_dialog(w2s_text);
    }
    else
    {
        _nav_updater_view_hide_simple_dialog();
    }

    return NAVR_OK;
}

static INT32 _nav_updater_dlg_show_uli_oob_processing_hint(BOOL b_show, UTF16_T* w2s_text)
{
    UPDATER_VIEW_T*    pt_this = &t_g_updater_view;
    NAV_UPGRADE_LOG_PRINT(("[NAV_UPDATER][%s %d]b_show = %d\n",__FUNCTION__,__LINE__,b_show));
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (b_show)
    {
        a_ui_simple_dialog_set_text(pt_this->h_dialog_oob_processing, w2s_text);

        /* show dialog */
        a_ui_simple_dialog_show(pt_this->h_dialog_oob_processing);

        /* repaint dialog */
        a_ui_simple_dialog_repaint(pt_this->h_dialog_oob_processing);
    }
    else
    {
        /* hide dialog */
        a_ui_simple_dialog_hide(pt_this->h_dialog_oob_processing);

        /* repaint dialog */
        a_ui_simple_dialog_repaint(pt_this->h_dialog_oob_processing);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_view_init
 *
 * Description:
 *          initialize the updater UI
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_view_init(UPDATER_CTRL_T*    pt_ctrl,
                                    HANDLE_T           h_canvas,
                                    INT32              i4_frame_x_offset,
                                    INT32              i4_frame_y_offset)
{
    INT32           i4_ret = NAVR_OK;
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;
    UINT8  u1_odm_idx;
    UINT32 u4_mode_idx;
    CHAR sz_model_name[64] = {0};
    pt_this->b_show_complete_page = FALSE;
    pt_this->b_show_progress = FALSE;
    pt_this->h_timer = NULL_HANDLE;

    pt_this->pt_ctrl    = pt_ctrl;

    /* get language id */
    pt_this->u1_lang_id = nav_get_mlm_lang_id();

    pt_this->h_canvas   = h_canvas;

    i4_ret = _nav_updater_view_create_simple_dialog();
    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = _nav_updater_view_create_oob_processing_hint();
    _UPDATER_CHK_FAIL(i4_ret, i4_ret);
   a_cfg_custom_get_odm_idx(&u1_odm_idx);
   a_cfg_custom_get_model_idx(&u4_mode_idx);
   a_cfg_custom_get_model_name(sz_model_name);
   NAV_UPGRADE_LOG_PRINT(("[NAV_UPDATER][%s %d],screen width => %d, u1_odm_idx = %d,u1_mode_idx = %d,mode name = %s\n",__FUNCTION__,__LINE__,
   1920,
   u1_odm_idx,
   u4_mode_idx,
   sz_model_name));
    /*toast wgl*/
    _nav_updater_view_toast_create_frm();
    _nav_updater_view_toast_create_title_txt();
    _nav_updater_view_toast_create_warnning_txt();
    _nav_updater_view_toast_create_base_ver_lable_txt();
    _nav_updater_view_toast_create_update_ver_lable_txt();
    _nav_updater_view_toast_create_base_ver_txt();
    _nav_updater_view_toast_create_update_ver_txt();
    _nav_updater_view_toast_create_toast_process_bar();

    c_wgl_set_visibility(pt_this->h_canvas,
                         WGL_SW_HIDE_RECURSIVE);

    i4_ret = nav_register_key_monitor_nty_fct(
                    NAV_COMP_ID_UPDATER,
                    _nav_updater_view_key_monitor_nty,
                    NULL);
    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_view_deinit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_view_deinit(VOID)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    pt_this->pt_ctrl        = NULL;

    nav_updater_res_deinit();

    if(pt_this->h_dl_sw_ver_tilte_txt != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_this->h_dl_sw_ver_tilte_txt);
    }
    if(pt_this->h_main_frm_dl != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_this->h_main_frm_dl);
    }

    if(pt_this->h_upg_pkg_desc_txt != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_this->h_upg_pkg_desc_txt);
    }

    if(pt_this->h_new_ver_txt != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_this->h_new_ver_txt);
    }

    if(pt_this->h_new_ver_title_txt != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_this->h_new_ver_title_txt);
    }

    if(pt_this->h_cur_ver_txt != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_this->h_cur_ver_txt);
    }

    if(pt_this->h_cur_ver_title_txt != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_this->h_cur_ver_title_txt);
    }

    if(pt_this->h_canvas != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_this->h_canvas);
    }

    /* delete dialog box */
    if (NULL_HANDLE != pt_this->h_dialog)
    {
        a_ui_simple_dialog_destory(pt_this->h_dialog);
    }
    if (NULL_HANDLE != pt_this->h_dialog_oob_processing)
    {
        a_ui_simple_dialog_destory(pt_this->h_dialog_oob_processing);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_view_update_progress
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_view_update_progress(UPDATER_UPDATE_REASON_T e_update_reason)
{
    UPDATER_VIEW_T*            pt_this = &t_g_updater_view;
    CHAR                       s_temp[128];
    UINT32                     ui4_curr_upg_item_idx = pt_this->pt_ctrl->ui4_crnt_upg_item_idx;

    if(UPDATER_UPDATE_REASON_PROGRESS == e_update_reason)
    {
        UPDATER_ITEM_T*    pt_upg_item;

        /* get current upgrade item */
        pt_upg_item =
            &(pt_this->pt_ctrl->t_upg_fw_info.pt_item[ui4_curr_upg_item_idx]);

        /* set text */
        if (UPDATER_ITEM_COND_RETRIEVING == pt_upg_item->e_cond)
        {
            c_snprintf(s_temp, 128, "Retrieving ");
        }
        else
        {
            c_snprintf(s_temp, 128, "Updating ");

            if (pt_this->b_show_progress)
            {
                _nav_updater_progress_bar_set_pos(pt_this->pt_ctrl->ui1_progress);
            }
        }

        c_strcat(s_temp, pt_upg_item->s_name);
        c_strcat(s_temp, "...");

        DBG_INFO((NAV_UPDATER_PREFIX"%s progress = %d, path = %s\n",
                        s_temp,
                        pt_this->pt_ctrl->ui1_progress,
                        pt_upg_item->s_dev_path));
        updater_log_printf(NAV_UPDATER_PREFIX"%s progress = %d, path = %s\n",
                       s_temp,
                       pt_this->pt_ctrl->ui1_progress,
                       pt_upg_item->s_dev_path);

    }
    else if(UPDATER_UPDATE_REASON_COND == e_update_reason)
    {
        switch(pt_this->pt_ctrl->e_cond)
        {
            case UPDATER_COND_INIT:
                break;
            case UPDATER_COND_PREPROCESSING:
                DBG_INFO((NAV_UPDATER_PREFIX"Preprocessing, please wait\n"));
                break;

            case UPDATER_COND_VALIDATING:
                DBG_INFO((NAV_UPDATER_PREFIX"Validating firmware\n"));
                break;

            case UPDATER_COND_PARSING:
                DBG_INFO((NAV_UPDATER_PREFIX"Checking firmware version\n"));
                break;

            case UPDATER_COND_INITED:
                DBG_INFO((NAV_UPDATER_PREFIX"Are you sure to upgrade the firmware?\n"));
                break;

            case UPDATER_COND_DOWNLOADING:
                DBG_INFO((NAV_UPDATER_PREFIX"Downloading\n"));
                break;

            case UPDATER_COND_EXIT:
                switch(pt_this->pt_ctrl->e_exit_reason)
                {
                    case UPDATER_EXIT_REASON_USB_DEV_FAIL:
                        DBG_INFO((NAV_UPDATER_PREFIX"There is some problem of the USB dongle.\n"));
                        break;

                    case UPDATER_EXIT_REASON_NETWORK_FAIL:
                        DBG_INFO((NAV_UPDATER_PREFIX"Can not download firmware from network.\n"));
                        break;

                    case UPDATER_EXIT_REASON_CHECKING_UPDATE_FAIL:
                        DBG_INFO((NAV_UPDATER_PREFIX"Check new firmware failed.\n"));
                        break;

                    case UPDATER_EXIT_REASON_NO_UPDATE:
                        DBG_INFO((NAV_UPDATER_PREFIX"No available firmware to update.\n"));
                        break;

                    case UPDATER_EXIT_REASON_DECRYP_FAIL:
                        DBG_INFO((NAV_UPDATER_PREFIX"Decryption failed.\n"));
                        break;

                    case UPDATER_EXIT_REASON_VALIDATE_FAIL:
                        DBG_INFO((NAV_UPDATER_PREFIX"Firmware is invalid.\n"));
                        break;

                    case UPDATER_EXIT_REASON_PARSE_FAIL:
                        DBG_INFO((NAV_UPDATER_PREFIX"No available firmware version.\n"));
                        break;

                    case UPDATER_EXIT_REASON_INTRNL_ERR:
                        DBG_INFO((NAV_UPDATER_PREFIX"Internal error.\n"));
                        break;

                    case UPDATER_EXIT_REASON_USB_NOT_READY:
                        DBG_INFO((NAV_UPDATER_PREFIX"USB dongle is not ready, please plug it and try again.\n"));
                        break;

                    case UPDATER_EXIT_REASON_USB_SPACE_NOT_ENOUGH:
                        DBG_INFO((NAV_UPDATER_PREFIX"Available space of your USB dongle is not enough.\n"));
                        break;

                    default:
                        break;
                }
                break;

            case UPDATER_COND_FAILED:
                break;

            case UPDATER_COND_COMPLETE:
                break;

            case UPDATER_COND_DEAD:
                break;

            case UPDATER_COND_COMPLETE_ONE:
                break;

            default:
                break;
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_view_show
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_view_show(UPDATER_SHOW_DLG_TYPE_T e_type, UTF16_T* w2s_text)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;

    if (pt_this->b_show_complete_page)
    {
        nav_updater_view_show_complete_info(FALSE);
    }

    if (UPDATER_SHOW_DLG_TYPE_COPY == e_type)
    {
        _nav_updater_show_dlg(TRUE);
    }
    else if (UPDATER_SHOW_DLG_TYPE_ULI_USB == e_type)
    {
       nav_updater_view_show_usb_info(TRUE);

    }
    else if (UPDATER_SHOW_DLG_TYPE_PREPROCESS == e_type)
    {
        nav_updater_show_preprocess_page_ex(TRUE);
    }
    else if (UPDATER_SHOW_DLG_TYPE_UPGRADE == e_type)
    {
        nav_updater_show_updating_page_ex(TRUE);
    }
    else if (UPDATER_SHOW_DLG_INTRNT_HINT == e_type)
    {
        _nav_updater_dlg_show_internet_hint(TRUE, w2s_text);
    }
    else if (UPDATER_SHOW_DLG_ULI_OOB_ENTER == e_type)
    {
        _nav_updater_dlg_show_uli_oob_enter_hint(TRUE, w2s_text);
    }
    else if (UPDATER_SHOW_DLG_ULI_OOB_PROCESSING == e_type)
    {
        _nav_updater_dlg_show_uli_oob_processing_hint(TRUE, w2s_text);
    }
    else if (UPDATER_SHOW_DLG_TYPE_UPGRADE_COMPLETE == e_type)
    {
        nav_updater_view_show_complete_info(TRUE);
    }
    else if (UPDATER_SHOW_DLG_TYPE_ULI_COMMAND_STICK == e_type)
    {
        nav_updater_view_show_command_stick_info(TRUE);
    }
    else if(UPDATER_SHOW_DLG_TYPE_ULI_USB_COMMAND_STICK_PROCESS == e_type)
    {
        nav_updater_view_show_usb_command_process_info(TRUE);
    }
    else if (UPDATER_SHOW_DLG_TYPE_ISP_UPGRADE == e_type)
    {
        nav_updater_show_isp_updating_page_ex(TRUE);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_view_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_view_hide(VOID)
{
    UPDATER_VIEW_T*            pt_this = &t_g_updater_view;
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    _nav_updater_show_dlg(FALSE);

    if (pt_this->b_show_complete_page)
    {
        nav_updater_view_show_complete_info(FALSE);
    }
    else
    {
        nav_updater_show_updating_page_ex(FALSE);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
                    public methods implementations
 -----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: nav_updater_view_register_default_hdlr
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 nav_updater_view_register_default_hdlr(UPDATER_VIEW_HDLR_T*    pt_view_hdlr)
{
    if (NULL == pt_view_hdlr)
    {
        return NAVR_INV_ARG;
    }

    pt_view_hdlr->pf_init            = _nav_updater_view_init;
    pt_view_hdlr->pf_deinit          = _nav_updater_view_deinit;
    pt_view_hdlr->pf_update_progress = _nav_updater_view_update_progress;
    pt_view_hdlr->pf_show_dialog     = _nav_updater_view_show;
    pt_view_hdlr->pf_hide_dialog     = _nav_updater_view_hide;

    return NAVR_OK;
}

INT32 nav_updater_view_show_usb_info(BOOL b_show)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;
    INT32           i4_ret;
    CHAR            s_str_tmp[128];
    UTF16_T         w2s_desc_str[128];
    UTF16_T         w2s_desc_str_update[128] = {0};

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d b_show[%d]\n",__FUNCTION__,__LINE__,b_show));
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (b_show)
    {
        UINT8  u1_odm_idx;
        UINT32 u4_mode_idx;
        CHAR sz_model_name[64] = {0};

        a_cfg_custom_get_odm_idx(&u1_odm_idx);
        a_cfg_custom_get_model_idx(&u4_mode_idx);
        a_cfg_custom_get_model_name(sz_model_name);
        NAV_UPGRADE_LOG_PRINT(("[NAV_UPDATER][%s %d],screen width => %d, u1_odm_idx = %d,u1_mode_idx = %d,mode name = %s\n",__FUNCTION__,__LINE__,
        1920,
        u1_odm_idx,
        u4_mode_idx,
        sz_model_name));
        nav_updater_view_set_toast_process_bar_status(TRUE);

        nav_updater_view_update_toast_process_bar(0,FALSE);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_title_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_IN_PROGRESS_TITLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_warning_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_IN_PROGRESS_WARNING));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_base_ver_lable_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_BASE_VER_LABLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_update_ver_lable_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_UPDATE_VER_LABLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        /* Get Version from TV */
        a_fw_updater_cust_get_sys_ver(UPGRADE_FIRM, s_str_tmp, 128);

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Current Version is %s...\n", s_str_tmp));

        updater_log_printf(NAV_UPDATER_PREFIX"Current Version is %s...\n", s_str_tmp);

        c_uc_ps_to_w2s(s_str_tmp, w2s_desc_str, 128);
        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_base_ver_txt,
                                            w2s_desc_str);
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        nav_updater_get_update_ver_string(s_str_tmp);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Update Version is %s...\n", s_str_tmp));
        c_uc_ps_to_w2s(s_str_tmp, w2s_desc_str_update, 128);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_update_ver_txt,
                                            w2s_desc_str_update);
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        /*first hide all*/
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        /*show selectd item*/
        c_wgl_set_visibility(pt_this->h_toast_title_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_warning_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_base_ver_lable_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_update_ver_lable_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_update_ver_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_base_ver_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_NORMAL);
		a_nav_updater_iom_all_key_locked(TRUE,TRUE);//for check update only the power  should work

    }
    else
    {
        nav_updater_view_set_toast_process_bar_status(FALSE);
		a_nav_updater_iom_all_key_locked(FALSE,FALSE);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);
    }

    c_wgl_repaint(pt_this->h_canvas, NULL, TRUE);

    return NAVR_OK;
}


INT32 nav_updater_view_show_command_stick_info(BOOL b_show)
{

    UPDATER_VIEW_T*            pt_this = &t_g_updater_view;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_view_show_command_stick_info b_show[%d]\n",b_show));
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (b_show)
    {
        _nav_updater_view_set_text(pt_this->h_toast_warning_txt,
                              NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_COMMAND_STICK_WARNING));
        /*first hide all*/
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        c_wgl_set_visibility(pt_this->h_toast_warning_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_NORMAL);
    }
    else
    {
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);
    }

    c_wgl_repaint(pt_this->h_canvas, NULL, TRUE);

    return NAVR_OK;
}

INT32 nav_updater_view_show_usb_command_process_info(BOOL b_show)
{

    UPDATER_VIEW_T*            pt_this = &t_g_updater_view;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_view_show_command_stick_info b_show[%d]\n",b_show));
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (b_show)
    {
        _nav_updater_view_set_text(pt_this->h_toast_warning_txt,
                              NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_USB_COMMAND_POP_INFO));
        /*first hide all*/
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        c_wgl_set_visibility(pt_this->h_toast_warning_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_NORMAL);
    }
    else
    {
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);
    }

    c_wgl_repaint(pt_this->h_canvas, NULL, TRUE);

    return NAVR_OK;
}


static BOOL _nav_updater_view_check_network_connected(VOID)
{
	return (0== a_nw_connection_test((CHAR*)"www.google.com") || 0 == a_nw_connection_test6((CHAR*)"www.google.com"));
}

INT32 nav_updater_view_show_download_fail_info(BOOL b_show)
{

    UPDATER_VIEW_T*            pt_this = &t_g_updater_view;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_view_show_firmware_check_not_avaliable_info b_show[%d]\n",b_show));
    UTF16_T *p_error = NULL;
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (b_show)
    {
        p_error = MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                              (!_nav_updater_view_check_network_connected() ?
                              MLM_NAV_KEY_NAV_UPDATE_DOWNLOADING_FAIL_NO_NETWORK : MLM_NAV_KEY_NAV_UPDATE_DOWNLOADING_FAIL_ERROR ));
        _nav_updater_view_set_text(pt_this->h_toast_warning_txt, p_error);
#ifdef APP_TTS_SUPPORT

        UTF16_T ws_buf[TTS_CNT_MAX_LEN+1] = {0};

        /* TTS string for UPDATE_FW_NOT_AVAILABLE has been changed.
           We removed the dash in up-to-date to avoid the dash pronunciation.
           If the source UPDATE_FW_NOT_AVAILABLE was changed,
           the corresponding string may need also be changed.*/

        c_uc_w2s_strncpy(ws_buf,
                         p_error,
                         TTS_CNT_MAX_LEN);

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_app_tts_play\n"));
        a_app_tts_play(ws_buf,c_uc_w2s_strlen (ws_buf));
#endif
#ifdef APP_ZOOM_MODE_SUPPORT
       a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_BANNER));
#endif

        /*first hide all*/
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        c_wgl_set_visibility(pt_this->h_toast_warning_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_NORMAL);
		a_nav_updater_iom_all_key_locked(TRUE,TRUE);
    }
    else
    {
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);
		a_nav_updater_iom_all_key_locked(FALSE,FALSE);
    }

    c_wgl_repaint(pt_this->h_canvas, NULL, TRUE);


    return NAVR_OK;
}

INT32 nav_updater_view_show_firmware_check_not_avaliable_info(BOOL b_show)
{

    UPDATER_VIEW_T*            pt_this = &t_g_updater_view;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_view_show_firmware_check_not_avaliable_info b_show[%d]\n",b_show));
    UTF16_T *p_error = NULL;
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (b_show)
    {
        p_error = MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                              (!_nav_updater_view_check_network_connected() ?
                              MLM_NAV_KEY_NAV_UPDATE_FOR_NO_NETWORK_CONNECT : MLM_NAV_KEY_NAV_UPDATE_FIRMWARE_NOT_AVAILABLE ));
        _nav_updater_view_set_text(pt_this->h_toast_warning_txt, p_error);
#ifdef APP_TTS_SUPPORT

        UTF16_T ws_buf[TTS_CNT_MAX_LEN+1] = {0};

        /* TTS string for UPDATE_FW_NOT_AVAILABLE has been changed.
           We removed the dash in up-to-date to avoid the dash pronunciation.
           If the source UPDATE_FW_NOT_AVAILABLE was changed,
           the corresponding string may need also be changed.*/

        c_uc_w2s_strncpy(ws_buf,
                         p_error,
                         TTS_CNT_MAX_LEN);

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_app_tts_play\n"));
        a_app_tts_play(ws_buf,c_uc_w2s_strlen (ws_buf));
#endif
#ifdef APP_ZOOM_MODE_SUPPORT
       a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_BANNER));
#endif

        /*first hide all*/
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        c_wgl_set_visibility(pt_this->h_toast_warning_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_NORMAL);
    }
    else
    {
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);
    }

    c_wgl_repaint(pt_this->h_canvas, NULL, TRUE);


    return NAVR_OK;
}

INT32 nav_updater_view_show_complete_info(BOOL b_show)
{
    UPDATER_VIEW_T*   pt_this = &t_g_updater_view;
    UTF16_T           w2s_str_ver[256];
    CHAR              s_str_tmp[128];
    INT32             i4_ret;
    GL_RECT_T         t_rect;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d b_show[%d]\n",__FUNCTION__,__LINE__,b_show));
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (b_show)
    {
        if (pt_this->b_show_complete_page)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_show_complete_info() [alread show]\n"));
            return NAVR_OK;
        }

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_show_complete_info()\n"));

        /* initial timer */
        if (!pt_this->h_timer)
        {
            i4_ret =c_timer_create (&pt_this->h_timer);
            _UPDATER_CHK_FAIL(i4_ret, i4_ret);
        }

        a_fw_updater_cust_get_sys_ver(0, s_str_tmp, 128);

        c_uc_ps_to_w2s(s_str_tmp, w2s_str_ver, 128);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Current Version is %s\n",s_str_tmp));
        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_update_ver_lable_txt,
                                            NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_BASE_VER_LABLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);
        _nav_updater_view_set_text(pt_this->h_toast_title_txt,
                                   (UTF16_T*)L"");

        _nav_updater_view_set_text(pt_this->h_toast_warning_txt,
                                   NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_COMPLETE_WARNING));
        _nav_updater_view_set_text(pt_this->h_toast_update_ver_txt, w2s_str_ver);
        SET_RECT_BY_SIZE (&t_rect,
                          NAV_UPDATE_TOAST_TITLE_W / 2 - NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_W,
                          NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_Y,
                          NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_W,
                          NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_H);

        c_wgl_move (pt_this->h_toast_update_ver_lable_txt, &t_rect, WGL_NO_AUTO_REPAINT);

        SET_RECT_BY_SIZE (&t_rect,
                          NAV_UPDATE_TOAST_TITLE_W / 2,
                          NAV_UPDATE_TOAST_UPDATE_VER_TXT_Y,
                          NAV_UPDATE_TOAST_UPDATE_VER_TXT_W,
                          NAV_UPDATE_TOAST_UPDATE_VER_TXT_H);

        c_wgl_move (pt_this->h_toast_update_ver_txt, &t_rect, WGL_NO_AUTO_REPAINT);

        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        c_wgl_set_visibility(pt_this->h_toast_title_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_warning_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_update_ver_lable_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_update_ver_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_NORMAL);

        _nav_updater_timer_start(TRUE);

        pt_this->b_show_progress = FALSE;
        pt_this->b_show_complete_page = TRUE;

        a_cfg_cust_set_log_level(_get_log_level_from_file("overall_default", "/config/loglevel.ini"));
    }
    else
    {
        pt_this->b_show_complete_page = FALSE;
        SET_RECT_BY_SIZE(&t_rect,
                         NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_X,
                         NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_Y,
                         NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_W,
                         NAV_UPDATE_TOAST_UPDATE_VER_LABLE_TXT_H);
        c_wgl_move (pt_this->h_toast_update_ver_lable_txt, &t_rect, WGL_NO_AUTO_REPAINT);
        SET_RECT_BY_SIZE(&t_rect,
                         NAV_UPDATE_TOAST_UPDATE_VER_TXT_X,
                         NAV_UPDATE_TOAST_UPDATE_VER_TXT_Y,
                         NAV_UPDATE_TOAST_UPDATE_VER_TXT_W,
                         NAV_UPDATE_TOAST_UPDATE_VER_TXT_H);
        c_wgl_move (pt_this->h_toast_update_ver_txt, &t_rect, WGL_NO_AUTO_REPAINT);
        _nav_updater_timer_start(FALSE);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);
    }

    c_wgl_repaint(pt_this->h_canvas, NULL, TRUE);

    return NAVR_OK;
}

INT32 nav_updater_show_preprocess_page_ex(BOOL b_show)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;
    INT32           i4_ret;
    CHAR            s_str_tmp[128];
    UTF16_T         w2s_desc_str[128];

    UTF16_T         w2s_desc_str_update[128] = {0};

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d b_show[%d]\n",__FUNCTION__,__LINE__,b_show));
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (b_show)
    {
        nav_updater_view_set_toast_process_bar_status(TRUE);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_title_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_IN_PROGRESS_TITLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_warning_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_IN_PROGRESS_WARNING));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_base_ver_lable_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_BASE_VER_LABLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_update_ver_lable_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_UPDATE_VER_LABLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        /* Get Version from TV */
        a_fw_updater_cust_get_sys_ver(UPGRADE_FIRM, s_str_tmp, 128);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Current Version is %s...\n", s_str_tmp));
        updater_log_printf(NAV_UPDATER_PREFIX"Current Version is %s...\n", s_str_tmp);

        c_uc_ps_to_w2s(s_str_tmp, w2s_desc_str, 128);
        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_base_ver_txt,
                                            w2s_desc_str);
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        nav_updater_get_update_ver_string(s_str_tmp);

        c_uc_ps_to_w2s(s_str_tmp, w2s_desc_str_update, 128);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Update Version is %s...\n", s_str_tmp));
        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_update_ver_txt,
                                            w2s_desc_str_update);
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        c_wgl_set_visibility(pt_this->h_toast_title_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_warning_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_base_ver_lable_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_update_ver_lable_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_update_ver_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_base_ver_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_NORMAL);

        pt_this->b_show_progress = TRUE;
		a_nav_updater_iom_all_key_locked(TRUE,TRUE);
    }
    else
    {
        nav_updater_view_set_toast_process_bar_status(FALSE);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        pt_this->b_show_progress = FALSE;
		a_nav_updater_iom_all_key_locked(FALSE,FALSE);
    }

    c_wgl_repaint(pt_this->h_canvas, NULL, TRUE);

    return NAVR_OK;
}

INT32 nav_updater_show_updating_page_ex(BOOL b_show)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;
    INT32           i4_ret;
    CHAR            s_str_tmp[128] = {0};
    UTF16_T         w2s_desc_str_base[128] = {0};
    UTF16_T         w2s_desc_str_update[128] = {0};

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d b_show[%d]\n",__FUNCTION__,__LINE__,b_show));
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (b_show)
    {
        nav_updater_view_set_toast_process_bar_status(TRUE);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_title_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_FIRMWARM_UPGRADING_TITLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_warning_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_FIRMWARM_UPGRADING_TEXT));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_base_ver_lable_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_BASE_VER_LABLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_update_ver_lable_txt,
                                        NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_UPDATE_VER_LABLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        /* Get Version from TV */
        a_fw_updater_cust_get_sys_ver(UPGRADE_FIRM, s_str_tmp, 128);

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Current Version is %s...\n", s_str_tmp));

        //updater_log_printf(NAV_UPDATER_PREFIX"Current Version is %s...\n", s_str_tmp);

        c_uc_ps_to_w2s(s_str_tmp, w2s_desc_str_base, 128);
        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_base_ver_txt,
                                            w2s_desc_str_base);
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Update Version is %s...\n", s_str_tmp));
        updater_log_printf(NAV_UPDATER_PREFIX"Update Version is %s...\n", s_str_tmp);

        nav_updater_get_update_ver_string(s_str_tmp);

        updater_log_printf(NAV_UPDATER_PREFIX"UTV Update Version is %s...\n", s_str_tmp);

        c_uc_ps_to_w2s(s_str_tmp, w2s_desc_str_update, 128);
        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_update_ver_txt,
                                            w2s_desc_str_update);
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        c_wgl_set_visibility(pt_this->h_toast_title_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_warning_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_base_ver_lable_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_update_ver_lable_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_base_ver_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_update_ver_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_NORMAL);

        pt_this->b_show_progress = TRUE;
		a_nav_updater_iom_all_key_locked(TRUE,TRUE);
    }
    else
    {
        nav_updater_view_set_toast_process_bar_status(FALSE);

        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        pt_this->b_show_progress = FALSE;
		a_nav_updater_iom_all_key_locked(FALSE,FALSE);
    }

    c_wgl_repaint(pt_this->h_canvas, NULL, TRUE);

    return NAVR_OK;
}

INT32 nav_updater_show_isp_updating_page_ex(BOOL b_show)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;
    INT32           i4_ret;
    CHAR            s_str_tmp[128] = {0};
    UTF16_T         w2s_desc_str_base[128] = {0};
    UTF16_T         w2s_desc_str_update[128] = {0};

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d b_show[%d]\n",__FUNCTION__,__LINE__,b_show));
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (b_show)
    {
        nav_updater_view_set_toast_process_bar_status(TRUE);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_title_txt,
                NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_ISP_FIRMWARM_UPGRADING_TITLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_warning_txt,
                NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_ISP_FIRMWARM_UPGRADING_TEXT));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_base_ver_lable_txt,
                NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_BASE_VER_LABLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_update_ver_lable_txt,
                NAV_UPDATER_TEXT(MLM_NAV_KEY_NAV_UPDATE_UPDATE_VER_LABLE));
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

#ifdef MTK_CAMERA_DPTZ_SUPPORT
        nav_updater_isp_get_current_version(s_str_tmp, 128);
#endif

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Current ISP Version is %s...\n", s_str_tmp));


        c_uc_ps_to_w2s(s_str_tmp, w2s_desc_str_base, 128);
        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_base_ver_txt,
                w2s_desc_str_base);
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Update Version is %s...\n", s_str_tmp));
        updater_log_printf(NAV_UPDATER_PREFIX"Update Version is %s...\n", s_str_tmp);

#ifdef MTK_CAMERA_DPTZ_SUPPORT
        nav_updater_isp_get_version(s_str_tmp, 128);
#endif

        updater_log_printf(NAV_UPDATER_PREFIX"UTV Update Version is %s...\n", s_str_tmp);

        c_uc_ps_to_w2s(s_str_tmp, w2s_desc_str_update, 128);
        i4_ret = _nav_updater_view_set_text(pt_this->h_toast_update_ver_txt,
                w2s_desc_str_update);
        _UPDATER_CHK_FAIL(i4_ret, i4_ret);

        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        c_wgl_set_visibility(pt_this->h_toast_title_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_warning_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_base_ver_lable_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_update_ver_lable_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_base_ver_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_update_ver_txt, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_NORMAL);

        pt_this->b_show_progress = FALSE;
        a_nav_updater_iom_all_key_locked(TRUE,TRUE);
    }
    else
    {
        nav_updater_view_set_toast_process_bar_status(FALSE);

        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);

        pt_this->b_show_progress = FALSE;
        a_nav_updater_iom_all_key_locked(FALSE,FALSE);
    }

    c_wgl_repaint(pt_this->h_canvas, NULL, TRUE);

    return NAVR_OK;
}

INT32 nav_updater_show_toast_progress_test(UINT8 ui1_value)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (0 == ui1_value)
    {
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_HIDE_RECURSIVE);
    }
    else
    {
        c_wgl_set_visibility(pt_this->h_toast_main_frm, WGL_SW_NORMAL);
        _nav_updater_view_update_toast_process_bar(ui1_value,FALSE);
    }

    c_wgl_repaint(pt_this->h_toast_main_frm, NULL, TRUE);

    return NAVR_OK;
}

INT32 nav_updater_view_update_toast_process_bar(UINT8 ui1_value,
                                                            BOOL  b_is_repaint)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;
    if(a_bgm_is_running())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s %d slient update mode show not go this flow\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if (pt_this->b_show_toast_progress)
    {
        _nav_updater_view_update_toast_process_bar(ui1_value,b_is_repaint);
    }

    return NAVR_OK;
}

INT32 nav_updater_view_set_toast_process_bar_status(BOOL b_is_show)
{
    UPDATER_VIEW_T* pt_this = &t_g_updater_view;
    pt_this->b_show_toast_progress = b_is_show;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_view_set_toast_process_bar_status b_is_show[%d]\n",b_is_show));

    return NAVR_OK;
}

BOOL nav_updater_view_warm_msg_is_showing(VOID)
{
    BOOL  b_visiable = FALSE;

    c_wgl_get_visibility(t_g_updater_view.h_toast_warning_txt,&b_visiable);

    return  b_visiable;
}

