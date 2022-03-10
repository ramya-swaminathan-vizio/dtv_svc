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
 * $RCSfile: ulpk.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_WR_UPDATER_UI_SUPPORT
#ifdef APP_537X_SUPPORT
#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "u_irrc_btn_def.h"
#include "u_fm.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "u_drv_cust.h"

#include "app_util/a_cfg.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "nav/a_navigator.h"
#include "nav/nav_common.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/dev_db/a_dev_db_custom.h"
#include "nav/wr_updater/wr_updater.h"
#include "wizard/a_wzd.h"
#include "res/nav/nav_dbg.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#if 0
#define TIME_OUT_FOR_START_SETUP_UI      (30000)
#endif
#define TIME_OUT_FOR_RESULT_UI           (10000)

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_WR_UPDATER_T t_g_nav_wr_updater;

#ifdef CLI_SUPPORT
typedef struct _NAV_DEV_DB_T
{
    /*dev type info*/
    DEV_DB_TYPE_T                    t_dev_type[DEV_DB_MAX_DEV_TYPE_CONT];
    UINT32                           ui4_type_num;
    UINT32                           ui4_type_sel_idx;
    BOOL                             b_is_type_sel;

    /* brand info of this view*/
    DEV_DB_BRMD_T                    t_brd_info[DEV_DB_DUL_OP_MAX];
    CHAR                             c_brd_pfx[DEV_DB_NAME_LEN_MAX + 1];
    UINT32                           ui4_brd_notify_count;
    UINT32                           ui4_brd_num;
    UINT32                           ui4_brd_sel_idx;
    BOOL                             b_is_brd_sel;

    /* model info of this view*/
    DEV_DB_BRMD_T                    t_mdl_info[DEV_DB_DUL_OP_MAX];
    CHAR                             c_mdl_pfx[DEV_DB_NAME_LEN_MAX + 1];
    UINT32                           ui4_mdl_notify_count;
    UINT32                           ui4_mdl_num;
    UINT32                           ui4_mdl_sel_idx;
    BOOL                             b_is_mdl_sel;

    /* codeset info*/
    DEV_DB_CODESET_T*                pt_codeset;
    DEV_DB_CODESET_LIST_T*           pt_codeset_list;

    /* the glob init info*/
    BOOL                             b_is_dev_db_init;
    BOOL                             b_online_reg;
    UINT32                           ui4_nfy_id;

} NAV_DEV_DB_T;

static NAV_DEV_DB_T t_g_nav_dev_db;

static INT32 _nav_wr_updater_cli_active
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_wr_updater_cli_reset_ui_status
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_wr_updater_cli_set_complete_flag
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_wr_updater_cli_set_wifi_remote_paired_flag
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_wr_updater_cli_set_wifi_remote_unpair_flag
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_dev_db_cli_init
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_dev_db_cli_reg_online_query
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_dev_db_cli_unreg_online_query
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_dev_db_cli_get_dev_type
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_dev_db_cli_get_brand_type
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_dev_db_cli_get_mdl
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_dev_db_cli_update_codeset_list
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_dev_db_cli_list_dev_type
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_dev_db_cli_list_brd
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_dev_db_cli_list_mdl
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_dev_db_cli_list_codeset
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);


static INT32 _nav_dev_db_cli_sel_dev_type
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_dev_db_cli_sel_brd
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_dev_db_cli_sel_mdl
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_dev_db_cli_upload_codeset
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_dev_db_cli_download_codeset
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_dev_db_cli_save_and_upload_codeset
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_dev_db_cli_clean_codeset_list
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);


static INT32 _nav_dev_db_cli_reset_query
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_dev_db_cli_manual_upload_codeset
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);


