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
 * $RCSfile: nav_cec_custom_id.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description: 
 *         This header file contains customization part of the CEC implementation.
 *---------------------------------------------------------------------------*/
/**
 * @file nav_cec_custom_id.h
 *
 * @brief This file declares feature IDs.
 *
 * @author Henry Yu
 */
#ifndef _NAV_CEC_CUSTOM_ID_H_
#define _NAV_CEC_CUSTOM_ID_H_

#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "nav/cec2/nav_cec.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/**
 * @brief This enum lists all CEC feature IDs.
 */
typedef enum
{
    NAV_CEC_FEATURE_ID_VIEW = 0,                /**< CEC View. This is not a feature in spec. */
    NAV_CEC_FEATURE_ID_OTP,                     /**< One touch play. */
    NAV_CEC_FEATURE_ID_SYS_STANDBY,             /**< System standby. */
    NAV_CEC_FEATURE_ID_OTR,                     /**< One touch record. */
    NAV_CEC_FEATURE_ID_DECK_CTRL,               /**< Deck control. */
    NAV_CEC_FEATURE_ID_OSD_DISPLAY,             /**< OSD Display. */
    NAV_CEC_FEATURE_ID_DMC,                     /**< Device meni control. */
    NAV_CEC_FEATURE_ID_SAC,                     /**< System audio control. */
    NAV_CEC_FEATURE_ID_ROUTING_CTRL,            /**< Routing control. */
    NAV_CEC_FEATURE_ID_SYS_INFO,                /**< System info. */
    NAV_CEC_FEATURE_ID_GDPS,                    /**< Give Device Power Status. */
    NAV_CEC_FEATURE_ID_VNDR_CTRL,               /**< Vendor-specific control. */
    NAV_CEC_FEATURE_ID_PASS_THROUGH,            /**< Pass through. */
    NAV_CEC_FEATURE_ID_ARC,
    NAV_CEC_FEATURE_ID_MISC,                    /**< Misc. */
    NAV_CEC_FEATURE_ID_LAST_ENTRY
#if 0
    NAV_CEC_FEATURE_ID_CUSTOM_1,                /**< Customer-specific feature. */
    NAV_CEC_FEATURE_ID_TIMER_PROG,              /**< Timer programming. */
    NAV_CEC_FEATURE_ID_TUNER_CTRL,              /**< Tuner control. */
    NAV_CEC_FEATURE_ID_REMOTE_CTRL_PASS,        /**< Remote control pass through. */
    NAV_CEC_FEATURE_ID_DEV_OSD_NAME_TRANSFER,   /**< Device OSD name transfer. */
    NAV_CEC_FEATURE_ID_AUD_RATE_CTRL,           /**< Audio rate control. */
#endif
} NAV_CEC_FEATURE_ID_T;
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
#endif /* APP_CEC2_SUPPORT */
#endif /* APP_CEC_SUPPORT */
#endif /* _NAV_CEC_CUSTOM_ID_H_ */

