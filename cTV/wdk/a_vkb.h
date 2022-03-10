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
 * $RCSfile: a_vkb.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: GUI composite component -- Time Entry
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_WDK_VKB_H_
#define _A_WDK_VKB_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_handle.h"
#include "u_wgl.h"
#include "u_wgl_common.h"
#include "app_util/a_common.h"

#include "wdk/a_wdk.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define   VKB_MSG_DLG_CANCEL         (1)
#define   VKB_MSG_DLG_FINISHED       (2)
#define   VKB_MSG_DLG_KEY_INPUT      (3)
#define   VKB_MSG_DLG_KEY_EB_CLEAR   (4)

/* The style could be changed run-time */
#define VKB_STYLE_MASK_DEFAULT          MAKE_BIT_MASK_32(0)
#define VKB_STYLE_MASK_WITH_TITLE       MAKE_BIT_MASK_32(1)
#define VKB_STYLE_MASK_PASSWORD         MAKE_BIT_MASK_32(2)

typedef enum _VKB_CMD_TYPE_T
{
    VKB_CMD_SET_MAX_CHAR_NUM = 0,    /* param1: max char # */
    VKB_CMD_SET_STYLE_MASK,          /* param1: UINT32 ui4_style_mask # */
    VKB_CMD_SET_TITLE_TEXT,
    VKB_CMD_SET_INITIAL_TEXT,        /* param1: UTF16_T* w2s_str, param2: num of char # */
    VKB_CMD_SET_LABEL_TEXT,          /* param1: UTF16_T* w2s_str, param2: num of char # */
    VKB_CMD_SET_OK_BTN_TEXT,         /* param1: UTF16_T* w2s_str, param2: num of char # */
    VKB_CMD_SET_CANCEL_BTN_TEXT,     /* param1: UTF16_T* w2s_str, param2: num of char # */
    VKB_CMD_CLEAR_TEXT,              /* clear all text # */
    VKB_CMD_GET_TEXT,                /* param1: UTF16_T* w2s_str, param2: sizeof w2s_str # */
    VKB_CMD_GET_EB_CONTENT,
    VKB_CMD_GET_ATTACH_DATA,
    VKB_CMD_GET_CTRL_BTN_IDX,
    VKB_CMD_GET_NORMAL_BTN_IDX,
    VKB_CMD_GET_LATIN_BTN_IDX,
    VKB_CMD_GET_CUR_LATIN_NUM,
    VKB_CMD_GET_STYLE_MASK
} VKB_CMD_TYPE_T ;


typedef INT32 (*vkb_data_change_nfy_fct)(
        VOID*    pv_tag,
        UINT32   ui4_msg,
        VOID*    pv_param1,
        VOID*    pv_param2
        );

typedef struct _VKB_GUI_RC_T
{
       INT32    i4_left;
       INT32    i4_top;
} VKB_GUI_RC_T;

/* VKB structure */
typedef struct _VKB_INIT_T
{
   HANDLE_T                     h_parent;
   VKB_GUI_RC_T                 t_gui_rc;
   UINT32                       ui4_style_mask;
   vkb_data_change_nfy_fct      pf_data_change_fct;
   VOID*                        pv_tag;
} VKB_INIT_T;

typedef struct _VKB_EB_ATTACH_DATE
{
    HANDLE_T            h_edit_box;         /* Must: EdidBox attached */
    GL_RECT_T           t_rect_eb;          /* Optional:RECT of EdidBox attached */

    BOOL                b_need_eb_clr;      /* Optional:Handle of EdidBox Clear all */
    HANDLE_T            h_eb_clr;           /* Optional: Delete ALL attached */
    GL_RECT_T           t_rect_eb_clr;      /* Optional:RECT of EdidBox attached */

    wgl_widget_proc_fct pf_eb_proc;         /* Optional:Save the old wgl proc of EdidBox attached */
    wgl_widget_proc_fct pf_eb_clr_proc;     /* Optional:Save the old wgl proc of Delete all attached */

}VKB_EB_ATTACH_DATE;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

/* VKB related functions */
extern INT32
a_vkb_create(
        VKB_INIT_T*      pt_init_data, /* IN */
        HANDLE_T*        ph_handle_out /* OUT */
        );

extern INT32
a_vkb_destroy(
        HANDLE_T         h_vkb_handle  /* IN */
        );

extern INT32
a_vkb_do_cmd(
        HANDLE_T                  h_vkb_handle, /* IN */
        VKB_CMD_TYPE_T      e_cmd,        /* IN */
        VOID*                       pv_param1,
        VOID*                       pv_param2
        );

extern INT32
a_vkb_repaint(
        HANDLE_T         h_vkb_handle  /* IN */
        );

extern INT32
a_vkb_set_visibility(
        HANDLE_T         h_vkb_handle  /* IN */,
        BOOL             b_visible     /* IN */
        );

extern INT32
a_vkb_set_focus(
        HANDLE_T         h_vkb_handle  /* IN */
        );

extern INT32
a_vkb_set_focus_ex(
        HANDLE_T         h_vkb_handle  /* IN */
        );

extern INT32 a_vkb_set_focus_sync(
        HANDLE_T                h_vkb_handle  /* IN */
        );

extern INT32
a_vkb_show(
        HANDLE_T         h_vkb_handle  /* IN */
        );

extern INT32
a_vkb_hide(
        HANDLE_T         h_vkb_handle  /* IN */
        );

extern UINT8
a_vkb_current_get_row_index(
        HANDLE_T  h_vkb_handle         /* IN */
        );

extern UINT8
a_vkb_current_get_col_index(
        HANDLE_T  h_vkb_handle         /* IN */
        );
extern INT32
a_vkb_reset_eb_handle(
        HANDLE_T h_vkb_handle
        );

extern INT32
a_vkb_attach_eb(
        HANDLE_T h_vkb_handle,
        VKB_EB_ATTACH_DATE *pt_attach_data
        );

extern INT32
a_vkb_is_eb_attach(
        HANDLE_T h_vkb_handle,
        BOOL *pb_is_eb_attach,
        BOOL *pb_is_eb_clr_attach
        );
extern VOID a_vkb_set_lang(
        CHAR *ps_lang);
extern INT32 a_vkb_set_focus_ctrl_del(HANDLE_T h_vkb_handle, BOOL b_repaint);

extern INT32 a_vkb_enable_ok_btn (HANDLE_T     h_vkb_handle,
                           BOOL         b_enable);

extern INT32 a_vkb_is_latin_stat(HANDLE_T h_vkb_handle, BOOL *pb_latin);

#endif /* _A_WDK_VKB_H_ */

