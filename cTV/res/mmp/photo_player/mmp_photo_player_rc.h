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
 * $RCSfile: mmp_photo_player_rc.h,v $
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
 
#ifndef _MMP_PHOTO_PLAYER_RC_H_
#define _MMP_PHOTO_PLAYER_RC_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_img_tfx.h"

#include "mmp/mmp_common.h"
#include "mmp/photo_eng/mmp_photo_eng.h"
#include MMP_MLM_HEADER_FILE
#include "res/mmp/common_ui/mmp_common_ui_rc.h"
#include "res/mmp/img/mmp_img.h"

/*-----------------------------------------------------------------------------
                    resource
 ----------------------------------------------------------------------------*/
#ifdef APP_MMP_TWO_PHOTO_BUF
    #define MMP_PP_RC_IS_QUICK_ROTATE()     (FALSE)
#else
    #define MMP_PP_RC_IS_QUICK_ROTATE()     (TRUE)
#endif
#define MMP_PP_RC_IS_NO_THUMB_FROM_MAIN()   (FALSE)
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/* Info handler*/
#define MMP_PP_INFO_HDLR_THUMB_ITEM_NUM      (5)
#define MMP_PP_INFO_HDLR_LST_ITEM_NUM        (5) 
#define MMP_PP_INFO_HDLR_ITEM_MAX_NUM        (MMP_PP_INFO_HDLR_THUMB_ITEM_NUM > MMP_PP_INFO_HDLR_LST_ITEM_NUM ? MMP_PP_INFO_HDLR_THUMB_ITEM_NUM : MMP_PP_INFO_HDLR_LST_ITEM_NUM)

#define MMP_PP_LIST_INFO_HDR_NAME            (0)
#define MMP_PP_LIST_INFO_HDR_DATE            (1)
#define MMP_PP_LIST_INFO_HDR_TIME            (2)
#define MMP_PP_LIST_INFO_HDR_SIZE            (3)
#define MMP_PP_LIST_INFO_HDR_TYPE            (4)
#define MMP_PP_LIST_INFO_HDR_PROTECT         (5)

#define MMP_PP_LIST_INFO_HDR_ICON_W          (40)
#define MMP_PP_LIST_INFO_HDR_ICON_H          (20)

/**/
#define MMP_PP_RC_TEXT_STYLE            (WGL_STL_GL_NO_BK | WGL_STL_TEXT_SMART_CUT | WGL_STL_TEXT_MAX_128)

#define MMP_PP_RC_STR_MAX_LEN               ((UINT32) MMP_RC_PATH_MAX_LEN)

#define MMP_PP_RC_MAIN_X                    (0)
#define MMP_PP_RC_MAIN_Y                    (0)
#define MMP_PP_RC_MAIN_W                    (1920)//(FRM_TOOLBAR_W)
#define MMP_PP_RC_MAIN_H                    (1080)//(FRM_TOOLBAR_Y + FRM_TOOLBAR_H)

#define MMP_PP_RC_LBL_X                     (22)
#define MMP_PP_RC_LBL_W                     (250)
#define MMP_PP_RC_LBL_H                     (40)
#define MMP_PP_RC_LBL_Y                     (20)
#define MMP_PP_RC_VAL_X                     (292)
#define MMP_PP_RC_VAL_W                     (420)

#define MMP_PP_RC_TOOLBAR_ELEM_COUNT        (2)

#if 0
#define MMP_PP_RC_LBL_NAME_X                MMP_PP_RC_LBL_X
#define MMP_PP_RC_LBL_NAME_Y                (20)
#define MMP_PP_RC_LBL_NAME_W                MMP_PP_RC_LBL_W
#define MMP_PP_RC_LBL_NAME_H                MMP_PP_RC_LBL_H

#define MMP_PP_RC_VAL_NAME_X                MMP_PP_RC_VAL_X
#define MMP_PP_RC_VAL_NAME_Y                (20)
#define MMP_PP_RC_VAL_NAME_W                MMP_PP_RC_VAL_W
#define MMP_PP_RC_VAL_NAME_H                MMP_PP_RC_LBL_H

#define MMP_PP_RC_LBL_ARTIST_X                MMP_PP_RC_LBL_X
#define MMP_PP_RC_LBL_ARTIST_Y                (20 + MMP_PP_RC_LBL_H)
#define MMP_PP_RC_LBL_ARTIST_W                MMP_PP_RC_LBL_W
#define MMP_PP_RC_LBL_ARTIST_H                MMP_PP_RC_LBL_H

#define MMP_PP_RC_VAL_ARTIST_X                MMP_PP_RC_VAL_X
#define MMP_PP_RC_VAL_ARTIST_Y                (20 + MMP_PP_RC_LBL_H)
#define MMP_PP_RC_VAL_ARTIST_W                MMP_PP_RC_VAL_W
#define MMP_PP_RC_VAL_ARTIST_H                MMP_PP_RC_LBL_H

#define MMP_PP_RC_LBL_ALBM_X                MMP_PP_RC_LBL_X
#define MMP_PP_RC_LBL_ALBM_Y                (20 + 2*MMP_PP_RC_LBL_H)
#define MMP_PP_RC_LBL_ALBM_W                MMP_PP_RC_LBL_W
#define MMP_PP_RC_LBL_ALBM_H                MMP_PP_RC_LBL_H

