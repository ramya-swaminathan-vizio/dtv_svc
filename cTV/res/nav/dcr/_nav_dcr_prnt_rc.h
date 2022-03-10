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
 * $RCSfile: _nav_dcr_prnt_rc.h,v $
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
 
#ifndef __NAV_DCR_PRNT_RC_H_
#define __NAV_DCR_PRNT_RC_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_wgl_common.h"
#include "u_wgl_text.h"
#include "res/nav/nav_view.h"
#include "res/nav/dcr/nav_dcr_mlm.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*language*/
#define _NAV_DCR_CTRL_639_GET(_idx, _ps_lang)                                         \
{                                                                                     \
    switch(_idx)                                                                      \
    {                                                                                 \
    case 4:                                                                           \
        (_ps_lang) = "esl";                                                           \
        break;                                                                        \
    case 3:                                                                           \
        (_ps_lang) = "fra";                                                           \
        break;                                                                        \
    case 2:                                                                           \
        (_ps_lang) = "spa";                                                           \
        break;                                                                        \
    case 1:                                                                           \
        (_ps_lang) = "fre";                                                           \
        break;                                                                        \
    case 0:                                                                           \
    default:                                                                          \
        (_ps_lang) = "eng";                                                           \
        break;                                                                        \
    }                                                                                 \
}

#define _NAV_DCR_CTRL_LANG_ID_GET(_idx, _id)                                          \
{                                                                                     \
    switch(_idx)                                                                      \
    {                                                                                 \
    case 4:                                                                           \
        (_id) = MLM_NAV_DCR_LANG_SPA;                                                 \
        break;                                                                        \
    case 3:                                                                           \
        (_id) = MLM_NAV_DCR_LANG_FRE;                                                 \
        break;                                                                        \
    case 2:                                                                           \
        (_id) = MLM_NAV_DCR_LANG_SPA;                                                 \
        break;                                                                        \
    case 1:                                                                           \
        (_id) = MLM_NAV_DCR_LANG_FRE;                                                 \
        break;                                                                        \
    case 0:                                                                           \
    default:                                                                          \
        (_id) = MLM_NAV_DCR_LANG_ENG;                                                 \
        break;                                                                        \
    }                                                                                 \
}
    
#define _NAV_DCR_CTRL_LANG_DEFAULT_ID_GET()             (MLM_NAV_DCR_LANG_ENG)
#define _NAV_DCR_CTRL_LANG_MAX_IDX_GET()                (5)
#define _NAV_DCR_CTRL_LANG_COUNT_GET()                  (MLM_NAV_DCR_NUM_LANG)

/*Widget*/
typedef enum _NAV_DCR_PRNT_WGT_ID_T
{
    NAV_DCR_PRNT_WGT_ID_FRAME           = 0,
    NAV_DCR_PRNT_WGT_ID_TITLE           = 1,
    NAV_DCR_PRNT_WGT_ID_DESC            = 2,
    NAV_DCR_PRNT_WGT_ID_PROGRESS        = 3,
    NAV_DCR_PRNT_WGT_ID_CHILD_COUNT     = 3,
    NAV_DCR_PRNT_WGT_ID_TOTAL_COUNT     = 4
} NAV_DCR_PRNT_WGT_ID_T;

#define NAV_DCR_PRNT_GET_ROOT_FRAME(_pt_wgt_set)            ((_pt_wgt_set)->ah_wgt[NAV_DCR_PRNT_WGT_ID_FRAME])
#define NAV_DCR_PRNT_GET_TITLE(_pt_wgt_set)                 ((_pt_wgt_set)->ah_wgt[NAV_DCR_PRNT_WGT_ID_TITLE])
#define NAV_DCR_PRNT_GET_DESC(_pt_wgt_set)                  ((_pt_wgt_set)->ah_wgt[NAV_DCR_PRNT_WGT_ID_DESC])
#define NAV_DCR_PRNT_GET_PROGRESS(_pt_wgt_set)              ((_pt_wgt_set)->ah_wgt[NAV_DCR_PRNT_WGT_ID_PROGRESS])

/*UI layout*/
#define NAV_DCR_OFFSET_X                ((UINT32)12)
#define NAV_DCR_OFFSET_Y                ((UINT32)4)

#define NAV_DCR_TITLE_X                 NAV_DCR_OFFSET_X
#define NAV_DCR_TITLE_Y                 NAV_DCR_OFFSET_Y
#define NAV_DCR_TITLE_W                 (((UINT32)PROG_TITLE_WIDTH) * 2 / 3)
#define NAV_DCR_TITLE_H                 ((UINT32)PROG_TITLE_HEIGHT)
#define NAV_DCR_TITLE_STYLE             (WGL_STL_GL_NO_BK)
#define NAV_DCR_TITLE_FG_COLOR          (APP_COLOR_ITEM_TEXT_HLT)
#define NAV_DCR_TITLE_FG_ALPHA          (DEFAULT_FG_ALPHA)
#define NAV_DCR_TITLE_ALIGN             WGL_AS_CENTER_CENTER
#define NAV_DCR_TITLE_FONT_INFO         {FE_FNT_SIZE_LARGE,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL}

#define NAV_DCR_DESC_X                  NAV_DCR_TITLE_X
#define NAV_DCR_DESC_Y                  (NAV_DCR_TITLE_X + NAV_DCR_TITLE_H + NAV_DCR_OFFSET_Y)
#define NAV_DCR_DESC_W                  NAV_DCR_TITLE_W
#define NAV_DCR_DESC_H                  ((UINT32)PROG_DETAIL_HEIGHT * 2)
#define NAV_DCR_DESC_STYLE              (WGL_STL_GL_NO_BK |                     \
                                         WGL_STL_TEXT_MULTILINE |               \
                                         WGL_STL_TEXT_SMART_CUT |               \
                                         WGL_STL_TEXT_MAX_512 |                 \
                                         WGL_STL_TEXT_MAX_DIS_10_LINE)
