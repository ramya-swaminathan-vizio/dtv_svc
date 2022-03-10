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
 * $RCSfile: epg_cli.c,v $
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
#include "u_cli.h"
#include "c_cli.h"
#include "c_os.h"

#include "app_util/a_cli_app.h"

#include "epg/a_epg.h"
#include "epg/epg_dbg.h"

extern CHAR c_cli_get_char_timeout(UINT32 ui4_time);

/*
   Internal variable for stopping cli commands.
*/
static BOOL b_stop = TRUE;

/*
   Default values for cli commands.
*/
#define  MIN_DELAY          100
#define  DEFAULT_LOOP       1
#define  DEFAULT_STEP       1
#define  DEFAULT_LOWER      200
#define  DEFAULT_UPPER      3000


#if defined(CLI_SUPPORT) || defined(CLI_STRESS_MODE)
/*
   Static function prototype declaraions.
*/
static INT32  _epg_cli_attach_cmd_tbl (VOID);
static INT32  _epg_cli_change_channel (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _epg_cli_scroll_list (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _epg_cli_change_channel_scroll_list (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _epg_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _epg_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _atoi (const CHAR* ps);
static UINT32 _random_delay (INT32 i4_lower, INT32 i4_upper);

/*
   Command tables.
*/
static CLI_EXEC_T at_epg_cmd_tbl[] =
{
    {
        "epg_chg_chn",
        "epg_cc",
        _epg_cli_change_channel,
        NULL,
        "Usage: epg_cc [#iteration #delay_lower #delay_upper] (press 'EXIT' button to exit)",
        CLI_ACCESS_RIGHT_APP_EPG
    },
    {
        "epg_scrol_lst",
        "epg_sl",
        _epg_cli_scroll_list,
        NULL,
        "Usage: epg_sl [#iteration #step #delay_lower #delay_upper] (press 'EXIT' button to exit)",
        CLI_ACCESS_RIGHT_APP_EPG
    },
    {
        "epg_chg_scrol",
        "epg_cs",
        _epg_cli_change_channel_scroll_list,
        NULL,
        "Usage: epg_cs [#iteration #step #chg_delay_lower #chg_delay_upper #scrol_delay_lower #scrol_delay_upper]",
        CLI_ACCESS_RIGHT_APP_EPG
    },
    {
        CLI_GET_DBG_LVL_STR,
        NULL,
        _epg_cli_get_dbg_level,
        NULL,
        CLI_GET_DBG_LVL_HELP_STR,
        CLI_ACCESS_RIGHT_APP_EPG
    },
    {
        CLI_SET_DBG_LVL_STR,
        NULL,
        _epg_cli_set_dbg_level,
        NULL,
        CLI_SET_DBG_LVL_HELP_STR,
        CLI_ACCESS_RIGHT_APP_EPG
    },
    END_OF_CLI_CMD_TBL
};

/*
   root command table.
*/
static CLI_EXEC_T at_epg_root_cmd_tbl[] =
{
    {"epg", NULL, NULL, at_epg_cmd_tbl, "EPG commands", CLI_ACCESS_RIGHT_APP_EPG},
    END_OF_CLI_CMD_TBL
};


/*----------------------------------------------------------------------------
 * Name:    _epg_cli_attach_cmd_tbl
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32  _epg_cli_attach_cmd_tbl (VOID)
{
    return (c_cli_attach_cmd_tbl (at_epg_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI | CLI_GRP_EPG));
}

/*----------------------------------------------------------------------------
 * Name:    _epg_cli_change_channel
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32  _epg_cli_change_channel (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_loop = DEFAULT_LOOP;         /* loop */
    INT32  i4_delay_lower = DEFAULT_LOWER; /* lower delay of changing channel */
    INT32  i4_delay_upper = DEFAULT_UPPER; /* upper delay of changing channel */
    INT32  i4_idx;

    if (i4_argc > 1)
    {
        i4_loop = _atoi (pps_argv[1]);

        if (i4_loop < 0)
        {
            i4_loop = DEFAULT_LOOP; /* use default setting */
        }
        else if (i4_loop == 0)
        {
            i4_loop = 0; /* forever loop */
        }
    }

    if (i4_argc > 2)
    {
        i4_delay_lower = _atoi (pps_argv[2]);

        if (i4_delay_lower < 0)
        {
            i4_delay_lower = DEFAULT_LOWER; /* use default setting */
        }
        else if (i4_delay_lower < MIN_DELAY)
        {
            i4_delay_lower = MIN_DELAY; /* limit shortest delay */
        }
    }

    if (i4_argc > 3)
    {
        i4_delay_upper = _atoi (pps_argv[3]);

        if (i4_delay_upper < 0)
        {
            i4_delay_upper = DEFAULT_UPPER; /* use default setting */
        }
        else if (i4_delay_upper < MIN_DELAY)
        {
            i4_delay_upper = MIN_DELAY; /* limit shortest delay */
        }
    }

    i4_idx = 0;

    b_stop = FALSE; /* CLI command running */

    while (((i4_idx < i4_loop) || (i4_loop == 0)) &&
           (! b_stop) &&
           (c_cli_get_char_timeout(50) != CLI_ASCII_KEY_CTRL_B))
    {
        a_epg_send_sim_key (BTN_PRG_UP); /* send a PRG_UP key to epg */

        c_thread_delay ((UINT32) _random_delay (i4_delay_lower, i4_delay_upper));

        DBG_INFO (("\n<EPG> %d-th change channel ...\n\r", i4_idx ++));
    }

    b_stop = TRUE; /* CLI command stop */

    return CLIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _epg_cli_scroll_list
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32  _epg_cli_scroll_list (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_loop = DEFAULT_LOOP;         /* loop */
    INT32  i4_step = DEFAULT_STEP;         /* step */
    INT32  i4_delay_lower = DEFAULT_LOWER; /* lower delay of scrolling listing */
    INT32  i4_delay_upper = DEFAULT_UPPER; /* upper delay of scrolling listing */
    INT32  i4_idx, i4_i;

    if (i4_argc > 1)
    {
        i4_loop = _atoi (pps_argv[1]);

        if (i4_loop < 0)
        {
            i4_loop = DEFAULT_LOOP; /* use default setting */
        }
        else if (i4_loop == 0)
        {
            i4_loop = 0; /* forever loop */
        }
    }

    if (i4_argc > 2)
    {
        i4_step = _atoi (pps_argv[2]);

        if (i4_step < 0)
        {
            i4_step = DEFAULT_STEP; /* use default setting */
        }
    }

    if (i4_argc > 3)
    {
        i4_delay_lower = _atoi (pps_argv[3]);

        if (i4_delay_lower < 0)
        {
            i4_delay_lower = DEFAULT_LOWER; /* use default setting */
        }
        else if (i4_delay_lower < MIN_DELAY)
        {
            i4_delay_lower = MIN_DELAY; /* limit shortest delay */
        }
    }

    if (i4_argc > 4)
    {
        i4_delay_upper = _atoi (pps_argv[4]);

        if (i4_delay_upper < 0)
        {
            i4_delay_upper = DEFAULT_UPPER; /* use default setting */
        }
        else if (i4_delay_upper < MIN_DELAY)
        {
            i4_delay_upper = MIN_DELAY; /* limit shortest delay */
        }
    }

    i4_idx = 0;

    b_stop = FALSE; /* CLI command running */

    while (((i4_idx < i4_loop) || (i4_loop == 0)) &&
           (! b_stop) &&
           (c_cli_get_char_timeout(50) != CLI_ASCII_KEY_CTRL_B))
    {
        /* scroll down for i4_step times */
        for (i4_i = 0; i4_i < i4_step; i4_i ++)
        {
            a_epg_send_sim_key (BTN_CURSOR_DOWN);
            c_thread_delay ((UINT32) _random_delay(i4_delay_lower, i4_delay_upper));

            if (b_stop)
            {
                break;
            }
        }

        /* scroll up for i4_step times */
        for (i4_i = 0; i4_i < i4_step; i4_i ++)
        {
            a_epg_send_sim_key (BTN_CURSOR_UP);
            c_thread_delay ((UINT32) _random_delay(i4_delay_lower, i4_delay_upper));

            if (b_stop)
            {
                break;
            }
        }

        DBG_INFO (("\n<EPG> %d-th scroll list ...\n\r", i4_idx ++));
    }

    b_stop = TRUE; /* CLI command stop */

    return CLIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _epg_cli_change_channel_scroll_list
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32  _epg_cli_change_channel_scroll_list (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_loop = DEFAULT_LOOP;   /* loop */
    INT32  i4_step = DEFAULT_STEP;   /* step */
    INT32  i4_chg_delay_lower   = DEFAULT_LOWER; /* lower delay of changing channel */
    INT32  i4_chg_delay_upper   = DEFAULT_UPPER; /* upper delay of changing channel */
    INT32  i4_scrol_delay_lower = DEFAULT_LOWER; /* lower delay of scrolling listing */
    INT32  i4_scrol_delay_upper = DEFAULT_UPPER; /* upper dealy of scrolling listing */
    INT32  i4_idx, i4_i;

    if (i4_argc > 1)
    {
        i4_loop = _atoi (pps_argv[1]);

        if (i4_loop < 0)
        {
            i4_loop = DEFAULT_LOOP; /* use default setting */
        }
        else if (i4_loop == 0)
        {
            i4_loop = 0; /* forever loop */
        }
    }

    if (i4_argc > 2)
    {
        i4_step = _atoi (pps_argv[2]);

        if (i4_step < 0)
        {
            i4_step = DEFAULT_STEP; /* use default setting */
        }
    }

    if (i4_argc > 3)
    {
        i4_chg_delay_lower = _atoi (pps_argv[3]);

        if (i4_chg_delay_lower < 0)
        {
            i4_chg_delay_lower = DEFAULT_LOWER; /* use default setting */
        }
        else if (i4_chg_delay_lower < MIN_DELAY)
        {
            i4_chg_delay_lower = MIN_DELAY; /* limit shortest delay */
        }
    }

    if (i4_argc > 4)
    {
        i4_chg_delay_upper = _atoi (pps_argv[4]);

        if (i4_chg_delay_upper < 0)
        {
            i4_chg_delay_upper = DEFAULT_UPPER; /* use default setting */
        }
        else if (i4_chg_delay_upper < MIN_DELAY)
        {
            i4_chg_delay_upper = MIN_DELAY; /* limit shortest delay */
        }
    }

    if (i4_argc > 5)
    {
        i4_scrol_delay_lower = _atoi (pps_argv[5]);

        if (i4_scrol_delay_lower < 0)
        {
            i4_scrol_delay_lower = DEFAULT_LOWER; /* use default setting */
        }
        else if (i4_scrol_delay_lower < MIN_DELAY)
        {
            i4_scrol_delay_lower = MIN_DELAY; /* limit shortest delay */
        }
    }

    if (i4_argc > 6)
    {
        i4_scrol_delay_upper = _atoi (pps_argv[6]);

        if (i4_scrol_delay_upper < 0)
        {
            i4_scrol_delay_upper = DEFAULT_UPPER; /* use default setting */
        }
        else if (i4_scrol_delay_upper < MIN_DELAY)
        {
            i4_scrol_delay_upper = MIN_DELAY; /* limit shortest delay */
        }
    }

    i4_idx = 0;

    b_stop = FALSE; /* CLI command running */

    while (((i4_idx < i4_loop) || (i4_loop == 0)) &&
           (!b_stop) &&
           (c_cli_get_char_timeout(50) != CLI_ASCII_KEY_CTRL_B))
    {
        /* scroll down for i4_step times */
        for (i4_i = 0; i4_i < i4_step; i4_i ++)
        {
            a_epg_send_sim_key (BTN_CURSOR_DOWN);
            c_thread_delay ((UINT32) _random_delay(i4_scrol_delay_lower, i4_scrol_delay_upper));

            if (b_stop)
            {
                break;
            }
        }

        /* scroll up for i4_step times */
        for (i4_i = 0; i4_i < i4_step; i4_i ++)
        {
            a_epg_send_sim_key (BTN_CURSOR_UP);
            c_thread_delay ((UINT32) _random_delay(i4_scrol_delay_lower, i4_scrol_delay_upper));

            if (b_stop)
            {
                break;
            }
        }

        a_epg_send_sim_key (BTN_PRG_UP); /* send a PRG_UP key to epg */

        c_thread_delay ((UINT32) _random_delay(i4_chg_delay_lower, i4_chg_delay_upper));

        DBG_INFO (("\n<EPG> %d-th change channel and scroll list ...\n\r", i4_idx ++));
    }

    b_stop = TRUE; /* CLI command stop */

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _epg_cli_get_dbg_level
 *
 * Description: This API gets the current debug level of EPG.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32  _epg_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    return c_cli_show_dbg_level (epg_get_dbg_level());
}

/*-----------------------------------------------------------------------------
 * Name: _epg_cli_set_dbg_level
 *
 * Description: This API sets the debug level of EPG.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 ----------------------------------------------------------------------------*/
static INT32  _epg_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32       i4_rc;
    UINT16      ui2_dbg_level;

    i4_rc = c_cli_parse_dbg_level (i4_argc, pps_argv, & ui2_dbg_level);

    if (i4_rc == CLIR_OK)
    {
        epg_set_dbg_level (ui2_dbg_level);
    }
    else
    {
        DBG_INFO (("<EPG> ERR: set debug level failed = %d\n\r", i4_rc));
    }

    return i4_rc;
}

/*----------------------------------------------------------------------------
 * Name:    _atoi
 *
 * Description: Convert a number string to a number.
 *
 * Inputs:  ps          A NULL-terminated string.
 *
 * Outputs: -
 *
 * Returns: The number.
 ----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------
 * Name:    _random_delay
 *
 * Description: Generate a random delay given lower and upper bounds.
 *
 * Inputs:  i4_lower    Lower bound.
 *          i4_upper    Upper bound.
 *
 * Outputs: -
 *
 * Returns: random delay
 ----------------------------------------------------------------------------*/
static UINT32  _random_delay (INT32 i4_lower, INT32 i4_upper)
{
    UINT32   ui4_interval;
    UINT32   ui4_random_num;

    ui4_interval = (UINT32)(i4_upper - i4_lower + 1);

    ui4_random_num = c_os_get_sys_tick() * c_os_get_sys_tick_period() + c_os_get_sys_tick_period();

    return ((UINT32)(i4_lower + (ui4_random_num % ui4_interval)));
}
#endif /* CLI_SUPPORT */

/*-----------------------------------------------------------------------------
 * Name: epg_cli_is_running
 *
 * Description: This API checks if a cli command is running.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: EPGR_OK                     Routine successful.
 *          EPGR_FAIL                   CLI operation failed.
 ----------------------------------------------------------------------------*/
BOOL epg_cli_is_running (VOID)
{
    return (! b_stop) ? TRUE : FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: epg_cli_stop
 *
 * Description: This API stops cli commands.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: EPGR_OK                     Routine successful.
 *          EPGR_FAIL                   CLI operation failed.
 ----------------------------------------------------------------------------*/
VOID epg_cli_stop (VOID)
{
    b_stop = TRUE;
}

/*-----------------------------------------------------------------------------
 * Name: epg_cli_init
 *
 * Description: This API initializes CLI component for EPG application.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: EPGR_OK                     Routine successful.
 *          EPGR_FAIL                   CLI operation failed.
 ----------------------------------------------------------------------------*/
INT32 epg_cli_init (VOID)
{
#if defined(CLI_SUPPORT) || defined(CLI_STRESS_MODE)
    INT32    i4_rc;

    /* attach command table to CLI */
    i4_rc = _epg_cli_attach_cmd_tbl ();

    if (i4_rc != CLIR_OK)
    {
        return EPGR_FAIL;
    }
    return EPGR_OK;
#else
    return EPGR_OK;
#endif /* CLI_SUPPORT */
}
