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
#include "u_sm_video_hdlr.h"
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
#include "c_svctx.h"

#include "wdk/a_vkb.h"
#include "wdk/vkb/vkb.h"

#include "app_util/a_ui.h"
#include "app_util/a_cfg.h"
#include "app_util/a_isl.h"
#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_page.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_dbg.h"

#ifdef COMMON_EX_CH_EDIT_ENABLE

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define _FRM_X                      (FRAME_X)
#define _FRM_Y                      (FRAME_Y)
#define _FRM_W                      (FRAME_W)
#define _FRM_H                      (FRAME_H)

#define _VKB_X                      (0*GRID_W)
#define _VKB_Y                      (0*GRID_H)

#define _CH_LST_STL_SCROLL          0
#define _CH_LST_BACK_ON_LEFT        0

#define _CH_LST_X                   (0 * GRID_W)
#define _CH_LST_Y                   (0 * GRID_H)
#define _CH_LST_W                   (CONTENT_W)
#define _CH_LST_H                   (CONTENT_H)

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

#define _MAX_CH_TYPE_LEN            (16)
#define _MAX_CH_NUM_LEN             ( 9)
#define _MAX_CH_NAME_LEN            (10)
#define _MAX_QUK_OP_TEXT_LEN        (32)

typedef enum {
   _QUK_OP_ITEM_MARK_ALL = 0 ,
   _QUK_OP_ITEM_UNMARK_ALL ,
   _QUK_OP_ITEM_DIG_ONLY ,
   _QUK_OP_ITEM_LAST_ENTRY

}  _QUK_OP_ITEM_T ;

typedef enum {
    _HELP_TIP_TYPE_CH_LST = 0 ,
    _HELP_TIP_TYPE_HOMEBAR ,
    _HELP_TIP_TYPE_BACKBAR ,
    _HELP_TIP_TYPE_VKB ,
    _HELP_TIP_TYPE_LAST_ENTRY

} _HELP_TIP_TYPE_T ;

typedef struct
{
    UINT32                          ui4_page_id;
    MENU_COMMON_CHANNEL_LIST_INIT_T t_ch_edit_init;
    UINT16                          ui2_ch_num;
    UINT16*                         pui2_idx_recid_map;
    HANDLE_T                        h_crnt_svl ;
    HANDLE_T                        h_cnt_frm ;
    HANDLE_T                        h_lb_ch;
    HANDLE_T                        h_vkb ;
    BOOL                            b_is_refreshing;
    BOOL                            b_is_vkb_shown;
} _CH_EDIT_T ;
    
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T                 t_g_menu_page_ex_ch_edit;
_CH_EDIT_T                          t_g_ch_edit ;

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

