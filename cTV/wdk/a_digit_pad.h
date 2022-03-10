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
 * $RCSfile: a_digit_pad.h $
 * $Revision: #1 $
 * $Date: 2020/03/20 $
 * $Author: yuwen.han $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: yuwen.han $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: GUI composite component -- Time Entry
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_WDK_DIGIT_PAD_H_
#define _A_WDK_DIGIT_PAD_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "a_wdk.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef enum _DIGIT_PAD_KEY_EVENT_
{
    /* data */
    DIGIT_PAD_DIGIT_KEY = 0,        // 0~9 and '-', pv_param can used to get the value of digit key
    DIGIT_PAD_DEL_KEY,              // del key
    DIGIT_PAD_BUTTON_OK,            // ok button
    DIGIT_PAD_BUTTON_CANCEL,        // cancel button
    DIGIT_PAD_BUTTON_INFO,          // info button
    DIGIT_PAD_NAV_BACK,             // notify parent to process back key
    DIGIT_PAD_FOCUS_TO_ABOVE_WGL,   // notify parent to foucs wgl above digit pad
    DIGIT_PAD_FOCUS_TO_BELOW_WGL    // notify parent to foucs wgl below digit pad
} DIGIT_PAD_EVENT_TYPE;

typedef struct _DIGIT_PAD_POSITION_
{
    /* data */
    UINT32  ui4_left;
    UINT32  ui4_top;

} DIGIT_PAD_POSITION;

typedef struct _DIGIT_PAD_BTN_KEY
{
    BOOL b_enable;              // if set false, button will not be created
    UINT16 ui2_text_key;        // the text of button, if button is enable, this field is necessary
} DIGIT_PAD_BTN_KEY;

typedef BOOL (*digit_rc_event_default_handle)(UINT32 ui4_msg,
                                          VOID* pv_param1,
                                          VOID* pv_param2);

typedef struct _DIGIT_PAD_CONFIG_
{
    BOOL b_dash_key_enable;     // if set false, button will not be created
    BOOL b_del_key_grayout;     // set 'del' gray out or not
    BOOL b_dash_key_grayout;
    HANDLE_T  parent_frame;     
    DIGIT_PAD_POSITION position;
    VOID (*digit_key_event_nfy)(DIGIT_PAD_EVENT_TYPE, VOID*);       // set callback function
    digit_rc_event_default_handle pf_rc_event_default_handle;       /* to process rc keys that digit pad doesn't processed*/
    DIGIT_PAD_BTN_KEY btn_ok;
    DIGIT_PAD_BTN_KEY btn_cancel;
    BOOL b_info_ok_key_enable; // if set info & ok key, should disable btn_ok to avoid fuction conflict
} DIGIT_PAD_CONFIG;

/*
  must use this function to init a configuration.
  this function will init a configuration for create a digit pad without '-' and buttons,
  you could modify the configuration inited by this function to create a digit pad you want.
*/
extern VOID a_digit_pad_init_config(DIGIT_PAD_CONFIG* pdigit_cfg);
extern INT32 a_digit_pad_create(DIGIT_PAD_CONFIG digit_cfg,
                                HANDLE_T* ph_digit_handle);
extern INT32 a_digit_pad_destroy(HANDLE_T h_vkb_handle);
extern INT32 a_digit_pad_show(HANDLE_T h_digit_pad_handle);
extern INT32 a_digit_pad_hide(HANDLE_T h_digit_pad_handle);
extern INT32 a_digit_pad_repaint(HANDLE_T h_digit_pad_handle);
extern INT32 a_digit_pad_set_visibility(HANDLE_T h_digit_pad_handle, BOOL b_visible);
extern INT32 a_digit_pad_focus(HANDLE_T h_digit_pad_handle);
extern INT32 a_digit_pad_grayout_del(HANDLE_T h_digit_pad_handle, BOOL b_gray); // set 'del' gray out or not
extern INT32 a_digit_pad_focus_btn_ok(HANDLE_T h_digit_pad_handle); 
extern INT32 a_digit_pad_grayout_dash(HANDLE_T h_digit_pad_handle, BOOL b_gray); // set '-' gray out or not
#endif // _A_WDK_DIGIT_PAD_H_
