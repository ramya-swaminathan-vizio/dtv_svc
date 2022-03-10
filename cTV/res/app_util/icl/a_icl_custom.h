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
 * $RCSfile: a_icl_custom.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_ICL_CUSTOM_H_
#define _A_ICL_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "app_util/a_icl.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

typedef enum
{
    ICL_CUSTOM_NW_WIDGET_DOCK = 0,
    ICL_CUSTOM_NW_WIDGET_APP,

    /* the last entry */
    ICL_CUSTOM_NW_WIDGET_LAST_ENTRY
} ICL_CUSTOM_NW_WIDGET_T;

typedef enum
{
    ICL_CUSTOM_RESUME_NEXT_APP_MMP = 0,
    ICL_CUSTOM_RESUME_NEXT_APP_WZD_NW,
    ICL_CUSTOM_RESUME_NEXT_APP_WZD_RC,
    ICL_CUSTOM_RESUME_NEXT_APP_WZD_DEVICE_SETUP,
    ICL_CUSTOM_RESUME_NEXT_APP_WIFI_WZD_RC,
    ICL_CUSTOM_RESUME_NEXT_APP_MIRACAST,
    ICL_CUSTOM_RESUME_NEXT_APP_WZD_TUNER_SETUP,
    ICL_CUSTOM_RESUME_NEXT_APP_LAST_ENTRY
}ICL_CUSTOM_RESUME_NEXT_APP_T;

/*-----------------------------------------------------------------------------
    Custom state field definition
-----------------------------------------------------------------------------*/

/* Group Sample */
#define ICL_GRPID_CUSTOM_SAMPLE_GROUP               ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+1)
#define ICL_RECID_CUSTOM_SAMPLE_RECORD              ((ICL_RECID_TYPE)  1)
#define ICL_RECID_CUSTOM_SAMPLE_RECORD_SIZE         (sizeof(UINT8))

/* Group reset */
#define ICL_GRPID_CUSTOM_RESET                      ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+2)
#define ICL_RECID_CUSTOM_RESET_TYPE                 ((ICL_RECID_TYPE)  1)
#define ICL_RECID_CUSTOM_RESET_TYPE_SIZE            (sizeof(UINT8))

#define ICL_RESET_TYPE_NONE                         (UINT8)0
#define ICL_RESET_TYPE_FACTORY                      (UINT8)1
#define ICL_RESET_TYPE_PRIVATE                      (UINT8)2
#define ICL_RESET_TYPE_PUBLIC                       (UINT8)3

/* Group NAV */
#define ICL_GRPID_CUSTOM_NAV                ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+3)
#define ICL_RECID_CUSTOM_NAV_IS_ENTER_WIDE_SELECTION_BY_KEY ((ICL_RECID_TYPE)  1)   /**< Determine whether the wide mode selection page is entered from hotkey. */
#define ICL_RECID_CUSTOM_NAV_IS_ENTER_WIDE_SELECTION_BY_KEY_SIZE (sizeof(UINT8))

#define ICL_NAV_ENTER_WIDE_SELECTION_BY_KEY     (1) /** The wide mode selection page is entered by hotkey. */
#define ICL_NAV_ENTER_WIDE_SELECTION_NOT_BY_KEY (0) /** The wide mode selection page is NOT entered by hotkey. */

#ifdef APP_NAV_CAMERA_PLUG_SUPPORT

#define ICL_RECID_CUSTOM_NAV_CAM_PLUG_STATUS    ((ICL_RECID_TYPE)  2)   /**< Determine whether the camera is plug in or not. */
#define ICL_RECID_CUSTOM_NAV_CAM_PLUG_INFO_SIZE (sizeof(UINT8))

#define ICL_CUSTOM_CAM_PLUG_IN     (1) /** The camera plug in the usb port. */
#define ICL_CUSTOM_CAM_PLUG_OUT    (0) /** The camera plug out from the usb port.  */
#endif

/* Group Network Widget */
#define ICL_GRPID_CUSTOM_NW_WIDGET           ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+4)
#define ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS ((ICL_RECID_TYPE)  1)   /**< Determine whether the Dock Ui show or not. */
#define ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS_SIZE (sizeof(UINT8))
#define ICL_RECID_CUSTOM_NW_WIDGET_APP_STATUS ((ICL_RECID_TYPE)  2)    /**< Determine whether the 3rd APP  Ui show or not. */
#define ICL_RECID_CUSTOM_NW_WIDGET_APP_STATUS_SIZE (sizeof(UINT8))

/* Group Co-exist App */
#define ICL_GRPID_CUSTOM_COEXIST_APP                                ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+5)
#define ICL_RECID_CUSTOM_COEXIST_APP_RESUME_AFTER_MENU_PAUSE        ((ICL_RECID_TYPE)  1)
#define ICL_RECID_CUSTOM_COEXIST_APP_RESUME_AFTER_MENU_PAUSE_SIZE   (sizeof(ICL_CUSTOM_RESUME_NEXT_APP_T))

/* Group MMP */
#define ICL_GRPID_CUSTOM_MMP                ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+6)
#define ICL_RECID_CUSTOM_MMP_BROWSER        ((ICL_RECID_TYPE)  1)   /**< Determine whether file browser status. */
#define ICL_RECID_CUSTOM_MMP_BROWSER_SIZE   (sizeof(UINT8))
#define ICL_RECID_CUSTOM_MMP_PLAYER         ((ICL_RECID_TYPE)  2)   /**< Determine whether photo player or video player is running. */
#define ICL_RECID_CUSTOM_MMP_PLAYER_SIZE    (sizeof(UINT8))
#define ICL_RECID_CUSTOM_MMP_AUDIO_PLAYER   ((ICL_RECID_TYPE)  3)   /**< Determine whether audio player is running. */
#define ICL_RECID_CUSTOM_MMP_PLAYER_SIZE    (sizeof(UINT8))
#define ICL_RECID_CUSTOM_MMP_MENU_FILE_LIST ((ICL_RECID_TYPE)  4)   /**< Determine whether menu file list set to play a audio file is running. */
#define ICL_RECID_CUSTOM_MMP_FILE_LIST_SIZE (sizeof(UINT8))
#define ICL_RECID_CUSTOM_MMP_IS_PLAY_VIDEO_FILE      ((ICL_RECID_TYPE)  5)   /**< Determine whether player is running set status to menu. */
#define ICL_RECID_CUSTOM_MMP_PLAY_VIDEO_FILE_SIZE    (sizeof(UINT8))
#define ICL_RECID_CUSTOM_MMP_BK_PLAYER_STATUS        ((ICL_RECID_TYPE)  6)  /* audio player status */
#define ICL_RECID_CUSTOM_MMP_BK_PLAYER_STATUS_SIZE   (sizeof(UINT32))
#define ICL_RECID_CUSTOM_MMP_EXIT_REASON             ((ICL_RECID_TYPE)  7) /* exit reason */
#define ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE       (sizeof(UINT32))
#define ICL_RECID_CUSTOM_MMP_SRC_STATUS                    ((ICL_RECID_TYPE)  8)
#define ICL_RECID_CUSTOM_MMP_SRC_STATUS_SIZE               (sizeof(UINT32))

/* Value definition of MMP_SRC_STATUS */
#define ICL_MMP_SRC_STATUS_RESUME             (MAKE_BIT_MASK_32(0))
#define ICL_MMP_SRC_STATUS_PAUSE              (MAKE_BIT_MASK_32(1))

/* Value definition of MMP BROWSER */
#define ICL_MMP_BROWSER_OFF                 (0) /**< Not in file browser. */
#define ICL_MMP_BROWSER_TOP                 (1) /**< Browse the top page. */
#define ICL_MMP_BROWSER_AUDIO               (2) /**< Browse audio files. */
#define ICL_MMP_BROWSER_PHOTO               (3) /**< Browse photo files. */
#define ICL_MMP_BROWSER_VIDEO               (4) /**< Browse video files. */
/* Value definition of MMP PLAYER */
#define ICL_MMP_PLAYER_OFF                  (0) /**< Both photo player & video player is running. */
#define ICL_MMP_PLAYER_PHOTO                (1) /**< Photo player is running. */
#define ICL_MMP_PLAYER_VIDEO                (2) /**< Video player is running. */

