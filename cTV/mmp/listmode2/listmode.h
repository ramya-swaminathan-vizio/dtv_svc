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
 * $RCSfile: listmode.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *          This is the header file for list_mode.
 *---------------------------------------------------------------------------*/
#ifndef _MMP_LISTMODE_H_
#define _MMP_LISTMODE_H_

#include "mmp/mmp_mmc_basic.h"
#include "listmode_view.h"
#include "mmp/mmp_intf_playlist.h"

#include "c_os.h"
#include MMP_MLM_HEADER_FILE
#include "u_irrc_btn_def.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/mmp/listmode/mmp_listmode_rc.h"
#include "mmp/browse_eng/mmp_browse_eng.h"

#define MMP_TM_TAG_PARENT               ((UINT32) 0x00000001)
#define MMP_TM_TAG_REPAINT              ((UINT32) 0x00000010)
#define MMP_TM_TAG_SET_HLT(hlt)         ((UINT32)hlt<<16)
#define MMP_TM_TAG_GET_HLT(hlt)         ((UINT32)(hlt>>16))

#define MMP_LM_TAG_SET_DEPTH(dep)       ((UINT32)dep<<8)
#define MMP_LM_TAG_GET_DEPTH(dep)       ((UINT32)(dep>>8)&0x000000FF)

#define MMP_LM_SEL_INDEX                ((UINT32)0xffffffff)

#define MMP_FB_LM_FILE_INFO_LENG        (60)
#define MMP_INV_FILE_IDX                MMP_NULL_FILE_IDX

typedef struct
{
    UINT32                  ui4_cnt;
    LM_DISPLAY_ITEM_REG_T   at_item_reg[LM_MAX_MEIDA_TYPE_CNT];
}MMP_LM_ITEM_REG_INFO_T;

#define EXTEND_INFO_LENGTH        (32)
#define MMP_LM_AUDIO_COL_ALBUM     (0)
#define MMP_LM_AUDIO_COL_ARTIST    (1)
#define MMP_LM_AUDIO_COL_DUEATION  (2)
#define MMP_LM_VIDEO_COL_DATE      (0)
#define MMP_LM_VIDEO_COL_DURATION  (1)

typedef struct _MMP_LM_EXTEND_AUDIO_INFO_T
{
    UTF16_T     w2s_album[EXTEND_INFO_LENGTH];
    UTF16_T     w2s_artist[EXTEND_INFO_LENGTH];
    UTF16_T     w2s_duration[EXTEND_INFO_LENGTH];
}MMP_LM_EXTEND_AUDIO_INFO_T;

typedef struct _MMP_LM_EXTEND_VIDEO_INFO_T
{
    UTF16_T     w2s_date[EXTEND_INFO_LENGTH];
    UTF16_T     w2s_duration[EXTEND_INFO_LENGTH];
}MMP_LM_EXTEND_VIDEO_INFO_T;

typedef struct _MMP_LM_ITEM_INFO_T
{
    UTF16_T       ws_name[MMP_BE_MAX_PATH_LEN];
    UTF16_T       ws_parent_name[MMP_BE_MAX_PATH_LEN];
    UTF16_T       w2s_num[LM_FILE_LB_FILE_NUM_MAX_BIT];
    MMP_ITEM_TYPE_T e_item_type;

    union
    {
        MMP_LM_EXTEND_AUDIO_INFO_T t_audio;
        MMP_LM_EXTEND_VIDEO_INFO_T t_video;
    }u_extend_info;
} MMP_LM_ITEM_INFO_T;

/* List mode status */
typedef enum _E_MMP_LM_LOAD_STATUS_T
{
    LM_STATUS_NORMAL = 0,
    LM_STATUS_LOOP,
    LM_STATUS_LAST_ENTRY
}E_MMP_LM_LOAD_STATUS_T;

typedef enum _MMP_LM_FILE_STATUS_T
{
    MMP_LM_FILE_STATUS_NONE = 0,
    MMP_LM_FILE_IS_PLAYING,
    MMP_LM_FILE_IS_PAUSED,
    MMP_LM_FILE_IS_STOPED,
    MMP_LM_FILE_LAST_ENTRY
}MMP_LM_FILE_STATUS_T;

extern INT32 a_mmp_listmode_register(VOID);

extern INT32 mmp_listmode_item_selected(UINT32   ui4_hlt_idx);

extern INT32 mmp_lm_get_file_status_by_idx(UINT32               ui4_sel_idx,
                                              MMP_MEDIA_TYPE_T      e_meida_type,
                                              MMP_LM_FILE_STATUS_T* pe_status);

extern INT32 mmp_listmode_media_item_info_register(LM_DISPLAY_ITEM_REG_T* pt_item);

extern INT32 mmp_lm_get_cur_display_item_info(LM_DISPLAY_ITEM_REG_T* pt_item);

extern VOID mmp_lm_set_load_status(E_MMP_LM_LOAD_STATUS_T e_load_status);

extern E_MMP_LM_LOAD_STATUS_T mmp_lm_get_load_status(VOID);
#if 0
extern INT32 mmp_lm_reload_current_page(VOID);
#endif
extern VOID mmp_lm_update_file_status(UINT32 ui4_file_idx);
extern VOID mmp_lm_update_crnt_playing_file();
#ifdef APP_TTS_SUPPORT
extern UTF16_T* mmp_lm_get_file_name_by_idx(UINT32  ui4_sel_idx);
#endif
#endif /* _MMP_LISTMODE_H_ */
