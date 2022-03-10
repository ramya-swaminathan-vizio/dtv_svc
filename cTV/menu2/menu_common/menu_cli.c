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
 * $RCSfile: menu_cli.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/12 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: adb10972b6baa2af26749cc7af35c284 $
 *
 * Description:
 *         This file contains the implementation of the CLI commands.
 *---------------------------------------------------------------------------*/

#include "u_sys_name.h"
#include "u_irrc_btn_def.h"
#include "u_dbg.h"
#include "u_sb.h"
#include "c_os.h"
#include "c_cli.h"
#include "c_time_msrt.h"
#include "c_net_config.h"
#include "c_svctx.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"

#ifdef APP_RETAIL_MODE_SUPPORT
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/retail_mode/nav_retail_mode.h"
#endif
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"
#ifdef ATSC_AUTO_SCAN2_ENABLE
#include "menu2/menu_atsc/menu_atsc.h"
#endif

#if defined (DVBT_AUTO_SCAN2_ENABLE) || defined (DVB_AUTO_SCAN3_ENABLE)
#include "menu2/menu_dvb/menu_dvb.h"
#endif
#ifdef DVBT_CI_TEST_ENABLE
#include "menu2/menu_dvb_ci/_dvb_ci_mmi.h"
#endif

#ifdef ISDB_AUTO_SCAN2_ENABLE
#include "menu2/menu_isdb/menu_isdb.h"
#endif
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/


extern INT32 ts_cli_get_smart_dim_method(INT32  i4_argc, const CHAR** pps_argv);
extern INT32 ts_cli_get_tv_state(INT32  i4_argc, const CHAR** pps_argv);
#ifdef CLI_SUPPORT
extern INT32 ts_cli_stop_detector(INT32  i4_argc, const CHAR** pps_argv);
extern INT32 ts_cli_start_detector(INT32  i4_argc, const CHAR** pps_argv);
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#ifdef LINUX_AUTO_TEST
#define MENU_CLI_RIGHT      CLI_GUEST
#else
#define MENU_CLI_RIGHT      CLI_SUPERVISOR
#endif
/*-----------------------------------------------------------------------------
                    private functions declarations
 ----------------------------------------------------------------------------*/
#ifdef CLI_SUPPORT
static INT32 _cmd_set_osd_size(INT32        i4_argc,
                               const CHAR** pps_argv);

static INT32 _cmd_get_osd_size(INT32        i4_argc,
                               const CHAR** pps_argv);

static INT32 _cmd_set_osd_offset(INT32        i4_argc,
                                 const CHAR** pps_argv);

static INT32 _cmd_get_osd_offset(INT32        i4_argc,
                                 const CHAR** pps_argv);

static INT32 _cmd_set_osd_alpha(INT32        i4_argc,
                                 const CHAR** pps_argv);

static INT32 _cmd_get_osd_alpha(INT32        i4_argc,
                                 const CHAR** pps_argv);

static INT32 _cmd_set_hide_delay(INT32        i4_argc,
                                 const CHAR** pps_argv);

static INT32 _cmd_get_hide_delay(INT32        i4_argc,
                                 const CHAR** pps_argv);

static INT32 _cmd_set_dbg_level(INT32 i4_argc,
                                const CHAR** pps_argv);

static INT32 _cmd_get_dbg_level(INT32 i4_argc,
                                const CHAR** pps_argv);

static INT32 _cmd_set_timer_delay(INT32        i4_argc,
                                  const CHAR** pps_argv);

#ifdef TIME_MEASUREMENT
static INT32 _cmd_set_tms_level(INT32 i4_argc,
                                const CHAR** pps_argv);

static INT32 _cmd_get_tms_level(INT32 i4_argc,
                                const CHAR** pps_argv);
#endif /* TIME_MEASUREMENT */
static INT32 _cmd_set_demo_mode_ctrl_idx(INT32 i4_argc,
                                const CHAR** pps_argv);

extern INT32 menu_repaint(INT32   i4_argc,const CHAR** pps_argv);

