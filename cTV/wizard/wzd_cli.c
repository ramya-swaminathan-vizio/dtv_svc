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
 * $RCSfile: wzd_cli.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/13 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 0dc5e5894593d8bd6b2c6ecc9869c8fa $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"

#include "c_cli.h"
#include "c_os.h"

#include "app_util/a_cli_app.h"

#include "wizard/a_wzd.h"
#include "wizard/wzd.h"
#include "wizard/wzd_view.h"
#include "wizard/wzd_dbg.h"

/*
   Internal variable for stopping cli commands.
*/
static BOOL b_stop = TRUE;

/*
   Definitions
*/
#define NAV_SEL_DEFAULT_LOOP       1000000
#define NAV_SEL_DEFAULT_MAX_NAV    5
#define NAV_SEL_DEFAULT_MAX_SEL    10
#define NAV_SEL_DEFAULT_DELAY      500

#ifdef CLI_SUPPORT
/*-----------------------------------------------------------------------------
 * funcation declarations
 *---------------------------------------------------------------------------*/
static INT32  _atoi (const CHAR* ps);
static INT32  _wzd_cli_attach_cmd_tbl (VOID);
static INT32  _wzd_cli_resume_app (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _wzd_cli_nav_select (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _wzd_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _wzd_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _wzd_cli_create_dialog (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _wzd_cli_destroy_dialog (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _wzd_cli_page_goto (INT32 i4_argc, const CHAR** pps_argv);

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
/* command table */
static CLI_EXEC_T at_wzd_cmd_tbl[] =
{
    {
        "resume_app",
        "r",
        _wzd_cli_resume_app,
        NULL,
        "Usage: r [y/n]",
        CLI_ACCESS_RIGHT_APP_WZD
    },
    {
        "auto_nav_select",
        "ns",
        _wzd_cli_nav_select,
        NULL,
        "Usage: ns [loop navigation select delay]",
        CLI_ACCESS_RIGHT_APP_WZD
    },
    {
        CLI_GET_DBG_LVL_STR,
        NULL,
        _wzd_cli_get_dbg_level,
        NULL,
        CLI_GET_DBG_LVL_HELP_STR,
        CLI_ACCESS_RIGHT_APP_WZD
    },
    {
        CLI_SET_DBG_LVL_STR,
        NULL,
        _wzd_cli_set_dbg_level,
        NULL,
        CLI_SET_DBG_LVL_HELP_STR,
        CLI_ACCESS_RIGHT_APP_WZD
    },
    {
        "create dlg",
        "cdlg",
        _wzd_cli_create_dialog,
        NULL,
        "Usage: cdlg",
        CLI_ACCESS_RIGHT_APP_WZD
    },
    {
        "destroy dlg",
        "ddlg",
        _wzd_cli_destroy_dialog,
        NULL,
        "Usage: ddlg",
        CLI_ACCESS_RIGHT_APP_WZD
    },    
    {
        "Change page",
        "cp",
        _wzd_cli_page_goto,
        NULL,
        "Usage:\n    cp 0 : 1st page\n    cp 1 : last page\n    cp 2 : next page\n    cp 3 : prev page",
        CLI_ACCESS_RIGHT_APP_WZD
    },                
    END_OF_CLI_CMD_TBL
};

/* root command table */
static CLI_EXEC_T at_wzd_root_cmd_tbl[] =
{
    {"wizard", "w", NULL, at_wzd_cmd_tbl, "Wizard commands", CLI_ACCESS_RIGHT_APP_WZD},
    END_OF_CLI_CMD_TBL
};

/*-----------------------------------------------------------------------------
 * export functions implementation
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name:    wzd_cli_attach_cmd_tbl
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _wzd_cli_attach_cmd_tbl (VOID)
{
    return (c_cli_attach_cmd_tbl (at_wzd_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI));
}

/*-----------------------------------------------------------------------------
 * static functions implementation
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name:    _atoi
 * Description: Convert a number string to a number.
 * Inputs:  ps          A NULL-terminated string.
 * Outputs: -
 * Returns: The number.
 ----------------------------------------------------------------------------*/
static INT32  _atoi (const CHAR* ps)
{
    INT32  i4_total = 0;

    while (*ps != 0)
    {
        if (*ps >= '0' && *ps <= '9')
        {
            i4_total = 10 * i4_total + (*ps - '0'); /* accumulate digit */
            ps ++; /* get next char */
        }
        else /* not a digit */
        {
            return (-1);
        }
    }

    return i4_total;
}

/*----------------------------------------------------------------------------
 * Name:    _wzd_cli_resume_app
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _wzd_cli_resume_app (INT32 i4_argc, const CHAR** pps_argv)
{
    BOOL    b_resume = TRUE;

    if (i4_argc > 1)
    {
        if (*pps_argv[1] != 0 && *pps_argv[1] == 'y')
        {
            b_resume = a_wzd_is_resume();
        }
    }

    if (b_resume)
    {
        return a_amb_resume_app (WZD_NAME);
    }

    return 0;
}

/*----------------------------------------------------------------------------
 * Name:    _wzd_cli_nav_select
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _wzd_cli_nav_select (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_loop    = NAV_SEL_DEFAULT_LOOP;
    INT32  i4_max_nav = NAV_SEL_DEFAULT_MAX_NAV;
    INT32  i4_max_sel = NAV_SEL_DEFAULT_MAX_SEL;
    INT32  i4_delay   = NAV_SEL_DEFAULT_DELAY;

    INT32  i4_nav, i4_sel, i4_idx, i4_i, i4_j;
    UINT16 ui2_scan_counter;

    if (i4_argc > 1)
    {
        i4_loop = _atoi (pps_argv[1]);

        if (i4_loop < 0)
        {
            i4_loop = NAV_SEL_DEFAULT_LOOP; /* use default setting */
        }
    }

    if (i4_argc > 2)
    {
        i4_max_nav = _atoi (pps_argv[2]);

        if (i4_max_nav < 0)
        {
            i4_max_nav = NAV_SEL_DEFAULT_MAX_NAV; /* use default setting */
        }
    }


    if (i4_argc > 3)
    {
        i4_max_sel = _atoi (pps_argv[3]);

        if (i4_max_sel < 0)
        {
            i4_max_sel = NAV_SEL_DEFAULT_MAX_SEL; /* use default setting */
        }
    }

    if (i4_argc > 4)
    {
        i4_delay = _atoi (pps_argv[4]);

        if (i4_delay < 0)
        {
            i4_delay = NAV_SEL_DEFAULT_DELAY; /* use default setting */
        }
    }

    i4_idx = 0;
    i4_nav = 0;
    i4_sel = 0;
    ui2_scan_counter = 0;

    b_stop = FALSE; /* CLI command running */

    while (((i4_idx < i4_loop) || (i4_loop == 0)) &&
           (! b_stop))
    {
        i4_nav++;
        i4_nav = i4_nav % i4_max_nav;

        DBG_LOG_PRINT(("\n<WZD> %d-th nav_select ...[nav = %d]\n\r", i4_idx ++, i4_nav));

        for (i4_i = 0; i4_i < i4_nav; i4_i ++)
        {
            i4_sel++;
            i4_sel = i4_sel % i4_max_sel;

            for (i4_j = 0; i4_j < i4_sel; i4_j ++)
            {
                a_wzd_send_sim_key (BTN_CURSOR_DOWN); /* send a CURSOR_DOWN key */
                c_thread_delay ((UINT32) i4_delay);

                if (b_stop)
                {
                    goto WZD_CLI_NAL_SELECT_EXIT;
                }
            }

            a_wzd_send_sim_key (BTN_CURSOR_RIGHT); /* send a CURSOR_RIGHT key */
            c_thread_delay ((UINT32) i4_delay);

            if (b_stop)
            {
                goto WZD_CLI_NAL_SELECT_EXIT;
            }

            /* wait when scanning. */
            if (wzd_is_scan_active ())
            {
                if ((ui2_scan_counter++ % 2) == 0)
                {
                    c_thread_delay (180000);     /* 180 seconds */
                }
                else
                {
                    c_thread_delay (3000);      /* 3 seconds */
                }

                if (wzd_is_scan_active ())
                {   /* cancel scan */                   
                    a_wzd_send_sim_key (BTN_EXIT); /* send a BTN_EXIT key */
                    c_thread_delay ((UINT32) i4_delay);

                    /* go to the next page */
                    a_wzd_send_sim_key (BTN_CURSOR_DOWN); /* send a CURSOR_DOWN key */
                    c_thread_delay ((UINT32) i4_delay);

                    a_wzd_send_sim_key (BTN_CURSOR_RIGHT); /* send a CURSOR_RIGHT key */
                    c_thread_delay ((UINT32) i4_delay);
                }
            }
        }

        for (i4_i = 0; i4_i < i4_nav; i4_i ++)
        {
            a_wzd_send_sim_key (BTN_CURSOR_LEFT); /* send a CURSOR_LEFT key */
            c_thread_delay ((UINT32) i4_delay);

            if (b_stop)
            {
                goto WZD_CLI_NAL_SELECT_EXIT;
            }
        }
    }

WZD_CLI_NAL_SELECT_EXIT:

    b_stop = TRUE; /* CLI command stop */

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_cli_get_dbg_level
 *
 * Description: This API gets the current debug level of Wizard application.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_rc;

    i4_rc = c_cli_show_dbg_level (wzd_get_dbg_level ());;

    return i4_rc;
}


/*-----------------------------------------------------------------------------
 * Name: _wzd_cli_set_dbg_level
 *
 * Description: This API sets the debug level of Wizard application.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32       i4_rc;
    UINT16      ui2_dbg_level;

    i4_rc = c_cli_parse_dbg_level (i4_argc, pps_argv, & ui2_dbg_level);

    if (i4_rc == CLIR_OK)
    {
        wzd_set_dbg_level (ui2_dbg_level);
    }
    else
    {
        DBG_LOG_PRINT(("<WZD> ERR: set debug level failed = %d\n\r", i4_rc));
    }

    return i4_rc;
}

/*----------------------------------------------------------------------------
 * Name:    _wzd_cli_resume_app
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _wzd_cli_create_dialog (INT32 i4_argc, const CHAR** pps_argv)
{
    wzd_app_send_msg (WZD_MSG_CLI_CREATE_DLG, NULL, 0);

    return 0;
}

/*----------------------------------------------------------------------------
 * Name:    _wzd_cli_resume_app
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _wzd_cli_destroy_dialog (INT32 i4_argc, const CHAR** pps_argv)
{    
    wzd_app_send_msg (WZD_MSG_CLI_DESTROY_DLG, NULL, 0);

    return 0;
}

/*----------------------------------------------------------------------------
 * Name:    _wzd_cli_resume_app
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _wzd_cli_page_goto (INT32 i4_argc, const CHAR** pps_argv)
{    
    WZD_PAGE_NAVI_T e_page_navi = WZD_PAGE_NAVI_LAST_VALID_ITEM;
    
    if (i4_argc > 1)
    {
        if (*pps_argv[1] != 0 && *pps_argv[1] == '0')
        {
            e_page_navi = WZD_PAGE_NAVI_FIRST_PAGE;
            wzd_app_send_msg (WZD_MSG_CLI_CHANGE_PAGE, (VOID*)&e_page_navi, sizeof(WZD_PAGE_NAVI_T));
        }
        else if(*pps_argv[1] != 0 && *pps_argv[1] == '1')
        {
            e_page_navi = WZD_PAGE_NAVI_LAST_PAGE;
            wzd_app_send_msg (WZD_MSG_CLI_CHANGE_PAGE, (VOID*)&e_page_navi, sizeof(WZD_PAGE_NAVI_T));
        }
        else if(*pps_argv[1] != 0 && *pps_argv[1] == '2')
        {
            e_page_navi = WZD_PAGE_NAVI_NEXT_PAGE;
            wzd_app_send_msg (WZD_MSG_CLI_CHANGE_PAGE, (VOID*)&e_page_navi, sizeof(WZD_PAGE_NAVI_T));
        }
        else if(*pps_argv[1] != 0 && *pps_argv[1] == '3')
        {
            e_page_navi = WZD_PAGE_NAVI_PREV_PAGE;
            wzd_app_send_msg (WZD_MSG_CLI_CHANGE_PAGE, (VOID*)&e_page_navi, sizeof(WZD_PAGE_NAVI_T));
        }
        else
        {
            DBG_LOG_PRINT(("[WZD][CLI] Wrong parameter!!!\n"));
        }
    }
    else
    {
        DBG_LOG_PRINT(("[WZD][CLI] Wrong parameter!!!\n"));
    }

    return 0;
}

#endif /* CLI_SUPPORT */

/*-----------------------------------------------------------------------------
 * Name: wzd_cli_stop
 *
 * Description: This API stops cli commands for the Wizard application.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID wzd_cli_stop (VOID)
{
    if (! b_stop)
    {
        b_stop = TRUE;
    }
}

/*-----------------------------------------------------------------------------
 * Name: wzd_cli_init
 *
 * Description: This API initializes CLI component for Wizard application.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: WZDR_OK          Routine successful.
 *          WZDR_FAIL        CLI operation is failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_cli_init (VOID)
{
#ifdef CLI_SUPPORT

    INT32       i4_rc;

    /* attach command table to CLI */
    i4_rc = _wzd_cli_attach_cmd_tbl ();

    if (i4_rc != CLIR_OK)
    {
        return WZDR_FAIL;
    }

    return WZDR_OK;

#else /* #ifndef CLI_SUPPORT */

    return WZDR_OK;

#endif /* CLI_SUPPORT */
}