static CLI_EXEC_T at_g_nav_dev_db_cli_cmd_tbl[] =
{
    { "dbinit",                   "dbi",  _nav_dev_db_cli_init,                                   NULL, "dev db init",                                  NAV_CLI_ACCESS_RIGHT_LVL },
    { "dbregonline",              "rgo",  _nav_dev_db_cli_reg_online_query,                       NULL, "register online query",                        NAV_CLI_ACCESS_RIGHT_LVL },
    { "dbunregonline",            "urgo", _nav_dev_db_cli_unreg_online_query,                     NULL, "unregister online query",                      NAV_CLI_ACCESS_RIGHT_LVL },
    { "gdtype",                   "gt",   _nav_dev_db_cli_get_dev_type,                           NULL, "get dev type",                                 NAV_CLI_ACCESS_RIGHT_LVL },
    { "gdbrand",                  "gb",   _nav_dev_db_cli_get_brand_type,                         NULL, "get dev brand",                                NAV_CLI_ACCESS_RIGHT_LVL },
    { "gdmodel",                  "gm",   _nav_dev_db_cli_get_mdl,                                NULL, "get dev model",                                NAV_CLI_ACCESS_RIGHT_LVL },
    { "ldtype",                   "lt",   _nav_dev_db_cli_list_dev_type,                          NULL, "list dev type",                                NAV_CLI_ACCESS_RIGHT_LVL },
    { "ldbrand",                  "lb",   _nav_dev_db_cli_list_brd,                               NULL, "list dev brand",                               NAV_CLI_ACCESS_RIGHT_LVL },
    { "ldmodel",                  "lm",   _nav_dev_db_cli_list_mdl,                               NULL, "list dev model",                               NAV_CLI_ACCESS_RIGHT_LVL },
    { "sdtype",                   "st",   _nav_dev_db_cli_sel_dev_type,                           NULL, "select dev type",                              NAV_CLI_ACCESS_RIGHT_LVL },
    { "sdbrand",                  "sb",   _nav_dev_db_cli_sel_brd,                                NULL, "select brand",                                 NAV_CLI_ACCESS_RIGHT_LVL },
    { "sdmodel",                  "sm",   _nav_dev_db_cli_sel_mdl,                                NULL, "select model",                                 NAV_CLI_ACCESS_RIGHT_LVL },
    { "dcodeset",                 "dc",   _nav_dev_db_cli_download_codeset,                       NULL, "download codeset",                             NAV_CLI_ACCESS_RIGHT_LVL },
    { "ucodeset",                 "uc",   _nav_dev_db_cli_upload_codeset,                         NULL, "upload codeset",                               NAV_CLI_ACCESS_RIGHT_LVL },
    { "resetquery",               "rq",   _nav_dev_db_cli_reset_query,                            NULL, "reset the query",                              NAV_CLI_ACCESS_RIGHT_LVL },
    { "updatecodesetlist",        "ucl",  _nav_dev_db_cli_update_codeset_list,                    NULL, "update codeset list",                          NAV_CLI_ACCESS_RIGHT_LVL },
    { "listcodeset",              "lc",   _nav_dev_db_cli_list_codeset,                           NULL, "list codeset",                                 NAV_CLI_ACCESS_RIGHT_LVL },
    { "saveuploadcodeset",        "suc",  _nav_dev_db_cli_save_and_upload_codeset,                NULL, "save upload codeset",                          NAV_CLI_ACCESS_RIGHT_LVL },
    { "cleancodesetlist",         "ccl",  _nav_dev_db_cli_clean_codeset_list,                     NULL, "clean codeset list",                           NAV_CLI_ACCESS_RIGHT_LVL },
    { "manualupcodeset",          "mus",  _nav_dev_db_cli_manual_upload_codeset,                  NULL, "manual upload codeset",                        NAV_CLI_ACCESS_RIGHT_LVL },
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_g_nav_wr_updater_cli_cmd_tbl[] =
{
    { "active_wr_updater",        "at",  _nav_wr_updater_cli_active,                              NULL, "active wr updater",                            NAV_CLI_ACCESS_RIGHT_LVL },
    { "set_status",               "s",   _nav_wr_updater_cli_reset_ui_status,                     NULL, "set the wr updater ui status",                 NAV_CLI_ACCESS_RIGHT_LVL },
    { "set_cmp",                  "h",   _nav_wr_updater_cli_set_complete_flag,                   NULL, "set the the updater complete flag",            NAV_CLI_ACCESS_RIGHT_LVL },
    { "set_paired",               "hp",  _nav_wr_updater_cli_set_wifi_remote_paired_flag,         NULL, "set the wifi remote paired flag",              NAV_CLI_ACCESS_RIGHT_LVL },
    { "set_unpair",               "hu",  _nav_wr_updater_cli_set_wifi_remote_unpair_flag,         NULL, "set the wifi remote unpair flag",              NAV_CLI_ACCESS_RIGHT_LVL },
    { "dev_db",                   "db",  NULL,                             at_g_nav_dev_db_cli_cmd_tbl, "set the wifi remote unpair flag",              NAV_CLI_ACCESS_RIGHT_LVL },
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T t_g_nav_wr_updater_cli_cmd_entry =
{
    "nav_wr_updater", NULL, NULL, at_g_nav_wr_updater_cli_cmd_tbl, "nav wr updater commands", NAV_CLI_ACCESS_RIGHT_LVL
};

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: _nav_wr_updater_cli_active
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_cli_active
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{

    nav_grab_activation(NAV_COMP_ID_WR_UPDATER);
    DBG_LOG_PRINT(("\nxxxx====cli active the wr updater ====xxxx\n"));

    return CLIR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _nav_wr_updater_cli_reset_ui_status
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_cli_reset_ui_status
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    nav_set_wr_updater_state(NAV_WR_UI_STATE_ID_NONE);
    DBG_LOG_PRINT(("\nxxxx====cli reset the wr updater ui status====xxxx\n"));

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_wr_updater_cli_set_complete_flag
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_cli_set_complete_flag
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    a_cfg_custom_set_updater_completed_flag(TRUE);
    DBG_LOG_PRINT(("\nxxxx====cli set the updater complete flag====xxxx\n"));

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_wr_updater_cli_set_complete_flag
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_cli_set_wifi_remote_paired_flag
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    a_cfg_custom_set_wifi_remote_pair_status(WIFI_REMOTE_PAIR_STATUS_PAIRED);
    DBG_LOG_PRINT(("\nxxxx====cli set the wifi remote paired flag====xxxx\n"));

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_wr_updater_cli_set_complete_flag
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_cli_set_wifi_remote_unpair_flag
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    a_cfg_custom_set_wifi_remote_pair_status(WIFI_REMOTE_PAIR_STATUS_UNPAIRED);
    DBG_LOG_PRINT(("\nxxxx====cli set wifi remote unpair flag====xxxx\n"));

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:_dev_db_cli_reset_brand_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_cli_reset_brand_info(VOID)
{
    UINT32          ui4_idx   = 0;
    NAV_DEV_DB_T*   pt_g_nav_dev_db = &t_g_nav_dev_db;

    for (ui4_idx = 0; ui4_idx < DEV_DB_DUL_OP_MAX; ui4_idx ++)
    {
        /* init the brand info*/
        c_memset(&(pt_g_nav_dev_db->t_brd_info[ui4_idx]),0,sizeof (DEV_DB_BRMD_T));
        pt_g_nav_dev_db->t_brd_info[ui4_idx].i4_local1_idx  = -1;
        pt_g_nav_dev_db->t_brd_info[ui4_idx].i4_online1_idx = -1;
        pt_g_nav_dev_db->t_brd_info[ui4_idx].i4_local2_idx  = -1;
        pt_g_nav_dev_db->t_brd_info[ui4_idx].i4_online2_idx = -1;
    }

    for (ui4_idx = 0; ui4_idx < DEV_DB_NAME_LEN_MAX + 1; ui4_idx ++)
    {
        pt_g_nav_dev_db->c_brd_pfx[ui4_idx] = '\0';
    }

    /* init the brand num*/

    pt_g_nav_dev_db->ui4_brd_notify_count       = 0;
    pt_g_nav_dev_db->ui4_brd_num       = 0;
    pt_g_nav_dev_db->ui4_brd_sel_idx   = 0;
    pt_g_nav_dev_db->b_is_brd_sel      = FALSE;
    return DEV_DBR_OK;

}

/*-----------------------------------------------------------------------------
 * Name:_dev_db_cli_reset_mdl_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _dev_db_cli_reset_mdl_info(VOID)
{
    UINT32          ui4_idx   = 0;
    NAV_DEV_DB_T*   pt_g_nav_dev_db = &t_g_nav_dev_db;

    for (ui4_idx = 0; ui4_idx < DEV_DB_DUL_OP_MAX; ui4_idx ++)
    {
        /* init the model info*/
        c_memset(&(pt_g_nav_dev_db->t_mdl_info[ui4_idx]),0,sizeof (DEV_DB_BRMD_T));
        pt_g_nav_dev_db->t_mdl_info[ui4_idx].i4_local1_idx  = -1;
        pt_g_nav_dev_db->t_mdl_info[ui4_idx].i4_online1_idx = -1;
        pt_g_nav_dev_db->t_mdl_info[ui4_idx].i4_local2_idx  = -1;
        pt_g_nav_dev_db->t_mdl_info[ui4_idx].i4_online2_idx = -1;
    }

    for (ui4_idx = 0; ui4_idx < DEV_DB_NAME_LEN_MAX + 1; ui4_idx ++)
    {
        pt_g_nav_dev_db->c_mdl_pfx[ui4_idx] = '\0';
    }

    /* init the model num*/

    pt_g_nav_dev_db->ui4_mdl_notify_count       = 0;
    pt_g_nav_dev_db->ui4_mdl_num       = 0;
    pt_g_nav_dev_db->ui4_mdl_sel_idx   = 0;
    pt_g_nav_dev_db->b_is_mdl_sel      = FALSE;
    return DEV_DBR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _dev_db_online_query_hdlr
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _dev_db_online_query_hdlr(
    VOID*                               pv_tag1,
    VOID*                               pv_tag2,
    VOID*                               pv_tag3)
{
    DEV_DB_BMC_QUERY_T*      pt_tag_query_info     = (DEV_DB_BMC_QUERY_T*)((UINT32)(pv_tag2));
    NAV_DEV_DB_T*            pt_g_nav_dev_db       = &t_g_nav_dev_db;
    INT32    i4_ret;

    if ((DEV_DB_THREAD_QUERY_BRAND != pt_tag_query_info->e_query_type)
        && (DEV_DB_THREAD_QUERY_MODEL != pt_tag_query_info->e_query_type)
        && (DEV_DB_THREAD_QUERY_CODESET != pt_tag_query_info->e_query_type)
        && (DEV_DB_THREAD_QUERY_CODESET_WITH_BRD != pt_tag_query_info->e_query_type))
    {
        ///i4_ret = a_dev_db_reset_brmd_tag_info(pt_tag_brand);
        ///c_dbg_secure_stmt("[nav_dev_db] a_dev_db_reset_brmd_tag_info(), i4_ret[%d]!\n",i4_ret);
        /* here should reset the query info*/
        return;
    }


    if (DEV_DB_THREAD_QUERY_BRAND == pt_tag_query_info->e_query_type)
    {
        if ((FALSE == pt_g_nav_dev_db->b_is_brd_sel)
            && (0 == c_strcmp(pt_g_nav_dev_db->c_brd_pfx,pt_tag_query_info->s_brd_prefix))
            && (pt_tag_query_info->ui4_notify_count != pt_g_nav_dev_db->ui4_brd_notify_count))
        {
            i4_ret = a_dev_db_get_brand_list(pt_g_nav_dev_db->t_brd_info,
                                    (UINT32*)(&(pt_g_nav_dev_db->ui4_brd_num)),
                                    pt_g_nav_dev_db->c_brd_pfx);

            DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_get_brand_list()--->ONLINE, i4_ret[%d]!\n",i4_ret));
            pt_g_nav_dev_db->ui4_brd_notify_count = pt_tag_query_info->ui4_notify_count;
        }

        if (pt_tag_query_info->b_is_to_clean)
        {

            DBG_LOG_PRINT(("[nav_dev_db] clean slot[%d]!\n",pt_tag_query_info->ui4_task_idx));
            a_dev_db_reset_bmc_query_info(pt_tag_query_info);
        }
    }

    if (DEV_DB_THREAD_QUERY_MODEL == pt_tag_query_info->e_query_type)
    {
        if ((FALSE == pt_g_nav_dev_db->b_is_mdl_sel)
            && (0 == c_strcmp(pt_g_nav_dev_db->c_mdl_pfx,pt_tag_query_info->s_mdl_prefix))
            && (pt_tag_query_info->ui4_notify_count != pt_g_nav_dev_db->ui4_mdl_notify_count))
        {
            i4_ret = a_dev_db_get_model_list(pt_g_nav_dev_db->t_mdl_info,
                                                   (UINT32*)(&(pt_g_nav_dev_db->ui4_mdl_num)),
                                                   pt_g_nav_dev_db->c_mdl_pfx);

            DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_get_model_list()--->ONLINE, i4_ret[%d]!\n",i4_ret));

            pt_g_nav_dev_db->ui4_mdl_notify_count = pt_tag_query_info->ui4_notify_count;
        }

        if (pt_tag_query_info->b_is_to_clean)
        {
            a_dev_db_reset_bmc_query_info(pt_tag_query_info);
        }
    }


    if (DEV_DB_THREAD_QUERY_CODESET == pt_tag_query_info->e_query_type)
    {
       i4_ret = a_dev_db_get_codeset(&(pt_g_nav_dev_db->pt_codeset));


        DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_get_codeset(), i4_ret[%d]!\n",i4_ret));

        a_dev_db_reset_bmc_query_info(pt_tag_query_info);
    }


    if (DEV_DB_THREAD_QUERY_CODESET_WITH_BRD == pt_tag_query_info->e_query_type)
    {
       i4_ret = a_dev_db_get_codeset_list(&(pt_g_nav_dev_db->pt_codeset_list));


        DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_get_codeset_list(), i4_ret[%d]!\n",i4_ret));

        a_dev_db_reset_bmc_query_info(pt_tag_query_info);
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _dev_db_online_query
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID  _dev_db_online_query(VOID* pv_tag, VOID* pv_nfy_param)
{

    /*post a message to itself*/
    nav_request_context_switch(_dev_db_online_query_hdlr,
                               (VOID*)pv_tag,
                               (VOID*)pv_nfy_param,
                               NULL);
    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_init
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32    i4_ret;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    if (pt_g_nav_dev_db->b_is_dev_db_init)
    {
        DBG_LOG_PRINT(("[nav_dev_db] the dev db alread init\n"));
        return CLIR_OK;
    }

    DBG_LOG_PRINT(("[nav_dev_db] _nav_dev_db_cli_init()\n"));
    i4_ret = a_dev_db_init();
    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_init() i4_ret=%d\n",i4_ret));
    c_memset(pt_g_nav_dev_db,0,sizeof(NAV_DEV_DB_T));

    _dev_db_cli_reset_brand_info();
    _dev_db_cli_reset_mdl_info();
    pt_g_nav_dev_db->pt_codeset = NULL;

    i4_ret = a_dev_db_register( _dev_db_online_query,(VOID*) pt_g_nav_dev_db, &(pt_g_nav_dev_db->ui4_nfy_id) );
    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_register() i4_ret=%d\n",i4_ret));

    pt_g_nav_dev_db->b_is_dev_db_init = TRUE;
    pt_g_nav_dev_db->b_online_reg = TRUE;

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_reg_online_query
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_reg_online_query
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32    i4_ret;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    if (TRUE != pt_g_nav_dev_db->b_is_dev_db_init)
    {
        DBG_LOG_PRINT(("[nav_dev_db] the dev db have not init\n"));
        return CLIR_OK;
    }

    if (TRUE == pt_g_nav_dev_db->b_online_reg)
    {
        DBG_LOG_PRINT(("[nav_dev_db] the dev db online query have alread reg!!\n"));
        return CLIR_OK;
    }

    i4_ret = a_dev_db_register( _dev_db_online_query,(VOID*) pt_g_nav_dev_db, &(pt_g_nav_dev_db->ui4_nfy_id) );
    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_register() i4_ret=%d\n",i4_ret));

    pt_g_nav_dev_db->b_online_reg = TRUE;
    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_unreg_online_query
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_unreg_online_query
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32    i4_ret;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    if (TRUE != pt_g_nav_dev_db->b_is_dev_db_init)
    {
        DBG_LOG_PRINT(("[nav_dev_db] the dev db have not init\n"));
        return CLIR_OK;
    }

    if (TRUE != pt_g_nav_dev_db->b_online_reg)
    {
        DBG_LOG_PRINT(("[nav_dev_db] the dev db online query have not reg!!\n"));
        return CLIR_OK;
    }

    i4_ret = a_dev_db_unregister( pt_g_nav_dev_db->ui4_nfy_id );
    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_unregister() i4_ret=%d\n",i4_ret));
    pt_g_nav_dev_db->b_online_reg = FALSE;
    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_reset_query
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_reset_query
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    if (FALSE == pt_g_nav_dev_db->b_is_dev_db_init)
    {
        DBG_LOG_PRINT(("[nav_dev_db] the dev db have not been init, please init it first!!\n"));
        return CLIR_OK;
    }

    pt_g_nav_dev_db->b_is_type_sel = FALSE;

    _dev_db_cli_reset_brand_info();
    _dev_db_cli_reset_mdl_info();

    DBG_LOG_PRINT(("[nav_dev_db] the dev db reset the query!!\n"));
    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_get_dev_type
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_get_dev_type
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32    i4_ret;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    DBG_LOG_PRINT(("[nav_dev_db] xxxx===_nav_dev_db_cli_get_dev_type() begin====xxxxx\n"));

    i4_ret = a_dev_db_update_dev_type(DEV_DB_DEV_TYPE_CTGY_ALL_DEV);
    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_update_dev_type() i4_ret=%d\n",i4_ret));

    i4_ret = a_dev_db_get_dev_type(pt_g_nav_dev_db->t_dev_type,&(pt_g_nav_dev_db->ui4_type_num));
    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_get_dev_type() i4_ret=%d\n",i4_ret));

    DBG_LOG_PRINT(("[nav_dev_db] xxxx===_nav_dev_db_cli_get_dev_type() end======xxxx\n"));

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_get_brand_type
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_get_brand_type
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32              i4_ret;
    CHAR               c_brand_prefix[DEV_DB_NAME_LEN_MAX + 1] = {0};
    NAV_DEV_DB_T*      pt_g_nav_dev_db     = &t_g_nav_dev_db;

    if (i4_argc > 2)
    {
        DBG_LOG_PRINT(("[nav_dev_db]parater error!\r\n"));
        return CLIR_OK;
    }

    /* reset the glob brand info*/
    _dev_db_cli_reset_brand_info();

    if ((FALSE == pt_g_nav_dev_db->b_is_type_sel)
        || (pt_g_nav_dev_db->ui4_type_sel_idx >= pt_g_nav_dev_db->ui4_type_num))
    {
        DBG_LOG_PRINT(("[nav_dev_db]the dev type have not been seleted, should select the dev type firest!\r\n"));
        return CLIR_OK;
    }

    if (i4_argc == 1)
    {
        /* do nothing*/
    }
    else
    {
        c_strncpy(c_brand_prefix, pps_argv[1], DEV_DB_NAME_LEN_MAX);
    }

    /* set the glob query prefix for brand*/
    c_strncpy(pt_g_nav_dev_db->c_brd_pfx, c_brand_prefix, DEV_DB_NAME_LEN_MAX);

    i4_ret = a_dev_db_update_brand_info(pt_g_nav_dev_db->ui4_type_sel_idx,
                                      pt_g_nav_dev_db->t_dev_type[pt_g_nav_dev_db->ui4_type_sel_idx],
                                      c_brand_prefix);


    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_update_brand_info(), i4_ret[%d]!\n",i4_ret));
#if 0

    i4_ret = a_dev_db_get_brand_list(pt_g_nav_dev_db->t_brd_info,
                            (UINT32*)(&(pt_g_nav_dev_db->ui4_brd_num)),
                            c_brand_prefix);
#endif

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_get_mdl
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_get_mdl
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32              i4_ret;
    CHAR               c_model_prefix[DEV_DB_NAME_LEN_MAX + 1] = {0};
    NAV_DEV_DB_T*      pt_g_nav_dev_db                         = &t_g_nav_dev_db;

    if (i4_argc > 2)
    {
        DBG_LOG_PRINT(("[nav_dev_db]parater error!\r\n"));
        return CLIR_OK;
    }

    /* reset the glob model info */
    _dev_db_cli_reset_mdl_info();

    if ((FALSE == pt_g_nav_dev_db->b_is_type_sel)
        || (FALSE == pt_g_nav_dev_db->b_is_brd_sel)
        || (pt_g_nav_dev_db->ui4_brd_sel_idx >= pt_g_nav_dev_db->ui4_brd_num))
    {
        DBG_LOG_PRINT(("[nav_dev_db]the dev type have not been seleted, should select the dev type firest!\r\n"));
        return CLIR_OK;
    }

    if (i4_argc == 1)
    {
        /* do nothing*/
    }
    else
    {
        c_strncpy(c_model_prefix, pps_argv[1], DEV_DB_NAME_LEN_MAX);
    }

    c_strncpy(pt_g_nav_dev_db->c_mdl_pfx, c_model_prefix, DEV_DB_NAME_LEN_MAX);

    i4_ret = a_dev_db_update_model_info(pt_g_nav_dev_db->ui4_type_sel_idx,
                                      pt_g_nav_dev_db->t_dev_type[pt_g_nav_dev_db->ui4_type_sel_idx],
                                      pt_g_nav_dev_db->t_brd_info[pt_g_nav_dev_db->ui4_brd_sel_idx],
                                      pt_g_nav_dev_db->t_brd_info[pt_g_nav_dev_db->ui4_brd_sel_idx].s_src_name,
                                      c_model_prefix);

    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_update_model_info(), i4_ret[%d]!\n",i4_ret));
#if 0

    i4_ret = a_dev_db_get_model_list(pt_g_nav_dev_db->t_mdl_info,
                                           (UINT32*)(&(pt_g_nav_dev_db->ui4_mdl_num)),
                                           c_model_prefix);
#endif

    return CLIR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_list_dev_type
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_list_dev_type
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT32   ui4_idx = 0;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    DBG_LOG_PRINT(("[nav_dev_db] dev_type_num=%d,b_sel=%d,sel_idx=%d\n",
                pt_g_nav_dev_db->ui4_type_num,
                pt_g_nav_dev_db->b_is_type_sel,
                pt_g_nav_dev_db->ui4_type_sel_idx));

    DBG_LOG_PRINT(("[nav_dev_db] xxxx=== dev type list begin====xxxxx\n"));

    for (ui4_idx = 0; ui4_idx < pt_g_nav_dev_db->ui4_type_num; ui4_idx ++)
    {
        DBG_LOG_PRINT(("[nav_dev_db] type_item_idx[%-3d]---> view_name[%-20s] , sa_name[%-20s] , sa_idx[%-3d] ,  sb_name[%-20s] ,  sb_idx[%-3d]\n",
                    ui4_idx,
                    pt_g_nav_dev_db->t_dev_type[ui4_idx].s_dev_view_name,
                    pt_g_nav_dev_db->t_dev_type[ui4_idx].s_deva_src_name,
                    pt_g_nav_dev_db->t_dev_type[ui4_idx].i4_deva_src_idx,
                    pt_g_nav_dev_db->t_dev_type[ui4_idx].s_devb_src_name,
                    pt_g_nav_dev_db->t_dev_type[ui4_idx].i4_devb_src_idx));
    }

    DBG_LOG_PRINT(("[nav_dev_db] xxxx=== dev type list end======xxxx\n"));

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_list_brd
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_list_brd
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT32   ui4_idx              = 0;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    DBG_LOG_PRINT(("[nav_dev_db] brd_num[%d],b_sel[%d],sel_idx[%d]\n",
                pt_g_nav_dev_db->ui4_brd_num,
                pt_g_nav_dev_db->b_is_brd_sel,
                pt_g_nav_dev_db->ui4_brd_sel_idx));

    DBG_LOG_PRINT(("[nav_dev_db] xxxx===brand info list begin====xxxxx\n"));

    for (ui4_idx = 0; ui4_idx < pt_g_nav_dev_db->ui4_brd_num; ui4_idx ++)
    {
        DBG_LOG_PRINT(("[nav_dev_db] brd_item_idx[%-3d]---> brd_name[%-20s] , brd_local1[%-3d] , brd_online1[%-3d] , brd_local2[%-3d] , brd_online2[%-3d]\n",
                    ui4_idx,
                    pt_g_nav_dev_db->t_brd_info[ui4_idx].s_src_name,
                    pt_g_nav_dev_db->t_brd_info[ui4_idx].i4_local1_idx,
                    pt_g_nav_dev_db->t_brd_info[ui4_idx].i4_online1_idx,
                    pt_g_nav_dev_db->t_brd_info[ui4_idx].i4_local2_idx,
                    pt_g_nav_dev_db->t_brd_info[ui4_idx].i4_online2_idx));
    }

    DBG_LOG_PRINT(("[nav_dev_db] xxxx===brand info list end======xxxx\n"));

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_list_mdl
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_list_mdl
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT32   ui4_idx              = 0;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    DBG_LOG_PRINT(("[nav_dev_db] mdl_num[%d],b_sel[%d],sel_idx[%d]\n",
                pt_g_nav_dev_db->ui4_mdl_num,
                pt_g_nav_dev_db->b_is_mdl_sel,
                pt_g_nav_dev_db->ui4_mdl_sel_idx));

    DBG_LOG_PRINT(("[nav_dev_db] xxxx=== model info list begin====xxxxx\n"));

    for (ui4_idx = 0; ui4_idx < pt_g_nav_dev_db->ui4_mdl_num; ui4_idx ++)
    {
        DBG_LOG_PRINT(("[nav_dev_db] mdl_item_idx[%-3d]---> mdl_name[%-20s] , mdl_local1[%-3d] , mdl_online1[%-3d] , mdl_local2[%-3d] , mdl_online2[%-3d]\n",
                    ui4_idx,
                    pt_g_nav_dev_db->t_mdl_info[ui4_idx].s_src_name,
                    pt_g_nav_dev_db->t_mdl_info[ui4_idx].i4_local1_idx,
                    pt_g_nav_dev_db->t_mdl_info[ui4_idx].i4_online1_idx,
                    pt_g_nav_dev_db->t_mdl_info[ui4_idx].i4_local2_idx,
                    pt_g_nav_dev_db->t_mdl_info[ui4_idx].i4_online2_idx));
    }

    DBG_LOG_PRINT(("[nav_dev_db] xxxx=== model info list end======xxxx\n"));

    return CLIR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_list_codeset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_list_codeset
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT32   ui4_idx              = 0;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    DBG_LOG_PRINT(("[nav_dev_db] codesetlist1_num[%d],codesetlist2_num[%d]\n",
                pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.i4_length,
                pt_g_nav_dev_db->pt_codeset_list->t_codeset_list2.i4_length));

    DBG_LOG_PRINT(("[nav_dev_db] xxxx=== model info list begin====xxxxx\n"));
     /* for codeset list1*/
    for (ui4_idx = 0; ui4_idx < pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.i4_length; ui4_idx ++)
    {
        if (NULL != pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.p_list[ui4_idx])
        {
            DBG_LOG_PRINT(("[nav_dev_db] codeset_idx[%-3d]---> codeset[%-20s]\n",
                        ui4_idx,
                        pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.p_list[ui4_idx]));
        }
    }


    /* for codeset list2*/
    for (ui4_idx = 0; ui4_idx < pt_g_nav_dev_db->pt_codeset_list->t_codeset_list2.i4_length; ui4_idx ++)
    {
        if (NULL != pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.p_list[ui4_idx])
        {
            DBG_LOG_PRINT(("[nav_dev_db] codeset_idx[%-3d]---> codeset[%-20s]\n",
                        ui4_idx + pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.i4_length,
                        pt_g_nav_dev_db->pt_codeset_list->t_codeset_list2.p_list[ui4_idx]));
        }
    }

    DBG_LOG_PRINT(("[nav_dev_db] xxxx=== model info list end======xxxx\n"));

    return CLIR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_list_codeset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_save_and_upload_codeset
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT32   ui4_sel              = 0;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;
    INT32        i4_ret;

    if (i4_argc != 2) {
        DBG_LOG_PRINT(("[nav_dev_db]parater error!\r\n"));
        return CLIR_OK;
    }

    ui4_sel = nav_atoi(pps_argv[1]);

    if (ui4_sel >= (pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.i4_length + pt_g_nav_dev_db->pt_codeset_list->t_codeset_list2.i4_length))
    {
        DBG_LOG_PRINT(("[nav_dev_db]the index for codeset should not more then [%d]\n",
                   pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.i4_length + pt_g_nav_dev_db->pt_codeset_list->t_codeset_list2.i4_length));
    }
    else
    {


        DBG_LOG_PRINT(("[nav_dev_db] xxxx===_nav_dev_db_cli_save_and_upload_codeset() begin====xxxxx\n"));

        DBG_LOG_PRINT(("[nav_dev_db] the codeset select idx[%d]\n",ui4_sel));

        if (ui4_sel >= pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.i4_length)
        {
            if (NULL != pt_g_nav_dev_db->pt_codeset_list->t_codeset_list2.p_list[ui4_sel - pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.i4_length])
            {
                i4_ret = a_dev_db_save_codeset(pt_g_nav_dev_db->pt_codeset_list->t_codeset_list2.p_list[ui4_sel - pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.i4_length]);
                DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_save_codeset() return[%d]\n",i4_ret));

                i4_ret = a_dev_db_upload_codeset_ex(pt_g_nav_dev_db->pt_codeset_list->t_codeset_list2.p_list[ui4_sel - pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.i4_length]);
                DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_upload_codeset_ex() return[%d]\n",i4_ret));

            }
        }
        else
        {
            if (NULL != pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.p_list[ui4_sel])
            {
                i4_ret = a_dev_db_save_codeset(pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.p_list[ui4_sel]);
                DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_save_codeset() return[%d]\n",i4_ret));


                i4_ret = a_dev_db_upload_codeset_ex(pt_g_nav_dev_db->pt_codeset_list->t_codeset_list1.p_list[ui4_sel]);
                DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_upload_codeset_ex() return[%d]\n",i4_ret));
            }
        }
        DBG_LOG_PRINT(("[nav_dev_db] xxxx===_nav_dev_db_cli_save_and_upload_codeset() end======xxxx\n"));
    }

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_clean_codeset_list
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_clean_codeset_list
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32        i4_ret;

    i4_ret = a_dev_db_clean_codeset_list();

    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_clean_codeset_list() return[%d]\n",i4_ret));

    return CLIR_OK;
}




/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_sel_dev_type
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_sel_dev_type
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT32   ui4_sel              = 0;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    if (i4_argc != 2) {
        DBG_LOG_PRINT(("[nav_dev_db]parater error!\r\n"));
        return CLIR_OK;
    }

    ui4_sel = nav_atoi(pps_argv[1]);

    if (ui4_sel >= pt_g_nav_dev_db->ui4_type_num)
    {
        DBG_LOG_PRINT(("[nav_dev_db]the index for dev type should not more then [%d]\n",
                   pt_g_nav_dev_db->ui4_type_num));
    }
    else
    {

        DBG_LOG_PRINT(("[nav_dev_db] xxxx===_nav_dev_db_cli_get_dev_type() begin====xxxxx\n"));

        pt_g_nav_dev_db->b_is_type_sel = TRUE;
        pt_g_nav_dev_db->ui4_type_sel_idx = ui4_sel;

        DBG_LOG_PRINT(("[nav_dev_db] the dev type is selected and the select idx[%d]\n",pt_g_nav_dev_db->ui4_type_sel_idx));

        DBG_LOG_PRINT(("[nav_dev_db] xxxx===_nav_dev_db_cli_get_dev_type() end======xxxx\n"));
    }

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_sel_brd
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_sel_brd
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT32   ui4_sel              = 0;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    if (i4_argc != 2) {
        DBG_LOG_PRINT(("[nav_dev_db]parater error!\r\n"));
        return CLIR_OK;
    }

    ui4_sel = nav_atoi(pps_argv[1]);

    if (ui4_sel >= pt_g_nav_dev_db->ui4_brd_num)
    {
        DBG_LOG_PRINT(("[nav_dev_db]the index for dev type should not more then [%d]\n",
                    pt_g_nav_dev_db->ui4_brd_num));
    }
    else
    {
        pt_g_nav_dev_db->b_is_brd_sel = TRUE;
        pt_g_nav_dev_db->ui4_brd_sel_idx = ui4_sel;

        DBG_LOG_PRINT(("[nav_dev_db] the dev type is selected and the select idx[%d]\n",pt_g_nav_dev_db->ui4_brd_sel_idx));
    }

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_sel_mdl
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_sel_mdl
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT32   ui4_sel              = 0;
    NAV_DEV_DB_T* pt_g_nav_dev_db = &t_g_nav_dev_db;

    if (i4_argc != 2) {
        DBG_LOG_PRINT(("[nav_dev_db]parater error!\r\n"));
        return CLIR_OK;
    }

    ui4_sel = nav_atoi(pps_argv[1]);

    if (ui4_sel >= pt_g_nav_dev_db->ui4_mdl_num)
    {
        DBG_LOG_PRINT(("[nav_dev_db]the index for dev type should not more then [%d]\n",
                    pt_g_nav_dev_db->ui4_mdl_num));
    }
    else
    {
        pt_g_nav_dev_db->b_is_mdl_sel    = TRUE;
        pt_g_nav_dev_db->ui4_mdl_sel_idx = ui4_sel;

        DBG_LOG_PRINT(("[nav_dev_db] the dev type is selected and the select idx[%d]\n",pt_g_nav_dev_db->ui4_mdl_sel_idx));
    }

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_download_upload_codeset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_download_codeset
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32              i4_ret;
    NAV_DEV_DB_T*      pt_g_nav_dev_db            = &t_g_nav_dev_db;

    if (FALSE == pt_g_nav_dev_db->b_is_mdl_sel)
    {
        DBG_LOG_PRINT(("[nav_dev_db]model info have not select, please select it first!\r\n"));
        return CLIR_OK;
    }

    i4_ret = a_dev_db_update_codeset(pt_g_nav_dev_db->ui4_type_sel_idx,
                            pt_g_nav_dev_db->t_dev_type[pt_g_nav_dev_db->ui4_type_sel_idx],
                            pt_g_nav_dev_db->t_brd_info[pt_g_nav_dev_db->ui4_brd_sel_idx],
                            pt_g_nav_dev_db->t_mdl_info[pt_g_nav_dev_db->ui4_mdl_sel_idx],
                            pt_g_nav_dev_db->t_brd_info[pt_g_nav_dev_db->ui4_brd_sel_idx].s_src_name,
                            pt_g_nav_dev_db->t_mdl_info[pt_g_nav_dev_db->ui4_mdl_sel_idx].s_src_name);

    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_update_codeset(), i4_ret[%d]!\n",i4_ret));

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_update_codeset_list
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_update_codeset_list
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32              i4_ret;
    NAV_DEV_DB_T*      pt_g_nav_dev_db            = &t_g_nav_dev_db;

    if (FALSE == pt_g_nav_dev_db->b_is_brd_sel)
    {
        DBG_LOG_PRINT(("[nav_dev_db]brand info have not select, please select it first!\r\n"));
        return CLIR_OK;
    }

    i4_ret = a_dev_db_update_codeset_with_brand(pt_g_nav_dev_db->ui4_type_sel_idx,
                            pt_g_nav_dev_db->t_dev_type[pt_g_nav_dev_db->ui4_type_sel_idx],
                            pt_g_nav_dev_db->t_brd_info[pt_g_nav_dev_db->ui4_brd_sel_idx],
                            pt_g_nav_dev_db->t_brd_info[pt_g_nav_dev_db->ui4_brd_sel_idx].s_src_name);

    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_update_codeset_with_brand(), i4_ret[%d]!\n",i4_ret));

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_download_upload_codeset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_upload_codeset
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32              i4_ret;
    NAV_DEV_DB_T*      pt_g_nav_dev_db            = &t_g_nav_dev_db;

    if (FALSE == pt_g_nav_dev_db->b_is_mdl_sel)
    {
        DBG_LOG_PRINT(("[nav_dev_db]model info have not select, please select it first!\r\n"));
        return CLIR_OK;
    }

    i4_ret = a_dev_db_upload_codeset(pt_g_nav_dev_db->pt_codeset);
    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_upload_codeset(), i4_ret[%d]!\n",i4_ret));

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_cli_manual_upload_codeset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_cli_manual_upload_codeset
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32            i4_ret;
    CHAR             s_codeset[DEV_DB_CODESET_LEN_MAX];
    SIZE_T           z_size;
    UINT32           ui4_index;
    NAV_DEV_DB_T*    pt_g_nav_dev_db            = &t_g_nav_dev_db;

    if (i4_argc != 2) {
        DBG_LOG_PRINT(("[nav_dev_db]parater error!\r\n"));
        return CLIR_OK;
    }

    z_size = c_strlen(pps_argv[1]);

    if (z_size < DEV_DB_CODESET_CHAR_NUM_LEN)
    {
        DBG_LOG_PRINT(("[nav_dev_db]parater[2] len should be more then 4!\r\n"));
        return CLIR_OK;
    }

    for (ui4_index = 0; ui4_index < DEV_DB_CODESET_CHAR_NUM_LEN; ui4_index ++)
    {
        s_codeset[ui4_index] = pps_argv[1][ui4_index];
    }

    i4_ret = a_dev_db_manual_upload_codeset(pt_g_nav_dev_db->ui4_type_sel_idx,
                                            s_codeset,
                                            DEV_DB_CODESET_LEN_MAX);

    DBG_LOG_PRINT(("[nav_dev_db] a_dev_db_manual_upload_codeset(), i4_ret[%d],s_codeset[%s]!\n",i4_ret,s_codeset));

    return CLIR_OK;
}

#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_wr_updater_stop_timer(
                    NAV_WR_UPDATER_T*                pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop wr_updater::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    NAV_WR_UPDATER_T* pt_this = &t_g_nav_wr_updater;
    INT32       i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    pt_this->h_hide_timer  = NULL_HANDLE;
    pt_this->t_wr_ui_state = NAV_WR_UI_STATE_ID_NONE;
    pt_this->b_is_on       = FALSE;

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = pt_this->t_view_hdlr.pf_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset
                    );


#ifdef CLI_SUPPORT
            nav_register_comp_cli_entry (&t_g_nav_wr_updater_cli_cmd_entry);
#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_deinit(VOID)
{
    NAV_WR_UPDATER_T* pt_this = &t_g_nav_wr_updater;
    INT32             i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    i4_ret = pt_this->t_view_hdlr.pf_deinit();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    pt_this->h_hide_timer  = NULL_HANDLE;
    pt_this->t_wr_ui_state = NAV_WR_UI_STATE_ID_NONE;
    pt_this->b_is_on       = FALSE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_wr_updater_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_WR_UPDATER_T* pt_this = &t_g_nav_wr_updater;

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_ANY_UI) == TRUE) {
        return FALSE;
    }

    return pt_this->t_view_hdlr.pf_is_key_handler(ui4_key_code);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 _nav_wr_updater_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_WR_UPDATER_T*     pt_this = &t_g_nav_wr_updater;
    NAV_WR_UI_STATE_ID_T  t_wr_updater_state = NAV_WR_UI_STATE_ID_NONE;
    INT32                 i4_ret;
    i4_ret = pt_this->t_view_hdlr.pf_activate(ui4_key_code);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    nav_get_wr_updater_state(&t_wr_updater_state);

    if (NAV_WR_UI_STATE_ID_START_SETUP == t_wr_updater_state)
    {
#if 0
        /* the timeout for the start setup dialog will assume to be 30s*/
        nav_wr_updater_reset_timer(
                        pt_this,
                        TIME_OUT_FOR_START_SETUP_UI
                        );
#endif
    }
    else
    {
        /* the timeout for the result dialog will assume to be 10s*/
        nav_wr_updater_reset_timer(
                        pt_this,
                        TIME_OUT_FOR_RESULT_UI
                        );
    }

    nav_grab_activation(NAV_COMP_ID_WR_UPDATER);
    nav_set_component_visible(NAV_COMP_ID_WR_UPDATER);
    pt_this->b_is_on = TRUE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_APP_RESUMED:
        {
            NAV_WR_UI_STATE_ID_T  t_wr_updater_state = NAV_WR_UI_STATE_ID_NONE;
            nav_get_wr_updater_state(&t_wr_updater_state);

            if (NAV_WR_UI_STATE_ID_WR_UPDATER_SUCCESSFUL == t_wr_updater_state)
            {
                nav_grab_activation(NAV_COMP_ID_WR_UPDATER);
            }
            break;
        }
        default:
            break;
    }
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_hide(
                    VOID
                    )
{
    NAV_WR_UPDATER_T* pt_this = &t_g_nav_wr_updater;
    NAV_WR_UI_STATE_ID_T  t_wr_updater_state = NAV_WR_UI_STATE_ID_NONE;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    nav_get_wr_updater_state(&t_wr_updater_state);

    if (NAV_WR_UI_STATE_ID_WR_UPDATER_SUCCESSFUL == t_wr_updater_state)
    {
        /* reset the wr ui status*/
        nav_set_wr_updater_state(NAV_WR_UI_STATE_ID_NONE);
    }

    pt_this->t_view_hdlr.pf_hide();
    pt_this->b_is_on = FALSE;
    _nav_wr_updater_stop_timer(pt_this);
    nav_return_activation(NAV_COMP_ID_WR_UPDATER);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_wr_updater_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    /* execute in navigator's thread context */
    nav_hide_component(NAV_COMP_ID_WR_UPDATER);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_wr_updater_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_wr_updater_timeout_to_hide, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_wr_updater_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_wr_updater_reset_timer(
                    NAV_WR_UPDATER_T*                 pt_this,
                    UINT32                            ui4_timeout
                    )
{
    INT32 i4_ret;

    _nav_wr_updater_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _nav_wr_updater_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start wr_updater::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 *      nav_set_wr_updater_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

VOID nav_set_wr_updater_state(NAV_WR_UI_STATE_ID_T t_wr_updater_state)
{
    NAV_WR_UPDATER_T* pt_this = &t_g_nav_wr_updater;
    pt_this->t_wr_ui_state = t_wr_updater_state;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_get_wr_updater_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

VOID nav_get_wr_updater_state(NAV_WR_UI_STATE_ID_T* pt_wr_updater_state)
{
    NAV_WR_UPDATER_T* pt_this = &t_g_nav_wr_updater;
    *pt_wr_updater_state = pt_this->t_wr_ui_state;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_wr_updater_start_setup
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

VOID nav_wr_updater_start_setup(VOID)
{
/* just for deal with the ph2 ui dev branch build error and in the ph2 ui dev branch will not test this function*/
#if 0
    NAV_WR_UPDATER_T* pt_this = &t_g_nav_wr_updater;
    _nav_wr_updater_stop_timer(pt_this);

    /* set the start setup flag to eeprom*/
    a_cfg_custom_set_start_setup(WIFI_REMOTE_START_SETUP_ON);

    /* CALL THE API JUMP TO WIZARD PAGE*/

#ifdef APP_WIFI_REMOTE
    a_wzd_resume_tv_remote_pairing_setup();
#endif
#endif
}


/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_wr_updater_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_wr_updater_register(
                    NAV_WR_UPDATER_VIEW_HDLR_T*      pt_view_hdlr
                    )
{
    NAV_WR_UPDATER_T* pt_this = &t_g_nav_wr_updater;
    NAV_COMP_T        t_comp;
    INT32             i4_ret;

    c_memset (& t_comp, 0, sizeof(NAV_COMP_T));
    t_comp.pf_init           = _nav_wr_updater_init;
    t_comp.pf_deinit         = _nav_wr_updater_deinit;
    t_comp.pf_is_key_handler = _nav_wr_updater_is_key_handler;
    t_comp.pf_activate       = _nav_wr_updater_activate;
    t_comp.pf_inactivate     = _nav_wr_updater_inactivate;
    t_comp.pf_hide           = _nav_wr_updater_hide;
    t_comp.pf_handle_msg     = _nav_wr_updater_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_WR_UPDATER, &t_comp, COMP_EXEC_SET_WR_UPDATER);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (pt_view_hdlr == NULL) {
        nav_wr_updater_view_register_default_hdlr(&pt_this->t_view_hdlr);
    } else {
        pt_this->t_view_hdlr = *pt_view_hdlr;
    }

    return NAVR_OK;
}
#endif
#endif
