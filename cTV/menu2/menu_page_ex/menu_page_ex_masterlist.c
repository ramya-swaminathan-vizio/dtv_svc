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
 * $RCSfile: menu_page_auto_color.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor:min.li $
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
#include "c_fe.h"

#include "u_sm_video_hdlr.h"
#include "c_svctx.h"

#include "app_util/a_ui.h"
#include "app_util/a_cfg.h"
#include "app_util/a_isl.h"
#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_page.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_dbg.h"

#ifdef COMMON_EX_MASTERLIST_ENABLE

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define _FRM_X                      (FRAME_X)
#define _FRM_Y                      (FRAME_Y)
#define _FRM_W                      (470)
#define _FRM_H                      (FRAME_H)

#define _QUK_OP_X                   (0*GRID_W)
#define _QUK_OP_Y                   (0*GRID_H)
#define _QUK_OP_W                   (_FRM_W/4+34)

#define _QUK_OP_H                   (3*GRID_H)

#define _CH_LST_STL_SCROLL          0
#define _CH_LST_BACK_ON_LEFT        0

#define _CH_LST_X                   (_QUK_OP_W + 20)
#define _CH_LST_Y                   (0 * GRID_H)
#define _CH_LST_W                   (_FRM_W - CONTENT_X - _CH_LST_X - 20)
#define _CH_LST_H                   (CONTENT_H - _CH_LST_Y)

#define _CH_LST_COL0_W              (55)
#define _CH_LST_COL1_W              (20)
#define _CH_LST_COL2_W              (_CH_LST_W - _CH_LST_COL0_W - _CH_LST_COL1_W - _CH_LST_COL3_W \
                                     - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R)
#define _CH_LST_COL3_W              (35)
#define _CH_LST_ELEM_H              GRID_H
#define _CH_LST_COL0_ALIGN          WGL_AS_LEFT_CENTER
#define _CH_LST_COL1_ALIGN          WGL_AS_LEFT_CENTER
#define _CH_LST_COL2_ALIGN          WGL_AS_LEFT_CENTER
#define _CH_LST_COL3_ALIGN          WGL_AS_RIGHT_CENTER

#define _MAX_CH_NAME_LEN            (48)
#define _MAX_CH_TYPE_LEN            (16)
#define _MAX_CH_NUM_LEN             (8)
#define _MAX_QUK_OP_TEXT_LEN        (32)

typedef enum {
   _QUK_OP_ITEM_MARK_ALL = 0 ,
   _QUK_OP_ITEM_UNMARK_ALL ,
   _QUK_OP_ITEM_DIG_ONLY ,
   _QUK_OP_ITEM_LAST_ENTRY

}  _QUK_OP_ITEM_T ;

typedef enum {
    HELP_LST_UP_ONLY = 0,
    HELP_LST_DOWN_ONLY,
    HELP_LST_UP_DOWN,
    HELP_LST_UNKNOWN

} HELP_LST_STATE;

typedef enum {
    _HELP_TIP_TYPE_QUK_OP = 0 ,
    _HELP_TIP_TYPE_LB_CH ,
    _HELP_TIP_TYPE_HOMEBAR ,
    _HELP_TIP_TYPE_BACKBAR ,
    _HELP_TIP_TYPE_LAST_ENTRY

} _HELP_TIP_TYPE_T ;

typedef struct
{
    UINT32                          ui4_page_id;
    MENU_COMMON_CHANNEL_LIST_INIT_T t_masterlist_init;
    UINT16                          ui2_ch_num;
    UINT16*                         pui2_idx_recid_map;
    HANDLE_T                        h_crnt_svl ;
    HANDLE_T                        h_cnt_frm ;
    HANDLE_T                        h_lb_ch;
    HANDLE_T                        h_quk_op;          /* quick operation list */
    BOOL                            b_is_refreshing;

} _MASTERLIST_T ;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_page_ex_masterlist;
_MASTERLIST_T        t_g_masterlist ;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _on_page_show(
    UINT32                      ui4_page_id
    ) ;

static INT32 _on_page_hide(
    UINT32                      ui4_page_id
    ) ;

static INT32 _on_page_get_focus(
    UINT32                      ui4_page_id,
    MENU_PAGE_HINT_T*           pt_hint
    ) ;

static INT32 _on_page_lose_focus(
    UINT32                      ui4_page_id
    ) ;

static INT32 _refresh_ch_lst (VOID);

static INT32 _hlt_curent_ch (VOID);

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
#ifdef ________________________________________________________JUST_FOR_DIVISION
#endif

/*----------------------------------------------------------------------------
 * Name: _ch_num_to_str
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
static VOID _ch_num_to_str (
    UINT16                      ui2_major,
    UINT16                      ui2_minor,
    BOOL                        b_one_part_ch,
    UTF16_T*                    w2s_str
    )
{
    CHAR                        s_str[64];

    c_memset(s_str, 0, sizeof(s_str));

    if (b_one_part_ch)
    {
        /* One part channel number */
        c_sprintf(s_str, "%d",  ui2_major);
    }
    else
    {   /* Two part channel number */
        c_sprintf(s_str,
                  CHANNEL_NUMBER_FORMAT,   /* Defined in a_common.h */
                  ui2_major,
                  ui2_minor);
    }

    c_uc_ps_to_w2s(s_str ,w2s_str, _MAX_CH_NUM_LEN);
}

