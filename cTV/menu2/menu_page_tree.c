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
 * $RCSfile: $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor: $
 * $MD5HEX:  $
 *
 * Description:
 *         This file contains the declarations of APPLICATION-RELATED functions
 * of the MENU applcation.
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                     include files
-----------------------------------------------------------------------------*/
#include "res/menu2/menu_img.h"

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_lnk_list.h"
#include "u_drv_cust.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_fe.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_wgl_rect.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_ui.h"

#include "u_sb_atsc_eng.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_page_tree.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"

#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/menu2/menu_custom.h"
#include "res/menu2/menu_cust_define.h"

#include "app_util/ui/_ui.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "menu2/menu_common/a_menu_page_color_tuner.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "nav/input_src/input_src.h"
#ifdef APP_MENU_MMP_COEXIST
#include "mmp/browse_eng/mmp_browse_eng.h"
#endif
#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif

#include "menu2/menu_dbg.h"


#if( defined(APP_SUPPORT_PIC_HOT_KEY) ) // MENU_SUPPORT_HOT_KEY_PIC
extern BOOL a_menu_is_pic_hot_key(VOID);
#endif

#if 0//( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO )
extern BOOL a_menu_is_hot_key_BTN_ASPECT(VOID);
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define DEBUG_PAGE_TREE(x)  // x


#define MENU_PAGE_TREE_MAX_ITEM  9
#define _TTS_CNT_MAX_LEN        ((UINT16)512)

#define _MENU_TREE_TTS_PLAY_UNKNOW              (0x00)
#define _MENU_TREE_TTS_PLAY_TITLE               (0x01)
#define _MENU_TREE_TTS_PLAY_VAL                 (0x10)
#define _MENU_TREE_TTS_PLAY_TITLE_AND_VAL       (_MENU_TREE_TTS_PLAY_TITLE|_MENU_TREE_TTS_PLAY_VAL)
#define _ITEMS_PER_IPAGE                         (11)
typedef DLIST_T(_PAGE_TREE_ITEM_T) PAGE_TREE_ITEM_LIST_T;
typedef DLIST_ENTRY_T(_PAGE_TREE_ITEM_T) PAGE_TREE_ITEM_LINK_T;

typedef enum
{
    PAGE_TREE_STATE_NORMAL,     /* The normal state */
    PAGE_TREE_STATE_SLIDER,     /* The slider state in which only the slider bar
                                   is shown */
    PAGE_TREE_STATE_LISTBOX     /* The listbox state in which the listbox is shown.
                                   is shown */
}   PAGE_TREE_STATE_T;

typedef enum
{
    PAGE_TREE_HELP_LST_UNKNOWN = 0,
    PAGE_TREE_HELP_LST_LIST,
    PAGE_TREE_HELP_LST_RANGE,
    PAGE_TREE_HELP_LST_SUBPAGE,
    PAGE_TREE_HELP_LST_ACTION,
    PAGE_TREE_HELP_LST_TEXT,
}   PAGE_TREE_HELP_LST_T;

typedef struct _PAGE_TREE_ITEM_T
{
    PAGE_TREE_ITEM_LINK_T   t_link;     /* the double linked list */
    MENU_ITEM_T         t_menuitem;     /* menu item object from client */
    struct _PAGE_TREE_T*    pt_page;    /* the page tree object the item belong to */
    UINT16              ui2_item_id;    /* item id */
    UINT16              ui2_item_idx;   /* item index, the location of item.
                                           The hidden item would have the same index
                                           of previous item; Otherwise, plus one of
                                           previous one. */
    HANDLE_T            h_widget;       /* the widget associate to this item */
    BOOL                b_enabled;      /* if the item is enabled */
    BOOL                b_hidden;       /* if the item is hidden */
    BOOL                b_auto_chg_lang;/* if the item is changed automatically */
    menu_item_is_enabled_fct    pf_is_enabled;
                                        /* Callback function to check if the
                                        item is enabled. If the function is NULL,
                                        it will not apply auto enable/disable
                                        feature */
    menu_item_is_hidden_fct     pf_is_hidden;
                                        /* Callback function to check if the
                                        item is hidden. If the function is NULL,
                                        it will not apply auto hide/show
                                        feature */
} PAGE_TREE_ITEM_T;

typedef struct _PAGE_TREE_T
{
    UINT32              ui4_page_id;        /* page id */
    UINT16              ui2_max_item_num;   /* maximum item of the page */
    UINT16              ui2_msgid_title;    /* title message id */
    UINT16              ui2_item_num;       /* total number of menu items */
    UINT16              ui2_item_id_counter;/* item id counter */
    UINT16              ui2_items_per_ipage;/* item number per inner-page */
    UINT16              ui2_ipage_crnt;     /* current inner-page */
    UINT16              ui2_ipage_num;      /* number of inner-page */
    INT16               i2_offset;          /* index of first show item */
    HANDLE_T            h_cnt_frm;          /* the content frame of this page */
    PAGE_TREE_STATE_T   e_state;            /* state of this page. */
    PAGE_TREE_ITEM_LIST_T   t_item_list;    /* the item list */
    PAGE_TREE_ITEM_T*   pt_item_focus;      /* the focused menu item */
    PAGE_TREE_HELP_LST_T    e_help_lst;     /* the help list state */
    BOOL                b_lang_chg;         /* If the flag turns on, when this
                                               page show, it will invoke the
                                               _chg_lang() procedure. */
    BOOL                b_res_alloc;        /* If the resouce has been allocated */
    BOOL                b_res_auto_free;    /* If the resouce dispose when page hide */
    BOOL                b_force_hlt;
} PAGE_TREE_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T    t_g_menu_page_tree;
HANDLE_T               h_g_input_source_wgt = NULL_HANDLE;
HANDLE_T               h_g_aud_lang_list_wgt = NULL_HANDLE;
HANDLE_T               h_g_cc_digital_style_wgt = NULL_HANDLE;

static HANDLE_T        h_listbox;
static BOOL            b_always_slider_mode = FALSE;
//static BOOL            b_is_done = FALSE;;

static BOOL            b_g_fm_enabled;        /* Fast Mode enabled or disabled */
static UINT32          ui4_fm_last_tick;      /* Fast Mode: Last tick */
static UINT8           ui1_fm_delta_idx;      /* Fast Mode: Delta Index */

BOOL b_is_press_ok_from_check_update = TRUE;
BOOL b_is_read_reset_advertiser_info = FALSE;

#ifdef APP_MENU_DLG_COEXIST
static UINT32          ui4_page_id_need_hide=0;
#endif
static menu_page_tree_event_listener_fct    pf_g_event_listener = NULL;

static INT32 _get_last_focusable_item(
                                        PAGE_TREE_T*        pt_page,
                                        PAGE_TREE_ITEM_T**  ppt_page_item);
static INT32 _item_list_subpage_change_style(PAGE_TREE_ITEM_T* pt_page_item);
static UINT16 _menu_page_tree_get_demo_mode_help_text_id(UINT8  ui1_demo_mode);
#define MAX_ELEM_NUM 50
#define PIC_KEY_APPLY_DELAY     (4000)

static HANDLE_T h_g_font = NULL_HANDLE;

static CHAR s_drrt_name[32];
static CHAR s_drrt_help_txt[256];
static UTF16_T w2s_drrt_help_txt[256];

#ifdef APP_TTS_SUPPORT
static UTF16_T w2s_tts_content[_TTS_CNT_MAX_LEN+1];
static UINT16 ui2_tts_lang = MLM_MENU_LANG_ENG;

static BOOL            b_btn_left_right_zoom = FALSE;

#endif
static UINT8  ui1_system_menu_item_num=0;
static BOOL   b_system_menu_help_tip_move = FALSE;
extern BOOL b_g_select_is_menu_key;

#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
extern UINT32 ui4_page_menu_language_dialog;
extern UINT16 ui2_menu_language_new_idx;
extern UINT16 menu_get_gui_lang_idx(VOID);
#define MLM_MENU_LANG_ENG 0
#define MLM_MENU_LANG_ESL 1
#define MLM_MENU_LANG_FRA 2
#endif
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
extern BOOL _is_one_listbox_mode(
    PAGE_TREE_T* pt_page_tree
);
static INT32 _homebar_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2);

static UINT16   ui2_list_hlt_before_hlt = 0xFF;
static UINT16  g_ui2_list_cnt     = 0;
static BOOL    b_is_page_show     = FALSE;
static BOOL    b_is_subpage_state  = FALSE;
static GL_RECT_T t_lb_rect = {0};

static UINT16   g_aui2_list_listbox_idx[MAX_ELEM_NUM];
static BOOL     b_hot_key_enter;
static HANDLE_T h_listbox_timer = NULL_HANDLE;

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
#if( defined(APP_SUPPORT_PIC_HOT_KEY) )
static VOID _menu_page_tree_listbox_timer_cb(HANDLE_T h_timer, VOID* pv_tag);
static INT32 _menu_page_tree_hot_key_page_proc(HANDLE_T   h_widget,
                                               UINT32     ui4_keycode,
                                               PAGE_TREE_ITEM_T* pt_page_tree_item,
                                               BOOL       *pb_handled);
#endif

static INT32 _menu_page_tree_play_tts(HANDLE_T h_widget, UINT8 ui1_play_mode);
#ifdef APP_TTS_SUPPORT
static INT32 _get_list_items_text(PAGE_TREE_ITEM_T*  pt_page_tree_item, UINT16 ui2_idx, UTF16_T *pw2s_str);
#endif


/*----------------------------------------------------------------------------
 * Name: _increase_delta_idx
 *
 * Description: Fast mode supporting function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static VOID _increase_delta_idx(UINT8*   pui1_fm_delta_idx)
{
    if(  (++(*pui1_fm_delta_idx)) >= 10 )
    {
        *pui1_fm_delta_idx = 9;
    }
}

/*----------------------------------------------------------------------------
 * Name: _get_delta_by_delta_idx
 *
 * Description: Fast mode supporting function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _get_delta_by_delta_idx(UINT8  ui1_fm_delta_idx)
{
    static INT8   aui1_delta_arr[10] = { 1,1,1,2,2,2,4,4,4,8 };

    if(ui1_fm_delta_idx > MENU_PAGE_TREE_MAX_ITEM)
    {
        ui1_fm_delta_idx = MENU_PAGE_TREE_MAX_ITEM;
    }

    return (INT32) aui1_delta_arr[ui1_fm_delta_idx];
}

/*----------------------------------------------------------------------------
 * Name: _get_item_data_by_widget
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _get_item_data_by_widget(
    HANDLE_T           h_widget,
    PAGE_TREE_ITEM_T** ppt_item)
{
    INT32 i4_ret;
    if(h_widget == NULL_HANDLE)
    {
        return MENUR_INV_ARG;
    }


    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_item),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _get_item_data_by_widget
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _get_item_data_by_id(
    PAGE_TREE_T* pt_page_tree,
    UINT16       ui2_item_id,
    PAGE_TREE_ITEM_T** ppt_item)
{
    PAGE_TREE_ITEM_T*   pt_page_item;

    if(pt_page_tree == NULL ||
       ppt_item == NULL)
    {
        return MENUR_INV_ARG;
    }

    DLIST_FOR_EACH(pt_page_item, &pt_page_tree->t_item_list, t_link)
    {
        if(pt_page_item->ui2_item_id == ui2_item_id)
        {
            break;
        }
    }

    if(pt_page_item != NULL)
    {
        *ppt_item = pt_page_item;
    }
    else
    {
        return MENUR_ITEM_NOT_FOUND;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _get_page_data_by_id
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _get_page_data_by_id(
    UINT32         ui4_page_id,
    PAGE_TREE_T**  ppt_page)
{
    MENU_ASSERT(ppt_page != NULL);

    return menu_page_get_data(ui4_page_id, (VOID**)ppt_page);
}

static INT32 _chk_item_enable_for_help_tip(PAGE_TREE_ITEM_T* pt_page_item)
{
    INT32       i4_ret = MENUR_OK;
    PAGE_TREE_ITEM_T *pt_page_item_last = NULL;
    PAGE_TREE_T     *pt_page = NULL;
    HANDLE_T        h_back_bar = NULL_HANDLE;

    if (NULL == pt_page_item)
    {
        return MENUR_OK;
    }

    pt_page = pt_page_item->pt_page;

    if (pt_page->pt_item_focus->b_enabled == TRUE
        && pt_page->pt_item_focus->b_hidden == FALSE
        && (MENU_ITEM_TYPE_SUBPAGE == pt_page->pt_item_focus->t_menuitem.e_item_type
            || MENU_ITEM_TYPE_LIST_SUBPAGE == pt_page->pt_item_focus->t_menuitem.e_item_type
            || MENU_ITEM_TYPE_LIST == pt_page->pt_item_focus->t_menuitem.e_item_type))
    {
        return MENUR_OK;
    }

    _get_last_focusable_item(pt_page, &pt_page_item_last);

    if (pt_page_item_last != NULL
        && pt_page->e_state == PAGE_TREE_STATE_NORMAL
        && menu_help_tip_get_focus() == TRUE)
    {
        pt_page->pt_item_focus = pt_page_item_last;
        menu_help_tip_keytip_set_focus(pt_page->pt_item_focus->h_widget, 0, FALSE);
    }

    if (pt_page_item_last == NULL
        && pt_page->e_state == PAGE_TREE_STATE_NORMAL
        && menu_help_tip_get_focus() == TRUE)
    {
        i4_ret=menu_get_backbar_handle(&h_back_bar);
        MENU_LOG_ON_FAIL(i4_ret);

        menu_help_tip_keytip_set_focus(h_back_bar, 0, FALSE);
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _do_layout
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _do_layout(
    PAGE_TREE_T* pt_page_tree)
{
    INT32              i4_ret=0;
    PAGE_TREE_ITEM_T*   pt_page_item;
    UINT16              ui2_items_per_ipage;
    UINT16              ui2_idx = 0;

    UINT16              ui2_pos = 0;
    UINT16              ui2_ipage = 0;
    GL_RECT_T           t_rect;
    BOOL                b_pic_mode_exist = FALSE;
    UINT16              ui2_visible_item = 0;
    UINT16              ui2_adj_page; /* only visible item should be counted into page */
    HANDLE_T              h_last_shadow_item = NULL_HANDLE;

    if (pt_page_tree->i2_offset < 0)
    {
        pt_page_tree->i2_offset = 0;

    }

    if (menu_get_nav_go())
    {
        pt_page_tree->i2_offset = 0;

        menu_set_nav_go(FALSE);
    }


    ui2_items_per_ipage = pt_page_tree->ui2_items_per_ipage;

    /* recount the index for each item */
    DLIST_FOR_EACH(pt_page_item, &pt_page_tree->t_item_list, t_link)
    {
        pt_page_item->ui2_item_idx = ui2_idx;

        if(pt_page_item->b_hidden == FALSE)
        {
            ui2_idx ++;
        }
    }

    if (pt_page_tree->pt_item_focus == NULL || ui2_idx <= pt_page_tree->ui2_items_per_ipage)
    {

        pt_page_tree->i2_offset = 0;

    }
    else if (pt_page_tree->i2_offset > ui2_idx - pt_page_tree->ui2_items_per_ipage)
    {

        pt_page_tree->i2_offset = ui2_idx - pt_page_tree->ui2_items_per_ipage;

    }

//    i2_offset = pt_page_tree->pt_item_focus->ui2_item_idx - pt_page_tree->ui2_items_per_ipage + 1;
//    i2_offset = i2_offset >= 0 ? i2_offset : 0;


    DLIST_FOR_EACH(pt_page_item, &pt_page_tree->t_item_list, t_link)
    {
        if (menu_is_picture_mode_item(pt_page_item->t_menuitem.ui2_msgid_title))
        {
            b_pic_mode_exist = TRUE;
        }
        if (pt_page_item->ui2_item_idx >= pt_page_tree->i2_offset
            && pt_page_item->ui2_item_idx < pt_page_tree->ui2_items_per_ipage
                + pt_page_tree->i2_offset)
        {
            if (pt_page_item->b_hidden == FALSE)
            {
                SET_RECT_BY_SIZE(&t_rect,
                             0,
                             MENU_ITEM_V_HEIGHT * ui2_visible_item,
                             MENU_ITEM_V_WIDE,
                             MENU_ITEM_V_HEIGHT);
                i4_ret=c_wgl_move(pt_page_item->h_widget, &t_rect, WGL_NO_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=c_wgl_set_visibility(pt_page_item->h_widget,
                                            WGL_SW_NORMAL);
                MENU_LOG_ON_FAIL(i4_ret);

                ui2_visible_item += 1;
            }
        }
        else
        {
            i4_ret=c_wgl_set_visibility(pt_page_item->h_widget,
                            WGL_SW_HIDE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }


    /* if in list box state, not adjust last shadow position */
    if (PAGE_TREE_STATE_LISTBOX != pt_page_tree->e_state)
    {
        /*Adjust last shadow position*/
        t_rect.i4_left = CONTENT_X;
        t_rect.i4_right = CONTENT_X + CONTENT_H;
        t_rect.i4_top = MENU_ITEM_V_HEIGHT * (ui2_visible_item)+ CONTENT_Y + 10;
        t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;
        if(pt_page_tree->ui2_msgid_title == MLM_MENU_KEY_MAIN_MENU_SYSTEM)
        {
            ui1_system_menu_item_num = ui2_visible_item;
        }
        menu_pm_get_last_shadow_item(&h_last_shadow_item);
        i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);

        t_rect.i4_left = CONTENT_X;
        t_rect.i4_right = CONTENT_W;
        t_rect.i4_top = CONTENT_Y - 10;
        t_rect.i4_bottom = MENU_ITEM_V_HEIGHT * ui2_visible_item + t_rect.i4_top;
        menu_list_arrow_move(&t_rect, FALSE);
        if (pt_page_tree->i2_offset == 0) {
            menu_list_up_arrow_show(FALSE, TRUE);
            if (b_pic_mode_exist == TRUE)
            {
                if (b_pic_mode_exist == TRUE && a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI)
                {
                    menu_doly_vision_logo_show_repaint(TRUE, FALSE);

                }
            }
        }
        else
        {
            menu_doly_vision_logo_show_repaint(FALSE, FALSE);
            menu_list_up_arrow_show(TRUE, TRUE);
        }
        if (pt_page_tree->i2_offset >= ui2_idx - pt_page_tree->ui2_items_per_ipage)
        {
            menu_list_down_arrow_show(FALSE, TRUE);
        }
        else
        {
            menu_list_down_arrow_show(TRUE, TRUE);
        }
    }

    /* some item may be invisible, do not count it into total page.*/
    ui2_adj_page = ui2_visible_item%ui2_items_per_ipage;
    pt_page_tree->ui2_ipage_num = ui2_visible_item/ui2_items_per_ipage;

    if(ui2_adj_page != 0)
    {
        pt_page_tree->ui2_ipage_num = (UINT16)(pt_page_tree->ui2_ipage_num + 1);
    }

    if(pf_g_event_listener != NULL)
    {
        pf_g_event_listener(pt_page_tree->ui4_page_id,
                            MENU_PAGE_TREE_EVENT_LAYOUT_UPDATE,
                            (VOID*)NULL);
    }

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _chg_item_list
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _chg_item_list(HANDLE_T h_widget,
                         BOOL b_repaint_item)
{
    INT32  i4_ret;
    UINT16 ui2_idx,ui2_elem_num;
    HANDLE_T h_img_left,h_img_right;
    WGL_LB_ITEM_IMG_SUIT_T    t_img_suit_left,t_img_suit_right;
    PAGE_TREE_ITEM_T* pt_page_tree_item;

    if(NULL_HANDLE==h_widget)
    {
       return MENUR_OK;
    }

    i4_ret =_get_item_data_by_widget(h_widget, &pt_page_tree_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_widget,
          WGL_CMD_LB_GET_ELEM_NUM,
          WGL_PACK(&ui2_elem_num),
          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if((pt_page_tree_item->b_enabled) && (pt_page_tree_item->t_menuitem.ui2_msgid_title != MLM_MENU_KEY_AUD_EQ_MODE_INDENTATION))
    {
        h_img_left = h_g_menu_img_list_item_leftarrow;
        h_img_right = h_g_menu_img_list_item_rightarrow;
    }
    else
    {
        h_img_left = NULL_HANDLE;
        h_img_right = NULL_HANDLE;
    }
    /*show image*/
    c_memset(&t_img_suit_left, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    t_img_suit_left.h_normal                      = NULL_HANDLE;
    t_img_suit_left.h_disable                     = NULL_HANDLE;
    t_img_suit_left.h_highlight                   = h_img_left;
    t_img_suit_left.h_highlight_unfocus           = NULL_HANDLE;
    t_img_suit_left.h_pushed                      = NULL_HANDLE;
    t_img_suit_left.h_selected                    = NULL_HANDLE;
    t_img_suit_left.h_selected_disable            = NULL_HANDLE;
    t_img_suit_left.h_selected_highlight          = h_img_left;
    t_img_suit_left.h_selected_highlight_unfocus  = NULL_HANDLE;
    t_img_suit_left.h_selected_pushed             = NULL_HANDLE;


    c_memset(&t_img_suit_right, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    t_img_suit_right.h_normal                      = NULL_HANDLE;
    t_img_suit_right.h_disable                     = NULL_HANDLE;
    t_img_suit_right.h_highlight                   = h_img_right;
    t_img_suit_right.h_highlight_unfocus           = NULL_HANDLE;
    t_img_suit_right.h_pushed                      = NULL_HANDLE;
    t_img_suit_right.h_selected                    = NULL_HANDLE;
    t_img_suit_right.h_selected_disable            = NULL_HANDLE;
    t_img_suit_right.h_selected_highlight          = h_img_right;
    t_img_suit_right.h_selected_highlight_unfocus  = NULL_HANDLE;
    t_img_suit_right.h_selected_pushed             = NULL_HANDLE;

    for(ui2_idx =0; ui2_idx<ui2_elem_num; ui2_idx++)
    {
        i4_ret = c_wgl_do_cmd(pt_page_tree_item->h_widget,
              WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
              WGL_PACK_2(ui2_idx, 0),
              WGL_PACK(&t_img_suit_left));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_page_tree_item->h_widget,
              WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
              WGL_PACK_2(ui2_idx, 2),
              WGL_PACK(&t_img_suit_right));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    _item_list_subpage_change_style(pt_page_tree_item);

    if(b_repaint_item)
    {
        i4_ret = c_wgl_repaint(h_widget,NULL,TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _item_def_proc_fct_cursor_up
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _show_elem_help_tips (UINT16 ui2_item_desc,
                                   UINT16 ui2_elem_desc_first,
                                   UINT16 ui2_hlt,
                                   BOOL b_desc)
{
    INT32 i4_ret = WGLR_OK;

    if (b_desc)
    {
        MENU_DEBUG_HELP( DBG_LOG_PRINT(("[MENU][TREE][HELP]{%s,%d} ui2_item_desc:%d, ui2_elem_desc_first:%d, ui2_hlt:%d \n",
            __FUNCTION__, __LINE__, ui2_item_desc, ui2_elem_desc_first, ui2_hlt )); );

        if (0 == ui2_elem_desc_first)
        {
            i4_ret = menu_set_and_show_help_tip(MENU_TEXT(ui2_item_desc));
        }
        else
        {
            i4_ret = menu_set_and_show_help_tip(MENU_TEXT(ui2_elem_desc_first + ui2_hlt));
        }
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

extern UINT32 a_get_5351_pin_state(VOID);

static INT32 _reset_page_cust_process(PAGE_TREE_ITEM_T* pt_page_tree_item, UINT32 *pui4_page_id, MENU_PAGE_HINT_T *pt_hint)
{
    DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%s,%d} \n", __FILE__, __FUNCTION__, __LINE__  )); );

    // Check para ...
    if( pt_page_tree_item == NULL )
    {
        DBG_LOG_PRINT(("[MENU][TREE]{%s,%s,%d} Error: pt_page_tree_item == NULL\n", __FILE__, __FUNCTION__, __LINE__  ));
        return MENUR_INV_ARG;
    }

    if( pui4_page_id == NULL )
    {
        DBG_LOG_PRINT(("[MENU][TREE]{%s,%s,%d} Error: pui4_page_id == NULL\n", __FILE__, __FUNCTION__, __LINE__  ));
        return MENUR_INV_ARG;
    }

    if( pt_hint == NULL )
    {
        DBG_LOG_PRINT(("[MENU][TREE]{%s,%s,%d} Error: pt_hint == NULL\n", __FILE__, __FUNCTION__, __LINE__  ));
        return MENUR_INV_ARG;
    }

    if (NULL != pt_hint)
    {
        c_memset(pt_hint, 0, sizeof(MENU_PAGE_HINT_T));
    }


    UTF16_T w2s_str[APP_CFG_MAX_PWD_LEN+1] = {0};

    c_uc_ps_to_w2s(ACFG_PASSWORD_DEF, w2s_str, APP_CFG_MAX_PWD_LEN);

    BOOL b_chk_password_pass = FALSE;

    INT32 i32_rtn = a_cfg_chk_password(w2s_str, &b_chk_password_pass);
    if( i32_rtn != APP_CFGR_OK )
    {
        DBG_LOG_PRINT(("[MENU][TREE]{%s,%s,%d} Error: a_cfg_chk_password() => %d\n", __FILE__, __FUNCTION__, __LINE__, i32_rtn  ));
        b_chk_password_pass = FALSE;
    }
    DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} => b_chk_password_pass:%d, \n", __FUNCTION__, __LINE__, b_chk_password_pass  )); );


    BOOL b_sys_pin_passed = FALSE;

    i32_rtn = a_cfg_custom_get_sys_pin_passed(&b_sys_pin_passed);
    if( i32_rtn != APP_CFGR_OK )
    {
        DBG_LOG_PRINT(("[MENU][TREE]{%s,%s,%d} Error: a_cfg_custom_get_sys_pin_passed() => %d\n", __FILE__, __FUNCTION__, __LINE__, i32_rtn  ));
        b_sys_pin_passed = FALSE;
    }
    DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} => b_sys_pin_passed:%d \n", __FUNCTION__, __LINE__, b_sys_pin_passed )); );


    DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} t_menuitem.ui2_msgid_title:%d\n", __FUNCTION__, __LINE__, pt_page_tree_item->t_menuitem.ui2_msgid_title )); );

    if( (MLM_MENU_KEY_CHG_PWD == pt_page_tree_item->t_menuitem.ui2_msgid_title)
      ||(MLM_MENU_KEY_PAR_CTR == pt_page_tree_item->t_menuitem.ui2_msgid_title)
      )
    {
        UINT32 u32_5351_pin_state = a_get_5351_pin_state();

        DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} b_chk_password_pass:%d, u32_5351_pin_state:%d\n", __FUNCTION__, __LINE__, b_chk_password_pass, u32_5351_pin_state )); );

        if( (b_chk_password_pass) || (u32_5351_pin_state == 2) )
        {
            DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} goto menu_page_chg_pwd \n",  __FUNCTION__, __LINE__  ));

            /* Change PIN Require page */
            if( (NULL != pt_hint) && (MLM_MENU_KEY_CHG_PWD != pt_page_tree_item->t_menuitem.ui2_msgid_title) )
            {
                DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} change to menu_page_chg_pwd \n", __FUNCTION__, __LINE__  )); );
                pt_hint->e_hint_type = MENU_PAGE_HT_CUSTOM;
                pt_hint->u.pv_custom_hint = (VOID*)*pui4_page_id;
            }

            *pui4_page_id = ui4_g_menu_page_chg_pwd;
        }
        else
        {
            DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} b_sys_pin_passed:%d \n", __FUNCTION__, __LINE__, b_sys_pin_passed )); );

            if( b_sys_pin_passed)
            {
                DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} No need input again \n", __FUNCTION__, __LINE__  ));
                /*If have input sys pin, no need input again until next power session*/
                return MENUR_OK;
            }

            DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} goto menu_page_input_sys_pin \n",  __FUNCTION__, __LINE__  ));

            /* Skip PIN Require page */
            if (NULL != pt_hint)
            {
                pt_hint->e_hint_type = MENU_PAGE_HT_CUSTOM;
                pt_hint->u.pv_custom_hint = (VOID*)*pui4_page_id;
            }

            *pui4_page_id = ui4_g_page_input_sys_pin;
        }
    }
    else if (MLM_MENU_KEY_RESET_TV_TO_FACTORY_SET == pt_page_tree_item->t_menuitem.ui2_msgid_title)
    {
        DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} b_sys_pin_passed:%d, b_chk_password_pass:%d\n", __FUNCTION__, __LINE__, b_sys_pin_passed, b_chk_password_pass )); );

        //if (a_cfg_custom_get_sys_pin_passed(&b_pass) == APP_CFGR_OK && b_pass)
        if( b_sys_pin_passed )
        {
            DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} No need input again \n", __FUNCTION__, __LINE__  ));
            /*If have input sys pin, no need input again until next power session*/
            return MENUR_OK;
        }
        //else if ((a_cfg_chk_password(w2s_str, &b_pass) == APP_CFGR_OK) && !b_pass)
        else if( !b_chk_password_pass )
        {
            DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} goto menu_page_input_sys_pin \n",  __FUNCTION__, __LINE__  ));

            if (NULL != pt_hint)
            {
                pt_hint->e_hint_type = MENU_PAGE_HT_CUSTOM;
                pt_hint->u.pv_custom_hint = (VOID*)*pui4_page_id;
            }

            *pui4_page_id = ui4_g_page_input_sys_pin;
            //Fix Coverity ID:4491011 Unchecked return value
            i32_rtn = menu_set_page_hide(TRUE);
            if( i32_rtn != MENUR_OK )
            {
                DBG_LOG_PRINT(("[MENU][TREE]{%s,%s,%d} Error: a_cfg_custom_get_sys_pin_passed() => %d\n", __FILE__, __FUNCTION__, __LINE__, i32_rtn  ));
                b_sys_pin_passed = FALSE;
            }
        }
    }
    else
    {
        /* Do nothing */
        DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%s,%d} \n", __FILE__, __FUNCTION__, __LINE__  )); );
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _item_def_proc_fct_cursor_up
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_def_proc_fct_cursor_up(PAGE_TREE_T* pt_page_tree,
                                      PAGE_TREE_ITEM_T* pt_page_tree_item)
{
    INT32 i4_ret=0;
    PAGE_TREE_ITEM_T* pt_page_tree_item_next=NULL;

    MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    pt_page_tree_item_next = pt_page_tree_item;

    do
    {
        pt_page_tree_item_next = DLIST_PREV(pt_page_tree_item_next, t_link);
        if(pt_page_tree_item_next == NULL)
        {
#if 0
            pt_page_tree_item_next = DLIST_TAIL(&pt_page_tree->t_item_list);
#endif      /*for back bar*/
            break;
        }

        if(pt_page_tree_item_next == pt_page_tree_item)
        {
            break;
        }
    } while(pt_page_tree_item_next->b_hidden == TRUE  ||
            pt_page_tree_item_next->b_enabled == FALSE);

    if(NULL==pt_page_tree_item_next)
    {
        i4_ret=menu_set_focus_on_backbar(TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

 #if 1/*MVP-4620*/
        UINT32 ui4_cnt_page = 0;
        INT32 i4_ret = menu_nav_get_crnt_page(&ui4_cnt_page);
        if((ui4_cnt_page == ui4_g_menu_page_aud) && (i4_ret == MENUR_OK))
        {
            pt_page_tree->i2_offset = 0;
            i4_ret=_do_layout(pt_page_tree);

            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_pm_repaint();
            MENU_LOG_ON_FAIL(i4_ret);
        }
#endif
        return WGLR_OK;
    }

    if(pt_page_tree_item == pt_page_tree_item_next)
    {
        return WGLR_OK;
    }

    pt_page_tree->pt_item_focus = pt_page_tree_item_next;

    MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} ui2_item_id:%d, ui2_item_idx:%d, h_widget:0x%X \n",
        __FUNCTION__, __LINE__, pt_page_tree->pt_item_focus->ui2_item_id,
        pt_page_tree->pt_item_focus->ui2_item_idx,
        pt_page_tree->pt_item_focus->h_widget,
        pt_page_tree->pt_item_focus->t_menuitem.ui2_msgid_title
        )); );
    MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} ui2_msgid_title:%d \n",
        __FUNCTION__, __LINE__, pt_page_tree->pt_item_focus->t_menuitem.ui2_msgid_title
        )); );

    if(pt_page_tree_item_next->ui2_item_idx < pt_page_tree->i2_offset)
    {
        pt_page_tree->i2_offset = pt_page_tree_item_next->ui2_item_idx;

        i4_ret=_do_layout(pt_page_tree);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=c_wgl_set_focus(pt_page_tree_item_next->h_widget,
                        WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if(pt_page_tree_item->ui2_item_idx != (UINT16)(pt_page_tree_item_next->ui2_item_idx+1) &&
            pt_page_tree_item->ui2_item_idx != (UINT16)(pt_page_tree_item_next->ui2_item_idx-1))
    {
        i4_ret=c_wgl_set_focus(pt_page_tree_item_next->h_widget,
                        WGL_SYNC_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        GL_RECT_T   t_rect_1;
        GL_RECT_T   t_rect_2;
        GL_RECT_T   t_rect_union;

        i4_ret=c_wgl_set_focus(pt_page_tree_item_next->h_widget,
                        WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=c_wgl_get_coords(pt_page_tree_item->h_widget,
                         WGL_COORDS_PARENT,
                         &t_rect_1);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=c_wgl_get_coords(pt_page_tree_item_next->h_widget,
                         WGL_COORDS_PARENT,
                         &t_rect_2);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=c_wgl_rect_union(&t_rect_union, &t_rect_1, &t_rect_2);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=c_wgl_repaint(pt_page_tree->h_cnt_frm,
                      &t_rect_union,
                      TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return WGLR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _item_def_proc_fct_cursor_down
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_def_proc_fct_cursor_down(PAGE_TREE_T*      pt_page_tree,
                                            PAGE_TREE_ITEM_T* pt_page_tree_item)
{
    PAGE_TREE_ITEM_T* pt_page_tree_item_next = NULL;

    pt_page_tree_item_next = pt_page_tree_item;
    DBG_INFO(("[%s %d]\n",__FUNCTION__,__LINE__));
    MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    do
    {
        pt_page_tree_item_next = DLIST_NEXT(pt_page_tree_item_next, t_link);
        if(pt_page_tree_item_next == NULL || pt_page_tree_item_next == pt_page_tree_item)
        {
            return WGLR_OK;
        }
    } while(pt_page_tree_item_next->b_hidden  == TRUE  ||
            pt_page_tree_item_next->b_enabled == FALSE);

    pt_page_tree->pt_item_focus = pt_page_tree_item_next;

    MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} ui2_item_id:%d, ui2_item_idx:%d, h_widget:0x%X \n",
        __FUNCTION__, __LINE__, pt_page_tree->pt_item_focus->ui2_item_id,
        pt_page_tree->pt_item_focus->ui2_item_idx,
        pt_page_tree->pt_item_focus->h_widget,
        pt_page_tree->pt_item_focus->t_menuitem.ui2_msgid_title
        )); );
    MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} ui2_msgid_title:%d \n",
        __FUNCTION__, __LINE__, pt_page_tree->pt_item_focus->t_menuitem.ui2_msgid_title
        )); );

    if(pt_page_tree_item_next->ui2_item_idx >= pt_page_tree->i2_offset + _ITEMS_PER_IPAGE)
    {
        pt_page_tree->i2_offset = pt_page_tree_item_next->ui2_item_idx - _ITEMS_PER_IPAGE + 1;

        MENU_LOG_ON_FAIL(_do_layout(pt_page_tree));
        MENU_LOG_ON_FAIL(c_wgl_set_focus(pt_page_tree_item_next->h_widget,
                                         WGL_NO_AUTO_REPAINT));
        menu_pm_repaint();
    }
    else
    {
        GL_RECT_T   t_rect_1;
        GL_RECT_T   t_rect_2;
        GL_RECT_T   t_rect_union;

        MENU_LOG_ON_FAIL(c_wgl_set_focus(pt_page_tree_item_next->h_widget,
                                         WGL_NO_AUTO_REPAINT));

        MENU_LOG_ON_FAIL(c_wgl_get_coords(pt_page_tree_item->h_widget,
                                          WGL_COORDS_PARENT,
                                          &t_rect_1));

        MENU_LOG_ON_FAIL(c_wgl_get_coords(pt_page_tree_item_next->h_widget,
                                          WGL_COORDS_PARENT,
                                          &t_rect_2));

        MENU_LOG_ON_FAIL(c_wgl_rect_union(&t_rect_union, &t_rect_1, &t_rect_2));

        MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_tree->h_cnt_frm,
                                       &t_rect_union,
                                       TRUE));
    }

    return WGLR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _item_def_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_def_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32   i4_ret=0;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            PAGE_TREE_ITEM_T* pt_page_tree_item;

            i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
            MENU_LOG_ON_FAIL(i4_ret);

            _menu_page_tree_play_tts(h_widget, _MENU_TREE_TTS_PLAY_TITLE_AND_VAL);

            if(pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_SLIDER)
            {
                i4_ret=menu_hide_help_tip();
                MENU_LOG_ON_FAIL(i4_ret);
                return WGLR_OK;
            }

            if (MLM_MENU_KEY_OP_VCHIP == pt_page_tree_item->t_menuitem.ui2_msgid_title)
            {
                CHAR s_mlm_str[128] = {0};

                c_memset(s_drrt_name, 0, sizeof(s_drrt_name));
                c_memset(s_drrt_help_txt, 0, sizeof(s_drrt_help_txt));
                c_memset(w2s_drrt_help_txt, 0, sizeof(w2s_drrt_help_txt));

                c_uc_w2s_to_ps(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_PARENT_OP_VCHIP_NEW), s_mlm_str, 127);
                c_uc_w2s_to_ps(menu_atsc_drrt_get_system_name(), s_drrt_name, 31);

                c_sprintf(s_drrt_help_txt, s_mlm_str, s_drrt_name);
                c_uc_ps_to_w2s(s_drrt_help_txt, w2s_drrt_help_txt, c_strlen(s_drrt_help_txt));

                i4_ret=menu_set_and_show_help_tip(w2s_drrt_help_txt);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if((pt_page_tree_item->pt_page->e_state != PAGE_TREE_STATE_SLIDER) && (!b_is_page_show))
            {
#if 0
                if(pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_POWER_MODE)
                {
                    GL_RECT_T           t_rect;
                    HANDLE_T            h_last_shadow_item = NULL_HANDLE;
                    t_rect.i4_left = CONTENT_X;
                    t_rect.i4_right = CONTENT_X + CONTENT_H+20;
                    t_rect.i4_top = MENU_ITEM_V_HEIGHT * (ui1_system_menu_item_num)+ CONTENT_Y-25;
                    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;
                    DBG_INFO(("%s_%d \n",__FUNCTION__,__LINE__));
                    menu_pm_get_last_shadow_item(&h_last_shadow_item);
                    i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
                    MENU_LOG_ON_FAIL(i4_ret);
                    i4_ret=c_wgl_repaint(h_last_shadow_item, NULL, TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    b_system_menu_help_tip_move = TRUE;
                }
                else
#endif
                if((b_system_menu_help_tip_move)&&(pt_page_tree_item->pt_page->ui2_msgid_title == MLM_MENU_KEY_MAIN_MENU_SYSTEM))
                {
                    GL_RECT_T           t_rect;
                    HANDLE_T            h_last_shadow_item = NULL_HANDLE;
                    t_rect.i4_left = CONTENT_X;
                    t_rect.i4_right = CONTENT_X + CONTENT_H;
                    t_rect.i4_top = MENU_ITEM_V_HEIGHT * (ui1_system_menu_item_num)+ CONTENT_Y;
                    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;
                    DBG_INFO(("%s_%d \n",__FUNCTION__,__LINE__));
                    menu_pm_get_last_shadow_item(&h_last_shadow_item);

                    i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    i4_ret=c_wgl_repaint(h_last_shadow_item, NULL, TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
                    MENU_LOG_ON_FAIL(i4_ret);
                    i4_ret=c_wgl_repaint(h_last_shadow_item, NULL, TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    b_system_menu_help_tip_move = FALSE;
                }
                i4_ret=menu_set_and_show_help_tip(MENU_TEXT(pt_page_tree_item->t_menuitem.ui2_msgid_desc));
                MENU_LOG_ON_FAIL(i4_ret);
            }
            b_is_page_show = FALSE;

            return WGLR_OK;
        }
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            INT32        i4_ret;
            PAGE_TREE_ITEM_T* pt_page_tree_item;
            PAGE_TREE_T* pt_page_tree;

            MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
                __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

            i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
            MENU_LOG_ON_FAIL(i4_ret);

            pt_page_tree = pt_page_tree_item->pt_page;

            switch (ui4_keycode)
            {
                case BTN_CURSOR_UP:
                    i4_ret = _item_def_proc_fct_cursor_up(pt_page_tree,
                                                          pt_page_tree_item);
                    MENU_LOG_ON_FAIL(i4_ret);
                    return WGLR_OK;
                case BTN_CURSOR_DOWN:
                    i4_ret = _item_def_proc_fct_cursor_down(pt_page_tree,
                                                            pt_page_tree_item);
                    MENU_LOG_ON_FAIL(i4_ret);
                    return WGLR_OK;
                case BTN_SELECT:
                    b_g_select_is_menu_key = FALSE;
                    break;

                case BTN_CURSOR_LEFT:
                #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                    return MENUR_OK;
                #endif
                case BTN_PREV_PRG:
                case BTN_RETURN:
                    pt_page_tree->pt_item_focus = DLIST_HEAD(&pt_page_tree->t_item_list);
                    pt_page_tree->i2_offset = 0;

                    i4_ret=_do_layout(pt_page_tree);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=menu_nav_back();
                    MENU_LOG_ON_FAIL(i4_ret);
                    return WGLR_OK;
                default:
                    break;
            }

        }
        default:
            break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _cvt_menu_idx_2_listbox_idx
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static UINT16 _cvt_menu_idx_2_listbox_idx (UINT16 ui2_idx)
{
    UINT16 ui2_i = 0;
    UINT16 ui2_ret = (UINT16) -1;

#if NEVER    //CID:4491244
    if (ui2_i >= MAX_ELEM_NUM)
    {
        return ui2_ret;
    }
#endif

    while ((g_aui2_list_listbox_idx[ui2_i] != (UINT16)-1) && (ui2_i < MAX_ELEM_NUM))
    {
        if (ui2_idx == g_aui2_list_listbox_idx[ui2_i])
        {
            return ui2_i;
        }
        ui2_i ++;
    }
    return ui2_ret;
}

/*----------------------------------------------------------------------------
 * Name: _cvt_listbox_idx_2_menu_idx
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static UINT16 _cvt_listbox_idx_2_menu_idx (UINT16 ui2_idx)
{
    UINT16 ui2_ret = (UINT16) -1;
    if (ui2_idx < MAX_ELEM_NUM)
    {
        return g_aui2_list_listbox_idx[ui2_idx];
    }
    return ui2_ret;
}

/*----------------------------------------------------------------------------
 * Name: _insert_list_box_items
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _insert_list_box_items(PAGE_TREE_ITEM_T*  pt_page_tree_item)
{
    UINT16  ui2_i           = 0;
    UINT16  ui2_elem_num    = 0;
    UINT16  ui2_start_idx   = 0;
    UINT16  ui2_next_idx    = 0;
    UINT16  aui2_list_item_index[MAX_ELEM_NUM];
    UTF16_T w2s_str[64];
    UINT16  ui2_msgid_elem_last = 0;
    UINT16  ui2_msgid_elem_first = 0;
    GL_RECT_T           t_rect;
    HANDLE_T    h_last_shadow_item = NULL_HANDLE;
    HANDLE_T    h_energy_start_icon = NULL_HANDLE;
    INT32       i4_arrow_hight = 0;
    INT32       i4_ret= 0;
    ISO_639_LANG_T  s639_lang;

    g_ui2_list_cnt     = 0;
    if (NULL == pt_page_tree_item)
    {
        return WGLR_INV_ARG;
    }

    c_memset(aui2_list_item_index, (UINT8)-1, sizeof (aui2_list_item_index));
    c_memset(g_aui2_list_listbox_idx, (UINT8)-1, sizeof (g_aui2_list_listbox_idx));
    MENU_LOG_ON_FAIL( c_wgl_do_cmd(h_listbox,
                                   WGL_CMD_LB_DEL_ALL,
                                   NULL, NULL));

    if ( (NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_prev_idx) ||
         (NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx) )
    {
        ui2_elem_num = pt_page_tree_item->t_menuitem.u.t_list.ui2_elem_num;
        if ((0 != pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_last) &&
            (0 != pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first))
        {
            ui2_msgid_elem_last = pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_last;
            ui2_msgid_elem_first= pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first;
            ui2_elem_num = (UINT16)((ui2_msgid_elem_last - ui2_msgid_elem_first) + 1);
        }

        if(menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))
        {
            ui2_elem_num = get_cust_picture_mode_num();
        }
        DBG_LOG_PRINT(("[%s,%d] list item num = %d \n",__FUNCTION__,__LINE__,ui2_elem_num));

        MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                      WGL_CMD_LB_SET_ELEM_NUM,
                                      WGL_PACK(ui2_elem_num),
                                      NULL));

        /* Show the listbox and insert the items to the listbox */
        for(ui2_i=0; ui2_i<ui2_elem_num;ui2_i++)
        {
            /*Klockwork issues */
            if (ui2_i >= MAX_ELEM_NUM -1)
            {
                break;
            }
            if(pt_page_tree_item->t_menuitem.u.t_list.pf_get_text != NULL)
            {
                pt_page_tree_item->t_menuitem.u.t_list.pf_get_text(ui2_i, w2s_str, 64);
            }
            else
            {
                c_uc_w2s_strcpy(w2s_str,
                                MENU_TEXT(pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first + ui2_i));
            }

            MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                          WGL_CMD_LB_SET_ITEM_TEXT,
                                          WGL_PACK_2 (ui2_i, 0),
                                          w2s_str));

            g_aui2_list_listbox_idx[ui2_i] = ui2_i;
            g_ui2_list_cnt = ui2_i;
        }
    }
    else /*Issue Maybe need needn't*/
    {
        UINT16  ui2_comp = 0;
        UINT16  ui2_first = 0;
        UINT16  ui2_sort_idx = 0;
        BOOL    b_is_model_name = FALSE;

        b_is_model_name = ( // for model name
                             pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx  != NULL &&
                             pt_page_tree_item->t_menuitem.u.t_list.pf_get_text != NULL &&
                             pt_page_tree_item->t_menuitem.u.t_list.pf_prev_idx != NULL &&
                             pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx != NULL &&
                             0xFFFF == pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_last &&
                             0 == pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first) ?
                             TRUE : FALSE;

        if (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx)
        {
            ui2_start_idx = pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx ();
        }
        else
        {
            ui2_start_idx = 0;
        }

        if(pt_page_tree_item->t_menuitem.u.t_list.pf_get_text == NULL||
           b_is_model_name)
        {
            /* store index for list items */
            aui2_list_item_index[g_ui2_list_cnt] = ui2_start_idx;
            g_ui2_list_cnt ++;

            ui2_next_idx = pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx();
            while ((ui2_start_idx != ui2_next_idx)
                   && (g_ui2_list_cnt < MAX_ELEM_NUM))
            {
                aui2_list_item_index[g_ui2_list_cnt] = ui2_next_idx;
                ui2_next_idx = pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx();
                g_ui2_list_cnt ++;
            }

            /* sort item index */
            ui2_comp = aui2_list_item_index[0];
            for (ui2_i = 0; ui2_i < g_ui2_list_cnt; ui2_i++ )
            {
                /*Klockwork issues */
                if (ui2_i >= MAX_ELEM_NUM-1)
                {
                    break;
                }
                if (ui2_comp > aui2_list_item_index [ui2_i])
                {
                    ui2_comp = aui2_list_item_index [ui2_i];
                    ui2_first = ui2_i;
                }
            }
            /* storing sorted index */
            if (0 != ui2_first)
            {
                for (ui2_i = 0; ui2_i < g_ui2_list_cnt; ui2_i ++)
                {
                    ui2_sort_idx = (ui2_i + ui2_first) % g_ui2_list_cnt;
                    g_aui2_list_listbox_idx[ui2_i] = aui2_list_item_index[ui2_sort_idx];
                }
            }
            else
            {
                c_memcpy(g_aui2_list_listbox_idx,
                         aui2_list_item_index,
                         sizeof (g_aui2_list_listbox_idx));
            }
            /* Set list items count */
            MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                          WGL_CMD_LB_SET_ELEM_NUM,
                                          WGL_PACK(g_ui2_list_cnt),
                                          NULL));

            /* insert items into list */
            for(ui2_i=0; ui2_i < g_ui2_list_cnt; ui2_i++)
            {
                if(pt_page_tree_item->t_menuitem.u.t_list.pf_get_text != NULL)
                {
                    pt_page_tree_item->t_menuitem.u.t_list.pf_get_text(g_aui2_list_listbox_idx[ui2_i], w2s_str, 64);
                }
                else
                {
                    c_uc_w2s_strcpy(w2s_str,
                                    MENU_TEXT(pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first + g_aui2_list_listbox_idx[ui2_i]));
                }

                MENU_LOG_ON_FAIL( c_wgl_do_cmd(h_listbox,
                                               WGL_CMD_LB_SET_ITEM_TEXT,
                                               WGL_PACK_2 (ui2_i, 0),
                                               w2s_str));
            }
        }
        else
        {
            WGL_LB_ITEM_T                at_items[1];

            for(ui2_i=0; ui2_i < MAX_ELEM_NUM; ui2_i++)
            {
                c_memset(&w2s_str, 0, sizeof(w2s_str));
                pt_page_tree_item->t_menuitem.u.t_list.pf_get_text(ui2_i, w2s_str, 64);
                if(c_uc_w2s_strlen(w2s_str) != 0)
                {
                    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
                    at_items[0].data.pw2s_text = w2s_str;
                    MENU_LOG_ON_FAIL( c_wgl_do_cmd(h_listbox,
                                                   WGL_CMD_LB_APPEND_ELEM,
                                                   at_items,
                                                   NULL ));

                    g_ui2_list_cnt++;
                    g_aui2_list_listbox_idx[ui2_i] = ui2_i;
                }
                else
                {
                    break;
                }
            }
        }

        ui2_elem_num = g_ui2_list_cnt;
    }

    //if (pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_VID_PIC_MODE_ITEM)
    {
        if (ui2_elem_num > 10)
        {
            t_rect.i4_left = t_lb_rect.i4_left;
            t_rect.i4_top = t_lb_rect.i4_top + 12;
            t_rect.i4_right = t_lb_rect.i4_right;
            t_rect.i4_bottom = t_lb_rect.i4_bottom + 12;

            i4_arrow_hight = 12;
        }
        else
        {
            t_rect.i4_left = t_lb_rect.i4_left;
            t_rect.i4_top = t_lb_rect.i4_top;
            t_rect.i4_right = t_lb_rect.i4_right;
            t_rect.i4_bottom = t_lb_rect.i4_bottom;

            i4_arrow_hight = 0;
        }

        c_wgl_move(h_listbox, &t_rect, FALSE);

        // menu_list_arrow_state_update(h_listbox, BTN_INVALID, TRUE);
    }

    /*Adjust last shadow position*/
    if(ui2_elem_num >= 10)
    {
        ui2_elem_num = 10;
        t_rect.i4_left = CONTENT_X;
        t_rect.i4_right = CONTENT_W;
        t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui2_elem_num + FRAME_Y + CONTENT_Y + 5;
        t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;
        menu_list_arrow_move(&t_lb_rect, FALSE);
    }
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui2_elem_num + FRAME_Y + CONTENT_Y + i4_arrow_hight + 5;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    menu_pm_get_last_shadow_item(&h_last_shadow_item);

    MENU_LOG_ON_FAIL(c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT));

    menu_doly_vision_logo_show(FALSE);

    if ( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title) )
    {
        BOOL        b_visible = FALSE;
        c_wgl_get_visibility(h_listbox, &b_visible);
        menu_pm_get_energy_start_icon_handle(&h_energy_start_icon);
        t_rect.i4_left = CONTENT_X + 65;
        t_rect.i4_right = t_rect.i4_left + 90;
        t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui2_elem_num + FRAME_Y + CONTENT_Y + i4_arrow_hight + 120;
        t_rect.i4_bottom = t_rect.i4_top + 90;
        MENU_LOG_ON_FAIL(c_wgl_move(h_energy_start_icon, &t_rect, WGL_SYNC_AUTO_REPAINT));

        if((0 == pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx())&&b_is_subpage_state)
        {
            menu_show_hide_enger_start_icon(TRUE, FALSE);
        }

        if( a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI)
        {
        /*
            i4_ret = a_cfg_get_gui_lang(s639_lang);
            MENU_LOG_ON_FAIL(i4_ret);

            if(c_strncmp(s639_lang,"spa",3) == 0 )
            {
                t_rect.i4_left   = CONTENT_X + 350-90;
            }
            else
            {
                t_rect.i4_left   = CONTENT_X + 299-50;
            }
            t_rect.i4_right  = t_rect.i4_left + 233;
            t_rect.i4_top    = 40;
            t_rect.i4_bottom = t_rect.i4_top + 64;
        */
            menu_doly_vision_resize_logo(MENU_DOLBY_LOGO_POS_PICTURE_MODE);

            menu_doly_vision_logo_show(TRUE);
        }
    }
    MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL));

    return MENUR_OK;
}

