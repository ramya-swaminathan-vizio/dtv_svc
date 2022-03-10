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
 * $RCSfile: fac_shell_dbg.h,v $
 * $Revision: #1 $
 * $Date: 2014/07/05 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 80d824ab48f4d49e3d38d28c8fc07509 $
 *
 * Description:
 *      This file contains the images used by the Wizard application.
 *---------------------------------------------------------------------------*/
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "u_common.h"
#include "u_cli.h"
#include "u_dbg.h"

#include "c_cli.h"

#include "a_gluelayer_comm.h"
#include "fac_shell_dbg.h"


extern T_CMD_DATA_MAP at_mac_cmd_map[];
extern T_CMD_DATA_MAP at_api_cmd_map[];
extern T_CMD_DATA_MAP at_stru_cmd_map[];

extern VOID* a_gluelayer_get_so_handle(VOID);
extern INT32 a_gluelayer_get_so_name(CHAR *ps_so_name);

UINT16 ui2_fac_shell_dbg_lvl = DBG_LEVEL_ERROR;

static INT32 _cmd_set_dbg_level(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _cmd_get_dbg_level(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _cmd_print_fac_symbol_addr(INT32 i4_argc, const CHAR** pps_argv);

static CLI_EXEC_T at_fac_shell_cmd_tbl[] = 
{
    {CLI_SET_DBG_LVL_STR,     NULL,   _cmd_set_dbg_level,   NULL, CLI_SET_DBG_LVL_HELP_STR,                         CLI_GUEST},
    {CLI_GET_DBG_LVL_STR,     NULL,   _cmd_get_dbg_level,   NULL, CLI_GET_DBG_LVL_HELP_STR,                         CLI_GUEST},
    {"fsa",                   NULL,   _cmd_print_fac_symbol_addr, NULL, "Print factory symbol addrs",               CLI_GUEST},

    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_fac_shell_root_cmd_tbl[] =
{
    {"fac_shell", NULL,  NULL,  at_fac_shell_cmd_tbl, "App Factory shell",   CLI_GUEST},
    END_OF_CLI_CMD_TBL
};


UINT16 fac_shell_get_dbg_lvl(VOID)
{
    return ui2_fac_shell_dbg_lvl;
}

static INT32 _cmd_set_dbg_level(INT32        i4_argc, 
                                const CHAR** pps_argv)
{
    UINT16 ui2_dbg_level;
    if (c_cli_parse_dbg_level (i4_argc, pps_argv, &ui2_dbg_level) == CLIR_OK)
    {
        ui2_fac_shell_dbg_lvl = ui2_dbg_level;
    }
    return(CLIR_OK);
}

static INT32 _cmd_get_dbg_level(INT32        i4_argc, 
                                const CHAR** pps_argv)
{
    c_cli_show_dbg_level(ui2_fac_shell_dbg_lvl);
    return 0;
}

static INT32 _cmd_print_fac_symbol_addr(INT32 i4_argc,
                                  const CHAR** pps_argv)
{
    UINT32  ui4_i = 0;
    char *error = NULL;
    char ac_so_name[128] = {0};
    VOID *pv_fct = NULL;
    VOID *dl_handle = NULL;

    a_gluelayer_get_so_name(ac_so_name);
    DBG_LOG_PRINT(("\ndlopen :%s\n", ac_so_name));

    if (2 == i4_argc && pps_argv[1] != NULL)
    {
        dl_handle = dlopen(ac_so_name, RTLD_NOW|RTLD_LOCAL);
        if (NULL == dl_handle)
        {
    		DBG_LOG_PRINT(("\ndlopen err:%s\n", dlerror()));
            return GLUELR_FAIL;				
        }

        pv_fct = dlsym(dl_handle, pps_argv[1]);
        error = dlerror();
        if (NULL == pv_fct || error != NULL )
        {  
            DBG_LOG_PRINT(("\nERROR:get symbol address from %s fail(%s)!!\n\n", 
                                                    ac_so_name,
                                                    error));
            dlclose(dl_handle);
            return GLUELR_FAIL;
        }

        DBG_LOG_PRINT(("<FAC SHELL> Gluelayer: Line %d: %s Addr:0x%p\r\n", __LINE__, pps_argv[1], pv_fct));
        dlclose(dl_handle);
        return GLUELR_OK;
    }

    DBG_LOG_PRINT((DBG_MODULE_NAME_PREFIX"begin print macro address.\r\n"));
    for (ui4_i = 0; ui4_i < GLUELAYER_CMD_M_END; ui4_i++)
    {
        if (at_mac_cmd_map[ui4_i].ui4_cmd == 0)
        {
            DBG_LOG_PRINT((DBG_MODULE_NAME_PREFIX"end print macro address, ui4_i=%d.\r\n",ui4_i));
            break;
        }
        DBG_LOG_PRINT(("<FAC SHELL> Gluelayer: name[%s] \tValue[0x%x] \tcmd=[%d]\r\n", 
                                                at_mac_cmd_map[ui4_i].s_name, 
                                                *((INT32*)at_mac_cmd_map[ui4_i].pv_data),
                                                at_mac_cmd_map[ui4_i].ui4_cmd));
    }

    DBG_LOG_PRINT((DBG_MODULE_NAME_PREFIX"begin print api address.\r\n"));
    for (ui4_i = 0; ui4_i < GLUELAYER_CMD_A_END; ui4_i++)
    {
        if (at_api_cmd_map[ui4_i].ui4_cmd == 0)
        {
            DBG_LOG_PRINT((DBG_MODULE_NAME_PREFIX"end print api address, ui4_i=%d.\r\n",ui4_i));
            break;
        }

        {
            DBG_LOG_PRINT(("<FAC SHELL> Gluelayer: name[%s] \tAddr[0x%x] \tcmd=[%d]\r\n", 
                                                at_api_cmd_map[ui4_i].s_name, 
                                                (*((UINT32*)at_api_cmd_map[ui4_i].pv_data)),
                                                at_api_cmd_map[ui4_i].ui4_cmd));
        }
    }

    DBG_LOG_PRINT((DBG_MODULE_NAME_PREFIX"begin print structure address.\r\n"));
    for (ui4_i = 0; ui4_i < GLUELAYER_CMD_S_END; ui4_i++)
    {
        if (at_stru_cmd_map[ui4_i].ui4_cmd == 0)
        {
            DBG_LOG_PRINT((DBG_MODULE_NAME_PREFIX"end print structure address, ui4_i=%d.\r\n",ui4_i));
            break;
        }
        DBG_LOG_PRINT(("<FAC SHELL> Gluelayer: name[%s] \tAddr[0x%x] \tcmd=[%d]\r\n", 
                                                at_stru_cmd_map[ui4_i].s_name, 
                                                at_stru_cmd_map[ui4_i].pv_data,
                                                at_stru_cmd_map[ui4_i].ui4_cmd));
    }
    
    return GLUELR_OK;
}

INT32 fac_shell_attach_cmd_tbl(VOID)
{
#ifdef CLI_SUPPORT
    INT32 i4_ret = c_cli_attach_cmd_tbl(at_fac_shell_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_NONE);
    if (i4_ret == CLIR_NOT_INIT)
    {
        DBG_LOG_PRINT(("<FAC SHELL>CLI not init"));
        return GLUELR_OK;
    }
#endif
    return GLUELR_OK;
}

