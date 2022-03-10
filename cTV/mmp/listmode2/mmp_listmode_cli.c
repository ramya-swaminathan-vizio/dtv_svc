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
 * $RCSfile: mmp_mmc_cli.c,v $
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
#include "c_os.h"
#include "c_cli.h"
#include "mmp/mmp_tools.h"
#include "mmp/app/mmp_cli.h"
#include "listmode.h"
#include "listmode_view.h"
#include "am/a_am.h"
#include "u_iom.h"
#include "c_dbg.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#ifdef CLI_SUPPORT
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static INT32 _mmp_lm_send_key(
        INT32                   i4_argc, 
        const CHAR**            pps_argv);

static CLI_EXEC_T at_mmp_lm_cmd_tbl[] =
{
    {   
        "send key",
        "sk",
        _mmp_lm_send_key,
        NULL,
        "Send keys to widget",
        CLI_ACCESS_RIGHT_APP_MMP
    },
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_mmp_lm_root_cmd_tbl[] =
{
    {   
        "listmode",
        "lm",
        NULL,
        at_mmp_lm_cmd_tbl,
        "Multimedia Listmode commands",
        CLI_ACCESS_RIGHT_APP_MMP
    },
    END_OF_CLI_CMD_TBL
};

/*-----------------------------------------------------------------------------
* private methods declarations
*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/ 
/*----------------------------------------------------------------------------
 * Name: mmp_lm_cli_init
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 mmp_lm_cli_init(VOID)
{
    /*register mmc CLI commands*/
    return mmp_cli_add_rec(&at_mmp_lm_root_cmd_tbl[0]);
}

/*-----------------------------------------------------------------------------
 * private VIEW methods implementations
 *---------------------------------------------------------------------------*/ 
/*-----------------------------------------------------------------------------
 * Name: _mmp_lm_send_key
 *
 * Description: This function is used to send keys, so that even we can not have rcu unit,
 *                    we can also oeprate in mmp/listmode.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_lm_send_key(
    INT32                       i4_argc, 
    const CHAR**                pps_argv)
{
    INT32      i4_ret = MMPR_OK;
    UINT32     ui4_key_code = 0;
    UINT8      ui1_browse_id = 0;
    BOOL       b_is_show = FALSE;
    CHAR       s_active_name [APP_NAME_MAX_LEN+1];

    i4_ret = a_am_get_active_app(s_active_name);
    if ((AMR_OK != i4_ret)
        ||(c_strcmp("mmp", s_active_name) != 0))
    {
        DBG_LOG_PRINT(("%s, %s, %d, crruent activated application is not mmp.\n\n\r",
                    __FILE__,
                    __FUNCTION__,
                    __LINE__));
        
        return MMPR_FAIL;
    }

    /* get browser type (listmode & visible ) */
    i4_ret = mmp_mc_browse_get_active(&ui1_browse_id, 
                                      &b_is_show);
    if ((MMPR_OK != i4_ret)
        ||(MMP_RC_BROWSER_ID_LIST != ui1_browse_id)
        ||(FALSE == b_is_show))
    {
        DBG_LOG_PRINT(("%s, %s, %d, crruent browse mode is not listmode.\n\n\r",
                    __FILE__,
                    __FUNCTION__,
                    __LINE__));
        
        return MMPR_FAIL;
    }

    /*help?*/
    if(c_strchr(pps_argv[1], 'h') || 1 == i4_argc)
    {
        DBG_LOG_PRINT(("Send key Parameter:\n\r"));
        DBG_LOG_PRINT(("    s       press BTN_SELECT key\n\r"));
        DBG_LOG_PRINT(("    l       press BTN_CURSOR_LEFT key\n\r"));
        DBG_LOG_PRINT(("    r       press BTN_CURSOR_RIGHT key\n\r"));
        DBG_LOG_PRINT(("    u       press BTN_CURSOR_UP key\n\r"));
        DBG_LOG_PRINT(("    d       press BTN_CURSOR_DOWN key\n\r"));
        return CLIR_OK;
    }

    if (c_strchr(pps_argv[1], 's'))
    {
        ui4_key_code = BTN_SELECT;
    }
    else if (c_strchr(pps_argv[1], 'l'))
    {
        ui4_key_code = BTN_CURSOR_LEFT;
    }
    else if (c_strchr(pps_argv[1], 'r'))
    {
        ui4_key_code = BTN_CURSOR_RIGHT;
    }
    else if (c_strchr(pps_argv[1], 'u'))
    {
        ui4_key_code = BTN_CURSOR_UP;
    }
    else if (c_strchr(pps_argv[1], 'd'))
    {
        ui4_key_code = BTN_CURSOR_DOWN;
    }
    else
    {
        DBG_LOG_PRINT(("Currently not support this key\n\r"));
    }


    /* send a key down & up event. */
    i4_ret = c_iom_send_evt(ui4_key_code,
                            100);
    if(IOMR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("%s, %s, %d, send key failed.\n\n\r",
                    __FILE__,
                    __FUNCTION__,
                    __LINE__));

        return MMPR_FAIL;
    }
    
    return MMPR_OK;
}
#endif