static INT32 _help_tip_update (
    _HELP_TIP_TYPE_T            e_help_tip_type
    ) ;

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
#ifdef ________________________________________________________JUST_FOR_DIVISION
#endif
/*----------------------------------------------------------------------------
 * Name: _strip_trailing_space
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static SIZE_T _strip_trailing_space(CHAR*   ps_char,
                                    UINT8   ui1_max_len)
{
    UINT8   ui1_len = 0;
    UINT8   ui1_idx = 0;

    ui1_len = (UINT8)c_strlen(ps_char);
    if(ui1_len == 0) {
        return ui1_len;
    }

    if (ui1_len > ui1_max_len) {
        ui1_len = ui1_max_len;
    }

    for (ui1_idx = ui1_len; ui1_idx > 0; ui1_idx--) {
        if(ps_char[ui1_idx-1] != ' ') {
           break;
        }
        ps_char[ui1_idx-1] = '\0';
    }

    return (SIZE_T)ui1_idx;
}
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
    UTF16_T                     w2s_digits[_MAX_CH_NUM_LEN+1];
    UTF16_T                     w2s_name[MAX_PROG_NAME_LEN+1];
    UTF16_T*                    w2s_type;
    BOOL                        b_one_part_ch ;
    UINT16                      ui2_major ;
    UINT16                      ui2_minor ;
    INT32                       i4_len ;
    UINT16                      ui2_idx ;
    WGL_LB_ITEM_T               at_items[4] ;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit ;
    _CH_EDIT_T*              pt_this = &t_g_ch_edit ;

    if (!pt_svl_rec)
    {
        return MENUR_INV_ARG ;
    }

    ui4_channel_id = pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id;
    ui4_rec_id     = pt_svl_rec->ui2_svl_rec_id;
    b_one_part_ch  = SB_ATSC_IS_ONE_PART_CHANNEL_ID(ui4_channel_id);
    ui2_major      = SB_ATSC_GET_MAJOR_CHANNEL_NUM(ui4_channel_id);
    ui2_minor      = SB_ATSC_GET_MINOR_CHANNEL_NUM(ui4_channel_id);

    /* Get the channel number */
    c_memset(w2s_digits, 0, sizeof(w2s_digits));
    _ch_num_to_str(ui2_major, ui2_minor, b_one_part_ch, w2s_digits);

    /* Get the channel name */
    c_memset(w2s_name, 0, sizeof(w2s_name));
    i4_len = (INT32)c_strlen(pt_svl_rec->uheader.t_rec_hdr.ac_name);
    if(i4_len > MAX_PROG_NAME_LEN)
    {
        i4_len = MAX_PROG_NAME_LEN;
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
    t_img_suit.h_normal                     = pt_this->t_ch_edit_init.h_img_normal;
    t_img_suit.h_disable                    = NULL_HANDLE;
    t_img_suit.h_highlight                  = pt_this->t_ch_edit_init.h_img_highlight;
    t_img_suit.h_highlight_unfocus          = pt_this->t_ch_edit_init.h_img_normal;
    t_img_suit.h_pushed                     = NULL_HANDLE;
    t_img_suit.h_selected                   = pt_this->t_ch_edit_init.h_img_selected;
    t_img_suit.h_selected_disable           = NULL_HANDLE;
    t_img_suit.h_selected_highlight         = pt_this->t_ch_edit_init.h_img_selected_highlight;
    t_img_suit.h_selected_highlight_unfocus = pt_this->t_ch_edit_init.h_img_selected;
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

    /* mapping */
    pt_this->pui2_idx_recid_map[ui2_idx] = ui4_rec_id;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _update_ch_name
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
static INT32 _update_ch_name (
    UINT16                      ui2_idx ,
    UTF16_T*                    pw2s_new_ch_name ,
    UINT32                      ui4_len
    )
{
    UINT16                      ui2_rec_id ;
    SVL_REC_T                   t_svl_rec ;
    UINT32                      ui4_ver_id = SVL_NULL_VER_ID ;
    _CH_EDIT_T*                 pt_this = &t_g_ch_edit ;

    MENU_CHK_FAIL (c_svl_lock(pt_this->h_crnt_svl)) ;

    do
    {
        /* get the rec id*/
        ui2_rec_id = pt_this->pui2_idx_recid_map[ui2_idx];

        MENU_BREAK_ON_FAIL (c_svl_get_rec(
                                pt_this->h_crnt_svl,
                                ui2_rec_id,
                                &t_svl_rec,
                                &ui4_ver_id)) ;

        c_uc_w2s_to_ps(pw2s_new_ch_name,
                                t_svl_rec.uheader.t_rec_hdr.ac_name,
                                ui4_len);

        /* set channel name modified flag */
        t_svl_rec.uheader.t_rec_hdr.ui4_option_mask |= SB_VOPT_CH_NAME_EDITED;

        MENU_BREAK_ON_FAIL (c_svl_update_rec(
                                pt_this->h_crnt_svl,
                                &t_svl_rec,
                                TRUE)) ;

        if (pt_this->h_crnt_svl == t_g_menu_common.h_svl_air)
        {
            t_g_menu_common.b_svl_air_dirty = TRUE;
        }
        else
        {
            t_g_menu_common.b_svl_cable_dirty = TRUE;
        }
    } while (0) ;

    MENU_CHK_FAIL (c_svl_unlock(pt_this->h_crnt_svl)) ;

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
    INT32                       i4_len ;
    UINT32                      ui4_ver_id;
    UINT16                      ui2_rec_id;
    SVL_REC_T                   t_svl_rec;
    UINT32                      ui4_channel_id ;
    BOOL                        b_one_part_ch ;
    UINT16                      ui2_major ;
    UINT16                      ui2_minor ;
    UTF16_T                     w2s_digits[_MAX_CH_NUM_LEN+1];
    UTF16_T                     w2s_name[MAX_PROG_NAME_LEN+1];
    _CH_EDIT_T*                 pt_this = &t_g_ch_edit ;

    if (pt_this->b_is_refreshing)
    {
        return MENUR_OK;
    }

    if (pt_this->h_crnt_svl == NULL_HANDLE)
    {
        return MENUR_OK;
    }

    /* get the rec id*/
    ui2_rec_id = pt_this->pui2_idx_recid_map[ui2_idx];

    MENU_CHK_FAIL (c_svl_get_rec(pt_this->h_crnt_svl,
                                ui2_rec_id,
                                &t_svl_rec,
                                &ui4_ver_id));

    ui4_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;
    b_one_part_ch  = SB_ATSC_IS_ONE_PART_CHANNEL_ID(ui4_channel_id);
    ui2_major      = SB_ATSC_GET_MAJOR_CHANNEL_NUM(ui4_channel_id);
    ui2_minor      = SB_ATSC_GET_MINOR_CHANNEL_NUM(ui4_channel_id);

    /* Get the channel number */
    c_memset(w2s_digits, 0, sizeof(w2s_digits));
    _ch_num_to_str(ui2_major, ui2_minor, b_one_part_ch, w2s_digits);

    /* Get the channel name */
    c_memset(w2s_name, 0, sizeof(w2s_name));
    i4_len = (INT32)c_strlen(t_svl_rec.uheader.t_rec_hdr.ac_name);
    if(i4_len > MAX_PROG_NAME_LEN)
    {
        i4_len = MAX_PROG_NAME_LEN;
    }
    c_uc_ps_to_w2s(t_svl_rec.uheader.t_rec_hdr.ac_name,w2s_name,(UINT32)i4_len);

    /* hide channel list */
    c_wgl_set_visibility(pt_this->h_lb_ch, WGL_SW_HIDE);

    /* set vkb lable */
    MENU_CHK_FAIL (a_vkb_do_cmd (pt_this->h_vkb,
                                VKB_CMD_SET_LABEL_TEXT,
                                (VOID*) w2s_digits,
                                (VOID*) _MAX_CH_NUM_LEN)) ;


    /* set vkb initial text */
    MENU_CHK_FAIL (a_vkb_do_cmd (pt_this->h_vkb,
                                VKB_CMD_SET_INITIAL_TEXT,
                                (VOID*) w2s_name,
                                (VOID*) MAX_PROG_NAME_LEN)) ;

    /* show vkb */
    pt_this->b_is_vkb_shown = TRUE;
    MENU_CHK_FAIL (a_vkb_show (pt_this->h_vkb)) ;

    /* repaint */
    menu_pm_repaint ();

    /* update help tip */
    _help_tip_update (_HELP_TIP_TYPE_VKB) ;

    return MENUR_OK ;
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
    _CH_EDIT_T*              pt_this = &t_g_ch_edit ;

    if (pt_this->h_crnt_svl == NULL_HANDLE)
    {
        /* do nothing */
        return MENUR_OK;
    }

    /* Set the refreshing flag */
    pt_this->b_is_refreshing = TRUE;

    /* get the list mask and broadcast type */
    ui4_nw_mask     = pt_this->t_ch_edit_init.ui4_lst_mask;
    e_brdcst_type   = pt_this->t_ch_edit_init.e_brdcst_type;

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
            if(ui2_rec_num > pt_this->t_ch_edit_init.ui2_max_rec_num)
            {
                DBG_ERROR(("<MENU> Record number exceeds max sec number: %d < %d.\r\n",
                           ui2_rec_num, pt_this->t_ch_edit_init.ui2_max_rec_num));
                ui2_rec_num = pt_this->t_ch_edit_init.ui2_max_rec_num;
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
    _CH_EDIT_T   *              pt_this = &t_g_ch_edit ;

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
    _CH_EDIT_T*                 pt_this = &t_g_ch_edit;

    switch (e_help_tip_type)
    {
    case _HELP_TIP_TYPE_CH_LST:
        {
            MENU_CHK_FAIL (c_wgl_do_cmd(pt_this->h_lb_ch,
                                        WGL_CMD_LB_GET_ELEM_NUM,
                                        WGL_PACK(&ui2_elem_num),
                                        NULL)) ;
            MENU_CHK_FAIL (c_wgl_do_cmd(pt_this->h_lb_ch,
                                        WGL_CMD_LB_GET_HLT_INDEX,
                                        WGL_PACK(&ui2_hlt_idx),
                                        NULL));
            if (ui2_elem_num == 0)
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
                pw2s_help_tip = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_TV_SETTING_BACK_NEXT);
            }
            else if (ui2_hlt_idx == ui2_elem_num -1)
            {
                /* highlight on last */
                pw2s_help_tip = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_TV_SETTING_PREV_HOME);
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
        break;
    case _HELP_TIP_TYPE_VKB:
        MENU_CHK_FAIL (menu_hide_help_tip ());
        break;
    case _HELP_TIP_TYPE_HOMEBAR:
        MENU_CHK_FAIL (menu_hide_help_tip ());
        MENU_CHK_FAIL (menu_set_and_trigger_help_tip (MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR))) ;
        break;
    case _HELP_TIP_TYPE_BACKBAR:
        MENU_CHK_FAIL (menu_hide_help_tip ());
        MENU_CHK_FAIL (menu_set_and_trigger_help_tip (MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR))) ;
        break;

    default:
        return MENUR_INV_ARG;
    }

    return MENUR_OK ;
}

