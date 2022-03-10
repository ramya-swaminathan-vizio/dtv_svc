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
 * $RCSfile: a_optl.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/5 $
 * $SWAuthor: $
 * $MD5HEX: 0555add6f5bb32c55eaf504cbf527d75 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_OPTL_H_
#define _A_OPTL_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_handle.h"
#include "u_wgl.h"
#include "u_wgl_common.h"
#include "app_util/a_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define OPTL_CUST_MASK_T            UINT32

/* Return Value */
#define OPTLR_OK                      ((INT32)  0)
#define OPTLR_FAIL                    ((INT32) -1)
#define OPTLR_INV_ARG                 ((INT32) -2)
#define OPTLR_OUT_OF_MEMORY           ((INT32) -3)
#define OPTLR_WIDGET_CREATE_FAIL      ((INT32) -4)

#define OPTL_LB_LABEL_TXT_MAX       31
#define OPTL_LB_MAIN_TXT_MAX        64
#define OPTL_LB_SUB_TXT_MAX         64

/* OPTL style mask */
#define OPTL_STYLE_MASK_NORMAL                MAKE_BIT_MASK_32(0)
#define OPTL_STYLE_MASK_BTN_R_AS_BTN_SEL      MAKE_BIT_MASK_32(1)
#define OPTL_STYLE_MASK_NO_CANCEL_OPERATION   MAKE_BIT_MASK_32(2)
#define OPTL_STYLE_MASK_DEFAULT_HIDE_TIMEOUT  MAKE_BIT_MASK_32(3)

/* optl customazation mask*/
#define OPTL_CUST_MASK_MAIN_FRM_BK              MAKE_BIT_MASK_32(0)
#define OPTL_CUST_MASK_MAIN_LB_ELM_HT_BK        MAKE_BIT_MASK_32(1)
#define OPTL_CUST_MASK_MAIN_LB_ELM_NML_BK       MAKE_BIT_MASK_32(2)
#define OPTL_CUST_MASK_MAIN_LB_ELEM_UF_HLT_BK   MAKE_BIT_MASK_32(3)
#define OPTL_CUST_MASK_SUB_FRM_BK               MAKE_BIT_MASK_32(4)
#define OPTL_CUST_MASK_SUB_LB_ELM_HT_BK         MAKE_BIT_MASK_32(5)
#define OPTL_CUST_MASK_SUB_LB_ELM_NML_BK        MAKE_BIT_MASK_32(6)
#define OPTL_CUST_MASK_OPTL_FRM_RECT            MAKE_BIT_MASK_32(7)
#define OPTL_CUST_MASK_MAIN_LB_INIT_DATA        MAKE_BIT_MASK_32(8)
#define OPTL_CUST_MASK_SUB_LB_INIT_DATA         MAKE_BIT_MASK_32(9)
#define OPTL_CUST_MASK_MAIN_LB_FONT             MAKE_BIT_MASK_32(10)
#define OPTL_CUST_MASK_SUB_LB_FONT              MAKE_BIT_MASK_32(11)
#define OPTL_CUST_MASK_MAIN_LB_TXT_CLR          MAKE_BIT_MASK_32(12)
#define OPTL_CUST_MASK_SUB_LB_TXT_CLR           MAKE_BIT_MASK_32(13)
#define OPTL_CUST_MASK_BACK_BTN_RECT            MAKE_BIT_MASK_32(14)
#define OPTL_CUST_MASK_BACK_BTN_NR_BK           MAKE_BIT_MASK_32(15)
#define OPTL_CUST_MASK_BACK_BTN_HLT_BK          MAKE_BIT_MASK_32(16)
#define OPTL_CUST_MASK_BACK_BTN_INIT_DATA       MAKE_BIT_MASK_32(17)

/* Data change notification*/
#define   OPTL_MSG_ITEM_HIGHLIGHT   (1)     /* pv1=Main Index, pv2=Sub Index*/
#define   OPTL_MSG_KEY_INPUT        (2)     /* pv1=ui4_key_code */
#define   OPTL_MSG_CANCELLED        (3)     /* [OPTION] on Main/Sub List;
                                               [BACK] or [LEFT] on Main List
                                               or Back Button*/

