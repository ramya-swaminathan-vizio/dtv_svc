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
 * Copyright (c) 2005, CrystalMedia Technology, Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: menu_page_tree.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *         This file contains the declarations of APPLICATION-RELATED functions
 * of the MENU applcation.
 *---------------------------------------------------------------------------*/

#ifndef _MENU_PAGE_TREE_H_
#define _MENU_PAGE_TREE_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_common/menu_common_simple_dialog.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef enum _MENU_ITME_TYPE_T
{
    MENU_ITEM_TYPE_LIST,
    MENU_ITEM_TYPE_LIST_SUBPAGE,
    MENU_ITEM_TYPE_LISTBOX,
    MENU_ITEM_TYPE_ACTION,
    MENU_ITEM_TYPE_SUBPAGE,
    MENU_ITEM_TYPE_MORE_SUBPAGE,
    MENU_ITEM_TYPE_RANGE,
    MENU_ITEM_TYPE_TEXT,
} MENU_ITEM_TYPE_T;

typedef enum _MENU_ITEM_RANGE_STYLE_T
{
    MENU_ITEM_RANGE_STYLE_BAR,
    MENU_ITEM_RANGE_STYLE_POINT
} MENU_ITEM_RANGE_STYLE_T;

typedef enum
{
    MENU_TAB_STYLE_NONE = 0,
    MENU_TAB_STYLE_LIST_TAB,
    MENU_TAB_STYLE_SUBPAGE_TAB,
    MENU_TAB_STYLE_LAST_ENTRY
}   MENU_TAB_STYLE_T;

/* list callback functions */
typedef VOID    (*menu_item_list_set_idx_fct)(UINT16 ui2_idx);
typedef UINT16  (*menu_item_list_get_idx_fct)(VOID);
typedef UINT16  (*menu_item_list_next_fct)(VOID);
typedef UINT16  (*menu_item_list_prev_fct)(VOID);
typedef VOID    (*menu_item_list_get_text_fct)(UINT16    ui2_idx,   /* in */
                                               UTF16_T*  w2s_str,   /* out */
                                               SIZE_T    z_len);    /* in, len of w2s_str */
typedef BOOL    (*menu_item_list_is_subpage_fct)(UINT16  ui2_idx,   /* in */
                                                  UINT32*   pui2_subpage);    /* output the subpage if return TRUE */
                                               

/* listbox callback functions */
typedef VOID    (*menu_item_listbox_set_idx_fct)(UINT16 ui2_idx);
typedef UINT16  (*menu_item_listbox_get_idx_fct)(VOID);
typedef VOID    (*menu_item_listbox_get_text_fct)(UINT16    ui2_idx,   /* in */
                                                  UTF16_T*  w2s_str,   /* out */
                                                  SIZE_T    z_len);    /* in, len of w2s_str */
typedef BOOL    (*menu_item_listbox_is_subpage_fct)(UINT16  ui2_idx,   /* in */
                                                  UINT32*   pui2_subpage);    /* output the subpage if return TRUE */

/* action calllback function */
typedef VOID (*menu_item_action_fct)(VOID);

/* range callback function */
typedef VOID (*menu_item_range_set_val_fct)(INT32 i4_val);
typedef INT32 (*menu_item_range_get_val_fct)(VOID);
typedef INT32 (*menu_item_range_incr_fct)(VOID);
typedef INT32 (*menu_item_range_decr_fct)(VOID);

/* text callback function */
typedef VOID  (*menu_item_text_get_text_fct)(UTF16_T*  w2s_str,   /* out */                                               
                                                 SIZE_T    z_len);    /* in, len of w2s_str */


/* is enabled/hidden callback function */
typedef BOOL (*menu_item_is_enabled_fct)(VOID);
typedef BOOL (*menu_item_is_hidden_fct)(VOID);

