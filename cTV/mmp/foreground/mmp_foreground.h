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
 * $RCSfile: thumbnailmode.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *         This header file contains public interfaces, constant and type
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/

#ifndef _MMP_FOREGROUND_H_
#define _MMP_FOREGROUND_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "c_os.h"
#include "u_irrc_btn_def.h"
#include "c_uc_str.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#include "mmp/common_ui2/mmp_info_bar.h"
#include "res/mmp/thumbnailmode/mmp_thumbnailmode_rc.h"
#include "res/mmp/gen/mmp_mmp_layout.h"
#include "res/mmp/gen/mmp_tm_focus_layout.h"
#include "app_util/option_list/a_optl.h"
#ifdef APP_NET_NEIGHBOR_SUPPORT
#include "app_util/pwd_dlg_util/a_pwd_dlg_util.h"
#endif
#include "res/nav/nav_variant.h"
#include "wdk/util/wdk_wgl_util.h"
#include "mmp/disp_res_ctrler/mmp_drc.h"
#include MMP_COM_UI_HEADER_FILE
#include MMP_MLM_HEADER_FILE
#include "res/mmp/gen/mmp_tm_focus_layout.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "mmp/mmp_common.h"



/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define MMP_FOREGROUND_X             (0) 
#define MMP_FOREGROUND_Y             (0)
#define MMP_FOREGROUND_WIDTH         (1920)
#define MMP_FOREGROUND_HEIGHT        (1080)

#define MMP_FG_LOGO_X             (43) 
#define MMP_FG_LOGO_Y             (22)
#define MMP_FG_LOGO_WIDTH         (156)
#define MMP_FG_LOGO_HEIGHT        (36)

#define MMP_FG_DEV_NAME_X             (4) 
#define MMP_FG_DEV_NAME_Y             (170)
#define MMP_FG_DEV_NAME_WIDTH         (562)
#define MMP_FG_DEV_NAME_HEIGHT        (66)

#define MMP_FG_LIST_X             (4) 
#define MMP_FG_LIST_Y             (170)
#define MMP_FG_LIST_WIDTH         (562)
#define MMP_FG_LIST_HEIGHT        (500)

#define MMP_FG_TIP_X             (4) 
#define MMP_FG_TIP_Y             (800)
#define MMP_FG_TIP_WIDTH         (562)
#define MMP_FG_TIP_HEIGHT        (66)


/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/

typedef struct _MMP_FG_MEMBER_T
{
    HANDLE_T            h_main_frm;
    HANDLE_T            h_logo;
    HANDLE_T            h_dev_name;
    HANDLE_T            h_msg_text;
    HANDLE_T            h_list;
    HANDLE_T            h_help_tip;

    UINT8               ui1_gui_lang_id;

    BOOL                b_is_type_list;
    BOOL                b_is_no_dev;

}   MMP_FG_MEMBER_T;


/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
extern INT32 a_mmp_foreground_register(VOID);

extern INT32 mmp_foreground_view_repaint(VOID);

extern INT32 mmp_foreground_chg_inp_src_to_cast(VOID);

#endif /*_MMP_FOREGROUDN_H_*/

