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
#ifndef __MMP_THUMBNAILMODE_LAYOUT_H__
#define __MMP_THUMBNAILMODE_LAYOUT_H__

#include "wdk/wdk_api.h"
#include "c_os.h"

#include "res/mmp/gen/mmp_gen_img.h"
#include "res/mmp/gen/mmp_gen_clr.h"
#include "res/mmp/gen/mmp_mlm.h"
#include "res/mmp/gen/mmp_gen_font_info.h"


enum
{
    WID_MMP_THUMBNAILMODE_FRM_BASE_FRM,
    WID_MMP_THUMBNAILMODE_FRM_LEFT_BASE_FRM,
    WID_MMP_THUMBNAILMODE_BTN_LOGO_ICON,
    WID_MMP_THUMBNAILMODE_FRM_LEFT_UI_FRM1,
    WID_MMP_THUMBNAILMODE_BTN_MEDIA_TYPE,
    WID_MMP_THUMBNAILMODE_LB_DRIVER,
    WID_MMP_THUMBNAILMODE_BTN_START_SLIDESHOW,
    WID_MMP_THUMBNAILMODE_BTN_NAME_A_Z,
    WID_MMP_THUMBNAILMODE_BTN_THUMBNAILS,
    WID_MMP_THUMBNAILMODE_BTN_SETTINGS,
    WID_MMP_THUMBNAILMODE_BTN_BROWSE_MUSIC,
    WID_MMP_THUMBNAILMODE_ICON_FILE_ICON,
    WID_MMP_THUMBNAILMODE_TXT_FILE_NAME,
    WID_MMP_THUMBNAILMODE_TXT_SORT,
    WID_MMP_THUMBNAILMODE_TXT_VIEW,
    WID_MMP_THUMBNAILMODE_BTN_BACK,
    WID_MMP_THUMBNAILMODE_BTN_LOGO_ICON_1,
    WID_MMP_THUMBNAILMODE_FRM_FILE_INFO,
    WID_MMP_THUMBNAILMODE_FRM_RIGHT_BASE_FRM,
    WID_MMP_THUMBNAILMODE_BTN_RIGHT_TO_LEFT_BTN,
    WID_MMP_THUMBNAILMODE_TXT_PAGE_NUM,
    WID_MMP_THUMBNAILMODE_TXT_PATH,
    WID_MMP_THUMBNAILMODE_BTN_PAGE_NEXT,
    WID_MMP_THUMBNAILMODE_BTN_PAGE_BACK,
    WID_MMP_THUMBNAILMODE_FRM_THUMBNAILMODE_UI,
    WID_MMP_THUMBNAILMODE_FRM_HLT_THUMB_MOV_FRM,
    WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE0,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT0,
    WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE1,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT1,
    WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE2,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT2,
    WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE3,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT3,
    WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE4,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT4,
    WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE5,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT5,
    WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE6,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT6,
    WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE7,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT7,
    WID_MMP_THUMBNAILMODE_BTN_THUMBNAILMODE8,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT8,
    WID_MMP_THUMBNAILMODE_FRM_HLT_FOLDER_MOVE_FRM,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_455,
    WID_MMP_THUMBNAILMODE_FRM_PRE_FOLDER,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEX0,
    WID_MMP_THUMBNAILMODE_FRM_FOLDER1,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_1,
    WID_MMP_THUMBNAILMODE_FRM_FOLDER2,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_2,
    WID_MMP_THUMBNAILMODE_FRM_FOLDER3,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_3,
    WID_MMP_THUMBNAILMODE_FRM_FOLDER4,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_4,
    WID_MMP_THUMBNAILMODE_FRM_FOLDER5,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_5,
    WID_MMP_THUMBNAILMODE_FRM_FOLDER6,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_6,
    WID_MMP_THUMBNAILMODE_FRM_FOLDER7,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_7,
    WID_MMP_THUMBNAILMODE_FRM_FOLDER8,
    WID_MMP_THUMBNAILMODE_TXT_NEWTEXT_8,
    WID_MMP_THUMBNAILMODE_BTN_SKIP0,
    WID_MMP_THUMBNAILMODE_BTN_SKIP0_1,
    WID_MMP_THUMBNAILMODE_BTN_SKIP0_2,
    WID_MMP_THUMBNAILMODE_BTN_SKIP0_3,
    WID_MMP_THUMBNAILMODE_BTN_SKIP0_4,
    WID_MMP_THUMBNAILMODE_BTN_SKIP0_5,
    WID_MMP_THUMBNAILMODE_BTN_SKIP0_6,
    WID_MMP_THUMBNAILMODE_BTN_SKIP0_7,
    WID_MMP_THUMBNAILMODE_BTN_SKIP0_8,
    WID_MMP_THUMBNAILMODE_FRM_POP_UP_BASE_FRM,
    WID_MMP_THUMBNAILMODE_FRM_IMAGE_PREVIEW_FRM,
    WID_MMP_THUMBNAILMODE_FRM_POP_UP_BG,
    WID_MMP_THUMBNAILMODE_TXT_EXCLUDE_STATUS_TEXT,
    WID_MMP_THUMBNAILMODE_BTN_STARTSLIDESHOW_BTN,
    WID_MMP_THUMBNAILMODE_BTN_PHOTO_INFO_BTN,
    WID_MMP_THUMBNAILMODE_BTN_PHOTO_ROTATE_LEFT_BTN,
    WID_MMP_THUMBNAILMODE_BTN_ROTATE_RIGHT_BTN,
    WID_MMP_THUMBNAILMODE_BTN_STOP_BTN,
    WID_MMP_THUMBNAILMODE_BTN_DONE_BTN,
    WID_MMP_THUMBNAILMODE_BTN_FULL_SCREEN_BTN,
    WID_MMP_THUMBNAILMODE_TXT_MODIFY_PHOTO,
    WID_MMP_THUMBNAILMODE_TOTAL_COUNT
};

INT32 mmp_thumbnailmode_clr_wgt_cb(VOID);
INT32 mmp_thumbnailmode_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct p_cb);

INT32 mmp_thumbnailmode_create_ui(HANDLE_T h_container);
HANDLE_T mmp_thumbnailmode_get_wgt_hdl(UINT32 e_widget_id);
INT32 mmp_thumbnailmode_update_text(UINT16 ui2_lang);
INT32 mmp_thumbnailmode_destroy_ui(VOID);

INT32 mmp_thumbnailmode_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *ph_mi);
HANDLE_T mmp_thumbnailmode_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T h_mi);
INT32 mmp_thumbnailmode_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi);
INT32 mmp_thumbnailmode_destroy_ui_mi(WDK_UI_MI_T h_mi);

#endif /* __MMP_THUMBNAILMODE_LAYOUT_H__ */
