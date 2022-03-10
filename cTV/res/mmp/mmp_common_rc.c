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
 * $RCSfile: mmp_common_rc.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "mmp/mmp_common.h"
#include "res/mmp/mmp_common_rc.h"

#include "mmp/mmp_tools.h"
#include "mmp/mmp_mmc_browse.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
const CHAR as_g_audio_ext [][MMP_RC_MAX_EXT_LEN] = {
    /* follow VIZIO MMP\Audio spec ,only support mp3&wav*/
    "mp3",
    "m4a",
    "wav",
    "flac" 
};

const CHAR as_g_audio_lst_ext [][MMP_RC_MAX_EXT_LEN] = {
    "m3u",
    "m3u8"
};

const CHAR as_g_audio_network_only_ext [][MMP_RC_MAX_EXT_LEN] = {
    "pcm"
};

#ifdef APP_IPCC_SUPPORT
const CHAR* as_g_video_expt[] =
{
    "xml",
    "m4t"
};
const INT16 ui2_g_video_expt_cnt = 2;
#endif

const CHAR as_g_video_ext [][MMP_RC_MAX_EXT_LEN] = {
        "mp4" ,
        "m4v" ,
        "3gp" ,
        "3g2" ,
        "webm",
        "mkv" ,
        "ogg" ,
        "ts",
        "mk4"
};
const CHAR as_g_video_3d_ext [][MMP_RC_MAX_EXT_LEN] = {
        "ssif"
};

const CHAR as_g_image_ext [][MMP_RC_MAX_EXT_LEN] = {
        "jpg",
        "jpeg",
        "bmp",
        "png",
        "gif"
};

const CHAR as_g_text_ext [][MMP_RC_MAX_EXT_LEN] = {
        "txt"
};

const UINT16 ui2_g_audio_ext_count = (UINT16)(sizeof (as_g_audio_ext) / sizeof (as_g_audio_ext[0]));
const UINT16 ui2_g_audio_lst_ext_count = (UINT16)(sizeof (as_g_audio_lst_ext) / sizeof (as_g_audio_lst_ext[0]));
const UINT16 ui2_g_audio_network_only_ext_count = (UINT16)(sizeof (as_g_audio_network_only_ext) / sizeof (as_g_audio_network_only_ext[0]));
const UINT16 ui2_g_video_ext_count = (UINT16)(sizeof (as_g_video_ext) / sizeof (as_g_video_ext[0]));
const UINT16 ui2_g_video_3d_ext_count = (UINT16)(sizeof (as_g_video_3d_ext) / sizeof (as_g_video_3d_ext[0]));
const UINT16 ui2_g_image_ext_count = (UINT16)(sizeof (as_g_image_ext) / sizeof (as_g_image_ext[0]));
const UINT16 ui2_g_text_ext_count  = (UINT16)(sizeof (as_g_text_ext) / sizeof (as_g_text_ext[0]));

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
 /*----------------------------------------------------------------------------
 * Name: mmp_mc_rc_switch_browser
 *
 * Description:
 *
 * Inputs: -ui1_browser_id: target browser_id
 *            -pv_info: information which will be used when switch browser
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
extern INT32 mmp_mc_rc_switch_browser(
    UINT8   ui1_browser_id,
    VOID*  pv_info)
{
    MMP_MC_RC_SWITCH_BROWSER_INFO_T* pt_switch_info = NULL;

    if(NULL == pv_info)
    {
        return MMPR_INV_ARG;
    }

    pt_switch_info = (MMP_MC_RC_SWITCH_BROWSER_INFO_T*)pv_info;

    MMP_DBG_INFO((" [%s]  ui1_browser_id = [%d] ui4_cur_focus_idx = [%d] \r\n",
                __FUNCTION__, ui1_browser_id, pt_switch_info->ui4_cur_focus_idx));


    return 0; //mmp_mc_browse_enter(ui1_browser_id,pt_switch_info->ui4_cur_focus_idx, TRUE);
}
