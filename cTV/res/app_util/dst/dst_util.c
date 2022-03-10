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
 * $RCSfile: dst_util.c,v $
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
#include "u_common.h"
#include "u_sb.h"

#include "c_dbg.h"
#include "c_svctx.h"
#include "c_svl.h"
#include "c_scc.h"
#include "c_version.h"
#include "c_dt.h"
#ifdef TIME_MEASUREMENT
#include "c_time_msrt.h"
#include "u_time_msrt_name.h"
#endif

#include "am/a_am.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/dst/a_dst_custom.h"
#include "app_util/a_tv.h"
#include "app_util/a_cfg.h"
#include "app_util/a_icl_common.h"
#include "nav/nav_common.h"
#ifdef LINUX_TURNKEY_SOLUTION
#include <stdlib.h>
#include <stdio.h>
#endif
#include <sys/time.h>
#include "u_sys_name.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
static BOOL _is_daylight_savings_time(UINT16     ui2_yr,
                                      UINT8      ui1_mon,
                                      UINT8      ui1_day,
                                      UINT8      ui1_hr)
{
    UINT8  ui1_time_zone_idx = 0;

    a_cfg_custom_get_timezone_idx(&ui1_time_zone_idx);

    switch(ui1_time_zone_idx)
    {
    case 0: case 7: case 8: case 9:      //change for new time zone standard (DTV02194418)
    case 10:case 11:case 12:case 13:
    case 14:case 15:case 16:case 17:
    case 18:case 19:case 20:case 21:
    case 22:case 23:case 24:
        return FALSE;
    default:
        break;
    }
    if (ui1_mon<3 || ui1_mon>11) /* Jan, Feb, Dec */
    {
        return FALSE;
    }

    if (ui1_mon >3 && ui1_mon<11) /* Apr, May, Jun, Jul, Aug, Sep, Oct */
    {
        return TRUE;
    }

    if (ui1_mon == 3) /* March */
    {
        UINT8   ui1_start_day = (UINT8)(14 - (1+ui2_yr*5/4)%7); /* The second Sunday in March */

        if (ui1_day > ui1_start_day)
        {
            return TRUE;
        }
        else if (ui1_day < ui1_start_day)
        {
            return FALSE;
        }
        else /* ui1_day==ui1_start_day */
        {
            if (ui1_hr < 2)
            {
                return FALSE;
            }
            else
            {
                return TRUE;
            }
        }
    }

    if (ui1_mon == 11) /* Nov */
    {
        UINT8   ui1_end_day = (UINT8)(7 - (1+ui2_yr*5/4)%7); /* The first Sunday in Nov. */

        if (ui1_day > ui1_end_day)
        {
            return FALSE;
        }
        else if (ui1_day < ui1_end_day)
        {
            return TRUE;
        }
        else /* ui1_day==ui1_end_day */
        {
            if (ui1_hr < 1)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }

    return FALSE;
}
#endif

static BOOL _get_ntp_time(DTG_T* pt_loc_dtg)
{

    struct timeval tv;
    struct timezone tz;
    INT64      sec;

    if (gettimeofday(&tv, &tz) == 0)
    {
        sec = (INT64)tv.tv_sec;
        c_dt_utc_sec_to_loc_dtg(sec, pt_loc_dtg);

        if ((pt_loc_dtg->ui2_yr == 0) ||
            (pt_loc_dtg->ui1_mo == 0) ||
            (pt_loc_dtg->ui2_yr == 1970))
        {
            return FALSE;
        }

        return TRUE;
    }

    return FALSE;
}

static BOOL _crnt_source_is_tv (VOID)
{
    TV_WIN_ID_T                e_tv_win_id = TV_WIN_ID_MAIN ;

    nav_get_focus_id (&e_tv_win_id) ;

    return ((INP_SRC_TYPE_TV == nav_get_src_type (e_tv_win_id)) ? TRUE : FALSE) ;
}

static BOOL _get_local_time(DTG_T* pt_loc_dtg)
{
    TIME_T      t_current_utc = 0;
    DT_COND_T   t_dt_cond = DT_FREE_RUNNING;
    BOOL        b_is_get_time = FALSE;
    INT32       i4_ret = 0;
    UINT8  ui1_time_zone_idx = 0;
    UINT16      ui2_dst = 0;
    t_current_utc = c_dt_get_utc(NULL, &t_dt_cond);

    if (_get_ntp_time(pt_loc_dtg))
    {
        b_is_get_time = TRUE;
    }
    else if ((_crnt_source_is_tv())
        && (0 != c_dt_get_last_sync_tbl_id())
        && (t_dt_cond == DT_SYNC_RUNNING) )
    {
        /* get current time */
        i4_ret = c_dt_utc_sec_to_loc_dtg (
                                    t_current_utc, pt_loc_dtg);
        if (DTR_OK != i4_ret)
        {
            b_is_get_time = FALSE;
        }

        b_is_get_time = TRUE;
    }
    else
    {
        b_is_get_time = FALSE;
    }
    a_cfg_custom_get_dst(&ui2_dst);
    if( ui2_dst==1)
    {
       if (b_is_get_time)
       {
       a_cfg_custom_get_timezone_idx(&ui1_time_zone_idx);
           if (ui1_time_zone_idx==0)//||ui1_time_zone_idx==4) remove for DTV03042868
           {
               if (pt_loc_dtg->ui1_hr != 0)
                {
                   pt_loc_dtg->ui1_hr = pt_loc_dtg->ui1_hr - 1;
                 }
               else
                {
                  pt_loc_dtg->ui1_hr = 23;
                 }
            }
        }
    }
    return b_is_get_time;
}

#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
static BOOL _get_local_time_with_dst(DTG_T* pt_loc_dtg)
{
    BOOL        b_is_get_time = FALSE;
    BOOL        b_is_dst      = FALSE;

    if (_get_ntp_time(pt_loc_dtg))
    {
        b_is_get_time = TRUE;
    }
    else
    {
        b_is_get_time = FALSE;
    }

    if (b_is_get_time)
    {
        b_is_dst = _is_daylight_savings_time(pt_loc_dtg->ui2_yr,
                                  pt_loc_dtg->ui1_mo,
                                  pt_loc_dtg->ui1_day,
                                  pt_loc_dtg->ui1_hr);
#if 0
        DBG_LOG_PRINT(("get dst ctrl %d b_is_dst = %d y:%d m:%d d:%d h:%d\n",
                       c_dt_get_dst_ctrl(),
                       b_is_dst,
                       pt_loc_dtg->ui2_yr,
                       pt_loc_dtg->ui1_mo,
                       pt_loc_dtg->ui1_day,
                       pt_loc_dtg->ui1_hr));
#endif
        c_dt_set_dst(b_is_dst);
    }
    return b_is_get_time;
}
#endif

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

BOOL a_dst_get_local_time(DTG_T* pt_loc_dtg)
{
    BOOL        b_is_get_time = FALSE;

#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
    UINT16      ui2_dst = 0;

    a_cfg_custom_get_dst(&ui2_dst);

    switch (ui2_dst)
    {
        case DST_AUTO:  /* Auto */
            b_is_get_time = _get_local_time_with_dst(pt_loc_dtg);
            break;
        case DST_ON: /* On */
        case DST_OFF:/* Off */
            b_is_get_time = _get_local_time(pt_loc_dtg);
            break;
        default:
            break;
    }

    return b_is_get_time;
#else
    b_is_get_time = _get_local_time(pt_loc_dtg);

    return b_is_get_time;
#endif
}

/*-----------------------------------------------------------------------------
 * Name
 *      _tv_custom_icl_app_status_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/


