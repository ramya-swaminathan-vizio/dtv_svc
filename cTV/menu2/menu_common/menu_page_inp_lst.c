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
 * $RCSfile: menu_page_inp_lst.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svctx.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_rating.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_dbg.h"

#include "res/menu2/menu_custom.h"





#ifdef COMMON_INP_LST_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/* Customizable part */

#ifndef INP_LST_STL_SCROLL
    #define INP_LST_STL_SCROLL    0
#endif

#ifndef INP_LST_STL_WRAP_OVER
    #define INP_LST_STL_WRAP_OVER 1
#endif

#ifndef INP_LST_BACK_ON_LEFT
    #define INP_LST_BACK_ON_LEFT  0
#endif

#ifndef INP_LST_X
    #define INP_LST_X            (1 * GRID_W)
#endif

#ifndef INP_LST_Y
    #define INP_LST_Y            (0 * GRID_H)
#endif

#ifndef INP_LST_W
    #define INP_LST_W            (14 * GRID_W)
#endif

#ifndef INP_LST_H
    #define INP_LST_H            (10 * GRID_H)
#endif

#ifndef INP_LST_COL0_W
    #define INP_LST_COL0_W       80
#endif

#ifndef INP_LST_COL1_W
    #define INP_LST_COL1_W       (INP_LST_W - INP_LST_COL0_W - INP_LST_COL2_W)
#endif

#ifndef INP_LST_COL2_W
    #define INP_LST_COL2_W       80
#endif

/* layout */
/*
  +----------------------------------------------------+
  |   1   |    Component 1                 | lock icon |
  +----------------------------------------------------+
   COL0     COL1                            COL2
*/


#ifndef INP_LST_ELEM_N
    #define INP_LST_ELEM_N       16
#endif

#ifndef INP_LST_ELEM_H
    #define INP_LST_ELEM_H       GRID_H
#endif

#ifndef INP_LST_COL0_ALIGN
    #define INP_LST_COL0_ALIGN   WGL_AS_LEFT_CENTER
#endif

#ifndef INP_LST_COL1_ALIGN
    #define INP_LST_COL1_ALIGN   WGL_AS_LEFT_CENTER
#endif

#ifndef INP_LST_COL2_ALIGN
    #define INP_LST_COL2_ALIGN   WGL_AS_CENTER_CENTER
#endif

#define MAX_INP_NAME_LEN     24
#define MAX_INP_NUM_LEN      8

typedef enum _HELP_LST_STATE{
    HELP_LST_UP_ONLY = 0,
    HELP_LST_DOWN_ONLY,
    HELP_LST_UP_DOWN,
    HELP_LST_UNKNOWN
} HELP_LST_STATE;

typedef struct _INPUT_LIST_INIT_T{
    UINT16              ui2_msg_title;
    UINT32              ui4_sel_mask;
    WGL_HIMG_TPL_T      h_img_normal;
    WGL_HIMG_TPL_T      h_img_selected;
    WGL_HIMG_TPL_T      h_img_highlight;
    WGL_HIMG_TPL_T      h_img_selected_highlight;
    UINT16              ui2_max_rec_num;
    BOOL                b_scroll;       /* TRUE, then turns off the listbox
                                           WGL_STL_LB_NO_SCROLL style */
    BOOL                b_wrap_over;    /* TRUE, then turns off the listbox
                                           WGL_STL_LB_NO_WRAP_OVER */
    BOOL                b_back_on_left; /* Back to previous page by
                                           BTN_CURSOR_LEFT */
}INPUT_LIST_INIT_T;

typedef struct _INPUT_LIST_T
{
    UINT32                  ui4_page_id;
    INPUT_LIST_INIT_T       t_inp_lst_init;
    UINT8*                  pui1_idx_recid_map;
    HANDLE_T                h_lb_inp;
    BOOL                    b_is_refreshing;
}INPUT_LIST_T;


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_inp_lst;

