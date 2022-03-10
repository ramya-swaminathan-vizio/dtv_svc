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
 * $RCSfile: nav_custom_comp_id.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/7 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 27bad65f0954f3bdb87f20fd6c804eab $
 *
 * Description:
 * The header file is used to let customer defined its own
 * component id if cutomer's features are very different with MTK turn-key solution
 * and need to custom her special Navigator components in custom-layer.
 *---------------------------------------------------------------------------*/
#ifndef _NAV_CUSTOM_COMP_ID_H_
#define _NAV_CUSTOM_COMP_ID_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#ifdef APP_NAV_CUSTOM_COMP_ID
/* navigator customer-defined component ids
 *
 * if the total componet is over 32, please remember to
 * define APP_NAV_MAX_64_COMPS in this file or customer's CFG
 * file (under custom modle's sys_build directory
 */
#ifndef APP_NAV_MAX_64_COMPS
    #define APP_NAV_MAX_64_COMPS
#endif
typedef enum
{
    /* WARNING: maximum = 32, current = 32 */
    NAV_COMP_ID_SI = 0,             /* all */
    //NAV_COMP_ID_DVD_PLAYER,         /* all */
    NAV_COMP_ID_SINGLE_RF_SCAN,     /* US: don't change the order, it needs to check to scan asap */
    NAV_COMP_ID_PWD_DLG,            /* all */
#ifdef NEVER
    NAV_COMP_ID_MHEG5,              /* EU  */
#endif /* NEVER */
#ifdef APP_TTX_SUPPORT
    NAV_COMP_ID_TTX,                /* EU  */
#endif
    NAV_COMP_ID_CH_LIST,            /* all */
    NAV_COMP_ID_CH_LIST_SELECTION,  /* EU  */
    NAV_COMP_ID_SATELLITE_SELECTION,/* EU  */
    NAV_COMP_ID_FAV_LIST,           /* all */
    NAV_COMP_ID_AUDIO_SEL,          /* all */
    NAV_COMP_ID_VIDEO_SEL,          /* all */
    NAV_COMP_ID_CC_SEL,             /* US:cc, EU:subtitle */
    NAV_COMP_ID_VOL_CTRL,           /* all */
    NAV_COMP_ID_SCREEN_MODE,        /* all */
    NAV_COMP_ID_DCR_AGENT,          /* US:DCR, EU:CI */
    NAV_COMP_ID_INPUT_SRC,          /* all */
    //NAV_COMP_ID_PIP_POP,            /* all */
    NAV_COMP_ID_EPG,                /* all */
    NAV_COMP_ID_BURNING_MODE,       /* all */
    NAV_COMP_ID_SLEEP,              /* all */
    NAV_COMP_ID_ULPK,               /* all */
    NAV_COMP_ID_WR_UPDATER,         /* all */
    NAV_COMP_ID_ON_TIMER_CH,        /* all */
    NAV_COMP_ID_FREEZE,             /* all */
    NAV_COMP_ID_ZOOM_PAN,           /* all */
    NAV_COMP_ID_PICTURE_EFFECT,     /* all */
    NAV_COMP_ID_SOUND_EFFECT,       /* all */
    NAV_COMP_ID_CH_SELECT,
    NAV_COMP_ID_POWER = 26,         /* all */
#ifdef APP_NAV_MAX_64_COMPS
    NAV_COMP_ID_CLOCK,              /* all */
    NAV_COMP_ID_CSM,                /* for customer-only compoent */
    //NAV_COMP_ID_EI,                 /* all */
    NAV_COMP_ID_COLOR_TEMPERATURE,  /* all */
#ifdef NEVER
    NAV_COMP_ID_SCART_MONITOR,      /* EU  */
#endif /* NEVER */
    NAV_COMP_ID_OAD,                /* EU Over Air Download */
    NAV_COMP_ID_RECORD,             /* all */
    NAV_COMP_ID_AUD_ONLY,           /* all */
    NAV_COMP_ID_RETAIL_MODE,        /* all */
    //NAV_COMP_ID_3D_SETTING,         /* 3D*/
    NAV_COMP_ID_VIEWPORT,
    NAV_COMP_ID_SFM,                /* for service and factory mode menu */
    NAV_COMP_ID_REMINDER,           /* all */
    NAV_COMP_ID_FACTORY,            /* all */
    NAV_COMP_ID_FLICKER,            /* all */
    NAV_COMP_ID_USB_OC,             /* USB OC */
    NAV_COMP_ID_DIALOG,             /* all */
    NAV_COMP_ID_MMP_LAUNCHER,       /* all */
    NAV_COMP_ID_CUSTOM_1,           /* for customer-only compoent */
    NAV_COMP_ID_CUSTOM_2,           /* for customer-only compoent */
    NAV_COMP_ID_CUSTOM_3,           /* for customer-only compoent */
    NAV_COMP_ID_CUSTOM_4,           /* for customer-only compoent */

    /* WARNING: maximum = 64, current = 50 */
#ifdef APP_NAV_USB_PLD
    NAV_COMP_ID_USB_PLD,
#endif

#ifndef LINUX_TURNKEY_SOLUTION
    NAV_COMP_ID_UPG,                /* all */
#else
    NAV_COMP_ID_UPDATER,            /* all */
#endif

#endif /* end of APP_NAV_MAX_64_COMPS */

    /* don't change the following's order */
    NAV_COMP_ID_IB,                 /* all */
    NAV_COMP_ID_BANNER,             /* all */
    NAV_COMP_ID_SCREEN_SAVER,       /* all */
    NAV_COMP_ID_MISC,               /* all */
    NAV_COMP_ID_VIA_DLG,
    NAV_COMP_ID_SCRN_BLANK,
#ifdef APP_C4TV_SUPPORT
    NAV_COMP_ID_C4TV_APRON, /* change it before banner */
#endif

     NAV_COMP_ID_REVOLT_MISC, /* revolt_misc_system_info*/
     NAV_COMP_ID_TUNER_SETUP, /* tuner setup*/
    NAV_COMP_ID_REVOLT_INFO, //rest notification
    NAV_COMP_ID_LINK,//link key
    NAV_COMP_ID_LONG_PRESS,//panel long press
    NAV_COMP_ID_TEST_PATTERN,
#ifdef APP_ZOOM_MODE_SUPPORT
    NAV_COMP_ID_ZOOM,
#endif
    NAV_COMP_ID_PPP, //  Picture Mode & Power Mode Popup notification
	NAV_COMP_ID_WEBUI_AGENT,
    NAV_COMP_ID_LAST_VALID_ENTRY    /* only for counting purpose */
} NAV_COMP_ID_T;
#endif
/*-----------------------------------------------------------------------------
                    customization declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
#endif /* _NAV_CUSTOM_COMP_ID_H_ */
