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
 * $RCSfile: acfg_custom.h,v $
 * $Revision: #4 $
 * $Date: 2015/06/22 $
 * $Author: heyi.wang $V
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the internal header file for APP CFG
 *---------------------------------------------------------------------------*/


#ifndef _ACFG_CUSTOM_H_
#define _ACFG_CUSTOM_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "res/app_util/config/acfg_cust_video.h"
#include "res/app_util/config/acfg_cust_audio.h"
#include "res/app_util/config/acfg_cust_vga.h"
#include "res/app_util/config/acfg_cust_mmp.h"
#include "res/app_util/config/acfg_cust_network.h"
#include "res/app_util/config/acfg_cust_hotel.h"
//#include "res/app_util/config/acfg_cust_factory.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "res/app_util/config/acfg_cust_eep_assign.h"
#include "u_drv_cust.h"
#include "wizard/wzd_util.h"
#include "wizard_anim/a_wzd.h"

/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/

#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))
#define BUILD_ERROR_IF_TRUE(condition) BUILD_BUG_ON((condition))

//=====================================================================================
//#ifdef MT5695_MODEL
    #define ACFG_CUST_VRR_INPUT_DO_FREESYNC_JOB     1
//#else
//    #define ACFG_CUST_VRR_INPUT_DO_FREESYNC_JOB     0
//#endif

// For MVP-3661
#define ACFG_CUST_MEMC_NEW_METHOD   1

//=====================================================================================

#define ACFG_DEBUG_SYS_PIN(x)    //x

#define ACFG_DEBUG_NR_DEFAULT(x)   // x

#define ACFG_DEBUG_OVER_SCAN(x)   // x

//=====================================================================================

#define ODM_ID_Amtran     1
#define ODM_ID_TPV        2
#define ODM_ID_Wistron    3
#define ODM_ID_Foxconn    4
#define ODM_ID_BOE        5
#define ODM_ID_Innolux    6
#define ODM_ID_KONKA      7

//=====================================================================================
#define ACFG_CUST_DEBUG_ID_CAL_OFFSET  0
#if(ACFG_CUST_DEBUG_ID_CAL_OFFSET)
extern UINT16 g_AcfgCust_u16DebugID_CalOffset;
#endif
//----------------------------------------------------------------------------
#define ACFG_DBG_PICT_BACKLIGHT     0x00000001 // Debug Backlight
#define ACFG_DBG_PICT_MODE          0x00000002 // Debug PictureMode
#define ACFG_DBG_PICT_VIEW_ANGLE    0x00000004 // Debug ViewAngle
#define ACFG_DBG_PICT_FULL_COLOR444 0x00000008 // Debug Full Color 444
#define ACFG_DBG_PICT_FILM_MODE     0x00000010 // Debug Adv-Picture.FilmMode
#define ACFG_DBG_PICT_CLEAR_ACTION  0x00000020 // Debug ClearAction
#define ACFG_DBG_PICT_LIGHT_SENSOR  0x00000040 // Debug LightSensor
#define ACFG_DBG_PICT_LOCAL_CONTRAST 0x00000080 // Local contrast
#define ACFG_DBG_PICT_GAME          0x00000100 // GLL(Game Low Latency)
#define ACFG_DBG_PICT_MEMC          0x00000200 // MEMC
#define ACFG_DBG_PICT_NR            0x00000400 // NR
#define ACFG_DBG_PICT_BLACK_DETAIL  0x00000800 // Black_detail(contrast_en)



extern UINT32 g_ACFG_u32DebugPicture;

#define ACFG_DEBUG_PICTURE_LOG( mask, log) do { \
    if( g_ACFG_u32DebugPicture &(mask) ) \
    {\
        log ; \
    }\
} while(0)

//----------------------------------------------------------------------------
// APP_CFG_RECID_DISP_BACK_LIGHT
#define ACFG_DEBUG_BACKLIGHT(x) do { \
    if(g_ACFG_u32DebugPicture&ACFG_DBG_PICT_BACKLIGHT) \
    { \
        x; \
    } \
} while(0)
//----------------------------------------------------------------------------
//
#define ACFG_DEBUG_PIC_MODE(x) do { \
    if(g_ACFG_u32DebugPicture&ACFG_DBG_PICT_MODE) \
    { \
        x; \
    } \
} while(0)
//----------------------------------------------------------------------------
// APP_CFG_RECID_VID_EN_VIEW_ANGLE
#define ACFG_DEBUG_VIEW_ANGLE(x) do { \
    if(g_ACFG_u32DebugPicture&ACFG_DBG_PICT_VIEW_ANGLE) \
    { \
        x; \
    } \
} while(0)

//=================================================================================

#define ENABLE_FULL_COLOR_444   1

// MVV-8021:
#define ENABLE_COLOR_444_TO_422_NEW_SPEC  1 // 2021

// APP_CFG_RECID_VID_CUST_FULL_COLOR_444
#define ACFG_DEBUG_FULL_COLOR444(x) do { \
    if(g_ACFG_u32DebugPicture&ACFG_DBG_PICT_FULL_COLOR444) \
    { \
        x; \
    } \
} while(0)

//=================================================================================
//#define ACFG_DEBUG_GAME(x)      x
#define ACFG_DEBUG_GAME(x) do { \
    if(g_ACFG_u32DebugPicture&ACFG_DBG_PICT_GAME) \
    { \
        x; \
    } \
} while(0)
//=================================================================================
// For OLED
// MVP-3909
#define ACFG_CUST_PEAK_LUMI_NEW_SPEC    1

#if 0
    #define ACFG_DEBUG_OLED_LUMI(x)     x
#else
    #define ACFG_DEBUG_OLED_LUMI(x) do { \
        if(g_ACFG_u32DebugPicture&ACFG_DBG_PICT_BACKLIGHT) \
        { \
            x; \
        } \
    } while(0)
#endif
//=================================================================================
// VRR
#define ACFG_CUST_VRR_SET_DRIVER_BY_PORT    1
//=================================================================================

// 2021-07-20:MVP-4156/MVP-4669
// 1. DV(non-Game)
//   UI GLL grey out and display "OFF",
//   set driver GAME_MODE=off
//   (Dolby Vision don't care about ALLM)
// 2. DV(Game)
//   UI GLL grey out and display "On",
//   set driver GAME_MODE=on
//
#define VZO_DV__GLL_CONTROL_BY_DV_GAME  1
//=================================================================================

#define ACFG_BLUE_MUTE_DEF          ((UINT8)  FALSE)
#define APP_CFG_CH_LST_CHECK_INSERT_FAKE_BY_FUNCTION
#define ACFG_NO_LEAVE_FACTORY_MODE_ON_POWER_OFF
#define ACFG_USE_UNIVERSAL_PASSWORD
#define APP_CFG_MODIFY_PIC_QLT_SETTINGS_DIRECTLY
#define WATCH_TIME_MULTIPLE  2     /* how many minutes of the timeout of the following timer*/
#define ACFG_TOTAL_WATCH_TIME_CUSTOM_TIMER_DELAY (60000*WATCH_TIME_MULTIPLE)   /* usually two minutes */
#define ACFG_TOTAL_USER_WATCH_TIME_CUSTOM_TIMER_DELAY   (60000*WATCH_TIME_MULTIPLE)   /*usually two minutes */
#define ACFG_TOTAL_NO_SIGNAL_MSG_TIME_CUSTOM_TIMER_DELAY (1000) /* usually one second */

#ifndef APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE
#define APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE                     ((UINT8)   0)
#endif

#ifndef APP_CFG_CAST_TV_STATUS_CAST_MODE
#define APP_CFG_CAST_TV_STATUS_CAST_MODE                         ((UINT8)   1)
#endif

/* Return on error */
#define ACFG_CUST_CHK_FAIL(_ret)                                      \
do{                                                                   \
if (_ret < 0)                                                         \
{                                                                     \
    DBG_ERROR(("<ACFG> Return fail:%d\r\n", _ret));                   \
    return _ret;                                                      \
}                                                                     \
}while(FALSE)

#define IDX_CUSTOM_TIMEZONE_IDX             IDX_CUSTOM_0    /* Time zone. */
#define IDX_CUSTOM_DCR_IDX                  IDX_CUSTOM_1
#define IDX_CUSTOM_LIGHT_SENSOR_IDX         IDX_CUSTOM_2
#define IDX_CUSTOM_ACC                      IDX_CUSTOM_3
#define IDX_CUSTOM_DCC                      IDX_CUSTOM_4
#define IDX_CUSTOM_ADDITIONAL_SCAN          IDX_CUSTOM_5
#define IDX_CUSTOM_ANA_AUD_OUT              IDX_CUSTOM_6
#define IDX_CUSTOM_INP_NAME_1               IDX_CUSTOM_7
#define IDX_CUSTOM_INP_NAME_2               IDX_CUSTOM_8
#define IDX_CUSTOM_INP_NAME_3               IDX_CUSTOM_9
#define IDX_CUSTOM_INP_NAME_4               IDX_CUSTOM_10
#define IDX_CUSTOM_INP_NAME_5               IDX_CUSTOM_11
#define IDX_CUSTOM_INP_NAME_6               IDX_CUSTOM_12
#define IDX_CUSTOM_INP_NAME_7               IDX_CUSTOM_13
#define IDX_CUSTOM_INP_NAME_8               IDX_CUSTOM_14
#define IDX_CUSTOM_INP_NAME_9               IDX_CUSTOM_15
#define IDX_CUSTOM_INP_NAME_10              IDX_CUSTOM_16
#define IDX_CUSTOM_OP_MODE                  IDX_CUSTOM_17   /* Retail or Home. */
#define IDX_CUSTOM_POSTAL_CODE              IDX_CUSTOM_18
#define IDX_CUSTOM_ULPK_FLAG                IDX_CUSTOM_19
#define IDX_CUSTOM_RETAIL_MODE              IDX_CUSTOM_20
#define IDX_CUSTOM_WZD_SUB_PAGE_IDX         IDX_CUSTOM_21   /* For wizard sub page index. */
#define IDX_CUSTOM_PLF_OPT_3D_SUPPORT       IDX_CUSTOM_22
#define IDX_CUSTOM_PLF_OPT_PIP_SUPPORT      IDX_CUSTOM_23
#define IDX_CUSTOM_PLF_OPT_BT_SUPPORT       IDX_CUSTOM_24
#define IDX_CUSTOM_PLF_OPT_03               IDX_CUSTOM_25
#define IDX_CUSTOM_PLF_OPT_04               IDX_CUSTOM_26
#define IDX_CUSTOM_PLF_OPT_05               IDX_CUSTOM_27
#define IDX_CUSTOM_PLF_OPT_06               IDX_CUSTOM_28
#define IDX_CUSTOM_PLF_OPT_07               IDX_CUSTOM_29
#define IDX_CUSTOM_PLF_OPT_08               IDX_CUSTOM_30
#define IDX_CUSTOM_PLF_OPT_09               IDX_CUSTOM_31
#define IDX_CUSTOM_PLF_OPT_10               IDX_CUSTOM_32
#define IDX_CUSTOM_PLF_OPT_11               IDX_CUSTOM_33
#define IDX_CUSTOM_PLF_OPT_12               IDX_CUSTOM_34

#define IDX_CUSTOM_UPDATER_COMPLETED        IDX_CUSTOM_35
#define IDX_CUSTOM_AUTO_POWER_OFF           IDX_CUSTOM_36
#define IDX_CUSTOM_H_SIZE                   IDX_CUSTOM_37
#define IDX_CUSTOM_V_SIZE                   IDX_CUSTOM_38
#define IDX_CUSTOM_DIMMING                  IDX_CUSTOM_39
#define IDX_CUSTOM_COUNTRY_CODE             IDX_CUSTOM_40

#define IDX_CUSTOM_MMP_PHOTO_RECUR_PARSING  IDX_CUSTOM_41
#define IDX_CUSTOM_MMP_AUDIO_RECUR_PARSING  IDX_CUSTOM_42
#define IDX_CUSTOM_MMP_VIDEO_RECUR_PARSING  IDX_CUSTOM_43
#define IDX_CUSTOM_MMP_PHOTO_SET_INFO       IDX_CUSTOM_44
#define IDX_CUSTOM_MMP_PHOTO_SORT           IDX_CUSTOM_45
#define IDX_CUSTOM_MMP_AUDIO_SORT           IDX_CUSTOM_46
#define IDX_CUSTOM_MMP_VIDEO_SORT           IDX_CUSTOM_47

#define IDX_CUSTOM_LED_LOGO_CTRL            IDX_CUSTOM_48

#define IDX_CUSTOM_BT_DEVICE_SETUP_IDX_AV           (IDX_CUSTOM_49)
#define IDX_CUSTOM_BT_DEVICE_SETUP_IDX_COMP1        (IDX_CUSTOM_50)
#define IDX_CUSTOM_BT_DEVICE_SETUP_IDX_COMP2        (IDX_CUSTOM_51)
#define IDX_CUSTOM_BT_DEVICE_SETUP_IDX_HDMI1        (IDX_CUSTOM_52)
#define IDX_CUSTOM_BT_DEVICE_SETUP_IDX_HDMI2        (IDX_CUSTOM_53)
#define IDX_CUSTOM_BT_DEVICE_SETUP_IDX_HDMI3        (IDX_CUSTOM_54)
#define IDX_CUSTOM_BT_DEVICE_SETUP_IDX_HDMI4        (IDX_CUSTOM_55)
#define IDX_CUSTOM_BT_DEVICE_SETUP_IDX_RGB          (IDX_CUSTOM_56)
#define IDX_CUSTOM_BT_AUDIO_DEVICE_SETUP            (IDX_CUSTOM_57)

#define IDX_CUSTOM_BLUETOOTH_AUDIO_DEVICE_CONTROL   (IDX_CUSTOM_58)

#define IDX_CUSTOM_BLUETOOTH_AUDIO                  (IDX_CUSTOM_59)

/* the following define will be used for cust video
  * item  first part: IDX_CUSTOM_60 ~ IDX_CUSTOM_99
  * second part(cust misc): IDX_CUSTOM_200 +  ~ IDX_CUSTOM_207
  */
    /*video new & will begin from 16+APP_CFG_RECID_VID_CUSTOM_BASE*/

    /* custom pic mode name should be store by src*/
#define IDX_CUST_PIC_MODE_0_NAME      (IDX_CUSTOM_60)  /* Picture Mode Name */
#define IDX_CUST_PIC_MODE_1_NAME      (IDX_CUSTOM_61)  /* Picture Mode Name */
#define IDX_CUST_PIC_MODE_2_NAME      (IDX_CUSTOM_62)  /* Picture Mode Name */
#define IDX_CUST_PIC_MODE_3_NAME      (IDX_CUSTOM_63)  /* Picture Mode Name */
#define IDX_CUST_PIC_MODE_4_NAME      (IDX_CUSTOM_64)  /* Picture Mode Name */
#define IDX_CUST_PIC_MODE_5_NAME      (IDX_CUSTOM_65)  /* Picture Mode Name */
#define IDX_CUST_PIC_MODE_6_NAME      (IDX_CUSTOM_66)  /* Picture Mode Name */
#define IDX_CUST_PIC_MODE_7_NAME      (IDX_CUSTOM_67)  /* Picture Mode Name */

    /* Should be by src & pic*/
