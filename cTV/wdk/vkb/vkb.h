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
 * $RCSfile: vkb.h,v $
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
#ifndef _WDK_VKB_H_
#define _WDK_VKB_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "wdk/a_wdk.h"
#include "wdk/a_vkb.h"

#include "res/wdk/vkb/vkb_rc.h"            /* Custom Logic */
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

#define VKB_RET_ON_ERR(_expr) if(_expr != 0) \
    {DBG_ERROR (("<VKB> ERR: file = %s, line = %d, ret = %d \n\r", __FILE__, __LINE__, _expr)); return -1;}

#define  VKB_INPUT_TEXT_MAX_LEN            (256)

/* Customization part of select key. */
#ifndef CUSTOM_BTN_VKB_SELECT
    #define CUSTOM_BTN_VKB_SELECT          (BTN_SELECT)
#endif

/* Customization part of key caption. */
#ifndef VKB_KEY_CAPTION_MAX_LEN
    #define VKB_KEY_CAPTION_MAX_LEN        (10)
#endif

#define VKB_INVALID_INDEX                  (0xFF)

#define VKBR_INV_ARG                       (-1)
#define VKBR_DO_NOT_CONTINUE               (1)

#define VKB_LATIN_KEY_MAX_ELEM_NUM         (10)

#define APP_VKB_SUPPORT_LATIN_CHAR
#define VKB_KEYPAD_CTRL_SYMBOL_KEY_IDX      (0)
#define VKB_KEYPAD_CTRL_CAPS_KEY_IDX        (1)
#define VKB_KEYPAD_CTRL_COM_KEY_IDX         (2)
#define VKB_KEYPAD_CTRL_LATIN_KEY_IDX       (2)
#define VKB_KEYPAD_CTRL_SPACE_KEY_IDX       (3)
#define VKB_KEYPAD_CTRL_DEL_KEY_IDX         (4)
#define VKB_KEYPAD_CTRL_DELETE_KEY_IDX      (VKB_KEYPAD_CTRL_KEY_TEXT_NUM - 1)


/*
   Focused widget types.
*/
typedef enum
{
    VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY = 0,      /* Normal keypad is focused. */
    VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY,            /* Ctrl keypad is focused. */
    VKB_FOCUS_WIDGET_BTN_OK,                     /* Button OK is focused. */
    VKB_FOCUS_WIDGET_BTN_CANCEL,                  /* Button Cancel is focused. */
    VKB_FOCUS_WIDGET_EDIT_BOX,                    /* Edit box is focused. */
    VKB_FOCUS_WIDGET_EB_CLR
}   VKB_FOCUS_WIDGET_T;

/*
   Focus change type.
*/
typedef enum
{
    VKB_FOCUS_CHG_INITIAL = 0,                   /* Change focus on initial widget. */
    VKB_FOCUS_CHG_UP_KEY,                        /* Change focus via UP key. */
    VKB_FOCUS_CHG_DOWN_KEY,                      /* Change focus via Down key. */
    VKB_FOCUS_CHG_LEFT_KEY,                      /* Change focus via Left key. */
    VKB_FOCUS_CHG_RIGHT_KEY                      /* Change focus via Right key. */
}   VKB_FOCUS_CHG_TYPE_T;

/*
   Keypad normal key focus description.
*/
typedef struct _VKB_FOCUS_KEYPAD_NORMAL_KEY_DESCR_T
{
    UINT8                   ui1_focus_idx_row;   /* Focus index of row */
    UINT8                   ui1_focus_idx_col;   /* Focus index of row */
} VKB_FOCUS_KEYPAD_NORMAL_KEY_DESCR_T;

/*
   Keypad ctrl key focus description.
*/
typedef struct _VKB_FOCUS_KEYPAD_CTRL_KEY_DESCR_T
{
    UINT8                   ui1_focus_idx;       /* Focus index of row */
} VKB_FOCUS_KEYPAD_CTRL_KEY_DESCR_T;

/*
   VKB focused item.
*/
typedef struct _VKB_FOCUS_ITEM_T
{
    VKB_FOCUS_WIDGET_T   e_type;                 /* Type of this item */

    VKB_FOCUS_KEYPAD_NORMAL_KEY_DESCR_T    t_normal_key;
    VKB_FOCUS_KEYPAD_CTRL_KEY_DESCR_T      t_ctrl_key;

} VKB_FOCUS_ITEM_T;

/*
   Key types.
*/
typedef enum
{
    VKB_KEY_TYPE_SINGLE_INPUT_KEY = 0,           /* Input one character & Caption is the same character. */
    VKB_KEY_TYPE_COMPOSITE_INPUT_KEY,            /* Input a string || Caption is a string. */
    VKB_KEY_TYPE_CTRL_KEY,                       /* Invoke a callback on every press. */
    VKB_KEY_TYPE_RESERVED_KEY                    /* Reserved for feature use. */
}   VKB_KEY_TYPE_T;

/*
   Input key definition -- UI related data
*/
typedef struct _VKB_KEY_UI_DESCR_T
{
    CHAR        ach_captions_no_caps_lock[VKB_KEY_CAPTION_MAX_LEN];
    CHAR        ach_captions_in_caps_lock[VKB_KEY_CAPTION_MAX_LEN];
    CHAR        ach_captions_symbol_page[VKB_KEY_CAPTION_MAX_LEN];
} VKB_KEY_UI_DESCR_T;

/*
   Input key definition -- SINGLE_INPUT_KEY
*/
typedef struct _VKB_KEY_SINGLE_INPUT_KEY_DESCR_T
{
    CHAR        ch_value_no_caps_lock;
    CHAR        ch_value_in_caps_lock;
    CHAR        ch_value_symbol_page;
} VKB_KEY_SINGLE_INPUT_KEY_DESCR_T;

/*
   Input key definition -- COMPOSITE_INPUT_KEY
*/
typedef struct _VKB_KEY_COMPOSITE_INPUT_KEY_DESCR_T
{
    CHAR        ach_values_no_caps_lock[VKB_KEY_CAPTION_MAX_LEN];
    CHAR        ach_values_in_caps_lock[VKB_KEY_CAPTION_MAX_LEN];

    VKB_KEY_UI_DESCR_T t_key_ui_descr;
} VKB_KEY_COMPOSITE_INPUT_KEY_DESCR_T;

/*
   Input key definition -- CTRL_KEY
*/

/* For Actions (No matter Main List or Sub List) */
typedef INT32 (*vkb_action_fct)(VOID* pv_tag, VOID* pv_vkb_ctrl);

typedef struct _VKB_KEY_CTRL_KEY_DESCR_T
{
    VOID*              pv_tag;                   /* Tag for action */
    vkb_action_fct     pf_fct;                   /* Function pointer to action */

    VKB_KEY_UI_DESCR_T t_key_ui_descr;
} VKB_KEY_CTRL_KEY_DESCR_T;

/*
   VKB Keypad Key Item.
*/
typedef struct _VKB_KEYPAD_KEY_ITEM_T
{
    VKB_KEY_TYPE_T   e_type;                     /* Type of this item */

    union
    {
        VKB_KEY_SINGLE_INPUT_KEY_DESCR_T    t_single_input_key;
        VKB_KEY_COMPOSITE_INPUT_KEY_DESCR_T t_composite_input_key;
        VKB_KEY_CTRL_KEY_DESCR_T            t_ctrl_key;
    } u;

} VKB_KEYPAD_KEY_ITEM_T;

typedef struct _VKB_KEYPAD_EB_CLEAR
{
    BOOL                    b_eb_clr_attached;      /* TRUE:indicator extern delete all attached to vkb */
    HANDLE_T                h_eb_clear_icon;
    HANDLE_T                h_eb_clear_icon_self;   /* edit box of vkb itself */
    GL_RECT_T               t_rect;
    WGL_INSET_T             t_inset;
    WGL_IMG_INFO_T          t_img_info;
    WGL_EB_KEY_MAP_T        t_eb_clear_key_map;

}VKB_KEYPAD_EB_CLEAR;

typedef struct _VKB_KEYPAD_LATIN_KEY_ITEM
{
    UINT8 ui1_row_offset;
    UINT8 ui1_col_offset;
    UINT8 ui1_elem_num;
    UTF16_T w2s_latin_char[VKB_LATIN_KEY_MAX_ELEM_NUM];
    UTF16_T w2s_latin_char_in_capslock[VKB_LATIN_KEY_MAX_ELEM_NUM];
}VKB_KEYPAD_LATIN_KEY_ITEM;
/*
   VKB internal control data.
*/
typedef struct _VKB_CONTROL_LOGIC_T
{
    UINT32                  ui4_style_mask;                        /* style of VKB, can be changed run-time */
    BOOL                    b_eb_attached;                         /* TRUE:indicator extern editbox attached to vkb */

    /* widgets definition */
    HANDLE_T                h_main_frm;                            /* container frame */
    HANDLE_T                h_kb_frm;                              /* keyboard frame */
    HANDLE_T                h_label_txt;                           /* label text (parent: main frame) */
    HANDLE_T                h_input_eb_self;                       /* edit box of vkb itself */
    HANDLE_T                h_input_editbox;                       /* edit box (parent: main frame) */
    HANDLE_T                h_ok_txt;                              /* ok button is a text widget */
    HANDLE_T                h_cancel_txt;                          /* cancel button is a text widget */

    VKB_KEYPAD_EB_CLEAR     t_eb_clear_icon;
    /* keypad widgets definition */
    /* normal key widgets in a 2-dimension arrary */
    HANDLE_T                aah_normal_key_txt[VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM][VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM];
    /* ctrl key widgets in a 1-dimension arrary */
    HANDLE_T                ah_ctrl_key_txt[VKB_KEYPAD_CTRL_KEY_TEXT_NUM];
    HANDLE_T                ah_ctrl_key_logo[VKB_KEYPAD_CTRL_KEY_TEXT_NUM];

    /* keypad: normal key */
    VKB_KEYPAD_KEY_ITEM_T   aat_keypad_normal_key[VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM][VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM];
    VKB_KEYPAD_LATIN_KEY_ITEM at_keypad_latin_key[VKB_KEYPAD_LATIN_KEY_TEXT_NUM];
    /* keypad: ctrl key */
    VKB_KEYPAD_KEY_ITEM_T   at_keypad_ctrl_key[VKB_KEYPAD_CTRL_KEY_TEXT_NUM];
    BOOL                    b_symbol_page;                         /* Symbol /Character page. */
    BOOL                    b_caps_lock;                           /* caps lock */
    BOOL                    b_latin_lock;                           /* Latin lock */
    BOOL                    b_latin_expand;
    UINT8                   ui1_cur_latin_key_idx;
    VKB_FOCUS_ITEM_T        t_focus_item;                          /* current focused item */
    UINT32                  ui4_max_char_num;                      /* max input char number */
    UTF16_T                 aw2s_txt[VKB_INPUT_TEXT_MAX_LEN+1];    /* input text value: UTF16_T */
    UTF16_T                 aw2s_ok_txt[32];
    UTF16_T                 aw2s_cncl_txt[32];

    VKB_RC_CONFIG_DATA_T*   pt_rc_config;                          /* general resource configuration data, shared by all instance */

    vkb_data_change_nfy_fct pf_fct;
    VOID*                   pv_tag;

    VKB_EB_ATTACH_DATE     t_eb_attach_data;                       /* Attached data of EditBox */
} VKB_CONTROL_LOGIC_T;

extern INT32 a_vkb_current_is_top_row(HANDLE_T  h_vkb_handle,
                                      BOOL*     pb_is_top_row);

extern INT32 a_vkb_current_is_bottom_row(HANDLE_T   h_vkb_handle,
                                         HANDLE_T*  ph_cancel_handle,
                                         BOOL*      pb_is_bottom_row);

extern INT32 a_vkb_set_focus_ex(HANDLE_T  h_vkb_handle);

extern INT32 a_vkb_reset_eb_handle(
                                HANDLE_T h_vkb_handle
                                );

extern INT32 a_vkb_attach_eb(
                                HANDLE_T h_vkb_handle,
                                VKB_EB_ATTACH_DATE *pt_attach_data
                            );

extern INT32 a_vkb_is_eb_attach(
                                HANDLE_T h_vkb_handle,
                                BOOL *pb_is_eb_attach,
                                BOOL *pb_is_eb_clr_attach);

extern VOID a_vkb_set_lang(CHAR *ps_lang);

extern INT32 a_vkb_set_focus_to_current_btn(HANDLE_T h_vkb_handle, BOOL b_repaint);
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
#endif /* _WDK_VKB_H_ */

