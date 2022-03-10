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
 * $RCSfile: wzd_clr.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/15 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: f52e6eab4b8f188db6b5557a2ccdae2c $
 *
 * Description:
 *      This file defines the color used by the Wizard application.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "res/wizard_anim/wzd_clr.h"
#include "res/wizard_anim/wzd_cfg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/

/* main frame */
GL_COLOR_T      t_g_wzd_color_main_frm_bk;

/* base map frame */
GL_COLOR_T      t_g_wzd_color_base_frm_bk;

/* layout frame */
GL_COLOR_T      t_g_wzd_color_layout_frm_bk;

/* title list */
GL_COLOR_T      t_g_wzd_color_title_lst_bk;
GL_COLOR_T      t_g_wzd_color_title_lst_vp;
GL_COLOR_T      t_g_wzd_color_title_lst_elem_bk;
GL_COLOR_T      t_g_wzd_color_title_lst_elem_hlt_bk;
GL_COLOR_T      t_g_wzd_color_title_lst_elem_hlt_uf_bk;
GL_COLOR_T      t_g_wzd_color_title_lst_col_bk;
GL_COLOR_T      t_g_wzd_color_title_lst_col_txt;
GL_COLOR_T      t_g_wzd_color_title_lst_col_hlt_txt;
GL_COLOR_T      t_g_wzd_color_title_lst_col_hlt_uf_txt;

/* Setting list */
GL_COLOR_T      t_g_wzd_color_seti_lst_bk;
GL_COLOR_T      t_g_wzd_color_seti_lst_vp;
GL_COLOR_T      t_g_wzd_color_seti_lst_elem_bk;
GL_COLOR_T      t_g_wzd_color_seti_lst_elem_hlt_bk;
GL_COLOR_T      t_g_wzd_color_seti_lst_elem_hlt_uf_bk;
GL_COLOR_T      t_g_wzd_color_seti_lst_col_bk;
GL_COLOR_T      t_g_wzd_color_seti_lst_col_txt;
GL_COLOR_T      t_g_wzd_color_seti_lst_col_dis_txt;
GL_COLOR_T      t_g_wzd_color_seti_lst_col_hlt_txt;
GL_COLOR_T      t_g_wzd_color_seti_lst_col_hlt_uf_txt;

/* help list */
GL_COLOR_T      t_g_wzd_color_help_lst_bk;
GL_COLOR_T      t_g_wzd_color_help_lst_vp;
GL_COLOR_T      t_g_wzd_color_help_lst_elem_bk;
GL_COLOR_T      t_g_wzd_color_help_lst_elem_hlt_bk;
GL_COLOR_T      t_g_wzd_color_help_lst_elem_hlt_uf_bk;
GL_COLOR_T      t_g_wzd_color_help_lst_col_bk;
GL_COLOR_T      t_g_wzd_color_help_lst_col_back_txt;
GL_COLOR_T      t_g_wzd_color_help_lst_col_back_hlt_txt;
GL_COLOR_T      t_g_wzd_color_help_lst_col_back_hlt_uf_txt;
GL_COLOR_T      t_g_wzd_color_help_lst_col_select_txt;
GL_COLOR_T      t_g_wzd_color_help_lst_col_select_hlt_txt;
GL_COLOR_T      t_g_wzd_color_help_lst_col_select_hlt_uf_txt;
GL_COLOR_T      t_g_wzd_color_help_lst_col_enter_txt;
GL_COLOR_T      t_g_wzd_color_help_lst_col_enter_hlt_txt;
GL_COLOR_T      t_g_wzd_color_help_lst_col_enter_hlt_uf_txt;
GL_COLOR_T      t_g_wzd_color_help_lst_col_exit_txt;
GL_COLOR_T      t_g_wzd_color_help_lst_col_exit_hlt_txt;
GL_COLOR_T      t_g_wzd_color_help_lst_col_exit_hlt_uf_txt;

/* Title text. */
GL_COLOR_T      t_g_wzd_color_title_txt_bk;
GL_COLOR_T      t_g_wzd_color_title_txt_nor;
GL_COLOR_T      t_g_wzd_color_title_txt_hlt;