#ifdef DVBT_CI_TEST_ENABLE
static CLI_EXEC_T at_ci_mmi_cmd_tbl[] =
{
    {"enq", "q", ci_mmi_cli_test_enq, NULL, "Test enq () usage: enq blind_ans", CLI_SUPERVISOR},
    {"menu", "m", ci_mmi_cli_test_menu, NULL, "Test menu ()", CLI_SUPERVISOR},
    {"close_mmi", "c", ci_mmi_cli_test_close_mmi, NULL, "Test close_mmi ()", CLI_SUPERVISOR},
    {"enq_close", "qc", ci_mmi_cli_test_enq_close, NULL, "usage: qc [#iteration]", CLI_SUPERVISOR},
    {"card_insert", "i", ci_mmi_cli_test_card_insert, NULL, "usage: i slot_idx", CLI_SUPERVISOR},
    {"card_remove", "r", ci_mmi_cli_test_card_remove, NULL, "usage: r slot_idx", CLI_SUPERVISOR},
    END_OF_CLI_CMD_TBL
};
#endif
/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
void _cb_test_ping(INT16 retTime)
{
    DBG_INFO(("retTime: %d\n", retTime));
}
static INT32 _cmd_test_ping(INT32   i4_argc,
                            const CHAR** pps_argv)
{
    c_net_ping_v4("192.168.1.1", 64, 1, &_cb_test_ping);

    return(CLIR_OK);
}

#ifdef LINUX_AUTO_TEST
static INT32 _cmd_check_screen_mode(INT32 argc, const CHAR **argv)
{
    INT32                   i4_ret = MENUR_OK;
    INT16                   i2_app_val = 0;
    HANDLE_T                h_svctx = NULL_HANDLE;
    VSH_REGION_INFO_T       t_dst_region = {0};
    VSH_REGION_INFO_T       t_disp_region = {0};
    VSH_REGION_INFO_T       t_fnal_disp_region = {0};
    SIZE_T                  z_size = sizeof(VSH_REGION_INFO_T);
    BOOL                    b_result = TRUE;

    /* Get current screen mode */

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), &i2_app_val);
    MENU_CHK_FAIL(i4_ret);

    /* Get current finnal display region */
    h_svctx = menu_get_crnt_svctx();

    if (NULL_HANDLE == h_svctx)
    {
        DBG_LOG_PRINT(("[AUTO TEST] Line %d: Get svctx handle fail!\n",__FUNCTION__,__LINE__));
        return MENUR_FAIL;
    }

    i4_ret = c_svctx_get_stream_attr(
                    menu_get_crnt_svctx(),
                    ST_VIDEO,
                    SM_VSH_GET_TYPE_DISP_REGION,
                    &t_disp_region,
                    &z_size
                    );

    i4_ret = c_svctx_get_stream_attr(
                    menu_get_crnt_svctx(),
                    ST_VIDEO,
                    SM_VSH_GET_TYPE_FINAL_DISP_REGION,
                    &t_fnal_disp_region,
                    &z_size
                    );

    /* Calculate dst_reg */
    t_dst_region.ui4_width = t_fnal_disp_region.ui4_width * VSH_REGION_MAX_WIDTH / t_disp_region.ui4_width;

    DBG_LOG_PRINT(("[AUTO TEST] Line %d: t_disp_region=[%d,%d,%d,%d]\n",__LINE__,
                                                        t_disp_region.ui4_x,
                                                        t_disp_region.ui4_y,
                                                        t_disp_region.ui4_width,
                                                        t_disp_region.ui4_height));
    DBG_LOG_PRINT(("[AUTO TEST] Line %d: t_fnal_disp_region=[%d,%d,%d,%d]\n",__LINE__,
                                                        t_fnal_disp_region.ui4_x,
                                                        t_fnal_disp_region.ui4_y,
                                                        t_fnal_disp_region.ui4_width,
                                                        t_fnal_disp_region.ui4_height));
    DBG_LOG_PRINT(("[AUTO TEST] Line %d: screen_mode = %d, t_dst_region.ui4_width=%d\n",
                                                        __LINE__,
                                                        (SCC_VID_SCREEN_MODE_T)i2_app_val,
                                                        t_dst_region.ui4_width));

    switch ((SCC_VID_SCREEN_MODE_T)i2_app_val)
    {
        case SCC_VID_SCREEN_MODE_NORMAL:          /* Normal */
        {
            if (t_dst_region.ui4_width > 7500+200
                || t_dst_region.ui4_width < 7500-200)  //the 200 is for floating value.
            {
                b_result = FALSE;
            }

            break;
        }

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:    /* Zoom */
        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:    /* Wide */
        case SCC_VID_SCREEN_MODE_LETTERBOX:       /* Stretch */
        case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM: /* Panoramic */
        {
            if (t_dst_region.ui4_width < 10000-200)
            {
                b_result = FALSE;
            }
            break;
        }
        default:                                  /* unknown screen mode? */
        {
            b_result = FALSE;
            break;
        }
    }

    if (b_result)
    {
        DBG_CREATE_TEMP_FILE("10400_test_case_screen_mode_check_ok");
    }

    DBG_LOG_PRINT(("[AUTO TEST]%s Line %d: check result is %d\n\n",
                                                            __FUNCTION__,
                                                            __LINE__,
                                                            b_result));

    return i4_ret;
}

