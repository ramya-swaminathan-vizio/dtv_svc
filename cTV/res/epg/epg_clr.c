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
 * $RCSfile: epg_clr.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/15 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: f52e6eab4b8f188db6b5557a2ccdae2c $
 *
 * Description:
 *      This file defines the color used by the EPG application.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "res/epg/epg_clr.h"
#include "res/epg/epg_cfg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/

/* main frame */
GL_COLOR_T t_g_epg_color_main_frm_bk;

/* base map frame */
GL_COLOR_T t_g_epg_color_base_frm_bk;

/* description background frame */
GL_COLOR_T t_g_epg_color_desc_bk_frm_bk;

/* description frame */
GL_COLOR_T t_g_epg_color_desc_frm_bk;

/* video frame */
GL_COLOR_T t_g_epg_color_video_frm_bk;

/* password frame */
GL_COLOR_T t_g_epg_color_passwd_frm_bk;

/* channel list */
GL_COLOR_T t_g_epg_color_chn_lst_bk;
GL_COLOR_T t_g_epg_color_chn_lst_vp;
GL_COLOR_T t_g_epg_color_chn_lst_elem_bk;
GL_COLOR_T t_g_epg_color_chn_lst_elem_hlt_bk;
GL_COLOR_T t_g_epg_color_chn_lst_elem_hlt_uf_bk;
GL_COLOR_T t_g_epg_color_chn_lst_col_bk;
GL_COLOR_T t_g_epg_color_chn_lst_col_prev_txt;
GL_COLOR_T t_g_epg_color_chn_lst_col_prev_hlt_txt;
GL_COLOR_T t_g_epg_color_chn_lst_col_prev_hlt_uf_txt;
GL_COLOR_T t_g_epg_color_chn_lst_col_crnt_txt;
GL_COLOR_T t_g_epg_color_chn_lst_col_crnt_hlt_txt;
GL_COLOR_T t_g_epg_color_chn_lst_col_crnt_hlt_uf_txt;
GL_COLOR_T t_g_epg_color_chn_lst_col_next_txt;
GL_COLOR_T t_g_epg_color_chn_lst_col_next_hlt_txt;
GL_COLOR_T t_g_epg_color_chn_lst_col_next_hlt_uf_txt;

/* program list */
GL_COLOR_T t_g_epg_color_prg_lst_bdr;
GL_COLOR_T t_g_epg_color_prg_lst_bdr_hlt;
GL_COLOR_T t_g_epg_color_prg_lst_bk;
GL_COLOR_T t_g_epg_color_prg_lst_vp;
GL_COLOR_T t_g_epg_color_prg_lst_elem_bk;
GL_COLOR_T t_g_epg_color_prg_lst_elem_hlt_bk;
GL_COLOR_T t_g_epg_color_prg_lst_elem_hlt_uf_bk;
GL_COLOR_T t_g_epg_color_prg_lst_title_txt;
GL_COLOR_T t_g_epg_color_prg_lst_title_hlt_txt;
GL_COLOR_T t_g_epg_color_prg_lst_col_bk;
GL_COLOR_T t_g_epg_color_prg_lst_col_date_txt;
GL_COLOR_T t_g_epg_color_prg_lst_col_date_hlt_txt;
GL_COLOR_T t_g_epg_color_prg_lst_col_date_hlt_uf_txt;
GL_COLOR_T t_g_epg_color_prg_lst_col_time_txt;
GL_COLOR_T t_g_epg_color_prg_lst_col_time_hlt_txt;
GL_COLOR_T t_g_epg_color_prg_lst_col_time_hlt_uf_txt;
GL_COLOR_T t_g_epg_color_prg_lst_col_title_txt;
GL_COLOR_T t_g_epg_color_prg_lst_col_title_hlt_txt;
GL_COLOR_T t_g_epg_color_prg_lst_col_title_hlt_uf_txt;