#define   OPTL_MSG_HIDE_TIMEOUT     (4)     /* Reached hide timeout.

                                               [Notice] This message originated from timer thread.
                                               You must context switch to your thread to do the behavior. */
#define   OPTL_MSG_CHECK_KEY_INPUT  (5)
#define   OPTL_INVALID_INDEX  (0xFFFF)

typedef enum
{
    OPTL_ITEM_TYPE_ACTION = 0,
    OPTL_ITEM_TYPE_SUBLIST

} OPTL_ITEM_TYPE_T;

typedef struct _OPTL_GUI_RC_T
{
       INT32    i4_left;
       INT32    i4_top;

} OPTL_GUI_RC_T;

typedef VOID (*optl_data_change_nfy_fct)(VOID*    pv_tag,
                                         UINT32   ui4_msg,
                                         VOID*    pv_param1,
                                         VOID*    pv_param2);

typedef UINT32 (*optl_get_key_src_fct)(VOID);

typedef struct _OPTL_LB_INIT_DATA_T
{
    GL_RECT_T                     t_frm_rect;
    GL_RECT_T                     t_back_rect;
    GL_RECT_T                     t_lb_rect;
    WGL_INSET_T                   t_lb_cnt_inser;
    WGL_INSET_T                   t_lb_elem_inser;
    WGL_INSET_T                   t_lb_col_inser;
    UINT8                         ui1_lb_txt_align;
    UINT8                         ui1_lb_label_align;
    UINT16                        ui2_lb_col_width;
    UINT16                        ui2_lb_label_col_width;
    UINT16                        ui2_lb_height;
    UINT16                        ui2_lb_elem_dtance;
}OPTL_LB_INIT_DATA_T;

typedef struct _OPTL_CUSTOMIZATION_DATA_T
{
    WGL_HIMG_TPL_T                h_main_frm_bk;
    WGL_HIMG_TPL_T                h_back_btn_nr;
    WGL_HIMG_TPL_T                h_back_btn_hlt;
    WGL_HIMG_TPL_T                h_main_lb_elem_hlt_bk;
    WGL_HIMG_TPL_T                h_main_lb_elem_nml_bk;
    WGL_HIMG_TPL_T                h_main_lb_elem_uf_hlt_bk;
    WGL_HIMG_TPL_T                h_sub_frm_bk;
    WGL_HIMG_TPL_T                h_sub_lb_elem_hlt_bk;
    WGL_HIMG_TPL_T                h_sub_lb_elem_nml_bk;
    GL_RECT_T                     t_optl_frm_rect;
    OPTL_LB_INIT_DATA_T*          pt_main_lb_init_data;
    OPTL_LB_INIT_DATA_T*          pt_sub_lb_init_data;
    WGL_FONT_INFO_T               t_main_lb_font;
    WGL_FONT_INFO_T               t_sub_lb_font;
    WGL_LB_COLOR_ELEM_SET_T       t_main_lb_col_txt_color;
    WGL_LB_COLOR_ELEM_SET_T       t_sub_lb_col_txt_color;
}OPTL_CUSTOMIZATION_DATA_T;

typedef struct _OPTL_INIT_T
{
    HANDLE_T                     h_parent;
    OPTL_GUI_RC_T                t_gui_rc;
    UINT32                       ui4_style_mask;
    optl_data_change_nfy_fct     pf_fct;
    optl_get_key_src_fct         pf_get_key_src_fct;
    VOID*                        pv_tag;
    OPTL_CUST_MASK_T             ui4_custom_flag;
    UINT32                       ui4_sleep_time;
    OPTL_CUSTOMIZATION_DATA_T    t_customization;
} OPTL_INIT_T;

/* For Actions (No matter Main List or Sub List) */
typedef INT32 (*optl_action_fct)(VOID* pv_tag);

/* For Sublist Descriptor */
typedef INT32 (*optl_get_sub_hlt_idx_fct)(VOID* pv_tag, UINT16* pui2_hlt_idx);


typedef struct _OPTL_ITEM_ACTION_DESCR_T
{
    VOID*              pv_tag;      /* Tag for action */
    optl_action_fct    pf_fct;      /* Function pointer to action */

} OPTL_ITEM_ACTION_DESCR_T;