#define IDX_CUST_PIC_EXIST_STATUS     (IDX_CUSTOM_68)

    /* lock status & pwd should be globe*/
#define IDX_CUST_PIC_LOCK_STATUS      (IDX_CUSTOM_69)
#define IDX_CUST_PIC_LOCK_PWD         (IDX_CUSTOM_70)


    /* Video Quality */
    /* Color Temp */
#define IDX_CLR_HUE_R                 (IDX_CUSTOM_71)  /* Color Gain R */
#define IDX_CLR_HUE_G                 (IDX_CUSTOM_72)  /* Color Gain G */
#define IDX_CLR_HUE_B                 (IDX_CUSTOM_73)  /* Color Gain B */
#define IDX_CLR_SAT_R                 (IDX_CUSTOM_74)  /* Color Offset R */
#define IDX_CLR_SAT_G                 (IDX_CUSTOM_75)  /* Color Offset G */
#define IDX_CLR_SAT_B                 (IDX_CUSTOM_76)  /* Color Offset B */
#define IDX_CLR_BRI_R                 (IDX_CUSTOM_77)  /* Color Offset R */
#define IDX_CLR_BRI_G                 (IDX_CUSTOM_78)  /* Color Offset G */
#define IDX_CLR_BRI_B                 (IDX_CUSTOM_79)  /* Color Offset B */
#define IDX_CLR_HUE_C                 (IDX_CUSTOM_80)  /* Color Gain R */
#define IDX_CLR_HUE_M                 (IDX_CUSTOM_81)  /* Color Gain G */
#define IDX_CLR_HUE_Y                 (IDX_CUSTOM_82)  /* Color Gain B */
#define IDX_CLR_SAT_C                 (IDX_CUSTOM_83)  /* Color Offset R */
#define IDX_CLR_SAT_M                 (IDX_CUSTOM_84)  /* Color Offset G */
#define IDX_CLR_SAT_Y                 (IDX_CUSTOM_85)  /* Color Offset B */
#define IDX_CLR_BRI_C                 (IDX_CUSTOM_86)  /* Color Offset R */
#define IDX_CLR_BRI_M                 (IDX_CUSTOM_87)  /* Color Offset G */
#define IDX_CLR_BRI_Y                 (IDX_CUSTOM_88)  /* Color Offset B */
#define IDX_REDUCE_BLUR               (IDX_CUSTOM_89)
#define IDX_RED                       (IDX_CUSTOM_90)
#define IDX_GREEN                     (IDX_CUSTOM_91)
#define IDX_BLUE                      (IDX_CUSTOM_92)

/* IDX_CUSTOM_93 ~ IDX_CUSTOM_99 define in Acfg_cust_factory_vizio.h */
/* IDX_CUSTOM_100 ~ IDX_CUSTOM_133 define in Acfg_cust_factory.h */

/* cust misc*/
#define IDX_CUST_AUD_MODE_EXIST       (IDX_CUSTOM_200)
#define IDX_CUST_NW_REG_STATUS        (IDX_CUSTOM_201)
#define IDX_11_POINT_GAIN             (IDX_CUSTOM_202)
#define IDX_11_POINT_GAIN_RED         (IDX_CUSTOM_203)
#define IDX_11_POINT_GAIN_GREEN       (IDX_CUSTOM_204)
#define IDX_11_POINT_GAIN_BLUE        (IDX_CUSTOM_205)
#define IDX_PRE_PIC_CHG               (IDX_CUSTOM_206)

/* Should be by src & pic*/
#define IDX_CUST_PIC_COPY_BASE        (IDX_CUSTOM_207)

/* CLR cust gain offset for app*/
#define IDX_CUST_CLR_GAIN_R           (IDX_CUSTOM_208)
#define IDX_CUST_CLR_GAIN_G           (IDX_CUSTOM_209)
#define IDX_CUST_CLR_GAIN_B           (IDX_CUSTOM_210)
#define IDX_CUST_CLR_OFFSET_R         (IDX_CUSTOM_211)
#define IDX_CUST_CLR_OFFSET_G         (IDX_CUSTOM_212)
#define IDX_CUST_CLR_OFFSET_B         (IDX_CUSTOM_213)
#define IDX_CLR_TEMP_CHG              (IDX_CUSTOM_215)

/*TV NAME*/
#define IDX_CUST_TV_NAME              (IDX_CUSTOM_216)

/*BOOTUP ASSISTANT FLAG*/
#define IDX_CUST_BOOTUP_ASSISTANT     (IDX_CUSTOM_217)

/*Audio mode*/
#define IDX_CUST_AUDIO_MODE           (IDX_CUSTOM_218)

/* Reserve Field */
#define IDX_CUSTOM_RSERVE_UI1_0       (IDX_CUSTOM_150)
#define IDX_CUSTOM_RSERVE_UI1_1       (IDX_CUSTOM_RSERVE_UI1_0 + 1)
#define IDX_CUSTOM_RSERVE_UI1_2       (IDX_CUSTOM_RSERVE_UI1_0 + 2)
#define IDX_CUSTOM_RSERVE_UI1_3       (IDX_CUSTOM_RSERVE_UI1_0 + 3)
#define IDX_CUSTOM_RSERVE_UI1_4       (IDX_CUSTOM_RSERVE_UI1_0 + 4)
#define IDX_CUSTOM_RSERVE_UI1_5       (IDX_CUSTOM_RSERVE_UI1_0 + 5)
#define IDX_CUSTOM_RSERVE_UI1_6       (IDX_CUSTOM_RSERVE_UI1_0 + 6)
#define IDX_CUSTOM_RSERVE_UI1_7       (IDX_CUSTOM_RSERVE_UI1_0 + 7)
#define IDX_CUSTOM_RSERVE_UI1_8       (IDX_CUSTOM_RSERVE_UI1_0 + 8)
#define IDX_CUSTOM_RSERVE_UI1_9       (IDX_CUSTOM_RSERVE_UI1_0 + 9)
#define IDX_CUSTOM_RSERVE_UI1_10      (IDX_CUSTOM_RSERVE_UI1_0 + 10)
#define IDX_CUSTOM_RSERVE_UI1_11      (IDX_CUSTOM_RSERVE_UI1_0 + 11)
#define IDX_CUSTOM_RSERVE_UI1_12      (IDX_CUSTOM_RSERVE_UI1_0 + 12)
#define IDX_CUSTOM_RSERVE_UI1_13      (IDX_CUSTOM_RSERVE_UI1_0 + 13)
#define IDX_CUSTOM_RSERVE_UI1_14      (IDX_CUSTOM_RSERVE_UI1_0 + 14)
#define IDX_CUSTOM_RSERVE_UI1_15      (IDX_CUSTOM_RSERVE_UI1_0 + 15)
#define IDX_CUSTOM_RSERVE_UI1_16      (IDX_CUSTOM_RSERVE_UI1_0 + 16)
#define IDX_CUSTOM_RSERVE_UI1_17      (IDX_CUSTOM_RSERVE_UI1_0 + 17)
#define IDX_CUSTOM_RSERVE_UI1_18      (IDX_CUSTOM_RSERVE_UI1_0 + 18)
#define IDX_CUSTOM_RSERVE_UI1_19      (IDX_CUSTOM_RSERVE_UI1_0 + 19)
#define IDX_CUSTOM_RSERVE_UI1_20      (IDX_CUSTOM_RSERVE_UI1_0 + 20)
#define IDX_CUSTOM_RSERVE_UI1_21      (IDX_CUSTOM_RSERVE_UI1_0 + 21)
#define IDX_CUSTOM_RSERVE_UI1_22      (IDX_CUSTOM_RSERVE_UI1_0 + 22)
#define IDX_CUSTOM_RSERVE_UI1_23      (IDX_CUSTOM_RSERVE_UI1_0 + 23)
#define IDX_CUSTOM_RSERVE_UI1_24      (IDX_CUSTOM_RSERVE_UI1_0 + 24)
#define IDX_CUSTOM_RSERVE_UI1_25      (IDX_CUSTOM_RSERVE_UI1_0 + 25)
#define IDX_CUSTOM_RSERVE_UI1_26      (IDX_CUSTOM_RSERVE_UI1_0 + 26)
#define IDX_CUSTOM_RSERVE_UI1_27      (IDX_CUSTOM_RSERVE_UI1_0 + 27)
#define IDX_CUSTOM_RSERVE_UI1_28      (IDX_CUSTOM_RSERVE_UI1_0 + 28)
#define IDX_CUSTOM_RSERVE_UI1_29      (IDX_CUSTOM_RSERVE_UI1_0 + 29)

#define IDX_CUSTOM_RSERVE_UI2_0       (IDX_CUSTOM_RSERVE_UI1_0 + 30)
#define IDX_CUSTOM_RSERVE_UI2_1       (IDX_CUSTOM_RSERVE_UI1_0 + 31)
#define IDX_CUSTOM_RSERVE_UI2_2       (IDX_CUSTOM_RSERVE_UI1_0 + 32)
#define IDX_CUSTOM_RSERVE_UI2_3       (IDX_CUSTOM_RSERVE_UI1_0 + 33)
#define IDX_CUSTOM_RSERVE_UI2_4       (IDX_CUSTOM_RSERVE_UI1_0 + 34)
#define IDX_CUSTOM_RSERVE_UI2_5       (IDX_CUSTOM_RSERVE_UI1_0 + 35)
#define IDX_CUSTOM_RSERVE_UI2_6       (IDX_CUSTOM_RSERVE_UI1_0 + 36)
#define IDX_CUSTOM_RSERVE_UI2_7       (IDX_CUSTOM_RSERVE_UI1_0 + 37)
#define IDX_CUSTOM_RSERVE_UI2_8       (IDX_CUSTOM_RSERVE_UI1_0 + 38)
#define IDX_CUSTOM_RSERVE_UI2_9       (IDX_CUSTOM_RSERVE_UI1_0 + 39)

#define IDX_CUSTOM_RSERVE_UI4_0       (IDX_CUSTOM_RSERVE_UI1_0 + 40)
#define IDX_CUSTOM_RSERVE_UI4_1       (IDX_CUSTOM_RSERVE_UI1_0 + 41)
#define IDX_CUSTOM_RSERVE_UI4_2       (IDX_CUSTOM_RSERVE_UI1_0 + 42)
#define IDX_CUSTOM_RSERVE_UI4_3       (IDX_CUSTOM_RSERVE_UI1_0 + 43)

#define IDX_CUSTOM_ACFG_LAST_IDX      (IDX_CUSTOM_RSERVE_UI1_0 + 44)

/* Reserve Field EX 280 ~ */
#define IDX_CUSTOM_RSERVE_UI1_EX_0        (IDX_CUSTOM_280)
#define IDX_CUSTOM_RSERVE_UI1_EX_1        (IDX_CUSTOM_281)
#define IDX_CUSTOM_RSERVE_UI1_EX_2        (IDX_CUSTOM_282)
#define IDX_CUSTOM_RSERVE_UI1_EX_3        (IDX_CUSTOM_283)
#define IDX_CUSTOM_RSERVE_UI1_EX_4        (IDX_CUSTOM_284)
#define IDX_CUSTOM_RSERVE_UI1_EX_5        (IDX_CUSTOM_285)
#define IDX_CUSTOM_RSERVE_UI1_EX_6        (IDX_CUSTOM_286)
#define IDX_CUSTOM_RSERVE_UI1_EX_7        (IDX_CUSTOM_287)
#define IDX_CUSTOM_RSERVE_UI1_EX_8        (IDX_CUSTOM_288)
#define IDX_CUSTOM_RSERVE_UI1_EX_9        (IDX_CUSTOM_289)
#define IDX_CUSTOM_RSERVE_UI1_EX_10       (IDX_CUSTOM_290)
#define IDX_CUSTOM_RSERVE_UI1_EX_11       (IDX_CUSTOM_291)
#define IDX_CUSTOM_RSERVE_UI1_EX_12       (IDX_CUSTOM_292)
#define IDX_CUSTOM_RSERVE_UI1_EX_13       (IDX_CUSTOM_293)
#define IDX_CUSTOM_RSERVE_UI1_EX_14       (IDX_CUSTOM_294)
#define IDX_CUSTOM_RSERVE_UI1_EX_15       (IDX_CUSTOM_295)
#define IDX_CUSTOM_RSERVE_UI1_EX_16       (IDX_CUSTOM_296)
#define IDX_CUSTOM_RSERVE_UI1_EX_17       (IDX_CUSTOM_297)
#define IDX_CUSTOM_RSERVE_UI1_EX_18       (IDX_CUSTOM_298)
#define IDX_CUSTOM_RSERVE_UI1_EX_19       (IDX_CUSTOM_299)
#define IDX_CUSTOM_RSERVE_UI1_EX_20       (IDX_CUSTOM_300)
#define IDX_CUSTOM_RSERVE_UI1_EX_21       (IDX_CUSTOM_301)
#define IDX_CUSTOM_RSERVE_UI1_EX_22       (IDX_CUSTOM_302)
#define IDX_CUSTOM_RSERVE_UI1_EX_23       (IDX_CUSTOM_303)
#define IDX_CUSTOM_RSERVE_UI1_EX_24       (IDX_CUSTOM_304)
#define IDX_CUSTOM_RSERVE_UI1_EX_25       (IDX_CUSTOM_305)
#define IDX_CUSTOM_RSERVE_UI1_EX_26       (IDX_CUSTOM_306)
#define IDX_CUSTOM_RSERVE_UI1_EX_27       (IDX_CUSTOM_307)
#define IDX_CUSTOM_RSERVE_UI1_EX_28       (IDX_CUSTOM_308)
#define IDX_CUSTOM_RSERVE_UI1_EX_29       (IDX_CUSTOM_309)
#define IDX_CUSTOM_RSERVE_UI1_EX_30       (IDX_CUSTOM_310)
#define IDX_CUSTOM_RSERVE_UI1_EX_31       (IDX_CUSTOM_311)
#define IDX_CUSTOM_RSERVE_UI1_EX_32       (IDX_CUSTOM_312)
#define IDX_CUSTOM_RSERVE_UI1_EX_33       (IDX_CUSTOM_313)
#define IDX_CUSTOM_RSERVE_UI1_EX_34       (IDX_CUSTOM_314)
#define IDX_CUSTOM_RSERVE_UI1_EX_35       (IDX_CUSTOM_315)
#define IDX_CUSTOM_RSERVE_UI1_EX_36       (IDX_CUSTOM_316)
#define IDX_CUSTOM_RSERVE_UI1_EX_37       (IDX_CUSTOM_317)
#define IDX_CUSTOM_RSERVE_UI1_EX_38       (IDX_CUSTOM_318)
#define IDX_CUSTOM_RSERVE_UI1_EX_39       (IDX_CUSTOM_319)
#define IDX_CUSTOM_RSERVE_UI1_EX_40       (IDX_CUSTOM_320)
#define IDX_CUSTOM_RSERVE_UI1_EX_41       (IDX_CUSTOM_321)
#define IDX_CUSTOM_RSERVE_UI1_EX_42       (IDX_CUSTOM_322)
#define IDX_CUSTOM_RSERVE_UI1_EX_43       (IDX_CUSTOM_323)
#define IDX_CUSTOM_RSERVE_UI1_EX_44       (IDX_CUSTOM_324)
#define IDX_CUSTOM_RSERVE_UI1_EX_45       (IDX_CUSTOM_325)
#define IDX_CUSTOM_RSERVE_UI1_EX_46       (IDX_CUSTOM_326)
#define IDX_CUSTOM_RSERVE_UI1_EX_47       (IDX_CUSTOM_327)
#define IDX_CUSTOM_RSERVE_UI1_EX_48       (IDX_CUSTOM_328)
#define IDX_CUSTOM_RSERVE_UI1_EX_49       (IDX_CUSTOM_329)
#define IDX_CUSTOM_RSERVE_UI1_EX_50       (IDX_CUSTOM_330)
#define IDX_CUSTOM_RSERVE_UI1_EX_51       (IDX_CUSTOM_331)
#define IDX_CUSTOM_RSERVE_UI1_EX_52       (IDX_CUSTOM_332)
#define IDX_CUSTOM_RSERVE_UI1_EX_53       (IDX_CUSTOM_333)
#define IDX_CUSTOM_RSERVE_UI1_EX_54       (IDX_CUSTOM_334)
#define IDX_CUSTOM_RSERVE_UI1_EX_55       (IDX_CUSTOM_335)
#define IDX_CUSTOM_RSERVE_UI1_EX_56       (IDX_CUSTOM_336)
#define IDX_CUSTOM_RSERVE_UI1_EX_57       (IDX_CUSTOM_337)
#define IDX_CUSTOM_RSERVE_UI1_EX_58       (IDX_CUSTOM_338)
#define IDX_CUSTOM_RSERVE_UI1_EX_59       (IDX_CUSTOM_339)
#define IDX_CUSTOM_RSERVE_UI1_EX_60       (IDX_CUSTOM_340)
#define IDX_CUSTOM_RSERVE_UI1_EX_61       (IDX_CUSTOM_341)
#define IDX_CUSTOM_RSERVE_UI1_EX_62       (IDX_CUSTOM_342)
#define IDX_CUSTOM_RSERVE_UI1_EX_63       (IDX_CUSTOM_343)
#define IDX_CUSTOM_RSERVE_UI1_EX_64       (IDX_CUSTOM_344)
#define IDX_CUSTOM_RSERVE_UI1_EX_65       (IDX_CUSTOM_345)
#define IDX_CUSTOM_RSERVE_UI1_EX_66       (IDX_CUSTOM_346)




