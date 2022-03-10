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
 * $RCSfile: wzd_clr.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/11 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: d86d704b96b676ace4198ef41405b049 $
 *
 * Description:
 *      This file defines the colors used by the Wizard application.
 *---------------------------------------------------------------------------*/
#ifndef _WZD_COLOR_H_
#define _WZD_COLOR_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_sets.h"

#include "app_util/a_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/

/* main frame */
extern GL_COLOR_T   t_g_wzd_color_main_frm_bk;

/* base map frame */
extern GL_COLOR_T   t_g_wzd_color_base_frm_bk;

/* layout frame */
extern GL_COLOR_T   t_g_wzd_color_layout_frm_bk;

/* title list */
extern GL_COLOR_T   t_g_wzd_color_title_lst_bk;
extern GL_COLOR_T   t_g_wzd_color_title_lst_vp;
extern GL_COLOR_T   t_g_wzd_color_title_lst_elem_bk;
extern GL_COLOR_T   t_g_wzd_color_title_lst_elem_hlt_bk;
extern GL_COLOR_T   t_g_wzd_color_title_lst_elem_hlt_uf_bk;
extern GL_COLOR_T   t_g_wzd_color_title_lst_col_bk;
extern GL_COLOR_T   t_g_wzd_color_title_lst_col_txt;
extern GL_COLOR_T   t_g_wzd_color_title_lst_col_hlt_txt;
extern GL_COLOR_T   t_g_wzd_color_title_lst_col_hlt_uf_txt;

/* Setting list */
extern GL_COLOR_T   t_g_wzd_color_seti_lst_bk;
extern GL_COLOR_T   t_g_wzd_color_seti_lst_vp;
extern GL_COLOR_T   t_g_wzd_color_seti_lst_elem_bk;
extern GL_COLOR_T   t_g_wzd_color_seti_lst_elem_hlt_bk;
extern GL_COLOR_T   t_g_wzd_color_seti_lst_elem_hlt_uf_bk;
extern GL_COLOR_T   t_g_wzd_color_seti_lst_col_bk;
extern GL_COLOR_T   t_g_wzd_color_seti_lst_col_txt;
extern GL_COLOR_T   t_g_wzd_color_seti_lst_col_dis_txt;
extern GL_COLOR_T   t_g_wzd_color_seti_lst_col_hlt_txt;
extern GL_COLOR_T   t_g_wzd_color_seti_lst_col_hlt_uf_txt;

/* help list */
extern GL_COLOR_T   t_g_wzd_color_help_lst_bk;
extern GL_COLOR_T   t_g_wzd_color_help_lst_vp;
extern GL_COLOR_T   t_g_wzd_color_help_lst_elem_bk;
extern GL_COLOR_T   t_g_wzd_color_help_lst_elem_hlt_bk;
extern GL_COLOR_T   t_g_wzd_color_help_lst_elem_hlt_uf_bk;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_bk;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_back_txt;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_back_hlt_txt;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_back_hlt_uf_txt;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_select_txt;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_select_hlt_txt;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_select_hlt_uf_txt;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_enter_txt;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_enter_hlt_txt;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_enter_hlt_uf_txt;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_exit_txt;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_exit_hlt_txt;
extern GL_COLOR_T   t_g_wzd_color_help_lst_col_exit_hlt_uf_txt;

/* Title text. */
extern GL_COLOR_T   t_g_wzd_color_title_txt_bk;
extern GL_COLOR_T   t_g_wzd_color_title_txt_nor;
extern GL_COLOR_T   t_g_wzd_color_title_txt_hlt;

/* Description text. */
extern GL_COLOR_T   t_g_wzd_color_desc_txt_bk;
extern GL_COLOR_T   t_g_wzd_color_desc_txt;

/* Scan progress bar. */
extern GL_COLOR_T   t_g_wzd_color_scan_bar_txt;

extern GL_COLOR_T   t_g_wzd_color_dlg_txt;
extern GL_COLOR_T	t_g_wzd_color_dlg_desc_txt;

extern GL_COLOR_T   t_g_wzd_color_network_frame_bk;
extern GL_COLOR_T   t_g_wzd_color_network_txt_nor;
extern GL_COLOR_T   t_g_wzd_color_network_txt_hlt;

/* TV Setup */
extern GL_COLOR_T   t_g_wzd_color_cho_sig_frame_bk;
extern GL_COLOR_T   t_g_wzd_color_cho_sig_txt_bk;

extern GL_COLOR_T   t_g_wzd_color_tv_setup_txt_nor;
extern GL_COLOR_T   t_g_wzd_color_tv_setup_txt_hlt;

extern GL_COLOR_T   t_g_wzd_color_tv_setup_lb_nor;
extern GL_COLOR_T   t_g_wzd_color_tv_setup_lb_hlt;
extern GL_COLOR_T   t_g_wzd_color_begin_txt;

extern GL_COLOR_T      t_g_wzd_color_scan_txt_bk;
extern GL_COLOR_T      t_g_wzd_color_scan_txt;

extern GL_COLOR_T      t_g_wzd_color_footer_hlt_txt;
extern GL_COLOR_T      t_g_wzd_color_footer_enable_txt;
extern GL_COLOR_T      t_g_wzd_color_footer_disable_txt;

/* Select box */
extern GL_COLOR_T	t_g_wzd_color_sel_box_hlt_txt;
extern GL_COLOR_T	t_g_wzd_color_sel_box_enable_txt;
extern GL_COLOR_T	t_g_wzd_color_sel_box_disable_txt;

extern GL_COLOR_T      t_g_wzd_color_edt_hlt_txt;
extern GL_COLOR_T      t_g_wzd_color_edt_enable_txt;

extern GL_COLOR_T      t_g_wzd_color_cho_mode_txt_bg;
extern GL_COLOR_T      t_g_wzd_color_cho_mode_txt_wihte;
extern GL_COLOR_T      t_g_wzd_color_cho_mode_txt_gray;

/* API's */
extern INT32 wzd_color_init (VOID);

#endif /* _WZD_COLOR_H_ */