/* Description text. */
GL_COLOR_T      t_g_wzd_color_desc_txt_bk;
GL_COLOR_T      t_g_wzd_color_desc_txt;
GL_COLOR_T      t_g_wzd_color_footer_txt;

GL_COLOR_T      t_g_wzd_color_dlg_txt;
GL_COLOR_T      t_g_wzd_color_dlg_desc_txt;

/* Scan progress bar. */
GL_COLOR_T      t_g_wzd_color_scan_bar_txt;

GL_COLOR_T      t_g_wzd_color_network_frame_bk;
GL_COLOR_T      t_g_wzd_color_network_txt_nor;
GL_COLOR_T      t_g_wzd_color_network_txt_hlt;

/* TV setup */
GL_COLOR_T      t_g_wzd_color_cho_sig_frame_bk;
GL_COLOR_T      t_g_wzd_color_cho_sig_txt_bk;
GL_COLOR_T      t_g_wzd_color_tv_setup_txt_nor;
GL_COLOR_T      t_g_wzd_color_tv_setup_txt_hlt;
GL_COLOR_T      t_g_wzd_color_tv_setup_lb_nor;
GL_COLOR_T      t_g_wzd_color_tv_setup_lb_hlt;
GL_COLOR_T      t_g_wzd_color_begin_txt;

GL_COLOR_T      t_g_wzd_color_scan_txt_bk;
GL_COLOR_T      t_g_wzd_color_scan_txt;

/* Footer */
GL_COLOR_T      t_g_wzd_color_footer_hlt_txt;
GL_COLOR_T      t_g_wzd_color_footer_enable_txt;
GL_COLOR_T      t_g_wzd_color_footer_disable_txt;

/* Select box */
GL_COLOR_T		t_g_wzd_color_sel_box_hlt_txt;
GL_COLOR_T		t_g_wzd_color_sel_box_enable_txt;
GL_COLOR_T		t_g_wzd_color_sel_box_disable_txt;

/* Edit box */
GL_COLOR_T      t_g_wzd_color_edt_hlt_txt;
GL_COLOR_T      t_g_wzd_color_edt_enable_txt;

GL_COLOR_T      t_g_wzd_color_cho_mode_txt_bg;
GL_COLOR_T      t_g_wzd_color_cho_mode_txt_wihte;
GL_COLOR_T      t_g_wzd_color_cho_mode_txt_gray;

/* color definitions */   
static const GL_COLOR_T COLOR_TRANS      = {   0, {   0 }, {   0 }, {   0 } }; /* fully transparent */
#if !(defined(APP_COLOR_MODE_PALLET))
static const GL_COLOR_T COLOR_WHITE      = { 255, { 255 }, { 255 }, { 255 } }; /* white color */
static const GL_COLOR_T COLOR_BLACK      = { 255, {   0 }, {   0 }, {   0 } }; /* black color */
static const GL_COLOR_T COLOR_HL         = { 255, { 240 }, { 240 }, {  90 } }; /* text highlight color */
static const GL_COLOR_T COLOR_TXT_HL     = { 255, { 255 }, { 200 }, { 100 } }; /* text highlight color */
static const GL_COLOR_T COLOR_DARK_BLUE  = { 255, {  31 }, {  49 }, {  99 } }; /* dark blue color */
static const GL_COLOR_T COLOR_LIGHT_BLUE = { 255, {  35 }, {  56 }, { 115 } }; /* light blue color */
static const GL_COLOR_T COLOR_HALF_GRAY  = { 255, {  200}, { 200 }, { 200 } }; /* Light Gray color */
static const GL_COLOR_T COLOR_GRAY       = { 255, {  150}, { 150 }, { 150 } }; /* Gray color */
static const GL_COLOR_T COLOR_DARK_GRAY  = { 255, {  51},  { 51 },  { 51 } };  /* Dark Gray color */
#else
   static const GL_COLOR_T COLOR_WHITE      = { 255, {   0 }, {   0 }, { 220 } }; /* white color */
   static const GL_COLOR_T COLOR_BLACK      = { 255, {   0 }, {   0 }, {   1 } }; /* black color */
   static const GL_COLOR_T COLOR_HL         = { 255, {   0 }, {   0 }, {  63 } }; /* text highlight color */
   static const GL_COLOR_T COLOR_TXT_HL     = { 255, {   0 }, {   0 }, {  61 } }; /* text highlight color */
   static const GL_COLOR_T COLOR_DARK_BLUE  = { 255, {   0 }, {   0 }, { 0 } }; /* dark blue color */
   static const GL_COLOR_T COLOR_LIGHT_BLUE = { 255, {   0 }, {   0 }, { 0 } }; /* light blue color */