/*----------------------------------------------------------------------------
 * Name: _add_ch
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
static INT32 _add_ch (
    SVL_REC_T*                  pt_svl_rec
    )
{
    INT32                       i4_ret;
    UINT32                      ui4_channel_id ;
    UINT16                      ui4_rec_id ;
    UINT32                      ui4_nw_mask ;
    UINT32                      ui4_sel_mask ;
    UTF16_T                     w2s_digits[_MAX_CH_NUM_LEN+1];
    UTF16_T                     w2s_name[_MAX_CH_NAME_LEN+1];
    UTF16_T*                    w2s_type;
    BOOL                        b_one_part_ch ;
    UINT16                      ui2_major ;
    UINT16                      ui2_minor ;
    INT32                       i4_len ;
    UINT16                      ui2_idx ;
    WGL_LB_ITEM_T               at_items[4] ;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit ;
    _MASTERLIST_T*              pt_this = &t_g_masterlist ;

    if (!pt_svl_rec)
    {
        return MENUR_INV_ARG ;
    }

    ui4_channel_id = pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id;
    ui4_rec_id     = pt_svl_rec->ui2_svl_rec_id;
    ui4_nw_mask    = pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask;
    ui4_sel_mask   = pt_this->t_masterlist_init.ui4_sel_mask;
    b_one_part_ch  = SB_ATSC_IS_ONE_PART_CHANNEL_ID(ui4_channel_id);
    ui2_major      = SB_ATSC_GET_MAJOR_CHANNEL_NUM(ui4_channel_id);
    ui2_minor      = SB_ATSC_GET_MINOR_CHANNEL_NUM(ui4_channel_id);

    /* Get the channel number */
    c_memset(w2s_digits, 0, sizeof(w2s_digits));
    _ch_num_to_str(ui2_major, ui2_minor, b_one_part_ch, w2s_digits);

    /* Get the channel name */
    c_memset(w2s_name, 0, sizeof(w2s_name));
    i4_len = (INT32)c_strlen(pt_svl_rec->uheader.t_rec_hdr.ac_name);
    if(i4_len > _MAX_CH_NAME_LEN)
    {
        i4_len = _MAX_CH_NAME_LEN;
    }
    c_uc_ps_to_w2s(pt_svl_rec->uheader.t_rec_hdr.ac_name,
                   w2s_name,
                   (UINT32)i4_len);

    /* Get the broadcast type */
    if(pt_svl_rec->uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG)
    {
        w2s_type = MENU_TEXT(MLM_MENU_KEY_CH_ANLG);
    }
    else
    {
        w2s_type = MENU_TEXT(MLM_MENU_KEY_CH_DIG);
    }

    /* prepare data */
    c_memset(&t_img_suit, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit.h_normal                     = pt_this->t_masterlist_init.h_img_normal;
    t_img_suit.h_disable                    = NULL_HANDLE;
    t_img_suit.h_highlight                  = pt_this->t_masterlist_init.h_img_highlight;
    t_img_suit.h_highlight_unfocus          = pt_this->t_masterlist_init.h_img_normal;
    t_img_suit.h_pushed                     = NULL_HANDLE;
    t_img_suit.h_selected                   = pt_this->t_masterlist_init.h_img_selected;
    t_img_suit.h_selected_disable           = NULL_HANDLE;
    t_img_suit.h_selected_highlight         = pt_this->t_masterlist_init.h_img_selected_highlight;
    t_img_suit.h_selected_highlight_unfocus = pt_this->t_masterlist_init.h_img_selected;
    t_img_suit.h_selected_pushed            = NULL_HANDLE;

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_digits;
    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_type;
    at_items[2].e_col_type = LB_COL_TYPE_TEXT;
    at_items[2].data.pw2s_text = w2s_name;
    at_items[3].e_col_type = LB_COL_TYPE_IMG_SUIT;
    at_items[3].data.pt_img_suit = &t_img_suit;

    /* append item */
    i4_ret = c_wgl_do_cmd(pt_this->h_lb_ch,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(at_items),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Get the index */
    i4_ret = c_wgl_do_cmd(pt_this->h_lb_ch,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&ui2_idx),
                          NULL);
    MENU_CHK_FAIL(i4_ret);
    ui2_idx -= 1;

    /* Sel or not */
    if (ui4_nw_mask & ui4_sel_mask)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_lb_ch,
                              WGL_CMD_LB_SEL_ELEM,
                              WGL_PACK(ui2_idx),
                              NULL);
        MENU_CHK_FAIL(i4_ret);
    }

    /* mapping */
    pt_this->pui2_idx_recid_map[ui2_idx] = ui4_rec_id;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _update_all_svl_rec_fct
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
static INT32 _update_all_svl_rec_fct (
    HANDLE_T                    h_svl,
    UINT16                      ui2_idx,
    SVL_REC_T*                  pt_svl_rec,
    UINT32                      ui4_data1,
    UINT32                      ui4_data2
    )
{
    _MASTERLIST_T*              pt_this = &t_g_masterlist ;

    if (!pt_svl_rec)
    {
        MENU_CHK_FAIL (MENUR_INV_ARG) ;
    }

    if (pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE)
    {
        /* skip fake channel */
        return MENUR_OK ;
    }

    switch ((_QUK_OP_ITEM_T)ui4_data1)
    {
    case _QUK_OP_ITEM_MARK_ALL :
        pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask |=
                                pt_this->t_masterlist_init.ui4_sel_mask ;
        break ;

    case _QUK_OP_ITEM_UNMARK_ALL :
        pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask &=
                                ~pt_this->t_masterlist_init.ui4_sel_mask ;
        break ;

    case _QUK_OP_ITEM_DIG_ONLY :
        if (BRDCST_TYPE_ANALOG == pt_svl_rec->uheader.t_rec_hdr.e_brdcst_type)
        {
            pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask &=
                                ~pt_this->t_masterlist_init.ui4_sel_mask ;
        }
        else
        {
            pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask |=
                                pt_this->t_masterlist_init.ui4_sel_mask ;
        }
        break ;

    default :
        return MENUR_INV_ARG ;
    }

    MENU_CHK_FAIL (c_svl_update_rec(h_svl,pt_svl_rec,TRUE));

    return MENUR_OK ;
}