#define MMP_PP_RC_VAL_ALBM_X                MMP_PP_RC_VAL_X
#define MMP_PP_RC_VAL_ALBM_Y                (20 + 2*MMP_PP_RC_LBL_H)
#define MMP_PP_RC_VAL_ALBM_W                MMP_PP_RC_VAL_W
#define MMP_PP_RC_VAL_ALBM_H                MMP_PP_RC_LBL_H

#define MMP_PP_RC_LBL_DATE_X                MMP_PP_RC_LBL_X
#define MMP_PP_RC_LBL_DATE_Y                (20 + 3 * MMP_PP_RC_LBL_H)
#define MMP_PP_RC_LBL_DATE_W                MMP_PP_RC_LBL_W
#define MMP_PP_RC_LBL_DATE_H                MMP_PP_RC_LBL_H

#define MMP_PP_RC_VAL_DATE_X                MMP_PP_RC_VAL_X
#define MMP_PP_RC_VAL_DATE_Y                (20 + 3 * MMP_PP_RC_LBL_H)
#define MMP_PP_RC_VAL_DATE_W                MMP_PP_RC_VAL_W
#define MMP_PP_RC_VAL_DATE_H                MMP_PP_RC_LBL_H

#define MMP_PP_RC_LBL_SIZE_X                MMP_PP_RC_LBL_X
#define MMP_PP_RC_LBL_SIZE_Y                (20 + 4 * MMP_PP_RC_LBL_H)
#define MMP_PP_RC_LBL_SIZE_W                MMP_PP_RC_LBL_W
#define MMP_PP_RC_LBL_SIZE_H                MMP_PP_RC_LBL_H

#define MMP_PP_RC_VAL_SIZE_X                MMP_PP_RC_VAL_X
#define MMP_PP_RC_VAL_SIZE_Y                (20 + 4 * MMP_PP_RC_LBL_H)
#define MMP_PP_RC_VAL_SIZE_W                MMP_PP_RC_VAL_W
#define MMP_PP_RC_VAL_SIZE_H                MMP_PP_RC_LBL_H

#define MMP_PP_RC_LBL_NEXT_X                MMP_PP_RC_LBL_X
#define MMP_PP_RC_LBL_NEXT_Y                (20 + 5 * MMP_PP_RC_LBL_H)
#define MMP_PP_RC_LBL_NEXT_W                MMP_PP_RC_LBL_W
#define MMP_PP_RC_LBL_NEXT_H                MMP_PP_RC_LBL_H

#define MMP_PP_RC_VAL_NEXT_X                MMP_PP_RC_VAL_X
#define MMP_PP_RC_VAL_NEXT_Y                (20 + 5 * MMP_PP_RC_LBL_H)
#define MMP_PP_RC_VAL_NEXT_W                MMP_PP_RC_VAL_W
#define MMP_PP_RC_VAL_NEXT_H                MMP_PP_RC_LBL_H
#endif

#define TXT_PP_SB_0_X                       (126)
#define TXT_PP_SB_1_X                       (304)
#define TXT_PP_SB_2_X                       (435)
#define TXT_PP_SB_3_X                       (540)
#define TXT_PP_SB_Y                         (27)
#define TXT_PP_SB_H                         (40)
#define TXT_PP_SB_S_VAL_W                   (80)
#define TXT_PP_SB_L_VAL_W                   (400)

#define ICON_PP_Y                           (0)
#define ICON_PP_W                           (46)
#define ICON_PP_H                           (46)

#define ICON_PP_REDICON_X                   (239)
#define ICON_PP_REDICON_Y                   (ICON_PP_Y)
#define ICON_PP_REDICON_W                   (ICON_PP_W)
#define ICON_PP_REDICON_H                   (ICON_PP_H)

#define TXT_PP_REDHINT_X                       (ICON_PP_REDICON_X+ICON_PP_W+12)
#define TXT_PP_REDHINT_Y                       (10)
#define TXT_PP_REDHINT_W                       (150)
#define TXT_PP_REDHINT_H                       (30)

#define ICON_PP_GREENICON_X                 (459)
#define ICON_PP_GREENICON_Y                 (ICON_PP_Y)
#define ICON_PP_GREENICON_W                 (ICON_PP_W)
#define ICON_PP_GREENICON_H                 (ICON_PP_H)

#define TXT_PP_GREENHINT_X                     (ICON_PP_GREENICON_X+ICON_PP_W+12)
#define TXT_PP_GREENHINT_Y                     (10)
#define TXT_PP_GREENHINT_W                     (150)
#define TXT_PP_GREENHINT_H                     (30)

#define ICON_PP_YELLOWICON_X                (689)
#define ICON_PP_YELLOWICON_Y                (ICON_PP_Y)
#define ICON_PP_YELLOWICON_W                (ICON_PP_W)
#define ICON_PP_YELLOWICON_H                (ICON_PP_H)

#define TXT_PP_YELLOWHINT_X                    (ICON_PP_YELLOWICON_X+ICON_PP_W+12)
#define TXT_PP_YELLOWHINT_Y                    (10)
#define TXT_PP_YELLOWHINT_W                    (150)
#define TXT_PP_YELLOWHINT_H                    (30)

#define ICON_PP_BLUEICON_X                  (869)
#define ICON_PP_BLUEICON_Y                  (ICON_PP_Y)
#define ICON_PP_BLUEICON_W                  (ICON_PP_W)
#define ICON_PP_BLUEICON_H                  (ICON_PP_H)

