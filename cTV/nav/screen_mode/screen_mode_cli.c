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
 * $RCSfile: screen_mode_cli.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

#include "c_cli.h"
#include "nav/navigator.h"
#include "screen_mode_cli.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
extern BOOL   g_b_sys_asp_rat_log_enable;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_scrn_set_sysbuild_log_enable(INT32 i4_argc, const CHAR** pps_argv);



static CLI_EXEC_T at_scrn_cmd_tbl[] =
{
    {"Disable/Enable", "to", _nav_scrn_set_sysbuild_log_enable, NULL, "Disable or Enable sysbuild log", NAV_CLI_ACCESS_RIGHT_LVL}, 
    END_OF_CLI_CMD_TBL
};
/* screen mode command entry */
static CLI_EXEC_T t_g_screen_mode_entry =
    {
        "screen mode",
        "scrn",
        NULL,
        at_scrn_cmd_tbl,
        "screen mode commands",
        NAV_CLI_ACCESS_RIGHT_LVL
    };

static INT32 _nav_scrn_set_sysbuild_log_enable(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32       i4_val = 0;
    
    /* Check arguments */
    if(i4_argc != 2)
    {        
        DBG_LOG_PRINT(("to 0 -- Disable sysbuild log\n"));         
        DBG_LOG_PRINT(("to 1  -- Enable sysbuild log\n"));         
        return 0;
    }
    
    i4_val = nav_atoi(pps_argv[1]);
    
    if (i4_val == 0)
    {
        DBG_LOG_PRINT(("Disable sysbuild log\n"));
        g_b_sys_asp_rat_log_enable = FALSE;
        
    }
    else if (i4_val == 1)
    {
        DBG_LOG_PRINT(("Enable sysbuild log\n"));
        g_b_sys_asp_rat_log_enable = TRUE;
    }
    
    return CLIR_OK;
}


/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name:    nav_scrn_mode_cli_register_cmd_tbl
 * Description:
 *      The API is used to register screen mode table. The API must be invoked
 *      in a_nav_screen_mode_register().
 * Input arguments:
 *      NONE
 * Output arguments:
 *      NONE
 * Returns:
 *      NONE
 *----------------------------------------------------------------------------*/
VOID nav_scrn_mode_cli_register_cmd_tbl(VOID)
{
    nav_register_comp_cli_entry(&t_g_screen_mode_entry);
}



