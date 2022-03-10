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
 * $RCSfile: menu_page_vga_ambiguous.c,v $
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
#include "c_scc.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/lang/a_lang.h"

#include "res/app_util/config/a_cfg_custom.h"

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/* layout */
/*
  +----------------------------------------------------+
  |   1   |    Component 1                    |  icon  |
  +----------------------------------------------------+
   COL0     COL1                                 COL2
*/
#ifdef COMMON_VGA_AMBIGUOUS_ENABLE

#ifndef VGA_AMBI_LST_COL0_ALIGN
#define VGA_AMBI_LST_COL0_ALIGN      (WGL_AS_CENTER_CENTER)
#define MAX_VGA_AMBI_LST_NUM_LEN     (20)
#define VGA_AMBI_LST_COL0_W          (CH_LST2_COL0_W)
#define VGA_AMBI_LST_COL1_ALIGN      (WGL_AS_CENTER_CENTER)
#define MAX_VGA_AMBI_LST_NAME_LEN    (128)
#define VGA_AMBI_LST_COL1_W          (CH_LST2_COL1_W+CH_LST2_COL2_W)
#define VGA_AMBI_LST_COL2_ALIGN      (WGL_AS_CENTER_CENTER)
#define VGA_AMBI_LST_COL2_W          (CH_LST2_COL3_W)
#define VGA_AMBI_LST_ELEM_H          (CH_LST_ELEM_H)
#define VGA_AMBI_LST_X               (CH_LST_X)
#define VGA_AMBI_LST_Y               (CH_LST_Y)
#define VGA_AMBI_LST_W               (CH_LST_W)
#define VGA_AMBI_LST_H               (CH_LST_H)
#define VGA_AMBI_LST_ELEM_N          (CH_LST_ELEM_N)
#define VGA_AMBI_LST_BACK_ON_LEFT    (TRUE)
#endif