typedef struct _MENU_ITEM_T
{
    MENU_ITEM_TYPE_T        e_item_type;
    UINT16                  ui2_msgid_title;
    UINT16                  ui2_msgid_desc;

    union
    {
        struct
        {
            UINT16  ui2_elem_num;
            UINT16  ui2_msgid_elem_first;   /* only used when pf_get_text_idx is NULL */
            UINT16  ui2_msgid_elem_last;    /* only used when pf_get_text_idx is NULL */
            menu_item_list_set_idx_fct  pf_set_idx;         /* set index callback, required */
            menu_item_list_get_idx_fct  pf_get_idx;         /* get index callback, required */
            menu_item_list_next_fct     pf_next_idx;        /* next elem callback, optional */
            menu_item_list_prev_fct     pf_prev_idx;        /* prev elem callback, optional */
            menu_item_list_get_text_fct pf_get_text;        /* get text callback, optional */
            menu_item_list_is_subpage_fct pf_is_subpage;    /* get if there the given index is a subpage */
            BOOL     b_elem_desc;                              /* If there is description for elements*/
            UINT16   ui2_msgid_elem_desc_first;                /* The description for the first element. */
            UINT16   ui2_msgid_elem_desc_last;                 /* The description for the last element  */

        } t_list;

        struct
        {
            UINT16  ui2_elem_num;
            UINT16  ui2_msgid_elem_first;   /* only used when pf_get_text_idx is NULL */
            UINT16  ui2_msgid_elem_last;    /* only used when pf_get_text_idx is NULL */
            menu_item_list_set_idx_fct  pf_set_idx;         /* set index callback, required */
            menu_item_list_get_idx_fct  pf_get_idx;         /* get index callback, required */
            menu_item_list_next_fct     pf_next_idx;        /* next elem callback, optional */
            menu_item_list_prev_fct     pf_prev_idx;        /* prev elem callback, optional */
            menu_item_list_get_text_fct pf_get_text;        /* get text callback, optional */
            UINT16  ui2_msgid_action;
            UINT32  ui4_subpage_id;    
            
        } t_list_subpage;

        struct
        {
            UINT16  ui2_elem_num;
            UINT16  ui2_msgid_elem_first;   /* only used when pf_get_text_idx is NULL */
            UINT16  ui2_msgid_elem_last;    /* only used when pf_get_text_idx is NULL */
            menu_item_listbox_set_idx_fct  pf_set_idx;         /* set index callback, required */
            menu_item_listbox_get_idx_fct  pf_get_idx;         /* get index callback, required */
            menu_item_listbox_get_text_fct pf_get_text;        /* get text callback, optional */
            menu_item_listbox_is_subpage_fct pf_is_subpage;    /* get if there the given index is a subpage */
            BOOL     b_elem_desc;                              /* If there is description for elements*/
            UINT16   ui2_msgid_elem_desc_first;                /* The description for the first element. */
            UINT16   ui2_msgid_elem_desc_last;                 /* The description for the last element  */

        } t_listbox;

        struct
        {
            UINT16                       ui2_msgid_action;
            menu_item_action_fct         pf_action;
        } t_action;

        struct 
        {
            UINT16  ui2_msgid_action;
            UINT32  ui4_subpage_id;  
        }t_subpage;

        struct 
        {
            MENU_ITEM_RANGE_STYLE_T      e_range_style;
            menu_item_range_set_val_fct  pf_set_val;        /* set value callback, required */
            menu_item_range_get_val_fct  pf_get_val;        /* get value callback, required */
            menu_item_range_incr_fct     pf_incr;           /* incr value callback, optional */
            menu_item_range_decr_fct     pf_decr;           /* decr value callback, optional */
            INT32   i4_val_min;
            INT32   i4_val_max;
            BOOL    b_fast_mode;                            /* if fast mode supported */
        }t_range;

        struct
        {
            menu_item_text_get_text_fct  pf_get_text; /* get text callback, mandatory. */
        }t_text;
    }u;
} MENU_ITEM_T;

typedef struct _MENU_PAGE_TREE_INIT_T
{
    UINT16      ui2_max_item_num;
    UINT16      ui2_msgid_title;
} MENU_PAGE_TREE_INIT_T;

typedef enum
{
    MENU_PAGE_TREE_EVENT_LAYOUT_UPDATE,     /* pv_data = NULL */

    /* The last entry */
    MENU_PAGE_TREE_EVENT_END
}   MENU_PAGE_TREE_EVENT_T;

typedef VOID (*menu_page_tree_event_listener_fct)(
    UINT32                  ui4_page_id,
    MENU_PAGE_TREE_EVENT_T  e_event,
    VOID*                   pv_data
);

typedef struct _MENU_ITEM_SELECTION_RANGE_INIT_T
{
    INT32 i4_val_min;                               /* Min value of this item. */
    INT32 i4_val_max;                               /* Max value of this item. */
    menu_item_range_set_val_fct pf_set_val;         /* Set value callback. */
    menu_item_range_get_val_fct pf_get_val;         /* Get value callback. */
    menu_item_range_incr_fct     pf_incr;           /* incr value callback, optional */
    menu_item_range_decr_fct     pf_decr;           /* decr value callback, optional */
} MENU_ITEM_SELECTION_RANGE_INIT_T;

typedef struct _MENU_ITEM_SELECTION_LIST_INIT_T
{
    UINT16 ui2_msgid_elem_first;                    /* The first message id of the list. */
    UINT16 ui2_msgid_elem_last;                     /* The last message id of the list. */
    menu_item_list_set_idx_fct pf_set_idx;          /* Set value callback. */
    menu_item_list_get_idx_fct pf_get_idx;          /* Set value callback. */
    menu_item_list_next_fct     pf_next_idx;        /* next elem callback, optional */
    menu_item_list_prev_fct     pf_prev_idx;        /* prev elem callback, optional */
    menu_item_list_get_text_fct pf_get_text;        /* get text callback, optional */
} MENU_ITEM_SELECTION_LIST_INIT_T;

typedef struct _MENU_ITEM_SELECTION_SUBPAGE_INIT_T
{
    UINT16 ui2_msgid_action;                        /* The message id of the action. */
    UINT32 ui4_page_id;                             /* The page id of the sub-page. */
} MENU_ITEM_SELECTION_SUBPAGE_INIT_T;




/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
extern MENU_PAGE_FCT_TBL_T  t_g_menu_page_tree;

/*-----------------------------------------------------------------------------
                    external function prototype
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_tree_init(VOID);

extern INT32 menu_page_tree_create(
    UINT16 ui2_max_item_num,
    UINT16  ui2_msgid_title,
    UINT32* pui4_page_id
);

extern INT32 menu_page_tree_destroy(
    UINT32 ui4_page_id
);

extern INT32 menu_page_tree_add(
    UINT32 ui4_page_id,
    MENU_ITEM_T* pt_items,
    UINT16* pui2_item_id
);

extern INT32 menu_page_tree_create_subpage(
    UINT16  ui2_max_item_num,
    UINT16  ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_action,
    MENU_ITEM_T* pt_menu_item,
    UINT32* pui4_page_id);
extern INT32 menu_pm_page_create_item(UINT16               ui2_msgid_title,
                                              UINT16               ui2_msgid_desc,
                                              UINT16               ui2_msgid_action,
                                              MENU_PAGE_FCT_TBL_T* pt_page_fct_tbl,
                                              VOID*                pv_create_data,
                                              MENU_ITEM_T*         pt_menu_item,
                                              UINT32*              pi4_page_id);
extern INT32 menu_pm_page_create_dialog(UINT16                                     ui2_msgid_title,
                                                UINT16                                     ui2_msgid_desc,
                                                UINT16                                     ui2_msgid_action,
                                                UINT16                                     ui2_msg_txt,        /* Messages in the text dialog */
                                                UINT16                                     ui2_msg_yes,        /* Messages in the [YES] button */
                                                UINT16                                     ui2_msg_no,         /* Messages in the [NO] button */
                                                UI_SIMPLE_DIALOG_STYLE_T                   e_style,            /* Dialog Style */
                                                UINT16                                     ui2_text_alignment, /* Dialog Text Alignment */
                                                BOOL                                       b_default_answer,   /* Default Answer */
                                                menu_common_page_simple_dialog_yes_fct     pf_yes,             /* Press Yes to run */
                                                menu_common_page_simple_dialog_no_fct      pf_no,              /* Press No to run */
                                                MENU_ITEM_T*                               pt_menu_item,
                                                UINT32* ui4_page_item_id);

extern INT32 menu_page_tree_add_ex(
    UINT32 ui4_page_id,
    MENU_ITEM_T* pt_item,
    menu_item_is_enabled_fct pf_item_is_enabled,
    menu_item_is_hidden_fct  pf_item_is_hidden,
    UINT32* ui4_page_item_id);

extern INT32 menu_page_tree_remove(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id
);

extern INT32 menu_page_tree_enable_item(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id,
    BOOL   b_enable
);

extern INT32 menu_page_tree_hide_item(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id,
    BOOL   b_hide
);

extern INT32 menu_page_tree_set_auto_enable_hide(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id,
    menu_item_is_enabled_fct pf_item_is_enabled,
    menu_item_is_hidden_fct pf_item_is_hidden
);


extern INT32 menu_page_tree_set_auto_enable(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id,
    menu_item_is_enabled_fct pf_item_is_enabled
);

extern INT32 menu_page_tree_set_auto_hide(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id,
    menu_item_is_hidden_fct pf_item_is_hidden
);

extern INT32 menu_page_tree_set_res_auto_free(
    UINT32 ui4_page_id,
    BOOL   b_enable
);

extern INT32 menu_page_tree_get_ipage_status(
    UINT32  ui4_page_id,
    UINT16* pui2_ipage_crnt,
    UINT16* pui2_ipage_num
);

extern INT32 menu_page_tree_set_focus_item(
    UINT32    ui4_page_id,
    UINT16    ui2_item_id,
    BOOL      b_force_hlt
);

extern BOOL menu_focus_item_is_the_assign_item(UINT16 ui2_msgid_title);

