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
 * $RCSfile: menu_page_date_time.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_dt.h"
#include "c_pcl.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"


#include "app_util/a_cfg.h"
#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_page_tree.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_dbg.h"

#ifdef COMMON_DATE_TIME_ENABLE

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#ifndef    COMMON_DATE_TIME_DATE_EB_IDX
    #define    COMMON_DATE_TIME_DATE_EB_IDX      0
#endif

#ifndef    COMMON_DATE_TIME_TIME_EB_IDX
    #define    COMMON_DATE_TIME_TIME_EB_IDX      1
#endif

#ifndef    TIMER_REFRESH_DELAY
    #define    TIMER_REFRESH_DELAY              1000
#endif

#define  DT_DISCONT_NEGATIVE_DELTA        (-10)                   /* Delta time for date-time discontinuity (in seconds). */
#define  DT_DISCONT_POSITIVE_DELTA        (10)                   /* Delta time for date-time discontinuity (in seconds). */


typedef struct _TIMER_EDIT_DATA_T
{
    CHAR*      ps_g_time;               /* Point to s_g_edit_time,  etc. */
    UINT8*     pui1_cursor_pos;         /* Point to gui1_eb_time_cursor_pos,  etc. */
} TIMER_EDIT_DATA_T;

#define   RTC_MAX_YEAR                          ((((UINT32)((APP_RTC_UPPER_BOUNDARY)/(86400*365)))-1)+1970)

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_date_time;

/* Widget */
static HANDLE_T      h_cnt_frm;
static HANDLE_T      h_lb_additional;
static HANDLE_T      h_homebar;
static HANDLE_T      h_backbar;
static HANDLE_T      h_eb_date;
static HANDLE_T      h_eb_time;
static HANDLE_T      ah_chain[5] = {NULL_HANDLE};
static INT8          i1_g_chain_len = 1;
UTF16_T*             apw2s_help_tip[5] = {0};

/* Timer */
static HANDLE_T      h_timer_refresh;

/* Backup Date/Time */
static DTG_T         t_g_backup_datetime;

/* Date Editing Mode */
static CHAR          s_g_edit_date[11];     /* Current Date Editing String */ /* 2006/08/01 */
static UINT8         gui1_eb_date_cursor_pos;

/* Time Editing Mode */
static CHAR          s_g_edit_time[9];      /* Current Time Editing String */ /* 10:30:20 */
static UINT8         gui1_eb_time_cursor_pos;

/* Indicate the Refresh state, no notify processing */
static BOOL          b_g_refreshing = FALSE;

/* Indicate the page state */
static BOOL          b_g_date_time_page_in_on = FALSE;

/* Date/Time library */
static HANDLE_T      h_g_dt                  = NULL_HANDLE;
static DT_COND_T     t_g_latest_dt_cond      = DT_FREE_RUNNING;

/* Additional menu-items */
static UINT8         gui1_additional_item_num = 0;
static MENU_ITEM_T   t_menu_additional_item;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _set_nav(VOID);
static VOID _timer_refresh_nfy_fct(HANDLE_T  h_timer,VOID*     pv_tag);
static VOID _timer_refresh_start(VOID);
static VOID _timer_refresh_stop(VOID);
static VOID _date_time_confirm_update(VOID);

static INT32 _chg_date_time_color(HANDLE_T h_widget, BOOL b_enable, BOOL b_repaint);

static INT32 _chg_wgt_foucs(BOOL b_next);

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _homebar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WMPR_DONE;

        case BTN_SELECT:
            menu_nav_go_home_menu();
            return WMPR_DONE;

        case BTN_CURSOR_RIGHT:
            break;

        case BTN_CURSOR_UP:
            c_wgl_set_focus(h_eb_time, WGL_NO_AUTO_REPAINT);
            menu_hide_help_tip();
            menu_set_and_trigger_help_tip(apw2s_help_tip[i1_g_chain_len - 1]);
            menu_pm_repaint();
            break;

        case BTN_CURSOR_DOWN:
            c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
            menu_hide_help_tip();
            menu_set_and_trigger_help_tip(apw2s_help_tip[1]);
            menu_pm_repaint();
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        case BTN_SELECT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WMPR_DONE;

        case BTN_CURSOR_RIGHT:
            break;

        case BTN_CURSOR_UP:
            c_wgl_set_focus(h_homebar, WGL_NO_AUTO_REPAINT);
            menu_hide_help_tip();
            menu_set_and_trigger_help_tip(apw2s_help_tip[0]);
            menu_pm_repaint();
            break;

        case BTN_CURSOR_DOWN:
            c_wgl_set_focus(h_eb_date, WGL_NO_AUTO_REPAINT);
            menu_hide_help_tip();
            menu_set_and_trigger_help_tip(apw2s_help_tip[2]);
            menu_pm_repaint();
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _hide_power_on_timer
 *
 * Description: Hide the power on timer, called by on_page_create
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _maximum_utc_range_check(VOID)
{
    TIME_T  t_utc = 0;

    t_utc = c_dt_get_utc(NULL,NULL);

    /* Maximum value = 2038/1/2 GMT+0 */
    if (t_utc > APP_RTC_UPPER_BOUNDARY)
    {
        /* Set to 2038/1/1 GMT+0 */
       c_dt_set_utc((APP_RTC_UPPER_BOUNDARY-86400), 0);

        /* Since the timer is updated, it should update the power also. */
        a_cfg_update_timer_power();
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _do_update_timer_power(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    a_cfg_update_timer_power();
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _menu_page_date_time_nfy_dt (HANDLE_T     h_dt,
                                         VOID*        pv_tag,
                                         DT_COND_T    t_dt_cond,
                                         TIME_T       t_delta)
{
    /* This page is not active, do nothing. */
    if (! b_g_date_time_page_in_on)
    {
        return;
    }

    if (t_dt_cond == DT_SYNC_DISCONT)
    {
        if ( (t_delta < DT_DISCONT_NEGATIVE_DELTA) ||
             (t_delta > DT_DISCONT_POSITIVE_DELTA) )
        {
             menu_async_invoke(_do_update_timer_power, NULL, 0, FALSE);
        }
    }

    else if (t_g_latest_dt_cond == DT_FREE_RUNNING &&   /* Transition from FREE_RUNNING to SYNC_RUNNING. */
             t_dt_cond == DT_SYNC_RUNNING)
    {
        menu_async_invoke(_do_update_timer_power, NULL, 0, FALSE);
    }

    if (t_dt_cond == DT_SYNC_RUNNING ||
        t_dt_cond == DT_FREE_RUNNING ||
        t_dt_cond == DT_NOT_RUNNING)
    {

        /* Save current DT Cond */
        t_g_latest_dt_cond = t_dt_cond;
    }
}


/*----------------------------------------------------------------------------
 * Name: _init_date_time_in_menu
 *
 * Description: Init the date time handle in menu
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _init_date_time_in_menu(VOID)
{
    if (h_g_dt == NULL_HANDLE)
    {
        c_dt_reg_nfy_fct(_menu_page_date_time_nfy_dt,
                         NULL,
                         & h_g_dt);

    }

    /* Get current date/time state */
    c_dt_get_utc(NULL, & t_g_latest_dt_cond);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _atoi
 *
 * Description: Convert a number string to a number.
 *
 * Inputs:  ps     null ('\0') terminated character string.
 *
 *
 * Outputs: -
 *
 * Returns: sum of the number string.
 *
 ----------------------------------------------------------------------------*/
static INT32 _atoi( const CHAR* ps )
{
    INT32  i4_total;

    i4_total = 0;
    while ( *ps != 0 )
    {
        if ( *ps >= '0' && *ps <= '9' )
        {
            /* accumulate digit */
            i4_total = 10 * i4_total + (*ps - '0');
            ps++; /* get next char */
        }
        else /* not a digit char */
        {
            return (-1);
        }
    }

    return i4_total;
}

/*----------------------------------------------------------------------------
 * Name: _date_time_set_attach_data
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_menu_item_data_by_widget(
    HANDLE_T           h_widget,
    MENU_ITEM_T**      ppt_menu_item)
{
    INT32 i4_ret;
    if(h_widget == NULL_HANDLE)
    {
        return MENUR_INV_ARG;
    }


    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_menu_item),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _date_time_set_attach_data
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _date_time_set_attach_data(HANDLE_T               h_eb_time,
                                        TIMER_EDIT_DATA_T*     pt_timer_edit_data)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_eb_time,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_timer_edit_data),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _date_time_get_attach_data
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _date_time_get_attach_data(HANDLE_T               h_eb_time,
                                        TIMER_EDIT_DATA_T**    ppt_timer_edit_data)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_eb_time,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_timer_edit_data),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _convert_date_str_to_val
 *
 * Description: Convert "2006/08/03" to ui2_year/ui1_month/ui1_day
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _convert_date_str_to_val(char*  ps_date,       /* in */
                                     UINT16* pui2_year,     /* out */
                                     UINT8*  pui1_month,    /* out */
                                     UINT8*  pui1_day)      /* out */
{
    CHAR     s_year[5];
    CHAR     s_month[3];
    CHAR     s_day[3];
    INT16    i2_year;
    INT8     i1_month;
    INT8     i1_day;

    /* Convert Year */
    s_year[0]  = ps_date[0];
    s_year[1]  = ps_date[1];
    s_year[2]  = ps_date[2];
    s_year[3]  = ps_date[3];
    s_year[4]  = '\0';
    i2_year    = (INT16) _atoi(s_year);

    /* Convert Month */
    s_month[0] = ps_date[5];
    s_month[1] = ps_date[6];
    s_month[2] = '\0';
    i1_month   = (INT8) _atoi(s_month);

    /* Convert Day */
    s_day[0]   = ps_date[8];
    s_day[1]   = ps_date[9];
    s_day[2]   = '\0';
    i1_day     = (INT8) _atoi(s_day);

    *pui2_year  = (UINT16) i2_year;
    *pui1_month = (UINT8)  i1_month;
    *pui1_day   = (UINT8)  i1_day;

}

/*----------------------------------------------------------------------------
 * Name: _convert_date_val_to_str
 *
 * Description: Convert ui2_year/ui1_month/ui1_day to "2006/08/03"
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _convert_date_val_to_str(UINT16  ui2_year,      /* in */
                                     UINT8   ui1_month,     /* in */
                                     UINT8   ui1_day,       /* in */
                                     char*  ps_date)       /* out */
{
    c_sprintf(ps_date,"%04d/%02d/%02d",ui2_year, ui1_month, ui1_day);
}

/*----------------------------------------------------------------------------
 * Name: _convert_time_str_to_val
 *
 * Description: Convert "22:11:30" to ui1_hour/ui1_min/ui1_sec
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _convert_time_str_to_val(char*   ps_time,       /* in */
                                     UINT8*  pui1_hour,     /* out */
                                     UINT8*  pui1_min,      /* out */
                                     UINT8*  pui1_sec)      /* out */
{
    /* 12:30:59 */
    /* 01234567 */

    CHAR     s_hour[3];
    CHAR     s_min[3];
    CHAR     s_sec[3];
    INT8     i1_hour;
    INT8     i1_min;
    INT8     i1_sec;

    /* Convert Hour */
    s_hour[0] = ps_time[0];
    s_hour[1] = ps_time[1];
    s_hour[2] = '\0';
    i1_hour = (INT8) _atoi(s_hour);

    /* Convert Minute */
    s_min[0] = ps_time[3];
    s_min[1] = ps_time[4];
    s_min[2] = '\0';
    i1_min = (INT8) _atoi(s_min);

    /* Convert Second */
    s_sec[0] = ps_time[6];
    s_sec[1] = ps_time[7];
    s_sec[2] = '\0';
    i1_sec = (INT8) _atoi(s_sec);

    *pui1_hour = (UINT8) i1_hour;
    *pui1_min  = (UINT8) i1_min;
    *pui1_sec  = (UINT8) i1_sec;

}

