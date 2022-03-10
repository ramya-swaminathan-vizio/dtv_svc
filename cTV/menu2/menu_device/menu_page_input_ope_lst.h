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
 * $RCSfile: menu_page_adv_scan_rng.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/22 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 223730d1bdc36ed27cb26dea5de9232d $
 *
 * Description:
 *      This scan includes both ATV channel scan and DTV channel scan.
 *---------------------------------------------------------------------------*/

#ifndef _MENU_INPUT_OPE_LIS_H_
#define _MENU_INPUT_OPE_LIS_H_


typedef enum
{
    MENU_HDMI_IF_CLRSPC_RGB,
    MENU_HDMI_IF_CLRSPC_YUV422,//
    MENU_HDMI_IF_CLRSPC_YUV444,
    MENU_HDMI_IF_CLRSPC_YUV420,
    MENU_HDMI_IF_CLRSPC_UNKNOW
}MENU_HDMI_IF_CLR_SPC; // see HDMI_IF_CLR_SPC for more detail

extern INT32 menu_input_ope_lst_page_set_title(UTF16_T *pw2s_input);

extern VOID menu_input_repaint_hide_input_orig(VOID);

extern INT32 menu_ope_lst_get_hdmi_color_space(INT32 *pi4_color_space);
extern BOOL menu_ope_lst_hdmi_color_space_is_444(MENU_HDMI_IF_CLR_SPC e_color_space);
extern BOOL menu_ope_lst_hdmi_color_space_is_RGB(MENU_HDMI_IF_CLR_SPC e_color_space);
extern BOOL menu_ope_lst_hdmi_color_space_is_422(MENU_HDMI_IF_CLR_SPC e_color_space);
extern BOOL menu_ope_lst_hdmi_color_space_is_420(MENU_HDMI_IF_CLR_SPC e_color_space);
extern INT32 menu_ope_lst_get_hdmi2_0_is_support(UINT8 ui1_hdmi_port,BOOL *pb_support);
extern UINT8 ope_lst_get_hide_from_input_list(ISL_REC_T* pt_isl_rec);
extern INT32 ope_lst_set_hide_from_input_list(ISL_REC_T* pt_isl_rec, UINT8 ui1_value);
extern INT32 inp_set_full_chroma_by_hdmi_idx(UINT16 ui2_hidmi_idx, BOOL b_on);
extern INT32 inp_lst_get_full_uhd_color_by_hdmi_idx(UINT16 ui2_idx, UINT8* pui1_value);
extern INT32 inp_lst_set_full_uhd_color_by_hdmi_idx(UINT16 ui2_hdmi_idx, UINT8 ui1_value);
extern INT32 inp_init_ctx(VOID);
extern INT32 inp_lst_set_edid_by_port(UINT16 ui2_hdmi_idx, UINT8 ui1_value,BOOL b_hdmi_mode);

#endif /* _MENU_PAGE_DEVICE_NAME_INPUT_H_ */