static INT32 _cmd_check_viewport(INT32 argc, const CHAR **argv)
{
    INT32                   i4_ret = MENUR_OK;
#if (VIEWPORT_SUPPORT == 1)
    BOOL                    b_apply_viewport = FALSE;
    VSH_REGION_INFO_T       t_fnal_disp_region = {0};
    SIZE_T                  z_size = sizeof(VSH_REGION_INFO_T);
    //APP_CFG_APP_STATUS_T    e_app_status = a_cfg_get_app_status ();
    APP_CFG_VIEWPORT_T      t_viewport = {0};
    BOOL                    b_result = TRUE;
    UINT32                  ui4_val = 0;

    b_apply_viewport = !a_cfg_get_skip_viewport_func() && a_cfg_is_able_to_apply_viewport();

    if (!b_apply_viewport)
    {
        DBG_LOG_PRINT(("[AUTO TEST] Line %d: No need of viewport checking\n\n",__LINE__));

        DBG_CREATE_TEMP_FILE("10401_test_case_viewport_check_ok");
        return i4_ret;
    }

    a_cfg_get_viewport(&t_viewport);

    i4_ret = c_svctx_get_stream_attr(
                    menu_get_crnt_svctx(),
                    ST_VIDEO,
                    SM_VSH_GET_TYPE_FINAL_DISP_REGION,
                    &t_fnal_disp_region,
                    &z_size
                    );
    ui4_val = t_fnal_disp_region.ui4_width;

    if ((ui4_val > 6289 - 200 && ui4_val < 6289 + 200)   /*SD Centered overlay*/
        || (ui4_val > 5077 - 200 && ui4_val < 5077 + 200)/*SD viewport*/
        || (ui4_val > 8386 - 200 && ui4_val < 8386 + 200)/*HD Centered overlay*/
        || (ui4_val > 6770 - 200 && ui4_val < 6770 + 200))/*HD viewport*/
    {
        b_result = TRUE;
    }
    else
    {
        b_result = FALSE;
    }

    if (b_result)
    {
        DBG_LOG_PRINT(("[AUTO TEST] Line %d: viewport check ok\n\n",__LINE__));
        DBG_CREATE_TEMP_FILE("10401_test_case_viewport_check_ok");
    }

#else
    DBG_LOG_PRINT(("[AUTO TEST] Line %d: Not support viewport!\n\n",__LINE__));
#endif

    return MENUR_OK;

}
#endif

