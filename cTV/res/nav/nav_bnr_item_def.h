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
 * $RCSfile: nav_bnr_item_def.h,v $
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

#ifndef _NAV_BNR_ITEM_DEF_H_
#define _NAV_BNR_ITEM_DEF_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

typedef enum _BANNER_ITEM_IDX_T
{
    /* frame item */
    BANNER_ITM_FRM_CH = 0,
    BANNER_ITM_FRM_INF,
    BANNER_ITM_FRM_DTL,
    BANNER_ITM_FRM_3D,

    /* text item */
    BANNER_ITM_TV_NAME,
    BANNER_ITM_CH_NO,
    BANNER_ITM_IPTS_ICON,
    BANNER_ITM_CH_NAME,
    BANNER_ITM_MSG,
    BANNER_ITM_PROG_TITLE,
    BANNER_ITM_RATING,
    BANNER_ITM_PROG_TIME,
    BANNER_ITM_NEXT_PROG_TITLE,
    BANNER_ITM_NEXT_PROG_TIME,
    BANNER_ITM_PROG_DETAIL,
    BANNER_ITM_PROG_DETAIL_PG_IDX,
    BANNER_ITM_AUDIO_LANG,

    BANNER_ITM_3D_MODE,
    BANNER_ITM_3D_FMT,
    BANNER_ITM_IPT_CH_NO,
    /* icon item */
    BANNER_ITM_IPTS_LOCK_ICON,
    BANNER_ITM_TV_LOCK_ICON,
    BANNER_ITM_PROG_DETAIL_UP_ICON,
    BANNER_ITM_PROG_DETAIL_DN_ICON,
    BANNER_ITM_AD_EYE,

    BANNER_ITM_CUST_TOPMOST_BEGIN,
    BANNER_ITM_VIDEO_INFO = BANNER_ITM_CUST_TOPMOST_BEGIN,
    BANNER_ITM_CAPTION_ICON,
    BANNER_ITM_CAPTION,

    BANNER_ITM_RESOLUTION_TXT,
    BANNER_ITM_ASPECT,

    BANNER_ITM_DOLBY_VISION,

    BANNER_ITM_DOLBY_AUDIO,
#if (CUSTOMER == VIZIO)
    BANNER_ITM_HEADPHONES,  /* Bluetooth headphones icon */
#endif
    BANNER_ITM_AUDIO_FARMAT,
    BANNER_ITM_AUDIO_OUT,
    BANNER_ITM_WIFI_ICON,
    BANNER_ITM_WIFI_TXT,
    BANNER_ITM_TIMER_24,
    BANNER_ITM_LAST_VALID_ENTRY  /* only for counting purpose */

}  NAV_BNR_STATE_ITEM_IDX_T;

/*
typedef enum _BANNER_SIDERBAR_HDR
{
    BANNER_HDR_SDR,
    BANNER_HDR_HLG,
    BANNER_HDR_HDR10,
    BANNER_HDR_DOLBY_VISION,
    BANNER_HDR_HDR10_PLUS
} BANNER_SIDERBAR_HDR;

typedef enum _BANNER_SIDERBAR_EX
{
    BANNER_EX_NULL,
    BANNER_PROGAMING_ENGINE,
    BANNER_FILMMAKER_MODE,
    BANNER_EX_COUNT
} BANNER_SIDERBAR_EX;
*/

typedef enum _BANNER_SIDERBAR_LOGO
{
    //HDR part
    BANNER_LOGO_HDR_SDR,//non
    BANNER_LOGO_HDR_HLG,//icon
    BANNER_LOGO_HDR_HDR10,//icon
    BANNER_LOGO_HDR_DOLBY_VISION,//icon
    BANNER_LOGO_HDR_HDR10_PLUS,//text

    BANNER_LOGO_DOLBY_AUDIO,//icon
    BANNER_LOGO_DOLBY_ATMOS,//icon
    
    BANNER_LOGO_PROGAMING_ENGINE,//icon
    BANNER_LOGO_V_GAMING_ENGINE,//icon
    
    BANNER_LOGO_FILMMAKER_MODE,//icon
    BANNER_LOGO_FREESYNC,//icon
    
    BANNER_LOGO_EX_COUNT
} BANNER_SIDERBAR_LOGO;

typedef enum _BANNER_MM_UPDATE_INFO_AUD
{
    BANNER_MM_UPDATE_INFO_AUD_MONO,
    BANNER_MM_UPDATE_INFO_AUD_STEREO,
    BANNER_MM_UPDATE_INFO_AUD_SAP,
    BANNER_MM_UPDATE_INFO_AUD_DD,
    BANNER_MM_UPDATE_INFO_AUD_DD_ATMOS,
    BANNER_MM_UPDATE_INFO_AUD_DD_DTS,
    BANNER_MM_UPDATE_INFO_AUD_DD_DTS_LBR,
    BANNER_MM_UPDATE_INFO_AUD_DD_DTSHD,
    BANNER_MM_UPDATE_INFO_AUD_DD_DTS_X,


    BANNER_MM_UPDATE_INFO_AUD_EX_COUNT
} BANNER_MM_UPDATE_INFO_AUD;

typedef enum _BANNER_AUD_UPDATE_TYPE
{
    BANNER_AUD_VIRTUAL_INPUT,
    BANNER_AUD_PHYSICAL_INPUT,
    BANNER_AUD_MTS,

    BANNER_AUD_EX_COUNT
} BANNER_AUD_UPDATE_TYPE;

/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif
