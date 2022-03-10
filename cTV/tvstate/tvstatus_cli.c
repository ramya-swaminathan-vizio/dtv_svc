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
 * $RCSfile: tvstatus_cli.c,v $
 * $Revision: #2 $
 * $Date: 2015/06/25 $
 * $Author: jg_wanlihong $
 * $CCRevision: /main/DTV_X_ATSC/13 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 0dc5e5894593d8bd6b2c6ecc9869c8fa $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "app_util/a_cli_app.h"

#include "tvstate/tvstatus.h"
#include "tvstate/a_tvstatus.h"
#include "tvstate/tvstatus_dbg.h"


#ifdef CLI_SUPPORT
/*
   Static function prototype declaraions.
*/
static INT32 _tvstatus_cli_attach_cmd_tbl (VOID);
static INT32 _tvstatus_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _tvstatus_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _tvstatus_cli_cli_in_tvstatus (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _tvstatus_cli_enable_func(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _tvstatus_cli_disable_func(INT32 i4_argc, const CHAR** pps_argv);

/*
   Command tables.
*/
static CLI_EXEC_T at_tvstatus_cmd_tbl[] =
{
    {
        CLI_GET_DBG_LVL_STR,
        NULL,
        _tvstatus_cli_get_dbg_level,
        NULL,
        CLI_GET_DBG_LVL_HELP_STR,
        CLI_GUEST
    },
    {
        CLI_SET_DBG_LVL_STR,
        NULL,
        _tvstatus_cli_set_dbg_level,
        NULL,
        CLI_SET_DBG_LVL_HELP_STR,
        CLI_GUEST
    },
    {
        "cli_in_tvstatus",
        "citt",
        _tvstatus_cli_cli_in_tvstatus,
        NULL,
        "Test CLI in tvstatus thread",
        CLI_SUPERVISOR
    },
    {
        "open_tvstat",
        "ot",
        _tvstatus_cli_enable_func,
        NULL,
        "Open tvstatus thread",
        CLI_SUPERVISOR
    },
    {
        "close_tvstat",
        "ct",
        _tvstatus_cli_disable_func,
        NULL,
        "Close tvstatus thread",
        CLI_SUPERVISOR
    },
    END_OF_CLI_CMD_TBL
};

/*
   root command table.
*/
static CLI_EXEC_T at_tvstatus_root_cmd_tbl[] =
{
    {"tvstatus", NULL, NULL, at_tvstatus_cmd_tbl, "TVSTATUS commands", CLI_GUEST},
    END_OF_CLI_CMD_TBL
};


/*----------------------------------------------------------------------------
 * Name:    _tvstatus_cli_attach_cmd_tbl
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _tvstatus_cli_attach_cmd_tbl (VOID)
{
    return (c_cli_attach_cmd_tbl (at_tvstatus_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI));
}

/*-----------------------------------------------------------------------------
 * Name: _tvstatus_cli_get_dbg_level
 *
 * Description: This API gets the current debug level of TVSTATUS application.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _tvstatus_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    return c_cli_show_dbg_level (tvstatus_get_dbg_level());
}

/*-----------------------------------------------------------------------------
 * Name: _tvstatus_cli_set_dbg_level
 *
 * Description: This API sets debug level to TVSTATUS application.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _tvstatus_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32       i4_ret;
    UINT16      ui2_dbg_level;

    i4_ret = c_cli_parse_dbg_level (i4_argc, pps_argv, & ui2_dbg_level);

    if (i4_ret == CLIR_OK)
    {
        tvstatus_set_dbg_level (ui2_dbg_level);
    }
    else
    {
        DBG_LOG_PRINT (("<TVSTATUS> ERR: set debug level failed = %d\n\r", i4_ret));
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _tvstatus_cli_cli_in_tvstatus
 *
 * Description: This API test the "CLI_IN_TVSTATUS_THREAD" feature
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _tvstatus_cli_cli_in_tvstatus (INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8*   pui1_data;

    CLI_IN_TVSTATUS_THREAD(_tvstatus_cli_cli_in_tvstatus);

    pui1_data = (UINT8*)c_mem_alloc(8);
    if(pui1_data != NULL)
    {
        DBG_LOG_PRINT(("Successful.\n"));
        c_mem_free(pui1_data);
        return 0;
    }
    else
    {
        DBG_LOG_PRINT(("Failed.\n"));
        return -1;
    }
}

static INT32 _tvstatus_cli_enable_func(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret = 0;
    extern BOOL b_g_enable_tvstat;

    b_g_enable_tvstat = TRUE;

    i4_ret = a_tvstat_start(b_g_enable_tvstat);

    return i4_ret;
}

static INT32 _tvstatus_cli_disable_func(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret = 0;
    extern BOOL b_g_enable_tvstat;

    b_g_enable_tvstat = FALSE;

    i4_ret = a_tvstat_start(b_g_enable_tvstat);

    return i4_ret;
}

#endif /* CLI_SUPPORT */

/*-----------------------------------------------------------------------------
 * Name: tvstatus_cli_init
 *
 * Description: This API initializes CLI component for TVSTATUS application.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TVSTAR_OK                     Routine successful.
 *          TVSTAR_FAIL                   CLI operation failed.
 ----------------------------------------------------------------------------*/
INT32 tvstatus_cli_init (VOID)
{

#if defined(CLI_SUPPORT) || defined(CLI_STRESS_MODE)

    INT32    i4_ret;

    /* Attach command table to CLI. */
    i4_ret = _tvstatus_cli_attach_cmd_tbl ();

    if (i4_ret != CLIR_OK)
    {
        return TVSTAR_FAIL;
    }

    return TVSTAR_OK;

#else

    return TVSTAR_OK;

#endif /* CLI_SUPPORT */

}