typedef struct _OPTL_SUBITEM_T
{
    UTF16_T*           pw2s_text;   /* Display text for this item. */
    UTF16_T*           pw2s_label;
    VOID*              pv_tag;      /* Tag for action */
    optl_action_fct    pf_fct;      /* Function pointer to action */

} OPTL_SUBITEM_T;

typedef struct _OPTL_ITEM_SUBLIST_DESCR_T
{
    UINT16          ui2_num_of_sub_items;   /* How many sub items */
    UTF16_T*        pw2s_title;
    OPTL_SUBITEM_T* pt_sub_item;            /* Point to array of sub items */
    VOID*                         pv_tag;                     /* Tag for get_sub_hlt_idx_fct */
    optl_get_sub_hlt_idx_fct      pf_get_sub_hlt_idx_fct;     /* Query for current sub hlt index. */
} OPTL_ITEM_SUBLIST_DESCR_T;


typedef struct _OPTL_ITEM_T
{
    OPTL_ITEM_TYPE_T   e_type;     /* Type of this item */
    UTF16_T*           pw2s_text;  /* Display text for this item. */
    UTF16_T*           pw2s_label;
    BOOL               b_is_disable;    /* The elem is disabled */

    union
    {
        OPTL_ITEM_ACTION_DESCR_T    t_action;
        OPTL_ITEM_SUBLIST_DESCR_T   t_subopt_list;
    } u;

} OPTL_ITEM_T;


typedef struct _OPTL_ITEM_DEF_T
{
    UINT16       ui2_num_of_opt_items;  /* How many option items */
    UTF16_T*     pw2s_title;            /* The option list's title */
    OPTL_ITEM_T* pt_opt_item;           /* Point to array of option items */

} OPTL_ITEM_DEF_T;


/* =========================================================================== */

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32 a_optl_create(
                    OPTL_INIT_T*        pt_optl_init,                   /* In  */
                    HANDLE_T*           ph_optl_handle);                /* Out */

extern INT32 a_optl_destroy(
                    HANDLE_T            h_optl_handle);                 /* In */

extern INT32 a_optl_set_float_widget(
                    HANDLE_T            h_optl_handle,                  /* In */
                    BOOL                b_float);                       /* In */

extern INT32 a_optl_set_option_items(
                    HANDLE_T            h_optl_handle,                  /* In */
                    OPTL_ITEM_DEF_T*    pt_optl_item_def);               /* In */

extern INT32 a_optl_set_gui_rc(
                    HANDLE_T            h_optl_handle,                  /* In */
                    OPTL_GUI_RC_T*      pt_gui_rc);                     /* In */

extern INT32 a_optl_set_next_hlt_index(
                        HANDLE_T        h_optl_handle,
                        BOOL          b_is_main_next_idx,
                        BOOL          b_is_sub_next_idx,
                        BOOL          b_is_repaint);

extern INT32 a_optl_set_hlt_index(
                        HANDLE_T        h_optl_handle,                  /* In */
                        UINT16          ui2_main_hlt_index,             /* In */
                        UINT16          ui2_sub_hlt_index);             /* In */

extern INT32 a_optl_get_hlt_index(
                        HANDLE_T        h_optl_handle,                  /* In */
                        UINT16*         pui2_main_hlt_index ,           /* Out */
                        UINT16*         pui2_sub_hlt_index);            /* Out */

extern INT32 a_optl_repaint(
                    HANDLE_T            h_optl_handle);                 /* In */

extern INT32 a_optl_set_visibility(
                    HANDLE_T            h_optl_handle,                  /* In */
                    BOOL                b_visible);                     /* In */

extern INT32 a_optl_set_focus(
                    HANDLE_T            h_optl_handle);                 /* In */

extern INT32 a_optl_show(
                    HANDLE_T            h_optl_handle);                 /* In */

extern INT32 a_optl_hide(
                    HANDLE_T            h_optl_handle);                 /* In */

extern INT32 a_optl_enable_disable_item(HANDLE_T            h_optl_handle,
                                             UINT8               ui1_item_idx,
                                         BOOL                b_is_disable,
                                             BOOL                b_is_repaint);

extern INT32 a_optl_set_main_list_text(HANDLE_T            h_optl_handle,
                                       OPTL_ITEM_DEF_T*    pt_optl_item_def);
#endif /* _A_OPTL_H_ */
