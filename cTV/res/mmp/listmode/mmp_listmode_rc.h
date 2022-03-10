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
 * $RCSfile: mmp_listmode_rc.h,v $
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

#ifndef _MMP_LISTMODE_RC_H_
#define _MMP_LISTMODE_RC_H_

#include "u_irrc_btn_def.h"
#include "mmp/mmp_common.h"
#include MMP_MLM_HEADER_FILE
#include "res/mmp/common_ui/mmp_common_ui_rc.h"
#include "res/mmp/img/mmp_img.h"

/* file list box size */
#define LM_FILE_LB_X                        (0*4/3)
#define LM_FILE_LB_Y                        (21*2)
#define LM_FILE_LB_W                        (664*2)
#define LM_FILE_LB_H                        (300*2)

/* preview rect */
#define LM_FILE_PREVIEW_X                   (572)
#define LM_FILE_PREVIEW_Y                   (4)
#define LM_FILE_PREVIEW_W                   (590)
#define LM_FILE_PREVIEW_H                   (268)

/* Playing item Info handle rect */
#define LM_FILE_INFO_HANDLE_X               (284*2)
#define LM_FILE_INFO_HANDLE_Y               (6*2)
#define LM_FILE_INFO_HANDLE_W               (671*2)
#define LM_FILE_INFO_HANDLE_H               (130*2)

/**/
#define LM_FILE_VIDEO_INFO_HANDLE_X         (584*2)
#define LM_FILE_VIDEO_INFO_HANDLE_Y         (2*2)
#define LM_FILE_VIDEO_INFO_HANDLE_W         (365*2)
#define LM_FILE_VIDEO_INFO_HANDLE_H         (118*2)

#define LM_OPTL_AU_SORT_NUM                 (6)
#define LM_OPTL_VD_SORT_NUM                 (4)

#define LM_OPTL_AU_VIEW_NUM                 (2)
#define LM_OPTL_VD_VIEW_NUM                 (2)
#define LM_OPTL_VD_PLAY_NUM                 (2)

#define LM_OPTL_ITEM_MAX_NUM                (9)

#define LM_FILE_LB_COL_MAX_NUM              (7)
#define LM_FILE_LB_FIX_COL_NUM              (4)
#define LM_FILE_LB_COL_FILE_NUM_IDX         (0)
#define LM_FILE_LB_COL_ICON_IDX             (1)
#define LM_FILE_LB_COL_FILE_NAME_IDX        (2)
#define LM_FILE_LB_COL_NULL_ICON_IDX        (3)

#define MMP_LEFT_LBW_IMG_COL_W              (50*4/3)

#define LM_FILE_LB_FILE_NUM_COL_W           (36*2)
#define LM_FILE_LB_ICON_COL_W               (30*2)
#define LM_FILE_LB_AUDIO_FILE_NAME_COL_W    (200*2)
#define LM_FILE_LB_AUDIO_ALBUM_COL_W        (180*2)
#define LM_FILE_LB_AUDIO_ARTIST_COL_W       (120*2)
#define LM_FILE_LB_AUDIO_DURATION_COL_W     (120*2)

#define LM_FILE_LB_VIDEO_FILE_NAME_COL_W    (310*2)
#define LM_FILE_LB_VIDEO_DATE_COL_W         (150*2)
#define LM_FILE_LB_VIDEO_DURATION_COL_W     (120*2)

#define LM_FILE_LB_COL_DEFAULT_W            (198*2)
#define LM_FILE_LB_COL_DEFAULT_LEN          (120)

#define MMP_LBW_NUM_TXT_TPML                ("%d.")
#define LM_FILE_LB_FILE_NUM_MAX_BIT         (5)

/* LBW ELEM SIZE */
#define LM_FILE_LB_LBW_ELEM_SIZE            (25*2)

/* number in per page in  LBW */
#define LM_LBW_ELEM_NUM_PER_PAGE            (LM_FILE_LB_H/LM_FILE_LB_LBW_ELEM_SIZE)

#define MMP_LIST_PAGE_LEFT_IDX              (0)
#define MMP_LIST_PAGE_TXT_IDX               (1)
#define MMP_LIST_PAGE_RIGHT_IDX             (2)

#define LBW_CUSTOM_COL_MAX_NUM              (3)
#define MMP_LM_TIMER_TIMEOUT_DELAY          (500)

#define LM_MAX_MEIDA_TYPE_CNT               (3)

#define LM_OPTION_LIST_TIMER                (10*1000)

#ifdef APP_COLOR_MODE_PALLET
#define MMP_LM_RC_GET_LISTMODE_TXT()                        \
    {                                                       \
        255, { 200 }, { 200 }, { MMP_CLR_IDX_GET_TXT() }    \
    }
#else
#define MMP_LM_RC_GET_LISTMODE_TXT()                        \
    {                                                       \
        255, { 255 }, { 255 }, { 255 }                      \
    }
#endif
#define MMP_LM_RC_GET_LISTMODE_TXT_OLED()                        \
    {                                                       \
        255, { 191 }, { 191 }, { 191 }                      \
    }