#define NAV_DCR_DESC_FG_COLOR           (APP_COLOR_ITEM_TEXT)
#define NAV_DCR_DESC_FG_ALPHA           (DEFAULT_FG_ALPHA)
#define NAV_DCR_DESC_ALIGN              WGL_AS_LEFT_TOP
#define NAV_DCR_DESC_FONT_INFO          {FE_FNT_SIZE_SMALL,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL}

#define NAV_DCR_PG_X                    NAV_DCR_DESC_X
#define NAV_DCR_PG_Y                    (NAV_DCR_DESC_Y + NAV_DCR_DESC_H + NAV_DCR_OFFSET_Y)
#define NAV_DCR_PG_W                    NAV_DCR_DESC_W
#define NAV_DCR_PG_H                    PROG_ATTR_RATING_HEIGHT
#define NAV_DCR_PG_STYLE                (WGL_STL_GL_NO_BK | WGL_STL_GL_NO_IMG_UI | WGL_STL_PG_POINT)
#define NAV_DCR_PG_BK_COLOR             (APP_COLOR_ITEM_CONTENT)
#define NAV_DCR_PG_BK_ALPHA             (LST_BOX_ELM_BK_ALPHA)
#define NAV_DCR_PG_BODY_COLOR           (APP_COLOR_ITEM_TEXT)
#define NAV_DCR_PG_BAR_COLOR            (APP_COLOR_ITEM_TEXT_HLT)
#define NAV_DCR_PG_FG_ALPHA             (DEFAULT_FG_ALPHA)

#define NAV_DCR_FRAME_Y                 (BANNER_FRAME_TOP + BANNER_FRAME_HEIGHT + NAV_DCR_OFFSET_Y + NAV_DCR_OFFSET_X)
#define NAV_DCR_FRAME_W                 (NAV_DCR_DESC_W + 2 * NAV_DCR_OFFSET_X)
#define NAV_DCR_FRAME_H                 (NAV_DCR_PG_Y + NAV_DCR_PG_H + NAV_DCR_OFFSET_Y)
#define NAV_DCR_FRAME_X                 ((DISPLAY_WIDTH - NAV_DCR_FRAME_W) / 2)
#define NAV_DCR_FRAME_STYLE             (WGL_STL_GL_NO_IMG_UI)
#define NAV_DCR_FRAME_BK_COLOR          (APP_COLOR_ITEM_MAIN)
#define NAV_DCR_FRAME_BK_ALPHA          (DEFAULT_BK_ALPHA)

#define NAV_DCR_FRAME_CARD_STATE_Y      NAV_DCR_FRAME_Y
#define NAV_DCR_FRAME_CARD_STATE_W      (NAV_DCR_TITLE_W + 2 * NAV_DCR_OFFSET_X)
#define NAV_DCR_FRAME_CARD_STATE_H      (NAV_DCR_TITLE_Y + NAV_DCR_TITLE_H + NAV_DCR_OFFSET_Y)
#define NAV_DCR_FRAME_CARD_STATE_X      ((DISPLAY_WIDTH - NAV_DCR_FRAME_CARD_STATE_W) / 2)

#define NAV_DCR_FRAME_ERROR_STATE_Y      NAV_DCR_FRAME_Y
#define NAV_DCR_FRAME_ERROR_STATE_W      (NAV_DCR_TITLE_W + 2 * NAV_DCR_OFFSET_X)
#define NAV_DCR_FRAME_ERROR_STATE_H      (NAV_DCR_DESC_Y + NAV_DCR_DESC_H + NAV_DCR_OFFSET_Y )
#define NAV_DCR_FRAME_ERROR_STATE_X      ((DISPLAY_WIDTH - NAV_DCR_FRAME_ERROR_STATE_W) / 2)

#define NAV_DCR_FRAME_UPGRADE_STATE_Y   NAV_DCR_FRAME_Y
#define NAV_DCR_FRAME_UPGRADE_STATE_W   (NAV_DCR_TITLE_W + 2 * NAV_DCR_OFFSET_X)
#define NAV_DCR_FRAME_UPGRADE_STATE_H   NAV_DCR_FRAME_CARD_STATE_H
#define NAV_DCR_FRAME_UPGRADE_STATE_X   ((DISPLAY_WIDTH - NAV_DCR_FRAME_UPGRADE_STATE_W) / 2)

/*behavior*/
/*timer duration*/
#define NAV_DCR_AUTOHIDE_UPGRADING      ((UINT32)0)                         /*ms. not to hide the upgrade message*/
#define NAV_DCR_AUTOHIDE_NON_UPGRADING  ((UINT32)3000)                      /*ms*/
#define NAV_DCR_AUTOHIDE_CP_ERROR       ((UINT32)10000)                     /*ms*/
#define NAV_DCR_AUTOHIDE_THRESHOLD      ((UINT32)200)                       /*tick. 200 tick ~= 1000ms*/
#define NAV_DCR_UPGRADING_REFRESH_DUR   ((UINT32)400)                       /*ms*/
#define NAV_DCR_PG_POS_MIN              ((INT16)0)
#define NAV_DCR_PG_POS_MAX              ((INT16)10)
#define NAV_DCR_PG_POS_STEP             ((INT16)1)
/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/
/*widget instances for dcr-presentation*/
typedef struct _NAV_DCR_PRNT_WGT_INST_T
{
   HANDLE_T             ah_wgt[NAV_DCR_PRNT_WGT_ID_TOTAL_COUNT];
} NAV_DCR_PRNT_WGT_INST_T;

/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif
