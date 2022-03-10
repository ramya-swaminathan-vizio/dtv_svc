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
 * $RCSfile: menu_page_nw_pwd.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <string.h>

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_drv_cust.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_page_animation.h"
#include "app_util/a_cfg.h"
#include "app_util/a_drv_interface.h"

#include "wdk/a_vkb.h"
#include "wdk/a_wdk.h"
#include "res/wdk/a_vkb_custom.h"
#include "wdk/vkb/vkb.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_video.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_common/a_menu_page_color_tuner.h"
#include "res/app_util/config/acfg_custom.h"

#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#endif

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif
#include "res/app_util/icl/a_icl_custom.h"

#include "menu2/menu_dbg.h"


/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
// DTV02079035 [MVV-2755]
#define MENU_COLOR_CALI_ENABLE_DYNAMIC_RANGE    1

#define COLOR_CALIBRATION_BTN_X                (MENU_ITEM_V_LEFT)
#define COLOR_CALIBRATION_BTN_Y                (400)
#define COLOR_CALIBRATION_BTN_W                (MENU_ITEM_V_WIDE)
#define COLOR_CALIBRATION_BTN_H                (MENU_ITEM_V_HEIGHT)

#define COLOR_CALIBRATION_BTN_INSET_LEFT            (FRAME_LEFT_RIGHT_INTV - 8)
#define COLOR_CALIBRATION_BTN_INSET_RIGHT       10

#define COLOR_CALIBRATION_GUIDE_TEXT_X          (5)
#define COLOR_CALIBRATION_GUIDE_TEXT_Y          (5)
#define COLOR_CALIBRATION_GUIDE_TEXT_W          (CONTENT_W -60)
#define COLOR_CALIBRATION_GUIDE_TEXT_H          (60)

#define COLOR_CALIBRATION_LST_VISIBLE_ELEM             (12)
#define COLOR_CALIBRATION_LST_X                        (0 * GRID_W)
#define COLOR_CALIBRATION_LST_Y                        (0 * GRID_H)
#define COLOR_CALIBRATION_LST_W                        (CONTENT_W)
#define COLOR_CALIBRATION_LST_H                        (COLOR_CALIBRATION_LST_VISIBLE_ELEM * GRID_H)

#define MAX_REC                                     (ACFG_PRE_SET_PIC_MODE_NUM)

#define MENU_PAGE_CAP_STL_MAX_ITEM_NUM      (11)

#define COLOR_CALIBRATION_LB_INSET_LEFT      (10)
#define COLOR_CALIBRATION_LB_INSET_RIGHT     (10)

#define COLOR_CALIBRATION_NAME_MAX_LEN         (32)

#define COLOR_CALIBRATION_DEV_DISP_NAME_ALIGN        (WGL_AS_LEFT_CENTER)
#define COLOR_CALIBRATION_DEV_DISP_NAME_MAX_TEXT_LEN (COLOR_CALIBRATION_NAME_MAX_LEN)
#define COLOR_CALIBRATION_DEV_DISP_NAME_COL_WIDTH    (UINT32)(MENU_ITEM_V_WIDE/2)

#define COLOR_CALIBRATION_DEV_USER_NAME_ALIGN        (WGL_AS_RIGHT_CENTER)
#define COLOR_CALIBRATION_DEV_USER_NAME_MAX_TEXT_LEN (COLOR_CALIBRATION_NAME_MAX_LEN)
#define COLOR_CALIBRATION_DEV_USER_NAME_COLUMN_WIDTH (MENU_ITEM_V_WIDE -COLOR_CALIBRATION_DEV_DISP_NAME_COL_WIDTH)

#define COLOR_CALIBRATION_MAX_DEVICE_NUM               (8)

#define COLOR_CALIBRATION_DEV_LIST_X           (MENU_ITEM_V_INSET_L)
#define COLOR_CALIBRATION_DEV_LIST_Y           (0)
#define COLOR_CALIBRATION_DEV_LIST_W           (MENU_ITEM_V_WIDE)
#define COLOR_CALIBRATION_DEV_LIST_H           (43*8)
#define COLOR_CALIBRATION_DEV_LIST_ELEM_HEIGHT      (COLOR_CALIBRATION_BTN_H)

#define COLOR_CALIBRATION_DV_ICON_X               (280)
#define COLOR_CALIBRATION_DV_ICON_Y               (5)
#define COLOR_CALIBRATION_DV_ICON_W               (49)
#define COLOR_CALIBRATION_DV_ICON_H               (64)

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

typedef enum _COLOR_CALIBRATION_SUBPAGE_T
{
    COLOR_CALIBRATION_SUBPAGE_MAIN = 0,
    COLOR_CALIBRATION_SUBPAGE_LAST_ENTRY,
}COLOR_CALIBRATION_SUBPAGE_T;

typedef struct COLOR_CALIBRATION
{
    HANDLE_T     h_cnt_frm;
    HANDLE_T     h_menu_current_focus;
    BOOL         b_finish;
    BOOL         b_this_page_show;
    HANDLE_T     h_dlg;
    BOOL         b_is_dlg_show;
    UINT32       ui4_page_id;
    CHAR         s_input_buf[MENU_CUST_PIC_MODE_NAME_MAX_LEN];
    UTF16_T      w2s_clr_temp[MENU_PRESET_PIC_MODE_NAME_LEN+1];

    HANDLE_T         h_color_tuner;
    HANDLE_T         h_wb_color_tuner;  //white balance tuner
    HANDLE_T         h_reset_color_tuner;//lock pic mode and unlock pic mode share the item
    BOOL             b_is_reset_enable;

  #if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
    HANDLE_T         h_calibration_test; // Calibration Test
    BOOL            bFromCaliTest;
  #endif

    HANDLE_T         h_info_list;//For pic mode && color temp
    COLOR_CALIBRATION_SUBPAGE_T e_subpage;
    COLOR_CALIBRATION_SUBPAGE_T e_pre_subpage;
    HANDLE_T         h_last_focus_item;
    UINT16           ui2_icl_nfy_id_pic_reset;  /* The icl picture reset notify id */
    HANDLE_T         h_dv_icon;
}COLOR_CALIBRATION;

typedef enum _COLOR_CALIBRATION_BTN_TYPE_T
{
#if( MENU_COLOR_CALI_ENABLE_DYNAMIC_RANGE )
    COLOR_CALIBRATION_BTN_COLOR_TUNER       = 3,
#else
    COLOR_CALIBRATION_BTN_COLOR_TUNER       = 2,
#endif

    COLOR_CALIBRATION_BTN_WB_COLOR_TUNER    ,
    COLOR_CALIBRATION_BTN_RESET_COLOR_TUNER ,
    COLOR_CALIBRATION_BTN_CALIBRATION_TEST  ,

    COLOR_CALIBRATION_BTN_LAST_ENTRY
}COLOR_CALIBRATION_BTN_TYPE_T;

#define MENU_COLOR_CALI_COLOR_TUNER_ITEM_IDX    _color_cali_UiFunc_convert_UiItemIdx(COLOR_CALIBRATION_BTN_COLOR_TUNER)

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_page_color_calibration;
static  COLOR_CALIBRATION   t_g_color_calibration_page_data;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _color_calibration_dlg_create(VOID);
static VOID _color_calibration_dlg_reset_yes_btn();
static VOID _color_calibration_dlg_reset_no_btn();
static BOOL _color_calibration_dlg_reset_back_btn(UINT32 ui4_keycode);
static INT32 _color_calibration_update_ui(VOID);
static INT32 _color_calibration_subpage_show(BOOL b_repaint);

static BOOL _is_hide_color_tuner_btn(VOID);

extern VOID set_preset_pic_mode_chg_status(BOOL b_is_chg);

//=====================================================================================================
static UINT8 _color_cali_UiFunc_convert_UiItemIdx(COLOR_CALIBRATION_BTN_TYPE_T eUiFunc)
{
    return eUiFunc;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _last_shadow_help_tip_update_position
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _last_shadow_help_tip_update_position(HANDLE_T h_item, BOOL b_repaint)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect = {0};
    GL_RECT_T           t_rect_item = {0};
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;

    if (NULL_HANDLE == h_item)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_get_coords(h_item,
                              WGL_COORDS_SCREEN,
                              &t_rect_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_top = t_rect_item.i4_bottom;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(h_last_shadow_item, NULL, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static HANDLE_T _color_cali_Get_last_item_handle(void)
{
#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
    // Last is  HANDLE_T         h_calibration_test; // Calibration Test
    return t_g_color_calibration_page_data.h_calibration_test;
#else
    // HANDLE_T         h_reset_color_tuner;
    return t_g_color_calibration_page_data.h_reset_color_tuner;
#endif
}

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
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
static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    COLOR_CALIBRATION*      pt_page_data = &t_g_color_calibration_page_data;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
        case BTN_RETURN:
        {
            MENU_LOG_ON_FAIL (menu_nav_back ());
            menu_pm_repaint();

            return MENUR_OK;
        }

        case BTN_CURSOR_DOWN:
        {
            if(_is_hide_color_tuner_btn())
            {
                //menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                //menu_pm_repaint();
                //break;
            #ifdef APP_TTS_SUPPORT
                UTF16_T w2s_str[128] = {0};
                c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_VID_WB_TUNER));
                a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
            #endif

                c_wgl_set_focus(pt_page_data->h_reset_color_tuner, WGL_SYNC_AUTO_REPAINT);

                //_last_shadow_help_tip_update_position(pt_page_data->h_reset_color_tuner,FALSE);
                _last_shadow_help_tip_update_position( _color_cali_Get_last_item_handle(), FALSE);

                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_HELP_COLOR_TUNER));//////

            }
            else
            {
            #ifdef APP_TTS_SUPPORT
                UTF16_T w2s_str[128] = {0};
                c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE));
                a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
            #endif

                c_wgl_set_focus(pt_page_data->h_color_tuner, WGL_SYNC_AUTO_REPAINT);

                //_last_shadow_help_tip_update_position(pt_page_data->h_reset_color_tuner,FALSE);
                _last_shadow_help_tip_update_position( _color_cali_Get_last_item_handle(), FALSE);

                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_HELP_COLOR_TUNER));
            }

        }
            break ;
        case BTN_CURSOR_UP:
            MENU_LOG_ON_FAIL (menu_set_focus_on_homebar(TRUE));
            break;
        default:
            break ;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
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
static INT32 _homebar_proc_fct (
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
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
            menu_nav_go_home_menu();
            return MENUR_OK ;
        case BTN_RETURN:

            menu_nav_back();


            return MENUR_OK;
        case BTN_CURSOR_DOWN :
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _color_calibration_dlg_reset_no_btn
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
static VOID _color_calibration_dlg_reset_no_btn()
{
    INT32               i4_ret = MENUR_OK;
    COLOR_CALIBRATION*      pt_page_data = &t_g_color_calibration_page_data;

    menu_page_color_calibration_dlg_hide();

    i4_ret = c_wgl_set_focus(pt_page_data->h_menu_current_focus,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
    c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_ITEM_CLR_TMP_RESET));
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif


}