/* Value definition of MMP AUDIO PLAYER */
#define ICL_MMP_AUDIO_PLAYER_OFF            (0) /**< Audio player is NOT running. */
#define ICL_MMP_AUDIO_PLAYER_ON             (1) /**< Audio player is running. */

/* Value definition of MENU FILE LIST  */
#define ICL_MMP_MENU_FILE_LIST_OFF          (0) /**< Menu file list player is NOT running. */
#define ICL_MMP_MENU_FILE_LIST_ON           (1) /**< Menu file list player is running. */

#define ICL_MMP_IS_PLAY_VIDEO_FILE_FALSE    (0)
#define ICL_MMP_IS_PLAY_VIDEO_FILE_TRUE     (1)

#define ICL_MMP_BK_PLAYER_STAT_PLAY         (0)
#define ICL_MMP_BK_PLAYER_STAT_NEXT         (1)
#define ICL_MMP_BK_PLAYER_STAT_UNSUP        (2)
#define ICL_MMP_BK_PLAYER_STAT_PAUSE        (3)
#define ICL_MMP_BK_PLAYER_STAT_BlANK        (4)
#define ICL_MMP_BK_PLAYER_STAT_FAST_FWD     (5)
#define ICL_MMP_BK_PLAYER_STAT_FAST_RWD     (6)
#define ICL_MMP_BK_PLAYER_STAT_SLOW_FWD     (7)
#define ICL_MMP_BK_PLAYER_STAT_SLOW_RWD     (8)
#define ICL_MMP_BK_PLAYER_STAT_STOP         (9)
#define ICL_MMP_BK_PLAYER_STAT_CLOSE        (10)

#define ICL_RECID_CUSTOM_MMP_EXIT_REASON_UNKNOWN (0)
#define ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_USER (1)
#define ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_REMOVE_USB (2)
#define ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_REMOVE_DLNA (3)
#define ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_SHORTCUT_TO_MEDIATYPE    (4)
#define ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_NETFLIX_LAUNCH (5)


#define ICL_WIZARD_STATUS_OFF               (0)
#define ICL_WIZARD_STATUS_INIT_SETUP        (1)
#define ICL_WIZARD_STATUS_AUTO_STARTUP      (2)

/*Grop of rating enabled status*/
#define ICL_GRPID_RATING_ENABLED_STATUS             ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+7)
#define ICL_RECID_RATING_ENABLED_STATUS             ((ICL_RECID_TYPE)  1)
#define ICL_RECID_RATING_ENABLED_STATUS_SIZE        (sizeof(UINT8))

/*value rating enabled status*/
#define RATING_ENABLED_STATUS_OFF           (0)
#define RATING_ENABLED_STATUS_ON            (1)

/*Grop of E-manual status*/
#define ICL_GRPID_EMANUAL_STATUS             ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+8)
#define ICL_RECID_EMANUAL_STATUS             ((ICL_RECID_TYPE)  1)
#define ICL_RECID_EMANUAL_STATUS_SIZE        (sizeof(UINT8))

/*value rating enabled status*/
#define ICL_EMANUAL_STATUS_OFF               (0)
#define ICL_EMANUAL_STATUS_ON                (1)

/*Grop of wifi remote battery status*/
#define ICL_GRPID_WIFI_REMOTE_BATTERY_STATUS                ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+9)
#define ICL_RECID_WIFI_REMOTE_BATTERY_STATUS                ((ICL_RECID_TYPE)  1)
#define ICL_RECID_WIFI_REMOTE_BATTERYL_STATUS_SIZE          (sizeof(UINT8))

/*value rating enabled status*/
#define ICL_WIFI_REMOTE_BATTERY_STATUS_NORMAL               (0)
#define ICL_WIFI_REMOTE_BATTERY_STATUS_LOW                  (1)