#if 0
static HELP_LST_STATE    e_g_help_lst_state = HELP_LST_UNKNOWN;
#endif
static UINT16            gui2_lb_elem_num;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _inp_lst_set_attach_data
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _inp_lst_set_attach_data(HANDLE_T            h_lb_inp,
                                      INPUT_LIST_T*     pt_inp_lst)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_inp_lst),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _inp_lst_get_attach_data
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _inp_lst_get_attach_data(HANDLE_T            h_lb_inp,
                                      INPUT_LIST_T**    ppt_inp_lst)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_inp_lst),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _ch_lst2_on_sel
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _inp_lst_on_sel(HANDLE_T    h_lb_inp,
                      UINT16      ui2_idx,
                      BOOL        b_sel)
{
    INT32           i4_result;
    UINT8           ui1_rec_id;
    UINT32          ui4_sel_mask;
    INPUT_LIST_T*   pt_inp_lst;

    /* get the channel list data */
    i4_result = _inp_lst_get_attach_data(h_lb_inp, &pt_inp_lst);
    MENU_CHK_FAIL(i4_result);

    if (pt_inp_lst == NULL)
    {
        return MENUR_FAIL;
    }

    if (pt_inp_lst->b_is_refreshing)
    {
        return MENUR_OK;
    }

    /* get the list mask */
    ui4_sel_mask = pt_inp_lst->t_inp_lst_init.ui4_sel_mask;

    /* get the rec id*/
    ui1_rec_id = pt_inp_lst->pui1_idx_recid_map[ui2_idx];

    /* update the record*/

    if(ui4_sel_mask & ISL_ATTR_BIT_BLOCKED)
    {
        if(b_sel)
        {
            a_cfg_set_input_src_block(ui1_rec_id,
                                      TRUE);
        }
        else
        {
            a_cfg_set_input_src_block(ui1_rec_id,
                                      FALSE);

        }
    }

    if(ui4_sel_mask & ISL_ATTR_BIT_SKIPPED)
    {
        if(b_sel)
        {
            a_cfg_set_input_src_skip(ui1_rec_id,
                                     TRUE);
        }
        else
        {
            a_cfg_set_input_src_skip(ui1_rec_id,
                                     FALSE);

        }
    }

    /* Flush update to ISL */

    a_cfg_update_input_src_attr();

    if( (ui4_sel_mask & ISL_ATTR_BIT_BLOCKED) > 0 )
    {
        if (c_svctx_unblock_svc(t_g_menu_common.h_svctx, FALSE) != SVCTXR_OK)
        {
            DBG_ERROR(("<MENU> (MAIN) c_svctx_unblock_svc() failed, ret=%d\n"));

        }
        if (c_svctx_unblock_svc(t_g_menu_common.h_svctx_sub, FALSE) != SVCTXR_OK)
        {
            DBG_ERROR(("<MENU> (SUB) c_svctx_unblock_svc() failed, ret=%d\n"));

        }

    }


    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _help_lst_update
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _help_lst_update(HELP_LST_STATE e_help_lst_state,
                              BOOL           b_repaint)
{
/* use help tip instead of menu's help list */
#if 0
#if 1
    MENU_HELP_LST_BUCKET_T at_help_lst[] =
    {
        {h_g_menu_img_btn_enter,    MLM_MENU_KEY_HELP_SET},
        {h_g_menu_img_btn_select,   MLM_MENU_KEY_HELP_SELECT},
        {h_g_menu_img_btn_exit,     MLM_MENU_KEY_HELP_BACK}
    };

    e_g_help_lst_state = e_g_help_lst_state;

    menu_main_set_help(at_help_lst,
                       (UINT16)(sizeof(at_help_lst)/ sizeof(at_help_lst[0])));
#else
    BOOL   b_no_color_key;
    BOOL   b_only_one_page;

#ifdef APP_NO_COLOR_KEY
    b_no_color_key = TRUE;
#else
    b_no_color_key = FALSE;
#endif

    /* Determine one page only */
    if(gui2_lb_elem_num <= ((INP_LST_H) / (INP_LST_ELEM_H)))
    {
        b_only_one_page = TRUE;
    }
    else
    {
        b_only_one_page = FALSE;
    }

    /* Current help_lst is already the same state */

    if(e_g_help_lst_state == e_help_lst_state)
    {
        return MENUR_OK;
    }

    /* Save the current state */

    e_g_help_lst_state = e_help_lst_state;

    /* If b_no_color_key, always show HELP_BACK only */

    if(b_no_color_key || b_only_one_page)
    {
        MENU_HELP_LST_BUCKET_T at_help_ch_lst[] =
        {
            {h_g_menu_img_btn_exit, MLM_MENU_KEY_HELP_BACK}
        };

        menu_main_set_help(at_help_ch_lst,
                           sizeof(at_help_ch_lst) / sizeof(at_help_ch_lst[0]));

        if(b_repaint)
        {
            menu_pm_repaint();
        }

        return MENUR_OK;
    }

    /* state = HELP_LST_UP_DOWN, show UP/DOWN/BACK */

    if(e_help_lst_state == HELP_LST_UP_DOWN)
    {
        MENU_HELP_LST_BUCKET_T at_help_ch_lst[] =
        {

            {h_g_menu_img_btn_red, MLM_MENU_KEY_HELP_PG_UP},
            {h_g_menu_img_btn_green, MLM_MENU_KEY_HELP_PG_DN},
            {h_g_menu_img_btn_exit, MLM_MENU_KEY_HELP_BACK}
        };

        menu_main_set_help(at_help_ch_lst,
                           sizeof(at_help_ch_lst) / sizeof(at_help_ch_lst[0]));

        if(b_repaint)
        {
            menu_pm_repaint();
        }

        return MENUR_OK;
    }

    /* state = HELP_LST_UP_ONLY, show UP/BACK */

    if(e_help_lst_state == HELP_LST_UP_ONLY)
    {
        MENU_HELP_LST_BUCKET_T at_help_ch_lst[] =
        {

            {h_g_menu_img_btn_red, MLM_MENU_KEY_HELP_PG_UP},
            {h_g_menu_img_btn_exit, MLM_MENU_KEY_HELP_BACK}
        };

        menu_main_set_help(at_help_ch_lst,
                           sizeof(at_help_ch_lst) / sizeof(at_help_ch_lst[0]));

        if(b_repaint)
        {
            menu_pm_repaint();
        }

        return MENUR_OK;
    }

    /* state = HELP_LST_DOWN_ONLY, show DOWN/BACK */

    if(e_help_lst_state == HELP_LST_DOWN_ONLY)
    {
        MENU_HELP_LST_BUCKET_T at_help_ch_lst[] =
        {
            {h_g_menu_img_btn_green, MLM_MENU_KEY_HELP_PG_DN},
            {h_g_menu_img_btn_exit, MLM_MENU_KEY_HELP_BACK}
        };

        menu_main_set_help(at_help_ch_lst,
                           sizeof(at_help_ch_lst) / sizeof(at_help_ch_lst[0]));

        if(b_repaint)
        {
            menu_pm_repaint();
        }

        return MENUR_OK;
    }
#endif
#endif
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_ch_lst2_on_notify
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _inp_lst_on_notify(HANDLE_T    h_lb_inp,
                         WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_LB_ELEM_SEL:
        {
            UINT16 i2_idx = pt_nfy_data->u.t_lb_elem_sel.ui2_elem_idx;
            BOOL b_sel = pt_nfy_data->u.t_lb_elem_sel.b_is_selected;

            if (menu_get_cond() != MENU_COND_NOT_INIT)
            {
                _inp_lst_on_sel(h_lb_inp, i2_idx, b_sel);
            }
            break;
        }

    case WGL_NC_LB_ELEM_HLT:
        {
            UINT16            i2_idx = pt_nfy_data->u.t_lb_elem_hlt.ui2_elem_idx;
            UINT16            i2_end_index;
            BOOL              b_hlt = pt_nfy_data->u.t_lb_elem_hlt.b_is_highlighted;
            INPUT_LIST_T*   pt_inp_lst;

            _inp_lst_get_attach_data(h_lb_inp,
                                     &pt_inp_lst);


            /* If the CH_LIST is refreshing, do nothing */
            if(pt_inp_lst->b_is_refreshing)
            {
                return WMPR_DONE;
            }

            /* Change the HELP_LST */

            /* Get the index */
            c_wgl_do_cmd(h_lb_inp,
                         WGL_CMD_LB_GET_ELEM_NUM,
                         WGL_PACK(&i2_end_index),
                         NULL);

            i2_end_index -= 1;

            if(i2_idx == 0 && b_hlt)
            {
                _help_lst_update(HELP_LST_DOWN_ONLY, TRUE);
            }
            else if(i2_idx == i2_end_index && b_hlt)
            {
                _help_lst_update(HELP_LST_UP_ONLY, TRUE);
            }
            else if(b_hlt)
            {
                _help_lst_update(HELP_LST_UP_DOWN, TRUE);
            }
            else
            {

            }
            break;
        }
    default:
        break;
    }

    return WMPR_DONE;
}
INT32 _inp_lst_proc_fct(HANDLE_T            h_widget,
                        UINT32              ui4_msg,
                        VOID*               pv_param1,
                        VOID*               pv_param2)
{
    INT32 i4_ret;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
        {
            INPUT_LIST_T* pt_inp_lst;
            UINT32 ui4_keycode = (UINT32)pv_param1;

            /* get the channel list data */
            i4_ret = _inp_lst_get_attach_data(h_widget, &pt_inp_lst);
            if(i4_ret != MENUR_OK)
            {
                return WGLR_OK;
            }

            switch (ui4_keycode)
            {
            case BTN_CURSOR_LEFT:
                if(pt_inp_lst->t_inp_lst_init.b_back_on_left)
                {
                    menu_nav_back();
                    return WGLR_OK;
                }
                else
                {
                    /* simulate the page up */
                    pv_param1 = WGL_PACK(BTN_RED);
                }
                break;
            case BTN_CURSOR_RIGHT:
                if(pt_inp_lst->t_inp_lst_init.b_back_on_left)
                {
                    /* do nothing */
                    return WGLR_OK;
                }
                else
                {
                    /* simulate the page up */
                    pv_param1 = WGL_PACK(BTN_GREEN);
                }
                break;
            case BTN_CURSOR_UP:
            case BTN_CURSOR_DOWN:
                ui4_msg = WGL_MSG_KEY_DOWN;
                break;
            case BTN_RETURN:
                menu_nav_back();
                return WGLR_OK;
            default:
                break;
            }
        }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static VOID _inp_num_to_str(ISL_REC_T*   pt_isl_rec,
                            UTF16_T*     pw2s_str)
{
    CHAR   s_str[64];

    /*
       In ISL record:     In LB widget:

       TV  = 0            1  TV
       AV1 = 1            2  AV1
       AV2 = 2            3  AV2
       .                  .
       .                  .
       .                  .
    */

    c_sprintf(s_str,"%d", pt_isl_rec->ui1_id+1);
    c_uc_ps_to_w2s(s_str ,pw2s_str, MAX_INP_NUM_LEN);
}

/*----------------------------------------------------------------------------
 * Name: _ch_lst2_add_ch
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _inp_lst_add_inp(HANDLE_T           h_lb_inp,
                              INPUT_LIST_T*       pt_inp_lst,
                              ISL_REC_T*          pt_isl_rec)
{
   INT32   i4_ret;
   UINT16  ui2_idx;
   UINT32  ui4_sel_mask = pt_inp_lst->t_inp_lst_init.ui4_sel_mask;
   UTF16_T w2s_digits[MAX_INP_NUM_LEN+1];
   UTF16_T w2s_name[MAX_INP_NAME_LEN+1];
   WGL_LB_ITEM_T at_items[3];
   WGL_LB_ITEM_IMG_SUIT_T t_img_suit;

    /* Get the input source # */
    c_memset(w2s_digits, 0, sizeof(w2s_digits));
    _inp_num_to_str(pt_isl_rec, w2s_digits);

    /* Get the display name of input source*/
    c_memset(w2s_name, 0, sizeof(w2s_name));
    c_uc_w2s_strncpy(w2s_name, a_isl_get_display_name(pt_isl_rec), MAX_INP_NAME_LEN);

    /* Append the data */
    c_memset(&t_img_suit, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit.h_normal                     = pt_inp_lst->t_inp_lst_init.h_img_normal;
    t_img_suit.h_disable                    = NULL_HANDLE;
    t_img_suit.h_highlight                  = pt_inp_lst->t_inp_lst_init.h_img_highlight;
    t_img_suit.h_highlight_unfocus          = NULL_HANDLE;
    t_img_suit.h_pushed                     = NULL_HANDLE;
    t_img_suit.h_selected                   = pt_inp_lst->t_inp_lst_init.h_img_selected;
    t_img_suit.h_selected_disable           = NULL_HANDLE;
    t_img_suit.h_selected_highlight         = pt_inp_lst->t_inp_lst_init.h_img_selected_highlight;
    t_img_suit.h_selected_highlight_unfocus = NULL_HANDLE;
    t_img_suit.h_selected_pushed            = NULL_HANDLE;

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_digits;
    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_name;
    at_items[2].e_col_type = LB_COL_TYPE_IMG_SUIT;
    at_items[2].data.pt_img_suit = &t_img_suit;

     /* append item */
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(at_items),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Get the index */
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&ui2_idx),
                          NULL);
    MENU_CHK_FAIL(i4_ret);
    ui2_idx -= 1;

    /* Sel or not */
    if (pt_isl_rec->ui4_attr_bits& ui4_sel_mask)
    {
        i4_ret = c_wgl_do_cmd(h_lb_inp,
                              WGL_CMD_LB_SEL_ELEM,
                              WGL_PACK(ui2_idx),
                              NULL);
        MENU_CHK_FAIL(i4_ret);
    }

    /* mapping */
    pt_inp_lst->pui1_idx_recid_map[ui2_idx] = pt_isl_rec->ui1_id;


    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_create_channel_list
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _inp_lst_create(HANDLE_T          h_parent,
                      INT32             i4_x,
                      INT32             i4_y,
                      INT32             i4_w,
                      INT32             i4_h,
                      INPUT_LIST_T*     pt_inp_lst,
                      HANDLE_T*         ph_lb_inp)
{
    INT32               i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[3];
    GL_RECT_T           t_rect;
    WGL_LB_KEY_MAP_T    t_lb_key_map;
    /*WGL_LB_SCROLL_IMG_INFO_T    t_scroll_img_info;*/

    /* input source no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = INP_LST_COL0_ALIGN;
    at_cols[0].ui2_max_text_len = MAX_INP_NUM_LEN;
    at_cols[0].ui2_width        = INP_LST_COL0_W;

    /* channel name or starting time */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = INP_LST_COL1_ALIGN;
    at_cols[1].ui2_max_text_len = MAX_INP_NAME_LEN;
    at_cols[1].ui2_width        = INP_LST_COL1_W;

    /* pre-selected */
    at_cols[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[2].ui1_align        = INP_LST_COL2_ALIGN;
    at_cols[2].ui2_width        = INP_LST_COL2_W;


    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_MULTI_SEL;
#ifndef APP_MENU_IMG_UI
    t_lb_init.ui4_style         |= WGL_STL_GL_NO_IMG_UI;
#endif

    if(!pt_inp_lst->t_inp_lst_init.b_scroll)
    {
        t_lb_init.ui4_style         |= WGL_STL_LB_NO_SCROLL;
    }

    if(!pt_inp_lst->t_inp_lst_init.b_wrap_over)
    {
        t_lb_init.ui4_style         |= WGL_STL_LB_NO_WRAP_OVER;
    }

    t_lb_init.ui2_max_elem_num  = pt_inp_lst->t_inp_lst_init.ui2_max_rec_num;
    t_lb_init.ui2_elem_size     = INP_LST_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 3;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      i4_x,
                      i4_y,
                      i4_w,
                      i4_h);

    i4_ret = menu_list2_create (h_parent,
                                &t_rect,
                                _inp_lst_proc_fct,
                                & t_lb_init,
                                NULL,
                                ph_lb_inp);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for input source list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_DOWN;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_UP;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    t_lb_key_map.ui4_key_page_up    = BTN_RED;
    t_lb_key_map.ui4_key_page_down  = BTN_GREEN;
    i4_ret = c_wgl_do_cmd(*ph_lb_inp, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_CHK_FAIL(i4_ret);

    /* attach data */
    i4_ret = _inp_lst_set_attach_data(*ph_lb_inp, pt_inp_lst);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_create_channel_list
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32   _inp_lst_refresh(HANDLE_T   h_lb_inp)
{
    INT32         i4_ret      = MENUR_OK;
    INT32         i4_result;
    INPUT_LIST_T* pt_inp_lst;
    UINT8         ui1_rec_num;
    UINT8         ui1_idx;
    ISL_REC_T     t_isl_rec;

    /* get the channel list data */
    _inp_lst_get_attach_data(h_lb_inp, &pt_inp_lst);
    if (pt_inp_lst == NULL)
    {
        return MENUR_FAIL;
    }

    /* Set the refreshing flag */
    pt_inp_lst->b_is_refreshing = TRUE;

    /* clear the list */
    i4_result = c_wgl_do_cmd(h_lb_inp,
                             WGL_CMD_LB_DEL_ALL,
                             NULL, NULL);
    MENU_CHK_FAIL(i4_result);

    /* get record number */
    a_isl_get_num_rec(&ui1_rec_num);

    /* check if the record number exceeds the max channel number */
    if((UINT16)ui1_rec_num > pt_inp_lst->t_inp_lst_init.ui2_max_rec_num)
    {
        DBG_ERROR(("<MENU> Record number exceeds max sec number: %d < %d.\r\n",
                  ui1_rec_num, pt_inp_lst->t_inp_lst_init.ui2_max_rec_num));

       ui1_rec_num = (UINT8)pt_inp_lst->t_inp_lst_init.ui2_max_rec_num;
    }

    /* iterate */
    for(ui1_idx = 0 ; ui1_idx < ui1_rec_num ; ui1_idx++)
    {
        a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);

/* Currently, TV input src is allow to block */
#if 0
        /* ignore TV inp src */
        if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
        {
            continue;
        }
#endif

        i4_result = _inp_lst_add_inp(h_lb_inp,
                                     pt_inp_lst,
                                     &t_isl_rec);
        if (i4_result < 0)
        {
            i4_ret = i4_result;
            DBG_ERROR(("<MENU> Can't add input source to input source list.\r\n"));
            break;
        }
    }

    /* Set the refreshing flag */
    pt_inp_lst->b_is_refreshing = FALSE;

    /* Set the total number to global */
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&gui2_lb_elem_num),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _inp_lst_hlt_curent_src
 *
 * Description:
 *  Highlight current playing channel
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _inp_lst_hlt_curent_src(HANDLE_T h_lb_inp)
{
    INT32           i4_ret;
    INPUT_LIST_T*   pt_inp_lst;
    ISL_REC_T       t_isl_rec;
    ISL_REC_T       t_isl_rec_crnt;
    UINT8           ui1_rec_num;
    UINT8           ui1_idx;

    /* get the channel list data */
    _inp_lst_get_attach_data(h_lb_inp, &pt_inp_lst);
    if (pt_inp_lst == NULL)
    {
        return MENUR_FAIL;
    }

    /* Get Input Source number */
    i4_ret = a_isl_get_num_rec(&ui1_rec_num);
    MENU_CHK_FAIL(i4_ret);

    /* get the current svl record */
    i4_ret = menu_get_crnt_isl(&t_isl_rec_crnt);
    MENU_CHK_FAIL(i4_ret);

    /* Iterate the ISL */
    for(ui1_idx = 0 ; ui1_idx < ui1_rec_num ; ui1_idx++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);
        MENU_CHK_FAIL(i4_ret);

        if(t_isl_rec.ui1_id == t_isl_rec_crnt.ui1_id)
        {
            break;
        }
    }
    if(ui1_idx == ui1_rec_num)
    {
        ui1_idx = 0;
    }

    /* Highlight Element */
    i4_ret = c_wgl_do_cmd(h_lb_inp,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui1_idx),                            /* hlt elem */
                          WGL_PACK(ui1_idx % (UINT16)(CONTENT_H / GRID_H)));    /* hlt pos */
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _frm_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _cnt_frm_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{

    switch (ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
            HANDLE_T h_source = (HANDLE_T)param1;
            WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)param2;
            _inp_lst_on_notify(h_source, pt_nfy_data);
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32                i4_ret       = MENUR_FAIL;
    INPUT_LIST_T*        pt_inp_lst   = NULL;
    INPUT_LIST_INIT_T*   pt_inp_lst_init = (INPUT_LIST_INIT_T*)pv_create_data;
    HANDLE_T             h_cnt_frm;

    if(pt_inp_lst_init == NULL)
    {
        return MENUR_INV_ARG;
    }

    /* Attach data */
    do
    {
        i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        pt_inp_lst = c_mem_alloc(sizeof(INPUT_LIST_T));

        if(pt_inp_lst == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        c_memset(pt_inp_lst, 0, sizeof(INPUT_LIST_T));

        c_memcpy(&pt_inp_lst->t_inp_lst_init,
                 pt_inp_lst_init,
                 sizeof(INPUT_LIST_INIT_T));

        pt_inp_lst->ui4_page_id = ui4_page_id;
        pt_inp_lst->pui1_idx_recid_map =
            c_mem_alloc(pt_inp_lst_init->ui2_max_rec_num * sizeof(UINT8));
        if(pt_inp_lst->pui1_idx_recid_map == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        i4_ret = menu_page_set_data(ui4_page_id, pt_inp_lst);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /* Create input list box */
        i4_ret = _inp_lst_create(h_cnt_frm,
                    INP_LST_X,
                    INP_LST_Y,
                    INP_LST_W,
                    INP_LST_H,
                    pt_inp_lst,
                    &pt_inp_lst->h_lb_inp);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }


        i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = menu_page_set_proc_func(ui4_page_id,
                                         _cnt_frm_proc_fct);
        if(i4_ret != WGLR_OK)
        {
            break;
        }

    } while(0);

    if(i4_ret != MENUR_OK)
    {
        if(pt_inp_lst != NULL)
        {
            if(pt_inp_lst->h_lb_inp != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_inp_lst->h_lb_inp);
            }
            if(pt_inp_lst->pui1_idx_recid_map != NULL)
            {
                c_mem_free(pt_inp_lst->pui1_idx_recid_map);
            }
            c_mem_free(pt_inp_lst);
        }
    }

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{

    /* Pending */

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32 i4_ret;
    INPUT_LIST_T* pt_inp_lst = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_inp_lst);
    MENU_CHK_FAIL(i4_ret);

    _inp_lst_refresh(pt_inp_lst->h_lb_inp);

    _inp_lst_hlt_curent_src(pt_inp_lst->h_lb_inp);

    menu_main_set_title(pt_inp_lst->t_inp_lst_init.ui2_msg_title);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32 i4_ret;
    INPUT_LIST_T* pt_inp_lst = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_inp_lst);
    MENU_CHK_FAIL(i4_ret);

    c_wgl_set_focus(pt_inp_lst->h_lb_inp, WGL_NO_AUTO_REPAINT);

    /* Initially, only Page Down button is shown */
    _help_lst_update(HELP_LST_DOWN_ONLY, FALSE);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    #if 0
    e_g_help_lst_state = HELP_LST_UNKNOWN;
    #endif
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        /* do_nothing */
    }
    return MENUR_OK;
}