/* surfing list */
GL_COLOR_T t_g_epg_color_surf_lst_bdr;
GL_COLOR_T t_g_epg_color_surf_lst_bdr_hlt;
GL_COLOR_T t_g_epg_color_surf_lst_bk;
GL_COLOR_T t_g_epg_color_surf_lst_vp;
GL_COLOR_T t_g_epg_color_surf_lst_elem_bk;
GL_COLOR_T t_g_epg_color_surf_lst_elem_hlt_bk;
GL_COLOR_T t_g_epg_color_surf_lst_elem_hlt_uf_bk;
GL_COLOR_T t_g_epg_color_surf_lst_title_txt;
GL_COLOR_T t_g_epg_color_surf_lst_title_hlt_txt;
GL_COLOR_T t_g_epg_color_surf_lst_col_bk;
GL_COLOR_T t_g_epg_color_surf_lst_col_no_txt;
GL_COLOR_T t_g_epg_color_surf_lst_col_no_hlt_txt;
GL_COLOR_T t_g_epg_color_surf_lst_col_no_hlt_uf_txt;
GL_COLOR_T t_g_epg_color_surf_lst_col_name_txt;
GL_COLOR_T t_g_epg_color_surf_lst_col_name_hlt_txt;
GL_COLOR_T t_g_epg_color_surf_lst_col_name_hlt_uf_txt;

/* description list */
GL_COLOR_T t_g_epg_color_desc_lst_bk;
GL_COLOR_T t_g_epg_color_desc_lst_vp;
GL_COLOR_T t_g_epg_color_desc_lst_elem_bk;
GL_COLOR_T t_g_epg_color_desc_lst_elem_hlt_bk;
GL_COLOR_T t_g_epg_color_desc_lst_elem_hlt_uf_bk;
GL_COLOR_T t_g_epg_color_desc_lst_col_bk;
GL_COLOR_T t_g_epg_color_desc_lst_col_time_txt;
GL_COLOR_T t_g_epg_color_desc_lst_col_time_hlt_txt;
GL_COLOR_T t_g_epg_color_desc_lst_col_time_hlt_uf_txt;
GL_COLOR_T t_g_epg_color_desc_lst_col_ca_txt;
GL_COLOR_T t_g_epg_color_desc_lst_col_ca_hlt_txt;
GL_COLOR_T t_g_epg_color_desc_lst_col_ca_hlt_uf_txt;

/* icon list */
GL_COLOR_T t_g_epg_color_icon_lst_bk;
GL_COLOR_T t_g_epg_color_icon_lst_vp;
GL_COLOR_T t_g_epg_color_icon_lst_elem_bk;
GL_COLOR_T t_g_epg_color_icon_lst_elem_hlt_bk;
GL_COLOR_T t_g_epg_color_icon_lst_elem_hlt_uf_bk;
GL_COLOR_T t_g_epg_color_icon_lst_col_bk;

/* help list */
GL_COLOR_T t_g_epg_color_help_lst_bk;
GL_COLOR_T t_g_epg_color_help_lst_vp;
GL_COLOR_T t_g_epg_color_help_lst_elem_bk;
GL_COLOR_T t_g_epg_color_help_lst_elem_hlt_bk;
GL_COLOR_T t_g_epg_color_help_lst_elem_hlt_uf_bk;
GL_COLOR_T t_g_epg_color_help_lst_col_bk;
GL_COLOR_T t_g_epg_color_help_lst_col_prev_txt;
GL_COLOR_T t_g_epg_color_help_lst_col_prev_hlt_txt;
GL_COLOR_T t_g_epg_color_help_lst_col_prev_hlt_uf_txt;
GL_COLOR_T t_g_epg_color_help_lst_col_next_txt;
GL_COLOR_T t_g_epg_color_help_lst_col_next_hlt_txt;
GL_COLOR_T t_g_epg_color_help_lst_col_next_hlt_uf_txt;
GL_COLOR_T t_g_epg_color_help_lst_col_up_txt;
GL_COLOR_T t_g_epg_color_help_lst_col_up_hlt_txt;
GL_COLOR_T t_g_epg_color_help_lst_col_up_hlt_uf_txt;
GL_COLOR_T t_g_epg_color_help_lst_col_down_txt;
GL_COLOR_T t_g_epg_color_help_lst_col_down_hlt_txt;
GL_COLOR_T t_g_epg_color_help_lst_col_down_hlt_uf_txt;

/* program text */
GL_COLOR_T t_g_epg_color_prg_txt_bk;
GL_COLOR_T t_g_epg_color_prg_txt;

/* time text */
GL_COLOR_T t_g_epg_color_time_txt_bk;
GL_COLOR_T t_g_epg_color_time_txt;

/* video text */
GL_COLOR_T t_g_epg_color_video_txt_bk;
GL_COLOR_T t_g_epg_color_video_txt;

/* description text */
GL_COLOR_T t_g_epg_color_desc_txt_bk;
GL_COLOR_T t_g_epg_color_desc_txt;

/* page text */
GL_COLOR_T t_g_epg_color_page_txt_bk;
GL_COLOR_T t_g_epg_color_page_txt;

/* channel info text */
GL_COLOR_T t_g_epg_color_chn_txt_bk;
GL_COLOR_T t_g_epg_color_chn_txt;

/* direct channel input text */
GL_COLOR_T t_g_epg_color_dci_txt_bk;
GL_COLOR_T t_g_epg_color_dci_txt;
GL_COLOR_T t_g_epg_color_dci_txt_dummy;

/* retrieving icon */
GL_COLOR_T t_g_epg_color_retrieve_icon_bk;

/* retrieving text */
GL_COLOR_T t_g_epg_color_retrieve_txt_bk;
GL_COLOR_T t_g_epg_color_retrieve_txt;

/* password text */
GL_COLOR_T t_g_epg_color_passwd_txt_bk;
GL_COLOR_T t_g_epg_color_passwd_txt;

/* password edit box */
GL_COLOR_T t_g_epg_color_passwd_edit_bdr_bk;
GL_COLOR_T t_g_epg_color_passwd_edit_cnt_bk;
GL_COLOR_T t_g_epg_color_passwd_edit_txt;
GL_COLOR_T t_g_epg_color_passwd_edit_txt_hlt;

#ifdef APP_DVBT_SUPPORT

/* type list */
GL_COLOR_T t_g_epg_color_type_lst_bk;
GL_COLOR_T t_g_epg_color_type_lst_vp;
GL_COLOR_T t_g_epg_color_type_lst_elem_bk;
GL_COLOR_T t_g_epg_color_type_lst_elem_hlt_bk;
GL_COLOR_T t_g_epg_color_type_lst_elem_hlt_uf_bk;
GL_COLOR_T t_g_epg_color_type_lst_col_bk;
GL_COLOR_T t_g_epg_color_type_lst_col_txt;
GL_COLOR_T t_g_epg_color_type_lst_col_hlt_txt;
GL_COLOR_T t_g_epg_color_type_lst_col_hlt_uf_txt;
GL_COLOR_T t_g_epg_color_type_lst_title_txt;
GL_COLOR_T t_g_epg_color_type_lst_title_hlt_txt;

/* subtype list */
GL_COLOR_T t_g_epg_color_subtype_lst_bk;
GL_COLOR_T t_g_epg_color_subtype_lst_vp;
GL_COLOR_T t_g_epg_color_subtype_lst_elem_bk;
GL_COLOR_T t_g_epg_color_subtype_lst_elem_hlt_bk;
GL_COLOR_T t_g_epg_color_subtype_lst_elem_hlt_uf_bk;
GL_COLOR_T t_g_epg_color_subtype_lst_col_bk;
GL_COLOR_T t_g_epg_color_subtype_lst_col_txt;
GL_COLOR_T t_g_epg_color_subtype_lst_col_hlt_txt;
GL_COLOR_T t_g_epg_color_subtype_lst_col_hlt_uf_txt;
GL_COLOR_T t_g_epg_color_subtype_lst_title_txt;
GL_COLOR_T t_g_epg_color_subtype_lst_title_hlt_txt;

#endif /* APP_DVBT_SUPPORT */

/* color definitions */
static const GL_COLOR_T COLOR_TRANS = {   0, {	 0 }, {   0 }, {   0 } }; /* fully transparent */
static const GL_COLOR_T COLOR_WHITE = { 255, { 255 }, { 255 }, { 255 } }; /* white color */
static const GL_COLOR_T COLOR_YELLOW ={ 255, { 255}, { 200}, { 100}};  /* yellow color */
static const GL_COLOR_T COLOR_BLUE1  = { 255, { 51 }, { 102 }, { 153 } }; /* light blue color */
static const GL_COLOR_T COLOR_ORANGE  = { 255, { 245 }, { 149 }, { 29 } }; /* orange color */	

/*----------------------------------------------------------------------------
 * Name: epg_color_init
 *
 * Description: This API initiates the colors of EPG.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 0                   Successful
 *          Any other valuse    Failed
 ----------------------------------------------------------------------------*/