#define IDX_CUSTOM_RSERVE_UI1_EX_99       (IDX_CUSTOM_379)

#define IDX_CUSTOM_RSERVE_UI2_EX_0        (IDX_CUSTOM_380)
#define IDX_CUSTOM_RSERVE_UI2_EX_1        (IDX_CUSTOM_381)
#define IDX_CUSTOM_RSERVE_UI2_EX_2        (IDX_CUSTOM_382)
#define IDX_CUSTOM_RSERVE_UI2_EX_3        (IDX_CUSTOM_383)
#define IDX_CUSTOM_RSERVE_UI2_EX_4        (IDX_CUSTOM_384)
#define IDX_CUSTOM_RSERVE_UI2_EX_5        (IDX_CUSTOM_385)
#define IDX_CUSTOM_RSERVE_UI2_EX_6        (IDX_CUSTOM_386)
#define IDX_CUSTOM_RSERVE_UI2_EX_7        (IDX_CUSTOM_387)
#define IDX_CUSTOM_RSERVE_UI2_EX_8        (IDX_CUSTOM_388)
#define IDX_CUSTOM_RSERVE_UI2_EX_9        (IDX_CUSTOM_389)
#define IDX_CUSTOM_RSERVE_UI2_EX_10       (IDX_CUSTOM_390)
#define IDX_CUSTOM_RSERVE_UI2_EX_11       (IDX_CUSTOM_391)
#define IDX_CUSTOM_RSERVE_UI2_EX_12       (IDX_CUSTOM_392)
#define IDX_CUSTOM_RSERVE_UI2_EX_13       (IDX_CUSTOM_393)
#define IDX_CUSTOM_RSERVE_UI2_EX_14       (IDX_CUSTOM_394)
#define IDX_CUSTOM_RSERVE_UI2_EX_15       (IDX_CUSTOM_395)
#define IDX_CUSTOM_RSERVE_UI2_EX_16       (IDX_CUSTOM_396)
#define IDX_CUSTOM_RSERVE_UI2_EX_17       (IDX_CUSTOM_397)
#define IDX_CUSTOM_RSERVE_UI2_EX_18       (IDX_CUSTOM_398)
#define IDX_CUSTOM_RSERVE_UI2_EX_19       (IDX_CUSTOM_399)
#define IDX_CUSTOM_RSERVE_UI2_EX_20       (IDX_CUSTOM_400)
#define IDX_CUSTOM_RSERVE_UI2_EX_21       (IDX_CUSTOM_401)
#define IDX_CUSTOM_RSERVE_UI2_EX_22       (IDX_CUSTOM_402)
#define IDX_CUSTOM_RSERVE_UI2_EX_23       (IDX_CUSTOM_403)
#define IDX_CUSTOM_RSERVE_UI2_EX_24       (IDX_CUSTOM_404)
#define IDX_CUSTOM_RSERVE_UI2_EX_25       (IDX_CUSTOM_405)
#define IDX_CUSTOM_RSERVE_UI2_EX_26       (IDX_CUSTOM_406)
#define IDX_CUSTOM_RSERVE_UI2_EX_27       (IDX_CUSTOM_407)
#define IDX_CUSTOM_RSERVE_UI2_EX_28       (IDX_CUSTOM_408)
#define IDX_CUSTOM_RSERVE_UI2_EX_29       (IDX_CUSTOM_409)
#define IDX_CUSTOM_RSERVE_UI2_EX_30       (IDX_CUSTOM_410)
#define IDX_CUSTOM_RSERVE_UI2_EX_79       (IDX_CUSTOM_459)

#define IDX_CUSTOM_RSERVE_UI4_EX_0       (IDX_CUSTOM_460)
#define IDX_CUSTOM_RSERVE_UI4_EX_1       (IDX_CUSTOM_461)
#define IDX_CUSTOM_RSERVE_UI4_EX_2       (IDX_CUSTOM_462)
#define IDX_CUSTOM_RSERVE_UI4_EX_3       (IDX_CUSTOM_463)
#define IDX_CUSTOM_RSERVE_UI4_EX_4       (IDX_CUSTOM_464)
#define IDX_CUSTOM_RSERVE_UI4_EX_5       (IDX_CUSTOM_465)
#define IDX_CUSTOM_RSERVE_UI4_EX_6       (IDX_CUSTOM_466)
#define IDX_CUSTOM_RSERVE_UI4_EX_7       (IDX_CUSTOM_467)
#define IDX_CUSTOM_RSERVE_UI4_EX_8       (IDX_CUSTOM_468)
#define IDX_CUSTOM_RSERVE_UI4_EX_9       (IDX_CUSTOM_469)
#define IDX_CUSTOM_RSERVE_UI4_EX_10      (IDX_CUSTOM_470)
#define IDX_CUSTOM_RSERVE_UI4_EX_11      (IDX_CUSTOM_471)
#define IDX_CUSTOM_RSERVE_UI4_EX_12      (IDX_CUSTOM_472)
#define IDX_CUSTOM_RSERVE_UI4_EX_13      (IDX_CUSTOM_473)
#define IDX_CUSTOM_RSERVE_UI4_EX_14      (IDX_CUSTOM_474)

#define IDX_CUSTOM_RSERVE_UI4_EX_69      (IDX_CUSTOM_529)

#define IDX_CUSTOM_FAC_CUST_11_POINT_RED           (IDX_CUSTOM_530)
#define IDX_CUSTOM_FAC_CUST_11_POINT_GREEN         (IDX_CUSTOM_531)
#define IDX_CUSTOM_FAC_CUST_11_POINT_BLUE          (IDX_CUSTOM_532)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_R        (IDX_CUSTOM_533)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_G        (IDX_CUSTOM_534)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_B        (IDX_CUSTOM_535)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_C        (IDX_CUSTOM_536)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_M        (IDX_CUSTOM_537)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_Y        (IDX_CUSTOM_538)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_R        (IDX_CUSTOM_539)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_G        (IDX_CUSTOM_540)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_B        (IDX_CUSTOM_541)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_C        (IDX_CUSTOM_542)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_M        (IDX_CUSTOM_543)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_Y        (IDX_CUSTOM_544)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_R        (IDX_CUSTOM_545)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_G        (IDX_CUSTOM_546)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_B        (IDX_CUSTOM_547)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_C        (IDX_CUSTOM_548)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_M        (IDX_CUSTOM_549)
#define IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_Y        (IDX_CUSTOM_550)


#define APP_CFG_RSERVE_UI1_EX_NUM      (IDX_CUSTOM_RSERVE_UI1_EX_99 - IDX_CUSTOM_RSERVE_UI1_EX_0 + 1)
#define APP_CFG_RSERVE_UI2_EX_NUM      (IDX_CUSTOM_RSERVE_UI2_EX_79 - IDX_CUSTOM_RSERVE_UI2_EX_0 + 1)
#define APP_CFG_RSERVE_UI4_EX_NUM      (IDX_CUSTOM_RSERVE_UI4_EX_69 - IDX_CUSTOM_RSERVE_UI4_EX_0 + 1)

#define ACFG_PASSWORD_DEF                   "0000"
#define ACFG_AGC_DEF                        FALSE

#define APP_CFG_ALWAYS_UPDATE_BACKLIGHT

/* Caution!!! Can only use rserved IDX to mapping new added acfg index */
#define IDX_CUSTOM_LIP_SYNC_IDX_TV              (IDX_CUSTOM_RSERVE_UI1_0)
#define IDX_CUSTOM_LIP_SYNC_IDX_CVBS            (IDX_CUSTOM_RSERVE_UI1_1)
#define IDX_CUSTOM_LIP_SYNC_IDX_COMP            (IDX_CUSTOM_RSERVE_UI1_2)
#define IDX_CUSTOM_LIP_SYNC_IDX_HDMI1           (IDX_CUSTOM_RSERVE_UI1_3)
#define IDX_CUSTOM_LIP_SYNC_IDX_HDMI2           (IDX_CUSTOM_RSERVE_UI1_4)
#define IDX_CUSTOM_LIP_SYNC_IDX_HDMI3           (IDX_CUSTOM_RSERVE_UI1_5)
#define IDX_CUSTOM_LIP_SYNC_IDX_HDMI4           (IDX_CUSTOM_RSERVE_UI1_6)
#define IDX_CUSTOM_LIP_SYNC_IDX_VGA             (IDX_CUSTOM_RSERVE_UI1_7)
#define IDX_CUSTOM_LIP_SYNC_IDX_MMP             (IDX_CUSTOM_RSERVE_UI1_8)
#define IDX_CUSTOM_LIP_SYNC_IDX_VTRL            (IDX_CUSTOM_RSERVE_UI1_9)
#define IDX_CUSTOM_SRS_SRUND_IDX_TV             (IDX_CUSTOM_RSERVE_UI1_10)
#define IDX_CUSTOM_SRS_SRUND_IDX_CVBS           (IDX_CUSTOM_RSERVE_UI1_11)
#define IDX_CUSTOM_SRS_SRUND_IDX_COMP           (IDX_CUSTOM_RSERVE_UI1_12)
#define IDX_CUSTOM_SRS_SRUND_IDX_HDMI1          (IDX_CUSTOM_RSERVE_UI1_13)
#define IDX_CUSTOM_SRS_SRUND_IDX_HDMI2          (IDX_CUSTOM_RSERVE_UI1_14)
#define IDX_CUSTOM_SRS_SRUND_IDX_HDMI3          (IDX_CUSTOM_RSERVE_UI1_15)
#define IDX_CUSTOM_SRS_SRUND_IDX_HDMI4          (IDX_CUSTOM_RSERVE_UI1_16)
#define IDX_CUSTOM_SRS_SRUND_IDX_VGA            (IDX_CUSTOM_RSERVE_UI1_17)
#define IDX_CUSTOM_SRS_SRUND_IDX_MMP            (IDX_CUSTOM_RSERVE_UI1_18)
#define IDX_CUSTOM_SRS_SRUND_IDX_VTRL           (IDX_CUSTOM_RSERVE_UI1_19)
#define IDX_CUSTOM_ACR_IDX                      (IDX_CUSTOM_RSERVE_UI1_20)
#define IDX_CUSTOM_WIFI_REMOTE_PAIR_STATUS      (IDX_CUSTOM_RSERVE_UI1_21)
#define IDX_CUSTOM_ENTERNET_CONNECTED_STATUS    (IDX_CUSTOM_RSERVE_UI1_22)
#define IDX_CUSTOM_MAIN_MENU_PRE_ITEM           (IDX_CUSTOM_RSERVE_UI1_23)
#define IDX_CUSTOM_MIRACAST_ENABLE_STATUS       (IDX_CUSTOM_RSERVE_UI1_24)
#define IDX_CUSTOM_START_SETUP                  (IDX_CUSTOM_RSERVE_UI1_25)
#define IDX_CUSTOM_LAST_P2P0_OP_CHANNEL         (IDX_CUSTOM_RSERVE_UI1_26)
#define IDX_CUSTOM_VOL_CONTROL                  (IDX_CUSTOM_RSERVE_UI1_27)
#define IDX_CUSTOM_SCRN_SAVER_TIME              (IDX_CUSTOM_RSERVE_UI1_28)
#define IDX_CUSTOM_PIC_QUALITY_ADJUST_PAGE      (IDX_CUSTOM_RSERVE_UI1_29)

#define IDX_CUSTOM_3D_BRIGHTNESS_BOOST          (IDX_CUSTOM_RSERVE_UI2_1)
#define IDX_CUSTOM_LANG_SELECT                  (IDX_CUSTOM_RSERVE_UI2_2)
#define IDX_CUSTOM_COUNTRY_SELECT               (IDX_CUSTOM_RSERVE_UI2_3)
#define IDX_CUSTOM_REDUCE_BLUR                  (IDX_CUSTOM_RSERVE_UI2_4)
#define IDX_CUSTOM_VGA_H_SIZE                   (IDX_CUSTOM_RSERVE_UI2_5)
#define IDX_CUSTOM_VGA_V_SIZE                   (IDX_CUSTOM_RSERVE_UI2_6)
#define IDX_CUSTOM_DST                          (IDX_CUSTOM_RSERVE_UI2_7)
#define IDX_CUSTOM_TIMEZONE_SELECT           	(IDX_CUSTOM_RSERVE_UI2_8)
#define IDX_CUSTOM_DHCP_STATUS                  (IDX_CUSTOM_RSERVE_UI2_9)

#define IDX_CUSTOM_SYS_BOOT_UP_TIMES            (IDX_CUSTOM_RSERVE_UI4_1)
#define IDX_CUSTOM_SYS_TOTAL_RUNNING_TIME       (IDX_CUSTOM_RSERVE_UI4_2)
#if 0
#define IDX_CUSTOM_BLEGATT_RSSI_THRESHOLD       (IDX_CUSTOM_RSERVE_UI4_3)
#endif