#define FRM_PP_DETAIL_X                        (681)//(454)
#define FRM_PP_DETAIL_Y                        (319)//(213)
#define FRM_PP_DETAIL_W                        (1146)//(764)
#define FRM_PP_DETAIL_H                        (693)//(462)

/* read only icon*/
#define READ_ONLY_ICON_X                       (960)
#define READ_ONLY_ICON_Y                       (30)
#define READ_ONLY_ICON_W                       (24)
#define READ_ONLY_ICON_H                       (24)

/* skip icon*/
#define MMP_PP_SKIP_ICON_X                  (840)//(560)
#define MMP_PP_SKIP_ICON_Y                  (0)
#define MMP_PP_SKIP_ICON_W                  (80)//(53)
#define MMP_PP_SKIP_ICON_H                  (80)

/*play icon*/
#define MMP_PP_PLAY_ICON_X                  (120)//(80)
#define MMP_PP_PLAY_ICON_Y                  (0)
#define MMP_PP_PLAY_ICON_W                  (72)//(48)
#define MMP_PP_PLAY_ICON_H                  (72)//(48)

/*pause  icon*/
#define MMP_PP_PLAY_ICON_X                  (120)//(80)
#define MMP_PP_PLAY_ICON_Y                  (0)
#define MMP_PP_PLAY_ICON_W                  (72)//(48)
#define MMP_PP_PLAY_ICON_H                  (72)//(48)

/*file title*/
#define MMP_PP_INFO_BAR_STATUS_TXT_X			((INT32) 165)//((INT32) 110)
#define MMP_PP_INFO_BAR_STATUS_TXT_Y			((INT32) 195)//((INT32) 130)
#define MMP_PP_INFO_BAR_STATUS_TXT_W			((INT32) 525)//((INT32) 350)
#define MMP_PP_INFO_BAR_STATUS_TXT_H			((INT32) 150)//((INT32)100)
#define MMP_PP_INFO_BAR_STATUS_TXT_STYLE		(WGL_STL_GL_NO_BK | WGL_STL_TEXT_MULTILINE | WGL_STL_TEXT_MAX_512)
#define MMP_PP_INFO_BAR_STATUS_FONT_NAME		SN_FONT_DEFAULT
#define MMP_PP_INFO_BAR_STATUS_FONT_SIZE		FE_FNT_SIZE_SMALL
#define MMP_PP_INFO_BAR_STATUS_FONT_STYLE		FE_FNT_STYLE_REGULAR
#define MMP_PP_INFO_BAR_STATUS_TXT_INSET_LEFT	((INT32)0)
#define MMP_PP_INFO_BAR_STATUS_TXT_INSET_RIGHT	((INT32)0)
#define MMP_PP_INFO_BAR_STATUS_TXT_INSET_TOP	((INT32)18)//((INT32)12)
#define MMP_PP_INFO_BAR_STATUS_TXT_INSET_BOTTOM	((INT32)18)//((INT32)12)
#define MMP_PP_INFO_BAR_STATUS_TXT_ALIGN		(WGL_AS_LEFT_TOP)
#define MMP_PP_INFO_BAR_STATUS_TXT_LINE_GAP     ((INT32) 4)
#define MMP_PP_INFO_BAR_STATUS_FONT_STYLE       FE_FNT_STYLE_REGULAR
#define MMP_PP_INFO_BAR_STATUS_FONT_NAME        SN_FONT_DEFAULT


#define MMP_PP_RC_GET_TOOLBAR_ICONS_RECT()                                                                              \
{                                                                                                                           \
    {ICON_PP_REDICON_X, ICON_PP_REDICON_Y, ICON_PP_REDICON_X + ICON_PP_REDICON_W, ICON_PP_REDICON_Y + ICON_PP_REDICON_H},                     \
    {ICON_PP_GREENICON_X, ICON_PP_GREENICON_Y, ICON_PP_GREENICON_X + ICON_PP_GREENICON_W, ICON_PP_GREENICON_Y + ICON_PP_GREENICON_H},         \
    {ICON_PP_YELLOWICON_X, ICON_PP_YELLOWICON_Y, ICON_PP_YELLOWICON_X + ICON_PP_YELLOWICON_W, ICON_PP_YELLOWICON_Y + ICON_PP_YELLOWICON_H},   \
    {ICON_PP_BLUEICON_X, ICON_PP_BLUEICON_Y, ICON_PP_BLUEICON_X + ICON_PP_BLUEICON_W, ICON_PP_BLUEICON_Y + ICON_PP_BLUEICON_H}                \
}

#define MMP_PP_RC_GET_TOOLBAR_HINTS_RECT()                                                                              \
{                                                                                                                           \
    {TXT_PP_GREENHINT_X, TXT_PP_GREENHINT_Y, TXT_PP_GREENHINT_X + TXT_PP_GREENHINT_W, TXT_PP_GREENHINT_Y + TXT_PP_GREENHINT_H},               \
    {TXT_PP_YELLOWHINT_X, TXT_PP_YELLOWHINT_Y, TXT_PP_YELLOWHINT_X + TXT_PP_YELLOWHINT_W, TXT_PP_YELLOWHINT_Y + TXT_PP_YELLOWHINT_H}         \
}

