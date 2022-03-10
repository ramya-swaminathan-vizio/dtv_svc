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
 *                                                                             *
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
 * $RCSfile: ui.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *
 *
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_NETWORK_SUPPORT
#ifndef _MENU_NETWORK_COM_UI_H_
#define _MENU_NETWORK_COM_UI_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "res/menu2/menu_config.h"
#include "menu_network.h"


#define SIMPLE_DIALOG_FRAM_X                      ((SCREEN_W - SIMPLE_DIALOG_FRAM_W)/2)
#define SIMPLE_DIALOG_FRAM_Y                      ((SCREEN_H - SIMPLE_DIALOG_FRAM_H)/2)
#define SIMPLE_DIALOG_FRAM_W                      (613)
#define SIMPLE_DIALOG_FRAM_H                      (234)

#define SIMPLE_DIALOG_TITLE_X                     (0)
#define SIMPLE_DIALOG_TITLE_Y                     (16)
#define SIMPLE_DIALOG_TITLE_W                     (SIMPLE_DIALOG_FRAM_W)
#define SIMPLE_DIALOG_TITLE_H                     (SIMPLE_DIALOG_FRAM_H - SIMPLE_DIALOG_PB_Y - SIMPLE_DIALOG_TITLE_Y)

#define SIMPLE_DIALOG_PB_X                       (SIMPLE_DIALOG_FRAM_W / 8)
#define SIMPLE_DIALOG_PB_Y                       (SIMPLE_DIALOG_BTN_Y - SIMPLE_DIALOG_PB_H - 32)
#define SIMPLE_DIALOG_PB_W                       (SIMPLE_DIALOG_FRAM_W * 3 / 4)
#define SIMPLE_DIALOG_PB_H                       (MENU_ITEM_V_HEIGHT / 2)

#define SIMPLE_DIALOG_BTN_X                      ((SIMPLE_DIALOG_FRAM_W-SIMPLE_DIALOG_BTN_W)/2)
#define SIMPLE_DIALOG_BTN_Y                      (SIMPLE_DIALOG_FRAM_H-SIMPLE_DIALOG_BTN_H-32)
#define SIMPLE_DIALOG_BTN_W                      (164)
#define SIMPLE_DIALOG_BTN_H                      (33)

#define EB_DIALOG_TITLE_X                       (0)
#define EB_DIALOG_TITLE_Y                       (16)
#define EB_DIALOG_TITLE_W                       (SIMPLE_DIALOG_FRAM_W)
#define EB_DIALOG_TITLE_H                       (64)

#define EB_DIALOG_EB_X                          ((SIMPLE_DIALOG_FRAM_W - EB_DIALOG_EB_W) / 2)
#define EB_DIALOG_EB_Y                          (EB_DIALOG_TITLE_Y + EB_DIALOG_TITLE_H+16)
#define EB_DIALOG_EB_W                          (70)
#define EB_DIALOG_EB_H                          (33)

#define NW_IPERF_PORT_MAX           (5)
#define NW_IPERF_PORT_DEFAULT       (8200)

/*-----------------------------------------------------------------------------
                    function declaraions
 ----------------------------------------------------------------------------*/
extern INT32 menu_network_simple_dialog_show(UINT16      ui2_msgid_title,
                                        UINT16      ui2_msgid_btn,
                                        nw_dialog_cb_fct  pf_back,
                                        BOOL         b_repaint);
extern INT32 menu_network_wps_dialog_show(UINT16      ui2_msgid_title,
                                    UINT16      ui2_msgid_btn,
                                    nw_dialog_cb_fct  pf_back,
                                    BOOL         b_repaint);
extern INT32 menu_network_wps_dialog_set_progress(INT32 i4_progress, BOOL b_repaint);
extern INT32 menu_network_simple_dialog_hide(BOOL  b_repaint);

extern INT32 menu_network_iperf_dialog_set_data(UINT16 i4_value, BOOL b_repaint);
extern UINT16 menu_network_iperf_dialog_get_data(VOID);
extern INT32 menu_network_iperf_dialog_show(UINT16      ui2_msgid_title,
                                            UINT16      ui2_msgid_btn,
                                            nw_dialog_cb_fct  pf_back,
                                            BOOL        b_repaint);

extern INT32 menu_network_com_ui_init(VOID);


#endif /* _MENU_NETWORK_COM_UI_H_ */
#endif /* APP_NETWORK_SUPPORT */

