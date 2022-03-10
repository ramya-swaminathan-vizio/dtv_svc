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
 * $RCSfile: optl.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *
 *
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_common.h"

#include "c_handle.h"
#include "c_wgl_image.h"
#include "c_wgl_sets.h"
#include "c_wgl.h"
#include "optl.h"
#include "res/app_util/option_list/optl_rc.h"            /* Custom Logic */

#include "res/app_util/option_list/optl_img.h"
#ifdef OPTL_GUI_AUTHORING
#include "res/app_util/option_list/gen/app_util_option_list_option_list_layout.h"
#endif

static UINT32 m_ui4_init_cnt = 0;
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name:
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
INT32 _optl_res_init(VOID)
{
    INT32 i4_ret;
    if (0 == m_ui4_init_cnt)
    {
#ifdef OPTL_GUI_AUTHORING
        i4_ret = app_util_option_list_gen_init_image();
        OPTL_CHK_FAIL(i4_ret);
#else
        optl_init_image();
#endif
    }
    m_ui4_init_cnt++;

    return OPTLR_OK;
}

INT32 _optl_res_deinit(VOID)
{
    if (m_ui4_init_cnt)
    {
        m_ui4_init_cnt--;
    }

    if (0 == m_ui4_init_cnt)
    {
#ifdef OPTL_GUI_AUTHORING
        app_util_option_list_gen_deinit_image();
#else
        optl_deinit_image();
#endif
    }

    return OPTLR_OK;
}

static INT32 _optl_set_attach_data(
                    HANDLE_T            h_optl_handle,
                    OPTL_CONTROL_T*     pt_opt_list)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_optl_handle,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_opt_list),
                          NULL);
    OPTL_CHK_FAIL(i4_ret);

    return OPTLR_OK;

}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _optl_get_attach_data(
                    HANDLE_T            pt_opt_list,
                    OPTL_CONTROL_T**    ppt_opt_list)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(pt_opt_list,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_opt_list),
                          NULL);
    OPTL_CHK_FAIL(i4_ret);

    return OPTLR_OK;
}

