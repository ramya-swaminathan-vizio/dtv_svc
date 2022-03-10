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
 * $RCSfile: a_wdk_wgl_util.h,v $
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
#ifndef _WDK_WGL_WIDGET_H_
#define _WDK_WGL_WIDGET_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_wgl_sets.h"
#include "u_wgl_hts.h"
#include "u_wgl_bdr_common.h"
#include "u_iom.h"
#include "u_time_msrt.h"
#include "u_wgl_animation.h"
#include "u_wgl.h"
#include "res/nav/nav_mlm.h"
#include "nav/nav_common.h"
#include "nav/nav_comp_id.h"
#include "c_fe.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

typedef struct _WDK_WIDGETS_T
{
    UINT32                      ui4_width;
    UINT32                      ui4_height;

    WGL_HIMG_TPL_T              t_img_frm_back; /* for base frame*/
    WGL_HIMG_TPL_T              t_img_toast_box_icon;
    WGL_HIMG_TPL_T              t_img_dialog_back;
    WGL_HIMG_TPL_T              t_img_dialog_frm_back;
    WGL_HIMG_TPL_T              t_img_title_line;

    BOOL                        b_is_show;
}WDK_WIDGETS_T;

typedef enum
{
    WDK_MSG_SPLICING = 0,
    WDK_MSG_SEPARATELY
} WDK_WIDGET_MSG_TYPE_T;

typedef struct _WDK_WIDGET_MSG_T
{
    WDK_WIDGET_MSG_TYPE_T       e_msy_style;
    VOID*                       w2s_str[128];
    UINT32                      i4_str_num;
}WDK_WIDGET_MSG_T;

typedef enum
{
    WDK_TOAST_VOL_TRACK_CENTER = 0,
    WDK_TOAST_VOL_TRACK_HALF
}   WDK_TOAST_VOL_TRACK_T;

typedef enum
{
    WDK_TOAST_SETTINGS_SLIDER = 0,
    WDK_STRING_TOAST,
    WDK_WARNING_TOAST,
    WDK_SINGLE_SELECT_LIST,
    WDK_INPUT_LIST,
    WDK_NO_SINGLE,
    WDK_CENTER_DIALOG,
    WDK_PIC_PW_POPUP,
    WDK_SCREEN_CENTER_MSG,
    WDK_TOAST_MAX_NUM
}   WDK_TOAST_STYLE_T;

typedef enum
{
    WDK_STRING_TRACK = 1,
    WDK_STRING_ID_ID,
    WDK_STRING_ID_VALUE,
    WDK_STRING_STRING,
    WDK_STRING_TITLE_CONTENT
}   WDK_STRING_STYLE_T;

typedef struct {
    HANDLE_T  h_pic_left_button;
    HANDLE_T  h_pic_middle_button;
    HANDLE_T  h_pic_right_button;
    HANDLE_T  h_pw_left_button;
    HANDLE_T  h_pw_right_button;
} WDK_PPP_BUTTON_T;

typedef struct _WDK_OSD_TOAST_T
{
    HANDLE_T                    h_canvas;
    HANDLE_T                    h_base_frm;
    HANDLE_T                    h_dialog_frm;
    HANDLE_T                    h_icon_toast_box;
    HANDLE_T                    h_txt_toast_box;
    HANDLE_T                    h_txt_help_toast_box;
    HANDLE_T                    h_title_line;
    HANDLE_T                    h_eq_hash_mark;
    HANDLE_T                    h_warning_icon;
    HANDLE_T                    h_track_cap_left;
    HANDLE_T                    h_track_cap_right;
    HANDLE_T                    h_eq_msg;
    HANDLE_T                    h_line_timer;
    HANDLE_T                    h_list_txt_frm;
    HANDLE_T                    h_list_txt_focus;
    HANDLE_T                    h_bk_timer;
    HANDLE_T                    h_focus_handle;     /*store the previous focus handle */
    HANDLE_T                    h_energy_star_icon;
	HANDLE_T					h_dolby_vision_icon;
    HANDLE_T                    *h_list_txt;
    BOOL                        b_have_init;

    BOOL                        b_is_pic_mode;
    UINT8                       ui1_pic_standard_idx;
    VOID*                       pt_wdk_param;
    WDK_TOAST_STYLE_T           e_style;
}WDK_OSD_TOAST_T;


typedef struct _WDK_TOAST_PARAM_T
{
    WDK_TOAST_VOL_TRACK_T       e_track_style;
    VOID*                       w2s_str;                /*TITLE TEXT*/
    VOID*                       w2s_help_str;           /*HELP TEXT*/
    WDK_TOAST_STYLE_T           e_toast_style;
    WDK_WIDGET_MSG_T            w2s_msg_t;              /*COMPENT TEXT*/
    wgl_widget_proc_fct         pf_cb;

    /*SLIDER PARAM*/
    INT32                       i4_vol_track_val;
    INT32                       i4_vol_track_range;

    /*SELECT LIST */
    wgl_widget_proc_fct         pf_send_msg_cb;
    UINT32                      ui4_sl_first_num ;
    UINT32                      ui4_sl_focus_num ;      /*SAVE SELECT LIST TEXT ITEM NUM */
    HANDLE_T                    h_t_focus_handle;

    /*for pic mode*/
    BOOL                        b_is_pic_mode;
    UINT8                       ui1_pic_standard_idx;

    union
    {
        struct
        {
            WDK_PPP_BUTTON_T*   pt_wdk_ppp_button;
            INT32               i4_frame_x_offset;
            INT32               i4_frame_y_offset;
            UINT8               ui1_crnt_page;
            UINT8               ui1_lang_idx;
        } style_ppp;
    } style;
}WDK_TOAST_PARAM_T;

typedef enum {
    TOAST_EVENT_HIDE = 0,
    TOAST_EVENT_KEY
} WDK_TOAST_CB_EVENT;

typedef enum {
    TOAST_REASON_HIDE_TIMEOUT = 0,
    TOAST_REASON_HIDE_INTERRUPTED,
    TOAST_REASON_KEY_DOWN
} WDK_TOAST_CB_REASON;

typedef VOID (*wdk_toast_cb_fct)(WDK_TOAST_CB_EVENT cb_event,
                                     WDK_TOAST_CB_REASON cb_reason,
                                     VOID* pv_data);


typedef struct _WDK_TOAST_T
{
    WDK_TOAST_STYLE_T  e_toast_style;
    WDK_STRING_STYLE_T e_string_style;
    wdk_toast_cb_fct   pf_cb;

    union
    {
        struct
        {
            // e_string_style == WDK_STRING_TRACK
            WDK_TOAST_VOL_TRACK_T       e_track_style;
            UINT32                      ui4_id;
            INT32                       i4_value;
            INT32                       i4_max_val;
        } style_1;

        struct
        {
            // e_string_style == WDK_STRING_ID_ID
            UINT32                      ui4_id_1;
            UINT32                      ui4_id_2;
        } style_2;

        struct
        {
            // e_string_style == WDK_STRING_ID_VALUE
            UINT32                      ui4_id;
            INT32                       i4_value;
        } style_3;

        struct
        {
            // e_string_style == WDK_STRING_STRING
            UINT32                      ui4_id;
            VOID*                       w2s_str;
        } style_4;

        struct
        {
            // e_string_style == WDK_STRING_TITLE_CONTENT
            VOID*                       w2s_title_str;
            VOID*                       w2s_content_str;
        } style_5;

    }style;

}WDK_TOAST_T;


typedef struct _WDK_WIDGET_SEND_MSG_T
{
    UINT32               ui4_keycode;
    UINT32               ui4_selected_num ;
}WDK_WIDGET_SEND_MSG_T;

typedef struct _WDK_WIDGET_COMMON_RES_T
{
    HFONT_T        h_font_handle;
    BOOL           b_is_init;
    HFONT_T        h_zoom_font_handle;
}WDK_WIDGET_COMMON_RES_T;



/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32 a_wdk_toast_init (
    HANDLE_T                    h_canvas,
    VOID*                       pv_param1,
    WDK_OSD_TOAST_T*            t_g_wdk_handle);

extern INT32 a_wdk_toast_activate(
    BOOL                        b_repaint,
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            t_g_wdk_handle);

extern void wdk_set_help_toast_visible(
        BOOL                        b_enalbe,
        WDK_OSD_TOAST_T*            pt_this);

extern INT32 a_wdk_toast_hide(
    BOOL                        b_repaint,
    VOID*                       pv_data,
    WDK_OSD_TOAST_T*            t_g_wdk_handle);

extern INT32 a_wdk_toast_deinit(WDK_OSD_TOAST_T*            t_g_wdk_handle);

extern INT32 wdk_widget_select_list_proc_fct(
                                     HANDLE_T    h_widget,
                                     UINT32      ui4_msg,
                                     VOID*       param1,
                                     VOID*       param2);

extern INT32 a_wdk_toast_list_adjust(HANDLE_T  *ph_list_txt,
                                         UINT32     i4_item_num
                                      );

extern INT32 a_wdk_toast_adjust_list_focus_line(UINT8 ui1_inp_before/*HANDLE_T  h_list_item*/,
                                            HANDLE_T  h_list_item_focus_line,
                                            HANDLE_T  *ph_list_txt,
                                            UINT32     i4_item_num
                                            );
extern BOOL a_wdk_toast_visible();
#endif /* _WDK_WGL_UTIL_H_ */

