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
 * $RCSfile: menu_page_mngr.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/13 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: ba03d0b5862ac3db66b17c6a36ddaf30 $
 *
 * Description:
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_lnk_list.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_wgl_image.h"
#include "c_wgl_anim.h"
#include "c_fe.h"
#include "c_version.h"

#include "amb/a_amb.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "app_util/help_tip/a_help_tip.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_page_tree.h"
#include "menu2/menu_help_lst.h"
#include "menu2/menu_page_ex/menu_page_ex.h"
#include "res/menu2/menu_custom.h"
#include "res/menu2/menu_cust_define.h"
#include "menu2/menu_util2.h"


#include "u_wgl_rect.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#endif

#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif

#ifdef APP_NAV_CUSTOM_COMP_ID
#include "res/nav/nav_custom_comp_id.h"
#endif

#include "nav/a_navigator.h"
#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_custom_comp_id.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "menu2/menu_device/menu_device.h"
#include "nav/scrn_blank/a_nav_scrn_blank.h"

#include "menu2/menu_dbg.h"
#include "res/wdk/digit_pad/digit_images.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
----------------------------------------------------------------------------*/

#define DEBUG_PM(x)     //x


#ifndef MENU_PM_HIDE_DELAY
    #define MENU_PM_HIDE_DELAY     0
#endif

#ifndef MENU_PM_HIDE_DELAY2
    #define MENU_PM_HIDE_DELAY2    MENU_PM_HIDE_DELAY
#endif

#ifndef MENU_PM_OSD_ALPHA
    #define MENU_PM_OSD_ALPHA       255
#endif

/* disable fade-in, fade-out */
#ifdef  MENU_PM_FADE_DELAY
    #undef  MENU_PM_FADE_DELAY
    #define MENU_PM_FADE_DELAY  0
#endif
#ifdef  MENU_PM_FADE_STEP
    #undef  MENU_PM_FADE_STEP
    #define MENU_PM_FADE_STEP   1
#endif

#ifndef MENU_PM_TAB_ALIGNMENT
    #define MENU_PM_TAB_ALIGNMENT   WGL_AS_CENTER_CENTER
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
----------------------------------------------------------------------------*/
#define MENU_PM_MAX_TAB_NUM     8
#define MENU_PM_MAX_NAV_SIZE    8
#define HELP_TIP_BACK_KEY_CB_MAX_NR E_HELP_TIP_CB_PAGE_LAST

#define HELP_BUCKET_NUM     4

typedef enum
{
    PM_COND_NOT_INIT,
    PM_COND_HIDE,
    PM_COND_TAB,
    PM_COND_PAGE
}   PM_COND_T;

typedef DLIST_T(_PM_PAGE_ENTRY_T) PM_PAGE_LIST_T;

typedef struct _PM_PAGE_ENTRY_T
{
    DLIST_ENTRY_T(_PM_PAGE_ENTRY_T) t_link;
    UINT32                          ui4_page_id;
    MENU_PAGE_FCT_TBL_T             t_fct_tbl;
    MENU_PAGE_STATE_T               e_state;
    /* cnt frame */
    HANDLE_T                        h_cnt_frm;
    wgl_widget_proc_fct             pf_wdgt_proc;
    /* page data */
    VOID*                           pv_page_data;
} PM_PAGE_ENTRY_T;

typedef struct _PM_TAB_ENTRY_T
{
    struct _PM_PAGE_ENTRY_T*  pt_page;
    HANDLE_T                  h_btn;
    BOOL                      b_enabled;     /* Enable Support */
    BOOL                      b_hidden;      /* Hidden Support */
    GL_RECT_T                 t_rect;        /* Keep the current widget position */
} PM_TAB_ENTRY_T;

typedef struct __HELP_TIP_CB_DATA
{
    UINT16          ui2_reg_nr;
    help_tip_cb     ap_fct[HELP_TIP_BACK_KEY_CB_MAX_NR];
    UINT32          aui4_page_id[HELP_TIP_BACK_KEY_CB_MAX_NR];
}_HELP_TIP_CB_DATA;

static _HELP_TIP_CB_DATA    _help_tip_back_key_cb;

#define PM_PAGEID_NONE      ((UINT32)0xFFFFFFFF)
#define PM_TABIDX_NONE      ((UINT16)0xFFFF)
#define MENU_TITLE_SCRL_TIMER   (1000)
#define MENU_TITLE_SCRL_LEN     (31)            // if title length > MENU_TITLE_SCRL_LEN, should scroll
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
UINT16                  ui2_g_menu_curr_lang = 0;

BOOL                    b_g_menu_lazy_init_support = FALSE;

/* font */
static CHAR             s_font_name[32] = "";

/* canvas */
static HANDLE_T         h_canvas;
static UINT32           ui4_canvas_width;
static UINT32           ui4_canvas_height;

/* help tip */
static HANDLE_T         h_menu_help_tip;
static HANDLE_T         h_last_shadow_item ;

static HANDLE_T         h_energy_start_icon_img;
static BOOL             b_need_energy_start;

#ifdef APP_HDR_SUPPORT
/*Dolby Vision Logo*/
static HANDLE_T         h_doly_vision_icon_img;
static BOOL             b_doly_vision_icon_img_visible;
#endif

/* root */
static HANDLE_T         h_frm_root;

/* other components */
static HANDLE_T         h_frm_tb;

/* homebar & backbar */
static HANDLE_T         h_homebar_frm;
static HANDLE_T         h_backbar_frm;

static HANDLE_T         h_backbar_txt;
static HANDLE_T         h_backbar_arrow;

/* used for title */
static HANDLE_T         h_txt_title;
/*Fake to hide Homebar icon*/
static HANDLE_T         h_main_title_txt;
static UINT16           ui2_msg_id_title;

/* used for factory page */
UINT32           ui4_page_factory;

/* the current scan type */
static MENU_SCAN_TYPE_T e_scan_type = MENU_SCAN_TYPE_UNKNOWN;

/* main */
static HANDLE_T         h_frm_main;
static INT32            i4_osd_width;
static INT32            i4_osd_height;
static INT32            i4_osd_hoffset;
static INT32            i4_osd_voffset;
static UINT8            ui1_osd_alpha = MENU_PM_OSD_ALPHA;
static UINT32           ui4_hide_delay1;
static UINT32           ui4_hide_delay2;
static GL_HPLANE_T      h_plane;
static BOOL             b_using_fading = FALSE;

/* page manager condition */
static PM_COND_T        e_pm_cond = PM_COND_NOT_INIT;
static BOOL             b_one_tab_mode;

/* tabs */
static BOOL             b_tab_vert;
static PM_TAB_ENTRY_T   at_tabs[MENU_PM_MAX_TAB_NUM];
static UINT16           ui2_tab_num;
static UINT16           ui2_tab_crnt;   /* current showing tab */

/* pages */
static PM_PAGE_LIST_T   t_page_list;
static UINT32           ui4_page_num;
static UINT32           ui4_page_crnt;  /*current showing page */

/* navigation stack. This stack is only used in PM_COND_PAGE state.
   e_page_cond == PM_COND_TAB                    => focus on tab
   e_page_cond == PM_COND_PAGE && stack_top == 0 => focus on top-most page
   e_page_cond == PM_COND_PAGE && stack_top != 0 => focus on not-top-most page
*/
static UINT32           aui4_nav_stack[MENU_PM_MAX_NAV_SIZE];
static UINT16           ui2_nav_stack_top;

/* Keep the latest state before hiding. If the menu show by menu_show_with_latest_state().
   it will use these state keeper to recover the latest state of menu */
static UINT16           ui2_nav_stack_top_keep;
static UINT16           ui2_tab_crnt_keep;
static UINT32           ui4_page_crnt_keep;
static PM_COND_T        e_pm_cond_keep;

/* Used for resume show. */
static UINT32           aui4_resume_show_pages[MENU_PM_MAX_NAV_SIZE];
static UINT16           ui2_resume_show_page_num;
static UINT16           ui2_resume_show_tab_idx;
static BOOL             b_is_resume_show;

/* Page Event Listener */
static menu_page_event_listener_fct pf_page_event_listener_fct = NULL;

/* Homebar & Backbar parameters */
static HANDLE_T         h_backbar_first_widget = NULL_HANDLE;
static HANDLE_T         h_backbar_last_widget = NULL_HANDLE;

/**/
static BOOL             b_hide_common_page = TRUE;

static GL_RECT_T        t_g_rect_out = {0};
static GL_RECT_T        t_g_rect_in = {0};

static BOOL             b_ver_show_curr;
static UINT16           ui2_ver_key_list_ptr;
static UINT32           aui4_ver_key_list[VERSION_KEY_LIST_SIZE];
static UINT32           aui4_ver_key_list_pattern[VERSION_KEY_LIST_SIZE] = VERSION_KEY_LIST;
static BOOL             b_hide_main_menu_in_page_switch = TRUE;
static BOOL             b_hot_key_page_with_animation = FALSE;
static UTF16_T          w2s_help_txt[HELP_TIP_LAST_TXT_LEN+1] = {0};
static BOOL             b_show_help_text = TRUE;
static BOOL             b_show_energy_start_icon = TRUE;
#ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT
static BOOL g_help_tip_blue_button_enable_status = FALSE;
#endif

#ifdef APP_TTS_SUPPORT
static UINT16   ui2_help_tip_mlm_key = 0;
static HANDLE_T h_timer_tts = NULL_HANDLE;
static UTF16_T *p_w2s_tts_str = NULL;
static INT32    i4_tts_play_id = 0;
static VOID  _menu_help_tip_tts_play_timer_cb (HANDLE_T  pt_tm_handle, VOID*     pv_tag);
static INT32 _menu_help_tip_stop_tts_play(VOID);
static INT32 _menu_help_tip_tts_play(UTF16_T *p_w2s_str);
#endif
static BOOL             b_is_nav_go = FALSE;
static UINT32           i4_scrl_title_offset = 0;
static UTF16_T          w2s_text_title[128] = {0};
static HANDLE_T         h_srcl_title_timer;

static wgl_widget_proc_fct pf_backbar_fct = NULL;

static INT32 _init_title_txt(
    HANDLE_T    h_parent,
    HANDLE_T*   ph_widget);
INT32 menu_scrl_title_reset(UTF16_T* w2s_new_title);

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _menu_set_show_enger_start_by_mode_name
 *
 * Description:
 *10 are energy star compliant:
    D24f-F1
    D32f-F1
    D39f-F1
    D40f-F1
    D43f-F1
    D43f-F2
    D43fx-F4
    D43-F1
    D50f-F1
    D50-F1
    5 do not support energy star:
    D32h-F0
    D32h-F1
    D32h-F4
    D39f-F0
    D48f-F0
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID _menu_set_show_enger_start_by_mode_name(VOID)
{
    CHAR s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};
    a_cfg_custom_get_model_name(s_model_name);
    DBG_INFO(("[ACFG]mode name: %s\n", s_model_name));
    if(a_cfg_cust_get_support_energy_start_by_mode_name())
      {
        b_need_energy_start = TRUE;
      }
      else
      {
        b_need_energy_start = FALSE;
      }
}
/*----------------------------------------------------------------------------
 * Name: _menu_backbar_common_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static  INT32 _menu_backbar_common_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if(WGL_MSG_KEY_DOWN==ui4_msg||
       WGL_MSG_KEY_REPEAT==ui4_msg)
    {
        INT32       i4_ret;
        UINT32      ui4_keycode = (UINT32)param1;

        if (NULL_HANDLE == h_backbar_last_widget ||
            NULL_HANDLE == h_backbar_first_widget)
        {
            return WGLR_INV_ARG;
        }

        MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][MNGR][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
            __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
                return WGLR_OK;
            case BTN_CURSOR_DOWN:
            {
                i4_ret = c_wgl_set_focus(h_backbar_first_widget, WGL_NO_AUTO_REPAINT);
                MENU_CHK_FAIL(i4_ret);

                i4_ret = c_wgl_do_cmd(h_backbar_first_widget,
                                    WGL_CMD_LB_HLT_ELEM,
                                    WGL_PACK(0),
                                    WGL_PACK(FALSE));
                MENU_LOG_ON_FAIL(i4_ret);

                menu_pm_repaint();
            }
            return WGLR_OK;

            case BTN_SELECT:
            case BTN_CURSOR_LEFT:
            {
                menu_nav_back();
            }
            return WGLR_OK;

            default:
                break;
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_homebar_common_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static  INT32 _menu_homebar_common_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        /* hide old help tip first*/
        menu_hide_help_tip();
        /* trigger help tip */
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }
    else if(WGL_MSG_KEY_DOWN == ui4_msg ||
            WGL_MSG_KEY_REPEAT == ui4_msg)
    {
        INT32       i4_ret;
        UINT32      ui4_keycode = (UINT32)param1;
        UINT16      ui2_elem_num;

        if(NULL_HANDLE == h_backbar_last_widget ||
           NULL_HANDLE == h_backbar_first_widget)
        {
            return WGLR_INV_ARG;
        }

        MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][MNGR][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
            __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
            {
                i4_ret=c_wgl_set_focus(h_backbar_last_widget,
                                       WGL_NO_AUTO_REPAINT);
                MENU_CHK_FAIL(i4_ret);

                i4_ret = c_wgl_do_cmd(h_backbar_last_widget,
                                      WGL_CMD_LB_GET_ELEM_NUM,
                                      WGL_PACK(&ui2_elem_num),
                                      NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=c_wgl_do_cmd(h_backbar_last_widget,
                             WGL_CMD_LB_HLT_ELEM,
                             WGL_PACK(ui2_elem_num-1),
                             WGL_PACK(FALSE));
                MENU_LOG_ON_FAIL(i4_ret);

                menu_pm_repaint();
            }
            return WGLR_OK;

            case BTN_CURSOR_DOWN:
            {
                i4_ret=c_wgl_set_focus(h_backbar_frm,
                                       WGL_NO_AUTO_REPAINT);
                MENU_CHK_FAIL(i4_ret);

                menu_pm_repaint();
            }
            return WGLR_OK;

            case BTN_SELECT:
            case BTN_CURSOR_LEFT:
            {
                i4_ret = menu_nav_go_home_menu();
                MENU_CHK_FAIL(i4_ret);
            }
            return WGLR_OK;

            default:
                break;
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _init_canvas
 *
 * Description:
 *      Get the canvas handle of the application. It would be the root of the
 *  widget hierarchy.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _init_canvas (VOID)
{
    INT32            i4_ret;
    GL_HSCREEN_T     h_screen = NULL_HANDLE;

    /*Open the screen */
    i4_ret = c_gl_screen_open (SN_PRES_MAIN_DISPLAY,
                               NULL,
                               NULL,
                               & h_screen);
    if (GL_FAILED(i4_ret))
    {
        DBG_ERROR(("<MENU>Can't open screen\n\r"));
        return MENUR_FAIL;
    }

    /*Open the plane */
    i4_ret = c_gl_plane_open (h_screen,

#ifdef APP_MERGE_INTO_ONE_OSD
                              0,
#else
                              1,
#endif

                              &h_plane);
    if (GL_FAILED(i4_ret))
    {
        DBG_ERROR(("<MENU>Can't open plane\n\r"));
        c_handle_free(h_screen);
        return MENUR_FAIL;
    }

    /*Link the plane*/
    i4_ret = c_gl_plane_link (h_plane, h_screen, TRUE);
    if (GL_FAILED(i4_ret))
    {
        DBG_ERROR(("<MENU>Can't link plane\n\r"));
        c_handle_free(h_screen);
        c_handle_free(h_plane);
        return MENUR_FAIL;
    }

    /*Open the canvas */
    i4_ret = c_wgl_get_canvas (h_plane,
                               & h_canvas);
    if (GL_FAILED(i4_ret))
    {
        DBG_ERROR(("<MENU>Can't get canvas %d\n\r", i4_ret));
        c_handle_free(h_screen);
        c_handle_free(h_plane);
        return MENUR_FAIL;
    }


    i4_ret = c_wgl_get_canvas_size(h_canvas,
                                   &ui4_canvas_width,
                                   &ui4_canvas_height);
    if (GL_FAILED(i4_ret))
    {
        DBG_ERROR(("<MENU>Can't get canvas %d\n\r", i4_ret));
    }

    /* Free the handles */
    c_handle_free(h_screen);
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _init_frm_root
 *
 * Description:
 *      Init the root frame of the menu. The root frame is as large as the
 *  the screen size. All the menu components should be child of the root frame.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _init_frm_root(VOID)
{
    INT32                   i4_ret;
    GL_RECT_T               t_rect;

    /* Init Caption Preview Frame */
    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     SCREEN_W,
                     SCREEN_H);
    i4_ret = c_wgl_create_widget(h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 0,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI | WGL_STL_GL_NO_BK),
                                 0,
                                 &h_frm_root);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _init_frm_main
 *
 * Description:
 *      Init the main frame of the menu. Main frame is the main menu frame.
 *  The location of main frame is defined by FRAME_X, FRAME_Y while
 *  the size of main frame is defined by FRAME_W, FRAME_H.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _init_frm_main(VOID)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    UINT32          ui4_style;
    UINT8           ui1_alpha;
    WGL_IMG_INFO_T  t_img_info;

    ui4_style = 0;

    i4_osd_width = FRAME_W;
    i4_osd_height = FRAME_H;
    i4_osd_hoffset = 0;
    i4_osd_voffset = 0;
    ui4_hide_delay1 = MENU_PM_HIDE_DELAY;
    ui4_hide_delay2 = MENU_PM_HIDE_DELAY2;

    SET_RECT_BY_SIZE(&t_rect,
                     FRAME_X - FRAME_W,
                     FRAME_Y,
                     FRAME_W,
                     FRAME_H + HELP_TIP_FRAME_H);

    if(b_using_fading)
    {
        ui1_alpha = 255;
    }
    else
    {
        ui1_alpha = ui1_osd_alpha;
    }

    i4_ret = c_wgl_create_widget(h_frm_root,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 ui1_alpha,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &h_frm_main);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* set image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_bk0;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_bk0;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_bk0;
    i4_ret = c_wgl_do_cmd(h_frm_main,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    t_g_rect_out = t_rect;

    t_g_rect_in.i4_left   = t_g_rect_out.i4_left+(WGL_RECT_GET_WIDTH(&t_g_rect_out));
    t_g_rect_in.i4_right  = t_g_rect_out.i4_right+(WGL_RECT_GET_WIDTH(&t_g_rect_out));
    t_g_rect_in.i4_bottom = t_g_rect_out.i4_bottom;
    t_g_rect_in.i4_top    = t_g_rect_out.i4_top;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _init_titlebar
 *
 * Description:
 *  The titlebar is the upper area of the main menu.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _init_titlebar(VOID)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    UINT32          ui4_style;
    ui4_style = WGL_STL_GL_NO_BK;

    SET_RECT_BY_SIZE(&t_rect, TITLEBAR_X, TITLEBAR_Y, TITLEBAR_W, TITLEBAR_H);
    i4_ret = c_wgl_create_widget(h_frm_main,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &h_frm_tb);
    if(i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_timer_create(&h_srcl_title_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*Fake to hide Homebar icon*/
/*----------------------------------------------------------------------------
 * Name: _init_main_title_text
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
static INT32 _init_main_title_text(VOID)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T     t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    UINT8               ui1_align=0;

    SET_RECT_BY_SIZE(&t_rect,
                     MAIN_TITLE_X,
                     MAIN_TITLE_Y,
                     MAIN_TITLE_W,
                     MAIN_TITLE_H);

    i4_ret = c_wgl_create_widget(h_frm_main,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_128),
                                 NULL,
                                 &h_main_title_txt);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_main_title_txt,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(MAIN_TITLE_ALIGN),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 10;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(h_main_title_txt,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;  //TITLE_FONT_SIZE
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    //t_fnt_info.ui1_custom_size = 24;

    i4_ret = c_wgl_do_cmd (h_main_title_txt,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_CHK_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(h_main_title_txt,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_bk0;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk0;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk0;
    i4_ret = c_wgl_do_cmd(h_main_title_txt,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    ui1_align = (UINT8)WGL_NO_AUTO_REPAINT;

    i4_ret = c_wgl_insert (h_main_title_txt,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           ui1_align);
    MENU_CHK_FAIL(i4_ret);


    return MENUR_OK;
}

HANDLE_T menu_get_backbar_txt_handle(VOID)
{
    return h_backbar_txt;
}

static INT32 _init_backbar_arrow(
    HANDLE_T    h_parent,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T     t_inset;
    WGL_IMG_INFO_T  t_img_info;

    /*backbar*/
    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     BACK_BAR_W,
                     BACK_BAR_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(0),
                                 (VOID*)0,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    t_inset.i4_left     = 12;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 15;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_back_left_arrow;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_back_left_arrow;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_back_left_arrow;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _init_backbar_txt(
    HANDLE_T    h_parent,
    HANDLE_T*   ph_widget
    )
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T     t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     BACK_BAR_W,
                     BACK_BAR_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_128),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(TITLE_ALIGN),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    t_inset.i4_left     = 42;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 10;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = TITLE_FONT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = 21;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_CHK_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _init_backbar(VOID)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_IMG_INFO_T  t_img_info;

    /*backbar*/
    SET_RECT_BY_SIZE(&t_rect,
                     BACK_BAR_X,
                     BACK_BAR_Y,
                     BACK_BAR_W,
                     BACK_BAR_H);

    i4_ret = c_wgl_create_widget(h_frm_main,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _menu_backbar_common_proc_fct,
                                 255,
                                 (VOID*)(0),
                                 (VOID*)0,
                                 &h_backbar_frm);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* set image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE; //h_g_menu_back_bar_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_back_bar_bk_hlt;
    t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE; //h_g_menu_back_bar_bk;
    i4_ret = c_wgl_do_cmd(h_backbar_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));

    i4_ret = _init_backbar_arrow(h_backbar_frm,
                            &h_backbar_arrow);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _init_backbar_txt(h_backbar_frm,
                            &h_backbar_txt);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_main_chg_backbar();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _init_title_txt
 *
 * Description:
 *      The title component is the title of current page.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _init_title_txt(
    HANDLE_T    h_parent,
    HANDLE_T*   ph_widget
){
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T     t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    SET_RECT_BY_SIZE(&t_rect,
                     TITLE_X,
                     TITLE_Y,
                     TITLE_W,
                     TITLE_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_128|WGL_STL_TEXT_MS_NO_SMARTCUT),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(TITLE_ALIGN),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = TITLE_FONT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = 28;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_CHK_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _init_title_frm
 *
 * Description:
 *      Init the main frame of the menu. Main frame is the main menu frame.
 *  The location of main frame is defined by FRAME_X, FRAME_Y while
 *  the size of main frame is defined by FRAME_W, FRAME_H.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _init_title_frm(VOID)
{
    return  _init_title_txt(h_frm_main,
                           &h_txt_title);
}

/*----------------------------------------------------------------------------
 * Name: _version_put_key
 *
 * Description:
 *      Filter the secret input sequence to open the version info. If the
 *  sequence matches the pattern, then return TRUE; Otherwise, FALSE is return.
 *
 * Inputs:
 *      ui4_key -   The key to filter.
 *
 * Outputs: -
 *
 * Returns:
 *      TRUE    -   Matches the pattern
 *      FALSE   -   Otherwise
 *
 ----------------------------------------------------------------------------*/
static BOOL _version_put_key(UINT32 ui4_key)
{
    UINT32  ui4_i, ui4_j;
    BOOL    b_show = TRUE;

    /* Make Klocwork happy */
    if(ui2_ver_key_list_ptr >= VERSION_KEY_LIST_SIZE)
    {
        return FALSE;
    }

    aui4_ver_key_list[ui2_ver_key_list_ptr++] = ui4_key;
    ui2_ver_key_list_ptr %= VERSION_KEY_LIST_SIZE;

    for(ui4_i = 0, ui4_j = ui2_ver_key_list_ptr;
        ui4_i<VERSION_KEY_LIST_SIZE;
        ui4_i++, ui4_j=(ui4_j+1)%VERSION_KEY_LIST_SIZE)
    {
        if(aui4_ver_key_list[ui4_j] !=  aui4_ver_key_list_pattern[ui4_i])
        {
            b_show = FALSE;
            break;
        }
    }

    return b_show;
}

/*----------------------------------------------------------------------------

                            Page Management
 ---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _page_get_page_entry_by_id
 *
 * Description:
 *      Get the page object by a given page id.
 *
 * Inputs:
 *      ui4_page_id -   The page id
 *
 * Outputs:
 *      ppt_page_entry  -   the page entry object
 *
 * Returns:
 *      MENUR_OK                -   Operation sucessful
 *      MENUR_PAGE_NOT_FOUND    -   Page not found
 ----------------------------------------------------------------------------*/
static INT32 _page_get_page_entry_by_id(UINT32            ui4_page_id,
                                        PM_PAGE_ENTRY_T** ppt_page_entry)
{
    PM_PAGE_ENTRY_T* pt_page_tmp;
    DLIST_FOR_EACH(pt_page_tmp, &t_page_list, t_link)
    {
        if(pt_page_tmp->ui4_page_id == ui4_page_id)
        {
            *ppt_page_entry = pt_page_tmp;
            return MENUR_OK;
        }
    }
    return MENUR_PAGE_NOT_FOUND;
}


/*----------------------------------------------------------------------------
 * Name: _page_get_page_entry_by_cnt_frm
 *
 * Description:
 *      Get the page object by the content frame.
 *
 * Inputs:
 *      h_cnt_frm -   The content frame.
 *
 * Outputs:
 *      ppt_page_entry  -   the page entry object
 *
 * Returns:
 *      MENUR_OK    -   Operation sucessful
 *      MENUR_FAIL  -   Operation failed
 ----------------------------------------------------------------------------*/
static INT32 _page_get_page_entry_by_cnt_frm(HANDLE_T          h_cnt_frm,
                                                    PM_PAGE_ENTRY_T**  ppt_page_entry)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_cnt_frm,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_page_entry),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_show
 *
 * Description:
 *      Show the given page and call the lifecycle callback (*pf_menu_page_show)()
 *  of this page.
 *
 * Inputs:
 *      pt_page_entry -   The page entry object
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK    -   Operation sucessful
 *      MENUR_FAIL  -   Operation failed
 ----------------------------------------------------------------------------*/
static INT32 _page_show(PM_PAGE_ENTRY_T* pt_page_entry)
{
    if(pt_page_entry == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(pt_page_entry->e_state != MENU_PAGE_STATE_HIDE)
    {
        return MENUR_INV_STATE;
    }

    DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d}PM: page show:[page_id=0x%x, handle = 0x%x]\r\n",
        __FUNCTION__, __LINE__, pt_page_entry->ui4_page_id, pt_page_entry->h_cnt_frm));

#ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT
        BOOL     b_blue_button_enable_status= FALSE;
        a_cfg_custom_get_wide_mode_enable_change(&b_blue_button_enable_status);

        if ( b_blue_button_enable_status == FALSE)
        {
            a_menu_set_help_tip_blue_button_enable_status(FALSE);//gray out view mode when content is 120HZ \MMP(except video full screen)
        }
        else
        {
            a_menu_set_help_tip_blue_button_enable_status(TRUE);
        }
#endif

#ifdef APP_ZOOM_MODE_SUPPORT
        /* TODO: (Steven) move to pf_page_event_listener_fct handler func */
        if (ui4_g_menu_custom_page_pic_quality == pt_page_entry->ui4_page_id)
        {
            menu_timer_set_delay(5 * 60 * 1000);
            a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_COLOR_TUNER));
        }
        else if (pt_page_entry->ui4_page_id == ui4_g_menu_page_pic_size||
                 pt_page_entry->ui4_page_id == ui4_g_menu_page_pic_postion)
        {
            a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_PIC_SIZE));
        }
        else if (pt_page_entry->ui4_page_id == ui4_g_menu_page_eq_bands_setting)
        {
            a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_EQUALIZER));
        }
        else if (ui4_g_menu_page_scr_mode == pt_page_entry->ui4_page_id)
        {
            a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_SCREEN_MODE));
        }
        else if (ui4_g_page_clear_memory_dialog == pt_page_entry->ui4_page_id ||
                 ui4_g_page_clear_memory == pt_page_entry->ui4_page_id ||
                 ui4_g_page_service_check_dialog == pt_page_entry->ui4_page_id ||
                 ui4_g_page_service_rst_dialog == pt_page_entry->ui4_page_id ||
                 ui4_page_chg_country_code_dialog == pt_page_entry->ui4_page_id||
                 ui4_page_oled_screen_1 == pt_page_entry->ui4_page_id ||
                 ui4_page_oled_screen_2 == pt_page_entry->ui4_page_id)
        {
            a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
        }
        else
        {
            a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DEFAULT));
        }
