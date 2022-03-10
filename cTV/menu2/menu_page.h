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
 * $RCSfile: menu_page.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/14 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 530b5f614fc48ad655af79370de4cf1b $
 *
 * Description:
 *         This file contains the declarations of APPLICATION-RELATED functions
 * of the MENU applcation.
 *---------------------------------------------------------------------------*/

#ifndef _MENU_PAGE_H_
#define _MENU_PAGE_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "menu2/menu.h"
#include "menu2/menu_help_lst.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef enum{
    MENU_PAGE_HT_NONE = 0,
    MENU_PAGE_HT_BACK,
    MENU_PAGE_HT_PORT,
    MENU_PAGE_HT_CUSTOM,
    MENU_PAGE_HT_CUST_ITEM_ID,
}MENU_PAGE_HINT_TYPE_T;

typedef enum{
    MENU_PAGE_PORT_FIRST,
    MENU_PAGE_PORT_LAST,
    MENU_PAGE_PORT_TOP,
    MENU_PAGE_PORT_BOTTOM,
    MENU_PAGE_PORT_LEFT,
    MENU_PAGE_PORT_RIGHT
}MENU_PAGE_HINT_PORT_T;

typedef struct _MENU_PAGE_HINT_T{
    MENU_PAGE_HINT_TYPE_T   e_hint_type;
    union{
        MENU_PAGE_HINT_PORT_T   e_port;
        VOID*                   pv_custom_hint;
        UINT16 u16_item_id;
    }u;
}MENU_PAGE_HINT_T;

typedef enum {
    MENU_PAGE_STATE_NEW = 0,
    MENU_PAGE_STATE_HIDE,
    MENU_PAGE_STATE_SHOW,
    MENU_PAGE_STATE_FOCUS,
    MENU_PAGE_STATE_DEAD
} MENU_PAGE_STATE_T;

typedef enum {
    MENU_PAGE_EVENT_SHOW,
    MENU_PAGE_EVENT_HIDE,
    MENU_PAGE_EVENT_FOCUS,
    MENU_PAGE_EVENT_UNFOCUS
} MENU_PAGE_EVENT_T;

/* Page Event Listener */
typedef VOID (*menu_page_event_listener_fct)(UINT32            ui4_page_id,
                                             MENU_PAGE_EVENT_T e_page_event);

typedef INT32 (*menu_page_create_fct)(UINT32 ui4_page_id,
                                     VOID*  pv_create_data);
typedef INT32 (*menu_page_destroy_fct)(UINT32 ui4_page_id);
typedef INT32 (*menu_page_show_fct)(UINT32 ui4_page_id);
typedef INT32 (*menu_page_hide_fct)(UINT32 ui4_page_id);
typedef INT32 (*menu_page_get_focus_fct)(UINT32 ui4_page_id,
                                         MENU_PAGE_HINT_T* pt_hint);
typedef INT32 (*menu_page_lose_focus_fct)(UINT32 ui4_page_id);
typedef INT32 (*menu_page_update_fct)(UINT32 ui4_page_id,
                                     UINT32 ui4_update_mask);

typedef struct _MENU_PAGE_FCT_TBL_T
{
    menu_page_create_fct        pf_menu_page_create;
    menu_page_destroy_fct       pf_menu_page_destroy;
    menu_page_show_fct          pf_menu_page_show;
    menu_page_hide_fct          pf_menu_page_hide;
    menu_page_get_focus_fct     pf_menu_page_get_focus;
    menu_page_lose_focus_fct    pf_menu_page_lose_focus;
    menu_page_update_fct        pf_menu_page_update;
} MENU_PAGE_FCT_TBL_T;

typedef enum
{
    E_HELP_TIP_CB_PAGE_DEVICE_STATUS_INFO = 0,
    E_HELP_TIP_CB_PAGE_TIME_LOCAL_SETTING,
    E_HELP_TIP_CB_PAGE_MC_VERSION,
    E_HELP_TIP_CB_PAGE_TV_NAME,
    E_HELP_TIP_CB_PAGE_LAST
}HELP_TIP_CB_PAGE;

typedef INT32 (*help_tip_cb)(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2,
                BOOL*               pb_processed);

typedef struct _T_HELP_TIP_REG
{
    help_tip_cb     p_fct;
    UINT32          ui4_page_id;
}T_HELP_TIP_REG;

/* Update Mask */
#define MENU_PAGE_UMASK_CHG_LANG   MAKE_BIT_MASK_32(0)
#define MENU_PAGE_UMASK_CHG_THEME  MAKE_BIT_MASK_32(1)
#define MENU_PAGE_UMASK_REFRESH    MAKE_BIT_MASK_32(2)
#define MENU_PAGE_UMASK_RESUME     MAKE_BIT_MASK_32(3)

