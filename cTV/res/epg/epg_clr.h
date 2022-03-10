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
 * $RCSfile: epg_clr.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/11 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: d86d704b96b676ace4198ef41405b049 $
 *
 * Description:
 *      This file defines the colors used by the EPG application.
 *---------------------------------------------------------------------------*/
#ifndef _EPG_COLOR_H_
#define _EPG_COLOR_H_

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

/*
   Main frame.
*/
extern GL_COLOR_T t_g_epg_color_main_frm_bk;


/*
   Base map frame.
*/
extern GL_COLOR_T t_g_epg_color_base_frm_bk;


/*
   Description background frame.
*/
extern GL_COLOR_T t_g_epg_color_desc_bk_frm_bk;


/*
   Description frame.
*/
extern GL_COLOR_T t_g_epg_color_desc_frm_bk;


/*
   Video frame.
*/
extern GL_COLOR_T t_g_epg_color_video_frm_bk;


/*
   Password frame.
*/
extern GL_COLOR_T t_g_epg_color_passwd_frm_bk;


/*
   Channel list.
*/
extern GL_COLOR_T t_g_epg_color_chn_lst_bk;
extern GL_COLOR_T t_g_epg_color_chn_lst_vp;
extern GL_COLOR_T t_g_epg_color_chn_lst_elem_bk;
extern GL_COLOR_T t_g_epg_color_chn_lst_elem_hlt_bk;
extern GL_COLOR_T t_g_epg_color_chn_lst_elem_hlt_uf_bk;
extern GL_COLOR_T t_g_epg_color_chn_lst_col_bk;
extern GL_COLOR_T t_g_epg_color_chn_lst_col_prev_txt;
extern GL_COLOR_T t_g_epg_color_chn_lst_col_prev_hlt_txt;
extern GL_COLOR_T t_g_epg_color_chn_lst_col_prev_hlt_uf_txt;
extern GL_COLOR_T t_g_epg_color_chn_lst_col_crnt_txt;
extern GL_COLOR_T t_g_epg_color_chn_lst_col_crnt_hlt_txt;
extern GL_COLOR_T t_g_epg_color_chn_lst_col_crnt_hlt_uf_txt;
extern GL_COLOR_T t_g_epg_color_chn_lst_col_next_txt;
extern GL_COLOR_T t_g_epg_color_chn_lst_col_next_hlt_txt;
extern GL_COLOR_T t_g_epg_color_chn_lst_col_next_hlt_uf_txt;


/*
   Program list.
*/
extern GL_COLOR_T t_g_epg_color_prg_lst_bdr;
extern GL_COLOR_T t_g_epg_color_prg_lst_bdr_hlt;
extern GL_COLOR_T t_g_epg_color_prg_lst_bk;
extern GL_COLOR_T t_g_epg_color_prg_lst_vp;
extern GL_COLOR_T t_g_epg_color_prg_lst_elem_bk;
extern GL_COLOR_T t_g_epg_color_prg_lst_elem_hlt_bk;
extern GL_COLOR_T t_g_epg_color_prg_lst_elem_hlt_uf_bk;
extern GL_COLOR_T t_g_epg_color_prg_lst_title_txt;
extern GL_COLOR_T t_g_epg_color_prg_lst_title_hlt_txt;
extern GL_COLOR_T t_g_epg_color_prg_lst_col_bk;
extern GL_COLOR_T t_g_epg_color_prg_lst_col_date_txt;
extern GL_COLOR_T t_g_epg_color_prg_lst_col_date_hlt_txt;
extern GL_COLOR_T t_g_epg_color_prg_lst_col_date_hlt_uf_txt;
extern GL_COLOR_T t_g_epg_color_prg_lst_col_time_txt;
extern GL_COLOR_T t_g_epg_color_prg_lst_col_time_hlt_txt;
extern GL_COLOR_T t_g_epg_color_prg_lst_col_time_hlt_uf_txt;
extern GL_COLOR_T t_g_epg_color_prg_lst_col_title_txt;
extern GL_COLOR_T t_g_epg_color_prg_lst_col_title_hlt_txt;
extern GL_COLOR_T t_g_epg_color_prg_lst_col_title_hlt_uf_txt;


