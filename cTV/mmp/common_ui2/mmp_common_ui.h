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
 * $RCSfile: mmp_common_ui.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description: 
 *         This header file contains public interfaces, constant and type 
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/
 
#ifndef _MMP_COMMON_UI_H_
#define _MMP_COMMON_UI_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_gl.h"
#include "c_wgl.h"
#include "c_os.h"

#include "mmp/mmp_common.h"
#include "mmp/mmp_intf_file_player.h"
#include "res/mmp/common_ui/mmp_common_ui_rc.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

 /*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/
/*tool bar*/
typedef struct _MMP_COM_UI_TOOLBAR_PARAM_T
{
    GL_RECT_T             t_rect_vol_bar;
    GL_RECT_T             at_rect_icon[MMP_COM_UI_RC_TOOLBAR_MAX_ICON];
    WGL_HIMG_TPL_T        ah_img[MMP_COM_UI_RC_TOOLBAR_MAX_ICON];
    GL_RECT_T             at_rect_hint[MMP_COM_UI_RC_TOOLBAR_MAX_TXT];
    UTF16_T*              aws_hint[MMP_COM_UI_RC_TOOLBAR_MAX_TXT];
    UINT8                 ui1_icon_num;
    UINT8                 ui1_hint_num;
} MMP_COM_UI_TOOLBAR_PARAM_T;

typedef struct _MMP_COM_UI_TOOLBAR_T
{
    HANDLE_T                    h_bar;
    HANDLE_T                    h_vol_bar;
    HANDLE_T                    ah_icon[MMP_COM_UI_RC_TOOLBAR_MAX_ICON];
    HANDLE_T                    ah_hint[MMP_COM_UI_RC_TOOLBAR_MAX_TXT];
} MMP_COM_UI_TOOLBAR_T;

/*status bar*/
typedef struct _MMP_COM_UI_STATUSBAR_PARAM_T
{
    GL_RECT_T             t_rect_pb;
    GL_RECT_T             at_rect_icon[MMP_COM_UI_RC_STATUSBAR_MAX_ICON];
    WGL_HIMG_TPL_T        ah_img[MMP_COM_UI_RC_STATUSBAR_MAX_ICON];
    GL_RECT_T             at_rect_label[MMP_COM_UI_RC_STATUSBAR_MAX_TXT];
    UTF16_T*              aw2s_label[MMP_COM_UI_RC_STATUSBAR_MAX_TXT];
    UINT8                 ui1_icon_num;
    UINT8                 ui1_label_num;
} MMP_COM_UI_STATUSBAR_PARAM_T;

typedef struct _MMP_COM_UI_STATUSBAR_T
{
    HANDLE_T                     h_bar;
    HANDLE_T                     h_pb_playback;
    HANDLE_T                     ah_icon[MMP_COM_UI_RC_STATUSBAR_MAX_ICON];
    HANDLE_T                     ah_label[MMP_COM_UI_RC_STATUSBAR_MAX_TXT];
} MMP_COM_UI_STATUSBAR_T;


/*detail page*/
typedef struct _MMP_COM_UI_DETAIL_ELEM_PARAM_T
{
    GL_RECT_T                   t_rect;
    UTF16_T*                    ws_desc;
} MMP_COM_UI_DETAIL_ELEM_PARAM_T;

/*list box*/
typedef struct _MMP_COM_UI_LISTBOX_REF_POINT_T
{
    GL_POINT_T                  t_origin;
    BOOL                        b_is_left_bottom;   /*TRUE: t_origin is left-bottom. FALSE: t_origin is left-top.*/
} MMP_COM_UI_LISTBOX_REF_POINT_T;

typedef struct _MMP_COM_UI_LISTBOX_PARAM_T
{
    UINT32                          ui4_max_elem_count;
    UINT32                          ui4_elem_count;
    UTF16_T**                       aw2_elem_desc;
    MMP_COM_UI_LISTBOX_REF_POINT_T  t_ref_pnt;
} MMP_COM_UI_LISTBOX_PARAM_T;

typedef struct _MMP_COM_UI_LISTBOX_T
{
    HANDLE_T                    h_box;
} MMP_COM_UI_LISTBOX_T;

typedef enum _MMP_COM_UI_MSG_BOX_OP_ITEM_T
{
    MMP_COM_UI_MSG_BOX_ITEM0,
    MMP_COM_UI_MSG_BOX_ITEM1
}MMP_COM_UI_MSG_BOX_OP_ITEM_T;

typedef VOID (*com_ui_msg_box_user_sel_nfy) (MMP_COM_UI_MSG_BOX_OP_ITEM_T e_sel_item, VOID* pv_tag);

