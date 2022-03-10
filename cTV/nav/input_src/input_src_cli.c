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
#include "app_util/a_cli_app.h"
#include "u_cli.h"
#include "c_cli.h"

#include "rest/a_rest.h"
#include "rest/a_rest_api.h"
#include "nav/nav_common.h"
#include "nav/input_src/a_input_src.h"
#include "nav/input_src/input_src.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/nav/nav_dbg.h"

//#include "banner_common.h"

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
static INT32 _ipts_create_vtrl_cmd (INT32 i4_argc, const CHAR** pps_argv);

static INT32 _ipts_delete_vtrl_cmd (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _ipts_list_vtrl_cmd (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _ipts_clean_vtrl_cmd (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _ipts_select_vtrl_cmd (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _ipts_list_source_cmd(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _ipts_change_src_cmd(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _ipts_set_log_cli_cmd(INT32 i4_argc, const CHAR** pps_argv);
static INT32  _atoi (const CHAR* ps);

/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/
static CLI_EXEC_T at_ipts_cmd_tbl[] =
{
    {
        "set log level",
        "l",
        _ipts_set_log_cli_cmd,
        NULL,
        "usage: log [f]",
        CLI_GUEST
    },
    {
        "create_vtrl",
        "c",
        _ipts_create_vtrl_cmd,
        NULL,
        "usage: create_vtrl cname,name_en[en],name_en[fr],name_en[es],Hide/Unhide,aftername",
        CLI_GUEST
    },
    {
        "delete_vtrl",
        "d",
        _ipts_delete_vtrl_cmd,
        NULL,
        "usage: delete_vtrl(d) cname",
        CLI_GUEST
    },
    {
        "list_vtrl",
        "l",
        _ipts_list_vtrl_cmd,
        NULL,
        "usage: list_vtrl(l) cname",
        CLI_GUEST
    },
    {
        "select_vtrl",
        "s",
        _ipts_select_vtrl_cmd,
        NULL,
        "usage: select_vtrl(s) cname",
        CLI_GUEST
    },
    {
        "clean_vtrl",
        "cl",
        _ipts_clean_vtrl_cmd,
        NULL,
        "usage: clean_vtrl(cl)",
        CLI_GUEST
    },
    {
        "list_source",
        "isl",
        _ipts_list_source_cmd,
        NULL,
        "usage: list_source(isl)",
        CLI_GUEST
    },
    {
        "change_source",
        "cs",
        _ipts_change_src_cmd,
        NULL,
        "usage: change_source(cs) id",
        CLI_GUEST
    },

    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T t_g_ipts_entry =
{
    "ipts",
    "i",
    NULL,
    at_ipts_cmd_tbl,
    "Commands for ipts",
    CLI_GUEST
};


/*-----------------------------------------------------------------------------
                    function implementations
-----------------------------------------------------------------------------*/
static INT32  _atoi (const CHAR* ps)
{
    INT32  i4_total;

    i4_total = 0;

    while (*ps != 0)
    {
        if (*ps >= '0' && *ps <= '9')
        {
            /* accumulate digit */
            i4_total = 10 * i4_total + (*ps - '0');
            ps ++; /* get next char */
        }
        else /* not a digit */
        {
            return (-1);
        }
    }

    return i4_total;
}
/*-----------------------------------------------------------------------------
 * Name: _ipts_create_vtrl_cmd
 *
 * Description: This API is used to do cli cmd for vtrl input
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _ipts_create_vtrl_cmd(INT32 i4_argc, const CHAR** pps_argv)
{
    TYPE_APP_VTRL_INPUT t_vtrl_input;

    if (i4_argc != 7)
    {
        DBG_LOG_PRINT(("\n usage: create_vtrl(c) cname,name_en[en],name_en[fr],name_en[es],Hide/Unhide,aftername")) ;
        return NAVR_OK ;
    }
    DBG_LOG_PRINT(("<VTRL INPUT> file: %s line: %d  %s pps_argv[1] %s,sizeof(pps_argv[2]) %d\n pps_argv[2] %s,pps_argv[3]%s,pps_argv[4] %s",
        __FILE__, __LINE__, __FUNCTION__, pps_argv[1],sizeof(pps_argv[2]),pps_argv[2],pps_argv[3],pps_argv[4]));


    c_strncpy(t_vtrl_input.s_cname, pps_argv[1], 24);
    t_vtrl_input.s_cname[23] = '\0';
    c_strncpy(t_vtrl_input.s_name_en[0], pps_argv[2], 24);
    t_vtrl_input.s_name_en[0][23] = '\0';
    c_strncpy(t_vtrl_input.s_name_en[1], pps_argv[3], 24);
    t_vtrl_input.s_name_en[1][23] = '\0';
    c_strncpy(t_vtrl_input.s_name_en[2], pps_argv[4], 24);
    t_vtrl_input.s_name_en[2][23] = '\0';
    t_vtrl_input.b_hideable= _atoi(pps_argv[5]);
    c_strncpy(t_vtrl_input.s_position_after, pps_argv[6], 24);
    t_vtrl_input.s_position_after[23] = '\0';

    a_nav_ipts_create_virtual_input(&t_vtrl_input);


    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _ipts_delete_vtrl_cmd
 *
 * Description: This API is used to do cli cmd for vtrl input
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _ipts_delete_vtrl_cmd (
    INT32                       i4_argc,
    const CHAR**                pps_argv
    )
{
    CHAR    s_cname[24] = {0} ;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: delete_vtrl(d) cname")) ;


        return NAVR_OK ;
    }

    c_strncpy(s_cname, pps_argv[1], 24);
    a_nav_ipts_delete_virtual_input(s_cname);



    return NAVR_OK ;
}
/*-----------------------------------------------------------------------------
 * Name: _ipts_list_vtrl_cmd
 *
 * Description: This API is used to do cli cmd for vtrl input
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _ipts_list_vtrl_cmd(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT16  ui2_i;
    SIZE_T  z_size = 0;
    //UINT16  ui2_cfg_idx;
    CHAR    s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    UINT8   ui1_hide_value = 0;
    UINT8   ui1_hide_value_unique = 0;

    if (i4_argc != 1)
    {
        DBG_LOG_PRINT(("\n usage: list_vtrl(l)")) ;
        return NAVR_OK ;
    }

    DBG_LOG_PRINT(("\ncname: "));
    for(ui2_i=0;ui2_i<5;ui2_i++)
    {
        //ui2_cfg_idx = IDX_IPTS_VTRL_NAME_1 + ui2_i;
        //i4_ret = acfg_get(ui2_cfg_idx, s_inp_name, &z_size);
        a_cfg_get_vtrl_name(ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
        DBG_LOG_PRINT((" %d):%s ",ui2_i,s_inp_name));

    }

    DBG_LOG_PRINT(("\nENG name: "));
    for(ui2_i=0;ui2_i<5;ui2_i++)//find id
    {
        //ui2_cfg_idx = IDX_IPTS_VTRL_DSP_NAME_ENG_1 + ui2_i;
        //i4_ret = acfg_get(ui2_cfg_idx, s_inp_name, &z_size);
        a_cfg_get_name_display(1,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
        DBG_LOG_PRINT((" %d):%s ",ui2_i,s_inp_name));

    }

    DBG_LOG_PRINT(("\nFRE name: "));
    for(ui2_i=0;ui2_i<5;ui2_i++)//find id
    {
        //ui2_cfg_idx = IDX_IPTS_VTRL_DSP_NAME_FRE_1 + ui2_i;
        //i4_ret = acfg_get(ui2_cfg_idx, s_inp_name, &z_size);
        a_cfg_get_name_display(2,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
        DBG_LOG_PRINT((" %d):%s ",ui2_i,s_inp_name));

    }

    DBG_LOG_PRINT(("\nSPA name: "));
    for(ui2_i=0;ui2_i<5;ui2_i++)//find id
    {
        //ui2_cfg_idx = IDX_IPTS_VTRL_DSP_NAME_SPA_1 + ui2_i;
        //i4_ret = acfg_get(ui2_cfg_idx, s_inp_name, &z_size);
        a_cfg_get_name_display(3,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
        DBG_LOG_PRINT((" %d):%s ",ui2_i,s_inp_name));

    }

    DBG_LOG_PRINT(("\nHide_value: "));

    acfg_get(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, &z_size);
    DBG_LOG_PRINT(("\nHide_value: %d",ui1_hide_value));
    for(ui2_i=0;ui2_i<5;ui2_i++)
    {
        ui1_hide_value_unique = ((ui1_hide_value >> ui2_i) & 0x1);
        DBG_LOG_PRINT((" %d):%d ",ui2_i,ui1_hide_value_unique));

    }

    DBG_LOG_PRINT(("\n"));

    return NAVR_OK ;
}
/*-----------------------------------------------------------------------------
 * Name: _ipts_clean_vtrl_cmd
 *
 * Description: This API is used to do cli cmd for vtrl input
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _ipts_clean_vtrl_cmd(INT32 i4_argc, const CHAR** pps_argv)
{
    a_nav_ipts_clean_virtual_input();

    return NAVR_OK ;
}
static INT32 _ipts_select_vtrl_cmd(INT32 i4_argc, const CHAR** pps_argv)
{
    CHAR    s_cname[24] = {0} ;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: select_vtrl(s) cname")) ;


        return NAVR_OK ;
    }

    c_strncpy(s_cname, pps_argv[1], 24);
    DBG_LOG_PRINT(("\n  select_vtrl s_cname %s",s_cname)) ;
    a_nav_ipts_select_virtual_input(s_cname);


    return NAVR_OK ;
}

static INT32 _ipts_change_src_cmd(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8       source_id = 0;
    ISL_REC_T   t_isl_iterate = {0};
    
    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: change_source(cs) id")) ;
        return NAVR_OK ;
    }

    source_id = _atoi(pps_argv[1]);
    if(ISLR_NOT_EXIST == a_isl_get_rec_by_idx(source_id, &t_isl_iterate))
    {
        DBG_LOG_PRINT(("\n usage: change_source(cs) id")) ;
        return NAVR_OK ;
    }
    
    DBG_LOG_PRINT(("\nchange source to id %d\n",source_id));
    nav_ipts_switch_src(NAV_IPTS_SMS_BY_ID,TV_WIN_ID_MAIN,source_id);
    return NAVR_OK ;
}


static INT32 _ipts_set_log_cli_cmd(INT32 i4_argc, const CHAR** pps_argv)
{
    INT16                       i2_log_type = 0 ;
    const CHAR*                 ps = NULL ;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("\n usage: log [-/f]")) ;
        DBG_LOG_PRINT(("\n        - -> NONE ")) ;
        DBG_LOG_PRINT(("\n        f -> function ")) ;
        DBG_LOG_PRINT(("\n---------------------\ncurrent = ")) ;

        i2_log_type = ipts_get_log_type() ;

        if (i2_log_type == 0)
        {
            DBG_LOG_PRINT(("NONE")) ;
        }
        else
        {
            if (i2_log_type & _ISL_LOG_TYPE_FUNC)
            {
                DBG_LOG_PRINT(("f")) ;
            }
        }
        return NAVR_OK ;
    }

    ps = pps_argv[1] ;

    if (!ps)
    {
        NAV_CHK_FAIL(NAVR_INV_ARG) ;
    }

    i2_log_type = 0 ;

    while (*ps)
    {
        if (*ps == '-')
        {
            i2_log_type = 0 ;
            return NAVR_OK ;
        }

        if (*ps == 'f'|| *ps =='F')
        {
            i2_log_type |= _ISL_LOG_TYPE_FUNC ;
        }

        ps ++ ;
    }

    ipts_set_log_type(i2_log_type) ;

    return NAVR_OK ;
}

static INT32 _ipts_list_source_cmd(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8           ui1_loop = 0;
    UINT8           ui1_isl_num = 0;
    INT32           i4_ret;
    ISL_REC_T       t_isl_iterate = {0};

    if (i4_argc != 1)
    {
        DBG_LOG_PRINT(("\n usage: list_source(isl)")) ;
        return NAVR_OK ;
    }
    
    i4_ret = a_isl_get_num_rec(&ui1_isl_num);
    
    for (ui1_loop = 0; ui1_loop < ui1_isl_num; ui1_loop++)
    {
        UTF16_T*        w2s_name;
        UTF16_T         w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
        CHAR            ac_elem_col1_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
        CHAR            ac_elem_col2_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1];

        i4_ret = a_isl_get_rec_by_idx(ui1_loop, &t_isl_iterate);

        c_memset (w2s_alias, 0, sizeof(w2s_alias));
        w2s_name = a_isl_get_display_name(&t_isl_iterate);
        a_isl_get_display_name_ex(&t_isl_iterate, w2s_alias, APP_CFG_CUSTOM_INP_NAME_LEN);

        c_uc_w2s_to_ps(w2s_name, ac_elem_col1_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        c_uc_w2s_to_ps(w2s_alias, ac_elem_col2_name, APP_CFG_CUSTOM_INP_NAME_LEN);

        DBG_LOG_PRINT(("input source ID: %d  input name: %s  alias name: %s\n", t_isl_iterate.ui1_id,ac_elem_col1_name,ac_elem_col2_name));
    }

    return NAVR_OK ;
}
/*-----------------------------------------------------------------------------
 * Name banner_cli_init
 *
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 ipts_cli_init(VOID)
{
    return nav_register_comp_cli_entry(&t_g_ipts_entry) ;
}


/*-----------------------------------------------------------------------------
                    export function implementations
-----------------------------------------------------------------------------*/

#endif /* CLI_SUPPORT */