/*
   Surfing list.
*/
extern GL_COLOR_T t_g_epg_color_surf_lst_bdr;
extern GL_COLOR_T t_g_epg_color_surf_lst_bdr_hlt;
extern GL_COLOR_T t_g_epg_color_surf_lst_bk;
extern GL_COLOR_T t_g_epg_color_surf_lst_vp;
extern GL_COLOR_T t_g_epg_color_surf_lst_elem_bk;
extern GL_COLOR_T t_g_epg_color_surf_lst_elem_hlt_bk;
extern GL_COLOR_T t_g_epg_color_surf_lst_elem_hlt_uf_bk;
extern GL_COLOR_T t_g_epg_color_surf_lst_title_txt;
extern GL_COLOR_T t_g_epg_color_surf_lst_title_hlt_txt;
extern GL_COLOR_T t_g_epg_color_surf_lst_col_bk;
extern GL_COLOR_T t_g_epg_color_surf_lst_col_no_txt;
extern GL_COLOR_T t_g_epg_color_surf_lst_col_no_hlt_txt;
extern GL_COLOR_T t_g_epg_color_surf_lst_col_no_hlt_uf_txt;
extern GL_COLOR_T t_g_epg_color_surf_lst_col_name_txt;
extern GL_COLOR_T t_g_epg_color_surf_lst_col_name_hlt_txt;
extern GL_COLOR_T t_g_epg_color_surf_lst_col_name_hlt_uf_txt;


/*
   Description list.
*/
extern GL_COLOR_T t_g_epg_color_desc_lst_bk;
extern GL_COLOR_T t_g_epg_color_desc_lst_vp;
extern GL_COLOR_T t_g_epg_color_desc_lst_elem_bk;
extern GL_COLOR_T t_g_epg_color_desc_lst_elem_hlt_bk;
extern GL_COLOR_T t_g_epg_color_desc_lst_elem_hlt_uf_bk;
extern GL_COLOR_T t_g_epg_color_desc_lst_col_bk;
extern GL_COLOR_T t_g_epg_color_desc_lst_col_time_txt;
extern GL_COLOR_T t_g_epg_color_desc_lst_col_time_hlt_txt;
extern GL_COLOR_T t_g_epg_color_desc_lst_col_time_hlt_uf_txt;
extern GL_COLOR_T t_g_epg_color_desc_lst_col_ca_txt;
extern GL_COLOR_T t_g_epg_color_desc_lst_col_ca_hlt_txt;
extern GL_COLOR_T t_g_epg_color_desc_lst_col_ca_hlt_uf_txt;


/*
   Icon list.
*/
extern GL_COLOR_T t_g_epg_color_icon_lst_bk;
extern GL_COLOR_T t_g_epg_color_icon_lst_vp;
extern GL_COLOR_T t_g_epg_color_icon_lst_elem_bk;
extern GL_COLOR_T t_g_epg_color_icon_lst_elem_hlt_bk;
extern GL_COLOR_T t_g_epg_color_icon_lst_elem_hlt_uf_bk;
extern GL_COLOR_T t_g_epg_color_icon_lst_col_bk;


/*
   Help list.
*/
extern GL_COLOR_T t_g_epg_color_help_lst_bk;
extern GL_COLOR_T t_g_epg_color_help_lst_vp;
extern GL_COLOR_T t_g_epg_color_help_lst_elem_bk;
extern GL_COLOR_T t_g_epg_color_help_lst_elem_hlt_bk;
extern GL_COLOR_T t_g_epg_color_help_lst_elem_hlt_uf_bk;
extern GL_COLOR_T t_g_epg_color_help_lst_col_bk;
extern GL_COLOR_T t_g_epg_color_help_lst_col_prev_txt;
extern GL_COLOR_T t_g_epg_color_help_lst_col_prev_hlt_txt;
extern GL_COLOR_T t_g_epg_color_help_lst_col_prev_hlt_uf_txt;
extern GL_COLOR_T t_g_epg_color_help_lst_col_next_txt;
extern GL_COLOR_T t_g_epg_color_help_lst_col_next_hlt_txt;
extern GL_COLOR_T t_g_epg_color_help_lst_col_next_hlt_uf_txt;
extern GL_COLOR_T t_g_epg_color_help_lst_col_up_txt;
extern GL_COLOR_T t_g_epg_color_help_lst_col_up_hlt_txt;
extern GL_COLOR_T t_g_epg_color_help_lst_col_up_hlt_uf_txt;
extern GL_COLOR_T t_g_epg_color_help_lst_col_down_txt;
extern GL_COLOR_T t_g_epg_color_help_lst_col_down_hlt_txt;
extern GL_COLOR_T t_g_epg_color_help_lst_col_down_hlt_uf_txt;