#if 1
/*Group of banner CC item status*/
#define ICL_GRPID_CC_ITEM_STATUS                ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+10)
#define ICL_RECID_CC_ITEM_STATUS                ((ICL_RECID_TYPE)  1)
#define ICL_RECID_CC_ITEM_STATUS_SIZE           (sizeof(UINT8))

/*banner cc item show or hide status*/
#define ICL_CC_ITEM_STATUS_HIDE                 (0)
#define ICL_CC_ITEM_STATUS_SHOW                 (1)
#endif

/*Group of wizard status*/
#define ICL_GRPID_WIZARD_STATUS               ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+11)
#define ICL_RECID_WIZARD_STATUS               ((ICL_RECID_TYPE)  1)
#define ICL_RECID_WIZARD_STATUS_SIZE          (sizeof(UINT8))

/*value rating enabled status*/
#define ICL_WIZARD_STATUS_PAUSE               (0)
#define ICL_WIZARD_STATUS_RESUME              (1)

/* Group custom updater */
#define ICL_GRPID_CUSTOM_UPDATER                        ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+12)
#define ICL_RECID_CUSTOM_UPDATER_STATUS                 ((ICL_RECID_TYPE)  1)
#define ICL_RECID_CUSTOM_UPDATER_STATUS_SIZES           (sizeof(UINT8))

#define ICL_CUSTOM_UPDATER_NOT_FIRST_BOOT_UP                     (0) /** No UI. */
#define ICL_CUSTOM_UPDATER_FIRST_BOOT_UP                         (1) /** UI Poping up. */


/* Group Msgconvert */
#define ICL_GRPID_MSGCVT_UI_POPUP                   ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+13)
#define ICL_RECID_MSGCVT_IS_UI_POPUP                ((ICL_RECID_TYPE)  1)
#define ICL_RECID_MSGCVT_IS_UI_POPUP_SIZE           (sizeof(UINT8))

#define ICL_MSGCVT_UI_NOT_EXIST                     (0) /** No UI. */
#define ICL_MSGCVT_UI_EXIST                         (1) /** UI Poping up. */

/* Group COLOR TUNER */
#define ICL_GRPID_CUSTOM_COLOR_TUNER            ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+14)
#define ICL_RECID_CUSTOM_COLOR_TUNER_11_POINT  ((ICL_RECID_TYPE)  1)   /**< Determine whether the Dock Ui show or not. */
#define ICL_RECID_CUSTOM_COLOR_TUNER_11_POINT_SIZE (sizeof(UINT8))
#define ICL_RECID_CUSTOM_COLOR_TUNER_TEST_PATTERN   ((ICL_RECID_TYPE)  2)    /**< Determine whether the 3rd APP  Ui show or not. */
#define ICL_RECID_CUSTOM_COLOR_TUNER_TEST_PATTERN_SIZE (sizeof(UINT8))
#define ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE   ((ICL_RECID_TYPE)  3)    /**< Determine whether screen mode is show or not. */
#define ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE_SIZE (sizeof(UINT8))

/* Group Dyanmic TOS download */
#ifdef APP_DYNAMIC_TOS_SUPPORT
#define ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS      ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+15)
#define ICL_RECID_TOS_DOWNLOAD_ITEM_STATUS      ((ICL_RECID_TYPE)  1)
#define ICL_RECID_TOS_DOWNLOAD_ITEM_STATUS_SIZE (sizeof(UINT8))
#define ICL_RECID_VPP_DOWNLOAD_ITEM_STATUS      ((ICL_RECID_TYPE)  2)
#define ICL_RECID_VPP_DOWNLOAD_ITEM_STATUS_SIZE (sizeof(UINT8))

#define ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS  ((ICL_RECID_TYPE)  3)
#define ICL_RECID_POLICY_DOWNLOAD_ITEM_STATUS_SIZE  (sizeof(UINT32))


/* TOS download item status*/
#define ICL_TOS_DOWNLOAD_ITEM_STOP              (0)
#define ICL_TOS_DOWNLOAD_ITEM_RUNNING           (1)

#define ICL_VPP_DOWNLOAD_ITEM_STOP              (0)
#define ICL_VPP_DOWNLOAD_ITEM_RUNNING           (1)

#define ICL_POLICY_DOWNLOAD_ITEM_STOP               (0)
#define ICL_POLICY_DOWNLOAD_ITEM_RUNNING            (1)

#endif

/* Group PQ change status */
#define ICL_GRPID_PQ_CHANGE_STATUS              ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+16)
#define ICL_RECID_PQ_CHANGE_STATUS              ((ICL_RECID_TYPE)  1)
#define ICL_RECID_PQ_CHANGE_STATUS_SIZE         (sizeof(UINT8))

/* PQ change type */
#define ICL_PQ_CHANGE_NOTHING                   (0)
#define ICL_PQ_CHANGE_PRESET_PQ                 (1)
#define ICL_PQ_CHANGE_COLOR_TEMP                (2)

/* Group custom flag change */
#define ICL_GRPID_CUSTOM_FLAG_CHANGE            ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+17)
#define ICL_RECID_CUSTOM_FLAG_CHANGE            ((ICL_RECID_TYPE)  1)
#define ICL_RECID_CUSTOM_FLAG_CHANGE_SIZE       (sizeof(UINT8))
#define ICL_RECID_CUSTOM_AUD_FMT_DTS_FLAG       ((ICL_RECID_TYPE)  2)
#define ICL_RECID_CUSTOM_AUD_FMT_DTS_FLAG_SIZE  (sizeof(UINT8))

#define ICL_GRPID_CUSTOM_TVAP_TOS_STATUS             ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+18)
#define ICL_RECID_CUSTOM_TVAP_TOS_STATUS             ((ICL_RECID_TYPE)  1)
#define ICL_RECID_CUSTOM_TVAP_TOS_STATUS_TYPE_SIZE   (sizeof(UINT8))
#define ICL_TOS_SET                                  ((ICL_RECID_TYPE)  1)
#define ICL_PRI_SET                                  ((ICL_RECID_TYPE)  2)

/* power mode flag */
#define ICL_GRPID_CUSTOM_POWER_MODE             ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+19)
#define ICL_RECID_CUSTOM_POWER_MODE             ((ICL_RECID_TYPE)  1)
#define ICL_RECID_CUSTOM_POWER_MODE_SIZE        (sizeof(UINT8))

#define ICL_CUSTOM_POWER_MODE_ECO               ((UINT8)  0)
#define ICL_CUSTOM_POWER_MODE_QUICK_START       ((UINT8)  1)

/* cast ipts select */
#define ICL_GRPID_CAST_SRC_STATUS               ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+20)
#define ICL_RECID_CAST_SRC_STATUS               ((ICL_RECID_TYPE)  1)
#define ICL_RECID_CAST_SRC_STATUS_SIZE          (sizeof(UINT8))

#define ICL_RECID_CAST_SRC_STATUS_TRUE          ((UINT8) 1)
#define ICL_RECID_CAST_SRC_STATUS_TRUE_REAL     ((UINT8) 3)
#define ICL_RECID_CAST_SRC_STATUS_TRUE_VTRL     ((UINT8) 5)
#define ICL_RECID_CAST_SRC_STATUS_FALSE         ((UINT8) 0)

/* test pattern */
#define ICL_GRPID_TEST_PATTERN_STATUS           ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+21)
#define ICL_RECID_TEST_PATTERN_STATUS           ((ICL_RECID_TYPE)  1)
#define ICL_RECID_TEST_PATTERN_STATUS_SIZE      (sizeof(UINT8))

#define ICL_RECID_TEST_PATTERN_STATUS_DISABLE               ((UINT8) 0)
#define ICL_RECID_TEST_PATTERN_STATUS_ENABLE                ((UINT8) 1)
#define ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ            ((UINT8) 2)

#define ICL_GRPID_DEMO_STATUS                  ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+22)
#define ICL_RECID_DEMO_STATUS                  ((ICL_RECID_TYPE)  1)
#define ICL_RECID_DEMO_STATUS_SIZE             (sizeof(UINT8))

