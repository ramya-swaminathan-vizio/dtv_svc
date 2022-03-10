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
 * $Revision: #3 $
 * $Date: 2015/07/14 $
 * $Author: lin.xu $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the internal header file for APP CFG
 *---------------------------------------------------------------------------*/
#ifndef _ACFG_CUST_VIDEO_H_
#define _ACFG_CUST_VIDEO_H_
#include "u_device_type.h"
#include "c_scc.h"



#include "../../../../../linux_core/misdk/mi/mi/mi_header/mi_common.h"
#include "../../../../../linux_core/misdk/mi/mi/mi_header/mi_mm.h"
#include "../../../../../linux_core/misdk/mi/mi/mi_header/mi_aout.h"
#include "../../../../../linux_core/misdk/mi/mi/mi_header/mi_disp.h"
#include "../../../../../linux_core/misdk/mi/mi/mi_header/mi_osd.h"
#include "../../../../../linux_core/misdk/mi/mi/mi_header/mi_os.h"
#include "../../../../../linux_core/misdk/mi/mi/mi_header/mi_sys.h"


/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
/* 3D Picture Settings */
#define VTRL_3D_ELEMENT             (1)
#define ACFG_3D_PIC_MODE_NUM        (ACFG_PIC_MODE_NUM)
#define ACFG_3D_PIC_QLT_ELEM_NUM    (ACFG_3D_PIC_MODE_NUM * VTRL_3D_ELEMENT)

/* Picture Quality */
#define ACFG_PIC_MODE_DEF           (ACFG_CUST_PIC_MODE_BRIGHT)
#define ACFG_VID_RGB_ENABLE         (1)
#define ACFG_VID_RGB_DISABLE        (0)

/*cust pic mode name MAX leng*/
#define APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN         (32)
#define APP_CFG_CUST_PIC_MODE_NAME_ELEM_NUM         ((ACFG_PIC_MODE_ELEM_NUM - ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM)*APP_CFG_CUST_PIC_MODE_NAME_MAX_LEN)



/* define according to the custom spec*/
#define ACFG_PRE_SET_PIC_MODE_NUM   (6)
#define ACFG_CUST_SET_PIC_MODE_NUM  (8)

#define ACFG_CUST_COPY_PIC_MODE_BASE  (20)


/* New cust spec cust pic mode will six, so the check
  *for it will be limit to six num
  */
#define ACFG_CUST_SET_PIC_MODE_NUM_EX  (6)

#define ACFG_VID_SETTINS_GLOBAL_IPT_SRC  (ACFG_CUST_INPUT_GRP_VTRL)


#define ACFG_PIC_MODE_NUM           (ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM)
#define ACFG_INPUT_SRC_NUM          (ACFG_CUST_INPUT_GRP_MAX + VTRL_3D_ELEMENT)


#define APP_CFG_PQ_ITEMS_NUM  (ACFG_CUST_INPUT_GRP_MAX * ACFG_PIC_MODE_NUM)

#define ACFG_PIC_QLT_ELEM_SKIP    (3)
#define ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM       (15)  //Three HDMI and MMP,include HDR10,HLG ,DOLBY VISION,the define is as bellow
/*
        1                2                       3                                     4               5                        6                                    7                  8                           9                          10                11                    12
HDMI1_HDR10  HDMI1_HLG  HDMI1_DOLBY_VISION  HDMI2_HDR10  HDMI2_HLG     HDMI2_DOLBY_VISION  HDMI3_HDR10  HDMI3_HLG   HDMI3_DOLBY_VISION  HDMI4_HDR10  HDMI4_HLG   HDMI4_DOLBY_VISION

       13               14                     15
MMP_HDR10     MMP_HLG    MMP_DOLBY_VISION
*/

#define ACFG_PIC_MODE_ELEM_NUM      (ACFG_CUST_INPUT_GRP_MAX + VTRL_3D_ELEMENT + ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM)
#define ACFG_PIC_QLT_ELEM_NUM       ((ACFG_INPUT_SRC_NUM + ACFG_PIC_QLT_ELEM_HDR10_HLG_NUM)* ACFG_PIC_MODE_NUM)

