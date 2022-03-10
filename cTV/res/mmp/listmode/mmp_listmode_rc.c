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
 * $RCSfile: mmp_listmode_rc.c,v $
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

#include "res/mmp/listmode/mmp_listmode_rc.h"
#include "mmp/listmode2/listmode.h"

static INT32 _mmp_lm_get_audio_album_info(UINT32 ui4_idx, UTF16_T* pw2s_text, SIZE_T* pt_size);
static INT32 _mmp_lm_get_audio_artist_info(UINT32 ui4_idx, UTF16_T* pw2s_text, SIZE_T* pt_size);
static INT32 _mmp_lm_get_audio_duration_info(UINT32 ui4_idx, UTF16_T* pw2s_text, SIZE_T* pt_size);
static INT32 _mmp_lm_get_video_date_info(UINT32 ui4_idx, UTF16_T* pw2s_text, SIZE_T* pt_size);
static INT32 _mmp_lm_get_video_duration_info(UINT32 ui4_idx, UTF16_T* pw2s_text, SIZE_T* pt_size);

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_get_audio_album_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_get_audio_album_info(UINT32 ui4_idx, UTF16_T* pw2s_text, SIZE_T* pt_size)
{
    INT32   i4_ret;
    i4_ret = mmp_mc_browse_get_file_info(MMP_FP_INFO_TYPE_ALBUM, pt_size, (UINT8*)pw2s_text);
    return (i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_get_audio_artist_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_get_audio_artist_info(UINT32 ui4_idx, UTF16_T* pw2s_text, SIZE_T* pt_size)
{
    INT32   i4_ret;
    i4_ret = mmp_mc_browse_get_file_info(MMP_FP_INFO_TYPE_ARTIST, pt_size, (UINT8*)pw2s_text);
    return (i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_get_audio_duration_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_get_audio_duration_info(UINT32 ui4_idx, UTF16_T* pw2s_text, SIZE_T* pt_size)
{
    INT32   i4_ret;
    i4_ret = mmp_mc_browse_get_file_info(MMP_FP_INFO_TYPE_DURATION, pt_size, (UINT8*)pw2s_text);
    return (i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_get_video_date_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_get_video_date_info(UINT32 ui4_idx, UTF16_T* pw2s_text, SIZE_T* pt_size)
{
    INT32   i4_ret;
    i4_ret = mmp_mc_browse_get_file_info(MMP_FP_INFO_TYPE_DATE, pt_size, (UINT8*)pw2s_text);
    return (i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_lm_get_video_duration_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_get_video_duration_info(UINT32 ui4_idx, UTF16_T* pw2s_text, SIZE_T* pt_size)
{
    INT32   i4_ret;
    i4_ret = mmp_mc_browse_get_file_info(MMP_FP_INFO_TYPE_DURATION, pt_size, (UINT8*)pw2s_text);
    return (i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: mmp_lm_custom_col_register
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_lm_custom_col_register(VOID)
{
    INT32                   i4_ret;
    LM_DISPLAY_ITEM_REG_T   t_item_reg;

    c_memset(&t_item_reg, 0, sizeof(LM_DISPLAY_ITEM_REG_T));

    t_item_reg.e_media_type = MMP_MEDIA_TYPE_AUDIO;
    t_item_reg.ui2_item_cnt = 3;
    t_item_reg.ui2_name_col_mlm_idx = MLM_MMP_KEY_LM_TITLE_TRACK;
    t_item_reg.ui4_name_col_width   = LM_FILE_LB_AUDIO_FILE_NAME_COL_W;

    t_item_reg.at_item_cfg[0].ui2_title_mlm_idx = MLM_MMP_KEY_LIST_MODE_ALBUM;
    t_item_reg.at_item_cfg[0].ui4_width = LM_FILE_LB_AUDIO_ALBUM_COL_W;
    t_item_reg.at_item_cfg[0].pf_item_get_info = _mmp_lm_get_audio_album_info;

    t_item_reg.at_item_cfg[1].ui2_title_mlm_idx = MLM_MMP_KEY_LIST_MODE_ARTIST;
    t_item_reg.at_item_cfg[1].ui4_width = LM_FILE_LB_AUDIO_ARTIST_COL_W;
    t_item_reg.at_item_cfg[1].pf_item_get_info = _mmp_lm_get_audio_artist_info;

    t_item_reg.at_item_cfg[2].ui2_title_mlm_idx = MLM_MMP_KEY_LIST_MODE_DURATION;
    t_item_reg.at_item_cfg[2].ui4_width = LM_FILE_LB_AUDIO_DURATION_COL_W;
    t_item_reg.at_item_cfg[2].pf_item_get_info = _mmp_lm_get_audio_duration_info;

    i4_ret = mmp_listmode_media_item_info_register(&t_item_reg);
    IS_MMPR_OK(i4_ret);

    c_memset(&t_item_reg, 0, sizeof(LM_DISPLAY_ITEM_REG_T));

    t_item_reg.e_media_type = MMP_MEDIA_TYPE_VIDEO;
    t_item_reg.ui2_item_cnt = 2;
    t_item_reg.ui2_name_col_mlm_idx = MLM_MMP_KEY_LM_TITLE_FILE;
    t_item_reg.ui4_name_col_width   = LM_FILE_LB_VIDEO_FILE_NAME_COL_W;

    t_item_reg.at_item_cfg[0].ui2_title_mlm_idx = MLM_MMP_KEY_LIST_MODE_DATE;
    t_item_reg.at_item_cfg[0].ui4_width = LM_FILE_LB_VIDEO_DATE_COL_W;
    t_item_reg.at_item_cfg[0].pf_item_get_info = _mmp_lm_get_video_date_info;

    t_item_reg.at_item_cfg[1].ui2_title_mlm_idx = MLM_MMP_KEY_LIST_MODE_DURATION;
    t_item_reg.at_item_cfg[1].ui4_width = LM_FILE_LB_VIDEO_DURATION_COL_W;
    t_item_reg.at_item_cfg[1].pf_item_get_info = _mmp_lm_get_video_duration_info;

    i4_ret = mmp_listmode_media_item_info_register(&t_item_reg);
    IS_MMPR_OK(i4_ret);

    return (MMPR_OK);
}


