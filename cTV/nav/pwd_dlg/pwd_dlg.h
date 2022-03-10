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
 * $RCSfile: pwd_dlg.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
#ifndef _PWD_DLG_H_
#define _PWD_DLG_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "nav/nav_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#ifdef NAVR_CHK_FAIL
#undef NAVR_CHK_FAIL
#endif

#define NAVR_CHK_FAIL(_ret)     \
do{                             \
    INT32 ret = _ret;           \
    if (ret < 0)               \
    {                           \
        DBG_ERROR(("<NAV> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret));   \
        return NAVR_FAIL;       \
    }                           \
}while(FALSE)

typedef struct _PWD_DLG_T
{
    HANDLE_T                  h_hide_timer;
    HANDLE_T                  h_chk_timer;
    BOOL                      b_force_stop_prompt;
    TV_WIN_ID_T               e_focus_tv_win_id;
    BOOL                      b_delay_chk_auto_active;

    BOOL                      b_pwd_osd_on;
    BOOL                      b_pwd_box_on;
    BOOL                      b_delay_return_activation;
    HANDLE_T                  h_pwd_frame;
    HANDLE_T                  h_pwd_title;
    HANDLE_T                  h_pwd_alarm;
    HANDLE_T                  h_pwd_box;
    UINT16                    ui2_acfg_nfy_id;
} PWD_DLG_T;

typedef enum{

  BUTTON_1 = 0,
  BUTTON_2,
  BUTTON_3,
  BUTTON_4,
  BUTTON_LAST_ENTRY
} PWD_DLG_BUTTON_T;

typedef struct _PWD_DLG_VIEW_T
{
   HANDLE_T h_parent_frm;
   HANDLE_T h_pwd_title;
   HANDLE_T h_image_no_match;
   HANDLE_T h_pwd_button[BUTTON_LAST_ENTRY];
   HANDLE_T h_txt_alarm;
   HANDLE_T h_title_txt;
   HANDLE_T h_pwd_icon;
   HANDLE_T h_cancel_icon;
   HANDLE_T h_help_tips;
   HANDLE_T h_hide_timer;

   BOOL     b_is_pin_box;
} PWD_DLG_VIEW_T;

#define PASSWORD_LENGTH                          (4)
#define PASSWORD_BOX_LENGTH                      (PASSWORD_LENGTH+1)
#define PWD_BOX_WAIT_REPAINT_TIMEOUT             (300)
#define PWD_BOX_DISCART_KEY_TIMEOUT              (500)
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 pwd_dlg_view_init(
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    );
extern INT32 pwd_dlg_view_deinit(
                    VOID
                    );
extern VOID pwd_dlg_view_load_msgs(
                    UINT8                       ui1_lang_id
                    );
extern INT32 pwd_dlg_view_hide_all(
                    VOID
                    );
extern INT32 pwd_dlg_view_show_box(
                    VOID
                    );
extern BOOL pwd_dlg_box_chk_pwd(
                    UTF16_T*                    w2s_pwd
                    );
extern VOID pwd_dlg_reset_timer(
                    VOID
                    );
extern VOID pwd_dlg_box_msg_nty_fct(
                    PWD_DLG_T*                  pt_this,
                    HANDLE_T                    h_source,
                    WGL_NOTIFY_DATA_T*          pt_nfy_data
                    );
extern VOID pwd_dlg_alarm_msg_nty_fct(
                    PWD_DLG_T*                  pt_this,
                    HANDLE_T                    h_source,
                    WGL_NOTIFY_DATA_T*          pt_nfy_data
                    );
extern BOOL pwd_dlg_get_delay_return_activation_status(VOID);

extern INT32 pwd_dlg_view_show_lock_msg_box(
                    VOID
                    );

extern BOOL pwd_dlg_view_is_show_box(VOID);

extern VOID pwd_dlg_stop_timer(VOID);
extern BOOL nav_get_pwd_dlg_view_cannel_status(VOID);
extern INT32 nav_update_pwd_digit_ui(VOID);


extern BOOL a_pwd_dlg_check_osd_on(void);
extern BOOL a_pwd_dlg_check_box_on(void);
extern void a_pwd_dlg_restore_rating_setting(void);

#endif /* _PWD_DLG_H_ */

