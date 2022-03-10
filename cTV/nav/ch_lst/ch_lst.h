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
 * $RCSfile: ch_lst.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/54 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e2d2b1a79d31b7290e162f409db02988 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _CH_LST_H_
#define _CH_LST_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_flm.h"
#include "u_irrc_btn_def.h"

#include "nav/nav_common.h"
#include "res/nav/nav_view.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define CUSTOM_BTN_CH_LST_PG_UP           ((UINT32)(KEY_GROUP_MAX | 0x0000f030))
#define CUSTOM_BTN_CH_LST_PG_DN           ((UINT32)(KEY_GROUP_MAX | 0x0000f031))

typedef struct _NAV_CH_LST_VIEW_T
{
    /* channel list */
    HANDLE_T                    h_ch_lst_frame;
    HANDLE_T                    h_ch_lst;
    HANDLE_T                    h_pg_up_icon;
    HANDLE_T                    h_pg_dn_icon;
    HANDLE_T                    h_sel_list_icon;
    HANDLE_T                    h_exit_icon;
    HANDLE_T                    h_pg_up_help_msg;
    HANDLE_T                    h_pg_dn_help_msg;
    HANDLE_T                    h_sel_list_help_msg;
    HANDLE_T                    h_exit_help_msg;
    WGL_HIMG_TPL_T              h_img_red_btn;
    WGL_HIMG_TPL_T              h_img_green_btn;
    WGL_HIMG_TPL_T              h_img_yellow_btn;
    WGL_HIMG_TPL_T              h_img_blue_btn;

    HANDLE_T                    h_cnt_indctr;
    UINT32                      ui4_indctr_sts;

#ifdef APP_IMG_UI
    WGL_HIMG_TPL_T              h_img_ch_list_bk;
    WGL_HIMG_TPL_T              h_img_hlt_bar_bk;
#endif

    HANDLE_T                    h_font;
    BOOL                        b_lazy_init;
} NAV_CH_LST_VIEW_T;

#define CH_DTL_THIS_PAGE        (0)
#define CH_DTL_NEXT_PAGE        (1)
#define CH_DTL_PREV_PAGE        (2)
#define CH_DTL_FIRST_PAGE       (3)

typedef struct _NAV_CH_DTL_VIEW_T
{
    HANDLE_T                    h_frame;
    HANDLE_T                    h_detail;
    HANDLE_T                    h_title;
    UINT16                      ui2_page_lines;
#ifndef APP_CH_DETAIL_NO_SCROLL
    HANDLE_T                    h_lf_icon;
    HANDLE_T                    h_rt_icon;
    HANDLE_T                    h_index;
    WGL_HIMG_TPL_T              h_img_arrow_lf;
    WGL_HIMG_TPL_T              h_img_arrow_rt;
#endif

#ifdef APP_IMG_UI
    WGL_HIMG_TPL_T              h_img_bk;
#endif
    BOOL                        b_lazy_init;
} NAV_CH_DTL_VIEW_T;

#ifndef MAX_ELEM_OF_CH_LIST
    #define MAX_ELEM_OF_CH_LIST      7 /* maximum = 7 */
#endif

typedef struct _NAV_CH_LST_T
{
    HANDLE_T                    h_crnt_svl;
    UINT16                      ui2_crnt_svl_id;
    TV_WIN_ID_T                 e_focus_tv_win_id;

    NAV_CH_LIST_ELMNT_T         t_elements[MAX_ELEM_OF_CH_LIST];
    BOOL                        b_is_on;
    BOOL                        b_is_list_on;       /*b_ch_list_on;*/
    BOOL                        b_is_detail_on;
    BOOL                        b_is_support_multiple_channel_list;           /* Multiple channel list supported */
    BOOL                        b_is_support_satellite_selection;             /* Satellite selection supported */
    UINT16                      ui2_focused_idx;    /*ui2_ch_list_hlt_idx;*/
    HANDLE_T                    h_hide_timer;
    BOOL                        b_ch_changed;

    UINT16                      ui2_first_svl_rec_id;
    UINT32                      ui4_first_channel_id;
    UINT16                      ui2_last_svl_rec_id;
    UINT32                      ui4_last_channel_id;
    UINT32                      ui4_cnt_indctr_state;

    NAV_CH_LST_VIEW_T           t_lst_view;
    NAV_CH_DTL_VIEW_T           t_dtl_view;
} NAV_CH_LST_T;
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern VOID nav_ch_lst_rcu_key_handler(
                    UINT32                      ui4_key_code
                    );
extern VOID nav_ch_lst_do_elem_hlt(
                    NAV_CH_LST_T*               pt_this,
                    UINT16                      ui2_hlt_idx
                    );
extern VOID nav_ch_lst_do_reach_top(
                    NAV_CH_LST_T*               pt_this
                    );
extern VOID nav_ch_lst_do_reach_bottom(
                    NAV_CH_LST_T*               pt_this
                    );
/* channel list view */
extern INT32 nav_ch_lst_view_init(
                    NAV_CH_LST_T*               pt_this,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    );
extern INT32 nav_ch_lst_view_deinit(
                    NAV_CH_LST_VIEW_T*          pt_view
                    );
extern INT32 nav_ch_lst_view_hide(
                    NAV_CH_LST_VIEW_T*          pt_view
                    );
extern INT32 nav_ch_lst_view_show(
                    NAV_CH_LST_VIEW_T*          pt_view,
                    UINT32                      ui4_cnt_indctr_sts
                    );
extern INT32 nav_ch_lst_view_update(
                    NAV_CH_LST_VIEW_T*          pt_view,
                    NAV_CH_LIST_ELMNT_T*        pt_ch_list,
                    UINT16                      ui2_total_size,
                    UINT16                      ui2_ch_list_size,
                    UINT16                      ui2_hlt_elem_idx,
                    UINT32                      ui4_cnt_indctr_sts,
                    BOOL                        b_repaint
                    );
extern VOID nav_ch_lst_view_load_msgs(
                    UINT8                       ui1_lang_id
                    );
/* channel details view */
extern INT32 nav_ch_dtl_view_init(
                    NAV_CH_LST_T*               pt_this,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    );
extern INT32 nav_ch_dtl_view_deinit(
                    NAV_CH_DTL_VIEW_T*          pt_view
                    );
extern INT32 nav_ch_dtl_view_show(
                    NAV_CH_DTL_VIEW_T*          pt_view
                    );
extern INT32 nav_ch_dtl_view_hide(
                    NAV_CH_DTL_VIEW_T*          pt_view
                    );
extern INT32 nav_ch_dtl_view_updn_page(
                    NAV_CH_DTL_VIEW_T*          pt_view,
                    UINT8                       ui1_page_dir,
                    BOOL                        b_repaint
                    );
extern INT32 nav_ch_dtl_view_reset_detail(
                    NAV_CH_DTL_VIEW_T*          pt_view,
                    BOOL                        b_repaint
                    );
extern INT32 nav_ch_dtl_view_update(
                    NAV_CH_DTL_VIEW_T*          pt_view,
                    UTF16_T*                    pw2s_detail,
                    CHAR*                       ps_ch_name
                    );
extern VOID nav_ch_lst_custom_rcu_key_pre_handler(
                    UINT32*                     pui4_key_code
                    );

extern BOOL nav_ch_lst_is_under_satellite_mode(VOID);
#endif /* _CH_LST_H_ */