/*CUST pic exist status (SRC*CUST_PIC)*/
#define APP_CFG_CUST_PIC_EXIST_STUTAS_ELEM_NUM         (ACFG_PIC_MODE_ELEM_NUM*ACFG_CUST_SET_PIC_MODE_NUM)

/*CUST pic lock status (SRC*CUST_PIC)*/
#define APP_CFG_CUST_PIC_LOCK_STUTAS_ELEM_NUM         (1)

#define ACFG_CUST_CLR_GAIN_OFFSET_MIN -100
#define ACFG_CUST_CLR_GAIN_OFFSET_MAX 100

/*  1.8 2.0 2.1 2.2 2.4*/
#define ACFG_CUST_GAMMA_MIN       (0)
#define ACFG_CUST_GAMMA_MAX       (4)

/* auto off on*/
#define ACFG_CUST_GAME_LOW_LATENCY_AUTO      (0)
#define ACFG_CUST_GAME_LOW_LATENCY_OFF       (1)
#define ACFG_CUST_GAME_LOW_LATENCY_ON        (2)

/* eotf */
#define ACFG_CUST_EOTF_MIN       (0)
#define ACFG_CUST_EOTF_MAX       (3)

/* off on*/
#define ACFG_CUST_COMMON_OFF       (0)
#define ACFG_CUST_COMMON_ON        (1)

/*  0 ~ 100 */
#define ACFG_CUST_COMMON_ZERO          (0)
#define ACFG_CUST_COMMON_TEN           (10)
#define ACFG_CUST_COMMON_HUNDRED       (100)

/*11 Point define*/

/* 11point gain will be store by src*clr_tmp*/
#define ACFG_CUST_11_GAIN_MIN       (0)
#define ACFG_CUST_11_GAIN_MAX       (19)

#define ACFG_CUST_11_WB_MIN         (-50)
#define ACFG_CUST_11_WB_MAX         (50)

#define APP_CFG_11_POINT_GAIN_NUM             (20)
#define APP_CFG_DYNAMIC_RANGE_NUM             (4)

#define APP_CFG_11_POINT_GAIN_ELEM_NUM        (APP_CFG_DYNAMIC_RANGE_NUM*ACFG_CLR_TEMP_NUM)

/* hue rgb will be store by dynamic_range by  picture mode by input source*/
/*preset picture mode * dynamic * input soure  + custom picture mode * dynamic*/
#define APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC    (ACFG_INPUT_SRC_NUM * APP_CFG_DYNAMIC_RANGE_NUM * ACFG_PRE_SET_PIC_MODE_NUM)
#define APP_CFG_CUS_PIC_BY_DYNAMIC              (APP_CFG_DYNAMIC_RANGE_NUM * ACFG_CUST_SET_PIC_MODE_NUM)

#define APP_CFG_HRGB_ELEM_NUM                 (APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + APP_CFG_CUS_PIC_BY_DYNAMIC)

/* 2p wb  will be store by dynamic_range by color tempture */
#define APP_CFG_2_POINT_WB_ELEM_NUM          (APP_CFG_DYNAMIC_RANGE_NUM*ACFG_CLR_TEMP_NUM)

/* PRE-SET pic mode change status*/
#define APP_CFG_PRE_SET_PIC_ELEM_NUM           (APP_CFG_DYNAMIC_RANGE_NUM*ACFG_PRE_SET_PIC_MODE_NUM)

/* 11point gain RGB will be store by src*clr_tmp*11_GAIN*/
//new ic support 20 point wb ,reuse the 11 point wb acfg position
#define APP_CFG_11_POINT_GAIN_RGB_ELEM_NUM    (APP_CFG_DYNAMIC_RANGE_NUM*ACFG_CLR_TEMP_NUM*APP_CFG_11_POINT_GAIN_NUM)

/*custom gamma*/
#define ACFG_VID_CUST_GAMMA_ELEM_NUM            (ACFG_PIC_QLT_ELEM_NUM)
#define ACFG_VID_CUST_FULL_COLOR_444            (1)