/* test pattern */
#define ICL_GRPID_TUNER_SETUP_STATUS           ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+23)
#define ICL_RECID_TUNER_SETUP_STATUS           ((ICL_RECID_TYPE)  1)
#define ICL_RECID_TUNER_SETUP_STATUS_SIZE      (sizeof(UINT8))

#define ICL_RECID_TUNER_SETUP_STATUS_COMPLETE           ((UINT8) 0)
#define ICL_RECID_TUNER_SETUP_STATUS_PROGRESS           ((UINT8) 1)
#define ICL_RECID_TUNER_SETUP_STATUS_CANCEL             ((UINT8) 2)
#define ICL_RECID_TUNER_SETUP_STATUS_ABORT              ((UINT8) 3)

#define ICL_GRPID_DOLBY_VISION_STATUS                  ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+24)
#define ICL_RECID_DOLBY_VISION_STATUS                  ((ICL_RECID_TYPE)  1)
#define ICL_RECID_DOLBY_VISION_STATUS_SIZE             (sizeof(UINT8))

/* custom flag change items */
#define ICL_RECID_CUSTOM_NOTHING_CHANGE         (0)
#define ICL_RECID_CUSTOM_INPUT_NAME_CHANGE      (1)
#define RECID_CUSTOM_DTS_STATUS_OFF             (0)
#define RECID_CUSTOM_DTS_STATUS_ON              (1)

#define ICL_GRPID_BGM_POWER                    ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+25)
#define ICL_RECID_BGM_POWER_DOWN_MODE          ((ICL_RECID_TYPE)  1)
#define ICL_RECID_BGM_POWER_DOWN_MODE_SIZE     (sizeof(UINT8))

/*Value define for bgm power down mode*/
#define BGM_POWER_DOWN_MODE_NORMAL                   (0)
#define BGM_POWER_DOWN_MODE_FORCE_REBOOT             (1)
#define BGM_POWER_DOWN_MODE_LAST_ENTRY               (2)

#define ICL_GRPID_ULI_DOWNLOAD_STATUS                 ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START + 26)
#define ICL_RECID_ULI_DOWNLOAD_STATUS_TYPE            ((ICL_RECID_TYPE)  1)
#define ICL_RECID_ULI_DOWNLOAD_STATUS_SIZE            (sizeof(UINT8))

#define ICL_ULI_DOWNLOAD_STATUS_NONE                       ((UINT8)0)
#define ICL_ULI_DOWNLOAD_STATUS_DONE                       ((UINT8)1)

#define ICL_GRPID_PICTURE_EDIT_TYPE_STATUS                  ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+27)
#define ICL_RECID_PICTURE_EDIT_TYPE_STATUS                  ((ICL_RECID_TYPE)  1)
#define ICL_RECID_PICTURE_EDIT_TYPE_SIZE                    (sizeof(UINT8))

#define ICL_GRPID_HDR_TYPE_STATUS                  ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+28)
#define ICL_RECID_HDR_TYPE_STATUS                  ((ICL_RECID_TYPE)  1)
#define ICL_RECID_HDR_TYPE_SIZE                    (sizeof(UINT8))

#define ICL_GRPID_3RD_PLAY_STATUS                  ((ICL_GRPID_TYPE)  ICL_GROUP_ID_CUSTOM_START+29)
#define ICL_RECID_3RD_PLAY_STATUS                  ((ICL_RECID_TYPE)  1)
#define ICL_RECID_3RD_PLAY_SIZE                    (sizeof(UINT8))


#define ICL_PICTURE_EDIT_LOCK_PIC                   ((UINT8)1)
#define ICL_PICTURE_EDIT_COPY_PIC                   ((UINT8)2)
#define ICL_PICTURE_EDIT_INVALID                    ((UINT8)255)

/*-----------------------------------------------------------------------------
    Priority definition for each client

    Naming rule:
    ICL_PRIORITY_[Group Name]_FOR_[What Client]        (Priority Value)

-----------------------------------------------------------------------------*/
#define ICL_PRIORITY_REMOVABLE_DEVICE_FOR_APP_USB_UPGRADE       (128)
#define ICL_PRIORITY_REMOVABLE_DEVICE_FOR_APP_MULTIMEDIA        (129)