/* used for log2usb, and log2usb not use this field again currently */
#define IDX_CUSTOM_LOG_TO_USB                   (IDX_CUSTOM_RSERVE_UI1_EX_1)
#define IDX_CUSTOM_VGA_POS_H_EXT                (IDX_CUSTOM_RSERVE_UI1_EX_2)
/* used for rest use internet time */
#define IDX_CUSTOM_USE_INTERNET_TIME            (IDX_CUSTOM_RSERVE_UI1_EX_3)
#define IDX_CUSTOM_TIME_FORMAT                  (IDX_CUSTOM_RSERVE_UI1_EX_4)
#define IDX_CUSTOM_LAST_CHANNEL_TUNER_TYPE      (IDX_CUSTOM_RSERVE_UI1_EX_7)
#define IDX_CUSTOM_CH_SCAN_PROGRESS             (IDX_CUSTOM_RSERVE_UI1_EX_9)
#define IDX_CUSTOM_FORCE_REBOOT_UP              (IDX_CUSTOM_RSERVE_UI1_EX_10)
#define IDX_CUSTOM_VLOG_CONTORL                 (IDX_CUSTOM_RSERVE_UI1_EX_11)

/* used for audio add vol control dis page item */
#define IDX_CUSTOM_VOL_CONTROL_DISPLAY        (IDX_CUSTOM_RSERVE_UI1_EX_12)

/* used for Full Color 4:4:4 menu item */
#define IDX_CUSTOM_FULL_COLOR_444            (IDX_CUSTOM_RSERVE_UI1_EX_13)

/* used for oobe IR mode */
/* 1 if user do oobe via IR flow, otherwise 0 */
#define IDX_CUSTOM_OOBE_IR_MODE               (IDX_CUSTOM_RSERVE_UI1_EX_14)

#define IDX_CUSTOM_HIDE_FROM_INPUT_LIST              (IDX_CUSTOM_RSERVE_UI1_EX_15)
#define IDX_CUSTOM_HIDE_FROM_INPUT_LIST_MANUAL       (IDX_CUSTOM_RSERVE_UI1_EX_16)
#define IDX_CUSTOM_COLOR_TUNER_OFFSET_ID             (IDX_CUSTOM_RSERVE_UI1_EX_17)
#define IDX_CUSTOM_FULL_UHD_COLOR                    (IDX_CUSTOM_RSERVE_UI1_EX_18)
#define IDX_CUSTOM_RETAIL_MODE_FIRST_TIME_SETTING    (IDX_CUSTOM_RSERVE_UI1_EX_19)
#define IDX_CUSTOM_RETAIL_MODE_SOURCE_INFO_STORE     (IDX_CUSTOM_RSERVE_UI1_EX_20)
#define IDX_CUSTOM_USB_POWER_CTRL                    (IDX_CUSTOM_RSERVE_UI1_EX_21)
#define IDX_CUSTOM_COLOR_SPACE			             (IDX_CUSTOM_RSERVE_UI1_EX_22)
#define IDX_CLEAR_ACTION				             (IDX_CUSTOM_RSERVE_UI1_EX_23)/* clear Action */
#define IDX_DEMO_MODE				                 (IDX_CUSTOM_RSERVE_UI1_EX_24)/* demo mode */
#define IDX_LOCAL_DIMMING				             (IDX_CUSTOM_RSERVE_UI1_EX_25)/* local dimming */
#define IDX_CUSTOM_AIRPLAY_STATE_CTRL                (IDX_CUSTOM_RSERVE_UI1_EX_26)/* airplay mode */
#define IDX_IPTS_VTRL_HIDE_MANUAL                    (IDX_CUSTOM_RSERVE_UI1_EX_27)/* hide nanual*/


#define IDX_CUSTOM_CONTRAST_EN                       (IDX_CUSTOM_RSERVE_UI1_EX_28)
#define IDX_CUSTOM_SUPER_RESOLUTION                  (IDX_CUSTOM_RSERVE_UI1_EX_29)
#define IDX_CUSTOM_MOTION_BLUR_REDUCTION             (IDX_CUSTOM_RSERVE_UI1_EX_30)
#define IDX_CUSTOM_VARIABLE_REFRESH_RATE             (IDX_CUSTOM_RSERVE_UI1_EX_31)
#define IDX_CUSTOM_ETOF                              (IDX_CUSTOM_RSERVE_UI1_EX_32)
#define IDX_CUSTOM_EN_VIEW_ANGLE                     (IDX_CUSTOM_RSERVE_UI1_EX_33)
#define IDX_CUSTOM_GAME_LOW_LATENCY                  (IDX_CUSTOM_RSERVE_UI1_EX_34)
#define IDX_CUSTOM_JUDDER_REDUCTION                  (IDX_CUSTOM_RSERVE_UI1_EX_35)
#define IDX_CUSTOM_FILM_MAKER_MODE                   (IDX_CUSTOM_RSERVE_UI1_EX_36)
#define IDX_CUSTOM_CONTOUR_SMOOTHING                 (IDX_CUSTOM_RSERVE_UI1_EX_37)

/* oled fature */
#define IDX_CUSTOM_OLED_OFF_RS                       (IDX_CUSTOM_RSERVE_UI1_EX_38)
#define IDX_CUSTOM_OLED_JB                           (IDX_CUSTOM_RSERVE_UI1_EX_39)

#define IDX_CUSTOM_OLED_PANEL_REFRESH                (IDX_CUSTOM_RSERVE_UI1_EX_40)
#define IDX_CUSTOM_OLED_PIXEL_SHIFT                  (IDX_CUSTOM_RSERVE_UI1_EX_41)

#define IDX_CUSTOM_DYNAMIC_CONTENT                   (IDX_CUSTOM_RSERVE_UI1_EX_42)
#define IDX_CUSTOM_OTA_LOOP_TEST                     (IDX_CUSTOM_RSERVE_UI1_EX_43)
#define IDX_CUSTOM_MEMC                              (IDX_CUSTOM_RSERVE_UI1_EX_44)
#define IDX_CUSTOM_LIMITED_AD_TRACKING               (IDX_CUSTOM_RSERVE_UI1_EX_45)
/*CUST gamma*/
#define IDX_CUST_GAMMA                               (IDX_CUSTOM_RSERVE_UI1_EX_46)

/*CUST Channel scan status*/
#define IDX_CUST_CH_SCAN_STATUS                      (IDX_CUSTOM_RSERVE_UI1_EX_47)

#define IDX_CUSTOM_EDGE_ENHANCEMENT                  (IDX_CUSTOM_RSERVE_UI1_EX_48)
#define IDX_CUSTOM_GAME_HDR                          (IDX_CUSTOM_RSERVE_UI1_EX_49)
#define IDX_CUSTOM_PEAK_LUMINANCE                    (IDX_CUSTOM_RSERVE_UI1_EX_50)

//eARC mode
#define IDX_CUSTOM_EARC_MODE                         (IDX_CUSTOM_RSERVE_UI1_EX_55)

//oled running status
#define IDX_CUSTOM_OLED_STATUS               (IDX_CUSTOM_RSERVE_UI1_EX_56)

//oled system locked
#define IDX_CUSTOM_OLED_ERR_COUNT_CHECKSUM                 (IDX_CUSTOM_RSERVE_UI1_EX_57)

//demo mode type
#define IDX_CUSTOM_DEMO_TYPE                          (IDX_CUSTOM_RSERVE_UI1_EX_58)
//oled error detect
#define IDX_CUSTOM_OLED_ERROR_COUNT                   (IDX_CUSTOM_RSERVE_UI1_EX_59)
#define IDX_CUSTOM_OLED_ERROR_COUNT_BACKUP1           (IDX_CUSTOM_RSERVE_UI1_EX_60)
#define IDX_CUSTOM_OLED_ERROR_COUNT_BACKUP2           (IDX_CUSTOM_RSERVE_UI1_EX_61)
#define IDX_CUSTOM_OLED_ERROR_DETECT_ON_OFF           (IDX_CUSTOM_RSERVE_UI1_EX_62)
#define IDX_CUSTOM_OLED_POWER_MODE_SAVE               (IDX_CUSTOM_RSERVE_UI1_EX_63)
#define IDX_CUSTOM_AUTOMATIC_TIME                     (IDX_CUSTOM_RSERVE_UI1_EX_64)
//for dolby game mode
#define IDX_CUSTOM_DV_GAME_MODE_LAST_PIC_MODE         (IDX_CUSTOM_RSERVE_UI1_EX_65)


#define IDX_CUSTOM_LAST_CHANNEL_ID            (IDX_CUSTOM_RSERVE_UI4_EX_0)
#define IDX_CUSTOM_HDMI1_VGA_SETTING          (IDX_CUSTOM_RSERVE_UI4_EX_1)
#define IDX_CUSTOM_HDMI2_VGA_SETTING          (IDX_CUSTOM_RSERVE_UI4_EX_2)
#define IDX_CUSTOM_HDMI3_VGA_SETTING          (IDX_CUSTOM_RSERVE_UI4_EX_3)
#define IDX_CUSTOM_HDMI4_VGA_SETTING          (IDX_CUSTOM_RSERVE_UI4_EX_4)
#define IDX_CUSTOM_COMP_VGA_SETTING           (IDX_CUSTOM_RSERVE_UI4_EX_5)
#define IDX_CUSTOM_OLED_PANEL_DISPLAY_TIME    (IDX_CUSTOM_RSERVE_UI4_EX_6)  //oled panel display time
#define IDX_CUSTOM_OLED_DEMO_MODE_DECLINE_TIME_H (IDX_CUSTOM_RSERVE_UI4_EX_7)  //oled panel demo mode decline time
#define IDX_CUSTOM_OLED_DEMO_MODE_DECLINE_TIME_L (IDX_CUSTOM_RSERVE_UI4_EX_8)  //oled panel demo mode decline time
#define IDX_CUSTOM_OLED_LAST_SCREEN_REFRESH_TIME_H (IDX_CUSTOM_RSERVE_UI4_EX_9)  //oled panel last screen refresh time
#define IDX_CUSTOM_OLED_LAST_SCREEN_REFRESH_TIME_L (IDX_CUSTOM_RSERVE_UI4_EX_10)  //oled panel last screen refresh time
#define IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_DISPLAY_TIME (IDX_CUSTOM_RSERVE_UI4_EX_11)  //oled panel display time from factory out
#define IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_OFFRS_TIME (IDX_CUSTOM_RSERVE_UI4_EX_12)  //oled panel off-RS time from factory out
#define IDX_CUSTOM_OLED_EX_FACTORY_TOTAL_JB_TIME (IDX_CUSTOM_RSERVE_UI4_EX_13)  //oled panel JB time from factory out



#define IDX_CUSTOM_WHITE_BALANCE_OFFSET_ID    (IDX_CUSTOM_RSERVE_UI2_EX_0)
#define IDX_CUSTOM_OLED_JB_COOLING_TIME       (IDX_CUSTOM_RSERVE_UI2_EX_1)
#define IDX_CUSTOM_OLED_OFFRS_COUNT           (IDX_CUSTOM_RSERVE_UI2_EX_2)
#define IDX_CUSTOM_OLED_JB_COUNT              (IDX_CUSTOM_RSERVE_UI2_EX_3)

#define USE_NET_TIME_OFF         (0)
#define USE_NET_TIME_ON          (1)
#define USE_TIME_12H             (0)
#define USE_TIME_24H             (1)

#define IDX_CUSTOM_SPEAKER_OUT_ADDRESS          (IDX_CUSTOM_RSERVE_UI1_EX_5)
#define IDX_CUSTOM_DIGITAL_AUDIO_ADDRESS        (IDX_CUSTOM_RSERVE_UI1_EX_6)
/*used for cec func defaults value for vizio*/
#define ACFG_CEC_FUNC_DEF           APP_CFG_CEC_ON

/* used for record 1st time chose HDMI-x/COMP */
#define IDX_CUSTOM_IPTS_SELECT_TIME           (IDX_CUSTOM_RSERVE_UI1_EX_8)
#define IPTS_IS_SELEC_FALSE        (0)
/*
Define address after EEP_OFFSET_END,use for special case after mp,the AP acfg layout can not change
*/
#define IDX_IPTS_VTRL_NAME_1_ADDR              (EEP_OFFSET_EXT_START + 1)   /* 24 bytes */
#define IDX_IPTS_VTRL_NAME_2_ADDR              (IDX_IPTS_VTRL_NAME_1_ADDR + 1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_NAME_3_ADDR              (IDX_IPTS_VTRL_NAME_2_ADDR + 1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_NAME_4_ADDR              (IDX_IPTS_VTRL_NAME_3_ADDR + 1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_NAME_5_ADDR              (IDX_IPTS_VTRL_NAME_4_ADDR + 1 + 24)   /* 24 bytes */

#define IDX_IPTS_VTRL_DSP_NAME_ENG_1_ADDR      (IDX_IPTS_VTRL_NAME_5_ADDR + 1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_ENG_2_ADDR      (IDX_IPTS_VTRL_DSP_NAME_ENG_1_ADDR +1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_ENG_3_ADDR      (IDX_IPTS_VTRL_DSP_NAME_ENG_2_ADDR + 1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_ENG_4_ADDR      (IDX_IPTS_VTRL_DSP_NAME_ENG_3_ADDR + 1 + 24 )   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_ENG_5_ADDR      (IDX_IPTS_VTRL_DSP_NAME_ENG_4_ADDR + 1+ 24)   /* 24 bytes */

#define IDX_IPTS_VTRL_DSP_NAME_FRE_1_ADDR      (IDX_IPTS_VTRL_DSP_NAME_ENG_5_ADDR + 1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_FRE_2_ADDR      (IDX_IPTS_VTRL_DSP_NAME_FRE_1_ADDR + 1+ 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_FRE_3_ADDR      (IDX_IPTS_VTRL_DSP_NAME_FRE_2_ADDR + 1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_FRE_4_ADDR      (IDX_IPTS_VTRL_DSP_NAME_FRE_3_ADDR + 1+ 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_FRE_5_ADDR      (IDX_IPTS_VTRL_DSP_NAME_FRE_4_ADDR + 1+ 24)   /* 24 bytes */

#define IDX_IPTS_VTRL_DSP_NAME_SPA_1_ADDR      (IDX_IPTS_VTRL_DSP_NAME_FRE_5_ADDR + 1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_SPA_2_ADDR      (IDX_IPTS_VTRL_DSP_NAME_SPA_1_ADDR + 1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_SPA_3_ADDR      (IDX_IPTS_VTRL_DSP_NAME_SPA_2_ADDR + 1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_SPA_4_ADDR      (IDX_IPTS_VTRL_DSP_NAME_SPA_3_ADDR + 1 + 24)   /* 24 bytes */
#define IDX_IPTS_VTRL_DSP_NAME_SPA_5_ADDR      (IDX_IPTS_VTRL_DSP_NAME_SPA_4_ADDR + 1 + 24)   /* 24 bytes */


/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
#define MAX_CACHE_BLE_NUMBER_DEF    70
#define MAX_CACHE_BLE_NUMBER	    64
#define MAC_ADDRESS_LENGTH_LEN		12

typedef struct _BLE_CACHE_DEVICE
{
    CHAR    c_mac_address[MAC_ADDRESS_LENGTH_LEN + 1];
    UINT8   ui_target_ID;
    BOOL    b_is_IOS;
}BLE_CACHE_DEVICE;

/* bluetooth default ON */
#define APP_CFG_BLUETOOTH_SWITCH_DEF            APP_CFG_BLUETOOTH_SWITCH_ON

