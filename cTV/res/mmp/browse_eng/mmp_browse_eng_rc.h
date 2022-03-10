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
 * $RCSfile: mmp_file_browser_rc.h,v $
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
 
#ifndef _MMP_BROWSE_ENG_RC_H_
#define _MMP_BROWSE_ENG_RC_H_

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define MMP_BE_RC_INIT_STATUS MMP_BE_STATUS_CHOOSE_FF

typedef enum
{
    MMP_BE_FILTER_IDX_PHOTO = 0,
    MMP_BE_FILTER_IDX_AUDIO,
#ifdef MMP_FB_RC_IS_ENABLE_VIDEO_FILTER
    MMP_BE_FILTER_IDX_VIDEO,
#endif
#ifdef MMP_FB_RC_IS_ENABLE_TEXT_FILTER
    MMP_BE_FILTER_IDX_TEXT,
#endif
    MMP_BE_FILTER_IDX_CNT
} MMP_BE_FILTER_IDX_T;

#define MMP_BE_RC_GET_FILTER_IDX_BY_TYPE(_e_media_type, _e_idx)                   \
{                                                                                 \
    (_e_idx) = mmp_be_rc_get_filter_idx_by_type(_e_media_type);                   \
}

#define MMP_BE_RC_GET_FILTER_TYPE_BY_IDX(_e_idx, _e_media_type)                   \
{                                                                                 \
    (_e_media_type) = mmp_be_rc_get_filter_type_by_idx(_e_idx);                   \
}

#define MMP_BE_RC_GET_FILTER_MLM_IDX(_e_idx, _ui4_mlm)                            \
{                                                                                 \
    (_ui4_mlm) = mmp_be_rc_get_filter_mlm_idx(_e_idx);                            \
}

/*-----Key definition-----*/
#define FILE_BROWSER_BTN_CURSOR_UP     BTN_CURSOR_UP
#define FILE_BROWSER_BTN_CURSOR_DOWN   BTN_CURSOR_DOWN
#define FILE_BROWSER_BTN_CURSOR_LEFT   BTN_CURSOR_LEFT
#define FILE_BROWSER_BTN_CURSOR_RIGHT  BTN_CURSOR_RIGHT
#define FILE_BROWSER_BTN_PAGE_UP       BTN_PRG_UP
#define FILE_BROWSER_BTN_PAGE_DOWN     BTN_PRG_DOWN
#define FILE_BROWSER_BTN_SELECT        BTN_SELECT
#define FILE_BROWSER_BTN_VOL_UP        BTN_VOL_UP
#define FILE_BROWSER_BTN_VOL_DOWN      BTN_VOL_DOWN
#define FILE_BROWSER_BTN_MUTE          BTN_MUTE
#define FILE_BROWSER_BTN_MARK          BTN_ADD_ERASE

#define BTN_SORT_PHOTO        BTN_DIGIT_1
#define BTN_SORT_AUDIO        BTN_DIGIT_2
#define BTN_SORT_VIDEO        BTN_DIGIT_3
#define BTN_SORT_TEXT         BTN_DIGIT_5

#define MMP_BE_TREE_TEXT_MAX_LENG          (34)
#define MMP_BE_TREE_TEXT_MAX_NODE_LENG     (24)

#ifdef MMP_GUI_AUTHORING
#define MMP_BE_THUMBNAIL_FRM_BORDER_INSET  (2*4/3)
#else
//#define MMP_BE_THUMBNAIL_FRM_BORDER_INSET  (5)
#endif

#define MMP_BE_TIMEOUT_DELAY               (150)

#define MMP_BE_TIMER_OPTION_LIST           (5*1000)

#define MMP_BE_MAX_USR_LEN          (32)
#define MMP_BE_MAX_PWD_LEN          (32)

#define MMP_BE_MAX_PAGE_INFO_LEN			(64)


#ifdef APP_COLOR_MODE_PALLET
#define MMP_BE_GET_CLR_TRAN_BK() {255, { 0 }, { 0 }, { MMP_CLR_IDX_GET_WHITE() }}
#define MMP_BE_GET_CLR_WHITE() {255, { 0 }, { 0 }, { MMP_CLR_IDX_GET_WHITE() }}
#define MMP_BE_GET_CLR_THUMB_FRM_BK() {255, { 0 }, { 0 }, { MMP_CLR_IDX_GET_BLUE() }}
#define MMP_FB_GET_CLR_YELLOW() {255, { 0 }, { 0 }, { MMP_CLR_IDX_GET_YELLOW()}}
#define MMP_BE_GET_CLR_THUMB_ITEM_BK() {255, { 35 }, {56 }, { 115 }}
#else
#define MMP_BE_GET_CLR_TRAN_BK() {255, { 255 }, {255 }, { 255 }}
#define MMP_BE_GET_CLR_WHITE() {255, { 255 }, {255 }, { 255 }}
#define MMP_BE_GET_CLR_THUMB_FRM_BK() {255, { 17 }, {91 }, { 156 }} 
#define MMP_FB_GET_CLR_YELLOW() {255, {255}, {255}, {0}}
#define MMP_BE_GET_CLR_THUMB_ITEM_BK() {255, { 35 }, {56 }, { 115 }}
#endif

#define MMP_BE_RC_GET_NEXT_ROTATE(_e_op_type, _b_clockwise)             \
{                                                                       \
   if ((_b_clockwise))                                                  \
   {                                                                    \
       switch ((_e_op_type))                                            \
       {                                                                \
           case IMG_ROTATE_CLOCKWS_0_OP_TYPE:                           \
               (_e_op_type) = IMG_ROTATE_CLOCKWS_90_OP_TYPE;            \
               break;                                                   \
           case IMG_ROTATE_CLOCKWS_90_OP_TYPE:                          \
               (_e_op_type) = IMG_ROTATE_CLOCKWS_180_OP_TYPE;           \
               break;                                                   \
           case IMG_ROTATE_CLOCKWS_180_OP_TYPE:                         \
               (_e_op_type) = IMG_ROTATE_CLOCKWS_270_OP_TYPE;           \
               break;                                                   \
           case IMG_ROTATE_CLOCKWS_270_OP_TYPE:                         \
               (_e_op_type) = IMG_ROTATE_CLOCKWS_0_OP_TYPE;             \
               break;                                                   \
           default:                                                     \
               break;                                                   \
       }                                                                \
   }                                                                    \
   else                                                                 \
   {                                                                    \
       switch ((_e_op_type))                                            \
       {                                                                \
           case IMG_ROTATE_CLOCKWS_0_OP_TYPE:                           \
               (_e_op_type) = IMG_ROTATE_CLOCKWS_270_OP_TYPE;           \
               break;                                                   \
           case IMG_ROTATE_CLOCKWS_270_OP_TYPE:                         \
               (_e_op_type) = IMG_ROTATE_CLOCKWS_180_OP_TYPE;           \
               break;                                                   \
           case IMG_ROTATE_CLOCKWS_180_OP_TYPE:                         \
               (_e_op_type) = IMG_ROTATE_CLOCKWS_90_OP_TYPE;            \
               break;                                                   \
           case IMG_ROTATE_CLOCKWS_90_OP_TYPE:                          \
               (_e_op_type) = IMG_ROTATE_CLOCKWS_0_OP_TYPE;             \
               break;                                                   \
           default:                                                     \
               break;                                                   \
       }                                                                \
   }                                                                    \
}

#define MMP_BE_ITEM_FLAG_ROTATE           MMP_FF_ITEM_FLAG_CUSTOM_4

#define MMP_BE_RC_GET_IMG_ROTATE_FROM_ITEM_FLAG(_e_flag, _e_img_rotate)             \
{                                                                                   \
    if (MMP_FF_ITEM_FLAG_CUSTOM_0 & (_e_flag))                                      \
    {                                                                               \
        (_e_img_rotate) = IMG_ROTATE_CLOCKWS_0_OP_TYPE;                             \
    }                                                                               \
    else if (MMP_FF_ITEM_FLAG_CUSTOM_1 & (_e_flag))                                 \
    {                                                                               \
        (_e_img_rotate) = IMG_ROTATE_CLOCKWS_90_OP_TYPE;                            \
    }                                                                               \
    else if (MMP_FF_ITEM_FLAG_CUSTOM_2 & (_e_flag))                                 \
    {                                                                               \
        (_e_img_rotate) = IMG_ROTATE_CLOCKWS_180_OP_TYPE;                           \
    }                                                                               \
    else if (MMP_FF_ITEM_FLAG_CUSTOM_3 & (_e_flag))                                 \
    {                                                                               \
        (_e_img_rotate) = IMG_ROTATE_CLOCKWS_270_OP_TYPE;                           \
    }                                                                               \
}

