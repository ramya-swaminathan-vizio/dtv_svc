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
#ifndef __MMP_PP_TB_LAYOUT_H__
#define __MMP_PP_TB_LAYOUT_H__

#include "wdk/wdk_api.h"
#include "c_os.h"

#include "res/mmp/gen/mmp_gen_img.h"
#include "res/mmp/gen/mmp_gen_clr.h"
#include "res/mmp/gen/mmp_mlm.h"
#include "res/mmp/gen/mmp_gen_font_info.h"


enum
{
    WID_MMP_PP_TB_FRM_MAIN_FRM,
    WID_MMP_PP_TB_FRM_TOP_BAR,
    WID_MMP_PP_TB_ICON_PLAY_ICON,
    WID_MMP_PP_TB_ICON_REPEAT_AB_ICON,
    WID_MMP_PP_TB_FRM_PLAYER_BAR,
    WID_MMP_PP_TB_TXT_PLAYER_HINT,
    WID_MMP_PP_TB_ICON_LINE_ICON,
    WID_MMP_PP_TB_ICON_DURA_ICON,
    WID_MMP_PP_TB_TXT_DURA_HINT,
    WID_MMP_PP_TB_ICON_EFFECT_ICON,
    WID_MMP_PP_TB_TXT_EFFECT_HINT,
    WID_MMP_PP_TB_ICON_SHUFFLE_ICON,
    WID_MMP_PP_TB_ICON_FILEIDX_ICON,
    WID_MMP_PP_TB_TXT_FILEIDX_HINT,
    WID_MMP_PP_TB_ICON_FILENAME_ICON,
    WID_MMP_PP_TB_TXT_FILENAME_HINT,
    WID_MMP_PP_TB_ICON_REPEAT_ICON,
    WID_MMP_PP_TB_TXT_REPEAT_HINT,
    WID_MMP_PP_TB_ICON_ZOOM_ICON,
    WID_MMP_PP_TB_TXT_ZOOM_HINT,
    WID_MMP_PP_TB_FRM_INFO_BAR,
    WID_MMP_PP_TB_ICON_MENU_ICON,
    WID_MMP_PP_TB_TXT_MENU_HINT,
    WID_MMP_PP_TB_ICON_SELECT_ICON,
    WID_MMP_PP_TB_TXT_SELECT_HINT,
    WID_MMP_PP_TB_ICON_ENTER_ICON,
    WID_MMP_PP_TB_TXT_ENTER_HINT,
    WID_MMP_PP_TB_TOTAL_COUNT
};

INT32 mmp_pp_tb_clr_wgt_cb(VOID);
INT32 mmp_pp_tb_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct p_cb);

INT32 mmp_pp_tb_create_ui(HANDLE_T h_container);
HANDLE_T mmp_pp_tb_get_wgt_hdl(UINT32 e_widget_id);
INT32 mmp_pp_tb_update_text(UINT16 ui2_lang);
INT32 mmp_pp_tb_destroy_ui(VOID);

INT32 mmp_pp_tb_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *ph_mi);
HANDLE_T mmp_pp_tb_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T h_mi);
INT32 mmp_pp_tb_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi);
INT32 mmp_pp_tb_destroy_ui_mi(WDK_UI_MI_T h_mi);

#endif /* __MMP_PP_TB_LAYOUT_H__ */
