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
 * $RCSfile: menu_atsc_settings.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/9 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 9cd3c20f32467f383f0d47c1431bb92b $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "c_scc.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svctx.h"
#include "c_svl.h"
#include "c_tsl.h"

#include "app_util/a_cfg.h"

#include "menu2/menu_atsc/menu_atsc.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "menu2/menu_dbg.h"




#if APP_ATSC_SPT
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

/* closed caption */
MENU_ITEM_T          t_g_menu_atsc_item_anlg_cc;
MENU_ITEM_T          t_g_menu_atsc_item_dig_cc;


/*-----------------------------------------------------------------------------
                    static function implementation
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    video related function implementation
 ----------------------------------------------------------------------------*/

/* Analog Closed Caption */
static VOID _set_anlg_cc_idx(UINT16 ui2_idx)
{
    a_cfg_set_anlg_cc((UINT8)ui2_idx);
}

static UINT16 _get_anlg_cc_idx(VOID)
{
    UINT8 ui1_cc = APP_CFG_CUSTOM_ANA_CC_CC1;

    a_cfg_get_anlg_cc(&ui1_cc);

    return (UINT16)ui1_cc;
}

/* Digital Closed Caption */
static VOID _set_dig_cc_idx(UINT16 ui2_idx)
{
    a_cfg_set_dig_cc((UINT8)ui2_idx);
}

static UINT16 _get_dig_cc_idx(VOID)
{
    UINT8 ui1_cc = APP_CFG_CUSTOM_DIG_CC_SERVICE1;

    a_cfg_get_dig_cc(&ui1_cc);

    return (UINT16)ui1_cc;
}

/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
INT32 menu_atsc_settings_init(VOID)
{
    INT32 i4_ret;

    /* Analog Closed Caption */
    i4_ret = menu_page_tree_listbox_item(&t_g_menu_atsc_item_anlg_cc,
                                         MLM_MENU_KEY_CC_ANA,
                                         MLM_MENU_KEY_HELP_TIP_CAPTION_ACC,
                                         MLM_MENU_KEY_CC_ANA_OFF,
                                         #ifdef APP_MENU_WITH_ACC_TEXT
                                         MLM_MENU_KEY_CC_ANA_TXT4,
                                         #else
                                         MLM_MENU_KEY_CC_ANA_CC4,
                                         #endif
                                         _set_anlg_cc_idx,
                                         _get_anlg_cc_idx);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_listbox_item_set_elem_help_tip(&t_g_menu_atsc_item_anlg_cc,
                                                          TRUE,
                                                          MLM_MENU_KEY_CC_ANA_OFF,
                                                          #ifdef APP_MENU_WITH_ACC_TEXT
                                                          MLM_MENU_KEY_CC_ANA_TXT4
                                                          #else
                                                          MLM_MENU_KEY_CC_ANA_CC4
                                                          #endif
                                                          );
    MENU_CHK_FAIL(i4_ret);

    /* Digtal Closed Caption */
    i4_ret = menu_page_tree_listbox_item(&t_g_menu_atsc_item_dig_cc,
                                         MLM_MENU_KEY_CC_DIG,
                                         MLM_MENU_KEY_HELP_TIP_CAPTION_DCC,
                                         MLM_MENU_KEY_CC_DIG_OFF,
                                         MLM_MENU_KEY_CC_DIG_SVC6,
                                         _set_dig_cc_idx,
                                         _get_dig_cc_idx);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_tree_listbox_item_set_elem_help_tip(&t_g_menu_atsc_item_dig_cc,
                                                           TRUE,
                                                           MLM_MENU_KEY_CC_DIG_OFF,
                                                           MLM_MENU_KEY_CC_DIG_SVC6);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}
#endif

