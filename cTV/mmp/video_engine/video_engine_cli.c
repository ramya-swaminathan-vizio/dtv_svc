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
 * $RCSfile: video_engine_cli.c,v $
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
#include "mmp/mmp_tools.h"
#include "mmp/app/mmp_cli.h"
#include "video_engine.h"

#ifdef CLI_SUPPORT

/*-----------------------------------------------------------------------------
 * macros, typedefs, enums
 *---------------------------------------------------------------------------*/
#define _MMP_VE_CLI_NFY_ARRAY_SIZE ((UINT8) (32 + 1))

/*-----------------------------------------------------------------------------
 * static function prototype declaraions.
 *---------------------------------------------------------------------------*/
static INT32 _mmp_video_engine_cli_dump (INT32 i4_argc, const CHAR** pps_argv);

static VOID  _mmp_video_engine_do_cli_dump(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4);

static CLI_EXEC_T at_mmp_video_engine_cmd_tbl[] =
{
    {
        "dump",
        NULL,
        _mmp_video_engine_cli_dump,
        NULL,
        "dump state",
        CLI_ACCESS_RIGHT_APP_MMP
    },
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_mmp_video_engine_root_tbl[] =
{
    {
        "videoengine",
        "ve",
        NULL,
        at_mmp_video_engine_cmd_tbl,
        "video engine commands",
        CLI_ACCESS_RIGHT_APP_MMP
    },
    END_OF_CLI_CMD_TBL
};

static CHAR aps_mmp_video_engine_nfy_tbl[][64] = {
    "SVCTX_NTFY_CODE_NORMAL",
    "SVCTX_NTFY_CODE_SVCTX_THREAD_KICK_OFF",
    "SVCTX_NTFY_CODE_DELIVERY_SYSTEM_CHANGE",
    "SVCTX_NTFY_CODE_SIGNAL_DETECTING",
    "SVCTX_NTFY_CODE_SIGNAL_LOCKED",
    "SVCTX_NTFY_CODE_SIGNAL_LOSS",
    "SVCTX_NTFY_CODE_INTERRUPTED",
    "SVCTX_NTFY_CODE_SERVICE_CHANGING",
    "SVCTX_NTFY_CODE_OWN_SERVICE_CHANGING",
    "SVCTX_NTFY_CODE_SERVICE_BLOCKED",
    "SVCTX_NTFY_CODE_SIGNAL_LOSS_AS_BLOCKED",
    "SVCTX_NTFY_CODE_SIGNAL_LOCKED_AS_BLOCKED",
    "SVCTX_NTFY_CODE_SERVICE_UNBLOCKED",
    "SVCTX_NTFY_CODE_STOPPED",
    "SVCTX_NTFY_CODE_IN_STOPPING",
    "SVCTX_NTFY_CODE_CRNT_EVN_START_QUERY",   
    "SVCTX_NTFY_CODE_CRNT_EVN_NOT_READY",
    "SVCTX_NTFY_CODE_CRNT_EVN_READY",
    "SVCTX_NTFY_CODE_NO_AUDIO_VIDEO_SVC",
    "SVCTX_NTFY_CODE_AUDIO_ONLY_SVC",
    "SVCTX_NTFY_CODE_VIDEO_ONLY_SVC",
    "SVCTX_NTFY_CODE_AUDIO_VIDEO_SVC",
    "SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_VIDEO_SVC",
    "SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_CLEAR_VIDEO_SVC",
    "SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_NO_VIDEO_SVC",
    "SVCTX_NTFY_CODE_SCRAMBLED_VIDEO_CLEAR_AUDIO_SVC",
    "SVCTX_NTFY_CODE_SCRAMBLED_VIDEO_NO_AUDIO_SVC",
    "SVCTX_NTFY_CODE_AUDIO_ONLY_STRM",
    "SVCTX_NTFY_CODE_VIDEO_ONLY_STRM",
    "SVCTX_NTFY_CODE_WITH_CC_AVIL_INDICATOR",
    "SVCTX_NTFY_CODE_NO_CC_AVIL_INDICATOR",
    "SVCTX_NTFY_CODE_EXISTED_CC_IND_CHG",
    "SVCTX_NTFY_CODE_NO_ANY_STREAM",
    "SVCTX_NTFY_CODE_NO_STREAM",
    "SVCTX_NTFY_CODE_STREAM_STOPPED",
    "SVCTX_NTFY_CODE_STREAM_STARTED",
    "SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE",
    "SVCTX_NTFY_CODE_AUDIO_FMT_UPDATE",
    "SVCTX_NTFY_CODE_VIDEO_AUTO_CLK_POS_PHS_DONE",
    "SVCTX_NTFY_CODE_VIDEO_AUTO_COLOR_DONE",
    "SVCTX_NTFY_CODE_VIDEO_ANA_COLOR_SYSTEM",
    "SVCTX_NTFY_CODE_STREAM_STOPPED_AS_BLOCKED",
    "SVCTX_NTFY_CODE_STREAM_STARTED_AS_BLOCKED",
    "SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE_AS_BLOCKED",
    "SVCTX_NTFY_CODE_AUDIO_AUTO_MUTE",
    "SVCTX_NTFY_CODE_AUDIO_AUTO_UNMUTE",
    "SVCTX_NTFY_CODE_VIDEO_AUTO_MUTE",
    "SVCTX_NTFY_CODE_VIDEO_AUTO_UNMUTE",
    "SVCTX_NTFY_CODE_VIDEO_PLAY_DONE",
    "SVCTX_NTFY_CODE_SCDB_ADD",
    "SVCTX_NTFY_CODE_SCDB_DEL",
    "SVCTX_NTFY_CODE_SCDB_MODIFY",
    "SVCTX_NTFY_CODE_NO_RESOURCES",
    "SVCTX_NTFY_CODE_INTERNAL_ERROR",
    "SVCTX_NTFY_CODE_CA",
    "SVCTX_NTFY_CODE_CP",    
    "SVCTX_NTFY_CODE_TUNER_SIGNAL_LOCKED",
    "SVCTX_NTFY_CODE_TUNER_SIGNAL_LOSS",
    "SVCTX_NTFY_CODE_CH_SRC_FROM_TUNER",
    "SVCTX_NTFY_CODE_CH_SRC_FROM_SCART",
    "SVCTX_NTFY_CODE_RF_SCAN_REQUIRED",
    "SVCTX_NTFY_CODE_UNFREEZE",
    "SVCTX_NTFY_CODE_TV_SYS_DETECTED",
    "SVCTX_NTFY_CODE_AUD_SYS_DETECTED",
    "SVCTX_NTFY_CODE_START_ALTER_FREQ_TUNE",
    "SVCTX_NTFY_CODE_END_ALTER_FREQ_TUNE",
    "SVCTX_NTFY_CODE_START_FIRST_TUNE",
    "SVCTX_NTFY_CODE_END_FIRST_TUNE",
    "SVCTX_NTFY_CODE_START_FREQ_LIST_UPDATED_CHK",
    "SVCTX_NTFY_CODE_END_FREQ_LIST_UPDATED_CHK",
    "SVCTX_NTFY_CODE_MEDIA_LOST",
    "SVCTX_NTFY_CODE_MEDIA_PRE_PROCESSING",
    "SVCTX_NTFY_CODE_MEDIA_PRE_PROCESSED",
    "SVCTX_NTFY_CODE_MEDIA_PB_RANGE_ALLOC",
    "SVCTX_NTFY_CODE_MEDIA_ERROR",
    "SVCTX_NTFY_CODE_MEDIA_CHAPTER_UPDATE", 
    "SVCTX_NTFY_CODE_MEDIA_TITLE_UPDATE",
    "SVCTX_NTFY_CODE_MEDIA_DURATION_UPDATE",
    "SVCTX_NTFY_CODE_MEDIA_SPEED_UPDATE",
    "SVCTX_NTFY_CODE_MEDIA_AB_REPEAT_DONE",
    "SVCTX_NTFY_CODE_MEDIA_UOP_INVALID",
    "SVCTX_NTFY_CODE_MEDIA_SEEK_READY",
    "SVCTX_NTFY_CODE_MEDIA_SEEK_ERROR",
    "SVCTX_NTFY_CODE_MEDIA_REPEAT_DONE",
    "SVCTX_NTFY_CODE_MEDIA_MENU_PRESNT",
    "SVCTX_NTFY_CODE_MEDIA_EOS",
    "SVCTX_NTFY_CODE_MEDIA_AS_CODEC_NOT_SUPPORT",
    "SVCTX_NTFY_CODE_MEDIA_VS_CODEC_NOT_SUPPORT",
    "SVCTX_NTFY_CODE_MEDIA_THUMBNAIL_DONE",
    "SVCTX_NTFY_CODE_MEDIA_HD_NOT_SUPPORT",
    "SVCTX_NTFY_CODE_MEDIA_DRM_NOT_SUPPORT",
    "SVCTX_NTFY_CODE_MEDIA_SUBTITLE_FMT_UPDATE",
    "SVCTX_NTFY_CODE_REACH_VALID_RANGE_START",
    "SVCTX_NTFY_CODE_REACH_VALID_RANGE_END",
    "SVCTX_NTFY_CODE_MEDIA_BAD_TICK_Y_TO_N",
    "SVCTX_NTFY_CODE_MEDIA_BAD_TICK_N_TO_Y",
    "SVCTX_NTFY_CODE_MEDIA_FILE_NOT_SUPPORT",
    "SVCTX_NTFY_CODE_MEDIA_RESOLUTION_NOT_SUPPORT",
    "SVCTX_NTFY_CODE_MEDIA_FRAMERATE_NOT_SUPPORT",
    "SVCTX_NTFY_CODE_MEDIA_NO_CONTENT",
    "SVCTX_NTFY_CODE_MEDIA_RANGE_AB_DONE",
    "SVCTX_NTFY_CODE_MEDIA_VIDEO_PRESENT",
    "SVCTX_NTFY_CODE_MEDIA_VS_BIT_RATE",
    "SVCTX_NTFY_CODE_INP_SIGNAL_UNKNOWN",
    "SVCTX_NTFY_CODE_HDCP_DETECT",
    "SVCTX_NTFY_CODE_HDCP_NOT_DETECT",
    "SVCTX_NTFY_CODE_MACROVISION_DETECT",
    "SVCTX_NTFY_CODE_MACROVISION_NOT_DETECT"
};

static SVCTX_NTFY_CODE_T t_g_nfy_array[_MMP_VE_CLI_NFY_ARRAY_SIZE];
static INT16 i2_g_bgn_idx = -1;
static INT16 i2_g_nxt_idx = 0;

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
 /*----------------------------------------------------------------------------
 * Name: _mmp_video_engine_cli_dump
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_video_engine_cli_dump (INT32 i4_argc, const CHAR** pps_argv)
{
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_video_engine_do_cli_dump,
                                NULL, NULL, NULL, NULL);
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_engine_do_cli_dump
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID  _mmp_video_engine_do_cli_dump(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4)
{
    INT16 i = 0, i2_disp_idx = 0;
    
    if(-1 == i2_g_bgn_idx)
    {
	    return;
	}

    DBG_LOG_PRINT(("The following is the latest context notification.\n"));

    for(i = i2_g_bgn_idx;
        i != i2_g_nxt_idx;
        i = ((i + 1) % _MMP_VE_CLI_NFY_ARRAY_SIZE))
    {
	    DBG_LOG_PRINT(("[%02d] %s\n", ++i2_disp_idx, aps_mmp_video_engine_nfy_tbl[ t_g_nfy_array[i] ]));
    }

    /*
    if(i2_g_bgn_idx == ((i2_g_nxt_idx + 1) % _MMP_VE_CLI_NFY_ARRAY_SIZE))
    {
        DBG_LOG_PRINT(("[%02d] %s\n", i2_disp_idx, aps_mmp_video_engine_nfy_tbl[i2_g_nxt_idx]));
    }
    */
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/ 
/*----------------------------------------------------------------------------
 * Name: mmp_video_engine_cli_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_video_engine_cli_init(VOID)
{
    c_memset(t_g_nfy_array, 0,
             sizeof(SVCTX_NTFY_CODE_T) * _MMP_VE_CLI_NFY_ARRAY_SIZE);
    
    return  mmp_cli_add_rec(&at_mmp_video_engine_root_tbl[0]);
}

/*----------------------------------------------------------------------------
 * Name: mmp_video_engine_cli_save_nfy_code
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_video_engine_cli_save_nfy_code(SVCTX_NTFY_CODE_T e_nfy_code)
{
    if(i2_g_bgn_idx == ((i2_g_nxt_idx + 1) % _MMP_VE_CLI_NFY_ARRAY_SIZE))
    {
        i2_g_bgn_idx = (i2_g_bgn_idx + 1) % _MMP_VE_CLI_NFY_ARRAY_SIZE;
    }

    t_g_nfy_array[i2_g_nxt_idx] = e_nfy_code;
    i2_g_nxt_idx = (i2_g_nxt_idx + 1) % _MMP_VE_CLI_NFY_ARRAY_SIZE;

    if(-1 == i2_g_bgn_idx)
    {
        i2_g_bgn_idx = 0;
    }

    if (SVCTX_NTFY_CODE_NORMAL > e_nfy_code)
    {
        return MMPR_INV_ARG;
    }

#if 0
    DBG_INFO(("The latest context notification: %s\n", aps_mmp_video_engine_nfy_tbl[e_nfy_code]));
#else
    if (e_nfy_code < (sizeof(aps_mmp_video_engine_nfy_tbl) / sizeof(aps_mmp_video_engine_nfy_tbl[0])))
    {
        DBG_LOG_PRINT(("%s\n", aps_mmp_video_engine_nfy_tbl[e_nfy_code]));
    }
#endif

    return MMPR_OK;
}
   
#endif /* CLI_SUPPORT */