/*----------------------------------------------------------------------------
 * Name: _convert_time_val_to_str
 *
 * Description: Convert ui1_hour/ui1_minute/ui1_second to "23:10:50"
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _convert_time_val_to_str(UINT16  ui1_hour,         /* in */
                                     UINT8   ui1_minute,       /* in */
                                     UINT8   ui1_second,       /* in */
                                     char*  ps_time)          /* out */
{
    c_sprintf(ps_time,"%02d:%02d:%02d",ui1_hour, ui1_minute, ui1_second);
}

/*----------------------------------------------------------------------------
 * Name: _force_correct_year
 *
 * Description: Give "YYYY/MM/DD", auto correct YYYY
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _force_correct_year(char* ps_date)
{
    UINT16    ui2_year;
    UINT8     ui1_month;
    UINT8     ui1_day;

    _convert_date_str_to_val(ps_date,
                             &ui2_year,
                             &ui1_month,
                             &ui1_day);

    if(  ui2_year >= 2000 && ui2_year <= (UINT16)(RTC_MAX_YEAR) )
    {
        return;   /* Current setting is correct */
    }

    if(  ui2_year < 2000 )  /* Update to correct setting */
    {
        ui2_year = 2000;
        _convert_date_val_to_str(ui2_year,
                                 ui1_month,
                                 ui1_day,
                                 ps_date);
        return;
    }

    if(  ui2_year > (UINT16) (RTC_MAX_YEAR) )  /* Update to correct setting */
    {
        ui2_year = (UINT16)(RTC_MAX_YEAR);
        _convert_date_val_to_str(ui2_year,
                                 ui1_month,
                                 ui1_day,
                                 ps_date);
        return;

    }
}

/*----------------------------------------------------------------------------
 * Name: _force_correct_month
 *
 * Description: Give "YYYY/MM/DD", auto correct MM
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _force_correct_month(char* ps_date)
{
    UINT16    ui2_year;
    UINT8     ui1_month;
    UINT8     ui1_day;

    _convert_date_str_to_val(ps_date,
                             &ui2_year,
                             &ui1_month,
                             &ui1_day);

    if(  ui1_month >= 1 && ui1_month <= 12 )   /* Current setting is correct */
    {
        return;
    }

    if(  ui1_month < 1 )                      /* Update to correct setting */
    {
        ui1_month = 1;
        _convert_date_val_to_str(ui2_year,
                                 ui1_month,
                                 ui1_day,
                                 ps_date);
        return;
    }

    if(  ui1_month > 12 )                     /* Update to correct setting */
    {
        ui1_month = 12;
        _convert_date_val_to_str(ui2_year,
                                 ui1_month,
                                 ui1_day,
                                 ps_date);
        return;
    }
}

/*----------------------------------------------------------------------------
 * Name: _force_correct_day
 *
 * Description: Give "YYYY/MM/DD", auto correct DD
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _force_correct_day(char* ps_date)
{
    UINT16    ui2_year;
    UINT8     ui1_month;
    UINT8     ui1_day;
    BOOL     b_leap_year;

    _convert_date_str_to_val(ps_date,
                             &ui2_year,
                             &ui1_month,
                             &ui1_day);

    b_leap_year = c_dt_leap_yr( (TIME_T)ui2_year );

    if(ui1_month == 2 && b_leap_year)
    {
        if((ui1_day >= 1 && ui1_day <= 29))
        {   /* Correct Setting */
            return;
        }

        if(ui1_day < 1)                       /* Update to correct setting */
        {
            ui1_day = 1;
            _convert_date_val_to_str(ui2_year,
                                     ui1_month,
                                     ui1_day,
                                     ps_date);
            return;
        }
        if(ui1_day > 29)                      /* Update to correct setting */
        {
            ui1_day = 29;
            _convert_date_val_to_str(ui2_year,
                                     ui1_month,
                                     ui1_day,
                                     ps_date);
            return;
        }

        return;
    }

    if(ui1_month == 2 && (!b_leap_year))
    {
        if((ui1_day >= 1 && ui1_day <= 28))
        {   /* Correct Setting */
            return;
        }

        if(ui1_day < 1)                       /* Update to correct setting */
        {
            ui1_day = 1;
            _convert_date_val_to_str(ui2_year,
                                     ui1_month,
                                     ui1_day,
                                     ps_date);
            return;
        }
        if(ui1_day > 28)                      /* Update to correct setting */
        {
            ui1_day = 28;
            _convert_date_val_to_str(ui2_year,
                                     ui1_month,
                                     ui1_day,
                                     ps_date);
            return;
        }

        return;
    }

    if( ui1_month == 1  ||
        ui1_month == 3  ||
        ui1_month == 5  ||
        ui1_month == 7  ||
        ui1_month == 8  ||
        ui1_month == 10 ||
        ui1_month == 12 )
    {
        if((ui1_day >= 1 && ui1_day <= 31))
        {   /* Correct Setting */
            return;
        }

        if(ui1_day < 1)                       /* Update to correct setting */
        {
            ui1_day = 1;
            _convert_date_val_to_str(ui2_year,
                                     ui1_month,
                                     ui1_day,
                                     ps_date);
            return;
        }
        if(ui1_day > 31)                      /* Update to correct setting */
        {
            ui1_day = 31;
            _convert_date_val_to_str(ui2_year,
                                     ui1_month,
                                     ui1_day,
                                     ps_date);
            return;
        }

        return;
    }

    if( ui1_month == 4  ||
        ui1_month == 6  ||
        ui1_month == 9  ||
        ui1_month == 11 )
    {
        if((ui1_day >= 1 && ui1_day <= 30))
        {   /* Correct Setting */
            return;
        }

        if(ui1_day < 1)                       /* Update to correct setting */
        {
            ui1_day = 1;
            _convert_date_val_to_str(ui2_year,
                                     ui1_month,
                                     ui1_day,
                                     ps_date);
            return;
        }
        if(ui1_day > 30)                      /* Update to correct setting */
        {
            ui1_day = 30;
            _convert_date_val_to_str(ui2_year,
                                     ui1_month,
                                     ui1_day,
                                     ps_date);
            return;
        }

        return;
    }


    DBG_ERROR(("[MENU] Un-handled Date/Time condition"));
    return;
}