#if( defined(APP_SUPPORT_PIC_HOT_KEY) )
static VOID _listbox_timer_reset(PAGE_TREE_ITEM_T *pt_page_tree_item)
{
    MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][TREE][KEY][PIC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if (h_listbox_timer != NULL_HANDLE
        && pt_page_tree_item != NULL
        && (( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title) )
        && PAGE_TREE_STATE_LISTBOX == pt_page_tree_item->pt_page->e_state))
    {

        MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][TREE][KEY][PIC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

        c_timer_stop(h_listbox_timer);

        c_timer_start(h_listbox_timer,
                      PIC_KEY_APPLY_DELAY,
                      X_TIMER_FLAG_ONCE,
                      _menu_page_tree_listbox_timer_cb,
                      (VOID *) pt_page_tree_item);
    }

}

static VOID _menu_page_tree_listbox_timer_cb(HANDLE_T  h_timer,
                                             VOID*     pv_tag)
{
    BOOL    b_handle = TRUE;
    PAGE_TREE_ITEM_T *pt_page_tree_item = (PAGE_TREE_ITEM_T *)pv_tag;

    MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][TREE][KEY][PIC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    _menu_page_tree_hot_key_page_proc(pt_page_tree_item->h_widget,
                                      BTN_RETURN,
                                      pt_page_tree_item,
                                      &b_handle);
}
#endif

#if( defined(APP_SUPPORT_PIC_HOT_KEY) ) // MENU_SUPPORT_HOT_KEY_PIC
static INT32 _menu_page_tree_enter_list_mode(PAGE_TREE_ITEM_T *pt_page_tree_item)
{
    INT32  i4_ret = MENUR_OK;
    UINT16 ui2_hlt = 0;
    UINT16 ui2_list_box_idx = 0;
    //HANDLE_T h_frm_main = NULL_HANDLE;

    MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][TREE][KEY][PIC]{%s,%d} \n", __FUNCTION__, __LINE__  )); );

    if (NULL == pt_page_tree_item)
    {
        DBG_LOG_PRINT(("Not a valid item. \n"));
        return WGLR_OK;
    }

    if(FALSE==pt_page_tree_item->b_enabled)
    {
        DBG_INFO(("Disable item \n"));
        return WGLR_OK;
    }

    if (PAGE_TREE_STATE_LISTBOX == pt_page_tree_item->pt_page->e_state)
    {
        DBG_INFO(("Already in ListBox state. \n"));
        return WGLR_OK;
    }

    b_is_subpage_state = TRUE;
    b_g_select_is_menu_key = FALSE;

    i4_ret = _insert_list_box_items(pt_page_tree_item);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Highlight the current one */
    ui2_hlt = pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx();
    if(ui2_hlt >= pt_page_tree_item->t_menuitem.u.t_list.ui2_elem_num)
    {
        ui2_hlt = 0;
    }

    ui2_list_box_idx = _cvt_menu_idx_2_listbox_idx(ui2_hlt);

    if ((UINT16)-1 != ui2_list_box_idx)
    {
        i4_ret = c_wgl_do_cmd(h_listbox,
                     WGL_CMD_LB_HLT_ELEM,
                     WGL_PACK(ui2_list_box_idx),
                     WGL_PACK(FALSE));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if(ui2_hlt > MENU_PAGE_TREE_MAX_ITEM)
    {
        i4_ret = c_wgl_do_cmd(h_listbox,
                              WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                              NULL,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set the title */
    i4_ret = menu_main_set_title(pt_page_tree_item->t_menuitem.ui2_msgid_title);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_tree_item->pt_page->h_cnt_frm, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_listbox, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_list_arrow_state_update(h_listbox, BTN_INVALID, FALSE);

    pt_page_tree_item->pt_page->e_state = PAGE_TREE_STATE_LISTBOX;

    //c_wgl_float(h_listbox, TRUE, WGL_NO_AUTO_REPAINT);
    menu_pm_repaint();

    MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][TREE][KEY][PIC]{%s,%d} ui2_hlt:%d, ui2_msgid_title:%d, ui2_msgid_desc:%d \n",
        __FUNCTION__, __LINE__, ui2_hlt,
        pt_page_tree_item->t_menuitem.ui2_msgid_title,
        pt_page_tree_item->t_menuitem.ui2_msgid_desc )); );

    /* Set the help tip */
#if 0
    i4_ret = menu_set_help_tip(MENU_TEXT(pt_page_tree_item->t_menuitem.ui2_msgid_desc));
    MENU_LOG_ON_FAIL(i4_ret);
#else
    i4_ret = _show_elem_help_tips(
        pt_page_tree_item->t_menuitem.ui2_msgid_desc,
        pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_desc_first,
        ui2_hlt,
        TRUE);
#endif

    if (TRUE == t_g_menu_common.b_is_hot_key_enter)
    {
        t_g_menu_common.b_is_hot_key_enter = FALSE;
    }

    b_hot_key_enter = TRUE;

  #if( defined(APP_SUPPORT_PIC_HOT_KEY) )
    _listbox_timer_reset(pt_page_tree_item);
  #endif

    return i4_ret;
}
#endif