extern INT32 menu_page_tree_get_focus_item(
    UINT32    ui4_page_id,
    UINT16*   pui2_item_id
);

extern INT32 menu_page_tree_set_help_tip(
    UINT32    ui4_page_id,
    UINT16    ui2_item_id,
    UINT16    ui2_msgid_desc
);

/* Event listener */
extern INT32 menu_page_tree_set_event_listener(
    menu_page_tree_event_listener_fct   pf_event_listener
);

/**
 *  Helper Function
 */
extern INT32 menu_page_tree_list_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_elem_first,
    UINT16 ui2_msgid_elem_last,
    menu_item_list_set_idx_fct pf_set_idx,
    menu_item_list_get_idx_fct pf_get_idx
);

INT32 menu_page_tree_list_item_by_text(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 num_elements,
    menu_item_list_set_idx_fct pf_set_idx,
    menu_item_list_get_idx_fct pf_get_idx,
    menu_item_list_get_text_fct pf_get_text);

extern INT32 menu_page_tree_sb_settings_eq_mode_list_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_elem_first,
    UINT16 ui2_msgid_elem_last,
    menu_item_list_set_idx_fct pf_set_idx,
    menu_item_list_get_idx_fct pf_get_idx,
    menu_item_list_get_text_fct pf_get_text,
    menu_item_list_prev_fct pf_prev_idx,
    menu_item_list_next_fct pf_next_idx);


extern INT32 menu_page_tree_list_item_set_elem_help_tip(
    MENU_ITEM_T* pt_menu_item,
    BOOL         b_elem_desc,
    UINT16       ui2_msgid_elem_desc_first,
    UINT16       ui2_msgid_elem_desc_last
);

extern INT32 menu_page_tree_listbox_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_elem_first,
    UINT16 ui2_msgid_elem_last,
    menu_item_list_set_idx_fct pf_set_idx,
    menu_item_list_get_idx_fct pf_get_idx
);

extern INT32 menu_page_tree_listbox_item_set_elem_help_tip(
    MENU_ITEM_T* pt_menu_item,
    BOOL         b_elem_desc,
    UINT16       ui2_msgid_elem_desc_first,
    UINT16       ui2_msgid_elem_desc_last
);

extern INT32 menu_page_tree_subpage_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_action,
    UINT32 ui4_page_id
);

extern INT32 menu_page_tree_action_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_action,
    menu_item_action_fct pf_action
);

extern INT32 menu_page_tree_range_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    INT32 i4_val_min,
    INT32 i4_val_max,
    MENU_ITEM_RANGE_STYLE_T e_range_style,
    menu_item_range_set_val_fct pf_set_val,
    menu_item_range_get_val_fct pf_get_val
);

extern INT32 menu_page_tree_text_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    menu_item_text_get_text_fct  pf_get_text
);

extern INT32 menu_page_tree_select_list_subpage_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    MENU_ITEM_SELECTION_LIST_INIT_T* pt_init);

extern INT32 menu_page_tree_select_list_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    MENU_ITEM_SELECTION_LIST_INIT_T* pt_init);

extern INT32 menu_page_tree_select_range_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    MENU_ITEM_SELECTION_RANGE_INIT_T* pt_init);

extern INT32 menu_page_tree_select_subpage_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    MENU_ITEM_SELECTION_SUBPAGE_INIT_T* pt_init);

extern INT32 menu_page_tree_add_with_help(
    UINT32 ui4_page_id,
    MENU_ITEM_T* pt_item,
    UINT16* pui2_item_id,
    UINT16 ui2_msgid_help);

extern INT32 menu_page_free(VOID);

extern HANDLE_T menu_page_get_font_h(VOID);

extern INT32 menu_page_tree_more_item(
                                      MENU_ITEM_T* pt_menu_item,
                                      UINT16 ui2_msgid_title,
                                      UINT16 ui2_msgid_desc,
                                      UINT16 ui2_msgid_action,
                                      UINT32 ui4_page_id);
extern BOOL menu_page_is_in_list_subpage_state(VOID);
extern VOID menu_page_tree_set_list_state(BOOL b_flag);

extern BOOL menu_page_is_reset_page(UINT32 ui4_page_id);
extern INT32 menu_page_tree_change_title(UINT32 ui4_page_id, UINT16 ui2_msgid_title);
extern INT32 menu_page_tree_help_tip_back_proc(VOID);
extern INT32 menu_page_tree_get_widget(
                                        UINT32      ui4_page_id,
                                        UINT16      ui2_msgid_title,
                                        HANDLE_T**  pt_hdr
                                        );
INT32 menu_page_tree_set_offset(UINT32 ui4_page_id, INT16 i2_offset);


#endif /* _MENU_PAGE_TREE_H_ */