/*----------------------------------------------------------------------------
 * Name: _date_validate
 *
 * Description: Give "YYYY/MM/DD", check if it is a correct date string
 *
 * Inputs:
 *
 * Outputs: TRUE    - valid
 *          FALSE   - invalid
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _date_validate(char* ps_date)
{
    /* 2005/11/10 */
    /* 0123456789 */

    /* Rule 1:   char[0]+char[1]+char[2]+char[3] => number between 1970~2080
       Rule 2:   char[5]+char[6]                 => number between 01~12
       Rule 3:   char[8]+char[9]                 => if month == 2 & leap year , range 01~29
       Rule 4:                                      if month == 2 & ! leap year, range 01~28
       Rule 5:                                      if month = 1,3,5,7,8,10,12, range 01~31
       Rule 6:                                      if month = 4,6,9,11, range 01~30

    */
    INT32    i4_ret = MENUR_FAIL;
    CHAR     s_year[5];
    CHAR     s_month[3];
    CHAR     s_day[3];
    INT16    i2_year;
    INT8     i1_month;
    INT8     i1_day;
    BOOL     b_leap_year;

    /* Convert Year */
    s_year[0]  = ps_date[0];
    s_year[1]  = ps_date[1];
    s_year[2]  = ps_date[2];
    s_year[3]  = ps_date[3];
    s_year[4]  = '\0';
    i2_year    = (INT16) _atoi(s_year);

    /* Convert Month */
    s_month[0] = ps_date[5];
    s_month[1] = ps_date[6];
    s_month[2] = '\0';
    i1_month   = (INT8) _atoi(s_month);

    /* Convert Day */
    s_day[0]   = ps_date[8];
    s_day[1]   = ps_date[9];
    s_day[2]   = '\0';
    i1_day     = (INT8) _atoi(s_day);

    do
    {
        /* Rule 1 */
        if(! (i2_year >= 1970 && i2_year <= 2080) )
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        b_leap_year = c_dt_leap_yr( (TIME_T) i2_year );

        /* Rule 2 */
        if(! (i1_month >= 1 && i1_month <= 12) )
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        /* Rule 3 */
        if(i1_month == 2 && b_leap_year)
        {
            if(! (i1_day >= 1 && i1_day <= 29) )
            {
                i4_ret = MENUR_FAIL;
                break;
            }
        }

        /* Rule 4 */
        if(i1_month == 2 && (!b_leap_year) )
        {
            if(! (i1_day >= 1 && i1_day <= 28) )
            {
                i4_ret = MENUR_FAIL;
                break;
            }
        }

        /* Rule 5 */
        if(  (i1_month == 1  ||
              i1_month == 3  ||
              i1_month == 5  ||
              i1_month == 7  ||
              i1_month == 8  ||
              i1_month == 10 ||
              i1_month == 12)   )
        {
            if(! (i1_day >= 1 && i1_day <= 31) )
            {
                i4_ret = MENUR_FAIL;
                break;
            }
        }


        /* Rule 6 */
        if(  (i1_month == 4  ||
              i1_month == 6  ||
              i1_month == 9  ||
              i1_month == 11)   )
        {
            if(! (i1_day >= 1 && i1_day <= 30) )
            {
                i4_ret = MENUR_FAIL;
                break;
            }
        }

        i4_ret = MENUR_OK;  /* The date is OK */
    } while(0);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _time_validate
 *
 * Description: Give "HH:MM:SS", check if it is a correct time string
 *
 * Inputs:
 *
 * Outputs: TRUE    - valid
 *          FALSE   - invalid
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _time_validate(CHAR *ps_time)
{
    /* 12:30:50 */
    /* 01234567 */

    /* Rule 1:   char[0]+char[1] => number between 0~23
       Rule 2:   char[3]+char[4] => number between 0~59
       Rule 3:   char[6]+char[7] => number between 0~59 */
    INT32    i4_ret = MENUR_FAIL;
    CHAR     s_num[3];
    INT8     i1_num;

    do
    {
        /* Convert Hour */
        s_num[0] = ps_time[0];
        s_num[1] = ps_time[1];
        s_num[2] = '\0';
        i1_num = (INT8) _atoi(s_num);
        if(! (i1_num >= 0  &&  i1_num <= 23))
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        /* Convert Minute */
        s_num[0] = ps_time[3];
        s_num[1] = ps_time[4];
        s_num[2] = '\0';
        i1_num = (INT8) _atoi(s_num);
        if(! (i1_num >= 0  &&  i1_num <= 59))
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        /* Convert Second */
        s_num[0] = ps_time[6];
        s_num[1] = ps_time[7];
        s_num[2] = '\0';
        i1_num = (INT8) _atoi(s_num);
        if(! (i1_num >= 0  &&  i1_num <= 59))
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        /* Success */
        i4_ret = MENUR_OK;
    } while(0);

    return i4_ret;   /* The timer is set OK */
}


/*----------------------------------------------------------------------------
 * Name: _widget_default_proc_fct
 *
 * Description: Common widget proc fct for all widgets in this page.
 *
 *              Normally, it handles BTN_EXIT for menu_nav_back().
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _widget_default_proc_fct(HANDLE_T    h_widget,
                                 UINT32      ui4_msg,
                                 VOID*       param1,
                                 VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:

        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
            case BTN_RETURN:
                menu_nav_back();
                return WMPR_DONE;
            case BTN_CURSOR_UP:
                _chg_wgt_foucs(FALSE);
                ui4_msg = WGL_MSG_KEY_DOWN;
                break;
            case BTN_CURSOR_DOWN:
                _chg_wgt_foucs(TRUE);
                ui4_msg = WGL_MSG_KEY_DOWN;
                break;
            }
        }
        break;
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _lb_additional_item_proc_fct
 *
 * Description: Additional menu item proc fct
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _lb_additional_item_proc_fct(HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       param1,
                                          VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
            case BTN_CURSOR_LEFT:
                {
                    UINT16       ui2_idx;
                    MENU_ITEM_T* pt_menu_item;
                    _get_menu_item_data_by_widget(h_widget, &pt_menu_item);

                    if(pt_menu_item->u.t_list.pf_prev_idx != NULL)
                    {
                        ui2_idx = pt_menu_item->u.t_list.pf_prev_idx();
                        if(ui2_idx < pt_menu_item->u.t_list.ui2_elem_num)
                        {
                            menu_list_set_idx(h_widget, ui2_idx);
                        }
                    }
                    else
                    {
                        c_wgl_do_cmd(h_widget,
                                     WGL_CMD_LB_HLT_PREV_ELEM,
                                     WGL_PACK(FALSE),
                                     NULL);

                        menu_list_get_idx(h_widget, &ui2_idx);
                        pt_menu_item->u.t_list.pf_set_idx(ui2_idx);
                    }

                    c_wgl_repaint(h_widget, NULL, TRUE);
                }
                return WMPR_DONE;

            case BTN_CURSOR_RIGHT:
                {
                    UINT16       ui2_idx;
                    MENU_ITEM_T* pt_menu_item;
                    _get_menu_item_data_by_widget(h_widget, &pt_menu_item);

                    if(pt_menu_item->u.t_list.pf_next_idx != NULL)
                    {
                        ui2_idx = pt_menu_item->u.t_list.pf_next_idx();
                        if(ui2_idx < pt_menu_item->u.t_list.ui2_elem_num)
                        {
                            menu_list_set_idx(h_widget, ui2_idx);
                        }
                    }
                    else
                    {
                        c_wgl_do_cmd(h_widget,
                                     WGL_CMD_LB_HLT_NEXT_ELEM,
                                     WGL_PACK(FALSE),
                                     NULL);

                        menu_list_get_idx(h_widget, &ui2_idx);
                        pt_menu_item->u.t_list.pf_set_idx(ui2_idx);
                    }

                    c_wgl_repaint(h_widget, NULL, TRUE);
                }
                return WMPR_DONE;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }

    return _widget_default_proc_fct(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _eb_dt_date_util_increase_cursor_pos
 *
 * Description: Increase the cursor of the date EB.
 *
 *              Note. This is a special purpose function for the EB only.
 *                    Multiple instances not supported.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
/* EB_DT_DATE utility functions implemented at here */
static VOID _eb_dt_date_util_increase_cursor_pos()
{
    /* 1980/11/10 */
    /* 0123456789 */

    UINT8    ui1_old_pos;

    ui1_old_pos = gui1_eb_date_cursor_pos;

    if(ui1_old_pos == 3)
    {
        gui1_eb_date_cursor_pos = 5;
    }
    else if(ui1_old_pos == 6)
    {
        gui1_eb_date_cursor_pos = 8;
    }
    else if(ui1_old_pos == 9)
    {
        /* No Change */
    }
    else
    {
        gui1_eb_date_cursor_pos++;
    }

    /* Set the widget's cursor position */

    c_wgl_do_cmd(h_eb_date,
                 WGL_CMD_EB_SET_CURSOR_POS,
                 WGL_PACK(gui1_eb_date_cursor_pos),
                 WGL_PACK(NULL));

}