#define ICL_PRIORITY_CEC_FOR_DEV_LST_UPDATE                     (128)

#define ICL_PRIORITY_CI_FOR_CI_STATUS_UPDATE                    (128)

#define ICL_PRIORITY_AUD_ONLY_FOR_AUO_ONLY_SETTING_UPDATE       (128)
#define ICL_PRIORITY_AUDIO_FOCUS                                (128)

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 a_icl_custom_set_reset_type (
    UINT8               ui1_reset_type
    ) ;

extern INT32 a_icl_custom_get_reset_type (
    UINT8*              pui1_reset_type
    ) ;
extern INT32 a_icl_custom_get_enter_wide_selection_by_key (UINT8* pui1_val);
extern INT32 a_icl_custom_set_enter_wide_selection_by_key (UINT8 ui1_val);
extern INT32 a_icl_custom_set_nw_widget_status(ICL_CUSTOM_NW_WIDGET_T e_widget_type, UINT8 ui1_status);
extern INT32 a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_T e_widget_type, UINT8* pui1_status);

extern INT32 a_icl_custom_set_next_resume_app(ICL_CUSTOM_RESUME_NEXT_APP_T e_next_app);
extern INT32 a_icl_custom_get_next_resume_app(ICL_CUSTOM_RESUME_NEXT_APP_T *pe_next_app);
#ifdef APP_NAV_CAMERA_PLUG_SUPPORT
extern INT32 a_icl_custom_set_camera_plug_status (UINT8 ui1_val);
extern INT32 a_icl_custom_get_camera_plug_status (UINT8* pui1_val);
#endif

extern INT32 a_icl_custom_set_is_ui_popup (UINT8 ui1_val);
extern INT32 a_icl_custom_set_cust_updater_status (UINT8 ui1_val);
extern INT32 a_icl_custom_get_cust_updater_status (UINT8* pui1_val);

extern INT32 a_icl_custom_set_pq_chg_status (UINT8 ui1_val);
extern INT32 a_icl_custom_get_pq_chg_status (UINT8* pui1_val);

extern INT32 a_icl_custom_set_tos_info (UINT8 ui1_val);

extern INT32 a_icl_custom_get_power_mode (UINT8* pui1_val);
extern INT32 a_icl_custom_set_power_mode (UINT8 ui1_val);

extern INT32 a_icl_custom_set_cast_src_status(UINT8 ui1_val);
extern INT32 a_icl_custom_get_cast_src_status(UINT8 *pui1_val);

extern INT32 a_icl_custom_set_test_pattern_status(UINT8 ui1_val);
extern INT32 a_icl_custom_get_test_pattern_status(UINT8 *pui1_val);

extern INT32 a_icl_custom_set_demo_status(UINT8 ui1_val);
extern INT32 a_icl_custom_get_demo_status(VOID);

extern INT32 a_icl_custom_set_tuner_setup_status(UINT8 ui1_val);
extern INT32 a_icl_custom_get_tuner_setup_status(UINT8 *pui1_val);

extern INT32 a_icl_custom_set_dolby_vision_status(UINT8 ui1_val);
extern INT32 a_icl_custom_get_dolby_vision_status(VOID);

extern INT32 a_icl_set_bgm_power_down_mode (UINT8 ui1_val);
extern INT32 a_icl_get_bgm_power_down_mode (UINT8* pui1_val);

extern INT32 a_icl_set_uli_download_status (UINT8 ui1_val);
extern INT32 a_icl_get_uli_download_status (UINT8* pui1_val);

INT32 a_icl_set_picture_edit_type_status (UINT8 ui1_val);
INT32 a_icl_get_picture_edit_type_status (UINT8* pui1_val);
INT32 a_icl_set_hdr_type_status (UINT8 ui1_val);
INT32 a_icl_get_hdr_type_status (UINT8* pui1_val);
INT32 a_icl_set_3rd_play_status (UINT8 ui1_val);
INT32 a_icl_get_3rd_play_status (UINT8* pui1_val);

#endif /* A_ICL_CUSTOM_H_ */