/* Text label in status bar */
typedef enum _MMP_PP_RC_SB_LBL_ID_T
{
    MMP_PP_RC_SB_LBL_ID_FILE_IDX = 0,
    MMP_PP_RC_SB_LBL_ID_TFX,    
    MMP_PP_RC_SB_LBL_ID_DUR,
    MMP_PP_RC_SB_LBL_ID_FILE_NAME,
    MMP_PP_RC_SB_LBL_ID_ZOOM,
    MMP_PP_RC_STATUSBAR_LABEL_COUNT
} MMP_PP_RC_SB_LBL_ID_T;

#define MMP_PP_RC_GET_STATUSBAR_LABEL_RECT()                                                                        \
{                                                                                                                       \
    {TXT_PP_SB_0_X, TXT_PP_SB_Y, TXT_PP_SB_0_X + TXT_PP_SB_L_VAL_W, TXT_PP_SB_Y + TXT_PP_SB_H},     \
    {TXT_PP_SB_1_X, TXT_PP_SB_Y, TXT_PP_SB_1_X + TXT_PP_SB_L_VAL_W, TXT_PP_SB_Y + TXT_PP_SB_H},     \
    {TXT_PP_SB_2_X, TXT_PP_SB_Y, TXT_PP_SB_2_X + TXT_PP_SB_L_VAL_W, TXT_PP_SB_Y + TXT_PP_SB_H},     \
    {TXT_PP_SB_3_X, TXT_PP_SB_Y, TXT_PP_SB_3_X + TXT_PP_SB_L_VAL_W, TXT_PP_SB_Y + TXT_PP_SB_H},     \
    {TXT_PP_SB_1_X, TXT_PP_SB_Y, TXT_PP_SB_1_X + TXT_PP_SB_S_VAL_W, TXT_PP_SB_Y + TXT_PP_SB_H}      \
}

#ifdef APP_COLOR_MODE_PALLET
    #define MMP_PP_RC_GET_STATUSBAR_LABEL_COLOR()               \
    {                                                           \
        255, {   0 }, {   0 }, { MMP_CLR_IDX_GET_WHITE() }      \
    }
#else
    #define MMP_PP_RC_GET_STATUSBAR_LABEL_COLOR()               \
    {                                                           \
        255, {   253 }, {   253 }, { 253 }                      \
    }
#endif

#define MMMP_PP_RC_GET_STATUSBAR_LABEL_FONT()                   \
{                                                               \
    FE_FNT_SIZE_SMALL,                                          \
    FE_FNT_STYLE_REGULAR,                                       \
    FE_CMAP_ENC_UNICODE,                                        \
    SN_FONT_DEFAULT,                                            \
    0                                                           \
}

#ifdef APP_COLOR_MODE_PALLET
    #define MMP_PP_RC_GET_TOOLBAR_HINT_COLOR()                  \
    {                                                           \
        255, {   0 }, {  0 }, { MMP_CLR_IDX_GET_WHITE() }       \
    }
#else
    #define MMP_PP_RC_GET_TOOLBAR_HINT_COLOR()                  \
    {                                                           \
        255, {   253 }, {  253 }, { 253 }                       \
    }
#endif

#define MMP_PP_RC_GET_TOOLBAR_HINT_FONT()                       \
{                                                               \
    FE_FNT_SIZE_SMALL,                                          \
    FE_FNT_STYLE_REGULAR,                                       \
    FE_CMAP_ENC_UNICODE,                                        \
    SN_FONT_DEFAULT,                                            \
    0                                                           \
}

#ifdef MMP_GUI_AUTHORING_DP 
typedef enum __MMP_PP_INFO_DATA_TYPE_T
{
    _MMP_PP_INFO_DATA_TYPE_CHAR = 0,
    _MMP_PP_INFO_DATA_TYPE_GL_SIZE,
    _MMP_PP_INFO_DATA_TYPE_DTG,
    _MMP_PP_INFO_DATA_TYPE_ROTATION,
    _MMP_PP_INFO_DATA_TYPE_EXPOSURE_TIME,
    _MMP_PP_INFO_DATA_TYPE_F_NUMBER,
    _MMP_PP_INFO_DATA_TYPE_FILENAME,
    _MMP_PP_INFO_DATA_TYPE_EXPOSURE_PROGRAM,
    _MMP_PP_INFO_DATA_TYPE_COLOR_SPACE,
    _MMP_PP_INFO_DATE_TYPE_RESOLUTION,
    _MMP_PP_INFO_DATE_TYPE_ISO,
    _MMP_PP_IFNO_DATA_TYPE_FLASH,
    _MMP_PP_INFO_DATA_TYPE_FILE_SIZE,
    _MMP_PP_INFO_DATA_TYPE_BIAS,
    _MMP_PP_INFO_DATA_TYPE_PATH,
    _MMP_PP_INFO_DATA_TYPE_CUR_OF_TOAL,
    _MMP_PP_IFNO_DATA_TYPE_CAMERA
} _MMP_PP_INFO_DATA_TYPE_T;