/*----------------------------------------------------------------------------
 * Name: _eb_dt_date_util_decrease_cursor_pos
 *
 * Description: Decrease the cursor of the date EB.
 *
 *              Note. This is a special purpose function for the EB only.
 *                    Multiple instances not supported.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _eb_dt_date_util_decrease_cursor_pos()
{
    /* 1980/11/10 */
    /* 0123456789 */

    UINT8    ui1_old_pos;

    ui1_old_pos = gui1_eb_date_cursor_pos;

    if(ui1_old_pos == 0)
    {
        /* No Change */
    }
    else if(ui1_old_pos == 5)
    {
        gui1_eb_date_cursor_pos = 3;
    }
    else if(ui1_old_pos == 8)
    {
        gui1_eb_date_cursor_pos = 6;
    }
    else
    {
        gui1_eb_date_cursor_pos--;
    }

    /* Set the widget's cursor position */

    c_wgl_do_cmd(h_eb_date,
                 WGL_CMD_EB_SET_CURSOR_POS,
                 WGL_PACK(gui1_eb_date_cursor_pos),
                 WGL_PACK(NULL));

}

/*----------------------------------------------------------------------------
 * Name: _eb_dt_date_util_update_string_to_widget
 *
 * Description: Update the current edited date setting string to widget.
 *
 *              Note. This is a special purpose function for the EB only.
 *                    Multiple instances not supported.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _eb_dt_date_util_update_string_to_widget(VOID)
{
    UTF16_T    w2s_date[14];
    UINT8      ui1_date_len;

    ui1_date_len = (UINT8) c_strlen(s_g_edit_date);
    c_uc_ps_to_w2s(s_g_edit_date, w2s_date, ui1_date_len);

    c_wgl_do_cmd(h_eb_date,
                WGL_CMD_EB_SET_TEXT,
                WGL_PACK(w2s_date),
                WGL_PACK(ui1_date_len));

}

/*----------------------------------------------------------------------------
 * Name: _eb_dt_date_util_input_current_pos
 *
 * Description: Do the input procedure when user press ui1_digit.
 *
 *              Note. This is a special purpose function for the EB only.
 *                    Multiple instances not supported.
 *
 * Inputs:  ui1_digit - The key user's pressed. (Numeric format)
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _eb_dt_date_util_input_current_pos(UINT8  ui1_digit)
{
    /* 2006/01/28 */
    /* 0123456789 */

    CHAR          s_bak_edit_date[11];

    /* 1. copy dup */
    c_strncpy(s_bak_edit_date, s_g_edit_date, 10);   /* 2006/01/28 */
    s_bak_edit_date[10] = '\0';

    /* Year - Special Processing - Start */

    if(gui1_eb_date_cursor_pos == 0)
    {
        /* Key Mapping */ /* Map 0,1,3-9 to 2 */
        if( ui1_digit == 0 ||
            ui1_digit == 1 ||
            ui1_digit == 3 ||
            ui1_digit == 4 ||
            ui1_digit == 5 ||
            ui1_digit == 6 ||
            ui1_digit == 7 ||
            ui1_digit == 8 ||
            ui1_digit == 9 )
        {
            ui1_digit = 2;
        }

        if(ui1_digit == 2)
        {
            s_bak_edit_date[0] = 2 + '0';   /* User's input */
            s_bak_edit_date[1] = 0 + '0';   /* Force update */
        }

        if(ui1_digit == 1)
        {
            s_bak_edit_date[0] = 1 + '0';   /* User's input */
            s_bak_edit_date[1] = 9 + '0';   /* Force update */
        }


        _force_correct_year(s_bak_edit_date);
        _force_correct_month(s_bak_edit_date);
        _force_correct_day(s_bak_edit_date);


    }

    if(gui1_eb_date_cursor_pos == 1)
    {
        /* Key Mapping */ /* Map 1-8,9 to 0 */
        if( ui1_digit == 1 ||
            ui1_digit == 2 ||
            ui1_digit == 3 ||
            ui1_digit == 4 ||
            ui1_digit == 5 ||
            ui1_digit == 6 ||
            ui1_digit == 7 ||
            ui1_digit == 8 ||
            ui1_digit == 9 )
        {
            ui1_digit = 0;
        }

        if(ui1_digit == 0)
        {
            s_bak_edit_date[0] = 2 + '0';   /* Force update */
            s_bak_edit_date[1] = 0 + '0';   /* user's input */
        }

        if(ui1_digit == 9)
        {
            s_bak_edit_date[0] = 1 + '0';   /* Force update */
            s_bak_edit_date[1] = 9 + '0';   /* user's input */
        }


        _force_correct_year(s_bak_edit_date);
        _force_correct_month(s_bak_edit_date);
        _force_correct_day(s_bak_edit_date);


    }

    /* Year - Special Processing - End */

    /* general processing - Start */

    if(gui1_eb_date_cursor_pos == 2 || gui1_eb_date_cursor_pos == 3 ||
       gui1_eb_date_cursor_pos == 5 || gui1_eb_date_cursor_pos == 6 ||
       gui1_eb_date_cursor_pos == 8 || gui1_eb_date_cursor_pos == 9 )
    {
        s_bak_edit_date[gui1_eb_date_cursor_pos] = (CHAR) (ui1_digit + '0');


        _force_correct_year(s_bak_edit_date);
        _force_correct_month(s_bak_edit_date);
        _force_correct_day(s_bak_edit_date);

    }

    /* general processing - End */


    /* Assume the date is OK now !! */

        c_strncpy(s_g_edit_date, s_bak_edit_date, 10);
        s_g_edit_date[10] = '\0';
        _eb_dt_date_util_update_string_to_widget();
        _eb_dt_date_util_increase_cursor_pos();


/*
    s_g_edit_date[gui1_eb_date_cursor_pos] = ui1_digit + '0';
    _eb_dt_date_util_update_string_to_widget();
    _eb_dt_date_util_increase_cursor_pos();
*/
}


