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
 * $RCSfile: menu_util2.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/14 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: aea1eb83e1965ae12a196e8d60ad5cd0 $
 *
 * Description:
 *      This file contains the declarations of GUI-realted typedefs, macros, data,
 * and functions of the MENU application
 *---------------------------------------------------------------------------*/
#ifndef _MENU_UTIL2_H_
#define _MENU_UTIL2_H_

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_gl.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef enum
{
    MENU_RANGE_STYLE_BAR,
    MENU_RANGE_STYLE_POINT
}   MENU_RANGE_STYLE_T;

typedef struct _MENU_SCAN_PB_ITEM_T
{
    HANDLE_T    h_frm;
    HANDLE_T    h_bar;
} MENU_SCAN_PB_ITEM_T;

/*-----------------------------------------------------------------------------
                            data declaration
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
INT32 menu_help_tip_last_shadow_create(
	HANDLE_T	h_parent,
	INT32		i4_index,
	wgl_widget_proc_fct pf_wdgt_proc,
	HANDLE_T*	ph_widget);

INT32 menu_list_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    UINT16      ui2_max_elem_num,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
);

INT32 menu_audio_eq_list_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    UINT16      ui2_max_elem_num,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
);

INT32 menu_list_chg_lang(
    HANDLE_T    h_widget,
    UINT16      ui2_msgid_title,
    UINT16      ui2_msgid_elem_first,
    UINT16      ui2_msgid_elem_last
);

INT32 menu_list_get_idx(
    HANDLE_T    h_widget,
    UINT16*     pui2_idx
);

INT32 menu_list_set_idx(
    HANDLE_T    h_widget,
    UINT16      ui2_idx
);

INT32 menu_list_set_title_text(
    HANDLE_T    h_widget,
    UTF16_T*    w2s_str
);

INT32 menu_list_set_text(
    HANDLE_T    h_widget,
    UINT16      ui2_idx,
    UTF16_T*    w2s_str
);

INT32 menu_action_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
);

INT32 menu_more_item_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget);

INT32 menu_action_chg_lang(
    HANDLE_T    h_widget,
    UINT16      ui2_msgid_title,
    UINT16      ui2_msgid_action
);

INT32 menu_range_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    INT32       i4_min,
    INT32       i4_max,
    MENU_RANGE_STYLE_T  e_style,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
);

INT32 menu_range_get_val(
    HANDLE_T    h_widget,
    INT32*      pi4_val
);

INT32 menu_range_set_val(
    HANDLE_T    h_widget,
    INT32       i4_val
);

INT32 menu_range_chg_lang(
    HANDLE_T    h_widget,
    UINT16      ui2_msgid_title
);

INT32 menu_edit_create(
    HANDLE_T    h_parent,
    INT32       i4_idx,
    BOOL        b_pwd_style,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
);

INT32 menu_edit_chg_lang(
    HANDLE_T    h_widget,
    UINT16      ui2_msgid_title
);

INT32 menu_list2_create(
    HANDLE_T                h_parent,
    const GL_RECT_T*        pt_rect,
    wgl_widget_proc_fct     pf_wdgt_proc,
    const WGL_LB_INIT_T*    pt_lb_init,
    VOID*                   pv_tag,
    HANDLE_T*               ph_lb
);

INT32 menu_text_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
);

INT32 menu_text_chg_lang(
    HANDLE_T    h_widget,
    UINT16      ui2_msgid_title
);

INT32 menu_text_set_text(
    HANDLE_T    h_widget,
    UTF16_T*    w2s_str
);

INT32 menu_list_create_ex(
    HANDLE_T    h_parent,
    INT32       i4_index,
    UINT16      ui2_max_elem_num,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget);

INT32 menu_list_adjust_rect(HANDLE_T h_widget);

INT32 menu_edit_create_ex(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
);

INT32 menu_scan_pb_create(
                         HANDLE_T	h_parent,
                         INT32		i4_index,
                         wgl_widget_proc_fct pf_wdgt_proc,
                         MENU_SCAN_PB_ITEM_T*	pt_scan_pb );

INT32 menu_scan_pb_set_satus(HANDLE_T h_widget,BOOL b_is_enable );

INT32 menu_util_create_txt(
    HANDLE_T                    h_parent,
    UINT32                      ui4_style,
    const GL_RECT_T*            pt_rect,
    UINT8                       ui1_align,
    HANDLE_T*                   ph_txt);

INT32 menu_util_itoa(UTF16_T* w2s_dst,
                   INT32 i4_src,
                   UINT32 ui4_dst_len);

VOID menu_util_ch_num_to_str(UINT16      ui2_major,
                          UINT16      ui2_minor,
                          BOOL        b_one_part_ch,
                          UTF16_T*    w2s_str,
                          UINT32      ui4_dst_len);

INT32 menu_list_arrow_state_update(HANDLE_T h_list, UINT32 ui4_keycode, BOOL b_repaint);
INT32 menu_list_arrow_create(HANDLE_T h_parent, GL_RECT_T *pt_rect);
INT32 menu_list_arrow_hide(BOOL b_repaint);
INT32 menu_list_arrow_move(GL_RECT_T *pt_list_rect, BOOL b_repaint);

VOID menu_toast_range_create(VOID);
VOID menu_toast_range_show(HANDLE_T h_widget,INT32 i4_min_val,INT32 i4_max_val,INT32 i4_val,UINT16 ui2_msgid);

VOID menu_toast_range_hide(VOID);
#endif  /* _MENU_UTIL2_H_ */
extern VOID menu_set_toast_range_flag(BOOL b_toast_range_flag);
extern BOOL menu_get_toast_range_flag(VOID);
extern INT32 menu_list_up_arrow_show(BOOL b_show, BOOL b_repaint);
extern INT32 menu_list_down_arrow_show(BOOL b_show, BOOL b_repaint);