#if( defined(APP_SUPPORT_PIC_HOT_KEY) )
static INT32 _menu_page_tree_apply_pic_mode(
                                             HANDLE_T           h_widget,
                                             UINT32             ui4_keycode,
                                             PAGE_TREE_ITEM_T   *pt_page_tree_item,
                                             BOOL               *pb_handled
                                           )
{
    INT32           i4_ret = MENUR_OK;
    UINT32          ui2_hlt = 0;
    UINT32          ui2_menu_idx = 0;
    UTF16_T         w2s_str[64] = {0};

    DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE][PIC]{%s,%d} \n", __FUNCTION__, __LINE__  )); );

    if (NULL == pt_page_tree_item)
    {
        return WGLR_INV_ARG;
    }

    if ( ( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title) == FALSE)
        || PAGE_TREE_STATE_LISTBOX != pt_page_tree_item->pt_page->e_state)
    {
        return i4_ret;
    }

    b_g_select_is_menu_key = FALSE;

    i4_ret = c_wgl_do_cmd(h_listbox,
                     WGL_CMD_LB_GET_HLT_INDEX,
                     WGL_PACK(&ui2_hlt),
                     NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_menu_idx = _cvt_listbox_idx_2_menu_idx (ui2_hlt);

    pt_page_tree_item->t_menuitem.u.t_list.pf_set_idx(ui2_menu_idx);

    /* Update listbox hlt index */
    if ((NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx) &&
        (NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
    {
        i4_ret = menu_list_set_idx(h_widget, ui2_hlt);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if ((NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx)&&
        (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
    {
        i4_ret = menu_list_set_idx(h_widget, ui2_hlt);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if ((NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx) &&
        (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
    {
        pt_page_tree_item->t_menuitem.u.t_list.pf_get_text(ui2_menu_idx, w2s_str, 64);
        i4_ret = menu_list_set_text(h_widget,
                       0,
                       w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_list_set_idx(h_widget, 0);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if ((NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx)&&
        (NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
    {
        i4_ret = menu_list_set_text(h_widget,
                       0,
                       MENU_TEXT(pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first+ui2_menu_idx));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_list_set_idx(h_widget, 0);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    i4_ret = menu_list_adjust_rect(pt_page_tree_item->h_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    _listbox_timer_reset(pt_page_tree_item);

    return i4_ret;
}

static INT32 _menu_page_tree_hot_key_page_proc(
                                         HANDLE_T   h_widget,
                                         UINT32     ui4_keycode,
                                         PAGE_TREE_ITEM_T* pt_page_tree_item,
                                         BOOL       *pb_handled)
{
    INT32 i4_ret = WGLR_USER;
    UINT16  ui2_hlt = 0;
    BOOL     b_pq_item = FALSE;

    MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][TREE][KEY][PIC]{%s,%d} \n", __FUNCTION__, __LINE__  )); );

    *pb_handled = FALSE;

    if (NULL == pt_page_tree_item)
    {
        return WGLR_INV_ARG;
    }

    if (FALSE == b_hot_key_enter)
    {
        return MENUR_INV_STATE;
    }

    if ( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title) == FALSE)
    {
        return MENUR_INV_ARG;
    }

    if ( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))
    {
        menu_list_arrow_state_update(h_listbox, ui4_keycode, TRUE);
    }

    switch (ui4_keycode)
    {
        case BTN_SELECT:
        case BTN_RETURN:
        case BTN_PREV_PRG:
        {
            UINT16 ui2_idx = 0;
            UTF16_T w2s_str[64] = {0};
            UINT16              ui2_visible_item = 0;
            GL_RECT_T           t_rect;
            HANDLE_T             h_last_shadow_item = NULL_HANDLE;
            PAGE_TREE_ITEM_T* pt_page_item;

            *pb_handled = TRUE;
            b_is_subpage_state = FALSE;

            c_wgl_set_visibility(pt_page_tree_item->pt_page->h_cnt_frm, WGL_SW_NORMAL);
            c_wgl_set_visibility(h_listbox, WGL_SW_HIDE);
            menu_list_arrow_hide(FALSE);
            if(_is_one_listbox_mode(pt_page_tree_item->pt_page))
            {
                i4_ret = menu_nav_back();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret = c_wgl_do_cmd(h_listbox,
                             WGL_CMD_LB_SET_ELEM_NUM,
                             WGL_PACK(0),
                             NULL);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            /* Set the title */
            i4_ret = menu_main_set_title(pt_page_tree_item->pt_page->ui2_msgid_title);
            MENU_LOG_ON_FAIL(i4_ret);

        #if 1
            /*Adjust last shadow position*/
            DLIST_FOR_EACH(pt_page_item, &pt_page_tree_item->pt_page->t_item_list, t_link)
            {
                if(pt_page_item->b_hidden == FALSE)
                {
                    ui2_visible_item += 1;
                }
            }
            t_rect.i4_left = CONTENT_X;
            t_rect.i4_right = CONTENT_X + CONTENT_H;
            t_rect.i4_top = MENU_ITEM_V_HEIGHT * (ui2_visible_item)+ CONTENT_Y;
            t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

            menu_pm_get_last_shadow_item(&h_last_shadow_item);
            i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
            MENU_LOG_ON_FAIL(i4_ret);
        #endif

            /* For sleep timer, this is not a perfect solution, but the lowest risk. */
            if ((NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_prev_idx) &&
                (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx) &&
                (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx)  &&
                (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
            {
                ui2_idx = pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx();

                pt_page_tree_item->t_menuitem.u.t_list.pf_get_text(ui2_idx, w2s_str, 63);
                i4_ret = menu_list_set_text(pt_page_tree_item->h_widget,
                                   0,
                                   w2s_str);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_list_adjust_rect(pt_page_tree_item->h_widget);
                MENU_LOG_ON_FAIL(i4_ret);
            }

            i4_ret = menu_pm_repaint();
            MENU_LOG_ON_FAIL(i4_ret);

            pt_page_tree_item->pt_page->e_state = PAGE_TREE_STATE_NORMAL;
            i4_ret = _show_elem_help_tips(
                pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_desc_first,
                ui2_hlt,
                TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            b_hot_key_enter = FALSE;
            i4_ret = c_timer_stop(h_listbox_timer);
            MENU_LOG_ON_FAIL(i4_ret);

            return WGLR_OK;
        }

        case BTN_CURSOR_UP:
        {
            *pb_handled = TRUE;
            i4_ret = c_wgl_do_cmd(h_listbox,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_hlt),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);
            if (0 == ui2_hlt)
            {
                i4_ret=menu_set_backbar_paremeter(pt_page_tree_item->h_widget,
                                                  pt_page_tree_item->h_widget);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_set_focus_on_backbar(FALSE);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_wgl_do_cmd(h_listbox,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_hlt),
                                          NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret = c_wgl_do_cmd(h_listbox,
                             WGL_CMD_LB_HLT_PREV_ELEM,
                             WGL_PACK(TRUE),
                             NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                /* update picture mode */
                i4_ret = _menu_page_tree_apply_pic_mode(h_widget,
                                                        ui4_keycode,
                                                        pt_page_tree_item,
                                                        pb_handled);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = _show_elem_help_tips(pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                                              pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_desc_first,
                                              ui2_hlt,
                                              TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }

            _listbox_timer_reset(pt_page_tree_item);

            return WGLR_OK;
        }
        case BTN_CURSOR_DOWN:
        case BTN_P_EFFECT:
        {
            UINT16 ui2_elem_num = 0;
            *pb_handled = TRUE;

            i4_ret = c_wgl_do_cmd(h_listbox,
                                  WGL_CMD_LB_GET_ELEM_NUM,
                                  WGL_PACK(&ui2_elem_num),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(h_listbox,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_hlt),
                                      NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            if(ui2_hlt == ui2_elem_num-1)
            {
                i4_ret = c_wgl_do_cmd(h_listbox,
                                     WGL_CMD_LB_HLT_ELEM_VISIBLE,
                                     WGL_PACK(0),
                                     WGL_PACK(0));
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret = c_wgl_do_cmd(h_listbox,
                             WGL_CMD_LB_HLT_NEXT_ELEM,
                             WGL_PACK(TRUE),
                             NULL);
                MENU_LOG_ON_FAIL(i4_ret);
            }

            if ( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))
            {
                menu_list_arrow_state_update(h_listbox, BTN_INVALID, TRUE);
            }

            /* update picture mode */
            i4_ret = _menu_page_tree_apply_pic_mode(h_widget,
                                                    ui4_keycode,
                                                    pt_page_tree_item,
                                                    pb_handled);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = _show_elem_help_tips(pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                                          pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_desc_first,
                                          ui2_hlt,
                                          TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            return WGLR_OK;
        }
        default:
            break;
    }

    //b_is_subpage_state = FALSE;
    return i4_ret;
}
#endif

#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _handle_special_page
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _handle_special_page(PAGE_TREE_ITEM_T* pt_page_tree_item)
{

    DBG_ERROR(("line %d, _handle_special_page", __LINE__));
    if (pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_OSD_LANG)
    {
        menu_page_set_hide_main_inpageswitch();
        menu_nav_go(ui4_page_menu_language_dialog, NULL);
        DBG_ERROR(("line %d, _handle_special_page ,ui4_page_menu_language_dialog:%ld", __LINE__, ui4_page_menu_language_dialog));
    }
    return MENUR_OK;

}
/*----------------------------------------------------------------------------
 * Name: menu_chang_language
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

VOID menu_chang_language(UINT16 ui2_idx)
{
    UINT16  ui2_lang;
    switch(ui2_idx)
    {
        case 0:
            ui2_lang = MLM_MENU_LANG_ENG;
            break;
        case 1:
            ui2_lang = MLM_MENU_LANG_ESL;
            break;
        case 2:
            ui2_lang = MLM_MENU_LANG_FRA;
            break;
        default:
            ui2_lang = MLM_MENU_LANG_ENG;
            break;
    }

    menu_chg_lang(ui2_lang);
    menu_pm_repaint();
}
#endif

typedef UINT16  (*menu_item_list_action)(VOID);

/*----------------------------------------------------------------------------
 * Name: _handle_key_list_normal
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _handle_key_list_normal (
             HANDLE_T   h_widget,
             UINT32     ui4_keycode,
             PAGE_TREE_ITEM_T* pt_page_tree_item,
             BOOL       *pb_handled)
{
    INT32 i4_ret = WGLR_OK;
    *pb_handled = FALSE;

    MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
        __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

    if (NULL == pt_page_tree_item)
    {
        return WGLR_INV_ARG;
    }

    switch(ui4_keycode)
    {
        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
        {
            UINT16 ui2_idx = 0;
            UTF16_T w2s_str[64];

            menu_item_list_action p_action_func = (ui4_keycode == BTN_CURSOR_LEFT ?
               pt_page_tree_item->t_menuitem.u.t_list.pf_prev_idx :
               pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx);

            *pb_handled = TRUE;
            if(FALSE == pt_page_tree_item->b_enabled)
            {
                DBG_ERROR(("Disable item \n"));
                return WGLR_OK;
            }

            if ((NULL != p_action_func)&&
                (NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
            {
                ui2_idx = p_action_func();
                MENU_LOG_ON_FAIL(menu_list_set_text(pt_page_tree_item->h_widget,
                                   0,
                                   MENU_TEXT(pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first + ui2_idx)));

                MENU_LOG_ON_FAIL( menu_list_set_idx(pt_page_tree_item->h_widget,0));
                MENU_LOG_ON_FAIL(menu_list_adjust_rect(pt_page_tree_item->h_widget));
            }

            if ((NULL != p_action_func)&&
                (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
            {
                ui2_idx = p_action_func();
                pt_page_tree_item->t_menuitem.u.t_list.pf_get_text(ui2_idx, w2s_str, 64);
                MENU_LOG_ON_FAIL( menu_list_set_text(pt_page_tree_item->h_widget,
                                                     0,
                                                     w2s_str));

                MENU_LOG_ON_FAIL(menu_list_set_idx(pt_page_tree_item->h_widget,0));

                MENU_LOG_ON_FAIL(menu_list_adjust_rect(pt_page_tree_item->h_widget));
            }

            if ((NULL == p_action_func)&&
                (NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
            {

                MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_widget,
                                              ui4_keycode == BTN_CURSOR_LEFT ?
                                              WGL_CMD_LB_HLT_PREV_ELEM : WGL_CMD_LB_HLT_NEXT_ELEM,
                                              WGL_PACK(FALSE),
                                              NULL));

                MENU_LOG_ON_FAIL(menu_list_adjust_rect(pt_page_tree_item->h_widget));
                MENU_LOG_ON_FAIL(menu_list_get_idx(h_widget, &ui2_idx));

#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
                if (pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_OSD_LANG)
                {
                    ui2_menu_language_new_idx = ui2_idx;
                    //menu_chang_language(ui2_idx);
                }
                else
                {
                    pt_page_tree_item->t_menuitem.u.t_list.pf_set_idx(ui2_idx);
                }
#else
                pt_page_tree_item->t_menuitem.u.t_list.pf_set_idx(ui2_idx);
#endif
                menu_pic_energy_change_set_status();

            }

            if ((NULL == p_action_func)&&
                (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
            {
                MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_widget,
                                              ui4_keycode == BTN_CURSOR_LEFT ?
                                              WGL_CMD_LB_HLT_PREV_ELEM : WGL_CMD_LB_HLT_NEXT_ELEM,
                                              WGL_PACK(FALSE),
                                              NULL));

                MENU_LOG_ON_FAIL( menu_list_get_idx(h_widget, &ui2_idx));

                pt_page_tree_item->t_menuitem.u.t_list.pf_get_text(ui2_idx, w2s_str, 64);
                MENU_LOG_ON_FAIL( menu_list_set_text(pt_page_tree_item->h_widget,
                                                     ui2_idx,
                                                     w2s_str));
                MENU_LOG_ON_FAIL(menu_list_adjust_rect(pt_page_tree_item->h_widget));
                pt_page_tree_item->t_menuitem.u.t_list.pf_set_idx(ui2_idx);

                menu_pic_energy_change_set_status();
            }

            UINT32  ui4_page_id = 0;

            i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
            if (ui4_page_id != ui4_g_menu_page_terms_sub)
            {
                MENU_LOG_ON_FAIL(_show_elem_help_tips(pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                                                      pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_desc_first,
                                                      ui2_idx,
                                                      TRUE));
            }
            c_wgl_repaint(h_widget, NULL, TRUE);
#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
            MENU_LOG_ON_FAIL(_handle_special_page(pt_page_tree_item));
#endif

#ifdef APP_TTS_SUPPORT

        if(FALSE == b_btn_left_right_zoom)
        {
            b_btn_left_right_zoom = TRUE;
        }
#endif
            if (pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_VID_HDMI_MODE)
            {
                return WGLR_OK;
            }
            _menu_page_tree_play_tts(h_widget, _MENU_TREE_TTS_PLAY_TITLE_AND_VAL);


            return WGLR_OK;
        }
        case BTN_SELECT:
        {
            DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} \n", __FUNCTION__, __LINE__  )); );

            UINT16 ui2_hlt = 0;
            UINT16 ui2_list_box_idx = 0;
            UINT32  ui4_subpage_id;

            *pb_handled = TRUE;

            if(FALSE==pt_page_tree_item->b_enabled)
            {
                DBG_ERROR(("Disable item \n"));
                return WGLR_OK;
            }

            if((NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_is_subpage) &&
                (FALSE == pt_page_tree_item->t_menuitem.u.t_list.pf_is_subpage(ui2_hlt, &ui4_subpage_id)))
            {
                DBG_ERROR(("It is subpage \n"));
                return WGLR_OK;
            }

            if (b_g_select_is_menu_key)
            {
                b_g_select_is_menu_key = FALSE;
                menu_leave(TRUE, 0);
                return WGLR_OK;
            }

            b_is_subpage_state = TRUE;
            b_g_select_is_menu_key = FALSE;

            MENU_LOG_ON_FAIL(_insert_list_box_items(pt_page_tree_item));

            c_wgl_set_highlight_widget(h_listbox);

            /* Highlight the current one */
            ui2_hlt = pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx();
            if(ui2_hlt >= pt_page_tree_item->t_menuitem.u.t_list.ui2_elem_num)
            {
                ui2_hlt = 0;
            }

            ui2_list_box_idx = _cvt_menu_idx_2_listbox_idx(ui2_hlt);

            if ((UINT16)-1 != ui2_list_box_idx)
            {
                MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                              WGL_CMD_LB_HLT_ELEM,
                                              WGL_PACK(ui2_list_box_idx),
                                              WGL_PACK(FALSE)));
            }

            if(ui2_hlt > MENU_PAGE_TREE_MAX_ITEM)
            {
                MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                              WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                                              NULL,
                                              NULL));
            }

#if 0 //def APP_HDR_SUPPORT
            menu_doly_vision_logo_show(FALSE);
            if(( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))&&
               ( a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI))
            {
                GL_RECT_T   t_rect;
                t_rect.i4_left   = CONTENT_X + 299;
                t_rect.i4_right  = t_rect.i4_left + 49;
                t_rect.i4_top    = 30;
                t_rect.i4_bottom = t_rect.i4_top + 64;
                menu_doly_vision_resize_logo(t_rect);
                menu_doly_vision_logo_show(TRUE);
            }
#endif

            /* Set the title */
            MENU_LOG_ON_FAIL( menu_main_set_title(pt_page_tree_item->t_menuitem.ui2_msgid_title));

            MENU_LOG_ON_FAIL( c_wgl_set_visibility(pt_page_tree_item->pt_page->h_cnt_frm, WGL_SW_HIDE));
            MENU_LOG_ON_FAIL( c_wgl_set_visibility(h_listbox, WGL_SW_NORMAL));

            menu_list_arrow_state_update(h_listbox, BTN_INVALID, FALSE);

            pt_page_tree_item->pt_page->e_state = PAGE_TREE_STATE_LISTBOX;

            menu_pm_repaint();

            _menu_page_tree_play_tts(pt_page_tree_item->h_widget, _MENU_TREE_TTS_PLAY_UNKNOW);

            if(pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_DEMO_MODE)
            {
                UINT8   ui1_demo_mode = 0;

                a_cfg_cust_get_demo_mode_value(&ui1_demo_mode);
                pt_page_tree_item->t_menuitem.ui2_msgid_desc=_menu_page_tree_get_demo_mode_help_text_id(ui1_demo_mode);
            }

            /* Set the help tip */
            i4_ret = _show_elem_help_tips(
                pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_desc_first,
                ui2_hlt,
                TRUE);
            if(pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_DEMO_MODE)
            {
                pt_page_tree_item->t_menuitem.ui2_msgid_desc=MLM_MENU_KEY_DEMO_MODE_HELP;
            }
            c_wgl_repaint(h_listbox, NULL, FALSE);
            return WGLR_OK;
        }

        default:
            break;
    }
    return i4_ret;

}

/*----------------------------------------------------------------------------
 * Name: _handle_key_list_box
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _handle_key_list_box(HANDLE_T           h_widget,
                                      UINT32             ui4_keycode,
                                      PAGE_TREE_ITEM_T*  pt_page_tree_item,
                                      BOOL           *   pb_handled)
{
    UINT32  ui4_subpage_id         = 0;
    UINT16  ui2_hlt                = 0;
    UINT16  ui2_menu_idx           = 0;
    *pb_handled                    = FALSE;
    HANDLE_T    h_last_shadow_item = NULL_HANDLE;


    MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
        __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );


    if (NULL == pt_page_tree_item)
    {
        return WGLR_INV_ARG;
    }


#if( defined(APP_SUPPORT_PIC_HOT_KEY) ) // MENU_SUPPORT_HOT_KEY_PIC
    _menu_page_tree_hot_key_page_proc(h_widget,
                                      ui4_keycode,
                                      pt_page_tree_item,
                                      pb_handled);
    if (TRUE == *pb_handled)
    {
        return WGLR_OK;
    }
#endif

    if ( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))
    {
        menu_list_arrow_state_update(h_listbox, ui4_keycode, TRUE);
    }

    switch (ui4_keycode)
    {
        case BTN_SELECT:
        {
            DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} \n", __FUNCTION__, __LINE__  )); );

            UTF16_T w2s_str[64];

            c_wgl_set_highlight_widget(NULL_HANDLE);
            if ( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))
            {
                menu_show_hide_enger_start_icon(FALSE, FALSE);
            }
            if (b_g_select_is_menu_key)
            {
                b_g_select_is_menu_key = FALSE;
                pt_page_tree_item->pt_page->e_state = PAGE_TREE_STATE_NORMAL;

                MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_listbox, WGL_SW_HIDE));
                menu_list_arrow_hide(FALSE);
                menu_leave(TRUE, 0);
                return WGLR_OK;
            }

            b_g_select_is_menu_key = FALSE;
            *pb_handled = TRUE;

            MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK(&ui2_hlt),
                                          NULL));

            ui2_menu_idx = _cvt_listbox_idx_2_menu_idx (ui2_hlt);

            /* Set menu item index */
            if ((UINT16)-1 != ui2_menu_idx)
            {
#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
                if (pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_OSD_LANG)
                {
                    ui2_menu_language_new_idx = ui2_hlt;
                }
                else
                {
                    pt_page_tree_item->t_menuitem.u.t_list.pf_set_idx(ui2_menu_idx);

                }
#else
                pt_page_tree_item->t_menuitem.u.t_list.pf_set_idx(ui2_menu_idx);
#endif
                menu_pic_energy_change_set_status();
            }

            /* Update listbox hlt index */
            if ((NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx) &&
                (NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
            {
#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
                if (pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_OSD_LANG)
                {
                    ui2_menu_language_new_idx = ui2_hlt;
                    //menu_chang_language(ui2_hlt);
                }
                else
                {
                    MENU_LOG_ON_FAIL(menu_list_set_idx(h_widget, ui2_hlt));
                }
#else
                MENU_LOG_ON_FAIL(menu_list_set_idx(h_widget, ui2_hlt));
#endif
            }

            if ((NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx)&&
                (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
            {
                MENU_LOG_ON_FAIL(menu_list_set_idx(h_widget, ui2_hlt));
            }

            if ((NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx) &&
                (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
            {
                pt_page_tree_item->t_menuitem.u.t_list.pf_get_text(ui2_menu_idx, w2s_str, 64);
                MENU_LOG_ON_FAIL( menu_list_set_text(h_widget,
                                                     0,
                                                     w2s_str));
                MENU_LOG_ON_FAIL(menu_list_set_idx(h_widget, 0));
            }

            if ((NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx)&&
                (NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
            {
                MENU_LOG_ON_FAIL( menu_list_set_text(h_widget,
                                                     0,
                                                     MENU_TEXT(pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first+ui2_menu_idx)));
                MENU_LOG_ON_FAIL( menu_list_set_idx(h_widget, 0));
            }
            MENU_LOG_ON_FAIL( menu_list_adjust_rect(pt_page_tree_item->h_widget));

            if(pt_page_tree_item->t_menuitem.u.t_list.pf_is_subpage != NULL &&
               pt_page_tree_item->t_menuitem.u.t_list.pf_is_subpage(ui2_hlt, &ui4_subpage_id))
            {
                MENU_LOG_ON_FAIL( menu_nav_go(ui4_subpage_id, NULL));
                return WGLR_OK;
            }

            MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_page_tree_item->pt_page->h_cnt_frm, WGL_SW_NORMAL));
            MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_listbox, WGL_SW_HIDE));
            menu_list_arrow_hide(FALSE);

            menu_pm_get_last_shadow_item(&h_last_shadow_item);

            MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE));

            if(_is_one_listbox_mode(pt_page_tree_item->pt_page))
            {
                MENU_LOG_ON_FAIL(menu_nav_back());
            }
            else
            {
                MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                              WGL_CMD_LB_SET_ELEM_NUM,
                                              WGL_PACK(0),
                                              NULL));
            }
            /* Set the title */
            UINT32    ui4_page_id = 0;
            MENU_LOG_ON_FAIL(menu_nav_get_crnt_page(&ui4_page_id));
            if (ui4_page_id != ui4_g_menu_page_terms_sub)
            {
                MENU_LOG_ON_FAIL( menu_main_set_title(pt_page_tree_item->pt_page->ui2_msgid_title));
            }
            else
            {
                return WGLR_OK;
            }
            b_is_subpage_state = FALSE;
            pt_page_tree_item->pt_page->e_state = PAGE_TREE_STATE_NORMAL;

            if (0 == pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_desc_first)
            {
                MENU_LOG_ON_FAIL(menu_set_help_tip(MENU_TEXT(pt_page_tree_item->t_menuitem.ui2_msgid_desc)));
            }
            else
            {
                MENU_LOG_ON_FAIL( menu_set_help_tip(MENU_TEXT(pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_desc_first + ui2_hlt)));
            }

#ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
            if (pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_OSD_LANG)
            {
                MENU_LOG_ON_FAIL(_handle_special_page(pt_page_tree_item));
                return WGLR_OK;
            }
#endif

    #ifdef APP_HDR_SUPPORT
            menu_doly_vision_logo_show(FALSE);
            if(( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))&&
               ( a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI))
            {
            /*
                GL_RECT_T   t_rect;
                t_rect.i4_left   = CONTENT_X + 269-120;
                t_rect.i4_right  = t_rect.i4_left + 233;
                t_rect.i4_top    = 120;
                t_rect.i4_bottom = t_rect.i4_top + 64;
            */
                menu_doly_vision_resize_logo(MENU_DOLBY_LOGO_POS_PICTURE);

                menu_doly_vision_logo_show(TRUE);
            }
    #endif

            menu_pm_repaint();
            if (pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_VID_HDMI_MODE)
            {
                return WGLR_OK;
            }

            _menu_page_tree_play_tts(pt_page_tree_item->h_widget, _MENU_TREE_TTS_PLAY_TITLE_AND_VAL);

            return WGLR_OK;
        }
        /* go through */
        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
            *pb_handled = TRUE;
            return WGLR_OK;

        case BTN_RETURN:
        case BTN_PREV_PRG:
        {
            UINT16 ui2_idx = 0;
            UTF16_T w2s_str[64] = {0};
            UINT16              ui2_visible_item = 0;
            GL_RECT_T           t_rect;
            HANDLE_T             h_last_shadow_item = NULL_HANDLE;
            PAGE_TREE_ITEM_T* pt_page_item;
            c_wgl_set_highlight_widget(NULL_HANDLE);

            *pb_handled = TRUE;
            b_is_subpage_state = FALSE;
            c_wgl_set_visibility(pt_page_tree_item->pt_page->h_cnt_frm, WGL_SW_NORMAL);
            c_wgl_set_visibility(h_listbox, WGL_SW_HIDE);
            menu_list_arrow_hide(FALSE);
            if (( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title)))
            {
                menu_show_hide_enger_start_icon(FALSE, FALSE);
            }
            if(_is_one_listbox_mode(pt_page_tree_item->pt_page))
            {
                MENU_LOG_ON_FAIL(menu_nav_back());
            }
            else
            {
                MENU_LOG_ON_FAIL( c_wgl_do_cmd(h_listbox,
                                               WGL_CMD_LB_SET_ELEM_NUM,
                                               WGL_PACK(0),
                                               NULL));
            }

            /* Set the title */
            MENU_LOG_ON_FAIL(menu_main_set_title(pt_page_tree_item->pt_page->ui2_msgid_title));

            /*Adjust last shadow position*/
            DLIST_FOR_EACH(pt_page_item, &pt_page_tree_item->pt_page->t_item_list, t_link)
            {
                if(pt_page_item->b_hidden == FALSE)
                {
                    ui2_visible_item += 1;
                }
            }

            ui2_visible_item -= pt_page_tree_item->pt_page->i2_offset;
            t_rect.i4_left   = CONTENT_X;
            t_rect.i4_right  = CONTENT_X + CONTENT_H;
            t_rect.i4_top    = MENU_ITEM_V_HEIGHT * (ui2_visible_item)+ CONTENT_Y;
            t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

            menu_pm_get_last_shadow_item(&h_last_shadow_item);
            MENU_LOG_ON_FAIL(c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT));
            MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL));

            /* For sleep timer, this is not a perfect solution, but the lowest risk. */
            if ((NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_prev_idx) &&
                (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx) &&
                (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx)  &&
                (NULL != pt_page_tree_item->t_menuitem.u.t_list.pf_get_text))
            {
                ui2_idx = pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx();

                pt_page_tree_item->t_menuitem.u.t_list.pf_get_text(ui2_idx, w2s_str, 63);
                MENU_LOG_ON_FAIL(menu_list_set_text(pt_page_tree_item->h_widget,
                                                    0,
                                                    w2s_str));

                MENU_LOG_ON_FAIL( menu_list_adjust_rect(pt_page_tree_item->h_widget));
            }

        #ifdef APP_HDR_SUPPORT

            menu_doly_vision_logo_show(FALSE);
            if(( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))&&
               (a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI ))
            {
            /*
                GL_RECT_T   t_rect;
                t_rect.i4_left   = CONTENT_X + 269-120;
                t_rect.i4_right  = t_rect.i4_left + 233;
                t_rect.i4_top    = 120;
                t_rect.i4_bottom = t_rect.i4_top + 64;
            */
                menu_doly_vision_resize_logo(MENU_DOLBY_LOGO_POS_PICTURE);

                menu_doly_vision_logo_show(TRUE);
            }
        #endif


            pt_page_tree_item->pt_page->e_state = PAGE_TREE_STATE_NORMAL;
            MENU_LOG_ON_FAIL(_show_elem_help_tips(pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                                                  pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_desc_first,
                                                  ui2_hlt,
                                                  TRUE));
            menu_pm_repaint();

            _menu_page_tree_play_tts(pt_page_tree_item->h_widget, _MENU_TREE_TTS_PLAY_TITLE_AND_VAL);

            return WGLR_OK;
        }
        case BTN_CURSOR_UP:
        {
            *pb_handled = TRUE;
            MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK(&ui2_hlt),
                                          NULL));

            if (( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))&&(1 == ui2_hlt))
            {
                menu_show_hide_enger_start_icon(TRUE, TRUE);
            }
            else if( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))
            {
                menu_show_hide_enger_start_icon(FALSE, TRUE);
            }
            if (0 == ui2_hlt)
            {
                c_wgl_set_highlight_widget(NULL_HANDLE);
                MENU_LOG_ON_FAIL(menu_set_backbar_paremeter(pt_page_tree_item->h_widget,
                                                            pt_page_tree_item->h_widget));

                MENU_LOG_ON_FAIL(menu_set_focus_on_backbar(TRUE));
                MENU_LOG_ON_FAIL( c_wgl_do_cmd(h_listbox,
                                               WGL_CMD_LB_UNHLT_ELEM,
                                               WGL_PACK(ui2_hlt),
                                               NULL));
            }
            else
            {
                MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                              WGL_CMD_LB_HLT_PREV_ELEM,
                                              WGL_PACK(TRUE),
                                              NULL));

                _menu_page_tree_play_tts(pt_page_tree_item->h_widget, _MENU_TREE_TTS_PLAY_UNKNOW);
                if(pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_DEMO_MODE)
                {
                    pt_page_tree_item->t_menuitem.ui2_msgid_desc=_menu_page_tree_get_demo_mode_help_text_id(ui2_hlt - 1);
                }
                MENU_LOG_ON_FAIL( _show_elem_help_tips (pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                                                        pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_desc_first,
                                                        ui2_hlt,
                                                        TRUE));

                if(pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_DEMO_MODE)
                {
                    pt_page_tree_item->t_menuitem.ui2_msgid_desc=MLM_MENU_KEY_DEMO_MODE_HELP;
                }
            }
            c_wgl_repaint(h_listbox,NULL,TRUE);
            return WGLR_OK;
        }
        case BTN_CURSOR_DOWN:
        {
            UINT16 ui2_elem_num = 0;
            *pb_handled = TRUE;
            MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                          WGL_CMD_LB_GET_ELEM_NUM,
                                          WGL_PACK(&ui2_elem_num),
                                          NULL));

            if (( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title)))
            {
                menu_show_hide_enger_start_icon(FALSE, TRUE);
            }

            MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK(&ui2_hlt),
                                          NULL));

            DBG_INFO(("[MENU][%s %d] ui2_elem_num = %d,ui2_hlt = %d\n",__FUNCTION__,__LINE__,ui2_elem_num,ui2_hlt));
            if(ui2_hlt  < ui2_elem_num - 1)
            {
                MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                              WGL_CMD_LB_HLT_NEXT_ELEM,
                                              WGL_PACK(TRUE),
                                              NULL));

                _menu_page_tree_play_tts(pt_page_tree_item->h_widget, _MENU_TREE_TTS_PLAY_UNKNOW);
                if(pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_DEMO_MODE)
                {
                    pt_page_tree_item->t_menuitem.ui2_msgid_desc=_menu_page_tree_get_demo_mode_help_text_id(ui2_hlt + 1);
                }
                MENU_LOG_ON_FAIL(_show_elem_help_tips(pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                                                      pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_desc_first,
                                                      ui2_hlt,
                                                      TRUE));

                if(pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_DEMO_MODE)
                {
                    pt_page_tree_item->t_menuitem.ui2_msgid_desc = MLM_MENU_KEY_DEMO_MODE_HELP;
                }
            }
            c_wgl_repaint(h_listbox,NULL,TRUE);
            return WGLR_OK;
        }
    }

    b_is_subpage_state = FALSE;
    return WGLR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _item_list_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_list_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32 i4_ret=0;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} h_widget:0x%X, ui4_msg:0x%X \n",
                __FUNCTION__, __LINE__, h_widget, ui4_msg )); );

            PAGE_TREE_ITEM_T* pt_page_tree_item = NULL;

            i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=_chg_item_list(h_widget,
                                  FALSE);
			
            MENU_LOG_ON_FAIL(i4_ret);
            DBG_INFO(("[MENU][%s %d] idx =%d, title =%d\n",__FUNCTION__,__LINE__,
                pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx(),
                pt_page_tree_item->t_menuitem.ui2_msgid_title));

            if((0 == pt_page_tree_item->t_menuitem.u.t_list.pf_get_idx())&&
                ( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))&&
                (pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_LISTBOX))
            {
                menu_show_hide_enger_start_icon(TRUE, FALSE);
            }

            if(pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_LISTBOX)
            {
                c_wgl_set_highlight_widget(h_listbox);
            }

            if (0xFFFF != ui2_list_hlt_before_hlt)
            {
                i4_ret=c_wgl_do_cmd(h_listbox,
                                 WGL_CMD_LB_HLT_ELEM,
                                 WGL_PACK(ui2_list_hlt_before_hlt),
                                 WGL_PACK(TRUE));
                MENU_LOG_ON_FAIL(i4_ret);

                ui2_list_hlt_before_hlt = 0xFFFF;

                if (i4_ret == WGLR_OK)
                    c_wgl_set_highlight_widget(h_listbox);
            }
            c_wgl_repaint(h_listbox,NULL,TRUE);
        }
        break;

        case WGL_MSG_LOSE_FOCUS:
        {
            MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} h_widget:0x%X, ui4_msg:0x%X \n",
                __FUNCTION__, __LINE__, h_widget, ui4_msg )); );

            PAGE_TREE_ITEM_T* pt_page_tree_item = NULL;

            i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
            MENU_LOG_ON_FAIL(i4_ret);

            if (pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_LISTBOX)
            {
                i4_ret = c_wgl_do_cmd(h_listbox,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_list_hlt_before_hlt),
                                     WGL_PACK(NULL));
                MENU_LOG_ON_FAIL(i4_ret);

                DBG_INFO(("_item_listbox_proc_fct() WGL_MSG_LOSE_FOCUS %x\n", ui2_list_hlt_before_hlt));

                if (0xFFFF != ui2_list_hlt_before_hlt)
                {
                    i4_ret = c_wgl_do_cmd(h_listbox,
                                         WGL_CMD_LB_UNHLT_ELEM,
                                         WGL_PACK(ui2_list_hlt_before_hlt),
                                         WGL_PACK(NULL));
                    MENU_LOG_ON_FAIL(i4_ret);

                    c_wgl_set_highlight_widget(NULL_HANDLE);
                    c_wgl_repaint(h_listbox, NULL, TRUE);
                }
            }
        }
        break;

        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            PAGE_TREE_ITEM_T* pt_page_tree_item;
            BOOL              b_handled = FALSE;

            MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
                __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

            i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
            MENU_LOG_ON_FAIL(i4_ret);

            if(BTN_SELECT==ui4_keycode)
            {
                if (pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_INPUT_SOURCE)
                {
                    menu_nav_go(ui4_page_inp_set, NULL);
                    return MENUR_OK;
                }
                else if (pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_MENU_ASPECT_RATIO)
                {
                    menu_nav_go(ui4_g_menu_page_aspect_ratio, NULL);
                    return MENUR_OK;
                }
                else if (pt_page_tree_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_AUD_EQ_MODE_INDENTATION)
                {
                    menu_nav_go(ui4_g_menu_page_sb_setting_eq_mode, NULL);
                    return MENUR_OK;
                }
            }

            if(pt_page_tree_item->pt_page->e_state != PAGE_TREE_STATE_LISTBOX)
            {
                i4_ret = _handle_key_list_normal(h_widget ,ui4_keycode, pt_page_tree_item, &b_handled);
                MENU_LOG_ON_FAIL(i4_ret);
                if (TRUE == b_handled)
                {
                    return i4_ret;
                }
            }
            else
            {
                i4_ret = _handle_key_list_box(h_widget, ui4_keycode, pt_page_tree_item, &b_handled);
                MENU_LOG_ON_FAIL(i4_ret);
                if (TRUE == b_handled)
                {
                    return i4_ret;
                }

            }
        }
        default:
            break;
    }

    return _item_def_proc_fct(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: menu_page_is_reset_page
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL menu_page_is_reset_page(UINT32 ui4_page_id)
{
    UINT8             ui1_i,ui1_num;
    BOOL              b_reset_page=FALSE;
    UINT32            aui4_page_id[]={
                                      ui4_g_menu_page_picture_reset,
                                      ui4_g_menu_page_pic_mode_reset,
                                      ui4_g_menu_page_audio_reset,
                                      ui4_g_menu_page_reset_pub,
                                      ui4_g_menu_page_channel_lock_reset,
                                      ui4_g_page_clear_memory_dialog,
                                      ui4_g_page_clear_memory,
                                      ui4_page_clr_tmp_reset_pm,
                                      ui4_g_page_service_check_dialog,
                                      ui4_g_page_service_rst_dialog,
                                      ui4_g_menu_custom_page_create_pic_mode,
                                      ui4_g_menu_page_del_aud_mode,
                                      #ifdef APP_ADD_MENU_LANGUAGE_SUPPORT
                                      ui4_page_menu_language_dialog,
                                      #endif
                                      ui4_page_chg_country_code_dialog,
                                      ui4_mobile_device_delete_dialog_page_id,
                                      ui4_page_reset_tv_ad_id_dialog,
                                      ui4_page_off_rs_entry,
                                      ui4_page_oled_jb,
                                      ui4_page_oled_screen_1,
                                      ui4_page_oled_screen_2
                                     };

    ui1_num = sizeof(aui4_page_id)/sizeof(aui4_page_id[0]);

    for (ui1_i=0;ui1_i<ui1_num;ui1_i++)
    {
        if(aui4_page_id[ui1_i]==ui4_page_id)
        {
            b_reset_page =TRUE;
            break;
        }
    }
    if((ui4_page_id==ui4_g_menu_custom_page_create_pic_mode)&&b_reset_page)
    {
        if(create_pic_mode_no_need_show_cnt_page())
        {
            b_reset_page =TRUE;
        }
        else
        {
            b_reset_page =FALSE;
        }
    }


    #ifdef APP_MENU_CUSTOM_FACTORY_TREE
    if (FALSE == b_reset_page)
    {
        b_reset_page = menu_cust_fact_is_reset_page(ui4_page_id);
    }
    #endif

    return b_reset_page;
}
/*----------------------------------------------------------------------------
 * Name: _item_list_subpage_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_list_subpage_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32 i4_ret=0;

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        i4_ret=_chg_item_list(h_widget,
                              FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    break;

    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        PAGE_TREE_ITEM_T* pt_page_tree_item;

        MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
            __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

        i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
        MENU_LOG_ON_FAIL(i4_ret);

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        {
            UINT16 ui2_idx;

            if(FALSE==pt_page_tree_item->b_enabled)
            {
                DBG_ERROR(("Disable item \n"));
                return WGLR_OK;
            }

            if(pt_page_tree_item->t_menuitem.u.t_list_subpage.pf_prev_idx != NULL)
            {
                ui2_idx = pt_page_tree_item->t_menuitem.u.t_list_subpage.pf_prev_idx();
                if(ui2_idx < pt_page_tree_item->t_menuitem.u.t_list_subpage.ui2_elem_num)
                {
                    i4_ret=menu_list_set_idx(h_widget, ui2_idx);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                i4_ret=menu_list_adjust_rect(h_widget);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret=c_wgl_do_cmd(h_widget,
                             WGL_CMD_LB_HLT_PREV_ELEM,
                             WGL_PACK(FALSE),
                             NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_list_adjust_rect(h_widget);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_list_get_idx(h_widget, &ui2_idx);
                MENU_LOG_ON_FAIL(i4_ret);
                pt_page_tree_item->t_menuitem.u.t_list_subpage.pf_set_idx(ui2_idx);
            }

            if(pt_page_tree_item->t_menuitem.u.t_list_subpage.pf_get_text != NULL)
            {
                UTF16_T w2s_str[64];

                pt_page_tree_item->t_menuitem.u.t_list_subpage.pf_get_text(ui2_idx, w2s_str, 64);
                i4_ret=menu_list_set_text(pt_page_tree_item->h_widget,
                                   ui2_idx,
                                   w2s_str);
                MENU_LOG_ON_FAIL(i4_ret);
                i4_ret=menu_list_adjust_rect(pt_page_tree_item->h_widget);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            _menu_page_tree_play_tts(h_widget, _MENU_TREE_TTS_PLAY_VAL);

            _item_list_subpage_change_style(pt_page_tree_item);

            i4_ret=c_wgl_repaint(h_widget, NULL, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
            return WGLR_OK;
        }
        case BTN_CURSOR_RIGHT:
        {
            UINT16 ui2_idx;

            if(FALSE==pt_page_tree_item->b_enabled)
            {
                return WGLR_OK;
            }

            if(pt_page_tree_item->t_menuitem.u.t_list_subpage.pf_next_idx != NULL)
            {
                ui2_idx = pt_page_tree_item->t_menuitem.u.t_list_subpage.pf_next_idx();
                if(ui2_idx < pt_page_tree_item->t_menuitem.u.t_list_subpage.ui2_elem_num)
                {
                    i4_ret=menu_list_set_idx(h_widget, ui2_idx);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                i4_ret=menu_list_adjust_rect(h_widget);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret=c_wgl_do_cmd(h_widget,
                             WGL_CMD_LB_HLT_NEXT_ELEM,
                             WGL_PACK(FALSE),
                             NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_list_adjust_rect(h_widget);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_list_get_idx(h_widget, &ui2_idx);
                MENU_LOG_ON_FAIL(i4_ret);
                pt_page_tree_item->t_menuitem.u.t_list_subpage.pf_set_idx(ui2_idx);
            }

            if(pt_page_tree_item->t_menuitem.u.t_list_subpage.pf_get_text != NULL)
            {
                UTF16_T w2s_str[64];

                pt_page_tree_item->t_menuitem.u.t_list_subpage.pf_get_text(ui2_idx, w2s_str, 64);
                i4_ret=menu_list_set_text(pt_page_tree_item->h_widget,
                                   ui2_idx,
                                   w2s_str);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_list_adjust_rect(pt_page_tree_item->h_widget);
                MENU_LOG_ON_FAIL(i4_ret);
            }

            _menu_page_tree_play_tts(h_widget, _MENU_TREE_TTS_PLAY_VAL);
            _item_list_subpage_change_style(pt_page_tree_item);

            i4_ret=c_wgl_repaint(h_widget, NULL, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            return WGLR_OK;
        }
        case BTN_SELECT:
        {
            UINT32            ui4_page_id;
            BOOL              b_reset_page = FALSE;

            if (b_g_select_is_menu_key)
            {
               b_g_select_is_menu_key = FALSE;
               menu_leave(TRUE, 0);
               return WGLR_OK;
            }
            b_g_select_is_menu_key = FALSE;
            if(FALSE==pt_page_tree_item->b_enabled)
            {
                DBG_ERROR(("Disable item \n"));
                return WGLR_OK;
            }

            ui4_page_id = pt_page_tree_item->t_menuitem.u.t_list_subpage.ui4_subpage_id;

            b_reset_page=menu_page_is_reset_page(ui4_page_id);

#ifdef APP_MENU_DLG_COEXIST
            if(b_reset_page)
            {
                i4_ret=menu_set_page_hide(FALSE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret=menu_set_page_hide(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
#else
            if(b_reset_page)
            {
                i4_ret=menu_hide_help_tip();
                MENU_LOG_ON_FAIL(i4_ret);
            }
#endif
            i4_ret=menu_nav_go(ui4_page_id,
                        NULL);
            MENU_LOG_ON_FAIL(i4_ret);
            return WGLR_OK;
        }
        default:
            break;
        }
    }
    default:
        break;
    }
    return _item_def_proc_fct(h_widget, ui4_msg, param1, param2);
}


/*----------------------------------------------------------------------------
 * Name: _item_listbox_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_listbox_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32   i4_ret = 0;

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        i4_ret = _chg_item_list(h_widget, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        if (0xFFFF != ui2_list_hlt_before_hlt)
        {
            i4_ret=c_wgl_do_cmd(h_listbox,
                             WGL_CMD_LB_HLT_ELEM,
                             WGL_PACK(ui2_list_hlt_before_hlt),
                             WGL_PACK(TRUE));
            MENU_LOG_ON_FAIL(i4_ret);
            ui2_list_hlt_before_hlt = 0xFFFF;
            c_wgl_repaint(h_listbox, NULL, TRUE);
        }
    }
    break;

    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        PAGE_TREE_ITEM_T* pt_page_tree_item;
        UINT16  ui2_hlt = 0;
        UINT16  ui2_elem_num;

        MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
            __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

        i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
        MENU_LOG_ON_FAIL(i4_ret);

        if(pt_page_tree_item->pt_page->e_state != PAGE_TREE_STATE_LISTBOX)
        {
            switch (ui4_keycode)
            {
            case BTN_CURSOR_RIGHT:
            case BTN_SELECT:
            {
                UINT16  ui2_i;
                UTF16_T w2s_str[64];

                if ((b_g_select_is_menu_key) && (BTN_SELECT == ui4_keycode))
                {
                   b_g_select_is_menu_key = FALSE;

                   menu_leave(TRUE, 0);
                   return WGLR_OK;
                }
                b_g_select_is_menu_key = FALSE;

                if(FALSE==pt_page_tree_item->b_enabled)
                {
                    DBG_ERROR(("Disable item \n"));
                    return WGLR_OK;
                }

                ui2_elem_num = pt_page_tree_item->t_menuitem.u.t_listbox.ui2_elem_num;

                i4_ret=c_wgl_do_cmd(h_listbox,
                             WGL_CMD_LB_SET_ELEM_NUM,
                             WGL_PACK(ui2_elem_num),
                             NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                /* Show the listbox and insert the items to the listbox */
                for(ui2_i=0; ui2_i<ui2_elem_num;ui2_i++)
                {
                    if(pt_page_tree_item->t_menuitem.u.t_listbox.pf_get_text != NULL)
                    {
                        pt_page_tree_item->t_menuitem.u.t_listbox.pf_get_text(ui2_i, w2s_str, 64);
                    }
                    else
                    {
                        c_uc_w2s_strcpy(w2s_str,
                                        MENU_TEXT(pt_page_tree_item->t_menuitem.u.t_listbox.ui2_msgid_elem_first + ui2_i));
                    }

                    i4_ret=c_wgl_do_cmd(h_listbox,
                                 WGL_CMD_LB_SET_ITEM_TEXT,
                                 WGL_PACK_2 (ui2_i, 0),
                                 w2s_str);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                /* Highlight the current one */
                ui2_hlt = pt_page_tree_item->t_menuitem.u.t_listbox.pf_get_idx();
                if(ui2_hlt >= ui2_elem_num)
                {
                    ui2_hlt = 0;
                }

                i4_ret=c_wgl_do_cmd(h_listbox,
                             WGL_CMD_LB_HLT_ELEM,
                             WGL_PACK(ui2_hlt),
                             WGL_PACK(FALSE));
                MENU_LOG_ON_FAIL(i4_ret);

                /* Set the title */
                i4_ret = menu_main_set_title(pt_page_tree_item->t_menuitem.ui2_msgid_title);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=c_wgl_set_visibility(pt_page_tree_item->pt_page->h_cnt_frm, WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=c_wgl_set_visibility(h_listbox, WGL_SW_NORMAL);
                MENU_LOG_ON_FAIL(i4_ret);
                c_wgl_repaint(h_listbox,NULL,TRUE);
                i4_ret=menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);

                pt_page_tree_item->pt_page->e_state = PAGE_TREE_STATE_LISTBOX;

                i4_ret = _show_elem_help_tips(
                                    pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                                    pt_page_tree_item->t_menuitem.u.t_listbox.ui2_msgid_elem_desc_first,
                                    ui2_hlt,
                                    TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
                return WGLR_OK;
            }
            default:
                break;
            }
        }
        else
        {
            UINT32  ui4_subpage_id;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                    i4_ret=c_wgl_do_cmd(h_listbox,
                                 WGL_CMD_LB_GET_HLT_INDEX,
                                 WGL_PACK(&ui2_hlt),
                                 NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    pt_page_tree_item->t_menuitem.u.t_listbox.pf_set_idx(ui2_hlt);

                    if(pt_page_tree_item->t_menuitem.u.t_listbox.pf_is_subpage != NULL &&
                       pt_page_tree_item->t_menuitem.u.t_listbox.pf_is_subpage(ui2_hlt, &ui4_subpage_id))
                    {
                        i4_ret=menu_nav_go(ui4_subpage_id, NULL);
                        MENU_LOG_ON_FAIL(i4_ret);
                        return WGLR_OK;
                    }

                /* go through */
                case BTN_PREV_PRG:
                case BTN_RETURN:
                    i4_ret=c_wgl_set_visibility(pt_page_tree_item->pt_page->h_cnt_frm, WGL_SW_NORMAL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=c_wgl_set_visibility(h_listbox, WGL_SW_HIDE);
                    MENU_LOG_ON_FAIL(i4_ret);


                    if(_is_one_listbox_mode(pt_page_tree_item->pt_page))
                    {
                        i4_ret=menu_nav_back();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        i4_ret=c_wgl_do_cmd(h_listbox,
                                     WGL_CMD_LB_SET_ELEM_NUM,
                                     WGL_PACK(0),
                                     NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        /* Set the title */
                        i4_ret = menu_main_set_title(pt_page_tree_item->pt_page->ui2_msgid_title);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret=menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);

                        pt_page_tree_item->pt_page->e_state = PAGE_TREE_STATE_NORMAL;

                        i4_ret=_show_elem_help_tips(
                            pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                            pt_page_tree_item->t_menuitem.u.t_listbox.ui2_msgid_elem_desc_first,
                            ui2_hlt,
                            TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }

                    return WGLR_OK;
                case BTN_CURSOR_UP:
                {
                    i4_ret = c_wgl_do_cmd(h_listbox,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK(&ui2_hlt),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);
                    if(0==ui2_hlt)
                    {
                        i4_ret=menu_set_backbar_paremeter(pt_page_tree_item->h_widget,
                                                          pt_page_tree_item->h_widget);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret=menu_set_focus_on_backbar(FALSE);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = c_wgl_do_cmd(h_listbox,
                                              WGL_CMD_LB_UNHLT_ELEM,
                                              WGL_PACK(ui2_hlt),
                                              NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret=menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        i4_ret=c_wgl_do_cmd(h_listbox,
                                     WGL_CMD_LB_HLT_PREV_ELEM,
                                     WGL_PACK(TRUE),
                                     NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret=_show_elem_help_tips(
                            pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                            pt_page_tree_item->t_menuitem.u.t_listbox.ui2_msgid_elem_desc_first,
                            ui2_hlt,
                            TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }
                return WGLR_OK;

                case BTN_CURSOR_DOWN:
                {
                    i4_ret = c_wgl_do_cmd(h_listbox,
                                          WGL_CMD_LB_GET_ELEM_NUM,
                                          WGL_PACK(&ui2_elem_num),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_do_cmd(h_listbox,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK(&ui2_hlt),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    if(ui2_hlt == ui2_elem_num - 1)
                    {
                        i4_ret=menu_set_backbar_paremeter(pt_page_tree_item->h_widget,
                                                          pt_page_tree_item->h_widget);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = menu_help_tip_keytip_set_focus(pt_page_tree_item->h_widget,
                                                                0,
                                                                FALSE);
                        MENU_LOG_ON_FAIL(i4_ret);
                        ui2_list_hlt_before_hlt = ui2_hlt;
                        #ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT//fix DTV00607321
                        if (MENUR_INV_STATE == i4_ret)
                        {
                            return MENUR_OK;
                        }
                        #endif
                        i4_ret = c_wgl_do_cmd(h_listbox,
                                              WGL_CMD_LB_UNHLT_ELEM,
                                              WGL_PACK(ui2_hlt),
                                              NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        menu_pm_repaint();
                    }
                    else
                    {
                        i4_ret=c_wgl_do_cmd(h_listbox,
                                     WGL_CMD_LB_HLT_NEXT_ELEM,
                                     WGL_PACK(TRUE),
                                     NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret=_show_elem_help_tips(
                            pt_page_tree_item->t_menuitem.ui2_msgid_desc,
                            pt_page_tree_item->t_menuitem.u.t_listbox.ui2_msgid_elem_desc_first,
                            ui2_hlt,
                            TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }
                return WGLR_OK;

                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                    return MENUR_OK;
                default:
                    break;
            }
        }
    }
    default:
        break;
    }
    return _item_def_proc_fct(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _item_action_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_action_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32 i4_ret=0;
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        PAGE_TREE_ITEM_T* pt_page_tree_item;

        MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
            __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

        i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
        MENU_LOG_ON_FAIL(i4_ret);

        switch (ui4_keycode)
        {
            case BTN_CURSOR_RIGHT:
            case BTN_SELECT:
            {
                if (BTN_SELECT == ui4_keycode)
                {
                    b_g_select_is_menu_key = FALSE;
                }
                if(FALSE==pt_page_tree_item->b_enabled)
                {
                    DBG_ERROR(("Disable item \n"));
                    return WGLR_OK;
                }
                pt_page_tree_item->t_menuitem.u.t_action.pf_action();
            }
            return WGLR_OK;

            default:
                break;
        }
    }
    default:
        break;
    }
    return _item_def_proc_fct(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _item_subpage_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_subpage_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32       i4_ret             = 0;
    HANDLE_T    h_last_shadow_item = NULL_HANDLE;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            PAGE_TREE_ITEM_T* pt_page_tree_item;
            UINT32            ui4_page_id;
            BOOL              b_reset_page = FALSE;

            MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
                __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

            i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
            MENU_LOG_ON_FAIL(i4_ret);

            switch (ui4_keycode)
            {
                case BTN_CURSOR_RIGHT:
#ifndef BTN_LEFT_BACK_RIGHT_SELECT
                    return WGLR_OK;
#endif
                case BTN_SELECT:
                {
                    if (BTN_SELECT == ui4_keycode)
                    {
                        b_g_select_is_menu_key = FALSE;
                    }
                    if(FALSE == pt_page_tree_item->b_enabled)
                    {
                        DBG_ERROR(("Disable item \n"));
                        return WGLR_OK;
                    }

                    ui4_page_id = pt_page_tree_item->t_menuitem.u.t_subpage.ui4_subpage_id;

                   b_reset_page=menu_page_is_reset_page(ui4_page_id);
#ifdef APP_MENU_DLG_COEXIST
                    if(b_reset_page)
                    {
                        i4_ret=menu_set_page_hide(FALSE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        i4_ret=menu_set_page_hide(TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
#else
                    if(b_reset_page)
                    {
                        i4_ret=menu_hide_help_tip();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
#endif
                    if (ui4_page_id == ui4_g_menu_page_3D_setting)
                    {
                        //menu_leave (TRUE, MENU_PM_HIDE_DELAY);
                        //a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)BTN_3D, NULL);

                        menu_nav_go(ui4_page_id, NULL);
                    }
                    else if (ui4_page_id == ui4_g_menu_page_blank_scrn)
                    {
                    #ifdef APP_MENU_MMP_COEXIST
                        if  (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
                        {
                            a_amb_resume_app(MMP_NAME);
                            c_thread_delay(100);
                        }
                        else if (a_mmp_get_ap_status() != MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
                    #endif
                        {
                            menu_leave (TRUE, MENU_PM_HIDE_DELAY);
                        }
                        a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)BTN_BLANK_SCREEN, NULL);
                    }
                    else
                    {
                        if(b_reset_page)
                        {
                        }
                        else
                        {
                            menu_pm_get_last_shadow_item(&h_last_shadow_item);
                            i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
                            MENU_LOG_ON_FAIL(i4_ret);
                        }

                        MENU_PAGE_HINT_T t_menu_page_hint = {0};
                        _reset_page_cust_process(pt_page_tree_item, &ui4_page_id, &t_menu_page_hint);

                        if (MENU_PAGE_HT_NONE == t_menu_page_hint.e_hint_type)
                        {
                            i4_ret=menu_nav_go(ui4_page_id, NULL);
                        }
                        else
                        {
                            i4_ret=menu_nav_go(ui4_page_id, &t_menu_page_hint);
                        }
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }

                return WGLR_OK;

                default:
                    break;
            }
        }
        default:
            break;
    }
    return _item_def_proc_fct(h_widget, ui4_msg, param1, param2);
}

static INT32 _item_range_proc_paint_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    c_wgl_default_msg_proc(h_widget,ui4_msg,param1,param2);

    return WGLR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _item_range_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_range_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32 i4_ret=0;

#ifdef APP_TTS_SUPPORT
    CHAR str_tmp[64] = {0};
    UTF16_T w2s_str[64] = {0};
#endif

    switch (ui4_msg)
    {
    case WGL_MSG_PAINT:
        return _item_range_proc_paint_fct(h_widget,ui4_msg,param1,param2);
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        PAGE_TREE_ITEM_T*   pt_page_tree_item;
        PAGE_TREE_ITEM_T*   pt_page_tree_item_next;
        PAGE_TREE_T*    pt_page_tree;
        INT32           i4_val;
        INT32           i4_val_old;

        INT32           i4_time     = 0;          /* Fast mode: iteration */
        INT32           i4_do_times = 1;          /* Fast mode: do how many times */
        UINT32          ui4_cur_tick;             /* Fast mode: current tick */
        UINT32          ui4_delta_tick;           /* Fast mode: tick delta */

        MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
            __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

        i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_page_tree = pt_page_tree_item->pt_page;
        pt_page_tree_item_next = pt_page_tree_item;

        /* Fast Mode - Determine the i4_do_times */
        if( b_g_fm_enabled &&
            (ui4_keycode == BTN_CURSOR_LEFT || ui4_keycode == BTN_CURSOR_RIGHT)
          )
        {
            if(pt_page_tree_item->t_menuitem.u.t_range.b_fast_mode)
            {
                /* With fast mode */
                if(ui4_fm_last_tick == 0)
                {
                    ui4_fm_last_tick = c_os_get_sys_tick();
                    //Fix Cverity ID = 1147493 Unused value
                    //i4_do_times = 1;
                }
                else  /* ui4_fm_last_tick != 0 */
                {
                    ui4_cur_tick = c_os_get_sys_tick();
                    ui4_delta_tick = ui4_cur_tick - ui4_fm_last_tick;
                    if(ui4_delta_tick < 200)
                    {
                        _increase_delta_idx(&ui1_fm_delta_idx);
                    }
                    ui4_fm_last_tick = ui4_cur_tick;
                }

                i4_do_times = _get_delta_by_delta_idx(ui1_fm_delta_idx);
            }
            else
            {
                /* No fast mode */
                i4_do_times = 1;
            }

        }
        /* Fast Mode end */


        /* If b_always_slider_mode is on, go to slider mode when pressing left
           or right */
        if(b_g_select_is_menu_key && ui4_keycode == BTN_SELECT)
        {
            b_g_select_is_menu_key = FALSE;
            if(pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_SLIDER)
            {
                menu_toast_range_hide();
                menu_set_toast_range_flag(FALSE);
            }
            menu_leave(TRUE, 0);
            return WGLR_OK;
        }
        if(b_always_slider_mode &&
           pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_NORMAL &&
           (ui4_keycode == BTN_CURSOR_LEFT || ui4_keycode == BTN_CURSOR_RIGHT))
        {
            ui4_keycode = BTN_SELECT;
        }

        switch (ui4_keycode)
        {
        case BTN_CURSOR_UP:
            if(pt_page_tree_item->pt_page->e_state != PAGE_TREE_STATE_SLIDER)
            {
                /* use default cursor up logic */
                break;
            }

            do
            {
                pt_page_tree_item_next = DLIST_PREV(pt_page_tree_item_next, t_link);
                if(pt_page_tree_item_next == NULL)
                {
                    pt_page_tree_item_next = DLIST_TAIL(&pt_page_tree->t_item_list);
                }

                if(pt_page_tree_item_next == pt_page_tree_item)
                {
                    break;
                }

            } while(pt_page_tree_item_next->b_hidden == TRUE ||
                    pt_page_tree_item_next->b_enabled ==  FALSE ||
                   pt_page_tree_item_next->t_menuitem.e_item_type != MENU_ITEM_TYPE_RANGE);

            if(pt_page_tree_item == pt_page_tree_item_next)
            {
                return WGLR_OK;
            }

            pt_page_tree->pt_item_focus = pt_page_tree_item_next;

            if(pt_page_tree_item_next->ui2_item_idx < pt_page_tree->i2_offset)
            {
                pt_page_tree->i2_offset = pt_page_tree_item_next->ui2_item_idx;

                i4_ret=_do_layout(pt_page_tree);
                MENU_LOG_ON_FAIL(i4_ret);
            }

            i4_ret=c_wgl_set_focus(pt_page_tree_item_next->h_widget,
                            WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);

            /* update the slider state */
            i4_ret=menu_range_get_val(pt_page_tree_item_next->h_widget, &i4_val);
            MENU_LOG_ON_FAIL(i4_ret);

            menu_toast_range_show(pt_page_tree_item_next->h_widget,
                                  pt_page_tree_item_next->t_menuitem.u.t_range.i4_val_min,
                                  pt_page_tree_item_next->t_menuitem.u.t_range.i4_val_max,
                                  i4_val,
                                  pt_page_tree_item_next->t_menuitem.ui2_msgid_title);
            menu_set_toast_range_flag(TRUE);

        #ifdef APP_TTS_SUPPORT
            c_uc_w2s_strncpy(w2s_tts_content,
                                MLM_MENU_TEXT(ui2_tts_lang, pt_page_tree_item_next->t_menuitem.ui2_msgid_title),
                                _TTS_CNT_MAX_LEN);

            c_snprintf(str_tmp, 63, "%d", i4_val);
            c_uc_ps_to_w2s(str_tmp, w2s_str, 63);
            c_uc_w2s_strncat(w2s_tts_content,
                            w2s_str,
                            _TTS_CNT_MAX_LEN - c_uc_w2s_strlen(w2s_tts_content));

            i4_ret = a_app_tts_play(w2s_tts_content, c_uc_w2s_strlen(w2s_tts_content));
            MENU_LOG_ON_FAIL(i4_ret);
        #endif

            return WGLR_OK;
        case BTN_CURSOR_DOWN:
            if(pt_page_tree_item->pt_page->e_state != PAGE_TREE_STATE_SLIDER)
            {
                /* use default cursor up logic */
                break;
            }

            do
            {
                pt_page_tree_item_next = DLIST_NEXT(pt_page_tree_item_next, t_link);
                if(pt_page_tree_item_next == NULL)
                {
                    pt_page_tree_item_next = DLIST_HEAD(&pt_page_tree->t_item_list);
                }

                if(pt_page_tree_item_next == pt_page_tree_item)
                {
                    break;
                }

            }while(pt_page_tree_item_next->b_hidden == TRUE ||
                   pt_page_tree_item_next->b_enabled ==  FALSE ||
                   pt_page_tree_item_next->t_menuitem.e_item_type != MENU_ITEM_TYPE_RANGE);

            if(pt_page_tree_item == pt_page_tree_item_next)
            {
                return WGLR_OK;
            }

            pt_page_tree->pt_item_focus = pt_page_tree_item_next;

            if(pt_page_tree_item_next->ui2_item_idx >= pt_page_tree->i2_offset + _ITEMS_PER_IPAGE)
            {
                pt_page_tree->i2_offset = pt_page_tree_item_next->ui2_item_idx - _ITEMS_PER_IPAGE + 1;

                i4_ret=_do_layout(pt_page_tree);
                MENU_LOG_ON_FAIL(i4_ret);
            }

            i4_ret=c_wgl_set_focus(pt_page_tree_item_next->h_widget,
                            WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);

            /* update the slider state */
            i4_ret=menu_range_get_val(pt_page_tree_item_next->h_widget, &i4_val);
            MENU_LOG_ON_FAIL(i4_ret);

            menu_toast_range_show(pt_page_tree_item_next->h_widget,
                                  pt_page_tree_item_next->t_menuitem.u.t_range.i4_val_min,
                                  pt_page_tree_item_next->t_menuitem.u.t_range.i4_val_max,
                                  i4_val,
                                  pt_page_tree_item_next->t_menuitem.ui2_msgid_title);
            menu_set_toast_range_flag(TRUE);

        #ifdef APP_TTS_SUPPORT
            c_uc_w2s_strncpy(w2s_tts_content,
                                MLM_MENU_TEXT(ui2_tts_lang, pt_page_tree_item_next->t_menuitem.ui2_msgid_title),
                                _TTS_CNT_MAX_LEN);

            c_snprintf(str_tmp, 63, "%d", i4_val);
            c_uc_ps_to_w2s(str_tmp, w2s_str, 63);
            c_uc_w2s_strncat(w2s_tts_content,
                            w2s_str,
                            _TTS_CNT_MAX_LEN - c_uc_w2s_strlen(w2s_tts_content));

            i4_ret = a_app_tts_play(w2s_tts_content, c_uc_w2s_strlen(w2s_tts_content));
            MENU_LOG_ON_FAIL(i4_ret);
        #endif

            return WGLR_OK;
        case BTN_CURSOR_LEFT:
        {
            if(FALSE==pt_page_tree_item->b_enabled)
            {
                DBG_ERROR(("Disable item \n"));
                return WGLR_OK;
            }

            i4_ret=menu_range_get_val(pt_page_tree_item->h_widget, &i4_val_old);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_val = i4_val_old - i4_do_times < pt_page_tree_item->t_menuitem.u.t_range.i4_val_min
                        ? pt_page_tree_item->t_menuitem.u.t_range.i4_val_min : i4_val_old - i4_do_times;

            /* Fast mode end */
            if (i4_val_old == i4_val)
            {
                return WGLR_OK;
            }
            pt_page_tree_item->t_menuitem.u.t_range.pf_set_val(i4_val);

            i4_ret=menu_range_set_val(pt_page_tree_item->h_widget, i4_val);
            MENU_LOG_ON_FAIL(i4_ret);

            menu_pic_energy_change_set_status();

#ifdef APP_TTS_SUPPORT
            c_snprintf(str_tmp, 63, "%d", i4_val);
            c_uc_ps_to_w2s(str_tmp, w2s_str, 63);
            if (i4_val < 0)
            {
                i4_ret = a_tts_switch_minus_to_minus_string(w2s_str,w2s_str,64);
                MENU_LOG_ON_FAIL(i4_ret == APP_TTSR_OK ? MENUR_OK : i4_ret);
            }
            i4_ret = a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
            MENU_LOG_ON_FAIL(i4_ret);
#endif

            if(pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_SLIDER)
            {
                menu_toast_range_show(pt_page_tree_item->h_widget,
                                      pt_page_tree_item->t_menuitem.u.t_range.i4_val_min,
                                      pt_page_tree_item->t_menuitem.u.t_range.i4_val_max,
                                      i4_val,
                                      pt_page_tree_item->t_menuitem.ui2_msgid_title);
                menu_set_toast_range_flag(TRUE);
            }
            else
            {
                i4_ret=c_wgl_repaint(h_widget, NULL, TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
                //c_dbg_secure_stmt("\n=====_item_range_proc_fct========%d\n",__LINE__);
            }

            return WGLR_OK;
        }
        case BTN_CURSOR_RIGHT:
        {
            if(FALSE==pt_page_tree_item->b_enabled)
            {
                DBG_ERROR(("Disable item \n"));
                return WGLR_OK;
            }
            i4_ret=menu_range_get_val(pt_page_tree_item->h_widget, &i4_val_old);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_val = i4_val_old + i4_do_times > pt_page_tree_item->t_menuitem.u.t_range.i4_val_max
                        ? pt_page_tree_item->t_menuitem.u.t_range.i4_val_max : i4_val_old + i4_do_times;
            /* Fast mode end */
            if (i4_val_old == i4_val)
            {
                return WGLR_OK;
            }
            pt_page_tree_item->t_menuitem.u.t_range.pf_set_val(i4_val);

            i4_ret=menu_range_set_val(pt_page_tree_item->h_widget, i4_val);
            MENU_LOG_ON_FAIL(i4_ret);

            menu_pic_energy_change_set_status();
#ifdef APP_TTS_SUPPORT
            c_snprintf(str_tmp, 63, "%d", i4_val);
            c_uc_ps_to_w2s(str_tmp, w2s_str, 63);
            if (i4_val < 0)
            {
                i4_ret = a_tts_switch_minus_to_minus_string(w2s_str,w2s_str,64);
                MENU_LOG_ON_FAIL(i4_ret == APP_TTSR_OK ? MENUR_OK : i4_ret);
            }
            i4_ret = a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
            MENU_LOG_ON_FAIL(i4_ret);
#endif


            if(pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_SLIDER)
            {
                 menu_toast_range_show(pt_page_tree_item->h_widget,
                                       pt_page_tree_item->t_menuitem.u.t_range.i4_val_min,
                                       pt_page_tree_item->t_menuitem.u.t_range.i4_val_max,
                                       i4_val,
                                       pt_page_tree_item->t_menuitem.ui2_msgid_title);
                 menu_set_toast_range_flag(TRUE);
            }
            else
            {
                i4_ret=c_wgl_repaint(h_widget, NULL, TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }

            return WGLR_OK;
        }
        case BTN_SELECT:

            if(FALSE==pt_page_tree_item->b_enabled)
            {
                DBG_ERROR(("Disable item \n"));
                return WGLR_OK;
            }
            if(pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_NORMAL)
            {
                pt_page_tree_item->pt_page->e_state = PAGE_TREE_STATE_SLIDER;

            #ifdef VIEWPORT_SUPPORT
                a_cfg_set_app_status(APP_CFG_APP_STATUS_MENU_WIDE_MODE);
                a_cfg_update_viewport();
            #endif

                /* update the slider state */
                i4_ret=menu_range_get_val(pt_page_tree_item->h_widget, &i4_val);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_main_set_visibility(FALSE);
                MENU_LOG_ON_FAIL(i4_ret);

                menu_toast_range_show(pt_page_tree_item->h_widget,
                                      pt_page_tree_item->t_menuitem.u.t_range.i4_val_min,
                                      pt_page_tree_item->t_menuitem.u.t_range.i4_val_max,
                                      i4_val,
                                      pt_page_tree_item->t_menuitem.ui2_msgid_title);
                menu_set_toast_range_flag(TRUE);

#if 0
                #ifdef APP_ZOOM_MODE_SUPPORT
                if((pt_page_tree->ui2_msgid_title == MLM_MENU_KEY_VID_PICTURE_TITLE)||
                   (pt_page_tree->ui2_msgid_title == MLM_MENU_KEY_AUD))
                {
                    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_SLIDER));
                }
                #endif
#endif
                i4_ret=menu_hide_help_tip();
                MENU_LOG_ON_FAIL(i4_ret);
                do
                {
                    pt_page_tree_item_next = DLIST_NEXT(pt_page_tree_item_next, t_link);
                    if(pt_page_tree_item_next == NULL)
                    {
                        pt_page_tree_item_next = DLIST_HEAD(&pt_page_tree->t_item_list);
                    }

                    if(pt_page_tree_item_next == pt_page_tree_item)
                    {
                        break;
                    }

                }while(pt_page_tree_item_next->b_hidden == TRUE ||
                    pt_page_tree_item_next->t_menuitem.e_item_type != MENU_ITEM_TYPE_RANGE);

                return WGLR_OK;
            }
            // return WGLR_OK;
            /* go through */
        case BTN_EXIT:
            if(pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_SLIDER)
            {
                pt_page_tree_item->pt_page->e_state = PAGE_TREE_STATE_NORMAL;
            #ifdef VIEWPORT_SUPPORT
                if (a_cfg_get_app_status() == APP_CFG_APP_STATUS_MENU_WIDE_MODE)
                {
                    a_cfg_set_app_status(APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
                }
                a_cfg_update_viewport();
            #endif

                menu_toast_range_hide();
                menu_set_toast_range_flag(FALSE);

             /* hide the slider */
                i4_ret=menu_main_set_visibility(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
                if (MLM_MENU_KEY_V_SIZE == pt_page_tree_item->t_menuitem.ui2_msgid_title
                    || MLM_MENU_KEY_H_SIZE == pt_page_tree_item->t_menuitem.ui2_msgid_title
                    || MLM_MENU_KEY_H_POS == pt_page_tree_item->t_menuitem.ui2_msgid_title
                    || MLM_MENU_KEY_V_POS == pt_page_tree_item->t_menuitem.ui2_msgid_title)
                {
                    menu_pm_refresh();
                }

                i4_ret=menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);

                /* trigger help tip */
                i4_ret=menu_set_and_show_help_tip(MENU_TEXT(pt_page_tree_item->t_menuitem.ui2_msgid_desc));
                MENU_LOG_ON_FAIL(i4_ret);
                return WGLR_OK;
            }
            break;
        case BTN_PREV_PRG:
        case BTN_RETURN:
            if(pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_NORMAL)
            {
                menu_nav_back();
            }
            else if(pt_page_tree_item->pt_page->e_state == PAGE_TREE_STATE_SLIDER)
            {
                pt_page_tree_item->pt_page->e_state = PAGE_TREE_STATE_NORMAL;

                if (a_cfg_get_app_status () == APP_CFG_APP_STATUS_MENU_WIDE_MODE)
                {
                    a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
                }
                a_cfg_update_viewport ();

                menu_toast_range_hide();
                menu_set_toast_range_flag(FALSE);

                /* hide the slider */
                menu_main_set_visibility(TRUE);
            #ifdef APP_ZOOM_MODE_SUPPORT
            if((pt_page_tree->ui2_msgid_title == MLM_MENU_KEY_VID_PICTURE_TITLE)||
            (pt_page_tree->ui2_msgid_title == MLM_MENU_KEY_AUD))
            {
                a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_SLIDER));
            }
            #endif
                if (MLM_MENU_KEY_V_SIZE == pt_page_tree_item->t_menuitem.ui2_msgid_title
                    || MLM_MENU_KEY_H_SIZE == pt_page_tree_item->t_menuitem.ui2_msgid_title
                    || MLM_MENU_KEY_H_POS == pt_page_tree_item->t_menuitem.ui2_msgid_title
                    || MLM_MENU_KEY_V_POS == pt_page_tree_item->t_menuitem.ui2_msgid_title)
                {
                    menu_pm_refresh();
                }

                menu_pm_repaint();

                /* trigger help tip */
                menu_set_and_show_help_tip(MENU_TEXT(pt_page_tree_item->t_menuitem.ui2_msgid_desc));
            }
            return WGLR_OK;
        default:
            break;
        }
    }
    /* Fast mode */
    case WGL_MSG_KEY_UP:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        if(ui4_keycode == BTN_CURSOR_LEFT ||
           ui4_keycode == BTN_CURSOR_RIGHT)
        {
            /* Reset the tick & delta_idx */
            ui4_fm_last_tick = 0;
            ui1_fm_delta_idx = 0;
        }
    }
    /* Fast mode end */

    default:
        break;
    }
    return _item_def_proc_fct(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _item_action_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_text_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    return _item_def_proc_fct(h_widget, ui4_msg, param1, param2);
}

#ifdef APP_TTS_SUPPORT
static INT32 _get_list_items_text(PAGE_TREE_ITEM_T*  pt_page_tree_item, UINT16 ui2_idx, UTF16_T *pw2s_str)
{
    INT32   i4_ret          = MENUR_OK;
    UINT16  ui2_i           = 0;
    UINT16  ui2_elem_num    = 0;
    UTF16_T w2s_str[64] = {0};
    UINT16  ui2_msgid_elem_last = 0;
    UINT16  ui2_msgid_elem_first = 0;

    if (NULL == pt_page_tree_item)
    {
        return MENUR_INV_ARG;
    }

    /* sleep timer  */
    if (MLM_MENU_KEY_TITLE_SLEEP_TIMER == pt_page_tree_item->t_menuitem.ui2_msgid_title)
    {
        /*Klockwork issues */
        if (ui2_idx >= MAX_ELEM_NUM -1)
        {
            return i4_ret;
        }

        if(pt_page_tree_item->t_menuitem.u.t_list.pf_get_text != NULL)
        {
            pt_page_tree_item->t_menuitem.u.t_list.pf_get_text(ui2_idx, w2s_str, 64);
        }
        else
        {
            c_uc_w2s_strcpy(w2s_str,
                            MLM_MENU_TEXT(ui2_tts_lang, pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first + ui2_idx));
        }

        c_memcpy(pw2s_str, w2s_str, sizeof(w2s_str));

        return i4_ret;
    }

    if ( (NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_prev_idx) ||
         (NULL == pt_page_tree_item->t_menuitem.u.t_list.pf_next_idx) )
    {
        ui2_elem_num = pt_page_tree_item->t_menuitem.u.t_list.ui2_elem_num;
        if ((0 != pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_last) &&
            (0 != pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first))
        {
            ui2_msgid_elem_last = pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_last;
            ui2_msgid_elem_first= pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first;
            //Fix Cverity ID : 4491475 Unused value
            ui2_elem_num = (UINT16)((ui2_msgid_elem_last - ui2_msgid_elem_first) + 1);
            MENU_LOG_ON_FAIL(ui2_elem_num);
        }

        if ( menu_is_picture_mode_item(pt_page_tree_item->t_menuitem.ui2_msgid_title))
        {
            ui2_elem_num = get_cust_picture_mode_num();
            DBG_INFO(("\n===============create_pic_mode_no_need_show_cnt_page========%d,%d\n",ui2_elem_num,__LINE__));
        }

        //for(ui2_i=0; ui2_i<ui2_elem_num;ui2_i++)
        {
            ui2_i = ui2_idx;
            /*Klockwork issues */
            if (ui2_i >= MAX_ELEM_NUM -1)
            {
                return i4_ret;
            }
            if(pt_page_tree_item->t_menuitem.u.t_list.pf_get_text != NULL)
            {
                pt_page_tree_item->t_menuitem.u.t_list.pf_get_text(ui2_i, w2s_str, 64);
            }
            else
            {
                c_uc_w2s_strcpy(w2s_str,
                                MLM_MENU_TEXT(ui2_tts_lang, pt_page_tree_item->t_menuitem.u.t_list.ui2_msgid_elem_first + ui2_i));
            }

            c_memcpy(pw2s_str, w2s_str, sizeof(w2s_str));
        }
    }

    return i4_ret;
}
#endif
static BOOL _menu_page_tree_play_tts_skip_item(UINT16 ui2_msgid_title)
{
    BOOL b_title = FALSE;
    /*play tts menu item*/
    switch(ui2_msgid_title)
    {
        case MLM_MENU_KEY_MENU_ASPECT_RATIO :
        case MLM_MENU_KEY_VID_VARIABLE_REFRESH_RATE :
        case MLM_MENU_KEY_TITLE_SLEEP_TIMER :
        case MLM_MENU_KEY_OSD_LANG :
        case MLM_MENU_KEY_AUD_SPEAKER :
        case MLM_MENU_KEY_MENU_ITEM_CC_ENABLED :
        case MLM_MENU_KEY_CC_STL_FONT_STYLE :
        case MLM_MENU_KEY_VID_CON_EHC :
        case MLM_MENU_KEY_FILM_MAKER_MODE :
        case MLM_MENU_KEY_HIDE_FROM_INP_TV  :
        case MLM_MENU_KEY_RATING_ENABLE  :
        case MLM_MENU_KEY_VID_BLUR :
        case MLM_MENU_KEY_VID_DNR :
        case MLM_MENU_KEY_VID_GAME_LOW_LATENCY :
        case MLM_MENU_KEY_TTS_TALKBACK :
        case MLM_MENU_KEY_ITEM_TV_NAME :
           {
              b_title = TRUE;
           }
           break;
        default :
           {
              b_title = FALSE;
           }
           break;
    }
    return b_title;
}
static INT32 _menu_page_tree_play_tts(HANDLE_T h_widget, UINT8 ui1_play_mode)
{
#ifdef APP_TTS_SUPPORT
    INT32 i4_ret = MENUR_OK;
    UINT16  ui2_list_idx = 0;
    UINT16  ui2_list_num = 0;
    UTF16_T w2s_str[64] = {0};
    BOOL    b_visible = FALSE;
    UINT8   ui1_tts_switch_status = APP_CFG_TTS_SWITCH_OFF;

    PAGE_TREE_ITEM_T* pt_page_item = NULL;

    a_cfg_get_tts_switch_status(&ui1_tts_switch_status);
    if (APP_CFG_TTS_SWITCH_OFF == ui1_tts_switch_status)
    {
        DBG_INFO(("_menu_page_tree_play_tts() TTS Switch is off\n"));
        return i4_ret;
    }

    i4_ret=_get_item_data_by_widget(h_widget, &pt_page_item);
    MENU_LOG_ON_FAIL(i4_ret);

    if (NULL == pt_page_item)
    {
        DBG_WARN(("_menu_page_tree_play_tts() get item date fail!\n"));
        return i4_ret;
    }

    c_wgl_get_visibility(h_widget, &b_visible);

    c_memset(w2s_tts_content, 0, sizeof(w2s_tts_content));
    DBG_INFO(("[MENU][%s %s %d] e_item_type = %d,title id => %d play mode => 0x%x\n ",__FILE__,__FUNCTION__,__LINE__,
        pt_page_item->t_menuitem.e_item_type,
        pt_page_item->t_menuitem.ui2_msgid_title,
        ui1_play_mode));
    switch (pt_page_item->t_menuitem.e_item_type)
    {
        case MENU_ITEM_TYPE_LIST:
        case MENU_ITEM_TYPE_LIST_SUBPAGE:
        {
            if (PAGE_TREE_STATE_LISTBOX == pt_page_item->pt_page->e_state)
            {
                i4_ret = c_wgl_do_cmd(h_listbox,
                                      WGL_CMD_LB_GET_ELEM_NUM,
                                      WGL_PACK(&ui2_list_num),
                                      NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_wgl_do_cmd(h_listbox,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_list_idx),
                                      NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                DBG_INFO(("%s() %d: ui2_list_idx=%d,ui2_list_num=%d\n",__FUNCTION__,__LINE__,ui2_list_idx,ui2_list_num));

                if (ui2_list_idx >= 0 && ui2_list_idx < ui2_list_num)
                {
                    _get_list_items_text(pt_page_item, ui2_list_idx, w2s_str);

                    c_uc_w2s_strncpy(w2s_tts_content, w2s_str, _TTS_CNT_MAX_LEN);
                }
                break;
            }

            if (!b_visible)
            {

                if(_menu_page_tree_play_tts_skip_item(pt_page_item->t_menuitem.ui2_msgid_title))
                {
                    DBG_ERROR(("menu item is not visible. timers.\n"));
                }
                else
                {
                    DBG_INFO(("menu item is not visible.@@@@ ERROR. WHY? ui2_msgid_title = %d\n",pt_page_item->t_menuitem.ui2_msgid_title));
                    return i4_ret;
                }
            }

            if(pt_page_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_VID_PIC_MODE_ITEM)
            {
                UTF16_T  w2s_dst[_TTS_CNT_MAX_LEN+1] ;
                SCC_VID_HDR_TYPE_T e_v_type = a_acfg_cust_get_video_type();
                switch(e_v_type)
                {
                    case SCC_VID_PQ_HDR10:
                         c_uc_w2s_strncpy(w2s_tts_content,MLM_MENU_TEXT(ui2_tts_lang, MLM_MENU_KEY_VID_PIC_MODE_HDR10_ITEM),_TTS_CNT_MAX_LEN);
                        break;
                    case SCC_VID_PQ_HLG:
                         c_uc_w2s_strncpy(w2s_tts_content,MLM_MENU_TEXT(ui2_tts_lang, MLM_MENU_KEY_VID_PIC_MODE_HLG_ITEM),_TTS_CNT_MAX_LEN);
                        break;
                    case SCC_VID_PQ_HDR10PLUS:
                        c_uc_w2s_strncpy(w2s_tts_content,MLM_MENU_TEXT(ui2_tts_lang, MLM_MENU_KEY_VID_PIC_MODE_HDR10_PLUS),_TTS_CNT_MAX_LEN);
                        break;
                    case SCC_VID_PQ_DOVI:
                    default:
                        c_uc_w2s_strncpy(w2s_tts_content,MLM_MENU_TEXT(ui2_tts_lang, MLM_MENU_KEY_VID_PIC_MODE_ITEM),_TTS_CNT_MAX_LEN);
                }

            }
            else if (ui1_play_mode&_MENU_TREE_TTS_PLAY_TITLE)
            {
                c_uc_w2s_strncpy(w2s_tts_content,
                                MLM_MENU_TEXT(ui2_tts_lang, pt_page_item->t_menuitem.ui2_msgid_title),
                                _TTS_CNT_MAX_LEN);
            }

            if (ui1_play_mode&_MENU_TREE_TTS_PLAY_VAL)
            {
                ui2_list_idx = pt_page_item->t_menuitem.u.t_list.pf_get_idx();
                DBG_INFO(("[MENU][TTS][%s %d] list idx = %d\n",__FUNCTION__,__LINE__,ui2_list_idx));
                if(pt_page_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_VID_PIC_MODE_ITEM)
                 {
                   if(a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI)
                    {
                      c_uc_w2s_strncat(w2s_tts_content,L" ",c_uc_w2s_strlen(L" "));
                      c_uc_w2s_strncat(w2s_tts_content,L"Dolby vision",c_uc_w2s_strlen(L"Dolby vision"));
                    }
                 }

                if(pt_page_item->t_menuitem.u.t_list.pf_get_text != NULL)
                {
                    pt_page_item->t_menuitem.u.t_list.pf_get_text(ui2_list_idx, w2s_str, 63);
                    c_uc_w2s_strncat(w2s_tts_content,L" ",c_uc_w2s_strlen(L" "));
                    c_uc_w2s_strncat(w2s_tts_content,
                                    w2s_str,
                                    _TTS_CNT_MAX_LEN - c_uc_w2s_strlen(w2s_str));
                }
                else
                {
                    if (pt_page_item->t_menuitem.u.t_list.ui2_msgid_elem_first+ui2_list_idx <= pt_page_item->t_menuitem.u.t_list.ui2_msgid_elem_last)
                    {
                        c_uc_w2s_strncat(w2s_tts_content,L" ",c_uc_w2s_strlen(L" "));
                        c_uc_w2s_strncat(w2s_tts_content,
                                        MLM_MENU_TEXT(ui2_tts_lang, pt_page_item->t_menuitem.u.t_list.ui2_msgid_elem_first+ui2_list_idx),
                                        _TTS_CNT_MAX_LEN - c_uc_w2s_strlen(w2s_tts_content));
                    }
                }
            }

            break;
        }
        case MENU_ITEM_TYPE_ACTION:
        case MENU_ITEM_TYPE_TEXT:
        {
            c_uc_w2s_strncpy(w2s_tts_content,
                            MLM_MENU_TEXT(ui2_tts_lang, pt_page_item->t_menuitem.ui2_msgid_title),
                            _TTS_CNT_MAX_LEN);
            break;
        }
        case MENU_ITEM_TYPE_SUBPAGE:
        case MENU_ITEM_TYPE_MORE_SUBPAGE:
        {
            UTF16_T *pw2s_str = NULL;

            if (MLM_MENU_KEY_OP_VCHIP == pt_page_item->t_menuitem.ui2_msgid_title)
            {
                pw2s_str = menu_atsc_drrt_get_system_name();
                if (pw2s_str != NULL)
                {
                    c_uc_w2s_strncpy(w2s_tts_content, pw2s_str, _TTS_CNT_MAX_LEN);
                }
            }
            else if (MLM_MENU_KEY_MAIN_MENU_SYS_INFO_AND_RESET == pt_page_item->t_menuitem.ui2_msgid_title)
            {
                c_uc_w2s_strncpy(w2s_tts_content,
                                 MLM_MENU_TEXT(ui2_tts_lang,MLM_MENU_KEY_RESET_ADMIN_TTC_PLAY),
                                 _TTS_CNT_MAX_LEN);
            }
            else
            {
                c_uc_w2s_strncpy(w2s_tts_content,
                                 MLM_MENU_TEXT(ui2_tts_lang, pt_page_item->t_menuitem.ui2_msgid_title),
                                 _TTS_CNT_MAX_LEN);
            }

            break;
        }
        case MENU_ITEM_TYPE_RANGE:
        {
            CHAR str_tmp[64] = {0};

            if (ui1_play_mode&_MENU_TREE_TTS_PLAY_TITLE)
            {
                c_uc_w2s_strncpy(w2s_tts_content,
                                MLM_MENU_TEXT(ui2_tts_lang, pt_page_item->t_menuitem.ui2_msgid_title),
                                _TTS_CNT_MAX_LEN);
            }
            if (ui1_play_mode&_MENU_TREE_TTS_PLAY_VAL)
            {
                c_snprintf(str_tmp, 63, "%d", pt_page_item->t_menuitem.u.t_range.pf_get_val());
                c_uc_ps_to_w2s(str_tmp, w2s_str, 63);
                c_uc_w2s_strncat(w2s_tts_content,
                                w2s_str,
                                _TTS_CNT_MAX_LEN - c_uc_w2s_strlen(w2s_tts_content));
                break;
            }
        }
        default:
            DBG_INFO(("Unknow menu item type(%d)\n", pt_page_item->t_menuitem.e_item_type));
            return MENUR_OK;
    }

    //============================================= ZOOM MODE
    CHAR c_my_item[512];
    SIZE_T  c_ps_str_len = 0;
    SIZE_T  c_w2s_str_len = 0;

    c_w2s_str_len = c_uc_w2s_strlen(w2s_tts_content);
    c_ps_str_len = c_w2s_str_len * sizeof(UTF16_T);

    c_uc_w2s_to_ps(w2s_tts_content, c_my_item, c_ps_str_len);

    if((0 == c_strcmp(c_my_item,"Zoom Mode On"))||(0 == c_strcmp(c_my_item,"Zoom Mode Off")))
    {
        DBG_INFO((" ENTER c_my_item[len:%d] = {%s} {left:(%d)}\n",c_ps_str_len,c_my_item,b_btn_left_right_zoom));

        if(TRUE == b_btn_left_right_zoom){
            b_btn_left_right_zoom  = FALSE;
            return MENUR_OK;
        }

    }else{
        b_btn_left_right_zoom  = FALSE;
    }
//=============================================

    UINT8   ui1_force_reboot_flag = ACFG_FORCE_REBOOT_UP_OFF;

    if (c_uc_w2s_strcmp(MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SERVICE_CHECK_ITEM),
                        w2s_tts_content) == 0)
    {
        if (b_is_press_ok_from_check_update)
        {
            i4_ret = a_app_tts_play(w2s_tts_content, c_uc_w2s_strlen(w2s_tts_content));
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            b_is_press_ok_from_check_update = TRUE;
        }
    }
    else if (c_uc_w2s_strcmp(MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_RESET_TV_AD_ID),
                        w2s_tts_content) == 0)
    {
        if (FALSE == b_is_read_reset_advertiser_info)
        {
            i4_ret = a_app_tts_play(w2s_tts_content, c_uc_w2s_strlen(w2s_tts_content));
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            b_is_read_reset_advertiser_info = FALSE;
        }
    }
    else if ((0 == c_strcmp(c_my_item,"eARC  On"))||(0 == c_strcmp(c_my_item,"eARC  Off")))
    {
        if(0 == c_strcmp(c_my_item,"eARC  On"))
        {
            i4_ret = a_app_tts_play(L"e--A--R-C  On", c_uc_w2s_strlen(L"e--A--R-C  On"));
        }
        else
        {
            i4_ret = a_app_tts_play(L"e--A--R-C  Off", c_uc_w2s_strlen(L"e--A--R-C  Off"));
        }
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        a_cfg_cust_get_force_reboot_up_flag(&ui1_force_reboot_flag);
        DBG_LOG_PRINT(("<TTS> %d: ui1_force_reboot_flag=%d\r\n",__LINE__,ui1_force_reboot_flag));

        if (ACFG_FORCE_REBOOT_UP_ON == ui1_force_reboot_flag)
        {
            return MENUR_OK;
        }

        i4_ret = a_app_tts_play(w2s_tts_content, c_uc_w2s_strlen(w2s_tts_content));
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return i4_ret;
#else
    return MENUR_OK;
#endif
}

/*----------------------------------------------------------------------------
 * Name: _cnt_frm_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _cnt_frm_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32 i4_ret=0;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;

            MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
                __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

            switch (ui4_keycode)
            {
            case BTN_RETURN:
                i4_ret=menu_nav_back();
                MENU_LOG_ON_FAIL(i4_ret);
                return WGLR_OK;
            default:
                break;
            }
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32  i4_ret=0;
    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            PAGE_TREE_ITEM_T* pt_page_tree_item;

            i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
            MENU_LOG_ON_FAIL(i4_ret);

            c_wgl_set_highlight_widget(menu_get_backbar_txt_handle());

            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
#ifdef APP_TTS_SUPPORT

            a_app_tts_play(MLM_MENU_TEXT(ui2_tts_lang, MLM_MENU_KEY_HELP_TIP_BACK_BAR),
                            c_uc_w2s_strlen(MLM_MENU_TEXT(ui2_tts_lang, MLM_MENU_KEY_HELP_TIP_BACK_BAR)));
#endif

            return MENUR_OK;
        }
        case WGL_MSG_LOSE_FOCUS:
        {
            c_wgl_set_highlight_widget(NULL_HANDLE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
            break;
        }
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            UINT32 ui4_keycode = (UINT32)param1;

            MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
                __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

            switch(ui4_keycode)
            {
                case BTN_CURSOR_DOWN:
                {
                    PAGE_TREE_T* pt_page;
                    PAGE_TREE_ITEM_T* pt_page_item;
                    UINT32  ui4_page_id;

                    HANDLE_T h_backbar;

                    i4_ret=menu_nav_get_crnt_page(&ui4_page_id);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=_get_page_data_by_id(ui4_page_id, &pt_page);
                    MENU_LOG_ON_FAIL(i4_ret);
                    if ((pt_page->e_state == PAGE_TREE_STATE_LISTBOX)&&
                        ( menu_is_picture_mode_item(pt_page->pt_item_focus->t_menuitem.ui2_msgid_title))
                        )
                    {
                        menu_show_hide_enger_start_icon(TRUE, TRUE);
                    }
                    if(pt_page->e_state == PAGE_TREE_STATE_NORMAL)
                    {
                        /* Normal mode */
                        pt_page_item = DLIST_HEAD(&pt_page->t_item_list);
                        while(pt_page_item != NULL &&
                              (pt_page_item->b_hidden == TRUE || pt_page_item->b_enabled== FALSE))
                        {
                            pt_page_item = DLIST_NEXT(pt_page_item, t_link);
                        }

                        if(pt_page_item != NULL)
                        {
                            i4_ret=c_wgl_set_focus(pt_page_item->h_widget, WGL_NO_AUTO_REPAINT);
                            MENU_LOG_ON_FAIL(i4_ret);

                            pt_page->pt_item_focus = pt_page_item;

                            i4_ret=_do_layout(pt_page);
                            MENU_LOG_ON_FAIL(i4_ret);

                            i4_ret=menu_pm_repaint();
                            MENU_LOG_ON_FAIL(i4_ret);
                        }
                        else
                        {
                            i4_ret=menu_help_tip_keytip_set_focus(h_widget,0,FALSE);
                            MENU_LOG_ON_FAIL(i4_ret);

                            i4_ret=menu_pm_repaint();
                            MENU_LOG_ON_FAIL(i4_ret);
                        }
                    }
                    else if(pt_page->e_state == PAGE_TREE_STATE_LISTBOX)
                    {
                        UINT16  ui2_elem_num = 0;
                        UINT16  ui2_elem_idx;

                        i4_ret=c_wgl_do_cmd(h_listbox,
                                     WGL_CMD_LB_GET_ELEM_NUM,
                                     WGL_PACK(&ui2_elem_num),
                                     NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        if(ui2_elem_num == 0)
                        {
                            /* Do nothing */
                            return WGLR_OK;
                        }

                        ui2_elem_idx = 0;

                        i4_ret=c_wgl_do_cmd(h_listbox,
                                     WGL_CMD_LB_HLT_ELEM,
                                     WGL_PACK(ui2_elem_idx),
                                     NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        b_is_page_show = TRUE;
                        i4_ret=c_wgl_set_focus(pt_page->pt_item_focus->h_widget, WGL_NO_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                        if (MENU_ITEM_TYPE_LIST == pt_page->pt_item_focus->t_menuitem.e_item_type)
                        {
                            if(pt_page->pt_item_focus->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_DEMO_MODE)
                            {
                                pt_page->pt_item_focus->t_menuitem.ui2_msgid_desc=_menu_page_tree_get_demo_mode_help_text_id(0);
                            }
                            i4_ret=_show_elem_help_tips(
                                pt_page->pt_item_focus->t_menuitem.ui2_msgid_desc,
                                pt_page->pt_item_focus->t_menuitem.u.t_list.ui2_msgid_elem_desc_first,
                                ui2_elem_idx,
                                TRUE);
                            MENU_LOG_ON_FAIL(i4_ret);
                            if(pt_page->pt_item_focus->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_DEMO_MODE)
                            {
                                pt_page->pt_item_focus->t_menuitem.ui2_msgid_desc=MLM_MENU_KEY_DEMO_MODE_HELP;
                            }
                        }
                        else if (MENU_ITEM_TYPE_LISTBOX == pt_page->pt_item_focus->t_menuitem.e_item_type)
                        {
                            i4_ret=_show_elem_help_tips(
                                pt_page->pt_item_focus->t_menuitem.ui2_msgid_desc,
                                pt_page->pt_item_focus->t_menuitem.u.t_listbox.ui2_msgid_elem_desc_first,
                                ui2_elem_idx,
                                TRUE);
                            MENU_LOG_ON_FAIL(i4_ret);
                        }

                    #if( defined(APP_SUPPORT_PIC_HOT_KEY) )
                        _listbox_timer_reset(pt_page->pt_item_focus);
                    #endif

                        menu_get_backbar_handle(&h_backbar);

                        i4_ret = c_wgl_repaint(h_backbar,NULL,TRUE);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    return WGLR_OK;
                }

            case BTN_CURSOR_UP:
            {
                INT32     i4_ret = 0;
                PAGE_TREE_T* pt_page;
                UINT32  ui4_page_id;

                i4_ret=menu_nav_get_crnt_page(&ui4_page_id);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=_get_page_data_by_id(ui4_page_id, &pt_page);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_set_focus_on_homebar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

            #if( defined(APP_SUPPORT_PIC_HOT_KEY) )
                _listbox_timer_reset(pt_page->pt_item_focus);
            #endif

                return WGLR_OK;
            }

            case BTN_CURSOR_LEFT:
            #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
            #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                PAGE_TREE_T* pt_page;
                UINT32  ui4_page_id;
                PAGE_TREE_ITEM_T* pt_page_item;
                UINT16              ui2_visible_item = 0;
                GL_RECT_T           t_rect;
                HANDLE_T             h_last_shadow_item = NULL_HANDLE;
                BOOL                 b_sleep_timer_page = FALSE;

                if (BTN_SELECT == ui4_keycode)
                {
                    b_g_select_is_menu_key = FALSE;
                }
                c_wgl_set_highlight_widget(NULL_HANDLE);

                i4_ret=menu_nav_get_crnt_page(&ui4_page_id);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=_get_page_data_by_id(ui4_page_id, &pt_page);
                MENU_LOG_ON_FAIL(i4_ret);

                menu_list_arrow_hide(FALSE);

                if(pt_page->e_state == PAGE_TREE_STATE_LISTBOX)
                {
                    b_is_subpage_state = FALSE;

                    i4_ret=c_wgl_set_visibility(pt_page->h_cnt_frm, WGL_SW_NORMAL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=c_wgl_set_visibility(h_listbox, WGL_SW_HIDE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    /*Adjust last shadow position*/
                    DLIST_FOR_EACH(pt_page_item, &pt_page->t_item_list, t_link)
                    {
                        if(pt_page_item->b_hidden == FALSE)
                        {
                            ui2_visible_item += 1;
                        }
                    }
                    t_rect.i4_left = CONTENT_X;
                    t_rect.i4_right = CONTENT_X + CONTENT_H;
                    t_rect.i4_top = MENU_ITEM_V_HEIGHT * (ui2_visible_item)+ CONTENT_Y;
                    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

                    menu_pm_get_last_shadow_item(&h_last_shadow_item);
                    i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    if(_is_one_listbox_mode(pt_page))
                    {
                        i4_ret=menu_nav_back();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        i4_ret=c_wgl_do_cmd(h_listbox,
                                     WGL_CMD_LB_SET_ELEM_NUM,
                                     WGL_PACK(0),
                                     NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret=menu_main_set_title(pt_page->ui2_msgid_title);
                        MENU_LOG_ON_FAIL(i4_ret);

                        pt_page->e_state = PAGE_TREE_STATE_NORMAL;

                    #ifdef APP_HDR_SUPPORT

                        menu_doly_vision_logo_show(FALSE);
                        if((pt_page->ui2_msgid_title == MLM_MENU_KEY_VID_PICTURE_TITLE)&&
                            ( a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI))
                        {
                        /*
                            GL_RECT_T   t_rect;
                            t_rect.i4_left = CONTENT_X + 269-120;
                            t_rect.i4_right = t_rect.i4_left + 233;
                            t_rect.i4_top = 120;
                            t_rect.i4_bottom = t_rect.i4_top + 64;
                        */
                            menu_doly_vision_resize_logo(MENU_DOLBY_LOGO_POS_PICTURE);

                            menu_doly_vision_logo_show(TRUE);
                        }
                    #endif

                        /*when sleep timer enable . the text may be show different according to the count down time*/
                        b_sleep_timer_page = menu_focus_item_is_the_assign_item(MLM_MENU_KEY_TITLE_SLEEP_TIMER);
                        if(b_sleep_timer_page)
                        {
                             i4_ret=menu_pm_refresh();
                             MENU_LOG_ON_FAIL(i4_ret);
                        }

                        /*end*/
                        i4_ret=menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret=c_wgl_set_focus(pt_page->pt_item_focus->h_widget, WGL_ASYNC_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }

                    c_timer_stop(h_listbox_timer);
                    b_hot_key_enter = FALSE;
                }
                else
                {
                    i4_ret=menu_nav_back();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                return WGLR_OK;
            }
            default:
                break;
            }
            break;
        }
        default:
            break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _homebar_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32 i4_ret=0;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            PAGE_TREE_ITEM_T* pt_page_tree_item;

            i4_ret=_get_item_data_by_widget(h_widget, &pt_page_tree_item);
            MENU_LOG_ON_FAIL(i4_ret);

            /* trigger help tip */
            i4_ret=menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
            MENU_LOG_ON_FAIL(i4_ret);

            return WGLR_OK;
        }
        case WGL_MSG_LOSE_FOCUS:
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
            break;
        }
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            UINT32 ui4_keycode = (UINT32)param1;

            MENU_DEBUG_KEY( DBG_LOG_PRINT(("[MENU][TREE][KEY]{%s,%d} h_widget:0x%X, ui4_keycode:0x%X \n",
                __FUNCTION__, __LINE__, h_widget, ui4_keycode )); );

            switch(ui4_keycode)
            {
            case BTN_CURSOR_DOWN:
            {
                PAGE_TREE_T*        pt_page;
                UINT32                ui4_page_id;

                i4_ret=menu_nav_get_crnt_page(&ui4_page_id);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=_get_page_data_by_id(ui4_page_id, &pt_page);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_set_focus_on_backbar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

            #if( defined(APP_SUPPORT_PIC_HOT_KEY) )
                _listbox_timer_reset(pt_page->pt_item_focus);
            #endif

                return WGLR_OK;
            }
            case BTN_SELECT:
            {
                HANDLE_T            h_last_shadow_item = NULL_HANDLE;
                PAGE_TREE_T*        pt_page;
                UINT32                ui4_page_id;

                c_wgl_set_highlight_widget(NULL_HANDLE);

                b_g_select_is_menu_key = FALSE;
                b_hot_key_enter = FALSE;
                c_timer_stop(h_listbox_timer);

                menu_pm_get_last_shadow_item(&h_last_shadow_item);
                i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE_RECURSIVE);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=menu_nav_get_crnt_page(&ui4_page_id);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=_get_page_data_by_id(ui4_page_id, &pt_page);
                MENU_LOG_ON_FAIL(i4_ret);

                pt_page->e_state = PAGE_TREE_STATE_NORMAL;
                i4_ret=c_wgl_set_visibility(h_listbox, WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);

                menu_list_arrow_hide(FALSE);

                ui2_list_hlt_before_hlt = 0xFFFF;
                b_is_subpage_state = FALSE;// list item list box state set false

                i4_ret=menu_nav_go_home_menu();
                MENU_LOG_ON_FAIL(i4_ret);
                return WGLR_OK;
            }
            case BTN_RETURN:
                {
                    PAGE_TREE_T*        pt_page;
                    UINT32                ui4_page_id;
                    PAGE_TREE_ITEM_T*   pt_page_item;
                    UINT16              ui2_visible_item = 0;
                    GL_RECT_T           t_rect;
                    HANDLE_T            h_last_shadow_item = NULL_HANDLE;
                    BOOL                 b_sleep_timer_page = FALSE;

                    i4_ret=menu_nav_get_crnt_page(&ui4_page_id);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=_get_page_data_by_id(ui4_page_id, &pt_page);
                    MENU_LOG_ON_FAIL(i4_ret);

                    if(pt_page->e_state == PAGE_TREE_STATE_LISTBOX)
                    {
                        i4_ret=c_wgl_set_visibility(pt_page->h_cnt_frm, WGL_SW_NORMAL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret=c_wgl_set_visibility(h_listbox, WGL_SW_HIDE);
                        MENU_LOG_ON_FAIL(i4_ret);

                        menu_list_arrow_hide(FALSE);
                        b_is_subpage_state = FALSE;

                        /*Adjust last shadow position*/
                        DLIST_FOR_EACH(pt_page_item, &pt_page->t_item_list, t_link)
                        {
                            if(pt_page_item->b_hidden == FALSE)
                            {
                                ui2_visible_item += 1;
                            }
                        }
                        t_rect.i4_left = CONTENT_X;
                        t_rect.i4_right = CONTENT_X + CONTENT_H;
                        t_rect.i4_top = MENU_ITEM_V_HEIGHT * (ui2_visible_item)+ CONTENT_Y;
                        t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

                        menu_pm_get_last_shadow_item(&h_last_shadow_item);
                        i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
                        MENU_LOG_ON_FAIL(i4_ret);

                    #ifdef APP_HDR_SUPPORT

                        menu_doly_vision_logo_show(FALSE);

                        if((pt_page->ui2_msgid_title == MLM_MENU_KEY_VID_PICTURE_TITLE)&&
                            (a_icl_custom_get_dolby_vision_status() == 1 ))
                        {
                        /*
                            GL_RECT_T   t_rect;
                            t_rect.i4_left = CONTENT_X + 209-120;
                            t_rect.i4_right = t_rect.i4_left + 233;
                            t_rect.i4_top = 120;
                            t_rect.i4_bottom = t_rect.i4_top + 64;
                        */
                            menu_doly_vision_resize_logo(MENU_DOLBY_LOGO_POS_PICTURE);

                            menu_doly_vision_logo_show(TRUE);
                        }
                    #endif

                        if(_is_one_listbox_mode(pt_page))
                        {
                            i4_ret=menu_nav_back();
                            MENU_LOG_ON_FAIL(i4_ret);
                        }
                        else
                        {
                            i4_ret=c_wgl_do_cmd(h_listbox,
                                         WGL_CMD_LB_SET_ELEM_NUM,
                                         WGL_PACK(0),
                                         NULL);
                            MENU_LOG_ON_FAIL(i4_ret);

                            i4_ret=c_wgl_set_focus(pt_page->pt_item_focus->h_widget, WGL_NO_AUTO_REPAINT);
                            MENU_LOG_ON_FAIL(i4_ret);

                            i4_ret=menu_main_set_title(pt_page->ui2_msgid_title);
                            MENU_LOG_ON_FAIL(i4_ret);

                            pt_page->e_state = PAGE_TREE_STATE_NORMAL;
                            /*For DTV00595241*/
                            b_sleep_timer_page = menu_focus_item_is_the_assign_item(MLM_MENU_KEY_TITLE_SLEEP_TIMER);
                            if(b_sleep_timer_page)
                            {
                                 i4_ret=menu_pm_refresh();
                                 MENU_LOG_ON_FAIL(i4_ret);
                            }
                            i4_ret=menu_pm_repaint();
                            MENU_LOG_ON_FAIL(i4_ret);
                        }

                        b_hot_key_enter = FALSE;
                        c_timer_stop(h_listbox_timer);
                    }
                    else
                    {
                        i4_ret=menu_nav_back();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    return WGLR_OK;
                }

            default:
                break;
            }
            break;
        }
        default:
            break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _create_item_widget
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _create_item_widget(
    PAGE_TREE_T*  pt_page_tree,
    PAGE_TREE_ITEM_T* pt_page_tree_item)
{
    INT32 i4_ret=0;
    MENU_ITEM_T* pt_menu_item = &pt_page_tree_item->t_menuitem;

    /* create widget */
    switch(pt_page_tree_item->t_menuitem.e_item_type)
    {
        case MENU_ITEM_TYPE_SUBPAGE:
            i4_ret = menu_action_create(pt_page_tree->h_cnt_frm,
                                        (INT32)(pt_page_tree_item->ui2_item_idx % pt_page_tree->ui2_items_per_ipage),
                                        _item_subpage_proc_fct,
                                        &pt_page_tree_item->h_widget);
            MENU_LOG_ON_FAIL(i4_ret);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }

            break;

        case MENU_ITEM_TYPE_MORE_SUBPAGE:
            i4_ret = menu_more_item_create(pt_page_tree->h_cnt_frm,
                                            (INT32)(pt_page_tree_item->ui2_item_idx % pt_page_tree->ui2_items_per_ipage),
                                            _item_subpage_proc_fct,
                                            &pt_page_tree_item->h_widget);
            MENU_LOG_ON_FAIL(i4_ret);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }
            break;

        case MENU_ITEM_TYPE_ACTION:
            i4_ret = menu_action_create(pt_page_tree->h_cnt_frm,
                                        (INT32)(pt_page_tree_item->ui2_item_idx % pt_page_tree->ui2_items_per_ipage),
                                        _item_action_proc_fct,
                                        &pt_page_tree_item->h_widget);
            MENU_LOG_ON_FAIL(i4_ret);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }

            break;
        case MENU_ITEM_TYPE_LIST:
            i4_ret = menu_list_create(pt_page_tree->h_cnt_frm,
                                      (INT32)(pt_page_tree_item->ui2_item_idx % pt_page_tree->ui2_items_per_ipage),
                                      pt_menu_item->u.t_list.ui2_elem_num,
                                      _item_list_proc_fct,
                                      &pt_page_tree_item->h_widget);
            MENU_LOG_ON_FAIL(i4_ret);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }

            break;
        case MENU_ITEM_TYPE_LIST_SUBPAGE:
            i4_ret = menu_list_create(pt_page_tree->h_cnt_frm,
                                      (INT32)(pt_page_tree_item->ui2_item_idx % pt_page_tree->ui2_items_per_ipage),
                                      pt_menu_item->u.t_list_subpage.ui2_elem_num,
                                      _item_list_subpage_proc_fct,
                                      &pt_page_tree_item->h_widget);
            MENU_LOG_ON_FAIL(i4_ret);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }

            break;
        case MENU_ITEM_TYPE_LISTBOX:
            i4_ret = menu_action_create(pt_page_tree->h_cnt_frm,
                                        (INT32)(pt_page_tree_item->ui2_item_idx % pt_page_tree->ui2_items_per_ipage),
                                        _item_listbox_proc_fct,
                                        &pt_page_tree_item->h_widget);
            MENU_LOG_ON_FAIL(i4_ret);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }

            break;
        case MENU_ITEM_TYPE_RANGE:
        {
            MENU_RANGE_STYLE_T e_style;

            if(pt_menu_item->u.t_range.e_range_style == MENU_ITEM_RANGE_STYLE_BAR)
            {
                e_style = MENU_RANGE_STYLE_BAR;
            }
            else
            {
                e_style = MENU_RANGE_STYLE_POINT;
            }

            i4_ret = menu_range_create(pt_page_tree->h_cnt_frm,
                                       (INT32)(pt_page_tree_item->ui2_item_idx % pt_page_tree->ui2_items_per_ipage),
                                       pt_menu_item->u.t_range.i4_val_min,
                                       pt_menu_item->u.t_range.i4_val_max,
                                       e_style,
                                       _item_range_proc_fct,
                                       &pt_page_tree_item->h_widget);
            MENU_LOG_ON_FAIL(i4_ret);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }
        }
            break;
        case MENU_ITEM_TYPE_TEXT:
        {
            i4_ret = menu_text_create(pt_page_tree->h_cnt_frm,
                                      (INT32)(pt_page_tree_item->ui2_item_idx % pt_page_tree->ui2_items_per_ipage),
                                      _item_text_proc_fct,
                                      &pt_page_tree_item->h_widget);
            MENU_LOG_ON_FAIL(i4_ret);
            if(i4_ret != MENUR_OK)
            {
                return i4_ret;
            }
        }
            break;
        default:
            break;
    }

    i4_ret = c_wgl_set_visibility(pt_page_tree_item->h_widget,
                         WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    /* attach data */
    i4_ret = c_wgl_do_cmd(pt_page_tree_item->h_widget,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_page_tree_item),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return MENUR_FAIL;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _add_item
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _add_item(
    PAGE_TREE_T*  pt_page_tree,
    MENU_ITEM_T*  pt_menu_item,
    UINT16*       pui2_item_id)
{
    UINT16 ui2_item_id;
    UINT16 ui2_item_idx;
    PAGE_TREE_ITEM_T* pt_page_tree_item;

    if(pt_page_tree == NULL ||
       pt_menu_item == NULL)
    {
        return MENUR_FAIL;
    }

    ui2_item_id = pt_page_tree->ui2_item_id_counter;

    if(pt_page_tree->ui2_item_num >= pt_page_tree->ui2_max_item_num)
    {
        DBG_ERROR(("<MENU>PM: Too many items. \r\n"));
        return MENUR_FAIL;
    }

    if(DLIST_TAIL(&pt_page_tree->t_item_list) != NULL)
    {
        ui2_item_idx = (UINT16)(DLIST_TAIL(&pt_page_tree->t_item_list)->ui2_item_idx + 1);
    }
    else
    {
        ui2_item_idx = 0;
    }

    /* allocate the data to page tree item */
    pt_page_tree_item = (PAGE_TREE_ITEM_T*)c_mem_alloc(sizeof(PAGE_TREE_ITEM_T));
    if(pt_page_tree_item == NULL)
    {
        return MENUR_OUT_OF_MEMORY;
    }

    c_memset(&pt_page_tree_item->t_menuitem,
             0,
             sizeof(MENU_ITEM_T));
    c_memcpy(&pt_page_tree_item->t_menuitem,
             pt_menu_item,
             sizeof(MENU_ITEM_T));
    pt_page_tree_item->pt_page = pt_page_tree;
    pt_page_tree_item->ui2_item_id = ui2_item_id;
    pt_page_tree_item->ui2_item_idx= ui2_item_idx;
    pt_page_tree_item->b_enabled = TRUE;
    pt_page_tree_item->b_hidden = FALSE;
    pt_page_tree_item->b_auto_chg_lang = TRUE;
    pt_page_tree_item->h_widget = NULL_HANDLE;
    pt_page_tree_item->pf_is_enabled = NULL;
    pt_page_tree_item->pf_is_hidden = NULL;

    *pui2_item_id = ui2_item_id;
    ++pt_page_tree->ui2_item_num;
    ++pt_page_tree->ui2_item_id_counter;

    DLIST_INSERT_TAIL(pt_page_tree_item, &pt_page_tree->t_item_list, t_link);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _remove_item
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _remove_item(
    PAGE_TREE_T*  pt_page_tree,
    PAGE_TREE_ITEM_T* pt_page_item)
{
    INT32 i4_ret=0;
    if(pt_page_tree->pt_item_focus == pt_page_item)
    {
        /* TODO */
        return MENUR_FAIL;
    }

    /* free the resource */
    DLIST_REMOVE(pt_page_item, &pt_page_tree->t_item_list, t_link);
    if(pt_page_item->h_widget != NULL_HANDLE)
    {
        i4_ret=c_wgl_destroy_widget(pt_page_item->h_widget);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    c_mem_free(pt_page_item);

    /* do layout */
    i4_ret=_do_layout(pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _enable_item
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _enable_item(
    PAGE_TREE_ITEM_T* pt_page_item,
    BOOL     b_enable)
{
    INT32 i4_ret;

    /* check if the menu item exists */
    if(pt_page_item->h_widget != NULL_HANDLE)
    {
        i4_ret = c_wgl_enable(pt_page_item->h_widget,
                      b_enable);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    pt_page_item->b_enabled = b_enable;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _hide_item
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _hide_item(PAGE_TREE_ITEM_T* pt_page_item, BOOL     b_hide)
{
    INT32 i4_ret;

    /*check if the menu item exists */
    if(pt_page_item->h_widget != NULL_HANDLE)
    {
        i4_ret = c_wgl_set_visibility(pt_page_item->h_widget,
                                      b_hide ? WGL_SW_HIDE : WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
        //c_wgl_repaint(pt_page_item->h_widget,NULL,FALSE);
    }

    pt_page_item->b_hidden = b_hide;

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _set_focus_2_special_item
 *
 * Description:  This case is for lock and unlock picture mode focus issue.
 * when select lock picture mode lock the custom picture mode then focus should on unlock picture mode .
 * when select  unock picture mode lock the custom picture mode then focus should on lock picture mode .
 *  Attention please the page->t_item_list is not a double cycle list .
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static PAGE_TREE_ITEM_T* _set_focus_2_special_item_for_lock_pic_mode(PAGE_TREE_ITEM_T*   pt_page_item,
                                                                              PAGE_TREE_T*        pt_page)

{
    PAGE_TREE_ITEM_T* pt_page_item_pre = pt_page_item;
    PAGE_TREE_ITEM_T* pt_page_item_head = NULL_HANDLE;
//    UINT16                   ui2_msgid_title = MLM_MENU_KEY_EMPTY;

    if(pt_page_item_pre == NULL)
        {
        DBG_INFO(("\n!!!<MENU> can't get right menu item  menu_page_tree.c line:%d\n",__LINE__));
        return pt_page_item;
        }

    pt_page_item_head = DLIST_HEAD(&pt_page->t_item_list);

    if(pt_page_item_pre->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_MENU_ITEM_UNLOCK_PIC_MODE)
    {
        /*last focus item is lock picture mode item or unlock picture mode item. Because  they are exclusive and when choose one of then the  focus should be on another..*/
    do
    {
        pt_page_item_pre  = DLIST_PREV(pt_page_item_pre, t_link);
        if(pt_page_item_pre == NULL)
        {
                DBG_INFO(("\n!!!<MENU> can't get right menu item  menu_page_tree.c line:%d\n",__LINE__));
                return pt_page_item;
        }
        if((pt_page_item_pre->b_enabled == TRUE && pt_page_item_pre->b_hidden == FALSE)&&
               (pt_page_item_pre->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_MENU_ITEM_LOCK_PIC_MODE))
        {
                /*focus should on lock or unlock pictuer mode item*/
                return pt_page_item_pre;
        }
        }while(pt_page_item_pre != pt_page_item_head);

        DBG_ERROR(("\n!!!<MENU> can't get right menu item  menu_page_tree.c line:%d\n",__LINE__));
        return pt_page_item_pre;
    }
    else
    {
        /*For lock picture &unlock picture mode other case.*/
        /*For e.g   delete picture mode maybe hide the find the previous visible focus item.*/
        do
        {
            pt_page_item_pre  = DLIST_PREV(pt_page_item_pre, t_link);
            if(pt_page_item_pre == NULL)
            {
                DBG_INFO(("\n!!!<MENU> can't get right menu item  menu_page_tree.c line:%d\n",__LINE__));
                return pt_page_item;
    }
            if(pt_page_item_pre->b_enabled == TRUE && pt_page_item_pre->b_hidden == FALSE)
            {
                /*find out the focusble item*/
    return pt_page_item_pre;
            }
        }while(pt_page_item_pre != pt_page_item_head);

        DBG_ERROR(("\n!!!<MENU> can't get right menu item  menu_page_tree.c line:%d\n",__LINE__));
        return pt_page_item_pre;
    }

}

static INT32 _get_next_focusable_item(
    PAGE_TREE_T*        pt_page,
    PAGE_TREE_ITEM_T**  ppt_page_item)
{
    PAGE_TREE_ITEM_T* pt_page_item_next;
    PAGE_TREE_ITEM_T* pt_page_item_start;

    if(ppt_page_item == NULL)
    {
        return MENUR_INV_ARG;
    }

    /* no element */
    if(pt_page->ui2_item_num == 0)
    {
        *ppt_page_item = NULL;
        return MENUR_OK;
    }

    if(pt_page->pt_item_focus == NULL)
    {
        pt_page_item_start = DLIST_TAIL(&pt_page->t_item_list);
    }
    else
    {
        pt_page_item_start = pt_page->pt_item_focus;
    }
    pt_page_item_next  = pt_page_item_start;

    if(pt_page_item_next->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_MENU_ITEM_UNLOCK_PIC_MODE)
    {
        pt_page_item_next = _set_focus_2_special_item_for_lock_pic_mode(pt_page_item_next,pt_page);
    }
    else
    {
    do
    {
        pt_page_item_next  = DLIST_NEXT(pt_page_item_next, t_link);
        if(pt_page_item_next == NULL)
        {
            pt_page_item_next = DLIST_HEAD(&pt_page->t_item_list);
        }
        if(pt_page_item_next->b_enabled == TRUE && pt_page_item_next->b_hidden == FALSE)
        {
            break;
        }
    }while(pt_page_item_next != pt_page_item_start);
    }

    if(pt_page_item_next->b_enabled == FALSE || pt_page_item_next->b_hidden == TRUE)
    {
        /* no focusable item */
        *ppt_page_item = NULL;
    }
    else
    {
        *ppt_page_item = pt_page_item_next;
    }

    return MENUR_OK;
}


static INT32 _get_last_focusable_item(
    PAGE_TREE_T*        pt_page,
    PAGE_TREE_ITEM_T**  ppt_page_item)
{
    PAGE_TREE_ITEM_T* pt_page_item_last;

    if(ppt_page_item == NULL)
    {
        return MENUR_INV_ARG;
    }

    /* no element */
    if(pt_page->ui2_item_num == 0)
    {
        *ppt_page_item = NULL;
        return MENUR_OK;
    }

    pt_page_item_last = DLIST_TAIL(&pt_page->t_item_list);

    do
    {
        if(pt_page_item_last->b_enabled == TRUE && pt_page_item_last->b_hidden == FALSE)
        {
            break;
        }
        pt_page_item_last = DLIST_PREV(pt_page_item_last,t_link);
    }while(pt_page_item_last != NULL);

    if(NULL == pt_page_item_last)
    {
        /* no focusable item */
        *ppt_page_item = NULL;
    }
    else
    {
        if (pt_page_item_last->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_MENU_ITEM_DELETE_PIC_MODE)
        {
            *ppt_page_item = _set_focus_2_special_item_for_lock_pic_mode(pt_page_item_last,pt_page);
        }
        else
        {
            *ppt_page_item = pt_page_item_last;
        }
    }

    return MENUR_OK;
}

static INT32 _item_list_subpage_change_style(PAGE_TREE_ITEM_T* pt_page_item)
{
    INT32   i4_ret = MENUR_OK;
    UTF16_T w2s_str[64+1] = {0};

    if (NULL == pt_page_item)
    {
        return MENUR_INV_ARG;
    }

    if (MLM_MENU_KEY_ITEM_TV_NAME == pt_page_item->t_menuitem.ui2_msgid_title)
    {
        WGL_LB_ITEM_T               at_items[3];
        WGL_LB_ITEM_IMG_SUIT_T t_img_suit_left;
        WGL_LB_ITEM_IMG_SUIT_T t_img_suit_right;

        i4_ret = c_wgl_do_cmd(pt_page_item->h_widget,
                              WGL_CMD_LB_DEL_ALL,
                              NULL,
                              NULL );
        MENU_LOG_ON_FAIL(i4_ret);

        if (pt_page_item->t_menuitem.u.t_list_subpage.pf_get_text)
        {
            pt_page_item->t_menuitem.u.t_list_subpage.pf_get_text(0, w2s_str, 64);
        }

        c_memset(&t_img_suit_left, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
        t_img_suit_left.h_highlight          = NULL_HANDLE;
        t_img_suit_left.h_selected_highlight = NULL_HANDLE;

        c_memset(&t_img_suit_right, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
        t_img_suit_right.h_highlight          = NULL_HANDLE;
        t_img_suit_right.h_selected_highlight = NULL_HANDLE;

        at_items[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
        at_items[0].data.pt_img_suit = &t_img_suit_left;

        at_items[1].e_col_type       = LB_COL_TYPE_TEXT;
        at_items[1].data.pw2s_text   = w2s_str;

        at_items[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
        at_items[2].data.pt_img_suit = &t_img_suit_right;

        i4_ret = c_wgl_do_cmd(pt_page_item->h_widget,
                              WGL_CMD_LB_APPEND_ELEM,
                              at_items,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_page_item->h_widget,
                              WGL_CMD_LB_HLT_ELEM_VISIBLE,
                              WGL_PACK(0),
                              WGL_PACK(0));
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set long text scroll effect */
        WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect = {0};
        t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
        t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                       WGL_LB_TEXT_SCRL_STL_REPEAT;
        t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
        t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
        t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

        i4_ret = c_wgl_do_cmd (pt_page_item->h_widget,
                                WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                                WGL_PACK (& t_hlt_elem_effect),
                                NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        extern INT32 menu_list_adjust_rect_ex(HANDLE_T h_widget);

        i4_ret=menu_list_adjust_rect_ex(pt_page_item->h_widget);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: _chg_lang
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 _chg_lang(PAGE_TREE_T* pt_page_tree)
{
    INT32 i4_ret=0;
    PAGE_TREE_ITEM_T* pt_page_item;

    DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    DLIST_FOR_EACH(pt_page_item, &pt_page_tree->t_item_list, t_link)
    {
        if(pt_page_item->b_auto_chg_lang == FALSE)
        {
            continue;
        }

        switch(pt_page_item->t_menuitem.e_item_type)
        {
            case MENU_ITEM_TYPE_LIST:
                if(pt_page_item->t_menuitem.u.t_list.pf_get_text != NULL)
                {
                    UINT16  ui2_i;
                    UTF16_T w2s_str[64] = {0};

                    /* Set Title language */
                    MENU_LOG_ON_FAIL(menu_list_set_title_text(pt_page_item->h_widget,
                                                              MENU_TEXT(pt_page_item->t_menuitem.ui2_msgid_title)));

        #ifdef APP_HDR_SUPPORT
                    if ( menu_is_picture_mode_item(pt_page_item->t_menuitem.ui2_msgid_title))
                    {
                        UINT8 u8_HDR_type = a_acfg_cust_get_video_type();
                        DBG_LOG_PRINT(("[MENU][PIC][%s %d] hdr type: %d\n",__FUNCTION__,__LINE__, u8_HDR_type ));

                        if( u8_HDR_type == SCC_VID_PQ_HDR10 )
                        {
                            MENU_LOG_ON_FAIL(menu_list_set_title_text(pt_page_item->h_widget,
                                                                      MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HDR10_ITEM)));
                        }
                        else if( u8_HDR_type == SCC_VID_PQ_HLG )
                        {
                            MENU_LOG_ON_FAIL(menu_list_set_title_text(pt_page_item->h_widget,
                                                                      MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HLG_ITEM)));
                        }
                        else if ( u8_HDR_type == SCC_VID_PQ_HDR10PLUS )
                        {
                            MENU_LOG_ON_FAIL(menu_list_set_title_text(pt_page_item->h_widget,
                                                                      MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HDR10_PLUS)));
                        }
                        else if ( u8_HDR_type == SCC_VID_PQ_DOVI)
                        {
                            MENU_LOG_ON_FAIL(menu_list_set_title_text(pt_page_item->h_widget,
                                                                      MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_ITEM)));
                        /*
                            GL_RECT_T	t_rect;
                            ISO_639_LANG_T	s639_lang;
                            MENU_LOG_ON_FAIL(a_cfg_get_gui_lang(s639_lang));
                            if(c_strncmp(s639_lang,"spa",3) == 0 )
                            {
                                t_rect.i4_left	 = CONTENT_X + 269-75;
                            }
                            else
                            {
                                t_rect.i4_left	 = CONTENT_X + 269-60;
                            }
                            t_rect.i4_right = t_rect.i4_left + 233;
                            t_rect.i4_top = 120;
                            t_rect.i4_bottom = t_rect.i4_top + 64;
                        */
                            menu_doly_vision_resize_logo(MENU_DOLBY_LOGO_POS_PICTURE);

//                            menu_doly_vision_logo_show(TRUE);
                        }
                        else
                        {
                            MENU_LOG_ON_FAIL(menu_list_set_title_text(pt_page_item->h_widget,
                                                                      MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_ITEM)));
                        }

                    }
        #endif

                    if ((NULL == pt_page_item->t_menuitem.u.t_list.pf_prev_idx) ||
                        (NULL == pt_page_item->t_menuitem.u.t_list.pf_next_idx))
                    {
                        /*
                        DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} e_item_type:%d, ui2_msgid_title:%d, ui2_msgid_desc:%d,\n",
                            __FILE__, __LINE__,
                            pt_page_item->t_menuitem.e_item_type,
                            pt_page_item->t_menuitem.ui2_msgid_title,
                            pt_page_item->t_menuitem.ui2_msgid_desc
                            ));
                            */

                        /*
                        DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} t_list.ui2_elem_num:%d, ui2_msgid_elem_first:%d, ui2_msgid_elem_last:%d \n",
                            __FILE__, __LINE__,
                            pt_page_item->t_menuitem.u.t_list.ui2_elem_num,
                            pt_page_item->t_menuitem.u.t_list.ui2_msgid_elem_first,
                            pt_page_item->t_menuitem.u.t_list.ui2_msgid_elem_last
                            ));
                        */

                        UINT16  ui2_elem_num = pt_page_item->t_menuitem.u.t_list.ui2_elem_num;
                        if( menu_is_picture_mode_item(pt_page_item->t_menuitem.ui2_msgid_title) )
                        {
                            ui2_elem_num = get_cust_picture_mode_num();

                            MENU_DEBUG_PIC_MODE( DBG_LOG_PRINT(("[MENU][TREE][PIC]{%s,%d} 2-ui2_elem_num:%d \n", __FUNCTION__, __LINE__, ui2_elem_num )); );

                            i4_ret = c_wgl_do_cmd(pt_page_item->h_widget,
                                                  WGL_CMD_LB_SET_ELEM_NUM,
                                                  WGL_PACK(ui2_elem_num),
                                                  NULL);
                            MENU_LOG_ON_FAIL(i4_ret);
                        }


                        /* Set elements language */
                        for (ui2_i = 0;
                             //ui2_i < pt_page_item->t_menuitem.u.t_list.ui2_elem_num;
                             ui2_i < ui2_elem_num;
                             ui2_i++)
                        {
                            pt_page_item->t_menuitem.u.t_list.pf_get_text(ui2_i, w2s_str, 64);

                            //SIZE_T w2s_str_len = c_uc_w2s_strlen(w2s_str);
                            //DBG_LOG_PRINT(("[MENU]{%s,%d} w2s_str_len:%d, w2s_str: [%s] \n", __FILE__, __LINE__, w2s_str_len, menu_custom_get_char_string( w2s_str ) ));
                          #if 1
                            MENU_LOG_ON_FAIL(menu_list_set_text(pt_page_item->h_widget, ui2_i, w2s_str));
                          #else
                            do{
                                INT32 ret = menu_list_set_text(pt_page_item->h_widget, ui2_i, w2s_str);
                                if (ret < 0)
                                {
                                    DBG_LOG_PRINT(("<MENU> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret));
                                    char tmp[128]={0};
                                    c_uc_w2s_to_ps(w2s_str, tmp, 127);
                                    DBG_LOG_PRINT(("<MENU> h_widget:0x%X, ui2_i:%d, tmp:%s \n",
                                        pt_page_item->h_widget, ui2_i, tmp ));
                                }
                            }while(FALSE);
                          #endif
                        }
                    }
                    else if (pt_page_item->t_menuitem.ui2_msgid_title == MLM_MENU_KEY_MENU_ASPECT_RATIO &&
                             pt_page_item->t_menuitem.u.t_list.pf_get_idx != NULL)
                    {
                        ui2_i = pt_page_item->t_menuitem.u.t_list.pf_get_idx();
                        pt_page_item->t_menuitem.u.t_list.pf_get_text(ui2_i, w2s_str, 64);
                        MENU_LOG_ON_FAIL(menu_list_set_text(pt_page_item->h_widget, 0, w2s_str));
                    }
                }
                else
                {
                    MENU_LOG_ON_FAIL(menu_list_chg_lang(pt_page_item->h_widget,
                                       pt_page_item->t_menuitem.ui2_msgid_title,
                                       pt_page_item->t_menuitem.u.t_list.ui2_msgid_elem_first,
                                       pt_page_item->t_menuitem.u.t_list.ui2_msgid_elem_last));
                }
                i4_ret=menu_list_adjust_rect(pt_page_item->h_widget);
                MENU_LOG_ON_FAIL(i4_ret);
                break;
            case MENU_ITEM_TYPE_LIST_SUBPAGE:
            {
                UTF16_T w2s_str[64];

                if(pt_page_item->t_menuitem.u.t_list_subpage.pf_get_text != NULL)
                {
                    UINT16  ui2_i;

                    /* Set Title language */
                    i4_ret=menu_list_set_title_text(pt_page_item->h_widget,
                                             MENU_TEXT(pt_page_item->t_menuitem.ui2_msgid_title));
                    MENU_LOG_ON_FAIL(i4_ret);

                    /* Set elements language */
                    for (ui2_i = 0;
                         ui2_i < pt_page_item->t_menuitem.u.t_list_subpage.ui2_elem_num;
                         ui2_i++)
                    {
                        pt_page_item->t_menuitem.u.t_list_subpage.pf_get_text(ui2_i, w2s_str, 64);
                        i4_ret=menu_list_set_text(pt_page_item->h_widget,
                                           ui2_i,
                                           w2s_str);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }
                else
                {
                    i4_ret=menu_list_chg_lang(pt_page_item->h_widget,
                                               pt_page_item->t_menuitem.ui2_msgid_title,
                                               pt_page_item->t_menuitem.u.t_list_subpage.ui2_msgid_elem_first,
                                               pt_page_item->t_menuitem.u.t_list_subpage.ui2_msgid_elem_last);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                i4_ret=menu_list_adjust_rect(pt_page_item->h_widget);
                MENU_LOG_ON_FAIL(i4_ret);

                _item_list_subpage_change_style(pt_page_item);

                break;
            }
            case MENU_ITEM_TYPE_LISTBOX:
                i4_ret=menu_action_chg_lang(pt_page_item->h_widget,
                                     pt_page_item->t_menuitem.ui2_msgid_title,
                                     MLM_MENU_KEY_EMPTY);
                MENU_LOG_ON_FAIL(i4_ret);
                break;

            case MENU_ITEM_TYPE_ACTION:
                i4_ret=menu_action_chg_lang(pt_page_item->h_widget,
                                     pt_page_item->t_menuitem.ui2_msgid_title,
                                     MLM_MENU_KEY_EMPTY);
                MENU_LOG_ON_FAIL(i4_ret);
                break;
            case MENU_ITEM_TYPE_SUBPAGE:
            case MENU_ITEM_TYPE_MORE_SUBPAGE:
                if (MLM_MENU_KEY_OP_VCHIP == pt_page_item->t_menuitem.ui2_msgid_title)
                {
                    i4_ret = c_wgl_do_cmd(pt_page_item->h_widget,
                                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                                          WGL_PACK(menu_atsc_drrt_get_system_name()),
                                          WGL_PACK(c_uc_w2s_strlen(
                                            menu_atsc_drrt_get_system_name())));
                }
                else
                {
                    i4_ret=menu_action_chg_lang(pt_page_item->h_widget,
                                         pt_page_item->t_menuitem.ui2_msgid_title,
                                         MLM_MENU_KEY_EMPTY);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                break;
            case MENU_ITEM_TYPE_RANGE:
                i4_ret=menu_range_chg_lang(pt_page_item->h_widget,
                                    pt_page_item->t_menuitem.ui2_msgid_title);
                MENU_LOG_ON_FAIL(i4_ret);
                break;
            case MENU_ITEM_TYPE_TEXT:
                i4_ret=menu_text_chg_lang(pt_page_item->h_widget,
                                   pt_page_item->t_menuitem.ui2_msgid_title);
                MENU_LOG_ON_FAIL(i4_ret);
                break;

            default:
                DBG_ERROR(("<MENU>Unknown type"));
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_change_title_indentation
 *
 * Description:
 *      Changing the title to indentation when SB was connected to TV
 * items.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static UINT16 menu_page_tree_change_title_indentation(UINT16 ui2_msgid_title)
{
    UINT16 ui2_tmp_msgid_title = ui2_msgid_title;

    if(ui2_msgid_title == MLM_MENU_KEY_AUD_BASS)
    ui2_tmp_msgid_title= MLM_MENU_KEY_AUD_BASS_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_AUD_TREBLE)
    ui2_tmp_msgid_title= MLM_MENU_KEY_AUD_TREBLE_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_AUD_SRD)
    ui2_tmp_msgid_title= MLM_MENU_KEY_AUD_SRD_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_AUD_SRS_TRUVOLUME)
    ui2_tmp_msgid_title= MLM_MENU_KEY_AUD_SRS_TRUVOLUME_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_AUD_SPEAKER)
    ui2_tmp_msgid_title= MLM_MENU_KEY_AUD_SPEAKER_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_DIALOGUE_ENHANCER)
    ui2_tmp_msgid_title= MLM_MENU_KEY_DIALOGUE_ENHANCER_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_EARC_MODE)
    ui2_tmp_msgid_title =MLM_MENU_KEY_EARC_MODE_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_AUD_BAL)
    ui2_tmp_msgid_title= MLM_MENU_KEY_AUD_BAL_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_EARC_MODE)
    ui2_tmp_msgid_title= MLM_MENU_KEY_EARC_MODE_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_AUD_SRS_TRUVOLUME)
    ui2_tmp_msgid_title = MLM_MENU_KEY_AUD_SRS_TRUVOLUME_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_AUD_DIGITAL_AUDIO_OUT)
    ui2_tmp_msgid_title= MLM_MENU_KEY_AUD_DIGITAL_AUDIO_OUT_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_AUD_DIGITAL_AUDIO_OUT)
    ui2_tmp_msgid_title = MLM_MENU_KEY_AUD_DIGITAL_AUDIO_OUT_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_AUD_LATENCY)
    ui2_tmp_msgid_title = MLM_MENU_KEY_AUD_LATENCY_INDENTATION;

    else if(ui2_msgid_title == MLM_MENU_KEY_AUD_LINEOUT)
    ui2_tmp_msgid_title= MLM_MENU_KEY_AUD_LINEOUT_INDENTATION;

    return ui2_tmp_msgid_title;
}
/*----------------------------------------------------------------------------
 * Name: _refresh
 *
 * Description:
 *      The refresh function will update the enable states and values of menu
 *  items.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 _refresh(PAGE_TREE_T* pt_page)
{
    INT32 i4_ret=0;
    PAGE_TREE_ITEM_T* pt_page_item;
    HANDLE_T    h_focus = NULL_HANDLE;
    HANDLE_T    h_back_bar = NULL_HANDLE;
    HANDLE_T    h_home_bar = NULL_HANDLE;
    UINT32      ui4_cnt_page = 0;
    BOOL        i4_bsoundbarsettings = (acfg_custom_get_enable_soundbarsettings() & acfg_custom_get_soundbarsettings_ready());

    DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    i4_ret=c_wgl_get_focus(&h_focus);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_get_backbar_handle(&h_back_bar);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_get_homebar_handle(&h_home_bar);
    MENU_LOG_ON_FAIL(i4_ret);

    extern BOOL b_3d_mode_playing;
    b_3d_mode_playing = a_tv_custom_is_3D_mode_playing();

    /* traverse the item list */
    DLIST_FOR_EACH(pt_page_item, &pt_page->t_item_list, t_link)
    {
        if(i4_bsoundbarsettings == TRUE)
        {
            pt_page_item->t_menuitem.ui2_msgid_title = menu_page_tree_change_title_indentation(pt_page_item->t_menuitem.ui2_msgid_title);
        }

        /* auto enable */
        if(pt_page_item->pf_is_enabled != NULL)
        {
            BOOL    b_enable = pt_page_item->pf_is_enabled();

            if(h_focus == pt_page_item->h_widget &&
               b_enable == FALSE )
            {
                if((pt_page_item->t_menuitem.e_item_type == MENU_ITEM_TYPE_RANGE) &&
                    (pt_page->e_state == PAGE_TREE_STATE_SLIDER))
                {
                    pt_page->e_state = PAGE_TREE_STATE_NORMAL;

                    c_wgl_set_highlight_widget(NULL_HANDLE);

                      menu_toast_range_hide();
                     /* hide the slider */
                    i4_ret=menu_main_set_visibility(TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    /* trigger help tip */
                    i4_ret=menu_set_and_show_help_tip(MENU_TEXT(pt_page_item->t_menuitem.ui2_msgid_desc));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                MENU_LOG_ON_FAIL(c_wgl_set_focus(pt_page->h_cnt_frm, WGL_NO_AUTO_REPAINT));

                h_focus = pt_page->h_cnt_frm;
            }

            i4_ret=_enable_item(pt_page_item, b_enable);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        /* auto hide */
        if(pt_page_item->pf_is_hidden != NULL)
        {
            BOOL    b_hidden = pt_page_item->pf_is_hidden();

            if(h_focus == pt_page_item->h_widget &&
               b_hidden == TRUE)
            {
                MENU_LOG_ON_FAIL(c_wgl_set_focus(pt_page->h_cnt_frm, WGL_NO_AUTO_REPAINT));
                h_focus = pt_page->h_cnt_frm;
            }

            MENU_LOG_ON_FAIL(_hide_item(pt_page_item, b_hidden));
        }

        //DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

        /* update the value of menu items */
        switch(pt_page_item->t_menuitem.e_item_type)
        {
            case MENU_ITEM_TYPE_LIST:
            {
                UTF16_T w2s_str[64]     = {0};
                UINT16 ui2_list_box_idx = 0;
                UINT16 ui2_list_idx     = 0;
                UINT16 ui2_hlt_pos      = 0;

#ifdef APP_AUD_LANUAGE_CUSTOM_SUPPORT
                extern UINT16 ui2_g_audio_stream_idx;
                if (MLM_MENU_KEY_AUD_DIGITAL_PREFERENCE == pt_page_item->t_menuitem.ui2_msgid_title)
                {
                    ui2_list_idx = ui2_g_audio_stream_idx >= menu_custom_get_aud_lang_num() ?
                                    0 : ui2_g_audio_stream_idx;
                }
                else
#endif
                {
                    if (pt_page_item->t_menuitem.u.t_list.pf_get_idx)
                        ui2_list_idx = pt_page_item->t_menuitem.u.t_list.pf_get_idx();
                }
                DBG_INFO(("[%s %d]status  = %d b_enabled = %d \n",__FUNCTION__,__LINE__,pt_page_item->pt_page->e_state,pt_page_item->b_enabled));
                if((pt_page->pt_item_focus == pt_page_item)&&
                   (pt_page_item->pt_page->e_state == PAGE_TREE_STATE_LISTBOX) && (pt_page_item->b_enabled))
                {

                    if (MLM_MENU_KEY_AUD_ANALOG_PREFERENCE == pt_page_item->t_menuitem.ui2_msgid_title||
                        MLM_MENU_KEY_AUD_DIGITAL_PREFERENCE == pt_page_item->t_menuitem.ui2_msgid_title)
                    {
                        BOOL    b_hide = FALSE;

                        if ( pt_page_item->pf_is_hidden != NULL)
                        {
                            b_hide = pt_page_item->pf_is_hidden();
                        }

                        if (b_hide)
                        {
                            UINT16  ui2_title = MLM_MENU_KEY_AUD_ANALOG_PREFERENCE == pt_page_item->t_menuitem.ui2_msgid_title ?
                                                    MLM_MENU_KEY_AUD_DIGITAL_PREFERENCE : MLM_MENU_KEY_AUD_ANALOG_PREFERENCE;

                            PAGE_TREE_ITEM_T* pt_page_item_next;
                            PAGE_TREE_ITEM_T* pt_page_item_start;

                            pt_page_item_next = pt_page_item;
                            pt_page_item_start = pt_page_item;

                            do{
                                pt_page_item_next  = DLIST_NEXT(pt_page_item_next, t_link);

                                if(pt_page_item_next == NULL)
                                {
                                    pt_page_item_next = DLIST_HEAD(&pt_page->t_item_list);
                                }

                                if(pt_page_item_next->t_menuitem.ui2_msgid_title == ui2_title
                                   && pt_page_item_next->pf_is_hidden() == FALSE)
                                {
                                    pt_page->pt_item_focus = pt_page_item_next;
                                    pt_page_item = pt_page_item_next;

                                    MENU_LOG_ON_FAIL(_hide_item(pt_page_item, FALSE));
                                    menu_main_set_title(ui2_title);

                                    break;
                                }
                                else if (pt_page_item_next->t_menuitem.ui2_msgid_title == ui2_title
                                         && pt_page_item_next->pf_is_hidden() == TRUE)
                                {
                                    break;
                                }
                            }while(pt_page_item_next != pt_page_item_start);

                        }
                    }

                    MENU_LOG_ON_FAIL(_insert_list_box_items(pt_page_item));
                    ui2_list_idx = pt_page_item->t_menuitem.u.t_list.pf_get_idx();

                    /* Highlight the current one */
                    if(ui2_list_idx >= pt_page_item->t_menuitem.u.t_list.ui2_elem_num)
                    {
                        ui2_list_idx = 0;
                    }

                    ui2_list_box_idx = _cvt_menu_idx_2_listbox_idx(ui2_list_idx);
                    DBG_INFO(("[%s %d] ui2_list_box_idx = %d\n",__FUNCTION__,__LINE__,ui2_list_box_idx));
                    if ((UINT16)-1 != ui2_list_box_idx)
                    {
                        if (h_focus == h_home_bar||
                            h_focus == h_back_bar||
                            menu_help_tip_get_focus() == TRUE)
                        {
                            ui2_list_box_idx = (ui2_list_hlt_before_hlt != 0xFFFF)
                                                ? ui2_list_hlt_before_hlt : 0;

                            ui2_hlt_pos = (ui2_list_box_idx > MENU_PAGE_TREE_MAX_ITEM)
                                                ? MENU_PAGE_TREE_MAX_ITEM : ui2_list_box_idx;
                            DBG_INFO(("[%s %d]ui2_list_hlt_before_hlt  = %d ui2_hlt_pos = %d \n",__FUNCTION__,__LINE__,ui2_list_hlt_before_hlt,ui2_hlt_pos));

                            MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                             WGL_CMD_LB_HLT_ELEM_VISIBLE,
                                             WGL_PACK(ui2_list_box_idx),
                                             WGL_PACK(ui2_hlt_pos)));

                            menu_list_arrow_state_update(h_listbox, BTN_INVALID, FALSE);

                            MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                             WGL_CMD_LB_UNHLT_ELEM,
                                             WGL_PACK(ui2_list_hlt_before_hlt),
                                             WGL_PACK(NULL)));
                        }
                        else
                        {
                            ui2_hlt_pos = (ui2_list_box_idx > MENU_PAGE_TREE_MAX_ITEM)
                                                ? MENU_PAGE_TREE_MAX_ITEM : ui2_list_box_idx;
                            DBG_INFO(("[%s %d]ui2_list_hlt_before_hlt  = %d ui2_hlt_pos = %d ui2_list_box_idx = %d\n",__FUNCTION__,__LINE__,ui2_list_hlt_before_hlt,ui2_hlt_pos,ui2_list_box_idx));

                            MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_listbox,
                                             WGL_CMD_LB_HLT_ELEM_VISIBLE,
                                             WGL_PACK(ui2_list_box_idx),
                                             WGL_PACK(ui2_hlt_pos)));
                            menu_list_arrow_state_update(h_listbox, BTN_INVALID, FALSE);
                        }
                    }
                }
                else if((pt_page->pt_item_focus == pt_page_item)&&(!pt_page_item->b_enabled)&&(pt_page_item->pt_page->e_state == PAGE_TREE_STATE_LISTBOX) )
                {
                    MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_page_item->pt_page->h_cnt_frm, WGL_SW_NORMAL));
                    MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_listbox, WGL_SW_HIDE));
                    pt_page_item->pt_page->e_state = PAGE_TREE_STATE_NORMAL;

                }
                else if ((pt_page->pt_item_focus == pt_page_item)&&
                        (pt_page_item->pt_page->e_state == PAGE_TREE_STATE_NORMAL) && (pt_page_item->pf_is_hidden))
                {
                    if (MLM_MENU_KEY_AUD_ANALOG_PREFERENCE == pt_page_item->t_menuitem.ui2_msgid_title||
                        MLM_MENU_KEY_AUD_DIGITAL_PREFERENCE == pt_page_item->t_menuitem.ui2_msgid_title)
                    {
                        BOOL    b_hide = pt_page_item->pf_is_hidden();

                        if (b_hide)
                        {
                            UINT16  ui2_title = MLM_MENU_KEY_AUD_ANALOG_PREFERENCE == pt_page_item->t_menuitem.ui2_msgid_title ?
                                                MLM_MENU_KEY_AUD_DIGITAL_PREFERENCE : MLM_MENU_KEY_AUD_ANALOG_PREFERENCE;

                            PAGE_TREE_ITEM_T* pt_page_item_next;
                            PAGE_TREE_ITEM_T* pt_page_item_start;

                            pt_page_item_next = pt_page_item;
                            pt_page_item_start = pt_page_item;

                            do{
                                pt_page_item_next  = DLIST_NEXT(pt_page_item_next, t_link);

                                if(pt_page_item_next == NULL)
                                {
                                    pt_page_item_next = DLIST_HEAD(&pt_page->t_item_list);
                                }

                                if(pt_page_item_next->t_menuitem.ui2_msgid_title == ui2_title
                                   && pt_page_item_next->pf_is_hidden() == FALSE)
                                {
                                    pt_page->pt_item_focus = pt_page_item_next;
                                    pt_page_item = pt_page_item_next;

                                    MENU_LOG_ON_FAIL(_hide_item(pt_page_item, FALSE));
                                    menu_main_set_title(ui2_title);

                                    break;
                                }
                                else if (pt_page_item_next->t_menuitem.ui2_msgid_title == ui2_title
                                         && pt_page_item_next->pf_is_hidden() == TRUE)
                                {
                                    break;
                                }
                            }while(pt_page_item_next != pt_page_item_start);

                        }
                    }
                }

            #ifdef APP_HDR_SUPPORT
                if(( a_acfg_cust_get_video_type() != SCC_VID_PQ_DOVI)&&
                    menu_page_get_dolby_vision_visible())
                {
                    menu_doly_vision_logo_show(FALSE);
                }
                else if(( a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI)&&!menu_page_get_dolby_vision_visible())
                {
                    if((pt_page->ui2_msgid_title == MLM_MENU_KEY_VID_PICTURE_TITLE)&&
                      (pt_page_item->pt_page->e_state == PAGE_TREE_STATE_NORMAL))
                    {
                    /*
                        ISO_639_LANG_T	s639_lang;
                        MENU_LOG_ON_FAIL(a_cfg_get_gui_lang(s639_lang));

                        GL_RECT_T   t_rect;
                        if(c_strncmp(s639_lang,"spa",3) == 0 )
                        {
                            t_rect.i4_left	 = CONTENT_X + 269-75;
                        }
                        else
                        {
                            t_rect.i4_left	 = CONTENT_X + 269-60;
                        }
                        //t_rect.i4_left = CONTENT_X + 269-60;
                        t_rect.i4_right = t_rect.i4_left + 233;
                        t_rect.i4_top = 120;
                        t_rect.i4_bottom = t_rect.i4_top + 64;
                    */
                        menu_doly_vision_resize_logo(MENU_DOLBY_LOGO_POS_PICTURE);
                        // menu_doly_vision_logo_show(TRUE);
                    }
                #ifdef NEVER
                    else if(menu_is_picture_mode_item(pt_page_item->t_menuitem.ui2_msgid_title))
                    {
                        t_rect.i4_left = CONTENT_X + 235;
                        t_rect.i4_right = t_rect.i4_left + 49;
                        t_rect.i4_top = 30;
                        t_rect.i4_bottom = t_rect.i4_top + 64;
                        menu_doly_vision_resize_logo(t_rect);
                        menu_doly_vision_logo_show(TRUE);
                    }
                #endif /* NEVER */
                }
            #endif

                if ((NULL == pt_page_item->t_menuitem.u.t_list.pf_next_idx) &&
                    (NULL == pt_page_item->t_menuitem.u.t_list.pf_get_text))
                {
                    i4_ret=menu_list_set_idx(pt_page_item->h_widget, ui2_list_idx);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                if ((NULL == pt_page_item->t_menuitem.u.t_list.pf_next_idx)&&
                    (NULL != pt_page_item->t_menuitem.u.t_list.pf_get_text))
                {
                    INT16     ui2_i = 0;
                    UINT16    ui2_elem_num = pt_page_item->t_menuitem.u.t_list.ui2_elem_num;;
                    DBG_INFO(("[%s %d]\n",__FUNCTION__,__LINE__));

                    //DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} ui2_elem_num:%d \n", __FUNCTION__, __LINE__, ui2_elem_num )); );

                    if (menu_is_picture_mode_item(pt_page_item->t_menuitem.ui2_msgid_title))
                    {
                        ui2_elem_num = get_cust_picture_mode_num();

                        //DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} 2-ui2_elem_num:%d \n", __FUNCTION__, __LINE__, ui2_elem_num )); );

                        i4_ret =c_wgl_do_cmd(pt_page_item->h_widget,
                                              WGL_CMD_LB_SET_ELEM_NUM,
                                              WGL_PACK(ui2_elem_num),
                                              NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_HDR_SUPPORT
                        DBG_INFO(("[%s %d] hdr type = %d\n",__FUNCTION__,__LINE__,a_acfg_cust_get_video_type()));
                        if((a_acfg_cust_get_video_type() == SCC_VID_PQ_HDR10 ))
                        {
                            i4_ret=menu_list_set_title_text(pt_page_item->h_widget,
                                MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HDR10_ITEM));
                        }
                        else if(a_acfg_cust_get_video_type() == SCC_VID_PQ_HLG )
                        {
                            i4_ret=menu_list_set_title_text(pt_page_item->h_widget,
                                MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HLG_ITEM));
                        }
                        else if(a_acfg_cust_get_video_type() == SCC_VID_PQ_HDR10PLUS )
                        {
                            i4_ret=menu_list_set_title_text(pt_page_item->h_widget,
                                MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_HDR10_PLUS));
                        }
                        else
                        {
                            i4_ret=menu_list_set_title_text(pt_page_item->h_widget,
                                MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_ITEM));
                        }
                        MENU_LOG_ON_FAIL(i4_ret);

                        if(pt_page_item->pt_page->e_state == PAGE_TREE_STATE_LISTBOX
                            && pt_page->pt_item_focus == pt_page_item)
                        {
                            menu_main_set_title(MLM_MENU_KEY_VID_PIC_MODE_ITEM);
                        }
#endif
                    }

                    i4_ret=menu_list_set_idx(pt_page_item->h_widget, ui2_list_idx);
                    MENU_LOG_ON_FAIL(i4_ret);

                    for (ui2_i = 0;
                         ui2_i < ui2_elem_num;
                         ui2_i++)
                    {
                        pt_page_item->t_menuitem.u.t_list.pf_get_text(ui2_i, w2s_str, 64);
                        i4_ret=menu_list_set_text(pt_page_item->h_widget, ui2_i, w2s_str);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }


                if ((NULL != pt_page_item->t_menuitem.u.t_list.pf_next_idx) &&
                    (NULL != pt_page_item->t_menuitem.u.t_list.pf_get_text))
                {
                    pt_page_item->t_menuitem.u.t_list.pf_get_text(ui2_list_idx, w2s_str, 64);
                    i4_ret=menu_list_set_text(pt_page_item->h_widget,
                                              0,
                                              w2s_str);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=menu_list_set_idx(pt_page_item->h_widget, 0);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                if ((NULL != pt_page_item->t_menuitem.u.t_list.pf_next_idx)&&
                    (NULL == pt_page_item->t_menuitem.u.t_list.pf_get_text))
                {
                    i4_ret=menu_list_set_text(pt_page_item->h_widget,
                                              0,
                                              MENU_TEXT(pt_page_item->t_menuitem.u.t_list.ui2_msgid_elem_first+ui2_list_idx));
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=menu_list_set_idx(pt_page_item->h_widget, 0);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                switch (pt_page_item->t_menuitem.ui2_msgid_title)
                {
                    case MLM_MENU_KEY_INPUT_SOURCE:
                        h_g_input_source_wgt = pt_page_item->h_widget;
                        break;
                    case MLM_MENU_KEY_AUD_DIGITAL_PREFERENCE:
                        h_g_aud_lang_list_wgt = pt_page_item->h_widget;
                        break;
                    default:
                        break;

                }

                i4_ret = menu_list_adjust_rect(pt_page_item->h_widget);
                MENU_LOG_ON_FAIL(i4_ret);
                break;
            }
            case MENU_ITEM_TYPE_LIST_SUBPAGE:
            {
                UINT16 ui2_list_idx =
                    pt_page_item->t_menuitem.u.t_list_subpage.pf_get_idx();

                i4_ret=menu_list_set_idx(pt_page_item->h_widget, ui2_list_idx);
                MENU_LOG_ON_FAIL(i4_ret);

                /* refresh text infomation */
                if(pt_page_item->t_menuitem.u.t_list_subpage.pf_get_text != NULL)
                {
                    UINT16  ui2_i;
                    UTF16_T w2s_str[64] = {0};

                    /* Set elements language */
                    for (ui2_i = 0;
                         ui2_i < pt_page_item->t_menuitem.u.t_list_subpage.ui2_elem_num;
                         ui2_i++)
                    {
                        pt_page_item->t_menuitem.u.t_list_subpage.pf_get_text(ui2_i, w2s_str, 64);
                        i4_ret=menu_list_set_text(pt_page_item->h_widget, ui2_i, w2s_str);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }

                if (MLM_MENU_KEY_CC_STL == pt_page_item->t_menuitem.ui2_msgid_title)
                {
                    DBG_INFO(("%s() Line %d: h_widget = %x \n", __FUNCTION__, __LINE__, pt_page_item->h_widget));
                    h_g_cc_digital_style_wgt = pt_page_item->h_widget;
                }

                i4_ret=menu_list_adjust_rect(pt_page_item->h_widget);
                MENU_LOG_ON_FAIL(i4_ret);

                _item_list_subpage_change_style(pt_page_item);

                break;
            }
            case MENU_ITEM_TYPE_RANGE:
            {
                INT32 i4_val =
                    pt_page_item->t_menuitem.u.t_range.pf_get_val();

                i4_ret=menu_range_set_val(pt_page_item->h_widget, i4_val);
                MENU_LOG_ON_FAIL(i4_ret);

                menu_pic_energy_change_set_status();

                i4_ret=c_wgl_do_cmd(pt_page_item->h_widget,
                             WGL_CMD_PG_SET_POS,
                             WGL_PACK(i4_val),
                             NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                 break;
            }
            case MENU_ITEM_TYPE_TEXT:
            {
                /* refresh text information */
                if (pt_page_item->t_menuitem.u.t_text.pf_get_text != NULL)
                {
                    UTF16_T w2s_str[64];

                    pt_page_item->t_menuitem.u.t_text.pf_get_text(w2s_str, 64);
                    i4_ret=menu_text_set_text(pt_page_item->h_widget, w2s_str);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                break;
            }
            case MENU_ITEM_TYPE_SUBPAGE:
            case MENU_ITEM_TYPE_MORE_SUBPAGE:
            {
                if (MLM_MENU_KEY_OP_VCHIP == pt_page_item->t_menuitem.ui2_msgid_title)
                {
                    i4_ret = c_wgl_do_cmd(pt_page_item->h_widget,
                                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                                          WGL_PACK(menu_atsc_drrt_get_system_name()),
                                          WGL_PACK(c_uc_w2s_strlen(
                                            menu_atsc_drrt_get_system_name())));
                }
                break;
            }
            default:
                break;
        }
    }
    _chk_item_enable_for_help_tip(pt_page->pt_item_focus);

    /* If in slider state and current item is disabled or hidden,
       pause the menu directly */
    if(pt_page->pt_item_focus != NULL &&
       pt_page->pt_item_focus->t_menuitem.e_item_type == MENU_ITEM_TYPE_RANGE &&
       (pt_page->pt_item_focus->b_hidden)&&
       pt_page->e_state == PAGE_TREE_STATE_SLIDER)
    {
        a_amb_pause_app(MENU_NAME);
        return MENUR_OK;
    }

    /* If in list box state and current item is hidden,
     * pause the menu directly
     */
    if(pt_page->pt_item_focus != NULL &&
       pt_page->pt_item_focus->t_menuitem.e_item_type == MENU_ITEM_TYPE_LIST&&
       pt_page->pt_item_focus->b_hidden&&
       pt_page->e_state == PAGE_TREE_STATE_LISTBOX
      )
    {
        a_amb_pause_app(MENU_NAME);
        return MENUR_OK;
    }

    /* Traverse the list and focus the first focusable item */
    if(pt_page->pt_item_focus != NULL)
    {
        if(pt_page->pt_item_focus->b_hidden ||
           !pt_page->pt_item_focus->b_enabled)
        {
            i4_ret=_get_next_focusable_item(pt_page, &pt_page->pt_item_focus);
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }
    DBG_INFO(("[%s %d] h_focus = 0x%x,h_cnt_frm = %d\n",__FUNCTION__,__LINE__,h_focus,pt_page->h_cnt_frm));

    /* Change the focus to current focus item */
    if(h_focus == pt_page->h_cnt_frm)
    {
        if(pt_page->pt_item_focus != NULL)
        {
            i4_ret=c_wgl_set_focus(pt_page->pt_item_focus->h_widget, WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            i4_ret=menu_main_set_visibility(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);
            a_amb_pause_app(MENU_NAME);
            return MENUR_OK;
        }
    }

    i4_ret=_do_layout(pt_page);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _is_one_listbox_mode
 *
 * Description:
 *  There is only one item in the page and the item is a listbox item.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern BOOL _is_one_listbox_mode(
    PAGE_TREE_T* pt_page_tree)
{
    PAGE_TREE_ITEM_T* pt_page_item;

    if(pt_page_tree == NULL)
    {
        return FALSE;
    }

    pt_page_item = DLIST_HEAD(&pt_page_tree->t_item_list);

    if(pt_page_tree->ui2_item_num == 1)
    {
        if(pt_page_item != NULL &&
           pt_page_item->t_menuitem.e_item_type ==MENU_ITEM_TYPE_LISTBOX)
        {
            return TRUE;
        }
    }

    return FALSE;
}

static INT32 _resource_alloc(
    PAGE_TREE_T* pt_page_tree)
{
    INT32 i4_ret=0;
    PAGE_TREE_ITEM_T* pt_page_item;
    INT32    i4_index = 0;

    //b_is_done = FALSE;
    /* traverse the item list */
    DLIST_FOR_EACH(pt_page_item, &pt_page_tree->t_item_list, t_link)
    {
        i4_ret = _create_item_widget(pt_page_tree, pt_page_item);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_index ++;
    }
    return MENUR_OK;
}

static INT32 _resource_free(
    PAGE_TREE_T* pt_page_tree)
{
    INT32 i4_ret;
    PAGE_TREE_ITEM_T* pt_page_item;

    /* traverse the item list */
    DLIST_FOR_EACH(pt_page_item, &pt_page_tree->t_item_list, t_link)
    {
        if(NULL_HANDLE!=pt_page_item->h_widget)
        {
            i4_ret = c_wgl_destroy_widget_ex(pt_page_item->h_widget, FALSE);
            MENU_LOG_ON_FAIL(i4_ret);

            pt_page_item->h_widget = NULL_HANDLE;
        }

    }
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,
                                 VOID*  pv_create_data)
{
    INT32 i4_ret = MENUR_FAIL;
    MENU_PAGE_TREE_INIT_T* pt_init = (VOID*)pv_create_data;
    PAGE_TREE_T*    pt_page = NULL;
    GL_RECT_T   t_rect;

    do
    {
        pt_page = (PAGE_TREE_T*)c_mem_alloc(sizeof(PAGE_TREE_T));
        if(pt_page == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        /* inititate page data */
        pt_page->ui4_page_id        = ui4_page_id;
        pt_page->ui2_max_item_num   = pt_init->ui2_max_item_num;
        pt_page->ui2_msgid_title    = pt_init->ui2_msgid_title;
        pt_page->ui2_item_num       = 0;
        pt_page->ui2_item_id_counter= 0;
        pt_page->pt_item_focus      = NULL;
        pt_page->ui2_ipage_crnt     = 0;
        pt_page->ui2_ipage_num      = 0;
        pt_page->b_lang_chg         = TRUE;
        pt_page->e_state            = PAGE_TREE_STATE_NORMAL;
        pt_page->e_help_lst         = PAGE_TREE_HELP_LST_UNKNOWN;
        pt_page->b_res_alloc        = FALSE;
        pt_page->b_res_auto_free    = TRUE;
        pt_page->b_force_hlt        = FALSE;
        pt_page->i2_offset          = 0;

        i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page->h_cnt_frm);
        MENU_LOG_ON_FAIL(i4_ret);
        if(i4_ret != MENUR_OK)
        {
            break;
        }


        i4_ret = c_wgl_get_coords(pt_page->h_cnt_frm,
                                  WGL_COORDS_LOCAL,
                                  &t_rect);
        MENU_LOG_ON_FAIL(i4_ret);
        if(i4_ret != WGLR_OK)
        {
            break;
        }

        pt_page->ui2_items_per_ipage = _ITEMS_PER_IPAGE;

        DLIST_INIT(&pt_page->t_item_list);

        /* attach page data */
        i4_ret = menu_page_set_data(ui4_page_id, pt_page);
        MENU_LOG_ON_FAIL(i4_ret);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = menu_page_set_proc_func(ui4_page_id, _cnt_frm_proc_fct);
        MENU_LOG_ON_FAIL(i4_ret);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = c_wgl_set_visibility(pt_page->h_cnt_frm,
                                      WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }while(0);

    if(i4_ret != MENUR_OK)
    {
        if(pt_page != NULL)
        {
            c_mem_free(pt_page);
        }
    }

    if(NULL_HANDLE == h_g_font)
    {
        i4_ret = c_fe_create_font(menu_font_name(),
                                          FE_FNT_SIZE_CUSTOM,
                                          MENU_ITEM_FNT_STYLE,
                                          FE_CMAP_ENC_UNICODE,
                                          &h_g_font);
        i4_ret = c_fe_set_custom_size(h_g_font, 24);

        MENU_LOG_ON_FAIL(i4_ret);
        if(AEER_OK != i4_ret)
        {
            return  i4_ret;
        }

    }


    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    INT32 i4_ret;
    PAGE_TREE_T*    pt_page = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID*) &pt_page);
    MENU_LOG_ON_FAIL(i4_ret);

    if(i4_ret != MENUR_OK)
    {
        if(pt_page != NULL)
        {
            /*TODO: Clean up the page item data */

            c_mem_free(pt_page);
        }
    }

    return MENUR_OK;
}

INT32 menu_page_tree_set_offset(UINT32 ui4_page_id, INT16 i2_offset)
{

    PAGE_TREE_T*    pt_page;

    MENU_CHK_FAIL( menu_page_get_data(ui4_page_id, (VOID**)&pt_page));

    if(pt_page == NULL_HANDLE)
    {
        return MENUR_FAIL;
    }

    pt_page->i2_offset = i2_offset;




    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    PAGE_TREE_T*    pt_page;

    DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

    MENU_LOG_ON_FAIL( menu_page_get_data(ui4_page_id, (VOID**)&pt_page));

    if(pt_page->b_res_alloc == FALSE)
    {
        MENU_LOG_ON_FAIL( _resource_alloc(pt_page));
        pt_page->b_res_alloc = TRUE;
    }

    pt_page->ui2_ipage_crnt = 0;
    pt_page->ui2_ipage_num  = 0;

    MENU_LOG_ON_FAIL(_refresh(pt_page));

    MENU_LOG_ON_FAIL( menu_main_set_title(pt_page->ui2_msgid_title));

    MENU_LOG_ON_FAIL( menu_main_chg_backbar());

    MENU_LOG_ON_FAIL( menu_help_tip_keytip_show(FALSE));

    MENU_LOG_ON_FAIL(_chg_lang(pt_page));

    menu_list_arrow_move(&t_lb_rect, FALSE);

    menu_list_arrow_hide(FALSE);

    b_is_subpage_state  = FALSE;

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

    PAGE_TREE_T*        pt_page;
#ifdef APP_MENU_DLG_COEXIST
    BOOL                b_hide;
#endif
    /* Check if resource is allocated */
    MENU_LOG_ON_FAIL( menu_page_get_data(ui4_page_id, (VOID**)&pt_page));

    /* Free the resource */
#ifdef APP_MENU_DLG_COEXIST
    MENU_LOG_ON_FAIL(menu_get_page_hide(&b_hide));

    if(pt_page->b_res_auto_free &&
       b_hide)
#else
     if(pt_page->b_res_auto_free)
#endif
    {
        MENU_LOG_ON_FAIL(_resource_free(pt_page));
        pt_page->b_res_alloc = FALSE;
    }
#ifdef APP_MENU_DLG_COEXIST
    if(!b_hide)
    {
        ui4_page_id_need_hide = ui4_page_id;

        MENU_LOG_ON_FAIL(menu_set_page_hide(TRUE));
    }
#endif

    MENU_LOG_ON_FAIL(menu_help_tip_keytip_show(TRUE));

    menu_list_arrow_hide(FALSE);

#ifdef APP_HDR_SUPPORT
    menu_doly_vision_logo_show(FALSE);
#endif

    b_hot_key_enter = FALSE;
    c_timer_stop(h_listbox_timer);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32               i4_ret=0;
    PAGE_TREE_T*        pt_page = NULL;
    PAGE_TREE_ITEM_T*   pt_page_item = NULL;
    BOOL                b_listbox_mode = FALSE;
    BOOL                b_found = FALSE;
    SVL_REC_T           t_svl_rec;
    ISL_REC_T           t_isl_rec = {0};

    UINT16              ui2_hint_item_id = 0;
    PAGE_TREE_ITEM_T*   pt_hint_item = NULL;
    extern BOOL menu_cc_is_visible(VOID);

    DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_page);
    MENU_LOG_ON_FAIL(i4_ret);

    b_hot_key_enter = FALSE;


    if(pt_page->b_force_hlt)
    {
        MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

        pt_page_item = pt_page->pt_item_focus;
        pt_page->b_force_hlt = FALSE;

        if(pt_page->e_state == PAGE_TREE_STATE_LISTBOX)
        {
            b_listbox_mode = TRUE;
        }
    }
    else
    {
        if(pt_hint != NULL)
        {
            if(pt_hint->e_hint_type == MENU_PAGE_HT_BACK)
            {
                MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

                pt_page_item = pt_page->pt_item_focus;

                if(pt_page->e_state == PAGE_TREE_STATE_LISTBOX)
                {
                    b_listbox_mode = TRUE;
                }
            }
            else if(pt_hint->e_hint_type == MENU_PAGE_HT_PORT)
            {
                MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

                switch(pt_hint->u.e_port)
                {
                    case MENU_PAGE_PORT_LAST:
                    case MENU_PAGE_PORT_BOTTOM:
                        pt_page_item = DLIST_TAIL(&pt_page->t_item_list);

                        while(pt_page_item != NULL &&
                              (pt_page_item->b_enabled == FALSE ||pt_page_item->b_hidden == TRUE))
                        {
                            pt_page_item = DLIST_PREV(pt_page_item, t_link);
                        }
                        break;
                    case MENU_PAGE_PORT_FIRST:
                    case MENU_PAGE_PORT_TOP:
                    case MENU_PAGE_PORT_LEFT:
                    case MENU_PAGE_PORT_RIGHT:
                    default:
                        pt_page_item = DLIST_HEAD(&pt_page->t_item_list);

                        while(pt_page_item != NULL &&
                              (pt_page_item->b_enabled == FALSE ||pt_page_item->b_hidden == TRUE))
                        {
                            pt_page_item = DLIST_NEXT(pt_page_item, t_link);
                        }
                        break;
                }
            }
            else if (MENU_PAGE_HT_CUSTOM == pt_hint->e_hint_type)
            {
                MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

                if (pt_hint->u.pv_custom_hint != NULL)
                {
                    ui2_hint_item_id = *((UINT8*)pt_hint->u.pv_custom_hint);
                    MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui2_hint_item_id:%d\n",
                        __FUNCTION__, __LINE__, ui2_hint_item_id )); );

                    i4_ret = _get_item_data_by_id(pt_page, ui2_hint_item_id, &pt_hint_item);	//Coverity ID:4490513
                    MENU_LOG_ON_FAIL(i4_ret);
                    pt_page_item = pt_hint_item;
                }
            }
            else if(MENU_PAGE_HT_CUST_ITEM_ID == pt_hint->e_hint_type)
            {
                MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

                ui2_hint_item_id = pt_hint->u.u16_item_id;
                MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui2_hint_item_id:%d\n",
                    __FUNCTION__, __LINE__, ui2_hint_item_id )); );

                i4_ret = _get_item_data_by_id(pt_page, ui2_hint_item_id, &pt_hint_item);
                //Coverity ID:4490513
                MENU_LOG_ON_FAIL(i4_ret);
                pt_page_item = pt_hint_item;
            }
        }
        else
        {
            MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

            pt_page_item = DLIST_HEAD(&pt_page->t_item_list);
            while(pt_page_item != NULL)
            {
                if(pt_page_item->b_enabled == TRUE && pt_page_item->b_hidden == FALSE)
                {
                    break;
                }

                pt_page_item = DLIST_NEXT(pt_page_item, t_link);
            }
        }
    }

    if(_is_one_listbox_mode(pt_page))
    {
        b_listbox_mode = TRUE;
    }

    /* Recover the listbox state */
    if(b_listbox_mode &&
       pt_page->pt_item_focus->t_menuitem.e_item_type == MENU_ITEM_TYPE_LISTBOX)
    {
        MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

        b_is_subpage_state = TRUE;
        pt_page_item = pt_page->pt_item_focus;

        UINT16  ui2_i;
        UINT16  ui2_elem_num = pt_page_item->t_menuitem.u.t_listbox.ui2_elem_num;
        UINT16  ui2_hlt;
        UTF16_T w2s_str[64];

        i4_ret=c_wgl_do_cmd(h_listbox,
                     WGL_CMD_LB_SET_ELEM_NUM,
                     WGL_PACK(ui2_elem_num),
                     NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Show the listbox and insert the items to the listbox */
        for(ui2_i=0; ui2_i<ui2_elem_num;ui2_i++)
        {
            if(pt_page_item->t_menuitem.u.t_listbox.pf_get_text != NULL)
            {
                pt_page_item->t_menuitem.u.t_listbox.pf_get_text(ui2_i, w2s_str, 64);
            }
            else
            {
                c_uc_w2s_strcpy(w2s_str,
                                MENU_TEXT(pt_page_item->t_menuitem.u.t_listbox.ui2_msgid_elem_first + ui2_i));
            }

            i4_ret=c_wgl_do_cmd(h_listbox,
                         WGL_CMD_LB_SET_ITEM_TEXT,
                         WGL_PACK_2 (ui2_i, 0),
                         w2s_str);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        /* Highlight the current one */
        ui2_hlt = pt_page_item->t_menuitem.u.t_listbox.pf_get_idx();
        if(ui2_hlt >= ui2_elem_num)
        {
            ui2_hlt = 0;
        }

        i4_ret=c_wgl_do_cmd(h_listbox,
                     WGL_CMD_LB_HLT_ELEM,
                     WGL_PACK(ui2_hlt),
                     WGL_PACK(FALSE));
        MENU_LOG_ON_FAIL(i4_ret);

        /* Help tip */
        menu_hide_help_tip();
        if (MENU_ITEM_TYPE_LIST == pt_page->pt_item_focus->t_menuitem.e_item_type)
        {
            i4_ret=_show_elem_help_tips(
                pt_page->pt_item_focus->t_menuitem.ui2_msgid_desc,
                pt_page->pt_item_focus->t_menuitem.u.t_list.ui2_msgid_elem_desc_first,
                ui2_hlt,
                TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else if (MENU_ITEM_TYPE_LISTBOX == pt_page->pt_item_focus->t_menuitem.e_item_type)
        {
            i4_ret=_show_elem_help_tips(
                pt_page->pt_item_focus->t_menuitem.ui2_msgid_desc,
                pt_page->pt_item_focus->t_menuitem.u.t_listbox.ui2_msgid_elem_desc_first,
                ui2_hlt,
                TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        /* Title */
        i4_ret=menu_main_set_title(pt_page_item->t_menuitem.ui2_msgid_title);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=c_wgl_set_visibility(pt_page_item->pt_page->h_cnt_frm, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=c_wgl_set_visibility(h_listbox, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_page->e_state = PAGE_TREE_STATE_LISTBOX;
    }
    else
    {
        MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );
        pt_page->e_state = PAGE_TREE_STATE_NORMAL;
    }

    if(pt_page_item == NULL)
    {
        MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

        pt_page->pt_item_focus = NULL;

        i4_ret=menu_set_focus_on_backbar(FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        MENU_DEBUG_FOCUS( DBG_LOG_PRINT(("[MENU][TREE][FOCUS]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

        if(a_menu_is_cc_hot_key())
        {
            if(pt_page_item->pt_page->ui4_page_id == ui4_g_menu_page_cc)
            {
                /* Get the tuner type */
                menu_get_crnt_isl(&t_isl_rec);
                menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
                if((b_found
                    && (t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG
                        || (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
                            && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI
                            && menu_cc_is_visible())))
                   || !b_found)
                {
                    pt_page_item = DLIST_HEAD(&pt_page->t_item_list);
                }
                else
                {
                    pt_page_item = DLIST_HEAD(&pt_page->t_item_list);
                    pt_page_item = DLIST_NEXT(pt_page_item, t_link);
                }
            }
        }

        pt_page->pt_item_focus = pt_page_item;

        b_is_page_show = TRUE;

        i4_ret=c_wgl_set_focus(pt_page_item->h_widget,
                        WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        if (MLM_MENU_KEY_OP_VCHIP == pt_page_item->t_menuitem.ui2_msgid_title)
        {
            i4_ret=menu_set_help_tip(w2s_drrt_help_txt);
        }
        else
        {
            i4_ret=menu_set_help_tip(MENU_TEXT(pt_page_item->t_menuitem.ui2_msgid_desc));

        }
        MENU_LOG_ON_FAIL(i4_ret);

        // i4_ret=_do_layout(pt_page);
        // MENU_LOG_ON_FAIL(i4_ret);
    }

    // i4_ret=_do_layout(pt_page);
    // MENU_LOG_ON_FAIL(i4_ret);

#if( defined(APP_SUPPORT_PIC_HOT_KEY) ) // MENU_SUPPORT_HOT_KEY_PIC
    if (a_menu_is_pic_hot_key() == TRUE)
    {
        MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][TREE][KEY][PIC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );
        _menu_page_tree_enter_list_mode(pt_page_item);
    }
#endif

#if 0//( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO )
    if (a_menu_is_hot_key_BTN_ASPECT() == TRUE)
    {
        MENU_DEBUG_KEY_ASPECT_RATIO( DBG_LOG_PRINT(("[MENU][TREE][KEY][RATIO]{%s,%d} \n", __FUNCTION__, __LINE__ )); );
        _menu_page_tree_enter_list_mode(pt_page_item);
    }
#endif


    /*Don't remove this for listbox style*/
    i4_ret=menu_set_backbar_proc(_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_set_homebar_proc(_homebar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_show_backbar (TRUE, FALSE);

    /* Fast Mode */
    ui4_fm_last_tick = 0;
    ui1_fm_delta_idx = 0;

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    INT32 i4_ret=0;
    PAGE_TREE_T*    pt_page;

    DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} ui4_page_id:%d\n", __FUNCTION__, __LINE__, ui4_page_id  )); );

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_page);
    MENU_LOG_ON_FAIL(i4_ret);

    /* reset to normal state */
    if(pt_page->e_state == PAGE_TREE_STATE_SLIDER)
    {
        menu_toast_range_hide();

        i4_ret=menu_main_set_visibility(TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_page->e_state = PAGE_TREE_STATE_NORMAL;

#ifdef VIEWPORT_SUPPORT
        if (a_cfg_get_app_status() == APP_CFG_APP_STATUS_MENU_WIDE_MODE)
        {
            a_cfg_set_app_status(APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
            a_cfg_update_viewport();
        }
#endif

    }

    if(pt_page->e_state == PAGE_TREE_STATE_LISTBOX)
    {
        i4_ret=c_wgl_set_visibility(h_listbox, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret=menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    INT32 i4_ret;
    PAGE_TREE_T*    pt_page;

    //DEBUG_PAGE_TREE( DBG_LOG_PRINT(("[MENU][TREE]{%s,%d} ui4_page_id:%d, ui4_update_mask:0x%X\n", __FUNCTION__, __LINE__, ui4_page_id, ui4_update_mask  )); );

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_page);
    MENU_LOG_ON_FAIL(i4_ret);

    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        MENU_PAGE_STATE_T e_state;
        menu_page_get_state(ui4_page_id, &e_state);
        if(e_state == MENU_PAGE_STATE_SHOW ||
           e_state == MENU_PAGE_STATE_FOCUS)
        {
            i4_ret = _chg_lang(pt_page);
            MENU_LOG_ON_FAIL(i4_ret);
            menu_pm_repaint();
        }
        else
        {
            pt_page->b_lang_chg = TRUE;
        }
    }

    if((ui4_update_mask & MENU_PAGE_UMASK_REFRESH) != 0)
    {
        MENU_PAGE_STATE_T e_state;
        menu_page_get_state(ui4_page_id, &e_state);
        if(e_state == MENU_PAGE_STATE_SHOW ||
           e_state == MENU_PAGE_STATE_FOCUS)
        {
            i4_ret = _refresh(pt_page);
            MENU_LOG_ON_FAIL(i4_ret);
//            i4_ret=_do_layout(pt_page);
//            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    if((ui4_update_mask & MENU_PAGE_UMASK_RESUME) != 0)
    {
        pt_page->pt_item_focus = DLIST_HEAD(&pt_page->t_item_list);
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        global functions implementation
-----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: menu_page_tree_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_init(VOID)
{
    INT32 i4_ret;
    HANDLE_T h_frm_root;
    HANDLE_T h_frm_main;
    UI_SLIDER_MATRIX_INIT_T t_ui_slider_martix_init;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;

    t_g_menu_page_tree.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_tree.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_tree.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_tree.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_tree.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_tree.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_tree.pf_menu_page_update=     _on_page_update;

    i4_ret = menu_pm_get_root_frm(&h_frm_root);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_get_main_frm(&h_frm_main);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_PAGE_TREE_ALWAYS_SLIDER_MODE
    b_always_slider_mode = TRUE;
#else
    b_always_slider_mode = FALSE;
#endif

    menu_toast_range_create();

    //GL_POINT_T t_offset1;
    //t_offset1.i4_x = 0;
    //t_offset1.i4_y = 0;
    c_memset(&t_ui_slider_martix_init, 0, sizeof(UI_SLIDER_MATRIX_INIT_T));
    t_ui_slider_martix_init.e_style = 0;
    t_ui_slider_martix_init.h_parent = h_frm_root;
    t_ui_slider_martix_init.pf_wdgt_proc = NULL;

    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W;//CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;
    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH|WGL_STL_LB_NO_WRAP_OVER;
    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      FRAME_X + CONTENT_X,
                      FRAME_Y + CONTENT_Y,
                      CONTENT_W,
                      MENU_ITEM_V_HEIGHT*10);

    t_lb_rect.i4_left = t_rect.i4_left;
    t_lb_rect.i4_top = t_rect.i4_top;
    t_lb_rect.i4_right = t_rect.i4_right;
    t_lb_rect.i4_bottom = t_rect.i4_bottom;

    i4_ret = menu_list2_create(h_frm_main,
                               &t_rect,
                               NULL,
                               &t_lb_init,
                               NULL,
                               &h_listbox);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (h_listbox,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =c_wgl_float(h_listbox, TRUE, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Create arrow up/down icon */
    menu_list_arrow_create(h_frm_main, &t_rect);

    i4_ret = c_timer_create(&h_listbox_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    b_g_fm_enabled = TRUE;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_create(
    UINT16  ui2_max_item_num,
    UINT16  ui2_msgid_title,
    UINT32* pui4_page_id)
{
    MENU_PAGE_TREE_INIT_T     t_init;

    t_init.ui2_max_item_num = ui2_max_item_num;
    t_init.ui2_msgid_title = ui2_msgid_title;

    return menu_pm_page_create(&t_g_menu_page_tree,
                               (VOID*)&t_init,
                               pui4_page_id);
}

INT32 menu_page_tree_create_subpage(
    UINT16  ui2_max_item_num,
    UINT16  ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_action,
    MENU_ITEM_T* pt_menu_item,
    UINT32* pui4_page_id)
{
    if(NULL == pt_menu_item || NULL == pui4_page_id )
    {
         return MENUR_FAIL;
    }

    if(MENUR_OK != menu_page_tree_create(ui2_max_item_num,ui2_msgid_title,pui4_page_id))
    {
         return MENUR_FAIL;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_SUBPAGE;
    pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc                = ui2_msgid_desc;
    pt_menu_item->u.t_subpage.ui2_msgid_action  = ui2_msgid_action;
    pt_menu_item->u.t_subpage.ui4_subpage_id    = *pui4_page_id;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_destroy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_destroy(
    UINT32 ui4_page_id)
{
    return menu_pm_page_destroy(ui4_page_id);
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_add
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_add(
    UINT32 ui4_page_id,
    MENU_ITEM_T* pt_item,
    UINT16* pui2_item_id)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;

    if(pt_item == NULL ||
       pui2_item_id == NULL)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);

    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret = _add_item(pt_page_tree,
                       pt_item,
                       pui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    return MENUR_OK;
}

INT32 menu_page_tree_add_ex(
    UINT32 ui4_page_id,
    MENU_ITEM_T* pt_item,
    menu_item_is_enabled_fct pf_item_is_enabled,
    menu_item_is_hidden_fct  pf_item_is_hidden,
    UINT32* ui4_page_item_id)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;
    UINT16  ui2_item_id;
    PAGE_TREE_ITEM_T* pt_page_item = NULL;

    if(pt_item == NULL)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);

    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret = _add_item(pt_page_tree,
                       pt_item,
                       &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }
    if(MENUR_OK != _get_item_data_by_id(pt_page_tree, ui2_item_id, &pt_page_item))
    {
        return MENUR_FAIL;
    }

    if(pf_item_is_enabled)
        pt_page_item->pf_is_enabled = pf_item_is_enabled;

    if(pf_item_is_hidden)
    {
        pt_page_item->pf_is_hidden = pf_item_is_hidden;
    }
    if(ui4_page_item_id)
    {
        *ui4_page_item_id = ui2_item_id;
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_remove
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_remove(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;
    PAGE_TREE_ITEM_T* pt_page_item;

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);

    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret = _get_item_data_by_id(pt_page_tree, ui2_item_id, &pt_page_item);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret = _remove_item(pt_page_tree,
                          pt_page_item);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_enable_item
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_enable_item(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id,
    BOOL   b_enable)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;
    PAGE_TREE_ITEM_T* pt_page_item;
    HANDLE_T    h_focus;

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret = _get_item_data_by_id(pt_page_tree, ui2_item_id, &pt_page_item);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret =c_wgl_get_focus(&h_focus);
    MENU_LOG_ON_FAIL(i4_ret);

    if(h_focus != NULL_HANDLE &&
       h_focus == pt_page_item->h_widget &&
       b_enable == FALSE)
    {
        /* if the caller would like to disable current focused widget,
           it will get failure from c_wgl_enable(). */
        i4_ret =c_wgl_set_focus(pt_page_tree->h_cnt_frm, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret =c_wgl_enable(pt_page_item->h_widget, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        /* focus the next focusable item */
        pt_page_item->b_enabled = FALSE;

        i4_ret =_get_next_focusable_item(pt_page_tree, &pt_page_tree->pt_item_focus);
        MENU_LOG_ON_FAIL(i4_ret);

        if(pt_page_tree->pt_item_focus != NULL)
        {
           i4_ret = c_wgl_set_focus(pt_page_tree->pt_item_focus->h_widget, WGL_NO_AUTO_REPAINT);
           MENU_LOG_ON_FAIL(i4_ret);

            i4_ret =_do_layout(pt_page_tree);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            a_amb_pause_app(MENU_NAME);
        }

        return MENUR_OK;
    }
    else
    {
        return _enable_item(pt_page_item, b_enable);
    }
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_hide_item
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_hide_item(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id,
    BOOL   b_hide)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;
    PAGE_TREE_ITEM_T* pt_page_item;
    HANDLE_T    h_focus;

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret = _get_item_data_by_id(pt_page_tree, ui2_item_id, &pt_page_item);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret =c_wgl_get_focus(&h_focus);
    MENU_LOG_ON_FAIL(i4_ret);

    if(h_focus != NULL_HANDLE &&
       h_focus == pt_page_item->h_widget &&
       b_hide == TRUE)
    {
        /* focus the next focusable item */
        pt_page_item->b_hidden = TRUE;

        i4_ret =_get_next_focusable_item(pt_page_tree, &pt_page_tree->pt_item_focus);
        MENU_LOG_ON_FAIL(i4_ret);

        if(pt_page_tree->pt_item_focus != NULL)
        {
            i4_ret =c_wgl_set_focus(pt_page_tree->pt_item_focus->h_widget, WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret =_do_layout(pt_page_tree);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            a_amb_pause_app(MENU_NAME);
        }

        return MENUR_OK;
    }
    else
    {
        i4_ret =_hide_item(pt_page_item, b_hide);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret =_do_layout(pt_page_item->pt_page);
        MENU_LOG_ON_FAIL(i4_ret);

        return MENUR_OK;
    }
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_set_auto_enable
 *
 * Description:
 *      Set auto the auto enable/disable function to a menu item. When the page
 *  the menu item is belong to is shown or refreshed, the associcated auto eanble
 *  callback would be called to get the enable state of this menu item. The client
 *  can auto enable/disable the menu item manually by menu_item_enable().
 *
 * Inputs:
 *      ui4_page_id - the page id
 *      ui2_item_id - the item id
 *      pf_item_is_enabled - the callback function. If the function is NULL,
 *          it will not apply the auto enable feature.
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_set_auto_enable_hide(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id,
    menu_item_is_enabled_fct pf_item_is_enabled,
    menu_item_is_hidden_fct pf_item_is_hidden)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;
    PAGE_TREE_ITEM_T* pt_page_item;

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret = _get_item_data_by_id(pt_page_tree, ui2_item_id, &pt_page_item);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    pt_page_item->pf_is_enabled = pf_item_is_enabled;
    pt_page_item->pf_is_hidden = pf_item_is_hidden;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_set_auto_enable
 *
 * Description:
 *      Set auto the auto enable/disable function to a menu item. When the page
 *  the menu item is belong to is shown or refreshed, the associcated auto eanble
 *  callback would be called to get the enable state of this menu item. The client
 *  can auto enable/disable the menu item manually by menu_item_enable().
 *
 * Inputs:
 *      ui4_page_id - the page id
 *      ui2_item_id - the item id
 *      pf_item_is_enabled - the callback function. If the function is NULL,
 *          it will not apply the auto enable feature.
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_set_auto_enable(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id,
    menu_item_is_enabled_fct pf_item_is_enabled)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;
    PAGE_TREE_ITEM_T* pt_page_item;

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret = _get_item_data_by_id(pt_page_tree, ui2_item_id, &pt_page_item);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    pt_page_item->pf_is_enabled = pf_item_is_enabled;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_set_auto_enable
 *
 * Description:
 *      Set auto the auto enable/disable function to a menu item. When the page
 *  the menu item is belong to is shown or refreshed, the associcated auto eanble
 *  callback would be called to get the enable state of this menu item. The client
 *  can auto enable/disable the menu item manually by menu_item_enable().
 *
 * Inputs:
 *      ui4_page_id - the page id
 *      ui2_item_id - the item id
 *      pf_item_is_enabled - the callback function. If the function is NULL,
 *          it will not apply the auto enable feature.
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_set_auto_hide(
    UINT32 ui4_page_id,
    UINT16 ui2_item_id,
    menu_item_is_hidden_fct pf_item_is_hidden)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;
    PAGE_TREE_ITEM_T* pt_page_item;

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret = _get_item_data_by_id(pt_page_tree, ui2_item_id, &pt_page_item);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    pt_page_item->pf_is_hidden = pf_item_is_hidden;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_set_res_auto_free
 *
 * Description:
 *      "Resouce Auto Free" is a feature that it will free the resource when the
 *  page hide. The auto free function is enabled by default. But the feature may
 *  have some overhead. For this reason, this function provide a API to disable
 *  this feature.
 *
 * Inputs:
 *  UINT32 ui4_page_id,
 *  BOOL   b_auto_free
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_set_res_auto_free(
    UINT32 ui4_page_id,
    BOOL   b_enable)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    pt_page_tree->b_res_auto_free = b_enable;

    return MENUR_OK;
}

extern INT32 menu_page_tree_get_ipage_status(
    UINT32  ui4_page_id,
    UINT16* pui2_ipage_crnt,
    UINT16* pui2_ipage_num)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    *pui2_ipage_crnt = pt_page_tree->ui2_ipage_crnt;
    *pui2_ipage_num  = pt_page_tree->ui2_ipage_num;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_set_focus_item
 *
 * Description:
 *  This function sets the item to be force highlighted when the page is dipplayed.
 *
 * Inputs:
 *  ui4_page_id       The page to be set.
 *  ui2_item_id   -   The item to be focused.
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_tree_set_focus_item(
    UINT32    ui4_page_id,
    UINT16    ui2_item_id,
    BOOL      b_force_hlt)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;
    PAGE_TREE_ITEM_T* pt_page_item;

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret = _get_item_data_by_id(pt_page_tree, ui2_item_id, &pt_page_item);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    pt_page_tree->b_force_hlt   = b_force_hlt;
    pt_page_tree->pt_item_focus = pt_page_item;

    i4_ret =c_wgl_set_focus(pt_page_tree->pt_item_focus->h_widget, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_show_backbar (TRUE, FALSE);
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_focus_item_is_the_assign_item
 *
 * Description:
 *  This function check the item is the corespond to the page id and msg title  or not.
 *  main menu page is not support this function.
 * Inputs:
 *  ui4_page_id       The page to be set.
 *  ui2_item_id   -   The item to be focused.
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern BOOL menu_focus_item_is_the_assign_item(UINT16 ui2_msgid_title)
{
    PAGE_TREE_ITEM_T*     pt_page_item = NULL;
    PAGE_TREE_T*           pt_page = NULL;
    UINT32                     ui4_page_id = 0;
    INT32                     i4_ret = 0;

    i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_get_data(ui4_page_id, ( VOID**)&pt_page);
    MENU_LOG_ON_FAIL(i4_ret);
    if(pt_page == NULL)
    {
        DBG_INFO(("\n====menu_focus_item_is_the_assign_item=== get handle null==\n"));
        return FALSE;
    }
    if(pt_page->pt_item_focus == NULL)
    {
        DBG_INFO(("\n====menu_focus_item_is_the_assign_item=== get handle null==\n"));
        return FALSE;
    }
    pt_page_item = pt_page->pt_item_focus;

    if(pt_page_item != NULL &&
        ui2_msgid_title == pt_page_item->t_menuitem.ui2_msgid_title)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_set_help_tip
 *
 * Description:
 *  Set the help tip.
 *
 * Inputs:
 *  ui4_page_id       The page to be set.
 *  ui2_item_id   -   The item to be focused.
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_tree_set_help_tip(
    UINT32    ui4_page_id,
    UINT16    ui2_item_id,
    UINT16    ui2_msgid_desc)
{
    INT32 i4_ret;
    PAGE_TREE_T* pt_page_tree;
    PAGE_TREE_ITEM_T* pt_page_item;

    i4_ret = _get_page_data_by_id(ui4_page_id, &pt_page_tree);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    i4_ret = _get_item_data_by_id(pt_page_tree, ui2_item_id, &pt_page_item);
    MENU_LOG_ON_FAIL(i4_ret);
    if(i4_ret != MENUR_OK)
    {
        return i4_ret;
    }

    pt_page_item->t_menuitem.ui2_msgid_desc = ui2_msgid_desc;


    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_set_event_listener
 *
 * Description:
 *  This function set the page tree event listener.
 *
 * Inputs:
 *  menu_page_tree_event_listener_fct    -   The event listener
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_page_tree_set_event_listener(
    menu_page_tree_event_listener_fct   pf_event_listener)
{
    pf_g_event_listener = pf_event_listener;

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_page_tree_subpage_item
 *
 * Description:
 *  This function is the helper function to set attributes for a subpage menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_elem_first    -   The first message id of the list.
 *  ui2_msgid_elem_first    -   The last message id of the list.
 *  pf_set_idx      -   The setter function
 *  pf_get_idx      -   The getter function
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_list_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_elem_first,
    UINT16 ui2_msgid_elem_last,
    menu_item_list_set_idx_fct pf_set_idx,
    menu_item_list_get_idx_fct pf_get_idx)
{
    if(pt_menu_item == NULL ||
       pf_set_idx == NULL ||
       pf_get_idx == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(ui2_msgid_elem_last < ui2_msgid_elem_first)
    {
        return MENUR_INV_ARG;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_LIST;
    pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc                = ui2_msgid_desc;
    pt_menu_item->u.t_list.pf_set_idx           = pf_set_idx;
    pt_menu_item->u.t_list.pf_get_idx           = pf_get_idx;
    pt_menu_item->u.t_list.ui2_msgid_elem_first = ui2_msgid_elem_first;
    pt_menu_item->u.t_list.ui2_msgid_elem_last  = ui2_msgid_elem_last;
    pt_menu_item->u.t_list.ui2_elem_num         = (UINT16)((ui2_msgid_elem_last - ui2_msgid_elem_first) + 1);
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_page_tree_list_item_by_text
 *
 * Description:
 *  This function is the helper function to set attributes for a subpage menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_title -   The message id of item title
 *  ui2_msgid_desc  -   The message id of item description
 *  pf_set_idx      -   The setter function
 *  pf_get_idx      -   The getter function
 *  pf_get_text     -   The get text function
 *  Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_list_item_by_text(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 num_elements,
    menu_item_list_set_idx_fct pf_set_idx,
    menu_item_list_get_idx_fct pf_get_idx,
    menu_item_list_get_text_fct pf_get_text)
{
    if(pt_menu_item == NULL ||
       pf_set_idx == NULL ||
       pf_get_idx == NULL)
    {
        return MENUR_INV_ARG;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_LIST;
    pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc                = ui2_msgid_desc;
    pt_menu_item->u.t_list.pf_set_idx           = pf_set_idx;
    pt_menu_item->u.t_list.pf_get_idx           = pf_get_idx;
    pt_menu_item->u.t_list.pf_get_text          = pf_get_text;
    pt_menu_item->u.t_list.ui2_elem_num         = num_elements;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_sb_setting_eq_subpage_item
 *
 * Description:
 *  This function is the helper function to set attributes for a subpage menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_elem_first    -   The first message id of the list.
 *  ui2_msgid_elem_first    -   The last message id of the list.
 *  pf_set_idx      -   The setter function
 *  pf_get_idx      -   The getter function
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_sb_settings_eq_mode_list_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_elem_first,
    UINT16 ui2_msgid_elem_last,
    menu_item_list_set_idx_fct pf_set_idx,
    menu_item_list_get_idx_fct pf_get_idx,
    menu_item_list_get_text_fct pf_get_text,
    menu_item_list_prev_fct pf_prev_idx,
    menu_item_list_next_fct pf_next_idx)
{
    if(pt_menu_item == NULL ||
       pf_set_idx == NULL ||
       pf_get_idx == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(ui2_msgid_elem_last < ui2_msgid_elem_first)
    {
        return MENUR_INV_ARG;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_LIST;
    pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc                = ui2_msgid_desc;
    pt_menu_item->u.t_list.pf_set_idx           = pf_set_idx;
    pt_menu_item->u.t_list.pf_get_idx           = pf_get_idx;
    pt_menu_item->u.t_list.ui2_msgid_elem_first = ui2_msgid_elem_first;
    pt_menu_item->u.t_list.ui2_msgid_elem_last  = ui2_msgid_elem_last;
    pt_menu_item->u.t_list.pf_prev_idx          = pf_prev_idx;
    pt_menu_item->u.t_list.pf_next_idx          = pf_next_idx;
    pt_menu_item->u.t_list.pf_get_text          = pf_get_text;
    pt_menu_item->u.t_list.ui2_elem_num         = (UINT16)((ui2_msgid_elem_last - ui2_msgid_elem_first) + 1);
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_is_in_list_subpage_state
 *
 * Description:
 *
 * Inputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL menu_page_is_in_list_subpage_state(VOID)
{
    return b_is_subpage_state;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_is_in_list_subpage_state
 *
 * Description:
 *
 * Inputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID menu_page_tree_set_list_state(BOOL b_flag)
{
    b_is_subpage_state = b_flag;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_listbox_item
 *
 * Description:
 *  This function is the helper function to set attributes for a listbox menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_elem_first    -   The first message id of the list.
 *  ui2_msgid_elem_first    -   The last message id of the list.
 *  pf_set_idx      -   The setter function
 *  pf_get_idx      -   The getter function
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_listbox_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_elem_first,
    UINT16 ui2_msgid_elem_last,
    menu_item_listbox_set_idx_fct pf_set_idx,
    menu_item_listbox_get_idx_fct pf_get_idx)
{
    if(pt_menu_item == NULL ||
       pf_set_idx == NULL ||
       pf_get_idx == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(ui2_msgid_elem_last < ui2_msgid_elem_first)
    {
        return MENUR_INV_ARG;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_LISTBOX;
    pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc                = ui2_msgid_desc;
    pt_menu_item->u.t_listbox.pf_set_idx           = pf_set_idx;
    pt_menu_item->u.t_listbox.pf_get_idx           = pf_get_idx;
    pt_menu_item->u.t_listbox.ui2_msgid_elem_first = ui2_msgid_elem_first;
    pt_menu_item->u.t_listbox.ui2_msgid_elem_last  = ui2_msgid_elem_last;
    pt_menu_item->u.t_listbox.ui2_elem_num         = (UINT16)((ui2_msgid_elem_last - ui2_msgid_elem_first) + 1);
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_page_tree_list_item_set_elem_help_tip
 *
 * Description:
 *  This function is the helper function to set attributes for a listbox menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  b_elem_desc     -   If there is element help tip
 *  ui2_msgid_elem_desc_first    -   The message id for the first element.
 *  ui2_msgid_elem_desc_last     -   The message id for the last element.
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_list_item_set_elem_help_tip(
    MENU_ITEM_T* pt_menu_item,
    BOOL         b_elem_desc,
    UINT16       ui2_msgid_elem_desc_first,
    UINT16       ui2_msgid_elem_desc_last)
{
    UINT16  ui2_elem_num;
    if(pt_menu_item == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(pt_menu_item->e_item_type != MENU_ITEM_TYPE_LIST)
    {
        return MENUR_INV_ARG;
    }

    if(b_elem_desc)
    {
        if(ui2_msgid_elem_desc_last < ui2_msgid_elem_desc_first)
        {
            return MENUR_INV_ARG;
        }

        ui2_elem_num = ui2_msgid_elem_desc_last - ui2_msgid_elem_desc_first + 1;

        if(ui2_elem_num != pt_menu_item->u.t_list.ui2_elem_num)
        {
            return MENUR_INV_ARG;
        }
    }
    /* Assign the helptip */
    pt_menu_item->u.t_list.b_elem_desc = b_elem_desc;

    if(b_elem_desc)
    {
        pt_menu_item->u.t_list.ui2_msgid_elem_desc_first = ui2_msgid_elem_desc_first;
        pt_menu_item->u.t_list.ui2_msgid_elem_desc_last  = ui2_msgid_elem_desc_last;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_listbox_item_set_elem_help_tip
 *
 * Description:
 *  This function is the helper function to set attributes for a listbox menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  b_elem_desc     -   If there is element help tip
 *  ui2_msgid_elem_desc_first    -   The message id for the first element.
 *  ui2_msgid_elem_desc_last     -   The message id for the last element.
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_listbox_item_set_elem_help_tip(
    MENU_ITEM_T* pt_menu_item,
    BOOL         b_elem_desc,
    UINT16       ui2_msgid_elem_desc_first,
    UINT16       ui2_msgid_elem_desc_last)
{
    UINT16  ui2_elem_num;
    if(pt_menu_item == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(pt_menu_item->e_item_type != MENU_ITEM_TYPE_LISTBOX)
    {
        return MENUR_INV_ARG;
    }

    if(b_elem_desc)
    {
        if(ui2_msgid_elem_desc_last < ui2_msgid_elem_desc_first)
        {
            return MENUR_INV_ARG;
        }

        ui2_elem_num = ui2_msgid_elem_desc_last - ui2_msgid_elem_desc_first + 1;

        if(ui2_elem_num != pt_menu_item->u.t_listbox.ui2_elem_num)
        {
            return MENUR_INV_ARG;
        }
    }
    /* Assign the helptip */
    pt_menu_item->u.t_listbox.b_elem_desc = b_elem_desc;

    if(b_elem_desc)
    {
        pt_menu_item->u.t_listbox.ui2_msgid_elem_desc_first = ui2_msgid_elem_desc_first;
        pt_menu_item->u.t_listbox.ui2_msgid_elem_desc_last  = ui2_msgid_elem_desc_last;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_subpage_item
 *
 * Description:
 *  This function is the helper function to set attributes for a subpage menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_title -   The message id of item title
 *  ui2_msgid_action-   The message id of the action
 *  ui4_page_id     -   The page id of the sub-page.
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_subpage_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_action,
    UINT32 ui4_page_id)
{
    if(pt_menu_item == NULL)
    {
        return MENUR_INV_ARG;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_SUBPAGE;
    pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc                = ui2_msgid_desc;
    pt_menu_item->u.t_subpage.ui2_msgid_action  = ui2_msgid_action;
    pt_menu_item->u.t_subpage.ui4_subpage_id    = ui4_page_id;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_more_item
 *
 * Description:
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_title -   The message id of item title
 *  ui2_msgid_action-   The message id of the action
 *  ui4_page_id     -   The page id of the sub-page.
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_more_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_action,
    UINT32 ui4_page_id)
{
    if(pt_menu_item == NULL)
    {
        return MENUR_INV_ARG;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_MORE_SUBPAGE;
    pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc                = ui2_msgid_desc;
    pt_menu_item->u.t_subpage.ui2_msgid_action  = ui2_msgid_action;
    pt_menu_item->u.t_subpage.ui4_subpage_id    = ui4_page_id;
    return MENUR_OK;
}



/*----------------------------------------------------------------------------
 * Name: menu_page_tree_action_item
 *
 * Description:
 *  This function is the helper function to set attributes for a action menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_title -   The message id of item title
 *  ui2_msgid_action-   The message id of the action
 *  pf_action       -   The action function
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_action_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    UINT16 ui2_msgid_action,
    menu_item_action_fct pf_action)
{
    if(pt_menu_item == NULL ||
       pf_action == NULL)
    {
        return MENUR_INV_ARG;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_ACTION;
    pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc                = ui2_msgid_desc;
    pt_menu_item->u.t_action.ui2_msgid_action   = ui2_msgid_action;
    pt_menu_item->u.t_action.pf_action          = pf_action;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_range_item
 *
 * Description:
 *  This function is the helper function to set attributes for a range menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_title -   The message id of item title
 *  i4_val_min      -   The minimum value
 *  i4_val_max      -   The maximum value
 *  pf_set_val      -   The setter function
 *  pf_get_val      -   The getter function
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_range_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    INT32 i4_val_min,
    INT32 i4_val_max,
    MENU_ITEM_RANGE_STYLE_T e_range_style,
    menu_item_range_set_val_fct pf_set_val,
    menu_item_range_get_val_fct pf_get_val)
{
    if(pt_menu_item == NULL ||
       pf_set_val == NULL ||
       pf_get_val == NULL)
    {
        return MENUR_INV_ARG;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type               = MENU_ITEM_TYPE_RANGE;
    pt_menu_item->ui2_msgid_title           = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc            = ui2_msgid_desc;
    pt_menu_item->u.t_range.i4_val_min      = i4_val_min;
    pt_menu_item->u.t_range.i4_val_max      = i4_val_max;
    pt_menu_item->u.t_range.e_range_style   = e_range_style;
    pt_menu_item->u.t_range.pf_set_val      = pf_set_val;
    pt_menu_item->u.t_range.pf_get_val      = pf_get_val;
    pt_menu_item->u.t_range.b_fast_mode     = FALSE;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_text_item
 *
 * Description:
 *  This function is the helper function to set attributes for a text menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_title -   The message id of item title
 *  pf_get_text     -   The get text function
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_text_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    UINT16 ui2_msgid_desc,
    menu_item_text_get_text_fct  pf_get_text)
{
    if(pt_menu_item == NULL ||
       pf_get_text  == NULL)
    {
        return MENUR_INV_ARG;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_TEXT;
    pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc                = ui2_msgid_desc;
    pt_menu_item->u.t_text.pf_get_text          = pf_get_text;


    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_page_tree_select_range_item
 *
 * Description:
 *  This function is the helper function to set attributes for a slection range
 *  menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_title -   The message id of item title
 *  i4_val_min      -   The minimum value
 *  i4_val_max      -   The maximum value
 *  pf_set_val      -   The setter function
 *  pf_get_val      -   The getter function
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_select_range_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    MENU_ITEM_SELECTION_RANGE_INIT_T* pt_init)
{

    return menu_page_tree_range_item(pt_menu_item,
                                     ui2_msgid_title,
                                     ui2_msgid_title,
                                     pt_init->i4_val_min,
                                     pt_init->i4_val_max,
                                     MENU_ITEM_RANGE_STYLE_BAR,
                                     pt_init->pf_set_val,
                                     pt_init->pf_get_val);
}
/*----------------------------------------------------------------------------
 * Name: menu_page_tree_select_list_item
 *
 * Description:
 *  This function is the helper function to set attributes for a selection
 *  list menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_elem_first    -   The first message id of the list.
 *  ui2_msgid_elem_first    -   The last message id of the list.
 *  pf_set_idx      -   The setter function
 *  pf_get_idx      -   The getter function
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_select_list_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    MENU_ITEM_SELECTION_LIST_INIT_T* pt_init)
{

    return menu_page_tree_list_item(pt_menu_item,
                                    ui2_msgid_title,
                                    ui2_msgid_title,
                                    pt_init->ui2_msgid_elem_first,
                                    pt_init->ui2_msgid_elem_last,
                                    pt_init->pf_set_idx,
                                    pt_init->pf_get_idx);
}

/*----------------------------------------------------------------------------
 * Name: menu_page_tree_select_list_subpage_item
 *
 * Description:
 *  This function is the helper function to set attributes for a selection
 *  list menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_elem_first    -   The first message id of the list.
 *  ui2_msgid_elem_first    -   The last message id of the list.
 *  pf_set_idx      -   The setter function
 *  pf_get_idx      -   The getter function
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_select_list_subpage_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    MENU_ITEM_SELECTION_LIST_INIT_T* pt_init)
{
    if(pt_menu_item == NULL ||
       pt_init->pf_set_idx == NULL ||
       pt_init->pf_get_idx == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(pt_init->ui2_msgid_elem_last < pt_init->ui2_msgid_elem_first)
    {
        return MENUR_INV_ARG;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_LIST_SUBPAGE;
    pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc                = ui2_msgid_title;
    pt_menu_item->u.t_list_subpage.pf_set_idx           = pt_init->pf_set_idx;
    pt_menu_item->u.t_list_subpage.pf_get_idx           = pt_init->pf_get_idx;
    pt_menu_item->u.t_list_subpage.ui2_msgid_elem_first = pt_init->ui2_msgid_elem_first;
    pt_menu_item->u.t_list_subpage.ui2_msgid_elem_last  = pt_init->ui2_msgid_elem_last;
    pt_menu_item->u.t_list_subpage.ui2_elem_num         = (UINT16)((pt_init->ui2_msgid_elem_last - pt_init->ui2_msgid_elem_first) + 1);
    pt_menu_item->u.t_list_subpage.pf_prev_idx          = pt_init->pf_prev_idx;
    pt_menu_item->u.t_list_subpage.pf_next_idx          = pt_init->pf_next_idx;

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_page_tree_select_subpage_item
 *
 * Description:
 *  This function is the helper function to set attributes for a slection
 *  subpage menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_title -   The message id of item title
 *  ui2_msgid_action-   The message id of the action
 *  ui4_page_id     -   The page id of the sub-page.
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_page_tree_select_subpage_item(
    MENU_ITEM_T* pt_menu_item,
    UINT16 ui2_msgid_title,
    MENU_ITEM_SELECTION_SUBPAGE_INIT_T* pt_init)
{

    return menu_page_tree_subpage_item(pt_menu_item,
                                       ui2_msgid_title,
                                       ui2_msgid_title,
                                       pt_init->ui2_msgid_action,
                                       pt_init->ui4_page_id);
}


/*----------------------------------------------------------------------------
 * Name: menu_page_tree_add_with_help
 *
 * Description:
 *  This function is the helper function to set attributes for a slection
 *  subpage menu item.
 *
 * Inputs:
 *  pt_menu_item    -   The menu item struct to set
 *  ui2_msgid_title -   The message id of item title
 *  ui2_msgid_action-   The message id of the action
 *  ui4_page_id     -   The page id of the sub-page.
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

INT32 menu_page_tree_add_with_help(
    UINT32 ui4_page_id,
    MENU_ITEM_T* pt_item,
    UINT16* pui2_item_id,
    UINT16 ui2_msgid_help)
{

    return menu_page_tree_add(ui4_page_id,
                              pt_item,
                              pui2_item_id);
}

/*----------------------------------------------------------------------------
 * Name: menu_page_free
 *
 *
 * Returns:
 ----------------------------------------------------------------------------*/

INT32 menu_page_free(VOID)
{
#ifdef  APP_MENU_DLG_COEXIST
    INT32 i4_ret;

    if(0!=ui4_page_id_need_hide)
    {
        i4_ret=_on_page_hide(ui4_page_id_need_hide);
        MENU_LOG_ON_FAIL(i4_ret);

        ui4_page_id_need_hide =0;
    }
#endif
    return MENUR_OK;
}

HANDLE_T menu_page_get_font_h(VOID)
{
    return h_g_font;
}

INT32 menu_page_tree_change_title(UINT32 ui4_page_id, UINT16 ui2_msgid_title)
{
    INT32           i4_ret = MENUR_OK;
    PAGE_TREE_T*    pt_page = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_page);
    MENU_LOG_ON_FAIL(i4_ret);

    if (MENUR_OK == i4_ret && pt_page != NULL)
    {
        pt_page->ui2_msgid_title = ui2_msgid_title;
    }

    return i4_ret;
}

INT32 menu_page_tree_help_tip_back_proc(VOID)
{
    INT32 i4_ret = MENUR_OK;
    PAGE_TREE_T* pt_page = NULL;
    UINT32  ui4_page_id = 0;
    PAGE_TREE_ITEM_T* pt_page_item = NULL;
    UINT16              ui2_visible_item = 0;
    GL_RECT_T           t_rect = {0};
    HANDLE_T             h_last_shadow_item = NULL_HANDLE;
    BOOL                b_sleep_timer_page = FALSE;

    i4_ret=menu_nav_get_crnt_page(&ui4_page_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=_get_page_data_by_id(ui4_page_id, &pt_page);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_list_arrow_hide(FALSE);

    if (pt_page->e_state == PAGE_TREE_STATE_LISTBOX)
    {
        i4_ret=c_wgl_set_visibility(pt_page->h_cnt_frm, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=c_wgl_set_visibility(h_listbox, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        /*Adjust last shadow position*/
        DLIST_FOR_EACH(pt_page_item, &pt_page->t_item_list, t_link)
        {
            if(pt_page_item->b_hidden == FALSE)
            {
                ui2_visible_item += 1;
            }
        }
        t_rect.i4_left = CONTENT_X;
        t_rect.i4_right = CONTENT_X + CONTENT_H;
        t_rect.i4_top = MENU_ITEM_V_HEIGHT * (ui2_visible_item)+ CONTENT_Y;
        t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

        menu_pm_get_last_shadow_item(&h_last_shadow_item);
        i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);

        if(_is_one_listbox_mode(pt_page))
        {
            i4_ret=menu_nav_back();
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            i4_ret=c_wgl_do_cmd(h_listbox,
                         WGL_CMD_LB_SET_ELEM_NUM,
                         WGL_PACK(0),
                         NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_main_set_title(pt_page->ui2_msgid_title);
            MENU_LOG_ON_FAIL(i4_ret);

            b_is_subpage_state = FALSE;
            pt_page->e_state = PAGE_TREE_STATE_NORMAL;

            /*For DTV00595241*/
            b_sleep_timer_page = menu_focus_item_is_the_assign_item(MLM_MENU_KEY_TITLE_SLEEP_TIMER);
            if(b_sleep_timer_page)
            {
                 i4_ret=menu_pm_refresh();
                 MENU_LOG_ON_FAIL(i4_ret);
            }


            i4_ret=menu_pm_repaint();
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=c_wgl_set_focus(pt_page->pt_item_focus->h_widget, WGL_ASYNC_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        b_hot_key_enter = FALSE;
        c_timer_stop(h_listbox_timer);
    }
    else
    {
        i4_ret=menu_nav_back();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return WGLR_OK;
}

INT32 menu_page_tree_get_widget(
        UINT32      ui4_page_id,
        UINT16      ui2_msgid_title,
        HANDLE_T**  pt_hdr
        )
{
    INT32 i4_ret = MENUR_OK;
    PAGE_TREE_T*  pt_page_tree;

    if (ui4_page_id == 0 ||
        ui2_msgid_title == 0 ||
        pt_hdr == NULL)
    {
        return MENUR_FAIL;
    }

    i4_ret = menu_page_get_data(ui4_page_id, (VOID **)&pt_page_tree);
    if (i4_ret == MENUR_OK)
    {
        PAGE_TREE_ITEM_T*  pt_page_item;
        DLIST_FOR_EACH(pt_page_item, &pt_page_tree->t_item_list, t_link)
        {
            if (pt_page_item != NULL &&
                pt_page_item->t_menuitem.ui2_msgid_title == ui2_msgid_title)
            {
                *pt_hdr = &pt_page_item->h_widget;
                return MENUR_OK;
            }
        }
    }

    MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_FAIL;
}

static UINT16 _menu_page_tree_get_demo_mode_help_text_id(UINT8  ui1_demo_mode)
{
    if(ui1_demo_mode == 0)
    {
        return MLM_MENU_KEY_DEMO_MODE_OFF_HELP;

    }
    else if(ui1_demo_mode == 1)
    {
        return MLM_MENU_KEY_DEMO_MODE_START_OVERLAY_HELP;
    }
    else
    {
        return MLM_MENU_KEY_DEMO_MODE_START_VIDEO_HELP;
    }
}

INT32 menu_pm_page_create_item(UINT16                 ui2_msgid_title,
                                      UINT16                 ui2_msgid_desc,
                                      UINT16                 ui2_msgid_action,
                                      MENU_PAGE_FCT_TBL_T*   pt_page_fct_tbl,
                                      VOID*                  pv_create_data,
                                      MENU_ITEM_T*           pt_menu_item,
                                      UINT32*                pi4_page_id)
 {
     UINT32 ui4_page_id;

     if(NULL == pt_menu_item)
     {
          return MENUR_FAIL;
     }
     if(MENUR_OK != menu_pm_page_create(pt_page_fct_tbl,pv_create_data,&ui4_page_id))
     {
          return MENUR_FAIL;
     }

     c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

     pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_SUBPAGE;
     pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
     pt_menu_item->ui2_msgid_desc                = ui2_msgid_desc;
     pt_menu_item->u.t_subpage.ui2_msgid_action  = ui2_msgid_action;
     pt_menu_item->u.t_subpage.ui4_subpage_id    = ui4_page_id;

     if(NULL != pi4_page_id)
        *pi4_page_id = ui4_page_id;
     return MENUR_OK;
 }

INT32 menu_pm_page_create_dialog(UINT16                                    ui2_msgid_title,
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
                                        UINT32*                                    pui4_item_id)
{
    UINT32 ui4_page_id;
    MENU_COMMON_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;

    c_memset(&t_simple_dialog_init, 0, sizeof(MENU_COMMON_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.ui2_msg_txt        = ui2_msg_txt;
    t_simple_dialog_init.ui2_msg_yes        = ui2_msg_yes;
    t_simple_dialog_init.ui2_msg_no         = ui2_msg_no;
    t_simple_dialog_init.e_style            = e_style;
    t_simple_dialog_init.ui2_text_alignment = ui2_text_alignment;
    t_simple_dialog_init.b_default_answer   = b_default_answer;
    t_simple_dialog_init.pf_yes             = pf_yes;
    t_simple_dialog_init.pf_no              = pf_no;

    if (MLM_MENU_KEY_SERVICE_CHECK_HELP_INFO    == ui2_msg_txt ||
        MLM_MENU_KEY_RESET_CONFIRM_FAC_SETTINGS == ui2_msg_txt)
    {
        t_simple_dialog_init.b_info_icon = TRUE;
    }
    else
    {
        t_simple_dialog_init.b_info_icon = FALSE;
    }

    if(MENUR_OK != menu_pm_page_create(&t_g_menu_common_page_simple_dialog,
                                       (VOID*)&t_simple_dialog_init,
                                       &ui4_page_id))
    {
        return MENUR_FAIL;
    }

    c_memset(pt_menu_item, 0, sizeof(MENU_ITEM_T));

    pt_menu_item->e_item_type                   = MENU_ITEM_TYPE_SUBPAGE;
    pt_menu_item->ui2_msgid_title               = ui2_msgid_title;
    pt_menu_item->ui2_msgid_desc                = ui2_msgid_desc;
    pt_menu_item->u.t_subpage.ui2_msgid_action  = ui2_msgid_action;
    pt_menu_item->u.t_subpage.ui4_subpage_id    = ui4_page_id;

    if(pui4_item_id)
        *pui4_item_id = ui4_page_id;
    return MENUR_OK;
}