/*----------------------------------------------------------------------------
 * Name: _vkb_nfy_fct
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
static INT32 _vkb_nfy_fct (
    VOID*                   pv_tag ,
    UINT32                  ui4_msg ,
    VOID*                   pv_param1 ,
    VOID*                   pv_param2
    )
{
    UINT16                  ui2_idx = 0 ;
    CHAR                    ps_temp[MAX_PROG_NAME_LEN+1]={0};
    UTF16_T                 w2s_new_ch_name[MAX_PROG_NAME_LEN+1] = {0};
    _CH_EDIT_T*             pt_this = &t_g_ch_edit;

    switch (ui4_msg)
    {
    case VKB_MSG_DLG_CANCEL :
        /* Hide VKB */
        pt_this->b_is_vkb_shown = FALSE;
        MENU_CHK_FAIL (a_vkb_set_visibility(pt_this->h_vkb ,FALSE));

        /* set focus on ch list */
        MENU_CHK_FAIL (c_wgl_set_visibility(pt_this->h_lb_ch, WGL_SW_RECURSIVE));
        MENU_CHK_FAIL (c_wgl_set_focus(pt_this->h_lb_ch ,WGL_NO_AUTO_REPAINT));

        /* update help tip */
        _help_tip_update (_HELP_TIP_TYPE_CH_LST) ;

        /* repaint */
        MENU_LOG_ON_FAIL (menu_pm_repaint ()) ;
    break ;

    case VKB_MSG_DLG_FINISHED :
        /* retrieve the new channel name. */
        MENU_CHK_FAIL (a_vkb_do_cmd(
                            pt_this->h_vkb,
                            VKB_CMD_GET_TEXT,
                            (VOID*) w2s_new_ch_name,
                            (VOID*) (UINT32) MAX_PROG_NAME_LEN));

        c_uc_w2s_to_ps(w2s_new_ch_name, ps_temp, _MAX_CH_NAME_LEN);
        _strip_trailing_space(ps_temp, MAX_PROG_NAME_LEN+1);
        c_uc_ps_to_w2s(ps_temp, w2s_new_ch_name,_MAX_CH_NAME_LEN);

        /* Apply the new channel name */
        MENU_CHK_FAIL (c_wgl_do_cmd(
                            pt_this->h_lb_ch ,
                            WGL_CMD_LB_GET_HLT_INDEX,
                            WGL_PACK(&ui2_idx),
                            NULL));
        MENU_CHK_FAIL (c_wgl_do_cmd (
                            pt_this->h_lb_ch,
                            WGL_CMD_LB_SET_ITEM_TEXT ,
                            WGL_PACK_2 (ui2_idx, 2),
                            WGL_PACK (w2s_new_ch_name))) ;

        /* update the record*/
        MENU_CHK_FAIL (_update_ch_name (ui2_idx ,w2s_new_ch_name ,MAX_PROG_NAME_LEN));

        /* Hide VKB */
        pt_this->b_is_vkb_shown = FALSE;
        MENU_CHK_FAIL (a_vkb_set_visibility (pt_this->h_vkb ,FALSE));

        /* set focus on ch list */
        MENU_CHK_FAIL (c_wgl_set_visibility(pt_this->h_lb_ch, WGL_SW_RECURSIVE));
        MENU_CHK_FAIL (c_wgl_set_focus(
                            pt_this->h_lb_ch,
                            WGL_NO_AUTO_REPAINT));

        /* update help tip */
        _help_tip_update (_HELP_TIP_TYPE_CH_LST);

        /* repaint */
        MENU_LOG_ON_FAIL (menu_pm_repaint ());
    break ;

    case VKB_MSG_DLG_KEY_INPUT :
    {
        UINT32               ui4_keycode = (*((UINT32*) pv_param1));
        VKB_CONTROL_LOGIC_T* pt_vkb_ctrl = NULL;

        if((BTN_PREV_PRG == ui4_keycode) ||
           (BTN_RETURN   == ui4_keycode))
        {
            /* Hide VKB */
            pt_this->b_is_vkb_shown = FALSE;
            MENU_CHK_FAIL (a_vkb_set_visibility (pt_this->h_vkb, FALSE));

            /* set focus on ch list */
            MENU_CHK_FAIL (c_wgl_set_visibility(pt_this->h_lb_ch, WGL_SW_RECURSIVE));
            MENU_CHK_FAIL (c_wgl_set_focus(pt_this->h_lb_ch ,WGL_NO_AUTO_REPAINT));

            /* update help tip */
            _help_tip_update (_HELP_TIP_TYPE_CH_LST) ;

            /* repaint */
            MENU_LOG_ON_FAIL (menu_pm_repaint ()) ;

            return WDK_NO_ACTION;
        }

        /* Get attach data */
        MENU_CHK_FAIL (c_wgl_do_cmd(pt_this->h_vkb,
                              WGL_CMD_GL_GET_ATTACH_DATA,
                              WGL_PACK(&pt_vkb_ctrl),
                              NULL));

        if((ui4_keycode == BTN_CURSOR_UP) &&
           (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY)&&
           (pt_vkb_ctrl->t_focus_item.t_normal_key.ui1_focus_idx_row == 0))
        {
            /* set highlight of backbar & focus on it */
            MENU_CHK_FAIL(menu_set_focus_on_backbar (TRUE));
            return WDK_NO_ACTION;
        }
        else if((ui4_keycode == BTN_CURSOR_DOWN) &&
                (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_CANCEL))
        {
            /* set highlight of homebar & focus on it */
            MENU_CHK_FAIL (menu_set_focus_on_homebar(TRUE));
            return WDK_NO_ACTION;
        }

    break;
    }
    default :
    break ;    
    }

    return MENUR_OK;
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
        _CH_EDIT_T*     pt_this     = &t_g_ch_edit ;
        UINT32          ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            if(pt_this->b_is_vkb_shown == TRUE)
            {
                 /* Hide VKB by set visibility and repaint  */
                pt_this->b_is_vkb_shown = FALSE;
                MENU_CHK_FAIL (a_vkb_set_visibility (pt_this->h_vkb ,FALSE)) ;

                /* invoke API to set foucs on parent page  */
                c_wgl_set_visibility(pt_this->h_lb_ch, WGL_SW_RECURSIVE);
                c_wgl_set_focus(pt_this->h_lb_ch, WGL_NO_AUTO_REPAINT);

                /* repaint */
                MENU_LOG_ON_FAIL (menu_pm_repaint ()) ;
                menu_hide_help_tip();
                MENU_CHK_FAIL (_help_tip_update (_HELP_TIP_TYPE_CH_LST));
            }
            else
            {
                menu_nav_back();
            }
            break;

        case BTN_SELECT:
            menu_nav_go_home_menu ();
            return WGLR_OK;

        case BTN_CURSOR_DOWN:
            /* set highlight on backbar & focus on it */
            menu_set_focus_on_backbar (TRUE) ;

            /* update help tip */
            _help_tip_update (_HELP_TIP_TYPE_BACKBAR) ;
            break;

        case BTN_CURSOR_UP:
            if(pt_this->b_is_vkb_shown == FALSE)
            {
                if (pt_this->ui2_ch_num)
                {
                    /* set highlight on backbar & focus on it */
                    c_wgl_do_cmd (pt_this->h_lb_ch ,
                                        WGL_CMD_LB_HLT_ELEM ,
                                        WGL_PACK(pt_this->ui2_ch_num - 1) ,
                                        NULL);
                    /* make sure it can be see */
                    MENU_CHK_FAIL (c_wgl_do_cmd (pt_this->h_lb_ch,
                                        WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                                        NULL,
                                        NULL));

                    c_wgl_set_focus (pt_this->h_lb_ch, WGL_SYNC_AUTO_REPAINT);

                    /* update help tip */
                    _help_tip_update (_HELP_TIP_TYPE_CH_LST);
                }
            }
            else
            {
                VKB_CONTROL_LOGIC_T* pt_vkb_ctrl = NULL;
                INT32  i4_ret = WDKR_OK;

                /* Get attach data */
                i4_ret = c_wgl_do_cmd(pt_this->h_vkb,
                                   WGL_CMD_GL_GET_ATTACH_DATA,
                                   WGL_PACK(&pt_vkb_ctrl),
                                   NULL);
                MENU_CHK_FAIL (i4_ret);

                pt_vkb_ctrl->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_CANCEL;

                /* set focus on Cancel button */
                i4_ret = c_wgl_set_focus (pt_vkb_ctrl->h_cancel_txt,
                                          WGL_SYNC_AUTO_REPAINT);
                WDK_CHK_FAIL(i4_ret);

                menu_hide_help_tip();
            }
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
        INT32                   i4_ret;
        _CH_EDIT_T*             pt_this = &t_g_ch_edit ;
        VKB_CONTROL_LOGIC_T*    pt_vkb_ctrl = NULL;
        UINT32                  ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        case BTN_SELECT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            if(pt_this->b_is_vkb_shown == TRUE)
            {
                 /* Hide VKB by set visibility and repaint  */
                pt_this->b_is_vkb_shown = FALSE;
                MENU_CHK_FAIL (a_vkb_set_visibility (pt_this->h_vkb ,FALSE)) ;

                /* invoke API to set foucs on parent page  */
                c_wgl_set_visibility(pt_this->h_lb_ch, WGL_SW_RECURSIVE);
                c_wgl_set_focus(pt_this->h_lb_ch, WGL_NO_AUTO_REPAINT);

                /* repaint */
                MENU_LOG_ON_FAIL (menu_pm_repaint ());

                menu_hide_help_tip();
                MENU_CHK_FAIL (_help_tip_update (_HELP_TIP_TYPE_CH_LST));
            }
            else
            {
                menu_nav_back();
            }
            return WGLR_OK;

        case BTN_CURSOR_DOWN:
            if(pt_this->b_is_vkb_shown == FALSE)
            {
                /* set highlight of quick_operation & focus on it */
                if (pt_this->ui2_ch_num)
                {
                    c_wgl_do_cmd (pt_this->h_lb_ch ,
                                        WGL_CMD_LB_HLT_ELEM ,
                                        WGL_PACK(0) ,
                                        NULL);

                    /* make sure it can be see */
                    MENU_CHK_FAIL (c_wgl_do_cmd (pt_this->h_lb_ch ,
                                        WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE ,
                                        NULL ,
                                        NULL)) ;

                    c_wgl_set_focus (pt_this->h_lb_ch, WGL_SYNC_AUTO_REPAINT);

                    /* update help tip */
                    _help_tip_update (_HELP_TIP_TYPE_CH_LST) ;
                }
            }
            else
            {
                /* Get attach data */
                i4_ret = c_wgl_do_cmd(pt_this->h_vkb,
                                   WGL_CMD_GL_GET_ATTACH_DATA,
                                   WGL_PACK(&pt_vkb_ctrl),
                                   NULL);
                MENU_CHK_FAIL (i4_ret);

                pt_vkb_ctrl->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                pt_vkb_ctrl->t_focus_item.t_normal_key.ui1_focus_idx_row = 0;
                pt_vkb_ctrl->t_focus_item.t_normal_key.ui1_focus_idx_col = 0;

                /* set focus on a button */
                i4_ret = c_wgl_set_focus (pt_vkb_ctrl->aah_normal_key_txt[0][0],
                                          WGL_SYNC_AUTO_REPAINT);
                WDK_CHK_FAIL(i4_ret);

                menu_hide_help_tip();
            }
            break;

        case BTN_CURSOR_UP:
            menu_set_focus_on_homebar (TRUE);

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
static INT32 _lb_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    UINT16                      ui2_idx;
    _CH_EDIT_T*                 pt_this = &t_g_ch_edit ;
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
        if (0 == ui2_idx
            &&
            BTN_CURSOR_UP == ui4_key_code)
        {
            /* set focuse on backbar */
            MENU_CHK_FAIL (menu_set_focus_on_backbar(TRUE));

            /* update help tip */
            _help_tip_update (_HELP_TIP_TYPE_BACKBAR);
        }
        else if (pt_this->ui2_ch_num -1 == ui2_idx
                 &&
                 BTN_CURSOR_DOWN == ui4_key_code)
        {
            /* set focuse on backbar */
            MENU_CHK_FAIL (menu_set_focus_on_homebar(TRUE));

            /* update help tip */
            _help_tip_update (_HELP_TIP_TYPE_HOMEBAR);
        }
    }

    else if(((BTN_PREV_PRG== ui4_key_code)||
             (BTN_RETURN== ui4_key_code))
            &&
            (WGL_MSG_KEY_DOWN == ui4_msg))
    {
        menu_nav_back();
    }

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
    _CH_EDIT_T*                 pt_this = &t_g_ch_edit ;

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
            if (menu_get_cond() != MENU_COND_NOT_INIT
                &&
                h_source == pt_this->h_lb_ch)
            {
                _ch_lst_on_sel (pt_nfy_data->u.t_lb_elem_sel.ui2_elem_idx,
                                pt_nfy_data->u.t_lb_elem_sel.b_is_selected);
            }
            break;

        case WGL_NC_LB_ELEM_HLT:
            if (pt_nfy_data->u.t_lb_elem_hlt.b_is_highlighted
                &&
                h_source == pt_this->h_lb_ch)
            {
                MENU_CHK_FAIL (_help_tip_update (_HELP_TIP_TYPE_CH_LST));
            }
            break ;

        case WGL_NC_GL_KEY_DOWN:
        case WGL_NC_GL_KEY_REPEAT:
            if (BTN_CURSOR_LEFT == pt_nfy_data->u.t_key.ui4_key_code)
            {
                menu_nav_back();
            }
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _vkb_create
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
static INT32 _vkb_create (VOID)
{
    VKB_INIT_T      t_init_data;
    _CH_EDIT_T*     pt_this = &t_g_ch_edit ;

    t_init_data.h_parent            = pt_this->h_cnt_frm ;
    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_DEFAULT ;
    t_init_data.t_gui_rc.i4_left    = _VKB_X;
    t_init_data.t_gui_rc.i4_top     = _VKB_Y;
    t_init_data.pf_data_change_fct  = _vkb_nfy_fct;
    t_init_data.pv_tag              = NULL;

    MENU_CHK_FAIL (a_vkb_create(&t_init_data ,&pt_this->h_vkb)) ;

    /* set max char num */
    a_vkb_do_cmd (pt_this->h_vkb,
                  VKB_CMD_SET_MAX_CHAR_NUM,
                  (VOID*)_MAX_CH_NAME_LEN,
                  NULL);

    return MENUR_OK ;
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
    _CH_EDIT_T*                 pt_ch_edit,
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
    at_cols[2].ui2_max_text_len = MAX_PROG_NAME_LEN;
    at_cols[2].ui2_width        = _CH_LST_COL2_W;

    /* pre-selected */
    at_cols[3].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[3].ui1_align        = _CH_LST_COL3_ALIGN;
    at_cols[3].ui2_width        = _CH_LST_COL3_W;

    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH ;

    if(!pt_ch_edit->t_ch_edit_init.b_scroll)
    {
        t_lb_init.ui4_style       |= WGL_STL_LB_NO_SCROLL;
    }

    if(!pt_ch_edit->t_ch_edit_init.b_wrap_over)
    {
        t_lb_init.ui4_style       |= WGL_STL_LB_NO_WRAP_OVER;
    }

    t_lb_init.ui2_max_elem_num  = pt_ch_edit->t_ch_edit_init.ui2_max_rec_num;
    t_lb_init.ui2_elem_size     = _CH_LST_ELEM_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 4;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect ,i4_x,i4_y,i4_w,i4_h);

    i4_ret = menu_list2_create (h_parent,
                                &t_rect,
                                _lb_proc_fct,
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
* Name: _ch_edit_alloc_resource
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
static INT32 _ch_edit_alloc_resource (
    _CH_EDIT_T*              pt_ch_edit
    )
{
    INT32                               i4_ret = MENUR_FAIL;
    MENU_COMMON_CHANNEL_LIST_INIT_T*    pt_ch_edit_init = NULL;

    if (!pt_ch_edit)
    {
        return MENUR_INV_ARG ;
    }

    pt_ch_edit_init = &pt_ch_edit->t_ch_edit_init;

    /* Attach data */
    do
    {
        pt_ch_edit->pui2_idx_recid_map =
            c_mem_alloc(pt_ch_edit_init->ui2_max_rec_num * sizeof(UINT16));
        if(pt_ch_edit->pui2_idx_recid_map == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        /* Create channel list box */
        i4_ret = _vkb_create () ;
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = a_vkb_set_visibility (pt_ch_edit->h_vkb ,FALSE) ;
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        /* Create channel list box */
        i4_ret = _ch_lst_create(pt_ch_edit->h_cnt_frm ,
                                _CH_LST_X,
                                _CH_LST_Y,
                                _CH_LST_W,
                                _CH_LST_H,
                                pt_ch_edit,
                                &pt_ch_edit->h_lb_ch);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = c_wgl_set_visibility(pt_ch_edit->h_lb_ch ,WGL_SW_NORMAL);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = MENUR_OK;
    }while(0);

    if(i4_ret != MENUR_OK)
    {
        if(pt_ch_edit->h_lb_ch != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ch_edit->h_lb_ch);
        }

        if(pt_ch_edit->pui2_idx_recid_map != NULL)
        {
            c_mem_free(pt_ch_edit->pui2_idx_recid_map);
        }
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _ch_edit_free_resource
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
static INT32 _ch_edit_free_resource (
    _CH_EDIT_T*              pt_ch_edit
    )
{
    if (pt_ch_edit->h_vkb != NULL_HANDLE)
    {
        a_vkb_set_visibility (pt_ch_edit->h_vkb ,FALSE) ;
        a_vkb_destroy (pt_ch_edit->h_vkb) ;
    }

    if(pt_ch_edit->h_lb_ch != NULL_HANDLE)
    {
        c_wgl_destroy_widget_ex(pt_ch_edit->h_lb_ch, FALSE);
    }

    if(pt_ch_edit->pui2_idx_recid_map != NULL)
    {
        c_mem_free(pt_ch_edit->pui2_idx_recid_map);
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
    _CH_EDIT_T*                 pt_this = &t_g_ch_edit ;

    do
    {
        c_memset(pt_this, 0, sizeof(_CH_EDIT_T));

        pt_this->ui4_page_id = ui4_page_id;

        pt_this->t_ch_edit_init.ui2_msg_title            = MLM_MENU_KEY_CHANNEL_NAME_EDIT;
        pt_this->t_ch_edit_init.ui2_max_rec_num          = CH_LST_ELEM_N;
        pt_this->t_ch_edit_init.h_img_normal             = NULL_HANDLE;
        pt_this->t_ch_edit_init.h_img_highlight          = NULL_HANDLE;
        pt_this->t_ch_edit_init.h_img_selected           = NULL_HANDLE;
        pt_this->t_ch_edit_init.h_img_selected_highlight = NULL_HANDLE;
        pt_this->t_ch_edit_init.ui4_lst_mask             = SB_VNET_ACTIVE;
        pt_this->t_ch_edit_init.ui4_sel_mask             = SB_VNET_VISIBLE;
        pt_this->t_ch_edit_init.e_brdcst_type            = BRDCST_TYPE_UNKNOWN;
        pt_this->t_ch_edit_init.b_scroll                 = _CH_LST_STL_SCROLL;
        pt_this->t_ch_edit_init.b_wrap_over              = CH_LST_STL_WRAP_OVER;
        pt_this->t_ch_edit_init.b_back_on_left           = TRUE;

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
    _CH_EDIT_T*              pt_this = &t_g_ch_edit ;

    pt_this->h_crnt_svl = menu_get_crnt_svl();

#if 0
    GL_RECT_T                   t_rect  ;
    HANDLE_T                    h_main_frm ;

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

    /* set background image for ch_edit */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE;
    MENU_CHK_FAIL (c_wgl_do_cmd(h_main_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info)));
#endif

    MENU_CHK_FAIL (_ch_edit_alloc_resource(pt_this));
    MENU_CHK_FAIL (_refresh_ch_lst());
    if (pt_this->ui2_ch_num)
    {
        MENU_CHK_FAIL (_hlt_curent_ch());
    }
    MENU_CHK_FAIL (menu_main_set_title(pt_this->t_ch_edit_init.ui2_msg_title));

    t_g_ch_edit.b_is_vkb_shown = FALSE;
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
    _CH_EDIT_T*                 pt_this = &t_g_ch_edit ;

    /* hide help tip */
    MENU_CHK_FAIL (menu_hide_help_tip ());

#if 0
    GL_RECT_T                   t_rect  ;
    HANDLE_T                    h_main_frm ;

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
#endif

    MENU_CHK_FAIL (_ch_edit_free_resource (pt_this));

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
    _CH_EDIT_T*              pt_this = &t_g_ch_edit ;

    /* set highlight of quick_operation & focus on it */
    if (pt_this->ui2_ch_num)
    {
        c_wgl_set_focus (pt_this->h_lb_ch, WGL_NO_AUTO_REPAINT);

        /* update help tip */
        _help_tip_update (_HELP_TIP_TYPE_CH_LST);
    }
    else
    {
        menu_set_focus_on_backbar (FALSE);

        /* update help tip */
        _help_tip_update (_HELP_TIP_TYPE_BACKBAR);
    }

    /* set callback function for homebar */
    menu_set_homebar_proc (_homebar_proc_fct);

    /* set callback function for backbar */
    menu_set_backbar_proc (_backbar_proc_fct);

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
 * Name: menu_page_ex_ch_edit
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
INT32 menu_page_ex_ch_edit_init (VOID)
{
    t_g_menu_page_ex_ch_edit.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_ex_ch_edit.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_ex_ch_edit.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_ex_ch_edit.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_ex_ch_edit.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_ex_ch_edit.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_ex_ch_edit.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

#endif /* COMMON_EX_CH_EDIT_ENABLE */