#define _MMP_PP_RC_DP_GET_CONFIG()      {                                                                                         \
    { MLM_MMP_KEY_DP_ALBUM,                             MMP_FP_INFO_TYPE_ALBUM,             _MMP_PP_INFO_DATA_TYPE_CHAR             },        \
    { MLM_MMP_KEY_DP_DT,                                MMP_FP_INFO_TYPE_LAST_WRITE_TIME,       _MMP_PP_INFO_DATA_TYPE_DTG              },        \
    { MLM_MMP_KEY_DP_NM,                                MMP_FP_INFO_TYPE_TITLE,             _MMP_PP_INFO_DATA_TYPE_CHAR             },        \
    { MLM_MMP_KEY_BUTX_PHOTO_CAMERA,                   MMP_FP_IFNO_TYPE_CAMERA,          _MMP_PP_IFNO_DATA_TYPE_CAMERA         },        \
    { MLM_MMP_KEY_THU_MODE_FILE_INFO_RESOLUTION,      MMP_FP_INFO_TYPE_RESOLUTION,        _MMP_PP_INFO_DATA_TYPE_GL_SIZE           },        \
    { MLM_MMP_KEY_DP_SZ,                                 MMP_FP_INFO_TYPE_SIZE,            _MMP_PP_INFO_DATA_TYPE_FILE_SIZE             },        \
    { MLM_MMP_KEY_BUTX_PHOTO_SPEED,                  MMP_FP_INFO_TYPE_F_NUMBER,           _MMP_PP_INFO_DATA_TYPE_F_NUMBER             },        \
    { MLM_MMP_KEY_BUTX_PHOTO_ISO,                      MP_FP_INFO_TYPE_ISO_SENSITIVITY,    _MMP_PP_INFO_DATE_TYPE_ISO    },        \
    { MLM_MMP_KEY_BUTX_PHOTO_FLASH,                   MP_FP_INFO_TYPE_FLASH_MODE,          _MMP_PP_IFNO_DATA_TYPE_FLASH         },        \
    { MLM_MMP_KEY_BUTX_PHOTO_EXPOSURE_PRO,              MMP_FP_INFO_TYPE_EXPOSURE_PROGRAM,  _MMP_PP_INFO_DATA_TYPE_EXPOSURE_PROGRAM },        \
    { MLM_MMP_KEY_BUTX_PHOTO_BAIS,                MP_FP_INFO_TYPE_EXPOSURE_BIAS,            _MMP_PP_INFO_DATA_TYPE_BIAS      }         \
}


typedef struct _MMP_PP_DP_CONFIG_T
{
    UINT32                      ui4_mlm_idx;
    MMP_FP_INFO_TYPE_T          e_type;
    _MMP_PP_INFO_DATA_TYPE_T    e_data_type;
    UINT8*                      pui1_buf;
} MMP_PP_DP_CONFIG_T;

#else

/*detail page*/
typedef enum _MMP_PP_RC_DP_LBL_ID_T
{
    MMP_PP_RC_DP_LBL_ID_LABEL_ALBM  = 0,
    MMP_PP_RC_DP_LBL_ID_VALUE_ALBM,
    MMP_PP_RC_DP_LBL_ID_LABEL_DATE,
    MMP_PP_RC_DP_LBL_ID_VALUE_DATE,
    MMP_PP_RC_DP_LBL_ID_LABEL_NAME,
    MMP_PP_RC_DP_LBL_ID_VALUE_NAME,
    MMP_PP_RC_DP_LBL_ID_LABEL_CAMERA,
    MMP_PP_RC_DP_LBL_ID_VALUE_CAMERA,
    MMP_PP_RC_DP_LBL_ID_LABEL_RESOLUTION,
    MMP_PP_RC_DP_LBL_ID_VALUE_RESOLUTION,
    MMP_PP_RC_DP_LBL_ID_LABEL_FILE_SIZE,
    MMP_PP_RC_DP_LBL_ID_VALUE_FILE_SIZE,
    MMP_PP_RC_DP_LBL_ID_LABEL_SPEED,
    MMP_PP_RC_DP_LBL_ID_VALUE_SPEED,
    MMP_PP_RC_DP_LBL_ID_LABEL_ISO,
    MMP_PP_RC_DP_LBL_ID_VALUE_ISO,
    MMP_PP_RC_DP_LBL_ID_LABEL_FLASH,
    MMP_PP_RC_DP_LBL_ID_VALUE_FLASH,
    MMP_PP_RC_DP_LBL_ID_LABEL_EXPOSURE_PROGRAM,
    MMP_PP_RC_DP_LBL_ID_VALUE_EXPOSURE_PROGRAM,
    MMP_PP_RC_DP_LBL_ID_LABEL_BIAS,
    MMP_PP_RC_DP_LBL_ID_VALUE_BIAS,
    MMP_PP_RC_DP_LBL_COUNT,
    MMP_PP_RC_DP_LBL_LAST_ENTRT
} MMP_PP_RC_DP_LBL_ID_T;

#define MMP_PP_RC_DP_LBL_GET_SETTING(_e_id, _t_rect, _pws_str)                                                                          \
{                                                                                                                                       \
    switch(_e_id)                                                                                                                       \
    {                                                                                                                                   \
    case MMP_PP_RC_DP_LBL_ID_LABEL_NAME:                                                                                                \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_LBL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_LABEL_NAME/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_LBL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = MLM_MMP_TEXT(MLM_MMP_LANG_ENG, MLM_MMP_KEY_DP_NM);                                                                 \
        break;            \
    case MMP_PP_RC_DP_LBL_ID_VALUE_NAME:                                                                                                \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_VAL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_VALUE_NAME/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_VAL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = NULL;                                                                                                              \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_LABEL_CAMERA:                                                                                              \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_LBL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_LABEL_CAMERA/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_LBL_W, MMP_PP_RC_LBL_H);   \
        (_pws_str) = MLM_MMP_TEXT(MLM_MMP_LANG_ENG, MLM_MMP_KEY_SB_ARTIST);                                                             \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_VALUE_CAMERA:                                                                                              \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_VAL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_VALUE_CAMERA/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_VAL_W, MMP_PP_RC_LBL_H);   \
        (_pws_str) = NULL;                                                                                                              \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_LABEL_ALBM:                                                                                                \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_LBL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_LABEL_ALBM/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_LBL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = MLM_MMP_TEXT(MLM_MMP_LANG_ENG, MLM_MMP_KEY_DP_ALBUM);                                                              \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_VALUE_ALBM:                                                                                                \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_VAL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_VALUE_ALBM/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_VAL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = NULL;                                                                                                              \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_LABEL_DATE:                                                                                                \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_LBL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_LABEL_DATE/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_LBL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = MLM_MMP_TEXT(MLM_MMP_LANG_ENG, MLM_MMP_KEY_DP_DT);                                                                 \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_VALUE_DATE:                                                                                                \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_VAL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_VALUE_DATE/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_VAL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = NULL;                                                                                                              \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_LABEL_RESOLUTION:                                                                                                \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_LBL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_LABEL_RESOLUTION/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_LBL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = MLM_MMP_TEXT(MLM_MMP_LANG_ENG, MLM_MMP_KEY_DP_SZ);                                                                 \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_VALUE_RESOLUTION:                                                                                                \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_VAL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_VALUE_RESOLUTION/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_VAL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = NULL;                                                                                                              \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_LABEL_FILE_SIZE:                                                                                                \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_LBL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_LABEL_FILE_SIZE/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_LBL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = MLM_MMP_TEXT(MLM_MMP_LANG_ENG, MLM_MMP_KEY_DP_NEXT);                                                               \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_VALUE_FILE_SIZE:                                                                                                \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_VAL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_VALUE_FILE_SIZE/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_VAL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = NULL;                                                                                                              \
        break;                                                      \
    case MMP_PP_RC_DP_LBL_ID_LABEL_SPEED:                                        \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_LBL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_LABEL_SPEED/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_LBL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = MLM_MMP_TEXT(MLM_MMP_LANG_ENG, MLM_MMP_KEY_BUTX_PHOTO_ORIENT);\
    break;                                                                      \
    case MMP_PP_RC_DP_LBL_ID_VALUE_SPEED:                                    \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_VAL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_VALUE_SPEED/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_VAL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = NULL;                                                          \
        break;                        \
    case MMP_PP_RC_DP_LBL_ID_LABEL_ISO:                               \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_LBL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_LABEL_ISO/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_LBL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = MLM_MMP_TEXT(MLM_MMP_LANG_ENG, MLM_MMP_KEY_BUTX_PHOTO_EXPOSURE_TIME);          \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_VALUE_ISO:                               \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_VAL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_VALUE_ISO/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_VAL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = NULL;                                                          \
        break;                                                                                                                         \
    case MMP_PP_RC_DP_LBL_ID_LABEL_FLASH:                                        \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_LBL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_LABEL_FLASH/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_LBL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = MLM_MMP_TEXT(MLM_MMP_LANG_ENG, MLM_MMP_KEY_BUTX_PHOTO_F_NUMBER);               \
        break;                                                                                                                         \
    case MMP_PP_RC_DP_LBL_ID_VALUE_FLASH:                                    \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_VAL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_VALUE_FLASH/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_VAL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = NULL;                                                          \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_LABEL_EXPOSURE_PROGRAM:                            \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_LBL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_LABEL_EXPOSURE_PROGRAM/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_LBL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = MLM_MMP_TEXT(MLM_MMP_LANG_ENG, MLM_MMP_KEY_BUTX_PHOTO_EXPOSURE_PRO);   \
        break;                                                                                                                         \
    case MMP_PP_RC_DP_LBL_ID_VALUE_EXPOSURE_PROGRAM:                            \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_VAL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_VALUE_EXPOSURE_PROGRAM/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_VAL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = NULL;                                                          \
        break;                                                                                                                         \
    case MMP_PP_RC_DP_LBL_ID_LABEL_BIAS:                                 \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_LBL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_LABEL_BIAS/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_LBL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = MLM_MMP_TEXT(MLM_MMP_LANG_ENG, MLM_MMP_KEY_BUTX_PHOTO_COLOR_SPACE);            \
        break;                                                                                                                          \
    case MMP_PP_RC_DP_LBL_ID_VALUE_BIAS:                                 \
        SET_RECT_BY_SIZE(&(_t_rect), MMP_PP_RC_VAL_X, MMP_PP_RC_LBL_Y + (MMP_PP_RC_DP_LBL_ID_VALUE_BIAS/2) * MMP_PP_RC_LBL_H, MMP_PP_RC_VAL_W, MMP_PP_RC_LBL_H);           \
        (_pws_str) = NULL;                                                          \
        break;                                                                      \
    default:                                                                                                                            \
        MMP_ASSERT(0);                                                                                                                  \
        break;                                                                                                                          \
    }                                                                                                                                   \
}
#endif