/* repaint rect */
typedef enum _MMP_LM_RC_REPAINT_RECT_ID_T
{
    MMP_LM_RC_REPAINT_RECT_ID_FILE_LB = 0,
    MMP_LM_RC_REPAINT_RECT_ID_MAIN_FRM,
    MMP_LM_RC_REPAINT_RECT_ID_SIDE_FRM,
    MMP_LM_RC_REPAINT_RECT_ID_CTRL_FRM,
    MMP_LM_RC_REPAINT_RECT_ID_INFO_FRM,
    MMP_LM_RC_REPAINT_RECT_ID_VIDEO_INFO,
    MMP_LM_RC_REPAINT_RECT_ID_AUDIO_INFO,
    MMP_LM_RC_REPAINT_RECT_ID_PAGE_INFO_LST,
    MMP_LM_RC_REPAINT_RECT_ID_BTN_AUDIO_PLAY,
    MMP_LM_RC_REPAINT_RECT_ID_FOLDER_PATH_TXT,
    MMP_LM_RC_REPAINT_RECT_ID_FOLDER_NAME,
    MMP_LM_RC_REPAINT_RECT_ID_AUDIO_CTRL_FRM,
    MMP_LM_RC_REPAINT_RECT_ID_VIDEO_CTRL_FRM,
    MMP_LM_RC_REPAINT_RECT_ID_OPT_LIST,
    MMP_LM_RC_REPAINT_RECT_ID_TO_SIDE_BAR,
    MMP_LM_RC_REPAINT_RECT_ID_LAST_ENTRY
} MMP_LM_RC_REPAINT_RECT_ID_T;


typedef INT32 (*lm_item_get_info_fct)(UINT32 ui4_idx,
                                      UTF16_T* pw2s_text,
                                      SIZE_T* pt_size);

typedef struct
{
    UINT16               ui2_title_mlm_idx;
    UINT32               ui4_width;
    lm_item_get_info_fct pf_item_get_info;
}LM_ITEM_CFG_T;

typedef struct
{
    MMP_MEDIA_TYPE_T    e_media_type;
    UINT16              ui2_item_cnt;
    UINT16              ui2_name_col_mlm_idx;
    UINT32              ui4_name_col_width;
    LM_ITEM_CFG_T       at_item_cfg[LBW_CUSTOM_COL_MAX_NUM];
}LM_DISPLAY_ITEM_REG_T;

extern INT32 mmp_lm_custom_col_register(VOID);

#define MMP_LM_RC_GET_SORT_TYPE(_e_media_type, _ui4_id, _e_sort)        \
{                                                                       \
    if (MMP_MEDIA_TYPE_AUDIO == (_e_media_type))                        \
    {                                                                   \
        switch ((_ui4_id))                                              \
        {                                                               \
            case 0:                                                     \
                (_e_sort) = MMP_SORT_TYPE_AUD_ALBUM;                    \
                break;                                                  \
            case 1:                                                     \
                (_e_sort) = MMP_SORT_TYPE_AUD_INV_ALBUM;                \
                break;                                                  \
            case 2:                                                     \
                (_e_sort) = MMP_SORT_TYPE_AUD_ARTIST;                   \
                break;                                                  \
            case 3:                                                     \
                (_e_sort) = MMP_SORT_TYPE_AUD_INV_ARTIST;               \
                break;                                                  \
            case 4:                                                     \
                (_e_sort) = MMP_SORT_TYPE_AUD_NAME;                     \
                break;                                                  \
            case 5:                                                     \
                (_e_sort) = MMP_SORT_TYPE_AUDIO_INV_NAME;               \
                break;                                                  \
            default:                                                    \
                (_e_sort) = MMP_SORT_TYPE_NONE;                         \
                break;                                                  \
        }                                                               \
    }                                                                   \
    else if (MMP_MEDIA_TYPE_VIDEO == (_e_media_type))                   \
    {                                                                   \
        switch ((_ui4_id))                                              \
        {                                                               \
            case 0:                                                     \
                (_e_sort) = MMP_SORT_TYPE_VIDEO_INV_DATE;               \
                break;                                                  \
            case 1:                                                     \
                (_e_sort) = MMP_SORT_TYPE_VIDEO_DATE;                   \
                break;                                                  \
            case 2:                                                     \
                (_e_sort) = MMP_SORT_TYPE_VIDEO_NAME;                   \
                break;                                                  \
            case 3:                                                     \
                (_e_sort) = MMP_SORT_TYPE_VIDEO_INV_NAME;               \
                break;                                                  \
            default:                                                    \
                (_e_sort) = MMP_SORT_TYPE_NONE;                         \
                break;                                                  \
        }                                                               \
    }                                                                   \
    else                                                                \
    {                                                                   \
        (_e_sort) = MMP_SORT_TYPE_NONE;                                 \
    }                                                                   \
}


/* listmode toolbar resource */

#endif /*_MMP_FILE_BROWSER_RC_H_*/