#define MMP_BE_RC_GET_MMP_ROTATE_FROM_ITEM_FLAG(_e_flag, _e_mmp_rotate)             \
{                                                                                   \
    if (MMP_FF_ITEM_FLAG_CUSTOM_0 & (_e_flag))                                      \
    {                                                                               \
        (_e_mmp_rotate) = MMP_FP_LOAD_IMG_ROTATE_OP_CLOCKWS_0;                      \
    }                                                                               \
    else if (MMP_FF_ITEM_FLAG_CUSTOM_1 & (_e_flag))                                 \
    {                                                                               \
        (_e_mmp_rotate) = MMP_FP_LOAD_IMG_ROTATE_OP_CLOCKWS_90;                     \
    }                                                                               \
    else if (MMP_FF_ITEM_FLAG_CUSTOM_2 & (_e_flag))                                 \
    {                                                                               \
        (_e_mmp_rotate) = MMP_FP_LOAD_IMG_ROTATE_OP_CLOCKWS_180;                    \
    }                                                                               \
    else if (MMP_FF_ITEM_FLAG_CUSTOM_3 & (_e_flag))                                 \
    {                                                                               \
        (_e_mmp_rotate) = MMP_FP_LOAD_IMG_ROTATE_OP_CLOCKWS_270;                    \
    }                                                                               \
}

#define MMP_BE_RC_GET_ITEM_FLAG_FROM_ROTATE(_e_op_type, _e_flag)        \
{                                                                       \
   switch ((_e_op_type))                                                \
   {                                                                    \
        case IMG_ROTATE_CLOCKWS_0_OP_TYPE:                              \
            (_e_flag) = MMP_FF_ITEM_FLAG_CUSTOM_0;                      \
            break;                                                      \
        case IMG_ROTATE_CLOCKWS_90_OP_TYPE:                             \
            (_e_flag) = MMP_FF_ITEM_FLAG_CUSTOM_1;                      \
            break;                                                      \
        case IMG_ROTATE_CLOCKWS_180_OP_TYPE:                            \
            (_e_flag) = MMP_FF_ITEM_FLAG_CUSTOM_2;                      \
            break;                                                      \
        case IMG_ROTATE_CLOCKWS_270_OP_TYPE:                            \
            (_e_flag) = MMP_FF_ITEM_FLAG_CUSTOM_3;                      \
            break;                                                      \
        default:                                                        \
            break;                                                      \
   }                                                                    \
}

#define MMP_BE_RC_APPLY_ROTATE_FLAG(_e_item_flag, _e_rotate_flag)                                                                    \
{                                                                                                                                    \
   _e_item_flag &= ~(MMP_FF_ITEM_FLAG_CUSTOM_0 | MMP_FF_ITEM_FLAG_CUSTOM_1 | MMP_FF_ITEM_FLAG_CUSTOM_2 | MMP_FF_ITEM_FLAG_CUSTOM_3); \
   e_item_flag |= e_rotate_flag;                                                                                                     \
}

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern MMP_BE_FILTER_IDX_T mmp_be_rc_get_filter_idx_by_type(
     MMP_MEDIA_TYPE_T           e_media_type);

extern MMP_MEDIA_TYPE_T mmp_be_rc_get_filter_type_by_idx(
     MMP_BE_FILTER_IDX_T        e_idx);

extern UINT32 mmp_be_rc_get_filter_mlm_idx(
    MMP_BE_FILTER_IDX_T         e_idx);

#endif /*_MMP_BROWSE_ENG_RC_H_*/
