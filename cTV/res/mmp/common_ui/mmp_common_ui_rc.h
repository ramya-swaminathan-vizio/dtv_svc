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
 * $RCSfile: mmp_common_ui_rc.h,v $
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

#ifndef _MMP_COMMON_UI_RC_H_
#define _MMP_COMMON_UI_RC_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_wgl_common.h"
#include "c_wgl.h"

#include "mmp/mmp_common.h"
#include "res/mmp/img/mmp_img.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MMP_COM_UI_DEFAULT_ALPHA            (255)

#define OPTION_LIST_LEFT                    (100*4/3)
#define OPTION_LIST_TOP                     (100*4/3)

/*-----------------------------------------------------------------------------
                    Info handler common ui
 ----------------------------------------------------------------------------*/
#define TM_INFO_UI_TITLE_X                 (40*4/3)
#define TM_INFO_UI_TITLE_Y                 (10*4/3)
#define TM_INFO_UI_TITLE_W                 (40*4/3)
#define TM_INFO_UI_TITLE_H                 (40*4/3)
#define TM_INFO_UI_TITLE_GRAP              (10*4/3)

#define TM_INFO_UI_VAL_X                   (TM_INFO_UI_TITLE_X + TM_INFO_UI_TITLE_W + TM_INFO_UI_TITLE_GRAP)
#define TM_INFO_UI_VAL_W                   (180*4/3)


#define LT_INFO_UI_TITLE_X                 (20*4/3)
#define LT_INFO_UI_TITLE_Y                 (20*4/3)
#define LT_INFO_UI_TITLE_W                 (80*4/3)
#define LT_INFO_UI_TITLE_H                 (30*4/3)
#define LT_INFO_UI_TITLE_GRAP              (4*4/3)

#define LT_INFO_UI_VAL_X                   (LT_INFO_UI_TITLE_X + LT_INFO_UI_TITLE_W + 8)
#define LT_INFO_UI_VAL_W                   (160*4/3)

/*-----------------------------------------------------------------------------
                    Common icon
 ----------------------------------------------------------------------------*/
#define ICON_W                              (46*4/3)
#define ICON_Y                              (0*4/3)
#define MMP_COM_UI_RC_ICON_STYLE            (WGL_STL_GL_NO_BK)


/*-----------------------------------------------------------------------------
                    Common text
 ----------------------------------------------------------------------------*/
#define MMP_COM_UI_RC_TEXT_STYLE            (WGL_STL_GL_NO_BK | WGL_STL_TEXT_SMART_CUT | WGL_STL_TEXT_MAX_512)

/*-----------------------------------------------------------------------------
                    toolbar
 ----------------------------------------------------------------------------*/
#define FRM_TOOLBAR_X                       (0)
#define FRM_TOOLBAR_Y                       (350*4/3/*674*/)
#define FRM_TOOLBAR_W                       (960*4/3/*1280*/)
#define FRM_TOOLBAR_H                       (190*4/3/*46*/)

#define ICON_REDICON_X                      (550*4/3)
#define ICON_REDICON_Y                      (ICON_Y)
#define ICON_REDICON_W                      (ICON_W)
#define ICON_REDICON_H                      (ICON_W)

#define TXT_REDHINT_X                       (ICON_REDICON_X+ICON_W+10*4/3)
#define TXT_REDHINT_Y                       (10*4/3)
#define TXT_REDHINT_W                       (150*4/3)
#define TXT_REDHINT_H                       (30*4/3)

#define ICON_GREENICON_X                    (710*4/3)
#define ICON_GREENICON_Y                    (ICON_Y)
#define ICON_GREENICON_W                    (ICON_W)
#define ICON_GREENICON_H                    (ICON_W)

#define TXT_GREENHINT_X                     (ICON_GREENICON_X+ICON_W+10*4/3)
#define TXT_GREENHINT_Y                     (10*4/3)
#define TXT_GREENHINT_W                     (150*4/3)
#define TXT_GREENHINT_H                     (30*4/3)

#define ICON_YELLOWICON_X                   (890*4/3)
#define ICON_YELLOWICON_Y                   (ICON_Y)
#define ICON_YELLOWICON_W                   (ICON_W)
#define ICON_YELLOWICON_H                   (ICON_W)

#define TXT_YELLOWHINT_X                    (ICON_YELLOWICON_X+ICON_W+10*4/3)
#define TXT_YELLOWHINT_Y                    (10*4/3)
#define TXT_YELLOWHINT_W                    (150*4/3)
#define TXT_YELLOWHINT_H                    (30*4/3)

#define ICON_BLUEICON_X                     (800*4/3/*1040*/)
#define ICON_BLUEICON_Y                     (ICON_Y)
#define ICON_BLUEICON_W                     (ICON_W)
#define ICON_BLUEICON_H                     (ICON_W)

#define TXT_BLUEHINT_X                      (ICON_BLUEICON_X+ICON_W+10*4/3)
#define TXT_BLUEHINT_Y                      (10*4/3)
#define TXT_BLUEHINT_W                      (150*4/3)
#define TXT_BLUEHINT_H                      (30*4/3)

#define MMP_COM_UI_RC_TOOLBAR_ELEM_COUNT    ((UINT32) 4)
#define MMP_COM_UI_RC_TOOLBAR_STYLE         (0)

typedef enum _MMP_COM_UI_RC_TB_HINT_ID_T
{
    MMP_COM_UI_RC_TB_HINT_ID_0 = 0,
    MMP_COM_UI_RC_TB_HINT_ID_1,
    MMP_COM_UI_RC_TB_HINT_ID_2,
    MMP_COM_UI_RC_TB_HINT_ID_3,
} MMP_COM_UI_RC_TB_HINT_ID_T;

#define MMP_COM_UI_RC_GET_TOOLBAR_HINTS_RECT()                                                                              \
{                                                                                                                           \
    {TXT_REDHINT_X, TXT_REDHINT_Y, TXT_REDHINT_X + TXT_REDHINT_W, TXT_REDHINT_Y + TXT_REDHINT_H},                           \
    {TXT_GREENHINT_X, TXT_GREENHINT_Y, TXT_GREENHINT_X + TXT_GREENHINT_W, TXT_GREENHINT_Y + TXT_GREENHINT_H},               \
    {TXT_YELLOWHINT_X, TXT_YELLOWHINT_Y, TXT_YELLOWHINT_X + TXT_YELLOWHINT_W, TXT_YELLOWHINT_Y + TXT_YELLOWHINT_H},         \
    {TXT_BLUEHINT_X, TXT_BLUEHINT_Y, TXT_BLUEHINT_X + TXT_BLUEHINT_W, TXT_BLUEHINT_Y + TXT_BLUEHINT_H}                      \
}

#define MMP_COM_UI_RC_GET_TOOLBAR_ICONS_RECT()                                                                              \
{                                                                                                                           \
    {ICON_REDICON_X, ICON_REDICON_Y, ICON_REDICON_X + ICON_REDICON_W, ICON_REDICON_Y + ICON_REDICON_H},                     \
    {ICON_GREENICON_X, ICON_GREENICON_Y, ICON_GREENICON_X + ICON_GREENICON_W, ICON_GREENICON_Y + ICON_GREENICON_H},         \
    {ICON_YELLOWICON_X, ICON_YELLOWICON_Y, ICON_YELLOWICON_X + ICON_YELLOWICON_W, ICON_YELLOWICON_Y + ICON_YELLOWICON_H},   \
    {ICON_BLUEICON_X, ICON_BLUEICON_Y, ICON_BLUEICON_X + ICON_BLUEICON_W, ICON_BLUEICON_Y + ICON_BLUEICON_H}                \
}

#define MMP_COM_UI_RC_GET_ICON_IMAGE_ID()                       \
{                                                               \
    MMP_IMG_IMAGE_ID_RED_ICON,                                  \
    MMP_IMG_IMAGE_ID_GREEN_ICON,                                \
    MMP_IMG_IMAGE_ID_YELLOW_ICON,                               \
    MMP_IMG_IMAGE_ID_BLUE_ICON                                  \
}

#define MMP_COM_UI_RC_GET_TOOLBAR_FCT_ICON_IMAGE_ID()           \
{                                                               \
    MMP_IMG_IMAGE_ID_PREV_ICON,                                 \
    MMP_IMG_IMAGE_ID_PAUSE_ICON,                                \
    MMP_IMG_IMAGE_ID_STOP_ICON,                                 \
    MMP_IMG_IMAGE_ID_NEXT_ICON,                                 \
    MMP_IMG_IMAGE_ID_VOL_ICON                                  \
}

#define MMP_COM_UI_RC_GET_TOOLBAR_HINT_FONT()                   \
{                                                               \
    FE_FNT_SIZE_SMALL,                                          \
    FE_FNT_STYLE_REGULAR,                                       \
    FE_CMAP_ENC_UNICODE,                                        \
    SN_FONT_DEFAULT,                                            \
    0                                                           \
}

#ifdef APP_COLOR_MODE_PALLET
    #define MMP_COM_UI_RC_GET_TOOLBAR_HINT_COLOR()                  \
    {                                                               \
        255, {   0 }, {   0 }, { MMP_CLR_IDX_GET_GARY() }           \
    }
#else
    #define MMP_COM_UI_RC_GET_TOOLBAR_HINT_COLOR()                  \
    {                                                               \
        255, {   204 }, {   204 }, { 204 }                          \
    }
#endif

/*-----------------------------------------------------------------------------
                    status bar
 ----------------------------------------------------------------------------*/
#define STATUS_FRM_X                        (0)
#define STATUS_FRM_Y                        (0)
#define STATUS_FRM_W                        (960*4/3/*1280*/)
#define STATUS_FRM_H                        (72*4/3)

#define TXT_Y                               (25*4/3)
#if 0
#define TXT_H                               (35)
#else /*For CR 139522 text cut issue*/
#define TXT_H                               (40*4/3)
#endif

#if 1
#define PB_PLAYBACK_X                       (452*4/3)
#define PB_PLAYBACK_Y                       (35*4/3)
#define PB_PLAYBACK_W                       (391*4/3)
#define PB_PLAYBACK_H                       (13*4/3)

#define TXT_PB_POSITION_X                   (850*4/3)
#define TXT_PB_POSITION_Y                   TXT_Y
#define TXT_PB_POSITION_W                   (220*4/3)
#define TXT_PB_POSITION_H                   TXT_H
#endif
#define ICON_STATUS_X                       (78*4/3)
#define ICON_STATUS_Y                       (0)
#define ICON_STATUS_W                       (40*4/3)
#define ICON_STATUS_H                       (72*4/3)

#define MMP_COM_UI_RC_STATUSBAR_MAX_ICON    (10)
#define MMP_COM_UI_RC_STATUSBAR_MAX_TXT     (10)

#define MMP_COM_UI_RC_TOOLBAR_MAX_ICON    (10)
#define MMP_COM_UI_RC_TOOLBAR_MAX_TXT     (10)

#define MMP_COM_UI_RC_GET_STATUSBAR_LABEL_FONT()                \
{                                                               \
    FE_FNT_SIZE_SMALL,                                          \
    FE_FNT_STYLE_REGULAR,                                       \
    FE_CMAP_ENC_UNICODE,                                        \
    SN_FONT_DEFAULT,                                            \
    0                                                           \
}

#ifdef APP_COLOR_MODE_PALLET
    #define MMP_COM_UI_RC_GET_STATUS_LABEL_COLOR()              \
    {                                                           \
        255, {   0 }, {   0 }, { MMP_CLR_IDX_GET_WHITE() }      \
    }
#else
    #define MMP_COM_UI_RC_GET_STATUS_LABEL_COLOR()              \
    {                                                           \
        255, {   253 }, {   253 }, { 253 }                      \
    }
#endif

#define MMP_COM_UI_RC_STATUSBAR_STYLE       (0)
/*-----------------------------------------------------------------------------
                    detail page
 ----------------------------------------------------------------------------*/

#define FRM_DETAIL_X                        (794*4/3)
#define FRM_DETAIL_Y                        (233*4/3)
#if 0
#define FRM_DETAIL_W                        (424)
#else
#define FRM_DETAIL_W                        (450*4/3)
#endif
#define FRM_DETAIL_H                        (442*4/3)

#define MMP_COM_UI_RC_GET_DETAILPGAE_TEXT_FONT()                \
{                                                               \
    FE_FNT_SIZE_SMALL,                                          \
    FE_FNT_STYLE_REGULAR,                                       \
    FE_CMAP_ENC_UNICODE,                                        \
    SN_FONT_DEFAULT,                                            \
    0                                                           \
}

#ifdef APP_COLOR_MODE_PALLET
    #define MMP_COM_UI_RC_GET_DETAILPGAE_TEXT_COLOR()           \
    {                                                           \
        255, {   0 }, {   0 }, { MMP_CLR_IDX_GET_WHITE() }      \
    }
#else
    #define MMP_COM_UI_RC_GET_DETAILPGAE_TEXT_COLOR()           \
    {                                                           \
        255, {   253 }, {   253 }, { 253 }                      \
    }
#endif

#define MMP_COM_UI_RC_DETAILPAGE_STYLE  (0)

#define MMP_COM_UI_RC_SBAR_TXT_STYLE  (WGL_STL_GL_NO_IMG_UI |WGL_STL_TEXT_SMART_CUT|WGL_STL_TEXT_MAX_32)
/*-----------------------------------------------------------------------------
                    nfybox
 ----------------------------------------------------------------------------*/
#define MMP_COM_UI_RC_NFY_TEXT_STYLE        (WGL_STL_TEXT_MAX_128)
#define MMP_COM_UI_RC_NFY_TEXT_ALIGN        (WGL_AS_LEFT_CENTER)

#define MMP_COM_UI_RC_NFY_X                 (210*4/3)
#define MMP_COM_UI_RC_NFY_Y                 (60*4/3)
#define MMP_COM_UI_RC_NFY_W                 (915*4/3)
#define MMP_COM_UI_RC_NFY_H                 (63*4/3)

#define MMP_COM_UI_RC_NFY_INSET_LEFT        (23*4/3)
#define MMP_COM_UI_RC_NFY_INSET_TOP         (0)
#define MMP_COM_UI_RC_NFY_INSET_RIGHT       (23*4/3)
#define MMP_COM_UI_RC_NFY_INSET_BOTTOM      (0)

#define MMP_COM_UI_RC_NFY_GET_TEXT_FONT()                       \
{                                                               \
    FE_FNT_SIZE_MEDIUM,                                          \
    FE_FNT_STYLE_REGULAR,                                       \
    FE_CMAP_ENC_UNICODE,                                        \
    SN_FONT_DEFAULT,                                            \
    0                                                           \
}

#ifdef APP_COLOR_MODE_PALLET
    #define MMP_COM_UI_RC_NFY_GET_TEXT_COLOR()                      \
    {                                                               \
        255, {   0 }, {   0 }, { MMP_CLR_IDX_GET_WHITE() }          \
    }
#else
    #define MMP_COM_UI_RC_NFY_GET_TEXT_COLOR()                      \
    {                                                               \
        255, {  253}, {  253}, { 253 }                              \
    }
#endif

/*-----------------------------------------------------------------------------
                    running box
 ----------------------------------------------------------------------------*/
#define  MMP_COM_UI_RC_RB_DUR               (1000)     /* 2 seconds  */


/*-----------------------------------------------------------------------------
                    Player Main frame
 ----------------------------------------------------------------------------*/

#define MMP_COM_UI_MAIN_X                    (0)
#define MMP_COM_UI_MAIN_Y                    (0)
#define MMP_COM_UI_MAIN_W                    (FRM_TOOLBAR_W)
#define MMP_COM_UI_MAIN_H                    (FRM_TOOLBAR_Y + FRM_TOOLBAR_H)

#ifdef APP_COLOR_MODE_PALLET
#define MMP_COM_UI_GET_CLR_BK() { 255, { 0 }, { 0 }, { MMP_CLR_IDX_GET_BLUE() }}
#else
#define MMP_COM_UI_GET_CLR_BK() { 255, { 17 }, {92 }, { 156 }}
#endif


/*-----------------------------------------------------------------------------
                    Time set box
 ----------------------------------------------------------------------------*/

#ifdef APP_COLOR_MODE_PALLET
    #define MMP_COM_UI_TIME_BOX_GET_TEXT_COLOR()                      \
    {                                                               \
        255, {   0 }, {   0 }, { MMP_CLR_IDX_GET_WHITE() }          \
    }
#else
    #define MMP_COM_UI_TIME_BOX_GET_TEXT_COLOR()                      \
    {                                                               \
        255, {  253}, {  253}, { 253 }                              \
    }
#endif


#ifdef APP_COLOR_MODE_PALLET
#define MMP_COM_UI_TIME_BOX_GET_CLR_BK() { 255, { 0 }, { 0 }, { MMP_CLR_IDX_GET_ORANGE() }}
#else
#define MMP_COM_UI_TIME_BOX_GET_CLR_BK() { 255, { 255 }, {0}, { 0 }}
#endif


#endif /*_MMP_COMMON_UI_H_*/
