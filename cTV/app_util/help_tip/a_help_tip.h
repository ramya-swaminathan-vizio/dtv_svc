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
 * $RCSfile: a_help_tip.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/19 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 7ed3c11a9ed90eba15305b24039bcab7 $
 *
 * Description:
 *      This file contains the implementation of channel lists.
 *---------------------------------------------------------------------------*/
#ifndef __A_HELP_TIP_H__
#define __A_HELP_TIP_H__

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct _HELP_TIP_INIT_T
{
    HANDLE_T            h_parent;
    GL_RECT_T           t_frame_rect;
    CHAR*               font_name;
    x_os_timer_cb_fct   pf_timeout_notify;
}HELP_TIP_INIT_T;

#define  HELP_TIPR_OK            (0)
#define  HELP_TIPR_FAIL          (-1)
#define  HELP_TIPR_OUT_OF_MEM    (-2)

#define  HELP_TIP_LAST_TXT_LEN   (512)

/* Return on error */
#define HELP_TIP_CHK_FAIL(_ret)  \
do{ \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("<HELP_TIP> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret)); \
    return HELP_TIPR_FAIL;  \
}   \
}while(FALSE)

#define HELP_TIP_LOG_ON_FAIL(_ret)  \
do{ \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("<HELP_TIP> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret)); \
}   \
}while(FALSE)

#define HELP_TIP_BREAK_ON_FAIL(_ret)  \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("<HELP_TIP> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret)); \
    break;  \
}

/*-----------------------------------------------------------------------------
                    public function declarations
 ----------------------------------------------------------------------------*/

extern INT32 a_help_tip_init (
    HELP_TIP_INIT_T*        pt_help_tip_init,   /* Input  */
    HANDLE_T*               ph_help_tip         /* Output */
    );

extern INT32 a_help_tip_deinit (
    HANDLE_T                h_help_tip
    );

extern INT32 a_help_tip_set_info (
    HANDLE_T                h_help_tip,
    UTF16_T*                w2s_text
    );

extern INT32 a_help_tip_show (
    HANDLE_T                h_help_tip
    );

extern INT32 a_help_tip_trigger (
    HANDLE_T                h_help_tip
    );

extern INT32 a_help_tip_hide (
    HANDLE_T                h_help_tip
    );
extern INT32 a_help_tip_move (
    HANDLE_T                h_help_tip ,
    GL_RECT_T*             pt_rect,
    BOOL                       b_repaint
    );

extern INT32 a_help_tip_show_help(
    HANDLE_T            h_help_tip
    );

extern INT32 a_help_tip_hide_help(
    HANDLE_T            h_help_tip
    );

extern INT32 a_help_tip_set_focus(HANDLE_T h_help_tip,
                                  HANDLE_T h_focus,
                                  UINT16 ui2_idx,
                                  BOOL b_repaint);

extern INT32 a_help_tip_set_proc(HANDLE_T h_help_tip,
                       wgl_widget_proc_fct pf_proc_1,
                       wgl_widget_proc_fct pf_proc_2);

extern INT32 a_help_tip_keytip_show(HANDLE_T h_help_tip, BOOL b_show);

extern INT32 a_help_tip_change_lang(HANDLE_T    h_help_tip,
                             UTF16_T*    w2s_last,
                             UTF16_T*    w2s_exit);

extern INT32 a_help_tip_visible(HANDLE_T h_help_tip);

#ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT
extern INT32 a_menu_set_help_tip_enable_status(HANDLE_T h_help_tip, BOOL b_status);
#endif
extern HANDLE_T a_help_tip_get_focus_last(VOID);

extern UINT8 a_help_tip_get_focus_icon_idx(HANDLE_T h_help_tip);

extern VOID a_help_tip_set_last_txt(const UTF16_T * w2s_src);

extern UTF16_T * a_help_tip_get_last_txt(VOID);

extern BOOL a_help_tip_get_focus(HANDLE_T h_help_tip);

#endif /* __A_HELP_TIP_H__ */