INT32 epg_color_init (VOID)
{
    /*
       Main frame .
    */
    t_g_epg_color_main_frm_bk                      = COLOR_TRANS;


    /*
       Base map frame.
    */
    t_g_epg_color_base_frm_bk                      = COLOR_TRANS;


    /*
       Description background frame.
    */
    t_g_epg_color_desc_bk_frm_bk                   = COLOR_TRANS;


    /*
       Description frame.
    */
    t_g_epg_color_desc_frm_bk                      = COLOR_TRANS;


    /*
       Video frame.
    */
    t_g_epg_color_video_frm_bk                     = COLOR_TRANS;


    /*
       Password frame.
    */
    t_g_epg_color_passwd_frm_bk                    = COLOR_TRANS;


    /*
       Channel list.
    */
    t_g_epg_color_chn_lst_bk                       = COLOR_TRANS;
    t_g_epg_color_chn_lst_vp                       = COLOR_TRANS;
    t_g_epg_color_chn_lst_col_bk                   = COLOR_TRANS;
    t_g_epg_color_chn_lst_elem_bk                  = COLOR_TRANS;
    t_g_epg_color_chn_lst_elem_hlt_bk              = COLOR_TRANS;
    t_g_epg_color_chn_lst_elem_hlt_uf_bk           = COLOR_TRANS;
    t_g_epg_color_chn_lst_col_prev_txt             = COLOR_WHITE;
    t_g_epg_color_chn_lst_col_prev_hlt_txt         = COLOR_WHITE;
    t_g_epg_color_chn_lst_col_prev_hlt_uf_txt      = COLOR_WHITE;
    t_g_epg_color_chn_lst_col_crnt_txt             = COLOR_WHITE; /*COLOR_BLUE1;*/
    t_g_epg_color_chn_lst_col_crnt_hlt_txt         = COLOR_WHITE; /*COLOR_BLUE1;*/
    t_g_epg_color_chn_lst_col_crnt_hlt_uf_txt      = COLOR_WHITE; /*COLOR_BLUE1;*/
    t_g_epg_color_chn_lst_col_next_txt             = COLOR_WHITE;
    t_g_epg_color_chn_lst_col_next_hlt_txt         = COLOR_WHITE;
    t_g_epg_color_chn_lst_col_next_hlt_uf_txt      = COLOR_WHITE;


    /*
       Program list.
    */
    t_g_epg_color_prg_lst_bdr                      = COLOR_TRANS;
    t_g_epg_color_prg_lst_bdr_hlt                  = COLOR_TRANS;
    t_g_epg_color_prg_lst_bk                       = COLOR_TRANS;
    t_g_epg_color_prg_lst_vp                       = COLOR_TRANS;
    t_g_epg_color_prg_lst_elem_bk                  = COLOR_TRANS;
    t_g_epg_color_prg_lst_elem_hlt_bk              = COLOR_TRANS;
    t_g_epg_color_prg_lst_elem_hlt_uf_bk           = COLOR_TRANS;
    t_g_epg_color_prg_lst_title_txt                = COLOR_TRANS;
    t_g_epg_color_prg_lst_title_hlt_txt            = COLOR_TRANS;
    t_g_epg_color_prg_lst_col_bk                   = COLOR_TRANS;
    t_g_epg_color_prg_lst_col_date_txt             = COLOR_WHITE;
    t_g_epg_color_prg_lst_col_date_hlt_txt         = COLOR_WHITE;
    t_g_epg_color_prg_lst_col_date_hlt_uf_txt      = COLOR_WHITE;
    t_g_epg_color_prg_lst_col_time_txt             = COLOR_WHITE;
    t_g_epg_color_prg_lst_col_time_hlt_txt         = COLOR_WHITE;
    t_g_epg_color_prg_lst_col_time_hlt_uf_txt      = COLOR_WHITE;
    t_g_epg_color_prg_lst_col_title_txt            = COLOR_WHITE;
    t_g_epg_color_prg_lst_col_title_hlt_txt        = COLOR_WHITE;
    t_g_epg_color_prg_lst_col_title_hlt_uf_txt     = COLOR_WHITE;


    /*
       Surfing list.
    */
    t_g_epg_color_surf_lst_bdr                     = COLOR_TRANS;
    t_g_epg_color_surf_lst_bdr_hlt                 = COLOR_TRANS;
    t_g_epg_color_surf_lst_bk                      = COLOR_TRANS;
    t_g_epg_color_surf_lst_vp                      = COLOR_TRANS;
    t_g_epg_color_surf_lst_elem_bk                 = COLOR_TRANS;
    t_g_epg_color_surf_lst_elem_hlt_bk             = COLOR_TRANS;
    t_g_epg_color_surf_lst_elem_hlt_uf_bk          = COLOR_TRANS;
    t_g_epg_color_surf_lst_title_txt               = COLOR_WHITE;
    t_g_epg_color_surf_lst_title_hlt_txt           = COLOR_WHITE;
    t_g_epg_color_surf_lst_col_bk                  = COLOR_TRANS;
    t_g_epg_color_surf_lst_col_no_txt              = COLOR_ORANGE;
    t_g_epg_color_surf_lst_col_no_hlt_txt          = COLOR_WHITE;
    t_g_epg_color_surf_lst_col_no_hlt_uf_txt       = COLOR_WHITE;
    t_g_epg_color_surf_lst_col_name_txt            = COLOR_ORANGE;
    t_g_epg_color_surf_lst_col_name_hlt_txt        = COLOR_WHITE;
    t_g_epg_color_surf_lst_col_name_hlt_uf_txt     = COLOR_WHITE;

    /*
       Description list.
    */
    t_g_epg_color_desc_lst_bk                      = COLOR_TRANS;
    t_g_epg_color_desc_lst_vp                      = COLOR_TRANS;
    t_g_epg_color_desc_lst_elem_bk                 = COLOR_TRANS;
    t_g_epg_color_desc_lst_elem_hlt_bk             = COLOR_TRANS;
    t_g_epg_color_desc_lst_elem_hlt_uf_bk          = COLOR_TRANS;
    t_g_epg_color_desc_lst_col_bk                  = COLOR_TRANS;
    t_g_epg_color_desc_lst_col_time_txt            = COLOR_BLUE1; 
    t_g_epg_color_desc_lst_col_time_hlt_txt        = COLOR_BLUE1; 
    t_g_epg_color_desc_lst_col_time_hlt_uf_txt     = COLOR_BLUE1; 
    t_g_epg_color_desc_lst_col_ca_txt              = COLOR_BLUE1; 
    t_g_epg_color_desc_lst_col_ca_hlt_txt          = COLOR_BLUE1; 
    t_g_epg_color_desc_lst_col_ca_hlt_uf_txt       = COLOR_BLUE1; 


    /*
       Icon list.
    */
    t_g_epg_color_icon_lst_bk                      = COLOR_TRANS;
    t_g_epg_color_icon_lst_vp                      = COLOR_TRANS;
    t_g_epg_color_icon_lst_elem_bk                 = COLOR_TRANS;
    t_g_epg_color_icon_lst_elem_hlt_bk             = COLOR_TRANS;
    t_g_epg_color_icon_lst_elem_hlt_uf_bk          = COLOR_TRANS;
    t_g_epg_color_icon_lst_col_bk                  = COLOR_TRANS;


    /*
       Help list.
    */
    t_g_epg_color_help_lst_bk                      = COLOR_TRANS;
    t_g_epg_color_help_lst_vp                      = COLOR_TRANS;
    t_g_epg_color_help_lst_col_bk                  = COLOR_TRANS;
    t_g_epg_color_help_lst_elem_bk                 = COLOR_TRANS;
    t_g_epg_color_help_lst_elem_hlt_bk             = COLOR_TRANS;
    t_g_epg_color_help_lst_elem_hlt_uf_bk          = COLOR_TRANS;
    t_g_epg_color_help_lst_col_prev_txt            = COLOR_WHITE;
    t_g_epg_color_help_lst_col_prev_hlt_txt        = COLOR_WHITE;
    t_g_epg_color_help_lst_col_prev_hlt_uf_txt     = COLOR_WHITE;
    t_g_epg_color_help_lst_col_next_txt            = COLOR_WHITE;
    t_g_epg_color_help_lst_col_next_hlt_txt        = COLOR_WHITE;
    t_g_epg_color_help_lst_col_next_hlt_uf_txt     = COLOR_WHITE;
    t_g_epg_color_help_lst_col_up_txt              = COLOR_WHITE;
    t_g_epg_color_help_lst_col_up_hlt_txt          = COLOR_WHITE;
    t_g_epg_color_help_lst_col_up_hlt_uf_txt       = COLOR_WHITE;
    t_g_epg_color_help_lst_col_down_txt            = COLOR_WHITE;
    t_g_epg_color_help_lst_col_down_hlt_txt        = COLOR_WHITE;
    t_g_epg_color_help_lst_col_down_hlt_uf_txt     = COLOR_WHITE;


    /*
       Time text.
    */
    t_g_epg_color_time_txt_bk                      = COLOR_TRANS;
    t_g_epg_color_time_txt                         = COLOR_WHITE;


    /*
       Program text.
    */
    t_g_epg_color_prg_txt_bk                       = COLOR_TRANS;
    t_g_epg_color_prg_txt                          = COLOR_WHITE;


    /*
       Video text.
    */
#ifdef APP_EPG_FULL_VIDEO
    t_g_epg_color_video_txt_bk                     = COLOR_TRANS;
#else
    t_g_epg_color_video_txt_bk                     = COLOR_TRANS;
#endif
    t_g_epg_color_video_txt                        = COLOR_WHITE;


    /*
       Description text.
    */
    t_g_epg_color_desc_txt_bk                      = COLOR_TRANS;
    t_g_epg_color_desc_txt                         = COLOR_WHITE;  


    /*
       Page text.
    */
    t_g_epg_color_page_txt_bk                      = COLOR_TRANS;
    t_g_epg_color_page_txt                         = COLOR_WHITE;


    /*
       Channel info text.
    */
    t_g_epg_color_chn_txt_bk                       = COLOR_TRANS;
    t_g_epg_color_chn_txt                          = COLOR_TRANS;


    /*
       Direct channel input text.
    */
    t_g_epg_color_dci_txt_bk                       = COLOR_TRANS;
    t_g_epg_color_dci_txt                          = COLOR_WHITE;
    t_g_epg_color_dci_txt_dummy                    = COLOR_WHITE;


    /*
       Retrieving icon.
    */
    t_g_epg_color_retrieve_icon_bk                 = COLOR_TRANS;


    /*
       Retrieving text.
    */
    t_g_epg_color_retrieve_txt_bk                  = COLOR_TRANS;
    t_g_epg_color_retrieve_txt                     = COLOR_TRANS;


    /*
       Password text.
    */
    t_g_epg_color_passwd_txt_bk                    = COLOR_TRANS;
    t_g_epg_color_passwd_txt                       = COLOR_WHITE;


    /*
       Password edit.
    */
    t_g_epg_color_passwd_edit_bdr_bk               = COLOR_TRANS;
    t_g_epg_color_passwd_edit_cnt_bk               = COLOR_TRANS;
    t_g_epg_color_passwd_edit_txt                  = COLOR_WHITE;
    t_g_epg_color_passwd_edit_txt_hlt              = COLOR_WHITE;

#ifdef APP_DVBT_SUPPORT

    /*
       Type list.
    */
    t_g_epg_color_type_lst_bk                      = COLOR_TRANS;
    t_g_epg_color_type_lst_vp                      = COLOR_TRANS;
    t_g_epg_color_type_lst_elem_bk                 = COLOR_TRANS;
    t_g_epg_color_type_lst_elem_hlt_bk             = COLOR_TRANS;
    t_g_epg_color_type_lst_elem_hlt_uf_bk          = COLOR_TRANS;
    t_g_epg_color_type_lst_col_bk                  = COLOR_TRANS;
    t_g_epg_color_type_lst_col_txt                 = COLOR_WHITE;
    t_g_epg_color_type_lst_col_hlt_txt             = COLOR_WHITE;
    t_g_epg_color_type_lst_col_hlt_uf_txt          = COLOR_WHITE;
    t_g_epg_color_type_lst_title_txt               = COLOR_WHITE;
    t_g_epg_color_type_lst_title_hlt_txt           = COLOR_WHITE;


    /*
       Subtype list.
    */
    t_g_epg_color_subtype_lst_bk                   = COLOR_TRANS;
    t_g_epg_color_subtype_lst_vp                   = COLOR_TRANS;
    t_g_epg_color_subtype_lst_elem_bk              = COLOR_TRANS;
    t_g_epg_color_subtype_lst_elem_hlt_bk          = COLOR_TRANS;
    t_g_epg_color_subtype_lst_elem_hlt_uf_bk       = COLOR_TRANS;
    t_g_epg_color_subtype_lst_col_bk               = COLOR_TRANS;
    t_g_epg_color_subtype_lst_col_txt              = COLOR_WHITE;
    t_g_epg_color_subtype_lst_col_hlt_txt          = COLOR_WHITE;
    t_g_epg_color_subtype_lst_col_hlt_uf_txt       = COLOR_WHITE;
    t_g_epg_color_subtype_lst_title_txt            = COLOR_WHITE;
    t_g_epg_color_subtype_lst_title_hlt_txt        = COLOR_WHITE;

#endif /* APP_DVBT_SUPPORT */

    return  0;
}