/*----------------------------------------------------------------------------
 * Name: _color_calibration_dlg_reset_yes_btn
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
static VOID _color_calibration_dlg_reset_yes_btn()
{
    INT32                   i4_ret = MENUR_OK;
    COLOR_CALIBRATION*      pt_page_data = &t_g_color_calibration_page_data;
    INT16                   i2_clr_temp = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_reset_clr_tuner(i2_clr_temp);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef NEVER
    i4_ret = color_tuner_get_rgb_cfg_value();
    MENU_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */

    i4_ret = a_menu_test_patterns_turn_off();
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef NEVER
    i4_ret = a_color_tuner_update_value();
    MENU_LOG_ON_FAIL(i4_ret);

    /*update 11 point: gain num,R,G,B*/
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN));
    MENU_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_color_calibration_dlg_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->e_subpage = COLOR_CALIBRATION_SUBPAGE_MAIN;
    i4_ret = _color_calibration_subpage_show(FALSE);

    menu_pm_repaint();

    menu_pic_energy_change_sepcial_page_set_status(TRUE);
}
/*----------------------------------------------------------------------------
 * Name: _color_calibration_dlg_reset_back_btn
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
static BOOL _color_calibration_dlg_reset_back_btn(UINT32 ui4_keycode)
{
    INT32               i4_ret = MENUR_OK;
    COLOR_CALIBRATION*      pt_page_data = &t_g_color_calibration_page_data;

    if(ui4_keycode == BTN_RETURN)
    {
        menu_page_color_calibration_dlg_hide();

        i4_ret = c_wgl_set_focus(pt_page_data->h_menu_current_focus,TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_ITEM_CLR_TMP_RESET));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif

        return TRUE;
    }

    return FALSE;

}

#ifdef APP_TTS_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _color_calibration_dlg_reset_back_btn
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
static INT32 _color_calibration_dlg_reset_msg_proc(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               param1,
                    VOID*               param2)
{
    UINT32 ui4_keycode = (UINT32)param1;
    UTF16_T w2s_str[128] = {0};
    if(ui4_keycode == BTN_CURSOR_LEFT)
    {
        c_memset(w2s_str, 0, sizeof(w2s_str));
        c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_RESET_ITEM_RESET));
    }
    else if(ui4_keycode == BTN_CURSOR_RIGHT)
    {
        c_memset(w2s_str, 0, sizeof(w2s_str));
        c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_RESET_ITEM_CANCEL));
    }
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));

    return a_ui_simple_dialog_default_msg_proc(h_widget,ui4_msg,param1,param2);

}
#endif


/*----------------------------------------------------------------------------
 * Name: _color_calibration_dlg_create
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
static INT32 _color_calibration_dlg_create(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    HANDLE_T        h_parent = NULL_HANDLE;


    i4_ret = menu_pm_get_root_frm(&h_parent);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = h_parent;
    //t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct    = _color_calibration_dlg_reset_no_btn;
    //t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _color_calibration_dlg_reset_yes_btn;
#ifdef APP_TTS_SUPPORT
    t_simple_dialog_init.pf_wdgt_proc                   = _color_calibration_dlg_reset_msg_proc;
#else
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
#endif

    t_simple_dialog_init.pt_begin_offset                = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_one_btn_mode                 = FALSE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                                &pt_page_data->h_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_is_dlg_show   = FALSE;

    return MENUR_OK;

}
/*----------------------------------------------------------------------------
 * Name: menu_page_color_calibration_dlg_is_show
 *
 * Description: menu_page_color_calibration_dlg_is_show
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_color_calibration_dlg_is_show(VOID)
{
    COLOR_CALIBRATION*          pt_page_data = &t_g_color_calibration_page_data;

    return pt_page_data->b_is_dlg_show;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_color_calibration_dlg_show
 *
 * Description: menu_page_color_calibration_dlg_show
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_color_calibration_dlg_show(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    COLOR_CALIBRATION*          pt_page_data = &t_g_color_calibration_page_data;
    UTF16_T                     w2s_str[MENU_PIC_MODE_EDIT_DLG_TEXT_LEN+1] = {0};
    CHAR                        s_space[8+1] = {0};
    UTF16_T                     w2s_space[8+1] = {0};

    /* get current color temp name */
    INT16       i2_idx = 0;
    UTF16_T     w2s_asterisk[8] = {0};
    BOOL        b_is_chg = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_idx);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_get_clr_temp_chg_status(i2_idx,&b_is_chg);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(pt_page_data->w2s_clr_temp, 0, MENU_PRESET_PIC_MODE_NAME_LEN+1);
    c_uc_w2s_strncpy(pt_page_data->w2s_clr_temp, MENU_TEXT(MLM_MENU_KEY_VID_CLR_TEMP_WARM+i2_idx),(MENU_PRESET_PIC_MODE_NAME_LEN));

    if(b_is_chg)
    {
        c_uc_ps_to_w2s("*",w2s_asterisk,1);
        c_uc_w2s_strncat(pt_page_data->w2s_clr_temp,w2s_asterisk,1);
    }

    c_uc_w2s_strncat(w2s_str,MENU_TEXT(MLM_MENU_KEY_RESET_COLOR_TUNER_DLG_TXT1),c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_RESET_COLOR_TUNER_DLG_TXT1)));

    c_sprintf(s_space, " ");
    c_uc_ps_to_w2s(s_space,w2s_space,8);
    c_uc_w2s_strcat(w2s_str,w2s_space);

    c_uc_w2s_strncat(w2s_str,pt_page_data->w2s_clr_temp,c_uc_w2s_strlen(pt_page_data->w2s_clr_temp));

    c_sprintf(s_space, " ");
    c_uc_ps_to_w2s(s_space,w2s_space,8);
    c_uc_w2s_strcat(w2s_str,w2s_space);

    c_uc_w2s_strncat(w2s_str,MENU_TEXT(MLM_MENU_KEY_RESET_COLOR_TUNER_DLG_TXT2),c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_RESET_COLOR_TUNER_DLG_TXT2)));

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_page_data->h_dlg,
                                             MENU_TEXT(MLM_MENU_KEY_RESET_ITEM_RESET));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_no_text(pt_page_data->h_dlg,
                                            MENU_TEXT(MLM_MENU_KEY_RESET_ITEM_CANCEL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_yes_fct(pt_page_data->h_dlg,_color_calibration_dlg_reset_yes_btn);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_no_fct(pt_page_data->h_dlg,_color_calibration_dlg_reset_no_btn);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_other_key_cb_fct(pt_page_data->h_dlg,_color_calibration_dlg_reset_back_btn);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_text(pt_page_data->h_dlg,
                                         w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
    if(pt_page_data->h_menu_current_focus == NULL_HANDLE)
    {
        i4_ret = c_wgl_get_focus(&pt_page_data->h_menu_current_focus);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = a_ui_simple_dialog_show(pt_page_data->h_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_float(pt_page_data->h_dlg,TRUE,FALSE);
    a_ui_simple_dialog_set_focus(pt_page_data->h_dlg, TRUE);
    /*set focus to cancel*/
    a_ui_simple_dialog_set_answer(pt_page_data->h_dlg,FALSE);
    a_ui_simple_dialog_repaint(pt_page_data->h_dlg);

#ifdef APP_TTS_SUPPORT
    c_uc_w2s_strncat(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_RESET_ITEM_CANCEL),c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_RESET_ITEM_CANCEL)));
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif


    pt_page_data->b_is_dlg_show = TRUE;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_color_calibration_dlg_hide
 *
 * Description: menu_page_color_calibration_dlg_hide
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_color_calibration_dlg_hide(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

#ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
#endif

    i4_ret = a_ui_simple_dialog_hide(pt_page_data->h_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_is_dlg_show  = FALSE;
    c_wgl_float(pt_page_data->h_dlg,FALSE,FALSE);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _color_tuner_btn_proc_fct
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
static INT32 _color_tuner_btn_proc_fct(HANDLE_T  h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif

            //_last_shadow_help_tip_update_position(pt_page_data->h_reset_color_tuner,FALSE);
            _last_shadow_help_tip_update_position( _color_cali_Get_last_item_handle(), FALSE);

            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_HELP_COLOR_TUNER));
            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    /*go to color tuner page*/
                    pt_page_data->h_last_focus_item = pt_page_data->h_color_tuner;
                #if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
                    pt_page_data->bFromCaliTest = FALSE;
                #endif
                    i4_ret = menu_nav_go(ui4_g_menu_custom_page_pic_quality,NULL);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_UP:
                {
                    MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                }
                    break;

                case BTN_CURSOR_DOWN:
                {
                    //if(pt_page_data->b_is_reset_enable)
                    if(1)
                    {
                        i4_ret = c_wgl_set_focus(pt_page_data->h_wb_color_tuner,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                        menu_pm_repaint();
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
/*----------------------------------------------------------------------------
 * Name: _white_balance_color_tuner_btn_proc_fct
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
static INT32 _white_balance_color_tuner_btn_proc_fct(HANDLE_T  h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_VID_WB_TUNER));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif

            //_last_shadow_help_tip_update_position(pt_page_data->h_reset_color_tuner,FALSE);
            _last_shadow_help_tip_update_position( _color_cali_Get_last_item_handle(), FALSE);

            //menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_HELP_COLOR_TUNER));
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_HELP_WHITE_BALANCE_TUNER));
            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    /*go to wb color tuner page*/
                    pt_page_data->h_last_focus_item = pt_page_data->h_wb_color_tuner;
                    i4_ret = menu_nav_go(ui4_g_menu_white_balance_tuner_page,NULL);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_UP:
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->h_color_tuner,WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_DOWN:
                { // goto next item ...
                    if(pt_page_data->b_is_reset_enable)
                    { // goto reset_color_temp
                        i4_ret = c_wgl_set_focus(pt_page_data->h_reset_color_tuner,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                    #if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
                        // goto calibration_test
                        i4_ret = c_wgl_set_focus(pt_page_data->h_calibration_test, WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                    #else
                        menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                        menu_pm_repaint();
                    #endif
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
/*----------------------------------------------------------------------------
 * Name: _reset_color_tuner_btn_proc_fct
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
static INT32 _reset_color_tuner_btn_proc_fct(HANDLE_T    h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_ITEM_CLR_TMP_RESET));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif

            //_last_shadow_help_tip_update_position(pt_page_data->h_reset_color_tuner,FALSE);
            _last_shadow_help_tip_update_position( _color_cali_Get_last_item_handle(), FALSE);

            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_RESET_COLOR_TUNER_HELP));
            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    /*focus to color tuner after reset color tuner, because the reset color tuner item is disable*/
#ifdef APP_ZOOM_MODE_SUPPORT
                    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
#endif
                    pt_page_data->h_last_focus_item = pt_page_data->h_color_tuner;
                    i4_ret = menu_page_color_calibration_dlg_show();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_UP:
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->h_wb_color_tuner,WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_DOWN:
                {
                #if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
                    // goto calibration_test
                    i4_ret = c_wgl_set_focus(pt_page_data->h_calibration_test, WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                #else
                    menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                    menu_pm_repaint();
                #endif
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

#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
/*----------------------------------------------------------------------------
 * Name: _color_tuner_btn_proc_fct
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
static INT32 _Calibration_Test_btn_proc_fct(HANDLE_T  h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32       i4_ret = MENUR_OK;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_COLOR_CALI_TEST));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif

            //_last_shadow_help_tip_update_position(pt_page_data->h_reset_color_tuner,FALSE);
            _last_shadow_help_tip_update_position( _color_cali_Get_last_item_handle(), FALSE);

            //menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ITEM_HELP_COLOR_TUNER));
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_COLOR_CALI_TEST_TIP));

            break;
        }
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    /*go to color tuner page*/
                    //pt_page_data->h_last_focus_item = pt_page_data->h_color_tuner;
                    pt_page_data->h_last_focus_item = pt_page_data->h_calibration_test;

                #if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
                    pt_page_data->bFromCaliTest = TRUE;
                #endif

                    i4_ret = menu_nav_go(ui4_g_menu_custom_page_pic_quality,NULL);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case BTN_CURSOR_UP:
                {
                    // goto prev item ...
                    if(pt_page_data->b_is_reset_enable)
                    { // goto reset_color_temp
                        i4_ret = c_wgl_set_focus(pt_page_data->h_reset_color_tuner,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        // goto wb_tuner
                        i4_ret = c_wgl_set_focus(pt_page_data->h_wb_color_tuner,WGL_SYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                    }
                }
                    break;

                case BTN_CURSOR_DOWN:
                {
                    // No next item
                    menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                    menu_pm_repaint();
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
#endif

/*----------------------------------------------------------------------------
 * Name: _color_calibration_btn_create
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

static INT32 _color_calibration_btn_create(HANDLE_T h_parent,
                                    wgl_widget_proc_fct  pf_wdgt_proc,
                                    COLOR_CALIBRATION_BTN_TYPE_T e_type,
                                    UTF16_T*  pw2s_str,
                                    HANDLE_T* ph_widget)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_color_info = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_FONT_INFO_T     t_font_info = {0};
    INT32               i4_top = 0;
    GL_COLOR_T          t_color_txt = t_g_menu_color_white;
    GL_COLOR_T          t_color_txt_disable = { 255, {128}, {128}, {128}};


    i4_top = COLOR_CALIBRATION_BTN_H * _color_cali_UiFunc_convert_UiItemIdx(e_type);

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     COLOR_CALIBRATION_BTN_X,
                     i4_top,
                     COLOR_CALIBRATION_BTN_W,
                     COLOR_CALIBRATION_BTN_H
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

    t_inset.i4_left   = COLOR_CALIBRATION_BTN_INSET_LEFT + 8;
    t_inset.i4_right  = COLOR_CALIBRATION_BTN_INSET_RIGHT;
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

    t_font_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_font_info.ui1_custom_size = 24;

    t_font_info.e_font_style = FE_FNT_STYLE_REGULAR;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_font_info),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(pw2s_str),
                          WGL_PACK(c_uc_w2s_strlen(pw2s_str)));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _color_tuner_btn_create
 *
 * Description: color tuner item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _color_tuner_btn_create (VOID)
{
    INT32       i4_ret = MENUR_OK;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

    i4_ret = _color_calibration_btn_create(pt_page_data->h_cnt_frm,
                                        _color_tuner_btn_proc_fct,
                                        COLOR_CALIBRATION_BTN_COLOR_TUNER,
                                        MENU_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE),
                                        &pt_page_data->h_color_tuner);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _color_tuner_btn_create
 *
 * Description: color tuner item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _white_balance_tuner_btn_create (VOID)
{
    INT32       i4_ret = MENUR_OK;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

    i4_ret = _color_calibration_btn_create(pt_page_data->h_cnt_frm,
                                        _white_balance_color_tuner_btn_proc_fct,
                                        COLOR_CALIBRATION_BTN_WB_COLOR_TUNER,
                                        MENU_TEXT(MLM_MENU_KEY_VID_WB_TUNER),
                                        &pt_page_data->h_wb_color_tuner);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _reset_color_tuner_btn_create
 *
 * Description: reset color tuner item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _reset_color_tuner_btn_create (VOID)
{
    INT32       i4_ret = MENUR_OK;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

    i4_ret = _color_calibration_btn_create(pt_page_data->h_cnt_frm,
                                        _reset_color_tuner_btn_proc_fct,
                                        COLOR_CALIBRATION_BTN_RESET_COLOR_TUNER,
                                        MENU_TEXT(MLM_MENU_KEY_ITEM_CLR_TMP_RESET),
                                        &pt_page_data->h_reset_color_tuner);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Calibration test item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
static INT32 _calibration_test_btn_create (VOID)
{
    INT32       i4_ret = MENUR_OK;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

    i4_ret = _color_calibration_btn_create(pt_page_data->h_cnt_frm,
                                        //_color_tuner_btn_proc_fct,
                                        _Calibration_Test_btn_proc_fct,
                                        COLOR_CALIBRATION_BTN_CALIBRATION_TEST,
                                        MENU_TEXT(MLM_MENU_KEY_COLOR_CALI_TEST),
                                        &pt_page_data->h_calibration_test);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _color_calibration_listbox_create
 *
 * Description: _color_calibration_listbox_create
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
 static INT32 _color_calibration_listbox_create(
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
    GL_COLOR_T                  t_color_disable = { 255, {128}, {128}, {128}};

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
    t_fnt_info.ui1_custom_size = 24;

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
    t_inset.i4_left     = COLOR_CALIBRATION_BTN_INSET_LEFT + 8;
    t_inset.i4_right    = COLOR_CALIBRATION_LB_INSET_RIGHT;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = 0;
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
    t_inset.i4_right  = COLOR_CALIBRATION_LB_INSET_RIGHT;
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

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _color_calibration_info_list_create
 *
 * Description: include picture mode and color temperature info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _color_calibration_info_list_create (VOID)
{
    INT32               i4_ret = MENUR_OK;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[2];
    GL_RECT_T           t_rect;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

    c_memset(at_cols, 0, 2*sizeof(WGL_LB_COL_INIT_T));
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = COLOR_CALIBRATION_DEV_DISP_NAME_ALIGN;
    at_cols[0].ui2_max_text_len = COLOR_CALIBRATION_DEV_DISP_NAME_MAX_TEXT_LEN;
    at_cols[0].ui2_width        = COLOR_CALIBRATION_DEV_DISP_NAME_COL_WIDTH;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = COLOR_CALIBRATION_DEV_USER_NAME_ALIGN;
    at_cols[1].ui2_max_text_len = COLOR_CALIBRATION_DEV_USER_NAME_MAX_TEXT_LEN;
    at_cols[1].ui2_width        = COLOR_CALIBRATION_DEV_USER_NAME_COLUMN_WIDTH;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = COLOR_CALIBRATION_MAX_DEVICE_NUM;
    t_lb_init.ui2_elem_size     = COLOR_CALIBRATION_DEV_LIST_ELEM_HEIGHT;
    t_lb_init.ui2_elem_distance = 1;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     COLOR_CALIBRATION_DEV_LIST_X,
                     COLOR_CALIBRATION_DEV_LIST_Y,
                     COLOR_CALIBRATION_BTN_W,
                     COLOR_CALIBRATION_DEV_LIST_H);
    i4_ret = _color_calibration_listbox_create(pt_page_data->h_cnt_frm,
                                                &t_rect,
                                                NULL,
                                                &t_lb_init,
                                                NULL,
                                                &pt_page_data->h_info_list);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _color_calibration_pic_mode_show
 *
 * Description: pic mode item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _color_calibration_pic_mode_show(VOID)
{
    INT16               i2_idx = 0;
    INT32               i4_ret = MENUR_OK;;
    WGL_LB_ITEM_T       at_items[2];
    CHAR                s_pic_mode[MENU_PRESET_PIC_MODE_NAME_LEN+1] = {0};
    UTF16_T             w2s_pic_mode[MENU_PRESET_PIC_MODE_NAME_LEN+1] = {0};
    COLOR_CALIBRATION*  pt_page_data = &t_g_color_calibration_page_data;
    UTF16_T             w2s_asterisk[8] = {0};
    BOOL                b_is_chg = 0;


    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_idx);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_pic_mode, 0, MENU_PRESET_PIC_MODE_NAME_LEN+1);

    if(i2_idx < ACFG_PRE_SET_PIC_MODE_NUM)
    {
        c_uc_w2s_strncpy(w2s_pic_mode, MENU_TEXT((MLM_MENU_KEY_VID_PIC_MODE_ITEM + 1)+i2_idx),(MENU_PRESET_PIC_MODE_NAME_LEN));
        a_cfg_get_preset_pic_mode_chg_status(i2_idx,&b_is_chg);
        if(b_is_chg)
        {
            c_uc_ps_to_w2s("*",w2s_asterisk,1);
            c_uc_w2s_strncat(w2s_pic_mode,w2s_asterisk,1);
        }
    }
    else
    {
        c_memset(s_pic_mode,0,MENU_PRESET_PIC_MODE_NAME_LEN+1);
        i4_ret = a_cfg_cust_get_cust_pic_mode_name(i2_idx, s_pic_mode,MENU_PRESET_PIC_MODE_NAME_LEN);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_ps_to_w2s(s_pic_mode,w2s_pic_mode,MENU_PRESET_PIC_MODE_NAME_LEN);
        w2s_pic_mode[MENU_PRESET_PIC_MODE_NAME_LEN] = 0;
    }

    c_memset(at_items, 0, 2*sizeof(WGL_LB_ITEM_T));
    at_items[0].e_col_type = LB_COL_TYPE_TEXT;

    if(a_acfg_cust_get_video_type() == SCC_VID_PQ_HDR10 )
    {
        at_items[0].data.pw2s_text = MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HDR10_ITEM);
    }
    else if(a_acfg_cust_get_video_type() == SCC_VID_PQ_HLG )
    {
        at_items[0].data.pw2s_text = MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HLG_ITEM);
    }
    else if (a_acfg_cust_get_video_type() == SCC_VID_PQ_HDR10PLUS )
    {
        at_items[0].data.pw2s_text = MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HDR10_PLUS);
    }
    else
    {
        if (a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI )
        {
            i4_ret = c_wgl_set_visibility (pt_page_data->h_dv_icon, WGL_SW_NORMAL);
            MENU_LOG_ON_FAIL (i4_ret);

        /*
            GL_RECT_T	t_rect;
            ISO_639_LANG_T	s639_lang;
            MENU_LOG_ON_FAIL(a_cfg_get_gui_lang(s639_lang));
            if(c_strncmp(s639_lang,"spa",3) == 0 )
            {
            	t_rect.i4_left	 = CONTENT_X + 269-75;
            }
            else
            {
            	t_rect.i4_left	 = CONTENT_X + 269-60;
            }
            t_rect.i4_right = t_rect.i4_left + 233;
            t_rect.i4_top = 120;
            t_rect.i4_bottom = t_rect.i4_top + 64;
            */
            //menu_doly_vision_resize_logo(MENU_DOLBY_LOGO_POS_COLOR_CALI);

            i4_ret = c_wgl_insert(pt_page_data->h_dv_icon,
                                  NULL_HANDLE,
                                  WGL_INSERT_TOPMOST,
                                  WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            i4_ret = c_wgl_set_visibility (pt_page_data->h_dv_icon, WGL_SW_HIDE);
            MENU_LOG_ON_FAIL (i4_ret);
        }

        at_items[0].data.pw2s_text = MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE);
    }

    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_pic_mode;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_info_list,
                          WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_info_list,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _color_calibration_color_temp_show
 *
 * Description: color temperature item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _color_calibration_color_temp_show(VOID)
{
    INT16               i2_idx = 0;
    INT32               i4_ret = MENUR_OK;;
    WGL_LB_ITEM_T       at_items[2];
    COLOR_CALIBRATION*  pt_page_data = &t_g_color_calibration_page_data;
    UTF16_T             w2s_asterisk[8] = {0};
    BOOL                b_is_chg = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_idx);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_get_clr_temp_chg_status(i2_idx,&b_is_chg);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(pt_page_data->w2s_clr_temp, 0, MENU_PRESET_PIC_MODE_NAME_LEN+1);
    c_uc_w2s_strncpy(pt_page_data->w2s_clr_temp, MENU_TEXT(MLM_MENU_KEY_VID_CLR_TEMP_WARM+i2_idx),(MENU_PRESET_PIC_MODE_NAME_LEN));

    if(b_is_chg)
    {
        c_uc_ps_to_w2s("*",w2s_asterisk,1);
        c_uc_w2s_strncat(pt_page_data->w2s_clr_temp,w2s_asterisk,1);
    }

    c_memset(at_items, 0, 2*sizeof(WGL_LB_ITEM_T));
    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = MENU_TEXT(MLM_MENU_KEY_VID_CLR_TEMP);
    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = pt_page_data->w2s_clr_temp;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_info_list,
                          WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_info_list,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

#if( MENU_COLOR_CALI_ENABLE_DYNAMIC_RANGE )
static INT32 _color_calibration_dynamic_range_show(VOID)
{
    INT32               i4_ret = MENUR_OK;;
    //INT16               i2_idx = 0;
    WGL_LB_ITEM_T       at_items[2];
    COLOR_CALIBRATION*  pt_page_data = &t_g_color_calibration_page_data;

#define MENU_COLOR_CALI_DYNAMIC_RANGE_SEL_LEN   32
    CHAR                acVideoTypeText[MENU_COLOR_CALI_DYNAMIC_RANGE_SEL_LEN] = {0};
    UTF16_T             w2s_VideoTypeText[MENU_COLOR_CALI_DYNAMIC_RANGE_SEL_LEN] = {0};

    c_memset(at_items, 0, 2*sizeof(WGL_LB_ITEM_T));


    // Get HDR status...
    UINT8 u8VideoType = a_acfg_cust_get_video_type();

    // Get Dynamic range string...
    switch(u8VideoType)
    {
        case SCC_VID_PQ_HDR10:
        case SCC_VID_PQ_HDR10PLUS:
            c_strcpy( acVideoTypeText, "HDR10/HDR10+");
            break;
        case SCC_VID_PQ_HLG:
            c_strcpy( acVideoTypeText, "HLG");
            break;
        case SCC_VID_PQ_DOVI:
            c_strcpy( acVideoTypeText, "Dolby Vision");
            break;
        default: // SDR
            c_strcpy( acVideoTypeText, "SDR");
            break;
    }

    // Convert to UTF16_T...
    c_uc_ps_to_w2s( acVideoTypeText, w2s_VideoTypeText, MENU_COLOR_CALI_DYNAMIC_RANGE_SEL_LEN-1);
    w2s_VideoTypeText[MENU_COLOR_CALI_DYNAMIC_RANGE_SEL_LEN-1] = 0;

    // Left text="Dynamic Range"
    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = MENU_TEXT(MLM_MENU_KEY_VID_DYNAMIC_RANGE);

    // Right text="SDR/HDR10/HDR10+/HLG/DolbyVision
    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_VideoTypeText;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_info_list,
                          WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_info_list,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
#endif

static BOOL _is_hide_color_tuner_btn(VOID)
{
    INT32                     i4_ret = 0;
    VSH_SRC_RESOLUTION_INFO_T t_res;
    ISL_REC_T                 t_isl_rec;
    TV_WIN_ID_T               t_win_id = TV_WIN_ID_MAIN;

    c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    i4_ret = c_svctx_get_video_src_resolution(menu_get_crnt_svctx(),&t_res);
    MENU_LOG_ON_FAIL(i4_ret);

    a_tv_get_focus_win(&t_win_id);
    a_tv_get_isl_rec_by_win_id(t_win_id,&t_isl_rec);

    if ((DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
        &&(t_res.e_timing_type == VSH_SRC_TIMING_GRAPHIC))  /* pc timing*/
    {
        DBG_LOG_PRINT(("[MENU][Color Tyner][%s %d] it is HDMI pc timing shoould not show this item!!\n",__FUNCTION__,__LINE__));
        return TRUE;

    }
    return FALSE;
}


/*----------------------------------------------------------------------------
 * Name: _color_calibration_btn_item_show
 *
 * Description: color tuner && reset color tuner
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _color_calibration_btn_item_show(VOID)
{
    INT32               i4_ret = MENUR_OK;;
    COLOR_CALIBRATION*  pt_page_data = &t_g_color_calibration_page_data;
    INT16               i2_clr_temp = 0;
    BOOL                b_is_chg = FALSE;
    BOOL                b_btn_pushed = FALSE;
    //BOOL                b_is_lock_status = FALSE;
    UINT32              ui4_state = 0;
    GL_RECT_T   t_rect = {0};

    UINT8 u8ItemIdx_ColorTuner = 0;
    UINT8 u8ItemIdx_WhiteBalance = 0;
    UINT8 u8ItemIdx_ResetColorTemp = 0;

#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
    UINT8 u8ItemIdx_CaliTest = 0;
#endif


    //DBG_LOG_PRINT(("[MENU]{%s: %s: %d}\n", __FILE__, __FUNCTION__,__LINE__));

    BOOL b_is_hide_color_tuner_btn = _is_hide_color_tuner_btn();
    DBG_LOG_PRINT(("[MENU]{%s: %s: %d} _is_hide_color_tuner_btn() => %d\n", __FILE__, __FUNCTION__,__LINE__, b_is_hide_color_tuner_btn));


    if( b_is_hide_color_tuner_btn )
    {
        #if 0
        SET_RECT_BY_SIZE(&t_rect,
                     COLOR_CALIBRATION_BTN_X,
                     COLOR_CALIBRATION_BTN_H*2,
                     COLOR_CALIBRATION_BTN_W,
                     COLOR_CALIBRATION_BTN_H);
        i4_ret = c_wgl_move(pt_page_data->h_wb_color_tuner,&t_rect,WGL_ASYNC_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_page_data->h_wb_color_tuner,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_VID_WB_TUNER)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_VID_WB_TUNER))));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_page_data->h_wb_color_tuner,
                                      WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
        #endif


        // Reset color tuner
        u8ItemIdx_ResetColorTemp = MENU_COLOR_CALI_COLOR_TUNER_ITEM_IDX; // 3
        DBG_LOG_PRINT(("[MENU]{%s: %s: %d} u8ItemIdx_ResetColorTemp:%d\n", __FILE__, __FUNCTION__,__LINE__, u8ItemIdx_ResetColorTemp));

        SET_RECT_BY_SIZE(&t_rect,
                     COLOR_CALIBRATION_BTN_X,
                     COLOR_CALIBRATION_BTN_H*u8ItemIdx_ResetColorTemp, //COLOR_CALIBRATION_BTN_H*2,
                     COLOR_CALIBRATION_BTN_W,
                     COLOR_CALIBRATION_BTN_H);
        i4_ret = c_wgl_move(pt_page_data->h_reset_color_tuner,&t_rect,WGL_ASYNC_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_page_data->h_reset_color_tuner,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_ITEM_CLR_TMP_RESET)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_ITEM_CLR_TMP_RESET))));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_page_data->h_reset_color_tuner, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_enable(pt_page_data->h_reset_color_tuner,FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
        pt_page_data->b_is_reset_enable = FALSE;


    #if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
        // Calibration Test
        u8ItemIdx_CaliTest = u8ItemIdx_ResetColorTemp + 1; // 6 or 4
        DBG_LOG_PRINT(("[MENU]{%s: %s: %d} u8ItemIdx_ResetColorTemp:%d, u8ItemIdx_CaliTest:%d\n", __FILE__, __FUNCTION__,__LINE__, u8ItemIdx_ResetColorTemp, u8ItemIdx_CaliTest));

        // Calibration Test: Position
        SET_RECT_BY_SIZE(&t_rect,
                     COLOR_CALIBRATION_BTN_X,
                     COLOR_CALIBRATION_BTN_H*u8ItemIdx_CaliTest, //COLOR_CALIBRATION_BTN_H*2,
                     COLOR_CALIBRATION_BTN_W,
                     COLOR_CALIBRATION_BTN_H);
        i4_ret = c_wgl_move(pt_page_data->h_calibration_test,&t_rect,WGL_ASYNC_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        // Calibration Test: text
        i4_ret = c_wgl_do_cmd(pt_page_data->h_calibration_test,
                              WGL_CMD_BTN_SET_TEXT,
                              WGL_PACK(MENU_TEXT(MLM_MENU_KEY_COLOR_CALI_TEST)),
                              WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_COLOR_CALI_TEST))));
        MENU_LOG_ON_FAIL(i4_ret);

        // Calibration Test: visible
        i4_ret = c_wgl_set_visibility(pt_page_data->h_calibration_test, WGL_SW_NORMAL );
        MENU_LOG_ON_FAIL(i4_ret);

        // Calibration Test: Enable
        i4_ret = c_wgl_enable(pt_page_data->h_calibration_test, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    #endif

        return i4_ret;
    }


    // Color Tuner
    u8ItemIdx_ColorTuner = MENU_COLOR_CALI_COLOR_TUNER_ITEM_IDX; // 3

    // White Balance
    u8ItemIdx_WhiteBalance = u8ItemIdx_ColorTuner + 1; // 4

    // Reset color temp
    u8ItemIdx_ResetColorTemp = u8ItemIdx_WhiteBalance + 1; // 5
    DBG_LOG_PRINT(("[MENU]{%s: %s: %d} u8ItemIdx_ResetColorTemp:%d\n", __FILE__, __FUNCTION__,__LINE__, u8ItemIdx_ResetColorTemp));

#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
    // Calibration Test
    u8ItemIdx_CaliTest = u8ItemIdx_ResetColorTemp + 1; // 6 or 4
    DBG_LOG_PRINT(("[MENU]{%s: %s: %d} u8ItemIdx_ResetColorTemp:%d, u8ItemIdx_CaliTest:%d\n", __FILE__, __FUNCTION__,__LINE__, u8ItemIdx_ResetColorTemp, u8ItemIdx_CaliTest));
#endif


    // White Balance Tuner ...
    if( !b_is_hide_color_tuner_btn ) // Need to show "White Balance Tuner"
    {
        // White Balance Tuner: Position
        SET_RECT_BY_SIZE(&t_rect,
                     COLOR_CALIBRATION_BTN_X,
                     COLOR_CALIBRATION_BTN_H*u8ItemIdx_WhiteBalance, //COLOR_CALIBRATION_BTN_H*3,
                     COLOR_CALIBRATION_BTN_W,
                     COLOR_CALIBRATION_BTN_H);
        i4_ret = c_wgl_move(pt_page_data->h_wb_color_tuner,&t_rect,WGL_ASYNC_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_page_data->h_wb_color_tuner,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_VID_WB_TUNER)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_VID_WB_TUNER))));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_page_data->h_wb_color_tuner,
                                      WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }


    // Color Tuner
    if( !b_is_hide_color_tuner_btn )
    {
        // Color Tuner: text
        i4_ret = c_wgl_do_cmd(pt_page_data->h_color_tuner,
                              WGL_CMD_BTN_SET_TEXT,
                              WGL_PACK(MENU_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE)),
                              WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE))));
        MENU_LOG_ON_FAIL(i4_ret);

        // Color Tuner: visible
        //i4_ret = c_wgl_set_visibility(pt_page_data->h_color_tuner, b_is_hide_color_tuner_btn ? WGL_SW_HIDE : WGL_SW_NORMAL);
        //CID: 4899995 , "b_is_hide_color_tuner_btn" must be equal 0

        i4_ret = c_wgl_set_visibility(pt_page_data->h_color_tuner, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    // Reset color tuner
    {
        // Reset color tuner: Position
        SET_RECT_BY_SIZE(&t_rect,
                     COLOR_CALIBRATION_BTN_X,
                     COLOR_CALIBRATION_BTN_H*u8ItemIdx_ResetColorTemp,//COLOR_CALIBRATION_BTN_H*4,
                     COLOR_CALIBRATION_BTN_W,
                     COLOR_CALIBRATION_BTN_H);
        i4_ret = c_wgl_move(pt_page_data->h_reset_color_tuner,&t_rect,WGL_ASYNC_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_page_data->h_reset_color_tuner,
                              WGL_CMD_BTN_SET_TEXT,
                              WGL_PACK(MENU_TEXT(MLM_MENU_KEY_ITEM_CLR_TMP_RESET)),
                              WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_ITEM_CLR_TMP_RESET))));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_page_data->h_reset_color_tuner,
                                      WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }


#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
    // Calibration Test
    {
        // Calibration Test: Position
        SET_RECT_BY_SIZE(&t_rect,
                     COLOR_CALIBRATION_BTN_X,
                     COLOR_CALIBRATION_BTN_H*u8ItemIdx_CaliTest, //COLOR_CALIBRATION_BTN_H*2,
                     COLOR_CALIBRATION_BTN_W,
                     COLOR_CALIBRATION_BTN_H);
        i4_ret = c_wgl_move(pt_page_data->h_calibration_test,&t_rect,WGL_ASYNC_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        // Calibration Test: text
        i4_ret = c_wgl_do_cmd(pt_page_data->h_calibration_test,
                              WGL_CMD_BTN_SET_TEXT,
                              WGL_PACK(MENU_TEXT(MLM_MENU_KEY_COLOR_CALI_TEST)),
                              WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_COLOR_CALI_TEST))));
        MENU_LOG_ON_FAIL(i4_ret);

        // Calibration Test: visible
        i4_ret = c_wgl_set_visibility(pt_page_data->h_calibration_test, WGL_SW_NORMAL );
        MENU_LOG_ON_FAIL(i4_ret);

        // Calibration Test: Enable
        i4_ret = c_wgl_enable(pt_page_data->h_calibration_test, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif


    if(!a_menu_is_color_tuner_enable())
    {
        i4_ret = c_wgl_do_cmd(pt_page_data->h_color_tuner,
                WGL_CMD_BTN_GET_PUSHED,
                WGL_PACK(&b_btn_pushed),
                WGL_PACK(NULL));
        MENU_LOG_ON_FAIL(i4_ret);

        if(b_btn_pushed)
        {
            i4_ret = c_wgl_do_cmd(pt_page_data->h_color_tuner,
                                    WGL_CMD_BTN_SET_PUSHED,
                                    WGL_PACK(FALSE),
                                    WGL_PACK(NULL));
            MENU_LOG_ON_FAIL(i4_ret);
        }

        /*set focus to backbar before disable color tuner item when the color tuner item is focused*/
        c_wgl_get_state(pt_page_data->h_color_tuner, &ui4_state);

        if(ui4_state & WGL_STATE_FOCUSED)
        {
            MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
        }
        i4_ret = c_wgl_enable(pt_page_data->h_color_tuner,FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_page_data->h_reset_color_tuner,
                WGL_CMD_BTN_GET_PUSHED,
                WGL_PACK(&b_btn_pushed),
                WGL_PACK(NULL));
        MENU_LOG_ON_FAIL(i4_ret);

        if(b_btn_pushed)
        {
            i4_ret = c_wgl_do_cmd(pt_page_data->h_reset_color_tuner,
                                    WGL_CMD_BTN_SET_PUSHED,
                                    WGL_PACK(FALSE),
                                    WGL_PACK(NULL));
            MENU_LOG_ON_FAIL(i4_ret);
        }

        /*set focus to backbar before disable reset color tuner item when the reset color tuner item is focused*/
        c_wgl_get_state(pt_page_data->h_reset_color_tuner, &ui4_state);

        if(ui4_state & WGL_STATE_FOCUSED)
        {
            MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
        }
        i4_ret = c_wgl_enable(pt_page_data->h_reset_color_tuner,FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
        pt_page_data->b_is_reset_enable = FALSE;
    }
    else
    {
        i4_ret = c_wgl_enable(pt_page_data->h_color_tuner,TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    #if 0 /* lock picture mode ,preset picture mode reset color tuner item can be available fix DTV00819099 */
        i4_ret = a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);
        MENU_LOG_ON_FAIL(i4_ret);
        if(b_is_lock_status)
        {
            i4_ret = c_wgl_do_cmd(pt_page_data->h_reset_color_tuner,
                    WGL_CMD_BTN_GET_PUSHED,
                    WGL_PACK(&b_btn_pushed),
                    WGL_PACK(NULL));
            MENU_LOG_ON_FAIL(i4_ret);

            if(b_btn_pushed)
            {
                i4_ret = c_wgl_do_cmd(pt_page_data->h_reset_color_tuner,
                                        WGL_CMD_BTN_SET_PUSHED,
                                        WGL_PACK(FALSE),
                                        WGL_PACK(NULL));
                MENU_LOG_ON_FAIL(i4_ret);
            }
            i4_ret = c_wgl_enable(pt_page_data->h_reset_color_tuner,FALSE);
        }
        else
    #endif
        {
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_get_clr_temp_chg_status(i2_clr_temp,&b_is_chg);
            MENU_LOG_ON_FAIL(i4_ret);

            if(b_is_chg)
            {
                i4_ret = c_wgl_enable(pt_page_data->h_reset_color_tuner,TRUE);
                pt_page_data->b_is_reset_enable = TRUE;
            }
            else
            {

                i4_ret = c_wgl_do_cmd(pt_page_data->h_reset_color_tuner,
                        WGL_CMD_BTN_GET_PUSHED,
                        WGL_PACK(&b_btn_pushed),
                        WGL_PACK(NULL));
                MENU_LOG_ON_FAIL(i4_ret);

                if(b_btn_pushed)
                {
                    i4_ret = c_wgl_do_cmd(pt_page_data->h_reset_color_tuner,
                                            WGL_CMD_BTN_SET_PUSHED,
                                            WGL_PACK(FALSE),
                                            WGL_PACK(NULL));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                i4_ret = c_wgl_enable(pt_page_data->h_reset_color_tuner,FALSE);
                pt_page_data->b_is_reset_enable = FALSE;
            }
        }
    }


#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
    c_uc_w2s_strcpy(w2s_str,MENU_TTS_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE));
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif


    return i4_ret;
}
static VOID _color_calibration_refresh_ui_for_reset_ap(VOID *p1, VOID *p2, VOID *p3)
{
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;
    UINT8               ui1_status = ICL_PQ_CHANGE_NOTHING;
    INT32               i4_ret;
    INT16               i2_clr_temp = 0;
    BOOL                b_is_chg = FALSE;
    i4_ret = a_icl_custom_get_pq_chg_status(&ui1_status);
    if (ICLR_OK != i4_ret)
    {
        return ;
    }
    if(!pt_page_data->b_this_page_show)
    {
        return ;
    }
    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_get_clr_temp_chg_status(i2_clr_temp,&b_is_chg);
    MENU_LOG_ON_FAIL(i4_ret);
    if (((!b_is_chg)&&(pt_page_data->b_is_reset_enable))||
        ((b_is_chg)&&(!pt_page_data->b_is_reset_enable)))
    {
        if(!b_is_chg)
        {
            c_wgl_set_focus(pt_page_data->h_color_tuner,TRUE);
        }
        _color_calibration_update_ui();
        menu_pm_repaint();
   }
}

static INT32 _color_calibration_pq_change_icl_nfy_cb(UINT16    ui2_nfy_id,
                                              VOID*     pv_tag,
                                              ICL_NOTIFY_DATA_T* pt_notify_data)
{
    menu_request_context_switch(_color_calibration_refresh_ui_for_reset_ap, NULL, NULL, NULL);
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _color_calibration_dv_icon_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _color_calibration_dv_icon_create(VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;


#if MENU_DOLBY_LOGO_TEST_NEW_SIZE
    t_rect.i4_left   = COLOR_CALIBRATION_DV_ICON_X;
    t_rect.i4_right  = t_rect.i4_left + 108;
    t_rect.i4_top    = COLOR_CALIBRATION_DV_ICON_Y;
    t_rect.i4_bottom = t_rect.i4_top + 45;
#else
    t_rect.i4_left   = COLOR_CALIBRATION_DV_ICON_X;
    t_rect.i4_right  = t_rect.i4_left + 116;
    t_rect.i4_top    = COLOR_CALIBRATION_DV_ICON_Y;
    t_rect.i4_bottom = t_rect.i4_top + 43;
#endif

    i4_ret = c_wgl_create_widget (pt_page_data->h_cnt_frm,
                                HT_WGL_WIDGET_ICON,
                                WGL_CONTENT_ICON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID *)WGL_STL_GL_NO_BK,
                                NULL,
                                &pt_page_data->h_dv_icon);
    MENU_LOG_ON_FAIL (i4_ret);

    /* set icon image buffer */

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_dolby_vision_icon;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_dolby_vision_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_dolby_vision_icon;

    i4_ret = c_wgl_do_cmd (pt_page_data->h_dv_icon,
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK(WGL_IMG_FG),
                                WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL (i4_ret);

    i4_ret = c_wgl_set_visibility (pt_page_data->h_dv_icon, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL (i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret=  MENUR_OK;
    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

    c_memset(&t_g_color_calibration_page_data, 0, sizeof(COLOR_CALIBRATION));

    pt_page_data->ui4_page_id = ui4_page_id;
    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page_data->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    /*picture mode && color temperature*/
    i4_ret = _color_calibration_info_list_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /* dv icon */
    i4_ret = _color_calibration_dv_icon_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /*color turner item*/
    i4_ret = _color_tuner_btn_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /*white balance tuner item*/
    i4_ret = _white_balance_tuner_btn_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /*reset color tuner item*/
    i4_ret = _reset_color_tuner_btn_create();
    MENU_LOG_ON_FAIL(i4_ret);

#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
    /* calibration test */
    i4_ret = _calibration_test_btn_create();
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = _color_calibration_dlg_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_finish = TRUE;
    i4_ret = a_icl_notify_reg(ICL_GRPID_PQ_CHANGE_STATUS,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _color_calibration_pq_change_icl_nfy_cb,
                              &pt_page_data->ui2_icl_nfy_id_pic_reset);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _color_calibration_subpage_show
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
static INT32 _color_calibration_subpage_show(BOOL b_repaint)
{
    INT32               i4_ret = MENUR_OK;
    COLOR_CALIBRATION*  pt_page_data = &t_g_color_calibration_page_data;

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    menu_set_help_tip_flag(TRUE);

    switch (pt_page_data->e_subpage)
    {
        case COLOR_CALIBRATION_SUBPAGE_MAIN:
        {
            i4_ret = _color_calibration_update_ui();
            MENU_LOG_ON_FAIL(i4_ret);

            if(_is_hide_color_tuner_btn())
            {
                MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                break;
            }

            if(!a_menu_is_color_tuner_enable())
            {
                MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
            }
            else
            {
                if(pt_page_data->h_last_focus_item != 0)
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->h_last_focus_item,
                                             WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->h_color_tuner,
                                             WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

            }

        }
            break;

        default:
            break;
    }

    if (b_repaint)
    {
        i4_ret = menu_pm_repaint();
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: update_color_calibration_ui
 *
 * Description: update the ui when the resolution is change (receive the msg: SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE)
 *              the color tuner/reset color tuner items display depend on the resolution.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern INT32 update_color_calibration_ui(VOID)
{
    INT32                   i4_ret = MENUR_OK;
    UINT32                  ui4_page_id = 0;
    COLOR_CALIBRATION*      pt_page_data = &t_g_color_calibration_page_data;

    i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
    MENU_LOG_ON_FAIL(i4_ret);

    if(ui4_page_id == ui4_g_menu_custom_page_color_calibration)
    {
        i4_ret = _color_calibration_update_ui();
        MENU_LOG_ON_FAIL(i4_ret);

        if(_is_hide_color_tuner_btn())
        {
            MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
            return MENUR_OK;
        }

        if(!a_menu_is_color_tuner_enable())
        {
            MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
        }
        else
        {
            if(pt_page_data->h_last_focus_item != 0)
            {
                i4_ret = c_wgl_set_focus(pt_page_data->h_last_focus_item,
                                         WGL_NO_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret = c_wgl_set_focus(pt_page_data->h_color_tuner,
                                         WGL_NO_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }

        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _color_calibration_update_ui
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
static INT32 _color_calibration_update_ui(VOID)
{
    INT32                   i4_ret = MENUR_OK;
    GL_RECT_T               t_rect = {0};
    HANDLE_T                h_last_shadow_item = NULL_HANDLE;
    COLOR_CALIBRATION*      pt_page_data = &t_g_color_calibration_page_data;

    /* set visibility */
    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_main_set_title(MLM_MENU_KEY_COLOR_CALIBRATION_TITLE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_info_list,
                          WGL_CMD_LB_DEL_ALL, NULL, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /*the pic mode and color temp is static and not selectable*/
    i4_ret = c_wgl_enable(pt_page_data->h_info_list,FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    /* remove pic mode & color temp item */
    i4_ret = _color_calibration_pic_mode_show();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _color_calibration_color_temp_show();
    MENU_LOG_ON_FAIL(i4_ret);

#if( MENU_COLOR_CALI_ENABLE_DYNAMIC_RANGE )
    // dynamic_range
    i4_ret = _color_calibration_dynamic_range_show();
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = _color_calibration_btn_item_show();
    MENU_LOG_ON_FAIL(i4_ret);

    /*Adjust last shadow position*/
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = MENU_ITEM_V_HEIGHT * 4+ CONTENT_Y;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32                   i4_ret;
    COLOR_CALIBRATION*      pt_page_data = &t_g_color_calibration_page_data;

    /* shit. */
    pt_page_data->b_finish = TRUE;
    pt_page_data->b_this_page_show = TRUE;
    pt_page_data->e_subpage = COLOR_CALIBRATION_SUBPAGE_MAIN;
    i4_ret = _color_calibration_subpage_show(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32   i4_ret = MENUR_OK;

    COLOR_CALIBRATION* pt_page_data = &t_g_color_calibration_page_data;

    if(pt_page_data->b_is_dlg_show)
    {
        i4_ret = menu_page_color_calibration_dlg_hide();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if(pt_page_data->b_this_page_show == FALSE)
    {
        return MENUR_OK;
    }
    menu_help_tip_keytip_show(TRUE);

    pt_page_data->b_this_page_show = FALSE;

    pt_page_data->b_finish = TRUE;
    pt_page_data->h_menu_current_focus = NULL_HANDLE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    //INT32   i4_ret = MENUR_OK;

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    //INT32   i4_ret = MENUR_OK;

    /* set callback function for backbar */
    menu_set_backbar_proc(NULL) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    /* stop animation */
    menu_page_animation_stop();

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    //INT32   i4_ret = MENUR_OK;

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_color_calibration_init(VOID)
{
    t_g_menu_page_color_calibration.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_color_calibration.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_color_calibration.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_color_calibration.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_color_calibration.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_color_calibration.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_color_calibration.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
extern BOOL menu_page_color_calibration_is_CaliTestMode(void)
{
    return  t_g_color_calibration_page_data.bFromCaliTest;
}
#endif