extern INT32 menu_common_create_page_sk_inp(UINT32 *pui4_page_id)
{
    INPUT_LIST_INIT_T    t_inp_lst_init;

    c_memset(&t_inp_lst_init, 0, sizeof(INPUT_LIST_INIT_T));

    t_inp_lst_init.ui2_msg_title            = MLM_MENU_KEY_INP_SK;
    t_inp_lst_init.ui2_max_rec_num          = INP_LST_ELEM_N;
    t_inp_lst_init.h_img_normal             = h_g_menu_img_unskip;
    t_inp_lst_init.h_img_highlight          = h_g_menu_img_unskip_hlt;
    t_inp_lst_init.h_img_selected           = h_g_menu_img_skip;
    t_inp_lst_init.h_img_selected_highlight = h_g_menu_img_skip_hlt;
    t_inp_lst_init.ui4_sel_mask             = ISL_ATTR_BIT_SKIPPED;   /* Should be changed */
    t_inp_lst_init.b_scroll                 = INP_LST_STL_SCROLL;
    t_inp_lst_init.b_wrap_over              = INP_LST_STL_WRAP_OVER;
    t_inp_lst_init.b_back_on_left           = INP_LST_BACK_ON_LEFT;

    return menu_pm_page_create(&t_g_menu_common_page_inp_lst,
                               (VOID*)&t_inp_lst_init,
                               pui4_page_id);

}


