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
 * $RCSfile: banner_cli.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

#ifdef CLI_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <stdlib.h>
#include "app_util/a_cli_app.h"

#include "cc_info.h"

/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/
extern VOID nav_ci_enable_log(BOOL b_on);
extern INT32 nav_ci_set_visible(BOOL b_show);
/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: _banner_cli_cmd
 *
 * Description: This API is used to do cli cmd for banner
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/


static INT32 _cc_info_enable_cc_cli_cmd (
    INT32                       i4_argc,
    const CHAR**                pps_argv
    )
{
    if(c_strlen(pps_argv[1]) != 1 ||
       (pps_argv[1][0] != '0' && pps_argv[1][0] != '1') )
    {
        DBG_LOG_PRINT(("error :invalid argv!!!\n"));
    }
    BOOL b_on_off = (BOOL)atoi(pps_argv[1]);
    nav_ci_set_visible((BOOL)atoi(pps_argv[1])) ;
    DBG_LOG_PRINT(("set cc  -> %s\n",b_on_off == TRUE ? "SHOW":"HIDE"));
    return NAVR_OK ;
}

static INT32 _cc_info_cli_cmd (
    INT32                       i4_argc,
    const CHAR**                pps_argv
    )
{
    if(c_strlen(pps_argv[1]) != 1 ||
       (pps_argv[1][0] != '0' && pps_argv[1][0] != '1') )
    {
        DBG_LOG_PRINT(("error :invalid argv!!!\n"));
    }
    BOOL b_on_off = (BOOL)atoi(pps_argv[1]);
    nav_ci_enable_log(b_on_off) ;
    DBG_LOG_PRINT(("set cc log -> %s\n",b_on_off == TRUE ? "ON":"OFF"));
    return NAVR_OK ;
}


static CLI_EXEC_T at_cc_cmd_tbl[] =
{
    {
        "log",
        "l",
        _cc_info_cli_cmd,
        NULL,
        "usage: log num (1->on,0->off)",
        NAV_CLI_ACCESS_RIGHT_LVL
    },
    {
       "enable cc",
       "ec",
       _cc_info_enable_cc_cli_cmd,
       NULL,
       "usage: en num (1->show,0->hide)",
        NAV_CLI_ACCESS_RIGHT_LVL
    },
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T t_g_cc_entry =
{
    "closed caption",
    "cc",
    NULL,
    at_cc_cmd_tbl,
    "Commands for Display closed caption(CC) informations",
    NAV_CLI_ACCESS_RIGHT_LVL
};


/*-----------------------------------------------------------------------------
 * Name banner_cli_init
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 cc_info_cli_init()
{
    return nav_register_comp_cli_entry(&t_g_cc_entry) ;
}


/*-----------------------------------------------------------------------------
                    export function implementations
-----------------------------------------------------------------------------*/

#endif /* CLI_SUPPORT */