#define ACFG_PRE_SET_PIC_MODE_CHG_ELEM_NUM   (APP_CFG_PRE_PIC_BY_SOURCE_BY_DYNAMIC + APP_CFG_CUS_PIC_BY_DYNAMIC)

/* 3D Color Temperature */
#define ACFG_3D_CLR_TEMP_DEF           (3)
#define ACFG_3D_CLR_TEMP_NUM           (4)
#define ACFG_3D_CLR_TEMP_ELEM_NUM      (ACFG_3D_PIC_QLT_ELEM_NUM) //(ACFG_CUST_INPUT_GRP_MAX * ACFG_PIC_MODE_NUM)
#define ACFG_3D_CLR_GAIN_ELEM_NUM      (ACFG_CLR_TEMP_NUM * (VTRL_3D_ELEMENT)) //(ACFG_CLR_TEMP_NUM * ACFG_CUST_INPUT_GRP_MAX) /* 4(mode) * 10(input_grp) */
#define ACFG_3D_CLR_OFFSET_ELEM_NUM    (ACFG_CLR_TEMP_NUM * (VTRL_3D_ELEMENT)) //(ACFG_CLR_TEMP_NUM * ACFG_CUST_INPUT_GRP_MAX) /* 4(mode) * 10(input_grp) */

/* Color Temperature */
#define ACFG_CLR_TEMP_DEF           (3)
#define ACFG_CLR_TEMP_NUM           (4)

/*CLR TEMP store the same as pq*/
#define ACFG_CLR_TEMP_ELEM_NUM      (ACFG_PIC_QLT_ELEM_NUM)

#define ACFG_CLR_GAIN_ELEM_NUM      (ACFG_CLR_TEMP_NUM * ACFG_INPUT_SRC_NUM)
#define ACFG_CLR_OFFSET_ELEM_NUM    (ACFG_CLR_TEMP_NUM * ACFG_INPUT_SRC_NUM)

/* Screen Mode */
#define ACFG_SCR_MODE_DEF           (SCC_VID_SCREEN_MODE_NORMAL)
#define ACFG_SCR_MODE_ELEM_FOR_MMP  (2)
#define WIDE_FUNCTION_ELEM          (27)

                                    /* New request: Screen mode setting by Source/Resolution */
                                    /* special case for ACFG_SCR_MODE_ELEM_FOR_MMP. In MMP case, */
                                    /* Screen mode only have 2 kind of setting. 16:9 and 4:3.*/
#define ACFG_SCR_MODE_ELEM_NUM      (WIDE_FUNCTION_ELEM + ACFG_SCR_MODE_ELEM_FOR_MMP )/*(ACFG_CUST_INPUT_GRP_MAX + 1)*/ /* Stored by "Input Group" + "MMP" */

#ifdef APP_MJC_SUPPORT
/* Smooth Motion Effect */
#define ACFG_VID_MJC_EFFECT_DEF         SCC_VID_MJC_EFFECT_MIDDLE
#define ACFG_VID_MJC_EFFECT_MIN         SCC_VID_MJC_EFFECT_OFF
#define ACFG_VID_MJC_EFFECT_MAX         SCC_VID_MJC_EFFECT_HIGH

/* Real Cinema Mode */
#define ACFG_VID_MJC_MODE_DEF_60HZ      SCC_VID_MJC_MODE_0
#define ACFG_VID_MJC_MODE_DEF_120HZ     SCC_VID_MJC_MODE_1
#define ACFG_VID_MJC_MODE_DEF           SCC_VID_MJC_MODE_0
#define ACFG_VID_MJC_MODE_MIN           SCC_VID_MJC_MODE_0
#define ACFG_VID_MJC_MODE_MAX           SCC_VID_MJC_MODE_2
#endif