/* Help tip */
#define MENU_PAGE_HELP_TIP_DEF_RECT     ((INT32)    -1)

/* Utility Macro */
#define MENU_COLOR_COPY(_dst, _src)                                          \
            c_memcpy((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

#ifdef APP_TTS_SUPPORT
#define MENU_TEXT(key)   \
            menu_help_tip_tts_play_record(ui2_g_menu_curr_lang, (key))
#else
#define MENU_TEXT(key)   \
            MLM_MENU_TEXT(ui2_g_menu_curr_lang, (key))
#endif

#define MENU_TTS_TEXT(key)   \
            MLM_MENU_TEXT(MLM_MENU_LANG_ENG, (key))

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
extern UINT16 ui2_g_menu_curr_lang;

extern BOOL   b_g_menu_lazy_init_support;

extern UINT32 ui4_page_factory;

extern UINT32 ui4_page_ch_scan;
extern UINT32 ui4_page_ch_scan_new;

extern UINT32 ui4_page_vid_professional;

/*-----------------------------------------------------------------------------
                    external function prototype
 ----------------------------------------------------------------------------*/
/* page operation functions */
extern INT32 menu_page_get_cnt_frm(UINT32 ui4_page_id,
                                   HANDLE_T* ph_cnt_frm);

extern INT32 menu_page_set_data(UINT32 ui4_page_id,
                                VOID* pv_data);

extern INT32 menu_page_get_data(UINT32 ui4_page_id,
                                VOID** ppv_data);

extern INT32 menu_page_set_proc_func(UINT32 ui4_page_id,
                                     wgl_widget_proc_fct pf_wdgt_proc);

extern INT32 menu_page_get_state(UINT32 ui4_page_id,
                                 MENU_PAGE_STATE_T* pe_state);

/* page manager */
extern INT32 menu_pm_init(VOID);

extern INT32 menu_pm_page_create(MENU_PAGE_FCT_TBL_T* pt_page_fct_tbl,
                                 VOID*   pv_create_data,
                                 UINT32* pui4_page_id);

extern INT32 menu_pm_page_destroy(UINT32 ui4_page_id);

extern INT32 menu_pm_add_tab(UINT32 ui4_page_id,
                             WGL_HIMG_TPL_T  h_img_normal,
                             WGL_HIMG_TPL_T  h_img_hlt,
                             WGL_HIMG_TPL_T  h_img_sel,
                             WGL_HIMG_TPL_T  h_img_disable,
                             UINT16* pui2_idx);

extern INT32 menu_pm_remove_tab(UINT16 ui2_idx);

extern INT32 menu_pm_enable_tab(UINT16 ui2_idx,
                                BOOL b_enable);

extern INT32 menu_pm_hide_tab(UINT16 ui2_idx,
                                BOOL b_hidden);

extern INT32 menu_pm_get_tab_num(UINT16* pui2_tab_num);

extern INT32 menu_pm_show(VOID);

extern INT32 menu_pm_show_with_tab(UINT16 ui2_tab_idx);

extern INT32 menu_pm_show_with_tab_ex(UINT16   ui2_tab_idx,
                                      BOOL     b_show);

extern INT32 menu_pm_show_first_tab(VOID);

extern INT32 menu_pm_show_last_tab(VOID);

extern INT32 menu_pm_show_by_latest_tab(VOID);

extern INT32 menu_pm_show_by_latest_state(VOID);

extern INT32 menu_pm_show_by_factory_page(VOID);

extern INT32 menu_pm_resume_show(VOID);

extern BOOL menu_pm_is_resume_show(VOID);

extern INT32 menu_pm_request_resume_show(
    UINT16  ui2_tab_idx,
    UINT32* pui4_page_ids,
    UINT16  ui2_page_num
);

extern INT32 menu_pm_short_cut_show(MENU_SHORT_CUT_T e_short_cut_key);

extern INT32 menu_pm_hide(VOID);

extern INT32 menu_pm_repaint(VOID);

extern INT32 menu_pm_update(UINT32 ui4_page_id,
                            UINT32 ui4_update_mask);

extern INT32 menu_pm_update_all(UINT32 ui4_update_mask);

extern INT32 menu_pm_get_plane(GL_HPLANE_T* ph_plane);
extern INT32 menu_pm_get_canvas(HANDLE_T* ph_canvas);
extern INT32 menu_pm_get_root_frm(HANDLE_T* ph_frm_root);
extern INT32 menu_pm_get_main_frm(HANDLE_T* ph_frm_main);
extern INT32 menu_pm_get_home_bar_frm( HANDLE_T* ph_frm_main );
extern INT32 menu_pm_get_last_shadow_item( HANDLE_T* ph_last_shadow_item);
extern INT32 menu_pm_get_energy_start_icon_handle( HANDLE_T* ph_energy_start_icon_handle );
extern HANDLE_T menu_get_backbar_txt_handle(VOID);

extern INT32 menu_pm_get_help_tip_item( HANDLE_T* ph_help_tip_item );

extern INT32 menu_pm_set_page_event_listener(menu_page_event_listener_fct  pf_fct);

/* navigation operations */
extern INT32 menu_nav_go(UINT32 ui4_page_id,
                         MENU_PAGE_HINT_T* pt_hint);
extern INT32 menu_nav_back(VOID);
extern INT32 menu_nav_back_and_go(UINT32 ui4_page_id,
                                  MENU_PAGE_HINT_T* pt_hint);
extern INT32 menu_nav_go_home_menu (VOID);
extern INT32 menu_nav_go_to_factory_page(VOID);

extern INT32 menu_nav_go_direct(UINT16   ui2_tab_idx,
                                UINT32*  pui4_page_ids,
                                UINT16   ui2_page_num,
                                MENU_PAGE_HINT_T* pt_hint);

extern INT32 menu_nav_go_direct_ex(UINT16   ui2_tab_idx,
                                   UINT32*  pui4_page_ids,
                                   UINT16   ui2_page_num,
                                   MENU_PAGE_HINT_T* pt_hint);

extern INT32 menu_nav_anim_go(UINT32            ui4_page_id,
                              MENU_PAGE_HINT_T* pt_hint);

extern INT32 menu_nav_get_nav_stack(UINT16* pui2_tab_idx,
                                    UINT32* pui4_page_ids,
                                    UINT16* pui2_size);

extern INT32 menu_nav_get_crnt_page(UINT32* pui4_page_id);

/* Update Operations */
extern INT32 menu_chg_lang(UINT16 ui2_lang);

extern INT32 menu_pm_refresh(VOID);

/* OSD adjustment */
extern INT32 menu_set_osd_offset(INT32 i4_hoffset,
                                 INT32 i4_voffset);

extern INT32 menu_get_osd_offset(INT32* pi4_hoffset,
                                 INT32* pi4_voffset);

extern INT32 menu_set_osd_size(INT32 i4_width,
                               INT32 i4_height);

extern INT32 menu_get_osd_size(INT32* pi4_width,
                               INT32* pi4_height);

extern INT32 menu_set_osd_alpha(UINT8  ui1_alpha);

extern INT32 menu_get_osd_alpha(UINT8* pui1_alpha);

extern INT32 menu_set_hide_delay(UINT32 ui4_delay1,
                                 UINT32 ui4_delay2);

extern INT32 menu_get_hide_delay(UINT32* pui4_delay1,
                                 UINT32* pui4_delay2);

/* UI relative info */
extern VOID menu_set_font_name(const CHAR* s_font_name);

extern CHAR* menu_font_name(VOID);

extern UINT32 menu_canvas_width(VOID);

extern UINT32 menu_canvas_height(VOID);

/* components */
extern INT32 menu_main_set_title(UINT16 ui2_msgid_txt);
extern INT32 menu_main_set_title_text(UTF16_T* w2s_dst);
extern INT32 menu_main_chg_backbar(VOID);
extern INT32 menu_main_set_main_title(UINT16 ui2_msgid_txt);
extern INT32 menu_main_set_main_title_visibility (BOOL b_show);

extern INT32 menu_main_update_input_ind(VOID);

extern INT32 menu_show_version(BOOL    b_show,
                               BOOL    b_repaint);

extern BOOL menu_version_key_filter(UINT32  ui4_keycode);
extern VOID menu_version_tab_info( BOOL* b_tab_mode, UINT32* ui4_page_id, HANDLE_T* h_btn);

extern INT32 menu_factory_set_pageid(UINT32 ui4_page_factory);

extern INT32 menu_main_set_visibility(BOOL b_visable);
extern INT32 menu_main_get_visibility(BOOL *b_visable);

extern VOID              menu_set_scan_type (MENU_SCAN_TYPE_T e_scan_type);
extern MENU_SCAN_TYPE_T  menu_get_scan_type (VOID);

/* backbar */
extern INT32  menu_show_backbar (BOOL b_show, BOOL b_repaint);
extern INT32  menu_get_backbar_handle (HANDLE_T *ph_handle);
extern INT32  menu_get_backbar_title_handle (HANDLE_T *ph_handle);
extern INT32  menu_set_focus_on_backbar (BOOL b_repaint);
extern INT32  menu_backbar_move_by_zoom_mode(VOID);
extern INT32  menu_set_backbar_proc (wgl_widget_proc_fct pf_proc);
extern INT32  menu_set_backbar_paremeter (HANDLE_T h_first_widget, HANDLE_T h_last_widget);

/* help tip */
extern INT32 menu_set_and_trigger_help_tip (UTF16_T* w2s_text);
extern INT32 menu_hide_help_tip (VOID);
extern INT32 menu_move_help_tip (INT32  i4_left,
                                 INT32  i4_top,
                                 INT32  i4_width,
                                 INT32  i4_height,
                                 BOOL   b_repaint);

extern INT32 menu_set_page_hide (BOOL b_hide);
extern INT32 menu_get_page_hide (BOOL *pb_hide);

/* homebar */
extern INT32  menu_get_homebar_handle (HANDLE_T *ph_handle);
extern INT32  menu_show_homebar (BOOL b_show,
                                 BOOL b_repaint);
extern INT32  menu_set_focus_on_homebar (BOOL b_repaint);
extern INT32  menu_set_homebar_proc (wgl_widget_proc_fct pf_proc);

extern INT32  menu_help_tip_keytip_set_focus(HANDLE_T h_last_widget,
                                 UINT16 ui2_idx,
                                 BOOL b_repaint);
extern INT32 menu_help_tip_keytip_set_proc(wgl_widget_proc_fct pf_proc1,
                                wgl_widget_proc_fct pf_proc2);

extern INT32 menu_set_and_show_help_tip (UTF16_T*    w2s_text);
extern INT32 menu_show_hide_enger_start_icon(BOOL b_show_status, BOOL b_repaint);
extern INT32 menu_help_tip_keytip_show (BOOL b_show);

#ifdef APP_HDR_SUPPORT
typedef enum {
    MENU_DOLBY_LOGO_POS_PICTURE,
    MENU_DOLBY_LOGO_POS_PICTURE_MODE,
    MENU_DOLBY_LOGO_POS_COLOR_CALI, // For Menu/Picture/Advanced Picture/color Calibration
} EnuMenuDolbyLogoPosition;

#define MENU_DOLBY_LOGO_TEST_NEW_SIZE   1

extern INT32 menu_doly_vision_resize_logo(EnuMenuDolbyLogoPosition eMenuDolbyLogoPos);

extern INT32 menu_doly_vision_logo_show(BOOL b_show_status);
extern BOOL  menu_page_get_dolby_vision_visible(VOID);
extern INT32 menu_doly_vision_logo_show_repaint(BOOL b_show_status, BOOL b_repaint);
#endif

#ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT
extern INT32 a_menu_set_help_tip_blue_button_enable_status (BOOL b_status);
#endif
extern INT32 menu_change_help_tip_lang (VOID);
extern INT32 menu_set_help_tip (UTF16_T*    w2s_text);
extern INT32 menu_main_title_hide (BOOL b_show);
extern INT32 menu_main_help_tip_repaint();
extern INT32 menu_nav_back_ex(BOOL b_repaint);
extern VOID menu_page_set_hide_main_inpageswitch(VOID);
extern BOOL menu_hot_key_page_with_animation(VOID);
extern BOOL menu_get_help_tip_flag(VOID);
extern VOID menu_set_help_tip_flag(BOOL b_show);

extern VOID menu_help_tip_key_clrreg(VOID);
extern INT32 menu_help_tip_key_reg(HELP_TIP_CB_PAGE e_page, T_HELP_TIP_REG *t_reg);
extern INT32 menu_help_tip_key_unreg(HELP_TIP_CB_PAGE e_page);

extern BOOL menu_help_tip_get_focus(VOID);
extern UINT32 menu_nav_get_pre_page_id_from_nav_stack(VOID);

#ifdef APP_TTS_SUPPORT
extern UTF16_T* menu_help_tip_tts_play_record(UINT16 ui2_lang, UINT16 ui2_key);
extern INT32 menu_help_tip_stop_tts_play(VOID);
extern VOID  a_menu_tts_play_id_record(INT32 id);
extern INT32 a_menu_tts_stop(VOID);
#endif

extern BOOL menu_get_nav_go(VOID);
extern VOID menu_set_nav_go(BOOL b_value);
extern INT32 menu_scrl_title_timer_stop(VOID);

#endif /* _MENU_PAGE_H_ */