/*----------------------------------------------------------------------------
 * Name: _eb_dt_date_proc_fct
 *
 * Description: The date EB's wdgt proc fct.
 *
 *              Note. When user pressed 0~9 digits, it will do save the setting.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _eb_dt_date_proc_fct(HANDLE_T    h_widget,
                                  UINT32      ui4_msg,
                                  VOID*       param1,
                                  VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
            case BTN_CURSOR_RIGHT:
                _eb_dt_date_util_increase_cursor_pos();
                c_wgl_repaint(h_widget, NULL, TRUE);
                return WMPR_DONE;

            case BTN_CURSOR_LEFT:
                _eb_dt_date_util_decrease_cursor_pos();
                c_wgl_repaint(h_widget, NULL, TRUE);
                return WMPR_DONE;

            case BTN_DIGIT_0:
            case BTN_DIGIT_1:
            case BTN_DIGIT_2:
            case BTN_DIGIT_3:
            case BTN_DIGIT_4:
            case BTN_DIGIT_5:
            case BTN_DIGIT_6:
            case BTN_DIGIT_7:
            case BTN_DIGIT_8:
            case BTN_DIGIT_9:
                _eb_dt_date_util_input_current_pos((UINT8)(ui4_keycode - BTN_DIGIT_0));
                _date_time_confirm_update();
                c_wgl_repaint(h_widget, NULL, TRUE);
                return WMPR_DONE;

            case BTN_SELECT:
                /*
                _date_time_confirm_update();
                c_wgl_set_focus(h_lb_dt_mode, TRUE);
                */
                /* Do not need to do repaint, because the call-back time will do that*/
                return WMPR_DONE;

            case BTN_PREV_PRG:
            case BTN_RETURN:
                menu_nav_back();
                return WMPR_DONE;
            }

        }
        break;
    default:
        break;
    }


    return _widget_default_proc_fct(h_widget, ui4_msg, param1, param2);
}


/*----------------------------------------------------------------------------
 * Name: _eb_dt_time_util_increase_cursor_pos
 *
 * Description: Increase the cursor of the time EB.
 *
 *              Multiple instances SUPPORTED.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
/* EB_DT_TIME utility functions implemented at here */
static VOID _eb_dt_time_util_increase_cursor_pos(HANDLE_T   h_eb_time)
{
    /* 22:11:00 */
    /* 01234567 */

    INT32                 i4_ret;
    UINT8                 ui1_old_pos;
    TIMER_EDIT_DATA_T*    pt_timer_edit_data;

    i4_ret = _date_time_get_attach_data(h_eb_time,
                                        &pt_timer_edit_data);
    MENU_LOG_ON_FAIL(i4_ret);

    ui1_old_pos = *(pt_timer_edit_data->pui1_cursor_pos);

    if(ui1_old_pos == 1)
    {
        *(pt_timer_edit_data->pui1_cursor_pos) = 3;
    }
    else if(ui1_old_pos == 4)
    {
        *(pt_timer_edit_data->pui1_cursor_pos) = 6;
    }
    else if(ui1_old_pos == 7)
    {
        /* No Change */
    }
    else
    {
        (*(pt_timer_edit_data->pui1_cursor_pos))++;
    }

    /* Set the widget's cursor position */

    c_wgl_do_cmd(h_eb_time,
                 WGL_CMD_EB_SET_CURSOR_POS,
                 WGL_PACK(  *(pt_timer_edit_data->pui1_cursor_pos)  ),
                 WGL_PACK(NULL));

}

/*----------------------------------------------------------------------------
 * Name: _eb_dt_time_util_decrease_cursor_pos
 *
 * Description: Decrease the cursor of the time EB.
 *
 *              Multiple instances SUPPORTED.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _eb_dt_time_util_decrease_cursor_pos(HANDLE_T   h_eb_time)
{
    /* 22:11:00 */
    /* 01234567 */

    INT32                 i4_ret;
    UINT8                 ui1_old_pos;
    TIMER_EDIT_DATA_T*    pt_timer_edit_data;

    i4_ret = _date_time_get_attach_data(h_eb_time,
                                        &pt_timer_edit_data);
    MENU_LOG_ON_FAIL(i4_ret);

    ui1_old_pos = *(pt_timer_edit_data->pui1_cursor_pos);

    if(ui1_old_pos == 0)
    {
        /* No Change */
    }
    else if(ui1_old_pos == 3)
    {
        *(pt_timer_edit_data->pui1_cursor_pos) = 1;
    }
    else if(ui1_old_pos == 6)
    {
        *(pt_timer_edit_data->pui1_cursor_pos) = 4;
    }
    else
    {
        (*(pt_timer_edit_data->pui1_cursor_pos))--;
    }

    /* Set the widget's cursor position */

    c_wgl_do_cmd(h_eb_time,
                 WGL_CMD_EB_SET_CURSOR_POS,
                 WGL_PACK(  *(pt_timer_edit_data->pui1_cursor_pos)  ),
                 WGL_PACK(NULL));

}

/*----------------------------------------------------------------------------
 * Name: _eb_dt_time_util_update_string_to_widget
 *
 * Description: Update the current edited time setting string to widget.
 *
 *              Multiple instances SUPPORTED.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _eb_dt_time_util_update_string_to_widget(HANDLE_T   h_eb_time)
{
    INT32                 i4_ret;
    UTF16_T               w2s_time[14];
    UINT8                 ui1_time_len;
    TIMER_EDIT_DATA_T*    pt_timer_edit_data;

    i4_ret = _date_time_get_attach_data(h_eb_time,
                                        &pt_timer_edit_data);
    MENU_LOG_ON_FAIL(i4_ret);

    ui1_time_len = (UINT8) c_strlen( pt_timer_edit_data->ps_g_time );
    c_uc_ps_to_w2s(pt_timer_edit_data->ps_g_time, w2s_time, ui1_time_len);

    c_wgl_do_cmd(h_eb_time,
                WGL_CMD_EB_SET_TEXT,
                WGL_PACK(w2s_time),
                WGL_PACK(ui1_time_len));

}

/*----------------------------------------------------------------------------
 * Name: _eb_dt_time_util_input_current_pos
 *
 * Description: Do the input procedure when user press ui1_digit.
 *
 *              Multiple instances SUPPORTED.
 *
 * Inputs:  ui1_digit - The key user's pressed. (Numeric format)
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _eb_dt_time_util_input_current_pos(HANDLE_T  h_eb_time,
                                               UINT8     ui1_digit)
{
/* Rough algo. */
/*
1. copy dup
2. update dup
3. validate dup
4. if(ok)
   update to real
5. if not (ok)
   =>search a proper digit
      if found
      => update to real
      if not found
      => abondon

*/
    INT32              i4_ret;
    UINT8              ui1_i;
    UINT8              ui1_new_digit;
    CHAR               s_bak_edit_time[9];
    TIMER_EDIT_DATA_T* pt_timer_edit_data;

    i4_ret = _date_time_get_attach_data(h_eb_time,
                                        &pt_timer_edit_data);
    MENU_LOG_ON_FAIL(i4_ret);

    /* 1. copy dup */
    c_strncpy(s_bak_edit_time, pt_timer_edit_data->ps_g_time, 8);   /* 12:30:50 */
    s_bak_edit_time[8] = '\0';

    /* 2. update dup */
    if (   (*(pt_timer_edit_data->pui1_cursor_pos)) >= 9)   /* range protect */
    {
        *(pt_timer_edit_data->pui1_cursor_pos) = 8;
    }

    s_bak_edit_time[  *(pt_timer_edit_data->pui1_cursor_pos) ] = (CHAR)(ui1_digit + '0');

    /* 3. validate dup */
    i4_ret = _time_validate(s_bak_edit_time);

    if(i4_ret == MENUR_OK)
    {
        /* 4. if(ok) */

        /* update to real */
        c_strncpy(pt_timer_edit_data->ps_g_time, s_bak_edit_time, 8);
        pt_timer_edit_data->ps_g_time[8] = '\0';
        _eb_dt_time_util_update_string_to_widget(h_eb_time);
        _eb_dt_time_util_increase_cursor_pos(h_eb_time);
        return ;
    }

    /* 5. if not (ok) */


    /* Special case handling */
    /* 17:11:22 , user may enter '2' or above at the first digit. => auto correct to 23:11:22 */

    if (*(pt_timer_edit_data->pui1_cursor_pos) == 0 &&
        (ui1_digit >= 2 && ui1_digit <= 9))
    {
        /* let it be 2 */
        ui1_digit = 2;

        /* Force update the first digit to 2 */
        s_bak_edit_time[0] = 2 + '0';

        /* Update the '27' => '23' */
        s_bak_edit_time[1] = 3 + '0';

        /* update to real */
        c_strncpy(pt_timer_edit_data->ps_g_time, s_bak_edit_time, 8);
        pt_timer_edit_data->ps_g_time[8] = '\0';
        _eb_dt_time_util_update_string_to_widget(h_eb_time);
        _eb_dt_time_util_increase_cursor_pos(h_eb_time);
        return ;

    }


    /* user's input is still invalid */
    /* find a proper digit if possible */

    for(ui1_i = 1 ; ui1_i <= 9 ; ui1_i++)
    {
        ui1_new_digit = (UINT8)((ui1_digit + 10 - ui1_i) % 10);

        if (   (*(pt_timer_edit_data->pui1_cursor_pos)) >= 9)   /* range protect */
        {
            *(pt_timer_edit_data->pui1_cursor_pos) = 8;
        }

        s_bak_edit_time[  *(pt_timer_edit_data->pui1_cursor_pos)  ] = (CHAR)(ui1_new_digit + '0');
        i4_ret = _time_validate(s_bak_edit_time);

        /* if founded */

        if(i4_ret == MENUR_OK)
        {
            /* update to real */
            c_strncpy(pt_timer_edit_data->ps_g_time, s_bak_edit_time, 8);
            pt_timer_edit_data->ps_g_time[8] = '\0';
            _eb_dt_time_util_update_string_to_widget(h_eb_time);
            _eb_dt_time_util_increase_cursor_pos(h_eb_time);
            return ;
        }

    }


    /* does not found a proper digit */
    /* abondon it */

    _eb_dt_time_util_increase_cursor_pos(h_eb_time);
    return ;

}

