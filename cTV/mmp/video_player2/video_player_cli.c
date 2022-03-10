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
 * $RCSfile: video_player_cli.c,v $
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
#include "mmp/video_engine/video_engine.h"
#include "video_player.h"

#ifdef CLI_SUPPORT
/*-----------------------------------------------------------------------------
   Static function prototype declaraions.
-----------------------------------------------------------------------------*/
static INT32 _mmp_video_player_cli_fopen (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _mmp_video_player_cli_play (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _mmp_video_player_cli_pause (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _mmp_video_player_cli_stop (INT32 i4_argc, const CHAR** pps_argv);
#if 0
static INT32 _mmp_video_player_cli_get_position (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _mmp_video_player_cli_set_position (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _mmp_video_player_cli_get_duration (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _mmp_video_player_cli_get_status (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _mmp_video_player_cli_get_elm (INT32 i4_argc, const CHAR** pps_argv);
#endif

static VOID  _mmp_video_player_do_cli_cmd_do(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4);
static VOID  _mmp_video_player_do_cli_fopen(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4);
#if 0
static VOID  _mmp_video_player_do_cli_get_position(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4);
static VOID  _mmp_video_player_do_cli_set_position(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4);
static VOID  _mmp_video_player_do_cli_get_elm(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4);
#endif

/*static VOID _mmp_video_player_show_nfy_fct(VOID* pv_tag, UINT32 ui4_ver,
                                 MMP_FP_SHOW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param);*/


static CLI_EXEC_T at_mmp_video_player_cmd_tbl[] =
{
    {   
        "fopen",
        NULL,
        _mmp_video_player_cli_fopen,
        NULL,
        "open the video_player file",
        CLI_ACCESS_RIGHT_APP_MMP
    },
    {   
        "play",
        NULL,
        _mmp_video_player_cli_play,
        NULL,
        "play the video_player file",
        CLI_ACCESS_RIGHT_APP_MMP
    },
    {   
        "pause",
        NULL,
        _mmp_video_player_cli_pause,
        NULL,
        "pause the video_player file",
        CLI_ACCESS_RIGHT_APP_MMP
    },
    {   
        "stop",
        NULL,
        _mmp_video_player_cli_stop,
        NULL,
        "stop the video_player file",
        CLI_ACCESS_RIGHT_APP_MMP
    },   
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_mmp_video_player_root_tbl[] =
{
    {   
        "videoplayer",
        "vp",
        NULL,
        at_mmp_video_player_cmd_tbl,
        "video player commands",
        CLI_ACCESS_RIGHT_APP_MMP
    },
    END_OF_CLI_CMD_TBL
};


/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/ 
/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_cli_fopen
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_video_player_cli_fopen (INT32 i4_argc, const CHAR** pps_argv)
{
    if ((i4_argc < 2)) {
        return MMPR_INV_ARG;
    }

    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_video_player_do_cli_fopen,
                                (VOID*)pps_argv[1],NULL,NULL,NULL);
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_cli_play
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_video_player_cli_play (INT32 i4_argc, const CHAR** pps_argv)
{
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_video_player_do_cli_cmd_do,
                                (VOID*)MMP_FP_SHOW_CMD_ID_START,NULL,NULL,NULL);
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_cli_pause
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_video_player_cli_pause (INT32 i4_argc, const CHAR** pps_argv)
{
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_video_player_do_cli_cmd_do,
                                (VOID*)MMP_FP_SHOW_CMD_ID_PAUSE,NULL,NULL,NULL);
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_cli_stop
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_video_player_cli_stop (INT32 i4_argc, const CHAR** pps_argv)
{
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_video_player_do_cli_cmd_do,
                                (VOID*)MMP_FP_SHOW_CMD_ID_STOP,NULL,NULL,NULL);
    return MMPR_OK;
}
#if 0
/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_cli_get_position
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_video_player_cli_get_position (INT32 i4_argc, const CHAR** pps_argv)
{
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_video_player_do_cli_get_position,
                                NULL,NULL,NULL,NULL);
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_cli_set_position
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_video_player_cli_set_position (INT32 i4_argc, const CHAR** pps_argv)
{
    if ((i4_argc < 2)) {
        return MMPR_INV_ARG;
    }

    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_video_player_do_cli_set_position,
                                (VOID*)pps_argv[1],NULL,NULL,NULL);
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_cli_get_duration
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_video_player_cli_get_duration (INT32 i4_argc, const CHAR** pps_argv)
{
    #if 0
    return video_engine_get_duration();
    #else
    return 0;
    #endif
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_cli_get_status
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_video_player_cli_get_status (INT32 i4_argc, const CHAR** pps_argv)
{
    #if 0
    return video_player_player_get_status();
    #else
    return 0;
    #endif
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_cli_get_elm
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_video_player_cli_get_elm (INT32 i4_argc, const CHAR** pps_argv)
{
    if ((i4_argc < 2)) {
        return MMPR_INV_ARG;
    }

    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_video_player_do_cli_get_elm,
                                (VOID*)pps_argv[1],NULL,NULL,NULL);
    return MMPR_OK;
}
#endif
/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_do_cli_fopen
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID  _mmp_video_player_do_cli_fopen(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4)
{
    /*CHAR* ps_filename = (CHAR*)pv_tag1;*/
    /* video_engine_info_open(ps_filename,_mmp_video_player_show_nfy_fct,NULL,0); */
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_do_cli_cmd_do
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID  _mmp_video_player_do_cli_cmd_do(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4)
{
    MMP_FP_SHOW_CMD_ID_T e_cmd_id = (MMP_FP_SHOW_CMD_ID_T)(INT32)pv_tag1;
    mmp_vp_cmd_do(e_cmd_id,NULL);
}
#if 0
/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_do_cli_get_position
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID  _mmp_video_player_do_cli_get_position(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4)
{
    #if 0
    video_player_get_position();
    #endif
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_do_cli_set_position
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID  _mmp_video_player_do_cli_set_position(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4)
{
    UINT32      ui4_pos;
    ui4_pos = (UINT32) x_strtoull((CHAR*)pv_tag1, NULL, 0);

    video_player_player_set_position(ui4_pos);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_do_cli_get_elm
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID  _mmp_video_player_do_cli_get_elm(VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3,VOID* pv_tag4)
{
    UINT32      ui4_idx;
    ui4_idx = (UINT32) x_strtoull((CHAR*)pv_tag1, NULL, 0);
    #if 0
    video_player_player_get_elm(ui4_idx);
    #endif
}
#endif
/*----------------------------------------------------------------------------
 * Name: _mmp_video_player_show_nfy_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
/*
static VOID _mmp_video_player_show_nfy_fct(VOID* pv_tag, UINT32 ui4_ver,
                                 MMP_FP_SHOW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
}
*/

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/ 
/*----------------------------------------------------------------------------
 * Name: mmp_video_player_cli_init
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
INT32 mmp_video_player_cli_init(VOID)
{
    return  mmp_cli_add_rec(&at_mmp_video_player_root_tbl[0]);
}

#endif /* CLI_SUPPORT */
