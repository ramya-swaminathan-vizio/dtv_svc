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
 * $RCSfile: record.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_REC_PVR_VIEW_CUSTOM_H_
#define _NAV_REC_PVR_VIEW_CUSTOM_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#include "app_util/a_common.h"
#include "nav/record/a_nav_rec.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/* Timer */
#define PVR_REFRESH_DELAY        500
#define PVR_HIDE_DELAY           10000
#define PVR_PAUSE_HIDE_DELAY     5000
#define PVR_MSG_HIDE_DELAY       5000

/* How many seconds the BTN_NEXT and BTN_PREV would jump over*/
#define PVR_STEP_SECS            10

/* Root frame */
#define PVR_FRM_X                (DISPLAY_WIDTH- PVR_FRM_W) / 2
#define PVR_FRM_Y                (DISPLAY_HEIGHT - PVR_FRM_H - 60)
#define PVR_FRM_W                540
#define PVR_FRM_H                (PVR_CH_LB_Y + PVR_CH_LB_H +6)

/* PVR line */
#define PVR_LINE_X        (6)
#define PVR_LINE_Y        (PVR_MINI_FRM_H)
#define PVR_LINE_W        (PVR_FRM_W - 2*PVR_LINE_X)
#define PVR_LINE_H        (2)

/* Broadcast Time */
#define PVR_BRDCST_TIME_X        (PVR_FRM_W - PVR_BRDCST_TIME_W)
#define PVR_BRDCST_TIME_Y        (PVR_REC_STATUS_Y)
#define PVR_BRDCST_TIME_W        (90)
#define PVR_BRDCST_TIME_H        (PVR_REC_STATUS_H)
#define PVR_BRDCST_TIME_ALIGN    (WGL_AS_LEFT_BOTTOM)

/* Chinnel Info */
#define PVR_CH_INFO_X        (20)
#define PVR_CH_INFO_Y        (PVR_LINE_Y + PVR_LINE_H)
#define PVR_CH_INFO_W        (500)
#define PVR_CH_INFO_H        (30)
#define PVR_CH_INFO_ALIGN    (WGL_AS_LEFT_CENTER)

/* Pro title */
#define PVR_PRO_TITLE_X        (20)
#define PVR_PRO_TITLE_Y        (PVR_CH_INFO_Y +PVR_CH_INFO_H+5)
#define PVR_PRO_TITLE_W        (500)
#define PVR_PRO_TITLE_H        (60)
#define PVR_PRO_TITLE_ALIGN    (WGL_AS_LEFT_TOP)


#define  PVR_CH_LB_COL_NUM                    (3)
#define  PVR_CH_LB_LONG_TXT_SCRL_DELAY        (180)
#define  PVR_CH_LB_ELEM_H                     (30)
#define  PVR_CH_LB_COL_TEXT_FNT_SIZE          FE_FNT_SIZE_MEDIUM

#define  PVR_CH_LB_X                          (6)
#define  PVR_CH_LB_Y                          (PVR_LINE_Y + PVR_LINE_H + 6)
#define  PVR_CH_LB_W                          (PVR_FRM_W - 2*PVR_CH_LB_X)
#define  PVR_CH_LB_H                          (40)
#define  PVR_CH_LB_CNT_INSET_L                (0)
#define  PVR_CH_LB_CNT_INSET_R                (0)
#define  PVR_CH_LB_CNT_INSET_T                (0)
#define  PVR_CH_LB_CNT_INSET_B                (0)
#define  PVR_CH_LB_ELEM_INSET_L               (0)
#define  PVR_CH_LB_ELEM_INSET_R               (0)
#define  PVR_CH_LB_ELEM_INSET_T               (0)
#define  PVR_CH_LB_ELEM_INSET_B               (0)
#define  PVR_CH_LB_COL_TEXT_INSET_L           (6)
#define  PVR_CH_LB_COL_TEXT_INSET_R           (6)
#define  PVR_CH_LB_COL_TEXT_INSET_T           (0)
#define  PVR_CH_LB_COL_TEXT_INSET_B           (0)

#define  PVR_CH_LB_COL0_W                 (90)
#define  PVR_CH_LB_COL0_ALIGN             WGL_AS_LEFT_CENTER
#define  PVR_CH_LB_COL1_W                 (PVR_CH_LB_W/2)
#define  PVR_CH_LB_COL1_ALIGN             WGL_AS_LEFT_CENTER
#define  PVR_CH_LB_COL2_W                 (PVR_CH_LB_W/2)
#define  PVR_CH_LB_COL2_ALIGN             WGL_AS_LEFT_CENTER

/*-----------------------------------------------------------------------------
    Mini
-----------------------------------------------------------------------------*/
#define PVR_MINI_FRM_X                (0)
#define PVR_MINI_FRM_Y                (DISPLAY_HEIGHT - 50)
#define PVR_MINI_FRM_W                (150)
#define PVR_MINI_FRM_H                (48)

/* Record status */
#define PVR_REC_STATUS_X              (6)
#define PVR_REC_STATUS_Y              (6)
#define PVR_REC_STATUS_W              (36)
#define PVR_REC_STATUS_H              (36)

#define PVR_MINI_TXT_X                (PVR_REC_STATUS_W + 12)
#define PVR_MINI_TXT_Y                (0)
#define PVR_MINI_TXT_W                (PVR_MINI_FRM_W - PVR_MINI_TXT_X)
#define PVR_MINI_TXT_H                PVR_MINI_FRM_H
#define PVR_MINI_TXT_ALIGN            WGL_AS_LEFT_CENTER

/*-----------------------------------------------------------------------------
    Msg
-----------------------------------------------------------------------------*/
#define PVR_MSG_FRM_X                120
#define PVR_MSG_FRM_Y                (DISPLAY_HEIGHT - PVR_FRM_H - 80)
#define PVR_MSG_FRM_W                500
#define PVR_MSG_FRM_H                80

#define PVR_MSG_TXT_X                0
#define PVR_MSG_TXT_Y                0
#define PVR_MSG_TXT_W                PVR_MSG_FRM_W
#define PVR_MSG_TXT_H                PVR_MSG_FRM_H
#define PVR_MSG_TXT_INSET_L          10
#define PVR_MSG_TXT_INSET_R          10
#define PVR_MSG_TXT_INSET_T          0
#define PVR_MSG_TXT_INSET_B          0

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

#endif /* _NAV_REC_PVR_VIEW_CUSTOM_H_ */