#ifdef APP_DVBT_SUPPORT

/*
   Type list.
*/
extern GL_COLOR_T t_g_epg_color_type_lst_bk;
extern GL_COLOR_T t_g_epg_color_type_lst_vp;
extern GL_COLOR_T t_g_epg_color_type_lst_elem_bk;
extern GL_COLOR_T t_g_epg_color_type_lst_elem_hlt_bk;
extern GL_COLOR_T t_g_epg_color_type_lst_elem_hlt_uf_bk;
extern GL_COLOR_T t_g_epg_color_type_lst_col_bk;
extern GL_COLOR_T t_g_epg_color_type_lst_col_txt;
extern GL_COLOR_T t_g_epg_color_type_lst_col_hlt_txt;
extern GL_COLOR_T t_g_epg_color_type_lst_col_hlt_uf_txt;
extern GL_COLOR_T t_g_epg_color_type_lst_title_txt;
extern GL_COLOR_T t_g_epg_color_type_lst_title_hlt_txt;


/*
   Subtype list.
*/
extern GL_COLOR_T t_g_epg_color_subtype_lst_bk;
extern GL_COLOR_T t_g_epg_color_subtype_lst_vp;
extern GL_COLOR_T t_g_epg_color_subtype_lst_elem_bk;
extern GL_COLOR_T t_g_epg_color_subtype_lst_elem_hlt_bk;
extern GL_COLOR_T t_g_epg_color_subtype_lst_elem_hlt_uf_bk;
extern GL_COLOR_T t_g_epg_color_subtype_lst_col_bk;
extern GL_COLOR_T t_g_epg_color_subtype_lst_col_txt;
extern GL_COLOR_T t_g_epg_color_subtype_lst_col_hlt_txt;
extern GL_COLOR_T t_g_epg_color_subtype_lst_col_hlt_uf_txt;
extern GL_COLOR_T t_g_epg_color_subtype_lst_title_txt;
extern GL_COLOR_T t_g_epg_color_subtype_lst_title_hlt_txt;

#endif /* APP_DVBT_SUPPORT */


/*
   Program text.
*/
extern GL_COLOR_T t_g_epg_color_prg_txt_bk;
extern GL_COLOR_T t_g_epg_color_prg_txt;


/*
   Time text.
*/
extern GL_COLOR_T t_g_epg_color_time_txt_bk;
extern GL_COLOR_T t_g_epg_color_time_txt;


/*
   Video text.
*/
extern GL_COLOR_T t_g_epg_color_video_txt_bk;
extern GL_COLOR_T t_g_epg_color_video_txt;


/*
   Description text.
*/
extern GL_COLOR_T t_g_epg_color_desc_txt_bk;
extern GL_COLOR_T t_g_epg_color_desc_txt;


/*
   Page text.
*/
extern GL_COLOR_T t_g_epg_color_page_txt_bk;
extern GL_COLOR_T t_g_epg_color_page_txt;


/*
   Channel text.
*/
extern GL_COLOR_T t_g_epg_color_chn_txt_bk;
extern GL_COLOR_T t_g_epg_color_chn_txt;


/*
   Direct channel input (DCI) text.
*/
extern GL_COLOR_T t_g_epg_color_dci_txt_bk;
extern GL_COLOR_T t_g_epg_color_dci_txt;
extern GL_COLOR_T t_g_epg_color_dci_txt_dummy;


/*
   Retrieving icon.
*/
extern GL_COLOR_T t_g_epg_color_retrieve_icon_bk;


/*
   Retrieving text.
*/
extern GL_COLOR_T t_g_epg_color_retrieve_txt_bk;
extern GL_COLOR_T t_g_epg_color_retrieve_txt;


/*
   Password text.
*/
extern GL_COLOR_T t_g_epg_color_passwd_txt_bk;
extern GL_COLOR_T t_g_epg_color_passwd_txt;


/*
   Password edit.
*/
extern GL_COLOR_T t_g_epg_color_passwd_edit_bdr_bk;
extern GL_COLOR_T t_g_epg_color_passwd_edit_cnt_bk;
extern GL_COLOR_T t_g_epg_color_passwd_edit_txt;
extern GL_COLOR_T t_g_epg_color_passwd_edit_txt_hlt;

/*
   API's.
*/
extern INT32 epg_color_init (VOID);


#endif /* _EPG_COLOR_H_ */