static CLI_EXEC_T at_menu_cmd_tbl[] =
{
#ifdef ATSC_AUTO_SCAN2_ENABLE
    {"scan",   "s",   menu_atsc_cli_scan, NULL, "usage: scan", CLI_SUPERVISOR},
#endif
#ifdef DVBT_AUTO_SCAN2_ENABLE
    {"scan",   "s",   menu_dvbt_cli_scan, NULL, "usage: scan", CLI_SUPERVISOR},
#endif
#ifdef ISDB_AUTO_SCAN2_ENABLE
    {"scan",   "s",   menu_isdb_cli_scan, NULL, "usage: scan", CLI_SUPERVISOR},
#endif
#ifdef ATSC_ADV_SCAN_RNG_ENABLE
    {"rscan",   "rs",   menu_atsc_cli_rscan, NULL, "usage: rscan", CLI_SUPERVISOR},
#endif
#ifdef DVBT_ANALOG_SCAN_RNG_ENABLE
    {"amscan",  "ams",  menu_dvb_cli_analog_manual_scan, NULL,"usage: Analog manual scan", CLI_SUPERVISOR},
#endif
#ifdef DVBT_CI_TEST_ENABLE
    {"ci",      "ci",   NULL, at_ci_mmi_cmd_tbl,   "CI MMI test suite",CLI_SUPERVISOR},
#endif
    {"ssize",   NULL,   _cmd_set_osd_size,  NULL, "usage: ssize [width] [height]", CLI_SUPERVISOR},
    {"gsize",   NULL,   _cmd_get_osd_size,  NULL, "usage: gsize", CLI_SUPERVISOR},
    {"soff",    NULL,   _cmd_set_osd_offset,  NULL, "usage: soff [hoffset] [goffset]", CLI_SUPERVISOR},
    {"goff",    NULL,   _cmd_get_osd_offset,  NULL, "usage: goff", CLI_SUPERVISOR},
    {"salpha",  NULL,   _cmd_set_osd_alpha,  NULL, "usage: salpha [alpha]", CLI_SUPERVISOR},
    {"galpha",  NULL,   _cmd_get_osd_alpha,  NULL, "usage: galpha", CLI_SUPERVISOR},
    {"shd",     NULL,   _cmd_set_hide_delay,  NULL, "usage: shd [delay1] [delay2]", CLI_SUPERVISOR},
    {"ghd",     NULL,   _cmd_get_hide_delay,  NULL, "usage: ghd", CLI_SUPERVISOR},
    {"std",     NULL,   _cmd_set_timer_delay,  NULL, "usage: std [delay]", CLI_SUPERVISOR},
    {CLI_SET_DBG_LVL_STR,     NULL,   _cmd_set_dbg_level, NULL, "usage: " CLI_SET_DBG_LVL_STR " [level]", CLI_GUEST},
    {CLI_GET_DBG_LVL_STR,     NULL,   _cmd_get_dbg_level, NULL, "usage: " CLI_GET_DBG_LVL_STR, CLI_GUEST},
#ifdef TIME_MEASUREMENT
    {CLI_SET_TMS_LVL_STR,     NULL,   _cmd_set_tms_level, NULL, "usage:" CLI_SET_TMS_LVL_HELP_STR, CLI_SUPERVISOR},
    {CLI_GET_TMS_LVL_STR,     NULL,   _cmd_get_tms_level, NULL, "usage:" CLI_GET_TMS_LVL_HELP_STR, CLI_SUPERVISOR},
#endif /* TIME_MEASUREMENT */
    {"tstping", NULL,   _cmd_test_ping, NULL, "usage: tstping", CLI_GUEST},
    {"sdm",         "sdm",      ts_cli_get_smart_dim_method,    NULL, "Get Smart dimming method",   CLI_SUPERVISOR},
    {"ts",          "ts",       ts_cli_get_tv_state,            NULL, "Get Tv state",               CLI_SUPERVISOR},
    {"stp_ts",      "stp_ts",   ts_cli_stop_detector,           NULL, "Get Tv state",               CLI_SUPERVISOR},
    {"start_ts",    "start_ts", ts_cli_start_detector,          NULL, "Get Tv state",               CLI_SUPERVISOR},
#ifdef LINUX_AUTO_TEST
    {"check_scrn_mode",    "chk_sm", _cmd_check_screen_mode,    NULL, "Check screen mode",          CLI_GUEST},
    {"check_viewport",     "chk_vp", _cmd_check_viewport,       NULL, "Check viewport",             CLI_GUEST},
#endif
    {"repaint",               "rp",     menu_repaint,      NULL, "usage: 0:main,1:current" , CLI_GUEST},
    {"s_demo_mode",        "s_dm",   _cmd_set_demo_mode_ctrl_idx,      NULL, "usage: s_demo_mode [demo_mode]" ,  CLI_GUEST},

    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_menu_root_cmd_tbl[] =
{
    {"menu", "m",  NULL,  at_menu_cmd_tbl, "Menu commands",   CLI_GUEST},
    END_OF_CLI_CMD_TBL
};

/*-----------------------------------------------------------------------------
                    private functions implementation
 ----------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Name:    _atoi
 *
 * Description: Convert a number string to a number.
 *
 * Inputs:  ps     null ('\0') terminated character string.
 *
 *
 * Outputs: -
 *
 * Returns: the number string. If it is a not numeral string, return 0.
 *
 ------------------------------------------------------------------------*/
static INT32 _atoi( const CHAR* ps )
{
    INT32  i4_total = 0;
    INT32  i4_sign = 1;

    if(*ps == '-')
    {
        i4_sign = -1;
        ps++;
    }

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
            return(0);
        }
    }

    return i4_sign * i4_total;
}
#ifdef APP_2K12_RETAIL_DEMO_MODE
static VOID _cmd_start_demo_mode(VOID)
{
#ifdef APP_RETAIL_MODE_SUPPORT
    RETAIL_MODE_PARAM_T t_param;
    c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));
    t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_MENU;
    t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
    t_param.t_launch_info.ui2_count = 5;
    a_nav_retail_mode_start(&t_param);