/* Noise Reduction */
#define ACFG_VID_NR_ELEM_NUM        (ACFG_PIC_QLT_ELEM_NUM) /* MPEG NR */
#define ACFG_VID_3D_NR_ELEM_NUM     (ACFG_PIC_QLT_ELEM_NUM) /* Noise Reduction */
#define ACFG_VID_LOCAL_CONTRAST_ELEM_NUM      (ACFG_PIC_QLT_ELEM_NUM)

/* MPEG NR */
#define ACFG_VID_MPEG_NR_DEF            (SCC_VID_MPEG_NR_LOW)
#define ACFG_VID_MPEG_NR_ELEM_NUM       (ACFG_PIC_QLT_ELEM_NUM)
#define ACFG_VID_MPEG_NR_MIN            (SCC_VID_MPEG_NR_OFF)
#define ACFG_VID_MPEG_NR_MAX            (SCC_VID_MPEG_NR_HIGH)


#ifdef APP_GAME_MODE_SUPPORT
/* GAME MODE */
#define ACFG_VID_GAME_MODE_DEF              ((UINT8)SCC_VID_GAME_MODE_OFF)
#define ACFG_VID_GAME_MODE_ELEM_NUM         (ACFG_PIC_QLT_ELEM_NUM)
#define ACFG_VID_GAME_MODE_MIN              ((UINT8)SCC_VID_GAME_MODE_OFF)
#define ACFG_VID_GAME_MODE_MAX              ((UINT8)SCC_VID_GAME_MODE_ON)
#endif

/* Color Enhancement */
#define ACFG_VID_FT_ELEM_NUM        (ACFG_PIC_QLT_ELEM_NUM)

/* Adaptive Luma */
#define ACFG_VID_LUMA_ELEM_NUM       (ACFG_PIC_QLT_ELEM_NUM)

/* Film Mode */
#define ACFG_VID_DI_FILM_MODE_DEF       ((UINT8) SCC_VID_DI_FILM_MODE_ACTION_PICTURE)
#if 0
#define ACFG_VID_DI_FILM_MODE_ELEM_NUM  (2)
#else
#define ACFG_VID_DI_FILM_MODE_ELEM_NUM  (ACFG_PIC_QLT_ELEM_NUM)
#endif
#define ACFG_VID_DI_FILM_MODE_MIN       ((UINT8) SCC_VID_DI_FILM_MODE_OFF)
#define ACFG_VID_DI_FILM_MODE_MAX       ((UINT8) SCC_VID_DI_FILM_MODE_ACTION_PICTURE)


/* Backlight*/
#define ACFG_DISP_BACK_LIGHT_ELEM_NUM       (ACFG_PIC_QLT_ELEM_NUM)
#define ACFG_DISP_ADP_BACK_LIGHT_ELEM_NUM   (ACFG_PIC_QLT_ELEM_NUM)

#define ACFG_VID_POS_H_DEF                  ( 0)
#define ACFG_VID_POS_H_MIN                  (-50)
#define ACFG_VID_POS_H_MAX                  ( 50)
#define ACFG_VID_POS_H_ELEM_NUM             ( 24)
#define ACFG_VID_POS_V_DEF                  ( 0)
#define ACFG_VID_POS_V_MIN                  (-50)
#define ACFG_VID_POS_V_MAX                  ( 50)
#define ACFG_VID_POS_V_ELEM_NUM             ( 24)

/* H size and V size. */
#define ACFG_CUSTOM_H_SIZE_MIN              (-50)
#define ACFG_CUSTOM_H_SIZE_MAX              (50)
#define ACFG_CUSTOM_H_SIZE_ELEM_NUM         (ACFG_VID_POS_H_ELEM_NUM)
#define ACFG_CUSTOM_V_SIZE_MIN              (-50)
#define ACFG_CUSTOM_V_SIZE_MAX              (50)
#define ACFG_CUSTOM_V_SIZE_ELEM_NUM         (ACFG_VID_POS_V_ELEM_NUM)

/* Custom config for the mute manger */
#define ACFG_MM_CUST_VMUTE_CONFIG

/*COLOR TUNER TEST PATTERN SCREEN MODE NUM*/
#define    ACFG_TEST_PATTERN_SCRN_MODE_NORMAL    (2)
#define    ACFG_TEST_PATTERN_SCRN_MODE_WIDE      (1)
#define    ACFG_TEST_PATTERN_SCRN_MODE_NONE      (0)