#endif

    pt_page_entry->e_state = MENU_PAGE_STATE_SHOW;

    c_wgl_set_visibility(pt_page_entry->h_cnt_frm,WGL_SW_NORMAL);
    MENU_CHK_FAIL(pt_page_entry->t_fct_tbl.pf_menu_page_show(pt_page_entry->ui4_page_id));

    // c_wgl_float(h_frm_main, TRUE, FALSE);
    /* Notify the listener */
    if (pf_page_event_listener_fct != NULL)
    {
        pf_page_event_listener_fct(pt_page_entry->ui4_page_id,MENU_PAGE_EVENT_SHOW);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_hide
 *
 * Description:
 *      Hide the given page and call the lifecycle callback (*pf_menu_page_hide)()
 *  of this page.
 *
 * Inputs:
 *      pt_page_entry -   The page entry object
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK    -   Operation sucessful
 *      MENUR_FAIL  -   Operation failed
 ----------------------------------------------------------------------------*/
static INT32 _page_hide(
    PM_PAGE_ENTRY_T* pt_page_entry
){
    INT32 i4_ret;

    if(pt_page_entry == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(pt_page_entry->e_state != MENU_PAGE_STATE_SHOW)
    {
        return MENUR_INV_STATE;
    }

    DBG_LOG_PRINT(("<MENU>PM: page hide:[pid=0x%x,handle =0x%x]b_hide_common_page = %d\r\n", pt_page_entry->ui4_page_id,pt_page_entry->h_cnt_frm,b_hide_common_page));

    pt_page_entry->e_state = MENU_PAGE_STATE_HIDE;

    if (b_hide_common_page == TRUE)
    {
        c_wgl_set_visibility(pt_page_entry->h_cnt_frm,WGL_SW_HIDE);
    }

    i4_ret = pt_page_entry->t_fct_tbl.pf_menu_page_hide(pt_page_entry->ui4_page_id);
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_ZOOM_MODE_SUPPORT
    /* TODO: (Steven) move to pf_page_event_listener_fct handler func */
    if (ui4_g_menu_custom_page_pic_quality == pt_page_entry->ui4_page_id)
    {
        menu_timer_set_delay(TIMER_DELAY);
        a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_COLOR_TUNER));
    }
    else if (pt_page_entry->ui4_page_id == ui4_g_menu_page_pic_size
        ||   pt_page_entry->ui4_page_id == ui4_g_menu_page_pic_postion)
    {
        a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_PIC_SIZE));
    }
    else if (pt_page_entry->ui4_page_id == ui4_g_menu_page_eq_bands_setting)
    {
        a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_EQUALIZER));
    }
    else if (ui4_g_menu_page_scr_mode == pt_page_entry->ui4_page_id)
    {
        a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_SCREEN_MODE));
    }
    else if (ui4_g_page_clear_memory_dialog == pt_page_entry->ui4_page_id ||
             ui4_g_page_clear_memory == pt_page_entry->ui4_page_id ||
             ui4_g_page_service_check_dialog == pt_page_entry->ui4_page_id ||
             ui4_g_page_service_rst_dialog == pt_page_entry->ui4_page_id ||
             ui4_page_chg_country_code_dialog == pt_page_entry->ui4_page_id)
    {
        a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
    }
    else
    {
        a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DEFAULT));
    }
#endif

    /* Notify the listener */
    if (pf_page_event_listener_fct != NULL)
    {
        pf_page_event_listener_fct(pt_page_entry->ui4_page_id,
                                   MENU_PAGE_EVENT_HIDE);
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_focus
 *
 * Description:
 *      Focus the given page and call the lifecycle callback (*pf_menu_page_get_focus)()
 *  of this page.
 *
 * Inputs:
 *      pt_page_entry -   The page entry object
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK                -   Operation sucessful
 *      MENUR_FAIL              -   Operation failed
 ----------------------------------------------------------------------------*/
static INT32 _page_focus(
    PM_PAGE_ENTRY_T* pt_page_entry,
    MENU_PAGE_HINT_T* pt_hint
){
    INT32   i4_ret;

    if(pt_page_entry == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(pt_page_entry->e_state != MENU_PAGE_STATE_SHOW)
    {
        return MENUR_INV_STATE;
    }

    DEBUG_PM( DBG_LOG_PRINT(("<MENU>PM: _page_focus():[page_id=%d]\n", pt_page_entry->ui4_page_id)); );
    DBG_INFO(("<MENU>PM: page get_focus:[pid=%d]\r\n", pt_page_entry->ui4_page_id));

    pt_page_entry->e_state = MENU_PAGE_STATE_FOCUS;

    i4_ret =  pt_page_entry->
        t_fct_tbl.pf_menu_page_get_focus(pt_page_entry->ui4_page_id, pt_hint);
    MENU_CHK_FAIL(i4_ret);

    /* Notify the listener */
    if (pf_page_event_listener_fct != NULL)
    {
        pf_page_event_listener_fct(pt_page_entry->ui4_page_id,
                                   MENU_PAGE_EVENT_FOCUS);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_unfocus
 *
 * Description:
 *      Unfocus the given page and call the lifecycle callback (*pf_menu_page_lose_focus)()
 *  of this page.
 *
 * Inputs:
 *      pt_page_entry -   The page entry object
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK    -   Operation sucessful
 *      MENUR_FAIL  -   Operation failed
 ----------------------------------------------------------------------------*/
static INT32 _page_unfocus(
    PM_PAGE_ENTRY_T* pt_page_entry
){
    INT32   i4_ret;

    if(pt_page_entry == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(pt_page_entry->e_state != MENU_PAGE_STATE_FOCUS)
    {
        return MENUR_INV_STATE;
    }

    DEBUG_PM( DBG_LOG_PRINT(("<MENU>PM{%s,%d}: page lose_focus:[page_id=%d]\r\n", __FUNCTION__,__LINE__, pt_page_entry->ui4_page_id)); );
    DBG_INFO(("<MENU>PM: page lose_focus:[pid=%d]\r\n", pt_page_entry->ui4_page_id));

    pt_page_entry->e_state = MENU_PAGE_STATE_SHOW;
    menu_hide_help_tip();
    i4_ret = pt_page_entry->
        t_fct_tbl.pf_menu_page_lose_focus(pt_page_entry->ui4_page_id);
    MENU_CHK_FAIL(i4_ret);

    /* Notify the listener */
    if (pf_page_event_listener_fct != NULL)
    {
        pf_page_event_listener_fct(pt_page_entry->ui4_page_id,
                                   MENU_PAGE_EVENT_UNFOCUS);
    }

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _page_cnt_frm_proc_fct
 *
 * Description:
 *      This is the widget procedure of the content frame. It will delegate the
 *  WGL_MSG_NOTIFY, WGL_MSG_KEY_DOWN, WGL_MSG_KEY_REPEAT, WGL_MSG_KEY_UP to the
 *  procedure function set by menu_page_set_proc_func()
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_cnt_frm_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2
){

    if(ui4_msg == WGL_MSG_NOTIFY     ||
       ui4_msg == WGL_MSG_KEY_DOWN   ||
       ui4_msg == WGL_MSG_KEY_REPEAT ||
       ui4_msg == WGL_MSG_KEY_UP)
    {
        PM_PAGE_ENTRY_T* pt_page_entry;

        _page_get_page_entry_by_cnt_frm(h_widget, &pt_page_entry);
        if(pt_page_entry->pf_wdgt_proc != NULL)
        {
            return pt_page_entry->pf_wdgt_proc(h_widget, ui4_msg, param1, param2);
        }
        else
        {
            return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _page_create_cnt_frm
 *
 * Description:
 *  Create a content frame.
 *
 * Inputs:
 *
 * Outputs:
 *  ph_cnt_frm  -   The content frame created.
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_create_cnt_frm(
    HANDLE_T*    ph_cnt_frm
){
    INT32               i4_ret;
    GL_RECT_T           t_rect;

    SET_RECT_BY_SIZE(&t_rect,
                     CONTENT_X,
                     CONTENT_Y,
                     CONTENT_W,
                     CONTENT_H);
    i4_ret = c_wgl_create_widget(h_frm_main,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _page_cnt_frm_proc_fct,
                                 0,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI |
                                         WGL_STL_GL_NO_BK),
                                 NULL,
                                 ph_cnt_frm);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _tab_focus_idx
 *
 * Description:
 *      Focus the tab by given tab index. As the tab is focused, the page attached
 *  to the page would be showed as well, but it does not get the focus. If the
 *  ui2_idx is PM_TABIDX_NONE, no tab would be focused.
 *
 * Inputs:
 *      ui2_idx -   The tab to be focused. If the value is PM_TABIDX_NONE, no
 *                  index would be focused.
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _tab_focus_idx(
    UINT16 ui2_idx
){
    INT32 i4_ret = 0;
    UINT16 ui2_i = 0;


    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui2_idx:%d, ui2_tab_crnt:%d, ui2_tab_num:%d\n",
        __FUNCTION__, __LINE__, ui2_idx, ui2_tab_crnt, ui2_tab_num )); );

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    if(ui2_idx < ui2_tab_num ||
       ui2_idx == PM_TABIDX_NONE)
    {
        /* valid */
    }
    else
    {
        return MENUR_INV_ARG;
    }

    /* set push state */
    for (;ui2_i < ui2_tab_num;ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(at_tabs[ui2_i].h_btn,
                              WGL_CMD_BTN_SET_PUSHED,
                              (VOID*)(ui2_i == ui2_idx ? TRUE : FALSE),
                              NULL);
        MENU_CHK_FAIL(i4_ret);
    }

    if(ui2_idx == PM_TABIDX_NONE)
    {
        DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui2_idx:%d, ui4_page_crnt:%d\n",
            __FUNCTION__, __LINE__, ui2_idx, ui4_page_crnt )); );

        /* close menu, from menu_pm_hide() */
        PM_PAGE_ENTRY_T* pt_page_entry;
        i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                            &pt_page_entry);
        MENU_CHK_FAIL(i4_ret);


        /* if focused, un-focus it */
        if(pt_page_entry->e_state == MENU_PAGE_STATE_FOCUS)
        {
            _page_unfocus(pt_page_entry);
        }

        /* hide it */
        _page_hide(pt_page_entry);

        /* keep the state before hiding */
        ui4_page_crnt_keep = ui4_page_crnt;
        ui2_tab_crnt_keep = ui2_tab_crnt;
        ui2_nav_stack_top_keep = ui2_nav_stack_top;
        e_pm_cond_keep = e_pm_cond;

        /* reset the state */
        ui4_page_crnt = PM_PAGEID_NONE;
        ui2_tab_crnt = PM_TABIDX_NONE;
        ui2_nav_stack_top = 0;
    }
    else if(ui2_tab_crnt == PM_TABIDX_NONE)
    {
        DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui2_idx:%d, ui2_tab_crnt:%d, ui4_page_id:%d\n",
            __FUNCTION__, __LINE__, ui2_idx, ui2_tab_crnt, at_tabs[ui2_idx].pt_page->ui4_page_id )); );

        /* open menu, from menu_pm_show() */
        _page_show(at_tabs[ui2_idx].pt_page);
        ui4_page_crnt = at_tabs[ui2_idx].pt_page->ui4_page_id;
        ui2_tab_crnt = ui2_idx;
        ui2_nav_stack_top = 0;

        DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui2_idx:%d, ui4_page_crnt:%d, ui2_tab_crnt:%d\n",
            __FUNCTION__, __LINE__, ui2_idx, ui4_page_crnt, ui2_tab_crnt )); );

    }
    else if(ui2_tab_crnt != ui2_idx)
    {
        DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui2_idx:%d, ui2_tab_crnt:%d\n",
            __FUNCTION__, __LINE__, ui2_idx, ui2_tab_crnt )); );

        /* 1. pressing left/right at nearby tab, from _tab_proc_fct() */
        /* 2. menu_pm_hide_tab() is called and hide current page */
        /* 3. menu_pm_enable_tab() is called and disable current page */
        /* 4. menu_pm_go_dirct() is called and go to a tab */
        PM_PAGE_ENTRY_T* pt_page_entry;
        i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                            &pt_page_entry);
        MENU_CHK_FAIL(i4_ret);

        if(pt_page_entry->e_state == MENU_PAGE_STATE_FOCUS)
        {
            _page_unfocus(pt_page_entry);
        }

        _page_hide(pt_page_entry);
        _page_show(at_tabs[ui2_idx].pt_page);
        ui4_page_crnt = at_tabs[ui2_idx].pt_page->ui4_page_id;
        ui2_tab_crnt = ui2_idx;
        ui2_nav_stack_top = 0;

        DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui2_idx:%d, ui4_page_crnt:%d, ui2_tab_crnt:%d\n",
            __FUNCTION__, __LINE__, ui2_idx, ui4_page_crnt, ui2_tab_crnt )); );

    }
    else if(at_tabs[ui2_idx].pt_page->e_state == MENU_PAGE_STATE_FOCUS)
    {
        /* back from the topmost page,
           the tab page is the same as showing page
           from menu_nav_back() */
        _page_unfocus(at_tabs[ui2_idx].pt_page);
        ui4_page_crnt = at_tabs[ui2_idx].pt_page->ui4_page_id;
        ui2_tab_crnt = ui2_idx;
        ui2_nav_stack_top = 0;
    }
    else if(at_tabs[ui2_idx].pt_page->e_state == MENU_PAGE_STATE_SHOW)
    {
        /* pressing left/right but only one tab, from _tab_proc_fct(),
           do nothing */
        return MENUR_OK;
    }
    else if(at_tabs[ui2_idx].pt_page->e_state == MENU_PAGE_STATE_HIDE)
    {
        /* back from the topmost page,
           if the topmost page is not the tab page.
           this case would occur when calling back_and_go() operation */
        PM_PAGE_ENTRY_T* pt_page_entry;
        i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                            &pt_page_entry);
        MENU_CHK_FAIL(i4_ret);

        _page_unfocus(pt_page_entry);
        _page_hide(pt_page_entry);
        _page_show(at_tabs[ui2_idx].pt_page);
        ui4_page_crnt = at_tabs[ui2_idx].pt_page->ui4_page_id;
        ui2_tab_crnt = ui2_idx;
        ui2_nav_stack_top = 0;
    }
    else
    {
        return MENUR_FAIL;
        /* unknown operation */
        /* do nothing */
    }

    /* set focus */
    if(ui2_idx != PM_TABIDX_NONE)
    {
        i4_ret = c_wgl_set_focus(at_tabs[ui2_idx].h_btn, WGL_NO_AUTO_REPAINT);
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _tab_proc_fct
 *
 * Description:
 *      The procedure function of the tab widgets.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _tab_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2
){
    typedef enum{
        TAB_VK_NEXT,
        TAB_VK_PREV,
        TAB_VK_ENTER_FIRST,
        TAB_VK_ENTER_LAST,
        TAB_VK_BACK,
        TAB_VK_UNKNOWN
    }TAB_VK_T;

    UINT16 ui2_idx;
    UINT16 ui2_idx_next;

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    for(ui2_idx = 0; ui2_idx < ui2_tab_num; ui2_idx++)
    {
        if(at_tabs[ui2_idx].h_btn == h_widget)
        {
            break;
        }
    }

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            TAB_VK_T e_vk;

            MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][MNGR][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
                __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

            /* key mapping */
            if(b_tab_vert)
            {
                switch (ui4_keycode)
                {
                case BTN_CURSOR_LEFT:
                    e_vk = TAB_VK_BACK;
                    break;
                case BTN_CURSOR_RIGHT:
                    e_vk = TAB_VK_ENTER_FIRST;
                    break;
                case BTN_CURSOR_UP:
                    e_vk = TAB_VK_PREV;
                    break;
                case BTN_CURSOR_DOWN:
                    e_vk = TAB_VK_NEXT;
                    break;
                case BTN_SELECT:
                    e_vk = TAB_VK_ENTER_FIRST;
                    break;
                case BTN_RETURN:
                    e_vk = TAB_VK_BACK;
                    break;
                default:
                    e_vk = TAB_VK_UNKNOWN;
                }
            }
            else
            {
                switch (ui4_keycode)
                {
                case BTN_CURSOR_LEFT:
                    e_vk = TAB_VK_PREV;
                    break;
                case BTN_CURSOR_RIGHT:
                    e_vk = TAB_VK_NEXT;
                    break;
                case BTN_CURSOR_UP:
                    e_vk = TAB_VK_ENTER_LAST;
                    break;
                case BTN_CURSOR_DOWN:
                    e_vk = TAB_VK_ENTER_FIRST;
                    break;
                case BTN_SELECT:
                    e_vk = TAB_VK_ENTER_FIRST;
                    break;
                case BTN_RETURN:
                    e_vk = TAB_VK_BACK;
                    break;
                default:
                    e_vk = TAB_VK_UNKNOWN;
                }
            }

            /* virtual key logic */
            switch (e_vk)
            {
            case TAB_VK_PREV:
                ui2_idx_next = ui2_idx;
                do
                {
                    if(ui2_idx_next == 0)
                    {
#ifdef APP_MENU_TAB_LEAVE_ON_BOUNDARY
                        menu_leave(TRUE, ui4_hide_delay1);
                        return WMPR_DONE;
#else
                        ui2_idx_next = (UINT16)(ui2_tab_num - 1);
#endif
                    }
                    else
                    {
                        ui2_idx_next = (UINT16)(ui2_idx_next - 1);
                    }

                    /* Make Klocwork happy */
                    if(ui2_idx_next >= MENU_PM_MAX_TAB_NUM)
                    {
                        break;
                    }

                } while(ui2_idx_next != ui2_idx &&
                        (at_tabs[ui2_idx_next].b_enabled == FALSE ||
                         at_tabs[ui2_idx_next].b_hidden == TRUE)
                       );  /* b_enabled == FALSE or b_hidden == TRUE,
                              continue search next tab */


                _tab_focus_idx(ui2_idx_next);
                menu_pm_repaint();

                return WMPR_DONE;
            case TAB_VK_NEXT:
                ui2_idx_next = ui2_idx;
                do
                {
                    if(ui2_idx_next == (UINT16)(ui2_tab_num - 1))
                    {
#ifdef APP_MENU_TAB_LEAVE_ON_BOUNDARY
                        menu_leave(TRUE, ui4_hide_delay2);
                        return WMPR_DONE;
#else
                        ui2_idx_next = 0;
#endif
                    }
                    else
                    {
                        ui2_idx_next = (UINT16)(ui2_idx_next + 1);
                    }

                    /* Make Klocwork happy */
                    if(ui2_idx_next >= MENU_PM_MAX_TAB_NUM)
                    {
                        break;
                    }
                } while(ui2_idx_next != ui2_idx &&
                        (at_tabs[ui2_idx_next].b_enabled == FALSE ||
                         at_tabs[ui2_idx_next].b_hidden == TRUE)
                       );  /* b_enabled == FALSE or b_hidden == TRUE,
                              continue search next tab */

                _tab_focus_idx(ui2_idx_next);
                menu_pm_repaint();

                return WMPR_DONE;
            case TAB_VK_ENTER_LAST:
                {
                    MENU_PAGE_HINT_T t_hint;

                    t_hint.e_hint_type = MENU_PAGE_HT_PORT;
                    t_hint.u.e_port = MENU_PAGE_PORT_BOTTOM;

                    /* Make Klocwork happy */
                    if(ui2_tab_crnt < MENU_PM_MAX_TAB_NUM)
                    {
                        menu_nav_go(at_tabs[ui2_tab_crnt].pt_page->ui4_page_id,
                                    &t_hint);
                    }

                    return WMPR_DONE;
                }
            case TAB_VK_ENTER_FIRST:
                {
                    MENU_PAGE_HINT_T t_hint;

                    t_hint.e_hint_type = MENU_PAGE_HT_PORT;
                    t_hint.u.e_port = MENU_PAGE_PORT_TOP;

                    /* Make Klocwork happy */
                    if(ui2_tab_crnt < MENU_PM_MAX_TAB_NUM)
                    {
                        menu_nav_go(at_tabs[ui2_tab_crnt].pt_page->ui4_page_id,
                                    &t_hint);
                    }

                    return WMPR_DONE;
                }
            case TAB_VK_BACK:
#ifdef APP_MENU_TAB_PAUSE_ON_EXIT
                menu_leave(FALSE, 0);
#else
                menu_leave(TRUE, ui4_hide_delay1);
#endif
                return WMPR_DONE;
            default:
                break;
            }
        }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _tab_reset_position
 *
 * Description: Re-determine every Tab's position according to it hidden status.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/