/*-----String Format for Resoultion-----*/
#define MMP_PP_RC_RES_FMT                   "%6d X %-6d"   /*6 + 6 + 1(:) + 1('\0') = 14, Cannot over MMP_PP_RC_STR_MAX_LEN*/
#define MMP_PP_RC_DATE_FMT                  "%d/%d/%d"   /*4 + 5 * 2 + 4(:) + 1(space) + 1('\0') = 20, Cannot over MMP_PP_RC_STR_MAX_LEN*/
#define MMP_PP_RC_FILEIDX_FMT               "%d of %d"   /* 3+1('/')+3+1('\0') = 8, Cannot over MMP_PP_RC_STR_MAX_LEN */
#define MMP_PP_RC_EXPOSURE_FMT              "%d/%d"  /*6 + 6 + 1(/) + 1(")+ 1('\0') = 15, Cannot over MMP_PP_RC_STR_MAX_LEN*/
#define MMP_PP_RC_F_NUM_FMT                 "%6d.%dF"   /*6 + 6 + 1(.) + 1(F)+ 1('\0') = 15, Cannot over MMP_PP_RC_STR_MAX_LEN*/
#define MMP_PP_RC_FILE_SIZE_FMT             "%d.%d KB"
#define MMP_PP_RC_ISO_FMT                   "%d"
#define MMP_PP_RC_FIEL_NAME_FMT             "\\%s %s"
/*-----Key definition-----*/
#define MMP_PP_RC_KEY_DETAIL                BTN_PRG_INFO
#define MMP_PP_RC_KEY_TFX                   BTN_YELLOW
#define MMP_PP_RC_KEY_ROTATE                BTN_GREEN
#define MMP_PP_RC_KEY_TIME                  BTN_GREEN
#define MMP_PP_RC_KEY_ZOOM                  BTN_YELLOW
#define MMP_PP_RC_KEY_PLAY                  BTN_SELECT
#define MMP_PP_RC_KEY_PAUSE                 BTN_SELECT
#define MMP_PP_RC_KEY_NEXT                  BTN_CURSOR_RIGHT
#define MMP_PP_RC_KEY_PREV                  BTN_CURSOR_LEFT
#define MMP_PP_RC_KEY_BROWSE                BTN_EXIT
#define MMP_PP_RC_KEY_OPTION                BTN_MENU
#define MMP_PP_RC_KEY_CAPTURE               BTN_RECORD
#define MMP_PP_RC_KEY_REPEAT                BTN_REPEAT
#define MMP_PP_RC_KEY_OK                    BTN_SELECT
#define MMP_PP_RC_KEY_BACK					BTN_RETURN
#define MMP_PP_RC_KEY_PHO_PLAY				BTN_PLAY
#define MMP_PP_RC_KEY_PHO_PAUSE				BTN_PAUSE
#define MMP_PP_RC_KEY_PHO_STOP				BTN_STOP
#define MMP_PP_RC_KEY_PLAY_NEXT				BTN_FF
#define MMP_PP_RC_KEY_PLAY_PREV				BTN_FR  



/*-----Transition Effect ListBox-----*/
#define MMP_PP_RC_TLB_LEFT                  (FRM_TOOLBAR_X + ICON_GREENICON_X)
#define MMP_PP_RC_TLB_BOTTOM                (FRM_TOOLBAR_Y)
#define MMP_PP_RC_TLB_GET_RET_PNT(_t_ref_pnt)                   \
{                                                               \
    (_t_ref_pnt).b_is_left_bottom = TRUE;                       \
    (_t_ref_pnt).t_origin.i4_x = MMP_PP_RC_TLB_LEFT;            \
    (_t_ref_pnt).t_origin.i4_y = MMP_PP_RC_TLB_BOTTOM;          \
}

#define MMP_PP_RC_TLB_NONE_MODE             ((UINT32)0)
#define MMP_PP_RC_TLB_ELEM_COUNT            ((UINT32)9)
#define MMP_PP_RC_TLB_GET_ELEM_DESC(_at_desc, _ui4_key)                             \
{                                                                                   \
    (_at_desc)[0] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_TLB_NONE);                 \
    (_at_desc)[1] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_TLB_DISSOLVE);             \
    (_at_desc)[2] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_TLB_WP_R);                 \
    (_at_desc)[3] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_TLB_WP_L);                 \
    (_at_desc)[4] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_TLB_WP_U);                 \
    (_at_desc)[5] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_TLB_WP_D);                 \
    (_at_desc)[6] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_TLB_BX_IN);                \
    (_at_desc)[7] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_TLB_BX_OUT);               \
    (_at_desc)[8] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_TLB_RANDOM);                \
}

#define MMP_PP_RC_TLB_GET_EFFECT(_ui4_idx, _e_effect)           \
{                                                               \
    switch(_ui4_idx)                                            \
    {                                                           \
    case 1:                                                     \
        (_e_effect) = TFX_DISSOLVE;                             \
        break;                                                  \
    case 2:                                                     \
        (_e_effect) = TFX_WIPE_RIGHT;                           \
        break;                                                  \
    case 3:                                                     \
        (_e_effect) = TFX_WIPE_LEFT;                            \
        break;                                                  \
    case 4:                                                     \
        (_e_effect) = TFX_WIPE_UP;                              \
        break;                                                  \
    case 5:                                                     \
        (_e_effect) = TFX_WIPE_DOWN;                            \
        break;                                                  \
    case 6:                                                     \
        (_e_effect) = TFX_BOX_IN;                               \
        break;                                                  \
    case 7:                                                     \
        (_e_effect) = TFX_BOX_OUT;                              \
        break;                                                  \
    case 0:                                                     \
    default:                                                    \
        (_e_effect) = TFX_TOTAL_NUMBER;                         \
    }                                                           \
}