/* COLOR TUNRE SET */
#define ACFG_CLR_TUNER_OFFSET_MID_VALUE		(128)

#define ACFG_CUST_VIDEO_PQ_DFT_TBL_MAX_NUM      (512)
#define ACFG_CUST_VIDEO_PRO_PQ_DFT_TBL_MAX_NUM  (32)

#define ACFG_MTK_CLR_RGB_MAX_VALUE	100
#define ACFG_MTK_CLR_RGB_MIN_VALUE -100

/* color tuner MODULE*/
typedef enum
{
    CLR_TUNER_ROW_BRIGHTNESS = 0,
    CLR_TUNER_ROW_HUE,
    CLR_TUNER_ROW_SATURATION
}CLR_TUNER_MODULE_T;

/* color tuner COLOR*/
typedef enum
{
    CLR_TUNER_COL_MAGENTA = 0,
    CLR_TUNER_COL_RED,
    CLR_TUNER_COL_YELLOW,
    CLR_TUNER_COL_GREEN,
    CLR_TUNER_COL_CYAN,
    CLR_TUNER_COL_BLUE
}CLR_TUNER_COLOR_T;

typedef enum
{
    ACFG_CUST_INPUT_GRP_TV = 0,
    ACFG_CUST_INPUT_GRP_CVBS,
    ACFG_CUST_INPUT_GRP_COMPONENT,
    ACFG_CUST_INPUT_GRP_HDMI1,
    ACFG_CUST_INPUT_GRP_HDMI2,
    ACFG_CUST_INPUT_GRP_HDMI3,
    ACFG_CUST_INPUT_GRP_HDMI4,
    ACFG_CUST_INPUT_GRP_VGA,
    ACFG_CUST_INPUT_GRP_MMP,
    ACFG_CUST_INPUT_GRP_VTRL,
    ACFG_CUST_INPUT_GRP_MAX
}   ACFG_CUST_INPUT_GRP_T;

#ifdef NEVER
typedef enum
{
    ACFG_CUST_PIC_MODE_STANDARD = 0,
    ACFG_CUST_PIC_MODE_BRIGHT_ROOM,
    ACFG_CUST_PIC_MODE_DARK_ROOM,
    ACFG_CUST_PIC_MODE_RETAIL,
    ACFG_CUST_PIC_MODE_VIVID = ACFG_CUST_PIC_MODE_RETAIL,
    ACFG_CUST_PIC_MODE_GAME,
    ACFG_CUST_PIC_MODE_COMPUTER,
    ACFG_CUST_PIC_MODE_BASKETBALL,
    ACFG_CUST_PIC_MODE_BASEBALL,
    ACFG_CUST_PIC_MODE_CUSTOM,
    ACFG_CUST_PIC_MODE_LAST_ENTRY
}   ACFG_CUST_PIC_MODE_T;
#endif /* NEVER */

typedef enum
{
    ACFG_CUST_PIC_MODE_RETAIL = 0,
    ACFG_CUST_PIC_MODE_VIVID = ACFG_CUST_PIC_MODE_RETAIL,
    ACFG_CUST_PIC_MODE_BRIGHT,
    ACFG_CUST_PIC_MODE_BRIGHT_ROOM,  //Calibrated
    ACFG_CUST_PIC_MODE_DARK_ROOM, //Calibrated Dark
    ACFG_CUST_PIC_MODE_GAME,
    ACFG_CUST_PIC_MODE_SPORT,
    ACFG_CUST_PIC_MODE_CUSTOM,     //not used
    ACFG_CUST_PIC_MODE_STANDARD,   //not used
    ACFG_CUST_PIC_MODE_COMPUTER,  //not used
    ACFG_CUST_PIC_MODE_BASKETBALL, //not usd
    ACFG_CUST_PIC_MODE_BASEBALL,   //not used
    ACFG_CUST_PIC_MODE_LAST_ENTRY  //not used
}   ACFG_CUST_PIC_MODE_T;