extern INT32 menu_common_create_page_bk_inp(UINT32 *pui4_page_id)
{
    INPUT_LIST_INIT_T    t_inp_lst_init;

    c_memset(&t_inp_lst_init, 0, sizeof(INPUT_LIST_INIT_T));

    t_inp_lst_init.ui2_msg_title            = MLM_MENU_KEY_INP_BK;
    t_inp_lst_init.ui2_max_rec_num          = INP_LST_ELEM_N;
    t_inp_lst_init.h_img_normal             = h_g_menu_img_unlock;
    t_inp_lst_init.h_img_highlight          = h_g_menu_img_unlock_hlt;
    t_inp_lst_init.h_img_selected           = h_g_menu_img_lock;
    t_inp_lst_init.h_img_selected_highlight = h_g_menu_img_lock_hlt;
    t_inp_lst_init.ui4_sel_mask             = ISL_ATTR_BIT_BLOCKED;
    t_inp_lst_init.b_scroll                 = INP_LST_STL_SCROLL;
    t_inp_lst_init.b_wrap_over              = INP_LST_STL_WRAP_OVER;
    t_inp_lst_init.b_back_on_left           = INP_LST_BACK_ON_LEFT;

    return menu_pm_page_create(&t_g_menu_common_page_inp_lst,
                               (VOID*)&t_inp_lst_init,
                               pui4_page_id);

}

extern INT32 menu_common_page_inp_lst_init(VOID)
{
    MENU_DEBUG_INPUT_SRC(DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    t_g_menu_common_page_inp_lst.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_inp_lst.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_inp_lst.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_inp_lst.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_inp_lst.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_inp_lst.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_inp_lst.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
#endif /* COMMON_INP_LST_ENABLE */

