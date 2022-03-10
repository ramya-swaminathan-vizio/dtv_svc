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
 * $RCSfile: menu_common_simple_dialog.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/23 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: $
 *
 * Description:
 *      This file contains the implementation of GUI-related functions of the
 * menu application
 *---------------------------------------------------------------------------*/
#ifndef _MENU_COMMON_SIMPLE_DIALOG_H_
#define _MENU_COMMON_SIMPLE_DIALOG_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_handle.h"
#include "app_util/a_ui.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef VOID (*menu_simple_dialog_yes_fct)(VOID);
typedef VOID (*menu_simple_dialog_no_fct)(VOID);
typedef VOID (*menu_simple_dialog_exit_fct)(VOID);

typedef struct _MENU_SIMPLE_DIALOG_T
{
    HANDLE_T                     h_simple_dialog;
    HANDLE_T                     h_focus_return;
    menu_simple_dialog_exit_fct  pf_exit_fct;
    BOOL                         b_flow_on_menu;
}MENU_SIMPLE_DIALOG_T;

typedef struct _MENU_SIMPLE_DIALOG_CFG_T
{
    UINT16                         ui2_msg_txt;        /* Messages in the text dialog */
    UINT16                         ui2_msg_yes;        /* Messages in the [YES] button */
    UINT16                         ui2_msg_no;         /* Messages in the [NO] button */
    UINT16                         ui2_text_alignment; /* Dialog Text Alignment */
    BOOL                           b_default_answer;   /* Default Answer */
    menu_simple_dialog_yes_fct     pf_yes;             /* Press Yes to run */
    menu_simple_dialog_no_fct      pf_no;              /* Press No to run */
    HANDLE_T                       h_focus_return;     /* Return focus to the Handle after hide */
    menu_simple_dialog_exit_fct    pf_exit_fct;        /* Press Exit Key to run */
    BOOL                           b_flow_on_menu;     /* False: Hide menu */
}MENU_SIMPLE_DIALOG_CFG_T;

/* Simple Dialog Page */
typedef VOID (*menu_common_page_simple_dialog_yes_fct)(VOID);
typedef VOID (*menu_common_page_simple_dialog_no_fct)(VOID);
typedef VOID (*menu_common_page_simple_dialog_info_fct)(VOID);
typedef INT32 (*menu_common_page_simple_dialog_tts_fct)(UTF16_T*);

typedef struct _MENU_COMMON_SIMPLE_DIALOG_INIT_T{
    UINT16                                   ui2_msg_txt;         /* Messages in the text dialog */
    UINT16                                   ui2_msg_yes;         /* Messages in the [YES] button */
    UINT16                                   ui2_msg_no;          /* Messages in the [NO] button */
    UINT16                                   ui2_msg_info;         /* Messages in the [INFO] button */
    UI_SIMPLE_DIALOG_STYLE_T                 e_style;             /* Dialog Style */
    UINT16                                   ui2_text_alignment;  /* Dialog Text Alignment */
    BOOL                                     b_default_answer;    /* Default Answer */
    UI_SIMPLE_DIALOG_ANSWER                  e_default_answer_ex; /* Default Answer */
    menu_common_page_simple_dialog_yes_fct   pf_yes;              /* Press Yes to run */
    menu_common_page_simple_dialog_no_fct    pf_no;               /* Press No to run */
    menu_common_page_simple_dialog_info_fct  pf_info;             /* Press Info to run */
    BOOL                                     b_info_icon;         /* TRUE: Dialog with icon*/
    BOOL                                     b_three_btn_mode;    /* has three btn*/
    BOOL                                     b_one_btn_mode;      /* One btn mode*/
} MENU_COMMON_SIMPLE_DIALOG_INIT_T;

typedef struct _MENU_COMMON_SIMPLE_DIALOG_T{
    UINT16                                   ui2_msg_txt;         /* Messages in the text dialog */
    UINT16                                   ui2_msg_yes;         /* Messages in the [YES] button */
    UINT16                                   ui2_msg_no;          /* Messages in the [NO] button */
    UINT16                                   ui2_msg_info;        /* Messages in the [NO] button */
    menu_common_page_simple_dialog_yes_fct   pf_yes;              /* Press Yes to run */
    menu_common_page_simple_dialog_no_fct    pf_no;               /* Press No to run */
    menu_common_page_simple_dialog_info_fct  pf_info;             /* Press Info to run */
    menu_common_page_simple_dialog_tts_fct   pf_tts;              /* Press Info to run */
    BOOL                                     b_default_answer;    /* Default Answer */
    BOOL                                     b_three_btn_mode;    /* Has three btn*/
    BOOL                                     b_one_btn_mode;      /* One btn mode*/
    UI_SIMPLE_DIALOG_ANSWER                  e_default_answer_ex; /* Default Answer_ex */
    HANDLE_T                                 h_simple_dialog;     /* The handle of the simple dialog */
} MENU_COMMON_SIMPLE_DIALOG_T;

/*-----------------------------------------------------------------------------
                    function declaraions
 ----------------------------------------------------------------------------*/
extern INT32 menu_simple_dialog_init(VOID);
extern INT32 menu_simple_dialog_destroy(VOID);
extern INT32 menu_simple_dialog_show(MENU_SIMPLE_DIALOG_CFG_T* pt_cfg);
extern INT32 menu_simple_dialog_hide(VOID);
extern BOOL  menu_simple_dialog_is_showed(VOID);
extern INT32 menu_common_page_simple_dialog_create(
    UINT16                                     ui2_msg_txt,        /* Messages in the text dialog */
    UINT16                                     ui2_msg_yes,        /* Messages in the [YES] button */
    UINT16                                     ui2_msg_no,         /* Messages in the [NO] button */
    UI_SIMPLE_DIALOG_STYLE_T                   e_style,            /* Dialog Style */
    UINT16                                     ui2_text_alignment, /* Dialog Text Alignment */
    BOOL                                       b_default_answer,   /* Default Answer */
    menu_common_page_simple_dialog_yes_fct     pf_yes,             /* Press Yes to run */
    menu_common_page_simple_dialog_no_fct      pf_no,              /* Press No to run */
    UINT32* pui4_page_id                                           /* Return the page id */
);

extern INT32 menu_common_page_simple_dialog_create_ex(
    UINT16                                     ui2_msg_txt,        /* Messages in the text dialog */
    UINT16                                     ui2_msg_yes,        /* Messages in the [YES] button */
    UINT16                                     ui2_msg_no,         /* Messages in the [NO] button */
    UINT16                                     ui2_msg_info,       /* Messages in the [Info] button */
    UI_SIMPLE_DIALOG_STYLE_T                   e_style,            /* Dialog Style */
    UINT16                                     ui2_text_alignment, /* Dialog Text Alignment */
    UI_SIMPLE_DIALOG_ANSWER                    e_default_answer,   /* Default Answer */
    menu_common_page_simple_dialog_yes_fct     pf_yes,             /* Press Yes to run */
    menu_common_page_simple_dialog_no_fct      pf_no,              /* Press No to run */
    menu_common_page_simple_dialog_info_fct    pf_info,            /* Press Info to run */
    UINT32* pui4_page_id                                           /* Return the page id */
);

#endif /* _MENU_COMMON_SIMPLE_DIALOG_H_ */