typedef struct _VGA_AMBI_LST_T
{
    HANDLE_T                h_lb_lst;
    BOOL                    b_is_refreshing;
} VGA_AMBI_LST_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_vga_ambi;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _set_ambiguous_vga_timing_num
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _set_ambiguous_vga_timing_num(UINT16 ui2_num)
{
    INT32 i4_ret = MENUR_OK;
    VSH_VGA_TIMING_OPTION_T  t_vga_timing_option;
    SIZE_T  t_size = sizeof(VSH_VGA_TIMING_OPTION_T);


    c_memset(&t_vga_timing_option, 0, sizeof(VSH_VGA_TIMING_OPTION_T));

    t_vga_timing_option.ui2_opt_index = (UINT16)(ui2_num + 1);
    t_vga_timing_option.b_is_default = TRUE;

    i4_ret = c_svctx_set_stream_attr(menu_get_crnt_svctx(),
                                     ST_VIDEO,
                                     SM_VSH_SET_TYPE_VGA_TIMING_OPTION,
                                      (VOID*)&t_vga_timing_option, t_size);
    MENU_CHK_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _get_ambiguous_vga_timing_num
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _get_ambiguous_vga_timing_num(UINT16 *pui2_num)
{
    INT32 i4_ret = MENUR_OK;
    VSH_AMBIG_VGA_TIMING_INFO_T  t_vga_timing_info;
    SIZE_T  t_size = sizeof(VSH_AMBIG_VGA_TIMING_INFO_T);




    c_memset(&t_vga_timing_info, 0, sizeof(VSH_AMBIG_VGA_TIMING_INFO_T));

    t_vga_timing_info.e_type = VSH_AMBIG_VGA_TIMING_TYPE_NUM_IN_GRP;
    i4_ret = c_svctx_get_stream_attr(menu_get_crnt_svctx(),
                                                    ST_VIDEO,
                                                    SM_VSH_GET_TYPE_AMBIG_VGA_TIMING,
                                                    (VOID*)&t_vga_timing_info,
                                                    &t_size);
    MENU_CHK_FAIL(i4_ret);


    *pui2_num = t_vga_timing_info.u.ui2_num;

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _get_ambiguous_vga_timing_option_by_index
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _get_ambiguous_vga_timing_option_by_index(UINT16 ui2_ind,
                                                                      VSH_AMBIG_VGA_TIMING_OPTION_T *pt_get_vga_timing_opt_info)
{
    INT32 i4_ret = MENUR_OK;
    VSH_AMBIG_VGA_TIMING_INFO_T  t_vga_timing_info;
    SIZE_T  t_size = sizeof(VSH_AMBIG_VGA_TIMING_INFO_T);

    c_memset(&t_vga_timing_info, 0, sizeof(VSH_AMBIG_VGA_TIMING_INFO_T));

    t_vga_timing_info.e_type = VSH_AMBIG_VGA_TIMING_TYPE_OPTION_IN_GRP;
    t_vga_timing_info.u.t_opt.ui2_opt_index = (UINT16)(ui2_ind + 1);  /* The index should be from 1;*/

    i4_ret = c_svctx_get_stream_attr(menu_get_crnt_svctx(),
                                                    ST_VIDEO,
                                                    SM_VSH_GET_TYPE_AMBIG_VGA_TIMING,
                                                     (VOID*)&t_vga_timing_info,
                                                    &t_size);
    MENU_CHK_FAIL(i4_ret);


    pt_get_vga_timing_opt_info->ui2_opt_index = t_vga_timing_info.u.t_opt.ui2_opt_index;
    pt_get_vga_timing_opt_info->ui2_ver_frequncy = t_vga_timing_info.u.t_opt.ui2_ver_frequncy;
    pt_get_vga_timing_opt_info->ui4_hor_resolution = t_vga_timing_info.u.t_opt.ui4_hor_resolution;
    pt_get_vga_timing_opt_info->ui4_ver_resolution = t_vga_timing_info.u.t_opt.ui4_ver_resolution;

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _get_ambiguous_vga_timing_get_crnt_opt_info
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _get_ambiguous_vga_timing_get_crnt_opt_info(
                                        VSH_AMBIG_VGA_TIMING_OPTION_T *pt_get_crnt_vga_timing_opt_info)
{
    INT32 i4_ret = MENUR_OK;
    VSH_AMBIG_VGA_TIMING_INFO_T  t_vga_timing_info;
    SIZE_T  t_size = sizeof(VSH_AMBIG_VGA_TIMING_INFO_T);

    c_memset(&t_vga_timing_info, 0, sizeof(VSH_AMBIG_VGA_TIMING_INFO_T));

    t_vga_timing_info.e_type = VSH_AMBIG_VGA_TIMING_TYPE_CURR_OPT_IN_GRP;
    i4_ret = c_svctx_get_stream_attr(menu_get_crnt_svctx(),
                                                    ST_VIDEO,
                                                    SM_VSH_GET_TYPE_AMBIG_VGA_TIMING,
                                                     (VOID*)&t_vga_timing_info,
                                                    &t_size);
    MENU_CHK_FAIL(i4_ret);


    pt_get_crnt_vga_timing_opt_info->ui2_opt_index = t_vga_timing_info.u.t_opt.ui2_opt_index;
    pt_get_crnt_vga_timing_opt_info->ui2_ver_frequncy = t_vga_timing_info.u.t_opt.ui2_ver_frequncy;
    pt_get_crnt_vga_timing_opt_info->ui4_hor_resolution = t_vga_timing_info.u.t_opt.ui4_hor_resolution;
    pt_get_crnt_vga_timing_opt_info->ui4_ver_resolution = t_vga_timing_info.u.t_opt.ui4_ver_resolution;

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_set_attach_data
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_set_attach_data(HANDLE_T         h_lb_lst,
                                       VGA_AMBI_LST_T*      pt_vga_ambi)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_lst,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_vga_ambi),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_get_attach_data
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_get_attach_data(HANDLE_T         h_lb_lst,
                                       VGA_AMBI_LST_T**     ppt_vga_ambi)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_lst,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_vga_ambi),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_get_elem_num
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_get_elem_num (UINT16 *pui2_elem_num)
{
    UINT16  ui2_elem_num;
    INT32   i4_ret;

    i4_ret = _get_ambiguous_vga_timing_num(&ui2_elem_num);
    MENU_CHK_FAIL(i4_ret);

    *pui2_elem_num = ui2_elem_num;

    if (MENUR_OK != i4_ret)
    {
        *pui2_elem_num = 0;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_get_sel_idx
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_get_sel_idx (UINT16 *p_ui2_index)
{
    VSH_AMBIG_VGA_TIMING_OPTION_T t_get_crnt_vga_timing_opt_info;

     /* variable initialization */
    c_memset(&t_get_crnt_vga_timing_opt_info, 0, sizeof(VSH_AMBIG_VGA_TIMING_OPTION_T));

    *p_ui2_index =0;

    _get_ambiguous_vga_timing_get_crnt_opt_info(&t_get_crnt_vga_timing_opt_info);

    *p_ui2_index = (UINT16)(t_get_crnt_vga_timing_opt_info.ui2_opt_index - 1);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_get_elem_text
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_get_elem_text ( UINT16             ui2_elem_idx,
                                   UTF16_T*           w2s_str,
                                   UINT32             ui4_len)
{

    INT32   i4_ret;
    CHAR    s_buf[13];
    VSH_AMBIG_VGA_TIMING_OPTION_T t_get_vga_timing_opt_info;

    /* variable initialization */
    c_memset(s_buf, 0, 13);
    c_memset(&t_get_vga_timing_opt_info, 0, sizeof(VSH_AMBIG_VGA_TIMING_OPTION_T));

    /* get ambiguous vga timing's optional information by index*/
    i4_ret = _get_ambiguous_vga_timing_option_by_index(ui2_elem_idx,
                                                                  &t_get_vga_timing_opt_info);
    if(i4_ret != MENUR_OK)
    {
        c_memset(w2s_str, 0, ui4_len);
    }

    /* print sesolution to string */
    c_sprintf(s_buf, "%d X %d", t_get_vga_timing_opt_info.ui4_hor_resolution, t_get_vga_timing_opt_info.ui4_ver_resolution);
    c_uc_ps_to_w2s(s_buf, w2s_str, (UINT32)ui4_len - 1);
    w2s_str[ui4_len - 1] = 0;


    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_on_sel
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_on_sel(HANDLE_T     h_lb_lst,
                       UINT16       ui2_idx)
{
    INT32            i4_ret;
    VGA_AMBI_LST_T*  pt_vga_ambi;

    /* get the channel list data */
    i4_ret = _vga_ambi_get_attach_data(h_lb_lst, &pt_vga_ambi);
    MENU_CHK_FAIL(i4_ret);

    if (pt_vga_ambi == NULL)
    {
        return MENUR_FAIL;
    }

    if (pt_vga_ambi->b_is_refreshing)
    {
        return MENUR_OK;
    }

    /**/
    i4_ret= _set_ambiguous_vga_timing_num(ui2_idx);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _help_lst_update
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _help_lst_update(VOID)
{
#if 0  /* If needed, change to use help tip */
    MENU_HELP_LST_BUCKET_T at_help_lst[] =
    {
        {h_g_menu_img_btn_enter,    MLM_MENU_KEY_HELP_SET},
        {h_g_menu_img_btn_select,   MLM_MENU_KEY_HELP_SELECT},
        {h_g_menu_img_btn_exit,     MLM_MENU_KEY_HELP_BACK}
    };

    menu_main_set_help(at_help_lst,
                       (UINT16)(sizeof(at_help_lst)/ sizeof(at_help_lst[0])));
#endif
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_on_notify
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_on_notify(HANDLE_T              h_lb_lst,
                               WGL_NOTIFY_DATA_T*    pt_nfy_data)
{
    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_LB_ELEM_SEL:
    {
        if (menu_get_cond() != MENU_COND_NOT_INIT)
        {
            if (pt_nfy_data->u.t_lb_elem_sel.b_is_selected == TRUE)
            {
                _vga_ambi_on_sel(h_lb_lst, pt_nfy_data->u.t_lb_elem_sel.ui2_elem_idx);
            }
        }
        break;
    }

    default:
        break;
    }

    return WMPR_DONE;
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_proc_fct
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_proc_fct(HANDLE_T           h_widget,
                              UINT32             ui4_msg,
                              VOID*              pv_param1,
                              VOID*              pv_param2)
{
    INT32 i4_ret;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
        {
            VGA_AMBI_LST_T* pt_vga_ambi;
            UINT16      ui2_hlt_idx;
            UINT16      ui2_sel_idx;
            UINT32      ui4_keycode = (UINT32)pv_param1;

            /* get the channel list data */
            i4_ret = _vga_ambi_get_attach_data(h_widget, &pt_vga_ambi);
            if(i4_ret != MENUR_OK)
            {
                return WGLR_OK;
            }

            switch (ui4_keycode)
            {
            case BTN_CURSOR_LEFT:
                menu_nav_back();
                return WGLR_OK;

            case BTN_RETURN:
                menu_nav_back();
                return WGLR_OK;

            case BTN_SELECT:
                ui2_hlt_idx = 0;
                c_wgl_do_cmd (pt_vga_ambi->h_lb_lst,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK (&ui2_hlt_idx),
                              NULL);

                _vga_ambi_get_sel_idx(&ui2_sel_idx);

                if (ui2_hlt_idx == ui2_sel_idx)
                {
                    /*keep selected status except users select another item. */
                    return WGLR_OK;
                }
                break;
            case BTN_CURSOR_UP:
            case BTN_CURSOR_DOWN:
                ui4_msg = WGL_MSG_KEY_DOWN;
                break;

            default:
                break;
            }
        }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_add_inp
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_add_inp(HANDLE_T         h_lb_lst,
                               VGA_AMBI_LST_T*      pt_vga_ambi,
                               UINT16           ui2_elem_idx)
{
   INT32                    i4_ret;
   CHAR                     s_str[MAX_VGA_AMBI_LST_NUM_LEN+1] = { 0 };
   UTF16_T                  w2s_digits[MAX_VGA_AMBI_LST_NUM_LEN+1];
   UTF16_T                  w2s_name[MAX_VGA_AMBI_LST_NAME_LEN+1];
   WGL_LB_ITEM_T            at_items[3];
   WGL_LB_ITEM_IMG_SUIT_T   t_img_suit;

    /* Get the input source # */
    c_memset(w2s_digits, 0, sizeof(w2s_digits));
    c_sprintf(s_str,"%d", ui2_elem_idx + 1);
    c_uc_ps_to_w2s(s_str ,w2s_digits, MAX_VGA_AMBI_LST_NUM_LEN);

    /* Get the display name of input source*/
    c_memset(w2s_name, 0, sizeof(w2s_name));
#ifndef  UNIT_TEST
    _vga_ambi_get_elem_text (ui2_elem_idx,
                             w2s_name,
                             MAX_VGA_AMBI_LST_NAME_LEN);
#endif

    /* Append the data */
    c_memset(&t_img_suit, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit.h_normal                     = h_g_menu_img_unskip;
    t_img_suit.h_disable                    = NULL_HANDLE;
    t_img_suit.h_highlight                  = h_g_menu_img_unskip_hlt;
    t_img_suit.h_highlight_unfocus          = NULL_HANDLE;
    t_img_suit.h_pushed                     = NULL_HANDLE;
    t_img_suit.h_selected                   = h_g_menu_img_skip;
    t_img_suit.h_selected_disable           = NULL_HANDLE;
    t_img_suit.h_selected_highlight         = h_g_menu_img_skip_hlt;
    t_img_suit.h_selected_highlight_unfocus = NULL_HANDLE;
    t_img_suit.h_selected_pushed            = NULL_HANDLE;

    at_items[0].e_col_type       = LB_COL_TYPE_TEXT;
#ifdef UNIT_TEST
    at_items[0].data.pw2s_text   = L"01";
#else
    at_items[0].data.pw2s_text   = w2s_digits;
#endif

    at_items[1].e_col_type       = LB_COL_TYPE_TEXT;
#ifdef UNIT_TEST
    at_items[1].data.pw2s_text   = L"Hello";
#else
    at_items[1].data.pw2s_text   = w2s_name;
#endif
    at_items[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_items[2].data.pt_img_suit = &t_img_suit;

     /* append item */
    i4_ret = c_wgl_do_cmd(h_lb_lst,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(at_items),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_create
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_create(HANDLE_T         h_parent,
                       INT32            i4_x,
                       INT32            i4_y,
                       INT32            i4_w,
                       INT32            i4_h,
                       VGA_AMBI_LST_T*      pt_vga_ambi,
                       HANDLE_T*        ph_lb_lst)
{
    INT32               i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[3];
    GL_RECT_T           t_rect;
    WGL_LB_KEY_MAP_T    t_lb_key_map;

    /* input source no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = VGA_AMBI_LST_COL0_ALIGN;
    at_cols[0].ui2_max_text_len = MAX_VGA_AMBI_LST_NUM_LEN;
    at_cols[0].ui2_width        = VGA_AMBI_LST_COL0_W;

    /* channel name or starting time */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = VGA_AMBI_LST_COL1_ALIGN;
    at_cols[1].ui2_max_text_len = MAX_VGA_AMBI_LST_NAME_LEN;
    at_cols[1].ui2_width        = VGA_AMBI_LST_COL1_W;

    /* pre-selected */
    at_cols[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[2].ui1_align        = VGA_AMBI_LST_COL2_ALIGN;
    at_cols[2].ui2_width        = VGA_AMBI_LST_COL2_W;


    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_NO_SCROLL;

#ifndef APP_MENU_IMG_UI
    t_lb_init.ui4_style         |= WGL_STL_GL_NO_IMG_UI;
#endif


    t_lb_init.ui2_max_elem_num  = VGA_AMBI_LST_ELEM_N;
    t_lb_init.ui2_elem_size     = VGA_AMBI_LST_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 3;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect, i4_x, i4_y, i4_w,i4_h);

    i4_ret = menu_list2_create (h_parent,
                                &t_rect,
                                _vga_ambi_proc_fct,
                                & t_lb_init,
                                NULL,
                                ph_lb_lst);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for input source list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next       = BTN_CURSOR_DOWN;
    t_lb_key_map.ui4_key_prev       = BTN_CURSOR_UP;
    t_lb_key_map.ui4_key_select     = BTN_SELECT;
    t_lb_key_map.ui4_key_page_up    = BTN_RED;
    t_lb_key_map.ui4_key_page_down  = BTN_GREEN;
    i4_ret = c_wgl_do_cmd(*ph_lb_lst, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_CHK_FAIL(i4_ret);

    /* attach data */
    i4_ret = _vga_ambi_set_attach_data(*ph_lb_lst, pt_vga_ambi);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_refresh
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_refresh (HANDLE_T   h_lb_lst)
{
    INT32         i4_ret = MENUR_OK;
    VGA_AMBI_LST_T*   pt_vga_ambi;
    UINT16        ui2_elem_num;
    UINT16        ui2_elem_idx;
    UINT16        ui2_sel_idx;

    /* get the list data */
    _vga_ambi_get_attach_data(h_lb_lst, &pt_vga_ambi);
    if (pt_vga_ambi == NULL)
    {
        return MENUR_FAIL;
    }

    /* Set the refreshing flag */
    pt_vga_ambi->b_is_refreshing = TRUE;

    /* clear the list */
    i4_ret = c_wgl_do_cmd(h_lb_lst,
                          WGL_CMD_LB_DEL_ALL,
                          NULL, NULL);
    MENU_CHK_FAIL(i4_ret);

    /* get element number */

#ifdef UNIT_TEST
    ui2_elem_num = 5;
#else
    i4_ret = _vga_ambi_get_elem_num(&ui2_elem_num);
    MENU_CHK_FAIL(i4_ret);
#endif

    /* check if the element number exceeds the max number */
    if(ui2_elem_num > VGA_AMBI_LST_ELEM_N)
    {
        DBG_ERROR(("<MENU> Record number exceeds max sec number: %d < %d.\r\n", ui2_elem_num, VGA_AMBI_LST_ELEM_N));
        return MENUR_FAIL;
    }

    /* iterate */
    for(ui2_elem_idx = 0; ui2_elem_idx < ui2_elem_num; ui2_elem_idx++)
    {
        i4_ret = _vga_ambi_add_inp (h_lb_lst, pt_vga_ambi, ui2_elem_idx);
        MENU_CHK_FAIL(i4_ret);
    }

    /* Select element */
#ifdef UNIT_TEST
     ui2_sel_idx =0;
#else
     i4_ret = _vga_ambi_get_sel_idx(&ui2_sel_idx);
     MENU_CHK_FAIL(i4_ret);
#endif
    i4_ret = c_wgl_do_cmd(h_lb_lst,
                          WGL_CMD_LB_SEL_ELEM,
                          WGL_PACK(ui2_sel_idx),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set the refreshing flag */
    pt_vga_ambi->b_is_refreshing = FALSE;

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _vga_ambi_hlt_elem
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vga_ambi_hlt_elem (HANDLE_T   h_lb_lst)
{
    INT32           i4_ret;
    VGA_AMBI_LST_T*     pt_vga_ambi;
    UINT16          ui2_hlt_idx;

    /* get the channel list data */
    _vga_ambi_get_attach_data(h_lb_lst, &pt_vga_ambi);
    if (pt_vga_ambi == NULL)
    {
        return MENUR_FAIL;
    }
#ifdef UNIT_TEST
    ui2_hlt_idx =0;
#else
    _vga_ambi_get_sel_idx (&ui2_hlt_idx);
#endif
    i4_ret = c_wgl_do_cmd(h_lb_lst,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui2_hlt_idx),                            /* hlt elem */
                          WGL_PACK(ui2_hlt_idx % (CONTENT_H / GRID_H)));    /* hlt pos */
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _frm_proc_fct
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
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
            _vga_ambi_on_notify(h_source, pt_nfy_data);
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
    INT32               i4_ret           = MENUR_FAIL;
    VGA_AMBI_LST_T*     pt_vga_ambi      = NULL;
    HANDLE_T            h_cnt_frm;

    /* Attach data */
    do
    {
        i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        pt_vga_ambi = c_mem_alloc(sizeof(VGA_AMBI_LST_T));

        if(pt_vga_ambi == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        c_memset(pt_vga_ambi, 0, sizeof(VGA_AMBI_LST_T));

        i4_ret = menu_page_set_data(ui4_page_id, pt_vga_ambi);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /* Create input list box */
        i4_ret = _vga_ambi_create(h_cnt_frm,
                    VGA_AMBI_LST_X,
                    VGA_AMBI_LST_Y,
                    VGA_AMBI_LST_W,
                    VGA_AMBI_LST_H,
                    pt_vga_ambi,
                    &pt_vga_ambi->h_lb_lst);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = c_wgl_set_visibility(h_cnt_frm, WGL_SW_RECURSIVE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = c_wgl_set_visibility(h_cnt_frm, WGL_SW_HIDE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = menu_page_set_proc_func(ui4_page_id, _cnt_frm_proc_fct);
        if(i4_ret != WGLR_OK)
        {
            break;
        }
    } while(0);

    if(i4_ret != MENUR_OK)
    {
        if(pt_vga_ambi != NULL)
        {
            if(pt_vga_ambi->h_lb_lst != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_vga_ambi->h_lb_lst);
            }
            c_mem_free(pt_vga_ambi);
        }
    }

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    INT32 i4_ret;
    VGA_AMBI_LST_T* pt_vga_ambi = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_vga_ambi);

    if(i4_ret == MENUR_OK)
    {
        if(pt_vga_ambi != NULL)
        {
            if(pt_vga_ambi->h_lb_lst != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_vga_ambi->h_lb_lst);
            }
            c_mem_free(pt_vga_ambi);
        }
    }

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32 i4_ret;
    VGA_AMBI_LST_T* pt_vga_ambi = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_vga_ambi);
    MENU_CHK_FAIL(i4_ret);

    _vga_ambi_refresh(pt_vga_ambi->h_lb_lst);

    _vga_ambi_hlt_elem(pt_vga_ambi->h_lb_lst);

    menu_main_set_title(MLM_MENU_KEY_VGA_AMBIGUOUS_TIMING);

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
    VGA_AMBI_LST_T* pt_vga_ambi = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_vga_ambi);
    MENU_CHK_FAIL(i4_ret);

    c_wgl_set_focus(pt_vga_ambi->h_lb_lst, WGL_NO_AUTO_REPAINT);

    _help_lst_update();

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
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

extern INT32 menu_common_get_ambiguous_vga_timing_num(UINT16 *pui2_num)
{
    INT32 i4_ret;

    i4_ret = _get_ambiguous_vga_timing_num(pui2_num);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

extern INT32 menu_common_vga_ambigous_init(VOID)
{
    t_g_menu_common_page_vga_ambi.pf_menu_page_create     = _on_page_create;
    t_g_menu_common_page_vga_ambi.pf_menu_page_destroy    = _on_page_destroy;
    t_g_menu_common_page_vga_ambi.pf_menu_page_show       = _on_page_show;
    t_g_menu_common_page_vga_ambi.pf_menu_page_hide       = _on_page_hide;
    t_g_menu_common_page_vga_ambi.pf_menu_page_get_focus  = _on_page_get_focus;
    t_g_menu_common_page_vga_ambi.pf_menu_page_lose_focus = _on_page_lose_focus;
    t_g_menu_common_page_vga_ambi.pf_menu_page_update     = _on_page_update;

    return MENUR_OK;
}
#endif /* COMMON_VGA_AMBIGUOUS_ENABLE */