#if 1
#define ACFG_CEC_AUTO_OFF_DEF       APP_CFG_CEC_ON
#define ACFG_CEC_AUTO_ON_DEF        APP_CFG_CEC_ON
#endif
#define APP_CFG_BS_SRC_DEF          APP_CFG_BS_SRC_CABLE
#define ACFG_EEP_CUST_SCHEMA        2

#define ACFG_CC_ENABLED_DEF         APP_CFG_CC_OFF

#define ACFG_DCS_FZ_DEF             APP_CFG_DCS_FZ_BROADCAST
#define ACFG_DCS_FS_DEF             APP_CFG_DCS_FS_BROADCAST
#define ACFG_DCS_FONT_CLR_DEF       APP_CFG_DCS_CLR_BROADCAST
#define ACFG_DCS_FONT_OP_DEF        APP_CFG_DCS_OP_BROADCAST
#define ACFG_DCS_BK_CLR_DEF         APP_CFG_DCS_CLR_BROADCAST
#define ACFG_DCS_BK_OP_DEF          APP_CFG_DCS_OP_BROADCAST
#define ACFG_DCS_WIN_CLR_DEF        APP_CFG_DCS_CLR_BROADCAST
#define ACFG_DCS_WIN_OP_DEF         APP_CFG_DCS_OP_BROADCAST

/* wifi remote pair status */
#define WIFI_REMOTE_PAIR_STATUS_UNKNOWN   ((UINT8)0)
#define WIFI_REMOTE_PAIR_STATUS_UNPAIRED  ((UINT8)1)
#define WIFI_REMOTE_PAIR_STATUS_PAIRING   ((UINT8)2)
#define WIFI_REMOTE_PAIR_STATUS_PAIRED    ((UINT8)3)

/* reduce blur support */
#define ACFG_REDUCE_BLUR_OFF    ((UINT16)0)
#define ACFG_REDUCE_BLUR_ON     ((UINT16)1)

/* reduce blur support */
#define ACFG_GAME_MODE_OFF    ((UINT16)0)
#define ACFG_GAME_MODE_ON     ((UINT16)1)

/* Value of APP_CFG_RECID_AUD_AD_SPEAKER */
#define APP_CFG_AUD_AD_SPEAKER_AUTO                 ((UINT8)    2)
#define APP_CFG_AUD_AD_SPEAKER_ON                   ((UINT8)    1)
#define APP_CFG_AUD_AD_SPEAKER_OFF                  ((UINT8)    0)

#define APP_AUD_SPDIF_FMT_AUTO                      ((UINT8)    0)

/* TTS input channel default volume */
#define APP_CFG_TTS_VOL_DEF    ((UINT8)100)
#define APP_CFG_TTS_VOL_MAX    ((UINT8)100)
#define APP_CFG_TTS_VOL_MIN    ((UINT8)0)

/* LOG TO USB */
#define ACFG_LOG_TO_USB_OFF    ((UINT16)0)
#define ACFG_LOG_TO_USB_ON     ((UINT16)1)

/* cust gamma */
#define ACFG_CUST_GAMMA_1_8     ((UINT16)0)
#define ACFG_CUST_GAMMA_2_0     ((UINT16)1)
#define ACFG_CUST_GAMMA_2_1     ((UINT16)2)
#define ACFG_CUST_GAMMA_2_2     ((UINT16)3)
#define ACFG_CUST_GAMMA_2_4     ((UINT16)4)

#define ACFG_CUST_DI_FILM_MODE_OFF     ((UINT16)0)
#define ACFG_CUST_DI_FILM_MODE_AUTO    ((UINT16)1)


/* cust channel scan status */
#define ACFG_CUST_BS_SRC_NUM          ((UINT8)3)

#define ACFG_CUST_CH_NOT_SCANED       ((UINT8)0)
#define ACFG_CUST_CH_SCANED_NO_CH     ((UINT8)1)
#define ACFG_CUST_PARTIAL_SCAN        ((UINT8)2)
#define ACFG_CUST_COMPLETED_SCAN      ((UINT8)3)


/* dhcp special status */
#define ACFG_DHCP_OFF           ((UINT16)0)
#define ACFG_DHCP_DNS_ONLY      ((UINT16)1)

/* ACR on/off status */
#define ACFG_ACR_ON             ((UINT8)1)
#define ACFG_ACR_OFF            ((UINT8)0)

/* VLOG */
#define ACFG_VLOG_ON             ((UINT8)1)
#define ACFG_VLOG_OFF            ((UINT8)0)


/* Last p2p0 op channel number  */
#define LAST_P2P0_OP_CHANNEL_UNKNOWN  ((UINT8)0)
#define LAST_P2P0_OP_CHANNEL_1   ((UINT8)1)
#define LAST_P2P0_OP_CHANNEL_2   ((UINT8)2)
#define LAST_P2P0_OP_CHANNEL_3   ((UINT8)3)
#define LAST_P2P0_OP_CHANNEL_4   ((UINT8)4)
#define LAST_P2P0_OP_CHANNEL_5   ((UINT8)5)
#define LAST_P2P0_OP_CHANNEL_6   ((UINT8)6)
#define LAST_P2P0_OP_CHANNEL_7   ((UINT8)7)
#define LAST_P2P0_OP_CHANNEL_8   ((UINT8)8)
#define LAST_P2P0_OP_CHANNEL_9   ((UINT8)9)
#define LAST_P2P0_OP_CHANNEL_10   ((UINT8)10)
#define LAST_P2P0_OP_CHANNEL_11  ((UINT8)11)

/* Screen Saver time */
#define ACFG_CUSTOM_SCRN_BLANK_DISABLE      ((UINT16)0)
#define ACFG_CUSTOM_SCRN_BLANK_2MIN         ((UINT16)1)
#define ACFG_CUSTOM_SCRN_BLANK_10MIN        ((UINT16)2)
#define ACFG_CUSTOM_SCRN_BLANK_20MIN        ((UINT16)3)

/*picture quality page*/
#define ACFG_CUSTOM_COLOR_TUNER		        ((UINT16)0)
#define ACFG_CUSTOM_11_PIONT_GAIN           ((UINT16)1)
#define ACFG_CUSTOM_SMPTE_TEST_PATTERNS     ((UINT16)2)
#define ACFG_CUSTOM_FLAT_TEST_PATTERNS      ((UINT16)3)
#define ACFG_CUSTOM_RAMP_TEST_PATTERNS      ((UINT16)4)
#ifdef APP_CAST_TEST_PATTERN
#define ACFG_CUSTOM_UNIFORMITY_ANALYZER_TEST_PATTERNS      ((UINT16)5)
#endif

#define DEFAULT_WAKEUP_TIME acfg_default_wakeup_time()

/* for wifi remote updater */
#define WIFI_REMOTE_START_SETUP_OFF    ((UINT8)0)
#define WIFI_REMOTE_START_SETUP_ON     ((UINT8)1)

#define ACFG_VGA_POS_H_MIN              -50
#define ACFG_VGA_POS_H_MAX              50
#define ACFG_VGA_POS_V_MIN              -50
#define ACFG_VGA_POS_V_MAX              50

/* VIZIO default enable fast boot */
#ifdef APP_SUPPORT_STR_CORE_OFF
#define ACFG_FAST_BOOT_DEF           (APP_CFG_FAST_BOOT_ON)
#endif

#define AUDIO_OUTPUT_TYPE_LINE_OUT      (UINT8)0
#define AUDIO_OUTPUT_TYPE_HEADPHONE     (UINT8)1
#define AUDIO_OUTPUT_TYPE_BOTH          (UINT8)2
#define AUDIO_OUTPUT_TYPE_END           (UINT8)3

#define AUD_SPDIF_AUDIO_OUT_AUTO                (0)
#define AUD_SPDIF_AUDIO_OUT_PCM                 (1)
#define AUD_SPDIF_AUDIO_OUT_DOLBY_D             (2)
#define AUD_SPDIF_AUDIO_OUT_BITSTREAM           (3)

#define PLF_OPT_MODEL_NAME_LEN          (16 + 1)
#define ACFG_CUSTOM_WIFI_MODULE_NAME_LEN        (64)

/* system update force reboot flag */
#define ACFG_FORCE_REBOOT_UP_OFF           ((UINT8)0)
#define ACFG_FORCE_REBOOT_UP_ON            ((UINT8)1)

/* volume control display flag */
#define ACFG_CUSTOM_VOL_SLIDER_DIS_OFF    ((UINT8)1)
#define ACFG_CUSTOM_VOL_SLIDER_DIS_ON     ((UINT8)0)

#define ACFG_CUSTOM_HDMI_RANGE_AUTO			((UINT8)0)
#define ACFG_CUSTOM_HDMI_RANGE_FULL			((UINT8)1)
#define ACFG_CUSTOM_HDMI_RANGE_LIMIT		((UINT8)2)
#define MI_INI_FILE_PATH_LEN                (255)
#define MI_INI_FILE_KEY_LEN                 (64)
#define GAMMA_LEN                           (386)
#define GAMMA_ERERY_LINE_LEN                (9)
#define MI_INI_FILE_SIZE_LEN                (6 * GAMMA_LEN)
#define MI_INI_FILE_PATH                    "/config/panel/UD_VB1_8LANE_CSOT_URSA.ini"



#define APP_CFG_VID_GAME_MODE_OFF           ((UINT8)  0)
#define APP_CFG_VID_GAME_MODE_ON            ((UINT8)  1)

#define APP_CFG_VID_DOLBY_COND_FALSE        ((UINT8)  0)
#define APP_CFG_VID_DOLBY_COND_TRUE         ((UINT8)  1)

typedef enum{
    LOGLEVEL_OFF,           // 0
    LOGLEVEL_APP_ONLY,      // 1
    LOGLEVEL_KERNEL_ONLY,   // 2
    LOGLEVEL_ALL,           // 3
} ACFG_LOGLEVEL;

typedef enum{
	ACFG_OLED_ERR_EVENT_PNL_ERR,
	ACFG_OLED_ERR_EVENT_PWM_ERR,
	ACFG_OLED_ERR_EVENT_GSP_IMG_STILL,
	ACFG_OLED_ERR_EVENT_GSP_IMG_MOVE
}ACFG_OLED_ERROR_DETECT_TYPE;

typedef struct _ACFG_GAMMA_TABLE_T
{
    UINT8 gamma_r[GAMMA_LEN];
    UINT8 gamma_g[GAMMA_LEN];
    UINT8 gamma_b[GAMMA_LEN];
} ACFG_GAMMA_TABLE_T;

typedef enum
{
    ACFG_COLOR_TUNER_BRI = 0,
    ACFG_COLOR_TUNER_HUE,
    ACFG_COLOR_TUNER_SAT,
    ACFG_COLOR_TUNER_OFFSET,
    ACFG_COLOR_TUNER_GAIN
}ACFG_COLOR_TUNER_MODULE;

typedef enum
{
    ACFG_COLOR_TUNER_M = 0,
    ACFG_COLOR_TUNER_R,
    ACFG_COLOR_TUNER_Y,
    ACFG_COLOR_TUNER_G,
    ACFG_COLOR_TUNER_C,
    ACFG_COLOR_TUNER_B,
    ACFG_COLOR_TUNER_F,
    ACFG_COLOR_TUNER_MAX
}ACFG_COLOR_TUNER_COLOR;

typedef struct _ACFG_TYPE_SET_RGB_T
{
    BOOL   bEnable;
    UINT16 u2R;
    UINT16 u2G;
    UINT16 u2B;
} ACFG_TYPE_SET_RGB_T;

typedef enum
{
    SCREEN_REFRESH_START_CANCEL,
    SCREEN_REFRESH_START_AT_POWER_OFF,
    SCREEN_REFRESH_START_AT_NOW,
}ACFG_SCREEN_REFRESH_TYPE_T;

// ===============LED parameters=======================
typedef enum
{
    //send to PM
    E_PM_TYPE_PM= 0,
    //send to RTPM
    E_PM_TYPE_RTPM,
} PM_PmType_e;

typedef enum
{
    //Set led on
    E_PM_LED_MODE_ON = 0,
    //set led dark
    E_PM_LED_MODE_OFF,
    //set led breath
    E_PM_LED_MODE_BREATH,
    //set led flicker,after flicker return the previous mode
    //(E_MI_PM_LED_ON, E_MI_PM_LED_OFF, E_MI_PM_LED_BREATH)
    E_PM_LED_MODE_FLICKER_ONCE,
    //set led flicker
    E_PM_LED_MODE_FLICKER,
} PM_LedMode_e;

typedef struct PM_LedDarkParams_s
{
    UINT8 u8Reserved;           ///[IN]: reserved
}PM_LedDarkParams_t;

typedef struct PM_LedLightParams_s
{
    UINT8 u8LightRate; //range:0~100, light rate(0~100%) eg. 60 -> 60% light rate
}PM_LedLightParams_t;

typedef struct PM_LedFlinkerParams_s
{
    UINT8 u8LightRate; //range:0~100, light rate(0~100%) eg. 60 -> 60% light rate
    UINT8 u8Period;  //one flinker period total time (dark+light) per 100ms
    UINT8 u8Duty; //one flinker period light time  per 100ms eg.10 -> 10*100ms = 1s
} PM_LedFlinkerParams_t;

typedef struct PM_LedBreathParams_s
{
    UINT8 u8LightRate; //range:0~100, light rate(0~100%) eg. 60 -> 60% light rate
    UINT8 u8DarkTime; //one breath period dark time per 100ms eg.10 -> 10*100ms = 1s
    UINT8 u8DarkToLightTime; //one breath period dark->light time per 100ms
    UINT8 u8LightTime; //one breath period light time per 100ms
    UINT8 u8LightToDarkTime; //one breath period light->dark time per 100ms
} PM_LedBreathParams_t;


typedef struct PM_LedStateInfo_s
{
    PM_LedMode_e eStageMode;
    union
    {
        PM_LedDarkParams_t stLedDarkParams;
        PM_LedLightParams_t stLedLightParams;
        PM_LedFlinkerParams_t stLedFlinkerParams;
        PM_LedBreathParams_t stLedBreathParams;
    };
}PM_LedStateInfo_t;

typedef struct PM_LedModeConfig_s
{
    PM_PmType_e ePmType;
    UINT8 u8StageSpaceTime; /// space time between two stage
    PM_LedStateInfo_t astStateInfo[2];
} PM_LedModeConfig_t;

// ===============LED parameters=======================


#ifdef CLI_SUPPORT
#define ACFG_DBG_PRINT(fmt, ...) \
    if(a_cfg_get_acfg_dl() >= 0) \
        DBG_LOG_PRINT( (" [ACFG] <%s:%4d> " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))    /**<        */

#define ACFG_DBG_INFO(fmt, ...) \
    if(a_cfg_get_acfg_dl() >= 1) \
        DBG_LOG_PRINT( (" [ACFG] <%s:%4d> " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))    /**<        */

#define ACFG_DBG_ERROR(fmt, ...) \
    if(a_cfg_get_acfg_dl() >= 0) \
        DBG_LOG_PRINT( (" [ACFG]Err : <%s:%4d> " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))    /**<        */

#else
#define SPLAYER_DBG_PRINT(fmt, ...)
#define SPLAYER_DBG_INFO(fmt, ...)
#define SPLAYER_DBG_ERROR(fmt)
#endif

#define ACFG_DEBUG_INPUT_SRC_NAME(x) do { \
    if(a_cfg_get_src_name_log() >0) \
    { \
        x; \
    } \
    } while(0)

typedef struct _WIFI_DEVICE_INFO
{
    CHAR   c_VenderID[64];
    CHAR   c_ProductID[64];
}WIFI_DEVICE_INFO;

//dolphin 20191210 add HDR support Api
typedef enum _HDR_TYPE_E
{
    E_HDR_TYPE_SDR=0,
    E_HDR_TYPE_HDR10,
    E_HDR_TYPE_HLG,
    E_HDR_TYPE_DOVI,
    E_HDR_TYPE_TECHNI,
    E_HDR_TYPE_HDR10PLUS,
    E_HDR_TYPE_MAX
}ACFG_HDR_TYPE;

typedef struct _HDR_SUPPORT_TYPE
{
    BOOL ui1_hdr_type[E_HDR_TYPE_MAX];
} HDR_SUPPORT_TYPE;


extern INT32 a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data);
extern INT32 a_cfg_custom_set_acr(UINT16 ui2_value);
extern INT32 a_cfg_custom_get_acr(UINT16 *pui2_val);
extern INT32 a_cfg_custom_set_wifi_remote_pair_status(UINT8 ui1_status);
extern INT32 a_cfg_custom_get_wifi_remote_pair_status(UINT8 *pui1_val);
extern INT32 a_cfg_custom_set_last_p2p0_op_channel(UINT8 ui1_status);
extern INT32 a_cfg_custom_get_last_p2p0_op_channel(UINT8 *pui1_val);
extern INT32 a_cfg_custom_set_main_menu_pre_item(UINT8 ui1_idx);
extern INT32 a_cfg_custom_get_main_menu_pre_item(UINT8 *pui1_val);
extern INT32 a_cfg_custom_set_miracast_enable_status(UINT8 ui1_status);
extern INT32 a_cfg_custom_get_miracast_enable_status(UINT8 *pui1_val);
extern INT32 a_cfg_custom_set_scrn_saver_time(UINT16 ui2_val);
extern INT32 a_cfg_custom_get_scrn_saver_time(UINT16 *pui2_val);
extern INT32 a_cfg_custom_set_pic_quality_page(UINT16 ui2_val);
extern INT32 a_cfg_custom_get_pic_quality_page(UINT16 *pui2_val);
#ifdef APP_MENU_3D_BRIGHTNESS_BOOST
extern INT32 a_cfg_custom_set_3d_brightness_boost(UINT16 ui2_value);
extern INT32 a_cfg_custom_get_3d_brightness_boost(UINT16 *pui2_val);
#endif
extern INT32 a_cfg_custom_set_lang_select(UINT16 ui2_value);
extern INT32 a_cfg_custom_get_lang_select(UINT16 *pui2_val);
extern INT32 a_cfg_custom_set_country_select(UINT16 ui2_value);
extern INT32 a_cfg_custom_get_country_select(UINT16 *pui2_val);
extern INT32 a_cfg_custom_set_tz_select(UINT16 ui2_value);
extern INT32 a_cfg_custom_get_tz_select(UINT16 *pui2_val);
extern INT32 a_cfg_custom_get_vol_control(UINT8 *pui1_val);
extern INT32 a_cfg_custom_set_vol_control(UINT8 ui1_value);
extern INT32 a_cfg_custom_update_vol_control(VOID);
extern INT32 a_cfg_custom_save_settings_in_eep(VOID);
extern INT32 a_cfg_custom_check_changed_user_settings(VOID);
extern INT32 a_cfg_custom_init_cache(VOID);
extern INT32 a_cfg_custom_recover_viewport_by_tv(UINT8 i1_viewport_type);
extern INT32 a_cfg_custom_set_reduce_blur(UINT8 ui12_status);
extern INT32 a_cfg_custom_get_reduce_blur(UINT8 *pui1_val);
extern INT32 a_cfg_custom_update_reduce_blur(UINT8 ui1_value);
extern INT32 a_cfg_custom_is_reduce_blur_support(BOOL *pb_support);

extern BOOL a_cfg_cust_FilmMode_CheckIfCanTurnOn(void);
extern INT32 a_cfg_custom_update_film_mode(UINT8 ui1_value);

extern INT32 a_cfg_custom_set_dhcp_status(UINT8 ui1_dhcp_status, UINT8 ui1_idx);
extern INT32 a_cfg_custom_get_dhcp_status(UINT8* pui1_dhcp_status, UINT8 ui1_idx);

extern INT32 a_cfg_cust_set_flat_test_pattern(UINT8 ui1_OnOff, UINT8 ui2_Ydata);
extern INT32 a_cfg_cust_set_smpte_test_pattern(UINT8 ui1_val);
extern INT32 a_cfg_cust_set_ramp_test_pattern(UINT8 ui1_val);
extern INT32 a_cfg_cust_clr_tuner_update_unit_value(VOID);
extern INT32 a_cfg_cust_create_pic_mode(VOID);
extern INT32 a_cfg_cust_delete_pic_mode(VOID);
extern INT32 a_cfg_cust_update_crnt_11_point_value(VOID);
extern INT32 a_cfg_cust_get_cust_pic_mode_name(INT16 i2_pic_mode, CHAR* ps_pic_mode_name,UINT32 ui4_length);
extern INT32 a_cfg_cust_set_cust_pic_mode_name(INT16 i2_pic_mode, CHAR* ps_pic_mode_name);
extern INT32 a_cfg_cust_get_cust_pic_mode_lock_status(BOOL* pb_is_lock);
extern INT32 a_cfg_cust_set_cust_pic_mode_lock_status(BOOL b_is_lock);
extern INT32 a_cfg_cust_get_cust_pic_mode_exist_status(INT16 i2_pic_mode, BOOL* pb_is_exist);
extern INT32 a_cfg_cust_get_cust_pic_mode_lock_pwd(CHAR* ps_pwd, UINT32 ui4_length);
extern INT32 a_cfg_cust_set_cust_pic_mode_lock_pwd(CHAR* ps_pwd,UINT32 ui4_length);
extern INT32 a_cfg_cust_get_cust_nw_register_status(UINT8* pui1_reg_status);
extern INT32 a_cfg_cust_set_cust_nw_register_status(UINT8 ui1_reg_status);
extern INT32 a_cfg_cust_blank_screen(VOID);
extern INT32 a_cfg_cust_unblank_screen(VOID);
extern INT32 a_cfg_cust_get_blank_screen_state(VOID* pv_get_info);
extern INT32 a_cfg_get_preset_pic_mode_chg_status(INT16 i2_pic_mode, BOOL* pb_is_chg);
extern INT32 a_cfg_set_preset_pic_mode_chg_status(INT16 i2_pic_mode, BOOL b_is_chg);
extern INT32 a_cfg_set_clr_temp_chg_status(INT16 i2_clr_temp, BOOL b_is_chg);
extern INT32 a_cfg_get_clr_temp_chg_status(INT16 i2_clr_temp, BOOL* pb_is_chg);
extern INT32 a_cfg_reset_clr_tuner(INT16 i2_clr_temp);
extern INT32 a_cfg_reset_current_color_tuner(INT16 i2_pic);
extern INT32 a_cfg_reset_current_color_temperature(INT16 i2_clr_temp);
extern BOOL a_cfg_cust_check_current_color_tuner_chg_status(VOID);
extern BOOL a_cfg_cust_check_current_wb_tuner_chg_status(VOID);
extern INT32 a_cfg_custom_set_tv_name(CHAR *ps_tv_name);
extern INT32 a_cfg_custom_get_tv_name(CHAR *ps_tv_name,
                                              UINT32* pui4_len);
extern INT32 a_cfg_reset_preset_pic_mode(VOID);
extern INT32 a_cfg_reset_all_pic_settings(VOID);
extern INT32 a_cfg_reset_preset_pic_mode_ex(INT16  i2_pic_mode);
extern INT32 acfg_cust_video_get_cust_gamma_def_value(
    INT16   i2_pic_mode,
    INT16*  pi2_val);
extern INT32 acfg_cust_video_get_cust_clear_action_def_value(
    INT16 i2_pic_mode,
    INT16 * pi2_val);
extern INT32 a_cfg_cust_set_color_space_value(UINT8  ui1_value);
extern BOOL a_cfg_cust_get_support_clear_aciton(VOID);
//extern INT32 a_cfg_cust_drv_set_full_color_444(SCC_VID_HDMI_MODE_T e_hdmi_mode);
extern INT32 a_cfg_cust_drv_set_full_color_444(UINT8 u8_full_color_444);



/* channel scan status */
extern INT32 a_cfg_cust_get_crnt_ch_scan_status(UINT8* pui1_ch_scan_status);
extern INT32 a_cfg_cust_set_crnt_ch_scan_status(UINT8 ui1_ch_scan_status);
extern INT32 a_cfg_cust_get_ch_scan_status(UINT8 ui1_bs_src,
                                          UINT8* pui1_ch_scan_status);
extern INT32 a_cfg_cust_set_ch_scan_status(UINT8 ui1_bs_src,
	                                            UINT8 ui1_ch_scan_status);


extern INT32 acfg_cust_video_get_reduce_blur_def_value(
    INT16   i2_pic_mode,
    INT16*  pi2_val);

extern INT32 acfg_cust_video_get_game_mode_def_value(
    INT16   i2_pic_mode,
    INT16*  pi2_val);

extern INT32 a_cfg_reset_preset_pic_mode_by_ipt(INT16  i2_pic_mode,UINT8 ui1_inp_src);
extern INT32 a_cfg_set_preset_pic_mode_chg_status_by_ipt(UINT8 ui1_pic_mode,UINT8 ui1_ipt_grp,UINT8 ui1_type, BOOL b_is_chg);
extern INT32 a_cfg_set_preset_pic_mode_chg_status_ex(INT16 i2_pic_mode, BOOL b_is_chg);
extern INT32 a_cfg_cust_update_color_tuner(VOID);
extern INT32 acfg_cust_video_get_di_film_mode_def_value(
    INT16*  pi2_val);

extern INT32 a_cfg_cust_set_sys_boot_up_times(UINT32 ui4_sys_boot_up_times);
extern INT32 a_cfg_cust_get_sys_boot_up_times(UINT32 *pui4_sys_boot_up_times);
extern INT32 a_cfg_cust_set_sys_total_running_time(UINT32 ui4_running_times);
extern INT32 a_cfg_cust_get_sys_total_running_time(UINT32 *pui4_running_times);
extern INT32 a_cfg_cust_set_log_to_usb_status(UINT8 ui1_log_to_usb_status);
extern INT32 a_cfg_cust_get_log_to_usb_status(UINT8 *pui1_log_to_usb_status);
extern INT32 a_cfg_set_blegatt_macaddress_threshold(BLE_CACHE_DEVICE* ui1_value);
extern INT32 a_cfg_get_blegatt_macaddress_threshold(BLE_CACHE_DEVICE *pui1_value);

extern INT32 a_cfg_custom_set_speakers_out(UINT16 ui1_status);
extern INT32 a_cfg_custom_get_speakers_out(UINT16 *pui1_val);

extern INT32 a_cfg_custom_set_earc(UINT16 ui1_status);
extern INT32 a_cfg_custom_get_earc(UINT16 *pui1_val);

extern INT32 a_cfg_custom_set_digital_audio(UINT16 ui1_status);
extern INT32 a_cfg_custom_get_digital_audio(UINT16 *pui1_val);

extern INT32 a_cfg_set_fs_partition_all (VOID);
extern BOOL a_cfg_is_fs_partition_all (VOID);

#ifdef ACFG_CUSTOM_DEF_UPDATE_TIME_ZONE
extern INT32 acfg_custom_update_time_zone (VOID);
extern INT32 acfg_custom_update_cast_time (VOID);
#endif

extern INT32 a_cfg_custom_get_odm_idx(UINT8 *pui1_odm_idx);
extern INT32 a_cfg_custom_get_model_idx(UINT32 *pui4_model_idx);
extern INT32 a_cfg_custom_get_model_name(CHAR *ps_model_name);

typedef enum
{
    CUS_MODEL_UNKNOWN, // Unknown

    // 2020-5691 Series ...
    CUS_MODEL_2020_91_V5, // 1, V**5-H**: V585-H1
    CUS_MODEL_2020_91_M6, // 2, M**6-H*: M556-H1/M586x-H1
    CUS_MODEL_2020_91_M7, // 3, M***7-H*: M55Q7-H1
    CUS_MODEL_2020_91_M8, // 4, M***8-H*: M55Q8-H1

    // 2020-5695 Series ...
    CUS_MODEL_2020_95_P9,   // 5, P***9-H**: P65Q9-H1
    CUS_MODEL_2020_95_PX,   // 6, P***X-H*: P75QX-H1
    CUS_MODEL_2020_95_OLED, // 7, OLED**-H*: OLED55-H1/OLED65-H1

    // 2021-5583 Series ...
    CUS_MODEL_2021_83_2K_D_HD,  // 8, D**h-J**: D32h-J05
    CUS_MODEL_2021_83_2K_D_FHD, // 9, D**f*-J**: D24f4-J01/D24f-J09

    // 2021-5691 Series ...
    CUS_MODEL_2021_91_V5, // 10, V**5-J**: V435-J01
    CUS_MODEL_2021_91_V6, // 11, V**6*-J**: V556-J01/V556*-J01
    CUS_MODEL_2021_91_M6, // 12, M***6-J**: M50Q6-J01
    CUS_MODEL_2021_91_M7, // 13, M***7-J**: M50Q7-J01
    CUS_MODEL_2021_91_M8, // 14, M***8-J**: none

    // 2021-5695 Series ...
    CUS_MODEL_2021_95_P9,   // 15, P***9-J**: P65Q9-J01
    CUS_MODEL_2021_95_PX,   // 16, P***X-J**:
    CUS_MODEL_2021_95_OLED, // 17, OLED**-J*:

    // 2021-5695L Series ...
    CUS_MODEL_2021_95L_V6,  // 18, V**C6-J**: V50C6-J09, V65C6-J09,

    // 2022-5691 Series ...
    CUS_MODEL_2022_91_M6,  // 19, M**Q6-K**:
    CUS_MODEL_2022_91_V6,  // 20, V**Q6-K**:

    // 2022-5583 Series ...
    CUS_MODEL_2022_83_2K_D,  // 21, D**F4-K**:

    // 2022-5695S Series ...
    CUS_MODEL_2022_95S_M9,  // 22, M**Q9-K**: M43Q9-K01, M65Q9-K03
    CUS_MODEL_2022_95S_P,   // 23, P65QXM-K04

    // 2022-5695L Series ...
    CUS_MODEL_2022_95L_V6,  // 24, V**CM-K**: V50CM-K09, V65CM-K09,

}EnuCusModelSeries;
EnuCusModelSeries a_cfg_cust_get_CurModelSeries(void);

UINT16 a_cfg_cust_get_CurModelYear(void);
BOOL a_cfg_cust_Is_CurModel_2020(void);
BOOL a_cfg_cust_Is_CurModel_2021(void);

#define a_cfg_cust_Is_CurModel_2021_J a_cfg_cust_Is_CurModel_2021
BOOL a_cfg_cust_Is_CurModel_after_2021_J(void);

