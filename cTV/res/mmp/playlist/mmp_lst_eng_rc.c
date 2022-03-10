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
 * $RCSfile: mmp_lst_eng_rc.c,v $
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
#include "am/a_am.h"
#include "mmp/a_mmp.h"
#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp/mmp_mmc_list.h"
#include "mmp/folder_parser/a_mmp_folder_psr.h"
#include "mmp/file_parser/a_mmp_ff_file_psr.h"
#include "mmp/playlist/_mmp_lst_eng.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
 
 /*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _mmp_lst_eng_rc_media_remove_handler(
        _MMP_LST_ENG_T*             pt_class, 
        _MMP_LST_ENG_PLAY_INST_T*   pt_object,
        MMP_REMOVE_DEVICE_INFO_T    e_info, 
        VOID*                       pv_tag);

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/ 
/*----------------------------------------------------------------------------
 * Name: mmp_lst_eng_rc_parser_register
 *
 * Description:
 *
 * Inputs:  
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 mmp_lst_eng_rc_parser_register(VOID)
{
    INT32                       i4_ret;

    /*register folder parser*/
    i4_ret = a_mmp_reg_folder_parser();
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }
    
    /*register alb parser*/

    /*register m3u parser*/
    i4_ret = a_mmp_reg_m3u_file_parser();
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }


/*register pls parser*/

    /*register file filter parser*/
    i4_ret = a_mmp_reg_ff_file_parser();
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: mmp_lst_eng_rc_override_handler
 *
 * Description:
 *
 * Inputs:  
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 mmp_lst_eng_rc_override_handler(VOID)
{
    INT32                       i4_ret;

    i4_ret = _mmp_lst_eng_override_media_remove_handler(_mmp_lst_eng_rc_media_remove_handler, NULL);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("_mmp_lst_eng_override_media_remove_handler() failed. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_lst_eng_rc_get_resumed_browser
 *
 * Description:
 *
 * Inputs:  
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
UINT8 mmp_lst_eng_rc_get_resumed_browser(MMP_APP_RESUME_INFO_T e_info)
{
    UINT8   ui1_bwr_id = MMP_BROWSE_ID_LAST;

    switch (e_info) 
    {
        case MMP_APP_RESUME_INFO_PHOTO_BWR:
            ui1_bwr_id = MMP_RC_BROWSER_ID_THUMBNAIL;
            break;
        case MMP_APP_RESUME_INFO_AUDIO_BWR:
        case MMP_APP_RESUME_INFO_VIDEO_BWR:
            ui1_bwr_id = MMP_RC_BROWSER_ID_LIST;
            break;
    #if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)  
        case MMP_APP_RESUME_INFO_DMR:
            ui1_bwr_id = MMP_RC_BROWSER_ID_DMR;
            break;
    #endif          
        default:
            break;
    }

    return ui1_bwr_id;
}

/*-----------------------------------------------------------------------------
 * private VIEW methods implementations
 *---------------------------------------------------------------------------*/ 
/*----------------------------------------------------------------------------
 * Name: _mmp_lst_eng_rc_media_remove_handler
 *
 * Description:
 *
 * Inputs:  
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_lst_eng_rc_media_remove_handler(
    _MMP_LST_ENG_T*             pt_class, 
    _MMP_LST_ENG_PLAY_INST_T*   pt_object,
    MMP_REMOVE_DEVICE_INFO_T    e_info, 
    VOID*                       pv_tag)
{
    MMP_PL_PCMD_BWR_EX_PARAM_T          t_bwr_param;
    INT32                               i4_ret;
    CHAR                                s_active_app[APP_NAME_MAX_LEN + 1];
    _MMP_LST_ENG_CHECK_NODE_RESULT_T    t_result;
    BOOL                                b_resume_browser = FALSE;

    if(NULL == pt_object)
    {
        /*in current design, pt_object should not be NULL.*/
        MMP_DBG_ERROR(("_mmp_lst_eng_rc_media_remove_handler(): pt_object is NULL.\r\n"));
        MMP_ASSERT(0);
        return;
    }
    /**/
    i4_ret = _mmp_lst_eng_check_play_node_valid(pt_class, pt_object, MMP_GROUND_MODE_ALL, &t_result);
    if(MMPR_OK != i4_ret)
    {
        b_resume_browser = TRUE;
    }
    else
    {
        if(t_result.b_remove_from_fg)
        {
            b_resume_browser = (_MMP_LST_ENG_GRND_STATUS_ACTIVATE & pt_object->t_ground[_MMP_LST_ENG_GROUND_IDX_FG].e_status) ? TRUE : FALSE;
        }

        if(FALSE == b_resume_browser)
        {
            if(t_result.b_remove_from_bk)
            {
                b_resume_browser = (_MMP_LST_ENG_GRND_STATUS_ACTIVATE & pt_object->t_ground[_MMP_LST_ENG_GROUND_IDX_BK].e_status) ? TRUE : FALSE;

                if(FALSE == b_resume_browser)
                {
                    i4_ret = mmp_mc_list_stop(MMP_GROUND_MODE_BACK);
                    if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_mc_list_stop(MMP_GROUND_MODE_BACK) failed. i4_ret = %d.\r\n", i4_ret));
                    }
                }
            }
        }
    }

    /**/
    if(b_resume_browser)
    {
        i4_ret = a_am_get_active_app(s_active_app);
        if(AMR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("a_am_get_active_app() failed. i4_ret = %d.\r\n", i4_ret));
            return;
        }
        
        /*not MMP active*/
        if(0 != c_strcmp(MMP_NAME, s_active_app))
        {
            return;
        }
        
        /*switch to file browser*/
        MMP_PL_PCMD_BWR_EX_PARAM_ZERO(t_bwr_param);
        t_bwr_param.ui1_browser_id = MMP_BROWSE_ID_LAST;
        t_bwr_param.e_stop_type = t_result.b_remove_from_bk ? MMP_PL_STOP_TYPE_STOP : MMP_PL_STOP_TYPE_AUTO;
        i4_ret = mmp_mc_list_browse_ex(&t_bwr_param);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_mc_list_browse_ex() failed. i4_ret = %d.\r\n", i4_ret));
        }
    }
}