#endif
    return;
}
static VOID _cmd_finish_demo_mode(VOID)
{
	ACFG_RETAIL_MODE_T	t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
	a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
	if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
	{
        a_nav_retail_mode_exit();
	}
	else if(ACFG_RETAIL_MODE_NO_PLAYING == t_retail_mode)
	{
		a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
	}
	menu_nav_back();
#ifdef APP_C4TV_SUPPORT
    UINT16      ui2_status    = 0;
    UINT8       ui1_state     = 0;
	a_cfg_get_wzd_status(&ui2_status);
	ui1_state	 = WZD_UTIL_GET_STATUS_STATE(ui2_status);
	if (WZD_STATE_RESUME_C4TV == ui1_state)
	{
	    DBG_LOG_PRINT(("[MENU] Resume wzd when exit demo mode which launch from wzd.\r\n"));
        c_svctx_sync_stop_svc(menu_get_crnt_svctx(), DEFAULT_STOP_SVC_TIMEOUT);
		a_wzd_resume_c4tv(ui1_state, 10); //WZD_PAGE_INDEX_C4TV_START_OOBE
	}
#endif
}
#endif
static INT32 _cmd_set_demo_mode_ctrl_idx(INT32 i4_argc,
                                const CHAR** pps_argv)
{
    UINT8 ui2_idx;
    if(i4_argc != 2)
    {
        DBG_ERROR(("s_demo_mode FAIL\n"));
        return 0;
    }
    ui2_idx = (UINT8)_atoi(pps_argv[1]);
    a_cfg_cust_set_demo_mode_value((UINT8)ui2_idx);
	a_cfg_cust_set_retail_mode_first_time_setting(ACFG_RETAIL_MODE_IS_FIRST_TIME_SETTING);
	if(ui2_idx == 0)
    {
        _cmd_finish_demo_mode();
    }
    else
    {
        _cmd_start_demo_mode();
    }
    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _cmd_set_dbg_level
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_set_osd_size(INT32        i4_argc,
                               const CHAR** pps_argv)
{
    if(i4_argc == 3)
    {
        INT32 i4_width;
        INT32 i4_height;
        if(i4_argc != 3)
        {
            DBG_ERROR(("ssize [width] [height]\n"));
            return 0;
        }

        i4_width = _atoi(pps_argv[1]);

        i4_height = _atoi(pps_argv[2]);

        if(i4_width <= 0)
        {
            DBG_ERROR(("Invalid width: %d \n", i4_width));
        }

        if(i4_height <= 0)
        {
            DBG_ERROR(("Invalid height: %d \n", i4_height));
        }

        menu_set_osd_size(i4_width, i4_height);

        menu_pm_repaint();
    }
    else
    {
        typedef struct _VDP_REGION_T
        {
            UINT32          u4X;
            UINT32          u4Y;
            UINT32          u4Width;
            UINT32          u4Height;
        } VDP_REGION_T;
        UINT32 VDP_SetOutRegion(UCHAR ucVdpId, UCHAR ucOutFullRegion, VDP_REGION_T rOutRegion);

        static VDP_REGION_T t_reg_from = {200, 200, 400 ,300};
        VDP_REGION_T t_reg_to;
        VDP_REGION_T t_reg;
        UINT32 ui4_time_delay = 200;
        UINT32 ui4_tick_start;
        UINT32 ui4_time_elapsed;
        UINT16 ui2_i = 0;


        if(i4_argc != 6)
        {
            DBG_ERROR(("ssize [width] [height]\n"));
            return 0;
        }

        ui4_tick_start = c_os_get_sys_tick();

        ui4_time_delay      = (UINT32)_atoi(pps_argv[1]);
        t_reg_to.u4X        = (UINT32)_atoi(pps_argv[2]);
        t_reg_to.u4Y        = (UINT32)_atoi(pps_argv[3]);
        t_reg_to.u4Width    = (UINT32)_atoi(pps_argv[4]);
        t_reg_to.u4Height   = (UINT32)_atoi(pps_argv[5]);

        while(TRUE)
        {
            ui4_time_elapsed = (c_os_get_sys_tick() - ui4_tick_start) * c_os_get_sys_tick_period();

            if(ui4_time_elapsed > ui4_time_delay)
            {
                break;
            }

            t_reg.u4X = (t_reg_from.u4X * (ui4_time_delay - ui4_time_elapsed) + t_reg_to.u4X * ui4_time_elapsed)/ui4_time_delay;;
            t_reg.u4Y = (t_reg_from.u4Y * (ui4_time_delay - ui4_time_elapsed) + t_reg_to.u4Y * ui4_time_elapsed)/ui4_time_delay;;
            t_reg.u4Width = (t_reg_from.u4Width * (ui4_time_delay - ui4_time_elapsed) + t_reg_to.u4Width * ui4_time_elapsed)/ui4_time_delay;
            t_reg.u4Height= (t_reg_from.u4Height * (ui4_time_delay - ui4_time_elapsed) + t_reg_to.u4Height * ui4_time_elapsed)/ui4_time_delay;
            DBG_INFO(("%d, %d, %d, %d\n", ui2_i++, ui4_time_elapsed, t_reg.u4Width, t_reg.u4Height));

            VDP_SetOutRegion(0, 0, t_reg);

            c_thread_delay(5);
        }

        t_reg_from = t_reg_to;
    }

    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _cmd_get_osd_size
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_get_osd_size(INT32        i4_argc,
                                 const CHAR** pps_argv)
{
    INT32 i4_width;
    INT32 i4_height;

    menu_get_osd_size(&i4_width, &i4_height);
    DBG_INFO(("iwidth=%d, height=%d \n", i4_width, i4_height));

    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _cmd_set_osd_offset
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_set_osd_offset(INT32        i4_argc,
                                 const CHAR** pps_argv)
{
    INT32 i4_hoffset;
    INT32 i4_voffset;
    if(i4_argc != 3)
    {
        DBG_ERROR(("soff [hoffset] [voffset]\n"));
        return 0;
    }

    i4_hoffset = _atoi(pps_argv[1]);

    i4_voffset = _atoi(pps_argv[2]);

    menu_set_osd_offset(i4_hoffset, i4_voffset);

    menu_pm_repaint();

    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _cmd_get_osd_offset
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_get_osd_offset(INT32        i4_argc,
                                 const CHAR** pps_argv)
{
    INT32 i4_hoffset;
    INT32 i4_voffset;

    menu_get_osd_offset(&i4_hoffset, &i4_voffset);
    DBG_INFO(("hoffset=%d, voffset=%d \n", i4_hoffset, i4_voffset));

    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _cmd_set_osd_alpha
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_set_osd_alpha(INT32        i4_argc,
                                 const CHAR** pps_argv)
{
    UINT8 ui1_alpha;
    if(i4_argc != 2)
    {
        DBG_ERROR(("salpha [alpha]\n"));
        return 0;
    }

    ui1_alpha = (UINT8)_atoi(pps_argv[1]);

    menu_set_osd_alpha(ui1_alpha);

    menu_pm_repaint();

    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _cmd_get_osd_alpha
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_get_osd_alpha(INT32        i4_argc,
                                 const CHAR** pps_argv)
{
    UINT8   ui1_alpha;
    //Fix Coverity ID : 1392081 Unchecked return value
    if (menu_get_osd_alpha(&ui1_alpha) != MENUR_OK)
    {
        DBG_ERROR((" Get osd alpha fail\n"));
    }
    DBG_INFO(("alpha=%d\n", ui1_alpha));

    return(CLIR_OK);
}


/******************************************************************************
 * Name
 *      _cmd_set_hide_delay
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_set_hide_delay(INT32        i4_argc,
                                 const CHAR** pps_argv)
{
    UINT32 ui4_delay1;
    UINT32 ui4_delay2;
    if(i4_argc != 3)
    {
        DBG_ERROR(("shd [delay1] [delay2]\n"));
        return 0;
    }

    ui4_delay1 = (UINT32)_atoi(pps_argv[1]);
    ui4_delay2 = (UINT32)_atoi(pps_argv[2]);

    menu_set_hide_delay(ui4_delay1, ui4_delay2);

    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _cmd_get_hide_delay
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_get_hide_delay(INT32        i4_argc,
                                 const CHAR** pps_argv)
{
    UINT32 ui4_delay1;
    UINT32 ui4_delay2;

    menu_get_hide_delay(&ui4_delay1, &ui4_delay2);
    DBG_INFO(("delay=%d, delay2=%d \n", ui4_delay1, ui4_delay2));

    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _cmd_set_timer_delay
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_set_timer_delay(INT32        i4_argc,
                                 const CHAR** pps_argv)
{
    UINT32 ui4_delay;
    if(i4_argc != 2)
    {
        DBG_ERROR(("std [delay]\n"));
        return 0;
    }

    ui4_delay = (UINT32)_atoi(pps_argv[1]);

    a_menu_set_timer_delay(ui4_delay);

    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _cmd_set_dbg_level
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_set_dbg_level(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    UINT16 ui2_dbg_level;
    if (c_cli_parse_dbg_level (i4_argc, pps_argv, &ui2_dbg_level) == CLIR_OK)
    {
        menu_set_dbg_level(ui2_dbg_level);
    }
    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _cmd_get_dbg_level
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_get_dbg_level(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    c_cli_show_dbg_level (menu_get_dbg_level());
    return 0;
}


#ifdef TIME_MEASUREMENT
/******************************************************************************
 * Name
 *      _cmd_get_dbg_level
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_set_tms_level(
    INT32          i4_argc,
    const CHAR**   pps_argv)
{
    INT32    i4_ret;
    UINT16   ui2_tms_level;

    i4_ret = c_cli_parse_tms_level(
        i4_argc,
        pps_argv,
        &ui2_tms_level );
    if ( i4_ret == CLIR_OK )
    {
        menu_set_tms_level(ui2_tms_level);
    }

    c_cli_show_tms_level( menu_get_tms_level() );

    return CLIR_OK;
}

/******************************************************************************
 * Name
 *      _cmd_get_dbg_level
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_get_tms_level(
    INT32          i4_argc,
    const CHAR**   pps_argv)
{
    return c_cli_show_tms_level( menu_get_tms_level() );
}
#endif /* TIME_MEASUREMENT */

#endif /*CLI_SUPPORT*/

#ifdef CLI_STRESS_MODE
static INT32 _cmd_set_dbg_level(INT32 i4_argc,
                                const CHAR** pps_argv);

static INT32 _cmd_get_dbg_level(INT32 i4_argc,
                                const CHAR** pps_argv);

extern INT32 menu_repaint(INT32   i4_argc,const CHAR** pps_argv);

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
static CLI_EXEC_T at_menu_cmd_tbl[] =
{
#ifdef ATSC_AUTO_SCAN2_ENABLE
    {"scan",   "s",   menu_atsc_cli_scan, NULL, "usage: scan", CLI_GUEST},
#endif
#ifdef DVBT_AUTO_SCAN2_ENABLE
    {"scan",                  "s",     menu_dvbt_cli_scan, NULL, "usage: scan", CLI_GUEST},
#endif
    {CLI_SET_DBG_LVL_STR,     NULL,   _cmd_set_dbg_level, NULL, "usage: " CLI_SET_DBG_LVL_STR " [level]", CLI_GUEST},
    {CLI_GET_DBG_LVL_STR,     NULL,   _cmd_get_dbg_level, NULL, "usage: " CLI_GET_DBG_LVL_STR, CLI_GUEST},
    {"repaint",               "rp",     menu_repaint,      NULL, "usage: 0:main,1:current" , CLI_GUEST},
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_menu_root_cmd_tbl[] =
{
    {"menu", "m",  NULL,  at_menu_cmd_tbl, "Menu commands",   CLI_GUEST},
    END_OF_CLI_CMD_TBL
};

/******************************************************************************
 * Name
 *      _cmd_set_dbg_level
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_set_dbg_level(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    UINT16 ui2_dbg_level;
    if (c_cli_parse_dbg_level (i4_argc, pps_argv, &ui2_dbg_level) == CLIR_OK)
    {
        menu_set_dbg_level(ui2_dbg_level);
    }
    return(CLIR_OK);
}

/******************************************************************************
 * Name
 *      _cmd_get_dbg_level
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 ******************************************************************************/
static INT32 _cmd_get_dbg_level(INT32        i4_argc,
                                const CHAR** pps_argv)
{
    c_cli_show_dbg_level (menu_get_dbg_level());
    return 0;
}
#endif /* CLI_STRESS_MODE */

/*-----------------------------------------------------------------------------
                    public functions implementation
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: menu_attach_cmd_tbl
 *
 * Description: This API attaches menu commnand table to CLI.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_cli_attach_cmd_tbl(VOID)
{
#if defined(CLI_SUPPORT) || defined(CLI_STRESS_MODE)
    INT32 i4_ret;

    /* attach the command table */
    i4_ret = c_cli_attach_cmd_tbl(at_menu_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI);
    if (i4_ret == CLIR_NOT_INIT)
    {
        DBG_LOG_PRINT(("[%s %d] c_cli_attach_cmd_tbl fail\n ",__FUNCTION__,__LINE__));
        return MENUR_FAIL;
    }
#endif

    return 0;
}


/*-----------------------------------------------------------------------------
 * Name: menu_attach_cmd_tbl
 *
 * Description: This API attaches menu commnand table to CLI.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_cli_detach_cmd_tbl(VOID)
{
    return 0;
}


/*-----------------------------------------------------------------------------
                    external functions implementation
 ----------------------------------------------------------------------------*/