BOOL a_cfg_cust_Is_CurModel_2022_K(void);
BOOL a_cfg_cust_Is_CurModel_after_2022_K(void);

BOOL a_cfg_cust_Is_CurModel_OLED(void);
BOOL a_cfg_cust_Is_CurModel_P_series(void);


EnuCusModelSeries a_cfg_cust_Convert_ModelNameToModelSeries(const CHAR* pcModelName);
void a_cfg_cust_get_wifi_model_name(CHAR *ps_model_name, int size);
//=====================================================================================================

/* KK_PORTING */
extern INT32 a_cfg_cust_set_Gamma_table(VID_CUSTOM_TYPE_SET_NVM_GAMMA_T prNVMGamma);
/* for INX Gamma table*/
extern INT32 a_cfg_cust_set_Gamma_table_For_INX(VID_CUSTOM_TYPE_SET_NVM_GAMMA_T prNVMGamma);
INT32 a_cfg_cust_get_gamma_table(VOID* pv_data, SIZE_T z_size_val);
INT32 a_cfg_cust_set_gamma_on_off(BOOL bOnOff);
INT32 a_cfg_cust_get_gamma_on_off(BOOL *bOnOff);
INT32 a_cfg_cust_set_gamma_enable_by_temp(VOID* pv_data, SIZE_T z_size_val);
extern INT32 VIZIO_Picture_mode_D_SET(UINT16 ui2_idx);
extern INT32 VIZIO_COPY_Picture_mode_D_SET(INT16 ui2_idx);

BOOL a_cfg_cust_BacklightCtrl_CheckIfCanTurnOn(void);
extern INT32 VIZIO_BACKLIGHT_CONTROL_D_SET(UINT16 ui2_idx);
extern INT32 VIZIO_BACKLIGHT_CONTROL_D_SET_FORCE(UINT16 ui2_idx);
extern VOID a_cfg_cust_backlight_ctrl_lock(BOOL b_lock);

extern INT32 VIZIO_SMART_DIMMING_D_SET(UINT16 ui2_idx);

BOOL a_cfg_cust_LightSensor_CheckIfCanTurnOn(void);
extern INT32 VIZIO_AMBIENT_LIGHT_SENSOR_D_SET(UINT16 ui2_idx);

extern INT32 VIZIO_ADAPTIVE_LUMA_D_SET(UINT16 ui2_idx);

// ClearAction
BOOL a_cfg_cust_ClaerAction_if_can_turn_on(void);
extern INT32 VIZIO_CLEAR_ACTION_D_SET(UINT16 ui2_idx);

extern INT32 VIZIO_EXTREME_BLACK_ENGINE_D_SET(UINT16 ui2_idx);
extern INT32 VIZIO_EXTREME_BLACK_ENGINE_D_SET_FORCE(UINT16 ui2_idx);
extern INT32 a_cfg_custom_set_oobe_mode(BOOL b_enable);
extern INT32 VIZIO_BACKLIGHT_CONTROL_FOR_LD_SCANING(BOOL ui2_idx);

/* use internet time set*/
extern INT32 a_cfg_cust_set_net_time(UINT8 net_time_status);

/* use internet time get*/
extern INT32 a_cfg_cust_get_net_time(UINT8* net_time_status);

/* rest time format set*/
extern INT32 a_cfg_cust_set_time_format(UINT8  time_format);

/* rest time format get*/
extern INT32 a_cfg_cust_get_time_format(UINT8* time_format);

/* last channel id set*/
extern INT32 a_cfg_cust_set_last_channel_id(UINT32  ui4_channel_id);

/* last channel id  get*/
extern INT32 a_cfg_cust_get_last_channel_id(UINT32* pui4_channel_id);

/* channel tuner type set*/
extern INT32 a_cfg_cust_set_last_channel_tuner_type(UINT8  ui1_tt);

/* channel tuner type get*/
extern INT32 a_cfg_cust_get_last_channel_tuner_type(UINT8*  pui1_tt);

extern VOID sys_asp_ratio_set_h_size (INT32 i4_h_size);
extern VOID sys_asp_ratio_set_v_size (INT32 i4_v_size);
extern VOID sys_asp_ratio_set_h_pos (INT32 i4_h_pos);
extern VOID sys_asp_ratio_set_v_pos (INT32 i4_v_pos);