typedef enum
{
    ACFG_CUST_VID_LUMA_OFF = 0,
    ACFG_CUST_VID_LUMA_LOW,
    ACFG_CUST_VID_LUMA_MEDIUM,
    ACFG_CUST_VID_LUMA_STRONG,
    ACFG_CUST_VID_LUMA_EXTEND,
    ACFG_CUST_VID_LUMA_LAST_ENTRY
}   ACFG_CUST_VID_LUMA_T;
typedef enum
{
    ACFG_CUST_VID_NR_OFF =0,
    ACFG_CUST_VID_NR_LOW ,
    ACFG_CUST_VID_NR_MEDIUM,
    ACFG_CUST_VID_NR_HIGH,
    ACFG_CUST_VID_NR_LAST_ENTRY
}   ACFG_CUST_VID_NR_T;
typedef enum
{
    ACFG_CUST_VID_3D_NR_OFF = 0,
    ACFG_CUST_VID_3D_NR_LOW,
    ACFG_CUST_VID_3D_NR_MEDIUM,
    ACFG_CUST_VID_3D_NR_HIGH,
    ACFG_CUST_VID_3D_NR_LAST_ENTRY
}   ACFG_CUST_VID_3D_NR_T;

typedef enum
{
    ACFG_CUST_VID_FLESH_TONE_OFF = 0,
    ACFG_CUST_VID_FLESH_TONE_NORMAL,
    ACFG_CUST_VID_FLESH_TONE_RICH_COLOR,
    ACFG_CUST_VID_FLESH_TONE_GRN_FLESH,
    ACFG_CUST_VID_FLESH_TONE_GRN_BLUE,
    ACFG_CUST_VID_FLESH_TONE_LAST_ENTRY
}   ACFG_CUST_VID_FLESH_TONE_T;
typedef enum
{
    ACFG_CUST_VID_FILM_MODE_OFF = 0,
    ACFG_CUST_VID_FILM_MODE_AUTO,
    ACFG_CUST_VID_FILM_MODE_LAST_ENTRY
}   ACFG_CUST_VID_FILM_MODE_T;

typedef enum
{
    ACFG_CUST_ADP_BACK_LIGHT_0 = 0,
    ACFG_CUST_ADP_BACK_LIGHT_1,
    ACFG_CUST_ADP_BACK_LIGHT_2,
    ACFG_CUST_ADP_BACK_LIGHT_3,
    ACFG_CUST_ADP_BACK_LIGHT_4,
    ACFG_CUST_ADP_BACK_LIGHT_5,
    ACFG_CUST_ADP_BACK_LIGHT_6,
    ACFG_CUST_ADP_BACK_LIGHT_7,
    ACFG_CUST_ADP_BACK_LIGHT_8,
    ACFG_CUST_ADP_BACK_LIGHT_9,
    ACFG_CUST_ADP_BACK_LIGHT_10,
    ACFG_CUST_ADP_BACK_LIGHT_11,
}   ACFG_CUST_ADP_BACK_LIGHT_T;

typedef enum
{
    ACFG_CUST_CLR_TEMP_WARM = 0,
    ACFG_CUST_CLR_TEMP_COOL,
    ACFG_CUST_CLR_TEMP_NORMAL,
    ACFG_CUST_CLR_TEMP_COMPUTER,
    ACFG_CUST_CLR_TEMP_CUSTOM,
} ACFG_CUST_CLR_TEMP_T;

typedef enum
{
	ACFG_CUST_CLEAR_ACTION_OFF = 0,
    ACFG_CUST_CLEAR_ACTION_ON
}ACFG_CUST_CLEAR_ACTION_T;

typedef enum
{
    ACFG_CUST_VID_EDGE_EN_OFF =0,
    ACFG_CUST_VID_EDGE_EN_LOW ,
    ACFG_CUST_VID_EDGE_EN_MEDIUM,
    ACFG_CUST_VID_EDGE_EN_HIGH,
    ACFG_CUST_VID_EDGE_EN_LAST_ENTRY
}   ACFG_CUST_VID_EDGE_EN_T;

/* Picture mode PQ table */
typedef struct _APP_CFG_CUST_PQ_TBL_T
{
    ACFG_CUST_PIC_MODE_T    e_pic_mode;      /* Picture mode */
    UINT16                  ui2_idx;         /* Acfg record idx */
    INT16                   i2_def;          /* Default value */
} APP_CFG_CUSTOM_PQ_TBL_T;

typedef struct _TIMING_HV_POS_MAP_T
{
    UINT8           ui1_idx;
    DEVICE_TYPE_T   e_video_type;
    UINT32          ui4_height;
    UINT8           ui1_internal_id; // input source number
}TIMING_HV_POS_MAP_T;

typedef enum
{
    ACFG_CUST_RGB_CONTENT_SDR = 1,
    ACFG_CUST_RGB_CONTENT_HDR_HLG,
    ACFG_CUST_RGB_CONTENT_DOLBY_VERSION,
    ACFG_CUST_RGB_CONTENT_MAX
}RGB_DYNAMIC_RANGE_T;

typedef enum
{
    ACFG_CUST_CONTENT_SDR = 0,
    ACFG_CUST_CONTENT_HDR,  // include hdr10 and hdr10plus
    ACFG_CUST_CONTENT_HLG,
    ACFG_CUST_CONTENT_DV,
    ACFG_CUST_CONTENT_MAX
}ACFG_CONTENT_RANGE_T;

typedef struct _ACFG_MI_MM_INFO_T
{
    UINT32 MI_U32_FramePerSec;
    UINT32 MI_U32_MovieWidth;
    UINT32 MI_U32_MovieHeight;
    MI_MM_VideoCodecType_e eVideoCodec;
    MI_MM_AudioCodecType_e eAudioCodec;

} ACFG_MI_MM_INFO_T;


extern BOOL b_3d_mode_playing;
/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_video_pre_init (VOID);

extern INT32 acfg_cust_video_post_init(VOID);
BOOL acfg_cust_video_is_special_item(UINT16          ui2_id);

extern INT32 acfg_cust_video_get_elem_idx(
                                UINT16          ui2_id,
                                UINT8           ui1_input_src,
                                UINT16*         pui2_idx
                                );

extern INT32 acfg_cust_video_get_predef_value(
                                UINT16          ui2_id,
                                UINT8           ui1_mode,
                                INT16*          pi2_val
                                );

extern INT32 acfg_cust_video_get_min_max(
                                UINT16          ui2_id,
                                INT16*          pi2_min,
                                INT16*          pi2_max
                                );

extern INT32 acfg_cust_video_incr(
                                UINT16          ui2_id,
                                INT16*          pi2_val
                                );

extern INT32  acfg_cust_video_decr(
                                UINT16          ui2_id,
                                INT16*          pi2_val
                                );

extern INT32 acfg_cust_video_get(
                                UINT16          ui2_id,
                                INT16*          pi2_val
                                );

extern INT32 acfg_cust_video_set(
                                UINT16          ui2_id,
                                INT16           i2_val
                                );

extern INT32 acfg_cust_video_update(
                                UINT16          ui2_id
                                );

extern INT32 acfg_cust_video_sync(
                                UINT16          ui2_id
                                );

extern INT32 acfg_cust_video_pos_reset(
                                UINT16          ui2_id
                                );

extern INT32 acfg_cust_video_get_overscan(CHAR * s_disp_name,
                                SCC_VID_OVER_SCAN_CLIPPER_T * pt_overscan);

extern INT32 acfg_cust_video_get_overscan_with_h_v_size(CHAR * s_disp_name,
                                SCC_VID_OVER_SCAN_CLIPPER_T * pt_overscan);
extern INT32 acfg_fac_rgb_value_mapping(INT16*   pi2_cfg_rec);
extern BOOL a_cfg_cust_video_is_sdr_hdr_444_content(VOID);

//=========================================================================================
/* from u_drv_cust.h
typedef enum
{
    DRV_CUSTOM_COLOR_FORMAT_RGB,
    DRV_CUSTOM_COLOR_FORMAT_YUV422,
    DRV_CUSTOM_COLOR_FORMAT_YUV444,
    DRV_CUSTOM_COLOR_FORMAT_YUV420
} DRV_CUSTOM_COLOR_FORMAT_T;
*/
typedef enum
{
    ACFG_CUST_HDMI_COLOR_RGB    = 0,
    ACFG_CUST_HDMI_COLOR_YUV422 = 1,
    ACFG_CUST_HDMI_COLOR_YUV444 = 2,
    ACFG_CUST_HDMI_COLOR_YUV420 = 3,
    ACFG_CUST_HDMI_COLOR_UNKNOWN= 4,
} ACFG_CUST_HDMI_COLOR_FORMAT_T;
ACFG_CUST_HDMI_COLOR_FORMAT_T acfg_cust_video_get_hdmi_color_space(void);
char* acfg_cust_video_get_hdmi_color_space_string(ACFG_CUST_HDMI_COLOR_FORMAT_T eAcfgCustHdmiColorFormat);

#if 1//(ENABLE_COLOR_444_TO_422_NEW_SPEC)
BOOL acfg_cust_Is_CurSrcHDMI(void);
extern BOOL acfg_cust_FullColor444_IfCanTurnOn(void);
BOOL acfg_cust_Is_CurHDMI_PQ_PCMode(void);

typedef enum
{
    ACFG_INPUT_RGB__FULL_COLOR_444_OFF,
    ACFG_INPUT_YUV444__FULL_COLOR_444_OFF,
    ACFG_INPUT_YUV422__FULL_COLOR_444_OFF,
    ACFG_INPUT_RGB__FULL_COLOR_444_ON,
    ACFG_INPUT_YUV444__FULL_COLOR_444_ON,
} EnuAcfgFullColor444Status;
EnuAcfgFullColor444Status acfg_cust_get_FullColor444_status(void);

#endif
//========================================================================================

extern INT32 acfg_cust_add_h_v_size_to_overscan(UINT16                                *pui2_up,      /* IN/OUT */
                                        UINT16                                  *pui2_down,    /* IN/OUT */
                                        UINT16                                  *pui2_left,    /* IN/OUT */
                                        UINT16                                  *pui2_right    /* IN/OUT */);
extern INT32 acfg_cust_add_h_v_position_to_overscan(UINT16                                *pui2_up,      /* IN/OUT */
                                        UINT16                                  *pui2_down,    /* IN/OUT */
                                        UINT16                                  *pui2_left,    /* IN/OUT */
                                        UINT16                                  *pui2_right    /* IN/OUT */);

INT32 acfg_cust_video_get_predef_value_by_idx(
    UINT16  ui2_rec_idx,
    UINT16  ui2_elem_idx,
    INT16*  pi2_val);
INT32 a_cfg_cust_copy_pic_mode_to_pic_mode(INT16 i2_from_pic,INT16 i2_to_pic);
INT32 acfg_cust_video_update_pq_def_from_odm(VOID);

extern INT32 a_cfg_mi_mm_querry(ACFG_MI_MM_INFO_T     *nav_mi_mm_info);
extern INT32 a_cfg_mi_mm_querry_ex(ACFG_MI_MM_INFO_T     *nav_mi_mm_info, BOOL *pb_interlace);

//=============================================================================================================

ACFG_CUST_INPUT_GRP_T acfg_cust_Get_CurInputGrp(void);

INT32 acfg_cust_video_get_DataOffset_By_Src_HdrType_PicMode( UINT8 u8SrcIdx, UINT8 u8DHR_type, UINT8 u8PicMode );

void acfg_cust_video_print_setting_data_u8_all(UINT8* pu8Data, UINT16 u16DataSize, BOOL bHDR, BOOL bCusPicMode );

//=============================================================================================================
INT32 acfg_cust_video_update_GLL_all(BOOL bUpdateLogo);
//=============================================================================================================



#endif /* _ACFG_CUST_VIDEO_H_ */