#endif
/*----------------------------------------------------------------------------
 * Name: wzd_color_init
 *
 * Description: Initiate colors for Wizard application.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 0                   Successful
 *          Any other valuse    Failed
 ----------------------------------------------------------------------------*/
INT32 wzd_color_init (VOID)
{
    /* Main frame. */
    t_g_wzd_color_main_frm_bk                      = COLOR_BLACK;

    /* Base map frame. */
    t_g_wzd_color_base_frm_bk                      = COLOR_TRANS;

#ifdef APP_IMG_UI
    t_g_wzd_color_base_frm_bk                      = COLOR_TRANS;
#endif 

    /* Layout frame. */
    t_g_wzd_color_layout_frm_bk                    = COLOR_LIGHT_BLUE;

#ifdef APP_IMG_UI
    t_g_wzd_color_layout_frm_bk                    = COLOR_TRANS;
#endif 

    /* Title list. */
    t_g_wzd_color_title_lst_bk                     = COLOR_LIGHT_BLUE;
    t_g_wzd_color_title_lst_vp                     = COLOR_TRANS;
    t_g_wzd_color_title_lst_elem_bk                = COLOR_TRANS;
    t_g_wzd_color_title_lst_elem_hlt_bk            = COLOR_TRANS;
    t_g_wzd_color_title_lst_elem_hlt_uf_bk         = COLOR_TRANS;
    t_g_wzd_color_title_lst_col_bk                 = COLOR_TRANS;
    t_g_wzd_color_title_lst_col_txt                = COLOR_WHITE;
    t_g_wzd_color_title_lst_col_hlt_txt            = COLOR_WHITE;
    t_g_wzd_color_title_lst_col_hlt_uf_txt         = COLOR_WHITE;


    /* Setting list */
    t_g_wzd_color_seti_lst_bk                      = COLOR_TRANS;
    t_g_wzd_color_seti_lst_vp                      = COLOR_LIGHT_BLUE;
    t_g_wzd_color_seti_lst_elem_bk                 = COLOR_LIGHT_BLUE;

#ifdef APP_IMG_UI
    t_g_wzd_color_seti_lst_vp                      = COLOR_TRANS;
    t_g_wzd_color_seti_lst_elem_bk                 = COLOR_TRANS;
#endif 

    t_g_wzd_color_seti_lst_elem_hlt_bk             = COLOR_HL;
    t_g_wzd_color_seti_lst_elem_hlt_uf_bk          = COLOR_LIGHT_BLUE;
    t_g_wzd_color_seti_lst_col_bk                  = COLOR_TRANS; 
    t_g_wzd_color_seti_lst_col_txt                 = COLOR_WHITE;
    t_g_wzd_color_seti_lst_col_hlt_txt             = COLOR_WHITE;
    t_g_wzd_color_seti_lst_col_hlt_uf_txt          = COLOR_TXT_HL;
    t_g_wzd_color_seti_lst_col_dis_txt             = COLOR_GRAY;

    /* Help list. */
    t_g_wzd_color_help_lst_bk                      = COLOR_BLACK;
    t_g_wzd_color_help_lst_vp                      = COLOR_TRANS;
    t_g_wzd_color_help_lst_elem_bk                 = COLOR_TRANS;
    t_g_wzd_color_help_lst_elem_hlt_bk             = COLOR_TRANS;
    t_g_wzd_color_help_lst_elem_hlt_uf_bk          = COLOR_TRANS;
    t_g_wzd_color_help_lst_col_bk                  = COLOR_TRANS;
    t_g_wzd_color_help_lst_col_back_txt            = COLOR_WHITE;
    t_g_wzd_color_help_lst_col_back_hlt_txt        = COLOR_WHITE;
    t_g_wzd_color_help_lst_col_back_hlt_uf_txt     = COLOR_WHITE;
    t_g_wzd_color_help_lst_col_select_txt          = COLOR_WHITE;
    t_g_wzd_color_help_lst_col_select_hlt_txt      = COLOR_WHITE;
    t_g_wzd_color_help_lst_col_select_hlt_uf_txt   = COLOR_WHITE;
    t_g_wzd_color_help_lst_col_enter_txt           = COLOR_WHITE;
    t_g_wzd_color_help_lst_col_enter_hlt_txt       = COLOR_WHITE;
    t_g_wzd_color_help_lst_col_enter_hlt_uf_txt    = COLOR_WHITE;
    t_g_wzd_color_help_lst_col_exit_txt            = COLOR_WHITE;
    t_g_wzd_color_help_lst_col_exit_hlt_txt        = COLOR_WHITE;
    t_g_wzd_color_help_lst_col_exit_hlt_uf_txt     = COLOR_WHITE;

	/* Title text. */
    t_g_wzd_color_title_txt_bk                 	   = COLOR_TRANS;
    t_g_wzd_color_title_txt_nor                    = COLOR_GRAY;
    t_g_wzd_color_title_txt_hlt                    = COLOR_WHITE;

    /* Description text. */
    t_g_wzd_color_desc_txt_bk                      = COLOR_TRANS;
    t_g_wzd_color_desc_txt                         = COLOR_WHITE;

    /* Scan progress bar. */
    t_g_wzd_color_scan_bar_txt                     = COLOR_WHITE;

    /* Footer color */
    t_g_wzd_color_footer_txt                       = COLOR_WHITE;

    t_g_wzd_color_dlg_txt                          = COLOR_WHITE;
	t_g_wzd_color_dlg_desc_txt                     = COLOR_GRAY;

    /* Network Base Frame. */
    t_g_wzd_color_network_frame_bk                 = COLOR_TRANS;
    t_g_wzd_color_network_txt_nor                  = COLOR_GRAY;
    t_g_wzd_color_network_txt_hlt                  = COLOR_WHITE;

    /* TV Setup */
    t_g_wzd_color_cho_sig_frame_bk                 = COLOR_TRANS;
    t_g_wzd_color_cho_sig_txt_bk                   = COLOR_TRANS;
    t_g_wzd_color_tv_setup_txt_nor                 = COLOR_HALF_GRAY;
    t_g_wzd_color_tv_setup_txt_hlt                 = COLOR_WHITE;
    t_g_wzd_color_tv_setup_lb_nor                  = COLOR_GRAY;
    t_g_wzd_color_tv_setup_lb_hlt                  = COLOR_WHITE;
    t_g_wzd_color_begin_txt                        = COLOR_WHITE;

    t_g_wzd_color_scan_txt_bk                      = COLOR_TRANS;
    t_g_wzd_color_scan_txt                         = COLOR_WHITE;

    t_g_wzd_color_footer_hlt_txt                   = COLOR_WHITE;
    t_g_wzd_color_footer_enable_txt                = COLOR_WHITE;
    t_g_wzd_color_footer_disable_txt               = COLOR_GRAY;

	t_g_wzd_color_sel_box_hlt_txt       		   = COLOR_WHITE;
    t_g_wzd_color_sel_box_enable_txt               = COLOR_DARK_GRAY;
    t_g_wzd_color_sel_box_disable_txt              = COLOR_GRAY;

    t_g_wzd_color_edt_hlt_txt                      = COLOR_WHITE;
    t_g_wzd_color_edt_enable_txt                   = COLOR_WHITE;

    t_g_wzd_color_cho_mode_txt_bg                  = COLOR_TRANS;
    t_g_wzd_color_cho_mode_txt_wihte               = COLOR_WHITE;
    t_g_wzd_color_cho_mode_txt_gray                = COLOR_GRAY;

    return  0;
}