/*-----Duration ListBox-----*/
#define MMP_PP_RC_DLB_LEFT                  (FRM_TOOLBAR_X + ICON_YELLOWICON_X)
#define MMP_PP_RC_DLB_BOTTOM                (FRM_TOOLBAR_Y)
#define MMP_PP_RC_DLB_GET_RET_PNT(_t_ref_pnt)                   \
{                                                               \
    (_t_ref_pnt).b_is_left_bottom = TRUE;                       \
    (_t_ref_pnt).t_origin.i4_x = MMP_PP_RC_DLB_LEFT;            \
    (_t_ref_pnt).t_origin.i4_y = MMP_PP_RC_DLB_BOTTOM;          \
}

#define MMP_PP_RC_DLB_ELEM_COUNT            ((UINT32)3)
#define MMP_PP_RC_DLB_GET_ELEM_DESC(_at_desc, _ui4_key)                             \
{                                                                                   \
    (_at_desc)[0] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_DLB_S);                    \
    (_at_desc)[1] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_DLB_M);                    \
    (_at_desc)[2] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_DLB_L);                    \
}

#define MMP_PP_RC_DLB_GET_DUR(_ui4_idx, _ui4_dur) /*ms*/        \
{                                                               \
    switch(_ui4_idx)                                            \
    {                                                           \
    case 1:                                                     \
        (_ui4_dur) = 10000;                                     \
        break;                                                  \
    case 2:                                                     \
        (_ui4_dur) = 15000;                                     \
        break;                                                  \
    case 0:                                                     \
    default:                                                    \
        (_ui4_dur) = 5000;                                      \
    }                                                           \
}

/*-----Zoom ListBox-----*/
#define MMP_PP_RC_ZLB_LEFT                  (FRM_TOOLBAR_X + ICON_YELLOWICON_X)
#define MMP_PP_RC_ZLB_BOTTOM                (FRM_TOOLBAR_Y)
#define MMP_PP_RC_ZLB_GET_RET_PNT(_t_ref_pnt)                   \
{                                                               \
    (_t_ref_pnt).b_is_left_bottom = TRUE;                       \
    (_t_ref_pnt).t_origin.i4_x = MMP_PP_RC_ZLB_LEFT;            \
    (_t_ref_pnt).t_origin.i4_y = MMP_PP_RC_ZLB_BOTTOM;          \
}

#define MMP_PP_RC_ZLB_ELEM_COUNT            ((UINT32)3)
#define MMP_PP_RC_ZLB_GET_ELEM_DESC(_at_desc, _ui4_key)                             \
{                                                                                   \
    (_at_desc)[0] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_ZLB_1);                    \
    (_at_desc)[1] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_ZLB_2);                    \
    (_at_desc)[2] = MLM_MMP_TEXT((_ui4_key), MLM_MMP_KEY_ZLB_4);                    \
}

#define MMP_PP_RC_ZLB_GET_ZOOM(_ui4_idx, _ui4_zoom)             \
{                                                               \
    switch(_ui4_idx)                                            \
    {                                                           \
    case 1:                                                     \
        (_ui4_zoom) = (UINT32)2 * MMP_PE_ZOOM_CONST;                    \
        break;                                                  \
    case 2:                                                     \
        (_ui4_zoom) = (UINT32)4 * MMP_PE_ZOOM_CONST;                    \
        break;                                                  \
    case 0:                                                     \
    default:                                                    \
        (_ui4_zoom) = (UINT32)MMP_PE_ZOOM_CONST;                        \
    }                                                           \
}

#define MMP_PP_RC_ZLB_ZOOM_2_IDX(_ui4_zoom, _ui4_idx)           \
{                                                               \
    switch(_ui4_zoom)                                           \
    {                                                           \
    case (2 * MMP_PE_ZOOM_CONST):                               \
        (_ui4_idx) = 1;                                         \
        break;                                                  \
    case (4 * MMP_PE_ZOOM_CONST):                               \
        (_ui4_idx) = 2;                                         \
        break;                                                  \
    case MMP_PE_ZOOM_CONST:                                     \
    default:                                                    \
        (_ui4_idx) = 0;                                         \
        break;                                                  \
    }                                                           \
}

/*-----Autohide Timer-----*/
#define MMP_PP_RC_AUTOHIDE_DUR              ((UINT32) 10000)

/*-----Running Box-----*/
#define MMP_PP_RC_RB_X                      ((UINT32) 600)
#define MMP_PP_RC_RB_Y                      ((UINT32) 27)

/*-----Repeat mode-----*/
#define MMP_PP_RC_RP_LB_ELEM_COUNT            ((UINT32)3)

/*-----Shuffle mode-----*/
#define MMP_PP_RC_SF_LB_ELEM_COUNT            ((UINT32)2)

/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/

#endif /*_MMP_PHOTO_PLAYER_RC_H_*/