typedef struct _MMP_COM_UI_MSG_BOX_2_OP_PARAM_T
{
    UTF16_T*                        pw2s_title;
    UTF16_T*                        pw2s_promt_text;
    UTF16_T*                        pw2s_item0_caption;
    UTF16_T*                        pw2s_item1_caption;
    com_ui_msg_box_user_sel_nfy     pf_user_sel_proc_fct;
}MMP_COM_UI_MSG_BOX_2_OP_PARAM_T;


 /*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
extern INT32 mmp_com_ui_create_toolbar(
        HANDLE_T                            h_parent,
        const MMP_COM_UI_TOOLBAR_PARAM_T*   pt_param,
        MMP_COM_UI_TOOLBAR_T*               pt_toolbar);
        
extern INT32 mmp_com_ui_create_statusbar(
        HANDLE_T                            h_parent,
        const MMP_COM_UI_STATUSBAR_PARAM_T* pt_param,
        MMP_COM_UI_STATUSBAR_T*             pt_statusbar);

#ifndef MMP_GUI_AUTHORING_DP
extern INT32 mmp_com_ui_create_detail_page(
    HANDLE_T                                h_parent,
    UINT32                                  ui4_elem_count,
    GL_RECT_T*                              pt_rect,
    UINT32                                  ui4_text_style,
    BOOL                                    b_custom_rect,
    const MMP_COM_UI_DETAIL_ELEM_PARAM_T*   at_elem_param,
    HANDLE_T*                               ah_elem,
    HANDLE_T*                               ph_detail_page);
#endif

extern INT32 mmp_com_ui_create_pg_bar(
        HANDLE_T                            h_parent,
        GL_RECT_T*                          pt_rect,
        HANDLE_T*                           ph_pg_bar);

extern INT32 mmp_com_ui_create_nfybox(
        HANDLE_T                            h_parent,
        HANDLE_T*                           ph_nfybox);

extern INT32 mmp_com_ui_create_txt_widget(
    HANDLE_T                    h_parent,
    UINT32                      ui4_style,
    UTF16_T*                    ws_text,
    const GL_RECT_T*            pt_rect,
    const GL_COLOR_T*           pt_clr_fg,
    const WGL_FONT_INFO_T*      pt_font,
    HANDLE_T*                   ph_txt);

extern INT32 mmp_com_ui_create_icon_widget(
    HANDLE_T                    h_parent,
    UINT32                      ui4_style,
    const GL_RECT_T*            pt_rect,
    WGL_HIMG_TPL_T              t_img_tpl,
    HANDLE_T*                   ph_icon);

extern INT32 mmp_com_ui_load_icon(HANDLE_T  h_icon,
                          WGL_HIMG_TPL_T t_img_tpl,
                          BOOL b_repaint);

extern INT32 mmp_com_ui_set_text(HANDLE_T      h_txt,
                        UTF16_T*      w2s_text,
                        BOOL          b_repaint);
extern INT32 mmp_com_ui_create_player_frm (HANDLE_T    h_canvas,
                                  wgl_widget_proc_fct pf_wdgt_proc,
                                  UINT8    ui1_alpha,
                                  HANDLE_T*   ph_frm);

extern INT32 mmp_com_ui_msg_box_2_option(HANDLE_T h_parent,
                                         MMP_COM_UI_MSG_BOX_2_OP_PARAM_T *pt_param,
                                         VOID* pv_tag);
/*-----------------------------------------------------------------------------
                    running box
 ----------------------------------------------------------------------------*/
/*running box*/
typedef struct _MMP_COM_UI_RUNNING_BOX_PARAM_T
{
    GL_POINT_T                  t_offset;
} MMP_COM_UI_RUNNING_BOX_PARAM_T;

typedef struct _MMP_COM_UI_RUNNING_BOX_T
{
    HANDLE_T                    h_icon;
    HANDLE_T                    h_timer;
    UINT8                       ui1_scene_idx;
    BOOL                        b_running;
} MMP_COM_UI_RUNNING_BOX_T;

extern INT32 mmp_com_ui_create_running_box(
        HANDLE_T                                h_parent,
        const MMP_COM_UI_RUNNING_BOX_PARAM_T*   pt_param,
        MMP_COM_UI_RUNNING_BOX_T*               pt_running_box);

extern INT32 mmp_com_ui_free_running_box(
        MMP_COM_UI_RUNNING_BOX_T*               pt_running_box);

extern INT32 mmp_com_ui_start_running_box(
        MMP_COM_UI_RUNNING_BOX_T*               pt_running_box);

extern INT32 mmp_com_ui_stop_running_box(
        MMP_COM_UI_RUNNING_BOX_T*               pt_running_box);

extern INT32 mmp_com_ui_info_ui_create(HANDLE_T             h_parent,
                              GL_RECT_T*                    pt_rect,
                              MMP_FP_INFO_HDLR_UI_TYPE_T    e_ui_type,
                              UINT8                         ui1_itm_num,
                              HANDLE_T*                     ph_page,
                              HANDLE_T*                     ah_title,
                              HANDLE_T*                     ah_value);

extern INT32 mmp_com_ui_info_ui_destroy(HANDLE_T            h_page);

extern INT32 mmp_com_ui_get_date_time(
                               BOOL                         b_is_dtg_fmt,
                               CHAR*                        ws_info,
                               DTG_T*                       pt_dtg,
                               UTF16_T*                     ws_d_and_t,
                               UTF16_T*                     ws_date,
                               UTF16_T*                     ws_time,
                               UINT16                       ui2_lang_id);

INT32 mmp_com_ui_info_ui_icon_create(HANDLE_T                      h_parent,
                                     UINT8                         ui1_icon_w,
                                     UINT8                         ui1_icon_h,
                                     UINT8                         ui1_index,
                                     HANDLE_T*                     ph_icon);

#endif /*_MMP_COMMON_UI_H_*/