#ifndef OPTL_GUI_AUTHORING
/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _optl_set_list_box_attr(
                    OPTL_LIST_TYPE_T    e_list_type,
                    HANDLE_T            h_list_box,
                    WGL_HIMG_TPL_T      h_lb_hlt_bk,
                    WGL_HIMG_TPL_T      h_lb_uf_hlt_bk,
                    WGL_HIMG_TPL_T      h_lb_nml_bk,
                    OPTL_INIT_T*        pt_optl_init)
{
    INT32                       i4_ret;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_FONT_INFO_T             t_fnt_info;

    /* Set image background for each item*/
    t_img_elem.h_normal              = h_lb_nml_bk;
    t_img_elem.h_disable             = NULL_HANDLE;
    t_img_elem.h_highlight           = h_lb_hlt_bk;
    t_img_elem.h_highlight_unfocus   = h_lb_uf_hlt_bk;
    t_img_elem.h_pushed              = NULL_HANDLE;
    t_img_elem.h_selected            = NULL_HANDLE;
    t_img_elem.h_selected_disable    = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(
                    h_list_box,
                    WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                    WGL_PACK(& t_img_elem),
                    NULL
                    );

    OPTL_CHK_FAIL(i4_ret);

    /* Set font for each item of col*/
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = OPTL_LIST_FONT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(
                    h_list_box,
                    WGL_CMD_LB_SET_COL_FONT,
                    WGL_PACK(0),
                    WGL_PACK(&t_fnt_info)
                    );
    OPTL_CHK_FAIL(i4_ret);

    /* Set fg color for each item */
    if (e_list_type == OPTL_MAIN_LIST)
    {
        if(pt_optl_init->ui4_custom_flag & OPTL_CUST_MASK_MAIN_LB_TXT_CLR)
        {
            i4_ret = c_wgl_do_cmd(h_list_box,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2(0, WGL_CLR_TEXT),
                                  WGL_PACK(&(pt_optl_init->t_customization.t_main_lb_col_txt_color)));
        }
        else
        {
            t_color_elem.t_normal             = t_g_oux_clr_black;
            t_color_elem.t_disable            = t_g_oux_clr_disnable;
            t_color_elem.t_highlight          = t_g_oux_clr_white;
            t_color_elem.t_highlight_unfocus  = t_g_oux_clr_180;
            t_color_elem.t_pushed             = t_g_oux_clr_black;
            t_color_elem.t_selected           = t_g_oux_clr_black;
            t_color_elem.t_selected_disable   = t_g_oux_clr_black;

            i4_ret = c_wgl_do_cmd(h_list_box,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2(0, WGL_CLR_TEXT),
                                  WGL_PACK(&t_color_elem));
        }
    }
    else
    {
        if(pt_optl_init->ui4_custom_flag & OPTL_CUST_MASK_SUB_LB_TXT_CLR)
        {
            i4_ret = c_wgl_do_cmd(h_list_box,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2(0, WGL_CLR_TEXT),
                                  WGL_PACK(&(pt_optl_init->t_customization.t_sub_lb_col_txt_color)));
        }
        else
        {
            t_color_elem.t_normal             = t_g_oux_clr_black;
            t_color_elem.t_disable            = t_g_oux_clr_disnable;
            t_color_elem.t_highlight          = t_g_oux_clr_white;
            t_color_elem.t_highlight_unfocus  = t_g_oux_clr_180;
            t_color_elem.t_pushed             = t_g_oux_clr_black;
            t_color_elem.t_selected           = t_g_oux_clr_black;
            t_color_elem.t_selected_disable   = t_g_oux_clr_black;

            i4_ret = c_wgl_do_cmd(h_list_box,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2(0, WGL_CLR_TEXT),
                                  WGL_PACK(&t_color_elem));
        }
    }
    OPTL_CHK_FAIL(i4_ret);

    /* Set highlight margin to 1. */
    i4_ret = c_wgl_do_cmd (h_list_box,
                           WGL_CMD_LB_SET_HLT_MARGIN,
                           WGL_PACK (0),
                           NULL);

    OPTL_CHK_FAIL(i4_ret);

    return OPTLR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _optl_list_key_map
 * Description: Set key map for listbox
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _optl_list_key_map(
                        HANDLE_T                h_listbox
                        )
{
    INT32                   i4_ret;
    WGL_LB_KEY_MAP_T        t_key_map = {0};

    t_key_map.ui4_key_next      = BTN_CURSOR_DOWN;
    t_key_map.ui4_key_prev      = BTN_CURSOR_UP;
    t_key_map.ui4_key_select    = 0;
    t_key_map.ui4_key_page_up   = 0;
    t_key_map.ui4_key_page_down = 0;

    i4_ret = c_wgl_do_cmd(
                    h_listbox,
                    WGL_CMD_LB_SET_KEY_MAP,
                    WGL_PACK(& t_key_map),
                    NULL
                    );
    OPTL_CHK_FAIL(i4_ret);

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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

static INT32 _optl_set_main_lst_text(
                    OPTL_CONTROL_T*      pt_opt_list)
{
    INT32               i4_ret;
    UINT8               ui1_idx;
    UTF16_T             w2s_menu_item_string[OPTL_LB_MAIN_TXT_MAX + 1] = {0};

    i4_ret = c_wgl_do_cmd(
                        pt_opt_list->h_back_btn,
                        WGL_CMD_BTN_SET_TEXT,
                        WGL_PACK(pt_opt_list->pw2s_title),
                        WGL_PACK((UINT16)0xFFFF));

    i4_ret = c_wgl_do_cmd(
                        pt_opt_list->h_list_box,
                        WGL_CMD_LB_SET_ELEM_NUM,
                        WGL_PACK(pt_opt_list->ui1_main_lb_item_num),
                        NULL
                        );
    OPTL_CHK_FAIL(i4_ret);

    for (ui1_idx = 0; (ui1_idx < OPTL_LB_MAIN_ITEM_DFLT_NUM)&&(ui1_idx < pt_opt_list->ui1_main_lb_item_num); ui1_idx++)
    {
        c_uc_w2s_strncpy(w2s_menu_item_string,
                        pt_opt_list->t_main_item[ui1_idx].pw2s_text,
                        OPTL_LB_MAIN_TXT_MAX);

        i4_ret = c_wgl_do_cmd(
                    pt_opt_list->h_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(ui1_idx, 0),
                    WGL_PACK(pt_opt_list->t_main_item[ui1_idx].pw2s_label)
                    );

        i4_ret = c_wgl_do_cmd(
                    pt_opt_list->h_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(ui1_idx, 1),
                    WGL_PACK(w2s_menu_item_string)
                    );
        OPTL_CHK_FAIL(i4_ret);
    }
    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
/*-----------------------------------------------------------------------------
 * Name: _optl_get_main_lb_next_hlt_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _optl_get_main_lb_next_hlt_idx(OPTL_CONTROL_T*     pt_opt_list,
                                                UINT8*                  pui1_hlt_idx,
                                                BOOL                 b_is_down)
{
    INT32                        i4_ret = -1;
    UINT8                        ui1_idx;
    UINT8                        ui1_hlt_idx;
    UINT8                        ui1_loop_cnt = 0;
    UINT16                       ui2_hlt_idx = 0;

    i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(&ui2_hlt_idx),
                          NULL);
    OPTL_CHK_FAIL(i4_ret);
    ui1_hlt_idx = (UINT8)ui2_hlt_idx;

    *pui1_hlt_idx = ui1_hlt_idx;

    ui1_idx = ui1_hlt_idx;

    /* To avoid divide by 0 */
    if (pt_opt_list->ui1_main_lb_item_num == 0)
    {
        *pui1_hlt_idx = 0;
        return OPTLR_OK;
    }

    do
    {
        if(b_is_down == TRUE)
        {
            ui1_idx = (UINT8)((ui1_idx + 1)%(pt_opt_list->ui1_main_lb_item_num));
        }
        else
        {
            ui1_idx = (UINT8)((ui1_idx + pt_opt_list->ui1_main_lb_item_num - 1) %(pt_opt_list->ui1_main_lb_item_num));
        }

        if((ui1_idx < OPTL_LB_MAIN_ITEM_DFLT_NUM)&&(ui1_idx < pt_opt_list->ui1_main_lb_item_num))
        {
            if(pt_opt_list->t_main_item[ui1_idx].b_is_disable != TRUE)
            {
                *pui1_hlt_idx = ui1_idx;

                break;
            }
        }
        else
        {
            break;
        }

        ui1_loop_cnt++;
        if (ui1_loop_cnt > pt_opt_list->ui1_main_lb_item_num)
        {
            return OPTLR_FAIL;
        }
    }
    while(1);

    return  OPTLR_OK;
}

static INT32 _optl_set_sub_lst_text(
                    OPTL_CONTROL_T*      pt_opt_list)
{
    INT32               i4_ret;
    UINT8               ui1_idx;
    UINT8               ui1_main_hlt_idx;
    UTF16_T             w2s_sub_item_string[OPTL_LB_SUB_TXT_MAX + 1] = {0};

    if(pt_opt_list->ui1_main_lb_hlt_idx >= OPTL_LB_MAIN_ITEM_DFLT_NUM)
    {
        return OPTLR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                        pt_opt_list->h_back_btn,
                        WGL_CMD_BTN_SET_TEXT,
                        WGL_PACK(pt_opt_list->t_main_item[pt_opt_list->ui1_main_lb_hlt_idx].u.t_subopt_list.pw2s_title),
                        WGL_PACK((UINT16)0xFFFF));

    ui1_main_hlt_idx = pt_opt_list->ui1_main_lb_hlt_idx;
    pt_opt_list->ui1_sub_lb_item_num
            = (UINT8)(pt_opt_list->t_main_item[pt_opt_list->ui1_main_lb_hlt_idx].u.t_subopt_list.ui2_num_of_sub_items);


    i4_ret = c_wgl_do_cmd(
                        pt_opt_list->h_list_box,
                        WGL_CMD_LB_SET_ELEM_NUM,
                        WGL_PACK(pt_opt_list->ui1_sub_lb_item_num),
                        NULL
                        );
    OPTL_CHK_FAIL(i4_ret);

    for (ui1_idx = 0; ui1_idx < pt_opt_list->ui1_sub_lb_item_num; ui1_idx++)
    {
        c_uc_w2s_strncpy(w2s_sub_item_string,
                        pt_opt_list->t_main_item[ui1_main_hlt_idx].u.t_subopt_list.pt_sub_item[ui1_idx].pw2s_text,
                        OPTL_LB_SUB_TXT_MAX);

        i4_ret = c_wgl_do_cmd(
                    pt_opt_list->h_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(ui1_idx, 0),
                    WGL_PACK(pt_opt_list->t_main_item[ui1_main_hlt_idx].u.t_subopt_list.pt_sub_item[ui1_idx].pw2s_label)
                    );

        i4_ret = c_wgl_do_cmd(
                    pt_opt_list->h_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(ui1_idx, 1),
                    WGL_PACK(w2s_sub_item_string)
                    );
        OPTL_CHK_FAIL(i4_ret);
    }
    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _optl_destroy(
                    HANDLE_T            h_optl_handle)

{
    INT32             i4_ret;
    OPTL_CONTROL_T*    pt_opt_list;
    UINT8              ui1_idx, ui1_sub_idx;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                   &pt_opt_list);

    if(i4_ret != OPTLR_OK)
    {
        return i4_ret;
    }

    /* Release childs*/
    app_util_option_list_option_list_destroy_ui_mi(pt_opt_list->h_layout_inst);

    /* delete the timer*/
    if (pt_opt_list->ui4_style_mask & OPTL_STYLE_MASK_DEFAULT_HIDE_TIMEOUT)
    {
        if(NULL_HANDLE != pt_opt_list->h_timer_auto_hide)
        {
            i4_ret = c_timer_delete(pt_opt_list->h_timer_auto_hide);

            if(OPTLR_OK!= i4_ret)
            {
                return OPTLR_FAIL;
            }
        }
    }

    for (ui1_idx = 0; ui1_idx < OPTL_LB_MAIN_ITEM_DFLT_NUM; ui1_idx++)
    {
        if (pt_opt_list->t_main_item[ui1_idx].e_type == OPTL_ITEM_TYPE_SUBLIST)
        {
            for (ui1_sub_idx = 0; ui1_sub_idx < (UINT8)(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.ui2_num_of_sub_items); ui1_sub_idx++)
            {
                if (pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text != NULL)
                {
                    c_mem_free(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text);
                    pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text = NULL;
                }
            }

            if (pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item != NULL)
            {
                c_mem_free(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item);
                pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item = NULL;
            }

        }
    }

    /* Release the structure */
    c_mem_free(pt_opt_list);

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
static VOID _optl_hide_timer_nfy_fct(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    OPTL_CONTROL_T*     pt_opt_list = (OPTL_CONTROL_T*) pv_tag;

    if (pt_opt_list == NULL)
    {
        return;
    }

    if (pt_opt_list->ui4_style_mask & OPTL_STYLE_MASK_DEFAULT_HIDE_TIMEOUT)
    {
        if ( pt_opt_list->pf_fct != NULL)
        {
            pt_opt_list->pf_fct(pt_opt_list->pv_tag,
                  OPTL_MSG_HIDE_TIMEOUT,
                  NULL,
                  NULL);
        }
    }
}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _optl_start_timer (
                    OPTL_CONTROL_T*     pt_opt_list
                    )
{
    INT32    i4_ret = OPTLR_OK;

    if (pt_opt_list->ui4_style_mask & OPTL_STYLE_MASK_DEFAULT_HIDE_TIMEOUT)
    {
        i4_ret = c_timer_start (pt_opt_list->h_timer_auto_hide,
                                pt_opt_list->ui4_sleep_time,
                                X_TIMER_FLAG_ONCE,
                                _optl_hide_timer_nfy_fct,
                                pt_opt_list);
        if (i4_ret < OSR_OK)
        {
            return OPTLR_FAIL;
        }
    }
    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _optl_stop_timer (
                    OPTL_CONTROL_T*     pt_opt_list
                    )
{
    INT32    i4_ret = OPTLR_OK;

    if (pt_opt_list->ui4_style_mask & OPTL_STYLE_MASK_DEFAULT_HIDE_TIMEOUT)
    {
        i4_ret = c_timer_stop (pt_opt_list->h_timer_auto_hide);

         if (i4_ret < OSR_OK)
         {
            return OPTLR_FAIL;
         }

    }

    if (i4_ret < OSR_OK)
    {
        return OPTLR_FAIL;
    }

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _optl_create_timer (
                    OPTL_CONTROL_T*     pt_opt_list
                    )
{
    INT32    i4_ret = OPTLR_OK;

    if (pt_opt_list->ui4_style_mask & OPTL_STYLE_MASK_DEFAULT_HIDE_TIMEOUT)
    {
         i4_ret = c_timer_create (& pt_opt_list->h_timer_auto_hide);

         if (i4_ret < OSR_OK)
         {
            return OPTLR_FAIL;
         }
    }

    return OPTLR_OK;
}
/*----------------------------------------------------------------------------
 * Name:
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
static INT32  _optl_launch_sub_menu(
                     OPTL_CONTROL_T*     pt_opt_list)
{
    INT32               i4_ret;

    /* 1. Set items text to Sub Opton list */
    i4_ret = _optl_set_sub_lst_text(pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /* 2. Set hightlight of the sub list*/
    i4_ret = c_wgl_do_cmd( pt_opt_list->h_list_box,
                           WGL_CMD_LB_HLT_ELEM_VISIBLE,
                           WGL_PACK(pt_opt_list->ui1_sub_lb_hlt_idx),
                           WGL_PACK(pt_opt_list->ui1_sub_lb_hlt_idx));

    /* 3. Ensure the highlight element could be visible */
    i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                          WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                          NULL,
                          NULL);

    /* 4. Set the focus to Sub Option list */
    pt_opt_list->e_hlt_list = OPTL_SUB_LIST;
    i4_ret = c_wgl_set_focus(pt_opt_list->h_list_box, FALSE);
    OPTL_CHK_FAIL(i4_ret);

    /* 5. Set visibility for content indicator */

    /* 6. Set to topmost */
    i4_ret = c_wgl_insert (pt_opt_list->h_frm_optl,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    OPTL_CHK_FAIL(i4_ret);

    /* 7. Repaint the frame */
    i4_ret = c_wgl_repaint(pt_opt_list->h_frm_optl, NULL, TRUE);
    OPTL_CHK_FAIL(i4_ret);
    return OPTLR_OK;

}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32  _optl_close_sub_menu(
                     OPTL_CONTROL_T*     pt_opt_list)
{
    INT32  i4_ret;
    pt_opt_list->ui1_sub_lb_hlt_idx = OPTL_LB_SUB_DFLT_HLT_IDX;

    /* 1. Set elements in the main list */
    i4_ret = _optl_set_main_lst_text(pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /* 2. Set focus on the main list box */
    pt_opt_list->e_hlt_list = OPTL_MAIN_LIST;

    /* 3. Set hightlight of the main list*/
    i4_ret = c_wgl_do_cmd( pt_opt_list->h_list_box,
                           WGL_CMD_LB_HLT_ELEM,
                           WGL_PACK(pt_opt_list->ui1_main_lb_hlt_idx),
                           NULL);
    OPTL_CHK_FAIL(i4_ret);

    /* 4. Ensure the highlight element could be visible */
    i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                          WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                          NULL,
                          NULL);
    OPTL_CHK_FAIL(i4_ret);

    c_wgl_set_focus(pt_opt_list->h_list_box, WGL_NO_AUTO_REPAINT);

    i4_ret = c_wgl_repaint(pt_opt_list->h_frm_optl, NULL, TRUE);
    OPTL_CHK_FAIL(i4_ret);

    /* 5. Send Cancel message to the caller */
    if (pt_opt_list->pf_fct != NULL)
    {
        pt_opt_list->pf_fct(pt_opt_list->pv_tag,
              OPTL_MSG_ITEM_HIGHLIGHT ,
              (VOID*)(UINT32)pt_opt_list->ui1_main_lb_hlt_idx,
              (VOID*)OPTL_INVALID_INDEX);
    }

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32  _optl_check_to_enter_sub_menu(
                     OPTL_CONTROL_T*     pt_opt_list)
{
    UINT16 ui2_hlt_idx           = pt_opt_list->ui1_main_lb_hlt_idx;
    UINT16 ui2_sublist_hlt_index = OPTL_LB_SUB_DFLT_HLT_IDX;
    INT32  i4_ret                = 0;

    if(ui2_hlt_idx >= OPTL_LB_MAIN_ITEM_DFLT_NUM)
    {
        return OPTLR_FAIL;
    }

    /* Check current sublist's hlt index */
    if (pt_opt_list->t_main_item[ui2_hlt_idx].u.t_subopt_list.pf_get_sub_hlt_idx_fct != NULL)
    {
        pt_opt_list->t_main_item[ui2_hlt_idx].u.t_subopt_list.pf_get_sub_hlt_idx_fct(
        pt_opt_list->t_main_item[ui2_hlt_idx].u.t_subopt_list.pv_tag,
        & ui2_sublist_hlt_index);

        /* Check range is correct */
        if (ui2_sublist_hlt_index >= pt_opt_list->t_main_item[ui2_hlt_idx].u.t_subopt_list.ui2_num_of_sub_items)
        {
            /* Range is not correct. Use default one. */
            ui2_sublist_hlt_index = OPTL_LB_SUB_DFLT_HLT_IDX;
        }
    }

    /* set current sublist hlt index */
    pt_opt_list->ui1_sub_lb_hlt_idx = (UINT8)ui2_sublist_hlt_index;

    /* Open the Sub Option list */
    i4_ret = _optl_launch_sub_menu(pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /* Send Highlight message to the caller */
    if (pt_opt_list->pf_fct != NULL)
    {
        pt_opt_list->pf_fct(pt_opt_list->pv_tag,
              OPTL_MSG_ITEM_HIGHLIGHT ,
              (VOID*)(UINT32)ui2_hlt_idx,
              (VOID*)(UINT32)pt_opt_list->ui1_sub_lb_hlt_idx);
    }

    return OPTLR_OK;
}

static INT32 _optl_lst_lb_hlt_chg(HANDLE_T          h_widget,
                                  OPTL_CONTROL_T*   pt_opt_list,
                                  UINT32            ui4_key_code,
                                  VOID*             pv_param2)
{
    INT32        i4_ret;
    UINT8        ui1_main_lb_hlt_idx = 0;
    UINT8        ui1_hlt_idx = 0;
    UINT16       ui2_hlt_idx = 0;
    BOOL         b_idx_change = FALSE;
    UINT16       ui2_item_num = 0;

    i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&ui2_item_num),
                          NULL);

    OPTL_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(&ui2_hlt_idx),
                          NULL);

    OPTL_CHK_FAIL(i4_ret);

    if(BTN_CURSOR_DOWN == ui4_key_code)
    {
        if (0 != ui2_item_num &&
            (ui2_hlt_idx + 1) == ui2_item_num)
        {
            return WGLR_OK;
        }
        /*  get next hlt elem idx */
        i4_ret = _optl_get_main_lb_next_hlt_idx(pt_opt_list,
                                                &ui1_main_lb_hlt_idx,
                                                TRUE);
        if (i4_ret != OPTLR_OK)
        {
            return WGLR_OK;
        }
    }
    else
    {
        if (0 != ui2_item_num &&
            ui2_hlt_idx == 0)
        {
            c_wgl_set_focus(pt_opt_list->h_back_btn, WGL_SYNC_AUTO_REPAINT);
            return WGLR_OK;
        }
        i4_ret = _optl_get_main_lb_next_hlt_idx(pt_opt_list,
                                                &ui1_main_lb_hlt_idx,
                                                FALSE);
        if (i4_ret != OPTLR_OK)
        {
            return WGLR_OK;
        }
    }

    /* if cursor down/up, run WIDGET default key handler first.*/
    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    WGL_MSG_KEY_DOWN,
                    (VOID*)ui4_key_code,
                    pv_param2
                    );
    OPTL_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
              WGL_CMD_LB_GET_HLT_INDEX,
          WGL_PACK(&ui2_hlt_idx),
              NULL);
    OPTL_CHK_FAIL(i4_ret);
    ui1_hlt_idx = (UINT8)ui2_hlt_idx;

    if (OPTL_MAIN_LIST == pt_opt_list->e_hlt_list &&
        ui1_hlt_idx != pt_opt_list->ui1_main_lb_hlt_idx)
    {
        pt_opt_list->ui1_main_lb_hlt_idx = ui1_hlt_idx;
        pt_opt_list->ui1_sub_lb_hlt_idx = OPTL_LB_SUB_DFLT_HLT_IDX;
        b_idx_change = TRUE;
    }
    else if (OPTL_SUB_LIST == pt_opt_list->e_hlt_list &&
        ui1_hlt_idx != pt_opt_list->ui1_sub_lb_hlt_idx)
    {
        pt_opt_list->ui1_sub_lb_hlt_idx= ui1_hlt_idx;
        b_idx_change = TRUE;
    }

    if (b_idx_change)
    {

        if ( pt_opt_list->pf_fct != NULL)
        {
            pt_opt_list->pf_fct(pt_opt_list->pv_tag,
                  OPTL_MSG_ITEM_HIGHLIGHT ,
                  (VOID*)(UINT32)pt_opt_list->ui1_main_lb_hlt_idx,
                  (VOID*)(UINT32)pt_opt_list->ui1_sub_lb_hlt_idx);
        }
    }
    return (OPTLR_OK);
}

static INT32 _optl_lst_item_select(OPTL_CONTROL_T*   pt_opt_list)
{
    INT32  i4_ret = -1;

    if (OPTL_MAIN_LIST == pt_opt_list->e_hlt_list)
    {
        UINT8    ui1_hlt_idx = 0;
        ui1_hlt_idx = pt_opt_list->ui1_main_lb_hlt_idx;

        if(ui1_hlt_idx >= OPTL_LB_MAIN_ITEM_DFLT_NUM)
        {
            return OPTLR_FAIL;
        }
        if (pt_opt_list->t_main_item[ui1_hlt_idx].e_type == OPTL_ITEM_TYPE_ACTION )
        {
            if (pt_opt_list->t_main_item[ui1_hlt_idx].u.t_action.pf_fct != NULL)
            {
                pt_opt_list->t_main_item[ui1_hlt_idx].u.t_action.pf_fct(
                            pt_opt_list->t_main_item[ui1_hlt_idx].u.t_action.pv_tag);
            }
        }
        else
        {
            _optl_check_to_enter_sub_menu (pt_opt_list);
        }
    }
    else
    {
        UINT8   ui1_main_hlt_idx = pt_opt_list->ui1_main_lb_hlt_idx;
        UINT8   ui1_sub_hlt_idx  = pt_opt_list->ui1_sub_lb_hlt_idx;

        if((ui1_sub_hlt_idx >= OPTL_LB_SUB_ITEM_DFLT_NUM) ||
           (ui1_main_hlt_idx >= OPTL_LB_MAIN_ITEM_DFLT_NUM))
        {
            return OPTLR_FAIL;
        }

        if (pt_opt_list->t_main_item[ui1_main_hlt_idx].u.t_subopt_list.pt_sub_item[ui1_sub_hlt_idx].pf_fct != NULL)
        {
            pt_opt_list->t_main_item[ui1_main_hlt_idx].u.t_subopt_list.pt_sub_item[ui1_sub_hlt_idx].pf_fct(
                    pt_opt_list->t_main_item[ui1_main_hlt_idx].u.t_subopt_list.pt_sub_item[ui1_sub_hlt_idx].pv_tag);
        }

        i4_ret = _optl_close_sub_menu(pt_opt_list);
        OPTL_CHK_FAIL(i4_ret);
    }
    return OPTLR_OK;
}

static INT32 _optl_lst_proc_fct(HANDLE_T h_widget,
                                UINT32   ui4_msg,
                                VOID*    pv_param1,
                                VOID*    pv_param2)
{
    INT32              i4_ret;
    HANDLE_T           h_optl_frm = NULL_HANDLE;
    OPTL_CONTROL_T*    pt_opt_list = NULL;

    switch(ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32             ui4_key_code = 0;
            BOOL               b_process = TRUE;

            i4_ret = c_wgl_get_parent(h_widget, &h_optl_frm);
            OPTL_CHK_FAIL(i4_ret);
            ui4_key_code = (UINT32) pv_param1;

            i4_ret = _optl_get_attach_data(h_optl_frm, &pt_opt_list);
            OPTL_CHK_FAIL(i4_ret);

            /* start the timer if necessary */
            i4_ret = _optl_start_timer(pt_opt_list);
            OPTL_CHK_FAIL(i4_ret);

            if (pt_opt_list->pf_fct != NULL)
            {
                pt_opt_list->pf_fct(pt_opt_list->pv_tag,
                                    OPTL_MSG_CHECK_KEY_INPUT,
                                    (VOID*)ui4_key_code,
                                    (VOID*)&b_process);
                if (b_process == FALSE)
                {
                    /* The key is ingored by optl widget. */
                    break;
                }

                pt_opt_list->pf_fct(pt_opt_list->pv_tag,
                          OPTL_MSG_KEY_INPUT ,
                          (VOID*)ui4_key_code,
                          (VOID*)0);
            }

            if (h_widget == pt_opt_list->h_list_box)
            {
                switch (ui4_key_code)
                {
                    case BTN_CURSOR_DOWN:
                    case BTN_CURSOR_UP:
                        i4_ret = _optl_lst_lb_hlt_chg(h_widget,
                                                      pt_opt_list,
                                                      ui4_key_code,
                                                      pv_param2);
                        return (i4_ret);
                    case BTN_RETURN:
                    {
                        i4_ret = c_wgl_set_focus(pt_opt_list->h_back_btn, WGL_SYNC_AUTO_REPAINT);
                        OPTL_CHK_FAIL(i4_ret);
                    }
                        break;

                    case BTN_EXIT:
                    case BTN_RED:
                    {
                        if (pt_opt_list->pf_fct != NULL)
                        {
                            pt_opt_list->pf_fct(pt_opt_list->pv_tag,
                                                OPTL_MSG_CANCELLED ,
                                                NULL,
                                                NULL);
                        }
                    }
                        break;

                    case BTN_SELECT:
                        i4_ret = _optl_lst_item_select(pt_opt_list);
                        OPTL_CHK_FAIL(i4_ret);
                        break;

                    default:
                        break;
                }
            }
            else
            {
                switch (ui4_key_code)
                {
                    case BTN_SELECT:
                    case BTN_RETURN:
                        if (OPTL_MAIN_LIST == pt_opt_list->e_hlt_list)
                        {
                            if (pt_opt_list->pf_fct != NULL)
                            {
                                pt_opt_list->pf_fct(pt_opt_list->pv_tag,
                                                    OPTL_MSG_CANCELLED ,
                                                    NULL,
                                                    NULL);
                            }
                        }
                        else
                        {
                            i4_ret = _optl_close_sub_menu(pt_opt_list);
                            OPTL_CHK_FAIL(i4_ret);
                        }
                        break;

                    default:
                        break;
                }
            }
        }
            break;

        default:
            break;
    }

    i4_ret = c_wgl_default_msg_proc(
                                    h_widget,
                                    ui4_msg,
                                    pv_param1,
                                    pv_param2
                                    );
    return i4_ret;

}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_create(
                    OPTL_INIT_T*        pt_optl_init,        /* In  */
                    HANDLE_T*           ph_optl_handle)      /* Out */
{
    INT32               i4_ret;
    INT32               i4_result;
    OPTL_CONTROL_T*     pt_opt_list;
    WGL_KEY_LINK_T      at_link[1];

    pt_opt_list = (OPTL_CONTROL_T *) c_mem_alloc(sizeof(OPTL_CONTROL_T));

    if(pt_opt_list == NULL)
    {
        return OPTLR_OUT_OF_MEMORY;
    }
    _optl_res_init();

    c_memset(pt_opt_list, 0 , sizeof(OPTL_CONTROL_T));

    /* Set the style mask */
    pt_opt_list->ui4_style_mask = pt_optl_init->ui4_style_mask;

    /* Create content frame widget */
    do
    {
        i4_result = app_util_option_list_option_list_create_ui_mi(pt_optl_init->h_parent, &pt_opt_list->h_layout_inst);
        if (i4_result != WDKR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        pt_opt_list->h_frm_optl = app_util_option_list_option_list_get_wgt_hdl_mi(WID_APP_UTIL_OPTION_LIST_OPTION_LIST_FRM_OPTION_FRM, pt_opt_list->h_layout_inst);
        pt_opt_list->h_list_box = app_util_option_list_option_list_get_wgt_hdl_mi(WID_APP_UTIL_OPTION_LIST_OPTION_LIST_LB_OPTION_LIST, pt_opt_list->h_layout_inst);
        pt_opt_list->h_back_btn = app_util_option_list_option_list_get_wgt_hdl_mi(WID_APP_UTIL_OPTION_LIST_OPTION_LIST_BTN_BACK, pt_opt_list->h_layout_inst);

        c_wgl_set_widget_proc(pt_opt_list->h_list_box, _optl_lst_proc_fct);
        c_wgl_set_widget_proc(pt_opt_list->h_back_btn, _optl_lst_proc_fct);
        i4_result = _optl_list_key_map(pt_opt_list->h_list_box);
        if(i4_result != OPTLR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* Create auto hide timer */
        i4_result = _optl_create_timer(pt_opt_list);
        if(i4_result != OPTLR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* Save the initial information */
        pt_opt_list->h_parent           = pt_optl_init->h_parent;
        pt_opt_list->t_gui_rc           = pt_optl_init->t_gui_rc;
        pt_opt_list->pf_fct             = pt_optl_init->pf_fct;
        pt_opt_list->pf_get_key_src_fct = pt_optl_init->pf_get_key_src_fct;
        pt_opt_list->pv_tag             = pt_optl_init->pv_tag;
        pt_opt_list->ui4_sleep_time     = pt_optl_init->ui4_sleep_time;
        pt_opt_list->ui4_custom_flag    = pt_optl_init->ui4_custom_flag;

        /* Hide the frame at initial time */
        c_wgl_set_visibility(pt_opt_list->h_frm_optl, WGL_SW_HIDE);

        /* Set navigation*/
        at_link[0].h_widget = pt_opt_list->h_list_box;
        at_link[0].ui4_key  = BTN_CURSOR_DOWN;
        c_wgl_set_navigation(pt_opt_list->h_back_btn, 1, at_link);

        /* Return the option list handle */
        *ph_optl_handle = pt_opt_list->h_frm_optl;

        /* Set main and sub lists index */
        pt_opt_list->ui1_main_lb_hlt_idx = OPTL_LB_MAIN_DFLT_HLT_IDX;
        pt_opt_list->ui1_sub_lb_hlt_idx = OPTL_LB_SUB_DFLT_HLT_IDX;

        /* Done */
        _optl_set_attach_data(pt_opt_list->h_frm_optl,
                              pt_opt_list);
        i4_ret = OPTLR_OK;

    } while(0);

    if(i4_ret != OPTLR_OK)
    {
        i4_ret = _optl_destroy(pt_opt_list->h_frm_optl);
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_destroy(
                    HANDLE_T            h_optl_handle)

{
    INT32   i4_ret;

    _optl_res_deinit();

    i4_ret = _optl_destroy(h_optl_handle);
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_set_float_widget(
                    HANDLE_T            h_optl_handle,
                    BOOL                b_float)
{
    INT32               i4_ret;
    OPTL_CONTROL_T*     pt_opt_list;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /* Float these widgets if necessary */
    if (b_float)
    {
        /* float widget */
        c_wgl_float(pt_opt_list->h_frm_optl, TRUE, FALSE);
        c_wgl_float(pt_opt_list->h_list_box, TRUE, FALSE);
        c_wgl_float(pt_opt_list->h_back_btn, TRUE, FALSE);
    }
    else
    {
        /* disable float widget */
        c_wgl_float(pt_opt_list->h_frm_optl, FALSE, FALSE);
        c_wgl_float(pt_opt_list->h_list_box, FALSE, FALSE);
        c_wgl_float(pt_opt_list->h_back_btn, FALSE, FALSE);
    }
    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_set_option_items(
                    HANDLE_T            h_optl_handle,
                    OPTL_ITEM_DEF_T*    pt_optl_item_def)
{
    INT32               i4_ret;
    UINT8               ui1_idx;
    UINT8               ui1_sub_idx;
    OPTL_CONTROL_T*     pt_opt_list;
    OPTL_SUBITEM_T*     pt_sub_item;
    UTF16_T*            pw2s_str;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /*Release the memory allcated for subitems*/
    for (ui1_idx = 0; ui1_idx < OPTL_LB_MAIN_ITEM_DFLT_NUM; ui1_idx++)
    {
        if (pt_opt_list->t_main_item[ui1_idx].e_type == OPTL_ITEM_TYPE_SUBLIST)
        {
            for (ui1_sub_idx = 0; ui1_sub_idx < (UINT8)(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.ui2_num_of_sub_items); ui1_sub_idx++)
            {
                if (pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text != NULL)
                {
                    c_mem_free(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text);
                    pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text = NULL;
                }
            }

            if (pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item != NULL)
            {
                c_mem_free(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item);
                pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item = NULL;
            }

        }

        /* also reset to default type */
        pt_opt_list->t_main_item[ui1_idx].e_type = OPTL_ITEM_TYPE_ACTION;
    }

    /* Reset the index to the default value */
    pt_opt_list->ui1_main_lb_hlt_idx = OPTL_LB_MAIN_DFLT_HLT_IDX;
    pt_opt_list->ui1_sub_lb_hlt_idx = OPTL_LB_MAIN_DFLT_HLT_IDX;

    /* 2. Reset the highlight list to the default value */
    pt_opt_list->e_hlt_list = OPTL_MAIN_LIST;

    pt_opt_list->ui1_main_lb_item_num = (UINT8)(pt_optl_item_def->ui2_num_of_opt_items);

    /*klocwork warning*/
    if(pt_optl_item_def->ui2_num_of_opt_items >= OPTL_LB_MAIN_ITEM_DFLT_NUM)
    {
        return OPTLR_FAIL;
    }

    pt_opt_list->pw2s_title = pt_optl_item_def->pw2s_title;
    c_memcpy(&pt_opt_list->t_main_item, pt_optl_item_def->pt_opt_item,
              sizeof(OPTL_ITEM_T)*pt_optl_item_def->ui2_num_of_opt_items);

    for (ui1_idx = 0; (ui1_idx < OPTL_LB_MAIN_ITEM_DFLT_NUM)&&(ui1_idx < pt_opt_list->ui1_main_lb_item_num); ui1_idx++)
    {
        /* Save item information and text for sublist  */
        if (pt_opt_list->t_main_item[ui1_idx].e_type == OPTL_ITEM_TYPE_SUBLIST)
        {
            pt_sub_item = pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item;
            pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item
                                = (OPTL_SUBITEM_T*)c_mem_alloc(sizeof(OPTL_SUBITEM_T)
                                   * pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.ui2_num_of_sub_items);

            if (pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item != NULL)
            {
                c_memcpy(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item,
                         pt_sub_item,
                         sizeof(OPTL_SUBITEM_T)* pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.ui2_num_of_sub_items);
            }
            else
            {
                return OPTLR_OUT_OF_MEMORY;
            }

            pt_opt_list->ui1_sub_lb_item_num = (UINT8)(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.ui2_num_of_sub_items);

            for (ui1_sub_idx = 0; ui1_sub_idx < pt_opt_list->ui1_sub_lb_item_num; ui1_sub_idx++)
            {
                pw2s_str = pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text;
                pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text
                                                                    =  (UTF16_T*)c_mem_alloc(sizeof(UTF16_T) * (OPTL_LB_SUB_TXT_MAX+1));
                if (pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text != NULL)
                {
                    c_memset(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text ,
                         0, sizeof(UTF16_T) * OPTL_LB_SUB_TXT_MAX);

                    c_uc_w2s_strncpy(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text,
                            pw2s_str,
                            OPTL_LB_SUB_TXT_MAX);

                }
                else
                {
                    return OPTLR_OUT_OF_MEMORY;
                }
            }
        }
    }

    /* Set text for main list */
    _optl_set_main_lst_text(pt_opt_list);

    /* disable elem */
    for (ui1_idx = 0; (ui1_idx < OPTL_LB_MAIN_ITEM_DFLT_NUM)&&(ui1_idx < pt_opt_list->ui1_main_lb_item_num); ui1_idx++)
    {
        if(pt_opt_list->t_main_item[ui1_idx].b_is_disable == TRUE)
        {
            i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                                  WGL_CMD_LB_DISABLE_ELEM,
                                  WGL_PACK(ui1_idx),
                                  NULL);

        }
        else
        {
            i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                                  WGL_CMD_LB_ENABLE_ELEM,
                                  WGL_PACK(ui1_idx),
                                  NULL);

        }

    }

    /* reset the item highlight */
    for (ui1_idx = 0; (ui1_idx < OPTL_LB_MAIN_ITEM_DFLT_NUM)&&(ui1_idx < pt_opt_list->ui1_main_lb_item_num); ui1_idx++)
    {
        if(pt_opt_list->t_main_item[ui1_idx].b_is_disable == FALSE)
        {
            pt_opt_list->ui1_main_lb_hlt_idx = ui1_idx;
            break;
        }
    }

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_set_gui_rc(
                    HANDLE_T          h_optl_handle,
                    OPTL_GUI_RC_T*    pt_gui_rc)
{
    INT32           i4_ret;
    OPTL_CONTROL_T*  pt_optl_list;

    /* Get Option List structure */

    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_optl_list);
    OPTL_CHK_FAIL(i4_ret);

    pt_optl_list->t_gui_rc.i4_left = pt_gui_rc->i4_left ;
    pt_optl_list->t_gui_rc.i4_top = pt_gui_rc->i4_top ;

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_set_next_hlt_index(
                        HANDLE_T        h_optl_handle,
                        BOOL          b_is_main_next_idx,
                        BOOL          b_is_sub_next_idx,
                        BOOL          b_is_repaint)
{
    INT32           i4_ret;
    OPTL_CONTROL_T*  pt_opt_list;
    UINT8            ui1_hlt_idx = 0;
    UINT16              ui2_hlt_idx = 0;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /* If highlight index of main list is changed, hide the sub list */
    if(TRUE == b_is_main_next_idx )
    {
        /* 3. Set elements in the main list */
        i4_ret = c_wgl_do_cmd( pt_opt_list->h_list_box,
                               WGL_CMD_LB_HLT_NEXT_ELEM,
                               WGL_PACK(b_is_repaint),
                               NULL);
        OPTL_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_hlt_idx),
                              NULL);
        OPTL_CHK_FAIL(i4_ret);
        ui1_hlt_idx = (UINT8)ui2_hlt_idx;

        pt_opt_list->ui1_main_lb_hlt_idx = ui1_hlt_idx;
        pt_opt_list->ui1_sub_lb_hlt_idx  = OPTL_LB_SUB_DFLT_HLT_IDX;
    }
    return OPTLR_OK;

}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_set_hlt_index(
                        HANDLE_T        h_optl_handle,
                        UINT16          ui2_main_hlt_index,
                        UINT16          ui2_sub_hlt_index)
{
    INT32           i4_ret;
    OPTL_CONTROL_T*  pt_opt_list;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /* If highlight index of main list is changed, hide the sub list */

    if (ui2_main_hlt_index != pt_opt_list->ui1_main_lb_hlt_idx)
    {
        pt_opt_list->ui1_main_lb_hlt_idx = (UINT8)ui2_main_hlt_index;
        pt_opt_list->ui1_sub_lb_hlt_idx  = OPTL_LB_SUB_DFLT_HLT_IDX;
    } else
    {
        if (pt_opt_list->e_hlt_list == OPTL_SUB_LIST)
        {
            pt_opt_list->ui1_sub_lb_hlt_idx = (UINT8)ui2_sub_hlt_index;
        }
    }

    return OPTLR_OK;

}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_get_hlt_index(
                        HANDLE_T        h_optl_handle,
                        UINT16*         pui2_main_hlt_index ,
                        UINT16*         pui2_sub_hlt_index)
{
    INT32           i4_ret;
    OPTL_CONTROL_T*  pt_opt_list;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    if (pt_opt_list->e_hlt_list == OPTL_SUB_LIST)
    {
       *pui2_main_hlt_index = pt_opt_list->ui1_main_lb_hlt_idx;
       *pui2_sub_hlt_index = pt_opt_list->ui1_sub_lb_hlt_idx;
    }
    else
    {
       *pui2_main_hlt_index = pt_opt_list->ui1_main_lb_hlt_idx;
       *pui2_sub_hlt_index = OPTL_INVALID_INDEX;
    }

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_repaint(
                    HANDLE_T        h_optl_handle)
{
    INT32           i4_ret;
    OPTL_CONTROL_T*  pt_opt_list;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /* 1. Set the visibility for frame of main list and sub list */
    c_wgl_set_visibility(pt_opt_list->h_frm_optl, WGL_SW_RECURSIVE);

    /* 3. Set elements in the main list */
    i4_ret = c_wgl_do_cmd( pt_opt_list->h_list_box,
                           WGL_CMD_LB_HLT_ELEM,
                           WGL_PACK(pt_opt_list->ui1_main_lb_hlt_idx),
                           NULL);
    OPTL_CHK_FAIL(i4_ret);

    /* 4. Ensure the highlight element could be visible */
    i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                          WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                          NULL,
                          NULL);
    OPTL_CHK_FAIL(i4_ret);

    pt_opt_list->e_hlt_list = OPTL_MAIN_LIST;
    i4_ret = c_wgl_set_focus(pt_opt_list->h_list_box, FALSE);
    OPTL_CHK_FAIL(i4_ret);

    /* 6. Set visibility for content indicator */

    /* 7. Set to topmost */
    i4_ret = c_wgl_insert (h_optl_handle,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    OPTL_CHK_FAIL(i4_ret);

    /* 8. Repaint the canvas */
    i4_ret = c_wgl_repaint(pt_opt_list->h_frm_optl, NULL, TRUE);
    OPTL_CHK_FAIL(i4_ret);

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_set_visibility(
                    HANDLE_T            h_optl_handle,
                    BOOL                b_visible)
{
    INT32           i4_ret;
    OPTL_CONTROL_T*  pt_opt_list;
    UINT8            ui1_hlt_idx;
    UINT16              ui2_hlt_idx = 0;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);


    if (b_visible)
    {
        c_wgl_set_visibility(h_optl_handle, WGL_SW_NORMAL);
    }
    else
    {
        c_wgl_set_visibility(h_optl_handle, WGL_SW_HIDE);

        /* On purpose to stop the timer. because it is not visible. */
        _optl_stop_timer(pt_opt_list);
    }

    i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(&ui2_hlt_idx),
                          NULL);
    OPTL_CHK_FAIL(i4_ret);
    ui1_hlt_idx = (UINT8)ui2_hlt_idx;

    pt_opt_list->ui1_main_lb_hlt_idx = ui1_hlt_idx;

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_set_focus(
                    HANDLE_T            h_optl_handle)
{
    INT32           i4_ret;
    OPTL_CONTROL_T*  pt_opt_list;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /* 1. Set focus */
    c_wgl_set_focus(pt_opt_list->h_list_box, FALSE);

    /* 2. start the timer if necessary */
    i4_ret = _optl_start_timer(pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_show(
                    HANDLE_T            h_optl_handle)
{
    INT32            i4_ret;
    OPTL_CONTROL_T*  pt_opt_list;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /* 1. Set the visibility for frame of main list and sub list */
    c_wgl_set_visibility(pt_opt_list->h_frm_optl, WGL_SW_RECURSIVE);

    /* 3. Set focus on the main list box */
    pt_opt_list->e_hlt_list = OPTL_MAIN_LIST;
    i4_ret = c_wgl_set_focus(pt_opt_list->h_list_box, FALSE);
    OPTL_CHK_FAIL(i4_ret);

    /* 4. Set hightlight of the main list*/
    i4_ret = c_wgl_do_cmd( pt_opt_list->h_list_box,
                           WGL_CMD_LB_HLT_ELEM,
                           WGL_PACK(pt_opt_list->ui1_main_lb_hlt_idx),
                           NULL);
    OPTL_CHK_FAIL(i4_ret);

    /* 5. Ensure the highlight element could be visible */
    i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                          WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                          NULL,
                          NULL);
    OPTL_CHK_FAIL(i4_ret);

    /* 6. Set visibility for content indicator */

    /* 7. Set to topmost */
    i4_ret = c_wgl_insert (h_optl_handle,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    OPTL_CHK_FAIL(i4_ret);


    /* 8. Repaint the frame */
    i4_ret = c_wgl_repaint(h_optl_handle, NULL, TRUE);
    OPTL_CHK_FAIL(i4_ret);

    /* 9. start the timer if necessary */
    i4_ret = _optl_start_timer(pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    pt_opt_list->b_is_show = TRUE;

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_hide(
                    HANDLE_T            h_optl_handle)
{
    INT32           i4_ret;
    OPTL_CONTROL_T*  pt_opt_list;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /* 0. Stop the timer */
    i4_ret = _optl_stop_timer(pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /* 1. Reset the highlight index to the default value */
    pt_opt_list->ui1_main_lb_hlt_idx = OPTL_LB_MAIN_DFLT_HLT_IDX;
    pt_opt_list->ui1_sub_lb_hlt_idx = OPTL_LB_SUB_DFLT_HLT_IDX;

    /* 2. Reset the highlight list to the default value */
    pt_opt_list->e_hlt_list = OPTL_MAIN_LIST;

    /* 3. Set the visibility for frame of main list and sub list */
    c_wgl_set_visibility(pt_opt_list->h_frm_optl, WGL_SW_HIDE_RECURSIVE);

    /* 4. Repaint */
    i4_ret = c_wgl_repaint(h_optl_handle, NULL, TRUE);
    OPTL_CHK_FAIL(i4_ret);

    pt_opt_list->b_is_show = FALSE;

    return OPTLR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_enable_disable_item(HANDLE_T            h_optl_handle,
                                     UINT8               ui1_item_idx,
                                     BOOL                 b_is_disable,
                                     BOOL                 b_is_repaint)
{
    INT32           i4_ret;
    OPTL_CONTROL_T*  pt_opt_list;
    UINT8            ui1_hlt_idx = 0;
    UINT16           ui2_hlt_idx = 0;

    if((ui1_item_idx >= OPTL_LB_MAIN_ITEM_DFLT_NUM)||
       (h_optl_handle == NULL_HANDLE))
    {
        return OPTLR_INV_ARG;
    }

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    if(ui1_item_idx >= pt_opt_list->ui1_main_lb_item_num)
    {
        return OPTLR_INV_ARG;
    }


    /* disable  elem */
    if(b_is_disable == TRUE)
    {

            i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                                  WGL_CMD_LB_DISABLE_ELEM,
                                  WGL_PACK(ui1_item_idx),
                                  NULL);
            OPTL_CHK_FAIL(i4_ret);
            pt_opt_list->t_main_item[ui1_item_idx].b_is_disable = TRUE;

            if(ui1_item_idx == pt_opt_list->ui1_main_lb_hlt_idx)
            {
                i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_hlt_idx),
                                      NULL);
                OPTL_CHK_FAIL(i4_ret);

                ui1_hlt_idx = (UINT8)ui2_hlt_idx;

                pt_opt_list->ui1_main_lb_hlt_idx = ui1_hlt_idx;
            }
    }
    else
    {

            i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                                  WGL_CMD_LB_ENABLE_ELEM,
                                  WGL_PACK(ui1_item_idx),
                                  NULL);
            OPTL_CHK_FAIL(i4_ret);

            pt_opt_list->t_main_item[ui1_item_idx].b_is_disable = FALSE;
    }

    if(b_is_repaint == TRUE)
    {
        /*  Repaint  elems */
        i4_ret = c_wgl_do_cmd (pt_opt_list->h_list_box,
                              WGL_CMD_LB_REPAINT_ELEMS,
                              WGL_PACK (ui1_item_idx),
                              WGL_PACK (ui1_item_idx));
        OPTL_CHK_FAIL(i4_ret);

    }

    return OPTLR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_optl_set_main_list_text(HANDLE_T            h_optl_handle,
                                OPTL_ITEM_DEF_T*    pt_optl_item_def)
{
    INT32               i4_ret;
    UINT8               ui1_idx;
    UINT8               ui1_sub_idx;
    OPTL_CONTROL_T*     pt_opt_list;
    OPTL_SUBITEM_T*     pt_sub_item;
    UTF16_T*            pw2s_str;

    /* Get option list structure */
    i4_ret = _optl_get_attach_data(h_optl_handle,
                                  &pt_opt_list);
    OPTL_CHK_FAIL(i4_ret);

    /*Release the memory allcated for subitems*/
    for (ui1_idx = 0; ui1_idx < OPTL_LB_MAIN_ITEM_DFLT_NUM; ui1_idx++)
    {
        if (pt_opt_list->t_main_item[ui1_idx].e_type == OPTL_ITEM_TYPE_SUBLIST)
        {
            for (ui1_sub_idx = 0; ui1_sub_idx < (UINT8)(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.ui2_num_of_sub_items); ui1_sub_idx++)
            {
                if (pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text != NULL)
                {
                    c_mem_free(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text);
                    pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text = NULL;
                }
            }

            if (pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item != NULL)
            {
                c_mem_free(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item);
                pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item = NULL;
            }

        }

        /* also reset to default type */
        pt_opt_list->t_main_item[ui1_idx].e_type = OPTL_ITEM_TYPE_ACTION;
    }

    /* 2. Reset the highlight list to the default value */
    pt_opt_list->e_hlt_list = OPTL_MAIN_LIST;

    pt_opt_list->ui1_main_lb_item_num = (UINT8)(pt_optl_item_def->ui2_num_of_opt_items);

    /*klocwork warning*/
    if(pt_optl_item_def->ui2_num_of_opt_items >= OPTL_LB_MAIN_ITEM_DFLT_NUM)
    {
        return OPTLR_FAIL;
    }

    pt_opt_list->pw2s_title = pt_optl_item_def->pw2s_title;
    c_memcpy(&pt_opt_list->t_main_item, pt_optl_item_def->pt_opt_item,
              sizeof(OPTL_ITEM_T)*pt_optl_item_def->ui2_num_of_opt_items);

    for (ui1_idx = 0; (ui1_idx < OPTL_LB_MAIN_ITEM_DFLT_NUM)&&(ui1_idx < pt_opt_list->ui1_main_lb_item_num); ui1_idx++)
    {
        /* Save item information and text for sublist  */
        if (pt_opt_list->t_main_item[ui1_idx].e_type == OPTL_ITEM_TYPE_SUBLIST)
        {
            pt_sub_item = pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item;
            pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item
                                = (OPTL_SUBITEM_T*)c_mem_alloc(sizeof(OPTL_SUBITEM_T)
                                   * pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.ui2_num_of_sub_items);

            if (pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item != NULL)
            {
                c_memcpy(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item,
                         pt_sub_item,
                         sizeof(OPTL_SUBITEM_T)* pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.ui2_num_of_sub_items);
            }
            else
            {
                return OPTLR_OUT_OF_MEMORY;
            }

            pt_opt_list->ui1_sub_lb_item_num = (UINT8)(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.ui2_num_of_sub_items);

            for (ui1_sub_idx = 0; ui1_sub_idx < pt_opt_list->ui1_sub_lb_item_num; ui1_sub_idx++)
            {
                pw2s_str = pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text;
                pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text
                                                                    =  (UTF16_T*)c_mem_alloc(sizeof(UTF16_T) * (OPTL_LB_SUB_TXT_MAX+1));
                if (pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text != NULL)
                {
                    c_memset(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text ,
                         0, sizeof(UTF16_T) * OPTL_LB_SUB_TXT_MAX);

                    c_uc_w2s_strncpy(pt_opt_list->t_main_item[ui1_idx].u.t_subopt_list.pt_sub_item[ui1_sub_idx].pw2s_text,
                            pw2s_str,
                            OPTL_LB_SUB_TXT_MAX);

                }
                else
                {
                    return OPTLR_OUT_OF_MEMORY;
                }
            }
        }
    }

    /* Set text for main list */
    _optl_set_main_lst_text(pt_opt_list);

    /* disable elem */
    for (ui1_idx = 0; (ui1_idx < OPTL_LB_MAIN_ITEM_DFLT_NUM)&&(ui1_idx < pt_opt_list->ui1_main_lb_item_num); ui1_idx++)
    {
        if(pt_opt_list->t_main_item[ui1_idx].b_is_disable == TRUE)
        {
            i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                                  WGL_CMD_LB_DISABLE_ELEM,
                                  WGL_PACK(ui1_idx),
                                  NULL);

        }
        else
        {
            i4_ret = c_wgl_do_cmd(pt_opt_list->h_list_box,
                                  WGL_CMD_LB_ENABLE_ELEM,
                                  WGL_PACK(ui1_idx),
                                  NULL);

        }

    }

    return OPTLR_OK;
}