/*----------------------------------------------------------------------------
 * Name: _eb_dt_time_proc_fct
 *
 * Description: The time EB's wdgt proc fct.
 *
 *              Note. When user pressed 0~9 digits, it will do save the setting.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _eb_dt_time_proc_fct(HANDLE_T    h_widget,
                                  UINT32      ui4_msg,
                                  VOID*       param1,
                                  VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
            case BTN_CURSOR_RIGHT:
                _eb_dt_time_util_increase_cursor_pos(h_widget);
                c_wgl_repaint(h_widget, NULL, TRUE);
                return WMPR_DONE;

            case BTN_CURSOR_LEFT:
                _eb_dt_time_util_decrease_cursor_pos(h_widget);
                c_wgl_repaint(h_widget, NULL, TRUE);
                return WMPR_DONE;

            case BTN_DIGIT_0:
            case BTN_DIGIT_1:
            case BTN_DIGIT_2:
            case BTN_DIGIT_3:
            case BTN_DIGIT_4:
            case BTN_DIGIT_5:
            case BTN_DIGIT_6:
            case BTN_DIGIT_7:
            case BTN_DIGIT_8:
            case BTN_DIGIT_9:
                _eb_dt_time_util_input_current_pos(h_widget, (UINT8) (ui4_keycode - BTN_DIGIT_0));

                /* When user enters a digit, update the system date/time immediately */
                _date_time_confirm_update();
                c_wgl_repaint(h_widget, NULL, TRUE);

                return WMPR_DONE;

            case BTN_SELECT:
                return WMPR_DONE;

            case BTN_PREV_PRG:
            case BTN_RETURN:
                menu_nav_back();
                return WMPR_DONE;
            }
        }
        break;
    default:
        break;
    }


    return _widget_default_proc_fct(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _eb_time_on_notify
 *
 * Description: if time EB is focused, reset cursor position.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _eb_time_on_notify(WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    if(b_g_refreshing == TRUE)
    {
        return    WMPR_DONE;
    }

    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_GL_GET_FOCUS:
        {
            /* Reset cursor position */
            gui1_eb_time_cursor_pos = 0;
        }
        break;
    default:
        break;
    }
    return WMPR_DONE;
}

/*----------------------------------------------------------------------------
 * Name: _eb_date_on_notify
 *
 * Description: if date EB is focused, reset cursor position.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _eb_date_on_notify(WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    if(b_g_refreshing == TRUE)
    {
        return    WMPR_DONE;
    }

    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_GL_GET_FOCUS:
        {
            /* Reset cursor position */
            gui1_eb_date_cursor_pos = 0;

        }
        break;
    default:
        break;
    }
    return WMPR_DONE;
}

/*----------------------------------------------------------------------------
 * Name: _lb_additional_item_on_notify
 *
 * Description: if power off EB  focused, reset cursor position.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _lb_additional_item_on_notify(WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    if(b_g_refreshing == TRUE)
    {
        return    WMPR_DONE;
    }

    return WMPR_DONE;
}


/*----------------------------------------------------------------------------
 * Name: _cnt_frm_proc_fct
 *
 * Description: Dispatch all notifications to corresponding widgets.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _cnt_frm_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
            HANDLE_T h_source = (HANDLE_T)param1;
            WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)param2;

            if(h_source == h_eb_date)
            {
                _eb_date_on_notify(pt_nfy_data);
            }
            else if(h_source == h_eb_time)
            {
                _eb_time_on_notify(pt_nfy_data);
            }
            else if(h_source == h_lb_additional)
            {
                _lb_additional_item_on_notify(pt_nfy_data);
            }
            else
            {
                /* Garbage notify */
            }
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

#if 0
/*----------------------------------------------------------------------------
 * Name: _set_nav_chain
 *
 * Description: Set the navigation chain. (utility function)
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _set_nav_chain(HANDLE_T  *ph_chain,
                            INT8      i1_chain_len)
{
    INT32                 i4_ret;
    WGL_KEY_LINK_T        at_key_lnk[4];
    INT8                  i1_i = 0;

    for (i1_i = 0; i1_i < i1_chain_len; i1_i++)
    {
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = ph_chain[i1_i == 0 ? i1_chain_len-1: i1_i-1];
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = ph_chain[i1_i == i1_chain_len-1 ? 0: i1_i+1];
        i4_ret = c_wgl_set_navigation(ph_chain[i1_i], 2, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _set_nav
 *
 * Description: Set the navigation for this page.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _set_nav(VOID)
{
    INT8         i1_chain_len = 0;

    /* Additional item check */
    if(gui1_additional_item_num != 0)
    {
        ah_chain[i1_chain_len++] = h_lb_additional;
        apw2s_help_tip[i1_chain_len - 1] = MENU_TEXT(MLM_MENU_KEY_EMPTY);
    }

    menu_get_homebar_handle(&h_homebar);
    ah_chain[i1_chain_len++] = h_homebar;
    apw2s_help_tip[i1_chain_len - 1] = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR);
    menu_get_backbar_handle(&h_backbar);
    ah_chain[i1_chain_len++] = h_backbar;
    apw2s_help_tip[i1_chain_len - 1] = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR);
    ah_chain[i1_chain_len++] = h_eb_date;
    apw2s_help_tip[i1_chain_len - 1] = MENU_TEXT(MLM_MENU_KEY_TIME_MODE_CUR_DATE);
    ah_chain[i1_chain_len++] = h_eb_time;
    apw2s_help_tip[i1_chain_len - 1] = MENU_TEXT(MLM_MENU_KEY_TIME_MODE_CUR_TIME);

    i1_g_chain_len = i1_chain_len;

    return MENUR_OK;
}