static INT32 _tab_reset_position(VOID)
{
    UINT16      ui2_i;
    UINT16      ui2_idx;
    GL_RECT_T   t_rect;

    ui2_i = 0;

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    for(ui2_idx = 0 ; ui2_idx < ui2_tab_num ; ui2_idx++)
    {
        if(at_tabs[ui2_idx].b_hidden == FALSE)    /* Do the same position set method */
        {

            SET_RECT_BY_SIZE(&t_rect,
                             TITLEBAR_TAB_X,
                             TITLEBAR_TAB_Y,
                             TITLEBAR_TAB_W,
                             TITLEBAR_TAB_H);
            ui2_i++;  /* Incremental the i */
        }
        else
        {
            /* Hidden */
                SET_RECT_BY_SIZE(&t_rect,
                                 0,
                                 0,
                                 0,
                                 0);
        }

        /* Save it */
        at_tabs[ui2_idx].t_rect = t_rect;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _tab_move
 *
 * Description: Move the Tabs to correct positions and set the correct
 *              visibility of them.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/

static INT32 _tab_move(VOID)
{
    UINT16      ui2_idx;

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    for(ui2_idx = 0 ; ui2_idx < ui2_tab_num ; ui2_idx++)
    {
        c_wgl_move(at_tabs[ui2_idx].h_btn,
                   &at_tabs[ui2_idx].t_rect,
                   FALSE);

        if(at_tabs[ui2_idx].b_hidden == TRUE)
        {
            c_wgl_set_visibility(at_tabs[ui2_idx].h_btn, WGL_SW_HIDE);
        }
        else
        {
            c_wgl_set_visibility(at_tabs[ui2_idx].h_btn, WGL_SW_NORMAL);
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _tab_are_all_hide
 *
 * Description: Check if all the Tabs are hidden.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/

BOOL _tab_are_all_hide(VOID)
{
    UINT16      ui2_idx;
    UINT16      ui2_count;

    ui2_count = 0;

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return FALSE;
    }

    for(ui2_idx = 0 ; ui2_idx < ui2_tab_num ; ui2_idx++)
    {
        if(at_tabs[ui2_idx].b_hidden == TRUE)
        {
            ui2_count++;
        }
    }

    if(ui2_count == ui2_tab_num)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

/*----------------------------------------------------------------------------
 * Name: _tab_enable
 *
 * Description:
 *      Enable the specified tab. The disabled tab cannot be the current focus
 *  tab.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _tab_enable(
    UINT16   ui2_idx,
    BOOL     b_enable)
{
    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    if(ui2_idx >= ui2_tab_num)
    {
        DBG_ERROR(("<MENU> Index out of bound\r\n"));
        return MENUR_INV_ARG;
    }

    if(ui2_idx == ui2_tab_crnt)
    {
        DBG_ERROR(("<MENU> Don't enable/disable current focused tab\r\n"));
        return MENUR_INV_ARG;
    }

    /* The tab status is not changed */
    if(at_tabs[ui2_idx].b_enabled == b_enable)
    {
        return MENUR_OK;
    }

    at_tabs[ui2_idx].b_enabled = b_enable;

    c_wgl_enable(at_tabs[ui2_idx].h_btn, b_enable);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _tab_hide
 *
 * Description: Hide a specified tab.
 *
 * Inputs:  ui2_idx  -  The tab index.
 *          b_hidden -  Hide or not.
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _tab_hide(
    UINT16   ui2_idx,
    BOOL     b_hidden)
{
    if(ui2_idx >= MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_ARG;
    }

    /* The tab status is not changed */
    if(at_tabs[ui2_idx].b_hidden == b_hidden)
    {
        return MENUR_OK;
    }

    at_tabs[ui2_idx].b_hidden = b_hidden;

    _tab_reset_position();
    _tab_move();

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _tab_create_widget
 *
 * Description:
 *      Create the tab button widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _tab_create_widget(
    HANDLE_T    h_parent,
    UINT16      ui2_idx,
    WGL_HIMG_TPL_T  h_img_normal,
    WGL_HIMG_TPL_T  h_img_hlt,
    WGL_HIMG_TPL_T  h_img_sel,
    WGL_HIMG_TPL_T  h_img_disable,
    HANDLE_T*   ph_widget,
    GL_RECT_T*   pt_rect
){
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_IMG_INFO_T  t_img_info;

    SET_RECT_BY_SIZE(&t_rect,
                     TITLEBAR_TAB_X + TITLEBAR_TAB_W,
                     TITLEBAR_TAB_Y,
                     TITLEBAR_TAB_W,
                     TITLEBAR_TAB_H);

    /* Save the initial rectangle infomation */
    *pt_rect = t_rect;

    i4_ret = c_wgl_create_widget(
                                h_frm_tb,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                _tab_proc_fct,
                                255,
                                (void*)(WGL_STL_GL_NO_IMG_UI | WGL_STL_BTN_CHECKBOX),
                                NULL,
                                ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          (VOID*)MENU_PM_TAB_ALIGNMENT,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set image */
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable = h_img_normal;
    t_img_info.u_img_data.t_extend.t_disable = h_img_disable;
    t_img_info.u_img_data.t_extend.t_highlight = h_img_hlt;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_img_hlt;
    t_img_info.u_img_data.t_extend.t_push = h_img_hlt;
    t_img_info.u_img_data.t_extend.t_push_unhighlight = h_img_sel;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info) );
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget, WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _help_tip_timeout_do
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
static VOID _help_tip_timeout_do(VOID*   pv_data,
                                 SIZE_T  z_data_size)
{
    a_help_tip_show_help(h_menu_help_tip);
}

/*----------------------------------------------------------------------------
 * Name: _help_tip_timer_nfy
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
static VOID _help_tip_timer_nfy(HANDLE_T  pt_tm_handle,
                                VOID*     pv_tag)
{
    menu_async_invoke(_help_tip_timeout_do,
                      NULL,
                      0,
                      TRUE);
}


/*----------------------------------------------------------------------------
 * Name: _menu_anim_start_move_animation
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
static INT32 _menu_anim_start_move_animation(
    HANDLE_T            h_anim_move,
    VOID*               pv_param1,
    VOID*               pv_param2)
{
    INT32        i4_ret = MENUR_OK;
    GL_RECT_T*   pt_rect_from = NULL;
    GL_RECT_T*   pt_rect_to = NULL;
    WGL_ANIMATION_DATA_T   t_anim_data;
    WGL_ANIM_CONTEXT_T e_menu_anim_context = ANIM_CONTEXT_APP_SYNC;
 //   INT32 tick = c_os_get_sys_tick();

    /* Get move animation start, end position */
    pt_rect_from = (GL_RECT_T*)pv_param1;
    pt_rect_to   = (GL_RECT_T*)pv_param2;


    /* Check move animation start, end position */
    if ((NULL == pt_rect_from) ||
        (NULL == pt_rect_to))
    {
        return MENUR_INV_ARG;
    }

    /* Check animation handle validation */
    if (NULL_HANDLE == h_anim_move)
    {
        return MENUR_INV_ARG;
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
            DBG_ERROR (("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
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

        t_anim_data.pt_path_mode->ui2_total_steps = 1;
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


        {
            UINT32 u32_sys_tick = c_os_get_sys_tick();

            //MENU_DEBUG_TIME_CHECK_POINT();

            /* Start animation */
            i4_ret= c_wgl_start_animation(h_anim_move,
                                          &t_anim_data,
                                          e_menu_anim_context);
            //MENU_DEBUG_TIME_CHECK_POINT();
            MENU_DEBUG_TIME( DBG_LOG_PRINT(("[MENU][MNGR][TIME]{%s,%d} c_wgl_start_animation() use %d ms\n",
                    __FUNCTION__, __LINE__, (c_os_get_sys_tick()-u32_sys_tick)*g_menu_u32_sys_tick_period )); );

            if (i4_ret != WGLR_OK)
            {
                DBG_INFO(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
                break;
            }
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
  //  DBG_INFO(("[MENU][%s %d] cost %d ms\n",__FUNCTION__,__LINE__,c_os_get_sys_tick_period()* (c_os_get_sys_tick() - tick)));

    return MENUR_OK;
}

static INT32 _help_tip_custom_page_proc_fct(HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       param1,
                                          VOID*       param2,
                                          BOOL*       pb_processed)
{
    UINT16 ui2_i = 0;
    UINT32 ui4_cur_page = 0;

    menu_nav_get_crnt_page(&ui4_cur_page);

    for (ui2_i = 0; ui2_i < E_HELP_TIP_CB_PAGE_LAST; ui2_i++)
    {
        if (_help_tip_back_key_cb.aui4_page_id[ui2_i] == ui4_cur_page
            && _help_tip_back_key_cb.ap_fct[ui2_i] != NULL)
        {
            _help_tip_back_key_cb.ap_fct[ui2_i](h_widget,ui4_msg, param1, param2, pb_processed);
            break;
        }
    }

    return HELP_TIPR_OK;
}

static INT32 _help_tip_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    BOOL b_processed = FALSE;

    if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)param1;

        MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][MNGR][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
            __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
                if (a_help_tip_get_focus_last() == h_widget)
                {
                    break;
                }

                if (!b_show_help_text)
                {
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
                }
                else
                {
                    c_memset(w2s_help_txt, 0, sizeof(w2s_help_txt));
                    c_uc_w2s_strcpy(w2s_help_txt, a_help_tip_get_last_txt());
                    menu_set_and_show_help_tip(w2s_help_txt);
                }
                c_wgl_set_focus(a_help_tip_get_focus_last(),WGL_SYNC_AUTO_REPAINT);
                break;
            case BTN_SELECT:
                if (2 == a_help_tip_get_focus_icon_idx(h_menu_help_tip))
                {
                    if (a_cfg_custom_chk_freqence_120hz())
                    {
                        DBG_INFO(("<MENU> %d:Not support viewport with 120Hz\n", __LINE__));
                        return MENUR_OK;
                    }

#ifdef APP_MENU_MMP_COEXIST
                    MMP_BE_BROWSER_STATUS_T     e_mmp_browse_status = MMP_BE_BROWSER_STATUS_NONE;

                    e_mmp_browse_status = a_mmp_be_get_browser_status();

                    DBG_INFO(("\n===e_mmp_browse_status=%d===\n", e_mmp_browse_status));

                    if ((MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status()) &&
                        ((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING != e_mmp_browse_status) &&
                        (MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING != e_mmp_browse_status) &&
                        (MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING != e_mmp_browse_status)&&
                        (MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING != e_mmp_browse_status)))
                    {
                        DBG_INFO(("\n===BTN_BLUE do nothing===\n"));
                        /* do nothing */
                        return MENUR_OK;
                    }
                    else
#endif
                    {
                        INT32 i4_ret;
                        UINT8 ui1_sts = ICL_VIEWPORT_LAST_REQ_FAIL;

                        if (!a_cfg_is_able_to_apply_viewport ())
                        {
                            ui1_sts = ICL_VIEWPORT_LAST_REQ_FAIL;
                            i4_ret = a_icl_set (
                                ICL_MAKE_ID(ICL_GRPID_VIEWPORT, ICL_RECID_VIEWPORT_LAST_REQ_STS),
                                (VOID *) &ui1_sts,
                                ICL_RECID_VIEWPORT_LAST_REQ_STS_SIZE);
                        }
                        else
                        {
                            ui1_sts = ICL_VIEWPORT_LAST_REQ_SUCCEED;
                            i4_ret = a_icl_set (
                                ICL_MAKE_ID(ICL_GRPID_VIEWPORT, ICL_RECID_VIEWPORT_LAST_REQ_STS),
                                (VOID *) &ui1_sts,
                                ICL_RECID_VIEWPORT_LAST_REQ_STS_SIZE);

                            a_cfg_set_next_viewport ();
                            a_cfg_update_viewport ();
                        }

                        DBG_INFO(("i4_ret=%d\n", i4_ret));

                        menu_pm_refresh();
                        menu_pm_repaint();
                    }
                }
                else
                {
                #ifdef APP_MENU_MMP_COEXIST
                    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
                    {
                        a_amb_resume_app (MMP_NAME);
                    }
                    else
                #endif
                    {
                        /* Exit the menu  */
                        menu_leave(FALSE,0);
                    }
                }
                break;

            case BTN_RETURN:
            {
                if (menu_page_is_in_list_subpage_state())
                {
                    menu_page_tree_help_tip_back_proc();
                }
                else
                {
                    _help_tip_custom_page_proc_fct(h_widget, ui4_msg, param1, param2, &b_processed);

                    if (b_processed)
                    {
                        return HELP_TIPR_OK;
                    }

                    menu_nav_back();
                }

                return HELP_TIPR_OK;
            }

            default:
                /* do nothing */
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

#ifdef APP_HDR_SUPPORT
BOOL  menu_page_get_dolby_vision_visible(VOID)
{
    return b_doly_vision_icon_img_visible;
}

INT32 menu_doly_vision_logo_show_repaint(BOOL b_show_status, BOOL b_repaint)
{
    if (b_doly_vision_icon_img_visible != b_show_status)
    {
        menu_doly_vision_logo_show(b_show_status);
        if (b_repaint)
        {
            MENU_LOG_ON_FAIL(c_wgl_repaint(h_doly_vision_icon_img, NULL, TRUE));
        }
    }
    return MENUR_OK;
}

INT32 menu_doly_vision_logo_show(BOOL b_show_status)
{
    INT32 i4_ret = 0;

    b_doly_vision_icon_img_visible = b_show_status;

    if(b_show_status)
    {
        MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_doly_vision_icon_img, WGL_SW_NORMAL));
        i4_ret = c_wgl_insert(h_doly_vision_icon_img,
                              NULL_HANDLE,
                              WGL_INSERT_TOPMOST,
                              WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
        //MENU_LOG_ON_FAIL(c_wgl_float(h_doly_vision_icon_img,TRUE,0));
     }
    else
    {
       MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_doly_vision_icon_img, WGL_SW_HIDE));
       //MENU_LOG_ON_FAIL(c_wgl_float(h_doly_vision_icon_img,FALSE,0));
    }
    return MENUR_OK;
}


#define MENU_DEBUG_DOLBY_LOGO   0

#if( MENU_DEBUG_DOLBY_LOGO )
UINT32 g_MENU_u32DolbyIcon_x = 0;
UINT32 g_MENU_u32DolbyIcon_y = 0;
UINT32 g_MENU_u32DolbyIcon_w = 0;
UINT32 g_MENU_u32DolbyIcon_h = 0;

void Menu_ParseFileSetVar(const char* pcVarName, unsigned int uiVal)
{
    //DBG_LOG_PRINT(("[MENU][DOLBY]Menu_ParseFileSetVar(%s, %u)\n", pcVarName, uiVal));

    if( 0 == strcmp("g_MENU_u32DolbyIcon_x", pcVarName) )
    {
        //printf(" Found ==> VarName=%s, uiVal=%d\n", pcVarName, uiVal);
        DBG_LOG_PRINT(("[MENU][DOLBY] Set %s = %u\n", pcVarName, uiVal ));
        g_MENU_u32DolbyIcon_x = uiVal;
    }
    else if( 0 == strcmp("g_MENU_u32DolbyIcon_y", pcVarName) )
    {
        //printf(" Found ==> VarName=%s, uiVal=%d\n", pcVarName, uiVal);
        DBG_LOG_PRINT(("[MENU][DOLBY] Set %s = %u\n", pcVarName, uiVal ));
        g_MENU_u32DolbyIcon_y = uiVal;
    }
    else if( 0 == strcmp("g_MENU_u32DolbyIcon_w", pcVarName) )
    {
        //printf(" Found ==> VarName=%s, uiVal=%d\n", pcVarName, uiVal);
        DBG_LOG_PRINT(("[MENU][DOLBY] Set %s = %u\n", pcVarName, uiVal ));
        g_MENU_u32DolbyIcon_w = uiVal;
    }
    else if( 0 == strcmp("g_MENU_u32DolbyIcon_h", pcVarName) )
    {
        //printf(" Found ==> VarName=%s, uiVal=%d\n", pcVarName, uiVal);
        DBG_LOG_PRINT(("[MENU][DOLBY] Set %s = %u\n", pcVarName, uiVal ));
        g_MENU_u32DolbyIcon_h = uiVal;
    }
}
#endif

/*
typedef enum {
    MENU_DOLBY_LOGO_POS_PICTURE,
    MENU_DOLBY_LOGO_POS_PICTURE_MODE,
    MENU_DOLBY_LOGO_POS_COLOR_CALI, // For Menu/Picture/Advanced Picture/color Calibration
} EnuMenuDolbyLogoPosition;
*/
INT32 menu_doly_vision_resize_logo(EnuMenuDolbyLogoPosition eMenuDolbyLogoPos)
{
    GL_RECT_T   t_rect;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

#if( MENU_DEBUG_DOLBY_LOGO )
    DBG_LOG_PRINT(("[MENU][DOLBY]menu_doly_vision_resize_logo(%d)\n", eMenuDolbyLogoPos ));
#endif

    if( eMenuDolbyLogoPos == MENU_DOLBY_LOGO_POS_PICTURE ) // For menu picture
    {
        // For menu picture
    #if MENU_DOLBY_LOGO_TEST_NEW_SIZE // todo
        #define MENU_DOLBY_ICON_1_H_START 250
        #define MENU_DOLBY_ICON_1_V_START 128
        #define MENU_DOLBY_ICON_1_WIDTH   108//120
        #define MENU_DOLBY_ICON_1_HIGH    45//50
    #else
        #define MENU_DOLBY_ICON_1_H_START 200 //209
        #define MENU_DOLBY_ICON_1_V_START 120

        #define MENU_DOLBY_ICON_1_WIDTH   233
        #define MENU_DOLBY_ICON_1_HIGH    64
    #endif

        UINT32 u32DolbyIcon_x = MENU_DOLBY_ICON_1_H_START; //CONTENT_X + 269-120;;
        UINT32 u32DolbyIcon_y = MENU_DOLBY_ICON_1_V_START; //120;
        UINT32 u32DolbyIcon_w = MENU_DOLBY_ICON_1_WIDTH; // 233
        UINT32 u32DolbyIcon_h = MENU_DOLBY_ICON_1_HIGH; // 64

        t_rect.i4_left   = u32DolbyIcon_x;
        t_rect.i4_right  = t_rect.i4_left + u32DolbyIcon_w;
        t_rect.i4_top    = u32DolbyIcon_y;
        t_rect.i4_bottom = t_rect.i4_top + u32DolbyIcon_h;

    #if( MENU_DEBUG_DOLBY_LOGO ) // For fine-tune
        DBG_LOG_PRINT(("[MENU][DOLBY]{%s: %s: %d} 2 rect(%d, %d, %d, %d)\n", __FILE__, __FUNCTION__,__LINE__,
                t_rect.i4_left, t_rect.i4_right, t_rect.i4_top, t_rect.i4_bottom ));

        g_MENU_u32DolbyIcon_x = 0;
        g_MENU_u32DolbyIcon_y = 0;
        g_MENU_u32DolbyIcon_w = 0;
        g_MENU_u32DolbyIcon_h = 0;

        AppTV_ParseDgbFile( "/data/menu_debug.txt", Menu_ParseFileSetVar );

        if( g_MENU_u32DolbyIcon_x )
            u32DolbyIcon_x = g_MENU_u32DolbyIcon_x;
        if( g_MENU_u32DolbyIcon_y )
            u32DolbyIcon_y = g_MENU_u32DolbyIcon_y;
        if( g_MENU_u32DolbyIcon_w )
            u32DolbyIcon_w = g_MENU_u32DolbyIcon_w;
        if( g_MENU_u32DolbyIcon_h )
            u32DolbyIcon_h = g_MENU_u32DolbyIcon_h;

        t_rect.i4_left   = u32DolbyIcon_x;
        t_rect.i4_right  = t_rect.i4_left + u32DolbyIcon_w;
        t_rect.i4_top    = u32DolbyIcon_y;
        t_rect.i4_bottom = t_rect.i4_top + u32DolbyIcon_h;
    #endif
    }
    else if( MENU_DOLBY_LOGO_POS_PICTURE_MODE == eMenuDolbyLogoPos )
    {
        // For menu-picture mode
        #define MENU_DOLBY_ICON_2_H_START 260
        #define MENU_DOLBY_ICON_2_V_START 40
        #define MENU_DOLBY_ICON_2_WIDTH   233
        #define MENU_DOLBY_ICON_2_HIGH    64

        UINT32 u32DolbyIcon_x = MENU_DOLBY_ICON_2_H_START; // 260
        UINT32 u32DolbyIcon_y = MENU_DOLBY_ICON_2_V_START; // 40;
        UINT32 u32DolbyIcon_w = MENU_DOLBY_ICON_2_WIDTH; // 233
        UINT32 u32DolbyIcon_h = MENU_DOLBY_ICON_2_HIGH; // 64

        t_rect.i4_left   = u32DolbyIcon_x;
        t_rect.i4_right  = t_rect.i4_left + u32DolbyIcon_w;
        t_rect.i4_top    = u32DolbyIcon_y;
        t_rect.i4_bottom = t_rect.i4_top + u32DolbyIcon_h;

    #if( MENU_DEBUG_DOLBY_LOGO ) // For fine-tune
        DBG_LOG_PRINT(("[MENU][DOLBY]{%s: %s: %d} 2 rect(%d, %d, %d, %d)\n", __FILE__, __FUNCTION__,__LINE__,
            t_rect.i4_left, t_rect.i4_right, t_rect.i4_top, t_rect.i4_bottom ));

        g_MENU_u32DolbyIcon_x = 0;
        g_MENU_u32DolbyIcon_y = 0;
        g_MENU_u32DolbyIcon_w = 0;
        g_MENU_u32DolbyIcon_h = 0;

        AppTV_ParseDgbFile( "/data/menu_debug2.txt", Menu_ParseFileSetVar );

        if( g_MENU_u32DolbyIcon_x )
            u32DolbyIcon_x = g_MENU_u32DolbyIcon_x;
        if( g_MENU_u32DolbyIcon_y )
            u32DolbyIcon_y = g_MENU_u32DolbyIcon_y;
        if( g_MENU_u32DolbyIcon_w )
            u32DolbyIcon_w = g_MENU_u32DolbyIcon_w;
        if( g_MENU_u32DolbyIcon_h )
            u32DolbyIcon_h = g_MENU_u32DolbyIcon_h;

        t_rect.i4_left   = u32DolbyIcon_x;
        t_rect.i4_right  = t_rect.i4_left + u32DolbyIcon_w;
        t_rect.i4_top    = u32DolbyIcon_y;
        t_rect.i4_bottom = t_rect.i4_top + u32DolbyIcon_h;
    #endif
    }
    else if( MENU_DOLBY_LOGO_POS_COLOR_CALI == eMenuDolbyLogoPos )
    {
        // Use different icon! => Do nothing
        // Fix coverity-4879205: Missing return statement
        return MENUR_OK;
    }
    else
    {
        return MENUR_INV_ARG;
    }


#if( MENU_DEBUG_DOLBY_LOGO ) // For fine-tune
    DBG_LOG_PRINT(("[MENU][DOLBY]{%s: %d}h_doly_vision_icon_img:0x%X, --3 rect(%d, %d, %d, %d)\n", __FUNCTION__,__LINE__, (unsigned int)h_doly_vision_icon_img,
        t_rect.i4_left, t_rect.i4_right, t_rect.i4_top, t_rect.i4_bottom ));
#endif

    MENU_LOG_ON_FAIL(c_wgl_move(h_doly_vision_icon_img, &t_rect, WGL_NO_AUTO_REPAINT));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_dolby_visio_logo_init
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
static INT32 menu_dolby_vision_logo_init(VOID)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;

#if( MENU_DEBUG_DOLBY_LOGO )
    DBG_LOG_PRINT(("[MENU][DOLBY]{%s: %s: %d} \n", __FILE__, __FUNCTION__,__LINE__));
#endif

#if MENU_DOLBY_LOGO_TEST_NEW_SIZE
    SET_RECT_BY_SIZE(&t_rect, HELP_TIP_FRAME_X + 43, HELP_TIP_FRAME_Y, 108, 45) ;
#else
    SET_RECT_BY_SIZE(&t_rect, HELP_TIP_FRAME_X + 43, HELP_TIP_FRAME_Y, 116, 43) ;
#endif

    i4_ret = c_wgl_create_widget (h_frm_main,
                                HT_WGL_WIDGET_ICON,
                                WGL_CONTENT_ICON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID *)WGL_STL_GL_NO_BK,
                                NULL,
                                &h_doly_vision_icon_img);
    MENU_LOG_ON_FAIL (i4_ret);

    /* set icon image buffer */

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_dolby_vision_icon;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_dolby_vision_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_dolby_vision_icon;

    i4_ret = c_wgl_do_cmd (h_doly_vision_icon_img,
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK(WGL_IMG_FG),
                                WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL (i4_ret);

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd (h_doly_vision_icon_img,
                                WGL_CMD_ICON_SET_ALIGN,
                                (VOID*)WGL_AS_CENTER_CENTER,
                                NULL);
    MENU_LOG_ON_FAIL (i4_ret);

    i4_ret = c_wgl_set_visibility (h_doly_vision_icon_img, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL (i4_ret);

    return MENUR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: menu_pm_init
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
INT32 menu_pm_init(VOID)
{
    INT32 i4_ret;

    e_pm_cond = PM_COND_NOT_INIT;

    /* Init color */
    i4_ret = menu_init_color();
    MENU_CHK_FAIL(i4_ret);

    /* Init images */
    i4_ret = menu_init_image();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = wdk_digit_pad_init_image();
    MENU_CHK_FAIL(i4_ret);
    /* Init the current language */
    /* As the pm init phase, always set the language to 0 because langmap
       maybe changed in menu_custom_init().
       We postpone the change language to the final state of initialization */
    ui2_g_menu_curr_lang = 0;

    /* Init the widgets */
    i4_ret = _init_canvas();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _init_frm_root();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _init_frm_main();
    MENU_CHK_FAIL(i4_ret);

    /*Table Frm*/
    i4_ret = _init_titlebar();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _init_backbar();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _init_title_frm();
    MENU_CHK_FAIL(i4_ret);

    /*Fake to hide Homebar icon*/
    i4_ret = _init_main_title_text();
    MENU_CHK_FAIL(i4_ret);

    /* Init Help tip */
    {
        HELP_TIP_INIT_T  t_help_tip_init = {0};

        t_help_tip_init.h_parent = h_frm_main; /* Menu animation contains help tips*/
        t_help_tip_init.font_name = menu_font_name();
        t_help_tip_init.pf_timeout_notify = _help_tip_timer_nfy;

        SET_RECT_BY_SIZE(&t_help_tip_init.t_frame_rect,
                         HELP_TIP_FRAME_X,
                         HELP_TIP_FRAME_Y ,
                         HELP_TIP_FRAME_W,
                         HELP_TIP_FRAME_H );

        i4_ret = a_help_tip_init(&t_help_tip_init, &h_menu_help_tip);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_insert(h_menu_help_tip, NULL_HANDLE, WGL_INSERT_TOPMOST, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    {
        INT32                       i4_ret;
        GL_RECT_T                   t_rect;
        WGL_IMG_INFO_T              t_img_info;
        SET_RECT_BY_SIZE(&t_rect, HELP_TIP_FRAME_X + 30, HELP_TIP_FRAME_Y, 34, 30) ;

        i4_ret = c_wgl_create_widget (h_frm_main,
                                    HT_WGL_WIDGET_ICON,
                                    WGL_CONTENT_ICON_DEF,
                                    WGL_BORDER_NULL,
                                    &t_rect,
                                    NULL,
                                    255,
                                    (VOID *)WGL_STL_GL_NO_BK,
                                    NULL,
                                    &h_energy_start_icon_img);
        MENU_LOG_ON_FAIL (i4_ret);

        /* set icon image buffer */

        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_energy_Star;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_energy_Star;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_energy_Star;

        i4_ret = c_wgl_do_cmd (h_energy_start_icon_img,
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK(WGL_IMG_FG),
                                WGL_PACK(&t_img_info));
        MENU_LOG_ON_FAIL (i4_ret);

        /* set icon alignment */
        i4_ret = c_wgl_do_cmd (h_energy_start_icon_img,
                                WGL_CMD_ICON_SET_ALIGN,
                                (VOID*)WGL_AS_CENTER_CENTER,
                                NULL);
        MENU_LOG_ON_FAIL (i4_ret);
   }

    // if not need shadow item (ui spec 3.1 req), re-point shadow handle to help tip handle for float help tip feature !
    h_last_shadow_item = h_menu_help_tip;

    /* data init */
    ui4_page_num = 0;
    ui2_tab_num = 0;
#ifdef APP_MENU_ONE_TAB_MODE
    b_one_tab_mode = TRUE;
#else
    b_one_tab_mode = FALSE;
#endif

#ifdef APP_MENU_VERTICAL_TABS
    b_tab_vert = TRUE;
#else
    b_tab_vert = FALSE;
#endif
    ui2_tab_crnt = PM_TABIDX_NONE;
    ui4_page_num = 0;
    ui4_page_crnt = PM_PAGEID_NONE;
    ui2_nav_stack_top = 0;
    ui4_page_factory = PM_PAGEID_NONE;
    _menu_set_show_enger_start_by_mode_name();

    menu_help_tip_key_clrreg();

    /* Set the visibility */
    i4_ret = c_wgl_set_visibility(h_frm_main,WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);
    /* make icon invisible */
    i4_ret = c_wgl_set_visibility (h_energy_start_icon_img, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL (i4_ret);

#ifdef APP_HDR_SUPPORT
        menu_dolby_vision_logo_init();
#endif

    /* change state */
    e_pm_cond = PM_COND_HIDE;
    menu_help_tip_keytip_set_proc(_help_tip_proc_fct,_help_tip_proc_fct);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_get_cnt_frm
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
INT32 menu_pm_deinit(VOID)
{
    /* change state */
    e_pm_cond = PM_COND_NOT_INIT;
    c_timer_delete(h_srcl_title_timer);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_pm_page_destroy
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
INT32 menu_pm_page_create(
    MENU_PAGE_FCT_TBL_T* pt_page_fct_tbl,
    VOID*   pv_create_data,
    UINT32* pui4_page_id
){
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_entry;

    if(pt_page_fct_tbl == NULL  ||
       pui4_page_id == NULL)
    {
        return MENUR_INV_ARG;
    }

    /* allocate entry */
    pt_page_entry = (PM_PAGE_ENTRY_T*)c_mem_alloc(sizeof(PM_PAGE_ENTRY_T));
    if(pt_page_entry == NULL)
    {
        return MENUR_OUT_OF_MEMORY;
    }

    /* initiate the page entry */
    c_memcpy(&pt_page_entry->t_fct_tbl,
             pt_page_fct_tbl,
             sizeof(MENU_PAGE_FCT_TBL_T));
    pt_page_entry->pv_page_data = NULL;
    pt_page_entry->ui4_page_id = ui4_page_num++;
    pt_page_entry->e_state = MENU_PAGE_STATE_NEW;
    pt_page_entry->h_cnt_frm = NULL_HANDLE;
    pt_page_entry->pf_wdgt_proc = NULL;

    /* create content frame */
    i4_ret = _page_create_cnt_frm(&pt_page_entry->h_cnt_frm);
    if(i4_ret != MENUR_OK)
    {
        c_mem_free(pt_page_entry);
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* attach data */
    i4_ret = c_wgl_do_cmd(pt_page_entry->h_cnt_frm,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_page_entry),
                          NULL);
    if(i4_ret != WGLR_OK)
    {
        c_mem_free(pt_page_entry);
        return MENUR_FAIL;
    }

    DLIST_INSERT_TAIL(pt_page_entry, &t_page_list, t_link);

    i4_ret = pt_page_entry->t_fct_tbl.pf_menu_page_create(pt_page_entry->ui4_page_id,
                                                          pv_create_data);
    if(i4_ret != MENUR_OK)
    {
        DLIST_REMOVE(pt_page_entry, &t_page_list, t_link);
        c_mem_free(pt_page_entry);
        ui4_page_num --;
        return MENUR_PAGE_INIT_FAIL;
    }

    *pui4_page_id = pt_page_entry->ui4_page_id;
    pt_page_entry->e_state = MENU_PAGE_STATE_HIDE;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_page_destroy
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
INT32 menu_pm_page_destroy(
    UINT32 ui4_page_id
){
    /* not implemented */
    return MENUR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_add_tab
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
INT32 menu_pm_add_tab(
    UINT32 ui4_page_id,
    WGL_HIMG_TPL_T  h_img_normal,
    WGL_HIMG_TPL_T  h_img_hlt,
    WGL_HIMG_TPL_T  h_img_sel,
    WGL_HIMG_TPL_T  h_img_disable,
    UINT16* pui2_idx
){
    INT32 i4_ret;
    UINT16 ui2_idx;
    PM_PAGE_ENTRY_T* pt_page_entry;

    if(ui2_tab_num >= MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    if(pui2_idx == NULL)
    {
        return MENUR_INV_ARG;
    }

    ui2_idx = ui2_tab_num++;

    i4_ret = _page_get_page_entry_by_id(ui4_page_id,
                                        &pt_page_entry);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    at_tabs[ui2_idx].pt_page= pt_page_entry;
    at_tabs[ui2_idx].b_enabled = TRUE;
    i4_ret = _tab_create_widget(h_frm_tb,
                                ui2_idx,
                                h_img_normal,
                                h_img_hlt,
                                h_img_sel,
                                h_img_disable,
                                &at_tabs[ui2_idx].h_btn,
                                &at_tabs[ui2_idx].t_rect);
    if(i4_ret != MENUR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }
    *pui2_idx = ui2_idx;

    /* Set the tab to visible as default */
    at_tabs[ui2_idx].b_hidden = FALSE;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_remove_tab
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
INT32 menu_pm_remove_tab(
    UINT16 ui2_idx
){
    /* not implemented */
    return MENUR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_enable_tab
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
INT32 menu_pm_enable_tab(
    UINT16  ui2_idx,
    BOOL    b_enable
){
    INT32   i4_ret;

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    /* b_enable == FALSE &&
       The current tab is focused one, search the first tab and focus it */
    if(b_enable == FALSE && ui2_idx == ui2_tab_crnt)
    {
        UINT16 ui2_i;
        for(ui2_i = 0; ui2_i < ui2_tab_num; ui2_i++)
        {
            if(at_tabs[ui2_i].b_enabled == TRUE &&
               at_tabs[ui2_i].b_hidden == FALSE &&
               ui2_idx != ui2_i)
            {
                break;
            }
        }

        if(ui2_idx == ui2_tab_num)
        {
            DBG_ERROR(("<MENU>No tab or no tab enabled\r\n"));
            return MENUR_INV_STATE;
        }

        i4_ret = _tab_focus_idx(ui2_i);
        MENU_CHK_FAIL(i4_ret);

        e_pm_cond = PM_COND_TAB;
    }

    i4_ret = _tab_enable(ui2_idx, b_enable);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_hide_tab
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
INT32 menu_pm_hide_tab(
    UINT16  ui2_idx,
    BOOL    b_hidden
){
    INT32   i4_ret;

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    /* b_hidden == TRUE &&
       The current tab is focused one, search the first tab and focus it */
    if(b_hidden == TRUE && ui2_idx == ui2_tab_crnt)
    {
        UINT16 ui2_i;
        for(ui2_i = 0; ui2_i < ui2_tab_num; ui2_i++)
        {
            if(at_tabs[ui2_i].b_enabled == TRUE &&
               at_tabs[ui2_i].b_hidden == FALSE &&
               ui2_idx != ui2_i)
            {
                break;
            }
        }

        if(ui2_idx == ui2_tab_num)
        {
            DBG_ERROR(("<MENU>No tab or no tab enabled\r\n"));
            return MENUR_INV_STATE;
        }

        i4_ret = _tab_focus_idx(ui2_i);
        MENU_CHK_FAIL(i4_ret);

        e_pm_cond = PM_COND_TAB;
    }

    i4_ret = _tab_hide(ui2_idx, b_hidden);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_pm_get_tab_num
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
INT32 menu_pm_get_tab_num(
    UINT16* pui2_tab_num
){
    if(pui2_tab_num == NULL)
    {
        return MENUR_FAIL;
    }

    *pui2_tab_num = ui2_tab_num;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_show
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
INT32 menu_pm_show(VOID)
{
    INT32 i4_ret;
    UINT32 tick = c_os_get_sys_tick();

    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    a_tv_net_OSD_appear();
    a_tv_net_send_cmd(":dtv_app_mtk,netflix,:ufocus=netflix\n");

    i4_ret = menu_pm_show_first_tab();
    MENU_LOG_ON_FAIL(i4_ret);

    MENU_DEBUG_TIME( DBG_LOG_PRINT(("[MENU][MNGR][%s %d] cost %d ms\n", __FUNCTION__,__LINE__,c_os_get_sys_tick_period()* (c_os_get_sys_tick() -tick))); );

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_show_with_tab
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
INT32 menu_pm_show_with_tab(
    UINT16 ui2_tab_idx
){
    INT32                   i4_ret;
    UINT8                   ui1_alpha;
    UINT8                   ui1_i;

    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui2_tab_idx:%d, ui2_tab_num:%d, e_pm_cond:%d\n",
        __FUNCTION__, __LINE__, ui2_tab_idx, ui2_tab_num, e_pm_cond )); );

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    if(ui2_tab_idx >= ui2_tab_num)
    {
        return MENUR_INV_ARG;
    }

    if(e_pm_cond == PM_COND_NOT_INIT)
    {
        return MENUR_INV_STATE;
    }

    if(e_pm_cond == PM_COND_TAB ||
       e_pm_cond == PM_COND_PAGE)
    {
        return MENUR_OK;
    }

    menu_main_set_visibility(TRUE);

    /* Send the resume update reason*/
    menu_pm_update_all(MENU_PAGE_UMASK_RESUME);

    i4_ret = _tab_focus_idx(ui2_tab_idx);
    MENU_CHK_FAIL(i4_ret);


    //DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} b_using_fading:%d\n", __FUNCTION__, __LINE__, b_using_fading ));

    e_pm_cond = PM_COND_TAB;
    do
    {
        if(b_using_fading && MENU_PM_FADE_STEP > 1)
        {
            c_gl_plane_set_alpha(h_plane, 0);
        }
        DBG_INFO(("[MENU][%s %d] b_one_tab_mode = %d,b_is_hot_key_enter = %d\n",__FUNCTION__,__LINE__,b_one_tab_mode,t_g_menu_common.b_is_hot_key_enter));

        //DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} b_one_tab_mode = %d, b_is_hot_key_enter = %d \n", __FUNCTION__, __LINE__, b_one_tab_mode,t_g_menu_common.b_is_hot_key_enter ));

        if (t_g_menu_common.b_is_hot_key_enter)
        {
            MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][MNGR][KEY]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

             if(BTN_CC      == t_g_menu_common.ui4_key_code ||
                BTN_NETWORK == t_g_menu_common.ui4_key_code
        #if( MENU_SUPPORT_HOT_KEY_PIC|| defined(APP_SUPPORT_PIC_HOT_KEY) )
               || BTN_P_EFFECT == t_g_menu_common.ui4_key_code
        #endif
        #if( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO)
               || BTN_ASPECT == t_g_menu_common.ui4_key_code
        #endif
               )
            {
                a_tv_net_send_cmd("\n:am,dtv_app_mtk,:resume=menu\n");

            #if( MENU_SUPPORT_HOT_KEY_PIC )
                if( BTN_P_EFFECT == t_g_menu_common.ui4_key_code )
                {
                    MENU_DEBUG_KEY_PIC(
                        DBG_LOG_PRINT(("[MENU][MNGR][KEY_PIC]{%s,%d} call menu_jump_to_hot_key_page() \n", __FUNCTION__, __LINE__ )); );
                }
            #endif
            #if( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO )
                if( BTN_ASPECT == t_g_menu_common.ui4_key_code )
                {
                    MENU_DEBUG_KEY_ASPECT_RATIO(
                        DBG_LOG_PRINT(("[MENU][MNGR][KEY][ASPECT]{%s,%d} call menu_jump_to_hot_key_page() \n", __FUNCTION__, __LINE__ )); );
                }
            #endif

                i4_ret = menu_jump_to_hot_key_page();
                MENU_BREAK_ON_FAIL(i4_ret);

                c_wgl_set_visibility(h_frm_root, WGL_SW_NORMAL);
                i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                                (VOID*)&t_g_rect_out,
                                                (VOID*)&t_g_rect_in);
                MENU_BREAK_ON_FAIL(i4_ret);
                b_hot_key_page_with_animation = TRUE;
            }
            else
            {
                b_hot_key_page_with_animation = FALSE;
                c_wgl_set_visibility(h_frm_root, WGL_SW_NORMAL);
                i4_ret = menu_jump_to_hot_key_page();
                MENU_BREAK_ON_FAIL(i4_ret);
            }
        }
        else if(b_one_tab_mode)
        {
            //DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui2_tab_crnt:%d\n", __FUNCTION__, __LINE__, ui2_tab_crnt ));

            if(ui2_tab_crnt >= MENU_PM_MAX_TAB_NUM)
            {
                break;
            }

            /* set the root frame visible*/
            c_wgl_set_visibility(h_frm_root, WGL_SW_NORMAL);

            if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
            {
                c_wgl_float(h_frm_main, TRUE, FALSE);

                menu_nav_go(ui4_g_menu_page_main_menu, NULL);

                /* Do fade out animation */
                i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                                (VOID*)&t_g_rect_out,
                                                (VOID*)&t_g_rect_in);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                MENU_DEBUG_TIME_CHECK_POINT();
                /* Do fade out animation */
                i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                                (VOID*)&t_g_rect_out,
                                                (VOID*)&t_g_rect_in);
                MENU_LOG_ON_FAIL(i4_ret);

                MENU_DEBUG_TIME_CHECK_POINT();

                i4_ret = menu_nav_go(at_tabs[ui2_tab_crnt].pt_page->ui4_page_id,
                                     NULL);
                MENU_BREAK_ON_FAIL(i4_ret);

                MENU_DEBUG_TIME_CHECK_POINT();
            }
        }
        else
        {
            /* show the root frame visible*/
            i4_ret = c_wgl_show(h_frm_root, WGL_SW_NORMAL);
            MENU_BREAK_ON_FAIL(i4_ret);
        }

        if(b_using_fading)
        {
            ui1_i = 1;
            while(TRUE)
            {
                ui1_alpha = (UINT8)(ui1_osd_alpha *ui1_i / MENU_PM_FADE_STEP);
                c_gl_plane_set_alpha(h_plane,  ui1_alpha);
                if(ui1_i >= MENU_PM_FADE_STEP)
                {
                    break;
                }
                ui1_i++;
                c_thread_delay(MENU_PM_FADE_DELAY / MENU_PM_FADE_STEP);
            }
        }
    }while(0);

    if(i4_ret != 0 && b_using_fading)
    {
        c_gl_plane_set_alpha(h_plane, 255);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_show_with_tab_ex
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
INT32 menu_pm_show_with_tab_ex(UINT16   ui2_tab_idx,
                               BOOL     b_show)
{
    INT32   i4_ret;

    if(ui2_tab_idx >= ui2_tab_num)
    {
        return MENUR_INV_ARG;
    }

    if(e_pm_cond == PM_COND_NOT_INIT)
    {
        return MENUR_INV_STATE;
    }

    menu_main_set_visibility(TRUE);

    /* Send the resume update reason*/
    menu_pm_update_all(MENU_PAGE_UMASK_RESUME);

    i4_ret = _tab_focus_idx(ui2_tab_idx);
    MENU_CHK_FAIL(i4_ret);

    e_pm_cond = PM_COND_TAB;

    if(b_show)
    {
        /* show the root frame visible*/
        i4_ret = c_wgl_show(h_frm_root, WGL_SW_NORMAL);
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
       /* show the root frame visible*/
       i4_ret = c_wgl_set_visibility(h_frm_root, WGL_SW_NORMAL);
       MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_show_first_tab
 *
 * Description:
 *      This function will show the first enabled tab.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_pm_show_first_tab(VOID)
{
    UINT16 ui2_idx;

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    for(ui2_idx = 0; ui2_idx < ui2_tab_num; ui2_idx++)
    {
        if(at_tabs[ui2_idx].b_enabled == TRUE &&
           at_tabs[ui2_idx].b_hidden == FALSE
          )
        {
            break;
        }
    }

    if(ui2_idx == ui2_tab_num)
    {
        DBG_ERROR(("<MENU>No tab or no tab enabled\r\n"));
        return MENUR_INV_STATE;
    }
    else
    {
        DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} call menu_pm_show_with_tab(%d)\n",
            __FUNCTION__, __LINE__, ui2_idx )); );

        return menu_pm_show_with_tab(ui2_idx);
    }
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_show_last_tab
 *
 * Description:
 *      This function will show the last enabled tab.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_pm_show_last_tab(VOID)
{
    UINT16 ui2_idx;

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    for(ui2_idx = (UINT16)(ui2_tab_num-1);
         ui2_idx != 0xFFFF;
         ui2_idx--)
    {
        if(at_tabs[ui2_idx].b_enabled == TRUE &&
           at_tabs[ui2_idx].b_hidden == FALSE
           )
        {
            break;
        }
    }

    if(ui2_idx == 0xFFFF)
    {
        DBG_ERROR(("<MENU>No tab or no tab enabed\r\n"));
        return MENUR_INV_STATE;
    }
    else
    {
        DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} call menu_pm_show_with_tab(%d)\n",
            __FUNCTION__, __LINE__, ui2_idx )); );

        return menu_pm_show_with_tab(ui2_idx);
    }
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_show_by_latest_tab
 *
 * Description:
 *      This function will show the latest tab when menu is hidden.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_pm_show_by_latest_tab(VOID)
{

    if(ui2_tab_crnt_keep >= MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    if( (at_tabs[ui2_tab_crnt_keep].b_enabled == FALSE) ||
        (at_tabs[ui2_tab_crnt_keep].b_hidden == TRUE) )
    {
        return menu_pm_show_first_tab();
    }

    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} call menu_pm_show_with_tab(ui2_tab_crnt_keep:%d)\n",
        __FUNCTION__, __LINE__, ui2_tab_crnt_keep )); );

    return menu_pm_show_with_tab(ui2_tab_crnt_keep);
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_show_by_latest_state
 *
 * Description:
 *      This function will show the latest state when menu is hidden.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_pm_show_by_latest_state(VOID)
{
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_entry;
    MENU_PAGE_HINT_T t_hint;

    if(e_pm_cond == PM_COND_NOT_INIT)
    {
        return MENUR_INV_STATE;
    }

    if(e_pm_cond == PM_COND_TAB ||
       e_pm_cond == PM_COND_PAGE)
    {
        return MENUR_OK;
    }

    menu_main_set_visibility(TRUE);


    /* Send the resume update reason*/
#ifdef APP_2K12_RETAIL_DEMO_MODE
        if((MENU_SHORT_CUT_STORE_MODE != a_get_cur_short_cur_key()) &&
            (MENU_SHORT_CUT_GUIDE_SETUP != a_get_cur_short_cur_key()))
        {
            /*After retail mode exit and go back to menu, the focus is go to the laset menu item */
            menu_pm_update_all(MENU_PAGE_UMASK_RESUME);
        }
#else
        if(MENU_SHORT_CUT_GUIDE_SETUP != a_get_cur_short_cur_key())
        {
            menu_pm_update_all(MENU_PAGE_UMASK_RESUME);
        }
#endif

    if(e_pm_cond_keep == PM_COND_TAB)
    {
        i4_ret = _tab_focus_idx(ui2_tab_crnt_keep);
        MENU_CHK_FAIL(i4_ret);

        e_pm_cond = PM_COND_TAB;

        /* show the root frame visible*/
        i4_ret = c_wgl_show(h_frm_root, WGL_SW_NORMAL);
        MENU_CHK_FAIL(i4_ret);

    }
    else if(e_pm_cond_keep == PM_COND_PAGE)
    {
        ui4_page_crnt = ui4_page_crnt_keep;
        ui2_tab_crnt = ui2_tab_crnt_keep;
        ui2_nav_stack_top = ui2_nav_stack_top_keep;
        e_pm_cond = e_pm_cond_keep;

        i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                            &pt_page_entry);
        MENU_CHK_FAIL(i4_ret);

        _page_show(pt_page_entry);

        t_hint.e_hint_type = MENU_PAGE_HT_BACK;
        _page_focus(pt_page_entry, &t_hint);

        /* show the root frame visible*/
        i4_ret = c_wgl_show(h_frm_root, WGL_SW_NORMAL);
        MENU_CHK_FAIL(i4_ret);

    }

    else
    {
        /* If current state != PM_COND_TAB   &&
              current state != PM_COND_PAGE, run default action */

        menu_pm_show();
    }


    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_show_by_factory_page
 *
 * Description:
 *      This function will show the menu and navigater go to factory menu.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_pm_show_by_factory_page(VOID)
{
    INT32   i4_ret;
    UINT16  ui2_idx;

    if(e_pm_cond == PM_COND_NOT_INIT)
    {
        return MENUR_INV_STATE;
    }

    if(e_pm_cond == PM_COND_TAB ||
       e_pm_cond == PM_COND_PAGE)
    {
        return MENUR_OK;
    }

    if(ui4_page_factory == PM_PAGEID_NONE)
    {
        return MENUR_INV_STATE;
    }

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    /* Search the first focusable page */
    for(ui2_idx = 0; ui2_idx < ui2_tab_num; ui2_idx++)
    {
        if(at_tabs[ui2_idx].b_enabled == TRUE &&
           at_tabs[ui2_idx].b_hidden == FALSE
          )
        {
            break;
        }
    }

    /* Set the root frame visiable */
    c_wgl_set_visibility(h_frm_root, WGL_SW_NORMAL);

    /* Set the main menu visiable */
    menu_main_set_visibility(TRUE);

    /* Change to TAB state */
    i4_ret = _tab_focus_idx(ui2_idx);
    MENU_CHK_FAIL(i4_ret);

    e_pm_cond = PM_COND_TAB;

    /* Navigate to factory page */
    i4_ret = menu_nav_go_to_factory_page();
    MENU_CHK_FAIL(i4_ret);

    /* Do fade out animation */
    {
        _menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_resume_show
 *
 * Description:
 *  This function is called when menu is resumed by menu_pm_request_resume_show().
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_pm_resume_show(VOID)
{
    INT32   i4_ret;
    UINT8   ui1_alpha;
    UINT8   ui1_i;

    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if(e_pm_cond == PM_COND_NOT_INIT ||
       e_pm_cond == PM_COND_TAB      ||
       e_pm_cond == PM_COND_PAGE)
    {
        return MENUR_INV_STATE;
    }

    if(b_is_resume_show == FALSE)
    {
        return MENUR_INV_STATE;
    }

    if(ui2_resume_show_tab_idx >= MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_ARG;
    }

    /* Reset b_is_resume_show */
    b_is_resume_show = FALSE;

    /* Check the tab state */
    if(at_tabs[ui2_resume_show_tab_idx].b_enabled == FALSE ||
       at_tabs[ui2_resume_show_tab_idx].b_hidden == TRUE)
    {
        return MENUR_INV_STATE;
    }



    /* Set the root frame visiable */
    c_wgl_set_visibility(h_frm_root, WGL_SW_NORMAL);

    /* Set the main menu visiable */
    menu_main_set_visibility(TRUE);

    /* Change to TAB state */
    i4_ret = _tab_focus_idx(ui2_resume_show_tab_idx);
    MENU_CHK_FAIL(i4_ret);

    e_pm_cond = PM_COND_TAB;

    do
    {
        if(b_using_fading && MENU_PM_FADE_STEP > 1)
        {
            c_gl_plane_set_alpha(h_plane, 0);
        }

        if(b_using_fading)
        {
            ui1_i = 1;
            while(TRUE)
            {
                ui1_alpha = (UINT8)(ui1_osd_alpha *ui1_i / MENU_PM_FADE_STEP);
                c_gl_plane_set_alpha(h_plane,  ui1_alpha);
                if(ui1_i >= MENU_PM_FADE_STEP)
                {
                    break;
                }
                ui1_i++;
                c_thread_delay(MENU_PM_FADE_DELAY / MENU_PM_FADE_STEP);
            }
        }

        /* Navigate to factory page */
        i4_ret = menu_nav_go_direct(ui2_resume_show_tab_idx,
                                    aui4_resume_show_pages,
                                    ui2_resume_show_page_num,
                                    NULL);
        MENU_CHK_FAIL(i4_ret);

    }while(0);

    if(i4_ret != 0 && b_using_fading)
    {
        c_gl_plane_set_alpha(h_plane, 255);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_is_resume_show
 *
 * Description:
 *  Check if it is in resume show state.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
BOOL menu_pm_is_resume_show(VOID)
{
    return b_is_resume_show;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_request_resume_show
 *
 * Description:
 *  Request to resume menu and navigate to a specific page.
 *  This function should be called when menu is in the MENU_COND_PAUSE state.
 *
 *  If (ui2_page_num == 0), it will resume menu and stay on the tab of ui2_tab_idx.
 *  If (ui2_page_num > 0), assume that the pages are (p1, p2, p3). It is equivalent to
 *  menu_pm_show_with_tab(ui2_tab_idx)
 *  => menu_nav_go(p1);
 *  => menu_nav_go(p2);
 *  => menu_nav_go(p3);
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_pm_request_resume_show(
    UINT16  ui2_tab_idx,
    UINT32* pui4_page_ids,
    UINT16  ui2_page_num)
{
    UINT16  ui2_i;

    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui2_tab_idx:%d, ui2_page_num:%d\n", __FUNCTION__, __LINE__, ui2_tab_idx, ui2_page_num )); );

    if(ui2_page_num > MENU_PM_MAX_NAV_SIZE)
    {
        return MENUR_INV_ARG;
    }

    if(ui2_page_num != 0 && pui4_page_ids == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(menu_get_cond() != MENU_COND_PAUSE)
    {
        return MENUR_INV_STATE;
    }

    ui2_resume_show_tab_idx  = ui2_tab_idx;
    ui2_resume_show_page_num = ui2_page_num;
    b_is_resume_show = TRUE;
    for(ui2_i = 0; ui2_i < ui2_page_num; ui2_i++)
    {
        aui4_resume_show_pages[ui2_i] = pui4_page_ids[ui2_i];
    }

    a_amb_resume_app(MENU_NAME);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_nav_to_main_page_
 *
 * Description:
 *  Navigation to first main page, but don`t show first main page
 *
 * Inputs:
 *  UINT8  ui1_hlt_idx: The index of item that should get focus
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_nav_to_main_page(UINT8  ui1_hlt_idx)
{
    INT32                   i4_ret;
    INT16                  ui2_idx;

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    for(ui2_idx = 0; ui2_idx < ui2_tab_num; ui2_idx++)
    {
        if(at_tabs[ui2_idx].b_enabled == TRUE &&
           at_tabs[ui2_idx].b_hidden == FALSE
          )
        {
            break;
        }
    }

    if(ui2_idx == ui2_tab_num)
    {
        DBG_ERROR(("<MENU>No tab or no tab enabled\r\n"));
        return MENUR_INV_STATE;
    }

    if(e_pm_cond == PM_COND_NOT_INIT)
    {
        return MENUR_INV_STATE;
    }

    if(e_pm_cond == PM_COND_TAB ||
        e_pm_cond == PM_COND_PAGE)
    {
        return MENUR_OK;
    }

    menu_main_set_visibility(TRUE);

    main_menu_set_hlt_index(ui1_hlt_idx);

    /* Send the resume update reason*/
    menu_pm_update_all(MENU_PAGE_UMASK_RESUME);
    // a_tv_net_OSD_appear();

    i4_ret = _tab_focus_idx(ui2_idx);
    MENU_CHK_FAIL(i4_ret);

    e_pm_cond = PM_COND_TAB;

    /* set the root frame visible*/
    c_wgl_set_visibility(h_frm_root, WGL_SW_NORMAL);
    i4_ret = menu_nav_go(ui4_g_menu_page_main_menu, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_short_cut_show
 *
 * Inputs:
 *      MENU_SHORT_CUT_T e_short_cut_key : The short cut key of target page
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern UINT32 ui4_g_menu_page_nw;
INT32 menu_pm_short_cut_show(MENU_SHORT_CUT_T e_short_cut_key)
{
    MENU_PAGE_HINT_T    t_hint;
    UINT8               ui1_hlt_indx;
    UINT32              aui4_page_ids_1[1] = {0};
    UINT32              *paui4_page_ids = NULL;
    INT32               i4_ret = 0;
    UINT8               ui1_size = 0;
    UINT32              ui4_tab_id = 0;

    switch(e_short_cut_key)
    {
        case MENU_SHORT_CUT_MMP_DEV_LIST:
        {
            ui1_hlt_indx = 0;
            aui4_page_ids_1[0] = ui4_g_menu_page_mmp_dev_list;

            paui4_page_ids = aui4_page_ids_1;
            ui1_size = 1;
            ui4_tab_id = 0;
        }
        break;
        case MENU_SHORT_CUT_MMP_MEDIA_TYPE:
        {
            ui1_hlt_indx = 0;
            aui4_page_ids_1[0] = ui4_g_menu_page_mmp_media_type;

            paui4_page_ids = aui4_page_ids_1;
            ui1_size = 1;
            ui4_tab_id = 0;
        }
        break;
        case MENU_SHORT_CUT_PAIR_WIFI_DEVICE:
        {
            ui1_hlt_indx = 0;
            aui4_page_ids_1[0] = menu_device_get_pageid(MENU_DEVICE_PAGE_PAIR_WIFI_DEVICE);

            paui4_page_ids = aui4_page_ids_1;
            ui1_size = 1;
            ui4_tab_id = 0;
        }
        break;
        case MENU_SHORT_CUT_DEVICE_SETTING:
        {
            if (a_cfg_custom_get_wifi_remote_support())
            {
                ui1_hlt_indx = 0;
                aui4_page_ids_1[0] = menu_device_get_pageid(MENU_DEVICE_PAGE_DEVICE_SETTING);

                paui4_page_ids = aui4_page_ids_1;
                ui1_size = 1;
                ui4_tab_id = 0;
            }
        }
        break;
#ifdef APP_2K12_RETAIL_DEMO_MODE
        case MENU_SHORT_CUT_STORE_MODE:
        {
            menu_pm_show_by_latest_state();

            a_tv_net_OSD_appear();

            _menu_anim_start_move_animation(h_frm_main,
                                    (VOID*)&t_g_rect_out,
                                    (VOID*)&t_g_rect_in);

            return MENUR_OK;
        }
        break;
#endif
        case MENU_SHORT_CUT_GUIDE_SETUP:
        {
            menu_pm_show_by_latest_state();

            a_tv_net_OSD_appear();

            _menu_anim_start_move_animation(h_frm_main,
                                    (VOID*)&t_g_rect_out,
                                    (VOID*)&t_g_rect_in);

            return MENUR_OK;
        }
        break;
        case MENU_SHORT_CUT_BT_HEADPHONES:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_BT_HEADPHONES);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_bt_headphones, NULL);

            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case MENU_SHORT_CUT_PICTURE:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_PIC);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_vid, NULL);

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case MENU_SHORT_CUT_AUDIO:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_AUD);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_aud, NULL);

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        /* only for shortcut from mmp. */
        case MENU_SHORT_CUT_NETWORK_PAGE:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_NETWORK);

            a_tv_net_OSD_appear();

            if (a_tv_custom_get_tos() == FALSE || a_tv_custom_get_privacy() == FALSE)
            {
                 menu_nav_go(ui4_g_menu_page_terms, NULL);
            }
            else
            {
                menu_nav_go(ui4_g_menu_page_nw, NULL);
            }

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case MENU_SHORT_CUT_TIMERS:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_TIMERS);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_slp, NULL);

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;

        }
        case MENU_SHORT_CUT_CHANNELS:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_TUNER_SET);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_channels, NULL);
            menu_page_tree_set_focus_item(ui4_g_menu_page_channels, ui2_item_page_ch_scan, TRUE);

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }

        case MENU_SHORT_CUT_SCAN_PAGE:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_TUNER_SET);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_channels, NULL);
            menu_page_tree_set_focus_item(ui4_g_menu_page_channels, ui2_item_page_ch_scan, TRUE);

            menu_nav_go(ui4_page_ch_scan, NULL);

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case MENU_SHORT_CUT_CLOSED_CAPTIONS:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_CC);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_cc, NULL);

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }

        case MENU_SHORT_CUT_INPUT_SETTINGS:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_DEVICES);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_device_setting, NULL);

            menu_show_backbar(TRUE, FALSE);

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);

            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case MENU_SHORT_CUT_SYSTEM:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_SYSTEM);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_setup, NULL);

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);

            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case MENU_SHORT_CUT_VER_INFO_PAGE:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_SYSTEM);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_setup, NULL);
            menu_page_tree_set_focus_item(ui4_g_menu_page_setup, ui2_item_page_ver_info, TRUE);

            menu_nav_go(ui4_g_menu_page_ver_info, NULL);

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case MENU_SHORT_CUT_POWER_MODE:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_SYSTEM);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_setup, NULL);
            menu_page_tree_set_focus_item(ui4_g_menu_page_setup, ui2_item_fast_boot, TRUE);


            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case MENU_SHORT_CUT_ACCESSIBILITY_PAGE:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_ACCESSIBILITY);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_page_accessibility, NULL);

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
       }
        case MENU_SHORT_CUT_RESET_ADMIN:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_SYSTEM);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_setup, NULL);
            menu_page_tree_set_focus_item(ui4_g_menu_page_setup, ui2_item_page_help_sys_info_and_reset, TRUE);

            menu_nav_go(ui4_page_help_sys_info_and_reset, NULL);

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case MENU_SHORT_CUT_MAX_VIEW_DATA:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_SYSTEM);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_setup, NULL);
            menu_page_tree_set_focus_item(ui4_g_menu_page_setup, ui2_item_page_help_sys_info_and_reset, TRUE);

            menu_nav_go(ui4_page_help_sys_info_and_reset, NULL);
            if (a_tv_custom_get_tos() == FALSE || a_tv_custom_get_privacy() == FALSE)
            {
                menu_page_tree_set_focus_item(ui4_page_help_sys_info_and_reset, ui2_item_page_help_tos, TRUE);
            }
            else
            {
                menu_page_tree_set_focus_item(ui4_page_help_sys_info_and_reset, ui2_item_acr, TRUE);

            }

            /* Do fade out animation */
            i4_ret =_menu_anim_start_move_animation(h_frm_main,
                                            (VOID*)&t_g_rect_out,
                                            (VOID*)&t_g_rect_in);

            MENU_LOG_ON_FAIL(i4_ret);
            return MENUR_OK;
        }
        case MENU_SHORT_CUT_USER_MANUAL:
        {
            _menu_nav_to_main_page(MAIN_MENU_ITEM_INDEX_USER_MANUAL);

            a_tv_net_OSD_appear();

            menu_nav_go(ui4_g_menu_page_user_manual, NULL);

            return MENUR_OK;
        }
        default :
        {
            DBG_ERROR(("<MENU>Short cut not support %s:%d\n", __FILE__, __LINE__));
        }
        return MENUR_INV_ARG;
    }

    a_tv_net_OSD_appear();

    menu_pm_show_with_tab_ex(ui4_tab_id, FALSE);

    c_memset(&t_hint,0,sizeof(t_hint));

    t_hint.e_hint_type = MENU_PAGE_HT_CUSTOM;
    t_hint.u.pv_custom_hint = (VOID *)&ui1_hlt_indx;

    i4_ret = menu_nav_go_direct_ex(ui4_tab_id,
                                   paui4_page_ids,
                                   ui1_size,
                                   &t_hint);
    MENU_LOG_ON_FAIL(i4_ret);

    _menu_anim_start_move_animation(h_frm_main,
                                    (VOID*)&t_g_rect_out,
                                    (VOID*)&t_g_rect_in);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_hide
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
INT32 menu_pm_hide(VOID)
{
    INT32   i4_ret;
    UINT8   ui1_alpha;
    UINT8   ui1_i;

    if(menu_page_is_reset_page(ui4_page_crnt))
    {
        menu_nav_back_ex(FALSE);
    }

    /* Before animation starts,  unfocus the listbox */
    i4_ret = _tab_focus_idx(PM_TABIDX_NONE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    MENU_LOG_ON_FAIL(i4_ret);
    //When show toast range, don't do animation
    if (menu_get_toast_range_flag() == TRUE)
    {
        menu_set_toast_range_flag(FALSE);
        if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
        {
               _menu_anim_start_move_animation(h_frm_main,
                                       (VOID*)&t_g_rect_in,
                                       (VOID*)&t_g_rect_out);
        }
    }
    else if (!t_g_menu_common.b_is_hot_key_enter)
    {
        /* Do fade out animation */
       _menu_anim_start_move_animation(h_frm_main,
                                       (VOID*)&t_g_rect_in,
                                       (VOID*)&t_g_rect_out);
    }
    else if (menu_hot_key_page_with_animation())
    {
        _menu_anim_start_move_animation(h_frm_main,
                                   (VOID*)&t_g_rect_in,
                                   (VOID*)&t_g_rect_out);
    }

    if(b_using_fading && MENU_PM_FADE_STEP > 1)
    {
        for(ui1_i = 1; ui1_i <= MENU_PM_FADE_STEP; ui1_i++)
        {
            ui1_alpha = (UINT8)(ui1_osd_alpha * (MENU_PM_FADE_STEP - ui1_i)/ MENU_PM_FADE_STEP);
            c_gl_plane_set_alpha(h_plane,  ui1_alpha);

            if(ui1_i != MENU_PM_FADE_STEP)
            {
                c_thread_delay(MENU_PM_FADE_DELAY / MENU_PM_FADE_STEP);
            }
        }
    }

    i4_ret = c_wgl_show(h_frm_root, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(h_frm_root, WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);

    if(b_using_fading)
    {
        i4_ret = c_gl_plane_set_alpha(h_plane,  255);
        MENU_CHK_FAIL(i4_ret);
    }

    e_pm_cond = PM_COND_HIDE;

    a_tv_net_OSD_disapper();
    a_tv_net_send_cmd(":dtv_app_mtk,am,:unfocus=dtv_app_mtk\n");
#ifdef APP_TTS_SUPPORT
    MENU_LOG_ON_FAIL(_menu_help_tip_stop_tts_play());
#endif

    return MENUR_OK;
}

extern BOOL menu_page_is_network_manual_setup_page(UINT32 ui4_page_id);

INT32 menu_pm_repaint_current_page(VOID)
{
    PM_PAGE_ENTRY_T* pt_page_crnt = NULL;
    UINT32 tick                   = c_os_get_sys_tick();

    if(MENUR_OK == _page_get_page_entry_by_id(ui4_page_crnt,&pt_page_crnt) &&
       pt_page_crnt)
    {
        DBG_INFO(("[MENU][%s %d] repaint current page\n",__FUNCTION__,__LINE__));
        if(menu_page_is_network_manual_setup_page(ui4_page_crnt) )
            MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_crnt->h_cnt_frm, NULL, TRUE));
        else
            MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_crnt->h_cnt_frm, NULL, TRUE));
    }
    DBG_INFO(("[MENU][%s %d] cost %d ms \n",__FUNCTION__,__LINE__,c_os_get_sys_tick_period()* (c_os_get_sys_tick() - tick)));
    return MENUR_OK;
}

INT32 menu_pm_repaint_sync(void)
{
    UINT32 tick = c_os_get_sys_tick();

    //DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui4_page_crnt:%d\n",__FUNCTION__,__LINE__, ui4_page_crnt  )); );
    DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui4_page_crnt:%d, PID:%d, TID:%d\n",__FUNCTION__,__LINE__, ui4_page_crnt, getpid(), MApi_Sys_get_thread_id() ));

    menu_pm_update(ui4_page_crnt, MENU_PAGE_UMASK_REFRESH);

    MENU_LOG_ON_FAIL(c_wgl_repaint(h_frm_main, NULL, TRUE));
    // menu_pm_repaint_current_page();


    c_wgl_repaint(h_backbar_frm,NULL,TRUE);
    c_wgl_repaint(h_homebar_frm,NULL,TRUE);
    // c_wgl_repaint(h_txt_title,  NULL,FALSE);
    //c_wgl_repaint(h_menu_help_tip,  NULL,FALSE);
    a_help_tip_show_help(h_menu_help_tip);

    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR][%s %d] ui4_page_crnt:%d, cost %d ms \n",__FUNCTION__,__LINE__, ui4_page_crnt, c_os_get_sys_tick_period()* (c_os_get_sys_tick() - tick))); );

    return MENUR_OK;
}

static VOID _menu_do_pm_repaint (
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    UINT32 tick = c_os_get_sys_tick();

    //DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui4_page_crnt:%d\n",__FUNCTION__,__LINE__, ui4_page_crnt )); );
    DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui4_page_crnt:%d, PID:%d, TID:%d\n",__FUNCTION__,__LINE__, ui4_page_crnt, getpid(), MApi_Sys_get_thread_id() ));

    menu_pm_update(ui4_page_crnt, MENU_PAGE_UMASK_REFRESH);

    MENU_DEBUG_TIME_CHECK_POINT();

    MENU_LOG_ON_FAIL(c_wgl_repaint(h_frm_main, NULL, TRUE));
    // menu_pm_repaint_current_page();

    MENU_DEBUG_TIME_CHECK_POINT();

    c_wgl_repaint(h_backbar_frm,NULL,TRUE);
    c_wgl_repaint(h_homebar_frm,NULL,TRUE);
    // c_wgl_repaint(h_txt_title,  NULL,FALSE);
    //c_wgl_repaint(h_menu_help_tip,  NULL,FALSE);

    MENU_DEBUG_TIME_CHECK_POINT();
    a_help_tip_show_help(h_menu_help_tip);

    MENU_DEBUG_TIME_CHECK_POINT();

    MENU_DEBUG_TIME( DBG_LOG_PRINT(("[MENU][MNGR][%s %d] ui4_page_crnt:%d, cost %d ms \n",__FUNCTION__,__LINE__, ui4_page_crnt, c_os_get_sys_tick_period()* (c_os_get_sys_tick() - tick))); );

    DBG_INFO(("[MENU][%s %d] ui4_page_crnt:%d, cost %d ms \n",__FUNCTION__,__LINE__, ui4_page_crnt, c_os_get_sys_tick_period()* (c_os_get_sys_tick() - tick)));
}


/*----------------------------------------------------------------------------
 * Name: menu_page_get_cnt_frm
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

INT32 menu_pm_repaint(VOID)
{
    //DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui4_page_crnt:%d\n",__FUNCTION__,__LINE__, ui4_page_crnt  ));
    DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui4_page_crnt:%d, PID:%d, TID:%d\n",__FUNCTION__,__LINE__, ui4_page_crnt, getpid(), MApi_Sys_get_thread_id() ));

    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui4_page_crnt:%d\n",__FUNCTION__,__LINE__, ui4_page_crnt  )); );

        menu_pm_update(ui4_page_crnt, MENU_PAGE_UMASK_REFRESH);
        MENU_LOG_ON_FAIL(c_wgl_float(h_frm_main, TRUE, TRUE));

        menu_common_page_ip_settings_on_repaint();

        c_wgl_repaint(h_backbar_frm,NULL,TRUE);
        c_wgl_repaint(h_homebar_frm,NULL,TRUE);
        c_wgl_repaint(h_txt_title,  NULL,TRUE);
        a_help_tip_show_help(h_menu_help_tip);
    }
    else
    {
        CHAR s_app_name[APP_NAME_MAX_LEN+1] = {0};

        a_am_get_active_app(s_app_name);

        DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui4_page_crnt:%d, app:{%s}\n",__FUNCTION__,__LINE__, ui4_page_crnt, s_app_name )); );

        c_wgl_float(h_frm_main, FALSE, FALSE);

        if (c_strcmp(s_app_name, MENU_NAME) == 0)
        {
            _menu_do_pm_repaint(0, FALSE);
        }
        else
        {
            menu_async_invoke(_menu_do_pm_repaint, (VOID*)NULL, 0, FALSE);
        }

    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_update_all
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
INT32 menu_pm_update_all(
    UINT32 ui4_update_mask
){
    PM_PAGE_ENTRY_T* pt_page_tmp;
    DLIST_FOR_EACH(pt_page_tmp, &t_page_list, t_link)
    if(NULL != pt_page_tmp->t_fct_tbl.pf_menu_page_update)
    {
        pt_page_tmp->t_fct_tbl.pf_menu_page_update(
            pt_page_tmp->ui4_page_id,
            ui4_update_mask);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_update
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
INT32 menu_pm_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_entry;

    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui4_page_id:%d, ui4_update_mask:0x%X\n",__FUNCTION__,__LINE__, ui4_page_id, ui4_update_mask  )); );

    i4_ret = _page_get_page_entry_by_id(ui4_page_id,
                                        &pt_page_entry);
    if(i4_ret != MENUR_OK)
    {
        DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} Error: i4_ret:%d\n",__FUNCTION__,__LINE__, i4_ret  ));
        return i4_ret;
    }

    pt_page_entry->t_fct_tbl.pf_menu_page_update(
        pt_page_entry->ui4_page_id,
        ui4_update_mask);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_refresh
 *
 * Description:
 *      Refresh current page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_pm_refresh(VOID)
{
    DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui4_page_crnt:%d\n",__FUNCTION__,__LINE__, ui4_page_crnt  ));

    UINT32 tick = c_os_get_sys_tick();

    menu_pm_update(ui4_page_crnt, MENU_PAGE_UMASK_REFRESH);
    c_wgl_repaint(h_backbar_frm,NULL,FALSE);
    c_wgl_repaint(h_homebar_frm,NULL,FALSE);
    c_wgl_repaint(h_txt_title,  NULL,FALSE);
    c_wgl_repaint(h_menu_help_tip,  NULL,FALSE);

    DEBUG_PM( DBG_LOG_PRINT(("[MENU][%s %d] ui4_page_crnt:%d, cost %d ms \n",__FUNCTION__,__LINE__, ui4_page_crnt, c_os_get_sys_tick_period()* (c_os_get_sys_tick() - tick))); );

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_get_plane
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
INT32 menu_pm_get_plane(
    GL_HPLANE_T* ph_plane
){
    if(ph_plane == NULL)
    {
        return MENUR_INV_ARG;
    }
    *ph_plane = h_plane;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_get_canvas
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
INT32 menu_pm_get_canvas(
    HANDLE_T* ph_canvas
){
    if(ph_canvas == NULL)
    {
        return MENUR_INV_ARG;
    }
    *ph_canvas = h_canvas;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_get_root_frm
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
INT32 menu_pm_get_root_frm(
    HANDLE_T* ph_frm_root
){
    if(ph_frm_root == NULL)
    {
        return MENUR_INV_ARG;
    }
    *ph_frm_root = h_frm_root;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_get_main_frm
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
INT32 menu_pm_get_main_frm( HANDLE_T* ph_frm_main )
{
    if(ph_frm_main == NULL)
    {
        return MENUR_INV_ARG;
    }
    *ph_frm_main = h_frm_main;
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_pm_get_home_bar_frm
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
INT32 menu_pm_get_home_bar_frm( HANDLE_T* ph_frm_main )
{
    if(ph_frm_main == NULL)
    {
        return MENUR_INV_ARG;
    }
    *ph_frm_main = h_homebar_frm;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_get_last_shadow_item
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
INT32 menu_pm_get_last_shadow_item( HANDLE_T* ph_last_shadow_item )
{
    if(ph_last_shadow_item == NULL)
    {
        return MENUR_INV_ARG;
    }
    *ph_last_shadow_item = h_last_shadow_item;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_pm_get_last_shadow_item
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
INT32 menu_pm_get_energy_start_icon_handle( HANDLE_T* ph_energy_start_icon_handle )
{
    if(ph_energy_start_icon_handle == NULL)
    {
        return MENUR_INV_ARG;
    }
    *ph_energy_start_icon_handle = h_energy_start_icon_img;
    return MENUR_OK;
}

INT32 menu_pm_get_help_tip_item( HANDLE_T* ph_help_tip_item )
{
    if(ph_help_tip_item == NULL)
    {
        return MENUR_INV_ARG;
    }
    *ph_help_tip_item = h_menu_help_tip;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_set_data
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
INT32 menu_pm_set_page_event_listener(menu_page_event_listener_fct  pf_fct)
{
    if (pf_fct == NULL)
    {
        return MENUR_INV_ARG;
    }

    pf_page_event_listener_fct = pf_fct;

    return MENUR_OK;
}

/* page operation functions */
/*----------------------------------------------------------------------------
 * Name: menu_page_get_cnt_frm
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
INT32 menu_page_get_cnt_frm(
    UINT32 ui4_page_id,
    HANDLE_T* ph_cnt_frm
){
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_entry;

    if(ph_cnt_frm == NULL)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = _page_get_page_entry_by_id(ui4_page_id,
                                        &pt_page_entry);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    *ph_cnt_frm = pt_page_entry->h_cnt_frm;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_get_data
 *
 * Description:
 *      Get canvas height. The canvas height is idnetical to screen height.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_page_set_data(
    UINT32 ui4_page_id,
    VOID* pv_data
){
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_entry;

    i4_ret = _page_get_page_entry_by_id(ui4_page_id,
                                        &pt_page_entry);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    pt_page_entry->pv_page_data = pv_data;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_get_data
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
INT32 menu_page_get_data(
    UINT32 ui4_page_id,
    VOID** ppv_data
){
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_entry;

    if(ppv_data == NULL)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = _page_get_page_entry_by_id(ui4_page_id,
                                        &pt_page_entry);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    *ppv_data = pt_page_entry->pv_page_data;

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_page_set_proc_func
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
INT32 menu_page_set_proc_func(
    UINT32 ui4_page_id,
    wgl_widget_proc_fct pf_wdgt_proc
){
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_entry;

    i4_ret = _page_get_page_entry_by_id(ui4_page_id,
                                        &pt_page_entry);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    pt_page_entry->pf_wdgt_proc = pf_wdgt_proc;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_get_state
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
INT32 menu_page_get_state(
    UINT32 ui4_page_id,
    MENU_PAGE_STATE_T* pe_state
){
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_entry;

    i4_ret = _page_get_page_entry_by_id(ui4_page_id,
                                        &pt_page_entry);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    *pe_state = pt_page_entry->e_state;

    return MENUR_OK;
}

/* navigation operations */
/*----------------------------------------------------------------------------
 * Name: reset_dialog_go
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
INT32 reset_dialog_go(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint
){
    INT32 i4_ret;

    if(ui2_tab_crnt >= MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    switch (e_pm_cond)
    {
    case PM_COND_NOT_INIT:
    case PM_COND_HIDE:
        return MENUR_INV_STATE;
    case PM_COND_TAB:
        {
            if(ui4_page_id == at_tabs[ui2_tab_crnt].pt_page->ui4_page_id)
            {
                _page_focus(at_tabs[ui2_tab_crnt].pt_page, pt_hint);

                menu_pm_repaint();
            }
            else
            {
                PM_PAGE_ENTRY_T* pt_page_next;

                i4_ret = _page_get_page_entry_by_id(ui4_page_id,
                                                    &pt_page_next);
                if(i4_ret != MENUR_OK)
                {
                    return i4_ret;
                }

                _page_hide(at_tabs[ui2_tab_crnt].pt_page);
                _page_show(pt_page_next);
                _page_focus(pt_page_next, pt_hint);

                ui4_page_crnt = ui4_page_id;

                menu_pm_repaint();
            }

            e_pm_cond = PM_COND_PAGE;
            break;
        }
    case PM_COND_PAGE:
        {
            PM_PAGE_ENTRY_T* pt_page_crnt;
            PM_PAGE_ENTRY_T* pt_page_next;

            if(ui4_page_crnt == ui4_page_id)
            {
                DBG_ERROR(("<MENU>The target page is current page"));
                return MENUR_INV_ARG;
            }

            if(ui2_nav_stack_top + 1 >= MENU_PM_MAX_NAV_SIZE)
            {
                DBG_ERROR(("<MENU>Navigation stack is full.\r\n"));
                return MENUR_FAIL;
            }

            i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                          &pt_page_crnt);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }

            i4_ret = _page_get_page_entry_by_id(ui4_page_id,
                                          &pt_page_next);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }

            _page_unfocus(pt_page_crnt);
            if(b_hide_main_menu_in_page_switch)
            {
                 //_page_hide(pt_page_crnt);
            }
            else
            {
                pt_page_crnt->e_state = MENU_PAGE_STATE_HIDE;
            }
            b_hide_main_menu_in_page_switch = TRUE;

            _page_show(pt_page_next);
            _page_focus(pt_page_next, pt_hint);

            aui4_nav_stack[ui2_nav_stack_top++] = ui4_page_crnt;
            ui4_page_crnt = ui4_page_id;

            menu_pm_repaint();
            break;
        }
    }

    return MENUR_OK;
}

/* navigation operations */
/*----------------------------------------------------------------------------
 * Name: menu_nav_go
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
INT32 menu_nav_go(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint
){
    INT32 i4_ret;
    INT32 tick = c_os_get_sys_tick();

    if(ui2_tab_crnt >= MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    b_is_nav_go = TRUE;

    DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} e_pm_cond: %d, ui4_page_id: %d\n",
        __FUNCTION__, __LINE__, e_pm_cond, ui4_page_id));

    switch (e_pm_cond)
    {
        case PM_COND_NOT_INIT:
        case PM_COND_HIDE:
            return MENUR_INV_STATE;
        case PM_COND_TAB:
            {
                if(ui4_page_id == at_tabs[ui2_tab_crnt].pt_page->ui4_page_id)
                {
                    _page_focus(at_tabs[ui2_tab_crnt].pt_page, pt_hint);
                    menu_pm_repaint();
                }
                else
                {
                    PM_PAGE_ENTRY_T* pt_page_next;

                    i4_ret = _page_get_page_entry_by_id(ui4_page_id,&pt_page_next);
                    if(i4_ret != MENUR_OK)
                    {
                        DBG_ERROR(("[%s %d]failed to get page entry.\r\n",__FUNCTION__,__LINE__));
                        return i4_ret;
                    }
                    _page_unfocus(at_tabs[ui2_tab_crnt].pt_page);
                    _page_hide(at_tabs[ui2_tab_crnt].pt_page);
                    _page_show(pt_page_next);
                    _page_focus(pt_page_next, pt_hint);
                    ui4_page_crnt = ui4_page_id;
                    menu_pm_repaint();
                }

                e_pm_cond = PM_COND_PAGE;
                break;
            }
        case PM_COND_PAGE:
            {
                PM_PAGE_ENTRY_T* pt_page_crnt;
                PM_PAGE_ENTRY_T* pt_page_next;

                if(ui4_page_crnt == ui4_page_id)
                {
                    DBG_ERROR(("[%s %d] The target page is current page",__FUNCTION__,__LINE__));
                    return MENUR_INV_ARG;
                }

                if(ui2_nav_stack_top + 1 >= MENU_PM_MAX_NAV_SIZE)
                {
                    DBG_ERROR(("<MENU>Navigation stack is full.\r\n"));
                    return MENUR_FAIL;
                }

                i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                                    &pt_page_crnt);
                if(i4_ret != MENUR_OK)
                {
                    return i4_ret;
                }

                i4_ret = _page_get_page_entry_by_id(ui4_page_id,
                                                    &pt_page_next);
                if(i4_ret != MENUR_OK)
                {
                    DBG_ERROR(("<MENU>failed to get page entry.\r\n"));
                    return i4_ret;
                }

                // menu_page_tree_set_offset(ui4_page_id, 0);

                _page_unfocus(pt_page_crnt);
                if(b_hide_main_menu_in_page_switch)
                {
                     _page_hide(pt_page_crnt);
                }
                else
                {
                    pt_page_crnt->e_state = MENU_PAGE_STATE_HIDE;
                }
                b_hide_main_menu_in_page_switch = TRUE;
                _page_show(pt_page_next);
                _page_focus(pt_page_next, pt_hint);

                aui4_nav_stack[ui2_nav_stack_top++] = ui4_page_crnt;
                ui4_page_crnt = ui4_page_id;

                menu_pm_repaint();
                break;
            }
    }
    DBG_INFO(("[MENU][%s %d] cost %d ms\n",__FUNCTION__,__LINE__,c_os_get_sys_tick_period()* (c_os_get_sys_tick() - tick)));
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_nav_back
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

BOOL g_PM_b_menu_nav_back_use_repaint_sync = 0;

void menu_pm_Set_nav_back_use_repaint_sync(BOOL bUseSyncApi)
{
    DBG_LOG_PRINT(("[MENU][MNGR] %s(bUseSyncApi:%d)\n", __FUNCTION__, bUseSyncApi  ));

    g_PM_b_menu_nav_back_use_repaint_sync = bUseSyncApi;
}

INT32 menu_nav_back(VOID)
{
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_crnt;
    PM_PAGE_ENTRY_T* pt_page_next;
    UINT32  ui4_page_next;


    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} e_pm_cond:%d\n",__FUNCTION__,__LINE__, e_pm_cond  )); );

    if(ui2_nav_stack_top > MENU_PM_MAX_NAV_SIZE)
    {
        return MENUR_INV_STATE;
    }

    b_is_nav_go = FALSE;

    switch (e_pm_cond)
    {
        case PM_COND_NOT_INIT:
        case PM_COND_HIDE:
            return MENUR_INV_STATE;
        case PM_COND_TAB:
            /* The reason for using menu_leave() instead of pause is because for
               slave mode, backing the menu will notify the master menu */
            menu_leave(TRUE, ui4_hide_delay1);
            break;

        case PM_COND_PAGE:
            DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui2_nav_stack_top:%d, \n",__FUNCTION__,__LINE__, ui2_nav_stack_top   )); );
            if(ui2_nav_stack_top != 0)
            {
                /* back to the upper page */
                MENU_PAGE_HINT_T t_hint;

                UINT16 ui2_stack_ptr = (UINT16)(ui2_nav_stack_top - 1);

                ui4_page_next = aui4_nav_stack[ui2_stack_ptr];

                i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                              &pt_page_crnt);
                if(i4_ret != MENUR_OK)
                {
                    return i4_ret;
                }
                DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui4_page_crnt:%d, ui4_page_next:%d\n",__FUNCTION__,__LINE__, ui4_page_crnt, ui4_page_next  )); );

                i4_ret = _page_get_page_entry_by_id(ui4_page_next,
                                              &pt_page_next);
                if(i4_ret != MENUR_OK)
                {
                    DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d}Error: i4_ret:%d\n",__FUNCTION__,__LINE__, i4_ret ));
                    return i4_ret;
                }


                t_hint.e_hint_type = MENU_PAGE_HT_BACK;

                DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} call _page_unfocus(%d)\n", __FUNCTION__,__LINE__, pt_page_crnt )); );
                _page_unfocus(pt_page_crnt);

                DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} call _page_hide(%d)\n", __FUNCTION__,__LINE__, pt_page_crnt )); );
                _page_hide(pt_page_crnt);

                DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} call _page_show(%d)\n", __FUNCTION__,__LINE__, pt_page_crnt )); );
                _page_show(pt_page_next);

                // get focus
                {
                    HANDLE_T  h_CurFocus = NULL_HANDLE;
                    c_wgl_get_focus(&h_CurFocus);
                    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} h_CurFocus:0x%X\n",__FUNCTION__,__LINE__, h_CurFocus  )); );
                }

                DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} call _page_focus(%d)\n", __FUNCTION__,__LINE__, pt_page_crnt )); );
                _page_focus(pt_page_next, &t_hint);

                // get focus
                {
                    HANDLE_T  h_CurFocus = NULL_HANDLE;
                    c_wgl_get_focus(&h_CurFocus);
                    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} h_CurFocus:0x%X\n",__FUNCTION__,__LINE__, h_CurFocus  )); );
                }


                ui2_nav_stack_top--;
                ui4_page_crnt = ui4_page_next;
                DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} ui2_nav_stack_top:%d, ui4_page_crnt:%d\n",__FUNCTION__,__LINE__, ui2_nav_stack_top, ui4_page_crnt  )); );


                if( g_PM_b_menu_nav_back_use_repaint_sync )
                {
                    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} call menu_pm_repaint_sync(%d)\n", __FUNCTION__,__LINE__, pt_page_crnt )); );
                    menu_pm_repaint_sync();
                }
                else
                {
                    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} call menu_pm_repaint(%d)\n", __FUNCTION__,__LINE__, pt_page_crnt )); );
                    menu_pm_repaint();
                }

            }
            else
            {
                if(b_one_tab_mode)
                {
                #ifdef APP_MENU_MMP_COEXIST
                    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
                    {
                        /* Multimedia */
                        a_amb_resume_app(MMP_NAME);
                    }
                    else
                #endif
                    {
                        menu_leave(TRUE, ui4_hide_delay1);
                    }

                }
                else
                {
                    /* back to the tab */
                    _tab_focus_idx(ui2_tab_crnt);

                    /* Check if all Tabs are hidden. */
                    /* The state is invalid, leave menu now. */
                    if(_tab_are_all_hide())
                    {
                        menu_leave(TRUE, ui4_hide_delay1);
                        DBG_ERROR(("<MENU> There are no visible Tabs !\n"));
                        return MENUR_OK;
                    }

                    /* The returning Tab is already hide. */
                    /* Search next selectable Tab and focus on it */
                    /* Reached by simulating pressing BTN_CURSOR_DOWN/BTN_CURSOR_RIGHT */
                    if(ui2_tab_crnt >= MENU_PM_MAX_TAB_NUM)
                    {
                        return MENUR_INV_STATE;
                    }

                    if(at_tabs[ui2_tab_crnt].b_hidden == TRUE)
                    {
                        if(b_tab_vert)
                        {
                            _tab_proc_fct(at_tabs[ui2_tab_crnt].h_btn,
                                          WGL_MSG_KEY_DOWN,
                                          (VOID *) BTN_CURSOR_DOWN,
                                          NULL);
                        }
                        else
                        {
                            _tab_proc_fct(at_tabs[ui2_tab_crnt].h_btn,
                                          WGL_MSG_KEY_DOWN,
                                          (VOID *) BTN_CURSOR_RIGHT,
                                          NULL);
                        }
                    }
                    menu_pm_repaint();
                    e_pm_cond = PM_COND_TAB;
                }
            }
            break;
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_nav_back
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
INT32 menu_nav_back_ex(BOOL b_repaint)
{
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_crnt;
    PM_PAGE_ENTRY_T* pt_page_next;
    UINT32  ui4_page_next;

    if(ui2_nav_stack_top > MENU_PM_MAX_NAV_SIZE)
    {
        return MENUR_INV_STATE;
    }

    switch (e_pm_cond)
    {
        case PM_COND_NOT_INIT:
        case PM_COND_HIDE:
            return MENUR_INV_STATE;
        case PM_COND_TAB:
            /* The reason for using menu_leave() instead of pause is because for
               slave mode, backing the menu will notify the master menu */
            menu_leave(TRUE, ui4_hide_delay1);
            break;
        case PM_COND_PAGE:
            if(ui2_nav_stack_top != 0)
            {
                /* back to the upper page */
                MENU_PAGE_HINT_T t_hint;

                UINT16 ui2_stack_ptr = (UINT16)(ui2_nav_stack_top - 1);

                ui4_page_next = aui4_nav_stack[ui2_stack_ptr];

                i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                              &pt_page_crnt);
                if(i4_ret != MENUR_OK)
                {
                    return i4_ret;
                }

                i4_ret = _page_get_page_entry_by_id(ui4_page_next,
                                              &pt_page_next);
                if(i4_ret != MENUR_OK)
                {
                    return i4_ret;
                }


                t_hint.e_hint_type = MENU_PAGE_HT_BACK;
                _page_unfocus(pt_page_crnt);
                _page_hide(pt_page_crnt);
                _page_show(pt_page_next);
                _page_focus(pt_page_next, &t_hint);

                ui2_nav_stack_top--;
                ui4_page_crnt = ui4_page_next;
                menu_pm_repaint();
            }
            else
            {
                if(b_one_tab_mode)
                {
                    menu_leave(TRUE, ui4_hide_delay1);
                }
                else
                {
                    /* back to the tab */
                    _tab_focus_idx(ui2_tab_crnt);

                    /* Check if all Tabs are hidden. */
                    /* The state is invalid, leave menu now. */
                    if(_tab_are_all_hide())
                    {
                        menu_leave(TRUE, ui4_hide_delay1);
                        DBG_ERROR(("<MENU> There are no visible Tabs !\n"));
                        return MENUR_OK;
                    }

                    /* The returning Tab is already hide. */
                    /* Search next selectable Tab and focus on it */
                    /* Reached by simulating pressing BTN_CURSOR_DOWN/BTN_CURSOR_RIGHT */
                    if(ui2_tab_crnt >= MENU_PM_MAX_TAB_NUM)
                    {
                        DBG_ERROR(("<MENU> There MENU_PM_MAX_TAB_NUM  < ui2_tab_crnt!\n"));
                        return MENUR_INV_STATE;
                    }

                    if(at_tabs[ui2_tab_crnt].b_hidden == TRUE)
                    {
                        if(b_tab_vert)
                        {
                            _tab_proc_fct(at_tabs[ui2_tab_crnt].h_btn,
                                          WGL_MSG_KEY_DOWN,
                                          (VOID *) BTN_CURSOR_DOWN,
                                          NULL);
                        }
                        else
                        {
                            _tab_proc_fct(at_tabs[ui2_tab_crnt].h_btn,
                                          WGL_MSG_KEY_DOWN,
                                          (VOID *) BTN_CURSOR_RIGHT,
                                          NULL);
                        }
                    }
                    menu_pm_repaint();
                    e_pm_cond = PM_COND_TAB;
                }
            }
            break;
    }

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_nav_back_and_go
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
INT32 menu_nav_back_and_go(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint
){
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_crnt;
    PM_PAGE_ENTRY_T* pt_page_next;

    switch(e_pm_cond)
    {
    case PM_COND_NOT_INIT:
    case PM_COND_HIDE:
    case PM_COND_TAB:
        return MENUR_INV_STATE;
    case PM_COND_PAGE:
        if(ui4_page_crnt == ui4_page_id)
        {
            DBG_ERROR(("<MENU>The target page is current page"));
            return MENUR_INV_ARG;
        }
        i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                      &pt_page_crnt);
        if(i4_ret != MENUR_OK)
        {
            return i4_ret;
        }

        i4_ret = _page_get_page_entry_by_id(ui4_page_id,
                                      &pt_page_next);
        if(i4_ret != MENUR_OK)
        {
            return i4_ret;
        }

        _page_unfocus(pt_page_crnt);
        _page_hide(pt_page_crnt);

        _page_show(pt_page_next);
        _page_focus(pt_page_next, pt_hint);

        menu_pm_repaint();
        ui4_page_crnt = ui4_page_id;
        break;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_nav_go_home_menu
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
INT32  menu_nav_go_home_menu (VOID)
{
    INT32 i4_ret;
    UINT32 aui4_pages[] = { ui4_g_menu_page_main_menu };

    i4_ret = menu_nav_go_direct(0,
                                aui4_pages,
                                sizeof(aui4_pages)/sizeof(aui4_pages[0]),
                                NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_nav_go_to_factory_page
 *
 * Description:
 *      Navigate to factory key. All the navigation stack data will be cleaned and
 *  current focus page is on the first enabled and visible (not hidden) tab.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *  MENUR_OK            -   Succesful
 *  MENUR_INV_STATE     -   1. If menu is paused. This API is only avaible when menu
 *                             is active.
 *                          2. menu facotry page has not been set.
 ----------------------------------------------------------------------------*/
INT32 menu_nav_go_to_factory_page(VOID)
{
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_crnt;
    PM_PAGE_ENTRY_T* pt_page_next;

    if(ui4_page_factory == PM_PAGEID_NONE)
    {
        return MENUR_INV_STATE;
    }

    switch (e_pm_cond)
    {
    case PM_COND_NOT_INIT:
    case PM_COND_HIDE:
        return MENUR_INV_STATE;
    case PM_COND_TAB:
        {
            menu_nav_go(ui4_page_factory, NULL);
            break;
        }
    case PM_COND_PAGE:
        {
            MENU_PAGE_STATE_T   e_page_state;

            i4_ret = menu_page_get_state(ui4_page_factory, &e_page_state);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }

            if(e_page_state == MENU_PAGE_STATE_FOCUS)
            {
                return MENUR_OK;
            }

            /* reset the navigation stack */

            i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                          &pt_page_crnt);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }

            i4_ret = _page_get_page_entry_by_id(ui4_page_factory,
                                                &pt_page_next);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }

            _page_unfocus(pt_page_crnt);
            _page_hide(pt_page_crnt);

            _page_show(pt_page_next);
            _page_focus(pt_page_next, NULL);

            ui2_nav_stack_top = 0;
            ui4_page_crnt = ui4_page_factory;

            menu_pm_repaint();

            break;
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_nav_go_direct
 *
 * Description:
 *  Navigate to a specific page with the specific path.
 *  This function should be called when menu is resumed.
 *
 *  If (ui2_page_num == 0), it will stay on the tab of ui2_tab_idx.
 *  If (ui2_page_num > 0), it will stay on the lastest page of pui4_page_ids.
 *      and the tab is on the ui2_tab_idx
 *      and the navigation stack is according to pui4_page_ids.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_nav_go_direct(
    UINT16   ui2_tab_idx,
    UINT32*  pui4_page_ids,
    UINT16   ui2_page_num,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32 i4_ret;
    PM_PAGE_ENTRY_T* pt_page_crnt;
    PM_PAGE_ENTRY_T* pt_page_next;
    UINT16  ui2_i;
    UINT32  ui4_page_next;

    if(e_pm_cond == PM_COND_NOT_INIT ||
       e_pm_cond == PM_COND_HIDE)
    {
        return MENUR_INV_STATE;
    }

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    if(ui2_tab_idx >= ui2_tab_num)
    {
        return MENUR_INV_ARG;
    }

    if(ui2_page_num > MENU_PM_MAX_NAV_SIZE)
    {
        return MENUR_INV_ARG;
    }

    if(ui2_page_num != 0 && pui4_page_ids == NULL)
    {
        return MENUR_INV_ARG;
    }


    if(ui2_page_num == 0)
    {
        /* Navigate to a tab. */
        if(e_pm_cond ==  PM_COND_TAB)
        {
            /* TAB -> TAB */
            if(ui2_tab_idx != ui2_tab_crnt)
            {
                _tab_focus_idx(ui2_tab_idx);
            }
        }
        else /* if(e_pm_cond ==  PM_COND_PAGE)*/
        {
            /* PAGE -> TAB */
            _tab_focus_idx(ui2_tab_idx);
        }

        e_pm_cond = PM_COND_TAB;
    }
    else
    {
        /* Navigate to a page. */
        ui4_page_next = pui4_page_ids[ui2_page_num - 1];

        /* Change the focus tab */
        if(ui2_tab_idx != ui2_tab_crnt)
        {
            for (ui2_i = 0;
                 ui2_i < ui2_tab_num;
                 ui2_i++)
            {
                i4_ret = c_wgl_do_cmd(at_tabs[ui2_i].h_btn,
                                      WGL_CMD_BTN_SET_PUSHED,
                                      (VOID*)(ui2_i == ui2_tab_idx ? TRUE : FALSE),
                                      NULL);
                MENU_CHK_FAIL(i4_ret);
            }
        }

        /* Get current/next page data */
        i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                            &pt_page_crnt);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = _page_get_page_entry_by_id(ui4_page_next,
                                            &pt_page_next);
        MENU_CHK_FAIL(i4_ret);

        if(e_pm_cond ==  PM_COND_TAB)
        {
            /* TAB -> PAGE */
            if(ui4_page_crnt == ui4_page_next)
            {
                _page_focus(pt_page_crnt, pt_hint);
            }
            else
            {
                _page_hide(pt_page_crnt);
                _page_show(pt_page_next);
                _page_focus(pt_page_next, pt_hint);
            }
        }
        else /* if(e_pm_cond ==  PM_COND_PAGE)*/
        {
            /* PAGE -> PAGE */

            /* Check if the navigation stack is identical to navigation request */
            if(ui2_nav_stack_top == (UINT16)(ui2_page_num - 1)                 &&
               c_memcmp(aui4_nav_stack, pui4_page_ids, ui2_nav_stack_top) == 0 &&
               ui4_page_crnt == pui4_page_ids[ui2_page_num - 1])
            {
                /* idential path */
            }
            else
            {
                _page_unfocus(pt_page_crnt);
                _page_hide(pt_page_crnt);
                _page_show(pt_page_next);
                _page_focus(pt_page_next, pt_hint);
            }
        }

        ui2_tab_crnt        = ui2_tab_idx;
        ui4_page_crnt       = ui4_page_next;
        ui2_nav_stack_top   = (UINT16)(ui2_page_num - 1);
        c_memcpy(aui4_nav_stack, pui4_page_ids, ui2_nav_stack_top);
        e_pm_cond           = PM_COND_PAGE;
    }

    menu_pm_repaint();

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_nav_go_direct_ex
 *
 * Description:
 *  Navigate to a specific page with the specific path.
 *  This function should be called when menu is resumed.
 *
 *  If (ui2_page_num == 0), it will stay on the tab of ui2_tab_idx.
 *  If (ui2_page_num > 0), it will stay on the lastest page of pui4_page_ids.
 *      and the tab is on the ui2_tab_idx
 *      and the navigation stack is according to pui4_page_ids.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_nav_go_direct_ex(UINT16   ui2_tab_idx,
                            UINT32*  pui4_page_ids,
                            UINT16   ui2_page_num,
                            MENU_PAGE_HINT_T* pt_hint)
{
    INT32               i4_ret;
    PM_PAGE_ENTRY_T*    pt_page_crnt;
    PM_PAGE_ENTRY_T*    pt_page_next;
    UINT16              ui2_i;
    UINT32              ui4_page_next;

    if(e_pm_cond == PM_COND_NOT_INIT ||
       e_pm_cond == PM_COND_HIDE)
    {
        return MENUR_INV_STATE;
    }

    if(ui2_tab_num > MENU_PM_MAX_TAB_NUM)
    {
        return MENUR_INV_STATE;
    }

    if(ui2_tab_idx >= ui2_tab_num)
    {
        return MENUR_INV_ARG;
    }

    if(ui2_page_num > MENU_PM_MAX_NAV_SIZE)
    {
        return MENUR_INV_ARG;
    }

    if(ui2_page_num != 0 && pui4_page_ids == NULL)
    {
        return MENUR_INV_ARG;
    }


    if(ui2_page_num == 0)
    {
        /* Navigate to a tab. */
        if(e_pm_cond ==  PM_COND_TAB)
        {
            /* TAB -> TAB */
            if(ui2_tab_idx != ui2_tab_crnt)
            {
                _tab_focus_idx(ui2_tab_idx);
            }
        }
        else /* if(e_pm_cond ==  PM_COND_PAGE)*/
        {
            /* PAGE -> TAB */
            _tab_focus_idx(ui2_tab_idx);
        }

        e_pm_cond = PM_COND_TAB;
    }
    else
    {
        /* Navigate to a page. */
        ui4_page_next = pui4_page_ids[ui2_page_num - 1];

        /* Change the focus tab */
        if(ui2_tab_idx != ui2_tab_crnt)
        {
            for (ui2_i = 0;
                 ui2_i < ui2_tab_num;
                 ui2_i++)
            {
                i4_ret = c_wgl_do_cmd(at_tabs[ui2_i].h_btn,
                                      WGL_CMD_BTN_SET_PUSHED,
                                      (VOID*)(ui2_i == ui2_tab_idx ? TRUE : FALSE),
                                      NULL);
                MENU_CHK_FAIL(i4_ret);
            }
        }

        /* Get current/next page data */
        i4_ret = _page_get_page_entry_by_id(ui4_page_crnt,
                                            &pt_page_crnt);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = _page_get_page_entry_by_id(ui4_page_next,
                                            &pt_page_next);
        MENU_CHK_FAIL(i4_ret);

        if(e_pm_cond ==  PM_COND_TAB)
        {
            /* TAB -> PAGE */
            if(ui4_page_crnt == ui4_page_next)
            {
                _page_focus(pt_page_crnt, pt_hint);
            }
            else
            {
                _page_hide(pt_page_crnt);
                _page_show(pt_page_next);
                _page_focus(pt_page_next, pt_hint);
            }
        }
        else /* if(e_pm_cond ==  PM_COND_PAGE)*/
        {
            /* PAGE -> PAGE */

            /* Check if the navigation stack is identical to navigation request */
            if(ui2_nav_stack_top == (UINT16)(ui2_page_num - 1)                 &&
               c_memcmp(aui4_nav_stack, pui4_page_ids, ui2_nav_stack_top) == 0 &&
               ui4_page_crnt == pui4_page_ids[ui2_page_num - 1])
            {
                /* idential path */
            }
            else
            {
                _page_unfocus(pt_page_crnt);
                _page_hide(pt_page_crnt);
                _page_show(pt_page_next);
                _page_focus(pt_page_next, pt_hint);
            }
        }

        ui2_tab_crnt        = ui2_tab_idx;
        ui4_page_crnt       = ui4_page_next;
        ui2_nav_stack_top   = (UINT16)(ui2_page_num - 1);
        c_memcpy(aui4_nav_stack, pui4_page_ids, ui2_nav_stack_top);
        e_pm_cond           = PM_COND_PAGE;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_nav_anim_go
 *
 * Description:
 *  Navigate to a specific page with the animation effect.
 *  This function should be called when menu is resumed.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_nav_anim_go(
                UINT32              ui4_page_id,
                MENU_PAGE_HINT_T*   pt_hint)
{
    switch(e_pm_cond)
    {
    case PM_COND_NOT_INIT:
    case PM_COND_HIDE:
    case PM_COND_TAB:
        return MENUR_INV_STATE;
    case PM_COND_PAGE:
        if(ui4_page_crnt == ui4_page_id)
        {
            DBG_ERROR(("<MENU>The target page is current page"));
            return MENUR_INV_ARG;
        }

        menu_pm_hide();
        menu_nav_back_and_go(ui4_page_id, NULL);
        menu_pm_show();
        break;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_nav_get_nav_stack
 *
 * Description:
 *  This function allow to get the current navigation stack. The pointer
 *  pui4_page_ids output the current stack.
 *
 *  if menu is not shown, the pui2_tab_idx would output 0xFFFF.
 *  Otherwise, pui4_page_ids[n] = n-layer page.
 *
 * Inputs:
 *  pui2_size       -  The buffer size of pui4_page_ids
 *
 * Outputs:
 *  pui2_tab_idx    -  The focused tab.
 *  pui4_page_ids   -  The nav stack.
 *  pui2_size       -  The nav stack size.
 *
 * Returns:
 *  MENUR_OK        - Operation successful
 *  MENUR_INV_ARG   - The pui2_size is not enough
 ----------------------------------------------------------------------------*/
extern INT32 menu_nav_get_nav_stack(
    UINT16* pui2_tab_idx,
    UINT32* pui4_page_ids,
    UINT16* pui2_size)
{
    UINT16   ui2_i;

    if(pui2_tab_idx  == NULL ||
       pui4_page_ids == NULL ||
       pui2_size     == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(ui2_nav_stack_top > MENU_PM_MAX_NAV_SIZE)
    {
        return MENUR_INV_STATE;
    }

    if(e_pm_cond == PM_COND_NOT_INIT ||
       e_pm_cond == PM_COND_HIDE)
    {
        /* Menu is not shown */
        *pui2_tab_idx = 0xFFFF;
        *pui2_size    = 0;
    }
    else
    {
        /* Menu is shown */
        if(*pui2_size < (UINT16)(ui2_nav_stack_top + 1))
        {
            return MENUR_INV_ARG;
        }

        *pui2_size        = (UINT16)(ui2_nav_stack_top + 1);
        *pui2_tab_idx     = ui2_tab_crnt;

        for(ui2_i=0; ui2_i<ui2_nav_stack_top; ui2_i++)
        {
            pui4_page_ids[ui2_i] = aui4_nav_stack[ui2_i];
        }

        pui4_page_ids[ui2_i] = ui4_page_crnt;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_nav_get_crnt_page
 *
 * Description:
 *  Get current showing page.
 *
 * Outputs:
 *  pui4_page_id   -  The page shown.
 *
 * Returns:
 *  MENUR_OK        - Operation successful
 *  MENUR_INV_ARG   - The pui2_size is not enough
 *  MENUR_INV_STATE - If the menu is not shown.
 ----------------------------------------------------------------------------*/
extern INT32 menu_nav_get_crnt_page(
    UINT32* pui4_page_id)
{
    if(pui4_page_id == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(e_pm_cond == PM_COND_NOT_INIT ||
       e_pm_cond == PM_COND_HIDE)
    {
        return MENUR_INV_STATE;
    }

    *pui4_page_id = ui4_page_crnt;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_set_title
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
INT32 menu_main_set_title(UINT16 ui2_msgid_txt)
{
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(h_txt_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          MENU_TEXT(ui2_msgid_txt),
                          WGL_PACK((UINT16)0x80));
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_HDR_SUPPORT
    if((ui2_msgid_txt == MLM_MENU_KEY_VID_PIC_MODE_ITEM)&&
        (a_acfg_cust_get_video_type() != SCC_VID_PQ_SDR ))
    {
        if( a_acfg_cust_get_video_type() == SCC_VID_PQ_HDR10)
        {
            i4_ret = c_wgl_do_cmd(h_txt_title,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HDR10_ITEM),
                                  WGL_PACK((UINT16)0x80));
            MENU_CHK_FAIL(i4_ret);

        }
        else if ( a_acfg_cust_get_video_type() == SCC_VID_PQ_HLG)
        {
            i4_ret = c_wgl_do_cmd(h_txt_title,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HLG_ITEM),
                                  WGL_PACK((UINT16)0x80));

            MENU_CHK_FAIL(i4_ret);

        }
        else if ( a_acfg_cust_get_video_type() == SCC_VID_PQ_HDR10PLUS)
        {
            i4_ret = c_wgl_do_cmd(h_txt_title,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HDR10_PLUS),
                                  WGL_PACK((UINT16)0x80));

            MENU_CHK_FAIL(i4_ret);

        }
    }
#endif
    c_wgl_repaint(h_txt_title,NULL,TRUE);
    ui2_msg_id_title = ui2_msgid_txt;

    if (c_uc_w2s_strcmp(w2s_text_title, MENU_TEXT(ui2_msg_id_title)) != 0)
    {
        MENU_LOG_ON_FAIL(menu_scrl_title_reset(MENU_TEXT(ui2_msg_id_title)));
    }

    return MENUR_OK;

}

/*----------------------------------------------------------------------------
 * Name: menu_main_set_title_text
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
INT32 menu_main_set_title_text(
    UTF16_T*        w2s_dst
){
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(h_txt_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          w2s_dst,
                          WGL_PACK((UINT16)0xFF));
    MENU_CHK_FAIL(i4_ret);

    if (c_uc_w2s_strcmp(w2s_text_title, w2s_dst) != 0)
    {
        MENU_LOG_ON_FAIL(menu_scrl_title_reset(w2s_dst));
    }

    return MENUR_OK;
}

INT32 menu_main_chg_backbar(VOID)
{
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(h_backbar_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          MENU_TEXT(MLM_MENU_KEY_HELP_BACK),
                          WGL_PACK((UINT16)0x80));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*Fake to hide Homebar icon*/
 /*----------------------------------------------------------------------------
 * Name: menu_main_set_main_title_visibility
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
INT32 menu_main_set_main_title_visibility (BOOL b_show)
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(h_main_title_txt,
                                  (b_show == TRUE) ? WGL_SW_RECURSIVE : WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_show_version
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
INT32 menu_show_version(
    BOOL   b_show,
    BOOL   b_repaint
){
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_version_tab_info
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
VOID menu_version_tab_info( BOOL* b_tab_mode, UINT32* ui4_page_id, HANDLE_T* h_btn)
{
    UINT16 ui2_i = 0;

    /* Searching the first visible and enable tab to make sure that
       the factory mode is reachable even if the first tab is hidden.*/
    for(ui2_i = 0; ui2_i < ui2_tab_num; ui2_i++)
    {
        if(at_tabs[ui2_i].b_enabled == TRUE &&
            at_tabs[ui2_i].b_hidden == FALSE)
        {
            break;
        }
    }

    *b_tab_mode = b_one_tab_mode;
    *ui4_page_id = at_tabs[ui2_i].pt_page->ui4_page_id;
    *h_btn = at_tabs[ui2_i].h_btn;
}

static BOOL menu_fac_version_key_filter (UINT32 ui4_keycode)
{
    BOOL b_show_factory_menu;
    UINT8 ui1_fac_mode;
    UINT32 ui4_page_crnt, ui4_page_id;
    HANDLE_T h_focus, h_btn;
    BOOL b_one_tab_mode;

    a_cfg_get_factory_mode (&ui1_fac_mode);

    //c_dbg_stmt ("%s:%d: ui4_keycode: 0x%08x\n", __FUNCTION__, __LINE__, ui4_keycode);

    // If we're in the Factory Mode(Factory Menu)
    if (ui1_fac_mode == APP_CFG_FAC_MODE_FACTORY)
    {
        // If "Exit" is pressed, set to normal mode
        // Ps. when menu is closed by any way, system will call "Exit" automatically.
        if (ui4_keycode == 0)
        {
            a_cfg_set_factory_mode (APP_CFG_FAC_MODE_NORMAL);
            a_cfg_update_factory_mode ();
            a_cfg_store ();
        }
    }
    else
    {
        // put the key into the key list
        // if Magic Key sequence is detected ,return true
        b_show_factory_menu = _version_put_key (ui4_keycode);

        /* Check condition */
        c_wgl_get_focus (&h_focus);
        menu_nav_get_crnt_page (&ui4_page_crnt);
        menu_version_tab_info (&b_one_tab_mode, &ui4_page_id, &h_btn);

        if (b_one_tab_mode)
        {
            /* if in one tab mode, open when in the first page */
            if (ui4_page_crnt != ui4_page_id)
            {
                b_show_factory_menu = FALSE;
            }
        }
        else
        {
            /* check if the focus is the first tab */
            if (h_focus != h_btn)
            {
                b_show_factory_menu = FALSE;
            }
        }

        // If magic key is pressed, enter factory menu
        if (b_show_factory_menu == TRUE)
        {
#ifdef APP_MENU_ENTER_FACOTRY_MODE_ON_SECRET_KEY
            // Set to Factory Mode
            a_cfg_set_factory_mode (APP_CFG_FAC_MODE_FACTORY);
            a_cfg_update_factory_mode ();
            a_cfg_store ();
#endif
            // Swtich to factory menu
            menu_nav_go (ui4_page_factory, NULL);
            menu_show_backbar (TRUE, FALSE);

            // Return TRUE to notify system that this key is handled by factory widget.
            return TRUE;
        }
    }
    return FALSE;
}


/*----------------------------------------------------------------------------
 * Name: menu_version_key_filter
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *  The key is processed or not.
 *
 ----------------------------------------------------------------------------*/
BOOL menu_version_key_filter(
    UINT32    ui4_keycode)
{
    BOOL        b_ver_show_next;
    BOOL        b_processed;

    if(ui2_tab_num >= MENU_PM_MAX_TAB_NUM)
    {
    return FALSE;
    }

    #ifdef APP_MENU_CUSTOM_FACTORY_TREE
    return menu_custom_version_key_filter( ui4_keycode);
    #endif

    return menu_fac_version_key_filter(ui4_keycode);

#if NEVER   //CID:4491064
    /* put the key into the key list */
    b_ver_show_next = _version_put_key(ui4_keycode);

    /* Need customze by ODM*/
    /*if(!focus in xxx()) */
    {
        b_ver_show_next = FALSE;
    }
    DBG_INFO((" ## b_ver_show_curr = %d  \n", b_ver_show_curr));
    DBG_INFO((" ## b_ver_show_next = %d  \n", b_ver_show_next));

    /* show or hide the version information */
    if(!b_ver_show_curr && b_ver_show_next)
    {
        menu_leave(FALSE,0);

        nav_hide_component (NAV_COMP_ID_BANNER);
#ifdef APP_NAV_MAX_64_COMPS
        a_nav_active_component(NAV_COMP_ID_SFM);
#endif
        b_processed = TRUE;
    }
    else
    {
        /* no-op */
        b_processed = FALSE;
    }

    b_ver_show_curr = b_ver_show_next;

    return b_processed;
#endif
}


/*----------------------------------------------------------------------------
 * Name: menu_factory_set_pageid
 *
 * Description:
 *      Set the page id of the factory page.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_factory_set_pageid(
    UINT32 _ui4_page_factory
){
    ui4_page_factory = _ui4_page_factory;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_main_set_visibility
 *
 * Description:
 *      Set the page id of the factory page.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_main_set_visibility(
    BOOL b_visible)
{
    c_wgl_set_visibility(h_frm_main, b_visible ? WGL_SW_NORMAL : WGL_SW_HIDE);
    c_wgl_repaint(h_frm_main,NULL,TRUE);
    return MENUR_OK;
}


INT32 menu_main_get_visibility(
    BOOL* b_visible)
{
    c_wgl_get_visibility(h_frm_main, b_visible);
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_main_update_input_ind
 *
 * Description:
 *      Update the input source indicator for current input source.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_main_update_input_ind(VOID)
{
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_chg_lang
 *
 * Description:
 *      Change the menu language. It will call all the pages'
 * (*pf_menu_page_update)() callback function with the MENU_PAGE_UMASK_CHG_LANG.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_chg_lang(
    UINT16 ui2_lang
){
    if(ui2_lang >= MLM_MENU_NUM_LANG)
    {
        return MENUR_INV_ARG;
    }

    if(ui2_g_menu_curr_lang != ui2_lang)
    {
        ui2_g_menu_curr_lang = ui2_lang;

        menu_main_set_title(ui2_msg_id_title);

        menu_main_chg_backbar();

        menu_pm_update_all(MENU_PAGE_UMASK_CHG_LANG);
    }

    menu_pm_repaint();
    menu_pm_refresh();
    /* For Y!W */
    a_tv_custom_set_lang(ui2_lang);

#ifdef LINUX_TURNKEY_SOLUTION
    a_tv_custom_set_3rd_app_info();
#endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_set_font_name
 *
 * Description:
 *      The font name that menu uses.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID menu_set_font_name(const CHAR* _s_font_name)
{
    c_strcpy(s_font_name, _s_font_name);
}

/*----------------------------------------------------------------------------
 * Name: menu_font_name
 *
 * Description:
 *      The font name that menu uses.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
CHAR* menu_font_name(VOID)
{
    return s_font_name;
}


/*----------------------------------------------------------------------------
 * Name: menu_set_osd_offset
 *
 * Description:
 *      Set the offset of menu OSD. It will not repaint the menu.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_set_osd_offset(
    INT32 i4_hoffset,
    INT32 i4_voffset
){
    GL_RECT_T t_rect;
    i4_osd_hoffset = i4_hoffset;
    i4_osd_voffset = i4_voffset;

    SET_RECT_BY_SIZE(&t_rect,
                     (SCREEN_W - i4_osd_width)/2 + i4_osd_hoffset,
                     (SCREEN_H - i4_osd_height)/2 + i4_osd_voffset,
                     i4_osd_width,
                     i4_osd_height);

    c_wgl_move(h_frm_main, &t_rect, WGL_NO_AUTO_REPAINT);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_get_osd_offset
 *
 * Description:
 *      Get the offset of menu OSD.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_get_osd_offset(
    INT32* pi4_hoffset,
    INT32* pi4_voffset
){
    if(pi4_hoffset == NULL ||
       pi4_voffset == NULL)
    {
        return MENUR_INV_ARG;
    }

    *pi4_hoffset = i4_osd_hoffset;
    *pi4_voffset = i4_osd_voffset;

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_set_osd_size
 *
 * Description:
 *      Set the size of menu OSD. It will not repaint the menu.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_set_osd_size(
    INT32 i4_width,
    INT32 i4_height
){
    GL_RECT_T t_rect;
    i4_osd_width = i4_width;
    i4_osd_height = i4_height;

    SET_RECT_BY_SIZE(&t_rect,
                     (SCREEN_W - i4_osd_width)/2 + i4_osd_hoffset,
                     (SCREEN_H - i4_osd_height)/2 + i4_osd_voffset,
                     i4_osd_width,
                     i4_osd_height);

    c_wgl_move(h_frm_main, &t_rect, WGL_NO_AUTO_REPAINT);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_get_osd_size
 *
 * Description:
 *      Get the offset of menu OSD.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_get_osd_size(
    INT32* pi4_width,
    INT32* pi4_height
){
    if(pi4_width == NULL ||
       pi4_height == NULL)
    {
        return MENUR_INV_ARG;
    }

    *pi4_width = i4_osd_width;
    *pi4_height = i4_osd_height;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_set_osd_alpha
 *
 * Description:
 *      Set the alpha of menu OSD. Note: It only change the alpha of the main
 *  frame. So the effect would be not good :(
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_set_osd_alpha(
    UINT8  ui1_alpha
){
    INT32 i4_ret;

    ui1_osd_alpha = ui1_alpha;

    if(b_using_fading)
    {
        i4_ret = c_gl_plane_set_alpha(h_plane,  ui1_alpha);
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_set_alpha(h_frm_main, ui1_osd_alpha);
        MENU_CHK_FAIL(i4_ret);
    }


    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_get_osd_alpha
 *
 * Description:
 *      Get the alpha of menu OSD.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_get_osd_alpha(
    UINT8*  pui1_alpha
){
    if(pui1_alpha == NULL)
    {
        return MENUR_INV_ARG;
    }

    *pui1_alpha = ui1_osd_alpha;

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_set_hide_delay
 *
 * Description:
 *      Set the hide delay of menu.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_set_hide_delay(
    UINT32 ui4_delay1,
    UINT32 ui4_delay2
){
    ui4_hide_delay1 = ui4_delay1;
    ui4_hide_delay2 = ui4_delay2;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_get_osd_alpha
 *
 * Description:
 *      Get the hide delay of menu.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_get_hide_delay(
    UINT32* pui4_delay1,
    UINT32* pui4_delay2
){
    if(pui4_delay1 == NULL ||
       pui4_delay2 == NULL)
    {
        return MENUR_INV_ARG;
    }

    *pui4_delay1 = ui4_hide_delay1;
    *pui4_delay2 = ui4_hide_delay2;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_canvas_width
 *
 * Description:
 *      Get canvas width. The canvas width is idnetical to screen width.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT32 menu_canvas_width(VOID)
{
    return ui4_canvas_width;
}


/*----------------------------------------------------------------------------
 * Name: menu_canvas_height
 *
 * Description:
 *      Get canvas height. The canvas height is idnetical to screen height.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT32 menu_canvas_height(VOID)
{
    return ui4_canvas_height;
}

/*----------------------------------------------------------------------------
 * Name: menu_set_scan_type
 *
 * Description:
 *      The current scan type.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID menu_set_scan_type (
    MENU_SCAN_TYPE_T _e_scan_type
){
    e_scan_type = _e_scan_type;
}

/*----------------------------------------------------------------------------
 * Name: menu_get_scan_type
 *
 * Description:
 *      The current scan type.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
MENU_SCAN_TYPE_T  menu_get_scan_type (VOID)
{
    return e_scan_type;
}

/*----------------------------------------------------------------------------
 * Name: menu_show_backbar
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32  menu_show_backbar (BOOL b_show,
                          BOOL b_repaint)
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(h_backbar_frm,
                                  (b_show == TRUE) ? WGL_SW_RECURSIVE : WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    if(b_repaint)
    {
        menu_pm_repaint();
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_get_backbar_handle
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32  menu_get_backbar_handle (HANDLE_T *ph_handle)
{
    *ph_handle = h_backbar_frm;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_get_backbar_title_handle
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32  menu_get_backbar_title_handle (HANDLE_T *ph_handle)
{
    *ph_handle = h_txt_title;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_set_focus_on_backbar
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32  menu_set_focus_on_backbar (BOOL b_repaint)
{
    c_wgl_set_focus(h_backbar_frm,
                    (b_repaint == TRUE) ? WGL_SYNC_AUTO_REPAINT : WGL_NO_AUTO_REPAINT);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[128] = {0};
    c_uc_ps_to_w2s("back", w2s_str, 128);
    a_app_tts_play(w2s_str, 128);
#endif

/* Don't set help tip here for CR:341363    xuan add at 20110511
    //menu_hide_help_tip();
    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    menu_set_and_trigger_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
*/

    return MENUR_OK;
}

INT32 menu_backbar_move_by_zoom_mode(VOID)
{
    INT32 i4_ret;
    GL_RECT_T t_rect = {0};
    UINT8 ui1_zoom_mode = 0;

    SET_RECT_BY_SIZE(&t_rect,
                     BACK_BAR_X,
                     BACK_BAR_Y,
                     BACK_BAR_W,
                     BACK_BAR_H
                     );

    a_cfg_cust_get_zoom_mode(&ui1_zoom_mode);

    if (APP_CFG_CUST_ZOOM_MODE_ON == ui1_zoom_mode)
    {
        t_rect.i4_left -= 10;
        i4_ret = c_wgl_move(h_backbar_frm, &t_rect, WGL_NO_AUTO_REPAINT);
    }
    else
    {
        i4_ret = c_wgl_move(h_backbar_frm, &t_rect, WGL_NO_AUTO_REPAINT);
    }

    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _menu_backbar_proc_zoom_mode(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               param1,
                VOID*               param2
                )
{
    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
            menu_backbar_move_by_zoom_mode();
            c_wgl_set_highlight_widget(menu_get_backbar_txt_handle());
            break;
        case WGL_MSG_LOSE_FOCUS:
            menu_backbar_move_by_zoom_mode();
            c_wgl_set_highlight_widget(NULL_HANDLE);
            break;
        case WGL_MSG_KEY_DOWN:
            if ((UINT32)param1 == BTN_RETURN)
            {
                menu_backbar_move_by_zoom_mode();
                c_wgl_set_highlight_widget(NULL_HANDLE);
            }
            break;
        default:
            break;
    }

    return pf_backbar_fct(h_widget, ui4_msg, param1, param2);

}

/*----------------------------------------------------------------------------
 * Name: menu_set_backbar_proc
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32  menu_set_backbar_proc (wgl_widget_proc_fct pf_proc)
{
    INT32 i4_ret;

    if (NULL == pf_proc)
    {
        pf_proc = _menu_backbar_common_proc_fct;
    }

#if 1
    pf_backbar_fct = pf_proc;
    i4_ret = c_wgl_set_widget_proc(h_backbar_frm, _menu_backbar_proc_zoom_mode);
    MENU_LOG_ON_FAIL(i4_ret);
#else
    i4_ret = c_wgl_set_widget_proc(h_backbar_frm, pf_proc);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_set_backbar_paremeter
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_set_backbar_paremeter (HANDLE_T  h_first_widget,
                                  HANDLE_T  h_last_widget)
{
    h_backbar_first_widget = h_first_widget;
    h_backbar_last_widget  = h_last_widget;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_set_and_trigger_help_tip
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_set_and_trigger_help_tip (UTF16_T* w2s_text)
{
    INT32 i4_ret;

    if (h_menu_help_tip == NULL_HANDLE)
    {
        return MENUR_FAIL;
    }

    i4_ret = a_help_tip_set_info(h_menu_help_tip, w2s_text);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_help_tip_trigger(h_menu_help_tip);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}
#ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT
INT32 a_menu_set_help_tip_blue_button_enable_status (BOOL b_status)
{
    INT32 i4_ret = MENUR_OK;

    if(h_menu_help_tip == NULL_HANDLE)
    {
        return MENUR_FAIL;
    }

    i4_ret = a_menu_set_help_tip_enable_status(h_menu_help_tip,b_status);

    MENU_LOG_ON_FAIL(i4_ret);

    g_help_tip_blue_button_enable_status = b_status;

    return MENUR_OK;
}
BOOL a_menu_get_help_tip_blue_button_enable (VOID)
{
    return g_help_tip_blue_button_enable_status;
}

#endif

INT32 menu_show_hide_enger_start_icon(BOOL b_show_status, BOOL b_repaint)
{
    INT32 i4_ret = 0;
    UINT16 ui2_idx = 0;
    BOOL   b_is_chg = 0;
    BOOL   b_old_show_status = FALSE;
    if(!b_need_energy_start)
    {
        return MENUR_OK;
    }

    c_wgl_get_visibility(h_energy_start_icon_img, &b_old_show_status);
    if (b_old_show_status == b_show_status) return MENUR_OK;
    a_cfg_get_preset_pic_mode_chg_status(ui2_idx,&b_is_chg);
    if(b_show_status&&(!b_is_chg))
    {
        i4_ret = c_wgl_set_visibility(h_energy_start_icon_img, WGL_SW_NORMAL);
        if(i4_ret < 0)
        {
            return MENUR_FAIL;
        }
     }
    else if(b_show_energy_start_icon)
    {
       i4_ret = c_wgl_set_visibility(h_energy_start_icon_img, WGL_SW_HIDE);
       if(i4_ret < 0)
       {
           return MENUR_FAIL;
       }
    }
     b_show_energy_start_icon = b_show_status;
     if (b_repaint)
     {
        i4_ret = c_wgl_repaint(h_energy_start_icon_img, NULL, TRUE);
     }
     if(i4_ret < 0)
     {
         return MENUR_FAIL;
     }
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_set_and_trigger_help_tip
 *
 * Description:
 *      set help tip text, and then trigger its timer.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_set_and_show_help_tip (UTF16_T*    w2s_text)
{
    INT32 i4_ret;

    if(h_menu_help_tip == NULL_HANDLE)
    {
        return MENUR_FAIL;
    }

    i4_ret = a_help_tip_set_info(h_menu_help_tip, w2s_text);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_help_tip_show(h_menu_help_tip);
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    _menu_help_tip_tts_play(MLM_MENU_TEXT(0, ui2_help_tip_mlm_key));
#endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_hide_help_tip
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_hide_help_tip(VOID)
{
    INT32 i4_ret;

    if (h_menu_help_tip == NULL_HANDLE)
    {
        return MENUR_FAIL;
    }

    i4_ret = a_help_tip_hide(h_menu_help_tip);
    MENU_CHK_FAIL(i4_ret);
    if(b_show_energy_start_icon)
    {
        menu_show_hide_enger_start_icon(FALSE, FALSE);
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_move_help_tip
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_move_help_tip (INT32     i4_left,
                          INT32     i4_top,
                          INT32     i4_width,
                          INT32     i4_height,
                          BOOL      b_repaint)
{
    GL_RECT_T  t_rect;

    if (i4_left == MENU_PAGE_HELP_TIP_DEF_RECT)
    {
        i4_left = HELP_TIP_FRAME_X;
    }
    if (i4_top == MENU_PAGE_HELP_TIP_DEF_RECT)
    {
        i4_top = HELP_TIP_FRAME_Y;
    }
    if (i4_width == MENU_PAGE_HELP_TIP_DEF_RECT)
    {
        i4_width = HELP_TIP_FRAME_W;
    }
    if (i4_height == MENU_PAGE_HELP_TIP_DEF_RECT)
    {
         i4_height = HELP_TIP_FRAME_H;
    }

    t_rect.i4_left   = i4_left;
    t_rect.i4_top    = i4_top;
    t_rect.i4_right  = i4_left + i4_width;
    t_rect.i4_bottom = i4_top + i4_height;

    MENU_CHK_FAIL (a_help_tip_move(h_menu_help_tip, &t_rect, b_repaint));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_set_page_hide
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_set_page_hide (BOOL b_hide)
{
    b_hide_common_page = b_hide;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_get_page_hide
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_get_page_hide (BOOL *pb_hide)
{
    *pb_hide = b_hide_common_page;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_get_homebar_handle
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32  menu_get_homebar_handle (HANDLE_T *ph_handle)
{
    *ph_handle = h_homebar_frm;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_show_homebar
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32  menu_show_homebar (BOOL b_show,
                          BOOL b_repaint)
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(h_homebar_frm,
                                  (b_show == TRUE) ? WGL_SW_RECURSIVE : WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    if(b_repaint)
    {
        menu_pm_repaint();
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_set_focus_on_homebar
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32  menu_set_focus_on_homebar (BOOL b_repaint)
{

    c_wgl_set_focus(h_homebar_frm, b_repaint?WGL_SYNC_AUTO_REPAINT:WGL_NO_AUTO_REPAINT);

/* Don't set help tip here for CR:341363    xuan add at 20110511
    menu_hide_help_tip();
    menu_set_and_trigger_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
*/
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_set_homebar_proc
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32  menu_set_homebar_proc (wgl_widget_proc_fct pf_proc)
{
    INT32 i4_ret;

    if (NULL == pf_proc)
    {
        pf_proc = _menu_homebar_common_proc_fct;
    }

    DEBUG_PM( DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} h_homebar_frm:0x%x, \n", __FUNCTION__,__LINE__, (unsigned int)h_homebar_frm )); );

    if( h_homebar_frm == 0 )
    {
        DBG_LOG_PRINT(("[MENU][MNGR]{%s,%d} Error: h_homebar_frm is NULL \n", __FUNCTION__,__LINE__ ));
        return MENUR_FAIL;
    }

    i4_ret = c_wgl_set_widget_proc(h_homebar_frm, pf_proc);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

VOID menu_page_set_hide_main_inpageswitch(VOID)
{
    b_hide_main_menu_in_page_switch = FALSE;
    return ;
}

/*----------------------------------------------------------------------------
 * Name: menu_help_tip_keytip_set_focus
 *
 * Description:
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_help_tip_keytip_set_focus(HANDLE_T h_last_widget,
                                 UINT16 ui2_idx,
                                 BOOL b_repaint)
{
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_help_tip_keytip_set_proc
 *
 * Description:
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_help_tip_keytip_set_proc(wgl_widget_proc_fct pf_proc1,
                                wgl_widget_proc_fct pf_proc2)
{
    INT32 i4_ret;

    i4_ret = a_help_tip_set_proc(h_menu_help_tip,pf_proc1,pf_proc2);
    MENU_CHK_FAIL(i4_ret);


    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_help_tip_keytip_show
 *
 * Description:
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_help_tip_keytip_show (BOOL b_show)
{
#if 0
    INT32 i4_ret;

    i4_ret = a_help_tip_keytip_show(h_menu_help_tip, b_show);
    MENU_LOG_ON_FAIL(i4_ret);

    /* If b_show is FALSE, the last text should be cleaned. */
    if(b_show)
    {
        i4_ret = a_help_tip_change_lang(h_menu_help_tip,
                                        MENU_TEXT(MLM_MENU_KEY_LAST),
                                        MENU_TEXT(MLM_MENU_KEY_EXIT));
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = a_help_tip_change_lang(h_menu_help_tip,
                                        MENU_TEXT(MLM_MENU_KEY_EMPTY),
                                        MENU_TEXT(MLM_MENU_KEY_EXIT));
        MENU_CHK_FAIL(i4_ret);


        a_help_tip_visible(h_menu_help_tip);
    }
#endif
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_change_help_tip_lang
 *
 * Description:
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_change_help_tip_lang (VOID)
{
    INT32 i4_ret;

    if(h_menu_help_tip == NULL_HANDLE)
    {
        return MENUR_INV_STATE;
    }

    i4_ret = a_help_tip_change_lang(h_menu_help_tip,
                                    MENU_TEXT(MLM_MENU_KEY_LAST),
                                    MENU_TEXT(MLM_MENU_KEY_EXIT));
    MENU_CHK_FAIL(i4_ret);


    return MENUR_OK;
}

#ifdef APP_TTS_SUPPORT
VOID a_menu_tts_play_id_record(INT32 id)
{
    i4_tts_play_id = id;
}

INT32 a_menu_tts_stop(VOID)
{
    if (i4_tts_play_id != 0)
    {
        return a_app_tts_stop(i4_tts_play_id);
    }
    else
    {
        return MENUR_OK;
    }
}

UTF16_T* menu_help_tip_tts_play_record(UINT16 ui2_lang, UINT16 ui2_key)
{
    ui2_help_tip_mlm_key = ui2_key;
    return MLM_MENU_TEXT(ui2_lang, ui2_key);
}

INT32 menu_help_tip_stop_tts_play(VOID)
{
    return _menu_help_tip_stop_tts_play();
}

static INT32 _menu_help_tip_stop_tts_play(VOID)
{
    INT32 i4_ret;

    return MENUR_OK;          //   remove  menu help tip tts play  16/12/28
#if NEVER    //CID:4491825
    if (h_timer_tts != NULL_HANDLE)
    {
        i4_ret = c_timer_stop(h_timer_tts);
        MENU_CHK_FAIL(i4_ret);

        c_mem_free(p_w2s_tts_str);
        p_w2s_tts_str = NULL;
    }

    i4_ret = a_app_tts_stop(i4_tts_play_id);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
#endif
}

static VOID _menu_help_tip_tts_play_timer_cb_fct(
                                    VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3)
{
    INT32 i4_ret = 0;

    if (1 == a_app_tts_get_string_state())
    {
        i4_ret = c_timer_stop(h_timer_tts);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_timer_start(
                        h_timer_tts,
                        5000,
                        X_TIMER_FLAG_ONCE,
                        _menu_help_tip_tts_play_timer_cb,
                        NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        return;
    }

    i4_ret = a_app_tts_play(p_w2s_tts_str, c_uc_w2s_strlen(p_w2s_tts_str));
    MENU_LOG_ON_FAIL(i4_ret);
    a_menu_tts_play_id_record(i4_ret);

    c_mem_free(p_w2s_tts_str);
    p_w2s_tts_str = NULL;

    i4_ret = c_timer_delete(h_timer_tts);
    MENU_LOG_ON_FAIL(i4_ret);

    if (i4_ret >= 0)
    {
        h_timer_tts = NULL_HANDLE;
    }
}

static VOID _menu_help_tip_tts_play_timer_cb (HANDLE_T  pt_tm_handle,
                                   VOID*     pv_tag)
{
    menu_request_context_switch(_menu_help_tip_tts_play_timer_cb_fct,
                                    NULL,
                                    NULL,
                                    NULL);
}

static INT32 _menu_help_tip_tts_play(UTF16_T *p_w2s_str)
{
    INT32 i4_ret = 0;
    SIZE_T  t_size = 0;

    return MENUR_OK;          //   remove  menu help tip tts play  16/12/28
#if NEVER    //CID:4492028
    if (p_w2s_tts_str != NULL)
    {
        c_mem_free(p_w2s_tts_str);
        p_w2s_tts_str = NULL;
    }

    t_size = c_uc_w2s_strlen(p_w2s_str);
    p_w2s_tts_str = c_mem_alloc((t_size+1)*sizeof(UTF16_T));
    if (NULL == p_w2s_tts_str)
    {
        MENU_CHK_FAIL(-1);
    }
    c_memset(p_w2s_tts_str, 0, (t_size+1)*sizeof(UTF16_T));
    c_uc_w2s_strcpy(p_w2s_tts_str, p_w2s_str);

    if (NULL_HANDLE == h_timer_tts)
    {
        i4_ret = c_timer_create(&h_timer_tts);
        MENU_LOG_ON_FAIL(i4_ret);
        if (i4_ret < 0)
        {
            c_mem_free(p_w2s_tts_str);
            return MENUR_FAIL;
        }
    }

    i4_ret = c_timer_stop(h_timer_tts);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_timer_start(
                    h_timer_tts,
                    5000,
                    X_TIMER_FLAG_ONCE,
                    _menu_help_tip_tts_play_timer_cb,
                    NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
#endif
}
#endif

INT32 menu_main_help_tip_repaint ()
{
    return c_wgl_repaint(h_menu_help_tip,NULL,FALSE);
}

/*----------------------------------------------------------------------------
 * Name: menu_set_help_tip
 *
 * Description:
 *      set help tip text.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_set_help_tip (UTF16_T*    w2s_text)
{
    INT32 i4_ret;

    if(h_menu_help_tip == NULL_HANDLE)
    {
        return MENUR_FAIL;
    }

    i4_ret = a_help_tip_set_info(h_menu_help_tip, w2s_text);
    MENU_CHK_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
    _menu_help_tip_tts_play(MLM_MENU_TEXT(0, ui2_help_tip_mlm_key));
    #endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_main_title_hide
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
INT32 menu_main_title_hide (BOOL b_show)
{
    return c_wgl_set_visibility(h_main_title_txt,b_show ? WGL_SW_NORMAL : WGL_SW_HIDE);
}

/*----------------------------------------------------------------------------
 * Name: menu_main_title_hide
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
BOOL menu_hot_key_page_with_animation(VOID)
{
    return b_hot_key_page_with_animation;
}

BOOL menu_get_help_tip_flag(VOID)
{
    return b_show_help_text;
}

VOID menu_set_help_tip_flag(BOOL b_show)
{
    b_show_help_text = b_show;
}

VOID menu_help_tip_key_clrreg(VOID)
{
    c_memset(&_help_tip_back_key_cb, 0, sizeof(_help_tip_back_key_cb));
}

INT32 menu_help_tip_key_reg(HELP_TIP_CB_PAGE e_page, T_HELP_TIP_REG *pt_reg)
{
    if (NULL == pt_reg
        || e_page >= E_HELP_TIP_CB_PAGE_LAST)
    {
        return MENUR_INV_ARG;
    }

    if (pt_reg->p_fct != NULL)
    {
        _help_tip_back_key_cb.ui2_reg_nr++;
        _help_tip_back_key_cb.ap_fct[e_page] = pt_reg->p_fct;
        _help_tip_back_key_cb.aui4_page_id[e_page] = pt_reg->ui4_page_id;
    }

    return MENUR_OK;
}

INT32 menu_help_tip_key_unreg(HELP_TIP_CB_PAGE e_page)
{
    if (e_page < E_HELP_TIP_CB_PAGE_LAST
        && _help_tip_back_key_cb.ap_fct[e_page] != NULL)
    {
        _help_tip_back_key_cb.ap_fct[e_page] = NULL;
        _help_tip_back_key_cb.aui4_page_id[e_page] = 0;
        _help_tip_back_key_cb.ui2_reg_nr--;
    }

    return MENUR_OK;
}

BOOL menu_help_tip_get_focus(VOID)
{
    return a_help_tip_get_focus(h_menu_help_tip);
}

UINT32 menu_nav_get_pre_page_id_from_nav_stack(VOID)
{
    UINT16 ui2_stack_ptr = (UINT16)(ui2_nav_stack_top - 1);

    return aui4_nav_stack[ui2_stack_ptr];
}

UINT32 menu_get_current_page_id()
{
   return ui4_page_crnt;
}

INT32 menu_repaint(INT32   i4_argc,const CHAR** pps_argv)
{
    if(i4_argc != 2)
    {
        DBG_INFO(("error this cmd allow 2 args = %d\n",i4_argc));
    }

    if(atoi(pps_argv[1]) == 0 )
    {
        MENU_LOG_ON_FAIL(c_wgl_repaint(h_frm_main, NULL, TRUE));
    }
    else if(atoi(pps_argv[1]) == 1)
    {
        menu_pm_repaint_current_page();
    }
    return 0;
}

BOOL menu_get_nav_go(VOID)
{
    return b_is_nav_go;
}

VOID menu_set_nav_go(BOOL b_value)
{
    b_is_nav_go = b_value;
}

static VOID _timer_scrl_title_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    UINT32 ui4_title_len = c_uc_w2s_strlen(w2s_text_title);
    if (ui4_title_len > MENU_TITLE_SCRL_LEN)
    {
        if (i4_scrl_title_offset + MENU_TITLE_SCRL_LEN > ui4_title_len + 1)
        {
            i4_scrl_title_offset = 0;
        }

        MENU_CHK_FAIL(c_wgl_do_cmd(h_txt_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          w2s_text_title + i4_scrl_title_offset,
                          WGL_PACK((UINT16)0xFF)));


        c_wgl_repaint(h_txt_title, NULL, FALSE);
        i4_scrl_title_offset++;
    }
}

INT32 menu_scrl_title_reset(UTF16_T* w2s_new_title)
{
    INT32 i4_ret = MENUR_OK;
    c_uc_w2s_strcpy(w2s_text_title, w2s_new_title);
    i4_scrl_title_offset = 0;
    i4_ret = menu_scrl_title_timer_stop();
    MENU_LOG_ON_FAIL(i4_ret);
    UINT32 ui4_title_len = c_uc_w2s_strlen(w2s_text_title);
    if (ui4_title_len >= MENU_TITLE_SCRL_LEN)
    {
        i4_ret = menu_scrl_title_timer_start();
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return i4_ret;
}

INT32 menu_scrl_title_timer_start(VOID)
{
    return c_timer_start(h_srcl_title_timer,
                  MENU_TITLE_SCRL_TIMER,
                  X_TIMER_FLAG_REPEAT,
                  _timer_scrl_title_fct,
                  NULL);
}

INT32 menu_scrl_title_timer_stop(VOID)
{
    return c_timer_stop(h_srcl_title_timer);;
}