/*----------------------------------------------------------------------------
 * Name: _quk_op_on_sel
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
static INT32 _quk_op_on_sel (
    UINT16                      ui2_idx,
    BOOL                        b_sel
    )
{
    _MASTERLIST_T*              pt_this = &t_g_masterlist ;

    if (pt_this->b_is_refreshing)
    {
        return MENUR_OK;
    }

    if ((_QUK_OP_ITEM_T)ui2_idx >= _QUK_OP_ITEM_LAST_ENTRY)
    {
        return MENUR_INV_ARG ;
    }

    MENU_CHK_FAIL (a_tv_update_all_svl_recs (
                            pt_this->h_crnt_svl,
                            _update_all_svl_rec_fct,
                            (UINT32)ui2_idx,
                            0)) ;

    MENU_CHK_FAIL (_refresh_ch_lst ()) ;
    MENU_CHK_FAIL (_hlt_curent_ch());
    MENU_CHK_FAIL (menu_pm_repaint ()) ;

    return MENUR_OK ;
}

/*----------------------------------------------------------------------------
 * Name: _ch_lst_on_sel
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
static INT32 _ch_lst_on_sel (
    UINT16                      ui2_idx,
    BOOL                        b_sel
    )
{
    INT32                       i4_result;
    INT32                       i4_ret;
    UINT32                      ui4_ver_id;
    UINT16                      ui2_rec_id;
    SVL_REC_T                   t_svl_rec;
    UINT32                      ui4_sel_mask;
    _MASTERLIST_T*              pt_this = &t_g_masterlist ;

    if (pt_this->b_is_refreshing)
    {
        return MENUR_OK;
    }

    if (pt_this->h_crnt_svl == NULL_HANDLE)
    {
        return MENUR_OK;
    }

    /* get the list mask */
    ui4_sel_mask = pt_this->t_masterlist_init.ui4_sel_mask;

    /* get the rec id*/
    ui2_rec_id = pt_this->pui2_idx_recid_map[ui2_idx];

    /* update the record*/
    i4_result = c_svl_lock(pt_this->h_crnt_svl);
    if (i4_result != SVLR_OK)
    {
        i4_ret = MENUR_FAIL;
    }
    else
    {
        i4_result = c_svl_get_rec(pt_this->h_crnt_svl,
                                  ui2_rec_id,
                                  &t_svl_rec,
                                  &ui4_ver_id);

        if (i4_result == SVLR_REC_NOT_FOUND)
        {
            i4_ret = MENUR_FAIL;
        }
        else if (i4_result < 0)
        {
            i4_ret = MENUR_FAIL;
        }
        else
        {
            if (b_sel)
            {
                t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask |= ui4_sel_mask;
            }
            else
            {
                t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask &= ~ui4_sel_mask;
            }

            i4_result = c_svl_update_rec(
                                pt_this->h_crnt_svl,
                                &t_svl_rec,
                                TRUE);
            if (i4_result != SVLR_OK)
            {
                i4_ret = MENUR_FAIL;
            }
            else
            {
                i4_ret = MENUR_OK;
                if (pt_this->h_crnt_svl == t_g_menu_common.h_svl_air)
                {
                    t_g_menu_common.b_svl_air_dirty = TRUE;
                }
                else
                {
                    t_g_menu_common.b_svl_cable_dirty = TRUE;
                }
            }
        }
        c_svl_unlock(pt_this->h_crnt_svl);

    }/* finish to update record */

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _refresh_ch_lst
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
static INT32 _refresh_ch_lst (VOID)
{
    INT32                       i4_result;
    INT32                       i4_ret = MENUR_OK ;
    UINT32                      ui4_nw_mask;
    BRDCST_TYPE_T               e_brdcst_type;
    SVL_REC_T                   t_svl_rec;
    UINT16                      ui2_idx;
    UINT32                      ui4_ver_id = SVL_NULL_VER_ID;
    UINT16                      ui2_rec_num = 0;
    BOOL                        b_again;
    _MASTERLIST_T*              pt_this = &t_g_masterlist ;

    if (pt_this->h_crnt_svl == NULL_HANDLE)
    {
        /* do nothing */
        return MENUR_OK;
    }

    /* Set the refreshing flag */
    pt_this->b_is_refreshing = TRUE;

    /* get the list mask and broadcast type */
    ui4_nw_mask     = pt_this->t_masterlist_init.ui4_lst_mask;
    e_brdcst_type   = pt_this->t_masterlist_init.e_brdcst_type;

    /* This loop is used for redo the iteration when somebody
     * modify the SVL during our iteration.
     */
    do
    {
        b_again = FALSE;

        /* clear the list */
        i4_result = c_wgl_do_cmd(pt_this->h_lb_ch,
                                 WGL_CMD_LB_DEL_ALL,
                                 NULL, NULL);
        MENU_CHK_FAIL(i4_result);

        /* get record number */
        i4_result = c_svl_get_num_rec_by_brdcst_type(
                                 pt_this->h_crnt_svl,
                                 e_brdcst_type,
                                 ui4_nw_mask,
                                 &ui2_rec_num,
                                 &ui4_ver_id);
        if(i4_result != SVLR_OK)
        {
            i4_ret = MENUR_FAIL;
            DBG_ERROR(("<MENU> Can't get record number.\r\n"));
        }
        else
        {
            /* check if the record number exceeds the max channel number */
            if(ui2_rec_num > pt_this->t_masterlist_init.ui2_max_rec_num)
            {
                DBG_ERROR(("<MENU> Record number exceeds max sec number: %d < %d.\r\n",
                           ui2_rec_num, pt_this->t_masterlist_init.ui2_max_rec_num));
                ui2_rec_num = pt_this->t_masterlist_init.ui2_max_rec_num;
            }

            pt_this->ui2_ch_num = 0 ;

            /* iterate */
            for (ui2_idx = 0; ui2_idx < ui2_rec_num ; ui2_idx ++)
            {
                i4_result = c_svl_get_rec_by_brdcst_type(
                                pt_this->h_crnt_svl,
                                e_brdcst_type,
                                ui4_nw_mask,
                                ui2_idx,
                                &t_svl_rec,
                                &ui4_ver_id);
                if (i4_result == SVLR_MODIFIED)
                {
                    DBG_INFO(("<MENU> Somebody modifed the SVL.\r\n"));
                    b_again = TRUE;
                    break;
                }
                else if(i4_result != SVLR_OK)
                {
                    i4_ret = MENUR_FAIL;
                    DBG_ERROR(("<MENU> Can't iterate service list at idx=%d.\r\n",
                               ui2_idx));
                    break;
                }
                else if (t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE)
                {
                    /* skip fake channel */
                    continue ;
                }

                i4_result = _add_ch (&t_svl_rec);
                if (i4_result < 0)
                {
                    i4_ret = i4_result;
                    DBG_ERROR(("<MENU> Can't add channel to channel list.\r\n"));
                    break;
                }

                pt_this->ui2_ch_num ++ ;
            } /* end of Iteration */
        }
    }while(b_again);

    /* Set the refreshing flag */
    pt_this->b_is_refreshing = FALSE;

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _hlt_curent_ch
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
static INT32 _hlt_curent_ch (VOID)
{
    INT32                       i4_ret;
    SVL_REC_T                   t_svl_rec;
    BOOL                        b_found;
    UINT16                      ui2_idx = 0;
    _MASTERLIST_T*              pt_this = &t_g_masterlist ;

    /* get the current svl record */
    c_memset(&t_svl_rec, 0, sizeof(SVL_REC_T));
    i4_ret = menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
    MENU_CHK_FAIL(i4_ret);

    if(b_found)
    {
        for(ui2_idx = 0; ui2_idx < pt_this->ui2_ch_num ; ui2_idx ++)
        {
            if(pt_this->pui2_idx_recid_map[ui2_idx] == t_svl_rec.ui2_svl_rec_id)
            {
                break;
            }
        }

        if(ui2_idx == pt_this->ui2_ch_num)
        {
            ui2_idx = 0;
        }
    }

    i4_ret = c_wgl_do_cmd(pt_this->h_lb_ch,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui2_idx),                                    /* hlt elem */
                          WGL_PACK(ui2_idx % (UINT16)(CONTENT_H / GRID_H)));    /* hlt pos */
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _help_tip_update
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
static INT32 _help_tip_update (
    _HELP_TIP_TYPE_T            e_help_tip_type
    )
{
    UINT16                      ui2_elem_num ;
    UINT16                      ui2_hlt_idx ;
    UTF16_T*                    pw2s_help_tip ;
    HANDLE_T                    h_source ;
    _MASTERLIST_T*              pt_this = &t_g_masterlist ;

    switch (e_help_tip_type)
    {
    case _HELP_TIP_TYPE_QUK_OP :
    case _HELP_TIP_TYPE_LB_CH :
        {
            h_source = (_HELP_TIP_TYPE_QUK_OP == e_help_tip_type)
                     ? pt_this->h_quk_op
                     : pt_this->h_lb_ch ;

            MENU_CHK_FAIL (c_wgl_do_cmd(h_source,
                                WGL_CMD_LB_GET_ELEM_NUM,
                                WGL_PACK(&ui2_elem_num),
                                NULL)) ;
            MENU_CHK_FAIL (c_wgl_do_cmd(h_source,
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK(&ui2_hlt_idx),
                                NULL));
            if (0 == ui2_elem_num)
            {
                /* empty */
                pw2s_help_tip = NULL ;
            }
            else if (1 == ui2_elem_num)
            {
                /* only one element */
                pw2s_help_tip = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_TV_SETTING_BACK_HOME);
            }
            else if (ui2_hlt_idx == 0)
            {
                /* highlight on first */
                pw2s_help_tip = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_TV_SETTING_PREV_NEXT);
            }
            else if (ui2_hlt_idx == ui2_elem_num -1)
            {
                /* highlight on last */
                pw2s_help_tip = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_TV_SETTING_PREV_NEXT);
            }
            else
            {
                /* highlight on middle */
                pw2s_help_tip = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_TV_SETTING_PREV_NEXT);
            }

            MENU_CHK_FAIL (menu_hide_help_tip ());
            if (pw2s_help_tip)
            {
                MENU_CHK_FAIL (menu_set_and_trigger_help_tip (pw2s_help_tip)) ;
            }
        }
        break ;
    case _HELP_TIP_TYPE_HOMEBAR :
        MENU_CHK_FAIL (menu_hide_help_tip ());
        MENU_CHK_FAIL (menu_set_and_trigger_help_tip (MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR))) ;
        break ;
    case _HELP_TIP_TYPE_BACKBAR :
        MENU_CHK_FAIL (menu_hide_help_tip ());
        MENU_CHK_FAIL (menu_set_and_trigger_help_tip (MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR))) ;
        break ;

    default :
        MENU_CHK_FAIL (MENUR_INV_ARG) ;
    }

    return MENUR_OK ;
}

/*----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
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
static INT32 _homebar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32          ui4_keycode = (UINT32)pv_param1;
        _MASTERLIST_T*  pt_this = &t_g_masterlist;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_SELECT :
            menu_nav_go_home_menu();
            return WGLR_OK;

        case BTN_CURSOR_UP:
            /* set highlight of quick_operation & focus on it */
            c_wgl_do_cmd (pt_this->h_quk_op,
                                WGL_CMD_LB_HLT_ELEM,
                                WGL_PACK(2),
                                NULL);
            c_wgl_set_focus (pt_this->h_quk_op, WGL_SYNC_AUTO_REPAINT);

            /* update help tip */
            _help_tip_update (_HELP_TIP_TYPE_QUK_OP);
            break;

        case BTN_CURSOR_DOWN:
            MENU_CHK_FAIL (menu_set_focus_on_backbar (TRUE));

            /* update help tip */
            _help_tip_update (_HELP_TIP_TYPE_BACKBAR);
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
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
static INT32 _backbar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32          ui4_keycode = (UINT32)pv_param1;
        _MASTERLIST_T*  pt_this = &t_g_masterlist;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        case BTN_SELECT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_CURSOR_DOWN:
            /* set highlight of quick_operation & focus on it */
            c_wgl_do_cmd (pt_this->h_quk_op,
                                WGL_CMD_LB_HLT_ELEM,
                                WGL_PACK(0),
                                NULL);
            c_wgl_set_focus (pt_this->h_quk_op, WGL_SYNC_AUTO_REPAINT);

            /* update help tip */
            _help_tip_update (_HELP_TIP_TYPE_QUK_OP);
            break;

        case BTN_CURSOR_UP:
            MENU_CHK_FAIL (menu_set_focus_on_homebar (TRUE));

            /* update help tip */
            _help_tip_update (_HELP_TIP_TYPE_HOMEBAR);
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _lb_proc_fct
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
static INT32 _lb_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    UINT16                      ui2_idx;
    UINT16                      ui2_elem_num ;
    UINT32                      ui4_key_code = (UINT32)param1 ;

    if ((BTN_CURSOR_UP == ui4_key_code ||
         BTN_CURSOR_DOWN == ui4_key_code)
        &&
        (WGL_MSG_KEY_DOWN == ui4_msg ||
         WGL_MSG_KEY_REPEAT == ui4_msg))
    {
        /* Notice :
         * As BTN_CURSOR_UP used in listbox to change highlight ,
         * there is no WGL_NC_GL_KEY_DOWN for this key(on its parent widget)
         * So, We just check the BTN_CURSOR_UP here
         * and check the other message in _cnt_frm_proc_fct.
         */
        MENU_CHK_FAIL (c_wgl_do_cmd(h_widget,
                        WGL_CMD_LB_GET_HLT_INDEX,
                        WGL_PACK(&ui2_idx),
                        NULL));

        MENU_CHK_FAIL (c_wgl_do_cmd(h_widget,
                        WGL_CMD_LB_GET_ELEM_NUM,
                        WGL_PACK(&ui2_elem_num),
                        NULL)) ;

        if (0 == ui2_idx &&
            BTN_CURSOR_UP == ui4_key_code)
        {
            /* set focuse on backbar */
            MENU_CHK_FAIL (menu_set_focus_on_backbar(TRUE)) ;

            /* update help tip */
            _help_tip_update (_HELP_TIP_TYPE_BACKBAR) ;
        }
        else if (ui2_idx == (ui2_elem_num -1) &&
                 BTN_CURSOR_DOWN == ui4_key_code)
        {
            MENU_CHK_FAIL (menu_set_focus_on_homebar (TRUE)) ;

            /* update help tip */
            _help_tip_update (_HELP_TIP_TYPE_HOMEBAR) ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _ch_lb_proc_fct
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
static INT32 _ch_lb_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _cnt_frm_proc_fct
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
static INT32 _cnt_frm_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    HANDLE_T                    h_source ;
    WGL_NOTIFY_DATA_T*          pt_nfy_data ;
    _MASTERLIST_T*              pt_this = &t_g_masterlist ;

    if (WGL_MSG_NOTIFY == ui4_msg)
    {
        if(pt_this->b_is_refreshing)
        {
            return WMPR_DONE;
        }

        h_source = (HANDLE_T)param1 ;
        pt_nfy_data = (WGL_NOTIFY_DATA_T*)param2 ;

        switch (pt_nfy_data->ui4_nc_code)
        {
        case WGL_NC_LB_ELEM_SEL:
            if (menu_get_cond() != MENU_COND_NOT_INIT)
            {
                if (h_source == pt_this->h_lb_ch)
                {
                    _ch_lst_on_sel (pt_nfy_data->u.t_lb_elem_sel.ui2_elem_idx,
                                    pt_nfy_data->u.t_lb_elem_sel.b_is_selected);
                }
                else
                {
                    _quk_op_on_sel (pt_nfy_data->u.t_lb_elem_sel.ui2_elem_idx,
                                    pt_nfy_data->u.t_lb_elem_sel.b_is_selected);
                }
            }
            break;

        case WGL_NC_LB_ELEM_HLT:
            if (pt_nfy_data->u.t_lb_elem_hlt.b_is_highlighted)
            {
                MENU_CHK_FAIL (_help_tip_update (
                                    h_source == pt_this->h_quk_op
                                    ? _HELP_TIP_TYPE_QUK_OP
                                    : _HELP_TIP_TYPE_LB_CH));
            }
            break ;

        case WGL_NC_GL_KEY_DOWN:
        case WGL_NC_GL_KEY_REPEAT:
            if ((BTN_CURSOR_LEFT == pt_nfy_data->u.t_key.ui4_key_code ||
                 BTN_PREV_PRG== pt_nfy_data->u.t_key.ui4_key_code ||
                 BTN_RETURN == pt_nfy_data->u.t_key.ui4_key_code)
                &&
                h_source == pt_this->h_quk_op)
            {
                menu_nav_back();
            }
            else if((BTN_PREV_PRG== pt_nfy_data->u.t_key.ui4_key_code ||
                     BTN_RETURN== pt_nfy_data->u.t_key.ui4_key_code)
                     &&
                     h_source == pt_this->h_lb_ch)
            {
                menu_nav_back();
            }
            else if (BTN_CURSOR_LEFT == pt_nfy_data->u.t_key.ui4_key_code
                     &&
                     h_source == pt_this->h_lb_ch)
            {
                /* set highlight of quick_operation */
                c_wgl_do_cmd (pt_this->h_quk_op ,
                            WGL_CMD_LB_HLT_ELEM ,
                            WGL_PACK(0),
                            NULL);

                /* jump to quick_operation list and refresh it */
                c_wgl_set_focus (pt_this->h_quk_op , TRUE) ;

                /* update help tip */
                _help_tip_update (_HELP_TIP_TYPE_QUK_OP) ;
            }
            else if (BTN_CURSOR_RIGHT == pt_nfy_data->u.t_key.ui4_key_code
                     &&
                     h_source == pt_this->h_quk_op
                     &&
                     pt_this->ui2_ch_num != 0)
            {
                /* jump to ch list and refresh it */
                c_wgl_set_focus (pt_this->h_lb_ch , TRUE) ;

                /* update help tip */
                _help_tip_update (_HELP_TIP_TYPE_LB_CH) ;
            }
            else
            {
                /* do nothing */
            }
            break ;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _quk_op_create
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
static INT32 _quk_op_create (
    HANDLE_T                    h_parent,
    INT32                       i4_x,
    INT32                       i4_y,
    INT32                       i4_w,
    INT32                       i4_h,
    _MASTERLIST_T*              pt_masterlist,
    HANDLE_T*                   ph_quk_op
    )
{
    INT32                       i4_ret;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    GL_RECT_T                   t_rect;
    WGL_LB_KEY_MAP_T            t_lb_key_map;

    /* channel no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = _MAX_QUK_OP_TEXT_LEN;
    at_cols[0].ui2_width        = i4_w;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_NO_SCROLL ;

    if(!pt_masterlist->t_masterlist_init.b_wrap_over)
    {
        t_lb_init.ui4_style       |= WGL_STL_LB_NO_WRAP_OVER;
    }

    t_lb_init.ui2_max_elem_num  = _QUK_OP_ITEM_LAST_ENTRY;
    t_lb_init.ui2_elem_size     = _CH_LST_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,i4_x,i4_y,i4_w,i4_h);

    i4_ret = menu_list2_create (h_parent,
                                &t_rect,
                                _lb_proc_fct,
                                &t_lb_init,
                                NULL,
                                ph_quk_op);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for channel list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next      = BTN_CURSOR_DOWN;
    t_lb_key_map.ui4_key_prev      = BTN_CURSOR_UP;
    t_lb_key_map.ui4_key_select    = BTN_SELECT;
    t_lb_key_map.ui4_key_page_up   = BTN_INVALID;
    t_lb_key_map.ui4_key_page_down = BTN_INVALID;
    i4_ret = c_wgl_do_cmd(*ph_quk_op, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set element number */
    i4_ret = c_wgl_do_cmd ( *ph_quk_op,
                            WGL_CMD_LB_SET_ELEM_NUM,
                            WGL_PACK (_QUK_OP_ITEM_LAST_ENTRY),
                            NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set content */
    i4_ret = c_wgl_do_cmd (*ph_quk_op,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2 (0, 0),
                            WGL_PACK (MENU_TEXT(MLM_MENU_KEY_MARK_ALL)));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_quk_op,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2 (1, 0),
                            WGL_PACK (MENU_TEXT(MLM_MENU_KEY_UNMARK_ALL)));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_quk_op,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2 (2, 0),
                            WGL_PACK (MENU_TEXT(MLM_MENU_KEY_DIGITAL_ONLY)));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _ch_lst_create
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
static INT32 _ch_lst_create (
    HANDLE_T                    h_parent,
    INT32                       i4_x,
    INT32                       i4_y,
    INT32                       i4_w,
    INT32                       i4_h,
    _MASTERLIST_T*              pt_masterlist,
    HANDLE_T*                   ph_lb_ch
    )
{
    INT32                       i4_ret;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[4];
    GL_RECT_T                   t_rect;
    WGL_LB_KEY_MAP_T            t_lb_key_map;

    /* channel no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = _CH_LST_COL0_ALIGN;
    at_cols[0].ui2_max_text_len = _MAX_CH_NUM_LEN;
    at_cols[0].ui2_width        = _CH_LST_COL0_W;

    /* ATV/DTV */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = _CH_LST_COL1_ALIGN;
    at_cols[1].ui2_max_text_len = _MAX_CH_TYPE_LEN;
    at_cols[1].ui2_width        = _CH_LST_COL1_W;

    /* channel name or starting time */
    at_cols[2].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[2].ui1_align        = _CH_LST_COL2_ALIGN;
    at_cols[2].ui2_max_text_len = _MAX_CH_NAME_LEN;
    at_cols[2].ui2_width        = _CH_LST_COL2_W;

    /* pre-selected */
    at_cols[3].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[3].ui1_align        = _CH_LST_COL3_ALIGN;
    at_cols[3].ui2_width        = _CH_LST_COL3_W;

    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_MULTI_SEL;

    if(!pt_masterlist->t_masterlist_init.b_scroll)
    {
        t_lb_init.ui4_style       |= WGL_STL_LB_NO_SCROLL;
    }

    #if 0
    if(!pt_masterlist->t_masterlist_init.b_wrap_over)
    {
        t_lb_init.ui4_style       |= WGL_STL_LB_NO_WRAP_OVER;
    }
    #endif

    t_lb_init.ui2_max_elem_num  = pt_masterlist->t_masterlist_init.ui2_max_rec_num;
    t_lb_init.ui2_elem_size     = _CH_LST_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 4;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect ,i4_x,i4_y,i4_w,i4_h);

    i4_ret = menu_list2_create (h_parent,
                                &t_rect,
                                _ch_lb_proc_fct,
                                &t_lb_init,
                                NULL ,
                                ph_lb_ch);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for channel list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next      = BTN_CURSOR_DOWN;
    t_lb_key_map.ui4_key_prev      = BTN_CURSOR_UP;
    t_lb_key_map.ui4_key_select    = BTN_SELECT;
    t_lb_key_map.ui4_key_page_up   = BTN_RED;
    t_lb_key_map.ui4_key_page_down = BTN_GREEN;
    i4_ret = c_wgl_do_cmd(*ph_lb_ch, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
* Name: _masterlist_alloc_resource
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
static INT32 _masterlist_alloc_resource (
    _MASTERLIST_T*              pt_masterlist
    )
{
    INT32                               i4_ret = MENUR_FAIL;
    MENU_COMMON_CHANNEL_LIST_INIT_T*    pt_masterlist_init = NULL;

    if (!pt_masterlist)
    {
        return MENUR_INV_ARG ;
    }

    pt_masterlist_init = &pt_masterlist->t_masterlist_init;

    /* Attach data */
    do
    {
        pt_masterlist->pui2_idx_recid_map =
            c_mem_alloc(pt_masterlist_init->ui2_max_rec_num * sizeof(UINT16));
        if(pt_masterlist->pui2_idx_recid_map == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        /* create quick_operation list box */
        i4_ret = _quk_op_create (pt_masterlist->h_cnt_frm ,
                                _QUK_OP_X,
                                _QUK_OP_Y,
                                _QUK_OP_W,
                                _QUK_OP_H,
                                pt_masterlist,
                                &pt_masterlist->h_quk_op);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /* Create channel list box */
        i4_ret = _ch_lst_create(pt_masterlist->h_cnt_frm ,
                                _CH_LST_X,
                                _CH_LST_Y,
                                _CH_LST_W,
                                _CH_LST_H,
                                pt_masterlist,
                                &pt_masterlist->h_lb_ch);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = c_wgl_set_visibility(pt_masterlist->h_cnt_frm ,
                                WGL_SW_RECURSIVE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = MENUR_OK;
    }while(0);

    if(i4_ret != MENUR_OK)
    {
        if(pt_masterlist->h_quk_op != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_masterlist->h_quk_op);
        }

        if(pt_masterlist->h_lb_ch != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_masterlist->h_lb_ch);
        }

        if(pt_masterlist->pui2_idx_recid_map != NULL)
        {
            c_mem_free(pt_masterlist->pui2_idx_recid_map);
        }
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _masterlist_free_resource
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
static INT32 _masterlist_free_resource (
    _MASTERLIST_T*              pt_masterlist
    )
{
    if(pt_masterlist->h_lb_ch != NULL_HANDLE)
    {
        c_wgl_destroy_widget_ex(pt_masterlist->h_lb_ch, FALSE);
    }

    if(pt_masterlist->h_quk_op != NULL_HANDLE)
    {
        c_wgl_destroy_widget_ex (pt_masterlist->h_quk_op ,FALSE);
    }

    if(pt_masterlist->pui2_idx_recid_map != NULL)
    {
        c_mem_free(pt_masterlist->pui2_idx_recid_map);
    }

    return MENUR_OK;
}

#ifdef ________________________________________________________JUST_FOR_DIVISION
#endif
/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _on_page_create
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
static INT32 _on_page_create (
    UINT32                      ui4_page_id,
    VOID*                       pv_create_data
    )
{
    INT32                       i4_ret  = MENUR_FAIL;
    _MASTERLIST_T*              pt_this = &t_g_masterlist ;

    do
    {
        c_memset(pt_this, 0, sizeof(_MASTERLIST_T));

        pt_this->ui4_page_id = ui4_page_id;

        pt_this->t_masterlist_init.ui2_msg_title            = MLM_MENU_KEY_MASTERLIST;
        pt_this->t_masterlist_init.ui2_max_rec_num          = CH_LST_ELEM_N;
        pt_this->t_masterlist_init.h_img_normal             = h_g_menu_img_unskip;
        pt_this->t_masterlist_init.h_img_highlight          = h_g_menu_img_unskip_hlt;
        pt_this->t_masterlist_init.h_img_selected           = h_g_menu_img_skip;
        pt_this->t_masterlist_init.h_img_selected_highlight = h_g_menu_img_skip_hlt;
        pt_this->t_masterlist_init.ui4_lst_mask             = SB_VNET_ACTIVE;
        pt_this->t_masterlist_init.ui4_sel_mask             = SB_VNET_VISIBLE;
        pt_this->t_masterlist_init.e_brdcst_type            = BRDCST_TYPE_UNKNOWN;
        pt_this->t_masterlist_init.b_scroll                 = _CH_LST_STL_SCROLL;
        pt_this->t_masterlist_init.b_wrap_over              = CH_LST_STL_WRAP_OVER;
        pt_this->t_masterlist_init.b_back_on_left           = TRUE;

        i4_ret = menu_page_get_cnt_frm (ui4_page_id, &pt_this->h_cnt_frm) ;
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm, WGL_SW_HIDE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = menu_page_set_proc_func (ui4_page_id, _cnt_frm_proc_fct) ;
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = MENUR_OK;
    }while(0);

    if(i4_ret != MENUR_OK)
    {
        /* do release function here */
    }

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: _on_page_destroy
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
static INT32 _on_page_destroy (
    UINT32                      ui4_page_id
    )
{
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_show
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
static INT32 _on_page_show(
    UINT32                      ui4_page_id
    )
{
    GL_RECT_T                   t_rect ;
    WGL_IMG_INFO_T              t_img_info;
    HANDLE_T                    h_main_frm;
    _MASTERLIST_T*              pt_this = &t_g_masterlist;

    pt_this->h_crnt_svl = menu_get_crnt_svl();

    /* move main frame */
    MENU_CHK_FAIL (menu_pm_get_main_frm (&h_main_frm)) ;
    SET_RECT_BY_SIZE(&t_rect ,_FRM_X ,_FRM_Y ,_FRM_W ,_FRM_H);
    MENU_CHK_FAIL (c_wgl_move (h_main_frm ,&t_rect, FALSE)) ;

    /* move content frame */
    SET_RECT_BY_SIZE(&t_rect ,CONTENT_X ,CONTENT_Y,_FRM_W - CONTENT_X,CONTENT_H);
    MENU_CHK_FAIL (c_wgl_move (pt_this->h_cnt_frm ,&t_rect, FALSE)) ;

    /* move help tip */
    MENU_CHK_FAIL (menu_move_help_tip (_FRM_X,
                                MENU_PAGE_HELP_TIP_DEF_RECT,
                                _FRM_W,
                                MENU_PAGE_HELP_TIP_DEF_RECT,
                                FALSE)) ;

    /* set background image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_bk3;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_bk3;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_bk3;
    MENU_CHK_FAIL (c_wgl_do_cmd(h_main_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info)));

    MENU_CHK_FAIL (_masterlist_alloc_resource(pt_this));
    MENU_CHK_FAIL (_refresh_ch_lst());

    if (pt_this->ui2_ch_num)
    {
        MENU_CHK_FAIL (_hlt_curent_ch());
    }
    MENU_CHK_FAIL (menu_main_set_title(pt_this->t_masterlist_init.ui2_msg_title));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_hide
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
static INT32 _on_page_hide (
    UINT32                      ui4_page_id
    )
{
    GL_RECT_T                   t_rect ;
    WGL_IMG_INFO_T              t_img_info;
    HANDLE_T                    h_main_frm;
    _MASTERLIST_T*              pt_this = &t_g_masterlist;

    /* hide help tip */
    MENU_CHK_FAIL (menu_hide_help_tip ());

    /* move back the help tip */
    MENU_CHK_FAIL (menu_move_help_tip (
                                MENU_PAGE_HELP_TIP_DEF_RECT,
                                MENU_PAGE_HELP_TIP_DEF_RECT,
                                MENU_PAGE_HELP_TIP_DEF_RECT,
                                MENU_PAGE_HELP_TIP_DEF_RECT,
                                FALSE)) ;

    /* move the main frame back to the orignal position */
    MENU_CHK_FAIL (menu_pm_get_main_frm (&h_main_frm)) ;
    SET_RECT_BY_SIZE(&t_rect ,FRAME_X ,FRAME_Y ,FRAME_W ,FRAME_H);
    MENU_CHK_FAIL (c_wgl_move (h_main_frm ,&t_rect, FALSE)) ;

    /* we need not move the content frame back to orignal position as
     * it will used only for this page
     */
    /* restore background image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_bk0;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_bk0;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_bk0;
    MENU_CHK_FAIL (c_wgl_do_cmd(h_main_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info)));

    MENU_CHK_FAIL (_masterlist_free_resource (pt_this));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_get_focus
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
static INT32 _on_page_get_focus(
    UINT32                      ui4_page_id,
    MENU_PAGE_HINT_T*           pt_hint
    )
{
    _MASTERLIST_T*              pt_this = &t_g_masterlist ;

    /* set highlight of quick_operation & focus on it */
    c_wgl_do_cmd (pt_this->h_quk_op ,WGL_CMD_LB_HLT_ELEM , WGL_PACK(0) ,NULL);
    c_wgl_set_focus (pt_this->h_quk_op, WGL_NO_AUTO_REPAINT);

    /* update help tip */
    _help_tip_update (_HELP_TIP_TYPE_QUK_OP) ;

    /* set callback function for homebar */
    menu_set_homebar_proc (_homebar_proc_fct) ;

    /* set callback function for backbar */
    menu_set_backbar_proc (_backbar_proc_fct) ;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_lose_focus
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
static INT32 _on_page_lose_focus (
    UINT32                      ui4_page_id
    )
{
    /* clean callback function of backbar & homebar */
    MENU_LOG_ON_FAIL (menu_set_backbar_proc (NULL)) ;
    MENU_LOG_ON_FAIL (menu_set_homebar_proc (NULL)) ;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_update
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
static INT32 _on_page_update (
    UINT32                      ui4_page_id,
    UINT32                      ui4_update_mask
    )
{
    INT32                       i4_ret;
    MENU_PAGE_STATE_T           e_state;
    ISL_REC_T                   t_isl_rec;

    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        /* do_nothing */
    }

    /* leave channel related items when input source is changed to non-TV. */
    if((ui4_update_mask & MENU_PAGE_UMASK_REFRESH) != 0)
    {
        i4_ret = menu_page_get_state(ui4_page_id, &e_state);
        MENU_CHK_FAIL(i4_ret);

        if (e_state == MENU_PAGE_STATE_SHOW
            ||
            e_state == MENU_PAGE_STATE_FOCUS)
        {
            i4_ret = menu_get_crnt_isl(&t_isl_rec);
            MENU_CHK_FAIL(i4_ret);

            if (t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
            {
                /* do_nothing */
            }
            else
            {
                menu_nav_back();
            }
        }
    }

    return MENUR_OK;
}

#ifdef ________________________________________________________JUST_FOR_DIVISION
#endif

/*----------------------------------------------------------------------------
 * Name: menu_ex_page_masterlist_init
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
INT32 menu_ex_page_masterlist_init (VOID)
{
    t_g_menu_page_ex_masterlist.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_ex_masterlist.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_ex_masterlist.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_ex_masterlist.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_ex_masterlist.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_ex_masterlist.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_ex_masterlist.pf_menu_page_update=     _on_page_update;

/*    i4_ret=c_fe_create_font(SN_FONT_DEFAULT,
                    FE_FNT_SIZE_MEDIUM,
                    FE_FNT_STYLE_REGULAR,
                    FE_CMAP_ENC_UNICODE,
                    &h_g_font);
    MENU_CHK_FAIL(i4_ret);
*/

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_ex_page_masterlist_enabled
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
BOOL menu_ex_page_masterlist_enabled(VOID)
{
    INT32       i4_ret;
    HANDLE_T    h_crnt_svl = menu_get_crnt_svl();
    UINT16      ui2_rec_num = 0;
    UINT32      ui4_ver_id = 0;

    if(h_crnt_svl == NULL_HANDLE)
    {
        return FALSE;
    }
    else
    {
        i4_ret = c_svl_get_num_rec_by_brdcst_type(h_crnt_svl,
                                                  BRDCST_TYPE_UNKNOWN,
                                                  SB_VNET_ACTIVE,
                                                  &ui2_rec_num,
                                                  &ui4_ver_id);
        if(i4_ret != 0 ||
           ui2_rec_num == 0)
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}

#endif /* COMMON_EX_MASTERLIST_ENABLE */