static INT32 _chg_wgt_foucs(BOOL b_next)
{
    HANDLE_T     h_cur_wgt = NULL_HANDLE;
    INT8         i1_idx = 0;

    c_wgl_get_focus(&h_cur_wgt);

    for (i1_idx = 0; i1_idx < i1_g_chain_len; i1_idx++)
    {
        if (h_cur_wgt == ah_chain[i1_idx])
        {
            if (b_next == TRUE)
            {
                i1_idx = (i1_idx + 1) % i1_g_chain_len;
            }
            else
            {
                i1_idx = (i1_idx > 0) ? i1_idx - 1 : i1_g_chain_len - 1;
            }
            c_wgl_set_focus(ah_chain[i1_idx], WGL_SYNC_AUTO_REPAINT);
            menu_hide_help_tip();
            menu_set_and_trigger_help_tip(apw2s_help_tip[i1_idx]);
            break;
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _chg_theme
 *
 * Description: Change the theme.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _chg_theme(VOID)
{
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _chg_help_lst
 *
 * Description: Change the help list.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _chg_help_lst(VOID)
{
#if 0   /* If needed, change to use help tip */
    INT32 i4_ret;
    MENU_HELP_LST_BUCKET_T at_help_back[] =
    {
        {h_g_menu_img_btn_select, MLM_MENU_KEY_HELP_SELECT},
        {h_g_menu_img_btn_exit, MLM_MENU_KEY_HELP_BACK}
    };

    i4_ret = menu_main_set_help(at_help_back,
                                (UINT16)(sizeof(at_help_back) / sizeof(at_help_back[0])));
    MENU_CHK_FAIL(i4_ret);
#endif
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _chg_date_time_color
 *
 * Description: Change the color of date time.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _chg_date_time_color(HANDLE_T      h_widget,
                                  BOOL          b_enable,
                                  BOOL          b_repaint)
{
    INT32 i4_ret;
    WGL_COLOR_INFO_T    t_clr_info;

    if (b_enable == FALSE)
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_bk1_txt_disable;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_bk1_txt_disable;
        t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_bk1_txt_disable;
    }
    else
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_bk1_txt_disable;
    }

    /* set timg title text color */
    i4_ret = c_wgl_do_cmd (h_widget,
                           WGL_CMD_GL_SET_BDR_COLOR,
                           (VOID*)WGL_CLR_BDR_TIMG_TITLE_TEXT,
                           &t_clr_info);
    MENU_CHK_FAIL(i4_ret);

    /* Set txt color */
    i4_ret = c_wgl_do_cmd (h_widget,
                           WGL_CMD_GL_SET_COLOR,
                           (VOID*)WGL_CLR_TEXT,
                           &t_clr_info);
    MENU_CHK_FAIL(i4_ret);

    if (b_repaint == TRUE)
    {
        i4_ret = c_wgl_repaint (h_widget, NULL, TRUE);
        MENU_CHK_FAIL(i4_ret);
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _do_update_date_time_widget_text
 *
 * Description: Get the current time and flush it to the date EB, time EB.
 *
 *              And also save the string.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _do_update_date_time_widget_text(VOID* pv_data,
                                             SIZE_T  z_data_size)
{
    /* GET Current Local Time and write to h_eb_date, h_eb_time */
    DTG_T      t_dtg={0};
    UTF16_T    w2s_date[14]={0};
    UTF16_T    w2s_time[14]={0};
    UINT8       ui1_date_len=0;
    UINT8       ui1_time_len=0;
    INT8       i1_repaint=0;

    /* pv_data[0] to indicate repaint or not */
    i1_repaint = ((INT8 *)pv_data)[0];

    /* Get Current Time (Local Time) */
    c_dt_utc_sec_to_loc_dtg(c_dt_get_utc(NULL,NULL),
                            &t_dtg);

    /* Save Current Time */
    c_memcpy(&t_g_backup_datetime, &t_dtg, sizeof(DTG_T));


    /* Save/Convert Current Time to String */
    _convert_date_val_to_str(t_dtg.ui2_yr, t_dtg.ui1_mo,  t_dtg.ui1_day,  s_g_edit_date);
    _convert_time_val_to_str(t_dtg.ui1_hr, t_dtg.ui1_min, t_dtg.ui1_sec, s_g_edit_time);

    ui1_date_len = (UINT8) c_strlen(s_g_edit_date);
    ui1_time_len = (UINT8) c_strlen(s_g_edit_time);

    c_uc_ps_to_w2s(s_g_edit_date, w2s_date, (UINT32) ui1_date_len);
    c_uc_ps_to_w2s(s_g_edit_time, w2s_time, (UINT32) ui1_time_len);

    c_wgl_do_cmd(h_eb_date,
                WGL_CMD_EB_SET_TEXT,
                WGL_PACK(w2s_date),
                WGL_PACK(ui1_date_len));

    c_wgl_do_cmd(h_eb_time,
                WGL_CMD_EB_SET_TEXT,
                WGL_PACK(w2s_time),
                WGL_PACK(ui1_time_len));

    /* Set the widget's cursor position */

    c_wgl_do_cmd(h_eb_date,
                 WGL_CMD_EB_SET_CURSOR_POS,
                 WGL_PACK(gui1_eb_date_cursor_pos),
                 WGL_PACK(NULL));

    c_wgl_do_cmd(h_eb_time,
                 WGL_CMD_EB_SET_CURSOR_POS,
                 WGL_PACK(gui1_eb_time_cursor_pos),
                 WGL_PACK(NULL));

    /* Use pv_data[0] == 1 to indicate repaint */
    /*     pv_data[0] == 0 to indicate don't repaint */


    if(i1_repaint == 1)
    {
    c_wgl_repaint(h_eb_date, NULL, TRUE);
    c_wgl_repaint(h_eb_time, NULL, TRUE);
    }
    else
    {

    }

    /* Maximum UTC Check */
    _maximum_utc_range_check();

}

/*----------------------------------------------------------------------------
 * Name: _timer_refresh_nfy_fct
 *
 * Description: Timer's nfy fct, do update the widget text.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _timer_refresh_nfy_fct(HANDLE_T  h_timer,
                                  VOID*     pv_tag)
{
    INT8   i1_repaint;

    i1_repaint = 1;

    menu_async_invoke(_do_update_date_time_widget_text, (VOID *) &i1_repaint, 1, FALSE);
}

/*----------------------------------------------------------------------------
 * Name: _timer_refresh_start
 *
 * Description: Enable timer.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _timer_refresh_start(VOID)
{
    c_timer_start(h_timer_refresh,
                  TIMER_REFRESH_DELAY,
                  X_TIMER_FLAG_REPEAT,
                  _timer_refresh_nfy_fct,
                  NULL);
}

/*----------------------------------------------------------------------------
 * Name: _timer_refresh_stop
 *
 * Description: Disable timer.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _timer_refresh_stop(VOID)
{
    c_timer_stop(h_timer_refresh);
}

/*----------------------------------------------------------------------------
 * Name: _date_time_confirm_update
 *
 * Description: Update the current user's edited date/time setting to
 *
 *              the system.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
/* Update the Date/Time Only */
static VOID _date_time_confirm_update(VOID)
{
    /* 0. Do validate, log it if fail */
    /* 1. Prepare t_dtg_local & t_dtg_utc */
    /* 2. call convert t_dtg_local to t_dtg_utc */
    /* 3. call convert t_dtg_utc to second */
    /* 4. call set_utc to set current time */

    INT32     i4_ret;
    DTG_T     t_dtg_local;
    DTG_T     t_dtg_utc;
    UINT16    ui2_yr;
    UINT8     ui1_mo;      /* 1-12, month of the year. */
    UINT8     ui1_day;     /* 1-31, day of the month. */
    UINT8     ui1_hr;      /* 0-23 */
    UINT8     ui1_min;     /* 0-59 */
    UINT8     ui1_sec;     /* 0-59 */
    TIME_T    t_utc_sec;

    c_memset(&t_dtg_local, 0, sizeof(DTG_T));
    c_memset(&t_dtg_utc, 0, sizeof(DTG_T));

    /* 0. Do validation, log it if fail */

    i4_ret = _date_validate(s_g_edit_date);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _time_validate(s_g_edit_time);
    MENU_LOG_ON_FAIL(i4_ret);

    /* 1. Prepare t_dtg_local & t_dtg_utc */

    _convert_date_str_to_val(s_g_edit_date,
                             &ui2_yr,
                             &ui1_mo,
                             &ui1_day);

    _convert_time_str_to_val(s_g_edit_time,
                             &ui1_hr,
                             &ui1_min,
                             &ui1_sec);

    t_dtg_local.ui2_yr    = ui2_yr;
    t_dtg_local.ui1_mo    = ui1_mo;
    t_dtg_local.ui1_day   = ui1_day;
    t_dtg_local.ui1_hr    = ui1_hr;
    t_dtg_local.ui1_min   = ui1_min;
    t_dtg_local.ui1_sec   = ui1_sec;
    t_dtg_local.ui1_dow   = 0;
    t_dtg_local.b_dst     = t_g_backup_datetime.b_dst;
    t_dtg_local.b_gmt     = FALSE;     /* Indicates this is a localtime */

    t_dtg_utc.b_dst       = t_g_backup_datetime.b_dst;
    t_dtg_utc.b_gmt       = TRUE;

    /* 2. call convert t_dtg_local to t_dtg_utc */

    c_dt_conv_utc_local(&t_dtg_local, &t_dtg_utc);

    /* 3. call convert t_dtg_utc to second */

    t_utc_sec = c_dt_dtg_to_sec(&t_dtg_utc);

    /* 4. call set_utc to set current time */

    /* Check valid minimum TIME */
    if(t_utc_sec < APP_RTC_LOW_BOUNDARY)
    {
        t_utc_sec = APP_RTC_LOW_BOUNDARY;
    }

    c_dt_set_utc(t_utc_sec, 0);

    /* Remember to update to MW about the timer setting */

    a_cfg_update_timer_power();

}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32    i4_ret = 0;
    WGL_COLOR_INFO_T    t_clr_info;
    TIMER_EDIT_DATA_T*  pt_timer_current;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    /* Additional Item Check: for Time Zone purpose.. etc */

    do
    {
        if(pv_create_data != NULL)
        {
            /* Additional menu_item founded */
            c_memcpy(&t_menu_additional_item, (MENU_ITEM_T *) pv_create_data, sizeof(MENU_ITEM_T));

            if(t_menu_additional_item.e_item_type != MENU_ITEM_TYPE_LIST)
            {
                return MENUR_CANT_CREATE_WIDGET;
            }

            i4_ret = menu_list_create(h_cnt_frm,
                                      gui1_additional_item_num,
                                      t_menu_additional_item.u.t_list.ui2_elem_num,
                                      _lb_additional_item_proc_fct,
                                      &h_lb_additional);

            MENU_CHK_FAIL(i4_ret);

            menu_list_chg_lang(h_lb_additional,
                               t_menu_additional_item.ui2_msgid_title,
                               t_menu_additional_item.u.t_list.ui2_msgid_elem_first,
                               t_menu_additional_item.u.t_list.ui2_msgid_elem_last);

            /* Attach the menuitem on the widget */

            c_wgl_do_cmd(h_lb_additional,
                         WGL_CMD_GL_SET_ATTACH_DATA,
                         WGL_PACK(&t_menu_additional_item),
                         NULL);

            /* Increase the additional item numbers */
            gui1_additional_item_num++;
        }
    } while(0);

    /* Date String in EB */
    i4_ret = menu_edit_create(h_cnt_frm,
                              COMMON_DATE_TIME_DATE_EB_IDX + gui1_additional_item_num,
                              FALSE,
                              _eb_dt_date_proc_fct,
                              &h_eb_date);

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(h_eb_date,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)10),
                          NULL);
    MENU_CHK_FAIL(i4_ret);


    /* Set EB Attr */
    i4_ret = c_wgl_do_cmd(h_eb_date,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));
    MENU_CHK_FAIL(i4_ret);

    /* Set EB Enable Cursor Highlight */
    i4_ret = c_wgl_do_cmd(h_eb_date,
                          WGL_CMD_EB_ENABLE_CURSOR_HT,
                          WGL_PACK(TRUE),
                          WGL_PACK(NULL));
    MENU_CHK_FAIL(i4_ret);

    /* Set EB Cursor Color */

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_highlight_cursor;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_highlight_cursor;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_highlight_cursor;

    i4_ret = c_wgl_do_cmd(h_eb_date,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_EB_CURSOR),
                          WGL_PACK(&t_clr_info));
    MENU_CHK_FAIL(i4_ret);

    menu_edit_chg_lang(h_eb_date,
                       MLM_MENU_KEY_TIME_MODE_CUR_DATE);

    /* ------------------------------------------------------------------------ */

    /* Time String in EB */

    i4_ret = menu_edit_create(h_cnt_frm,
                              COMMON_DATE_TIME_TIME_EB_IDX + gui1_additional_item_num,
                              FALSE,
                              _eb_dt_time_proc_fct,
                              &h_eb_time);

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(h_eb_time,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)8),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set EB Attr */
    i4_ret = c_wgl_do_cmd(h_eb_time,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));
    MENU_CHK_FAIL(i4_ret);

    /* Set EB Enable Cursor Highlight */
    i4_ret = c_wgl_do_cmd(h_eb_time,
                          WGL_CMD_EB_ENABLE_CURSOR_HT,
                          WGL_PACK(TRUE),
                          WGL_PACK(NULL));
    MENU_CHK_FAIL(i4_ret);

    /* Set EB Cursor Color */

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_highlight_cursor;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_highlight_cursor;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_highlight_cursor;

    i4_ret = c_wgl_do_cmd(h_eb_time,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_EB_CURSOR),
                          WGL_PACK(&t_clr_info));
    MENU_CHK_FAIL(i4_ret);

    menu_edit_chg_lang(h_eb_time,
                       MLM_MENU_KEY_TIME_MODE_CUR_TIME);

    /* Set Timer Data to Widget */

    pt_timer_current = (TIMER_EDIT_DATA_T *) c_mem_alloc (sizeof(TIMER_EDIT_DATA_T));

    if(pt_timer_current == NULL)
    {
        return MENUR_FAIL;
    }

    pt_timer_current->ps_g_time       = s_g_edit_time;
    pt_timer_current->pui1_cursor_pos = &gui1_eb_time_cursor_pos;

    i4_ret = _date_time_set_attach_data(h_eb_time, pt_timer_current);

    MENU_CHK_FAIL(i4_ret);

    /* theme */
    i4_ret = _chg_theme();

    MENU_CHK_FAIL(i4_ret);

    /* Refresh timer */
    i4_ret = c_timer_create(&h_timer_refresh);

    MENU_CHK_FAIL(i4_ret);

    /* set content frame proc fct */

    i4_ret = menu_page_set_proc_func(ui4_page_id,
                                     _cnt_frm_proc_fct);
    MENU_CHK_FAIL(i4_ret);

    /* Set visibility */
    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT8   i1_repaint = 0;
    INT32  i4_ret = 0;

    i4_ret = menu_show_homebar(TRUE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_show_backbar(TRUE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Page is ON */
    b_g_date_time_page_in_on = TRUE;

    /* Initialize date/time */
    _init_date_time_in_menu();

    /* Load config and reset values to current widgets */

    b_g_refreshing = TRUE;

    /* Additional Item: reserve for Time Zone */
    if(gui1_additional_item_num != 0)
    {
        UINT16 ui2_list_idx =
        t_menu_additional_item.u.t_list.pf_get_idx();
        menu_list_set_idx(h_lb_additional, ui2_list_idx);
    }

    /* Auto Synchronization */
    {
        /* change data and time font color */
        if (0/*ui1_dt_sync_mode == APP_CFG_DT_SYNC_MODE_AUTO*/)
        {
            _chg_date_time_color(h_eb_date, FALSE, FALSE);
            _chg_date_time_color(h_eb_time, FALSE, FALSE);
        }
        else
        {
            _chg_date_time_color(h_eb_date, TRUE, FALSE);
            _chg_date_time_color(h_eb_time, TRUE, FALSE);
        }
    }

    /* Reset current date/time cursor pos */
    gui1_eb_date_cursor_pos = 0;
    gui1_eb_time_cursor_pos = 0;

    /* title */
    menu_main_set_title(MLM_MENU_KEY_TIME_MODE_CURRENT_TIME);

    /* change the info in help list */
    _chg_help_lst();

    /* enable timer */
    _timer_refresh_start();

    /* Force update the timer at 1st time */
    _do_update_date_time_widget_text((VOID *) &i1_repaint, 1);

    /* last one, set navigation */
    _set_nav();

    b_g_refreshing = FALSE;

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{

    /* Page is OFF */
    b_g_date_time_page_in_on = FALSE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32 i4_ret;

    i4_ret = menu_set_homebar_proc(_homebar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_backbar_proc(_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Additional item check */
    if(gui1_additional_item_num != 0)
    {
        c_wgl_set_focus(h_lb_additional, WGL_NO_AUTO_REPAINT);
        menu_hide_help_tip();
        menu_set_and_trigger_help_tip(apw2s_help_tip[0]);
        return MENUR_OK;
    }

    /* Default */
    c_wgl_set_focus(h_eb_date, WGL_NO_AUTO_REPAINT);

    menu_hide_help_tip();
    menu_set_and_trigger_help_tip(apw2s_help_tip[2]);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    INT32 i4_ret;

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    _timer_refresh_stop();

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        /* Additional item check */
        if(gui1_additional_item_num == 1)
        {
            menu_list_chg_lang(h_lb_additional,
                               t_menu_additional_item.ui2_msgid_title,
                               t_menu_additional_item.u.t_list.ui2_msgid_elem_first,
                               t_menu_additional_item.u.t_list.ui2_msgid_elem_last);
        }

        menu_edit_chg_lang(h_eb_date,
                           MLM_MENU_KEY_TIME_MODE_CUR_DATE);

        menu_edit_chg_lang(h_eb_time,
                           MLM_MENU_KEY_TIME_MODE_CUR_TIME);
    }

    return MENUR_OK;
}

extern INT32 menu_common_page_date_time_init(VOID)
{
    t_g_menu_common_page_date_time.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_date_time.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_date_time.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_date_time.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_date_time.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_date_time.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_date_time.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
#endif /* COMMON_DATE_TIME_ENABLE */

