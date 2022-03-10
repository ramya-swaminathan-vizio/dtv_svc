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
 * $RCSfile: clock.h,v $
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
#ifndef _NAV_DIALOG_H_
#define _NAV_DIALOG_H_

#include "c_wgl.h"
#include "app_util/a_ui.h"
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef enum
{
    NAV_DIALOG_ID_NULL = 0,
    NAV_DIALOG_ID_USB_PLG_DLG,
    NAV_DIALOG_ID_USB_UPLG_DLG,
    NAV_DIALOG_ID_AMP_PLG_DLG,
    NAV_DIALOG_ID_CUSTOM_1,
    NAV_DIALOG_ID_CUSTOM_2,
    NAV_DIALOG_ID_CUSTOM_3,
    NAV_DIALOG_ID_CUSTOM_4,
    NAV_DIALOG_ID_OLED_SCREEN_REFRESH_DLG,
    NAV_DIALOG_ID_AUTO_PC_GLL,

}   NAV_DIALOG_ID_T;

#define NAV_DIALOG_ONLY_MSG_FRM_X               (420)
#define NAV_DIALOG_ONLY_MSG_FRM_Y               (308)
#define NAV_DIALOG_ONLY_MSG_FRM_W               (440)
#define NAV_DIALOG_ONLY_MSG_FRM_H               (104)

typedef struct _NAV_DIALOG_INIT_T
{
    NAV_DIALOG_ID_T                    e_id;
    wgl_widget_proc_fct                pf_wdgt_proc;
    UI_SIMPLE_DIALOG_STYLE_T           e_style;
    UINT32                             ui4_timeout;
    UINT16                             ui2_txt_align_type;
    GL_POINT_T*                        pt_begin_offset;    /* For Small/Medium/Big style only */
    BOOL                               b_default_answer;   /* For Small/Medium/Big style only */
    BOOL                               b_one_btn_mode;     /**< Determine whether there is only one button if e_style != UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY! */
    BOOL                               b_three_btn_mode;     /**< Determine whether there is three button if e_style != UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY! */
    ui_simple_dialog_yes_cb_fct        pf_ui_simple_dialog_yes_cb_fct; /* For Small/Medium/Big style only */
    ui_simple_dialog_no_cb_fct         pf_ui_simple_dialog_no_cb_fct;  /* For Small/Medium/Big style only */
    ui_simple_dialog_info_cb_fct       pf_ui_simple_dialog_info_cb_fct;  /* For Small/Medium/Big style only */
    ui_simple_dialog_other_key_cb_fct  pf_ui_simple_dialog_other_key_cb_fct;  /* For other key process */
    ui_simple_dialog_tts_cb_fct        pf_ui_simple_dialog_tts_cb_fct;
    UTF16_T*                           p_msg_txt;
    UTF16_T*                           p_yes_txt;
    UTF16_T*                           p_no_txt;
    UTF16_T*                           p_info_txt;
} NAV_DIALOG_INIT_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

/* Prompt a dialog */
extern INT32 nav_dialog_prompt_yes_no_dialog(
    NAV_DIALOG_ID_T              e_dialog_id,
    UTF16_T*                     pw2s_msg,
    UTF16_T*                     pw2s_yes,
    UTF16_T*                     pw2s_no,
    wgl_widget_proc_fct          pf_wdgt_proc,
    ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct,
    ui_simple_dialog_no_cb_fct   pf_ui_simple_dialog_no_cb_fct
);

extern INT32 nav_dialog_prompt_yes_no_dialog_ex(
    NAV_DIALOG_ID_T              e_dialog_id,
    UTF16_T*                     pw2s_msg,
    UTF16_T*                     pw2s_yes,
    UTF16_T*                     pw2s_no,
    UI_SIMPLE_DIALOG_STYLE_T     e_style,
    UINT16                       ui2_txt_align_type,
    GL_POINT_T*                  pt_begin_offset,
    BOOL                         b_default_answer,
    wgl_widget_proc_fct          pf_wdgt_proc,
    ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct,
    ui_simple_dialog_no_cb_fct   pf_ui_simple_dialog_no_cb_fct,
    ui_simple_dialog_tts_cb_fct  pf_ui_simple_dialog_tts_cb_fct,
    UINT32*                      pui4_timeout
);

extern INT32 nav_dialog_prompt_msg_dialog(
            NAV_DIALOG_ID_T              e_dialog_id,
            UTF16_T*                     pw2s_msg,
            UTF16_T*                     pw2s_yes,
            GL_POINT_T*                  pt_begin_offset,
            wgl_widget_proc_fct          pf_wdgt_proc,
            ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct);

extern INT32 nav_dialog_prompt_msg_dialog_ex(
            NAV_DIALOG_ID_T              e_dialog_id,
            UTF16_T*                     pw2s_msg,
            UTF16_T*                     pw2s_yes,
            GL_RECT_T*                   pt_rect,
            GL_POINT_T*                  pt_begin_offset,
            wgl_widget_proc_fct          pf_wdgt_proc,
            ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct);

#ifdef APP_ARC_ONLY
extern INT32 nav_dialog_prompt_only_msg_dialog(
            NAV_DIALOG_ID_T              e_dialog_id,
            UTF16_T*                     pw2s_msg,
            //UTF16_T*                     pw2s_yes,
            GL_RECT_T*                   pt_rect,
            GL_POINT_T*                  pt_begin_offset,
            wgl_widget_proc_fct          pf_wdgt_proc);
#endif
/* Hide the dialog */
extern INT32 nav_dialog_hide(VOID);

/* Start hide timer */
extern INT32 nav_dialog_set_hide_timer(
    UINT32  ui4_time
);

extern INT32 nav_dialog_stop_hide_timer(VOID);

/* Default procedure */
extern INT32 nav_dialog_default_msg_proc(
    HANDLE_T            h_widget,
    UINT32              ui4_msg,
    VOID*               pv_param1,
    VOID*               pv_param2
);

/* Get current showing dialog id */
extern NAV_DIALOG_ID_T nav_dialog_get_crnt_id(VOID);

#endif /* _NAV_DIALOG_H_ */
