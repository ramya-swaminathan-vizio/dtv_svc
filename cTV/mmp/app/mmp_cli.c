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
 * $RCSfile: mmp_cli.c,v $
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

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define MMP_CLI_RESERVED_COUNT   ((UINT32) 10)

typedef struct __MMP_CLI_DATA_MEMBER_T
{
    CLI_EXEC_T  at_recs[MMP_CLI_RESERVED_COUNT + 1];
    UINT16      ui2_dbg_level;
    UINT8       ui1_used;
    BOOL        b_is_inited;
} _MMP_CLI_DATA_MEMBER_T;

#ifdef CLI_SUPPORT
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _MMP_CLI_DATA_MEMBER_T   t_g_mmp_cli;

static INT32 _mmp_cli_cmd_get_dbg_level(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _mmp_cli_cmd_set_dbg_level(INT32 i4_argc, const CHAR** pps_argv);

static CLI_EXEC_T at_mmp_def_cmd_tbl[] =
{
    {   
        "sub",
        NULL,
        NULL,
        NULL,
        "Sub component's commands",
        CLI_ACCESS_RIGHT_APP_MMP
    },
    {
        CLI_GET_DBG_LVL_STR,
        NULL,
        _mmp_cli_cmd_get_dbg_level,
        NULL,
        CLI_GET_DBG_LVL_HELP_STR,
        CLI_ACCESS_RIGHT_APP_MMP
    },
    {
        CLI_SET_DBG_LVL_STR,
        NULL,
        _mmp_cli_cmd_set_dbg_level,
        NULL,
        CLI_SET_DBG_LVL_HELP_STR,
        CLI_ACCESS_RIGHT_APP_MMP
    },
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_mmp_root_cmd_tbl[] =
{
    {   
        "mmp",
        NULL,
        NULL,
        at_mmp_def_cmd_tbl,
        "Multimedia commands",
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
 * Name: mmp_cli_init
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 mmp_cli_init(VOID)
{
    _MMP_CLI_DATA_MEMBER_T*     pt_this = &t_g_mmp_cli;
    CLI_EXEC_T                  t_empty_rec = END_OF_CLI_CMD_TBL;
    INT32                       i4_ret, i;

    /*init instance*/
    pt_this->ui2_dbg_level = DBG_LEVEL_NONE;
    pt_this->ui1_used = 0;
    for(i = 0; i < (MMP_CLI_RESERVED_COUNT + 1); i++)
    {
        pt_this->at_recs[i] = t_empty_rec;
    }

    /*init root table*/
    at_mmp_def_cmd_tbl[0].pt_next_level = pt_this->at_recs;

    /*register to CLI*/
    if(FALSE == pt_this->b_is_inited)
    {
    i4_ret = c_cli_attach_cmd_tbl(at_mmp_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI);
    if(CLIR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_cli_attach_cmd_tbl() failed. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

        pt_this->b_is_inited = TRUE;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_cli_add_rec
 *
 * Description: This API performs the registration for the EPG application.
 *
 * Inputs:  pt_reg       References the registration structure.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
extern INT32 mmp_cli_deinit(VOID)
{
    _MMP_CLI_DATA_MEMBER_T*     pt_this = &t_g_mmp_cli;
    CLI_EXEC_T                  t_empty_rec = END_OF_CLI_CMD_TBL;
    INT32                       i;

    /*init instance*/
    pt_this->ui2_dbg_level = DBG_LEVEL_NONE;
    pt_this->ui1_used = 0;
    for(i = 0; i < (MMP_CLI_RESERVED_COUNT + 1); i++)
    {
        pt_this->at_recs[i] = t_empty_rec;
    }

    /*init root table*/
    at_mmp_def_cmd_tbl[0].pt_next_level = NULL;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_cli_add_rec
 *
 * Description: This API performs the registration for the EPG application.
 *
 * Inputs:  pt_reg       References the registration structure.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 mmp_cli_add_rec(const CLI_EXEC_T* pt_rec)
{
    _MMP_CLI_DATA_MEMBER_T* pt_this = &t_g_mmp_cli;

    if(NULL == pt_rec)
    {
        MMP_DBG_ERROR(("pt_rec cannot be NULL.\r\n"));
        return MMPR_OUT_OF_LIMIT;
    }

    if(MMP_CLI_RESERVED_COUNT <= pt_this->ui1_used)
    {
        MMP_DBG_ERROR(("Pool for CLI command is full. Max count = %d.\r\n", MMP_CLI_RESERVED_COUNT));
        return MMPR_OUT_OF_LIMIT;
    }

    pt_this->at_recs[pt_this->ui1_used] = *pt_rec;
    pt_this->ui1_used++;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_cli_get_dbg_level
 *
 * Description: This API returns the current setting of debug level.
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns: The current setting of debug level.
 ----------------------------------------------------------------------------*/
UINT16 mmp_cli_get_dbg_level(VOID)
{
    return t_g_mmp_cli.ui2_dbg_level;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_cli_set_dbg_level
 *
 * Description: This API set the debug level.
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns: The current setting of debug level.
 ----------------------------------------------------------------------------*/
VOID mmp_cli_set_dbg_level(
    UINT16                      ui2_db_level)
{
    t_g_mmp_cli.ui2_dbg_level = ui2_db_level;
}

/*-----------------------------------------------------------------------------
 * private VIEW methods implementations
 *---------------------------------------------------------------------------*/ 
/*-----------------------------------------------------------------------------
 * Name: _mmp_cli_cmd_get_dbg_level
 *
 * Description: This API gets the current debug level of Navigator.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_cli_cmd_get_dbg_level(
    INT32                       i4_argc, 
    const CHAR**                pps_argv)
{
    INT32  i4_ret;

    i4_ret = c_cli_show_dbg_level(mmp_cli_get_dbg_level());

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_cli_cmd_set_dbg_level
 *
 * Description: This API sets the debug level of Navigator.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_cli_cmd_set_dbg_level(
    INT32                       i4_argc, 
    const CHAR**                pps_argv)
{
    UINT16 ui2_dbg_level;
    INT32  i4_ret;

    i4_ret = c_cli_parse_dbg_level(i4_argc, pps_argv, &ui2_dbg_level);

    if(CLIR_OK == i4_ret)
    {
        mmp_cli_set_dbg_level(ui2_dbg_level);
    }

    return i4_ret;
}

#endif /*CLI_SUPPORT*/