/* used for record 1st time chose HDMI-x/COMP */
extern INT32 a_cfg_cust_get_ipts_select_state(UINT8* ipts_sel_st);
extern INT32 a_cfg_cust_set_ipts_select_state(UINT8 ipts_sel_st);
/*channel scan progress*/
extern INT32 a_cfg_cust_set_ch_scan_progress(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_ch_scan_progress(UINT8* pui1_value);

extern INT32 a_cfg_cust_set_wzd_sys_upgrade_status(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_wzd_sys_upgrade_status(UINT8* pui1_value);

extern INT32 a_cfg_custom_set_cast_name(CHAR *ps_tv_name);
extern INT32 a_cfg_custom_get_cast_name(CHAR *ps_tv_name,
                                              UINT32* pui4_len);

extern INT32 a_cfg_cust_set_force_reboot_up_flag(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_force_reboot_up_flag(UINT8* pui1_value);

extern INT32 a_cfg_cust_set_zoom_mode(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_zoom_mode(UINT8* pui1_value);
extern INT32 a_cfg_cust_get_zoom_status(UINT8* pui1_value);

extern INT32 a_cfg_cust_set_vol_control_dis_flag(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_vol_control_dis_flag(UINT8* pui1_value);

extern INT32 a_cfg_cust_set_full_color_444(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_full_color_444(UINT8* pui1_value);
#if(ENABLE_COLOR_444_TO_422_NEW_SPEC)
extern INT32 a_cfg_cust_set_full_color_444_ForCurHDMI(UINT8 ui1_value);
extern INT32 a_cfg_cust_get_full_color_444_ForCurHDMI(UINT8* pui1_value);
#endif

extern INT32 a_cfg_cust_set_hide_from_input(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_hide_from_input(UINT8* pui1_value);

extern INT32 a_cfg_cust_set_full_uhd_color(UINT8  ui1_value);
extern INT32 a_cfg_cust_set_full_uhd_color_by_hdmi_idx(UINT8 u8_hdmi_idx, UINT8 ui1_value);

extern INT32 a_cfg_cust_get_full_uhd_color(UINT8* pui1_value);
extern INT32 a_cfg_cust_get_full_uhd_color_by_hdmi_idx(UINT8 u8_hdmi_idx, UINT8* pui1_value);


extern INT32 a_cfg_cust_set_hide_from_input_manually(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_hide_from_input_manually(UINT8* pui1_value);

extern INT32 a_cfg_cust_set_oobe_ir_mode(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_oobe_ir_mode(UINT8* pui1_value);
extern INT32 a_cfg_custom_get_vtrl_name(UINT16 ui2_cfg_idx,CHAR *ps_vtrl_name,
                                              UINT32* pui4_len);
extern INT32 a_cfg_custom_set_vtrl_name(UINT16 ui2_cfg_idx,CHAR *ps_vtrl_name);

extern INT32 a_cfg_cust_set_color_tune_offset(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_color_tune_offset(UINT8* pui1_value);
extern INT32 a_cfg_cust_set_white_balance_offset(INT16 i2_value);
extern INT32 a_cfg_cust_get_white_balance_offset(INT16 *pi2_value);
/* retail mode set*/
extern INT32 a_cfg_cust_set_retail_mode_first_time_setting(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_retail_mode_first_time_setting(UINT8* pui1_value);
extern INT32 a_cfg_cust_set_retail_mode_source_info(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_retail_mode_source_info(UINT8* pui1_value);

extern INT32 a_cfg_set_vtrl_name (UINT8 ui1_source_id, VOID* pt_vtrl_name,SIZE_T z_size);

extern INT32 a_cfg_get_vtrl_name (UINT8 ui1_source_id, VOID* pt_vtrl_name,SIZE_T z_size);

extern INT32 a_cfg_set_name_display (UINT8  ui1_lang_id, UINT8 ui1_source_id,VOID* pt_vtrl_name,SIZE_T z_size);
extern INT32 a_cfg_get_name_display (UINT8  ui1_lang_id, UINT8 ui1_source_id,VOID* pt_vtrl_name,SIZE_T z_size);
extern VOID a_cfg_set_bgm_wake_disable(BOOL b_disable_bgm);
extern BOOL a_cfg_get_bgm_wake_up(VOID);
extern INT32 a_cfg_cust_get_hdmi_dectect_range(UINT8* ui1_range);
extern UINT8 acfg_check_play_content(VOID);
extern UINT16 a_cfg_get_local_dimming_mlm_string(VOID);
extern INT32 VIZIO_CTRL_ENABLE_SPI_HW_MODE(UINT16 ui2_idx);
extern INT32 a_cfg_get_dolby_version_info(DRV_CUSTOM_DOLBY_VERSION_TYPE_T* pt_dv_info);
INT32 a_cfg_cust_set_local_dimming_value(UINT8  ui1_value);
INT32 a_cfg_cust_get_local_dimming_value(UINT8*  ui1_value);
extern BOOL a_cfg_cust_get_support_local_dimming(VOID);
extern UINT8 a_cfg_gethdmiports(VOID);
extern VOID acfg_custom_set_wakeup_time(INT32 time);
extern VOID acfg_custom_power_off_by_python();
extern INT32 a_cfg_cust_set_demo_mode_value(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_demo_mode_value(UINT8* ui1_value);
extern INT32  a_cfg_11_point_gain_default(VOID);

extern INT32 a_cfg_cust_get_ota_loop_test(UINT8 *pui1_value);
extern INT32 a_cfg_cust_set_ota_loop_test(UINT8 ui1_value);
extern INT32 a_cfg_cust_set_memc(UINT8 ui1_value);
extern INT32 a_cfg_cust_get_memc(UINT8 *pui1_value);
extern INT32 a_cfg_cust_get_limited_ad_tracking(UINT8 *pui1_value);
extern INT32 a_cfg_cust_set_limited_ad_tracking(UINT8 ui1_value);
extern INT32 a_cfg_cust_set_log_level(UINT8 log_level);
extern INT32 a_cfg_cust_get_log_level(UINT8 *log_level);
extern INT32 a_cfg_cust_set_vlog_status(UINT8 ui1_vlog_status);
extern INT32 a_cfg_cust_get_vlog_status(UINT8* pui1_vlog_status);
extern INT32 a_cfg_cust_get_color_space_value(UINT8* ui1_value);
extern BOOL a_cfg_get_energy_star(VOID);
extern BOOL a_cfg_cust_get_support_energy_start_by_mode_name(VOID);

// Black detail
extern BOOL a_cfg_cust_contrast_en_CheckIfCanTurnOn(void);
extern INT32 a_cfg_cust_drv_set_contrast_enhancement(UINT8 ui1_idx);

extern INT32 a_cfg_cust_drv_set_super_resolution(UINT8 ui1_idx);
INT32 a_cfg_cust_drv_set_edge_enhancement(UINT8 ui1_idx);
INT32 a_cfg_cust_drv_set_peak_lunminance(UINT8 ui1_idx);
extern INT32 a_cfg_cust_drv_set_judder_reduction(UINT8 ui1_idx);
extern INT32 a_cfg_cust_drv_set_motion_blur_reduction(UINT8 ui1_idx);

BOOL a_cfg_cust_local_contrast_CheckIfCanTurnOn(void);
INT32 a_cfg_cust_drv_set_local_contrast(UINT8 ui1_idx);

INT32 a_cfg_cust_drv_set_contour_smoothing(UINT8 ui1_idx);
BOOL a_cfg_cust_is_variable_refresh_rate_support(VOID);
BOOL a_cfg_cust_is_FreeSync_logo_support(VOID);
extern INT32 a_cfg_cust_drv_set_variable_refresh_rate(UINT8 ui1_idx);
BOOL a_cfg_cust_drv_get_allm_status(VOID);
BOOL a_cfg_cust_is_support_progaming_engine(VOID);
BOOL a_cfg_cust_is_support_game_low_latency(VOID);
void a_acfg_update_gaming_logo(void);
BOOL a_cfg_cust_is_gll_support_and_gaming_engine_no_support(VOID);
extern INT32 a_cfg_cust_drv_set_game_low_latency(UINT8 ui1_idx);
extern BOOL a_cfg_cust_GLL_get_force_value(UINT8* pu8_GLL_setting);


INT32 a_cfg_cust_drv_set_game_hdr(UINT8 ui1_idx);
INT32 a_cfg_cust_drv_set_game_mode(BOOL b_enable);
extern INT32 a_cfg_cust_drv_set_drv_eotf(UINT8 ui1_idx);

// Enhance View Angle
BOOL a_cfg_cust_en_view_angle_Is_Panel_Support_But_UI_Not_Support(void);
BOOL a_cfg_cust_en_view_angle_support(VOID);
BOOL a_cfg_cust_enhanced_viewing_angle_IfCanTurnOn(void);
extern INT32 a_cfg_cust_drv_set_enhanced_viewing_angle(UINT8 ui1_idx);

extern INT32 a_cfg_cust_drv_set_20_p_wb(VOID);
INT32 a_cfg_cust_set_color_temp(UINT8 ui1_idx);
INT32 a_cfg_cust_set_flat_pattern(UINT8 ui1_idx);
INT32 a_cfg_cust_set_rgb_pattern(VOID* pv_data, SIZE_T z_size_val);
INT32 a_cfg_update_20_point(VOID* pv_GammactrlPts, SIZE_T z_size_val);
INT32 a_cfg_cust_user_set_color_tuner_hsb(UINT8 ui1_main_item);
INT32 a_cfg_cust_drv_set_drv_film_maker_mode(UINT8 ui1_idx);
INT32 a_cfg_cust_drv_set_drv_Lcdim_Scrolling_OnOff(BOOL bOnOff);
BOOL a_cfg_cust_drv_get_drv_game_mode_enable(VOID);
BOOL a_acfg_cust_is_gll_enable(VOID);
UINT8 a_cfg_cust_get_pqbypass_status(VOID);
INT32 a_cfg_cust_drv_set_pq_bypass(UINT8 ui1_idx);
INT32 a_cfg_cust_drv_set_pq_bypass_ex(VOID* pv_data, SIZE_T z_size_val);
INT32 a_cfg_cust_get_yuv_data(VOID* pv_s_data, SIZE_T z_s_size_val,VOID* pv_g_data, SIZE_T z_g_size_val);
INT32 a_cfg_cust_get_rgb_output_status(UINT16 ui2_x_pos, UINT16 ui2_y_pos, UINT16 *pui2_RGB);
INT32 a_cfg_cust_drv_read_panel_nits(UINT16 *ui2_panel_nits);
INT32 a_cfg_cust_drv_write_panel_nits(UINT16 ui2_panel_nits, UINT8 ui1_col_tmp);
INT32 a_cfg_cust_drv_update_panel_nits(VOID);
BOOL a_cfg_cust_drv_get_memc_enable(VOID);
BOOL a_cfg_cust_drv_get_4k_source(VOID);
INT32 a_cfg_cust_drv_get_RJ45_addr(UINT32 *pui4_addr);
INT32 a_cfg_cust_drv_read_RJ45_value(UINT8 *aui1_val);
INT32 a_cfg_cust_drv_write_RJ45_value(UINT8* aui1_val);
INT32 a_cfg_cust_drv_update_eth0_mac(VOID);
BOOL a_cfg_cust_drv_is_lightsensor_support(VOID);
INT32 a_cfg_cust_drv_set_vcom_pattern(VOID* pv_data, SIZE_T z_size_val);
INT32 a_cfg_cust_drv_set_mod_pattern(VOID* pv_data, SIZE_T z_size_val);


extern INT32 a_cfg_cust_drv_set_oled_off_rs(UINT8 ui1_idx);
extern BOOL a_cfg_cust_drv_get_oled_off_rs(VOID);
extern BOOL a_cfg_cust_drv_get_oled_off_rs_jb_status(VOID);
extern BOOL a_cfg_cust_drv_get_oled_on_rf_status(VOID);
extern INT32 a_cfg_cust_drv_set_oled_jb(UINT8 ui1_idx);
extern BOOL a_cfg_cust_drv_get_oled_jb(VOID);
extern INT32 a_cfg_cust_drv_set_oled_display_time(UINT32 ui4_idx);
extern INT32 a_cfg_cust_drv_get_oled_display_time(UINT32* pui4_idx);
extern INT32 a_cfg_custom_set_oled_panel_display_time(UINT32 ui4_val);
extern INT32 a_cfg_custom_get_oled_panel_display_time(UINT32 *pui4_val);
extern INT32 a_cfg_custom_set_oled_jb_cooling_time(UINT16 ui2_val);
extern INT32 a_cfg_custom_get_oled_jb_cooling_time(UINT16 *pui2_val);
extern INT32 a_cfg_custom_set_oled_demo_mode_decline_time(INT64 t_val);
extern INT64 a_cfg_custom_get_oled_demo_mode_decline_time();
extern INT32 a_cfg_custom_set_oled_last_screen_refresh_time(INT64 t_val);
extern INT64 a_cfg_custom_get_oled_last_screen_refresh_time();
extern INT32 a_cfg_custom_set_oled_ex_factory_display_time(UINT32 ui4_val);
extern INT32 a_cfg_custom_get_oled_ex_factory_display_time(UINT32 *pui4_val);
extern INT32 a_cfg_custom_set_oled_ex_factory_offrs_time(UINT32 ui4_val);
extern INT32 a_cfg_custom_get_oled_ex_factory_offrs_time(UINT32 *pui4_val);
extern INT32 a_cfg_custom_set_oled_ex_factory_jb_time(UINT32 ui4_val);
extern INT32 a_cfg_custom_get_oled_ex_factory_jb_time(UINT32 *pui4_val);
extern INT32 a_cfg_custom_set_oled_ex_factory_offrs_count(UINT16 ui2_val);
extern INT32 a_cfg_custom_get_oled_ex_factory_offrs_count(UINT16 *pui2_val);
extern INT32 a_cfg_custom_set_oled_ex_factory_jb_count(UINT16 ui2_val);
extern INT32 a_cfg_custom_get_oled_ex_factory_jb_count(UINT16 *pui2_val);

extern INT32 a_cfg_cust_drv_set_oled_lea(UINT8 ui1_idx);
extern BOOL a_cfg_cust_drv_get_oled_lea(VOID);
extern INT32 a_cfg_cust_drv_set_oled_tpc(UINT8 ui1_idx);
extern BOOL a_cfg_cust_drv_get_oled_tpc(VOID);
extern INT32 a_cfg_cust_drv_set_oled_cpc(UINT8 ui1_idx);
extern BOOL a_cfg_cust_drv_get_oled_cpc(VOID);
extern INT32 a_cfg_cust_drv_set_oled_hdr(UINT8 ui1_idx);
extern BOOL a_cfg_cust_drv_get_oled_hdr(VOID);
extern INT32 a_cfg_cust_drv_set_oled_cmo(UINT8 ui1_idx);
extern BOOL a_cfg_cust_drv_get_oled_cmo(VOID);
extern INT32 a_cfg_cust_drv_set_oled_plc_curve(VOID* pv_data, SIZE_T z_size_val);
extern INT32 a_cfg_cust_drv_get_oled_plc_curve(VOID* pv_data, SIZE_T z_size_val);
extern INT32 a_cfg_cust_drv_get_oled_temperature(UINT8 ui1_idx,UINT32 *pui4_val);
extern INT32 a_cfg_cust_drv_get_oled_support_compensation(UINT32 *pui4_val);
extern INT32 a_cfg_cust_drv_get_oled_display_total(UINT32 *pui4_val);
extern INT32 a_cfg_cust_drv_get_oled_display_period(UINT32 *pui4_val);
extern INT32 a_cfg_cust_drv_set_oled_mute(UINT8 ui1_idx);
extern INT32 a_cfg_custom_set_oled_status(UINT8 ui1_status);
extern INT32 a_cfg_custom_get_oled_status(UINT8 *pui1_val);
extern INT32 a_cfg_custom_set_oled_err_detect_checksum(UINT8 ui1_status);
extern INT32 a_cfg_custom_get_oled_err_detect_checksum(UINT8 *pui1_val);
extern BOOL a_cfg_cust_is_off_rs_enable();
extern BOOL a_cfg_cust_oled_support(VOID);
extern BOOL a_cfg_cust_zoom_digit_selection_support(VOID);
extern INT32 a_cfg_cust_set_oled_panel_refresh_value(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_oled_panel_refresh_value(UINT8* ui1_value);
extern INT32 a_cfg_cust_set_oled_pixel_shift_value(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_oled_pixel_shift_value(UINT8* ui1_value);
extern INT32 a_cfg_cust_drv_set_oled_pixel_shift(UINT8 ui1_idx);
extern INT32 a_cfg_cust_drv_set_oled_orbit(BOOL b_en);

extern BOOL a_cfg_cust_CheckIfPeakLumiCanAdjust(void);
extern INT32 a_cfg_cust_drv_set_oled_panel_gain(UINT8 ui1_idx);
extern INT32 a_cfg_cust_drv_set_oled_panel_power_reset(UINT8 ui1_value);
extern BOOL a_is_oled_compensation_support();

extern INT32 a_cfg_custom_set_oled_error_detect_count(UINT8 ui1_status);
extern INT32 a_cfg_custom_get_oled_error_detect_count(UINT8 *pui1_val);
extern INT32 a_acfg_disp_detect_oled_pal_err_nfy_fct(
                               HANDLE_T                         h_disp,
                               VOID*                            pv_nfy_tag,
                               UINT32                           ui4_data );
extern INT32 a_cfg_custom_set_oled_error_detect_disable(UINT8 ui1_disable);
extern INT32 a_cfg_custom_get_oled_error_detect_disable(UINT8 *pui1_val);

extern ACFG_OLED_ERROR_DETECT_TYPE a_acfg_get_still_image_status(VOID);
extern INT32 a_cfg_custom_set_power_mode_save(UINT8 ui1_val);
extern INT32 a_cfg_custom_get_power_mode_save(UINT8 *pui1_val);

INT32 a_cfg_cust_set_sif_data(VOID* pv_data, SIZE_T z_size_val);
INT32 a_cfg_cust_get_sif_data(VOID* pv_data, SIZE_T z_size_val);
INT32 a_cfg_cust_update_hdcp(VOID);
UINT8 a_acfg_cust_get_video_type(VOID);
UINT8 a_acfg_cust_get_dynamic_range(VOID);
INT32 a_cfg_cust_info_get_gamma_table_from_ini(INT8 i1_idx,ACFG_GAMMA_TABLE_T* pt_gamma_info);
INT32 a_cfg_cust_info_set_gamma_table_to_ini(INT8 i1_idx,ACFG_GAMMA_TABLE_T* pt_gamma_info);
INT32 a_cfg_custom_get_panel_name(CHAR* pt_name);
extern INT32 a_cfg_cust_set_surround_mode(UINT8  ui1_value);
extern INT32 a_cfg_cust_get_surround_mode(UINT8* pui1_value);
extern INT32 a_cfg_cust_get_wifi_module_info(WIFI_DEVICE_INFO* pt_info );
extern INT32 a_cfg_cust_drv_set_spdif_enable(BOOL bOnOff);
INT32 a_cfg_cust_drv_set_blank_screen(UINT8 ui1_idx);
INT32 a_cfg_cust_drv_get_outregion(VOID* pv_data,SIZE_T z_size_val);
INT32 a_cfg_cust_drv_set_outregion(VOID* pv_data, SIZE_T z_size_val);
INT32 a_cfg_cust_drv_get_srcregion(VOID* pv_data, SIZE_T z_size_val);
INT32 a_cfg_cust_drv_set_srcregion(VOID* pv_data, SIZE_T z_size_val);
INT32 a_cfg_cust_update_local_dimming(VOID);
INT32 a_cfg_cust_drv_get_support_hdr_type(VOID* pv_data, SIZE_T z_size_val);

//INT32 a_cfg_cust_drv_get_vrr_status(VOID* pv_data, SIZE_T z_size_val);
BOOL a_cfg_cust_drv_get_vrr_status(void);
BOOL a_cfg_cust_is_VRR_enable_and_driver_detect_VRR(VOID);

BOOL a_cfg_cust_is_tts_item_enable(VOID);

INT32 a_cfg_cust_drv_get_frc_version(VOID* pv_data, SIZE_T z_size_val);

//extern INT32 a_cfg_cust_drv_get_free_sync_rate(VOID* pv_data, SIZE_T z_size_val);
UINT16 a_cfg_cust_drv_get_free_sync_rate(void);

extern VOID a_cfg_cust_audio_mute(BOOL b_mute);
extern VOID a_cfg_cust_audio_mute_to_drv(BOOL b_mute);
extern VOID a_cfg_cust_backlight_onoff(BOOL b_on);
extern VOID a_cfg_cust_panel_onoff(BOOL b_on);
extern UINT32 acfg_default_wakeup_time();

extern VOID a_cfg_set_hdr_type(SCC_VID_HDR_TYPE_T t_hdr_type);
extern INT32 a_cfg_cust_drv_get_pq_ver_by_bin_type(UINT8 ui1_idx, UINT8 *aui1_val, SIZE_T z_size_val);

extern INT32 a_cfg_custom_set_black_pattern(BOOL b_on);

extern UINT32 a_cfg_cust_v_logo_delay();

extern INT32 a_cfg_custom_set_power_mode(UINT16 ui2_eco);
extern INT32 a_cfg_cust_get_automatic_time(UINT8* pui1_value);
extern INT32 a_cfg_cust_set_automatic_time(UINT8  ui1_value);

extern INT32 a_cfg_custom_switch_dv_game_mode(UINT8 ui1_dv_game_mode_flag);
extern UINT8 a_cfg_cust_get_cur_dv_game_mode_flag(VOID);

//===================================================================================================
// This value is sync with BSP, don't change it!!
typedef enum
{
    ACFG_VRR_STATUS_NONE        = 0,
    ACFG_VRR_STATUS_VRR         = 1,
    ACFG_VRR_STATUS_FREE_SYNC   = 2,
    ACFG_VRR_STATUS_UNKNOWN     = 3,
} EnuAcfgVrrStatus;

extern EnuAcfgVrrStatus acfg_cust_get_cur_VrrFreeSync_status(void);
extern void a_acfg_cust_reset_VRR_FreeSync_status(void);
extern UINT8 acfg_cust_get_CurSrcHdmi_UI_Idx(void);
extern BOOL acfg_cust_is_Vrr_or_FreeSync_detected(void);

extern BOOL a_acfg_cust_vrr_is_enable_and_detect_stream(VOID);
extern BOOL a_acfg_cust_is_detect_hdmi_freesync_flag(VOID);
//===================================================================================================

//extern VOID acfg_custom_set_crnt_pic_mode_all_dynamic_en_view_angle_for_on(VOID);
extern INT32 a_cfg_cust_drv_set_backlight_status(BOOL b_enable);
extern INT32 a_cfg_cust_drv_get_backlight_status(BOOL *b_enable);
extern INT32 a_cfg_custom_get_model_group_id(UINT32 *pui4_model_group);
extern INT32 a_cfg_cust_set_panel_ssc_en(BOOL b_enable);
extern INT32 a_cfg_cust_trigger_led_ac_on_ready_action(void);
extern INT32 a_cfg_cust_set_demura(BOOL b_enable);
extern INT32 a_cfg_cust_get_demura(UINT32 *pu4_RegValue);
extern INT32 a_cfg_cust_set_LED_indicator(VOID* pv_data, SIZE_T z_size_val);
extern INT32 a_cfg_cust_set_LED_light_rate(UINT8 u8light_rate);


extern INT32 ACFG_CustDrv_Set_BacklightCtrl( INT8 iBacklightCtrl );
extern INT32 ACFG_CustDrv_Set_Backlight( UINT16 u16Backlight, INT8 iBacklightCtrl );

//===================================================================================================
extern BOOL acfg_custom_get_enable_soundbarsettings(VOID);
extern BOOL acfg_custom_get_soundbarsettings_ready(VOID);
//===================================================================================================
extern BOOL acfg_custom_get_enable_eq(VOID);
extern BOOL acfg_custom_get_enable_bass(VOID);
extern BOOL acfg_custom_get_enable_treble(VOID);
extern BOOL acfg_custom_get_enable_dialogue(VOID);
extern BOOL acfg_custom_get_enable_subwoofer(VOID);
extern BOOL acfg_custom_get_enable_nightmode(VOID);
extern BOOL acfg_custom_get_enable_virtual(VOID);

//===================================================================================================
extern BOOL acfg_custom_get_eq_mode_enable_music(VOID);
extern BOOL acfg_custom_get_eq_mode_enable_movie(VOID);
extern BOOL acfg_custom_get_eq_mode_enable_game(VOID);
extern BOOL acfg_custom_get_eq_mode_enable_direct(VOID);
extern BOOL acfg_custom_get_eq_mode_enable_dialogue(VOID);

//===================================================================================================
extern UINT8 acfg_custom_get_eq_mode_type(VOID);

//===================================================================================================
extern UINT8 acfg_custom_get_bass_type(VOID);
extern UINT8 acfg_custom_get_treble_type(VOID);
extern UINT8 acfg_custom_get_dialogue_type(VOID);
extern UINT8 acfg_custom_get_subwoofer_type(VOID);
extern UINT8 acfg_custom_get_nightmode_type(VOID);
extern UINT8 acfg_custom_get_virtualx_type(VOID);

//====================================================================================================
extern INT32 acfg_custom_set_eq_mode(INT32 i4_val);
extern INT32 acfg_custom_set_bass_val(INT32 i4_val);
extern INT32 acfg_custom_set_treble_val(INT32 i4_val);
extern INT32 acfg_custom_set_dialogue_val(INT32 i4_val);
extern INT32 acfg_custom_set_subwoofer_val(INT32 i4_val);
extern INT32 acfg_custom_set_nightmode_val(INT32 i4_val);
extern INT32 acfg_custom_set_virtualx_val(INT32 i4_val);
extern INT32 acfg_custom_set_speakertest_val(INT32 i4_val);
extern INT32 acfg_custom_set_info_val(INT32 i4_val);
//====================================================================================================
#if 1//(ACFG_CUST_MEMC_NEW_METHOD)
BOOL a_cfg_cust_MEMC_get_UserOnOff(void);
#endif

//====================================================================================================




//====================================================================================================

#endif /* __ACFG_H_ */

