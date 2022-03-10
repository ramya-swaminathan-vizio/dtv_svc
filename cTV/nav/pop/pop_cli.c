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
 * $RCSfile: pop_cli.c,v $
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
#if (defined(APP_PIP_POP_CTRL) || defined (APP_VOG_SUPPORT))
#ifdef CLI_SUPPORT
#include "c_cli.h"

#include "nav/pop/pop.h"
#include "nav/navigator.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_pop_cli_toggle_tv_mode(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _nav_pop_cli_toggle_focus_win(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _nav_pop_cli_swap(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _nav_pop_cli_dump(INT32 i4_argc, const CHAR** pps_argv);

#ifdef APP_NAV_LISTEN_PIP_SUB_POS_SIZE_CFG_CHANGE
    static INT32 _nav_pop_cli_set_sub_position(INT32 i4_argc, const CHAR** pps_argv);
    static INT32 _nav_pop_cli_set_sub_size(INT32 i4_argc, const CHAR** pps_argv);
#endif
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static CLI_EXEC_T at_pop_cmd_tbl[] =
{
 	{
 	    "dump",
 	    "d",
 	    _nav_pop_cli_dump,
 	    NULL,
 	    "usage: d",
 	    NAV_CLI_ACCESS_RIGHT_LVL
 	},
 	{
 	    "toggle",
 	    "t",
 	    _nav_pop_cli_toggle_tv_mode,
 	    NULL,
 	    "usage: t (as nav paused)",
 	    NAV_CLI_ACCESS_RIGHT_LVL
 	},
 	{
 	    "focus",
 	    "f",
 	    _nav_pop_cli_toggle_focus_win,
 	    NULL,
 	    "usage: f (as nav paused)",
 	    NAV_CLI_ACCESS_RIGHT_LVL
 	},
#ifdef APP_NAV_LISTEN_PIP_SUB_POS_SIZE_CFG_CHANGE 	
 	{
 	    "position",
 	    "p",
 	    _nav_pop_cli_set_sub_position,
 	    NULL,
 	    "usage: p #",
 	    NAV_CLI_ACCESS_RIGHT_LVL
 	},
 	{
 	    "size",
 	    "s",
 	    _nav_pop_cli_set_sub_size,
 	    NULL,
 	    "usage: s #",
 	    NAV_CLI_ACCESS_RIGHT_LVL
 	},
#endif
 	{
 	    "swap",
 	    "swap",
 	    _nav_pop_cli_swap,
 	    NULL,
 	    "usage: swap [#iteration #delay_lower_bound #delay_upper_bound]",
 	    NAV_CLI_ACCESS_RIGHT_LVL
 	},
 	END_OF_CLI_CMD_TBL
};
/* pop command entry */
static CLI_EXEC_T t_g_pop_entry =
	{   "pop",
	    "pop",
	    NULL,
	    at_pop_cmd_tbl,
	    "pop commands",
	    NAV_CLI_ACCESS_RIGHT_LVL
	};
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
#ifdef APP_NAV_LISTEN_PIP_SUB_POS_SIZE_CFG_CHANGE
/*----------------------------------------------------------------------------
 * Name:    _nav_pop_cli_set_sub_position
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _nav_pop_cli_set_sub_position(INT32 i4_argc, const CHAR** pps_argv)
{
    if (i4_argc == 1) {
    #if 0       
        TV_PIP_SUB_POSITION_T e_id = TV_PIP_SUB_POS_UNKNOWN;
        UTF16_T*              pw2s_display_name;
        CHAR                  s_rating[32+1] = {0};
        INT32                 i4_ret;
        
        DBG_INFO(("loop from first to last \r\n"));
        for (;;) {
            i4_ret = a_tv_iterate_pip_sub_position_id(
                        e_id,
                        TV_ITERATE_DIR_NEXT_NO_LOOP,
                        &e_id
                        );
            if (i4_ret != TVR_OK) {
                break;
            }
            
            pw2s_display_name = a_tv_get_pip_sub_position_display_name(e_id);            
            if (pw2s_display_name != NULL) {               
                c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                DBG_INFO(("pip pos(%d, %s)\r\n", e_id, s_rating));
            }
        }
        
        DBG_INFO(("loop from last to first \r\n"));
        for (;;) {
            i4_ret = a_tv_iterate_pip_sub_position_id(
                        e_id,
                        TV_ITERATE_DIR_PREV_NO_LOOP,
                        &e_id
                        );
            if (i4_ret != TVR_OK) {
                break;
            }
            
            pw2s_display_name = a_tv_get_pip_sub_position_display_name(e_id);            
            if (pw2s_display_name != NULL) {               
                c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                DBG_INFO(("pip pos(%d, %s)\r\n", e_id, s_rating));
            }
        }
        
        i4_ret = a_tv_iterate_pip_sub_position_id(
                    TV_PIP_SUB_POS_UNKNOWN,
                    TV_ITERATE_DIR_NEXT,
                    &e_id
                    );
        if (i4_ret == TVR_OK) {
            pw2s_display_name = a_tv_get_pip_sub_position_display_name(e_id);
            if (pw2s_display_name != NULL) {               
                c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                DBG_INFO(("(POS_UNKNOWN, DIR_NEXT) = %s\r\n", s_rating));
            }
        }
        
        i4_ret = a_tv_iterate_pip_sub_position_id(
                    TV_PIP_SUB_POS_UNKNOWN,
                    TV_ITERATE_DIR_FIRST,
                    &e_id
                    );
        if (i4_ret == TVR_OK) {
            TV_PIP_SUB_POSITION_T e_tmp_id = e_id;
            
            pw2s_display_name = a_tv_get_pip_sub_position_display_name(e_id);
            if (pw2s_display_name != NULL) {               
                c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                DBG_INFO(("(POS_UNKNOWN, DIR_FIRST) = %s\r\n", s_rating));
            }
            
            i4_ret = a_tv_iterate_pip_sub_position_id(
                        e_tmp_id,
                        TV_ITERATE_DIR_PREV,
                        &e_tmp_id
                        );
            if (i4_ret == TVR_OK) {
                pw2s_display_name = a_tv_get_pip_sub_position_display_name(e_tmp_id);
                if (pw2s_display_name != NULL) {               
                    c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                    DBG_INFO(("(POS_FIRST, DIR_PREV) = %s\r\n", s_rating));
                }
            }
            
            i4_ret = a_tv_iterate_pip_sub_position_id(
                        e_id,
                        TV_ITERATE_DIR_NEXT,
                        &e_id
                        );
            if (i4_ret == TVR_OK) {
                pw2s_display_name = a_tv_get_pip_sub_position_display_name(e_id);
                if (pw2s_display_name != NULL) {               
                    c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                    DBG_INFO(("(POS_FIRST, DIR_NEXT) = %s\r\n", s_rating));
                }
            }
        }
        
        i4_ret = a_tv_iterate_pip_sub_position_id(
                    TV_PIP_SUB_POS_UNKNOWN,
                    TV_ITERATE_DIR_LAST,
                    &e_id
                    );
        if (i4_ret == TVR_OK) {
            TV_PIP_SUB_POSITION_T e_tmp_id = e_id;
            
            pw2s_display_name = a_tv_get_pip_sub_position_display_name(e_id);
            if (pw2s_display_name != NULL) {               
                c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                DBG_INFO(("(POS_UNKNOWN, DIR_LAST) = %s\r\n", s_rating));
            }
            
            i4_ret = a_tv_iterate_pip_sub_position_id(
                        e_tmp_id,
                        TV_ITERATE_DIR_PREV,
                        &e_tmp_id
                        );
            if (i4_ret == TVR_OK) {
                pw2s_display_name = a_tv_get_pip_sub_position_display_name(e_tmp_id);
                if (pw2s_display_name != NULL) {               
                    c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                    DBG_INFO(("(POS_LAST, DIR_PREV) = %s\r\n", s_rating));
                }
            }
            
            i4_ret = a_tv_iterate_pip_sub_position_id(
                        e_id,
                        TV_ITERATE_DIR_NEXT,
                        &e_id
                        );
            if (i4_ret == TVR_OK) {
                pw2s_display_name = a_tv_get_pip_sub_position_display_name(e_id);
                if (pw2s_display_name != NULL) {               
                    c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                    DBG_INFO(("(POS_LAST, DIR_NEXT) = %s\r\n", s_rating));
                }
            }
        }
        
    #endif       
        return CLIR_OK;
    }

    a_tv_set_pip_sub_position((TV_PIP_SUB_POSITION_T)nav_atoi(pps_argv[1]));
    return CLIR_OK;
}
/*----------------------------------------------------------------------------
 * Name:    _nav_pop_cli_set_sub_size
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _nav_pop_cli_set_sub_size(INT32 i4_argc, const CHAR** pps_argv)
{
    if (i4_argc == 1) {
    #if 0
        TV_PIP_SUB_SIZE_T e_id = TV_PIP_SUB_SIZE_UNKNOWN;
        UTF16_T*          pw2s_display_name;
        CHAR              s_rating[32+1] = {0};
        INT32             i4_ret;
        
        DBG_INFO(("loop from first to last \r\n"));
        for (;;) {
            i4_ret = a_tv_iterate_pip_sub_size_id(
                        e_id,
                        TV_ITERATE_DIR_NEXT_NO_LOOP,
                        &e_id
                        );
            if (i4_ret != TVR_OK) {
                break;
            }
            
            pw2s_display_name = a_tv_get_pip_sub_size_display_name(e_id);            
            if (pw2s_display_name != NULL) {               
                c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                DBG_INFO(("size pos(%d, %s)\r\n", e_id, s_rating));
            }
        }
        
        DBG_INFO(("loop from last to first \r\n"));
        for (;;) {
            i4_ret = a_tv_iterate_pip_sub_size_id(
                        e_id,
                        TV_ITERATE_DIR_PREV_NO_LOOP,
                        &e_id
                        );
            if (i4_ret != TVR_OK) {
                break;
            }
            
            pw2s_display_name = a_tv_get_pip_sub_size_display_name(e_id);            
            if (pw2s_display_name != NULL) {               
                c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                DBG_INFO(("size pos(%d, %s)\r\n", e_id, s_rating));
            }
        }
        
        i4_ret = a_tv_iterate_pip_sub_size_id(
                    TV_PIP_SUB_SIZE_UNKNOWN,
                    TV_ITERATE_DIR_NEXT,
                    &e_id
                    );
        if (i4_ret == TVR_OK) {
            pw2s_display_name = a_tv_get_pip_sub_size_display_name(e_id);
            if (pw2s_display_name != NULL) {               
                c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                DBG_INFO(("(SIZE_UNKNOWN, DIR_NEXT) = %s\r\n", s_rating));
            }
        }
        
        i4_ret = a_tv_iterate_pip_sub_size_id(
                    TV_PIP_SUB_SIZE_UNKNOWN,
                    TV_ITERATE_DIR_FIRST,
                    &e_id
                    );
        if (i4_ret == TVR_OK) {
            TV_PIP_SUB_POSITION_T e_tmp_id = e_id;
            
            pw2s_display_name = a_tv_get_pip_sub_size_display_name(e_id);
            if (pw2s_display_name != NULL) {               
                c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                DBG_INFO(("(SIZE_UNKNOWN, DIR_FIRST) = %s\r\n", s_rating));
            }
            
            i4_ret = a_tv_iterate_pip_sub_size_id(
                        e_tmp_id,
                        TV_ITERATE_DIR_PREV,
                        &e_tmp_id
                        );
            if (i4_ret == TVR_OK) {
                pw2s_display_name = a_tv_get_pip_sub_size_display_name(e_tmp_id);
                if (pw2s_display_name != NULL) {               
                    c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                    DBG_INFO(("(SIZE_FIRST, DIR_PREV) = %s\r\n", s_rating));
                }
            }
            
            i4_ret = a_tv_iterate_pip_sub_size_id(
                        e_id,
                        TV_ITERATE_DIR_NEXT,
                        &e_id
                        );
            if (i4_ret == TVR_OK) {
                pw2s_display_name = a_tv_get_pip_sub_size_display_name(e_id);
                if (pw2s_display_name != NULL) {               
                    c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                    DBG_INFO(("(SIZE_FIRST, DIR_NEXT) = %s\r\n", s_rating));
                }
            }
        }
        
        i4_ret = a_tv_iterate_pip_sub_size_id(
                    TV_PIP_SUB_SIZE_UNKNOWN,
                    TV_ITERATE_DIR_LAST,
                    &e_id
                    );
        if (i4_ret == TVR_OK) {
            TV_PIP_SUB_POSITION_T e_tmp_id = e_id;
            
            pw2s_display_name = a_tv_get_pip_sub_size_display_name(e_id);
            if (pw2s_display_name != NULL) {               
                c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                DBG_INFO(("(SIZE_UNKNOWN, DIR_LAST) = %s\r\n", s_rating));
            }
            
            i4_ret = a_tv_iterate_pip_sub_size_id(
                        e_tmp_id,
                        TV_ITERATE_DIR_PREV,
                        &e_tmp_id
                        );
            if (i4_ret == TVR_OK) {
                pw2s_display_name = a_tv_get_pip_sub_size_display_name(e_tmp_id);
                if (pw2s_display_name != NULL) {               
                    c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                    DBG_INFO(("(SIZE_LAST, DIR_PREV) = %s\r\n", s_rating));
                }
            }
            
            i4_ret = a_tv_iterate_pip_sub_size_id(
                        e_id,
                        TV_ITERATE_DIR_NEXT,
                        &e_id
                        );
            if (i4_ret == TVR_OK) {
                pw2s_display_name = a_tv_get_pip_sub_size_display_name(e_id);
                if (pw2s_display_name != NULL) {               
                    c_uc_w2s_to_ps(pw2s_display_name, s_rating, 32);
                    DBG_INFO(("(SIZE_LAST, DIR_NEXT) = %s\r\n", s_rating));
                }
            }
        }        
    #endif
        return CLIR_OK;
    }

    a_tv_set_pip_sub_size((TV_PIP_SUB_SIZE_T)nav_atoi(pps_argv[1]));
    return CLIR_OK;
}
#endif
/*----------------------------------------------------------------------------
 * Name:    _nav_pop_cli_toggle_focus_win
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _nav_pop_cli_toggle_focus_win(INT32 i4_argc, const CHAR** pps_argv)
{
    TV_WIN_ID_T e_focus_id;
    INT32       i4_ret;

    i4_ret = a_tv_get_focus_win(&e_focus_id);
    if (i4_ret != TVR_OK) {
        DBG_ERROR(("get focus twin failed!"));
        return CLIR_OK;
    }

    a_tv_set_focus_win(NAV_GET_FOCUS_ID(e_focus_id));

    return CLIR_OK;
}
/*----------------------------------------------------------------------------
 * Name:    _nav_pop_cli_toggle_tv_mode
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _nav_pop_cli_toggle_tv_mode(INT32 i4_argc, const CHAR** pps_argv)
{
    TV_MODE_T e_tv_mode;
    INT32     i4_ret;

    i4_ret = a_tv_get_mode(&e_tv_mode);
    if (i4_ret != TVR_OK) {
        DBG_ERROR(("get tv mode failed!"));
        return CLIR_OK;
    }

    switch(e_tv_mode) {
    case TV_MODE_TYPE_NORMAL:
        e_tv_mode = TV_MODE_TYPE_PIP;
        DBG_INFO(("set tv mode to PIP!"));
        break;
    case TV_MODE_TYPE_PIP:
        e_tv_mode = TV_MODE_TYPE_POP;
        DBG_INFO(("set tv mode to POP!"));
        break;
    case TV_MODE_TYPE_POP:
    default:
        e_tv_mode = TV_MODE_TYPE_NORMAL;
        DBG_INFO(("set tv mode to NORMAL!"));
        break;
    }

    a_tv_set_mode(e_tv_mode);
    return CLIR_OK;
}
/*----------------------------------------------------------------------------
 * Name:    _nav_pop_cli_swap
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _nav_pop_cli_swap(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_delay_lower = 3000;
    INT32  i4_delay_upper = 3000;
    INT32  i4_delay_delta = 0;
    INT32  i4_loop        = 10;
    UINT32 ui4_idx        = 0;
    UINT32 ui4_delay      = 0;
    BOOL   b_is_random_ch = FALSE;

    if (i4_argc > 1) {
        i4_loop = nav_atoi(pps_argv[1]);
        if (i4_loop < 0) {
            DBG_ERROR(("iteration must larger or equal to zero!\r\n"));
            return CLIR_OK;
        }
    }

    if (i4_argc > 2) {
        i4_delay_lower = nav_atoi(pps_argv[2]);
        if (i4_delay_lower == -1 || i4_delay_lower == 0) {
            i4_delay_lower = 3000;
        }

        if (i4_delay_lower < 50) {
            i4_delay_lower = 50;
        }
    }

    if (i4_argc > 3) {
        i4_delay_upper = nav_atoi(pps_argv[3]);
        if (i4_delay_upper == -1 || i4_delay_upper == 0) {
            i4_delay_upper = 3000;
        }

        if (i4_delay_upper < 50) {
            i4_delay_upper = 50;
        }

        if (i4_delay_upper < i4_delay_lower) {
            DBG_ERROR(("upper bound must large or equal to lower bound!\r\n"));
            return CLIR_OK;
        }
    } else {
        i4_delay_upper = i4_delay_lower;
    }

    b_is_random_ch = (i4_delay_upper == i4_delay_lower) ? FALSE : TRUE;
    i4_delay_delta = (i4_delay_upper - i4_delay_lower + 1);
    ui4_delay      = (UINT32)i4_delay_lower;

    while ((ui4_idx < i4_loop || i4_loop == 0) && nav_is_active() == TRUE) {
        if (b_is_random_ch == TRUE){
            ui4_delay = (UINT32)((nav_rand() % i4_delay_delta) + i4_delay_lower);
        }

        DBG_INFO(("\r\n----> %d-th swap(delay=%d ms)...\r\n", ui4_idx++, ui4_delay));
        nav_send_sim_rc_key_event(BTN_SWAP);

        c_thread_delay(ui4_delay);
    }

    return CLIR_OK;
}
/*----------------------------------------------------------------------------
 * Name:    _nav_pop_cli_dump
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _nav_pop_cli_dump(INT32 i4_argc, const CHAR** pps_argv)
{
    pop_print_self();
    return CLIR_OK;
}
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name:    nav_pop_cli_register_cmd_tbl
 * Description:
 *      The API is used to register POP table. The API must be invoked
 *      in a_nav_pop_register().
 * Input arguments:
 *      NONE
 * Output arguments:
 *      NONE
 * Returns:
 *      NONE
 *----------------------------------------------------------------------------*/
VOID nav_pop_cli_register_cmd_tbl(VOID)
{
    nav_register_comp_cli_entry(&t_g_pop_entry);
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
#endif /* end of CLI_SUPPORT */ 
#endif /* end of APP_PIP_POP_CTRL */
