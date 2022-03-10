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
 * $RCSfile: acfg_custom.c,v $
 * $Revision: #3 $
 * $Date: 2015/10/20 $
 * $Author: weijia.wang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *      This file implements the APP CFG APIs. APP CFG is a utility library which
 * encapsulates the definition of config database and builds a facade for the
 * application developer.
 *---------------------------------------------------------------------------*/
#ifdef CLI_SUPPORT

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_cli.h"
#include "u_sb.h"
#include "c_os.h"
#include "c_dbg.h"
#include "c_scc.h"
#include "c_svctx.h"
#include "c_dt.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_fm.h"
#include "c_pcl.h"
#include "am/a_am.h"
#include <string.h>

#include "app_util/config/_acfg.h"
#include "app_util/a_cli_app.h"
#include "agent/a_agent.h"
#include "res/app_util/config/acfg_custom.h"
#include "intertaca_api.h"
#include "acfg_cust_cli.h"
#include "wizard_anim/a_wzd.h"
#include "menu2/menu_common/menu_common.h"
#include "rest/a_rest_event.h"
#include "res/app_util/icl/a_icl_custom.h"

static UINT8 ui1_g_splayer_level = 0;
static UINT8 ui1_g_acfg_level = 0;
static UINT8 ui1_g_src_name_log = 0;

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#ifdef NEVER
static INT32 _acfg_cust_set_gamma_table(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_get_gamma_table(INT32 i4_argc, const CHAR** pps_argv);
#endif
static INT32 _acfg_cust_set_hdcp_key(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_set_gamma_simple_table(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_get_gamma_simple_table(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_gamma_enable(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_test_pattern(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_pq_bypss(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_get_rgb_or_yuv(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_set_splayer_dl(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_set_acfg_dl(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_hdr_type_fct(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_set_lcd(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_panel_nits(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_rj45(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_set_vlog(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_set_oled_off_rs(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_set_oled_jb(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_is_lightsensor_support(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_oled_api_test(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_sif(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_skip_oobe(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_bootlogo_show_test(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _acfg_cust_set_power_mode(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_get_oled_display_time(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_set_oled_display_time(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_get_oled_jb_cooling_time(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_set_oled_jb_cooling_time(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_get_pq_ver_by_bin_type(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_reboot_tv(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_set_panel_ssc_en(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_reset_wifi(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_set_demura(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_get_demura(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_cust_set_led_indicator_para(INT32 i4_argc,const CHAR** pps_argv);
static INT32 _acfg_set_src_name_log(INT32 i4_argc,const CHAR** pps_argv);


/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/

#ifdef NEVER
static CLI_EXEC_T t_acfg_cust_set_gamma_table =
{
    "set gamma",
    "set_gamma",
    _acfg_cust_set_gamma_table,
    NULL,
    "set gamma table to ini",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_get_gamma_table =
{
    "get gamma",
    "get_gamma",
    _acfg_cust_get_gamma_table,
    NULL,
    "get gamma table from ini",
    CLI_ACCESS_RIGHT_APP_CFG
};
#endif /* NEVER */


static CLI_EXEC_T t_acfg_cust_set_hdcp_key =
{
    "hdcp key",
    "hdcp_key",
    _acfg_cust_set_hdcp_key,
    NULL,
    "1: hdcp1x ;2: hdcp2x ;3: update",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_gamma_simple_table =
{
    "gamma simple s",
    "gamma_s",
    _acfg_cust_set_gamma_simple_table,
    NULL,
    "set 3 * 17 gammabe table ",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_get_gamma_simple_table =
{
    "gamma simple g",
    "gamma_g",
    _acfg_cust_get_gamma_simple_table,
    NULL,
    "get 3 * 17 gammabe table ",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_gamma_on_off =
{
    "gamma enable",
    "g_en",
    _acfg_cust_gamma_enable,
    NULL,
    "0:set val 1:get 2:set val clr ",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_rgb_pattern =
{
    "set pattern",
    "s_pa",
    _acfg_cust_test_pattern,
    NULL,
    "0 rgb: 1/0 x x x; 1 flat: xx ; 2 vcom: 1/0; 3 mod: 1/0 x x x",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_pq_bypss =
{
    "pq bypass",
    "pq_b",
    _acfg_cust_pq_bypss,
    NULL,
    "0 :set pq bypass : 1 bypass, 0 not bypass ; 1 set pq bypass and module ; 2 :get pqbypss on/off",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_get_rgb_yuv =
{
    "rgb or yuv",
    "r_y",
    _acfg_cust_get_rgb_or_yuv,
    NULL,
    "0 : get rgb output status, 1 : get yuv data ",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_lcd =
{
    "lcd scroll",
    "lcd",
    _acfg_cust_set_lcd,
    NULL,
    "set lcd : 1 true,0 false",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_panel_nits =
{
    "panel nits",
    "p_nits",
    _acfg_cust_panel_nits,
    NULL,
    "0: read ; 1 val col_tmp : write; 2 :update",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_rj45 =
{
    "rj45 f",
    "rj45",
    _acfg_cust_rj45,
    NULL,
    "0: read ; 1 a[6]: write; 2 :update",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_splayer_dl =
{
    "spler debug lever",
    "s_dl",
    _acfg_cust_set_splayer_dl,
    NULL,
    "set splayer debug level : 0 ~ 7 ",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_acfg_dl =
{
    "acfg debug lever",
    "acfg_dl",
    _acfg_cust_set_acfg_dl,
    NULL,
    "set acfg debug level : 0 ~ 7 ",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_hdr_type =
{
    "hdr type",
    "hdr",
    _acfg_cust_hdr_type_fct,
    NULL,
    "0 set; 1 :get",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_vlog =
{
    "set vlog",
    "vlog",
    _acfg_set_vlog,
    NULL,
    "vlog [0=>off,1=>ap,2=>kernel,3=>all]",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_oled_off_rs =
{
    "set oled off rs",
    "off_rs",
    _acfg_set_oled_off_rs,
    NULL,
    "off_rs y|n ",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_oled_jb =
{
    "set oled jb",
    "jb",
    _acfg_set_oled_jb,
    NULL,
    "jb y|n ",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_is_lightsensor_support =
{
    "get light sensor",
    "get_ls",
    _acfg_is_lightsensor_support,
    NULL,
    "1 : support,0: not supprt",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_oled_api_test =
{
    "oled api",
    "t_oled",
    _acfg_oled_api_test,
    NULL,
    "type, set/get,val,",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_sif =
{
    "sif s/g",
    "sif",
    _acfg_cust_sif,
    NULL,
    "0:write, 1: read",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_skip_oobe =
{
    "skip oobe",
    "so",
    _acfg_cust_skip_oobe,
    NULL,
    "",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_bootlogo_show_test =
{
    "bootloge",
    "bl",
    _acfg_cust_bootlogo_show_test,
    NULL,
    "show [name_path]  |  hide  | get_image_raw <name_path>",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_power_mode =
{
    "set power mode",
    "spm",
    _acfg_cust_set_power_mode,
    NULL,
    "0:eco mode 1:quick start mode",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_get_oled_display_time =
{
    "get display time",
    "gdt",
    _acfg_cust_get_oled_display_time,
    NULL,
    "0:period 1:total",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_oled_display_time =
{
    "set display time",
    "sdt",
    _acfg_cust_set_oled_display_time,
    NULL,
    "sdt  [0|1] n min 0:period 1:total",
    CLI_ACCESS_RIGHT_APP_CFG
};


static CLI_EXEC_T t_acfg_cust_get_oled_jb_cooling_time =
{
    "get cooling time",
    "gct",
    _acfg_cust_get_oled_jb_cooling_time,
    NULL,
    "gct",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_oled_jb_cooling_time =
{
    "set cooling time",
    "sct",
    _acfg_cust_set_oled_jb_cooling_time,
    NULL,
    "sct n ",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_get_pq_version_by_bin_type =
{
    "get pq version by bin type",
    "gpvbbt",
    _acfg_cust_get_pq_ver_by_bin_type,
    NULL,
    "0:Standard 1:Extension 2:Customer 3:UFSC 4:CF 5:TMO 6:HSY",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_reboot_tv =
{
    "reboot",
    "rb",
    _acfg_cust_reboot_tv,
    NULL,
    "reboot TV",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_panel_ssc_en =
{
    "set panel ssc on off",
    "sps",
    _acfg_cust_set_panel_ssc_en,
    NULL,
    "0:off 1:on",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_reset_wifi =
{
    "wifireset",
    "wr",
    _acfg_cust_reset_wifi,
    NULL,
    "Reset wifi",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_demura =
{
    "set demura on off",
    "sdmr",
    _acfg_cust_set_demura,
    NULL,
    "0:off 1:on",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_get_demura =
{
    "get demura status",
    "gdmr",
    _acfg_cust_get_demura,
    NULL,
    "0:off 1:on",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_led_indicator_para =
{
    "set led indicator",
    "sli",
    _acfg_cust_set_led_indicator_para,
    NULL,
    "set para",
    CLI_ACCESS_RIGHT_APP_CFG
};

static CLI_EXEC_T t_acfg_cust_set_src_name_log =
{
    "set src_name log",
    "srcnl",
    _acfg_set_src_name_log,
    NULL,
    "src_name_log [0=>off,1=>on]",
    CLI_ACCESS_RIGHT_APP_CFG
};

/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/


#ifdef NEVER
static INT32 _acfg_cust_set_gamma_table(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    INT8    i1_idx;
    ACFG_GAMMA_TABLE_T t_gamma_info;
    UINT16  ui2_idx = 0;
    UINT16  ui2_val = 0;
    c_memset(&t_gamma_info, 0, sizeof(ACFG_GAMMA_TABLE_T));

    if(i4_argc != 3)
    {
        DBG_LOG_PRINT(("Invalid argument\n"));
        return 0;
    }

    i1_idx  = (INT8)c_strtoll(pps_argv[1], NULL, 0);
    ui2_val = (INT16)c_strtoll(pps_argv[2], NULL, 0);
    a_cfg_cust_info_get_gamma_table_from_ini(i1_idx,&t_gamma_info);
    for(ui2_idx = 0; ui2_idx < 386; ui2_idx++)
    {
        if(ui2_idx % 9 ==  0)
        {
            t_gamma_info.gamma_r[ui2_idx] = ui2_val;
            t_gamma_info.gamma_g[ui2_idx] = ui2_val;
            t_gamma_info.gamma_b[ui2_idx] = ui2_val;
        }
    }
    a_cfg_cust_info_set_gamma_table_to_ini(i1_idx,&t_gamma_info);

    return 0;
}


static INT32 _acfg_cust_get_gamma_table(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    INT8    i1_val;
    ACFG_GAMMA_TABLE_T t_gamma_info;
    c_memset(&t_gamma_info, 0, sizeof(ACFG_GAMMA_TABLE_T));

    if(i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid argument\n"));
        return 0;
    }

    i1_val  = (INT8)c_strtoll(pps_argv[1], NULL, 0);

    a_cfg_cust_info_get_gamma_table_from_ini(i1_val,&t_gamma_info);
    return 0;
}
#endif /* NEVER */

static INT32 _acfg_cust_set_hdcp_key(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    INT8    i1_val;

    if(i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid argument\n"));
        return 0;
    }

    i1_val  = (INT8)c_strtoll(pps_argv[1], NULL, 0);
    if(i1_val == 2)
    {
        DBG_LOG_PRINT((" set hdcp 2x\n"));
        TEEC_SendData2TA("8", 1);
    }
    else if(i1_val == 1)
    {
        DBG_LOG_PRINT((" set hdcp 1x\n"));
        TEEC_SendData2TA("21", 0);
    }
    else if(i1_val == 3)
    {
        DBG_LOG_PRINT((" update hdcp key\n"));
        a_cfg_cust_update_hdcp();
    }
    else
    {
        DBG_LOG_PRINT(("Invalid argument\n"));
    }

    return 0;
}

static INT32 _acfg_cust_set_gamma_simple_table(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    INT32       i4_ret;
    UINT8       ui1_idx = 0;
    UINT8       ui1_jdx = 0;

    VID_CUSTOM_TYPE_SET_NVM_GAMMA_T prNVMGamma;
    c_memset(&prNVMGamma, 0, sizeof(VID_CUSTOM_TYPE_SET_NVM_GAMMA_T));

    if (i4_argc < 3)
    {
        DBG_LOG_PRINT(("Invalid argument\n"));
        return 0;
    }

    prNVMGamma.u4TblIndex = (UINT32)c_strtoll(pps_argv[1], NULL, 0);
    prNVMGamma.u4RGBIndex = (UINT16)c_strtoll(pps_argv[2], NULL, 0);

    if(prNVMGamma.u4RGBIndex == 0) //linear
    {
       //R:
        ui1_idx = 0;
        prNVMGamma.u2GammaTbl[ui1_idx][0] = 0;
        prNVMGamma.u2GammaTbl[ui1_idx][1] = 256;
        prNVMGamma.u2GammaTbl[ui1_idx][2] = 512;
        prNVMGamma.u2GammaTbl[ui1_idx][3] = 768;
        prNVMGamma.u2GammaTbl[ui1_idx][4] = 1024;
        prNVMGamma.u2GammaTbl[ui1_idx][5] = 1280;
        prNVMGamma.u2GammaTbl[ui1_idx][6] = 1536;
        prNVMGamma.u2GammaTbl[ui1_idx][7] = 1792;
        prNVMGamma.u2GammaTbl[ui1_idx][8] = 2048;
        prNVMGamma.u2GammaTbl[ui1_idx][9] = 2304;
        prNVMGamma.u2GammaTbl[ui1_idx][10] = 2560;
        prNVMGamma.u2GammaTbl[ui1_idx][11] = 2816;
        prNVMGamma.u2GammaTbl[ui1_idx][12] = 3072;
        prNVMGamma.u2GammaTbl[ui1_idx][13] = 3328;
        prNVMGamma.u2GammaTbl[ui1_idx][14] = 3584;
        prNVMGamma.u2GammaTbl[ui1_idx][15] = 3840;
        prNVMGamma.u2GammaTbl[ui1_idx][16] = 4080;

        //G:
        ui1_idx = 1;
        prNVMGamma.u2GammaTbl[ui1_idx][0] = 0;
        prNVMGamma.u2GammaTbl[ui1_idx][1] = 256;
        prNVMGamma.u2GammaTbl[ui1_idx][2] = 512;
        prNVMGamma.u2GammaTbl[ui1_idx][3] = 768;
        prNVMGamma.u2GammaTbl[ui1_idx][4] = 1024;
        prNVMGamma.u2GammaTbl[ui1_idx][5] = 1280;
        prNVMGamma.u2GammaTbl[ui1_idx][6] = 1536;
        prNVMGamma.u2GammaTbl[ui1_idx][7] = 1792;
        prNVMGamma.u2GammaTbl[ui1_idx][8] = 2048;
        prNVMGamma.u2GammaTbl[ui1_idx][9] = 2304;
        prNVMGamma.u2GammaTbl[ui1_idx][10] = 2560;
        prNVMGamma.u2GammaTbl[ui1_idx][11] = 2816;
        prNVMGamma.u2GammaTbl[ui1_idx][12] = 3072;
        prNVMGamma.u2GammaTbl[ui1_idx][13] = 3328;
        prNVMGamma.u2GammaTbl[ui1_idx][14] = 3584;
        prNVMGamma.u2GammaTbl[ui1_idx][15] = 3840;
        prNVMGamma.u2GammaTbl[ui1_idx][16] = 4080;

        //B:
        ui1_idx = 2;
        prNVMGamma.u2GammaTbl[ui1_idx][0] = 0;
        prNVMGamma.u2GammaTbl[ui1_idx][1] = 256;
        prNVMGamma.u2GammaTbl[ui1_idx][2] = 512;
        prNVMGamma.u2GammaTbl[ui1_idx][3] = 768;
        prNVMGamma.u2GammaTbl[ui1_idx][4] = 1024;
        prNVMGamma.u2GammaTbl[ui1_idx][5] = 1280;
        prNVMGamma.u2GammaTbl[ui1_idx][6] = 1536;
        prNVMGamma.u2GammaTbl[ui1_idx][7] = 1792;
        prNVMGamma.u2GammaTbl[ui1_idx][8] = 2048;
        prNVMGamma.u2GammaTbl[ui1_idx][9] = 2304;
        prNVMGamma.u2GammaTbl[ui1_idx][10] = 2560;
        prNVMGamma.u2GammaTbl[ui1_idx][11] = 2816;
        prNVMGamma.u2GammaTbl[ui1_idx][12] = 3072;
        prNVMGamma.u2GammaTbl[ui1_idx][13] = 3328;
        prNVMGamma.u2GammaTbl[ui1_idx][14] = 3584;
        prNVMGamma.u2GammaTbl[ui1_idx][15] = 3840;
        prNVMGamma.u2GammaTbl[ui1_idx][16] = 4080;

    }
    else
    {
       //R:
        ui1_idx = 0;
        prNVMGamma.u2GammaTbl[ui1_idx][0] = 0;
        prNVMGamma.u2GammaTbl[ui1_idx][1] = 249;
        prNVMGamma.u2GammaTbl[ui1_idx][2] = 516;
        prNVMGamma.u2GammaTbl[ui1_idx][3] = 709;
        prNVMGamma.u2GammaTbl[ui1_idx][4] = 953;
        prNVMGamma.u2GammaTbl[ui1_idx][5] = 1199;
        prNVMGamma.u2GammaTbl[ui1_idx][6] = 1489;
        prNVMGamma.u2GammaTbl[ui1_idx][7] = 1741;
        prNVMGamma.u2GammaTbl[ui1_idx][8] = 1991;
        prNVMGamma.u2GammaTbl[ui1_idx][9] = 2256;
        prNVMGamma.u2GammaTbl[ui1_idx][10] = 2533;
        prNVMGamma.u2GammaTbl[ui1_idx][11] = 2780;
        prNVMGamma.u2GammaTbl[ui1_idx][12] = 3066;
        prNVMGamma.u2GammaTbl[ui1_idx][13] = 3340;
        prNVMGamma.u2GammaTbl[ui1_idx][14] = 3570;
        prNVMGamma.u2GammaTbl[ui1_idx][15] = 3818;
        prNVMGamma.u2GammaTbl[ui1_idx][16] = 4080;

        //G:
        ui1_idx = 1;
        prNVMGamma.u2GammaTbl[ui1_idx][0] = 0;
        prNVMGamma.u2GammaTbl[ui1_idx][1] = 223;
        prNVMGamma.u2GammaTbl[ui1_idx][2] = 485;
        prNVMGamma.u2GammaTbl[ui1_idx][3] = 675;
        prNVMGamma.u2GammaTbl[ui1_idx][4] = 880;
        prNVMGamma.u2GammaTbl[ui1_idx][5] = 1117;
        prNVMGamma.u2GammaTbl[ui1_idx][6] = 1397;
        prNVMGamma.u2GammaTbl[ui1_idx][7] = 1638;
        prNVMGamma.u2GammaTbl[ui1_idx][8] = 1881;
        prNVMGamma.u2GammaTbl[ui1_idx][9] = 2137;
        prNVMGamma.u2GammaTbl[ui1_idx][10] = 2396;
        prNVMGamma.u2GammaTbl[ui1_idx][11] = 2639;
        prNVMGamma.u2GammaTbl[ui1_idx][12] = 2896;
        prNVMGamma.u2GammaTbl[ui1_idx][13] = 3135;
        prNVMGamma.u2GammaTbl[ui1_idx][14] = 3417;
        prNVMGamma.u2GammaTbl[ui1_idx][15] = 3619;
        prNVMGamma.u2GammaTbl[ui1_idx][16] = 3857;

        //B:
        ui1_idx = 2;
        prNVMGamma.u2GammaTbl[ui1_idx][0] = 0;
        prNVMGamma.u2GammaTbl[ui1_idx][1] = 162;
        prNVMGamma.u2GammaTbl[ui1_idx][2] = 417;
        prNVMGamma.u2GammaTbl[ui1_idx][3] = 582;
        prNVMGamma.u2GammaTbl[ui1_idx][4] = 741;
        prNVMGamma.u2GammaTbl[ui1_idx][5] = 924;
        prNVMGamma.u2GammaTbl[ui1_idx][6] = 1165;
        prNVMGamma.u2GammaTbl[ui1_idx][7] = 1332;
        prNVMGamma.u2GammaTbl[ui1_idx][8] = 1549;
        prNVMGamma.u2GammaTbl[ui1_idx][9] = 1772;
        prNVMGamma.u2GammaTbl[ui1_idx][10] = 2002;
        prNVMGamma.u2GammaTbl[ui1_idx][11] = 2221;
        prNVMGamma.u2GammaTbl[ui1_idx][12] = 2420;
        prNVMGamma.u2GammaTbl[ui1_idx][13] = 2623;
        prNVMGamma.u2GammaTbl[ui1_idx][14] = 2859;
        prNVMGamma.u2GammaTbl[ui1_idx][15] = 3101;
        prNVMGamma.u2GammaTbl[ui1_idx][16] = 3258;

    }

    DBG_LOG_PRINT(("\r\n gamma vlaue :"));

    for(ui1_idx = 0; ui1_idx < 3 ; ui1_idx++)
    {
        for(ui1_jdx = 0; ui1_jdx < 17 ; ui1_jdx++)
        {
            DBG_LOG_PRINT((" %d ,\r\n",prNVMGamma.u2GammaTbl[ui1_idx][ui1_jdx]));
        }
    }

    DBG_LOG_PRINT(("\r\n"));

    i4_ret = a_cfg_cust_set_Gamma_table(prNVMGamma);
    DBG_LOG_PRINT(("[ACFG] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));

    return 0;
}

static INT32 _acfg_cust_get_gamma_simple_table(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    INT32       i4_ret;
    UINT16      ui2_idx = 0;
    UINT8       gamma[306]={0};


    i4_ret = a_cfg_cust_get_gamma_table(&gamma,sizeof(gamma));
    DBG_LOG_PRINT(("[ACFG] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));
    DBG_LOG_PRINT((" %d ,\r\n",sizeof(gamma)));

    for(ui2_idx = 0; ui2_idx < 306 ; ui2_idx++)
    {
        DBG_LOG_PRINT((" %d ,\r\n",gamma[ui2_idx]));
    }

    return 0;
}


static INT32 _acfg_cust_gamma_enable(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    INT32       i4_ret;
    UINT8       ui1_idx;
    UINT8       ui1_val = 0;

    ui1_idx = (UINT8)c_strtoll(pps_argv[1], NULL, 0);
    if( ui1_idx == 0)
    {
        ui1_val = (UINT8)c_strtoll(pps_argv[2], NULL, 0);
        if(ui1_val == 0)
        {
            i4_ret = a_cfg_cust_set_gamma_on_off(FALSE);
        }
        else
        {
            i4_ret = a_cfg_cust_set_gamma_on_off(TRUE);
        }
        DBG_LOG_PRINT(("[ACFG] a_cfg_cust_set_gamma_on_off %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));
    }
    else if( ui1_idx == 1)
    {
        BOOL b_val;
        i4_ret = a_cfg_cust_get_gamma_on_off(&b_val);
        DBG_LOG_PRINT(("[ACFG] a_cfg_cust_get_gamma_on_off: b_val: %d,i4_ret :%d\r\n",b_val,i4_ret));

    }
    else if( ui1_idx == 2)
    {
        GAMMA_ONOFF_INFO_T t_info;
        c_memset(&t_info, 0, sizeof(t_info));
        ui1_val = (UINT8)c_strtoll(pps_argv[2], NULL, 0);

        if(ui1_val == 0)
        {
            t_info.bEnable = FALSE;
        }
        else
        {
            t_info.bEnable = TRUE;
        }

        t_info.u1ColTemp = (UINT8)c_strtoll(pps_argv[3], NULL, 0);

        i4_ret = a_cfg_cust_set_gamma_enable_by_temp(&t_info,sizeof(t_info));
        DBG_LOG_PRINT(("[ACFG] a_cfg_cust_set_gamma_enable_by_temp %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));

    }
    else
    {
        DBG_LOG_PRINT(("Invalid argument\n"));
    }

    return 0;
}

static INT32 _acfg_cust_test_pattern(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    INT32       i4_ret = 0;
    UINT8       ui1_type = 0;
    UINT8       ui1_val = 0;
    UINT8       ui1_idx = 0;

    ui1_type = (UINT8)c_strtoll(pps_argv[1], NULL, 0);
    ui1_val  = (UINT8)c_strtoll(pps_argv[2], NULL, 0);

    if(ui1_type == ACFG_CUST_PATTERN_RGB) //test pattern rgb
    {
        ACFG_TYPE_SET_RGB_T t_info;
        c_memset(&t_info, 0, sizeof(t_info));

        if(ui1_val == 0)
        {
            t_info.bEnable = FALSE;
        }
        else
        {
            t_info.bEnable = TRUE;
        }

        t_info.u2R = (UINT16)c_strtoll(pps_argv[3], NULL, 0);
        t_info.u2G = (UINT16)c_strtoll(pps_argv[4], NULL, 0);
        t_info.u2B = (UINT16)c_strtoll(pps_argv[5], NULL, 0);

        i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));
        DBG_LOG_PRINT(("[ACFG] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));
    }
    else if(ui1_type == ACFG_CUST_PATTERN_FLAT) //test pattern flat
    {
        i4_ret = a_cfg_cust_set_flat_pattern(ui1_val);
        DBG_LOG_PRINT(("[ACFG] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));
    }
    else if(ui1_type == ACFG_CUST_PATTERN_VCOM) //test pattern vcom
    {
        DRV_CUSTOM_VCOM_PATTERN_T t_info;
        c_memset(&t_info, 0, sizeof(t_info));
        if(ui1_val == 0)
        {
            t_info.bEnable = FALSE;
        }
        else
        {
            t_info.bEnable = TRUE;
        }

        for (ui1_idx = 0 ; ui1_idx < 96; ui1_idx++)
        {
            t_info.u2Tbl[ui1_idx] = ui1_idx;
        }

        i4_ret = a_cfg_cust_drv_set_vcom_pattern(&t_info,sizeof(t_info));
        DBG_LOG_PRINT(("[ACFG] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));

    }
    else if(ui1_type == ACFG_CUST_PATTERN_MOD) //test pattern mod
    {
        VID_TYPE_MOD_PATTERN_T t_info;
        c_memset(&t_info, 0, sizeof(t_info));
        if(ui1_val == 0)
        {
            t_info.b_on_off = FALSE;
        }
        else
        {
            t_info.b_on_off = TRUE;
        }

        t_info.ui2_r= (UINT16)c_strtoll(pps_argv[3], NULL, 0);
        t_info.ui2_g= (UINT16)c_strtoll(pps_argv[4], NULL, 0);
        t_info.ui2_b = (UINT16)c_strtoll(pps_argv[5], NULL, 0);

        i4_ret = a_cfg_cust_drv_set_mod_pattern(&t_info,sizeof(t_info));
        DBG_LOG_PRINT(("[ACFG] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));

    }
    else if(ui1_type == ACFG_CUST_PATTERN_MM) //test pattern mod
    {
        UINT8 ui1_pattern  = (UINT8)c_strtoll(pps_argv[2], NULL, 0);
        UINT8 ui1_idx  = (UINT8)c_strtoll(pps_argv[3], NULL, 0);
        i4_ret = menu_page_color_tuner_adjust_test_pattern(ui1_pattern,ui1_idx);
        DBG_LOG_PRINT(("[ACFG] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));
    }

    return 0;
}

static INT32 _acfg_cust_pq_bypss(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    INT32       i4_ret;
    UINT8       ui1_type = 0;
    UINT8       ui1_val  = 0;

    ui1_type = (UINT8)c_strtoll(pps_argv[1], NULL, 0);
    ui1_val = (UINT8)c_strtoll(pps_argv[2], NULL, 0);

    if ( ui1_type == 0)
    {
        i4_ret = a_cfg_cust_drv_set_pq_bypass(ui1_val);
        DBG_LOG_PRINT(("[ACFG] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));
    }
    else if ( ui1_type == 1)
    {
        DRV_CUSTOM_PQ_BYPASS_T t_info;
        c_memset(&t_info, 0, sizeof(t_info));

        if(ui1_val == 0)
        {
            t_info.bEnable = FALSE;
        }
        else
        {
            t_info.bEnable = TRUE;
        }
        t_info.u4Val = (UINT32)c_strtoll(pps_argv[3], NULL, 0);


        i4_ret = a_cfg_cust_drv_set_pq_bypass_ex(&t_info,sizeof(t_info));
        DBG_LOG_PRINT(("[ACFG] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));

    }
    else if ( ui1_type == 2)
    {
        UINT8 ui1_status = a_cfg_cust_get_pqbypass_status();
        DBG_LOG_PRINT(("a_cfg_cust_get_pqbypass_status :%d\r\n",ui1_status));
    }
    else
    {
        DBG_LOG_PRINT(("[ACFG] %s,invalid type :%d\r\n",__FUNCTION__,ui1_type));

    }

    return 0;
}

static INT32 _acfg_cust_get_rgb_or_yuv(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    INT32       i4_ret;
    UINT8       ui1_val = 0;
    UINT16      ui2_data[3]={0};
    UINT16      ui2_s_data[2]={0};

    ui1_val = (UINT8)c_strtoll(pps_argv[1], NULL, 0);

    if(ui1_val == 0)
    {
        UINT16 ui2_x_pos = (UINT16)c_strtoll(pps_argv[2], NULL, 0);
        UINT16 ui2_y_pos = (UINT16)c_strtoll(pps_argv[3], NULL, 0);

        i4_ret = a_cfg_cust_get_rgb_output_status( ui2_x_pos, ui2_y_pos, ui2_data);

        DBG_LOG_PRINT(("[ACFG] R :%d\r\n",ui2_data[0]));
        DBG_LOG_PRINT(("[ACFG] G :%d\r\n",ui2_data[1]));
        DBG_LOG_PRINT(("[ACFG] B :%d\r\n",ui2_data[2]));
        DBG_LOG_PRINT(("[ACFG] size :%d\r\n",sizeof(ui2_data)));
        DBG_LOG_PRINT(("[ACFG] i4_ret :%d\r\n",i4_ret));

    }
    else
    {
        ui2_s_data[0] = (UINT16)c_strtoll(pps_argv[2], NULL, 0);
        ui2_s_data[1] = (UINT16)c_strtoll(pps_argv[3], NULL, 0);
        i4_ret = a_cfg_cust_get_yuv_data(ui2_s_data,sizeof(ui2_s_data),ui2_data,sizeof(ui2_data));

        DBG_LOG_PRINT(("[ACFG] Y :%d\r\n",ui2_data[0]));
        DBG_LOG_PRINT(("[ACFG] U :%d\r\n",ui2_data[1]));
        DBG_LOG_PRINT(("[ACFG] V :%d\r\n",ui2_data[2]));
        DBG_LOG_PRINT(("[ACFG] size :%d\r\n",sizeof(ui2_data)));
        DBG_LOG_PRINT(("[ACFG] i4_ret :%d\r\n",i4_ret));

    }

    return 0;
}

static INT32 _acfg_cust_set_lcd(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    UINT8 ui1_val = (UINT8)c_strtoll(pps_argv[1], NULL, 0);

    if(ui1_val == 1)
    {
        a_cfg_cust_drv_set_drv_Lcdim_Scrolling_OnOff(TRUE);
    }
    else if (ui1_val == 0)
    {
        a_cfg_cust_drv_set_drv_Lcdim_Scrolling_OnOff(FALSE);
    }
    else
    {
        DBG_LOG_PRINT(("[ACFG] Invalid value %s,%d\r\n",__FUNCTION__,__LINE__));

    }
    return 0;
}

static INT32 _acfg_cust_panel_nits(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    UINT8  ui1_val = (UINT8)c_strtoll(pps_argv[1], NULL, 0);
    UINT16 ui2_val = 0;
    UINT8  ui1_tmp = 0;

    if(ui1_val == 0) //read
    {
        a_cfg_cust_drv_read_panel_nits(&ui2_val);

        DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_read_panel_nits  : %d \r\n",ui2_val));

    }
    else if (ui1_val == 1) //write
    {

        ui2_val = (UINT16)c_strtoll(pps_argv[2], NULL, 0);
        ui1_tmp = (UINT8)c_strtoll(pps_argv[3], NULL, 0);
        a_cfg_cust_drv_write_panel_nits(ui2_val,ui1_tmp);

        DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_write_panel_nits :ui2_val : %d, ui1_tmp :%d\r\n",ui2_val,ui1_tmp));
    }
    else if (ui1_val == 2) //update
    {
        a_cfg_cust_drv_update_panel_nits();
        DBG_LOG_PRINT(("[ACFG]  a_cfg_cust_drv_update_panel_nits \r\n"));
    }
    else
    {
        DBG_LOG_PRINT(("[ACFG] Invalid value %s,%d\r\n",__FUNCTION__,__LINE__));

    }
    return 0;
}

static INT32 _acfg_cust_rj45(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    UINT8    ui1_val = (UINT8)c_strtoll(pps_argv[1], NULL, 0);
    UINT8    aui1_val[6] = {0};
    UINT8    ui1_idx = 0;

    if(ui1_val == 0) //read
    {
        a_cfg_cust_drv_read_RJ45_value(aui1_val);
        for(ui1_idx = 0; ui1_idx < 6;ui1_idx++)
        {
            DBG_LOG_PRINT((" *aui1_val[%d] :%d \r\n",ui1_idx,aui1_val[ui1_idx]));
        }

    }
    else if (ui1_val == 1) //write
    {
        for(ui1_idx = 0; ui1_idx < 6;ui1_idx++)
        {
            aui1_val[ui1_idx] = (UINT16)c_strtoll(pps_argv[ui1_idx + 2], NULL, 0);
        }
        a_cfg_cust_drv_write_RJ45_value(aui1_val);
    }
    else if (ui1_val == 2) //update
    {
        a_cfg_cust_drv_update_eth0_mac();
    }
    else
    {
        DBG_LOG_PRINT(("[ACFG] Invalid value %s,%d\r\n",__FUNCTION__,__LINE__));

    }
    return 0;
}

static INT32 _acfg_cust_set_splayer_dl(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));
    UINT8       ui1_level = 0;

    ui1_level = (UINT8)c_strtoll(pps_argv[1], NULL, 0);
    ui1_g_splayer_level = ui1_level;
    return 0;
}

UINT8 a_cfg_get_splayer_dl(VOID)
{
    return ui1_g_splayer_level;
}

static INT32 _acfg_cust_set_acfg_dl(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8       ui1_level = 0;

    ui1_level = (UINT8)c_strtoll(pps_argv[1], NULL, 0);
    ui1_g_acfg_level = ui1_level;
    DBG_LOG_PRINT(("[ACFG], acfg debug level :%d\r\n",ui1_level));
    return 0;
}

UINT8 a_cfg_get_acfg_dl(VOID)
{
    return ui1_g_acfg_level;
}

static INT32 _acfg_cust_hdr_type_fct(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8       ui1_op = 0;
    UINT8       ui1_type = 0;

    ui1_op = (UINT8)c_strtoll(pps_argv[1], NULL, 0);

    if (ui1_op ==  0) //set hdr type
    {
        ui1_type  = (UINT8)c_strtoll(pps_argv[2], NULL, 0);
        a_cfg_set_hdr_type(ui1_type);
        DBG_LOG_PRINT(("[ACFG],a_cfg_set_hdr_type ui1_type :%d\r\n",ui1_type));
    }
    else //get hdr type
    {
        ui1_type = a_cfg_get_hdr_type();
        DBG_LOG_PRINT(("[ACFG],a_cfg_get_hdr_type ui1_type :%d\r\n",ui1_type));
    }

    return 0;
}

static INT32 _acfg_set_vlog(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
       return APP_CFGR_OK;
    }

    if (pps_argv[1][0]>='0' && pps_argv[1][0] < '4'){
        a_cfg_cust_set_log_level(pps_argv[1][0] - '0');
        printf("[ACFG] log level set to %d success \n", pps_argv[1][0] - '0');
    } else {
        printf("[ACFG] INVALID args 0=>off,1=>ap,2=>kernel,3=>all\n");
    }
    return APP_CFGR_OK;
}

static INT32 _acfg_set_oled_off_rs(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
       return APP_CFGR_OK;
    }

    if (c_strcmp("y", pps_argv[1]) == 0 || c_strcmp("Y", pps_argv[1]) == 0)
    {
        a_cfg_cust_set_oled_off_rs(1);
        a_cfg_cust_set_oled_jb(0);
        a_amb_power_on(FALSE);
    }
    else if(c_strcmp("n", pps_argv[1]) == 0 || c_strcmp("N", pps_argv[1]) == 0)
    {
        a_cfg_cust_set_oled_off_rs(0);
    }
    return APP_CFGR_OK;
}

static INT32 _acfg_set_oled_jb(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
       return APP_CFGR_OK;
    }

    if (c_strcmp("y", pps_argv[1]) == 0 || c_strcmp("Y", pps_argv[1]) == 0)
    {
        a_cfg_cust_set_oled_jb(1);
        a_cfg_cust_set_oled_off_rs(1);
        a_amb_power_on(FALSE);
    }
    else if(c_strcmp("n", pps_argv[1]) == 0 || c_strcmp("N", pps_argv[1]) == 0)
    {
        a_cfg_cust_set_oled_jb(0);
    }
    return APP_CFGR_OK;
}

static INT32 _acfg_cust_get_oled_display_time(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
       return APP_CFGR_OK;
    }

    if (c_strcmp("0", pps_argv[1]) == 0)
    {
        UINT32 ui4_period_time = 0;
        UINT32 ui4_panel_time = 0;
        a_cfg_cust_drv_get_oled_display_period(&ui4_period_time);
        a_cfg_custom_get_oled_panel_display_time(&ui4_panel_time);
        DBG_LOG_PRINT(("period:%d min\n",ui4_period_time > ui4_panel_time ?  ui4_period_time : ui4_panel_time));
    }
    else if(c_strcmp("1", pps_argv[1]) == 0)
    {
        UINT32 ui4_display_total = 0;
        a_cfg_cust_drv_get_oled_display_time(&ui4_display_total);
        DBG_LOG_PRINT(("total:%d min\n",ui4_display_total));
    }
    return APP_CFGR_OK;
}

static INT32 _acfg_cust_set_oled_display_time(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 2)
    {
       return APP_CFGR_OK;
    }

    UINT32 ui4_new_value = (UINT32)atoi(pps_argv[2]);

    if (c_strcmp("1", pps_argv[1]) == 0)
    {
        if(ui4_new_value >= 0)
        {
            a_cfg_cust_drv_set_oled_display_time(ui4_new_value);
            a_cfg_cust_drv_get_oled_display_time(&ui4_new_value);
            DBG_LOG_PRINT(("new total display time:%d min\n",ui4_new_value));
        }
    }
    else if(c_strcmp("0", pps_argv[1]) == 0)
    {
        UINT32 ui4_panel_time = 0;
        a_cfg_custom_set_oled_panel_display_time(ui4_new_value);
        a_cfg_custom_get_oled_panel_display_time(&ui4_panel_time);
        DBG_LOG_PRINT(("period:%d min\n", ui4_panel_time));
    }
    return APP_CFGR_OK;
}

static INT32 _acfg_cust_get_oled_jb_cooling_time(INT32 i4_argc,const CHAR** pps_argv)
{
    UINT16 ui2_cooling_time = 0;
    a_cfg_custom_get_oled_jb_cooling_time(&ui2_cooling_time);
    DBG_LOG_PRINT(("current cooling time:%d min\n",ui2_cooling_time));
    return APP_CFGR_OK;
}

static INT32 _acfg_cust_set_oled_jb_cooling_time(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
       return APP_CFGR_OK;
    }
    UINT16 ui2_cooling_time = 0;
    UINT16 ui2_new_value = (UINT32)atoi(pps_argv[1]);
    if(ui2_new_value > 0)
    {
        a_cfg_custom_set_oled_jb_cooling_time(ui2_new_value);
        a_cfg_custom_get_oled_jb_cooling_time(&ui2_cooling_time);
        DBG_LOG_PRINT(("current cooling time:%d min\n",ui2_cooling_time));
    }
    else
    {
        DBG_LOG_PRINT(("error at less 1 min\n"));
    }
    return APP_CFGR_OK;

}

static INT32 _acfg_is_lightsensor_support(INT32 i4_argc,const CHAR** pps_argv)
{
    BOOL b_support = a_cfg_cust_drv_is_lightsensor_support();

    DBG_LOG_PRINT(("[ACFG], a_cfg_cust_drv_is_lightsensor_support :%d\r\n",b_support));

    return APP_CFGR_OK;
}

static INT32 _acfg_oled_api_test(INT32 i4_argc,const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    INT32       i4_ret = 0;
    UINT8       ui1_type = 0;
    UINT8       ui1_op = 0;
    UINT8       ui1_val = 0;
    BOOL        b_enable = 0;
    UINT32      ui4_val = 0;
    UINT8       ui1_idx = 0;

    ui1_type = (UINT8)c_strtoll(pps_argv[1], NULL, 0);
    ui1_op  = (UINT8)c_strtoll(pps_argv[2], NULL, 0);
    ui1_val  = (UINT8)c_strtoll(pps_argv[3], NULL, 0);

    switch(ui1_type)
    {
        case ACFG_OLED_API_OFF_RS:
        {
            if(ui1_op == 0) //set
            {
                i4_ret = a_cfg_cust_drv_set_oled_off_rs(ui1_val);
            }
            else //get
            {
                b_enable = a_cfg_cust_drv_get_oled_off_rs();
                DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_get_oled_off_rs :%d\r\n",b_enable));
            }
        }
        break;
        case ACFG_OLED_API_JB:
        {
            if(ui1_op == 0) //set
            {
                i4_ret = a_cfg_cust_drv_set_oled_jb(ui1_val);
            }
            else //get
            {
                b_enable = a_cfg_cust_drv_get_oled_jb();
                DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_get_oled_jb :%d\r\n",b_enable));
            }
        }
            break;
        case ACFG_OLED_API_LEA:
        {
            if(ui1_op == 0) //set
            {
                i4_ret = a_cfg_cust_drv_set_oled_lea(ui1_val);
            }
            else //get
            {
                b_enable = a_cfg_cust_drv_get_oled_lea();
                DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_get_oled_lea :%d\r\n",b_enable));
            }
        }
            break;
        case ACFG_OLED_API_TPC:
        {
            if(ui1_op == 0) //set
            {
                i4_ret = a_cfg_cust_drv_set_oled_tpc(ui1_val);
            }
            else //get
            {
                b_enable = a_cfg_cust_drv_get_oled_tpc();
                DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_get_oled_tpc :%d\r\n",b_enable));
            }
        }
            break;
        case ACFG_OLED_API_CPC:
        {
            if(ui1_op == 0) //set
            {
                i4_ret = a_cfg_cust_drv_set_oled_cpc(ui1_val);
            }
            else //get
            {
                b_enable = a_cfg_cust_drv_get_oled_cpc();
                DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_get_oled_cpc :%d\r\n",b_enable));
            }
        }
            break;
        case ACFG_OLED_API_HDR:
        {
            if(ui1_op == 0) //set
            {
                i4_ret = a_cfg_cust_drv_set_oled_hdr(ui1_val);
            }
            else //get
            {
                b_enable = a_cfg_cust_drv_get_oled_hdr();
                DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_get_oled_hdr :%d\r\n",b_enable));
            }
        }
            break;
        case ACFG_OLED_API_PLC_CURVE:
        {
            OLED_PLC_CURVE_INFO_T t_info;
            c_memset(&t_info, 0, sizeof(t_info));

            if(ui1_op == 0) //set
            {
                i4_ret = a_cfg_cust_drv_get_oled_plc_curve(&t_info,sizeof(t_info));
                DBG_LOG_PRINT(("ui1_Curve: %d ,\r\n",t_info.ui1_LumaGain));
                DBG_LOG_PRINT(("ui1_Curve: %d ,\r\n",t_info.ui2_StartPoint));
                for (ui1_idx = 0 ; ui1_idx < 8; ui1_idx++)
                {
                    DBG_LOG_PRINT(("ui1_Curve:idx %d :value %d ,\r\n",ui1_idx,t_info.ui1_Curve[ui1_idx]));
                    t_info.ui1_Curve[ui1_idx] = t_info.ui1_Curve[ui1_idx] + 1;
                }
                t_info.ui1_LumaGain = t_info.ui1_LumaGain + 1;
                t_info.ui2_StartPoint = t_info.ui2_StartPoint + 1;
                i4_ret = a_cfg_cust_drv_set_oled_plc_curve(&t_info,sizeof(t_info));
            }
            else //get
            {
                i4_ret = a_cfg_cust_drv_get_oled_plc_curve(&t_info,sizeof(t_info));
                DBG_LOG_PRINT(("ui1_Curve: %d ,\r\n",t_info.ui1_LumaGain));
                DBG_LOG_PRINT(("ui1_Curve: %d ,\r\n",t_info.ui2_StartPoint));
                for (ui1_idx = 0 ; ui1_idx < 8; ui1_idx++)
                {
                    DBG_LOG_PRINT(("ui1_Curve:idx %d :value %d ,\r\n",ui1_idx,t_info.ui1_Curve[ui1_idx]));
                }
            }
        }
            break;
        case ACFG_OLED_API_TEMP:
        {
            i4_ret = a_cfg_cust_drv_get_oled_temperature(ui1_val,&ui4_val);
            DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_get_oled_temperature :%d\r\n",ui4_val));
            break;
        }
        case ACFG_OLED_API_ORBIT:
        {
            i4_ret = a_cfg_cust_drv_set_oled_orbit((BOOL)ui1_val);
            DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_set_oled_orbit :%d\r\n",ui4_val));
            break;
        }
        case ACFG_OLED_API_OFFRSJB_STATUS:
        {
            b_enable = a_cfg_cust_drv_get_oled_off_rs_jb_status();
            DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_get_oled_off_rs_jb_status :%d\r\n",b_enable));
            break;
        }
        default:
            break;
    }

    DBG_LOG_PRINT(("[ACFG] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));

    return 0;
}

static INT32 _acfg_cust_sif(INT32 i4_argc, const CHAR** pps_argv)
{
    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    INT32       i4_ret     = 0;
    UINT8       ui1_type   = 0;
    UINT32      ui4_addr   = 0;              /* device address */
    UINT32      ui4_offset = 0;            /* sub-address (or called offset) */
    UINT8       ui1_idx    = 0;
    UINT8       ui1_data   = 0;

    MISC_TYPE_SIF_ADVANCED_T t_info;

    c_memset(&t_info, 0, sizeof(t_info));

    ui1_type = (UINT8)c_strtoll(pps_argv[1], NULL, 0);
    ui4_addr = (UINT32)c_strtoll(pps_argv[2], NULL, 0);
    ui4_offset = (UINT32)c_strtoll(pps_argv[3], NULL, 0);
    ui1_data = (UINT8)c_strtoll(pps_argv[4], NULL, 0);

    t_info.ui1_channel = 9;
    t_info.ui2_clkdiv = 200;
    t_info.ui4_addr = 0x62;
    t_info.ui1_offset_len = 1;
    t_info.ui4_offset = ui4_offset;
    t_info.ui1_data_len = 1;

    for(ui1_idx = 0; ui1_idx < 16;ui1_idx ++)
    {
       t_info.pui1_data[ui1_idx] = ui1_data;
    }

    if(ui1_type == 0) //write sif data
    {
        i4_ret = a_cfg_cust_set_sif_data(&t_info,sizeof(t_info));
        DBG_LOG_PRINT(("[ACFG]  ui1_channel %d\r\n",t_info.ui1_channel));
        DBG_LOG_PRINT(("[ACFG]ui2_clkdiv %d\r\n",t_info.ui2_clkdiv));
        DBG_LOG_PRINT(("[ACFG]ui4_addr %d\r\n",t_info.ui4_addr));
        DBG_LOG_PRINT(("[ACFG]ui1_offset_len %d\r\n",t_info.ui1_offset_len));
        DBG_LOG_PRINT(("[ACFG]ui4_offset %d\r\n",t_info.ui4_offset));
        DBG_LOG_PRINT(("[ACFG]ui1_data_len %d\r\n",t_info.ui1_data_len));
        DBG_LOG_PRINT(("[ACFG]pui1_data %d\r\n", t_info.pui1_data[0]));
        DBG_LOG_PRINT(("[ACFG]   a_cfg_cust_set_sif_data type %s,%d\r\n",__FUNCTION__,__LINE__));
    }
    else if(ui1_type == 1)//read sif data
    {
        i4_ret = a_cfg_cust_get_sif_data(&t_info,sizeof(t_info));
        DBG_LOG_PRINT(("[ACFG]  ui1_channel %d\r\n",t_info.ui1_channel));
        DBG_LOG_PRINT(("[ACFG]ui2_clkdiv %d\r\n",t_info.ui2_clkdiv));
        DBG_LOG_PRINT(("[ACFG]ui4_addr %d\r\n",t_info.ui4_addr));
        DBG_LOG_PRINT(("[ACFG]ui1_offset_len %d\r\n",t_info.ui1_offset_len));
        DBG_LOG_PRINT(("[ACFG]ui4_offset %d\r\n",t_info.ui4_offset));
        DBG_LOG_PRINT(("[ACFG]ui1_data_len %d\r\n",t_info.ui1_data_len));
        DBG_LOG_PRINT(("[ACFG]pui1_data %d\r\n", t_info.pui1_data[0]));
        DBG_LOG_PRINT(("[ACFG]  a_cfg_cust_get_sif_data type %s,%d\r\n",__FUNCTION__,__LINE__));
    }
    else
    {
        DBG_LOG_PRINT(("[ACFG]invalid type %s,%d\r\n",__FUNCTION__,__LINE__));
    }
    DBG_LOG_PRINT(("[ACFG] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));

    return 0;
}

static INT32 _acfg_cust_skip_oobe(INT32 i4_argc,const CHAR** pps_argv)
{
    a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));
    a_cfg_store();
    a_amb_enable_system_key(TRUE);
    a_amb_enable_power_key(TRUE);
    a_amb_reboot();
    return APP_CFGR_OK;
}

static INT32 _acfg_cust_set_power_mode(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
       return APP_CFGR_OK;
    }

    if (c_strcmp("0", pps_argv[1]) == 0)
    {
        a_icl_custom_set_power_mode(0);
        a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_ON);
        a_cfg_custom_set_drv_eco_mode(0);
        rest_event_notify("tv_settings/system/power_mode",0,"Eco Mode");
    }
    else
    {
        a_icl_custom_set_power_mode(1);
        a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_OFF);
        a_cfg_custom_set_drv_eco_mode(1);
        rest_event_notify("tv_settings/system/power_mode",0,"Quick Start");
    }
    return APP_CFGR_OK;
}

static INT32 _acfg_cust_bootlogo_show_test(INT32 i4_argc, const CHAR** pps_argv)
{
    extern char g_bootlogo_file_path[256];

    DBG_LOG_PRINT(("[ACFG] %s,%d\r\n",__FUNCTION__,__LINE__));

    if (i4_argc <= 1)
    {
        return APP_CFGR_OK;
    }

    if(c_strcmp("show", pps_argv[1]) == 0 && i4_argc == 2)
    {
        a_cfg_custom_draw_logo_image(BOOTLOGO_INIT);
        a_cfg_custom_draw_logo_image(BOOTLOGO_SHOW);
    }
    else if(c_strcmp("show", pps_argv[1]) == 0 && i4_argc == 3)
    {
        memcpy(g_bootlogo_file_path,pps_argv[2],strlen(pps_argv[2]));
        DBG_LOG_PRINT(("[ACFG] %s,%d  bootlogo_file_path:%s \r\n",__FUNCTION__,__LINE__,g_bootlogo_file_path));
        a_cfg_custom_draw_logo_image(BOOTLOGO_INIT);
        a_cfg_custom_draw_logo_image(BOOTLOGO_SHOW);
    }
    else if(c_strcmp("hide", pps_argv[1]) == 0 && i4_argc == 2)
    {
        a_cfg_custom_draw_logo_image(BOOTLOGO_HIDE);
        a_cfg_custom_draw_logo_image(BOOTLOGO_DEINIT);
    }
    else
    {
        DBG_LOG_PRINT(("[ACFG] Invalid value %s,%d\r\n",__FUNCTION__,__LINE__));
    }

    return APP_CFGR_OK;

}


static INT32 _acfg_cust_get_pq_ver_by_bin_type(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
       return APP_CFGR_OK;
    }

    UINT8 ui1_HSY_ver[16]   = {0};
    UINT8 ui1_idx           = (UINT8)c_strtoll(pps_argv[1], NULL, 0);

    a_cfg_cust_drv_get_pq_ver_by_bin_type(ui1_idx, ui1_HSY_ver, sizeof(ui1_HSY_ver));
    ui1_HSY_ver[15]   = '\0';

    DBG_LOG_PRINT(("%s\n",(CHAR*)ui1_HSY_ver));

    return APP_CFGR_OK;
}

static INT32 _acfg_cust_reboot_tv(INT32 i4_argc,const CHAR** pps_argv)
{
    if(a_am_is_power_on())
    {
        a_cfg_custom_service_reset(1,ACFG_FORCE_REBOOT_UP_ON);
    }
    else
    {
        a_cfg_custom_set_drv_bgmupdate_flag(1);
        a_cfg_cust_set_force_reboot_up_flag(ACFG_FORCE_REBOOT_UP_OFF);
        system("reboot");
    }
    return APP_CFGR_OK;
}

static INT32 _acfg_cust_set_panel_ssc_en(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
       return APP_CFGR_OK;
    }

    if (c_strcmp("0", pps_argv[1]) == 0)
    {
        a_cfg_cust_set_panel_ssc_en(0);
    }
    else if (c_strcmp("1", pps_argv[1]) == 0)
    {
        a_cfg_cust_set_panel_ssc_en(1);
    }
    else
    {
        DBG_LOG_PRINT(("[ACFG] Invalid value %s,%d\r\n",__FUNCTION__,__LINE__));
    }
    return APP_CFGR_OK;
}

static INT32 _acfg_cust_reset_wifi(INT32 i4_argc,const CHAR** pps_argv)
{
#ifdef MT5583_MODEL
    DBG_LOG_PRINT(("[MT5583 Model]%s %d Reset Wifi\r\n",__FUNCTION__,__LINE__));
    c_pcl_set_gpio(16, PCL_GPIO_STATUS_LOW);
    c_thread_delay(20);
    c_pcl_set_gpio(16, PCL_GPIO_STATUS_HIGH);
#endif
    return APP_CFGR_OK;
}

static INT32 _acfg_cust_set_demura(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
       return APP_CFGR_OK;
    }

    if (c_strcmp("0", pps_argv[1]) == 0)
    {
        a_cfg_cust_set_demura(0);
    }
    else if (c_strcmp("1", pps_argv[1]) == 0)
    {
        a_cfg_cust_set_demura(1);
    }
    else
    {
        DBG_LOG_PRINT(("[ACFG] Invalid value %s,%d\r\n",__FUNCTION__,__LINE__));
    }
    return APP_CFGR_OK;
}

static INT32 _acfg_cust_get_demura(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
       return APP_CFGR_OK;
    }
    UINT32 *pu32_RegValue = NULL;

    a_cfg_cust_get_demura(pu32_RegValue);
    DBG_LOG_PRINT(("[ACFG] %s,%d, Demura RegValue = %s\r\n",__FUNCTION__,__LINE__,*pu32_RegValue));

    return APP_CFGR_OK;
}

static INT32 _acfg_cust_set_led_indicator_para(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
        return APP_CFGR_OK;
    }
        printf("\x1b[31m[Frank] %s [%d] [%s]\x1b[0m\n",__FUNCTION__,__LINE__,__FILE__);
        PM_LedModeConfig_t stLedModeConfig;
        memset(&stLedModeConfig, 0, sizeof(PM_LedModeConfig_t));

        stLedModeConfig.u8StageSpaceTime = (UINT8)c_strtoll(pps_argv[1], NULL, 0);//state1 space Time 2s (/100ms),after 2s change to stage2
        stLedModeConfig.astStateInfo[0].eStageMode = (UINT8)c_strtoll(pps_argv[2], NULL, 0);//E_MI_PM_LED_MODE_ON
        stLedModeConfig.astStateInfo[0].stLedFlinkerParams.u8LightRate = (UINT8)c_strtoll(pps_argv[3], NULL, 0);//light_rate: 0~100%
        stLedModeConfig.astStateInfo[0].stLedFlinkerParams.u8Period = (UINT8)c_strtoll(pps_argv[4], NULL, 0);  //state1 flink period Tf: 1s (/100ms)
        stLedModeConfig.astStateInfo[0].stLedFlinkerParams.u8Duty = (UINT8)c_strtoll(pps_argv[5], NULL, 0);//state1 flink duty Tf_h: 500ms (/100ms)
        stLedModeConfig.astStateInfo[1].eStageMode = (UINT8)c_strtoll(pps_argv[6], NULL, 0);//E_MI_PM_LED_MODE_OFF
        stLedModeConfig.astStateInfo[1].stLedBreathParams.u8LightRate = (UINT8)c_strtoll(pps_argv[7], NULL, 0);
        stLedModeConfig.astStateInfo[1].stLedBreathParams.u8DarkTime = (UINT8)c_strtoll(pps_argv[8], NULL, 0);//state2 breath(low) Tb1: 1s(/100ms)
        stLedModeConfig.astStateInfo[1].stLedBreathParams.u8DarkToLightTime = (UINT8)c_strtoll(pps_argv[9], NULL, 0);  //state2 breath(low->high) Tb2: 4s(/100ms)
        stLedModeConfig.astStateInfo[1].stLedBreathParams.u8LightTime = (UINT8)c_strtoll(pps_argv[10], NULL, 0); //state2 breath(high) Tb3: 2s(/100ms)
        stLedModeConfig.astStateInfo[1].stLedBreathParams.u8LightToDarkTime = (UINT8)c_strtoll(pps_argv[11], NULL, 0); //state2 breath(high->low) Tb4: 4s(/100ms)

        a_cfg_cust_set_LED_indicator(&stLedModeConfig, sizeof(PM_LedModeConfig_t));

        return APP_CFGR_OK;
}

static INT32 _acfg_set_src_name_log(INT32 i4_argc,const CHAR** pps_argv)
{
    if (i4_argc <= 1)
    {
       return APP_CFGR_OK;
    }

    if (c_strcmp("1", pps_argv[1]) == 0){
        ui1_g_src_name_log = 1;
        printf("[ACFG] _acfg_set_src_name_log to 1 \n");
    } 
    else if (c_strcmp("0", pps_argv[1]) == 0){
        ui1_g_src_name_log = 0;
        printf("[ACFG] _acfg_set_src_name_log to 0 \n");
    } 
    return APP_CFGR_OK;
}

UINT8 a_cfg_get_src_name_log(VOID)
{
    return ui1_g_src_name_log;
}


/*-----------------------------------------------------------------------------
 * Name: acfg_cust_regist_cli_cmd_tbl
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *---------------------------------------------------------------------------*/
VOID acfg_cust_regist_cli_cmd_tbl(VOID)
{
#ifdef NEVER
    acfg_register_customer_cli_entry(&t_acfg_cust_set_gamma_table);
    acfg_register_customer_cli_entry(&t_acfg_cust_get_gamma_table);
#endif /* NEVER */
    acfg_register_customer_cli_entry(&t_acfg_cust_set_hdcp_key);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_gamma_simple_table);
    acfg_register_customer_cli_entry(&t_acfg_cust_get_gamma_simple_table);
    acfg_register_customer_cli_entry(&t_acfg_cust_gamma_on_off);
    acfg_register_customer_cli_entry(&t_acfg_cust_rgb_pattern);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_pq_bypss);
    acfg_register_customer_cli_entry(&t_acfg_cust_get_rgb_yuv);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_lcd);
    acfg_register_customer_cli_entry(&t_acfg_cust_panel_nits);
    acfg_register_customer_cli_entry(&t_acfg_cust_rj45);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_splayer_dl);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_acfg_dl);
    acfg_register_customer_cli_entry(&t_acfg_cust_hdr_type);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_vlog);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_oled_off_rs);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_oled_jb);
    acfg_register_customer_cli_entry(&t_acfg_cust_is_lightsensor_support);
    acfg_register_customer_cli_entry(&t_acfg_cust_oled_api_test);
    acfg_register_customer_cli_entry(&t_acfg_cust_sif);
    acfg_register_customer_cli_entry(&t_acfg_cust_skip_oobe);
    acfg_register_customer_cli_entry(&t_acfg_cust_bootlogo_show_test);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_power_mode);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_oled_display_time);
    acfg_register_customer_cli_entry(&t_acfg_cust_get_oled_display_time);
    acfg_register_customer_cli_entry(&t_acfg_cust_get_oled_jb_cooling_time);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_oled_jb_cooling_time);
    acfg_register_customer_cli_entry(&t_acfg_cust_get_pq_version_by_bin_type);
    acfg_register_customer_cli_entry(&t_acfg_cust_reboot_tv);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_panel_ssc_en);
    acfg_register_customer_cli_entry(&t_acfg_cust_reset_wifi);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_demura);
    acfg_register_customer_cli_entry(&t_acfg_cust_get_demura);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_led_indicator_para);
    acfg_register_customer_cli_entry(&t_acfg_cust_set_src_name_log);
}
#endif

